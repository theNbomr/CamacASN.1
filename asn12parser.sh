#! /bin/bash -x
#
#   This is to automate the production of parsers for
#   all of the ASN.1 elements defined in a ASN.1 module file.
#   It compiles the basic source code output from the asn1c
#   compiler, and then creates specific parsers for each
#   of the types/elements that the asn1c compiler identifies
#   in the module.
#
#
#   Run this script *from the asn1c.output* directory
#   after any modification to the asn.1 module.
#
#----------------------------------------------------

if [ "asn1c.output" != "$(basename ${PWD} )" ]; then 
   echo "Run this from the asn1c.output directory"
   echo "Usage: ASN.1/asn1c/asn1c.output$ ../asn12parser.sh ../epics2camac.asn1" 
   exit
fi

#  Translate the specified ASN.1 module into 
#  the C source code resulting from the compilation
#
asn1c -pdu=all $1

for t in $(grep ::= ../epics2camac.asn1 | cut -d' ' -f1) ; do 
    echo -n ${t}' ==> '
    ls ${t}.h
    if [ -e ${t}.h ]; then
        gcc -DPDU=${t} -I. -o convert_${t} *.c
    fi
done


