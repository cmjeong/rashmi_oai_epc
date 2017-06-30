
/********************************************************************20**

     Name:    eGTP product

     Type:    C Header file

     Desc:    Macros and hash defines related with test engine

     File:    egac_acc.h

     Sid:      egac_acc.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:53:10 2016

     Prg:     an 

*********************************************************************21*/


/*******PROC DEFINITIONS ************/

#define CMXTA_DFLT_PROCID  100
#define EGAC_PROCID_SINGLE 100

#define EGAC_PROCID_ZERO   100
#define EGAC_PROCID_ONE    200
#define EGAC_PROCID_TWO    300
#define EGAC_PROCID_THREE  400
/* eg004.201 New PROC ID added for eGTP-C PSF Upgrade*/
#define EGAC_PROCID_FOUR   500

#define EGAC_PROC0           0
#define EGAC_PROC1           1
#define EGAC_PROC2           2
#define EGAC_PROC3           3

#define SFndProcId() CMXTA_DFLT_PROCID

/*----------------------------------------------------------------------
             EGTP TA: Flags
-----------------------------------------------------------------------*/
#define CMXTA_DEBUGP             2
#define CMXTA_IPV6_SUPPORTED     3

/*-- This shall be equal one more than the last flag value --*/
/*-- eg002.201 : updated to number flags present--*/
/* eg001.102 Multithreaded performance changes */
/* eg004.201 Updated array size to support new flags introduced for eGTP-C PSF Upgrade*/
#define  EGAC_MAX_FLAGS     20 


#define  EGAC_DBG_MASK       4
/* #define  EGAC_DBG_MASK       0xFFFFFFFF */
/*-- eg003.201 : removed warnings due to dual macro definition--*/
#ifndef EG_REL_930
#define  MAX_APP_INTERFACES  7
#else
#define  MAX_APP_INTERFACES  9
#endif /* EG_REL_930 */


#define CMXTA_MAX_HDR_LEN    10000


#define MATCH_PROCID  TRUE

/*----------------------------------------------------------------------
            eGTP TA: TUCL Specific Defines
-----------------------------------------------------------------------*/
/* defines for configuration */
#define CMXTA_TSTREG           DFLT_REGION    /* memory region id */
#define CMXTA_TSTPOOL          DFLT_POOL      /* memory pool id */
#define CMXTA_TSTINST_0        0              /* instance */
#define CMXTA_TSTINST_1        1              /* instance */
#define CMXTA_TSTINST_2        2              /* instance */
#define CMXTA_TSTINST_3        3              /* instance */

#define CMXTA_TUCL_MAX_TSAP           CMXTA_MAX_TSAP

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

#define CMXTA_DBGLEVEL_HI           5
#define CMXTA_MAX_TSAP              10 
/* defines for UDP transport params */
#define CMXTA_TPTPARAM_QSIZE        1


/*********************************************************************
           GENERAL CONFIGURATION 
*********************************************************************/
#define       EGAC_LEG_DFLT_NODE_TYPE                  1  /* Default Node Type */
#define       EGAC_LEG_DFLT_NMB_INTFS                  2  /* Default number of interfaces */
#define       EGAC_LEG_DFLT_MAX_USAPS                  5  /* Default Max USAPS */
#define       EGAC_LEG_DFLT_MAX_TSAPS                  5  /* Default Max TSAPS */
/* eg007.201: Updated number of default servers to 5 */
#ifdef EG_MULTI_IP
#define       EGAC_LEG_DFLT_NMB_SRVS                   5  /* Default No of Servers */
#else
#define       EGAC_LEG_DFLT_NMB_SRVS                  15  /* Default No of Servers */
#endif
#define       EGAC_LEG_DFLT_MAX_TUNNELS               10  /* Maximum Tunnels   */
#define       EGAC_LEG_DFLT_TUN_ARRAY_SIZE             3  /* Max Tunnel Array Size */
#define       EGAC_LEG_DFLT_N3_REQUESTS                3  /* Max N3 Requests   */
/* Default Timer Resolution in MS */
#define       EGAC_LEG_DFLT_TMR_RES                    1000  

#define       EGAC_LEG_DFLT_LOWER_THRES                1  /* Default Lower mem threshold */
#define       EGAC_LEG_DFLT_UPPER_THRES                9  /* Default Upper mem threshold */
#define       EGAC_LEG_DFLT_ECHO_TMR_ENB            FALSE  /* echo timer flag */
#define       EGAC_LEG_DFLT_ECHO_TMR_VAL               60  /* echo timer flag */
#define       EGAC_LEG_DFLT_LMPST_DST_PID_CFG          0  /* U16   :  Dst ProcId in LM Pst         */
#define       EGAC_LEG_DFLT_LMPST_SRC_PID_CFG          0  /* U16   :  Src ProcId in LM Pst         */
#define       EGAC_LEG_DFLT_LMPST_DST_ENT_CFG        ENTSM/* U8    :  Dst EntityId in LM Pst       */    
#define       EGAC_LEG_DFLT_LMPST_SRC_ENT_CFG        ENTEG/* U8    :  Src EntityId in LM Pst       */
#define       EGAC_LEG_DFLT_LMPST_DST_INST_CFG        0   /* U8    :  Dst Instance Id in LM Pst    */ 
#define       EGAC_LEG_DFLT_LMPST_SRC_INST_CFG        0   /* U8    :  Sro Instance Id in LM Pst    */
#define       EGAC_LEG_DFLT_LMPST_PRIOR_CFG           0   /* U8    :  Priority in LM Pst           */
#define       EGAC_LEG_DFLT_LMPST_ROUTE_CFG           0   /* U8    :  Route in LM Pst              */
#define       EGAC_LEG_DFLT_LMPST_EVENT_CFG           0   /* U8    :  Event in LM Pst              */ 
#define       EGAC_LEG_DFLT_LMPST_REGION_CFG          0   /* U8    :  Region in LM Pst             */
#define       EGAC_LEG_DFLT_LMPST_POOL_CFG            0   /* U8    :  Pool in LM Pst               */
#define       EGAC_LEG_DFLT_LMPST_SEL_CFG             0   /* U8    :  Selector in LM Pst           */

#define       EGAC_LEG_DFLT_GTP_PROT_FLG          LEG_EGTP_U   /* Bool    : eGTP-C/eGTP-U protocol flag  */
#define       EGAC_LEG_DFLT_GTP_C_ON              LEG_EGTP_C /* Bool    : eGTP-C/eGTP-U protocol flag  */
#define       EGAC_LEG_DFLT_GTP_MTU_SIZE           1964   /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_TYPE        CM_TPTADDR_IPV4   /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_EGTPU_PORT              2152  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_T3_TMR_ENB             FALSE  /* BOOL    : T3 Timer enable/disable flag */
#define       EGAC_LEG_DFLT_T3_TMR_VAL                15  /* U8      : T3 Timer value               */
#define       EGAC_LEG_DFLT_NMB_TRIES                  3  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_REORD_TMR_ENB           TRUE  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_REORD_TMR_VAL             20  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_ECHO_REQ_PVTEXT           10  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_ECHO_RSP_PVTEXT           10  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_ERR_IND_PVTEXT            10  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_REORDER_WINSIZE           20  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_ADDR_TYPE    CM_TPTADDR_IPV4  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_EGTPU_PORT              2152  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_NMB_IP_ADDR                1  /* U16     : eGTP-U message unit size     */
#define       EGAC_IP_ADDR                            22  /* U16     : eGTP-U message unit size     */
#define       EGAC_EXT_HDR_TYPE_LST                   44  /* U16     : eGTP-U message unit size     */
#define       EGAC_LEG_DFLT_NMB_IP                     1  /* U8    :  No of IP's                   */
#define       EGAC_LEG_DFLT_NODE_ARCH                  1  /* U8    :  Node Architecture UMTS/LTE   */

#define       EGAC_LEG_DFLT_ECHO_SEQ_NUM_START         1000
#define       EGAC_LEG_DFLT_ECHO_SEQ_NUM_END           1100

/********************************************************************************************
                USAP CONFIGURATION
********************************************************************************************/
#define  EGAC_DFLT_SPID_UCFG               0                /* S16   :  Service Provider ID          */
#define  EGAC_DFLT_ECHO_UCFG               FALSE            /* U8    :  echo sap                     */
#define  EGAC_DFLT_INTF_TYPE_UCFG          EGT_GTP_INT_S11  /* U8    :  Interface Type               */
#define  EGAC_DFLT_SEL_UCFG                0                /* U8    :  Type of Coupling(selector)   */ 
#define  EGAC_DFLT_MEMID_REG_UCFG          0                /* U8    :  Memory Region                */ 
#define  EGAC_DFLT_MEMID_POOL_UCFG         0                /* U8    :  Memory Pool                  */
#define  EGAC_DFLT_PRIOR_UCFG              0                /* U8    :  Priority                     */
#define  EGAC_DFLT_ROUTE_UCFG              RTESPEC          /* U8    :  Route information            */
      

/********************************************************************************************
                LSAP CONFIGURATION
********************************************************************************************/
#define  EGAC_DFLT_SUID_LCFG                   0          /* S16   :  eGTP Sap Id              */
#define  EGAC_DFLT_SPID_LCFG                   0          /* S16   :  Service Provider Sap Id      */ 
#define  EGAC_DFLT_INTF_TYPE                   1          /* U16   :  Interface Type               */
#ifdef HI_MULTI_THREADED
#define  EGAC_DFLT_SEL_LCFG                    1          /* U8    :  Selector                     */
#else
#define  EGAC_DFLT_SEL_LCFG                    1          /* U8    :  Selector                     */
#endif

#define  EGAC_DFLT_MEMID_REG_LCFG              0          /* U8    :  Memory Region                */
#define  EGAC_DFLT_MEMID_POOL_LCFG             0          /* U8    :  Memory Pool                  */
#define  EGAC_DFLT_PRIOR_LCFG                  0          /* U8    :  Priority                     */
#define  EGAC_DFLT_ROUTE_LCFG                  RTESPEC    /* U8    :  Route information            */
#define  EGAC_DFLT_DST_PROC_ID_LCFG            0          /* U16   :  Dest Proc Id                 */
#define  EGAC_DFLT_DST_ENT_ID_LCFG             ENTEG      /* U8    :  Dest Entity Id               */
#define  EGAC_DFLT_DST_INST_ID_LCFG            0          /* U8    :  Dest Instance Id             */
#define  EGAC_DFLT_INIT_TMR_VAL_LCFG          10          /* U16   :  Init Timer Value             */

#define  EGAC_LEG_DFLT_SPID                    0

#define EGAC_LEG_DFLT_TRCMASK                  0xffff
#define EGAC_LEG_DFLT_TRCLEN                   0
/* TODO: Verify these values */
#define EGAC_DFLT_TPT_SRV_ID                   1

#define EGAC_DFLT_PORT                         2123

#define EGAC_DFLT_ADDR_TYPE                    CM_TPTADDR_IPV4
#define EGAC_DFLT_ADDR                         "172.25.0.27"
/* IPv6 Loop back Address */
#define EGAC_DFLT_ADDR_IPV6                     "::1"

#define EGAC_DFLT_TPT_PAR_TYPE                 CM_TPTPARAM_SOCK
#define EGAC_DFLT_SOC_NUM_OPTS                   0

#define EGAC_DFLT_SOC_LIS_QSIZE                   5
#define EGAC_DFLT_OPNSRV_RETRY_CNT             3
#define EGAC_DFLT_BND_RETRY_CNT                3
#define EGAC_DFLT_BND_TMRVAL                   300
#define EGAC_DFLT_OPNSRV_TMR_VAL               10
#define EGAC_DFLT_HOST_LEN                     15
#define EGAC_DFLT_HOST_NAME                    "host.domain.com"
#define EGAC_DFLT_TSRVPAR_TYPE                   LEG_TSRV_ID

#define EGAC_DFLT_STS_ACTION                   NOZEROSTS
#define EGAC_DFLT_STS_TYPE                     STEGGEN
#define EGAC_DFLT_STA_TYPE                     STEGGEN

#ifdef EGTP_U
#define EGUAC_DFLT_PDU_NMB              10
#define EGUAC_DFLT_SEQ_NMB              10
#define EGUAC_DFLT_UDP_PORT_NMB         1234
#define EGUAC_DFLT_PDCP_PORT_NMB        2345
#define EGUAC_DFLT_TEID                 100
#define EGUAC_DFLT_MSGTYPE              0
#define EGUAC_DFLT_ACTION               EGT_TMGMT_REQTYPE_ADD
#define EGUAC_DFLT_REORDER              FALSE
#define EGUAC_DFLT_ERRCAUSE             1
#define EGUAC_DFLT_DIAGINFO             0
#define EGUAC_DFLT_IETYPE               0
#define EGUAC_DFLT_INTFTYPE             0
#define EGUAC_DFLT_EXPSEQNMB            1000
#define EGUAC_DFLT_MAXTPDUSZ            500
#define EGUAC_DFLT_EXTTYPE_VAL          10
#define EGUAC_DFLT_ADDR                 "172.25.0.27"
/* IPv6 Loop back Address */
#define EGUAC_DFLT_ADDR_IPV6            "::1"
#define EGUAC_DFLT_LCL_PORT             10000
#define EGUAC_DFLT_RMT_PORT             2152

#define EGUAC_MAX_TXT_LEN               100 
#define EGUAC_DFLT_SPID_TCFG            0   
#define EGUAC_DFLT_SPID_TNLCFG          0   
#define EGUAC_DFLT_REORDALGO            EG_REORDER_TYPE_1

#ifdef EGTP_U_MULTI_THREADED
#define EGAC_LEG_DFLT_NMB_WORK_THRD     3
#define EGAC_LEG_DFLT_THR_REGID         0
#define EGAC_LEG_DFLT_THR_POOL          0
#define EGAC_LEG_DFLT_THR_ASSGN_TMR_ENB 1
#define EGAC_LEG_DFLT_THR_ASSGN_TMR_VAL 1
#endif /* EGTP_U_MULTI_THREADED */

#endif /* EGTP_U */
/********************************************************
*                    FOR DUMMY TESTING                  *
********************************************************/
#define EGAC_LEN_BYTES        0x03
#define EGAC_MAX_STR_LEN       255
#define EGAC_IMSI_IETYPE        1
#define EGAC_PCO_IETYPE         78
#define EGAC_MSG_LEN_BYTES    0x03
#define EGAC_MSG_VERSION      0x02
#define EGAC_ZERO             0x00
#define EGAC_IE_LEN_OFFSET    0x01
#define EGAC_LEN_ONE          0x01
#define EGAC_LEN_TWO          0x02
#define EGAC_LEN_THREE        0x03
#define EGAC_LEN_FOUR         0x04
#define EGAC_LEN_FIVE         0x05
#define EGAC_LEN_EIGHT        0x08
#define EGAC_LEN_TWELVE       0x0C
#define EGAC_LEN_SIXTEEN      0x10
#define EGAC_LEN_32           0x20
#define EGAC_LEN_64           0x40
#define EGAC_LEN_132          0xf0
#define EGAC_QOS_LEN          0x15
#define EGAC_MAX_BYTES        255 
#define EGAC_RECOV_IETYPE     3 
#define EGAC_PEXT_IETYPE      255 
#define EGAC_DELAY_IETYPE     94

/****************************************
*    DEFINES FOR IE CLASS               *
****************************************/
#define  EGAC_IE_MANDATORY                1
#define  EGAC_IE_OPTIONAL                 2
#define  EGAC_IE_CONDITIONAL              3

#define  EGAC_ERR_MEM_ALLOC_FAILED        20

/****************************************
*    DEFINES FOR MASK AND SHIFT         *
****************************************/
#define  EGAC_MASK_INST                   0x0F
#define  EGAC_MASK_CR                     0xE0
#define  EGAC_MASK_ECI                    0x0FFFFFFF
#define  EGAC_MASK_MSG_VER                0xE0

#define  EGAC_MASK_HIGH4                  0xF0
#define  EGAC_MASK_LOW3                   0x07
#define  EGAC_MASK_LOW4                   0x0F
#define  EGAC_MASK_LOW5                   0x1F

#define  EGAC_MASK_BIT1                   0x01
#define  EGAC_MASK_BIT2                   0x02
#define  EGAC_MASK_BIT3                   0x04
#define  EGAC_MASK_BIT4                   0x08
#define  EGAC_MASK_BIT5                   0x10
#define  EGAC_MASK_BIT6                   0x20
#define  EGAC_MASK_BIT7                   0x40 
#define  EGAC_MASK_BIT8                   0x80


#define  EGAC_SHIFT_5                     5
#define  EGAC_SHIFT_4                     4



#define EGAC_SUCCESS 100



/***************************************
*      EGT      DATA       TYPES       *
***************************************/
#define  EGAC_IE_F_TEID                   1
#define  EGAC_UNSIGNED_8                  2
#define  EGAC_UNSIGNED_16                 3
#define  EGAC_UNSIGNED_32                 4
#define  EGAC_EMB_CAUSE                   5
#define  EGAC_PVT_EXTN                    6
#define  EGAC_TRC_INFO                    7
#define  EGAC_ULI_DATA                    8
#define  EGAC_FQOS                        9
#define  EGAC_BQOS_IEDATA                 10
#define  EGAC_PAA_IEDATA                  11
#define  EGAC_GLOBAL_CNID                 12
#define  EGAC_STRING_8                    13
#define  EGAC_STRING_16                   14
#define  EGAC_STRING_32                   15
#define  EGAC_STRING_132                  16
#define  EGAC_STRING_MAX                  17
#define  EGAC_SNETWORK                    18
#define  EGAC_INDICATION                  19
#define  EGAC_BEARER_FLAG                 20
#define  EGAC_GROUPED                     21
#define  EGAC_IP_ADDR                     22
#define  EGAC_BID_LST                     23
#define  EGAC_S103_PDN_FW_INFO            24
#define  EGAC_S1U_DATA_FW                   25
#define  EGAC_PDUNUM                        26
#define  EGAC_GSM_KEY_TRIP                  27
#define  EGAC_UMTS_KEY_CIPH_QUIN            28
#define  EGAC_GSM_KEY_CIPH_QUIN             29
#define  EGAC_UMTS_KEY_QUIN                 30
#define  EGAC_EPS_SEC_QUAD_QUIN             31
#define  EGAC_UMTS_KEY_QUAD_QUIN            32
#define  EGAC_AUTH_QUIN                     33
#define  EGAC_AUTH_QUAD                     34
#define  EGAC_CMP_REQ                       35
#define  EGAC_GUTI                          36
#define  EGAC_F_CONT                        37
#define  EGAC_F_CAUSE                       38
#define  EGAC_TRGTID                        39
#define  EGAC_CELLID                        40
#define  EGAC_PKTFLOWID                     41
#define  EGAC_SRC_RNC_PDCP_CTX              42
#define  EGAC_PDN_CONN_SET_ID               43
#define  EGAC_EXT_HDR_TYPE_LST              44
#define  EGAC_MAX_DATATYPE                  45


/*********************************************************
*              DFLT VALUE FOR TH S11 MESSGAGES           *
*********************************************************/

#define EGAC_DFLT_LAC_VAL        100
#define EGAC_DFLT_CI_VAL         101
#define EGAC_DFLT_SAI_VAL        102
#define EGAC_DFLT_RAC_VAL        103
#define EGAC_DFLT_TAC_VAL        104
#define EGAC_DFLT_ECID_VAL       105
#define DFLT_MSISDN_VAL          "12345"
#define DFLT_MEI_VAL             "12346"
/* eg005.201: IE length update for EG_IMSI_IETYPE  --*/
#define DFLT_IMSI_VAL            "12345678"

#define DFLT_RAT_TYPE_VAL         1
#define DFLT_INTF_TYPE            2
#define DFLT_TEID_VAL            106
#define DFLT_EBI                 10 
#define DFLT_SEL_MODE_VAL         3
#define DFLT_PDNTYPE_VAL          1
#define DFLT_APN_RESTRICT_VAL     5 
#define DFLT_CHARG_CHAR_VAL       107 
#define DFLT_BEARERTFT_VAL       "123456"
#define DFLT_IP_ADDRESS            "127.0.0.1"
#define DFLT_ACCESS_POINT_NAME_VAL "accesspointname"
#define DFLT_QOS_UMBR_VAL        "12347"
#define DFLT_QOS_DMBR_VAL        "12348"
#define DFLT_QOSUGBR_VAL         "12349"
#define DFLT_QOSDGBR_VAL         "12350"
#define DFLT_ARP_VAL             108
#define DFLT_UNKNOWN_DATATYPE    15 
#define DFLT_UNKNOWN_VAL         "UNKNOWN" 
#define DFLT_BEARER_FLAG_VAL     1
#define DFLT_PTMSI_VAL           1
#define DFLT_PTMSI_SIG_VAL       1
#define DFLT_CRM_TYPE_VAL        1
#define DFLT_CRM                 "crm"
#define DFLT_IPADDR_TYPE_VAL     CM_TPTADDR_IPV4
#define DFLT_PORT                30245
#define DFLT_HOP_CNTR            1
#define DFLT_RAND_LEN            4
#define DFLT_RAND                "rand"
#define DFLT_XRES_LEN            4
#define DFLT_XRES                "xres"
#define DFLT_AUTN_LEN            4
#define DFLT_AUTN                "xres"
#define DFLT_KASME_LEN           4
#define DFLT_KASME               "xres"
#define DFLT_CK_LEN              2
#define DFLT_CK                  "ck"
#define DFLT_KC_LEN              2
#define DFLT_KC                  "kc"
#define DFLT_IK_LEN              2
#define DFLT_IK                  "ik"
#define DFLT_NMBTRIP             1
#define DFLT_NMBQUAD             1
#define DFLT_USED_CIPHER         1
#define DFLT_AUTH_TRIP_LEN       8
#define DFLT_USED_NAS_CIPHER     1
#define DFLT_USED_NAS_PROT_ALGO  1
#define DFLT_NAS_DLCOUNT         1
#define DFLT_NAS_ULCOUNT         1
#define DFLT_AUTH_TRIP           "authtrip"
#define DFLT_DRXPARAM_LEN        10
#define DFLT_DRXPARAM            "drxparamdr"

#define DFLT_MS_NTWRK_CAPB_LEN  10
#define DFLT_MS_NTWRK_CAPB_VAL "1234567890"
#define DFLT_UE_NTWRK_CAPB_LEN   15
#define DFLT_UE_NTWRK_CAPB       "123456789012345"
#define DFLT_MEID_LEN            16
#define DFLT_MEID                "1234567890123456"

#define DFLT_SECMODE             1
#define DFLT_CKSN                5
#define DFLT_NMBQUIN             1
#define DFLT_KSI                 1
#define DFLT_FCAUSE_TYPE         1
#define DFLT_FCAUSE_LENGTH       7
#define DFLT_FCAUSE              "f_cause"
#define DFLT_FCONTAINER_TYPE     1
#define DFLT_FCONTAINER_LENGTH   11
#define DFLT_FCONTAINER          "f_container"
#define DFLT_TARGET_ID_TYPE      1
#define DFLT_TARGET_ID_LENGTH    8
#define DFLT_TARGET_ID           "targetid"
#define DFLT_TARGET_CELL_ID_LENGTH 12
#define DFLT_TARGET_CELL_ID      "targetcellid"
#define DFLT_CELL_ID_SOURCE_TYPE 1
#define DFLT_CELL_ID_SOURCE_ID_LENGTH    14
#define DFLT_CELL_ID_SOURCE_ID   "cellidsourceid"
#define DFLT_SEL_PLMN_ID_LENGTH  8
#define DFLT_SEL_PLMN_ID         "selplmnid"
#define DFLT_BID_LST_NUM         3
#define DFLT_CNG_RPT_ACT         1

#define NMB_MAX_SEQ_NOS          63535
#define DFLT_PDN_TYPE            1
#define DFLT_PDN_PREFIX          1
#define DFLT__PDN_IPV4_ADDR      "1235"
#define DFLT__PDN_IPV6_ADDR      "1234567890123456"
#define DFLT_PVTEXT_PRY_VAL      "CCPU"
#define DFLT_PVTEXT_ENT_ID       109
#define DFLT_EBI_VAL             6
#define DFLT_PTID                110
#define DFLT_FLOW_QOS_QCI        7
#define DFLT_FLOW_QOS_UP_MBR_VAL "12351"
#define DFLT_FLOW_QOS_DN_MBR_VAL "12352"
#define DFLT_FLOW_QOS_UP_GBR_VAL  "12353"
#define DFLT_FLOW_QOS_DN_GBR_VAL  "12354"
#define DFLT_TAD_VAL              "123457"
#define DFLT_DELAY                8
#define DFLT_APN_RESTRICTION_VAL  9
#define DFLT_AMBR_VAL             "12355"
#define DFLT_UPLINK_APNAMBR       0xFFAAFFAA
#define DFLT_DWLINK_APNAMBR       0xFFAAFFAA
#define DFLT_PCO_VAL              "123458"
#define DFLT_RECOVERY_VAL         10
#define DFLT_TRC_REF_LEN          1
#define DFLT_TRC_ID_LEN           2
#define DFLT_TRG_ID_LEN           3
#define DFLT_OMC_ID_LEN           4
#define DFLT_TRC_REF_VAL          "1"
#define DFLT_TRC_ID_VAL           "12"
#define DFLT_TRG_ID_VAL           "123"
#define DFLT_OMC_ID_VAL           "1234"
#define DFLT_CSID_VAL             "123459"
#define DFLT_CAUSE_VAL            11
#define DFLT_BEARER_CMODE_VAL     12
#define DFLT_GRE_KEY_VAL         "123460"
#define DFLT_ID_ID                1
#define DFLT_EMBD_CAUSE_VAL       5
#define DFLT_EMBD_CAUSE_IE_TYPE   1
#define DFLT_EMBD_CAUSE_IE_CR     1
#define DFLT_EMBD_CAUSE_IE_INST   0
#define DFLT_EMBD_CAUSE_IE_LEN    8
#define DFLT_EMBD_CAUSE_VALUE     "12345678"
/* rakesh*/
#define DFLT_UPSUBSUEAMBR 0xFFFFFFFF 
#define DFLT_DNSUBSUEAMBR 0xFFFFFFFF
#define DFLT_UPUSEDUEAMBR 0xFFFFFFFF
#define DFLT_DNUSEDUEAMBR 0xFFFFFFFF 
#define DFLT_AUTH_TRIP_RAND_LEN 15
#define DFLT_AUTH_TRIP_RAND_VAL "123456789123456"
#define DFLT_AUTH_TRIP_SRES_LEN 3
#define DFLT_AUTH_TRIP_SRES_VAL "123"
#define DFLT_AUTH_TRIP_KC_LEN 7
#define DFLT_AUTH_TRIP_KC_VAL "1234567"
#define DFLT_NCCOLD 0xFF 
#define DFLT_KSIOLD 0xFF 
#define DFLT_NXT_HOP_OLD_LEN 7
#define DFLT_NXT_HOP_OLD "1234567" 
#define DFLT_VBEARER_FLAG_VAL 0xFF
#define DFLT_NODE_IDTYPE 0xFF
#define DFLT_CSID_NUM 0xFF
#define DFLT_NODE_ID_LEN 5
#define DFLT_NODE_ID "12345" 
#define DFLT_CAUSE 0xFFFF
#define DFLT_APN_VAL "1234567890"  
#define DFLT_FQDN_VAL "01234567890123456789"
#define DFLT_UENTWRKCAPB_VAL "12345"
#define DFLT_CHNLNEEDED 0xFFFF
#define DFLT_EMLPPPRIOR 0xFFFF
#define DFLT_TRANSID 0xFFFF
#define DFLT_PROCEDURETID 0xFF
#define DFLT_PROCEDURETID 0xFF
#define DFLT_NODETYPE     0
#define DFLT_CSGINFOREPACT  1
#define DFLT_SERVIND    1
#define DFLT_SOURCETYPE  1
#define DFLT_SOURCEID_VAL     "1234"
#define DFLT_TARGETCELLID_VAL "4321"
#define DFLT_PRIRTLVL 0
#define DFLT_QCI 1
#define DFLT_UPMBR_VAL "50"
#define DFLT_DNMBR_VAL "100" 
#define DFLT_UPGBR_VAL "25"
#define DFLT_DNGBR_VAL "75"
#define DFLT_GBLCNID_VAL "12345"
#define DFLT_DNLNKSEQNO 100
#define DFLT_UPLNKSEQNO 200
#define DFLT_SNPDUNO    111
#define DFLT_RNPDUNO    222
#define DFLT_PKTFLOWID  1
#define DFLT_NSAPI      1
#define DFLT_DNLEGUSEQNO 0xAAAA
#define DFLT_UPLEGUSEQNO 0xBBBB
#define DFLT_DNLPDCPSEQNO 0xCCCC
#define DFLT_UPLPDCPSEQNO 0xDDDD
#define DFLT_GREKEY 0xAAAA
#define DFLT_EBINUM 0x08
#define DFLT_TIMEZONE 02
#define DFLT_DAYLITESAVTIME 0
#define DFLT_TRCID 1
#define DFLT_CK_VAL "ck_val"
#define DFLT_IK_VAL "ck_val"
#define DFLT_SRCRNCPDCPCTX_VAL "SrcRncPdcpCtxPres"
#define DFLT_SGW_S1UTEID 0xAAAA
#define DFLT_RFSPID  1234
#define DFLT_CSGID 0xABCDEF
#define DFLT_MBMSDISTACK 1
#define DFLT_CMI 1
#define DFLT_MBMSFLOWID 0xABC
#define DFLT_MBMSSERVAREA 0xABCD
#define DFLT_MBMSSESSID 1
/* eg009.201 - Added for S2B and S2A */ 
#define DFLT_LDN_VAL              "9876543210"
#define DFLT_TRIG_EVT_LIST        "ABCDEFABC"
#define DFLT_INTF_LIST            "ABCDEFABCDEF"
#define DFLT_TRIG_EVT_LEN         9
#define DFLT_INTF_LEN             12
#define DFLT_APCO_VAL             "123458"

/* Max procs allowed */
#define EGAC_MAX_PROCS  1000      

/* Max no of transactions ID (Same as suConnId) */
#define EGAC_LEG_MAX_TRANSID     10

/* Address Type is Local  */
#define EGAC_ADDRTYPE_LCL     1

/*  Address Type is Remote */
#define EGAC_ADDRTYPE_RMT     2

/* Address Type is From Remote */
#define EGAC_ADDRTYPE_FRMRMT  3

#define EG_MAX_STRING_LEN    100




/* get hi byte from word */
#define GetHiByteSgnd(w)   (((S16)(w) >> 8) & 0xff)  
/* get lo byte from word */
#define GetLoByteSgnd(w)   ((S16)(w) & 0xff)   
/* get hi word of long */
#define GetHiWordSgnd(l)   (((S32)(l) >> 16) & 0xffffL)  
/* get lo word of long */
#define GetLoWordSgnd(l)   ((S32)(l) & 0xffffL)  

#if (defined (ALIGN_64BIT) || defined (WIN32))
/* get lo 32 bits */
#define GetLo32BitSgnd(l) ((S64)(l) & 0xffffffffL) 
/* get hi 32 bits */
#define GetHi32BitSgnd(l) (((S64)(l) >> 32) & 0xffffffffL) 
#endif


/********************************************************
 * Convert the U16 to network byte order and encode it  *
 *******************************************************/
#define EGAC_ENC_WORD(_param, _mBuf, _data) \
{ \
    _data[0] = (U8)(GetHiByte(_param)); \
    _data[1] = (U8)(GetLoByte(_param)); \
    SAddPstMsgMult(_data, EGAC_LEN_TWO, _mBuf); \
}

#define EGAC_ENC_LEN(_len, _mBuf, _idx) \
{ \
   U8 nwByte[EGAC_LEN_TWO]; \
   nwByte[0] = 0; nwByte[1] = 0;\
   nwByte[0] = (U8)(GetHiByte(_len)); \
   nwByte[1] = (U8)(GetLoByte(_len)); \
   SRepMsg(nwByte[0], _mBuf, _idx++); \
   SRepMsg(nwByte[1], _mBuf, _idx++); \
}  


/********************************************************
 * Convert the U24 to network byte order and encode it  *
 *******************************************************/

/* convert the U24 to Nw byte order and encode */
#define EGAC_ENC_U24(_param, _mBuf) \
{ \
   U16 nwWord[EGAC_LEN_TWO]; \
   U8 nwByte[EGAC_LEN_THREE]; \
   nwWord[0] = 0; nwWord[1] = 0; \
   nwByte[0] = 0; nwByte[1] = 0; nwByte[2] = 0; \
   nwWord[0] = (U16)(GetHiWord(_param)); \
   nwWord[1] = (U16)(GetLoWord(_param)); \
   nwByte[0] = GetLoByte(nwWord[0]); \
   nwByte[1] = GetHiByte(nwWord[1]); \
   nwByte[2] = GetLoByte(nwWord[1]); \
   SAddPstMsgMult(nwByte, EGAC_LEN_THREE, _mBuf); \
}

#define EGAC_DEC_U24(_param, _mBuf) \
{ \
  U16   nwWord[EGAC_LEN_TWO]; \
  U32   tmpU32; \
  Data  nwByte[EGAC_LEN_THREE];  \
  S16   tmpRetBS = 0; \
  tmpU32 = 0; \
  nwWord[0] = 0; nwWord[1] = 0; \
  nwByte[0] = 0; nwByte[1] = 0; nwByte[2] = 0; \
  tmpRetBS = SRemPreMsgMult(nwByte, EGAC_LEN_THREE, _mBuf); \
  nwWord[0] = ((U16)nwByte[0] & 0x00FF); \
  nwWord[1] = ((U16)nwByte[1] & 0x00FF); \
  nwWord[1] <<= EGAC_LEN_EIGHT; \
  nwWord[1] |= ((U16)nwByte[2] & 0x00FF); \
  tmpU32 = ((U32)nwWord[0] & 0x0000FFFF); \
  tmpU32 <<= EGAC_LEN_SIXTEEN; \
  tmpU32 |= ((U32)nwWord[1] & 0x0000FFFF); \
  _param = tmpU32; \
}

/* convert the U32 to Nw byte order and encode */
#define EGAC_ENC_U32(_param, _mBuf) \
{ \
  U16 nwWord = 0; \
  U8  data[EGAC_LEN_TWO]; \
  data[0] = 0; data[1] = 0; \
  nwWord = (U16)(GetHiWord(_param)); \
  EGAC_ENC_WORD(nwWord, _mBuf, data); \
  nwWord = (U16)(GetLoWord(_param)); \
  EGAC_ENC_WORD(nwWord, _mBuf, data); \
}


/* convert the U16 to Nw byte order and encode */
#define EGAC_ENC_U16(_param, _mBuf) \
{ \
   U8 nwByte[EGAC_LEN_TWO]; \
   nwByte[0] = 0; nwByte[1] = 0; \
   nwByte[0] = GetHiByte(_param); \
   nwByte[1] = GetLoByte(_param); \
   SAddPstMsgMult(nwByte, EGAC_LEN_TWO, _mBuf); \
}

#define EGAC_ENC_U8(_param, _mBuf) \
{ \
   SAddPstMsg(&_param, _mBuf); \
}

/* Decodes the string data types of length 4,8,16,32,132,EGAC_MAX_STR bytes of length data */ 
#define EGAC_DEC_STR(_mBuf, _val, _length, _strType, _retVal) \
{ \
   if( _length <= _strType) \
   { \
      SRemPreMsgMult(_val, _length, _mBuf); \
      _retVal = ROK; \
   } \
   else \
   { \
      _retVal = EGT_ERR_INV_IE_VAL; \
   } \
} \

/* encodes the string data types of length 4,8,16,32,132,EGAC_MAX_STR bytes of length data */ 
#define EGAC_ENC_STR(_mBuf, _val, _length, _strType, _retVal) \
{ \
   SAddPstMsgMult(_val, _length, _mBuf); \
   _retVal = ROK; \
} \

#define  EGAC_ENC_NETID(_sNwk, _mBuf) \
{ \
   U8 tmpByte1[EGAC_LEN_THREE]; \
   tmpByte1[0] = ((_sNwk.mccDigit1) << EGAC_SHIFT_4) | ((_sNwk.mccDigit2) & 0x0f); \
   tmpByte1[1] = ((_sNwk.mccDigit3) << EGAC_SHIFT_4) | ((_sNwk.mncDigit1) & 0x0f); \
   tmpByte1[2] = ((_sNwk.mncDigit2) << EGAC_SHIFT_4) | ((_sNwk.mncDigit3) & 0x0f); \
   SAddPstMsgMult(tmpByte1, EGAC_LEN_THREE, _mBuf); \
} \

#define  EGAC_DEC_NETID(_sNwk, _mBuf) \
{ \
   U8 tmpByte1[EGAC_LEN_THREE]; \
   SRemPreMsgMult(tmpByte1, EGAC_LEN_THREE, _mBuf); \
   _sNwk.mccDigit1 = tmpByte1[0] >> EGAC_SHIFT_4;  \
   _sNwk.mccDigit2 = tmpByte1[0] & 0x0f; \
   _sNwk.mccDigit3 = tmpByte1[1] >> EGAC_SHIFT_4;  \
   _sNwk.mncDigit1 = tmpByte1[1] & 0x0f; \
   _sNwk.mncDigit2 = tmpByte1[2] >> EGAC_SHIFT_4; \
   _sNwk.mncDigit3 = tmpByte1[2] & 0x0f; \
} \

#define EGAC_DEC_U16(_param, _mBuf) \
{ \
   U8   nwByte[EGAC_LEN_TWO]; \
   U16   tmpU16 = 0; \
   nwByte[0] = 0; nwByte[1] = 0; \
   SRemPreMsg(&nwByte[0], _mBuf); \
   SRemPreMsg(&nwByte[1], _mBuf); \
   tmpU16 = PutHiByte(tmpU16, nwByte[0]); \
   tmpU16 = PutLoByte(tmpU16, nwByte[1]); \
   _param = tmpU16; \
}



/************************************************************
 * Macros for decoding information element                  *
 ***********************************************************/
/* decode U16 and return it in _param */
#define EGAC_DEC_WORD(_param, _mBuf) \
{ \
   U16   decWord = 0; \
   U8    nwByte[EGAC_LEN_TWO];  \
   S16   tmpRetBS = 0; \
   nwByte[0] = 0; nwByte[1] = 0; \
   tmpRetBS = SRemPreMsgMult(nwByte, EGAC_LEN_TWO, _mBuf); \
   decWord = PutHiByte(decWord, nwByte[0]); \
   decWord = PutLoByte(decWord, nwByte[1]); \
   _param = decWord; \
}

/* decode U32 and return it in _param */
#define EGAC_DEC_U32(_param, _mBuf) \
{ \
   U16   nwWord[EGAC_LEN_TWO]; \
   U32   tmpU32 = 0; \
   nwWord[0] = 0; nwWord[1] = 0; \
   EGAC_DEC_WORD(nwWord[0], _mBuf); \
   EGAC_DEC_WORD(nwWord[1], _mBuf); \
   tmpU32 = PutHiWord(tmpU32, nwWord[0]); \
   tmpU32 = PutLoWord(tmpU32, nwWord[1]); \
   _param = tmpU32; \
}
/********************************************************
 * Decodes the FQOS IE DATA Part                        *
 *******************************************************/
#define EGAC_DEC_FQOS(_param, _mBuf) \
{ \
  SRemPreMsg(&_param->qci, _mBuf); \
  SRemPreMsgMult(_param->upMBR.val, EGAC_LEN_FIVE, _mBuf); \
  SRemPreMsgMult(_param->dnMBR.val, EGAC_LEN_FIVE, _mBuf); \
  SRemPreMsgMult(_param->upGBR.val, EGAC_LEN_FIVE, _mBuf); \
  SRemPreMsgMult(_param->dnGBR.val, EGAC_LEN_FIVE, _mBuf); \
}


/********************************************************
 * encodes the FQOS IE DATA Part                        *
 *******************************************************/
#define EGAC_ENC_FQOS(_param, _mBuf) \
{ \
  SAddPstMsg((U8)_param.qci, _mBuf); \
  SAddPstMsgMult((U8*)_param.upMBR.val, EGAC_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.dnMBR.val, EGAC_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.upGBR.val, EGAC_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.dnGBR.val, EGAC_LEN_FIVE, _mBuf); \
}


/********************************************************
 * encodes the BQOS IE DATA Part                        *
 *******************************************************/
#define EGAC_ENC_BQOS(_param, _mBuf) \
{ \
  U8 Dummy = (((U8)_param.isPVIPres & EGAC_MASK_BIT1) | ((U8)_param.isPVIPres & 0x3c) | ((U8)_param.isPCIPres & 0x40)); \
  SAddPstMsg((U8)Dummy, _mBuf); \
  SAddPstMsg((U8)_param.qci, _mBuf); \
  SAddPstMsgMult((U8*)_param.upMBR.val, EGAC_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.dnMBR.val, EGAC_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.upGBR.val, EGAC_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.dnGBR.val, EGAC_LEN_FIVE, _mBuf); \
}

/********************************************************
 * Decodes the BQOS IE DATA Part                        *
 *******************************************************/
#define EGAC_DEC_bQOS(_param, _mBuf) \
{ \
  U8 Dummy;\
  SRemPreMsg(&Dummy, _mBuf); \
  _param->isPVIPres = Dummy & 0X01; \
  _param->prityLvl  = Dummy & 0X3C; \
  _param->isPCIPres = Dummy & 0X40; \
  SRemPreMsg(&_param->qci, _mBuf); \
  SRemPreMsgMult(_param->upMBR.val, EGAC_LEN_FIVE, _mBuf); \
  SRemPreMsgMult(_param->dnMBR.val, EGAC_LEN_FIVE, _mBuf); \
  SRemPreMsgMult(_param->upGBR.val, EGAC_LEN_FIVE, _mBuf); \
  SRemPreMsgMult(_param->dnGBR.val, EGAC_LEN_FIVE, _mBuf); \
}
#define EGAC_XML_GET_VALLIST_TXT(_parseStr, _strName, _strTok, _dstArray, _ret,_cnt)       \
{                                                                                   \
    Txt   *_token   =  NULLP;                                                        \
    U8    _i        =  0;            \ 
    _cnt = 0;                                               \
           CMXTA_ZERO(_parseStr, sizeof(_parseStr));                                        \
           _ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, _strName, _parseStr);    \
           _token =  strtok(_parseStr, _strTok);                                            \
           for(_i=0;_token != NULLP;(_token =  strtok(NULLP, _strTok)), _i++)               \
           {\
               strcpy(_dstArray[_i],_token); \
                   _cnt++;\
           }                          \
}


/**********************************************************************

         End of file:     egac_acc.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:53:10 2016

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rkumar         1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced. 
						  rss					  2. Multithreaded performance changes .
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3      eg003.201 psingh     1. Updated the value of EGAC_MAX_FLAGS     
                                  2. Updated compile issue for macro definition
/main/3      eg004.201 magnihotri 1. New PROC ID added for eGTP-C PSF Upgrade 
                                  2. Updated array size to support new flags introduced 
                                     for eGTP-C PSF Upgrade
/main/3      eg005.201 psingh     1. IE length update for EG_IMSI_IETYPE 
/main/3      eg007.201 psingh     1. Updated EGAC_LEG_DFLT_NMB_SRVS to 5
             eg009.201 asaurabh   1. DFLT values added for S2B and S2A.
*********************************************************************91*/
