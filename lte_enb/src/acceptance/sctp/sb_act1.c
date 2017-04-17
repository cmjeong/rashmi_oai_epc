

/********************************************************************20**

     Name:     sb_act1.c - Acceptance Tests for the SCTP layer

     Type:     C source file

     Desc:     C code for acceptance tests test cases.
     Includes all the configuration tests.

     File:     sb_act1.c

     Sid:      sb_act1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:06 2015

     Prg:      nct

*********************************************************************21*/

/*

  sb_act1.c - Acceptance Tests for the SCTP layer

Following functions are provided in this file:
         tst                  - main test function

*/

/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000163                      SCTP layer
 */

 /* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS defines */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb_mtu.h"        /* MTU defines */
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */
#include "sb_acc.h"        /* defines for SCTP layer */



/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* common DNS */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_mtu.x"        /* MTU typedefs */
/* #include "sb.x"   */         /* SCTP internal typedefs */
#include "sb_acc.x"        /* defines for SCTP layer */


/* local defines */

/* local typedefs */

/* forward references */

PRIVATE  S16 sbTSapCfgTst   ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbGenCfgTst    ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbSctSapCfgTst ARGS((U8 curtstnum, S8 *numstr));
/* sb003.103 - addition - */
/* SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
PRIVATE  S16 sbPathProfCfgTst ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbDstAddrCfgTst ARGS((U8 curtstnum, S8 *numstr));
#endif

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */

/*
*       Fun:   sbC100_01
*
*       Desc:  Test case : C.100.01
*              Purpose   : Verify acceptance of the general configuration
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_01
(
Void
)
#else
PUBLIC   S16 sbC100_01(Void)
#endif
{
   U8          curtstnum;   /* number of the current test: eg. C.101.01 */

   TRC2(sbC100_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(curtstnum,"C.100.01");
   RETVALUE(ROK);
} /* end sbC100_01 */



/*
*       Fun:   sbC100_02
*
*       Desc:  Test case : C.100.02
*              Purpose   : Verify failure in configuration if the configuration
*              request header includes an invalid element
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC100_02
(
Void
)
#else
PUBLIC   S16 sbC100_02(Void)
#endif
{
#ifdef LCSMSBMILSB
   SctStatus      status;
   Reason      reason;
#endif
   U8          curtstnum;

   TRC2(sbC100_02)

#ifdef LCSMSBMILSB
   if (sbAccCb.tcFlg == FALSE)
   {
      /* this is a hack :) */
      sbAccCb.testsRun--;
      sbAccCb.testsFail--;

      reason = 0;
      status = NO_LCTEST;
      sbAccDispErrTstRslt("C.100.02", 0, ACC_EVT_CFG_CFM, status, reason);
      sbAccCb.curTst.bTestsCompleted = TRUE;
      SB_CLEAN()
   }
   else
   {
      curtstnum = 2;
      sbAccCb.curTst.numSubTst  = 2;
      sbGenCfgTst(curtstnum,"C.100.02");
   }

#else
   curtstnum = 2;
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(curtstnum,"C.100.02");
#endif /* end LCSMSBMILSB */

   RETVALUE(ROK);
} /* end sbC100_02 */



/*
*       Fun:   sbC100_03
*
*       Desc:  Test case : C.100.03
*              Purpose   : Verify that 0 maxNmbSctSaps is not allowed in General Configuration
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_03
(
Void
)
#else
PUBLIC   S16 sbC100_03(Void)
#endif
{
   TRC2(sbC100_03)
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(3, "C.100.03");
   RETVALUE(ROK);
} /* end sbC100_03 */


/*
*       Fun:   sbC100_04
*
*       Desc:  Test case : C.100.04
*              Purpose   : Verify that 0 maxNmbTSaps is not allowed in General Configuration
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_04
(
void
)
#else
PUBLIC   S16 sbC100_04(void)
#endif
{
   TRC2(sbC100_04)
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(4, "C.100.04");
   RETVALUE(ROK);
} /* end sbC100_04 */


/*
*       Fun:   sbC100_05
*
*       Desc:  Test case : C.100.05
*              Purpose   : Verify that 0 maxNmbAssoc is not allowed in General Configuration
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_05
(
void
)
#else
PUBLIC   S16 sbC100_05(void)
#endif
{
   TRC2(sbC100_05)
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(5, "C.100.05");
   RETVALUE(ROK);
} /* end sbC100_05 */


/*
*       Fun:   sbC100_06
*
*       Desc:  Test case : C.100.06
*              Purpose   : Verify that 0 maxNmbEndp is not allowed in General Configuration
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_06
(
void
)
#else
PUBLIC   S16 sbC100_06(void)
#endif
{
   TRC2(sbC100_06)
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(6, "C.100.06");
   RETVALUE(ROK);
} /* end sbC100_06 */


/*
*       Fun:   sbC100_07
*
*       Desc:  Test case : C.100.07
*              Purpose   : Verify that 0 timeRes is not allowed in General Configuration
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_07
(
void
)
#else
PUBLIC   S16 sbC100_07(void)
#endif
{
   TRC2(sbC100_07)
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(7, "C.100.07");
   RETVALUE(ROK);
} /* end sbC100_07 */


/*
*       Fun:   sbC100_08
*
*       Desc:  Test case : C.100.08
*              Purpose   : Verify that 0 maxNmbTxChunks is not allowed in General Configuration
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_08
(
void
)
#else
PUBLIC   S16 sbC100_08(void)
#endif
{
   TRC2(sbC100_08)
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(8, "C.100.08");
   RETVALUE(ROK);
} /* end sbC100_08 */


/*
*       Fun:   sbC100_09
*
*       Desc:  Test case : C.100.09
*              Purpose   : Verify that 0 maxNmbRxChunks is not allowed in General Configuration
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_09
(
void
)
#else
PUBLIC   S16 sbC100_09(void)
#endif
{
   TRC2(sbC100_03)
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(9, "C.100.09");
   RETVALUE(ROK);
} /* end sbC100_09 */


/*  sb032.102 : IPV6 Support Added */
/*
*       Fun:   sbC100_10
*
*       Desc:  Test case : C.100.10
*              Purpose   : Verify that ipv6SrcvReqdFlg can either be TRUE or
*                          FLASE 
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbC100_10
(
void
)
#else
PUBLIC   S16 sbC100_10(void)
#endif
{
   TRC2(sbC100_10)
   sbAccCb.curTst.numSubTst  = 2;
   sbGenCfgTst(10, "C.100.10");
   RETVALUE(ROK);
} /* end sbC100_10 */
/*
*       Fun:   sbC101_01
*
*       Desc:  Test case : C.101.01
*              Purpose   : Verify failure in configuration if it does not follow on a
*                         successful general configuration request.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC101_01
(
void
)
#else
PUBLIC   S16 sbC101_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.01 */

   TRC2(sbC101_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(curtstnum,"C.101.01");
   RETVALUE(ROK);
} /* end sbC101_01 */

/*
*       Fun:   sbC101_02
*
*       Desc:  Test case : C.101.02
*              Purpose   : Verify failure in configuration if the configuration
*              request header includes an invalid element
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC101_02
(
void
)
#else
PUBLIC   S16 sbC101_02(void)
#endif
{

#ifdef LCSMSBMILSB
   SctStatus   status;
   Reason      reason;
#endif
   U8          curtstnum;   /* number of the current test: eg. C.101.02 */

   TRC2(sbC101_02)
#ifdef LCSMSBMILSB
   if ( sbAccCb.tcFlg == FALSE )
   {
      /* this is a hack :) */
      sbAccCb.testsRun--;
      sbAccCb.testsFail--;

      reason = 0;
      status = NO_LCTEST;
      sbAccDispErrTstRslt("C.101.02", 0, ACC_EVT_CFG_CFM, status, reason);
      sbAccCb.curTst.bTestsCompleted = TRUE;
      SB_CLEAN()
   }
   else
   {
      curtstnum = 2;
      sbAccCb.curTst.numSubTst  = 2;
      sbSctSapCfgTst(curtstnum,"C.101.02");
   }

#else
   curtstnum = 2;
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(curtstnum,"C.101.02");
#endif /* end LCSMSBMILSB */
   RETVALUE(ROK);
} /* end sbC101_02 */


/*
*       Fun:   sbC101_03
*
*       Desc:  Test case : C.101.03
*              Purpose   : Verify acceptance of standard configuration (for SAP1,
*                          SAP2, SAP3)
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_03
(
void
)
#else
PUBLIC   S16 sbC101_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.01 */

   TRC2(sbC101_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(curtstnum, "C.101.03");
   RETVALUE(ROK);
} /* end sbC101_03 */


/*
*       Fun:   sbC101_04
*
*       Desc:  Test case : C.101.04
*              Purpose   : Verify that only LSB_IETF_99 is accepted as a valid swtch
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_04
(
void
)
#else
PUBLIC   S16 sbC101_04(void)
#endif
{
   TRC2(sbC101_04)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(4, "C.101.04");
   RETVALUE(ROK);
} /* end sbC101_04 */


/*
*       Fun:   sbC101_05
*
*       Desc:  Test case : C.101.05
*              Purpose   : Range check that spId < maxNmbSctSaps
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_05
(
void
)
#else
PUBLIC   S16 sbC101_05(void)
#endif
{
   TRC2(sbC101_05)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(5, "C.101.05");
   RETVALUE(ROK);
} /* end sbC101_05 */


/*
*       Fun:   sbC101_06
*
*       Desc:  Test case : C.101.06
*              Purpose   : Range check that cookieLife must be > 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_06
(
void
)
#else
PUBLIC   S16 sbC101_06(void)
#endif
{
   TRC2(sbC101_06)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(6, "C.101.06");
   RETVALUE(ROK);
} /* end sbC101_06 */


/*
*       Fun:   sbC101_07
*
*       Desc:  Test case : C.101.07
*              Purpose   : Range check that maxAckDelayTm must be > 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_07
(
void
)
#else
PUBLIC   S16 sbC101_07(void)
#endif
{
   TRC2(sbC101_07)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(7, "C.101.07");
   RETVALUE(ROK);
} /* end sbC101_07 */

/*
*       Fun:   sbC101_08
*
*       Desc:  Test case : C.101.08
*              Purpose   : Range check that maxAckDelayDg must be > 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_08
(
void
)
#else
PUBLIC   S16 sbC101_08(void)
#endif
{
   TRC2(sbC101_08)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(8, "C.101.08");
   RETVALUE(ROK);
} /* end sbC101_08 */

/*
*       Fun:   sbC101_09
*
*       Desc:  Test case : C.101.09
*              Purpose   : Range check that rtoMin must be > 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_09
(
void
)
#else
PUBLIC   S16 sbC101_09(void)
#endif
{
   TRC2(sbC101_09)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(9, "C.101.09");
   RETVALUE(ROK);
} /* end sbC101_09 */

/*
*       Fun:   sbC101_10
*
*       Desc:  Test case : C.101.10
*              Purpose   : Range check that freezeTm must be > 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_10
(
void
)
#else
PUBLIC   S16 sbC101_10(void)
#endif
{
   TRC2(sbC101_10)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(10, "C.101.10");
   RETVALUE(ROK);
} /* end sbC101_10 */

/*
*       Fun:   sbC101_11
*
*       Desc:  Test case : C.101.11
*              Purpose   : Range check that rtoInitial must be > 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_11
(
void
)
#else
PUBLIC   S16 sbC101_11(void)
#endif
{
   TRC2(sbC101_11)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(11, "C.101.11");
   RETVALUE(ROK);
} /* end sbC101_11 */

/*
*       Fun:   sbC101_12
*
*       Desc:  Test case : C.101.12
*              Purpose   : Range check that intervalTm must be > 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_12
(
void
)
#else
PUBLIC   S16 sbC101_12(void)
#endif
{
   TRC2(sbC101_12)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(12, "C.101.12");
   RETVALUE(ROK);
} /* end sbC101_12 */

/*
*       Fun:   sbC101_13
*
*       Desc:  Test case : C.101.13
*              Purpose   : Range check that rtoMax must be > 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/


#ifdef ANSI
PUBLIC   S16 sbC101_13
(
void
)
#else
PUBLIC   S16 sbC101_13(void)
#endif
{
   TRC2(sbC101_13)
   sbAccCb.curTst.numSubTst  = 2;
   sbSctSapCfgTst(13, "C.101.13");
   RETVALUE(ROK);
} /* end sbC101_13 */

/*
*       Fun:   sbC102_01
*
*       Desc:  Test case : C.102.01
*              Purpose   : Verify failure in configuration if it does not follow on a
 *                         successful general configuration request.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC102_01
(
void
)
#else
PUBLIC   S16 sbC102_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.01 */

   TRC2(sbC102_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst  = 2;
   sbTSapCfgTst(curtstnum,"C.102.01");
   RETVALUE(ROK);
} /* end sbC102_01 */

/*
*       Fun:   sbC102_02
*
*       Desc:  Test case : C.102.02
*              Purpose   : Verify failure in configuration if the configuration
*              request header includes an invalid element
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC102_02
(
void
)
#else
PUBLIC   S16 sbC102_02(void)
#endif
{
#ifdef LCSMSBMILSB
   SctStatus      status;
   Reason      reason;
#endif
   U8          curtstnum;           /* number of the current test: eg. C.101.01 */

   TRC2(sbC102_02)

#ifdef LCSMSBMILSB
   if ( sbAccCb.tcFlg == FALSE )
   {
      /* this is a hack :) */
      sbAccCb.testsRun--;
      sbAccCb.testsFail--;

      reason = 0;
      status = NO_LCTEST;
      sbAccDispErrTstRslt("C.102.02", 0, ACC_EVT_CFG_CFM, status, reason);
      sbAccCb.curTst.bTestsCompleted = TRUE;
      SB_CLEAN()
   }
   else
   {
      curtstnum = 2;
      sbAccCb.curTst.numSubTst  = 2;
      sbTSapCfgTst(curtstnum,"C.102.02");
   }

#else
   curtstnum = 2;
   sbAccCb.curTst.numSubTst  = 2;
   sbTSapCfgTst(curtstnum,"C.102.02");
#endif /* end LCSMSBMILSB */
   RETVALUE(ROK);
} /* end sbC102_02 */


/*
*       Fun:   sbC102_03
*
*       Desc:  Test case : C.102.03
*              Purpose   : Verify acceptance of standard configuration (for TSAP1,
*                          TSAP2, TSAP3)
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC102_03
(
void
)
#else
PUBLIC   S16 sbC102_03(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.01 */

   TRC2(sbC102_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst  = 2;
   sbTSapCfgTst(curtstnum,"C.102.03");
   RETVALUE(ROK);
} /* end sbC102_03 */


/*  sb032.102 : IPV6 Support Added */
/*
*       Fun:   sbC102_08
*
*       Desc:  Test case : C.102.08
*              Purpose   : Verify acceptance of standard configuration (for TSAP1,
*                          TSAP2, TSAP3 for IPV6 addresses)
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC102_08
(
void
)
#else
PUBLIC   S16 sbC102_08(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.01 */

   TRC2(sbC102_08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst  = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbTSapCfgTst(curtstnum,"C.102.08");
   RETVALUE(ROK);
} /* end sbC102_03 */

/*
*       Fun:   sbC102_04
*
*       Desc:  Test case : C.102.04
*              Purpose   : Verify that only LSB_IETF_99 is a valid value
*                          for swtch
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC102_04
(
void
)
#else
PUBLIC   S16 sbC102_04(void)
#endif
{

   TRC2(sbC102_04)
   sbAccCb.curTst.numSubTst  = 2;
   sbTSapCfgTst(4,"C.102.04");
   RETVALUE(ROK);
} /* end sbC102_04 */



/*
*       Fun:   sbC102_05
*
*       Desc:  Test case : C.102.05
*              Purpose   : Verify range checking for suId
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC102_05
(
void
)
#else
PUBLIC   S16 sbC102_05(void)
#endif
{

   TRC2(sbC102_05)
   sbAccCb.curTst.numSubTst  = 2;
   sbTSapCfgTst(5,"C.102.05");
   RETVALUE(ROK);
} /* end sbC102_05 */

/*
*       Fun:   sbC102_06
*
*       Desc:  Test case : C.102.06
*              Purpose   : : Verify range checking for tIntTmr
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC102_06
(
void
)
#else
PUBLIC   S16 sbC102_06(void)
#endif
{

   TRC2(sbC102_06)
   sbAccCb.curTst.numSubTst  = 2;
   sbTSapCfgTst(6,"C.102.06");
   RETVALUE(ROK);
} /* end sbC102_06 */


/*
*       Fun:   sbC102_07
*
*       Desc:  Test case : C.102.07
*              Purpose   : Verify range checking for maxBndRetry.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC102_07
(
void
)
#else
PUBLIC   S16 sbC102_07(void)
#endif
{

   TRC2(sbC102_07)
   sbAccCb.curTst.numSubTst  = 2;
   sbTSapCfgTst(7,"C.102.07");
   RETVALUE(ROK);
} /* end sbC102_07 */

/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
/*
*       Fun:   sbC103_01
*
*       Desc:  Test case : C.103.01
*              Purpose   : Verify failure in Path Profile configuration if it
*                          does not follow on a successful general configuration
*                          request.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_01
(
void
)
#else
PUBLIC   S16 sbC103_01(void)
#endif
{

   TRC2(sbC103_01)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(1,"C.103.01");
   RETVALUE(ROK);
} /* end sbC103_01 */

/*
*       Fun:   sbC103_02
*
*       Desc:  Test case : C.103.02
*              Purpose   : Verify acceptance of standard configuration.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_02
(
void
)
#else
PUBLIC   S16 sbC103_02(void)
#endif
{

   TRC2(sbC103_02)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(2,"C.103.02");
   RETVALUE(ROK);
} /* end sbC103_02 */

/*
*       Fun:   sbC103_03
*
*       Desc:  Test case : C.103.03
*              Purpose   : Verify that profId is less thean maxNmbPathProfs
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_03
(
void
)
#else
PUBLIC   S16 sbC103_03(void)
#endif
{

   TRC2(sbC103_03)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(3,"C.103.03");
   RETVALUE(ROK);
} /* end sbC103_03 */

/*
*       Fun:   sbC103_04
*
*       Desc:  Test case : C.103.04
*              Purpose   : Verify that value of initCwnd in Config. Reg is greater
*                          than 0. 
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_04
(
void
)
#else
PUBLIC   S16 sbC103_04(void)
#endif
{

   TRC2(sbC103_04)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(4,"C.103.04");
   RETVALUE(ROK);
} /* end sbC103_04 */

/*
*       Fun:   sbC103_05
*
*       Desc:  Test case : C.103.05
*              Purpose   : Verify that value of initSsthresh in config req is 
*                          greater than 0
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_05
(
void
)
#else
PUBLIC   S16 sbC103_05(void)
#endif
{

   TRC2(sbC103_05)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(5,"C.103.05");
   RETVALUE(ROK);
} /* end sbC103_05 */

/*
*       Fun:   sbC103_06
*
*       Desc:  Test case : C.103.06
*              Purpose   : Verify that value of rtoInitial in config req is 
*                          greater than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_06
(
void
)
#else
PUBLIC   S16 sbC103_06(void)
#endif
{

   TRC2(sbC103_06)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(6,"C.103.06");
   RETVALUE(ROK);
} /* end sbC103_06 */

/*
*       Fun:   sbC103_07
*
*       Desc:  Test case : C.103.07
*              Purpose   : Verify that value of rtoMin in Config. Reg is greater
*                          than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_07
(
void
)
#else
PUBLIC   S16 sbC103_07(void)
#endif
{

   TRC2(sbC103_07)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(7,"C.103.07");
   RETVALUE(ROK);
} /* end sbC103_07 */

/*
*       Fun:   sbC103_08
*
*       Desc:  Test case : C.103.08
*              Purpose   : Verify that value of rtoMax in Config. Reg is greater
*                          than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_08
(
void
)
#else
PUBLIC   S16 sbC103_08(void)
#endif
{

   TRC2(sbC103_08)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(8,"C.103.08");
   RETVALUE(ROK);
} /* end sbC103_08 */

/*
*       Fun:   sbC103_09
*
*       Desc:  Test case : C.103.9
*              Purpose   : Verify that value of alpha in Config. Reg is greater
*                          than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_09
(
void
)
#else
PUBLIC   S16 sbC103_09(void)
#endif
{

   TRC2(sbC103_09)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(9,"C.103.09");
   RETVALUE(ROK);
} /* end sbC103_09 */

/*
*       Fun:   sbC103_10
*
*       Desc:  Test case : C.103.10
*              Purpose   : Verify that value of beta in Config. Reg is greater
*                          than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_10
(
void
)
#else
PUBLIC   S16 sbC103_10(void)
#endif
{

   TRC2(sbC103_10)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(10,"C.103.10");
   RETVALUE(ROK);
} /* end sbC103_10 */

/*
*       Fun:   sbC103_11
*
*       Desc:  Test case : C.103.11
*              Purpose   : Verify that value of intervalTm in Config. Reg is greater
*                          than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_11
(
void
)
#else
PUBLIC   S16 sbC103_11(void)
#endif
{

   TRC2(sbC103_11)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(11,"C.103.11");
   RETVALUE(ROK);
} /* end sbC103_11 */

/*
*       Fun:   sbC103_12
*
*       Desc:  Test case : C.103.12
*              Purpose   : Verify that value of intervalTm in Config. Reg is greater
*                          than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_12
(
void
)
#else
PUBLIC   S16 sbC103_12(void)
#endif
{

   TRC2(sbC103_12)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(12,"C.103.12");
   RETVALUE(ROK);
} /* end sbC103_12 */

/*
*       Fun:   sbC103_13
*
*       Desc:  Test case : C.103.13
*              Purpose   : Verify that value of bc1 in Config. Reg is greater
*                          than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_13
(
void
)
#else
PUBLIC   S16 sbC103_13(void)
#endif
{

   TRC2(sbC103_13)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(13,"C.103.13");
   RETVALUE(ROK);
} /* end sbC103_13 */

/*
*       Fun:   sbC103_14
*
*       Desc:  Test case : C.103.14
*              Purpose   : Verify that value of idleCwndRate in Config. Reg is 
                           <= 100 and >=0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_14
(
void
)
#else
PUBLIC   S16 sbC103_14(void)
#endif
{

   TRC2(sbC103_14)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(14,"C.103.14");
   RETVALUE(ROK);
} /* end sbC103_14 */

/*
*       Fun:   sbC103_15
*
*       Desc:  Test case : C.103.15
*              Purpose   : Verify that value of frCwndRate in Config. Reg is
*                          <=100 and >=0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_15
(
void
)
#else
PUBLIC   S16 sbC103_15(void)
#endif
{

   TRC2(sbC103_15)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(15,"C.103.15");
   RETVALUE(ROK);
} /* end sbC103_15 */

/*
*       Fun:   sbC103_16
*
*       Desc:  Test case : C.103.16
*              Purpose   : Verify that value of rtrCwndRate in Config. Reg is
*                          <=100 and >=0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_16
(
void
)
#else
PUBLIC   S16 sbC103_16(void)
#endif
{

   TRC2(sbC103_16)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(16,"C.103.16");
   RETVALUE(ROK);
} /* end sbC103_16 */

/*
*       Fun:   sbC103_17
*
*       Desc:  Test case : C.103.17
*              Purpose   : Verify that value of maxPathReTx in Config. Reg is greater
*                          than 0.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC103_17
(
void
)
#else
PUBLIC   S16 sbC103_17(void)
#endif
{

   TRC2(sbC103_17)
   sbAccCb.curTst.numSubTst  = 2;
   sbPathProfCfgTst(17,"C.103.17");
   RETVALUE(ROK);
} /* end sbC103_17 */

/*
*       Fun:   sbC104_01
*
*       Desc:  Test case : C.104.01
*              Purpose   : Verify that Destination Address config fails if not
*                          followed by successful general configuration and path
*                          configuration.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC104_01
(
void
)
#else
PUBLIC   S16 sbC104_01(void)
#endif
{

   TRC2(sbC104_01)
   sbAccCb.curTst.numSubTst  = 2;
   sbDstAddrCfgTst(1,"C.104.01");
   RETVALUE(ROK);
} /* end sbC104_01 */

/*
*       Fun:   sbC104_02
*
*       Desc:  Test case : C.104.02
*              Purpose   : Verify that standard configuration is accepted.
*
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/

#ifdef ANSI
PUBLIC   S16 sbC104_02
(
void
)
#else
PUBLIC   S16 sbC104_02(void)
#endif
{

   TRC2(sbC104_02)
   sbAccCb.curTst.numSubTst  = 2;
   sbDstAddrCfgTst(2,"C.104.02");
   RETVALUE(ROK);
} /* end sbC104_02 */
#endif /* SB_SATELLITE */

/*
*       Fun:   sbGenCfgTst
*
*       Desc:   The general configuration tests
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbGenCfgTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.100.curtstnum) */
S8   *numstr        /* test number */
)
#else
PRIVATE  S16 sbGenCfgTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   PRIVATE     SbMgmtQElm  mgmt;
   PRIVATE     SbMgmt      sbMgmt;
   SctStatus   status;
   Reason      reason;
   S16         ret;

   TRC2(sbGenCfgTst)

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;
   if (sbAccCb.curTst.bBusyPreTestConf == TRUE)
   { /* No pre-test setup */
      if (curtstnum <= 2)
      {
         SB_GENCFG()
         if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
         {
            SB_ENABLE_DEBUGP(0xffffffff)
            SB_ENTERTEST(sbAccCb.curTst.bDebugPMask, BIT0 )
         }
      }
      else
      {
         sbAccCb.curTst.bBusySubtest = TRUE;        /* Now a test */
         sbAccCb.curTst.bBusyPreTestConf = FALSE;   /* Done with pre-test setup */
      }
   }
   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)
      {
         /* Send CfgReq */
         case 0:
            /* set configuration parameters */
            sbStdGenCfg(&sbMgmt);
            switch(curtstnum)
            {
               case 1: /* C.100.01: Execution */
                  sbMgmt.hdr.transId = 10001;
                  break;
               case 2:   /* C.100.02: Execution */
                  sbMgmt.hdr.transId = 10002;
                  sbMgmt.hdr.elmId.elmnt = HDR_ERR;
                  break;
               case 3:   /* C.100.03: Execution */
                  sbMgmt.hdr.transId = 10003;
                  sbMgmt.t.cfg.s.genCfg.maxNmbSctSaps = 0;
                  break;
               case 4:   /* C.100.04: Execution */
                  sbMgmt.hdr.transId = 10004;
                  sbMgmt.t.cfg.s.genCfg.maxNmbTSaps = 0;
                  break;
               case 5:   /* C.100.05: Execution */
                  sbMgmt.hdr.transId = 10005;
                  sbMgmt.t.cfg.s.genCfg.maxNmbAssoc = 0;
                  break;
               case 6:   /* C.100.06: Execution */
                  sbMgmt.hdr.transId = 10006;
                  sbMgmt.t.cfg.s.genCfg.maxNmbEndp = 0;
                  break;
               case 7:   /* C.100.07: Execution */
                  sbMgmt.hdr.transId = 10007;
                  sbMgmt.t.cfg.s.genCfg.timeRes = 0;
                  break;
               case 8:   /* C.100.08: Execution */
                  sbMgmt.hdr.transId = 10008;
                  sbMgmt.t.cfg.s.genCfg.maxNmbTxChunks = 0;
                  break;
               case 9:   /* C.100.09: Execution */
                  sbMgmt.hdr.transId = 10009;
                  sbMgmt.t.cfg.s.genCfg.maxNmbRxChunks = 0;
                  break;
/*  sb032.102 : IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
               case 10:   /* C.100.10: Execution */
                  sbMgmt.hdr.transId = 10010;
                  sbMgmt.t.cfg.s.genCfg.ipv6SrvcReqdFlg = 5;
                  break;
#endif
            }
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.state++;
            break;
         /* Dequeue CfgCfm and confirm status */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   ACC_EVT_CFG_CFM, TIMEOUT_ON_PRIM, 0);
            }
            else
            {
               /* fill the mgmt */
             switch(curtstnum)
             {
             case 1:    /* Test C.100.01: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                break;
             case 2:     /* Test C.100.02: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_ELMNT;
                break;
             case 3:     /* Test C.100.03: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
             case 4:     /* Test C.100.04: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
             case 5:     /* Test C.100.05: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
             case 6:     /* Test C.100.06: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
             case 7:     /* Test C.100.07: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
/*  sb032.102 : IPV6 Support Added */
             case 8:     /* Test C.100.08: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
             case 9:     /* Test C.100.09: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
             case 10:     /* Test C.100.10: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                break;

             }
               mgmt.transId = sbAccCb.curTst.curTransId;
               ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM);
               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       ACC_EVT_CFG_CFM, status, reason);
               }
               else
                 sbAccCb.curTst.subTestsPass++;
            } /* end primitive received */
            sbAccCb.curTst.state++;
            sbAccCb.curTst.subTest++;
            break;
         case 2: /* Do cleanup before next test */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;/* Done with a test/subtest*/
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
               if(curtstnum > 2)
                  sbAccCb.curTst.bConfigDeleted = TRUE;

            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;
      } /* end switch */
   } /* end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbGenCfgTst */

/*
*       Fun:   sbSctSapCfgTst
*
*       Desc:   The sctSap configuration tests
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctSapCfgTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.101.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctSapCfgTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   PRIVATE     SbMgmtQElm  mgmt;
   PRIVATE     SbMgmt      sbMgmt;
   SctStatus   status;
   Reason      reason;
   S16         ret;

   TRC2(sbSctSapCfgTst)
   ret = ROK;
   reason = LCM_REASON_NOT_APPL;


  /* Check for gen config */
  if( (sbAccCb.curTst.bBusyPreTestConf == TRUE)  )  /* cleanup has been performed */
  {
     if ( curtstnum!=1)
     {
        SB_GENCFG()
        if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
        {
           sbAccCb.curTst.bBusySubtest = TRUE;       /* Now do a test */
           sbAccCb.curTst.bBusyPreTestConf = FALSE;  /* Done with pre-test setup */
        }
     }
     else
     {
         sbAccCb.curTst.bBusySubtest = TRUE;       /* Now do a test */
         sbAccCb.curTst.bBusyPreTestConf = FALSE;  /* Done with pre-test setup */
     }
  }

  /* Do test */
  if (sbAccCb.curTst.bBusySubtest)
  {
     switch(sbAccCb.curTst.state)
     {
        /* Send CfgReq */
        case 0:
           /* set configuration parameters */
           sbStdSctSapCfg(&sbMgmt, SAP_1);
           switch(curtstnum)
           {
              case 1:
                 sbMgmt.hdr.transId = 10101;
                 break;
              case 2:  /* Execution of C.101.02 */
                 sbMgmt.hdr.elmId.elmnt = HDR_ERR;
                 sbMgmt.hdr.transId = 10102;
                 break;
              case 3:
                 sbMgmt.hdr.transId = 10103;
                 break;
              case 4:
                 sbMgmt.hdr.transId = 10104;
                 sbMgmt.t.cfg.s.sctSapCfg.swtch = (U8)(LSB_SW_RFC_REL0+1);
                 break;
              case 5:
                 sbMgmt.hdr.transId = 10105;
                 sbMgmt.t.cfg.s.sctSapCfg.spId = 0xfff;
                 break;
              case 6:
                 sbMgmt.hdr.transId = 10106;
                 sbMgmt.t.cfg.s.sctSapCfg.reConfig.cookieLife = 0;
                 break;
              case 7:
                 sbMgmt.hdr.transId = 10107;
                 sbMgmt.t.cfg.s.sctSapCfg.reConfig.maxAckDelayTm = 0;
                 break;
              case 8:
                 sbMgmt.hdr.transId = 10108;
                 sbMgmt.t.cfg.s.sctSapCfg.reConfig.maxAckDelayDg = 0;
                 break;
              case 9:
                 sbMgmt.hdr.transId = 10109;
                 sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin = 0;
                 break;
              case 10:
                 sbMgmt.hdr.transId = 10110;
                 sbMgmt.t.cfg.s.sctSapCfg.reConfig.freezeTm = 0;
                 break;
              case 11:
                 sbMgmt.hdr.transId = 10111;
                 sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial = 0;
                 break;
              case 12:
                 sbMgmt.hdr.transId = 10112;
                 sbMgmt.t.cfg.s.sctSapCfg.reConfig.intervalTm = 0;
                 break;
              case 13:
                 sbMgmt.hdr.transId = 10113;
                 sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax = 0;
                 break;
           }
           sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
           (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
           sbAccCb.curTst.state++;
           break;
        case 1:/* Dequeue CfgCfm and confirm status */
           sbAccVfyMsg(&status);
           if(status == WAIT)
           {   /* wait for message to reach the queue */
              RETVALUE(ROK);
           }
           else if(status == TIMEOUT)
           {
              sbAccCb.curTst.subTestsFail++;
              sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   ACC_EVT_CFG_CFM, TIMEOUT_ON_PRIM, 0);
           }
           else
           { /* primitive received */
              /* fill the mgmt */
              switch(curtstnum)
              {
              case 1:    /* Test C.101.01: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
                 break;
              case 2:     /* Test C.101.02: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_ELMNT;
                 break;
              case 3:      /* Test C.101.03: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_OK;
                 mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                 break;
              case 4:      /* Test C.101.04: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                 break;
              case 5:      /* Test C.101.05: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                 break;
              case 6:      /* Test C.101.06: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                 break;
              case 7:      /* Test C.101.07: Expected Results  */
                 /* sb018.103: maxAckDelayTm value can be zero */
                 mgmt.cfm.status = LCM_PRIM_OK;
                 mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                 break;
              case 8:      /* Test C.101.08: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                 break;
              case 9:      /* Test C.101.09: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                 break;
              case 10:      /* Test C.101.10: Expected Results  */
                 /* patch sb034.102 : changes to support change in patch sb028.102 */
                 mgmt.cfm.status = LCM_PRIM_OK;
                 mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                 break;
              case 11:      /* Test C.101.11: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                 break;
              case 12:      /* Test C.101.12: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                 break;
              case 13:      /* Test C.101.13: Expected Results  */
                 mgmt.cfm.status = LCM_PRIM_NOK;
                 mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                 break;
              }
              mgmt.transId = sbAccCb.curTst.curTransId;
              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM );
              if(ret == RFAILED)
              {
                 sbAccCb.curTst.subTestsFail++;
                 sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       ACC_EVT_CFG_CFM, status, reason);
              }
              else
              {
                 sbAccCb.curTst.subTestsPass++;
              }
           }   /*end primitive received */
           sbAccCb.curTst.state++;
           sbAccCb.curTst.subTest++;
           break;
        case 2: /* Do cleanup before next test */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
               {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE; /* Done with a test*/
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
               if(curtstnum == 1)
                  sbAccCb.curTst.bConfigDeleted = TRUE;
               }
               sbAccCb.curTst.state = 0;   /* For delete config to work */
               break;
     } /* end switch */
  } /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbSctSapCfgTst */


/*
*       Fun:   sbTSapCfgTst
*
*       Desc:   The tSap configuration tests
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbTSapCfgTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.101.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbTSapCfgTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   PRIVATE        SbMgmtQElm      mgmt;
   PRIVATE        SbMgmt          sbMgmt;
   SctStatus      status;
   Reason         reason;
   S16            ret;

   /* Check for gen config */

   TRC2(sbTSapCfgTst);
   ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   if( (sbAccCb.curTst.bBusyPreTestConf == TRUE)  )  /* cleanup has been performed */
   {
     if ( curtstnum!=1)
     {
        SB_GENCFG()
        if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
        {
           sbAccCb.curTst.bBusySubtest = TRUE;       /* Now do a test */
           sbAccCb.curTst.bBusyPreTestConf = FALSE;  /* Done with pre-test setup */
        }
     }
     else
     {
         sbAccCb.curTst.bBusySubtest = TRUE;       /* Now do a test */
         sbAccCb.curTst.bBusyPreTestConf = FALSE;  /* Done with pre-test setup */
     }

   }

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)
      {
         /* Send CfgReq */
         case 0:
           /* set configuration parameters */
            /* SB_SETUP_SCTNETADDRLST(assoc_1.localNAddrLst, localNAddrLst_1) */
            sbStdTSapCfg(&sbMgmt, SAP_1);
            switch(curtstnum)
            {
               case 1:
                  sbMgmt.hdr.transId = 10201;
                  break;
               case 2:    /* Test 102.02: Execution */
                  sbMgmt.hdr.transId = 10202;
                  sbMgmt.hdr.elmId.elmnt = HDR_ERR;
                  break;
               case 3:
                  sbMgmt.hdr.transId = 10203;
                  break;
               case 4:
                  sbMgmt.hdr.transId = 10204;
                  sbMgmt.t.cfg.s.tSapCfg.swtch = (U8)(LSB_SW_RFC_REL0 + 1);
                  break;
               case 5:
                  sbMgmt.hdr.transId = 10205;
                  sbMgmt.t.cfg.s.tSapCfg.suId = sbMgmt.t.cfg.s.genCfg.maxNmbTSaps;
                  break;
               case 6:
                  sbMgmt.hdr.transId = 10206;
                  sbMgmt.t.cfg.s.tSapCfg.reConfig.tIntTmr= 0;
                  break;
               case 7:
                  sbMgmt.hdr.transId = 10207;
                  sbMgmt.t.cfg.s.tSapCfg.reConfig.maxBndRetry = 0;
                  break;
/*  sb032.102 : IPV6 Support Added */
               case 8:
                  sbMgmt.hdr.transId = 10208;
                  break;
            }
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.state++;
            break;
         case 1: /* Dequeue CfgCfm and confirm status */
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   ACC_EVT_CFG_CFM, TIMEOUT_ON_PRIM, 0);
            }
            else
            {  /* primitive received */
               /* fill the mgmt */
               switch(curtstnum)
               {
                  case 1:   /* Test C.102.01: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
                     break;
                  case 2:    /* Test C.102.02: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason = LCM_REASON_INVALID_ELMNT;
                     break;
                  case 3:    /* Test C.102.03: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_OK;
                     mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                     break;
                  case 4: /* Test C.102.04: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason =  LCM_REASON_INVALID_PAR_VAL;
                     break;
                  case 5: /* Test C.102.05: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                     break;
                  case 6: /* Test C.102.06: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                     break;
                 case 7: /* Test C.102.07: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                     break;
                  case 8:    /* Test C.102.08: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_OK;
                     mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                     break;
               }
               mgmt.transId = sbAccCb.curTst.curTransId;
               ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM);
               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       ACC_EVT_CFG_CFM, status, reason);
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }

            } /* end primitive received */
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.state++;
            break;
         case 2: /* Do cleanup before next subtest */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test/subtest */
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
               if(curtstnum == 1)
                  sbAccCb.curTst.bConfigDeleted = TRUE;
             }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;
      } /* end switch */
   }   /* end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end tsapCfg_tst */

/* sb003.103 - addition - new function for path profile configuration test cases
 */
/* SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
/*
*       Fun:   sbPathProfCfgTst
*
*       Desc:   The path profile configuration tests
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbPathProfCfgTst
(
U8 curtstnum,   /* number of current test within test group (e.g. O.101.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbPathProfCfgTst(curtstnum, numstr)
U8 curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   PRIVATE        SbMgmtQElm      mgmt;
   PRIVATE        SbMgmt          sbMgmt;
   SctStatus      status;
   Reason         reason;
   S16            ret;

   TRC2(sbPathProfCfgTst);

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   if (sbAccCb.curTst.bBusyPreTestConf == TRUE)
   {  /* No pre-test setup */
      if (curtstnum != 1)
      {
         SB_GENCFG()
         if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
         {
            SB_ENABLE_DEBUGP(0xffffffff)
            SB_ENTERTEST(sbAccCb.curTst.bDebugPMask, BIT0 )
         }
      }
      else
      {
         sbAccCb.curTst.bBusySubtest = TRUE;        /* Now a test */
         sbAccCb.curTst.bBusyPreTestConf = FALSE;   /* Done with pre-test setup */
      }
   }
   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)
      {
         /* Send CfgReq */
         case 0:
            /* set path profile configuration parameters */
            sbStdPathProfCfg(&sbMgmt);
            switch(curtstnum)
            {
               case 1: /* C.103.01: Execution */
                  sbMgmt.hdr.transId = 10301;
                  break;
               case 2:   /* C.103.02: Execution */
                  sbMgmt.hdr.transId = 10302;
                  break;
               case 3:   /* C.103.03: Execution */
                  sbMgmt.hdr.transId = 10303;
                  /* setting profId to 1 since maxNmbPathProfs is set to 1. if
                   * maxNmbPathProfs is changed then the profId should also be
                   * changed since this is a negative test case and profId
                   * should be same as maxNmbPathProfs.
                   */
                  sbMgmt.t.cfg.s.pathProfCfg.profId = 6;
                  break;
               case 4:   /* C.103.04: Execution */
                  sbMgmt.hdr.transId = 10304;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.initCwnd = 0;
                  break;
               case 5:   /* C.103.05: Execution */
                  sbMgmt.hdr.transId = 10305;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.initSsthresh = 0;
                  break;
               case 6:   /* C.103.06: Execution */
                  sbMgmt.hdr.transId = 10306;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.rtoInitial = 0;
                  break;
               case 7:   /* C.103.07: Execution */
                  sbMgmt.hdr.transId = 10307;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.rtoMin = 0;
                  break;
               case 8:   /* C.103.08: Execution */
                  sbMgmt.hdr.transId = 10308;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.rtoMax = 0;
                  break;
               case 9:   /* C.103.09: Execution */
                  sbMgmt.hdr.transId = 10309;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.alpha = 0;
                  break;
               case 10:   /* C.103.10: Execution */
                  sbMgmt.hdr.transId = 10310;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.beta = 0;
                  break;
               case 11:   /* C.103.11: Execution */
                  sbMgmt.hdr.transId = 10311;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.intervalTm = 0;
                  break;
               case 12:   /* C.103.12: Execution */
                  sbMgmt.hdr.transId = 10312;
#ifdef LSB4
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.bundleTm = 0;
#endif
                  break;
               case 13:   /* C.103.13: Execution */
                  sbMgmt.hdr.transId = 10313;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.bcl = 0;
                  break;
               case 14:   /* C.103.14: Execution */
                  sbMgmt.hdr.transId = 10314;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.idleCwndRate = 101;
                  break;
               case 15:   /* C.103.15: Execution */
                  sbMgmt.hdr.transId = 10315;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.frCwndRate = 101;
                  break;
               case 16:   /* C.103.16: Execution */
                  sbMgmt.hdr.transId = 10316;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.rtrCwndRate = 101;
                  break;
               case 17:   /* C.103.17: Execution */
                  sbMgmt.hdr.transId = 10317;
                  sbMgmt.t.cfg.s.pathProfCfg.reConfig.maxPathReTx = 0;
                  break;
            }
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.state++;
            break;
         /* Dequeue CfgCfm and confirm status */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   ACC_EVT_CFG_CFM, TIMEOUT_ON_PRIM, 0);
            }
            else
            {
               switch(curtstnum)
               {
                  case 1:    /* Test C.103.01: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
                     break;
                  case 2:     /* Test C.103.02: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_OK;
                      mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                      break;
                  case 3:     /* Test C.103.03: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 4:     /* Test C.103.04: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 5:     /* Test C.103.05: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 6:     /* Test C.103.06: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 7:     /* Test C.103.07: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 8:     /* Test C.103.08: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 9:     /* Test C.103.09: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 10:     /* Test C.103.10: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 11:     /* Test C.103.11: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 12:     /* Test C.103.12: Expected Results  */
/* sb005.103: bundle Timer can be zero now */
                      mgmt.cfm.status = LCM_PRIM_OK;
                      mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                      break;
                  case 13:     /* Test C.103.13: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 14:     /* Test C.103.14: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 15:     /* Test C.103.15: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 16:     /* Test C.103.16: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                  case 17:     /* Test C.103.17: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                      break;
                }
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM);
                if(ret == RFAILED)
                {
                   sbAccCb.curTst.subTestsFail++;
                   sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                        ACC_EVT_CFG_CFM, status, reason);
                }
                else
                   sbAccCb.curTst.subTestsPass++;
            } /* end primitive received */
            sbAccCb.curTst.state++;
            sbAccCb.curTst.subTest++;
            break;
         case 2: /* Do cleanup before next test */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;/* Done with a test/subtest*/
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
#if 0               
               if(curtstnum > 2)
                  sbAccCb.curTst.bConfigDeleted = TRUE;
#endif               
            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;
      } /* end switch */
   } /* end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);

}  /* end pathProfCfg_tst */

/* sbxxx.103 - addition - new function for destination address configuration test
 * cases.
 */
/*
*       Fun:   sbDstAddrCfgTst
*
*       Desc:   The path profile configuration tests
*       Ret:   ROK
*
*       Group: Configuration
*
*       Notes:
*
*       File:  sb_act1.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDstAddrCfgTst
(
U8 curtstnum,   /* number of current test within test group (e.g. O.101.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDstAddrCfgTst(curtstnum, numstr)
U8 curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   PRIVATE        SbMgmtQElm      mgmt;
   PRIVATE        SbMgmt          sbMgmt;
   SctStatus      status;
   Reason         reason;
   S16            ret;

   TRC2(sbDstAddrCfgTst);

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   if (sbAccCb.curTst.bBusyPreTestConf == TRUE)
   {  /* No pre-test setup */
      if (curtstnum != 1)
      {
         SB_GENCFG()
         if(isBitSet(sbAccCb.curTst.bConfigMask, BIT1) == FALSE )
         {                                                
           sbStdPathProfCfg(&sbMgmt);                           
           sbSendConfigReq(&sbMgmt, STSBPATHPROF, GEN);           
         }                                                 
         if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
         {
            SB_ENABLE_DEBUGP(0xffffffff)
            SB_ENTERTEST(sbAccCb.curTst.bDebugPMask, BIT0 )
         }
      }
      else
      {
         sbAccCb.curTst.bBusySubtest = TRUE;        /* Now a test */
         sbAccCb.curTst.bBusyPreTestConf = FALSE;   /* Done with pre-test setup */
      }
   }
   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)
      {
         /* Send CfgReq */
         case 0:
            /* set path profile configuration parameters */
            sbStdDstAddrCfg(&sbMgmt);
            switch(curtstnum)
            {
               case 1: /* C.104.01: Execution */
                  sbMgmt.hdr.transId = 10401;
                  break;
               case 2:   /* C.104.02: Execution */
                  sbMgmt.hdr.transId = 10402;
                  break;
            }
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.state++;
            break;

         /* Dequeue CfgCfm and confirm status */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   ACC_EVT_CFG_CFM, TIMEOUT_ON_PRIM, 0);
            }
            else
            {
               switch(curtstnum)
               {
                  case 1:    /* Test C.103.01: Expected Results  */
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
                     break;
                  case 2:     /* Test C.103.02: Expected Results  */
                      mgmt.cfm.status = LCM_PRIM_OK;
                      mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                      break;
                }
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM);
                if(ret == RFAILED)
                {
                   sbAccCb.curTst.subTestsFail++;
                   sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                        ACC_EVT_CFG_CFM, status, reason);
                }
                else
                   sbAccCb.curTst.subTestsPass++;
            } /* end primitive received */
            sbAccCb.curTst.state++;
            sbAccCb.curTst.subTest++;
            break;
         case 2: /* Do cleanup before next test */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;/* Done with a test/subtest*/
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
               if(curtstnum > 2)
                  sbAccCb.curTst.bConfigDeleted = TRUE;

            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;
      } /* end switch */
   } /* end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);

}  /* end pathProfCfg_tst */
#endif /* SB_SATELLITE */
/******************************************************************30**

         End of file:     sb_act1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:06 2015

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/3      ---     hnh  1. Initial version
/main/3      ---      sb  1. Modified for SCTP release based on 
                             RFC-2960 'Oct 2000.
          sb034.102   hm  1. changes to support change in patch sb028.102.
                             Now it allows Freeze Timer to be zero
          sb042.102   hl  1. Added change for SHT interface
/main/4      ---   rsr/ag 1. Updated for Release of 1.3
          sb003.103   ag   1. Satellite SCTP feature (under compile-time
                              flag SB_SATELLITE): Added test cases for
                              path profile & dst addr configuration.
          sb005.103   ag   1. Bundle timer can be zero in path profile. 
          sb018.103   pkaX 1. SACK delayTmr issue: maxAckDelayTm value can be 
                              zero.
*********************************************************************91*/
