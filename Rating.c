/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "Messages"
 * 	found in "../asn1-trustmessages/messages.asn"
 * 	`asn1c -fcompound-names -gen-PER`
 */

#include "Rating.h"

static asn_TYPE_member_t asn_MBR_Rating_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Rating, source),
		(ASN_TAG_CLASS_UNIVERSAL | (22 << 2)),
		0,
		&asn_DEF_Entity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"source"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Rating, target),
		(ASN_TAG_CLASS_UNIVERSAL | (22 << 2)),
		0,
		&asn_DEF_Entity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"target"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Rating, service),
		(ASN_TAG_CLASS_UNIVERSAL | (22 << 2)),
		0,
		&asn_DEF_Service,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"service"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Rating, date),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_BinaryTime,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"date"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Rating, value),
		(ASN_TAG_CLASS_UNIVERSAL | (4 << 2)),
		0,
		&asn_DEF_OCTET_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"value"
		},
};
static const ber_tlv_tag_t asn_DEF_Rating_tags_1[] = {
	(ASN_TAG_CLASS_APPLICATION | (4 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_Rating_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 3, 0, 0 }, /* date */
    { (ASN_TAG_CLASS_UNIVERSAL | (4 << 2)), 4, 0, 0 }, /* value */
    { (ASN_TAG_CLASS_UNIVERSAL | (22 << 2)), 0, 0, 2 }, /* source */
    { (ASN_TAG_CLASS_UNIVERSAL | (22 << 2)), 1, -1, 1 }, /* target */
    { (ASN_TAG_CLASS_UNIVERSAL | (22 << 2)), 2, -2, 0 } /* service */
};
static asn_SEQUENCE_specifics_t asn_SPC_Rating_specs_1 = {
	sizeof(struct Rating),
	offsetof(struct Rating, _asn_ctx),
	asn_MAP_Rating_tag2el_1,
	5,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_Rating = {
	"Rating",
	"Rating",
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
	asn_DEF_Rating_tags_1,
	sizeof(asn_DEF_Rating_tags_1)
		/sizeof(asn_DEF_Rating_tags_1[0]) - 1, /* 1 */
	asn_DEF_Rating_tags_1,	/* Same as above */
	sizeof(asn_DEF_Rating_tags_1)
		/sizeof(asn_DEF_Rating_tags_1[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_Rating_1,
	5,	/* Elements count */
	&asn_SPC_Rating_specs_1	/* Additional specs */
};

