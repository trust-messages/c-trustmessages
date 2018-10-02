#include <sys/time.h>
#include <Message.h>

typedef struct measurement
{
    long double total;
    long double average;
} Measurement_t;

long double duration(const struct timeval *start, const struct timeval *stop);

Measurement_t time_decode(
    asn_dec_rval_t (*decoder)(asn_codec_ctx_t *, asn_TYPE_descriptor_t *, void **, const void *, size_t), const char *buf,
    const size_t size,
    const size_t iterations);