ASN_MODULE_SOURCES=	\
	Message.c	\
	FormatRequest.c	\
	FormatResponse.c	\
	DataRequest.c	\
	DataResponse.c	\
	Rating.c	\
	Query.c	\
	Constraint.c	\
	Expression.c	\
	Value.c	\
	Fault.c	\
	Format.c	\
	Entity.c	\
	Service.c	\
	BinaryTime.c	\
	QTM.c	\
	SL.c	\
	utils.c

ASN_MODULE_HEADERS=	\
	Message.h	\
	FormatRequest.h	\
	FormatResponse.h	\
	DataRequest.h	\
	DataResponse.h	\
	Rating.h	\
	Query.h	\
	Constraint.h	\
	Expression.h	\
	Value.h	\
	Fault.h	\
	Format.h	\
	Entity.h	\
	Service.h	\
	BinaryTime.h	\
	QTM.h	\
	SL.h	\
	utils.h

ASN_MODULE_HEADERS+=ANY.h
ASN_MODULE_SOURCES+=ANY.c
ASN_MODULE_HEADERS+=INTEGER.h
ASN_MODULE_HEADERS+=NativeEnumerated.h
ASN_MODULE_HEADERS+=IA5String.h
ASN_MODULE_SOURCES+=IA5String.c
ASN_MODULE_SOURCES+=INTEGER.c
ASN_MODULE_SOURCES+=NativeEnumerated.c
ASN_MODULE_HEADERS+=NativeInteger.h
ASN_MODULE_SOURCES+=NativeInteger.c
ASN_MODULE_HEADERS+=NativeReal.h
ASN_MODULE_SOURCES+=NativeReal.c
ASN_MODULE_HEADERS+=REAL.h
ASN_MODULE_HEADERS+=OBJECT_IDENTIFIER.h
ASN_MODULE_SOURCES+=OBJECT_IDENTIFIER.c
ASN_MODULE_SOURCES+=REAL.c
ASN_MODULE_HEADERS+=asn_SEQUENCE_OF.h
ASN_MODULE_SOURCES+=asn_SEQUENCE_OF.c
ASN_MODULE_HEADERS+=asn_SET_OF.h
ASN_MODULE_SOURCES+=asn_SET_OF.c
ASN_MODULE_HEADERS+=constr_CHOICE.h
ASN_MODULE_SOURCES+=constr_CHOICE.c
ASN_MODULE_HEADERS+=constr_SEQUENCE.h
ASN_MODULE_SOURCES+=constr_SEQUENCE.c
ASN_MODULE_HEADERS+=constr_SEQUENCE_OF.h
ASN_MODULE_SOURCES+=constr_SEQUENCE_OF.c
ASN_MODULE_HEADERS+=constr_SET_OF.h
ASN_MODULE_SOURCES+=constr_SET_OF.c
ASN_MODULE_HEADERS+=asn_application.h
ASN_MODULE_HEADERS+=asn_system.h
ASN_MODULE_HEADERS+=asn_codecs.h
ASN_MODULE_HEADERS+=asn_internal.h
ASN_MODULE_HEADERS+=OCTET_STRING.h
ASN_MODULE_SOURCES+=OCTET_STRING.c
ASN_MODULE_HEADERS+=BIT_STRING.h
ASN_MODULE_SOURCES+=BIT_STRING.c
ASN_MODULE_SOURCES+=asn_codecs_prim.c
ASN_MODULE_HEADERS+=asn_codecs_prim.h
ASN_MODULE_HEADERS+=ber_tlv_length.h
ASN_MODULE_SOURCES+=ber_tlv_length.c
ASN_MODULE_HEADERS+=ber_tlv_tag.h
ASN_MODULE_SOURCES+=ber_tlv_tag.c
ASN_MODULE_HEADERS+=ber_decoder.h
ASN_MODULE_SOURCES+=ber_decoder.c
ASN_MODULE_HEADERS+=der_encoder.h
ASN_MODULE_SOURCES+=der_encoder.c
ASN_MODULE_HEADERS+=constr_TYPE.h
ASN_MODULE_SOURCES+=constr_TYPE.c
ASN_MODULE_HEADERS+=constraints.h
ASN_MODULE_SOURCES+=constraints.c
ASN_MODULE_HEADERS+=xer_support.h
ASN_MODULE_SOURCES+=xer_support.c
ASN_MODULE_HEADERS+=xer_decoder.h
ASN_MODULE_SOURCES+=xer_decoder.c
ASN_MODULE_HEADERS+=xer_encoder.h
ASN_MODULE_SOURCES+=xer_encoder.c
ASN_MODULE_HEADERS+=per_support.h
ASN_MODULE_SOURCES+=per_support.c
ASN_MODULE_HEADERS+=per_decoder.h
ASN_MODULE_SOURCES+=per_decoder.c
ASN_MODULE_HEADERS+=per_encoder.h
ASN_MODULE_SOURCES+=per_encoder.c
ASN_MODULE_HEADERS+=per_opentype.h
ASN_MODULE_SOURCES+=per_opentype.c


lib_LTLIBRARIES=libsomething.la
libsomething_la_SOURCES=$(ASN_MODULE_SOURCES) $(ASN_MODULE_HEADERS)

# This file may be used as an input for make(3)
# Remove the lines below to convert it into a pure .am file
# TARGET = decoder
CFLAGS += -I.
CFLAGS += -Ofast
# CFLAGS += -g # debug
CFLAGS += -pg # profile
OBJS=${ASN_MODULE_SOURCES:.c=.o}

all: decode encode generate ber2xml time_decode time_encode

generate: ${OBJS} generate.c
	$(CC) $(CFLAGS) -o generate generate.c ${OBJS} $(LDFLAGS) $(LIBS) -lm

ber2xml: ${OBJS} ber2xml.c
	$(CC) $(CFLAGS) -o ber2xml ber2xml.c ${OBJS} $(LDFLAGS) $(LIBS) -lm

encode: ${OBJS} encode.c
	$(CC) $(CFLAGS) -o encode encode.c ${OBJS} $(LDFLAGS) $(LIBS) -lm

decode: ${OBJS} decode.c
	$(CC) $(CFLAGS) -o decode decode.c ${OBJS} $(LDFLAGS) $(LIBS) -lm

time_decode: ${OBJS} time_decode.c
	$(CC) $(CFLAGS) -o time_decode time_decode.c ${OBJS} $(LDFLAGS) $(LIBS) -lm

time_encode: ${OBJS} time_encode.c
	$(CC) $(CFLAGS) -o time_encode time_encode.c ${OBJS} $(LDFLAGS) $(LIBS) -lm

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f encode decode time_encode time_decode ber2xml generate
	rm -f $(OBJS)

regen: regenerate-from-asn1-source

regenerate-from-asn1-source:
	asn1c -fcompound-names -gen-PER ../asn1-trustmessages/messages.asn ../asn1-trustmessages/formats.asn

