

/********************************************************************20**

     Name:     sb_acc.h - Acceptance Tests Defines for SCTP Layer

     Type:     C include file

     Desc:     #defines and macros for the SCTP layer acceptance tests

     File:     sb_acc.h

     Sid:      sb_acc.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:04 2015

     Prg:      nct

*********************************************************************21*/

#ifndef __SBACCH__
#define __SBACCH__

/*

*   sb_acc.h -
*
*   Defines declared in this file correspond to defines used by the
*   following TRILLIUM software:
*     part no.                      description
*     --------    ----------------------------------------------
*     1000163                   SCTP layer
*/

/*
*     this software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000163                   SCTP layer
*/

/* Include temporarily from ssi.h */
#define PRNTSZE     255               /* print buffer size */

/* sb003.103: SATELLITE SCTP feature */ 
#define PROFID_0 1
#define DSTADDR_0 1

/* File name of test list configuration file */
#define CFG_FILE "sb_acc.cfg"
#define ACC_PROT_ID   20                 /* Protocol ID to be included in outgoing data messages */

/* Timer related defines */
#define ACC_NO_LIFETM_LIM      0   /* No limit to the lifetime of a datagram */
#define ACC_SMALL_LIFETM_LIM   1   /* Small value for lifetime parameter */

/* Abortflag options: Abort and Shutdown */
#define ABORT         TRUE       /* association aborts immediately */
#define SHTDWN        FALSE      /* associations shuts down gracefully */

/* Data handling defines */
#define ORDER         FALSE      /* deliver user datagrams out of sequence */
#define UNORDER       TRUE       /* deliver user datagrams in sequence */
#define BUNDLE        FALSE      /* do not bundle the user datagram with other user datagrams */
#define NOBUNDLE      TRUE       /* bundle the datagram with other user datagrams  */
#define NOFRAGM       TRUE       /* do not fragment the data */
#define FRAGM         FALSE      /* fragment the data */



/* Define mask BITs */
#define BIT0            1     /* Set when masking 1 */
#define BIT1            2     /* Set when masking 2 */
#define BIT2            4     /* Set when masking 4 */
#define BIT3            8     /* Set when masking 8 */
#define BIT4            16

#define HDR_ERR         254   /* Error in the header  */

/*Imaginary destination network addresses of assoc_1*/
#define ACC_ASSOC1_DEST_1   /*32*/32236546
#define ACC_ASSOC1_DEST_2   /*32*/32236547
#define ACC_ASSOC1_DEST_3   /*32*/32236548
#define ACC_ASSOC1_DEST_4   /*32*/32236549
#define ACC_ASSOC1_DEST_5   /*32*/32236550

/*Imaginary destination network addresses of assoc_2 */
#define ACC_ASSOC2_DEST_1   /*32*/32336581   /* Address starting with 192.169.4.1 and incrementing */
#define ACC_ASSOC2_DEST_2   /*32*/32236582
#define ACC_ASSOC2_DEST_3   /*32*/32236583
#define ACC_ASSOC2_DEST_4   /*32*/32236584
#define ACC_ASSOC2_DEST_5   /*32*/32236585

/* sb012.103: Added non-unicast address (multi-cast address) */
#define ACC_ASSOC3_DEST_1   0xE0000001    /* Multi-cast Address 224.0.0.1 */
#define ACC_ASSOC3_DEST_2   0xEF000001    /* Multi-cast Address 239.0.0.1 */ 

                                                  /*Imaginary source network addresses of assoc_1 */
#define ACC_ASSOC1_LOCAL_1   /*32*/32171009    /* Address starting with 192.167.4.1 and incrementing */
#define ACC_ASSOC1_LOCAL_2   /*32*/32171010
#define ACC_ASSOC1_LOCAL_3   /*32*/32171011
#define ACC_ASSOC1_LOCAL_4   /*32*/32171012
#define ACC_ASSOC1_LOCAL_5   /*32*/32171013

/* sb032.102 :  IPV6 Support Added */ 
#define CPY_ACC_ASSOC1_LOCAL_IPV6(tgtPtr, i) \
{ \
  U8 locAssoc1Ipv6Addr1[] = {63, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 207}; \
  U8 locAssoc1Ipv6Addr2[] = {63, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 208}; \
  U8 locAssoc1Ipv6Addr3[] = {63, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 209}; \
  U8 locAssoc1Ipv6Addr4[] = {63, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 210}; \
  U8 locAssoc1Ipv6Addr5[] = {63, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 211}; \
  if(i == 0) \
    cmMemcpy(tgtPtr, locAssoc1Ipv6Addr1, 16); \
  else if(i == 1) \
    cmMemcpy(tgtPtr, locAssoc1Ipv6Addr2, 16); \
  else if(i == 2) \
    cmMemcpy(tgtPtr, locAssoc1Ipv6Addr3, 16); \
  else if(i == 3) \
    cmMemcpy(tgtPtr, locAssoc1Ipv6Addr4, 16); \
  else if(i == 4) \
    cmMemcpy(tgtPtr, locAssoc1Ipv6Addr5, 16); \
}


/* sb032.102 :  IPV6 Support Added */ 
#define CPY_ACC_ASSOC2_LOCAL_IPV6(tgtPtr, i) \
{  \
  U8  locAssoc2Ipv6Addr1[] = {62, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 207}; \
  U8  locAssoc2Ipv6Addr2[] = {62, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 208};  \
  U8  locAssoc2Ipv6Addr3[] = {62, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 209}; \
  U8  locAssoc2Ipv6Addr4[] = {62, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 210};    \
  U8  locAssoc2Ipv6Addr5[] = {62, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 211};    \
     if(i == 0)  \
        cmMemcpy(tgtPtr, locAssoc2Ipv6Addr1, 16); \
     else if(i == 1)  \
        cmMemcpy(tgtPtr, locAssoc2Ipv6Addr2, 16); \
     else if(i == 2)  \
        cmMemcpy(tgtPtr, locAssoc2Ipv6Addr3, 16); \
     else if(i == 3)  \
        cmMemcpy(tgtPtr, locAssoc2Ipv6Addr4, 16); \
     else if(i == 4)  \
        cmMemcpy(tgtPtr, locAssoc2Ipv6Addr5, 16); \
}
/* sb032.102 :  IPV6 Support Added */ 
#define CPY_ACC_ASSOC1_PEER_IPV6(tgtPtr, i) \
{ \
  U8  peerAssoc1Ipv6Addr1[] = {64, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 207}; \
  U8  peerAssoc1Ipv6Addr2[] = {64, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 208};  \
  U8  peerAssoc1Ipv6Addr3[] = {64, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 209}; \
  U8  peerAssoc1Ipv6Addr4[] = {64, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 210};  \
  U8  peerAssoc1Ipv6Addr5[] = {64, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 211};  \
  /* sb012.103: Added IPv6 address, non-unicast address */					\
  U8  peerAssoc1Ipv6Addr6[] = {255, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 212};  \
        if(i == 0)  \
           cmMemcpy(tgtPtr, peerAssoc1Ipv6Addr1, 16);  \
        else if(i == 1)  \
           cmMemcpy(tgtPtr, peerAssoc1Ipv6Addr2, 16);  \
        else if(i == 2)  \
           cmMemcpy(tgtPtr, peerAssoc1Ipv6Addr3, 16);  \
        else if(i == 3)  \
           cmMemcpy(tgtPtr, peerAssoc1Ipv6Addr4, 16);  \
        else if(i == 4) \
           cmMemcpy(tgtPtr, peerAssoc1Ipv6Addr5, 16);  \
   /* sb012.103: Copying the non-unicast address */    \
        else if(i == 5) \
           cmMemcpy(tgtPtr, peerAssoc1Ipv6Addr6, 16);  \
}
/* sb032.102 :  IPV6 Support Added */
#define CPY_ACC_ASSOC2_PEER_IPV6(tgtPtr, i) \
{ \
   U8 peerAssoc2Ipv6Addr1[] = {65, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 207}; \
   U8 peerAssoc2Ipv6Addr2[] = {65, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 208}; \
   U8 peerAssoc2Ipv6Addr3[] = {65, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 209}; \
   U8 peerAssoc2Ipv6Addr4[] = {65, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 210}; \
   U8 peerAssoc2Ipv6Addr5[] = {65, 252, 25, 00, 69, 69, 00, 03, 02, 00, 248, 255, 254, 33, 103, 211}; \
       if(i == 0) \
                cmMemcpy(tgtPtr, peerAssoc2Ipv6Addr1, 16); \
         else if(i == 1) \
                cmMemcpy(tgtPtr, peerAssoc2Ipv6Addr2, 16); \
         else if(i == 2) \
                cmMemcpy(tgtPtr, peerAssoc2Ipv6Addr3, 16); \
         else if(i == 3) \
                cmMemcpy(tgtPtr, peerAssoc2Ipv6Addr4, 16); \
         else if(i == 4) \
                cmMemcpy(tgtPtr, peerAssoc2Ipv6Addr5, 16); \
}
/*Imaginary source network addresses of assoc_2 */
#define ACC_ASSOC2_LOCAL_1   /*32*/32105473   /* Address starting with 192.166.4.1 and incrementing */
#define ACC_ASSOC2_LOCAL_2   /*32*/32105474
#define ACC_ASSOC2_LOCAL_3   /*32*/32105475
#define ACC_ASSOC2_LOCAL_4   /*32*/32105476
#define ACC_ASSOC2_LOCAL_5   /*32*/32105477

/* 2D test table's size */
#define ACC_TSTTBLROWS 14
#define ACC_TSTTBLROWSIZE 40

/* used in it_bdy1.c */
#define ACC_REASON_NOTUSED  255
#define ACC_CAUSE_NOTUSED   255
#define ACC_STATUS_NOTUSED  255
#define ACC_RESULT_NOTUSED  255

/* Test sequence list maximum length */
#define ACC_TSTSEQLEN 255

/* Test name's maximum length */
#define ACC_TSTIDSZE 10

/* Print Buffer size */
#define SB_PRNTBUF_SIZE 512
#define MSG_SIZE        128
/* sb013.103: Message size */
#define MSG_SIZE_MAX    512

#define MAX_PKT_SIZE    1000 /*32767*/

#define MAX_QUEUE_SIZE  100
#define FLC_TR_SIZE     95

/* defines for delay Cntr */
#define DELAY_CNTR_INIT         0
#define DELAY_CNTR_MAX          8
/* sb014.103: Define ticks per second according to SS_TICKS_SEC */
#define SB_ACC_1_SECOND         (SS_TICKS_SEC == SS_100MS) ? 10 : ((SS_TICKS_SEC == SS_10MS) ? 100 : 1000)
#define WAIT                    10
#define DONT_WAIT               11
#define TIMEOUT                 12
#define HOLD_TEST_INIT          0
#define HOLD_TEST_MAX           500

/* Maximum number of Tests */
#define SB_MAX_TESTS            255

/* defines for configuration */
#define TSTREG       DFLT_REGION      /* memory region id */
#define TSTPOOL      DFLT_POOL        /* memory pool id */
#define TSTINST_0    0                /* instance */
#define SEL_LC       0                /* selector: loosely-coupled */
#define SEL_TC       1                /* selector: tightly-coupled */


/* Define the SAPs for the upper and lower layer */
#define SUID_0                  0
#define SUID_1                  1
#define SUID_2                  2
#define SUID_3                  3
#define SUID_4                  4
#define SPID_0                  0
#define SPID_1                  1
#define SPID_2                  2
#define SPID_3                  3
#define SPID_4                  4

/* Define endpoints for the SCTP */
#define SUENDPID_0              0
#define SUENDPID_1              1
#define SUENDPID_2              2
#define SPENDPID_0              3             /* INIT value */
#define SPENDPID_1              4             /* INIT value */
#define SPENDPID_2              5             /* INIT value */

/*Define association ID's */
#define SPASSOCID_0             0             /* INIT value */
#define SPASSOCID_1             1             /* INIT value */
#define SPASSOCID_2             2             /* INIT value */
#define SUASSOCID_0             3
#define SUASSOCID_1             4
#define SUASSOCID_2             5
#define ASSOC_1                 6             /* Referring to association 1 */
#define ASSOC_2                 7             /* Referring to association 2 */
#define ASSOC_3                 8             /* Referring to association 3 */
/* sb046.102: Multiple IP address per Endp */
#define ASSOC_4                 9             /* Referring to association 4 */
#define ASSOC_5                 10             /* Referring to association 4 */

/*Arbitrary parameters used in the chunks */
#define ACC_INIT_LOCTAG         25      /* the initiate tag used in the INIT_ACK chunk */
#define ACC_INIT_PEERTAG        22      /* the initiate tag used in the INIT chunk */
#define ACC_INIT_TSN            25
#define ACC_ERROR_VERTAG        13
#define ACC_ARWND_INIT          4096
#define MAXPARVAL               10       /* maximum number of parameters expected for INIT/INITACK */
#define MAXFRAGSACK             20       /* maximum number of fragments that may be acknowledged */
#define ACC_RESERVED            0        /* set value of reserved parameter */
#define ACC_STREAMID            2        /* set value of StreamId  */
#define ACC_MEAS_STALE          0        /* set to zero - sender does not provide this informative  */
#define ACC_MTU_INIT            1024     /* size of MTU in octets */
#define ACC_RTO_INIT            150      /* initial value of RTO */
#define ACC_RTO_SHORT           10       /* initial value of RTO */
/* Type used to differentiate between Init and Cookie AssocInd */
#define ACC_INIT                1        /* AssocInd contains init paramters */
#define ACC_COOKIE              0        /* AssocInd contains cookie  paramters */

/* Specific referencing to a specific SAP */
#define SAP_1                      1
#define SAP_2                      2
#define SAP_3                      3
#define GEN                        4
#define SAP_4                      5
#define SAP_5                      6
/* sb046.102: Multiple IP address per Endp */
#define SAP_6                      7


/* Define the port numbers */
#define LOCALPORT_0                  5
#define LOCALPORT_1                  1
#define PEERPORT_0                   3
#define PEERPORT_1                   4

/* Define the service user connection ID */
#define SPCONID_0                 5
#define SPCONID_1                 6
#define SUCONID_0                 0
#define SUCONID_1                 1

/*Define indices into the following Arrays */
#define SU                    0
#define SP                    1

/* The different timertypes */
#define ACC_T1_INIT                    0
#define ACC_T2_SDOWN                   1
#define ACC_TINT                       2
#define ACC_T3RTX                      3
#define ACC_HBEAT                      4
#define ACC_T1_COOKIE                  5
#define STOPPED                        FALSE
#define RUNNING                        TRUE

/*  The incoming upper layer events used in it_bdy1.c, sb_acc*.c, sb_act*.c */
#define ACC_EVT_BND_CFM                 0
#define ACC_EVT_ENDPOPEN_CFM            1
#define ACC_EVT_ENDPCLOSE_CFM           2
#define ACC_EVT_ASSOC_IND               3
#define ACC_EVT_ASSOC_CFM               4
#define ACC_EVT_SETPRI_CFM              5
#define ACC_EVT_HBEAT_CFM               6
#define ACC_EVT_DAT_IND                 7
#define ACC_EVT_TERM_IND                8
#define ACC_EVT_TERM_CFM                9
#define ACC_EVT_STA_IND                 10
#define ACC_EVT_STA_CFM                 11
#define ACC_EVT_FLC_IND                 12

/*  The incoming lower layer events used in tu_bdy1.c, sb_acc*.c, sb_act*.c */

#define ACC_EVT_BND_REQ                 13
#define ACC_EVT_UBND_REQ                14
#define ACC_EVT_SERVOPEN_REQ            15
#define ACC_EVT_DISC_REQ                16
#define ACC_EVT_UDAT_REQ                17
/*  The incoming/outgoing layer manager events used in smsbbdy1.c, sb_acc*.c, sb_act*.c */

#define ACC_EVT_CFG_CFM                 18
#define ACC_EVT_CNTRL_CFM               19
#define ACC_EVT_TRC_IND                 20
#define ACC_EVT_STS_CFM                 21
#define ACC_EVT_CFG_REQ                 22
#define ACC_EVT_CNTRL_REQ               23
#define ACC_EVT_STS_REQ                 24
#define ACC_EVT_STA_REQ                 25
#define ACC_EVT_NO_RESP                 26
#define ACC_EVT_UNKNOWN                 27

/*  The outgoing layer manager events used in smsbbdy1.c */
#define ACC_EVT_UDAT_IND                28

/* sb042.102: Add values for SHT interface */
#ifdef SB_FTHA
#define ACC_EVT_SHT_CNTRL_CFM           29
#endif

/* The layer manager also has STA_IND and STA_CFM */

 /*
 *  verification status returned by AccChk routines
 *  used for printing appropriate error msg from the
 *  sbAccDispErrTstRslt
 */
#define PRIMITIVE_NOT_RECV       1
#define PRIMITIVE_FAILED         0
#define TIMEOUT_ON_PRIM          2
#define INC_TRANSID              3
#define INC_MSGTYPE              4      /* e.g. TCFG, TCNTL etc */
#define INC_EVNTTYPE             5      /* primitive type */
#define INC_ELMT                 6      /* element id */
#define INC_SUID                 7      /* service user Id */
#define INC_CONNID               8      /* service user connection Id */
#define INC_STATUS               9
#define INC_REASON               10
#define INC_EVNT                 11     /* Incorrect alarm event */
#define INC_CAUSE                12     /* Incorrect alarm cause */
#define INC_TYPE                 13
#define INC_DATA                 14     /* Data received incorrect */
#define INC_DATA_LEN             15     /* Packet len of data received incorrect */
#define INC_ADLER                16     /* Incorrect adler */
#define INC_NO_RECV              17     /* Incorrect number of packets recived */
#define NO_FLCIND_RECV           18     /* No FlcInd received */
#define INV_CHUNK_RECV           19     /* Invalid message received */
#define INV_INFO                 20     /* Invalid sta/sts buildPar */
#define STS_CNTR_NOT_ZERO        21     /* Stats counters not zero */
#define STS_SENT_PCKTS_INC       22     /* Stats - number of sent packets incorrect */
#define INV_PROT                 23     /* Invalid protocol */
#define INV_STATE                24     /* Invalid state */
#define INV_VER                  25     /* Invalid version */
#define INV_PART_NR              26     /* Invalid part number */
#define INC_RESULT               27     /* Incorrect result ID */
#define INC_ENDP_ID              28     /* Incorrect endpoint ID */
#define INC_SAP                  29     /* Incorrect SAP ID */
#define INC_SPID                 30     /* Incorrect spId */
#define PRIMITIVE_SUCCEED        31     /* primitive succeeds */
#define INC_TMRSTATE             32     /* Timer state incorrect */
#define INV_COOKIE               33     /* Invalid cookie */
#define INV_VERTAG               34     /* Invalid verification tag */
#define INC_PORT                 35     /* Incorrect port */
#define INV_CAUSECODE            36     /* Invalid causecode with chunk */
#define INV_SEGM                 37     /* Invalid segmentation */
#define INC_ADDR                 38     /* Incorrect address */
#define INC_INDTYPE              39     /* Incorrect indication type */
#define INC_ASSOC_ID             40     /* Incorrect association ID */
#define NO_LCTEST                41     /* No test in the loosely coupled state*/
#define NO_TEST                  42     /* No test with this number currently listed */
#define NO_SUBTEST               43     /* No test with this number currently listed */
#define BUFF_EMPTY               44     /* The buffer is empty */
#define INC_RTRVINFO             45     /* Incorrect datagram retrieval info*/
#define INC_RWND                 46     /* Incorrect RWND */
#define INC_STRM                 47     /* Incorrect number of streams */
#define INC_TSN                  48     /* Incorrect TSN */
#define INC_SACKFRAG             49     /* Incorrect SACK fragments */
#define INC_STSCNTR              50      /* Incorrect statistics counter */

/* Reasons - for test code only */
#define NO_DATCFM_NOK            50     /* No data confirm with status = NOK */


#define DEQUE_ERROR              7
#define NMB_ERRMSG               8     /* number of columns in ErrMsgMatrix */

#define SBUT_TXPKTRANDSIZE       0     /* Used with sbGetPacket*/
#define SBUT_TXPKTFIXEDSIZE      1

/* Message queue size */
#define SB_ACC_MSG_QSIZE 200

/* Test sequence terminator */
#define SB_END_TST_CASES 200

/* sb060.102 : TOS changes */
#ifdef SCT3
/* SCT TOS */
#define SB_ACC_SCT_TOS 0
#endif /* SCT3 */

#ifdef SS_MULTIPLE_PROCS

#define PROC_MP_ID0 1000

#define SFndProcId() PROC_MP_ID0

#define SRegTTsk(_ent, _inst, _type , _pri, _actvInit, _actvTsk)   \
        SRegTTsk(PROC_MP_ID0,_ent, _inst, _type , _pri, (PAIFS16)_actvInit,  \
                 (ActvTsk)_actvTsk)

#define SAttachTTsk(_ent, _inst, _sId)  \
        SAttachTTsk(PROC_MP_ID0, _ent, _inst, _sId)

#endif /* SS_MULTIPLE_PROCS */



/* Macros for the tests  */
/* Alternative to strCmp library function */

#define SB_SCTSAPCFG(specCfg)                                     \
{                                                                 \
  if(isBitSet(sbAccCb.curTst.bSctSapCfgMask, specCfg) == FALSE )  \
  {                                                               \
    sbStdSctSapCfg(&sbMgmt, specCfg);                             \
    sbSendConfigReq(&sbMgmt, STSBSCTSAP, specCfg);                \
  }                                                               \
}

#define SB_TSAPCFG(specCfg)                         \
{                                                   \
  if(isBitSet(sbAccCb.curTst.bTSapCfgMask, specCfg) == FALSE )  \
  {                                                 \
    sbStdTSapCfg(&sbMgmt, specCfg);                 \
    sbSendConfigReq(&sbMgmt, STSBTSAP, specCfg);      \
  }                                                 \
}

#define SB_GENCFG()                                 \
{                                                   \
  if(isBitSet(sbAccCb.curTst.bConfigMask, BIT0) == FALSE )  \
  {                                                 \
    sbStdGenCfg(&sbMgmt);                           \
    sbSendConfigReq(&sbMgmt, STSBGEN, GEN);           \
  }                                                 \
}
/* sb003.103: SATELLITE SCTP feature */ 
#define SB_PATHPROFCFG()                                 \
{                                                   \
  if(isBitSet(sbAccCb.curTst.bPathProfCfgMask, BIT1) == FALSE )  \
  {                                                 \
    sbStdPathProfCfg(&sbMgmt);                           \
    sbSendConfigReq(&sbMgmt, STSBPATHPROF, GEN);           \
  }                                                 \
}
/* sb003.103: SATELLITE SCTP feature */ 
#define SB_DESTADDRCFG()                                 \
{                                                   \
   if ((isBitSet( sbAccCb.curTst.bConfigMask, BIT1) == TRUE) && (isBitSet( sbAccCb.curTst.bConfigMask, BIT2) == FALSE))\
  {                                                 \
    sbStdDstAddrCfg(&sbMgmt);                           \
    sbSendConfigReq(&sbMgmt, STSBDSTADDR, GEN);           \
  }                                                 \
}
 
#define SB_SETUP_ASSOC_1()     /*Include primary and destination address list later */        \
   {                                                       \
  if ( isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == FALSE ) { \
     /* SCT parameters */                                  \
     assoc_1.spId = SPID_0;                                \
     assoc_1.suId = SUID_0;                                \
     assoc_1.suEndpId = SUENDPID_0;                        \
     assoc_1.peerPort =  PEERPORT_0;                         \
     assoc_1.localPort = LOCALPORT_0;                          \
     assoc_1.suAssocId =  SUASSOCID_0;                     \
     assoc_1.outStrms = genCfg->maxNmbOutStrms;              \
     SB_SETUP_CMNETADDR((assoc_1.priPeerNAddr), peerNAddrLst_2[2] )     \
     SB_SETUP_CMNETADDR((assoc_1.intfNAddr),  localNAddrLst_1[1] )      \
     SB_SETUP_SCTNETADDRLST(assoc_1.peerNAddrLst, peerNAddrLst_1)      \
     SB_SETUP_SCTNETADDRLST(assoc_1.localNAddrLst, localNAddrLst_1)      \
     /* set up transport addresses for the HIT primitives */                                   \
     SB_SETUP_CMNETADDR(assoc_1.intfNAddr,  localNAddrLst_1[2] )                                 \
     SB_SETUP_CMTPTADDR(assoc_1.localTAddr, assoc_1.intfNAddr, assoc_1.localPort)                   \
     SB_SETUP_CMTPTADDR(assoc_1.peerTAddr, assoc_1.priPeerNAddr, assoc_1.peerPort)                 \
     assoc_1.verTag = ACC_INIT_LOCTAG;                                                          \
     assoc_1.suConId = SUCONID_0;                                                              \
     assoc_1.spConId = SPCONID_0;                                                              \
     SB_BIND_SCTSAP(assoc_1.suId, assoc_1.spId, BIT0)                                          \
     if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE) {                                    \
        SB_OPEN_ENDP(assoc_1, BIT0)        }                                                   \
     buildPar.misChunk = FALSE; /* no parameters in chunk builds should be skipped */          \
     setBit(&sbAccCb.curTst.bAssocSetupMask, BIT0);                                            \
  }                                                                                            \
}

#define SB_SETUP_ASSOC_2()      /*Include primary and destination address list later */   \
  {                                                              \
  if ( isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT1) == FALSE ) { \
     assoc_2.spId = SPID_1;                                \
     assoc_2.suId = SUID_1;                                \
     assoc_2.suEndpId = SUENDPID_1;                        \
     assoc_2.localPort =  LOCALPORT_1;                         \
     assoc_2.peerPort =  PEERPORT_1;                         \
     assoc_2.suAssocId =  SUASSOCID_1;                     \
     assoc_2.outStrms = genCfg->maxNmbOutStrms;            \
     assoc_2.verTag = ACC_INIT_TAG;                        \
     SB_SETUP_CMNETADDR(assoc_2.priPeerNAddr, peerNAddrLst_2[2] )     \
     SB_SETUP_CMNETADDR(assoc_2.intfNAddr,  localNAddrLst_2[1] )      \
     SB_SETUP_SCTNETADDRLST(assoc_2.peerNAddrLst, peerNAddrLst_2)      \
     SB_SETUP_SCTNETADDRLST(assoc_2.scrNAddrLst, localNAddrLst_2)      \
     /* set up transport addresses for the HIT primitives */                           \
     SB_SETUP_CMNETADDR(assoc_2.intfNAddr,  localNAddrLst_2[2] )                          \
     SB_SETUP_CMTPTADDR(assoc_2.localTAddr, assoc_2.intfNAddr, assoc_2.localPort)            \
     SB_SETUP_CMTPTADDR(assoc_2.peerAddr, assoc_2.priPeerNAddr, assoc_2.peerPort)          \
     assoc_2.spConId = SPCONID_1;                                                      \
     SB_BIND_SCTSAP(assoc_2.suId, assoc_2.spId, BIT1)                                   \
     assoc_2.suConId = SUCONID_1;                                                       \
     if (isBitSet(sbAccCb.curTst.bSapMask, BIT1) == TRUE) {                             \
        SB_OPEN_ENDP(assoc_2, BIT1)                }                                    \
     setBit(&sbAccCb.curTst.bAssocSetupMask, BIT1);                                     \
  }                                                                                     \
}


/* sb032.102 :  IPV6 Support Added */ 
#define SB_SETUP_CMNETADDR(dAddr, sAddr)  /* initialize a network address */     \
{                                                                                \
 if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4) \
 { \
   /* sb058.102 : Changed to remove compilation warning */ \
   cmMemcpy((U8*)&dAddr.u.ipv4NetAddr, (U8*)&sAddr, CM_IPV4ADDR_SIZE); \
   dAddr.type = CM_TPTADDR_IPV4;                                                \
 }\
 else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6) \
 { \
   cmMemcpy((U8*)&dAddr.u.ipv6NetAddr, (U8*)sAddr, CM_IPV6ADDR_SIZE); \
   dAddr.type = CM_TPTADDR_IPV6; \
 } \
}

/* sb032.102 :  IPV6 Support Added */ 
#define SB_SETUP_CMTPTADDR(dAddr, sAddr, inPort)  /* initialize a tranport address */  \
{                                                                                    \
   if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4) \
   {   \
   /* sb058.102 : Changed to remove compilation warning */ \
   cmMemcpy((U8*)&dAddr.u.ipv4TptAddr.address, (U8*)&sAddr, CM_IPV4ADDR_SIZE); \
   dAddr.type = CM_TPTADDR_IPV4;      /* IPV4 addresses  */                          \
   dAddr.u.ipv4TptAddr.port = inPort;                                              \
   }    \
   else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)   \
   {      \
      dAddr.type = CM_TPTADDR_IPV6;   \
      cmMemcpy((U8*)dAddr.u.ipv6TptAddr.ipv6NetAddr, (U8*)sAddr, CM_IPV6ADDR_SIZE); \
      dAddr.u.ipv6TptAddr.port = inPort;  \
   } \
}

/* SB_VER13 fixed the bug of -- i<=dAddr.nmb -- */
#define SB_SETUP_SCTNETADDRLST(dAddr, sAddr)  /* initialize a tranport address */    \
{                                                                                     \
   dAddr.nmb = 5;                                                                    \
   for(i = 0; (i < dAddr.nmb); ++i)  {                                               \
     dAddr.nAddr[i].type = CM_TPTADDR_IPV4;  /* IPV4 addresses  */                   \
     dAddr.nAddr[i].u.ipv4NetAddr = sAddr[i];                                        \
   }                                                                                 \
}

#define SB_SETUP_ENDPOPENREQ(assoc, sapId, endpId, port, localAddr)   /* initialize parameters for EndpOpenReq */     \
{   assoc.spId = sapId;                                                            \
   assoc.suEndpId = endpId;                                                       \
   assoc.localPort = port;                                                          \
   SB_SETUP_CMNETADDR(assoc.localNAddr, localAddr )                                  \
}

#define SB_OPEN_ENDP(assoc,  bit)  /* Open an endpoint */                                \
{                                                                                         \
if((isBitSet(sbAccCb.curTst.bEndpMask, bit) == FALSE ))                                   \
{                                                                                         \
   sbSendEndpOpenReq(assoc);                                                              \
}                                                                                         \
}


#define SB_BIND_SCTSAP(suId, spId, bit)  /* bind SCT SAP */                                 \
{                                                                                           \
 if((isBitSet(sbAccCb.curTst.bSapMask, bit) == FALSE ))                                     \
  {                                                                                         \
     sbSendSctBndReq(suId, spId);                                                           \
  }                                                                                         \
}



#define SB_BIND_HITSAP(suId, spId, bit)  /* bind TSAP */                                    \
{                                                                                           \
  if(isBitSet(sbAccCb.curTst.bTSapMask, bit) == FALSE )                                     \
  {                                                                                         \
   sbSendHitBndReq(suId, spId);                                                             \
  }                                                                                         \
}

#define SB_EST_ASSOC(assoc, bit)  /* establish an association */                            \
{                                                                                           \
  if(isBitSet(sbAccCb.curTst.bAssocMask, bit) == FALSE )                                    \
  {                                                                                         \
     setupAssocSnd(&assoc, &buildPar);                                                      \
  }                                                                                         \
}

#define SB_DISABLE_TRACE()  /* disable the message tracing */                               \
{                                                                                           \
  if(isBitSet(sbAccCb.curTst.bTraceMask, BIT0) == FALSE )                                   \
  {                                                                                         \
     sbDisAbleTrace(&sbMgmt);                                                                \
  }                                                                                         \
}

#define SB_ENABLE_DEBUGP(dbgMask)  /* enable the message tracing */                         \
{                                                                                           \
  if(isBitSet(sbAccCb.curTst.bDebugPMask, BIT0) == FALSE )                                  \
  {                                                                                         \
     sbEnableDebugP(dbgMask);                                                                \
  }                                                                                         \
}

#define SB_SUBTESTFAIL()  /* set all the flags for an unsuccessful subtest */               \
{                                                                                           \
   sbAccCb.curTst.bTestsCompleted = TRUE;                                                   \
   sbAccCb.curTst.bBusyCleanup = TRUE;                                                      \
   sbAccCb.curTst.bBusySubtest = FALSE;                                                     \
   sbAccCb.curTst.bBusyPreTestConf = FALSE;                                                 \
}

#define SB_ENTERTEST(mask, bit)  /* enter test if the cond is met */                        \
{                                                                                           \
 if (  isBitSet(mask, bit)  == TRUE  )                                                      \
 {                                                                                          \
   sbAccCb.curTst.tickLstDoneFlg = TRUE;                                                    \
   sbAccCb.curTst.bBusySubtest = TRUE;       /* Now do a test */                            \
   sbAccCb.curTst.bBusyPreTestConf = FALSE;  /* Done with pre-test setup */                 \
 }                                                                                          \
}

#define SB_CLEAN()  /* resetting flags after shutdown have been completed */                \
{                                                                                           \
      sbAccCb.curTst.bBusyCleanup = FALSE;                                                  \
      sbAccCb.curTst.bConfigDeleted = FALSE;                                                 \
                                                                                             \
      /* Check if all subtests were executed */                                              \
      if (sbAccCb.curTst.bTestsCompleted == TRUE)                                            \
         {                                                                                   \
         sbAccCb.curTst.bCompleted = TRUE;  /* Done with this test */                        \
         }                                                                                   \
      else  /* Continue with next test */                                                    \
      {                                                                                      \
         /* Reset masks and pre-test config must be done. */                                 \
         sbAccCb.curTst.bBusyPreTestConf = TRUE;                                             \
         sbAccCb.curTst.bConfigMask = 0;                                                     \
         sbAccCb.curTst.bSctSapCfgMask = 0;                                                  \
         sbAccCb.curTst.bTSapCfgMask   = 0;                                                  \
         sbAccCb.curTst.bSapMask    = 0;                                                     \
         sbAccCb.curTst.bAssocMask  = 0;                                                     \
         sbAccCb.curTst.bTSapMask = 0;                                                       \
         sbAccCb.curTst.bEndpMask = 0;                                                       \
         sbAccCb.curTst.bAssocMask = 0;                                                      \
         sbAccCb.curTst.bAssocSetupMask = 0;                                                 \
         sbAccCb.curTst.bSapMask = 0;                                                        \
         sbAccCb.curTst.bTraceMask = FALSE;                                                  \
         sbAccCb.curTst.bDebugPMask = FALSE;                                                 \
         sbAccCb.curTst.state = 0;                                                           \
        }      /*end else */                                                                 \
}

/* Calculate the checksum of the parameters common to all the chunks */
#define SB_ADLER_CM(adler)                                                                  \
{                                                                                           \
   checksum = 0;                                                                  \
   adler = sbChecksum32(adler,(U8 *) &srcPort, sizeof(srcPort) );                                       \
   adler = sbChecksum32(adler,(U8 *) &dstPort, sizeof(dstPort) );                                       \
   adler = sbChecksum32(adler,(U8 *) &verTag, sizeof(verTag) );                                         \
   adler = sbChecksum32(adler,(U8 *) &checksum, sizeof(checksum) );                                     \
   adler = sbChecksum32(adler,(U8 *) &chunkId, sizeof(chunkId) );                                       \
   adler = sbChecksum32(adler,(U8 *) &chunkFlg, sizeof(chunkFlg) );                                     \
   adler = sbChecksum32(adler,(U8 *) &chunkLeng, sizeof(chunkLeng) );                                   \
}
 /*Initialize common parameters and calculate their Adler checksum */
#define SB_BUILD_CM()                                                                  \
{                                                                                           \
   srcPort =  assoc->peerPort;    /* Set up for specific sending endpoint in this case  */ \
   dstPort = assoc->localPort;     /* Set up for the specific receiving endpoint */         \
   verTag = assoc->verTagPeer;                                                              \
   chunkFlg = 0;                                                                            \
   SB_ADLER_CM(adler)                                                                        \
}

/* Perform packing functions common to all the chunk builds */
#define SB_PACK_CM()                             \
{                                                \
   SB_PKU16(chunkLeng);                         \
   SB_PKU8(chunkFlg);                           \
   SB_PKU8(chunkId);                            \
/*   SB_PKU32(adler);   */                          \
   SB_PKU32(verTag);                            \
   SB_PKU16(srcPort);                           \
   SB_PKU16(dstPort);                           \
}

/* Perform unpacking functions common to all the chunk checks */
#define SB_UNPACK_CM()                                         \
{                                                              \
   SB_UNPKU16(localPort);      /* Pop Destination Port */   \
   SB_UNPKU16(peerPort);      /* Pop source port */        \
   SB_UNPKU32(verTag);                                     \
   SB_UNPKU32(adlerRcv);     /* Pop Adler checksum */     \
   SB_UNPKU8(chunkId);                                    \
   SB_UNPKU8(chunkFlg);                                   \
   SB_UNPKU16(chunkLeng);                                 \
}



#define SB_HITMSGCMP(datRcv, mBufRec, ret)              \
 {       lenRec = 0;                                    \
         dataRec = 0;                                   \
         if ( mBufRec != (Buffer *) NULLP )             \
         {                                              \
            SFndLenMsg(mBufRec,(MsgLen *) &lenRec);     \
         } else{                                        \
            SPrint("Recorded buffer not allocated \n ");\
         }                                              \
         len = sbAccCb.curTst.datRcvLen;                \
               sprintf(prntBuf, "expected  length: %u\n", lenRec); \
                    SPrint(prntBuf);                               \
              sprintf(prntBuf, "received length: %u\n", len);      \
                    SPrint(prntBuf);                               \
         if (len != lenRec)                                        \
         {                                                         \
            buildPar->status = INC_DATA_LEN;                       \
            *status = INC_DATA_LEN;                                \
            ret = RFAILED;                                         \
         }                                                         \
         else                                                      \
         {  \
            ret = ROK;                                             \
            for (i = 0; i < (U32)lenRec; i++)                      \
            {  if ( mBufRec != (Buffer *) NULLP )   {              \
               SExamMsg((Data *)&dataRec, mBufRec,(S16)i);         \
              }                                                    \
               if (datRcv[i] != dataRec)                           \
               {                                                   \
                   sprintf(prntBuf, "expected  data: %u\n", dataRec); \
                    SPrint(prntBuf);                               \
                    sprintf(prntBuf, "received  data: %u\n", datRcv[i]);\
                      SPrint(prntBuf); \
                  *status = INC_DATA;                                 \
                  buildPar->status = INC_DATA;                        \
                  ret = RFAILED;                                      \
                  break;                                              \
               } /* end if */                                         \
            }    /* end for */                                        \
         }       /* end if/else */                                    \
 }

#define SB_SCTMSGCMP(mBuf, mBufRec)                                       \
 {                                                                        \
         len = 0;                                                         \
         lenRec = 0;                                                      \
         data = 0;                                                        \
         dataRec = 0;                                                     \
          if( ( mBuf != (Buffer *) NULLP )&& ( mBuf != (Buffer *) NULLP )) \
         {                                                                \
            SFndLenMsg(mBuf,(MsgLen *) &len);                             \
            SFndLenMsg(mBufRec,(MsgLen *) &lenRec);                       \
         } else {                                                         \
           SPrint("Buffers not allocated \n\n ");                         \
         }                                                                \
           sprintf(prntBuf, "\n\n received  len: %u\n\n\n", len);         \
                    SPrint(prntBuf);                                      \
          sprintf(prntBuf, "recorded  len: %u\n\n\n", lenRec);            \
                    SPrint(prntBuf);                                      \
         if (len != lenRec)                                               \
         {                                                                \
            *status = INC_DATA_LEN;                                       \
            RETVALUE(RFAILED);                                            \
         }                                                                \
         else                                                             \
         {                                                                \
            for (i = 0; i < (U32)lenRec; i++)                             \
            {                                                             \
               SExamMsg(&data, mBuf, i);                                  \
               SExamMsg(&dataRec, mBufRec, i);                            \
               if (data != dataRec)                                       \
               {                                                          \
                  *status = INC_DATA;                                     \
                  RETVALUE(RFAILED);                                      \
               } /* end if */                                             \
            }    /* end for */                                            \
         }       /* end if/else */                                        \
 }

#define SB_RLSMEM(mBuf)                                       \
{                                                             \
      /* Release memory  */                                   \
      if (mBuf != (Buffer *)NULLP)                            \
         {                                                    \
            (Void) SPutMsg(mBuf);                             \
            mBuf = (Buffer *)NULLP;                           \
         }                                                    \
 }

#define SB_SETUP_ORDERED_DATA(seq, transn)                                  \
{                                                                           \
    buildPar.seqNr = seq;                                                   \
    buildPar.tsn = transn;                                                  \
    buildPar.streamId = ACC_STREAMID;                                      \
    buildPar.chunkFlg = 3; /*unsegmented data + ordered */                       \
}

#define SB_SETUP_UNORDERED_DATA(transn)                                      \
{                                                                            \
    buildPar.tsn = transn;                                                   \
    buildPar.streamId = ACC_STREAMID;                                      \
    /* buildPar.chunkFlg = 3 + (4 & (buildPar.unOrderFlg) );   */               \
    buildPar.chunkFlg = 7; /*unsegmented data +un ordered */                       \
}

#define SB_SETUP_HBEAT_CFM(assoc, rslt, sta, cse)                       \
{                                                                       \
   oper.it.result = rslt;                                               \
   oper.it.status = sta;                                                \
   oper.it.cause = cse;                                                 \
   oper.it.suId = assoc.suId;                                           \
   oper.it.suAssocId = assoc.suAssocId;                                 \
   (Void) cmMemcpy((U8 *) &(oper.it.peerNAddr),                         \
                              (U8 *) &( assoc.priPeerNAddr),            \
                              (PTR) sizeof(CmNetAddr) );                \
}


#define SB_SETUP_CHUNK_INFO(cse, sta, extLtFlg, type)        \
{                                                                       \
    buildPar.cause = cse;                                            \
    buildPar.status = sta;                                          \
    buildPar.extLifetimeFlg = extLtFlg;                          \
    buildPar.chunkId = type;                                         \
}

#define SB_SETUP_SACK_INFO(start, end, cTsn)                                \
{                                                                           \
    buildPar.chunkId = SB_ID_SACK;                                          \
    buildPar.numFrag = 1;                                                   \
    buildPar.cumTsn = cTsn;                                                 \
    buildPar.fragStart[1] =  start;                                         \
    buildPar.fragEnd[1] =    end;                                           \
    buildPar.arwnd = ACC_ARWND_INIT;                                        \
    buildPar.nmbDup = 0;  /*default value */                                \
}
/* sb018.103: Added new macro for the SACK gap-ack */
#define SB_SETUP_SACK_INFO1(start1, end1, start2, end2, cTsn) \
{                                                               \
    buildPar.chunkId = SB_ID_SACK;                                          \
    buildPar.numFrag = 2;                                                   \
    buildPar.cumTsn = cTsn;                                                 \
    buildPar.fragStart[1] =  start1;                                         \
    buildPar.fragEnd[1] =    end1;                                           \
    buildPar.fragStart[2] =  start2;                                         \
    buildPar.fragEnd[2] =    end2;                                           \
    buildPar.arwnd = ACC_ARWND_INIT;                                        \
    buildPar.nmbDup = 0;  /*default value */                                \
}
#define SB_SETUP_BUILDPAR(assoc)                                        \
{                                                                       \
    buildPar.peerPort = assoc.peerPort;                                   \
    buildPar.localPort = assoc.localPort;                                   \
    buildPar.extLifetimeFlg = genreCfg->altAcceptFlg;                   \
    buildPar.chunktype = type;                                         \
}

/* sb032.102 :  IPV6 Support Added */ 
#define SB_SETUP_IPHDR_PAR(bit)                                         \
{                                                                       \
   if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)                       \
   {                                                                    \
    hdrParm.type = CM_HDRPARM_IPV4;                                     \
    hdrParm.u.hdrParmIpv4.proto.pres = TRUE;                            \
    hdrParm.u.hdrParmIpv4.proto.val = CM_PROTOCOL_SCTP;                 \
    hdrParm.u.hdrParmIpv4.dfBit.pres = TRUE;                           \
    hdrParm.u.hdrParmIpv4.dfBit.val = bit;     /*don't fragment bit */      \
    hdrParm.u.hdrParmIpv4.tos.pres = FALSE;                             \
    hdrParm.u.hdrParmIpv4.ttl.pres = FALSE;                             \
   }                                                                    \
   else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)                  \
   {                                                                    \
    cmMemset((U8*)&hdrParm, 0, sizeof(CmIpHdrParm));                    \
   }                                                                    \
}


/* Makro for setting up of the Primitive parameters */
#define SB_SETUP_ENDPOPEN_CFM(assoc, results, causes)                    \
{                                                                        \
     oper.it.suId =assoc.suId;                                          \
     oper.it.suEndpId = assoc.suEndpId;                                  \
     oper.it.result = results;                                           \
     oper.it.cause = causes;                                             \
}

#define SB_SETUP_ENDPCLOSE_CFM(assoc, results, causes)                  \
{                                                                       \
     oper.it.suId = assoc.suId;                                         \
     oper.it.suEndpId = assoc.suEndpId;                                 \
     oper.it.result = results;                                          \
     oper.it.cause = causes;                                            \
}

#define SB_SETUP_TERM_CFM(_assoc, _results, _causes) \
{                                                 \
    oper.it.suId = _assoc.suId;                    \
    oper.it.suAssocId = _assoc.suAssocId;          \
    oper.it.result = _results;                     \
    oper.it.cause = _causes;                       \
}

#define SB_SETUP_TERM_IND(assoc, sta, cse) \
{                                                 \
    oper.it.suId = assoc.suId;                    \
    oper.it.suAssocId = assoc.suAssocId;          \
    oper.it.spAssocId = assoc.spAssocId;          \
    oper.it.assocIdType = SCT_ASSOCID_SU;         \
    oper.it.status = sta;                         \
    oper.it.cause = cse;                          \
}

/*-- RFC 4460 -- MLK Fix */
#define SB_SETUP_BUNDLDAT_REQ(mBuf)                                        \
{                                                                          \
    SB_RLSMEM(sbAccCb.curTst.gmBuf);\
    sbGetPacket(&sbAccCb.curTst.gmBuf, SBUT_TXPKTFIXEDSIZE, 64);           \
    SAddMsgRef(sbAccCb.curTst.gmBuf, DFLT_REGION, DFLT_POOL, &(mBuf));     \
    sbGetPacket(&tmpBuf, SBUT_TXPKTFIXEDSIZE, 64);                         \
    (Void) SCatMsg(sbAccCb.curTst.gmBuf, tmpBuf, M2M1);                    \
    SPutMsg(tmpBuf);                                                       \
}

/*-- RFC 4460 -- MLK Fix */
#define SB_SETUP_DAT_REQ(mBuf)                                             \
{                                                                          \
    SB_RLSMEM(sbAccCb.curTst.gmBuf);\
    sbGetPacket(&sbAccCb.curTst.gmBuf, SBUT_TXPKTFIXEDSIZE, 64);           \
    SAddMsgRef(sbAccCb.curTst.gmBuf, DFLT_REGION, DFLT_POOL, &(mBuf));     \
}

#define SB_SETUP_ASSOC_CFM(assoc)                                                               \
  {                                                                                             \
  oper.it.suId = assoc.suId;                                                                    \
  oper.it.suAssocId = assoc.suAssocId;                                                          \
  (Void) cmMemcpy((U8  *)&(oper.it.peerNAddrLst), (U8  *)&(assoc.peerNAddrLst),                       \
  (S32)PRNTSZE);                                                                                \
  oper.it.peerPort = assoc.peerPort;                                                              \
  oper.it.outStrms = assoc.outStrms;                                                            \
  }

#define SB_SETUP_ASSOC_IND(assoc, _typeConst)                                          \
{                                                                                      \
   S32 _type;                                                                          \
                                                                                       \
   _type = (S32)_typeConst;                                                            \
   oper.it.suId = assoc.suId;                                                          \
   if (_type == ACC_INIT)                                                              \
   {                                                                                   \
      oper.it.assocParams.type = SCT_ASSOC_IND_INIT;                                   \
      oper.it.assocParams.t.initParams.iTag = ACC_INIT_PEERTAG;                        \
      oper.it.assocParams.t.initParams.a_rwnd =  ACC_ARWND_INIT;                                  \
      oper.it.assocParams.t.initParams.outStrms = buildPar.outStrms;                              \
      oper.it.assocParams.t.initParams.inStrms = buildPar.inStrms;                                \
      oper.it.assocParams.t.initParams.iTsn = (SctTSN) ACC_INIT_TSN;                              \
      oper.it.assocParams.t.initParams.cookieLife =(U32) 500;                                     \
      oper.it.assocParams.t.initParams.peerPort = assoc.peerPort;                                 \
      oper.it.assocParams.t.initParams.localPort = assoc.localPort;                               \
      SB_CPY_NADDRLST(&(oper.it.assocParams.t.initParams.peerAddrLst), &(assoc.peerNAddrLst));    \
      SB_CPY_NADDRLST(&(oper.it.assocParams.t.initParams.localAddrLst), &(assoc.localNAddrLst));  \
   }                                                                                              \
   else if (_type == ACC_COOKIE)                                                                  \
   {                                                                                              \
      oper.it.assocParams.type = SCT_ASSOC_IND_COOKIE;                                            \
      oper.it.assocParams.t.cookieParams.spAssocId = assoc.spAssocId;                             \
      oper.it.assocParams.t.cookieParams.suAssocId = assoc.suAssocId;                             \
      oper.it.assocParams.t.cookieParams.peerPort = assoc.peerPort;                               \
      SB_CPY_NADDRLST(&(oper.it.assocParams.t.cookieParams.peerAddrLst), &(assoc.peerNAddrLst));  \
   }                                                                                              \
}

#define SB_SETUP_STA_CFM(assoc, status, rslt, cse )                                       \
{                                                                                         \
  oper.it.suId = assoc.suId;                                                              \
  oper.it.suAssocId = assoc.suAssocId;                                                    \
  oper.it.peerPort= assoc.peerPort;                                                       \
  oper.it.staType = status;                                                               \
  oper.it.cause = cse;                                                                    \
  oper.it.result = rslt;                                                                  \
}

#define SB_SETUP_STA_IND(assoc, sta, cse)                                            \
  {                                                                                       \
  oper.it.suId = assoc.suId;                                                              \
  oper.it.suAssocId = assoc.suAssocId;                                                    \
  oper.it.spAssocId = assoc.spAssocId;                                                    \
  oper.it.status = sta;                                                                \
  oper.it.cause = cse;                                                                  \
  }

#define SB_SETUP_FLC_IND(assoc, rsn)                                                   \
  {                                                                                       \
  oper.it.suId = assoc.suId;                                                              \
  oper.it.suAssocId = assoc.suAssocId;                                                    \
  oper.it.reason = rsn;                                                                \
  }

#define SB_SETUP_DAT_IND(assoc, tpe)                                                    \
  {                                                                                       \
  oper.it.suId = assoc.suId;                                                              \
  oper.it.suAssocId = assoc.suAssocId;                                                    \
  oper.it.indType.type = tpe;                                                             \
  }

   /* Macro to enter a test function into the test able (used in sb_acc1.c) */

#define SBACCADDTEST(dst, vtestFunc, testIdstr)   \
 {                                                 \
   tstCb.testFunc = vtestFunc;                     \
   sprintf((S8 *)tstCb.testId, testIdstr);         \
   sbTblAddTestSubIndex(dst, &tstCb);              \
 }

#define SBACCPRINT(_arg)               \
 {                                     \
    if (sbAccCb.curTst.prntFlag)       \
    {                                  \
       sprintf _arg;                   \
       SPrint(prntBuf);                \
       SBACCPRINTDELAY();              \
    }                                  \
 }

/* Macro to print error message */
#define SBACCPRNERROR(_arg)            \
 {                                     \
    sprintf _arg;                      \
    SPrint(prntBuf);                   \
    SBACCPRINTDELAY();                 \
 }

#ifdef VW
#define SBACCPRINTDELAY()              \
     {                                 \
        U16 _delay;                    \
         _delay = 1000;                \
        while(_delay--);                 \
     }
#else
#define SBACCPRINTDELAY()
#endif

#ifdef SB_ACC 
#ifndef SS_PS
#define cmInetGetHostByName   sbInetGetHostByName
#endif
#endif

#endif


/********************************************************************30**

         End of file:     sb_acc.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:04 2015

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
          sb042.102   hl   1. Added change for SHT interface and Rolling
                              Up Grade
          sb046.102   hl   1. Multiple IP address per endpoint support
          sb057.102   pr   1. Multiple proc ids support added.
          sb058.102   pr   1. Remove compilation warnings.
          sb060.102   pr   1. TOS changes.
/main/4      --     rsr/ag  1. Updated for Release of 1.3
          sb003.103   ag   1. Satellite SCTP feature: Path Profile and
                              Destination address configuration
	  sb012.103  pkaX  1. Non-Unicast Address Fix: New IPv4 & IPv6 
			      addresses are defined (non-unicast).
          sb013.103  pkaX  1. a_rwnd Fix: Defined Message size.
          sb014.103  pkaX  1. Changed define value of SB_ACC_1_SECOND.
          sb018.103  pkaX  1. Added macro to build a sack header with
                              two gap-ack.
*********************************************************************91*/
