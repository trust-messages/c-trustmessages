#include <sys/time.h>
#include <stdio.h>
#include <utils.h>
#include <FormatRequest.h>
#include <FormatResponse.h>
#include <DataRequest.h>
#include <Fault.h>
#include <Message.h>
#include <QTM.h>
#include <SL.h>
#include <time.h>

int endswith(const char *string, const char *suffix)
{
    return strlen(string) > strlen(suffix) && !strcmp(string + strlen(string) - strlen(suffix), suffix);
}

long double duration(const struct timeval *start, const struct timeval *stop)
{
    return (long double)(stop->tv_usec - start->tv_usec) / 1000000 + (long double)(stop->tv_sec - start->tv_sec);
}

Measurement_t time_decode(
    asn_dec_rval_t (*decoder)(asn_codec_ctx_t *, asn_TYPE_descriptor_t *, void **, const void *, size_t),
    const char *buf,
    const size_t size,
    const size_t iterations)
{
    struct timeval start, stop;
    long double total = 0.0;

    for (uint64_t i = 0; i < iterations; i++)
    {
        void *message = 0;
        asn_dec_rval_t rval;
        gettimeofday(&start, NULL);
        rval = (*decoder)(0, &asn_DEF_Message, (void **)&message, buf, size);
        gettimeofday(&stop, NULL);
        assert(rval.code == RC_OK);
        total += duration(&start, &stop);
        ASN_STRUCT_FREE(asn_DEF_Message, message);
    }

    return (Measurement_t){total, total / iterations, size};
}

// NO-NOP function used for encoding messages and discarding them
static int no_op_consume_bytes(const void *buffer, size_t size, void *app_key)
{
    return 0;
}

Measurement_t time_encode_der(
    Message_t *message,
    const size_t iterations)
{
    struct timeval start, stop;
    long double total = 0.0;

    char buff[200];
    size_t errSize = sizeof(buff);
    size_t encodedSize;

    FILE *dev_null = fopen("/dev/null", "w");

    for (uint64_t i = 0; i < iterations; i++)
    {
        asn_enc_rval_t ec;
        gettimeofday(&start, NULL);
        // ec = der_encode(&asn_DEF_Message, message, write_out, dev_null);
        ec = der_encode(&asn_DEF_Message, message, NULL, NULL);
        gettimeofday(&stop, NULL);

        assert(ec.encoded != -1);
        assert(asn_check_constraints(&asn_DEF_Message, message, buff, &errSize) == 0);
        encodedSize = ec.encoded;

        total += duration(&start, &stop);
    }

    return (Measurement_t){total, total / iterations, encodedSize};
}

Measurement_t time_encode_xer(
    Message_t *message,
    const size_t iterations)
{
    struct timeval start, stop;
    long double total = 0.0;

    char buff[200];
    size_t errSize = sizeof(buff);
    size_t encodedSize;

    FILE *dev_null = fopen("/dev/null", "w");

    for (uint64_t i = 0; i < iterations; i++)
    {
        asn_enc_rval_t ec;
        gettimeofday(&start, NULL);
        // TODO: xer_encode() segfaults if function for consuming bytes is null.
        // Setting it to NO-OP function might add a bit of overhead
        // ec = xer_encode(&asn_DEF_Message, message, XER_F_BASIC, write_out, dev_null);
        ec = xer_encode(&asn_DEF_Message, message, XER_F_BASIC, no_op_consume_bytes, NULL);
        gettimeofday(&stop, NULL);

        assert(ec.encoded != -1);
        assert(asn_check_constraints(&asn_DEF_Message, message, buff, &errSize) == 0);
        encodedSize = ec.encoded;

        total += duration(&start, &stop);
    }

    return (Measurement_t){total, total / iterations, encodedSize};
}

Measurement_t time_encode_uper(
    Message_t *message,
    const size_t iterations)
{
    struct timeval start, stop;
    long double total = 0.0;

    char buff[200];
    size_t errSize = sizeof(buff);
    size_t encodedSize;

    FILE *dev_null = fopen("/dev/null", "w");

    for (uint64_t i = 0; i < iterations; i++)
    {
        asn_enc_rval_t ec;
        gettimeofday(&start, NULL);
        ec = uper_encode(&asn_DEF_Message, message, write_out, dev_null);
        gettimeofday(&stop, NULL);

        assert(ec.encoded != -1);
        assert(asn_check_constraints(&asn_DEF_Message, message, buff, &errSize) == 0);
        encodedSize = ec.encoded;

        total += duration(&start, &stop);
    }

    return (Measurement_t){total, total / iterations, encodedSize};
}

/* Write the encoded output into some FILE stream. */
int write_out(const void *buffer, size_t size, void *app_key)
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
    message->payload.choice.data_request.type = DataRequest__type_assessment;
    message->payload.choice.data_request.query.present = Query_PR_con;
    message->payload.choice.data_request.query.choice.con.operator= Constraint__operator_eq;
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
    message->payload.choice.data_request.query.choice.exp->operator= Expression__operator_or;

    // left operand
    message->payload.choice.data_request.query.choice.exp->left = calloc(1, sizeof(Query_t));
    message->payload.choice.data_request.query.choice.exp->left->present = Query_PR_con;
    message->payload.choice.data_request.query.choice.exp->left->choice.con.operator= Constraint__operator_eq;
    message->payload.choice.data_request.query.choice.exp->left->choice.con.value.present = Value_PR_date;
    message->payload.choice.data_request.query.choice.exp->left->choice.con.value.choice.date = 123;

    // right operand
    message->payload.choice.data_request.query.choice.exp->right = calloc(1, sizeof(Query_t));
    message->payload.choice.data_request.query.choice.exp->right->present = Query_PR_con;
    message->payload.choice.data_request.query.choice.exp->right->choice.con.operator= Constraint__operator_eq;
    message->payload.choice.data_request.query.choice.exp->right->choice.con.value.present = Value_PR_service;
    OCTET_STRING_fromString(&message->payload.choice.data_request.query.choice.exp->right->choice.con.value.choice.service, "My Service");
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

int buff_write(const void *buffer, size_t size, void *app_key);

void create_data_response(Message_t *message, Encoding encoding, const size_t num_elements)
{
    const int def_id[] = {1, 1, 1};
    const size_t def_len = sizeof(def_id) / sizeof(def_id[0]);

    message->version = 1;
    message->payload.present = Message__payload_PR_data_response;
    message->payload.choice.data_response.rid = 11;
    message->payload.choice.data_response.type = DataResponse__type_assessment;
    OBJECT_IDENTIFIER_set_arcs(&message->payload.choice.data_response.format, def_id, sizeof(def_id[0]), def_len);
    OCTET_STRING_fromString(&message->payload.choice.data_response.provider, "Some provider");

    // init PRG
    srand48(time(NULL));

    for (size_t i = 0; i < num_elements; i++)
    {
        for (size_t j = 0; j < num_elements; j++)
        {
            char source[10], target[10];
            sprintf(source, "agent-%03ld", i);
            sprintf(target, "agent-%03ld", j);

            Rating_t *r = calloc(1, sizeof(Rating_t));
            OCTET_STRING_fromString(&r->source, source);
            OCTET_STRING_fromString(&r->target, target);
            OCTET_STRING_fromString(&r->service, "seller");
            r->date = 10 * i + j;

            // QTM: 0A 01 04
            QTM_t v = (i * num_elements + j) % 5;
            /*SL_t *v = calloc(1, sizeof(SL_t));
            v->b = 0.3;
            v->d = 0.2;
            v->u = 0.4;*/

            switch (encoding)
            {
            case BER:
                der_encode(&asn_DEF_SL, &v, buff_write, &r->value);
                break;
            case XER:
                xer_encode(&asn_DEF_SL, &v, XER_F_BASIC, buff_write, &r->value);
                break;
            case UPER:
                uper_encode(&asn_DEF_SL, &v, buff_write, &r->value);
                break;
            default:
                perror("Invalid encoding. Allowed values are; BER, XER or UPER.\n");
                exit(1);
                break;
            }

            // ASN_STRUCT_FREE(asn_DEF_SL, v);
            ASN_SET_ADD(&message->payload.choice.data_response.response.list, r);
        }
    }
}

struct _callback_arg
{
    uint8_t *buffer;
    size_t offset;
    size_t size;
};

int buff_write(const void *buffer, size_t size, void *key)
{
    struct _callback_arg *arg = (struct _callback_arg *)key;

    if ((arg->offset + size) >= arg->size)
    {
        size_t nsize = (arg->size ? arg->size << 2 : 16) + size;
        void *p = REALLOC(arg->buffer, nsize);
        if (!p)
            return -1;
        arg->buffer = (uint8_t *)p;
        arg->size = nsize;
    }

    memcpy(arg->buffer + arg->offset, buffer, size);
    arg->offset += size;
    assert(arg->offset < arg->size);

    return 0;
}
