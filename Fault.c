/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names`
 */

#include "Fault.h"

static asn_TYPE_member_t asn_MBR_Fault_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Fault, rid),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"rid"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Fault, message),
		(ASN_TAG_CLASS_UNIVERSAL | (19 << 2)),
		0,
		&asn_DEF_PrintableString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"message"
		},
};
static const ber_tlv_tag_t asn_DEF_Fault_tags_1[] = {
	(ASN_TAG_CLASS_APPLICATION | (7 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_Fault_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 0 }, /* rid */
    { (ASN_TAG_CLASS_UNIVERSAL | (19 << 2)), 1, 0, 0 } /* message */
};
static asn_SEQUENCE_specifics_t asn_SPC_Fault_specs_1 = {
	sizeof(struct Fault),
	offsetof(struct Fault, _asn_ctx),
	asn_MAP_Fault_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_Fault = {
	"Fault",
	"Fault",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_Fault_tags_1,
	sizeof(asn_DEF_Fault_tags_1)
		/sizeof(asn_DEF_Fault_tags_1[0]) - 1, /* 1 */
	asn_DEF_Fault_tags_1,	/* Same as above */
	sizeof(asn_DEF_Fault_tags_1)
		/sizeof(asn_DEF_Fault_tags_1[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_Fault_1,
	2,	/* Elements count */
	&asn_SPC_Fault_specs_1	/* Additional specs */
};

