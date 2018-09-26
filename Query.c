/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 */

#include "Query.h"

static asn_TYPE_member_t asn_MBR_Query_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Query, choice.con),
		(ASN_TAG_CLASS_APPLICATION | (5 << 2)),
		0,
		&asn_DEF_Constraint,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"con"
		},
	{ ATF_POINTER, 0, offsetof(struct Query, choice.exp),
		(ASN_TAG_CLASS_APPLICATION | (6 << 2)),
		0,
		&asn_DEF_Expression,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"exp"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_Query_tag2el_1[] = {
    { (ASN_TAG_CLASS_APPLICATION | (5 << 2)), 0, 0, 0 }, /* con */
    { (ASN_TAG_CLASS_APPLICATION | (6 << 2)), 1, 0, 0 } /* exp */
};
static asn_CHOICE_specifics_t asn_SPC_Query_specs_1 = {
	sizeof(struct Query),
	offsetof(struct Query, _asn_ctx),
	offsetof(struct Query, present),
	sizeof(((struct Query *)0)->present),
	asn_MAP_Query_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_Query = {
	"Query",
	"Query",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	0,	/* No PER visible constraints */
	asn_MBR_Query_1,
	2,	/* Elements count */
	&asn_SPC_Query_specs_1	/* Additional specs */
};

