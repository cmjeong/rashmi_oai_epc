
/********************************************************************20**

     Name:    S1AP 

     Type:    C Header file

     Desc:    Macros and hash defines related with test engine

     File:    szac_acc.h

     Sid:      szac_acc.h@@/main/4 - Mon Jan 10 22:15:35 2011

     Prg:     ms 

*********************************************************************21*/


/* to be deleted once updated inother files */
/*  Only for compilation pourposes */

/***************************************************/
#define STSZUSAP  1
#define STSZLSAP  2

#define SZ_FREE_EVNT_MEM(a)

#define LSZ_PEER_STATE_ACTIVE 1
#define LSZ_USTA_DGNVAL_PEERID 3
#define LSZ_MAX_NO_OF_PEERS   10

#define LSZ_MAX_MME_GROUP  10

/* Hash defines used by SZT Interface */
#define SZT_CAUSE_INV_UNKNOWN 33
#define SZT_CON_ST_CONNECTED  38

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

/* ENDS */

/***************************************************/
#define SZ_ACC_DFLT_RGN DFLT_REGION
#define SZ_ACC_DFLT_POOL DFLT_POOL
#define SZAC_SCTP_DM    152

#define SZAC_MAX_CONN_IDX  10
/* Hash defines used by SCT Interface */
#define SZAC_DFLT_IPADDR  0x7F000001
#define DFL_PORT 7000
#define SZAC_DFLT_ENDPID 1
#define SZAC_SUID_DSCTP 1
#define SZAC_DFLT_SPID  1
#define SZAC_DFLT_SUID  1
#define SZAC_DFLT_SU_ENDPID 1
#define SZAC_DFLT_SP_ENDPID 1
/* sz005.301: */
#define SZAC_DFLT_OUT_STRMS 5
#define SZAC_DFLT_IN_STRMS 5
#define SZAC_DFLT_PEER_PORT 1
#define SZAC_DFLT_LCL_PORT 1
#define SZAC_DFLT_NMB_IPS 1
#define SZAC_DFLT_SU_ASSOCID 1
#define SZT_CONNID_NOTUSED 1
#define SZAC_DFLT_SP_ASSOCID 1
#define SZAC_DFLT_ASSOCIDX 0

/*******PROCS ************/

#define CMXTA_DFLT_PROCID  100

#define SZAC_PROCID_SINGLE 100

#define SZAC_PROCID_ZERO   100
#define SZAC_PROCID_ONE    200
#define SZAC_PROCID_TWO    300
#define SZAC_PROCID_THREE  400

#define SZAC_PROC0   0
#define SZAC_PROC1   1
#define SZAC_PROC2   2
#define SZAC_PROC3   3

#ifdef SS_MULTIPLE_PROCS
#define SFndProcId() CMXTA_DFLT_PROCID
#endif /* SS_MULTIPLE_PROCS */

/********* ACC #defines ************/

/* sz004.301: Updted for TC Enc/Dec */
/* sz005.301: Updted for S1 abort request */
/* sz008.301: support for Source RNC to Target RNC */
#define SZAC_MAX_FLAGS 18
#define SZAC_MAX_USAP  10

#define SZAC_SB_DBG    3
#define SZAC_HI_DBG    3
#define SZAC_SZ_DBG    4


#define SZAC_ERRIND  33
#define SZAC_STAIND  34
#define SZAC_AUDIT   35
#define SZAC_FLCIND  36
/* Hash defines used by SZT Interface */

/* Hash defines used in szac_acc.x */
#define SZAC_CQ_SIZE    50

/* Hash defines used for the LSB interface */

/* CM_XTA ACC DEFINES */
#define MATCH_PROCID  TRUE

/* gen cfg */
#define SZAC_LSZ_MAX_SZTSAP   10
#define SZAC_LSZ_MAX_SCTSAP   10
#define SZAC_LSZ_MAX_CONN     10
#define SZAC_LSZ_MAX_PEER     10

#define SZAC_LSZ_TIMERES      10
#define SZAC_LSZ_HBFLAG       TRUE

/* sap cfg */
#define SZAC_LSZ_DFLT_SPID    0
#define SZAC_LSZ_DFLT_SUID    0


/* Prot cfg */
#define SZAC_LSZ_IPADDR       "127.0.0.1"
#define SZAC_ENB_IPADDR       "127.0.0.1"
#define SZAC_MME_IPADDR       "127.0.0.1"
#define SZAC_LSZ_SCTPORT      4000
#define SZAC_LSZ_ENB_PRC0     1
#define SZAC_LSZ_MME_PRC1     2
#define SZAC_LSZ_GW_PRC2      3
#define SZAC_LSZ_INV_NODE     10
#define SZAC_LSZ_ENB_SCTPORT  10000
#define SZAC_LSZ_MME_SCTPORT  10001

/* Added new defines for GW ports */
#define SZAC_LSZ_GW_SCTPORT1  10000
#define SZAC_LSZ_GW_SCTPORT2  10001

#define SZAC_LSZ_RESETRETRY   10

/* Peer Cfg */
#define SZAC_LSZ_NUM_PEERS       1
#define SZAC_LSZ_INV_NUM_PEERS   (LSZ_MAX_NUM_OF_PEERS + 1)
#define SZAC_LSZ_INV_SAPID       (LSZ_MAX_SAP + 1)
#define SZAC_LSZ_OUT_STRMS       3

/* Peer cntrl */
#define SZAC_LSZ_PEERID       0

#define SZAC_LSZ_VAL_3        3
#define SZAC_LSZ_VAL_5        5
#define SZAC_LSZ_VAL_10       10 
#define SZAC_LSZ_VAL_50       50


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

/* DEFINES FOR SZAC_ACC.X */
/* defines for configuration */
#define CMXTA_TSTREG           DFLT_REGION    /* memory region id */
#define CMXTA_TSTPOOL          DFLT_POOL      /* memory pool id */
#define CMXTA_TSTINST_0        0              /* instance */
#define CMXTA_TSTINST_1        1              /* instance */
#define CMXTA_TSTINST_2        2              /* instance */
#define CMXTA_TSTINST_3        3              /* instance */

#define SZAC_MAX_SERVERS   5
#define SZAC_MAXBLKSIZE    2048
#define SZ_AC_DNS_IP       0xac1000f0
#define CMXTA_MAX_HDR_LEN  10000
#define SZ_AC_STK_MID      "<mid1.ccpu.com>"
#define SZ_AC_PEER_MID     "<mid2.ccpu.com>"
#define SZ_AC_MY_DOMAIN_NAME  "localhost.ccpu.com"
#define SZ_AC_INIT_RTT     100
#define SZ_AC_MY_MID       SZ_AC_STK_MID
#define SZ_AC_PRISZC_NAME  SZ_AC_MY_DOMAIN_NAME
#define SZ_AC_STKADDR_IP   0x7f000001
#define SZ_AC_LCLADDR_IP   0xAC190013
#define SZ_AC_DUMMY_IP     0x7f000002
#define SZ_AC_MY_STACK_IP  "127.0.0.1"
#define SZ_AC_ALADDR_IP    0x7f000001
#define SZ_AC_IUT_PORT     2827
#define SZ_AC_MAX_MTU_SIZE 1500
#define SZAC_MAX_DIAL_STR  60
#define SZAC_MAX_PROF_STR  100            

#define SZAC_ENB_PROC   100
#define SZAC_MME_PROC   200
#define SZAC_GW_PROC    300
/* sz003.301: Updted for PSF-S1AP 3.1 release */
#define SZAC_SBY_PROC   400
#define SZAC_ENB_PROC1 SZAC_SBY_PROC
#define SZAC_MME_PROC1 SZAC_SBY_PROC

/* Max procs allowed */
#define SZAC_MAX_PROCS  1000            

/* Defines of Additional IE Ids for criticality test cases. This need to be
 * changed when DB is getting updated */
#define Sztid_Crit_Tst1    200
#define Sztid_Crit_Tst_ID  201
#define Sztid_Crit_Tst2    202
#define Sztid_Crit_Tst3    203
#define Sztid_Crit_Tst4    204


#define SZAC_GET_IPADDR(_tmpAddr, _selfAddr)                                \
{                                                                           \
   ProcId   _procId = SZAC_ENB_PROC;                                        \
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "procId",   \
                                                            &(_procId));    \
   if(_selfAddr == TRUE)                                                    \
   {                                                                        \
      _tmpAddr = (_procId == SZAC_ENB_PROC)?                                \
         (szAccCb.directives.eNbIpAddr): (szAccCb.directives.mmeIpAddr);    \
   }                                                                        \
   else                                                                     \
   {                                                                        \
      _tmpAddr = (_procId == SZAC_ENB_PROC)?                                \
         (szAccCb.directives.mmeIpAddr): (szAccCb.directives.eNbIpAddr);    \
   }                                                                        \
}                                                                           \


/**********************************************************************

         End of file:     szac_acc.h@@/main/4 - Mon Jan 10 22:15:35 2011

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
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz004.301   va    1. Updated for Transparent Container Enc/Dec 
/main/4   sz005.301   va    1. Updated for S1 Abort request 
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
