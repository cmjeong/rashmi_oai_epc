

/********************************************************************20**

     Name:     sb_act3.c - Acceptance Tests for the SCTP layer

     Type:     C source file

     Desc:     C code for acceptance tests test cases.  Includes all the
     association establishment tests.

     File:     sb_act3.c

     Sid:      sb_act3.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:07 2015

     Prg:      hnh

*********************************************************************21*/

/*

  sb_act3.c - Acceptance Tests for the SCTP layer

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
PRIVATE  S16 sbSctEndpTst         ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbSctAssocSndTst_1   ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbSctAssocSndTst_2   ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbSctAssocSndTst_3   ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbSctAssocSndTst_4   ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbSctAssocSndTst_5   ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbSctAssocRcvTst     ARGS((U8 curtstnum, S8  *numstr));
/* sb012.103: Placed the function under the flag LSB12 */
#ifdef LSB12
PRIVATE  S16 sbSctAssocTmrTst_1   ARGS((U8 curtstnum, S8  *numstr));
PRIVATE  S16 sbSctAssocTmrTst_2   ARGS((U8 curtstnum, S8  *numstr));
#endif /* LSB12 */
PRIVATE  S16 sbSctAssocDuplTst_1  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE  S16 sbSctAssocDuplTst_2  ARGS((U8 curtstnum, S8  *numstr ));



/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */


/*
*       Fun:   sbO200_01
*
*       Desc:  Test case : O.200.01
*              Purpose   : Verify successful openings of endpoints.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_01
(
void
)
#else
PUBLIC  S16 sbO200_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200_01)
   curtstnum = 1;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 3;
#else
   sbAccCb.curTst.numSubTst = 2;
#endif
   sbSctEndpTst(curtstnum,"O.200.01");
   RETVALUE(ROK);
} /* end sbO200_01 */

/*
*       Fun:   sbO200_10
*
*       Desc:  Test case : O.200.10
*              Purpose   : Verify successful openings of endpoints.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_10
(
void
)
#else
PUBLIC  S16 sbO200_10(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200_10)
   curtstnum = 10;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 5;
#else
   sbAccCb.curTst.numSubTst = 3;
#endif
   sbSctEndpTst(curtstnum,"O.200.10");
   RETVALUE(ROK);
} /* end sbO200_10 */

/*
*       Fun:   sbO200_07
*
*       Desc:  Test case : O.200.07
*              Purpose   : Verify successful openings of endpoints for IPV6
*              interface address.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_07
(
void
)
#else
PUBLIC  S16 sbO200_07(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200_07)
   curtstnum = 7;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 3;
#else
   sbAccCb.curTst.numSubTst = 2;
#endif
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctEndpTst(curtstnum,"O.200.07");
   RETVALUE(ROK);
} /* end sbO200_07 */


/*
*       Fun:   sbO200_02
*
*       Desc:  Test case : O.200.02
*              Purpose   : Verify unsuccessful opening of endpoints if the
*                          interface address does not correspond to an
*                          available interface on the host.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_02
(
void
)
#else
PUBLIC  S16 sbO200_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C..02.curtstnum */

   TRC2(sbO200_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 2;
   sbSctEndpTst(curtstnum,"O.200.02");
   RETVALUE(ROK);
} /* end sbO200_02 */

/*
*       Fun:   sbO200_03
*
*       Desc:  Test case : O.200.03
*              Purpose   : Verify successful opening of endpoints if the
*                          user attempts to open two endpoints with the same
*                          suEndpId.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_03
(
void
)
#else
PUBLIC  S16 sbO200_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 2;
   sbSctEndpTst(curtstnum,"O.200.03");
   RETVALUE(ROK);
} /* end sbO200_03 */

/*
*       Fun:   sbO200.04
*
*       Desc:  Test case : O.200.04
*              Purpose   : Verify that opening of an endpoint is unsuccessful
*                          if the source address list and port combination
*                          overlaps with the source address list and port
*                          combination of another endpoint on the host.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_04
(
void
)
#else
PUBLIC  S16 sbO200_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200.04)
   curtstnum = 4;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 3;
#else
   sbAccCb.curTst.numSubTst = 2;
#endif
   sbSctEndpTst(curtstnum,"O.200.04");
   RETVALUE(ROK);
} /* end sbO200.04 */

/*
*       Fun:   sbO200_05
*
*       Desc:  Test case : O.200.05
*              Purpose   : Verify successful closing of endpoints.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_05
(
void
)
#else
PUBLIC  S16 sbO200_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200.05)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 2;
   sbSctEndpTst(curtstnum,"O.200.05");
   RETVALUE(ROK);
} /* end sbO200.05 */

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbO200_08
*
*       Desc:  Test case : O.200.08
*              Purpose   : Verify successful closing of endpoints for IPV6 
*              interface address.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_08
(
void
)
#else
PUBLIC  S16 sbO200_08(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200.08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctEndpTst(curtstnum,"O.200.08");
   RETVALUE(ROK);
} /* end sbO200.08 */


   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
/*
*       Fun:   sbO200_09
*
*       Desc:  Test case : O.200.09
*              Purpose   : Verify successful openings of endpoints.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_09
(
void
)
#else
PUBLIC  S16 sbO200_09(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200_09)
   curtstnum = 9;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   sbAccCb.curTst.numSubTst = 4;
#else
   sbAccCb.curTst.numSubTst = 2;
#endif
   sbSctEndpTst(curtstnum,"O.200.09");
   RETVALUE(ROK);
} /* end sbO200_09 */
#endif /* SCT_ENDP_MULTI_IPADDR */

/*
*       Fun:   sbO200_06
*
*       Desc:  Test case : O.200.06
*              Purpose   : Verify unsuccessful closing of endpoints if the
*                          specified endpoint ID is invalid.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO200_06
(
void
)
#else
PUBLIC  S16 sbO200_06(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO200_06)
   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 2;
   sbSctEndpTst(curtstnum,"O.200.06");
   RETVALUE(ROK);
} /* end sbO200_06 */

/*
*       Fun:   sbSctEndpTst
*
*       Desc:  Opening and Closing of Endpoints.
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctEndpTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctEndpTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   PRIVATE       SbMgmtQElm    mgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbOperQElm    oper;
   PRIVATE       SbMgmt        sbMgmt;
   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
   PRIVATE       SctNetAddrLst intfNAddrLst;
#endif
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbAccMsgQElm    *msg;
#endif
   /* sb058.102 : Added to remove compilation warning. */
   U32           netAddr;

   TRC2(sbSctEndpTst)

   ret = ROK;
   /* sb058.102 : Added to remove compilation warning. */
   netAddr = 0;

   /* Pretests/Setup */
   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
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
                     SB_BIND_SCTSAP(SUID_0, SPID_0, BIT0)
                     switch(curtstnum)/* Pretests continues */
                     {  case 1:
                           SB_ENTERTEST(sbAccCb.curTst.bSapMask, BIT0 )
                           break;
                        case 2:
                           SB_ENTERTEST(sbAccCb.curTst.bSapMask, BIT0 )
                           break;
                        case 3: /* pretests: O.200.03 */
                           if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE)
                           {
                              SB_SETUP_ENDPOPENREQ(assoc_1, SPID_0, SUENDPID_0,
                                                   LOCALPORT_0,
                                                   localNAddrLst_1[1])
                              SB_OPEN_ENDP(&assoc_1, BIT0)
                              SB_ENTERTEST(sbAccCb.curTst.bEndpMask, BIT0 )
                           }
                           break;
                        case 4: /* pretests: O.200.04 */
                           if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE)
                           {
                              SB_SETUP_ENDPOPENREQ(assoc_1, SPID_0, SUENDPID_0,
                                                   LOCALPORT_0,
                                                   localNAddrLst_1[1])
                              SB_OPEN_ENDP(&assoc_1, BIT0)
                              SB_ENTERTEST(sbAccCb.curTst.bEndpMask, BIT0 )
                           }
                           break;
                        case 5: /* pretests: O.200.05 */
                           if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE)
                           {
                              SB_SETUP_ENDPOPENREQ(assoc_1, SPID_0, SUENDPID_0 ,\
                                                   LOCALPORT_0,
                                                   sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0].u.ipv4NetAddr)
                              SB_OPEN_ENDP(&assoc_1, BIT0)
                              SB_ENTERTEST(sbAccCb.curTst.bEndpMask, BIT0 )
                           }
                           break;
                        case 6: /* pretests: O.200.06 */
                           if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE) {
                              SB_SETUP_ENDPOPENREQ(assoc_1, SPID_0, SUENDPID_0,
                                                   LOCALPORT_0,
                                                   localNAddrLst_1[1])
                              SB_OPEN_ENDP(&assoc_1, BIT0)
                              SB_ENTERTEST(sbAccCb.curTst.bEndpMask, BIT0 )
                           }
                           break;
                        /* sb032.102 :  IPV6 Support Added */
                        case 7:
                           SB_ENTERTEST(sbAccCb.curTst.bSapMask, BIT0 )
                           break;
                        case 8: /* pretests: O.200.08 */
                           if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE)
                           {
                              SB_SETUP_ENDPOPENREQ(assoc_1, SPID_0, SUENDPID_0 ,\
                                                   LOCALPORT_0,
                                                   sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0].u.ipv6NetAddr)
                              SB_OPEN_ENDP(&assoc_1, BIT0)
                              SB_ENTERTEST(sbAccCb.curTst.bEndpMask, BIT0 )
                           }
                           break;
                        /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
                        case 9:
                           SB_ENTERTEST(sbAccCb.curTst.bSapMask, BIT0 )
                           break;
#endif /* SCT_ENDP_MULTI_IPADDR */
                        case 10: /*-- pretests: O.200.10 --*/
                           SB_ENTERTEST(sbAccCb.curTst.bSapMask, BIT0 )
                           break;
                        default:
                           break;
                     }/*end switch */
                  } /*Tsap end of if */
               } /* TSapCfg end of if*/
            } /* SctSapCfg end of if*/
         } /* Debugp end of if */
      } /* config end of if */
   }  /* end pretests */


   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
               case 1:     /* Test O.200.01: Execution */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                  switch (sbAccCb.curTst.subTest)
		  {
                    case 1:
#endif
                   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
                      intfNAddrLst.nmb = 1;
                      SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[0],
                                        sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0].u.ipv4NetAddr)
                      (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                              SPID_0, SUENDPID_0, LOCALPORT_0,
                                              &intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
                      SB_SETUP_CMNETADDR(assoc_1.localNAddr,
                                        sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0]
.u.ipv4NetAddr)
                     (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                               SPID_0, SUENDPID_0, LOCALPORT_0,
                                               &assoc_1.localNAddr);
#endif /* SCT_ENDP_MULTI_IPADDR */

                     sbAccCb.curTst.evtType = ACC_EVT_ENDPOPEN_CFM;  /*expected result */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     break;
		   case 2:

                       (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                    assoc_1.suId, sbAccCb.curTst.suConId,\
                                    sbAccCb.curTst.spConId,\
                                    &sbAccCb.curTst.localTAddr);
                       break;
		   }
#endif
	         break;

               case 2:     /* Test O.200.02: Execution */
                  /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
                  intfNAddrLst.nmb = 2;
                  /* sb058.102 : Added to remove compilation warning. */
                  netAddr = ACC_ASSOC1_LOCAL_4;
                  SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[0], netAddr)
                  netAddr = ACC_ASSOC1_LOCAL_3;
                  SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[1], netAddr)
                  (void) ItLiSctEndpOpenReq(&sbAccCb.itPst, SPID_0,
                                            SUENDPID_0, LOCALPORT_0,
                                            &intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
                  /* sb058.102 : Added to remove compilation warning. */
                  netAddr = ACC_ASSOC1_LOCAL_4;
                  SB_SETUP_CMNETADDR(assoc_1.localNAddr,  netAddr)
                  (void) ItLiSctEndpOpenReq(&sbAccCb.itPst, SPID_0,
                                            SUENDPID_0, LOCALPORT_0,
                                            &assoc_1.localNAddr);
#endif /* SCT_ENDP_MULTI_IPADDR */
                  sbAccCb.curTst.evtType = ACC_EVT_ENDPOPEN_CFM;
                  break;
               case 3:      /* Test O.200.03: Execution */
                  /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
                  intfNAddrLst.nmb = 1;
                  SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[0], localNAddrLst_1[1])
                  (void) ItLiSctEndpOpenReq(&sbAccCb.itPst, SPID_0,
                                            SUENDPID_0, LOCALPORT_1,
                                            &intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
                  SB_SETUP_CMNETADDR(assoc_1.localNAddr,  localNAddrLst_1[1] )
                  (void) ItLiSctEndpOpenReq(&sbAccCb.itPst, SPID_0,
                                            SUENDPID_0, LOCALPORT_1,
                                            &assoc_1.localNAddr);
#endif /* SCT_ENDP_MULTI_IPADDR */
                  sbAccCb.curTst.evtType = ACC_EVT_ENDPOPEN_CFM;
                  break;
               case 4:      /* Test O.200.04: Execution */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
       	           switch (sbAccCb.curTst.subTest)
                   {
                     case 1:
#endif
                        /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
                        intfNAddrLst.nmb = 1;
                        SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[0], localNAddrLst_1[1])
                        (void) ItLiSctEndpOpenReq(&sbAccCb.itPst, SPID_0,
                                                 SUENDPID_1, LOCALPORT_0,
                                                          &intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
                        SB_SETUP_CMNETADDR(assoc_1.localNAddr,  localNAddrLst_1[1] )
                        (void) ItLiSctEndpOpenReq(&sbAccCb.itPst, SPID_0,
                                            SUENDPID_1, LOCALPORT_0,
                                            &assoc_1.localNAddr);
#endif /* SCT_ENDP_MULTI_IPADDR */
                        sbAccCb.curTst.evtType = ACC_EVT_ENDPOPEN_CFM;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                        break;
		     case 2:
                         (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                      assoc_1.suId, sbAccCb.curTst.suConId,\
                                      sbAccCb.curTst.spConId,\
                                      &sbAccCb.curTst.localTAddr);
                        break;
		     }	
#endif
		     break;
               case 5:        /* Test O.200.05: Execution */
                  (void) ItLiSctEndpCloseReq(&sbAccCb.itPst, SPID_0,
                                             assoc_1.suEndpId, SCT_ENDPID_SU);
                  sbAccCb.curTst.evtType = ACC_EVT_ENDPCLOSE_CFM;
                  break;
               case 6:       /* Test O.200.06: Execution */
                  (void) ItLiSctEndpCloseReq(&sbAccCb.itPst, SPID_0,
                                             SUENDPID_2, SCT_ENDPID_SP);
                  sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                  break;
               /* sb032.102 :  IPV6 Support Added */
               case 7:    /* Test O.200.07: Execution */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                  switch (sbAccCb.curTst.subTest)
                  {
                    case 1:
#endif
#ifdef SCT_ENDP_MULTI_IPADDR
                       intfNAddrLst.nmb = 1;
                       SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[0], 
                                        sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0].u.ipv6NetAddr)
                       (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                               SPID_0, SUENDPID_0, LOCALPORT_0,
                                               &intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
                       SB_SETUP_CMNETADDR(assoc_1.localNAddr,
                                         sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0].u.ipv6NetAddr)
                      (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                                SPID_0, SUENDPID_0, LOCALPORT_0,
                                                &assoc_1.localNAddr);
#endif /* SCT_ENDP_MULTI_IPADDR */
                      sbAccCb.curTst.evtType = ACC_EVT_ENDPOPEN_CFM;  /*expected result */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                      break;
		  case 2:
                       (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                    assoc_1.suId, sbAccCb.curTst.suConId,\
                                    sbAccCb.curTst.spConId,\
                                    &sbAccCb.curTst.localTAddr);
                       break;
                  }
#endif
            
                 break;
               case 8:        /* Test O.200.08: Execution */
                  (void) ItLiSctEndpCloseReq(&sbAccCb.itPst, SPID_0,
                                            assoc_1.suEndpId, SCT_ENDPID_SU);
                  sbAccCb.curTst.evtType = ACC_EVT_ENDPCLOSE_CFM;
                  break;
               /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
               case 9:    /* Test O.200.09: Execution */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                  switch (sbAccCb.curTst.subTest)	       
	          {
		   case 1:
#endif
                     intfNAddrLst.nmb = 2;
                     SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[0],
                     sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0].u.ipv4NetAddr)
                     SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[1],
                     sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[1].u.ipv4NetAddr)
                     (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                             SPID_0, SUENDPID_0, LOCALPORT_0,
                                             &intfNAddrLst);

                     sbAccCb.curTst.evtType = ACC_EVT_ENDPOPEN_CFM;  /*expected result */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                    break;
          	   case 2:
                   (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                   assoc_1.suId, sbAccCb.curTst.suConId,\
                                   sbAccCb.curTst.spConId,\
                                   &sbAccCb.curTst.localTAddr);
                   break;
	         case 3:
                   (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                   assoc_1.suId, sbAccCb.curTst.suConId,\
                                   sbAccCb.curTst.spConId,\
                                   &sbAccCb.curTst.localTAddr);
                   break;
                }
#endif
	        break;
#endif /* SCT_ENDP_MULTI_IPADDR */
               case 10:    /* Test O.200.10: Execution */
                  switch(sbAccCb.curTst.subTest)
                  {
                   case 1:
#ifdef SCT_ENDP_MULTI_IPADDR
                      intfNAddrLst.nmb = 1;
                      SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[0], 
                                         sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0].u.ipv6NetAddr)
                      (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                            SPID_0, SUENDPID_0, SB_PORT_ANY,
                                            &intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
                      SB_SETUP_CMNETADDR(assoc_1.localNAddr,
                                         sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[0]
.u.ipv4NetAddr)
                      (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                                SPID_0, SUENDPID_0, SB_PORT_ANY,
                                                &assoc_1.localNAddr);
#endif
                      sbAccCb.curTst.evtType = ACC_EVT_ENDPOPEN_CFM;  /*expected result */
                      break;
                   case 2:
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                       (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                           assoc_1.suId, sbAccCb.curTst.suConId,\
                                           sbAccCb.curTst.spConId,\
                                           &(sbAccCb.curTst.localTAddr));
		       break;
                   case 3:
#endif
#ifdef SCT_ENDP_MULTI_IPADDR
                      intfNAddrLst.nmb = 1;
                      SB_SETUP_CMNETADDR(intfNAddrLst.nAddr[0], 
                                         sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[1].u.ipv6NetAddr)
                      (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                                SPID_0, SUENDPID_1, SB_PORT_ANY,
                                                &intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
                      SB_SETUP_CMNETADDR(assoc_1.localNAddr,
                                         sbMgmt.t.cfg.s.tSapCfg.srcNAddrLst.nAddr[1]
.u.ipv4NetAddr)
                      (void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                                SPID_0, SUENDPID_1, SB_PORT_ANY,
                                                &assoc_1.localNAddr);
#endif
                      sbAccCb.curTst.evtType = ACC_EVT_ENDPOPEN_CFM;  /*expected result */
                      break;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
		  case 4:
                       (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                           assoc_1.suId, sbAccCb.curTst.suConId,\
                                           sbAccCb.curTst.spConId,\
                                           &sbAccCb.curTst.localTAddr);

                       break;
#endif
                  }
                  break;
            }      /* End switch(curtstnum) #1 */

            sbAccCb.curTst.state++;
            break;

         /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
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
            { /*primitive received */
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 1:    /* Test O.200.01: Expected Results */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
		     switch (sbAccCb.curTst.subTest) 
                     {
		       case 1:
		         sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                         {
	               	   oper.hi.spId = SPID_0;
                           ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                         , &status, &reason);
                         }
                        break;
                      case 2:
#endif
                         SB_SETUP_ENDPOPEN_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL )
                         ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPOPEN_CFM, &status, &reason);
                         break;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
		    }
		    break;
#endif
                  case 2:     /* Test O.200.02: Expected Results */
                     SB_SETUP_ENDPOPEN_CFM(assoc_1, SCT_NOK,
                                           SCT_CAUSE_INV_PAR_VAL)
                     ret = sbSctChkCfm(&oper, &mgmt,
                                       ACC_EVT_ENDPOPEN_CFM,
                                       &status, &reason);
                     break;
                  case 3:      /* Test O.200.03: Expected Results */
                     SB_SETUP_ENDPOPEN_CFM(assoc_1, SCT_NOK,
                                           SCT_CAUSE_ENDP_OPEN)
                     ret = sbSctChkCfm(&oper, &mgmt,
                                       ACC_EVT_ENDPOPEN_CFM,
                                       &status, &reason);
                     break;
                  case 4:      /* Test O.200.04: Expected Results */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     switch (sbAccCb.curTst.subTest)
                     {
                       case 1:
                         sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                         {
                           ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                         , &status, &reason);
                         }
                         break;
                      case 2:
#endif
                           SB_SETUP_ENDPOPEN_CFM(assoc_1, SCT_NOK,
                                              SCT_CAUSE_ENDP_OPEN)
                           oper.it.suEndpId = SUENDPID_1;
                           ret = sbSctChkCfm(&oper, &mgmt,
                                       ACC_EVT_ENDPOPEN_CFM,
                                       &status, &reason);
                          break;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
		     }	
		     break;
#endif
                  case 5:        /* Test O.200.05: Expected Results */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_DISC_REQ)
		     {
			 ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_DISC_REQ, &status, &reason);
		     }
#endif
                     SB_SETUP_ENDPCLOSE_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL)
                     ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPCLOSE_CFM, &status, &reason);
                     break;
                  case 6:     /* Test O.200.06: Expected Results */
                     mgmt.transId = sbAccCb.curTst.curTransId;
                     mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                     mgmt.s.usta.cause = LCM_CAUSE_INV_PAR_VAL;
                     ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_STA_IND);
                     break;
                  /* sb032.102 :  IPV6 Support Added */
                  case 7:    /* Test O.200.07: Expected Results */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     switch (sbAccCb.curTst.subTest)
                     {
                       case 1:
                         sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                         {
                           oper.hi.spId = SPID_0;
                           ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                         , &status, &reason);
                         }
                        break;
                      case 2:
#endif

               	     SB_SETUP_ENDPOPEN_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL )
                     ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPOPEN_CFM, &status, &reason);
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     break;
	           }		
#endif
                   break;
                  case 8:        /* Test O.200.08: Expected Results */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_DISC_REQ)
                     {
                         ret = sbHitChkReq(&oper, &mgmt,
                                             ACC_EVT_DISC_REQ, &status, &reason);
                     }
#endif
                     SB_SETUP_ENDPCLOSE_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL)
                     ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPCLOSE_CFM, &status, &reason);
                     break;
               /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
                  case 9:    /* Test O.200.09: Expected Results */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     switch (sbAccCb.curTst.subTest)
                     {
                      case 1:
                         sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                         {		
                            ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                       , &status, &reason);
                         }
                         break;
                      case 2:
                         sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                         {
                           ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                      , &status, &reason);
                         }
                         break;
		     case 3:
#endif
                        SB_SETUP_ENDPOPEN_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL )
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPOPEN_CFM, &status, &reason);
                        break;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
	            }
                 break;	
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */
                  case 10:    /* Test O.200.10: Expected Results */
                     switch(sbAccCb.curTst.subTest)
                     {
		      case 1:
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
	                 sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                         {
                           ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                         , &status, &reason);
                         }
                         break;
                       case 2:
#endif
                           SB_SETUP_ENDPOPEN_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL )
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPOPEN_CFM, &status, &reason);
                           break;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
		        case 3:
         		   sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                           {
                             ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                           , &status, &reason);
                           }
                           break;
                        case 4:
#else
                        case 2:
#endif
                           assoc_1.suEndpId = SUENDPID_1;
                           SB_SETUP_ENDPOPEN_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL )
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPOPEN_CFM, &status, &reason);
                           break;
                     }
                     break;
               }      /* End switch(curtstnum) #2 */

               if(ret == RFAILED)
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

            } /* end primitive received */

            sbAccCb.curTst.subTest++;
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
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbSctEndpTst */

/* Initialization and Termination of Association */
/* Sending SCTP Endpoint */

/*
 *       Fun:   sbO201_01
 *
 *       Desc:  Test case : O.201.01
 *              Purpose   : Verify successful initialization of an
 *                          association (handleInit = TRUE).
 *
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *       Notes:
 *
 *       File:  sb_act3.c
 *
 */

#ifdef ANSI
PUBLIC  S16 sbO201_01
(
void
)
#else
PUBLIC  S16 sbO201_01(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_01)

   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocSndTst_1(curtstnum, "O.201.01");

   RETVALUE(ROK);
} /* end sbO201_01 */

/* sb032.102 :  IPV6 Support Added */
/*
 *       Fun:   sbO201_19
 *
 *       Desc:  Test case : O.201.19
 *              Purpose   : Verify successful initialization of an
 *                          association (handleInit = TRUE)for IPV6 address.
 *
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *       Notes:
 *
 *       File:  sb_act3.c
 *
 */

#ifdef ANSI
PUBLIC  S16 sbO201_19
(
void
)
#else
PUBLIC  S16 sbO201_19(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_19)

   curtstnum = 19;
   sbAccCb.curTst.numSubTst = 4;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctAssocSndTst_1(curtstnum, "O.201.19");

   RETVALUE(ROK);
} /* end sbO201_19 */

/*
*       Fun:   sbO201_02
*
*       Desc:  Test case : O.201.02
*              Purpose   : Verify that on reception of a stale cookie error,
*                          the sender should retry association establishment
*                          with a request for an extended cookie-lifetime
*                          included in the second INIT chunk.
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_02
(
void
)
#else
PUBLIC  S16 sbO201_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocSndTst_1(curtstnum,"O.201.02");
   RETVALUE(ROK);
} /* end sbO201_02 */


/*
*       Fun:   sbO201_03
*
*       Desc:  Test case : O.201.03
*              Purpose   : Verify unsuccessful initialization when the spId
*                          is not valid.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_03
(
void
)
#else
PUBLIC  S16 sbO201_03(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocSndTst_1(curtstnum,"O.201.03");
   RETVALUE(ROK);
} /* end sbO201_03 */



/*
*       Fun:   sbO201_04
*
*       Desc:  Test case : O.201.04
*              Purpose   : Verify unsuccessful initialization of an
*                          association when the SAP is not in the bound state.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_04
(
void
)
#else
PUBLIC  S16 sbO201_04(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocSndTst_1(curtstnum,"O.201.04");
   RETVALUE(ROK);
} /* end sbO201_04 */



/*
*       Fun:   sbO201_05
*
*       Desc:  Test case : O.201.05
*              Purpose   : Verify successful abort from operation if the peer
*                          SCTP cannot set up the new association.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_05
(
void
)
#else
PUBLIC  S16 sbO201_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_05)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 3;
   sbSctAssocSndTst_1(curtstnum,"O.201.05");
   RETVALUE(ROK);
} /* end sbO201_05 */



/*
*       Fun:   sbO201_06
*
*       Desc:  Test case : O.201.06
*              Purpose   : Verify that successful abort from association
*                          takes place after association establishment
*                          if the service user requests it.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_06
(
void
)
#else
PUBLIC  S16 sbO201_06(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO201_06)
   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocSndTst_2(curtstnum,"O.201.06");
   RETVALUE(ROK);
} /* end sbO201_06 */


/*
*       Fun:   sbO201_20
*
*       Desc:  Test case : O.201.20
*              Purpose   : Verify that successful abort from association for
*              IPV6 address 
*                          takes place after association establishment
*                          if the service user requests it.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_20
(
void
)
#else
PUBLIC  S16 sbO201_20(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO201_20)
   curtstnum = 20;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctAssocSndTst_2(curtstnum,"O.201.20");
   RETVALUE(ROK);
} /* end sbO201_20 */

/*
*       Fun:   sbO201.07
*
*       Desc:  Test case : O.201.07
*              Purpose   : Verify that successful graceful termination from
*                          association takes place after association
*                          establishment if the service user requests it.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_07
(
void
)
#else
PUBLIC  S16 sbO201_07(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_07)
   curtstnum = 7;
   sbAccCb.curTst.numSubTst = 3;
   sbSctAssocSndTst_2(curtstnum,"O.201.07");
   RETVALUE(ROK);
} /* end sbO201_07 */


/*
*       Fun:   sbO201.21
*
*       Desc:  Test case : O.201.21
*              Purpose   : Verify that successful graceful termination from
*                          association for IPV6 takes place after association
*                          establishment if the service user requests it.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_21
(
void
)
#else
PUBLIC  S16 sbO201_21(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_21)
   curtstnum = 21;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctAssocSndTst_2(curtstnum,"O.201.21");
   RETVALUE(ROK);
} /* end sbO201_21 */

/*
*       Fun:   sbO205.01
*
*       Desc:  Test case : O.205.01
*              Purpose   : Verify that in successful graceful termination from
*                          association SCTP is sending TermInd to user.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO205_01
(
void
)
#else
PUBLIC  S16 sbO205_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_01)
   curtstnum = 01;
   sbAccCb.curTst.numSubTst = 4;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.01");
   RETVALUE(ROK);
} /* end sbO205_01 */ 

/*--
*       Fun:   sbO205.02
*
*       Desc:  Test case : O.205.02
*              Purpose   : 
*                         
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO205_02
(
void
)
#else
PUBLIC  S16 sbO205_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_02)
   curtstnum = 02;
   sbAccCb.curTst.numSubTst = 5;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.02");
   RETVALUE(ROK);
} /* end sbO205_01 */ 
/*--
*       Fun:   sbO205.03
*
*       Desc:  Test case : O.205.03
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_03
(
void
)
#else
PUBLIC  S16 sbO205_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_03)
   curtstnum = 03;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.03");
   RETVALUE(ROK);
} /* end sbO205_03 */

/*--
*       Fun:   sbO205.04
*
*       Desc:  Test case : O.205.04
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_04
(
void
)
#else
PUBLIC  S16 sbO205_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_04)
   curtstnum = 04;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.04");
   RETVALUE(ROK);
} /* end sbO205_04 */

/*--
*       Fun:   sbO205.05
*
*       Desc:  Test case : O.205.05
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_05
(
void
)
#else
PUBLIC  S16 sbO205_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_05)
   curtstnum = 05;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.05");
   RETVALUE(ROK);
} /* end sbO205_05 */

/*--
*       Fun:   sbO205.06
*
*       Desc:  Test case : O.205.06
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_06
(
void
)
#else
PUBLIC  S16 sbO205_06(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_06)
   curtstnum = 06;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.06");
   RETVALUE(ROK);
} /* end sbO205_06 */

/*--
*       Fun:   sbO205.07
*
*       Desc:  Test case : O.205.07
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_07
(
void
)
#else
PUBLIC  S16 sbO205_07(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_07)
   curtstnum = 07;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.07");
   RETVALUE(ROK);
} /* end sbO205_06 */

/*--
*       Fun:   sbO205.08
*
*       Desc:  Test case : O.205.08
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_08
(
void
)
#else
PUBLIC  S16 sbO205_08(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 4;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.08");
   RETVALUE(ROK);
} /* end sbO205_08 */

/*--
*       Fun:   sbO205.09
*
*       Desc:  Test case : O.205.09
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_09
(
void
)
#else
PUBLIC  S16 sbO205_09(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_09)
   curtstnum = 9;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.09");
   RETVALUE(ROK);
} /* end sbO205_09 */

/*--
*       Fun:   sbO205.10
*
*       Desc:  Test case : O.205.10
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_10
(
void
)
#else
PUBLIC  S16 sbO205_10(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_10)
   curtstnum = 10;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.10");
   RETVALUE(ROK);
} /* end sbO205_10 */

/*--
*       Fun:   sbO205.11
*
*       Desc:  Test case : O.205.11
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_11
(
void
)
#else
PUBLIC  S16 sbO205_11(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_11)
   curtstnum = 11;
   sbAccCb.curTst.numSubTst = 6;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.11");
   RETVALUE(ROK);
} /* end sbO205_11 */

/*--
*       Fun:   sbO205.12
*
*       Desc:  Test case : O.205.12
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_12
(
void
)
#else
PUBLIC  S16 sbO205_12(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_12)
   curtstnum = 12;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.12");
   RETVALUE(ROK);
} /* end sbO205_12 */

/*--
*       Fun:   sbO205.13
*
*       Desc:  Test case : O.205.13
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_13
(
void
)
#else
PUBLIC  S16 sbO205_13(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_13)
   curtstnum = 13;
   sbAccCb.curTst.numSubTst = 5;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.13");
   RETVALUE(ROK);
} /* end sbO205_13 */

/*--
*       Fun:   sbO205.14
*
*       Desc:  Test case : O.205.14
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_14
(
void
)
#else
PUBLIC  S16 sbO205_14(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_14)
   curtstnum = 14;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.14");
   RETVALUE(ROK);
} /* end sbO205_14 */

/*--
*       Fun:   sbO205.15
*
*       Desc:  Test case : O.205.15
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_15
(
void
)
#else
PUBLIC  S16 sbO205_15(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_15)
   curtstnum = 15;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.15");
   RETVALUE(ROK);
} /* end sbO205_15 */

/*--
*       Fun:   sbO205.16
*
*       Desc:  Test case : O.205.16
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_16
(
void
)
#else
PUBLIC  S16 sbO205_16(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_16)
   curtstnum = 16;
   sbAccCb.curTst.numSubTst = 6;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.16");
   RETVALUE(ROK);
} /* end sbO205_16 */

/*--
*       Fun:   sbO205.17
*
*       Desc:  Test case : O.205.17
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_17
(
void
)
#else
PUBLIC  S16 sbO205_17(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_17)
   curtstnum = 17;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.17");
   RETVALUE(ROK);
} /* end sbO205_17 */

/*--
*       Fun:   sbO205.18
*
*       Desc:  Test case : O.205.18
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_18
(
void
)
#else
PUBLIC  S16 sbO205_18(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_18)
   curtstnum = 18;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.18");
   RETVALUE(ROK);
} /* end sbO205_18 */

/*--
*       Fun:   sbO205.19
*
*       Desc:  Test case : O.205.19
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_19
(
void
)
#else
PUBLIC  S16 sbO205_19(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_19)
   curtstnum = 19;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.19");
   RETVALUE(ROK);
} /* end sbO205_19 */

/*--
*       Fun:   sbO205.20
*
*       Desc:  Test case : O.205.20
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_20
(
void
)
#else
PUBLIC  S16 sbO205_20(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_20)
   curtstnum = 20;
   sbAccCb.curTst.numSubTst = 5;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.20");
   RETVALUE(ROK);
} /* end sbO205_20 */

/*--
*       Fun:   sbO205.21
*
*       Desc:  Test case : O.205.21
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_21
(
void
)
#else
PUBLIC  S16 sbO205_21(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_21)
   curtstnum = 21;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.21");
   RETVALUE(ROK);
} /* end sbO205_21 */

/*--
*       Fun:   sbO205.22
*
*       Desc:  Test case : O.205.22
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_22
(
void
)
#else
PUBLIC  S16 sbO205_22(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_22)
   curtstnum = 22;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.22");
   RETVALUE(ROK);
} /* end sbO205_22 */

/*--
*       Fun:   sbO205.23
*
*       Desc:  Test case : O.205.23
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_23
(
void
)
#else
PUBLIC  S16 sbO205_23(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_23)
   curtstnum = 23;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.23");
   RETVALUE(ROK);
} /* end sbO205_23 */

/*--
*       Fun:   sbO205.24
*
*       Desc:  Test case : O.205.24
*              Purpose   :
*
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_24
(
void
)
#else
PUBLIC  S16 sbO205_24(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_24)
   curtstnum = 24;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.24");
   RETVALUE(ROK);
} /* end sbO205_24 */

/* sb012.103: Test case added for non-unicast address issue fix */
/*
*       Fun:   sbO205.25
*
*       Desc:  Test case : O.205.25
*              Purpose   : Discarding COOKIE-ECHO chunk sent from non-unicast
*			   address.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_25
(
void
)
#else
PUBLIC  S16 sbO205_25(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.205.curtstnum */
                                                                                                                       
   TRC2(sbO205_25)
   curtstnum = 25;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.25");
   RETVALUE(ROK);
} /* end sbO205_25 */

/* sb012.103: Test case added for non-unicast address issue fix */
/*
*       Fun:   sbO205.26
*
*       Desc:  Test case : O.205.26
*              Purpose   : Discarding COOKIE-ECHO chunk if peer address
*			   list consists of non-unicast address.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO205_26
(
void
)
#else
PUBLIC  S16 sbO205_26(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.205.curtstnum */
                                                                                                                        
   TRC2(sbO205_25)
   curtstnum = 26;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.26");
   RETVALUE(ROK);
} /* end sbO205_26 */

/* sb029.103: Added test case O.205.27 */
/*
 *       Fun:   sbO205.27
 *
 *       Desc:  Test case : O.205.27
 *              Purpose   : When INIT chunk received with source  port ZERO, SCTP
 *                          will send abort.
 *                           
 *         
 *
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *       Notes:
 *
 *       File:  sb_act3.c
 *
 */
#ifdef ANSI
PUBLIC  S16 sbO205_27
(
 void
)
#else
PUBLIC  S16 sbO205_27(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.205.curtstnum */

   TRC2(sbO205_27)
   curtstnum = 27;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.27");
   RETVALUE(ROK);
} /* end sbO205_27 */

/* sb030.103: Added test case O.205.28 */
/*
 *       Fun:   sbO205.28
 *
 *       Desc:  Test case : O.205.28
 *
 *       Purpose: When SCTP received a SHUTDOWN ACK with Vtag
 *                did not match with own Initiate Tag in COOKIE-WAIT 
 *                or COOKIE-SENT, have to respond with SHUTDOWN-CMPLT,
 *                Also T-Bit need to be set. 
 *
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *           
 *       File:  sb_act3.c
 *
 */
#ifdef ANSI
PUBLIC  S16 sbO205_28
(
 void
)
#else
PUBLIC  S16 sbO205_28(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.205.curtstnum */
                                                                                                                                          
   TRC2(sbO205_28)
   curtstnum = 28;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.28");
   RETVALUE(ROK);
} /* end sbO205_28 */

/* sb030.103: Added test case O.205.29 */
/*
*       Fun:   sbO205.29
*
*       Desc:  Test case : O.205.29
*              Purpose   : If SCTP receives a SHUTDOWNCMPLT chunk with T-bit 
*                          to 1 and the Vtag set to SCTP's own-initiate tag,
*                          discard the SHUTDOWNCMPLT chunk.  
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO205_29
(
void
)
#else
PUBLIC  S16 sbO205_29(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO205_29)
   curtstnum = 29;
   sbAccCb.curTst.numSubTst = 4;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.29");
   RETVALUE(ROK);
} /* end sbO205_29 */
 
                                                                                                                                          
/* sb030.103: Added test case O.205.30 */
/*
*       Fun:   sbO205.30
*
*       Desc:  Test case : O.205.30
*              Purpose   : If SCTP receives a DATA chunk with an invalid
*                          stream identifier, send an ERROR chunk 
*                          and SACK with correct cumTsn value.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
                                                                                                                                          
#ifdef ANSI
PUBLIC  S16 sbO205_30
(
void
)
#else
PUBLIC  S16 sbO205_30(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */
                                                                                                                                          
   TRC2(sbO205_30)
   curtstnum = 30;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocSndTst_5(curtstnum,"O.205.30");
   RETVALUE(ROK);
} /* end sbO205_30 */

/*
*       Fun:   sbO201_08
*
*       Desc:  Test case : O.201.08
*              Purpose   : Verify unsuccessful graceful termination of
*                          association when the association identifier
*                          does not correspond to an established association.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_08
(
void
)
#else
PUBLIC  S16 sbO201_08(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocSndTst_2(curtstnum,"O.201.08");
   RETVALUE(ROK);
} /* end sbO201_08 */



/*
*       Fun:   sbO201_09
*
*       Desc:  Test case : O.201.09
*              Purpose   : Verify unsuccessful termination of association when
*                          the maximum number of retries for shutdown have
*                          been made by the service provider without receiving
*                          SHUTDOWN_ACK from the remote peer endpoint.
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_09
(
void
)
#else
PUBLIC  S16 sbO201_09(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */


   TRC2(sbO201_09)
   curtstnum = 9;
   sbSctAssocSndTst_3(curtstnum,"O.201.09");
   RETVALUE(ROK);
} /* end sbO201_09 */



/*
*       Fun:   sbO201_10
*
*       Desc:  Test case : O.201.10
*              Purpose   : Verify unsuccessful data delivery after
*                          termination of association.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_10
(
void
)
#else
PUBLIC  S16 sbO201_10(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_10)
   curtstnum = 10;
   sbAccCb.curTst.numSubTst = 3;
   sbSctAssocSndTst_3(curtstnum,"O.201.10");
   RETVALUE(ROK);
} /* end sbO201_10 */



/*
*       Fun:   sbO201_11
*
*       Desc:  Test case : O.201.11
*              Purpose   : Verify that initialization is unsuccessful (abort) when outStrms
*                          from the receiving end is more than remInStrms from the sending end.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_11
(
void
)
#else
PUBLIC  S16 sbO201_11(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_11)
   curtstnum = 11;
   sbAccCb.curTst.numSubTst = 3;
   sbSctAssocSndTst_3(curtstnum,"O.201.11");
   RETVALUE(ROK);
} /* end sbO201_11 */



/*
*       Fun:   sbO201_12
*
*       Desc:  Test case : O.201.12
*              Purpose   : Verify that when remInStrms of the receiving end is
*                          less than the outStrms, the association will
*                          continue provided the value of negAbrtFlg = FALSE.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_12
(
void
)
#else
PUBLIC  S16 sbO201_12(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_12)
   curtstnum = 12;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocSndTst_3(curtstnum,"O.201.12");
   RETVALUE(ROK);
} /* end sbO201_12 */



/*
*       Fun:   sbO201_13
*
*       Desc:  Test case : O.201.13
*              Purpose   : Verify that when remInStrms of the receiving end is
*                          less than the outStrms the association will abort
*                          provided the value of negAbrtFlg = TRUE
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_13
(
void
)
#else
PUBLIC  S16 sbO201_13(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_13)
   curtstnum = 13;
   sbAccCb.curTst.numSubTst = 3;
   sbSctAssocSndTst_3(curtstnum,"O.201.13");
   RETVALUE(ROK);
} /* end sbO201_13 */



/*
*       Fun:   sbO201_14
*
*       Desc:  Test case : O.201.14
*              Purpose   : Verify that multiple associations may be
*                          initialized with success.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_14
(
void
)
#else
PUBLIC  S16 sbO201_14(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_14)
   curtstnum = 14;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocSndTst_4(curtstnum,"O.201.14");
   RETVALUE(ROK);
} /* end sbO201_14 */


/*
*       Fun:   sbO201_15
*
*       Desc:  Test case : O.201.15
*              Purpose   : Verify that if a mandatory chunk in the INIT_ACK is
*                          missing, an ABORT chunk will be generated.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_15
(
void
)
#else
PUBLIC  S16 sbO201_15(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_15)
   curtstnum = 15;
   sbAccCb.curTst.numSubTst = 3;
   sbSctAssocSndTst_4(curtstnum,"O.201.15");
   RETVALUE(ROK);
} /* end sbO201_15 */

/*
*       Fun:   sbO201_16
*
*       Desc:  Test case : O.201.16
*              Purpose   : Verify that maxInitReTx is the maximum number of
*                          times that a sender should unsuccessfully attempt
*                          to send an Init chunk.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_16
(
void
)
#else
PUBLIC  S16 sbO201_16(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_16)
   curtstnum = 16;
   sbSctAssocSndTst_4(curtstnum,"O.201.16");
   RETVALUE(ROK);
} /* end sbO201_16 */


/* Added for SB_VER13 */

/*
*       Fun:   sbO201_17
*
*       Desc:  Test case : O.201.17
*              Purpose   : This test case test the successful establishment
*              of association, when hostname parameter is send in the INIT-ACK
*              message.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_17
(
void
)
#else
PUBLIC  S16 sbO201_17(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_17)
   curtstnum = 17;
   sbAccCb.curTst.numSubTst = 4;
   /* sb012.103: Assigning Dummy GetHostByName function */
   sbGlobalCb.funcGetHostByName =sbInetGetHostByName;
   sbSctAssocSndTst_1(curtstnum,"O.201.17");
   RETVALUE(ROK);
} /* end sbO201_17 */



/*
*       Fun:   sbO201_18
*
*       Desc:  Test case : O.201.18
*              Purpose   :  This test case test the unsuccessful association
*              establishment when hostname is a part of INIT-ACK message and
*              it could not be resolved.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO201_18
(
void
)
#else
PUBLIC  S16 sbO201_18(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_18)
   curtstnum = 18;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocSndTst_1(curtstnum,"O.201.18");
   RETVALUE(ROK);
} /* end sbO201_18 */

/* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
/*
 *       Fun:   sbO201_22
 *
 *       Desc:  Test case : O.201.22
 *              Purpose   : Verify successful initialization of an
 *                          association (handleInit = TRUE).
 *
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *       Notes:
 *
 *       File:  sb_act3.c
 *
 */

#ifdef ANSI
PUBLIC  S16 sbO201_22
(
void
)
#else
PUBLIC  S16 sbO201_22(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_22)

   curtstnum = 22;
   sbAccCb.curTst.numSubTst = 7;
   sbSctAssocSndTst_1(curtstnum, "O.201.22");

   RETVALUE(ROK);
} /* end sbO201_22 */
#endif /* SCT_ENDP_MULTI_IPADDR */

/* sb028.103: Added new test case for multiple TermInd issue. */ 
/*
*       Fun:   sbO201_23
*
*       Desc:  Test case : O.201.23
*              Purpose   : Verify that SCTP will not generate multiple
*                          TermInd even if it receives an abort chunk on an 
*                          association (state = CLOSED) and freeze timer
*                          is running.
*                 
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO201_23
(
 void
 )
#else
PUBLIC  S16 sbO201_23(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_23)

   curtstnum = 23;

   sbAccCb.curTst.numSubTst = 6;
   sbSctAssocSndTst_1(curtstnum, "O.201.23");

   RETVALUE(ROK);
} /* end sbO201_23 */

/* sb029.103: Added test case to check OOTB INIT-ACK chunk.  */                                                                                                                                          
/*
 *       Fun:   sbO201_24
 *
 *       Desc:  Test case : O.201.24
 *              Purpose   : Verify that SCTP sends ABORT in response
 *                          to OOTB INIT-ACK chunk.
 *                          
 *                          
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *       Notes:
 *
 *       File:  sb_act3.c
 *
 */
#ifdef ANSI
PUBLIC  S16 sbO201_24
(
 void
)
#else
PUBLIC  S16 sbO201_24(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_24)

   curtstnum = 24;

   sbAccCb.curTst.numSubTst = 3;
   sbSctAssocSndTst_2(curtstnum, "O.201.24");

   RETVALUE(ROK);
} /* end sbO201_24 */

/* sb030.103:  Added test case O.201.25 */                                                                                                                                           
/*
 *       Fun:   sbO201_25
 *
 *       Desc:  Test case : O.201.25
 *              Purpose   : Checking the logic of indentifying invalid vtag
 *                          for ABORT chunk.
 *                         
 *
 *
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *       Notes:
 *
 *       File:  sb_act3.c
 *
 */
#ifdef ANSI
PUBLIC  S16 sbO201_25
(
 void
)
#else
PUBLIC  S16 sbO201_25(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */
                                                                                                                                          
   TRC2(sbO201_25)
                                                                                                                                          
   curtstnum = 25;
                                                                                                                                          
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocSndTst_2(curtstnum, "O.201.25");
                                                                                                                                          
   RETVALUE(ROK);
} /* end sbO201_25 */

/* sb035.103: Added new test case sbO201_26*/
/*
 *      Fun:   sbO201_26
 *   
 *      Desc:  Test case : O.201.26
 *      Purpose : Verify that SCTP aborts the association upon receiving
 *                a ABORT chunk having Unresolved Host Name parameter 
 *                greater than 256 bytes.
 *                                 
 *                                  
 *      Ret:   ROK
 *          
 *      Group: Association
 *            
 *      Notes:
 *              
 *      File:  sb_act3.c
 *                
 */
#ifdef ANSI
PUBLIC  S16 sbO201_26
(
 void
 )
#else
PUBLIC  S16 sbO201_26(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_26)
      curtstnum = 26;

   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocSndTst_2(curtstnum, "O.201.26");

   RETVALUE(ROK);
} /* end sbO201_26 */


/* sb035.103: Added new test case sbO201_27*/
/*
 *      Fun:   sbO201_27
 *   
 *      Desc:  Test case : .201.27
 *      Purpose : Verify that SCTP Terminates the association upon receiving
 *                a Error chunk having Unresolved Host Name parameter 
 *                greater than 256 bytes.
 *                                  
 *      Ret:   ROK
 *          
 *      Group: Association
 *            
 *      Notes:
 *              
 *      File:  sb_act3.c
 *                
 */
#ifdef ANSI
PUBLIC  S16 sbO201_27
(
 void
 )
#else
PUBLIC  S16 sbO201_27(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_27)
      curtstnum = 27;

   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocSndTst_2(curtstnum, "O.201.27");

   RETVALUE(ROK);

} /* end sbO201_27 */


/* sb035.103: Added new test case sbO201_28*/
/*
 *      Fun:   sbO201_28
 *   
 *      Desc:  Test case : O.201.28
 *      Purpose : Verify that SCTP sends ABORT in response INIT-ACK chunk
 *                having Host Name parameter is greater than 256 bytes.  
 *                                  
 *      Ret:   ROK
 *          
 *      Group: Association
 *            
 *      Notes:
 *              
 *      File:  sb_act3.c
 *                
 */
#ifdef ANSI
PUBLIC  S16 sbO201_28
(
 void
 )
#else
PUBLIC  S16 sbO201_28(void)
#endif
{
   U8   curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO201_28)

   curtstnum = 28;
   sbAccCb.curTst.numSubTst = 3;
   sbSctAssocSndTst_1(curtstnum, "O.201.28");

   RETVALUE(ROK);
} /* end sbO201_28 */


/* Above case added for SB_VER13 */


/*
 *       Fun:   sbSctAssocSndTst_1
 *
 *       Desc:  Initialization and Termination of Association for the
 *              sending endpoint (#1).
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *       Notes:
 *
 *       File:  sb_act3.c
 *
 */
#ifdef ANSI
PRIVATE  S16 sbSctAssocSndTst_1
(
U8   curtstnum,              /* number of current test within test group */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocSndTst_1 (curtstnum, numstr)
U8   curtstnum;              /* number of current test within test group */
S8  *numstr;       /* test number */
#endif
{
   PRIVATE SbMgmtQElm    mgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf;
   PRIVATE CmIpHdrParm   hdrParm;
   SbAccMsgQElm  *msg;

   PRIVATE SbAccChunkBld buildPar;
   PRIVATE  SbAccAssoc    assoc_1;
   /* sb058.102 : Added to remove compilation warning. */
#ifdef SCT_ENDP_MULTI_IPADDR
   PRIVATE  SbAccAssoc    assoc_2;
#endif
   PRIVATE SbOperQElm    oper;
   PRIVATE SbMgmt        sbMgmt;

   TRC2(sbSctAssocSndTst_1)
   /* Pretests/Setup */
   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            SB_SCTSAPCFG(SAP_1)
            if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
            {
               /* sb046.102: Multiple IP address per Endp */
               if (curtstnum != 22)
               {
                  SB_TSAPCFG(SAP_1)
               }
               else
               {
#ifdef SCT_ENDP_MULTI_IPADDR
                  if(isBitSet(sbAccCb.curTst.bTSapCfgMask, SAP_1) == FALSE )
                  {
                  sbStdTSapCfg(&sbMgmt, SAP_6); 
                  sbSendConfigReq(&sbMgmt, STSBTSAP, SAP_1);
                  }
#endif /* SCT_ENDP_MULTI_IPADDR */
               }
               if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
               {
                  SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                  if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
                  {
                     /* sb046.102: Multiple IP address per Endp */
                     if (curtstnum != 22)
                     {
                        setupAssoc(&assoc_1, ASSOC_1);
                        if (isBitSet(sbAccCb.curTst.bAssocSetupMask,BIT0) == TRUE)
                        {
                           SB_DISABLE_TRACE() /* disable trace */
                           SB_ENTERTEST( sbAccCb.curTst.bTraceMask, BIT0)
                        }
                     }
                     else
                     {
#ifdef SCT_ENDP_MULTI_IPADDR
                        setupAssoc(&assoc_1, ASSOC_4);
                        setupAssoc(&assoc_2, ASSOC_5);
                        if ((isBitSet(sbAccCb.curTst.bAssocSetupMask,BIT0) == TRUE)
                           && (isBitSet(sbAccCb.curTst.bAssocSetupMask,BIT1) == TRUE))
                        {
                           SB_DISABLE_TRACE() /* disable trace */
                           SB_ENTERTEST( sbAccCb.curTst.bTraceMask, BIT0)
                        }
#endif /* SCT_ENDP_MULTI_IPADDR */
                     }
                  } /* end TSapMask if */
               }/*end TSapCfgMask if*/
            } /* end SctSapCfgMask if */
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      ret = 0;
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
               case 1:    /* Test O.201.01: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId, \
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, \
                                              SB_ACC_SCT_TOS, \
                                              (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId,
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,  
#endif
                                              mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 3:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
/* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,  
#endif
                                              mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                        break;
                  }
                  break;
               /* sb032.102 :  IPV6 Support Added */
               case 19:    /* Test O.201.19: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId, \
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, \
                                              SB_ACC_SCT_TOS, \
                                              (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId, \
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.hstNamePrsnt = FALSE;
                        buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,  
#endif
                                              mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 3:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,  
#endif
                                              mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                        break;
                  }
                  break;
               case 2:     /* Test O.201.02: Execution */
                  switch( sbAccCb.curTst.subTest)
                 {
                    case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                       (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId, \
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, \
                                              SB_ACC_SCT_TOS, \
                                              (Buffer*)NULLP);
#else
                       (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId, \
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */

                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                       break;
                    case 2:  /* INIT_ACK Chunk */
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildInitAckChunk(mBuf,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                       /*expected results */
                       sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                       break;
                    case 3:  /* ERROR Chunk */
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildPar.chunkId = SB_ID_ERROR;
                       buildPar.causeCode = SB_CHUNK_ERROR_STALE;
                       buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                       /*expected results */
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                       break;
                    default:
                       break;
                 }
                 break;
               case 3:      /* Test O.201.03: Execution */
/* sb060.102: TOS changes. */
#ifdef SCT3
                  (void) ItLiSctAssocReq(&sbAccCb.itPst, SPID_4, \
                                         assoc_1.spEndpId, assoc_1.suAssocId, \
                                         &assoc_1.priPeerNAddr, \
                                         assoc_1.peerPort, assoc_1.outStrms, \
                                         &assoc_1.peerNAddrLst, \
                                         &assoc_1.localNAddrLst, \
                                         SB_ACC_SCT_TOS, \
                                         (Buffer*)NULLP);
#else
                  (void) ItLiSctAssocReq(&sbAccCb.itPst, SPID_4, \
                                         assoc_1.spEndpId, assoc_1.suAssocId, \
                                         &assoc_1.priPeerNAddr, \
                                         assoc_1.peerPort, assoc_1.outStrms, \
                                         &assoc_1.peerNAddrLst, \
                                         &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
/* SUID_4 not configured */
                  /*expected results */
                  sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                  break;
               case 4:      /* Test O.201.04: Execution */
/* sb060.102: TOS changes. */
#ifdef SCT3
                  (void) ItLiSctAssocReq(&sbAccCb.itPst, SPID_3, \
                                         assoc_1.spEndpId, assoc_1.suAssocId, \
                                         &assoc_1.priPeerNAddr, \
                                         assoc_1.peerPort,assoc_1.outStrms, \
                                         &assoc_1.peerNAddrLst, \
                                         &assoc_1.localNAddrLst, \
                                         SB_ACC_SCT_TOS, \
                                         (Buffer*)NULLP);
#else
                  (void) ItLiSctAssocReq(&sbAccCb.itPst, SPID_3, \
                                         assoc_1.spEndpId, assoc_1.suAssocId, \
                                         &assoc_1.priPeerNAddr, \
                                         assoc_1.peerPort,assoc_1.outStrms, \
                                         &assoc_1.peerNAddrLst, \
                                         &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                  /* SUID_3 not bound */
                  /*expected results */
                  sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                  break;
               case 5:    /* Test O.201.05: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, \
                                               SB_ACC_SCT_TOS, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /*expected results */
                        break;
                    case 2:    /* ABORT chunk */
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildPar.chunkId = SB_ID_ABORT;
                       buildPar.causeCode = SB_CHUNK_ERROR_RES;
                       buildAbortErrChunk(mBuf,&buildPar, &assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_TERM_IND;  /*expected results */
                       break;
                }
                break;
  
                case 17:    /* Test O.201.17: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId,
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, \
                                              SB_ACC_SCT_TOS, \
                                              (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId,
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.hstNamePrsnt = TRUE;
                        if(assoc_1.spId == SPID_1)
                         cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trillium1.com", 
                              cmStrlen((CONSTANT U8 *)"www.trillium1.com"));
                        else
                         cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trillium2.com", 
                             cmStrlen((CONSTANT U8 *)"www.trillium2.com"));
                        buildInitAckChunk(mBuf,&buildPar, &assoc_1);

                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 3:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                        break;
                  }
                  break;

               case 18:    /* Test O.201.18: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId,
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, \
                                              SB_ACC_SCT_TOS, \
                                              (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId,
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.hstNamePrsnt = TRUE;
                        cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trillium3.com", 
                            cmStrlen((CONSTANT U8 *)"www.trillium3.com"));
                        buildInitAckChunk(mBuf,&buildPar, &assoc_1);

                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                  }
                  break;
#ifdef SCT_ENDP_MULTI_IPADDR
               case 22:    /* Test O.201.22: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId,
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, \
                                              SB_ACC_SCT_TOS, \
                                              (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId,
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.hstNamePrsnt = FALSE;/* RFC 4460 -- RTR */
                        buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,  
#endif
                                              mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 3:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,  
#endif
                                              mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                        break;
                     case 4:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_2.spId, \
                                              assoc_2.spEndpId, \
                                              assoc_2.suAssocId,
                                              &assoc_2.priPeerNAddr, \
                                              assoc_2.peerPort, \
                                              assoc_2.outStrms, \
                                              &assoc_2.peerNAddrLst, \
                                              &assoc_2.localNAddrLst, \
                                              SB_ACC_SCT_TOS, \
                                              (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_2.spId, \
                                              assoc_2.spEndpId, \
                                              assoc_2.suAssocId,
                                              &assoc_2.priPeerNAddr, \
                                              assoc_2.peerPort, \
                                              assoc_2.outStrms, \
                                              &assoc_2.peerNAddrLst, \
                                              &assoc_2.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 5:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf, &buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_2.suConId, \
                                              &assoc_2.peerTAddr, \
                                              &assoc_2.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                              &assoc_2.localIf,  
#endif
                                              mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 6:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf, &buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_2.suConId, \
                                              &assoc_2.peerTAddr, \
                                              &assoc_2.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                              &assoc_2.localIf,  
#endif
                                              mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                        break;
                  }
                  break;
#endif /* SCT_ENDP_MULTI_IPADDR */

               /* sb028.103: Added new test case for multiple TermInd issue */
               case 23:    /* Test O.201.23: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        /* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, \
                                               SB_ACC_SCT_TOS, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId,
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;

                     case 2:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 3:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                        break;
                     case 4:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.chunkId = SB_ID_ABORT;
                        buildPar.causeCode = SB_CHUNK_ERROR_STREAM;
                        buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 5:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.chunkId = SB_ID_ABORT;
                        buildPar.causeCode = SB_CHUNK_ERROR_STREAM;
                        buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                  }
                  break;
                
               case 28:    /*sb035.103: Test case O.201.28: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                              assoc_1.spEndpId, \
                              assoc_1.suAssocId, \
                              &assoc_1.priPeerNAddr, \
                              assoc_1.peerPort, \
                              assoc_1.outStrms, \
                              &assoc_1.peerNAddrLst, \
                              &assoc_1.localNAddrLst, \
                              SB_ACC_SCT_TOS, \
                              (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                              assoc_1.spEndpId, \
                              assoc_1.suAssocId,
                              &assoc_1.priPeerNAddr, \
                              assoc_1.peerPort, \
                              assoc_1.outStrms, \
                              &assoc_1.peerNAddrLst, \
                              &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.hstNamePrsnt = TRUE;
                        cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trillium2trum2t.com",260);
                        buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                 assoc_1.suConId, \
                                 &assoc_1.peerTAddr, \
                                 &assoc_1.localTAddr, \
                                 &hdrParm ,
#ifdef LOCAL_INTF
                                 &assoc_1.localIf,
#endif
                                 mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                  } 
                  break;     
            } /*end curtstnum switch #1 */
            sbAccCb.curTst.state++;
            break;

            /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {
               RETVALUE(ROK);
            }
            else if (status == TIMEOUT)
            {
               /* sb028.103: Added new test case for multiple TermInd issue */
               if ((curtstnum == 23 ) && (sbAccCb.curTst.subTest == 5))
               {
                  sbAccCb.curTst.subTestsPass++;
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  break;
               }
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest, \
                                   sbAccCb.curTst.evtType, \
                                   TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            { /*primitive received */
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 1:    /* Test O.201.01: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_ASSOC_CFM, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                            SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                           break;
                     } /*end switch */
                     break;
                  /* sb032.102 :  IPV6 Support Added */
                  case 19:    /* Test O.201.19: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_ASSOC_CFM, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                            SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                           break;
                     } /*end switch */
                     break;
                  case 2:    /* Test O.201.02: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check INIT chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                  &assoc_1, &status);
                            break;
                         case 2:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_ASSOC_CFM)
                            {
                               SB_SETUP_ASSOC_CFM(assoc_1)
                               ret = sbSctChkCfm(&oper, &mgmt, \
                                                 ACC_EVT_ASSOC_CFM, \
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               /* Check COOKIE chunk */
                               oper.hi.spId = SPID_0;
                               SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                     &assoc_1, &status);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else
                            {
                               status = INC_EVNTTYPE;
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                               ret = RFAILED;
                            }
                            break;
                         case 3:
                            /* Check INIT chunk with request for
                             * extended lifetime */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, TRUE, SB_ID_INIT)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                  &assoc_1, &status);
                            break;
                      }
                      break;

                   case 3:      /* Test O.201.03: Expected Results */
                      mgmt.transId = sbAccCb.curTst.curTransId;
                      mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                      mgmt.s.usta.cause = LCM_CAUSE_INV_SPID;
                      ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_STA_IND);
                      break;
                   case 4:   /* Test O.201.04: Expected Results */
                      mgmt.transId = sbAccCb.curTst.curTransId;
                      mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                      mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
                      ret = sbLsbChkCfm(&mgmt, &status, &reason, \
                                        ACC_EVT_STA_IND);
                      break;
                  case 5:    /* Test O.201.05: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 2:
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_OUTRES)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           break;
                     }
                     break;

                   case 17:    /* Test O.201.17: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_ASSOC_CFM, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                            SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                           break;
                     } /*end switch */
                     break;

                    case 18:    /* Test O.201.18: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_TERM_IND)
                           {
			   /* sb008.103: Modified after adding new values for the status field  */
#ifdef SCT_ENHANCED_TERMIND
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_ABORT_SENT, SCT_CAUSE_INIT_FAILED)
#else
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED)
#endif
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           if (msg->evntType == ACC_EVT_STA_IND)
                           {
                             mgmt.s.usta.event = LCM_EVENT_LYR_SPECIFIC;
                             mgmt.s.usta.cause = LSB_CAUSE_UNRSLVD_ADDR;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_STA_IND);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           break;
                       } /*end switch */
                       break;
#ifdef SCT_ENDP_MULTI_IPADDR
                  case 22:    /* Test O.201.22: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_ASSOC_CFM, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                            SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                           break;
                        case 4:
                           /* Check INIT chunk */
                           if (isBitSet(sbAccCb.curTst.bTickMask, BIT1) 
                               && isBitSet(sbAccCb.curTst.bTickMask, BIT0)) 
                           {
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_2, &status );
                           break;
                        case 5:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_2)
                              oper.it.suAssocId = assoc_2.suAssocId;
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_ASSOC_CFM, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_2, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 6:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_2, SCT_STATUS_COMM_UP, \
                                            SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                           break;
                     } /*end switch */
                     break;
#endif /* SCT_ENDP_MULTI_IPADDR */
                /* sb028.103: Added new test case for multiple TermInd issue */
                  case 23:    /* Test O.201.23: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                    &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                                 ret = sbSctChkCfm(&oper, &mgmt, \
                                       ACC_EVT_ASSOC_CFM, \
                                       &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                       &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                 SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                    ACC_EVT_STA_IND, \
                                    &status, &reason);
                           break;
                        case 4:
                           SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_ABRT, SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           break;
                        case 5:
                           SPrint("Ooops, something arrived that I'm not expecting\n\n\n");
                           ret = RFAILED;
                           break;
                     } /*end switch */
                     break;
                     
                  case 28:    /* sb035.103: Test case  O.201.28: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                    &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                                 ret = sbSctChkCfm(&oper, &mgmt, \
                                       ACC_EVT_ASSOC_CFM, \
                                       &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check ABORT chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_ABORT)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                       &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
               }      /* End switch(curtstnum) #2 */


                if(ret == RFAILED)
                {
                   sbAccCb.curTst.subTestsFail++;
                   sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest, \
                                       sbAccCb.curTst.evtType, status, reason);
                   /* Problem - do cleanup */
                   sbAccCb.curTst.bBusyPreTestConf = FALSE;
                   sbAccCb.curTst.bBusyCleanup = TRUE;
                }
                else     /* Subtest successful */
                {
                   sbAccCb.curTst.subTestsPass++;
                }  /*End Subtest successful */
            }  /* end primitive received */

            if (( ((curtstnum == 1)|| (curtstnum == 2) || (curtstnum == 17) || (curtstnum == 19))
                   && (sbAccCb.curTst.subTest == 2)) || ((curtstnum == 22) && ((sbAccCb.curTst.subTest == 2) || (sbAccCb.curTst.subTest == 5))))
            {
               if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                   (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
            }
            /* sb028.103: Added new test case for multiple TermInd issue */
            else if (((curtstnum == 23) && (sbAccCb.curTst.subTest == 2)))
            {                                                                                                 
               if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                     (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
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
            if (sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst)
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               /* Done with a test/subtest */
               sbAccCb.curTst.bBusySubtest = FALSE;
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
}  /* end sbSctAssocSndTst_1 */

/*
*       Fun:   sbSctAssocSndTst_2
*
*       Desc:  Initialization and Termination of Association for the sending endpoint (#2).
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctAssocSndTst_2
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocSndTst_2(curtstnum, numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   PRIVATE SbMgmtQElm    mgmt;
   PRIVATE SbOperQElm    oper;
   PRIVATE SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf;
   SbAccMsgQElm  *msg;
   CmIpHdrParm   hdrParm;
   PRIVATE       SbAccChunkBld buildPar;
   PRIVATE       SbAccAssoc    assoc_1;

   TRC2(sbSctAssocSndTst_2)
   ret = RFAILED;

     /* Pretests/Setup */
   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            SB_SCTSAPCFG(SAP_1)
            if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
            {
               SB_TSAPCFG(SAP_1)
               if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
               {
                  SB_DISABLE_TRACE() /* disable trace */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                     if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
                     {
                        setupAssoc(&assoc_1, ASSOC_1);
                        if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                        {
                           /* sb032.102 :  IPV6 Support Added */
                           if((curtstnum == 20) || (curtstnum == 21))
                           buildPar.hstNamePrsnt = FALSE;
                           SB_EST_ASSOC(assoc_1, BIT0)
                           SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                        } /*end bAssocSetupMask */
                     } /* end bTSapMask */
                  } /* end bTraceMask if */
               }/*end TSapCfgMask if*/
            } /* end SctSapCfgMask if */
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {
               /* Start switch(curtstnum) #1 */
               case 6:     /* Test O.201.06: Execution */
                  /* Send a TermReq with AbrtFlg = True */
                  (void)  ItLiSctTermReq(&sbAccCb.itPst,
                                         assoc_1.spId,
                                         assoc_1.spAssocId,
                                         SCT_ASSOCID_SP,
                                         ABORT);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /*expected results */
                  break;
               case 7:      /* Test O.201.07: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:  /* Send a TermReq with AbrtFlg = False */
                        SPrint(" == SENDING TERM REQ ==\n");
                        (Void)ItLiSctTermReq(&sbAccCb.itPst,
                                              assoc_1.spId,
                                              oper.it.spAssocId,
                                              SCT_ASSOCID_SP, SHTDWN);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:  /* Shutdown Ack chunk */
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildShutdwnAckChunk(mBuf,&buildPar,&assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst,
                                                  SUID_0,assoc_1.suConId,
                                                  &assoc_1.peerTAddr,
                                                  &assoc_1.localTAddr,
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        }
                        break;
                     case 3:  /* for checking ACC_EVT_TERM_CFM */
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_TERM_CFM;
                        break;
                  }
                  break;
               case 8:      /* Test O.201.08: Execution */
                  /* Send a TermReq with AbrtFlg = False */
                  (void)  ItLiSctTermReq(&sbAccCb.itPst, assoc_1.spId, SUASSOCID_1, SCT_ASSOCID_SU, FALSE);
                  sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /*expected results */
                  break;
               /* sb032.102 :  IPV6 Support Added */
               case 20:     /* Test O.201.20: Execution */
                  /* Send a TermReq with AbrtFlg = True */
                  (void)  ItLiSctTermReq(&sbAccCb.itPst,
                                         assoc_1.spId,
                                         assoc_1.spAssocId,
                                         SCT_ASSOCID_SP,
                                         ABORT);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /*expected results */
                  break;
               case 21:      /* Test O.201.21: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:  /* Send a TermReq with AbrtFlg = False */
                        SPrint(" == SENDING TERM REQ ==\n");
                        (Void)ItLiSctTermReq(&sbAccCb.itPst,
                                              assoc_1.spId,
                                              oper.it.spAssocId,
                                              SCT_ASSOCID_SP, SHTDWN);
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:  /* Shutdown Ack chunk */
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildShutdwnAckChunk(mBuf,&buildPar,&assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst,
                                                  SUID_0,assoc_1.suConId,
                                                  &assoc_1.peerTAddr,
                                                  &assoc_1.localTAddr,
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        }
                        break;
                     case 3:  /* for checking ACC_EVT_TERM_CFM */
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_TERM_CFM;
                        break;
                  }
                  break;
               case 24: /* sb029.103: Test case O.201.24: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:    /* ABORT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.chunkId = SB_ID_ABORT;
                        buildPar.causeCode = SB_CHUNK_ERROR_RES;
                        buildAbortErrChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                 assoc_1.suConId, \
                                 &assoc_1.peerTAddr, \
                                 &assoc_1.localTAddr, \
                                 &hdrParm ,
#ifdef LOCAL_INTF
                                 &assoc_1.localIf,
#endif
                                 mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_TERM_IND;  /*expected results */
                        break;
                     case 2:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                 assoc_1.suConId, \
                                 &assoc_1.peerTAddr, \
                                 &assoc_1.localTAddr, \
                                 &hdrParm ,
#ifdef LOCAL_INTF
                                 &assoc_1.localIf,
#endif
                                 mBuf);
                        /* expected results */
                        sbAccCb.curTst.evtType =  ACC_EVT_UDAT_REQ;
                        break;
                  } /* switch of O.201.24 */
                  break;
               case 25: /* sb030.103: Test case O.201.25: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:    /* ABORT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.chunkId = SB_ID_ABORT;
                        buildPar.chunkFlg= 1; /* set T-bit to one. */
                        buildPar.causeCode = SB_CHUNK_ERROR_RES;
                        buildAbortErrChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                        sbAccCb.curTst.evtType =  ACC_EVT_TERM_IND; /*ACC_EVT_NO_RESP;*/  /*expected results */
                        /* sb035.103: set buildPar.chunkFlg to 0 */
                        buildPar.chunkFlg= 0; /* set T-bit to Zero. */
                        break;
                  }
                  break; 

               case 26: /* sb035.103: Test case O.201.26: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.chunkId = SB_ID_ABORT;
                        buildPar.causeCode = SB_CHUNK_ERROR_UNRSLV_ADDR;
                        buildPar.pkUnknownPar = TRUE;
                        buildAbortErrChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                 assoc_1.suConId, \
                                 &assoc_1.peerTAddr, \
                                 &assoc_1.localTAddr, \
                                 &hdrParm ,
#ifdef LOCAL_INTF
                                 &assoc_1.localIf,
#endif
                                 mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_TERM_IND;  /*expected results */
                        buildPar.pkUnknownPar = FALSE;
                        break;
                  }
                  break;

               case 27: /* sb035.103: Test case O.201.27: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.chunkId = SB_ID_ERROR;
                        buildPar.causeCode = SB_CHUNK_ERROR_UNRSLV_ADDR;
                        buildPar.pkUnknownPar = TRUE;
                        buildAbortErrChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                 assoc_1.suConId, \
                                 &assoc_1.peerTAddr, \
                                 &assoc_1.localTAddr, \
                                 &hdrParm ,
#ifdef LOCAL_INTF
                                 &assoc_1.localIf,
#endif
                                 mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_TERM_IND;  /*expected results */
                        buildPar.pkUnknownPar = FALSE;
                        break;
                  }
                  break;
            } /* end switch curtstnum #1 */
            sbAccCb.curTst.state++;
            break;

         /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {
               /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if (status == TIMEOUT)
            {
               /* sb030.103: Timeout Expected for O.201.25 */
               if((curtstnum == 25 ) && (sbAccCb.curTst.subTest == 1))
               {
                  sbAccCb.curTst.subTestsPass++;
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  break;
               }
               else
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                        sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
            }
            else
            {
               /*primitive received */
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 6:    /* Test O.201.06: Expected Results */
                     /* Check ABORT chunk and TermCfm */
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_UDAT_REQ)
                     {
                        oper.hi.spId = SPID_0;
                        /* RFC 4460 upgrade -- */
                        SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_USR_INITIATED_ABORT, 0, FALSE, SB_ID_ABORT)
                        ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if (msg->evntType == ACC_EVT_TERM_CFM)
                     {
                        SB_SETUP_TERM_CFM(assoc_1,SCT_OK, SCT_CAUSE_NOT_APPL)
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status, &reason);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                     }
                     else
                     {
                        status = INC_EVNTTYPE;
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        ret = RFAILED;
                     }
                     break;

                  case 7:   /* Test O.201.07: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check SHUTDOWN chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                           break;

                        case 2: /* SB_VER13 - change in logic for SDOWN-CMPLT case */
                           sbAccPeekMsg(&msg);

                           /* Check SDOWNCMPLT chunk */
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNCMPLT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                          /* Check TermCfm */
                           else if (msg->evntType == ACC_EVT_TERM_CFM)
                           {
                              SB_SETUP_TERM_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                  case 8:    /* Test O.201.08: Expected Results */
                     mgmt.transId = sbAccCb.curTst.curTransId;
                     mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                     mgmt.s.usta.cause = LCM_CAUSE_INV_PAR_VAL;
                     /* sb031.103: Modified the test case expected primitive.*/
                     ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_TERM_CFM);
                     break;
                  /* sb032.102 :  IPV6 Support Added */
                  case 20:    /* Test O.201.20: Expected Results */
                     /* Check ABORT chunk and TermCfm */
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_UDAT_REQ)
                     {
                        oper.hi.spId = SPID_0;
                        /* sb005.103: IPV6 Change */
                        SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_USR_INITIATED_ABORT, 0, FALSE, SB_ID_ABORT)
                        ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if (msg->evntType == ACC_EVT_TERM_CFM)
                     {
                        SB_SETUP_TERM_CFM(assoc_1,SCT_OK, SCT_CAUSE_NOT_APPL)
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status, &reason);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                     }
                     else
                     {
                        status = INC_EVNTTYPE;
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        ret = RFAILED;
                     }
                     break;
                  case 21:   /* Test O.201.21: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check SHUTDOWN chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                           break;

                        case 2: /* SB_VER13 - change in logic for SDOWN-CMPLT case */
                           sbAccPeekMsg(&msg);

                           /* Check SDOWNCMPLT chunk */
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNCMPLT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                          /* Check TermCfm */
                           else if (msg->evntType == ACC_EVT_TERM_CFM)
                           {
                              SB_SETUP_TERM_CFM(assoc_1, SCT_OK, SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                  case 24:    /* sb029.103: Test O.201.24 Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {

                        case 1:    /* Test O.201.24: Expected Results */
                           SPrint(" \n =====Recevied TermInd at the user of SCTP ==== \n ");
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_ABRT, SCT_CAUSE_NOT_APPL) /* new cause need to be defined */
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           if (ret!= ROK)
                              SPrint(" \n ===== TermInd with error ==== \n\n ");
                           break;

                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              /* RFC 4460 upgrade -- */
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_ABORT)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              printf("\n\n received abort for OOTB INIT-ACK chunk \n\n");
                           }
                           break;
                     }/* end of switch O.201.24.*/
                     break;
                     /* sb030.103: */
                  case 25:    /* sb029.103: Test O.201.25 Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1: /* expect nothing. */ 
                           break;
                     }
                     break;
                  case 26:    /* sb035.103: Test O.201.26 Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:  
                           SPrint(" \n =====Recevied TermInd at the user of SCTP ==== \n ");
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS) /* new cause need to be defined */
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           if (ret!= ROK)
                              SPrint(" \n ===== TermInd with error ==== \n\n ");
                           break;
                     }
                     break;

                  case 27:    /* sb035.103: Test O.201.27 Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:  
                           SPrint(" \n =====Recevied TermInd at the user of SCTP ==== \n ");
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS) /* new cause need to be defined */
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           if (ret!= ROK)
                              SPrint(" \n ===== TermInd with error ==== \n\n ");
                           break;
                     }
                     break;

               }      /* End switch(curtstnum) #2 */

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

                  /* sb032.102 :  IPV6 Support Added */
            if ( ((curtstnum == 6) || (curtstnum == 20)) || (((curtstnum == 7)||(curtstnum == 21)) && (sbAccCb.curTst.subTest == 2)) )
            {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
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
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
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
   {
      doCleanup();
   }

   RETVALUE(ROK);
}  /* end sbSctAssocSndTst_2 */


/*
*       Fun:   sbSctAssocSndTst_5
*
*       Desc:  Patch Test cases (#5).
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctAssocSndTst_5
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocSndTst_5(curtstnum, numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   PRIVATE SbMgmtQElm    mgmt;
   PRIVATE SbOperQElm    oper;
   PRIVATE SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf;
   SbAccMsgQElm  *msg;
   CmIpHdrParm   hdrParm;
   PRIVATE       SbAccChunkBld buildPar;
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbAccAssoc    assoc_2;
   Buffer        *vsInfo;
   CmNetAddr     dfltPriPeerNAddr;
   static char   count = 0;
   /* sb012.103: Added for non-unicast address issue fix */
   CmTptAddr     nonUnicastAddr;
  /* sb030.103: Added for test case O.205.30 */ 
   U8            ID;

   TRC2(sbSctAssocSndTst_5)
   ret = RFAILED;

     /* Pretests/Setup */
   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      if (curtstnum == 11)
      {
         if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
         {
            sbStdGenCfg(&sbMgmt);
            /* sb013.103: Changed initial ARwnd value */
            sbMgmt.t.cfg.s.genCfg.initARwnd = 1500;
            sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
         }
      }
      if (curtstnum == 16)
      {
         if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
         {
            sbStdGenCfg(&sbMgmt);
            sbMgmt.t.cfg.s.genCfg.reConfig.maxInitReTx = 1;
            sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
         }
      }
      if (curtstnum == 20)
      {
         if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
         {
            sbStdGenCfg(&sbMgmt);
            sbMgmt.t.cfg.s.genCfg.reConfig.keyTm = 10;
            sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
         }
      }
      if (curtstnum == 21)
      {
         if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
         {
            sbStdGenCfg(&sbMgmt);
            sbMgmt.t.cfg.s.genCfg.maxNmbRxChunks = 1;
            sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
         }
      }
      if (curtstnum == 22)
      {
         if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
         {
            sbStdGenCfg(&sbMgmt);
            sbMgmt.t.cfg.s.genCfg.reConfig.keyTm = 10;
            sbMgmt.t.cfg.s.genCfg.useHstName = TRUE;
            cmMemcpy(sbMgmt.t.cfg.s.genCfg.hostname,(CONSTANT U8 *)"www.trillium1.com", 
            cmStrlen((CONSTANT U8 *)"www.trillium1.com"));
            sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
         }
      }
      else
      {
         SB_GENCFG()
      }
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            if( (curtstnum == 01) || (curtstnum == 8)) 
            {
                if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                {
                   sbStdSctSapCfg(&sbMgmt, SAP_1);
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial = 5;
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin = 5;
                   sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                }
            }
            else if (curtstnum == 02) 
            {
                if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                {
                   sbStdSctSapCfg(&sbMgmt, SAP_1);
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.negAbrtFlg = TRUE;
                   sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                }
            }
            else if (curtstnum == 07) 
            {
                if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                {
                   sbStdSctSapCfg(&sbMgmt, SAP_1);
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.t5SdownGrdTm = 2;
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial = 5;
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin = 5;
                   sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                }
            }
            else if (curtstnum == 9) 
            {
                if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                {
                   sbStdSctSapCfg(&sbMgmt, SAP_1);
#ifdef LSB4
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.bundleTm = 2;
#endif /* LSB4 */
                   sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                }
            }
            else if ((curtstnum == 13) || (curtstnum == 16) ) 
            {
                if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                {
                   sbStdSctSapCfg(&sbMgmt, SAP_1);
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.freezeTm = 0;
                   sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                }
            }
            else if (curtstnum == 15) 
            {
                if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                {
                   sbStdSctSapCfg(&sbMgmt, SAP_1);
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.freezeTm = 1;
                   sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                }
            }
            else
            {
               SB_SCTSAPCFG(SAP_1)
            }
            SB_SCTSAPCFG(SAP_1)

            if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
            {  
               if  (curtstnum == 22) 
               {
                   if(isBitSet(sbAccCb.curTst.bTSapCfgMask, SAP_1) == FALSE )
                   {                                             
                      sbStdTSapCfg(&sbMgmt, SAP_1);                 
                      sbMgmt.t.cfg.s.tSapCfg.reConfig.sbDnsCfg.dnsTmOut = 1;
                      sbMgmt.t.cfg.s.tSapCfg.reConfig.sbDnsCfg.useDnsLib = TRUE;
                      sbMgmt.t.cfg.s.tSapCfg.reConfig.sbDnsCfg.maxRtxCnt = 1;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                      sbAccCb.useDnsFlag = sbMgmt.t.cfg.s.tSapCfg.reConfig.sbDnsCfg.useDnsLib;
#endif
                      sbSendConfigReq(&sbMgmt, STSBTSAP, SAP_1);  
                   }
               }
               else 
               {
                  SB_TSAPCFG(SAP_1)
               }
               if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
               {
                  SB_DISABLE_TRACE() /* disable trace */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                     if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
                     {
                        setupAssoc(&assoc_1, ASSOC_1);
                        /* sb030.103: Added new test cases O.205.29, O.205.30. */
                        if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                        {
                           if((curtstnum == 01) || (curtstnum == 03) || (curtstnum == 07) ||
                              (curtstnum == 9) || (curtstnum == 11) || (curtstnum == 13) || 
                              (curtstnum == 14) || (curtstnum == 15) || (curtstnum == 17) ||
                              (curtstnum == 18) || (curtstnum == 21) || (curtstnum == 04) ||
                              (curtstnum == 29) || (curtstnum == 30))     
                           {
                              buildPar.hstNamePrsnt = FALSE;
                              SB_EST_ASSOC(assoc_1, BIT0)
                              SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                           }
                           else
                           {
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                        } /*end bAssocSetupMask */
                     } /* end bTSapMask */
                  } /* end bTraceMask if */
               }/*end TSapCfgMask if*/
            } /* end SctSapCfgMask if */
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {
              /* sb035.102 TermInd aftre the shutdown comp */
              case 01:      /* Test O.205.01: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:  /* Send a SHUTDOWN with AbrtFlg = False */
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE ) && 
                            (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE ))
                        {      
                           SPrint("\n\n == SENDING SHUTDOWN CHUNK ==\n");
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.chunkId = SB_ID_SDOWN;
                           buildPar.cumTsn = (assoc_1.verTagPeer - 1 );
                           buildShutdwnChunk(mBuf, &buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        }
                        break;                      
                     case 2:  /* Shutdown Ack chunk */
                        break;                      
                     case 3:
                        SPrint(" == SENDING SHUTDOWN COMPLETE CHUNK ==\n");
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildShutdwnCmplChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst,
                                               SUID_0,assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        oper.it.status = SCT_STATUS_SHUTDOWN;
                        break;
                     case 4:  /* for checking ACC_EVT_TERM_IND */
                        /* expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_TERM_IND;
                        break;
                  }
                  break;
               case 2: /*-- Test O.205.02: Execution --*/
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 10;
                        buildPar.inStrms = 10;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 3:
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        break;
                     case 4:
                        cmMemcpy((U8 *) &assoc_2, (U8 *) &assoc_1,
                                 sizeof(SbAccAssoc));

                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 1;
                        buildPar.inStrms = 1;
                        /* different peer tag */
                        buildInitChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        buildPar.newAddr = TRUE;/* Reset the flag, so that it wont affect other test cases */
                        break;
                   }
                break;
             case 3:   /* Test O.205.03: Execution --*/
                if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) &&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                {
                   SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                   buildPar.streamId = 1;
                   buildPar.tsn = ACC_INIT_TSN;
                   buildPar.seqNr = 0;
                   buildPar.chunkFlg = 3;     /* set up for sequenced delivery --*/
                   buildPar.noData = TRUE;     /* Send no data --*/
                   buildDataChunk(mBuf,&buildPar,&assoc_1);
                   SB_SETUP_IPHDR_PAR(NOFRAGM)
                   /* sb032.102 :  IPV6 Support Added --*/
                   (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                          &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                          &assoc_1.localIf,
#endif
                                          mBuf);
                   buildPar.noData = FALSE;     /* reset the flag --*/
                   sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                }
                break;
             case 4:/* Test O.205.04: Execution */
                SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                buildUnrecogChunk(mBuf,&buildPar, &assoc_1);
                SB_SETUP_IPHDR_PAR(NOFRAGM)
                 /* sb032.102 :  IPV6 Support Added */
                (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                       assoc_1.suConId,
                                       &assoc_1.peerTAddr,
                                       &assoc_1.localTAddr,
                                       &hdrParm ,
#ifdef LOCAL_INTF
                                       &assoc_1.localIf,
#endif
                                       mBuf);
                sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                break;
             case 5: /* Test O.205.05: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, 
                                             SB_ACC_SCT_TOS, (Buffer *)NULLP);
#else
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, (Buffer *)NULLP);
#endif /* SCT3 */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.chunkId = SB_ID_ABORT;
                      buildPar.causeCode = SB_CHUNK_ERROR_PARAM;
                      buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                             &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                      /*expected results */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                      break;
                }
                break;
             case 6: /* Test O.205.06: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
#ifdef SCT3
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, 
                                             SB_ACC_SCT_TOS, (Buffer *)NULLP);
#else
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, (Buffer *)NULLP);
#endif /* SCT3 */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.chunkId = SB_ID_ABORT;
                      buildPar.causeCode = SB_CHUNK_ERROR_STREAM;
                      buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                             &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                      /*expected results */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                      break;
                }
                break;
             case 7:    /* Test O.205.07: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
                   SPrint(" Send TermReq \n");
                   /* Send a TermReq with AbrtFlg = False */
                   (void)  ItLiSctTermReq(&sbAccCb.itPst, assoc_1.spId,
                                          assoc_1.spAssocId, SCT_ASSOCID_SP,
                                          SHTDWN);
                   sbAccCb.curTst.evtType = ACC_EVT_TERM_CFM;
                   break;
                }
                break;
             case 8: /* Test O.205.08: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
#ifdef SCT3
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, 
                                             SB_ACC_SCT_TOS, (Buffer *)NULLP);
#else
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, (Buffer *)NULLP);
#endif /* SCT3 */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:  
                      if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE ) &&
                            ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE )  )
                      {
                         SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                         buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                         SB_SETUP_IPHDR_PAR(NOFRAGM)
                         /* sb032.102 :  IPV6 Support Added */
                         (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                assoc_1.suConId, \
                                                &assoc_1.peerTAddr, \
                                                &assoc_1.localTAddr, \
                                                &hdrParm , 
#ifdef LOCAL_INTF
                                                &assoc_1.localIf,  
#endif
                                                mBuf);
                         /* expected results */
                         sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                      }
                      break;
                }
                break;
             case 9: /* O.205.09: Execution  */
                SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters for data transmission */
                dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                     assoc_1.spAssocId, \
                                     &dfltPriPeerNAddr, \
                                     ACC_STREAMID, ORDER, \
                                     BUNDLE, ACC_NO_LIFETM_LIM, \
                                     ACC_PROT_ID, mBuf);
                sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                break;
             case 10:/* Test O.205.10: Execution */
                SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                buildPar.pkUnknownPar = TRUE;
                buildPar.outStrms = 4;
                buildPar.inStrms = 5;
                buildInitChunk(mBuf,&buildPar, &assoc_1);
                SB_SETUP_IPHDR_PAR(NOFRAGM)
                /* sb032.102 :  IPV6 Support Added */
                (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                       assoc_1.suConId,
                                       &assoc_1.peerTAddr,
                                       &assoc_1.localTAddr,
                                       &hdrParm ,
#ifdef LOCAL_INTF
                                       &assoc_1.localIf,
#endif
                                       mBuf);
                buildPar.pkUnknownPar = FALSE;
                sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                break;
             case 11: /* Test O.205.11: Execution */
                switch(sbAccCb.curTst.subTest)
                { 
                   case 1:
                      sbAccCb.curTst.tickLstDoneFlg = TRUE;
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.streamId = 1;
                      buildPar.tsn = ACC_INIT_TSN;
                      buildPar.seqNr = 0;
                      /*buildPar.chunkFlg = 3; */     /* set up for sequenced delivery --*/
                      buildPar.chunkFlg = 0x02; 
                      /* sb013.103: New function to build data Chunk with size 512 */
                      buildLargeDataChunk(mBuf,&buildPar,&assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added --*/
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                             &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                      break;
                   case 2:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.streamId = 1;
                      buildPar.tsn = ACC_INIT_TSN;
                      buildPar.seqNr = 0;
                      buildPar.chunkFlg = 0x02;     /* set up for sequenced delivery --*/
                      /* sb013.103: New function to build data Chunk with size 512 */
                      buildLargeDataChunk(mBuf,&buildPar,&assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added --*/
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                             &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                          mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                      break;
                   case 3:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.streamId = 1;
                      buildPar.tsn = ACC_INIT_TSN + 2;
                      buildPar.seqNr = 0;
                      buildPar.chunkFlg = 0x01;
                      /* sb013.103: New function to build data Chunk with size 512 */
                      buildLargeDataChunk(mBuf,&buildPar,&assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added --*/
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                             &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                          mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                      break;
                   case 4:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.streamId = 1;
                      buildPar.tsn = ACC_INIT_TSN + 1;
                      buildPar.seqNr = 0;
                      buildPar.chunkFlg = 0x00;
                      /* sb013.103: New function to build data Chunk with size 512 */
                      buildLargeDataChunk(mBuf,&buildPar,&assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added --*/
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                             &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                          mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                      break;
                }
                break;
             case 12:     /* Test O.205.12: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
                      vsInfo = (Buffer *) NULLP;
/* sb060.102: TOS changes. */
#ifdef SCT3
                      ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                      assoc_1.spEndpId, assoc_1.suAssocId,
                                      &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                      assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                      &assoc_1.localNAddrLst, SB_ACC_SCT_TOS, 
                                      vsInfo);
#else
                      ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                      assoc_1.spEndpId, assoc_1.suAssocId,
                                      &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                      assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                      &assoc_1.localNAddrLst, vsInfo);
#endif /* SCT3 */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:    /* INIT_ACK chunk */
                      if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                           (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                      {
                         SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                         buildPar.inStrms = 10;
                         buildPar.outStrms =  10;
                         buildPar.pkUnknownPar = TRUE;
                         buildInitAckChunk(mBuf, &buildPar,&assoc_1);
                         SB_SETUP_IPHDR_PAR(NOFRAGM)
                         /* sb032.102 :  IPV6 Support Added */
                         (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                assoc_1.suConId, \
                                                &assoc_1.peerTAddr, \
                                                &assoc_1.localTAddr, \
                                                &hdrParm ,
#ifdef LOCAL_INTF
                                                &assoc_1.localIf,
#endif
                                                mBuf);
                         sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                      }
                      break;
                }
                break;
             case 13:     /* Test O.205.13: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
                      (void)  HiUiHitDiscInd(&sbAccCb.hiPst, SUID_0, \
                                             1, assoc_1.suConId, 1);
                      break;
                   case 2:
                      break;
                }
                break;
             case 14:     /* Test O.205.14: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
                      SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters for data\
                                                transmission */
                      (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                           &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                           ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.chunkId = SB_ID_ABORT;
                      buildPar.causeCode = SB_CHUNK_ERROR_NO_USR_DATA;
                      /* sb030.103: Set the chunk flag to zero.  */
                      buildPar.chunkFlg = 0;
                      buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                             &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                      /*expected results */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                      break;
                }
                break;
             case 15:   /* Test O.205.15: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.chunkId = SB_ID_ABORT;
                      buildPar.causeCode = SB_CHUNK_ERROR_USR_INITIATED_ABORT;
                      /* sb030.103: Set the chunkflag to zero. */
                      buildPar.chunkFlg = 0;
                      buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                             &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                      /*expected results */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                      break;
                   case 2:
                      break;
                }
                break;
             case 16:   /* Test O.205.16: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
                      vsInfo = (Buffer *) NULLP;
/* sb060.102: TOS changes. */
#ifdef SCT3
                      ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                      assoc_1.spEndpId, assoc_1.suAssocId,
                                      &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                      assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                      &assoc_1.localNAddrLst, SB_ACC_SCT_TOS, 
                                      vsInfo);
#else
                      ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                      assoc_1.spEndpId, assoc_1.suAssocId,
                                      &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                      assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                      &assoc_1.localNAddrLst, vsInfo);
#endif /* SCT3 */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                      if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                           (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                         {
                            SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                            buildPar.inStrms = 10;
                            buildPar.outStrms =  10;
                            buildInitAckChunk(mBuf, &buildPar,&assoc_1);
                            SB_SETUP_IPHDR_PAR(NOFRAGM)
                            /* sb032.102 :  IPV6 Support Added */
                            (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                   assoc_1.suConId, \
                                                   &assoc_1.peerTAddr, \
                                                   &assoc_1.localTAddr, \
                                                   &hdrParm ,
#ifdef LOCAL_INTF
                                                   &assoc_1.localIf,
#endif
                                                   mBuf);
                            sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                         }
                         break;
                      case 3:
                         SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                         buildPar.chunkId = SB_ID_ABORT;
                         buildPar.causeCode = SB_CHUNK_ERROR_STALE;
                         /* sb030.103: set the ABORT-chunk flag to ZERO. */
                         buildPar.chunkFlg = 0;
                         buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                         SB_SETUP_IPHDR_PAR(NOFRAGM)
                         /* sb032.102 :  IPV6 Support Added */
                         (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                assoc_1.suConId, \
                                                &assoc_1.peerTAddr, \
                                                &assoc_1.localTAddr, \
                                                &hdrParm ,
#ifdef LOCAL_INTF
                                                &assoc_1.localIf,
#endif
                                                mBuf);
                         /*expected results */
                         sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                         break;
                      case 4:
                         if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                              (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                         {
                            SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                            buildPar.inStrms = 10;
                            buildPar.outStrms =  10;
                            buildInitAckChunk(mBuf, &buildPar,&assoc_1);
                            SB_SETUP_IPHDR_PAR(NOFRAGM)
                            /* sb032.102 :  IPV6 Support Added */
                            (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                   assoc_1.suConId, \
                                                   &assoc_1.peerTAddr, \
                                                   &assoc_1.localTAddr, \
                                                   &hdrParm ,
#ifdef LOCAL_INTF
                                                   &assoc_1.localIf,
#endif
                                                   mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        }
                        break;
                     case 5:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.chunkId = SB_ID_ABORT;
                        buildPar.causeCode = SB_CHUNK_ERROR_STALE;
                        buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                       /*expected results */
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                    break;
                 }
                 break;
              case 17: /* O.205.17: Execution  */
                 SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters for data transmission */
                 dfltPriPeerNAddr.type = CM_INET_IPV4ADDR_TYPE;
                 dfltPriPeerNAddr.u.ipv4NetAddr = 0x1234;
                 (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                      assoc_1.spAssocId, \
                                      &dfltPriPeerNAddr, \
                                      ACC_STREAMID, ORDER, \
                                      BUNDLE, ACC_NO_LIFETM_LIM, \
                                      ACC_PROT_ID, mBuf);
                 sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                 break;
              case 18:   /* Test O.205.18: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters for data transmission */
                       dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                            assoc_1.spAssocId, \
                                            &dfltPriPeerNAddr, \
                                            ACC_STREAMID, ORDER, \
                                            BUNDLE, ACC_NO_LIFETM_LIM, \
                                            ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildPar.chunkId = SB_ID_ERROR;
                       buildPar.causeCode = SB_CHUNK_ERROR_STREAM;
                       buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                       /*expected results */
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                       break;
                 }
                 break;
              case 19:   /* Test O.205.19: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:
                       vsInfo = (Buffer *) NULLP;
/* sb060.102: TOS changes. */
#ifdef SCT3
                       ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                       assoc_1.spEndpId, assoc_1.suAssocId,
                                       &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                       assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                       &assoc_1.localNAddrLst, SB_ACC_SCT_TOS, 
                                       vsInfo);
#else
                       ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                       assoc_1.spEndpId, assoc_1.suAssocId,
                                       &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                       assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                       &assoc_1.localNAddrLst, vsInfo);
#endif /* SCT3 */
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                    break;
                     case 2:
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.chunkId = SB_ID_ERROR;
                           buildPar.causeCode = SB_CHUNK_ERROR_RES;
                           buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,
#endif
                                                  mBuf);
                           /*expected results */
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        }
                        break;
                 }
                 break;
              case 20:    /* Test O.205.20: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, \
                                               SB_ACC_SCT_TOS, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId,
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk */
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm , 
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,  
#endif
                                                  mBuf);
                           /* expected results */
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        }
                        break;
                     case 3:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
/* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                               &hdrParm , 
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,  
#endif
                                               mBuf);
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                        break;
                 }
                 break;
              case 21:    /* Test O.205.21: Execution */
                 switch(sbAccCb.curTst.subTest)
                 { 
                    case 1:
                       sbAccCb.curTst.tickLstDoneFlg = TRUE;
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildPar.streamId = 1;
                       buildPar.tsn = ACC_INIT_TSN;
                       buildPar.seqNr = 0;
                       buildPar.chunkFlg = 0x02;      /* set up for sequenced delivery --*/
                       buildDataChunk(mBuf,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added --*/
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                              &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                      break;
                   case 2:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.streamId = 1;
                      buildPar.tsn = ACC_INIT_TSN+1;
                      buildPar.seqNr = 0;
                      buildPar.chunkFlg = 0x01;     /* set up for sequenced delivery --*/
                      buildDataChunk(mBuf,&buildPar,&assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added --*/
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                             &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                          mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                      break;
                 }
                 break;
              case 22:    /* Test O.205.22: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, \
                                               SB_ACC_SCT_TOS, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                              assoc_1.spEndpId, \
                                              assoc_1.suAssocId,
                                              &assoc_1.priPeerNAddr, \
                                              assoc_1.peerPort, \
                                              assoc_1.outStrms, \
                                              &assoc_1.peerNAddrLst, \
                                              &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        /*expected results */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk */
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT3) == FALSE))
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.hstNamePrsnt = TRUE;
                           cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trillium1.com", 
                           cmStrlen((CONSTANT U8 *)"www.trillium1.com"));
                           buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                                  &hdrParm , 
#ifdef LOCAL_INTF
                                                  &assoc_1.localIf,  
#endif
                                                  mBuf);
                           /* expected results */
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        }
                        break;
                 }
                 break;
              case 24: /* Test O.205.24: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, 
                                             SB_ACC_SCT_TOS, (Buffer *)NULLP);
#else
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, (Buffer *)NULLP);
#endif /* SCT3 */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.chunkId = SB_ID_ERROR;
                      buildPar.causeCode = SB_CHUNK_ERROR_PARAM;
                      buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                             &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                      /*expected results */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                      break;
                }
                break;
             case 23: /* Test O.205.23: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, 
                                             SB_ACC_SCT_TOS, (Buffer *)NULLP);
#else
                      (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                             assoc_1.spEndpId, assoc_1.suAssocId,
                                             &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                             assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                             &assoc_1.localNAddrLst, (Buffer *)NULLP);
#endif /* SCT3 */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      buildPar.chunkId = SB_ID_ERROR;
                      buildPar.causeCode = SB_CHUNK_ERROR_UNRSLV_ADDR;
                      buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                             &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                      /*expected results */
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                      break;
                }
                break;

  	   /* sb012.103: Test case to check discarding COOKIE-ECHO Chunk if 
	    * peer address is non-unicast address
            */
	    case 25:  /* Test O.205.25 : Execution */
              switch(sbAccCb.curTst.subTest)
              {
                 case 1 :
                       /* Send an INIT chunk */
			SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 10;
                        buildPar.inStrms = 10;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;

                   break;
                                                                                                                  
                 case 2:
                   /* send cookie with peer addresss as non-unicast address */
			SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM);
#ifdef SB_IPV6_SUPPORTED
			nonUnicastAddr.type = CM_INET_IPV6ADDR_TYPE;
			CPY_ACC_ASSOC1_PEER_IPV6(nonUnicastAddr.u.ipv6TptAddr.ipv6NetAddr,5);
			nonUnicastAddr.u.ipv6TptAddr.port = assoc_1.localPort;
#else
			nonUnicastAddr.type = CM_INET_IPV4ADDR_TYPE;
        	        nonUnicastAddr.u.ipv4TptAddr.address = ACC_ASSOC3_DEST_1;
			nonUnicastAddr.u.ipv4TptAddr.port = assoc_1.localPort;
#endif
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &nonUnicastAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                                                                                                                       
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;

                   break;
               }
               break;
	     
 	    /* sb012.103: Test case to check discarding COOKIE-ECHO Chunk
	     * if peer address list contains non-unicast address
             */

            case 26:  /* Test O.205.26 : Execution */
              switch(sbAccCb.curTst.subTest)
              {
                 case 1 :
                       /* Send an INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 10;
                        buildPar.inStrms = 10;
			buildPar.hstNamePrsnt = FALSE;
			/* change the buildPar to bundle non-unicast IPV6 address if IPV6 supported */
#ifdef SB_IPV6_SUPPORTED
			buildPar.multAddrTypes = TRUE;
#endif /* SB_IPV6_SUPPORTED */

			/* Bundle non-unicast address in Init Chunk */
                        buildInitChunkUnicast(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
#ifdef SB_IPV6_SUPPORTED
			/* Reset the flag, so that it will not effect other test case */
			buildPar.multAddrTypes = FALSE; 
#endif /* SB_IPV6_SUPPORTED */

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                                                                                                                        
                   break;
		 case 2:
                   /*  send cookie */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM);

                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                                                                                                                        
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                                                                                                                        
                   break;
               }
              break;
            case 27: /* sb029.103: Test O.205.27 Execution */
              switch(sbAccCb.curTst.subTest)
              {
                 case 1:
                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                    assoc_1.peerPort = 0;
                    buildInitChunk(mBuf,&buildPar, &assoc_1);
                    SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                             assoc_1.suConId,
                             &assoc_1.peerTAddr,
                             &assoc_1.localTAddr,
                             &hdrParm ,
#ifdef LOCAL_INTF
                             &assoc_1.localIf,
#endif
                             mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                    break;
              }
              break; /* case 27: */

            case 28: /* sb030.103: Test O.205.28 Execution */
              switch(sbAccCb.curTst.subTest)
              {
                 case 1:
#ifdef SCT3
                    (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                           assoc_1.spEndpId, \
                                           assoc_1.suAssocId, \
                                           &assoc_1.priPeerNAddr, \
                                           assoc_1.peerPort, \
                                           assoc_1.outStrms, \
                                           &assoc_1.peerNAddrLst, \
                                           &assoc_1.localNAddrLst, \
                                           SB_ACC_SCT_TOS, \
                                           (Buffer*)NULLP);
#else
                    (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                           assoc_1.spEndpId, \
                                           assoc_1.suAssocId,
                                           &assoc_1.priPeerNAddr, \
                                           assoc_1.peerPort, \
                                           assoc_1.outStrms, \
                                           &assoc_1.peerNAddrLst, \
                                           &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                    /*expected results */
                    sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                    break;
                 case 2:
                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                    assoc_1.verTagPeer = 100;
                    buildShutdwnAckChunk(mBuf,&buildPar,&assoc_1);
                    SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst,
                                              SUID_0,assoc_1.suConId,
                                              &assoc_1.peerTAddr,
                                              &assoc_1.localTAddr,
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                    break; 
              }
              break;
            case 29:      /* sb030.103: Test O.205.29: Execution */
              switch( sbAccCb.curTst.subTest)
              {
                 case 1:
                    SPrint("\n\n == SENDING SHUTDOWN CHUNK ==\n");
                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                    buildPar.chunkId = SB_ID_SDOWN;
                    buildPar.cumTsn = (assoc_1.verTagPeer - 1 );
                    buildShutdwnChunk(mBuf, &buildPar, &assoc_1);
                    SB_SETUP_IPHDR_PAR(NOFRAGM)
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &assoc_1.peerTAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                    break;
                 case 2:  /* Shutdown Ack chunk */
                    break;
                 case 3:
                    SPrint(" == SENDING SHUTDOWN COMPLETE CHUNK ==\n");
                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                    buildPar.chunkFlg = 1; /* set the T-bit to one. */ 
                    buildShutdwnCmplChunk(mBuf,&buildPar,&assoc_1);
                    SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst,
                                              SUID_0,assoc_1.suConId,
                                              &assoc_1.peerTAddr,
                                              &assoc_1.localTAddr,
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                    oper.it.status = SCT_STATUS_SHUTDOWN;
                    break;
              }
              break;
              /* sb030.103: Added new test case O.205.30 */
            case 30:    /* Test O.205.30: Execution */
              switch(sbAccCb.curTst.subTest)
              {
                 case 1:/* send DATA chunk with invalid stream identifier. */
                    sbAccCb.curTst.tickLstDoneFlg = TRUE;
                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                    buildPar.streamId = 11; 
                    buildPar.tsn = ACC_INIT_TSN;
                    buildPar.seqNr = 0;
                    buildPar.chunkFlg = 0x03;      /* set up for sequenced delivery --*/
                    buildDataChunk(mBuf,&buildPar,&assoc_1);
                    SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added --*/
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                              &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                    break;
              }
              break;

            } /* end switch curtstnum #1 */

            sbAccCb.curTst.state++;
            break;

         /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {
               /* wait for message to reach the queue */

               RETVALUE(ROK);
            }
            else if (status == TIMEOUT)
            {
               /* sb030.103: Added new test case O.205.29. */ 
               if ( (curtstnum == 6 ) || ((curtstnum == 15 ) && (sbAccCb.curTst.subTest == 2)) ||
                    ((curtstnum == 18 ) && (sbAccCb.curTst.subTest == 2)) ||
                    ((curtstnum == 20 ) && (sbAccCb.curTst.subTest == 4)) ||
                    ((curtstnum == 25 ) && (sbAccCb.curTst.subTest == 2)) ||
                    ((curtstnum == 26 ) && (sbAccCb.curTst.subTest == 2)) ||
                    ((curtstnum == 29 ) && (sbAccCb.curTst.subTest == 3)))
               {
                  sbAccCb.curTst.subTestsPass++;
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  break;
               }
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            {
               /*primitive received */
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */

                     /* sb035.102 Receive TermInd after ShutDown comp */
                  case 1:   /* Test O.205.01: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SPrint("\n\n == Checking for SHUTDOWNACK CHUNK ==\n");
                              /* Check SHUTDOWN_ack chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              if(ret != ROK) SPrint("\n\n == ERROR in  SHUTDOWNACK CHUNK ==\n");
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if(msg->evntType == ACC_EVT_TERM_IND)
                           { 
                              SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_SHUTDOWN, SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                              if (ret!= ROK)SPrint(" \n ===== TermInd with error ==== \n\n ");
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              SPrint(" \n ===== Not Recevide TermInd at the user oF SCTP ==== \n ");
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                           
                           case  2:
                              sbAccPeekMsg(&msg);
                              if (msg->evntType == ACC_EVT_UDAT_REQ)
                              {
                                 /* Check SHUTDOWN_ack chunk */
                                 SPrint("\n\n == Checking for SHUTDOWNACK CHUNK ==\n");
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNACK)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                                 if(ret != ROK) SPrint("\n\n == ERROR in  SHUTDOWNACK CHUNK ==\n");
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              }
                              break;
                            
                           case 3:
                              SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_SHUTDOWN_CMPLT, SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                              if (ret!= ROK)SPrint(" \n ===== TermInd with error ==== \n\n ");
                              break;
                     }
                     break; 
                  case 2: /*-- O.205.02: Expected results --*/
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* we expect a COMM UP status indication */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL )
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {

                              if(isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)
                              {
                                 printf("\n\nreceived HBEAT\n\n");
                                 /* RFC 4460 upgrade -- expect the probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              else
                              {
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_STREAM, 0, FALSE, SB_ID_ABORT)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                                 printf("\n\nreceived ABORT\n\n");
                              }
                           }
                           else
                           {
                              printf("\n\nreceived !@#$#$\n\n");
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                     }
                     break;
                  case 3:/*--  Test O.205.03: Expected Results --*/
                     sbAccPeekMsg(&msg);
                     /* Check TermInd */
                     if (msg->evntType == ACC_EVT_TERM_IND)
                     {
                        SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                        SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_NOUSR_DATA)
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                        if (ret!= ROK)SPrint(" \n ===== TermInd with error ==== \n\n ");
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if (msg->evntType == ACC_EVT_UDAT_REQ)
                     {
                        SPrint(" \n =====Recevide ABORT ==== \n ");
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_NO_USR_DATA, 0, FALSE, SB_ID_ABORT)
                        ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                     }
                     else
                     {
                        status = INC_EVNTTYPE;
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        ret = RFAILED;
                     }
                     break;
                  case 4: /* O.205.04 Expected results */
                     SPrint(" \n =====Recevide ERROR ==== \n ");
                     oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_UNRECOG_CHUNK, 0, FALSE, SB_ID_ERROR)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                     break;
                  case 5: /* O.205.05 Expected results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           break;
                     }
                    break;
                   case 6: /* O.205.06 Expected results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                    case 2:
                          break;
                     }
                    break;
               case 7:    /* Test O.205.07: Expected results */
                switch ( sbAccCb.curTst.subTest )
                {
                  case 1:
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                        ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                  break;
                  case 2:
                           sbAccPeekMsg(&msg);
                          /* Check TermInd */
                           if (msg->evntType == ACC_EVT_TERM_CFM)
                           {
                              SPrint(" \n =====Recevide Termcfm at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_CFM(assoc_1, SCT_NOK, SCT_CAUSE_REM_UNREACH)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status, &reason);
                              if (ret!= ROK)SPrint(" \n ===== TermInd with error ==== \n\n ");
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SPrint(" \n =====Recevide ABORT ==== \n ");
                                 oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_NO_USR_DATA, 0, FALSE, SB_ID_ABORT)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
               case 8:    /* Test O.205.08: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_ASSOC_CFM, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                         case 3:
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                            break;
                     } /*end switch */
                    break;
                 case 9: /* O.205.09: Expected Results */
                    switch( sbAccCb.curTst.subTest )
                    {
                        case 1:
                           /* Check DATA chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 2:
                           /* Check DATA chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                      }
                      break;
                   case 10: /* O.205.10 Expected results */
                     SPrint(" \n =====Recevide ERROR ==== \n ");
                     oper.hi.spId = SPID_0;
                     /* sb001.103: Now we get INIT-ACK, and not the ERROR */
                     SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                     /* SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_UNRECOG_PAR, 0, FALSE, SB_ID_ERROR)*/
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                     break;
                   case 11:/* O.205.11 Expected results */
                     switch( sbAccCb.curTst.subTest )
                     {
                        case 1:
                        SPrint(" \n =====Recevide SACK==== \n ");
                        SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                        break; 
                   case 2:
                           SPrint(" \n =====Recevide SACK2==== \n ");
                        SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break; 
                   case 3:
                           SPrint(" \n =====Recevide SACK3==== \n ");
                        SB_SETUP_SACK_INFO(2, 2, ACC_INIT_TSN)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break; 
                   case 4:
                           SPrint(" \n =====Recevide SACK4==== \n ");
                        SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break; 
                   case 5:
                           SPrint(" \n =====Recevide SACK5==== \n ");
                        SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN+1)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break; 
                     }
                     break;
                  case 12:    /* Test O.205.12: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check INIT chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                  &assoc_1, &status);
                            break;
                         case 2:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_ASSOC_CFM)
                            {
                               SB_SETUP_ASSOC_CFM(assoc_1)
                               ret = sbSctChkCfm(&oper, &mgmt, \
                                                 ACC_EVT_ASSOC_CFM, \
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               /* Check COOKIE chunk */
                               oper.hi.spId = SPID_0;
                               SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                     &assoc_1, &status);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                  case 13:    /* Test O.205.13: Expected Results */
                     switch(sbAccCb.curTst.subTest)
                     {
                       case 1:
                       ret = ROK;
                      break;
                       case 2:
                       ret = ROK;
                      break;
                       case 3:
                       ret = ROK;
                      break;
                       case 4:
                       ret = ROK;
                      break;
                     }
                      break;
                  case 14:    /* Test O.205.14: Expected Results */
                     switch(sbAccCb.curTst.subTest)
                     {
                       case 1:
                          /* Check DATA chunk */
                          SPrint("Wait for UDatReq \n ");
                          oper.hi.spId = SPID_0;
                          SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                          ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                      break;
                       case 2:
                              SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_NOUSR_DATA)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                              if (ret!= ROK)SPrint(" \n ===== TermInd with error ==== \n\n ");
                      break;
                     }
                      break;
                  case 15:    /* Test O.205.15: Expected Results */
                     switch(sbAccCb.curTst.subTest)
                     {
                       case 1:
                              SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_ABRT, SCT_CAUSE_NOT_APPL) /* new cause need to be defined */
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                              if (ret!= ROK)SPrint(" \n ===== TermInd with error ==== \n\n ");
                      break;
                       case 2:
                              SPrint(" \n =====Recevide Unexpected message==== \n ");
                              ret = RFAILED;
                      break;
                     }
                      break;
                  case 16:    /* Test O.205.16: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check INIT chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                  &assoc_1, &status);
                            break;
                         case 2:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_ASSOC_CFM)
                            {
                               SB_SETUP_ASSOC_CFM(assoc_1)
                               ret = sbSctChkCfm(&oper, &mgmt, \
                                                 ACC_EVT_ASSOC_CFM, \
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               /* Check COOKIE chunk */
                               oper.hi.spId = SPID_0;
                               SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                     &assoc_1, &status);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
#ifdef COMMENTED
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_INIT )
                              {
                               
                                 /* Check INIT chunk */
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                  &assoc_1, &status);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              if ( ID == SB_ID_COOKIE )
                              {
                               }
#endif
                            }
                            else
                            {
                               status = INC_EVNTTYPE;
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                               ret = RFAILED;
                            }
                            break;
                         case 3:
                            /* Check INIT chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                  &assoc_1, &status);
                            break;
                           case 4:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_ASSOC_CFM)
                            {
                               SB_SETUP_ASSOC_CFM(assoc_1)
                               ret = sbSctChkCfm(&oper, &mgmt, \
                                                 ACC_EVT_ASSOC_CFM, \
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               /* Check COOKIE chunk */
                               oper.hi.spId = SPID_0;
                               SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                     &assoc_1, &status);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else
                            {
                               status = INC_EVNTTYPE;
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                               ret = RFAILED;
                            }
                            break;
                           case 5:
                               ret = ROK;
                              break;
                      }
                      break;
                    case 17:   /* Test O.205.17: Expected Results */
                           /* Check DATA chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                      break;
                    case 18:   /* Test O.205.18: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                           /* Check DATA chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                         case 2:
                              SPrint(" \n =====Recevide Unexpected message==== \n ");
                              ret = RFAILED;
                           break;
                       }
                       break;
                    case 19:   /* Test O.205.19: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check INIT chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                  &assoc_1, &status);
                           break;
                         case 2:
                           sbAccPeekMsg(&msg);
                          /* Check TermInd */
                           if (msg->evntType == ACC_EVT_TERM_IND)
                           {
                              SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_OUTRES)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                              if (ret!= ROK)SPrint(" \n ===== TermInd with error ==== \n\n ");
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SPrint(" \n =====Recevide ABORT ==== \n ");
                                 oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_NO_USR_DATA, 0, FALSE, SB_ID_ABORT)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                  case 20:    /* Test O.205.20: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_ASSOC_CFM, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                            SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                           break;
                     } /*end switch */
                     break;
                  case 21:    /* Test O.205.21: Expected Results */
                     switch( sbAccCb.curTst.subTest )
                     {
                        case 1:
                        SPrint(" \n =====Recevide SACK==== \n ");
                        SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                        break; 
                   case 2:
                              SPrint(" \n =====Recevide ABORT ==== \n ");
                                 oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_RES, 0, FALSE, SB_ID_ABORT)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break; 
                      }
                     break;
                  case 22:    /* Test O.205.22: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                              SPrint("Receive INIT \n ");
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              SPrint("Receive SCT_STA_IND \n ");
                              mgmt.s.usta.event = LCM_EVENT_LYR_SPECIFIC;
                              mgmt.s.usta.cause = LSB_CAUSE_UNRSLVD_ADDR;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_STA_IND);
                             setBit(&sbAccCb.curTst.bTickMask, BIT3);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check DNS Query */
               ret = sbAccPopMsg(&msg);

                           count++;
                           if ( count == 1 )
                           {
                              printf("\n\n setting 0\n\n");
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else if ( count == 2 )
                           {
                              printf("\n\n setting 1\n\n");
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if ( count == 3 )
                           {
                              printf("\n\n setting 2\n\n");
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                           count = 0;
                           }
                           }
                           else
                           {
                              printf("\n\n failed \n\n");
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT3);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                     } /*end switch */
                     break;
                   case 24: /* O.205.24 Expected results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                              SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           break;
                     }
                     break;
                  case 23: /* O.205.23 Expected results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                              SPrint(" \n =====Recevide TermInd at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           break;
                     }
                    break;
                  /* sb032.102 :  IPV6 Support Added */

  	    /* sb012.103: Test case Added for non-unicast address issue fix */	
	     case 25: /* O.205.25 Expected results */
                   switch(sbAccCb.curTst.subTest)
                     {
                        case 1 :
                          /* Check for INIT ACK */
			   oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                          break;
                        case 2:
                           /* Dont expect anything */
			    SPrint("Ooops, something arrived that I'm not expecting\n\n\n");
                            ret = RFAILED;
                            break;
                     }
                   break;

	      /* sb012.103: Test case Added for non-unicast address issue fix */
             case 26: /* O.205.26 Expected results */
                   switch(sbAccCb.curTst.subTest)
                     {
                        case 1 :
                          /* Check for INIT ACK */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                          break;
                        case 2:
                           /* Dont expect anything */
                            SPrint("Ooops, something arrived that I'm not expecting\n\n\n");
                            ret = RFAILED;
                            break;
                     }
                   break;
             case 27: /*--sb029.103: O.205.27: Expected results --*/
                   switch( sbAccCb.curTst.subTest)
                   {
                      case 1:
                         /* Check ABORT chunk */
                         oper.hi.spId = SPID_0;
                         SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_INVAL_MAND_PAR, 0, FALSE, SB_ID_ABORT)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                         setBit(&sbAccCb.curTst.bTickMask, BIT0);
                         printf("\n\n received ABORT chunk  \n\n");
                         break;
                   }
                   break; 

             case 28: /* sb030.103: O.205.28 Expected results */
                   switch(sbAccCb.curTst.subTest)
                   {
                      case 1 :
                         /* Check for INIT  */
                         oper.hi.spId = SPID_0;
                         SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                         break;
                      case 2 :
                         sbAccPeekMsg(&msg);

                         /* Check SDOWNCMPLT chunk */
                         if (msg->evntType == ACC_EVT_UDAT_REQ)
                         {
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNCMPLT)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                         }
                         break;
                   }
                   break;
 
             case 29:   /* sb030.103: Test O.205.29: Expected Results */
                   switch( sbAccCb.curTst.subTest)
                   {
                      case 1:
                         sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_UDAT_REQ)
                         {
                            SPrint("\n\n == Checking for SHUTDOWNACK CHUNK ==\n");
                            /* Check SHUTDOWN_ack chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNACK)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                            if(ret != ROK)
                               SPrint("\n\n == ERROR in  SHUTDOWNACK CHUNK ==\n");
                         }
                         else if(msg->evntType == ACC_EVT_TERM_IND)
                         { 
                            SPrint(" \n ===== Recevied TermInd at the user oF SCTP ==== \n ");
                            SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_SHUTDOWN, SCT_CAUSE_NOT_APPL)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                            if (ret!= ROK)SPrint(" \n ===== TermInd with error ==== \n\n ");
                         }
                         else
                         {
                            SPrint(" \n ===== Not Recevied TermInd at the user oF SCTP ==== \n ");
                            status = INC_EVNTTYPE;
                            ret = RFAILED;
                         }
                         break;

                      case  2:
                         sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_UDAT_REQ)
                         {
                            /* Check SHUTDOWN_ack chunk */
                            SPrint("\n\n == Checking for SHUTDOWNACK CHUNK ==\n");
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNACK)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                            if(ret != ROK)
                               SPrint("\n\n == ERROR in  SHUTDOWNACK CHUNK ==\n");
                         }
                         else if(msg->evntType == ACC_EVT_TERM_IND)
                         {
                            SPrint(" \n ===== Recevied TermInd at the user oF SCTP ==== \n ");
                            SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_SHUTDOWN, SCT_CAUSE_NOT_APPL)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                            if (ret!= ROK)
                               SPrint(" \n ===== TermInd with error ==== \n\n ");
                         }
                         else
                         {
                            SPrint(" \n ===== Not Recevied TermInd at the user oF SCTP ==== \n ");
                            status = INC_EVNTTYPE;
                            ret = RFAILED;
                         }
                         break;

                      case 3:
                         SPrint(" \n =====  OOPS something arrived that I'm not expecting\n....\n  ");
                         break;
                   }
                   break;
                   /* sb030.103: Added test case O.205.30. */
             case 30:    /* Test O.205.30: Expected Results */
                   switch( sbAccCb.curTst.subTest )
                   {
                      case 1:
                         sbAccPeekMsg(&msg);
                         if (msg->evntType == ACC_EVT_UDAT_REQ)
                         {
                            SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                            if ( ID == SB_ID_ERROR)
                            {
                               oper.hi.spId = SPID_0;
                               SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_STREAM, 0, FALSE, SB_ID_ERROR)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if( ID == SB_ID_SACK )
                            {
                               SPrint(" \n =====Recevide SACK==== \n ");
                               SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN)
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else
                            {
                               status = INC_EVNTTYPE;
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               ret = RFAILED;
                            }
                            break;
                         }
                         break;
                   }/* O.205.30 expected results */
                   break;
 
             }      /* End switch(curtstnum) #2 */

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

                  /* sb032.102 :  IPV6 Support Added */
             if  ( (curtstnum == 1) && ((sbAccCb.curTst.subTest == 1) || (sbAccCb.curTst.subTest == 2)))
             {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
             }
            else if  ( (curtstnum == 2) && ((sbAccCb.curTst.subTest == 3) || (sbAccCb.curTst.subTest == 4)))
             {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
             }
            else if  ( (curtstnum == 3) )
             {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
             }
            else if  ( ((curtstnum == 7) || (curtstnum == 8)) && (sbAccCb.curTst.subTest == 2) )
             {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
             }
            else if  ( (curtstnum == 12)  && (sbAccCb.curTst.subTest == 2) )
             {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
             }
            else if  ( (curtstnum == 16)  && ( (sbAccCb.curTst.subTest == 2) || (sbAccCb.curTst.subTest == 4)) )
             {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
             }
             else if  (( (curtstnum == 19) || (curtstnum == 20) || (curtstnum == 22))  && (sbAccCb.curTst.subTest == 2) )
             {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
             }
             else if  ( (curtstnum == 22)  && (sbAccCb.curTst.subTest == 2))
             {
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT3) == TRUE) )
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  sbAccCb.curTst.bTickMask = 0;
               }
             }
             /* sb030.103: Added test case O.205.30 */
             else if( (curtstnum == 30) && (sbAccCb.curTst.subTest == 1))
             {
                if (( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                      ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
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
   {
      doCleanup();
   }

   RETVALUE(ROK);
}  /* end sbSctAssocSndTst_5 */

/*
*       Fun:   sbSctAssocSndTst_3
*
*       Desc:  Initialization and Termination of Association for the sending endpoint (#3).
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctAssocSndTst_3
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocSndTst_3(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   PRIVATE SbMgmtQElm    mgmt;
   PRIVATE SbOperQElm    oper;
   PRIVATE SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE SbAccChunkBld buildPar;             /* Information for checking the chunks */
   PRIVATE SbAccAssoc    assoc_1;
   PRIVATE SbAccAssoc    assoc_2;
   Buffer        *mBuf;
   Buffer        *vsInfo;
   SbAccMsgQElm  *msg;
   PRIVATE CmIpHdrParm   hdrParm;
   CmNetAddr      dfltPriPeerNAddr;

   TRC2(sbSctAssocSndTst_3)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            if ( curtstnum == 13 )
            {
               SB_TSAPCFG(SAP_2);
            }
            else
            {
               SB_TSAPCFG(SAP_1);
            }
            if ( (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE) ||
                 ( (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT1) == TRUE) &&
                   (curtstnum == 13) ) )
            {
               if ( curtstnum == 13 )
               {
                  SB_BIND_HITSAP(SUID_1, SPID_1, BIT1);
               }
               else
               {
                  SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
               }
               if ( (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE) ||
                    (isBitSet(sbAccCb.curTst.bTSapMask, BIT1) == TRUE) )
               {
                  SB_DISABLE_TRACE() /* disable trace */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     switch(curtstnum)/* Pretests continues */
                     {
                        case 9: /* pretests: O.201.09 */
                           if(isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                           {
                              sbStdSctSapCfg(&sbMgmt, SAP_1);
                              /* sb042.102: change the timer values */
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial = 5;
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin = 5;
                              sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                           }
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                              {
                                 SB_EST_ASSOC(assoc_1, BIT0)
                                 /*sb071.102 Accptance changes for Decreasing maxAssocReTx */
                                 sbAccCb.curTst.numSubTst = \
                                    (U8)(sbGlobalCb.genCfg.reConfig.maxAssocReTx + 3);
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                              }
                           }
                           break;
                        case 10: /* pretests: O.201.10 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                              {
                                 SB_EST_ASSOC(assoc_1, BIT0)
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                              }
                           }
                           break;
                        case 11: /* pretests: O.201.11 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        case 12: /* pretest: O.201.12 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        case 13:/* pretest : O.201.13 */
                           SB_SCTSAPCFG(SAP_2)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT1) == TRUE)
                           {
                              setupAssoc(&assoc_2, ASSOC_2);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT1 )
                           }
                           break;
                        default:
                           break;
                     } /*end curtstnum switch */
                  } /* end bTraceMask if */
               } /* end bTSapMask */
            }/*end TSapCfgMask if*/
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
               case 9:    /* Test O.201.09: Execution */
                  if ( sbAccCb.curTst.subTest == 1)
                  {
                     SPrint(" Send TermReq \n");
                     /* Send a TermReq with AbrtFlg = False */
                     (void)  ItLiSctTermReq(&sbAccCb.itPst, assoc_1.spId,
                                            assoc_1.spAssocId, SCT_ASSOCID_SP,
                                             SHTDWN);
                     sbAccCb.curTst.evtType = ACC_EVT_TERM_CFM;
                  }
                  else if ( sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1) )
                  {
                      sbAccCb.curTst.evtType = ACC_EVT_TERM_CFM;
                  }
                  else
                  {
                     sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                  }
                  break;
               case 10:     /* Test O.201.10: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1: /* Send a TermReq with AbrtFlg = False */
                        (void)  ItLiSctTermReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, SCT_ASSOCID_SP, SHTDWN);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected reply */
                        break;
                     case 2:
                        SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters for data transmission */
                        dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                        (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spAssocId, \
                                             &dfltPriPeerNAddr, \
                                             ACC_STREAMID, ORDER, \
                                             NOBUNDLE, ACC_NO_LIFETM_LIM, \
                                             ACC_PROT_ID, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                        break;
                  }
                  break;
               case 11:     /* Test O.201.11: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        vsInfo = (Buffer *) NULLP;
/* sb060.102: TOS changes. */
#ifdef SCT3
                        ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                        assoc_1.spEndpId, assoc_1.suAssocId,
                                        &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                        assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                        &assoc_1.localNAddrLst, SB_ACC_SCT_TOS, 
                                        vsInfo);
#else
                        ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                        assoc_1.spEndpId, assoc_1.suAssocId,
                                        &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                        assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                        &assoc_1.localNAddrLst, vsInfo);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;
                     case 2:    /* INIT_ACK chunk */
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.inStrms = buildPar.outStrms;
                           buildPar.outStrms =  (U16)(sbMgmt.t.cfg.s.genCfg.maxNmbOutStrms + 2);
                           buildInitAckChunk(mBuf, &buildPar,&assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                  assoc_1.suConId, \
                                                  &assoc_1.peerTAddr, \
                                                  &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                                   &assoc_1.localIf,
#endif
                                                  mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                        }
                        break;
                  }
                  break;
               case 12:      /* Test O.201.12: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {   /* Use Sct SAP with negAbrtFlg = LSB_ASSOC_NEG */
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                        assoc_1.spEndpId, assoc_1.suAssocId,
                                        &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                        assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                        &assoc_1.localNAddrLst, 
                                        SB_ACC_SCT_TOS, (Buffer *)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId,
                                       assoc_1.spEndpId, assoc_1.suAssocId,
                                       &assoc_1.priPeerNAddr,assoc_1.peerPort,
                                       assoc_1.outStrms, &assoc_1.peerNAddrLst,
                                       &assoc_1.localNAddrLst, (Buffer *)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;
                     case 2:    /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        {
                           U16   tmp;
                           tmp = buildPar.outStrms;
                           buildPar.outStrms = buildPar.inStrms;
                           buildPar.inStrms = (U16)(tmp - 1);
                        }
                        buildInitAckChunk(mBuf, &buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst,
                                               SUID_0, assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                           (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                        {
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                        }
                        break;
                     case 3:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf, &buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                        break;
                  }
                  break;
               case 13:      /* Test O.201.13: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               assoc_2.suAssocId, \
                                               &assoc_2.priPeerNAddr, \
                                               assoc_2.peerPort, \
                                               assoc_2.outStrms, \
                                               &assoc_2.peerNAddrLst, \
                                               &assoc_2.localNAddrLst, \
                                               SB_ACC_SCT_TOS, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               assoc_2.suAssocId, \
                                               &assoc_2.priPeerNAddr, \
                                               assoc_2.peerPort, \
                                               assoc_2.outStrms, \
                                               &assoc_2.peerNAddrLst, \
                                               &assoc_2.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;
                     case 2:    /* INIT_ACK chunk */
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           {
                              U16   tmp;
                              tmp = buildPar.outStrms;
                              buildPar.outStrms = buildPar.inStrms;
                              buildPar.inStrms = (U16)(tmp - 1);
                           }
                           buildInitAckChunk(mBuf, &buildPar, &assoc_2);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                                  assoc_2.suConId, \
                                                  &assoc_2.peerTAddr, \
                                                  &assoc_2.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                                  &assoc_2.localIf,
#endif
                                                  mBuf);
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                        }
                        break;
                  }
                  break;
            } /* end curtstnum switch # 1 */
            sbAccCb.curTst.state++;
            break;
         /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if (status == TIMEOUT)
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   sbAccCb.curTst.evtType,
                                   TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
			{  /* primitive received */
				reason = 0;
				switch(curtstnum)
				{/* Start switch(curtstnum) #2 */
					case 9:    /* Test O.201.09: Expected Results */
						if (sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1) )
						{
							SB_SETUP_TERM_CFM(assoc_1,SCT_NOK, SCT_CAUSE_REM_UNREACH)
								ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status, &reason);
						}
						else
						{  /* Check SHUTDOWN chunk */
							oper.hi.spId = SPID_0;
							SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
								ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
						}
						break;
					case 10:    /* Test O.201.10: Expected Results */
						switch( sbAccCb.curTst.subTest)
						{
							case 1:/* Check SHUTDOWN chunk */
								oper.hi.spId = SPID_0;
								SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
									ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
								break;
							case 2:/* Receive a StaInd - shutdown in progress */
								SB_SETUP_STA_IND(assoc_1, SCT_STATUS_SND_FAIL, SCT_CAUSE_SHUTDOWN_PRGS)
								/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
								oper.it.protId = ACC_PROT_ID;
#endif
								ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
								break;
						}
						break;
					case 11:    /* Test O.201.11: Expected Results */
						switch(sbAccCb.curTst.subTest)
						{
							case 1:  /* Check INIT chunk */
								oper.hi.spId = SPID_0;
								SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
									ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
								break;
							case 2: /* Check ABORT chunk and TermInd */
								sbAccPeekMsg(&msg);
								if (msg->evntType == ACC_EVT_UDAT_REQ)
								{
									oper.hi.spId = SPID_0;
									/* SB_VER13 Error cause change from  SB_CHUNK_ERROR_STREAM to
									 * SB_CHUNK_ERROR_INVAL_MAND_PAR */
									SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_INVAL_MAND_PAR, 0, FALSE, SB_ID_ABORT)
										ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
									setBit(&sbAccCb.curTst.bTickMask, BIT1);
								}
								else if (msg->evntType == ACC_EVT_TERM_IND)
								{
									/* sb008.103: Modified after adding new values for the status field  */
#ifdef SCT_ENHANCED_TERMIND
									SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_ABORT_SENT, SCT_CAUSE_INIT_FAILED)
#else
										SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED)
#endif
										ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
									setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                     }
                     break;
                  case 12:   /* Test O.201.12: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,
                                                 &assoc_1, &status   );
                           break;
                        case 2:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_ASSOC_CFM)
                            {
                               SB_SETUP_ASSOC_CFM(assoc_1)
                               ret = sbSctChkCfm(&oper, &mgmt, \
                                                 ACC_EVT_ASSOC_CFM, \
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               /* Check COOKIE chunk */
                               oper.hi.spId = SPID_0;
                               SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                               ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,
                                                     &assoc_1, &status);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP,
                                            SCT_CAUSE_NOT_APPL )
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND,
                                             &status, &reason);
                           break;
                     }
                     break;
                  case 13:    /* Test O.201.13: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_1;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,
                                                 &assoc_2, &status );
                           break;
                        case 2:
                           /* Check ABORT chunk and TermInd */
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              oper.hi.spId = SPID_1;
                          /* SB_VER13 -Error cause SB_CHUNK_ERROR_STREAM to 
                           * SB_CHUNK_ERROR_INVAL_MAND_PAR */
                              SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_INVAL_MAND_PAR, 0,
                                                  FALSE, SB_ID_ABORT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,
                                                    &assoc_2, &status );
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else if (msg->evntType == ACC_EVT_TERM_IND)
                           {
			   /* sb008.103: Modified after adding new values for the status field  */
#ifdef SCT_ENHANCED_TERMIND
                              SB_SETUP_TERM_IND(assoc_2, SCT_STATUS_ABORT_SENT, SCT_CAUSE_INIT_FAILED)
#else
                              SB_SETUP_TERM_IND(assoc_2, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED)
#endif
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND,
                                                &status, &reason);
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
                     }
                     break;
               }      /* End switch(curtstnum) #2 */

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
            }  /*end primitive received */

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
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbSctAssocSndTst_3 */

/*
*       Fun:   sbSctAssocSndTst_4
*
*       Desc:  Initialization and Termination of Association for the sending endpoint (#4).
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctAssocSndTst_4
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocSndTst_4(curtstnum, numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   PRIVATE SbMgmtQElm        mgmt;
   PRIVATE SbOperQElm        oper;
   PRIVATE SbMgmt    sbMgmt;
   SctStatus         status;
   Reason            reason;
   S16               ret;
   SbGenReCfg        *genReCfg;
   PRIVATE SbAccChunkBld     buildPar;            /* Information for checking the chunks */
   PRIVATE SbAccAssoc        assoc_1;
   PRIVATE SbAccAssoc        assoc_2;
   Buffer            *mBuf;
   CmIpHdrParm       hdrParm;
   SbAccMsgQElm      *msg;


   TRC2(sbSctAssocSndTst_4)
   ret = ROK;
   genReCfg = (SbGenReCfg *)NULLP;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      if ( curtstnum == 16)
      {
         if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
         {
            /* use lesser INIT retransmission count */
            sbStdGenCfg(&sbMgmt);
            sbMgmt.t.cfg.s.genCfg.reConfig.maxInitReTx = 2;
            sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
         }
      }
      else
      {
         SB_GENCFG()
      }
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            SB_TSAPCFG(SAP_1)
            if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
            {
               SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
               if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
               {
                  SB_TSAPCFG(SAP_2)
                  if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT1) == TRUE)
                  {
                     SB_BIND_HITSAP(SUID_1, SPID_1, BIT1)
                     if (isBitSet(sbAccCb.curTst.bTSapMask, BIT1) == TRUE)
                     {
                        SB_DISABLE_TRACE() /* disable trace */
                        if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                        {
                           switch(curtstnum)/* Pretests continues */
                           {
                              case 14: /* pretests: O.201.14 */
                                 SB_SCTSAPCFG(SAP_1)
                                 if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                                 {
                                    setupAssoc(&assoc_1, ASSOC_1);
                                    if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                                    {
                                       SB_EST_ASSOC(assoc_1, BIT0)
                                       if(isBitSet(sbAccCb.curTst.bAssocMask, BIT0) == TRUE )
                                       {
                                          SB_SCTSAPCFG(SAP_2)
                                          if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT1) == TRUE)
                                          {
                                             setupAssoc(&assoc_2, ASSOC_2);
                                             SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT1 )
                                          }
                                       }
                                    }
                                 }
                                 break;
                              case 15: /* pretests: O.201.15 */
                                 SB_SCTSAPCFG(SAP_1)
                                 if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE) {
                                    setupAssoc(&assoc_1, ASSOC_1);
                                    SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                                 }
                                 break;
                              case 16: /* pretests: O.201.16 */
                                 if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                                 {
                                    /* use lesser INIT TO */
                                    sbStdSctSapCfg(&sbMgmt, SAP_1);
                                    sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial = 5;
                                    sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin = 5;
                                    sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                                 }
                                 if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                                 {
                                    setupAssoc(&assoc_1, ASSOC_1);
                                    SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                                    sbAccCb.curTst.numSubTst = \
                                       (U8)(sbGlobalCb.genCfg.reConfig.maxInitReTx + 3);
                                 }
                                 break;
                              default:
                                 break;
                           }/*end curtstnum switch */
                        }/* end bTraceMask if */
                     }/* end bTSapMask */
                  }/*end TSapCfgMask if*/
               }/* end bTSapMask */
            }/*end TSapCfgMask if*/
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
               case 14:     /* Test O.201.14: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        ItLiSctAssocReq(&sbAccCb.itPst, SPID_1, \
                                        assoc_2.spEndpId, \
                                        assoc_2.suAssocId, \
                                        &assoc_2.priPeerNAddr, \
                                        assoc_2.peerPort, \
                                        assoc_2.outStrms, \
                                        &assoc_2.peerNAddrLst, \
                                        &assoc_2.localNAddrLst, \
                                        SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                        ItLiSctAssocReq(&sbAccCb.itPst, SPID_1, \
                                        assoc_2.spEndpId, \
                                        assoc_2.suAssocId, \
                                        &assoc_2.priPeerNAddr, \
                                        assoc_2.peerPort, \
                                        assoc_2.outStrms, \
                                        &assoc_2.peerNAddrLst, \
                                        &assoc_2.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected reply */
                        break;
                     case 2:    /* INIT_ACK chunk */
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildInitAckChunk(mBuf,&buildPar, &assoc_2);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                           /* sb032.102 :  IPV6 Support Added */
                           HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                          assoc_2.suConId, \
                                          &assoc_2.peerTAddr, \
                                          &assoc_2.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                          &assoc_2.localIf,
#endif
                                          mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        }
                        break;
                     case 3:    /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                             assoc_2.suConId, \
                                             &assoc_2.peerTAddr, \
                                             &assoc_2.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_2.localIf,
#endif
                                             mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND; /* expected reply */
                        break;
                     default:
                         break;
                  }
                  break;
               case 15:     /* Test O.201.15: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, \
                                             SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT_ACK chunk with missing cookie */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.misChunk = TRUE;
                        buildInitAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     default:
                        break;
                  }
                  break;
               case 16:      /* Test O.201.16: Execution */
                  if ( sbAccCb.curTst.subTest == 1)
                  {
/* sb060.102: TOS changes. */
#ifdef SCT3
                     ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                           assoc_1.spEndpId, \
                                           assoc_1.suAssocId, \
                                           &assoc_1.priPeerNAddr, \
                                           assoc_1.peerPort, \
                                           assoc_1.outStrms, \
                                           &assoc_1.peerNAddrLst, \
                                           &assoc_1.localNAddrLst, \
                                           SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                     ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                           assoc_1.spEndpId, \
                                           assoc_1.suAssocId, \
                                           &assoc_1.priPeerNAddr, \
                                           assoc_1.peerPort, \
                                           assoc_1.outStrms, \
                                           &assoc_1.peerNAddrLst, \
                                           &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                     sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected reply */
                  }
                  else if (sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst - 1) )
                  {
                     sbAccCb.curTst.evtType = ACC_EVT_TERM_IND; /* expected reply */
                  }
                  else
                  {
                     sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected reply */
                  }
                  break;
            } /* end curtstnum # 1 */
            sbAccCb.curTst.state++;
            break;
            /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if (status == WAIT)
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
               /* primitive received */
               reason = 0;
               switch(curtstnum)
               {
                  /* Start switch(curtstnum) #2 */
                  case 14:    /* Test O.201.14: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_1;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,
                                                 &assoc_2, &status   );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_2)
                              ret = sbSctChkCfm(&oper, &mgmt,
                                                ACC_EVT_ASSOC_CFM,
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              oper.hi.spId = SPID_1;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,
                                                    &assoc_2, &status   );
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_2, SCT_STATUS_COMM_UP,
                                            SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND,
                                             &status, &reason);
                           break;
                     }
                     break;
                  case 15:    /* Test O.201.15: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 2:
                           /* Check ABORT chunk and TermInd */
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_PARAM, 0, FALSE, SB_ID_ABORT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_TERM_IND)
                           {
			   /* sb008.103: Modified after adding new values for the status field  */
#ifdef SCT_ENHANCED_TERMIND
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_ABORT_SENT, SCT_CAUSE_INIT_FAILED)
#else
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED)
#endif
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                  case 16:   /* Test O.201.16: Expected Results */
                     if ( sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst - 1) )
                     {
                        /* check TermInd */
		      /* sb008.103: Modified after adding new values for the status field  */
#ifdef SCT_ENHANCED_TERMIND
                        SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_MAX_INIT_SENT, SCT_CAUSE_INIT_FAILED)
#else
                        SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED)
#endif
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                     }
                     else
                     {
                        /* Check INIT chunk */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                        ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                     }
                     break;
               }/* End switch(curtstnum) #2 */

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
            }/*end primitive received */

            if ( ((curtstnum == 14) && (sbAccCb.curTst.subTest == 2)) ||
                 ((curtstnum == 15) && (sbAccCb.curTst.subTest == 2)) )
            {
               if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                   (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
               {
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.bTickMask = 0;
               }
            }
            else
            {
               sbAccCb.curTst.subTest++;
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
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
   {
      doCleanup();
   }

   RETVALUE(ROK);
}  /* end sbSctAssocSndTst_4 */

 /* Association establishment for receiving endpoints */


/*
*       Fun:   sbO202_01
*
*       Desc:  Test case : O.202.01
*              Purpose   : Verify successful initialization of an association (handleInit = TRUE).
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_01
(
void
)
#else
PUBLIC  S16 sbO202_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO202_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocRcvTst(curtstnum,"O.202.01");
   RETVALUE(ROK);
} /* end sbO202_01 */

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbO202_08
*
*       Desc:  Test case : O.202.08
*              Purpose   : Verify successful initialization of an association (handleInit = TRUE) for IPV6 address. 
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_08
(
void
)
#else
PUBLIC  S16 sbO202_08(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO202_08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 4;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctAssocRcvTst(curtstnum,"O.202.08");
   RETVALUE(ROK);
} /* end sbO202_08 */
/*
*       Fun:   sbO202_02
*
*       Desc:  Test case : O.202.02
*              Purpose   : Verify successful initialization of an association (handleInit = FALSE).
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_02
(
void
)
#else
PUBLIC  S16 sbO202_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.100.02.curtstnum */

   TRC2(sbO202_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 5;
   sbSctAssocRcvTst(curtstnum,"O.202.02");
   RETVALUE(ROK);
} /* end sbO202_02 */

/*
*       Fun:   sbO202_03
*
*       Desc:  Test case : O.202.03
*              Purpose   :  Verify that if an optional parameter in the INIT
*                           chunk is not recognised, an INIT_ACK chunk will be
*                           generated with the correct unrecognised parameters
*                           (handleInit = TRUE).
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_03
(
void
)
#else
PUBLIC  S16 sbO202_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO202_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.03");
   RETVALUE(ROK);
} /* end sbO202_03 */

/*
*       Fun:   sbO202_04
*
*       Desc:  Test case : O.202.04
*              Purpose   : Verify that the receiving end SCTP successfully
*                          negotiates stream numbers based on it's configured
*                          values.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_04
(
void
)
#else
PUBLIC  S16 sbO202_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.104.curtstnum */

   TRC2(sbO202_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.04");
   RETVALUE(ROK);
} /* end sbO202_04 */

/*
*       Fun:   sbO202_05
*
*       Desc:  Test case : O.202.05
*              Purpose   : Verify that multiple associations can be opened
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_05
(
void
)
#else
PUBLIC  S16 sbO202_05(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_05)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 7;
   sbSctAssocRcvTst(curtstnum,"O.202.05");
   RETVALUE(ROK);
} /* end sbO202_05 */


/* SB_VER13 - following test cases were added for DNS testing */

/*
*       Fun:   sbO202_06
*
*       Desc:  Test case : O.202.06
*              Purpose   : Verify successful establishment of association when
*              hostname parameter is a part of INIT chunk.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_06
(
void
)
#else
PUBLIC  S16 sbO202_06(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_06)
   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocRcvTst(curtstnum,"O.202.06");
   RETVALUE(ROK);
} /* end sbO202_06 */

/*
*       Fun:   sbO202_07
*
*       Desc:  Test case : O.202.07
*              Purpose   : Verify unsuccessful establishment of association
*              when hostname ( in INIT Chunk ) could not be resolved.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_07
(
void
)
#else
PUBLIC  S16 sbO202_07(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_07)
   curtstnum = 7;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocRcvTst(curtstnum,"O.202.07");
   RETVALUE(ROK);
} /* end sbO202_07 */

/* RFC 4460: Acceptance Testing */
/*
*       Fun:   sbO202_09
*
*       Desc:  Test case : O.202.09
*              Purpose   : Verify that when Upper layer ABORTs the association, it
*                          provides the ABORT reason to the peer
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_09
(
void
)
#else
PUBLIC  S16 sbO202_09(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_09)
   curtstnum = 9;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.09");
   RETVALUE(ROK);
} /* end sbO202_09 */

/*
*       Fun:   sbO202_10
*
*       Desc:  Test case : O.202.10
*              Purpose   : Verify that when ABORT is sent in response to INIT, the
*                          verification tag should be equal to the initiate-tag of the
*                          received INIT and T-bit should be 0
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_10
(
void
)
#else
PUBLIC  S16 sbO202_10(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_10)
   curtstnum = 10;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.10");
   RETVALUE(ROK);
} /* end sbO202_10 */

/*
*       Fun:   sbO202_11
*
*       Desc:  Test case : O.202.11
*              Purpose   : Verify that if an endpoint receives INIT with IPV4 and IPV6
*                          parameter, and if the endpoint supports only IPV4 or IPV6 it
*                          should use all the addresses belonging to the supported address
*                          type
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_11
(
void
)
#else
PUBLIC  S16 sbO202_11(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_11)
   curtstnum = 11;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV4;
   sbSctAssocRcvTst(curtstnum,"O.202.11");
   RETVALUE(ROK);
} /* end sbO202_11 */

/*
*       Fun:   sbO202_12
*
*       Desc:  Test case : O.202.12
*              Purpose   : Verify that while preparing the state cookie,real
*                          verification tags are not used, instead two 32-bit
*                          random numbers are used and also verify that both
*                          listening port and local verification tag is added
*                          in the state cookie
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_12
(
void
)
#else
PUBLIC  S16 sbO202_12(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_12)
   curtstnum = 12;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.12");
   RETVALUE(ROK);
} /* end sbO202_12 */

/*
*       Fun:   sbO202_13
*
*       Desc:  Test case : O.202.13
*              Purpose   : Verify that on reception of INIT with a source address type
*                          different from which is listed in the "supported address type.,
*                          the responder considers the source address type as the
*                          supported address and sends back the INIT_ACK
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_13
(
void
)
#else
PUBLIC  S16 sbO202_13(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_13)
   curtstnum = 13;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.13");
   RETVALUE(ROK);
} /* end sbO202_13 */

/*
*       Fun:   sbO202_14
*
*       Desc:  Test case : O.202.14
*              Purpose   : Verify that on reception of INIT with a known parameter but
*                          not optional parameter of the INIT,the responder responds
*                          with INIT_ACK
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_14
(
void
)
#else
PUBLIC  S16 sbO202_14(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_14)
   curtstnum = 14;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.14");
   RETVALUE(ROK);
} /* end sbO202_14 */

/* RFC 4460 -- SB_ETSI_1 */
/*
*       Fun:   sbO202_15
*
*       Desc:  Test case : O.202.15
*              Purpose   : Verify on receipt of INIT with hostname address parameter, 
*                          SCTP responds with an ABORT with error message "Unresolvable address" 
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_15
(
void
)
#else
PUBLIC  S16 sbO202_15(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_15)
   curtstnum = 15;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.15");
   RETVALUE(ROK);
} /* end sbO202_15 */

/* sb028.103: Added new test case to process the data chunk bundled with Cookie.

*       Fun:   sbO202_16
*
*       Desc:  Test case : O.202.16
*              Purpose   : Verify on receipt of data chunk bundled 
*                          with Cookie chunk.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_16
(
 void
 )
#else
PUBLIC  S16 sbO202_16(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_16)
   curtstnum = 16;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocRcvTst(curtstnum,"O.202.16");
   RETVALUE(ROK);
} /* end sbO202_16 */

/* sb028.103: Added new test case to process the data chunk bundled with Cookie.
*       Fun:   sbO202_17
*
*       Desc:  Test case : O.202.17
*              Purpose   : Verify on receipt of data chunk bundled 
*                          with two Cookie chunk.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
                                                                                                                       
#ifdef ANSI
PUBLIC  S16 sbO202_17
(
void
)
#else
PUBLIC  S16 sbO202_17(void)
#endif
{
   U8          curtstnum;
                                                                                                                       
   TRC2(sbO202_17)
   curtstnum = 17;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocRcvTst(curtstnum,"O.202.17");
   RETVALUE(ROK);
} /* end sbO202_17 */
                                                                                                                       
/* sb028.103: Added new test case to process the data chunk bundled with Cookie.
*       Fun:   sbO202_18
*
*       Desc:  Test case : O.202.18
*              Purpose   : Verify SCTP will generate the ABORT chunk when 
*                          data chunk will be sent seperately instead of
*                          bundling it with cookie.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbO202_18
(
void
)
#else
PUBLIC  S16 sbO202_18(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */
                                                                                                                       
   TRC2(sbO202_18)
   curtstnum = 18;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocRcvTst(curtstnum,"O.202.18");
   RETVALUE(ROK);
} /* end sbO202_18 */

/* sb029.103: Added new test case O.202.19.  */
/*
 *       Fun:   sbO202_19
 *
 *       Desc:  Test case : O.202.19
 *              Purpose   : If SCTP user don't wants the association (sends assocRsp with SCT_NOK)  
 *                          'user initiated abort' is sent by SCTP. (handleInit = FALSE).
 *
 *       Ret:   ROK
 *
 *       Group: Association
 *
 *       Notes:
 *
 *       File:  sb_act3.c
 *
 */

#ifdef ANSI
PUBLIC  S16 sbO202_19
(
 void
)
#else
PUBLIC  S16 sbO202_19(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO202_19)
   curtstnum = 19;
   sbAccCb.curTst.numSubTst = 7;
   sbSctAssocRcvTst(curtstnum,"O.202.19");
   RETVALUE(ROK);
} /* end sbO202_19 */

/* sb030.103: Added new test case to process the ABORT chunk bundled with Cookie.

*       Fun:   sbO202_20
*
*       Desc:  Test case : O.202.20
*              Purpose   : Verify on receipt of cookie chunk bundled 
*                          with ABORT chunk. Here COOKIE-ECHO chunk is 
*                          the first chunk. 
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO202_20
(
 void
)
#else
PUBLIC  S16 sbO202_20(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_20)
   curtstnum = 20;
   sbAccCb.curTst.numSubTst = 5;
   sbSctAssocRcvTst(curtstnum,"O.202.20");
   RETVALUE(ROK);
} /* end sbO202_20 */

/* sb035.103: Added new testcase O.202.21 */
/*
*        Fun:   sbO202_21
* 
*        Desc:  Test case : O.202.21
*        Purpose : Verify that SCTP sends ABORT in response INIT chunk
*                having Host Name parmater is greater than 256 bytes.  
* 
*        Ret:   ROK
* 
*        Group: Association
* 
*        Notes:
* 
*        File:  sb_act3.c
* 
*/

#ifdef ANSI
PUBLIC  S16 sbO202_21
(
 void
 )
#else
PUBLIC  S16 sbO202_21(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO202_21)

   curtstnum = 21;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocRcvTst(curtstnum,"O.202.21");

   RETVALUE(ROK);
} /* end sbO202_21 */

/* End of SB_VER13 */

/*
*       Fun:   sbSctAssocRcvTst
*
*       Desc:  Initialization and Termination of Association for the sending endpoint.
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctAssocRcvTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocRcvTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   PRIVATE SbOperQElm    oper;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE SbAccChunkBld buildPar;            /* Parameters used for checking chunks */
   /* Buffer        *vsInfo; */ /* RFC 4460 -- RTR Fix */
   PRIVATE SbAccAssoc    assoc_1;
   PRIVATE SbAccAssoc    assoc_2;
   CmIpHdrParm   hdrParm;
   Buffer        *mBuf;
   SbAccMsgQElm  *msg;
   U8            ID;

   /* RFC 4460: Acceptance test */
   SbTcb         *tcb;

   TRC2(sbSctAssocRcvTst)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            if ( (curtstnum == 2) || (curtstnum == 19) )
            {
               SB_TSAPCFG(SAP_2);
            }
            else
            {
               SB_TSAPCFG(SAP_1)
            }
            if ( (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE) ||
                 ( (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT1) == TRUE) &&
                   ((curtstnum == 2) || (curtstnum == 19)) ) )
            {
               if ( (curtstnum == 2) || (curtstnum == 19) )
               {
                  SB_BIND_HITSAP(SUID_1, SPID_1, BIT1);
               }
               else
               {
                  SB_BIND_HITSAP(SUID_0, SPID_0, BIT0);
               }
               if ( (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE) ||
                    ( (isBitSet(sbAccCb.curTst.bTSapMask, BIT1) == TRUE) &&
                      ((curtstnum == 2) || (curtstnum == 19))) )
               {
                  SB_DISABLE_TRACE() /* disable trace */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     switch(curtstnum)/* Pretests continues */
                     {
                        case 1: /* pretests: O.202.01 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        case 2: /* pretests: O.202.02 */
                           SB_SCTSAPCFG(SAP_2)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT1) == TRUE)
                           {
                              setupAssoc(&assoc_2, ASSOC_2);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT1 )
                           }
                           break;
                        case 3: /* pretests: O.202.03 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        case 4: /* pretests: O.202.04 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        case 5: /* pretests: O.202.05 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                              {
                                 setupAssoc(&assoc_2, ASSOC_3);
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT3 )
                                 if ( (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT3) == TRUE) &&
                                      (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE) )
                                 {
                                    sbAccCb.curTst.bBusySubtest = TRUE;       /* Now do a test */
                                    sbAccCb.curTst.bBusyPreTestConf = FALSE;  /* Done with pre-test setup */
                                 }
                              }
                           }
                           break;
                        
                         case 6: /* pretests: O.202.06 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;

                        case 7: /* pretests: O.202.07 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        /* sb032.102 :  IPV6 Support Added */
                        case 8: /* pretests: O.202.08 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        case 9: /* pretests: O.202.09 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                              {
                                 SB_EST_ASSOC(assoc_1, BIT0)
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                              }
                           }
                           break;

                        case 10: /* pretests: O.202.10 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;

                        case 11: /* pretests: O.202.11 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;

                        case 12: /* pretests: O.202.12 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;

                        case 13: /* pretests: O.202.13 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;

                        case 14: /* pretests: O.202.14 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;

                        case 15: /* pretests: O.202.15 */
                           SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        /* sb028.103 : Added new test cases to process the 
                                       data chunk bundled with Cookie */
                        case 16:  /* pretests: O.202.16 */
                           SB_SCTSAPCFG(SAP_1)
                              if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                              {
                                 setupAssoc(&assoc_1, ASSOC_1);
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                              }
                           break;
                        case 17:  /* pretests: O.202.17 */
                           SB_SCTSAPCFG(SAP_1)
                              if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                              {
                                 setupAssoc(&assoc_1, ASSOC_1);
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                              }
                           break;
                        case 18: /* pretests: O.202.18 */
                           SB_SCTSAPCFG(SAP_1)
                              if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                              {
                                 setupAssoc(&assoc_1, ASSOC_1);
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                              }
                           break;
                           /* sb029.103: SAP_2 configuration to make handleInit as FALSE.  */
                        case 19: /* pretests: O.202.19 */
                           SB_SCTSAPCFG(SAP_2)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT1) == TRUE)
                           {
                              setupAssoc(&assoc_2, ASSOC_2);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT1 )
                           }
                           break;
                        case 20:  /* sb030.103: pretest: O.202.20 */
                           SB_SCTSAPCFG(SAP_1)
                              if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                              {
                                 setupAssoc(&assoc_1, ASSOC_1);
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                              }
                        break;

                        case 21: /* sb035.103: Pretests for O.202.21 */
                        SB_SCTSAPCFG(SAP_1)
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                        break;

                        default:
                           break;
                     } /*end curtstnum switch */
                  } /* end bTraceMask if */
               } /* end bTSapMask */
            }/*end TSapCfgMask if*/
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:

            switch(curtstnum)
            {  /* Start switch(curtstnum) #1 */

               case 1:    /* Test O.202.01: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {

                     case 1:   /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 5;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;

                     case 2:    /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                        break;
                     case 3:  /* AssocRsp with assocIndParams received from SCTP */
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3

                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        break;
                     default:
                        break;
                  }
                  break;

               case 2:     /* Test O.202.02: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:   /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 4;
                        buildPar.inStrms = 5;
                        buildInitChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                         assoc_2.suConId = SUCONID_0;
#endif
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                               assoc_2.suConId, \
                                               &assoc_2.peerTAddr, \
                                               &assoc_2.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_ASSOC_IND; /* expected response */
                        break;
                     case 2:
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;
                     case 3:    /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                               assoc_2.suConId, \
                                               &assoc_2.peerTAddr, \
                                               &assoc_2.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 4:
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_2.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_ASSOC_IND;
                        break;
                     default:
                        break;
                  }
                  break;

               case 3:      /* Test O.202.03: Execution */
                  buildPar.misChunk = TRUE;
                  SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                  buildPar.outStrms = 5;
                  buildPar.inStrms = 4;
                  buildInitChunk(mBuf,&buildPar, &assoc_1);
                  SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                  (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                         assoc_1.suConId, \
                                         &assoc_1.peerTAddr, \
                                         &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                         &assoc_1.localIf,
#endif
                                         mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                  buildPar.misChunk = FALSE;/* RFC 4460 -- RTR */
                  break;

               case 4:      /* Test O.202.04: Execution */
                  switch(sbAccCb.curTst.subTest)
                  {
                     case 1:
                        /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 4;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;
                  }
                  break;
               case 5:      /* Test O.202.05: Execution */
                  switch(sbAccCb.curTst.subTest)
                  {
                     case 1:
                        /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 4;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;
                     case 2:
                        /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                        break;
                     case 3:  /* AssocRsp with assocIndParams received from SCTP */
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3

                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        break;
                     case 4:
                        /* RFC 4460 upgrade -- send the HBEAT_ACK */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildHBeatAckChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                               &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                               &hdrParm, mBuf);

                        /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 4;
                        buildPar.inStrms = 3;
                        buildInitChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_2.suConId, \
                                               &assoc_2.peerTAddr, \
                                               &assoc_2.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;
                     case 5:
                        /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_2.suConId, \
                                               &assoc_2.peerTAddr, \
                                               &assoc_2.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                        break;
                     case 6:  /* AssocRsp with assocIndParams received from SCTP */
                        /*-- RFC 4460: MLK fix --*/
                        /*-- sbGetPacket(&vsInfo, SBUT_TXPKTFIXEDSIZE, 4);--*/
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_2.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer *)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer *)NULLP);
#endif /* SCT3 */
                        break;
                     default:
                        break;
                  }
                  break;

                case 6:    /* Test O.202.06: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {

                     case 1:   /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 5;
                        buildPar.hstNamePrsnt = TRUE;
                        if(assoc_1.spId == SPID_1)
                         cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trillium1.com", 
                               cmStrlen((CONSTANT U8 *)"www.trillium1.com"));
                         else
                         cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trillium2.com",
                                cmStrlen((CONSTANT U8 *)"www.trillium2.com"));
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;

                     case 2:    /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                        break;
                     case 3:  /* AssocRsp with assocIndParams received from SCTP */
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        break;
                     default:
                        break;
                  }
                  break;

                case 7:    /* Test O.202.07: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {

                     case 1:   /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 5;
                        buildPar.hstNamePrsnt = TRUE;
                        cmMemcpy((U8 *)buildPar.hostName, (CONSTANT U8*)"www.trillium3.com", 
                        cmStrlen((CONSTANT U8 *)"www.trillium3.com"));
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        /* RFC 4460: Acceptance test */
                        buildPar.hstNamePrsnt = FALSE;
                        buildPar.misChunk = FALSE;
                        break;

                     case 2:    /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                        break;

                     default:
                        break;
                  }
                  break;
               /* sb032.102 :  IPV6 Support Added */
               case 8:    /* Test O.202.08: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {

                     case 1:   /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 5;
                        buildPar.hstNamePrsnt = FALSE;
                        buildPar.misChunk = FALSE;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;

                     case 2:    /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                              &hdrParm , 
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                        break;
                     case 3:  /* AssocRsp with assocIndParams received from SCTP */
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        break;
                     default:
                        break;
                  }
                  break;
               case 9:      /* Test O.202.09: Execution */
                  (void)  ItLiSctTermReq(&sbAccCb.itPst,
                                        assoc_1.spId,
                                        assoc_1.spAssocId,
                                        SCT_ASSOCID_SP, TRUE);
                   sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                   break;

               case 10:      /* Test O.202.10: Execution */
                   SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                   buildPar.outStrms = 5;
                   buildPar.inStrms = 5;
                   buildPar.usrITag = TRUE;
                   buildPar.iTag = 0;
                   buildInitChunk(mBuf,&buildPar, &assoc_1);
                   SB_SETUP_IPHDR_PAR(NOFRAGM)
                   /* sb032.102 :  IPV6 Support Added */
                   (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                            assoc_1.suConId, \
                                            &assoc_1.peerTAddr, \
                                            &assoc_1.localTAddr, \
                                            &hdrParm ,
#ifdef LOCAL_INTF
                                            &assoc_1.localIf,
#endif
                                            mBuf);
                     sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                     buildPar.usrITag = FALSE;
                     break;

               case 11:      /* Test O.202.11: Execution */
                  SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                  buildPar.outStrms = 5;
                  buildPar.inStrms = 4;
                  buildPar.multAddrTypes = TRUE;
                  buildPar.misChunk = FALSE;
                  buildInitChunk(mBuf,&buildPar, &assoc_1);
                  SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                  (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                         assoc_1.suConId, \
                                         &assoc_1.peerTAddr, \
                                         &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                         &assoc_1.localIf,
#endif
                                         mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                  buildPar.multAddrTypes = FALSE;
                  break;

               case 12:      /* Test O.202.12: Execution */
                  SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                  buildPar.outStrms = 5;
                  buildPar.inStrms = 4;
                  buildInitChunk(mBuf,&buildPar, &assoc_1);
                  SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                  (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                         assoc_1.suConId, \
                                         &assoc_1.peerTAddr, \
                                         &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                         &assoc_1.localIf,
#endif
                                         mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                  break;

               case 13:      /* Test O.202.13: Execution */
                  SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                  buildPar.outStrms = 5;
                  buildPar.inStrms = 4;
                  buildPar.suppAddrTypes = 2;
                  buildInitChunk(mBuf,&buildPar, &assoc_1);
                  SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                  (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                         assoc_1.suConId, \
                                         &assoc_1.peerTAddr, \
                                         &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                         &assoc_1.localIf,
#endif
                                         mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                  buildPar.suppAddrTypes = 0;
                  break;

               case 14:      /* Test O.202.14: Execution */
                  SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                  buildPar.outStrms = 5;
                  buildPar.inStrms = 4;
                  buildPar.pkUnrecogPar = TRUE;
                  buildInitChunk(mBuf,&buildPar, &assoc_1);
                  SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                  (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                         assoc_1.suConId, \
                                         &assoc_1.peerTAddr, \
                                         &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                         &assoc_1.localIf,
#endif
                                         mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                  buildPar.pkUnrecogPar = FALSE;
                  break;

               case 15: /* Test O.202.15: Execution */
                     SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                     buildPar.outStrms = 5;
                     buildPar.inStrms = 4;
                     buildPar.hstNamePrsnt = TRUE;
                     cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trillium1.com", 
                              cmStrlen((CONSTANT U8 *)"www.trillium1.com"));
                     buildInitChunk(mBuf,&buildPar, &assoc_1);
                     SB_SETUP_IPHDR_PAR(NOFRAGM)
                     /* sb032.102 :  IPV6 Support Added */
                     (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                            assoc_1.suConId,
                                            &assoc_1.peerTAddr,
                                            &assoc_1.localTAddr,
                                            &hdrParm ,
#ifdef LOCAL_INTF
                                            &assoc_1.localIf,
#endif
                                            mBuf);
                     sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                     break;

               /* sb028.103 : Added new test case to process the data 
                              chunk bundled with Cookie */

               case 16:    /* Test O.202.16: Execution */
                     switch( sbAccCb.curTst.subTest)
                     {

                        case 1:   /* Send the INIT chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.outStrms = 5;
                           buildPar.inStrms = 5;
                           buildInitChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                     assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, \
                                                     &assoc_1.localTAddr, \
                                                     &hdrParm ,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                           break;
                        case 2:    /* Send the COOKIE chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.noBundleFlg =TRUE;
                           buildPar.streamId = 1;
                           buildPar.tsn = ACC_INIT_TSN;
                           buildPar.seqNr = 0;
                           buildPar.chunkFlg = 3;     /* set up for sequenced delivery --*/
                           buildPar.noData = TRUE;  
                           buildCookieWitDatChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                     assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, \
                                                     &assoc_1.localTAddr, \
                                                     &hdrParm ,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           buildPar.noBundleFlg = FALSE;
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                           break;
                        case 3:  /* AssocRsp with assocIndParams received from SCTP */
                           oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
                           /* sb060.102: TOS changes */
#ifdef SCT3

                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                                  assoc_1.spEndpId, \
                                                  &oper.it.assocParams, \
                                                  SB_ACC_SCT_TOS, SCT_OK, \
                                                  (Buffer*)NULLP);
#else
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                                  assoc_1.spEndpId, \
                                                  &oper.it.assocParams, \
                                                  SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                           break;
                     }
                     break;
              /* sb028.103 : Added new test case to process the data
                             chunk bundled with Cookie */

               case 17:    /* Test O.202.17: Execution */
                     switch( sbAccCb.curTst.subTest)
                     {

                        case 1:   /* Send the INIT chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.outStrms = 5;
                           buildPar.inStrms = 5;
                           buildInitChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                     assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, \
                                                     &assoc_1.localTAddr, \
                                                     &hdrParm ,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                           break;
                        case 2:    /* Send the COOKIE chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.noBundleFlg = FALSE;
                           buildPar.streamId = 1;
                           buildPar.tsn = ACC_INIT_TSN;
                           buildPar.seqNr = 0;
                           buildPar.chunkFlg = 3;     /* set up for sequenced delivery --*/
                           buildPar.noData = TRUE;
                           buildCookieWitDatChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                     assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, \
                                                     &assoc_1.localTAddr, \
                                                     &hdrParm ,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                           break;
                        case 3:  /* AssocRsp with assocIndParams received from SCTP */
                           oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
                           /* sb060.102: TOS changes */
#ifdef SCT3

                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                                  assoc_1.spEndpId, \
                                                  &oper.it.assocParams, \
                                                  SB_ACC_SCT_TOS, SCT_OK, \
                                                  (Buffer*)NULLP);
#else
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                                  assoc_1.spEndpId, \
                                                  &oper.it.assocParams, \
                                                  SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */

                           break;
                     }
                     break;

             /* sb028.103 : Added new test case to process the data chunk
                            bundled with Cookie */
               case 18:    /* Test O.202.18: Execution */
                     switch( sbAccCb.curTst.subTest)
                     {

                        case 1:   /* Send the INIT chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.outStrms = 5;
                           buildPar.inStrms = 5;
                           buildInitChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                     assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, \
                                                     &assoc_1.localTAddr, \
                                                     &hdrParm ,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                           break;

                        case 2:    /* Send the COOKIE chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildCookieChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                     assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, \
                                                     &assoc_1.localTAddr, \
                                                     &hdrParm ,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                           break;
                        case 3: /* Send the DATA chunk */ 
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.streamId = 1;
                           buildPar.tsn = ACC_INIT_TSN;
                           buildPar.seqNr = 0;
                           buildPar.chunkFlg = 3;     /* set up for sequenced delivery --*/
                           buildPar.noData = TRUE;     /* Send no data --*/
                           buildDataChunk(mBuf,&buildPar,&assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added --*/
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           buildPar.noData = FALSE;     /* reset the flag --*/
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected --*/
                           break;

                     }
                     break;
                     /* sb029.103: Test case O.202.19 execution. */
               case 19:    /* Test O.202.19: Execution */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:   /* Send the INIT chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.outStrms = 4;
                           buildPar.inStrms = 5;
                           buildInitChunk(mBuf,&buildPar, &assoc_2);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                              assoc_2.suConId = SUCONID_0;
#endif
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                 assoc_2.suConId, \
                                 &assoc_2.peerTAddr, \
                                 &assoc_2.localTAddr, \
                                 &hdrParm ,
#ifdef LOCAL_INTF
                                 &assoc_2.localIf,
#endif
                                 mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_ASSOC_IND; /* expected response */
                           break;
                        case 2: /* Send AssocRsp with SCT_NOK. */
                           /* sb060.102: TOS changes */
#ifdef SCT3
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                 assoc_2.spEndpId, \
                                 &oper.it.assocParams, \
                                 SB_ACC_SCT_TOS, SCT_NOK, \
                                 (Buffer*)NULLP);
#else
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                 assoc_2.spEndpId, \
                                 &oper.it.assocParams, \
                                 SCT_NOK, (Buffer*)NULLP);
#endif /* SCT3 */
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                           break;
                        case 3:   /* Send the INIT chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.outStrms = 4;
                           buildPar.inStrms = 5;
                           buildInitChunk(mBuf,&buildPar, &assoc_2);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                              assoc_2.suConId = SUCONID_0;
#endif
                           /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                 assoc_2.suConId, \
                                 &assoc_2.peerTAddr, \
                                 &assoc_2.localTAddr, \
                                 &hdrParm ,
#ifdef LOCAL_INTF
                                 &assoc_2.localIf,
#endif
                                 mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_ASSOC_IND; /* expected response */
                           break;
                        case 4:
                           /* sb060.102: TOS changes */
#ifdef SCT3
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                 assoc_2.spEndpId, \
                                 &oper.it.assocParams, \
                                 SB_ACC_SCT_TOS, SCT_OK, \
                                 (Buffer*)NULLP);
#else
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                 assoc_2.spEndpId, \
                                 &oper.it.assocParams, \
                                 SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                           break;
                        case 5:    /* Send the COOKIE chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildCookieChunk(mBuf,&buildPar, &assoc_2);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                    assoc_2.suConId, \
                                    &assoc_2.peerTAddr, \
                                    &assoc_2.localTAddr, \
                                    &hdrParm ,
#ifdef LOCAL_INTF
                                    &assoc_2.localIf,
#endif
                                    mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                           break;
                        case 6:  /* Send AssocRsp with SCT_NOK. */
                           oper.it.assocParams.t.cookieParams.suAssocId = assoc_2.suAssocId;
                           /* sb060.102: TOS changes */
#ifdef SCT3
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                 assoc_2.spEndpId, \
                                 &oper.it.assocParams, \
                                 SB_ACC_SCT_TOS, SCT_NOK, \
                                 (Buffer*)NULLP);
#else
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                 assoc_2.spEndpId, \
                                 &oper.it.assocParams, \
                                 SCT_NOK, (Buffer*)NULLP);
#endif /* SCT3 */
                           sbAccCb.curTst.evtType = ACC_EVT_ASSOC_IND;
                           break;
                        default:
                           break;
                     } /*  switch of O.202.19 */
                     break;

               /* sb030.103 : Added new test case to process the ABORT 
                              chunk bundled with Cookie */

               case 20:    /* Test O.202.20: Execution */
                     switch( sbAccCb.curTst.subTest)
                     {

                        case 1:   /* Send the INIT chunk */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.outStrms = 5;
                           buildPar.inStrms = 5;
                           buildInitChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                     assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, \
                                                     &assoc_1.localTAddr, \
                                                     &hdrParm ,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                           break;
                        case 2:    /* Send the COOKIE chunk, bundled with ABORT. */
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildCookieWithAbortChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                                     assoc_1.suConId, \
                                                     &assoc_1.peerTAddr, \
                                                     &assoc_1.localTAddr, \
                                                     &hdrParm ,
#ifdef LOCAL_INTF
                                                     &assoc_1.localIf,
#endif
                                                     mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /* expected response */
                           break;
                        case 3:
                        break;
                        case 4:  /* AssocRsp with assocIndParams received from SCTP */
                           oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
                           /* sb060.102: TOS changes */
#ifdef SCT3

                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                                  assoc_1.spEndpId, \
                                                  &oper.it.assocParams, \
                                                  SB_ACC_SCT_TOS, SCT_OK, \
                                                  (Buffer*)NULLP);
#else
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                                  assoc_1.spEndpId, \
                                                  &oper.it.assocParams, \
                                                  SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                           break;
                     }/*  switch of O.202.20 */
                     break;

               case 21:      /* sb035.103: Test O.202.21: Execution */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:   /* Send the INIT chunk */

                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildPar.outStrms = 5;
                           buildPar.inStrms = 5;
                           buildPar.hstNamePrsnt = TRUE;
                           cmMemcpy(buildPar.hostName,(CONSTANT U8 *)"www.trilliumumtrilliumumtrilliumumtrilliumumtrilliumumtrilliumumtrilliumumtrilliumumtrilliumumtrilliumum.comtrilliumumtrilliumumtrilliumumtrilliumumtrilliumum.comtrilliumumtrilliumumtrilliumumtrilliumumtrilliumum.comtrilliumumtrilliumumtrilliumumtrilliumumtrilliumum.comtrilliumumtrilliumumtrilliumumtrilliumumtrilliumum.com.com", 260);
                           buildInitChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                              /* sb032.102 :  IPV6 Support Added */
                              (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                    assoc_1.suConId, \
                                    &assoc_1.peerTAddr, \
                                    &assoc_1.localTAddr, \
                                    &hdrParm ,
#ifdef LOCAL_INTF
                                    &assoc_1.localIf,
#endif
                                    mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                           break;
                     }/*  switch of O.202.20 */
                     break;
            }/*end curtstnum #1 */

            sbAccCb.curTst.state++;
            break;
            /* Dequeue response and test */

         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
            {   /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if (status == TIMEOUT)
            {
               /* sb030.103: Added new test case O.202.20  */
               if ((curtstnum == 20 ) && (sbAccCb.curTst.subTest == 4))
               {
                  sbAccCb.curTst.subTestsPass++;
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  break;
               }
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            {
               /*primitive received */
               reason = 0;
               switch(curtstnum)
               {
                  /* Start switch(curtstnum) #2 */
                  case 1:    /* Test O.202.01: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                           /*RFC 4460: MLK Fix*/
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_COOKIEACK )
                              {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
                              else if (ID == SB_ID_HBEAT)
                              {
                                 /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                       &assoc_1, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* Communication Up */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                               SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
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
                           break;
                        default:
                           break;
                     }
                     break;

                  case 2:    /* Test O.202.02: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           SB_SETUP_ASSOC_IND(assoc_2, ACC_INIT)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 2:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_1;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status   );
                           break;
                        case 3:
                           /* cech assocInd */
                           SB_SETUP_ASSOC_IND(assoc_2, ACC_COOKIE)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 4:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                           /*RFC 4460: MLK Fix*/
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_COOKIEACK )
                              {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_1;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
                              else if (ID == SB_ID_HBEAT)
                              {
                                 /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                       &assoc_2, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* Communication Up */
                              SB_SETUP_STA_IND(assoc_2, SCT_STATUS_COMM_UP, \
                                               SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
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
                           break;
                        default:
                           break;
                     }
                     break;

                  case 3:      /* Test O.202.03: Expected Results */
                     /* Check INIT ACK chunk */
                     oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                     if ( (ret == ROK) && (buildPar.unrecogParFound == TRUE) )
                     {
                        SPrint("Unrecognised parameter found in INIT ACK\n");
                        ret = ROK;
                     }
                     else
                     {
                        SPrint("Unrecognised parameter not found in INIT ACK\n");
                        ret = RFAILED;
                     }
                     break;

                  case 4:      /* Test O.202.04: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           {
                              U16 initInStrms;
                              U16 initOutStrms;
                              initInStrms = buildPar.inStrms;
                              initOutStrms = buildPar.outStrms;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                              if ( (buildPar.inStrms == initOutStrms) &&
                                   (buildPar.outStrms == initInStrms) )
                              {
                                 ret = ROK;
                              }
                              else
                              {
                                 ret = RFAILED;
                              }
                           }
                           break;
                        default:
                           break;
                     }
                     break;

                  case 5:    /* Test O.202.05: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_COOKIEACK )
                              {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
                              else if (ID == SB_ID_HBEAT)
                              {
                                 /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                       &assoc_1, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* Communication Up */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                               SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                        case 4:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status   );
                           break;
                        case 5:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_2, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 6:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_COOKIEACK )
                              {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
                              else if (ID == SB_ID_HBEAT)
                              {
                                 /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                       &assoc_2, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* Communication Up */
                              SB_SETUP_STA_IND(assoc_2, SCT_STATUS_COMM_UP, \
                                               SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                        default:
                           break;
                     }
                     break;

                   case 6:    /* Test O.202.06: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                           /*RFC 4460: MLK Fix*/
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_COOKIEACK )
                              {
                             printf("\nreceived COOKIE_ACK\n\n");
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
                              else if (ID == SB_ID_HBEAT)
                              {
                                 /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                       &assoc_1, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               }
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                             printf("\nreceived SCT_STATUS_COMM_UP\n\n");
                              /* Communication Up */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                               SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
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
                           break;
                        default:
                           break;
                     }
                     break;

                   case 7:    /* Test O.202.07: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_UNRSLV_ADDR, 0, FALSE, SB_ID_ABORT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_TERM_IND)
                           {
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           } 
                            else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                             mgmt.s.usta.event = LCM_EVENT_LYR_SPECIFIC;
                             mgmt.s.usta.cause = LSB_CAUSE_UNRSLVD_ADDR;
                             ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_STA_IND);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;

                        default:
                           break;
                     }
                     break;
                  /* sb032.102 :  IPV6 Support Added */
                  case 8:    /* Test O.202.08: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* Communication Up */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                               SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
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
                           break;
                        default:
                           break;
                     }
                     break;
                  case 9:      /* Test O.202.09: Expected Results */
                     oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_USR_INITIATED_ABORT, 0, FALSE, SB_ID_ABORT)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                     if ( status == INC_REASON )
                     {
                        SPrint("Incorrect Abort Reason received\n");
                        ret = RFAILED;
                     }
                     break;

                  case 10:      /* Test O.202.10: Expected Results */
                     /* Check INIT ACK chunk */
                     oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_INVAL_MAND_PAR, 0, FALSE, SB_ID_ABORT)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                     if ( (ret == ROK) && (buildPar.vTag == 0)&& (buildPar.chunkFlg == 0))
                     {
                        SPrint("Abort received with V-Tag=0 and T-bit=0\n");
                        ret = ROK;
                     }
                     else
                     {
                        SPrint("Incorrect values of V-Tag and T-bit in the received Abort\n");
                        ret = RFAILED;
                     }
                     break;

                  case 11:      /* Test O.202.11: Expected Results */
                     /* Check INIT ACK chunk */
                     oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                     /* sb001.103 : IPv6 address should not be there */
                     if ( (ret == ROK) && (buildPar.ipv6AddrFound == FALSE))
                     {
                        SPrint("Only IPv4 Address found in INIT ACK\n");
                        ret = ROK;
                     }
                     else
                     {
                        SPrint("Only IPv4 address not found in INIT ACK\n");
                        ret = RFAILED;
                     }
                     break;

                  case 12:      /* Test O.202.12: Expected Results */
                     /* Check INIT ACK chunk */
                     oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                     tcb = (SbTcb *)(assoc_1.cookie);
                     if ( (ret == ROK) && (buildPar.peerPort == tcb->tcbInitAck.localPort) && (buildPar.vTag == tcb->tcbInitAck.iTag) )
                     {
                        SPrint("Both listening port and verification tag found in state cookie\n");
                        ret = ROK;
                     }
                     else
                     {
                        SPrint("Error in getting listening port and verification tag in state cookie\n");
                        ret = RFAILED;
                     }
                     break;

                  case 13:      /* Test O.202.13: Expected Results */
                     /* Check INIT ACK chunk */
                     oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                     /* sb001.103: If only one address then it won't be sent in the address list */
                     if ( (ret == ROK) )
                     {
                        SPrint("IPv4 Address found in INIT ACK\n");
                        ret = ROK;
                     }
                     else
                     {
                        SPrint("IPv4 address not found in INIT ACK\n");
                        ret = RFAILED;
                     }
                     break;

                  case 14:      /* Test O.202.14: Expected Results */
                     /* Check INIT ACK chunk */
                     oper.hi.spId = SPID_0;
                     SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                     ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                     break;

                  case 15: /* O.202.15: Expected results */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_UNRSLV_ADDR, 0, FALSE, SB_ID_ABORT)
                        ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                  break;
                  /* sb028.103 : Added new test case to process the data
                                 chunk bundled with Cookie */
                  case 16:    /* Test O.202.16: Expected Results */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        /* Check INIT_ACK chunk */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                        break;
                     case 2:
                        /* we expect an AssocInd */
                        SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                        break;
                     case 3:
                        sbAccPeekMsg(&msg);
                        if (msg->evntType == ACC_EVT_UDAT_REQ)
                        {
                           /*RFC 4460: MLK Fix*/
                           SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                           if ( ID == SB_ID_COOKIEACK )
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              buildPar.chunkId = SB_ID_COOKIEACK;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              /* setBit(&sbAccCb.curTst.bTickMask, BIT0);*/
                           }
                           else if (ID == SB_ID_HBEAT)
                           {
                              /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                              buildPar.chunkId = SB_ID_HBEAT;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                    &assoc_1, &status );
                           }
                           else if (ID == SB_ID_SACK)
                           {
                              buildPar.chunkId = SB_ID_SACK;
                              oper.hi.spId = SPID_0;
                              buildPar.cumTsn = 25;
                              ret=sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                              setBit(&sbAccCb.curTst.bTickMask, BIT3);
                           }
                        }
                        else if (msg->evntType == ACC_EVT_STA_IND)
                        {
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                 SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                    ACC_EVT_STA_IND, \
                                    &status, &reason);
                        }
                        else if (msg->evntType == ACC_EVT_DAT_IND)
                        {
                           SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);

                        }
                        else
                        {
                           status = INC_EVNTTYPE;
                           setBit(&sbAccCb.curTst.bTickMask, BIT3);
                           ret = RFAILED;
                        }
                        break;
                  }
                  break;
                  /* sb028.103 : Added new test case to process the data 
                                 chunk bundled with Cookie */
                  case 17:    /* Test O.202.17: Expected Results */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        /* Check INIT_ACK chunk */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                        break;
                     case 2:
                        /* we expect an AssocInd */
                        SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                        break;
                     case 3:
                        sbAccPeekMsg(&msg);
                        if (msg->evntType == ACC_EVT_UDAT_REQ)
                        {
                           /*RFC 4460: MLK Fix*/
                           SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                           if ( ID == SB_ID_COOKIEACK )
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              buildPar.chunkId = SB_ID_COOKIEACK;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                           }
                           else if (ID == SB_ID_HBEAT)
                           {
                              /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                              buildPar.chunkId = SB_ID_HBEAT;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                    &assoc_1, &status );
                           }
                           else if (ID == SB_ID_SACK)
                           {
                              buildPar.chunkId = SB_ID_SACK;
                              oper.hi.spId = SPID_0;
                              buildPar.cumTsn = 26;
                              ret=sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                              setBit(&sbAccCb.curTst.bTickMask, BIT3);
                           }
                        }
                        else if (msg->evntType == ACC_EVT_STA_IND)
                        {
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                 SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                    ACC_EVT_STA_IND, \
                                    &status, &reason);
                        }
                        else if (msg->evntType == ACC_EVT_DAT_IND)
                        {
                           SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                        }
                        else
                        {
                           status = INC_EVNTTYPE;
                           setBit(&sbAccCb.curTst.bTickMask, BIT3);
                           ret = RFAILED;
                        }
                  }
                  break;
                  /* sb028.103 : Added new test case to process the data
                                 chunk bundled with Cookie */
                  case 18:    /* Test O.202.18: Expected Results */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        /* Check INIT_ACK chunk */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                        break;
                     case 2:
                        /* we expect an AssocInd */
                        SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                        break;
                     case 3:
                        sbAccPeekMsg(&msg);
                        if (msg->evntType == ACC_EVT_UDAT_REQ)
                        {
                           /*RFC 4460: MLK Fix*/
                           SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                           if ( ID == SB_ID_ABORT  )
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_ABORT)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                           }
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

                  /* sb029.103: Test case O.202.19 expected results.  */
                  case 19:  
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SB_SETUP_ASSOC_IND(assoc_2, ACC_INIT)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                        break;
                     case 2: /* expecting user initiated ABORT.*/
                        oper.hi.spId = SPID_1; 
                        SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_USR_INITIATED_ABORT, 0, FALSE, SB_ID_ABORT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status  );
                        break;
                     case 3:
                        SB_SETUP_ASSOC_IND(assoc_2, ACC_INIT)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                        break;
                     case 4:
                        /* Check INIT_ACK chunk */
                        oper.hi.spId = SPID_1;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status   );
                        break;
                     case 5:
                        /*  assocInd */
                        SB_SETUP_ASSOC_IND(assoc_2, ACC_COOKIE)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                        break;
                     case 6: /* expecting user initiated ABORT.*/
                        oper.hi.spId = SPID_1;
                        SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_USR_INITIATED_ABORT, 0, FALSE, SB_ID_ABORT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status  );
                        break;

                     default:
                        break;
                  }/* switch of  Test O.202.19 */
                  break;

                  /* sb030.103 : Added new test case to process the ABORT
                                 chunk bundled with Cookie */
                  case 20:    /* Test O.202.20: Expected Results */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        /* Check INIT_ACK chunk */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                        break;
                     case 2:
                        /* we expect an AssocInd */
                        SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                        break;
                     case 3:
                        /* we expect an TermInd */
                        assoc_1.suAssocId=0;
                        SB_SETUP_TERM_IND(assoc_1, 6,0);
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                        break;
                  }/* switch of  Test O.202.20 */
                  break;

                  case 21:      /* sb035.103: Test O.202.21: Expected Results */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        /* Check ABORT chunk */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_INVAL_MAND_PAR, 0, FALSE, SB_ID_ABORT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                        if (ret == ROK)
                        {
                           ret = ROK;
                        }
                        else
                        {
                           ret = RFAILED;
                        }
                        break;
                  }
                  break;
               }      /* End switch(curtstnum) #2 */

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
                  /* sb032.102 :  IPV6 Support Added */
                  if (((curtstnum == 7 ) || (curtstnum == 8)) && (sbAccCb.curTst.subTest == 3) )
                  {
                     if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
                     {
                        sbAccCb.curTst.subTestsPass++;
                        sbAccCb.curTst.subTest++;
                        sbAccCb.curTst.state++;
                        sbAccCb.curTst.bTickMask = 0;
                     }
                  }
                  /*-- RFC 4460: MLK fix*/
                  else if ( ((curtstnum == 1)||(curtstnum == 6)) &&
                             (sbAccCb.curTst.subTest == 3)) 
                  {
                     if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE)) 
                     {
                        sbAccCb.curTst.subTestsPass++;
                        sbAccCb.curTst.subTest++;
                        sbAccCb.curTst.state++;
                        sbAccCb.curTst.bTickMask = 0;
                     }
                  }
                  /*-- RFC 4460: MLK fix*/
                  else if ( (curtstnum == 2) && (sbAccCb.curTst.subTest == 4) )
                  {
                     if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE)) 
                     {
                        sbAccCb.curTst.subTestsPass++;
                        sbAccCb.curTst.subTest++;
                        sbAccCb.curTst.state++;
                        sbAccCb.curTst.bTickMask = 0;
                     }
                  }
                  else if ( (curtstnum == 5) &&
                            ( (sbAccCb.curTst.subTest == 3) ||
                              (sbAccCb.curTst.subTest == 6) ) )
                  {
                     if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE)) /* RFC 4460 upgrade */
                     {
                        sbAccCb.curTst.subTestsPass++;
                        sbAccCb.curTst.subTest++;
                        sbAccCb.curTst.state++;
                        sbAccCb.curTst.bTickMask = 0;
                     }
                  }
                  else
                  {
                     sbAccCb.curTst.subTestsPass++;
                     sbAccCb.curTst.subTest++;
                     sbAccCb.curTst.state++;
                  }
               } /* ret = ROK */
            } /* primitive received */
            break;

         case 2: /* Do cleanup before next test */
            if (sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
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
   {
      doCleanup();
   }

   RETVALUE(ROK);
}  /* end sbSctAssocRcvTst */


/* sb012.103: Functions placed under the flag LSB12 */
#ifdef LSB12
/* Timers of Association Initialization and Termination */

/*
*       Fun:   sbO203_01
*
*       Desc:  Test case : O.203.01
*              Purpose   : Verify that the sending end t1InitTimer is
*                          started after the Init chunk is sent.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO203_01
(
void
)
#else
PUBLIC  S16 sbO203_01(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO203_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocTmrTst_1(curtstnum,"O.203.01");
   RETVALUE(ROK);
} /* end sbO203_01 */

/*
*       Fun:   sbO203_02
*
*       Desc:  Test case : O.203.02
*              Purpose   : Verify that the sending end T1-Init Timer is stopped
*                          after the INIT_ACK chunk is received.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO203_02
(
void
)
#else
PUBLIC  S16 sbO203_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.102.curtstnum */

   TRC2(sbO203_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocTmrTst_1(curtstnum,"O.203.02");
   RETVALUE(ROK);
} /* end sbO203_02 */

/*
*       Fun:   sbO203_03
*
*       Desc:  Test case : O.203.03
*              Purpose   : Verify that the sending end t1InitTimer is
*                          started again when the COOKIE chunk is sent.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO203_03
(
void
)
#else
PUBLIC  S16 sbO203_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO203_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocTmrTst_1(curtstnum,"O.203.03");
   RETVALUE(ROK);
} /* end sbO203_03 */

/*
*       Fun:   sbO203_04
*
*       Desc:  Test case : O.203.04
*              Purpose   : Verify that the sending end cookieTmr is stopped
*                          after the COOKIE_ACK chunk is sent.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO203_04
(
void
)
#else
PUBLIC  S16 sbO203_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO203_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 5;
   sbSctAssocTmrTst_1(curtstnum,"O.203.04");
   RETVALUE(ROK);
} /* end sbO203_04 */



/*
*       Fun:   sbO203_05
*
*       Desc:  Test case : O.203.05
*              Purpose   : Verify that the sending end t2Shutdown timer is
*                          started right after the SHUTDOWN chunk
*                          has been sent.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO203_05
(
void
)
#else
PUBLIC  S16 sbO203_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO203_05)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocTmrTst_2(curtstnum,"O.203.05");
   RETVALUE(ROK);
} /* end sbO203_05 */

/*
*       Fun:   sbO203_06
*
*       Desc:  Test case : O.203.06
*              Purpose   : Verify that if the SHUTDOWN_ACK is received
*                          before the sending end t2Shutdown timer expires,
*                          the SCTP should stop the timer.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO203_06
(
void
)
#else
PUBLIC  S16 sbO203_06(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.01 curtstnum */

   TRC2(sbO203_06)
   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocTmrTst_2(curtstnum,"O.203.06");
   RETVALUE(ROK);
} /* end sbO203_06 */

/*
*       Fun:   sbSctAssocTmrTst_1
*
*       Desc:  Initialization and Termination of Association timers (#1).
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctAssocTmrTst_1
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocTmrTst_1(curtstnum, numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   PRIVATE SbMgmtQElm    mgmt;
   PRIVATE SbOperQElm    oper;
   PRIVATE SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE SbAccAssoc    assoc_1;
   Buffer        *mBuf;
   CmIpHdrParm   hdrParm;
   SbAccMsgQElm  *msg;

   TRC2(sbSctAssocTmrTst_1)
   ret = ROK;

  /* Pretests/Setup */
   if (sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG();
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff);
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            SB_SCTSAPCFG(SAP_1);
            if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
            {
               SB_TSAPCFG(SAP_1);
               if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
               {
                  SB_BIND_HITSAP(SUID_0, SPID_0, BIT0);
                  if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
                  {
                     setupAssoc(&assoc_1, ASSOC_1);
                     if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                     {
                        SB_DISABLE_TRACE();
                        SB_ENTERTEST( sbAccCb.curTst.bTraceMask, BIT0 )
                     } /* end bAssocMask if */
                  } /* end TSapMask if */
               }/*end TSapCfgMask if*/
            } /* end SctSapCfgMask if */
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
               case 1:    /* Test O.203.01: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBTMR;
                        (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;
                        break;
                     case 2: /* Send the AssocReq chunk */
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, \
                                             SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /*expected response */
                        break;
                     case 3:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBTMR;
                        (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response */
                        break;
                     default:
                        break;
                  }
                  break;
               case 2:     /* Test O.203.02: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1: /* Send the AssocReq chunk */
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, \
                                             SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /*expected response */
                        break;
                     case 2:   /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /*expected response */
                        break;
                     case 3:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBTMR;
                        (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response */
                        break;
                     default:
                        break;
                  }
                  break;
               case 3:      /* Test O.203.03: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1: /* Send the AssocReq chunk */
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, \
                                             SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /*expected response */
                        break;
                     case 2:   /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /*expected response */
                        break;
                     case 3:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBTMR;
                        (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response */
                        break;
                     default:
                        break;
                  }
                  break;
               case 4:      /* Test O.203.04: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1: /* Send the AssocReq chunk */
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, \
                                             SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spEndpId, \
                                             assoc_1.suAssocId, \
                                             &assoc_1.priPeerNAddr, \
                                             assoc_1.peerPort, \
                                             assoc_1.outStrms, \
                                             &assoc_1.peerNAddrLst, \
                                             &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /*expected response */
                        break;
                     case 2:   /* INIT_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN; /*expected response */
                        break;
                     case 3: /* COOKIE_ACK chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                             assoc_1.suConId, \
                                             &assoc_1.peerTAddr, \
                                             &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                             &assoc_1.localIf,
#endif
                                             mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND; /*expected response */
                        break;
                     case 4:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBTMR;
                        (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response */
                        break;
                     default:
                        break;
                  }
                  break;  /* End switch(curtstnum) #1 */
            }
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
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 1:    /* Test O.203.01: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check that INIT timer is stopped */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T1_INIT, STOPPED);
                           break;
                        case 2:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 3:
                           /* Check that INIT timer is running */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T1_INIT, RUNNING);
                           break;
                        default:
                           break;
                     }
                     break;
                  case 2:    /* Test O.203.02: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt,
                                                ACC_EVT_ASSOC_CFM,
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Check that INIT timer is stopped */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T1_INIT, STOPPED);
                           break;
                        default:
                           break;
                     }
                     break;
                  case 3:      /* Test O.203.03: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt,
                                                ACC_EVT_ASSOC_CFM,
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Check that COOKIE timer is running */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T1_COOKIE, RUNNING);
                           break;
                        default:
                           break;
                     }
                     break;
                  case 4:   /* Test O.203.04: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt,
                                                ACC_EVT_ASSOC_CFM,
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, \
                                                    &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                          /* Communication Up */
                          SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
                           break;
                        case 4:
                           /* Check that COOKIE timer is stopped */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T1_COOKIE, STOPPED);
                           break;
                        default:
                           break;
                     }
                     break;
               }     /* End switch(curtstnum) #2 */

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
            } /* end primitive received */

            if ( ( (curtstnum == 2) || (curtstnum == 3) || (curtstnum == 4) ) &&
                 (sbAccCb.curTst.subTest == 2) )
            {
               if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                   (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
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
               sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test/subtest */
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
   {
      doCleanup();
   }

   RETVALUE(ROK);
}  /* end sbSctAssocTmrTst_1 */

/*
*       Fun:   sbSctAssocTmrTst_2
*
*       Desc:  Initialization and Termination of Association timers (#2).
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctAssocTmrTst_2
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocTmrTst_2(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbOperQElm    oper;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   SbAccMsgQElm  *msg;
   PRIVATE SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE SbAccAssoc    assoc_1;
   Buffer        *mBuf;
   CmIpHdrParm   hdrParm;

   TRC2(sbSctAssocTmrTst_2)
   ret = ROK;

   /* Pretests/Setup */
   if(sbAccCb.curTst.bBusyPreTestConf)
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            SB_SCTSAPCFG(SAP_1)
            if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
            {
               SB_TSAPCFG(SAP_1)
               if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
               {
                  SB_DISABLE_TRACE() /* disable trace */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                     if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
                     {
                        setupAssoc(&assoc_1, ASSOC_1);
                        if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                        {
                           SB_EST_ASSOC(assoc_1, BIT0)
                           SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                        } /*end bAssocSetupMask */
                     } /* end bTSapMask */
                  } /* end bTraceMask if */
               }/*end TSapCfgMask if*/
            } /* end SctSapCfgMask if */
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
               case 5:    /* Test O.203.05: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBTMR;
                        (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response */
                        break;
                     case 2:   /* Send a TermReq with AbrtFlg = False */
                        (void)  ItLiSctTermReq(&sbAccCb.itPst,
                                             assoc_1.spId,
                                             assoc_1.spAssocId,
                                             SCT_ASSOCID_SP, FALSE);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 3:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBTMR;
                        (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response */
                        break;
                     default:
                        break;
                  }
                  break;
               case 6:      /* Test O.203.06: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1: /* Send a TermReq with AbrtFlg = False */
                        (void)  ItLiSctTermReq(&sbAccCb.itPst,
                                               assoc_1.spId,
                                               assoc_1.spAssocId,
                                               SCT_ASSOCID_SP, FALSE);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2: /* SHUTDOWN_ACK chunk */
                       if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                           ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                        {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildShutdwnAckChunk(mBuf,&buildPar, &assoc_1);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                     assoc_1.suConId, \
                                     &assoc_1.peerTAddr, \
                                     &assoc_1.localTAddr, \
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                     &assoc_1.localIf,
#endif
                                     mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /*expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                        }
                          break;
                     case 3:
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.elmId.elmnt = STSBTMR;
                        (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;  /*expected response */
                        break;
                     default:
                        break;
                  }
                  break;
            }  /* End curtstum switch #1 */
            sbAccCb.curTst.state++;
            break;

         /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if(status == WAIT)
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
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */

                  case 5:    /* Test O.203.05: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check that SHUTDOWN timer is stopped */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T2_SDOWN, STOPPED);
                           break;
                        case 2:
                           /* Check SHUTDOWN chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 3:
                           /* Check that SHUTDOWN timer is running */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T2_SDOWN, RUNNING);
                           break;
                        default:
                           break;
                     }
                     break;
                  case 6:      /* Test O.203.06: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                       case 1:
                          /* Check SHUTDOWN chunk */
                          oper.hi.spId = SPID_0;
                          SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                          ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                          break;
                       case 2:
                          sbAccPeekMsg(&msg);
                          if(msg->evntType == ACC_EVT_TERM_CFM)
                          {
                             SB_SETUP_TERM_CFM(assoc_1,SCT_OK, SCT_CAUSE_NOT_APPL)
                             ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status, &reason);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          }
                          else if (msg->evntType == ACC_EVT_UDAT_REQ)
                          {     /* SB_VER13 - case added for SDOWN-CMPLT */
                             oper.hi.spId = SPID_0;
                             SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNCMPLT)
                             ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                               (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                                 sbAccCb.curTst.tickLstDoneFlg = TRUE;
                          break;
                       case 3:
                          /* Check that SHUTDOWN timer is stopped */
                          mgmt.cfm.status = LCM_PRIM_OK;
                          ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T2_SDOWN, STOPPED);
                          break;
                       default:
                          break;
                     }
                     break;
                  }     /* End switch(curtstnum) #2 */

               if(ret == RFAILED)
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

            } /*end of primitive received */

            if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
            {
               sbAccCb.curTst.subTest++;
               sbAccCb.curTst.bTickMask = 0;
            }
            sbAccCb.curTst.state++;
            break;

         case 2: /* Do cleanup before next test */
                if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst)
                {
                   sbAccCb.curTst.bTestsCompleted = TRUE;
                   sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test/subtest */
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
}  /* end sbSctAssocTmrTst_2 */
#endif /* LSB12 */



/*Duplication tests*/

/*
*       Fun:   sbO204_01
*
*       Desc:  Test case : O.204.01
*              Purpose   : Verify that if both endpoints try to generate an
*                          association at about the same time, the two
*                          requests will result in a single successful
*                          association.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_01
(
void
)
#else
PUBLIC  S16 sbO204_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO204_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocDuplTst_1(curtstnum,"O.204.01");
   RETVALUE(ROK);
} /* end sbO204_01 */

/*
*       Fun:   sbO204_02
*
*       Desc:  Test case : O.204.02
*              Purpose   : Verify that upon the reception of the INIT,
*                          the receiver generates an INIT_ACK with an
*                          encryption cookie.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_02
(
void
)
#else
PUBLIC  S16 sbO204_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO204_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 7;
   sbSctAssocDuplTst_1(curtstnum,"O.204.02");
   RETVALUE(ROK);
} /* end sbO204_02 */

/*
*       Fun:   sbO204_03
*
*       Desc:  Test case : O.204.03
*              Purpose   : Verify that the endpoint discards the duplicate INIT_ACK received in any other
*              state than COOKIE_WAIT.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_03
(
void
)
#else
PUBLIC  S16 sbO204_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO204_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 2;
   sbSctAssocDuplTst_1(curtstnum,"O.204.03");
   RETVALUE(ROK);
} /* end sbO204_03 */

/*
*       Fun:   sbO204_04
*
*       Desc:  Test case : O.204.04
*              Purpose   : Verify that an invalid duplicate cookie, received in any state of an association, will be discarded.              the two requests will result in a single successful association.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_04
(
void
)
#else
PUBLIC  S16 sbO204_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO204_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocDuplTst_1(curtstnum,"O.204.04");
   RETVALUE(ROK);
} /* end sbO204_04 */

/*
*       Fun:   sbO204_05
*
*       Desc:  Test case : O.204.05
*              Purpose   : Verify that if a valid duplicate cookie with an
*                          expired lifetime is received, in any state for
*                          an association, a stale cookie error will be
*                          generated.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_05
(
void
)
#else
PUBLIC  S16 sbO204_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO204_05)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocDuplTst_2(curtstnum,"O.204.05");
   RETVALUE(ROK);
} /* end sbO204_05 */

/*
*       Fun:   sbO204_06
*
*       Desc:  Test case : O.204.06
*              Purpose   : Test the handling of a duplicate cookie in any
*                          state of an association.  If the cookie is valid,
*                          the TCB is unpacked in to a temporary TCB.  In the
*                          case where the verification tag in the temporary
*                          TCB matches the verification tag of the existing
*                          TCB, the cookie is considered to be a duplicate.
*                          Verify that the endpoint send a COOKIE_ACK to the
*                          peer endpoint, without updating the existing TCB.
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_06
(
void
)
#else
PUBLIC  S16 sbO204_06(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO204_06)
   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 5;
   sbSctAssocDuplTst_2(curtstnum,"O.204.06");
   RETVALUE(ROK);
} /* end sbO204_06 */

/*
*       Fun:   sbO204_07
*
*       Desc:  Test case : O.204.07
*              Purpose   : Test the handling of a duplicate cookie in any
*                          state of an association.  If the cookie is valid,
*                          the TCB is unpacked into a temporary TCB. In the
*                          case where the peer's verification tag in the
*                          temporary TCB does not match the peer's
*                          verification tag in the existing TCB, it may be
*                          accepted that a restart of the peer had occurred.
*                          Verify that the endpoint will report the restart
*                          to the upper layer and send a COOKIE_ACK to its
*                          peer.
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_07
(
void
)
#else
PUBLIC  S16 sbO204_07(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.103.curtstnum */

   TRC2(sbO204_07)
   curtstnum = 7;
   sbAccCb.curTst.numSubTst = 6;
   sbSctAssocDuplTst_2(curtstnum,"O.204.07");
   RETVALUE(ROK);
} /* end sbO204_07 */

/* sb030.103: Fixed the test case. */
/*
*       Fun:   sbO204_08
*
*       Desc:  Test case : O.204.08
*              Purpose   : Test the handling of a duplicate shutdown in the
*                          SHUTDOWN RECEIVED state. The shutdown should be
*                          silently discarded. 
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_08
(
void
)
#else
PUBLIC  S16 sbO204_08(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO204_08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 4;
   sbSctAssocDuplTst_2(curtstnum,"O.204.08");
   RETVALUE(ROK);
} /* end sbO204_08 */

/* RFC 4460 -- SB_RFC_2, SB_RFC_10 */
/*
*       Fun:   sbO204_09
*
*       Desc:  Test case : O.204.09
*              Purpose   : Test the handling INIT with new address in ESTABLSIHED state
*                          ABORT <Restart with new address> shall be sent
*
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO204_09
(
void
)
#else
PUBLIC  S16 sbO204_09(void)
#endif
{
   U8          curtstnum;

   TRC2(sbO204_09)
   curtstnum = 9;
   sbAccCb.curTst.numSubTst = 5;
   sbSctAssocDuplTst_2(curtstnum,"O.204.09");
   RETVALUE(ROK);
} /* end sbO204_09 */


/* sbSctAssocDuplTst_1*/

/*
*       Fun:   sbSctAssocDuplTst_1
*
*       Desc:  Initialization and Termination of Association timers (#2).
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctAssocDuplTst_1
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocDuplTst_1(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf;
   CmIpHdrParm   hdrParm;
   PRIVATE       SbOperQElm     oper;
   PRIVATE       SbMgmt         sbMgmt;
   PRIVATE       SbAccAssoc     assoc_1;
   PRIVATE       SbAccAssoc     assoc_2;
   PRIVATE       SbAccChunkBld  buildPar;            /* Parameters used for checking chunks */
   U8            ID;
   SbAccMsgQElm  *msg;

   TRC2(sbSctAssocDuplTst_1)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            SB_TSAPCFG(SAP_1)
            if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
            {
               SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
               if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
               {
                  SB_SCTSAPCFG(SAP_1)
                  if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                  {
                     setupAssoc(&assoc_1, ASSOC_1);
                     if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                     {
                        switch(curtstnum)/* Pretests continues */
                        {
                           case 1: /* pretests: O.204.01 */
                              if (isBitSet(sbAccCb.curTst.bAssocMask, BIT0) == FALSE)
                              {
                                 cmMemcpy((U8 *) &assoc_2, (U8 *) &assoc_1,
                                          sizeof(SbAccAssoc));
                                 setBit(&sbAccCb.curTst.bAssocMask,BIT0);
                              }
                              break;
                           case 2: /* pretests: O.204.02 */
                              if (isBitSet(sbAccCb.curTst.bAssocMask, BIT0) == FALSE)
                              {
                                 cmMemcpy((U8 *) &assoc_2, (U8 *) &assoc_1,
                                          sizeof(SbAccAssoc));
                                 setBit(&sbAccCb.curTst.bAssocMask,BIT0);
                              }
                              break;
                           case 3: /* pretests: O.204.03 */
                              cmMemcpy((U8 *) &assoc_2, (U8 *) &assoc_1,
                                       sizeof(SbAccAssoc));
                              SB_EST_ASSOC(assoc_1, BIT0 )
                              break;
                           case 4: /* pretests: O.204.04 */
                              if (isBitSet(sbAccCb.curTst.bAssocMask, BIT0) == FALSE)
                              {
                                 setBit(&sbAccCb.curTst.bAssocMask,BIT0);
                              }
                              break;
                           default:
                              break;
                        }
                        if (isBitSet(sbAccCb.curTst.bAssocMask,BIT0) == TRUE)
                        {
                           SB_DISABLE_TRACE() /* disable trace */
                           SB_ENTERTEST( sbAccCb.curTst.bTraceMask, BIT0)
                        } /* end bAssocMask if */
                     } /* end bAssocSetupMask if */
                  } /* end SctSapCfgMask if */
               }/*end TSapMask if*/
            } /* end TSapCfgMask if */
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest == TRUE)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
               case 1:    /* Test O.204.01: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, \
                                               SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:    /* INIT chunk and INIT ACK */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitChunk(mBuf,&buildPar, &assoc_2);
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                              &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /*expected response */
                        break;
                     case 3:   /* COOKIE and COOKIE_ACK */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_2);
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /*expected response */
                        break;
                  }
                  break;

               case 2:     /* Test O.204.02: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, \
                                               SB_ACC_SCT_TOS, (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               assoc_1.suAssocId, \
                                               &assoc_1.priPeerNAddr, \
                                               assoc_1.peerPort, \
                                               assoc_1.outStrms, \
                                               &assoc_1.peerNAddrLst, \
                                               &assoc_1.localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildInitAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 3:   /* COOKIE_ACK */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieAckChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;
                        break;
                     case 4:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        /* RFC 4460 upgrade -- need to have new Itag */
                        buildPar.newITag = TRUE; 
                        buildInitChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 5: /* SB_VER13  - Case modified */
                       if(( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                           ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                           SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                           buildCookieChunk(mBuf,&buildPar, &assoc_2);
                           SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                           (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                                 assoc_2.suConId,
                                                 &assoc_2.peerTAddr,
                                                 &assoc_2.localTAddr,
                                                 &hdrParm ,
#ifdef LOCAL_INTF
                                                 &assoc_2.localIf,
#endif
                                                 mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /*expected response */
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 6 :
                       if(isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE)
                       {
                         oper.it.assocParams.t.cookieParams.suAssocId = assoc_2.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                         (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                         (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                         sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                       }
                       break;
                  }
                  break;

               case 3:      /* Test O.204.03: Execution */
                  /* Duplicate INIT_ACK chunk */
                  SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                  buildInitAckChunk(mBuf,&buildPar, &assoc_2);
                  SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                  (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                         assoc_2.suConId, \
                                         &assoc_2.peerTAddr, \
                                         &assoc_2.localTAddr, \
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_NO_RESP;  /*expected response */
                  break;

               case 4:      /* Test O.204.04: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 5;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_ASSOC_IND;
                        break;
                     case 3:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        assoc_2.cookieLeng = 16;
                        buildCookieChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;

                  }
                  break;
            }  /* End switch(curtstnum) #1*/
            sbAccCb.curTst.state++;
            break;

            /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if (status == WAIT)
            {
               if ( ( curtstnum == 3 ) ||
                    ( (curtstnum == 4) && (sbAccCb.curTst.subTest == 3) ) )
               {
                  if (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)
                  {
                     setBit(&sbAccCb.curTst.bTickMask, BIT0);
                     SPrint("No response expected, wait for timeout\n");
                  }
               }
               /* wait for message to reach the queue */
               RETVALUE(ROK);
            }
            else if (status == TIMEOUT)
            {
               if ( ( curtstnum == 3 ) ||
                    ( (curtstnum == 4) && (sbAccCb.curTst.subTest == 3) ) )
               {
                  sbAccCb.curTst.subTestsPass++;
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  break;
               }
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            {
               /*primitive received */
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 1:    /* Test O.204.01: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              /* check AssocCfm */
                              SB_SETUP_ASSOC_CFM(assoc_1)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_CFM, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_COOKIE )
                              {
                                 /* Check COOKIE chunk */
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              else if ( ID == SB_ID_INITACK )
                              {
                                 /* Check INIT_ACK chunk */
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status   );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
                              else
                              {
                                 status = INC_MSGTYPE;
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT2);
                                 ret = RFAILED;
                              }
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /*RFC 4460: MLK Fix*/
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_COOKIEACK )
                              {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
                              else if (ID == SB_ID_HBEAT)
                              {
                                 /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                       &assoc_2, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* Communication Up */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                               SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                     }
                     break;

                  case 2:    /* Test O.204.02: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INIT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_ASSOC_CFM)
                           {
                              /* check AssocCfm */
                              SB_SETUP_ASSOC_CFM(assoc_2)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_CFM, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIE)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              ret = RFAILED;
                           }
                           break;
                        case 3:
                           /* Communication Up */
                           SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
                           break;
                        case 4:
                           /* duplicate INIT ACK */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status   );
                           break;
                        case 5:
                          sbAccPeekMsg(&msg);
                          if(msg->evntType == ACC_EVT_TERM_IND)
                          {
                             SB_SETUP_TERM_IND(assoc_2, SCT_STATUS_RESTART, SCT_CAUSE_NOT_APPL)
                             ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                             setBit(&sbAccCb.curTst.bTickMask, BIT0);
                          }
                          else if(msg->evntType == ACC_EVT_ASSOC_IND)
                          {
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           setBit(&sbAccCb.curTst.bTickMask, BIT2);
                          }
                         break;
                       case 6:
                          sbAccPeekMsg(&msg);
                          if(msg->evntType == ACC_EVT_UDAT_REQ)
                          {
                              /*RFC 4460: MLK Fix*/
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if ( ID == SB_ID_COOKIEACK )
                              {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                              }
                              else if (ID == SB_ID_HBEAT)
                              {
                                 /* RFC 4460 upgrade -- receive the  path probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                       &assoc_2, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                          }
                          /* RFC 4460: MLK Fix*/
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* Communication Up */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, \
                                               SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, \
                                                ACC_EVT_STA_IND, \
                                                &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                          else
                          {
                             status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                             setBit(&sbAccCb.curTst.bTickMask, BIT2);
                             ret = RFAILED;
                          }
                          break;
                     }
                     break;

                  case 3:    /* Test O.204.03: Expected Results */
                     /* No response to duplicate INIT_ACK */
                     SPrint("Ooops, something arrived that I'm not expecting\n\n\n");
                     ret = RFAILED;
                     break;

                  case 4:      /* Test O.204.04: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                           cmMemcpy((U8 *) &assoc_2, (U8 *) &assoc_1, sizeof(SbAccAssoc));
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           SPrint("Ooops, something arrived that I'm not expecting\n\n\n");
                           ret = RFAILED;
                           break;
                     }
                     break;
               }     /* End switch(curtstnum) #2 */

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
               /*RFC 4460 : MLK fix --*/
                   if ( ( (curtstnum == 1) && ((sbAccCb.curTst.subTest == 2)||(sbAccCb.curTst.subTest == 3)) ) ||
                     ( (curtstnum == 2) && ((sbAccCb.curTst.subTest == 5)||(sbAccCb.curTst.subTest == 6)) ) )
                  {
                     if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE) )
                     {
                        sbAccCb.curTst.subTestsPass++;
                        sbAccCb.curTst.subTest++;
                        sbAccCb.curTst.state++;
                        sbAccCb.curTst.bTickMask = 0;
                     }
                  }
                  else if ( (curtstnum == 2) && (sbAccCb.curTst.subTest == 2) )
                  {
                     if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                     {
                        sbAccCb.curTst.subTestsPass++;
                        sbAccCb.curTst.subTest++;
                        sbAccCb.curTst.state++;
                        sbAccCb.curTst.bTickMask = 0;
                     }
                  }  /* SB_VER13 - */
                  else
                  {
                     sbAccCb.curTst.subTestsPass++;
                     sbAccCb.curTst.subTest++;
                     sbAccCb.curTst.state++;
                     sbAccCb.curTst.bTickMask = 0;
                  }
               } /* ret = ROK */
            } /* primitive received */
            break;

         case 2: /* Do cleanup before next test */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            sbAccCb.curTst.state = 0;
            break;
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
   {
      doCleanup();
   }

   RETVALUE(ROK);
}  /* end sbSctAssocDuplTst_1 */

/*
*       Fun:   sbSctAssocDuplTst_2
*
*       Desc:  Initialization and Termination of Association timers (#2).
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctAssocDuplTst_2
(
U8   curtstnum,
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctAssocDuplTst_2(curtstnum,numstr)
U8   curtstnum;
S8  *numstr;       /* test number */
#endif
{
   PRIVATE SbMgmtQElm           mgmt;
   PRIVATE SbOperQElm           oper;
   PRIVATE SbMgmt               sbMgmt;
   SctStatus            status;
   Reason               reason;
   S16                  ret;
   PRIVATE SbAccChunkBld        buildPar;
   PRIVATE SbAccAssoc           assoc_1;
   PRIVATE SbAccAssoc           assoc_2;
   Buffer              *mBuf;
   CmIpHdrParm          hdrParm;
   SbAccMsgQElm        *msg;
   CmNetAddr            dfltPriPeerNAddr;

   TRC2(sbSctAssocDuplTst_2)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            SB_TSAPCFG(SAP_1)
            if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
            {
               SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
               if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
               {
                  if ( curtstnum == 5 )
                  {
                     if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                     {  /* SB_SCTSAPCFG with different cookieLife */
                        sbStdSctSapCfg(&sbMgmt, SAP_1);
                        sbMgmt.t.cfg.s.sctSapCfg.reConfig.cookieLife = 5;
                        sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                     }
                  }
                  else if ( curtstnum == 8 ) /* sb030.103: Fix for the test case.  */
                  {
                     if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                     {
                        sbStdSctSapCfg(&sbMgmt, SAP_1);
                        sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial = 5;
                        sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin = 5;
                        sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                     }
                  }
                  else
                  {
                     SB_SCTSAPCFG(SAP_1)
                  }
                  if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                  {
                     setupAssoc(&assoc_1, ASSOC_1);
                      if ( curtstnum == 8 )   /* 204.08 */
                     {
                        if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                        {
                           SB_DISABLE_TRACE()
                           if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                           {
                              SB_EST_ASSOC(assoc_1, BIT0)
                              if(isBitSet(sbAccCb.curTst.bAssocMask, BIT0) == TRUE )
                              {
                                 SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                              }
                           }
                        }
                     }
                     else
                     {
                        if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                        {
                           SB_DISABLE_TRACE() /* disable trace */
                           if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                           {
                              SB_ENTERTEST( sbAccCb.curTst.bTraceMask, BIT0)
                           }
                        }
                     }
                  } /* end SctSapCfgMask if */
               }/*end TSapMask if*/
            } /* end TSapCfgMask if */
         } /* end debugPMask if*/
      } /* end ConfigMask if */
   }  /* end pretests */


   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
               case 5:    /* Test O.204.05: Execution */
               {
                  switch( sbAccCb.curTst.subTest )
                  {
                     case 1:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 4;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                                &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:
                        sbAccCb.curTst.delay = 2;
                        break;
                     case 3:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     default:
                        break;
                  }
                  break;
               } /* 204.05 execution */
               case 6:     /* Test O.204.06: Execution */
                  switch( sbAccCb.curTst.subTest )
                  {
                     case 1:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 4;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        cmMemcpy((U8 *) &assoc_2, (U8 *) &assoc_1,
                                 sizeof(SbAccAssoc));
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 3:
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        break;
                     case 4:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;

                     default:
                        break;
                  }
                  break;
               case 7:      /* Test O.204.07: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 4;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 3:
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        break;
                     case 4:
                        cmMemcpy((U8 *) &assoc_2, (U8 *) &assoc_1,
                                 sizeof(SbAccAssoc));

                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 4;
                        /* different peer tag */
                        buildPar.newITag = TRUE;
                        buildInitChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 5:
                        /* RFC 4460 upgrade -- send back the HBEAT_ACK in response to probe HBEAT */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildHBeatAckChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                               &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
/* end */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                  }
                  break;
               case 8:      /* Test O.204.08: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters for data transmission */
                        dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                        (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                             assoc_1.spAssocId, \
                                             &dfltPriPeerNAddr, \
                                             ACC_STREAMID, ORDER, \
                                             NOBUNDLE, ACC_NO_LIFETM_LIM, \
                                             ACC_PROT_ID, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:
                        SB_SETUP_DAT_REQ(mBuf);
                        SB_RLSMEM(mBuf);
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.cumTsn--;
                        buildShutdwnChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                                mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        break;
                     case 3:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildShutdwnChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /*expected response */
                        break;
                  } /* O.204.08 execution. */
                  break;
               case 9: /* Test O.204.09: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 4;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 2:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_1.suConId,
                                               &assoc_1.peerTAddr,
                                               &assoc_1.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);

                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 3:
                        oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;
/* sb060.102: TOS changes */
#ifdef SCT3
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SB_ACC_SCT_TOS, SCT_OK, \
                                               (Buffer*)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */
                        break;
                     case 4:
                        cmMemcpy((U8 *) &assoc_2, (U8 *) &assoc_1,
                                 sizeof(SbAccAssoc));

                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 4;
                        /* different peer tag */
                        buildPar.newITag = TRUE;
                        /* use new address in INIT */
                        buildPar.newAddr = TRUE;
                        buildInitChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                               assoc_2.suConId,
                                               &assoc_2.peerTAddr,
                                               &assoc_2.localTAddr,
                                               &hdrParm ,
#ifdef LOCAL_INTF
                                               &assoc_2.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        buildPar.newAddr = TRUE;/* Reset the flag, so that it wont affect other test cases */
                        break;
                   }
                break;
            }  /* End switch(curtstnum) #1*/
            sbAccCb.curTst.state++;
            break;
         /* Dequeue response and test */
         case 1:
            sbAccVfyMsg(&status);
            if (status == WAIT)
            { 
               /* sb030.103: Fix for test case O.204.08  */ 
               RETVALUE(ROK);
            }
            else if (status == TIMEOUT)
            {
               if ( (curtstnum == 5) && (sbAccCb.curTst.subTest == 2) )
               {
                  SPrint("Delay of 2 s completed \n");
                  sbAccCb.curTst.delay = 0; /* return to default setting */
                  sbAccCb.curTst.subTestsPass++;
                  sbAccCb.curTst.subTest++;
                  sbAccCb.curTst.state++;
                  break;
               }
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                   sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            {
               /*primitive received */
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 5:    /* Test O.204.05: Expected Results */
                  {
                     switch( sbAccCb.curTst.subTest )
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status   );
                           break;
                        case 3:
                           /* we expect a stale cookie error */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_STALE, 0, FALSE, SB_ID_ERROR)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                           break;
                        default:
                           break;
                     }
                     break;
                  } /* 204.05 expected */
                  case 6:    /* Test O.204.06: Expected Results */
                  {
                     switch( sbAccCb.curTst.subTest )
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* we expect a COMM UP status indication */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL )
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {

                              if(isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)
                              {
                                 /* RFC 4460 upgrade -- receive the probing HBEAT */
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_HBEAT)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              else
                              {
                                 /* we expect a COOKIE ACK */
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              }
                           }
                           break;
                        default:
                           break;
                     }
                     break;
                  } /* 204.06 expected */
                  case 7:      /* Test O.204.07: Expected Results */
                  {
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* we expect a COMM UP status indication */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL )
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {

                              if(isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)
                              {
                                /* RFC 4460 upgrade -- expect the probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              else
                              {
                           /* Check INIT_ACK chunk */
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_2, &status);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              }
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              ret = RFAILED;
                           }
                           break;
                        case 5:
                           /* we expect a RESTART TermInd */
                           SB_SETUP_TERM_IND(assoc_2, SCT_STATUS_RESTART, SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                           break;
                     }
                     break;
                  } /* 204.07 expected */
                  case 8:      /* Test O.204.08: Expected Results */
                  {
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check DATA chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SPrint("\n\n == Checking for SHUTDOWNACK CHUNK ==\n");
                              /* Check SHUTDOWN_ack chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              if(ret != ROK)
                              SPrint("\n\n == ERROR in SHUTDOWNACK CHUNK ==\n");
                           }
                           else if(msg->evntType == ACC_EVT_TERM_IND)
                           {
                              SPrint(" \n ===== Recevied TermInd at the user oF SCTP ==== \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_SHUTDOWN, SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND, &status, &reason);
                              if (ret!= ROK)
                              SPrint(" \n ===== TermInd with error ==== \n\n ");
                           }
                           else
                           {
                              SPrint(" \n ===== Not Recevied TermInd at the user oF SCTP ==== \n ");
                              status = INC_EVNTTYPE;
                              ret = RFAILED;
                           }
                           break;
                        /* sb043.102: TermInd is generated when rcv SDown */
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SPrint("\n\n ==  Checking for DATA CHUNK ==\n");
                              /* Check SHUTDOWN_ack chunk */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              if(ret != ROK)
                              SPrint("\n\n == ERROR in DATA CHUNK ==\n");
                           }
                           else
                           {
                              SPrint(" \n ===== Not sending DATA  ==== \n ");
                              status = INC_EVNTTYPE;
                              ret = RFAILED;
                           }
                           break;
                     } /* O.204.08 expected */
                     break;
                  }
                  case 9: /* Test O.204.09: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           /* Check INIT_ACK chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_INITACK)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                           break;
                        case 2:
                           /* we expect an AssocInd */
                           SB_SETUP_ASSOC_IND(assoc_1, ACC_COOKIE);
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND, &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              /* we expect a COMM UP status indication */
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL )
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {

                              if(isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)
                              {
                                /* RFC 4460 upgrade -- expect the probing HBEAT */
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              else
                              {
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_RESTART_ASSOC_NEW_ADDR, 0, FALSE, SB_ID_ABORT)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              }
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
               } /* End switch(curtstnum) #2 */
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
/*
                  if ( ( (curtstnum == 7) || (curtstnum == 6) ) &&
                       (sbAccCb.curTst.subTest == 3) )
*/
                  if ( ( (curtstnum == 7) &&( (sbAccCb.curTst.subTest == 3) || (sbAccCb.curTst.subTest == 4) ) ) || \
                       ( (curtstnum == 6)&& ((sbAccCb.curTst.subTest == 3) || (sbAccCb.curTst.subTest == 4) )) ||
                       ( (curtstnum == 9)&& ((sbAccCb.curTst.subTest == 3) || (sbAccCb.curTst.subTest == 4) )))
                  {
                     if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                     {
                        sbAccCb.curTst.subTestsPass++;
                        sbAccCb.curTst.subTest++;
                        sbAccCb.curTst.state++;
                        sbAccCb.curTst.bTickMask = 0;
                     }
                  }
                  else
                  {
                     sbAccCb.curTst.subTestsPass++;
                     sbAccCb.curTst.subTest++;
                     sbAccCb.curTst.state++;
                     sbAccCb.curTst.bTickMask = 0;
                  }
               } /* ret = ROK */
            } /* primitive received */
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
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
   {
      doCleanup();
   }

   RETVALUE(ROK);
}  /* end sbSctAssocDuplTst_2 */


/********************************************************************30**

         End of file:     sb_act3.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:07 2015

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
            sb043.102 hl   1. TermInd is generated when rcv SDown
            sb046.102 hl   1. Multiple IP address per endpoint support
            sb058.102 pr   1. Removed compilation warning. 
            sb060.102 pr   1. TOS changes.
            sb071.102 kp   1. Adjusted the value for maxPathReTx and
                              maxAssocReTx.
/main/4      ---  rsr/ag   1. Updated for Release of 1.3
            sb001.103 ag   1. If one address is there, then it is not sent
                              in INIT/INIT-AACK address list
                           2. ERROR is not sent for unrecognised parameter
            sb005.103 ag   1. IPV6 change.
	    sb008.103 nuX  1. Modified after adding new values for the status field.
            sb009.103 nuX  1. Changes made for SOL10 upgrade, changes are made under
                              SB_SOL10_MULTIPORT flag.
	    sb012.103 pkaX 1. Non-Unicast Address Fix: Added two new test cases.
                           2. Timer related functions are placed under LSB12 flag.
            sb013.103 pkaX 1. a_rwnd Fix: New function to build data chunk.
/main/4     sb024.103 ajainx 1. Included protId parameter in status indication. 
/main/4     sb028.103 ajainx 1. Added new test case for multiple TermInd issue.
                             2. Added new test cases to process the data
                                chunk bundled with Cookie.
/main/4     sb029.103 krkX   1. Added new test cases to check RFC compliance
                                issues.
/main/4     sb030.103 krkX   1. Added new testcases O.201.25,O.202.20,O.205.28,
                                O.205.29 and O.205.30.
                             2. Modified the test cases O.205.14, O.205.15,
                                O.205.16, O.204.08.
/main/4     sb031.103  vsk   1. Modified the test cases O.201.08
/main/4     sb035.103  vsk   1. Added new testcases O.201.26, O.201.27,
                                O.201.28 and O.201.21.
*********************************************************************91*/
