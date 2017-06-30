
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_reg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:26 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include <stdlib.h>
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */
#include "cm_inet.h"        /* common inet */

#include "cm_xta.h"
/* cm_xta_reg_c_001.main_4 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */
#include "cm_inet.x"        /* common inet */

#include "cm_xta.x"

/* cm_xta_reg_c_001.main_4 Removed cm_xta_app.x for Psf-Diameter 1.1 */
PRIVATE Bool parse;

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaRegister
(
Void
)
#else
PUBLIC S16 cmXtaRegister()
#endif
{
   U16  cnt;
   U8  topId;

   CmXtaTopology *top;
   CmXtaEntReg *entReg;

   TRC2(cmXtaRegister)

   /*-- Get the topology id --*/
   topId = cmXtaCb.curTopId;

   /* This should not happen here, put the same check in 
      command line parse, and in case of all topology mode,
      the calling function shall again verify the topology
      is valid before calling this function */
   top = &cmXtaTop[topId];

   if (top->valid == FALSE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaRegister(): Invalid top Id (%d)\n", topId));
      RETVALUE(RFAILED);
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaRegister(): Registeration initiated\n"));

   /* Create System Tasks */
   for (cnt = 0; cnt < top->sTasks; cnt++)
   {
      if (SCreateSTsk(PRIOR0, &cmXtaCb.tskId[cnt]) != CMXTA_ERR_NONE)
      {
         CMXTA_DBG_FATAL((_cmxtap, "cmXtaRegister(): sTask creation failed, initiate cleanup\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      CMXTA_DBG_INFO((_cmxtap, "cmXtaRegister() : Created STask [%d]\n", cmXtaCb.tskId[cnt]));
   }

   /*-- Set the proc ids for this intance --*/
#ifdef SS_MULTIPLE_PROCS            
   if (SAddProcIdLst(top->procCnt, top->procId) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaRegister(): sTask creation failed, initiate cleanup\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
#else
   /*-- We use only the first procId in this case --*/
   if (top->procCnt != 0)
/* cm_xta_reg_c_001.main_1 : Support for multiple proc */
#ifndef SS_MULTIPLE_PROCS
      SSetProcId(top->procId[0]);
#endif
      ; /* to terminate if */
#endif

   for (cnt = 0; cnt < SS_MAX_TTSKS; cnt++)
   {
      entReg = &top->entReg[cnt];

      /*-- Check if the valid flag is set, else this is
           the last element --*/
      if (entReg->valid == FALSE)
         break;

      if (SRegTTsk(
#ifdef SS_MULTIPLE_PROCS            
               entReg->proc,
#endif
               entReg->ent, entReg->inst,
               entReg->tskType, entReg->tskPrior,
               entReg->initTsk, entReg->actvTsk) != CMXTA_ERR_NONE)
      {
         CMXTA_DBG_FATAL((_cmxtap, "cmXtaRegister(): SRegTTsk failed, initiate cleanup\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      CMXTA_DBG_INFO((_cmxtap, "cmXtaRegister() : Registered Task [%d.%d.%hd.%hd]\n",
                     entReg->sTskId, entReg->proc, entReg->ent, entReg->inst));
   }

   for (cnt = 0; cnt < SS_MAX_TTSKS; cnt++)
   {
      entReg = &top->entReg[cnt];

      /*-- Check if the valid flag is set, else this is
           the last element --*/
      if (entReg->valid == FALSE)
         break;

      if (SAttachTTsk(
#ifdef SS_MULTIPLE_PROCS            
               entReg->proc,
#endif
               entReg->ent, entReg->inst, cmXtaCb.tskId[entReg->sTskId - 1]) != CMXTA_ERR_NONE)
      {
         CMXTA_DBG_FATAL((_cmxtap, "cmXtaRegister(): SRegTTsk failed, initiate cleanup\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      CMXTA_DBG_INFO((_cmxtap, "cmXtaRegister() : Attached Task [%d.%d.%hd.%hd]\n",
                     entReg->sTskId, entReg->proc, entReg->ent, entReg->inst));
   }

#ifdef CMXTA_MASTER
   /*-- Init Tmr module if running in master mode --*/
   if ((cmXtaCb.masterMode == CMXTA_TA_INST_NONE)     ||
       (cmXtaCb.masterMode == CMXTA_TA_INST_MASTER))
   {
      if (cmXtaTmrInitQ() != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "cmXtaRegister(): tmr init failed\n"));

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_INT);
      }

      CMXTA_DBG_INFO((_cmxtap, "cmXtaRegister(): Timer inititated\n"));
   }
#endif /*-- CMXTA_MASTER --*/
   CMXTA_DBG_INFO((_cmxtap, "cmXtaRegister(): Registeration complete\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaRegister */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaDeRegister
(
Bool finalShutdown
)
#else
PUBLIC S16 cmXtaDeRegister(finalShutdown)
Bool finalShutdown;
#endif
{
   U16  cnt;
   U8  topId;

   CmXtaTopology *top;
   CmXtaEntReg *entReg;

   TRC2(cmXtaDeRegister)

   /*-- Get the topology id --*/
   topId = cmXtaCb.curTopId;

   /* This should not happen here, put the same check in 
      command line parse, and in case of all topology mode,
      the calling function shall again verify the topology
      is valid before calling this function */
   top = &cmXtaTop[topId];

   if (top->valid == FALSE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaDeRegister(): Invalid top Id (%d)\n", topId));
      RETVALUE(RFAILED);
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaDeRegister(): De-Registeration initiated\n"));

#ifdef CMXTA_MASTER
   /*-- Shutdown the timer module if running in master mode --*/
   if ((cmXtaCb.masterMode == CMXTA_TA_INST_NONE)     ||
       (cmXtaCb.masterMode == CMXTA_TA_INST_MASTER))
      (Void)cmXtaTmrDeInitQ();
#endif /*-- CMXTA_MASTER  --*/

   /*-- Detach the tasks --*/
   for (cnt = 0; cnt < SS_MAX_TTSKS; cnt++)
   {
      entReg = &top->entReg[cnt];

      /*-- Check if the valid flag is set, else this is
           the last element --*/
      if (entReg->valid == FALSE)
         break;

      CMXTA_DBG_INFO((_cmxtap, "cmXtaDeRegister() : Detach Task [%d.%d.%hd.%hd]\n",
                     entReg->sTskId, entReg->proc, entReg->ent, entReg->inst));
      SDetachTTsk(
#ifdef SS_MULTIPLE_PROCS            
               entReg->proc,
#endif
               entReg->ent, entReg->inst);
   }

   /* De-register tasks */
   for (cnt = 0; cnt < SS_MAX_TTSKS; cnt++)
   {
      entReg = &top->entReg[cnt];

      /*-- Check if the valid flag is set, else this is
           the last element --*/
      if (entReg->valid == FALSE)
         break;

      CMXTA_DBG_INFO((_cmxtap, "cmXtaDeRegister() : DeReg Task [%d.%d.%hd.%hd]\n",
                     entReg->sTskId, entReg->proc, entReg->ent, entReg->inst));
      SDeregTTsk(
#ifdef SS_MULTIPLE_PROCS            
               entReg->proc,
#endif
               entReg->ent, entReg->inst);
   }

   /*-- In case of single threaded SSI, even in case of 
        multiple System Task creation requests, only one
        system task is created still. Do not destroy the
        task if we are running in multiple topology mode --*/
#ifdef SS_SINGLE_THREADED
   /* Destroy System Tasks only if MT SSI or final shutdown */
   if (finalShutdown == TRUE)
   {
      for (cnt = 0; cnt < top->sTasks; cnt++)
         SDestroySTsk(cmXtaCb.tskId[cnt]);
   }
#else
   /*-- Always destroy in case of MT SSI --*/
   for (cnt = 0; cnt < top->sTasks; cnt++)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaDeRegister() : Destroy STask [%d]\n",
                     cmXtaCb.tskId[cnt]));

      SDestroySTsk(cmXtaCb.tskId[cnt]);
   }
#endif

#ifdef SS_MULTIPLE_PROCS            
   SRemProcIdLst(top->procCnt, top->procId);
#endif

   CMXTA_DBG_INFO((_cmxtap, "cmXtaDeRegister(): De-Registeration complete\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaDeRegister */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaParseDebug
(
Void
)
#else
PUBLIC S16 cmXtaParseDebug()
#endif
{
   S16          ret;                            /* return value         --*/
   Bool         loop;

   TRC2(cmXtaParseDebug)

   parse = FALSE;
   loop =  TRUE;

   /* cm_xta_reg_c_001.main_3 - LTE RLC 1.1 */
#ifdef SS_VW
            cmXtaCb.dbgMask = 9;
            cmXtaCb.ipcPort = 9001;
            cmInetAddr("192.168.200.3", &cmXtaCb.localIpcIpAddr);
            cmInetAddr("172.25.0.28", &cmXtaCb.remoteIpcIpAddr);
            cmXtaCb.masterMode = CMXTA_TA_INST_SLAVE;
#ifndef SS_MULTIPLE_PROCS
            SSetProcId(CMXTA_PROCID_SLAVE);
#endif
#else

   /*-- To reuse the same command line parameters for SSI, TA, and App TA, the following
        logic is used. -x Represents the boundanry between different module specific 
        parameters, we still can't use the options used by SSI, because it does not
        recognize these boundaries --*/

   /*-- SSI does not support this logic, hence skip till first -x --*/

   /*-- To avoid making -x mandatory, if any non matching option is received
        while skipping, it is assume to be same as -x. For resue, use -x
        explicitly --*/
   loop = TRUE;
   while ((loop == TRUE) &&
          ((ret = SGetOpt(msArgc, msArgv, "d:f:o:s:A:B:I:P:SMx")) != EOF))
   {
      switch(ret)
      {

         case 'o':
         case 'f':
         case 's':
            break;

         case 'd':
            /*-- Set debug level --*/
            cmXtaCb.dbgMask = atoi(msOptArg);
            break;

         case 'x':
            loop = FALSE;
            break;

         case 'I':
            /*-- Set IPC Port --*/
            cmXtaCb.ipcPort = atoi(msOptArg);

            break;

         case 'A':
            /*-- Set IPC Address --*/
            cmInetAddr(msOptArg, &cmXtaCb.localIpcIpAddr);
            break;

         case 'B':
            /*-- Set Remote IPC Address --*/
            cmInetAddr(msOptArg, &cmXtaCb.remoteIpcIpAddr);
            break;

         case 'P':
            cmXtaCb.portBase = atoi(msOptArg);
            break;

         case 'S':
            /*-- Set slave mode --*/
            cmXtaCb.masterMode = CMXTA_TA_INST_SLAVE;

            /*-- Set default procId --*/

/* cm_xta_reg_c_001.main_1 : Support for multiple proc */
#ifndef SS_MULTIPLE_PROCS
            SSetProcId(CMXTA_PROCID_SLAVE);
#endif
            break;

         case 'M':
            /*-- Set master mode, default anyway --*/
            cmXtaCb.masterMode = CMXTA_TA_INST_MASTER;

            /*-- Set default procId --*/
#ifndef SS_MULTIPLE_PROCS
            SSetProcId(CMXTA_PROCID_MASTER);
#endif
            break;


         case '?':
         default:
            /*-- No match, assume same as -x and move on --*/
            /*-- Reset parsed instance --*/
            msOptInd -= 1;
            loop = FALSE;
            break;
      }
   }
#endif

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaParseDebug --*/

/********************************************************************30**

         End of file:     cm_xta_reg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:26 2015

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
/main/1      ----     up  1. Main release
/main/2    cm_xta_reg_c_001.main_1  sk  1. Support for multiple proc
/main/3      ----     aj  1. Added the suppport for the port Base 
/main/3    cm_xta_reg_c_001.main_3  nm  1. Update for Release of LTE RLC 1.1
/main/5      ---- cm_xta_reg_c_001.main_4 nh 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
