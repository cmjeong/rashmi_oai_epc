
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_ex_ms.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:14 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/*cm_xta_ex_ms_c_001.main_2 Removed cm_xta_app.h for Psf-Diameter 1.1*/
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
/*cm_xta_ex_ms_c_001.main_2 Removed cm_xta_app.x for Psf-Diameter 1.1*/
/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaActvTsk
(
Pst            *pst,           /* pst structure */
Buffer         *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmXtaActvTsk(pst, mBuf)
Pst            *pst;           /* pst structure */
Buffer         *mBuf;           /* message buffer */
#endif
{
   CmXtaTCCb *tcCb;

   TRC2(cmXtaActvTsk)

   switch(pst->srcEnt)
   {
      case ENTTST:
         switch(pst->event)
         {
            case EVTSTTTSTINIT:
               (Void) SPutMsg(mBuf);
               cmXtaTAReq(CMXTA_ERR_NONE);
               break;

            case EVTSTTTSTSKIP:
               CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&tcCb, mBuf, 0, pst);

               (Void) SPutMsg(mBuf);

               /*-- Check if the message has arrived in a TC fashion, this
                 may happen if the test engine was sending a message and
                 the layer sent a message back in TC fashion, do not 
                 trigger the test engine now in that case, the test engine
                 will have a look at the queued message --*/
               if (tcCb->busy == FALSE)
                  cmXtaTCEngine(tcCb);
               else
               {
                  CMXTA_DBG_FATAL((_cmxtap, "cmXtaActvTsk(): Invalid busy state for TC\n"));
               }

               break;

            default:
               CMXTA_DBG_ERR((_cmxtap, "cmXtaActvTsk(): invalid event (%d)\n", pst->event));
               (Void) SPutMsg(mBuf);
               break;
         }
         break;

      default:
         CMXTA_DBG_ERR((_cmxtap, "cmXtaActvTsk(): invalid src entity (%d)\n", pst->srcEnt));
         (Void) SPutMsg(mBuf);
         break;
   }

   SExitTsk();

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaActvTsk */
/********************************************************************30**

         End of file:     cm_xta_ex_ms.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:14 2015

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
/main/2      ----     up  1. Main release
/main/3      ---  cm_xta_ex_ms_c_001.main_2 nh 1.Updated for Psf-Diameter 1.1
                             release Removed cm_xta_app.[hx]
*********************************************************************91*/
