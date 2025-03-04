/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names -gen-PER`
 */

#ifndef	_Entity_H_
#define	_Entity_H_


#include <asn_application.h>

/* Including external dependencies */
#include <IA5String.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Entity */
typedef IA5String_t	 Entity_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Entity;
asn_struct_free_f Entity_free;
asn_struct_print_f Entity_print;
asn_constr_check_f Entity_constraint;
ber_type_decoder_f Entity_decode_ber;
der_type_encoder_f Entity_encode_der;
xer_type_decoder_f Entity_decode_xer;
xer_type_encoder_f Entity_encode_xer;
per_type_decoder_f Entity_decode_uper;
per_type_encoder_f Entity_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _Entity_H_ */
#include <asn_internal.h>
