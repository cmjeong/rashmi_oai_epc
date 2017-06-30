

/********************************************************************20**

     Name:     sb_act2.c - Acceptance Tests for the SCTP layer

     Type:     C source file

     Desc:     C code for acceptance tests test cases.  Includes the binding and unbinding
               tests for the upper and the lower layer.
               tests.

     File:     sb_act2.c

     Sid:      sb_act2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:06 2015

     Prg:      nct

*********************************************************************21*/

/*

  sb_act2.c - Acceptance Tests for the SCTP layer

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
#include "sb.x"            /* SCTP internal typedefs */
#include "sb_acc.x"        /* defines for SCTP layer */



/* local defines */

/* local typedefs */

/* forward references */
PRIVATE  S16 sbSctBindTst     ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbHitBindTst     ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbHitUBindTst    ARGS((U8 curtstnum, S8  *numstr));
/* sb042.102 - Added change for SHT interface and rolling upgrade */
#ifdef SB_RUG
PRIVATE  S16 sbShtCntrlTst    ARGS((U8 curtstnum, S8  *numstr));
#endif
/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */

/*
*       Fun:   sbO100_01
*
*       Desc:  Test case : O.100.01
*              Purpose   : Verify successful transmission of a bind request
*                          for SAP 1.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO100_01
(
void
)
#else
PUBLIC  S16 sbO100_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.\
                                       curtstnum */

   TRC2(sbO100_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 2;
   sbSctBindTst(curtstnum,"O.100.01");
   RETVALUE(ROK);
} /* end sbO100_01 */

/*
*       Fun:   sbO100_02
*
*       Desc:  Test case : O.100.02
*              Purpose   : Verify unsuccessful transmission of a bind request \
*                          for SAP 4 (unconfigured).
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO100_02
(
void
)
#else
PUBLIC  S16 sbO100_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.\
                                       curtstnum */

   TRC2(sbO100_02)
   curtstnum = 2;                    /* number of test within group */
   sbAccCb.curTst.numSubTst = 2;
   sbSctBindTst(curtstnum,"O.100.02");
   RETVALUE(ROK);
} /* end sbO100_02 */

/*
*       Fun:   sbO100_03
*
*       Desc:  Test case : O.100.03
*              Purpose   : Verify successful transmission of a unbind request
*                          for SAP 1.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO100_03
(
void
)
#else
PUBLIC  S16 sbO100_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: \
                                       eg. C.101.curtstnum */

   TRC2(sbO100_03)
   curtstnum = 3;                    /* number of test within group */
   sbAccCb.curTst.numSubTst = 2;
   sbSctBindTst(curtstnum,"O.100.03");
   RETVALUE(ROK);
} /* end sbO100_03 */


/*
*       Fun:   sbO100_04
*
*       Desc:  Test case : O.100.04
*              Purpose   : Verify that a configured and bound SCT SAP can be
*                          unbound and later be bound again.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO100_04
(
void
)
#else
PUBLIC  S16 sbO100_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.\
                                       curtstnum */

   TRC2(sbO100_04)
   curtstnum = 4;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 3;
   sbSctBindTst(curtstnum,"O.100.04");
   RETVALUE(ROK);
} /* end sbO100_04 */

/*
*       Fun:   sbO100_05
*
*       Desc:  Test case : O.100.05
*              Purpose   : Verify that the SCTP layer generates an alarm
*                          when it receives a unbind request for
*                          SAP 4 (unconfigured).
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO100_05
(
void
)
#else
PUBLIC  S16 sbO100_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test:
                                       eg. C.101.curtstnum */

   TRC2(sbO100_05)
   curtstnum = 5;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 2;
   sbSctBindTst(curtstnum,"O.100.05");
   RETVALUE(ROK);
} /* end sbO100_05 */

/*
*       Fun:   sbO100_06
*
*       Desc:  Test case : O.100.06
*              Purpose   : Verify that the SCTP layer generates an alarm when
*                          it receives an unbind request for SAP 2
*                          (configured but not bound).
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO100_06
(
void
)
#else
PUBLIC  S16 sbO100_06(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO100_06)
   curtstnum = 6;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 2;
   sbSctBindTst(curtstnum,"O.100.06");
   RETVALUE(ROK);
} /* end sbO100_06 */


/*
*       Fun:   sbO100_07
*
*       Desc:  Test case : O.100.07
*              Purpose   : Verify that if SAP 1 is unbounded, all existing
*                          associations on the SAP terminates.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO100_07
(
void
)
#else
PUBLIC  S16 sbO100_07(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO100_07)
   curtstnum = 7;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 2;
   /* sb032.102 :  IPV6 Support Added */
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctBindTst(curtstnum,"O.100.07");
   RETVALUE(ROK);
} /* end sbO100_07 */


/*
*       Fun:   sbO101_01
*
*       Desc:  Test case : O.101.01
*              Purpose   : Verify successful binding and opening of
*                          IP server for TSAP 1.
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_01
(
void
)
#else
PUBLIC  S16 sbO101_01(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_01)
   curtstnum = 1;                   /* number of test within group */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 3;
#else
   sbAccCb.curTst.numSubTst = 4;
#endif
   sbHitBindTst(curtstnum,"O.101.01");
   RETVALUE(ROK);
} /* end sbO101_01*/

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbO101_04
*
*       Desc:  Test case : O.101.04
*              Purpose   : Verify successful binding and opening of
*                          IP server for TSAP 1 for IPV6 addresses.
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_04
(
void
)
#else
PUBLIC  S16 sbO101_04(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_01)
   curtstnum = 4;                   /* number of test within group */
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 3;
#else
   sbAccCb.curTst.numSubTst = 4;
#endif
   sbHitBindTst(curtstnum,"O.101.04");
   RETVALUE(ROK);
} /* end sbO101_01*/


/*
*       Fun:   sbO101_02
*
*       Desc:  Test case : O.101.02
*              Purpose   : Verify unsuccessful binding and opening of IP server
*                          for TSAP 3 (unconfigured).
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_02
(
void
)
#else
PUBLIC  S16 sbO101_02(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_02)
   curtstnum = 2;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 2;
   sbHitBindTst(curtstnum,"O.101.02");
   RETVALUE(ROK);
} /* end sbO101_02*/

/*
*       Fun:   sbO101_03
*
*       Desc:  Test case : O.101.03
*              Purpose   : Verify the SCTP module will unsuccessfully try a
*                          maximum of maxBndRetry times
*                          to bind.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_03
(
void
)
#else
PUBLIC  S16 sbO101_03(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_03)
   curtstnum = 3;                   /* number of test within group */
   sbHitBindTst(curtstnum,"O.101.03");
   RETVALUE(ROK);
} /* end sbO101_03*/


/* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA 
/*
*       Fun:   sbO101_05
*
*       Desc:  Test case : O.101.05
*              Purpose   : Verify successful binding and opening of
*                          IP server for TSAP 1 at SHT interface.
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_05
(
void
)
#else
PUBLIC  S16 sbO101_05(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_05)
   curtstnum = 5;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 4;
   sbHitBindTst(curtstnum,"O.101.05");
   RETVALUE(ROK);
} /* end sbO101_05*/

/*
*       Fun:   sbO101_11
*
*       Desc:  Test case : O.101.11
*              Purpose   : Verify successful binding and opening of
*                          IP server for TSAP 1 at SHT interface.
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_11
(
void
)
#else
PUBLIC  S16 sbO101_11(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_11)
   curtstnum = 11;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 4;
   sbHitBindTst(curtstnum,"O.101.11");
   RETVALUE(ROK);
} /* end sbO101_11*/
#endif /* SB_FTHA */

/* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG 
/*
*       Fun:   sbO101_06
*
*       Desc:  Test case : O.101.06
*              Purpose   : 
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_06
(
void
)
#else
PUBLIC  S16 sbO101_06(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_06)
   curtstnum = 1;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 1;
   sbShtCntrlTst(curtstnum,"O.101.06");
   RETVALUE(ROK);
} /* end sbO101_06*/

/*
*       Fun:   sbO101_07
*
*       Desc:  Test case : O.101.07
*              Purpose   : 
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_07
(
void
)
#else
PUBLIC  S16 sbO101_07(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_07)
   curtstnum = 2;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 4;
   sbShtCntrlTst(curtstnum,"O.101.07");
   RETVALUE(ROK);
} /* end sbO101_07*/

/*
*       Fun:   sbO101_08
*
*       Desc:  Test case : O.101.08
*              Purpose   : 
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_08
(
void
)
#else
PUBLIC  S16 sbO101_08(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_08)
   curtstnum = 3;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 4;
   sbShtCntrlTst(curtstnum,"O.101.08");
   RETVALUE(ROK);
} /* end sbO101_08*/

/*
*       Fun:   sbO101_09
*
*       Desc:  Test case : O.101.09
*              Purpose   : 
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_09
(
void
)
#else
PUBLIC  S16 sbO101_09(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_09)
   curtstnum = 4;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 4;
   sbShtCntrlTst(curtstnum,"O.101.09");
   RETVALUE(ROK);
} /* end sbO101_09*/

/*
*       Fun:   sbO101_10
*
*       Desc:  Test case : O.101.10
*              Purpose   : 
*
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO101_10
(
void
)
#else
PUBLIC  S16 sbO101_10(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO101_10)
   curtstnum = 5;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 4;
   sbShtCntrlTst(curtstnum,"O.101.10");
   RETVALUE(ROK);
} /* end sbO101_10*/

#endif /* SB_RUG */

/*
*       Fun:   sbO102_01
*
*       Desc:  Test case : O.102.01
*              Purpose   : Verify successful unbinding and termination of IP
*                          server for TSAP 1.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO102_01
(
void
)
#else
PUBLIC  S16 sbO102_01(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO102_01)
   curtstnum = 1;                   /* number of test within group */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 2;
#else 
   sbAccCb.curTst.numSubTst = 3;
#endif
   sbHitUBindTst(curtstnum,"O.102.01");
   RETVALUE(ROK);
} /* end sbO102_01*/

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbO102_05
*
*       Desc:  Test case : O.102.05
*              Purpose   : Verify successful unbinding and termination of IP
*                          server for TSAP 1 for IPV6 addresses.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO102_05
(
void
)
#else
PUBLIC  S16 sbO102_05(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO102_05)
   curtstnum = 5;                   /* number of test within group */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 2;
#else
   sbAccCb.curTst.numSubTst = 3;
#endif
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbHitUBindTst(curtstnum,"O.102.05");
   RETVALUE(ROK);
} /* end sbO102_01*/
/*
*       Fun:   sbO102_02
*
*       Desc:  Test case : O.102.02
*              Purpose   : Verify that the unbinding and termination of IP
*                          server for TSAP 3 (unconfigured) is unsuccessful.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO102_02
(
void
)
#else
PUBLIC  S16 sbO102_02(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO102_02)
   curtstnum = 2;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 2;
   sbHitUBindTst(curtstnum,"O.102.02");
   RETVALUE(ROK);
} /* end sbO102_02*/

/*
*       Fun:   sbO102_03
*
*       Desc:  Test case : O.102.03
*              Purpose   : Verify that the unbinding and termination of
*                          IP server for TSAP 2 (configured but not bound)
*                          is unsuccessful.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO102_03
(
void
)
#else
PUBLIC  S16 sbO102_03(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO102_03)
   curtstnum = 3;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 2;
   sbHitUBindTst(curtstnum,"O.102.03");
   RETVALUE(ROK);
} /* end sbO102_03*/

/*
*       Fun:   sbO102_04
*
*       Desc:  Test case : O.102.04
*              Purpose   : Verify that a configured and bound TSAP can be
*                          unbound and later be configured and bound again.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO102_04
(
void
)
#else
PUBLIC  S16 sbO102_04(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO102_04)
   curtstnum = 4;              /* number of test within group */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 6;
#else
   sbAccCb.curTst.numSubTst = 8;
#endif
   sbHitUBindTst(curtstnum,"O.102.04");
   RETVALUE(ROK);
} /* end sbO102_04*/

/*
*       Fun:   sbO102_06
*
*       Desc:  Test case : O.102.06
*              Purpose   : Verify that a configured and bound TSAP can be
*                          unbound and later be configured and bound again for
*                          for IPV6 addresses.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO102_06
(
void
)
#else
PUBLIC  S16 sbO102_06(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO102_04)
   curtstnum = 6;              /* number of test within group */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 6;
#else
   sbAccCb.curTst.numSubTst = 8;
#endif
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbHitUBindTst(curtstnum,"O.102.06");
   RETVALUE(ROK);
} /* end sbO102_06*/


/* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
/*
*       Fun:   sbO102_07
*
*       Desc:  Test case : O.102.07
*              Purpose   : Verify successful unbinding and termination of IP
*                          server for TSAP 1 at SHT interface.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO102_07
(
void
)
#else
PUBLIC  S16 sbO102_07(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO102_07)
   curtstnum = 7;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 3;
   sbHitUBindTst(curtstnum,"O.102.07");
   RETVALUE(ROK);
} /* end sbO102_07*/

/*
*       Fun:   sbO102_08
*
*       Desc:  Test case : O.102.08
*              Purpose   : Verify successful unbinding and termination of IP
*                          server for TSAP 1 at SHT interface.
*
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO102_08
(
void
)
#else
PUBLIC  S16 sbO102_08(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO102_08)
   curtstnum = 8;                   /* number of test within group */
   sbAccCb.curTst.numSubTst = 3;
   sbHitUBindTst(curtstnum,"O.102.08");
   RETVALUE(ROK);
} /* end sbO102_08*/
#endif /* SB_FTHA */


/*
*       Fun:   sbSctBindTst
*
*       Desc:   Binding and unbinding the upper SAPs
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctBindTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.101.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctBindTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbMgmtQElm     mgmt;
   PRIVATE        SbOperQElm     oper;
   SctStatus      status;
   Reason         reason;
   S16            ret;
   PRIVATE        SbMgmt         sbMgmt;
   PRIVATE        SbAccAssoc     assoc_1;
   PRIVATE        SbAccChunkBld  buildPar;
   SbAccMsgQElm  *msg;

   TRC2(sbSctBindTst)
   /* Pretests */
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE){
         SB_ENABLE_DEBUGP(0xffffffff)

         switch(curtstnum)                           /* Pretests continues */
         {
            case 1:
            if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
               {
                  SB_SCTSAPCFG(SAP_1)
                  SB_ENTERTEST( sbAccCb.curTst.bSctSapCfgMask, BIT0 )
               }
               break;
            case 2:
               SB_ENTERTEST(sbAccCb.curTst.bDebugPMask, BIT0 )
               break;
            case 3:
               if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
               {
                  SB_SCTSAPCFG(SAP_1)
                     if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE){
                        SB_BIND_SCTSAP(SUID_0, SPID_0, BIT0)
                        SB_ENTERTEST( sbAccCb.curTst.bSapMask, BIT0 )
                     }
               }
               break;
            case 4:  /* Test O.100.04: Pretest/Setup */
               if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
               {
               SB_SCTSAPCFG(SAP_1)
               if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE){
                  SB_BIND_SCTSAP(SUID_0, SPID_0, BIT0)
                  SB_ENTERTEST( sbAccCb.curTst.bSapMask, BIT0 )
               }
               }
               break;
            case 5:
               SB_ENTERTEST( sbAccCb.curTst.bDebugPMask, BIT0 )
               break;
            case 6:
               if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE ) {
                  SB_SCTSAPCFG(SAP_2)
                  SB_ENTERTEST( sbAccCb.curTst.bSctSapCfgMask, BIT1 )
               }
               break;
            case 7:  /* Test O.100.07: Pretest/Setup */
               if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
               {
               SB_SCTSAPCFG(SAP_1)
                  if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                  {
                     SB_TSAPCFG(SAP_1)
                     if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
                     {
                        SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                        if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
                        {
                           SB_DISABLE_TRACE() /* disable trace */
                           if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                              {
                                 SB_EST_ASSOC(assoc_1, BIT0)
                                 if (isBitSet(sbAccCb.curTst.bAssocMask, BIT0) == TRUE)
                                 {
                                    SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                                 }/* end bAssocMask if */
                              }/*end Assoc Setup mask */
                           } /* end trace mask */
                        } /* end TSapMask if */
                     }/*end TSapCfgMask if*/
                  } /* end SctSapCfgMask, bit 0, if */
               } /* end debugPMask if*/
               break;
            default:
              sbAccDispErrTstRslt("Pretests:  ", 0,0, NO_TEST,0);
              SB_SUBTESTFAIL()
              break;
         } /* end curtstnum switch */
      }/* end ConfigMask if */
   }  /* end pretests */

       /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
              { /* start curtstnum tests */
              case 1:    /* Test O.100.01: Execution */
                (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_0, SPID_0);
                sbAccCb.curTst.evtType = ACC_EVT_BND_CFM;   /* expected result */
                break;
              case 2:     /* Test O.100.02: Execution */
                (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_3, SPID_3);
                sbAccCb.curTst.evtType = ACC_EVT_STA_IND;   /* expected result */
                break;
              case 3:    /* Test O.100.03: Execution */
                 setResponse(&sbMgmt.hdr.response);
                 sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
                 sbMgmt.t.cntrl.action = AUBND_DIS;
                 sbMgmt.t.cntrl.sapId =  SPID_0;
                 sbMgmt.hdr.transId = 10003;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                 sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                 (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                 sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                 break;
              case 4:         /* Test O.100.04: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       setResponse(&sbMgmt.hdr.response);
                       sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
                       sbMgmt.t.cntrl.action = AUBND_DIS;
                       sbMgmt.t.cntrl.sapId = SPID_0;
                       sbMgmt.hdr.transId = 10004;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                       sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                       (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;
                        /* expected result */
                       break;
                    case 2:
                       (void) ItLiSctBndReq(&sbAccCb.itPst, SUID_0, SPID_0);
                       sbAccCb.curTst.evtType = ACC_EVT_BND_CFM;
                                                    /* expected result */
                       break;
                 }
                 break;
              case 5:     /* Test O.100.05: Execution */
                 setResponse(&sbMgmt.hdr.response);
                 sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
                 sbMgmt.t.cntrl.action = AUBND_DIS;
                 sbMgmt.t.cntrl.sapId = SPID_3;
/* sb003.103 : SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                 sbMgmt.hdr.transId = 10005;
                 sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                 (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                 sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                 break;
              case 6:       /* Test O.100.06: Execution */
                 setResponse(&sbMgmt.hdr.response);
                 sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
                 sbMgmt.t.cntrl.action = AUBND_DIS;
                 sbMgmt.t.cntrl.sapId = SPID_1;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                 sbMgmt.hdr.transId = 10006;
                 sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                 (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                 sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                 break;
              case 7:         /* Test O.100.07: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                     case 1:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
                        sbMgmt.t.cntrl.action = AUBND_DIS;
                        sbMgmt.t.cntrl.sapId = SPID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                        sbMgmt.hdr.transId = 10007;
                        sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                        SPrint(" ===Cntrl Req===\n\n");
                        (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;    /* expected result */
                        break;
                 }
                 break;
         }   /*end curtstnum switch #1 */

         sbAccCb.curTst.state++;
         break;

         /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if (status == WAIT)
            {
               /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if (status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            {
               /*result received */
               reason = 0;
               switch(curtstnum)
               {
                  case 1:    /* Test O.100.01: Expected results */
                     oper.it.suId = SUID_0;
                     oper.it.result = CM_BND_OK;
                     ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_BND_CFM, &status, &reason);
                     break;
                  case 2:     /* Test O.100.02: Expected results */
                     mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                     mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
                     mgmt.s.usta.sapId = SPID_3;
                     ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_IND);
                     break;
                  case 3:    /* Test O.100.03: Expected results */

                     mgmt.s.cntrl.sapId = SUID_0;
                     mgmt.cfm.status = LCM_PRIM_OK;
                     mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                     mgmt.transId = sbAccCb.curTst.curTransId;
                     ret = sbLsbChkCfm(&mgmt,&status, &reason, \
                                       ACC_EVT_CNTRL_CFM);
                      break;
                  case 4:         /* Test O.100.04: Expected results */
                     switch(sbAccCb.curTst.subTest)
                     {
                        case 1:
                           mgmt.s.cntrl.sapId = SUID_0;
                           mgmt.cfm.status = LCM_PRIM_OK;
                           mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                           mgmt.transId = sbAccCb.curTst.curTransId;
                           ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                             ACC_EVT_CNTRL_CFM);
                           break;
                        case 2:
                           oper.it.suId = SUID_0;
                           oper.it.result = CM_BND_OK;
                           ret = sbSctChkCfm(&oper, &mgmt,\
                                             ACC_EVT_BND_CFM, \
                                             &status, &reason);
                           break;
                     }
                     break;
                  case 5: /* Test O.100.05: Expected results */
                     mgmt.s.cntrl.sapId = SUID_3;
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                     mgmt.transId = sbAccCb.curTst.curTransId;
                     ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                       ACC_EVT_CNTRL_CFM);
                     break;
                  case 6: /* Test O.100.06: Expected results */
                     mgmt.s.cntrl.sapId = SUID_1;
                     mgmt.cfm.status = LCM_PRIM_NOK;
                     mgmt.cfm.reason = LCM_REASON_INVALID_STATE;
                     mgmt.transId = sbAccCb.curTst.curTransId;
                     ret = sbLsbChkCfm(&mgmt, &status, &reason, \
                                       ACC_EVT_CNTRL_CFM);
                     break;
                  case 7:         /* Test O.100.07: Expected results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* ABORT for the association */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_ABORT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,
                                                    &assoc_1, &status  );
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
			   else if(msg->evntType == ACC_EVT_DISC_REQ)
			   {
				ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_DISC_REQ, &status, &reason);
			   }
#endif
                           else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                           {
                              /* control confirm */
                              mgmt.s.cntrl.sapId = SUID_0;
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, \
                                                ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                     }
                     break;
               } /*end curtstnum switch #2 */

               if (ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                      sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else     /* Subtest successful */
               {
                 sbAccCb.curTst.subTestsPass++;
               }      /*End Subtest successful */
            } /*end primitive received */

            if ( (curtstnum == 7) )
            {
               if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                    ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
            }
            else
            {
               sbAccCb.curTst.state++;
               sbAccCb.curTst.subTest++;
            }
            break;

         case 2: /* Do cleanup before next test */
            if (sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test */
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;
      } /*end swicth #1 */
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
   {
      doCleanup();
   }

   RETVALUE(ROK);
}  /* end sbSctBindTst */



/*
*       Fun:   sbHitBindTst
*
*       Desc:  Binding TSAP and Initializing IP server connection
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbHitBindTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.101.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbHitBindTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbAccMsgQElm   *msg;
   SbMgmtQElm     mgmt;
   PRIVATE        SbOperQElm     oper;
   PRIVATE        SbMgmt         sbMgmt;
   SctStatus      status;
   Reason         reason;
   S16            ret;
   PRIVATE        SbAccAssoc     assoc_1;


   TRC2(sbHitBindTst)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
            if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
            {
            SB_DISABLE_TRACE()

            switch(curtstnum)                           /* Pretests continues */
            {
               case 1:   /* Test O.101.01: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                      SB_TSAPCFG(SAP_1)
                      SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
                  }
                  break;
               case 2:
                  SB_ENTERTEST( sbAccCb.curTst.bTraceMask, BIT0)
                  break;
               case 3:      /* Test O.101.03: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                  SB_TSAPCFG(SAP_1)
                  SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
                  }
                  break;
                  /* sb032.102 :  IPV6 Support Added */
               case 4:   /* Test O.101.04: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_TSAPCFG(SAP_1)
                      SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
                  }
                  break;
               /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
               case 5:   /* Test O.101.05: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                      SB_TSAPCFG(SAP_1)
                      SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
                  }
                  break;
               case 11:   /* Test O.101.11: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                      SB_TSAPCFG(SAP_1)
                      SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
                  }
                  break;
#endif /* SB_FTHA */
              default:
                  sbAccDispErrTstRslt("Pretest:  ", 0,0, NO_TEST,0);
                  SB_SUBTESTFAIL()
                  break;

            } /*end switch curtstnum */
         } /* end debugMask if */
      } /*end if configMask */

   }/*end pretest config */


   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
       case 0:
            sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
            sbMgmt.t.cntrl.action =  ABND_ENA;

            switch(curtstnum)
            {
              case 1:         /*Test O.101.01: Execution */
                 switch (sbAccCb.curTst.subTest)
                 {
                    case 1:
                       if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                           ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)){
                           sbMgmt.t.cntrl.sapId =  SUID_0;
                           sbMgmt.hdr.transId = 10101;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                           sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                           setResponse(&sbMgmt.hdr.response);
                           (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                         }
                       break;
                    case 2:
                      (Void) HiUiHitBndCfm(&sbAccCb.hiPst, SUID_0, CM_BND_OK);
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                       sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
#else
                       sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;   /* expected result */
#endif
                       break;
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                    case 3:
                       (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0, sbAccCb.curTst.suConId, \
                                            sbAccCb.curTst.spConId,&sbAccCb.curTst.localTAddr);
                       if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
#endif
                    default:
                       sbAccDispErrTstRslt("O.101.01: ", 0,0, NO_SUBTEST,0);
                       SB_SUBTESTFAIL()
                       break;
                 }
                 break;
              case 2:   /*Test O.101.02: Execution */
                 sbMgmt.t.cntrl.sapId =  SUID_2;
                 sbMgmt.hdr.transId = 10102;
                 sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                 setResponse(&sbMgmt.hdr.response);
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                 (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                 sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                 break;
              case 3:       /*Test O.101.03: Execution */
                 sbAccCb.curTst.numSubTst = \
                    (U8)(sbMgmt.t.cfg.s.tSapCfg.reConfig.maxBndRetry + 1);
                 if (sbAccCb.curTst.subTest == 1 )
                 {
                    if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                       (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                    {
                       sbMgmt.t.cntrl.sapId =  SUID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                       sbMgmt.hdr.transId = 10103;
                       sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                       setResponse(&sbMgmt.hdr.response);
                       (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  
                       sbAccCb.curTst.tickLstDoneFlg = FALSE;
                    }
                 }
                 else  if (sbAccCb.curTst.subTest <= (sbAccCb.curTst.numSubTst-2) )
                 {
                    sbAccCb.curTst.evtType = ACC_EVT_BND_REQ;   /* expected result */
                 }
                 else  if (sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1) )
                 {
                    if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                       (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                    {
                       sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                       sbAccCb.curTst.tickLstDoneFlg = FALSE;
                    }
                 }
                 break;
              /* sb032.102 :  IPV6 Support Added */
              case 4:         /*Test O.101.04: Execution */
                 switch (sbAccCb.curTst.subTest)
                 {
                    case 1:
                       if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                           ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)){
                           sbMgmt.t.cntrl.sapId =  SUID_0;
                           sbMgmt.hdr.transId = 10104;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                           sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                           setResponse(&sbMgmt.hdr.response);
                           (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                         }
                       break;
                    case 2:
                      (Void) HiUiHitBndCfm(&sbAccCb.hiPst, SUID_0, CM_BND_OK);
                       sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;   /* expected result */
                       break;
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                    case 3:
                       (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0, sbAccCb.curTst.suConId, \
                                            sbAccCb.curTst.spConId,&sbAccCb.curTst.localTAddr);
                       if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
#endif
                    default:
                       sbAccDispErrTstRslt("O.101.01: ", 0,0, NO_SUBTEST,0);
                       SB_SUBTESTFAIL()
                       break;
                 }
                 break;
               /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
              case 5:         /*Test O.101.05: Execution */
                 switch (sbAccCb.curTst.subTest)
                 {
                     case 1:
                     {
                        ShtCntrlReqEvnt  reqInfo;
                        if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                            ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)){
                            setResponse(&reqInfo.hdr.response);
                            reqInfo.reqType = SHT_REQTYPE_BND_ENA;
                            reqInfo.s.bndEna.grpType = SHT_GRPTYPE_ALL;
                            reqInfo.s.bndEna.dstProcId = SFndProcId();
                            reqInfo.s.bndEna.dstEnt.ent = ENTHI;
                            reqInfo.s.bndEna.dstEnt.inst = TSTINST_0;
                            reqInfo.hdr.response.selector = 0;
                            /* send an sht request primitive*/
                            cmPkMiShtCntrlReq(&sbAccCb.shtPst, &reqInfo);
                            sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                            sbAccCb.curTst.tickLstDoneFlg = FALSE;
                          }
                     }
                     break;
                    case 2:
                      (Void) HiUiHitBndCfm(&sbAccCb.hiPst, SUID_0, CM_BND_OK);
                       sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;   /* expected result */
                       break;
                    case 3:
                       (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0, sbAccCb.curTst.suConId, \
                                            sbAccCb.curTst.spConId,&sbAccCb.curTst.localTAddr);
                       if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    default:
                       sbAccDispErrTstRslt("O.101.05: ", 0,0, NO_SUBTEST,0);
                       SB_SUBTESTFAIL()
                       break;
                 }
                 break;
              case 11:         /*Test O.101.11: Execution */
                 switch (sbAccCb.curTst.subTest)
                 {
                     case 1:
                     {
                        ShtCntrlReqEvnt  reqInfo;
                        if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                            ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)){
                            setResponse(&reqInfo.hdr.response);
                            reqInfo.reqType = SHT_REQTYPE_BND_ENA;
                            reqInfo.s.bndEna.grpType = SHT_GRPTYPE_ENT;
                            reqInfo.s.bndEna.dstProcId = SFndProcId();
                            reqInfo.s.bndEna.dstEnt.ent = ENTHI;
                            reqInfo.s.bndEna.dstEnt.inst = TSTINST_0;
                            reqInfo.hdr.response.selector = 0;
                            /* send an sht request primitive*/
                            cmPkMiShtCntrlReq(&sbAccCb.shtPst, &reqInfo);
                            sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                            sbAccCb.curTst.tickLstDoneFlg = FALSE;
                          }
                     }
                     break;
                    case 2:
                      (Void) HiUiHitBndCfm(&sbAccCb.hiPst, SUID_0, CM_BND_OK);
                       sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;   /* expected result */
                       break;
                    case 3:
                       (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0, sbAccCb.curTst.suConId, \
                                            sbAccCb.curTst.spConId,&sbAccCb.curTst.localTAddr);
                       if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    default:
                       sbAccDispErrTstRslt("O.101.11: ", 0,0, NO_SUBTEST,0);
                       SB_SUBTESTFAIL()
                       break;
                 }
                 break;
#endif /* SB_FTHA */
            } /* end curtstnum switch #1 */
            sbAccCb.curTst.state++;
            break;
         /* Dequeue response and test */
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
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
               reason = 0;
               /* fill the mgmt */
              switch(curtstnum)
              {
                 case 1:  /*Test O.101.01: Expected Results */
                    switch (sbAccCb.curTst.subTest)
                    {
                       case 1:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_BND_REQ)
                          {
                             oper.hi.suId =  SUID_0;
                             oper.hi.spId =  SPID_0;
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                               &status, &reason);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          }
                          else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                          {
                             mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                             mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                             mgmt.transId = sbAccCb.curTst.curTransId;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else
                          {
                             status = INC_EVNTTYPE;
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             ret = RFAILED;
                          }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       case 2:
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                          oper.hi.spId = SPID_0;
                          ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ,\
                                            &status, &reason);
                          break;
                       case 3:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                          {
                             oper.hi.spId = SPID_0;
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                               , &status, &reason);
                             assoc_1.suConId = sbAccCb.curTst.suConId;
                          }
                          else if (msg->evntType == ACC_EVT_CNTRL_CFM)
			  {
#else 
			  if (msg->evntType == ACC_EVT_CNTRL_CFM)
                          {
#endif
                             mgmt.cfm.status = LCM_PRIM_OK;
                             mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                               ACC_EVT_CNTRL_CFM);
                             /*  sbAccCb.curTst.subTest++; */
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else
                          {
                             status = INC_EVNTTYPE;
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             ret = RFAILED;
                          }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       default:
                          sbAccDispErrTstRslt("O.101.01: ", 0,0, NO_SUBTEST,0);
                          SB_SUBTESTFAIL()
                          break;
                    }
                    break;
                 /* sb032.102 :  IPV6 Support Added */
                 case 4:  /*Test O.101.04: Expected Results */
                    switch (sbAccCb.curTst.subTest)
                    {
                       case 1:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_BND_REQ)
                          {
                             oper.hi.suId =  SUID_0;
                             oper.hi.spId =  SPID_0;
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                               &status, &reason);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          }
                          else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                          {
                             mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                             mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                             mgmt.transId = sbAccCb.curTst.curTransId;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else
                          {
                             status = INC_EVNTTYPE;
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             ret = RFAILED;
                          }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       case 2:
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                          oper.hi.spId = SPID_0;
                          ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ,\
                                            &status, &reason);
                          break;
                       case 3:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                          {
                             oper.hi.spId = SPID_0;
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                               , &status, &reason);
                             assoc_1.suConId = sbAccCb.curTst.suConId;
                          }
                          else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                          {
#else
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_CNTRL_CFM)
                          {
#endif
                             mgmt.cfm.status = LCM_PRIM_OK;
                             mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                               ACC_EVT_CNTRL_CFM);
                             /*  sbAccCb.curTst.subTest++; */
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else
                          {
                             status = INC_EVNTTYPE;
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             ret = RFAILED;
                          }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       default:
                          sbAccDispErrTstRslt("O.101.01: ", 0,0, NO_SUBTEST,0);
                          SB_SUBTESTFAIL()
                          break;
                    }
                    break;
                 case 2:        /*Test O.101.02: Expected Results */
                    switch (sbAccCb.curTst.subTest)
                    {     /* document the unbound SAPs */
                       case 1:
                          mgmt.cfm.status = LCM_PRIM_NOK;
                          mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                          ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                            ACC_EVT_CNTRL_CFM);
                          break;
                    }
                    break;
                 case 3:       /*Test O.101.03: Expected Results */
                    if (sbAccCb.curTst.subTest == 1 )
                    {
                       sbAccPeekMsg(&msg);
                       if (msg->evntType == ACC_EVT_BND_REQ)
                       {
                          SPrint("Bind req detected \n");
                          oper.hi.suId =  SUID_0;
                          oper.hi.spId =  SPID_0;
                          ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                            &status, &reason);
                          setBit(&sbAccCb.curTst.bTickMask, BIT0);
                       }
                       else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                       {
                          SPrint("Cntrl cfm detected \n");
                          mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                          mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                          mgmt.transId = sbAccCb.curTst.curTransId;
                          ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                            ACC_EVT_CNTRL_CFM);
                          setBit(&sbAccCb.curTst.bTickMask, BIT1);
                       }
                       else
                       {
                          status = INC_EVNTTYPE;
                          setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          ret = RFAILED;
                       }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;

                    }
                    else  if (sbAccCb.curTst.subTest <= \
                                (sbAccCb.curTst.numSubTst-2) )
                    {
                       SPrint("Bind req detected \n");
                       oper.hi.suId =  SUID_0;
                       oper.hi.spId =  SPID_0;
                       ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                         &status, &reason);
                    }
                    else  if (sbAccCb.curTst.subTest == \
                                (sbAccCb.curTst.numSubTst-1) )
                    {
                       sbAccPeekMsg(&msg);
                       if (msg->evntType == ACC_EVT_BND_REQ)
                       {
                          SPrint("Bind req detected \n");
                          oper.hi.suId =  SUID_0;
                          oper.hi.spId =  SPID_0;
                          ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                            &status, &reason);
                          setBit(&sbAccCb.curTst.bTickMask, BIT0);
                       }
                       else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                       {
                          SPrint("Cntrl cfm detected \n");
                          mgmt.cfm.status = LCM_PRIM_NOK;
                          mgmt.cfm.reason = LSB_REASON_MAX_BND_TRY;
                          mgmt.transId = sbAccCb.curTst.curTransId;
                          ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                            ACC_EVT_CNTRL_CFM);
                          setBit(&sbAccCb.curTst.bTickMask, BIT1);
                       }
                       else
                       {
                          status = INC_EVNTTYPE;
                          setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          ret = RFAILED;
                       }
                       if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                    } /*end of if statement */
                    break;
                 /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
                 case 5:  /*Test O.101.05: Expected Results */
                    switch (sbAccCb.curTst.subTest)
                    {
                       case 1:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_BND_REQ)
                          {
                             oper.hi.suId =  SUID_0;
                             oper.hi.spId =  SPID_0;
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                               &status, &reason);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          }
                          else if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                          {
                             mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                             mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                             mgmt.transId = sbAccCb.curTst.curTransId;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else
                          {
                             status = INC_EVNTTYPE;
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             ret = RFAILED;
                          }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       case 2:
                          oper.hi.spId = SPID_0;
                          ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ,\
                                            &status, &reason);
                          break;
                       case 3:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                          {
                             oper.hi.spId = SPID_0;
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                               , &status, &reason);
                             assoc_1.suConId = sbAccCb.curTst.suConId;
                          }
                          else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                          {
                             mgmt.cfm.status = LCM_PRIM_OK;
                             mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                               ACC_EVT_CNTRL_CFM);
                             /*  sbAccCb.curTst.subTest++; */
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else
                          {
                             status = INC_EVNTTYPE;
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             ret = RFAILED;
                          }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       default:
                          sbAccDispErrTstRslt("O.101.05: ", 0,0, NO_SUBTEST,0);
                          SB_SUBTESTFAIL()
                          break;
                    }
                    break;
                 case 11:  /*Test O.101.11: Expected Results */
                    switch (sbAccCb.curTst.subTest)
                    {
                       case 1:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_BND_REQ)
                          {
                             oper.hi.suId =  SUID_0;
                             oper.hi.spId =  SPID_0;
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                               &status, &reason);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          }
                          else if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                          {
                             mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                             mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                             mgmt.transId = sbAccCb.curTst.curTransId;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else
                          {
                             status = INC_EVNTTYPE;
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             ret = RFAILED;
                          }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       case 2:
                          oper.hi.spId = SPID_0;
                          ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ,\
                                            &status, &reason);
                          break;
                       case 3:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                          {
                             oper.hi.spId = SPID_0;
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                               , &status, &reason);
                             assoc_1.suConId = sbAccCb.curTst.suConId;
                          }
                          else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                          {
                             mgmt.cfm.status = LCM_PRIM_OK;
                             mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                               ACC_EVT_CNTRL_CFM);
                             /*  sbAccCb.curTst.subTest++; */
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else
                          {
                             status = INC_EVNTTYPE;
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             ret = RFAILED;
                          }
                          if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                             sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       default:
                          sbAccDispErrTstRslt("O.101.11: ", 0,0, NO_SUBTEST,0);
                          SB_SUBTESTFAIL()
                          break;
                    }
                    break;
#endif /* SB_FTHA */
               }/* end curtstnum switch */

               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }
            } /*end if/else primitive received */
            if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
            {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.bTickMask = 0;
            }
            sbAccCb.curTst.state++;
            break;
         case 2: /* Do cleanup before next test */

            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test/subtest */
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;
      }/*end switch #1 */
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbHitBindTst */


/*
*       Fun:   sbHitUBindTst
*
*       Desc:   Unbinding TSAP and terminating IP server connection.
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbHitUBindTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.101.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbHitUBindTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbAccMsgQElm      *msg;
   SbMgmtQElm        mgmt;
   PRIVATE           SbOperQElm        oper;
   PRIVATE           SbMgmt            sbMgmt;
   SctStatus         status;
   Reason            reason;
   S16               ret;
   UConnId           dns_suConId;
   UConnId           dns_spConId;
   CmTptAddr         tAddr;

   TRC2(sbHitUBindTst)
   ret = ROK;

   /* Pretests */
   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if(isBitSet( sbAccCb.curTst.bDebugPMask, BIT0) == TRUE)
         {
            SB_DISABLE_TRACE()
            switch(curtstnum)                           /* Pretests continues */
            {
               case 1:   /* Test O.102.01: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_TSAPCFG(SAP_1)
                     if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
                     {
                        SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                        SB_ENTERTEST( sbAccCb.curTst.bTSapMask, BIT0 )
                     }
                  }
                  break;
               case 2: /*Test O.102.02: Pretest/setup */
                  SB_ENTERTEST( sbAccCb.curTst.bTraceMask, BIT0 )
                  break;
               case 3:      /* Test O.102.03: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_TSAPCFG(SAP_2)
                     SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT1 );
                  }
                  break;
               case 4:     /* Test O.102.04: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     /* sb044.102: DNS Call conditioned */
                     sbAccCb.useDnsFlag = TRUE;
                     SB_TSAPCFG(SAP_1)
                     if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
                     {
                        SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                        SB_ENTERTEST( sbAccCb.curTst.bTSapMask, BIT0 )
                     }
                  }
                  break;
               /* sb032.102 :  IPV6 Support Added */
               case 5:   /* Test O.102.05: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_TSAPCFG(SAP_1)
                     if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
                     {
                        SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                        SB_ENTERTEST( sbAccCb.curTst.bTSapMask, BIT0 )
                     }
                  }
                  break;
               case 6:   /* Test O.102.06: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
/* sb066.102: dns flag is set */
                     sbAccCb.useDnsFlag = TRUE;
                     SB_TSAPCFG(SAP_1)
                     if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
                     {
                        SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                        SB_ENTERTEST( sbAccCb.curTst.bTSapMask, BIT0 )
                     }
                  }
                  break;
               /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
               case 7:   /* Test O.102.07: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_TSAPCFG(SAP_1)
                     if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
                     {
                        SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                        SB_ENTERTEST( sbAccCb.curTst.bTSapMask, BIT0 )
                     }
                  }
                  break;
               case 8:   /* Test O.102.08: Pretest/Setup */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_TSAPCFG(SAP_1)
                     if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
                     {
                        SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                        SB_ENTERTEST( sbAccCb.curTst.bTSapMask, BIT0 )
                     }
                  }
                  break;
#endif /* SB_FTHA */
               default:
                  sbAccDispErrTstRslt("Pretest:  ", 0,0, NO_TEST,0);
                  SB_SUBTESTFAIL()
                  break;
            } /* end curtstnum */
         } /* end if debugMask */
      } /*end if configMask */
   }

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
            sbMgmt.t.cntrl.action =  AUBND_DIS;

            switch(curtstnum)
            {
               case 1:    /*Test O.102.01: Execution */
                  switch (sbAccCb.curTst.subTest)
                  {
                     case 1:
                        sbMgmt.t.cntrl.sapId =  SUID_0;
                        sbMgmt.hdr.transId = 10201;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                        sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                        setResponse(&sbMgmt.hdr.response);
                        (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_DISC_REQ;   /* expected result */
                        break;
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                     case 2:
                        (Void) HiUiHitDiscCfm(&sbAccCb.hiPst, SUID_0,
                                              HI_USER_CON_ID,
                                              sbAccCb.curTst.suConId,
                                              HI_CLOSE);
                        sbAccCb.curTst.evtType = ACC_EVT_DISC_REQ;   /* expected result */
                        break;
#endif
                  }
                  break;
               case 2:        /*Test O.102.02: Execution */
                  sbMgmt.t.cntrl.sapId =  SUID_2;  /* TSAP3 */
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                  setResponse(&sbMgmt.hdr.response);
                  (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                  sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                  break;
               case 3:       /*Test O.102.03: Execution */
                  sbMgmt.t.cntrl.sapId =  SUID_1;
                  sbMgmt.hdr.transId = 10203;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                  sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                  setResponse(&sbMgmt.hdr.response);
                  (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                  sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;
                  break;
               case 4:       /*Test O.102.04: Execution */
                  switch (sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb012.103: fix for TSAP Unbind Issue */
                        if ( !(isBitSet(sbAccCb.curTst.bTickMask, BIT0)) &&
                              !(isBitSet(sbAccCb.curTst.bTickMask, BIT1)) &&
                                 !(isBitSet(sbAccCb.curTst.bTickMask, BIT2)))
                        {
                          sbMgmt.t.cntrl.sapId =  SUID_0;
                          sbMgmt.hdr.transId = 10204;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                          sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                          sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                          setResponse(&sbMgmt.hdr.response);
                          (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                        }
                        else
                        {
                          (Void) HiUiHitDiscCfm(&sbAccCb.hiPst, SUID_0,
                                               HI_USER_CON_ID,
                                               sbAccCb.curTst.suConId,
                                               HI_CLOSE);
                        }
                        break;
                     case 2:
                        sbStdTSapCfg(&sbMgmt, SAP_1);
                        sbAccCb.curTst.curTransId = 10204;
                        sbMgmt.t.cfg.s.tSapCfg.reConfig.tIntTmr = 100;
                        setResponse(&sbMgmt.hdr.response);
                        (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_CFG_CFM;
                        break;
                     case 3:
                        sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
                        sbMgmt.t.cntrl.action =  ABND_ENA;
                        sbMgmt.t.cntrl.sapId =  SUID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                        sbMgmt.hdr.transId = 10204;
                        sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                        setResponse(&sbMgmt.hdr.response);
                        (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 4:
                        (Void) HiUiHitBndCfm(&sbAccCb.hiPst, SUID_0, CM_BND_OK);
                        sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;   /* expected result */
                        break;
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                     case 5:
                        (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0,
                                             sbAccCb.curTst.suConId,
                                             sbAccCb.curTst.spConId,
                                             &sbAccCb.curTst.localTAddr);
                        sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;
                        break;
                     case 6:
                        (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0,
                                             sbAccCb.curTst.suConId,
                                             sbAccCb.curTst.spConId,
                                             &sbAccCb.curTst.localTAddr);
                        sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;
                        break;
                 /* SB_VER13 - Added for version 13  */
                     case 7:
#else
                     case 5:
#endif
                        dns_suConId = sbGlobalCb.dnsInfo.suConId;
                        dns_spConId = sbGlobalCb.dnsInfo.spConId;
                        tAddr.type = CM_TPTADDR_IPV4;
                        tAddr.u.ipv4TptAddr.address = CM_INET_INADDR_ANY;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                        tAddr.u.ipv4TptAddr.port  = SB_MIN_REG_PORT;
#else
                        tAddr.u.ipv4TptAddr.port  = SB_PORT_ANY;
#endif
                        (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0, dns_suConId,
                                           dns_spConId, &tAddr);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_REQ;
                        break;
                  } /* end subTstnum of test 4 */
                  break;
               case 6:       /*Test O.102.06: Execution */
                  /* sb032.102 :  IPV6 Support Added */
                  switch (sbAccCb.curTst.subTest)
                  {
/* sb012.103: fix for TSAP Unbind Issue */
                     case 1:
                        if ( !(isBitSet(sbAccCb.curTst.bTickMask, BIT0)) &&
                              !(isBitSet(sbAccCb.curTst.bTickMask, BIT1)) &&
                                 !(isBitSet(sbAccCb.curTst.bTickMask, BIT2)))
                        {
                          sbMgmt.t.cntrl.sapId =  SUID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                          sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                          sbMgmt.hdr.transId = 10206;
                          sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                          setResponse(&sbMgmt.hdr.response);
                          (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                        }
                        else
                        {
                          (Void) HiUiHitDiscCfm(&sbAccCb.hiPst, SUID_0,
                                               HI_USER_CON_ID,
                                               sbAccCb.curTst.suConId,
                                               HI_CLOSE);
                        }
                        break;
                     case 2:
                        sbStdTSapCfg(&sbMgmt, SAP_1);
                        sbAccCb.curTst.curTransId = 10206;
                        sbMgmt.t.cfg.s.tSapCfg.reConfig.tIntTmr = 100;
                        setResponse(&sbMgmt.hdr.response);
                        (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_CFG_CFM;
                        break;
                     case 3:
                        sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
                        sbMgmt.t.cntrl.action =  ABND_ENA;
                        sbMgmt.t.cntrl.sapId =  SUID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                        sbMgmt.hdr.transId = 10206;
                        sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                        setResponse(&sbMgmt.hdr.response);
                        (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 4:
                        (Void) HiUiHitBndCfm(&sbAccCb.hiPst, SUID_0, CM_BND_OK);
                        sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;   /* expected result */
                        break;
                     case 5:
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                        (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0,
                                             sbAccCb.curTst.suConId,
                                             sbAccCb.curTst.spConId,
                                             &sbAccCb.curTst.localTAddr);
                        sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;
                        break;
                     case 6:
                        (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0,
                                             sbAccCb.curTst.suConId,
                                             sbAccCb.curTst.spConId,
                                             &sbAccCb.curTst.localTAddr);
                        sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;
                        break;
                 /* SB_VER13 - Added for version 13  */
                     case 7:
#endif
                        dns_suConId = sbGlobalCb.dnsInfo.suConId;
                        dns_spConId = sbGlobalCb.dnsInfo.spConId;
                        tAddr.type = CM_TPTADDR_IPV4;
                        tAddr.u.ipv4TptAddr.address = CM_INET_INADDR_ANY;
                        tAddr.u.ipv4TptAddr.port  = SB_PORT_ANY;
                        (Void) HiUiHitConCfm(&sbAccCb.hiPst, SUID_0, dns_suConId,
                                           dns_spConId, &tAddr);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;
                        break;
                  } /* end subTstnum of test 4 */
                  break;
               case 5:    /*Test O.102.05: Execution */
                  switch (sbAccCb.curTst.subTest)
                  {
                     case 1:
                        sbMgmt.t.cntrl.sapId =  SUID_0;
                        sbMgmt.hdr.transId = 10205;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                        sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                        setResponse(&sbMgmt.hdr.response);
                        (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_DISC_REQ;   /* expected result */
                        break;

/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                     case 2:
                        (Void) HiUiHitDiscCfm(&sbAccCb.hiPst, SUID_0,
                                              HI_USER_CON_ID,
                                              sbAccCb.curTst.suConId,
                                              HI_CLOSE);
                        sbAccCb.curTst.evtType = ACC_EVT_DISC_REQ;   /* expected result */
#endif
                        break;
                  }
                  break;
               /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
               case 7:    /*Test O.102.07: Execution */
               {
                  ShtCntrlReqEvnt  reqInfo;
                  switch (sbAccCb.curTst.subTest)
                  {
                     case 1:
                        setResponse(&reqInfo.hdr.response);
                        reqInfo.reqType = SHT_REQTYPE_UBND_DIS;
                        reqInfo.s.bndEna.grpType = SHT_GRPTYPE_ALL;
                        reqInfo.s.bndEna.dstProcId = SFndProcId();
                        reqInfo.s.bndEna.dstEnt.ent = ENTHI;
                        reqInfo.s.bndEna.dstEnt.inst = TSTINST_0;
                        reqInfo.hdr.response.selector = 0;
                        /* send an sht request primitive*/
                        cmPkMiShtCntrlReq(&sbAccCb.shtPst, &reqInfo);

                        sbAccCb.curTst.evtType = ACC_EVT_DISC_REQ;   /* expected result */
                        break;
                     case 2:
                        (Void) HiUiHitDiscCfm(&sbAccCb.hiPst, SUID_0,
                                              HI_USER_CON_ID,
                                              sbAccCb.curTst.suConId,
                                              HI_CLOSE);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                        break;
                  }
                  break;
               }
               case 8:    /*Test O.102.08: Execution */
               {
                  ShtCntrlReqEvnt  reqInfo;
                  switch (sbAccCb.curTst.subTest)
                  {
                     case 1:
                        setResponse(&reqInfo.hdr.response);
                        reqInfo.reqType = SHT_REQTYPE_UBND_DIS;
                        reqInfo.s.bndEna.grpType = SHT_GRPTYPE_ENT;
                        reqInfo.s.bndEna.dstProcId = SFndProcId();
                        reqInfo.s.bndEna.dstEnt.ent = ENTHI;
                        reqInfo.s.bndEna.dstEnt.inst = TSTINST_0;
                        reqInfo.hdr.response.selector = 0;
                        /* send an sht request primitive*/
                        cmPkMiShtCntrlReq(&sbAccCb.shtPst, &reqInfo);

                        sbAccCb.curTst.evtType = ACC_EVT_DISC_REQ;   /* expected result */
                        break;
                     case 2:
                        (Void) HiUiHitDiscCfm(&sbAccCb.hiPst, SUID_0,
                                              HI_USER_CON_ID,
                                              sbAccCb.curTst.suConId,
                                              HI_CLOSE);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                        break;
                  }
                  break;
               }
#endif /* SB_FTHA */
            } /* end curtstnum #1 */
            sbAccCb.curTst.state++;
            break;

         /* Dequeue response and test */
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
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            {
               reason = 0;
               /* fill the mgmt */
               switch(curtstnum)
               {
                  case 1:    /*Test O.102.01: Expected results */
                     switch (sbAccCb.curTst.subTest)
                     {
                        case 1:
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                           oper.hi.spId = SPID_0;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_DISC_REQ, &status,
                                             &reason);
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_DISC_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_DISC_REQ, &status, &reason);
                           }
                           else if (msg->evntType == ACC_EVT_CNTRL_CFM)
#endif
                           {
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           break;
                     }
                     break;
                  case 2:    /*Test O.102.02: Expected Results */
                     switch (sbAccCb.curTst.subTest)
                     {     /* document the unbound SAPs */
                        case 1:
                           mgmt.cfm.status = LCM_PRIM_NOK;
                           mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                           ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                             ACC_EVT_CNTRL_CFM);
                           break;
                     }
                     break;
                  case 3:   /*Test O.102.03: Expected Results */
                     switch (sbAccCb.curTst.subTest)
                     {     /* document the unbound SAPs */
                        case 1:
                           mgmt.cfm.status = LCM_PRIM_NOK;
                           mgmt.cfm.reason = LCM_REASON_INVALID_STATE;
                           ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                             ACC_EVT_CNTRL_CFM);
                           break;
                     }
                     break;
                  case 4:       /*Test O.102.04: Expected Results */
                     switch (sbAccCb.curTst.subTest)
                     {     /* document the unbound SAPs */
                        case 1:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_CNTRL_CFM)
                           {
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                                ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else if ( msg->evntType == ACC_EVT_DISC_REQ )
                           {
                              oper.hi.spId = SPID_0;
                              oper.hi.suConId = SUCONID_0;
                              ret = sbHitChkReq(&oper, &mgmt,
                                                ACC_EVT_DISC_REQ, &status,
                                                &reason);
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                              if (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)
                              {
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              else if (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE)
                              {
                                 setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
#endif
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 2:
                           mgmt.transId = sbAccCb.curTst.curTransId;
                           mgmt.cfm.status = LCM_PRIM_OK;
                           mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                           ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                             ACC_EVT_CFG_CFM);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_BND_REQ)
                           {
                              oper.hi.suId =  SUID_0;
                              oper.hi.spId =  SPID_0;
                              ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                           {
                              mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                                ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                        case 4:
                           oper.hi.spId = SPID_0;
                           oper.hi.suConId = SUCONID_0;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_SERVOPEN_REQ, &status,
                                             &reason);
                           break;
                        case 5:
                           oper.hi.spId = SPID_0;
                           oper.hi.suConId = SUCONID_0;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_SERVOPEN_REQ, &status,
                                             &reason);
                           break;

                    /* SB_VER13 - Added for verions 13 */
                        case 6:
#else
                        case 4:
#endif
                           oper.hi.spId = SPID_0;
                           oper.hi.suConId = sbGlobalCb.dnsInfo.suConId;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_SERVOPEN_REQ, &status,
                                             &reason);
                           break;

/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                        case 7:
#else
                        case 5:
#endif
                           mgmt.transId = sbAccCb.curTst.curTransId;
                           mgmt.cfm.status = LCM_PRIM_OK;
                           mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                           ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                             ACC_EVT_CNTRL_CFM);
                           break;
                     }
                     break;
                  /* sb032.102 :  IPV6 Support Added */
                  case 6:       /*Test O.102.06: Expected Results */
                     switch (sbAccCb.curTst.subTest)
                     {     /* document the unbound SAPs */
                        case 1:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_CNTRL_CFM)
                           {
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                                ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else if ( msg->evntType == ACC_EVT_DISC_REQ )
                           {
                              oper.hi.spId = SPID_0;
                              oper.hi.suConId = SUCONID_0;
                              ret = sbHitChkReq(&oper, &mgmt,
                                                ACC_EVT_DISC_REQ, &status,
                                                &reason);
                              if (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)
                              {
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                              else if (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE)
                              {
                                 setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
#endif
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 2:
                           mgmt.transId = sbAccCb.curTst.curTransId;
                           mgmt.cfm.status = LCM_PRIM_OK;
                           mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                           ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                             ACC_EVT_CFG_CFM);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_BND_REQ)
                           {
                              oper.hi.suId =  SUID_0;
                              oper.hi.spId =  SPID_0;
                              ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                           {
                              mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                                ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 4:
                           oper.hi.spId = SPID_0;
                           oper.hi.suConId = SUCONID_0;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_SERVOPEN_REQ, &status,
                                             &reason);
                           break;
                        case 5:
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
                           oper.hi.spId = SPID_0;
                           oper.hi.suConId = SUCONID_0;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_SERVOPEN_REQ, &status,
                                             &reason);
                           break;

                    /* SB_VER13 - Added for verions 13 */
                        case 6:
                           oper.hi.spId = SPID_0;
                           oper.hi.suConId = sbGlobalCb.dnsInfo.suConId;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_SERVOPEN_REQ, &status,
                                             &reason);
                           break;

                        case 7:
#endif
                           mgmt.transId = sbAccCb.curTst.curTransId;
                           mgmt.cfm.status = LCM_PRIM_OK;
                           mgmt.cfm.reason = LCM_REASON_NOT_APPL;
/*sb066.102: changed the accepted  event to ACC_EVT_CNTRL_CFM */
                           ret = sbLsbChkCfm(&mgmt, &status, &reason,
                                             ACC_EVT_CNTRL_CFM);
                           break;
                     }
                     break;
                  case 5:    /*Test O.102.05: Expected results */
                     switch (sbAccCb.curTst.subTest)
                     {
                        case 1:
#ifndef SB_SOL10_MULTIPORT
                           oper.hi.spId = SPID_0;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_DISC_REQ, &status,
                                             &reason);
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_DISC_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_DISC_REQ, &status, &reason);
                           }
                           else if (msg->evntType == ACC_EVT_CNTRL_CFM)
#endif
                           {
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           break;
                     }
                     break;
                  /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
                  case 7:    /*Test O.102.07: Expected results */
                     switch (sbAccCb.curTst.subTest)
                     {
                        case 1:
                           oper.hi.spId = SPID_0;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_DISC_REQ, &status,
                                             &reason);
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_DISC_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_DISC_REQ, &status, &reason);
                           }
                           else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                           {
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                           {
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           break;
                     }
                     break;
                  case 8:    /*Test O.102.08: Expected results */
                     switch (sbAccCb.curTst.subTest)
                     {
                        case 1:
                           oper.hi.spId = SPID_0;
                           ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_DISC_REQ, &status,
                                             &reason);
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_DISC_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_DISC_REQ, &status, &reason);
                           }
                           else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                           {
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                           {
                              mgmt.cfm.status = LCM_PRIM_OK;
                              mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                              mgmt.transId = sbAccCb.curTst.curTransId;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           break;
                     }
                     break;
#endif /* SB_FTHA */
               }    /*end curtstnum #2 switch */

               if (ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {     /* Subtest successful */
                  sbAccCb.curTst.subTestsPass++;
               }
            }/*end else/if primitive received */
            if ( (curtstnum ==1)  )
            {
               if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                    ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
               else if (sbAccCb.curTst.subTest == 1)
               {
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.subTest++;
               }
#endif

            }
            /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
            else if ( (curtstnum ==7) || (curtstnum ==8) )
            {
               if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                    ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
               else if (sbAccCb.curTst.subTest == 1)
               {
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.subTest++;
               }
            }
#endif /* SB_FTHA */
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
           /* sb032.102 :  IPV6 Support Added */
            else if ( ((curtstnum == 4) && (sbAccCb.curTst.subTest == 1)) || ((curtstnum == 6) && (sbAccCb.curTst.subTest == 1)))
            {
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)&&
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
            
/* sb012.103: fix for TSAP Unbind Issue */
            else if ( ((curtstnum == 4) && (sbAccCb.curTst.subTest == 1)) ||
                        ((curtstnum == 6) && (sbAccCb.curTst.subTest == 1)))
               {
                  sbAccCb.curTst.state = 0;
               }
            }

#else
            /* sb032.102 :  IPV6 Support Added */
            else if ( ((curtstnum == 4) && (sbAccCb.curTst.subTest == 1)))
            {
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE))
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
            }

            else if (((curtstnum == 6) && (sbAccCb.curTst.subTest == 1)))
            {
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
            }
#endif

            /* sb032.102 :  IPV6 Support Added */
            else if ( ((curtstnum == 4) && (sbAccCb.curTst.subTest == 3)) || ((curtstnum == 6) && (sbAccCb.curTst.subTest == 3)))
            {
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
            }
            else
            {
               sbAccCb.curTst.state++;
               sbAccCb.curTst.subTest++;
            }
            break;

         case 2: /* Do cleanup before next test */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
               sbAccCb.useDnsFlag = FALSE;
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test/subtest */
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbHitUBindTst */


/* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
/*
*       Fun:   sbShtCntrlTst
*
*       Desc:  Test cases for Rolling Upgrade Feature
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes:
*
*       File:  sb_act2.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbShtCntrlTst
(
U8   curtstnum,              /* number of current test within test group  */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbShtCntrlTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group  */
S8  *numstr;       /* test number */
#endif
{
   SbAccMsgQElm   *msg;
   SbMgmtQElm     mgmt;
   PRIVATE        SbMgmt         sbMgmt;
   SctStatus      status;
   Reason         reason;
   S16            ret;


   TRC2(sbShtCntrlTst)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      switch(curtstnum)                           /* Pretests continues */
      {
         case 1:   /* Test O.101.06: Pretest/Setup */
            SB_GENCFG()
            SB_ENABLE_DEBUGP(0xffffffff)
            if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
            {
                SB_TSAPCFG(SAP_1)
                SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
            }
            break;
         case 2:   /* Test O.101.07: Pretest/Setup */
            SB_GENCFG()
            SB_ENABLE_DEBUGP(0xffffffff)
            if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
            {
                SB_SCTSAPCFG(SAP_1)
                SB_TSAPCFG(SAP_1)
                /*
                SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                */
                SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
            }
            break;
         case 3:   /* Test O.101.08: Pretest/Setup */
            SB_GENCFG()
            SB_ENABLE_DEBUGP(0xffffffff)
            if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
            {
                SB_SCTSAPCFG(SAP_1)
                SB_TSAPCFG(SAP_1)
                SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
            }
            break;
         case 4:   /* Test O.101.9: Pretest/Setup */
            sbStdGenCfg(&sbMgmt); 
/* sb003.103: Moved from GenCfg to General reConfig structure */ 
/* sb004.103: Protected under compile-time flag */
#ifdef LSB9
            sbMgmt.t.cfg.s.genCfg.reConfig.smPst.intfVer = LSBIFVER-1;
#else
            sbMgmt.t.cfg.s.genCfg.smPst.intfVer = LSBIFVER-1;
#endif
            sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
            SB_ENTERTEST( sbAccCb.curTst.bConfigMask, BIT0 )
            break;
         case 5:   /* Test O.101.10: Pretest/Setup */
            SB_GENCFG()
            SB_SCTSAPCFG(SAP_1)
            sbStdTSapCfg(&sbMgmt, SAP_1);  
            sbMgmt.t.cfg.s.tSapCfg.reConfig.remIntfValid = FALSE;
            sbMgmt.t.cfg.s.tSapCfg.reConfig.remIntfVer = HITIFVER;
            sbSendConfigReq(&sbMgmt, STSBTSAP, SAP_1); 
            SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
            break;
        default:
            sbAccDispErrTstRslt("Pretest:  ", 0,0, NO_TEST,0);
            SB_SUBTESTFAIL()
            break;
      }

      if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
      {
         SB_DISABLE_TRACE()
      } /*end switch curtstnum */
   }/*end pretest config */


   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
       case 0:
          switch(curtstnum)
          {
            case 1:         /*Test O.101.06: Execution */
               if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)){
                  sbShtCntrlReq(SHT_REQTYPE_GETVER, 0, 0, 0, 0, 0, 0);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                   sbAccCb.curTst.tickLstDoneFlg = FALSE;
                 }
               break;
               
            case 2:         /*Test O.101.07: Execution */
               if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)){
                  sbShtCntrlReq(SHT_REQTYPE_SETVER, SHT_GRPTYPE_ALL, SFndProcId(), ENTHI, TSTINST_0, HITIF, HITIFVER);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; 
                   sbAccCb.curTst.tickLstDoneFlg = FALSE;
                 }
               break;

            case 3:         /*Test O.101.08: Execution */
               {
                  SbSctSapCb *sctSap;

                  sctSap = sbGlobalCb.sctSaps[0];
                  if ((sctSap->remIntfValid != TRUE) ||
                      (sctSap->sctPst.intfVer != SCTIFVER))
                      
                  {
                     ret = RFAILED;
                     reason = 4;
                  }
                   (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_0, SPID_0);
                   sbAccCb.curTst.evtType = ACC_EVT_BND_CFM;  
               }
               break;
            case 4:         /*Test O.101.09: Execution */
/* sb003.103: Moved from GenCfg to General reConfig structure */ 
/* sb004.103: Protected under compile-time flag */
#ifdef LSB9
               if (sbGlobalCb.genCfg.reConfig.smPst.intfVer != LSBIFVER-1)
#else
               if (sbGlobalCb.genCfg.smPst.intfVer != LSBIFVER-1)
#endif
               {
                  ret = RFAILED;
                  reason = 4;
               }
               sbAccCb.curTst.state++;
               break;
            case 5:         /*Test O.101.10: Execution */
               if ((sbGlobalCb.tSaps[0])->tSapCfg.reConfig.remIntfValid != FALSE)
               {
                  ret = RFAILED;
                  reason = 4;
               }
               sbAccCb.curTst.state++;
               break;
          } /* end curtstnum switch #1 */
          sbAccCb.curTst.state++;
          break;
         /* Dequeue response and test */
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
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
               reason = 0;
               /* fill the mgmt */
              switch(curtstnum)
              {
                 case 1:  /*Test O.101.06: Expected Results */
                    sbAccPeekMsg(&msg);
                    if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                    {
                       mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                       mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                       mgmt.transId = sbAccCb.curTst.curTransId;
                       ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                       setBit(&sbAccCb.curTst.bTickMask, BIT1);

                       /* this test is done */
                       if (ret == ROK)
                       {
                          sbAccCb.curTst.state = 13;
                          break;
                       }
                    }
                    
                    break;
                 case 2:  /*Test O.101.07: Expected Results */
                    sbAccPeekMsg(&msg);
                    if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                    {
                       mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                       mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                       mgmt.transId = sbAccCb.curTst.curTransId;
                       ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                       /* check the version info */
                       if ((sbGlobalCb.numIntfInfo != 1) ||
                           (sbGlobalCb.intfInfo[0].intf.intfId != HITIF) ||
                           (sbGlobalCb.intfInfo[0].intf.intfVer != HITIFVER))
                       {
                          ret = RFAILED;
                          reason = 3;
                       }
                       else
                       {
                          SbTSapCb *tSap;
                          tSap = sbGlobalCb.tSaps[0];
                          if (tSap->remIntfValid != TRUE)
                          {
                             ret = RFAILED;
                             reason = 4;
                          }
                       }
                    }
                    break;
                 case 3:  /*Test O.101.08: Expected Results */
                    {
                       SbOperQElm  oper;
                       oper.it.suId = SUID_0;
                       oper.it.result = CM_BND_OK;
                       ret = sbSctChkCfm(&oper, NULLP, ACC_EVT_BND_CFM, &status, &reason);
                    }
                    break;
               }/* end curtstnum switch */

               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }
            } /*end if/else primitive received */
            sbAccCb.curTst.state++;
            break;
       case 2:
          switch(curtstnum)
          {
            case 2:         /*Test O.101.07: Execution */
               if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)){
                  sbShtCntrlReq(SHT_REQTYPE_SETVER, SHT_GRPTYPE_ALL, SFndProcId(), ENTIT, TSTINST_0, SCTIF, SCTIFVER);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                   sbAccCb.curTst.tickLstDoneFlg = FALSE;
                 }
                break;
            case 3:         /*Test O.101.08: Execution */
                setResponse(&sbMgmt.hdr.response);
                sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
                sbMgmt.t.ssta.sapId = SPID_0;
                (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);

                sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;
                break;
            case 4:         /*Test O.101.09: Execution */
               (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_3, SPID_1);
               sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
               break;
            case 5:         /*Test O.101.10: Execution */
               sbMgmt.t.cntrl.sapId =  SUID_0;
               sbMgmt.t.cntrl.action =  ABND_ENA;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.transId = 10101;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               setResponse(&sbMgmt.hdr.response);
               (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;
               break;

          } /* end curtstnum switch #1 */
          sbAccCb.curTst.state++;
          break;
         /* Dequeue response and test */
       case 3:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
              reason = 0;
              /* fill the mgmt */
              switch(curtstnum)
              {
                 case 2:  /*Test O.101.07: Expected Results */
                    sbAccPeekMsg(&msg);
                    if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                    {
                       mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                       mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                       mgmt.transId = sbAccCb.curTst.curTransId;
                       ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                       /* check the version info */
                       if ((sbGlobalCb.numIntfInfo != 2) ||
                           (sbGlobalCb.intfInfo[1].intf.intfId != SCTIF) ||
                           (sbGlobalCb.intfInfo[1].intf.intfVer != SCTIFVER))
                       {
                          ret = RFAILED;
                          reason = 3;
                       }
                       else
                       {
                          SbSctSapCb *sctSap;
                          sctSap = sbGlobalCb.sctSaps[0];
                          /* the Sap is not bounded */
                          if (sctSap->remIntfValid != TRUE)
                          {
                             ret = RFAILED;
                             reason = 4;
                          }
                       }

                       setBit(&sbAccCb.curTst.bTickMask, BIT1);
                    }
                    break;
                 case 3:  /*Test O.101.08: Expected Results */
                    mgmt.cfm.status = LCM_PRIM_OK;
                    mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                    mgmt.transId = sbAccCb.curTst.curTransId;
                    ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                    if ((mgmt.s.ssta.s.sapSta.remIntfValid !=  TRUE) || (mgmt.s.ssta.s.sapSta.selfIfVer != SCTIFVER))
                    {
                       ret    = RFAILED;
                       status = INV_STATE;
                    }
                    break;
                 case 4:  /*Test O.101.09: Expected Results */
                    sbAccPopMsg(&msg);
                    if ((msg->evntType != ACC_EVT_STA_IND) ||
                        (msg->t.mgmtMsg.s.usta.event != LCM_EVENT_UI_INV_EVT) ||
                        (msg->t.mgmtMsg.s.usta.cause !=LCM_CAUSE_INV_SAP ) ||
                        (msg->t.mgmtMsg.s.usta.pst.intfVer !=SCTIFVER-1))

                    {
                       ret    = RFAILED;
                       status = INV_STATE;
                    }
                    sbAccCb.curTst.state = 13;
                    break;
                 case 5:  /*Test O.101.10: Expected Results */
                    sbAccPeekMsg(&msg);
                    if (msg->evntType == ACC_EVT_CNTRL_CFM)
                    {
                       mgmt.cfm.status = LCM_PRIM_NOK;
                       mgmt.cfm.reason = LCM_REASON_SWVER_NAVAIL;
                       mgmt.transId = sbAccCb.curTst.curTransId;
                       ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                       setBit(&sbAccCb.curTst.bTickMask, BIT1);
                    }
                    else
                    {
                       status = INC_EVNTTYPE;
                       setBit(&sbAccCb.curTst.bTickMask, BIT1);
                       setBit(&sbAccCb.curTst.bTickMask, BIT0);
                       ret = RFAILED;
                    }
                    break;
               }/* end curtstnum switch */

               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }
            } /*end if/else primitive received */
            sbAccCb.curTst.state++;
            break;
       case 4:
          switch(curtstnum)
          {
            case 2:         /*Test O.101.07: Execution */
               (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_0, SPID_0);
               sbAccCb.curTst.evtType = ACC_EVT_BND_CFM;

               break;
            case 3:         /*Test O.101.08: Execution */
            {
               SbSctSapCb *sctSap;
               SB_SCTSAPCFG(SAP_5)

               sctSap = sbGlobalCb.sctSaps[0];
               if ((sctSap->remIntfValid != TRUE) ||
                   (sctSap->sctPst.intfVer != SCTIFVER-1))
                   
               {
                  ret = RFAILED;
                  reason = 4;
               }
               sbAccCb.curTst.state = 13;
               break;
            }
            case 5:         /*Test O.101.10: Execution */
               sbStdTSapCfg(&sbMgmt, SAP_1);  
               sbMgmt.t.cfg.s.tSapCfg.reConfig.remIntfValid = TRUE;
               sbMgmt.t.cfg.s.tSapCfg.reConfig.remIntfVer = HITIFVER-1;

               sbAccCb.curTst.state = 0;
               sbSendConfigReq(&sbMgmt, STSBTSAP, SAP_1); 

               if (sbGlobalCb.tSaps[0]->remIntfValid != FALSE)
               {
                  ret = RFAILED;
                  reason = 4;
               }
               sbAccCb.curTst.state = 5;
               break;
          }
          sbAccCb.curTst.state++;
          break;
         /* Dequeue response and test */
       case 5:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
               reason = 0;
               /* fill the mgmt */
              switch(curtstnum)
              {
                 case 2:  /*Test O.101.07: Expected Results */
                    {
                       SbOperQElm  oper;
                       SbSctSapCb *sctSap;

                       oper.it.suId = SUID_0;
                       oper.it.result = CM_BND_OK;
                       ret = sbSctChkCfm(&oper, NULLP, ACC_EVT_BND_CFM, &status, &reason);
                       sctSap = sbGlobalCb.sctSaps[0];
                       /* the Sap is not bounded */
                       if ((sctSap->remIntfValid != TRUE) ||
                           (sctSap->sctPst.intfVer != SCTIFVER))
                       {
                          ret = RFAILED;
                          reason = 4;
                       }
                    }
                    break;
               }/* end curtstnum switch */

               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }
            } /*end if/else primitive received */
            sbAccCb.curTst.state++;
            break;
       case 6:
          switch(curtstnum)
          {
            case 2:         /*Test O.101.07: Execution */
                  sbShtCntrlReq(SHT_REQTYPE_SETVER, SHT_GRPTYPE_ALL, SFndProcId()+1, ENTIT, TSTINST_0, SCTIF, SCTIFVER-1);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                   sbAccCb.curTst.tickLstDoneFlg = FALSE;
               break;
            case 5:         /*Test O.101.10: Execution */
               sbMgmt.t.cntrl.sapId =  SUID_0;
               sbMgmt.t.cntrl.action =  ABND_ENA;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.transId = 10101;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               setResponse(&sbMgmt.hdr.response);
               (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_BND_REQ;
               sbAccCb.curTst.bTickMask = 0;
               break;
          } /* end curtstnum switch #1 */
          sbAccCb.curTst.state++;
          break;
         /* Dequeue response and test */
       case 7:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
               reason = 0;
               /* fill the mgmt */
              switch(curtstnum)
              {
                 case 2:  /*Test O.101.07: Expected Results */
                    sbAccPeekMsg(&msg);
                    if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                    {
                       mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                       mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                       mgmt.transId = sbAccCb.curTst.curTransId;
                       ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                       /* check the layer stores the interface version
                        * information */
                       if ((sbGlobalCb.numIntfInfo != 3) ||
                           (sbGlobalCb.intfInfo[2].intf.intfId != SCTIF) ||
                           (sbGlobalCb.intfInfo[2].intf.intfVer != SCTIFVER-1))
                       {
                          ret = RFAILED;
                          reason = 3;
                       }
                       else
                       {
                          SbSctSapCb *sctSap;
                          sctSap = sbGlobalCb.sctSaps[0];
                          /* the Sap should not be changed */
                          if ((sctSap->remIntfValid != TRUE) ||
                              (sctSap->sctPst.intfVer != SCTIFVER))
                          {
                             ret = RFAILED;
                             reason = 4;
                          }
                       }

                    }
                    break;
                 case 5:  /*Test O.101.10: Expected Results */
                    {
                       sbAccPeekMsg(&msg);
                       if (msg->evntType == ACC_EVT_CFG_CFM)
                       {
                          mgmt.cfm.status = LCM_PRIM_OK;
                          mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                          mgmt.transId = sbAccCb.curTst.curTransId;
                          ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM);
                          setBit(&sbAccCb.curTst.bTickMask, BIT1);
                       }
                       else
                       {
                          status = INC_EVNTTYPE;
                          setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          ret = RFAILED;
                       }
                       sbAccCb.curTst.state++;
                    }
                    break;
               }/* end curtstnum switch */

               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }
            } /*end if/else primitive received */
            sbAccCb.curTst.state++;
            break;
       case 8:
            sbMgmt.hdr.elmId.elmnt =  STSBSCTSAP;
            sbMgmt.t.cntrl.action =  AUBND_DIS;

          switch(curtstnum)
          {
            case 2:         /*Test O.101.07: Execution */
               sbMgmt.t.cntrl.sapId =  SUID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                 
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.transId = 10201;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               setResponse(&sbMgmt.hdr.response);
               (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_DISC_REQ; 

               break;
          }
          sbAccCb.curTst.state++;
          break;
         /* Dequeue response and test */
       case 9:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
               reason = 0;
               /* fill the mgmt */
              switch(curtstnum)
              {
                 SbSctSapCb *sctSap;
                 case 2:  /*Test O.101.07: Expected Results */
                    sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_CNTRL_CFM)
                     {
                        mgmt.cfm.status = LCM_PRIM_OK;
                        mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                        mgmt.transId = sbAccCb.curTst.curTransId;
                        ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }

                    sctSap = sbGlobalCb.sctSaps[0];
                    /* the Sap is not bounded */
                    if ((sctSap->remIntfValid != TRUE) ||
                        (sctSap->sapState != SB_SAPSTATE_UBND))
                    {
                       ret = RFAILED;
                       reason = 4;
                    }
                    break;
                 case 5:  /*Test O.101.10: Expected Results */
                    {
                       SbOperQElm  oper;
                       sbAccPeekMsg(&msg);
                       if (msg->evntType == ACC_EVT_BND_REQ)
                       {
                          oper.hi.suId =  SUID_0;
                          oper.hi.spId =  SPID_0;
                          ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                            &status, &reason);
                          setBit(&sbAccCb.curTst.bTickMask, BIT0);
                       }
                       else
                       {
                          status = INC_EVNTTYPE;
                          setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          ret = RFAILED;
                       }
                       sbAccCb.curTst.state++;
                    }
                    break;
               }/* end curtstnum switch */

               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }
            } /*end if/else primitive received */
            if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
            {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.bTickMask = 0;
            }
            sbAccCb.curTst.state++;
            break;
       case 10:
          switch(curtstnum)
          {
            case 2:         /*Test O.101.07: Execution */
                  sbShtCntrlReq(SHT_REQTYPE_SETVER, SHT_GRPTYPE_ALL, SFndProcId()+1, ENTIT, TSTINST_0, SCTIF, SCTIFVER);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                   sbAccCb.curTst.tickLstDoneFlg = FALSE;
               break;
          } /* end curtstnum switch #1 */
          sbAccCb.curTst.state++;
          break;
         /* Dequeue response and test */
       case 11:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
               reason = 0;
               /* fill the mgmt */
              switch(curtstnum)
              {
                 case 2:  /*Test O.101.07: Expected Results */
                    sbAccPeekMsg(&msg);
                    if (msg->evntType == ACC_EVT_SHT_CNTRL_CFM)
                    {
                       mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                       mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                       mgmt.transId = sbAccCb.curTst.curTransId;
                       ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_SHT_CNTRL_CFM);
                       /* check the version info */
                       if ((sbGlobalCb.numIntfInfo != 3) ||
                           (sbGlobalCb.intfInfo[2].dstProcId != SFndProcId()+1) ||
                           (sbGlobalCb.intfInfo[2].intf.intfId != SCTIF) ||
                           (sbGlobalCb.intfInfo[2].intf.intfVer != SCTIFVER))
                       {
                          ret = RFAILED;
                          reason = 3;
                       }

                       setBit(&sbAccCb.curTst.bTickMask, BIT1);
                    }
                    else
                    if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                       ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                       sbAccCb.curTst.tickLstDoneFlg = TRUE;
                    break;
                 case 5:  /*Test O.101.10: Expected Results */
                    {
                       sbAccPeekMsg(&msg);
                       if (msg->evntType == ACC_EVT_CNTRL_CFM)
                       {
                          mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                          mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                          mgmt.transId = sbAccCb.curTst.curTransId;
                          ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                          setBit(&sbAccCb.curTst.bTickMask, BIT2);
                           sbGlobalCb.sbMgmt.hdr.elmId.elmnt = 0;
                       }
                       else
                       {
                          status = INC_EVNTTYPE;
                          setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          ret = RFAILED;
                       }
                       sbAccCb.curTst.tickLstDoneFlg = TRUE;
                       sbAccCb.curTst.state = 13;
                       sbAccFlushQ();
                    }
                    break;
               }/* end curtstnum switch */

               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }
            } /*end if/else primitive received */
            if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
            {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.bTickMask = 0;
            }
            sbAccCb.curTst.state++;
            break;
       case 12:
          switch(curtstnum)
          {
             Pst pst;
            case 2:         /*Test O.101.07: Execution */
               cmMemcpy((U8*)&pst, (U8*)&sbAccCb.itPst, sizeof(Pst));
               pst.srcProcId = SFndProcId() + 1;
               (Void) ItLiSctBndReq(&pst, SUID_0, SPID_0);
               sbAccCb.curTst.evtType = ACC_EVT_BND_CFM;   /* expected result */
               break;
          }
          sbAccCb.curTst.state++;
          break;
         /* Dequeue response and test */
       case 13:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if(status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
               reason = 0;
               /* fill the mgmt */
              switch(curtstnum)
              {
                 SbOperQElm  oper;
                 SbSctSapCb *sctSap;
                 case 2:  /*Test O.101.07: Expected Results */
                    oper.it.suId = SUID_0;
                    oper.it.result = CM_BND_OK;
                    ret = sbSctChkCfm(&oper, NULLP, ACC_EVT_BND_CFM, &status, &reason);
                    sctSap = sbGlobalCb.sctSaps[0];
                    /* the Sap is not bounded */
                    if ((sctSap->remIntfValid != TRUE) ||
                        (sctSap->sctPst.intfVer != SCTIFVER))
                    {
                       ret = RFAILED;
                       reason = 4;
                    }
                    break;
               }/* end curtstnum switch */

               if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
               else
               {
                 sbAccCb.curTst.subTestsPass++;
               }
            } /*end if/else primitive received */
            if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
            {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.bTickMask = 0;
            }
            sbAccCb.curTst.state++;
            break;


         case 14: /* Do cleanup before next test */
            sbAccCb.curTst.bTestsCompleted = TRUE;
            sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test/subtest */
            /* Now first delete all config before next test */
            sbAccCb.curTst.bBusyCleanup = TRUE;
            sbAccCb.curTst.state = 0;
            break;
      }/*end switch #1 */
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbShtCntrlTst */
#endif /* SB_RUG */


/********************************************************************30**

         End of file:     sb_act2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:06 2015

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
/main/3      ---      mrw  1. Initial version
/main/3      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
            sb042.102 hl   1. Added change for SHT interface and Rolling
                              Up Grade
            sb044.102 rs   1. DNS Call conditioned.
            sb066.102 kp   1. DNS bit was set and expected event was 
                              changed.
/main/4      ---   rsr/ag  1. Updated for Release of 1.3
            sb003.103 ag   1. Changes for Satellite SCTP feature (under 
                              compile time flag SB_SATELLITE).
                           2. Moved the smPst structure from genCfg to 
                              reConfig structure of general configuration.
            sb004.103 ag   1. Protected the changes for making smPst structure
                              reconfigurable under a new compile time flag LSB9.
            sb009.103 nuX  1. Changes made for SOL10 upgrade, changes made under
                              SB_SOL10_MULTIPORT flag.
            sb012.103 pkaX 1. Fixed the test case for TSAP Unbind issue. 
*********************************************************************91*/
