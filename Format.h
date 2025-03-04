/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names -gen-PER`
 */

#ifndef	_Format_H_
#define	_Format_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OBJECT_IDENTIFIER.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Format */
typedef OBJECT_IDENTIFIER_t	 Format_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Format;
asn_struct_free_f Format_free;
asn_struct_print_f Format_print;
asn_constr_check_f Format_constraint;
ber_type_decoder_f Format_decode_ber;
der_type_encoder_f Format_encode_der;
xer_type_decoder_f Format_decode_xer;
xer_type_encoder_f Format_encode_xer;
per_type_decoder_f Format_decode_uper;
per_type_encoder_f Format_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _Format_H_ */
#include <asn_internal.h>
