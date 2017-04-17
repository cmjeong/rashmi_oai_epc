

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_tst.c

     Sid:      rmac_tst.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:31 2013

     Prg:      vprabhu

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS libraru defines */
#include "cm_xta.h" 
#include "cm_pasn.h"
#include "rm.h"
//#include "wr_cmn.h"
//#include "wr_smm_init.h"
#include "rmac_acc.h"
#include "rmu.h"
#include "lrm.h"
#include "rgm.h"

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */
#include "cm_xta.x" 
#include "cm_pasn.x"
#include "lrm.x"
#include "rmu.x"
#include "rgm.x"
#include "rmac_acc.x"

/*
*
*       Fun:   cmXtaAppMasterDeInit
*
*       Desc:  This functions is called from the SSI.
*              It registers the various layers with
*              SSI.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  tq_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppMasterDeInit()
#endif
{
   TRC2(cmXtaAppMasterDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterDeInit(): Shutting down the Test Architecture\n"));

   /*-- Opposite of the steps done in aqAcInit --*/

   /*-- Put DeInit functions for rest of the
        modules here, this will happen only once --*/

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterDeInit(): Test Architecture Shutdown Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterDeInit */


/*
*
*      Fun  : cmXtaAppMasterParseCmdLine
*
*      Desc : This function parses the command line to set
*             the test usage options.
*
*      Ret  : Void
*
*      Notes: None
*
*      File : tq_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterParseCmdLine
(
Void
)
#else
PUBLIC S16 cmXtaAppMasterParseCmdLine()
#endif
{
   S16          ret = 0;                        /* return value         */
   ProcId           procId;


   TRC2(cmXtaAppMasterParseCmdLine)

   while ((ret = SGetOpt(msArgc, msArgv, "ab:c:d:f:hi:o:p:r:t:")) != EOF)
   {
      switch(ret)
      {
         /*-- SSI specific --*/
         case 'f':
         case 'o':
            /* we ignore the output specifier and specifiers used by TA command
               line parser --*/
            break;

         case 'd':
            /*-- Set debug level --*/
            cmXtaCb.dbgMask = atoi(msOptArg);
            break;

         case 'h':
            /* help and unknown options display help message    */
            cmXtaMasterUsage();
            RETVALUE(RFAILED);
            break;

         case '?':
         default:
            /* help and unknown options display help message    */
            cmXtaMasterUsage();
            RETVALUE(RFAILED);
            break;
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterParseCmdLine */

/*
*
*       Fun:   cmXtaAppTst
*
*       Desc:  This functions is called from the SSI.
*              It registers the various layers with
*              SSI.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  wrac_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppTst
(
)
#else
PUBLIC S16 cmXtaAppTst(Void)
#endif
{
   TRC2(cmXtaAppTst)

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTst */

/*
*
*       Fun:   cmXtaAppMasterInit
*
*       Desc:  Initialization function for acceptance test
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  wrac_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterInit
(
Void
)
#else
PUBLIC S16 cmXtaAppMasterInit(Void)
#endif
{
   S16      ret = 0;
   U8       ipType = 4; /* IV4 = 4, IPV6 = 6*/

   TRC2(cmXtaAppMasterInit)
      CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Initializing the Test Architecture\n"));

   rlSetLogPath(".");
   rlSetLogFile("dbglog.txt");
   rlSetNumOfLogFiles(5);
   rlSetLogFileSizeLimit(5);
   rlSetLogLevel(6);
   rlSetLogPort(9999);
   rlSetRemoteLoggingFlag(0);
   rlSetCircularBufferSize(100);
   rlEnableDisableCore(1);
   rlSetModuleMask(0);
   rlInitLog(0);

#if 0
   /* Read the parameters from the file and copy into global control block */
   if(smWrReadConfigParams() != ROK)
   {
#if 0
      WRDBGP(DBGMASK_SM, (smCb.init.prntBuf, "FAILED TO READ FROM FILE \
               wr_cfg.txt\n"));
#endif
   } /* end of if statement */
   /* Enable sm debugs */
   if(smCfgCb.smDbg == 1)
   {
      /* Update DbgMsk */
      smCb.init.dbgMask = 0xffffffff;
      WRDBGP(DBGMASK_SM, (smCb.init.prntBuf, "Enabled SM Debug Prints\n"));
   } /* end of if statement */
#endif

#if 0
   /*-- RLC/PDCP module init function --*/
   if ((ret = wrAcKwuInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- LTE MAC module init function --*/
   if ((ret = wrAcRguInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- Convergence layer(L1) module init function --*/
   if ((ret = wrAcl1Init()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- RRC module init function --*/
   if ((ret = wrAcNhuInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif
   rmAcLrmInit();
   rmAcRmuInit();
#ifdef RRM_UNUSED_FUNC
   rmAcRgmInit();
#endif

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Test Architecture Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterInit */

/*
*
*      Fun  : cmXtaAppMasterUsage
*
*      Desc : This function displays an acceptance test usage message.
*
*      Ret  : Void
*
*      Notes: None.
*
*      File :
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppMasterUsage
(
Void
)
#else
PUBLIC Void cmXtaAppMasterUsage()
#endif
{
   Txt   pBuf[100];  /* output string buffer */

   TRC2(cmXtaAppUsage);

   cmMemset((U8*)&pBuf, 0 , 100);
   sprintf(pBuf, "eNbApp Options:\n============\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-d 0-9 dbgMask     ]   - Enable Debug Masks \n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-r xtaProcId       ]   - Set the xtaProcId\n");
   SPrint(pBuf);

   RETVOID;
} /* cmXtaAppMasterUsage */

/*
*
*      Fun  : cmXtaAppSlaveUsage
*
*      Desc : This function displays an acceptance test usage message.
*
*      Ret  : Void
*
*      Notes: None.
*
*      File :
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppSlaveUsage
(
Void
)
#else
PUBLIC Void cmXtaAppSlaveUsage()
#endif
{
   TRC2(cmXtaAppSlaveUsage);

   RETVOID;
} /* cmXtaAppSlaveUsage */


/*
*
*       Fun:   cmXtaAppSlaveInit
*
*       Desc:  Initialization function for acceptance test
*
*       Ret:   Void
*
*       Notes: None
*
*       File:
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveInit
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveInit(Void)
#endif
{
   TRC2(cmXtaAppSlaveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Initializing the slave\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveInit */

/*
*
*       Fun:   cmXtaAppSlaveDeInit
*
*       Desc:  This functions is called from the SSI.
*              It registers the various layers with
*              SSI.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveDeInit()
#endif
{
   TRC2(cmXtaAppSlaveDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveDeInit(): Shutting down the Test Architecture\n"));

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveDeInit(): Test Architecture Shutdown Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveDeInit */

/*
*
*      Fun  : cmXtaAppSlaveParseCmdLine
*
*      Desc : This function parses the command line to set
*             the test usage options.
*
*      Ret  : Void
*
*      Notes: None
*
*      File : 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveParseCmdLine
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveParseCmdLine()
#endif
{

   TRC2(cmXtaAppSlaveParseCmdLine)

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveParseCmdLine */

/*
*
*       Fun:   cmXtaAppDirectiveInit
*
*       Desc:  Call handler for Command Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppDirectiveInit
(
Void
)
#else
PUBLIC S16 cmXtaAppDirectiveInit()
#endif
{

   TRC2(cmXtaAppDirectiveInit)


   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppDirectiveInit(): Init done\n"));

   cmXtaCb.directives.capAlarm  =   TRUE;
   cmXtaCb.directives.capTrc  =   TRUE;


   RETVALUE(ROK);
}/* cmXtaAppDirectiveInit */
 
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
PUBLIC S16 cmXtaAppInitQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC S16 cmXtaAppInitQ(msgQ)
CmXtaMsgQ   *msgQ;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppInitQ */

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
PUBLIC Void cmXtaAppFlushQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC Void cmXtaAppFlushQ(msgQ)
CmXtaMsgQ *msgQ;
#endif
{
   RETVOID;
} /* cmXtaAppFlushQ */

/*
 *
 *       Fun:    cmXtaAppTCCreate
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaAppTCCreate
(
CmXtaTCCb         *tcCb
)
#else
PUBLIC S16 cmXtaAppTCCreate(tcCb)
CmXtaTCCb    *tcCb;
#endif
{

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppTCCreate() */

/*
*
*       Fun:   cmXtaAppTCDelete
*
*       Desc:  This function deletes an existing transaction.
*
*       Ret:   If success, return CMXTA_ERR_NONE
*              If failure, return error Code
*
*       Notes: None
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16  cmXtaAppTCDelete
(
CmXtaTCCb         *tcCb       /* Transaction Block   */
)
#else
PUBLIC S16  cmXtaAppTCDelete (tcCb)
CmXtaTCCb      *tcCb;         /* Transaction Block   */
#endif
{
/*   szAccCb.hitCb.nxtConnId = 0; */
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTCDelete */

#if (!defined(SZAC_INTG_TEST) && !defined(ENB_RELAY))
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
PUBLIC S16 cmXtaAppIpcInit
(
Void
)
#else
PUBLIC S16 cmXtaAppIpcInit(Void)
#endif
{

   TRC2(cmXtaAppIpcInit)
   /*-- Part of support for multiple slaves. In order to talk to 
        multiple slaves we need to have relay configured for each of the 
        nodes. The following code if the relay flag is enabled will use the 
        common relay product else it will used the minmial relay that we have as 
        part of CM_XTA. --*/

   RETVALUE(ROK);

}/* cmXtaAppIpcInit()*/

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
PUBLIC S16 cmXtaAppIpcDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppIpcDeInit(Void)
#endif
{
   TRC2(cmXtaAppIpcDeInit)

   RETVALUE(ROK);
}/* cmXtaAppIpcDeInit()*/
#endif /* (!defined(SZAC_INTG_TEST) && !defined(SS_VW))*/


/*
*       Fun:   cmXtaAppPyInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File: 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppPyInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}/* */

/*
*
*       Fun:   cmXtaAppPyDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File: 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppPyDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyDeInit()
#endif
{
   TRC2(cmXtaAppPyDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppPyDeInit(): Shutting down python interpreter\n"));

   RETVALUE(CMXTA_ERR_NONE);
}/* aqacPyDeInit */


