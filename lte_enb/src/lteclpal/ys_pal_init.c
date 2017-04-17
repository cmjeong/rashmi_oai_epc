
/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_init.c
  
     Sid:      yw_init.c@@/main/3 - Thu Dec  2 03:31:41 2010
  
     Prg:      pk
  
**********************************************************************/
/* ys005.102 : Since configuration parameters in the ys_cfg.txt at eNodeb
 * UESIM differs.By default this flag always must be enabled at the eNodeB 
 * side. */
#ifdef YS_ENB_CFG
/** @file ys_init.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"
#ifndef NOFILESYS
#include "cm_os.h"         /* file operations */
#endif

/* ys005.102 : Included SS_4GMX_LCORE flag in below check */
#if !(defined SS_CAVIUM || defined SS_4GMX_LCORE)
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */


#ifdef YS_MSPD
#else
#include "ys_pal.h"            /* defines and macros for CL */
#include <sys/time.h>
#endif
#include <stdlib.h>        /*  ys004.102 :186 : exit warning */
#include "ys_pal_err.h"        /* YS error defines */
#include <stdlib.h>        /* ys004.102 : CR 7528 exit warning */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#ifndef NOFILESYS
#include "cm_os.x"         /* file operations */
#endif

/* ys005.102 : Included SS_4GMX_LCORE flag in below check */
#if !(defined SS_CAVIUM || defined SS_4GMX_LCORE)
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */


#ifdef YS_MSPD
#else
#include "ys_pal.x"            /* typedefs for CL */
#endif


#ifdef YS_LTE_PAL
PRIVATE S16 ysPalInit ARGS (( Region region));
#endif



#ifndef NOFILESYS
U32  YS_TTI_TMR_VAL_CFG;/* ys004.102 : CR 7531 TTI configured*/
U16 YS_PORT_ENB;
U16 YS_PORT_UE;
U8  YS_IP_ADDR_ENB[YS_IP_ADDR_STR_LEN];
U8  YS_IP_ADDR_UE[YS_IP_ADDR_STR_LEN];
U8 WIRESHARK_SRVR_IP_ADDR[YS_IP_ADDR_STR_LEN]; /* ys005.102 : Wireshark changes */ 
U16 YS_CELL_ID; /* ys005.102 : Cell Id changes */          
U16 ysPalNumCells = 1;

PRIVATE S8 ysCfgParams[8][YS_MAX_CFG_PARAM_LEN] = 
{
   "YS_IP_ADDR_ENB",
   "YS_IP_ADDR_UE",
   "YS_PORT_ENB",
   "YS_PORT_UE",
   "YS_TTI_TMR_VAL_CFG",
   "WIRESHARK_SRVR_IP_ADDR", 
   "YS_CELL_ID"            ,
   "YS_NUM_CELLS"
};

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
 *     -# ROK 
 *     -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16  ysInitCfg
(
Void
)
#else
PUBLIC S16  ysInitCfg (Void)
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
      /* ys004.102 : Defect 117186 */
      /* Configuration file check */
      YSLOGDBGERR(0, 0, "FAILED to open the file ys_cfg.txt\n");
      exit(0);
   } /* if */
   /* ys004.102 Kworks warning fix*/
   numParams = (U8)(sizeof(ysCfgParams)/YS_MAX_CFG_PARAM_LEN);

   lineNo = 1;

   for (;;)
   {
      cmMemset((U8*)line, 0, YS_MAX_CFG_FILE_LINE_LEN);

      ret1 = osFgets(line, YS_MAX_CFG_FILE_LINE_LEN, fp);

      if (ret1 == (S8*)-1 || ret1 == NULLD) /* eof or NULL */
      {
         YS_DBG_ERR((_ysp, "End of File reached, ys_cfg.txt\n"));
         break;
      }
      /* ys004.102 Kworks warnings fix*/
      if (!(lineLen = (U8)(osStripBlanks(line))))
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
               if (idx == numParams)
               {
                  YS_DBG_ERR((_ysp, " invalid configuration parameter \n"));
                  if(fp) osFclose(fp);
                  RETVALUE(RFAILED);
               }
            }/*ys004.102 Kworks warning fix*/
         }
         else
         {
            /* Now based on the index store the configuration values */
            switch(idx)
            {
               case 0: /* YS_IP_ADDR_ENB */
               {
                  osStrcpy((S8*)YS_IP_ADDR_ENB, word);
                  break;
               }
               case 1: /* YS_IP_ADDR_UE */
               {
                  osStrcpy((S8*)YS_IP_ADDR_UE, word);
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
               case 4:/* ys004.102 : CR 7531 TTI configured */ 
               {
                  YS_TTI_TMR_VAL_CFG = (U32)osStrtol(word, NULL, 10);
                  break;
               }
               /* ys005.102 : Wireshark changes */
               case 5: /* added case 5 */ 
               {
                   osStrcpy((S8*)WIRESHARK_SRVR_IP_ADDR, word);
                   break;
               }
               /* ys005.102 : Cell Id changes */
               case 6: /* YS_CELL_ID */
               {
                  YS_CELL_ID = (U16)osStrtol(word, NULL, 10);    
                  break;
               }

               case 7: /* YS_NUM_CELLS */
               {
                  ysPalNumCells = (U16)osStrtol(word, NULL, 10);
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

   RETVALUE(ROK);
}
#endif
#ifdef MSPD
extern void SetMacInstanceId(UINT32 MacId);
extern U32 YsLiMsgHandler (Void * ysCtx, Void * msg);
/* ys005.102 : Deleted ysCtx variable */
/* ys005.102 : Introduced new variable */
static U32  ysMsgList = 0;
#endif

/**
 * @brief Task Initiation callback function. 
 *
 * @details
 *
 *     Function : ysActvInit
 *     
 *     This function is supplied as one of parameters during CL's 
 *     task registration. SSI will invoke this function once, after
 *     it creates and attaches this Tapa Task to a system task.
 *     
 *  @param[in]  Ent entity, the entity Id of this task.     
 *  @param[in]  Inst inst, the instance Id of this task.
 *  @param[in]  Region region, the region Id registered for memory 
 *              usage of this task.
 *  @param[in]  Reason reason.
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 ysActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 ysActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
{
#ifndef YS_MSPD
   U16  idx;
#endif
#ifdef YS_MS_PHY
   MXRC ret;
#endif

   TRC2(ysActvInit);

   /* Initialize the CL TskInit structure to zero */
   cmMemset ((U8 *)&ysCb, 0, sizeof(ysCb));

   /* Initialize the CL TskInit with received values */
   ysCb.ysInit.ent = entity;
   ysCb.ysInit.inst = inst;
   ysCb.ysInit.region = region;
#ifdef MSPD
   ysCb.ysInit.pool = 0;
#else
   ysCb.ysInit.pool = 3; /* Changing from 0 to 3 for performance */
#endif
   ysCb.ysInit.reason = reason;
   ysCb.ysInit.cfgDone = FALSE;
   ysCb.ysInit.acnt = FALSE;
   ysCb.ysInit.usta = FALSE;
   ysCb.ysInit.trc = FALSE;
   ysCb.trcLen = 0; 
#ifdef DEBUGP
#ifdef MSPD
   ysCb.ysInit.dbgMask = 0x0;
   ysCb.ysInit.dbgMask = YS_DBGMASK_FATAL;
#else
#ifdef YS_DEBUG
   ysCb.ysInit.dbgMask = 0xffffffff; 
#endif
#endif
#endif /* DEBUGP */
   ysCb.ysInit.procId = SFndProcId();

   /* Initialize CTF sap state */
   ysCb.ctfSap.sapState = LYS_NOT_CFG;

#ifndef NOFILESYS
   if ((ysInitCfg()) != ROK)
   {
      RETVALUE (RFAILED);
   }
#endif

#ifndef YS_MSPD
   for (idx=0; idx < YS_TQ_SIZE; idx++)
   {
      ysCb.tmrTq[idx].first = NULLP;
      ysCb.tmrTq[idx].tail  = NULLP;
   }
   ysCb.tmrTqCp.nxtEnt = 0;
   ysCb.tmrTqCp.tmrLen = YS_TQ_SIZE;

   cmInitTimers(&(ysCb.tmr), 1);
#endif

#ifdef YS_LTE_PAL
   ysPalInit(region);
#endif /* YS_LTE_PAL */

/* ys005.102 : Wireshark changes */
#ifdef  YS_WIRESHARK_LOG
  ysInitLogWireless();
#endif


   RETVALUE(ROK);
} /* ysActvInit */
#ifdef MSPD
#define PID_MAC_PROCESSING_THREAD   30000

U32 MacGetTick(void)
{
    return *(volatile U32 *)0xFE050004;
}


PUBLIC U32 YsLiMsgHandler (Void * ysCtx, Void * msg)
{

   U32 size = 0;
   /* sdass_ssi */
   static Bool firstMsg = TRUE;
   volatile int t = MacGetTick();
   /* ys005.102: Introduced new local variable */
   int t2;
   YsCellCb *cellCb;
   /* ys005.102: Introduced new local variable */
   U32       isList = ysCtx == (void *)&ysMsgList ? TRUE : FALSE;
   /*uart_printf("YsLiMsgHandler %x\n", *(U32*)msg);*/
   /* ysCtx is not used ignore */

   /* sdass_ssi */
   if (firstMsg)
   {
      MxSetThreadPriority(MxGetCurrentThread(),0);
      firstMsg = FALSE;
   }

   /* ys005.102 :Change in passing arugument of below functions  */
   MacDispatch(isList, (PTR)msg);
   MLogTask(PID_MAC_PROCESSING_THREAD, RESOURCE_LARM, t, t2 = MacGetTick());
   MLogTask(PID_L2_PROCESSING, RESOURCE_LARM, t, t2);

   RETVALUE(SUCCESS);
}
#endif


#ifdef YS_LTE_PAL
#ifdef ANSI
PRIVATE S16 ysPalInit
(
Region region
)
#else
PRIVATE S16 ysPalInit(region)
Region region;
#endif
{
   YsTfuSapCb    *tfuSap;
   YsCellCb      *cellCb;
   U16           indx;

   TRC2(ysPalInit);
#ifdef LTE_PAL_ENB
   /*ys004.102:Cell Delete CRID:ccpu00117556*/
   /*TTI Thread Initilization*/
   if(!ysCb.ttiReady)
   {
      ysPalInitTti();
   }
#endif

   /* set the cfgDone to TRUE */
   ysCb.ysInit.cfgDone = TRUE;

   /* Initialize CTF sap */
   /* Since no LM, set state ubnd */
   ysCb.ctfSap.spId     = 0;
   ysCb.ctfSap.suId     = 0;
   ysCb.ctfSap.sapState = LYS_UNBND;
   ysCb.ctfSap.sapPst.selector  = YS_SELECTOR_LC;
   ysCb.ctfSap.sapPst.dstProcId = SFndProcId();
   ysCb.ctfSap.sapPst.srcProcId = SFndProcId();
   ysCb.ctfSap.sapPst.dstEnt    = ENTVE;
   ysCb.ctfSap.sapPst.srcEnt    = ENTTF;
   ysCb.ctfSap.sapPst.region    = region;

   /* Initialize CTF sap for MAC communications */
   /* Since no LM, set state ubnd */
   for(indx = 0; indx < ysPalNumCells; indx++)
   {
      tfuSap = (YsTfuSapCb *) ysUtlMalloc(sizeof(YsTfuSapCb));

      if(NULLP == tfuSap)
      {
         RETVALUE(RFAILED);
      }
      tfuSap->spId     = indx;
      tfuSap->suId     = 0;
      tfuSap->sapState = LYS_UNBND;
      tfuSap->sapPst.selector  = YS_SELECTOR_TC;
      tfuSap->sapPst.dstProcId = SFndProcId();
      tfuSap->sapPst.srcProcId = SFndProcId();
      tfuSap->sapPst.dstEnt    = ENTRG;
      tfuSap->sapPst.dstInst   = indx;
      tfuSap->sapPst.srcEnt    = ENTTF;
      tfuSap->sapPst.region    = region;

      ysCb.tfuSapLst[indx] = tfuSap;
      tfuSap = NULLP;
   }

   for(indx = 0; indx < ysPalNumCells; indx++)
   {
      tfuSap = (YsTfuSapCb *) ysUtlMalloc(sizeof(YsTfuSapCb));

      if(NULLP == tfuSap)
      {
         RETVALUE(RFAILED);
      }

      /* 
       * When we have maximum number of cells, will have 
       * 0 to max cell - 1 number of MAC instance and will
       * have one SAP per MAC instance. Hence 
       * the SCHD SAP spId starts from max cell 
       */

      tfuSap->spId     = indx + ysPalNumCells;
      tfuSap->suId     = indx;
      tfuSap->sapState = LYS_UNBND;
      tfuSap->sapPst.selector  = YS_SELECTOR_TC;
      tfuSap->sapPst.dstProcId = SFndProcId();
      tfuSap->sapPst.srcProcId = SFndProcId();
      tfuSap->sapPst.dstEnt    = ENTRG;
      /* 
       * When we have maximum number of cells, will have 
       * 0 to max cell - 1 number of MAC instance. Hence 
       * the SCHD instance starts from max cell 
       */
      tfuSap->sapPst.dstInst   = indx + ysPalNumCells;
      tfuSap->sapPst.srcEnt    = ENTTF;
      tfuSap->sapPst.region    = region;

      ysCb.schTfuSapLst[indx] = tfuSap;
      tfuSap = NULLP;
   }

   for(indx = 0; indx < ysPalNumCells; indx++)
   {
      cellCb = (YsCellCb *) ysUtlMalloc(sizeof(YsCellCb));

      if(NULLP == cellCb)
      {
         RETVALUE(RFAILED);
      }

      cellCb->cellId = indx + 1;

      cellCb->peerPst.dstProcId = YS_DST_PROCID;
      cellCb->peerPst.srcProcId = SFndProcId();
      cellCb->peerPst.dstEnt    = ENTTF;
      cellCb->peerPst.srcEnt    = ENTTF;
      cellCb->peerPst.region    = region;
      cellCb->peerPst.pool    = ysCb.ysInit.pool; 
      cellCb->peerPst.selector  = YS_SELECTOR_LC;
      cellCb->tfuSap = ysCb.tfuSapLst[indx];
      cellCb->schTfuSap = ysCb.schTfuSapLst[indx];

      ysCb.cellCb[indx] = cellCb;
      cellCb = NULLP;
   }

  /* Initialize Cell control block */
/* ys005.102 : Cell Id changes */
#ifndef SS_CAVIUM
   ysPalInitRcvrTsk();
#endif
   
   RETVALUE(ROK);
} /* ysPalInit */
#endif /* YS_LTE_PAL */


/* ys005.102 : Reading the uesim configuration parameters from ys_cfg.txt.
 * This flag must always disabled at UESIM side */ 

#else /* YS_ENB_CFG */

/** @file ys_init.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"
#ifndef NOFILESYS
#include "cm_os.h"         /* file operations */
#endif

#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */


#ifdef YS_MSPD
#else
#include "ys_pal.h"            /* defines and macros for CL */
#endif

#include <sys/time.h>
#include "ys_pal_err.h"        /* YS error defines */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#ifndef NOFILESYS
#include "cm_os.x"         /* file operations */
#endif

#ifndef SS_CAVIUM
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */


#ifdef YS_MSPD
#else
#include "ys_pal.x"            /* typedefs for CL */
#endif


#ifdef YS_LTE_PAL
PRIVATE S16 ysPalInit ARGS (( Region region));
#endif



#ifndef NOFILESYS

U16 YS_PORT_ENB[YS_MAX_ENB_SUPP];
U16 YS_PORT_UE;
U16 YS_NUM_ENBS;
U8  YS_IP_ADDR_ENB[YS_MAX_ENB_SUPP][YS_IP_ADDR_STR_LEN];
U8  YS_IP_ADDR_UE[YS_IP_ADDR_STR_LEN];
U8  YS_ENB_PCI[YS_MAX_ENB_SUPP];
U8  YS_ENB_CELLID[YS_MAX_ENB_SUPP];
U8  actvIdx;

PRIVATE S8 ysCfgParams[][YS_MAX_CFG_PARAM_LEN] = 
{
   "YS_IP_ADDR_UE",
   "YS_PORT_UE",
   "YS_NUM_ENBS",
   "YS_IP_ADDR_ENB1",
   "YS_IP_ADDR_ENB2",
   "YS_IP_ADDR_ENB3",
   "YS_IP_ADDR_ENB4",
   "YS_IP_ADDR_ENB5",
   "YS_PORT_ENB1",
   "YS_PORT_ENB2",
   "YS_PORT_ENB3",
   "YS_PORT_ENB4",
   "YS_PORT_ENB5",
   "YS_ENB1_PCI",
   "YS_ENB2_PCI",
   "YS_ENB3_PCI",
   "YS_ENB4_PCI",
   "YS_ENB5_PCI",
   "YS_ENB1_CELLID",
   "YS_ENB2_CELLID",
   "YS_ENB3_CELLID",
   "YS_ENB4_CELLID",
   "YS_ENB5_CELLID"
};

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
 *     -# ROK 
 *     -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16  ysInitCfg
(
Void
)
#else
PUBLIC S16  ysInitCfg (Void)
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
      YS_DBG_ERR((_ysp, "FAILED to open the file ys_cfg.txt\n"));
      RETVALUE(RFAILED);
   } /* if */

   numParams = sizeof(ysCfgParams)/YS_MAX_CFG_PARAM_LEN;

   lineNo = 1;

   for (;;)
   {
      cmMemset((U8*)line, 0, YS_MAX_CFG_FILE_LINE_LEN);

      ret1 = osFgets(line, YS_MAX_CFG_FILE_LINE_LEN, fp);

      if (ret1 == (S8*)-1 || ret1 == NULLD) /* eof or NULL */
      {
         YS_DBG_ERR((_ysp, "End of File reached, ys_cfg.txt\n"));
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
               YS_DBG_ERR((_ysp, " invalid configuration parameter \n"));
               if(fp) osFclose(fp);
               RETVALUE(RFAILED);
            }
         }
         else
         {
            /* Now based on the index store the configuration values */
            switch(idx)
            {
               case 0: /* YS_IP_ADDR_UE */
               {
                  osStrcpy((S8*)YS_IP_ADDR_UE, word);
                  break;
               }
               case 1: /* YS_PORT_UE */
               {
                  YS_PORT_UE = (U16)osStrtol(word, NULL, 10);
                  break;
               }
               case 2: /* YS_NUM_ENBS */
               {
                  YS_NUM_ENBS = (U16)osStrtol(word, NULL, 10);
                  break;
               }
               case 3: /* YS_IP_ADDR_ENB1 */
               case 4: /* YS_IP_ADDR_ENB2 */
               case 5: /* YS_IP_ADDR_ENB3 */
               case 6: /* YS_IP_ADDR_ENB4 */
               case 7: /* YS_IP_ADDR_ENB5 */
               {
                  osStrcpy((S8*)YS_IP_ADDR_ENB[idx - 3], word);
                  break;
               }
               case 8:  /* YS_PORT_ENB1 */
               case 9:  /* YS_PORT_ENB2 */
               case 10: /* YS_PORT_ENB3 */
               case 11: /* YS_PORT_ENB4 */
               case 12: /* YS_PORT_ENB5 */
               {
                  YS_PORT_ENB[idx - 8] = (U16)osStrtol(word, NULL, 10);
                  break;
               }
               case 13: /* YS_ENB1_PCI */
               case 14: /* YS_ENB2_PCI */
               case 15: /* YS_ENB3_PCI */
               case 16: /* YS_ENB4_PCI */
               case 17: /* YS_ENB5_PCI */
               {
                  YS_ENB_PCI[idx - 13]= (U16)osStrtol(word, NULL, 10);
                  break;
               }
               case 18: /* YS_ENB1_CELLID */
               case 19: /* YS_ENB2_CELLID */
               case 20: /* YS_ENB3_CELLID */
               case 21: /* YS_ENB4_CELLID */
               case 22: /* YS_ENB5_CELLID */
               {
                  YS_ENB_CELLID[idx - 18]= (U16)osStrtol(word, NULL, 10);
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

   /* Active index is zero. By default we communicate with enodeb 1 */
   actvIdx = 0; 

   if(fp) osFclose(fp);

   RETVALUE(ROK);
}
#endif

/**
 * @brief Task Initiation callback function. 
 *
 * @details
 *
 *     Function : ysActvInit
 *     
 *     This function is supplied as one of parameters during CL's 
 *     task registration. SSI will invoke this function once, after
 *     it creates and attaches this Tapa Task to a system task.
 *     
 *  @param[in]  Ent entity, the entity Id of this task.     
 *  @param[in]  Inst inst, the instance Id of this task.
 *  @param[in]  Region region, the region Id registered for memory 
 *              usage of this task.
 *  @param[in]  Reason reason.
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 ysActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 ysActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
{
#ifndef YS_MSPD
   U16  idx;
#endif

   TRC2(ysActvInit);

   /* Initialize the CL TskInit structure to zero */
   cmMemset ((U8 *)&ysCb, 0, sizeof(ysCb));

   /* Initialize the CL TskInit with received values */
   ysCb.ysInit.ent = entity;
   ysCb.ysInit.inst = inst;
   ysCb.ysInit.region = region;
   ysCb.ysInit.pool = 3; /* Changing from 0 to 3 for performance */
   ysCb.ysInit.reason = reason;
   ysCb.ysInit.cfgDone = FALSE;
   ysCb.ysInit.acnt = FALSE;
   ysCb.ysInit.usta = FALSE;
   ysCb.ysInit.trc = FALSE;
   ysCb.trcLen = 0; 
#ifdef DEBUGP
#ifdef YS_DEBUG
   ysCb.ysInit.dbgMask = 0xffffffff; 
#endif
#endif /* DEBUGP */
   ysCb.ysInit.procId = SFndProcId();

   /* Initialize CTF sap state */
   ysCb.ctfSap.sapState = LYS_NOT_CFG;

#ifndef NOFILESYS
   if ((ysInitCfg()) != ROK)
   {
      RETVALUE (RFAILED);
   }
#endif

#ifndef YS_MSPD
   for (idx=0; idx < YS_TQ_SIZE; idx++)
   {
      ysCb.tmrTq[idx].first = NULLP;
      ysCb.tmrTq[idx].tail  = NULLP;
   }
   ysCb.tmrTqCp.nxtEnt = 0;
   ysCb.tmrTqCp.tmrLen = YS_TQ_SIZE;

   cmInitTimers(&(ysCb.tmr), 1);
#endif

#ifdef YS_LTE_PAL
   ysPalInit(region);
#endif /* YS_LTE_PAL */



   RETVALUE(ROK);
} /* ysActvInit */


#ifdef YS_LTE_PAL
#ifdef ANSI
PRIVATE S16 ysPalInit
(
Region region
)
#else
PRIVATE S16 ysPalInit(region)
Region region;
#endif
{
   TRC2(ysPalInit);

   /* set the cfgDone to TRUE */
   ysCb.ysInit.cfgDone = TRUE;

   /* Initialize CTF sap */
   /* Since no LM, set state ubnd */
   ysCb.ctfSap.spId     = 0;
   ysCb.ctfSap.suId     = 0;
   ysCb.ctfSap.sapState = LYS_UNBND;
   ysCb.ctfSap.sapPst.selector  = YS_SELECTOR_LC;
   ysCb.ctfSap.sapPst.dstProcId = SFndProcId();
   ysCb.ctfSap.sapPst.srcProcId = SFndProcId();
   ysCb.ctfSap.sapPst.dstEnt    = ENTVE;
   ysCb.ctfSap.sapPst.srcEnt    = ENTTF;
   ysCb.ctfSap.sapPst.region    = region;

   /* Initialize MAC TFU saps */
   /* Since no LM, set state ubnd */
   ysCb.tfuSap.spId     = 0;
   ysCb.tfuSap.suId     = 0;
   ysCb.tfuSap.sapState = LYS_UNBND;
   ysCb.tfuSap.sapPst.selector  = YS_SELECTOR_TC;
   ysCb.tfuSap.sapPst.dstProcId = SFndProcId();
   ysCb.tfuSap.sapPst.srcProcId = SFndProcId();
   ysCb.tfuSap.sapPst.dstEnt    = ENTRG;
   ysCb.tfuSap.sapPst.srcEnt    = ENTTF;
   ysCb.tfuSap.sapPst.region    = region;

   /* Initialize scheduler TFU saps */
   /* Since no LM, set state ubnd */
   ysCb.schTfuSap.spId     = 1;
   ysCb.schTfuSap.suId     = 0;
   ysCb.schTfuSap.sapState = LYS_UNBND;
   ysCb.schTfuSap.sapPst.selector = YS_SELECTOR_TC;
   ysCb.schTfuSap.sapPst.dstProcId = SFndProcId();
   ysCb.schTfuSap.sapPst.srcProcId = SFndProcId();
   ysCb.schTfuSap.sapPst.dstEnt = ENTRG;
   ysCb.schTfuSap.sapPst.srcEnt = ENTTF;
   ysCb.schTfuSap.sapPst.dstInst = 1;
   ysCb.schTfuSap.sapPst.srcInst = 0;
   ysCb.schTfuSap.sapPst.region = region;
   ysCb.schTfuSap.sapPst.pool = ysCb.ysInit.pool;

   /* Initialize Cell control block */
   ysCb.cellCb.cellId = 1;
   ysCb.cellCb.peerPst.dstProcId = YS_DST_PROCID;
   ysCb.cellCb.peerPst.srcProcId = SFndProcId();
   ysCb.cellCb.peerPst.dstEnt    = ENTTF;
   ysCb.cellCb.peerPst.srcEnt    = ENTTF;
   ysCb.cellCb.peerPst.region    = region;
   ysCb.cellCb.peerPst.pool    = ysCb.ysInit.pool; 
   ysCb.cellCb.peerPst.selector  = YS_SELECTOR_LC;

   /* ys003.102: Fix for CID:1622-02-01 DefectId:ccpu00115333.
      adding Cell delete feature for PAL.*/
   ysCb.cellCb.tfuSap = &ysCb.tfuSap;
   ysCb.cellCb.schTfuSap = &ysCb.schTfuSap;
#ifndef SS_CAVIUM
   ysPalInitRcvrTsk();
#endif
   
   RETVALUE(ROK);
} /* ysPalInit */
#endif /* YS_LTE_PAL */


#endif /* YS_ENB_CFG */

/**********************************************************************
  
         End of file:     yw_init.c@@/main/3 - Thu Dec  2 03:31:41 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm        1. eNodeB 1.2 release
/main/2   ys003.102  sgm        1.Fix for CID:1622-02-01 DefectId:ccpu00115333
/main/2   ys004.102  ms         1.configuration file check.                                   
                                2.TTI configured.
                     pkd        3.Kworks warnings fix.
                     pkd        4.Cell Delete functionality CRID:ccpu00117556
/main/2   ys005.102  pbyadgi    1.TIC_ID :ccpu00117545 Fixed warning for gcc 
                                  compilation on CentOS
                                2.Cell Id changes.
                                3.Wireshark changes.
                                4.Introduced new local variable.
                                5.Changes for reading config parameters from
                                  config file ys_cfg.txt for both eNodeB and 
                                  UESIM.
*********************************************************************91*/
