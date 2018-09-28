#include <stdio.h>
#include <sys/types.h>
#include <Query.h>
#include <Fault.h>
#include <Message.h>
#include <time.h>

/*
Plan
- create large messages (10 MB)
- measure encoding / decoding speed
- measure message size (be fair to XML?)
- try BER / PER / XER
*/


void time_decode(Message_t *message, char *buf, size_t size)
{
    asn_dec_rval_t rval;
    clock_t start, stop;

    const uint64_t NUM = 100000000;
    long double total = 0.0;

    start = clock();
    for (uint64_t i = 0; i < NUM; i++)
    {
        ber_decode(0, &asn_DEF_Message, (void **)&message, buf, size);
    }
    stop = clock();

    total = (long double)(stop - start) / CLOCKS_PER_SEC;

    printf("print(%Lf / %ld)\n", total, NUM);
}

int main(int ac, char **av)
{
    char buf[8 * 1024];         /* Temporary buffer */
    asn_dec_rval_t rval;    /* Decoder return value */
    Message_t *message = 0; /* Type to decode. Note 0! */
    FILE *fp;               /* Input file handler */
    size_t size;            /* Number of bytes read */
    char *filename;         /* Input file name */

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
    rval = ber_decode(0, &asn_DEF_Message, (void **)&message, buf, size);
    if (rval.code != RC_OK)
    {
        fprintf(stderr, "%s: Broken encoding at byte %ld\n ",
                filename, rval.consumed);
        exit(1);
    }

    time_decode(message, buf, size);

    /* Print */
    // xer_fprint(stdout, &asn_DEF_Message, message);
    // asn_fprint(stdout, &asn_DEF_Message, message);
    ASN_STRUCT_FREE(asn_DEF_Message, message);
    return 0;
}