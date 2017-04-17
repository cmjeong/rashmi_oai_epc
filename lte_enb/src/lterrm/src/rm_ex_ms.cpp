
/********************************************************************20**

     Name:     RRM Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     rm_ex_ms.c

     Sid:      qf_ex_ms.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:33 2013

     Prg:     jbm 

*********************************************************************21*/

/* header include files */
#include "rm_cmn.h"
#include "rgm.x"
/*
 *
 *       Fun:    rmActvTsk - RRC user activation
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   rm_ex_ms.c
 *
 */

PUBLIC S16 rmActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
{
   Mem sMem;
   Size     maxBlkSize;
   maxBlkSize = RM_MEM_PDU_SIZE;

   TRC3(rmActvTsk);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (pst == (Pst *)NULLP)
   {
//    RM_DBG_ERROR((RM_PRNT_BUF,"rmActvTsk: Invalid Pst \n"));
      if (mBuf != (Buffer *)NULLP)
      {
         (Void)SPutMsg(mBuf);
      }

      RETVALUE(RFAILED);
   }

   if (mBuf == (Buffer *)NULLP)
   {
//      RM_DBG_ERROR((RM_PRNT_BUF,"rmActvTsk: Invalid MBuf \n"));
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   /* Assigning the proper region */
   sMem.region = g_stRmCb.rmInit.region;
   sMem.pool   = RM_MEM_POOL;

   switch (pst->srcEnt)
   {
      case ENTSM:
         switch (pst->event)
         {
	    #ifdef LWLCSMRMMILRM	
            case EVTLRMCFGREQ:
               cmUnpkLwLcLrmCfgReq(RmMiLrmCfgReq, pst, mBuf);
               break;
            case EVTLRMCNTRLREQ:
               cmUnpkLwLcLrmCntrlReq(RmMiLrmCntrlReq, pst, mBuf);
               break;
            case EVTLRMENBSTAIND:
               cmUnpkLwLcLrmEnbStaInd(RmMiLrmEnbStaInd, pst, mBuf);
               break;
	    #endif 

            default:
#ifdef DEBUGP
//               RM_DBG_ERROR((RM_PRNT_BUF,"rmActvTsk: Unknown Event from SM\n"));
#endif
               (Void)SPutMsg(mBuf);
               break;
         }
         break;

      case ENTEU: 
         switch(pst->event)
         {
               /*RRM_SP3*/
            case EVTRMUUEINACTIND:
               {
                  cmUnpkLwLcRmuUeInactInd (RmUiRmuUeInactInd, pst, mBuf);
                  break;
               }
            default:
#ifdef DEBUGP
//               RM_DBG_ERROR((RM_PRNT_BUF,"rmActvTsk: Unknown Evnt from ENTEU.\n"));
#endif
               (Void)SPutMsg(mBuf);
               break;
         }
         break;

      case ENTWR: 
         switch(pst->event)
         {
         	case EVTRMUBNDREQ:
         	   cmUnpkLwLcRmuBndReq(RmUiRmuBndReq, pst, mBuf);
         	   break;
            case EVTRMUUEADMITREQ:
            	cmUnpkLwLcRmuUeAdmitReq (RmUiRmuUeAdmitReq, pst, mBuf);
               break;
            case EVTRMUUEHOREQ:
               cmUnpkLwLcRmuUeHoReq (RmUiRmuUeHoReq, pst, mBuf);
               break;
            case EVTRMUUERELREQ:
               cmUnpkLwLcRmuUeRelReq (RmUiRmuUeRelReq, pst, mBuf);
               break;
            case EVTRMUUERECFGREQ:
               cmUnpkLwLcRmuUeRecfgReq (RmUiRmuUeRecfgReq, pst, mBuf);
               break;
            case EVTRMUOVLDSTRTIND:
               cmUnpkLwLcRmuMmeOvldStartInd (RmUiRmuMmeOvldStartInd, pst, mBuf);
               break;
            case EVTRMUOVLDSTPIND:
               cmUnpkLwLcRmuMmeOvldStopInd (RmUiRmuMmeOvldStopInd, pst, mBuf);
               break;
            case EVTRMUFSMSTAIND:
               cmUnpkLwLcRmuFsmStatusInd (RmUiRmuFsmStatusInd, pst, mBuf);
               break;
            case EVTRMUUESPSDISIND:
               cmUnpkLwLcRmuUeSpsDisInd (RmUiRmuUeSpsDisInd, pst, mBuf);
               break;
            default:
#ifdef DEBUGP
//               RM_DBG_ERROR((RM_PRNT_BUF,"rmActvTsk: Unknown Evnt from NHU.\n"));
#endif
               (Void)SPutMsg(mBuf);
               break;
         }
         break;

      case ENTRG:
         switch (pst->event)
         {
      	    case EVTRGMBNDCFM:
      	       cmUnpkRgmBndCfm(RmLiRgmBndCfm, pst, mBuf);
      	       break;
             case EVTRGMPRBRPRTIND:
               cmUnpkRgmPrbRprtInd (RmLiRgmPrbRprtInd, pst, mBuf);
               break;
      	    case EVTRGMTRANSMODEIND:
      	       cmUnpkRgmTransModeInd(RmLiRgmTransModeInd, pst, mBuf);
      	       break;
            default:
#ifdef DEBUGP
//               RM_DBG_ERROR((RM_PRNT_BUF,"rmActvTsk: Unknown event from RGR\n"));
#endif
               (Void)SPutMsg(mBuf);
               break;
         } 
         break;

      default:
#ifdef DEBUGP
//         RM_DBG_ERROR((RM_PRNT_BUF,"rmActvTsk: Received Msg From Unknow Src.\n"));
#endif
         (Void)SPutMsg(mBuf);
         break;
   }

   (Void)SExitTsk();
   RETVALUE(ROK);
} /* end of rmActvTsk() */



/********************************************************************30**

           End of file:     qf_ex_ms.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:33 2013

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
*********************************************************************91*/
