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

    if (ac != 2)
    {
        fprintf(stderr, "Usage: %s <file.ber>\n", av[0]);
        exit(1);
    }
    else
    {
        filename = av[1];
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
    rval = ber_decode(0, &asn_DEF_Message, &instance, buf, size);
    if (rval.code != RC_OK)
    {
        fprintf(stderr, "%s: Broken encoding at byte %ld\n ",
                filename, rval.consumed);
        exit(1);
    }
    /* Print as XML */
    xer_fprint(stdout, &asn_DEF_Message, instance);
    return 0;
}