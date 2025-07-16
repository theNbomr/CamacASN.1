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

typedef struct requesttype requesttype_t;
typedef union CamacRequestFrame__requesttype_u CamacRequestFrame__requesttype_u_t;

static int write_out( const void *buffer, 
                          size_t size, 
                            void *app_key);

requesttype_t * buildCycleRequest( uint8_t e, 
                                   uint8_t b, 
                                   uint8_t c, 
                                   uint8_t n, 
                                   uint8_t a, 
                                   uint8_t f, 
                            requesttype_PR present, 
                                  uint32_t wdata );

int main( int argc, char * argv[] ){
    
const char *filename = argv[1];
FILE *fp;

CamacRequestFrame_t  * camacRequestFrame;  /* Type to encode */
CamacReplyFrame_t    * camacReplyFrame;  /* Type to encode */
CamacCycleRequestR_t * camacCycleRequestR;
CamacCycleRequestW_t * camacCycleRequestW;
BasicCycleRequest_t  * basicCycleRequestR;
BasicCycleRequest_t  * basicCycleRequestW;

asn_enc_rval_t      ec;                 /* Encoder return value */

/* The frame to be encoded can have multiple requests becasue 
     * the outermost element is a SET OF production.
     */
    requesttype_t * cycle0 = buildCycleRequest( 1, 1, 2, 3, 4, 5, requesttype_PR_requestR, 0xffffffff );
    requesttype_t * cycle1 = buildCycleRequest( 1, 1, 2, 3, 4, 5, requesttype_PR_requestW, 0xabcdef );

    /* The SET OF production in the ASN.1 spec results in the need to assign one r more
     * elements to the SET, using the asn1c runtime function asn_set_add()
     */
    camacRequestFrame = (CamacRequestFrame_t *)calloc( 1, sizeof( CamacRequestFrame_t ) );
    asn_set_add( camacRequestFrame, cycle0 );
    asn_set_add( camacRequestFrame, cycle1 );
        
    /* Encode the Rectangle type as BER (DER) 
    */
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
