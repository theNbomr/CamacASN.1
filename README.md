# EPICS to CAMAC protocol using *ASN.1* and the *asn1c* compiler tools.
This is to explore the use of *ASN.1* notsation and the *asn1c* implementation of *ASN.1* compiler and skeleton code generator.

### What has been accomplished so far?

* A working (?) ASN.1 notation protocol description for communications between a CAMAC Crate Controller 
and and EPICS IOC (or other arbitrary network host) has been developed.

* The ASN.1 protocol definition has been used to generate a collection of C language source code for implementing
 encoders and decoders of the protocol
 
* A reference application for one encoder and one decoder have been implemented.
	
* A Makfile that describes the nature of the build process and some organization 
of the source code collection has been created.

Of course, the usual example code doesn't touch the complex real-world cases. For that, I needed the help of 
AI, and a Reddit poster suggested Claude.IO. I did so, and the results were quite impressive; withut it I would 
not have known about the undocumented macros and functions for manipulting the C structures that implement the
ASN.1 SET, SEQUENCE, SET OF & SEQUENCE OF data structures. It also provided helpful information about the 
CHOICE structure. The source code samples provided by <Claude.io> have been folded into a C language source file,
although I never intended for itto be compiled.

### To-Do

* More thorough testing and fleshing the reference implementation into something more general-purpose.
* Integrating the asn1c compilation process into the Makefile workflow.
    * Probably this will require some scripting to handle the changing collection of source files that will be created when new ASN.1 syntax is introduced to the project.
* Create some protocol handlers for the use of CAMAC LAMS
* Create some protocol handlers for the use of Diagnostics modes and status monitors
* Create a testbed implementation that uses actual netowrk or other communications channels

#### An explanatory excerpt from the Makefile:

```make
#	Build recipes for ASN.1 encoders and decoders based on the
#	asn1c 'compiler' package. <https://github.com/vlm/asn1c>
#
#	This Makefile assumes that the asn1c package is installed 
#  	and has already be executed against the configuration file:
#  		* epics2camac.asn1
#
#	The strategy is to build a shared object libarary containing the
#	generic asn1c runtime support modules, and build the individual
#	application modules (also produced by the asn1c compiler) to 
#	link against the main module (hand written). This uses a 
#	subset of all available modules, and if a different PDU format
#	is developed or if there are additons to the PDU defined here,
#	then additional asn1c support modules will probably have to 
#	be added.
#	
#	RN - 2025-Jul-13 
# ================================================================
```
### References:
1. asn1c <https://github.com/vlm/asn1c>
2. claude.io  <https://claude.ai/share/9c96387d-d6af-4e0b-8b7b-73335263356c>
3. EPICS <https://epics-controls.org>
