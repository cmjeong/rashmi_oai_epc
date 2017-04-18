

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     

     Desc:     
               

     File:    nlac_acc.h 

     Sid:      nlac_acc.h@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:02:42 2014

     Prg:     subhamay 

*********************************************************************21*/

/********************************************************************20**

     Name:     

     Type:     

     Desc:     
               

     File:     nlac_acc.h 

     Sid:      nlac_acc.h@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:02:42 2014

     Prg:      

*********************************************************************21*/

#ifndef __NLAC_ACC_H__
#define __NLAC_ACC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SON_DFLT_ADDR     "54.235.222.154"
#define NLAC_NUM_TQENTRY  5
#define NLAC_TMR_RES                      1
#define NLAC_CALC_WAIT_TIME(_delay) (_delay/((20/10/*SS_TICKS_SEC*/) * NLAC_TMR_RES))
#define NLAC_TMR_SON_SERVER_INIT_TMR     1
#define NLAC_TMR_SON_SERVER_INIT_TMR_VAL 1

#define NLAC_TMR_NLU_BIND_TMR            2
#define NLAC_TMR_NLU_BIND_TMR_VAL        1

#define WRAC_MEM_PDU_SIZE    3584
#define WRAC_MAX_SDU_SIZE    8188
#define WRAC_MAX_CONNS       32
#define WRAC_FULL_RESET      0
#define WRAC_PARTIAL_RESET   1
#define CMXTA_DFLT_PROCID    100
#define WRAC_MAX_FLAGS       10
#define WR_NL_SPID           0
#define WR_NL_SUID           0 
#define SM_NL_PROC           0   /*100*/

#define WRAC_PJU_MAX_FLAT_BUF_SIZE    5000

#define WRAC_RGR_USERENT    ENTNX 
#define WRAC_RGR_PROVENT    ENTRG
#define WRAC_RGR_USERINST   CMXTA_INST_ID
#define WRAC_RGR_PROVINST   CMXTA_INST_ID
#define WRAC_RGR_SRCPROC    CMXTA_PROC_ID 
#define WRAC_RGR_DSTPROC    CMXTA_PROC_ID
#define WRAC_RGR_MATCHPROC  FALSE


#define WRAC_RGR_EVTBNDCFM   EVTRGRBNDCFM
#define WRAC_RGR_EVTBNDREQ   EVTRGRBNDREQ
#define WRAC_RGR_EVTUBNDREQ  EVTRGRBNDREQ
#define WRAC_RGR_EVTCFGREQ   EVTRGRCFGREQ
#define WRAC_RGR_EVTCFGCFM   EVTRGRCFGCFM
#define WRAC_RGR_EVTTTIIND   EVTRGRTTIIND

#ifdef RGR_CQI_REPT
#define WRAC_RGR_EVTSTAIND   EVTRGRSTAIND
#endif
#define WRAC_RGR_DEFAULT_TRANSID 1
#define WRAC_RGR_CONFIG   RGR_CONFIG 
#define WRAC_RGR_RECONFIG RGR_RECONFIG
#define WRAC_RGR_DELETE   RGR_DELETE
#define WRAC_RGR_RESET    RGR_RESET

#ifdef RGR_SI_SCH
#define WRAC_RGR_EVTSICFGREQ   EVTRGRSICFGREQ
#define WRAC_RGR_EVTSICFGCFM   EVTRGRSICFGCFM
#endif

#define Sztid_Crit_Tst1    200
#define Sztid_Crit_Tst_ID  201
#define Sztid_Crit_Tst2    202
#define Sztid_Crit_Tst3    203
#define Sztid_Crit_Tst4    204

#define WRAC_GP         0
#define WRAC_BMP        1
#define WRAC_ERR        2

#define WRAC_ADDRTYPE_LCL    1
#define WRAC_ADDRTYPE_RMT    2
#define WRAC_ADDRTYPE_FRMRMT 3

#define WRAC_DFLT_PDU_NMB              10
#define WRAC_DFLT_SEQ_NMB              10
#define WRAC_DFLT_UDP_PORT_NMB         1234
#define WRAC_DFLT_PDCP_PORT_NMB        2345
#define WRAC_DFLT_TEID                 100
#define WRAC_DFLT_MSGTYPE              0
#define WRAC_DFLT_ACTION               EGT_TMGMT_REQTYPE_ADD
#define WRAC_DFLT_REORDER              FALSE
#define WRAC_DFLT_ERRCAUSE             1
#define WRAC_DFLT_DIAGINFO             0
#define WRAC_DFLT_IETYPE               0
#define WRAC_DFLT_INTFTYPE             0
#define WRAC_DFLT_EXPSEQNMB            1000
#define WRAC_DFLT_MAXTPDUSZ            500
#define WRAC_DFLT_EXTTYPE_VAL          10
#define WRAC_DFLT_LCL_PORT             10000
#define WRAC_DFLT_RMT_PORT             2152
#define WRAC_MAX_TXT_LEN               100 
#define WRAC_DFLT_SPID_TCFG            0   
#define WRAC_DFLT_SPID_TNLCFG          0   
#define WRAC_DFLT_REORDALGO            1

/* EGTPU */
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
#define WRAC_LEN_BYTES        0x03
#define WRAC_MAX_STR_LEN       255
#define WRAC_IMSI_IETYPE        1
#define WRAC_PCO_IETYPE         78
#define WRAC_MSG_LEN_BYTES    0x03
#define WRAC_MSG_VERSION      0x02
#define WRAC_ZERO             0x00
#define WRAC_IE_LEN_OFFSET    0x01
#define WRAC_LEN_ONE          0x01
#define WRAC_LEN_TWO          0x02
#define WRAC_LEN_THREE        0x03
#define WRAC_LEN_FOUR         0x04
#define WRAC_LEN_FIVE         0x05
#define WRAC_LEN_EIGHT        0x08
#define WRAC_LEN_TWELVE       0x0C
#define WRAC_LEN_SIXTEEN      0x10
#define WRAC_LEN_32           0x20
#define WRAC_LEN_64           0x40
#define WRAC_LEN_132          0xf0
#define WRAC_QOS_LEN          0x15
#define WRAC_MAX_BYTES        255 
#define WRAC_RECOV_IETYPE     3 
#define WRAC_PEXT_IETYPE      255 
#define WRAC_DELAY_IETYPE     94
#define WRAC_DFLT_ADDR        "127.0.0.1"


#define WRAC_FILL_U8_U32_TKN(_ie, _pres, _val) {\
   _ie.pres = _pres;\
   _ie.val = _val;\
}

#define FILL_UINT_TKN(_ie, _val) {\
   _ie.pres = PRSNT_NODEF;\
   _ie.val = _val;\
}

#define FILL_BIT_STR(_ptr, _len, _val, _pdu) {\
   U8      i;                                    \
   U16     _tmpLen;                             \
   _ptr.pres = PRSNT_NODEF;                     \
   _ptr.len =  _len;                            \
\
   _tmpLen = _len;                              \
   if((_len%8) > 0)                              \
   {                                             \
      _tmpLen = (_len/8)+1;                         \
   }                                             \
   else                                          \
   {                                             \
      _tmpLen = _len/8;                             \
   }                                             \
   CMXTA_GET_MEM(_pdu, _tmpLen * sizeof(U8), (Ptr *)&(_ptr.val));  \
                   \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = 0; i < _tmpLen; i++)                  \
      {                                          \
         _ptr.val[i] = _val;                  \
      }                                          \
   }                                             \
}

#define FILL_OCT_STR(_ptr, _len, _val, _pdu) {\
   U8      i;                                    \
   _ptr.pres = PRSNT_NODEF;                      \
   _ptr.len =  _len;                             \
                   \
   CMXTA_GET_MEM(_pdu, _len * sizeof(U8), (Ptr *)&(_ptr.val));  \
                   \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = 0; i < _len; i++)                  \
      {                                          \
         _ptr.val[i] = _val;                  \
      }                                          \
   }                                             \
}


#define WRAC_FREE_SDU(_sdu) \
{\
   if (_sdu != NULLP) \
   {\
      cmFreeMem ((Ptr)(_sdu));\
      _sdu = NULLP;\
   }\
}

#define WRAC_FORM_SDU(_sdu, _size, _sData, _mBuf)                    \
{                                                                    \
   U16   _idx;                                                       \
   if (_size)                                                        \
   {                                                                 \
      for (_idx = 0; _idx < _size; _idx++)                           \
      {                                                              \
         _sdu[_idx] = (U8)(_idx % 255);                              \
      }                                                              \
                                                                     \
      /* put flat buffer into mBuf */                                \
      if (SAddPreMsgMult((Data *)_sdu, _size , *_mBuf) != ROK)       \
      {                                                              \
         CMXTA_DBG_ERR((_cmxtap, "FORM_SDU Failed: resource unavailble \n"));\
         RETVALUE(CMXTA_ERR_RSRC);                                   \
      }                                                              \
   }                                                                 \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

