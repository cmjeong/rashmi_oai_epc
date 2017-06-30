
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_tst.c

     Sid:      egac_edmtst.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:26 2015

     Prg:     an 
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
#include "cm_dns.h"         /* common DNS libraru defines */

#include "egt.h"           /* EGT defines */
#include "leg.h"           /* layer management defines for S1AP */

#ifdef HI
#include "lhi.h"
#endif

#include "cm_xta.h"

#include "eg.h"            /* defines and macros for S1AP */
#include "egac_acc.h"      /* defines for S1AP acceptance tests */
#include "egac_edm.h"

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

#include "egt.x"           /* EGT types */
#include "leg.x"           /* layer management typedefs for S1AP */
#include "cm_xta.x"

#ifdef HI
#include "lhi.x"
#include "egac_lhi.x"
#endif

#include "eg.x"            /* typedefs for EG*/
#include "egac_acc.x"      /* typedefs for EG acceptance tests */
#include "egac_edm.x"

#include <stdlib.h>



PUBLIC CmXtaTopology cmXtaTop[] =
{
   cmXtaTopStart("TC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
   cmXtaTopProcStart(1)  
       EGAC_PROCID_SINGLE 
   cmXtaTopProcEnd
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart


        cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, edActvInit,   edActvTsk)
        cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk)
      cmXtaTopEntitiesEnd


      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTTST,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTTST,  CMXTA_INST_ID,     1, 1)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/
};




/*
*
*       Fun:   cmXtaAppTst
*
*       Desc:  This function is invoked from tst() function
*              defined in cm_xta_tst() function.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  egac_tst.c
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
*       Desc:  Initialization function for acceptance test.
*              This function is invoked from cmXtaMasterInit().
*              After performing all the initializations, this
*              function is invoked.
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  egac_tst.c
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

   TRC2(cmXtaAppMasterInit)
   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Initializing the Test Architecture\n"));

   /*  Initialize the global structure   */
   cmMemset((U8 *)&egAccCb,0,sizeof(EgAccCb));

   /*-- EDM module init function --*/
   if ((ret = egAcEdmInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   egAccCb.directives.xtaProcId =   EGAC_PROCID_SINGLE;
   egAccCb.directives.hiProcId  =   EGAC_PROCID_SINGLE;

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Test Architecture Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterInit */


/*
*
*       Fun:   cmXtaAppMasterDeInit
*
*       Desc:  This function de-initializes the various interfaces.
*              This function is invoked from cmXtaMasterDeInit().
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  egac_tst.c
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

   /*-- EGT module deInit function --*/
   (Void)egAcEdmDeInit();

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
*      File : egac_tst.c
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
   ProcId       procId= 0;


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

         case 'r':
            /* Xta Proc Id */
            procId = atoi(msOptArg);
            egAccCb.directives.xtaProcId = procId;
            egAccCb.directives.hiProcId = procId;
            break;

         case '?':
         default:
            /* help and unknown options display help message    */
            cmXtaMasterUsage();
            RETVALUE(RFAILED);
            break;
      }
   }

   if(cmXtaCb.curTopId == 3) 
   {
            egAccCb.directives.xtaProcId =   EGAC_PROCID_ONE;
            egAccCb.directives.hiProcId  =   EGAC_PROCID_ONE;
   }
   if((cmXtaCb.curTopId == 5))
   {
            egAccCb.directives.xtaProcId = CMXTA_PROCID_MASTER;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterParseCmdLine */

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
*      File : egac_tst.c
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
   sprintf(pBuf, "eGTP Options:\n============\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-d 0-9 dbgMask     ]   - Enable Debug Masks \n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-r xtaProcId       ]   - Set the xtaProcId\n");
   SPrint(pBuf);

   RETVOID;
} /* cmXtaAppMasterUsage */

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
*       File:  egac_tst.c
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
#ifdef SS_MULTIPLE_PROCS
   egActvInit(ENTEG, 0, 0, 0);
#endif
   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Init Done\n"));

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
*       File:  egac_tst.c
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
*      File : egac_tst.c
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
*      Fun  : cmXtaAppSlaveUsage
*
*      Desc : This function displays an acceptance test usage message.
*
*      Ret  : Void
*
*      Notes: None.
*
*      File : egac_tst.c
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
*       Fun:   cmXtaAppDirectiveInit
*
*       Desc:  Directive Initialization
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_tst.c
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
*       Fun:  cmXtaAppInitQ
*  
*       Desc: Initialization of Application queue 
*              
*       Ret:  ROK 
*              
*       Notes: 
*
*       File: egac_tst.c 
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
*       Fun:  cmXtaAppFlushQ
*
*       Desc: Hook function which is invoked by cmXta. 
*              
*       Ret:  Void 
*              
*       Notes: 
*
*       File: egac_tst.c 
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
 *       Desc:   Application TC Create 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   egac_tst.c
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
*       File:  egac_tst.c
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
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTCDelete */


/*
*       Fun:   cmXtaAppPyInit
*
*       Desc:  Python Initialization
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_tst.c
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
}/* egacPyInit */


 
/*
 *
 *       Fun:    edActvInit - eGTP user initialization function
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   ed_ex_ms.c
 *
 */
#ifdef ANSI
PUBLIC S16 edActvInit
(
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason               /* reason */
)
#else
PUBLIC S16 edActvInit(ent, inst, region, reason)
Ent      ent;                 /* entity */
Inst     inst;                /* instance */
Region   region;              /* region */
Reason   reason;              /* reason */
#endif /* ANSI */
{
   TRC3(edActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of edActvInit() */


/*
 *
 *       Fun:    edActvTsk - eGTP user activation
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   ed_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 edActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else
PUBLIC S16 edActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   Mem sMem;

   TRC3(edActvTsk)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP)
   {
      if (mBuf != (Buffer *)NULLP)
      {
         (Void)SPutMsg(mBuf);
      }
      RETVALUE(RFAILED);
   }
   if (mBuf == (Buffer *)NULLP)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;

  (Void)SExitTsk();
   RETVALUE(ROK);
} /* end of edActvTsk() */


/*
*
*       Fun:   cmXtaAppPyDeInit
*
*       Desc:  Python De-initialization
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_tst.c
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
}/* egacPyDeInit */

/********************************************************************30**

         End of file:     egac_edmtst.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:26 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
*********************************************************************91*/
