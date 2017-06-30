
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_master.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:24 2015

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
/* cm_xta_master_c_001.main_8 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
#include <stdlib.h>
/* cm_xta_master_c_001.main_8 Removed cm_xta_app.x for Psf-Diameter 1.1 */
/* cm_xta_master_c_001.main_7: Removed the redundent declaration of function */

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
PUBLIC S16 cmXtaMasterTst
(
Void
)
#else
PUBLIC S16 cmXtaMasterTst()
#endif
{
   TRC2(cmXtaMasterTst)

   /*-- Basic tst function for TA running as master --*/

   /* Basic Init global control block */
   if (cmXtaMasterPreInit() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): pre init failed, exiting\n"));

      RETVALUE(CMXTA_ERR_INT);
   }

   /* check and process command line options            */
   if (cmXtaMasterParseDebug() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): parse debug failed, exiting\n"));

      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Check we have to capture XML logs here --*/
   cmXtaLogXml(NULLP, CMXTA_MEM_LOG_INIT);

   /*-- Check we have to show the SSI memory usage here --*/
   cmXtaLogXml(NULLP, CMXTA_MEM_TA_INIT);

   /* Basic Init global control block */
   if (cmXtaMasterInit() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterTst(): master init failed, exiting\n"));

      /*-- Check we have to show the SSI memory usage here --*/
      cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

      /*-- Check we have to capture XML logs here --*/
      cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

      RETVALUE(RFAILED);
   }

   /* check and process command line options            */
   if (cmXtaMasterParseCmdLine() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterTst(): master parse cmdline failed, exiting\n"));

      cmXtaMasterDeInit();

      /*-- Check we have to show the SSI memory usage here --*/
      cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

      /*-- Check we have to capture XML logs here --*/
      cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

      SExit();
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterTst(): Initiating testing\n"));

   /* If we reach here, we have atleast one TC to run   */
   /* Initiate Sample App High Level STM                */

   /* Setting state for STM outside the STM, see it as  
      creation of STM rather */
   cmXtaCb.state = CMXTA_START_INIT;

   /*-- Call STM entry function --*/
   cmXtaTAReq(CMXTA_ERR_NONE);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaMasterTst */

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
PUBLIC S16 cmXtaMasterPreInit
(
Void
)
#else
PUBLIC S16 cmXtaMasterPreInit(Void)
#endif
{
   TRC2(cmXtaMasterPreInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterPreInit(): Pre Initializing the Test Architecture\n"));

   CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterPreInit(): Test Architecture Pre Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaMasterPreInit */

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
PUBLIC S16 cmXtaMasterInit
(
Void
)
#else
PUBLIC S16 cmXtaMasterInit(Void)
#endif
{
   CmXtaDirectives directives;

   S16      ret;
   U32      dbgMask;
   S16      tmpXmlIndent;
   Bool     tmpMasterMode;
   U32      tmpIpcPort;
   U32      tmpLocalIpcIpAddr;
   U32      tmpRemoteIpcIpAddr;

   TRC2(cmXtaMasterInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterInit(): Initializing the Test Architecture\n"));

   /*-- dbgMask is already set in cmXtaMasterParseDebug, so save it before init --*/
   dbgMask = cmXtaCb.dbgMask;

   directives = cmXtaCb.directives;
   tmpXmlIndent = cmXtaCb.xmlIndent;
   tmpMasterMode = cmXtaCb.masterMode;
   tmpIpcPort = cmXtaCb.ipcPort;
   tmpLocalIpcIpAddr = cmXtaCb.localIpcIpAddr;
   tmpRemoteIpcIpAddr = cmXtaCb.remoteIpcIpAddr;

   CMXTA_ZERO(&cmXtaCb, sizeof(CmXtaCb));

   /*-- Reset the dbgMask value --*/
   cmXtaCb.dbgMask = dbgMask;

   cmXtaCb.directives = directives;
   cmXtaCb.ipcPort = tmpIpcPort;
   cmXtaCb.localIpcIpAddr = tmpLocalIpcIpAddr;
   cmXtaCb.remoteIpcIpAddr = tmpRemoteIpcIpAddr;
   cmXtaCb.xmlIndent = tmpXmlIndent;
   cmXtaCb.masterMode = tmpMasterMode;

   /* Initialize the entity for TA, required by debug macros */
   cmXtaCb.init.ent   = ENTTST;
   cmXtaCb.init.inst  = CMXTA_INST_ID;
   cmXtaCb.init.ent   = ENTTST;
   cmXtaCb.init.inst  = CMXTA_INST_ID;
/* cm_xta_master_c_001.main_1 : Support for multiple proc */
#ifndef SS_MULTIPLE_PROCS
   cmXtaCb.init.procId  = SFndProcId();
#endif

   /* Initialize the region/pool */
   cmXtaCb.init.region   = DFLT_REGION;
   cmXtaCb.init.pool     = DFLT_POOL;

   /*-- Set default topology --*/
   cmXtaCb.curTopId = CMXTA_DFLT_TOP;

   cmXtaCb.maxLoopCnt = 10;

   /*-- Init Timer Information --*/
   cmXtaCb.timerPeriod = 1;
   cmXtaCb.timerUnit   = SS_100MS;

   /*-- Default Test Delay timer --*/
   cmXtaCb.delayTstVal = CMXTA_TMR_DELAY_TST_VAL;
   cmXtaCb.delayTstShutDownVal = CMXTA_TMR_DELAY_SHUTDOWN_VAL;

   /*-- Set default mode --*/
   cmXtaCb.mode = CMXTA_TA_MODE_DFLT;

   /*-- Init the flags associated with the TA --*/
   if ((ret = cmXtaFlInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- Init the global hash list cp for TCs, compound
        commands and simple commands --*/
   if ((ret = cmXtaXmlInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- Read XML TCs and compound commands here --*/
   if ((ret = cmXtaXmlLoadFiles(parse)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- Int module init function --*/
   if ((ret = cmXtaIntInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- SM module init function --*/
   if ((ret = cmXtaTxnInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if ((ret = cmXtaAppMasterInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterInit(): Test Architecture Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaMasterInit */

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
PUBLIC S16 cmXtaMasterDeInit
(
Void
)
#else
PUBLIC S16 cmXtaMasterDeInit()
#endif
{
   TRC2(cmXtaMasterDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterDeInit(): Shutting down the Test Architecture\n"));

   /*-- Opposite of the steps done in cmXtaMasterInit --*/

   /*-- Put DeInit functions for rest of the
        modules here, this will happen only once --*/

   (Void)cmXtaAppMasterDeInit();

   /*-- SM module deInit function --*/
   (Void)cmXtaTxnDeInit();

   /*-- Int module deinit function --*/
   (Void)cmXtaIntDeInit();

   /*-- DeInit the global hash list cp for TCs, compound
        commands and simple commands --*/
   (Void)cmXtaXmlDeInit();

   CMXTA_DBG_INFO((_cmxtap, "cmXtaMasterDeInit(): Test Architecture Shutdown Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaMasterDeInit */

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
PUBLIC  S16 cmXtaMasterInitPst
(
Void
)
#else
PUBLIC  S16 cmXtaMasterInitPst(Void)
#endif
{
   U16 j;
   U16  cnt;
   U8  topId;

   CmXtaTopology *top;

   TRC2(cmXtaMasterInitPst)

   /*-- Get the topology id --*/
   topId = cmXtaCb.curTopId;

   top = &cmXtaTop[topId];

   /* This should not happen here, put the same check in 
      command line parse, and in case of all topology mode,
      the calling function shall again verify the topology
      is valid before calling this function */
   if (top->valid == FALSE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaMasterInitPst(): Invalid top Id (%d)\n", topId));
      RETVALUE(RFAILED);
   }

   /* Init common values */
   for (j = 0; j < CMXTA_MAX_INTERFACE; j++)
   {
#ifndef SS_MULTIPLE_PROCS
      cmXtaCb.pst[j].dstProcId = SFndProcId();
      cmXtaCb.pst[j].srcProcId = SFndProcId();
#endif

      cmXtaCb.pst[j].prior     = PRIOR0;
      cmXtaCb.pst[j].route     = RTESPEC;

      cmXtaCb.pst[j].region    = DFLT_REGION;
      cmXtaCb.pst[j].pool      = DFLT_POOL;

      /* Default Loose Coupled */
      cmXtaCb.pst[j].selector  = 0;

      cmXtaCb.pst[j].intfVer   = 0;       /* interface version */
   }

   /*-- Build Pst structure --*/
   for (cnt = 0; cnt < CMXTA_MAX_INTERFACE/2; cnt++)
   {
      /*-- Check if the valid flag is set, else this is
           the last element --*/
      if (top->sel[cnt].valid == FALSE)
         break;

      /* Fill entity and selector information for Ent 1 -> Ent 2 */
      cmXtaCb.pst[cnt * 2].srcEnt    = top->sel[cnt].srcEnt;
      cmXtaCb.pst[cnt * 2].srcInst   = top->sel[cnt].srcInst;
      cmXtaCb.pst[cnt * 2].srcProcId = top->sel[cnt].srcProc;

      cmXtaCb.pst[cnt * 2].dstEnt    = top->sel[cnt].dstEnt;
      cmXtaCb.pst[cnt * 2].dstInst   = top->sel[cnt].dstInst;
      cmXtaCb.pst[cnt * 2].dstProcId = top->sel[cnt].dstProc;

      cmXtaCb.pst[cnt * 2].selector  = top->sel[cnt].toSel;
#ifdef SS_MULTIPLE_PROCS
#endif


      /* Fill entity and selector information for Ent 2 -> Ent 1 */
      cmXtaCb.pst[cnt * 2 + 1].srcEnt    = top->sel[cnt].dstEnt;
      cmXtaCb.pst[cnt * 2 + 1].srcInst   = top->sel[cnt].dstInst;
      cmXtaCb.pst[cnt * 2 + 1].srcProcId = top->sel[cnt].dstProc;

      cmXtaCb.pst[cnt * 2 + 1].dstEnt    = top->sel[cnt].srcEnt;
      cmXtaCb.pst[cnt * 2 + 1].dstInst   = top->sel[cnt].srcInst;
      cmXtaCb.pst[cnt * 2 + 1].dstProcId = top->sel[cnt].srcProc;

      cmXtaCb.pst[cnt * 2 + 1].selector  = top->sel[cnt].fromSel;
#ifdef SS_MULTIPLE_PROCS
#endif
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaMasterInitPst */

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
PUBLIC Void cmXtaMasterUsageDebug
(
Void
)
#else
PUBLIC Void cmXtaMasterUsageDebug()
#endif
{
   Txt   pBuf[100];  /* output string buffer */

   TRC2(cmXtaMasterUsageDebug);

   sprintf(pBuf, "Global Options:\n===============\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "Common:\n-------\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-o filename  ]   - Write output to 'filename'\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-f filename  ]   - Write memory cfg from 'filename'\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-A address   ]   - Set local IPC IP address\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-B address   ]   - Set remote IPC IP address\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-I port      ]   - Set IPC Port\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-S           ]   - Run in Slave mode\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-M           ]   - Run in Master mode\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-d 0-9       ]   - Turn ON debug flags\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-h           ]   - Print this usage message\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-x           ]   - End of option section\n");
   SPrint(pBuf);

   sprintf(pBuf, "\n");
   SPrint(pBuf);

   sprintf(pBuf, "Master:\n-------\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-P           ]   - Parse XML test cases\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-K           ]   - Show test results in XML\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-L           ]   - Turn ON Memory Leak Validation\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-R           ]   - Display Memory Leak Usage\n");
   SPrint(pBuf);

   sprintf(pBuf, "\n");
   SPrint(pBuf);

   RETVOID;
} /* cmXtaMasterUsageDebug */

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
PUBLIC Void cmXtaMasterUsage
(
Void
)
#else
PUBLIC Void cmXtaMasterUsage()
#endif
{
   /* cm_xta_master_c_001.main_5 :Increased the buffer size */
   Txt   pBuf[130];  /* output string buffer */
   U32   ind;        /* test group index     --*/
   U32   tstCnt;     /* test coutn           --*/
   U8  cnt;

   TRC2(cmXtaMasterUsage);

   sprintf(pBuf, "\nUSAGE: %s [options]\n\n", msArgv[0]);
   SPrint(pBuf);

   /*-- Master Global Options --*/
   cmXtaMasterUsageDebug();

   /*-- Slave Global Options --*/
   cmXtaSlaveUsage();

   /*-- TA Options --*/
   sprintf(pBuf, "TA Options:\n===========\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-a           ]   - Run all test groups\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-b timerUnit ]   - Change SSI Timer Unit (default SS_100MS)\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    Allowed values :\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - SS_100MS   : 10\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - SS_10MS    : 100\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - SS_1MS     : 1000\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-c timerPeriod]  - Change SSI Timer Period (default 1)\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-e testNumber]   - End test id in test group\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-G 1-%-2d      ]   - Run specified range of test groups\n", cmXtaCb.tstGrpCnt);
   SPrint(pBuf);
   sprintf(pBuf, "\t                    -G <start> -G <end>\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-g 1-%-2d      ]   - Run specified test group\n", cmXtaCb.tstGrpCnt);
   SPrint(pBuf);
   sprintf(pBuf, "\t[-i           ]   - Ignore tapa.delay commands\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-j testNumber]   - Start test id in test group\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-m           ]   - Set TA mode\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    Allowed values :\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - [ 1] : Default\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - [ 2] : Skip Shutdown\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - [ 4] : Loop\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - [ 8] : All topologies\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - [16] : Skip Test Group Shutdown\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - [32] : External\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t                    - [64] : Load\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-n count     ]   - Set TA loop value\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-p profile   ]   - Set TA profile\n");
   SPrint(pBuf);
   for (cnt = 0; cnt < sizeof(cmXtaTop)/sizeof(cmXtaTop[0]); cnt++)
   {
      /*-- Break at first not valid topology --*/
      if (cmXtaTop[cnt].valid == FALSE)
         break;

      sprintf(pBuf, "\t                  - [%2d]: %s\n", cnt, cmXtaTop[cnt].descr);
      SPrint(pBuf);
   }

   sprintf(pBuf, "\t[-q           ]   - Set non verbose mode\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-T delay     ]   - Delay before TC shutdown\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-U delay     ]   - Delay after TC shutdown\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-t testNumber]   - Test id in test group\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-u testNumber]   - Test id not to be used in test group\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-z           ]   - Dump intenal/leaf command info\n\n");
   SPrint(pBuf);

   /*-- Application Specific Options for Master mode --*/
   cmXtaAppMasterUsage();

   /*-- Application Specific Options for Slave mode --*/
   cmXtaAppSlaveUsage();

   sprintf(pBuf, "\nTest Groups:\n============\n\n");
   SPrint(pBuf);

   tstCnt = 0;
   for (ind = 0; ind < cmXtaCb.tstGrpCnt; ++ind)
   {
      /* cm_xta_master_c_001.main_7: Fixed the 64bit compilation warning */
#ifdef ALIGN_64BIT
      sprintf(pBuf, "\t%2d: %-65s [%4d]\n", ind+1, cmXtaCb.tstGrp[ind].name,
              cmXtaCb.tstGrp[ind].numTests);
#else
      sprintf(pBuf, "\t%2ld: %-65s [%4d]\n", ind+1, cmXtaCb.tstGrp[ind].name,
              cmXtaCb.tstGrp[ind].numTests);
#endif /* ALIGN_64BIT */
      SPrint(pBuf);
      tstCnt += cmXtaCb.tstGrp[ind].numTests;
   }

   sprintf(pBuf, "\n");
   SPrint(pBuf);
   /* cm_xta_master_c_001.main_7: Fixed the 64bit compilation warning */
#ifdef ALIGN_64BIT
   sprintf(pBuf, "\t%-68s: [%4d]\n", "Total Tests", tstCnt);
#else
   sprintf(pBuf, "\t%-68s: [%4ld]\n", "Total Tests", tstCnt);
#endif /* ALIGN_64BIT */
   SPrint(pBuf);
   sprintf(pBuf, "\n");
   SPrint(pBuf);

   RETVOID;
} /* cmXtaMasterUsage */

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
PUBLIC S16 cmXtaMasterParseCmdLine
(
Void
)
#else
PUBLIC S16 cmXtaMasterParseCmdLine()
#endif
{
   /* cm_xta_master_c_001.main_5 :Added initialization */
   U16          startGroupNum=0;                      /* test group number    */
   U16          endGroupNum=0;                      /* test group number    */
   U16          tGroupNum=0;                      /* test group number    */
   S16          descNum;                      /* test group number    */
   U16          testNum=0;                        /* test number          */
   S16          ret;                            /* return value         */
   U16          i;                              /* index                */
   U16          j;                              /* index                */
   Bool         groupSelected;                  /* was a group selected */
   Bool         groupRangeSelected;                  /* was a group selected */
   Bool         oneGroup;                       /* was a group selected */
   Bool         tcRangeSelected;                /* was a group selected */
   Bool         tcSelected;                     /* was a group selected */
   Bool         loop;

   TRC2(cmXtaMasterParseCmdLine)

   tGroupNum = cmXtaCb.tstGrpCnt + 1;

   descNum = -1;
   /* parse the command line parameters                         */
   groupSelected = FALSE;
   oneGroup = FALSE;
   tcRangeSelected = FALSE;
   groupRangeSelected = FALSE;
   tcSelected = FALSE;

   loop =  TRUE;

   while ((loop == TRUE) &&
          ((ret = SGetOpt(msArgc, msArgv, "G:U:T:ab:c:d:e:f:g:hij:m:n:o:p:qs:t:u:xz")) != EOF))
   {
      switch(ret)
      {
         /*-- SSI specific --*/
         case 'f':
         case 'o':
            /* we ignore the output specifier and specifiers used by TA command
               line parser --*/
            break;

         case 'a':
            /* Run all test groups */
            groupSelected = TRUE;
            oneGroup = TRUE;
            for (i = 0; i < cmXtaCb.tstGrpCnt; i++)
            {
               if (cmXtaCb.tstGrp[i].state == CMXTA_IDLE)
               {
                  cmXtaCb.tstGrp[i].state = CMXTA_RUN;

                  cmXtaCb.tstGrp[i].startTest = -1;
                  cmXtaCb.tstGrp[i].endTest = cmXtaCb.tstGrp[i].numTests;

                  for (j = 0; j < cmXtaCb.tstGrp[i].numTests; j++)
                     if (cmXtaCb.tstGrp[i].tstList[j].tcSet == TRUE)
                        cmXtaCb.tstGrp[i].tstList[j].state = CMXTA_RUN;
               }
            }

            break;

         case 'b':
            /*-- Set timerUnit --*/
            cmXtaCb.timerUnit = atoi(msOptArg);

            if ((cmXtaCb.timerUnit != SS_100MS) &&
                (cmXtaCb.timerUnit != SS_10MS) &&
                (cmXtaCb.timerUnit != SS_1MS))
            {
               SPrint("ERROR: Invalid timerUnit value");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            break;

         case 'c':
            /*-- Set timerPeriod --*/
            cmXtaCb.timerPeriod = atoi(msOptArg);
            break;

         case 'd':
            /*-- Set debug level --*/
            cmXtaCb.dbgMask = atoi(msOptArg);
            break;

         case 'e':
            /* test number has been specified, end here */
            if (groupSelected == FALSE)
            {
               SPrint("ERROR: Enter -g option before -e");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            else
            {
               testNum = atoi(msOptArg);
            }
            /* cm_xta_master_c_001.main_5 :Added validation for tGroupNum and testNum*/
            if ((tGroupNum <= cmXtaCb.tstGrpCnt) && (tGroupNum > 0))
            {
               if ((testNum > cmXtaCb.tstGrp[tGroupNum-1].numTests) || (testNum <= 0))
               {
                  SPrint("ERROR: Invalid test number");
                  SPrint("\n\n");
                  cmXtaMasterUsage();
                  RETVALUE(RFAILED);
               }
            }
            else
            {
               SPrint("ERROR: Invalid test group number");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            /* Set the end range, the start range shall have been set with 
               the test group option (to default) and may have been overridden
               with the start range option */
            cmXtaCb.tstGrp[tGroupNum-1].endTest = testNum;

            /*-- Reset this test group options --*/
            groupSelected = FALSE;
            tcRangeSelected = FALSE;
            break;

         case 'G':

            /*-- Check if we are here for the first time --*/
            if (groupRangeSelected == FALSE)
            {
               startGroupNum = atoi(msOptArg);
               groupRangeSelected = TRUE;
               /* cm_xta_master_c_001.main_5 :Added validation for startGroupNum */
               if ((startGroupNum > cmXtaCb.tstGrpCnt) || (startGroupNum <= 0))
               {  
                  SPrint("ERROR: Invalid start group");
                  SPrint("\n\n");
                  cmXtaMasterUsage();
                  RETVALUE(RFAILED);
               }
            }
            else
            {
               endGroupNum = atoi(msOptArg);
               groupRangeSelected = FALSE;
               /* cm_xta_master_c_001.main_5 :Added validation for startGroupNum and endGroupNum*/
               if ((endGroupNum > cmXtaCb.tstGrpCnt) || (endGroupNum <= 0) ||
                   (startGroupNum > cmXtaCb.tstGrpCnt) || (startGroupNum <= 0))
               {
                  SPrint("ERROR: Invalid group");
                  SPrint("\n\n");
                  cmXtaMasterUsage();
                  RETVALUE(RFAILED);
               }

               if (startGroupNum > endGroupNum)
               {
                  SPrint("ERROR: Invalid group range");
                  SPrint("\n\n");
                  cmXtaMasterUsage();
                  RETVALUE(RFAILED);
               }

               for (j = startGroupNum; j < endGroupNum + 1; j++)
               {
                  if ((j <= cmXtaCb.tstGrpCnt) && (j > 0))
                  {
                     if (cmXtaCb.tstGrp[j-1].state == CMXTA_IDLE)
                     {
                        /*-- If atleast one group found, mark groupSelected as TRUE, 
                          this may get reset at the end of this TG --*/
                        cmXtaCb.tstGrp[j-1].state = CMXTA_RUN;
                        oneGroup = TRUE;

                        /*-- Mark all TCs to be run --*/
                        cmXtaCb.tstGrp[j-1].startTest = -1;
                        cmXtaCb.tstGrp[j-1].endTest = cmXtaCb.tstGrp[j-1].numTests;

                        for (i = 0; i < cmXtaCb.tstGrp[j-1].numTests; i++)
                           if (cmXtaCb.tstGrp[j-1].tstList[i].tcSet == TRUE)
                              cmXtaCb.tstGrp[j-1].tstList[i].state = CMXTA_RUN;
                     }
                  }
               }
            }
            break;

         case 'g':
            /* Test group to be tested           */
            /*-- We allow multiple test groups to be selected at
                 the same time by specifying multiple g options.

                 For eg -g <g1> -g <g2> -g <3> 
             --*/
            tGroupNum = atoi(msOptArg);
            if ((tGroupNum <= cmXtaCb.tstGrpCnt) && (tGroupNum > 0))
            {
               if (cmXtaCb.tstGrp[tGroupNum-1].state == CMXTA_IDLE)
               {
                  /*-- If atleast one group found, mark groupSelected as TRUE, 
                       this may get reset at the end of this TG --*/
                  cmXtaCb.tstGrp[tGroupNum-1].state = CMXTA_RUN;
                  groupSelected = TRUE;
                  oneGroup = TRUE;

                  /*-- Set start and end range of TC within the group, this 
                       would change if start and end range options are given --*/
                  cmXtaCb.tstGrp[tGroupNum-1].startTest = -1;
                  cmXtaCb.tstGrp[tGroupNum-1].endTest = cmXtaCb.tstGrp[tGroupNum-1].numTests;

                  for (i = 0; i < cmXtaCb.tstGrp[tGroupNum-1].numTests; i++)
                     if (cmXtaCb.tstGrp[tGroupNum-1].tstList[i].tcSet == TRUE)
                        cmXtaCb.tstGrp[tGroupNum-1].tstList[i].state = CMXTA_RUN;
               }
            }
            else
            {
               SPrint("ERROR: Invalid group number");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            break;

         case 'h':
            /* help and unknown options display help message    */
            cmXtaMasterUsage();
            RETVALUE(RFAILED);
            break;

         case 'i':
            /* help and unknown options display help message    */
            cmXtaCb.directives.ignoreDelay = TRUE;
            break;

         case 'j':
            /* test number has been specified, start from there */
            if (groupSelected == FALSE)
            {
               SPrint("ERROR: Enter -g option before -f");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            else if (tcRangeSelected == TRUE)
            {
               SPrint("ERROR: Multiple TC range not allowed");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            else
            {
               testNum = atoi(msOptArg);
            }

            /* cm_xta_master_c_001.main_5 :Added validation for tGroupNum */
            if ((tGroupNum <= cmXtaCb.tstGrpCnt) && (tGroupNum > 0))
            {
               if ((testNum > cmXtaCb.tstGrp[tGroupNum-1].numTests) || (testNum <= 0))
               {
                  SPrint("ERROR: Invalid test number");
                  SPrint("\n\n");
                  cmXtaMasterUsage();
                  RETVALUE(RFAILED);
               }
            }
            /*-- Set start and end of the TC range, set end as default, this may
                 be overridden if end range option is given --*/
            cmXtaCb.tstGrp[tGroupNum-1].startTest = testNum - 2;
            cmXtaCb.tstGrp[tGroupNum-1].endTest = cmXtaCb.tstGrp[tGroupNum-1].numTests;
            tcRangeSelected = TRUE;
            break;

         case 'm':
            /*-- to set the TA mode --*/

            /*-- Copy the value directly in the mode as the 
                 mode defines are set that way --*/
            cmXtaCb.mode = atoi(msOptArg);
            break;

         case 'n':
            /*-- to set the TA loop value --*/

            /*-- Copy the value directly in the mode as the 
                 mode defines are set that way --*/
            cmXtaCb.maxLoopCnt = atoi(msOptArg);
            break;

         case 'p':
            /*-- to set the profile --*/
            cmXtaCb.curTopId = atoi(msOptArg);

            if (cmXtaCb.curTopId >= topCount)
            {
               SPrint("ERROR: Invalid profile Id");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }

            break;

         case 'q':
            /* turn off the verbose flag - disable printing     */
            cmXtaCb.dbgMask = 0;
            break;

         case 'T':
            /*-- Slow down before TC Shutdown --*/
            /*-- to set the delay timer for TA --*/
            cmXtaCb.delayTstShutDownVal = atoi(msOptArg);

            if (cmXtaCb.delayTstShutDownVal == 0)
               cmXtaCb.delayTstShutDownVal = CMXTA_TMR_DELAY_SHUTDOWN_VAL;
            cmXtaCb.directives.delayShutDown = TRUE;
            break;

         case 'U':
            /*-- Slow down TA --*/
            /*-- to set the delay timer for TA --*/
            cmXtaCb.delayTstVal = atoi(msOptArg);
            if (cmXtaCb.delayTstVal == 0)
               cmXtaCb.delayTstVal = CMXTA_TMR_DELAY_TST_VAL;
            cmXtaCb.directives.delayTest = TRUE;
            break;

         case 't':
            /* test number has been specified, run the particular TC */
            if (groupSelected == FALSE)
            {
               SPrint("ERROR: Enter -g option before -t");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            else if (tcRangeSelected == TRUE)
            {
               SPrint("ERROR: -t and -f & -e not allowed together");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            else
            {
               testNum = atoi(msOptArg);
            }
   
            /* cm_xta_master_c_001.main_5 :Added validation for tGroupNum */
            if ((tGroupNum <= cmXtaCb.tstGrpCnt) && (tGroupNum > 0))
            {
               if ((testNum > cmXtaCb.tstGrp[tGroupNum-1].numTests) || (testNum <= 0))
               {
                  SPrint("ERROR: Invalid test number");
                  SPrint("\n\n");
                  cmXtaMasterUsage();
                  RETVALUE(RFAILED);
               }
            }
            /* Set the start and end range --*/
            cmXtaCb.tstGrp[tGroupNum-1].startTest = testNum - 2;
            cmXtaCb.tstGrp[tGroupNum-1].tstList[testNum -1].state = CMXTA_RUN;

            cmXtaCb.tstGrp[tGroupNum-1].endTest = testNum;

            /*-- Reset this test group options --*/
            groupSelected = FALSE;
            tcRangeSelected = FALSE;

            break;

         case 'u':
            /* test number has been specified, leave the particular TC from the
             * group.Multiple options can be given through this.
             * For e.g. r -g 10 -u 1 -u 2*/
            if (groupSelected == FALSE)
            {
               SPrint("ERROR: Enter -g option before -u");
               SPrint("\n\n");
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
            }
            else
            {
               testNum = atoi(msOptArg);
            }
            /* cm_xta_master_c_001.main_5 :Added validation for tGroupNum */
            if ((tGroupNum <= cmXtaCb.tstGrpCnt) && (tGroupNum > 0))
            {
               if ((testNum > cmXtaCb.tstGrp[tGroupNum-1].numTests) || (testNum <= 0))
               {
                  SPrint("ERROR: Invalid test number");
                  SPrint("\n\n");
                  cmXtaMasterUsage();
                  RETVALUE(RFAILED);
               }
            }
            /* Set the state of the particular test case */
            cmXtaCb.tstGrp[tGroupNum-1].tstList[testNum -1].state = CMXTA_IDLE;

            break;

         case 'x':
            loop = FALSE;
            break;

         case 'z':
            /*-- Dump the simple command documentation --*/
            ret = cmXtaXmlDumpSimpleCmd();
            RETVALUE(CMXTA_ERR_COMPLETE);
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

   /* if no group selected, show usage                          */
   if((oneGroup == FALSE) && (descNum == -1))
   {
      cmXtaMasterUsage();
      RETVALUE(RFAILED);
   }

   /* check and process command line options            */
   if ((ret = cmXtaAppMasterParseCmdLine()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaMasterParseCmdLine */

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
PUBLIC S16 cmXtaMasterParseDebug
(
Void
)
#else
PUBLIC S16 cmXtaMasterParseDebug()
#endif
{
   S16          ret;                            /* return value         */
   Bool         loop;

   TRC2(cmXtaMasterParseDebug)

   parse = FALSE;

   /*-- SSI options skipped, move to TA options --*/
   loop = TRUE;
   /* parse the command line parameters                         */
   while ((loop == TRUE) &&
          ((ret = SGetOpt(msArgc, msArgv, "Pd:hKRLx")) != EOF))
   {
      switch(ret)
      {

         case 'd':
            /*-- Set debug level --*/
            cmXtaCb.dbgMask = atoi(msOptArg);
            break;

         case 'K':
            cmXtaCb.directives.xmlOutput = TRUE;
            break;

         case 'L':
            cmXtaCb.directives.memCalculate = TRUE;
            break;

         case 'R':
            cmXtaCb.directives.memFlag = TRUE;
            break;

         case 'P':
            /*-- Parse all XML Test cases while loading itself --*/
            parse = TRUE;
            break;

         case 'x':
            /*-- No match, assume same as -x and move on --*/
            loop = FALSE;
            break;

         case 'h':
            /* help and unknown options display help message    */
            cmXtaMasterUsage();
            RETVALUE(RFAILED);
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

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaMasterParseDebug */

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
PUBLIC S16 cmXtaMasterParseRdConQ
(
Data data
)
#else
PUBLIC S16 cmXtaMasterParseRdConQ(data)
Data data;
#endif
{
   U32  memAvail;

   TRC2(cmXtaMasterParseRdConQ)

   /*-- Check if we are in load mode --*/
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      switch (data)
      {
         case 'p' :
         case 'P' :
/* cm_xta_master_c_002.main_1 : Updated for MT-SIP Release*/
#ifdef SO_MT_SIP
#ifdef SO_MT_SIP_INTDBG
            cmXtaAppPrintInfo();
            break;

         case 'l' :
         case 'L' :
            cmXtaTuclPrintInfo();
#endif
#endif
/* cm_xta_master_c_001.main_4: IU_UP changes during perfomance */
#ifdef LX_ACC
#ifdef DEBUGP
            lxCmPrintSts();
#endif
            cmXtaAppPrintInfo();
#endif

/* cm_xta_master_c_002.main_1 : Updated for MT-SIP Release*/
#ifdef SO_MT_SIP
#ifdef SO_MT_SIP_INTDBG
/* cm_xta_master_c_001.main_3: DEBUGP added MT_SIP debug prints   */
#ifdef DEBUGP
            cmXtaAppPrintInfo();
            break;

         case 'l' :
         case 'L' :
            cmXtaTuclPrintInfo();
#endif
#endif
#endif
            break;

         case 's' :
         case 'S' :
            cmXtaLoadDisplay();
            break;

         case 'm' :
         case 'M' :
            SRegInfoShow(cmXtaCb.init.region, &memAvail);
            break;

/* cm_xta_master_c_001.main_6: control switch over implemented 
      for PSF-SIP integrated set-up. */
#ifdef CMXTA_FTHA_INTEGRATED
         case 'c' :
         case 'C' :
            cmXtaControlSwitch();
            break;
#endif

         case 'q' :
         case 'Q' :
            cmXtaCb.loadDir.loadMode = FALSE;

            /*-- Inform application code that the load sampling is 
                 stopped */
            cmXtaAppLoadDeInit();

            /*-- Re ignite the TC engine --*/
            cmXtaTCReq(cmXtaCb.curTCCb, CMXTA_ERR_NONE);
            break;

         default :
            break;
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaMasterParseRdConQ */

/********************************************************************30**

         End of file:     cm_xta_master.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:24 2015

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
/main/2      ----     sk  1. Support for multiple proc
                      aj  2. Updated for MT-SIP Release
/main/3      ----     aj  1. Updated for the FTHA Integration   
/main/4      ----  cm_xta_master_c_001.main_3   ve  1. DEBUGP added for MT_SIP 
                                                       debug prints   
/main/5      ----  cm_xta_master_c_001.main_4   rss 1. IU_UP changes during perfomance
                                                       Testing.
/main/6      ----  cm_xta_master_c_001.main_5   kchaitanya  1. Updated for fixing klockwork
                                                             errors
/main/7      ----  cm_xta_master_c_001.main_6   ve  1. control switch over implemented 
                                                       for PSF-SIP integrated set-up.
/main/8      ---      cm_xta_master_c_001.main_7  pkaX  1. Fix for the 64bit compilation warning.
/main/9      ---   cm_xta_master_c_001.main_8     nh 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
