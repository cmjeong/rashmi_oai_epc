

/************************************************************************
 
     Name:     LTE UE Simulator
  
     Type:     C source file
  
     Desc:     C source code for Utilities
  
     File:     ue_utl.c
  
     Sid:      ue_utl.c@@/main/1 - Sun Mar 28 22:59:27 2010
  
     Prg:      vp
  
**********************************************************************/

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#include "cm_pasn.h"        /* common LTE */
#ifndef SS_CAVIUM
#include "pcap.h"       /* common tokens */
#endif /* SS_CAVIUM */
/* ue007.101: cavium compile warning fix */
#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-wqe.h"
#endif /* SS_CAVIUM */

#include "nhu_asn.h"
#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
#include <sys/time.h>
#include "tfu.h"
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
#include "cm_pasn.x"        /* common LTE */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */
#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* UE App Interface with RRC */
#include "cm_emm.x"        /* EMM Defines */
#include "cm_esm.x"        /* ESM Defines */
#include "cm_emm_esm.x"    /* EMM-ESM Defines */
#include "ue_app.x"        /* UE application includes */
#include "tfu.x"
#include "ue.x"            /* UE Includes */

/* ue008.101 : TIC_ID : ccpu00117550 ADD: Fixed warning for gcc compilation on CentOS*/
#include <stdlib.h>

/* ue008.101 : ADD : Fixed error for g++ compilation on CentOS*/
#ifndef SS_CAVIUM
#ifdef __cplusplus
EXTERN "C" {
#endif
/* ue008.101 : ADD_END : Fixed error for g++ compilation on CentOS*/

EXTERN S16 SRegInfoShow  ARGS((Region region, U32 *availmem));

/* ue008.101 : ADD : Fixed error for g++ compilation on CentOS*/
#ifdef __cplusplus   
}
#endif
#endif /*SS_CAVIUM */
/* ue008.101 : ADD_END : Fixed error for g++ compilation on CentOS*/

/* ue008.101 : TIC_ID : ccpu00117550 ADD_END: Fixed warning for gcc compilation on CentOS*/

/* 
 *
 *       Fun:    ueUtlFndCell
 * 
 *       Desc:   This functions finds a UE in the cell.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_utl.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueUtlFndCell
(
U16          cellId,
CellCb      **cell
)
#else
PUBLIC S16 ueUtlFndCell(cellId,cell)
U16         cellId;
CellCb     **cell;
#endif
{
   U16      cellIdx;
   S16      ret;

   TRC2(ueUtlFndCell)

   for (cellIdx=0; cellIdx < UE_NUM_CELL; cellIdx++)
   {
       if (cellId == cellArr[cellIdx].cellId)
       {
           *cell = &cellArr[cellIdx];
           ret = ROK;
           break;
       }
   }

   if (cellIdx == UE_NUM_CELL)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE129, (ErrVal)cellId,
      "ueUtlFndCell: CellCb not found for cellid \n");
      *cell = NULLP;
      ret = RFAILED;
   }

   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueUtlFndUe
 * 
 *       Desc:   This functions finds a UE in the cell.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_utl.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueUtlFndUe
(
CellCb      *cell,
U16         crnti,
UeCb        **ueCb
)
#else
PUBLIC S16 ueUtlFndUe(cell,crnti,ueCb)
CellCb     *cell;
U16         crnti;
UeCb       **ueCb;
#endif
{
   S16      ueIdx;

   TRC2(ueUtlFndUe)

   /* ue002.101: Multi ue support changes */
   if (crnti < cell->startRnti)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE129, (ErrVal)crnti,
      "ueUtlFndUe: ueCb not found for crnti \n");
      *ueCb = NULLP;
      RETVALUE(RFAILED);
   }
   else
   {
      /* ue003.101: correction to ueIdx calculation */
      ueIdx = (UE_NUM_PER_CELL > 1)? (crnti - UE_START_RNTI): 0;
      if (ueIdx < 0)
      {
         printf("ueUtlFndUe: ueIdx less than zero \n");
         *ueCb = NULLP;
         RETVALUE(RFAILED);
      }
      *ueCb = &cell->ueArr[ueIdx];
      RETVALUE(ROK);
   }
}

/* 
 *
 *       Fun:    ueUtlInit
 * 
 *       Desc:   This functions initializes a UE.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_utl.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueUtlInit
(
Void
)
#else
PUBLIC S16 ueUtlInit(void)
#endif
{
   U16             cellIdx;
   S16             idx;

   TRC2(ueUtlInit)

   UE_DBGP_INFO((UE_PRNTBUF, 
     "ueUtlInit: Initializinf the preamble and rnti  "));

   for (cellIdx = 0; cellIdx < UE_NUM_CELL; cellIdx ++)
   {
      for (idx = 0; idx < UE_NUM_PER_CELL; idx++)
      {
         cellArr[cellIdx].ueArr[idx].mac.preambleId = 0xff;
         cellArr[cellIdx].ueArr[idx].rnti           = 0xffff;
      }
   }
   RETVALUE(ROK);
}
#ifdef TOTAL_ENB
/* ue009.101: Added feature to drop the diffrent RRC messages.
 *  depends on the RRC timer. */
/* CLI For HO & TU: Start */
 /* 
 *
 *       Fun:    ueSndMesurMntRpt
 * 
 *       Desc:   This function will send the mesurement report
 *                message
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_utl.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueSndMesurMntRpt
(
Void
)
#else
PUBLIC S16 ueSndMesurMntRpt(Void)
#endif
{
   UeAppCb        *ueAppCb = NULLP;
   NhuDatReqSdus **measPdu = NULLP;
   S16             idx;
   S16             ret;
   Buffer         *sendBuf = NULLP;
   CellCb         *cellCb = NULLP;
   UeCb           *ueCb = NULLP;

   TRC2(ueSndMesurMntRpt);

   for(idx = 0; idx < UE_NUM_PER_CELL; idx++)
   {
#if 0
      ueAppCb = &(ueAppCellCb.ueAppCbLst[idx]);
#endif
      if(ueAppCb != NULLP)
      {
         break;
      }
   }

   if(idx == UE_NUM_PER_CELL)
   {
      printf("\n Not able to find any UE connected state\n");
      RETVALUE(RFAILED);
   }
   /* ue010.101 : Enhanced measurement feature.
    * This function should not call while running 
    * with Enb Refrence application */
#ifndef TOTAL_ENB 
   ret = ueRrcBuildMeasRpt(ueAppCb, &measPdu);
#endif

   if(ROK != ret)
   {
      printf("\n Failed to build the Mesurment Report msg\n");
      RETVALUE(RFAILED);
   } 

   RETVALUE(ueAppLimSndRRCMsg(measPdu, ueAppCb)); 


   RETVALUE(ROK);
} 
/* CLI For HO & TU: End */

/* RRC Re-Est Start */
/* 
 *
 *       Fun:    ueSndRrcReEstReqMsg
 * 
 *       Desc:   This function will send the RRC re-establishment message from
 *               first UE connected to eNB.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_utl.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueSndRrcReEstReqMsg
(
Void
)
#else
PUBLIC S16 ueSndRrcReEstReqMsg(Void)
#endif
{
   UeAppCb        *ueAppCb = NULLP;
   NhuDatReqSdus  *rrcReestPdu = NULLP;
   S16             idx;
   S16             ret;
   Buffer         *sendBuf = NULLP;
   CellCb         *cellCb = NULLP;
   UeCb           *ueCb = NULLP;

   TRC2(ueSndRrcReEstReqMsg);

   for(idx = 0; idx < UE_NUM_PER_CELL; idx++)
   {
#if 0
      ueAppCb = &(ueAppCellCb.ueAppCbLst[idx]);
#endif

      if(ueAppCb != NULLP)
      {
         break;
      }
   }

   if(idx == UE_NUM_PER_CELL)
   {
      printf("\n Not able to find any UE connected state\n");
      RETVALUE(RFAILED);
   }

   ret = ueAppUtlBldRRCReEstlmntReqMsg(&rrcReestPdu, ueAppCb);
   if(ROK != ret)
   {
      printf("\n Failed to build the RRC Re-Est msg\n");
      RETVALUE(RFAILED);
   }
   ret = ueRrcEncRRCMsg(NHU_MSG_ULCCCH, rrcReestPdu, &sendBuf);
   if(ROK != ret)
   {
      printf("\n Failed to build the RRC Re-Est msg\n");
      RETVALUE(RFAILED);
   }

   cellCb = &(cellArr[0]);
   ueCb   = &(cellCb->ueArr[(ueAppCb->ueId) - 61]);

   ueMacRachReq(cellCb, ueCb, sendBuf);

   RETVALUE(ROK);
}
/* RRC Re-Est End */
#endif /* #ifdef TOTAL_ENB */
/* 
 *
 *       Fun:    rdConQ
 * 
 *       Desc:   This is a dummy function.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_utl.c
 *
 */
#ifdef ANSI
PUBLIC S16 rdConQ
(
Data data
)
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   /* ue007.101: UESim Reading user key hit support */
   /* ue008.101: Fix for compilation warning in cavium platform */
#ifndef SS_CAVIUM
   U32  memAvail;
#endif
   /* ue008.101 : TIC_ID : ccpu00117550 DEL: Deleted unused variable for warning removal on CentOS*/
   U8          cellIdx;
   U8          ueIdx;
/* ue010.101: Enhanced sending of TAU request from CLI interface */
   U8           idx;
   UeAppCb  *_ueAppCellCb = NULLP;

   TRC2(rdConQ)

#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
   U32 memIndx;
#endif

   if ((data == 0x03) ||
         (data == 27))
   {
      printf("wrong key hit \n"); 
   }
   switch (data)
   {
/* ue007.101: cavium compile warning fix */
#ifndef SS_CAVIUM
      case 'm' :
      case 'M' :
#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
         for(memIndx = 0; memIndx < 4/* (SS_MAX_REGS)*/; memIndx++)
         {
            SRegInfoShow(memIndx, &memAvail);
            memAvail = 0;
         }
#else
         SRegInfoShow(DFLT_REGION, &memAvail);
#endif
         break;
#endif
      case 'q' :
      case 'Q' :
         /* Uninitilize cell */
         for(cellIdx=0; cellIdx< UE_NUM_CELL; cellIdx++)
         {
            /* Shutdown UESIM */
            ueMacDeInit(&cellArr[cellIdx]);
            
#if 0
            /* Uninitilize UE */
            for(ueIdx=0; ueIdx < UE_NUM_PER_CELL; ueIdx++)
            {
               CmLList           *lnk;
               UeCb    *ueCb;
               while(cellArr[cellIdx].rachLst.first != NULLP)
               {
                  lnk = cellArr[cellIdx].rachLst.first;
                  cmLListDelFrm(&cellArr[cellIdx].rachLst, lnk);
                  ueCb = (UeCb *)(lnk->node);
                  if(ueCb && ueCb->mac.msg3)
                  {
                     (Void)SPutMsg(ueCb->mac.msg3);
                     ueCb->mac.msg3 = NULLP;
                  }
               }
            } 
#endif
         }
         if(ueSimAppCb.rrcSapCb)
            UEAPP_FREE(ueSimAppCb.rrcSapCb, sizeof(UeAppNhuSapCb));
         if(ueSimAppCb.pdcpSapCb)
            UEAPP_FREE(ueSimAppCb.pdcpSapCb, sizeof(UeAppPjuSapCb));

#ifdef SS_MEM_LEAK_STS
         /* To find memory leak */
         SLogLkInfo();
#endif
/* ue007.101: cavium compile warning fix */
#ifndef SS_CAVIUM
         SRegInfoShow(DFLT_REGION, &memAvail);
#endif
         exit(0);
#ifdef TOTAL_ENB
/* ue009.101: Added CLI feature to send RRC-reEst, Mesurement report, TAU message. */
      case 'r':
      case 'R':
         printf("\n Entering in rdConQ for sending RRC-RE-Establish\n");
         ueSndRrcReEstReqMsg();
         break;
         /* CLI For HO & TU: Start */
      case 'h':
      case 'H':
         printf("\n Entering in rdConq for sending Measurement report \n");
         ueSndMesurMntRpt();
         break;
       /* ue010.101: Enhanced sending of TAU request from CLI interface. */
#ifdef TRACKING_AREA_UPDATE
       case 't' :
       case 'T' :
        printf("\n Sending TAU Request for a connected UE\n");
        for (idx = UE_START_RNTI; idx < UE_START_RNTI+UE_NUM_PER_CELL ; idx++)
         { 
            _ueAppCellCb = &ueAppCellCb.ueAppCbLst[idx - UE_START_RNTI];
            if ((_ueAppCellCb != NULLP) && (_ueAppCellCb->emmCb.state == UE_EMM_UE_REGISTERED))
              {
                ueAppSndTAURequest(_ueAppCellCb);
                printf("\n Sent TAU Request from UE[%d]\n",idx + UE_START_RNTI);
                break;
              }
          }
         break; 
#endif
#endif /* #ifdef TOTAL_ENB */
      default :
         break;
   }

   RETVALUE(ROK);
}

/**********************************************************************
 
         End of file:     ue_utl.c@@/main/1 - Sun Mar 28 22:59:27 2010
 
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
/main/1      ---      vp               1. Initial Release.
/main/1+   ue002.101  sv               1. Multi ue support changes.
                                       2. Changes to support MSPD CL.
/main/1+   ue003.101  rp               1. Dedic Bearer support changes.
/main/1+   ue007.101  rk               1. UESim shutdown support.
                                       2. UESim memory usage support.
                                       3. Cavium compilation error fix
/main/1+   ue008.101  ragrawal         1. TIC_ID :ccpu00117550 Fixed warning for 
                                          gcc and g++ compilation on CentOS.
                                       2. Fixed compilation warning for Cavium platform. 
/main/1+    ue009.101 akaranth         1. Added CLI feature to send 
                                          RRC-reEst, Mesurement report, TAU message.
/main/1+    ue010.101 akaranth         1. Enhanced measurement feature.
                                       2. Enhanced the sending of TAU request from CLI interface.
 *********************************************************************91*/
