CC = gcc
CFLAGS = -I .
CFLAGS += -fPIC
CFLAGS += -D_DEFAULT_SOURCE

LDFLAGS = -L .

LIBASN1C = libasn1c.so

ASN1C_OBJS = asn_codecs_prim.o   \
	INTEGER.o   \
	BIT_STRING.o   \
	OCTET_STRING.o   \
	asn_SET_OF.o   \
	constraints.o   \
	constr_CHOICE.o   \
	constr_SEQUENCE.o   \
	constr_SET.o   \
	constr_SET_OF.o   \
	constr_TYPE.o   \
	ber_tlv_length.o   \
	ber_tlv_tag.o   \
	NativeEnumerated.o   \
	NativeInteger.o   \
	pdu_collection.o   \
	der_encoder.o   \
	ber_decoder.o   \
	per_decoder.o   \
	per_encoder.o   \
	per_opentype.o   \
	per_support.o   \
	xer_decoder.o   \
	xer_encoder.o   \
	xer_support.o

PRJ_OBJS = CamacCycleReplyR.o   \
	CamacCycleReplyW.o   \
	CamacCycleRequestR.o   \
	CamacCycleRequestW.o   \
	CamacReplyFrame.o   \
	CamacRequestFrame.o   \
	BasicCycleRequest.o
#	converter-sample.o

DECODER_OBJS = exampleASN1-Decoder.o exampleASN1-Encoder.o

DECODERS = exampleASN1-Decoder exampleASN1-Encoder

.PHONY : clean all

all : $(DECODERS)

exampleASN1-Decoder : exampleASN1-Decoder.o $(PRJ_OBJS) libasn1c.so
	gcc -o $@ $< $(LDFLAGS) $(PRJ_OBJS) -lasn1c
 
exampleASN1-Encoder : exampleASN1-Encoder.o $(PRJ_OBJS) libasn1c.so
	gcc -o $@ $< $(LDFLAGS) $(PRJ_OBJS) -lasn1c
 
 
libasn1c.so : $(ASN1C_OBJS) 
	gcc -shared -o $@ $^


.o:.c	
	gcc $(CFLAGS) $< -o $@

clean :
	rm $(ASN1C_OBJS) 
	rm $(DECODERS) 
	rm $(PRJ_OBJS) 
	rm libasn1c.so


