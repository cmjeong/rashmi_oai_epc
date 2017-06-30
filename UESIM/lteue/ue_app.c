
/********************************************************************20**
 
     Name:     LTE UE Simulator Application Module
  
     Type:     C source file
  
     Desc:     C source code for UE Sample Application
  
     File:     ue_app.c
  
     Sid:      ue_app.c@@/main/1 - Sun Mar 28 22:59:20 2010
  
     Prg:      vp
  
*********************************************************************21*/


/* ue008.101: Added new header file inclusion */
#include<signal.h>         /*  header for handling signals */
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
#endif /* SS_CAVIUM */
#include "cm_pasn.h"       /* common LTE */
#include "nhu_asn.h"
#include "nhu.h"
#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#ifndef SS_CAVIUM
#include <pcap.h>
#endif /* SS_CAVIUM */
/* ue007.101: cavium compile error fix */
#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-wqe.h"
#endif /* SS_CAVIUM */

#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
#include "tfu.h"
#include "ue.h"
#include "ue_err.h"

/* ue002.101: Changes for MSPD CL support */
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

#include "cm_emm.x"        /* EMM Includes */
#include "cm_esm.x"        /* ESM Includes */
#include "cm_emm_esm.x"    /* EMM-ESM Includes */
#include "ue_app.x"        /* UE App Includes */
#include "tfu.x"
#include "ue.x"

#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-config.h"
#include "cvmx-fpa.h"
#include "cvmx-wqe.h"
#include "cvmx-pko.h"
#include "cvmx-helper.h"
#include "cvmx-pip.h"
#include "cvmx-packet.h"
#endif /* SS_CAVIUM */
#include <stdlib.h> /* ue007.101 : defination for exit() */
/* ue002.101: Changes for end to end multi ue performance support */
/* ue008.101: Fix for compilation warning */
#include <unistd.h>

/* ue002.101: Changes for end to end multi ue performance support */
PUBLIC UeSimAppCb ueSimAppCb;
#ifdef LTE_E2E_PERF_MEAS
PUBLIC U8 dataBuf[UE_MAX_PDU_SIZE_E2E_PERF]={0};
#endif

#ifdef LTE_START_UL_DL_DATA
PUBLIC U8  data[1500] = {0};
#endif /* LTE_START_UL_DL_DATA */
/* ue006.101: Changes for end to end performance support */
PRIVATE U8 buf[2000];

/* Forward declarations */
/* ue002.101: Changes for multi ue support */
PRIVATE S16 ueAppSndAttachComplete ARGS((UeAppCb *ueAppCb));
PRIVATE S16 ueAppSndAuthResponse ARGS((UeAppCb *ueAppCb));
PRIVATE S16 ueAppSndIdResponse ARGS((UeAppCb *ueAppCb));
PRIVATE S16 ueAppSndSecModeComplete ARGS((UeAppCb *ueAppCb));
/* ue007.101: Network initiated detach support */
PRIVATE S16 ueAppSndDetachAccept ARGS((UeAppCb *ueAppCb));

PRIVATE S16 ueAppInit ARGS((Void));
/* ue002.101: Changes for multi ue support */
PRIVATE S16 ueAppInitUe ARGS((U16  cellId,UeAppCb *ueAppCb));

PRIVATE S16 ueAppHdlConTmrEvnt ARGS((Ptr cb));
PRIVATE S16 ueAppActvTmr ARGS((Void));
/* ue003.101: Added support for detach timer */
PRIVATE S16  ueAppHdlDetachTmr ARGS (( Ptr cb));
/* ue007:101: unused */
/* ue007.101: Added support for attach timer */
PRIVATE S16  ueAppHdlAttachTmr ARGS (( Ptr cb));
/* ue002.101: Changes for end to end multi ue performance support */
/* ue008.101: Fix for compilation warning. */
void SndUEInitDtachReq (int temp);
#ifdef LTE_E2E_PERF_MEAS
PRIVATE S16  ueAppHdlDataTmr ARGS (( Ptr cb));
#endif

/* ue003.101: Latency related changes */
#ifdef UE_COMPUTE_LATENCY
EXTERN TimeDelayInfo tmDelayInfo;
#endif

/*
*
*       Fun:   ueAppInit
*       
*       Desc:  This function initializes UE application information.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PRIVATE S16 ueAppUeInit
(
UeAppCellCb  *cell
)
#else
PRIVATE S16 ueAppUeInit(cell)
UeAppCellCb  *cell;
#endif
{
   UeAppGUMMEI  *gummei;
   /* ue002.101: Changes for multi ue support */
   U8           *ueImsi;
   U8           *nextUeImsi;
   CmEmmUeNwCap *nwCap;
   CmEdmInit     edmInit;
   U16           ueIdx;
   S16           digitIndex;
   
   TRC2(ueAppInit);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppInit: Initializing UE"));


   /* Serving GUMMEI for this UE. This information can
      later be updated if any arriving from RRC Connection
      Setup Complete from eNodeB or Attach Accept from MME for all the UEs*/
   /* IMSI has to be unique per UE */
   /* Fisrt initialize the IMSI for the 1st UE */
   ueImsi = &((cell->ueAppCbLst[0]).ueCtxt.ueImsi[0]);
   ueImsi[0] = UE_APP_MCC_DIG0;
   ueImsi[1] = UE_APP_MCC_DIG1;
   ueImsi[2] = UE_APP_MCC_DIG2;

   ueImsi[3] = UE_APP_MNC_DIG0;
   ueImsi[4] = UE_APP_MNC_DIG1;
   ueImsi[5] = UE_APP_MNC_DIG2;

   ueImsi[6] =  UE_APP_ID_DIG1;
   ueImsi[7] =  UE_APP_ID_DIG2;
   ueImsi[8] =  UE_APP_ID_DIG3;
   ueImsi[9] =  UE_APP_ID_DIG4;
   ueImsi[10] = UE_APP_ID_DIG5;
   ueImsi[11] = UE_APP_ID_DIG6;

   ueImsi[12] = UE_APP_ID_DIG7;
   ueImsi[13] = UE_APP_ID_DIG8;
   ueImsi[14] = UE_APP_ID_DIG9 + cell->cellId;
   /* Now initialize for other UEs */
   for (ueIdx=1;ueIdx < UE_NUM_PER_CELL;ueIdx++)
   {
      nextUeImsi = &((cell->ueAppCbLst[ueIdx]).ueCtxt.ueImsi[0]);
      /* First copy the 1st UE's IMSI into next UE */ 
      cmMemcpy(nextUeImsi,
              (U8 *)&((cell->ueAppCbLst[ueIdx-1]).ueCtxt.ueImsi),
              CM_EMM_MAX_MOBILE_ID_DIGS);

      for(digitIndex = CM_EMM_MAX_MOBILE_ID_DIGS-1;digitIndex >= 0;digitIndex--)
      {
         if(nextUeImsi[digitIndex] == 9)
         {
            nextUeImsi[digitIndex] = 0;
            continue;
         }
         else
         {
            nextUeImsi[digitIndex]++;
            break;
         }
      }
   }
   for(ueIdx = 0; ueIdx< UE_NUM_PER_CELL; ueIdx++)
   {
      gummei = &((cell->ueAppCbLst[ueIdx]).ueCtxt.gummei);
      gummei->nwId.mcc[0] = UE_APP_MCC_DIG0;
      gummei->nwId.mcc[1] = UE_APP_MCC_DIG1;
      gummei->nwId.mcc[2] = UE_APP_MCC_DIG2;

      gummei->nwId.mnc[0] = UE_APP_MNC_DIG0;
      gummei->nwId.mnc[1] = UE_APP_MNC_DIG1;
      gummei->nwId.mnc[2] = UE_APP_MNC_DIG2;

      gummei->mmeGrpId = UE_APP_MME_GROUP_ID;
      gummei->mmeCode = UE_APP_MME_CODE;
      /* Network Capability of UE */
      nwCap = &((cell->ueAppCbLst[ueIdx]).ueCtxt.ueNwCap);
   
      nwCap->pres = TRUE;
      nwCap->len = 2; /* Filling 2 Octets, one each for EPS EA & EPS IA */

      /* EPS Encryption Algorithm - EEA0 Supported */
      nwCap->eea0 = TRUE; 

      /* EIA - EPS Integrity ALgorithm - 128-EIA1 Supported */
      nwCap->eia1_128 = TRUE;

      /* Remaining algorithms UMTS Encryption Algo and UCS2 Algorithms
      are set to all 0 indicating not supported */ 
      cell->ueAppCbLst[ueIdx].ueCtxt.selfAddr.type = CM_IPV4ADDR_TYPE;
    
      /* Rest of the values in UE Context shall be updated upon receipt of 
      different EMM Messages from MME */

      /* Initialize emmCb */
      cell->ueAppCbLst[ueIdx].emmCb.state = UE_EMM_UE_NULL;
      cell->ueAppCbLst[ueIdx].emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_IDLE;
      cell->ueAppCbLst[ueIdx].emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_NONE;
      cell->ueAppCbLst[ueIdx].emmCb.esmPiggyBacked = TRUE;
 
      /* Add the cellId and the ueId as well */
      cell->ueAppCbLst[ueIdx].cellId = cell->cellId;
      cell->ueAppCbLst[ueIdx].ueId = ueIdx + cell->startRnti;

   }/*end of for */
  
   RETVALUE(ROK);
}


/*
*
*       Fun:   ueAppCellInit
*       
*       Desc:  This function initializes UE application information.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PRIVATE S16 ueAppCellInit
(
Void
)
#else
PRIVATE S16 ueAppCellInit()
#endif
{
   U16           cellIdx;
   UeAppCellCb   *cell;
   
   TRC2(ueAppCellInit);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppInit: Initializing Cell"));

   for (cellIdx = 0; cellIdx < UE_NUM_CELL; cellIdx++)
   {
      cell  = &(ueSimAppCb.cellCb[cellIdx]);
      cell->cellIdx = cellIdx;
      cell->cellId = UE_APP_CELL_ID + cellIdx;
      cell->startRnti = (UE_START_RNTI + (UE_CELL_RNTI_SPACE_DIFF * cellIdx));
      ueAppUeInit(cell);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   ueSimAppInit
*       
*       Desc:  This function initializes UE application information.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PRIVATE S16 ueSimAppInit
(
Void
)
#else
PRIVATE S16 ueSimAppInit()
#endif
{
   UeAppGUMMEI  *gummei;
   /* ue002.101: Changes for multi ue support */
   U8           *ueImsi;
   U8           *nextUeImsi;
   CmEmmUeNwCap *nwCap;
   CmEdmInit     edmInit;
   U16           ueIdx;
   S16           digitIndex;
   
   TRC2(ueSimAppInit);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppInit: Initializing UE"));

   /* ue002.101: Changes for multi ue support */
   UEAPP_ALLOC(&ueSimAppCb.rrcSapCb, sizeof(UeAppNhuSapCb));

   if(ueSimAppCb.rrcSapCb == NULLP)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE001, (ErrVal)0,
            "ueAppInit: Failed to allocate memory for rrcSapCb \n");
      RETVALUE(RFAILED);
   }
   ueSimAppCb.rrcSapCb->suId = UEAPP_RRC_SUID;
   ueSimAppCb.rrcSapCb->spId = UEAPP_SPID;
   ueSimAppCb.rrcSapCb->maxBndRetry = UEAPP_MAX_BND_RETRY;
   ueSimAppCb.rrcSapCb->bndRetryCnt = UEAPP_BND_RETRY_CNT;

   /* Initialize PDCP sap cb */
   UEAPP_ALLOC(&ueSimAppCb.pdcpSapCb, sizeof(UeAppPjuSapCb));

   if(ueSimAppCb.pdcpSapCb == NULLP)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE002, (ErrVal)0,
            "ueAppInit: Failed to allocate memory for PDCP SapCb\n");
      UEAPP_FREE(ueSimAppCb.rrcSapCb, sizeof(UeAppNhuSapCb));
      RETVALUE(RFAILED);
   }
   ueSimAppCb.pdcpSapCb->suId = UEAPP_PDCP_SUID;
   ueSimAppCb.pdcpSapCb->spId = UEAPP_SPID;
   ueSimAppCb.pdcpSapCb->maxBndRetry = UEAPP_MAX_BND_RETRY;
   ueSimAppCb.pdcpSapCb->bndRetryCnt = UEAPP_BND_RETRY_CNT;


#ifdef MULTI_UE_ATTACH
   ueSimAppCb.multAtchStrt = 0;
   ueSimAppCb.multDtchStrt = 0;
#endif

   /* Initialize EMM/ESM EDM */
   edmInit.ent = ueSimAppCb.init.ent;
   edmInit.inst = ueSimAppCb.init.inst;
   edmInit.region = ueSimAppCb.init.region;
   edmInit.pool = ueSimAppCb.init.pool;
   edmInit.procId = ueSimAppCb.init.procId;
#ifdef DEBUGP
   edmInit.dbgMask = ueSimAppCb.init.dbgMask;
#endif
   if(cmEmmEsmEdmInit(edmInit) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE003, (ErrVal)0,
         "ueAppInit: Failed to Initialize EMM_ESM EDM module\n");
      UEAPP_FREE(ueSimAppCb.rrcSapCb, sizeof(UeAppNhuSapCb));
      UEAPP_FREE(ueSimAppCb.pdcpSapCb, sizeof(UeAppPjuSapCb));
      RETVALUE(RFAILED);
   }
#ifdef UESIM_ENABLE_PCAP
   /* Initialize the UE App data handler */
   if (ueAppRouteInit() != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE004, (ErrVal)0,
         "ueAppInit: Failed to initialize data app routing params\n");
      UEAPP_FREE(ueSimAppCb.rrcSapCb, sizeof(UeAppNhuSapCb));
      UEAPP_FREE(ueSimAppCb.pdcpSapCb, sizeof(UeAppPjuSapCb));
      RETVALUE(RFAILED);
   }
#endif
#ifdef ENB_PERF_MEAS
   ueSimAppCb.state= UE_STATE_NOT_READY;
   ueSimAppCb.wait = 10;
#endif

   ueAppCellInit();

   RETVALUE(ROK);
}
/*
*
*       Fun:   ueAppActvInit
*       
*       Desc:  This function initializes UE application
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI 
PUBLIC S16 ueAppActvInit
(
Ent    entity,         /* entity */
Inst   inst,           /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 ueAppActvInit(entity, inst, region, reason)
Ent    entity;         /* entity */
Inst   inst;           /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
{

   TRC2(ueAppActvInit);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppActvInit: Initializing UE ActvTsk"));
   /*  Initialize global cb values here */
   /* ue002.101: Changes for multi ue support */
   cmMemset ((U8 *)&ueSimAppCb, 0, sizeof(UeSimAppCb));
   ueSimAppCb.init.procId = SFndProcId();

   ueSimAppCb.init.ent = entity;
   ueSimAppCb.init.inst = inst;
   ueSimAppCb.init.region = region;
   ueSimAppCb.init.reason = reason;
   ueSimAppCb.init.cfgDone = FALSE;
   ueSimAppCb.init.pool = 0;
   ueSimAppCb.init.acnt = FALSE;

#ifdef UEAPP_USTA
   ueSimAppCb.init.usta = TRUE;
#else
   ueSimAppCb.init.usta = FALSE;
#endif /* UEAPP_USTA */

#ifdef DEBUGP
   ueSimAppCb.init.dbgMask = 0xffffffff;
#endif /* DEBUGP */

   if(ueSimAppInit() != ROK)
   {
      /* ue007.101: Fix to ccpu00117388 */
      /* Failed to initialize uesim application */
      UELOGERROR(ERRCLS_ADD_RES, EUE002, (ErrVal)0,
            "ueAppActvInit: Failed to initialize uesim application\n");
      exit(0);
   }

   RETVALUE(ROK);
} /* ueAppActvInit */

/**
 *
 *       Fun:   ueAppTmrInit
 *       
 *       Desc:  This function initializes Timers in the application.
 *       
 *       Ret:   ROK
 *       
 *       Notes: None
 *              
 *       File:  ue_app.c
 *       
**/

#ifdef ANSI
PUBLIC S16 ueAppTmrInit
(
Void
)
#else
PUBLIC S16 ueAppTmrInit()
#endif
{
   U8 timeRes = 10;
   U16 idx;
   
   TRC2(ueAppTmrInit);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppTmrInit: Initializing UE Tmr"));
   /* ue002.101: Changes for multi ue support */
   cmInitTimers(ueSimAppCb.timers, UE_APP_MAX_TMRS);
   ueSimAppCb.ueTqCp.nxtEnt = 0;
   ueSimAppCb.ueTqCp.tmrLen = UE_APP_TQSIZE;
   SRegTmr(UE_ENT_APP, 0, (S16)timeRes, (PFS16)ueAppActvTmr);
   for (idx = 0; idx<UE_APP_TQSIZE; idx++)
   {
      ueSimAppCb.ueTq[idx].first    = NULLP;
      ueSimAppCb.ueTq[idx].tail     = NULLP;
   }

   /* Disabling this as of now. For a complete
    * functionality, this timer should be disabled
    * when random access is done (or nearabouts).
    * Also, the timer value should be scaled based
    * on actual TTI. In the absence of this, and when
    * TTI is large (say 10 ms), this timer expires in the middle
    * of random access procedure. (Expiring after the
    * procedure works as enb-mac discards the PDU containing
    * CCCH.)
    */
   /* Start RRC Connection Setup Timer */
   /* ueAppStartTmr(UE_APP_CR_TMR, UE_APP_CR_TMR_VAL); */

   RETVALUE(ROK);

}

/*
*
*       Fun:   ueAppActvTmr
*       
*       Desc:  This function handles the Application timer.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/
#ifdef ANSI
PRIVATE S16 ueAppActvTmr
(
void
)
#else
PRIVATE S16 ueAppActvTmr ()
#endif
{

   TRC2(ueAppActvTmr);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppActvTmr: Processing UE Tmri event"));

   /* ue002.101: Changes for multi ue support */
   cmPrcTmr (&ueSimAppCb.ueTqCp, ueSimAppCb.ueTq, (PFV) ueAppTmrEvnt);

   RETVALUE (ROK);

} /* end of ueAppActvTmr */

/*
*
*       Fun:   ueAppTmrEvnt
*       
*       Desc:  This function handles the timer events.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppTmrEvnt
(
Ptr       cb,
S16       tmrEvnt
)
#else
PUBLIC S16 ueAppTmrEvnt(cb, tmrEvnt)
Ptr       cb;
S16       tmrEvnt;
#endif
{
   S16 ret;

   TRC2(ueAppTmrEvnt);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppTmrEvnt: Processing Timer Event"));
   switch(tmrEvnt)
   {
      case UE_APP_CR_TMR: /* Connection Request Timer */
      {
         ret = ueAppHdlConTmrEvnt(cb);
         break;
      }
/* ue003.101: Added support for dedicated bearers */
#ifdef UESIM_TRIGGER_DRB_EST
      case UE_APP_BR_RES_TMR:
      {
         /* Send Dedicated Bearer  Resource Allocation Request */
         /* ue008.101: Removed calling of ueAppSndBrResAllocReq()*/
      /*   ret = ueAppSndBrResAllocReq(); */
         break;
      }
#endif 
      case UE_APP_DETACH_TMR: /* Connection Detach Timer */
      {
         ret = ueAppHdlDetachTmr(cb);
         break;
      }
      /* ue007.101: Added support for attach timer */
      /* multiple attach */
      case UE_APP_MULT_ATTACH_TMR:
      {
         ret = ueAppHdlAttachTmr(cb);
         break;
      }
#ifdef LTE_E2E_PERF_MEAS
      case UE_APP_DATA_TMR: /*start pumping the data */
      {
         ret = ueAppHdlDataTmr(cb);
         break;
      }
#endif
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
      case UE_INIT_DED_BEARER_RELEASE_TMR: /* Connection Dedicated bearer release Timer */
      {
         ret = ueAppSndModBrReq();
         break;
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE005, (ErrVal)tmrEvnt,
            "ueAppTmrEvnt: Invalid Timer Event\n");
         RETVALUE(RFAILED);
      }
   }
   RETVALUE(ret);
}

/*
*
*       Fun:   ueAppHdlConTmrEvnt
*       
*       Desc:  This function handles the Connection Timer event
*              and triggers RRC Connection Setup.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/
#ifdef ANSI
PRIVATE S16 ueAppHdlConTmrEvnt
(
Ptr       cb
)
#else
PRIVATE S16 ueAppHdlConTmrEvnt(cb)
Ptr       cb;
#endif
{
   U16 cellIdx;
   U16 ueIdx;
   TRC2(ueAppHdlConTmrEvnt);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppHdlConTmrEvnt: Handling Connection Timer Event"));
   /* Initialize the UE and start triggering RRC Connection Setup */
   /* ue002.101: Start the RRC coonection setup for all the UEs */
   cellIdx = (U16)cb;
   for(ueIdx = 0;ueIdx < UE_NUM_PER_CELL; ueIdx++)
   {
     ueAppInitUe(cellIdx,&ueSimAppCb.cellCb[cellIdx].ueAppCbLst[ueIdx]);
   }

   RETVALUE(ROK);
}


/* ue008.101: Added new function SndUEInitDtachReq(). */
/*
*  Fun:  SndUEInitDtachReq
*       Desc:  This Function will handle the SIGINIT signal(Ctlr+c)
*     and triggers the Detatch request for the UE
*  Ret:    Exit()
*
*  Notes None
*
*  File  ue_app.c
*
*/
#ifdef ANSI
void SndUEInitDtachReq
(
int temp
)
#else
void SndUEInitDtachReq(temp)
int temp;
#endif
{
   S16 ret;
   UeAppCellCb *cell;
   U16          cellIdx;
   CmNasEvnt   *detachReq = NULLP;
   U16 ueIdx;
   U16 idx;
   UeAppCb       *ueAppCb;

   TRC2(SndUEInitDtachReq);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "SndUEInitDtachReq: Handling SIGINIT signal"));
   
#ifdef MULTI_UE_ATTACH
   /*ue009.101: since Detach timer has been popped, it will be needed to be restarted
     * set the flag to false */
   ueSimAppCb.multDtchStrt = 0;
#endif

   for (cellIdx = 0; cellIdx < UE_NUM_CELL; cellIdx++);
   {
      cell = &ueSimAppCb.cellCb[cellIdx];
      /* ue002.101: Initialize the UE and start triggering UE detach request */
      for(ueIdx=0;ueIdx < UE_NUM_PER_CELL;ueIdx++)
      {
#ifdef MULTI_UE_ATTACH
         if (!cell->ueAppCbLst[ueIdx].isDetached)
         {
#endif
            ret = ueAppUtlBldDetachReq(&(cell->ueAppCbLst[ueIdx]), &detachReq,
                              UE_DETACH_IMSI, CM_EMM_MID_TYPE_IMSI);
            if (ret != ROK)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE006, (ErrVal)0,
                  "ueAppHdlDetachTmr : Building DetachReq Failed\n");
            }
   
            ret = ueAppEmmHdlOutUeEvnt(detachReq,&cell->ueAppCbLst[ueIdx]);
            if(ret != ROK)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE007, (ErrVal)ueIdx,
                  "ueAppHdlDetachTmr : Failed to Send Detach\n");
            }
            printf("Sent detach for ueIdx %d\n",ueIdx);
            UE_DBGP_INFO((UE_PRNTBUF,
              "ueAppHdlDetachTmr :  Sent Detach Successfully "));
            /* ue007.101: Resetting ueAppCb */
            ueAppCb = &cell->ueAppCbLst[ueIdx];
            ueAppCb->ecmCb.state = UE_ECM_IDLE;
            ueAppCb->transIdCntr = 0;
            ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_IDLE;
            ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_NONE;
            ueAppCb->emmCb.esmPiggyBacked = TRUE;

            /* Delete TRANS and BID EsmCbs */
            for(idx=0; idx < CM_ESM_MAX_BEARER_ID; idx++)
            {
               if(ueAppCb->esmTList[idx] != NULLP)
               {
                  ueAppUtlDelEsmCb(ueAppCb->esmTList[idx], ueAppCb);
                  ueAppCb->esmTList[idx] = NULLP;
               }
               if(ueAppCb->esmBList[idx] != NULLP)
               {
                  ueAppUtlDelEsmCb(ueAppCb->esmBList[idx], ueAppCb);
                  ueAppCb->esmBList[idx] = NULLP;
               }
            }

#ifdef MULTI_UE_ATTACH
               cell->ueAppCbLst[ueIdx].isDetached = TRUE;
         }
#endif
      }

#ifdef MULTI_UE_ATTACH
      /* Set the MultiAttach flag to indicate that
       * Multi-attach timer has been started    */ 
      if(!ueSimAppCb.multAtchStrt)
      { 
          ueSimAppCb.multAtchStrt++;
          ueSimAppCb.multAtchStrt%=UE_NUM_PER_CELL;
         //Start detach timer when the first Attach is received ;)
         /* ue007.101: Starting multiple attach timer */
         ueAppStartTmr(cell->cellId,UE_APP_MULT_ATTACH_TMR, UE_APP_MULT_ATTACH_VAL);
      }
      else
      {
          ueSimAppCb.multAtchStrt++;
          ueSimAppCb.multAtchStrt%=UE_NUM_PER_CELL;
      } 
#else
      /* ue007.101: Starting multiple attach timer */
      printf("\nStarting multiple attach timer\n");
      ueAppStartTmr(cell->cellId,UE_APP_MULT_ATTACH_TMR, UE_APP_MULT_ATTACH_VAL);
#endif
   }
#ifndef SS_CAVIUM 
sleep(1);
#endif
exit(0);
}

/*
*
*       Fun:   ueAppHdlDetachTmr
*       
*       Desc:  This function builds and sends the
*              detach request to the network.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PRIVATE S16  ueAppHdlDetachTmr
(
Ptr       cb
)
#else
PRIVATE S16 ueAppHdlDetachTmr(cb)
Ptr       cb;
#endif
{

   S16 ret;
   CmNasEvnt   *detachReq = NULLP;
   UeAppCellCb *cell;
   U16          cellIdx;
   U16 ueIdx;
   U16 idx;
   UeAppCb       *ueAppCb;

   TRC2(ueAppHdlDetachTmr);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppHdlDetachTmr: Handling Detach Timer Event"));

#ifdef MULTI_UE_ATTACH
   /*ue008.101: since Detach timer has been popped, it will be needed to be restarted
     * set the flag to false */
   ueSimAppCb.multDtchStrt = 0;
#endif

   for (cellIdx = 0; cellIdx < UE_NUM_CELL; cellIdx++);
   {
      cell = &ueSimAppCb.cellCb[cellIdx];
 
      /* ue002.101: Initialize the UE and start triggering UE detach request */
      for(ueIdx=0;ueIdx < UE_NUM_PER_CELL;ueIdx++)
      {
         /* ue008.101: MULTI_UE_ATTACH Support */
#ifdef MULTI_UE_ATTACH
         if (!cell->ueAppCbLst[ueIdx].isDetached)
         {
#endif
            ret = ueAppUtlBldDetachReq(&(cell->ueAppCbLst[ueIdx]), &detachReq,
                              UE_DETACH_IMSI, CM_EMM_MID_TYPE_IMSI);
            if (ret != ROK)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE006, (ErrVal)0,
                  "ueAppHdlDetachTmr : Building DetachReq Failed\n");
               RETVALUE(ret);
            }
   
            ret = ueAppEmmHdlOutUeEvnt(detachReq,&cell->ueAppCbLst[ueIdx]);
            if(ret != ROK)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE007, (ErrVal)ueIdx,
                  "ueAppHdlDetachTmr : Failed to Send Detach\n");
               RETVALUE(ret);
            }
            printf("Sent detach for ueIdx %d\n",ueIdx);
            UE_DBGP_INFO((UE_PRNTBUF,
              "ueAppHdlDetachTmr :  Sent Detach Successfully "));
            /* ue007.101: Resetting ueAppCb */
            ueAppCb = &cell->ueAppCbLst[ueIdx];
            ueAppCb->ecmCb.state = UE_ECM_IDLE;
            ueAppCb->transIdCntr = 0;
            ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_IDLE;
            ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_NONE;
            ueAppCb->emmCb.esmPiggyBacked = TRUE;

            /* Delete TRANS and BID EsmCbs */
            for(idx=0; idx < CM_ESM_MAX_BEARER_ID; idx++)
            {
               if(ueAppCb->esmTList[idx] != NULLP)
               {
                  ueAppUtlDelEsmCb(ueAppCb->esmTList[idx], ueAppCb);
                  ueAppCb->esmTList[idx] = NULLP;
               }
               if(ueAppCb->esmBList[idx] != NULLP)
               {
                  ueAppUtlDelEsmCb(ueAppCb->esmBList[idx], ueAppCb);
                  ueAppCb->esmBList[idx] = NULLP;
               }
            }

#ifdef MULTI_UE_ATTACH
            cell->ueAppCbLst[ueIdx].isDetached = TRUE;
         }
#endif
      }

#ifdef MULTI_UE_ATTACH
   /* ue008.101: Set the MultiAttach flag to indicate that
    * Multi-attach timer has been started    */ 
      if(!ueSimAppCb.multAtchStrt)
      { 
          ueSimAppCb.multAtchStrt++;
          ueSimAppCb.multAtchStrt%=UE_NUM_PER_CELL;
         //Start detach timer when the first Attach is received ;)
         /* ue007.101: Starting multiple attach timer */
         ueAppStartTmr(cell->cellId,UE_APP_MULT_ATTACH_TMR, UE_APP_MULT_ATTACH_VAL);
      }
      else
      {
          ueSimAppCb.multAtchStrt++;
          ueSimAppCb.multAtchStrt%=UE_NUM_PER_CELL;
      } 
#else
      /* ue007.101: Starting multiple attach timer */
      printf("\nStarting multiple attach timer\n");
      ueAppStartTmr(cell->cellid,UE_APP_MULT_ATTACH_TMR, UE_APP_MULT_ATTACH_VAL);
#endif
   }

   RETVALUE(ret);
}

/* ue007.101: Added support for attach timer */
/*
 *
 *       Fun:   ueAppHdlAttachTmr
 *       
 *       Desc:  This function re initiate UE
 *       
 *       Ret:   ROK
 *       
 *       Notes: None
 *              
 *       File:  ue_app.c
 *       
 */

#ifdef ANSI
PRIVATE S16  ueAppHdlAttachTmr
(
 Ptr       cb
 )
#else
PRIVATE S16 ueAppHdlAttachTmr(cb)
   Ptr       cb;
#endif
{
   /* ue008.101 : TIC_ID : ccpu00117550 MOD: Fixed warning for gcc compilation on CentOS*/
   S16 ret = ROK;
   /* ue008.101 : TIC_ID : ccpu00117550 MOD_END: Fixed warning for gcc compilation on CentOS*/
   U16 cellIdx ;
   U16 idx = 0;
#ifdef MULTI_UE_ATTACH
   U16 ueIdx=0;
#endif
   UeCb  *ue;
   Buffer      *msg3;
   static U32 numAttach = 1;
   TRC2(ueAppHdlAttachTmr);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppHdlAttachTmr: Handling Attach Timer Event"));

   printf("\nRe initiating UE \n");
/* ue008.101: MULTI_UE_ATTACH Support  */
   cellIdx = (U16) cb;
#ifdef MULTI_UE_ATTACH
   for(ueIdx=0; ueIdx < UE_NUM_PER_CELL; ueIdx++)
   {
      ue = &cellArr[cellIdx].ueArr[ueIdx];
#else
      ue = &cellArr[cellIdx].ueArr[0];
#endif
   for(idx=0; idx<UE_NUM_RLC_RB_PER_UE; idx++)
   {
      printf("\n Values reset for RB %d\n", idx);
      ue->rlc.rbArr[idx].cur_um_seq = 0;
      ue->rlc.rbArr[idx].rcvd_um_seq = 0;
      ue->rlc.snLen = 2; /* 10 bits SN Len */

      ue->rlc.rbArr[idx].cur_am_seq = 0;
      ue->rlc.rbArr[idx].rcvd_am_seq = 0;
      ue->rlc.rbArr[idx].ackToBeSent = FALSE;
      ue->rlc.rbArr[idx].bo = 0;
      ue->rlc.rbArr[idx].mBuf = NULLP;
      ue->rlc.rbArr[idx].lcId = idx;

      ue->rlc.rbArr[idx].pdcpSn = 0;
      ue->rlc.rbArr[idx].rcvdPdcpSn = 0;
   }
   ue->isDel = 0;

#ifdef MULTI_UE_ATTACH
   ueRrcBuildRRCConReq(&msg3, &cellArr[cellIdx].ueArr[ueIdx], TRUE);
#else
   ueRrcBuildRRCConReq(&msg3, &cellArr[cellIdx].ueArr[0], TRUE);
#endif
   /* Assuming Single UE. Initiate the RACH procedure for the ueIdx == 0 */
   /* Construct the message 3 */
#ifdef MULTI_UE_ATTACH
   ueMacRachReq(&cellArr[cellIdx], &cellArr[cellIdx].ueArr[ueIdx], msg3);
#else
   ueMacRachReq(&cellArr[cellIdx], &cellArr[cellIdx].ueArr[cellIdx], msg3);
#endif
   printf("num Attach = %ld\n", numAttach);
   numAttach++;
      
#ifdef MULTI_UE_ATTACH
      // Set the flags
      ueSimAppCb.cellCb[cellIdx].ueAppCbLst[ueIdx].isDetached = FALSE;
   }
   // All attach sent, Reset the Attach timer Flag
   ueSimAppCb.multAtchStrt = 0;
#endif

   RETVALUE(ret);
}

#ifdef LTE_E2E_PERF_MEAS
#ifdef ANSI
PRIVATE S16  ueAppHdlDataTmr
(
Ptr       cb
)
#else
PRIVATE S16 ueAppHdlDataTmr(cb)
Ptr       cb;
#endif
{
  /*send the data for all the UEs */
  U16    cellId;
  Buffer *mBuf;
  U16    ueIdx;
  S16    ret;

  UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppLimSndPdcpMsg: Sending the PDU to eNodeB"));
  cellId = (U16) cb;
  do
  {
  for (ueIdx = 0; ueIdx < UE_NUM_PER_CELL; ueIdx++)
  {
     /* Convert to mBuf */
     ret = SGetMsg(ueSimAppCb.init.region, ueSimAppCb.init.pool, &mBuf);
     if(ROK != ret)
     {
        printf("Memory unavailable for sending UL data \n");
        RETVALUE(ROK);  
     } 
     ret = SAddPstMsgMult((Data *)(dataBuf), UE_MAX_PDU_SIZE_E2E_PERF, mBuf);

     if (ROK != ret)
     {
        UELOGERROR(ERRCLS_ADD_RES, EUE026, (ErrVal)ret,
        "ueAppLimSndPdcpMsg : Converting to mBuf failed\n"); 
        SPutMsg(mBuf);
        RETVALUE(ROK);
     }
     /* ue008.101: Added new parameter in UeUiPjuDatReq().*/
     ret = UeUiPjuDatReq(&(ueSimAppCb.pdcpSapCb->pst),
                         ueSimAppCb.pdcpSapCb->spId,
                         mBuf,cellId,ueIdx, 3);
  }
  usleep(30000);
  }while(1);

  /*ueAppStartTmr(UE_APP_DATA_TMR, UE_APP_DATA_TMR_VAL);*/

  RETVALUE(ret);
}
#endif
/*
*
*       Fun:   ueAppStartTmr
*       
*       Desc:  This function starts the specified timer.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/


#ifdef ANSI
PUBLIC S16 ueAppStartTmr
(
U16  cellId,
U8   tmrEvnt,
/* ue006.101:Fix for CID:1465-02-01, DefectId:
   ccpu00116336. Removing the compiler
   warning.
*/
U32  wait
)
#else
PUBLIC S16 ueAppStartTmr(cellId,tmrEvnt, wait)
U16  cellId,
U8   tmrEvnt;
/* ue006.101:Fix for CID:1465-02-01, DefectId:
   ccpu00116336. Removing the compiler
   warning.
*/
U32   wait;
#endif
{
   CmTmrArg arg;

   TRC2(ueAppStartTmr);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppStartTmr: Starting UE Timer for event %d",tmrEvnt));

   switch (tmrEvnt)
   {
      case UE_APP_CR_TMR:
      {
         arg.max= UE_APP_MAX_TMRS;
         break;
      }
/* ue003.101: Added support for dedicated bearers */
#ifdef UESIM_TRIGGER_DRB_EST
      case UE_APP_BR_RES_TMR:
      {
         arg.max= UE_APP_MAX_TMRS;
         break;
      }
#endif
      case UE_APP_DETACH_TMR:
      {
         printf("\nStarting detach timer\n");
         arg.max= UE_APP_MAX_TMRS;
         break;
      }
      /* ue007.101: Added support for attach timer */
      /* Multiple attach */
      case UE_APP_MULT_ATTACH_TMR:
      {
         printf("\nStarting attach timer\n");
         arg.max= UE_APP_MAX_TMRS;
         break;
      }
#ifdef LTE_E2E_PERF_MEAS
      case UE_APP_DATA_TMR:
      {
        arg.max= UE_APP_MAX_TMRS;
        break;
      }
#endif
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
      case UE_INIT_DED_BEARER_RELEASE_TMR:
      {
         printf("\nStarting dedicated Bearer Release Timer\n");
         arg.max= UE_APP_MAX_TMRS;
         break;
      }
      default:
      {  
         UELOGERROR(ERRCLS_ADD_RES, EUE008, (ErrVal)tmrEvnt,
            "ueAppStartTmr: Invalid Timer event \n");
         RETVALUE(RFAILED);
      }
   }

   arg.timers = ueSimAppCb.timers;
   arg.tq = ueSimAppCb.ueTq;
   arg.tqCp = &(ueSimAppCb.ueTqCp);
   arg.cb = (PTR)cellId;
   arg.evnt = tmrEvnt;
   arg.wait = wait;
   arg.tNum = NOTUSED;
   arg.max = UE_APP_MAX_TMRS;

   /* Start the timer only if timer value (wait) is not zero */
   if(wait != 0)
   {
      cmPlcCbTq(&arg);
   }

   RETVALUE(ROK);
}

/*
 *       Fun:    ueAppInitUe
 * 
 *       Desc:   This function initializes a UE procedure for RRC Connection
 *               establishment.
 *
 *       Ret:    ROK 
 *
 *       Notes:  None 
 *
 *       File:   uesim.c
 */

#ifdef ANSI           
PRIVATE S16 ueAppInitUe
(
U16      cellId,
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppInitUe(cellId, ueAppCb)
U16      cellId;
UeAppCb *ueAppCb;
#endif
{
   NhuDatReqSdus  *datReqPdu = NULLP;
   S16 ret;

   TRC2(ueAppInitUe);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppInitUe: Initializing the UE"));
   /* Build Connection Request for this UE */
   ret = ueAppUtlBldRRCConReq(&datReqPdu);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE009, (ErrVal)ret,
         "ueAppInitUe: Failed to Build RRC Connection Request\n");
      RETVALUE(RFAILED);
   }

   /* ue002.101: Multi ue support changes */
   ret = ueAppLimSndRRCMsg(datReqPdu, ueAppCb);

   RETVALUE(ret);

} /* end of ueInit */


/*
*
*       Fun:   ueAppActvTsk
*       
*       Desc:  This function handles UE events 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else
PUBLIC S16 ueAppActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   Mem  sMem;

   TRC2(ueAppActvTsk);

   UE_DBGP_INFO((UE_PRNTBUF,
                  "ueAppActvTsk: UE ActvTsk called for event %d", pst->event));

   sMem.region = ueSimAppCb.init.region;
   sMem.pool = DFLT_POOL;


   switch(pst->srcEnt)
   {
/* ue006.101: Changes for end to end performance support */
      case UE_ENT_APP:
      {
         switch(pst->event)
         {
/* ue006.101: Changes for end to end performance support */
            default:
/* ue007.101: Macro added for e2e perf  */               
#ifdef UESIM_ENABLE_PCAP               
            {
               MsgLen       len, len1;
               SFndLenMsg(mBuf, &len);
               if (len != 0)
               {
                  SCpyMsgFix(mBuf, 0, len, (Data *)buf, &len1);
#ifndef SS_CAVIUM
                  ueAppHndlIPPkt(buf, len);
#else
                  ueAppHndlIPPkt((cvmx_wqe_t *)buf);
#endif
               }
               SPutMsg(mBuf);
            }
#endif            
               break;
         }
         break;
      }
      default:
         UNUSED(sMem);
         SPutMsg(mBuf);
         break;
   }

   (Void)SExitTsk();
   RETVALUE(ROK);
}

/*
*
*       Fun:   ueAppRcvEmmMsg
*       
*       Desc:  This function handles all the incoming EMM messages from MME
*              through eNodeB on RRC. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppRcvEmmMsg
(
CmNasEvnt  *evnt,
U8          emmMsgType,
UeAppCb    *ueAppCb
)
#else
PUBLIC S16 ueAppRcvEmmMsg(evnt, emmMsgType, ueAppCb)
CmNasEvnt  *evnt;
U8          emmMsgType;
UeAppCb    *ueAppCb;
#endif
{
   S16 ret = RFAILED;
   U16 ueIdx = 0;
   UeAppCellCb *ueAppCellCb;

   TRC2(ueAppRcvEmmMsg);

   /* Release the Event Structure as we dont use it anymore */
   CM_FREE_NASEVNT(&evnt);
   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppRcvEmmMsg:Received EMM Msg with MsgType(%d)",emmMsgType));

   /* ue002.101: Multi ue support changes for application cb */
   switch(emmMsgType)
   {
      case CM_EMM_MSG_ATTACH_ACC: /* Attach accept from MME */
         {
#ifdef TOTAL_ENB
            /* ue009.101: Added feature to drop the diffrent RRC messages.
             * depends on the RRC timer. */
            if(UE_RRC_TIMER != UE_RRC_RECONFIG_TMR)
            {
#endif
#ifndef UESIM_ENABLE_PCAP
               /* Initiate Attach complete to MME */
               ret = ueAppSndAttachComplete(ueAppCb);
               /* ue003.101: dedicated bearer support */
#ifdef UESIM_TRIGGER_DRB_EST
               /* ue008.101: Send Dedicated Bearer  Resource Allocation Request */
               /*   ueAppStartTmr(UE_APP_BR_RES_TMR, UE_APP_BR_RES_TMR_VAL);*/
               ret = ueAppSndBrResAllocReq(ueAppCb);
#endif 
#else
               UE_DBGP_INFO((UE_PRNTBUF,
                        "ueAppRcvEmmMsg:Received EMM Msg with MsgType(%ld)",ueAppCb->ueCtxt.selfAddr.u.ipv4NetAddr));
               /* Send the ifconfig/ARP request to the PDN address received */
               /* ue007.101: get the proper ueIdx */
               
               UE_GET_APPCELLCB(ueAppCb->cellId, ueAppCellCb);
               ueIdx=(UE_NUM_PER_CELL > 1)? (ueAppCb->ueId - ueAppCellCb->startRnti): 0;
               ret = ueAppCfgrPdnAssignedAddr(ueAppCb->ueCtxt.selfAddr.u.ipv4NetAddr,ueAppCellCb->cellIdx, ueIdx);
#endif
#ifdef TOTAL_ENB
               /* ue009.101: Added feature to drop the diffrent RRC messages.
                * depends on the RRC timer. */
            }
            else 
            {
               printf("Blocking reconfiguration message\n");
            }
#endif
            break;
         }
      case CM_EMM_MSG_AUTH_REQ: /* Authentication request from mme */
      {
         /* Initiate authentication response to MME */
         ret = ueAppSndAuthResponse(ueAppCb);
         break;
      }
      case CM_EMM_MSG_ID_REQ: /* */
      {
         /* Initiate ID response to MME */
         ret = ueAppSndIdResponse(ueAppCb);
         break;
      }
      case CM_EMM_MSG_SEC_MODE_CMD: /* */
      {
         /* Initiate Security mode complete */
         ret = ueAppSndSecModeComplete(ueAppCb);
         break;
      }
      case CM_EMM_MSG_DETACH_REQ: /* */
      {
         /* ue007.101: Initiate detach accept */
         ret = ueAppSndDetachAccept(ueAppCb);
         break;
      }
      case CM_EMM_MSG_ATTACH_REJ: /* */
      {
         /* ue008.101: Initiate detach reject */
         /*TODO: Handle Attach Reject */
         break;
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE010, (ErrVal)emmMsgType,
            " ueAppRcvEmmMsg:Invalid EMM MsgType \n");
         ret = RFAILED;
      }
   }
   RETVALUE(ret);
} /* End od ueAppRcvEmmMsg */

/*
*
*       Fun:   ueAppSndAttachRequest
*       
*       Desc:  This function sends Attach request message to MME using EMM
*              through eNodeB on RRC. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppSndAttachRequest
(
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppSndAttachRequest(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   CmNasEvnt   *attachReqEvnt = NULLP;
   S16 ret;

   TRC2(ueAppSndAttachRequest);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndAttachComplete:Sending Attach request"));
   ret = ueAppUtlBldAttachReq(ueAppCb, &attachReqEvnt, CM_EMM_MID_TYPE_IMSI);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE011, (ErrVal)ret,
            " ueAppSndAttachRequest: Could not send the Attach request\n");
      RETVALUE(ret);
   }

   RETVALUE(ueAppEmmHdlOutUeEvnt(attachReqEvnt, ueAppCb));
} /* End of ueAppSndAttachRequest */

/* ue003.101: changes for paging support */
/*
*
*       Fun:   ueAppSndServiceRequest
*       
*       Desc:  This function sends Service request message to MME using EMM
*              through eNodeB on RRC. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppSndServiceRequest
(
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppSndServiceRequest(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   CmNasEvnt   *serviceReqEvnt = NULLP;
   S16 ret;

   TRC2(ueAppSndServiceRequest);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndServiceRequest:Sending Service request"));
   ret = ueAppUtlBldServiceReq(ueAppCb, &serviceReqEvnt);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE011, (ErrVal)ret,
            " ueAppSndAttachRequest: Could not send the Service request\n");
      RETVALUE(ret);
   }

   RETVALUE(ueAppEmmHdlOutUeEvnt(serviceReqEvnt, ueAppCb));
} /* End of ueAppSndAttachRequest */




/*
*
*       Fun:   ueAppSndAttachComplete
*       
*       Desc:  This function sends Attach complete message to MME using EMM
*              through eNodeB on RRC. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PRIVATE S16 ueAppSndAttachComplete
(
UeAppCb  *ueAppCb
)
#else
PRIVATE S16 ueAppSndAttachComplete(ueAppCb)
UeAppCb  *ueAppCb;
#endif
{
   CmNasEvnt   *attachCompEvnt = NULLP;
   S16 ret;

   TRC2(ueAppSndAttachComplete);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndAttachComplete:Sending Attach complete"));

   ret = ueAppUtlBldAttachComplete(ueAppCb, &attachCompEvnt);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE012, (ErrVal)ret,
            " ueAppSndAttachComplete: Could not send the Attach complete\n");
      RETVALUE(ret);
   }

   ret = ueAppEmmHdlOutUeEvnt(attachCompEvnt,ueAppCb);

/* ue003.101: latency related changes */
#ifdef UE_COMPUTE_LATENCY
   tmDelayInfo.attachComp.status = 1;
#endif

/* ue008.101: MULTI_UE_ATTACH Support */
#ifdef MULTI_UE_ATTACH
   /* Set the MultiAttach flag to indicate that
    * Multi-attach timer has been started    */ 
   if(!ueSimAppCb.multDtchStrt++)
   { 

      /*-- Start detach timer when the first Attach is received  --*/
      ueAppStartTmr(ueAppCb->cellId,UE_APP_DETACH_TMR, UE_APP_DATA_DETACH_TMR_VAL);
   }
   else
   {
      ueSimAppCb.multDtchStrt%=(UE_NUM_PER_CELL-1);
   }


#else
/* ue003.101: Added support for detach timer */
   /* start the detach timer */
   ueAppStartTmr(ueAppCb->cellId,UE_APP_DETACH_TMR, UE_APP_DATA_DETACH_TMR_VAL);
#endif

   /* ue002.101: UL data generator for E2E perf multi ue: 
      Variable keeps count of no of attch complete sent.
      When this is equal to UE_NUM_PER_CELL, start a timer.
      On the expiry of this timer start pumping UL data */
#ifdef LTE_E2E_PERF_MEAS     
   if (ret == ROK )
   {
      ueSimAppCb.numAttachCompSent++;
      if(ueSimAppCb.numAttachCompSent == UE_NUM_PER_CELL)
      { 
         /* start the data timer */
         ueAppStartTmr(ueAppCb->cellId,UE_APP_DATA_TMR, UE_APP_DATA_TMR_VAL);

      }  
   }
#endif
   RETVALUE(ret); 
} /* End of ueAppSndAttachComplete */
/*
*
*       Fun:   ueAppSndArpCompInd
*       
*       Desc:  This function sends Attach complete message to MME using EMM
*              through eNodeB on RRC. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppSndArpCompInd
(
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppSndArpCompInd(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   S16 ret;

   TRC2(ueAppSndArpCompInd);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndArpCompInd:Sending Attach complete"));

   /* Ideally this state check is part of EMM State machine  / module */
   /* But adding here, to prevent more errors in processing :) */
   /* ue002.101: Multi ue support changes */
   if(ueAppCb->emmCb.state != UE_EMM_UE_REG_INIT)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE013, (ErrVal)ueAppCb->emmCb.state,
      " ueAppSndArpCompInd : Could not send the Attach complete, Invalid state.\n");
      RETVALUE(RFAILED);
   }
   ret = ueAppSndAttachComplete(ueAppCb);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE014, (ErrVal)ret,
            " ueAppSndArpCompInd : ueAppSndAttachComplete failed. \
              Could not send the Attach complete.\n");
      RETVALUE(ret);
   }
   /* ue003.101: support for dedicated bearers */
#ifdef UESIM_TRIGGER_DRB_EST
   /* ue008.101: Send Dedicated Bearer  Resource Allocation Request */
   /*  ueAppStartTmr(UE_APP_BR_RES_TMR, UE_APP_BR_RES_TMR_VAL);*/
   ret = ueAppSndBrResAllocReq(ueAppCb);
#endif 


   RETVALUE(ret);

} /* End of ueAppSndArpCompInd */


/*
*
*       Fun:   ueAppSndAuthResponse
*       
*       Desc:  This function sends authentication response message 
*              to MME using EMM through eNodeB on RRC. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PRIVATE S16 ueAppSndAuthResponse
(
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppSndAuthResponse(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   CmNasEvnt   *authRspEvnt = NULLP;
   CmEmmAuthPrmRES authParmRes;
   S16 ret;

   TRC2(ueAppSndAuthResponse);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndAuthResponse:Sending Authentication response"));

   /* Fill authParmRes */
   cmMemset((U8*)&authParmRes, 0, sizeof(CmEmmAuthPrmRES));
   authParmRes.pres = TRUE;
   authParmRes.len = 16;
   ret = ueAppUtlBldAuthResp(ueAppCb, &authRspEvnt, &authParmRes);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE015, (ErrVal)ret,
            " ueAppSndAuthResponse: Could not send the Authentication response.\n");
      RETVALUE(ret);
   }

   /* ue002.101: Multi ue support changes */
   RETVALUE(ueAppEmmHdlOutUeEvnt(authRspEvnt,ueAppCb));
} /* End of ueAppSndAuthResponse */

/*
*
*       Fun:   ueAppSndIdResponse
*       
*       Desc:  This function sends ID response message to MME using EMM
*              through eNodeB on RRC. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PRIVATE S16 ueAppSndIdResponse
(
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppSndIdResponse(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   CmNasEvnt   *idRspEvnt = NULLP;
   S16 ret;

   TRC2(ueAppSndIdResponse);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndIdResponse:Sending ID response"));

   /* ue002.101: Multi ue support changes */
   ret = ueAppUtlBldIdentityResp(ueAppCb, &idRspEvnt);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE016, (ErrVal)ret,
            " ueAppSndIdResponse: Could not send the ID response.\n");
      RETVALUE(ret);
   }

   /* ue002.101: Multi ue support changes */
   RETVALUE(ueAppEmmHdlOutUeEvnt(idRspEvnt, ueAppCb));
} /* End of ueAppSndIdResponse */

/*
*
*       Fun:   ueAppSndSecModeComplete
*       
*       Desc:  This function sends Security mode complete message 
*              to MME using EMM through eNodeB on RRC. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PRIVATE S16 ueAppSndSecModeComplete
(
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppSndSecModeComplete(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   CmNasEvnt   *secModeCompEvnt = NULLP;
   S16 ret;

   TRC2(ueAppSndSecModeComplete);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppSndSecModeComplete:Sending security mode complete"));

   /* ue002.101: Multi ue support changes */
   ret = ueAppUtlBldSecModComplete(ueAppCb, &secModeCompEvnt);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE017, (ErrVal)ret,
         " ueAppSndSecModeComplete: Could not build  and send the \
         security mode complete.\n");
      RETVALUE(ret);
   }

   /* ue002.101: Multi ue support changes */
   RETVALUE(ueAppEmmHdlOutUeEvnt(secModeCompEvnt, ueAppCb));
} /* End of ueAppSndSecModeComplete */

/*
*
*       Fun:   ueAppRcvRRCConSetup
*       
*       Desc:  This function handles connection set up message from RRC
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppRcvRRCConSetup
(
NhuDatIndSdus *datIndSdus
)
#else
PUBLIC S16 ueAppRcvRRCConSetup(datIndSdus)
NhuDatIndSdus *datIndSdus;
#endif
{
   UeAppCb *ueAppCb;
   TRC2(ueAppRcvRRCConSetup);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppRcvRRCConSetup:Received Connection setup"));

   /* Initiate Attach Request now - This message is sent as
      NAS PDU with RRC Connection Setup Complete */

   /* ue002.101: Multi ue support: Get the ueAppCb from the
      ueId in the datIndSdus */
   printf("received connection setup for cellId %d, ueId %d\n", datIndSdus->hdr.cellId, datIndSdus->hdr.ueId);
   UE_GET_APPCB((datIndSdus->hdr.cellId),ueAppCb,(datIndSdus->hdr.ueId));
   if(ueAppCb != NULLP)
   {
      /* ue003.101: new feature addition */
      ueAppCb->ueId = datIndSdus->hdr.ueId; 
      /* Change ECM state of the UE to CONNECTED */
      ueAppCb->ecmCb.state = UE_ECM_CONNECTED;
      ueAppCb->cellId = datIndSdus->hdr.cellId;
      /* ue007.101: ccpu00117835 Transaction Id used same as recived from enb */
      ueAppCb->rcvdTxId.rrc_con_setupTxId =
                      datIndSdus->sdu.m.dlCcchMsg.ccchMsg.message.val.c1.val.rrcConSetup.rrc_TrnsxnId.val;
      if(ueAppCb->emmCb.state  == UE_EMM_UE_REGISTERED)
      {
         /* The UE is already registered and now sending the
          * Service Request message
          */
         RETVALUE(ueAppSndServiceRequest(ueAppCb));
      }
      else
      {
         /* The UE is not in EMM_REGISTERED state so we are sending the
          * Attach Request message
          */
         RETVALUE(ueAppSndAttachRequest(ueAppCb));
      }
   }
   else
   {
     UELOGERROR(ERRCLS_ADD_RES, EUE016, (ErrVal)ueAppCb->ueId,
           " ueAppRcvRRCConSetup: NULL ueAppCb \n");   
     RETVALUE(RFAILED);
   }
} /* End of ueAppRcvRRCConSetup */

/* ue003.101: Added for paging support */
/*
*
*       Fun:   ueAppRcvRRCPaging
*       
*       Desc:  This function handles Paging message from RRC
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppRcvRRCPaging
(
U16                   cellId,
NhuPCCH_Msg          *pcchMsg
)
#else
PUBLIC S16 ueAppRcvRRCPaging(cell,pcchMsg)
U16                   cellId;
NhuPCCH_Msg          *pcchMsg;
#endif
{
   /* ue008.101 : TIC_ID : ccpu00117550 MOD: Fixed warning for gcc compilation on CentOS*/
   NhuPag      *nhuPag = NULLP;
   /* ue008.101 : TIC_ID : ccpu00117550 MOD_END: Fixed warning for gcc compilation on CentOS*/
   NhuPagRecord *nhuPagRecord;
   Bool        isPagingValid = FALSE;
   Buffer      *msg3;
   U8          nmbRecords;
   U8          digit;
   U8          cnt=0;
   NhuIMSI_Digit tempDigit;

   TRC2(ueAppRcvRRCPaging);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppRcvRRCPaging:Received RRC Paging "));

   if(pcchMsg != NULLP)
   {
      nhuPag = &pcchMsg->message.val.c1.val.paging;
   }
  
   /* For the List of Paging Records based on the UE Identity type
     IMSI or s-TMSI check if the paging is relevant for this UE */ 
   if(nhuPag != NULLP)
   {
      if((nhuPag->pagingRecordLst.noComp.pres == PRSNT_NODEF) && (nhuPag->pagingRecordLst.noComp.val > 0))
      {
         /* For all ther records check if the value corresponds to this UE */
         for(nmbRecords = 0; nmbRecords < nhuPag->pagingRecordLst.noComp.val; nmbRecords++)
         {
            nhuPagRecord = &nhuPag->pagingRecordLst.member[nmbRecords]; 
            if(nhuPagRecord->pres.pres == TRUE)
            {
               if(nhuPagRecord->ue_Identity.choice.pres == TRUE)
               {
                  if(nhuPagRecord->ue_Identity.choice.val == PAGUE_IDENTITY_S_TMSI)
                  {
                     /* The UE Identity received in the Paging message is STMSI.
                      * Match the value of STMSI to see if the Paging message is
                      * for this UE. We assume that the paging message is for this
                      * UE. Single UE case.
                     */
                     if(nhuPagRecord->ue_Identity.val.s_TMSI.pres.pres == TRUE)
                     {
                        if(nhuPagRecord->ue_Identity.val.s_TMSI.mmec.pres == TRUE)
                        {
                           printf("\n MMEC is %d\n", nhuPagRecord->ue_Identity.val.s_TMSI.mmec.val[0]);
                        } /* end of if statement */
                        if(nhuPagRecord->ue_Identity.val.s_TMSI.m_TMSI.pres == TRUE)
                        {
                           for(cnt=0; cnt < 4; cnt++)
                           {
                              printf("\n M-TMSI is %d\n", nhuPagRecord->ue_Identity.val.s_TMSI.m_TMSI.val[cnt]);
                           }
                        } /* end of if statement */
   
                     } /* end of if statement */
   
                  }
                  else if(nhuPagRecord->ue_Identity.choice.val == PAGUE_IDENTITY_IMSI)
                  {
                     /* The UE Identity received in the Paging message is IMSI 
   
                      * Match the value of IMSI to see if the Paging message is
                      * for this UE. We assume that the paging message is for this
                      * UE. Single UE case. IMSI shall generally used for the case
                      * of Emergency calls.
                     */
                     /* ue004.101: Corrected condition expression */
                     for(digit =0; digit < nhuPagRecord->ue_Identity.val.imsi.noComp.val; digit++)
                     {
                        tempDigit = nhuPagRecord->ue_Identity.val.imsi.member[digit];
                        if(tempDigit.pres == PRSNT_NODEF)
                        {
                           printf("Digit[%d]= %c",digit, (S8)tempDigit.val);
                        }
                     }
                     printf("\n");
   
                  }
                  else
                  {
                     /* ue007.101: Fix to ccpu00117388 */
                     /* Compilation error after ERRCLS defined in make file */
                     UELOGERROR(ERRCLS_ADD_RES, EUE016, (ErrVal)nhuPagRecord->ue_Identity.choice.val,
                           " ueAppRcvRRCPaging : Received invalid UE Identity \n");   
                  }
               } /* end of if statement */
            }

            /* Assume that the S-TMSI matches. A Single Paging Record shall be sent
             * with the S-TMSI of the existing UE
             */
             isPagingValid = TRUE;
         } /* end of for loop */
      } /* end of if statement */
   } /* end of if statement */

   if(isPagingValid == TRUE)
   {
      CellCb *cell;
      ueUtlFndCell(cellId,&cell);
      if (cell != NULLP)
      {
         ueRrcBuildRRCConReq(&msg3, &cell->ueArr[0], TRUE);
         /* Assuming Single UE. Initiate the RACH procedure for the ueIdx == 0 */
         /* Construct the message 3 */
         ueMacRachReq(cell, &cell->ueArr[0], msg3);
      }
   }/* end of if statement */
    RETVALUE(ROK);   
} /* End of ueAppRcvRRCPaging*/



#ifdef LTE_START_UL_DL_DATA
PUBLIC S16 ueAppTti
(
CmLteTimingInfo    tti
)
{

   UeCb            *ueCb;
   Buffer          *buf;
#ifndef SS_CAVIUM   
   U32             dummy;
#endif
   S16             noPkts = 9;
   S16             i;
   U16             szOfPkt;

   TRC2(ueAppTti);
   /* For now we will check for a single UEs state */
   /* When active, we shall start UL data          */
   ueCb = &cellArr[0].ueArr[0];
   if (ueCb->drbEst == TRUE)
   {
      /* Generate data every 10 ms for now */
      if (tti.subframe == 0)
      {
         /* Allow few frames for E Nodeb to be seutp */
         if (ueCb->wait > 0)
         {
            ueCb->wait--;
         }
         else
         {
            if ( recvPkt < UE_NUM_UL_PKT )
            {
            szOfPkt =  ueCb->szOfLastPkt - 4;
            UE_ALLOC_BUF(buf);
            SAddPreMsgMult((Data *)&(ueCb->szOfLastPkt), 2, buf);
            SAddPstMsgMult((Data *)data, szOfPkt, buf);
            SAddPstMsgMult((Data *)&(ueCb->szOfLastPkt), 2, buf);
            ueCb->szOfLastPkt = (ueCb->szOfLastPkt + 100 )% 1500; 
            ueRlcDatReq(ueCb, 3, buf);
            ueCb->mac.reportBsr = TRUE;
            }
         }
      }
   }

#ifndef SS_CAVIUM   
   if ((tti.subframe == 0) && ((tti.sfn % 100) == 0))
   {
      SRegInfoShow(0, &dummy);
   }
#endif

   RETVALUE(ROK);
}
#endif /* LTE_START_UL_DL_DATA */

/* ue003.101: Added SI broadcast feature */
/*
*
*       Fun:   ueAppSibInd
*       
*       Desc:  This function prints the contents of BCCH-DLSCH message. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC Void ueAppSibInd
(
NhuBCCH_DL_SCH_Msg *bcchSchMsg
)
#else
PUBLIC S16 ueAppSibInd(bcchSchMsg)
NhuBCCH_DL_SCH_Msg *bcchSchMsg;
#endif
{
   NhuSysInfocriticalExtns *critExt = &(bcchSchMsg->message.val.c1.val.systemInfo.criticalExtns);
   NhuSysInfoBlockTyp2 *sib2 = NULLP;
   NhuSysInfoBlockTyp3 *sib3 = NULLP;
   NhuSysInfoBlockTyp4 *sib4 = NULLP;
   NhuSysInfoBlockTyp5 *sib5 = NULLP;
   U32 i, j;

   TRC2(ueAppSibInd);

   if (bcchSchMsg->message.val.c1.choice.val == C1_SYSTEMINFOBLOCKTYP1)
   {
      printf("ueAppSIBInd:Received SIB1\n");
   }
   else if (bcchSchMsg->message.val.c1.choice.val == C1_SYSTEMINFO)
   {
      switch(critExt->val.systemInfo_r8.sib_TypAndInfo.member[0].choice.val)
      {
         case MEMBER_SIB2:
            printf("ueAppSIBInd:Received SIB2\n");
            sib2 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[0].val.sib2);
         break;
         case MEMBER_SIB3:
            printf("ueAppSIBInd:Received SIB3\n");
            sib3 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[0].val.sib3);
            printf("q_Hyst = %d\n", (int)sib3->cellReselectionInfoCmn.q_Hyst.val);
            printf("t_Evaluation = %d\n",
            (int)sib3->cellReselectionInfoCmn.speedStateReselectionPars.mobilityStateParams.t_Evaluation.val);
            printf("t_HystNormal = %d\n",
            (int)sib3->cellReselectionInfoCmn.speedStateReselectionPars.mobilityStateParams.t_HystNormal.val);
            printf("n_CellChangeMedium = %d\n",
            (int)sib3->cellReselectionInfoCmn.speedStateReselectionPars.mobilityStateParams.n_CellChangeMedium.val);
            printf("n_CellChangeHigh = %d\n",
            (int)sib3->cellReselectionInfoCmn.speedStateReselectionPars.mobilityStateParams.n_CellChangeHigh.val);
            printf("q_HystSF.sf_Medium = %d\n",
            (int)sib3->cellReselectionInfoCmn.speedStateReselectionPars.q_HystSF.sf_Medium.val);
            printf("q_HystSF.sf_High = %d\n",
            (int)sib3->cellReselectionInfoCmn.speedStateReselectionPars.q_HystSF.sf_High.val);
            printf("s_NonIntraSearch = %d\n",
            (int)sib3->cellReselectionServingFreqInfo.s_NonIntraSearch.val);
            printf("threshServingLow = %d\n",
            (int)sib3->cellReselectionServingFreqInfo.threshServingLow.val);
            printf("cellReselectionPriority = %d\n",
            (int)sib3->cellReselectionServingFreqInfo.cellReselectionPriority.val);
            printf("q_RxLevMin = %d\n",
            (int)sib3->intraFreqCellReselectionInfo.q_RxLevMin.val);
            printf("p_Max = %d\n",
            (int)sib3->intraFreqCellReselectionInfo.p_Max.val);
            printf("s_IntraSearch = %d\n",
            (int)sib3->intraFreqCellReselectionInfo.s_IntraSearch.val);
            printf("allowedMeasBandwidth = %d\n",
            (int)sib3->intraFreqCellReselectionInfo.allowedMeasBandwidth.val);
            printf("presenceAntennaPort1 = %d\n",
            (int)sib3->intraFreqCellReselectionInfo.presenceAntennaPort1.val);
            printf("neighCellConfig.len = %d\n",
            (int)sib3->intraFreqCellReselectionInfo.neighCellConfig.len);
            printf("neighCellConfig.val = %s\n",
            sib3->intraFreqCellReselectionInfo.neighCellConfig.val);
            printf("t_ReselectionEUTRA = %d\n",
            (int)sib3->intraFreqCellReselectionInfo.t_ReselectionEUTRA.val);
         break;
         case MEMBER_SIB4:
            printf("ueAppSIBInd:Received SIB4\n");
            sib4 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[0].val.sib4);
            printf("intraFreqNeighCellLst.noComp = %d\n",
            (int)sib4->intraFreqNeighCellLst.noComp.val);
            for (i=0; i < sib4->intraFreqNeighCellLst.noComp.val; i++)
            {
               printf("physCellId[%d] = %d\n", 
               (int)i, (int)sib4->intraFreqNeighCellLst.member[i].physCellId.val);
               printf("q_OffsetCell[%d] = %d\n", 
               (int)i, (int)sib4->intraFreqNeighCellLst.member[i].q_OffsetCell.val);
            }
            printf("intraFreqBlackCellLst.noComp = %d\n",
            (int)sib4->intraFreqBlackCellLst.noComp.val);
            for (i=0; i < sib4->intraFreqBlackCellLst.noComp.val; i++)
            {
               printf("intraFreqBlackCellLst.start[%d] = %d\n", 
               (int)i, (int)sib4->intraFreqBlackCellLst.member[i].start.val);
               printf("intraFreqBlackCellLst.range[%d] = %d\n", 
               (int)i, (int)sib4->intraFreqBlackCellLst.member[i].range.val);
            }
            printf("csg_PhysCellIdRange.start = %d\n", 
            (int)sib4->csg_PhysCellIdRange.start.val);
            printf("csg_PhysCellIdRange.range = %d\n", 
            (int)sib4->csg_PhysCellIdRange.range.val);
         break;
         case MEMBER_SIB5:
            printf("ueAppSIBInd:Received SIB5\n");
            sib5 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[0].val.sib5);
            printf("interFreqCarrierFreqLst.noComp = %d\n", 
            (int)sib5->interFreqCarrierFreqLst.noComp.val);
            for (i = 0; i < sib5->interFreqCarrierFreqLst.noComp.val; i++)
            {
               printf("dl_CarrierFreq[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].dl_CarrierFreq.val);
               printf("q_RxLevMin[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].q_RxLevMin.val);
               printf("p_Max.pres[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].p_Max.pres);
               printf("t_ReselectionEUTRA[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].t_ReselectionEUTRA.val);
               printf("threshX_High[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].threshX_High.val);
               printf("threshX_Low[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].threshX_Low.val);
               printf("allowedMeasBandwidth[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].allowedMeasBandwidth.val);
               printf("presenceAntennaPort1[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].presenceAntennaPort1.val);
               printf("cellReselectionPriority[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].cellReselectionPriority.val);
               printf("neighCellConfig[%d] = %s\n", 
               (int)i, sib5->interFreqCarrierFreqLst.member[i].neighCellConfig.val);
               printf("q_OffsetFreq[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].q_OffsetFreq.val);
               printf("interFreqNeighCellLst.noComp[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].interFreqNeighCellLst.noComp.val);
               for (j = 0; j < sib5->interFreqCarrierFreqLst.member[i].\
                    interFreqNeighCellLst.noComp.val; j++)
               {
                  printf("physCellId[%d][%d] = %d\n", 
                  (int)i, (int)j, (int)sib5->interFreqCarrierFreqLst.member[i].
                  interFreqNeighCellLst.member[j].physCellId.val);
                  printf("q_OffsetCell[%d][%d] = %d\n", 
                  (int)i, (int)j, (int)sib5->interFreqCarrierFreqLst.member[i].
                  interFreqNeighCellLst.member[j].q_OffsetCell.val);
               }
               printf("interFreqBlackCellLst.noComp[%d] = %d\n", 
               (int)i, (int)sib5->interFreqCarrierFreqLst.member[i].interFreqBlackCellLst.noComp.val);
               /* ue0010.101: Fixed Compilaion error,
                * when defining LTERRC_REL9 compile time flag */
               for (j = 0; j < sib5->interFreqCarrierFreqLst.member[i].\
                    interFreqBlackCellLst.noComp.val; j++)
               {
                  printf("physCellIdRange.start[%d][%d] = %d\n", 
                  (int)i, (int)j, (int)sib5->interFreqCarrierFreqLst.member[i].
                  interFreqBlackCellLst.member[j].start.val);
                  printf("physCellIdRange.range[%d][%d] = %d\n", 
                  (int)i, (int)j, (int)sib5->interFreqCarrierFreqLst.member[i].
                  interFreqBlackCellLst.member[j].range.val);
               }
            }
         break;
         default:
               printf("ueAppSIBInd: Invalid SIB recieved \n"); 
         break;
      }
   }
   RETVOID;

} /* End of ueAppSibInd*/

/* ue007.101: Sending Detach Accept to Nw initiated Detach Req */
/*
 *
 *       Fun:   ueAppSndDetachAccept
 *       
 *       Desc:  This function sends detach accept message 
 *              to MME using EMM through eNodeB on RRC. 
 *       
 *       Ret:   ROK
 *       
 *       Notes: None
 *              
 *       File:  ue_app.c
 *       
 */

#ifdef ANSI
PRIVATE S16 ueAppSndDetachAccept
(
 UeAppCb *ueAppCb
 )
#else
PRIVATE S16 ueAppSndDetachAccept(ueAppCb)
   UeAppCb *ueAppCb;
#endif
{
   CmNasEvnt   *detAcceptEvnt = NULLP;
   S16 ret;
   S16 idx;

   TRC2(ueAppSndDetachAccept);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndDetachAccept:Detach accept"));

   ret = ueAppUtlBldDetachAcc(ueAppCb, &detAcceptEvnt);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE017, (ErrVal)ret,
            " ueAppSndDetachAccept: Could not build  and send the \
            detach request .\n");
      RETVALUE(ret);
   }

   ueAppEmmHdlOutUeEvnt(detAcceptEvnt, ueAppCb);

   printf("Sent detach accept for ueId %d\n",ueAppCb->ueId);
   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndDetachAccept:  Sent Detach acceptSuccessfully "));
   /* Resetting ueAppCb */
   ueAppCb->ecmCb.state = UE_ECM_IDLE;
   ueAppCb->transIdCntr = 0;
   ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_IDLE;
   ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_NONE;
   ueAppCb->emmCb.esmPiggyBacked = TRUE;

   /* Delete TRANS and BID EsmCbs */
   for(idx=0; idx < CM_ESM_MAX_BEARER_ID; idx++)
   {
      if(ueAppCb->esmTList[idx] != NULLP)
      {
         ueAppUtlDelEsmCb(ueAppCb->esmTList[idx], ueAppCb);
         ueAppCb->esmTList[idx] = NULLP;
      }
      if(ueAppCb->esmBList[idx] != NULLP)
      {
         ueAppUtlDelEsmCb(ueAppCb->esmBList[idx], ueAppCb);
         ueAppCb->esmBList[idx] = NULLP;
      }
   }

/* ue008.101: MULTI_UE_ATTACH Support */
#ifdef MULTI_UE_ATTACH
   /* Set the MultiAttach flag to indicate that
    * Multi-attach timer has been started    */ 
   if(!ueSimAppCb.multAtchStrt)
   { 
       ueSimAppCb.multAtchStrt++;
       ueSimAppCb.multAtchStrt%=UE_NUM_PER_CELL;

      //Start detach timer when the first Attach is received ;)
      /* ue007.101: Starting multiple attach timer */
      printf("\n\n\nPSINGH_DEBUG: ueAppSndDetachAccept: Starting multiple attach timer\n");
      ueAppStartTmr(ueAppCb->cellId,UE_APP_MULT_ATTACH_TMR, UE_APP_MULT_ATTACH_VAL);
   }
   else
   {
      printf("\n\n\nPSINGH_DEBUG: ++++ueAppCellCb.multAtchStrt =%d \n\n", ueSimAppCb.multAtchStrt);
   } 

#else
   /* Starting multiple attach timer */
   printf("\nStarting multiple attach timer\n");
   ueAppStartTmr(ueAppCb->cellId,UE_APP_MULT_ATTACH_TMR, UE_APP_MULT_ATTACH_VAL);
   RETVALUE(ROK);
#endif

   /* ue008.101: Returning ROK in case of success */
   RETVALUE(ROK);
} /* End of ueAppSndDetachAccept */

/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
/*
*
*       Fun:   ueAppSndServiceReqMsg 
*       
*       Desc:  This is trigger Service Request Procedure ue in EMM Idle state
*              
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppSndServiceReqMsg 
(
 UeAppCb     *ueAppCb
 )
#else
PUBLIC S16 ueAppSndServiceReqMsg(ueAppCb)
   UeAppCb     *ueAppCb;
#endif
{
   Buffer      *msg3;

   TRC2(ueAppSndServiceReqMsg);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndServiceReqMsg:Sending a message to eNB"));
   ueRrcBuildRRCConReq(&msg3, &cellArr[0].ueArr[0], TRUE);
   /* Assuming Single UE. Initiate the RACH procedure for the ueIdx == 0 */
   /* Construct the message 3 */
   ueMacRachReq(&cellArr[0], &cellArr[0].ueArr[0], msg3);
   RETVALUE(ROK);

}
#ifdef TOTAL_ENB
/* ue009.101: Added feature to drop the diffrent RRC messages.
 * depends on the RRC timer. */
/* RRC RE-EST START */
/*
 * 
 *        Fun:   ueAppRcvRRCConReestab
 *        
 *        Desc:  This function handles connection set up message from RRC
 *        
 *        Ret:   ROK
 *        
 *        Notes: None
 *               
 *        File:  ue_app.c
 *        
 */
#ifdef ANSI
PUBLIC S16 ueAppRcvRRCConReestab
(
NhuDatIndSdus *datIndSdus
)
#else
PUBLIC S16 ueAppRcvRRCConReestab(datIndSdus)
NhuDatIndSdus *datIndSdus;
#endif
{
   UeAppCb *ueAppCb;
   U16   ret;
   U32   transId;
   NhuDatReqSdus *pdu;
   TRC2(ueAppRcvRRCConReestab);

   UE_DBGP_INFO((UE_PRNTBUF,
            " Recevied ueAppRcvRRCConReestab: RRC Con Re-establishment  from ENB"));

   /* Initiate Attach Request now - This message is sent as
    *       NAS PDU with RRC Connection Setup Complete */

   /* ue002.101: Multi ue support: Get the ueAppCb from the */
   transId = datIndSdus->sdu.m.dlCcchMsg.ccchMsg.message.val.c1.val.rrcConReestb.rrc_TrnsxnId.val;

   UE_GET_APPCB(datIndSdus->hdr.cellId,ueAppCb,(datIndSdus->hdr.ueId));
   if(ueAppCb != NULLP)
   {
      /* ue003.101: new feature addition */
      ueAppCb->ueId = datIndSdus->hdr.ueId; 
      ueAppCb->cellId = datIndSdus->hdr.cellId;
      /* ue007.101: ccpu00117835 Transaction Id used same as recived from enb */
      ueAppCb->rcvdTxId.rrc_con_reestbTxId =
         datIndSdus->sdu.m.dlCcchMsg.ccchMsg.message.val.c1.val.rrcConReestb.rrc_TrnsxnId.val;

   }
   ueAppCb->isReest = TRUE;
   ret = ueAppUtlBldRRCReEstlmntCmpltMsg(&pdu, transId);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE024, (ErrVal)ret,
            "ueAppLimHdlRRCConReCfg : Could not build the RRC \
            Reconfiguration Complete\n");
      RETVALUE(ret);
   }

   if(ueAppLimSndRRCMsg(pdu, ueAppCb)!= ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE016, (ErrVal)ueAppCb->ueId,
            " ueAppRcvRRCConSetup: NULL ueAppCb \n");   
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppRcvRRCConReestabRej
 *       
 *       Desc:  This function handles connection set up message from RRC
 *       
 *       Ret:   ROK
 *      
 *       Notes: None
 *              
 *       File:  ue_app.c
 *       
 */

#ifdef ANSI
PUBLIC S16 ueAppRcvRRCConReestabRej
(
 NhuDatIndSdus *datIndSdus
 )
#else
PUBLIC S16 ueAppRcvRRCConReestabRej(datIndSdus)
   NhuDatIndSdus *datIndSdus;
#endif
{
   UeAppCb *ueAppCb;
   TRC2(ueAppRcvRRCConReestabRej);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppRcvRRCConReestabRej :Received Connection Re-establishment Reject"));

   RETVALUE(ROK);
}
/* RRC-REEST END*/
#endif
/**********************************************************************
 
         End of file:     ue_app.c@@/main/1 - Sun Mar 28 22:59:20 2010
 
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
/main/1      ---      vp                  1. Initial Release.
/main/1+   ue002.101  sv                  1. Multi ue support changes.
/main/1+   ue003.101  rp                  1. Added support for paging.
                                          2. Added support for dedicated bearers
                                          3. Added support TA and SIB
/main/1+   ue004.101  rk                  1. Corrected for loop condition 
                                             expression in ueAppRcvRRCPaging
/main/1+   ue006.101  sgm                 1. Fix for CID:1465-02-01, DefectId:
                                             ccpu00116336. Removing the compiler 
                                             warning.
               sriky               2. Performance tuning
               sriky                      2. Performance tuning
/main/1+  ue007.101   ms            1. Transaction ID used from enodeb.               
                                    2.  Compilation error after ERRCLS defined
                                        in make file.     
                                    3.  unused varibale removed and macro added for e2e perf. 
                      rk            1. Fix for CID:1465-02-01, DefectId: 117388
                                       Fixed segmentaion fault if failure to 
                                       initialize uesim application
                                    2. Added support for Multiple attach and detach.
                                    3. Added support for Network initiated Detach.
/main/1+  ue008.101   ragrawal      1. CRID:ccpu00117391 ERAB RELEASE support.            
                                    2. MULTI_UE_ATTACH Support.
                                    3. Fix for compilation warnings.
                                    4. Added new header file inclusion.
                                    5. Added new function SndUEInitDtachReq().
                                    6. Send Dedicated Bearer  Resource Allocation
                                       Request in ueAppRcvEmmMsg() and ueAppSndArpCompInd().
/main/1+  ue009.101   akaranth      1. Added feature to drop the RRC messages depends on the RRC timer.
/main/1+  ue010.101   akaranth      1. Fixed compilation error, when defining 
                                       LTERRC_REL9 compile time flag.
 *********************************************************************91*/
