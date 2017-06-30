
/********************************************************************20**

     Name:    EGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_slave.c

     Sid:      egac_slave.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:41 2015

     Prg:     pc 

*********************************************************************21*/

/* header include files (.h) */
#include "egac_acc.x"

#include <stdlib.h>

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
Void
)
#else
PUBLIC S16 cmXtaAppTst()
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(cmXtaAppTst)

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
*       File:  tq_acc.c
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
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(cmXtaAppSlaveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Initializing the slave\n"));
#ifdef SS_MULTIPLE_PROCS
   egCbPtr = &egCbLst[0];
#else
   egActvInit( ENTEG, 0, 0, 0 );
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
*       File:  tq_acc.c
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
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(cmXtaAppSlaveDeInit)

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
*      File : tq_acc.c
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
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(cmXtaAppSlaveParseCmdLine)

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
*      File : tq_acc.c
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
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(cmXtaAppSlaveUsage);

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
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(cmXtaAppDirectiveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppDirectiveInit(): Init\n"));
   RETVALUE(ROK);
}/* cmXtaAppDirectiveInit */

/********************************************************************30**

         End of file:     egac_slave.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:41 2015

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
/main/3     eg003.201 psingh      1. Merged code from eg006.102 to Fix
                                     TRACE5 macro related issue
*********************************************************************91*/
