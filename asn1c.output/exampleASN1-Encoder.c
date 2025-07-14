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


static int write_out( const void *buffer, 
                          size_t size, 
                            void *app_key);


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
    
    /* How to build up the Set of Choices...  ?
     */

    // /* CamacRequestFrame */
    // typedef struct CamacRequestFrame {
    //     A_SET_OF(struct requesttype {
    //         requesttype_PR present;
    //         union CamacRequestFrame__requesttype_u {
    //             CamacCycleRequestR_t	 requestR;
    //             CamacCycleRequestW_t	 requestW;
    //         } choice;
    //
    //         /* Context for parsing across buffer boundaries */
    //         asn_struct_ctx_t _asn_ctx;
    //     } ) list;
    //
    //     /* Context for parsing across buffer boundaries */
    //     asn_struct_ctx_t _asn_ctx;
    // } CamacRequestFrame_t;
    
    // typedef enum requesttype_PR {
    //     requesttype_PR_NOTHING,	/* No components present */
    //     requesttype_PR_requestR,
    //     requesttype_PR_requestW
    // } requesttype_PR;
   
    typedef union CamacRequestFrame__requesttype_u {
        CamacCycleRequestR_t	 requestR;
        CamacCycleRequestW_t	 requestW;
    } CamacRequestFrame__requesttype_u_t;
     
    typedef struct requesttype {
        requesttype_PR              present;
        CamacRequestFrame__requesttype_u_t   choice;    
        asn_struct_ctx_t            _asn_ctx;
    } requesttype_t;
     
     
    requesttype_t * cycle0 = (requesttype_t *)calloc( 1, sizeof( requesttype_t ) );
    requesttype_t * cycle1 = (requesttype_t *)calloc( 1, sizeof( requesttype_t ) );

    cycle0->present = requesttype_PR_requestR;
    cycle0->choice.requestR = *camacCycleRequestR;
    
    cycle1->present = requesttype_PR_requestW;
    cycle0->choice.requestW = *camacCycleRequestW;

    asn_set_add( camacRequestFrame, cycle0 );
    asn_set_add( camacRequestFrame, cycle1 );
    
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

