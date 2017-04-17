

/************************************************************************
 
     Name:     LTE UE Simulator
  
     Type:     C source file
  
     Desc:     C source code for PAL
  
     File:     ue_pal.c
  
     Sid:      ue_pal.c@@/main/1 - Sun Mar 28 22:59:25 2010
  
     Prg:      vp
  
**********************************************************************/

/* header include files -- defines (.h) */
#include <sched.h>
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#ifndef NOFILESYS
#include "cm_os.h"         /* file operations */
#endif
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_pasn.h"        /* common LTE */
#include "nhu_asn.h"
#ifndef SS_CAVIUM
#include "pcap.h"          /* common tokens */
#endif /* SS_CAVIUM */
/* ue007.101: cavium compile warning fix */
#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-wqe.h"
#endif /* SS_CAVIUM */

#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
#include "tfu.h"
#include "ue.h"            /* UE Includes */
#include "ue_err.h"

/* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD 
#include "LtePhyL2Api.h" /* Phy api file */
#include "apidefs.h"     /* Phy api file */
#include "resultcodes.h" /* Phy api file */
#include "osal.h"
#endif /* YS_MSPD*/
#include <stdlib.h>      /* ue007.101: warning exit */
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
#ifndef NOFILESYS
#include "cm_os.x"         /* file operations */
#endif
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

#include "lys.h"
#include "lys.x"

#include "ctf.h"
#include "ctf.x"
/* ue002.101: Changes to support MSPD CL */
#ifndef YS_MSPD
#include "ys_pal.h"
#include "ys_pal.x"
#endif

/* ue0010.101: Enahnced measurement feature */
UeNetWorkParam   *uenetworkparam = NULL; 
#if (!defined(NOFILESYS) || !defined(SS_CAVIUM))
/* End of OSAL Definitions */
PRIVATE S16 ueSimInitCfg(Void);

U32 UE_APP_SELF_ETH_INF_ADDR;
U32 UE_APP_SELF_PDN_ADDR;
U32 UE_APP_DATA_SRVR_ADDR;
U32 UE_APP_DATA_SRVR_PORT;
/* ue009.101: Added feature to drop the diffrent RRC messages.
 *  depends on the RRC timer. */
U32 UE_RRC_TIMER;

PRIVATE S8 ueSimCfgParams[][UESIM_MAX_CFG_PARAM_LEN] =
{
   "UE_APP_SELF_ETH_INF_ADDR",
   "UE_APP_SELF_PDN_ADDR",
   "UE_APP_DATA_SRVR_ADDR",
   "UE_APP_DATA_SRVR_PORT",
/* ue009.101: Added feature to drop the diffrent RRC messages.
 *  depends on the RRC timer. */
   "UE_RRC_TIMER",
/* ue010.101: Enhanced measurement feature */
   "YS_ENB1_TAC",
   "YS_ENB2_TAC",
   "YS_ENB3_TAC",
   "YS_ENB4_TAC",
   "YS_ENB5_TAC",
   "YS_ENB1_ECI",
   "YS_ENB2_ECI",           
   "YS_ENB3_ECI",           
   "YS_ENB4_ECI",           
   "YS_ENB5_ECI",           
   "YS_ENB1_MCC",
   "YS_ENB2_MCC",       
   "YS_ENB3_MCC",      
   "YS_ENB4_MCC",       
   "YS_ENB5_MCC",       
   "YS_ENB1_MNC",
   "YS_ENB2_MNC",       
   "YS_ENB3_MNC",      
   "YS_ENB4_MNC",       
   "YS_ENB5_MNC",       
   "YS_ENB1_CGI",
   "YS_ENB2_CGI",
   "YS_ENB3_CGI",
   "YS_ENB4_CGI",
   "YS_ENB5_CGI",
   "YS_ENB1_RSRP",
   "YS_ENB2_RSRP",
   "YS_ENB3_RSRP",
   "YS_ENB4_RSRP",
   "YS_ENB5_RSRP",
   "YS_ENB1_RSRQ",
   "YS_ENB2_RSRQ",
   "YS_ENB3_RSRQ",
   "YS_ENB4_RSRQ",
   "YS_ENB5_RSRQ"
};
#endif

#ifdef YS_MSPD
U16 YS_PORT_ENB;
U16 YS_PORT_UE;
U8  YS_IP_ADDR_ENB[YS_IP_ADDR_STR_LEN];
U8  YS_IP_ADDR_UE[YS_IP_ADDR_STR_LEN];

PRIVATE S8 ysCfgParams[][YS_MAX_CFG_PARAM_LEN] =
{
   "YS_IP_ADDR_ENB",
   "YS_IP_ADDR_UE",
   "YS_PORT_ENB",
   "YS_PORT_UE"
};
#endif


#ifdef YS_MSPD
PRIVATE S16 ysInitCfg(Void);
#ifdef YS_MSPD_OSAL
PUBLIC S16 MsgDispatchInit (Void);
#endif

/* OSAL Definitions */
extern OSAL_HEAP OsalGlobalHeap;
OSAL_MEMARRAY MsgArray;
OSAL_PADDRESS MsgArrayMem;

#define MSG_MAXMSG 128
#endif /* YS_MSPD*/

PUBLIC UeMsSrCfgInfo        ueSrCfgDb[UE_NUM_SR_CFG];
PUBLIC UeMsSrsCfgInfo       ueSrsCfgDb[UE_NUM_SRS_CFG];
PUBLIC UeMsCqiPmiCfgIdxInfo ueCqiPmiCfgDb[UE_NUM_CQI_CFG];
PUBLIC UeRiCfgIdxInfo       ueRiCfgDb[UE_NUM_RI_CFG];

PUBLIC CellCb cellArr[UE_NUM_CELL];


EXTERN S16 ueAppActvInit ARGS((Ent    entity,
                               Inst   inst,
                               Region region,
                               Reason reason));

EXTERN S16 ueAppActvTsk ARGS((Pst           *pst,
                              Buffer        *mBuf));

PRIVATE S16 initCell( Void);
/* ue003.101: latency computation */
#ifdef UE_COMPUTE_LATENCY
EXTERN TimeDelayInfo tmDelayInfo;
#endif

/*
 *       Fun:    initUe
 * 
 *       Desc:   This function shall initialize a UE
 *
 *       Ret:    ROK 
 *
 *       Notes:  None 
 *
 *       File:   ue_pal.c
 */

#ifdef ANSI           
PUBLIC S16 initUe
(
UeCb *ue,
U8 cellId,
U8 ueId
)
#else
PUBLIC S16 initUe (ue, cellId, ueId)
UeCb *ue;
U8 cellId;
U8 ueId;
#endif
{
   U8 idx;

   /* ue008.101: Fix for cellId as other than 1 */ 
   ue->cellId = cellArr[cellId].cellId;
   ue->rnti   = 0xffff;
   ue->ueId   = ueId;
   ue->state  = 0;
#ifdef ENB_PERF_MEAS
   ue->ueAppState = 0;
#endif
   ue->drbEst = FALSE;
   ue->wait   = 10;
   ue->szOfLastPkt = 40; 

   UE_DBGP_INFO((UE_PRNTBUF, 
         "initUe: Initializing the UE with ueId %d", ueId));

   for(idx=0; idx<UE_NUM_RLC_RB_PER_UE; idx++)
   {
      /* ue002.101: Changes to support RLC UM mode */ 
      ue->rlc.rbArr[idx].cur_um_seq = 0;
      ue->rlc.rbArr[idx].rcvd_um_seq = 0;
      ue->rlc.rbArr[idx].cur_am_seq = 0;
      ue->rlc.rbArr[idx].rcvd_am_seq = 0;
      
      ue->rlc.snLen = 2; /* 10 bits SN Len */

      ue->rlc.rbArr[idx].ackToBeSent = FALSE;
      ue->rlc.rbArr[idx].mBuf = NULLP;
      ue->rlc.rbArr[idx].bo = 0;
      ue->rlc.rbArr[idx].lcId = idx;
   }
   ue->mac.reportBsr  = FALSE;
   ue->mac.srReq      = FALSE;
   ue->mac.preambleId = 0xff;
/* ue003.101: timing advance changes */
#ifdef TA_NEW
   cmInitTimers(&ue->mac.taAlgntmr, 1);
   cmInitTimers(&ue->mac.taChngtmr, 1);
   cmInitTimers(&ue->mac.taAppltmr, 1);
   ue->mac.ulSyncStatus = FALSE;
#endif

   /* ue002.101: Changes to support MSPD CL */ 
#ifdef YS_MSPD
   ue->srCfgInfo      = NULLP;
   ue->srsCfgInfo     = NULLP;
   ue->cqiCfgInfo     = NULLP;
#ifdef YS_MSPD_OSAL 
   MsgDispatchInit();
#endif
#endif /* YS_MSPD*/

   RETVALUE(ROK);
} /* end of initUe */

#ifdef YS_MSPD
#ifdef YS_MSPD_OSAL
#ifdef ANSI
PUBLIC S16 MsgDispatchInit
(
Void
)
#else
PUBLIC S16 MsgDispatchInit()
#endif
{
   if (OsalAllocHeap(&OsalGlobalHeap, &MsgArrayMem, MSG_MAXSIZE * MSG_MAXMSG) != SUCCESS)
   {
      return FAILURE;
   }
   OsalCreateMemArray(&MsgArray, MsgArrayMem, MSG_MAXSIZE * MSG_MAXMSG, MSG_MAXSIZE);
   return SUCCESS;

}
#endif /* YS_MSPD_OSAL */
#endif /* YS_MSPD*/
/* 
 *       Fun:    initCell
 * 
 *       Desc:   This function shall initialize  Cells.
 * 
 *       Ret:    ROK 
 * 
 *       Notes:  None 
 *
 *       File:   ue_pal.c
 */
#ifdef ANSI
PRIVATE S16 initCell
(
Void
)
#else
PRIVATE S16 initCell(void)
#endif
{
   U8          cellIdx;

   U8          ueIdx;
   Buffer      *msg3;
/* ue003.101: timing advance changes */
#ifdef TA_NEW
   U8          i;
#endif

   UE_DBGP_INFO((UE_PRNTBUF, 
         "initCell: Initializing all the cells"));


   for(cellIdx=0; cellIdx< UE_NUM_CELL; cellIdx++)
   {
   /* ue002.101: Changes to support MSPD CL */ 
#ifdef YS_MSPD
      /*initialize the Pst */
      cellArr[cellIdx].pst.dstProcId = SFndProcId();
      cellArr[cellIdx].pst.srcProcId = SFndProcId();
      cellArr[cellIdx].pst.dstEnt = ENTTF;
      cellArr[cellIdx].pst.srcEnt = ENTTF;
      cellArr[cellIdx].pst.srcInst = 0;
      cellArr[cellIdx].pst.dstInst = 0;
      cellArr[cellIdx].pst.route = RTESPEC;
      cellArr[cellIdx].pst.prior = PRIOR0;
      cellArr[cellIdx].pst.region = 0; 
      cellArr[cellIdx].pst.pool = 0;
      cellArr[cellIdx].pst.selector = 1;
      cellArr[cellIdx].suId = 0;
#endif /* YS_MSPD*/

      cellArr[cellIdx].bw = UE_MAX_BW;
   /* ue002.101: Changes to support TDD Configuration */ 
      cellArr[cellIdx].dlUlCfg  = LTE_TDD_CFG_TYPE_5;
      cmLListInit(&cellArr[cellIdx].rachLst);
      
      /* Initializing cellId and start Rnti for each cell */
      cellArr[cellIdx].cellId = UE_APP_CELL_ID + cellIdx;
      cellArr[cellIdx].startRnti =  (UE_START_RNTI + (UE_CELL_RNTI_SPACE_DIFF * cellIdx));
   /* ue003.101: timing advance changes */
#ifdef TA_NEW
      cellArr[cellIdx].tmrTqCp.nxtEnt = 0;
      cellArr[cellIdx].tmrTqCp.tmrLen = UE_MAX_TMR_Q;
      for (i=0; i<UE_MAX_TMR_Q; i++)
      {
         cellArr[cellIdx].tmrTq[i].first = NULLP;
         cellArr[cellIdx].tmrTq[i].tail  = NULLP;
      }
#endif
      for(ueIdx=0; ueIdx < UE_NUM_PER_CELL; ueIdx++)
      {
        initUe(&(cellArr[cellIdx].ueArr[ueIdx]), cellIdx, ueIdx);
#if 0
/* ue003.101: changes to pass UeInfo for bld */
        ueRrcBuildRRCConReq(&msg3 ,&(cellArr[cellIdx].ueArr[ueIdx]), FALSE);
        ueMacRachReq(&cellArr[cellIdx], &cellArr[cellIdx].ueArr[ueIdx], msg3);
#endif
      } 
    
      ueMacInit(&cellArr[cellIdx]);
   }
   
/* ue003.101: latency computation */
#ifdef UE_COMPUTE_LATENCY
   memset(&tmDelayInfo, 0, sizeof(TimeDelayInfo));
#endif
   RETVALUE(ROK);
}

/*
 *       Fun:    startFunc
 * 
 *       Desc:   This function initializes the active tasks.
 *
 *       Ret:    ROK 
 *
 *       Notes:  None 
 *
 *       File:   ue_pal.c
 */
#ifdef ANSI
PUBLIC S16 tst
(
)
#else
PUBLIC S16 tst()
#endif
{
   SSTskId tskId;

   /* ue002.101: Changes to support MSPD CL */ 
   S16     idx;
/* ue003.101: Mac initialization */

   /* Init Cell and UE Cb */
   initCell();

   SCreateSTsk(0, &tskId);

   /* ue002.101: Changes to support MSPD CL */ 
#ifdef YS_MSPD
   if ((ysInitCfg()) != ROK)
   {
      RETVALUE (RFAILED);
   }
#endif

   /* ue002.101: Changes to support reading uesim configuration
      from file: uesim_cfg.txt */ 
#if (!defined (NOFILESYS) || !defined(SS_CAVIUM))
   if ((ueSimInitCfg()) != ROK)
   {
      RETVALUE (RFAILED);
   }
#endif

   SRegTTsk (UE_ENT_APP, 0, TTNORM, 0, ueAppActvInit, ueAppActvTsk);
   SAttachTTsk(UE_ENT_APP, 0, tskId);

   /* ue002.101: Changes to support MSPD CL */ 
#ifdef YS_MSPD
   /* Start the receiver thread */
   ysMsUePalInitRcvrTsk();
#endif
/* ue003.101: Removed mac initialization */
  
   ueAppTmrInit();

   /* initialize SR Configuration DB */
   for(idx = 0; idx < UE_NUM_SR_CFG; idx++)
   {
      ueSrCfgDb[idx].srCfgIndex = idx;

      if(idx <= 4)
      {
         ueSrCfgDb[idx].srPeriod = 5;
         ueSrCfgDb[idx].srSfOffSet = idx;
      }
      else if (idx >= 5 && idx <= 14)
      {
         ueSrCfgDb[idx].srPeriod = 10;
         ueSrCfgDb[idx].srSfOffSet = idx - 5;
      }
      else if (idx >= 15 && idx <= 34)
      {
         ueSrCfgDb[idx].srPeriod = 20;
         ueSrCfgDb[idx].srSfOffSet = idx - 15;
      }
      else if (idx >= 35 && idx <= 74)
      {
         ueSrCfgDb[idx].srPeriod = 40;
         ueSrCfgDb[idx].srSfOffSet = idx - 35;
      }
      else if (idx >= 75 && idx <= 154)
      {
         ueSrCfgDb[idx].srPeriod = 80;
         ueSrCfgDb[idx].srSfOffSet = idx - 75;
      }
      else if (idx >=155 && idx <=156)
      {
         ueSrCfgDb[idx].srPeriod = 2;
         ueSrCfgDb[idx].srSfOffSet = idx - 155;
      }
      else if (idx == 157)
      {
         ueSrCfgDb[idx].srPeriod = 1;
         ueSrCfgDb[idx].srSfOffSet = idx - 157;
      }
      else
      {
         printf("Invalid SR Configuration %d\n",idx);
         RETVALUE (RFAILED);
      }
   }

   /* initialize SRS Configuration DB */
   /* 3GPP Spec 36.213 Table 8.2-1 */
   for(idx = 0; idx < UE_NUM_SRS_CFG; idx++)
   {
      ueSrsCfgDb[idx].srsCfgIndex = idx;

      if(idx <= 1)
      {
         ueSrsCfgDb[idx].srsPeriod = 2;
         ueSrsCfgDb[idx].srsSfOffSet = idx;
      }
      else if (idx >= 2 && idx <= 6)
      {
         ueSrsCfgDb[idx].srsPeriod = 5;
         ueSrsCfgDb[idx].srsSfOffSet = idx - 2;
      }
      else if (idx >= 7 && idx <= 16)
      {
         ueSrsCfgDb[idx].srsPeriod = 10;
         ueSrsCfgDb[idx].srsSfOffSet = idx - 7;
      }
      else if (idx >= 17 && idx <= 36)
      {
         ueSrsCfgDb[idx].srsPeriod = 20;
         ueSrsCfgDb[idx].srsSfOffSet = idx - 17;
      }
      else if (idx >= 37 && idx <= 76)
      {
         ueSrsCfgDb[idx].srsPeriod = 40;
         ueSrsCfgDb[idx].srsSfOffSet = idx - 37;
      }
      else if (idx >= 77 && idx <= 156)
      {
         ueSrsCfgDb[idx].srsPeriod = 80;
         ueSrsCfgDb[idx].srsSfOffSet = idx - 77;
      }
      else if (idx >= 157 && idx <= 316)
      {
         ueSrsCfgDb[idx].srsPeriod = 160;
         ueSrsCfgDb[idx].srsSfOffSet = idx - 157;
      }
      else if (idx >= 317 && idx <= 636)
      {
         ueSrsCfgDb[idx].srsPeriod = 320;
         ueSrsCfgDb[idx].srsSfOffSet = idx - 317;
      }
      else
      {
         printf("Invalid SRS Configuration SRS(%d)\n", idx);
         RETVALUE (RFAILED);
      }
   }

   /* initialize Cqi-Pmi Configuration DB */
   /* 3GPP Spec 36.213 7.2.2-1A */
   for(idx = 0; idx < UE_NUM_CQI_CFG; idx++)
   {
      ueCqiPmiCfgDb[idx].cqiPmiCfgIndex = idx;

      if(idx >= 0 && idx <= 2)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 2;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx;
      }
      else if (idx >= 2 && idx <= 6)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 5;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 2;
      }
      else if (idx >= 7 && idx <= 16)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 10;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 7;
      }
      else if (idx >= 17 && idx <= 36)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 20;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 17;
      }
      else if (idx >= 37 && idx <= 76)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 40;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 37;
      }
      else if (idx >= 77 && idx <= 156)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 80;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 77;
      }
      else if (idx >= 157 && idx <= 316)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 160;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 157;
      }
      else if (idx >= 317 && idx <= 349)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 32;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 318;
      }
      else if (idx >= 350 && idx <= 413)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 64;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 350;
      }
      else if (idx >= 414 && idx <= 541)
      {
         ueCqiPmiCfgDb[idx].cqiPeriod = 128;
         ueCqiPmiCfgDb[idx].cqiSfOffSet = idx - 414;
      }
      else
      {
         printf("Invalid Configuration CQI(%d) \n",idx);
         RETVALUE (RFAILED);
      }
   }

   /* initialize ri Configuration DB */
   /* 3GPP Spec 36.213 7.2.2-1A */
   for(idx = 0; idx < UE_NUM_RI_CFG; idx++)
   {
      ueRiCfgDb[idx].riCfgIndex = idx;

      if(idx >= 0 && idx <= 160)
      {
         ueRiCfgDb[idx].mRi = 1;
         ueRiCfgDb[idx].riOffset = -idx;
      }
      else if (idx >= 161 && idx <= 321)
      {
         ueRiCfgDb[idx].mRi = 2;
         ueRiCfgDb[idx].riOffset = -(idx - 161);
      }
      else if (idx >= 322 && idx <= 482)
      {
         ueRiCfgDb[idx].mRi = 4;
         ueRiCfgDb[idx].riOffset = -(idx - 322);
      }
      else if (idx >= 483 && idx <= 643)
      {
         ueRiCfgDb[idx].mRi = 8;
         ueRiCfgDb[idx].riOffset = -(idx - 483);
      }
      else if (idx >= 644 && idx <= 804)
      {
         ueRiCfgDb[idx].mRi = 16;
         ueRiCfgDb[idx].riOffset = -(idx - 644);
      }
      else if (idx >= 805 && idx <= 965)
      {
         ueRiCfgDb[idx].mRi = 32;
         ueRiCfgDb[idx].riOffset = -(idx - 805);
      }
      else
      {
         printf("Invalid Configuration RI(%d) \n",idx);
         RETVALUE (RFAILED);
      }
   }   

   /* In case of PAL, CL spawns the receiver thread. So
    * starting up CL at the end to ensure that everything
    * else is initialised.
    */
#ifndef YS_MSPD
   SRegTTsk (ENTTF, 0, TTNORM, 0, ysActvInit, ysActvTsk);
   SAttachTTsk(ENTTF, 0, tskId);
#endif

   RETVALUE(ROK);
} /* end of tst*/


/* ue002.101: Changes to support reading uesim configuration
   from file: uesim_cfg.txt */ 
#if (!defined(NOFILESYS) || !defined(SS_CAVIUM)) 
/*
 *
 *       Fun:    ueSimInitCfg
 *
 *       Desc:   This function is called during uesim initialization for
 *               reading the configuration file
 *
 *       Ret:    S16 (ROK, RFAILED)
 *
 *       Notes:  1. Reads configuration file uesim_cfg.txt
 *
 *       File:   ue_main.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueSimInitCfg
(
Void
)
#else
PRIVATE S16 ueSimInitCfg(Void)
#endif
{
   S8               line[UESIM_MAX_CFG_FILE_LINE_LEN];
   OsFile           *fp = NULLP;
   S8               *ret1 = NULLP;
   U32              idx = 0;
   S32              lineNo = 0;
   U8               numParams;
   S8               *lPtr;
   S8               word[UESIM_MAX_CFG_PARAM_LEN];
   U8               lineLen;
   Bool             inToken = TRUE;
/* ue010.101 : Enhanced measurement feature */
   /* TODO :Need to change from malloc to TAPA function */
   uenetworkparam = (UeNetWorkParam*)malloc(sizeof(UeNetWorkParam));
   if(uenetworkparam == NULL)
   {
      printf("Not ablte to allocate memorey \n");
      RETVALUE(RFAILED);
   }

/* ue003.101: Removed unuesd variables */

   TRC2(ueSimInitCfg);

   if((fp = (OsFile*)osFopen("uesim_cfg.txt","r")) == (S32)NULLP)
   {
      /* ue007.101: Fix to ccpu00117388 */
      /* configuration file checking */
      UEAPP_LOGERROR(ERRCLS_DEBUG, 0, (ErrVal)0,
             "FAILED to open the file uesim_cfg.txt\n");
      exit(0);
   } /* if */

   numParams = sizeof(ueSimCfgParams)/UESIM_MAX_CFG_PARAM_LEN;

   lineNo = 1;

   for (;;)
   {
      cmMemset((U8*)line, 0, UESIM_MAX_CFG_FILE_LINE_LEN);

      ret1 = osFgets(line, UESIM_MAX_CFG_FILE_LINE_LEN, fp);

      if (ret1 == (S8*)-1 || ret1 == NULLD) /* eof or NULL */
      {
         UE_DBGP_ERROR((UE_PRNTBUF, "End of File reached, uesim_cfg.txt\n"));
         break;
      }

      if (!(lineLen = osStripBlanks(line)))
      {
         lineNo++;
         continue;   /* blank line */
      }

      if (*line == '#')
      {
         lineNo++;
         continue;   /* blank line */
      }

      lPtr = line;

      /* Get each of the words from the line */
      while ((lPtr = osGetWord(lPtr, word)) != NULLP)
      {
         if (word[0] == '#')
         {
            break;
         }

         if (inToken)
         {
            /* Compare the word with the list of tokens */
            for (idx = 0; idx < numParams; idx++)
            {
               if(!osStrcmp(word, ueSimCfgParams[idx]))
               {
                  inToken = FALSE;
                  break;
               }
            }
            if (idx == numParams)
            {
               UE_DBGP_ERROR((UE_PRNTBUF, " invalid configuration parameter \n"));
               if(fp) osFclose(fp);
               RETVALUE (RFAILED);
            }
         }
         else
         {
            /* Now based on the index store the configuration values */
            switch(idx)
            {
               case 0: /* UE_APP_SELF_ETH_INF_ADDR */
                  {
                     cmInetAddr(word, &UE_APP_SELF_ETH_INF_ADDR);
                     UE_APP_SELF_ETH_INF_ADDR = CM_INET_NTOH_U32(UE_APP_SELF_ETH_INF_ADDR);
                     break;
                  }
               case 1: /* UE_APP_SELF_PDN_ADDR */
                  {
                     cmInetAddr(word, &UE_APP_SELF_PDN_ADDR);
                     UE_APP_SELF_PDN_ADDR = CM_INET_NTOH_U32(UE_APP_SELF_PDN_ADDR);
                     break;
                  }
               case 2: /* UE_APP_DATA_SRVR_ADDR */
                  {
                     cmInetAddr(word, &UE_APP_DATA_SRVR_ADDR);
                     UE_APP_DATA_SRVR_ADDR = CM_INET_NTOH_U32(UE_APP_DATA_SRVR_ADDR);
                     break;
                  }
               case 3: /* UE_APP_DATA_SRVR_PORT */
                  {
                     UE_APP_DATA_SRVR_PORT = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
                  /* ue009.101: Added feature to drop the diffrent RRC messages.
                   *  depends on the RRC timer. */
               case 4:/*RRC TIMER */
                  {
                     UE_RRC_TIMER = (U16)osStrtol(word, NULL, 10);
                     break; 
                  }
                  /* ue010.101: Enhanced measurement feature */
               case 5: /* YS_ENB1_TAC */
                  {
                     uenetworkparam->ueenbtac.ys_enb1_tac = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 6: /* YS_ENB2_TAC */
                  {
                     uenetworkparam->ueenbtac.ys_enb2_tac = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 7: /* YS_ENB3_TAC */
                  {
                     uenetworkparam->ueenbtac.ys_enb3_tac = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 8: /* YS_ENB4_TAC */
                  {
                     uenetworkparam->ueenbtac.ys_enb4_tac = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 9: /* YS_ENB5_TAC */
                  {
                     uenetworkparam->ueenbtac.ys_enb5_tac = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 10: /* YS_ENB1_ECI */
                  {
                     uenetworkparam->ueenbeci.ys_enb1_eci = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 11: /* YS_ENB2_ECI */
                  {
                     uenetworkparam->ueenbeci.ys_enb2_eci = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 12: /* YS_ENB3_ECI */
                  {
                     uenetworkparam->ueenbeci.ys_enb3_eci = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 13: /* YS_ENB4_ECI */
                  {
                     uenetworkparam->ueenbeci.ys_enb4_eci = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 14: /* YS_ENB5_ECI */
                  {
                     uenetworkparam->ueenbeci.ys_enb5_eci = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 15: /* YS_ENB1_MCC */
                  {
                     uenetworkparam->ueenbmcc.ys_enb1_mcc= (U16)osStrtol(word, NULL, 10);
                     {
                         U32 mcc = uenetworkparam->ueenbmcc.ys_enb1_mcc ;
                         int i = 0;
                         printf("\n ** MCC ** %d\n",mcc);
                         for(i = 0 ; i < 3 ; i++)
                         {
                            printf("%d ", (mcc%10));
                            mcc = mcc/10;
                          }
                         printf("\n ** THE END**\n");
                     }
                     break;
                  }
               case 16: /* YS_ENB2_MCC */
                  {
                     uenetworkparam->ueenbmcc.ys_enb2_mcc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 17: /* YS_ENB3_MCC */ 
                  {
                     uenetworkparam->ueenbmcc.ys_enb3_mcc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 18:/* YS_ENB4_MCC */
                  {
                     uenetworkparam->ueenbmcc.ys_enb4_mcc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 19:/* YS_ENB5_MCC*/
                  {
                     uenetworkparam->ueenbmcc.ys_enb5_mcc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 20: /* YS_ENB1_MNC */
                  {
                     uenetworkparam->ueenbmnc.ys_enb1_mnc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 21: /* YS_ENB2_MNC */
                  {
                     uenetworkparam->ueenbmnc.ys_enb2_mnc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 22:/* YS_ENB3_MNC */
                  {

                     uenetworkparam->ueenbmnc.ys_enb3_mnc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 23:/* YS_ENB4_MNC */
                  {

                     uenetworkparam->ueenbmnc.ys_enb4_mnc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 24:/* YS_ENB5_MNC */
                  {

                     uenetworkparam->ueenbmnc.ys_enb5_mnc= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 25: /* YS_ENB1_CGI */
                  {
                     uenetworkparam->ueenbcgi.ys_enb1_cgi= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 26: /* YS_ENB2_CGI */
                  {
                     uenetworkparam->ueenbcgi.ys_enb2_cgi= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 27: /* YS_ENB3_CGI */
                  {
                     uenetworkparam->ueenbcgi.ys_enb3_cgi= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 28: /* YS_ENB4_CGI */
                  {
                     uenetworkparam->ueenbcgi.ys_enb4_cgi= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 29: /* YS_ENB5_CGI */
                  {
                     uenetworkparam->ueenbcgi.ys_enb5_cgi= (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 30: /* YS_ENB1_RSRP */
                  {
                     uenetworkparam->ueenbrsrp.ys_enb1_rsrp = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 31: /* YS_ENB2_RSRP */
                  {
                     uenetworkparam->ueenbrsrp.ys_enb2_rsrp = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 32: /* YS_ENB3_RSRP */
                  {
                     uenetworkparam->ueenbrsrp.ys_enb3_rsrp = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 33: /* YS_ENB4_RSRP */
                  {
                     uenetworkparam->ueenbrsrp.ys_enb4_rsrp = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 34: /* YS_ENB5_RSRP */
                  {
                     uenetworkparam->ueenbrsrp.ys_enb5_rsrp = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 35: /* YS_ENB1_RSRQ */
                  {
                     uenetworkparam->ueenbrsrq.ys_enb1_rsrq = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 36: /* YS_ENB2_RSRQ */
                  {
                     uenetworkparam->ueenbrsrq.ys_enb2_rsrq = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 37: /* YS_ENB3_RSRQ */
                  {
                     uenetworkparam->ueenbrsrq.ys_enb3_rsrq = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 38: /* YS_ENB4_RSRQ */
                  {
                     uenetworkparam->ueenbrsrq.ys_enb4_rsrq = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               case 39: /* YS_ENB5_RSRQ */
                  {
                     uenetworkparam->ueenbrsrq.ys_enb5_rsrq = (U16)osStrtol(word, NULL, 10);
                     break;
                  }
               default:
                  {
                     break;
                  }
            }
            inToken = TRUE;
         }

         cmMemset((U8*)word, 0, UESIM_MAX_CFG_PARAM_LEN);

      }
   } /* End of for loop */

   if(fp) osFclose(fp);

   RETVALUE (ROK);
}
#endif

#ifdef YS_MSPD
/**
 * @Configuration file read function.
 *
 * @details
 *
 *     Function : ysInitCfg
 *
 *     This function is called suring the CL's initialization for
 *     reading the CL configuration file
 *
 *  @param[in]  NONE
 *  @return  S16
 *        - # ROK
 *        - # RFAILED
 **/
#ifdef ANSI
PUBLIC S16 ysInitCfg
(
Void
)
#else
PUBLIC S16 ysInitCfg (Void)
#endif
{
   S8               line[YS_MAX_CFG_FILE_LINE_LEN];
   OsFile           *fp = NULLP;
   S8               *ret1 = NULLP;
   U32              idx = 0;
   S32              lineNo = 0;
   U8               numParams;
   S8               *lPtr;
   S8               word[YS_MAX_CFG_PARAM_LEN];
   U8               lineLen;
   Bool             inToken = TRUE;

   TRC2(ysInitCfg);

   if((fp = (OsFile*)osFopen("ys_cfg.txt","r")) == (S32)NULLP)
   {
      UE_DBGP_ERROR((UE_PRNTBUF, "FAILED to open the file ys_cfg.txt\n"));
      RETVALUE (RFAILED);
   } /* if */

   numParams = sizeof(ysCfgParams)/YS_MAX_CFG_PARAM_LEN;

   lineNo = 1;

   for (;;)
   {
      cmMemset((U8*)line, 0, YS_MAX_CFG_FILE_LINE_LEN);

      ret1 = osFgets(line, YS_MAX_CFG_FILE_LINE_LEN, fp);

      if (ret1 == (S8*)-1 || ret1 == NULLD) /* eof or NULL */
      {
         UE_DBGP_ERROR((UE_PRNTBUF, "End of File reached, ys_cfg.txt\n"));
         break;
      }

      if (!(lineLen = osStripBlanks(line)))
      {
         lineNo++;
         continue;   /* blank line */
      }

      if (*line == '#')
      {
         lineNo++;
         continue;   /* blank line */
      }

      lPtr = line;

      /* Get each of the words from the line */
      while ((lPtr = osGetWord(lPtr, word)) != NULLP)
      {
         if (word[0] == '#')
         {
            break;
         }

         if (inToken)
         {
            /* Compare the word with the list of tokens */
            for (idx = 0; idx < numParams; idx++)
            {
               if(!osStrcmp(word, ysCfgParams[idx]))
               {
                  inToken = FALSE;
                  break;
               }
            }
            if (idx == numParams)
            {
               UE_DBGP_ERROR((UE_PRNTBUF, " invalid configuration parameter \n"));
               if(fp) osFclose(fp);
               RETVALUE (RFAILED);
            }
         }
         else
         {
            /* Now based on the index store the configuration values */
            switch(idx)
            {
               case 0: /* YS_IP_ADDR_ENB */
               {
                  osStrcpy((S8 *)YS_IP_ADDR_ENB, word);
                  break;
               }
               case 1: /* YS_IP_ADDR_UE */
               {
                  osStrcpy((S8 *)YS_IP_ADDR_UE, word);
                  break;
               }
               case 2: /* YS_PORT_ENB */
               {
                  YS_PORT_ENB = (U16)osStrtol(word, NULL, 10);
                  break;
               }
               case 3: /* YS_PORT_UE */
               {
                  YS_PORT_UE = (U16)osStrtol(word, NULL, 10);
                  break;
               }
               default:
               {
                  break;
               }
            }
            inToken = TRUE;
         }

         cmMemset((U8*)word, 0, YS_MAX_CFG_PARAM_LEN);

      }
   } /* End of for loop */

   if(fp) osFclose(fp);

   RETVALUE (ROK);
}
#endif /* YS_MSPD */

/**********************************************************************
 
         End of file:     ue_pal.c@@/main/1 - Sun Mar 28 22:59:25 2010
 
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
                                       2. Changes to support reading 
                                          uesim configuration from file.
                                       3. Changes to support MSPD CL.
/main/1+   ue003.101  rp               1. Timing advance support changes.
                                       2. Latency computation  changes.
/main/1+   ue007.101  rk               1. Fix for DefectId: ccpu00117388
                                          Exit if failed to open configuration file.
                      ms               1. configuration file checking.                                       
/main/1+  ue008.101  ragrawal          1. Fix for cellId as other than 1.
/main/1+  ue009.101  akaranth          1. Added feature to drop RRC messages, depends on the RRC timer.
/main/1+  ue010.101  akaranth          1. Enhanced measurement feature.
 *********************************************************************91*/

