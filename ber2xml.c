#include <stdio.h>
#include <sys/types.h>
#include <Query.h>
#include <Fault.h>
#include <Message.h>
#include <time.h>
#include <sys/time.h>
#include <utils.h>

int main(int ac, char **av)
{
    if (ac != 3)
    {
        fprintf(stderr, "Usage: %s file.ber file.xml\n", av[0]);
        exit(1);
    }
    const char *ber_file = av[1];
    const char *xml_file = av[2];

    /* Open input file as read-only binary */
    FILE *fp = fopen(ber_file, "rb");
    if (!fp)
    {
        perror(ber_file);
        exit(1);
    }

    // file size in bytes
    fseek(fp, 0, SEEK_END);
    const size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    printf("fsize: %ld bytes (%.2f MB)\n", fsize, (double)fsize / 1024.0 / 1024.0);

    struct timeval start, stop;

    char *buf = malloc(fsize * sizeof(char));
    gettimeofday(&start, NULL);
    size_t read = fread(buf, 1, fsize, fp);
    gettimeofday(&stop, NULL);
    fclose(fp);

    printf("Reading file: %Lf\n", duration(&start, &stop));

    if (read != fsize)
    {
        fprintf(stderr, "%s: Empty or broken\n", ber_file);
        exit(1);
    }

    // decode
    Message_t *message = 0; // Type to decode: remember 0!
    gettimeofday(&start, NULL);
    asn_dec_rval_t rval = ber_decode(0, &asn_DEF_Message, (void **)&message, buf, read);
    gettimeofday(&stop, NULL);
    printf("BER decoding: %Lf\n", duration(&start, &stop));

    if (rval.code != RC_OK)
    {
        fprintf(stderr, "%s: Broken encoding at byte %ld\n", ber_file, rval.consumed);
        exit(1);
    }

    // encode to XML
    FILE *xml_fp = fopen(xml_file, "wb");
    if (!xml_fp)
    {
        perror(xml_file);
        exit(1);
    }

    gettimeofday(&start, NULL);
    asn_enc_rval_t ec = xer_encode(&asn_DEF_Message, message, XER_F_BASIC, write_out, xml_fp);
    gettimeofday(&stop, NULL);
    printf("XML encoding: %Lf\n", duration(&start, &stop));
    printf("XML size: %.2f MB\n", (double)ec.encoded / 1024 / 1024);
    
    if (ec.encoded == -1)
    {
        fprintf(stderr, "Could not encode, error at %s\n",
                ec.failed_type ? ec.failed_type->name : "unknown");
        exit(1);
    }

    free(buf);
    ASN_STRUCT_FREE(asn_DEF_Message, message);
    return 0;
}