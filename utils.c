#include <sys/time.h>
#include <stdio.h>
#include <utils.h>

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
        total += (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
        ASN_STRUCT_FREE(asn_DEF_Message, message);
    }

    return (Measurement_t){total, total / iterations};
}