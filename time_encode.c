#include <stdio.h>
#include <sys/types.h>
#include <Message.h>
#include <stdlib.h>
#include <time.h>
#include <utils.h>

int main(int ac, char **av)
{

    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s <file.{ber,xml}> ...\n", av[0]);
        exit(1);
    }

    printf("\"Filename\", \"Average\", \"Total\", \"Bytes\"\n");

    for (int i = 1; i < ac; i++)
    {
        // 1: Read file contents
        const char *filename = av[i];

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
        
        if (endswith(filename, ".ber"))
            rval = ber_decode(0, &asn_DEF_Message, (void **)&message, buf, read);
        else if (endswith(filename, ".xml"))
            rval = xer_decode(0, &asn_DEF_Message, (void **)&message, buf, read);
        free(buf);
        if (rval.code != RC_OK)
        {
            fprintf(stderr, "%s: Broken encoding at byte %ld\n", filename, rval.consumed);
            exit(1);
        }

        // 3: Measure
        Measurement_t m;
        if (endswith(filename, ".ber"))
            m = time_encode_der(message, 100000);
        else if (endswith(filename, ".xml"))
            m = time_encode_xer(message, 100000);

        printf("\"%s\", \"%Lf\", \"%Lf\", \"%ld\"\n", filename, m.average, m.total, fsize);
    }

    return 0;
}
