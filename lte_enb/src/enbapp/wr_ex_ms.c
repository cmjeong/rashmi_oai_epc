
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_ex_ms.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_MODULE_ID=2;
static int RLOG_FILE_ID=28;

/* header include files */
#include "wr.h"
#include "wr_lwr.h"

#include "wr_ifm_l1.h"
#include "wr_ifm_pdcp.h"

#include "czt.h"
#include "rmu.h"
#include "cpj.h"

#include "czt.x"

#include "egt.h"
#include "egt.x"
#include "cm_lte.x"
#include "cm_lte_rrm.x"
#include "rmu.x"
#include "rgr.x"
#include "cpj.x"

#include "wr_ifm_dam_utils.h"
#include "wr_ifm_dam_utils.x"

#include "wr_ifm_dam.h"
#include "rl_rlog.h"

#ifdef TIP_L3
#include "tip_cmn.h"
#endif

EXTERN void wrHandleSnfMsgs(Buffer *ptrClMsg);
#ifdef ENABLE_CNM
EXTERN PUBLIC U16 wrCnmHandleIctaMsg
(
   Buffer *mBuf
);
#endif
#ifdef L2_L3_SPLIT
EXTERN PUBLIC U16 wrHandleNmmMsg
(
   Buffer *mBuf
);
#endif
#ifdef WR_RELAY


/*
 *
 *       Fun:    wrActvTsk - RRC user activation
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_ex_ms.c
 *
 */
#ifdef ANSI
PUBLIC S16 wrActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else
PUBLIC S16 wrActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   Mem sMem;
   Size     maxBlkSize;
   maxBlkSize = WR_MEM_PDU_SIZE;

   TRC3(wrActvTsk);
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
      RLOG0(L_ERROR, "Invalid MBuf ");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   /* Assigning the proper region */
   sMem.region = wrCb.init.region;
   sMem.pool   = WR_MEM_POOL;

   switch (pst->srcEnt)
   {
      case ENTSM:
         switch (pst->event)
         {
#if (defined(LCLWR) || defined(LWLCLWR))
            case EVTLWRCFGREQ:
               cmUnpkLwrCfgReq(WrMiLwrCfgReq, pst, mBuf);
               break;

            case EVTLWRCELLCFGREQ:
               cmUnpkLwrCellCfgReq(WrMiLwrCellCfgReq, pst, mBuf);
               break;

            case EVTLWRCNTRLREQ:
               cmUnpkLwrCntrlReq(WrMiLwrCntrlReq, pst, mBuf);
               break;

            case EVTLWRCELLCNTRLREQ:
               cmUnpkLwrCellCntrlReq(WrMiLwrCellCntrlReq, pst, mBuf);
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
      case ENTEG:
         switch(pst->event)
         {
            case EVTEGTBNDCFM:
               {
                  (Void)cmUnpkEgtBndCfm(EuLiEgtBndCfm, pst, mBuf);
                  break;
               }

            case EVTEGTUDATIND:
               {
                  (Void)cmUnpkEgtEguDatInd(EuLiEgtEguDatInd, pst, mBuf);
                  break;
               }

            case EVTEGTULCLTNLMGMTCFM:
               {
                  (Void)cmUnpkEgtEguLclTnlMgmtCfm(EuLiEgtEguLclTnlMgmtCfm, pst, mBuf);
                  break;
               }

            case EVTEGTUSTACFM:
               {
                  (Void)cmUnpkEgtEguStaCfm(EuLiEgtEguStaCfm, pst, mBuf);
                  break;
               }

            case EVTEGTUUSTAIND:
               {
                  (Void)cmUnpkEgtEguUStaInd(EuLiEgtEguUStaInd, pst, mBuf);
                  break;
               }

            case EVTEGTUERRIND:
               {
                  (Void)cmUnpkEgtEguErrInd(EuLiEgtEguErrInd, pst, mBuf);
                  break;
               }

         }
       break;

      case ENTNH: 
         switch(pst->event)
         {
#if (defined(LCNHU) || defined(LWLCNHU))
            case EVTNHUBNDCFM:
               cmUnpkNhuBndCfm(NxLiNhuBndCfm, pst, mBuf);
               break;

            case EVTNHUERRIND:
               cmUnpkNhuErrInd(NxLiNhuErrInd, pst, mBuf);
               break;

            case EVTNHUDATIND:
               cmUnpkNhuDatInd(NxLiNhuDatInd, pst, mBuf,&sMem, WR_MEM_PDU_SIZE);
               break;

            case EVTNHUDATCFM:
               cmUnpkNhuDatCfm(NxLiNhuDatCfm, pst, mBuf);
               break;

            case EVTNHUCFGCFM:
               cmUnpkNhuCfgCfm(NxLiNhuCfgCfm, pst, mBuf);
               break;

            case  EVTNHUCELLCFGCFM :
               cmUnpkNhuCellCfgCfm(NxLiNhuCellCfgCfm, pst, mBuf);
               break;
            case  EVTNHUENCODECFM:
               cmUnpkNhuEncodeCfm(NxLiNhuEncodeCfm, pst, mBuf);
               break;
            case  EVTNHUDCODECFM:
               cmUnpkNhuDecodeCfm(NxLiNhuDecodeCfm, pst, mBuf, &sMem, maxBlkSize);
               break;
#endif
            default:
               RLOG0(L_ERROR, "wrActvTsk: Unknown Evnt from NHU.");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;

      case ENTRG:
         switch (pst->event)
         {
            case EVTRGRBNDCFM:
               cmUnpkRgrBndCfm(NxLiRgrBndCfm, pst, mBuf);
               break;

            case EVTRGRCFGCFM:
               cmUnpkRgrCfgCfm(NxLiRgrCfgCfm, pst, mBuf);
               break;

            case EVTRGRTTIIND: /* Indication every 10ms */
               cmUnpkRgrTtiInd(NxLiRgrTtiInd, pst, mBuf);
               break;
#ifdef RGR_SI_SCH
            case EVTRGRSICFGCFM: 
               cmUnpkRgrSiCfgCfm(NxLiRgrSiCfgCfm, pst, mBuf);
               break;
            /* PH04_CMAS : Need to add code here. */
            case EVTRGRWARNINGSICFGCFM:
               cmUnpkRgrWarningSiCfgCfm(NxLiRgrWrngSiCfgCfm, pst, mBuf);
               break;

            case EVTRGRWARNINGSISTOPREQ:
               cmUnpkRgrWarningSiStopReq(NxLiRgrStopWrngSiCfgCfm, pst, mBuf);
               break;
            /* PH04_CMAS : end */

#endif
#ifdef RGR_CQI_REPT
            case EVTRGRSTAIND:
               cmUnpkRgrStaInd(NxLiRgrStaInd, pst, mBuf);
               break;               
#endif
/* LTE_ADV_DSFR starts */
            case EVTRGRLOADINFIND:
               cmUnpkRgrLoadInfInd(NxLiRgrLoadInfInd, pst, mBuf);
               /* dsfr_pal_fixes ** 21-March-2013 ** SKS */
               break;
/* LTE_ADV_DSFR ends */
            case EVTRGRUESTAIND:
               cmUnpkRgrUeStaInd(NxLiRgrUeStaInd, pst, mBuf);
               break;               
#ifdef TIP_L3
            case EVTAPPTIPPMSG:
               tipUnpkMacAppMsg(pst, mBuf);
               break;  
#endif
            default:
               RLOG1(L_ERROR, "wrActvTsk: Unknown event from RGR %d", pst->event );
               (Void)SPutMsg(mBuf);
               break;
         } 
         break;

      case ENTPJ:
         switch (pst->event)
         {
#ifdef TENB_AS_SECURITY
            case EVTCPJKDFCFM:
               cmUnpkCpjKdfCfm (WrIfmPdcpKdfCfm, pst, mBuf);
               break;
#endif /* TENB_AS_SECURITY */ 
           default:
               RLOG0(L_ERROR,"Unknown event from CPJ");
               (Void)SPutMsg(mBuf);
               break;
         } 
         break;
      case ENTTF:
         switch (pst->event)
         {
            case EVTCTFBNDCFM:
               cmUnpkCtfBndCfm (WrIfmL1BndCfm, pst, mBuf);
               break;

            case EVTCTFCFGCFM:
               cmUnpkCtfCfgCfm (WrIfmL1CfgCfm, pst, mBuf);
               break;
            case EVTCTFENBSTOPIND:
               cmUnpkCtfEnbStopInd (WrIfmL1EnbStopInd, pst, mBuf);
               break;
#ifdef TENB_AS_SECURITY
            case EVTCTFKDFCFM:
               cmUnpkCtfKdfCfm (WrIfmL1KdfCfm, pst, mBuf);
               break;
#endif /* TENB_AS_SECURITY */
#ifdef RSYS_WIRESHARK
#if 1  /* Imp: Do not delete this */
            case EVTCTFWIRESHARKMSG:
               wrHandleWireSharkMsg(mBuf);
               break;
#endif
#endif
#ifdef SS_RBUF
            case EVTCTFSNFRSPMSGS:
               printf("\n REM : Received SNIFFER MSGS \n");
               wrHandleSnfMsgs(mBuf);
               break;
#endif /* SS_RBUF */

#ifdef L2_L3_SPLIT
           case EVTCTFNMMMSG:
               {
                  printf("\n [APP::]Received NMM MSG...%d\n",pst->event);
                  /* Function Def not found;;need to fix it
                   * DONT DELETE....
                  wrHandleNmmMsg(mBuf);
                  */
               }
               break;
#endif
/*#if 0*/
#ifdef ENABLE_CNM
           case EVTCTFCNMMSG:
               {
                  printf("\n [APP::]Received ICTA MSG...%d\n",pst->event);
                  wrCnmHandleIctaMsg(mBuf);
               }
               break;
#endif
/*#endif*/
               /* CNM_DEV start */
            case EVTCTFCNMINITSYNCRSP:
               cmUnpkCtfCnmInitSyncRsp (TfLiCtfCnmInitialSyncRsp, pst, mBuf);
               break;

            case EVTCTFCNMSYNCIND:
               cmUnpkCtfCnmCellSyncInd (TfLiCtfCnmSyncInd, pst, mBuf);
               break;

            case EVTCTFCNMSYNCRSP:
               cmUnpkCtfCnmCellSyncRsp (TfLiCtfCnmSyncRsp, pst, mBuf);
               break;
               /* CNM_DEV end */

               /* Periodic REM for TPM */
            case EVTCTFPREMCELLSRCHRSP:
               cmUnpkPerRemCellSrchRsp (TfLiCtfPerCellSrchRsp, pst, mBuf);
               break;
               /* Periodic REM for TPM End */
               /* RLOG changes start */
            case EVTL2LOGBUF:
               /* Data from mBuf is copied inside this function and 
                  can be freed after the function comes out */
               rlProcessLogBufFromL2((void*) mBuf);
               (Void)SPutMsg(mBuf);
               break;
               /* RLOG changes end */
#ifdef TIP_L3
            case EVTL1TIPPMSG:
               tipUnpkL1AppMsg(pst, mBuf);
               break;
            case EVTTIPINITMSG:
               tipL3ProcessInitMsg(mBuf);
               break;
#endif
            default:
               RLOG0(L_ERROR, "wrActvTsk: Unknown event from CTF ");
               (Void)SPutMsg(mBuf);
               break;
         } 
         break;
#ifndef LTE_ENB_PERF
      case ENTSZ:
         switch (pst->event)
         {
            case EVTSZTBNDCFM:
               (Void)cmUnpkSztBndCfm(UzLiSztBndCfm, pst, mBuf);
               break;

            case EVTSZTSTAIND:
               (Void)cmUnpkSztStaInd(UzLiSztStaInd, pst, mBuf);
               break;

            case EVTSZTERRIND:
               (Void)cmUnpkSztLclErrInd(UzLiSztErrInd, pst, mBuf);
               break;

            case EVTSZTUDATIND:
               (Void)cmUnpkSztUDatInd(UzLiSztUDatInd, pst, mBuf, &sMem);
               break;

            case EVTSZTCONIND:
               (Void)cmUnpkSztConInd(UzLiSztConInd, pst, mBuf, &sMem);
               break;

            case EVTSZTCONCFM:
               (Void)cmUnpkSztConCfm(UzLiSztConCfm, pst, mBuf, &sMem);
               break;

            case EVTSZTRELIND:
               (Void)cmUnpkSztRelInd(UzLiSztRelInd, pst, mBuf, &sMem);
               break;

            case EVTSZTRELCFM:
               (Void)cmUnpkSztRelCfm(UzLiSztRelCfm, pst, mBuf, &sMem);
               break;

            case EVTSZTDATIND:
               (Void)cmUnpkSztDatInd(UzLiSztDatInd, pst, mBuf, &sMem);
               break;

            default:
               RLOG0(L_ERROR, "wrActvTsk: Unknown event from SZT ");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;

      case ENTCZ:
         switch (pst->event)
         {
            case EVTCZTBNDCFM:
            {
               (Void)cmUnpkCztBndCfm(RsLiCztBndCfm, pst, mBuf);
               break;
            }

            case EVTCZTGPIND:
            {
               (Void)cmUnpkCztGpInd(RsLiCztGpInd, pst, mBuf); 
               break;
            }

            case EVTCZTGPCFM:
            {
               (Void)cmUnpkCztGpCfm(RsLiCztGpCfm, pst, mBuf); 
               break;
            }

            case EVTCZTBMPIND:
            {
               (Void)cmUnpkCztBmpInd(RsLiCztBmpInd, pst, mBuf); 
               break;
            }
            case EVTCZTBMPCFM:
            {
               (Void)cmUnpkCztBmpCfm(RsLiCztBmpCfm, pst, mBuf); 
               break;
            }
            case EVTCZTGPERRIND:
            {
               (Void)cmUnpkCztGpErrInd(RsLiCztGpErrInd, pst, mBuf); 
                break;
            }
            case EVTCZTERRIND:
            {
               (Void)cmUnpkCztLclErrorInd(RsLiCztLclErrorInd, pst, mBuf); 
               break;
            }

            case EVTCZTSTAIND:
            {
               (Void)cmUnpkCztStatusInd(RsLiCztStatusInd, pst, mBuf);
               break;
            }
            case EVTCZTPEERASSOCIND:
            {
               (Void)cmUnpkCztDynamPeerAssocInd(RsLiCztDynamPeerAssocInd, pst, mBuf);
               break;
            }

            case EVTCZTLOCALRELCFM:
            {
               (Void)cmUnpkCztRelCfm(RsLiCztRelCfm, pst, mBuf);
               break;
            }

            case EVTCZTAUDCFM:
            {
               (Void)cmUnpkCztAudCfm(RsLiCztAudCfm, pst, mBuf);
               break;
            }

            default:
            {
               RLOG0(L_ERROR, "wrActvTsk: Unknown event from CZT ");
               (Void)SPutMsg(mBuf);
               break;
            }
         }
         break;
#endif
      case ENTEU:
         switch (pst->event)
         {
            case EVTDAMTNLCRETCFM:
               cmUnPkTnlCreatCfm(EuLiDamTnlCreatCfm,pst, mBuf);
               break;
            case EVTDAMUEDELTCFM:
               cmUnPkUeDelCfm(EuLiDamUeDelCfm,pst, mBuf);
               break;
            case EVTDAMREESTABCFM:
               cmUnPkReestabCfm(EuLiDamReestabCfm,pst, mBuf);
               break;
             case EVTDAMTNLMODCFM:
               cmUnpkTnlModCfm(EuLiDamTnlModCfm,pst, mBuf);
               break;
             case EVTDAMPDCPDATCFM:
               cmUnpkDamPdcpDatCfm(EuLiDamPdcpDatCfm, pst, mBuf);
               break;
             case EVTDAMCTXTRELREQ:
              cmUnPkDamSendCtxtRel(EuLiDamSendCtxtRel,pst,mBuf);
               break;
             case EVTDAMEGTERRIND:
              cmUnpkEgtpErrInd(EuLiDamEgtpErrInd,pst,mBuf);
               break;
             case EVTDAMBNDCFM:
               (Void)cmUnpkDamBndCfm(EuLiDamBndCfm, pst, mBuf);
               break;
#ifndef TIP_L3_UL2_LL2_SPLIT
             case EVTDAMCFGCFM:
               cmUnpkDamCfgCfm(pst, mBuf);
               break;
             case EVTDAMCNTRLCFM:
               cmUnpkDamCntrlCfm(pst, mBuf);
               break;
             case EVTDAMALARMIND:
               cmUnpkDamSendAlarmInd(pst, mBuf);
               break;
#endif
             default:
               RLOG0(L_ERROR,"Unknown event from DAM");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;

#ifdef EU_DAT_APP
#ifndef LTE_ENB_PERF
#endif
      case ENTWR:
         switch (pst->event)
         {
            default:
               RLOG0(L_ERROR, "wrActvTsk: Unknown event from internal\
                        EU Interface");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;
/*RRM_FSM: Changes for change of coupling*/
#ifdef RM_INTF
      case ENTRM:
         switch (pst->event)
         {
            case EVTRMUCELLRECFGIND:
            {        
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                     cmUnpkRmuCellRecfgInd(WrLiRmuCellRecfgInd, pst, mBuf);
                     break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                     cmUnpkLwLcRmuCellReCfgInd(WrLiRmuCellRecfgInd, pst, mBuf);
                     break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                     cmUnpkNoPkRmuCellRecfgInd(WrLiRmuCellRecfgInd, pst, mBuf);
                     break;
#endif
                  default:
                     RLOG2(L_ERROR, "ENTRM: Rcvd event %d and selector %d ",pst->event, pst->selector);
                     SPutMsg(mBuf);
                     break;
               }
            }
            break;
            case EVTRMUUERECFGIND:
            {        
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                     cmUnpkRmuUeRecfgInd(WrLiRmuUeRecfgInd, pst, mBuf);
                     break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                     cmUnpkLwLcRmuUeReCfgInd(WrLiRmuUeRecfgInd, pst, mBuf);
                     break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                     cmUnpkNoPkRmuUeRecfgInd(WrLiRmuUeRecfgInd, pst, mBuf);
                     break;
#endif
                  default:
                     RLOG2(L_ERROR, "ENTRM: Rcvd event %d and selector %d ",pst->event, pst->selector);
                     SPutMsg(mBuf);
                     break;
               }
            }
            break;
            case EVTRMUUEADMITRSP:
            {
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                  cmUnpkRmuUeAdmitRsp(WrLiRmuUeAdmitRsp, pst, mBuf);
                  break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                  cmUnpkLwLcRmuUeAdmitRsp(WrLiRmuUeAdmitRsp, pst, mBuf);
                  break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                  cmUnpkNoPkRmuUeAdmitRsp(WrLiRmuUeAdmitRsp, pst, mBuf);
                  break;
#endif
                  default:
                  SPutMsg(mBuf);
                  break;
               }
            }
            break;
            case EVTRMUUEHORSP:
            {
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                     cmUnpkRmuUeHoRsp(WrLiRmuUeHoRsp, pst, mBuf);
                     break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                     cmUnpkLwLcRmuUeHoRsp(WrLiRmuUeHoRsp, pst, mBuf);
                     break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                     cmUnpkNoPkRmuUeHoRsp(WrLiRmuUeHoRsp, pst, mBuf);
                     break;
#endif
                  default:
                     SPutMsg(mBuf);
                     break;
               }
            }
            break;
            case EVTRMUUERELRSP:
            {
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                     cmUnpkRmuUeRelRsp(WrLiRmuUeRelRsp, pst, mBuf);
                     break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                     cmUnpkLwLcRmuUeRelRsp(WrLiRmuUeRelRsp, pst, mBuf);
                     break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                     cmUnpkNoPkRmuUeRelRsp(WrLiRmuUeRelRsp, pst, mBuf);
                     break;
#endif
                  default:
                     SPutMsg(mBuf);
                     break;
               }
            }
            break;
            case EVTRMUUERELIND:
            {
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                     cmUnpkRmuUeRelInd(WrLiRmuUeRelInd, pst, mBuf);
                     break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                     cmUnpkLwLcRmuUeRelInd(WrLiRmuUeRelInd, pst, mBuf);
                     break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                     cmUnpkNoPkRmuUeRelInd(WrLiRmuUeRelInd, pst, mBuf);
                     break;
#endif
                  default:
                     SPutMsg(mBuf);
                     break;
               }
            }
            break;
            case EVTRMUUERECFGRSP:
            {
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                     cmUnpkRmuUeRecfgRsp(WrLiRmuUeRecfgRsp, pst, mBuf);
                     break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                     cmUnpkLwLcRmuUeRecfgRsp(WrLiRmuUeRecfgRsp, pst, mBuf);
                     break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                     cmUnpkNoPkRmuUeRecfgRsp(WrLiRmuUeRecfgRsp, pst, mBuf);
                     break;
#endif
                  default:
                     SPutMsg(mBuf);
                     break;
               }
            }
            break;
            case EVTRMUUEERABRELIND:
            {
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                     cmUnpkRmuUeERabRelInd(WrLiRmuUeERabRelInd, pst, mBuf);
                     break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                     cmUnpkLwLcRmuUeERabRelInd(WrLiRmuUeERabRelInd, pst, mBuf);
                     break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                     cmUnpkNoPkRmuUeERabRelInd(WrLiRmuUeERabRelInd, pst, mBuf);
                     break;
#endif
               }
            }
            break;
            case EVTRMUBNDCFM:
            {
               switch(pst->selector)
               {
                  case RMU_SEL_LC:
                     cmUnpkRmuBndCfm(WrLiRmuBndCfm, pst, mBuf);
                     break;
#ifdef RMU_LWLC
                  case RMU_SEL_LWLC:
                     cmUnpkLwLcRmuBndCfm(WrLiRmuBndCfm, pst, mBuf);
                     break;
#endif
#ifdef RMU_NPLC
                  case RMU_SEL_NPKLC:
                     cmUnpkNoPkRmuBndCfm(WrLiRmuBndCfm, pst, mBuf);
                     break;
#endif
                  default:
                     SPutMsg(mBuf);
                     break;
               }
            }
            break;
            default:
            SPutMsg(mBuf);
            break;
         }
         break; /* Break for case ENTRM */
#endif /*RM_INTF*/
      case ENTNL:
      {
         switch(pst->event)
         {
            case EVTNLUBNDCFM :
            {
               cmUnpkNluBndCfm(WrLiNluBndCfm, pst, mBuf);
            }
            break;
            default :
            {
               RLOG0(L_ERROR, "wrActvTsk: Received Invalid event from SON \n");
               (Void)SPutMsg(mBuf);
            }
            break;
         }
      }
      break;

#endif /* EU_DAT_APP */

      default:
         RLOG0(L_ERROR, "wrActvTsk: Received Msg From Unknow Src.");
         (Void)SPutMsg(mBuf);
         break;
   }

   (Void)SExitTsk();
   RETVALUE(ROK);
} /* end of wrActvTsk() */

#endif



/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
