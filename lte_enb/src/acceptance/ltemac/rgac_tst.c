


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for the functions needed by CM XTA to execute 
               layer specific code. 
  
     File:     rgac_tst.c 
  
     Sid:      rgac_tst.c@@/main/3 - Sat Jul 30 02:21:10 2011
  
     Prg:     sm 
  
**********************************************************************/

/** @file rgac_tst.c.
@brief It has The functions that are neede by CM XTA to execute any layer 
specific code, during intialization and shutdown. 
*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */
#include "rgac_rgr.h"

#include "cm_xta.h"
#include "cm_xta_app.h"
#include <stdlib.h>

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
#include "cm_xta_app.x"
#include "rgac_acc.x"

PUBLIC RgAcCb rgAccCb;
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
PUBLIC S16 cmXtaAppTCCreate
(
CmXtaTCCb         *tcCb
)
#else
PUBLIC S16 cmXtaAppTCCreate(tcCb)
CmXtaTCCb    *tcCb;
#endif
{
   U8    dlSchedType;
   U8    ulSchedType;
   UNUSED(tcCb);
   CMXTA_ZERO(&rgAcTfCb, sizeof(rgAcTfCb));
   CMXTA_ZERO(&junkData, (sizeof(U8) * RG_ACC_MAX_PDU_SIZE));
   /* Work around for now as there is a possiblity of incorrect state being
    * carried to the next test case. - Ideal solution would entail memseting
    * once in cmXtaAppTst.
    */
   dlSchedType = rgAccCb.dlSchedType;
   ulSchedType = rgAccCb.ulSchedType;
   CMXTA_ZERO(&rgAccCb, sizeof(RgAcCb));
   /* Restoring */
   rgAccCb.dlSchedType = dlSchedType;
   rgAccCb.ulSchedType = ulSchedType;
   rgAccCb.dedCrnti    = RG_ACC_DED_RNTI_START;  /* Dedicated RNTI added in rgAccCb for HO UE */
   rgAcTfCb.crntTime.subframe = 9;
   rgAcTfCb.crntTime.sfn = 1023;
   /* Added for sending TTI tick to RRM */
#ifdef RGR_RRM_TICK
   rgAccCb.rgrCrntTime.sfn = 0;
   rgAccCb.rgrCrntTime.subframe = 0;
#endif
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppTCCreate() */
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
PUBLIC S16  cmXtaAppTCDelete
(
CmXtaTCCb         *tcCb       /* Transaction Block   */
)
#else
PUBLIC S16  cmXtaAppTCDelete (tcCb)
CmXtaTCCb      *tcCb;         /* Transaction Block   */
#endif
{
   U8                 idx;
   RgAcUeCb           *ueCb;
   RguDStaIndInfo     *dSta;
   CmLList            *node;

   TRC2(cmXtaAppTCDelete);

   UNUSED(tcCb);
   for (idx = 0; idx < RG_ACC_MAX_BCCH; idx++)
   {
      if (rgAccCb.bcchBuf[idx] != NULLP)
      {
         (Void)SPutMsg (rgAccCb.bcchBuf[idx]);
         rgAccCb.bcchBuf[idx] = NULLP;
      }
   }
   for (idx = 0; idx < RG_ACC_MAX_UE; idx++)
   {
      if (rgAccCb.dedBuf[idx] != NULLP)
      {
         (Void)SPutMsg (rgAccCb.dedBuf[idx]);
         rgAccCb.dedBuf[idx] = NULLP;
      }
   }
   for (idx = 0; idx < RG_ACC_MAX_UE; idx++)
   {
      ueCb = &(rgAccCb.acUeCb[idx]);
      while (ueCb->staIndLst.first)
      {
         dSta = (RguDStaIndInfo *)ueCb->staIndLst.first->node;
         node = ueCb->staIndLst.first;
         cmLListDelFrm(&ueCb->staIndLst, ueCb->staIndLst.first);
         SPutSBuf(cmXtaCb.init.region,cmXtaCb.init.pool, 
               (Data *)node, sizeof(*node));
         SPutSBuf(cmXtaCb.init.region,cmXtaCb.init.pool, 
               (Data *)dSta, sizeof(RguDStaIndInfo));
      }

   }
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTCDelete */

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
PUBLIC S16 cmXtaAppPyInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaAppPyInit */
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
PUBLIC S16 cmXtaAppLoadEngine
(
CmXtaLoadCb    *loadCb,
Void        *loadMsg,
Bool        retransMode,
U16         curLoadIndx,
U16         retransLoadIndx
)
#else
PUBLIC S16 cmXtaAppLoadEngine(loadCb, loadMsg, retransMode, curLoadIndx,retransLoadIndx)
CmXtaLoadCb    *loadCb;
Void        *loadMsg;
Bool        retransMode;
U16         curLoadIndx;
U16         retransLoadIndx;
#endif
{
   UNUSED(loadCb);
   UNUSED(loadMsg);
   UNUSED(retransMode);
   UNUSED(curLoadIndx);
   UNUSED(retransLoadIndx);
   RETVALUE(CMXTA_ERR_NONE);
}

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
PUBLIC S16 cmXtaAppPyDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyDeInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaAppPyDeInit */

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
PUBLIC S16 cmXtaAppLoadInit
(
)
#else
PUBLIC S16 cmXtaAppLoadInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}
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
PUBLIC S16 cmXtaAppLoadGetCurStep
(
Void  *loadMsg,
CmXtaLoadCb  *loadCb,
U16   *curLoadIndx,
U16   *retransLoadIndx
)
#else
PUBLIC S16 cmXtaAppLoadGetCurStep(loadMsg, loadCb, curLoadIndx, retransLoadIndx)
Void  *loadMsg;
CmXtaLoadCb  *loadCb;
U16   *curLoadIndx;
U16   *retransLoadIndx;
#endif
{
   UNUSED(loadMsg);
   UNUSED(loadCb);
   UNUSED(curLoadIndx);
   UNUSED(retransLoadIndx);
   RETVALUE(CMXTA_ERR_NONE);
}

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
PUBLIC S16 cmXtaAppLoadFindnCreate
(
Void  *msg,
Bool  *newCall,
CmXtaLoadCb  **loadCb
)
#else
PUBLIC S16 cmXtaAppLoadFindnCreate(msg, newCall, loadCb)
Void  *msg;
Bool  *newCall;
CmXtaLoadCb  **loadCb;
#endif
{
   UNUSED(msg);
   UNUSED(newCall);
   UNUSED(loadCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadFindnCreate() */
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
PUBLIC S16 cmXtaAppLoadDelete
(
CmXtaLoadCb  *loadCb,
Bool      fail
)
#else
PUBLIC S16 cmXtaAppLoadDelete(loadCb, fail)
CmXtaLoadCb  *loadCb;
Bool      fail;
#endif
{
   UNUSED(loadCb);
   UNUSED(fail);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadDelete() */

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
PUBLIC S16 cmXtaAppLoadFreeMsg
(
Void     *loadMsg
)
#else
PUBLIC S16 cmXtaAppLoadFreeMsg(loadMsg)
Void     *loadMsg;
#endif
{
   UNUSED(loadMsg);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadFreeMsg() */
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
   UNUSED(msgQ);
   RETVOID;
} /* cmXtaAppFlushQ */

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
   UNUSED(msgQ);
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppInitQ */

 /** @brief This function is called by CM XTA, to help layer specific
  * intialization. 
  *
  * @details 
  *
  *     Function: cmXtaAppTst
  *
  *         Processing steps:
  *         - Node
  *
  *
  * @return CMXTA_ERR_NONE
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppTst
(
 Void
 )
#else
PUBLIC S16 cmXtaAppTst ()
#endif
{
   TRC2(cmXtaAppTst)
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppTst*/ 

 /** @brief This function is called by cm xta to intialize layer specific code.
  *
  * @details
  *
  *     Function: cmXtaAppMasterInit
  *
  *         Processing steps:
  *         - Initialize the rgAcCb structure
  *         - Call the initializing function of all the interfaces.
  *
  *
  * @return 
  * -# CMXTA_ERR_NONE
  * -# CMXTA_ERR_INT
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterInit
(
 Void
 )
#else
PUBLIC S16 cmXtaAppMasterInit ()
#endif
{
   S16      ret;
   U8       ipType = 4; /* IPV4 = 4, IPV6 = 6 */

   TRC2(cmXtaAppMasterInit);

   ret = CMXTA_ERR_NONE;

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Initializing the LTE-MAC Test Architecture\n"));

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
   rlInitLog(ipType);

   /* Initialize LRG */
   if ((ret = rgAcLrgInit ()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   /* Initialize TFU */
   if ((ret = rgAcTfuInit ()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   /* Initialize RGU */
   if ((ret = rgAcRguInit ()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   /* Initialize CRG */
   if ((ret = rgAcCrgInit ()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   /* Initialize RGM */
   if ((ret = rgAcRgmInit ()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   /* Initialize CRG */
   if ((ret = rgAcRgrInit ()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   if ((ret = rgAcDcfiStubSimpleCmdInit ()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   if ((ret = rgAcPfsSimSimpleCmdInit ()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppMasterInit */ 

 /** @brief This function is called by CM XTA to let the layer specific clean up
  * code execute.
  *
  * @details
  *
  *     Function: cmXtaAppMasterDeInit
  *
  *         Processing steps:
  *         - Free up any memory stored in the control blocks
  *         - Call the DeInit for all the interfaces. 
  *
  *
  * @return 
  * -# CMXTA_ERR_NONE
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterDeInit
(
 Void
 )
#else
PUBLIC S16 cmXtaAppMasterDeInit ()
#endif
{
   TRC2(cmXtaAppMasterDeInit)

   (Void) rgAcLrgDeInit();
   (Void) rgAcTfuDeInit();
   (Void) rgAcRguDeInit();
   (Void) rgAcCrgDeInit();
   (Void) rgAcRgrDeInit();
   (Void) rgAcDcfiStubSimpleCmdDeInit();
   (Void) rgAcPfsSimSimpleCmdDeInit();
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppMasterDeInit */ 

 /** @brief This function is called by CM XTA to parse the layer specific
  * command line option provided by the user.
  *
  * @details
  *
  *     Function: cmXtaAppMasterParseCmdLine
  *
  *         Processing steps:
  *         - Run through the arguments and fill in the values into the rgAcCb
  *
  * @return 
  * -# CMXTA_ERR_NONE
  * -# CMXTA_ERR_INT
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterParseCmdLine
(
 Void
 )
#else
PUBLIC S16 cmXtaAppMasterParseCmdLine ()
#endif
{
   S16   ret;
   TRC2(cmXtaAppMasterParseCmdLine)
   ret = CMXTA_ERR_NONE;
   /* Set Default scheduler types to RR*/
   rgAccCb.dlSchedType = RGAC_RGR_SCH_TYPE_RR;
   rgAccCb.ulSchedType = RGAC_RGR_SCH_TYPE_RR;

   while ((ret = SGetOpt(msArgc, msArgv, "b:f:o:s:u:")) != EOF)
   {
      switch (ret)
      {
         case 'f':
         case 'o':
            break;
         case 's':
            rgAccCb.dlSchedType = atoi(msOptArg);
            break;
         case 'u':
            rgAccCb.ulSchedType = atoi(msOptArg);
            break;
         default:
            cmXtaMasterUsage();
            RETVALUE(CMXTA_ERR_INT);
            break;
      } /* end of switch */
   } /* end of while */
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppMasterParseCmdLine */ 

 /** @brief This function is called to intialize the slave in the case of a
  * Master/Slave execution. 
  *
  * @details
  *
  *     Function: cmXtaAppSlaveInit
  *
  *         Processing steps:
  *         - None
  *
  *
  * @return CMXTA_ERR_NONE
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveInit
(
 Void
 )
#else
PUBLIC S16 cmXtaAppSlaveInit ()
#endif
{
   TRC2(cmXtaAppSlaveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Initializing the slave\n"));
   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Init Done\n"));
   RETVALUE(CMXTA_ERR_NONE);
} /* end of */ 

 /** @brief This function is called to shut down any layer specific code being
  * run at the slave.
  *
  * @details
  *
  *     Function: cmXtaAppSlaveDeInit
  *
  *         Processing steps:
  *         - 
  *
  * @return CMXTA_ERR_NONE
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveDeInit
(
 Void
 )
#else
PUBLIC S16 cmXtaAppSlaveDeInit ()
#endif
{
   TRC2(cmXtaAppSlaveDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveDeInit(): Shutting down the Test Architecture\n"));

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveDeInit(): Test Architecture Shutdown Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppSlaveDeInit  */ 

 /** @brief This function is called to parse the command line options given at
  * the slave. 
  *
  * @details
  *
  *     Function:  cmXtaAppSlaveParseCmdLine
  *
  *         Processing steps:
  *         - 
  *
  * @return CMXTA_ERR_NONE
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveParseCmdLine
(
 Void
 )
#else
PUBLIC S16 cmXtaAppSlaveParseCmdLine ()
#endif
{
   TRC2(cmXtaAppSlaveParseCmdLine)

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppSlaveParseCmdLine  */ 

 /** @brief This function prints the options provided for slave execution. 
  *
  * @details
  *
  *     Function: cmXtaAppSlaveUsage
  *
  *         Processing steps:
  *         - 
  * @return Void
  */
#ifdef ANSI
PUBLIC Void cmXtaAppSlaveUsage
(
 Void
 )
#else
PUBLIC Void cmXtaAppSlaveUsage ()
#endif
{
   TRC2(cmXtaAppSlaveUsage);

   RETVOID;
} /* end of cmXtaAppSlaveUsage */ 

 /** @brief This function is called by CM XTA to intialize any layer specific
  * directive.
  *
  * @details
  *
  *     Function:  cmXtaAppDirectiveInit
  *
  *         Processing steps:
  *         - 
  *
  *
  * @return CMXTA_ERR_NONE
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppDirectiveInit
(
 Void
 )
#else
PUBLIC S16 cmXtaAppDirectiveInit ()
#endif
{
   TRC2(cmXtaAppDirectiveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppDirectiveInit(): Init\n"));
   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppDirectiveInit(): Init done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppDirectiveInit */ 

 /** @brief This function prints the usage of MAC specific XTA options.
  *
  * @details
  *
  *     Function: 
  *
  *         Processing steps:
  *         - 
  *
  *
  */
#ifdef ANSI
PUBLIC Void cmXtaAppMasterUsage 
(
 Void
 )
#else
PUBLIC Void cmXtaAppMasterUsage ()
#endif
{
   TRC2(cmXtaAppMasterUsage)
   RETVOID;
} /* end of */ 

 /** @brief This function 
  * @param  
  * @param 
  * @return 
  */
#ifdef ANSI 
PUBLIC S16 cmXtaAppLoadDeInit
(
)
#else
PUBLIC S16 cmXtaAppLoadDeInit()
#endif
{
   TRC2(cmXtaAppLoadDeInit)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaAppLoadDeInit(): \n"));
   RETVALUE(CMXTA_ERR_NONE);
}


/**********************************************************************
 
         End of file:     rgac_tst.c@@/main/3 - Sat Jul 30 02:21:10 2011
 
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
/main/1      ---     sm   1. Initial Release.
/main/2      ---     sm   1. LTE MAC 2.1 release
             rg001.201 sm            1. Added TTI indication towards 
                                        RGR user.
/main/3      ---     nu   1. Updated for release LTE-MAC 3.1.
$SID$        ---     rt   1. LTE MAC 4.1 release
*********************************************************************91*/
