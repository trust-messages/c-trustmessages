/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names -gen-PER`
 */

#include "FormatResponse.h"

static asn_TYPE_member_t asn_MBR_FormatResponse_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct FormatResponse, rid),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rid"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FormatResponse, assessment_id),
		(ASN_TAG_CLASS_UNIVERSAL | (6 << 2)),
		0,
		&asn_DEF_Format,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"assessment-id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FormatResponse, assessment_def),
		(ASN_TAG_CLASS_UNIVERSAL | (19 << 2)),
		0,
		&asn_DEF_PrintableString,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"assessment-def"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FormatResponse, trust_id),
		(ASN_TAG_CLASS_UNIVERSAL | (6 << 2)),
		0,
		&asn_DEF_Format,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"trust-id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FormatResponse, trust_def),
		(ASN_TAG_CLASS_UNIVERSAL | (19 << 2)),
		0,
		&asn_DEF_PrintableString,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"trust-def"
		},
};
static const ber_tlv_tag_t asn_DEF_FormatResponse_tags_1[] = {
	(ASN_TAG_CLASS_APPLICATION | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_FormatResponse_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 0 }, /* rid */
    { (ASN_TAG_CLASS_UNIVERSAL | (6 << 2)), 1, 0, 1 }, /* assessment-id */
    { (ASN_TAG_CLASS_UNIVERSAL | (6 << 2)), 3, -1, 0 }, /* trust-id */
    { (ASN_TAG_CLASS_UNIVERSAL | (19 << 2)), 2, 0, 1 }, /* assessment-def */
    { (ASN_TAG_CLASS_UNIVERSAL | (19 << 2)), 4, -1, 0 } /* trust-def */
};
static asn_SEQUENCE_specifics_t asn_SPC_FormatResponse_specs_1 = {
	sizeof(struct FormatResponse),
	offsetof(struct FormatResponse, _asn_ctx),
	asn_MAP_FormatResponse_tag2el_1,
	5,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_FormatResponse = {
	"FormatResponse",
	"FormatResponse",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_FormatResponse_tags_1,
	sizeof(asn_DEF_FormatResponse_tags_1)
		/sizeof(asn_DEF_FormatResponse_tags_1[0]) - 1, /* 1 */
	asn_DEF_FormatResponse_tags_1,	/* Same as above */
	sizeof(asn_DEF_FormatResponse_tags_1)
		/sizeof(asn_DEF_FormatResponse_tags_1[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_FormatResponse_1,
	5,	/* Elements count */
	&asn_SPC_FormatResponse_specs_1	/* Additional specs */
};

