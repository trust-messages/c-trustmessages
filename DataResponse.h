/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names -gen-PER`
 */

#ifndef	_DataResponse_H_
#define	_DataResponse_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include "Format.h"
#include <NativeEnumerated.h>
#include "Entity.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum DataResponse__type {
	DataResponse__type_trust	= 0,
	DataResponse__type_assessment	= 1
} e_DataResponse__type;

/* Forward declarations */
struct Rating;

/* DataResponse */
typedef struct DataResponse {
	long	 rid;
	Format_t	 format;
	long	 type;
	Entity_t	 provider;
	struct DataResponse__response {
		A_SEQUENCE_OF(struct Rating) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} response;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DataResponse_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_type_4;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_DataResponse;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Rating.h"

#endif	/* _DataResponse_H_ */
#include <asn_internal.h>
