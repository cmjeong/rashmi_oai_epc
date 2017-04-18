

/************************************************************************
 
     Name:     LTE UE Simulator
  
     Type:     C source file
  
     Desc:     C source code for UE SIM Upper interface for dummy RRC
  
     File:     ue_uim.c
  
     Sid:      ue_uim.c@@/main/1 - Sun Mar 28 22:59:26 2010
  
     Prg:      vp
  
**********************************************************************/

/* header include files -- defines (.h) */
#include <sched.h>
#include <sys/time.h>
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#include "pcap.h"       /* common tokens */
#endif /* SS_CAVIUM */
/* ue007.101: cavium compile warning fix */
#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-wqe.h"
#endif /* SS_CAVIUM */

#include "cm_pasn.h"        /* common LTE */
#include "nhu_asn.h"
#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
#include "tfu.h"
#include "nhu.h"
#include "ue.h"            /* UE Includes */
#include "ue_err.h"

/* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
#include "LtePhyL2Api.h" /* Phy api file */
#include "apidefs.h"     /* Phy api file */
#include "resultcodes.h" /* Phy api file */
#endif
/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"       /* common tokens */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_pasn.x"        /* common LTE */
#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* UE App Interface with RRC */
#include "cm_emm.x"        /* EMM Defines */
#include "cm_esm.x"        /* ESM Defines */
#include "cm_emm_esm.x"    /* EMM-ESM Defines */
#include "ue_app.x"        /* UE application includes */
#include "tfu.x"
#include "ue.x"            /* UE Includes */
#include "ue_pju_app.x"

#ifdef LTE_START_UL_DL_DATA
PUBLIC U32 recvPkt = 0;
#endif /* LTE_START_UL_DL_DATA */

/* ue002.101: Multi ue support on uu interface */
#ifdef ENB_PERF_MEAS
PUBLIC U32 ueAppNumRecfgComplSent;
#endif

PRIVATE S16 ueHdlUlDcchDatReq ARGS((NhuDatReqSdus *datReqSdus, 
                                     U16 cellId, U16 ueId));

PRIVATE S16 ueHdlUlCcchDatReq ARGS((NhuDatReqSdus *datReqSdus,
                                   U16 cellId, U16 ueId));


/* 
 *
 *       Fun:    UeUiNhuDatReq 
 * 
 *       Desc:   Processes the RRC data request for SRB0, SRB1 and SRB2.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_uim.c
 *
 */
#ifdef ANSI
PUBLIC S16 UeUiNhuDatReq
(
Pst           *pst,              
SpId           spId,             
NhuDatReqSdus *datReqSdus,
U16            cellId,
U16            ueId
)
#else
PUBLIC S16 UeUiNhuDatReq(pst, spId, datReqSdus, cellId, ueId)
Pst           *pst;           
SpId           spId;         
NhuDatReqSdus *datReqSdus;
U16            cellId;
U16            ueId;
#endif
{
   S16  ret = ROK;

   TRC2(UeUiNhuDatReq)
   
   UE_DBGP_INFO((UE_PRNTBUF, 
      "UeUiNhuDatReq :Received a RRC message of category %d ",
       datReqSdus->sdu.msgCategory));

   /* ue002.101: Multi ue support changes */
   switch(datReqSdus->sdu.msgCategory)
   {
      case NHU_MSG_ULCCCH:
      {
         ret = ueHdlUlCcchDatReq(datReqSdus, cellId, ueId);
         break;
      }
      case NHU_MSG_ULDCCH:
      {
         ret = ueHdlUlDcchDatReq(datReqSdus, cellId, ueId);
         break;
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE123, (ErrVal)datReqSdus->sdu.msgCategory,
            "UeUiNhuDatReq:  Unknown RRC Data Request msg category \n");
         break;
      }
   } 

   UE_RRC_FREE_EVNT(datReqSdus);
   RETVALUE(ret);
}

/* ue008.101: Added new parameter lcId in UeUiPjuDatReq() */
/* 
 *
 *       Fun:    UeUiPjuDatReq 
 * 
 *       Desc:   Processes the PDCP data request for SRB1 and SRB2.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_uim.c
 *
 */
#ifdef ANSI
PUBLIC S16 UeUiPjuDatReq
(
Pst    *pst,
SpId   spId,
Buffer *mBuf,
U16     cellId,
U16     ueId,
U8      lcId
)
#else
PUBLIC S16 UeUiPjuDatReq(pst, spId, mBuf, cellId, ueId,lcId)
Pst    *pst;
SpId   spId;
Buffer *mBuf;
U16    cellId;
U16    ueId;
U8     lcId;
#endif
{
   CellCb  *cell;
   UeCb    *ueCb;
   
   TRC2(UeUiPjuDatReq)

   UE_DBGP_INFO((UE_PRNTBUF, 
      "UeUiPjuDatReq :Sending a DATA PDU to RLC "));
   
   ueUtlFndCell(cellId, &cell);
   if (cell == NULLP)
   {
       printf("cell not found\n");
       RETVALUE(RFAILED);
   }
   
   ueUtlFndUe(cell,ueId, &ueCb);


/* ue002.101: Multi ue support on uu interface */
   ueRlcDatReq(ueCb, lcId, mBuf);

   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueHdlUlDcchDatReq 
 * 
 *       Desc:   Processes the DCCH data from Application.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_uim.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueHdlUlDcchDatReq
(
NhuDatReqSdus *datReqSdus,
U16            cellId,
U16            ueId
)
#else
PRIVATE S16 ueHdlUlDcchDatReq(datReqSdus, cellId, ueId)
NhuDatReqSdus *datReqSdus;
U16            cellId;
U16            ueId;
#endif
{
   CellCb      *cell;
   U8           msgType;
   Buffer      *sendBuf;
   S16          ret;
   NhuUlDcchMsg *ulDcchPdu = NULLP;
   UeCb         *ueCb = NULLP;

   TRC2(ueHdlUlDcchDatReq)

   ulDcchPdu = &datReqSdus->sdu.m.ulDcchMsg;
   msgType = ulDcchPdu->dcchMsg.message.val.c1.choice.val;


   UE_DBGP_INFO((UE_PRNTBUF, 
     "ueHdlUlDcchDatReq:msgType %d ",msgType));

   ueUtlFndCell(cellId, &cell);

   if (cell == NULLP)
   {
      printf("ueHdlUlDcchDatReq: cell Not found for cellId \n", cellId);
      RETVALUE(RFAILED);
   }

   switch(msgType)
   {
#ifdef TOTAL_ENB
   /* ue009.101: Added feature to drop the diffrent RRC messages.
    *  depends on the RRC timer. */
      case C1_RRCCONREESTBCOMPL:
#endif
      case C1_RRCCONSETUPCOMPL:
      case C1_SECURITYMODECOMPL: /* RRC Security Mode Complete */
      case C1_ULINFOTFR: /* Uplink Information Transfer */
/* ue005.101: Added support for UeCapability */
#ifdef UE_RAD_CAP
      case C1_UECAPINFO: /* Ue Capability info */
#endif
         break;
      
   /* ue002.101: Multi ue support changes */
      case C1_RRCCONRECFGNCOMPL: /* RRC Reconfiguration Request Complete */
#ifdef ENB_PERF_MEAS         
         ueAppNumRecfgComplSent++;
         if (ueAppNumRecfgComplSent == UE_NUM_PER_CELL)
         {
            ueAppCellCb.state = UE_STATE_SIGNALLING_COMPLETED; /*Ready to generate UP Link data*/
         }
#endif
         break;
         /* ue008.101: Added new case C1_MEASUREMENTREPORT for
          * Encoding Measurement Report. */
      case C1_MEASUREMENTREPORT:
         printf("\n Encoding Measurement Report\n");
         break;

      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE124, (ErrVal)msgType,
            "ueHdlUlDcchDatReq:Unrecognized message for Uplink DCCH \n");
         RETVALUE(RFAILED);
      }
   }

   ret = ueRrcEncRRCMsg(NHU_MSG_ULDCCH, datReqSdus, &sendBuf);

   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE125, (ErrVal)msgType,
        "ueHdlUlDcchDatReq: Encoding RRC SDU failed for message type \n");
      RETVALUE(RFAILED);
   }

   if (ueUtlFndUe(cell,ueId, &ueCb) != ROK)
   {
/* ue003.101: ueId variable change */
      UE_DBGP_INFO((UE_PRNTBUF, 
            "RgLiTfuDatReq: Could not find UE with rnti %d ",ueId));
      printf("ueHdlUlDcchDatReq: Ue not Found: ueId = %d\n", ueId);
      RETVALUE(RFAILED);
   }

   /* We have the successful RRC Message encoded buffer to send to eNodeB */
   /* ue002.101: Multi ue support changes */
   ueRlcDatReq(ueCb, 1, sendBuf);
   
   RETVALUE(ret);
} /* end of ueHdlUlDcchDatReq*/

/* 
 *
 *       Fun:    ueHdlUlCcchDatReq 
 * 
 *       Desc:   Processes the CCCH data from Application.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_uim.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueHdlUlCcchDatReq
(
NhuDatReqSdus *datReqSdus,
U16            cellId,
U16            ueId
)
#else
PRIVATE S16 ueHdlUlCcchDatReq(datReqSdus, cellId, ueId)
NhuDatReqSdus *datReqSdus;
U16            cellId;
U16            ueId;
#endif
{
   CellCb      *cell;
   U8           msgType;
   Buffer      *sendBuf;
   S16          ret = ROK;
   U16          rnti;  
   UeCb         *ueCb = NULLP;

   NhuUlCcchMsg *ulCcchPdu;

   TRC2(ueHdlUlCcchDatReq)

   ueUtlFndCell(cellId, &cell);
   if (cell == NULLP)
   {
      printf("ueHdlUlDcchDatReq: cell Not found for cellId \n", cellId);
      RETVALUE(RFAILED);
   }

   rnti = cell->startRnti;


   ulCcchPdu = &datReqSdus->sdu.m.ulCcchMsg;
   msgType = ulCcchPdu->ccchMsg.message.val.c1.choice.val;

   UE_DBGP_INFO((UE_PRNTBUF, 
     "ueHdlUlCcchDatReq: msgChoice %d ",msgType));

   /* ue002.101: Multi ue support changes */
   if (ueUtlFndUe(cell,ueId, &ueCb) != ROK)
   {
      /* Print Error here and go to the next ulAlloc */
      UELOGERROR(ERRCLS_ADD_RES, EUE094, (ErrVal)0,
         "RgLiTfuCntrlReq: Allocation failed for UE control block\n");
      printf("Could not find Uecb for UeId = %d\n", ueId);
      RETVALUE(RFAILED);
   }

   switch(msgType)
   {
      case C1_RRCCONRQST:
      {
         /* Get the encoded Connection Request message and add header */
         ret = ueRrcEncRRCMsg(NHU_MSG_ULCCCH, datReqSdus, &sendBuf);
         if(ROK != ret)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE126, (ErrVal)0,
               "ueHdlUlCcchDatReq: Encoding RRC SDU failed for RRC ConReq \n");
            RETVALUE(RFAILED);
         }

         /* ue002.101: Multi ue support changes */
         ueRlcDatReq(ueCb, 0, sendBuf);

         break;
      } 
      case C1_RRCCONSETUPCOMPL: /* RRC Connection Setup Complete */
      {
         /* Get the encoded setup complete message and add header */
         ret = ueRrcEncRRCMsg(NHU_MSG_ULCCCH, datReqSdus, &sendBuf);
         if(ROK != ret)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE127, (ErrVal)0,
               "ueHdlUlCcchDatReq:Encoding RRC SDU failed for RRC SetUpComp\n");
            RETVALUE(RFAILED);
         }

         /* ue002.101: Multi ue support changes */
         ueRlcDatReq(ueCb, 1, sendBuf);

         break; 
      }
#ifdef TOTAL_ENB
   /* ue009.101: Added feature to drop the diffrent RRC messages.
    *  depends on the RRC timer. */
      /* RRC RE-EST start */
      case C1_RRCCONREESTBRQST:
      {
         /* Get the encoded setup complete message and add header */
         ret = ueRrcEncRRCMsg(NHU_MSG_ULCCCH, datReqSdus, &sendBuf);
         if(ROK != ret)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE127, (ErrVal)0,
               "ueHdlUlCcchDatReq:Encoding RRC SDU failed for RRC SetUpComp\n");
            RETVALUE(RFAILED);
         }

         /* ue002.101: Multi ue support changes */
         ueRlcDatReq(ueCb, 1, sendBuf);

         break; 
      }

      /* RRC RE-EST start */
      case C1_RRCCONREESTBCOMPL:
      {
         /* Get the encoded setup complete message and add header */
         ret = ueRrcEncRRCMsg(NHU_MSG_ULCCCH, datReqSdus, &sendBuf);
         if(ROK != ret)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE127, (ErrVal)0,
               "ueHdlUlCcchDatReq:Encoding RRC SDU failed for RRC SetUpComp\n");
            RETVALUE(RFAILED);
         }

         /* ue002.101: Multi ue support changes */
         ueRlcDatReq(ueCb, 1, sendBuf);

         break; 
      }

      break;
      /* RRC RE-EST end */
#endif /* #ifdef TOTAL_ENB */
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE128, (ErrVal)msgType,
            "ueHdlUlCcchDatReq:Invalid msgType\n");
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ret);

} /* end of ueHdlUlCcchDatReq */

/* 
 *
 *       Fun:    ueDapDatInd
 * 
 *       Desc:   Processes the Data from lower layers.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_uim.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueDapDatInd
(
UeCb   *ueCb, 
U8     lcId, 
Buffer *mBuf
)
#else
PUBLIC S16 ueDapDatInd(ueCb,lcId,mBuf)
UeCb   *ueCb;
U8     lcId;
Buffer *mBuf;
#endif
{
   /* ue008.101: Added new variables for HandOver Support*/
#ifdef LTE_HO_SUPPORT    
   NhuDatReqSdus **measPdu = NULLP;
   S16 ret;
   PRIVATE U32 count = 1;
#endif
   UeAppCb     *ueAppCb = NULLP;
   
   TRC2(ueDapDatInd)

   UE_DBGP_INFO((UE_PRNTBUF, 
     "ueDapDatInd: Application received data from RLC  "));
/* ue003.101: printing lcid */
/* ue006.101: Changed printf to UE_DBG_INFO */
   UE_DBGP_INFO((UE_PRNTBUF, "\n Recvd Data on lcId:%d",lcId ));  
#ifdef LTE_START_UL_DL_DATA
   MsgLen len  = 0;
   SPrntMsg(mBuf,0,0);
#endif

   /* ue002.101: Multi ue support changes for uu interface */
#ifndef LTE_START_UL_DL_DATA
#ifndef ENB_PERF_MEAS
  UeAppLiPjuDatInd(NULLP,0,mBuf,ueCb->cellId,ueCb->ueId);
#else
#ifndef UESIM_ENABLE_PCAP 
  UePerfAppLiPjuDatInd(NULLP,0,mBuf,ueCb->cellId,ueCb->ueId);
#else   /* ENB_PERF_MEAS & UESIM_ENABLE_PCAP */
  UeAppLiPjuDatInd(NULLP,0,mBuf,ueCb->cellId,ueCb->ueId);
#endif


#endif /* ENB_PERF_MEAS */
#else
   SFndLenMsg(mBuf,&len);

   recvPkt++;

   SPutMsg(mBuf);
   mBuf = NULLP;
#endif /* LTE_START_UL_DL_DATA */

   /* ue008.101: HandOver Support.*/
   UE_GET_APPCB(ueCb->cellId,ueAppCb,ueCb->rnti);

#ifdef LTE_HO_SUPPORT
   if( ueAppCb != NULLP)
   { 
#ifdef TOTAL_ENB
      /* Sending Measurement Report. */
/* ue009.101 : Changes to send the measurement report */
      if(count++ == 5)
      {
         ret = ueRrcBuildMeasRpt(ueAppCb, &measPdu);
#else /* #ifdef TOTAL_ENB */
   /* Sending Measurement Report. */
      if(count++ == 1)
      {
         ret = ueRrcBuildMeasRpt(&measPdu);
#endif /* #ifdef TOTAL_ENB */

         if(ROK != ret)
         {
            RETVALUE(RFAILED);
         }

         RETVALUE(ueAppLimSndRRCMsg(measPdu, ueAppCb));
      } /* end of if statement */
   } /* end of if statement */
#endif
  RETVALUE(ROK);
}



/**********************************************************************
 
         End of file:     ue_uim.c@@/main/1 - Sun Mar 28 22:59:26 2010
 
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
/main/1      ---      vp             1. Initial Release.
/main/1+   ue002.101  sv             1. Multi ue support changes.
                                     2. Changes to support MSPD CL.
/main/1+   ue003.101  sv             1. Dedic bearer support changes.
/main/1+   ue005.101  cshekar        1. Added support for ue capability.
/main/1+   ue006.101  sriky          1. Performance tuning
/main/1+   ue007.101  rk             1. Cavium warning fix
/main/1+   ue008.101 ragrawal        1 .Added new parameter lcId in UeUiPjuDatReq(). 
                                     2. Added HandOver Support.
/main/1+   ue009.101 akaranth        1 .Added support drop RRC messages, depends on the RRC timer.
                                     2. Changes to send the measurement report.
*********************************************************************91*/

