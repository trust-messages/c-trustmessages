#include <stdio.h>
#include <sys/types.h>
#include <FormatRequest.h>
#include <FormatResponse.h>
#include <DataRequest.h>
#include <Fault.h>
#include <Message.h>
#include <QTM.h>
#include <SL.h>
#include <stdlib.h>
#include <time.h>

/* Write the encoded output into some FILE stream. */
static int write_out(const void *buffer, size_t size, void *app_key)
{
    FILE *out_fp = app_key;
    size_t wrote = fwrite(buffer, 1, size, out_fp);
    return (wrote == size) ? 0 : -1;
}

void create_format_request(Message_t *message)
{
    message->version = 1;
    message->payload.present = Message__payload_PR_format_request;
    message->payload.choice.format_request = 73;
}

void create_data_request(Message_t *message)
{
    const char *service_name = "Hello Service";

    message->version = 1;
    message->payload.present = Message__payload_PR_data_request;
    message->payload.choice.data_request.rid = 10;
    message->payload.choice.data_request.type_rq = DataRequest__type_rq_assessment;
    message->payload.choice.data_request.query.present = Query_PR_con;
    message->payload.choice.data_request.query.choice.con.operator_c = Constraint__operator_c_eq;
    message->payload.choice.data_request.query.choice.con.value.present = Value_PR_service;
    OCTET_STRING_fromString(&message->payload.choice.data_request.query.choice.con.value.choice.service, service_name);
}

void create_data_request_exp(Message_t *message)
{
    message->version = 1;
    message->payload.present = Message__payload_PR_data_request;
    message->payload.choice.data_request.rid = 11;

    // expression
    message->payload.choice.data_request.query.present = Query_PR_exp;
    message->payload.choice.data_request.query.choice.exp = calloc(1, sizeof(Expression_t));
    message->payload.choice.data_request.query.choice.exp->operator_e = Expression__operator_e_or;

    // left operand
    message->payload.choice.data_request.query.choice.exp->left = calloc(1, sizeof(Query_t));
    message->payload.choice.data_request.query.choice.exp->left->present = Query_PR_con;
    message->payload.choice.data_request.query.choice.exp->left->choice.con.operator_c = Constraint__operator_c_eq;
    message->payload.choice.data_request.query.choice.exp->left->choice.con.value.present = Value_PR_date;
    message->payload.choice.data_request.query.choice.exp->left->choice.con.value.choice.date = 123;

    // right operand
    message->payload.choice.data_request.query.choice.exp->right = calloc(1, sizeof(Query_t));
    message->payload.choice.data_request.query.choice.exp->right->present = Query_PR_con;
    message->payload.choice.data_request.query.choice.exp->right->choice.con.operator_c = Constraint__operator_c_eq;
    message->payload.choice.data_request.query.choice.exp->right->choice.con.value.present = Value_PR_service;
    OCTET_STRING_fromString(&message->payload.choice.data_request.query.choice.exp->right->choice.con.value.choice.service, "My Service!");
}

void create_format_response(Message_t *message)
{
    const char *def_asn1 = "Here be ASN.1 type definitions";
    const int def_id[] = {1, 2, 3};
    const size_t def_len = sizeof(def_id) / sizeof(def_id[0]);

    message->version = 1;
    message->payload.present = Message__payload_PR_format_response;
    message->payload.choice.format_response.rid = 1;

    OBJECT_IDENTIFIER_set_arcs(
        &message->payload.choice.format_response.assessment_id,
        def_id, sizeof(def_id[0]), def_len);
    OCTET_STRING_fromString(&message->payload.choice.format_response.assessment_def, def_asn1);

    OBJECT_IDENTIFIER_set_arcs(
        &message->payload.choice.format_response.trust_id,
        def_id, sizeof(def_id[0]), def_len);
    OCTET_STRING_fromString(&message->payload.choice.format_response.trust_def, def_asn1);
}

void create_fault(Message_t *message)
{
    char *description = "We're out of beer, sorry.";

    message->version = 1;
    message->payload.present = Message__payload_PR_fault;
    message->payload.choice.fault.rid = 1;
    OCTET_STRING_fromString(&message->payload.choice.fault.message, description);
}

void create_data_response(Message_t *message)
{
    const int def_id[] = {1, 1, 1};
    const size_t def_len = sizeof(def_id) / sizeof(def_id[0]);

    message->version = 1;
    message->payload.present = Message__payload_PR_data_response;
    message->payload.choice.data_response.rid = 11;
    message->payload.choice.data_response.type_rs = DataResponse__type_rs_assessment;
    OBJECT_IDENTIFIER_set_arcs(&message->payload.choice.data_response.format, def_id, sizeof(def_id[0]), def_len);
    OCTET_STRING_fromString(&message->payload.choice.data_response.provider, "Some provider");

    // init PRG
    srand48(time(NULL));

    for (size_t i = 0; i < 2000; i++)
    {
        for (size_t j = 0; j < 2000; j++)
        {
            /*if (j == i)
            {
                continue;
            }*/

            char source[10], target[10];
            sprintf(source, "agent-%03ld", i);
            sprintf(target, "agent-%03ld", j);

            Rating_t *r = calloc(1, sizeof(Rating_t));
            OCTET_STRING_fromString(&r->source, source);
            OCTET_STRING_fromString(&r->target, target);
            OCTET_STRING_fromString(&r->service, "seller");
            r->date = 10 * i + j;

            // SL
            /* SL_t *v = calloc(1, sizeof(SL_t));
            v->b = drand48();
            v->d = (1.0 - v->b) * drand48();
            v->u = 1 - v->b - v->d;
            ANY_fromType(&r->value, &asn_DEF_SL, v);
            asn_fprint(stdout, &asn_DEF_SL, v);
            ASN_STRUCT_FREE(asn_DEF_SL, v);*/

            // QTM
            QTM_t v = QTM_neutral;
            ANY_fromType(&r->value, &asn_DEF_QTM, &v);
            ASN_SET_ADD(&message->payload.choice.data_response.response.list, r);
        }
    }
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
    // create_data_request(message);
    // create_data_request_exp(message);
    // create_format_response(message);
    // create_fault(message);
    create_data_response(message);

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
        // asn_enc_rval_t ec = xer_encode(&asn_DEF_Message, message, XER_F_BASIC, write_out, fp);
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
    // asn_fprint(stdout, &asn_DEF_Message, message);

    ASN_STRUCT_FREE(asn_DEF_Message, message);
    // ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_Message, &message);
    return 0;
}
