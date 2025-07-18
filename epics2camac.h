/*
 *      epics2camac.h
*/

#ifndef _EPICS2CAMAC_H
#define _EPICS2CAMAC_H
#include "CamacRequestFrame.h"
#include "PduType.h"

    /* These two types have no definition in any of 
    * the header files generated by asn1c.
    * Seems unclean... I wonder if there's a better way.
    */
    // typedef union CamacRequestFrame__requesttype_u {
    //     CamacCycleRequestR_t	 requestR;
    //     CamacCycleRequestW_t	 requestW;
    // } CamacRequestFrame__requesttype_u_t;

    // typedef struct requesttype {
    //     requesttype_PR              present;
    //     CamacRequestFrame__requesttype_u_t   choice;    
    //     asn_struct_ctx_t            _asn_ctx;
    // } requesttype_t;
typedef struct requesttype requesttype_t;
typedef union CamacRequestFrame__requesttype_u CamacRequestFrame__requesttype_u_t;

BasicCycleRequest_t  * buildCycle(  uint8_t g,
                                    uint8_t b, 
                                    uint8_t c, 
                                    uint8_t n, 
                                    uint8_t a, 
                                    uint8_t f 
                                 // requesttype_PR present, 
                                 //    uint32_t wdata 
                                    );

requesttype_t * buildRequest( BasicCycleRequest_t * basicCycle, requesttype_PR present, uint32_t wData  );


/* CamacRequestFrame
    typedef struct CamacRequestFrame {
    	A_SET_OF(
            struct requesttype {
    		    requesttype_PR present;
    		    union CamacRequestFrame__requesttype_u {
    		    	struct BasicCycleRequest	*requestR;
    			    struct CamacCycleRequestW	*requestW;
    		    } choice;
            
    		    // Context for parsing across buffer boundaries
    		    asn_struct_ctx_t _asn_ctx;
    	    } 
        ) list;
        
    	// Context for parsing across buffer boundaries
    	asn_struct_ctx_t _asn_ctx;
    } CamacRequestFrame_t;
*/

#endif
