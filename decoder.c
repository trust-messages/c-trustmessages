#include <stdio.h>
#include <sys/types.h>
#include <Query.h>
#include <Fault.h>
#include <Message.h>

int main(int ac, char **av)
{
    char buf[1024];                   /* Temporary buffer */
    asn_dec_rval_t rval;              /* Decoder return value */
    void *instance = 0;               /* Type to decode. Note this 01! */
    FILE *fp;                         /* Input file handler */
    size_t size;                      /* Number of bytes read */
    char *filename;                   /* Input file name */
    char *typename;                   /* Input type name*/
    asn_TYPE_descriptor_t descriptor; /* Descriptor for parsing bytes */

    if (ac != 3)
    {
        fprintf(stderr, "Usage: %s <Type> <file.ber>\n", av[0]);
        exit(1);
    }
    else
    {
        typename = av[1];
        filename = av[2];
    }

    if (0 == strcmp("Query", typename))
    {
        descriptor = asn_DEF_Query;
    }
    else if (0 == strcmp("Fault", typename))
    {
        descriptor = asn_DEF_Fault;
    }
    else if (0 == strcmp("Message", typename))
    {
        descriptor = asn_DEF_Message;
    }
    else
    {
        fprintf(stderr, "Invalid type: %s \n", typename);
        exit(1);
    }

    /* Open input file as read-only binary */
    fp = fopen(filename, "rb");
    if (!fp)
    {
        perror(filename);
        exit(1);
    }
    /* Read up to the buffer size */
    size = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);
    if (!size)
    {
        fprintf(stderr, "%s: Empty or broken\n", filename);
        exit(1);
    }
    // decode
    rval = ber_decode(0, &descriptor, (void **)&instance, buf, size);
    if (rval.code != RC_OK)
    {
        fprintf(stderr, "%s: Broken encoding at byte %ld\n ",
                filename, (long)rval.consumed);
        exit(1);
    }
    /* Print as XML */
    xer_fprint(stdout, &descriptor, instance);
    return 0;
}