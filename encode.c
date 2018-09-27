#include <stdio.h>
#include <sys/types.h>
#include <FormatRequest.h>
#include <DataRequest.h>
#include <Message.h>

/* Write the encoded output into some FILE stream. */
static int write_out(const void *buffer, size_t size, void *app_key)
{
    FILE *out_fp = app_key;
    size_t wrote = fwrite(buffer, 1, size, out_fp);
    return (wrote == size) ? 0 : -1;
}

void create_format_request(Message_t *message)
{
    FormatRequest_t payload = 73;
    message->payload.present = payload_PR_format_request;
    message->payload.choice.format_request = payload;
    message->version = 1;
}

void create_data_request(Message_t *message)
{
    Service_t service = {"seller", 6};

    Query_t query;
    query.present = Query_PR_con;
    query.choice.con.value.present = Value_PR_service;
    query.choice.con.operator_c = operator_c_eq;
    query.choice.con.value.choice.service = service;

    DataRequest_t request;
    request.rid = 10;
    request.type_rq = type_rq_trust;
    request.query = query;

    message->payload.choice.data_request = request;
    message->payload.present = payload_PR_data_request;
    message->version = 1;
}

int main(int ac, char **av)
{
    // printf("Message_t size = %lu\n", sizeof(Message_t));
    // 240 ... hum?

    // Message_t message;
    Message_t *message = calloc(1, sizeof(Message_t));
    if (!message)
    {
        perror("calloc() failed");
        exit(1);
    }

    // create_format_request(message);
    create_data_request(message);

    if (ac < 2)
    {
        fprintf(stderr, "Specify filename for BER output\n");
    }
    else
    {
        const char *filename = av[1];
        FILE *fp = fopen(filename, "wb"); /* for BER output */
        if (!fp)
        {
            perror(filename);
            exit(1);
        }

        asn_enc_rval_t ec = der_encode(&asn_DEF_Message, message, write_out, fp);
        fclose(fp);
        if (ec.encoded == -1)
        {
            fprintf(stderr, "Could not encode, error at %s\n",
                    ec.failed_type ? ec.failed_type->name : "unknown");
            exit(1);
        }
        else
        {
            fprintf(stderr, "Created %s with DER encodeding\n", filename);
        }
    }

    // xer_fprint(stdout, &asn_DEF_Message, message);
    asn_fprint(stdout, &asn_DEF_Message, message);

    // ASN_STRUCT_FREE(asn_DEF_Message, message);
    return 0;
}