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

#include    "epics2camac.h"

static int write_out( const void *buffer, 
                          size_t size, 
                            void *app_key);

int main( int argc, char * argv[] ){
    
const char *filename = argv[1];
FILE *fp;

CamacRequestFrame_t  * camacRequestFrame;  /* Type to encode */
CamacReplyFrame_t    * camacReplyFrame;  /* Type to encode */

BasicCycleRequest_t * basicCycleR;
BasicCycleRequest_t * basicCycleW;

requesttype_t        * requestR;
requesttype_t        * requestW;

CamacCycleRequestR_t * camacCycleRequestR;
CamacCycleRequestW_t * camacCycleRequestW;


asn_enc_rval_t      ec;                 /* Encoder return value */

    /* BER encode the data if filename is given 
    */
    if(argc < 2) {
        fprintf(stderr, "Specify filename for BER output\n");
    } 
    else {
        
        filename = argv[1];
        fp = fopen(filename, "wb");
        
        /* for BER output 
        */
        if(!fp) {
            perror(filename);
            exit(1);
        }
    }
    
    //                        g, b, c, n, a, f
    basicCycleR = buildCycle( 1, 1, 2, 3, 4, 5 );
    basicCycleW = buildCycle( 1, 1, 2, 3, 4, 22 );

    /* Use dummy wdata for read cycle requests */
    requestR = buildRequest( basicCycleR, requesttype_PR_requestR, 0xffffffff );
    requestW = buildRequest( basicCycleW, requesttype_PR_requestW, 0xabcdef );

    camacRequestFrame = (CamacRequestFrame_t *)calloc( 1, sizeof( CamacRequestFrame_t ) );
    if( !camacRequestFrame ){
        perror( "calloc( CamacRequestFrame_t ) failed" );
        exit(1);
    }

    /* Populate the request frame with 2 requests, already composed; one Read & one Write 
     */
    asn_set_add( &(camacRequestFrame->set_of), requestR );
    asn_set_add( &(camacRequestFrame->set_of), requestW );
    camacRequestFrame -> pduType = PduType_requestFrame;
    printf( "Ready to encode to BER\n" );
    
    
    /* Encode the Rectangle type as BER (DER) 
    */
    /* ec = der_encode(&asn_DEF_Rectangle, rectangle, write_out, fp); */
    ec = der_encode(&asn_DEF_CamacRequestFrame, camacRequestFrame, write_out, fp);
    
    if(ec.encoded == -1) {
        fprintf(stderr, "Could not encode epics2camac request (at %s)\n",
                            ec.failed_type ? ec.failed_type->name : "unknown");
        exit(1);
    } 
    else {
        fprintf(stderr, "Created %s with BER encoded CamacRequestFrame\n", filename);
    }
    
    /* Also print the constructed Rectangle XER encoded (XML) 
    */
    xer_fprint(stdout, &asn_DEF_CamacRequestFrame, camacRequestFrame );



    /* =======================================================================
     *      FIXME:  Figure out how to de-allocate all of the calloc()'d memory 
     * =======================================================================
     */
    // asn_set_del( camacRequestFrame, 1, 1);
    // asn_set_add( camacRequestFrame, requestW );

    // free( requestR );
    // free( requestW );
    ec = der_encode(&asn_DEF_CamacRequestFrame, camacRequestFrame, write_out, fp);
    
    if(ec.encoded == -1) {
        fprintf(stderr, "Could not encode CamacRequestFrame (at %s)\n",
                            ec.failed_type ? ec.failed_type->name : "unknown");
        exit(1);
    } 
    else {
        fprintf(stderr, "Created %s with BER encoded CamacRequestFrame\n", filename);
    }
    
    /* Also print the constructed Rectangle XER encoded (XML) 
    */
    xer_fprint(stdout, &asn_DEF_CamacRequestFrame, camacRequestFrame );


    fclose(fp);

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

