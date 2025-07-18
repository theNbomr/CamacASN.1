/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EPICS2CAMAC"
 * 	found in "../epics2camac.asn1"
 * 	`asn1c -pdu=all`
 */

#include "CamacReplyFrame.h"

static asn_TYPE_member_t asn_MBR_replytype_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct replytype, choice.replyR),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CamacCycleReplyR,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"replyR"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct replytype, choice.replyW),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CamacCycleReplyW,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"replyW"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_replytype_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* replyR */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* replyW */
};
static asn_CHOICE_specifics_t asn_SPC_replytype_specs_3 = {
	sizeof(struct replytype),
	offsetof(struct replytype, _asn_ctx),
	offsetof(struct replytype, present),
	sizeof(((struct replytype *)0)->present),
	asn_MAP_replytype_tag2el_3,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_replytype_3 = {
	"replytype",
	"replytype",
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
	asn_MBR_replytype_3,
	2,	/* Elements count */
	&asn_SPC_replytype_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_CamacReplyFrame_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CamacReplyFrame, pduType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PduType,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"pduType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamacReplyFrame, replytype),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_replytype_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"replytype"
		},
};
static const ber_tlv_tag_t asn_DEF_CamacReplyFrame_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_CamacReplyFrame_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pduType */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* replytype */
};
static asn_SEQUENCE_specifics_t asn_SPC_CamacReplyFrame_specs_1 = {
	sizeof(struct CamacReplyFrame),
	offsetof(struct CamacReplyFrame, _asn_ctx),
	asn_MAP_CamacReplyFrame_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_CamacReplyFrame = {
	"CamacReplyFrame",
	"CamacReplyFrame",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_CamacReplyFrame_tags_1,
	sizeof(asn_DEF_CamacReplyFrame_tags_1)
		/sizeof(asn_DEF_CamacReplyFrame_tags_1[0]), /* 1 */
	asn_DEF_CamacReplyFrame_tags_1,	/* Same as above */
	sizeof(asn_DEF_CamacReplyFrame_tags_1)
		/sizeof(asn_DEF_CamacReplyFrame_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_CamacReplyFrame_1,
	2,	/* Elements count */
	&asn_SPC_CamacReplyFrame_specs_1	/* Additional specs */
};

