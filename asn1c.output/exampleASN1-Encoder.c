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

CamacRequestFrame_t * assembleCamacRequestW( int b, int c, int n, int a, int f, long, int wData );
CamacRequestFrame_t * assembleCamacRequestR( int b, int c, int n, int a, int f, long );


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

    camacCycleRequestR = assembleCamacRequestR( 1, 2, 3, 4, 5 );
    camacCycleRequestW = assembleCamacRequestW( 1, 2, 3, 4, 5+16, 0xabcdef );

    
    camacRequestFrame = calloc( 1, sizeof( CamacRequestFrame_t ) );



    /* Allocate the CamacRequestFrame_t 
    */
    camacRequestFrame = (CamacRequestFrame_t *)calloc(1, sizeof(CamacRequestFrame_t)); /* not malloc! */
    
    /* Allocate all of the nested sub-elements individually
     */ 
    basicCycleRequestR = (BasicCycleRequest_t *)calloc( 1, sizeof( BasicCycleRequest_t) );
    basicCycleRequestW = (BasicCycleRequest_t *)calloc( 1, sizeof( BasicCycleRequest_t) );
    camacCycleRequestW = (CamacCycleRequestW_t *)calloc( 1, sizeof( CamacCycleRequestW_t) );
    camacCycleRequestR = (CamacCycleRequestR_t *)calloc( 1, sizeof( CamacCycleRequestR_t) );
    camacRequestFrame = (CamacRequestFrame_t *)calloc( 1, sizeof( CamacRequestFrame_t ) );
    if( !camacRequestFrame  || 
        !camacCycleRequestR || 
        !camacCycleRequestW ||
        !basicCycleRequestR ||
        !camacRequestFrame  ||
        !basicCycleRequestW ){
        
        perror("calloc() failed");
        exit(1);
    }

    
    /* Build up the RequestFrame from its initialized component parts
     */
    basicCycleRequestR->id = 0x0;
    basicCycleRequestR->b  = 1;
    basicCycleRequestR->c  = 2;
    basicCycleRequestR->n  = 3;
    basicCycleRequestR->a  = 4;
    basicCycleRequestR->f  = 5;
    
    basicCycleRequestW->id = 0x80;
    basicCycleRequestW->b  = 1;
    basicCycleRequestW->c  = 2;
    basicCycleRequestW->n  = 3;
    basicCycleRequestW->a  = 4;
    basicCycleRequestW->f  = 5;

    camacCycleRequestR = basicCycleRequestR;  // types are equivalent
    
    camacCycleRequestW->requestW = *basicCycleRequestW;
    camacCycleRequestW->wdata = 0xabcdef;
    
    requesttype_t * cycle0 = (requesttype_t *)calloc( 1, sizeof( requesttype_t ) );
    requesttype_t * cycle1 = (requesttype_t *)calloc( 1, sizeof( requesttype_t ) );

    /* cycle0 is a CAMAC Read request */
    cycle0->present = requesttype_PR_requestR;
    cycle0->choice.requestR = *camacCycleRequestR;
    
    /* cycle1 is a CAMAC Read request */
    cycle1->present = requesttype_PR_requestW;
    cycle1->choice.requestW = *camacCycleRequestW;

    asn_set_add( camacRequestFrame, cycle0 );
    asn_set_add( camacRequestFrame, cycle1 );

    cycle0->choice.requestR.id++;
    asn_set_add( camacRequestFrame, cycle0 );

    cycle1->choice.requestW->id++;
    asn_set_add( camacRequestFrame, cycle1 );

    cycle0->choice.requestR->id++;
    asn_set_add( camacRequestFrame, cycle0 );
    
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

