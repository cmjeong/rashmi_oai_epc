
/**********************************************************************
  
     Name:     LTE RRC Layer
 
     Type:     C source file
  
     Desc:     Handler functions  for controlling acceptance 
               tests execution.

     File:     nhac_nhuhdl.c
  
     Sid:      nhac_nhuhdl.c@@/main/3 - Fri Jul  1 01:13:05 2011
   
     Prg:      Reena
  
**********************************************************************/

/* header include files (.h) */
#include <stdlib.h>        /* for atoi */
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
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "nhu_asn.h"
#include "cm_pasn.h"
#include <stdlib.h>        /* For atoi function */
#include <string.h>        /* for strlen */
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
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_acc_nhu.x"
#include "nhac_acc1.x"
#include "nh.x"

EXTERN NhAccCb nhAccCb;
EXTERN NhAccCpjVal  gCpjCfgStore[25];
EXTERN NhAccCrgVal  gCrgValStore[25];
EXTERN NhAccCkwVal  gCkwValStore[25];
#ifdef RRC_PHY_CFG_SUPP
EXTERN NhAccCtfVal  gCtfValStore[25];
#endif
EXTERN U8 gValIdx;


/*
*
*       Fun:   nhAcHdlNhuBndReq
*
*       Desc:  Handler for NHU Bind Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhuBndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId; 
   SuId          suId;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            cfmFail = 0;

   TRC2(nhAcHdlNhuBndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuBndReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuBndReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",&dstProcId);
#endif

   /*-- Get the Pst information here from RRC User to RRC Layer --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event   = EVTNHUBNDREQ;

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   suId = 0;
   spId = 0;

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* if the spId value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuBndReq(): SpId not provided\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   /* if the suId value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuBndReq(): SuId not provided\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cfmFail",  &(cfmFail));
   if (cfmFail)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }

   /* Send the request to the RRC --*/
   if(CMXTA_ERR_NONE != NxLiNhuBndReq(&pst, suId, spId))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuBndReq(): Mapping returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);

}/*-- nhAcHdlNhuBndReq --*/

/*
*
*       Fun:   nhAcHdlNhuBndCfm
*
*       Desc:  Call Handler for NHU Bind Confirmation
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuBndCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NhAccMsgQElm  *rrcMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U16            status;

   TRC2(nhAcHdlNhuBndCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rrcMsg = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Get the Pst information here from RRC User to RRC Layer --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event = EVTNHUBNDCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   suId = 0;

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   /* if the suId value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuBndCfm(): SuId not provided from xml\n"));
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Compare the value in the message and the value provided from xml */
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rrcMsg->u.nhuInfo.suId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   status = 0;
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "status",
                  &(status));
   if (status != rrcMsg->u.nhuInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : status MisMatch: exp (%d) rcvd (%d) \n",
                  status, rrcMsg->u.nhuInfo.status), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlNhuBndCfm --*/

/*
*
*       Fun:   nhAcHdlNhuUbndReq
*
*       Desc:  Call Handler for NHU UnBind Request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId;
   Reason         reason;
   ProcId         srcProcId;
   ProcId         dstProcId;
   S16            ret = 0;

   TRC2(nhAcHdlNhuUbndReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Any API validation if required, use Python wrapper APIs --*/
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",&dstProcId);
#endif

   /*-- Get the Pst information here from RRC User to RRC Layer --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event = EVTNHUUBNDREQ;

   spId = 0;
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   /* if the spId value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuUbndReq(): SpId not provided from xml\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   reason = 0; /*-- Reason is unused --*/

   /* Send the request to the RRC --*/
   if(CMXTA_ERR_NONE != NxLiNhuUbndReq(&pst, spId, reason))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuUbndReq(): returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);

} /*-- nhAcHdlNhuUbndReq --*/

/*
*
*       Fun:   nhAcHdlNhuDatCfm
*
*       Desc:  NHU Data Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuDatCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuDatCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            datCfmStatus;
   U8            pdcpId;

   TRC2(nhAcHdlNhuDatCfm)

#ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDatCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDatCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuDatCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg      =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
         dstProcId,FALSE);

   pst.event = EVTNHUDATCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuDatCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Validate PDCP ID */
   pdcpId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId",  &(pdcpId));
   rrcMsg = (NhAccMsgQElm *)msg->data;
   if(pdcpId)
   {
      if(((NhuDatCfmSdus *)rrcMsg->mBuf)->pdcpId != pdcpId)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuDatCfm() : pdcpId mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_NOMATCH);

      }
   }

   /* Validate Data Cfm Status */
   datCfmStatus = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "datCfmStatus",
         &(datCfmStatus));
   if(datCfmStatus)
   {
      if(((NhuDatCfmSdus *)rrcMsg->mBuf)->datCfmStatus != datCfmStatus)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuDatCfm() : datCfmStatus mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_NOMATCH);

      }
   }

   /*-- Set default value & validate for suId --*/
   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) recvd (%d) \n",
               suId, rrcMsg->u.nhuInfo.suId),2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* nhAcHdlNhuDatCfm */

/*
*
*       Fun:   nhAcHdlNhuStaInd
*
*       Desc:  NHU Status Indication
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuStaInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            errCause;
   U8           pdcpId;

   TRC2(nhAcHdlNhuStaInd)

#ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuStaInd(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg      =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
         dstProcId,FALSE);

   pst.event = EVTNHUSTAIND;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuStaInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Validate PDCP ID */
   pdcpId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId",  &(pdcpId));
   if(pdcpId)
   {
      if(((NhuStaIndSdus *)((NhAccMsgQElm *)msg->data)->mBuf)->pdcpId
            != pdcpId)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuStaInd() : pdcpId mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_NOMATCH);

      }
   }

   /* Validate error cause */
   errCause = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "errorCause",
         &(errCause));
   if(errCause)
   {
      if(((NhuStaIndSdus *)((NhAccMsgQElm *)msg->data)->mBuf)->cause
            != errCause)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuStaInd() : errCause mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_NOMATCH);

      }
   }

   /*-- Set default value & validate for suId --*/
   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) recvd (%d) \n",
               suId, rrcMsg->u.nhuInfo.suId),2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* nhAcHdlNhuStaInd */

/*
*
*       Fun:   nhAcHdlNhuErrInd
*
*       Desc:  NHU Error Indication
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuErrInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuErrInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            errType;
   U16           errCause;
   U16           ueId;

   TRC2(nhAcHdlNhuErrInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuErrInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuErrInd(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuErrInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg      =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);
   if((nhAccCb.sndErrReq.expMacErr || nhAccCb.sndErrReq.expPdcpErr || 
         nhAccCb.sndErrReq.expRlcErr) && (pst.selector != 1))
   {
       RETVALUE(CMXTA_ERR_NONE);
   }

   pst.event = EVTNHUERRIND;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuErrInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Validate ueId */
   ueId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   if(ueId)
   {
      if(((NhuErrIndSdus *)((NhAccMsgQElm *)msg->data)->mBuf)->hdr.ueId != ueId)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuErrInd() : ueId mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_NOMATCH);
      }
   }

   /* Validate error type */
   errType = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "errorType",
               &(errType));
   if(errType)
   {
      if(((NhuErrIndSdus *)((NhAccMsgQElm *)msg->data)->mBuf)->sdu.errType
                  != errType)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuErrInd() : errorType mismatch (expected) %d != %d (received)\n",
                  errType, ((NhuErrIndSdus *)((NhAccMsgQElm *)msg->data)->mBuf)->sdu.errType));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_NOMATCH);

      }
   }

   /* Validate error cause */
   errCause = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "errorCause",
                  &(errCause));
   if(errCause)
   {
      if(((NhuErrIndSdus *)((NhAccMsgQElm *)msg->data)->mBuf)->sdu.errCause
                  != errCause)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuErrInd() : errCause mismatch (expected) %d != %d (received)\n",
                  errCause, ((NhuErrIndSdus *)((NhAccMsgQElm *)msg->data)->mBuf)->sdu.errCause));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_NOMATCH);

      }
   }

   /*-- Set default value & validate for suId --*/
   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) recvd (%d) \n",
                  suId, rrcMsg->u.nhuInfo.suId),2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* nhAcHdlNhuErrInd */

/*
*
*       Fun:   nhAcHdlNhuDatReq
*
*       Desc:  NHU Dat Request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuDatReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            msgCategory;
   U8            msgType;
   NhuDatReqSdus *nhuDatReqEvntSdu=NULLP;
   U8            bitMask;
   U32           pag_cause = 0;
   U32           domainIdent = 0;
   S16           ret;
   U8            rbId;
   U8            sfn;
   U8            subFrmNo;
   U32           numOfUe = 0;
   Mem           sMem;
   U8            expCfgBitMask;
   NhuUeCfgInfo  *ueCfg;
   U8            valChk=TRUE;
   U8            invalidMsgCat=0;
   U8            nullSdu = 0;
   Bool          sCellAdd = FALSE;

   TRC2(nhAcHdlNhuDatReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDatReq(), tcId (%d)\n", tcCb->tcId));
#endif

   /* Initial structs to zero */
   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   /* allocate Data request event */
   sMem.region = 0;
   sMem.pool = 0;
   CMXTA_ALLOC_EVNT(&nhuDatReqEvntSdu, sizeof(NhuDatReqSdus), &sMem,
                                                    NHAC_MEM_PDU_SIZE);

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",
               &srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
               dstProcId,FALSE);

   spId = 0;

   cmMemset((U8*)&nhAccCb.sndErrReq, 0 , sizeof(NhAcSndErrReq));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expMacErr",
                  &(nhAccCb.sndErrReq.expMacErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expRlcErr",
                  &(nhAccCb.sndErrReq.expRlcErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expPdcpErr",
                  &(nhAccCb.sndErrReq.expPdcpErr));
#ifdef RRC_PHY_CFG_SUPP
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expPhyErr",
                  &(nhAccCb.sndErrReq.expPhyErr));
#endif

   /* spId */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   /* Fill HDR Info */
   nhAcUtlFillNhuEvntHdr(&tcCb, &spCb, &(nhuDatReqEvntSdu->hdr));

   /* Bit Mask Value if Msg or UeCfg or Both */
   bitMask = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "bitMask",\
               &(bitMask));
   if(!bitMask)
      bitMask = 0; /* Fill Msg Only */

   if(bitMask)
   {
     nhuDatReqEvntSdu->sdu.isUeCfgPres = TRUE;
   }
   else
   {
     nhuDatReqEvntSdu->sdu.isUeCfgPres = FALSE;
   }
      
   msgCategory = 0;
   /* Message Type (Based on Channel) */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "msgCategory",  &(msgCategory));

   /* RB ID */
   rbId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "rbId",\
         &rbId);

   /*-- System frame number --*/
   sfn = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "sfn",\
         &sfn);

   /*-- subframe number --*/
   subFrmNo = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "subFrmNo",\
         &subFrmNo);

   msgType = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "msgType",
               &(msgType));



   /*-- Check for bit mask --*/
   if((bitMask == 0) || (bitMask == 2))
   {
      switch(msgCategory)
      {
         case NHU_MSG_DLPCCH:
            /* Fill the massage category */

            /*Initialise validation check to FALSE by default*/
            nhAccCb.valChk = FALSE;
            nhuDatReqEvntSdu->sdu.ueMsg.isMsgDed = 0;
            nhuDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgCategory = msgCategory;
            nhuDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgInfo.rbId = rbId;

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "pagingCause",
                   &pag_cause);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "noUe",
                   &numOfUe);
            if(!numOfUe)
               numOfUe = 1;

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,
                     "domainIdentity", &domainIdent);

/*
            if(!pag_cause)
               pag_cause = NhuPagCausecauseValueEnum;

            if(!domainIdent)
               domainIdent = NhuPagRecordLstMembercn_DomainpsEnum;
*/

            /* Fill the paging message --*/
            ret = nhAcUtlFillNhuPagingMsg(tcCb, spCb, nhuDatReqEvntSdu, sfn,
                     subFrmNo);

            if (ret != CMXTA_ERR_NONE)
            {
               CMXTA_FREEEVNT(nhuDatReqEvntSdu);
               RETVALUE(RFAILED);
            }
            break;

         case NHU_MSG_DLDCCH:
            /* Fill the message category */
            nhuDatReqEvntSdu->sdu.ueMsg.isMsgDed = 1;
            nhuDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.isMsgEncoded 
                                            = FALSE;
            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,
                     "isMsgEncoded", 
               &nhuDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.isMsgEncoded);

            FILL_UINT_TKN(nhuDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.\
                          m.dcchMsg.message.val.c1.choice, msgType);

            switch(msgType)
            {
               /* Downlink Transfer Information */
               case C1_DLINFOTFR:

            /*Initialise validation check to FALSE by default*/
                  nhAccCb.valChk = FALSE;
                  ret = nhAcUtlFillNhuInfoTfr(tcCb, spCb, nhuDatReqEvntSdu,
                        sfn, subFrmNo);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;
               /* Connection Reconfiguration  */
               case C1_RRCCONRECFGN:

                  /*Initialise validation check to FALSE by default*/
                  cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8, "valChk", &(valChk));
                  nhAccCb.valChk = valChk;
                  ret = nhAcUtlFillNhuRrcConReCfgn(tcCb, spCb, nhuDatReqEvntSdu,
                              sfn, subFrmNo);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;
               /* Connection Release */
               case C1_RRCCONRLS:
                  /*nothing much to validate*/
                  nhAccCb.valChk = FALSE;
                  ret = nhAcUtlFillNhuConRls(tcCb, spCb, nhuDatReqEvntSdu);
                  
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;
               /* Security Mode Command */
               case C1_SECURITYMODECMD:
                  /*Initialise validation check to FALSE by default*/
                  cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8, "valChk", &(valChk));
                  nhAccCb.valChk = valChk;

                  ret = nhAcUtlFillNhuSecurityModeCmd(tcCb, spCb, 
                                                      nhuDatReqEvntSdu);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;

               /* UE Capability Enquiry */
               case C1_UECAPENQUIRY:
                  /*Initialise validation check to FALSE by default*/
                  nhAccCb.valChk = FALSE;

                  ret = nhAcUtlFillNhuUeCapEnq(tcCb, spCb, 
                                                      nhuDatReqEvntSdu);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }

                  break;

               /* Mobility from E-UTRA Command */
               case C1_MOBILITYFROMEUTRACMD:
                  /*Initialise validation check to FALSE by default*/
                  nhAccCb.valChk = FALSE;

                  ret = nhAcUtlFillNhuMobFrmEutraCmd(tcCb, spCb, 
                                                      nhuDatReqEvntSdu);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }

                  break;

               /* HO From E-UTRA Preparation Transfer */
               case C1_HANDOVERFROMEUTRAPREPRQST:
                  /*Initialise validation check to FALSE by default*/
                  nhAccCb.valChk = FALSE;

                  ret = nhAcUtlFillNhuHoFrmEutraPrep(tcCb, spCb, 
                                                      nhuDatReqEvntSdu);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;

               /* Counter Check Request */
               case C1_COUNTERCHECK:
                  /*Initialise validation check to FALSE by default*/
                  nhAccCb.valChk = FALSE;

                  ret = nhAcUtlFillNhuCounterCheckMsg(tcCb, spCb, 
                                                      nhuDatReqEvntSdu);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;

#ifdef LTERRC_REL9
               /*TODO:MP: UE Information Request */
               case C1_UEINFORQST_R9__1:
                  /*Initialise validation check to FALSE by default*/
                  nhAccCb.valChk = FALSE;

                  ret = nhAcUtlFillNhuUEInfoRqst(tcCb, spCb, 
                                                      nhuDatReqEvntSdu);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;
#endif /* LTERRC_REL9 */

               default:
                  break;
            }
            break;

         case NHU_MSG_DLBCCHBCH:
            /*Initialise validation check to FALSE by default*/
            nhAccCb.valChk = FALSE;

            nhuDatReqEvntSdu->sdu.ueMsg.isMsgDed = 0;
            nhuDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgCategory = msgCategory;
            nhuDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgInfo.rbId = rbId;

            ret = nhAcUtlFillNhuNhuBCCH_BCHMsg(tcCb, spCb, nhuDatReqEvntSdu,
                     sfn, subFrmNo);
            if (ret != CMXTA_ERR_NONE)
            {
               CMXTA_FREEEVNT(nhuDatReqEvntSdu);
               RETVALUE(RFAILED);
            }
            break;

         case NHU_MSG_DLBCCHDLSCH:

            /*Initialise validation check to FALSE by default*/
            nhAccCb.valChk = FALSE;
            nhuDatReqEvntSdu->sdu.ueMsg.isMsgDed = 0;
            nhuDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgCategory = msgCategory;
            nhuDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgInfo.rbId = rbId;

            switch (msgType)
            {
               case C1_SYSTEMINFO:
                  ret = nhAcUtlFillNhuSysInfo(tcCb, spCb, nhuDatReqEvntSdu,
                           sfn, subFrmNo);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;

               case C1_SYSTEMINFOBLOCKTYP1:
                  ret = nhAcUtlFillNhuSysInfoBlockType1(tcCb, spCb,
                           nhuDatReqEvntSdu, sfn, subFrmNo);
                  if (ret != CMXTA_ERR_NONE)
                  {
                     CMXTA_FREEEVNT(nhuDatReqEvntSdu);
                     RETVALUE(RFAILED);
                  }
                  break;

               default:
                  break;
            }
            break;
         default:
            /* Shouldnt be here */
            break;
      }
   }
    if(nhAccCb.valChk)
     {
     ret = nhAcUtlGetNxtValIdx();

     if(ret == RFAILED)
     {
        CMXTA_DBG_ERR((_cmxtap," No un-used slot available\n"));
        RETVALUE(RFAILED);
     }

     gCrgValStore[gValIdx].cellId = nhuDatReqEvntSdu->hdr.cellId;
     gCrgValStore[gValIdx].ueId = nhuDatReqEvntSdu->hdr.ueId;

     gCkwValStore[gValIdx].cellId = nhuDatReqEvntSdu->hdr.cellId;
     gCkwValStore[gValIdx].ueId = nhuDatReqEvntSdu->hdr.ueId;
     gCkwValStore[gValIdx].transId = nhuDatReqEvntSdu->hdr.transId;

     gCpjCfgStore[gValIdx].cellId = nhuDatReqEvntSdu->hdr.cellId;
     gCpjCfgStore[gValIdx].ueId = nhuDatReqEvntSdu->hdr.ueId;
     gCpjCfgStore[gValIdx].transId = nhuDatReqEvntSdu->hdr.transId;

#ifdef RRC_PHY_CFG_SUPP
     gCtfValStore[gValIdx].cellId = nhuDatReqEvntSdu->hdr.cellId;
     gCtfValStore[gValIdx].ueId = nhuDatReqEvntSdu->hdr.ueId;
     gCtfValStore[gValIdx].transId = nhuDatReqEvntSdu->hdr.transId;
#endif /* RRC_PHY_CFG_SUPP */

     }
      if((bitMask == 1) || (bitMask == 2))
      {
         /*- Fill the UE configuration information --*/
         ueCfg = &(nhuDatReqEvntSdu->sdu.ueCfg);

         /* 
            UE Configuration Inforamtion :
            ------------------------------
               RB Configuration - ADD/MODIFY/RELEASE 
               Transport Channel Configuration
               Physical Channel Configuration      
               Security Channel Configuration
               UE Info Configuration   
          */
         expCfgBitMask = NHU_EXP_CFG_RB_CFG |
                         NHU_EXP_CFG_TRCH_CFG;

         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expCfgBitMask",
                        &expCfgBitMask);
#ifdef LTE_ADV
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "sCellAdd",
                        &sCellAdd);
         if(TRUE == sCellAdd)
         {
            expCfgBitMask = NHU_EXP_CFG_UESEC_CFG;

         }
#endif /* LTE_ADV */

         ueCfg->ueCfgBitMsk = expCfgBitMask;

         ret = nhAcUtlFillNhuUeCfgInfo(tcCb, spCb, &nhuDatReqEvntSdu->sdu.ueCfg,
                  nhuDatReqEvntSdu);
         if (ret != CMXTA_ERR_NONE)
         {
            CMXTA_FREEEVNT(nhuDatReqEvntSdu);
            RETVALUE(RFAILED);
         }
      }
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "invalidMsgCat",
                  &(invalidMsgCat));

      if (invalidMsgCat)
      {
         /* Put somw dummy value */
         nhuDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgCategory = 127;
      }

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
      if (nullSdu)
      {
         if (pst.selector == 1)
         {
            CMXTA_FREEEVNT(nhuDatReqEvntSdu);
            nhuDatReqEvntSdu = NULLP;
         }
         else
         {
            CMXTA_FREEEVNT(nhuDatReqEvntSdu);
            RETVALUE(CMXTA_ERR_NONE);
         }
      }

      nhAcUtlFillFailStatus(tcCb, spCb);

      /* Issue the primitive */
      if(CMXTA_ERR_NONE != NxLiNhuDatReq(&pst, spId, nhuDatReqEvntSdu))
      {
         CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuDatReq returned RFAILED\n"));
      }

      RETVALUE(CMXTA_ERR_NONE);
} /* nhAcHdlNhuDatReq */

/*
*
*       Fun:   nhAcHdlNhuDatInd
*
*       Desc:  NHU Dat Indication
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhuDatInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
      NhAccMsgQElm  *rrcMsg = NULLP;
      CmXtaMsgQElm  *msg = NULLP;
      Pst           pst;
      S16           ret = CMXTA_ERR_NONE;
      SuId          suId;
      ProcId        srcProcId;
      ProcId        dstProcId;
      U8            errType;
      U8            errCause;
      U16           ueId;
      U16           cellId;

      TRC2(nhAcHdlNhuDatInd)

   #ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDatInd(), tcId (%ld)\n", tcCb->tcId));
   #else
      CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDatInd(), tcId (%d)\n", tcCb->tcId));
   #endif

      cmMemset((U8*)&pst, 0 , sizeof(Pst));
      if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuDatInd(): cmXtaPeekMsg failed\n"));
         RETVALUE(CMXTA_ERR_FATAL);
      }
      srcProcId   =   CMXTA_DFLT_PROCID;
      dstProcId   =   CMXTA_DFLT_PROCID;
      rrcMsg     =   (NhAccMsgQElm *)msg->data;

   #ifdef SS_MULTIPLE_PROCS
      cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
   #endif

      /*-- Validate if this is the msg for this function --*/
      cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
               dstProcId,FALSE);

      pst.event = EVTNHUDATIND;
      ret = cmXtaValidatePst(&(msg->pst), &pst);

      if (ret != CMXTA_ERR_NONE)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuDatInd() : pst mismatch\n"));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      suId = 0;
      /*-- Set default value & validate for suId --*/
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

      /*-- Remove the msg from the Queue --*/
      cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

      /* Compare the value in the message and the value provided from xml */
      if (suId != rrcMsg->u.nhuInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                     suId, rrcMsg->u.nhuInfo.suId), 2);
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      ueId = 0;
      cellId = 0;
      cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
      cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
      if(ueId)
      {
         if(((NhuDatIndSdus *)((NhAccMsgQElm *)msg->data)->mBuf)->hdr.ueId != ueId)
         {
            CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuDatInd() : ueId mismatch\n"));
            cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
            RETVALUE(CMXTA_ERR_NOMATCH);
         }
      }

      if(((NhuDatIndSdus *)rrcMsg->mBuf)->err.errPres == PRSNT_NODEF)
      {
         errType = 0;
         errCause = 0;
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "errorType",
                        &(errType));
         if(errType)
         {
            if(((NhuDatIndSdus *)rrcMsg->mBuf)->err.errType != errType)
            {
               CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuDatInd() : errorType mismatch (expected) %d != %d (received)\n", errType,
                        ((NhuDatIndSdus *)rrcMsg->mBuf)->err.errType));
               cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
               RETVALUE(CMXTA_ERR_NOMATCH);
            }
         }
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "errorCause",
                        &(errCause));
         if(errCause)
         {
            if(((NhuDatIndSdus *)rrcMsg->mBuf)->err.errCause != errCause)
            {
               CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuDatInd() : errorCause mismatch (expected) %d != %d (received)\n", errCause,
                           ((NhuDatIndSdus *)rrcMsg->mBuf)->err.errCause));
               cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
               RETVALUE(CMXTA_ERR_NOMATCH);
            }
         }
      }

      /*-- free memory, use callback function --*/
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

      RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   nhAcHdlNhuDatRsp
*
*       Desc:  NHU Dat Response
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlNhuDatRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuDatRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   NhuDatRspSdus *nhuDatRspSdus = NULLP;
   ProcId        srcProcId;
   ProcId        dstProcId;
   Mem           sMem;
   U8            bitMask;
   U8            msgCategory;
   U8            rbId;
   U8            expCfgBitMask;
   NhuUeCfgInfo  *ueCfg;
   U8            msgType;
   S16           ret;
   U8            nullSdu = 0;
   U8            valChk = 1; /* TRUE */

   TRC2(nhAcHdlNhuDatRsp)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDatRsp(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDatRsp(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
               dstProcId,FALSE);

   /* allocate Data request event */
   sMem.region = 0;
   sMem.pool = 0;
   CMXTA_ALLOC_EVNT(&nhuDatRspSdus, sizeof(NhuDatRspSdus), &sMem, 
                                                              NHAC_MEM_PDU_SIZE);

   cmMemset((U8*)&nhAccCb.sndErrReq, 0 , sizeof(NhAcSndErrReq));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expMacErr",
                  &(nhAccCb.sndErrReq.expMacErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expRlcErr",
                  &(nhAccCb.sndErrReq.expRlcErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expPdcpErr",
                  &(nhAccCb.sndErrReq.expPdcpErr));
   /* Filling Event structure - Hdr,bitMask for identifying msg and
      Message type */

   /* Filling Header */
   nhAcUtlFillNhuEvntHdr(&tcCb, &spCb, &(nhuDatRspSdus->hdr));

   /* Filling Bit Mask Value to identify whether we need to fill
      Msg or UeCfg or Both */
   bitMask = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "bitMask",
                  &(bitMask));

   if(!bitMask)
      bitMask = 0; /* Fill Msg Only */

   if(bitMask)
      nhuDatRspSdus->sdu.isUeCfgPres = TRUE;
   else
      nhuDatRspSdus->sdu.isUeCfgPres = FALSE;
      
  /*Initialise validation check to FALSE by default*/
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8, "valChk", &(valChk));
   if (1 == valChk)
   {
      nhAccCb.valChk = TRUE;
   }
   else
   {
      nhAccCb.valChk = FALSE;
   }
 
   if(nhAccCb.valChk)
   {
    ret = nhAcUtlGetNxtValIdx();

    if(ret == RFAILED)
    {
      CMXTA_DBG_ERR((_cmxtap," No un-used slot available\n"));
      RETVALUE(RFAILED);
    }

    gCrgValStore[gValIdx].cellId = nhuDatRspSdus->hdr.cellId;
    gCrgValStore[gValIdx].ueId = nhuDatRspSdus->hdr.ueId;
 
    gCkwValStore[gValIdx].cellId = nhuDatRspSdus->hdr.cellId;
    gCkwValStore[gValIdx].ueId = nhuDatRspSdus->hdr.ueId;
    gCkwValStore[gValIdx].transId = nhuDatRspSdus->hdr.transId;

    gCpjCfgStore[gValIdx].cellId = nhuDatRspSdus->hdr.cellId;
    gCpjCfgStore[gValIdx].ueId = nhuDatRspSdus->hdr.ueId;
    gCpjCfgStore[gValIdx].transId = nhuDatRspSdus->hdr.transId;

#ifdef RRC_PHY_CFG_SUPP
    gCtfValStore[gValIdx].cellId = nhuDatRspSdus->hdr.cellId;
    gCtfValStore[gValIdx].ueId = nhuDatRspSdus->hdr.ueId;
    gCtfValStore[gValIdx].transId = nhuDatRspSdus->hdr.transId;
#endif /* RRC_PHY_CFG_SUPP */

  }     
   if((bitMask == 0) || (bitMask == 2))
   {
      /* Filling Message Type - DL CCCH */
      msgCategory = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,
                     "msgCategory", &(msgCategory));
      nhuDatRspSdus->sdu.msgCategory = msgCategory;

      switch(msgCategory)
      {
         case NHU_MSG_DLCCCH:
         {
            rbId = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                           "rbId", &(nhuDatRspSdus->sdu.m.dlCcchMsg.rbId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                           "tCrnti", &(nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti));

               gCrgValStore[gValIdx].tCrnti = nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti;
               gCkwValStore[gValIdx].tCrnti = nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti;
               gCpjCfgStore[gValIdx].tCrnti = nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti;
#ifdef RRC_PHY_CFG_SUPP
               gCtfValStore[gValIdx].tCrnti = nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti;
#endif
#ifdef TENB_MULT_CELL_SUPPRT
         nhAcUtlFillUeSapCfg(tcCb, spCb, nhuDatRspSdus->hdr.cellId, &(nhuDatRspSdus->sdu.ueCfg.uellyrSapIdInfo));
#endif

            /* DL-CCCH Msgs - Connection Setup, Connection Reject, 
                              Connection Re-establishment Reject */
            msgType = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,
                           CMXTA_ATTRIB_U8, "msgType",
                           &(msgType));
            FILL_UINT_TKN(nhuDatRspSdus->sdu.m.dlDcchMsg.m.dcchMsg.message.val.c1.choice,
                          msgType);

            switch(msgType)
            {
               case C1_RRCCONSETUP:
               {
                   nhAcUtlFillNhuDlCcchConSetup(tcCb, spCb,
                                                nhuDatRspSdus);

                  break;
               }
               case C1_RRCCONREJ:
                  nhAcUtlFillNhuDlCcchConRej(tcCb, spCb, nhuDatRspSdus);
                  break;
               case C1_RRCCONREESTBREJ:
                  nhAcUtlFillNhuDlCcchConReestbRej(tcCb, spCb, nhuDatRspSdus);
                  break;
               case C1_RRCCONREESTB:
                  nhAcUtlFillNhuDlCcchConReestb(tcCb, spCb, nhuDatRspSdus);
                  break;
            }
         }
         break;
         case NHU_MSG_DLDCCH:
         {
            rbId = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                           "rbId", &(nhuDatRspSdus->sdu.m.dlDcchMsg.pdcpId));

            /* DL-DCCH Msgs -  CSFB CDMA2000 Parameters Response */
            msgType = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,
                           CMXTA_ATTRIB_U8, "msgType",
                           &(msgType));
            FILL_UINT_TKN(nhuDatRspSdus->sdu.m.dlDcchMsg.m.dcchMsg.message.val.c1.choice,
                          msgType);
            switch(msgType)
            {
               case C1_CSFBPARAMSRSPCDMA2000:
                  nhAcUtlFillNhuDlDcchCDMACsfbPrmRsp(tcCb, spCb, nhuDatRspSdus);
                  break;
            }
         }
         break;
         default:
            CMXTA_DBG_ERR((_cmxtap," Wrong Msg Type\n"));
            break;
      }
   }


  if((bitMask == 1) || (bitMask == 2))
  {
      ueCfg = &(nhuDatRspSdus->sdu.ueCfg);

      expCfgBitMask = NHU_EXP_CFG_RB_CFG |
                      NHU_EXP_CFG_TRCH_CFG; 
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expCfgBitMask",
                     &expCfgBitMask);
      ueCfg->ueCfgBitMsk = expCfgBitMask;
      nhAcUtlFillNhuUeCfgInfo(tcCb, spCb, ueCfg, nhuDatRspSdus);
  }

   spId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREEEVNT(nhuDatRspSdus);
         nhuDatRspSdus = NULLP;
      }
      else
      {
         CMXTA_FREEEVNT(nhuDatRspSdus);
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   nhAcUtlFillFailStatus(tcCb, spCb);

   if(CMXTA_ERR_NONE != NxLiNhuDatRsp(&pst, spId, nhuDatRspSdus))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuDatRsp returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nhAcHdlMcellNhuDatRsp
*
*       Desc:  NHU Dat Response
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlMcellNhuDatRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlMcellNhuDatRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   NhuDatRspSdus *nhuDatRspSdus = NULLP;
   ProcId        srcProcId;
   ProcId        dstProcId;
   Mem           sMem;
   U8            bitMask;
   U8            msgCategory;
   U8            rbId;
   U8            expCfgBitMask;
   NhuUeCfgInfo  *ueCfg;
   U8            msgType;
   S16           ret;
   U8            nullSdu = 0;
   U8            valChk = 1; /* TRUE */

   TRC2(nhAcHdlNhuDatRsp)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlMcellNhuDatRsp(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlMcellNhuDatRsp(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
               dstProcId,FALSE);

   /* allocate Data request event */
   sMem.region = 0;
   sMem.pool = 0;
   CMXTA_ALLOC_EVNT(&nhuDatRspSdus, sizeof(NhuDatRspSdus), &sMem, 
                                                              NHAC_MEM_PDU_SIZE);

   cmMemset((U8*)&nhAccCb.sndErrReq, 0 , sizeof(NhAcSndErrReq));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expMacErr",
                  &(nhAccCb.sndErrReq.expMacErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expRlcErr",
                  &(nhAccCb.sndErrReq.expRlcErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expPdcpErr",
                  &(nhAccCb.sndErrReq.expPdcpErr));
   /* Filling Event structure - Hdr,bitMask for identifying msg and
      Message type */

   /* Filling Header */
   nhAcUtlFillNhuEvntHdr(&tcCb, &spCb, &(nhuDatRspSdus->hdr));

   /* Filling Bit Mask Value to identify whether we need to fill
      Msg or UeCfg or Both */
   bitMask = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "bitMask",
                  &(bitMask));

   if(!bitMask)
      bitMask = 0; /* Fill Msg Only */

   if(bitMask)
      nhuDatRspSdus->sdu.isUeCfgPres = TRUE;
   else
      nhuDatRspSdus->sdu.isUeCfgPres = FALSE;
      
  /*Initialise validation check to FALSE by default*/
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8, "valChk", &(valChk));
   if (1 == valChk)
   {
      nhAccCb.valChk = TRUE;
   }
   else
   {
      nhAccCb.valChk = FALSE;
   }
 
   if(nhAccCb.valChk)
   {
    ret = nhAcUtlGetNxtValIdx();

    if(ret == RFAILED)
    {
      CMXTA_DBG_ERR((_cmxtap," No un-used slot available\n"));
      RETVALUE(RFAILED);
    }

    gCrgValStore[gValIdx].cellId = nhuDatRspSdus->hdr.cellId;
    gCrgValStore[gValIdx].ueId = nhuDatRspSdus->hdr.ueId;
 
    gCkwValStore[gValIdx].cellId = nhuDatRspSdus->hdr.cellId;
    gCkwValStore[gValIdx].ueId = nhuDatRspSdus->hdr.ueId;
    gCkwValStore[gValIdx].transId = nhuDatRspSdus->hdr.transId;

    gCpjCfgStore[gValIdx].cellId = nhuDatRspSdus->hdr.cellId;
    gCpjCfgStore[gValIdx].ueId = nhuDatRspSdus->hdr.ueId;
    gCpjCfgStore[gValIdx].transId = nhuDatRspSdus->hdr.transId;

#ifdef RRC_PHY_CFG_SUPP
    gCtfValStore[gValIdx].cellId = nhuDatRspSdus->hdr.cellId;
    gCtfValStore[gValIdx].ueId = nhuDatRspSdus->hdr.ueId;
    gCtfValStore[gValIdx].transId = nhuDatRspSdus->hdr.transId;
#endif /* RRC_PHY_CFG_SUPP */
#ifdef TENB_MULT_CELL_SUPPRT
         nhAcUtlFillUeMsapCfg(tcCb,spCb,&(nhuDatRspSdus->sdu.ueCfg.uellyrSapIdInfo));
#endif

  }     
   if((bitMask == 0) || (bitMask == 2))
   {
      /* Filling Message Type - DL CCCH */
      msgCategory = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,
                     "msgCategory", &(msgCategory));
      nhuDatRspSdus->sdu.msgCategory = msgCategory;

      switch(msgCategory)
      {
         case NHU_MSG_DLCCCH:
         {
            rbId = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                           "rbId", &(nhuDatRspSdus->sdu.m.dlCcchMsg.rbId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                           "tCrnti", &(nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti));

               gCrgValStore[gValIdx].tCrnti = nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti;
               gCkwValStore[gValIdx].tCrnti = nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti;
               gCpjCfgStore[gValIdx].tCrnti = nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti;
#ifdef RRC_PHY_CFG_SUPP
               gCtfValStore[gValIdx].tCrnti = nhuDatRspSdus->sdu.m.dlCcchMsg.tmpCrnti;
#endif

            /* DL-CCCH Msgs - Connection Setup, Connection Reject, 
                              Connection Re-establishment Reject */
            msgType = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,
                           CMXTA_ATTRIB_U8, "msgType",
                           &(msgType));
            FILL_UINT_TKN(nhuDatRspSdus->sdu.m.dlDcchMsg.m.dcchMsg.message.val.c1.choice,
                          msgType);

            switch(msgType)
            {
               case C1_RRCCONSETUP:
               {
                   nhAcUtlFillNhuDlCcchConSetup(tcCb, spCb,
                                                nhuDatRspSdus);

                  break;
               }
               case C1_RRCCONREJ:
                  nhAcUtlFillNhuDlCcchConRej(tcCb, spCb, nhuDatRspSdus);
                  break;
               case C1_RRCCONREESTBREJ:
                  nhAcUtlFillNhuDlCcchConReestbRej(tcCb, spCb, nhuDatRspSdus);
                  break;
               case C1_RRCCONREESTB:
                  nhAcUtlFillNhuDlCcchConReestb(tcCb, spCb, nhuDatRspSdus);
                  break;
            }
         }
         break;
         case NHU_MSG_DLDCCH:
         {
            rbId = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                           "rbId", &(nhuDatRspSdus->sdu.m.dlDcchMsg.pdcpId));

            /* DL-DCCH Msgs -  CSFB CDMA2000 Parameters Response */
            msgType = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,
                           CMXTA_ATTRIB_U8, "msgType",
                           &(msgType));
            FILL_UINT_TKN(nhuDatRspSdus->sdu.m.dlDcchMsg.m.dcchMsg.message.val.c1.choice,
                          msgType);
            switch(msgType)
            {
               case C1_CSFBPARAMSRSPCDMA2000:
                  nhAcUtlFillNhuDlDcchCDMACsfbPrmRsp(tcCb, spCb, nhuDatRspSdus);
                  break;
            }
         }
         break;
         default:
            CMXTA_DBG_ERR((_cmxtap," Wrong Msg Type\n"));
            break;
      }
   }


  if((bitMask == 1) || (bitMask == 2))
  {
      ueCfg = &(nhuDatRspSdus->sdu.ueCfg);

      expCfgBitMask = NHU_EXP_CFG_RB_CFG |
                      NHU_EXP_CFG_TRCH_CFG; 
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expCfgBitMask",
                     &expCfgBitMask);
      ueCfg->ueCfgBitMsk = expCfgBitMask;
      nhAcUtlFillNhuUeCfgInfo(tcCb, spCb, ueCfg, nhuDatRspSdus);
  }

   spId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREEEVNT(nhuDatRspSdus);
         nhuDatRspSdus = NULLP;
      }
      else
      {
         CMXTA_FREEEVNT(nhuDatRspSdus);
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   nhAcUtlFillFailStatus(tcCb, spCb);

   if(CMXTA_ERR_NONE != NxLiNhuDatRsp(&pst, spId, nhuDatRspSdus))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuDatRsp returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   nhAcHdlNhuCfgReq
*
*       Desc:  General Config Request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst              pst;
   SuId             spId;
   ProcId           srcProcId;
   ProcId           dstProcId;
   Mem              sMem;
   U8               expCfgBitMask;
   NhuCfgReqSdus    *nhuCfgReqSdus = NULLP;
   NhuUeCfgInfo     *ueCfg = NULLP;
   U8                nullSdu = 0;
   U8                valChk = 0; /* FALSE */

   /* Initial structs to zero */
   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   sMem.region = 0;
   sMem.pool = 0;

   TRC2(nhAcHdlNhuCfgReq)

   CMXTA_ALLOC_EVNT(&nhuCfgReqSdus, sizeof(NhuCfgReqSdus), &sMem,
                                                           NHAC_MEM_PDU_SIZE);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
               dstProcId,FALSE);

  /*Initialise validation check to FALSE by default*/
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8, "valChk", &(valChk));
   if (1 == valChk)
   {
      nhAccCb.valChk = TRUE;
   }
   else
   {
      nhAccCb.valChk = FALSE;
   }

   /* Filling Header */
   nhAcUtlFillNhuEvntHdr(&tcCb, &spCb, &(nhuCfgReqSdus->hdr));

   ueCfg = &(nhuCfgReqSdus->cfgInfo);

   expCfgBitMask = NHU_EXP_CFG_RB_CFG |
                   NHU_EXP_CFG_TRCH_CFG |
                   NHU_EXP_CFG_SEC_CFG |
                   NHU_EXP_CFG_UE_CFG;

#ifdef RRC_PHY_CFG_SUPP
   expCfgBitMask |= NHU_EXP_CFG_PHY_CFG;
#endif /* RRC_PHY_CFG_SUPP */

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expCfgBitMask",
                  &expCfgBitMask);
   ueCfg->ueCfgBitMsk = expCfgBitMask;

   /* UE Configuration Inforamtion :
         RB Configuration - ADD/MODIFY/RELEASE 
         Transport Channel Configuration
         Physical Channel Configuration      
         Security Channel Configuration
         UE Info Configuration   */
       
   nhAcUtlFillNhuUeCfgInfo(tcCb, spCb, ueCfg, nhuCfgReqSdus);

   spId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));


   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",
                                                            &nullSdu);
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREEEVNT(nhuCfgReqSdus);
         nhuCfgReqSdus = NULLP;
      }
      else
      {
         CMXTA_FREEEVNT(nhuCfgReqSdus);
         RETVALUE(CMXTA_ERR_NONE);
      }
   }
   nhAcUtlFillFailStatus(tcCb, spCb);

   if(CMXTA_ERR_NONE != NxLiNhuCfgReq(&pst, spId, nhuCfgReqSdus))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuCfgReq returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* nhAcHdlNhuCfgReq */

/*
*
*       Fun:   nhAcHdlNhuCfgCfm
*
*       Desc:  General Config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   Bool          status;
   U8            errType;
   U8            errCause;

   TRC2(nhAcHdlNhuCfgCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
               dstProcId,FALSE);

   pst.event = EVTNHUCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuCfgCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Set default value & validate for suId --*/
   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
   rrcMsg = (NhAccMsgQElm *)msg->data;   

   /* Compare the value in the message and the value provided from xml */
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rrcMsg->u.nhuInfo.suId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   status = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "status",  &(status));
   if(status)
   {
      if(((NhuCfgCfmSdus *)rrcMsg->mBuf)->sdu.isCfgSuccess != status)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuCfgCfm() : Config status mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_NOMATCH);
      }
   }

   if(((NhuCfgCfmSdus *)rrcMsg->mBuf)->sdu.cfgError.errPres == PRSNT_NODEF)
   {
      errType = 0;
      errCause = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "errType",
                  &(errType));
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "errCause",
                     &(errCause));
      if(errType)
      {
         if(((NhuCfgCfmSdus *)rrcMsg->mBuf)->sdu.cfgError.errType != errType)
         {
            CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuCfgCfm() : errType mismatch\n"));
            cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
            RETVALUE(CMXTA_ERR_NOMATCH);
         }
      }
      if(errCause)
      {
         if(((NhuCfgCfmSdus *)rrcMsg->mBuf)->sdu.cfgError.errCause != errCause)
         {
            CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuCfgCfm() :errCause mismatch\n"));
            cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
            RETVALUE(CMXTA_ERR_NOMATCH);
         }
      }
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* nhAcHdlNhuCfgCfm */

/*
*
*       Fun:   nhAcHdlNhuCancelUeReq
*
*       Desc:  Cancel UE Req
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuCnclUeReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuCnclUeReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   NhuCrnti      ueId;
   NhuCellId     cellId;

   TRC2(nhAcHdlNhuCnclUeReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCnclUeReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCnclUeReq(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
               dstProcId,FALSE);

   spId = 0;
   ueId = 0;
   cellId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   if(CMXTA_ERR_NONE != NxLiNhuCnclUeReq(&pst, spId, cellId, ueId))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuCnclUeReq() : returned RFAILED\n"));
   }

    RETVALUE(CMXTA_ERR_NONE);

} /* nhAcHdlNhuCnclUeReq */

/*
*
*       Fun:   nhAcHdlNhuCellCfgReq
*
*       Desc:  Cancel UE Req
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuCellCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuCellCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst               pst;
   SpId              spId;
   Mem               sMem;
   ProcId            srcProcId;
   ProcId            dstProcId;
   NhuCellCfgReqSdus *nhuCellCfgReqSdus = NULLP;
   NhuRbCfgList      *rbCfgList = NULLP;
   U8               numCellRb;
   U8               nullSdu = 0;
   U8               duplexMode = 1; /* NHU_MODE_FDD */

   TRC2(nhAcHdlNhuCellCfgReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCellCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCellCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   sMem.region = 0;
   sMem.pool = 0;

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   CMXTA_ALLOC_EVNT(&nhuCellCfgReqSdus, sizeof(NhuCellCfgReqSdus), &sMem, 
                                                   NHAC_MEM_PDU_SIZE);

   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
               dstProcId,FALSE);

   pst.event   = EVTNHUCELLCFGREQ;

  /*Initialise validation check to FALSE by default*/
   nhAccCb.valChk = FALSE;
   cmMemset((U8*)&nhAccCb.sndErrReq, 0 , sizeof(NhAcSndErrReq));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expMacErr",
                  &(nhAccCb.sndErrReq.expMacErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expRlcErr",
                  &(nhAccCb.sndErrReq.expRlcErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expPdcpErr",
                  &(nhAccCb.sndErrReq.expPdcpErr));
   
   /* Filling Header */
   nhAcUtlFillNhuEvntHdr(&tcCb, &spCb, &(nhuCellCfgReqSdus->hdr));

   /* Cell Cfg Type -- ADD/MODIFY/RLS */
   nhuCellCfgReqSdus->sdu.cfgType = NHU_ACTION_ADD;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cellCfgType",
                  &(nhuCellCfgReqSdus->sdu.cfgType));

   /* nh002.201 - reconfig corrected */
   if (nhuCellCfgReqSdus->sdu.cfgType == NHU_ACTION_ADD)
   {
      /* Duplex Mode - FDD or TDD */
      nhuCellCfgReqSdus->sdu.u.cfgInfo.duplexMode    = NHU_MODE_FDD;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "duplexMode", 
                        &(duplexMode));
      nhuCellCfgReqSdus->sdu.u.cfgInfo.duplexMode = (NhuDuplexMode)duplexMode;

      /* nh002.201: changes due to structure modification */
      nhuCellCfgReqSdus->sdu.u.cfgInfo.sysBwCfg.dlSysBw = NHU_SYS_BW_N50;
      nhuCellCfgReqSdus->sdu.u.cfgInfo.sysBwCfg.ulSysBw = NHU_SYS_BW_N75;

      /* cellCfgBitMask - to indicate presence of Cell Config Info */
      nhuCellCfgReqSdus->sdu.u.cfgInfo.cellCfgBitMsk    = NHU_CELL_CFG_RB;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cellCfgBitMask",
                     &(nhuCellCfgReqSdus->sdu.u.cfgInfo.cellCfgBitMsk));

      /* Fill RB Configuration */
      if(nhuCellCfgReqSdus->sdu.u.cfgInfo.cellCfgBitMsk & NHU_CELL_CFG_RB &&
         nhuCellCfgReqSdus->sdu.cfgType == NHU_CFGTYPE_SETUP)
      {
         numCellRb = 6;
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"numCellRb",
                        &(numCellRb));

         rbCfgList = &(nhuCellCfgReqSdus->sdu.u.cfgInfo.rbToAddCfgList);
         rbCfgList->numOfRbCfgInfo = numCellRb;
         CMXTA_GET_MEM(nhuCellCfgReqSdus, sizeof(NhuRbCfgInfo)*numCellRb,
                       &(rbCfgList->rbCfgInfoList));
         nhAcUtlFillCellRbCfg(tcCb,spCb,&rbCfgList);
      }

      /* Fill RACH Configuration */
      if(nhuCellCfgReqSdus->sdu.u.cfgInfo.cellCfgBitMsk & NHU_CELL_CFG_MAC_CMN)
      {
         nhAcUtlFillRachCfg(tcCb,spCb,&(nhuCellCfgReqSdus->sdu.u.cfgInfo.macCmnCfg.rachCfg));
      }

#ifdef RRC_PHY_CFG_SUPP
      /* Fill Physical layer common configuration */
      if(nhuCellCfgReqSdus->sdu.u.cfgInfo.cellCfgBitMsk & NHU_CELL_PHY_CFG)
      {
         nhAcUtlFillCmnPhyAddCfg(tcCb,spCb,&(nhuCellCfgReqSdus->sdu.u.cfgInfo.phyCellCfg));
      }
#endif

      /* MSAP config info */
#ifdef TENB_MULT_CELL_SUPPRT
      if(nhuCellCfgReqSdus->sdu.u.cfgInfo.cellCfgBitMsk & NHU_CELL_CFG_MSAP)
      {
         nhAcUtlFillMsapCfg(tcCb,spCb,&(nhuCellCfgReqSdus->sdu.u.cfgInfo.llyrSapIdInfo));
      }
      else
      {
         if (nhuCellCfgReqSdus->sdu.cfgType == NHU_CFGTYPE_SETUP)
         {
            nhuCellCfgReqSdus->sdu.u.cfgInfo.cellCfgBitMsk |= NHU_CELL_CFG_MSAP;
            nhAcUtlFillMsapCfg(tcCb,spCb,&(nhuCellCfgReqSdus->sdu.u.cfgInfo.llyrSapIdInfo));
         }
      }
#endif
   }
   if (nhuCellCfgReqSdus->sdu.cfgType == NHU_ACTION_MODIFY)
   {
      /* cellCfgBitMask - to indicate presence of Cell Config Info */
      nhuCellCfgReqSdus->sdu.u.reCfgInfo.cellCfgBitMsk    = NHU_CELL_CFG_MAC_CMN;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cellCfgBitMask",
                     &(nhuCellCfgReqSdus->sdu.u.reCfgInfo.cellCfgBitMsk));
      
      /* Fill RACH Configuration */
      if(nhuCellCfgReqSdus->sdu.u.reCfgInfo.cellCfgBitMsk & NHU_CELL_CFG_MAC_CMN)
      {
         nhAcUtlFillRachCfg(tcCb,spCb,&(nhuCellCfgReqSdus->sdu.u.reCfgInfo.macCmnCfg.rachCfg));
      }

#ifdef RRC_PHY_CFG_SUPP
      /* Fill Physical layer common configuration */
      if(nhuCellCfgReqSdus->sdu.u.reCfgInfo.cellCfgBitMsk & NHU_CELL_PHY_CFG)
      {
         nhAcUtlFillCmnPhyModCfg(tcCb,spCb,&(nhuCellCfgReqSdus->sdu.u.reCfgInfo.phyCellCfg));
      }
#endif
   }

   spId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",
                                                            &nullSdu);
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREEEVNT(nhuCellCfgReqSdus);
         nhuCellCfgReqSdus = NULLP;
      }
      else
      {
         CMXTA_FREEEVNT(nhuCellCfgReqSdus);
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   nhAcUtlFillFailStatus(tcCb, spCb);

   if(CMXTA_ERR_NONE != NxLiNhuCellCfgReq(&pst, spId, nhuCellCfgReqSdus))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuCellCfgReq returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* nhAcHdlNhuCellCfgReq */

/*
*
*       Fun:   nhAcHdlNhuCellCfgCfm
*
*       Desc:  Cancel UE Req
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuCellCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuCellCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   SuId          suId;
   U8            errType;
   U8            errCause;
   Bool          status;

   TRC2(nhAcHdlNhuCellCfgCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCellCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCellCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuCellCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
    rrcMsg = (NhAccMsgQElm *)msg->data;   
   suId = 0;
   /* Compare the value in the message and the value provided from xml */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rrcMsg->u.nhuInfo.suId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   status = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "status",  &(status));
   if(status)
   {
      if(((NhuCellCfgCfmSdus *)rrcMsg->mBuf)->sdu.isCfgSuccess != status)
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuCellCfgCfm() : status mismatch\n"));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }
   }

   if(((NhuCellCfgCfmSdus *)rrcMsg->mBuf) && ((NhuCellCfgCfmSdus *)rrcMsg->mBuf)->sdu.cfgError.errPres == PRSNT_NODEF)
   {
      errType = 0;
      errCause = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "errType", &(errType));
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "errCause",
                     &(errCause));
      if(errType)
      {
         if(((NhuCellCfgCfmSdus *)rrcMsg->mBuf)->sdu.cfgError.errType != errType)
         {
            CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuCellCfgCfm() : errType mismatch\n"));
            RETVALUE(CMXTA_ERR_NOMATCH);
         }
      }
      if(errCause)
      {
         if(((NhuCellCfgCfmSdus *)rrcMsg->mBuf)->sdu.cfgError.errCause != errCause)
         {
            CMXTA_DBG_ERR((_cmxtap, "nhAcHdlNhuCellCfgCfm() :errCause mismatch\n"));
            RETVALUE(CMXTA_ERR_NOMATCH);
         }
      }
   }
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* nhAcHdlNhuCellCfgCfm */

/*
*
*       Fun:   nhAcHdlNhuDeleteTransReq
*
*       Desc:  Delete Transaction Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuDeleteTransReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuDeleteTransReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U32           transId;
   U16           ueId;
   U16           cellId;
   Mem           sMem;

   sMem.region = 0;
   sMem.pool = 0;

   TRC2(nhAcHdlNhuDeleteTransReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDeleteTransReq(), tcId (%ld)\n",
                  tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDeleteTransReq(), tcId (%d)\n",
                  tcCb->tcId));
#endif

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif


   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event   = EVTNHUDELETETRANSREQ;

   spId = 0;
   ueId = 0;
   cellId = 0;
   transId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));

   if (CMXTA_ERR_NONE != NxLiNhuDeleteTransReq(&pst, spId,  cellId, ueId, transId))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuDeleteTransReq() : returned RFAILED\n"));
   }
   RETVALUE(CMXTA_ERR_NONE);

} /* nhAcHdlNhuDeleteTransReq */

/*
*
*       Fun:   nhAcHdlNhuPdcpSduStaReq
*
*       Desc:  PDCP SDU Status request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuPdcpSduStaReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuPdcpSduStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U32           transId;
   U16           ueId;
   U16           cellId;
   Mem           sMem;
   NhuHdr        hdr;

   sMem.region = 0;
   sMem.pool = 0;

   TRC2(nhAcHdlNhuPdcpSduStaReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuPdcpSduStaReq(), tcId (%ld)\n",
                  tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuPdcpSduStaReq(), tcId (%d)\n",
                  tcCb->tcId));
#endif

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif


   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event   = EVTNHUPDCPSDUSTAREQ;

   spId = 0;
   ueId = 0;
   cellId = 0;
   transId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
   hdr.cellId = cellId;
   hdr.ueId = ueId;
   hdr.transId = transId;

   if (CMXTA_ERR_NONE != NxLiNhuPdcpSduStaReq(&pst, spId, hdr))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuPdcpSduStaReq() : returned RFAILED\n"));
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuPdcpSduStaReq */

/*
*
*       Fun:   nhAcHdlNhuPdcpSduStaCfm
*
*       Desc:  PDCP SDU Status confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuPdcpSduStaCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuPdcpSduStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NhAccMsgQElm  *rrcMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   Status        status;
   U8            numDrb;

   TRC2(nhAcHdlNhuPdcpSduStaCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuPdcpSduStaCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuPdcpSduStaCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuPdcpSduStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rrcMsg = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Get the Pst information here from RRC User to RRC Layer --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event = EVTNHUPDCPSDUSTACFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for suId --*/
   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) recvd (%d) \n",
               suId, rrcMsg->u.nhuInfo.suId),2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   status = 0;
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "numDrbs",  &(numDrb));
   /* if the numDrbs value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuPdcpSduStaCfm(): numDrbs not provided from xml\n"));
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Compare the value in the message and the value provided from xml */
   if (numDrb != ((NhuPdcpSduStaCfm *)rrcMsg->mBuf)->numRbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : numDrb MisMatch: exp (%d) rcvd (%d) \n",
                  status, ((NhuPdcpSduStaCfm *)rrcMsg->mBuf)->numRbId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   status = 0;
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "sduStatus",  &(status));
   /* if the status value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuPdcpSduStaCfm(): sduStatus not provided from xml\n"));
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Compare the value in the message and the value provided from xml */
   if (status != ((NhuPdcpSduStaCfm *)rrcMsg->mBuf)->status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : sduStatus MisMatch: exp (%d) rcvd (%d) \n",
                  status, ((NhuPdcpSduStaCfm *)rrcMsg->mBuf)->status), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuPdcpSduStaCfm */

/*
*
*       Fun:   nhAcHdlNhuCountReq
*
*       Desc:  Count Request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuCountReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuCountReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U32           transId;
   U16           ueId;
   U16           cellId;
   Mem           sMem;
   NhuHdr        *cntHdr;
   U8            nullSdu = 0;

   sMem.region = 0;
   sMem.pool = 0;

   TRC2(nhAcHdlNhuCountReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCountReq(), tcId (%ld)\n",
                  tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCountReq(), tcId (%d)\n",
                  tcCb->tcId));
#endif

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif


   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event   = EVTNHUCOUNTREQ;

   spId = 0;
   ueId = 0;
   cellId = 0;
   transId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));


   CMXTA_ALLOC(&cntHdr, sizeof(NhuHdr));

   cntHdr->cellId = cellId;
   cntHdr->ueId = ueId;
   cntHdr->transId = transId;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(cntHdr, sizeof(NhuHdr));
         cntHdr = NULLP;
      }
      else
      {
         CMXTA_FREE(cntHdr, sizeof(NhuHdr));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   if (CMXTA_ERR_NONE != NxLiNhuCountReq(&pst, spId, cntHdr))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuCountReq() : returned RFAILED\n"));
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuCountReq */

/*
*
*       Fun:   nhAcHdlNhuCountCfm
*
*       Desc:  PDCP SDU Status confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuCountCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuCountCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NhAccMsgQElm  *rrcMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            numDrbCnt;
   Txt           msgStr[100];
   Txt           frstWrd[3];
   U16           drb[32];
   U16           rbVal;
   U16           len;
   U8            rbCnt;
   U8            rbId;
   S16           i;
   Bool          found = FALSE;

   TRC2(nhAcHdlNhuCountCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCountCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuCountCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuCountCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rrcMsg = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Get the Pst information here from RRC User to RRC Layer --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event = EVTNHUCOUNTCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for suId --*/
   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) recvd (%d) \n",
               suId, rrcMsg->u.nhuInfo.suId),2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "drbIdStr", msgStr);
   len = 0;
   numDrbCnt = 0;
   while(len < strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      drb[numDrbCnt] = rbVal;
      numDrbCnt++;
   }

   /* Compare the value in the message and the value provided from xml */
   if (numDrbCnt != ((NhuDRBCountInfoLst *)rrcMsg->mBuf)->numDrbs)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : numDrbs MisMatch: exp (%d) rcvd (%d) \n",
                  numDrbCnt, ((NhuDRBCountInfoLst *)rrcMsg->mBuf)->numDrbs), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   rbCnt = 0;
   while(rbCnt < ((NhuDRBCountInfoLst *)rrcMsg->mBuf)->numDrbs)
   {
      rbId = ((NhuDRBCountInfoLst *)rrcMsg->mBuf)->member[rbCnt].drbId;
      found = FALSE;
      for(i = 0; i < ((NhuDRBCountInfoLst *)rrcMsg->mBuf)->numDrbs; i++)
      {
         if(drb[i] == rbId)
         {
            found = TRUE;
            break;
         }
      }
      if(found == FALSE)
      {
         CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuCountCfm() : rbId String mismatch\n"));
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
      rbCnt++;
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuCountCfm */

/*
*
*       Fun:   nhAcHdlNhuEncodeReq
*
*       Desc:  Encode request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuEncodeReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuEncodeReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U32           transId;
   U16           ueId;
   U16           cellId;
   Mem           sMem;
   NhuEncReqSdus *nhuEncReqSdus;
   U8            msgType;
#ifdef RRC_REL11
   U8            msgCategory=0;
#endif
   S16           ret = ROK;
   U8            nullSdu= 0;

   sMem.region = 0;
   sMem.pool = 0;

   TRC2(nhAcHdlNhuEncodeReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuEncodeReq(), tcId (%ld)\n",
                  tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuEncodeReq(), tcId (%d)\n",
                  tcCb->tcId));
#endif

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event   = EVTNHUENCODEREQ;

   spId = 0;
   ueId = 0;
   cellId = 0;
   transId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &nullSdu);
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         NxLiNhuEncodeReq(&pst, spId, NULLP);
         RETVALUE(CMXTA_ERR_NONE);
      }
      else
      {
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   CMXTA_ALLOC_EVNT(&nhuEncReqSdus, sizeof(NhuEncReqSdus), &sMem, 
                                                   NHAC_MEM_PDU_SIZE);
   nhuEncReqSdus->hdr.cellId = cellId;
   nhuEncReqSdus->hdr.ueId = ueId;
   nhuEncReqSdus->hdr.transId = transId;

   msgType = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "msgType",  &(msgType));
   nhuEncReqSdus->sdu.msgCategory = msgType;
   switch(msgType)
   {
      case NHU_MSG_DLDCCH:
#ifdef RRC_REL11
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "msgCategory",
               &(msgCategory));
         if(msgCategory == C1_RNRECFGN_R10__1)
         {
           ret = nhAcUtlFillNhuRNRecfgn_r10(tcCb, spCb, (Ptr)nhuEncReqSdus, 
                                            &nhuEncReqSdus->sdu.u.dcchMsg);
         }
         else if(msgCategory == C1_LOGGEDMEASUREMENTCFG_R10__1)
         {
           ret = nhAcUtlFillNhuLoggedMeasurementCfg_r10(tcCb, spCb, (Ptr)nhuEncReqSdus, 
                                            &nhuEncReqSdus->sdu.u.dcchMsg);
         }
         else
         {
           ret = nhAcUtlFillNhuRrcConReCfgnHo(tcCb, spCb, (Ptr)nhuEncReqSdus, 
                                            &nhuEncReqSdus->sdu.u.dcchMsg);
         }

#else
         ret = nhAcUtlFillNhuRrcConReCfgnHo(tcCb, spCb, (Ptr)nhuEncReqSdus, 
                                            &nhuEncReqSdus->sdu.u.dcchMsg);
#endif
      break;

      case NHU_MSG_HOCMD:
         ret = nhAcUtlFillNhuHoCmd(tcCb, spCb, (Ptr)nhuEncReqSdus, 
                                   &nhuEncReqSdus->sdu.u.hovrCmd);
      break;

      case NHU_MSG_UERACAPINFO:
         ret = nhAcUtlFillNhuUeRadAccessCapInfo(tcCb, spCb, (Ptr)nhuEncReqSdus, 
                                                &nhuEncReqSdus->sdu.u.ueRadioCapInfo);
      break;

      case NHU_MSG_UECAPINFO:
         ret = nhAcUtlFillNhuUeCapInfo(tcCb, spCb, (Ptr)nhuEncReqSdus,
                                       &nhuEncReqSdus->sdu.u.ueCapInfo);
      break;

      case NHU_MSG_HOPREPINFO:
         ret = nhAcUtlFillNhuHoPrepInfo(tcCb, spCb, (Ptr)nhuEncReqSdus, 
                                        &nhuEncReqSdus->sdu.u.hovrPrepInfo);
      break;

#ifdef NHU_VER2
      case NHU_MSG_VARSHORTMACI:
         ret = nhAcUtlFillNhuVarShortMACInput(tcCb, spCb, (Ptr)nhuEncReqSdus, 
                                        &nhuEncReqSdus->sdu.u.varShortMacInput);
      break;
#endif/*LTERRC_REL9*/   

      default:
         CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuEncodeReq() invalid msgType :\
                         returned RFAILED\n"));
      break;
   }

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_FREEEVNT(nhuEncReqSdus);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (CMXTA_ERR_NONE != NxLiNhuEncodeReq(&pst, spId, nhuEncReqSdus))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuEncodeReq() : returned RFAILED\n"));
      CMXTA_FREEEVNT(nhuEncReqSdus);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuEncodeReq */

/*
*
*       Fun:   nhAcHdlNhuEncodeCfm
*
*       Desc:  Encode confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuEncodeCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuEncodeCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NhAccMsgQElm  *rrcMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            encMsgType;
   Bool          storeEncMsg;
   U8            status;

   TRC2(nhAcHdlNhuEncodeCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuEncodeCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuEncodeCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuEncodeCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rrcMsg = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Get the Pst information here from RRC User to RRC Layer --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event = EVTNHUENCODECFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for suId --*/
   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) recvd (%d) \n",
               suId, rrcMsg->u.nhuInfo.suId),2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "encMsgType",  &(encMsgType));
   /* if the encMsgType value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuEncodeCfm(): encMsgType not provided from xml\n"));
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Compare the value in the message and the value provided from xml */
   if (encMsgType != ((NhuEncCfmSdus *)rrcMsg->mBuf)->sdu.msgCategory)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : encode message type MisMatch: exp (%d) rcvd (%d) \n",
                  encMsgType, ((NhuEncCfmSdus *)rrcMsg->mBuf)->sdu.msgCategory), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));
   /* if the status value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuEncodeCfm(): encode status not provided from xml\n"));
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Compare the value in the message and the value provided from xml */
   if (status != ((NhuEncCfmSdus *)rrcMsg->mBuf)->sdu.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : encode status type MisMatch: exp (%d) rcvd (%d) \n",
                  status, ((NhuEncCfmSdus *)rrcMsg->mBuf)->sdu.status), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   storeEncMsg = FALSE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "storeEncMsg",  &(storeEncMsg));
   /* If storeEncMsg is TRUE, then store the message nhAccCb. This is reqd to *
    * send the encoded msg in DatReq in case of HO at source enodeb .         */
   if(TRUE == storeEncMsg)
   {
      if(!(rrcMsg->u.nhuInfo.encBufInfo.encBufPres))
      {
         CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuEncodeCfm():no message to store \n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      SCpyMsgMsg(rrcMsg->u.nhuInfo.encBufInfo.encBuf,
                 0, 0, &nhAccCb.encBufInfo.encBuf);
      nhAccCb.encBufInfo.encBufPres = TRUE;
      nhAccCb.encBufInfo.msgLen = rrcMsg->u.nhuInfo.encBufInfo.msgLen;
   }
   /* Free the mBuf memory from nhuInfo */
   if(rrcMsg->u.nhuInfo.encBufInfo.encBufPres)
   {
      rrcMsg->u.nhuInfo.encBufInfo.encBufPres = FALSE;
      rrcMsg->u.nhuInfo.encBufInfo.msgLen = 0;
      CMXTA_FREEMBUF(rrcMsg->u.nhuInfo.encBufInfo.encBuf);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuEncodeCfm */

/*
*
*       Fun:   nhAcHdlNhuDecodeReq
*
*       Desc:  Decode request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuDecodeReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuDecodeReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U32           transId;
   U16           ueId;
   U16           cellId;
   Mem           sMem;
   NhuDecodeSduReq *nhuDecodeSduReq;
   NhuDecodeSduCfm *nhuDecodeSduCfm;
   Buffer        *mBuf;
   U8            msgType;
   S16           ret = ROK;
   Bool          dbgFlag = NH_PASN_DBG_FLAG;
   CmPAsnErr     err;
   U32           fLen;
   U8            fillInvalid = 0;
   U8             nullSdu=0;
   U8             nullMbuf=0;
   U8             cfmFail=0;
   U8             tmpDat[4]={0x1,0x2,0x3,0x4};
   MsgLen         tmpCnt=0;

   sMem.region = 0;
   sMem.pool = 0;

   TRC2(nhAcHdlNhuDecodeReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDecodeReq(), tcId (%ld)\n",
                  tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDecodeReq(), tcId (%d)\n",
                  tcCb->tcId));
#endif

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif


   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event   = EVTNHUENCODEREQ;

   spId = 0;
   ueId = 0;
   cellId = 0;
   transId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));

   CMXTA_ALLOC(&nhuDecodeSduReq, sizeof(NhuDecodeSduReq));
   CMXTA_ALLOCMBUF(&mBuf);

   CMXTA_ALLOC_EVNT(&nhuDecodeSduCfm, sizeof(NhuDecodeSduCfm), &sMem,
                                                   NHAC_MEM_PDU_SIZE);

   nhuDecodeSduReq->hdr.cellId = cellId;
   nhuDecodeSduReq->hdr.ueId = ueId;
   nhuDecodeSduReq->hdr.transId = transId;

   msgType = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "msgType",  &(msgType));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "fillInvalid",
                           &(fillInvalid));
   if (1 == fillInvalid)
   {
      /* Fill a dummy value here to not to leave mBuf as NULL */
      SCpyFixMsg((Data *)&tmpDat, (Buffer *)mBuf, 0, (MsgLen)4, &tmpCnt);
      nhuDecodeSduReq->sduType = NHU_MSG_DLBCCHDLSCH;
      ret = CMXTA_ERR_NONE;
   }
   else
   {
      nhuDecodeSduReq->sduType = msgType;
      switch(msgType)
      {
         case NHU_MSG_HOCMD:
            ret = nhAcUtlFillNhuHoCmd(tcCb, spCb, (Ptr)nhuDecodeSduCfm,
                                      &nhuDecodeSduCfm->ie.hovrCmd);
            if(ROK == ret)
            {
               /* Encode the message */
               ret = cmPAsnEncMsgUalign ((TknU8*)(&nhuDecodeSduCfm->ie.hovrCmd), 
                                         CM_PASN_USE_MBUF, (Void *)(mBuf),0, 
                                         nhHovrCmd_Pdu, &err, &fLen, dbgFlag, FALSE);
            }
         break;

         case NHU_MSG_UERACAPINFO:
            ret = nhAcUtlFillNhuUeRadAccessCapInfo(tcCb, spCb, (Ptr)nhuDecodeSduCfm,
                                               &nhuDecodeSduCfm->ie.ueRadioCapInfo);
            if(ROK == ret)
            {
               /* Encode the message */
               ret = cmPAsnEncMsgUalign ((TknU8*)(&nhuDecodeSduCfm->ie.ueRadioCapInfo), 
                                         CM_PASN_USE_MBUF, (Void *)(mBuf),0, 
                           nhUERadioAccessCapInfo_Pdu, &err, &fLen, dbgFlag, FALSE);
            }
         break;

         case NHU_MSG_UECAPINFO:
            ret = nhAcUtlFillNhuUeCapInfo(tcCb, spCb, (Ptr)nhuDecodeSduCfm,
                                          &nhuDecodeSduCfm->ie.ueCapInfo);
            if(ROK == ret)
            {
               /* Encode the message */
               ret = cmPAsnEncMsgUalign ((TknU8*)(&nhuDecodeSduCfm->ie.ueCapInfo), 
                                         CM_PASN_USE_MBUF, (Void *)(mBuf),0,
                                  nhUECapInfo_Pdu, &err, &fLen, dbgFlag, FALSE);
            }
         break;

         case NHU_MSG_HOPREPINFO:
            ret = nhAcUtlFillNhuHoPrepInfo(tcCb, spCb, (Ptr)nhuDecodeSduCfm,
                                           &nhuDecodeSduCfm->ie.nhuHovrPrepInfo);
            if(ROK == ret)
            {
               /* Encode the message */
               ret = cmPAsnEncMsgUalign ((TknU8*)(&nhuDecodeSduCfm->ie.nhuHovrPrepInfo), 
                                         CM_PASN_USE_MBUF, (Void *)(mBuf),0, 
                               nhHovrPrepInfo_Pdu, &err, &fLen, dbgFlag, FALSE);
            }
         break;

         case NHU_DEC_SDUTYPE_EUTRA_UECAP_IE:
            ret = nhAcUtlFillNhuUECapIE(tcCb, spCb, (Ptr)nhuDecodeSduCfm,
                                        &nhuDecodeSduCfm->ie.nhuUE_EUTRA_Cap);
            if(ROK == ret)
            {
               /* Encode the message */
               ret = cmPAsnEncMsgUalign ((TknU8*)(&nhuDecodeSduCfm->ie.nhuUE_EUTRA_Cap), 
                                         CM_PASN_USE_MBUF, (Void *)(mBuf),0,
                             nhUE_EUTRA_Cap_Pdu, &err, &fLen, dbgFlag, FALSE);
            }
         break;
#if 0 /* TODO - Need to update for IRAT HO container encoding test */
         case NHU_DEC_SDUTYPE_UTRA_INTR_HOVR_MESSGE:
            ret = nhAcUtlFillNhuUE_UTRANHovrInfo(tcCb, spCb, (Ptr)nhuDecodeSduCfm,
                                        &nhuDecodeSduCfm->ie.nhuUTRAUECapOctStr.
                                        nhuUE_UTRAHovrInfo);
            if(ROK == ret)
            {
               /* Encode the message */
               ret = cmPAsnEncMsgUalign ((TknU8*)(&nhuDecodeSduCfm->ie.
                       nhuUTRAUECapOctStr.nhuUE_UTRAHovrInfo), CM_PASN_USE_MBUF,
                       (Void *)(mBuf),0, nhUTRANInterRATHovrInfo_Pdu, &err, &fLen,
                       dbgFlag, FALSE);
            }
         break;
#endif

         default:
            CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuDecodeReq() invalid msgType \n"));
            RETVALUE(CMXTA_ERR_NONE);
      }
   }

   CMXTA_FREEEVNT(nhuDecodeSduCfm);
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuDecodeReq() : Encoding FAILED\n"));
      CMXTA_FREEMBUF(mBuf);
      RETVALUE(CMXTA_ERR_INT);
   }

   nhuDecodeSduReq->mbuf = mBuf;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREEMBUF(nhuDecodeSduReq->mbuf);
         CMXTA_FREE(nhuDecodeSduReq, sizeof(NhuDecodeSduReq));
         nhuDecodeSduReq = NULLP;
      }
      else
      {
         CMXTA_FREEMBUF(nhuDecodeSduReq->mbuf);
         CMXTA_FREE(nhuDecodeSduReq, sizeof(NhuDecodeSduReq));
         RETVALUE(CMXTA_ERR_NONE);
      }

   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullMbuf",  &(nullMbuf));
   if (nullMbuf)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREEMBUF(nhuDecodeSduReq->mbuf);
         CMXTA_FREE(nhuDecodeSduReq, sizeof(NhuDecodeSduReq));
         nhuDecodeSduReq = NULLP;
      }
      else
      {
         CMXTA_FREEMBUF(nhuDecodeSduReq->mbuf);
         CMXTA_FREE(nhuDecodeSduReq, sizeof(NhuDecodeSduReq));
         RETVALUE(CMXTA_ERR_NONE);
      }

   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cfmFail",  &(cfmFail));
   if (cfmFail)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }

   if (CMXTA_ERR_NONE != NxLiNhuDecodeReq(&pst, spId, nhuDecodeSduReq))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuDecodeReq() : returned RFAILED\n"));
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuDecodeReq */

/*
*
*       Fun:   nhAcHdlNhuDecodeCfm
*
*       Desc:  Decode confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlNhuDecodeCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nhAcHdlNhuDecodeCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NhAccMsgQElm  *rrcMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U16            decMsgType;

   TRC2(nhAcHdlNhuDecodeCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDecodeCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuDecodeCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlNhuDecodeCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rrcMsg = (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Get the Pst information here from RRC User to RRC Layer --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);

   pst.event = EVTNHUDCODECFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for suId --*/
   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   if (suId != rrcMsg->u.nhuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) recvd (%d) \n",
               suId, rrcMsg->u.nhuInfo.suId),2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "decMsgType",  &(decMsgType));
   /* if the suId value is not given from the xml file return with failure*/
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlNhuDecodeCfm(): decMsgType not provided from xml\n"));
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Compare the value in the message and the value provided from xml */
   if (decMsgType != rrcMsg->u.nhuInfo.decMsgType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : decode message type MisMatch: exp (%d) rcvd (%d) \n",
                  decMsgType, rrcMsg->u.nhuInfo.decMsgType), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuDecodeCfm */
/*
*
*       Fun:   nhAcHdlNhuPdcpDataFwdReq
*
*       Desc:  PDCP Data Forward Request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16  nhAcHdlNhuPdcpDataFwdReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  nhAcHdlNhuPdcpDataFwdReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SpId          spId = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   NhuHdr        nhuHeader;
   U32           transId;
   U16           ueId;
   U16           cellId;


   TRC2(nhAcHdlNhuPdcpDataFwdReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuPdcpDataFwdReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlNhuPdcpDataFwdReq(), tcId (%d)\n", tcCb->tcId));
#endif
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;


   cmXtaGetPst(&pst, ENTNX, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,
                  dstProcId,FALSE);
   pst.event = EVTNHUSTARTPDCPDATAFWDREQ;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
  
   nhuHeader.cellId =  cellId;
   nhuHeader.ueId   =  ueId; 
   nhuHeader.transId = transId | 0x2;  
   nhuHeader.isUlDatFwdReq = FALSE;  
   if(CMXTA_ERR_NONE != NxLiNhuPdcpDatFwdReq(&pst,spId,nhuHeader))
   {
 	
   }
  
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcHdlNhuDecodeCfm */

/**********************************************************************
  
         End of file:     nhac_nhuhdl.c@@/main/3 - Fri Jul  1 01:13:05 2011
   
**********************************************************************/
/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      Reena            1. LTE RRC Initial Release.
/main/2      ---      chebli           1. RRC Release 2.1.
nh002.201    ---      vkulkarni        1. Changes due to NhuSysBwCfg structure 
                                          modification
/main/3      ---      sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
