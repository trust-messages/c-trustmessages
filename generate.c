#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <utils.h>

int main(int ac, char **av)
{
    Message_t *message = calloc(1, sizeof(Message_t));

    char usage[200];
    sprintf(usage, "Usage: %s <data-request | data-response | format-request | format-response | fault> <out-filename>\n", av[0]);

    if (!message)
    {
        perror("calloc() failed");
        exit(1);
    }

    if (ac < 3)
    {
        printf("%s", usage);
        exit(1);
    }

    const char *messageType = av[1];
    const char *filename = av[2];

    if (0 == strcmp(messageType, "data-request"))
    {
        create_data_request_exp(message);
    }
    else if (0 == strcmp(messageType, "data-response"))
    {
        create_data_response(message, BER, 2000);
    }
    else if (0 == strcmp(messageType, "format-request"))
    {
        create_format_request(message);
    }
    else if (0 == strcmp(messageType, "format-response"))
    {
        create_format_response(message);
    }
    else if (0 == strcmp(messageType, "fault"))
    {
        create_fault(message);
    }
    else
    {
        printf("ERROR: An invalid message type parameter: %s\n", messageType);
        printf("%s", usage);
        exit(1);
    }

    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        perror(filename);
        exit(1);
    }

    asn_enc_rval_t ec;
    if (endswith(filename, ".ber"))
    {
        ec = der_encode(&asn_DEF_Message, message, write_out, fp);
    }
    else if (endswith(filename, ".xml"))
    {
        ec = xer_encode(&asn_DEF_Message, message, XER_F_BASIC, write_out, fp);
    }
    else if (endswith(filename, ".per"))
    {
        /*
        struct asn_TYPE_descriptor_s *type_descriptor,
        asn_per_constraints_t *constraints,
        void *struct_ptr,	// Structure to be encoded
        void **buffer_r		// Buffer allocated and returned
        */
        ec = uper_encode(&asn_DEF_Message, message, write_out, fp);
    }
    else
    {
        perror("ERROR: File suffix has to be .ber, .xer, or .per\n");
        exit(1);
    }

    fclose(fp);

    if (ec.encoded == -1)
    {
        fprintf(stderr, "Could not encode, error at %s\n",
                ec.failed_type ? ec.failed_type->name : "unknown");
        exit(1);
    }

    char buff[200];
    size_t errSize = sizeof(buff);
    int rv = asn_check_constraints(&asn_DEF_Message, message, buff, &errSize);

    ASN_STRUCT_FREE(asn_DEF_Message, message);
    return 0;
}
