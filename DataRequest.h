/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names -gen-PER`
 */

#ifndef	_DataRequest_H_
#define	_DataRequest_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <NativeEnumerated.h>
#include "Query.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum DataRequest__type {
	DataRequest__type_trust	= 0,
	DataRequest__type_assessment	= 1
} e_DataRequest__type;

/* DataRequest */
typedef struct DataRequest {
	long	 rid;
	long	 type;
	Query_t	 query;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DataRequest_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_type_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_DataRequest;

#ifdef __cplusplus
}
#endif

#endif	/* _DataRequest_H_ */
#include <asn_internal.h>
