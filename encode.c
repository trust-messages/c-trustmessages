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
    Service_t service = {strdup("seller"), 6};
    Value_t value = {Value_PR_service, .choice.service = service};
    Constraint_t con = {operator_c_eq, value};
    Query_t query = {Query_PR_con, con};
    DataRequest_t request = {10, type_rq_assessment, query};

    message->payload.choice.data_request = request;
    message->payload.present = payload_PR_data_request;
    message->version = 1;
}

void create_data_request_exp(Message_t *message)
{
    Value_t left_value = {Value_PR_date, .choice.date = 123};
    Constraint_t left_con = {operator_c_eq, left_value};
    Query_t *left_query = calloc(1, sizeof(Query_t));
    left_query->present = Query_PR_con;
    left_query->choice.con = left_con;

    Value_t right_value = {Value_PR_date, .choice.date = 321};
    Constraint_t right_con = {operator_c_eq, right_value};
    Query_t *right_query = calloc(1, sizeof(Query_t));
    right_query->present = Query_PR_con;
    right_query->choice.con = right_con;

    Expression_t *expression = calloc(1, sizeof(Expression_t));
    expression->operator_e = operator_e_or;
    expression->left = left_query;
    expression->right = right_query;

    Query_t query = {Query_PR_exp, .choice.exp = expression};
    DataRequest_t request = {10, type_rq_trust, query};

    message->payload.choice.data_request = request;
    message->payload.present = payload_PR_data_request;
    message->version = 1;
}

int main(int ac, char **av)
{
    // printf("Message_t size = %lu\n", sizeof(Message_t));
    // 240 ... hum?
    Message_t *message = calloc(1, sizeof(Message_t));
    if (!message)
    {
        perror("calloc() failed");
        exit(1);
    }

    // create_format_request(message);
    create_data_request(message);
    // create_data_request_exp(message);

    if (ac < 2)
    {
        fprintf(stderr, "Specify filename for output\n");
    }
    else
    {
        const char *filename = av[1];
        FILE *fp = fopen(filename, "wb");
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
            fprintf(stderr, "Created %s\n", filename);
        }
    }

    char buff[200];
    size_t errSize = sizeof(buff);
    int rv = asn_check_constraints(&asn_DEF_Message, message, buff, &errSize);

    if (rv == 0)
    {
        printf("Message is valid.\n");
    }
    else
    {
        printf("Message invalid (code %d): %s\n", rv, buff);
    }

    // xer_fprint(stdout, &asn_DEF_Message, message);
    asn_fprint(stdout, &asn_DEF_Message, message);

    ASN_STRUCT_FREE(asn_DEF_Message, message);
    // ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_Message, &message);
    return 0;
}
