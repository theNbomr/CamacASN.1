/* 
 *  Sample asn.1 encoder appliation from asn1c documentation:
 *      'Using the Open SOurce ASN.1 Compiler'
 *  Companion decoder utility fro the same document is here.
 *
 */

#include    <stdio.h>
#include    <sys/types.h>
#include    <CamacRequestFrame.h>
#include    <CamacReplyFrame.h>

int main( int argc, char * argv[] ){

/* Rectangle_t *rectangle;              /* Type to encode */
CamacRequestFrame_t * camacRequestFrame;  /* Type to encode */
CamacReplyFrame_t   * camacReplyFrame;  /* Type to encode */
asn_enc_rval_t      ec;                 /* Encoder return value */

    /* Allocate the CamacRequestFrame_t 
    */
    camacRequestFrame = (CamacRequestFrame_t *)calloc(1, sizeof(CamacRequestFrame_t)); /* not malloc! */
    if(!camacRequestFrame) {
        perror("calloc() failed");
        exit(1);
    }
        

    /* Initialize the Rectangle members 
    */
    // rectangle->height = 42; /* any random value */
    // rectangle->width = 23;  /* any random value */
    
    camacRequestFrame->choice.requestW->b = 1;
    camacRequestFrame->choice.requestW->c = 2;
    camacRequestFrame->choice.requestW->n = 3;
    camacRequestFrame->choice.requestW->a = 4;
    camacRequestFrame->choice.requestW->f = 5;
    camacRequestFrame->requestW.wdata = 0xabcdef;
    
    /* BER encode the data if filename is given 
    */
    if(argc < 2) {
        fprintf(stderr, "Specify filename for BER output\n");
    } 
    else {
        
        const char *filename = argv[1];
        FILE *fp = fopen(filename, "wb");
        
        /* for BER output 
        */
        if(!fp) {
            perror(filename);
            exit(1);
        }
    }
    
    
    /* Encode the Rectangle type as BER (DER) 
    */
    /* ec = der_encode(&asn_DEF_Rectangle, rectangle, write_out, fp); */
    ec = der_encode(&asn_DEF_CamacRequestFrame, camacRequestFrame, write_out, fp);
    fclose(fp);
    
    if(ec.encoded == -1) {
        fprintf(stderr, "Could not encode Rectangle (at %s)\n",
                            ec.failed_type ? ec.failed_type->name : "unknown");
        exit(1);
    } 
    else {
        fprintf(stderr, "Created %s with BER encoded CamacRequestFrame\n", filename);
    }
    
    /* Also print the constructed Rectangle XER encoded (XML) 
    */
    xer_fprint(stdout, &asn_DEF_CamacRequestFrame, camacRequestFrame );

    /* Encoding finished successfully 
    */
    return( 0 ); 
}


/* Write the encoded output into some FILE stream. 
*/
static int write_out( const void *buffer, 
                          size_t size, 
                            void *app_key) {

    FILE *out_fp = app_key;
    size_t wrote = fwrite(buffer, 1, size, out_fp);
    return (wrote == size) ? 0 : 1;
}

