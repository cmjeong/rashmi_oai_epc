


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     rgac_rguhdl.c 
  
     Sid:      rgac_rguhdl.c@@/main/3 - Sat Jul 30 02:21:04 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_rguhdl.c
@brief This file contains the definitions for XTA RGU interface handler 
functions.
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
#include "rg.h"            /* Product defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_acc.h"        /* MAC error defines */
#include "rgac_rgu.h"        /* MAC error defines */
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
#include "rgac_rgu.x"        /* MAC error defines */

PRIVATE Txt *rgAcStrtok ARGS((
         Txt *start,
         Txt delim,
         Txt **pp,
         Txt buf[]
         ));



/**
 * @brief XTA Bind Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguBndReq
 *     
 *     Issues a bindrequest from Dummy RLC to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRguBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;             /* service user SAP identifier */
   SpId          spId = 0;             /* service user SAP identifier */
   Inst          instId = 0;
   
   TRC2(rgAcHdlRguBndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   
   cmXtaGetPst(&pst, RGAC_RGU_USERENT, RGAC_RGU_USERINST, RGAC_RGU_PROVENT, instId,
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
   
   pst.event = RGAC_RGU_EVTBNDREQ;
   
 
   /* Send the request to the MAC --*/
   RGAC_RGU_BNDREQ(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlRguBndReq --*/



/**
 * @brief XTA Bind Confirm Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguBndCfm 
 *     
 *     Validates a Bind Confirm from MAC to Dummy RLC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRguBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   Status        status = CM_BND_OK;
   Inst          instId = 0;
 
   TRC2(rgAcHdlRguBndCfm);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRguBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGU_PROVENT, instId, RGAC_RGU_USERENT, RGAC_RGU_USERINST, 
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
   
   pst.event = RGAC_RGU_EVTBNDCFM;
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rguInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rguInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));
 
   if (status != rgMsg->u.rguInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, rgMsg->u.rguInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlRguBndCfm --*/
 
 

/**
 * @brief XTA UnBind Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguUbndReq 
 *     
 *     Issues an Un-Bind request from Dummy RLC to MAC. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/ 
#ifdef ANSI
PUBLIC S16 rgAcHdlRguUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRguUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   Reason         reason = 0;
   Inst           instId =0;

   TRC2(rgAcHdlRguUbndReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   cmXtaGetPst(&pst, RGAC_RGU_USERENT, RGAC_RGU_USERINST, RGAC_RGU_PROVENT, instId,
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
 
   pst.event = RGAC_RGU_EVTUBNDREQ;
 
 
   /* Send the request to the MAC --*/
   RGAC_RGU_UBNDREQ(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlRguUbndReq --*/



/**
 * @brief XTA Common Channel Data Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguCDatReq 
 *     
 *     Issues a Cdat request from Dummy RLC to MAC. This handler 
 *     Considers data that tester has provided and also the data
 *     that the test engine has cached from the previous status
 *     response and indication. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguCDatReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlRguCDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16             retVal;
   Pst             pst;
   SpId            spId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
   CmLteLcId       lcId = 0;
   CmLteLcType     lcType = 0;              /*!< Logical Channel Type */
   CmLteTimingInfo timingInfo;
   U8              ueId=0;
   U8              bcchIdx=0;
   U32             bufSize=0;
   U32             transId=0;
   Bool            sendNoMatter= FALSE;
   RguCDatReqInfo  *datReq=NULLP;
   Inst          instId = 0;

   TRC2(rgAcHdlRguCDatReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguCDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguCDatReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&timingInfo, sizeof(CmLteTimingInfo));
 
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL,
            (Data **)&datReq, sizeof(RguCDatReqInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(datReq, sizeof(RguCDatReqInfo));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGU_USERENT, RGAC_RGU_USERINST, RGAC_RGU_PROVENT, instId,
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
 
   pst.event = RGAC_RGU_EVTCDATREQ;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId", &(lcId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcType", &(lcType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "bufSize", &(bufSize));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bcchIdx", &(bcchIdx));
   if ((lcType == CM_LTE_LCH_BCCH) || (lcType == CM_LTE_LCH_PCCH))
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "frameNum",
      &(timingInfo.sfn));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subFrameNum",
      &(timingInfo.subframe));
   }
   else if (lcType == CM_LTE_LCH_CCCH)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", &(ueId));
   }
   else
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Invalid LcId(%d) for a Common \
      channel Data Request primitive\n", lcId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "sendNoMatter", &(sendNoMatter));
   retVal = rgAcUtlRguGenCDatReq(datReq,cellId,lcId, lcType, &timingInfo,
            rgAccCb.acUeCb[ueId].crnti,bufSize, transId, sendNoMatter, bcchIdx);
   if (retVal != ROK)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "rgAcUtlRguGenCDatReq() : failed\n"), 1);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /* Send the request to the MAC --*/
   RGAC_RGU_CDATREQ(&pst, spId, datReq);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlRguCDatReq --*/



/**
 * @brief XTA Dedicated Channel Data Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguDDatReq  
 *     
 *     Issues a Ddat request from Dummy RLC to MAC. This handler 
 *     Considers data that tester has provided and also the data
 *     that the test engine has cached from the previous status
 *     response and indication. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguDDatReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlRguDDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst             pst;
   SpId            spId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
   U8              ueId = 0;
   CmLteTimingInfo timingInfo;
   U32             transId = 0;
   U8              numLchTb1 = 1, numLchTb2 = 0;
   RguLchDatReq    lchData[RGAC_RGU_MAX];  
   RguDDatReqInfo  *datReq = NULLP;
   Txt             lchTb1DataStr[RGAC_RGU_TXTLEN], lchTb2DataStr[RGAC_RGU_TXTLEN];
   Txt             *holdMain,*tokMain,*tok1;
   Txt             *holdSub,*tokSub,*tok2;
   U16             tokCount=0,i=0;
   U8              sndLess = 0;
   U8              isMeasTypeDlTpt = 0;
#ifdef RGU_INF_OPTIMIZATION
   U8              dispatchDatReq = 0;
#endif
   U8              instId;

   TRC2(rgAcHdlRguDDatReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDDatReq(), tcId (%d)\n", tcCb->tcId));
#endif
   tok1 = NULLP; 
   tok2 = NULLP; 
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&timingInfo, sizeof(CmLteTimingInfo));
   CMXTA_ZERO(lchTb1DataStr, RGAC_RGU_TXTLEN);
   CMXTA_ZERO(lchData, RGAC_RGU_MAX*sizeof(RguLchDatReq));
 
   instId = RGAC_RGU_PROVINST;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGU_USERENT, RGAC_RGU_USERINST, RGAC_RGU_PROVENT, 
   instId, RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
 
   pst.event = RGAC_RGU_EVTDDATREQ;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLchTb1", &(numLchTb1));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLchTb2", &(numLchTb2));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchTb1Data", lchTb1DataStr);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchTb2Data", lchTb2DataStr);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sndLess", &sndLess);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isMeasTypeDlTpt", &isMeasTypeDlTpt);
#ifdef RGU_INF_OPTIMIZATION
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dispatchDatReq", &dispatchDatReq);
#endif

   if (numLchTb1 != 0)
   {
      tokCount = 0;
      for (holdMain = lchTb1DataStr;;holdMain=NULLP) {
         Txt buf1[100];
         tokMain = rgAcStrtok(holdMain,':',&tok1, buf1);
         if (tokMain == NULLP) break; 
         /* process each lcId data */
         for (holdSub = tokMain, i = 0; i < 8; i++, holdSub=NULLP)
         {
            Txt buf2[100];
            if ((tokSub=rgAcStrtok(holdSub,',',&tok2,buf2)) == NULLP)
               break;
            switch(i)
            {
               case 0:
                  lchData[tokCount].lcId = atoi(tokSub);   
                  break;
               case 1:
                  lchData[tokCount].boReport.bo = atoi(tokSub);  
                  break;
               case 2:
                  lchData[tokCount].pdu.numPdu = atoi(tokSub);  
                  break;
               case 3:
                  lchData[tokCount].boReport.oldestSduArrTime= SGetTtiCount() - atoi(tokSub);  
                  break;
#ifdef CCPU_OPT 
               case 4:
                  lchData[tokCount].boReport.estRlcHdrSz = atoi(tokSub);  
                  break;
               case 5:
                  if (cmStrcmp((U8 *)tokSub, (U8 *)"TRUE") == 0)
                     lchData[tokCount].boReport.staPduPrsnt = TRUE;  
                  else   
                     lchData[tokCount].boReport.staPduPrsnt = FALSE;  
                  break;
#endif                  
            }
         }
         tokCount++;
      }
      if (tokCount != numLchTb1)
      {
         CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRguDDatReq():Insufficient LC data\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   if (numLchTb2 != 0)
   {
      tokCount = 0;
      for (holdMain = lchTb2DataStr;;holdMain=NULLP) {
         Txt buf1[100];
         tokMain = rgAcStrtok(holdMain,':',&tok1, buf1);
         if (tokMain == NULLP) break; 
         /* process each lcId data */
         for (holdSub = tokMain, i = 0; i < 8; i++, holdSub=NULLP)
         {
            Txt buf2[100];
            if ((tokSub=rgAcStrtok(holdSub,',',&tok2,buf2)) == NULLP)
               break;
            switch(i)
            {
               case 0:
                  lchData[tokCount].lcId = atoi(tokSub);   
                  break;
               case 1:
                  lchData[tokCount].boReport.bo = atoi(tokSub);  
                  break;
               case 2:
                  lchData[tokCount].pdu.numPdu = atoi(tokSub);  
                  break;
               case 3:
                  lchData[tokCount].boReport.oldestSduArrTime = SGetTtiCount() - atoi(tokSub);  
                  break;
#ifdef CCPU_OPT 
               case 4:
                  lchData[tokCount].boReport.estRlcHdrSz = atoi(tokSub);  
                  break;
               case 5:
                  if (cmStrcmp((U8 *)tokSub, (U8 *)"TRUE") == 0)
                     lchData[tokCount].boReport.staPduPrsnt = TRUE;  
                  else   
                     lchData[tokCount].boReport.staPduPrsnt = FALSE;  
                  break;
#endif                  
            }
         }
         tokCount++;
      }
      if (tokCount != numLchTb2)
      {
         CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRguDDatReq():Insufficient LC data\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#ifndef RGU_INF_OPTIMIZATION
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL,
            (Data **)&datReq, sizeof(RguDDatReqInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   CMXTA_ZERO(datReq, sizeof(RguDDatReqInfo));
#else
   if(!(rgAccCb.datReq))
   {
      if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL,
               (Data **)&datReq, sizeof(RguDDatReqInfo)) != ROK)
      {
         RETVALUE(RFAILED);
      }
      CMXTA_ZERO(datReq, sizeof(RguDDatReqInfo));
      rgAccCb.datReq = datReq;
   }
   else
   {
      datReq = rgAccCb.datReq;
   }
#endif
#ifdef LTE_L2_MEAS
   if (rgAcUtlRguGenDDatReq(tcCb, spCb, datReq,cellId, ueId, rgAccCb.acUeCb[ueId].crnti,
            transId,numLchTb1, lchData, sndLess, isMeasTypeDlTpt)!=ROK)
#else
   if (rgAcUtlRguGenDDatReq(datReq,cellId, ueId, rgAccCb.acUeCb[ueId].crnti,
            transId,numLchTb1, lchData, sndLess)!=ROK)
#endif
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRguGenDDatReq() : failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /* Send the request to the MAC --*/
#ifndef RGU_INF_OPTIMIZATION
   RGAC_RGU_DDATREQ(&pst, spId, datReq);
#else
if((!(--(rgAccCb.nmbOfUeDatReqToBeSent))) || dispatchDatReq)
{
   datReq->nmbOfUeGrantPerTti = (datReq->nmbOfUeGrantPerTti - 
         rgAccCb.nmbOfUeDatReqToBeSent);
   /* Remove reference of DatReq present in rgAccCb*/
   rgAccCb.datReq = NULLP;
   RGAC_RGU_DDATREQ(&pst, spId, datReq);
}
#endif
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlRguDDatReq --*/



/**
 * @brief XTA Common Channel Status Response Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguCStaRsp  
 *     
 *     Issues a Cstatus response from Dummy-RLC to MAC.
 *     It also caches the required information, that would 
 *     be used to formulate/validate subsequent staInd/DatReq/
 *     DatInd primitives.
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguCStaRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlRguCStaRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst             pst;
   SpId            spId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
   CmLteLcId       lcId = 0;
   CmLteLcType     lcType = 0;              /*!< Logical Channel Type */
   U8              ueId = 0;
   RguCStaRspInfo  *staRsp = NULLP;
   CmLteTimingInfo timingInfo;
   S32             bo=-1;
   U8              sfOffset = 0;
   Inst          instId = 0;

   /* Cache required info in rgAcRguCb */
   RgAcRguCStaInfo *staInfo = NULLP;
   U16 count;

   TRC2(rgAcHdlRguCStaRsp);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguCStaRsp(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguCStaRsp(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&timingInfo, sizeof(CmLteTimingInfo));
 
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL,
            (Data **)&staRsp, sizeof(RguCStaRspInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGU_USERENT, RGAC_RGU_USERINST, RGAC_RGU_PROVENT, 
   instId, RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
 
   pst.event = RGAC_RGU_EVTCSTARSP;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId", &(lcId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcType", &(lcType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "bo", &(bo));

   staRsp->cellId = cellId;
   staRsp->lcId = lcId;
   staRsp->bo = bo;
   staRsp->lcType = lcType;

   if ((lcType == CM_LTE_LCH_BCCH) || (lcType == CM_LTE_LCH_PCCH))
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "frameNum",
      &(timingInfo.sfn));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subFrameNum",
      &(timingInfo.subframe));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sfOffset",
      &(sfOffset));
      if (sfOffset)
      {
         RGADDTOCRNTTIME(rgAcTfCb.crntTime, timingInfo, sfOffset);
      }
      
      cmMemcpy((U8 *)&staRsp->u.timeToTx, (U8 *)&timingInfo, 
      sizeof(CmLteTimingInfo));
   }
   else if (lcType == CM_LTE_LCH_CCCH)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", &(ueId));
      staRsp->u.rnti = rgAccCb.acUeCb[ueId].crnti;
   }
   
   for (count=0; count < rgAccCb.rgAcRguCb.nmbCSta; count++)
   {
      staInfo = &rgAccCb.rgAcRguCb.rguCStaInfo[count];
      if (staInfo->state == 2) /* 2-  datReq sent, then reuse this index */ 
      {
         staInfo->cellId = staRsp->cellId;
         staInfo->lcId = staRsp->lcId;
         staInfo->lcType = staRsp->lcType;
         staInfo->state = 0; /* staRsp filled */
         break;
      }
   }
   if (count ==  rgAccCb.rgAcRguCb.nmbCSta)
   {
      staInfo = &rgAccCb.rgAcRguCb.rguCStaInfo[count];
      staInfo->cellId = staRsp->cellId;
      staInfo->lcId = staRsp->lcId;
      staInfo->lcType = staRsp->lcType;
      staInfo->state = 0; /* staRsp filled */
      rgAccCb.rgAcRguCb.nmbCSta++;
   }
   if (staInfo != NULLP) /* irrelevant: just to avoid klockwork warning */
   {
      staInfo->bo = staRsp->bo;
      if ((staRsp->lcType == CM_LTE_LCH_BCCH) || (staRsp->lcType == CM_LTE_LCH_PCCH))
         staInfo->u.timeToTx = staRsp->u.timeToTx;
      else if (staRsp->lcType == CM_LTE_LCH_CCCH)
         staInfo->u.rnti = staRsp->u.rnti;
   }
   /* Send the request to the MAC --*/
   RGAC_RGU_CSTARSP(&pst, spId, staRsp);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlRguCStaRsp --*/



/**
 * @brief XTA Dedicated Channel Status Response Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguDStaRsp  
 *     
 *     Issues a Dstatus response from Dummy-RLC to MAC.
 *     It also caches the required information, that would 
 *     be used to formulate/validate subsequent staInd/DatReq/
 *     DatInd primitives.
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguDStaRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlRguDStaRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst             pst;
   SpId            spId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
   CmLteLcId       lcId = 0;
   U8              ueId = 0;
   RguDStaRspInfo  *staRsp = NULLP;
   CmLteTimingInfo timingInfo;
   S32             bo=-1;
   U32             oldestSduDelay = 0;
   U32             staPduBo = 0;
#ifdef CCPU_OPT 
   U16             estRlcHdrSz=0;
   Bool            staPduPrsnt=FALSE;
#endif                  
   Inst           instId = 0;


   TRC2(rgAcHdlRguDStaRsp);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDStaRsp(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDStaRsp(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&timingInfo, sizeof(CmLteTimingInfo));
 
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL,
           (Data **) &staRsp, sizeof(RguDStaRspInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGU_USERENT, RGAC_RGU_USERINST, RGAC_RGU_PROVENT, 
   instId, RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
 
   pst.event = RGAC_RGU_EVTDSTARSP;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId", &(lcId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "bo", &(bo));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "oldestSduDelay", &(oldestSduDelay));

   staRsp->cellId = cellId;
   /* Added the check for The lcId to be within the range */  
   if(lcId >10)
       RETVALUE(RFAILED); 
   staRsp->lcId = lcId;
   staRsp->rnti = rgAccCb.acUeCb[ueId].crnti;
   staRsp->boReport.bo = bo;
#ifdef LTE_ADV
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "staPduBo", &(staPduBo));
   staRsp->boReport.staPduBo = staPduBo;
#endif
	staRsp->boReport.oldestSduArrTime = SGetTtiCount() - oldestSduDelay;
#ifdef CCPU_OPT 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "estRlcHdrSz", &(estRlcHdrSz));
   staRsp->boReport.estRlcHdrSz = estRlcHdrSz;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "staPduPrsnt", &(staPduPrsnt));
   staRsp->boReport.staPduPrsnt = staPduPrsnt;
#endif                  
   
   rgAccCb.acUeCb[ueId].lcs[lcId].bo = bo;
   
   /* Send the request to the MAC --*/
   RGAC_RGU_DSTARSP(&pst, spId, staRsp);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlRguDStaRsp --*/



/**
 * @brief XTA Common Channel Data Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguCDatInd  
 *     
 *     Validates Data Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information.
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguCDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRguCDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   CmLteCellId   cellId = RG_ACC_CELLID;
   U8            ueId = 0;
   CmLteLcId     lcId = 0;
   Inst          instId = 0;
 
   TRC2(rgAcHdlRguCDatInd);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguCDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguCDatInd(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRguCDatInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGU_PROVENT, instId, RGAC_RGU_USERENT, RGAC_RGU_USERINST, 
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
   
   pst.event = RGAC_RGU_EVTCDATIND;
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rguInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rguInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
 
   if (cellId != rgMsg->u.rguInfo.u.rguCDatInd->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, rgMsg->u.rguInfo.u.rguCDatInd->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",  &(ueId));
 
   if (rgAccCb.acUeCb[ueId].crnti != rgMsg->u.rguInfo.u.rguCDatInd->rnti)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : rnti MisMatch: exp (%d) rcvd (%d) \n",
                  rgAccCb.acUeCb[ueId].crnti, rgMsg->u.rguInfo.u.rguCDatInd->rnti), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",  &(lcId));
 
   if (lcId != rgMsg->u.rguInfo.u.rguCDatInd->lcId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : LCID MisMatch: exp (%d) rcvd (%d) \n",
                  lcId, rgMsg->u.rguInfo.u.rguCDatInd->lcId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlRguCDatInd --*/



/**
 * @brief XTA Dedicated Channel Data Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguDDatInd  
 *     
 *     Validates Data Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information.
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguDDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRguDDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   CmLteCellId   cellId = RG_ACC_CELLID;
   U16           ueId = 0;
   CmLteLcId     lcId = 0;
   U8            numLch = 1;
   U8            numPdu = 0;
   Txt           lcInfoStr[RGAC_RGU_TXTLEN];
   Txt           *holdMain,*tok1,*holdSub,*tok2,*tokMain,*tokSub;
   U16           tokCount=0,i=0,j=0;
   RguDDatIndInfo     *rguDDatInd=NULLP;
   S16                dedBufIdx=-1;

   TRC2(rgAcHdlRguDDatInd);

   tok1 = NULLP;
   tok2 = NULLP;
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDDatInd(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRguDDatInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaGetPst(&pst, RGAC_RGU_PROVENT, RGAC_RGU_PROVINST, RGAC_RGU_USERENT, RGAC_RGU_USERINST, 
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
   
   pst.event = RGAC_RGU_EVTDDATIND;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "srcInst",  &(pst.srcInst));
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rguInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rguInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
 
   if (cellId != rgMsg->u.rguInfo.u.rguDDatInd->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, rgMsg->u.rguInfo.u.rguDDatInd->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));

   if (rgAccCb.acUeCb[ueId].crnti != rgMsg->u.rguInfo.u.rguDDatInd->rnti)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : rnti MisMatch: exp (%d) rcvd (%d) \n",
                  rgAccCb.acUeCb[ueId].crnti, rgMsg->u.rguInfo.u.rguDDatInd->rnti), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch",  &(numLch));
 
   if (numLch != rgMsg->u.rguInfo.u.rguDDatInd->numLch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed :numLch  MisMatch: exp (%d) rcvd (%d) \n",
                 numLch , rgMsg->u.rguInfo.u.rguDDatInd->numLch), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchTb1Data",  &(lcInfoStr));


   tokCount = 0;
   for (holdMain = lcInfoStr;;holdMain=NULLP) {
      Txt buf1[100];
      tokMain = rgAcStrtok(holdMain,':',&tok1,buf1);
      if (tokMain == NULLP) break;
      /* process each lcId data */
      for (holdSub = tokMain, i=0;i<3;holdSub=NULLP,i++)
      {
         Txt buf2[100];
         if ((tokSub=rgAcStrtok(holdSub,',',&tok2,buf2)) == NULLP)
            break;
         switch(i)
         {
            case 0:
               lcId = atoi(tokSub);   
               rguDDatInd = rgMsg->u.rguInfo.u.rguDDatInd;
               for (j=0; j<rguDDatInd->numLch; j++)
               {
                  if (lcId == rguDDatInd->lchData[j].lcId) break;
               }
               if (j == rguDDatInd->numLch)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "rgAcHdlRguDDatInd():LCID=%d \
                  not found in DDATIND\n", lcId),2);
                  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
                  RETVALUE(CMXTA_ERR_INT);
               }
               break;
            case 1:
               numPdu = atoi(tokSub);  
               if (numPdu != rguDDatInd->lchData[j].pdu.numPdu)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "rgAcHdlRguDDatInd():For LCID=%d \
                  numPdu=%d in DDATIND is not same\n", lcId, numPdu),2);
                  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
                  RETVALUE(CMXTA_ERR_INT);
               }
               break;
            case 2:
            /* as of now we are assuming only 1 pdu per LC */
               dedBufIdx = atoi(tokSub);  
               if ((dedBufIdx < 0) || (dedBufIdx >= RG_ACC_MAX_UE))
               {
                  CMXTA_DBG_ERR((_cmxtap, "rgAcUtlTfuValidateDatReq(): Invalid dedBufIdx\n"));
                  RETVALUE(CMXTA_ERR_NOMATCH);
               }
               if ((rgAcUtlTfuCompareBuf (rguDDatInd->lchData[j].pdu.mBuf[0],
                          rgAccCb.dedBuf[dedBufIdx])) != CMXTA_ERR_NONE)
               {
                  CMXTA_DBG_ERR((_cmxtap, "rgAcUtlTfuValidateDatReq(): Comparison for BCCH \
                  PCCH buffer failed \n"));
                  RETVALUE(CMXTA_ERR_NOMATCH);
               }
               break;
         }
      }
      
      tokCount++;
   }
   if (tokCount != numLch) goto error_inappropriate;

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);

error_inappropriate:   
   CMXTA_DBG_ERR((_cmxtap, "Failed : lchData provided is inappropriate \n"));
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_INT);
 
}/*-- rgAcHdlRguDDatInd --*/



/**
 * @brief XTA Common Channel Status Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguCStaInd  
 *     
 *     Validates CStatus Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information. It also caches the required information to
 *     used in sub-sequent DatReq/DatInd primitives. 
 *     
 *  @param[in] CmXtaTCCb *tcCb 
 *  @param[in] CmXtaSpCb *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguCStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRguCStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   CmLteCellId   cellId = RG_ACC_CELLID;
   CmLteLcId     lcId = 0;
   RgAcRguCStaInfo *staInfo;
   U8             saveTransId = 0;
   U16 count;
   Inst          instId = 0;
 
   TRC2(rgAcHdlRguCStaInd);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguCStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguCStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRguCStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGU_PROVENT, instId, RGAC_RGU_USERENT, RGAC_RGU_USERINST, 
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
   
   pst.event = RGAC_RGU_EVTCSTAIND;
   
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rguInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rguInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
 
   if (cellId != rgMsg->u.rguInfo.u.rguCStaInd->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, rgMsg->u.rguInfo.u.rguCStaInd->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",  &(lcId));
 
   if (lcId != rgMsg->u.rguInfo.u.rguCStaInd->lcId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : LCID MisMatch: exp (%d) rcvd (%d) \n",
                  lcId, rgMsg->u.rguInfo.u.rguCStaInd->lcId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   /* cache transId in staInfo */

   for (count=0; count < rgAccCb.rgAcRguCb.nmbCSta; count++)
   {
      staInfo = &rgAccCb.rgAcRguCb.rguCStaInfo[count];
      if ((staInfo->cellId == rgMsg->u.rguInfo.u.rguCStaInd->cellId) && 
         (staInfo->lcId == rgMsg->u.rguInfo.u.rguCStaInd->lcId) && 
         (staInfo->state == 0))
      {
         staInfo->transId = rgMsg->u.rguInfo.u.rguCStaInd->transId;
         staInfo->state=1; /* staInd stored */
         break;
      }
   }
   if (count ==  rgAccCb.rgAcRguCb.nmbCSta)
   {
      CMXTA_DBG_ERR((_cmxtap, "Failed : StaInd Recieved with out a StaRsp. \n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* The following code is added to store the transid given by mac, this would
    * be later validated at PHY */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTransId",  &(saveTransId));
   if (saveTransId != 0)
   {
      rgAccCb.transId[saveTransId] = rgMsg->u.rguInfo.u.rguCStaInd->transId;
   }
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlRguCStaInd --*/



#ifndef RGU_INF_OPTIMIZATION
/**
 * @brief XTA Dedicated Channel Status Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguDStaInd  
 *     
 *     Validates DStatus Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information. It also caches the required information to
 *     used in sub-sequent DatReq/DatInd primitives. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguDStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRguDStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm    *msg = NULLP;
   RgAccMsgQElm    *rgMsg = NULLP;
   Pst             pst;
   SpId            suId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
   U8              ueId = 0;
   CmLteLcId       lcId = 0;
   U8             numLchTb1=1, numLchTb2=0;
   U16             j=0;
   RguDStaIndInfo  *rguDStaInd= NULLP;
   U8             saveTransId = 0;
   RgAcUeCb        *ueCb=NULLP;
   CmLList         *node;
   S16             totBufSize;
   U8              lcIds[10];
   U8              numLcs = 0;
   Inst            instId = 0;
 
   TRC2(rgAcHdlRguDStaInd);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRguDStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

   cmXtaGetPst(&pst, RGAC_RGU_PROVENT, instId, RGAC_RGU_USERENT, RGAC_RGU_USERINST, 
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
   
   pst.event = RGAC_RGU_EVTDSTAIND;
   
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",  &(ueId));
   if (rgAccCb.acUeCb[ueId].crnti != rgMsg->u.rguInfo.u.rguDStaInd->rnti)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : RNTI MisMatch: exp (%d) rcvd (%d) \n",
                  rgAccCb.acUeCb[ueId].crnti, rgMsg->u.rguInfo.u.rguDStaInd->rnti), 2);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rguInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rguInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
 
   if (cellId != rgMsg->u.rguInfo.u.rguDStaInd->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, rgMsg->u.rguInfo.u.rguDStaInd->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLchTb1",  &(numLchTb1));
 
   if (numLchTb1 != rgMsg->u.rguInfo.u.rguDStaInd->staIndTb[0].nmbLch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : numLchTb1 MisMatch: exp (%d) rcvd (%d) \n",
                  numLchTb1 , rgMsg->u.rguInfo.u.rguDStaInd->staIndTb[0].nmbLch), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLchTb2",  &(numLchTb2));
 
   if (rgMsg->u.rguInfo.u.rguDStaInd->nmbOfTbs == 1)
   {
      rgMsg->u.rguInfo.u.rguDStaInd->staIndTb[1].nmbLch = 0;
   }

   if (numLchTb2 != rgMsg->u.rguInfo.u.rguDStaInd->staIndTb[1].nmbLch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : numLchTb2 MisMatch: exp (%d) rcvd (%d) \n",
                  numLchTb2, rgMsg->u.rguInfo.u.rguDStaInd->staIndTb[1].nmbLch), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
   "lchTb1Data",  lcIds, &numLcs);
   if (numLcs != numLchTb1)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : numLchTb1 and lchTb1Data MisMatch"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Perform validation to make sure that MAC must have allocated   */
   /* resources only if we had BO. BO is updated when we send StaRsp */
   
   rguDStaInd = rgMsg->u.rguInfo.u.rguDStaInd;
   for (j=0; j<rguDStaInd->staIndTb[0].nmbLch; j++)
   {
      U32 i=0;
      ueCb = &rgAccCb.acUeCb[ueId];
      lcId = rguDStaInd->staIndTb[0].lchStaInd[j].lcId;
      for (; i<numLcs; i++)
      {
         if (lcId == lcIds[i]) break;
      }
      if (i == numLcs) goto error_incorrect;
      /*if (ueCb->lcs[lcId].done == TRUE)
      {
         continue;
      }*/
      totBufSize = rguDStaInd->staIndTb[0].lchStaInd[j].totBufSize;
      /*for (i=0; i<rguDStaInd->staIndTb[0].nmbLch; i++)
      {
         if ((lcId == rguDStaInd->staIndTb[0].lchStaInd[i].lcId) && (j != i))
         {
            totBufSize += rguDStaInd->staIndTb[0].lchStaInd[i].totBufSize;
         }
      }*/
      if (ueCb->lcs[lcId].bo == 0)
      {
         continue;
      }
      else if (totBufSize >= (S32)(ueCb->lcs[lcId].bo))
      {
         ueCb->lcs[lcId].bo = 0;
      }
      else
      {
         ueCb->lcs[lcId].bo -= totBufSize;
      }
      /*ueCb->lcs[lcId].done = TRUE;*/
   }

   /* Perform validation to make sure that MAC must have allocated   */
   /* resources only if we had BO. BO is updated when we send StaRsp */
   
   for (j=0; j<rguDStaInd->staIndTb[1].nmbLch; j++)
   {
      ueCb = &rgAccCb.acUeCb[ueId];
      lcId = rguDStaInd->staIndTb[1].lchStaInd[j].lcId;
      if (ueCb->lcs[lcId].done == TRUE)
      {
         continue;
      }
      if (ueCb->lcs[lcId].bo == 0)
      {
      }
      else if (rguDStaInd->staIndTb[1].lchStaInd[j].totBufSize >= (S32)(ueCb->lcs[lcId].bo))
      {
         ueCb->lcs[lcId].bo = 0;
      }
      else
      {
         ueCb->lcs[lcId].bo -= rguDStaInd->staIndTb[1].lchStaInd[j].totBufSize;
      }
   }

   /* Store the STA IND received so that we could send out DatReq */
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
                (Data **)&node, sizeof(CmLList)) != ROK)
   {
      goto error_incorrect;
   }
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
                (Data **)&rguDStaInd, sizeof(*rguDStaInd)) != ROK)
   {
      goto error_incorrect;
   }
   cmMemcpy((U8 *)rguDStaInd, (U8 *)rgMsg->u.rguInfo.u.rguDStaInd, 
            sizeof(*rguDStaInd));

   node->node = (PTR)rguDStaInd;
   cmLListAdd2Tail(&ueCb->staIndLst, node);


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTransId",  &(saveTransId));
   if (saveTransId != 0)
   {
      rgAccCb.transId[saveTransId] = rgMsg->u.rguInfo.u.rguDStaInd->transId;
   }
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);

error_incorrect:
      CMXTA_DBG_ERR((_cmxtap, "Failed : StaInd Recieved with out a StaRsp. \n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
}/*-- rgAcHdlRguDStaInd --*/
#else
/**
 * @brief XTA Dedicated Channel Status Indication Handler for RGU interface
 *        with RGU_INF_OPTIMIZATION flag enabled. 
 *
 * @details
 *
 *     Function : rgAcHdlRguConsolidatedDStaInd  
 *     
 *     Validates DStatus Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information. It also caches the required information to
 *     used in sub-sequent DatReq/DatInd primitives. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguConsolidatedDStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRguConsolidatedDStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm    *msg = NULLP;
   RgAccMsgQElm    *rgMsg = NULLP;
   Pst             pst;
   SpId            suId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
   U8              ueId = 0;
   CmLteLcId       lcId = 0;
   U8             numLchTb1=1, numLchTb2=0;
   U16             j=0;
   RguDStaIndInfo  *dStaIndInfo = NULLP;  /* Consolidated dStaInd for all UEs*/ 
   RguDStaIndPerUe *dStaInd = NULLP;      /* Per UE DStaInd */
   U8             saveTransId = 0;
   RgAcUeCb        *ueCb=NULLP;
   CmLList         *node;
   S16             totBufSize;
   U8              lcIds[10];
   U8              numLcs = 0;
   U8              idx = 0;
   Inst            instId = 0;
 
   TRC2(rgAcHdlRguConsolidatedDStaInd);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguDStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRguDStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;
   dStaIndInfo = rgMsg->u.rguInfo.u.rguDStaInd;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));
   cmXtaGetPst(&pst, RGAC_RGU_PROVENT, instId, RGAC_RGU_USERENT, RGAC_RGU_USERINST, 
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
   
   pst.event = RGAC_RGU_EVTDSTAIND;
   
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",  &(ueId));
   for(idx =0; idx < dStaIndInfo->nmbOfUeGrantPerTti; idx++)
   {
      dStaInd = &(dStaIndInfo->staInd[idx]);
      if ((rgAccCb.acUeCb[ueId].crnti) == (dStaInd->rnti))
      {
         break;
      }
   }
   if(idx == (dStaIndInfo->nmbOfUeGrantPerTti))
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : RNTI MisMatch: exp (%d) \n",
               rgAccCb.acUeCb[ueId].crnti), 2);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rguInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rguInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
 
   if (cellId != dStaIndInfo->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, dStaIndInfo->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLchTb1",  &(numLchTb1));
 
   if (numLchTb1 != dStaInd->staIndTb[0].nmbLch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : numLchTb1 MisMatch: exp (%d) rcvd (%d) \n",
                  numLchTb1 , dStaInd->staIndTb[0].nmbLch), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLchTb2",  &(numLchTb2));
 
   if (dStaInd->nmbOfTbs == 1)
   {
      dStaInd->staIndTb[1].nmbLch = 0;
   }

   if (numLchTb2 != dStaInd->staIndTb[1].nmbLch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : numLchTb2 MisMatch: exp (%d) rcvd (%d) \n",
                  numLchTb2, dStaInd->staIndTb[1].nmbLch), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
   "lchTb1Data",  lcIds, &numLcs);
   if (numLcs != numLchTb1)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : numLchTb1 and lchTb1Data MisMatch"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
#ifdef LTE_ADV
   if(rgAccCb.lrgCb.forceCntrlSrbBoOnPCel)
   {
      if(dStaInd->fillCtrlPdu && (dStaIndInfo->cellId == 4))
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed :RLC sta pdu is scheduled on SCell"), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#endif
   /* Perform validation to make sure that MAC must have allocated   */
   /* resources only if we had BO. BO is updated when we send StaRsp */
   
   for (j=0; j< dStaInd->staIndTb[0].nmbLch; j++)
   {
      U32 i=0;
      ueCb = &rgAccCb.acUeCb[ueId];
      lcId = dStaInd->staIndTb[0].lchStaInd[j].lcId;
      for (; i<numLcs; i++)
      {
         if (lcId == lcIds[i]) break;
      }
      if (i == numLcs) goto error_incorrect;
      /*if (ueCb->lcs[lcId].done == TRUE)
      {
         continue;
      }*/
      totBufSize = dStaInd->staIndTb[0].lchStaInd[j].totBufSize;
      /*for (i=0; i< dStaInd->staIndTb[0].nmbLch; i++)
      {
         if ((lcId == dStaInd->staIndTb[0].lchStaInd[i].lcId) && (j != i))
         {
            totBufSize += dStaInd->staIndTb[0].lchStaInd[i].totBufSize;
         }
      }*/
      if (ueCb->lcs[lcId].bo == 0)
      {
         continue;
      }
      else if (totBufSize >= (S32)(ueCb->lcs[lcId].bo))
      {
         ueCb->lcs[lcId].bo = 0;
      }
      else
      {
         ueCb->lcs[lcId].bo -= totBufSize;
      }
      /*ueCb->lcs[lcId].done = TRUE;*/
   }

   /* Perform validation to make sure that MAC must have allocated   */
   /* resources only if we had BO. BO is updated when we send StaRsp */
   
   for (j=0; j< dStaInd->staIndTb[1].nmbLch; j++)
   {
      ueCb = &rgAccCb.acUeCb[ueId];
      lcId = dStaInd->staIndTb[1].lchStaInd[j].lcId;
      if (ueCb->lcs[lcId].done == TRUE)
      {
         continue;
      }
      if (ueCb->lcs[lcId].bo == 0)
      {
      }
      else if (dStaInd->staIndTb[1].lchStaInd[j].totBufSize >= (S32)(ueCb->lcs[lcId].bo))
      {
         ueCb->lcs[lcId].bo = 0;
      }
      else
      {
         ueCb->lcs[lcId].bo -= dStaInd->staIndTb[1].lchStaInd[j].totBufSize;
      }
   }

   /* Store the STA IND received so that we could send out DatReq */
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
                (Data **)&node, sizeof(CmLList)) != ROK)
   {
      goto error_incorrect;
   }
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
                (Data **)&dStaIndInfo, sizeof(*dStaIndInfo)) != ROK)
   {
      goto error_incorrect;
   }
   cmMemcpy((U8 *)dStaIndInfo, (U8 *)rgMsg->u.rguInfo.u.rguDStaInd, 
            sizeof(*dStaIndInfo));

   /* Storing nmbOfUeGrantPerTti in global Cb to use it while preparing 
    * consolidated DDatReq*/
   rgAccCb.nmbOfUeDatReqToBeSent = dStaIndInfo->nmbOfUeGrantPerTti;
   node->node = (PTR)dStaIndInfo;
   cmLListAdd2Tail(&ueCb->staIndLst, node);


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTransId",  &(saveTransId));
   if (saveTransId != 0)
   {
      rgAccCb.transId[saveTransId] = dStaInd->transId;
   }
   
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);

error_incorrect:
      CMXTA_DBG_ERR((_cmxtap, "Failed : StaInd Recieved with out a StaRsp. \n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
}/*--rgAcHdlRguConsolidatedDStaInd --*/
#endif
#ifdef LTE_L2_MEAS

/**
 * @brief XTA HARQ Status Indication Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguHqStaInd 
 *     
 *     Validates HqStatus Indication primitive recieved from MAC
 *     to Dummy-RLC against tester provided input and cached 
 *     information. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16  rgAcHdlRguHqStaInd 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRguHqStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm    *msg = NULLP;
   RgAccMsgQElm    *rgMsg = NULLP;
   Pst             pst;
   SpId            suId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
   U8              ueId = 0;
   U16             status[RGU_MAX_TB];
   U8              numSta;
   U8              idx;
 
   TRC2(rgAcHdlRguHqStaInd);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguHqStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguHqStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRguHqStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;

   cmXtaGetPst(&pst, RGAC_RGU_PROVENT, RGAC_RGU_PROVINST, RGAC_RGU_USERENT, RGAC_RGU_USERINST, 
   RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
   
   pst.event = RGAC_RGU_EVTHQSTAIND;
   
   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",  &(ueId));
   if (rgAccCb.acUeCb[ueId].crnti != rgMsg->u.rguInfo.u.rguHqStaInd->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : RNTI MisMatch: exp (%d) rcvd (%d) \n",
                  rgAccCb.acUeCb[ueId].crnti, rgMsg->u.rguInfo.u.rguHqStaInd->ueId), 2);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rguInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rguInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
 
   if (cellId != rgMsg->u.rguInfo.u.rguHqStaInd->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, rgMsg->u.rguInfo.u.rguHqStaInd->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   numSta = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSta",  &(numSta));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON, 
   "status",  status, &numSta);

   for(idx = 0; idx < numSta; idx++)
   {
#if 0
      if(rgMsg->u.rguInfo.u.rguHqStaInd->rguSnMapInfo[idx] != NULLP)
      {
         SPutSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
         (Data *)rgMsg->u.rguInfo.u.rguHqStaInd->rguSnMapInfo[idx],
         sizeof(RguSnMapInfo));
      }
#endif
      if(rgMsg->u.rguInfo.u.rguHqStaInd->status[idx] != status[idx])
      {
           RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- rgAcHdlRguHqStaInd --*/

#ifdef LTEMAC_R9
/**
 * @brief XTA L2M UL Throughput Measurement Req Handler for RGU interface. 
 *
 * @details
 *
 *     Function :  rgAcHdlRguL2MUlThrpMeasReq 
 *     
 *     Issues a UL Throughput Measurment Request from Dummy-RLC to MAC.
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguL2MUlThrpMeasReq 
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlRguL2MUlThrpMeasReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst             pst;
   SpId            spId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
   CmLteLcId       lcId[10];
   U8              ueId = 0;
   RguL2MUlThrpMeasReqInfo *measReq = NULLP;
   CmLteTimingInfo timingInfo;
   Bool            enbMeas = FALSE;
   U8              numLcId, i; 

   TRC2(rgAcHdlRguL2MUlThrpMeasReq);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguL2MUlThrpMeasReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguL2MUlThrpMeasReq(), tcId (%d)\n", tcCb->tcId));
#endif
 
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&timingInfo, sizeof(CmLteTimingInfo));
 
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL,
           (Data **) &measReq, sizeof(RguL2MUlThrpMeasReqInfo)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   cmXtaGetPst(&pst, RGAC_RGU_USERENT, RGAC_RGU_USERINST, RGAC_RGU_PROVENT, 
   RGAC_RGU_PROVINST, RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC);
 
   pst.event = RGAC_RGU_EVTULTHRMEASREQ;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "enbMeas", &(enbMeas));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
                  CMXTA_SEP_COLON,"lcIdLst", lcId, &numLcId);
   measReq->cellId = cellId;
   if(numLcId >10)
       RETVALUE(RFAILED); 
   for(i=0;i<numLcId;i++)
   {
      measReq->lcId[i] = lcId[i];
   }
   measReq->numLcId = numLcId;
   measReq->rnti = rgAccCb.acUeCb[ueId].crnti;
   measReq->enbMeas = enbMeas;
   
   
   /* Send the request to the MAC --*/
   RGAC_RGU_ULTHRPMEASREQ(&pst, spId, measReq);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlRguL2MUlThrpMeasReq --*/
#endif
#endif


/**
 * @brief Skip Validation Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRguSkipValidation  
 *     
 *     If tester does not want a particular indication from MAC 
 *     to be validated, he can just issue the leaf command SKIP,
 *     This is the corresponding handler function for SKIP, which
 *     will pop off the last received indication, without any 
 *     further processing. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRguSkipValidation
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRguSkipValidation(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;

   TRC2(rgAcHdlRguSkipValidation);
 
   UNUSED(spCb);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguSkipValidation(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRguSkipValidation(): tcId (%d)\n", tcCb->tcId));
#endif
 
   if(cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRguSkipValidation(): Peek failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /*-- Remove the msg from the Queue --*/
   if(cmXtaPopMsg(&(tcCb->msgQ[0]), &msg) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlRguSkipValidation(): Pop failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*rgAcHdlRguSkipValidation*/


#ifdef ANSI
PRIVATE Txt *rgAcStrtok
(
   Txt *start,
   Txt delim,
   Txt **pp,
   Txt buf[]
)
#else
PRIVATE Txt *rgAcStrtok(start, delim, pp, buf)
   Txt *start;
   Txt delim;
   Txt **pp;
   Txt buf[];
#endif
{
   S32 i = 0;
   Txt *p;
   S32 more = 0;
   if (start)
   {
      p = start;
   }
   else
   {
      p = *pp;
   }
   while (p && *p && *p != delim)
   {
      buf[i++] = *p;
      p++;
   }
   if (p && *p)
   {
      more = 1;
      p++;
   }
   *pp = p;
   buf[i] = '\0';
   if (more || i)
      RETVALUE(buf);
   else
      RETVALUE(NULL);
}



/**********************************************************************
 
         End of file:     rgac_rguhdl.c@@/main/3 - Sat Jul 30 02:21:04 2011
 
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
           rg007.201   ap  1. Added support for MIMO
           rg008.201  rsharon  1.Removed dependency on LTEMAC_MIMO flag.
           rg009.201  nudupi   1.Added The insure fixes.
                      rsharon  1. Change for CR ccpu00115756 . 
/main/3      ---     dvasisht      1. Updated for LTE MAC Release 3.1
$SID$      ---       rt            1. LTE MAC 4.1 release
*********************************************************************91*/
