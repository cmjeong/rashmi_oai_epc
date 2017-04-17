
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_tst.c

     Sid:      szac_tst.c@@/main/4 - Mon Jan 10 22:16:05 2011

     Prg:     sn 
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

#include "szt.h"           /* SZT defines */
/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#include "lyt.h"
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for S1AP */
#include "sct.h"           /* SB (SCTP) layer */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_pasn.h"
#include "cm_xta.h"

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef    YT
#include "ytac_acc.h"
#endif    /* YT */
#include "sz.h"            /* defines and macros for S1AP */
#include "szac_acc.h"      /* defines for S1AP acceptance tests */
#include <stdlib.h>
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

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

#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Interface Structures */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SZT types */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#include "lyt.x"
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for S1AP */
#include "cm_xta.x"

#ifdef HI
#include "lhi.x"
#include "szac_lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "szac_lsb.x"
#endif    /* SB */

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef    YT
#include "ytac_acc.x"
#endif    /* YT */
#include "cm_pasn.x"
#include "sz.x"            /* typedefs for SZCP */
#include "szac_acc.x"        /* typedefs for SZCP acceptance tests */
#include "szac_lsz.x"
#include "szac_szt.x"

#ifdef DM
#include "szac_sct.x"
#endif /*DM*/



PUBLIC SzAccCb szAccCb;

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
*       File:  tq_acc.c
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

#ifdef CMXTA_MASTER
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
*ilps       File:  tq_acc.c
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

#ifdef HI
   /*-- HI module init function --*/
   if ((ret = szAcLhiInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif

   /*-- SB module init function --*/
#ifdef SB 
   if ((ret = szAcLsbInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif

   /*-- SZ  module init function --*/
   if ((ret = szAcLszInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- CMXTA_ENHANCE:  Put Init functions for rest of the
        modules here, this will happen only once --*/

#ifdef DM
   /*-- SCT module init function --*/
   if ((ret = szAcSctInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif /*DM*/

   /* sz003.301: Updted for PSF-S1AP 3.1 release. Added initialization
    * of YT commands */
#ifdef YT
   /* S1AP -PSF init function */
   if ((ret = ytAcLytInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif /*YT*/

   /*-- AQU module init function --*/
   if ((ret = szAcSztInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /* sz003.301: Updted for PSF-S1AP 3.1 release. Added initialization
    * of YT commands */
#ifdef YT_ACC
   /* S1AP -PSF init function */
   if ((ret = ytShtInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if ((ret = ytMrInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if ((ret = ytPitInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif /*YT_ACC*/

#ifdef CMXTA_FTHA_INTEGRATED
      if(( ret = cmXtaLsgInit()) != CMXTA_ERR_NONE)
      {
         RETVALUE(ret);
      }
      
      if(( ret = cmXtaLmrInit()) != CMXTA_ERR_NONE)
      {
         RETVALUE(ret);
      }
      
      if(( ret = cmXtaLshInit()) != CMXTA_ERR_NONE)
      {
         RETVALUE(ret);
      }
      
#endif

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Test Architecture Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterInit */


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

   /*-- AQU module deInit function --*/
   (Void)szAcSztDeInit();

#ifdef DM 

   /*-- SCT module deInit function --*/
#ifdef SB 
   (Void)szAcSctDeInit();
#endif /* end of SZ_SCTP */
#endif /*DM*/

   /*-- LAQ module deInit function --*/
   (Void)szAcLszDeInit();

   /*-- LSB module deInit function --*/
#ifdef SB
   (Void)szAcLsbDeInit();
#endif

#ifdef HI
   /*-- LHI module deInit function --*/
   (Void)szAcLhiDeInit();
#endif

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

         case 'r':
            /* Xta Proc Id */
            procId = atoi(msOptArg);
            szAccCb.directives.xtaProcId = procId;
            szAccCb.directives.eNbProcId = procId;
            szAccCb.directives.mmeProcId = procId;
            /* sz003.301: Updted for PSF-S1AP 3.1 release. Added standby and 
             * transport procId */
#ifdef SZ_FTHA
            szAccCb.directives.sbyProcId = procId;
            szAccCb.directives.tptProcId = procId;
#endif /* SZ_FTHA */
            break;

         case '?':
         default:
            /* help and unknown options display help message    */
            cmXtaMasterUsage();
            RETVALUE(RFAILED);
            break;
      }
   }

   szAccCb.directives.eNbIpAddr =   cmXtaCb.localIpcIpAddr; 
   szAccCb.directives.mmeIpAddr =   cmXtaCb.remoteIpcIpAddr;

   if((cmXtaCb.curTopId == 6))
   {
      szAccCb.directives.xtaProcId = CMXTA_PROCID_MASTER;
      szAccCb.directives.eNbIpAddr =   cmXtaCb.remoteIpcIpAddr; 
      szAccCb.directives.mmeIpAddr =   cmXtaCb.remoteIpcIpAddr;
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
*      File : aqac_tst.c
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
   sprintf(pBuf, "S1AP Options:\n============\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-d 0-9 dbgMask     ]   - Enable Debug Masks \n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-r xtaProcId       ]   - Set the xtaProcId\n");
   SPrint(pBuf);

   RETVOID;
} /* cmXtaAppMasterUsage */
#endif /* CMXTA_MASTER */

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
*       File:  aqac_tst.c
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
   szActvInit(ENTSZ, 0, 0, 0);
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
*       File:  aqac_tst.c
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
*      File : aqac_tst.c
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
*      File : aqac_tst.c
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
*       Desc:  Call handler for Command Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  aqac_tst.c
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

   /* sz003.301: Updted for PSF-S1AP 3.1 release. Added standby and 
    * transport procId */
#ifdef SS_MULTIPLE_PROCS
   szAccCb.directives.xtaProcId =   SZAC_PROCID_SINGLE;
   szAccCb.directives.eNbProcId =   SZAC_PROCID_SINGLE;
   szAccCb.directives.mmeProcId =   SZAC_PROCID_ONE;
   szAccCb.directives.sbyProcId =   SZAC_PROCID_THREE;
#endif /* SS_MULTIPLE_PROCS */
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Added standby and 
    * transport procId */
#ifdef SZAC_INTG_TEST
   szAccCb.directives.xtaProcId =   CMXTA_PROCID_MASTER;
   szAccCb.directives.eNbProcId =   CMXTA_PROCID_MASTER;
   szAccCb.directives.mmeProcId =   CMXTA_PROCID_SLAVE;
#ifdef SZ_FTHA
   szAccCb.directives.eNbProcId =   CMXTA_PROCID_SLAVE;
   szAccCb.directives.mmeProcId =   CMXTA_PROCID_SLAVE2;
   szAccCb.directives.sbyProcId =   CMXTA_PROCID_SLAVE4;
#endif /* SZ_FTHA */
#endif /* SZAC_INTG_TEST */
#ifdef CMXTA_FTHA_INTEGRATED
   szAccCb.directives.xtaProcId =   CMXTA_PROCID_MASTER;
   szAccCb.directives.eNbProcId =   CMXTA_PROCID_SLAVE1;
   szAccCb.directives.mmeProcId =   CMXTA_PROCID_SLAVE2;
   szAccCb.directives.sbyProcId =   CMXTA_PROCID_SLAVE4;
   szAccCb.directives.tptProcId =   CMXTA_PROCID_SLAVE3;
#endif /* CMXTA_FTHA_INTEGRATED */

   szAccCb.directives.eNbIpAddr =   cmXtaCb.localIpcIpAddr; 
   szAccCb.directives.mmeIpAddr =   cmXtaCb.remoteIpcIpAddr;

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
 *       File:   xx_sotutl.c
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
*       File:  ag_txn.c
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
   szAccCb.hitCb.nxtConnId = 0;
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
*       File:  aqac_py.c
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
}/* aqacPyInit */

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
*       File:  aqac_py.c
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
/********************************************************************30**

         End of file:     szac_tst.c@@/main/4 - Mon Jan 10 22:16:05 2011

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
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
