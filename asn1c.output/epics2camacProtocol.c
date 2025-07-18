/* 
 * Compose a CAMAC Cycle request PDU with
 * runtime-specified values.
*/


#include "epics2camac.h"

typedef struct requesttype requesttype_t;
typedef union CamacRequestFrame__requesttype_u CamacRequestFrame__requesttype_u_t;


static int  cycleId(){
static int  id;

    return( id++ % 0x100 );
}


/* Instantiate a request cycle with the specified pararameters
*/

BasicCycleRequest_t  * buildCycle(  uint8_t g, 
                                    uint8_t b, 
                                    uint8_t c, 
                                    uint8_t n, 
                                    uint8_t a, 
                                    uint8_t f 
                                 // requesttype_PR present, 
                                 //    uint32_t wdata 
                                    ){

BasicCycleRequest_t  * basicCycleRequest;

    basicCycleRequest = (BasicCycleRequest_t *)calloc( 1, sizeof( BasicCycleRequest_t) );
    if( !basicCycleRequest ){  perror("calloc() failed"); return( NULL ); }

    basicCycleRequest->id = cycleId();
    basicCycleRequest->g  = g;
    basicCycleRequest->b  = b;
    basicCycleRequest->c  = c;
    basicCycleRequest->n  = n;
    basicCycleRequest->a  = a;
    basicCycleRequest->f  = f;
    basicCycleRequest->pduType = PduType_basicCycle;
    // basicCycleRequest->present = present;

    return( basicCycleRequest );
}



requesttype_t * buildRequest( BasicCycleRequest_t * basicCycle, requesttype_PR present, uint32_t wData ){

requesttype_t * request;
CamacCycleRequestR_t * camacCycleRequestR;
CamacCycleRequestW_t * camacCycleRequestW;

    request = (requesttype_t *)calloc( 1, sizeof( requesttype_t ) );
    if( !request ){  
        perror("calloc() failed"); 
        // free( basicCycle );
        return( NULL ); 
    }
    
    switch( present ){
        case requesttype_PR_NOTHING : /* No components present */
            free( request );
            request = NULL;
            break;

        case requesttype_PR_requestR :
            /* Read requests are just the basic request; no data 
            */
            camacCycleRequestR = (CamacCycleRequestR_t *)calloc( 1, sizeof( CamacCycleRequestR_t) );
            if( !camacCycleRequestR ){  
                perror("calloc() failed");
                free( basicCycle );
                free( request );
                return( NULL ); 
            }
            camacCycleRequestR->pduType = PduType_requestR;

            // Arrrgggg....!  This prevents us from updating basicCylce asynchronously to for a new request...
            camacCycleRequestR->basicCycle = *basicCycle;  // types are equivalent
            free( basicCycle );  // Might as well; we've made a copy here

            /* Flesh out the CHOICE union
            */
            request->present = requesttype_PR_requestR;
            request->choice.requestR = *camacCycleRequestR;
            free(camacCycleRequestR );
            break;

        case requesttype_PR_requestW :
            /* Write requests add the Write-data elements
            */
            camacCycleRequestW = (CamacCycleRequestW_t *)calloc( 1, sizeof( CamacCycleRequestW_t) );
            if( !camacCycleRequestW ){  
                perror("calloc() failed");
                free( basicCycle );
                free( request );
                return( NULL ); 
            }

            camacCycleRequestW->pduType = PduType_requestW;
            camacCycleRequestW->requestW = *basicCycle;
            free( basicCycle );
            camacCycleRequestW->wdata = wData;

            /* Flesh out the CHOICE union
            */
            request->present = requesttype_PR_requestW;
            request->choice.requestW = *camacCycleRequestW;
            free(camacCycleRequestW );
            break;
    }
    return( request );
}
