#include <stdio.h>
#include <sys/types.h>
#include <Message.h>
#include <stdlib.h>
#include <time.h>
#include <utils.h>

static const int ITERATIONS = 10;

int main(int ac, char **av)
{
    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s <file.{ber,xer,uper}> ...\n", av[0]);
        exit(1);
    }

    printf("Filename, Average, Total, Bytes\n");

    for (int i = 1; i < ac; i++)
    {
        // 1: Read file contents
        const char *filename = av[i];
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

        FILE *fp = fopen(filename, "rb");
        if (!fp)
        {
            perror(filename);
            exit(1);
        }

        fseek(fp, 0, SEEK_END);
        const size_t fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char *buf = malloc(fsize * sizeof(char));
        size_t read = fread(buf, 1, fsize, fp);
        fclose(fp);

        if (read != fsize)
        {
            fprintf(stderr, "%s: Empty or broken\n", filename);
            exit(1);
        }

        // 2: Decode
        Message_t *message = 0;
        asn_dec_rval_t rval;

        switch (encoding)
        {
        case BER:
            rval = ber_decode(0, &asn_DEF_Message, (void **)&message, buf, read);
            break;
        case XER:
            rval = xer_decode(0, &asn_DEF_Message, (void **)&message, buf, read);
            break;
        case UPER:
            rval = uper_decode(0, &asn_DEF_Message, (void **)&message, buf, read, 0, 0);
            break;
        default:
            perror("Invalid state: A valid encoding shout be set.\n");
            exit(1);
            break;
        }
        free(buf);

        if (rval.code != RC_OK)
        {
            fprintf(stderr, "%s: Broken encoding at byte %ld\n", filename, rval.consumed);
            exit(1);
        }

        // 3: Measure
        Measurement_t m;

        switch (encoding)
        {
        case BER:
            m = time_encode_der(message, ITERATIONS);
            break;
        case XER:
            m = time_encode_xer(message, ITERATIONS);
            break;
        case UPER:
            m = time_encode_uper(message, ITERATIONS);
            break;
        default:
            perror("Invalid state: A valid encoding shout be set.\n");
            exit(1);
            break;
        }

        printf("%s, %Lf, %Lf, %ld\n", filename, m.average, m.total, fsize);
    }

    return 0;
}
