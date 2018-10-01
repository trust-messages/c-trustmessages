/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_Query_H_
#define	_Query_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Constraint.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Query_PR {
	Query_PR_NOTHING,	/* No components present */
	Query_PR_con,
	Query_PR_exp
} Query_PR;

/* Forward declarations */
struct Expression;

/* Query */
typedef struct Query {
	Query_PR present;
	union Query_u {
		Constraint_t	 con;
		struct Expression	*exp;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Query_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Query;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Expression.h"

#endif	/* _Query_H_ */
#include <asn_internal.h>
