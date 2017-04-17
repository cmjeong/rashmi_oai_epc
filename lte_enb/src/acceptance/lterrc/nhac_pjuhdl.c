/********************************************************************20**

     Name:    RRC  

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_pjuhdl.c

     Sid:      nhac_pjuhdl.c@@/main/3 - Fri Jul  1 01:13:08 2011

     Prg:     dm

*********************************************************************21*/

/* header include files (.h) */
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

/*
*
*
*       Fun:   nhAcHdlPjuBndReq
*
*       Desc:  Handler for Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_pjuhdl.c
*
*/


#ifdef ANSI
PUBLIC S16 nhAcHdlPjuBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlPjuBndReq(tcCb, spCb)
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

   TRC2(nhAcHdlPjuBndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlPjuBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
   
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTPJUBNDREQ;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlPjuBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spId --*/
   /* define the following function    */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.pjuInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.pjuInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlPjuBndReq --*/


/*
*
*       Fun:   nhAcHdlPjuUbndReq
*
*       Desc:  Unbind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_pjuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlPjuUbndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlPjuUbndReq(tcCb, spCb)
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

   TRC2(nhAcHdlPjuUbndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlPjuUbndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTPJUUBNDREQ;
   
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlPjuUbndReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   spId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.pjuInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.pjuInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlPjuUbndReq --*/

/*
*
*       Fun:   nhAcHdlPjuBndCfm
*
*       Desc:  PJU Bnd Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_pjuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlPjuBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlPjuBndCfm(tcCb, spCb)
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

   TRC2(nhAcHdlPjuBndCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlRluBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTPJUBNDCFM;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));
    
   PjUiPjuBndCfm(&pst, suId,  status);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlPjuBndCfm --*/


/*
*
*       Fun:   nhAcHdlPjuDatReq
*
*       Desc:  PJU Data Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_pjuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlPjuDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlPjuDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret=ROK;
   SpId          spId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   Bool          matchProc = FALSE;
   U8            pdcpInstId;
   U16           cellId;
   U16           ueId;
   
 
   TRC2(nhAcHdlPjuDatReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuDatReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlPjuDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,
                  matchProc);
   pst.event = EVTPJUDATREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlPjuDatReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   spId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.pjuInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.pjuInfo.spId), 2);

      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpInstId",
         &(pdcpInstId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16,"ueId",&(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   if ((rrcMsg->u.pjuInfo.pdcpId.rbId != pdcpInstId)  ||
        (rrcMsg->u.pjuInfo.pdcpId.ueId != ueId) ||
              (rrcMsg->u.pjuInfo.pdcpId.cellId != cellId))
   {
       cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
       RETVALUE(CMXTA_ERR_INT);
   }
   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlPjuDatReq --*/

/*
*
*       Fun:   nhAcHdlPjuDatInd
*
*       Desc:  PJU Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_pjuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlPjuDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlPjuDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SpId          spId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   Buffer        *mBuf = NULLP, *tmpBuf = NULLP;
   CmLtePdcpId   *pdcpId;
   S16           msgType;
   SuId          suId = 0;      
   U16           cellId = 65535;
   U8            svcType;
   U8            pdcpFailCause = 0;
   Bool          matchProc = FALSE;
   U8            pdcpInstId = 255;
   U32           ueId;
   U8            decodeFail = 0;
   U8            failInd = 0;
   U8            nullPdcpId = 0;
   U8            nullmBuf = 0;

   TRC2(nhAcHdlPjuDatInd)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuDatInd(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ALLOC(&pdcpId, sizeof(CmLtePdcpId));

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTPJUDATIND;

   /*-- Set default value & validate for spid --*/
   spId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16,"cellId",&cellId);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "msgType",  &msgType);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "svcType", &svcType);

   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U32, "ueId",  &(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpInstId", &(pdcpInstId));

   pdcpId->rbId = pdcpInstId;
   pdcpId->ueId = ueId;
   pdcpId->cellId = cellId;
   
   cmMemset((U8*)&nhAccCb.sndErrReq, 0 , sizeof(NhAcSndErrReq));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expMacErr",
                  &(nhAccCb.sndErrReq.expMacErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expRlcErr",
                  &(nhAccCb.sndErrReq.expRlcErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expPdcpErr",
                  &(nhAccCb.sndErrReq.expPdcpErr));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpFailCause",
         &pdcpFailCause);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "decodeFail",
         &(decodeFail));

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

   if (decodeFail)
   {
     /* Copy some dummy data into mBuf */
     nhAcUtlPjuFillForDecodeFail(&mBuf);
   }
   else
   {
      if(nhAcConstructAndEncode(&pst, msgType, &mBuf,spCb,tcCb) !=
                  CMXTA_ERR_NONE)
      {
         CMXTA_DBG_ERR((_cmxtap, "Failed Constructing message\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   tmpBuf = (Buffer *)mBuf;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullPdcpId",  &(nullPdcpId));
   if (nullPdcpId)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId))
         pdcpId = NULLP;
      }
      else
      {
         CMXTA_FREEMBUF(mBuf);
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId))
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
         tmpBuf = NULLP;
      }
      else
      {
         CMXTA_FREEMBUF(mBuf);
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId))
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   nhAcUtlFillFailStatus(tcCb, spCb);

   PjUiPjuDatInd(&pst, suId, pdcpId, tmpBuf); 

   RETVALUE(CMXTA_ERR_NONE);

}/*-- pjAcHdlPjuDatInd--*/


/*
*
*       Fun:   nhAcHdlPjuDatCfm
*
*       Desc:  PJU Data Confirmation
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_pjuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlPjuDatCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlPjuDatCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   CmLtePdcpId   *pdcpId;
   PjuDatCfmInfo *datCfmInfo;
   SuId          suId=0;
   Bool          matchProc = FALSE;
   U8            failCfm=0;
   U8            numSdus=1;
   U8            nullPdcpId = 0;
   U8            nullSdu = 0;
   
   TRC2(nhAcHdlPjuDatCfm)
   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuDatCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuDatCfm(), tcId (%d)\n", tcCb->tcId));
#endif


   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;


#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTPJUDATCFM;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   /* Allocate memory for PDCP ID */
   CMXTA_ALLOC(&pdcpId, sizeof(CmLtePdcpId));
   /* Fill MUI */
   if (NULLP == pdcpId)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlPjuDatCfm() : failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /* Fetch the ueid and pdcpInstId */   
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(pdcpId->ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(pdcpId->cellId));


   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpInstId",
  &(pdcpId->rbId));
   
   /* Allocate memory for DatInd */
   CMXTA_ALLOC(&datCfmInfo, sizeof(PjuDatCfmInfo));
   /* Fill MUI */
   if (NULLP == datCfmInfo)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlPjuDatCfm() : failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "numSdus",
         &(numSdus));
   datCfmInfo->numSdus = numSdus;
   datCfmInfo->cfmSta[0].sduId = nhAccCb.mui;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "mui",
                                                  &(datCfmInfo->cfmSta[0].sduId));

   datCfmInfo->cfmSta[0].status = PJU_DAT_CFM_SUCCESS; /* by default */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",
         &(datCfmInfo->cfmSta[0].status));

  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "failCfm",
         &(failCfm));

   if (failCfm)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullPdcpId",  &(nullPdcpId));
   if (nullPdcpId)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId))
         pdcpId = NULLP;
      }
      else
      {
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId))
         CMXTA_FREE(datCfmInfo, sizeof(PjuDatCfmInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(datCfmInfo, sizeof(PjuDatCfmInfo));
         datCfmInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId))
         CMXTA_FREE(datCfmInfo, sizeof(PjuDatCfmInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }


   PjUiPjuDatCfm(&pst, suId, pdcpId, datCfmInfo);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlPjuDatCfm--*/
/*
*
*       Fun:   nhAcHdlPjuStaInd
*
*       Desc:  PJU Status Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_pjuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlPjuStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlPjuStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   CmLtePdcpId   *pdcpId;
   PjuStaIndInfo *staInd;
   SuId          suId=0;
   Bool          matchProc = FALSE;
   Buffer        *mBuf = NULLP;
   U8            secModFailMsg = 0;
   Bool          decodeFail = FALSE;
   U8            failInd=0;
   U8            ueCap=0;
   U8            nullSdu = 0;
   U8            nullPdcpId = 0;


   TRC2(nhAcHdlPjuStaInd)
   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlPjuStaInd(), tcId (%d)\n", tcCb->tcId));
#endif


   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;


#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTPJUSTAIND;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /* Allocate memory for pdcpId */
   CMXTA_ALLOC(&pdcpId, sizeof(CmLtePdcpId));
   /* Fill MUI */
   if (NULLP == pdcpId)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlPjuDatCfm() : failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   /* Fetch the ueid and pdcpInstId */   
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(pdcpId->ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",
         &(pdcpId->cellId));

   /* Allocate memory for staInd */
   CMXTA_ALLOC(&staInd, sizeof(PjuStaIndInfo));
   if (NULLP == staInd)
   {
      CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
      RETVALUE(RFAILED); 
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpInstId",
                                          &(pdcpId->rbId));
   /* Fill MUI */

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cause",  &(staInd->cause));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "secModFailMsg",
                     &secModFailMsg);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "decodeFail",
                     &(decodeFail));

  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "failInd",
         &(failInd));
  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "ueCap",
         &(ueCap));
  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullPdcpId",  &(nullPdcpId));

   if (failInd)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }

   if (secModFailMsg)
   {
      if (decodeFail)
      {
        CMXTA_ALLOCMBUF(&mBuf);
      }
      else
      {
         if (nhAcConstructAndEncode(&pst, C1_SECURITYMODEFAIL, &mBuf,spCb,tcCb) !=
                     CMXTA_ERR_NONE)
         {
            CMXTA_DBG_ERR((_cmxtap, "Failed Constructing message\n"));
            CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
            CMXTA_FREE(staInd, sizeof(PjuStaIndInfo));
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      if (nullPdcpId)
      {
         if (pst.selector == 1)
         {
            CMXTA_FREE(staInd, sizeof(PjuStaIndInfo));
            staInd = NULLP;
         }
         else
         {
            CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
            CMXTA_FREE(staInd, sizeof(PjuStaIndInfo));
            if (mBuf)
            {
               CMXTA_FREEMBUF(mBuf);
            }
            RETVALUE(CMXTA_ERR_NONE);
         }
      }

      if (nullSdu)
      {
         if (pst.selector == 1)
         {
            CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
            pdcpId = NULLP;
         }
         else
         {
            CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
            CMXTA_FREE(staInd, sizeof(PjuStaIndInfo));
            if (mBuf)
            {
               CMXTA_FREEMBUF(mBuf);
            }
            RETVALUE(CMXTA_ERR_NONE);
         }
      }

      PjUiPjuStaInd(&pst, suId, pdcpId, staInd, mBuf);

      RETVALUE(CMXTA_ERR_NONE);
   }

   if(ueCap)
   {
      if (nhAcConstructAndEncode(&pst, C1_UECAPINFO, &mBuf,spCb,tcCb) !=
                  CMXTA_ERR_NONE)
      {
         CMXTA_DBG_ERR((_cmxtap, "Failed Constructing message\n"));
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
         CMXTA_FREE(staInd, sizeof(PjuStaIndInfo));
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(staInd, sizeof(PjuStaIndInfo));
         staInd = NULLP;
      }
      else
      {
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
         CMXTA_FREE(staInd, sizeof(PjuStaIndInfo));
         if (mBuf)
         {
            CMXTA_FREEMBUF(mBuf);
         }
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   if (nullPdcpId)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
         pdcpId = NULLP;
      }
      else
      {
         CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId));
         CMXTA_FREE(staInd, sizeof(PjuStaIndInfo));
         if (mBuf)
         {
            CMXTA_FREEMBUF(mBuf);
         }
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

/*  CMXTA_ALLOCMBUF(&mBuf); */

  PjUiPjuStaInd(&pst, suId, pdcpId, staInd, mBuf);

  RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlPjuStaInd--*/


/**********************************************************************
         End of file:     nhac_pjuhdl.c@@/main/3 - Fri Jul  1 01:13:08 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat     init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     dm               1. LTE RRC Initial Release.
/main/2      ---     chebli           1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

