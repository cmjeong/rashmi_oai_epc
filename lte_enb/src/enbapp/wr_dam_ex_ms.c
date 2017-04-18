

/********************************************************************20**

     Name:    EnodeB Application

     Type:    C Source file

     Desc:    This file contains the functions to handle any incoming
              message (loosely coupled), from other layers.

     File:    wr_dam_ex_ms.c

     Sid:      fc_dam_ex_ms.c@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:51:33 2014

     Prg:     sps

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="DAM";
static int RLOG_MODULE_ID=16;
static int RLOG_FILE_ID=107;

/* header include files */
#include "wr.h"
#include "wr_ifm_dam.h"
#include "wr_ifm_dam_utils.h"
#include "wr_ifm_dam_utils.x"
#include "ssi.h"
#ifdef SS_RBUF
#include "ss_rbuf.h"
#include "ss_rbuf.x"
#endif
#include "wr_smm_init.h"

#ifdef SS_RBUF
extern SsRngBufCnt rngCb;
extern U32 gulRcvdCnt;
#endif
#ifdef SS_RBUF
#ifdef ANSI
PUBLIC void wrDamBatchProc
(
Void
)
#else
PUBLIC void wrDamBatchProc()
Void;
#endif
{
   U32 mBuf = 0;
   Pst pst = {0};
   U32 n=0;
   U32 count = 0;
   U32 tempBuff[128]; /* Increasing size as number if read increased*/
   /* Fill pst */
   pst.srcProcId = WR_SRC_PROC_ID;
   pst.dstProcId = WR_DST_PROC_ID;
   pst.dstEnt = ENTPX;
   pst.dstInst = 0;
   pst.srcEnt = ENTPJ;
   pst.srcInst = 0;
   pst.prior = PRIOR0;
   pst.route = RTESPEC;
   pst.event = EVTFPPJUDATIND;
   pst.region = BC_SHRD_REG;
   pst.pool = 1;
   pst.selector = 1; /*SM_SELECTOR_LC */
   /*Void *elem = NULLP;*/
   /* MITUL tcp data stoll n =10 */
   while((n< rngCb.ulRngBuffCnt) && (SDeqSRngBuf(SS_RNG_BUF_ICPU_TO_DAM, (void *)&mBuf) == ROK))
   {
       tempBuff[n] = mBuf;
       n++;
   }
   gulRcvdCnt = n; 
   for(count = 0; count < n; count++)
   {
       cmUnpkFpPjuDatInd(PxLiPjuDatInd, &pst, (Buffer *)tempBuff[count]);
   }
}
#endif
/*
 *
 *       Fun:    wrDamActvTsk - DAM activation
 *
 *       Desc:   Function used to handle the event generated for DAM module.
 *               Will call the unpack functions which in turn calls the
 *               handlers of it.
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_dam_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 wrDamActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else
PUBLIC S16 wrDamActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   TRC3(wrDamActvTsk);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (pst == (Pst *)NULLP)
   {
      RLOG0(L_ERROR, "Invalid Pst");
      if (mBuf != (Buffer *)NULLP)
      {
         (Void)SPutMsg(mBuf);
      }

      RETVALUE(RFAILED);
   }

   if (mBuf == (Buffer *)NULLP)
   {
      RLOG0(L_ERROR, "Invalid MBuf");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   /*  Handling Events for ENTEU */
   switch (pst->srcEnt)
   {
      case ENTWR:
         switch (pst->event)
         {
              /* Tunnel Creation */
            case EVTDAMTNLCRETREQ:
               cmUnPkTnlCreatReq(EuUiDamTnlCreatReq, pst,mBuf);
               break;
              /* Tunnel Del Req */
            case EVTDAMTNLDELTREQ:
               cmUnPkTnlDelReq(EuUiDamTnlDelReq, pst, mBuf);
               break;
              /* UE Del Req */
            case EVTDAMUEDELTREQ:
               cmUnPkUeDelReq(EuUiDamUeDelReq, pst, mBuf);
               break;
              /* Cell Add Req */
            case EVTDAMCELLADDREQ:
              cmUnPkCellAddReq(EuUiDamCellAddReq, pst, mBuf);
               break;
              /* UE Reconf Req */
            case EVTDAMRECFGREQ:
               cmUnPkReCfgReq(EuUiDamReCfgReq, pst, mBuf);
               break;
             /* UE Re-Estb. */
            case EVTDAMRESTREQ:
               cmUnPkReestabReq(EuUiDamReestabReq, pst, mBuf);
               break;
             /* Tunnel State Change Req */
            case EVTDAMTNLSTCHNGREQ:
              cmUnPkTnlStChngReq(EuUiDamTnlStChngReq, pst,mBuf);
              break;
             /* Start Inactivity Timer */
            case EVTDAMINACTIVITYTMR:
              cmUnPkStartInactivityTmr(EuUiDamStartInactivityTmr, pst,mBuf);
              break;
              /* UE Stop Timer */
            case EVTDAMUESTOPTMR:
              cmUnPkStopUeTmr(EuUiDamStopUeTmr, pst,mBuf);
              break;
             /* DAM Cfg Req */
            case EVTDAMCFGREQ:
              cmUnpkDamCfgReq(EuUiDamCfgReq, pst,mBuf);
              break;
             /* DAM Control Req */
            case EVTDAMCNTRLREQ:
              cmUnpkDamCntrlReq(EuUiDamCntrlReq, pst,mBuf);
              break;
             /* DAM Tunnel Modification Req */
            case EVTDAMTNLMODREQ:
              cmUnpkTnlModReq(EuUiDamTnlModReq, pst,mBuf);
              break;
            case EVTDAMHDLHOFAIL:
              cmUnPkHdlHoFailure(EuUiDamHdlHoFailure, pst,mBuf); 
              break;
            /*ccpu00138576 - start*/ 
            case EVTDAMDATRCVDFLAG:
              cmUnPkSetDataRcvdFlag(EuUiDamSetDataRcvdFlag,pst,mBuf);
              break;
            case EVTDAMBNDREQ:
              cmUnpkDamBndReq(EuUiDamBndReq,pst,mBuf);
              break;
            /*ccpu00138576 - end*/ 
            default:
              RLOG0(L_ERROR, "Unknown Event from SM");
               (Void)SPutMsg(mBuf);
               break;
         }/* Event Switch */
         break;
      case ENTEG:
         switch (pst->event)
         {
            case EVTEGTBNDCFM:
               (Void)cmUnpkEgtBndCfm(EuLiEgtBndCfm, pst, mBuf);
               break;
            case EVTEGTULCLTNLMGMTCFM:
               (Void)cmUnpkEgtEguLclTnlMgmtCfm(EuLiEgtEguLclTnlMgmtCfm, pst, mBuf);
               break;
            default:
              RLOG0(L_ERROR, "Unknown Event from EGT");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;
      case ENTSM:
         switch (pst->event)
         {
#if (defined(LCLWR) || defined(LWLCLWR))
            case EVTLWRCFGREQ:
               cmUnpkLwrCfgReq(WrMiDamLwrCfgReq, pst, mBuf);
               break;

            case EVTLWRCNTRLREQ:
               cmUnpkLwrCntrlReq(WrMiDamLwrCntrlReq, pst, mBuf);
               break;

            case EVTLWRLOADIND:
               cmUnpkLwrLoadInd(WrMiLwrLoadInd, pst, mBuf);
               break;
            case EVTLWRDYNCFGREQ:
               cmUnpkLwrDynCfgReq(WrMiLwrDynCfgReq, pst, mBuf);
               break;
#endif
            default:
               RLOG0(L_ERROR, "wrActvTsk: Unknown Event from SM");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;
 
      case ENTPJ:
         switch (pst->event)
         {
            case  EVTPJUBNDCFM:
               cmUnpkPjuBndCfm(PxLiPjuBndCfm, pst, mBuf);
               break;
            case  EVTPJUDATIND:
               cmUnpkPjuDatInd(PxLiPjuDatInd, pst, mBuf);
               break;
#ifdef SS_RBUF
            case  EVTFPPJUDATIND:
               cmUnpkFpPjuDatInd(PxLiPjuDatInd, pst, mBuf);
               break;
#endif
            case EVTPJUDATFWDIND:
               cmUnpkPjuDatFwdInd(PxLiPjuDatFwdInd, pst, mBuf);
               break;
            case  EVTPJUDATCFM:
               cmUnpkPjuDatCfm(PxLiPjuDatCfm, pst, mBuf);
               break;
            default:
               RLOG0(L_ERROR, "Unknown Event from PJU");
               (Void)SPutMsg(mBuf);
               break;
         }

         break;
   default:
      RLOG0(L_ERROR, "Received Msg From Unknow Src");
         (Void)SPutMsg(mBuf);
         break;
   }/* Entity Switch */
   (Void)SExitTsk();
   RETVALUE(ROK);
} /* end of wrDamActvTsk() */

/********************************************************************30**
  
         End of file:     fc_dam_ex_ms.c@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:51:33 2014
  
*********************************************************************31*/
/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**
 
    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
*********************************************************************91*/
