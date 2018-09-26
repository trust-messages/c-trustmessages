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

void create_format_request(Message_t *instance)
{
    FormatRequest_t *payload = calloc(1, sizeof(FormatRequest_t));
    if (!payload)
    {
        perror("calloc() failed");
        exit(1);
    }
    *payload = 73;
    instance->payload.present = payload_PR_format_request;
    instance->payload.choice.format_request = *payload;
}

void create_data_request(Message_t *instance)
{
    DataRequest_t *payload = calloc(1, sizeof(DataRequest_t));
    if (!payload)
    {
        perror("calloc() failed");
        exit(1);
    }

    payload->rid = 10;
    payload->type_rq = type_rq_trust;

    Query_t *query = calloc(1, sizeof(Query_t));
    if (!query)
    {
        perror("calloc() failed");
        exit(1);
    }
    
    Service_t *service = calloc(1, sizeof(Service_t));
    if (!service)
    {
        perror("calloc() failed");
        exit(1);
    }
    service->buf = "seller";
    service->size = 6;
    query->choice.con.value.present = Value_PR_service;
    query->choice.con.value.choice.service = *service;
    query->choice.con.operator_c = operator_c_eq;
    query->present = Query_PR_con;
    payload->query = *query;

    instance->payload.present = payload_PR_data_request;
    instance->payload.choice.data_request = *payload;
}

int main(int ac, char **av)
{
    Message_t *instance = calloc(1, sizeof(Message_t));
    if (!instance)
    {
        perror("calloc() failed");
        exit(1);
    }
    instance->version = 1;

    // create_format_request(instance);
    create_data_request(instance);

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

        asn_enc_rval_t ec = der_encode(&asn_DEF_Message, instance, write_out, fp);
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

    // xer_fprint(stdout, &asn_DEF_Message, instance);
    asn_fprint(stdout, &asn_DEF_Message, instance);

    // ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_Message, instance);
    return 0;
}