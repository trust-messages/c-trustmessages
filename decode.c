#include <stdio.h>
#include <sys/types.h>
#include <Query.h>
#include <Fault.h>
#include <Message.h>
#include <time.h>
#include <sys/time.h>
#include <utils.h>

/*
Plan
- create large messages (10 MB)
- measure encoding / decoding speed
- measure message size (be fair to XML?)
- try BER / XER (/ PER)
*/

int main(int ac, char **av)
{
    if (ac != 2)
    {
        fprintf(stderr, "Usage: %s <file.ber>\n", av[0]);
        exit(1);
    }
    const char *filename = av[1];

    /* Open input file as read-only binary */
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        perror(filename);
        exit(1);
    }

    Encoding encoding;
    if (endswith(filename, ".ber"))
    {
        encoding = BER;
    }
    else if (endswith(filename, ".xer"))
    {
        encoding = XER;
    }
    else if (endswith(filename, ".uper"))
    {
        encoding = UPER;
    }
    else
    {
        printf("Unknown file: %s\n", filename);
        exit(1);
    }

    // file size in bytes
    fseek(fp, 0, SEEK_END);
    const size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    printf("fsize: %ld bytes (%.2f MB)\n", fsize, (double)fsize / 1024.0 / 1024.0);

    struct timeval start, stop;

    char *buf = malloc(fsize * sizeof(char));
    gettimeofday(&start, NULL);
    size_t read = fread(buf, 1, fsize, fp);
    gettimeofday(&stop, NULL);
    fclose(fp);

    printf("fread: %Lf\n", duration(&start, &stop));

    if (read != fsize)
    {
        fprintf(stderr, "%s: Empty or broken\n", filename);
        exit(1);
    }

    // const Measurement_t m = time_decode(&ber_decode, buf, read, 100);
    // printf("Total: %Lf, Average %Lf\n", m.total, m.average);

    // decode
    Message_t *message = 0; // Type to decode: remember 0!
    asn_dec_rval_t rval;

    switch (encoding)
    {
    case BER:
        gettimeofday(&start, NULL);
        rval = ber_decode(0, &asn_DEF_Message, (void **)&message, buf, read);
        gettimeofday(&stop, NULL);
        break;
    case XER:
        gettimeofday(&start, NULL);
        rval = xer_decode(0, &asn_DEF_Message, (void **)&message, buf, read);
        gettimeofday(&stop, NULL);
        break;
    case UPER:
        gettimeofday(&start, NULL);
        rval = uper_decode(0, &asn_DEF_Message, (void **)&message, buf, read, 0, 0);
        gettimeofday(&stop, NULL);
        break;
    default:
        perror("Invalid state: A valid encoding shout be set.\n");
        exit(1);
        break;
    }

    printf("decode: %Lf\n", duration(&start, &stop));

    if (rval.code != RC_OK)
    {
        fprintf(stderr, "%s: Broken encoding at byte %ld\n", filename, rval.consumed);
        exit(1);
    }
    //time_decode(&ber_decode, buf, read, 10);
    free(buf);

    // xer_fprint(stdout, &asn_DEF_Message, message);
    asn_fprint(stdout, &asn_DEF_Message, message);

    ASN_STRUCT_FREE(asn_DEF_Message, message);
    return 0;
}
