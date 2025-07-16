
#include "epics2camac.h"

static int  cycleId(){
static int  id = 0;

    return( ++id % 0x100 );
}


/* Instantiate a request cycle with the specified pararameters
*/

requesttype_t * buildCycleRequest( uint8_t e, 
                                   uint8_t b, 
                                   uint8_t c, 
                                   uint8_t n, 
                                   uint8_t a, 
                                   uint8_t f, 
                            requesttype_PR present, 
                                  uint32_t wdata ){

CamacCycleRequestR_t * camacCycleRequestR;
CamacCycleRequestW_t * camacCycleRequestW;
BasicCycleRequest_t  * basicCycleRequest;
requesttype_t * cycle;

    basicCycleRequest = (BasicCycleRequest_t *)calloc( 1, sizeof( BasicCycleRequest_t) );
    if( !basicCycleRequest ){  perror("calloc() failed"); return( NULL ); }

    basicCycleRequest->id = 0x0;
    basicCycleRequest->b  = b;
    basicCycleRequest->c  = c;
    basicCycleRequest->n  = n;
    basicCycleRequest->a  = a;
    basicCycleRequest->f  = f;

    cycle = (requesttype_t *)calloc( 1, sizeof( requesttype_t ) );
    if( !cycle ){  
        perror("calloc() failed"); 
        free( basicCycleRequest );
        return( NULL ); 
    }
    
    switch( present ){
        case requesttype_PR_NOTHING : /* No components present */
            free( cycle );
        break;

        case requesttype_PR_requestR :
            /* Read requests are just the basic request; no data 
            */
            camacCycleRequestR = (CamacCycleRequestR_t *)calloc( 1, sizeof( CamacCycleRequestR_t) );
            if( !camacCycleRequestR ){  
                perror("calloc() failed");
                free( basicCycleRequest );
                free( cycle );
                return( NULL ); 
            }

            camacCycleRequestR = basicCycleRequest;  // types are equivalent

            /* Flesh out the CHOICE union
            */
            cycle->present = requesttype_PR_requestR;
            cycle->choice.requestR = *camacCycleRequestR;
            break;

        case requesttype_PR_requestW :
            /* Write requests add the Write-data elements
            */
            camacCycleRequestW = (CamacCycleRequestW_t *)calloc( 1, sizeof( CamacCycleRequestW_t) );
            if( !camacCycleRequestW ){  
                perror("calloc() failed");
                free( basicCycleRequest );
                free( cycle );
                return( NULL ); 
            }

            camacCycleRequestW->requestW = *basicCycleRequest;
            camacCycleRequestW->wdata = wdata;

            /* Flesh out the CHOICE union
            */
            cycle->present = requesttype_PR_requestW;
            cycle->choice.requestW = *camacCycleRequestW;
            break;
    }
    return( cycle );
}

