#include <stdio.h>
#include <sys/types.h>
#include <Query.h>
#include <Fault.h>
#include <Message.h>
#include <time.h>
#include <sys/time.h>
#include <utils.h>

static int ITERATIONS = 10000;

int main(int ac, char **av)
{
    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s <file.ber>\n", av[0]);
        exit(1);
    }

    printf("Filename, Average, Total, Bytes\n");

    for (int i = 1; i < ac; i++)
    {
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

        struct timeval start, stop;

        char *buf = malloc(fsize * sizeof(char));
        gettimeofday(&start, NULL);
        size_t read = fread(buf, 1, fsize, fp);
        gettimeofday(&stop, NULL);
        fclose(fp);

        if (read != fsize)
        {
            fprintf(stderr, "%s: Empty or broken\n", filename);
            exit(1);
        }

        Measurement_t m;

        switch (encoding)
        {
        case BER:
            m = time_decode_ber(buf, read, ITERATIONS);
            break;
        case XER:
            m = time_decode_xer(buf, read, ITERATIONS);
            break;
        case UPER:
            m = time_decode_uper(buf, read, ITERATIONS);
            break;
        default:
            perror("Invalid state: A valid encoding shout be set.\n");
            exit(1);
            break;
        }

        printf("%s, %Lf, %Lf, %ld\n", filename, m.average, m.total, fsize);

        free(buf);
    }

    return 0;
}
