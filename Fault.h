/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names -gen-PER`
 */

#ifndef	_Fault_H_
#define	_Fault_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <IA5String.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Fault */
typedef struct Fault {
	long	 rid;
	IA5String_t	 message;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Fault_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Fault;

#ifdef __cplusplus
}
#endif

#endif	/* _Fault_H_ */
#include <asn_internal.h>
