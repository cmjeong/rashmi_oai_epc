
/********************************************************************20**

     Name:    X2AP 

     Type:    C Header file

     Desc:    Macros and hash defines related with test engine

     File:    czac_acc.h

     Sid:      czac_acc.h@@/main/2 - Tue Aug 30 18:35:43 2011

     Prg:     sy 

*********************************************************************21*/


/* cz001.101 : CR Fixes */
/* TODO to be deleted once updated inother files */
/* TODO Only for compilation pourposes */

/***************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define STCZUSAP  1
#define STCZLSAP  2

#define CZAC_MEM_PDU_SIZE 2048

#define CZ_FREE_EVNT_MEM(a)

#define LCZ_PEER_STATE_ACTIVE 1
#define LCZ_USTA_DGNVAL_PEERID 3
#define LCZ_MAX_NO_OF_PEERS   10

#define LCZ_MAX_MME_GROUP  10

/* Hash defines used by CZT Interface */
#define CZT_CAUSE_INV_UNKNOWN 33
#define CZT_CON_ST_CONNECTED  38

#define CZAC_GP         0
#define CZAC_BMP        1
#define CZAC_ERR        2

/* SCT EVENTS */
#define EVTSCTBNDREQ        1
#define EVTSCTSTAREQ        2
#define EVTSCTENDPOPENREQ   3
#define EVTSCTENDPCLOSEREQ  4
#define EVTSCTASSOCRSP      5
#define EVTSCTTERMREQ       6
#define EVTSCTASSOCREQ      7
#define EVTSCTDATREQ        8
#define EVTSCTHBEATREQ      9 
#define EVTSCTSETPRIREQ     10

/* TODO ENDS */

/***************************************************/
#define CZ_ACC_DFLT_RGN DFLT_REGION
#define CZ_ACC_DFLT_POOL DFLT_POOL
#define CZAC_SCTP_DM    1000
#define CZAC_DBGLEVEL_CZ 3
#define CZAC_MAX_CONN_IDX  10
/* Hash defines used by SCT Interface */
#define CZAC_DFLT_IPADDR  0x7F000001
#define DFL_PORT 7000
#define CZAC_DFLT_ENDPID 1
#define CZAC_SUID_DSCTP 1
#define CZAC_DFLT_SPID  1
#define CZAC_DFLT_SUID  1
#define CZAC_DFLT_SU_ENDPID 1
#define CZAC_DFLT_SP_ENDPID 1
#define CZAC_DFLT_OUT_STRMS 1
#define CZAC_DFLT_IN_STRMS 1
#define CZAC_DFLT_PEER_PORT 10000
#define CZAC_DFLT_LCL_PORT 1
#define CZAC_DFLT_NMB_IPS 1
#define CZAC_DFLT_SU_ASSOCID 1
#define CZT_CONNID_NOTUSED 1
#define CZAC_DFLT_SP_ASSOCID 1
#define CZAC_DFLT_ASSOCIDX 0
#define CZAC_LCZ_GLOBAL_STRM_ID 0
/*******PROCS ************/

#define CMXTA_DFLT_PROCID  100

#define CZAC_PROCID_SINGLE 100

#define CZAC_PROCID_ZERO   100
#define CZAC_PROCID_ONE    200
#define CZAC_PROCID_TWO    300
#define CZAC_PROCID_THREE  400

#define CZAC_PROC0   0
#define CZAC_PROC1   1
#define CZAC_PROC2   2
#define CZAC_PROC3   3
#define CZAC_START   1
#define CZAC_STOP    2

#ifdef SS_MULTIPLE_PROCS
#define SFndProcId() CMXTA_DFLT_PROCID
#endif /* SS_MULTIPLE_PROCS */

/********* ACC #defines ************/

#define CZAC_MAX_FLAGS 10
#define CZAC_MAX_USAP  10

#define CZAC_SB_DBG    3
#define CZAC_HI_DBG    3
#define CZAC_CZ_DBG    4


#define CZAC_ERRIND  1
#define CZAC_STAIND  2
#define CZAC_AUDIT   3
#define CZAC_FLCIND  4
#define CZAC_RLSCFM  6
#define CZAC_AUDCFM  7
/* Hash defines used by CZT Interface */

/* Hash defines used in czac_acc.x */
#define CZAC_CQ_SIZE    50

/* Hash defines used for the LSB interface */

/* CM_XTA ACC DEFINES */
#define MATCH_PROCID  TRUE

/* gen cfg */
#define CZAC_LCZ_MAX_CZTSAP   3
#define CZAC_LCZ_MAX_SCTSAP   3
#define CZAC_LCZ_MAX_CONN     5
#define CZAC_LCZ_MAX_PEER     5

#define CZAC_LCZ_TIMERES      10
#define CZAC_LCZ_HBFLAG       TRUE

/* sap cfg */
#define CZAC_LCZ_DFLT_SPID    0
#define CZAC_LCZ_KSCTP_SPID   1
#define CZAC_LCZ_DFLT_SUID    0

#define CZAC_TPT_SCTP    1
#define CZAC_TPT_KSCTP   2

/* Prot cfg */
/*- IPV6 Change -*/
#ifndef SB_IPV6_SUPPORTED /* SB_IPV6 supported */
#define CZAC_LCZ_IPADDR       "127.0.0.1"
#define CZAC_ENB_IPADDR       "127.0.0.1"
#else /* SB_IPV6 supported */
#define CZAC_LCZ_IPADDR       "::1"
#define CZAC_ENB_IPADDR       "::1"
#endif  /* SB_IPV6 supported */
#define CZAC_LCZ_SCTPORT      4000
#define CZAC_LCZ_ENB_PRC0     1
#define CZAC_LCZ_ENB1_PRC0     2
#define CZAC_LCZ_ENB2_PRC0     3
#define CZAC_LCZ_INV_NODE     10
#define CZAC_LCZ_ENB_SCTPORT  10000
#define CZAC_LCZ_RESETRETRY   10
#define CMXTA_CZ_RES_THR_UP         2
#define CMXTA_CZ_RES_THR_LOW        1
#define  CMXTA_CZ_500_MSECONDS     5
#define  CMXTA_CZ_4_SECONDS        40
#define CZAC_LCZ_ENC_ALGO 1
#define CZAC_LCZ_INTG_ALGO 2
/* Peer Cfg */
#define CZAC_LCZ_NUM_PEERS       1
#define CZAC_LCZ_INV_NUM_PEERS   (LCZ_MAX_NUM_OF_PEERS + 1)
#define CZAC_LCZ_INV_SAPID       (LCZ_MAX_SAP + 1)
#define CZAC_LCZ_OUT_STRMS       3

/* Peer cntrl */
#define CZAC_LCZ_PEERID       0

#define CZAC_LCZ_VAL_3        3
#define CZAC_LCZ_VAL_5        5
#define CZAC_LCZ_VAL_10       10 
#define CZAC_LCZ_VAL_50       50


/* TUCL DEFINES */
#define CMXTA_MAX_TSAP         10

#define CMXTA_TUCL_MAX_TSAP      CMXTA_MAX_TSAP

#ifdef HI_MULTI_THREADED
#define CMXTA_TUCL_MAX_CON            1024
#define CMXTA_TUCL_FDS                1024
#else
#define CMXTA_TUCL_MAX_CON            800
#define CMXTA_TUCL_FDS                64
#endif /* HI_MULTI_THREADED */

#define CMXTA_TUCL_FDBINS             4
#define CMXTA_TUCL_STP_THRESH         1
#define CMXTA_TUCL_DRP_THRESH         1
#define CMXTA_TUCL_STRT_THRESH        1
#define CMXTA_TUCL_NMB_HLBINS         16

#define CMXTA_TUCL_SELTIMEOUT         2
#define CMXTA_TUCL_UDP_MSGS_TOREAD    20
#define CMXTA_TUCL_NUMCL_TOACCEPT     5
/* defines for TUCL upper SAP configuration */
#define CMXTA_TUCL_CONG_STRT       15000
#define CMXTA_TUCL_CONG_DRP        20000
#define CMXTA_TUCL_CONG_STP        10000

/* DEFINES FOR CZAC_ACC.X */
/* defines for configuration */
#define CMXTA_TSTREG           DFLT_REGION    /* memory region id */
#define CMXTA_TSTPOOL          DFLT_POOL      /* memory pool id */
#define CMXTA_TSTINST_0        0              /* instance */
#define CMXTA_TSTINST_1        1              /* instance */
#define CMXTA_TSTINST_2        2              /* instance */
#define CMXTA_TSTINST_3        3              /* instance */

#define CZAC_MAX_SERVERS   5
#define CZAC_MAXBLKSIZE    2048
#define CZ_AC_DNS_IP       0xac1000f0
#define CMXTA_MAX_HDR_LEN  10000
#define CZ_AC_STK_MID      "<mid1.ccpu.com>"
#define CZ_AC_PEER_MID     "<mid2.ccpu.com>"
#define CZ_AC_MY_DOMAIN_NAME  "localhost.ccpu.com"
#define CZ_AC_INIT_RTT     100
#define CZ_AC_MY_MID       CZ_AC_STK_MID
#define CZ_AC_PRICZC_NAME  CZ_AC_MY_DOMAIN_NAME
#define CZ_AC_STKADDR_IP   0x7f000001
#define CZ_AC_LCLADDR_IP   0xAC190013
#define CZ_AC_DUMMY_IP     0x7f000002
#define CZ_AC_MY_STACK_IP  "127.0.0.1"
#define CZ_AC_ALADDR_IP    0x7f000001
#define CZ_AC_IUT_PORT     2827
#define CZ_AC_MAX_MTU_SIZE 1500
#define CZAC_MAX_DIAL_STR  60
#define CZAC_MAX_PROF_STR  100            

#define CZAC_ENB_PROC   100
#define CZAC_ENB1_PROC   100
#define CZAC_ENB2_PROC   200

/* Max procs allowed */
#define CZAC_MAX_PROCS  1000            

#define CZAC_GET_IPADDR(_tmpAddr, _selfAddr)                                \
{                                                                           \
   ProcId   _procId = CZAC_ENB_PROC;                                        \
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "procId",   \
                                                            &(_procId));    \
   if(_selfAddr == TRUE)                                                    \
   {                                                                        \
      _tmpAddr = (_procId == CZAC_ENB1_PROC)?                                \
         (czAccCb.directives.eNb1IpAddr): (czAccCb.directives.eNb2IpAddr);    \
   }                                                                        \
   else                                                                     \
   {                                                                        \
      _tmpAddr = (_procId == CZAC_ENB2_PROC)?                                \
         (czAccCb.directives.eNb2IpAddr): (czAccCb.directives.eNb1IpAddr);    \
   }                                                                        \
}                                                                           \

#define CZ_GET_PEERPROF_INDEX(_procId, _indx)                               \
{                                                                           \
   _indx = (_procId / 100) - 1;                                             \
}                                                                           \

#define CZ_MAX_ENODEB 5
#define IPADDR_2 "172.25.0.27"

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**********************************************************************

         End of file:     czac_acc.h@@/main/2 - Tue Aug 30 18:35:43 2011

**********************************************************************/

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
------------ -------- ---- ----------------------------------------------
/main/1      ---     sy        1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm 1. Fix CRs.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
