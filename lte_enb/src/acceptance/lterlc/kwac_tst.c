

/********************************************************************20**

     Name:    RLC - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    kwac_tst.c

     Sid:      kwac_tst.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:43 2014

     Prg:     cp 
*********************************************************************21*/


/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "kw_dl.h"
#include "kw_ul.h"
#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kw_udx.x"
#include "kw_dl.x"
#include "kw_ul.x"

#include <stdlib.h>
#include <string.h>

#ifdef CMXTA_MASTER
PUBLIC KwAcCb kwAcCb;
/*
EXTERN S16 kwAcCkwInit(Void);
EXTERN S16 kwAcKwuInit(Void);
EXTERN S16 kwAcLkwInit(Void);
EXTERN S16 kwAcRguInit(Void);
EXTERN S16 kwAcKwuDeInit(Void);
EXTERN S16 kwAcCkwDeInit(Void);
EXTERN S16 kwAcLkwDeInit(Void);
EXTERN S16 kwAcRguDeInit(Void);
*/



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
*       File:  kwac_tst.c
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
*ilps       File:  kwac_tst.c
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
   S16      ret = ROK;
   U8       ipType = 4; /* IPV4 = 4, IPV6 = 6 */

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
   rlInitLog(ipType);


   /*  Initialize the global structure   */
   cmMemset((U8 *)&kwAcCb, 0, sizeof(KwAcCb));

   /*-- CKW module init function --*/
   if ((ret = kwAcCkwInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- KWU module init function --*/
   if ((ret = kwAcKwuInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- LKW module init function --*/
   if ((ret = kwAcLkwInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- CMXTA_ENHANCE:  Put Init functions for rest of the
        modules here, this will happen only once --*/

   /*-- RGU module init function --*/
   if ((ret = kwAcRguInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

#ifdef KW_PDCP
   /*-- CPJ module init function --*/
   if ((ret = kwAcCpjInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- PJU module init function --*/
   if ((ret = kwAcPjuInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- LPJ module init function --*/
   if ((ret = kwAcLpjInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if ((ret = kwAcObdInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   kwAcCb.directive.numPosTc  =  0;
   kwAcCb.directive.numNegTc  =  0;
#endif /* KW_PDCP */
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
*       File:  kwac_tst.c
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
#ifdef KWAC_TC_SUMMARY
   Txt   buffer[100];
#endif /* KWAC_TC_SUMMARY */
   TRC2(cmXtaAppMasterDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterDeInit(): Shutting down the Test Architecture\n"));

   /*-- Opposite of the steps done in aqAcInit --*/

   /*-- Put DeInit functions for rest of the
        modules here, this will happen only once --*/

   /*-- KWU module deInit function --*/
   (Void)kwAcKwuDeInit();

   /*-- CKW module deInit function --*/
   (Void)kwAcCkwDeInit();

   /*-- LKW module deInit function --*/
   (Void)kwAcLkwDeInit();

   /*-- RGU module deInit function --*/
   (Void)kwAcRguDeInit();
#ifdef KW_PDCP

   /*-- CPJ module deInit function --*/
   (Void)kwAcCpjDeInit();

   /*-- PJU module deInit function --*/
   (Void)kwAcPjuDeInit();

   /*-- LPJ module deInit function --*/
   (Void)kwAcLpjDeInit();

#ifdef KWAC_TC_SUMMARY
   sprintf(buffer, "\n\nTESTCASES SUCCESS/FAILURE RESULT SUMMARY\n");
   SPrint(buffer);
   sprintf(buffer, "========================================\n");
   SPrint(buffer);
   sprintf(buffer, "\n\t\tNumber of TCs with success scenarios =  %d", kwAcCb.directive.numPosTc);
   SPrint(buffer);
   sprintf(buffer, "\n\t\tNumber of TCs with failure scenarios =  %d\n\n", kwAcCb.directive.numNegTc);
   SPrint(buffer);
#endif /* KWAC_TC_SUMMARY */
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
*      File : kwac_tst.c
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
            {
               /* we ignore the output specifier and specifiers used by TA command
                  line parser --*/
               break;
            }

         case 'd':
            {
               /*-- Set debug level --*/
               cmXtaCb.dbgMask = atoi(msOptArg);
               break;
            }

         case 'h':
            {
               /* help and unknown options display help message    */
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
               break;
            }

         case 'r':
            {
               /* Xta Proc Id */
               procId = atoi(msOptArg);
               break;
            }

         case '?':
         default:
            {
               /* help and unknown options display help message    */
               cmXtaMasterUsage();
               RETVALUE(RFAILED);
               break;
            }
      }
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
*      File : kwac_tst.c
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
   sprintf(pBuf, "RLC Split Architecture Note:\n============================\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-f mem_cfg.txt]  - Always run RLC acceptance test-suite with this\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t\t\t    option. It is required for \"AM Test Group\"\n");
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
*       File:  kwac_tst.c
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
/*Pradeep - added kwDlActvInit & kwUlActvInit*/
   kwDlActvInit(ENTKW, 0, 0, 0);
   kwUlActvInit(ENTKW, 1, 0, 0);
#ifdef KW_PDCP
   pjActvInit(ENTPJ, 0, 0, 0);
#endif /* KWPDCP */
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
*       File:  kwac_tst.c
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
*      File : kwac_tst.c
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
*      File : kwac_tst.c
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
*       File:  kwac_tst.c
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

   RETVALUE(ROK);
}/* cmXtaAppDirectiveInit */

#else /* SLAVE */

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
*       File:  kwac_slave.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppTst
(
Void
)
#else
PUBLIC S16 cmXtaAppTst()
#endif
{
   TRC2(cmXtaAppTst)

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTst */

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
*       File:  kwac_slave.c
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
   kwActvInit( ENTKW, 0, 0, 0 ) ;
#ifdef KW_PDCP
   pjActvInit(ENTPJ, 0, 0, 0);
#endif /* KWPDCP */

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
*       File:  kwac_slave.c
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
*      File : kwac_slave.c
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
*      File : kwac_slave.c
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
*       File:  tq_aghdlr.c
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

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppDirectiveInit(): Init\n"));
   RETVALUE(ROK);
}/* cmXtaAppDirectiveInit */
#endif /* CMXTA_MASTER */

/********************************************************************30**

         End of file:     kwac_tst.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:43 2014

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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
*********************************************************************91*/

