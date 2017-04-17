
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_tst.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:44:16 2013

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
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
/* cm_xta_tst_c_001.main_6 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */
#include "cm_inet.x"        /* common inet */

#include "cm_xta.x"
#include "cm_lte.x" /* Acc Fix */
#include <stdlib.h>

#ifdef RM_ACC
#include "lrm.h"
#include "lrm.x"
#endif /* RM_ACC */

/* cm_xta_tst_c_001.main_6 Removed cm_xta_app.x for Psf-Diameter 1.1 */
PUBLIC CmXtaCb cmXtaCb;
PUBLIC U16 topCount;
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
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst()
#endif
{
#ifdef RM_ACC
   /* For RRM */
   SSTskId  taskId = 0;
#endif
   S16  ret;

   TRC2(tst)

   /*-- This init is required even before the basic init --*/

   /*-- Init the dbgMask value --*/
   cmXtaCb.dbgMask = 2;

   /* cm_xta_tst_c_001.main_5: tst1() is removed. */

   /*-- Check if we want to plugin an alternate TA in this 
        TA engine and run the same based on command line
        input --*/
   if (cmXtaAppTst() == CMXTA_ERR_SKIP)
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): alt TA invoked, exiting from XML TA\n"));

      RETVALUE(CMXTA_ERR_COMPLETE);
   }

   /* Basic Init global control block */
   if (cmXtaPreInit() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): pre init failed, exiting\n"));

      SExit();
      RETVALUE(CMXTA_ERR_INT);
   }

   /* check and process command line options            */
   if (cmXtaParseDebug() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): parse debug failed, exiting\n"));

      SExit();
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Further processing based on the TA instance mode we
        are running in --*/
   /*-- Check if master mode or single binary mode --*/
   if ((cmXtaCb.masterMode == CMXTA_TA_INST_MASTER)  ||
       (cmXtaCb.masterMode == CMXTA_TA_INST_NONE))
   {
      if ((ret = cmXtaMasterTst()) != CMXTA_ERR_NONE)
      {
         if (ret == CMXTA_ERR_INT)
         {
            CMXTA_DBG_INFO((_cmxtap, "tst(): master mode failed, exiting\n"));
         }

         SExit();
      }
   }
   /*-- Slave mode --*/
   else if ((ret = cmXtaSlaveTst()) != CMXTA_ERR_NONE)
   {
      if (ret == CMXTA_ERR_INT)
      {
         CMXTA_DBG_INFO((_cmxtap, "tst(): slave mode failed, exiting\n"));
      }

      SExit();
   }


   RETVALUE(CMXTA_ERR_NONE);
} /* tst */

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
PUBLIC S16 cmXtaPreInit
(
Void
)
#else
PUBLIC S16 cmXtaPreInit(Void)
#endif
{
   U8  cnt;

   TRC2(cmXtaPreInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPreInit(): Pre Initializing the Test Architecture\n"));

   /*-- Set default as the single binary mode, we are using two default proc Ids,
        for multi proc mode, the proc Ids shall be explicitly set through
        the profile file --*/

   /*-- Please do not use SSI -s option to set the SSI proc Id directly. This
        will be overwritten by TA specified one, since the user may specify
        a different value in the profile file and the values there are 
        compiled again --*/

   /*-- Default is single binary mode --*/
   cmXtaCb.masterMode = CMXTA_TA_INST_NONE;
/*  cm_xta_tst_c_001.main_2 :Support for multiple proc */ 
#ifndef SS_MULTIPLE_PROCS
   SSetProcId(CMXTA_PROCID_MASTER);
#endif

   /*-- Set default IPC Port --*/
   cmXtaCb.ipcPort = 18000;
   /*--Added the feature for providing the base port in case of Master Slave
    * communication*/
  
   /*Added the support for the port base*/
   cmXtaCb.portBase = 0;
   cmInetAddr("127.0.0.1", &cmXtaCb.localIpcIpAddr);
   cmInetAddr("127.0.0.1", &cmXtaCb.remoteIpcIpAddr);

   /*-- Update total profile/topology count --*/
   topCount = 0;
   for (cnt = 0; cnt < sizeof(cmXtaTop)/sizeof(cmXtaTop[0]); cnt++)
   {
      /*-- Break at first not valid topology --*/
      if (cmXtaTop[cnt].valid == FALSE)
         break;

      topCount++;
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPreInit(): Test Architecture Pre Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaPreInit */

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
PUBLIC S16 rdConQ
(
Data data
)
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   TRC2(rdConQ)

#ifdef DOS
   /* check if control-c */
   if (data == 0x03)
   {
      SExit();
   }
#else
#ifdef UNIX
   /* check if control-c */
   if (data == 0x03)
   {
      SExit();
   }
#else
#ifdef MVME162_1
   /* check if control-c */
   if (data == 0x03)
   {
      SExit();
   }
#else
#ifdef WIN32
   /* check if control-c */
   if (data == 0x03)
   {
      SExit();
   }
#else
#endif /* WIN32 */
#endif /* MVME162_1 */
#endif /* UNIX */
#endif /* DOS */

   /*-- Further processing based on the TA instance mode we
        are running in --*/
   /*-- Check if master mode or single binary mode --*/
   if ((cmXtaCb.masterMode == CMXTA_TA_INST_MASTER)  ||
       (cmXtaCb.masterMode == CMXTA_TA_INST_NONE))
      cmXtaMasterParseRdConQ(data);
   else
      cmXtaSlaveParseRdConQ(data);

   RETVALUE(CMXTA_ERR_NONE);
}/* rdConQ */

/********************************************************************30**

         End of file:     cm_xta_tst.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:44:16 2013

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
/main/2      ----     up  1. Main release
/main/3      ---      cm_xta_tst_c_001.main_2  sk  1. Support for multiple proc
/main/4      ---      aj  1. Support for the port Base  
/main/5      ---  cm_xta_tst_c_001.main_4    ve  1. SW_MSG_ACC changes added  
/main/6      ---  cm_xta_tst_c_001.main_5    rss  1. tst1() is removed.
/main/7      ---- cm_xta_tst_c_001.main_6    jj 1. Updated for Psf-Diameter 1.1
                                             release Removed cm_xta_app.[hx]
*********************************************************************91*/
