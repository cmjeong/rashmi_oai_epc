
/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source

     File:    rgac_rgrcb.c

     Sid:      rgac_rgrcb.c@@/main/2 - Sat Jul 30 02:21:00 2011

     Prg:     nsadar 
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_rgr.h"
#include "rgac_acc.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"
#include "rgac_rgr.x"        /* MAC error defines */


/* Added for sending TTI tick to RRM */
PRIVATE S16 rgAcUtlValidateTiming ARGS((
         U16      sfn));

/*
*
*       Fun:   NxLiRgrBndCfm
*       
*       Desc:  Call handler for Bind Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgrcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 NxLiRgrBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 NxLiRgrBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(NxLiRgrBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NxLiRgrBndCfm():\n"));

   pst->event = RGAC_RGR_EVTBNDCFM;
 
   rgAcRgrSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of NxLiRgrBndCfm */
/*
*
*       Fun:   NxLiRgrCfgCfm
*       
*       Desc:  Call handler for Config Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgrcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 NxLiRgrCfgCfm
(
Pst            *pst,
SuId           suId,
RgrCfgTransId  transId,
U8             status
)
#else
PUBLIC S16 NxLiRgrCfgCfm(pst, suId, transId, status)
Pst            *pst;
SuId           suId;
RgrCfgTransId  transId;
U8             status;
#endif
{
   TRC2(NxLiRgrCfgCfm);
   CMXTA_DBG_PARAM((_cmxtap, "NxLiRgrCfgCfm():\n"));

   pst->event = RGAC_RGR_EVTCFGCFM;
   rgAcRgrSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of NxLiRgrCfgCfm*/


/*  Added for sending TTI tick to RRM */
/*
*
*       Fun:   NxLiRgrTtiInd
*       
*       Desc:  Call handler for TTI indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgrcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 NxLiRgrTtiInd
(
Pst            *pst,
SuId           suId,
RgrTtiIndInfo  *ttiInd
)
#else
PUBLIC S16 NxLiRgrTtiInd(pst, suId, ttiInd)
Pst            *pst;
SuId           suId;
RgrTtiIndInfo  *ttiInd;
#endif
{
   S16   ret;
   Pst   expPst;
   ProcId   srcProcId;
   ProcId   dstProcId;

   TRC2(NxLiRgrTtiInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "NxLiRgrTtiInd():\n"));

   /* We shall add some rudimentary validation here itself */
   pst->event = RGAC_RGR_EVTTTIIND;
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaGetPst(&expPst, ENTRG, CMXTA_INST_ID + 1, ENTNX, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   expPst.event = RGAC_RGR_EVTTTIIND;

   /* In case of a mismatch we shall push the message into the expect queue
    * and hence would cause a test case failure - unexpected message
    * received.
    */
   if((ret = cmXtaValidatePst(pst, &expPst)) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "NxLiRgrTtiInd(): PST Mismatch Expected \
               RGR Event (%d) Received (%d)\n", RGAC_RGR_EVTTTIIND, pst->event));
      /* Push into the expect queue to force a failure */
      rgAcRgrSendMsg(pst, suId, 1, ttiInd);    
      RETVALUE(RFAILED);
   }
   if ((ret = rgAcUtlValidateTiming (ttiInd->sfn)) == CMXTA_ERR_NOMATCH)
   {
      CMXTA_DBG_FATAL((_cmxtap, "NxLiRgrTtiInd() Error : Timing mismatch:\n"));
      /* Push into the expect queue to force a failure */
      rgAcRgrSendMsg(pst, suId, 1, ttiInd);    
      RETVALUE(RFAILED);
   }

   /* Increment the current time for next SFN RGR */
   RGR_ADD_TO_CRNTTIME(rgAccCb.rgrCrntTime, rgAccCb.rgrCrntTime, 
         (rgAccCb.rrmTtiIndPrd));
   (Void) SPutSBuf(pst->region, pst->pool, (Data *) ttiInd, 
                   sizeof(RgrTtiIndInfo));

   RETVALUE(ROK);
} /* End of NxLiRgrTtiInd */

/* Added for SI Enhancement*/
#ifdef RGR_SI_SCH
/*
*
*       Fun:   NxLiRgrSiCfgCfm
*       
*       Desc:  Call handler for SI Config Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgrcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 NxLiRgrSiCfgCfm
(
Pst            *pst,
SuId           suId,
RgrCfgTransId  transId,
U8             status
)
#else
PUBLIC S16 NxLiRgrSiCfgCfm(pst, suId, transId, status)
Pst            *pst;
SuId           suId;
RgrCfgTransId  transId;
U8             status;
#endif
{
   TRC2(NxLiRgrSiCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NxLiRgrSiCfgCfm():\n"));

   pst->event = RGAC_RGR_EVTSICFGCFM;
 
   rgAcRgrSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of NxLiRgrSiCfgCfm*/


/*
*
*       Fun:   NxLiRgrWarningSiCfgCfm
*       
*       Desc:  Call handler for SI Config Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgrcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 NxLiRgrWarningSiCfgCfm
(
Pst            *pst,
SuId           suId,
RgrCfgTransId  transId,
U8             siId,
U8             status
)
#else
PUBLIC S16 NxLiRgrWarningSiCfgCfm(pst, suId, transId, siId, status)
Pst            *pst;
SuId           suId;
RgrCfgTransId  transId;
U8             siId;
U8             status;
#endif
{
   TRC2(NxLiRgrWarningSiCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NxLiRgrWarningSiCfgCfm():\n"));

   pst->event = RGAC_RGR_EVTSIWARNINGCFGCFM;
 
   rgAcRgrSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);

}
#endif/*RGR_SI_SCH*/

/*
*
*       Fun:   rgAcRgrSendMsg 
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  rgac_rgrcb.c
*
*/
#ifdef ANSI
PUBLIC S16 rgAcRgrSendMsg
(
Pst            *pst,
SpId           suId,
U8             reason,
Void           *ptr
)
#else
PUBLIC S16 rgAcRgrSendMsg(pst, suId, reason, ptr)
Pst            *pst;
SpId           suId;
U8             reason;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   RgAccMsgQElm *rgMsg;
   RgAcRgrInfo  *rgrInfo;
   S16 ret = ROK;
   /* Added for sending TTI tick to RRM */
   RgrTtiIndInfo  *ttiInd;

 
   TRC3(rgAcRgrSendMsg);
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = (CmXtaTCCb *)rgAcRgrTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped RGAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(ROK);
   }

   rgMsg = NULLP;
   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcRgrSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)rgMsg;
   qElm.msgFreeFun = rgAcUtlFreeRgrCb;
   rgrInfo = &(rgMsg->u.rgrInfo);

   /*** fill the suId in the Q element****/
   rgrInfo->suId = suId;

   switch (pst->event) 
   {
      case RGAC_RGR_EVTBNDCFM:
      {
         rgrInfo->status = reason; 
         break;
      }
      case RGAC_RGR_EVTCFGCFM:
      {
         rgrInfo->status = reason;
         break;
      }
      case RGAC_RGR_EVTTTIIND:
      ttiInd = (RgrTtiIndInfo*)ptr;
      rgrInfo->ttiInd = *ttiInd;
      break;

#ifdef RGR_SI_SCH
      case RGAC_RGR_EVTSICFGCFM:
      {
         rgrInfo->status = reason;
         break;
      }

       case RGAC_RGR_EVTSIWARNINGCFGCFM:
      {
         rgrInfo->status = reason;
         break;
      }
#endif
#ifdef RGR_CQI_REPT
      case RGAC_RGR_EVTSTAIND:
      {
         rgrInfo->staInd = *((RgrStaIndInfo*)ptr);
         break;
      }
#endif
      case RGAC_RGR_EVTRGRUESTAIND:
      {
         rgrInfo->ueStaInd = *((RgrUeStaIndInfo *)ptr);
      }
      break;
      /* LTE_ADV_FLAG_REMOVED_START */
     case RGAC_RGR_EVTLOADINFIND:
     {
        rgrInfo->loadInfInd = *((RgrLoadInfIndInfo*)ptr);
        break;
     }
     /* LTE_ADV_FLAG_REMOVED_END */
      default:
         ret = RFAILED;
   }/* end fo switch */

   if( ret == ROK)
   {
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
 
      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will RGAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(rgMsg, sizeof(RgAccMsgQElm));
   }
   RETVALUE(ret);
} /* end of rgAcRgrSendMsg() */


/*
*
*       Fun:   rgAcRgrTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  rgac_rgrcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  rgAcRgrTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  rgAcRgrTstCbFind ()
#endif
{
   TRC2(rgAcRgrTstCbFind);
 
   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif
 
   RETVALUE(NULLP);
} /* End of rgAcRgrTstCbFind */

/**
 * @brief XTA Function to free resources aquired by the interface messages
 * received from MAC to RRM Layer.
 *
 * @details
 *
 *     Function : rgAcUtlFreeRgrCb
 *     
 *     A pointer to this function is registered with each 
 *     Queue element that gets enqueued as part of its call
 *     handler functionality. After the interface primitive 
 *     validation is done by the validation handler, the queue
 *     element is flushed, this function gets invoked as part
 *     of this flushing. Based on type of primitive, the memory
 *     freeing takes place.
 *     
 *  @param[in]  *qElm 
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/

#ifdef ANSI
PUBLIC S16 rgAcUtlFreeRgrCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 rgAcUtlFreeRgrCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   RgAccMsgQElm *rgMsg;
   RgAcRgrInfo  *rgrInfo = NULLP; 
 
   TRC2(rgAcUtlFreeRgrCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "rgAcUtlFreeRgrCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   rgMsg = (RgAccMsgQElm *)qElm->data;
  
   if(rgMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   rgrInfo = &(rgMsg->u.rgrInfo);
   
   if (rgMsg != NULLP)
   {
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcUtlFreeRgrCb() */

 /** @brief This function validates the timing information coming from MAC to
  * PHY. Ideally it should be the same as current time + TFU_DELTA
  *
  * @details
  *
  *     Function: 
  *
  *         Processing steps:
  *         - 
  *
  *
  * @param  
  * @param 
  * @return 
  */
#ifdef ANSI
PRIVATE S16 rgAcUtlValidateTiming
(
 U16       sfn
 )
#else
PRIVATE S16 rgAcUtlValidateTiming (sfn)
 U16      sfn;
#endif
{
   TRC2(rgAcUtlValidateTiming);

   /* Validate SFN only */
   if (rgAccCb.rgrCrntTime.sfn != sfn)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Info : Timing SFN mismatch rcvd (%d) exp (%d) \n",
                  sfn, rgAccCb.rgrCrntTime.sfn), 3);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcUtlValidateTiming */ 

#ifdef RGR_CQI_REPT
/*
*
*       Fun:   NxLiRgrStaInd
*       
*       Desc:  Call handler for STA indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgrcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 NxLiRgrStaInd
(
Pst            *pst,
SuId           suId,
RgrStaIndInfo  *staInd
)
#else
PUBLIC S16 NxLiRgrStaInd(pst, suId, staInd)
Pst            *pst;
SuId           suId;
RgrStaIndInfo  *staInd;
#endif
{

   TRC2(NxLiRgrStaInd);

   CMXTA_DBG_PARAM((_cmxtap, "NxLiRgrStaInd():\n"));

   /* We shall add some rudimentary validation here itself */
   pst->event = RGAC_RGR_EVTSTAIND;

   rgAcRgrSendMsg(pst, suId, 0, staInd);

   (Void) SPutSBuf(pst->region,pst->pool, (Data *)staInd,
                   sizeof(RgrStaIndInfo));

   RETVALUE(ROK);
} /* End of NxLiRgrStaInd */
#endif /* End of RGR_CQI_REPT */

#ifdef ANSI
PUBLIC S16 NxLiRgrUeStaInd
(
Pst *pst, 
SuId suid,
RgrUeStaIndInfo  *ueStaInd
)
#else
PUBLIC S16 NxLiRgrUeStaInd(pst, suid, ueStaInd)
Pst  *pst;
SuId suid;
RgrUeStaIndInfo *ueStaInd;
#endif
{
   TRC2(NxLiRgrUeStaInd);
   CMXTA_DBG_PARAM((_cmxtap,"NxLiRgrStaInd ():\n"));
   pst->event = RGAC_RGR_EVTRGRUESTAIND;
   rgAcRgrSendMsg(pst, suid, 0, ueStaInd);

   (Void) SPutSBuf(pst->region,pst->pool, (Data *)ueStaInd,
         sizeof(RgrUeStaIndInfo));

   RETVALUE(ROK);

}

/* LTE_ADV_FLAG_REMOVED_START */
#ifdef ANSI
PUBLIC S16 NxLiRgrLoadInfInd
(
 Pst* pst,
 SuId suId,
 RgrLoadInfIndInfo  *loadInfInd
 )
#else
PUBLIC S16 NxLiRgrLoadInfInd(pst, suId, loadInfInd)
   Pst* pst;
   SuId suId;
   RgrLoadInfIndInfo *loadInfInd;
#endif
{
   /* TODO: Temprorarily added for compilation */
   TRC3(NxLiRgrLoadInfInd);

   CMXTA_DBG_PARAM((_cmxtap, "NxLiRgrLoadInfInd():\n"));

   /* We shall add some rudimentary validation here itself */
   pst->event = RGAC_RGR_EVTLOADINFIND;

   rgAcRgrSendMsg(pst, suId, 0, loadInfInd);

   (Void) SPutSBuf(pst->region,pst->pool, (Data *)loadInfInd,
                   sizeof(RgrLoadInfIndInfo));

   RETVALUE(ROK);
} /* End of NxLiRgrLoadInfInd */
/* LTE_ADV_FLAG_REMOVED_END */


/********************************************************************30**

         End of file:     rgac_rgrcb.c@@/main/2 - Sat Jul 30 02:21:00 2011

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
/main/1      ---     ns  1. Initial Release.
            rg001.201 sm 1. Added TTI indication towards RGR user.
            rg004.201 rnt 1. Modified for SI Enhancement
/main/2      ---        dvasisht          1. Updated for LTE MAC Release 3.1
$SID$        ---      rt    1. LTE MAC 4.1 release
*********************************************************************91*/
