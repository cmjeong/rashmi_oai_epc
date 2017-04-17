

/********************************************************************20**

     Name:     sb_act4.c - Acceptance Tests for the SCTP layer

     Type:     C source file

     Desc:     C code for acceptance tests test cases.  Includes all the data transfer
               tests.

     File:     sb_act4.c

     Sid:      sb_act4.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:07 2015

     Prg:      nct

*********************************************************************21*/

/*

  sb_act4.c - Acceptance Tests for the SCTP layer

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
PRIVATE  S16 sbDatTfTst_1     ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbDatTfTst_2     ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbDatTfTmrTst    ARGS((U8 curtstnum, S8 *numstr ));
PRIVATE  S16 sbDatTfSeqDel    ARGS((U8 curtstnum, S8 *numstr ));
PRIVATE  S16 sbDatTfSack_1    ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbDatTfSack_2    ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbDatTfCCntrl    ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbDatTfMuxTst    ARGS((U8 curtstnum, S8 *numstr));
PRIVATE  S16 sbDatTfSegTst    ARGS((U8 curtstnum, S8 *numstr));
/* SATELLITE SCTP feature */ 
/* sb003.103 - addition - */
#ifdef SB_ECN
PRIVATE  S16 sbDatTfECNCntrl    ARGS((U8 curtstnum, S8 *numstr));
#endif /* SB_ECN */

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */


/* 300 series:  */

/*
*       Fun:   sbO300_01
*
*       Desc:  Test case : O.300.01
*              Purpose   : Verify that data transfer is unsuccessful when the spAssocId
*                          is invalid.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_01
(
void
)
#else
PUBLIC  S16 sbO300_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfTst_1(curtstnum,"O.300.01");
   RETVALUE(ROK);
} /* end sbO300_01 */

/*
*       Fun:   sbO300_02
*
*       Desc:  Test case : O.300.02
*              Purpose   : Verify that data transfer is unsuccessful when the spId
*                          is invalid.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_02
(
void
)
#else
PUBLIC  S16 sbO300_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C..02.curtstnum */

   TRC2(sbO300_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfTst_1(curtstnum,"O.300.02");
   RETVALUE(ROK);
} /* end sbO300_02 */

/*
*       Fun:   sbO300_03
*
*       Desc:  Test case : O.300.03
*              Purpose   : Verify that data transfer is unsuccessful when the SAP state is unbound.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_03
(
void
)
#else
PUBLIC  S16 sbO300_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_03)
   curtstnum = 3;
    sbAccCb.curTst.numSubTst = 2;
   sbDatTfTst_1(curtstnum,"O.300.03");
   RETVALUE(ROK);
} /* end sbO300_03 */

/*
*       Fun:   sbO300_04
*
*       Desc:  Test case : O.300.04
*              Purpose   : Verify that the datagram retrieval informative can be successfully obtained
*              from the SCTP layer.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_04
(
void
)
#else
PUBLIC  S16 sbO300_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfTst_1(curtstnum,"O.300.04");
   RETVALUE(ROK);
} /* end sbO300_04 */


/*
*       Fun:   sbDatTfTst_1
*
*       Desc:  General data transfer tests (#1).
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbDatTfTst_1
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PUBLIC  S16 sbDatTfTst_1(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   PRIVATE       SbOperQElm    oper;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE       SbAccChunkBld buildPar;            /* Parameters used for checking chunks */
   PRIVATE       SbAccAssoc    assoc_1;
   Buffer        *mBuf;

   TRC2(sbDatTfTst_1)
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
               SB_SCTSAPCFG(SAP_2)
               if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT1) == TRUE)
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
               } /* end SctSapCfgMask, bit 1, if */
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
              case 1:    /* Test O.300.01: Execution */
                  SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other parameters
                                           for data transmission */
                 (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, SPASSOCID_2, \
                                      &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                      ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                 sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                 break;
              case 2:     /* Test O.300.02: Execution */
                 SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other parameters
                                          for data transmission */
                 (void) ItLiSctDatReq(&sbAccCb.itPst, SPID_2, assoc_1.spAssocId,\
                                      &assoc_1.priPeerNAddr,
                 ACC_STREAMID, ORDER, NOBUNDLE, ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                 sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                 break;
              case 3:      /* Test O.300.03: Execution */
                  SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other parameters for data transmission */
                 (void) ItLiSctDatReq(&sbAccCb.itPst, SPID_1, assoc_1.spAssocId, &assoc_1.priPeerNAddr,
                  ACC_STREAMID, ORDER, NOBUNDLE, ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                 sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                 break;
              case 4:     /* Test O.300.04: Execution */
                  switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* Send the datagram */
                       SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other
                                                parameters for data transmission */
                       buildPar.noBundleFlg = NOBUNDLE;
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, \
                                            buildPar.noBundleFlg, \
                                            ACC_NO_LIFETM_LIM,\
                                            ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:  /* Send the status request to obtain number of
                                unacknowledged datagrams */
                       (void) ItLiSctStaReq(&sbAccCb.itPst, assoc_1.spId, \
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,SCT_GET_RTRV_INFO);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;  /* reply event expected */
                       break;
                    default:
                       break;
                   }
              break;
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
				switch(curtstnum)
				{    /* Start switch(curtstnum) #2 */
					case 1:    /* Test O.300.01: Expected Results */
						oper.it.suId = assoc_1.suId;
						oper.it.suAssocId = 0;
						oper.it.spAssocId = SPASSOCID_2;
						oper.it.status = SCT_STATUS_SND_FAIL;
                  /* sb031.103: Modified the test case expected cause.*/
						oper.it.cause = SCT_CAUSE_NO_ASSOC; 
						/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7                     
						oper.it.protId = ACC_PROT_ID;
#endif
						ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
						break;
					case 2:    /* Test O.300.02: Expected Results */
						mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
						mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
						ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_STA_IND);
						break;
					case 3:      /* Test O.300.03: Expected Results */
						mgmt.s.usta.category = LCM_CATEGORY_INTERFACE;
						mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
						mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
						ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_STA_IND);
						break;
					case 4:   /* Test O.300.04: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                       case 1:
                          /* Check DATA chunk */
                          oper.hi.spId = SPID_0;
                          SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                          ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                          break;
                       case 2:
                          /* Check status */
                          SB_SETUP_STA_CFM(assoc_1, SCT_GET_RTRV_INFO, SCT_OK, SCT_CAUSE_NOT_APPL)
                          ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_CFM, &status, &reason);
                          if (oper.it.staInfo.u.rtrvInfo.nmbUnackDgms != 1)
                          {
                             status = INC_RTRVINFO;
                             ret = RFAILED;
                          }
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
}  /* end sbDatTfTst_1 */

/*
*       Fun:   sbO300_05
*
*       Desc:  Test case : O.300.05
*              Purpose   : Verify than an indicator is received in the event of an incoming datagram from the peer.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_05
(
void
)
#else
PUBLIC  S16 sbO300_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_05)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfTst_2(curtstnum,"O.300.05");
   RETVALUE(ROK);
} /* end sbO300_05 */

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbO300_09
*
*       Desc:  Test case : O.300.09
*              Purpose   : Verify than an indicator is received in the event of an incoming datagram from the peer of IPV6 address.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_09
(
void
)
#else
PUBLIC  S16 sbO300_09(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_09)
   curtstnum = 9;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbDatTfTst_2(curtstnum,"O.300.09");
   RETVALUE(ROK);
} /* end sbO300_09 */
/*
*       Fun:   sbO300_06
*
*       Desc:  Test case : O.300.06
*              Purpose   : Verify that the user datagram can not be sent to
*                          the peer during shutdown procedure.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_06
(
void
)
#else
PUBLIC  S16 sbO300_06(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_06)
   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfTst_2(curtstnum,"O.300.06");
   RETVALUE(ROK);
} /* end sbO300_06 */

/*
*       Fun:   sbO300_07
*
*       Desc:  Test case : O.300.07
*              Purpose   : Verify that an error is generated when data is received on a
*                          non-existent stream.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_07
(
void
)
#else
PUBLIC  S16 sbO300_07(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_07)
   curtstnum = 7;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfTst_2(curtstnum,"O.300.07");
   RETVALUE(ROK);
} /* end sbO300_07 */

/*
*       Fun:   sbO300_08
*
*       Desc:  Test case : O.300.08
*              Purpose   : Verify that "Out of the blue" packets is dealt with successfully.
*                          a) If the datagram includes an abort chunk it should be ignored.
*                          b) Otherwise, the SCTP should respond the sender of the packet
*                             with a abort.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_08
(
void
)
#else
PUBLIC  S16 sbO300_08(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfTst_2(curtstnum,"O.300.08");
   RETVALUE(ROK);
} /* end sbO300_08 */

/* RFC 4460 -- SB_ETSI_2 */

/*
*       Fun:   sbO300_10
*
*       Desc:  Test case : O.300.10
*              Purpose   : Verify that "Out of the blue" packets is dealt with successfully.
*                          a) If the datagram includes an abort chunk it should be ignored.
*                          b) Otherwise, the SCTP should respond the sender of the packet
*                             with a abort.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO300_10
(
void
)
#else
PUBLIC  S16 sbO300_10(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO300_10)
   curtstnum = 10;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfTst_2(curtstnum,"O.300.10");
   RETVALUE(ROK);
} /* end sbO300_10 */


/*
*       Fun:   sbDatTfTst_2
*
*       Desc:  General data transfer tests (#2 ).
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDatTfTst_2
(
U8   curtstnum,    /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDatTfTst_2(curtstnum,numstr)
U8   curtstnum;      /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   U8            tsn;
   S16           ret;
   CmIpHdrParm   hdrParm;
   Buffer        *mBuf;
   PRIVATE       SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbOperQElm    oper;
   CmTptAddr     blueAddr;
   SbAccMsgQElm  *msg;
   /* RFC 4460: MLK Fix*/
   U8            ID;

   TRC2(sbDatTfTst_2)
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
#ifdef SB_ETSI /* RFC 4460 -- RTR */
            if (curtstnum == 10)
            {
                if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
                {
                   sbStdSctSapCfg(&sbMgmt, SAP_1);
                   sbMgmt.t.cfg.s.sctSapCfg.reConfig.maxDataSize = 40;
                   sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
                }
            }
            else
#endif /* SB_ETSI */
            {
               SB_SCTSAPCFG(SAP_1)
            }

            /* SB_SCTSAPCFG(SAP_1) */
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
               case 5:    /* Test O.300.05: Execution */
                  if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                      (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                  {
                     SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                     tsn = (ACC_INIT_TSN);
                     SB_SETUP_IPHDR_PAR(NOFRAGM)
                     SB_SETUP_UNORDERED_DATA(tsn)
                     buildDataChunk(mBuf,&buildPar,&assoc_1);
                     /* sb032.102 :  IPV6 Support Added */
                     (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,
                             &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                             &assoc_1.localIf,
#endif
                             mBuf );
                     sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                     sbAccCb.curTst.tickLstDoneFlg = FALSE;
                  }
                  break;
               case 6:     /* Test O.300.06: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:  /* Send a TermReq with AbrtFlg = False */
                        (void)  ItLiSctTermReq(&sbAccCb.itPst, assoc_1.spId,
                              assoc_1.spAssocId, SCT_ASSOCID_SP, SHTDWN);
                        sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                        break;
                     case 2:   /* Send the datagram */
                        SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters for data\
                                                  transmission */
                        (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                             &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                             ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;
                     default:
                        break;
                  }
                  break;
              case 7:   /* Test O.300.07: Execution */
                /* RFC 4460: MLK fix */
                if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                   {
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                 SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                 buildPar.streamId = 20;
                 buildPar.tsn = ACC_INIT_TSN;
                 buildPar.seqNr = 0;
                 buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                 buildDataChunk(mBuf,&buildPar,&assoc_1);
                  SB_SETUP_IPHDR_PAR(NOFRAGM)
                 /* sb032.102 :  IPV6 Support Added */
                 (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                        &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                        &assoc_1.localIf,
#endif
                                        mBuf);
                   sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                   }
                 break;
               case 8: /* O.300.08 */
                 SB_SETUP_CMTPTADDR(blueAddr,peerNAddrLst_2[2], PEERPORT_1)
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:
                       SPrint("\n Send abort \n\n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildPar.chunkId = SB_ID_ABORT;
                       buildPar.causeCode = SB_CHUNK_ERROR_STALE;
                       buildAbortErrChunk(mBuf, &buildPar, &assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, \
                                              assoc_1.suConId, \
                                              &blueAddr, \
                                              &assoc_1.localTAddr, \
                                              &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_NO_RESP;
                       break;
                    case 2:   /* Send the datagram */
                        SPrint("\n Send datagram\n ");
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.streamId = 20;
                        buildPar.tsn = ACC_INIT_TSN;
                        buildPar.seqNr = 0;
                        buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                        buildDataChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                               &blueAddr, &assoc_1.localTAddr,\
                                              &hdrParm, 
#ifdef LOCAL_INTF
                                               &assoc_1.localIf,
#endif
                                               mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;
                     default:
                        break;
                  }
                  break;
                       /* sb032.102 :  IPV6 Support Added */
               case 9:    /* Test O.300.09: Execution */
                  if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                      (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                  {
                     SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                     tsn = (ACC_INIT_TSN);
                     SB_SETUP_IPHDR_PAR(NOFRAGM)
                     SB_SETUP_UNORDERED_DATA(tsn)
                     buildDataChunk(mBuf,&buildPar,&assoc_1);
                       /* sb032.102 :  IPV6 Support Added */
                     (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,
                             &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                             &assoc_1.localIf,
#endif
                             mBuf );
                     sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                     sbAccCb.curTst.tickLstDoneFlg = FALSE;
                  }
                  break;
              case 10:   /* Test O.300.10: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters for data\
                                              transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                         &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                         ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       break;
                    case 2: /* RFC 4460 -- RTR */
                       if (sbAccCb.curTst.tickLstDoneFlg == FALSE )
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.streamId = 1;
                          buildPar.tsn = ACC_INIT_TSN;
                          buildPar.seqNr = 0;
                          buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                          buildDataChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                          /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                           &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                        &assoc_1.localIf,
#endif
                                           mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                       }
                       break;
                  } 
               break; 
              } /* end curtstnum switch */
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
               if(( (sbAccCb.curTst.subTest == 1) && (curtstnum == 8 ) ) ||
                  ( (curtstnum == 10 ) && (sbAccCb.curTst.subTest == 2) ))
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
            {
               reason = 0;
               switch(curtstnum)
               {    /* Start switch(curtstnum) #2 */
                  case 5:  /* Test O.300.05: Expected Results */
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_DAT_IND)
                     {
                        SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if (msg->evntType == ACC_EVT_UDAT_REQ)
                     {
                        SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN))
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
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
				  case 6:   /* Test O.300.06: Expected Results */
					 switch( sbAccCb.curTst.subTest)
					 {
						 case 1:
							 /* Check DATA chunk */
							 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
								 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
							 break;
						 case 2:  /* Check status indication */
							 SB_SETUP_STA_IND(assoc_1, SCT_STATUS_SND_FAIL, SCT_CAUSE_SHUTDOWN_PRGS)
						     /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
						     oper.it.protId = ACC_PROT_ID;
#endif
							 ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
							 break;
						 default:
							 break;
					 }
					 break;
				  case 7:  /* Test O.300.07: Expected Results */
                     /*-- RFC 4460 : MLK fix*/
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_UDAT_REQ)
                     {
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if (ID == SB_ID_SACK )
                              {
                                 SPrint("Received SACK  \n ");
                                 SB_RLSMEM(msg->t.sbMsg.hi.mBuf);
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              else if ( ID == SB_ID_ERROR)
                              {
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_STREAM, 0, FALSE, SB_ID_ERROR)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
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
                     if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                         sbAccCb.curTst.tickLstDoneFlg = TRUE;
                     break;
                  case 8:   /* Test O.300.08: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 2:
                           /* Check DATA chunk */
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_RES, 0, FALSE, SB_ID_ABORT)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                           break;
                        default:
                           break;
                     }
                     break;
                       /* sb032.102 :  IPV6 Support Added */
                  case 9:  /* Test O.300.09: Expected Results */
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_DAT_IND)
                     {
                        SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if (msg->evntType == ACC_EVT_UDAT_REQ)
                     {
                        SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN))
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
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
                  case 10:  /* Test O.300.10: Expected Results */
                    switch(sbAccCb.curTst.subTest)
                    {
                       case 1:
                         printf("\nreceived SCT_STATUS_SND_FAIL\n\n");
                         SB_SETUP_STA_IND(assoc_1, SCT_STATUS_SND_FAIL, SCT_CAUSE_UNKNOWN)
                         ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, &status, &reason);
                         break;
                       case 2: /* RFC 4460 -- RTR */
                        sbAccPeekMsg(&msg);
                        if ((msg->evntType == ACC_EVT_UDAT_REQ) )
                        {
                           SPrint(" Receive ABORT \n ");
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_RES, 0, FALSE, SB_ID_ABORT) 
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status  );
                           setBit(&sbAccCb.curTst.bTickMask, BIT1);
                        }
                        else if (msg->evntType == ACC_EVT_TERM_IND)
                        {
                           /* check TermInd */
                           SPrint(" Receive TermInd \n ");
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_INV,\
                                             SCT_CAUSE_OUTRES)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND,\
                                             &status, &reason);
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        }
                        else
                        {
                           status = INC_EVNTTYPE;
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           ret = RFAILED;
                        }
                        if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                              ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)  )
                              sbAccCb.curTst.tickLstDoneFlg = TRUE;
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
               else  /* Subtest successful */
               {
                  sbAccCb.curTst.subTestsPass++;

               }      /*End Subtest successful */
            } /*primitive received */
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
}  /* end sbDatTfTst_2 */



/* Segmentation */
/*
*       Fun:   sbO301_01
*
*       Desc:  Test case : O.301.01
*              Purpose   : Verify that a message is divided into segments before transmission
*                          if its size >MTU.
*
*       Ret:   ROK
*
*       Group: Segmentation
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO301_01
(
void
)
#else
PUBLIC  S16 sbO301_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO301_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfSegTst(curtstnum,"O.301.01");
   RETVALUE(ROK);
} /* end sbO301_01 */

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbO301_02
*
*       Desc:  Test case : O.301.02
*              Purpose   : Verify that a message is divided into segments before transmission
*                          if its size >MTU for IPV6 address.
*
*       Ret:   ROK
*
*       Group: Segmentation
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO301_02
(
void
)
#else
PUBLIC  S16 sbO301_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO301_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 3;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbDatTfSegTst(curtstnum,"O.301.02");
   RETVALUE(ROK);
} /* end sbO301_02 */

/*
*       Fun:   sbDatTfSegTst
*
*       Desc:  General data transfer tests (#1).
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDatTfSegTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDatTfSegTst(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf = NULLP; /* RFC 4460 -- RTR -- windows compilation */
   SbGenCfg      *genCfg;

   PRIVATE SbMgmt        sbMgmt;
   PRIVATE SbAccChunkBld buildPar;            /* Parameters used for checking chunks */
   PRIVATE SbAccAssoc    assoc_1;
   PRIVATE SbOperQElm    oper;

   TRC2(sbDatTfSegTst)
   ret = ROK;

  /* Pretests/Setup */
   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
      {
         sbStdGenCfg(&sbMgmt);
         genCfg = &(sbMgmt.t.cfg.s.genCfg);
         genCfg->mtuInitial = 80;
         genCfg->mtuMaxInitial = 80;
         genCfg->mtuMinInitial = 80;
         sbSendConfigReq(&sbMgmt, STSBGEN, GEN);
      }
      if (isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
         SB_ENABLE_DEBUGP(0xffffffff)
         if( isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == TRUE )
         {
            SB_SCTSAPCFG(SAP_1)
            if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
            {
               SB_SCTSAPCFG(SAP_2)
               if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT1) == TRUE)
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
               } /* end SctSapCfgMask, bit 1, if */
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
              case 1:     /* Test O.301.01: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* Send the datagram */
                       SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other parameters\
                                                for data transmission */
                       SPrint("Send the datagram \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:
                       /*-- RFC 4460: MLK Fix*/
                       SB_SETUP_DAT_REQ(mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    default:
                       break;
                   }
              break;
              /* sb032.102 :  IPV6 Support Added */
              case 2:     /* Test O.301.02: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* Send the datagram */
                       SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other parameters\
                                                for data transmission */
                       SPrint("Send the datagram \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:
                       /* sb005.103: IPV6 change*/
                       SB_SETUP_DAT_REQ(mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    default:
                       break;
                   }
              break;
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
                switch(curtstnum)
                {    /* Start switch(curtstnum) #2 */
                  case 1:   /* Test O.301.01: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                       case 1:
                          /* Check DATA chunk */
                          SPrint("Wait for UDatReq \n ");
                          oper.hi.spId = SPID_0;
                          SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                          ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                          break;
                       case 2:
                          /* Check DATA chunk */
                          oper.hi.spId = SPID_0;
                          SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                          ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                       /*-- RFC 4460: MLK Fix*/
                          SB_RLSMEM(mBuf);
                          break;
                       default:
                          break;
                     }
                     break;
                  /* sb032.102 :  IPV6 Support Added */
                  case 2:   /* Test O.301.02: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                       case 1:
                          /* Check DATA chunk */
                          SPrint("Wait for UDatReq \n ");
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
}  /* end sbDatTfSegTst */


/* Chunk multiplexing */
/*
*       Fun:   sbO302_01
*
*       Desc:  Test case : O.302.01
*              Purpose   : Verify that multiple data chunks can be successfully included in one
*                          outbound SCTP datagram (bundling).
*
*       Ret:   ROK
*
*       Group: Multiplexing/Bundling
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO302_01
(
void
)
#else
PUBLIC  S16 sbO302_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO302_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 4;
   sbDatTfMuxTst(curtstnum,"O.302.01");
   RETVALUE(ROK);
} /* end sbO302_01 */

/* sb032.102 :  IPV6 Support Added */
/* Chunk multiplexing */
/*
*       Fun:   sbO302_05
*
*       Desc:  Test case : O.302.05
*              Purpose   : Verify that multiple data chunks can be successfully included in one
*                          outbound SCTP datagram (bundling) for IPV6 address.
*
*       Ret:   ROK
*
*       Group: Multiplexing/Bundling
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO302_05
(
void
)
#else
PUBLIC  S16 sbO302_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO302_05)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 4;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbDatTfMuxTst(curtstnum,"O.302.05");
   RETVALUE(ROK);
} /* end sbO302_05 */

/*
*       Fun:   sbO302_02
*
*       Desc:  Test case : O.302.02
*              Purpose   : Verify that multiple data chunks can be successfully included
*                          in one inbound SCTP datagram..
*
*       Ret:   ROK
*
*       Group: Multiplexing/Bundling
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO302_02
(
void
)
#else
PUBLIC  S16 sbO302_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO302_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfMuxTst(curtstnum,"O.302.02");
   RETVALUE(ROK);
} /* end sbO302_02 */

/*
*       Fun:   sbO302_03
*
*       Desc:  Test case : O.302.03
*              Purpose   : Verify that bundling is unsuccessful if the
*                          nobundle flag is set.
*
*       Ret:   ROK
*
*       Group: Multiplexing/Bundling
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO302_03
(
void
)
#else
PUBLIC  S16 sbO302_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO302_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 5;
   sbDatTfMuxTst(curtstnum,"O.302.03");
   RETVALUE(ROK);
} /* end sbO302_03 */

/*
*       Fun:   sbO302_04
*
*       Desc:  Test case : O.302.04
*              Purpose   : Verify that the nobundle flag is ignored during shutdown operations.
*
*       Ret:   ROK
*
*       Group: Multiplexing/Bundling
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO302_04
(
void
)
#else
PUBLIC  S16 sbO302_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO302_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 6;
   sbDatTfMuxTst(curtstnum,"O.302.04");
   RETVALUE(ROK);
} /* end sbO302_04 */

/*
*       Fun:   sbDatTfMuxTst
*
*       Desc:  General data transfer tests (#1).
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDatTfMuxTst
(
U8   curtstnum,   /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDatTfMuxTst(curtstnum,numstr)
U8   curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf;
   Buffer        *mBuf1;
   Buffer        *mBuf3;
   Buffer        *tmpBuf;
   CmIpHdrParm   hdrParm;
   SbAccMsgQElm  *msg;
   PRIVATE       SbOperQElm    oper;
   PRIVATE       SbMgmt        sbMgmt;
   PRIVATE       SbAccChunkBld buildPar;            /* Parameters used for checking chunks */
   PRIVATE       SbAccAssoc    assoc_1;


   TRC2(sbDatTfMuxTst)

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
 /*sb033.103 : modified to pass test case O.302.05 */           
            if ( (curtstnum == 1) || (curtstnum == 5) ) /* sb030.103:  Fix for the testcase O.302.01 */
            {
               if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
               {
                  sbStdSctSapCfg(&sbMgmt, SAP_1);
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin =  ACC_RTO_SHORT;
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax =  ACC_RTO_SHORT;
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial  =  ACC_RTO_SHORT;
#ifdef LSB4
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.bundleTm = 5;
#endif /* LSB4 */
                  sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
               }
            }
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
               SB_SCTSAPCFG(SAP_2)
               if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT1) == TRUE)
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
               } /* end SctSapCfgMask, bit 1, if */
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
              case 1:    /* Test O.302.01: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       SB_SETUP_DAT_REQ(mBuf)
                          /* buildPar.noBundleFlg = BUNDLE; */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, BUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID,mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                       break;
                    case 2:
                     SB_SETUP_DAT_REQ(mBuf1)
                          /* buildPar.noBundleFlg = BUNDLE; */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, BUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID,mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                       break;
                    case 3:
                       SB_SETUP_BUNDLDAT_REQ(mBuf1)
                          SB_RLSMEM(mBuf1)
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                       break;
                 }
                 break;
              case 2:     /* Test O.302.02: Execution */
                 if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                      (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                 {
                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                    buildPar.tsn = ACC_INIT_TSN;
                    buildPar.chunkFlg = 6;
                     buildPar.streamId = ACC_STREAMID;
                    buildDataChunk(mBuf,&buildPar,&assoc_1);
                    SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                    (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,\
                                           assoc_1.suConId,\
                                          &assoc_1.peerTAddr,\
                                           &assoc_1.localTAddr,\
                                           &hdrParm,
#ifdef LOCAL_INTF
                                           &assoc_1.localIf,
#endif
                                           mBuf);

                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                    buildPar.tsn = (ACC_INIT_TSN + 1);
                    buildPar.chunkFlg = 5;
                     buildPar.streamId = ACC_STREAMID;
                    buildDataChunk(mBuf1,&buildPar,&assoc_1);
                       /* sb032.102 :  IPV6 Support Added */
                    (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,\
                                           assoc_1.suConId, \
                                           &assoc_1.peerTAddr,\
                                           &assoc_1.localTAddr, \
                                           &hdrParm,
#ifdef LOCAL_INTF
                                           &assoc_1.localIf,
#endif
                                           mBuf1);
                    sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                    SB_SETUP_BUNDLDAT_REQ(mBuf1)
                    SB_RLSMEM(mBuf1)
                    sbAccCb.curTst.tickLstDoneFlg = FALSE;
                 }
                 break;
              case 3:      /* Test O.302.03: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send datareq */
                       SB_SETUP_DAT_REQ(mBuf)
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID\
                                            , ORDER, BUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;/* reply event expected */
                       break;
                    case 2:   /* send SACK chunk  to change arwnd */
                       buildPar.arwnd = 10;
                       buildPar.numFrag = 0;
                       buildPar.cumTsn = buildPar.tsn;
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                              &assoc_1.peerTAddr,\
                                              &assoc_1.localTAddr,&hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                           mBuf);

                        SB_SETUP_DAT_REQ(mBuf1)
                      /* send datareq */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, BUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:   /* send datareq */
                        SB_SETUP_DAT_REQ(mBuf)
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                           ACC_SMALL_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                       break;
                    case 4:   /* send SACK chunk  to change arwnd */
                       SB_SETUP_DAT_REQ(mBuf1)
                       if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                           /* send datareq */
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                               assoc_1.spAssocId, \
                                               &assoc_1.priPeerNAddr,\
                                               ACC_STREAMID, ORDER, NOBUNDLE,\
                                               ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf1);
                          buildPar.arwnd = 200;
                          buildPar.numFrag = 0;
                          buildPar.cumTsn = buildPar.tsn + 1;
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildSackChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,\
                                                 assoc_1.suConId, \
                                                 &assoc_1.peerTAddr,\
                                                 &assoc_1.localTAddr,\
                                           &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                           mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       } 
                       else
                       {
                          SB_RLSMEM(mBuf1);
                       }
                       break;
                    default:
                       break;
                 }
                 break;
              case 4:     /* Test O.302.04: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send datareq */
                       SB_SETUP_DAT_REQ(mBuf)
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, BUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:   /* send SACK chunk  to change arwnd */
                       buildPar.arwnd = 10;
                       buildPar.numFrag = 0;
                       buildPar.cumTsn = buildPar.tsn;
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);

                        SB_SETUP_DAT_REQ(mBuf1)
                      /* send datareq */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,  assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, BUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:   /* send datareq */

                          SB_SETUP_BUNDLDAT_REQ(mBuf)
                          SAddMsgRef(mBuf, DFLT_REGION, DFLT_POOL, &(mBuf1));
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,  assoc_1.spAssocId, \
                                               &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                               ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);

                          /* send datareq */
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,  assoc_1.spAssocId, \
                                               &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                               ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf1);

                          (void)  ItLiSctTermReq(&sbAccCb.itPst, assoc_1.spId, oper.it.spAssocId,\
                                              SCT_ASSOCID_SP, SHTDWN);

                          buildPar.arwnd = 200;
                          buildPar.numFrag = 0;
                          buildPar.cumTsn = buildPar.tsn + 1;
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf3);
                          buildSackChunk(mBuf3,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                                 &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf3);
                           sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /*expected results */
                       break;
                    case 4:
                       buildPar.arwnd = 200;
                       buildPar.numFrag = 0;
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       buildPar.cumTsn = buildPar.tsn + 2;
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf3);
                       buildSackChunk(mBuf3,&buildPar,&assoc_1);
                       /* sb032.102 :  IPV6 Support Added */

                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf3);
                       buildPar.cumTsn = buildPar.tsn + 3;
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildSackChunk(mBuf,&buildPar,&assoc_1);

                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /*expected results */
                       break;
                    case 5:  /* SB_VER13 - change done here for verion 13 */
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
                                                  &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                           sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                        }
                        break;
                    default:
                       break;
                 }
              break;
              /* sb032.102 :  IPV6 Support Added */
              case 5:    /* Test O.302.05: Execution */
                 switch(sbAccCb.curTst.subTest)
                 {
                    case 1:
                       SB_SETUP_DAT_REQ(mBuf)
                          /* buildPar.noBundleFlg = BUNDLE; */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, BUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID,mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                       break;
                    case 2:
                     SB_SETUP_DAT_REQ(mBuf1)
                          /* buildPar.noBundleFlg = BUNDLE; */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, BUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID,mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                       break;
                    case 3:
                       SB_SETUP_BUNDLDAT_REQ(mBuf1)
                          SB_RLSMEM(mBuf1)
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                       break;
                 }
                 break;
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
                switch(curtstnum)
                {    /* Start switch(curtstnum) #2 */
                  case 1:    /* Test O.302.01: Expected Results */
                     switch (sbAccCb.curTst.subTest)
                     {
                        case 1:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 2:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 3:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        default:
                           status = INC_EVNTTYPE;
                           ret = RFAILED;
                           break;
                     }
                     break;
                  case 2:    /* Test O.302.02: Expected Results */
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_DAT_IND)
                     {
                        SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if (msg->evntType == ACC_EVT_UDAT_REQ)
                     {
                        SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
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
                  case 3:      /* Test O.302.03: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* check DATA chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 2: /* check DATA chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
							break;
						 case 3:
							SB_SETUP_STA_IND(assoc_1, SCT_STATUS_SND_FAIL, \
									SCT_CAUSE_LTIME_EXPIRE)
							/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
							oper.it.protId = ACC_PROT_ID;
#endif
							ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, \
									&status, &reason);
							break;
						 case 4:
                            sbAccPeekMsg(&msg);
                            if ( (msg->evntType == ACC_EVT_UDAT_REQ)&&
                                 ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                            {
                               SPrint("\n UDATREQ 1 detected \n\n ");
                               oper.hi.spId = SPID_0;
                               SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if( (msg->evntType == ACC_EVT_UDAT_REQ) && \
                                       ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) )
                            {
                               SPrint("\n UDATREQ 2  detected \n\n ");
                               oper.hi.spId = SPID_0;
                               SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
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
                  case 4:   /* Test O.302.04: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* check DATA chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 2: /* check DATA chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 3:
                            SPrint("\n UDATREQ 1 detected \n\n ");
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 4:
                            SPrint("\n SDOWN  detected \n\n ");
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                            ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                            break;
                         case 5: /* Check SDOWNCMPLT chunk and TermCfm */
                           sbAccPeekMsg(&msg);
                           if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              oper.hi.spId = SPID_0;
                              SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWNCMPLT)
                              ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                              setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           }
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
                           if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                                (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                           break;
                        default:
                           break;
                     }
                     break;
                  /* sb032.102 :  IPV6 Support Added */
                  case 5:    /* Test O.302.05: Expected Results */
                     switch (sbAccCb.curTst.subTest)
                     {
                        case 1:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 2:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        case 3:
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                           break;
                        default:
                           status = INC_EVNTTYPE;
                           ret = RFAILED;
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
            } /* end primitive received */
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
}  /* end sbDatTfMuxTst */



/* 303 series: Timers */

/*
*       Fun:   sbO303_01
*
*       Desc:  Test case : O.303.01
*              Purpose   : Verify that a datagram is removed from the waiting
*                          and congestion queues after the time-out of the
*                          DgLifetimeTmr.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO303_01
(
void
)
#else
PUBLIC  S16 sbO303_01(void)
#endif
{
   U8         curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO303_01)
   curtstnum = 1;
     sbAccCb.curTst.numSubTst = 4;
   sbDatTfTmrTst(curtstnum,"O.303.01");
   RETVALUE(ROK);
} /* end sbO303_01 */

/* sb012.103: Functions placed under flag LSB12 */
#ifdef LSB12
/*
*       Fun:   sbO303_02
*
*       Desc:  Test case : O.303.02
*       Purpose   : Verify that everytime a data packet is sent, t3rtx timer is
*                          started (if it is not already running).
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO303_02
(
void
)
#else
PUBLIC  S16 sbO303_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO303_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 4;
   sbDatTfTmrTst(curtstnum,"O.303.02");
   RETVALUE(ROK);
} /* end sbO303_02 */
#endif /* LSB12 */

/*
*       Fun:   sbO303_03
*
*       Desc:  Test case : O.303.03
*              Purpose   :  Verify that whenever the retransmission timer expires,
*                           all the outstanding datagrams should be marked for
*                           retransmission and some of them sent out.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO303_03
(
void
)
#else
PUBLIC  S16 sbO303_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO303_03)
   curtstnum = 3;
     sbAccCb.curTst.numSubTst = 2;
   sbDatTfTmrTst(curtstnum,"O.303.03");
   RETVALUE(ROK);
} /* end sbO303_03 */

/* sb012.103: Function placed under flag LSB12 */
#ifdef LSB12
/*
*       Fun:   sbO303_04
*
*       Desc:  Test case : O.303.04
*              Purpose   : Verify that the abort operation stops all the timers.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO303_04
(
void
)
#else
PUBLIC  S16 sbO303_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO303_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 6;
   sbDatTfTmrTst(curtstnum,"O.303.04");
   RETVALUE(ROK);
} /* end sbO303_04 */
#endif /* LSB12 */


/*
*       Fun:   sbDatTfTmrTst
*
*       Desc:  Data transfer timer tests.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDatTfTmrTst
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDatTfTmrTst(curtstnum, numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   CmIpHdrParm   hdrParm;
   PRIVATE       Buffer        *mBuf1;
   PRIVATE       Buffer        *mBuf;
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE       SbOperQElm    oper;
   SbAccMsgQElm  *msg;

   TRC2(sbDatTfTmrTst)
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
            if(isBitSet(sbAccCb.curTst.bSctSapCfgMask, SAP_1) == FALSE )
            {
               sbStdSctSapCfg(&sbMgmt, SAP_1);
               if (curtstnum == 3)
               {
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin =  ACC_RTO_SHORT;
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax =  ACC_RTO_SHORT;
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial  =  ACC_RTO_SHORT;
               }
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
          switch(curtstnum)
          {    /* Start switch(curtstnum) #1 */
             case 1:    /* Test O.303.01: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send datareq */
                       SB_SETUP_DAT_REQ(mBuf)
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:   /* send SACK chunk  to change arwnd */
                       buildPar.arwnd = 10;
                       buildPar.numFrag = 0;
                       buildPar.cumTsn = buildPar.tsn;
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_DAT_IND;  /* reply event expected */

                        SB_SETUP_DAT_REQ(mBuf1)
                      /* send datareq */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,  assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:   /* send datareq */
                        SB_SETUP_DAT_REQ(mBuf)
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,  assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                           ACC_SMALL_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                       break;
                    default:
                       break;
                }
                break;
/* sb012.103: Test case placed under flag LSB12 */
#ifdef LSB12
             case 2:     /* Test O.303.02: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                    case 1:   /* check timer */
                       setResponse(&sbMgmt.hdr.response);
                       sbMgmt.hdr.elmId.elmnt = STSBTMR;
                       sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 1101;
                       (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;
                       break;
                    case 2:  /* Send the datagram */
                       SB_SETUP_DAT_REQ(mBuf)
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                       break;
                    case 3: /* check timer */
                       setResponse(&sbMgmt.hdr.response);
                       sbMgmt.hdr.elmId.elmnt = STSBTMR;
                       sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 1101;
                       (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;
                       break;
                    default:
                       break;
                }
                 break;
#endif /* LSB12 */
             case 3:     /* Test O.303.03: Execution */
                /* Send the datagram */
                   SB_SETUP_DAT_REQ(mBuf)
                if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                     (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                {
                    (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId \
                                       ,&assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                       ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                   sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                   sbAccCb.curTst.tickLstDoneFlg = FALSE;
                }
                break;
/* sb012.103: Test case placed under flag LSB12 */
#ifdef LSB12
             case 4:   /* Test O.303.04: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                    case 1:   /* check timer */
                       setResponse(&sbMgmt.hdr.response);
                       sbMgmt.hdr.elmId.elmnt = STSBTMR;
                       sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 1101;
                       (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;
                       break;
                    case 2:  /* Send the datagram */
                       SB_SETUP_DAT_REQ(mBuf)
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                       break;
                    case 3: /* check timer */
                       setResponse(&sbMgmt.hdr.response);
                       sbMgmt.hdr.elmId.elmnt = STSBTMR;
                       sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 1101;
                       (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;
                       break;
                   case 4:
                       if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                             (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                          (void) ItLiSctTermReq(&sbAccCb.itPst, assoc_1.spId,\
                                             assoc_1.spAssocId,\
                                             SCT_ASSOCID_SP, ABORT);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                      break;
                   case 5:
                       setResponse(&sbMgmt.hdr.response);
                       sbMgmt.hdr.elmId.elmnt = STSBTMR;
                       sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 1101;
                       (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;
                      break;
                    default:
                       break;
                }
                /* no execution */
                break;
#endif /* LSB12 */
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
          /* Problem - do cleanup */
                sbAccCb.curTst.subTestsFail++;
                sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
                sbAccCb.curTst.bBusyPreTestConf = FALSE;
                sbAccCb.curTst.bBusyCleanup = TRUE;
           }
          else
          {  /*primitive received */
             reason = 0;
                switch(curtstnum)
                {    /* Start switch(curtstnum) #2 */
                  case 1:      /* Test O.303.01: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* check DATA chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 2: /* check DATA chunk */
                            oper.hi.spId = SPID_0;
                            SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
						 case 3:
							SB_SETUP_STA_IND(assoc_1, SCT_STATUS_SND_FAIL, \
									SCT_CAUSE_LTIME_EXPIRE)
							/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
							oper.it.protId = ACC_PROT_ID;
#endif
							ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND, \
									&status, &reason);
							break;
                         default:
                            break;
                      }
                     break;
/* sb012.103: Placed test case under flag LSB12 */
#ifdef LSB12
                  case 2:   /* Test O.303.02: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                       case 1:
                           /* Check that retransmission timer is stopped */
                          mgmt.cfm.status = LCM_PRIM_OK;
                          ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T3RTX, STOPPED);
                          break;
                       case 2:   /* Check DATA chunk */
                          SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                          ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                   &assoc_1, &status );
                          break;
                       case 3:
                           /* Check that retransmission timer is running */
                          mgmt.cfm.status = LCM_PRIM_OK;
                          ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T3RTX, RUNNING);
                          break;
                       default:
                          break;
                     }
                     break;
#endif /* LSB12 */
                  case 3:   /* Test O.303.03: Expected Results */
                     sbAccPeekMsg(&msg);
                     if ( (msg->evntType == ACC_EVT_UDAT_REQ) &&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                     {
                        /* Check DATA chunk */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1,\
                                                   &status );
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if ( (msg->evntType == ACC_EVT_UDAT_REQ) &&
                                 ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                     {
                        /* Check retransmitted DATA chunk  */
                         oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1,\
                                                   &status );
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                       /*-- RFC 4460 -- MLK Fix*/
                       SB_RLSMEM(mBuf);
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
/* sb012.103: Placed test case under flag LSB12 */
#ifdef LSB12
                  case 4:  /* Test O.303.04: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                       case 1:
                           /* Check that retransmission timer is stopped */
                          mgmt.cfm.status = LCM_PRIM_OK;
                          ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T3RTX, STOPPED);
                          break;
                       case 2:   /* Check DATA chunk */
                          SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                          ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, \
                                                   &status );
                          break;
                       case 3:
                           /* Check that retransmission timer is running */
                          mgmt.cfm.status = LCM_PRIM_OK;
                          ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T3RTX, RUNNING);
                          break;
                       case 4:
                          sbAccPeekMsg(&msg);
                          if (msg->evntType == ACC_EVT_TERM_CFM)
                          {
                             SPrint("TermCfm detected \n");
                             SB_SETUP_TERM_CFM(assoc_1,SCT_OK, SCT_CAUSE_NOT_APPL)
                             ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_CFM, &status,\
                                               &reason);
                             setBit(&sbAccCb.curTst.bTickMask, BIT1);
                          }
                          else if (msg->evntType == ACC_EVT_UDAT_REQ)
                          {
                             SPrint("Abort chunk detected \n");
                             oper.hi.spId = SPID_0;
                             /* RFC 4460 upgrade -- user initiated ABORT is expected */
                             SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_USR_INITIATED_ABORT, 0, FALSE, \
                                                 SB_ID_ABORT)
                                 oper.hi.spId = SPID_0;
                             ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1,\
                                                   &status  );
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
                           /* Check that retransmission timer is running */
                          mgmt.cfm.status = LCM_PRIM_OK;
                          ret = sbLsbChkTmr(&mgmt, &status, &reason, ACC_T3RTX, STOPPED);
                          break;
                       default:
                          break;
                     }
#endif /* LSB12 */

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
          } /*primitive received */
          if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
          {
             sbAccCb.curTst.subTest++;
             sbAccCb.curTst.bTickMask = 0;
          }
          sbAccCb.curTst.state++;
          break;
       case 2: /* Do cleanup before next test */
          if( (sbAccCb.curTst.subTest == 4) && (curtstnum == 3) )
             sbAccCb.curTst.subTest ++;

            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst)
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
}  /* end sbDatTfTmrTst */

/* Sequenced delivery */
/*
*       Fun:   sbO304_01
*
*       Desc:  Test case : O.304.01
*              Purpose   : Verify that when datagrams marked for in order transmission arrive
*                          out of order (according to tsn and seq nr), the SCTP will
*                          wait for a complete sequence to arrive before sending the indication
*                          to the service provider.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO304_01
(
void
)
#else
PUBLIC  S16 sbO304_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO304_01)
   curtstnum = 1;
     sbAccCb.curTst.numSubTst = 4;
   sbDatTfSeqDel(curtstnum,"O.304.01");
   RETVALUE(ROK);
} /* end sbO304_01 */


/*
*       Fun:   sbO304_02
*
*       Desc:  Test case : O.304.02
*              Purpose   : Verify that when DATA chunks marked for out of order delivery arrive,
*                          the SCTP will send data indications to the service provider for every
*                          chunk arriving (unorderFlg = TRUE).
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO304_02
(
void
)
#else
PUBLIC  S16 sbO304_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO304_02)
   curtstnum = 2;
     sbAccCb.curTst.numSubTst = 4;
   sbDatTfSeqDel(curtstnum,"O.304.02");
   RETVALUE(ROK);
} /* end sbO304_02 */

/*
*       Fun:   sbO304_03
*
*       Desc:  Test case : O.304.03
*              Purpose   : Verify the use of different streams in ordered and unordered data
*                          transfer.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO304_03
(
void
)
#else
PUBLIC  S16 sbO304_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO304_03)
   curtstnum = 3;
     sbAccCb.curTst.numSubTst = 6;
   sbDatTfSeqDel(curtstnum,"O.304.03");
   RETVALUE(ROK);
} /* end sbO304_03 */


/*
*       Fun:   sbDatTfSeqDel
*
*       Desc:  Data transfer sequenced delivery tests.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDatTfSeqDel
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDatTfSeqDel(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   CmIpHdrParm   hdrParm;
   Buffer        *mBuf;
   SbAccMsgQElm  *msg;
   PRIVATE       SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbOperQElm    oper;
   PRIVATE       SbMgmt        sbMgmt;

   TRC2(sbDatTfSeqDel)
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
              case 1:    /* Test O.304.01: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                       if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN;
                          buildPar.seqNr = 0;
                          buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                          buildPar.streamId = ACC_STREAMID;
                          buildDataChunk(mBuf, &buildPar, &assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 2:
                        /* send DATA chunk */
                       SPrint("Send the data seqNr2\n\n");
                        SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                        buildPar.tsn = ACC_INIT_TSN + 2;
                        buildPar.seqNr = 2;
                        buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                        buildPar.streamId = ACC_STREAMID;
                        buildDataChunk(mBuf,&buildPar,&assoc_1);
                         SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                       break;
                    case 3:  /* send DATA chunk */
                       if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) &&
                            ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE))
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN + 1;
                          buildPar.seqNr = 1;
                          buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                           buildPar.streamId = ACC_STREAMID;
                          buildDataChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    default:
                       break;
                }
                break;
              case 2:    /* Test O.304.02: Execution */
                     switch( sbAccCb.curTst.subTest)
                 {
                    case 1:  /* 304.02*/ /* send DATA chunk */
                       if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN;
                          buildPar.chunkFlg = 7;     /* set up for unordered delivery */
                           buildPar.streamId = ACC_STREAMID;
                          buildDataChunk(mBuf, &buildPar, &assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 2: /* 304.02 */
                       /* send DATA chunk */
                       if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                       {
                          SPrint("Send the data seqNr2\n");
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN + 1;
                          buildPar.chunkFlg = 7;     /* set up for sequenced delivery */
                           buildPar.streamId = ACC_STREAMID;
                          buildDataChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr, \
                                                 &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 3:  /* 304.02 */ /* send DATA chunk */
                       if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN + 2;
                          buildPar.chunkFlg = 7;     /* set up for sequenced delivery */
                           buildPar.streamId = ACC_STREAMID;
                          buildDataChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    default:
                       break;
                } /*end O.304.02 switch */
                break;
             case 3:    /* Test O.304.03: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:  /* 304.03*/ /* STREAM 1 */
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       buildPar.tsn = ACC_INIT_TSN;
                       buildPar.seqNr = 1;
                       buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                       buildPar.streamId = ACC_STREAMID;
                       buildDataChunk(mBuf, &buildPar, &assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                       break;
                    case 2: /* 304.03 */  /* STREAM 2 */
                        if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN +1;
                          buildPar.seqNr = 0;
                          buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                          buildPar.streamId = ACC_STREAMID + 1;
                          buildDataChunk(mBuf, &buildPar, &assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                                 &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 3:  /* 304.03 */ /* send DATA chunk  on STREAM 1*/
                       if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN +2;
                          buildPar.chunkFlg = 7;     /* set up for unordered delivery */
                           buildPar.streamId = ACC_STREAMID;
                          buildDataChunk(mBuf, &buildPar, &assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr, \
                                                 &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 4: /* 304.03 */ /* send DATA chunk  on STREAM 2*/
                       if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                            ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN + 3;
                          buildPar.chunkFlg = 7;     /* set up for unordered delivery */
                          buildPar.streamId = ACC_STREAMID + 1;
                          buildDataChunk(mBuf, &buildPar, &assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                                 &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 5: /* send DATA chunk  on STREAM 1*/
                       if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                            ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) &&
                            ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE))
                       {
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.tsn = ACC_INIT_TSN + 4;
                          buildPar.seqNr = 0;
                          buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                           buildPar.streamId = ACC_STREAMID;
                          buildDataChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                          (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                                 &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                                 &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    default:
                       break;
                }
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
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            else
            {
             reason = 0;
                switch(curtstnum)
                {    /* Start switch(curtstnum) #2 */
                   case 1:      /* Test O.304.01: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            { SPrint("SACK detected \n");
                               SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN))
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SPrint("DatInd detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
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
                         case 2: /* Check SACK chunk */
                            SB_SETUP_SACK_INFO(2, 2, ACC_INIT_TSN )
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 3:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint("SACK detected \n");
                               SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN + 2))
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( ( msg->evntType == ACC_EVT_DAT_IND ) &&
                                      (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                            {
                               SPrint("DatInd1 detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if ( ( msg->evntType == ACC_EVT_DAT_IND ) &&
                                      (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)  )
                            {
                               SPrint("DatInd2 detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT2);
                            }
                            else
                            {
                               status = INC_EVNTTYPE;
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                               setBit(&sbAccCb.curTst.bTickMask, BIT2);
                               ret = RFAILED;
                            }
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)&&
                                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE))
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         default:
                            break;
                     }
                     break;
                  case 2:      /* Test O.304.02: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* 304.02 */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint(" Receive SACK 1 \n ");
                               SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN))
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SPrint("DatInd detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         case 2:  /* 304.02 */ /* Check SACK chunk */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               SPrint("Receive SACK 2 \n ");
                               SB_SETUP_SACK_INFO(0, 0, ( ACC_INIT_TSN + 1) )
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar\
                                                        , &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SPrint("DatInd1 detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                         case 3: /* 304.02 */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint("Receive SACK 3 \n ");
                               SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN + 2))
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SPrint("DatInd1 detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         default:
                            break;

                      } /* end 304.02 switch */
                      break;
                    case 3:      /* Test O.304.03: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* 304.03 */
                            SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN )
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1,\
                                                     &status );
                            break;
                         case 2:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint("Receive SACK 1 \n ");
                               SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN+1))
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SPrint("DatInd detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND\
                                                 , &status, &reason);
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
                         case 3:  /* 304.03 */ /* Check SACK chunk */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               SPrint("Receive SACK 2 \n ");
                               SB_SETUP_SACK_INFO(0, 0, ( ACC_INIT_TSN + 2) )
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SPrint("DatInd1 detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                         case 4: /* 304.03 */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint("Receive SACK 3 \n ");
                               SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN + 3))
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SPrint("DatInd1 detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         case 5:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint("SACK detected \n");
                               SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN + 4))
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1,\
                                                        &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( ( msg->evntType == ACC_EVT_DAT_IND ) &&
                                      (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                            {
                               SPrint("DatInd1 detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if ( ( msg->evntType == ACC_EVT_DAT_IND ) &&
                                      (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)  )
                            {
                               SPrint("DatInd2 detected \n");
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT);
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT2);
                            }
                            else
                            {
                               status = INC_EVNTTYPE;
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                               setBit(&sbAccCb.curTst.bTickMask, BIT2);
                               ret = RFAILED;
                            }
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)&&
                                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE))
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         default:
                            break;

                      } /* end 304.03 switch */
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
            } /* end primitive received */
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
}  /* end sbDatTfSeqDel */

/* Acknowledgements */
/*
*       Fun:   sbO305_01
*
*       Desc:  Test case : O.305.01
*              Purpose   :Verify that the first datagram send to the SCTP peer endpoint of an
*                         established association will receive a SACK.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_01
(
void
)
#else
PUBLIC  S16 sbO305_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfSack_1(curtstnum,"O.305.01");
   RETVALUE(ROK);
} /* end sbO305_01 */

/*
*       Fun:   sbO305_02
*
*       Desc:  Test case : O.305.02
*              Purpose   : Verify that for every second DATA chunk received (after the first SACK) a
*                          SACK will be sent.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_02
(
void
)
#else
PUBLIC  S16 sbO305_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 4;
   sbDatTfSack_1(curtstnum,"O.305.02");
   RETVALUE(ROK);
} /* end sbO305_02 */

/*
*       Fun:   sbO305_03
*
*       Desc:  Test case : O.305.03
*              Purpose   : Verify that if a gap is detected in the tsn numbers every DATA chunk
*                          received will be acknowledged.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_03
(
void
)
#else
PUBLIC  S16 sbO305_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfSack_1(curtstnum,"O.305.03");
   RETVALUE(ROK);
} /* end sbO305_03 */

/*
*       Fun:   sbO305_04
*
*       Desc:  Test case : O.305.04
*              Purpose   : Verify that if the service user takes longer than the configured
*                          value of maxAckDelayTm (typically 200 ms) to send the second
*                          datagram to the receiving peer, the peer SCTP will acknowledge
*                          every DATA chunk received.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_04
(
void
)
#else
PUBLIC  S16 sbO305_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 4;
   sbDatTfSack_1(curtstnum,"O.305.04");
   RETVALUE(ROK);
} /* end sbO305_04 */


/*
*       Fun:   sbO305_05
*
*       Desc:  Test case : O.305.05
*              Purpose   : Verify that all unacknowledged datagrams can be sent to
*                          the service user.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_05
(
void
)
#else
PUBLIC  S16 sbO305_05(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_05)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfSack_2(curtstnum,"O.305.05");
   RETVALUE(ROK);
} /* end sbO305_05 */


/*
*       Fun:   sbO305_06
*
*       Desc:  Test case : O.305.06
*              Purpose   : Verify that an unacknowledged datagram may be retrieved from
*                          the SCTP in the event of communication failure, if the
*                          freezetimer has not expired.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_06
(
void
)
#else
PUBLIC  S16 sbO305_06(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_06)
   curtstnum = 6;
   sbDatTfSack_2(curtstnum,"O.305.06");
   RETVALUE(ROK);
} /* end sbO305_06 */

/*
*       Fun:   sbO305_07
*
*       Desc:  Test case : O.305.07
*              Purpose   : Verify fast retransmission, when four SACKs is received
*                          that skip a specific data chunk.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_07
(
void
)
#else
PUBLIC  S16 sbO305_07(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_07)
   curtstnum = 7;
   sbAccCb.curTst.numSubTst = 6;
   sbDatTfSack_2(curtstnum,"O.305.07");
   RETVALUE(ROK);
} /* end sbO305_07 */

/*
*       Fun:   sbO305_08
*
*       Desc:  Test case : O.305.08
*              Purpose   : Verify fast retransmission, when four SACKs imply that a
*                          datagram has been discarded (probably due to buffer problems )
*                          contradicting a previous SACK..
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_08
(
void
)
#else
PUBLIC  S16 sbO305_08(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_08)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 7;
   sbDatTfSack_2(curtstnum,"O.305.08");
   RETVALUE(ROK);
} /* end sbO305_08 */

/*
*       Fun:   sbO305_09
*
*       Desc:  Test case : O.305.09
*              Purpose   : Verify that if the freezetimer expires after communication failure,
*                          no data will be retrievable from the SCTP.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_09
(
void
)
#else
PUBLIC  S16 sbO305_09(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_09)
   curtstnum = 9;
   sbDatTfSack_2(curtstnum,"O.305.09");
   RETVALUE(ROK);
} /* end sbO305_09 */
/* sb018.103: Added new test case */
/*
*       Fun:   sbO305_11
*
*       Desc:  Test case : O.305.11
*              Purpose   : Verify that bytesOut is not going to negative if
*                          chunk is Gap-Acked and missing in further 3 SACKs
*                          and  then fast retransmitted.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_11
(
void
)
#else
PUBLIC  S16 sbO305_11(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_11)
   curtstnum = 11;
   sbAccCb.curTst.numSubTst = 7;
   sbDatTfSack_2(curtstnum,"O.305.11");
   RETVALUE(ROK);
} /* end sbO305_11 */


/* RFC 4460 -- SB_RFC_7 */
/*
*       Fun:   sbO305_10
*
*       Desc:  Test case : O.305.10
*              Purpose   : In SHUTDOWN-SENT state, if a peer DATA is to sacked < reporting the fragments >
                           it should send SACK and then SHUTDOWN
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO305_10
(
void
)
#else
PUBLIC  S16 sbO305_10(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO305_10)
   curtstnum = 10;
   sbAccCb.curTst.numSubTst = 4;
   sbDatTfSack_2(curtstnum,"O.305.10");
   RETVALUE(ROK);
} /* end sbO305_10 */

/*
*       Fun:   sbDatTfSack_1
*
*       Desc:  Data transfer acknowledgements tests.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDatTfSack_1
(
U8   curtstnum,  /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDatTfSack_1(curtstnum,numstr)
U8   curtstnum;  /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   PRIVATE       SbMgmtQElm    mgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   CmIpHdrParm   hdrParm;
   Buffer        *mBuf;
   PRIVATE       U8            tsn;
   SbAccMsgQElm  *msg;
   PRIVATE       SbOperQElm    oper;
   PRIVATE       SbMgmt        sbMgmt;
   PRIVATE       SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE       SbAccAssoc    assoc_1;

   TRC2(sbDatTfSack_1)
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
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
              case 1:    /* Test O.305.01: Execution */
                 if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                      ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                 {
                    SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                    tsn = (ACC_INIT_TSN);
                    SB_SETUP_UNORDERED_DATA(tsn)
                    buildDataChunk(mBuf,&buildPar,&assoc_1);
                     SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                    (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, &assoc_1.peerTAddr,
                                           &assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                    sbAccCb.curTst.tickLstDoneFlg = FALSE;
                 }
                 break;
              case 2:    /* Test O.305.02: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:   /* send DATA chunk */
                      if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                         ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                      {
                         SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                         tsn = ACC_INIT_TSN;
                         SB_SETUP_UNORDERED_DATA(tsn )
                         buildDataChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                         (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                                &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                         sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                      }
                      break;
                   case 2:   /* send DATA chunk */  
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      tsn = (ACC_INIT_TSN + 1);
                      SB_SETUP_UNORDERED_DATA(tsn )
                      buildDataChunk(mBuf,&buildPar,&assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                             assoc_1.suConId,
                                             &assoc_1.peerTAddr,
                                             &assoc_1.localTAddr,
                                             &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                      break;
                   case 3:
                      if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                         ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                      {
                         SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                         tsn = (ACC_INIT_TSN + 2);
                         SB_SETUP_UNORDERED_DATA(tsn)
                         buildDataChunk(mBuf,&buildPar,&assoc_1);
                         SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                         (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,
                                                assoc_1.suConId,
                                                &assoc_1.peerTAddr,
                                                &assoc_1.localTAddr,
                                                &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                         sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                      }
                      break;
                   default:
                       break;
                }
                break;
             case 3:    /* Test O.305.03: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:   /* send DATA chunk */
                      if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                         ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                      {
                         SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                         tsn = ACC_INIT_TSN;
                         SB_SETUP_ORDERED_DATA(0,tsn )
                         buildDataChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                         (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                                &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                         sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* expected response */
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                      }
                      break;
                   case 2:   /* send DATA chunk */
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      tsn = ACC_INIT_TSN + 2;
                      SB_SETUP_ORDERED_DATA(2,tsn )
                      buildDataChunk(mBuf,&buildPar,&assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                             &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                      break;
                   default:
                       break;
                }
                break;
             case 4:    /* Test O.305.04: Execution */
                switch( sbAccCb.curTst.subTest)
                {
                   case 1:   /* send DATA chunk */
                      if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                         ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                      {
                         SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                         tsn = (ACC_INIT_TSN);
                         SB_SETUP_ORDERED_DATA(0, tsn )
                         buildDataChunk(mBuf,&buildPar,&assoc_1);
                         SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                         (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, &assoc_1.peerTAddr,\
                                                &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                         sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                      }
                      break;
                   case 2:
                      sbAccCb.curTst.delay = 2;
                      sbAccCb.curTst.evtType = ACC_EVT_NO_RESP;  /* expected response */
                      break;
                   case 3:   /* send DATA chunk */
                      if ( ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                         ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                      {
                         SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                         tsn = (ACC_INIT_TSN + 1);
                         SB_SETUP_ORDERED_DATA(1, tsn  )
                         buildDataChunk(mBuf,&buildPar,&assoc_1);
                         SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                        (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                            &assoc_1.peerTAddr,&assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* expected response */
                        sbAccCb.curTst.tickLstDoneFlg = FALSE;
                      }
                     break;
                  default:
                     break;
                }
                break;
            } /* end curtstnum switch */
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
               if( (curtstnum == 4) && (sbAccCb.curTst.subTest == 2) )
               {
                  sbAccCb.curTst.subTestsPass++;
                  sbAccCb.curTst.delay = 0;
               }
               else
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,\
                                      sbAccCb.curTst.evtType, \
                                      TIMEOUT_ON_PRIM, 0);
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
             }
            else
            {
             reason = 0;
                switch(curtstnum)
                {    /* Start switch(curtstnum) #2 */
                   case 1:      /* Test O.305.01: Expected Results */
                      sbAccPeekMsg(&msg);
                      if (msg->evntType == ACC_EVT_UDAT_REQ)
                      {  SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN )
                         ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                  &assoc_1, &status );
                         setBit(&sbAccCb.curTst.bTickMask, BIT1);
                      }
                      else if ( msg->evntType == ACC_EVT_DAT_IND )
                      {
                         SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                         ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
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
                   case 2:      /* Test O.305.02: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN )
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&\
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         case 2:
                            SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                            ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
                                              &status, &reason);
                            break;
                         case 3:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SB_SETUP_SACK_INFO(2, 2, (ACC_INIT_TSN+2) )
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         default:
                            break;
                      }
                      break;
                  case 3:      /* Test O.305.03: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN )
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&& \
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         case 2:
                            SB_SETUP_SACK_INFO(2, 2, (ACC_INIT_TSN) )
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         default:
                            break;
                      }
                     break;
                  case 4:      /* Test O.305.04: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               SB_SETUP_SACK_INFO(0, 0, ACC_INIT_TSN )
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&\
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         case 3:
                                sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {
                               SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN+1) )
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            else if ( msg->evntType == ACC_EVT_DAT_IND )
                            {
                               SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
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
                }      /*End Subtest successful */
             } /* end primitive received */

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
}  /* end sbDatTfSack_1 */

/*
*       Fun:   sbDatTfSack_2
*
*       Desc:  Data transfer acknowledgements tests.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbDatTfSack_2
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PUBLIC  S16 sbDatTfSack_2(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   PRIVATE       SbOperQElm    oper;
   PRIVATE       SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE       SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE       SbAccAssoc    assoc_1;
   Buffer        *mBuf;
   Buffer        *mBuf1;
   Buffer        *mBuf2;
   SbAccMsgQElm  *msg;
   CmIpHdrParm   hdrParm;
   U8           ID; 

   TRC2(sbDatTfSack_2)
   ret = ROK;
 
   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
      {
         sbStdGenCfg(&sbMgmt);
         sbMgmt.t.cfg.s.genCfg.reConfig.maxPathReTx = 2;
         sbMgmt.t.cfg.s.genCfg.reConfig.maxAssocReTx = 1;
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

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
       case 0:
            switch(curtstnum)
            {    /* Start switch(curtstnum) #1 */
              case 5:    /* Test O.305.05: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                        SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:  /* Send the status request to obtain the unacknowledged datagrams */
                       (void) ItLiSctStaReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,SCT_RTRV_UNACK_DGMS);
                       sbAccCb.curTst.evtType = ACC_EVT_DAT_IND;  /* reply event expected */
                       break;
                    default:
                       break;
                }
                break;
              case 6:    /* Test O.305.06: Execution */
                 sbAccCb.curTst.numSubTst = (U8) (sbMgmt.t.cfg.s.genCfg.reConfig.maxAssocReTx  + 4);
                 if ( sbAccCb.curTst.subTest == 1)
                 {
                      SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */ 
                    (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                         &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                         ORDER, NOBUNDLE,\
                                         ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
            
                 }
                 else  if ( sbAccCb.curTst.subTest  == (sbAccCb.curTst.numSubTst -2) )
                 {
                    if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                    {
                       sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                    }
                 }
                 else if ( sbAccCb.curTst.subTest  == (sbAccCb.curTst.numSubTst -1) )
                 {
                     SB_SETUP_DAT_REQ(mBuf)
                     SB_RLSMEM(mBuf)
                    (void) ItLiSctStaReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                         &assoc_1.priPeerNAddr,SCT_RTRV_UNACK_DGMS);
                    sbAccCb.curTst.evtType = ACC_EVT_DAT_IND;  /* reply event expected */
                 }
                 else
                 {
                    if ( sbAccCb.curTst.subTest < (sbAccCb.curTst.numSubTst -2) )
                    {
                        SB_SETUP_DAT_REQ(mBuf)
                        SB_RLSMEM(mBuf)
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                    }
                 }
                 break;
              case 7:    /* Test O.305.07: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:  /* Send the status request to obtain the unacknowledged datagrams */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:  /* Send the status request to obtain the unacknowledged datagrams */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 4:  /* Send the status request to obtain the unacknowledged datagrams */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 5:
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       SB_RLSMEM(mBuf)
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       SB_SETUP_SACK_INFO(2, 2, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       SB_SETUP_SACK_INFO(2, 3, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf1,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf1);

                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf2);
                       SB_SETUP_SACK_INFO(2, 4, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf2,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf2);

/*                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf3);
                       SPrint("Send SACK 4 \n ");
                       SB_SETUP_SACK_INFO(2, 4, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf3,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)*/
                       /* sb032.102 :  IPV6 Support Added */
/*                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf3);
                       break;*/
                    default:
                       break;
                 }
                 break;
              case 8:    /* Test O.305.08: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:   /* send DATA chunk */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       SPrint("Send SACK 1 \n ");
                       SB_SETUP_SACK_INFO(2, 2, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);

                       SB_SETUP_DAT_REQ(mBuf1) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM,\
                                            ACC_PROT_ID, mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 4:   /* send DATA chunk */
                       SB_SETUP_DAT_REQ(mBuf1) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 5:   /* send DATA chunk */
                       SB_SETUP_DAT_REQ(mBuf1) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 6:
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       SB_RLSMEM(mBuf)
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       SPrint("Send SACK 1 \n ");
                       SB_SETUP_SACK_INFO(2, 2, (buildPar.tsn) ) 
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       SPrint("Send SACK 2 \n ");
                       SB_SETUP_SACK_INFO(2, 3, (buildPar.tsn) ) 
                       buildSackChunk(mBuf1,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf1);

                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf2);
                       SPrint("Send SACK 3 \n ");
                       SB_SETUP_SACK_INFO(2, 4, (buildPar.tsn) ) 
                       buildSackChunk(mBuf2,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf2);

                       /*SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf3);
                       SPrint("Send SACK 4 \n ");
                       SB_SETUP_SACK_INFO(2, 2, (buildPar.tsn) ) 
                       buildSackChunk(mBuf3,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)*/
                       /* sb032.102 :  IPV6 Support Added */
                       /*(void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf3);*/
                 
                       break;
                    default:
                       break;
                 }
                 break;
              case 9:    /* Test O.305.09: Execution */
                 sbAccCb.curTst.numSubTst = (U8) (sbMgmt.t.cfg.s.genCfg.reConfig.maxAssocReTx  + 5);
                 if ( sbAccCb.curTst.subTest == 1)
                 {
                    SPrint("&&&&& Send Data \n");
                    SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                    (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                         assoc_1.spAssocId, \
                                         &assoc_1.priPeerNAddr,\
                                         ACC_STREAMID,\
                                         ORDER, NOBUNDLE,\
                                         ACC_NO_LIFETM_LIM,\
                                         ACC_PROT_ID, mBuf);
                    sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
            
                 }
                 else  if ( sbAccCb.curTst.subTest  == (sbAccCb.curTst.numSubTst -3) )
                 {
                    if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) )
                    {
                       sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
                    }
                 }
                 else if ( sbAccCb.curTst.subTest  == (sbAccCb.curTst.numSubTst -1) )
                 {
                    (void) ItLiSctStaReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                         &assoc_1.priPeerNAddr,SCT_RTRV_UNACK_DGMS);
                    sbAccCb.curTst.evtType = ACC_EVT_STA_CFM;  /* reply event expected */
                 }
                 else
                 {
                    if ( sbAccCb.curTst.subTest < (sbAccCb.curTst.numSubTst -3) )
                    {
                       SB_SETUP_DAT_REQ(mBuf)
                       SB_RLSMEM(mBuf)
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                    }
                 }
                 break;
              case 10:    /* Test O.305.10: Execution */
                switch(sbAccCb.curTst.subTest)
                {
                   case 1:
                      SPrint("Send Data \n");
                      SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                      (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                         assoc_1.spAssocId, \
                                         &assoc_1.priPeerNAddr,\
                                         ACC_STREAMID,\
                                         ORDER, NOBUNDLE,\
                                         ACC_NO_LIFETM_LIM,\
                                         ACC_PROT_ID, mBuf);
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      break;
                   case 2:
                      SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                      SPrint("Send SACK  \n ");
                      SB_SETUP_SACK_INFO(0, 0, (buildPar.tsn) ) 
                      buildSackChunk(mBuf,&buildPar,&assoc_1);
                      SB_SETUP_IPHDR_PAR(NOFRAGM)
                      /* sb032.102 :  IPV6 Support Added */
                      (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                       (void)  ItLiSctTermReq(&sbAccCb.itPst, assoc_1.spId,
                              assoc_1.spAssocId, SCT_ASSOCID_SP, SHTDWN);
                       sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* reply event expected */
                       break;
                   case 3:
                       if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) &&
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) )
                       {
                          SPrint("Send DATA from TUCL  \n ");
                          SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                          buildPar.streamId = 1;
                          buildPar.tsn = ACC_INIT_TSN+2;
                          buildPar.seqNr = 0;
                          buildPar.chunkFlg = 3;     /* set up for sequenced delivery */
                          buildDataChunk(mBuf,&buildPar,&assoc_1);
                          SB_SETUP_IPHDR_PAR(NOFRAGM)
                          /* sb032.102 :  IPV6 Support Added */
                         (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                        &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                        &assoc_1.localIf,
#endif
                                        mBuf);
                         sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                      }
                      break;
                 }
                 break;
            /* sb018.103: Added the test case for check bytes out is not
               going to nagative */
            case 11 :    /* Test O.305.11 Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:  /* Send the status request to obtain the unacknowledged datagrams */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:  /* Send the status request to obtain the unacknowledged datagrams */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 4:  /* Send the status request to obtain the unacknowledged datagrams */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 5:  /* Send the status request to obtain the unacknowledged datagrams */
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 6:
                       SB_SETUP_DAT_REQ(mBuf) /* Setup data buffer and other parameters \
                                                 for data transmission */
                       SB_RLSMEM(mBuf)
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       SB_SETUP_SACK_INFO(2, 2, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       SB_SETUP_SACK_INFO1(1, 1, 3, 3, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf1,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf1);

                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf2);
                       SB_SETUP_SACK_INFO(4, 4, (buildPar.tsn-1));
                       buildSackChunk(mBuf2,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf2);

                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf2);
                       SB_SETUP_SACK_INFO(5, 5, (buildPar.tsn-1));
                       buildSackChunk(mBuf2,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf2);
                       break;
                    default:
                       break;
                 }
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
               if ( (curtstnum == 9) && (sbAccCb.curTst.subTest  ==\
                                        (sbAccCb.curTst.numSubTst -2)) )
               {
                  sbAccCb.curTst.subTestsPass++;
               }
               else
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,\
                                      sbAccCb.curTst.evtType, \
                                      TIMEOUT_ON_PRIM, 0);
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
            }
            else
            {
             reason = 0;
                switch(curtstnum)
                {    /* Start switch(curtstnum) #2 */
                  case 5:      /* Test O.305.05: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check DATA chunk */
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            /*record the tsn to check in the DAT_IND */
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 2:
                            SB_SETUP_DAT_IND(assoc_1, SCT_UNACK_DAT) 
                            ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
                                              &status, &reason);
                                           /* check tsn if type = UNACK_DAT */
                            break;
                         default:
                            break;
                      }
                     break;
                  case 6:      /* Test O.305.06: Expected Results */
                     if ( sbAccCb.curTst.subTest < (sbAccCb.curTst.numSubTst-2 ) )
                     {
                        SPrint(" Receive UDATREQ \n ");
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status );
                     }
                     else if ( sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-2 ) )
                     {
                        sbAccPeekMsg(&msg);
                        if ((msg->evntType == ACC_EVT_UDAT_REQ) )
                        {
                           SPrint(" Receive ABORT \n ");
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_RES, 0, FALSE, SB_ID_ABORT) 
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status  );
                           setBit(&sbAccCb.curTst.bTickMask, BIT1);
                        }
                        else if (msg->evntType == ACC_EVT_TERM_IND)
                        {
                           /* check TermInd */
                           SPrint(" Receive TermInd \n ");
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_COMM_LOST,\
                                             SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND,\
                                             &status, &reason);
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        }
                        else
                        {
                           status = INC_EVNTTYPE;
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           ret = RFAILED;
                        }
                        if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                              ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)  )
                              sbAccCb.curTst.tickLstDoneFlg = TRUE;
                        
                     }
                     else if ( sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1 ) )
                     {
                        SB_SETUP_DAT_IND(assoc_1, SCT_UNACK_DAT)
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                     }
                     break;
                  case 7:      /* Test O.305.07: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check DATA chunk */
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 2:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 3:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 4:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 5:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         default:
                            break;
                      }
                     break;
                  case 8:      /* Test O.305.08: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check DATA chunk */
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 2:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 3:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 4:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 5:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 6:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            if (buildPar.cumTsn != (buildPar.tsn+1))
                            {
                               status = INC_TSN;
                               ret = RFAILED;
                            }
                            break;
                         default:
                            break;
                      }
                      break;
                   case 9:      /* Test O.305.09: Expected Results */
                     if ( sbAccCb.curTst.subTest < (sbAccCb.curTst.numSubTst-3 ) )
                     {
                        SPrint(" Receive UDATREQ \n ");
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                     }
                     else if ( sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-3 ) )
                     {
                        sbAccPeekMsg(&msg);
                        if ((msg->evntType == ACC_EVT_UDAT_REQ) )
                        {
                           SPrint(" Receive ABORT \n ");
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(SB_CHUNK_ERROR_RES, 0, FALSE, SB_ID_ABORT) 
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar,\
                                                 &assoc_1, &status  );
                           setBit(&sbAccCb.curTst.bTickMask, BIT1);
                        }
                        else if (msg->evntType == ACC_EVT_TERM_IND)
                        {
                           /* check TermInd */
                           SPrint(" Receive TermInd \n ");
                           SB_SETUP_TERM_IND(assoc_1, SCT_STATUS_COMM_LOST,\
                                             SCT_CAUSE_NOT_APPL)
                           ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_TERM_IND,\
                                             &status, &reason);
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        }
                        else
                        {
                           status = INC_EVNTTYPE;
                           setBit(&sbAccCb.curTst.bTickMask, BIT0);
                           setBit(&sbAccCb.curTst.bTickMask, BIT1);
                           ret = RFAILED;
                        }
                        if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                              ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)  )
                              sbAccCb.curTst.tickLstDoneFlg = TRUE;
                        
                     }
                     else if ( sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1 ) )
                     {
                        oper.it.staType = SCT_RTRV_UNACK_DGMS;
                        oper.it.cause =  SCT_CAUSE_INV_PAR_VAL;
                        oper.it.result = SCT_NOK;
                        oper.it.suId = 0;
                        oper.it.suAssocId = 0;
                        ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_CFM, &status, &reason);
                     }
                     break;
                  case 10:   /* Test O.305.10: Expected Results */
                     switch (sbAccCb.curTst.subTest)
                     {          
                        case 1:
                           SPrint("Received UDATREQ \n ");
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, \
                                                 &assoc_1, &status );
                           break;
                        case 2:
                           SPrint("Received SDOWN \n");
                           oper.hi.spId = SPID_0;
                           SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                           ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                           break;
                        case 3:
                           sbAccCb.curTst.tickLstDoneFlg = FALSE;
                           sbAccPeekMsg(&msg);
                           if ( msg->evntType == ACC_EVT_DAT_IND )
                           {
                              SPrint("Received DAT ind at UL  \n ");
                              SB_SETUP_DAT_IND(assoc_1, SCT_PEER_DAT) 
                              ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND,\
                                              &status, &reason);
                              setBit(&sbAccCb.curTst.bTickMask, BIT2);
                           }
                           else if (msg->evntType == ACC_EVT_UDAT_REQ)
                           {
                              SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                              if (ID == SB_ID_SACK )
                              {
                                 SPrint("Received SACK  \n ");
                                 SB_SETUP_SACK_INFO(3, 3, ACC_INIT_TSN-1)
                                 ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT1);
                              }
                              else if ( ID == SB_ID_SDOWN)
                              {
                                 SPrint("Received SDOWN \n ");
                                 oper.hi.spId = SPID_0;
                                 SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_SDOWN)
                                 ret = sbHitChkUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status  );
                                 setBit(&sbAccCb.curTst.bTickMask, BIT0);
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
                           if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                                 ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) &&
                                 ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE) )
                                 sbAccCb.curTst.tickLstDoneFlg = TRUE;
                     }
                     break;
            /* sb018.103: Added the test case for check bytes out is not
               going to nagative */
		case 11 :  /* O.305.11 expected result */
		        switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check DATA chunk */
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 2:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 3:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 4:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 5:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 6:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
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
            } /* end primitive received */
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
}  /* end sbDatTfSack_2 */

/*
*       Fun:   sbO306_01
*
*       Desc:  Test case : O.306.01
*              Purpose   : Verify that when the waiting queue is fuller than flcUpThr, flow control
*                          will be activated.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO306_01
(
void
)
#else
PUBLIC  S16 sbO306_01(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO306_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 5;
   sbDatTfCCntrl(curtstnum,"O.306.01");
   RETVALUE(ROK);
} /* end sbO306_01 */

/*
*       Fun:   sbO306_02
*
*       Desc:  Test case : O.306.02
*              Purpose   : Verify that when data is sent to a queue with activated flow control and
*                          the number of unSack'ed datagrams exceeds maxNmbTxChunks, the datagram
*                          will be dropped.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO306_02
(
void
)
#else
PUBLIC  S16 sbO306_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO306_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 6;
   sbDatTfCCntrl(curtstnum,"O.306.02");
   RETVALUE(ROK);
} /* end sbO306_02 */

/*
*       Fun:   sbO306_03
*
*       Desc:  Test case : O.306.03
*              Purpose   : Verify that when the waiting queue with activated flow control is emptier *                          than flcLowThr, flow control will be suspended.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO306_03
(
void
)
#else
PUBLIC  S16 sbO306_03(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO306_03)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 7;
   sbDatTfCCntrl(curtstnum,"O.306.03");
   RETVALUE(ROK);
} /* end sbO306_03 */



/*
*       Fun:   sbO306_04
*
*       Desc:  Test case : O.306.04
*              Purpose   : Verify that the awnd parameter in the SACK chunk limits the size of the
*                          congestion queue.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO306_04
(
void
)
#else
PUBLIC  S16 sbO306_04(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO306_04)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 4;
   sbDatTfCCntrl(curtstnum,"O.306.04");
   RETVALUE(ROK);
} /* end sbO306_04 */

/*
*       Fun:   sbDatTfCCntrl
*
*       Desc:  Data transfer acknowledgements tests.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act3.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDatTfCCntrl
(
U8   curtstnum,              /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDatTfCCntrl(curtstnum,numstr)
U8   curtstnum;              /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbAccMsgQElm  *msg;
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf;
   Buffer        *mBuf1;
   Buffer        *mBuf2;
   Buffer        *mBuf3;
   CmIpHdrParm   hdrParm;
   PRIVATE       SbAccChunkBld buildPar;             /* Parameters for building the chunks */
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbOperQElm    oper;
   Txt           prntBuf[64];

   TRC2(sbDatTfCCntrl)
   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)            /* Clean-up has been done */
   {
      if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
      {
         sbStdGenCfg(&sbMgmt);
         sbMgmt.t.cfg.s.genCfg.maxNmbTxChunks = 5;
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
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.flcUpThr = 3;
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.flcLowThr = 2;
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

   /*  flcUpThr = 3, flcLowThr = 2 and maxNmbTxChunks = 4 */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch(sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            SB_SETUP_DAT_REQ(mBuf)            /* Setup data buffer and other parameters for
                                                 data transmission */
            switch(curtstnum)
              {    /* Start switch(curtstnum) #1 */
              case 1:    /* Test O.306.01: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                       SPrint("Send data 1 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:   /* send DATA chunk */
                        SPrint("Send data 2 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:   /* send DATA chunk */
                       SPrint("Send data 3 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 4:   /* send DATA chunk */
                        /*-- RFC 4460 -- MLK Fix*/
                       SB_RLSMEM(mBuf);
                       if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                       (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                        /*-- RFC 4460 -- MLK Fix*/
                        SB_SETUP_DAT_REQ(mBuf); 
                           SPrint("Send data 4 \n ");
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId\
                                               ,assoc_1.spAssocId,\
                                              &assoc_1.priPeerNAddr,\
                                               ACC_STREAMID, ORDER, NOBUNDLE,\
                                              ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;/* reply event expected */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    default:
                       break;
                }
                break;
              case 2:    /* Test O.306.02: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /*306.02*/ /* send DATA chunk */
                       SPrint("Send data 1 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:  /*306.02*/  /* send DATA chunk */
                        SPrint("Send data 2 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:   /*306.02*/ /* send DATA chunk */
                       SPrint("Send data 3 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 4:  /*306.02*/  /* send DATA chunk */
                        /*-- RFC 4460 -- MLK Fix*/
                       SB_RLSMEM(mBuf);
                       if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                       (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                        /*-- RFC 4460 -- MLK Fix*/
                         SB_SETUP_DAT_REQ(mBuf); 
                           SPrint("Send data 4 \n ");
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                               assoc_1.spAssocId,\
                                              &assoc_1.priPeerNAddr,\
                                               ACC_STREAMID, ORDER, NOBUNDLE,\
                                              ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;/* reply event expected */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 5:
                        /*-- RFC 4460 -- MLK Fix*/
                        SB_RLSMEM(mBuf);
                       if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                           (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                        /*-- RFC 4460 -- MLK Fix*/
                        SB_SETUP_DAT_REQ(mBuf); 
                          SPrint("Send data 5 - TOO many \n ");
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                               assoc_1.spAssocId,\
                                               &assoc_1.priPeerNAddr,\
                                               ACC_STREAMID, ORDER, NOBUNDLE,\
                                               ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;/* reply event expected */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    default:
                       break;
                 }
                 break;
              case 3:    /* Test O.306.03: Execution */    /* use SACK of previous test */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /*306.03*/ /* send DATA chunk */
                       SPrint("Send data 1 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:  /*306.03*/  /* send DATA chunk */
                        SPrint("Send data 2 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:   /*306.03*/ /* send DATA chunk */
                       SPrint("Send data 3 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                            assoc_1.spAssocId,\
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 4:  /*306.03*/  /* send DATA chunk */
                        /*-- RFC 4460 -- MLK Fix*/
                        SB_RLSMEM(mBuf);
                       if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                       (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                        /*-- RFC 4460 -- MLK Fix*/
                        SB_SETUP_DAT_REQ(mBuf); 
                           SPrint("Send data 4 \n ");
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                               assoc_1.spAssocId,\
                                              &assoc_1.priPeerNAddr,\
                                               ACC_STREAMID, ORDER, NOBUNDLE,\
                                              ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;/* reply event expected */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 5:
                        /*-- RFC 4460 -- MLK Fix*/
                        SB_RLSMEM(mBuf);
                       if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                           (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                       {
                        /*-- RFC 4460 -- MLK Fix*/
                        SB_SETUP_DAT_REQ(mBuf); 
                          SPrint("Send data 5 - TOO many \n ");
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                               assoc_1.spAssocId,\
                                               &assoc_1.priPeerNAddr,ACC_STREAMID, \
                                               ORDER, NOBUNDLE,\
                                               ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                          sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;/* reply event expected */
                          sbAccCb.curTst.tickLstDoneFlg = FALSE;
                       }
                       break;
                    case 6:   /* send SACK chunk */
                       /*-- RFC 4460 -- MLK Fix*/
                       SB_RLSMEM(mBuf);
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       SPrint("Send SACK 1 \n ");
                       buildPar.numFrag = 0;
                       buildPar.arwnd = ACC_ARWND_INIT;
                       buildPar.cumTsn = buildPar.tsn;
                       buildSackChunk(mBuf1,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,\
                                              &assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);

                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf2);
                       SPrint("Send SACK 2 \n ");
                       buildPar.numFrag = 0;
                       buildPar.arwnd = ACC_ARWND_INIT;
                       buildPar.cumTsn = buildPar.tsn +1;
                       buildSackChunk(mBuf2,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                             &assoc_1.peerTAddr,\
                                              &assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf2);

                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf3);
                       SPrint("Send SACK 3 \n\n ");
                       buildPar.numFrag = 0;
                       buildPar.arwnd = ACC_ARWND_INIT;
                       buildPar.cumTsn = buildPar.tsn +2;
                       buildSackChunk(mBuf3,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                             &assoc_1.peerTAddr,\
                                             &assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                             mBuf3);
                       sbAccCb.curTst.evtType = ACC_EVT_FLC_IND;  /* reply event expected */
                       break;
                    default:
                       break;
                 }
                break;
              case 4:    /* Test O.306.04: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send datareq */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:   /* send SACK chunk */
                       buildPar.arwnd = 10;
                       buildPar.numFrag = 0;
                       buildPar.cumTsn = buildPar.tsn;
                       /*-- RFC 4460 -- MLK Fix*/
                       /*SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);*/
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                        SB_SETUP_IPHDR_PAR(NOFRAGM)
                       /* sb032.102 :  IPV6 Support Added */
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId, \
                                              &assoc_1.peerTAddr,\
                                              &assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_DAT_IND;  /* reply event expected */


                       SB_SETUP_DAT_REQ(mBuf1)
                      /* send datareq */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf1);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                       /*-- RFC 4460 -- MLK Fix*/
                    case 3:   /* send datareq */
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, \
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, \
                                            ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_NO_RESP;  /* reply event expected */
                       break;
                    default:
                       break;
                }
                break;
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
               if ( (sbAccCb.curTst.subTest == 3) && (curtstnum == 4) )
               {  sbAccCb.curTst.subTestsPass++;
               }
               else
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,\
                                      sbAccCb.curTst.evtType,\
                                      TIMEOUT_ON_PRIM, 0);
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
            }
            else
            { /* primitive received */
             reason = 0;
                switch(curtstnum)
                {    /* Start switch(curtstnum) #2 */
                   case 1:      /* Test O.306.01: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* check DATA chunk */
                            SPrint("Ready to received data 1 \n ");
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 2: /* check DATA chunk */
                            SPrint("Ready to received data 2 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 3: /* check DATA chunk */
                            SPrint("Ready to received data 3 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 4: /* check DATA chunk */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint("Ready to received data 4 \n ");
                               buildPar.chunkId = SB_ID_DATA;
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if (msg->evntType == ACC_EVT_FLC_IND)
                            {
                               /* check FlcInd  */
                               SB_SETUP_FLC_IND(assoc_1, SCT_FLC_START)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_FLC_IND,\
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
                         default:
                            break;
                      } /* end results of O.306.01 */
                      break;
                   case 2:      /* Test O.306.02: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* O.306.02 */ /* check DATA chunk */
                            SPrint("Ready to received data 1 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 2: /* O.306.02 */ /* check DATA chunk */
                            SPrint("Ready to received data 2 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 3:/* O.306.02 */  /* check DATA chunk */
                            SPrint("Ready to received data 3 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 4: /* O.306.02 */ /* check DATA chunk */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint("Ready to received data 4 \n ");
                               buildPar.chunkId = SB_ID_DATA;
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if (msg->evntType == ACC_EVT_FLC_IND)
                            {
                               /* check FlcInd  */
                               SB_SETUP_FLC_IND(assoc_1, SCT_FLC_START)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_FLC_IND,\
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
                         case 5:/* check FlcInd  */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_FLC_IND)
                            {  SPrint("FlcInd detected\n\n");
                               SB_SETUP_FLC_IND(assoc_1, SCT_FLC_DROP)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_FLC_IND,\
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
							}
							else if (msg->evntType == ACC_EVT_STA_IND)
							{
								SPrint("StaInd detected\n\n");
								oper.it.suId = assoc_1.suId;
								oper.it.suAssocId = assoc_1.suAssocId;
								oper.it.spAssocId = assoc_1.spAssocId;
								oper.it.status = SCT_STATUS_SND_FAIL;
								oper.it.cause = SCT_CAUSE_QFULL;
								/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
								oper.it.protId = ACC_PROT_ID;
#endif
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         default:
                            break;
                      } /* end results of O.306.02 */
                      break;
                  case 3:      /* Test O.306.03: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* O.306.03 */ /* check DATA chunk */
                            SPrint("Ready to received data 1 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 2: /* O.306.03 */ /* check DATA chunk */
                            SPrint("Ready to received data 2 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, \
                                                     &assoc_1, &status );
                            break;
                         case 3:/* O.306.03 */  /* check DATA chunk */
                            SPrint("Ready to received data 3 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 4: /* O.306.03 */ /* check DATA chunk */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_UDAT_REQ)
                            {  SPrint("Ready to received data 4 \n ");
                               buildPar.chunkId = SB_ID_DATA;
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               setBit(&sbAccCb.curTst.bTickMask, BIT0);
                            }
                            else if (msg->evntType == ACC_EVT_FLC_IND)
                            {
                               /* check FlcInd  */
                               SB_SETUP_FLC_IND(assoc_1, SCT_FLC_START)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_FLC_IND,\
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
                         case 5:/* check FlcInd  */
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_FLC_IND)
                            {  SPrint("FlcInd detected\n\n");
                               SB_SETUP_FLC_IND(assoc_1, SCT_FLC_DROP)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_FLC_IND,\
                                                 &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
							else if (msg->evntType == ACC_EVT_STA_IND)
							{
								SPrint("StaInd detected\n\n");
								oper.it.suId = assoc_1.suId;
								oper.it.suAssocId = assoc_1.suAssocId;
								oper.it.spAssocId = assoc_1.spAssocId;
								oper.it.status = SCT_STATUS_SND_FAIL;
								oper.it.cause = SCT_CAUSE_QFULL;
								/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
								oper.it.protId = ACC_PROT_ID;
#endif
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
                            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                               sbAccCb.curTst.tickLstDoneFlg = TRUE;
                            break;
                         case 6:
                            /* check FlcInd  */
                            SB_SETUP_FLC_IND(assoc_1, SCT_FLC_STOP)
                            ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_FLC_IND,\
                                              &status, &reason);
                            break;
                         default:
                            break;
                      } /* end results of O.306.03 */
                     break;
                  case 4:  /* Test O.306.04: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                      {
                         case 1: /* check DATA chunk */
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 2: /* check DATA chunk */
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
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
               }  /*End Subtest successful */
            } /*primitive receive end */

            if (sbAccCb.curTst.tickLstDoneFlg == TRUE)
            {
               sbAccCb.curTst.subTest++;
               sbAccCb.curTst.bTickMask = 0;
               sprintf(prntBuf, "Incr. subtest nr to : %u \n", sbAccCb.curTst.subTest);
               SPrint(prntBuf);
            }
            sbAccCb.curTst.state++;
            break;
         case 2: /* Do cleanup before next test */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst)
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test/subtest */
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
/*-- RFC 4460 -- MLK Fix */
    SB_RLSMEM(sbAccCb.curTst.gmBuf);
            break;
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbDatTfCCntrl */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN 
/*
*       Fun:   sbO307_01
*
*       Desc:  Test case : O.307.01
*              Purpose   : Verify that when ECN parameter is exchanged in INIT
*                          and INIT-ACK, ECT bit is set in the IP header of all
*                          the outgoing SCTP packets containing DATA chunks.

*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO307_01
(
void
)
#else
PUBLIC  S16 sbO307_01(void)
#endif
{
   U8 curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO307_01)

   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfECNCntrl(curtstnum,"O.307.01");
   RETVALUE(ROK);
} /* end sbO307_01 */

/*
*       Fun:   sbO307_02
*
*       Desc:  Test case : O.307.02
*              Purpose   : Verify that when SCTP packet containing DATA chunk
                           is received with CE bit set in the IP header,
                           ECNE chunk is bundled with the outgoing SACK.

*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO307_02
(
void
)
#else
PUBLIC  S16 sbO307_02(void)
#endif
{
   U8 curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO307_02)

   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfECNCntrl(curtstnum,"O.307.02");
   RETVALUE(ROK);
} /* end sbO307_02 */

/*
*       Fun:   sbO307_03
*
*       Desc:  Test case : O.307.03
*              Purpose   : Verify that when SCTP packet containing DATA chunk
*                          is received with CE bit set in the IP header,
*                          ECNE chunk is bundled with every outgoing SACK.
*
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO307_03
(
void
)
#else
PUBLIC  S16 sbO307_03(void)
#endif
{
   U8 curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO307_03)

   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfECNCntrl(curtstnum,"O.307.03");
   RETVALUE(ROK);
} /* end sbO307_03 */

/*
*       Fun:   sbO307_04
*
*       Desc:  Test case : O.307.04
*              Purpose   : Verify that when SCTP packet containing DATA chunk
*                          is received with CE bit set in the IP header,
*                          ECNE chunk is bundled with every outgoing SACK until
*                          CWR chunk is received.
*
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO307_04
(
void
)
#else
PUBLIC  S16 sbO307_04(void)
#endif
{
   U8 curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO307_04)

   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 4;
   sbDatTfECNCntrl(curtstnum,"O.307.04");
   RETVALUE(ROK);
} /* end sbO307_04 */

/*
*       Fun:   sbO307_05
*
*       Desc:  Test case : O.307.05
*              Purpose   : Verify that when ECNE chunk is received, CWR chunk
*                          is bundled and sent with the next outgoing new DATA
*                          chunk.
*
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO307_05
(
void
)
#else
PUBLIC  S16 sbO307_05(void)
#endif
{
   U8 curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO307_05)

   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 4;
   sbDatTfECNCntrl(curtstnum,"O.307.05");
   RETVALUE(ROK);
} /* end sbO307_05 */

/*
*       Fun:   sbO307_06
*
*       Desc:  Test case : O.307.06
*              Purpose   : Verify that when t3-rtx timer expire, CWR chunk is
*                          bundled and sent with the next outgoing new DATA
*                          chunk.
*
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO307_06
(
void
)
#else
PUBLIC  S16 sbO307_06(void)
#endif
{
   U8 curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO307_06)

   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 3;
   sbDatTfECNCntrl(curtstnum,"O.307.06");
   RETVALUE(ROK);
} /* end sbO307_06 */

/*
*       Fun:   sbO307_07
*
*       Desc:  Test case : O.307.07
*              Purpose   : Verify that when fast retransmission happens CWR
*                          chunk is bundled and sent with the next outgoing new 
*                          DATA chunk.
*
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbO307_07
(
void
)
#else
PUBLIC  S16 sbO307_07(void)
#endif
{
   U8 curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbO307_07)

   curtstnum = 7;
   sbAccCb.curTst.numSubTst = 7;
   sbDatTfECNCntrl(curtstnum,"O.307.07");
   RETVALUE(ROK);
} /* end sbO307_07 */

/* sb014.103: New test case for ECNE chunk */
/*
*       Fun:   sbO307_08
*
*       Desc:  Test case : O.307.08
*              Purpose   : Build and send the ECNE chunk without bundling
*                          with SACK chunk.
*
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/
                                                                                                                 
#ifdef ANSI
PUBLIC  S16 sbO307_08
(
void
)
#else
PUBLIC  S16 sbO307_08(void)
#endif
{
   U8 curtstnum;   /* number of the current test: eg. C.101.curtstnum */
                                                                                                                 
   TRC2(sbO307_08)
                                                                                                                 
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 2;
   sbDatTfECNCntrl(curtstnum,"O.307.08");
   RETVALUE(ROK);
} /* end sbO307_08 */

/* SATELLITE SCTP feature */
/* sb003.103 - addition - new function for ECN test cases. */
/*
*       Fun:   sbDatTfECNCntrl
*
*       Desc:  Explicit Congestion Notification test caes.
*       Ret:   ROK
*
*       Group: Data transfer
*
*       Notes:
*
*       File:  sb_act4.c
*
*/
#ifdef ANSI
PRIVATE  S16 sbDatTfECNCntrl
(
U8   curtstnum,   /* number of current test within test group (e.g. O.200.curtstnum) */
S8 *numstr        /* test number */
)
#else
PRIVATE  S16 sbDatTfECNCntrl(curtstnum,numstr)
U8   curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8 *numstr;       /* test number */
#endif
{
   SbAccMsgQElm  *msg;
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf;
   Buffer        *mBuf1;
   Buffer        *mBuf2;
   CmIpHdrParm   hdrParm;
   PRIVATE       SbAccChunkBld buildPar;   /* Parameters for building the chunks */
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbOperQElm    oper;
   Txt           prntBuf[64];

   TRC2(sbDatTfECNCntrl)

   ret = ROK;

   if(sbAccCb.curTst.bBusyPreTestConf)   /* Clean-up has been done */
   {
      if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )
      {
         sbStdGenCfg(&sbMgmt);
         sbMgmt.t.cfg.s.genCfg.maxNmbTxChunks = 10;
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
               if ((curtstnum == 6) || (curtstnum == 7))
               {
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMin =  ACC_RTO_SHORT;
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoMax =  ACC_RTO_SHORT;
                  sbMgmt.t.cfg.s.sctSapCfg.reConfig.rtoInitial  =  ACC_RTO_SHORT;
               }
               sbMgmt.t.cfg.s.sctSapCfg.reConfig.maxAckDelayDg = 1;
               sbSendConfigReq(&sbMgmt, STSBSCTSAP, SAP_1);
            }
/* SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
         if(isBitSet(sbAccCb.curTst.bConfigMask, BIT1) == FALSE )
         {                                                
           sbStdPathProfCfg(&sbMgmt);                           
           sbSendConfigReq(&sbMgmt, STSBPATHPROF, GEN);           
         }                                                 
         if ((isBitSet( sbAccCb.curTst.bConfigMask, BIT1) == TRUE) && (isBitSet( sbAccCb.curTst.bConfigMask, BIT2) == FALSE))
        {                                                 
          sbStdDstAddrCfg(&sbMgmt);                           
          sbSendConfigReq(&sbMgmt, STSBDSTADDR, GEN);           
        }                                                 
#endif        
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
                              SB_ENTERTEST(sbAccCb.curTst.bAssocMask, BIT0)
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
            SB_SETUP_DAT_REQ(mBuf)    /* Setup data buffer and other parameters
                                       * for data transmission
                                       */
            switch(curtstnum)
            {  /* Start switch(curtstnum) #1 */
               case 1:    /* Test O.307.01: Execution */
                  switch( sbAccCb.curTst.subTest)
                  {
                     case 1:   /* send DATA chunk */
                        SPrint("Send data 1 \n ");
                        (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                             assoc_1.spAssocId, \
                                             &assoc_1.priPeerNAddr,\
                                             ACC_STREAMID, ORDER, NOBUNDLE,\
                                             ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;

                     default:
                        break;
                  }
                  break;
              case 2:    /* Test O.307.02: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /*307.02*/ /* send DATA chunk */
                       SPrint("\n Send datagram\n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       buildPar.tsn = ACC_INIT_TSN;
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
                       {
                          hdrParm.u.hdrParmIpv4.tos.pres = TRUE;
                          hdrParm.u.hdrParmIpv4.tos.val = 0x1;
                       }
                       SB_SETUP_UNORDERED_DATA(ACC_INIT_TSN)
                       buildDataChunk (mBuf1,&buildPar,&assoc_1);
                       (void) HiUiHitUDatInd (&sbAccCb.hiPst, SUID_0, 
                                              assoc_1.suConId, &assoc_1.peerTAddr,
                                              &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;

                    default:
                       break;
                 }
                 break;

              case 3:    /* Test O.307.03: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /*307.03*/ /* send DATA chunk */
                       SPrint("\n Send datagram\n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       buildPar.tsn = ACC_INIT_TSN;
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
                       {
                          hdrParm.u.hdrParmIpv4.tos.pres = TRUE;
                          hdrParm.u.hdrParmIpv4.tos.val = 0x1;
                       }
                       SB_SETUP_UNORDERED_DATA(ACC_INIT_TSN)
                       buildDataChunk (mBuf1,&buildPar,&assoc_1);
                       (void) HiUiHitUDatInd (&sbAccCb.hiPst, SUID_0, 
                                              assoc_1.suConId, &assoc_1.peerTAddr,
                                              &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;

                    case 2:   /*307.03*/ /* send DATA chunk */
                       SPrint("\n Send datagram\n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       buildPar.tsn = ACC_INIT_TSN + 1;
                       buildPar.cumTsn = buildPar.tsn;
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
                       {
                          hdrParm.u.hdrParmIpv4.tos.pres = TRUE;
                          hdrParm.u.hdrParmIpv4.tos.val = 0x1;
                       }
                       SB_SETUP_UNORDERED_DATA(ACC_INIT_TSN + 1)
                       buildDataChunk (mBuf1,&buildPar,&assoc_1);
                       (void) HiUiHitUDatInd (&sbAccCb.hiPst, SUID_0, 
                                              assoc_1.suConId, &assoc_1.peerTAddr,
                                              &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;
                    default:
                       break;
                 }
                break;
              case 4:    /* Test O.307.04: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /*307.04*/ /* send DATA chunk */
                       SPrint("\n Send datagram 1\n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       buildPar.tsn = ACC_INIT_TSN;
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
                       {
                          hdrParm.u.hdrParmIpv4.tos.pres = TRUE;
                          hdrParm.u.hdrParmIpv4.tos.val = 0x1;
                       }
                       SB_SETUP_UNORDERED_DATA(ACC_INIT_TSN)
                       buildDataChunk (mBuf1,&buildPar,&assoc_1);
                       (void) HiUiHitUDatInd (&sbAccCb.hiPst, SUID_0, 
                                              assoc_1.suConId, &assoc_1.peerTAddr,
                                              &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;

                    case 2:   /*307.04*/ /* send DATA chunk */
                       SPrint("\n Send datagram 2 \n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       buildPar.tsn = ACC_INIT_TSN + 1;
                       buildPar.cumTsn = buildPar.tsn;
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       SB_SETUP_UNORDERED_DATA(ACC_INIT_TSN + 1)
                       buildDataChunk (mBuf1,&buildPar,&assoc_1);
                       (void) HiUiHitUDatInd (&sbAccCb.hiPst, SUID_0, 
                                              assoc_1.suConId, &assoc_1.peerTAddr,
                                              &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;
                    case 3:   /*307.04*/ /* send DATA chunk */
                       SPrint("\n Send datagram 3 \n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       buildPar.tsn = ACC_INIT_TSN + 2;
                       buildPar.cumTsn = buildPar.tsn;
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       SB_SETUP_UNORDERED_DATA(ACC_INIT_TSN + 2)
                       buildDataCwrChunk (mBuf1,&buildPar,&assoc_1);
                       (void) HiUiHitUDatInd (&sbAccCb.hiPst, SUID_0, 
                                              assoc_1.suConId, &assoc_1.peerTAddr,
                                              &assoc_1.localTAddr, &hdrParm, 
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);
                        sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                        break;
                    default:
                       break;
                 }
                 break;
              case 5:    /* Test O.307.05: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                       SPrint("Send data 1 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:   /* send SACK chunk */
                       SB_RLSMEM(mBuf);
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       SPrint("Send SACK and ECNE \n ");
                       buildPar.numFrag = 0;
                       buildPar.arwnd = ACC_ARWND_INIT;
                       buildPar.cumTsn = buildPar.tsn;
                       buildSackEcneChunk(mBuf1,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       (void) HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,\
                                              &assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);

                    break;

                    case 3:   /* send DATA chunk */
                       SPrint("Send data 2 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId,\
                                            assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,\
                                            ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;

                    default:
                       break;
                 }
                 break;
              case 6:    /* Test O.307.06: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                      if ((isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE) &&
                          (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) &&
                          (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE))
                      {
                          SPrint("Send data 1 \n ");
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId \
                                             ,&assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                             ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                         sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                      }
                      else if ((isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE) &&
                          (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
                      {
                          SPrint("Send data 2 \n ");
                          (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId \
                                             ,&assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                             ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                         sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                         sbAccCb.curTst.tickLstDoneFlg = FALSE;
                      }
                      break;
                 }
                 break;
              case 7:    /* Test O.307.07: Execution */
                 switch( sbAccCb.curTst.subTest)
                 {
                    case 1:   /* send DATA chunk */
                       SPrint("Send data 1 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 2:  
                       SPrint("Send data 2 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 3:
                       SPrint("Send data 3 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 4:
                       SPrint("Send data 4 \n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    case 5:
                       SPrint("Send SACK chunk 1 \n ");
                       SB_RLSMEM(mBuf)
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                       SB_SETUP_SACK_INFO(2, 2, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf);
                       SPrint("Send SACK chunk 2 \n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       SB_SETUP_SACK_INFO(2, 3, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf1,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf1);

                       SPrint("Send SACK chunk 3 \n ");
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf2);
                       SB_SETUP_SACK_INFO(2, 4, (buildPar.tsn-1) ) 
                       buildSackChunk(mBuf2,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,&assoc_1.localTAddr,\
                                              &hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                                mBuf2);

                       break;
                    case 6:
                       SPrint("Send data 4\n ");
                       (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                            &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                            ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                       sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
                       break;
                    default:
                       break;
                 }
                 break;
          /* sb014.103: New test case for ECNE chunk*/
            case 8:   /* O.307.08 Excecution */
                switch( sbAccCb.curTst.subTest)
                 {
                  case 1:
                       SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf1);
                       SPrint("Send ECNE chunk\n");
                       /* Build ECNE chunk */
                       buildEcneChunk(mBuf1,&buildPar,&assoc_1);
                       SB_SETUP_IPHDR_PAR(NOFRAGM)
                       (void) HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,\
                                              &assoc_1.peerTAddr,\
                                              &assoc_1.localTAddr,&hdrParm,
#ifdef LOCAL_INTF
                                              &assoc_1.localIf,
#endif
                                              mBuf1);
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
               /* sb014.103: New test case O.307.08 */
               if (((sbAccCb.curTst.subTest == 2) && (curtstnum == 5)) || ((sbAccCb.curTst.subTest == 1) && (curtstnum == 8)))
               {
                 sbAccCb.curTst.subTestsPass++;
                 sbAccCb.curTst.tickLstDoneFlg = TRUE;
               }
               else
               {
                  sbAccCb.curTst.subTestsFail++;
                  sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,\
                                      sbAccCb.curTst.evtType,\
                                      TIMEOUT_ON_PRIM, 0);
                  sbAccCb.curTst.bBusyPreTestConf = FALSE;
                  sbAccCb.curTst.bBusyCleanup = TRUE;
               }
            }
            else
            { /* primitive received */
               reason = 0;
               switch(curtstnum)
               {  /* Start switch(curtstnum) */
                  case 1:      /* Test O.307.01: Expected Results */
                     switch( sbAccCb.curTst.subTest)
                     {
                        case 1: /* check DATA chunk */
                           SPrint(" Ready to receive data 1 and Check if ECT \
                                    bit is set in the IP header\n ");
                           oper.hi.spId = SPID_0;
                           buildPar.chunkId = SB_ID_DATA;
                           ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                    &assoc_1, &status );
                           break;
                        default:
                           break;
                     } /* end results of O.307.01 */
                     break;
                   case 2:     /* Test O.307.02: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_DAT_IND)
                            {
                               SPrint(" Check Data Ind 1 \n ");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            SPrint("Ready to receive SACK 1 and ECNE chunk \n ");
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_SACK;
                            buildPar.expectEcne = TRUE;
                            buildPar.cumTsn = ACC_INIT_TSN;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            buildPar.expectEcne = FALSE;
                            break;

                      } /* end results of O.307.02 */
                      break;
                  case 3:      /* Test O.307.03: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_DAT_IND)
                            {
                               SPrint(" Check Data Ind 1 \n ");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            SPrint("Ready to receive SACK 1 and ECNE chunk \n ");
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_SACK;
                            buildPar.cumTsn = ACC_INIT_TSN;
                            buildPar.expectEcne = TRUE;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            buildPar.expectEcne = FALSE;
                            break;

                         case 2:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_DAT_IND)
                            {
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                               SPrint(" Check Data Ind 2 \n ");
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               SPrint("Ready to receive SACK 2 and ECNE chunk \n ");
                               oper.hi.spId = SPID_0;
                               buildPar.chunkId = SB_ID_SACK;
                               buildPar.cumTsn = ACC_INIT_TSN + 1;
                               buildPar.expectEcne = TRUE;
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               buildPar.expectEcne = FALSE;
                            }
                            break;

                      } /* end results of O.307.03 */
                      break;

                  case 4:      /* Test O.307.04: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_DAT_IND)
                            {
                               SPrint(" Check Data Ind 1 \n ");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                            }
                            SPrint("Ready to receive SACK 1 and ECNE \n ");
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_SACK;
                            buildPar.cumTsn = ACC_INIT_TSN;
                            buildPar.expectEcne = TRUE;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            buildPar.expectEcne = FALSE;
                            break;

                         case 2:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_DAT_IND)
                            {
                               SPrint(" Check Data Ind 2 \n ");
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               SPrint("Ready to receive SACK 2 and ECNE \n ");
                               oper.hi.spId = SPID_0;
                               buildPar.chunkId = SB_ID_SACK;
                               buildPar.cumTsn = ACC_INIT_TSN + 1;
                               buildPar.expectEcne = TRUE;
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                            }
                            break;
                         case 3:
                            sbAccPeekMsg(&msg);
                            if (msg->evntType == ACC_EVT_DAT_IND)
                            {
                               SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                               SPrint(" Check Data Ind 3 \n ");
                               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                               setBit(&sbAccCb.curTst.bTickMask, BIT1);
                               SPrint("Ready to receive SACK 3 and ECNE \n ");
                               oper.hi.spId = SPID_0;
                               buildPar.chunkId = SB_ID_SACK;
                               buildPar.cumTsn = ACC_INIT_TSN + 2;
                               buildPar.expectEcne = TRUE;
                               ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                        &assoc_1, &status );
                               buildPar.expectEcne = FALSE;
                            }
                            break;

                      } /* end results of O.307.04 */
                      break;
                  case 5:      /* Test O.307.05: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            SPrint("Ready to receive data 1 \n ");
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;

                         case 3:
                            SPrint("Ready to receive data 2 and CWR \n ");
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            buildPar.expectCwr = TRUE;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            buildPar.expectCwr = FALSE;
                            break;

                      } /* end results of O.307.05 */
                      break;
                  case 6:      /* Test O.307.06: Expected Results */
                     sbAccPeekMsg(&msg);
                     if ( (msg->evntType == ACC_EVT_UDAT_REQ) &&
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE) )
                     {
                        /* Check DATA chunk */
                        oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        SPrint("Ready to receive data 1 \n ");
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1,\
                                                   &status );
                        setBit(&sbAccCb.curTst.bTickMask, BIT2);
                     }
                     else if ((msg->evntType == ACC_EVT_UDAT_REQ) &&
                                 ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE) && 
                                 ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
                     {
                        /* Check retransmitted DATA chunk  */
                         oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        SPrint("Ready to receive data 2 -- retranmitted \n ");
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1,\
                                                   &status );
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     else if ((msg->evntType == ACC_EVT_UDAT_REQ) &&
                                 ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                     {
                         oper.hi.spId = SPID_0;
                        SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                        SPrint("Ready to receive data 3 and CWR \n ");
                        buildPar.expectCwr = TRUE;
                        ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1,\
                                                   &status );
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        buildPar.expectCwr = FALSE;
                     }
                     else
                     {
                        status = INC_EVNTTYPE;
                        setBit(&sbAccCb.curTst.bTickMask, BIT2);
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        ret = RFAILED;
                     }

                     if (( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                        (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) && 
                        (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE))
                        sbAccCb.curTst.tickLstDoneFlg = TRUE;
                     break;
                  case 7:      /* Test O.307.07: Expected Results */
                      switch( sbAccCb.curTst.subTest)
                      {
                         case 1:
                            /* Check DATA chunk */
                            oper.hi.spId = SPID_0;
                            SPrint("Ready to receive data 1 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            break;
                         case 2:
                            oper.hi.spId = SPID_0;
                            SPrint("Ready to receive data 2 \n ");
                            buildPar.chunkId = SB_ID_DATA;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 3:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            SPrint("Ready to receive data 3 \n ");
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 4:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            SPrint("Ready to receive data 4 \n ");
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 5:
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            SPrint("Ready to receive data 5 \n ");
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                            break;
                         case 6:
                            /* Check DATA chunk */
                            SPrint("Ready to receive data 6 and CWR \n ");
                            oper.hi.spId = SPID_0;
                            buildPar.chunkId = SB_ID_DATA;
                            buildPar.expectCwr = TRUE;
                            buildPar.lowestTsn = ACC_INIT_TSN;
                            ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                                     &assoc_1, &status );
                            buildPar.expectCwr = FALSE;
                            break;
                         default:
                            break;
                      }
                     break;
       /* sb014.103: New test case for ECNE chunk */
                case 8 : /* O.307.08 Expected result */
                    switch( sbAccCb.curTst.subTest) /* Excecution of O.307.08 */
                     {
                      case 1:
                           SPrint("Ooops, something arrived that I'm not expecting\n\n\n");
                           ret = RFAILED;
                          break;
                     }
                  break;
                }     /* End switch(curtstnum) */

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
               }  /*End Subtest successful */
            } /*primitive receive end */

            if (sbAccCb.curTst.tickLstDoneFlg == TRUE)
            {
               sbAccCb.curTst.subTest++;
               sbAccCb.curTst.bTickMask = 0;
               sprintf(prntBuf, "Incr. subtest nr to : %u \n", sbAccCb.curTst.subTest);
               SPrint(prntBuf);
            }
            sbAccCb.curTst.state++;
            break;
         case 2: /* Do cleanup before next test */
            if(sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst)
            {
               sbAccCb.curTst.bTestsCompleted = TRUE;
               sbAccCb.curTst.bBusySubtest = FALSE;  /* Done with a test/subtest */
               /* Now first delete all config before next test */
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
            sbAccCb.curTst.state = 0;   /* For delete config to work */
/*-- RFC 4460 -- MLK Fix */
            SB_RLSMEM(sbAccCb.curTst.gmBuf);
            break;
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if (sbAccCb.curTst.bBusyCleanup == TRUE)
      doCleanup();

   RETVALUE(ROK);
}  /* end sbDatTfECNCntrl */
#endif /* SB_ECN */






/********************************************************************30**

         End of file:     sb_act4.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:07 2015

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
                              UpGrade
/main/4      ---      rsr/ag   1. Updated for Release of 1.3
            sb003.103 ag   1. Satellite SCTP feature (under compile time
                              flags SB_ECN & SB_SATELLITE): Added ECN
                              related test cases.
            sb005.103 ag   1. IPV6 change.
            sb012.103 pkaX 1. Placed timer related test cases under the flag LSB12.
            sb014.103 pkaX 1. Memory leak Fix: Added New test case.
            sb018.103 pkaX 1. BytesOut issue: Added new test case.
/main/4     sb024.103 ajainx 1. Included protId parameter in status indication.
/main/4     sb030.103 krkX 1. Fixed the test case O.302.01.
/main/4     sb031.103 vsk  1. Modified the test cases O.300.01
/main/4     sb033.103 sdey 1. Modified to pass test case O.302.05. 
*********************************************************************91*/
