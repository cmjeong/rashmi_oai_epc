

/********************************************************************20**

     Name:     sb_act6.c - Acceptance Tests for the SCTP layer

     Type:     C source file

     Desc:     C code for acceptance tests test cases. Includes all the layer
               manager tests.

     File:     sb_act6.c

     Sid:      sb_act6.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:08 2015

     Prg:      nct

*********************************************************************21*/

/*

  sb_act6.c - Acceptance Tests for the SCTP layer

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
PRIVATE S16 sbSctStatisticsRequestTst  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE S16 sbSctStatusRequestTst  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE S16 sbSctEnableDisableAlarmsTst  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE S16 sbSctEnableDisableMessageTraceTst  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE S16 sbSctEnableDisableDebugPrintsTst  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE S16 sbSctShutdownOperationsTst  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE S16 sbSctDeleteTsapSctsapTst  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE S16 sbMainTrcIndTst  ARGS((U8  curtstnum, S8  *numstr));
/* SATELLITE SCTP feature */ 
/* sb003.103 - addition - */
#ifdef SB_SATELLITE
PRIVATE S16 sbDeletePathProfTst  ARGS((U8  curtstnum, S8  *numstr));
PRIVATE S16 sbDeleteDstAddrTst  ARGS((U8  curtstnum, S8  *numstr));
#endif /* SB_SATELLITE */

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */

/*
*       Fun:   sbM200_01
*
*       Desc:  Test case : M.200.01
*              Purpose   : Verify successful general status request
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM200_01
(
void
)
#else
PUBLIC  S16 sbM200_01(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM200_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatusRequestTst(curtstnum,"M.200.01");
   RETVALUE(ROK);
} /* end sbM200_01 */

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbM200_02
*
*       Desc:  Test case : M.200.02
*              Purpose   : Verify successful general status request for IPV6
*                          address
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM200_02
(
void
)
#else
PUBLIC  S16 sbM200_02(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM200_02)
   curtstnum = 9;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctStatusRequestTst(curtstnum,"M.200.02");
   RETVALUE(ROK);
} /* end sbM200_02 */

/*
*       Fun:   sbM201_01
*
*       Desc:  Test case : M.201.01
*              Purpose   : Verify successful association status request
*                          if element is invalid
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM201_01
(
void
)
#else
PUBLIC  S16 sbM201_01(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM201_01)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatusRequestTst(curtstnum,"M.201.01");
   RETVALUE(ROK);
} /* end sbM201_01 */

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbM201_02
*
*       Desc:  Test case : M.201.02
*              Purpose   : Verify successful association status request
*                          if element is invalid for IPV6 address
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM201_02
(
void
)
#else
PUBLIC  S16 sbM201_02(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM201_02)
   curtstnum = 10;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctStatusRequestTst(curtstnum,"M.201.02");
   RETVALUE(ROK);
} /* end sbM201_02 */

/*
*       Fun:   sbM202_01
*
*       Desc:  Test case : M.202.01
*              Purpose   : Verify successful data status request.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM202_01
(
void
)
#else
PUBLIC  S16 sbM202_01(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM202_01)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatusRequestTst(curtstnum,"M.202.01");
   RETVALUE(ROK);
} /* end sbM202_01 */

/* sb032.102 :  IPV6 Support Added */
/*
*       Fun:   sbM202_02
*
*       Desc:  Test case : M.202.02
*              Purpose   : Verify successful data status request for IPV6 addr
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM202_02
(
void
)
#else
PUBLIC  S16 sbM202_02(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM202_02)
   curtstnum = 11;
   sbAccCb.curTst.numSubTst = 2;
   sbAccCb.curTst.addrType = CM_NETADDR_IPV6;
   sbSctStatusRequestTst(curtstnum,"M.202.02");
   RETVALUE(ROK);
} /* end sbM202_02 */

/*
*       Fun:   sbM203_01
*
*       Desc:  Test case : M.203.01
*              Purpose   : Verify successful SCTSAP status request.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM203_01
(
void
)
#else
PUBLIC  S16 sbM203_01(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM203_01)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatusRequestTst(curtstnum,"M.203.01");
   RETVALUE(ROK);
} /* end sbM203_01 */

/*
*       Fun:   sbM203_02
*
*       Desc:  Test case : M.203.02
*              Purpose   : Verify unsuccessful SCTSAP status request if
*                          the sapId is incorrect.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM203_02
(
void
)
#else
PUBLIC  S16 sbM203_02(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM203_01)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatusRequestTst(curtstnum,"M.203.02");
   RETVALUE(ROK);
} /* end sbM203_01 */

/*
*       Fun:   sbM204_01
*
*       Desc:  Test case : M.204.01
*              Purpose   : Verify successful TSAP status request.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM204_01
(
void
)
#else
PUBLIC  S16 sbM204_01(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM204_01)
   curtstnum = 6;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatusRequestTst(curtstnum,"M.204.01");
   RETVALUE(ROK);
} /* end sbM204_01 */

/*
*       Fun:   sbM204_02
*
*       Desc:  Test case : M.204.02
*              Purpose   : Verify unsuccessful TSAP status request if the
*                          sapId is incorrect.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM204_02
(
void
)
#else
PUBLIC  S16 sbM204_02(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM204_01)
   curtstnum = 7;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatusRequestTst(curtstnum,"M.204.02");
   RETVALUE(ROK);
} /* end sbM204_01 */

/*
*       Fun:   sbM205_01
*
*       Desc:  Test case : M.205.01
*              Purpose   : Verify successful system Id status request.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM205_01
(
void
)
#else
PUBLIC  S16 sbM205_01(void)
#endif
{
   U8          curtstnum;/* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM205_01)
   curtstnum = 8;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatusRequestTst(curtstnum,"M.205.01");
   RETVALUE(ROK);
} /* end sbM204_01 */

/*
*       Fun:   sbSctStatusRequestTst
*
*       Desc:  Enable/Disable Alarms.
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctStatusRequestTst
(
U8   curtstnum,/* number of current test within test group */
S8  *numstr  /* test number */
)
#else
PRIVATE S16 sbSctStatusRequestTst(curtstnum, numstr)
U8   curtstnum; /* number of current test within test group  */
S8  *numstr; /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbAccAssoc    assoc_2;
   PRIVATE       SbAccChunkBld buildPar;
   /* sb032.102 :  IPV6 Support Added */
   U8            ipv6Addr[16];

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   TRC2(  sbSctStatusRequestTst)
   /* Pretests/Setup: open 2 endpoints */
   if(sbAccCb.curTst.bBusyPreTestConf)  /* Clean-up has been done */
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
                     setupAssoc(&assoc_1, ASSOC_1);
                     if (isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == TRUE)
                     {
                        SB_EST_ASSOC(assoc_1, BIT0)
                        if (isBitSet(sbAccCb.curTst.bAssocMask, BIT0) == TRUE)
                        {
                           if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
                           {
                              SB_SETUP_ENDPOPENREQ(assoc_2, SPID_0, SUENDPID_1,\
                                                LOCALPORT_1, \
                                                localNAddrLst_1[1])
                           }
                           /* sb032.102 :  IPV6 Support Added */
                           else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
                           {
                              CPY_ACC_ASSOC1_LOCAL_IPV6(ipv6Addr, 1)
                              SB_SETUP_ENDPOPENREQ(assoc_2, SPID_0, SUENDPID_1, LOCALPORT_1, ipv6Addr)  
                           }

                           SB_OPEN_ENDP(&assoc_2, BIT1)
                           SB_ENTERTEST( sbAccCb.curTst.bEndpMask, BIT1 )
                        } /*end Assoc Setup mask */
                     }  /*end AssocSetup end  */
                  } /* Bind TSap end of if*/
               } /* TSapCfg end of if*/
            } /* SctSapCfg end of if */
         } /* end DebugP */
      } /* config end of if */
   } /* end pretesConf */

   /* Initialize the sbMgmt structure */
   cmMemset((U8 *)&sbMgmt, 0, sizeof(sbMgmt));

   /* Do test */
   if ( sbAccCb.curTst.bBusySubtest ) {
      switch ( sbAccCb.curTst.state )   /* Switch #1 */
      {
      case 0:
         switch ( curtstnum ) {    /* Start switch(curtstnum) #1 */
         case 1:    /* Test M.200.01: Execution (status request STSBGEN)   */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20001;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.hdr.elmId.elmnt = STSBGEN;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 2:    /* Test M.201.01: Execution (status request STSBASSOC) */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20101;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.t.ssta.sapId = assoc_1.spId;
            sbMgmt.t.ssta.s.assocSta.assocId  = assoc_1.spAssocId;
            sbMgmt.hdr.elmId.elmnt = STSBASSOC;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 3:    /* Test M.202.01: Execution (status request STSBDTA)   */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20201;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.t.ssta.sapId = assoc_1.spId;
            sbMgmt.t.ssta.s.dtaSta.dstNAddr = assoc_1.priPeerNAddr;
            sbMgmt.t.ssta.s.dtaSta.dstPort = assoc_1.peerPort;
            sbMgmt.t.ssta.s.dtaSta.assocId = assoc_1.spAssocId;
            sbMgmt.hdr.elmId.elmnt = STSBDTA;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 4:    /* Test M.203.01: Execution (status request STSBSCTSAP) */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20301;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.t.ssta.sapId = assoc_1.spId;
            sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 5:    /* Test M.203.02: Execution (status request STSBSCTSAP) */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20302;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.t.ssta.sapId = SPID_2;
            sbMgmt.hdr.elmId.elmnt =  STSBSCTSAP;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 6:    /* Test M.204.01: Execution (status request STSBTSAP)   */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20401;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.t.ssta.sapId = assoc_1.suId;
            sbMgmt.hdr.elmId.elmnt = STSBTSAP;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 7:    /* Test M.204.02: Execution (status request STSBTSAP)   */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20402;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.t.ssta.sapId = SUID_2;
            sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 8:    /* Test M.205.01: Execution (status request STSBSID)   */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20501;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.hdr.elmId.elmnt = STSBSID;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         /* sb032.102 :  IPV6 Support Added */
         case 9:    /* Test M.200.02: Execution (status request STSBGEN)   */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20002;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.hdr.elmId.elmnt = STSBGEN;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 10:    /* Test M.201.02: Execution (status request STSBASSOC) */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20102;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.t.ssta.sapId = assoc_1.spId;
            sbMgmt.t.ssta.s.assocSta.assocId  = assoc_1.spAssocId;
            sbMgmt.hdr.elmId.elmnt = STSBASSOC;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         case 11:    /* Test M.202.02: Execution (status request STSBDTA)   */
            setResponse(&sbMgmt.hdr.response);
            sbMgmt.hdr.transId = 20202;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.t.ssta.sapId = assoc_1.spId;
            sbMgmt.t.ssta.s.dtaSta.dstNAddr = assoc_1.priPeerNAddr;
            sbMgmt.t.ssta.s.dtaSta.dstPort = assoc_1.peerPort;
            sbMgmt.t.ssta.s.dtaSta.assocId = assoc_1.spAssocId;
            sbMgmt.hdr.elmId.elmnt = STSBDTA;
            (Void) SmMiLsbStaReq(&sbAccCb.smPst, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STA_CFM; /*expected response  */
            break;
         }
         sbAccCb.curTst.state++;
         break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg( &status );
         if ( status == WAIT ) {   /* wait for message to reach the queue */
            RETVALUE( ROK );
         }
         else if ( status == TIMEOUT ) {
            sbAccCb.curTst.subTestsFail++;
            sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
               ACC_EVT_CNTRL_CFM, TIMEOUT_ON_PRIM, 0 );
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
             case 1:    /* Test M.200.01: Expected Results  */
                /* subtest pass if  OK and number of endpoints == 2 */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                if (mgmt.s.ssta.s.genSta.nmbEndp != 2)
                {
                  ret    = RFAILED;
                  status = INC_ENDP_ID;
                }
                break;
             case 2:    /* Test M.201.01: Expected Results  */
                /* subtest pass if  OK and assocState is ESTABLISHED */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                if (mgmt.s.ssta.s.assocSta.assocState != SB_ST_ESTABLISHED)
                {
                  ret    = RFAILED;
                  status = INC_ASSOC_ID;
                }
                break;
             case 3:    /* Test M.202.01: Expected Results  */
                /* subtest pass if  OK and the path is ACTIVE  */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                if (mgmt.s.ssta.s.dtaSta.state != SCT_PATH_ACTIVE)
                {
                  ret    = RFAILED;
                  status = INV_STATE;
                }
                break;
             case 4:    /* Test M.203.01: Expected Results  */
                /* subtest pass if OK and SAP state bound*/
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                if (mgmt.s.ssta.s.sapSta.hlSt !=  SB_SAPSTATE_BND)
                {
                  ret    = RFAILED;
                  status = INC_SAP;
                }
                break;
             case 5:    /* Test M.203.02: Expected Results  */
                /* subtest pass if NOK */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                break;
             case 6:    /* Test M.204.01: Expected Results  */
                /* subtest pass if OK and SAP bound */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                if (mgmt.s.ssta.s.sapSta.hlSt !=  SB_SAPSTATE_BND)
                {
                  ret    = RFAILED;
                  status = INV_STATE;
                }
                break;
             case 7:    /* Test M.204.02: Expected Results  */
                /* subtest pass if NOK */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                break;
             case 8:    /* Test M.205.01: Expected Results  */
                /* subtest pass if OK */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                break;
             /* sb032.102 :  IPV6 Support Added */
             case 9:    /* Test M.200.02: Expected Results  */
                /* subtest pass if  OK and number of endpoints == 2 */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                if (mgmt.s.ssta.s.genSta.nmbEndp != 2)
                {
                  ret    = RFAILED;
                  status = INC_ENDP_ID;
                }
                break;
             case 10:    /* Test M.201.02: Expected Results  */
                /* subtest pass if  OK and assocState is ESTABLISHED */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                if (mgmt.s.ssta.s.assocSta.assocState != SB_ST_ESTABLISHED)
                {
                  ret    = RFAILED;
                  status = INC_ASSOC_ID;
                }
                break;
             case 11:    /* Test M.202.02: Expected Results  */
                /* subtest pass if  OK and the path is ACTIVE  */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_CFM);
                if (mgmt.s.ssta.s.dtaSta.state != SCT_PATH_ACTIVE)
                {
                  ret    = RFAILED;
                  status = INV_STATE;
                }
                break;
             }

            if ( ret == RFAILED )
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                  ACC_EVT_CNTRL_CFM, status, reason );
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
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         break;
      case 2: /* Do cleanup before next test */
         if ( sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
         {
            sbAccCb.curTst.bTestsCompleted = TRUE;
            sbAccCb.curTst.bBusySubtest = FALSE; /*Done with a test/subtest */
            /* Now first delete all config before next test */
            sbAccCb.curTst.bBusyCleanup = TRUE;
         }
         sbAccCb.curTst.state = 0;   /* For delete config to work */
         break;
      } /* end switch #1*/
   }   /*end bBusySubtest */

   /* Cleanup configuration before next test */
   if ( sbAccCb.curTst.bBusyCleanup == TRUE )
      doCleanup( );

   RETVALUE( ROK );
}  /* end sbSctStatusRequestTst */



/*
*       Fun:   sbM100_01
*
*       Desc:  Test case : M.100.01
*              Purpose   : Verify clearing of statistical counters
*
*       Ret:   ROK
*
*       Group: Statistics
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM100_01
(
void
)
#else
PUBLIC  S16 sbM100_01(void)
#endif
{
   U8          curtstnum;  /* number of the current test */

   TRC2(sbM100_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 3;
   sbSctStatisticsRequestTst(curtstnum,"M.100.01");
   RETVALUE(ROK);
} /* end sbM100_01 */


/*
*       Fun:   sbM100_02
*
*       Desc:  Test case : M.100.02
*              Purpose   : Verify send of DatReq packet
*
*       Ret:   ROK
*
*       Group: Statistics
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM100_02
(
void
)
#else
PUBLIC  S16 sbM100_02(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM100_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 4;
   sbSctStatisticsRequestTst(curtstnum,"M.100.02");
   RETVALUE(ROK);
} /* end sbM100_02 */


/*
*       Fun:   sbM101_01
*
*       Desc:  Test case : M.101.01
*              Purpose   : Verify that the statistic structure may be cleared
*                          when action = ZEROSTS
*       Ret:   ROK
*
*       Group: Statistics
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM101_01
(
void
)
#else
PUBLIC  S16 sbM101_01(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM101_01)
   curtstnum = 3;
   sbAccCb.curTst.numSubTst = 3;
   sbSctStatisticsRequestTst(curtstnum,"M.101.01");
   RETVALUE(ROK);
} /* end sbM101_01 */


/*
*       Fun:   sbM101_02
*
*       Desc:  Test case : M.101.02
*              Purpose   : Verify that INIT chunk is sent for AssocReq
*
*       Ret:   ROK
*
*       Group: Statistics
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM101_02
(
void
)
#else
PUBLIC  S16 sbM101_02(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM101_02)
   curtstnum = 4;
   sbAccCb.curTst.numSubTst = 4;
   sbSctStatisticsRequestTst(curtstnum,"M.101.02");
   RETVALUE(ROK);
} /* end sbM101_02 */


/*
*       Fun:   sbM101_03
*
*       Desc:  Test case : M.101.03
*              Purpose   : Verify unsuccessful send of DatReq packet when
*                          SAP id invalid
*       Ret:   ROK
*
*       Group: Statistics
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM101_03
(
void
)
#else
PUBLIC  S16 sbM101_03(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM101_03)
   curtstnum = 5;
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatisticsRequestTst(curtstnum,"M.101.03");
   RETVALUE(ROK);
} /* end sbM101_03 */

/*
*       Fun:   sbM102_01
*
*       Desc:  Test case : M.102.01
*              Purpose   : Verify TSAP statistics may be cleared.
*
*       Ret:   ROK
*
*       Group: Statistics
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM102_01
(
void
)
#else
PUBLIC  S16 sbM102_01(void)
#endif
{

   TRC2(sbM102_01)
   sbAccCb.curTst.numSubTst = 3;
   sbSctStatisticsRequestTst(6,"M.102.01");
   RETVALUE(ROK);
} /* end sbM102_01 */


/*
*       Fun:   sbM102_02
*
*       Desc:  Test case : M.102.02
*              Purpose   : Verify TSAP statistics.
*
*       Ret:   ROK
*
*       Group: Statistics
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM102_02
(
void
)
#else
PUBLIC  S16 sbM102_02(void)
#endif
{

   TRC2(sbM102_02)
   sbSctStatisticsRequestTst(7,"M.102.02");
   RETVALUE(ROK);
} /* end sbM102_02 */

/*
*       Fun:   sbM102_03
*
*       Desc:  Test case : M.102.03
*              Purpose   : Verify TSAP statistics may be acquired with success.
*
*       Ret:   ROK
*
*       Group: Statistics
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM102_03
(
void
)
#else
PUBLIC  S16 sbM102_03(void)
#endif
{
   TRC2(sbM102_03)
   sbAccCb.curTst.numSubTst = 2;
   sbSctStatisticsRequestTst(8,"M.102.03");
   RETVALUE(ROK);
} /* end sbM102_03 */



/*
*       Fun:   sbSctStatisticsRequestTst
*
*       Desc:  Enable/Disable Alarms.
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctStatisticsRequestTst
(
U8   curtstnum, /* number of current test within test group */
S8  *numstr        /* test number */
)
#else
PRIVATE S16 sbSctStatisticsRequestTst(curtstnum, numstr)
U8   curtstnum; /* number of current test within test group */
S8  *numstr;       /* test number */
#endif
{
   SbAccMsgQElm  *msg;
   SbMgmtQElm    mgmt;
   PRIVATE       SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbAccChunkBld buildPar;
   Buffer        *mBuf;
   CmNetAddr     dfltPriPeerNAddr;
   PRIVATE       SbOperQElm    oper;

   TRC2(  sbSctStatisticsRequestTst)

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;


       /* Pretests/Setup */
   if(sbAccCb.curTst.bBusyPreTestConf)      /* Clean-up has been done */
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
                               SB_TSAPCFG(SAP_2)
                               SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT1 )
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
   if ( sbAccCb.curTst.bBusySubtest ) {
      switch ( sbAccCb.curTst.state )   /* Switch #1 */
      {
      case 0:
         switch ( curtstnum )
         {    /* Start switch(curtstnum) #1 */
         case 1:    /* Test M.100.01: Execution (status request STSBGEN)   */
            sbMgmt.hdr.transId = 10001;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.hdr.elmId.elmnt = STSBGEN;
            sbMgmt.t.sts.sapId = assoc_1.spId;
            (Void) SbMiLsbStsReq(&sbAccCb.smPst, ZEROSTS, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
            break;
         case 2:   /* M.100.02 Execution */
            switch ( sbAccCb.curTst.subTest )
            {
            case 1:
               sbMgmt.hdr.transId = 100021;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               sbMgmt.hdr.elmId.elmnt = STSBGEN;
               sbMgmt.t.sts.sapId = assoc_1.spId;
               (Void) SbMiLsbStsReq(&sbAccCb.smPst, ZEROSTS, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
               break;
            case 2:
               /* Send a DatReq packet */
               SB_SETUP_DAT_REQ(mBuf)
               dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
               sbMgmt.hdr.elmId.elmnt          = STSBDTA;
               (Void) SbUiSctDatReq(&sbAccCb.smPst, assoc_1.spId, assoc_1.spAssocId, \
                                    &assoc_1.priPeerNAddr, ACC_STREAMID, ORDER, \
                                    NOBUNDLE, ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
               sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ; /*expected response  */
               break;
            case 3:
               sbMgmt.hdr.transId = 100023;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               sbMgmt.hdr.elmId.elmnt = STSBGEN;
               sbMgmt.t.sts.sapId = assoc_1.spId;
               (Void) SbMiLsbStsReq(&sbAccCb.smPst,NOZEROSTS, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
               break;
            }
            break;
         case 3:    /* Test M.101.01: Execution (status request STSBSCTSAP)   */
            sbMgmt.hdr.transId = 10101;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
            sbMgmt.t.sts.sapId = assoc_1.spId;
            (Void) SbMiLsbStsReq(&sbAccCb.smPst, ZEROSTS, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
            break;
         case 4:   /* M.101.02 Execution */
            switch ( sbAccCb.curTst.subTest )
            {
            case 1:
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = 101021;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
               sbMgmt.t.sts.sapId = assoc_1.spId;
               (Void) SmMiLsbStsReq(&sbAccCb.smPst, ZEROSTS, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
               break;
            case 2:
               SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other parameters for
                                                 data transmission */
               (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                    &assoc_1.priPeerNAddr,ACC_STREAMID, ORDER, NOBUNDLE,\
                                    ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
               sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;  /* reply event expected */
               break;
            case 3:
               sbMgmt.hdr.transId = 101023;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
               sbMgmt.t.sts.sapId   = assoc_1.spId;
               (Void) SbMiLsbStsReq(&sbAccCb.smPst, NOZEROSTS, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
               break;
            }
            break;
         case 5:   /* M.101.03 Execution (Incorrect SAP Id)*/
            sbMgmt.hdr.transId = 10103;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;
            sbMgmt.t.sts.sapId = SPID_1;
            (Void) SbMiLsbStsReq(&sbAccCb.smPst, NOZEROSTS, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
            break;
         case 6:    /* Test M.102.01: Execution (status request STSBTSAP)   */
            sbMgmt.hdr.transId = 10201;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.hdr.elmId.elmnt = STSBTSAP;
            sbMgmt.t.sts.sapId = assoc_1.suId;
            (Void) SbMiLsbStsReq(&sbAccCb.smPst, ZEROSTS, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
            break;
         case 7:   /* M.102.02 Execution */
            sbAccCb.curTst.numSubTst = (U8)(sbMgmt.t.cfg.s.tSapCfg.reConfig.maxBndRetry + 3);
            if ( sbAccCb.curTst.subTest == 1 )
            {
               sbMgmt.hdr.transId = 102021;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               sbMgmt.hdr.elmId.elmnt = STSBTSAP;
               sbMgmt.t.sts.sapId = SUID_1;
               (Void) SbMiLsbStsReq(&sbAccCb.smPst, ZEROSTS, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
            }
            else if (sbAccCb.curTst.subTest == 2 )
            {
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                  (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
               {
                  sbMgmt.t.cntrl.sapId =  SUID_1;
                  sbMgmt.hdr.transId = 102022;
                  sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                  sbMgmt.t.cntrl.action = ABND_ENA;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                  (Void) SbMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                  sbAccCb.curTst.tickLstDoneFlg = FALSE;
               }
            }
            else  if (sbAccCb.curTst.subTest <= (sbAccCb.curTst.numSubTst-3) )
            {
                  sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;   /* expected result */
            }
            else  if (sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-2) )
            {
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                  (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
               {
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;   /* expected result */
                  sbAccCb.curTst.tickLstDoneFlg = FALSE;
               }
            } else if ( sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1) ) {
               sbMgmt.hdr.transId = 102023;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               sbMgmt.hdr.elmId.elmnt = STSBTSAP;
               sbMgmt.t.sts.sapId = SUID_1;
               (Void) SbMiLsbStsReq(&sbAccCb.smPst, NOZEROSTS, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
            }
            break;
         case 8:   /* M.101.03 Execution (Incorrect SAP Id)*/
            sbMgmt.hdr.transId = 10103;
            sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
            sbMgmt.hdr.elmId.elmnt = STSBTSAP;
            sbMgmt.t.sts.sapId = SUID_2;
            (Void) SbMiLsbStsReq(&sbAccCb.smPst, NOZEROSTS, &sbMgmt);
            sbAccCb.curTst.evtType = ACC_EVT_STS_CFM; /*expected response  */
            break;
         }
         sbAccCb.curTst.state++;
         break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg( &status );
         if ( status == WAIT )
         {   /* wait for message to reach the queue */
            RETVALUE( ROK );
         }
         else if ( status == TIMEOUT )
         {
            sbAccCb.curTst.subTestsFail++;
            sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
               ACC_EVT_CNTRL_CFM, TIMEOUT_ON_PRIM, 0 );
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
             case 1:    /* Test M.100.01: Expected Results  */
                /* subtest pass if  OK */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);

                /* The second time the counters must all be ZERO */
                if (sbAccCb.curTst.subTest == 2) {
                   if (
                         mgmt.s.sts.u.genSts.sbChunkSts.noInitTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noInitReTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noInitRx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noIAckTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noIAckRx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noShDwnTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noShDwnReTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noShDwnRx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noShDwnAckTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noShDwnAckRx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noCookieTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noCookieReTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noCookieRx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noCkAckTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noCkAckRx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noDataTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noDataReTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noDataRx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noDAckTx
                      |  mgmt.s.sts.u.genSts.sbChunkSts.noDAckRx
/* sb019.102 Heartbeat statistics added */
#ifdef LSB2
                      | mgmt.s.sts.u.genSts.sbChunkSts.noHBeatTx
                      | mgmt.s.sts.u.genSts.sbChunkSts.noHBeatRx
                      | mgmt.s.sts.u.genSts.sbChunkSts.noHBAckTx
                      | mgmt.s.sts.u.genSts.sbChunkSts.noHBAckRx
#endif
/* sb052.102 Abort statistics added */
#ifdef LSB3
                      | mgmt.s.sts.u.genSts.sbChunkSts.noAbortTx
                      | mgmt.s.sts.u.genSts.sbChunkSts.noAbortRx
#endif
/* sb068.102 Error statistics added */
#ifdef LSB6
                      | mgmt.s.sts.u.genSts.sbChunkSts.noErrorTx
                      | mgmt.s.sts.u.genSts.sbChunkSts.noErrorRx
#endif/* LSB6 */

                      |  mgmt.s.sts.u.genSts.sbByteSts.bytesTx
                      |  mgmt.s.sts.u.genSts.sbByteSts.bytesRx
                      )
                   {
                      ret    = RFAILED;
                      status = STS_CNTR_NOT_ZERO;
                   }
                }
                break;

             case 2:    /* Test M.100.02: Expected Results  */
                switch ( sbAccCb.curTst.subTest )
                {
                case 1:
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);
                   break;
                case 2:
                   /* Check DATA chunk */
                   oper.hi.spId = SPID_0;
                   SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                   ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                   break;
                case 3:
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);
                   if (mgmt.s.sts.u.genSts.sbChunkSts.noDataTx != 1)
                   {
                      status = INC_STSCNTR;
                      ret = RFAILED;
                   }
                   break;
                }
                break;
             case 3:    /* Test M.101.01: Expected Results  */
                /* subtest pass if  OK */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);

                /* The second time the counters must all be ZERO */
                if (sbAccCb.curTst.subTest == 2) {
                   if (
                      mgmt.s.sts.u.sctSts.sbByteSts.bytesTx
                      |  mgmt.s.sts.u.sctSts.sbByteSts.bytesRx
                      )
                   {
                      ret    = RFAILED;
                      status = STS_CNTR_NOT_ZERO;
                   }
                }
                break;
             case 4:    /* Test M.101.02: Expected Results  */
                switch ( sbAccCb.curTst.subTest )
                {
                case 1:
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);
                   break;
                case 2:
                   oper.hi.spId = SPID_0;
                   buildPar.chunkId = SB_ID_DATA;
                   ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar, &assoc_1, &status );
                   break;
                case 3:
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);
                   if (mgmt.s.sts.u.sctSts.sbByteSts.bytesRx == 0)
                   {
                      status = INC_STSCNTR;
                      ret = RFAILED;
                   }
                   break;
                }
                break;
             case 5:     /* Test M.101.03: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);
                break;
             case 6:    /* Test M.102.01: Expected Results  */
                /* subtest pass if  OK */
                mgmt.cfm.status = LCM_PRIM_OK;
                mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);

                /* The second time the counters must all be ZERO */
                if (sbAccCb.curTst.subTest == 2) {
                   if (
                         mgmt.s.sts.u.tSts.sbChunkSts.noInitTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noInitReTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noInitRx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noIAckTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noIAckRx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noShDwnTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noShDwnReTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noShDwnRx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noShDwnAckTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noShDwnAckRx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noCookieTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noCookieReTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noCookieRx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noCkAckTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noCkAckRx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noDataTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noDataReTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noDataRx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noDAckTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noDAckRx
/* sb019.102 Heartbeat statistics added */
#ifdef LSB2
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noHBeatTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noHBeatRx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noHBAckTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noHBAckRx
#endif
/* sb052.102 Abort statistics added */
#ifdef LSB3
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noAbortTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noAbortRx
#endif
/* sb068.102  Error statistics added */
#ifdef LSB6
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noErrorTx
                      |  mgmt.s.sts.u.tSts.sbChunkSts.noErrorRx
#endif /* LSB6 */
                      |  mgmt.s.sts.u.tSts.sbByteSts.bytesTx
                      |  mgmt.s.sts.u.tSts.sbByteSts.bytesRx
                      |  mgmt.s.sts.u.tSts.nmbBndRetry
                      )
                   {
                      ret    = RFAILED;
                      status = STS_CNTR_NOT_ZERO;
                   }
                }
                break;
             case 7:    /* Test M.102.02: Expected Results  */
                if (sbAccCb.curTst.subTest == 1 )
                {
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);
                }
                else if (sbAccCb.curTst.subTest == 2 )
                {
                   sbAccPeekMsg(&msg);
                   if (msg->evntType == ACC_EVT_BND_REQ)
                   {
                      oper.hi.suId =  SUID_1;
                      oper.hi.spId =  SPID_1;
                      ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ, &status, &reason);
                      setBit(&sbAccCb.curTst.bTickMask, BIT0);
                   } else if (msg->evntType == ACC_EVT_CNTRL_CFM) {
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

                } else  if (sbAccCb.curTst.subTest <= (sbAccCb.curTst.numSubTst-3) )
                {
                   oper.hi.suId =  SUID_1;
                   oper.hi.spId =  SPID_1;
                   ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ, &status, &reason);
                } else  if (sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-2) )
                {
                   sbAccPeekMsg(&msg);
                   if (msg->evntType == ACC_EVT_BND_REQ)
                   {
                      oper.hi.suId =  SUID_1;
                      oper.hi.spId =  SPID_1;
                      ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ, &status, &reason);
                      setBit(&sbAccCb.curTst.bTickMask, BIT0);
                   }
                   else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                   {
                      mgmt.cfm.status = LCM_PRIM_NOK;
                      mgmt.cfm.reason = LSB_REASON_MAX_BND_TRY;
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
                }
                else  if (sbAccCb.curTst.subTest == (sbAccCb.curTst.numSubTst-1) )
                {
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);

                   if (sbMgmt.t.cfg.s.tSapCfg.reConfig.maxBndRetry !=\
                       mgmt.s.sts.u.tSts.nmbBndRetry)
                   {
                      status = INC_STSCNTR;
                      ret = RFAILED;
                   }
                } /*end of if statement */
                break;
             case 8:     /* Test M.102.03: Expected Results  */
                mgmt.cfm.status = LCM_PRIM_NOK;
                mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                mgmt.transId = sbAccCb.curTst.curTransId;
                ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STS_CFM);
                break;
             }

            if ( ret == RFAILED )
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                  ACC_EVT_CNTRL_CFM, status, reason );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;

            }
            else     /* Subtest successful */
            {
               sbAccCb.curTst.subTestsPass++;
            }   /*End Subtest successful */
         } /* end primitive received */
          if (sbAccCb.curTst.tickLstDoneFlg == TRUE)
          {
             sbAccCb.curTst.subTest++;
             sbAccCb.curTst.bTickMask = 0;
          }
         sbAccCb.curTst.state++;
         break;
      case 2: /* Do cleanup before next test */
         if ( sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
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
   if ( sbAccCb.curTst.bBusyCleanup == TRUE )
      doCleanup( );

   RETVALUE( ROK );
}  /* end sbSctStatisticsRequestTst */


/*
*       Fun:   sbM300_01
*
*       Desc:  Test case : M.300.01
*              Purpose   : Verify that Alarms can be Enabled
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM300_01
(
void
)
#else
PUBLIC  S16 sbM300_01(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM300_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 3;
   sbSctEnableDisableAlarmsTst(curtstnum,"M.300.01");
   RETVALUE(ROK);
} /* end sbM300_01 */


/*
*       Fun:   sbM300_02
*
*       Desc:  Test case : M.300.02
*              Purpose   : Verify that Alarms can be Disabled
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM300_02
(
void
)
#else
PUBLIC  S16 sbM300_02(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM300_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 3;
   sbSctEnableDisableAlarmsTst(curtstnum,"M.300.02");
   RETVALUE(ROK);
} /* end sbM300_02 */


/*
*       Fun:   sbM301_01
*
*       Desc:  Test case : M.301.01
*              Purpose   : Verify that Message Trace can be Enabled
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM301_01
(
void
)
#else
PUBLIC  S16 sbM301_01(void)
#endif
{
   U8          curtstnum;    /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM301_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 3;
   sbSctEnableDisableMessageTraceTst(curtstnum,"M.301.01");
   RETVALUE(ROK);
} /* end sbM301_01 */


/*
*       Fun:   sbM301_02
*
*       Desc:  Test case : M.301.02
*              Purpose   : Verify that Message Trace can be Disabled
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM301_02
(
void
)
#else
PUBLIC  S16 sbM301_02(void)
#endif
{
   U8          curtstnum;           /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM301_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 3;
   sbSctEnableDisableMessageTraceTst(curtstnum,"M.301.02");
   RETVALUE(ROK);
} /* end sbM301_02 */


/*
*       Fun:   sbM302_01
*
*       Desc:  Test case : M.302.02
*              Purpose   : Verify that Debug Prints can be Enabled
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM302_01
(
void
)
#else
PUBLIC  S16 sbM302_01(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM302_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 3;
   sbSctEnableDisableDebugPrintsTst(curtstnum,"M.302.01");
   RETVALUE(ROK);
} /* end sbM302_01 */


/*
*       Fun:   sbM302_02
*
*       Desc:  Test case : M.302.02
*              Purpose   : Verify that Debug Prints can be Disabled
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM302_02
(
void
)
#else
PUBLIC  S16 sbM302_02(void)
#endif
{
   U8          curtstnum;   /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM302_02)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 3;
   sbSctEnableDisableDebugPrintsTst(curtstnum,"M.302.02");
   RETVALUE(ROK);
} /* end sbM302_02 */


/*
*       Fun:   sbM303_01
*
*       Desc:  Test case : M.303.01
*              Purpose   : Verify Shutdown Operations
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM303_01
(
void
)
#else
PUBLIC  S16 sbM303_01(void)
#endif
{
   U8          curtstnum; /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM303_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 5;
   sbSctShutdownOperationsTst(curtstnum,"M.303.01");
   RETVALUE(ROK);
} /* end sbM303_01 */


/*
*       Fun:   sbM304_01
*
*       Desc:  Test case : M.304.01
*              Purpose   : Verify Delete SCTSAP
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM304_01
(
void
)
#else
PUBLIC  S16 sbM304_01(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM304_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 3;
   sbSctDeleteTsapSctsapTst(curtstnum,"M.304.01");
   RETVALUE(ROK);
} /* end sbM304_01 */


/*
*       Fun:   sbM305_01
*
*       Desc:  Test case : M.305.01
*              Purpose   : Verify Delete TSAP
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM305_01
(
void
)
#else
PUBLIC  S16 sbM305_01(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM305_01)
   curtstnum = 2;
   sbAccCb.curTst.numSubTst = 3;
   sbSctDeleteTsapSctsapTst(curtstnum,"M.305.01");
   RETVALUE(ROK);
} /* end sbM305_01 */

/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
/*
*       Fun:   sbM306_01
*
*       Desc:  Test case : M.306.01
*              Purpose   : Verify that path profile deletion operation is
*                          successful and an alarm is raised in the event of 
*                          any further efforts to access this path profile.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM306_01
(
void
)
#else
PUBLIC  S16 sbM306_01(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM306_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 4;
   sbDeletePathProfTst(curtstnum,"M.306.01");
   RETVALUE(ROK);
} /* end sbM306_01 */

/*
*       Fun:   sbM307_01
*
*       Desc:  Test case : M.307.01
*              Purpose   : Verify that destination deletion operation is
*                          successful and an alarm is raised in the event of 
*                          any further efforts to access this path profile.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM307_01
(
void
)
#else
PUBLIC  S16 sbM307_01(void)
#endif
{
   U8          curtstnum;  /* number of the current test: eg. C.101.curtstnum */

   TRC2(sbM307_01)
   curtstnum = 1;
   sbAccCb.curTst.numSubTst = 3;
   sbDeleteDstAddrTst(curtstnum,"M.307.01");
   RETVALUE(ROK);
} /* end sbM307_01 */

/*
*       Fun:   sbDeletePathProfTst
*
*       Desc:  Test delete PATHPROF 
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbDeletePathProfTst
(
U8   curtstnum,    /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr    /* test number */
)
#else
PRIVATE S16 sbDeletePathProfTst(curtstnum, numstr)
U8   curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;  /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;

   TRC2(sbDeletePathProfTst)

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;


   /* Pretests/Setup */
   if (sbAccCb.curTst.bBusyPreTestConf)      /* Clean-up has been done */
   {
      SB_GENCFG( )
      if (isBitSet( sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
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
         if (isBitSet( sbAccCb.curTst.bConfigMask, BIT2) == TRUE)
         {
            SB_SCTSAPCFG( SAP_1 )
            if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
            {
               SB_TSAPCFG(SAP_1)
               if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
               {
                  SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                  if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
                  {
                     SB_BIND_SCTSAP(SUID_0, SPID_0, BIT0)
                     SB_ENTERTEST(sbAccCb.curTst.bSapMask, BIT0)
                  } /* end TSapMask if */
               }/*end TSapCfgMask if*/
            } /* end SctSapCfgMask, bit 0, if */
         } 
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch (sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch (curtstnum) 
            {  /* Start switch(curtstnum) #1 */
               case 1:    /* Test M.309.01: Execution */
                  switch (sbAccCb.curTst.subTest) 
                  {
                     case 1:
                        /* Set header to delete DSTADDR */
                        /* Action    = Delete DSTADDR */
                        /* Element   = STSBDSTADDR */
                        cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30901;
                        sbMgmt.t.cntrl.action = ADEL;
                        sbMgmt.hdr.elmId.elmnt = STSBDSTADDR;
                        sbMgmt.t.cntrl.profId = PROFID_0;
                        sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_IPV4; 
                        sbMgmt.t.cntrl.dstAddr.u.ipv4NetAddr = 32236548; 

                        (void)  SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                        break;
                     case 2:
                        /* Set header to delete PATHPROF */
                        /* Action    = Delete PATHPROF   */
                        /* Element   = STSBPATHPROF      */
                        cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30901;
                        sbMgmt.t.cntrl.action = ADEL;
                        sbMgmt.t.cntrl.profId = PROFID_0;
                        sbMgmt.hdr.elmId.elmnt = STSBPATHPROF;
                        sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 

                        (void)  SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                        break;
                     case 3:
                        /* Set header to delete PATHPROF */
                        /* Action    = Delete PATHPROF   */
                        /* Element   = STSBPATHPROF      */
                        cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30901;
                        sbMgmt.t.cntrl.action = ADEL;
                        sbMgmt.t.cntrl.profId = PROFID_0;
                        sbMgmt.hdr.elmId.elmnt = STSBPATHPROF;
                        sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 

                        (void)  SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                        break;
                  }
                  break;
            }
            sbAccCb.curTst.state++;
            break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg(&status);
         if (status == WAIT)
         {   /* wait for message to reach the queue */
            RETVALUE(ROK);
         }
         else if (status == TIMEOUT)
         {
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                                    sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0 );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }

         }
         else
         {
            reason = 0;
               /* fill the mgmt */
             switch(curtstnum)
             {
                case 1:     /* Test M.309.01: Expected Results  */
                   switch (sbAccCb.curTst.subTest) 
                   {
                      case 1:
                         /* subtest pass if OK */
                         mgmt.s.cntrl.sapId = SUID_0;
                         mgmt.cfm.status = LCM_PRIM_OK;
                         mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                         mgmt.transId = sbAccCb.curTst.curTransId;
                         ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_CNTRL_CFM);
                         break;
                      case 2:
                         /* subtest pass if OK */
                         mgmt.s.cntrl.sapId = SUID_0;
                         mgmt.cfm.status = LCM_PRIM_OK;
                         mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                         mgmt.transId = sbAccCb.curTst.curTransId;
                         ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_CNTRL_CFM);
                         break;
                      case 3: 
                         mgmt.cfm.status = LCM_PRIM_NOK;
                         mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                         mgmt.transId = sbAccCb.curTst.curTransId;
                         ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_CNTRL_CFM);
                         break;
                  }
                  break;
             }
             if (ret != 10)
             {
                if (ret == RFAILED)
                {
                   sbAccCb.curTst.subTestsFail++;
                   sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       ACC_EVT_CNTRL_CFM, status, reason);
                   /* Problem - do cleanup */
                   sbAccCb.curTst.bBusyPreTestConf = FALSE;
                   sbAccCb.curTst.bBusyCleanup = TRUE;
                }
                else     /* Subtest successful */
                {
                   sbAccCb.curTst.subTestsPass++;
                }   /*End Subtest successful */
             }
         } /* end primitive received */
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         sbAccCb.curTst.state++;
         break;
      case 2: /* Do cleanup before next test */
         if (sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst)
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
      doCleanup( );

   RETVALUE(ROK);
}  /* end sbDeletePathProfTst */

/*
*       Fun:   sbDeleteDstAddrTst
*
*       Desc:  Test delete DSTADDR 
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbDeleteDstAddrTst
(
U8   curtstnum,    /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr    /* test number */
)
#else
PRIVATE S16 sbDeleteDstAddrTst(curtstnum, numstr)
U8   curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;  /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;

   TRC2(sbDeleteDstAddrTst)

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;


   /* Pretests/Setup */
   if (sbAccCb.curTst.bBusyPreTestConf)      /* Clean-up has been done */
   {
      SB_GENCFG( )
      if (isBitSet( sbAccCb.curTst.bConfigMask, BIT0) == TRUE)
      {
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
         if (isBitSet( sbAccCb.curTst.bConfigMask, BIT2) == TRUE)
         {
            SB_SCTSAPCFG( SAP_1 )
            if (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)
            {
               SB_TSAPCFG(SAP_1)
               if (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)
               {
                  SB_BIND_HITSAP(SUID_0, SPID_0, BIT0)
                  if (isBitSet(sbAccCb.curTst.bTSapMask, BIT0) == TRUE)
                  {
                     SB_BIND_SCTSAP(SUID_0, SPID_0, BIT0)
                     SB_ENTERTEST(sbAccCb.curTst.bSapMask, BIT0)
                  } /* end TSapMask if */
               }/*end TSapCfgMask if*/
            } /* end SctSapCfgMask, bit 0, if */
         } 
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if (sbAccCb.curTst.bBusySubtest)
   {
      switch (sbAccCb.curTst.state)   /* Switch #1 */
      {
         case 0:
            switch (curtstnum) 
            {  /* Start switch(curtstnum) #1 */
               case 1:    /* Test M.309.01: Execution */
                  switch (sbAccCb.curTst.subTest) 
                  {
                     case 1:
                        /* Set header to delete DSTADDR */
                        /* Action    = Delete DSTADDR */
                        /* Element   = STSBDSTADDR */
                        cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30901;
                        sbMgmt.t.cntrl.action = ADEL;
                        sbMgmt.hdr.elmId.elmnt = STSBDSTADDR;
                        sbMgmt.t.cntrl.profId = PROFID_0;
                        sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_IPV4; 
                        sbMgmt.t.cntrl.dstAddr.u.ipv4NetAddr = 32236548; 

                        (void)  SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                        break;
                     case 2:
                        /* Set header to delete DSTADDR */
                        /* Action    = Delete DSTADDR */
                        /* Element   = STSBDSTADDR */
                        cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
                        setResponse(&sbMgmt.hdr.response);
                        sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30901;
                        sbMgmt.t.cntrl.action = ADEL;
                        sbMgmt.hdr.elmId.elmnt = STSBDSTADDR;
                        sbMgmt.t.cntrl.profId = PROFID_0;
                        sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_IPV4; 
                        sbMgmt.t.cntrl.dstAddr.u.ipv4NetAddr = ACC_ASSOC1_LOCAL_1; 

                        (void)  SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                        sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
                        break;
                  }
                  break;
            }
            sbAccCb.curTst.state++;
            break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg(&status);
         if (status == WAIT)
         {   /* wait for message to reach the queue */
            RETVALUE(ROK);
         }
         else if (status == TIMEOUT)
         {
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                                    sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0 );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }

         }
         else
         {
            reason = 0;
               /* fill the mgmt */
             switch(curtstnum)
             {
                case 1:     /* Test M.309.01: Expected Results  */
                   switch (sbAccCb.curTst.subTest) 
                   {
                      case 1:
                         /* subtest pass if OK */
                         mgmt.s.cntrl.sapId = SUID_0;
                         mgmt.cfm.status = LCM_PRIM_OK;
                         mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                         mgmt.transId = sbAccCb.curTst.curTransId;
                         ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_CNTRL_CFM);
                         break;
                      case 2: 
                         mgmt.cfm.status = LCM_PRIM_NOK;
                         mgmt.cfm.reason = LCM_REASON_INVALID_PAR_VAL;
                         mgmt.transId = sbAccCb.curTst.curTransId;
                         ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_CNTRL_CFM);
                         break;
                  }
                  break;
             }
             if (ret != 10)
             {
                if (ret == RFAILED)
                {
                   sbAccCb.curTst.subTestsFail++;
                   sbAccDispErrTstRslt(numstr, sbAccCb.curTst.subTest,
                                       ACC_EVT_CNTRL_CFM, status, reason);
                   /* Problem - do cleanup */
                   sbAccCb.curTst.bBusyPreTestConf = FALSE;
                   sbAccCb.curTst.bBusyCleanup = TRUE;
                }
                else     /* Subtest successful */
                {
                   sbAccCb.curTst.subTestsPass++;
                }   /*End Subtest successful */
             }
         } /* end primitive received */
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         sbAccCb.curTst.state++;
         break;
      case 2: /* Do cleanup before next test */
         if (sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst)
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
      doCleanup( );

   RETVALUE(ROK);
}  /* end sbDeleteDstAddrTst */
#endif /* SB_SATELLITE */

/*
*       Fun:   sbSctEnableDisableAlarmsTst
*
*       Desc:  Enable/Disable Alarms.
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctEnableDisableAlarmsTst
(
U8   curtstnum,/* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE S16 sbSctEnableDisableAlarmsTst(curtstnum, numstr)
U8   curtstnum; /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;
   TRC2( sbSctEnableDisableMessageTraceTst )
   /* Pretests/Setup */
   if ( sbAccCb.curTst.bBusyPreTestConf ) /* Clean-up has been done */
   {
      SB_GENCFG( )
      if ( isBitSet( sbAccCb.curTst.bConfigMask, BIT0 ) == TRUE )
      {
         SB_SCTSAPCFG( SAP_1 )
         if ( isBitSet( sbAccCb.curTst.bSctSapCfgMask, BIT0 ) == TRUE )
         {
            SB_TSAPCFG( SAP_1 )
            SB_ENTERTEST( sbAccCb.curTst.bTSapCfgMask, BIT0 )
         } /* end SctSapCfgMask, bit 0, if */
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if ( sbAccCb.curTst.bBusySubtest )
   {
      switch ( sbAccCb.curTst.state )   /* Switch #1 */
      {
      case 0:
         switch ( curtstnum )
         {    /* Start switch(curtstnum) #1 */
         case 1:    /* Test M.300.01: Execution */
            switch (sbAccCb.curTst.subTest) {
            case 1:
               /* Set header to ensable alarms */
               /* Action    = enable (AENA)     */
               /* Subaction = Alarms (SAUSTA)     */
               /* Element   = STSBGEN             */
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 300011;
               sbMgmt.t.cntrl.action = AENA;
               sbMgmt.t.cntrl.subAction = SAUSTA;
               sbMgmt.hdr.elmId.elmnt = STSBGEN;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
               break;
            case 2:
               (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_3, SPID_3);
               sbAccCb.curTst.evtType = ACC_EVT_STA_IND;   /* expected result */
               break;
            }

            break;
         case 2:    /* Test M.300.02: Execution */
            switch (sbAccCb.curTst.subTest)
            {
            case 1:
               /* Set header to disable alarms*/
               /* Action    = disable (ADISIMM) */
               /* Subaction = Alarms (SAUSTA)     */
               /* Element   = STSBGEN             */
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 300021;
               sbMgmt.t.cntrl.action = ADISIMM;
               sbMgmt.t.cntrl.subAction = SAUSTA;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.elmId.elmnt = STSBGEN;

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
               break;

            case 2:
                (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_3, SPID_3);
               sbAccCb.curTst.evtType = ACC_EVT_STA_IND;   /* expected result */
               break;
            }
            break;
         }
         sbAccCb.curTst.state++;
         break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg( &status );
         if ( status == WAIT )
         {   /* wait for message to reach the queue */
            RETVALUE( ROK );
         }
         else if ( status == TIMEOUT ) {
            if ( (curtstnum == 2) && (sbAccCb.curTst.subTest == 2) )
            {
               sbAccCb.curTst.subTestsPass++;
            }else {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
               ACC_EVT_CNTRL_CFM, TIMEOUT_ON_PRIM, 0 );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
         }
         else {
            reason = 0;
               /* fill the mgmt */
             switch(curtstnum)
             {
             case 1:    /* Test M.300.01: Expected Results  */
                switch (sbAccCb.curTst.subTest)
                {
                  case 1:
                      /* subtest pass if OK */
                      mgmt.cfm.status = LCM_PRIM_OK;
                      mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                      mgmt.transId = sbAccCb.curTst.curTransId;
                      ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                      break;
                  case 2:
                      mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                      mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
                      mgmt.s.usta.sapId = SPID_3;
                      mgmt.transId = sbAccCb.curTst.curTransId;
                      ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_IND);
                      break;
                }
                break;
             case 2:    /* Test M.300.02: Expected Results  */
                switch (sbAccCb.curTst.subTest)
                {
                  case 1:
                      /* subtest pass if OK */
                      mgmt.cfm.status = LCM_PRIM_OK;
                      mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                      mgmt.transId = sbAccCb.curTst.curTransId;
                      ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                      break;
                  case 2:
                      mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                      mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
                      mgmt.s.usta.sapId = SPID_3;
                      mgmt.transId = sbAccCb.curTst.curTransId;
                      ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_IND);
                      break;
                }
                break;

             }

            if ( ret == RFAILED )
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                  ACC_EVT_CNTRL_CFM, status, reason );
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
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         break;
      case 2: /* Do cleanup before next test */
         if ( sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
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
   if ( sbAccCb.curTst.bBusyCleanup == TRUE )
      doCleanup( );

   RETVALUE( ROK );
}  /* end sbSctEnableDisableAlarmsTst */


/*
*       Fun:   sbSctEnableDisableMessageTraceTst
*
*       Desc:  Enable/Disable Message Trace.
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctEnableDisableMessageTraceTst
(
U8   curtstnum, /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE S16 sbSctEnableDisableMessageTraceTst(curtstnum, numstr)
U8   curtstnum;/* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   Buffer        *mBuf;
   S16           ret;
   SbAccMsgQElm  *msg;
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbOperQElm    oper;
   PRIVATE       SbAccChunkBld buildPar; /* Parameters used for checking chunks */
   CmNetAddr     dfltPriPeerNAddr;

    ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   TRC2( sbSctEnableDisableMessageTraceTst )
   /* Pretests/Setup */
   if(sbAccCb.curTst.bBusyPreTestConf)     /* Clean-up has been done */
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
   if ( sbAccCb.curTst.bBusySubtest ) {
      switch ( sbAccCb.curTst.state )   /* Switch #1 */
      {
      case 0:
         switch ( curtstnum )
         {    /* Start switch(curtstnum) #1 */
         case 1:    /* Test M.301.01: Execution */
            switch (sbAccCb.curTst.subTest) {
            case 1:
               /* Set header to enable trace    */
               /* Action    = enable (AENA)     */
               /* Subaction = trace (SATRC)     */
               /* Element   = STSBGEN           */
               cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30101;
               sbMgmt.t.cntrl.action = AENA;
               sbMgmt.t.cntrl.subAction = SATRC;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.elmId.elmnt = STSBGEN;

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;  /* reply event expected */
               break;
            case 2:
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
               {
               /* Send a DatReq packet */
                  dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                  SB_SETUP_DAT_REQ(mBuf)
                  (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                       &dfltPriPeerNAddr, ACC_STREAMID, ORDER, NOBUNDLE,\
                                       ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                  sbAccCb.curTst.tickLstDoneFlg = FALSE;
               } else if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE) &&
                           (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
               {
                  SB_SETUP_DAT_REQ(mBuf)
                  SB_RLSMEM(mBuf)
               }
               break;
            }
            break;
         case 2:    /* Test M.301.02: Execution */
            switch (sbAccCb.curTst.subTest) {
            case 1:
               /* Set header to disable trace   */
               /* Action    = disable (ADISIMM) */
               /* Subaction = trace (SATRC)     */
               /* Element   = STSBGEN           */
               cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30102;
               sbMgmt.t.cntrl.action = ADISIMM;
               sbMgmt.t.cntrl.subAction = SATRC;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.elmId.elmnt = STSBGEN;

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               break;
            case 2:
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
               {
                  /* Send a DatReq packet */
                  SB_SETUP_DAT_REQ(mBuf)/* Setup data buffer and other parameters \
                                           for data transmission */
                  (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                       &assoc_1.priPeerNAddr,ACC_STREAMID,\
                                       ORDER, NOBUNDLE,\
                                       ACC_NO_LIFETM_LIM, \
                                       ACC_PROT_ID, mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                  sbAccCb.curTst.tickLstDoneFlg = FALSE;
               }

               break;
            }
            break;
         }
         sbAccCb.curTst.state++;
         break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg( &status );
         if ( status == WAIT )
         {   /* wait for message to reach the queue */
            RETVALUE( ROK );
         }
         else if ( status == TIMEOUT )
         {
            if ( ( sbAccCb.curTst.subTest == 2) && \
                 (curtstnum == 2) )
            {
               sbAccCb.curTst.subTestsPass++;
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                      sbAccCb.curTst.tickLstDoneFlg = TRUE;
            }
            else
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
               sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0 );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }

         }
         else
         {
            reason = 0;
               /* fill the mgmt */
             switch(curtstnum)
             {
             case 1:    /* Test M.301.01: Expected Results  */
                switch (sbAccCb.curTst.subTest) {
                case 1:
                   /* subtest pass if OK */
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                   break;
                case 2:
                   /* subtest pass if trace indication received */
                   sbAccPeekMsg(&msg);
                   if (msg->evntType == ACC_EVT_UDAT_REQ)
                   {
                      oper.hi.spId = SPID_0;
                      SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                      ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                               &assoc_1, &status );

                      if (oper.hi.peerTAddr.u.ipv4TptAddr.address != \
                         assoc_1.priPeerNAddr.u.ipv4NetAddr)
                      {
                         status = INC_ADDR;
                         ret = RFAILED;
                      }
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                      setBit(&sbAccCb.curTst.bTickMask, BIT1);
                   } else if (msg->evntType == ACC_EVT_TRC_IND)
                   {
                        mgmt.transId = 0;
                        mgmt.s.trc.sapId = SPID_0;
                        ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_TRC_IND);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        sbAccCb.curTst.evtType = ACC_EVT_TRC_IND;
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
             case 2:    /* Test M.301.02: Expected Results  */
                switch (sbAccCb.curTst.subTest) {
                case 1:
                   /* subtest pass if OK */
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                   break;
                case 2:
                   /* subtest pass if SCTP does not respond with TrcInd */
                   sbAccPeekMsg(&msg);
                   if (msg->evntType == ACC_EVT_UDAT_REQ)
                   {
                      oper.hi.spId = SPID_0;
                      SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                      ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                               &assoc_1, &status );

                      if (oper.hi.peerTAddr.u.ipv4TptAddr.address != \
                         assoc_1.priPeerNAddr.u.ipv4NetAddr)
                      {
                         status = INC_ADDR;
                         ret = RFAILED;
                      }
                      sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
                      setBit(&sbAccCb.curTst.bTickMask, BIT1);
                   } else {
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

             }
            if ( ret == RFAILED ) {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                  sbAccCb.curTst.evtType, status, reason );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;

            }
            else     /* Subtest successful */
            {
               sbAccCb.curTst.subTestsPass++;
            }   /*End Subtest successful */
         } /* end primitive received */
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         sbAccCb.curTst.state++;
         break;
      case 2: /* Do cleanup before next test */
         if ( sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
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
   if ( sbAccCb.curTst.bBusyCleanup == TRUE )
      doCleanup( );

   RETVALUE( ROK );
}  /* end sbSctEnableDisableMessageTraceTst */

/*
*       Fun:   sbSctEnableDisableDebugPrintsTst
*
*       Desc:  Enable/Disable Debug Prints.
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctEnableDisableDebugPrintsTst
(
U8   curtstnum, /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr /* test number */
)
#else
PRIVATE S16 sbSctEnableDisableDebugPrintsTst(curtstnum, numstr)
U8   curtstnum; /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;  /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   TRC2( sbSctEnableDisableDebugPrintsTst )
   /* Pretests/Setup */
   if ( sbAccCb.curTst.bBusyPreTestConf )            /* Clean-up has been done */
   {
      SB_GENCFG( )
      if ( isBitSet( sbAccCb.curTst.bConfigMask, BIT0 ) == TRUE )
      {
         SB_SCTSAPCFG( SAP_1 )
         if ( isBitSet( sbAccCb.curTst.bSctSapCfgMask, BIT0 ) == TRUE )
         {
            SB_TSAPCFG( SAP_1 )
            if ( isBitSet( sbAccCb.curTst.bTSapCfgMask, BIT0 ) == TRUE )
            {
               SB_BIND_HITSAP( SUID_0, SPID_0, BIT0 )
               if ( isBitSet( sbAccCb.curTst.bTSapMask, BIT0 ) == TRUE )
               {
                  SB_BIND_SCTSAP( SUID_0, SPID_0, BIT0 )
                  SB_ENTERTEST( sbAccCb.curTst.bSapMask, BIT0 )
               } /* end TSapMask if */
            }/*end TSapCfgMask if*/
         } /* end SctSapCfgMask, bit 0, if */
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if ( sbAccCb.curTst.bBusySubtest )
   {
      switch ( sbAccCb.curTst.state )   /* Switch #1 */
      {
      case 0:
         switch ( curtstnum )
         {    /* Start switch(curtstnum) #1 */
         case 1:    /* Test M.302.01: Execution */
            switch (sbAccCb.curTst.subTest) {
            case 1:
               /* Set header to enable debug prints */
               /* Action    = enable (AENA)     */
               /* Subaction = Debug Prints (SADBG)     */
               /* Element   = STSBGEN             */
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30201;
               sbMgmt.t.cntrl.action = AENA;
               sbMgmt.t.cntrl.subAction = SADBG;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.elmId.elmnt = STSBGEN;

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               break;
            case 2:
               /* Create and exception */
               (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_3, SPID_3);
               sbAccCb.curTst.evtType = ACC_EVT_STA_IND;   /* expected result */
               SPrint("\n========================================\n");
               SPrint(  "Confirm that Debug Prints are displayed!\n");
               SPrint(  "========================================\n\n");
               break;
            }
            break;
         case 2:    /* Test M.302.02: Execution */
            switch (sbAccCb.curTst.subTest)
            {
            case 1:
               /* Set header to disable debug prints */
               /* Action    = disable (ADISIMM) */
               /* Subaction = Debug Prints (SADBG)     */
               /* Element   = STSBGEN             */
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30202;
               sbMgmt.t.cntrl.action = ADISIMM;
               sbMgmt.t.cntrl.subAction = SADBG;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.elmId.elmnt = STSBGEN;

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               break;
            case 2:
               /* Create and exception */
               (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_3, SPID_3);
               sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /* expected result */
               SPrint("\n============================================\n");
               SPrint(  "Confirm that Debug Prints are NOT displayed!\n");
               SPrint(  "============================================\n\n");
               break;
            }
            break;
         }
         sbAccCb.curTst.state++;
         break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg( &status );
         if ( status == WAIT )
         {   /* wait for message to reach the queue */
            RETVALUE( ROK );
         }
         else if ( status == TIMEOUT ) {
            sbAccCb.curTst.subTestsFail++;
            sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
               ACC_EVT_CNTRL_CFM, TIMEOUT_ON_PRIM, 0 );
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
             case 1:     /* Test M.302.01: Expected Results  */
                switch (sbAccCb.curTst.subTest)
                {
                case 1:
                   /* subtest pass if OK */
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                   break;
                case 2:
                   /* subtest pass if debug message is displayed */
                   mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                   mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
                   mgmt.s.usta.sapId = SPID_3;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_IND);
                   break;
               }
               break;
             case 2:     /* Test M.302.02: Expected Results  */
                switch (sbAccCb.curTst.subTest)
                {
                case 1:
                   /* subtest pass if OK */
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                   break;
                case 2:
                   /* subtest pass if debug message is not displayed */
                   mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                   mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
                   mgmt.s.usta.sapId = SPID_3;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_IND);
                   break;
               }
               break;

             }



            if ( ret == RFAILED ) {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                  ACC_EVT_CNTRL_CFM, status, reason );
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
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         break;
      case 2: /* Do cleanup before next test */
         if ( sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst ) {
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
   if ( sbAccCb.curTst.bBusyCleanup == TRUE )
      doCleanup( );

   RETVALUE( ROK );
}  /* end sbSctEnableDisableDebugPrintsTst */


/*
*       Fun:   sbSctShutdownOperationsTst
*
*       Desc:  Test Shutdown Operations
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctShutdownOperationsTst
(
U8   curtstnum,   /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr  /* test number */
)
#else
PRIVATE S16 sbSctShutdownOperationsTst(curtstnum, numstr)
U8   curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;  /* test number */
#endif
{
   PRIVATE       SbMgmtQElm    mgmt;
   PRIVATE       SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   SbAccMsgQElm  *msg;
   PRIVATE        SbOperQElm     oper;

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   TRC2( sbSctShutdownOperationsTst )
   /* Pretests/Setup */
   if ( sbAccCb.curTst.bBusyPreTestConf )            /* Clean-up has been done */
   {
      SB_GENCFG( )
      if ( isBitSet( sbAccCb.curTst.bConfigMask, BIT0 ) == TRUE )
      {
         SB_SCTSAPCFG( SAP_1 )
         if ( isBitSet( sbAccCb.curTst.bSctSapCfgMask, BIT0 ) == TRUE )
         {
            SB_TSAPCFG( SAP_1 )
            if ( isBitSet( sbAccCb.curTst.bTSapCfgMask, BIT0 ) == TRUE )
            {
               SB_BIND_HITSAP( SUID_0, SPID_0, BIT0 )
               if ( isBitSet( sbAccCb.curTst.bTSapMask, BIT0 ) == TRUE )
               {
                  SB_BIND_SCTSAP( SUID_0, SPID_0, BIT0 )
                  SB_ENTERTEST( sbAccCb.curTst.bSapMask, BIT0 )
               } /* end TSapMask if */
            }/*end TSapCfgMask if*/
         } /* end SctSapCfgMask, bit 0, if */
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if ( sbAccCb.curTst.bBusySubtest )
   {
      switch ( sbAccCb.curTst.state )   /* Switch #1 */
      {
      case 0:
         switch ( curtstnum ) {    /* Start switch(curtstnum) #1 */
         default:
         case 1:    /* Test M.303.01: Execution */
            switch (sbAccCb.curTst.subTest) {
            case 1:
               /* Set header to shutdown operations */
               /* Action    =  Shutdown (ASHUTDOWN) */
               /* Element   = STSBGEN               */
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&& \
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) && \
                    ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE))
               {
                  setResponse(&sbMgmt.hdr.response);
                  sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 303011;
                  sbMgmt.t.cntrl.action = ASHUTDOWN;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                  sbMgmt.hdr.elmId.elmnt = STSBGEN;

                  (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
                  sbAccCb.curTst.tickLstDoneFlg = FALSE;
                  sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
               }
               break;
            case 2:
               /* Complete configuration on a configured SCTP */
               /* set configuration parameters */
               SB_ZERO(&sbMgmt, (S32)sizeof(sbMgmt));
               setResponse(&sbMgmt.hdr.response);
               sbStdGenCfg(&sbMgmt);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 303012;
               (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_CFG_CFM;   /* expected result */
               break;
            case 3:
               sbStdSctSapCfg(&sbMgmt, SAP_1);
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 303013;
               (Void) SmMiLsbCfgReq(&sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_CFG_CFM;   /* expected result */
               break;
            case 4:
               (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_0, SPID_0);
               sbAccCb.curTst.evtType = ACC_EVT_BND_CFM;   /* expected result */
               break;
            }
            break;
         }
         sbAccCb.curTst.state++;
         break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg( &status );
         if ( status == WAIT ) {   /* wait for message to reach the queue */
            RETVALUE( ROK );
         }
         else if ( status == TIMEOUT ) {
            if ( (curtstnum == 1) && (sbAccCb.curTst.subTest == 1) )
            {
               sbAccCb.curTst.delay = 0;
               setBit(&sbAccCb.curTst.bTickMask, BIT0);
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)&&
                      ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE))
                     sbAccCb.curTst.tickLstDoneFlg = TRUE;
            }
            else
            {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                                    sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0 );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }
         }
         else
         {
            reason = 0;
               /* fill the mgmt */
             switch(curtstnum)
             {
             default:
             case 1:     /* Test M.303.01: Expected Results  */
                switch (sbAccCb.curTst.subTest) {
                case 1:
                   /* subtest pass if OK */
                   sbAccPeekMsg(&msg);
                   if (msg->evntType == ACC_EVT_CNTRL_CFM)
                   {
                      mgmt.cfm.status = LCM_PRIM_OK;
                      mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                      mgmt.transId = sbAccCb.curTst.curTransId;
                      ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                      sbAccCb.curTst.delay = 1;
                      setBit(&sbAccCb.curTst.bTickMask, BIT1);
                   }
                   else
                   {
                      sbAccPopMsg(&msg);  /* pop unwanted closedown from the stack */
                      setBit(&sbAccCb.curTst.bTickMask, BIT2);
                      ret = 10;
                   }
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                   if (( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) ) 
#else
                   if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                      ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) && 
                       ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE))
#endif
                         sbAccCb.curTst.tickLstDoneFlg = TRUE;
                   break;
                case 2:
                   /* subtest pass if configuration was successful */
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM);
                   break;
                case 3:
                   /* subtest pass if configuration was successful */
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM);
                   break;
                case 4:
                   oper.it.suId = SUID_0;
                   oper.it.result = CM_BND_OK;
                   ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_BND_CFM, &status, &reason);
                   break;
               }
               break;
             }

             if (ret != 10 ) {
                if ( ret == RFAILED ) {
                   sbAccCb.curTst.subTestsFail++;
                   sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason );
                   /* Problem - do cleanup */
                   sbAccCb.curTst.bBusyPreTestConf = FALSE;
                   sbAccCb.curTst.bBusyCleanup = TRUE;
                }
                else     /* Subtest successful */
                {
                   sbAccCb.curTst.subTestsPass++;
                }   /*End Subtest successful */
            } /* end primitive received */
         }
         sbAccCb.curTst.state++;
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         break;
      case 2: /* Do cleanup before next test */
         if ( sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst ) {
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
   if ( sbAccCb.curTst.bBusyCleanup == TRUE )
      doCleanup( );

   RETVALUE( ROK );
}  /* end sbSctShutdownOperationsTst */


/*
*       Fun:   sbSctDeleteTsapSctsapTst
*
*       Desc:  Test delete SCTSAP and delete TSAP.
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbSctDeleteTsapSctsapTst
(
U8   curtstnum,    /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr    /* test number */
)
#else
PRIVATE S16 sbSctDeleteTsapSctsapTst(curtstnum, numstr)
U8   curtstnum;   /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;  /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   SbAccMsgQElm  *msg;

    ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   TRC2( sbSctDeleteTsapSctsapTst )
   /* Pretests/Setup */
   if ( sbAccCb.curTst.bBusyPreTestConf )      /* Clean-up has been done */
   {
      SB_GENCFG( )
      if ( isBitSet( sbAccCb.curTst.bConfigMask, BIT0 ) == TRUE )
      {
         SB_SCTSAPCFG( SAP_1 )
         if ( isBitSet( sbAccCb.curTst.bSctSapCfgMask, BIT0 ) == TRUE )
         {
            SB_TSAPCFG( SAP_1 )
            if ( isBitSet( sbAccCb.curTst.bTSapCfgMask, BIT0 ) == TRUE )
            {
               SB_BIND_HITSAP( SUID_0, SPID_0, BIT0 )
               if ( isBitSet( sbAccCb.curTst.bTSapMask, BIT0 ) == TRUE )
               {
                  SB_BIND_SCTSAP( SUID_0, SPID_0, BIT0 )
                  SB_ENTERTEST( sbAccCb.curTst.bSapMask, BIT0 )
               } /* end TSapMask if */
            }/*end TSapCfgMask if*/
         } /* end SctSapCfgMask, bit 0, if */
      } /* end ConfigMask if */
   }  /* end pretests */

   /* Do test */
   if ( sbAccCb.curTst.bBusySubtest ) {
      switch ( sbAccCb.curTst.state )   /* Switch #1 */
      {
      case 0:
         switch ( curtstnum ) {    /* Start switch(curtstnum) #1 */
         case 1:    /* Test M.307.01: Execution */
            switch (sbAccCb.curTst.subTest) {
            case 1:
               /* Set header to delete SCTSAP   */
               /* Action    = Delete SCTSAP     */
               /* Element   = STSBGEN           */
               /* SAP ID    = SPID_0            */
               cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30701;
               sbMgmt.t.cntrl.action = ADEL;
               sbMgmt.t.cntrl.sapId = SPID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.elmId.elmnt = STSBSCTSAP;

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
               break;
            case 2:
               /* Attempt to access SAP */
               (Void) ItLiSctBndReq(&sbAccCb.itPst, SUID_0, SPID_0);
               sbAccCb.curTst.evtType = ACC_EVT_STA_IND;   /* expected result */
               break;
            }
            break;
         case 2:    /* Test M.308.01: Execution */
            switch (sbAccCb.curTst.subTest) {
            case 1:
               /* Set header to delete TSAP        */
               /* Action    = delete (ADEL)        */
               /* Element   = STSBTSAP           */
               /* SAP ID    = SUID_0               */
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE) &&
                    ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE))
               {
                  cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
                  setResponse(&sbMgmt.hdr.response);
                  sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 308011;
                  sbMgmt.t.cntrl.action = ADEL;
                  sbMgmt.t.cntrl.sapId = SUID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
                  sbMgmt.hdr.elmId.elmnt = STSBTSAP;
                  (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
                  sbAccCb.curTst.tickLstDoneFlg = FALSE;
                  sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
               }
               break;
            case 2:
               /* Attempt to access TSAP */
               cmMemset((U8 *)&sbMgmt, 0, sizeof(SbMgmt));
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
               sbMgmt.t.cntrl.action =  ABND_ENA;
               sbMgmt.t.cntrl.sapId =  SUID_0;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       
               sbMgmt.hdr.transId = 308012;
               sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
               (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
               sbAccCb.curTst.evtType = ACC_EVT_CNTRL_CFM;   /* expected result */
               break;
            }
            break;
         }
         sbAccCb.curTst.state++;
         break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg( &status );
         if ( status == WAIT ) {   /* wait for message to reach the queue */
            RETVALUE( ROK );
         }
         else if ( status == TIMEOUT ) {
            if ( (curtstnum == 2) && (sbAccCb.curTst.subTest == 1) )
            {
               sbAccCb.curTst.delay = 0;
               setBit(&sbAccCb.curTst.bTickMask, BIT0);
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)&&
                      ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE))
                     sbAccCb.curTst.tickLstDoneFlg = TRUE;
            } else {
               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                                    sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0 );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }

         }
         else
         {
            reason = 0;
               /* fill the mgmt */
             switch(curtstnum)
             {
             case 1:     /* Test M.307.01: Expected Results  */
                switch (sbAccCb.curTst.subTest) {
                case 1:
                   /* subtest pass if OK */
                   mgmt.s.cntrl.sapId = SUID_0;
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_CNTRL_CFM);
                   break;
                case 2: /* subtest pass if SAP may be bound successfully */
                   mgmt.s.usta.event = LCM_EVENT_UI_INV_EVT;
                   mgmt.s.usta.cause = LCM_CAUSE_INV_SAP;
                   mgmt.s.usta.sapId = SPID_0;
                   mgmt.transId = 0;
                   ret = sbLsbChkCfm(&mgmt,&status, &reason, ACC_EVT_STA_IND);
                   break;
               }
               break;
             case 2:     /* Test M.308.01: Expected Results  */
                switch (sbAccCb.curTst.subTest) {
                case 1:
                   sbAccPeekMsg(&msg);
                   if (msg->evntType == ACC_EVT_CNTRL_CFM)
                   {
                      /* subtest pass if OK */
                      mgmt.cfm.status = LCM_PRIM_OK;
                      mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                      mgmt.transId = sbAccCb.curTst.curTransId;
                      ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                      sbAccCb.curTst.delay = 1;
                      setBit(&sbAccCb.curTst.bTickMask, BIT1);
                   } else {
                      sbAccPopMsg(&msg);  /* pop unwanted closedown from the stack */
                      setBit(&sbAccCb.curTst.bTickMask, BIT2);
                      ret = 10;
                   }
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                   if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE))
#else
                   if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                     ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) &&
                        ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE)  )
#endif
                     sbAccCb.curTst.tickLstDoneFlg = TRUE;
                   break;
                case 2:
                   /* subtest pass if alarm is raised for the TSAP access */
                   mgmt.cfm.status = LCM_PRIM_NOK;
                   mgmt.cfm.reason = LCM_REASON_INVALID_SAP;
                   mgmt.transId = 0;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                   break;
               }
               break;
             }
             if (ret != 10 )
             {
                if ( ret == RFAILED ) {
                   sbAccCb.curTst.subTestsFail++;
                   sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                   ACC_EVT_CNTRL_CFM, status, reason );
                   /* Problem - do cleanup */
                   sbAccCb.curTst.bBusyPreTestConf = FALSE;
                   sbAccCb.curTst.bBusyCleanup = TRUE;
                }
                else     /* Subtest successful */
                {
                   sbAccCb.curTst.subTestsPass++;
                }   /*End Subtest successful */
             }
         } /* end primitive received */
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         sbAccCb.curTst.state++;
         break;
      case 2: /* Do cleanup before next test */
         if ( sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
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
   if ( sbAccCb.curTst.bBusyCleanup == TRUE )
      doCleanup( );

   RETVALUE( ROK );
}  /* end sbSctDeleteTsapSctsapTst */


/*
*       Fun:   sbM400_01
*
*       Desc:  Test case : M.400.01
*              Purpose   : Verify that when tracing is enabled, the layer
*                          manager receives a
*                          TrcInd for every data packet sent.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM400_01
(
void
)
#else
PUBLIC  S16 sbM400_01(void)
#endif
{
   TRC2(sbM400_01)
   sbAccCb.curTst.numSubTst = 3;
   sbMainTrcIndTst(1,"M.400.01");
   RETVALUE(ROK);
} /* end sbM400_01 */


/*
*       Fun:   sbM400_02
*
*       Desc:  Test case : M.400.02
*              Purpose   : Verify that when tracing is disabled, the layer
*                          manager does not receive a
*                          TrcInd for every data packet received.
*
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/

#ifdef ANSI
PUBLIC  S16 sbM400_02
(
void
)
#else
PUBLIC  S16 sbM400_02(void)
#endif
{

   TRC2(sbM400_02)
   sbAccCb.curTst.numSubTst = 3;
   sbMainTrcIndTst(2,"M.400.02");
   RETVALUE(ROK);
} /* end sbM400_02 */


/*
*       Fun:   sbMainTrcIndTst
*
*       Desc:  Enable/Disable Message Trace.
*       Ret:   ROK
*
*       Group: Maintenance
*
*       Notes:
*
*       File:  sb_act6.c
*
*/
#ifdef ANSI
PRIVATE S16 sbMainTrcIndTst
(
U8   curtstnum,     /* number of current test within test group (e.g. O.200.curtstnum) */
S8  *numstr        /* test number */
)
#else
PRIVATE S16 sbMainTrcIndTst(curtstnum, numstr)
U8   curtstnum; /* number of current test within test group (e.g. O.100.curtstnum) */
S8  *numstr;       /* test number */
#endif
{
   SbMgmtQElm    mgmt;
   SbMgmt        sbMgmt;
   SctStatus     status;
   Reason        reason;
   Buffer        *mBuf;
   S16           ret;
   SbAccMsgQElm  *msg;
   PRIVATE       SbAccAssoc    assoc_1;
   PRIVATE       SbOperQElm    oper;
   PRIVATE       SbAccChunkBld buildPar;   /* Parameters used for checking chunks */
   CmNetAddr     dfltPriPeerNAddr;
   CmIpHdrParm   hdrParm;
   U32           tsn;

   ret = ROK;
   reason = LCM_REASON_NOT_APPL;
   TRC2( sbMainTrcIndTst )
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
   if ( sbAccCb.curTst.bBusySubtest )
   {
      switch ( sbAccCb.curTst.state )   /* Switch #1 */
      {
      case 0:
         switch ( curtstnum ) {    /* Start switch(curtstnum) #1 */
         case 1:    /* Test M.400.01: Execution */
            switch (sbAccCb.curTst.subTest)
            {
            case 1:
               /* Set header to enable trace    */
               /* Action    = enable (AENA)     */
               /* Subaction = trace (SATRC)     */
               /* Element   = STSBGEN           */
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30101;
               sbMgmt.t.cntrl.action = AENA;
               sbMgmt.t.cntrl.subAction = SATRC;
               sbMgmt.hdr.elmId.elmnt = STSBGEN;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               break;
            case 2:
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&& \
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
               {
               /* Send a DatReq packet */
                  SB_SETUP_DAT_REQ(mBuf)
                  dfltPriPeerNAddr.type = CM_NETADDR_NOTPRSNT;
                  (void) ItLiSctDatReq(&sbAccCb.itPst, assoc_1.spId, assoc_1.spAssocId, \
                                       &dfltPriPeerNAddr, ACC_STREAMID, ORDER, NOBUNDLE,\
                                       ACC_NO_LIFETM_LIM, ACC_PROT_ID, mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                  sbAccCb.curTst.tickLstDoneFlg = FALSE;
               }
               break;
            }
            break;
         case 2:    /* Test M.400.02: Execution */
            switch (sbAccCb.curTst.subTest)
            {
            case 1:
               /* Set header to disable trace   */
               /* Action    = disable (ADISIMM) */
               /* Subaction = trace (SATRC)     */
               /* Element   = STSBGEN           */
               setResponse(&sbMgmt.hdr.response);
               sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 30101;
               sbMgmt.t.cntrl.action = ADISIMM;
               sbMgmt.t.cntrl.subAction = SATRC;
               sbMgmt.hdr.elmId.elmnt = STSBGEN;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                       
                       sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif                       

               (void)  SmMiLsbCntrlReq( &sbAccCb.smPst, &sbMgmt);
               break;
            case 2:
               if ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&  \
                    (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE)&&  \
                     (isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE))
               {
                  SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
                  tsn = (ACC_INIT_TSN);
                  SB_SETUP_IPHDR_PAR(NOFRAGM)
                  SB_SETUP_UNORDERED_DATA(tsn)
                  buildDataChunk(mBuf,&buildPar,&assoc_1);
                  SB_RLSMEM(sbAccCb.curTst.gmBuf)
                  /* sb032.102 :  IPV6 Support Added */
                  (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0, assoc_1.suConId,
                          &assoc_1.peerTAddr, &assoc_1.localTAddr, &hdrParm,
#ifdef LOCAL_INTF
                          &assoc_1.localIf,
#endif
                          mBuf);
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /* reply event expected */
                  sbAccCb.curTst.tickLstDoneFlg = FALSE;
               }
               break;
            }
            break;
         }
         sbAccCb.curTst.state++;
         break;
      /* Dequeue response and test */
      case 1:
         sbAccVfyMsg( &status );
         if ( status == WAIT ) {   /* wait for message to reach the queue */
            RETVALUE( ROK );
         }
         else if ( status == TIMEOUT ) {
            if ( ( sbAccCb.curTst.subTest == 2) && \
                 (curtstnum == 2) ) {
               sbAccCb.curTst.subTestsPass++;
               if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
                      sbAccCb.curTst.tickLstDoneFlg = TRUE;
            } else {

               sbAccCb.curTst.subTestsFail++;
               sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
               ACC_EVT_CNTRL_CFM, TIMEOUT_ON_PRIM, 0 );
               /* Problem - do cleanup */
               sbAccCb.curTst.bBusyPreTestConf = FALSE;
               sbAccCb.curTst.bBusyCleanup = TRUE;
            }

         }
         else {
            reason = 0;
               /* fill the mgmt */
             switch(curtstnum)
             {
             case 1:    /* Test M.400.01: Expected Results  */
                switch (sbAccCb.curTst.subTest) {
                case 1:
                   /* subtest pass if OK */
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                   break;
                case 2:
                   /* subtest pass if trace indication received */
                   sbAccPeekMsg(&msg);
                   if (msg->evntType == ACC_EVT_UDAT_REQ)
                   {
                      oper.hi.spId = SPID_0;
                      SB_SETUP_CHUNK_INFO(0, 0, FALSE, SB_ID_DATA)
                      SB_SETUP_DAT_REQ(mBuf)
                      SB_RLSMEM(mBuf)
                      ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                               &assoc_1, &status );

                      if (oper.hi.peerTAddr.u.ipv4TptAddr.address != \
                         assoc_1.priPeerNAddr.u.ipv4NetAddr)
                      {
                         status = INC_ADDR;
                         ret = RFAILED;
                      }
                      setBit(&sbAccCb.curTst.bTickMask, BIT1);
                   }
                   else if (msg->evntType == ACC_EVT_TRC_IND)
                   {
                        /* Expected SAP Id */
                        mgmt.s.trc.sapId = SPID_0;
                        oper.hi.spId = SPID_0;
                        SB_SETUP_DAT_REQ(mBuf)
                        SB_RLSMEM(mBuf)
                        mgmt.transId = 0;
                        ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_TRC_IND);
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
                }
                break;
             case 2:    /* Test M.400.02: Expected Results  */
                switch (sbAccCb.curTst.subTest)
                {
                case 1:
                   /* subtest pass if OK */
                   mgmt.cfm.status = LCM_PRIM_OK;
                   mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                   mgmt.transId = sbAccCb.curTst.curTransId;
                   ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
                   break;
                case 2:
                   /* subtest pass if SCTP does not respond with TrcInd */
                   sbAccPeekMsg(&msg);
                   if (msg->evntType == ACC_EVT_DAT_IND)
                   {
                      SB_SETUP_DAT_REQ(mBuf)
                      SB_RLSMEM(mBuf)
                      SB_SETUP_DAT_IND(assoc_1, SCT_UNORDER_DAT)
                      ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_DAT_IND, &status, &reason);
                      setBit(&sbAccCb.curTst.bTickMask, BIT0);
                   }
                   else if (msg->evntType == ACC_EVT_UDAT_REQ)
                   {
                      SB_SETUP_SACK_INFO(0, 0, (ACC_INIT_TSN))
                      ret = sbHitChkMuxUDatReq(&oper, &mgmt, &buildPar,\
                                               &assoc_1, &status );
                      setBit(&sbAccCb.curTst.bTickMask, BIT1);
                   }
                   else if ( (msg->evntType == ACC_EVT_TRC_IND) && \
                             ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == FALSE) )
                   {
                      SB_SETUP_DAT_REQ(mBuf)
                      SB_RLSMEM(mBuf)
                      oper.hi.spId = SPID_0;

                      /* Expected SAP Id */
                      mgmt.s.trc.sapId = SPID_0;
                      mgmt.transId = 0;

                      ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_TRC_IND);
                      setBit(&sbAccCb.curTst.bTickMask, BIT2);
                   }
                   else if ( (msg->evntType == ACC_EVT_TRC_IND) &&  \
                               ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE) )
                   {
                      /* Pop the TrcInd of the SACK */
                      sbAccPopMsg(&msg);
                   }
                   else
                   {
                     status = INC_EVNTTYPE;
                     setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     setBit(&sbAccCb.curTst.bTickMask, BIT0);
                     setBit(&sbAccCb.curTst.bTickMask, BIT2);
                     ret = RFAILED;
                   }
                   if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&& \
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE)&& \
                          ( isBitSet(sbAccCb.curTst.bTickMask, BIT2) == TRUE) )
                         sbAccCb.curTst.tickLstDoneFlg = TRUE;
                   break;
               }
               break;

             }
             if (ret != 10 )
             {
                 if ( ret == RFAILED )
                 {
                   sbAccCb.curTst.subTestsFail++;
                   sbAccDispErrTstRslt( numstr, sbAccCb.curTst.subTest,
                   ACC_EVT_CNTRL_CFM, status, reason );
                   /* Problem - do cleanup */
                   sbAccCb.curTst.bBusyPreTestConf = FALSE;
                   sbAccCb.curTst.bBusyCleanup = TRUE;
                }
                else     /* Subtest successful */
                {
                   sbAccCb.curTst.subTestsPass++;
                }   /*End Subtest successful */
             }

         } /* end primitive received */
         if(sbAccCb.curTst.tickLstDoneFlg == TRUE)
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.bTickMask = 0;
         }
         sbAccCb.curTst.state++;
         break;
      case 2: /* Do cleanup before next test */
         if ( sbAccCb.curTst.subTest == sbAccCb.curTst.numSubTst )
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
   if ( sbAccCb.curTst.bBusyCleanup == TRUE )
      doCleanup( );

   RETVALUE( ROK );
}  /* end sbMainTrcIndTst */


/********************************************************************30**

         End of file:     sb_act6.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:08 2015

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
           sb019.102  ab   1. Modification in acceptance tests M100.01 
                              and M102.01 because of patch sb018.102. 
           sb042.102  hl   1. Added change for SHT interface and Rolling
                              UpGrade
           sb052.102 ag    1. Abort Statistics added.
           sb068.102 kp    1. Error Statistics added.
/main/4      ---   rsr/ag  1. Updated for Release of 1.3
           sb003.103 ag    1. Satellite SCTP feature (under compile-time
                              flag SB_SATELLITE): Added test cases to delete
                              path profile & dst addr.
           sb009.103 nuX   1. Changes made for SOL10 upgrade and chages are made under
                              SB_SOL10_MULTIPORT flag
*********************************************************************91*/
