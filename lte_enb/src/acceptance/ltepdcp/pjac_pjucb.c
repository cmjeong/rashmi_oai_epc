

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_pjucb.c

     Sid:      pjac_pjucb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:04 2015

     Prg:     Adarsh
*********************************************************************21*/

/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "pju.h"           /* PJU defines */
#include "rgu.h"           /* RGU defines */
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_pju.h"      /* CKW Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_pju.x"      /* CKW Acceptance defines */


/**
@brief
@return CmXtaTCCb*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  kwAcPjuTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  kwAcPjuTstCbFind ()
#endif
{
   TRC2(kwAcPjuTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change PJAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* kwAcPjuTstCbFind */


/**
@brief utility function for sending the message to test engine
@param pst
@param suId
@param status
@param ptr
@param ptr2
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcPjuSendMsg
(
Pst            *pst,
SpId           suId,
U8             status,
Void           *ptr,
Void           *ptr2,
Buffer         *mBuf
)
#else
PUBLIC S16 kwAcPjuSendMsg(pst, suId, status, ptr, ptr2, mBuf)
Pst            *pst;
SpId           suId;
U8             status;
Void           *ptr;
Void           *ptr2;
Buffer         *mBuf;
#endif /* ANSI */
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   KwAcMsgQElm    *kwElm;
   KwAcPjuInfo    *pjuInfo;

   S16 ret = CMXTA_ERR_NONE;
 
   TRC3(kwAcPjuSendMsg);

   CMXTA_DBG_PARAM((_cmxtap, "kwAcPjuSendMsg())\n"));

   CMXTA_ZERO(&qElm, sizeof(CmXtaMsgQElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcPjuTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious
        message, drop it --*/
 
      /*-- Update debug prints --*/
      CMXTA_DBG_INFO((_cmxtap, "kwAcPjuTstCbFind is returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Check if any tapa directives set --*/
 
   /*-- Allocate KW memory data --*/
   kwElm = NULLP;
   CMXTA_ALLOC(&kwElm, sizeof (KwAcMsgQElm));
   if (kwElm == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcPjuSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)kwElm;
   qElm.msgFreeFun = pjAcUtlPjuFreeCb;
   
    /*** fill the suId in teh Q element****/
   pjuInfo = &(kwElm->u.pjuInfo);
   pjuInfo->cmInfo.suId = suId;

   switch (pst->event) 
   {
      case EVTPJUBNDCFM:
      {
         pjuInfo->u.status = status;
         break;
      }

      case EVTPJUDATIND:
      {
         pjuInfo->pdcpId = (CmLtePdcpId*)ptr2;
         kwElm->mBuf = mBuf; /* Take pointer of mBuf to Element */
         break;
      }

      case EVTPJUDATCFM:
      {
         pjuInfo->pdcpId = (CmLtePdcpId*)ptr2;
         pjuInfo->u.datCfm = (PjuDatCfmInfo*)ptr;
         break;
      }

      case EVTPJUSTAIND:
      {
         pjuInfo->pdcpId = (CmLtePdcpId*)ptr2;
         pjuInfo->u.staInd = (PjuStaIndInfo*)ptr;
         kwElm->mBuf = mBuf; /* Take pointer of mBuf to Element */
         break;
      }

      case EVTPJUDATFWDIND:
      {
         pjuInfo->pdcpId = (CmLtePdcpId*)ptr2;
         pjuInfo->u.datFwdInd = (PjuDatFwdIndInfo*)ptr;
         break;
      }
   }

   if( ret == ROK)
   {
      /*-- Test case found, queue the message for the tcCb --*/
       /* Push it onto the message queue --*/
       (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

       /*-- Check if the message has arrived in a TC fashion, this
            may happen if the test engine was sending a message and
            the layer sent a message back in TC fashion, do not
            trigger the test engine now in that case, the test engine
            will later have a look at the queued message --*/
       if (tcCb->busy == FALSE)
          cmXtaTCEngine(tcCb);
   }
   else
   {
      CMXTA_FREE(kwElm, sizeof(KwAcMsgQElm));
   }

   RETVALUE(ROK);
} /* kwAcPjuSendMsg */


/**
@brief Call handler for Bind confirmation
@param pst
@param suId
@param status
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PxLiPjuBndCfm
(
Pst *pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 PxLiPjuBndCfm(pst,suId,status)
Pst *pst;
SuId suId;
U8 status;
#endif
{
   TRC2(PxLiPjuBndCfm);

   CMXTA_DBG_PARAM((_cmxtap, "PxLiPjuBndCfm():\n"));

   pst->event = EVTPJUBNDCFM;

   kwAcPjuSendMsg(pst, suId, status, NULLP, NULLP, NULLP);

   RETVALUE(ROK);
} /* PxLiPjuBndCfm */


/**
@brief Call handler for Data Indication
@param pst
@param suId
@param datInd
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PxLiPjuDatInd
(
Pst            *pst,
SuId           suId,
CmLtePdcpId    *pdcpId,
Buffer         *mBuf
)
#else
PUBLIC S16 PxLiPjuDatInd(pst, suId, pdcpId, mBuf)
Pst            *pst;
SuId           suId;
CmLtePdcpId    *pdcpId;
Buffer         *mBuf;
#endif
{
   TRC2(PxLiPjuDatInd);
   CMXTA_DBG_PARAM((_cmxtap, "PxLiPjuDatInd():\n"));

   pst->event = EVTPJUDATIND;
   
   kwAcPjuSendMsg(pst, suId, 0, NULLP, pdcpId, mBuf);
   RETVALUE(ROK); 
} /* PxLiPjuDatInd */

/**
@brief Call handler for Data Confirmation
@param pst
@param suId
@param datCfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PxLiPjuDatCfm
(
Pst            *pst,
SuId           suId,
CmLtePdcpId    *pdcpId,
PjuDatCfmInfo  *datCfm
)
#else
PUBLIC S16 PxLiPjuDatCfm(pst, suId, pdcpId, datCfm)
Pst            *pst;
SuId           suId;
CmLtePdcpId    *pdcpId;
PjuDatCfmInfo  *datCfm;
#endif
{
   CmLtePdcpId    *tmppdcpId; 
   TRC2(PxLiPjuDatCfm);
   CMXTA_DBG_PARAM((_cmxtap, "PxLiPjuDatCfm():\n"));

   /* Allocate memory for pdcpId */
   KW_ALLOC_ACC(tmppdcpId, sizeof(CmLtePdcpId));
   if (tmppdcpId == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "PxLiPjuDatFwdInd(): KW_ALLOC pdcpId Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   tmppdcpId->ueId   =  pdcpId->ueId;
   tmppdcpId->cellId =  pdcpId->cellId;
   tmppdcpId->rbId   =  pdcpId->rbId;
   tmppdcpId->rbType =  pdcpId->rbType; 
   
   pst->event = EVTPJUDATCFM;
   
   kwAcPjuSendMsg(pst, suId, 0, datCfm, tmppdcpId, NULLP);
   RETVALUE(ROK); 
} /* PxLiPjuDatCfm */

/**
@brief Call handler for Status Indication
@param pst
@param suId
@param staInd
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PxLiPjuStaInd
(
Pst            *pst,
SuId           suId,
CmLtePdcpId    *pdcpId,
PjuStaIndInfo  *staInd,
Buffer         *mBuf
)
#else
PUBLIC S16 PxLiPjuStaInd(pst, suId, pdcpId, staInd, mBuf)
Pst            *pst;
SuId           suId;
CmLtePdcpId    *pdcpId;
PjuStaIndInfo  *staInd;
Buffer         *mBuf;
#endif
{
   CmLtePdcpId    *tmppdcpId;
   PjuStaIndInfo  *tmpstaInd; 
   TRC2(PxLiPjuStaInd);
   CMXTA_DBG_PARAM((_cmxtap, "PxLiPjuStaInd():\n"));

   /* Allocate memory for pdcpId */
   KW_ALLOC_ACC(tmppdcpId, sizeof(CmLtePdcpId));
   KW_ALLOC_ACC(tmpstaInd, sizeof(PjuStaIndInfo));
   if ((tmppdcpId == NULLP) ||(tmpstaInd == NULLP))
   {
      CMXTA_DBG_FATAL((_cmxtap, "PxLiPjuDatFwdInd(): KW_ALLOC Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   tmppdcpId->ueId   =  pdcpId->ueId;
   tmppdcpId->cellId =  pdcpId->cellId;
   tmppdcpId->rbId   =  pdcpId->rbId;
   tmppdcpId->rbType =  pdcpId->rbType;
   tmpstaInd->cause =   staInd->cause; 

   pst->event = EVTPJUSTAIND;
   
   kwAcPjuSendMsg(pst, suId, 0, tmpstaInd, tmppdcpId, mBuf);
   RETVALUE(ROK); 
} /* PxLiPjuStaInd */

/**
@brief Call handler for Data Forward Indication
@param pst
@param suId
@param pdcpId
@param datFwdInd
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PxLiPjuDatFwdInd
(
Pst            *pst,
SuId           suId,
CmLtePdcpId    *pdcpId,
PjuDatFwdIndInfo   *datFwdInd
)
#else
PUBLIC S16 PxLiPjuDatFwdInd(pst, suId, pdcpId, datFwdInd)
Pst            *pst;
SuId           suId;
CmLtePdcpId    *pdcpId;
PjuDatFwdIndInfo   *datFwdInd;
#endif
{
   CmLtePdcpId    *tmppdcpId; 
   TRC2(PxLiPjuDatFwdInd);
   CMXTA_DBG_PARAM((_cmxtap, "PxLiPjuDatFwdInd():\n"));

   /* Allocate memory for pdcpId */
   KW_ALLOC_ACC(tmppdcpId, sizeof(CmLtePdcpId));
   if (tmppdcpId == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "PxLiPjuDatFwdInd(): KW_ALLOC pdcpId Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   tmppdcpId->ueId   =  pdcpId->ueId;
   tmppdcpId->cellId =  pdcpId->cellId;
   tmppdcpId->rbId   =  pdcpId->rbId;
   tmppdcpId->rbType =  pdcpId->rbType; 

   pst->event = EVTPJUDATFWDIND;
   
   kwAcPjuSendMsg(pst, suId, 0, datFwdInd, tmppdcpId, NULLP);
   RETVALUE(ROK); 
} /* PxLiPjuDatFwdInd */


/**
@brief Call handler for Bind confirmation
@param pst
@param suId
@param status
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiPjuBndCfm
(
Pst *pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 NhLiPjuBndCfm(pst,suId,status)
Pst *pst;
SuId suId;
U8 status;
#endif
{
   TRC2(NhLiPjuBndCfm);

   CMXTA_DBG_PARAM((_cmxtap, "NhLiPjuBndCfm():\n"));

   pst->event = EVTPJUBNDCFM;

   kwAcPjuSendMsg(pst, suId, status, NULLP, NULLP, NULLP);

   RETVALUE(ROK);
} /* NhLiPjuBndCfm */


/**
@brief Call handler for Data Indication
@param pst
@param suId
@param datInd
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiPjuDatInd
(
Pst            *pst,
SuId           suId,
CmLtePdcpId    *pdcpId,
Buffer         *mBuf
)
#else
PUBLIC S16 NhLiPjuDatInd(pst, suId, pdcpId, mBuf)
Pst            *pst;
SuId           suId;
CmLtePdcpId    *pdcpId;
Buffer         *mBuf;
#endif
{
   TRC2(NhLiPjuDatInd);
   CMXTA_DBG_PARAM((_cmxtap, "NhLiPjuDatInd():\n"));

   pst->event = EVTPJUDATIND;
   
   kwAcPjuSendMsg(pst, suId, 0, NULLP, pdcpId, mBuf);
   RETVALUE(ROK); 
} /* NhLiPjuDatInd */

/**
@brief Call handler for Data Confirmation
@param pst
@param suId
@param datCfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiPjuDatCfm
(
Pst            *pst,
SuId           suId,
CmLtePdcpId    *pdcpId,
PjuDatCfmInfo  *datCfm
)
#else
PUBLIC S16 NhLiPjuDatCfm(pst, suId, pdcpId, datCfm)
Pst            *pst;
SuId           suId;
CmLtePdcpId    *pdcpId;
PjuDatCfmInfo  *datCfm;
#endif
{
   TRC2(NhLiPjuDatCfm);
   CMXTA_DBG_PARAM((_cmxtap, "NhLiPjuDatCfm():\n"));

   pst->event = EVTPJUDATCFM;
   
   kwAcPjuSendMsg(pst, suId, 0, datCfm, pdcpId, NULLP);
   RETVALUE(ROK); 
} /* NhLiPjuDatCfm */

/**
@brief Call handler for Status Indication
@param pst
@param suId
@param staInd
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiPjuStaInd
(
Pst            *pst,
SuId           suId,
CmLtePdcpId    *pdcpId,
PjuStaIndInfo  *staInd,
Buffer         *mBuf
)
#else
PUBLIC S16 NhLiPjuStaInd(pst, suId, pdcpId, staInd, mBuf)
Pst            *pst;
SuId           suId;
CmLtePdcpId    *pdcpId;
PjuStaIndInfo  *staInd;
Buffer         *mBuf;
#endif
{
   CmLtePdcpId    *tmppdcpId;
   PjuStaIndInfo  *tmpstaInd; 
   TRC2(NhLiPjuStaInd);
   CMXTA_DBG_PARAM((_cmxtap, "NhLiPjuStaInd():\n"));

   /* Allocate memory for pdcpId */
   KW_ALLOC_ACC(tmppdcpId, sizeof(CmLtePdcpId));
   KW_ALLOC_ACC(tmpstaInd, sizeof(PjuStaIndInfo));
   if ((tmppdcpId == NULLP) ||(tmpstaInd == NULLP))
   {
      CMXTA_DBG_FATAL((_cmxtap, "PxLiPjuDatFwdInd(): KW_ALLOC Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   tmppdcpId->ueId   =  pdcpId->ueId;
   tmppdcpId->cellId =  pdcpId->cellId;
   tmppdcpId->rbId   =  pdcpId->rbId;
   tmppdcpId->rbType =  pdcpId->rbType;
   tmpstaInd->cause =   staInd->cause; 
   pst->event = EVTPJUSTAIND;
   
   kwAcPjuSendMsg(pst, suId, 0, tmpstaInd, tmppdcpId, mBuf);
   RETVALUE(ROK); 
} /* NhLiPjuStaInd */

/**
@brief Call handler for Data Forward Indication
@param pst
@param suId
@param pdcpId
@param datFwdInd
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiPjuDatFwdInd
(
Pst            *pst,
SuId           suId,
CmLtePdcpId    *pdcpId,
PjuDatFwdIndInfo   *datFwdInd
)
#else
PUBLIC S16 NhLiPjuDatFwdInd(pst, suId, pdcpId, datFwdInd)
Pst            *pst;
SuId           suId;
CmLtePdcpId    *pdcpId;
PjuDatFwdIndInfo   *datFwdInd;
#endif
{
   TRC2(NhLiPjuDatFwdInd);
   CMXTA_DBG_PARAM((_cmxtap, "NhLiPjuDatFwdInd():\n"));

   pst->event = EVTPJUDATFWDIND;
   
   kwAcPjuSendMsg(pst, suId, 0, datFwdInd, pdcpId, NULLP);
   RETVALUE(ROK); 
} /* NhLiPjuDatFwdInd */


/********************************************************************30**

         End of file:     pjac_pjucb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:04 2015

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
/main/1      ---      vb         1. LTE PDCP Release 2.1.
*********************************************************************91*/

