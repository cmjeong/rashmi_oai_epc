
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    contains the definition of the control blocks needed by 
               the common fault detection system. 

     File:   cm_xta_fm.x  

     Sid:      cm_xta_fm.x@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:15 2015

     Prg:     sm 

*********************************************************************21*/
#ifndef __CMXTA_FM_X__
#define __CMXTA_FM_X__

#ifdef __cplusplus
extern "C" {
#endif
#include "ss_err.h"        /* errors --*/
#include "ss_dep.h"        /* implementation-specific --*/
#include "ss_queue.h"      /* queues --*/
#include "ss_task.h"       /* tasking --*/
#include "ss_msg.h"        /* messaging --*/
#include "ss_mem.h"        /* memory management interface --*/
#include "ss_gen.h"        /* general --*/

#include "ss_dep.x"        /* implementation-specific --*/
#include "ss_queue.x"      /* queues --*/
#include "ss_task.x"       /* tasking --*/
#include "ss_timer.x"      /* timers --*/
#include "ss_strm.x"       /* STREAMS --*/
#include "ss_msg.x"        /* messaging --*/
#include "ss_mem.x"        /* memory management interface --*/
#include "ss_drvr.x"       /* driver tasks --*/
#include "ss_gen.x"


/*----------------------------------------------------------------------
             TA: TC, data structure
-----------------------------------------------------------------------*/


/*-- Control block for Fault manager --*/
typedef struct cmXtaFmCb
{
   U8       curNode;                /*-- current node that is being pinged --*/
   U8       retryCount;             /*-- Number of retries --*/
   CmTqCp   tqCp;  
   CmTqType tq[CMXTA_FM_TQ_SIZE];
   CmTimer  timers[CMXTA_FM_MAX_TIMERS];
}CmXtaFmCb; /*-- cmXtaFmCb --*/

EXTERN CmXtaFmCb cmXtaFmCb;

#ifdef __cplusplus
}
#endif
#endif /* __CMXTA_FM_X__ */
/********************************************************************30**

         End of file:     cm_xta_fm.x@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:15 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ----      aj      1. main release
*********************************************************************91*/
