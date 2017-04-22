
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_tst.c

     Sid:      egac_tst.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:41 2015

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

#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for S1AP */
#include "egac_acc.h"      /* defines for S1AP acceptance tests */

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
/*eg004.201 Modified for eGTP-C PSF Upgrade*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "hwac_acc.x" 
#endif
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for EG*/
#include "egac_acc.x"      /* typedefs for EG acceptance tests */
#include "egac_leg.x"
#include "egac_egt.x"
#include "egac_hit.x"

#include <stdlib.h>

/* ccpu00130610 */
Bool memAlarm = FALSE;

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
#ifdef EG_ACC_INT
   /*-- LHI module init function --*/
   if ((ret = egAcLhiInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif /* EG_ACC_INT */
   /*-- LEG module init function --*/
   if ((ret = egAcLegInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);



   /*-- HIT module init function --*/
   if ((ret = egAcHitInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- EGT module init function --*/
   if ((ret = egAcEgtInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   egAccCb.directives.xtaProcId =   EGAC_PROCID_SINGLE;
   egAccCb.directives.hiProcId  =   EGAC_PROCID_SINGLE;

/*eg004.201 Modified for eGTP-C PSF Upgrade:Call the PSF module Init functions*/
#ifdef HW
   /*-- eGTP-PSF module init function --*/
   if ((ret = hwAcLhwInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

      /*-- eGTP-PSF module init function --*/
   if ((ret = hwShtInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   

   /*-- MR module init function --*/
   if ((ret = hwMrInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif

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
   (Void)egAcEgtDeInit();

   /*-- HIT module deInit function --*/
   (Void)egAcHitDeInit();
   
   /*-- LEG module deInit function --*/
   (Void)egAcLegDeInit();

#ifdef EG_ACC_INT
   /*-- LHI module deInit function --*/
   (Void)egAcLhiDeInit();
#endif /* EG_ACC_INT */
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

   TRC2(cmXtaAppMasterUsage);

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
#ifndef SS_MULTIPLE_PROCS
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

         End of file:     egac_tst.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:41 2015

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
/main/2      ---      nkottapalli 1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3      eg004.201 magnihotri 1. Modified for eGTP-C PSF Upgrade:
                                     Call the PSF module Init functions
*********************************************************************91*/
