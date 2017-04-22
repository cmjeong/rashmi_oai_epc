
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_intutl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:18 2015

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
/* cm_xta_intutl_c_001.main_5: Made the flag generaic for CM XTA */
/* cm_xta_intutl_c_001.main_6- Removed cm_xta_app.h for Psf-Diameter 1.1 */
#ifdef CM_XTA_PSF
#include "cm_pftha.h"
#endif  /* CM_XTA_PSF */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
/* cm_xta_intutl_c_001.main_6- Removed cm_xta_app.x for Psf-Diameter 1.1 */
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
PUBLIC S16 cmXtaIntPrcTimerExp
(
CmXtaTCCb *tcCb,
S16    event
)
#else
PUBLIC S16 cmXtaIntPrcTimerExp(tcCb, event)
CmXtaTCCb *tcCb;
S16    event;
#endif /* ANSI */
{
   CmXtaMsgQElm qElm;
   Pst pst;
   ProcId         srcProcId;
   ProcId         dstProcId;

   TRC3(cmXtaIntPrcTimerExp)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaIntPrcTimerExp(): event(%d)\n", event));

   switch (event)
   {
      case CMXTA_TMR_DELAY:
      {
         tcCb->delayTmr = TRUE;
         break;
      }

      case CMXTA_TMR_DELAY_TST:
      {
         tcCb->delayTestTmr = TRUE;
         break;
      }

      case CMXTA_TMR_DELAY_SHUTDOWN:
      {
         cmXtaTCReq(tcCb, CMXTA_ERR_NONE);
         RETVALUE(ROK);
         break;
      }

      case CMXTA_TMR_GUARD_EXP:
      {
         tcCb->guardTmr = TRUE;
         break;
      }

      case CMXTA_TMR_TIMEOUT:
      {
         CMXTA_ZERO(&qElm, sizeof(qElm));

         /* Moved cmXtaGetPst out of Multi Proc flag*/
         /*-- Get the Pst information here --*/
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;
         cmXtaGetPst(&pst, ENTTST, CMXTA_INST_ID, ENTTST, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
         pst.event = CMXTA_TMR_TIMEOUT;

         (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)&pst, sizeof(Pst));

         /*-- Test case already found, queue the message for the tcCb --*/
         /* Push it onto the message queue --*/
         (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
         break;
      }

      default:
         CMXTA_DBG_ERR((_cmxtap, "cmXtaProcTmr(): invalid tmrEvnt (%d)\n", event));
         break;
   } /* End of switch */

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/

   /*-- This should not happen in case of the timer, a preventive check
        and the comments though --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);
   else
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaIntPrcTimerExp(): Invalid busy state for TC\n"));
   }

   RETVALUE(ROK);
} /* end of cmXtaIntPrcTimerExp() */

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
PUBLIC Void cmXtaGetStatus
(
Void           *curStep,
CmStatus       *status
)
#else
PUBLIC Void cmXtaGetStatus(curStep, status)
Void           *curStep;
CmStatus       *status;
#endif
{

   /*-- Set Default values of return value and reason --*/
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   /*-- Update values --*/
   /*-- so003 fixed for 64 bits --*/
   cmXtaXmlGetVal(NULLP, curStep, CMXTA_ATTRIB_ENUM_U16, "status",  &status->status);
   cmXtaXmlGetVal(NULLP, curStep, CMXTA_ATTRIB_ENUM_U16, "reason", &status->reason);

   RETVOID;
}
/* cm_xta_intutl_c_001.main_5: Made the flag generaic for CM XTA */
#ifdef CM_XTA_PSF
/*
*
*       Fun:     Get psf state
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
PUBLIC Void cmXtaGetState
(
Void           *curStep,
State          *state
)
#else
PUBLIC Void cmXtaGetState(curStep, state)
Void           *curStep;
State          *state;
#endif
{

   /*-- Set Default values of return value and reason --*/
   *state = ACTIVE;

   /*-- Update values --*/
   cmXtaXmlGetVal(NULLP, curStep, CMXTA_ATTRIB_ENUM_U8, "state",  state);

   RETVOID;
}
#endif /* CM_XTA_PSF */
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
PUBLIC S16 cmXtaValidateStatus
(
CmStatus       *status,
CmStatus       *incStatus
)
#else
PUBLIC S16 cmXtaValidateStatus(status, incStatus)
CmStatus       *status;
CmStatus       *incStatus;
#endif
{
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaValidateStatus() : Status(%hd) reason(%hd) \n",
                     incStatus->status, incStatus->reason));

   if ((status->status != incStatus->status) ||
         (status->reason != incStatus->reason))
   {
      CMXTA_DBG_CALLIND((_cmxtap,
               "Received: [status '%hd' reason '%hd']\tExpected: [status '%hd' reason '%hd']\n",
               incStatus->status, incStatus->reason, status->status, status->reason), 2);

      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/* cm_xta_intutl_c_001.main_2 : To validate psf state */ 
/*
*
*       Fun:     To validate psf state
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
PUBLIC S16 cmXtaValidateState
(
State          *state,
State          *incState
)
#else
PUBLIC S16 cmXtaValidateState(state, incState)
State          *state;
State          *incState;
#endif
{
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaValidateState() : State(%hd) \n",
                     *incState));

   if (*state != *incState) 
   {
      CMXTA_DBG_CALLIND((_cmxtap,
               "Received: [state '%hd']\tExpected: [state '%hd']\n",
               *incState, *state), 2);

      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

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
PUBLIC S16 cmXtaValidatePst
(
Pst  *recvPst,
Pst  *expPst
)
#else
PUBLIC S16 cmXtaValidatePst(recvPst, expPst)
Pst  *recvPst;
Pst  *expPst;
#endif
{

   CMXTA_DBG_PARAM((_cmxtap,
      "cmXtaValidatePst() : Received: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\n",
                     recvPst->srcProcId, recvPst->srcEnt, recvPst->srcInst, 
                     recvPst->dstProcId, recvPst->dstEnt, recvPst->dstInst, 
                     recvPst->event));

   CMXTA_DBG_PARAM((_cmxtap, 
      "cmXtaValidatePst() : Expected: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\n",
                     expPst->srcProcId, expPst->srcEnt, expPst->srcInst, 
                     expPst->dstProcId, expPst->dstEnt, expPst->dstInst, 
                     expPst->event));

/*    RETVALUE(ROK);*/
    
   if (
         (recvPst->srcProcId != expPst->srcProcId)    ||
       (recvPst->dstProcId != expPst->dstProcId)    ||
       (recvPst->srcEnt    != expPst->srcEnt)       ||
       (recvPst->srcInst   != expPst->srcInst)      ||
       (recvPst->dstEnt    != expPst->dstEnt)       ||
       (recvPst->dstInst   != expPst->dstInst)      ||
       (recvPst->event     != expPst->event))
   {
      CMXTA_DBG_CALLIND((_cmxtap,
         "Received: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\tExpected: [src:%d.%hd.%hd dst:%d.%hd.%hd evt:%hd]\n",
         recvPst->srcProcId, recvPst->srcEnt, recvPst->srcInst, 
         recvPst->dstProcId, recvPst->dstEnt, recvPst->dstInst, recvPst->event,
         expPst->srcProcId, expPst->srcEnt, expPst->srcInst, 
         expPst->dstProcId, expPst->dstEnt, expPst->dstInst, expPst->event), 2);

      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/********************************************************************30**

         End of file:     cm_xta_intutl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:18 2015

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
/main/3      ---      cm_xta_intutl_c_001.main_2  sk  1. Support for multiple proc
                                       2. Added functions to get and validate psf state
/main/4      ---      rb  1. Updated for PDCP Software release 1.1
/main/5      ---      aj  1. Moved the cmXtaGetPst out of the MultiProc Flag 
/main/6      ---      cm_xta_intutl_c_001.main_5 pka 1. Made the flag as generic for CM XTA.
/main/7      ---- cm_xta_intutl_c_001.main_6 nh 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
