#include <stdio.h>
#include <sys/types.h>
#include <Query.h>
#include <Fault.h>
#include <Message.h>
#include <time.h>
#include <sys/time.h>
#include <utils.h>

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

        if (endswith(filename, ".ber"))
            m = time_decode(&ber_decode, buf, read, 100000);
        else if (endswith(filename, ".xml"))
            m = time_decode(&xer_decode, buf, read, 100000);

        printf("%s, %Lf, %Lf, %ld\n", filename, m.average, m.total, fsize);

        free(buf);
    }

    return 0;
}
