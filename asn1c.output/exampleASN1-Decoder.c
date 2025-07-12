/* 
 *  Sample asn.1 decoder application from asn1c documentation:
 *      'Using the Open SOurce ASN.1 Compiler'
 *  Companion encoder utility from the same document is here.
 *
 */

#include    <stdio.h>
#include    <sys/types.h>

/* Include type definitions for the ASN.1 object to be decoded
 */
/* #include    <Rectangle.h>          /* Rectangle ASN.1 type */
#include    <CamacRequestFrame.h>  /* CamacRequestFrame ASN.1 type */


int main(int argc, char * argv[] ) {

char buf[1024];         /* Temporary buffer */
asn_dec_rval_t rval;    /* Decoder return value */
CamacRequestFrame_t *camacRequestFrame = 0;     /* Type to decode. Note this = 0! */

FILE *fp;               /* Input file handler   */
size_t size;            /* Number of bytes read */
char *filename;         /* Input file name      */

    /* Require a single filename argument 
     */
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <file.ber>\n", argv[0]);
        exit(1);
    } 
    else {
        filename = argv[1];
    }
    
    /* Open input file as readି only binary 
     */
    fp = fopen(filename, "rb");
    if(!fp) {
        perror(filename);
        exit(1);
    }
    
    /* Read up to the buffer size 
     */
    size = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);
    if(!size) {
        fprintf(stderr, "%s: Empty or broken\n", filename);
        exit(1);
    }
    
    /* Decode the input buffer as CamacRequestFrame type 
     */
    rval = ber_decode(0, &asn_DEF_CamacRequestFrame, (void **)&camacRequestFrame, buf, size);
    if(rval.code != RC_OK) {
        fprintf(stderr, "%s: Broken CamacRequestFrame encoding at byte %ld\n", filename, (long)rval.consumed );
        exit(1);
    }
    
    /* Print the decoded CamacRequestFrame type as XML 
     */
    xer_fprint(stdout, &asn_DEF_CamacRequestFrame, camacRequestFrame);
    return 0;       /* Decoding finished successfully */
}
