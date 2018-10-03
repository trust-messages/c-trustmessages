#include <sys/time.h>
#include <Message.h>

typedef struct measurement
{
    long double total;
    long double average;
    size_t size;
} Measurement_t;

long double duration(const struct timeval *start, const struct timeval *stop);

Measurement_t time_decode(
    asn_dec_rval_t (*decoder)(asn_codec_ctx_t *, asn_TYPE_descriptor_t *, void **, const void *, size_t), const char *buf,
    const size_t size,
    const size_t iterations);

Measurement_t time_encode_der(
    Message_t *message,
    const size_t iterations);

Measurement_t time_encode_xer(
    Message_t *message,
    const size_t iterations);

int write_out(const void *buffer, size_t size, void *app_key);

void create_format_request(Message_t *message);

void create_data_request(Message_t *message);

void create_data_request_exp(Message_t *message);

void create_format_response(Message_t *message);

void create_fault(Message_t *message);

void create_data_response(Message_t *message, const size_t num_elements);