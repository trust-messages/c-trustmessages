/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 */

#ifndef	_Rating_H_
#define	_Rating_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Entity.h"
#include "Service.h"
#include "BinaryTime.h"
#include <ANY.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Rating */
typedef struct Rating {
	Entity_t	 source;
	Entity_t	 target;
	Service_t	 service;
	BinaryTime_t	 date;
	ANY_t	 value;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Rating_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Rating;

#ifdef __cplusplus
}
#endif

#endif	/* _Rating_H_ */
#include <asn_internal.h>
