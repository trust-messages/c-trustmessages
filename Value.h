/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names -gen-PER`
 */

#ifndef	_Value_H_
#define	_Value_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Entity.h"
#include "BinaryTime.h"
#include "Service.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Value_PR {
	Value_PR_NOTHING,	/* No components present */
	Value_PR_source,
	Value_PR_target,
	Value_PR_date,
	Value_PR_service
} Value_PR;

/* Value */
typedef struct Value {
	Value_PR present;
	union Value_u {
		Entity_t	 source;
		Entity_t	 target;
		BinaryTime_t	 date;
		Service_t	 service;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Value_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Value;

#ifdef __cplusplus
}
#endif

#endif	/* _Value_H_ */
#include <asn_internal.h>
