


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     rgac_lrgcb.c 
  
     Sid:      rgac_lrgcb.c@@/main/3 - Sat Jul 30 02:20:55 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_lrgcb.c
@brief This file contains the definitions for XTA LRG interface call 
handler functions. These functions are called from function defined in
rgac_lrghdl.c
*/

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
#include "rgac_acc.h"        /* MAC error defines */
#include "rgac_lrg.h"        /* MAC error defines */
#include <stdlib.h>

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
#include "rgac_acc.x"        /* MAC error defines */
#include "rgac_lrg.x"        /* MAC error defines */



/**
 * @brief XTA Config Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgCfgCfm
 *     
 *     Enqueues the Config Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgCfgCfm 
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgCfgCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   TRC3(SmMiLrgCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgCfgCfm():\n"));

   pst->event = RGAC_LRG_EVTCFGCFM;
 
   rgAcLrgSendMsg(pst, cfm);    

   RETVALUE(ROK);
} /* End of SmMiLrgCfgCfm */

/**
 * @brief XTA Scheduler Config Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgSchCfgCfm
 *     
 *     Enqueues the Scheduler Config Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchCfgCfm 
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgSchCfgCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   TRC3(SmMiLrgSchCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgSchCfgCfm():\n"));

   pst->event = RGAC_LRG_EVTSCHCFGCFM;
 
   rgAcLrgSendMsg(pst, cfm);    

   RETVALUE(ROK);
} /* End of SmMiLrgSchCfgCfm */


/**
 * @brief XTA Control Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgCntrlCfm
 *     
 *     Enqueues the Control Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgCntrlCfm 
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgCntrlCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   TRC3(SmMiLrgCntrlCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgCntrlCfm():\n"));

   pst->event = RGAC_LRG_EVTCNTRLCFM;
 
   rgAcLrgSendMsg(pst, cfm);    

   RETVALUE(ROK);
} /* End of SmMiLrgCntrlCfm */

/**
 * @brief XTA Scheduler Control Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgSchCntrlCfm
 *     
 *     Enqueues the Scheduler Control Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchCntrlCfm 
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgSchCntrlCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   TRC3(SmMiLrgSchCntrlCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgSchCntrlCfm():\n"));

   pst->event = RGAC_LRG_EVTSCHCNTRLCFM;
 
   rgAcLrgSendMsg(pst, cfm);    

   RETVALUE(ROK);
} /* End of SmMiLrgSchCntrlCfm */


/**
 * @brief XTA Statistics Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgStsCfm
 *     
 *     Enqueues the Statistics Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgStsCfm 
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgStsCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   TRC3(SmMiLrgStsCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgStsCfm():\n"));

   pst->event = RGAC_LRG_EVTSTSCFM;
 
   rgAcLrgSendMsg(pst, cfm);    

   RETVALUE(ROK);
} /* End of SmMiLrgStsCfm */


/**
 * @brief XTA Status Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgStaCfm
 *     
 *     Enqueues the Status Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst  *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgStaCfm 
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 SmMiLrgStaCfm(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif
{
   TRC3(SmMiLrgStaCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgStaCfm():\n"));

   pst->event = RGAC_LRG_EVTSTACFM;
 
   rgAcLrgSendMsg(pst, cfm);    

   RETVALUE(ROK);
} /* End of SmMiLrgStaCfm */



/**
 * @brief XTA Trace Indication Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgTrcInd
 *     
 *     Enqueues the Trace Indication received from MAC to XTA queue. 
 *     
 *  @param[in] Pst  *pst 
 *  @param[in] RgMngmt  *trcInd 
 *  @param[in] Buffer   *mBuf 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgTrcInd 
(
Pst            *pst,
RgMngmt        *trcInd,
Buffer         *mBuf
)
#else
PUBLIC S16 SmMiLrgTrcInd(pst, trcInd, mBuf)
Pst            *pst;
RgMngmt        *trcInd;
Buffer         *mBuf;
#endif
{
   TRC3(SmMiLrgTrcInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgTrcInd():\n"));

   pst->event = RGAC_LRG_EVTTRCIND;

   if (mBuf != NULLP)
      CMXTA_FREEMBUF(mBuf);
 
   rgAcLrgSendMsg(pst, trcInd);    

   RETVALUE(ROK);
} /* End of SmMiLrgTrcInd */


/**
 * @brief XTA Status Indication Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgStaInd
 *     
 *     Enqueues the Status Indication received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *staInd 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgStaInd 
(
Pst            *pst,
RgMngmt        *staInd
)
#else
PUBLIC S16 SmMiLrgStaInd(pst, staInd)
Pst            *pst;
RgMngmt        *staInd;
#endif
{
   TRC3(SmMiLrgStaInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgStaInd():\n"));

   pst->event = RGAC_LRG_EVTSTAIND;
 
   rgAcLrgSendMsg(pst, staInd);    

   RETVALUE(ROK);
} /* End of SmMiLrgStaInd */


/**
 * @brief XTA Status Indication Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgStaInd
 *     
 *     Enqueues the Status Indication received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *staInd 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchStaInd 
(
Pst            *pst,
RgMngmt        *staInd
)
#else
PUBLIC S16 SmMiLrgSchStaInd(pst, staInd)
Pst            *pst;
RgMngmt        *staInd;
#endif
{
   TRC3(SmMiLrgStaInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgStaInd():\n"));

   pst->event = RGAC_LRG_EVTSCHSTAIND;
 
   rgAcLrgSendMsg(pst, staInd);    

   RETVALUE(ROK);
} /* End of SmMiLrgSchStaInd */
#ifdef LTE_L2_MEAS

/**
 * @brief XTA Function to enqueue a interface primitive to Test Engine Queue.
 *
 * @details
 *
 *     Function : rgAcLrgSchL2SendMsg
 *     
 *     Allocates a queue element data structure and fills in
 *     the appropriate primitive with additional information
 *     like free function pointer and enqueue it to the XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] LrgSchMeasCfmInfo  *cfm 
 *  @return  CMXTA_ERR_INT
 *  @return  CMXTA_ERR_NONE
 *  @return  CMXTA_ERR_RSRC
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 rgAcLrgSchL2SendMsg
(
Pst               *pst,
LrgSchMeasCfmInfo *cfm
)
#else
PUBLIC S16 rgAcLrgSchL2SendMsg(pst, cfm)
Pst            *pst;
LrgSchMeasCfmInfo *cfm;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   RgAccMsgQElm *rgMsg;
   S16 ret = CMXTA_ERR_NONE;
 
   TRC2(rgAcLrgSchL2SendMsg);
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = rgAcLrgTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped RGAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   rgMsg = NULLP;
   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcLrgSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)rgMsg;
   qElm.msgFreeFun = rgAcUtlFreeLrgCb;
   cmMemcpy((U8 *) &(rgMsg->u.l2MeasInfo), (U8 *)cfm, sizeof(LrgSchMeasCfmInfo));
/*   SPutSBuf(0, 0, (Data *)cfm, sizeof(RgMngmt)); */

   if( ret == CMXTA_ERR_NONE)
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
} /* end of rgAcLrgSchL2SendMsg() */

/**
 * @brief XTA L2 Measurement Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgSchL2MeasCfm
 *     
 *     Enqueues the Config Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2MeasCfm
(
Pst               *pst,
LrgSchMeasCfmInfo *schL2MeasCfm
)
#else
PUBLIC S16 SmMiLrgSchL2MeasCfm(pst, schL2MeasCfm)
Pst               *pst;
LrgSchMeasCfmInfo *schL2MeasCfm;
#endif
{
   TRC3(SmMiLrgSchL2MeasCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgSchL2MeasCfm():\n"));

   pst->event = RGAC_LRG_EVTL2MEASCFM;
 
   rgAcLrgSchL2SendMsg(pst, schL2MeasCfm);    

   RETVALUE(ROK);
} /* End of SmMiLrgSchL2MeasCfm */

/**
 * @brief XTA L2 Measurement Stop Confirm Handler for LRG interface. 
 *
 * @details
 *
 *     Function : SmMiLrgSchL2MeasStopCfm
 *     
 *     Enqueues the Meas Stop Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2MeasStopCfm
(
Pst               *pst,
LrgSchMeasCfmInfo *schL2MeasStopCfm
)
#else
PUBLIC S16 SmMiLrgSchL2MeasStopCfm(pst, schL2MeasCfm)
Pst               *pst;
LrgSchMeasCfmInfo *schL2MeasStopCfm;
#endif
{
   TRC3(SmMiLrgSchL2MeasStopCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrgSchL2MeasStopCfm():\n"));

   pst->event = EVTLRGSCHL2MEASSTOPCFM;
 
   rgAcLrgSchL2SendMsg(pst, schL2MeasStopCfm);    

   RETVALUE(ROK);
} /* End of SmMiLrgSchL2MeasStopCfm */

#endif

/**
 * @brief XTA Function to enqueue a interface primitive to Test Engine Queue.
 *
 * @details
 *
 *     Function : rgAcLrgSendMsg
 *     
 *     Allocates a queue element data structure and fills in
 *     the appropriate primitive with additional information
 *     like free function pointer and enqueue it to the XTA queue. 
 *     
 *  @param[in] Pst   *pst 
 *  @param[in] RgMngmt  *cfm 
 *  @return  CMXTA_ERR_INT
 *  @return  CMXTA_ERR_NONE
 *  @return  CMXTA_ERR_RSRC
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 rgAcLrgSendMsg
(
Pst            *pst,
RgMngmt        *cfm
)
#else
PUBLIC S16 rgAcLrgSendMsg(pst, cfm)
Pst            *pst;
RgMngmt        *cfm;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   RgAccMsgQElm *rgMsg;
   S16 ret = CMXTA_ERR_NONE;
 
   TRC2(rgAcLrgSendMsg);
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = rgAcLrgTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped RGAC_ENHANCE: may be Sts Ind etc...\n"));
      SPutSBuf(0, 0, (Data *)cfm, sizeof(RgMngmt));
      RETVALUE(CMXTA_ERR_INT);
   }

   rgMsg = NULLP;
   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcLrgSendMsg(): resource error\n"));
      SPutSBuf(0, 0, (Data *)cfm, sizeof(RgMngmt));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)rgMsg;
   qElm.msgFreeFun = rgAcUtlFreeLrgCb;
   cmMemcpy((U8 *) &(rgMsg->u.rgMngmt), (U8 *)cfm, sizeof(RgMngmt));
/*   SPutSBuf(0, 0, (Data *)cfm, sizeof(RgMngmt)); */

   if( ret == CMXTA_ERR_NONE)
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
} /* end of rgAcLrgSendMsg() */



/**
 * @brief XTA Function to test case association for a received message.
 *
 * @details
 *
 *     Function : rgAcLrgTstCbFind
 *     
 *     Whenever a message is received from MAC to Dummy-RLC, this 
 *     function is called to check if this is associated to a running 
 *     test case. If test case shut down is done, then any message
 *     received there after is discarded as a spurious message.
 *     
 *  @return  CmXtaTCCb*
 *      -# NULLP
 *      -# CmXtaTCCb*
 **/
#ifdef ANSI
PUBLIC CmXtaTCCb*  rgAcLrgTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  rgAcLrgTstCbFind ()
#endif
{
   TRC2(rgAcLrgTstCbFind);
 
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
} /* End of rgAcLrgTstCbFind */



/**
 * @brief XTA Function to free resources aquired by the interface messages
 * received from MAC to Dummy-Layer Manager
 *
 * @details
 *
 *     Function : rgAcUtlFreeLrgCb
 *     
 *     A pointer to this function is registered with each 
 *     Queue element that gets enqueued as part of its call
 *     handler functionality. After the interface primitive 
 *     validation is done by the validation handler, the queue
 *     element is flushed, this function gets invoked as part
 *     of this flushing. Based on type of primitive, the memory
 *     freeing takes place.
 *     
 *  @param[in] CmXtaMsgQElm  *qElm 
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlFreeLrgCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 rgAcUtlFreeLrgCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   RgAccMsgQElm *rgMsg;
 
   TRC2(rgAcUtlFreeLrgCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "rgAcUtlFreeLrgCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   rgMsg = (RgAccMsgQElm *)qElm->data;
  
   if(rgMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   if (rgMsg != NULLP)
   {
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcUtlFreeLrgCb() */



/**********************************************************************
 
         End of file:     rgac_lrgcb.c@@/main/3 - Sat Jul 30 02:20:55 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm                1. Initial Release.
/main/2      ---     sm                1. LTE MAC 2.1 release
           rg003.201 ns                1. Trace added for functions.
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$        ---     rt    1. LTE MAC 4.1 release
*********************************************************************91*/
