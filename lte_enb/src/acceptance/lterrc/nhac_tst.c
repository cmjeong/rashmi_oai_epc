/********************************************************************20**

     Name:    LTE-RRC 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_tst.c

     Sid:      nhac_tst.c@@/main/3 - Fri Jul  1 01:13:10 2011

     Prg:     rer 

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
/* external headers */


/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhac_asn.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "cm_tpt.h"

#include "nhac_acc.x"

#ifdef CMXTA_MASTER
   #include <Python.h>         
   #include "cm_xta_py.x"      
#endif

/*
*
*       Fun:   cmXtaAppLoadDeInit
*
*       Desc:  CM XTA APP Load De Init  function for acceptance test
*
*       Ret:   Void
*
*       Notes: None
*              
*       File:  nhac_tst.c
*
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

   RETVALUE(CMXTA_ERR_NONE);
}

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
*       File:  nhac_tst.c
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
   rlSetLogPath(".");
   rlSetLogFile("rrc_acc");
   rlSetLogLevel(L_DEBUG);
   rlInitLog(CM_TPTADDR_IPV4);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Initializing the Test Architecture\n"));
#ifndef SS_MULTIPLE_PROCS
   /* TBD -- take from RRC */
   nhActvInit(ENTNH, 0, 0, 0);
#else
   nhActvInit(CMXTA_PROC_ID,ENTNH, 0, 0, 10,&xxCb);
#endif

/* Initialize nhAccCb here */

   /*-- All module init function  TBD --*/
#ifdef CMXTA_MASTER
   if ((ret = nhAcCrgInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   if ((ret = nhAcKwuInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   if ((ret = nhAcCkwInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   if ((ret = nhAcNhuInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   if ((ret = nhAcLnhInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   if ((ret = nhAcCpjInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   if ((ret = nhAcPjuInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#ifdef RRC_PHY_CFG_SUPP
   if ((ret = nhAcCtfInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif
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
*       File:  nhac_tst.c
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

   /*-- Opposite of the steps done in nhAcInit --*/

   /*-- Put DeInit functions for rest of the
        modules here, this will happen only once --*/

   /*-- CMK module deInit function --*/
#ifdef CMXTA_MASTER
   (Void)nhAcCrgDeInit();
   (Void)nhAcCkwDeInit();
   (Void)nhAcKwuDeInit();
   (Void)nhAcCpjDeInit();
   (Void)nhAcPjuDeInit();
   (Void)nhAcCrgDeInit();
   (Void)nhAcNhuDeInit();
   (Void)nhAcLnhDeInit();
#ifdef RRC_PHY_CFG_SUPP
   (Void)nhAcCtfDeInit();
#endif
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
*      File : nhac_tst.c
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

   TRC2(cmXtaAppMasterParseCmdLine)
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
*      File : nhac_tst.c
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

   TRC2(cmXtaAppMasterUsage);
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
*       File:  nhac_tst.c
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
   nhActvInit(ENTNH, 0, 0, 0);
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
*       File:  nhac_tst.c
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
*      File : nhac_tst.c
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
*      File : nhac_tst.c
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
*       File:  nhac_tst.c
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


/********************************************************************30**

         End of file:     nhac_tst.c@@/main/3 - Fri Jul  1 01:13:10 2011

*********************************************************************31*/
/********************************************************************40**

        Notes:

*********************************************************************41*/
/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**

   ver       pat     init                  description
------------ --------  ---- ----------------------------------------------
/main/1      ---     rer              1. LTE RRC Initial Release.
/main/2      ---     chebli           1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
