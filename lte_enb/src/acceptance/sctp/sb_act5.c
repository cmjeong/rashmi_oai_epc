

/********************************************************************20**

     Name:     sb_act5.c - Acceptance Tests for the SCTP layer

     Type:     C source file

     Desc:     C code for acceptance tests test cases.  Includes all the datapath tests.

     File:     sb_act5.c

     Sid:      sb_act5.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:08 2015

     Prg:      nct

*********************************************************************21*/

/*

  sb_act5.c - Acceptance Tests for the SCTP layer

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
   PRIVATE S16 sbSctDatPathPrmAddrTst  ARGS((U8  curtstnum, S8  *numstr));
   PRIVATE S16 sbSctDatPathHBeatTst_1  ARGS((U8   curtstnum, S8  *numstr ));
   PRIVATE S16 sbSctDatPathHBeatTst_2  ARGS((U8   curtstnum, S8  *numstr ));
   PRIVATE S16 sbSctDatPathFailoverTst  ARGS((U8   curtstnum, S8  *numstr ));

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */


/*
*       Fun:   sbO400_01
*
*       Desc:  Test case : O.400.01
*              Purpose   : Verify that data the destination network address may be successfully changed
*                          by the user.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO400_01
(
void
)
#else
PUBLIC  S16 sbO400_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO400_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 4;
   sbSctDatPathPrmAddrTst(curtstnum,"O.400.01");
   RETVALUE(ROK);
} /* end sbO400_01 */

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbO400_04
*
*       Desc:  Test case : O.400.04
*              Purpose   : Verify that data the destination network address may be successfully changed
*                          by the user for IPV6 addresses.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO400_04
(
void
)
#else
PUBLIC  S16 sbO400_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO400_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 4;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctDatPathPrmAddrTst(curtstnum,"O.400.04");
   RETVALUE(ROK);
} /* end sbO400_01 */
/*
*       Fun:   sbO400_02
*
*       Desc:  Test case : O.400.02
*              Purpose   : Verify that an effort to change the primary destination identifier fails
*                          when the association identifier does not correspond to an established
*                          association.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO400_02
(
void
)
#else
PUBLIC  S16 sbO400_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO400_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 2;
   (S16) sbSctDatPathPrmAddrTst(curtstnum,"O.400.02");
   RETVALUE(ROK);
} /* end sbO400_02 */

/*
*       Fun:   sbO400_03
*
*       Desc:  Test case : O.400.03
*              Purpose   : Verify that an effort to change the primary destination
*                          network address fails when the destination network address
*                          is not present in the network address list.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO400_03
(
void
)
#else
PUBLIC  S16 sbO400_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO400_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 2;
   (S16) sbSctDatPathPrmAddrTst(curtstnum,"O.400.03");
   RETVALUE(ROK);
} /* end sbO400_03 */

/*
*       Fun:   sbSctDatPathPrmAddrTst
*
*       Desc:  Setting of the primary address.
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctDatPathPrmAddrTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE S16 sbSctDatPathPrmAddrTst(curtstnum, numstr)
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
   CmNetAddr     dfltPriPeerNAddr;
   PRIVATE       SbAccChunkBld buildPar;
   PRIVATE       SbAccAssoc    assoc_1;
   Buffer       *mBuf;
   U8            ipv6NAddr[16];
   /* sb032.102 :  IPV6 Support Added */
   Bool            ipv6Ret;
/*   Txt           prntBuf[64]; */
   
   TRC2(sbSctDatPathPrmAddrTst)
   ret = ROK;

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
             case 1:    /* Test O.400.01: Execution */
                SB_SETUP_DAT_REQ(mBuf)     
                switch(sbAccCb.curTst.subTest)
                {
                   case 1:
                      dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                      (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                           &dfltPriPeerNAddr, ACC_STREAMID, ORDER, NOBUNDLE,\
                                           ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                     /*-- RFC 4460 - MLK Fix*/
                      SB_RLSMEM(mBuf);
                      SB_SETUP_CMNETADDR((assoc_1.priPeerNAddr), peerNAddrLst_1[3] )
                      (void)  ItLiSctSetPriReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                               &assoc_1.priPeerNAddr);
                      break;
                   case 3:
                      dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                      (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                           &dfltPriPeerNAddr, ACC_STREAMID, ORDER, NOBUNDLE,\
                                           ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                }
                break;
             case 2:    /* Test O.400.02: Execution */
                SB_SETUP_CMNETADDR(assoc_1.priPeerNAddr, peerNAddrLst_1[3] )
                (void)  ItLiSctSetPriReq(&sbAccCb.itPst, assoc_1.spId, SUASSOCID_2, \
                                         &assoc_1.priPeerNAddr);
                break;
             case 3:    /* Test O.400.03: Execution */
                 SB_SETUP_CMNETADDR(assoc_1.priPeerNAddr, peerNAddrLst_2[3] )
                (void)  ItLiSctSetPriReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                         &assoc_1.priPeerNAddr);
                break;
             /* sb032.102 :  IPV6 Support Added */
             case 4:    /* Test O.400.04: Execution */
                SB_SETUP_DAT_REQ(mBuf)     
                switch(sbAccCb.curTst.subTest)
                {
                   case 1:
                      dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                      (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                           &dfltPriPeerNAddr, ACC_STREAMID, ORDER, NOBUNDLE,\
                                           ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                      CPY_ACC_ASSOC1_PEER_IPV6(ipv6NAddr, 3)
                      SB_SETUP_CMNETADDR((assoc_1.priPeerNAddr), ipv6NAddr )
                      (void)  ItLiSctSetPriReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                               &assoc_1.priPeerNAddr);
                      break;
                   case 3:
                      dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                      (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                           &dfltPriPeerNAddr, ACC_STREAMID, ORDER, NOBUNDLE,\
                                           ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                }
                break;
          } /* end switch */
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
                                   ACC_EVT_SETPRI_CFM, TIMEOUT_ON_PRIM, 0);
                   /* Problem - do cleanup */
                   sbAccCb.curTst.bBusyPreTestConf = FALSE;
                   sbAccCb.curTst.bBusyCleanup = TRUE;

            }
            else
            {
             reason = 0;
                switch(curtstnum)
                {    /* Start switch(curtstnum) #2 */
                  case 1:      /* Test O.400.01: Expected Results */
                     switch(sbAccCb.curTst.subTest)
                     {  case 1:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
                            if (oper.hi.peerTAddr.u.ipv4TptAddr.address !=\
                                assoc_1.priPeerNAddr.u.ipv4NetAddr)
                           {
                              status = INC_ADDR;
                              ret = RFAILED;
                           }
                           break;
                        case 2:
                           oper.it.result = SCT_OK;
                           oper.it.cause = SCT_CAUSE_NOT_APPL;
                           oper.it.suAssocId = assoc_1.suAssocId;
                           oper.it.suId = assoc_1.suId;
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_SETPRI_CFM,\
                                             &status, &reason);
                        break;
                        case 3:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
                           
                           if (oper.hi.peerTAddr.u.ipv4TptAddr.address !=\
                               assoc_1.priPeerNAddr.u.ipv4NetAddr)
                           {
                              status = INC_ADDR;
                              ret = RFAILED;
                           }
                           break;
                     }
                     break;
                  case 2:      /* Test O.400.02: Expected Results */
                       oper.it.result = SCT_NOK;
                       oper.it.cause = SCT_CAUSE_INV_PAR_VAL;
                       oper.it.suAssocId = SUASSOCID_2;
                       oper.it.suId = assoc_1.suId;
                       ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_SETPRI_CFM, &status, &reason);
                       break;
                  case 3:      /* Test O.400.03: Expected Results */
                       oper.it.result = SCT_NOK;
                       oper.it.cause = SCT_CAUSE_INV_PAR_VAL;
                       oper.it.suAssocId = assoc_1.suAssocId;
                       oper.it.suId = assoc_1.suId;
                       ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_SETPRI_CFM, &status, &reason);
                       break;
                  /* sb032.102 :  IPV6 Support Added */
                  case 4:      /* Test O.400.04: Expected Results */
                     switch(sbAccCb.curTst.subTest)
                     {  case 1:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
                           SB_INET6_SAMEADDR(oper.hi.peerTAddr.u.ipv6TptAddr.ipv6NetAddr, assoc_1.priPeerNAddr.u.ipv6NetAddr, &ipv6Ret)
                            /*if (oper.hi.peerTAddr.u.ipv4TptAddr.address !=\
                                assoc_1.priPeerNAddr.u.ipv4NetAddr)*/
                           if(ipv6Ret == FALSE)
                           {
                              status = INC_ADDR;
                              ret = RFAILED;
                           }
                           break;
                        case 2:
                           oper.it.result = SCT_OK;
                           oper.it.cause = SCT_CAUSE_NOT_APPL;
                           oper.it.suAssocId = assoc_1.suAssocId;
                           oper.it.suId = assoc_1.suId;
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_SETPRI_CFM,\
                                             &status, &reason);
                        break;
                        case 3:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
                           
                           SB_INET6_SAMEADDR(oper.hi.peerTAddr.u.ipv6TptAddr.ipv6NetAddr, assoc_1.priPeerNAddr.u.ipv6NetAddr, &ipv6Ret)
                           /*if (oper.hi.peerTAddr.u.ipv4TptAddr.address !=\
                               assoc_1.priPeerNAddr.u.ipv4NetAddr)*/
                           if(ipv6Ret == FALSE)
                           {
                              status = INC_ADDR;
                              ret = RFAILED;
                           }
                           break;
                     }
                     break;
                 }     /* End switch(curtstnum) #2 */

             if(ret == RFAILED)
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       ACC_EVT_SETPRI_CFM, status, reason);
                  /* Problem - do cleanup */
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;

               }
               else     /* Subtest successful */
               {
                 sbAccCb.curTst.subTestsPass++;
               }   /*End Subtest successful */
            } /* end primitive received */
            sbAccCb.curTst.state++;
            sbAccCb.curTst.subTest++;
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
}  /* end sbSctDatPathPrmAddrTst */


/*
*       Fun:   sbO401_01
*
*       Desc:  Test case : O.401.01
*              Purpose   : Verify that the Heartbeat can be successfully enabled between two peer SCTP
*                          endpoints in an association.
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_01
(
void
)
#else
PUBLIC  S16 sbO401_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_01)
   curtstnum = 1;
   /*-- RFC 4460: MLK fix*/
   sbAccCb.curTst.numSubTst = 4;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.01");
   RETVALUE(ROK);
} /* end sbO401_01 */

/*
*       Fun:   sbO401_02
*
*       Desc:  Test case : O.401.02
*              Purpose   : Verify that if a heartbeat is activated,  HBEAT and HBEAT_ACK chunks will
*                          be sent between the two endpoints.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_02
(
void
)
#else
PUBLIC  S16 sbO401_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_02)
   curtstnum = 2;
   /*-- RFC 4460: MLK fix*/
   sbAccCb.curTst.numSubTst = 5;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.02");
   RETVALUE(ROK);
} /* end sbO401_02 */


/*
*       Fun:   sbO401_03
*
*       Desc:  Test case : O.401.03
*              Purpose   : Verify that the Heartbeat can be successfully
*                          disabled between two peer SCTP endpoints on an
*                          association.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_03
(
void
)
#else
PUBLIC  S16 sbO401_03(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 5;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.03");
   RETVALUE(ROK);
} /* end sbO401_03 */

/*
*       Fun:   sbO401_04
*
*       Desc:  Test case : O.401.04
*              Purpose   : Verify that the SCTP declares the transport address unreachable
*                          after maxPathReTx unsuccessful attempts to send a Heartbeat to it.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_04
(
void
)
#else
PUBLIC  S16 sbO401_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_04)
   curtstnum = 4;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.04");
   RETVALUE(ROK);
} /* end sbO401_04 */

/* sb012.103: Placed test case under the flag LSB12 */
#ifdef LSB12
/*
*       Fun:   sbO401_05
*
*       Desc:  Test case : O.401.05
*              Purpose   : Verify that the Heartbeat timer is running while the HBeat is activated.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_05
(
void
)
#else
PUBLIC  S16 sbO401_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_05)
   curtstnum = 5;
   /*-- RFC 4460: MLK fix*/
   sbAccCb.curTst.numSubTst = 4;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.05");
   RETVALUE(ROK);
} /* end sbO401_05 */
#endif /* LSB12 */

/* RFC 4460 -- SB_RFC_3 */
/*
*       Fun:   sbO401_10
*
*       Desc:  Test case : O.401.10
*              Purpose   : Verify the unacked HBEAT are considered for incrementing
*                          the error count on the address on which HBEAT is sent
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_10
(
void
)
#else
PUBLIC  S16 sbO401_10(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_10)
   curtstnum = 10;
   sbAccCb.curTst.numSubTst = 5;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.10");
   RETVALUE(ROK);
}  /* end sbO401_10 */

/* RFC 4460 -- SB_RFC_3 */
/*
*       Fun:   sbO401_11
*
*       Desc:  Test case : O.401.11
*              Purpose   : Verify that the HBEATing stops after sending SHUTDOWN
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_11
(
void
)
#else
PUBLIC  S16 sbO401_11(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_11)
   curtstnum = 11;
   sbAccCb.curTst.numSubTst = 10;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.11");
   RETVALUE(ROK);
}  /* end sbO401_11 */

/* RFC 4460 -- SB_RFC_5 */
/*
*       Fun:   sbO401_12
*
*       Desc:  Test case : O.401.12
*              Purpose   : Verify that om receipt of HBEAT with multiple TLV parameters,
*                          SCTP responds with HBEAT_ACK with all TLV's copied into it 
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_12
(
void
)
#else
PUBLIC  S16 sbO401_12(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_12)
   curtstnum = 12;
   sbAccCb.curTst.numSubTst = 2;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.12");
   RETVALUE(ROK);
}  /* end sbO401_12 */

/* sb021.103: Added new testcase */
/*
*       Fun:   sbO401_13
*
*       Desc:  Test case : O.401.13
*              Purpose   : Verify the changing HBeat timer value through HBeatReq and also through
*                          the SctSapReCfg.
*                          
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act5.c
*
*/
                                                                                                                                        
#ifdef ANSI
PUBLIC  S16 sbO401_13
(
void
)
#else
PUBLIC  S16 sbO401_13(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */
                                                                                                                                        
   TRC2(sbO401_13)
   curtstnum = 13;
   /*-- RFC 4460: MLK fix*/
   sbAccCb.curTst.numSubTst = 7;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.13");
   RETVALUE(ROK);
} /* end sbO401_13 */
                                                                                                                                        



/* sb012.103: Placed test case under the flag LSB12 */
#ifdef LSB12
/*
*
*       Fun:   sbO401_06
*
*       Desc:  Test case : O.401.06
*              Purpose   : Verify that the Heartbeat timer is stopped  when a transport
*                          address becomes unreachable.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_06
(
void
)
#else
PUBLIC  S16 sbO401_06(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_06)
   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 5;
   sbSctDatPathHBeatTst_1(curtstnum,"O.401.06");
   RETVALUE(ROK);
} /* end sbO401_06 */
#endif  /* LSB12 */

/*
*       Fun:   sbSctDatPathHBeatTst_1
*
*       Desc:  Checking the heartbeat functions.
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctDatPathHBeatTst_1
(
U8   curtstnum,     /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctDatPathHBeatTst_1(curtstnum,numstr)
U8   curtstnum;     /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   PRIVATE    SbOperQElm    oper;
   PRIVATE    SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE    SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE    SbAccAssoc    assoc_1;
   SbAccMsgQElm  *msg;
   CmIpHdrParm   hdrParm;
   Buffer        *mBuf;
/*   Txt           prntBuf[64]; */


   TRC2(sbSctDatPathHBeatTst_1)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
      {
         sbStdGenCfg(&sbMgmt);
         if ( curtstnum == 10 )
         {
            sbMgmt.t.cfg.s.genCfg.reConfig.maxPathReTx = 1;
            sbMgmt.t.cfg.s.genCfg.reConfig.maxAssocReTx = 2;
         }
         else
         {
            sbMgmt.t.cfg.s.genCfg.reConfig.maxPathReTx = 2;
         }
         sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
      }
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff) 
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            if(isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )  
            {                                                               
               sbStdSctSapCfg(&sbMgmt, SAP_1);
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin =  ACC_RTO_SHORT;
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax =  ACC_RTO_SHORT;
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial  =  ACC_RTO_SHORT;
               sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);                
            }                                                          
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
      } /* end ConfigMask if */  
   }  /* end pretests */   

   /* sb008.103: Initializing hdrParam strucure to zero */
   cmMemset((U8*)&hdrParm, 0, sizeof(CmIpHdrParm));

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
       case 0:
            switch(curtstnum)
               {    /* Start switch(curtstnum) #1 */
               case 1:    /* Test O.401.01: Execution */
                  switch(sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SPrint("Send HBeat Req \n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, 10,SCT_HBEAT_ENB_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                     case 2:
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                           /*-- RFC 4460: MLK fix*/
                     case 3:
                        SPrint("Send HBeat Req \n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, 0,SCT_HBEAT_DIS_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
 
                  }
                  break;
              case 2:    /* Test O.401.02: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spAssocId, \
                                               &assoc_1.priPeerNAddr,\
                                               10,SCT_HBEAT_ENB_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                    case 2:
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                    case 3:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildHBeatAckChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                               &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                           /*-- RFC 4460: MLK fix*/
                     case 4:
                        SPrint("Send HBeat Req \n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, 0,SCT_HBEAT_DIS_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                 }
                 break;
              case 3:    /* Test O.401.03: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                               &assoc_1.priPeerNAddr, 10,SCT_HBEAT_ENB_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                    case 2:
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                    case 3:
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                                &assoc_1.priPeerNAddr, 10,SCT_HBEAT_DIS_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                    case 4:
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildHBeatAckChunk(mBuf,&buildPar,&assoc_1);
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                               &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_NO_RESP;
                       break;
                 }
                 break;
              case 4:    /* Test O.401.04: Execution */
                 sbAccCb.curTst.numSubTst = \
                    (U8)(sbMgmt.t.cfg.s.genCfg.reConfig.maxPathReTx + 3);
                 if ( sbAccCb.curTst.subTest == 1)
                 {
                    (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr, 10,\
                                            SCT_HBEAT_ENB_DTA);
                    sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                 }
                 else
                 {
                    if ( sbAccCb.curTst.subTest < (sbAccCb.curTst.numSubTst -1) )
                    {
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                    }
                    else
                    {
                       if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                       {
                               sbAccCb.curTst.tickLstDoneFlg = FALSE;   
                               sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                       }
                    }
                 }
                 break;
/* sb012.103: Placed test case under the flag LSB12 */
#ifdef LSB12
              case 5:    /* Test O.401.05: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                               &assoc_1.priPeerNAddr, 10,SCT_HBEAT_ENB_DTA);
                       sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                       break;
                    case 2:
                       setResponse(&sbMgmt.hdr.response);
                       sbMgmt.hdr.elmId.elmnt = STSBTMR;
                       sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 1101;
                       (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;  /* expected result */
                       break;
                           /*-- RFC 4460: MLK fix*/
                     case 3:
                        SPrint("Send HBeat Req \n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, 0,SCT_HBEAT_DIS_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                 }

                   break;
              case 6:    /* Test O.401.06: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                               &assoc_1.priPeerNAddr, 10,SCT_HBEAT_ENB_DTA);
                       sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                       break;
                    case 2:
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                       break;
                    case 3:
                       (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                                &assoc_1.priPeerNAddr, 10,SCT_HBEAT_DIS_DTA);
                       sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                       break;
                    case 4:
                       setResponse(&sbMgmt.hdr.response);
                       sbMgmt.hdr.elmId.elmnt = STSBTMR;
                       sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 1102;
                       (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;  /* expected result */
                       break;
                 } /* end subtest switch  of 406.04 */
                 break;/* end execution of 406.04 */
#endif  /* LSB12 */
                case 10: /* Test O.401.10: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                               &assoc_1.priPeerNAddr, 10,SCT_HBEAT_ENB_DTA);
                       sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                       break;
                    case 3:
                       if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       break;
                    case 4:
                       if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       break;
                    default:
                       break;
                 } /* end subtest switch  of 401.10 */
                 break;
                case 11: /* Test O.401.11: Execution */
                   if(sbAccCb.curTst.subTest == 1)
                   {
                        SPrint("Send HBEAT Request\n ");
                       (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                               &assoc_1.priPeerNAddr, 10,SCT_HBEAT_ENB_DTA);
                       sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                   }
                   else if ((sbAccCb.curTst.subTest == 3) || (sbAccCb.curTst.subTest == 4))
                   {
                        SPrint("Send HBEAT_ACK\n ");
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildHBeatAckChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                               &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                   }
                   else if (sbAccCb.curTst.subTest == 5)
                   {
                        SPrint("Send SHUTDOWN \n ");
                       (Void)ItLiSctTermReq(&sbAccCb.itPst,
                                            assoc_1.spId,
                                            oper.it.spAssocId,
                                            SCT_ASSOCID_SP, SHTDWN);
                       /* expected results */
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                   }
                   else if (sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1))
                   {
                      sbAccCb.curTst.evtType = ACC_EVT_TERM_CFM;
                   }
                   else
                   {
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                   }
                 break;
                 case 12: /* Test O.401.12: Execution */
                    /* Send HBEAT */
                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                    buildPar.multHBParam = TRUE;
                    buildHBeatChunk(mBuf,&buildPar, &assoc_1);
                    (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                            assoc_1.suConId, \
                                            &assoc_1.peerTAddr, \
                                            &assoc_1.localTAddr, \
                                            &hdrParm, mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                    buildPar.multHBParam = FALSE;
                 break;
                  case 13:    /* Test O.401.13: Execution */
                  switch(sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SPrint("Send HBeat Req \n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, 10,SCT_HBEAT_ENB_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                     case 2:
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 3:
                        sbStdSctSapCfg(&sbMgmt, SAP_1);
                        sbMgmt.t.cfg.s.sctSapCfg.reConfig.intervalTm  =  30;
                        sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                        sbAccCb.curTst.state--;
                        sbAccCb.curTst.evtType = ACC_EVT_CFG_CFM;
                        break;
                     case 4:
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 5:
                        SPrint("Send HBeat Req \n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, 10,SCT_HBEAT_ENB_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                     case 6:
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                    default :
                        break; 
                  }
                  break;
              }
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
               if ( (curtstnum == 3) && (sbAccCb.curTst.subTest == 4) )
               {
                  sbAccCb.curTst.subTestsPass++;
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
            {        /* strt primitive received */
            reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 1:      /* Test O.401.01: Expected Results */
                     switch (sbAccCb.curTst.subTest )
                     {
                       case 1:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA\
                                             ,SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                            &status, &reason);
                          break;
                        case 2:
                           SPrint("HBeat chunk detected \n");
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                           /*-- RFC 4460: MLK fix*/
                       case 3:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_DIS_DTA\
                                             ,SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                            &status, &reason);
                          break;
                        default:
                           break;
                     }
                     break;
                  case 2:      /* Test O.401.02: Expected Results */
                     switch ( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA,SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
                           break;
                        case 2:
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 3:
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                           /*-- RFC 4460: MLK fix*/
                       case 4:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_DIS_DTA\
                                             ,SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                            &status, &reason);
                          break;
                     }
                     break;
                  case 3:      /* Test O.401.03: Expected Results */
                     switch ( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           SPrint("HBeatCfm detected \n");
                           SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA,\
                                              SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, \
                                             &status, &reason);
                           break;
                        case 2:
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 3:
                           SPrint("HBeatCfm detected \n");
                           SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_DIS_DTA,\
                                              SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                             &status, &reason);
                           break;
                     }
                     break;
                  case 4:      /* Test O.401.04: Expected Results */
                     if ( sbAccCb.curTst.subTest == 1)
                     {
                        SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA,\
                                           SCT_CAUSE_NOT_APPL)
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                          &status, &reason);
                     }
                     else
                     {
                        if ( sbAccCb.curTst.subTest < (sbAccCb.curTst.numSubTst-1 ) )
                        {
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status );
                        }
                        else
                        {
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              buildPar.chunkId = SB_ID_HBEAT;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {   
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_NET_DOWN, 0)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND,\
                                                &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                             }
                               /* sb003.12 - Addition : Termination indication is
                                * received here because if all address are down
                                * association will be down now */
                           else if (msg->evntType == ACC_EVT_TERM_IND)
                           {
                              /* check TermInd */
                              SPrint(" Receive TermInd \n ");
                              SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_COMM_LOST,\
                                                 SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND,\
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
                        }
                     }
                     break;
/* sb012.103: Test case placed under flag LSB12 */
#ifdef LSB12
                  case 5: /* Test O.401.05: Expected results */
                     switch ( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA,SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
                           break;
                        case 2:
                           /* Check that HBEAT timer is running */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_HBEAT, RUNNING);
                           break;
                           /*-- RFC 4460: MLK fix*/
                       case 3:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_DIS_DTA\
                                             ,SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                            &status, &reason);
                          break;
                     }
                     break;
                  case 6:
                     switch ( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA,SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
                           break;
                        case 2:
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 3:
                           SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_DIS_DTA,SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
                           break;
                        case 4 :
                           /* Check that HBEAT timer is stopped */
                           mgmt.cfm.status = LCM_PRIM_OK;
                           ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_HBEAT, STOPPED);
                           break;
                     }
                     break;
#endif  /* LSB12 */
                  case 10: /* Test O.401.10: Expected results */
                     switch ( sbAccCb.curTst.subTest)
                     {
                        case 1:
                           SPrint("\nReceive HBEAT_CFM  \n ");
                           SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA,SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
                           break;
                        case 2:
                           SPrint("Receive HBEAT 1 \n ");
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {

                              /* we expect a HBEAT */
                           SPrint("Receive HBEAT 2\n ");
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              SPrint("Receive SCT_STATUS_NET_DOWN 1 \n ");
                              SB_SETUP_STA_IND(assoc_1, SCT_STATUS_NET_DOWN, 0)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND,\
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
                           if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                                ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                           break;
                        case 4:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                                 /* we expect a HBEAT */
                                 SPrint("Receive HBEAT 3\n ");
                                 buildPar.chunkId = SB_ID_HBEAT;
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if (msg->evntType == ACC_EVT_STA_IND)
                           {
                              SPrint("Receive SCT_STA_IND \n ");
                              mgmt.s.usta.event = LCM_EVENT_LYR_SPECIFIC;
                              mgmt.s.usta.cause = LSB_CAUSE_PATH_FAILURE;
                              ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_STA_IND);
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           }
                           else
                           {
                              status = INC_EVNTTYPE;
                              setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              ret = RFAILED;
                           }
                           if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                                ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) ) 
                              sbAccCb.curTst.tickLstDoneFlg = TRUE;
                           break;
                     }
                     break;
                  case 11: /* Test O.401.11: Expected results */
                        if (sbAccCb.curTst.subTest == 1)
                        {
                           SPrint("\nReceive HBEAT_CFM  \n ");
                           SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA,SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
                           break;
                        }
                        else if( (sbAccCb.curTst.subTest ==4) || (sbAccCb.curTst.subTest == 2)||( sbAccCb.curTst.subTest == 3) )
                        {
                           SPrint("\nReceive HBEAT  \n ");
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        }
                        else if(sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1))
                        {
                           SPrint("\nReceive TermCfm \n ");
                           SB_SETUP_TERM_CFM(assoc_1,SCT_NOK, SCT_CAUSE_REM_UNREACH)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status, &reason);
                        }
                        else
                        {
                           /* Check SHUTDOWN chunk */
                           printf("Receive SHUTDOWN \n");
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                        }
                     break;
                 case 12: /* O.401.12: Expected results */
                       /* Receive HBEAT */
                    SPrint("\nReceive HBEAT_ACK  \n ");
                    buildPar.chunkId = SB_ID_HBEATACK;
                    buildPar.multHBParam = TRUE;
                    ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                    break;
                 case 13:      /* Test O.401.13: Expected Results */
                     switch (sbAccCb.curTst.subTest )
                     {
                       case 1:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA\
                                             ,SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                            &status, &reason);
                          break;
                        case 2:
                           SPrint("HBeat chunk detected \n");
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 3:
                           mgmt.cfm.status = LCM_PRIM_NOK;
                           mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                           sbLsbChkCfm(&mgmt, &status, &reason,ACC_EVT_CFG_CFM);
                           break;
                      case 4:
                           SPrint("HBeat chunk detected \n");
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                       case 5:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_DTA\
                                             ,SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                            &status, &reason);
                           break;
                        case 6:
                           SPrint("HBeat chunk detected \n");
                           buildPar.chunkId = SB_ID_HBEAT;
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
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
               }  /* End Subtest successful */
            }     /* end primitive received */

            if  (sbAccCb.curTst.tickLstDoneFlg == TRUE)
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
}  /* end sbSctDatPathHBeatTst_1 */


/*
*       Fun:   sbO401_07
*
*       Desc:  Test case : O.401.07
*              Purpose   : Sending end: Verify that if the Heartbeat timer is activated
*                          on an association, a Heartbeat chunk is sent to all the addresses
*                          received from the peer in the INIT_ACK chunk.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_07
(
void
)
#else
PUBLIC  S16 sbO401_07(void)
#endif
{
   U8      curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_07)
   curtstnum = 7;
   sbAccCb.curTst.numSubTst = 4;
   sbSctDatPathHBeatTst_2(curtstnum,"O.401.07");
   RETVALUE(ROK);
} /* end sbO401_07 */


/*
*       Fun:   sbO401_08
*
*       Desc:  Test case : O.401.08
*              Purpose   : Receiving end: Verify that if the Heartbeat timer
*                          is activated on an association, the addresses
*                          received in the INIT chunk is used to send
*                          heartbeats to the peer.
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_08
(
void
)
#else
PUBLIC  S16 sbO401_08(void)
#endif
{
   U8      curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 6;
   sbSctDatPathHBeatTst_2(curtstnum,"O.401.08");
   RETVALUE(ROK);
} /* end sbO401_08 */


/*
*       Fun:   sbO401_09
*
*       Desc:  Test case : O.401.09
*              Purpose   : Verify that if the Heartbeat timer is activated
*                          on an association, the subset of the INIT chunk
*                          addresses received in the AssocRsp primitive is
*                          used to send heartbeats to the peer.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO401_09
(
void
)
#else
PUBLIC  S16 sbO401_09(void)
#endif
{
   U8      curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO401_09)
   curtstnum = 9;
   sbAccCb.curTst.numSubTst = 7;
   sbSctDatPathHBeatTst_2(curtstnum,"O.401.09");
   RETVALUE(ROK);
} /* end sbO401_09 */

/*
*       Fun:   sbSctDatPathHBeatTst_2
*
*       Desc:  Checking the heartbeat functions.
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctDatPathHBeatTst_2
(
U8   curtstnum,   /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctDatPathHBeatTst_2(curtstnum,numstr)
U8   curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   PRIVATE    SbOperQElm    oper;
   PRIVATE    SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE    SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE    SbAccAssoc    assoc_1;
   PRIVATE    SbAccAssoc    assoc_2;
   SbAccMsgQElm  *msg;
   CmIpHdrParm   hdrParm;
   Buffer        *mBuf;
   Txt           prntBuf[200];


   TRC2(sbSctDatPathHBeatTst_2)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            if ( curtstnum == 9 )
            {
               SB_TSAPCFG(SAP_2);
            }
            else
            {
               SB_TSAPCFG(SAP_1)
            }
            if ( (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE) ||
                 ( (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT1) == TRUE) &&
                   (curtstnum == 9) ) )
            {
               if ( curtstnum == 9 )
               {
                  SB_BIND_HITSAP(SUID_1, SPID_1, BIT1);
               }
               else
               {
                  SB_BIND_HITSAP(SUID_0, SPID_0, BIT0);
               }
               if ( (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE) ||
                    ( (isBitSet(sbAccCb.curTst.bTSapMask, BIT1) == TRUE) &&
                      (curtstnum == 9) ) )
               {
                  SB_DISABLE_TRACE() /* disable trace */
                  if (isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == TRUE)
                  {
                     switch(curtstnum)/* Pretests continues */
                     {
                        case 7: /* pretests: O.401.07 */
                           if(isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )  
                           {                                                               
                              sbStdSctSapCfg(&sbMgmt, SAP_1);
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin =  ACC_RTO_SHORT;
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax =  ACC_RTO_SHORT;
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial  =  ACC_RTO_SHORT;
                              sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);                
                           }                                                          
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                              {
                                 SB_EST_ASSOC(assoc_1, BIT0)
                                 if (isBitSet(sbAccCb.curTst.bAssocMask, BIT0) == TRUE)
                                 {
                                    SB_ENTERTEST( sbAccCb.curTst.bAssocMask, BIT0 )
                                 } /* end assoc est */
                              } /* end assocsetup mask */
                           }
                           break;
                        case 8: /* pretests: O.401.08 */
                           if(isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )  
                           {                                                               
                              sbStdSctSapCfg(&sbMgmt, SAP_1);
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin =  ACC_RTO_SHORT;
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax =  ACC_RTO_SHORT;
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial  =  ACC_RTO_SHORT;
                              sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);                
                           }                                                          
                           if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
                           {
                              setupAssoc(&assoc_1, ASSOC_1);
                              SB_ENTERTEST( sbAccCb.curTst.bAssocSetupMask, BIT0 )
                           }
                           break;
                        case 9: /* pretests: O.401.09*/
                           if(isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_2) == FALSE )  
                           {                                                               
                              sbStdSctSapCfg(&sbMgmt, SAP_2);
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin =  2;
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax =  2;
                              sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial  =  2;
                              sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_2);                
                           }                                                          
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
               case 7:    /* Test O.401.07: Execution */
                  switch(sbAccCb.curTst.subTest)
                  {
                     case 1:
                        SPrint("Send HBeat Req \n\n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId,\
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, \
                                                10,SCT_HBEAT_ENB_ASSOC);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                     case 2:
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                        {
                            sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                            sbAccCb.curTst.tickLstDoneFlg = FALSE;
                        }
                        break;
                           /*-- RFC 4460: MLK fix*/
                     case 3:
                        SPrint("Send HBeat Req \n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, 0,SCT_HBEAT_DIS_DTA);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                  }
                  break;
              case 8:    /* Test O.401.08: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {

                     case 1:   /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 5;
                        buildPar.inStrms = 5;
                        buildInitChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM) /* RFC 4460 -- win compilation */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;

                     case 2:    /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM) /* RFC 4460 -- win compilation */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                               assoc_1.suConId, \
                                               &assoc_1.peerTAddr, \
                                               &assoc_1.localTAddr, \
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;
                     case 3:  /* AssocRsp with assocIndParams received from SCTP */
                        if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                           ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                        {
                           SPrint("  =========SENDING AN ASSOC RESPONSE TO SCTP========\n\n");
                           oper.it.assocParams.t.cookieParams.suAssocId = assoc_1.suAssocId;

#ifdef SCT3 
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                                  assoc_1.spEndpId, \
                                                  &oper.it.assocParams, 0, \
                                                  SCT_OK, (Buffer *)NULLP);
#else
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_1.spId, \
                                                  assoc_1.spEndpId, \
                                                  &oper.it.assocParams, \
                                                  SCT_OK, (Buffer *)NULLP);
#endif
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                        }
                        break;
                      case 4:
                        sbAccCb.curTst.tickLstDoneFlg = FALSE;
                        SPrint("Send HBeat Req \n\n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_1.spId, \
                                                assoc_1.spAssocId,\
                                                &assoc_1.priPeerNAddr, \
                                                10,SCT_HBEAT_ENB_ASSOC);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;

                     case 5:
                        SPrint(" Send HBEAT_ACK  \n\n ");
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildHBeatAckChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                               &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     default:
                        break;
                  }
                  break;
              case 9:    /* Test O.401.09: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:   /* Send the INIT chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.outStrms = 4;
                        buildPar.inStrms = 5;
                        buildInitChunk(mBuf,&buildPar, &assoc_2);
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                         assoc_2.suConId = SUCONID_0;
#endif
                        SB_SETUP_IPHDR_PAR(NOFRAGM) /* RFC 4460 -- win compilation */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                               assoc_2.suConId, \
                                               &assoc_2.peerTAddr, \
                                               &assoc_2.localTAddr, \
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_ASSOC_IND; /* expected response */
                        break;
                     case 2:
                        SPrint("  =========SENDING AN ASSOC RESPONSE TO SCTP========\n\n");
                         oper.it.assocParams.t.initParams.peerAddrLst.nmb = 1;
                         oper.it.assocParams.t.initParams.peerAddrLst.nAddr[0].type = \
                            CM_TPTADDR_IPV4;
                         oper.it.assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = \
                                                            assoc_2.priPeerNAddr.u.ipv4NetAddr;
#ifdef SCT3 
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, 0, \
                                               SCT_OK, (Buffer *)NULLP);
#else
                        (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                               assoc_2.spEndpId, \
                                               &oper.it.assocParams, \
                                               SCT_OK, (Buffer *)NULLP);
#endif
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /* expected response */
                        break;
                     case 3:    /* Send the COOKIE chunk */
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildCookieChunk(mBuf,&buildPar, &assoc_2);
                        SB_SETUP_IPHDR_PAR(NOFRAGM) /* RFC 4460 -- win compilation */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_1, \
                                               assoc_2.suConId, \
                                               &assoc_2.peerTAddr, \
                                               &assoc_2.localTAddr, \
                                               &hdrParm, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                        break;
                     case 4:
                        if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                           ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                        {
                           SPrint("  =========SENDING AN ASSOC RESPONSE TO SCTP========\n\n");
                           oper.it.assocParams.t.cookieParams.suAssocId = assoc_2.suAssocId;
                           SB_CPY_NADDRLST(&(oper.it.assocParams.t.initParams.peerAddrLst),\
                                           &(assoc_2.peerNAddrLst));
                           oper.it.assocParams.t.initParams.peerAddrLst.nmb = 1;
                           oper.it.assocParams.t.initParams.peerAddrLst.nAddr[0].type =\
                                                                     CM_TPTADDR_IPV4;
                           oper.it.assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = \
                                                            assoc_2.priPeerNAddr.u.ipv4NetAddr;

#ifdef SCT3 
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                                  assoc_2.spEndpId, \
                                                  &oper.it.assocParams,0, \
                                                  SCT_OK, (Buffer *)NULLP);
#else
                           (void) ItLiSctAssocRsp(&sbAccCb.itPst, assoc_2.spId, \
                                                  assoc_2.spEndpId, \
                                                  &oper.it.assocParams, \
                                                  SCT_OK, (Buffer *)NULLP);
#endif
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                        }
                        break;
                     case 5:
                        SPrint("Send HBeat Req \n ");
                        (void)  ItLiSctHBeatReq(&sbAccCb.itPst, assoc_2.spId, assoc_2.spAssocId,\
                                                &assoc_2.priPeerNAddr, 10,SCT_HBEAT_ENB_ASSOC);
                        sbAccCb.curTst.evtType = ACC_EVT_HBEAT_CFM;
                        break;
                     case 6:
                        if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                        {
                            sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                            sbAccCb.curTst.tickLstDoneFlg = FALSE;
                        }
                     default:
                        break;
                  }
                 break;
              }
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
               if ( (curtstnum == 3) && (sbAccCb.curTst.subTest == 4) )
               {
                  sbAccCb.curTst.subTestsPass++;
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
            {        /* strt primitive received */
            reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 7:      /* Test O.401.07: Expected Results */
                     switch (sbAccCb.curTst.subTest )
                     {
                       case 1:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_ASSOC,\
                                             SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                            &status, &reason);
                          break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if ( (msg->evntType == ACC_EVT_UDAT_REQ) )
                           {
                              SPrint("HBeat chunk detected \n");
                              buildPar.chunkId = SB_ID_HBEAT;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                              sprintf(prntBuf,"Expected address 1 = %d\n",
                                      assoc_1.priPeerNAddr.u.ipv4NetAddr);
#else
                              sprintf(prntBuf,"Expected address 1 = %ld\n",
                                      assoc_1.priPeerNAddr.u.ipv4NetAddr);
#endif                              
                              SPrint(prntBuf);
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                              sprintf(prntBuf,"Expected address 2 = %d\n",
                                      peerNAddrLst_1[3]);
#else
                              sprintf(prntBuf,"Expected address 2 = %ld\n",
                                      peerNAddrLst_1[3]);
#endif                              
                              SPrint(prntBuf);
                              if ( (oper.hi.peerTAddr.u.ipv4TptAddr.address ==\
                                  assoc_1.priPeerNAddr.u.ipv4NetAddr)  &&
                                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                              {
                          
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              }
                              else if ( (oper.hi.peerTAddr.u.ipv4TptAddr.address ==\
                                   peerNAddrLst_1[3]) &&
                                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                              {
                                   setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               
                              }
                              else
                              {
                                 status = INC_ADDR;
                                 ret = RFAILED;
                              }
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
                           /*-- RFC 4460: MLK fix*/
                       case 3:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_DIS_DTA\
                                             ,SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM,\
                                            &status, &reason);
                          break;
                        default:
                           break;
                     }
                     break;
                  case 8:      /* Test O.401.08: Expected Results */
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
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND,\
                                             &status, &reason);
                           break;
                        case 3:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* we expect a COOKIE ACK */
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status   );
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
                           if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                              ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)  )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                           break;
                        case 4:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                             /* RFC 4460 -- expect path probing HBEAT */
                             SPrint("got HBEAT \n");
                              buildPar.chunkId = SB_ID_HBEAT;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
                           else if( msg->evntType == ACC_EVT_HBEAT_CFM ) 
                           {
                             SPrint("got HBEAT CFM \n");
                              SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_ASSOC,\
                                             SCT_CAUSE_NOT_APPL)
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
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
                        case 5:
                          sbAccPeekMsg(&msg); 
                           if ( (msg->evntType == ACC_EVT_UDAT_REQ) )
                           {
                              SPrint("HBeat chunk detected \n");
                              buildPar.chunkId = SB_ID_HBEAT;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                              sprintf(prntBuf,"Expected address 1 = %d\n",
                                      assoc_1.priPeerNAddr.u.ipv4NetAddr);
#else
                              sprintf(prntBuf,"Expected address 1 = %ld\n",
                                      assoc_1.priPeerNAddr.u.ipv4NetAddr);
#endif
                              SPrint(prntBuf);
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                              sprintf(prntBuf,"Expected address 2 = %d\n",
                                      peerNAddrLst_1[3]);
#else
                              sprintf(prntBuf,"Expected address 2 = %ld\n",
                                      peerNAddrLst_1[3]);
#endif                                                            
                              SPrint(prntBuf);
                              if ( (oper.hi.peerTAddr.u.ipv4TptAddr.address ==\
                                  assoc_1.priPeerNAddr.u.ipv4NetAddr)  &&
                                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                              {
                          
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              } else if ( (oper.hi.peerTAddr.u.ipv4TptAddr.address ==\
                                   peerNAddrLst_1[3]) &&
                                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                              {
                                   setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               
                              }
                              else
                              {
                                 status = INC_ADDR;
                                 ret = RFAILED;
                              }
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
                        default:
                           break;
                     }
                     break;
                  case 9:      /* Test O.401.09: Expected Results */
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
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_IND,\
                                             &status, &reason);
                           break;
                        case 4:
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              /* Check COOKIE_ACK chunk */
                              oper.hi.spId = SPID_1;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_COOKIEACK)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_2, &status   );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
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
                           if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                              ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)  )
                              sbAccCb.curTst.tickLstDoneFlg = TRUE;
                           break;
                       case 5:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_2, SCT_OK, SCT_HBEAT_ENB_ASSOC,\
                                             SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
                          break;
                        case 6:
                           sbAccPeekMsg(&msg);
                           if ( (msg->evntType == ACC_EVT_UDAT_REQ) &&
                                ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                           {
                              SPrint("HBeat chunk detected \n");
                              buildPar.chunkId = SB_ID_HBEAT;
                              oper.hi.spId = SPID_1;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_2, &status );
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                              sprintf(prntBuf,"Expected address = %d\n",
                                      assoc_2.priPeerNAddr.u.ipv4NetAddr); 
#else
                              sprintf(prntBuf,"Expected address = %ld\n",
                                      assoc_2.priPeerNAddr.u.ipv4NetAddr); 
#endif                              
                              SPrint(prntBuf);
                              if ( (oper.hi.peerTAddr.u.ipv4TptAddr.address !=\
                                  assoc_2.priPeerNAddr.u.ipv4NetAddr) )
                              {
                                 status = INC_ADDR;
                                 ret = RFAILED;
                              }
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           } else if ( (msg->evntType == ACC_EVT_UDAT_REQ) &&
                                       ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) )
                           {
                              SPrint("HBeat chunk detected \n");
                              buildPar.chunkId = SB_ID_HBEAT;
                              oper.hi.spId = SPID_1;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_2, &status );
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                              sprintf(prntBuf,"Expected address 1 = %d\n",
                                      assoc_2.priPeerNAddr.u.ipv4NetAddr);  
#else
                              sprintf(prntBuf,"Expected address 1 = %ld\n",
                                      assoc_2.priPeerNAddr.u.ipv4NetAddr);  
#endif
                              SPrint(prntBuf);
                              if ( (oper.hi.peerTAddr.u.ipv4TptAddr.address !=\
                                  assoc_2.priPeerNAddr.u.ipv4NetAddr) )
                              {
                                 status = INC_ADDR;
                                 ret = RFAILED;
                              }
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
                        default:
                           break;
                     }
                     break;
                  case 10:      /* Test O.401.10: Expected Results */
                     switch (sbAccCb.curTst.subTest )
                     {
                       case 1:
                          SPrint("HBeatCfm detected \n");
                          SB_SETUP_HBEAT_CFM(assoc_1, SCT_OK, SCT_HBEAT_ENB_ASSOC,\
                                             SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_HBEAT_CFM, &status, &reason);
                          break;
                        case 2:
                           sbAccPeekMsg(&msg);
                           if ( (msg->evntType == ACC_EVT_UDAT_REQ) )
                           {
                              SPrint("HBeat chunk detected \n");
                              buildPar.chunkId = SB_ID_HBEAT;
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar\
                                                    , &assoc_1, &status );
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                              sprintf(prntBuf,"Expected address 1 = %d\n",
                                      assoc_1.priPeerNAddr.u.ipv4NetAddr);         
#else
                              sprintf(prntBuf,"Expected address 1 = %ld\n",
                                      assoc_1.priPeerNAddr.u.ipv4NetAddr);         
#endif
                              SPrint(prntBuf);
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                              sprintf(prntBuf,"Expected address 2 = %d\n",
                                      peerNAddrLst_1[3]);                          
#else
                              sprintf(prntBuf,"Expected address 2 = %ld\n",
                                      peerNAddrLst_1[3]);                          
#endif
                              SPrint(prntBuf);
                              if ( (oper.hi.peerTAddr.u.ipv4TptAddr.address ==\
                                  assoc_1.priPeerNAddr.u.ipv4NetAddr)  &&
                                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                              {
                          
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
                              } else if ( (oper.hi.peerTAddr.u.ipv4TptAddr.address ==\
                                   peerNAddrLst_1[3]) &&
                                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                              {
                                   setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               
                              }
                              else
                              {
                                 status = INC_ADDR;
                                 ret = RFAILED;
                              }
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
               }  /* End Subtest successful */
            }     /* end primitive received */

            if  (sbAccCb.curTst.tickLstDoneFlg == TRUE)
            {
              sbAccCb.curTst.state++;
               sbAccCb.curTst.subTest++;
                sbAccCb.curTst.bTickMask = 0;
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
      doCleanup();
   RETVALUE(ROK);
}  /* end sbSctDatPathHBeatTst_2 */

/* Fail over */

/*
*       Fun:   sbO402_01
*
*       Desc:  Test case : O.402.01
*              Purpose   : Verify that when the service user explicitly requests to send data to an
*                          inactive address, the SCTP should first try to send data to an alternative
*                          address before reporting the error.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO402_01
(
void
)
#else
PUBLIC  S16 sbO402_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO402_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 2;
   sbSctDatPathFailoverTst(curtstnum,"O.402.01");
   RETVALUE(ROK);
} /* end sbO402_01 */

               /* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbO402_02
*
*       Desc:  Test case : O.402.02
*              Purpose   : Verify that when the service user explicitly requests to send data to an
*                          inactive address, the SCTP should first try to send data to an alternative
*                          address before reporting the error for IPV6 address.
*
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act5.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO402_02
(
void
)
#else
PUBLIC  S16 sbO402_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO402_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctDatPathFailoverTst(curtstnum,"O.402.02");
   RETVALUE(ROK);
} /* end sbO402_02 */

/*
*       Fun:   sbSctDatPathFailoverTst
*
*       Desc:  Checking the heartbeat functions.
*       Ret:   ROK
*
*       Group: Data path
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbSctDatPathFailoverTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE  S16 sbSctDatPathFailoverTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   PRIVATE    SbOperQElm    oper;
   PRIVATE    SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE    SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE    SbAccAssoc    assoc_1;
   SbAccMsgQElm  *msg;
   /* sb058.102 : Deleted to remove compilation warning */
   Buffer        *mBuf;
   /* sb032.102 :  IPV6 Support Added */
   Bool         ipv6Ret;
   U8           ipv6Addr[16];
/*   Txt           prntBuf[64]; */


   TRC2(sbSctDatPathFailoverTst)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      SB_GENCFG()
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff) 
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            if(isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )  
            {                                                               
               sbStdSctSapCfg(&sbMgmt, SAP_1);
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin =  ACC_RTO_SHORT;
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax =  ACC_RTO_SHORT;
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial  =  ACC_RTO_SHORT;
               sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);                
            }                                                          
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
      } /* end ConfigMask if */  
   }  /* end pretests */   

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
       case 0:
            SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other parameters for data transmission */
            switch(curtstnum)
               {    /* Start switch(curtstnum) #1 */
               case 1:    /* Test O.402.01: Execution */
                   /*-- RFC 4460 -- MLK Fix*/
                   SB_RLSMEM(mBuf);
                  if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                       ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                  {
                   /*-- RFC 4460 -- MLK Fix*/
                   SB_SETUP_DAT_REQ(mBuf)
                     (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                          &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                          ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                     sbAccCb.curTst.tickLstDoneFlg = FALSE;
                     sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                 }
                 break;
               /* sb032.102 :  IPV6 Support Added */
               case 2:    /* Test O.402.02: Execution */
                  if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                       ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                  {
                     (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                          &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                          ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                     sbAccCb.curTst.tickLstDoneFlg = FALSE;
                     sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                 }
                 break;
               }
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
            {        /* strt primitive received */
            reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 1:      /* Test O.402.01: Expected Results */
                     sbAccPeekMsg(&msg);
                     if( (msg->evntType == ACC_EVT_UDAT_REQ) &&
                         ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                     {
                        SPrint (" Received UDAT_REQ 1 \n");
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status );
                        if (oper.hi.peerTAddr.u.ipv4TptAddr.address !=\
                               assoc_1.priPeerNAddr.u.ipv4NetAddr)
                        {
                              status = INC_ADDR;
                              ret = RFAILED;
                        }
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if ( (msg->evntType == ACC_EVT_UDAT_REQ)&&
                                ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                     {
                        SPrint ("Received UDAT_REQ 2 \n");
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status );
                        if (oper.hi.peerTAddr.u.ipv4TptAddr.address !=  peerNAddrLst_1[3])
                        {
                              status = INC_ADDR;
                              ret = RFAILED;
                        }
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
                  /* sb032.102 :  IPV6 Support Added */
                  case 2:      /* Test O.402.02: Expected Results */
                     sbAccPeekMsg(&msg);
                     if( (msg->evntType == ACC_EVT_UDAT_REQ) &&
                         ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                     {
                        SPrint (" Received UDAT_REQ 1 \n");
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status );
                        SB_INET6_SAMEADDR(oper.hi.peerTAddr.u.ipv6TptAddr.ipv6NetAddr, assoc_1.priPeerNAddr.u.ipv6NetAddr, &ipv6Ret)
                        /*if (oper.hi.peerTAddr.u.ipv4TptAddr.address !=\
                               assoc_1.priPeerNAddr.u.ipv4NetAddr)*/
                        if(ipv6Ret == FALSE)
                        {
                              status = INC_ADDR;
                              ret = RFAILED;
                        }
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if ( (msg->evntType == ACC_EVT_UDAT_REQ)&&
                                ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                     {
                        SPrint ("Received UDAT_REQ 2 \n");
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status );
                        CPY_ACC_ASSOC1_PEER_IPV6(ipv6Addr, 3)
                        SB_INET6_SAMEADDR(oper.hi.peerTAddr.u.ipv6TptAddr.ipv6NetAddr, ipv6Addr, &ipv6Ret)
                        /*if (oper.hi.peerTAddr.u.ipv4TptAddr.address !=  peerNAddrLst_1[3])*/
                        if(ipv6Ret == FALSE)
                        {
                              status = INC_ADDR;
                              ret = RFAILED;
                        }
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
               }  /* End Subtest successful */
            }     /* end primitive received */

            if  (sbAccCb.curTst.tickLstDoneFlg == TRUE)
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
}  /* end sbSctDatPathFailoverTst */


/********************************************************************30**

         End of file:     sb_act5.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:08 2015

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
           sb003.12   sb   1. Modification in acceptance test 401-04 
                              because of patch sb002.12.
           sb042.102  hl   1. Added change for SHT interface and Rolling
                              UpGrade
           sb058.102  pr   1. Removed compilation warning. 
           sb060.102  pr   1. TOS changes. 
/main/4      ---   rsr/ag  1. Updated for Release of 1.3
	   sb008.103  nuX  1. Initializing hdrParam strucure to zero.
           sb009.103  nuX  1. Changes made for SOL10 upgrade , and the change 
                              is made under SB_SOL10_MULTIPORT flag.
           sb012.103  pkaX 1. Timer related test cases placed under flag LSB12.
/main/4    sb021.103  krkX 1. Added testcase for hBeat timer.
/main/4    sb033.103  sdey 1. Modified code base to remove warning for 64 bit i
                              compilation.
 *********************************************************************91*/
