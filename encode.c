#include <stdio.h>
#include <sys/types.h>
#include <Message.h>
#include <stdlib.h>
#include <time.h>
#include <utils.h>

int main(int ac, char **av)
{
    Message_t *message = calloc(1, sizeof(Message_t));
    if (!message)
    {
        perror("calloc() failed");
        exit(1);
    }

    // create_format_request(message);
    // create_data_request(message);
    // create_data_request_exp(message);
    // create_format_response(message);
    // create_fault(message);
    create_data_response(message, 1000);

    const Measurement_t m = time_encode_der(message, 10);
    printf("Total: %Lf, Average: %Lf, size: %.2f MB (%lu B)\n", m.total, m.average, (double)m.size / 1024 / 1024, m.size);
    return 0;

    const char *filename;
    asn_enc_rval_t ec;
    if (ac < 2)
    {
        filename = "RAM";
        printf("Destination: RAM\n");
        ec = der_encode(&asn_DEF_Message, message, NULL, NULL);
    }
    else
    {
        filename = av[1];
        FILE *fp = fopen(filename, "wb");
        if (!fp)
        {
            perror(filename);
            exit(1);
        }

        printf("Destination: %s\n", filename);
        ec = der_encode(&asn_DEF_Message, message, write_out, fp);
        fclose(fp);
    }

    if (ec.encoded == -1)
    {
        fprintf(stderr, "Could not encode, error at %s\n",
                ec.failed_type ? ec.failed_type->name : "unknown");
        exit(1);
    }
    else
    {
        printf("Size: %.2f MB (%ld B)\n", (double)ec.encoded / 1024 / 1024, ec.encoded);
    }

    char buff[200];
    size_t errSize = sizeof(buff);
    int rv = asn_check_constraints(&asn_DEF_Message, message, buff, &errSize);

    if (rv == 0)
    {
        printf("Validity: OK\n");
    }
    else
    {
        printf("Validity: False -- %s\n", buff);
    }

    // xer_fprint(stdout, &asn_DEF_Message, message);
    // asn_fprint(stdout, &asn_DEF_Message, message);
    ASN_STRUCT_FREE(asn_DEF_Message, message);
    // ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_Message, &message);
    return 0;
}
