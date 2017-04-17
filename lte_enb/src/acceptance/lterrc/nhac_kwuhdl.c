/********************************************************************20**

     Name:    RRC

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_kwuhdl.c

     Sid:      nhac_kwuhdl.c@@/main/3 - Fri Jul  1 01:13:02 2011

     Prg:     rer

*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
/* external headers */


/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhac_asn.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"

EXTERN NhAccCb nhAccCb;

PUBLIC Txt  pbuf[255] = {0};

/*
*
*       Fun:   nhAcHdlKwuBndReq
*
*       Desc:  Handler for Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_kwuhdl.c
*
*/


#ifdef ANSI
PUBLIC S16 nhAcHdlKwuBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlKwuBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SpId          spId = 0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   Bool          matchProc = FALSE;

   TRC2(nhAcHdlKwuBndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlKwuBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
   
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = KWU_EVT_BND_REQ;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlKwuBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spId --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.kwuInfo.kwInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.kwuInfo.kwInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlKwuBndReq --*/

/*
*
*       Fun:   nhAcHdlKwuUbndReq
*
*       Desc:  Unbind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_kwuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlKwuUbndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlKwuUbndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SpId          spId = 0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   Bool          matchProc = FALSE;

   TRC2(nhAcHdlKwuUbndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlKwuUbndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = KWU_EVT_UBND_REQ;
   
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlKwuUbndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.kwuInfo.kwInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.kwuInfo.kwInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlKwuUbndReq --*/

/*
*
*       Fun:   nhAcHdlKwuBndCfm
*
*       Desc:  KWU Bnd Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_kwuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlKwuBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlKwuBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;

   U8             status = CM_BND_OK;
   Bool           matchProc = FALSE;

   TRC2(nhAcHdlKwuBndCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = KWU_EVT_BND_CFM;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));
     
   
   if (CMXTA_ERR_NONE != KwUiKwuBndCfm(&pst, suId, status))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlkwuBndCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlkwuBndCfm --*/

/*
*
*       Fun:   nhAcHdlKwuDatReq
*
*       Desc:  KWU Measurement Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_kwuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlKwuDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlKwuDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   U16 cellId = 65535;
   U16 tCrnti = 0;
   U8 rbId;
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   U16           ueId;
   U16           numOfUe=0;
   S16           ret=ROK;
   SpId          spId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   Bool          matchProc = FALSE;
#ifdef CCPU_OPT
   U8            subFrmNo=0;
   U16           sfn=0;
#endif
   
 
   TRC2(nhAcHdlKwuDatReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuDatReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlKwuDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = KWU_EVT_DAT_REQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlKwuDatReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.kwuInfo.kwInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.kwuInfo.kwInfo.spId), 2);

      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16,"ueId",&(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rbId",&(rbId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16,"numOfUe",&(numOfUe));

   if ((rrcMsg->u.kwuInfo.kwInfo.datReqInfo.rlcId.rbId != rbId)  ||
       (numOfUe > 1 && rrcMsg->u.kwuInfo.kwInfo.datReqInfo.rlcId.ueId != ueId) ||
       (rrcMsg->u.kwuInfo.kwInfo.datReqInfo.rlcId.cellId != cellId))
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlKwuDatReq() : Validation of UeId/CellId/rbId Failed\n"));
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

#ifdef CCPU_OPT
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U8,"subFrmNo",&(subFrmNo));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16,"sfn",&(sfn));
   if (rrcMsg->u.kwuInfo.kwInfo.datReqInfo.lcType == CM_LTE_LCH_PCCH)
   {
      if ((rrcMsg->u.kwuInfo.kwInfo.datReqInfo.tm.tmg.sfn != sfn)
          || (rrcMsg->u.kwuInfo.kwInfo.datReqInfo.tm.tmg.subframe !=
              subFrmNo))
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlKwuDatReq() : Validation of timing info Failed\n"));
         cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#endif
   
   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlKwuDatReq --*/

/*
*
*       Fun:   nhAcHdlKwuDatInd
*
*       Desc:  KWU Data Indication to RRC
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_kwuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlKwuDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlKwuDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   KwuDatIndInfo  *datIndInfo; 
   SpId          spId=0;
   SuId          suId = 0; 
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   Bool          matchProc = FALSE;
   Buffer        *mBuf = NULLP;
   U16           cellId=0, tCrnti=0;
   U8            rbId=0;
   S16           msgType=0;
   U8            failInd = 0;
   U8            nullSdu = 0;
   U8            nullmBuf = 0;


   TRC2(nhAcHdlKwuDatInd)


   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   /* Allocate memory for DatInd */
   CMXTA_ALLOC(&datIndInfo, sizeof(KwuDatIndInfo));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlKwuDatInd(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- This message should be osted to RRC --*/
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = KWU_EVT_DAT_IND;

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "rbId",  &(rbId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "msgType",  &msgType);


   datIndInfo->rlcId.rbId = rbId;
   datIndInfo->rlcId.cellId = cellId;
   /* Dont Fill UE ID for Connection Request Messages */

#ifdef CCPU_OPT
   datIndInfo->tCrnti = tCrnti;
#endif

   nhAcConstructAndEncodeCcchMsg(&pst, msgType, &mBuf, spCb, tcCb);

  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "failInd",
         &(failInd));
   if (failInd)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(datIndInfo, sizeof(KwuDatIndInfo));
         datIndInfo = NULLP;
      }
      else
      {
         CMXTA_FREEMBUF(mBuf);
         CMXTA_FREE(datIndInfo, sizeof(KwuDatIndInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullmBuf",  &(nullmBuf));
   if (nullmBuf)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREEMBUF(mBuf);
         mBuf = NULLP;
      }
      else
      {
         CMXTA_FREEMBUF(mBuf);
         CMXTA_FREE(datIndInfo, sizeof(KwuDatIndInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }


   if ((msgType == C1_RRCCONREESTBRQST) || 
       (msgType == C1_RRCCONRQST))
   {
      SPrntMsg(mBuf, 0, 0);
      sprintf( pbuf , " \n\n\n");
      SPrint(  pbuf  );
      
      if (CMXTA_ERR_NONE != KwUiKwuDatInd(&pst, suId, datIndInfo, mBuf))
      {
         CMXTA_DBG_ERR((_cmxtap,"nhAcHdlKwuDatInd() : returned RFAILED\n"));
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlKwuDatInd() : Invalid Message Type\n"));
      RETVALUE(RFAILED);
   }
    
   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlKwuDatInd--*/


/**********************************************************************
         End of file:     nhac_kwuhdl.c@@/main/3 - Fri Jul  1 01:13:02 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    rer              1. LTE RRC Initial Release.
/main/2      ---    chebli           1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/


