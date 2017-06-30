#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    cm_xta_py.py
#
#     Sid:      cm_xta_py.py@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 19:25:43 2013
#
#     Prg:      
#
#*********************************************************************21*/
#!/usr/bin/env python


import re
import sys
import glob
import xml.dom.minidom
import cm_xta_pycmd
import cm_xta_pyattr

from cm_xta_cmdmap import *

try :
   import cm_xta_tclist
   newTcList = xx_tclist.testCase
   newTgList = xx_tclist.testGroup
except ImportError :
   newTcList = None
   newTgList = None

reList = {}

LSO_PRX_STATELESS          = 1
LSO_PRX_CALL_STATEFUL      = 2
LSO_PRX_TRANS_STATEFUL     = 3

dbgMask = False;
updTCForAPI = True
proxyType   =  LSO_PRX_CALL_STATEFUL

UA1 =  0
UA2 =  1
UA3 =  2
UA4 =  3
UA5 =  4

SLP1 =  5
SLP2 =  6
SLP3 =  7
SLP4 =  8
SLP5 =  9

CSP1 =  10
CSP2 =  11
CSP3 =  12
CSP4 =  13
CSP5 =  14

TSP1 =  15
TSP2 =  16
TSP3 =  17
TSP4 =  18
TSP5 =  19

PRX1 =  20
PRX2 =  21
PRX3 =  22
PRX4 =  23
PRX5 =  24

SFP1 =  25
SFP2 =  26
SFP3 =  27
SFP4 =  28
SFP5 =  29

DUA1 =  30
DUA2 =  31
DUA3 =  32
DUA4 =  33
DUA5 =  34

SPECTRA =  35
SPECTRA2 =  36
SPECTRA3 =  37

SIPENT1    =  40
SIPENT2    =  41
SIPENT3    =  42

SU1  =  0
SU2  =  1
SU3  =  2
SU4  =  3
SU5  =  4

entityDef = {
   'UA1' :  UA1,
   'UA2' :  UA2,
   'UA3' :  UA3,
   'UA4' :  UA4,
   'UA5' :  UA5,

   'SLP1' : SLP1,
   'SLP2' : SLP2,
   'SLP3' : SLP3,
   'SLP4' : SLP4,
   'SLP5' : SLP5,

   'CSP1' : CSP1,
   'CSP2' : CSP2,
   'CSP3' : CSP3,
   'CSP4' : CSP4,
   'CSP5' : CSP5,

   'TSP1' : TSP1,
   'TSP2' : TSP2,
   'TSP3' : TSP3,
   'TSP4' : TSP4,
   'TSP5' : TSP5,

   'DUA1' :  DUA1,
   'DUA2' :  DUA2,
   'DUA3' :  DUA3,
   'DUA4' :  DUA4,
   'DUA5' :  DUA5,

   'SU1'  :  SU1,
   'SU2'  :  SU2,
   'SU3'  :  SU3,
   'SU4'  :  SU4,
   'SU5'  :  SU5,

   'PRX1' :  PRX1,
   'PRX2' :  PRX2,
   'PRX3' :  PRX3,
   'PRX4' :  PRX4,
   'PRX5' :  PRX5,

   'SFP1' :  SFP1,
   'SFP2' :  SFP2,
   'SFP3' :  SFP3,
   'SFP4' :  SFP4,
   'SFP5' :  SFP5,

   'SPECTRA' : SPECTRA,
   'SPECTRA2' : SPECTRA2,
   'SPECTRA3' : SPECTRA3,

   'SIPENT1' : SIPENT1,
   'SIPENT2' : SIPENT2,
   'SIPENT3' : SIPENT3,
}
 
#cm_xta_py_py_001.main_50 : Added flags for diameter 1.3 release.
AQ_IFDEF = 0
AQ_IFNDEF = 1
AQ_SCTP =  2
AQ_TLS = 3
DSB = 16
AQ_DUMMY_SCTP = 4
AQ_PEER_DISCOVERY = 5
AQ_MULT_VEND_PER_APP = 6
AQ_KSCTP = 7
DL_SDK_SESS = 8
LAQv2 = 9
AQUv2 = 10
AQ_MT = 11
AQ_REQTMR = 12
SS_MT_TMR = 13
AQ_INTIGRATED = 14
AQ_RUG =15
LX_RTP = 2
LX_AAL2 = 5
LX_GTP = 3
LX_DEBUGP = 4
EG_DEBUGP = 2
SZ_IFDEF = 0
SZ_IFNDEF = 1
SZ_DBG = 2
SZAC_LSZ_LC = 3
SZ_KSCTP = 4
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
SZ_RUG  = 14
SZ_SCTP = 5
SZAC_DYN_PEER = 6
SZAC_INTG_TEST = 7
SZAC_ENB = 8
SZAC_MME = 9
SZAC_VXWORKS = 10
SZ_ACC_TST_ESC_FUNC = 11
#cm_xta_py_py_001.main_37: Updated for S1AP 3.1 release
LSZV1 = 12
CM_PASN_CRIT_HANDL = 13
# cm_xta_py_py_001.main_53: Added for TC Dec/Enc 
SZTV1 = 15
# cm_xta_py_py_001.main_54: Added for S1 abort request
SZTV2 = 16
# cm_xta_py_py_001.main_58: support for Source RNC to target RNC
SZTV3 = 17

PJ_SEC_ASYNC = 2
PJ_CMP_ASYNC = 3
CCPU_OPT = 4

CZ_IFDEF = 0
CZ_IFNDEF = 1
CZ_DBG = 2
CZAC_LCZ_LC = 3
CZAC_LKSCTP = 4
CZAC_SCTP = 5
DEBUGP = 6
DM = 7
CZAC_INTSCTP = 8


SO_IFDEF = 0
SO_IFNDEF = 1
SO_SCTP =  2
SO_NS_STATEFUL =  3
SO_UA = 4
SO_EXT_OFFER_ANS = 5
SO_TLS = 6
LSO_ACNT = 7
SO_EVENT = 8
SO_REFER = 9
SO_RFC_3262 = 10 
SO_DNS = 11 
SO_NS = 12
SO_SESSTIMER = 13
SO_REPLACES = 14
SO_INSTMSG = 15
SO_DIS_SESS_NEG = 16
SO_JOIN = 17
SO_100TRY_PASS = 18 
SO_DIVERSION = 19
SO_ENUM =   20
SO_PRESENCE = 21
SO_PATH_ROUTE = 22
SO_COMPRESS = 23
SOT2 = 24
SO_PUBLISH = 25
SW_SDP = 26
SO_SSAP_RETRY = 27
SO_NAT = 28
SO_USE_UDP_SRVR = 29
SO_OUTDLGNOTIFY = 30
HI_TLS = 31
LCSOT = 32
LCHIT = 33
LCSCT = 34
DEBUGP = 35
PDCP_UE = 3
STCKWSAP = 184
STKWUSAP = 185
STRGUSAP = 186
STUDXSAP = 189
STCPJSAP = 187
STPJUSAP = 188
KWAC_NH_SAP = 0
KWAC_PJ_SAP = 1
KWAC_CKW_SAP = 2
KWAC_RG_SAP = 3
KWAC_CPJ_SAP = 4
KWAC_NH_PJU_SAP = 5
KWAC_PX_PJU_SAP = 6
KWAC_UDX_SAP = 7
KWAC_KWU_SAP = 8
PJAC_NH_SAP = 0
PJAC_PJ_SAP = 1
PJAC_CKW_SAP = 2
PJAC_RG_SAP = 3
PJAC_CPJ_SAP = 4
PJAC_NH_PJU_SAP = 5
PJAC_PX_PJU_SAP = 6
PJAC_UDX_SAP = 7
PJAC_KWU_SAP = 8
ENTRG  =  214
ENTKW  =  215
ENTPJ  =  216
ENTNH  =  217
ENTNX  =  218
ENTPX  =  226
NH_LOG_TO_FILE = 3
TENB_MULT_CELL_SUPPRT = 4
#cm_xta_py_py_001.main_49 - eGTP-PSF upgrade parameters
CM_MIN_UPD_MSG = 11
DEBUGP = 12
LCSMHWMILHW = 13
EG_MULTI_IP = 14
#cm_xta_py_py_001.main_56 - S2B and S2A 
EG_S2B_SUPP = 15
EG_S2A_SUPP = 16
#cm_xta_py_py_001.main_57 - Outgoing Piggyback support 
EG_PIGGYBACK_SUPP = 17
NH_ASN_COND_VALIDATE = 5
RRC_PHY_CFG_SUPP = 6
LTERRC_REL9 = 7
NHU_VER1 = 8
CTF_VER1 = 9
NHU_VER2 = 10
CTF_VER2 = 11
LTE_ADV  = 13
#Iuh 2.1 release
HMDBG  = 2
HM_LHM_LC  = 3
HM_LKSCTP =4
HM_SCTP =5
HM_HNB  =6
HM_HNBGW = 7
HM_REL9  = 8
CM_PASN_CRIT_HANDL=9

# For EGTP
IPV6_SUPPORTED = 3
EGTP_C         = 4
EGTP_U         = 5
EGTP_U_MULTI_THREADED = 6
#cm_xta_py_py_001.main_42 - eGTP-u R9 upgrade
EGTP_U_REL_9   = 7
EG_REL_930  = 930
#cm_xta_py_py_001.main_53 - eGTP-C define Path mgmt 
EGTP_C_PTH_MGT = 10

# For LTE MAC
TFU_TDD        = 2
RG_PHASE2_SCHED   = 3
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
LTEMAC_MIMO        = 4
RGR_SI_SCH     = 5
#cm_xta_py_py_001.main_37 - Added support for SPS
TFU_UPGRADE = 6
LTEMAC_SPS         =7
LTE_L2_MEAS         =8
LTE_RLC_R9          =9
LTEMAC_HDFDD        =9
LTEMAC_DLUE_TMGOPTMZ=10 # ADD Changes for Downlink UE Timing Optimization
LTEMAC_RGU_PAD=11
ERRCLS_ADD_RES      =12
ERRCLASS            =13
#cm_xta_py_py_001.main_44 - ADD - New feature defines 
RGR_CQI_REPT = 14
LTEMAC_DRX          =15
LTEMAC_R9           =16
DEBUGP              =17
RGR_V1              =18
# cm_xta_py_py_001.main_52 - Add - Changes for UL Scheduling at CRC Indication
RG_ULSCHED_AT_CRC   =19 #ADD Changes for UL Scheduling at CRC Indication
RGR_V2              =20
#For CM IPHC  and ROHC
#cm_xta_py_py_001.main_32 : Run Time Debug Support
CM_IPHC_DBG       = 4
CM_ROHC_DBG       = 5


#cm_xta_py_py_001.main_50 : Added flags for diameter 1.3 release.
flagDef = {
   "AQ_IFDEF"             : AQ_IFDEF,
   "AQ_IFNDEF"            : AQ_IFNDEF,
   "AQ_SCTP"              : AQ_SCTP,
   "AQ_TLS"               : AQ_TLS,
   "DSB"                  : DSB,
   "AQ_DUMMY_SCTP"                  : AQ_DUMMY_SCTP,
   "AQ_PEER_DISCOVERY"    : AQ_PEER_DISCOVERY,
   "AQ_MULT_VEND_PER_APP" : AQ_MULT_VEND_PER_APP,
   "AQ_KSCTP"             : AQ_KSCTP,
   "DL_SDK_SESS"          : DL_SDK_SESS,
   "LAQv2"                : LAQv2,
   "AQUv2"                : AQUv2,
   "AQ_MT"                : AQ_MT,
   "AQ_REQTMR"            : AQ_REQTMR,
   "SS_MT_TMR"            : SS_MT_TMR,
   "AQ_INTIGRATED"        : AQ_INTIGRATED,
   "AQ_RUG"               : AQ_RUG,
   "LX_RTP"             : LX_RTP,
   "LX_AAL2"             : LX_AAL2,
   "LX_GTP"             : LX_GTP,
   "LX_DEBUGP"          : LX_DEBUGP,
   "EG_DEBUGP"          : EG_DEBUGP,

   "SZ_IFDEF"           : SZ_IFDEF,
   "SZ_IFNDEF"          : SZ_IFNDEF,
   "SZ_DBG"             : SZ_DBG,
   "SZAC_LSZ_LC"        : SZAC_LSZ_LC,
   "SZ_KSCTP"           : SZ_KSCTP,
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   "SZ_RUG"             : SZ_RUG,
   "SZ_SCTP"            : SZ_SCTP,
   "SZAC_DYN_PEER"      : SZAC_DYN_PEER,
   "SZAC_INTG_TEST"     : SZAC_INTG_TEST,
   "SZAC_ENB"           : SZAC_ENB,
   "SZAC_MME"           : SZAC_MME,
   "SZAC_VXWORKS"       : SZAC_VXWORKS,
   "SZ_ACC_TST_ESC_FUNC" : SZ_ACC_TST_ESC_FUNC,
#cm_xta_py_py_001.main_37: Updated for S1AP 3.1 release
   "LSZV1"              : LSZV1,
# cm_xta_py_py_001.main_53: Added for TC Dec/Enc 
   "SZTV1"              : SZTV1,
# cm_xta_py_py_001.main_54: Added for S1 abort request
   "SZTV2"              : SZTV2,
#cm_xta_py_py_001.main_58 suppoty for source RNC to target RNC
   "SZTV3"              : SZTV3,
   "CM_PASN_CRIT_HANDL" : CM_PASN_CRIT_HANDL,
   
   "PJ_SEC_ASYNC"     : PJ_SEC_ASYNC,
   "PJ_CMP_ASYNC"       : PJ_CMP_ASYNC,
   "CCPU_OPT"           : CCPU_OPT,

   "CZ_IFDEF"           : CZ_IFDEF,
   "CZ_IFNDEF"          : CZ_IFNDEF,
   "CZ_DBG"             : CZ_DBG,
   "CZAC_LCZ_LC"        : CZAC_LCZ_LC,
   "CZAC_LKSCTP"        : CZAC_LKSCTP,
   "CZAC_SCTP"          : CZAC_SCTP,
   "DEBUGP"             : DEBUGP,
   "DM"                 : DM,
   "CZAC_INTSCTP"       : CZAC_INTSCTP,

   "SO_IFDEF"           : SO_IFDEF,
   "SO_IFNDEF"          : SO_IFNDEF,
   "SO_SCTP"            : SO_SCTP,
   "SO_NS_STATEFUL"     : SO_NS_STATEFUL,
   "SO_UA"              : SO_UA,
   "SO_EXT_OFFER_ANS"   : SO_EXT_OFFER_ANS,
   "SO_TLS"             : SO_TLS,
   "LSO_ACNT"           : LSO_ACNT,
   "SO_EVENT"           : SO_EVENT,
   "SO_REFER"           : SO_REFER,
   "SO_RFC_3262"        : SO_RFC_3262,
   "SO_DNS"             : SO_DNS,
   "SO_NS"              : SO_NS,
   "SO_SESSTIMER"       : SO_SESSTIMER,
   "SO_REPLACES"        : SO_REPLACES,
   "SO_INSTMSG"         : SO_INSTMSG,
   "SO_DIS_SESS_NEG"    : SO_DIS_SESS_NEG,
   "SO_JOIN"            : SO_JOIN,
   "SO_100TRY_PASS"     : SO_100TRY_PASS,
   "SO_DIVERSION"       : SO_DIVERSION,
   "SO_ENUM"            : SO_ENUM,
   "SO_PRESENCE"        : SO_PRESENCE,
   "SO_PATH_ROUTE"      : SO_PATH_ROUTE,
   "SO_COMPRESS"        : SO_COMPRESS,
   "SOT2"               : SOT2,
   "SO_PUBLISH"         : SO_PUBLISH,
   "SW_SDP"             : SW_SDP,
   "SO_SSAP_RETRY"      : SO_SSAP_RETRY,
   "SO_NAT"             : SO_NAT,
   "SO_USE_UDP_SRVR"    : SO_USE_UDP_SRVR,
   "SO_OUTDLGNOTIFY"    : SO_OUTDLGNOTIFY,
   "HI_TLS"             : HI_TLS,
   "LCSOT"              : LCSOT,
   "LCHIT"              : LCHIT,
   "LCSCT"              : LCSCT,
   "DEBUGP"             : DEBUGP,
   "PDCP_UE"            : PDCP_UE,
   "IPV6_SUPPORTED"     : IPV6_SUPPORTED,
   "EGTP_C"             : EGTP_C,
   "EGTP_U"             : EGTP_U,
#cm_xta_py_py_001.main_42 - eGTP-u R9 upgrade
   "EGTP_U_REL_9"       : EGTP_U_REL_9,
   "EGTP_U_MULTI_THREADED"     : EGTP_U_MULTI_THREADED,
   "EG_REL_930"     : EG_REL_930,
   "EGTP_C_PTH_MGT"     : EGTP_C_PTH_MGT,
   "STCKWSAP"           : STCKWSAP,
   "STKWUSAP"           : STKWUSAP,
   "STRGUSAP"           : STRGUSAP,
   "STUDXSAP"           : STUDXSAP,
   "STCPJSAP"           : STCPJSAP,
   "STPJUSAP"           : STPJUSAP,
   "KWAC_KWU_SAP"       : KWAC_KWU_SAP,
   "KWAC_NH_SAP"        : KWAC_NH_SAP,
   "KWAC_PJ_SAP"        : KWAC_PJ_SAP,
   "KWAC_CKW_SAP"       : KWAC_CKW_SAP,
   "KWAC_RG_SAP"        : KWAC_RG_SAP,
   "KWAC_CPJ_SAP"       : KWAC_CPJ_SAP,
   "KWAC_NH_PJU_SAP"    : KWAC_NH_PJU_SAP,
   "KWAC_PX_PJU_SAP"    : KWAC_PX_PJU_SAP,
   "KWAC_UDX_SAP"       : KWAC_UDX_SAP,
   "PJAC_KWU_SAP"       : PJAC_KWU_SAP,
   "PJAC_NH_SAP"        : PJAC_NH_SAP,
   "PJAC_PJ_SAP"        : PJAC_PJ_SAP,
   "PJAC_CKW_SAP"       : PJAC_CKW_SAP,
   "PJAC_RG_SAP"        : PJAC_RG_SAP,
   "PJAC_CPJ_SAP"       : PJAC_CPJ_SAP,
   "PJAC_NH_PJU_SAP"    : PJAC_NH_PJU_SAP,
   "PJAC_PX_PJU_SAP"    : PJAC_PX_PJU_SAP,
   "PJAC_UDX_SAP"       : PJAC_UDX_SAP,
   "ENTNH"              : ENTNH,
   "ENTKW"              : ENTKW,
   "ENTRG"              : ENTRG,
   "ENTPJ"              : ENTPJ,
   "ENTNX"              : ENTNX,
   "ENTPX"              : ENTPX,
   "NH_LOG_TO_FILE"     : NH_LOG_TO_FILE,
   "LTE_ADV"            : LTE_ADV,
   "TENB_MULT_CELL_SUPPRT" : TENB_MULT_CELL_SUPPRT,
#cm_xta_py_py_001.main_49 - eGTP-PSF upgrade parameters
   "CM_MIN_UPD_MSG" : CM_MIN_UPD_MSG,
   "DEBUGP" : DEBUGP,
   "LCSMHWMILHW" : LCSMHWMILHW,
   "EG_MULTI_IP" : EG_MULTI_IP,
#cm_xta_py_py_001.main_56 - S2B and S2A 
   "EG_S2B_SUPP" : EG_S2B_SUPP,
   "EG_S2A_SUPP" : EG_S2A_SUPP,
   #cm_xta_py_py_001.main_57 -Outgoing Piggyback support 
   "EG_PIGGYBACK_SUPP" : EG_PIGGYBACK_SUPP,
   "NH_ASN_COND_VALIDATE" : NH_ASN_COND_VALIDATE,
   "RRC_PHY_CFG_SUPP" : RRC_PHY_CFG_SUPP,
   "LTERRC_REL9"      : LTERRC_REL9,
   "NHU_VER1"         : NHU_VER1,
   "CTF_VER1"         : CTF_VER1,
   "NHU_VER2"         : NHU_VER2,
   "CTF_VER2"         : CTF_VER2,
   "TFU_TDD"            : TFU_TDD,
   "RG_PHASE2_SCHED"       : RG_PHASE2_SCHED,
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   "LTEMAC_MIMO"            : LTEMAC_MIMO,
   "RGR_SI_SCH"       : RGR_SI_SCH,
#cm_xta_py_py_001.main_38 - Added support for SPS
   "TFU_UPGRADE"      : TFU_UPGRADE, 
   "LTEMAC_SPS"      : LTEMAC_SPS, 
   "CM_IPHC_DBG"           : CM_IPHC_DBG,
   "CM_ROHC_DBG"           : CM_ROHC_DBG,
   #Iuh 2.1 release
   "HM_DBG"             : HMDBG,
   "HM_LHM_LC"          : HM_LHM_LC,
   "HM_LKSCTP"          : HM_LKSCTP,
   "HM_SCTP"            : HM_SCTP,
   "HM_HNB"             : HM_HNB,
   "HM_HNBGW"           : HM_HNBGW,
   "HM_REL9"            : HM_REL9,
   "CM_PASN_CRIT_HANDL" : CM_PASN_CRIT_HANDL,
   "LTE_L2_MEAS"     : LTE_L2_MEAS,
   "LTE_RLC_R9"      : LTE_RLC_R9,
   "LTEMAC_HDFDD"    : LTEMAC_HDFDD, 
   "LTEMAC_DLUE_TMGOPTMZ"  : LTEMAC_DLUE_TMGOPTMZ, # ADD Changes for Downlink UE Timing Optimization
# cm_xta_py_py_001.main_52 - Add - Changes for UL Scheduling at CRC Indication
   "RG_ULSCHED_AT_CRC":RG_ULSCHED_AT_CRC, # ADD Changes for Downlink UE Timing Optimization
   "LTEMAC_RGU_PAD": LTEMAC_RGU_PAD,
   "ERRCLS_ADD_RES"  : ERRCLS_ADD_RES, 
   "ERRCLASS"     : ERRCLASS, 
#cm_xta_py_py_001.main_44 - ADD - New feature defines
   "RGR_CQI_REPT" :RGR_CQI_REPT,
   "LTEMAC_DRX"   : LTEMAC_DRX,
   "LTEMAC_R9"    : LTEMAC_R9,
   "DEBUGP"    : DEBUGP,
   "RGR_V1"    : RGR_V1,
   "RGR_V2"    : RGR_V2,
}

#
#       Fun:   validateRe
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def validateRe(node, msg) :
   '''Return the attribute value of  defined by type'''

   # Get the tapa.re Node, consider only the first one, ignore rest
   reNodeList = node.getElementsByTagName('tapa.re')

   for reNode in reNodeList :
      # Check for the presence of the attribute
      if reNode.hasAttribute('re') :
         rePatt = str(reNode.getAttribute('re'))

         # Compile the pattern
         patt = re.compile(rePatt)

         # Now match 
         reObj = patt.search(msg)

         # Any non match, return a failure
         if reObj == None :
            return False
         else :
            # Add all matches to the global re List
            reList.update(reObj.groupdict())

   return True


#
#       Fun:   validateAttr
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def validateAttr(xmlNode) :
   '''Return the attribute value of  defined by type'''

   for node in xmlNode.childNodes :
      # Find all the steps under the top Node
      # Skip anything except ELEMENT_NODE
      if node.nodeType != node.ELEMENT_NODE :
         continue

      # Get the tagName for the step
      cmdName = str(node.tagName)

      # Check if compound command
      if compCmdDict.has_key(cmdName) :
         # Check attributes
         for s, t in node.attributes.items() :
            # Compound command, move ahead
            if not cm_xta_pyattr.attrDict.has_key(s) :
               print 'Unknown attribute :', s
               # raise xml.dom.SyntaxErr (s + ': Unknown attribute\n')
               # return False

      elif intCmdDict.has_key(cmdName) :
         # Check attributes
         for s, t in node.attributes.items() :
            # Compound command, move ahead
            if not cm_xta_pyattr.attrDict.has_key(s) :
               print 'Unknown attribute :', s
               # raise xml.dom.SyntaxErr (s + ': Unknown attribute\n')
               # return False

         # Internal command, an internal command can
         # have only simple commands, call itself
         # recursively to validate the same
         for subNode in node.childNodes :
            # Find all the steps under the top Node
            # Skip anything except ELEMENT_NODE
            if subNode.nodeType != node.ELEMENT_NODE :
               continue

            # Get the tagName for the step
            subCmdName = str(subNode.tagName)

            for s, t in subNode.attributes.items() :
               # Compound command, move ahead
               if not cm_xta_pyattr.attrDict.has_key(s) :
                  print 'Unknown attribute :', s
                  # raise xml.dom.SyntaxErr (s + ': Unknown attribute\n')
                  # return False
      else :
         # Unknown command, return False
         return False

   #dbgPrnt('Validation passed')
   return True


#
#       Fun:   validatePre
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def validatePre(xmlPre) :
   '''Return the attribute value of  defined by type'''

   XX_INV_IFDEF  =  0
   XX_INV_IFNDEF =  1

   AQ_SCTP =  2
   AQ_TLS = 3
   DSB = 16
   AQ_DUMMY_SCTP = 4
   AQ_PEER_DISCOVERY = 5
   AQ_MULT_VEND_PER_APP = 6
   AQ_KSCTP = 7
   DL_SDK_SESS = 8
   LAQv2 = 9 
   AQUv2 = 10
   AQ_MT = 11
   AQ_REQTMR = 12
   SS_MT_TMR = 13
   AQ_INTIGRATED = 14
   AQ_RUG = 15
   LX_RTP = 2
   LX_AAL2 = 5
   LX_GTP = 3
   LX_DEBUGP = 4

   EG_DEBUGP = 2
   SZ_IFDEF = 0
   SZ_IFNDEF = 1
   SZ_DBG = 2
   SZAC_LSZ_LC = 3
   SZ_KSCTP = 4
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   SZ_RUG  = 14
   SZ_SCTP = 5
   SZAC_DYN_PEER = 6
   SZAC_INTG_TEST = 7
   SZAC_ENB = 8
   SZAC_MME = 9
   SZAC_VXWORKS = 10
   SZ_ACC_TST_ESC_FUNC = 11
#cm_xta_py_py_001.main_37: Updated for S1AP 3.1 release
   LSZV1 = 12
   CM_PASN_CRIT_HANDL = 13
# cm_xta_py_py_001.main_53: Added for TC Dec/Enc 
   SZTV1 = 15
# cm_xta_py_py_001.main_54: Added for S1 abort request
   SZTV2 = 16
#cm_xta_py_py_001.main_58 suppoty for source RNC to target RNC
   SZTV3 = 17
   
   PJ_SEC_ASYNC = 2
   PJ_CMP_ASYNC = 3
   CCPU_OPT = 4

   CZ_IFDEF = 0
   CZ_IFNDEF = 1
   CZ_DBG = 2
   CZAC_LCZ_LC = 3
   CZAC_LKSCTP = 4
   CZAC_SCTP = 5
   DEBUGP = 6
   DM = 7
   CZAC_INTSCTP = 8

   SO_SCTP =  2
   SO_NS_STATEFUL =  3
   SO_UA          = 4
   SO_EXT_OFFER_ANS = 5
   SO_TLS = 6
   LSO_ACNT = 7
   SO_EVENT    = 8
   SO_REFER  = 9
   SO_RFC_3262 = 10 
   SO_DNS = 11 
   SO_NS = 12
   SO_SESSTIMER = 13
   SO_REPLACES = 14
   SO_INSTMSG = 15
   SO_DIS_SESS_NEG = 16
   SO_JOIN = 17
   SO_100TRY_PASS = 18 
   SO_DIVERSION = 19
   SO_ENUM = 20
   SO_PRESENCE = 21
   SO_PATH_ROUTE = 22
   SO_COMPRESS = 23
   SOT2 = 24
   SO_PUBLISH = 25
   SW_SDP = 26
   SO_SSAP_RETRY = 27
   SO_NAT = 28
   SO_USE_UDP_SRVR = 29
   SO_OUTDLGNOTIFY = 30
   HI_TLS = 31
   LCSOT = 32
   LCHIT = 33
   LCSCT = 34
   DEBUGP = 35
   PDCP_UE = 3
   NH_LOG_TO_FILE = 3
   TENB_MULT_CELL_SUPPRT = 4
#cm_xta_py_py_001.main_49 - eGTP-PSF upgrade parameters
   CM_MIN_UPD_MSG = 11
   DEBUGP = 12
   LCSMHWMILHW = 13
   EG_MULTI_IP = 14
#cm_xta_py_py_001.main_56 - S2B and S2A 
   EG_S2B_SUPP = 15
   EG_S2A_SUPP = 16
   #cm_xta_py_py_001.main_57 - Piggyback support 
   EG_PIGGYBACK_SUPP = 17
   NH_ASN_COND_VALIDATE = 5
   RRC_PHY_CFG_SUPP = 6
   LTERRC_REL9 = 7
   NHU_VER1    = 8
   CTF_VER1    = 9
   NHU_VER2    = 10
   CTF_VER2    = 11
   LTE_ADV     = 13

   IPV6_SUPPORTED = 3
   EGTP_C         = 4
   EGTP_U         = 5
   EGTP_U_MULTI_THREADED = 6
#cm_xta_py_py_001.main_42 - eGTP-u R9 upgrade
   EGTP_U_REL_9   = 7
#cm_xta_py_py_001.main_53 - eGTP-C define Path mgmt 
   EGTP_C_PTH_MGT = 10

   TFU_TDD = 2
   RG_PHASE2_SCHED = 3
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   LTEMAC_MIMO = 4
   RGR_SI_SCH = 5
#cm_xta_py_py_001.main_37 - Added supprt for SPS
   LTEMAC_SPS  = 7
   LTE_L2_MEAS  = 8 
   LTE_RLC_R9 = 9
   LTEMAC_HDFDD = 9
   LTEMAC_DLUE_TMGOPTMZ=10 # ADD Changes for Downlink UE Timing Optimization
   LTEMAC_RGU_PAD=11 
   ERRCLS_ADD_RES = 12
   ERRCLASS       = 13
#cm_xta_py_py_001.main_44 - ADD - New feature defines
   RGR_CQI_REPT = 14
   LTEMAC_DRX     = 15
   LTEMAC_R9      = 16
   DEBUGP         = 17
   RGR_V1         = 18
# cm_xta_py_py_001.main_52 - Add - Changes for UL Scheduling at CRC Indication
   RG_ULSCHED_AT_CRC = 19 #ADD Changes for UL Scheduling at CRC Indication
   RGR_V2         = 20 
   RG_PFS_STATS   = 21
   
   CM_IPHC_DBG       = 4
   CM_ROHC_DBG       = 5


   XX_MODE_SINGLE = 0
   XX_MODE_MULTIPLE = 1
   XX_MODE_EXTERNAL = 2
   XX_MODE_LOAD     = 3

   #Iuh 2.1 release
   HMDBG  = 2
   HM_LHM_LC  = 3
   HM_LKSCTP =4
   HM_SCTP =5
   HM_HNB  =6
   HM_HNBGW = 7
   HM_REL9 = 8
   CM_PASN_CRIT_HANDL=9

#cm_xta_py_py_001.main_50 : Added flags for diameter 1.3 release.

   genDef = {
      "XX_INV_IFDEF"       : XX_INV_IFDEF,
      "XX_INV_IFNDEF"      : XX_INV_IFNDEF,
      "AQ_SCTP"            : AQ_SCTP,
      "AQ_TLS"             : AQ_TLS,
      "DSB"                : DSB,
      "AQ_DUMMY_SCTP"                : AQ_DUMMY_SCTP,
      "AQ_MULT_VEND_PER_APP" : AQ_MULT_VEND_PER_APP,
      "AQ_PEER_DISCOVERY"  : AQ_PEER_DISCOVERY,
      "AQ_KSCTP"           : AQ_KSCTP,
      "DL_SDK_SESS"        : DL_SDK_SESS,
      "LAQv2"              : LAQv2,
      "AQUv2"              : AQUv2,
      "AQ_MT"              : AQ_MT,
      "AQ_REQTMR"          : AQ_REQTMR,
      "SS_MT_TMR"          : SS_MT_TMR,
      "AQ_INTIGRATED"      : AQ_INTIGRATED,
      "AQ_RUG"             : AQ_RUG,

      "LX_RTP"             : LX_RTP,
      "LX_AAL2"             : LX_AAL2,
      "LX_GTP"             : LX_GTP,
      "LX_DEBUGP"          : LX_DEBUGP,
      "EG_DEBUGP"          : EG_DEBUGP,

      "SZ_IFDEF"           : SZ_IFDEF,
      "SZ_IFNDEF"          : SZ_IFNDEF,
      "SZ_DBG"             : SZ_DBG,
      "SZAC_LSZ_LC"        : SZAC_LSZ_LC,
      "SZ_KSCTP"           : SZ_KSCTP,
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
      "SZ_RUG"             : SZ_RUG,
      "SZ_SCTP"            : SZ_SCTP,
      "SZAC_DYN_PEER"      : SZAC_DYN_PEER,
      "SZAC_INTG_TEST"     : SZAC_INTG_TEST,
      "SZAC_ENB"           : SZAC_ENB,
      "SZAC_MME"           : SZAC_MME,
      "SZAC_VXWORKS"       : SZAC_VXWORKS,
      "SZ_ACC_TST_ESC_FUNC"       : SZ_ACC_TST_ESC_FUNC,
#cm_xta_py_py_001.main_37: Updated for S1AP 3.1 release
      "LSZV1"              : LSZV1,
# cm_xta_py_py_001.main_53: Added for TC Dec/Enc 
      "SZTV1"              : SZTV1,
# cm_xta_py_py_001.main_54: Added for S1 abort request
      "SZTV2"              : SZTV2,
#cm_xta_py_py_001.main_58 suppoty for source RNC to target RNC
      "SZTV3"              : SZTV3,
      "CM_PASN_CRIT_HANDL" : CM_PASN_CRIT_HANDL,
     
      "CZ_IFDEF"           : CZ_IFDEF,
      "CZ_IFNDEF"          : CZ_IFNDEF,
      "CZ_DBG"             : CZ_DBG,
      "CZAC_LCZ_LC"        : CZAC_LCZ_LC,
      "CZAC_LKSCTP"        : CZAC_LKSCTP,
      "CZAC_SCTP"          : CZAC_SCTP,
      "DEBUGP"             : DEBUGP,
      "DM"                 : DM,
      "CZAC_INTSCTP"       : CZAC_INTSCTP,

      "SO_SCTP"            : SO_SCTP,
      "SO_NS_STATEFUL"     : SO_NS_STATEFUL,
      "SO_UA"              : SO_UA,
      "SO_EXT_OFFER_ANS"   : SO_EXT_OFFER_ANS,
      "SO_TLS"             : SO_TLS,
      "LSO_ACNT"           : LSO_ACNT,
      "SO_EVENT"           : SO_EVENT,
      "SO_REFER"           : SO_REFER,
      "SO_RFC_3262"        : SO_RFC_3262,
      "SO_DNS"             : SO_DNS,
      "SO_NS"              : SO_NS,
      "SO_SESSTIMER"       : SO_SESSTIMER,
      "SO_REPLACES"        : SO_REPLACES,
      "SO_INSTMSG"         : SO_INSTMSG,
      "SO_DIS_SESS_NEG"    : SO_DIS_SESS_NEG,
      "SO_JOIN"            : SO_JOIN,
      "SO_100TRY_PASS"     : SO_100TRY_PASS,
      "SO_DIVERSION"       : SO_DIVERSION,
      "SO_ENUM"            : SO_ENUM,
      "SO_PRESENCE"        : SO_PRESENCE,
      "SO_PATH_ROUTE"      : SO_PATH_ROUTE,
      "SO_COMPRESS"        : SO_COMPRESS,
      "SOT2"               : SOT2,
      "SO_PUBLISH"         : SO_PUBLISH,
      "SW_SDP"             : SW_SDP,
      "SO_SSAP_RETRY"      : SO_SSAP_RETRY,
      "SO_NAT"             : SO_NAT,
      "SO_USE_UDP_SRVR"    : SO_USE_UDP_SRVR,
      "SO_OUTDLGNOTIFY"    : SO_OUTDLGNOTIFY,
      "HI_TLS"             : HI_TLS,
      "LCSOT"              : LCSOT,
      "LCHIT"              : LCHIT,
      "LCSCT"              : LCSCT,
      "DEBUGP"             : DEBUGP,
      "PDCP_UE"            : PDCP_UE,
      "NH_LOG_TO_FILE"     : NH_LOG_TO_FILE,
      "LTE_ADV"            : LTE_ADV,
      "TENB_MULT_CELL_SUPPRT" : TENB_MULT_CELL_SUPPRT,
#cm_xta_py_py_001.main_49 - eGTP-PSF upgrade parameters
      "CM_MIN_UPD_MSG"     : CM_MIN_UPD_MSG,
      "DEBUGP"             : DEBUGP,
      "LCSMHWMILHW"        : LCSMHWMILHW,
      "EG_MULTI_IP"        : EG_MULTI_IP,
#cm_xta_py_py_001.main_56 - S2B and S2A 
      "EG_S2B_SUPP"        : EG_S2B_SUPP,
      "EG_S2A_SUPP"        : EG_S2A_SUPP,
#cm_xta_py_py_001.main_57 - Outgoing Piggyback support  
      "EG_PIGGYBACK_SUPP"  : EG_PIGGYBACK_SUPP,
      "NH_ASN_COND_VALIDATE" : NH_ASN_COND_VALIDATE,
      "RRC_PHY_CFG_SUPP"   : RRC_PHY_CFG_SUPP,
      "LTERRC_REL9"        : LTERRC_REL9,
      "NHU_VER1"           : NHU_VER1,
      "CTF_VER1"           : CTF_VER1,
      "NHU_VER2"           : NHU_VER2,
      "CTF_VER2"           : CTF_VER2,
      "IPV6_SUPPORTED"     : IPV6_SUPPORTED,
#cm_xta_py_py_001.main_42 - eGTP-u R9 upgrade
      "EGTP_U_REL_9"       : EGTP_U_REL_9,
      "EGTP_U_MULTI_THREADED"             : EGTP_U_MULTI_THREADED,
      "EGTP_C"             : EGTP_C,
      "EGTP_U"             : EGTP_U,
#cm_xta_py_py_001.main_53 - eGTP-C define Path mgmt 
      "EGTP_C_PTH_MGT"     : EGTP_C_PTH_MGT,
      "TFU_TDD"            : TFU_TDD,
	  "RG_PFS_STATS"        : RG_PFS_STATS,
      "RG_PHASE2_SCHED"    : RG_PHASE2_SCHED,
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
      "LTEMAC_MIMO"        : LTEMAC_MIMO,
      "RGR_SI_SCH"         : RGR_SI_SCH,
      "CM_IPHC_DBG"        : CM_IPHC_DBG,
      "CM_ROHC_DBG"        : CM_ROHC_DBG,
#cm_xta_py_py_001.main_37 - Added support for SPS
      "LTEMAC_MIMO"        : LTEMAC_MIMO,
      "TFU_UPGRADE"        : TFU_UPGRADE, 
	  "LTEMAC_SPS"          : LTEMAC_SPS,
	  "LTE_L2_MEAS"         : LTE_L2_MEAS,
        "LTE_RLC_R9"       : LTE_RLC_R9,
      "LTEMAC_HDFDD"       : LTEMAC_HDFDD,
     "LTEMAC_DLUE_TMGOPTMZ": LTEMAC_DLUE_TMGOPTMZ, # ADD Changes for Downlink UE Timing Optimization
     "RG_ULSCHED_AT_CRC"   :RG_ULSCHED_AT_CRC, # ADD Changes for Downlink UE Timing Optimization
     "LTEMAC_RGU_PAD"      :LTEMAC_RGU_PAD, 
     "ERRCLS_ADD_RES"      : ERRCLS_ADD_RES, 
     "ERRCLASS"            : ERRCLASS, 
#cm_xta_py_py_001.main_44 - ADD - New feature defines
     "LTEMAC_DRX"          : LTEMAC_DRX,
     "LTEMAC_R9"           : LTEMAC_R9,
     "DEBUGP"              : DEBUGP,
     "RGR_V1"              : RGR_V1,
     "RGR_V2"              : RGR_V2,
      "single"             : XX_MODE_SINGLE,
      "multiple"           : XX_MODE_MULTIPLE,
      "external"           : XX_MODE_EXTERNAL,
      "load"               : XX_MODE_LOAD,
   #Iuh 2.1 release
   "HM_DBG"                : HMDBG,
   "HM_LHM_LC"             : HM_LHM_LC,
   "HM_LKSCTP"             : HM_LKSCTP,
   "HM_SCTP"               : HM_SCTP,
   "HM_HNB"                : HM_HNB,
   "HM_HNBGW"              : HM_HNBGW,
   "HM_REL9"               : HM_REL9,
   "CM_PASN_CRIT_HANDL"    : CM_PASN_CRIT_HANDL,
   "RGR_CQI_REPT"          : RGR_CQI_REPT,
   "PJ_SEC_ASYNC"          : PJ_SEC_ASYNC,
   "PJ_CMP_ASYNC"          : PJ_CMP_ASYNC,
   "CCPU_OPT"              : CCPU_OPT,

   }

   ifdefValStr = []
   ifndefValStr = []
   ifdefVal  = []
   ifndefVal = []
   mode      = XX_MODE_MULTIPLE

   # Get the tapa.ifdef Node, consider only the first one, ignore rest
   ifdefNodeLst = xmlPre.getElementsByTagName('tapa.ifdef')[0].getElementsByTagName('tapa.flag')

   # Get the tapa.ifndef Node, consider only the first one, ignore rest
   ifndefNodeLst = xmlPre.getElementsByTagName('tapa.ifndef')[0].getElementsByTagName('tapa.flag')

   # Get the tapa.mode Node
   modeNodeLst = xmlPre.getElementsByTagName('tapa.mode')

   for node in ifdefNodeLst :
      if node.hasAttribute('id') :
         attrVal = str(node.getAttribute('id'))
         ifdefValStr.append(attrVal)

         # Check if it is a valid flag
         if genDef.has_key(attrVal) :
            # Add the ifdef value
            ifdefVal.append(genDef[attrVal])
         else :
            ifdefVal.append(XX_INV_IFDEF)
            #print 'validatePre(): Invalid flag', attrVal

   for node in ifndefNodeLst :
      if node.hasAttribute('id') :
         attrVal = str(node.getAttribute('id'))
         ifndefValStr.append(attrVal)

         # Check if it is a valid flag
         if genDef.has_key(attrVal) :
            # Add the ifdef value
            ifndefVal.append(genDef[attrVal])
         else :
            ifndefVal.append(XX_INV_IFNDEF)
            #print 'validatePre(): Invalid flag', attrVal

   for node in modeNodeLst :
      if node.hasAttribute('mode') :
         attrVal = str(node.getAttribute('mode'))

         # Check if it is a valid flag
         if genDef.has_key(attrVal) :
            # Add the ifdef value
            mode = genDef[attrVal]
            modeStr = attrVal
         else :
            print 'validatePre(): Invalid flag', attrVal
            raise xml.dom.SyntaxErr ('tapa.mode invalid mode value: ' + attrVal + '\n')
            return None
      else :
         raise xml.dom.SyntaxErr ('tapa.mode mode attribute not found\n')
         return None

   #print [ifdefValStr, ifdefVal, ifndefValStr, ifndefVal, modeStr, mode]
   return [ifdefValStr, ifdefVal, ifndefValStr, ifndefVal, modeStr, mode]

#
#       Fun:   getFlagDict
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getFlagDict(key) :
   '''Return the attribute value of  defined by type'''

   XX_INV_IFDEF  =  0

   if flagDef.has_key(key) :
      return flagDef[key]
   else :
      return XX_INV_IFDEF


#
#       Fun:   getValDict
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getValDict(key) :
   '''Return the attribute value of  defined by type'''


   AENA =  1
   ASHUTDOWN = 36
   ADISGRC =  3
   AADD =  6
   ADEL =  7
   AMODIFY =  62
   ACLEAR = 16
   ADISIMM = 2
   ABND_ENA = 21
   ABND = 30
   AUBND = 31
   AUBND_DIS = 31
   AADD_ASSOC_TPTSRV = 70
   ADEL_ASSOC_TPTSRV = 71
   STGEN = 1  
   STSSAP = 117
   STPSAP = 7
   # cm_xta_py_py_001.main_ : Updated for FTHA
   CMXTA_INST_ID = 0 
   # Added the support for FTHA Integration
   LSG_HI_ENT_DIST = 1 
   LSG_HI_ENT_DEDICATED_FT = 2 
   LSG_HI_ENT_NONDEDICATED_FT = 4 
   LSG_HI_ENT_CONVENTIONAL = 8 
   LSG_HI_USE_ACTIVE = 1 
   LSG_HI_USE_STANDBY = 2 
#cm_xta_py_py_001.main_50 : Correcting the ProcId values.
   CMXTA_PROCID_ONE = 100 
   CMXTA_PROCID_SINGLE = 900
   ZO_ZOT_MODE_MANUAL = 1
   JC_JCT_MODE_MANUAL = 1
   JC_UPDTMR_EXPIRED = 17
   JCPIF = 273
   HITIF = 172
   AQUIF = 214
   JCPIFVER = 0x100
   AQUIFVER = 0x100
   HITIFVER = 0x100

   RTE_PROTO = 0x06
   CMXTA_PROCID_TWO = 200 
   CMXTA_PROCID_THREE = 300 
   CMXTA_PROCID_FOUR = 400 
   CMXTA_PROCID_FIVE = 500 
   CMXTA_PROCID_MASTER = 900 
   CMXTA_PROCID_SLAVE1 = 100 
   CMXTA_PROCID_SLAVE2 = 200 
   CMXTA_PROCID_SLAVE3 = 300 
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   CMXTA_PROCID_SLAVE4 = 400 
   CMXTA_PROCID_SLAVE5 = 500 
   CMXTA_PROCID_SLAVE6 = 600 
   CMXTA_PROCID_SLAVE7 = 700 
   CMXTA_PROCID_SLAVE8 = 800 
   CMPFTHA_STATE_ACTIVE = 1;
   CMPFTHA_STATE_STANDBY = 2;
   CMPFTHA_STATE_OOS = 3;
   STTPTSRV = 149
   STTPTENDP = 177 
   STSIPENT = 155
   STTSAP = 2 

   DBGMASK_SI =1
   DBGMASK_MI =2
   DBGMASK_UI=4
   DBGMASK_LI=8
   DBGMASK_PI=16
   
   LAQ_DBGMASK_SMEM=(0x100 << 0)
   LAQ_DBGMASK_MODULES=(0x100 << 1) 
   LAQ_DBGMASK_SUPP_FUNC=(0x100 << 2)
#cm_xta_py_py_001.main_50 : Added diameter modules debug masks.
   LAQ_DBGMASK_MP=(0x100 << 3)
   LAQ_DBGMASK_PSM=(0x100 << 4)
   LAQ_DBGMASK_DENC=(0x100 << 5)
   LAQ_DBGMASK_CDB=(0x100 << 6)
   LAQ_DBGMASK_TMR=(0x100 << 7)
   LAQ_DBGMASK_PD=(0x100 << 8)
   LAQ_DBGMASK_FOFB=(0x100 << 9)
   LAQ_DBGMASK_AG=(0x100 << 10)

   LLX_DBGMASK_MSG =(0x00000100 << 0)
   LLX_DBGMASK_FLOW =(0x00000100 << 1)
   LLX_DBGMASK_DBG =(0x00000100 << 2)
   LLX_DBGMASK_INFO =(0x00000100 << 3)
   LLX_DBGMASK_TRC =(0x00000100 << 4)
   LLX_DBGMASK_WARN =(0x00000100 << 5)
   LLX_DBGMASK_ERROR =(0x00000100 << 6)
   LLX_DBGMASK_FATAL =(0x00000100 << 7)
   LLX_DBGMASK_MEM =(0x00000100 << 8)
   LLX_DBGMASK_BUF =(0x00000100 << 9)
   LLX_DBGMASK_PARAM =(0x00000100 << 10)

   DUMMY_TUCL = 2
   DUMMY_SCTP = 2
   AQ_DUMMY_SCTP = 2

   LCM_PRIM_OK = 0 
   LCM_PRIM_NOK = 1 
   LCM_PRIM_OK_NDONE = 2

#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   LCM_REASON_UPDTMR_EXPIRED = 17
   LCM_REASON_INVALID_MSGTYPE = 3
   LCM_REASON_LYR_SPECIFIC = 256
   LCM_REASON_MEM_NOAVAIL = 4
   LCM_REASON_REGTMR_FAIL = 7
   LCM_REASON_GENCFG_NOT_DONE = 8
   LCM_REASON_INVALID_ACTION = 9
   LCM_REASON_INVALID_SUBACTION = 10
   LCM_REASON_EXCEED_CONF_VAL = 19
   LCM_REASON_INVALID_SAP = 12
   LCM_REASON_INVALID_PAR_VAL = 13
   LCM_REASON_INVALID_STATE = 11
   LCM_REASON_PRTLYRCFG_NOT_DONE = 22
   LCM_REASON_INVALID_ENTITY = 1
   LCM_REASON_INVALID_ELMNT = 5
   LCM_REASON_RECONFIG_FAIL = 6
   LCM_REASON_INV_NODE_TYPE = 48
   LCM_REASON_INV_NMB_USAPS = 49
   LCM_REASON_INV_NMB_SRVS = 50
   LCM_REASON_INV_NMB_TNLS = 51
   LCM_REASON_INVALID_INTFTYPE = 52
   LCM_REASON_INVALID_TPTTYPE = 53
   LCM_REASON_INVALID_TMRVAL = 54
   LCM_REASON_INVALID_NUMRETRY = 55
   LCM_REASON_TSAPCFG_NOT_DONE = 56
#cm_xta_py_py_001.main_55:  TSAP config reason
   LCM_REASON_TSAP_IP_CFGD = 83
   LCM_REASON_TPTSRV_CFGD = 57
   LCM_REASON_TPTCONID_NOAVAIL = 58
   LCM_REASON_SRVINIT_FAIL = 59
   LCM_REASON_ECOSAP_CFGD = 60
   LCM_REASON_DEFSRV_CFGD = 61
   LCM_REASON_INVALID_NMB_INTFS = 62
   LCM_REASON_INVALID_PORT = 63
   LCM_REASON_INV_TNL_ARRSIZ = 64
   LCM_REASON_ECOSAP_NOTCFGD = 65
   LCM_REASON_HASHING_FAILED = 20
   LCM_EVENT_UI_INV_EVT = 1
   LCM_EVENT_LI_INV_EVT = 2
   LCM_EVENT_PI_INV_EVT = 3
   LCM_EVENT_INV_EVT = 4
   LCM_EVENT_INV_STATE = 5
   LCM_EVENT_INV_TMR_EVT = 6
   LCM_EVENT_MI_INV_EVT = 7
   LCM_EVENT_BND_FAIL = 8
   LCM_EVENT_NAK = 9
   LCM_EVENT_TIMEOUT = 10
   LCM_EVENT_BND_OK = 11
   LCM_EVENT_SMEM_ALLOC_FAIL = 12
   LCM_EVENT_DMEM_ALLOC_FAIL = 13
   LCM_EVENT_SEQERR = 14
   LCM_EVENT_OOM = 15
   LCM_EVENT_UPDMSG_ERR = 16
   LCM_EVENT_HTBT_EXP = 17
   LCM_EVENT_TRANSLATION_FAILURE = 18
   LCM_EVENT_LYR_SPECIFIC = 256
   LCM_CAUSE_UNKNOWN = 0
   LCM_CAUSE_OUT_OF_RANGE = 1
   LCM_CAUSE_INV_SAP = 2
   LCM_CAUSE_INV_SPID = 3
   LCM_CAUSE_INV_SUID = 4
   LCM_CAUSE_INV_NETWORK_MSG = 5
   LCM_CAUSE_DECODE_ERR = 6
   LCM_CAUSE_USER_INITIATED = 7
   LCM_CAUSE_MGMT_INITIATED = 8
   LCM_CAUSE_INV_STATE = 9
   LCM_CAUSE_TMR_EXPIRED = 10
   LCM_CAUSE_INV_MSG_LENGTH = 11
   LCM_CAUSE_PROT_NOT_ACTIVE = 12
   LCM_CAUSE_INV_PAR_VAL = 13
   LCM_CAUSE_NEG_CFM = 14
   LCM_CAUSE_MEM_ALLOC_FAIL = 15
   LCM_CAUSE_HASH_FAIL = 16
   LCM_CAUSE_VERSION_MISMATCH = 17
   LCM_CAUSE_SWVER_NAVAIL = 18
   LCM_CAUSE_DLGFAIL_DUETO_RECOVERY = 19
   LCM_CAUSE_INV_ACTION = 20
   LCM_CAUSE_LYR_SPECIFIC = 256
   LSO_CAUSE_SAP_BNDDIS = 257
   LSO_CAUSE_SAP_BNDENA = 258
   LSO_CAUSE_SAP_UBNDDIS= 259
   LSO_CAUSE_LI_INITIATED = 260
   LSO_CAUSE_INV_SUCONNID = 261
   LSO_CAUSE_INV_SPCONNID = 262
   LSO_CAUSE_INV_ENTID  = 263
   LSO_CAUSE_TPT_FAIL   = 264
   LSO_ENT_NONE  = 0
   LSO_ENT_B2BUA = 0
   LSO_ENT_UA = 1
   LSO_ENT_NS = 2
   LSO_STS_UA = 6
   LSO_STS_NS = 7
   LSO_PAR_NONE = 1
   LSO_PAR_MEM = 2
   LSO_PAR_SAP = 3
   LSO_PAR_ENT = 4
   LSO_PAR_CONNID = 5
   LSO_PAR_TPTADDR = 6
   LSO_PAR_STATUS = 7
   LSO_PAR_REASON = 8
   LSO_PAR_CHOICE = 9
   LSO_PAR_TPTSRV = 10
   LSO_PAR_REG = 11
   LSO_PAR_TSAP = 12
   LSO_PAR_SSAP = 13
   LSO_PAR_TPTPARM = 14
   LSO_PAR_VAL = 15
   LSO_ORIGINATOR = 1
   LSO_RECEIVER = 2
   LSO_ACNT_NONE = 0
   LSO_ACNT_MEDIA_SDP_DECODED = 2
   LSO_ACNT_EST = 1
   LSO_TSAP_TYPE_TUCL = 1
   LSO_TSAP_TYPE_SCTP = 2
   LSO_TSAP_TYPE_DTUCL = 3
   LSO_TSAP_TYPE_DSCTP = 4
   LSO_DFLT_PRX_NONE = 0
   LSO_DFLT_PRX_TPT_ADDR = 1
   LSO_DFLT_PRX_DOMAIN_NAME = 2
   LSO_REASON_INVALID_ENTID = 260
   LSO_REASON_INV_TPTSRV    = 259
   INVALID_ACTION = 201
   ENTSO                   =  0x99
   ENTSG                   =  0x5d

   ENTAQ                   =  0xc9
   ENTHR                   =  0x78
   ENTGT                   =  0x6d
   ENTSB                   =  0x88
   ENTSV                   =  0xa1

   ENTAB                   =  0xca
   ENTHI                   =  0x75
   ENTHR                   =  0x78
   ENTRR                   =  0xa6
   ENTRL                   =  0x8b
   ENTTC                   =  0x12
   ENTSM                   =  0x0e
   ENTLR                   =  0x33
   ENTLX                   =  0xce
   ENTXU                   =  0xcf

   TC_IPHC      = 0
   TC_ROHC      = 1
   TC_IPHC_ROHC = 2
   TC_HC_INVALID=10
   
   TCP = 6
   UDP = 17
   ESP = 50
   IPV4 = 4
   IPV6 = 41
   IPV6F = 44   
   IPV6_FRAG = 44
   IPV6_RTE = 43
   IPV6_HOP = 0        
   IPV6_DST = 60
   RTP   = 60
   GRE   =  47
   AH    =  51
   CM_COMP_ROHC_NOCOMP_PROF=0
   CM_COMP_ROHC_RTP_PROF=1
   CM_COMP_ROHC_UDP_PROF=2
   CM_COMP_ROHC_ESP_PROF=3
   CM_COMP_ROHC_PROF0=0
   CM_COMP_ROHC_PROF1=1
   CM_COMP_ROHC_PROF2=2
   CM_COMP_ROHC_PROF3=3
   CM_COMP_ROHC_PROF_ALL=4
   
   IR_PKT = 253
   IR_DYN_PKT = 248
   R0_PKT = 0
   U0_PKT = 0
   R0_CRC_PKT = 1
   R1_PKT = 2
   R1_ID_PKT = 2
   R1_TS_PKT = 2
   UO1_PKT = 2
   UO1_ID_PKT = 2
   UO1_TS_PKT = 2
   UOR2_PKT = 6
   UOR2_ID_PKT = 6
   UOR2_TS_PKT = 6
   NO_COMP_NORM_PKT = 45
   NO_COMP_IR_PKT = 20
  
   ROHC_F2_ACK = 1
   ROHC_F1_ACK = 2
   ROHC_NACK   = 3
   ROHC_SNACK  = 4
 
   LSO_DNS_A_CACHE = 1
   LSO_DNS_SRV_CACHE = 2
   LSO_MCAST_CACHE  = 3
   LSO_LOCSRV_CACHE = 4
   LSO_DNS_NAPTR_CACHE = 5
   SATRC = 4

   SOT_ET_INVALID    = 0
   SOT_ET_INVITE     = 1
   SOT_ET_ACK        = 2
   SOT_ET_OPTIONS    = 3
   SOT_ET_BYE        = 4
   SOT_ET_CANCEL     = 5
   SOT_ET_REGISTER   = 6
   SOT_ET_INFO       = 7
   SOT_ET_PRECON_MET = 8
   SOT_ET_PRACK      = 9
   SOT_ET_REFER      = 10
   SOT_ET_SUBSCRIBE  = 11
   SOT_ET_NOTIFY     = 12
   SOT_ET_MESSAGE    = 13
   SOT_ET_UPDATE     = 14
   SOT_ET_PUBLISH     = 15 
   SOT_ET_PROGRESS   = 16 
   SOT_ET_TRYING     = 17 
   SOT_ET_RINGING    = 18
   SOT_ET_FORWARDING = 19
   SOT_ET_QUEUED     = 20
   SOT_ET_REDIRECT   = 21
   SOT_ET_ERROR      = 22
   SOT_ET_OK         = 23
   SOT_ET_REG_TMO    = 24
   SOT_ET_LRQ        = 25
   SOT_ET_MODIFY     = 26
   SOT_ET_STATUS     = 27
   SOT_ET_UNKNOWN    = 28
   SOT_ET_REGISTER_LOC          = 29
   SOT_ET_SIP_ERROR             = 30
   SOT_ET_INT_REFRESHTMR_EXPD   = 31
   SOT_ET_INT_SESSTIMER_EXPD    = 32
   SOT_ET_SUBSC_TMO             = 33
   SOT_ET_AUDIT                 = 34
   SOT_ET_REFRESH               = 35
   SOT_ET_LOCAL_REL             = 36
   SOT_ET_MAXIMUM               = 37
   SOT_ERR_AUDIT_IN_PROGRESS    = 68


   SO_SIPMESSAGE_NONE      = 0
   SO_SIPMESSAGE_REQUEST   = 1
   SO_SIPMESSAGE_RESPONSE  = 2
   SO_SIPMESSAGE_ERROR     = 3     
   SO_SIPMESSAGE_AUDIT     = 4     
   SO_SIPMESSAGE_REFRESH   = 5

   SOT_AUDIT_CALL          = 1
   SOT_AUDIT_SSAP          = 2


   LSO_PRX_STATELESS       = 1
   LSO_PRX_CALL_STATEFUL   = 2
   LSO_PRX_TRANS_STATEFUL  = 3
   LSO_NO_REGISTER         = 0
   LSO_STAND_ALONE         = 1
   LSO_COLOCATED           = 2
   LSO_FRK_SEQUENTIAL      = 0  
   LSO_FRK_PARALLEL        = 1  

   LSO_REASON_INV_CALLHDL = 263
   LSO_REASON_NO_ENDPS = 264
   LSO_REASON_INV_ENDP = 265
   TRUE = 1
   FALSE = 0
   DTX = 2
#cm_xta_py_py_001.main_50 : Added diameter interface macros.
   DBP = 0
   DBPAPP=1
   CXDX = 2
   SH   = 3
   RORF = 4
   RF   = 4
   RO   = 5
   GQ   = 6
   GX   = 7
   GY   = 14
   GZ   = 15
   GXC  = 16
   S6B  = 17
   SWX  = 18
   SWM  = 19
   E4   = 8
   RX   = 9
   APP  = 10
   E2  = 11
   RQ   = 12
   S6A   = 13

   SCT_OK = 0
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   SCT_ASSOC_IND_NONE = 0
   SCT_ASSOC_IND_INIT = 1
   SCT_ASSOC_IND_COOKIE = 2
   ZEROSTS = 0
   NOZEROSTS = 1
   SCT_STATUS_COMM_UP = 1
   SCT_STATUS_NET_UP = 2
   SCT_STATUS_NET_DOWN = 3
   SCT_STATUS_COMM_LOST = 9
   # Iuh 2.1 release
   SCT_STATUS_SND_FAIL  = 4
   SCT_PARTIAL_DAT=4
   LSO_EVENT_HIT_BNDCFM = 257
   LSO_EVENT_HIT_CONCFM = 258
   LSO_EVENT_HIT_CONIND = 259
   LSO_EVENT_HIT_DATIND = 260
   LSO_EVENT_HIT_DISCIND = 261
   LSO_EVENT_HIT_DISCCFM    = 262
   LSO_EVENT_HIT_UDATIND   = 263
   LSO_EVENT_SOT_BNDREQ     = 264
   LSO_EVENT_SOT_UBNDREQ   = 265
   LSO_EVENT_SOT_CONREQ    = 266
   LSO_EVENT_SOT_CONRSP    = 267
   LSO_EVENT_SOT_CIMREQ    = 268
   LSO_EVENT_SOT_CIMRSP     = 269
   LSO_EVENT_SOT_CNSTREQ   = 270
   LSO_EVENT_SOT_RELREQ    = 271
   LSO_EVENT_SOT_RELRSP    = 272
   LSO_EVENT_SOT_MODREQ    = 273
   LSO_EVENT_SOT_MODRSP    = 274
   LSO_EVENT_SOT_ACKREQ  = 275
   LSO_EVENT_SOT_CANCELREQ= 276 
   LSO_EVENT_SOT_AUDITREQ = 277
   LSO_EVENT_SOT_CAMREQ   = 278
   LSO_EVENT_SOT_CAMRSP   = 279
   LSO_EVENT_TPTSRV_ENA = 280
   LSO_EVENT_ENT_ENA    = 281
   LSO_EVENT_ENT_DIS = 282
   LSO_EVENT_TPTSRV_DIS = 283
   LSO_EVENT_UBND_OK = 284
   LSO_EVENT_RES_CONG_STRT = 285
   LSO_EVENT_RES_CONG_STOP = 286
   LSO_EVENT_RES_PRX_SWITCH = 287
   LSO_EVENT_REG_WARN_ON = 288
   LSO_EVENT_REG_WARN_OFF = 289
   LSO_EVENT_REG_FULL = 290
   LSO_EVENT_ENDP_ENA = 291
   LSO_EVENT_ENDP_CLOSE = 292
   LSO_EVENT_SCT_BNDCFM = 293
   LSO_EVENT_SCT_ENDPOPENCFM = 294
   LSO_EVENT_SCT_TERMIND = 295
   LSO_EVENT_SCT_ASSOCCFM = 296
   LSO_EVENT_SCT_ASSOCIND = 297
   LSO_EVENT_SCT_DATIND = 298
   LSO_EVENT_SCT_STACFM = 299
   LSO_EVENT_SCT_STAIND = 300
   LSO_EVENT_SCT_HBEATCFM = 301
   LSO_EVENT_SCT_TERMCFM = 302
   LSO_EVENT_SCT_SETPRICFM = 303
   LSO_EVENT_SCT_FLCIND = 304
   LSO_EVENT_SCT_ENDPCLOSECFM = 305
   LSO_EVENT_SOT_PROXYREQ = 306
   LSO_EVENT_SOT_PROXYRSP = 307
   LSO_EVENT_SOT_TRANSREQ = 308
   LSO_EVENT_SOT_TRANSRSP = 309
   LSO_EVENT_HIT_FLCIND   = 310


   LSO_TPTPROT_UDP           =  1  
   LSO_TPTPROT_TCP           =  2  
   LSO_TPTPROT_SCTP          =  3  
   LSO_TPTPROT_TLS_TCP       =  4  
   LSO_TPTPROT_UDP_PRIOR     =  5  


   EGT_GTPC_MSG_ECHO_REQ     =  1
   EGT_GTPC_MSG_ECHO_RSP     =  2
   EGT_GTPC_MSG_VER_N_SUPP_IND =  3
   EGT_GTPC_MSG_INVALID      =  05
#eGTP-C 9.3 Spec 
   EGT_GTPC_MSG_CS_REQ          = 32
   EGT_GTPC_MSG_CS_RSP          = 33
   EGT_GTPC_MSG_MB_REQ          = 34
   EGT_GTPC_MSG_MB_RSP          = 35
   EGT_GTPC_MSG_DS_REQ          = 36
   EGT_GTPC_MSG_DS_RSP          = 37
   EGT_GTPC_MSG_CN_REQ          = 38
   EGT_GTPC_MSG_CN_RSP          = 39
   EGT_GTPC_MSG_MB_CMND          = 64
   EGT_GTPC_MSG_MBFAIL_IND       = 65
   EGT_GTPC_MSG_DB_CMND          = 66
   EGT_GTPC_MSG_DB_FAIL_IN       = 67
   EGT_GTPC_MSG_BR_CMND          = 68
   EGT_GTPC_MSG_BR_FAIL_IND      = 69
   EGT_GTPC_MSG_DD_NOTFN_FAIL_IND = 70
   EGT_GTPC_MSG_TRC_SESS_ACTVN    = 71
   EGT_GTPC_MSG_TRC_SESS_DEACTVN  = 72
   EGT_GTPC_MSG_STOP_PAGING_IND   = 73
   EGT_GTPC_MSG_CB_REQ          = 95
   EGT_GTPC_MSG_CB_RSP           = 96
   EGT_GTPC_MSG_UB_REQ          = 97
   EGT_GTPC_MSG_UB_RSP          = 98
   EGT_GTPC_MSG_DB_REQ          = 99 
   EGT_GTPC_MSG_DB_RSP          = 100
   EGT_GTPC_MSG_DPDN_CON_SET_REQ  = 101
   EGT_GTPC_MSG_DPDN_CON_SET_RSP = 102
   EGT_GTPC_MSG_ID_REQ          = 128
   
   EGT_GTPC_MSG_ID_RSP    = 129
   EGT_GTPC_MSG_CNTXT_REQ = 130
   EGT_GTPC_MSG_CNTXT_RSP = 131
   EGT_GTPC_MSG_CNTXT_ACK = 132
   EGT_GTPC_MSG_FR_REQ = 133
   EGT_GTPC_MSG_FR_RSP  = 134
   EGT_GTPC_MSG_FR_COMP_NOTFN  = 135
   EGT_GTPC_MSG_FR_COMP_ACK  = 136
   EGT_GTPC_MSG_FWD_ACC_CNTXT_NOTFN  = 137
   EGT_GTPC_MSG_FWD_ACC_CNTXT_ACK = 138
   EGT_GTPC_MSG_RC_REQ = 139
   EGT_GTPC_MSG_RC_RSP = 140
   EGT_GTPC_MSG_CFG_TRAN_TUNN = 141
   EGT_GTPC_MSG_DTCH_NOTFN      = 149
   EGT_GTPC_MSG_DTCH_ACK      = 150
   EGT_GTPC_MSG_CS_PGNG_IND    = 151
   EGT_GTPC_MSG_RAN_INFO_RELAY  = 152
   EGT_GTPC_MSG_ALRT_MME_NOTFN  = 153
   EGT_GTPC_MSG_ALRT_MME_ACK    = 154
   EGT_GTPC_MSG_UE_ACT_NOTFN   = 155 
   EGT_GTPC_MSG_UE_ACT_ACK   = 156
   EGT_GTPC_MSG_CF_TUNN_REQ     = 160
   EGT_GTPC_MSG_CF_TUNN_RSP    = 161
   EGT_GTPC_MSG_SSPND_NOTFN   = 162
   EGT_GTPC_MSG_SSPND_ACK   = 163
   EGT_GTPC_MSG_RSME_NOTFN  = 164
   EGT_GTPC_MSG_RSME_ACK   = 165
   EGT_GTPC_MSG_CIDF_TUNN_REQ  = 166

   EGT_GTPC_MSG_CIDF_TUNN_RSP = 167
   EGT_GTPC_MSG_DIDF_TUNN_REQ  = 168
   EGT_GTPC_MSG_DIDF_TUNN_RSP  = 169 
   EGT_GTPC_MSG_RAB_REQ         = 170
   EGT_GTPC_MSG_RAB_RSP         = 171
   EGT_GTPC_MSG_DWN_DATA_NOTFN  = 176
   EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK  = 177
   EGT_GTPC_MSG_UPD_PDN_CON_SET_REQ = 200
   EGT_GTPC_MSG_UPD_PDN_CON_SET_RSP  = 201
   EGT_GTPC_MSG_MBMS_SESS_START_REQ = 231
   EGT_GTPC_MSG_MBMS_SESS_START_RSP   = 232
   EGT_GTPC_MSG_MBMS_SESS_UPD_REQ  = 233
   EGT_GTPC_MSG_MBMS_SESS_UPD_RSP    = 234
   EGT_GTPC_MSG_MBMS_SESS_STOP_REQ = 235
   EGT_GTPC_MSG_MBMS_SESS_STOP_RSP = 236

#cm_xta_py_py_001.main_56 - S2B and S2A 
   EGT_GTP_INT_S2A           =   11
   EGT_GTP_INT_S2B           =   10
   EGT_GTP_INT_SN            =   9
   EGT_GTP_INT_SM            =   8
   EGT_GTP_INT_S16           =   6
   EGT_GTP_INT_S10           =   5
   EGT_GTP_INT_S4            =   4
   EGT_GTP_INT_S3            =   3
   EGT_GTP_INT_S11           =   2
   EGT_GTP_INT_S5_S8         =   1
   EGT_GTP_INT_UNKNWN        =   0

   EGT_INT_S5_S8_SGW_GTP_C   =  6
   EGT_INT_S5_S8_PGW_GTP_C   =  7
   EGT_INT_S11_MME_GTP_C     = 10
   EGT_INT_S11_SGW_GTP_C     = 11
   EGT_INT_S10_MME_GTP_C     = 12
   EGT_INT_S3_MME_GTP_C      = 13
   EGT_INT_S3_SGSN_GTP_C      = 14
   EGT_INT_S4_SGSN_GTP_U      = 15
   EGT_INT_S4_SGW_GTP_U       = 16
   EGT_INT_S4_SGSN_GTP_C      = 17
   EGT_INT_S16_SGSN_GTP_C    =  18
   EGT_INT_SM_MME_GTP_C = 24
   EGT_INT_SN_SGSN_GTP_C = 25
   EGT_INT_SM_MBMSGW_GTP_C = 26
   EGT_INT_SN_MBMSGW_GTP_C = 27

#cm_xta_py_py_001.main_56 - S2B and S2A 
   EGT_INT_SGW_UL_FWD         = 28
   EGT_INT_SN_SGSN_GTP_U      = 29

   EGT_INT_S2B_EPDG_GTP_C =30
   EGT_INT_S2B_EPDG_GTP_U =31
   EGT_INT_S2B_PGW_GTP_C = 32
   EGT_INT_S2B_PGW_GTP_U = 33


   EGT_INT_S2A_TWAN_GTP_U =34
   EGT_INT_S2A_TWAN_GTP_C =35
   EGT_INT_S2A_PGW_GTP_C = 36
   EGT_INT_S2A_PGW_GTP_U  =37
   
   EGT_INT_S1_U_ENB_GTP_U    =  0
   EGT_INT_X2_DL_ENB_GTP_U   =  19
   EGT_INT_S1_U_SGW_GTP_U    =  1
   EGT_INT_S5_S8_SGW_GTP_U   =  4
   EGT_INT_X2_UL_ENB_GTP_U   =  20 

   LEG_EGTP_C                =  0
   LEG_EGTP_U                =  1

   EGT_SUCCESS               =  0
   EGT_ERR_MSG_UNABLE_TO_COMPLY  =  9
   EGT_GTP_INT_UNKNWN        =  0
   EGT_INV_INTF_TYPE         =  4
   #cm_xta_py_py_001.main_56 : adding  Error indication defnitions
   EGT_ERR_INV_TUNN_NET_EVNT = 5
   EGT_ERR_INV_TUNN_USR_EVNT = 6
   EGT_ERR_MSG_INV_INT       = 7
   
   EGT_ERR_MSG_NO_MATCH      = 8
   EGT_ERR_INV_VERSION       =  12
   EGT_ERR_INV_MSG_HDR       =  13 
   EGT_ERR_INV_MSG_TYPE      =  14
   EGT_ERR_IE_UNKNOWN        =  15
   EGT_ERR_IE_INV_LEN        =  16
   EGT_ERR_MSG_INV_LEN       =  11
   EGT_ERR_MISSING_MAND_IE   =   10
   EG_ERR_MEM_ALLOC_FAILED   =  19
   EGT_ERR_INV_IE_VAL        =  18
   EGT_ERR_MAND_IE_INCOR     =  19
   EG_INV_DATA_TYPE          =  20
   EGT_ERR_INV_IE_TYPE       =  17
   EGT_ERR_INV_SAP           =  24
   EGT_ERR_INV_TEID          =  20
   EGT_ERR_NO_SEQ            =  32
   EGT_ERR_MAX_TDPU_SIZE_EXCED = 33
   EGT_ERR_INV_DATA_TYPE        =34
   EGT_ERR_MSG_NOT_ALLWD     =  37
   EGT_ERR_END_MARKER_RCVD   =  44
   EGT_ERR_INV_TEID_RCVD     =  42
   EGT_ERR_INV_DST_IP        =  36
   EGT_ERR_DST_MULT_IP       =  38
   EGT_ERR_INV_SRC_IP        =  39
   EGT_ERR_INV_SRC_PORT      =  40
   EGT_ERR_PENDING_CNTRL_OP =  43
   # cm_xta_py_py_001.main_53 : parm for indicating max retry error
   EGT_ERR_MAX_RETRY_EXHAUSTED =  46
  
   # cm_xta_py_py_001.main_53 : parm for indicating invalid Seq Num
   EGT_ERR_INV_SEQ_NUM         = 47

   # cm_xta_py_py_001.main_57 : parm for indicating piggyback error
   EGT_ERR_INV_PIGGY_MSG      = 48

   EGT_TMGMT_REQTYPE_ADD     =  1
   EGT_TMGMT_REQTYPE_DEL     =  2
   EGT_TMGMT_REQTYPE_MOD     =  3
   EGT_TMGMT_REQTYPE_STOP_QING  =  4
   EGT_TMGMT_REQTYPE_DEL_ALL  =  5
   EGT_TMGMT_REQTYPE_REORD_ENA  =  6
   EGT_TMGMT_REQTYPE_REORD_DIS  =  7
   EGT_TMGMT_INV_ACTION   = 8
   EGT_GTPU_CAUSE_INV_SRC_IP         =  94
   EGT_GTPU_CAUSE_INV_PORT           =  95
   EGT_GTPU_CAUSE_INV_DST_IP         =  96
   EGT_GTPU_CAUSE_NO_RES_AVAIL       =  97
   EGT_GTPU_CAUSE_INV_TEID           =  98
   EGT_GTPU_CAUSE_REORD_DIS          =  99
   EGT_GTPU_CAUSE_INV_ACTION         =  100
   EGT_GTPU_CAUSE_DST_MULT_IP        =  101
   EGT_EGTPU_CAUSE_PENDING_CNTRL_OP  =  102
   EGT_EGTPU_CAUSE_PROC_FAIL         =  103
   EGT_EGTPU_REASON_DEST_UNREACH     =  3
   EGT_ERR_MSG_MISS_MAND_IE         =  10
   EGU_RECOVERY_IETYPE         =  14
   CM_TPTADDR_IPV4 =  4
   CM_TPTADDR_IPV6 =  6
   EG_REORDER_TYPE_1 = 1
   EG_REORDER_TYPE_2 = 2

#cm_xta_py_py_001.main_50 : Added diameter AVP Type macros.
   AQ_OCTET_STRING              = 1
   AQ_SIGNED_32                 = 2
   AQ_UNSIGNED_64               = 5
   AQ_UNSIGNED_32               = 4
   AQ_ENUMERATED                = 2 
   LAQ_MAX_NUM_OF_AVP_PROP      =   25      
   LAQ_MAX_NUM_OF_AVPS          =  100      
   LAQ_MAX_NUM_OF_HOST_IDS      =   10      
   LAQ_MAX_NUM_OF_REALMS        =    2      
   LAQ_MAX_NUM_OF_PEERS         =   10      
   LAQ_MAX_NUM_OF_CMDS          =   20      
   LAQ_MAX_OPT_AVP              =   10
   LAQ_MAX_HOST_TO_IP           =   10
#cm_xta_py_py_001.main_50 : Added AVP value for proxy agent in DLSDK.
   IP_CONN_ON                   =   1
   LAQ_MAX_SUPP_VEN_ID          =    5      
   LAQ_MAX_VEN_SPEC_APPID       =    5   
   LAQ_MAX_INBAND_SEC           =    2      
   LAQ_MAX_APP_HOST_MAP         =   10   
   LAQ_MAX_APP_ID               =   10      
   LAQ_MIN_LSAPS                =    0      
   LAQ_MAX_LSAPS                =   10   
   LAQ_MIN_USAPS                =    0      
   LAQ_MAX_USAPS                =   10   
   LAQ_MIN_PEERS                =    1      
   LAQ_MAX_PEERS                =   10      
   LAQ_MIN_REALMS               =    1      
   LAQ_MAX_REALMS               =   10      
   LAQ_MIN_WRKTHRDS             =    0   
   LAQ_MAX_WRKTHRDS             =    5      
   LAQ_MIN_BURST_CNT            =    0   
   LAQ_MAX_BURST_CNT            =  100
   LAQ_MIN_TMR_RES              =    1
   EVTLAQCFGREQ                 =    1
   EVTLAQCFGCFM                 =    2
   EVTLAQCNTRLREQ               =    3
   EVTLAQCNTRLCFM               =    4
   EVTLAQSTAREQ                 =    5
   EVTLAQSTACFM                 =    6
   EVTLAQSTSREQ                 =    7
   EVTLAQSTSCFM                 =    8
   EVTLAQSTAIND                 =    9
   EVTLAQTRCIND                 =   10
   EVTLAQPRBREQ                 =   11
   EVTLAQPRBCFM                 =   12
   LAQ_SAP_CFG                  =    1
   LAQ_SAP_BND                  =    2
   LAQ_SAP_BINDING              =    3
   LAQ_SAP_UBND                 =    4
   LAQ_SAP_BND_ENB              =    5
   LAQ_SAP_WAIT_BNDCFM          =    6
   LAQ_SEL_LC                   =    0
   LAQ_SEL_LWLC                 =    1
   LAQ_SEL_TC_AB                    =    1   
   LAQ_SEL_TC_HIT                   =    1
   LAQ_SEL_TC_SCT                   =    2
   LAQ_SEL_TC_SM                    =    1
   LAQ_NRM_TERMINATION              =    0
   LAQ_SHUTDOWN                     =    1
   LAQ_PWR_UP                       =    2
   LAQ_DONT_CARE                    =    3
   LAQIFVER                         =0x0100
   LAQ_TRANS_TYPE_TCP_TLS           =    1   
   LAQ_TRANS_TYPE_TCP_IPSEC         =    2
   LAQ_TRANS_TYPE_TCP_BOTH          =    3
   LAQ_TRANS_TYPE_SCTP_IPSEC        =    4
   LAQ_TRANS_TYPE_SCTP_TLS          =    5
   LAQ_TRANS_TYPE_SCTP_BOTH         =    6
   LAQ_MIN_TCP_PORT_NUM             = 3000
   LAQ_MAX_TCP_PORT_NUM             =65550
   LAQ_MIN_SCTP_PORT_NUM            = 3000
   LAQ_MAX_SCTP_PORT_NUM            =65550
   STAQGEN                          =    1
   STAQPROT                         =    2
   STAQUSAP                         =    3
   STAQLSAP                         =    4
   STAQREALM                        =    5
   STAQPEER                         =    6
   STAQAVP                          =    7
   STAQDM                           =    8
   STAQALLREALM                     =    9
   STAQALLPEER                      =   10
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   AQ_ALL_CONNS                     =    0
   STAQSID                          =   11
   STAQPRAPP                      	=   13
   STAQPRALLAPP                    	=   14

   STJCGEN                          =   74
   STJCRSET                         =   75
   STJCSID                          =   76
   STJCGENCFG                       =   77
   LAQ_EVENT_RESET_FAIL             =(LCM_EVENT_LYR_SPECIFIC+ 1)
   LAQ_EVENT_DMEM_ALLOC_PASS        =(LCM_EVENT_LYR_SPECIFIC+ 2)
   LAQ_EVENT_AUDIT_FIN              =(LCM_EVENT_LYR_SPECIFIC+ 3)
   LAQ_EVENT_CONN_OK                =    (LCM_EVENT_LYR_SPECIFIC + 4)
   LAQ_EVENT_CONN_FAIL              =    (LCM_EVENT_LYR_SPECIFIC + 5)
   LAQ_EVENT_MAX_CONN_RETRY         =    (LCM_EVENT_LYR_SPECIFIC + 6)
   LAQ_EVENT_FAILOVER_INIT          =    (LCM_EVENT_LYR_SPECIFIC + 7)
   LAQ_EVENT_PEER_DOWN              =    (LCM_EVENT_LYR_SPECIFIC + 8)
   LAQ_EVENT_PEER_UP                =    (LCM_EVENT_LYR_SPECIFIC + 9)
   LAQ_EVENT_PEER_DOWN_PERM         =    (LCM_EVENT_LYR_SPECIFIC + 10)
   LAQ_EVENT_NO_ALT_PEER_FOUND      =    (LCM_EVENT_LYR_SPECIFIC + 11)
   LAQ_EVENT_PEER_NOT_INSERTED      =    (LCM_EVENT_LYR_SPECIFIC + 12)
   LAQ_EVENT_REALM_NOT_INSERTED     =   (LCM_EVENT_LYR_SPECIFIC + 13)
   LAQ_EVENT_PEER_DELETED           =   (LCM_EVENT_LYR_SPECIFIC + 14)
   LAQ_EVENT_UI_SAP_UBND_SUCC       =   (LCM_EVENT_LYR_SPECIFIC + 15)
   LAQ_EVENT_OPEN_SERV_FAIL         =   (LCM_EVENT_LYR_SPECIFIC + 16)
   LAQ_EVENT_LI_BND_CFM             =   (LCM_EVENT_LYR_SPECIFIC + 17)
   LAQ_EVENT_LI_HIT_CON_CFM         =   (LCM_EVENT_LYR_SPECIFIC + 18)
   LAQ_EVENT_LI_HIT_CON_IND         =   (LCM_EVENT_LYR_SPECIFIC + 19)
   LAQ_EVENT_LI_SCT_ENDP_OPEN_CFM   =   (LCM_EVENT_LYR_SPECIFIC + 20)
   LAQ_EVENT_LI_SCT_ENDP_CLOSE_CFM   =   (LCM_EVENT_LYR_SPECIFIC + 21)
   LAQ_EVENT_LI_SCT_ENDP_ASSOC_IND   =   (LCM_EVENT_LYR_SPECIFIC + 22)
   LAQ_EVENT_LI_SCT_ENDP_ASSOC_CFM   =   (LCM_EVENT_LYR_SPECIFIC + 23)
   LAQ_EVENT_LI_HIT_DAT_IND         =   (LCM_EVENT_LYR_SPECIFIC + 24)
   LAQ_EVENT_LI_SCT_DAT_IND         =   (LCM_EVENT_LYR_SPECIFIC + 25)
   LAQ_EVENT_LI_HIT_DISC_IND        =   (LCM_EVENT_LYR_SPECIFIC + 26)
   LAQ_EVENT_LI_SCT_TERM_IND        =   (LCM_EVENT_LYR_SPECIFIC + 27)
   LAQ_EVENT_LI_SCT_TERM_CFM        =   (LCM_EVENT_LYR_SPECIFIC + 28)
   LAQ_EVENT_LI_SCT_SET_PRI_CFM     =   (LCM_EVENT_LYR_SPECIFIC + 29)
   LAQ_EVENT_LI_SCT_HBEAT_CFM       =   (LCM_EVENT_LYR_SPECIFIC + 30)
   LAQ_EVENT_LI_SCT_STA_CFM         =   (LCM_EVENT_LYR_SPECIFIC + 31)
   LAQ_EVENT_LI_SCT_STA_IND         =   (LCM_EVENT_LYR_SPECIFIC + 32)
   LAQ_EVENT_LI_HIT_FLC_IND         =   (LCM_EVENT_LYR_SPECIFIC + 33)
   LAQ_EVENT_LI_SCT_FLC_IND         =   (LCM_EVENT_LYR_SPECIFIC + 34)
   LAQ_EVENT_OPEN_SERV_UP           =   (LCM_EVENT_LYR_SPECIFIC + 35)
   LAQ_EVENT_PEER_INSERTED              =   (LCM_EVENT_LYR_SPECIFIC + 36)
   LAQ_EVENT_RECONN_TIMEOUT             =   (LCM_EVENT_LYR_SPECIFIC + 37)
   LAQ_USTA_DGNVAL_NONE             =    1
   LAQ_USTA_DGNVAL_MEM              =    2
   LAQ_USTA_DGNVAL_SAPID            =    3
   LAQ_USTA_DGNVAL_APPID            =    4
   LAQ_USTA_DGNVAL_PEER             =    5
   LAQ_USTA_DGNVAL_REALM            =    6
   LAQ_USTA_DGNVAL_AVPCODE          =    7
   LAQ_USTA_MAX_DGNVAL              =  256
   LAQ_START                        =  100
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   LAQ_DEL_PEER                     =  101
   LAQ_STOP                         =  102
   LAQ_STOP_IMM                     =  103
   SAUSTA                       =    3
   SADBG                        =    5
   SAELMNT                          =     1
   LAQ_SAALL                        =    4
   LAQ_SPEC                         =    5
   LAQ_MAX_TRC_LEN                  =  256
   LAQ_TRC_PNODE                    =    1
   LAQ_TRC_LSAP_IN                  =    2
   LAQ_TRC_LSAP_OUT                 =    4
   LAQ_TRC_PNODE_IN                 =    8
   LAQ_TRC_PNODE_OUT                =   16
   LAQ_CAUSE_N_RETRY                =(LCM_CAUSE_LYR_SPECIFIC+ 1)
   LAQ_CAUSE_UNKNOWN_OPT_AVP        =(LCM_CAUSE_LYR_SPECIFIC+ 2)
   LAQ_CAUSE_NO_PEER_INOPEN_ST      =(LCM_CAUSE_LYR_SPECIFIC+ 3)
   LAQ_CAUSE_INV_SRV_STATE          =(LCM_CAUSE_LYR_SPECIFIC+ 4)
   LAQ_CAUSE_NO_COMM_APP            =(LCM_CAUSE_LYR_SPECIFIC+ 5)
   LAQ_CAUSE_NO_COMM_SEC            =(LCM_CAUSE_LYR_SPECIFIC+ 6)
   LAQ_CAUSE_CER_EXCHGD             =(LCM_CAUSE_LYR_SPECIFIC+ 7)
   LAQ_CAUSE_DPR_SENT               =(LCM_CAUSE_LYR_SPECIFIC+ 8)
   LAQ_CAUSE_DPR_RCVD               =(LCM_CAUSE_LYR_SPECIFIC+ 9)
   LAQ_CAUSE_DW_TIMEOUT             =(LCM_CAUSE_LYR_SPECIFIC+ 10)
   LAQ_CAUSE_TERM_IND               =(LCM_CAUSE_LYR_SPECIFIC+ 11)
   LAQ_CAUSE_TCP_IPSEC_SRV_OPEN_FAIL=(LCM_CAUSE_LYR_SPECIFIC+ 12)
   LAQ_CAUSE_TCP_TLS_SRV_OPEN_FAIL   =(LCM_CAUSE_LYR_SPECIFIC+ 13)
   LAQ_CAUSE_SCTP_IPSEC_SRV_OPEN_FAIL=(LCM_CAUSE_LYR_SPECIFIC+ 14)
   LAQ_CAUSE_DEC                    =(LCM_CAUSE_LYR_SPECIFIC+ 15)
   LAQ_CAUSE_TCP_IPSEC_SRV_UP       =(LCM_CAUSE_LYR_SPECIFIC+ 16)
   LAQ_CAUSE_TCP_TLS_SRV_UP         =(LCM_CAUSE_LYR_SPECIFIC + 17)
   LAQ_CAUSE_SCTP_IPSEC_SRV_UP      =(LCM_CAUSE_LYR_SPECIFIC+ 18)
   LAQ_CAUSE_TCP_IPSEC_SRV_DISCONNECTED   =(LCM_CAUSE_LYR_SPECIFIC+ 19)
   LAQ_CAUSE_TCP_TLS_SRV_DISCONNECTED   =(LCM_CAUSE_LYR_SPECIFIC + 20)
   LAQ_CAUSE_SCTP_IPSEC_SRV_DISCONNECTED   =(LCM_CAUSE_LYR_SPECIFIC + 21)
   LAQ_CAUSE_TCP_IPSEC_SRV_OPEN_SUCC   =(LCM_CAUSE_LYR_SPECIFIC + 22)
   LAQ_CAUSE_TCP_TLS_SRV_OPEN_SUCC   =(LCM_CAUSE_LYR_SPECIFIC   + 23)
   LAQ_CAUSE_SCTP_IPSEC_SRV_OPEN_SUCC   =(LCM_CAUSE_LYR_SPECIFIC+ 24)
   LAQ_PROT_NONE                    =    0
   LAQ_PROT_TCP                     =    1
   LAQ_PROT_SCTP                    =    2
   LAQ_TSAP_TYPE_TUCL               = 0x01
   LAQ_TSAP_TYPE_SCTP               = 0x02
   LAQ_TSAP_TYPE_DTUCL              = 0x03
   LAQ_TSAP_TYPE_DSCTP              = 0x04
   LAQ_TPTSRV_MAX_SSAP              =   10
   LAQ_HOSTNAME_MAX_SZ              =   50
   LAQ_NO_INBAND_SEC                =    0
   LAQ_SEC_TLS                      =    1
   LAQ_SEC_IPSEC                    =    2
   LAQ_SEC_BOTH                     =    3
   LAQ_MAX_CONN_RETRY_CNT           =    3
   LAQ_PEER_STATIC                  =    1
   LAQ_PEER_DYNAMIC                 =    2
   LAQ_PEER_UNKNOWN                 =    3
   LAQ_PEER_DSC_NONE                =    0
   LAQ_PEER_DSC_SLP                 =    1
   LAQ_PEER_DSC_NAPTR               =    2
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   LAQ_PEER_PRIMARY                 =    1
   LAQ_PEER_SECONDARY               =    2
   LAQ_ACTION_LOCAL                 =    1
   LAQ_ACTION_RELAY                 =    2
   LAQ_ACTION_PROXY                 =    3
   LAQ_ACTION_REDIRECT              =    4
   LAQ_INCOMING_CONN_ACCEPT         =    1
   LAQ_INCOMING_CONN_DENY           =    2
   LAQ_REASON_PROTCFG_NOT_DONE      =(LCM_REASON_LYR_SPECIFIC+ 1)
   LAQ_REASON_INVALID_DOMAIN        =(LCM_REASON_LYR_SPECIFIC+ 2)
   LAQ_REASON_HASHINIT_FAIL         =(LCM_REASON_LYR_SPECIFIC+ 3)
   LAQ_REASON_SAP_ASSOC_EXISTS      =(LCM_REASON_LYR_SPECIFIC+ 4)
   LAQ_REASON_LSAPCFG_NOT_DONE      =(LCM_REASON_LYR_SPECIFIC+ 5)
   LAQ_REASON_INV_PAR_VAL           =(LCM_REASON_LYR_SPECIFIC+ 6)
   LAQ_REASON_INV_NMB_LSAPS         =(LCM_REASON_LYR_SPECIFIC+ 7)
   LAQ_REASON_INV_NMB_USAPS         =(LCM_REASON_LYR_SPECIFIC+ 8)
   LAQ_REASON_INV_NMB_PEERS         =(LCM_REASON_LYR_SPECIFIC+ 9)
   LAQ_REASON_INV_NMB_REALMS        =(LCM_REASON_LYR_SPECIFIC+ 10)
   LAQ_REASON_INV_NMB_WRKTHRDS      =(LCM_REASON_LYR_SPECIFIC+ 11)
   LAQ_REASON_INV_NMB_BURST_CNT     =(LCM_REASON_LYR_SPECIFIC+ 12)
   LAQ_REASON_INV_USAP_CFG          =(LCM_REASON_LYR_SPECIFIC+ 13)
   LAQ_REASON_INV_TCP_PORT          =(LCM_REASON_LYR_SPECIFIC+ 14)
   LAQ_REASON_INV_SCTP_PORT         =(LCM_REASON_LYR_SPECIFIC+ 15)
   LAQ_REASON_INV_TRANS_TYPE        =(LCM_REASON_LYR_SPECIFIC+ 16)
   LAQ_REASON_INV_PROT_TIMERS       =(LCM_REASON_LYR_SPECIFIC+ 17)
   LAQ_REASON_INV_PEER_DSC_TYPE     =(LCM_REASON_LYR_SPECIFIC+ 18)
   LAQ_REASON_INV_SEC_TYPE          =(LCM_REASON_LYR_SPECIFIC+ 19)
   LAQ_REASON_INV_MAX_RETRY_CNT     =(LCM_REASON_LYR_SPECIFIC+ 20)
   LAQ_REASON_INV_LCL_POLICY        =(LCM_REASON_LYR_SPECIFIC+ 21)
   LAQ_REASON_INV_PROT              =(LCM_REASON_LYR_SPECIFIC+ 22)
   LAQ_REASON_INV_NUM_OF_APPS       =(LCM_REASON_LYR_SPECIFIC+ 23)
   LAQ_REASON_INV_LOCAL_ACTION      =(LCM_REASON_LYR_SPECIFIC+ 24)
   LAQ_REASON_INV_APP_ID            =(LCM_REASON_LYR_SPECIFIC+ 25)
   LAQ_REASON_INV_SAP_STATE         =(LCM_REASON_LYR_SPECIFIC+ 26)
   LAQ_REASON_INV_SUBACTION_ITEM    =(LCM_REASON_LYR_SPECIFIC+ 27)
   LAQ_REASON_INV_ACTION_ITEM       =(LCM_REASON_LYR_SPECIFIC+ 28)
   LAQ_REASON_UPD_HOST_CER_FAILED   =(LCM_REASON_LYR_SPECIFIC+ 29)
   LAQ_REASON_MEM_ALLOC_FAILED      =(LCM_REASON_LYR_SPECIFIC+ 30)
   LAQ_REASON_INV_PMQ_SIZE              =(LCM_REASON_LYR_SPECIFIC+ 31)
   LAQ_REASON_INV_HOST_NAME             =(LCM_REASON_LYR_SPECIFIC+ 32)
   LAQ_REASON_INV_REALM_NAME            =(LCM_REASON_LYR_SPECIFIC+ 33)
   LAQ_REASON_INV_PROD_NAME             =(LCM_REASON_LYR_SPECIFIC+ 34)
   LAQ_REASON_INV_PEER_CFG              =(LCM_REASON_LYR_SPECIFIC+ 35)
   LAQ_REASON_INV_NODE_TYPE             =(LCM_REASON_LYR_SPECIFIC+ 36)
   LAQ_REASON_INV_NMB_AVPS              =(LCM_REASON_LYR_SPECIFIC+ 37)
   LAQ_REASON_INV_NMB_CMDS              =(LCM_REASON_LYR_SPECIFIC+ 38)
   LAQ_REASON_USAPCFG_NOT_DONE          =(LCM_REASON_LYR_SPECIFIC+ 39)
   LAQ_REASON_UNKNOWN                   =(LCM_REASON_LYR_SPECIFIC+ 40)
   LAQ_REASON_INV_AVP_CFG               =(LCM_REASON_LYR_SPECIFIC+ 41)
   LAQ_REASON_INV_DM_CFG                =(LCM_REASON_LYR_SPECIFIC+ 42)
   LAQ_REASON_INV_CFG_PARAMS            =(LCM_REASON_LYR_SPECIFIC+ 43)
   LAQ_REASON_INV_REALM_CFG             =(LCM_REASON_LYR_SPECIFIC+ 44)
   LAQ_REASON_INV_APP_HOST_MAP          =(LCM_REASON_LYR_SPECIFIC+ 45)
   LAQ_REASON_INV_PEER_DSC_SERVICE      =(LCM_REASON_LYR_SPECIFIC+ 46)
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   LAQ_REASON_INV_AGENT_CFG             =(LCM_REASON_LYR_SPECIFIC+ 48)
   LAQ_REASON_RECONFIG_FAILED           =(LCM_REASON_LYR_SPECIFIC+ 51)
   LAQ_REASON_INV_AGENT_TYPE            =(LCM_REASON_LYR_SPECIFIC+ 52)
   LAQ_REASON_MAX_REALM_MAP_REACHED     =(LCM_REASON_LYR_SPECIFIC+ 53)
   LAQ_REASON_MAX_APP_REACHED_IN_REALM  =(LCM_REASON_LYR_SPECIFIC+ 54)
   LAQ_REASON_INV_DFLT_REALM            =(LCM_REASON_LYR_SPECIFIC+ 55)
   LAQ_REASON_RESOURCE_IN_USE           =(LCM_REASON_LYR_SPECIFIC+ 56)
   LAQ_REASON_INV_PEER_DESIG            =(LCM_REASON_LYR_SPECIFIC+ 57)
   LAQ_REASON_INV_NMB_OF_CONNS          =(LCM_REASON_LYR_SPECIFIC+ 58)
   LAQ_REASON_PEERS_ACTIVE              =(LCM_REASON_LYR_SPECIFIC + 59)
   LAQ_REASON_SPECIFIED_PEERS_NOT_PRSNT =(LCM_REASON_LYR_SPECIFIC + 60)   

   AQ_AUTH_TYPE                     =    0 
   AQ_ACTT_TYPE                     =    1
   LAQ_ZEROSTS                      =    0
   LAQ_NOZEROSTS                    =    1
   LAQ_PART_NUM_STR_LEN             =   32
   LAQ_DATAGRAM_LIFETIME            =    0
   LAQIFVER                         =0x0100
   LAQ_MAX_STR_SIZE                 =   50   
   ELAQBASE                         =    0
   ELAQXXX                          =(ELAQBASE)

   LAQ_CLIENT                           =    1
   LAQ_SERVER                           =    2
   LAQ_BOTH                             =    3
   CM_IPV4ADDR_TYPE                     =    4   
   CM_IPV6ADDR_TYPE                     =    6   
   CM_NETADDR_IPV4 =    4   
   CM_NETADDR_IPV6 =    6   
   AQU_AVP_FLAG_VENDOR_SPF          = 0x80
   AQU_AVP_FLAG_MANDATORY           = 0x40
   AQU_AVP_FLAG_ENCRYPT             = 0x20
   AQU_PRIM_OK                      =    1
   AQU_PRIM_NOK                     =    2
   AQU_SUCCESS                      =    0
   AQU_ERR_ENC                          =    1         
   AQU_ERR_RSRC                         =    2          
   AQU_ERR_INV_REQUEST                  =    3         
   AQU_ERR_INV_DM_HDR                   =    4        
   AQU_ERR_INV_APP_ID                   =    5       
   AQU_ERR_INV_CMD_FLAGS                =    6      
   AQU_ERR_MISSING_MND_AVP              =    7     
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   AQU_ERR_MISSING_MAND_AVP             =    5005     
   AQ_ERR_NO_COMM_SEC                   =    5017
   AQ_ERR_NO_COMM_APP                   =    5010     
   AQ_ERR_UNABLE_TO_DELIVER             =    3002
   AQ_ERR_REALM_NOT_SERVED              =    3003
   AQ_LOOP_DETECTED                     =    3005
   AQU_ERR_AVP_NOT_ALLOWED              =    5008
   AQU_ERR_AVP_NOT_IN_FXD_POS           =    8    
   AQU_ERR_INV_SAP_STATE                =    9   
   AQU_ERR_INV_MSG                      =   10 
   AQU_ERR_INV_PARAM                    =   11
   AQU_ERR_PEER_UNDER_SUSPECT           =   12
   AQU_ERR_PEER_DOWN                    =   13 
   AQU_ERR_NO_ALT_PEER                  =   14 
   AQU_ERR_UNABLE_TO_DELIVER            =   15
   AQU_ERR_MEM_ALLOC_FAILED             =   16
   AQU_IND_PEER_DELETED                 =   17
   AQU_ERR_PEER_UNDER_SUSPECT_NO_ALT_PEER = 18
   AQU_ERR_INV_ORIG_HOST                =   19
   AQU_ERR_INV_ORIG_REALM               =   20
   AQU_ERR_DUPLICATE_TRANS_ID           =   21
   AQU_ERR_SHUTDOWN_IN_PROGRESS         =   22
   AQU_ERR_TRANS_INV_TTYPE              =   23
   AQU_ERR_TRANS_HDR_MAP                =   24
   AQU_ERR_TRANS_AVP_ATTR_MAP           =   25
   AQU_ERR_PMQ_FULL                     =   26
   AQU_ERR_REQ_TMR_EXPIRED              =   27
   AQU_ERR_INV_HOST_CONN_COMB           =   28
   AQU_ERR_CONN_CONGESTED               =   29
   AQU_ERR_INV_CONN_ID                  =   30

   AQU_ERR_INV_CMD_CODE                 =  5019
   AQU_ERR_UNSUPP_APPID                 =  3007  
   AQU_ERR_INV_CMD_FLAG                 =  3008
   AQU_ERR_INV_AVP_FLAGS                =  3009

   AQU_ERR_AVP_UNSUPP                   =  5001
   AQU_ERR_INV_AVP_VALUE                =  5004
   AQU_ERR_MISSING_MAND_AVP             =  5005
   AQ_ERR_NO_COMM_SEC                   =  5017
   AQ_ERR_NO_COMM_APP                   =  5010     
   AQU_ERR_AVP_NOT_ALLOWED              =  5008
   AQU_ERR_CONTRADICT_AVPS              =  5007
   AQU_ERR_TOO_MANY_AVP_OCC             =  5009
   AQU_ERR_INV_VERSION                  =  5011
   AQU_ERR_UNABLE_TO_COMPLY             =  5012
   AQU_ERR_INV_HDR_BIT                  =  3011
   AQU_ERR_INV_AVP_LEN                  =  5014         
   AQU_ERR_INV_MSG_LEN                  =  5015         

   AQU_ERR_FIXED_AVP_POS                =  5900  
   AQU_ERR_INV_AVP_TYPE                 =  5901 
   AQU_ERR_MND_AVP_DEC_FAIL             =  5902 
   AQU_ERR_HBH_ID_NOTPRSNT              =  5903 

   EVTAQUBNDREQ                     =    1
   EVTAQUBNDCFM                     =    2
   EVTAQUUBNDREQ                    =    3
   EVTAQUDMMSGREQ                   =    4
   EVTAQUDMMSGIND                   =    5
   EVTAQUDMMSGRSP                   =    6
   EVTAQUDMMSGCFM                   =    7
   EVTAQURMVTXREQ                   =    9
   EVTAQURMVTXCFM                   =   10
   EVTAQUPEERDWNIND                 =   11
   EVTAQUPEERUPIND                  =   12
   EVTAQUFLCIND                     =   13
   AQU_SEL_LC                       =    0
   AQU_SEL_TC                       =    1
   AQU_SEL_LWLC                     =    2
   AQU_SAP_BND                      =    0
   AQU_SAP_CFG                      =    1
   AQU_MAX_STR_SIZE                 =  256
   AQ_MAX_TRANS_IDS                 =   50
   EAQUXXX                          =    1

   SSL_FILETYPE_PEM                 =     1
   SSL_VERIFY_PEER                  =  0x01
   SSL_VERIFY_FAIL_IF_NO_PEER_CERT  =  0x02
   HI_TLS_SSLV3_METHOD              =     1
   HI_TLS_SSLV23_METHOD             =     4

   AQ_ACR_CMD_CODE                      =    271
   AQ_ASR_CMD_CODE                      =    274
   AQ_RAR_CMD_CODE                      =    258
   AQ_STR_CMD_CODE                      =    275
   AQ_DPR_CMD_CODE                      =    282
   AQ_DWR_CMD_CODE                      =    280
   AQ_CER_CMD_CODE                      =    257
   AQ_ERR_CMD_CODE                      =     0
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   AQ_GQ_AAR_CMD_CODE                    =  265
   AQ_GQ_STR_CMD_CODE                    =  275
   AQ_GQ_ASR_CMD_CODE                    =  274
   AQ_GQ_RAR_CMD_CODE                    =  258

   AQ_RO_RF_CCR_CMD_CODE                =  272
   AQ_RO_RF_RAR_CMD_CODE                =  258
   AQ_RO_RF_CCA_CMD_CODE                =  272
   AQ_RO_RF_RAA_CMD_CODE                =  258

   AQ_CXDX_UAR_CMD_CODE                =  300
   AQ_CXDX_SAR_CMD_CODE                =  301
   AQ_CXDX_LIR_CMD_CODE                =  302
   AQ_CXDX_MAR_CMD_CODE                =  303
   AQ_CXDX_RTR_CMD_CODE                =  304
   AQ_CXDX_PPR_CMD_CODE                =  305
   AQ_CXDX_UAA_CMD_CODE                =  300
   AQ_CXDX_SAA_CMD_CODE                =  301
   AQ_CXDX_LIA_CMD_CODE                =  302
   AQ_CXDX_MAA_CMD_CODE                =  303
   AQ_CXDX_RTA_CMD_CODE                =  304
   AQ_CXDX_PPA_CMD_CODE                =  305

   AQ_RX_AAR_CMD_CODE                   =  265
   AQ_RX_ASR_CMD_CODE                   =  274
   AQ_RX_RAR_CMD_CODE                   =  258
   AQ_RX_STR_CMD_CODE                   =  275
   AQ_RX_AAA_CMD_CODE                   =  265
   AQ_RX_ASA_CMD_CODE                   =  274
   AQ_RX_RAA_CMD_CODE                   =  258
   AQ_RX_STA_CMD_CODE                   =  275
   AQ_RQ_AAR_CMD_CODE                   =  265
   AQ_RQ_AAR_CMD_CODE                   =  265
   AQ_RQ_ASR_CMD_CODE                   =  274
   AQ_RQ_RAR_CMD_CODE                   =  258
   AQ_RQ_STR_CMD_CODE                   =  275
	# aq016.102 
   AQ_SH_UDR_CMD_CODE                =  306
   AQ_SH_PUR_CMD_CODE                =  307
   AQ_SH_SNR_CMD_CODE                =  308
   AQ_SH_PNR_CMD_CODE                =  309
   AQ_SH_UDA_CMD_CODE                =  306
   AQ_SH_PUA_CMD_CODE                =  307
   AQ_SH_SNA_CMD_CODE                =  308
   AQ_SH_PNA_CMD_CODE                =  309
   AQ_E2_UDR_CMD_CODE                =  306

   AQ_GX_CCR_CMD_CODE                  =   272
   AQ_GX_CCA_CMD_CODE                  =   272
   AQ_GX_RAR_CMD_CODE                  =   258
   AQ_GX_RAA_CMD_CODE                  =   258

   AQ_GY_CCR_CMD_CODE                  =   272
   AQ_GY_CCA_CMD_CODE                  =   272
   AQ_GY_RAR_CMD_CODE                  =   258
   AQ_GY_RAA_CMD_CODE                  =   258

   AQ_GZ_ACR_CMD_CODE                  =   271
   AQ_GZ_ACA_CMD_CODE                  =   271

   AQ_GXC_CCR_CMD_CODE                 =   272
   AQ_GXC_CCA_CMD_CODE                 =   272
   AQ_GXC_RAR_CMD_CODE                 =   258
   AQ_GXC_RAA_CMD_CODE                 =   258

   AQ_S6A_NOR_CMD_CODE                  =  323
   AQ_S6A_RSR_CMD_CODE                  =  322
   AQ_S6A_ULR_CMD_CODE                  =  316
   AQ_S6A_AIR_CMD_CODE                  =  318
   AQ_S6A_CLR_CMD_CODE                  =  317
   AQ_S6A_DSR_CMD_CODE                  =  320
   AQ_S6A_IDR_CMD_CODE                  =  319
   AQ_S6A_PUR_CMD_CODE                  =  321
   AQ_S6A_ECR_CMD_CODE                  =  324
   AQ_S6A_NOA_CMD_CODE                  =  323
   AQ_S6A_RSA_CMD_CODE                  =  322
   AQ_S6A_ULA_CMD_CODE                  =  316
   AQ_S6A_AIA_CMD_CODE                  =  318
   AQ_S6A_CLA_CMD_CODE                  =  317
   AQ_S6A_DSA_CMD_CODE                  =  320
   AQ_S6A_IDA_CMD_CODE                  =  319
   AQ_S6A_PUA_CMD_CODE                  =  321
   AQ_S6A_ECA_CMD_CODE                  =  324

   AQ_E4_UDR_CMD_CODE                  =   306
   AQ_E4_UDA_CMD_CODE                  =   306
   AQ_E4_PNR_CMD_CODE                  =   309
   AQ_E4_PNA_CMD_CODE                  =   309

   AQ_S6B_DER_CMD_CODE                 =   268
   AQ_S6B_DEA_CMD_CODE                 =   268
   AQ_S6B_AAR_CMD_CODE                 =   265
   AQ_S6B_AAA_CMD_CODE                 =   265
   AQ_S6B_STR_CMD_CODE                 =   275
   AQ_S6B_STA_CMD_CODE                 =   275
   AQ_S6B_ASR_CMD_CODE                 =   274
   AQ_S6B_ASA_CMD_CODE                 =   274
   AQ_S6B_RAR_CMD_CODE                 =   258
   AQ_S6B_RAA_CMD_CODE                 =   258

   AQ_SWX_MAR_CMD_CODE                 =   303
   AQ_SWX_MAA_CMD_CODE                 =   303
   AQ_SWX_PPR_CMD_CODE                 =   305
   AQ_SWX_PPA_CMD_CODE                 =   305
   AQ_SWX_SAR_CMD_CODE                 =   301
   AQ_SWX_SAA_CMD_CODE                 =   301
   AQ_SWX_RTR_CMD_CODE                 =   304
   AQ_SWX_RTA_CMD_CODE                 =   304

   AQ_SWM_DER_CMD_CODE                 =   268
   AQ_SWM_DEA_CMD_CODE                 =   268
   AQ_SWM_AAR_CMD_CODE                 =   265
   AQ_SWM_AAA_CMD_CODE                 =   265
   AQ_SWM_STR_CMD_CODE                 =   275
   AQ_SWM_STA_CMD_CODE                 =   275
   AQ_SWM_ASR_CMD_CODE                 =   274
   AQ_SWM_ASA_CMD_CODE                 =   274
   AQ_SWM_RAR_CMD_CODE                 =   258
   AQ_SWM_RAA_CMD_CODE                 =   258


   DL_AUTH_CLIENT_STATEFUL_MACHINE                =  0
   DL_AUTH_SERVER_STATEFUL_MACHINE                =  1
   DL_AUTH_CLIENT_STATELESS_MACHINE                =  2
   DL_AUTH_SERVER_STATELESS_MACHINE                =  3
   DL_ACC_CLIENT_STATEFUL_MACHINE                =  4
   DL_ACC_SERVER_STATEFUL_MACHINE                =  5
   DL_ACC_CLIENT_STATELESS_MACHINE                =  6
   DL_ACC_SERVER_STATELESS_MACHINE                =  7

   IDLE                                           =  0
   PENDING                                        =  1
   OPEN                                           =  2
   DISCONNECT                                     =  3
   ACC_OPEN                                       =  1
   ACC_PENDINGS                                   =  2
   ACC_PENDINGI                                   =  3
   ACC_PENDINGE                                   =  4
   ACC_PENDINGB                                   =  5
   ACC_PENDINGL                                   =  6

   DL_EVT_RCV_TIME_OUT                            =  0
   DL_AUTH_SFMEVT_ACCESS_DEVICE                   =  1
   DL_AUTH_SFMEVT_RCV_AUTH_ANS_DFLT_VALUE         =  2
   DL_AUTH_SFMEVT_RCV_AUTH_ANSWER_NO_SERVICE      =  3
   DL_AUTH_SFMEVT_RCV_ERR_EVENT                   =  4
   DL_AUTH_SFMEVT_RCV_FAILED_AUTH_ANS             =  5
   DL_AUTH_SFMEVT_RCV_ASR_ACCEPT                  =  6
   DL_AUTH_SFMEVT_RCV_ASR_REJECT                  =  7
   DL_AUTH_SFMEVT_RCV_STA                         =  8

   DL_AUTH_SFMEVT_RCV_AUTH_REQ_USR_AUTH           =  1
   DL_AUTH_SFMEVT_RCV_AUTH_REQ_USR_NOT_AUTH       =  2
   DL_AUTH_SFMEVT_RCV_TERM_SESS                   =  3
   DL_AUTH_SFMEVT_RCV_ASA                         =  4
   DL_AUTH_SFMEVT_RCV_STR                         =  5

   DL_AUTH_SLMEVT_RCV_AUTH_ANS_DFLT_VALUE         =  1
   DL_AUTH_SLMEVT_RCV_FAILED_AUTH_ANS             =  2
   DL_AUTH_SLMEVT_ACCESS_DEVICE                   =  3
   DL_AUTH_SLMEVT_RCV_SERV_TERM                   =  4

   DL_AUTH_SLMEVT_RCV_AUTH_REQ                    =  1

   DL_ACC_SFMEVT_RCV_ACC_EVENT_REQ                =  1
   DL_ACC_SFMEVT_RCV_ACC_REQ_NO_SPACE             =  2
   DL_ACC_SFMEVT_RCV_INTERIM_RECORD               =  3
   DL_ACC_SFMEVT_RCV_STOP_REQ                     =  4
   DL_ACC_SFMEVT_RCV_ACC_START_REQ                =  5

   DL_ACC_SFMEVT_ACCESS_DEVICE                    =  0
   DL_ACC_SFMEVT_RCV_ONE_TIME_SERVICE             =  1
   DL_ACC_SFMEVT_RCV_REC_IN_STORE                 =  2
   DL_ACC_SFMEVT_RCV_ACC_START_ANS                =  3
   DL_ACC_SFMEVT_SEND_FAILED_NEQ_DELIVER_GRANT    =  4
   DL_ACC_SFMEVT_RCV_SERVICE_TERMINATED           =  5
   DL_ACC_SFMEVT_SEND_FAILED_NO_BUFFER_EQ_GRANT_LOSE =  6
   DL_ACC_SFMEVT_SEND_FAILED_NO_BUFFER_NEQ_GRANT_LOSE =  7
   DL_ACC_SFMEVT_RCV_FAILED_ANS_EQ_GRANT_LOSE     =  8
   DL_ACC_SFMEVT_RCV_FAILED_ANS_NEQ_GRANT_LOSE     =  9
   DL_ACC_SFMEVT_INTERVAL_ELAPSES                  =  10
   DL_ACC_SFMEVT_RCV_ACC_INTERIM_ANS               =  11
   DL_ACC_SFMEVT_RCV_ACC_EVENT_ANS                 =  12
   DL_ACC_SFMEVT_SEND_FAILED                       =  13
   DL_ACC_SFMEVT_RCV_FAILED_ANS                    =  14
   DL_ACC_SFMEVT_SEND_FAILED_NO_BUFFER             =  15
   DL_ACC_SFMEVT_RCV_ACC_ANS                       =  16
   DL_ACC_SFMEVT_RCV_ACC_STOP_ANS                  =  17

   DL_ACC_SLMEVT_RCV_ACC_EVENT_REQ                 =  1
   DL_ACC_SLMEVT_RCV_ACC_REQ_NO_SPACE              =  2
   DL_ACC_SLMEVT_RCV_INTERIM_RECORD                =  3
   DL_ACC_SLMEVT_RCV_STOP_REQ                      =  4
   DL_ACC_SLMEVT_RCV_ACC_START_REQ                 =  5

   DL_DIAM_FIRST_REGISTRATION                 =  2001
   AQ_REJECT                                  =  5001
   NASREQAPP                                  = 15




   
   AQ_CX_DX_UAR_CMD_CODE                =  300
   AQ_CX_DX_SAR_CMD_CODE                =  301
   AQ_CX_DX_LIR_CMD_CODE                =  302
   AQ_CX_DX_MAR_CMD_CODE                =  303
   AQ_CX_DX_RTR_CMD_CODE                =  304
   AQ_CX_DX_PPR_CMD_CODE                =  305
   LAQ_PSMST_CLOSED                    =   0
   LAQ_PSMST_WAIT_CONN_ACK             =   1
   LAQ_PSMST_WAIT_I_CEA                =   2
   LAQ_PSMST_WAIT_CONN_ACK_ELECT       =   3
   LAQ_PSMST_WAIT_RETURNS              =   4
   LAQ_PSMST_OPEN                      =   5
   LAQ_PSMST_CLOSING                   =   6
   LAQ_PSMST_SUSPECT                   =   7
   LAQ_PSMST_DOWN                      =   8
   LAQ_PSMST_REOPEN                    =   9
   LAQ_PSMST_WAIT_TLS_CFM              =   10
   AQ_DSC_REASON_REBOOTING             =   0
   AQ_DSC_REASON_BUSY                  =   1
   AQ_DSC_REASON_DNWT                  =   2
   AQ_DSC_REASON_DEL_PEER              =   3
   AQ_DSC_REASON_CLOSE_PEER            =   4
   AQ_DSC_REASON_TLS_FAIL              =   5
   LAQ_CAUSE_MISSING_MAND_AVP          =   285
   TC_CTC_COMP_ALGO_NOT_SUPPORTED = 0
   TC_CTC_COMP_ROHC_PROF_NOT_SUPPORTED = 1
   TC_CTC_RELOC_CTXT_NOT_SUPPORTED = 2
   TC_CTC_RES_NOT_AVAIL = 3
   TC_CTC_INVALID_PDCPID = 4
   TC_CTC_INVALID_RLC_MODE = 5
   TC_SDU_DISCARD_MODE_NONE = 0
   TC_SDU_DISCARD_MODE_MAX_DAT = 1 
   TC_SDU_DISCARD_MODE_TIMER = 2 
   TC_SDU_DISCARD_MODE_TIMER_AND_MAX_DAT = 3
   TC_EVC_RESET_FAILED = 1 
   LCM_REASON_NOT_APPL = 0
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   LCM_REASON_INV_RSET = 23
   LXT_REASON_SESS_NOT_RELSD = 258
   CM_BND_OK = 1
   LXT_INSTCREATE = 0
   LXT_INSTDELETE = 1
   LXT_INSTUPDATE = 2
   LXT_MODE_TRANSPARENT = 0
   LXT_MODE_SUPPORT_V1 = 1
   LXT_MODE_SUPPORT_V2 = 1
   LHR_TSAP_HIT = 1
   LLX_TSAP_TYPE_RTP = 1
   LLX_TSAP_TYPE_GTPU = 2
   LLX_TSAP_TYPE_AAL2 = 3
   LLX_TSAP_TYPE_DRTP = 4
   LLX_TSAP_TYPE_DGTPU = 5
   LLX_TSAP_TYPE_DAAL2 = 6
   LXT_TRCH_TYPE_RTP = 1
   LXT_TRCH_TYPE_GTP = 2
   LXT_TRCH_TYPE_AAL = 3
   LXT_INIT = 0
   LXT_RNC = 0
   LXT_CN = 1
   LXT_RATECNTRL = 1
   LXT_TIMEALGN = 2
   LXT_ERREVT = 3
   LXT_PROC_CNTRL= 0
   LXT_PROC_ACK = 1
   LXT_PROC_NACK = 2
   LXT_PROC_ERR = 3
   LXT_ERR_CRC_FRMHDR = 0
   LXT_ERR_CRC_FRMPYLD= 1
   LXT_ERR_UNEXPECTED_FRM_NUM = 2
   LXT_ERR_FRM_LOSS = 3
   LXT_ERR_PDU_TYPE_UNKNOWN = 4
   LXT_ERR_UNKNOWN_PROC = 5
   LXT_ERR_UNKNOWN_RESVD_VAL = 6
   LXT_ERR_UNKNOWN_FIELD = 7
   LXT_ERR_FRM_TOO_SHRT = 8
   LXT_ERR_MISSIN_FIELDS = 9
   LXT_ERR_UNEXPECTED_PDU_TYPE = 16
   LXT_ERR_UNEXPECTED_PROC = 18
   LXT_ERR_UNEXPECTED_RFCI = 19
   LXT_ERR_UNEXPECTED_VAL = 20
   LXT_ERR_INIT_FAIL1 = 42
   LXT_ERR_INIT_FAIL_NW_ERROR = 43
   LXT_ERR_INIT_FAIL_TMR_EXP = 43
   LXT_ERR_INIT_FAIL_FUNC_ERR = 44
   LXT_ERR_INIT_FAIL_REP_NACK = 44
   LXT_ERR_RATE_CNTRL_FAIL = 45
   LXT_ERR_ERROR_EVNT_FAIL = 46
   LXT_ERR_TIME_ALGN_NOT_SUPP = 47
   LXT_ERR_TIME_ALGN_NOT_POS = 48
   LXT_IUUP_MODE_VER_NOT_SUPP = 49
   LXT_CAUSE_INVALID_STATE=0
   LXT_ERR_DIST0 = 0
   LXT_ERR_DIST1 = 1
   LXT_ERR_DIST2 = 2
   LXAC_PDU_TYPE0 = 0
   LXAC_PDU_TYPE1 = 1
   LXAC_PDU_TYPE14 = 14

   LLX_CAUSE_SAP_BNDDIS = (LCM_CAUSE_LYR_SPECIFIC + 1)
   LLX_CAUSE_SAP_BNDENA = (LCM_CAUSE_LYR_SPECIFIC + 2)
   LLX_CAUSE_SAP_UBNDDIS = (LCM_CAUSE_LYR_SPECIFIC + 3)
   LLX_CAUSE_LI_INITIATED = (LCM_CAUSE_LYR_SPECIFIC + 4)
   LLX_CAUSE_INV_SUINSTID = (LCM_CAUSE_LYR_SPECIFIC + 5)
   LLX_CAUSE_INV_SPINSTID = (LCM_CAUSE_LYR_SPECIFIC + 6)
   LLX_CAUSE_SAP_DISGRC = (LCM_CAUSE_LYR_SPECIFIC + 7)
   LLX_CAUSE_SPINSTID_NOT_AVAIL = (LCM_CAUSE_LYR_SPECIFIC + 8)
   LLX_CAUSE_PROC_FAIL = (LCM_CAUSE_LYR_SPECIFIC + 9)
   LLX_CAUSE_INVALID_INST_STATE = (LCM_CAUSE_LYR_SPECIFIC + 10)

   LLX_REASON_INVALID_INSTANCE = (LCM_REASON_LYR_SPECIFIC + 1)
   LLX_REASON_INVALID_TPTTYPE = (LCM_REASON_LYR_SPECIFIC + 2)
   LLX_REASON_INVALID_MTUSIZE = (LCM_REASON_LYR_SPECIFIC + 3)
   LLX_REASON_INVALID_BINSIZE   =  (LCM_REASON_LYR_SPECIFIC + 4)
   LLX_REASON_INVALID_TMRVAL    =  (LCM_REASON_LYR_SPECIFIC + 5)
   LLX_REASON_INVALID_NUMRETRY  =  (LCM_REASON_LYR_SPECIFIC + 6)

   LLX_TRC_EVENT_TX = 1
   LLX_TRC_EVENT_RX = 2

   GGU_GTP_VER_0 = 0
   GGU_GTP_VER_1 = 1

   GGU_TMGMT_REQTYPE_DEL_ALL = 5
   
   SW_PROVIDER_NOTFOUND = 1
   SW_LISTENER_NOTFOUND = 2
   SW_SESSION_NOTFOUND = 3
   SW_SIPMSG_NOTFOUND = 4
   SW_DLG_NOTFOUND = 5
   SW_DLGDATA_NOTFOUND = 6
   SW_DLGSTATE_NOTFOUND = 7
   SW_SIPEVENT_INVALID = 8
   SW_FORKDLG_CREATED = 9
   SW_SIPOAENGNE_NOTFOUND = 10
   SW_SDPSESSION_NOTFOUND = 11
   SW_PREV_SDPOA_INCOMPLETE = 12
   SW_SDPOA_INCOMPLETE_UPDATE_SEND_491 = 13
   SW_SDPOA_INCOMPLETE_UPDATE_SEND_504 = 14
   SW_SEND_LOCALSDP_NULL = 15
   SW_APP_SEND_SDP_REQD = 16
   SW_SIPOA_REJECT_MSG = 17
   SW_SDP_EINSDP = 18
   SW_SDP_EINVAL = 19
   SW_SDP_EINVER = 20
   SW_SDP_EINORIGIN = 21
   SW_SDP_EINTIME = 22
   SW_SDP_EINNAME = 23
   SW_SDP_EINCONN = 24
   SW_SDP_EMISSINGCONN = 25
   SW_SDP_EINATTR = 26
   SW_SDP_EINRTPMAP = 27
   SW_SDP_ERTPMAPTOOLONG = 28
   SW_SDP_EMISSINGRTPMAP = 29
   SW_SDP_EINMEDIA = 30
   SW_SDP_ENOFMT = 31
   SW_SDP_EINPT = 32
   SW_SDP_EINFMTP = 33
   SW_SDP_EINRTCP = 34
   SW_SDP_EINPROTO = 35
   SW_SDP_EMISSINGMEDIA = 36
   SW_SDPNEG_EINSTATE = 37
   SW_SDPNEG_NO_LOCAL_SDP = 38
   SW_SDPNEG_NO_REMOTE_SDP = 39
   SW_SDPNEG_ENOACTIVE = 40
   SW_SDPNEG_ENONEG = 41
   SW_SDPNEG_EMISMEDIA = 42
   SW_SDPNEG_EINVANSMEDIA = 43
   SW_SDPNEG_EINVANSTP = 44
   SW_SDPNEG_EANSNOMEDIA = 45
   SW_SDPNEG_ENOMEDIA = 46
   SW_SDPNEG_NOANSCODEC = 47
   SW_SDPNEG_NOANSTELEVENT = 48
   SW_SDPNEG_NOANSUNKNOWN = 49
   SW_SDPNEG_EINVMOD = 50
   SW_SDP_NOMODIFY = 51
   SW_SDP_DUPLICATE = 52
   SW_SDPNEG_EDUPSDP = 53
   SW_SDP_EMEDIANOTEQUAL = 54
   SW_SDP_EPORTNOTEQUAL = 55
   SW_SDP_ETPORTNOTEQUAL = 56
   SW_SDP_EFORMATNOTEQUAL = 57
   SW_SDP_ECONNNOTEQUAL = 58
   SW_SDP_EATTRNOTEQUAL = 59
   SW_SDP_EDIRNOTEQUAL = 60
   SW_SDP_EFMTPNOTEQUAL = 61
   SW_SDP_ERTPMAPNOTEQUAL = 62
   SW_SDP_ESESSNOTEQUAL = 63
   SW_SDP_EORIGINNOTEQUAL = 64
   SW_SDP_ENAMENOTEQUAL = 65
   SW_SDP_ETIMENOTEQUAL = 66
   SW_CODEC_EUNSUP = 67
   SW_CODEC_EFAILED = 68
   SW_CODEC_EFRMTOOSHORT = 69
   SW_CODEC_EPCMTOOSHORT = 70
   SW_CODEC_EFRMINLEN = 71
   SW_CODEC_EPCMFRMINLEN = 72
   SW_CODEC_EINMODE = 73
   SW_EINVALIDIP = 74
   SW_EASYMCODEC = 75
   SW_EINVALIDPT = 76
   SW_EMISSINGRTPMAP = 77
   SW_EINVALIMEDIATYPE = 78
   SW_EREMOTENODTMF = 79
   SW_RTP_EINDTMF = 80
   SW_RTP_EREMNORFC2833 = 81
   SW_SDP_NOPORT = 82
   SW_SDK_ERR_MAX = 83

#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   ENTSZ             =  209
   ENTUZ             =  210
   LSZ_MAX_NUM_OF_PEERS =  16000
   SZAC_LSZ_INV_NUM_PEERS  =  LSZ_MAX_NUM_OF_PEERS + 1
   LCM_REASON_EXCEED_CONF_VAL =  19

   # Iuh 2.1 release 
   LHM_TYPE_HNB = 1
   LHM_TYPE_HNBGW = 2

   LCM_CATEGORY_PROTOCOL      =    1
   LCM_CATEGORY_INTERFACE     =    2
   LCM_CATEGORY_INTERNAL      =    3
   LCM_CATEGORY_RESOURCE      =    4
   LCM_CATEGORY_PSF_FTHA      =    5
   LCM_CATEGORY_PERF_MONIT    =    6

   LSZ_USTA_DGNVAL_NONE       =    1
   LSZ_USTA_DGNVAL_MEM        =    2
   LSZ_USTA_DGNVAL_SAPID      =    3
   LSZ_USTA_DGNVAL_DATA       =    4
   LSZ_USTA_DGNVAL_PEER       =    5
   LSZ_USTA_DGNVAL_CONID      =    6

   LSZ_REASON_PROTCFG_NOT_DONE   =    257
   LSZ_REASON_HASHINIT_FAIL      =    259
   LSZ_REASON_SAP_ASSOC_EXISTS   =    260
   LSZ_REASON_LSAPCFG_NOT_DONE   =    261
   LSZ_REASON_DUP_AUDIT_REQ      =    262

   LSZ_EVENT_LI_BND_CFM         =  257
   LSZ_EVENT_LI_ENDP_OPEN_CFM   =  258
   LSZ_EVENT_LI_ENDP_CLOSE_CFM  =  259
   LSZ_EVENT_LI_ASSOC_IND       =  260
   LSZ_EVENT_LI_ASSOC_CFM       =  261
   LSZ_EVENT_LI_TERM_IND        =  262
   LSZ_EVENT_LI_TERM_CFM        =  263
   LSZ_EVENT_LI_FLC_IND         =  264
   LSZ_EVENT_LI_DAT_IND         =  265
   LSZ_EVENT_LI_STA_IND         =  266
   LSZ_EVENT_LI_SEND_FAIL       =  267
   LSZ_EVENT_DMEM_ALLOC_PASS    =  268

   LSZ_CAUSE_CONGESTION_RECV    =   257
   LSZ_CAUSE_ASSOC_UP           =   258
   LSZ_CAUSE_ASSOC_DOWN         =   259
   LSZ_CAUSE_PEER_DELETED       =   260
   LSZ_CAUSE_ENDP_OPEN          =   261
   LSZ_CAUSE_EXCEED_CONF_VAL    =   262
   LSZ_CAUSE_OUTRES             =   263
   LSZ_CAUSE_SCT_ENPOPEN_SUCC   =   264
   LSZ_CAUSE_INV_PAR_VAL        =   265
   LSZ_CAUSE_EPCLOSE_OK         =   266

   SCT_CAUSE_INV_PAR_VAL        =   11
   SCT_CAUSE_ENDP_OPEN          =   1
   SCT_CAUSE_EXCEED_CONF_VAL    =   4
   SCT_CAUSE_OUTRES             =   3

#RMU Cause
   RMU_CAUSE_CELLID_UNKNOWN     = 0
   RMU_CAUSE_MMEID_UNKNOWN      = 1
   RMU_CAUSE_UEID_UNKNOWN       = 2
   RMU_CAUSE_OUT_OF_RESOURCE    = 3
   RMU_CAUSE_MAX_UE_REACHED      = 4
   RMU_CAUSE_CELL_ALREADY_EXISTS = 5
   RMU_CAUSE_MME_ALREADY_EXISTS  = 6
   RMU_CAUSE_ENB_ALREADY_UP = 7
   RMU_CAUSE_NOT_APP = 8
   RMU_CAUSE_OTHER = 9

#RMU HO TYPE
   RMU_HO_TYPE_IntraLTE = 0
   RMU_HO_TYPE_LTEtoUTRAN = 1
   RMU_HO_TYPE_LTEtoGERAN = 2
   RMU_HO_TYPE_UTRANtoLTE = 3
   RMU_HO_TYPE_GERANtoLTE = 4
   RMU_HO_TYPE_S1 = 5
   RMU_HO_TYPE_X2 = 6

#RMU CAUSE
   RMU_CAUSE_REDUCE_LOAD_IN_SERV_CELL = 0
   RMU_CAUSE_SUCC_HANDOVER = 1
   RMU_CAUSE_REL_EUTRAN_REASON = 2
   RMU_CAUSE_HANDOVER_CANCELLED = 3
   RMU_CAUSE_CELL_NOTAVAILABLE = 4

#RMU STATUS
   RMU_FAILURE = 0
   RMU_SUCCESS = 1
   RMU_REDIRECT = 2

#RMU EST CAUSE
   RMU_EST_CAUSE_EMERGENCY = 0
   RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS = 1
   RMU_EST_CAUSE_MT_ACCESS = 2
   RMU_EST_CAUSE_MO_SIGNALLING = 3
   RMU_EST_CAUSE_MO_DATA = 4
   RMU_EST_CAUSE_DELAY_TOLERANT = 5

#RMU OVLD STATUS
   RMU_MME_REJECT_MODATA = 0
   RMU_MME_REJECT_MOSIG_MODATA = 1
   RMU_MME_PERMITONLY_EMG_MTACCESS = 2
   RMU_MME_PERMITONLY_HIGHPRI_MTACCESS = 3
   RMU_MME_REJECT_DELAY_TOLERNT_ACCESS = 4
   RMU_MME_OVLD_STATUS_NORMAL = 5

#RMU FSM STATUS TYPE
   RMU_FSM_STATUS_MME  = 0
   RMU_FSM_STATUS_ENB  = 1

#RMU MME STATUS
   RMU_MME_STATUS_UP   = 0
   RMU_MME_STATUS_DOWN = 1

#RMU ENB STATUS
   RMU_ENB_STATE_UP   = 0
   RMU_ENB_STATE_DOWN = 1

#RMU AC BARRING FACTOR
   RMU_ACBFACTOR_P00 = 0
   RMU_ACBFACTOR_P05 = 1
   RMU_ACBFACTOR_P10 = 2
   RMU_ACBFACTOR_P15 = 3
   RMU_ACBFACTOR_P20 = 4
   RMU_ACBFACTOR_P25 = 5
   RMU_ACBFACTOR_P30 = 6
   RMU_ACBFACTOR_P40 = 7
   RMU_ACBFACTOR_P50 = 8
   RMU_ACBFACTOR_P60 = 9
   RMU_ACBFACTOR_P70 = 10
   RMU_ACBFACTOR_P75 = 11
   RMU_ACBFACTOR_P80 = 12
   RMU_ACBFACTOR_P85 = 13
   RMU_ACBFACTOR_P90 = 14
   RMU_ACBFACTOR_P95 = 15
   RMU_ACBFACTOR_NA = 16

#RMU AC BARRING TIME
   RMU_ACBTIME_S4 = 0
   RMU_ACBTIME_S8 = 1
   RMU_ACBTIME_S16 = 2
   RMU_ACBTIME_S32 = 3
   RMU_ACBTIME_S64 = 4
   RMU_ACBTIME_S128 = 5
   RMU_ACBTIME_S256 = 6
   RMU_ACBTIME_S512 = 7

#RMU PCQI FORMAT
   RMU_PCQI_FMT_WIDEBAND = 0
   RMU_PCQI_FMT_SUBBAND = 1

#RMU PUCCH REPORT MODE
   RMU_CQI_MODE10 = 0
   RMU_CQI_MODE11 = 1
   RMU_CQI_MODE20 = 2
   RMU_CQI_MODE21 = 3

#RMU ERAB ACTION
   RMU_ADD_ERAB = 0
   RMU_MOD_ERAB = 1
   RMU_DEL_ERAB = 2
 
#  ACCESS STRATUM REL
   RMU_ACCESS_STRATUM_REL8 = 0
   RMU_ACCESS_STRATUM_REL9 = 1
   RMU_ACCESS_STRATUM_REL9HIGHER = 2

# RMU SPS IMPLCT REL AFTER
   RMU_SPS_E2 = 0
   RMU_SPS_E3 = 1
   RMU_SPS_E4 = 2
   RMU_SPS_E8 = 3

#RMU SPS INTERVAL
   RMU_SPS_INTERVAL_E10 = 0 
   RMU_SPS_INTERVAL_E20 = 1
   RMU_SPS_INTERVAL_E32 = 2
   RMU_SPS_INTERVAL_E40 = 3
   RMU_SPS_INTERVAL_E64 = 4
   RMU_SPS_INTERVAL_E80 = 5
   RMU_SPS_INTERVAL_E128 = 6
   RMU_SPS_INTERVAL_E160 = 7
   RMU_SPS_INTERVAL_E320 = 8
   RMU_SPS_INTERVAL_E640 = 9

#RMU Radio Res Bitmap
   RM_RCM_MAC_MAIN_CFG = 1
   RM_RCM_PHY_DED_RES_CFG = 2
   RM_RCM_MAC_PHY_CFG = 3

#LRM CFG ACTION
   LRM_SEL_LWLC = 2
   LRM_SEL_TC = 1
   LRM_CFG_ADD = 1
   LRM_CFG_MOD = 2
   LRM_CFG_DEL = 3

#LRM CELL BW
   LRM_BANDWIDTH_6 = 0
   LRM_BANDWIDTH_15 = 1
   LRM_BANDWIDTH_25 = 2
   LRM_BANDWIDTH_50 = 3
   LRM_BANDWIDTH_75 = 4
   LRM_BANDWIDTH_100 = 5
   LRM_BANDWIDTH_MAX = 6

#LRM CFG TYPE
   LRM_ENB_CONFIG = 0
   LRM_CELL_CONFIG = 1

#Special Subframe Config Type
   LRM_SPL_SF_CONFIG_0 = 0
   LRM_SPL_SF_CONFIG_1 = 1
   LRM_SPL_SF_CONFIG_2 = 2
   LRM_SPL_SF_CONFIG_3 = 3
   LRM_SPL_SF_CONFIG_4 = 4
   LRM_SPL_SF_CONFIG_5 = 5
   LRM_SPL_SF_CONFIG_6 = 6
   LRM_SPL_SF_CONFIG_7 = 7
   LRM_SPL_SF_CONFIG_8 = 8

#UL DL Config Type
   LRM_UL_DL_CONFIG_0 = 0
   LRM_UL_DL_CONFIG_1 = 1
   LRM_UL_DL_CONFIG_2 = 2
   LRM_UL_DL_CONFIG_3 = 3
   LRM_UL_DL_CONFIG_4 = 4
   LRM_UL_DL_CONFIG_5 = 5
   LRM_UL_DL_CONFIG_6 = 6

#SR Periodicity Cfg
   LRM_SR_PRDCTY_5   = 0
   LRM_SR_PRDCTY_10  = 1
   LRM_SR_PRDCTY_20  = 2
   LRM_SR_PRDCTY_40  = 3
   LRM_SR_PRDCTY_80  = 4
   LRM_SR_PRDCTY_2   = 5
   LRM_SR_PRDCTY_1   = 6

#CQI Periodicity Cfg
   LRM_CQI_PRDCTY_1   = 0
   LRM_CQI_PRDCTY_2   = 0
   LRM_CQI_PRDCTY_5   = 1
   LRM_CQI_PRDCTY_10  = 2
   LRM_CQI_PRDCTY_20  = 3
   LRM_CQI_PRDCTY_40  = 4
   LRM_CQI_PRDCTY_80  = 5
   LRM_CQI_PRDCTY_160 = 6
   LRM_CQI_PRDCTY_32  = 7
   LRM_CQI_PRDCTY_64  = 8
   LRM_CQI_PRDCTY_128 = 9

#DRX Trans Max Type

   DSR_TRANS_N4  = 0
   DSR_TRANS_N8  = 1
   DSR_TRANS_N16 = 2
   DSR_TRANS_N32 = 3
   DSR_TRANS_N64 = 4

#cm_xta_py_py_001.main_37: Updated for S1AP 3.1 release
   SZ_ASSOC_DOWN     =  0 
   SZAC_LSZ_ENB_PRC0 =  1
   SZAC_LSZ_MME_PRC1 =  2
   SZAC_LSZ_GW_PRC2  =  3
   SZAC_NODE_ENB     =  2
   SZAC_NODE_GW      =  3
   SZAC_NODE_MME     =  1
   SZAC_LSZ_INV_NODE =  10
   SZAC_SCTP_DM      =  152
   LSZ_SAP_CFG       =   1
   LSZ_SAP_ISBOUND   =   2
   LSZ_SAP_BINDING   =   3
   LSZ_SAP_UBND      =   4
   STSZGEN           =   1
   STSZPROT          =   2
   STSZSZTSAP        =   3
   STSZSCTSAP        =   4
   STSZPEER          =   5
   STSZSID           =   6
   SZAC_PRC0         =  0
   SZAC_PRC1         =  1
   SZAC_PRC2         =  2
   SZAC_PRC3         =  3

   SZT_ND_ST_IDLE         = 4 
   SZT_ND_ST_SETUP_IN_PRG = 3 
   SZT_ND_ST_NORMAL       = 2 
   SZT_ND_ST_RESET        = 1 
   SZT_CON_ST_IDLE        = 0  
   SZT_CON_ST_CONNECTING  = 1  
   SZT_CON_ST_ESTBLD      = 2  
   SZT_CON_ST_RELEASING   = 3  
   SZT_CON_ST_NON_EXST    = 0xF

   SZT_AUD_CONN           = 1   
   SZT_AUD_PEER           = 2   
   SZT_AUD_FLC            = 3   
   SZT_FLC_START          =  1 
   SZT_FLC_DROP           =  2 
   SZT_FLC_STOP           =  3 
   SZT_FLC_ACTIVE         =  4 
   SZT_FLC_INACTIVE       =  5 
   SCT_FLC_START          =  1    
   SCT_FLC_DROP           =  2    
   SCT_FLC_STOP           =  3    
   SCT_FLC_ACTIVE         =  4    
   SCT_FLC_INACTIVE       =  5    

   SZAC_ENB_PROC          =  100 
   SZAC_XTA_PROC          =  100 
   SZAC_MME_PROC          =  200 
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   SZAC_SBY_PROC          =  400
   SZAC_ENB_PROC1         =  400 
   SZAC_MME_PROC1         =  400 
   YT_YTT_MODE_MANUAL     =  1
   YT_YTT_MODE_AUTO       =  2
   YT_YTT_MODE_CHECK      =  3
   SCTIF                  =  192
   SZTIF                  =  213
   YTPIF                  =  271
   SZTIFVER               =  0x0100
   SCTIFVER               =  0x0700
   YTPIFVER               =  0x0100

   SHT_REQTYPE_BND_ENA    = 1
   SHT_REQTYPE_UBND_DIS   = 2
   SHT_REQTYPE_GETVER     = 3
   SHT_REQTYPE_SETVER     = 4

   LCM_CATEGORY_INTERFACE = 2
   # Iuh 2.1 release 
   LHM_TYPE_HNB = 1
   LHM_TYPE_HNBGW = 2
   LSZ_EVENT_LI_ENDP_OPEN_CFM = 258
   LSZ_CAUSE_SCT_ENPOPEN_SUCC = 264
   LSZ_USTA_DGNVAL_SAPID = 3

#cm_xta_py_py_001.main_37: Updated for S1AP 3.1 release
   SZT_MSG_ID_SAE_BRR_SETUP_REQ =    0
   SZT_MSG_ID_SAE_BRR_SETUP_RSP =    1
   SZT_MSG_ID_SAE_BRR_MOD_REQ =      2
   SZT_MSG_ID_SAE_BRR_MOD_RSP =      3
   SZT_MSG_ID_SAE_BRR_REL_CMD =      4
   SZT_MSG_ID_SAE_BRR_REL_CMPLT =    5
   SZT_MSG_ID_SAE_BRR_REL_REQ =      6
   SZT_MSG_ID_ERAB_SETUP_REQ =       0
   SZT_MSG_ID_ERAB_SETUP_RSP =       1
   SZT_MSG_ID_ERAB_MOD_REQ =         2
   SZT_MSG_ID_ERAB_MOD_RSP =         3
   SZT_MSG_ID_ERAB_REL_CMD =         4
   SZT_MSG_ID_ERAB_REL_CMPLT =       5
   SZT_MSG_ID_ERAB_REL_REQ =         6
   SZT_MSG_ID_CXT_SETUP_REQ =        7
   SZT_MSG_ID_CXT_SETUP_RSP =        8
   SZT_MSG_ID_INIT_CXT_SETUP_FAIL =  9
   SZT_MSG_ID_UE_CXT_REL_REQ =      10
   SZT_MSG_ID_UE_CXT_REL_CMD =      11
   SZT_MSG_ID_UE_CXT_REL_CMPL =     12
   SZT_MSG_ID_UE_CXT_MOD_REQ =      13
   SZT_MSG_ID_UE_CXT_MOD_RSP =      14
   SZT_MSG_ID_UE_CXT_MOD_FAIL =     15
   SZT_MSG_ID_INIT_UE_MSG =         16
   SZT_MSG_ID_DL_NAS_TPT =          17
   SZT_MSG_ID_UL_NAS_TPT =          18
   SZT_MSG_ID_NAS_NON_DEL_IND =     19
   SZT_MSG_ID_ERR_IND =             20
   SZT_MSG_ID_NO_DATA =             21
   SZT_MSG_ID_RESET =               22
   SZT_MSG_ID_RESET_ACK =           23
   SZT_MSG_ID_SETUP_REQ  =          24
   SZT_MSG_ID_SETUP_RSP  =          25
   SZT_MSG_ID_SETUP_FAIL =          26
   SZT_MSG_ID_PAGING =              27
   SZT_MSG_ID_HO_REQD =             28
   SZT_MSG_ID_HO_CMD =              29
   SZT_MSG_ID_HO_PREP_FAIL =        30
   SZT_MSG_ID_HO_REQ =              31
   SZT_MSG_ID_HO_REQ_ACK =          32
   SZT_MSG_ID_HO_FAIL =             33
   SZT_MSG_ID_HO_NTFY =             34
   SZT_MSG_ID_PATH_SWTCH_REQ =      35
   SZT_MSG_ID_PATH_SWTCH_REQ_ACK =  36
   SZT_MSG_ID_PATH_SWTCH_REQ_FAIL = 37
   SZT_MSG_ID_HO_CANCEL =           38
   SZT_MSG_ID_HO_CANCEL_ACK =       39
   SZT_MSG_ID_ENB_STA_TRFR =        40
   SZT_MSG_ID_MME_STA_TRFR =        41
   SZT_MSG_ID_DEACTV_TRACE =        42
   SZT_MSG_ID_TRACE_START =         43
   SZT_MSG_ID_TRACE_FAIL_IND =      44
   SZT_MSG_ID_LOC_REPORT_CNTRL =    45
   SZT_MSG_ID_LOC_REPORT_FAIL_IND = 46
   SZT_MSG_ID_LOC_REPORT =          47
   SZT_MSG_ID_ENB_CFG_UPD =         48
   SZT_MSG_ID_ENB_CFG_UPD_ACK =     49
   SZT_MSG_ID_ENB_CFG_UPD_FAIL =    50
   SZT_MSG_ID_MME_CFG_UPD =         51
   SZT_MSG_ID_MME_CFG_UPD_ACK =     52
   SZT_MSG_ID_MME_CFG_UPD_FAIL =    53
   SZT_MSG_ID_UPLNK_CDMA_TUNNL =    54
   SZT_MSG_ID_DNLNK_CDMA_TUNNL =    55
   SZT_MSG_ID_UE_CAP_INFO =         56
   SZT_MSG_ID_OVLD_START =          57
   SZT_MSG_ID_OVLD_STOP =           58
   SZT_MSG_ID_WARNING_REQ =         59
   SZT_MSG_ID_WARNING_RSP =         60
   SZT_MSG_ID_ENB_DIR_TRANS =       61
   SZT_MSG_ID_MME_DIR_TRANS =       62
   SZT_MSG_ID_PRIVATE_MSG   =       63
   SZT_MSG_ID_ENB_CONFIG_TRANS =    64
   SZT_MSG_ID_MME_CONFIG_TRANS =    65
   SZT_MSG_ID_CELL_TRAFFIC_TRACE =  66
   
   SZT_MSG_ID_KILL_REQ =            67
   SZT_MSG_ID_KILL_RSP =            68
   SZT_MSG_ID_DNLNK_UE_ASSOC_LPPA_TPRT     = 69
   SZT_MSG_ID_UPLNK_UE_ASSOC_LPPA_TPRT     = 70
   SZT_MSG_ID_DNLNK_NON_UE_ASSOC_LPPA_TPRT = 71
   SZT_MSG_ID_UPLNK_NON_UE_ASSOC_LPPA_TPRT = 72

   SZT_MSG_ID_NO_MSG = 255

   SZT_STA_TYPE_FLC      = 1
   SZT_STA_TYPE_ASSOC    = 2

   SZT_STATUS_ASSOC_DOWN   =  1
   SZT_STATUS_ASSOC_UP     =  2
   SZT_STATUS_FLOW         =  3

   SZT_REASON_RCVD_TERMIND   =  1
   SZT_REASON_RCVD_COMM_UP   =  2
   SZT_REASON_UBND_SAP       =  3
   SZT_REASON_FLC_START      =  4
   SZT_REASON_FLC_STOP       =  5

   SZT_CAUSE_UNEXP_MSG     =   1
   SZT_CAUSE_NODE_RESET    =   2
   SZT_CAUSE_MEM_ALLOC_FAIL=   3
   SZT_CAUSE_INV_CONID     =   4
   SZT_CAUSE_INV_TYPE      =   5
   SZT_CAUSE_NOT_APPL      =   6
   SZT_CAUSE_PC_TX_SYNTAX_ERR = 7
   SZT_CAUSE_PC_ABS_SYNTAX_ERR = 8
   SZT_CAUSE_MSG_NOT_DELIVERED = 9
   SZT_CAUSE_LOWER_LAYER_SND_FAILED = 10
   SZT_CAUSE_INV_STATE        =  11
   SZT_CAUSE_INV_PEERID       = 12
   SZT_CAUSE_RX_ERRONEOUS_RSP       = 16

   SZT_CAUSE_RADIONW  = 0
   SZT_CAUSE_TRANSPORT  = 1
   SZT_CAUSE_NAS  = 2
   SZT_CAUSE_PROTOCOL  = 3
   SZT_CAUSE_MISC  = 4

# For Dynamic Peer Allocation Feature -- DPA
   SZT_STA_TYPE_PEER = 3
   SZT_REASON_NOT_APPL = 0
   SZT_STATUS_DYNAM_PEERCFG_OK = 4
   SZT_STATUS_DYNAM_PEERCFG_NOK = 5
   SZT_PRIM_OK = 0
   SZT_PRIM_NOK = 1
   SZT_CAUSE_NOT_APPL = 6
   LSZ_EVENT_UI_PEERASSOC_RSP = 268
   LSZ_CAUSE_DYNAM_PEERCFG_OK = 269
   LSZ_CAUSE_DYNAM_PEERCFG_NOK = 270

   SZT_LOCAL_REL = 1
   SZT_CXT_REL = 0
   SZT_CONN_TYPE_SU = 0
   SZT_CONN_TYPE_SP = 1

# cm_xta_py_py_001.main_24 : X2AP Patch release
#LTE X2AP
   ENTCZ             =  206
   LCZ_MAX_NUM_OF_PEERS =  16000
   CZAC_LCZ_INV_NUM_PEERS  =  LCZ_MAX_NUM_OF_PEERS + 1
   LCM_REASON_EXCEED_CONF_VAL =  19

   LCM_CATEGORY_PROTOCOL      =    1
   LCM_CATEGORY_INTERFACE     =    2
   LCM_CATEGORY_INTERNAL      =    3
   LCM_CATEGORY_RESOURCE      =    4
   LCM_CATEGORY_PSF_FTHA      =    5
   LCM_CATEGORY_PERF_MONIT    =    6

   LCZ_USTA_DGNVAL_NONE       =    1
   LCZ_USTA_DGNVAL_MEM        =    2
   LCZ_USTA_DGNVAL_SAPID      =    3
   LCZ_USTA_DGNVAL_PEER       =    4
   LCZ_USTA_DGNVAL_UE         =    5
   LCZ_USTA_DGNVAL_CONID      =    6
   LCZ_USTA_DGNVAL_DATA       =    7

   LCZ_REASON_PROTCFG_NOT_DONE   =    257
   LCZ_REASON_HASHINIT_FAIL      =    259
   LCZ_REASON_SAP_ASSOC_EXISTS   =    260
   LCZ_REASON_LSAPCFG_NOT_DONE   =    261
   LCZ_REASON_DUP_AUDIT_REQ      =    262

   LCZ_EVENT_LI_BND_CFM         =  257
   LCZ_EVENT_LI_ENDP_OPEN_CFM   =  258
   LCZ_EVENT_LI_ENDP_CLOSE_CFM  =  259
   LCZ_EVENT_LI_ASSOC_IND       =  260
   LCZ_EVENT_LI_ASSOC_CFM       =  261
   LCZ_EVENT_LI_TERM_IND        =  262
   LCZ_EVENT_LI_TERM_CFM        =  263
   LCZ_EVENT_LI_FLC_IND         =  264
   LCZ_EVENT_LI_DAT_IND         =  265
   LCZ_EVENT_LI_STA_IND         =  266
   LCZ_EVENT_UI_MSG_PEER        =  267
   LCZ_EVENT_UI_INV_EVT         =  268
   LCZ_EVENT_UI_PEERASSOC_RSP   =  269
   LCZ_EVENT_LI_COMM_UP         = 272
   LCZ_EVENT_DMEM_ALLOC_PASS    =  268
   LCZ_EVENT_LI_NET_DOWN        = 274

   LCZ_CAUSE_CONGESTION_RECV    =   257
   LCZ_CAUSE_ASSOC_UP           =   258
   LCZ_CAUSE_ASSOC_DOWN         =   259
   LCZ_CAUSE_PEER_DELETED       =   260
   LCZ_CAUSE_ENDP_OPEN          =   261
   LCZ_CAUSE_EXCEED_CONF_VAL    =   262
   LCZ_CAUSE_OUTRES             =   263
   LCZ_CAUSE_SCT_ENPOPEN_SUCC   =   264
   LCZ_CAUSE_INV_PAR_VAL        =   265
   LCZ_CAUSE_EPCLOSE_OK         =   266
   LCZ_CAUSE_NOT_BIND            =   270
   LCZ_CAUSE_INVALID_SAP         =   271
   LCZ_CAUSE_DYNAM_PEERCFG_OK   =   272
   LCZ_CAUSE_DYNAM_PEERCFG_NOK   =   273
   LCZ_CAUSE_INV_SPID         =   274
   LCZ_CAUSE_SCT_SEND_FAIL     =  275
   LCZ_CAUSE_SCT_NOT_APPL     =  276

   SCT_CAUSE_INV_PAR_VAL        =   11
   SCT_CAUSE_ENDP_OPEN          =   1
   SCT_CAUSE_EXCEED_CONF_VAL    =   4
   SCT_CAUSE_OUTRES             =   3

   CZ_ASSOC_DOWN     =  0 
   CZAC_LCZ_ENB1_PRC =  100
   CZAC_LCZ_ENB2_PRC =  200
   CZAC_LCZ_ENB3_PRC =  300
   CZAC_LCZ_ENB4_PRC =  400
   CZAC_NODE_ENB     =  2
   CZAC_NODE_MME     =  1
   CZAC_LCZ_INV_NODE =  10
   CZAC_SCTP_DM      =  1000
   LCZ_SAP_CFG       =   1
   LCZ_SAP_ISBOUND   =   2
   LCZ_SAP_BINDING   =   3
   LCZ_SAP_UBND      =   4
   STCZGEN           =   1
   STCZPROT          =   2
   STCZCZTSAP        =   3
   STCZSCTSAP        =   4
   STCZPEER          =   5
   STCZSID           =   6
   CZAC_PRC0         =  0
   CZAC_PRC1         =  1
   CZAC_PRC2         =  2
   CZAC_PRC3         =  3

   CM_IPV4ADDR_TYPE  =  4   

   CZT_ND_ST_IDLE         = 4 
   CZT_ND_ST_SETUP_IN_PRG = 3 
   CZT_ND_ST_NORMAL       = 2 
   CZT_ND_ST_RESET        = 1 
   CZT_CON_ST_IDLE        = 0  
   CZT_CON_ST_CONNECTING  = 1  
   CZT_CON_ST_ESTBLD      = 2  
   CZT_CON_ST_RELEASING   = 3  
   CZT_CON_ST_NON_EXST    = 0xF

   CZT_AUD_UNKNOWN        = 0   
   CZT_AUD_PEER           = 1   
   CZT_AUD_FLC            = 2   

   CZT_STACAUSE_INV_TYPE  = 1
   CZT_STACAUSE_NOT_APPL  = 2

   CZ_GP_IDLE             = 0
   CZ_GP_CONNECTING       = 1
   CZ_GP_CONNECTED        = 2 
   CZ_GP_STATE_MAX        = 3



   CZT_STATUS_FLC_START          =  1 
   CZT_STATUS_FLC_DROP           =  2 
   CZT_STATUS_FLC_STOP           =  3 
   CZT_STATUS_FLC_ACTIVE         =  4 
   CZT_STATUS_FLC_INACTIVE       =  5 
   SCT_FLC_START          =  1    
   SCT_FLC_DROP           =  2    
   SCT_FLC_STOP           =  3    
   SCT_FLC_ACTIVE         =  4    
   SCT_FLC_INACTIVE       =  5    

   CZAC_ENB1_PROC          =  100 
   CZAC_XTA_PROC          =  100 
   CZAC_ENB2_PROC          =  200 

   LCM_CATEGORY_INTERFACE = 2
   LCZ_EVENT_LI_ENDP_OPEN_CFM = 258
   LCZ_CAUSE_SCT_ENPOPEN_SUCC = 264
   LCZ_USTA_DGNVAL_SAPID = 3

   CZT_MSG_HO_REQ          =    0
   CZT_MSG_HO_ACK          =    1
   CZT_MSG_HO_FAIL         =    2
   CZT_MSG_HO_CANCEL       =    3
   CZT_MSG_SN_STATUS_TRFR  =    4
   CZT_MSG_UE_CXT_RELEASE  =    5
   CZT_MSG_LOAD_IND        =    6
   CZT_MSG_ERR_IND         =    7
   CZT_MSG_X2_SETUP        =    8
   CZT_MSG_X2_SETUP_RSP    =    9
   CZT_MSG_X2_SETUP_FAIL   =   10
   CZT_MSG_RESET           =   11 
   CZT_MSG_RESET_RSP       =   12
   CZT_MSG_CFG_UPD_REQ     =   13
   CZT_MSG_CFG_UPD_ACK     =   14
   CZT_MSG_CFG_UPD_FAIL    =   15
   CZT_MSG_RSRC_ST_REQ     =   16
   CZT_MSG_RSRC_ST_RSP     =   17
   CZT_MSG_RSRC_ST_FAIL    =   18
   CZT_MSG_RSRC_ST_UPD     =   19
   # cm_xta_py_py_001.main_45  : X2AP 3.1
   CZT_MSG_MOB_CHANGE_REQ  =   20
   CZT_MSG_MOB_CHANGE_ACK  =   21
   CZT_MSG_MOB_CHANGE_FAIL =   22
   CZT_MSG_RLF_INDICATION  =   23
   CZT_MSG_HO_REPORT       =   24
   CZT_MSG_CELL_ACTIVATION_REQ = 25
   CZT_MSG_CELL_ACTIVATION_RES = 26
   CZT_MSG_CELL_ACTIVATION_FAIL = 27
   CZT_MSG_PRIV_MSG        =   28
   
   CZT_MSG_ID_NO_MSG = 255

   CZAC_START = 1
   CZAC_STOP = 2

   CZT_STA_TYPE_FLC      = 1
   CZT_STA_TYPE_ASSOC    = 2
   CZT_STA_TYPE_TMR_EXPIRY = 4
   CZT_STA_TYPE_TMR_START  = 5

   CZT_STATUS_ASSOC_DOWN   =  1
   CZT_STATUS_ASSOC_UP     =  2
   CZT_STATUS_FLOW         =  3
   CZT_STATUS_UE_TRELOCPREP_EXPIRY     =   6
   CZT_STATUS_UE_TX2RELOCOVERALL_EXPIRY =  7
   CZT_STATUS_SETUPREQ_TMR_STARTED      = 8
   CZT_STATUS_CFGUPD_TMR_STARTED        = 9
   CZT_STATUS_SETUPREQ_TW_EXPIRY        = 10
   CZT_STATUS_CFGUPD_TW_EXPIRY          = 11

   CZT_REASON_NOT_APPL       =  0
   CZT_REASON_RCVD_TERMIND   =  1
   CZT_REASON_RCVD_COMM_UP   =  2
   CZT_REASON_RCVD_NET_UP    =  3
   CZT_REASON_RCVD_NET_DOWN  =  4
   CZT_REASON_SCT_SEND_FAIL  =  5
   CZT_REASON_UBND_SAP       =  6
   CZT_REASON_FLC_START      =  7
   CZT_REASON_FLC_STOP       =  100
   CZT_REASON_DYNAM_PEER_NOT_CFG = 15

# All Error Cause Types
   CZT_ERRTYPE_NONE             = 0x000 
   CZT_ERRTYPE_INV_SDU_PARAM    = 0x010
   CZT_ERRTYPE_ENC_FAILED       = 0x020
   CZT_ERRTYPE_DEC_FAILED       = 0x030
   CZT_ERRTYPE_INV_PARAM        = 0x040
   CZT_ERRTYPE_MSG_SEND_FAILED  = 0x050
   CZT_ERRTYPE_INTERNAL         = 0x060
   CZT_ERRTYPE_SYS              = 0x070
   CZT_ERRTYPE_FROM_PEER        = 0x080

# All Error Cause values set for X2AP
   CZT_ERRCAUSE_MEM_ALLOC_FAIL    =      CZT_ERRTYPE_SYS + 1
   CZT_ERRCAUSE_HASH_INS_FAIL     =      CZT_ERRTYPE_SYS + 2 
   CZT_ERRCAUSE_UE_CB_CREATE_FAILED =    CZT_ERRTYPE_SYS + 3
   CZT_ERRCAUSE_RSRC_CB_CREATE_FAILED =  CZT_ERRTYPE_SYS + 4
   CZT_ERRCAUSE_TMR_ERR               =  CZT_ERRTYPE_SYS + 5
   CZT_ERRCAUSE_PEER_CB_CREATE_FAILED =  CZT_ERRTYPE_SYS + 6

# Type CZT_ERRTYPE_ENC_FAILED and CZT_ERRTYPE_DEC_FAILED
   CZT_ERRCAUSE_SYNTAX_ERR           =   CZT_ERRTYPE_ENC_FAILED + 1
   CZT_ERRCAUSE_MAND_PARAM_MISSING   =   CZT_ERRTYPE_ENC_FAILED + 2

   CZT_ERRCAUSE_INV_STATE           =    CZT_ERRTYPE_INTERNAL + 1
   CZT_ERRCAUSE_UNEXP_MSG           =    CZT_ERRTYPE_INTERNAL + 2
   CZT_ERRCAUSE_NODE_RESET          =    CZT_ERRTYPE_INTERNAL + 3
   CZT_ERRCAUSE_MAX_PEER_CONN       =    CZT_ERRTYPE_INTERNAL + 4
   CZT_ERRCAUSE_MAX_UE_CONN         =    CZT_ERRTYPE_INTERNAL + 5
   CZT_ERRCAUSE_WAIT_TMR_ON         =    CZT_ERRTYPE_INTERNAL + 6
   CZT_ERRCAUSE_PARALLEL_CFGUPD_TRANS =  CZT_ERRTYPE_INTERNAL + 7

# For messages coming from UI the errorType will be CZT_ERRTYPE_INV_SDU_PARAM
# and for incoming messages it will be CZT_ERRTYPE_INV_PARAM 
   CZT_ERRCAUSE_INV_PEERID             =     CZT_ERRTYPE_INV_PARAM + 1
   CZT_ERRCAUSE_INV_OLD_UE_X2AP_ID     =     CZT_ERRTYPE_INV_PARAM + 2
   CZT_ERRCAUSE_INV_NEW_UE_X2AP_ID     =     CZT_ERRTYPE_INV_PARAM + 3
   CZT_ERRCAUSE_INV_ENB_ID             =     CZT_ERRTYPE_INV_PARAM + 4
   CZT_ERRCAUSE_INV_ENB1_MEAS_ID       =     CZT_ERRTYPE_INV_PARAM + 5
   CZT_ERRCAUSE_INV_ENB2_MEAS_ID       =     CZT_ERRTYPE_INV_PARAM + 6
   CZT_ERRCAUSE_DUPLICATE_PEERID       =     CZT_ERRTYPE_INV_PARAM + 7
   CZT_ERRCAUSE_DUPLICATE_OLD_UE_X2AP_ID  =  CZT_ERRTYPE_INV_PARAM + 8
   CZT_ERRCAUSE_DUPLICATE_ENB1_MEAS_ID    =  CZT_ERRTYPE_INV_PARAM + 9
   CZT_ERRCAUSE_DUPLICATE_ENB2_MEAS_ID    =  CZT_ERRTYPE_INV_PARAM + 0x0A
   CZT_ERRCAUSE_PARAM_OUT_OF_BOUNDS       =  CZT_ERRTYPE_INV_PARAM + 0x0B

# CZT_ERRTYPE_MSG_SEND_FAILED 
   CZT_ERRCAUSE_SAP_NOTPRST              =   CZT_ERRTYPE_MSG_SEND_FAILED + 1
   CZT_ERRCAUSE_SAP_NOT_BOUND            =   CZT_ERRTYPE_MSG_SEND_FAILED + 2
   CZT_ERRCAUSE_ASSOC_NOTPRST            =   CZT_ERRTYPE_MSG_SEND_FAILED + 3
   CZT_ERRCAUSE_ENC_FAILED               =   CZT_ERRTYPE_MSG_SEND_FAILED + 4
   CZT_ERRCAUSE_MSG_NOT_DELIVERED        =   CZT_ERRTYPE_MSG_SEND_FAILED + 5


   CAUSE_RADIONW  = 0
   CAUSE_TRANSPORT  = 1
   CAUSE_PROTOCOL  = 2
   CAUSE_MISC  = 3
   CAUSE_ERR  = 4

# For Dynamic Peer Allocation Feature -- DPA
   CZT_STA_TYPE_PEER = 3
   CZT_REASON_NOT_APPL = 0
   CZT_REASON_INV_PEERID = 12
   CZT_REASON_INV_RELTYPE = 13 
   CZT_REASON_INV_UEID = 16 
   CZT_REASON_INV_RSRCID = 17
   CZT_REASON_INV_IDTYPE = 18
   CZT_STATUS_DYNAM_PEERCFG_OK = 4
   CZT_STATUS_DYNAM_PEERCFG_NOK = 5
   CZT_PRIM_OK = 0
   CZT_PRIM_NOK = 1
   CZT_CAUSE_NOT_APPL = 2
   CZT_CAUSE_INV_PEERID = 4 

   CZT_LOCAL_REL = 1
   CZT_CXT_REL = 0
   CZT_CONN_TYPE_SU = 0
   CZT_CONN_TYPE_SP = 1

# LTE X2AP: For various flavours of release
   CZT_RELTYPE_INVALID =   0
   CZT_RELTYPE_RESET =   1
   CZT_RELTYPE_TERM  =   2
   CZT_RELTYPE_UE    =   3
   CZT_RELTYPE_RSRC  =   4

   CZT_NODETYPE_INVALID =   0
   CZT_NODETYPE_LOCAL =   1
   CZT_NODETYPE_REMOTE =  2


#For NG Values in DUMMY CRG config for LTE MAC
   RGAC_RGR_NG_ONESIXTH  = 0
   RGAC_RGR_NG_HALF = 1
   RGAC_RGR_NG_ONE = 2
   RGAC_RGR_NG_TWO = 3
   RGAC_RGR_NG_ERR_THREE = 4
   RGAC_RGR_NG_ERR = -1
   #For Tx Mode values
   RGR_UE_TM_1 = 1
   RGR_UE_TM_2 = 2
   RGAC_RGR_UE_TM_3 = 3
   RGAC_RGR_UE_TM_4 = 4
   RGAC_RGR_UE_TM_5 = 5
   RGAC_RGR_UE_TM_6 = 6
   RGAC_RGR_UE_TM_7 = 7
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   RGR_UE_TM_3 = 3
   RGR_UE_TM_4 = 4
   RGR_UE_TM_5 = 5
   RGR_UE_TM_6 = 6
   RGR_UE_TM_7 = 7
   CRG_UE_TM_1 = 1
   CRG_UE_TM_2 = 2
   CRG_UE_TM_3 = 3
   CRG_UE_TM_4 = 4
   CRG_UE_TM_5 = 5
   CRG_UE_TM_6 = 6
   CRG_UE_TM_7 = 7
   TFU_UE_TM_1 = 1
   TFU_UE_TM_2 = 2
   TFU_UE_TM_3 = 3
   TFU_UE_TM_4 = 4
   TFU_UE_TM_5 = 5
   TFU_UE_TM_6 = 6
   TFU_UE_TM_7 = 7
   TFU_RPT_CQI = 0
   TFU_RPT_RI = 1
   RGAC_RGR_UE_TM_ERR = 8
   RGAC_ACKNACK_REPFACT_N2_ERR = 8
   RGAC_RGR_APRD_CQI_MOD12 = 0 
   RGAC_RGR_APRD_CQI_MOD20 = 1 
   RGAC_RGR_APRD_CQI_MOD22 = 2 
   RGAC_RGR_APRD_CQI_MOD30 = 3 
   RGAC_RGR_APRD_CQI_MOD31 = 4
   RGAC_RGR_APRD_CQI_MODERR = 5
   RGAC_RGR_PRD_CQI_MOD10 = 0 
   RGAC_RGR_PRD_CQI_MOD11 = 1 
   RGAC_RGR_PRD_CQI_MOD20 = 2 
   RGAC_RGR_PRD_CQI_MOD21 = 3
   RGAC_RGR_PRD_CQI_MODERR = 4
   RGAC_RGR_CELL_CFG  = 1
   RGAC_RGR_UE_CFG    = 2
   RGAC_RGR_LCH_CFG   = 3 
   RGAC_RGR_LCG_CFG   = 4
   RGAC_RGR_ENB_CFG  = 5
   RGAC_CRG_CELL_CFG  = 1 
   RGAC_CRG_UE_CFG    = 2
   RGAC_CRG_LCH_CFG   = 3
   CM_LTE_UE_CAT_1 = 1
   CM_LTE_UE_CAT_2 = 2
   CM_LTE_UE_CAT_3 = 3
   CM_LTE_UE_CAT_4 = 4
   CM_LTE_UE_CAT_5 = 5
   RGR_TDD_ACKNACK_MODE_BUNDL = 0
   RGR_TDD_ACKNACK_MODE_MULT = 1
   RG_ACC_PLUS = 1
   RG_ACC_MINUS = 2
   STTFUSAP = 5
   STRGRSAP = 3
   STCRGSAP = 2
   RGR_ACKNACK_REPFACT_N2 = 2
   RGR_ACKNACK_REPFACT_N4 = 4
   RGR_ACKNACK_REPFACT_N6 = 6
   RGAC_RGR_SRS_BWCFG_0 = 0
   RGAC_RGR_SRS_BWCFG_1 = 1
   RGAC_RGR_SRS_BWCFG_2 = 2
   RGAC_RGR_SRS_BWCFG_3 = 3
   RGAC_RGR_SRS_BWCFG_4 = 4
   RGAC_RGR_SRS_BWCFG_5 = 5
   RGAC_RGR_SRS_BWCFG_6 = 6
   RGAC_RGR_SRS_BWCFG_7 = 7
   RGAC_RGR_SRS_BWCFG_ERR = 8
   RGAC_RGR_SRS_CFG_PRD_1 = 1
   RGAC_RGR_SRS_CFG_PRD_2 = 2 
   RGAC_RGR_SRS_CFG_PRD_5 = 5 
   RGAC_RGR_SRS_CFG_PRD_10 = 10
   RGAC_RGR_SFN_EVEN = 0
   RGAC_RGR_SFN_ANY = 1
   RGAC_RGR_SFN_NA = 2
   RGAC_RGR_SI_CFG_TYPE_MIB = 0
   RGAC_RGR_SI_CFG_TYPE_SIB1 = 1
   RGAC_RGR_SI_CFG_TYPE_SI = 2
   RGAC_RGR_SI_CFG_TYPE_INV = 3
   RGAC_TFU_DCIFMT_0 = 0
   RGAC_TFU_DCIFMT_1 = 1
   RGAC_TFU_DCIFMT_1A = 2
   TFU_CQI_MODE20 = 0
   TFU_CQI_MODE30 = 1
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   TFU_PUSCH_CQI_MODE_12 = 0
   TFU_PUSCH_CQI_MODE_20 = 1
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   TFU_PUSCH_CQI_MODE_22 = 2 
   TFU_PUSCH_CQI_MODE_30 = 3
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   TFU_PUSCH_CQI_MODE_31 = 4
   TFU_DCI_FORMAT_2      = 6
   RGR_TXMODE_RECFG_CMPLT = 0
   RGR_TXMODE_RECFG_START = 1
   TFU_HQ_ACK = 1
   TFU_HQ_NACK = 2
   TFU_HQ_ACK_OR_NACK = 3
   TFU_HQ_DTX = 4
   TFU_HQ_ACK_OR_DTX = 5
   TFU_HQ_NACK_OR_DTX = 6
   TFU_HQ_ACK_OR_NACK_OR_DTX =7
   TFU_HQ_DTX = 4
   RGR_SPS_E2 = 2
   RGR_SPS_E3 = 3
   RGR_SPS_E4 = 4
   RGR_SPS_E8 = 8
   RGR_SPS_PRD_10SF = 10 
   RGR_SPS_PRD_20SF = 20 
   RGR_SPS_PRD_32SF = 32 
   RGR_SPS_PRD_40SF = 40 
   RGR_SPS_PRD_64SF = 64 
   RGR_SPS_PRD_80SF = 80 
   RGR_SPS_PRD_128SF = 128 
   RGR_SPS_PRD_160SF = 160 
   RGR_SPS_PRD_320SF = 320 
   RGR_SPS_PRD_640SF = 640 
   RGR_SPS_PRD_INVALID = 0
   RGAC_RGR_UE_TX_ANT_OPENLOOP = 0
   RGAC_RGR_UE_TX_ANT_CLOSEDLOOP = 1
#cm_xta_py_py_001.main_44 - ADD - New feature defines
   RGRUE_DLPWRCNTRL_PA_DB_6 = 0
   RGRUE_DLPWRCNTRL_PA_DB_4DOT77 = 1
   RGRUE_DLPWRCNTRL_PA_DB_3 = 2
   RGRUE_DLPWRCNTRL_PA_DB_1DOT77 = 3
   RGRUE_DLPWRCNTRL_PA_DB0 = 4
   RGRUE_DLPWRCNTRL_PA_DB1 = 5
   RGRUE_DLPWRCNTRL_PA_DB2 = 6
   RGRUE_DLPWRCNTRL_PA_DB3 = 7

   RGR_REL_8 = 0
   RGR_REL_9 = 1
   RGR_REL_10 = 2
   RGR_REL_SPARE_5 = 3
   RGR_REL_SPARE_4 = 4
   RGR_REL_SPARE_3 = 5
   RGR_REL_SPARE_2 = 6
   RGR_REL_SPARE_1 = 7

# For EGTP 
   LEG_TSAP_TYPE_TUCL = 1
   LEG_TRC_EVENT_RX = 1
   LEG_TRC_EVENT_TX = 2
   LEG_TSAP_TYPE_DTUCL = 2
   LEG_GTP_ENT_MME = 1
   LEG_GTP_ENT_SGW = 2
   LEG_GTP_ENT_PGW = 3
   LEG_GTP_ENT_SGSN = 4
   LEG_GTP_ENT_MBMSGW = 5
#cm_xta_py_py_001.main_56 - S2B and S2A 
   LEG_GTP_ENT_MSC = 6
   LEG_GTP_ENT_EPDG = 7
   LEG_GTP_ENT_TWAN = 8
   LEG_GTP_ENT_UNKNWN = 0
   LEG_INV_GEN_CNTRL_ACTION = 3
   LEG_INV_GEN_CNTRL_SUBACTION = 0
   LEG_INV_USAP_CNTRL_ACTION = 0
   LEG_INV_LSAP_CNTRL_ACTION = 0
   LEG_INV_TSRV_CNTRL_ACTION = 0

   LEG_EVENT_TPTSRV_ENA = 257 
   LEG_EVENT_TPTSRV_DIS = 258 
   LEG_EVENT_USAP_DIS   = 259
   LEG_EVENT_HIT_BNDCFM = 260 
   LEG_EVENT_HIT_DISCIND = 261
   LEG_EVENT_HIT_DISCCFM = 262
   LEG_EVENT_HIT_UDATIND = 263
   LEG_EVENT_HIT_FLCIND  = 264
   LEG_EVENT_DMEM_ALLOC_PASS = 265
   LEG_EVENT_HIT_CONCFM      = 266
   LCM_EVENT_UBND_OK         = 19
   LEG_CAUSE_SAP_BND         = 257
   LEG_CAUSE_SAP_UBND        = 258
   LEG_CAUSE_SAP_BNDDIS      = 259
   LEG_CAUSE_SAP_BNDENA      = 260
   LEG_CAUSE_LI_INITIATED    = 261
   LEG_CAUSE_TPT_FAIL        = 262
   LEG_CAUSE_DST_IP_DEL      = 263
   LEG_CAUSE_LCL_PORT_NOT_REACHABLE = 264
   LEG_CAUSE_DST_IP_NOT_REACHABLE = 265
   LEG_CAUSE_PENDING_CNTRL_OP = 266

   LEG_CAUSE_DST_IP_REACHABLE = 269
   LEG_CAUSE_DST_IP_NOT_CONFIG = 270

   LEG_PAR_USAP = 1
   LEG_PAR_MEM = 2
   LEG_PAR_TSAP = 3
   LEG_PAR_IECODE = 4
   LEG_PAR_TSRV = 5
   LEG_PAR_GEN = 6
   LEG_PAR_CONNID = 7
   LEG_PAR_IP = 8
   LEG_PAR_PORT = 9

   STEGGEN = 1
   STEGUSAP = 2
   STEGTSAP = 3
   STEGSRVR = 4
   STEGMSG = 5
   STEGIE = 6
   STEGSID = 7
   EGT_STATYPE_PATH  = 1
   EGT_STATYPE_TUNNEL = 2

   # cm_xta_py_py_001.main_53 : parm for inidcating the creation of dummy tunnel
   DUMMY = 2

# Added for eGTPU
   LEG_NODE_UMTS =  0
   LEG_NODE_LTE =  1
   STEGTHRD = 9
   STEGSRVR = 4
   STEGIPADDR = 8
   STEGTNL = 10
   EGT_GTPU_MSG_ECHO_REQ = 1
   EGT_GTPU_MSG_ECHO_RSP = 2
   EGT_GTPU_MSG_INVALID  = 0 
   EGT_GTPU_MSG_GPDU = 255
   EGT_GTPU_MSG_END_MARKER = 254
   EGT_GTPU_MSG_ERROR_IND  = 26
   EGT_GTPU_MSG_SUPP_EXT_HDR_NTF = 31
   EGU_IE_EXT_HDR_LST = 141
   ROKPENDING = 16
   EGU_IE_RECOVERY = 14
   EGU_IE_TEID     = 16
   EGU_IE_GSN_ADDR  = 133
   EGU_IE_PVT_EXTN  = 255
   LEG_MOVE_IP = 107

   EGT_GTPU_DEST_UNREACHABLE = 3
   EGT_GTPU_DEST_REACHABLE = 2
   EGT_GTPU_PORT_ACTIVE = 0
   EGT_GTPU_PORT_INACTIVE = 1
   LEG_REASON_INV_PROTFLAG = 82
   LEG_REASON_FOUND_IP_ADDR_FAILED = 71
   LEG_REASON_DFLT_PORT_NOT_OPEANED = 78
   CM_TPTADDR_NOTPRSNT = 0
   LEG_REASON_INVALID_IP_TYPE = 70
   LEG_REASON_INVALID_PORT = 81
   LEG_REASON_USAPCFG_NOT_DONE = 80
   LEG_REASON_IP_EXISTS = 68
   LEG_REASON_FOUND_DEST_ADDR_FAILED = 76
   LEG_REASON_FOUND_TEID_FAILED = 77
   LEG_REASON_FOUND_TPT_ADDR_FAILED = 75

# For LTE-RRC
   LNH_REASON_PROTCFG_NOT_DONE = 256
   LNH_REASON_LSAPCFG_NOT_DONE = 257
   LNH_REASON_USAPCFG_NOT_DONE = 258
   LNH_REASON_UE_DOES_NOT_EXIST = 259
   LNH_REASON_DUP_SAP_ENTRY = 260
   LNH_REASON_SEL_VAL_NOT_ALLOWED = 261
   LNH_REASON_SHUTDOWN_TMR_EXPD = 262
   LNH_REASON_CELL_DOES_NOT_EXIST = 263

# Iuh release 2.1
   HMAC_SCTP_DM             =  1000
   LHM_TYPE_HNB             =  1
   LHM_TYPE_HNBGW           =  2   
   LHM_TYPE_INVALID         =  3   
   STHMSCTSAP               =  4   
   STHMPEER                 =  5   
   ASHMESTABLISH            =  4
   ASHMTERMINATE            =  5   
   SAELMNT                  =  1   
   HMAC_RUA_CONNECT         =  1   
   HMAC_RUA_DIRECT_TRANSFER =  2   
   HMAC_RUA_DISCONNECT      =  3
   HMAC_RUA_CONNECTION_LESS =  4
   HMAC_RUA_ERR_IND         =  5
   HMAC_HNBAP_HNB_REG_REQ   =  1
   HMAC_HNBAP_HNB_REG_ACC   =  2
   HMAC_HNBAP_HNB_REG_REJ   =  3
   HMAC_HNBAP_UE_REG_REQ    =  4
   HMAC_HNBAP_UE_REG_ACC    =  5
   HMAC_HNBAP_UE_REG_REJ    =  6
   HMAC_HNBAP_HNB_DEREG_REQ =  7
   HMAC_HNBAP_UE_DEREG_REQ  =  8
   HMAC_HNBAP_ERR_IND_PROC  =  9
   HMAC_HNBAP_CSG_UPD_REQ   =  10
   HMAC_HNT_LCL_ERR         =  0
   HMAC_HNT_PEER_ERR        =  1
   HNT_ERRCAUSE_INV_MSG     =  2
   HNT_ERRCAUSE_ENC_FAILED  =  5
   HNT_ERRCAUSE_UE_NOT_REG  =  11
   HNT_ERRCAUSE_HNB_NOT_REG =  12
   HNT_ERRCAUSE_INV_PEERID  =  15
   HNT_ERRCAUSE_NO_PEERID   =  16
   HNT_ERRCAUSE_UNEXP_MSG   =  17
   HNT_ERRCAUSE_NO_SDU      =  18
   HNT_ERRCAUSE_INV_LSAPCB  =  23
   HNT_ERRCAUSE_NO_UE_CNTXID =  25
   HNT_ERRCAUSE_ERRONEOUS_RSP = 26
   HNT_ERRCAUSE_RADNWHNB_NOT_REG = 9
   HNT_ACC_STRTM_REL_IND_8_BEYOND = 5
   HNT_ERRCAUSE_PROT_NOT_COMPATBLE_RCVR_STATE = 3
   HNT_ERRCAUSE_PROT_TRANSFER_SYNTX_ERR = 0
   HNT_ERRCAUSE_PROT_ABS_SYNTX_REJ = 1
   HNT_ERRCAUSE_PROT_ABS_SYNTX_ERR_FALSE_CONST_MSG = 6
   HMAC_RUA                 =  0
   HMAC_HNBAP               =  1
   HMAC_INV                 =  2
   CUS_RADIONW              =  0
   HntCusRadNwoverloadEnum  =  0
   RutCusRadNwnormalEnum    =  0
   HMAC_UNKNOWN_IE          =  3
   HMAC_LOGICVOIL_IE        =  4
   HMAC_OUTOFORD_IE         =  2
   HMAC_MULTOCC_IE          =  1
   LHM_CAUSE_SCT_ENPOPEN_SUCC = 264
   LHM_EVENT_LI_ENDP_OPEN_CFM = 258
   LHM_TRC_PNODE              =    1
   LHM_TRC_LSAP_IN            =    2
   LHM_TRC_LSAP_OUT           =    4
   LHM_TRC_PNODE_IN           =    8
   LHM_TRC_PNODE_OUT          =   16
   LHM_INV_ZEROSTS            = 3
   # Iuh 2.1 release
   RUT_CAUSE_INV_CTXT_DMN_ID  = 14
   RUT_CAUSE_INV_DMN_ID       = 15
   RUT_CAUSE_INV_PDU          = 16
   RUT_CAUSE_PC_ABS_SYNTAX_ERR=  8
   LHM_CAUSE_CONGESTION_RECV = (LCM_CAUSE_LYR_SPECIFIC + 1)
   LHM_CAUSE_ASSOC_UP   =      (LCM_CAUSE_LYR_SPECIFIC + 2)
   LHM_CAUSE_ASSOC_DOWN  =     (LCM_CAUSE_LYR_SPECIFIC + 3)
   LHM_CAUSE_PEER_DELETED  =   (LCM_CAUSE_LYR_SPECIFIC + 4)
   LHM_CAUSE_ENDP_OPEN     =   (LCM_CAUSE_LYR_SPECIFIC + 5)
   LHM_CAUSE_EXCEED_CONF_VAL = (LCM_CAUSE_LYR_SPECIFIC + 6)
   LHM_CAUSE_OUTRES        =   (LCM_CAUSE_LYR_SPECIFIC + 7)
   LHM_CAUSE_SCT_ENPOPEN_SUCC =(LCM_CAUSE_LYR_SPECIFIC + 8)
   LHM_CAUSE_EPCLOSE_OK   =    (LCM_CAUSE_LYR_SPECIFIC + 9)
   LHM_CAUSE_SAP_BND      =    (LCM_CAUSE_LYR_SPECIFIC + 10)
   LHM_CAUSE_SAP_UBND      =   (LCM_CAUSE_LYR_SPECIFIC + 11)
   LHM_CAUSE_INV_PEER      =   (LCM_CAUSE_LYR_SPECIFIC + 12)
   LHM_CAUSE_INV_UE        =   (LCM_CAUSE_LYR_SPECIFIC + 13)
   LHM_CAUSE_HNB_REG_TMR_EXP = (LCM_CAUSE_LYR_SPECIFIC + 14)
   LHM_CAUSE_SCT_BND_TMR_EXP = (LCM_CAUSE_LYR_SPECIFIC + 15)
   LHM_CAUSE_TMR_EXPIRED     = (LCM_CAUSE_LYR_SPECIFIC + 16)
   LHM_CAUSE_RETRY_EXCEED   =  (LCM_CAUSE_LYR_SPECIFIC + 17)
   LHM_CAUSE_FLC_DROP      =   (LCM_CAUSE_LYR_SPECIFIC + 18)
   LHM_EVENT_LI_BND_OK       = (LCM_EVENT_LYR_SPECIFIC + 1)
   LHM_EVENT_RUT_BND_OK      = (LCM_EVENT_LYR_SPECIFIC + 2)
   LHM_EVENT_HNT_BND_OK     =  (LCM_EVENT_LYR_SPECIFIC + 3)
   LHM_EVENT_EOPEN_OK      =   (LCM_EVENT_LYR_SPECIFIC + 4)
   LHM_EVENT_LI_ENDP_CLOSE_CFM = (LCM_EVENT_LYR_SPECIFIC + 5)
   LHM_EVENT_LI_ASSOC_IND  =    (LCM_EVENT_LYR_SPECIFIC + 6)
   LHM_EVENT_LI_ASSOC_CFM   =   (LCM_EVENT_LYR_SPECIFIC + 7)
   LHM_EVENT_LI_TERM_IND     =  (LCM_EVENT_LYR_SPECIFIC + 8)
   LHM_EVENT_LI_TERM_CFM      = (LCM_EVENT_LYR_SPECIFIC + 9)
   LHM_EVENT_LI_FLC_IND        =(LCM_EVENT_LYR_SPECIFIC + 10)
   LHM_EVENT_DMEM_ALLOC_PASS  = (LCM_EVENT_LYR_SPECIFIC + 11)
   LHM_EVENT_UI_SAP_UBND_SUCC = (LCM_EVENT_LYR_SPECIFIC + 12)
   LHM_EVENT_LI_DAT_IND    =    (LCM_EVENT_LYR_SPECIFIC + 13)
   LHM_EVENT_LI_STA_IND    =    (LCM_EVENT_LYR_SPECIFIC + 14)
   LHM_EVENT_MAX_PEERS_REACHED = (LCM_EVENT_LYR_SPECIFIC + 15)
   LHM_EVENT_MAX_UES_REACHED  =   (LCM_EVENT_LYR_SPECIFIC + 16)
   LHM_EVENT_EOPEN_FAIL      =   (LCM_EVENT_LYR_SPECIFIC + 17)
   LHM_EVENT_TERM_FAIL        =  (LCM_EVENT_LYR_SPECIFIC + 18)
   LHM_EVENT_ECLOSE_OK        =  (LCM_EVENT_LYR_SPECIFIC + 19)
   LHM_EVENT_ECLOSE_NOK       =  (LCM_EVENT_LYR_SPECIFIC + 20)
   LHM_EVENT_SCTP_FLCIND      =  (LCM_EVENT_LYR_SPECIFIC + 21)
   LHM_EVENT_SCTP_ASSOC_UP    =  (LCM_EVENT_LYR_SPECIFIC + 22)
   LHM_EVENT_SCTP_SND_FAIL   =   (LCM_EVENT_LYR_SPECIFIC + 23)
   LHM_EVENT_ERRIND_NOK      =   (LCM_EVENT_LYR_SPECIFIC + 24)
   LHM_EVENT_REGREQ_OK       =   (LCM_EVENT_LYR_SPECIFIC + 25)
   LHM_EVENT_REGREQ_NOK      =   (LCM_EVENT_LYR_SPECIFIC + 26)
   LHM_EVENT_REGRESP_OK      =   (LCM_EVENT_LYR_SPECIFIC + 27)
   LHM_EVENT_REGRESP_NOK     =   (LCM_EVENT_LYR_SPECIFIC + 28)
   LHM_EVENT_DEREGREQ_OK     =   (LCM_EVENT_LYR_SPECIFIC + 29)
   LHM_EVENT_DEREGREQ_NOK    =   (LCM_EVENT_LYR_SPECIFIC + 30)
   LHM_EVENT_TIMEOUT         =   (LCM_EVENT_LYR_SPECIFIC + 31)
   LHM_EVENT_LI_STA_CFM      =   (LCM_EVENT_LYR_SPECIFIC + 32)
   LHM_SAP_CFG               =    1
   LHM_SAP_ISBOUND           =    2
   LHM_SAP_BINDING           =    3
   LHM_SAP_UBND              =    4

   EG_NORMAL_DATA_TUNN       =    1
   EG_FWD_DATA_TUNN          =    2

   #For RLC L2 Measurement
   LKW_CAUSE_RB_DELETION      = (LCM_CAUSE_LYR_SPECIFIC + 5)
   LKW_CAUSE_INVALID_MEASTYPE = (LCM_CAUSE_LYR_SPECIFIC + 6)
   LKW_CAUSE_EXCEED_NUMMEAS   = (LCM_CAUSE_LYR_SPECIFIC + 7)
   LKW_CAUSE_INVALID_NUMQCI   = (LCM_CAUSE_LYR_SPECIFIC + 8)
   LKW_CAUSE_ZERO_NUMSAM      = (LCM_CAUSE_LYR_SPECIFIC + 9)
   LKW_CAUSE_INVALID_NUMSAM   = (LCM_CAUSE_LYR_SPECIFIC + 10)
   LKW_CAUSE_INVALID_UE       = (LCM_CAUSE_LYR_SPECIFIC + 11)
   LKW_CAUSE_INVALID_QCI      = (LCM_CAUSE_LYR_SPECIFIC + 12)
   LKW_CAUSE_MEAS_ALREADY_ENA = (LCM_CAUSE_LYR_SPECIFIC + 13)
   LPJ_CAUSE_MEM_FAILED       = (LCM_CAUSE_LYR_SPECIFIC + 5)
   LPJ_CAUSE_INVALID_MEASTYPE = (LCM_CAUSE_LYR_SPECIFIC  + 6)
   LPJ_CAUSE_EXCEED_MEASREQ   = (LCM_CAUSE_LYR_SPECIFIC  + 7)
   LPJ_CAUSE_EXCEED_NUMQCI    = (LCM_CAUSE_LYR_SPECIFIC  + 8)
   LPJ_CAUSE_MEAS_ALREADY_ENA = (LCM_CAUSE_LYR_SPECIFIC  + 9)
   LPJ_CAUSE_INVALID_QCI      = (LCM_CAUSE_LYR_SPECIFIC + 10)
   LPJ_CAUSE_ZERO_MEASPERIOD  = (LCM_CAUSE_LYR_SPECIFIC + 11)

   # For RRC Connection Establishment Counters
   KPI_ID_LTE_RRC_ATTCONESTAB_EMERGENCY                     = 0
   KPI_ID_LTE_RRC_ATTCONESTAB_HIGHPRIORITYACCES             = 1
   KPI_ID_LTE_RRC_ATTCONESTAB_MTACCESS                      = 2
   KPI_ID_LTE_RRC_ATTCONESTAB_MOSIGNALLING                  = 3
   KPI_ID_LTE_RRC_ATTCONESTAB_MODATA                        = 4 
   KPI_ID_LTE_RRC_ATTCONESTAB_DE_TO_ACCESS                  = 5
   KPI_ID_LTE_RRC_ATTCONESTAB_SUM                           = 6
   KPI_ID_LTE_RRC_SUCCCONESTAB_EMERGENCY                    = 7
   KPI_ID_LTE_RRC_SUCCCONESTAB_HIGHPRIORITYACCES            = 8
   KPI_ID_LTE_RRC_SUCCCONESTAB_MTACCESS                     = 9
   KPI_ID_LTE_RRC_SUCCCONESTAB_MOSIGNALLING                 = 10
   KPI_ID_LTE_RRC_SUCCCONESTAB_MODATA                       = 11
   KPI_ID_LTE_RRC_SUCCCONESTAB_DE_TO_ACCESS                 = 12
   KPI_ID_LTE_RRC_FAILCONESTAB_EMERGENCY                    = 14
   KPI_ID_LTE_RRC_FAILCONESTAB_DE_TO_ACCESS                 = 19

   #For Handover Counters
   #Inter HO Counters
   KPI_ID_LTE_HO_TOENBATT_SUM                               = 196
   KPI_ID_LTE_HO_TOENBSUCC_SUM                              = 197
   KPI_ID_LTE_HO_S1_BASED_HANDOUT_SUCC_SUM                  = 202  
   KPI_ID_LTE_HO_TOENBFAIL_SUM                              = 198
   KPI_ID_LTE_HO_FROMENBATT_SUM                             = 199
   KPI_ID_LTE_HO_FROMENBSUCC_SUM                            = 200
   KPI_ID_LTE_HO_FROMENBFAIL_SUM                            = 201
   KPI_ID_LTE_HO_S1_BASED_HANDIN_SUCC_SUM                   = 203
   KPI_ID_LTE_HO_INTERENBOUTPREPATT                         = 210
   KPI_ID_LTE_HO_INTRAFREQOUTATT                            = 211
   KPI_ID_LTE_HO_INTRAFREQOUTSUCC                           = 212
   KPI_ID_LTE_HO_INTERFREQMEASGAPOUTATT                     = 213
   KPI_ID_LTE_HO_INTERFREQMEASGAPOUTSUCC                    = 214
   KPI_ID_LTE_HO_NODRXOUTATT                                = 219
   KPI_ID_LTE_HO_NODRXOUTSUCC                               = 220
   KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_CAUSE1               = 413 
   KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_CAUSE1              = 417
   KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_CAUSE1_PER_TGT_CELL  = 421
   KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_SUM_PER_TGT_CELL     = 425
   KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_CAUSE1_PER_TGT_CELL = 426
   KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_SUM_PER_TGT_CELL    = 430 
   #IRAT Counters
   KPI_ID_LTE_INTER_RAT_UTRA_ATT_SUM               = 471 
   KPI_ID_LTE_INTER_RAT_UTRA_SUCC_SUM              = 472
   KPI_ID_LTE_INTER_RAT_UTRA_FAIL_SUM              = 473
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE1 = 474
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE2 = 475
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE3 = 476
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE4 = 477
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE1 = 478  
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE2 = 479
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE3 = 480   
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE4 = 481
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE1 = 482 
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE2 = 483
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE3 = 484
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE4 = 485

   #RIM Counters
   KPI_ID_LTE_RIM_PROC_ATT  = 486 
   KPI_ID_LTE_RIM_PROC_SUCC = 487
   KPI_ID_LTE_RIM_PROC_FAIL = 488

   # CSFB Counters
   KPI_ID_LTE_CSFB_ATT_SUM   =  457
   KPI_ID_LTE_CSFB_SUCC_SUM  =  458
   KPI_ID_LTE_CSFB_FAIL_SUM  =  459
   KPI_ID_LTE_CSFB_UTRA_ATT_SUM = 460
   KPI_ID_LTE_CSFB_UTRA_SUCC_SUM = 461 
   KPI_ID_LTE_CSFB_UTRA_FAIL_SUM = 462
   KPI_ID_LTE_CSFB_UTRA_WITH_REDIR_WITH_SI = 463
   KPI_ID_LTE_CSFB_UTRA_WITHOUT_REDIR = 464 
   KPI_ID_LTE_CSFB_CDMA2000_DUALRX_WO_REDIR = 465
   KPI_ID_LTE_CSFB_CDMA2000_REDIR = 466
   KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_SUCC = 467
   KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_FAIL = 468
   KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_ATT  = 469
   KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_FAIL_REDIR_SUCC = 470
   # GERAN Counters
   KPI_ID_LTE_CSFB_GERAN_ATT_SUM     = 489
   KPI_ID_LTE_CSFB_GERAN_SUCC_SUM    = 490
   KPI_ID_LTE_CSFB_GERAN_REDIR       = 491
   KPI_ID_LTE_CSFB_GERAN_CCO         = 492
   KPI_ID_LTE_CSFB_GERAN_FAIL        = 493
   KPI_ID_LTE_IRAT_MOB_LAI_1   = 494
   KPI_ID_LTE_IRAT_MOB_LAI_2   = 495
   KPI_ID_LTE_IRAT_MOB_LAI_3   = 496
   KPI_ID_LTE_IRAT_MOB_LAI_4   = 497
   KPI_ID_LTE_IRAT_MOB_LAI_5   = 498
   KPI_ID_LTE_IRAT_MOB_LAI_6   = 499
   KPI_ID_LTE_IRAT_MOB_LAI_7   = 500
   KPI_ID_LTE_IRAT_MOB_LAI_8   = 501
   KPI_ID_LTE_IRAT_MOB_LAI_9   = 502
   KPI_ID_LTE_IRAT_MOB_LAI_10   = 503
   KPI_ID_LTE_IRAT_MOB_LAI_11   = 504
   KPI_ID_LTE_IRAT_MOB_LAI_12   = 505
   KPI_ID_LTE_IRAT_MOB_LAI_13   = 506
   KPI_ID_LTE_IRAT_MOB_LAI_14   = 507
   KPI_ID_LTE_IRAT_MOB_LAI_15   = 508
   KPI_ID_LTE_IRAT_MOB_LAI_16   = 509
   KPI_ID_LTE_IRAT_MOB_LAI_17 =  510
   KPI_ID_LTE_IRAT_MOB_LAI_18 =  511
   KPI_ID_LTE_IRAT_MOB_LAI_19 =  512
   KPI_ID_LTE_IRAT_MOB_LAI_20 =  513
   KPI_ID_LTE_IRAT_MOB_LAI_21 =  514
   KPI_ID_LTE_IRAT_MOB_LAI_22 =  515
   KPI_ID_LTE_IRAT_MOB_LAI_23 =  516
   KPI_ID_LTE_IRAT_MOB_LAI_24 =  517
   KPI_ID_LTE_IRAT_MOB_LAI_25 =  518
   KPI_ID_LTE_IRAT_MOB_LAI_26 =  519
   KPI_ID_LTE_IRAT_MOB_LAI_27 =  520
   KPI_ID_LTE_IRAT_MOB_LAI_28 =  521
   KPI_ID_LTE_IRAT_MOB_LAI_29 =  522
   KPI_ID_LTE_IRAT_MOB_LAI_30 =  523
   KPI_ID_LTE_IRAT_MOB_LAI_31 =  524
   KPI_ID_LTE_IRAT_MOB_LAI_32 =  525
   KPI_ID_LTE_IRAT_MOB_LAI_OTH  = 526
   KPI_ID_LTE_CSFB_GERAN_CCO_WITH_NACC = 527
   KPI_ID_LTE_CSFB_GERAN_REDIR_WITH_SI = 528
   KPI_ID_LTE_HO_FROMENBSUCC_SUM_AFTR_REEST = 529
   KPI_ID_LTE_CSFB_CDMA2000_DUALRXTX_REDIR = 530
   KPI_ID_LTE_CSFB_CDMA2000_DUALRXTX_DLNAS = 531
   KPI_ID_LTE_HO_FROMENB_FULL_RECFG        = 532
   KPI_ID_LTE_RRC_CONNREESTAB_FULL_RECFG   = 533
   # SRVCC counters 
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_ATT_SUM   = 910 
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_SUCC_SUM  = 911
   KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_FAIL_SUM  = 912
   KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_ATT_SUM  = 913
   KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_SUCC_SUM = 914
   KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_FAIL_SUM = 915
   #MultiCell Params
  
   LWR_TRANSID_GEN            = 1000
   LWR_TRANSID_CTF            = (LWR_TRANSID_GEN + 1)
   LWR_TRANSID_NHU            = (LWR_TRANSID_GEN + 2)
   LWR_TRANSID_PJU            = (LWR_TRANSID_GEN + 3)
   LWR_TRANSID_EGT            = (LWR_TRANSID_GEN + 4)
   LWR_TRANSID_SZT            = (LWR_TRANSID_GEN + 5)
   LWR_TRANSID_CZT            = (LWR_TRANSID_GEN + 6)
   LWR_TRANSID_RGR            = (LWR_TRANSID_GEN + 7)
   LWR_TRANSID_ENBCFG         = (LWR_TRANSID_GEN + 8)
   LWR_TRANSID_CELLCFG        = (LWR_TRANSID_GEN + 9)
   LWR_TRANSID_MME            = (LWR_TRANSID_GEN + 10)
   LWR_TRANSID_NHCFG          = (LWR_TRANSID_GEN + 11)
   LWR_TRANSID_NREUTRAN       = (LWR_TRANSID_GEN + 12)
   LWR_TRANSID_NRUTRAN        = (LWR_TRANSID_GEN + 13)
   LWR_TRANSID_NHCELLCFG            = (LWR_TRANSID_GEN + 14)
   LWR_TRANSID_NHUTRAN_CELLCFG      = (LWR_TRANSID_GEN + 15)
   LWR_TRANSID_INTER_NHCELLCFG      = (LWR_TRANSID_GEN + 16)
   LWR_TRANSID_CDMA1XRTT_BAND       = (LWR_TRANSID_GEN + 17)
   LWR_TRANSID_CDMA1XRTT_FREQ       = (LWR_TRANSID_GEN + 18)
   LWR_TRANSID_CDMAHRPD_CLASS       = (LWR_TRANSID_GEN + 19)
   LWR_TRANSID_CDMAHRPD_FREQ        = (LWR_TRANSID_GEN + 20)
   LWR_TRANSID_RMU                  = (LWR_TRANSID_GEN + 22)
   LWR_TRANSID_MME_DYN_ADDCFG       = (LWR_TRANSID_GEN + 23)
   LWR_TRANSID_MME_DYN_DELCFG       = (LWR_TRANSID_GEN + 24)
   LWR_TRANSID_ADD_NGHCELL_MEAS     = (LWR_TRANSID_GEN + 25)
   LWR_TRANSID_CDMA1XRTT_CELL       = (LWR_TRANSID_GEN + 26)
   LWR_TRANSID_GERAN_FREQ           = (LWR_TRANSID_GEN + 27)
   LWR_TRANSID_GERAN_CELL           = (LWR_TRANSID_GEN + 28)
   LWR_TRANSID_NLU                  = (LWR_TRANSID_GEN + 29)
   #MultiCell Params

   #RRC EVENT TYPES
   C4_CSFBPARAMSRSPCDMA2000 = 0
   C4_DLINFOTFR = 1
   C4_HANDOVERFROMEUTRAPREPRQST = 2
   C4_MOBILITYFROMEUTRACMD = 3
   C4_RRCCONRECFGN =  4
   C4_RRCCONRLS =  5
   C4_SECURITYMODECMD = 6
   C4_UECAPENQUIRY = 7
   C4_COUNTERCHECK = 8
   C4_UEINFORQST_R9 = 9
   C4_LOGGEDMEASUREMENTCFG_R10 = 10
   C4_RNRECFGN_R10 = 11
#CA Changes
   RG_SCH_UCI_FORMAT1A_1B = 0
   RG_SCH_UCI_FORMAT1B_CS = 1
   RG_SCH_UCI_FORMAT3 = 2
   RG_SCH_UCI_FORMAT_NON_CA = 3
   RGR_SCELLRELEASE = 16
   RGR_SCELLADD = 32
   RGR_SCELLACT = 64
   RGR_SCELLDEACT = 128

   genDef = {
      "AENA" : AENA,
      "ADISGRC" : ADISGRC,
      "AADD" : AADD,
      "ADISIMM" : ADISIMM,
      "ADEL" : ADEL,
      "AMODIFY" : AMODIFY,
      "ACLEAR" : ACLEAR,
      "ABND_ENA" : ABND_ENA,
      "AUBND_DIS" : AUBND_DIS,
      "AUBND" : AUBND,
      "ABND" : ABND,
      "AADD_ASSOC_TPTSRV" : AADD_ASSOC_TPTSRV,
      "ADEL_ASSOC_TPTSRV" : ADEL_ASSOC_TPTSRV,
      "LCM_PRIM_NOK" : LCM_PRIM_NOK,
      "LCM_PRIM_OK_NDONE" : LCM_PRIM_OK_NDONE,
           "LAQ_PSMST_CLOSED"        : LAQ_PSMST_CLOSED,          
           "AQ_DSC_REASON_REBOOTING" : AQ_DSC_REASON_REBOOTING,
          "AQ_DSC_REASON_BUSY"       : AQ_DSC_REASON_BUSY,
          "AQ_DSC_REASON_DNWT"       : AQ_DSC_REASON_DNWT,
          "AQ_DSC_REASON_DEL_PEER"   : AQ_DSC_REASON_DEL_PEER,
          "AQ_DSC_REASON_CLOSE_PEER" : AQ_DSC_REASON_CLOSE_PEER,
          "AQ_DSC_REASON_TLS_FAIL"   : AQ_DSC_REASON_TLS_FAIL,
      "LAQ_PSMST_WAIT_CONN_ACK"              : LAQ_PSMST_WAIT_CONN_ACK,              
      "LAQ_PSMST_WAIT_I_CEA"                 : LAQ_PSMST_WAIT_I_CEA,                 
      "LAQ_PSMST_WAIT_CONN_ACK_ELECT"       : LAQ_PSMST_WAIT_CONN_ACK_ELECT,       
      "LAQ_PSMST_WAIT_RETURNS"               : LAQ_PSMST_WAIT_RETURNS,               
      "LAQ_PSMST_OPEN"                       : LAQ_PSMST_OPEN,                       
      "LAQ_PSMST_CLOSING"                    : LAQ_PSMST_CLOSING,                  
      "LAQ_PSMST_SUSPECT"                    : LAQ_PSMST_SUSPECT,                   
      "LAQ_PSMST_DOWN"                       : LAQ_PSMST_DOWN,                    
      "LAQ_PSMST_REOPEN"                     : LAQ_PSMST_REOPEN,                     
      "LAQ_PSMST_WAIT_TLS_CFM"               : LAQ_PSMST_WAIT_TLS_CFM, 
      "LAQ_CAUSE_MISSING_MAND_AVP"           : LAQ_CAUSE_MISSING_MAND_AVP,

      "LCM_REASON_MEM_NOAVAIL" : LCM_REASON_MEM_NOAVAIL,
      "LCM_REASON_GENCFG_NOT_DONE" : LCM_REASON_GENCFG_NOT_DONE,
      "LCM_REASON_EXCEED_CONF_VAL" : LCM_REASON_EXCEED_CONF_VAL,
      "LCM_REASON_INVALID_PAR_VAL" : LCM_REASON_INVALID_PAR_VAL,
      "LCM_REASON_INVALID_SAP" : LCM_REASON_INVALID_SAP,
      "LCM_REASON_INVALID_SUBACTION": LCM_REASON_INVALID_SUBACTION,
      "LCM_REASON_RECONFIG_FAIL" : LCM_REASON_RECONFIG_FAIL,
      "LCM_REASON_INVALID_ACTION" : LCM_REASON_INVALID_ACTION,
      "LCM_REASON_INVALID_STATE" : LCM_REASON_INVALID_STATE,
      "LCM_REASON_PRTLYRCFG_NOT_DONE" : LCM_REASON_PRTLYRCFG_NOT_DONE,
      "LCM_REASON_INVALID_ENTITY" : LCM_REASON_INVALID_ENTITY,
      "LCM_REASON_INVALID_ELMNT"  : LCM_REASON_INVALID_ELMNT,
      "LCM_REASON_REGTMR_FAIL":LCM_REASON_REGTMR_FAIL,
      "LCM_REASON_INV_NODE_TYPE" : LCM_REASON_INV_NODE_TYPE,
      "LCM_REASON_INV_NMB_USAPS" : LCM_REASON_INV_NMB_USAPS,
      "LCM_REASON_INV_NMB_SRVS" : LCM_REASON_INV_NMB_SRVS,
      "LCM_REASON_INV_NMB_TNLS" : LCM_REASON_INV_NMB_TNLS,
      "LCM_REASON_INVALID_INTFTYPE" : LCM_REASON_INVALID_INTFTYPE,
      "LCM_REASON_INVALID_TPTTYPE" : LCM_REASON_INVALID_TPTTYPE,
      "LCM_REASON_INVALID_TMRVAL" : LCM_REASON_INVALID_TMRVAL,
      "LCM_REASON_INVALID_NUMRETRY" : LCM_REASON_INVALID_NUMRETRY,
      "LCM_REASON_TSAPCFG_NOT_DONE" : LCM_REASON_TSAPCFG_NOT_DONE,
#cm_xta_py_py_001.main_55: TSAP config reason
      "LCM_REASON_TSAP_IP_CFGD" :LCM_REASON_TSAP_IP_CFGD ,
      "LCM_REASON_TPTSRV_CFGD" : LCM_REASON_TPTSRV_CFGD,
      "LCM_REASON_TPTCONID_NOAVAIL" : LCM_REASON_TPTCONID_NOAVAIL,
      "LCM_REASON_SRVINIT_FAIL" : LCM_REASON_SRVINIT_FAIL,
      "LCM_REASON_ECOSAP_CFGD" : LCM_REASON_ECOSAP_CFGD,
      "LCM_REASON_DEFSRV_CFGD" : LCM_REASON_DEFSRV_CFGD,
      "LCM_REASON_INVALID_NMB_INTFS" : LCM_REASON_INVALID_NMB_INTFS,
      "LCM_REASON_INVALID_PORT" : LCM_REASON_INVALID_PORT,
      "LCM_REASON_INV_TNL_ARRSIZ" : LCM_REASON_INV_TNL_ARRSIZ,
      "LCM_REASON_ECOSAP_NOTCFGD" : LCM_REASON_ECOSAP_NOTCFGD,
      "LCM_REASON_HASHING_FAILED" : LCM_REASON_HASHING_FAILED,
      "LCM_REASON_LYR_SPECIFIC" : LCM_REASON_LYR_SPECIFIC,
      "LCM_EVENT_UI_INV_EVT" : LCM_EVENT_UI_INV_EVT,
      "LCM_EVENT_LI_INV_EVT" : LCM_EVENT_LI_INV_EVT,
      "LCM_EVENT_PI_INV_EVT" : LCM_EVENT_PI_INV_EVT,
      "LCM_EVENT_INV_EVT" : LCM_EVENT_INV_EVT,
      "LCM_EVENT_INV_STATE" : LCM_EVENT_INV_STATE,
      "LCM_EVENT_INV_TMR_EVT" : LCM_EVENT_INV_TMR_EVT,
      "LCM_EVENT_MI_INV_EVT" : LCM_EVENT_MI_INV_EVT,
      "LCM_EVENT_BND_FAIL" : LCM_EVENT_BND_FAIL,
      "LCM_EVENT_NAK" : LCM_EVENT_NAK,
      "LCM_EVENT_TIMEOUT" : LCM_EVENT_TIMEOUT,
      "LCM_EVENT_BND_OK" : LCM_EVENT_BND_OK,
      "LCM_EVENT_SMEM_ALLOC_FAIL" : LCM_EVENT_SMEM_ALLOC_FAIL,
      "LCM_EVENT_DMEM_ALLOC_FAIL" : LCM_EVENT_DMEM_ALLOC_FAIL,
      "LCM_EVENT_SEQERR" : LCM_EVENT_SEQERR,
      "LCM_EVENT_OOM" : LCM_EVENT_OOM,
      "LCM_EVENT_UPDMSG_ERR" : LCM_EVENT_UPDMSG_ERR,
      "LCM_EVENT_HTBT_EXP" : LCM_EVENT_HTBT_EXP,
      "LCM_EVENT_TRANSLATION_FAILURE" : LCM_EVENT_TRANSLATION_FAILURE,
      "LCM_EVENT_LYR_SPECIFIC" : LCM_EVENT_LYR_SPECIFIC,
      "LCM_CAUSE_UNKNOWN" : LCM_CAUSE_UNKNOWN,
      "LCM_CAUSE_OUT_OF_RANGE" : LCM_CAUSE_OUT_OF_RANGE,
      "LCM_CAUSE_INV_SAP" : LCM_CAUSE_INV_SAP,
      "LCM_CAUSE_INV_SPID" : LCM_CAUSE_INV_SPID,
      "LCM_CAUSE_INV_SUID" : LCM_CAUSE_INV_SUID,
      "LCM_CAUSE_INV_NETWORK_MSG" : LCM_CAUSE_INV_NETWORK_MSG,
      "LCM_CAUSE_DECODE_ERR" : LCM_CAUSE_DECODE_ERR,
      "LCM_CAUSE_USER_INITIATED" : LCM_CAUSE_USER_INITIATED,
      "LCM_CAUSE_MGMT_INITIATED" : LCM_CAUSE_MGMT_INITIATED,
      "LCM_CAUSE_INV_STATE" : LCM_CAUSE_INV_STATE,
      "LCM_CAUSE_TMR_EXPIRED" : LCM_CAUSE_TMR_EXPIRED,
      "LCM_CAUSE_INV_MSG_LENGTH" : LCM_CAUSE_INV_MSG_LENGTH,
      "LCM_CAUSE_PROT_NOT_ACTIVE" : LCM_CAUSE_PROT_NOT_ACTIVE,
      "LCM_CAUSE_INV_PAR_VAL" : LCM_CAUSE_INV_PAR_VAL,
      "LCM_CAUSE_NEG_CFM" : LCM_CAUSE_NEG_CFM,
      "LCM_CAUSE_MEM_ALLOC_FAIL" : LCM_CAUSE_MEM_ALLOC_FAIL,
      "LCM_CAUSE_HASH_FAIL" : LCM_CAUSE_HASH_FAIL,
      "LCM_CAUSE_VERSION_MISMATCH" : LCM_CAUSE_VERSION_MISMATCH,
      "LCM_CAUSE_SWVER_NAVAIL" : LCM_CAUSE_SWVER_NAVAIL,
      "LCM_CAUSE_DLGFAIL_DUETO_RECOVERY" : LCM_CAUSE_DLGFAIL_DUETO_RECOVERY,
      "LCM_CAUSE_INV_ACTION" : LCM_CAUSE_INV_ACTION,
      "LCM_CAUSE_LYR_SPECIFIC" : LCM_CAUSE_LYR_SPECIFIC,
      "LSO_CAUSE_SAP_BNDDIS" : LSO_CAUSE_SAP_BNDDIS,
      "LSO_CAUSE_SAP_BNDENA" :  LSO_CAUSE_SAP_BNDENA,
      "LSO_CAUSE_SAP_UBNDDIS" : LSO_CAUSE_SAP_UBNDDIS,
      "LSO_CAUSE_LI_INITIATED" : LSO_CAUSE_LI_INITIATED,
      "LSO_CAUSE_INV_SUCONNID" : LSO_CAUSE_INV_SUCONNID,
      "LSO_CAUSE_INV_SPCONNID" : LSO_CAUSE_INV_SPCONNID,
      "LSO_CAUSE_INV_ENTID" :  LSO_CAUSE_INV_ENTID,
      "LSO_CAUSE_TPT_FAIL" : LSO_CAUSE_TPT_FAIL,
      "LSO_ENT_NONE" : LSO_ENT_NONE,
      "LSO_ENT_B2BUA" : LSO_ENT_B2BUA,
      "LSO_ENT_UA" : LSO_ENT_UA,
      "LSO_ENT_NS" : LSO_ENT_NS,
      "LSO_STS_UA" : LSO_STS_UA,
      "LSO_STS_NS" : LSO_STS_NS,
      "LSO_PAR_NONE" : LSO_PAR_NONE,
      "LSO_PAR_MEM" : LSO_PAR_MEM,
      "LSO_PAR_SAP" : LSO_PAR_SAP,
      "LSO_PAR_ENT" : LSO_PAR_ENT,
      "LSO_PAR_CONNID" : LSO_PAR_CONNID,
      "LSO_PAR_TPTADDR" : LSO_PAR_TPTADDR,
      "LSO_PAR_STATUS" : LSO_PAR_STATUS,
      "LSO_PAR_REASON" : LSO_PAR_REASON,
      "LSO_PAR_CHOICE" : LSO_PAR_CHOICE,
      "LSO_PAR_TPTSRV" : LSO_PAR_TPTSRV,
      "LSO_PAR_REG" : LSO_PAR_REG,
      "LSO_PAR_TSAP" : LSO_PAR_TSAP,
      "LSO_PAR_SSAP" : LSO_PAR_SSAP,
      "LSO_PAR_TPTPARM" : LSO_PAR_TPTPARM,
      "LSO_PAR_VAL" : LSO_PAR_VAL,
      "LSO_REASON_INV_CALLHDL" : LSO_REASON_INV_CALLHDL,
      "LSO_REASON_NO_ENDPS" : LSO_REASON_NO_ENDPS,
      "LSO_REASON_INV_ENDP" : LSO_REASON_INV_ENDP,
      "LSO_ORIGINATOR" : LSO_ORIGINATOR,
      "LSO_RECEIVER" : LSO_RECEIVER, 
      "LSO_ACNT_NONE" : LSO_ACNT_NONE, 
      "LSO_ACNT_MEDIA_SDP_DECODED" : LSO_ACNT_MEDIA_SDP_DECODED,
      "LSO_ACNT_EST" : LSO_ACNT_EST,
      "LSO_TSAP_TYPE_TUCL" : LSO_TSAP_TYPE_TUCL,
      "LSO_TSAP_TYPE_SCTP" : LSO_TSAP_TYPE_SCTP,
      "LSO_TSAP_TYPE_DTUCL" : LSO_TSAP_TYPE_DTUCL,
      "LSO_TSAP_TYPE_DSCTP" : LSO_TSAP_TYPE_DSCTP,
      "LSO_REASON_INVALID_ENTID" : LSO_REASON_INVALID_ENTID,
      "ENTSO"                    : ENTSO,
      "ENTSG"                    : ENTSG,
      "ENTSB"                    : ENTSB,
      "ENTSV"                    : ENTSV,
 

      "DBP" : DBP,
      "DBPAPP" : DBPAPP,
      "CXDX"  : CXDX ,
      "SH"   : SH,
      "RF"   : RF,
      "RO"   : RO,
      "RORF"   : RORF,
      "GQ"   : GQ,
      "APP"  : APP,
      "E2"  : E2,
      "S6A"  : S6A,
      "S6B"  : S6B,
      "SWX"  : SWX,
      "SWM"  : SWM,

      "DBGMASK_SI"  :  DBGMASK_SI,
      "DBGMASK_MI"  :  DBGMASK_MI,
      "DBGMASK_UI"  :  DBGMASK_UI, 
      "DBGMASK_LI"  :  DBGMASK_LI,
      "DBGMASK_PI"  :  DBGMASK_PI,

      "LAQ_DBGMASK_SMEM" : LAQ_DBGMASK_SMEM,
      "LAQ_DBGMASK_MODULES" : LAQ_DBGMASK_MODULES,
      "LAQ_DBGMASK_SUPP_FUNC":LAQ_DBGMASK_SUPP_FUNC,
#cm_xta_py_py_001.main_50 : Added debug masks for diameter 1.3 release.
      "LAQ_DBGMASK_PSM":LAQ_DBGMASK_PSM,
      "LAQ_DBGMASK_MP":LAQ_DBGMASK_MP,
      "LAQ_DBGMASK_DENC":LAQ_DBGMASK_DENC,
      "LAQ_DBGMASK_CDB":LAQ_DBGMASK_CDB,
      "LAQ_DBGMASK_TMR":LAQ_DBGMASK_TMR,
      "LAQ_DBGMASK_PD":LAQ_DBGMASK_PD,
      "LAQ_DBGMASK_FOFB":LAQ_DBGMASK_FOFB,
      "LAQ_DBGMASK_AG":LAQ_DBGMASK_AG,

      "LLX_DBGMASK_MSG"    : LLX_DBGMASK_MSG,
      "LLX_DBGMASK_FLOW"   : LLX_DBGMASK_FLOW,
      "LLX_DBGMASK_DBG"    : LLX_DBGMASK_DBG,
      "LLX_DBGMASK_INFO"   : LLX_DBGMASK_INFO,
      "LLX_DBGMASK_TRC"    : LLX_DBGMASK_TRC,
      "LLX_DBGMASK_WARN"   : LLX_DBGMASK_WARN,
      "LLX_DBGMASK_ERROR"  : LLX_DBGMASK_ERROR,
      "LLX_DBGMASK_FATAL"  : LLX_DBGMASK_FATAL,
      "LLX_DBGMASK_MEM"    : LLX_DBGMASK_MEM,
      "LLX_DBGMASK_BUF"    : LLX_DBGMASK_BUF,
      "LLX_DBGMASK_PARAM"  : LLX_DBGMASK_PARAM,

      "LLX_CAUSE_SAP_BNDDIS"          : LLX_CAUSE_SAP_BNDDIS,
      "LLX_CAUSE_SAP_BNDENA"          : LLX_CAUSE_SAP_BNDENA,
      "LLX_CAUSE_SAP_UBNDDIS"         : LLX_CAUSE_SAP_UBNDDIS,
      "LLX_CAUSE_LI_INITIATED"        : LLX_CAUSE_LI_INITIATED,
      "LLX_CAUSE_INV_SUINSTID"        : LLX_CAUSE_INV_SUINSTID,
      "LLX_CAUSE_INV_SPINSTID"        : LLX_CAUSE_INV_SPINSTID,
      "LLX_CAUSE_SAP_DISGRC"          : LLX_CAUSE_SAP_DISGRC,
      "LLX_CAUSE_SPINSTID_NOT_AVAIL"  : LLX_CAUSE_SPINSTID_NOT_AVAIL,
      "LLX_CAUSE_PROC_FAIL"           : LLX_CAUSE_PROC_FAIL,
      "LLX_CAUSE_INVALID_INST_STATE"  : LLX_CAUSE_INVALID_INST_STATE,

      "LLX_REASON_INVALID_INSTANCE"   : LLX_REASON_INVALID_INSTANCE,
      "LLX_REASON_INVALID_TPTTYPE"    : LLX_REASON_INVALID_TPTTYPE,
      "LLX_REASON_INVALID_MTUSIZE"    : LLX_REASON_INVALID_MTUSIZE,
      "LLX_REASON_INVALID_BINSIZE"   :  LLX_REASON_INVALID_BINSIZE,
      "LLX_REASON_INVALID_TMRVAL"    :  LLX_REASON_INVALID_TMRVAL,
      "LLX_REASON_INVALID_NUMRETRY"  :  LLX_REASON_INVALID_NUMRETRY,
      "LLX_TRC_EVENT_TX"  :  LLX_TRC_EVENT_TX,
      "LLX_TRC_EVENT_RX"  :  LLX_TRC_EVENT_RX,

      "GGU_GTP_VER_0"  : GGU_GTP_VER_0,
      "GGU_GTP_VER_1"  : GGU_GTP_VER_1,
    
      "GGU_TMGMT_REQTYPE_DEL_ALL"  : GGU_TMGMT_REQTYPE_DEL_ALL,

      "ENTAQ"                    : ENTAQ,
      "ENTSB"                    : ENTSB,
      "ENTAB"                    : ENTAB,

      "ENTHI"                    : ENTHI,
      "ENTHR"                    : ENTHR,
      "INVALID_ACTION" : INVALID_ACTION,
      "LSO_DNS_A_CACHE" : LSO_DNS_A_CACHE,
      "LSO_DNS_SRV_CACHE" : LSO_DNS_SRV_CACHE,
      "LSO_MCAST_CACHE" : LSO_MCAST_CACHE,
      "LSO_DNS_NAPTR_CACHE" : LSO_DNS_NAPTR_CACHE,
      "LSO_REASON_INV_TPTSRV"     : LSO_REASON_INV_TPTSRV,
      "LSO_FRK_SEQUENTIAL"        : LSO_FRK_SEQUENTIAL,
      "LSO_FRK_PARALLEL"          : LSO_FRK_PARALLEL,

      "SATRC" : SATRC,
      "STSIPENT" : STSIPENT,
      "STTSAP" : STTSAP,
      "SOT_ET_INVALID" : SOT_ET_INVALID,
      "SOT_ET_INVITE" : SOT_ET_INVITE,
      "SOT_ET_ACK" : SOT_ET_ACK,
      "SOT_ET_PUBLISH" : SOT_ET_PUBLISH,
      "SOT_ET_OPTIONS" : SOT_ET_OPTIONS,
      "SOT_ET_BYE" : SOT_ET_BYE,
      "SOT_ET_CANCEL" : SOT_ET_CANCEL,
      "SOT_ET_REGISTER" : SOT_ET_REGISTER,
      "SOT_ET_INFO" : SOT_ET_INFO,
      "SOT_ET_PRECON_MET" : SOT_ET_PRECON_MET,
      "SOT_ET_PRACK" : SOT_ET_PRACK,
      "SOT_ET_REFER" : SOT_ET_REFER,
      "SOT_ET_SUBSCRIBE" : SOT_ET_SUBSCRIBE,
      "SOT_ET_NOTIFY" : SOT_ET_NOTIFY,
      "SOT_ET_MESSAGE" : SOT_ET_MESSAGE,
      "SOT_ET_UPDATE" : SOT_ET_UPDATE,
      "SOT_ET_PROGRESS" : SOT_ET_PROGRESS,
      "SOT_ET_TRYING" : SOT_ET_TRYING,
      "SOT_ET_RINGING" : SOT_ET_RINGING,
      "SOT_ET_PROGRESS" : SOT_ET_PROGRESS,
      "SOT_ET_FORWARDING" : SOT_ET_FORWARDING,
      "SOT_ET_QUEUED" : SOT_ET_QUEUED,
      "SOT_ET_REDIRECT" : SOT_ET_REDIRECT,
      "SOT_ET_ERROR" : SOT_ET_ERROR,
      "SOT_ET_OK" : SOT_ET_OK,
      "SOT_ET_REG_TMO" : SOT_ET_REG_TMO,
      "SOT_ET_LRQ" : SOT_ET_LRQ,
      "SOT_ET_MODIFY" : SOT_ET_MODIFY,
      "SOT_ET_STATUS" : SOT_ET_STATUS,
      "SOT_ET_UNKNOWN" : SOT_ET_UNKNOWN,
      "SOT_ET_REGISTER_LOC" : SOT_ET_REGISTER_LOC,
      "SOT_ET_SIP_ERROR" : SOT_ET_SIP_ERROR,
      "SOT_ET_INT_REFRESHTMR_EXPD" : SOT_ET_INT_REFRESHTMR_EXPD,
      "SOT_ET_INT_SESSTIMER_EXPD" : SOT_ET_INT_SESSTIMER_EXPD,
      "SOT_ET_SUBSC_TMO" : SOT_ET_SUBSC_TMO,
      "SOT_ET_AUDIT" : SOT_ET_AUDIT,
      "SOT_ET_REFRESH" : SOT_ET_REFRESH,
      "SOT_ET_LOCAL_REL" : SOT_ET_LOCAL_REL,
      "SOT_ET_MAXIMUM" : SOT_ET_MAXIMUM,
      "SOT_ERR_AUDIT_IN_PROGRESS" : SOT_ERR_AUDIT_IN_PROGRESS,

      "SO_SIPMESSAGE_NONE"     : SO_SIPMESSAGE_NONE,
      "SO_SIPMESSAGE_REQUEST"  : SO_SIPMESSAGE_REQUEST,
      "SO_SIPMESSAGE_RESPONSE" : SO_SIPMESSAGE_RESPONSE,
      "SO_SIPMESSAGE_ERROR"    : SO_SIPMESSAGE_ERROR,
      "SO_SIPMESSAGE_AUDIT"    : SO_SIPMESSAGE_AUDIT,
      "SO_SIPMESSAGE_REFRESH"  : SO_SIPMESSAGE_REFRESH,

      "SOT_AUDIT_CALL"    : SOT_AUDIT_CALL,
      "SOT_AUDIT_SSAP"    : SOT_AUDIT_SSAP,

      "STGEN" : STGEN, 
      "ASHUTDOWN" : ASHUTDOWN,
      "STSSAP" : STSSAP,
      "STPSAP" : STPSAP,
      # Added the support for FTHA Integration
      "CMXTA_INST_ID" : CMXTA_INST_ID, 
      "LSG_HI_ENT_DIST" : LSG_HI_ENT_DIST, 
      "LSG_HI_ENT_DEDICATED_FT" : LSG_HI_ENT_DEDICATED_FT, 
      "LSG_HI_ENT_NONDEDICATED_FT" : LSG_HI_ENT_NONDEDICATED_FT, 
      "LSG_HI_ENT_CONVENTIONAL" : LSG_HI_ENT_CONVENTIONAL, 
      "LSG_HI_USE_ACTIVE" : LSG_HI_USE_ACTIVE, 
      "LSG_HI_USE_STANDBY" : LSG_HI_USE_STANDBY, 
      "CMXTA_PROCID_ONE" : CMXTA_PROCID_ONE, 
      "CMXTA_PROCID_SINGLE" : CMXTA_PROCID_SINGLE,
      "CMXTA_PROCID_TWO" : CMXTA_PROCID_TWO, 
      "CMXTA_PROCID_THREE" : CMXTA_PROCID_THREE, 
      "CMXTA_PROCID_FOUR" : CMXTA_PROCID_FOUR, 
      "CMXTA_PROCID_FIVE" : CMXTA_PROCID_FIVE, 
      "CMXTA_PROCID_MASTER" : CMXTA_PROCID_MASTER, 
      "CMXTA_PROCID_SLAVE1" : CMXTA_PROCID_SLAVE1, 
      "CMXTA_PROCID_SLAVE2" : CMXTA_PROCID_SLAVE2, 
      "CMXTA_PROCID_SLAVE3" : CMXTA_PROCID_SLAVE3, 
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
      "CMXTA_PROCID_SLAVE4" : CMXTA_PROCID_SLAVE4, 
      "CMXTA_PROCID_SLAVE5" : CMXTA_PROCID_SLAVE5, 
      "CMXTA_PROCID_SLAVE6" : CMXTA_PROCID_SLAVE6, 
      "CMXTA_PROCID_SLAVE7" : CMXTA_PROCID_SLAVE7, 
      "CMXTA_PROCID_SLAVE8" : CMXTA_PROCID_SLAVE8, 
      "CMPFTHA_STATE_ACTIVE" : CMPFTHA_STATE_ACTIVE, 
      "CMPFTHA_STATE_STANDBY" : CMPFTHA_STATE_STANDBY, 
      "CMPFTHA_STATE_OOS" : CMPFTHA_STATE_OOS, 
      "ZO_ZOT_MODE_MANUAL" : ZO_ZOT_MODE_MANUAL, 
      "JC_JCT_MODE_MANUAL" : JC_JCT_MODE_MANUAL, 
      "JC_UPDTMR_EXPIRED": JC_UPDTMR_EXPIRED,
      "JCPIF": JCPIF,
      "AQUIF": AQUIF,
      "HITIF": HITIF,
      "JCPIFVER": JCPIFVER,
      "AQUIFVER": AQUIFVER,
      "HITIFVER": HITIFVER,
      "RTE_PROTO" : RTE_PROTO,
      "STTPTSRV" : STTPTSRV,
      "STTPTENDP" : STTPTENDP,
      "LSO_PRX_STATELESS" : LSO_PRX_STATELESS,
      "LSO_PRX_CALL_STATEFUL" : LSO_PRX_CALL_STATEFUL,
      "LSO_PRX_TRANS_STATEFUL" : LSO_PRX_TRANS_STATEFUL,
      "LSO_DFLT_PRX_NONE" : LSO_DFLT_PRX_NONE,
      "LSO_DFLT_PRX_TPT_ADDR" : LSO_DFLT_PRX_TPT_ADDR,
      "LSO_DFLT_PRX_DOMAIN_NAME" : LSO_DFLT_PRX_DOMAIN_NAME,
      "LSO_NO_REGISTER"        : LSO_NO_REGISTER,
      "LSO_STAND_ALONE"        : LSO_STAND_ALONE,
      "LSO_COLOCATED"          : LSO_COLOCATED, 
      "TRUE" : TRUE,
      "FALSE" : FALSE,
      "SCT_OK" : SCT_OK,
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
      "SCT_ASSOC_IND_NONE" : SCT_ASSOC_IND_NONE,
     "SCT_ASSOC_IND_INIT" : SCT_ASSOC_IND_INIT,
      "SCT_ASSOC_IND_COOKIE" : SCT_ASSOC_IND_COOKIE,
      "ZEROSTS" : ZEROSTS,
      "NOZEROSTS" : NOZEROSTS,
      "SCT_STATUS_COMM_UP" : SCT_STATUS_COMM_UP,
      "SCT_STATUS_NET_UP" : SCT_STATUS_NET_UP,
      "SCT_STATUS_NET_DOWN" : SCT_STATUS_NET_DOWN,
      "SCT_STATUS_COMM_LOST" : SCT_STATUS_COMM_LOST,
      #Iuh 2.1 release
      "SCT_STATUS_SND_FAIL"  :   SCT_STATUS_SND_FAIL,
      "SCT_PARTIAL_DAT" : SCT_PARTIAL_DAT,
      "LSO_EVENT_HIT_BNDCFM" : LSO_EVENT_HIT_BNDCFM,
      "LSO_EVENT_HIT_CONCFM" : LSO_EVENT_HIT_CONCFM,
      "LSO_EVENT_HIT_CONIND" : LSO_EVENT_HIT_CONIND,
      "LSO_EVENT_HIT_DATIND" : LSO_EVENT_HIT_DATIND,
      "LSO_EVENT_HIT_DISCIND" : LSO_EVENT_HIT_DISCIND,
      "LSO_EVENT_HIT_DISCCFM" : LSO_EVENT_HIT_DISCCFM,
      "LSO_EVENT_HIT_UDATIND" : LSO_EVENT_HIT_UDATIND,
      "LSO_EVENT_SOT_BNDREQ" : LSO_EVENT_SOT_BNDREQ,
      "LSO_EVENT_SOT_UBNDREQ" : LSO_EVENT_SOT_UBNDREQ,
      "LSO_EVENT_SOT_CONREQ" : LSO_EVENT_SOT_CONREQ,
      "LSO_EVENT_SOT_CONRSP" : LSO_EVENT_SOT_CONRSP,
      "LSO_EVENT_SOT_CIMREQ" : LSO_EVENT_SOT_CIMREQ,
      "LSO_EVENT_SOT_CIMRSP" : LSO_EVENT_SOT_CIMRSP,
      "LSO_EVENT_SOT_CNSTREQ" : LSO_EVENT_SOT_CNSTREQ,
      "LSO_EVENT_SOT_RELREQ" : LSO_EVENT_SOT_RELREQ,
      "LSO_EVENT_SOT_RELRSP" : LSO_EVENT_SOT_RELRSP,
      "LSO_EVENT_SOT_MODREQ" : LSO_EVENT_SOT_MODREQ,
      "LSO_EVENT_SOT_MODRSP" : LSO_EVENT_SOT_MODRSP,
      "LSO_EVENT_SOT_ACKREQ" : LSO_EVENT_SOT_ACKREQ,
      "LSO_EVENT_SOT_CANCELREQ" : LSO_EVENT_SOT_CANCELREQ,
      "LSO_EVENT_SOT_AUDITREQ" : LSO_EVENT_SOT_AUDITREQ,
      "LSO_EVENT_SOT_CAMREQ" : LSO_EVENT_SOT_CAMREQ,
      "LSO_EVENT_SOT_CAMRSP" : LSO_EVENT_SOT_CAMRSP,
      "LSO_EVENT_TPTSRV_ENA" : LSO_EVENT_TPTSRV_ENA,
      "LSO_EVENT_ENT_ENA" : LSO_EVENT_ENT_ENA,
      "LSO_EVENT_ENT_DIS" : LSO_EVENT_ENT_DIS,
      "LSO_EVENT_TPTSRV_DIS" : LSO_EVENT_TPTSRV_DIS,
      "LSO_EVENT_UBND_OK" : LSO_EVENT_UBND_OK,
      "LSO_EVENT_RES_CONG_STRT" : LSO_EVENT_RES_CONG_STRT,
      "LSO_EVENT_RES_CONG_STOP" : LSO_EVENT_RES_CONG_STOP,
      "LSO_EVENT_RES_PRX_SWITCH" : LSO_EVENT_RES_PRX_SWITCH,
      "LSO_EVENT_REG_WARN_ON" : LSO_EVENT_REG_WARN_ON,
      "LSO_EVENT_REG_WARN_OFF" : LSO_EVENT_REG_WARN_OFF,
      "LSO_EVENT_REG_FULL" : LSO_EVENT_REG_FULL,
      "LSO_EVENT_ENDP_ENA" : LSO_EVENT_ENDP_ENA,
      "LSO_EVENT_ENDP_CLOSE" : LSO_EVENT_ENDP_CLOSE,
      "LSO_EVENT_SCT_BNDCFM" : LSO_EVENT_SCT_BNDCFM,
      "LSO_EVENT_SCT_ENDPOPENCFM" : LSO_EVENT_SCT_ENDPOPENCFM,
      "LSO_EVENT_SCT_TERMIND" : LSO_EVENT_SCT_TERMIND,
      "LSO_EVENT_SCT_ASSOCCFM" : LSO_EVENT_SCT_ASSOCCFM,
      "LSO_EVENT_SCT_ASSOCIND" : LSO_EVENT_SCT_ASSOCIND,
      "LSO_EVENT_SCT_DATIND" : LSO_EVENT_SCT_DATIND,
      "LSO_EVENT_SCT_STACFM" : LSO_EVENT_SCT_STACFM,
      "LSO_EVENT_SCT_STAIND" : LSO_EVENT_SCT_STAIND,
      "LSO_EVENT_SCT_HBEATCFM" : LSO_EVENT_SCT_HBEATCFM,
      "LSO_EVENT_SCT_TERMCFM" : LSO_EVENT_SCT_TERMCFM,
      "LSO_EVENT_SCT_SETPRICFM" : LSO_EVENT_SCT_SETPRICFM,
      "LSO_EVENT_SCT_FLCIND" : LSO_EVENT_SCT_FLCIND,
      "LSO_EVENT_SCT_ENDPCLOSECFM" : LSO_EVENT_SCT_ENDPCLOSECFM,
      "LSO_EVENT_HIT_FLCIND" : LSO_EVENT_HIT_FLCIND,
      "LSO_EVENT_SOT_PROXYREQ" : LSO_EVENT_SOT_PROXYREQ,
      "LSO_EVENT_SOT_PROXYRSP" : LSO_EVENT_SOT_PROXYRSP,
      "LSO_EVENT_SOT_TRANSREQ" : LSO_EVENT_SOT_TRANSREQ,
      "LSO_EVENT_SOT_TRANSRSP" : LSO_EVENT_SOT_TRANSRSP,

      "LSO_TPTPROT_UDP"        : LSO_TPTPROT_UDP,   
      "LSO_TPTPROT_TCP"        : LSO_TPTPROT_TCP,  
      "LSO_TPTPROT_SCTP"       : LSO_TPTPROT_SCTP,  
      "LSO_TPTPROT_TLS_TCP"    : LSO_TPTPROT_TLS_TCP,  
      "LSO_TPTPROT_UDP_PRIOR"  : LSO_TPTPROT_UDP_PRIOR,  

      "EGT_GTPC_MSG_VER_N_SUPP_IND"    : EGT_GTPC_MSG_VER_N_SUPP_IND,
      "EGT_GTPC_MSG_ECHO_REQ"    : EGT_GTPC_MSG_ECHO_REQ,
      "EGT_GTPC_MSG_ECHO_RSP"    : EGT_GTPC_MSG_ECHO_RSP,
      "EGT_GTPC_MSG_INVALID"    : EGT_GTPC_MSG_INVALID,
     	
      "EGT_GTPC_MSG_CS_REQ" : EGT_GTPC_MSG_CS_REQ, 
      "EGT_GTPC_MSG_CS_RSP"          :   EGT_GTPC_MSG_CS_RSP,
      "EGT_GTPC_MSG_MB_REQ"         :    EGT_GTPC_MSG_MB_REQ,
      "EGT_GTPC_MSG_MB_RSP"         :    EGT_GTPC_MSG_MB_RSP,          
      "EGT_GTPC_MSG_DS_REQ"        :     EGT_GTPC_MSG_DS_REQ,  
      "EGT_GTPC_MSG_DS_RSP"         :    EGT_GTPC_MSG_DS_RSP,   
      "EGT_GTPC_MSG_CN_REQ"        :     EGT_GTPC_MSG_CN_REQ,     
      "EGT_GTPC_MSG_CN_RSP"         :    EGT_GTPC_MSG_CN_RSP,     
      "EGT_GTPC_MSG_MB_CMND"          :   EGT_GTPC_MSG_MB_CMND,    
      "EGT_GTPC_MSG_MBFAIL_IND"      :    EGT_GTPC_MSG_MBFAIL_IND,  
      "EGT_GTPC_MSG_DB_CMND"         :    EGT_GTPC_MSG_DB_CMND,      
      "EGT_GTPC_MSG_DB_FAIL_IN"       :   EGT_GTPC_MSG_DB_FAIL_IN,    
      "EGT_GTPC_MSG_BR_CMND"           :  EGT_GTPC_MSG_BR_CMND,        
      "EGT_GTPC_MSG_BR_FAIL_IND"      :   EGT_GTPC_MSG_BR_FAIL_IND,     
      "EGT_GTPC_MSG_DD_NOTFN_FAIL_IND"  :  EGT_GTPC_MSG_DD_NOTFN_FAIL_IND, 
      "EGT_GTPC_MSG_TRC_SESS_ACTVN"     :  EGT_GTPC_MSG_TRC_SESS_ACTVN,  
      "EGT_GTPC_MSG_TRC_SESS_DEACTVN"  :   EGT_GTPC_MSG_TRC_SESS_DEACTVN, 
      "EGT_GTPC_MSG_STOP_PAGING_IND"  :    EGT_GTPC_MSG_STOP_PAGING_IND, 
      "EGT_GTPC_MSG_CB_REQ"          :   EGT_GTPC_MSG_CB_REQ,  
      "EGT_GTPC_MSG_CB_RSP"          :    EGT_GTPC_MSG_CB_RSP,  
      "EGT_GTPC_MSG_UB_REQ"         :    EGT_GTPC_MSG_UB_REQ,    
      "EGT_GTPC_MSG_UB_RSP"         :    EGT_GTPC_MSG_UB_RSP,     
      "EGT_GTPC_MSG_DB_REQ"          :   EGT_GTPC_MSG_DB_REQ,      
      "EGT_GTPC_MSG_DB_RSP"         :    EGT_GTPC_MSG_DB_RSP,       
      "EGT_GTPC_MSG_DPDN_CON_SET_REQ" :    EGT_GTPC_MSG_DPDN_CON_SET_REQ,
      "EGT_GTPC_MSG_DPDN_CON_SET_RSP" :  EGT_GTPC_MSG_DPDN_CON_SET_RSP,
      "EGT_GTPC_MSG_ID_REQ"    :        EGT_GTPC_MSG_ID_REQ,  
      "EGT_GTPC_MSG_ID_RSP"    :  EGT_GTPC_MSG_ID_RSP,  
      "EGT_GTPC_MSG_CNTXT_REQ" :  EGT_GTPC_MSG_CNTXT_REQ,
      "EGT_GTPC_MSG_CNTXT_RSP" :  EGT_GTPC_MSG_CNTXT_RSP,
      "EGT_GTPC_MSG_CNTXT_ACK" :  EGT_GTPC_MSG_CNTXT_ACK,
      "EGT_GTPC_MSG_FR_REQ" :  EGT_GTPC_MSG_FR_REQ,
      "EGT_GTPC_MSG_FR_RSP"  :  EGT_GTPC_MSG_FR_RSP, 
      "EGT_GTPC_MSG_FR_COMP_NOTFN" :   EGT_GTPC_MSG_FR_COMP_NOTFN, 
      "EGT_GTPC_MSG_FR_COMP_ACK"  :  EGT_GTPC_MSG_FR_COMP_ACK, 
      "EGT_GTPC_MSG_FWD_ACC_CNTXT_NOTFN" :   EGT_GTPC_MSG_FWD_ACC_CNTXT_NOTFN,
      "EGT_GTPC_MSG_FWD_ACC_CNTXT_ACK" :  EGT_GTPC_MSG_FWD_ACC_CNTXT_ACK,
      "EGT_GTPC_MSG_RC_REQ" :  EGT_GTPC_MSG_RC_REQ,
      "EGT_GTPC_MSG_RC_RSP" :  EGT_GTPC_MSG_RC_RSP, 
      "EGT_GTPC_MSG_CFG_TRAN_TUNN" :  EGT_GTPC_MSG_CFG_TRAN_TUNN, 
      "EGT_GTPC_MSG_DTCH_NOTFN"   :     EGT_GTPC_MSG_DTCH_NOTFN,
      "EGT_GTPC_MSG_DTCH_ACK"     :   EGT_GTPC_MSG_DTCH_ACK,     
      "EGT_GTPC_MSG_CS_PGNG_IND"   :   EGT_GTPC_MSG_CS_PGNG_IND,   
      "EGT_GTPC_MSG_RAN_INFO_RELAY" :   EGT_GTPC_MSG_RAN_INFO_RELAY,
      "EGT_GTPC_MSG_ALRT_MME_NOTFN" :   EGT_GTPC_MSG_ALRT_MME_NOTFN, 
      "EGT_GTPC_MSG_ALRT_MME_ACK" :     EGT_GTPC_MSG_ALRT_MME_ACK,
      "EGT_GTPC_MSG_UE_ACT_NOTFN" :    EGT_GTPC_MSG_UE_ACT_NOTFN,
      "EGT_GTPC_MSG_UE_ACT_ACK"   :  EGT_GTPC_MSG_UE_ACT_ACK,  
      "EGT_GTPC_MSG_CF_TUNN_REQ"  :     EGT_GTPC_MSG_CF_TUNN_REQ,
      "EGT_GTPC_MSG_CF_TUNN_RSP"  :    EGT_GTPC_MSG_CF_TUNN_RSP,
      "EGT_GTPC_MSG_SSPND_NOTFN"  :   EGT_GTPC_MSG_SSPND_NOTFN,
      "EGT_GTPC_MSG_SSPND_ACK"  :   EGT_GTPC_MSG_SSPND_ACK, 
      "EGT_GTPC_MSG_RSME_NOTFN"  :  EGT_GTPC_MSG_RSME_NOTFN, 
      "EGT_GTPC_MSG_RSME_ACK"   :  EGT_GTPC_MSG_RSME_ACK,  
      "EGT_GTPC_MSG_CIDF_TUNN_REQ" :   EGT_GTPC_MSG_CIDF_TUNN_REQ, 

      "EGT_GTPC_MSG_CIDF_TUNN_RSP" :  EGT_GTPC_MSG_CIDF_TUNN_RSP,
      "EGT_GTPC_MSG_DIDF_TUNN_REQ" :   EGT_GTPC_MSG_DIDF_TUNN_REQ,
      "EGT_GTPC_MSG_DIDF_TUNN_RSP" :   EGT_GTPC_MSG_DIDF_TUNN_RSP,
      "EGT_GTPC_MSG_RAB_REQ"       :    EGT_GTPC_MSG_RAB_REQ,      
      "EGT_GTPC_MSG_RAB_RSP"       :    EGT_GTPC_MSG_RAB_RSP,       
      "EGT_GTPC_MSG_DWN_DATA_NOTFN"   : EGT_GTPC_MSG_DWN_DATA_NOTFN, 
      "EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK"  :  EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK,
      "EGT_GTPC_MSG_UPD_PDN_CON_SET_REQ" :  EGT_GTPC_MSG_UPD_PDN_CON_SET_REQ,
      "EGT_GTPC_MSG_UPD_PDN_CON_SET_RSP" :   EGT_GTPC_MSG_UPD_PDN_CON_SET_RSP,
      "EGT_GTPC_MSG_MBMS_SESS_START_REQ" :  EGT_GTPC_MSG_MBMS_SESS_START_REQ, 
      "EGT_GTPC_MSG_MBMS_SESS_START_RSP" :    EGT_GTPC_MSG_MBMS_SESS_START_RSP,
      "EGT_GTPC_MSG_MBMS_SESS_UPD_REQ"   : EGT_GTPC_MSG_MBMS_SESS_UPD_REQ,  
      "EGT_GTPC_MSG_MBMS_SESS_UPD_RSP"  :    EGT_GTPC_MSG_MBMS_SESS_UPD_RSP,    
      "EGT_GTPC_MSG_MBMS_SESS_STOP_REQ" :   EGT_GTPC_MSG_MBMS_SESS_STOP_REQ,
      "EGT_GTPC_MSG_MBMS_SESS_STOP_RSP"  :   EGT_GTPC_MSG_MBMS_SESS_STOP_RSP,


      "EGT_GTPC_MSG_INVALID"    : EGT_GTPC_MSG_INVALID,
#cm_xta_py_py_001.main_56 - S2B and S2A 
      "EGT_GTP_INT_S2B"         : EGT_GTP_INT_S2B,
      "EGT_GTP_INT_S2A"         : EGT_GTP_INT_S2A,
      "EGT_GTP_INT_SN"         : EGT_GTP_INT_SN,
      "EGT_GTP_INT_SM"         : EGT_GTP_INT_SM,
      "EGT_GTP_INT_S16"         : EGT_GTP_INT_S16,
      "EGT_GTP_INT_S10"         : EGT_GTP_INT_S10,
      "EGT_GTP_INT_S4"          : EGT_GTP_INT_S4,
      "EGT_GTP_INT_S3"          : EGT_GTP_INT_S3,
      "EGT_GTP_INT_S11"        : EGT_GTP_INT_S11,
      "EGT_GTP_INT_S5_S8"      : EGT_GTP_INT_S5_S8,
      "EGT_GTP_INT_UNKNWN"      : EGT_GTP_INT_UNKNWN,
      "EGT_INT_S5_S8_SGW_GTP_C" : EGT_INT_S5_S8_SGW_GTP_C,
      "EGT_INT_S5_S8_PGW_GTP_C" : EGT_INT_S5_S8_PGW_GTP_C,
      "EGT_INT_S11_MME_GTP_C"  : EGT_INT_S11_MME_GTP_C,
      "EGT_INT_S11_SGW_GTP_C"  : EGT_INT_S11_SGW_GTP_C,
      "EGT_INT_S10_MME_GTP_C" : EGT_INT_S10_MME_GTP_C,
      "EGT_INT_S3_MME_GTP_C" : EGT_INT_S3_MME_GTP_C,
      "EGT_INT_S3_SGSN_GTP_C" : EGT_INT_S3_SGSN_GTP_C,
      "EGT_INT_S4_SGSN_GTP_U" : EGT_INT_S4_SGSN_GTP_U,
      "EGT_INT_S4_SGW_GTP_U" : EGT_INT_S4_SGW_GTP_U,
      "EGT_INT_S4_SGSN_GTP_C" : EGT_INT_S4_SGSN_GTP_C,
      "EGT_INT_S16_SGSN_GTP_C" : EGT_INT_S16_SGSN_GTP_C,
      "EGT_INT_SM_MBMSGW_GTP_C" : EGT_INT_SM_MBMSGW_GTP_C,
      "EGT_INT_SN_MBMSGW_GTP_C" : EGT_INT_SN_MBMSGW_GTP_C,

#cm_xta_py_py_001.main_56 - S2B and S2A 
      "EGT_INT_S2B_EPDG_GTP_C"  :   EGT_INT_S2B_EPDG_GTP_C,
      "EGT_INT_S2B_EPDG_GTP_U"  :   EGT_INT_S2B_EPDG_GTP_U,
      "EGT_INT_S2B_PGW_GTP_C "  :   EGT_INT_S2B_PGW_GTP_C,
      "EGT_INT_S2B_PGW_GTP_U "  :   EGT_INT_S2B_PGW_GTP_U ,

      "EGT_INT_S2A_TWAN_GTP_U"  :   EGT_INT_S2A_TWAN_GTP_U,
      "EGT_INT_S2A_TWAN_GTP_C"  :   EGT_INT_S2A_TWAN_GTP_C,
      "EGT_INT_S2A_PGW_GTP_C "  :   EGT_INT_S2A_PGW_GTP_C,
      "EGT_INT_S2A_PGW_GTP_U "  :   EGT_INT_S2A_PGW_GTP_U ,
      
      "EGT_INT_SGW_UL_FWD"        :    EGT_INT_SGW_UL_FWD,
      "EGT_INT_SN_SGSN_GTP_U"     :    EGT_INT_SN_SGSN_GTP_U,

		"EGT_INT_S1_U_ENB_GTP_U"  : EGT_INT_S1_U_ENB_GTP_U,
      "EGT_INT_X2_DL_ENB_GTP_U"  : EGT_INT_X2_DL_ENB_GTP_U,
      "EGT_INT_S1_U_SGW_GTP_U"  : EGT_INT_S1_U_SGW_GTP_U,
      "EGT_INT_S5_S8_SGW_GTP_U"  : EGT_INT_S5_S8_SGW_GTP_U,
      "EGT_INT_X2_UL_ENB_GTP_U"  : EGT_INT_X2_UL_ENB_GTP_U,
      "EGT_SUCCESS"            : EGT_SUCCESS,
      "EGT_ERR_MSG_UNABLE_TO_COMPLY" : EGT_ERR_MSG_UNABLE_TO_COMPLY,
      "EGT_ERR_MSG_NO_MATCH" : EGT_ERR_MSG_NO_MATCH,
      "EGT_GTP_INT_UNKNWN"     : EGT_GTP_INT_UNKNWN,
      "EGT_INV_INTF_TYPE"      : EGT_INV_INTF_TYPE,   
      "EGT_ERR_INV_VERSION"   : EGT_ERR_INV_VERSION,
      "EGT_ERR_INV_MSG_HDR"   : EGT_ERR_INV_MSG_HDR,
      "EGT_ERR_INV_MSG_TYPE"  : EGT_ERR_INV_MSG_TYPE,
      "EGT_ERR_IE_UNKNOWN"    : EGT_ERR_IE_UNKNOWN,
      "EGT_ERR_IE_INV_LEN"    : EGT_ERR_IE_INV_LEN,
      "EGT_ERR_MSG_INV_LEN"   : EGT_ERR_MSG_INV_LEN,
      "EGT_ERR_MISSING_MAND_IE" :  EGT_ERR_MISSING_MAND_IE,
      "EG_ERR_MEM_ALLOC_FAILED" :  EG_ERR_MEM_ALLOC_FAILED,
      "EGT_ERR_INV_IE_VAL" :  EGT_ERR_INV_IE_VAL,
      "EGT_ERR_MAND_IE_INCOR" : EGT_ERR_MAND_IE_INCOR,
      "EG_INV_DATA_TYPE"      : EG_INV_DATA_TYPE,
      "EGT_ERR_INV_IE_TYPE"   : EGT_ERR_INV_IE_TYPE,
      "EGT_ERR_INV_SAP"   : EGT_ERR_INV_SAP,
      "EGT_ERR_INV_TEID"      : EGT_ERR_INV_TEID,
      "EGT_ERR_NO_SEQ"    : EGT_ERR_NO_SEQ,
      "EGT_ERR_MAX_TDPU_SIZE_EXCED"    : EGT_ERR_MAX_TDPU_SIZE_EXCED,
      "EGT_ERR_INV_DATA_TYPE"    : EGT_ERR_INV_DATA_TYPE,
      "EGT_ERR_MSG_NOT_ALLWD"    : EGT_ERR_MSG_NOT_ALLWD,
      "EGT_ERR_END_MARKER_RCVD"      : EGT_ERR_END_MARKER_RCVD,
      "EGT_ERR_INV_TEID_RCVD"      : EGT_ERR_INV_TEID_RCVD,
      "EGT_ERR_INV_DST_IP"      : EGT_ERR_INV_DST_IP,
      "EGT_ERR_DST_MULT_IP"      : EGT_ERR_DST_MULT_IP,
      "EGT_ERR_INV_SRC_IP"      : EGT_ERR_INV_SRC_IP,
      "EGT_ERR_INV_SRC_PORT"      : EGT_ERR_INV_SRC_PORT,
      "EGT_ERR_PENDING_CNTRL_OP"      : EGT_ERR_PENDING_CNTRL_OP,

      # cm_xta_py_py_001.main_56 : adding definition for EGT_ERR_MAX_RETRY_EXHAUSTED 
      "EGT_ERR_MAX_RETRY_EXHAUSTED"      : EGT_ERR_MAX_RETRY_EXHAUSTED,
      # cm_xta_py_py_001.main_57 : adding definition for EGT_ERR_INV_PIGGY_MSG
      "EGT_ERR_INV_PIGGY_MSG"          : EGT_ERR_INV_PIGGY_MSG,
      "EGT_ERR_INV_TUNN_NET_EVNT"      : EGT_ERR_INV_TUNN_NET_EVNT,
      "EGT_ERR_INV_TUNN_USR_EVNT"      : EGT_ERR_INV_TUNN_USR_EVNT,
      "EGT_ERR_MSG_INV_INT"            : EGT_ERR_MSG_INV_INT,

      "EGT_TMGMT_REQTYPE_ADD"      : EGT_TMGMT_REQTYPE_ADD,
      "EGT_TMGMT_REQTYPE_DEL"      : EGT_TMGMT_REQTYPE_DEL,
      "EGT_TMGMT_REQTYPE_MOD"      : EGT_TMGMT_REQTYPE_MOD,
      "EGT_TMGMT_REQTYPE_STOP_QING"      : EGT_TMGMT_REQTYPE_STOP_QING,
      "EGT_TMGMT_REQTYPE_DEL_ALL"      : EGT_TMGMT_REQTYPE_DEL_ALL,
      "EGT_TMGMT_REQTYPE_REORD_ENA"      : EGT_TMGMT_REQTYPE_REORD_ENA,
      "EGT_TMGMT_REQTYPE_REORD_DIS"      : EGT_TMGMT_REQTYPE_REORD_DIS,
      "EGT_TMGMT_INV_ACTION"      : EGT_TMGMT_INV_ACTION,
      "EGT_GTPU_CAUSE_INV_SRC_IP"      : EGT_GTPU_CAUSE_INV_SRC_IP,
      "EGT_GTPU_CAUSE_INV_PORT"      : EGT_GTPU_CAUSE_INV_PORT,
      "EGT_GTPU_CAUSE_INV_DST_IP"      : EGT_GTPU_CAUSE_INV_DST_IP,
      "EGT_GTPU_CAUSE_NO_RES_AVAIL"      : EGT_GTPU_CAUSE_NO_RES_AVAIL,
      "EGT_GTPU_CAUSE_INV_TEID"      : EGT_GTPU_CAUSE_INV_TEID,
      "EGT_GTPU_CAUSE_REORD_DIS"      : EGT_GTPU_CAUSE_REORD_DIS,
      "EGT_GTPU_CAUSE_INV_ACTION"      : EGT_GTPU_CAUSE_INV_ACTION,
      "EGT_GTPU_CAUSE_DST_MULT_IP"      : EGT_GTPU_CAUSE_DST_MULT_IP,
      "EGT_EGTPU_CAUSE_PENDING_CNTRL_OP"      : EGT_EGTPU_CAUSE_PENDING_CNTRL_OP,
      "EGT_EGTPU_CAUSE_PROC_FAIL"      : EGT_EGTPU_CAUSE_PROC_FAIL,
      "EGT_ERR_MSG_MISS_MAND_IE"      : EGT_ERR_MSG_MISS_MAND_IE,
      "EGU_RECOVERY_IETYPE"      : EGU_RECOVERY_IETYPE,
      "EGT_EGTPU_REASON_DEST_UNREACH"      : EGT_EGTPU_REASON_DEST_UNREACH,
      
      "LEG_EGTP_C"      : LEG_EGTP_C,
      "LEG_EGTP_U"      : LEG_EGTP_U,
      "EG_REORDER_TYPE_1"      : EG_REORDER_TYPE_1,
      "EG_REORDER_TYPE_2"      : EG_REORDER_TYPE_2,
      "CM_TPTADDR_IPV4"      : CM_TPTADDR_IPV4,
      "CM_TPTADDR_IPV6"      : CM_TPTADDR_IPV6,

   "AQ_OCTET_STRING"         :  AQ_OCTET_STRING,
   "AQ_SIGNED_32"            :  AQ_SIGNED_32,
   "AQ_UNSIGNED_64"          :  AQ_UNSIGNED_64,
   "AQ_UNSIGNED_32"          :  AQ_UNSIGNED_32,
   "AQ_ENUMERATED"           :  AQ_ENUMERATED,
   "LAQ_MAX_NUM_OF_AVP_PROP"      :LAQ_MAX_NUM_OF_AVP_PROP,      
   "LAQ_MAX_NUM_OF_AVPS"      :LAQ_MAX_NUM_OF_AVPS,      
   "LAQ_MAX_NUM_OF_HOST_IDS"       :LAQ_MAX_NUM_OF_HOST_IDS,      
   "LAQ_MAX_NUM_OF_REALMS"      :LAQ_MAX_NUM_OF_REALMS,   
   "LAQ_MAX_NUM_OF_PEERS"      :LAQ_MAX_NUM_OF_PEERS,      
   "LAQ_MAX_NUM_OF_CMDS"      :LAQ_MAX_NUM_OF_CMDS,      
   "LAQ_MAX_OPT_AVP"      :LAQ_MAX_OPT_AVP,      
   "LAQ_MAX_HOST_TO_IP"      :LAQ_MAX_HOST_TO_IP,      
   "IP_CONN_ON"              : IP_CONN_ON,
   "LAQ_MAX_SUPP_VEN_ID"      :LAQ_MAX_SUPP_VEN_ID,   
   "LAQ_MAX_VEN_SPEC_APPID"   :LAQ_MAX_VEN_SPEC_APPID,
   "LAQ_MAX_INBAND_SEC"      :LAQ_MAX_INBAND_SEC,   
   "LAQ_MAX_APP_HOST_MAP"      :LAQ_MAX_APP_HOST_MAP,   
   "LAQ_MAX_APP_ID"      :LAQ_MAX_APP_ID,
   "LAQ_MIN_LSAPS"      :   LAQ_MIN_LSAPS,      
   "LAQ_MAX_LSAPS"      :   LAQ_MAX_LSAPS,      
   "LAQ_MIN_USAPS"      :   LAQ_MIN_USAPS,      
   "LAQ_MAX_USAPS"      :   LAQ_MAX_USAPS,      # /* maximum num of upper SAPs */
   "LAQ_MIN_PEERS"      :   LAQ_MIN_PEERS,      # /* minimum num of peers */
   "LAQ_MAX_PEERS"      :   LAQ_MAX_PEERS,      # /* maximum num of peers */
   "LAQ_MIN_REALMS"      :LAQ_MIN_REALMS,      # /* minimum num of realms */
   "LAQ_MAX_REALMS"      :LAQ_MAX_REALMS,      # /* maximum num of realms */
   "LAQ_MIN_WRKTHRDS"      :LAQ_MIN_WRKTHRDS,      # /* minimum num of worker threads */
   "LAQ_MAX_WRKTHRDS"      :LAQ_MAX_WRKTHRDS,   
        "LAQ_MIN_BURST_CNT"      :LAQ_MIN_BURST_CNT,      # /* minimum num of burst count */
   "LAQ_MAX_BURST_CNT"   :LAQ_MAX_BURST_CNT,      # /* maximum num of burst count */
   "LAQ_MIN_TMR_RES"   :LAQ_MIN_TMR_RES,      # /* minimum timer resolution */
   "EVTLAQCFGREQ"      :EVTLAQCFGREQ,      # /* configuration request */
   "EVTLAQCFGCFM"      :EVTLAQCFGCFM,      # /* configuration confirm */
   "EVTLAQCNTRLREQ"   :EVTLAQCNTRLREQ,      # /* control request */
   "EVTLAQCNTRLCFM"   :EVTLAQCNTRLCFM,      # /* control confirm */
   "EVTLAQSTAREQ"      :EVTLAQSTAREQ,      # /* status request */
   "EVTLAQSTACFM"      :EVTLAQSTACFM,      # /* status confirm */
   "EVTLAQSTSREQ"      :EVTLAQSTSREQ,      # /* statistics request */
   "EVTLAQSTSCFM"      :EVTLAQSTSCFM,      # /* statistics confirm */
   "EVTLAQSTAIND"      :EVTLAQSTAIND,      # /* status indicattion */
   "EVTLAQTRCIND"      :EVTLAQTRCIND,      # /* trace indicattion */
   "EVTLAQPRBREQ"      :EVTLAQPRBREQ,      # /* probe request */
   "EVTLAQPRBCFM"      :EVTLAQPRBCFM,      # /* probe confirm */
   "LAQ_SAP_CFG"      :LAQ_SAP_CFG,      # /* SAP Configured but not not bound */
   "LAQ_SAP_BND"      :LAQ_SAP_BND,      # /* SAP Bound */
   "LAQ_SAP_BINDING"   :LAQ_SAP_BINDING,      # /* SAP Bind initiated */
   "LAQ_SAP_UBND"      :LAQ_SAP_UBND,      # /* SAP UnBound */
   "LAQ_SAP_BND_ENB"   :LAQ_SAP_BND_ENB,      # /* SAP bind enabled */
   "LAQ_SAP_WAIT_BNDCFM"   :LAQ_SAP_WAIT_BNDCFM,      # /* SAP wait bind confirm */
   "LAQ_SEL_LC"      :LAQ_SEL_LC,      # /* Loose coupling */
   "LAQ_SEL_LWLC"      :LAQ_SEL_LWLC,      # /* Light weight loose coupling -
   "LAQ_SEL_TC_AB"      :LAQ_SEL_TC_AB,      # /* Tight coupling Diameter Base Protocol User */
   "LAQ_SEL_TC_HIT"   :LAQ_SEL_TC_HIT,      # /* Tight coupling TUCL */
   "LAQ_SEL_TC_SCT"   :LAQ_SEL_TC_SCT,      # /* Tight coupling SCTP */
   "LAQ_SEL_TC_SM"      :LAQ_SEL_TC_SM,      # /* Tight coupling SM */
   "LAQ_NRM_TERMINATION"   :LAQ_NRM_TERMINATION,      # /* normal termination */
   "LAQ_SHUTDOWN"      :LAQ_SHUTDOWN,      # /* shutdown */
   "LAQ_PWR_UP"      :LAQ_PWR_UP,      # /* power up */
   "LAQ_DONT_CARE"      :LAQ_DONT_CARE,      # /* dont care */
   "LAQIFVER"      :LAQIFVER,      # /* interface version 1.0 */
   "LAQ_TRANS_TYPE_TCP_TLS" :LAQ_TRANS_TYPE_TCP_TLS,      # /* TCP with TLS transport type */
   "LAQ_TRANS_TYPE_TCP_IPSEC":LAQ_TRANS_TYPE_TCP_IPSEC,      # /* TCP with IpSec transport type */
   "LAQ_TRANS_TYPE_TCP_BOTH":LAQ_TRANS_TYPE_TCP_BOTH,      # /* TCP with IpSec+TLS transport type */
   "LAQ_TRANS_TYPE_SCTP_IPSEC":LAQ_TRANS_TYPE_SCTP_IPSEC,      # /* SCTP with IpSec transport type */
   "LAQ_TRANS_TYPE_SCTP_TLS":LAQ_TRANS_TYPE_SCTP_TLS,      # /* SCTP with TLS transport type */
   "LAQ_TRANS_TYPE_SCTP_BOTH":LAQ_TRANS_TYPE_SCTP_BOTH,      # /* SCTP with IpSec+TLS transport type */
   "LAQ_MIN_TCP_PORT_NUM"   :LAQ_MIN_TCP_PORT_NUM,      # /* minimum TCP port number */
   "LAQ_MAX_TCP_PORT_NUM":LAQ_MAX_TCP_PORT_NUM,      # /* maximum TCP port number */
   "LAQ_MIN_SCTP_PORT_NUM":LAQ_MIN_SCTP_PORT_NUM,      # /* minimum SCTP port number */
   "LAQ_MAX_SCTP_PORT_NUM"   :LAQ_MAX_SCTP_PORT_NUM,      # /* maximum SCTP port number */
   "STAQGEN"      :      STAQGEN,      # /* general */
   "STAQPROT"      :      STAQPROT,      # /* protocol */
   "STAQUSAP"      :      STAQUSAP,      # /* upper SAP */
   "STAQLSAP"      :      STAQLSAP,      # /* lower SAP */
   "STAQREALM"      :      STAQREALM,      # /* Realm */
   "STAQPEER"      :      STAQPEER,      # /* Peer */
   "STAQAVP"      :      STAQAVP,      # /* AVP Dictionary */
   "STAQDM"      :      STAQDM,      # /* DM Dictionary */
   "STAQALLREALM"      :      STAQALLREALM,      # /* All Realms */
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   "STAQALLPEER"       :      STAQALLPEER,       # /* All Peers */
   "AQ_ALL_CONNS"      :      AQ_ALL_CONNS,      # /* All Conns */
   "STAQSID"      :      STAQSID,      # /* System Id */
	"STAQPRAPP"		:		STAQPRAPP,		# /* particular app */
	"STAQPRALLAPP"		:		STAQPRALLAPP,		# /* All appIds */

   "STJCGEN"      :      STJCGEN,      # /* JC General */
   "STJCRSET"     :      STJCRSET,     # /* JC Resource set */
   "STJCSID"      :      STJCSID,      # /* JC System Id */
   "STJCGENCFG"   :      STJCGENCFG,   # /* JC General configuration */
   "LAQ_EVENT_CONN_OK"      :LAQ_EVENT_CONN_OK,      # /* connection with peer is OK */
   "LAQ_EVENT_CONN_FAIL"      :LAQ_EVENT_CONN_FAIL,      # /* connection with peer failed */
   "LAQ_EVENT_MAX_CONN_RETRY":LAQ_EVENT_MAX_CONN_RETRY,      # /* max connection retry count has reached */
   "LAQ_EVENT_FAILOVER_INIT"      :   LAQ_EVENT_FAILOVER_INIT,      # /* indication that fialover was started for the peer */
   "LAQ_EVENT_PEER_DOWN"      :LAQ_EVENT_PEER_DOWN,      # /* indication that the peer is down */
   "LAQ_EVENT_PEER_UP"      :LAQ_EVENT_PEER_UP,      # /* indication that the peer is up */
   "LAQ_EVENT_PEER_DOWN_PERM"      :LAQ_EVENT_PEER_DOWN_PERM,      # /* indication that the peer is down permanently */
   "LAQ_EVENT_NO_ALT_PEER_FOUND"      :LAQ_EVENT_NO_ALT_PEER_FOUND,      # /* indication that no alternate peer was found */
   "LAQ_EVENT_PEER_NOT_INSERTED"      :LAQ_EVENT_PEER_NOT_INSERTED,      # /* indication that peer is not inserted into peer table */
   "LAQ_EVENT_REALM_NOT_INSERTED"      :      LAQ_EVENT_REALM_NOT_INSERTED,      # /* indication that realm is not inserted into realm table */
   "LAQ_EVENT_PEER_DELETED"      :      LAQ_EVENT_PEER_DELETED,      # /* indication that peer is deleted */
   "LAQ_EVENT_UI_SAP_UBND_SUCC"      :      LAQ_EVENT_UI_SAP_UBND_SUCC,      # /* SAP unbind succeeded */
   "LAQ_EVENT_OPEN_SERV_FAIL"      :      LAQ_EVENT_OPEN_SERV_FAIL,      # /* server opening failed */
   "LAQ_EVENT_LI_BND_CFM"      :      LAQ_EVENT_LI_BND_CFM,      # /* bind confirm from lower layer */
   "LAQ_EVENT_LI_HIT_CON_CFM"      :      LAQ_EVENT_LI_HIT_CON_CFM,      # /* connection confirm from HIT interface */
   "LAQ_EVENT_LI_HIT_CON_IND"      :      LAQ_EVENT_LI_HIT_CON_IND,      # /* connection indication from HIT interface */
   "LAQ_EVENT_LI_SCT_ENDP_OPEN_CFM"      :      LAQ_EVENT_LI_SCT_ENDP_OPEN_CFM,      # /* end point open confirm from SCT interface */
   "LAQ_EVENT_LI_SCT_ENDP_CLOSE_CFM"      :      LAQ_EVENT_LI_SCT_ENDP_CLOSE_CFM,      # /* end point close confirm from SCT interface */
   "LAQ_EVENT_LI_SCT_ENDP_ASSOC_IND"      :      LAQ_EVENT_LI_SCT_ENDP_ASSOC_IND,      # /* Association indication from SCT interface */
   "LAQ_EVENT_LI_SCT_ENDP_ASSOC_CFM"      :      LAQ_EVENT_LI_SCT_ENDP_ASSOC_CFM,      # /* Association confirm from SCT interface */
   "LAQ_EVENT_LI_HIT_DAT_IND"      :      LAQ_EVENT_LI_HIT_DAT_IND,      # /* data indication from HIT interface */
   "LAQ_EVENT_LI_SCT_DAT_IND"      :      LAQ_EVENT_LI_SCT_DAT_IND,      # /* data indication from SCT interface */
   "LAQ_EVENT_LI_HIT_DISC_IND"      :      LAQ_EVENT_LI_HIT_DISC_IND,      # /* disconnect indication from HIT interface */
   "LAQ_EVENT_LI_SCT_TERM_IND"      :      LAQ_EVENT_LI_SCT_TERM_IND,      # /* termination indication from SCT interface */
   "LAQ_EVENT_LI_SCT_TERM_CFM"      :      LAQ_EVENT_LI_SCT_TERM_CFM,      # /* termination confirm from SCT interface */
   "LAQ_EVENT_LI_SCT_SET_PRI_CFM"      :      LAQ_EVENT_LI_SCT_SET_PRI_CFM,      # /* set prority confirm from SCT interface */
   "LAQ_EVENT_LI_SCT_HBEAT_CFM"      :      LAQ_EVENT_LI_SCT_HBEAT_CFM,      # /* heart beat confirm from SCT interface */
   "LAQ_EVENT_LI_SCT_STA_CFM"      :      LAQ_EVENT_LI_SCT_STA_CFM,      # /* status confirm from SCT interface */
   "LAQ_EVENT_LI_SCT_STA_IND"      :      LAQ_EVENT_LI_SCT_STA_IND,      # /* status indication from SCT interface */
   "LAQ_EVENT_LI_HIT_FLC_IND"      :      LAQ_EVENT_LI_HIT_FLC_IND,      # /* flow control indication from HIT interface */
   "LAQ_EVENT_LI_SCT_FLC_IND"      :      LAQ_EVENT_LI_SCT_FLC_IND,      # /* flow control indication from SCT interface */
   "LAQ_EVENT_OPEN_SERV_UP"      :      LAQ_EVENT_OPEN_SERV_UP,      # /* server opening succeeded */
        "LAQ_EVENT_PEER_INSERTED"              :                LAQ_EVENT_PEER_INSERTED,
        "LAQ_EVENT_RECONN_TIMEOUT"             :                LAQ_EVENT_RECONN_TIMEOUT,
   "LAQ_USTA_DGNVAL_NONE"      :      LAQ_USTA_DGNVAL_NONE,      #
   "LAQ_USTA_DGNVAL_MEM"      :      LAQ_USTA_DGNVAL_MEM,      #
   "LAQ_USTA_DGNVAL_SAPID"      :      LAQ_USTA_DGNVAL_SAPID,      #
   "LAQ_USTA_DGNVAL_APPID"      :      LAQ_USTA_DGNVAL_APPID,      #
   "LAQ_USTA_DGNVAL_PEER"      :      LAQ_USTA_DGNVAL_PEER,      #
   "LAQ_USTA_DGNVAL_REALM"      :      LAQ_USTA_DGNVAL_REALM,      #
   "LAQ_USTA_DGNVAL_AVPCODE"      :      LAQ_USTA_DGNVAL_AVPCODE,      #
   "LAQ_USTA_MAX_DGNVAL"      :      LAQ_USTA_MAX_DGNVAL,      #
   "LAQ_START"      :      LAQ_START,      # /* start */
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   "LAQ_DEL_PEER"   :      LAQ_DEL_PEER,      # /* delete peer */
   "LAQ_STOP"       :      LAQ_STOP,      # /* stop */
   "LAQ_STOP_IMM"       :      LAQ_STOP_IMM,  # /* stop  immediately*/
   "SAUSTA"      :      SAUSTA,      # /* unsolicited status generation */
   "SAELMNT"      :      SAELMNT,      # /* unsolicited status generation */
        "SADBG"                 :               SADBG,
   "LAQ_SAALL"      :      LAQ_SAALL,      # /* Overload message to peer */
   "LAQ_SPEC"      :      LAQ_SPEC,      # /* specific to peer and realm */
   "LAQ_MAX_TRC_LEN"      :      LAQ_MAX_TRC_LEN,      #
   "LAQ_TRC_PNODE"      :      LAQ_TRC_PNODE,      #
   "LAQ_TRC_LSAP_IN"      :      LAQ_TRC_LSAP_IN,      #
   "LAQ_TRC_LSAP_OUT"      :      LAQ_TRC_LSAP_OUT,      #
   "LAQ_TRC_PNODE_IN"      :      LAQ_TRC_PNODE_IN,      #
   "LAQ_TRC_PNODE_OUT"      :      LAQ_TRC_PNODE_OUT,      #
   "LAQ_EVENT_RESET_FAIL"      :      LAQ_EVENT_RESET_FAIL ,
   "LAQ_EVENT_DMEM_ALLOC_PASS"      :      LAQ_EVENT_DMEM_ALLOC_PASS ,
   "LAQ_EVENT_AUDIT_FIN"      :      LAQ_EVENT_AUDIT_FIN       ,
   "LAQ_CAUSE_N_RETRY"      :      LAQ_CAUSE_N_RETRY       ,
   "LAQ_CAUSE_UNKNOWN_OPT_AVP"      :      LAQ_CAUSE_UNKNOWN_OPT_AVP,
   "LAQ_CAUSE_NO_PEER_INOPEN_ST"      :      LAQ_CAUSE_NO_PEER_INOPEN_ST,
   "LAQ_CAUSE_INV_SRV_STATE"      :      LAQ_CAUSE_INV_SRV_STATE,
   "LAQ_CAUSE_NO_COMM_APP"      :      LAQ_CAUSE_NO_COMM_APP,
   "LAQ_CAUSE_NO_COMM_SEC"      :      LAQ_CAUSE_NO_COMM_SEC,
   "LAQ_CAUSE_CER_EXCHGD"      :      LAQ_CAUSE_CER_EXCHGD,
   "LAQ_CAUSE_DPR_SENT"      :      LAQ_CAUSE_DPR_SENT,
   "LAQ_CAUSE_DPR_RCVD"      :      LAQ_CAUSE_DPR_RCVD,
   "LAQ_CAUSE_DW_TIMEOUT"      :      LAQ_CAUSE_DW_TIMEOUT,
   "LAQ_CAUSE_TERM_IND"      :      LAQ_CAUSE_TERM_IND,
   "LAQ_CAUSE_TCP_IPSEC_SRV_OPEN_FAIL"      :      LAQ_CAUSE_TCP_IPSEC_SRV_OPEN_FAIL ,
   "LAQ_CAUSE_TCP_TLS_SRV_OPEN_FAIL"      :      LAQ_CAUSE_TCP_TLS_SRV_OPEN_FAIL    ,
   "LAQ_CAUSE_SCTP_IPSEC_SRV_OPEN_FAIL"      :      LAQ_CAUSE_SCTP_IPSEC_SRV_OPEN_FAIL ,
   "LAQ_CAUSE_DEC"      :      LAQ_CAUSE_DEC ,
   "LAQ_CAUSE_TCP_IPSEC_SRV_UP"      :      LAQ_CAUSE_TCP_IPSEC_SRV_UP ,
   "LAQ_CAUSE_TCP_TLS_SRV_UP"      :      LAQ_CAUSE_TCP_TLS_SRV_UP,
   "LAQ_CAUSE_SCTP_IPSEC_SRV_UP"      :      LAQ_CAUSE_SCTP_IPSEC_SRV_UP ,
   "LAQ_CAUSE_TCP_IPSEC_SRV_DISCONNECTED"      :      LAQ_CAUSE_TCP_IPSEC_SRV_DISCONNECTED,
   "LAQ_CAUSE_TCP_TLS_SRV_DISCONNECTED"      :      LAQ_CAUSE_TCP_TLS_SRV_DISCONNECTED,
   "LAQ_CAUSE_SCTP_IPSEC_SRV_DISCONNECTED"      :      LAQ_CAUSE_SCTP_IPSEC_SRV_DISCONNECTED,
   "LAQ_CAUSE_TCP_IPSEC_SRV_OPEN_SUCC"      :      LAQ_CAUSE_TCP_IPSEC_SRV_OPEN_SUCC,
   "LAQ_CAUSE_TCP_TLS_SRV_OPEN_SUCC"      :      LAQ_CAUSE_TCP_TLS_SRV_OPEN_SUCC ,
   "LAQ_CAUSE_SCTP_IPSEC_SRV_OPEN_SUCC"      :      LAQ_CAUSE_SCTP_IPSEC_SRV_OPEN_SUCC ,
   "LAQ_PROT_NONE"      :      LAQ_PROT_NONE,      #
   "LAQ_PROT_TCP"      :      LAQ_PROT_TCP,      #
   "LAQ_PROT_SCTP"      :      LAQ_PROT_SCTP,      #
        "LAQ_TSAP_TYPE_TUCL"      :      LAQ_TSAP_TYPE_TUCL,      #
   "LAQ_TSAP_TYPE_SCTP"      :      LAQ_TSAP_TYPE_SCTP,      #
   "LAQ_TSAP_TYPE_DTUCL"      :      LAQ_TSAP_TYPE_DTUCL,      #
   "LAQ_TSAP_TYPE_DSCTP"      :      LAQ_TSAP_TYPE_DSCTP,      #
   "LAQ_TPTSRV_MAX_SSAP"      :      LAQ_TPTSRV_MAX_SSAP,      #
   "LAQ_HOSTNAME_MAX_SZ"      :      LAQ_HOSTNAME_MAX_SZ,      #
   "LAQ_NO_INBAND_SEC"      :      LAQ_NO_INBAND_SEC,      #
   "LAQ_SEC_TLS"      :      LAQ_SEC_TLS,      #
   "LAQ_SEC_IPSEC"      :      LAQ_SEC_IPSEC,      #
   "LAQ_SEC_BOTH"      :      LAQ_SEC_BOTH,      #
   "LAQ_MAX_CONN_RETRY_CNT"      :      LAQ_MAX_CONN_RETRY_CNT,      #
   "LAQ_PEER_STATIC"      :      LAQ_PEER_STATIC,      #
   "LAQ_PEER_DYNAMIC"      :      LAQ_PEER_DYNAMIC,      #
   "LAQ_PEER_UNKNOWN"      :      LAQ_PEER_UNKNOWN,      #
   "LAQ_PEER_DSC_NONE"      :      LAQ_PEER_DSC_NONE,      #
   "LAQ_PEER_DSC_SLP"      :      LAQ_PEER_DSC_SLP,      #
   "LAQ_PEER_DSC_NAPTR"      :      LAQ_PEER_DSC_NAPTR,      #
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   "LAQ_PEER_PRIMARY"        :      LAQ_PEER_PRIMARY,      #
   "LAQ_PEER_SECONDARY"      :      LAQ_PEER_SECONDARY,      #
   "LAQ_ACTION_LOCAL"      :      LAQ_ACTION_LOCAL,      #
   "LAQ_ACTION_RELAY"      :      LAQ_ACTION_RELAY,      #
   "LAQ_ACTION_PROXY"      :      LAQ_ACTION_PROXY,      #
   "LAQ_ACTION_REDIRECT"      :      LAQ_ACTION_REDIRECT,      #
   "LAQ_INCOMING_CONN_ACCEPT"      :      LAQ_INCOMING_CONN_ACCEPT,      #
   "LAQ_INCOMING_CONN_DENY"      :      LAQ_INCOMING_CONN_DENY,      #
   "LAQ_REASON_PROTCFG_NOT_DONE"      :      LAQ_REASON_PROTCFG_NOT_DONE,
   "LAQ_REASON_INVALID_DOMAIN"      :      LAQ_REASON_INVALID_DOMAIN,
   "LAQ_REASON_HASHINIT_FAIL"      :      LAQ_REASON_HASHINIT_FAIL,
   "LAQ_REASON_SAP_ASSOC_EXISTS"      :      LAQ_REASON_SAP_ASSOC_EXISTS,
   "LAQ_REASON_LSAPCFG_NOT_DONE"      :      LAQ_REASON_LSAPCFG_NOT_DONE,
   "LAQ_REASON_INV_PAR_VAL"      :      LAQ_REASON_INV_PAR_VAL   ,
   "LAQ_REASON_INV_NMB_LSAPS"      :      LAQ_REASON_INV_NMB_LSAPS,
   "LAQ_REASON_INV_NMB_USAPS"      :      LAQ_REASON_INV_NMB_USAPS,
   "LAQ_REASON_INV_NMB_PEERS"      :      LAQ_REASON_INV_NMB_PEERS,
   "LAQ_REASON_INV_NMB_REALMS"      :      LAQ_REASON_INV_NMB_REALMS,
   "LAQ_REASON_INV_NMB_WRKTHRDS"      :      LAQ_REASON_INV_NMB_WRKTHRDS,
   "LAQ_REASON_INV_NMB_BURST_CNT"      :      LAQ_REASON_INV_NMB_BURST_CNT,
   "LAQ_REASON_INV_USAP_CFG"      :      LAQ_REASON_INV_USAP_CFG,
   "LAQ_REASON_INV_TCP_PORT"      :      LAQ_REASON_INV_TCP_PORT,
   "LAQ_REASON_INV_SCTP_PORT"      :      LAQ_REASON_INV_SCTP_PORT,
   "LAQ_REASON_INV_TRANS_TYPE"      :      LAQ_REASON_INV_TRANS_TYPE,
   "LAQ_REASON_INV_PROT_TIMERS"      :      LAQ_REASON_INV_PROT_TIMERS,
   "LAQ_REASON_INV_PEER_DSC_TYPE"      :      LAQ_REASON_INV_PEER_DSC_TYPE,
   "LAQ_REASON_INV_SEC_TYPE"      :      LAQ_REASON_INV_SEC_TYPE,
   "LAQ_REASON_INV_MAX_RETRY_CNT"      :      LAQ_REASON_INV_MAX_RETRY_CNT,
   "LAQ_REASON_INV_LCL_POLICY"      :      LAQ_REASON_INV_LCL_POLICY,
   "LAQ_REASON_INV_PROT"      :      LAQ_REASON_INV_PROT,
   "LAQ_REASON_INV_NUM_OF_APPS"      :      LAQ_REASON_INV_NUM_OF_APPS,
   "LAQ_REASON_INV_LOCAL_ACTION"      :      LAQ_REASON_INV_LOCAL_ACTION,
   "LAQ_REASON_INV_APP_ID"      :      LAQ_REASON_INV_APP_ID,
   "LAQ_REASON_INV_SAP_STATE"      :      LAQ_REASON_INV_SAP_STATE,
   "LAQ_REASON_INV_SUBACTION_ITEM"      :      LAQ_REASON_INV_SUBACTION_ITEM,
   "LAQ_REASON_INV_ACTION_ITEM"      :      LAQ_REASON_INV_ACTION_ITEM,
   "LAQ_REASON_UPD_HOST_CER_FAILED"      :      LAQ_REASON_UPD_HOST_CER_FAILED,
   "LAQ_REASON_MEM_ALLOC_FAILED"      :      LAQ_REASON_MEM_ALLOC_FAILED,
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
   "LAQ_REASON_INV_PMQ_SIZE"               :      LAQ_REASON_INV_PMQ_SIZE,
   "LAQ_REASON_INV_HOST_NAME"              :      LAQ_REASON_INV_HOST_NAME, 
   "LAQ_REASON_INV_REALM_NAME"             :     LAQ_REASON_INV_REALM_NAME,
   "LAQ_REASON_INV_PROD_NAME"              :     LAQ_REASON_INV_PROD_NAME,
   "LAQ_REASON_INV_PEER_CFG"              :     LAQ_REASON_INV_PEER_CFG,
   "LAQ_REASON_INV_NODE_TYPE"              :     LAQ_REASON_INV_NODE_TYPE,
   "LAQ_REASON_INV_NMB_AVPS"              :     LAQ_REASON_INV_NMB_AVPS,
   "LAQ_REASON_INV_NMB_CMDS"              :     LAQ_REASON_INV_NMB_CMDS,
   "LAQ_REASON_USAPCFG_NOT_DONE"              :     LAQ_REASON_USAPCFG_NOT_DONE,
   "LAQ_REASON_UNKNOWN"              :     LAQ_REASON_UNKNOWN,
   "LAQ_REASON_INV_AVP_CFG"              :     LAQ_REASON_INV_AVP_CFG,
   "LAQ_REASON_INV_DM_CFG"              :     LAQ_REASON_INV_DM_CFG,
   "LAQ_REASON_INV_CFG_PARAMS"              :     LAQ_REASON_INV_CFG_PARAMS,
   "LAQ_REASON_INV_REALM_CFG"              :     LAQ_REASON_INV_REALM_CFG,
   "LAQ_REASON_INV_APP_HOST_MAP"              :     LAQ_REASON_INV_APP_HOST_MAP,
   "LAQ_REASON_INV_PEER_DSC_SERVICE"     :        LAQ_REASON_INV_PEER_DSC_SERVICE,
   "LAQ_REASON_INV_AGENT_CFG"              :      LAQ_REASON_INV_AGENT_CFG,
   "LAQ_REASON_RECONFIG_FAILED"            :      LAQ_REASON_RECONFIG_FAILED,
   "LAQ_REASON_INV_AGENT_TYPE"             :      LAQ_REASON_INV_AGENT_TYPE,
   "LAQ_REASON_MAX_REALM_MAP_REACHED"      :      LAQ_REASON_MAX_REALM_MAP_REACHED,
   "LAQ_REASON_MAX_APP_REACHED_IN_REALM"   :      LAQ_REASON_MAX_APP_REACHED_IN_REALM,
   "LAQ_REASON_INV_DFLT_REALM"             :      LAQ_REASON_INV_DFLT_REALM,
   "LAQ_REASON_RESOURCE_IN_USE"            :      LAQ_REASON_RESOURCE_IN_USE,
   "LAQ_REASON_INV_PEER_DESIG"             :      LAQ_REASON_INV_PEER_DESIG,
   "LAQ_REASON_INV_NMB_OF_CONNS"           :      LAQ_REASON_INV_NMB_OF_CONNS,
   "LAQ_REASON_PEERS_ACTIVE"               :      LAQ_REASON_PEERS_ACTIVE,
   "LAQ_REASON_SPECIFIED_PEERS_NOT_PRSNT"  :      LAQ_REASON_SPECIFIED_PEERS_NOT_PRSNT,
   "AQ_AUTH_TYPE"      :      AQ_AUTH_TYPE,      # /* Reset the statistics counters */
   "AQ_ACTT_TYPE"      :      AQ_ACTT_TYPE,      # /* no reset of statistics counters */
   "LAQ_ZEROSTS"      :      LAQ_ZEROSTS,      # /* Reset the statistics counters */
   "LAQ_NOZEROSTS"      :      LAQ_NOZEROSTS,      # /* no reset of statistics counters */
   "LAQ_PART_NUM_STR_LEN"      :      LAQ_PART_NUM_STR_LEN,      #
   "LAQ_DATAGRAM_LIFETIME"      :      LAQ_DATAGRAM_LIFETIME,      #
   "LAQIFVER"      :      LAQIFVER,      # /* interface version 1.0 */
   "LAQ_MAX_STR_SIZE"      :      LAQ_MAX_STR_SIZE,      #
   "ELAQBASE"      :      ELAQBASE,      # /* base */
   "ELAQXXX"      :      ELAQXXX,      #
        "LAQ_CLIENT"            :               LAQ_CLIENT,
        "LAQ_SERVER"            :               LAQ_SERVER,
        "LAQ_BOTH"              :               LAQ_BOTH,
        "CM_IPV4ADDR_TYPE"      :               CM_IPV4ADDR_TYPE,
        "CM_IPV6ADDR_TYPE"      :               CM_IPV6ADDR_TYPE,
        "CM_NETADDR_IPV4"      :               CM_NETADDR_IPV4,
        "CM_NETADDR_IPV6"      :               CM_NETADDR_IPV6,
         "AQU_AVP_FLAG_VENDOR_SPF"   :      AQU_AVP_FLAG_VENDOR_SPF,      # /* Diameter request message */
   "AQU_AVP_FLAG_MANDATORY":      AQU_AVP_FLAG_MANDATORY,      # /* Diameter request message */
   "AQU_AVP_FLAG_ENCRYPT"      :      AQU_AVP_FLAG_ENCRYPT,      # /* Diameter request message */
   "AQU_PRIM_OK"      :      AQU_PRIM_OK,      #
   "AQU_PRIM_NOK"      :      AQU_PRIM_NOK,      #
   "AQU_SUCCESS"      :      AQU_SUCCESS,      # /* success */
        "AQU_ERR_ENC"           :               AQU_ERR_ENC,
        "AQU_ERR_RSRC"          :               AQU_ERR_RSRC,
        "AQU_ERR_INV_REQUEST"   :               AQU_ERR_INV_REQUEST, 
        "AQU_ERR_INV_DM_HDR"    :               AQU_ERR_INV_DM_HDR,  
        "AQU_ERR_INV_APP_ID"    :               AQU_ERR_INV_APP_ID,     
        "AQU_ERR_INV_CMD_FLAGS" :               AQU_ERR_INV_CMD_FLAGS,   
        "AQU_ERR_MISSING_MND_AVP" :             AQU_ERR_MISSING_MND_AVP,       
        "AQU_ERR_AVP_NOT_IN_FXD_POS"  :         AQU_ERR_AVP_NOT_IN_FXD_POS,    
        "AQU_ERR_INV_SAP_STATE"     :           AQU_ERR_INV_SAP_STATE,        
        "AQU_ERR_INV_MSG"           :           AQU_ERR_INV_MSG,             
        "AQU_ERR_INV_PARAM"         :           AQU_ERR_INV_PARAM,          
        "AQU_ERR_PEER_UNDER_SUSPECT" :          AQU_ERR_PEER_UNDER_SUSPECT,
        "AQU_ERR_PEER_DOWN"          :          AQU_ERR_PEER_DOWN,        
        "AQU_ERR_NO_ALT_PEER"        :          AQU_ERR_NO_ALT_PEER,     
        "AQU_ERR_UNABLE_TO_DELIVER"  :          AQU_ERR_UNABLE_TO_DELIVER,      
        "AQU_ERR_MEM_ALLOC_FAILED"   :          AQU_ERR_MEM_ALLOC_FAILED,      
#cm_xta_py_py_001.main_50 : Added macros for diameter 1.3 release.
        "AQU_IND_PEER_DELETED"       :      AQU_IND_PEER_DELETED,
        "AQU_ERR_PEER_UNDER_SUSPECT_NO_ALT_PEER"  : AQU_ERR_PEER_UNDER_SUSPECT_NO_ALT_PEER,
        "AQU_ERR_INV_ORIG_HOST"                   : AQU_ERR_INV_ORIG_HOST,                 
        "AQU_ERR_INV_ORIG_REALM"                  : AQU_ERR_INV_ORIG_REALM,                
        "AQU_ERR_DUPLICATE_TRANS_ID"              : AQU_ERR_DUPLICATE_TRANS_ID,            
        "AQU_ERR_SHUTDOWN_IN_PROGRESS"            : AQU_ERR_SHUTDOWN_IN_PROGRESS,          
        "AQU_ERR_TRANS_INV_TTYPE"                 : AQU_ERR_TRANS_INV_TTYPE,               
        "AQU_ERR_TRANS_HDR_MAP"                   : AQU_ERR_TRANS_HDR_MAP,                 
        "AQU_ERR_TRANS_AVP_ATTR_MAP"              : AQU_ERR_TRANS_AVP_ATTR_MAP,            
        "AQU_ERR_PMQ_FULL"                        : AQU_ERR_PMQ_FULL,                      
        "AQU_ERR_REQ_TMR_EXPIRED"                 : AQU_ERR_REQ_TMR_EXPIRED,               
        "AQU_ERR_INV_HOST_CONN_COMB"              : AQU_ERR_INV_HOST_CONN_COMB,            
        "AQU_ERR_CONN_CONGESTED"                  : AQU_ERR_CONN_CONGESTED,                
        "AQU_ERR_INV_CONN_ID"                     : AQU_ERR_INV_CONN_ID,                   
        "AQU_ERR_INV_CMD_CODE"        :     AQU_ERR_INV_CMD_CODE,               
        "AQU_ERR_UNSUPP_APPID"         :     AQU_ERR_UNSUPP_APPID,  
        "AQU_ERR_INV_CMD_FLAG"         :     AQU_ERR_INV_CMD_FLAG,          
        "AQU_ERR_INV_AVP_FLAGS"        :     AQU_ERR_INV_AVP_FLAGS,            

        "AQU_ERR_AVP_UNSUPP"          :    AQU_ERR_AVP_UNSUPP,
        "AQU_ERR_INV_AVP_VALUE"       :    AQU_ERR_INV_AVP_VALUE,    
        "AQU_ERR_MISSING_MAND_AVP"    :    AQU_ERR_MISSING_MAND_AVP,  
        "AQ_ERR_NO_COMM_SEC"          :    AQ_ERR_NO_COMM_SEC,
        "AQ_ERR_NO_COMM_APP"          :    AQ_ERR_NO_COMM_APP,
        "AQU_ERR_AVP_NOT_ALLOWED"     :    AQU_ERR_AVP_NOT_ALLOWED,
        "AQU_ERR_AVP_NOT_ALLOWED"     :    AQU_ERR_AVP_NOT_ALLOWED,
        "AQU_ERR_CONTRADICT_AVPS"     :    AQU_ERR_CONTRADICT_AVPS,      
        "AQU_ERR_TOO_MANY_AVP_OCC"    :    AQU_ERR_TOO_MANY_AVP_OCC,
        "AQU_ERR_INV_VERSION"         :    AQU_ERR_INV_VERSION,        
        "AQU_ERR_UNABLE_TO_COMPLY"    :    AQU_ERR_UNABLE_TO_COMPLY,  
        "AQU_ERR_INV_HDR_BIT"         :    AQU_ERR_INV_HDR_BIT,      
        "AQU_ERR_INV_AVP_LEN"         :    AQU_ERR_INV_AVP_LEN,     
        "AQU_ERR_INV_MSG_LEN"         :    AQU_ERR_INV_MSG_LEN,    

        "AQU_ERR_FIXED_AVP_POS"       :    AQU_ERR_FIXED_AVP_POS,            
        "AQU_ERR_INV_AVP_TYPE"        :    AQU_ERR_INV_AVP_TYPE,            
        "AQU_ERR_MND_AVP_DEC_FAIL"    :    AQU_ERR_MND_AVP_DEC_FAIL,
        "AQU_ERR_HBH_ID_NOTPRSNT"     :    AQU_ERR_HBH_ID_NOTPRSNT,
        "AQ_ERR_UNABLE_TO_DELIVER"    :    AQ_ERR_UNABLE_TO_DELIVER,
        "AQ_LOOP_DETECTED"            :    AQ_LOOP_DETECTED,
        "AQ_ERR_REALM_NOT_SERVED"     :    AQ_ERR_REALM_NOT_SERVED,
       
   "EVTAQUBNDREQ"      :      EVTAQUBNDREQ,      # /* bind request */
   "EVTAQUBNDCFM"      :      EVTAQUBNDCFM,      # /* bind confirm */
   "EVTAQUUBNDREQ"      :      EVTAQUUBNDREQ,      # /* unbind request */
   "EVTAQUDMMSGREQ"      :      EVTAQUDMMSGREQ,      # /* diameter message request */
   "EVTAQUDMMSGIND"      :      EVTAQUDMMSGIND,      # /* diameter message indication */
   "EVTAQUDMMSGRSP"      :      EVTAQUDMMSGRSP,      # /* diameter message response */
   "EVTAQUDMMSGCFM"      :      EVTAQUDMMSGCFM,      # /* diameter message confirmation */
   "EVTAQURMVTXREQ"      :      EVTAQURMVTXREQ,      # /* remove transaction details request */
   "EVTAQURMVTXCFM"      :      EVTAQURMVTXCFM,      # /* remove transaction details confirm */
   "EVTAQUPEERDWNIND"      :      EVTAQUPEERDWNIND,      # /* peer down indication */
   "EVTAQUPEERUPIND"      :      EVTAQUPEERUPIND,      # /* peer up indication */
   "EVTAQUFLCIND"      :      EVTAQUFLCIND,      # /* flow control indication */
   "AQU_SEL_LC"      :      AQU_SEL_LC,      # /* loose couple */
   "AQU_SEL_TC"      :      AQU_SEL_TC,      # /* tight couple */
   "AQU_SEL_LWLC"      :      AQU_SEL_LWLC,      # /* light weight loose couple */
   "AQU_SAP_BND"      :      AQU_SAP_BND,      # /* SAP binded */
   "AQU_SAP_CFG"      :      AQU_SAP_CFG,      # /* SAP configured */
   "AQU_MAX_STR_SIZE"      :      AQU_MAX_STR_SIZE,      #
   "AQ_MAX_TRANS_IDS"      :      AQ_MAX_TRANS_IDS,      #
   "EAQUXXX"      :      EAQUXXX,   
   
        "AQ_ACR_CMD_CODE"       :            AQ_ACR_CMD_CODE,
        "AQ_ASR_CMD_CODE"       :           AQ_ASR_CMD_CODE,     
        "AQ_RAR_CMD_CODE"       :           AQ_RAR_CMD_CODE, 
        "AQ_STR_CMD_CODE"       :           AQ_STR_CMD_CODE, 
        "AQ_DPR_CMD_CODE"       :           AQ_DPR_CMD_CODE, 
        "AQ_DWR_CMD_CODE"       :           AQ_DWR_CMD_CODE, 
        "AQ_CER_CMD_CODE"       :           AQ_CER_CMD_CODE, 
        "AQ_ERR_CMD_CODE"       :           AQ_ERR_CMD_CODE, 
 
        "AQ_CX_DX_UAR_CMD_CODE"  :         AQ_CX_DX_UAR_CMD_CODE,
   "AQ_CX_DX_SAR_CMD_CODE"       :  AQ_CX_DX_SAR_CMD_CODE,
   "AQ_CX_DX_LIR_CMD_CODE"       :   AQ_CX_DX_LIR_CMD_CODE,
   "AQ_CX_DX_MAR_CMD_CODE"       :  AQ_CX_DX_MAR_CMD_CODE,
   "AQ_CX_DX_RTR_CMD_CODE"       :  AQ_CX_DX_RTR_CMD_CODE,
   "AQ_CX_DX_PPR_CMD_CODE"       :  AQ_CX_DX_PPR_CMD_CODE,
   "SSL_FILETYPE_PEM"            : SSL_FILETYPE_PEM,
   "SSL_VERIFY_PEER"                  : SSL_VERIFY_PEER,
   "SSL_VERIFY_FAIL_IF_NO_PEER_CERT"  : SSL_VERIFY_FAIL_IF_NO_PEER_CERT,
   "HI_TLS_SSLV3_METHOD"              : HI_TLS_SSLV3_METHOD,
   "HI_TLS_SSLV23_METHOD"             : HI_TLS_SSLV23_METHOD,
   "DUMMY_TUCL"                       : DUMMY_TUCL,
   "DUMMY_SCTP"                       : DUMMY_SCTP,
   "DUMMY_SCTP"                       : DUMMY_SCTP,
   "LCM_PRIM_OK": LCM_PRIM_OK,
   "LCM_REASON_INVALID_MSGTYPE" :LCM_REASON_INVALID_MSGTYPE,
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   "LCM_REASON_UPDTMR_EXPIRED"   :LCM_REASON_UPDTMR_EXPIRED,
   "ENTRR"  :  ENTRR,
   "ENTRL" :  ENTRL,     
   "ENTTC"  :  ENTTC,          
   "ENTSM"  :  ENTSM,
   "ENTLR"  :  ENTLR,
   "ENTLX"  :  ENTLX,
   "ENTXU"  :  ENTXU,
   "TCP"    :  TCP,
   "RTP"    :  RTP,
   "UDP"    :  UDP,
   "ESP"    :  ESP,
   "IPV4"   :  IPV4,
   "GRE"   :  GRE,
   "AH"     :  AH,
   "IPV6"   :  IPV6,
   "IPV6F"  :  IPV6F,
   "IR_PKT" :  IR_PKT,
   "IR_DYN_PKT" : IR_DYN_PKT,
   "R0_PKT" : R0_PKT,
   "U0_PKT" : U0_PKT,
   "R0_CRC_PKT" : R0_CRC_PKT,
   "R1_PKT" : R1_PKT,
   "R1_ID_PKT" : R1_ID_PKT,
   "R1_TS_PKT" : R1_TS_PKT,
   "UO1_PKT" : UO1_PKT,
   "UO1_ID_PKT" : UO1_ID_PKT,
   "UO1_TS_PKT" : UO1_TS_PKT,
   "UOR2_PKT" : UOR2_PKT,
   "UOR2_ID_PKT" : UOR2_ID_PKT,
   "UOR2_TS_PKT" : UOR2_TS_PKT,
   "NO_COMP_NORM_PKT" : NO_COMP_NORM_PKT,
   "NO_COMP_IR_PKT" : NO_COMP_IR_PKT,
   "ROHC_F2_ACK" : ROHC_F2_ACK,
   "ROHC_F1_ACK" : ROHC_F1_ACK,
   "ROHC_NACK" : ROHC_NACK,
   "ROHC_SNACK" : ROHC_SNACK,
   "IPV6_FRAG"  :  IPV6_FRAG,        
   "IPV6_RTE"  :  IPV6_RTE,        
   "IPV6_HOP"  :  IPV6_HOP,        
   "IPV6_DST"  :  IPV6_DST,        
   "CM_COMP_ROHC_PROF0":CM_COMP_ROHC_PROF0,
   "CM_COMP_ROHC_PROF1":CM_COMP_ROHC_PROF1,
   "CM_COMP_ROHC_PROF2":CM_COMP_ROHC_PROF2,
   "CM_COMP_ROHC_PROF3":CM_COMP_ROHC_PROF3,
   "CM_COMP_ROHC_NOCOMP_PROF":CM_COMP_ROHC_NOCOMP_PROF,
   "CM_COMP_ROHC_RTP_PROF":CM_COMP_ROHC_RTP_PROF,
    "CM_COMP_ROHC_UDP_PROF":CM_COMP_ROHC_UDP_PROF,
   "CM_COMP_ROHC_ESP_PROF":CM_COMP_ROHC_ESP_PROF,
   "CM_COMP_ROHC_PROF_ALL":CM_COMP_ROHC_PROF_ALL,
   "TC_IPHC":TC_IPHC,
   "TC_ROHC":TC_ROHC,
   "TC_IPHC_ROHC":TC_IPHC_ROHC,
   "TC_HC_INVALID":TC_HC_INVALID,
   "TC_CTC_COMP_ALGO_NOT_SUPPORTED" :TC_CTC_COMP_ALGO_NOT_SUPPORTED,
   "TC_CTC_COMP_ROHC_PROF_NOT_SUPPORTED" :TC_CTC_COMP_ROHC_PROF_NOT_SUPPORTED,
   "TC_CTC_RELOC_CTXT_NOT_SUPPORTED" :TC_CTC_RELOC_CTXT_NOT_SUPPORTED,
   "TC_CTC_RES_NOT_AVAIL" :TC_CTC_RES_NOT_AVAIL,
   "TC_CTC_INVALID_PDCPID" :TC_CTC_INVALID_PDCPID,
   "TC_CTC_INVALID_RLC_MODE": TC_CTC_INVALID_RLC_MODE,
   "TC_SDU_DISCARD_MODE_NONE": TC_SDU_DISCARD_MODE_NONE,
   "TC_SDU_DISCARD_MODE_MAX_DAT" : TC_SDU_DISCARD_MODE_MAX_DAT,
   "TC_SDU_DISCARD_MODE_TIMER" :TC_SDU_DISCARD_MODE_TIMER,
   "TC_SDU_DISCARD_MODE_TIMER_AND_MAX_DAT" :TC_SDU_DISCARD_MODE_TIMER_AND_MAX_DAT,
   "TC_EVC_RESET_FAILED" : TC_EVC_RESET_FAILED,
   "LCM_REASON_NOT_APPL" :LCM_REASON_NOT_APPL,
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   "LCM_REASON_INV_RSET" :LCM_REASON_INV_RSET,
   "LXT_REASON_SESS_NOT_RELSD" :LXT_REASON_SESS_NOT_RELSD,
   "LXT_PROC_CNTRL":LXT_PROC_CNTRL,
   "LXT_PROC_ACK":LXT_PROC_ACK,
   "LXT_PROC_NACK":LXT_PROC_NACK,
   "LXT_PROC_ERR":LXT_PROC_ERR,
   "CM_BND_OK"                        : CM_BND_OK,
   "LXT_INSTCREATE"                   : LXT_INSTCREATE,
   "LXT_INSTDELETE"                   : LXT_INSTDELETE,
   "LXT_INSTUPDATE"                   : LXT_INSTUPDATE,
   "LXT_MODE_TRANSPARENT"             : LXT_MODE_TRANSPARENT,
   "LXT_MODE_SUPPORT_V1"              : LXT_MODE_SUPPORT_V1,
   "LXT_MODE_SUPPORT_V2"              : LXT_MODE_SUPPORT_V2,
   "LHR_TSAP_HIT"              : LHR_TSAP_HIT,
   "LLX_TSAP_TYPE_RTP"              : LLX_TSAP_TYPE_RTP,
   "LLX_TSAP_TYPE_GTPU"             : LLX_TSAP_TYPE_GTPU,
   "LLX_TSAP_TYPE_AAL2"             : LLX_TSAP_TYPE_AAL2,
   "LLX_TSAP_TYPE_DRTP"              : LLX_TSAP_TYPE_DRTP,
   "LLX_TSAP_TYPE_DGTPU"             : LLX_TSAP_TYPE_DGTPU,
   "LLX_TSAP_TYPE_DAAL2"             : LLX_TSAP_TYPE_DAAL2,
   "LXT_TRCH_TYPE_RTP"               : LXT_TRCH_TYPE_RTP,
   "LXT_TRCH_TYPE_GTP"               : LXT_TRCH_TYPE_GTP,
   "LXT_TRCH_TYPE_AAL"               : LXT_TRCH_TYPE_AAL,
   "LXT_INIT"              : LXT_INIT,
   "LXT_RNC"              : LXT_RNC,
   "LXT_CN"              : LXT_CN,
   "LXT_RATECNTRL"              : LXT_RATECNTRL,
   "LXT_TIMEALGN"              : LXT_TIMEALGN,
   "LXT_ERREVT"              : LXT_ERREVT,
   "LXT_ERR_CRC_FRMHDR" : LXT_ERR_CRC_FRMHDR,
   "LXT_ERR_CRC_FRMPYLD" : LXT_ERR_CRC_FRMPYLD,
   "LXT_ERR_UNEXPECTED_FRM_NUM" : LXT_ERR_UNEXPECTED_FRM_NUM,
   "LXT_ERR_FRM_LOSS" : LXT_ERR_FRM_LOSS,
   "LXT_ERR_PDU_TYPE_UNKNOWN" : LXT_ERR_PDU_TYPE_UNKNOWN,
   "LXT_ERR_UNKNOWN_PROC" : LXT_ERR_UNKNOWN_PROC,
   "LXT_ERR_UNKNOWN_RESVD_VAL": LXT_ERR_UNKNOWN_RESVD_VAL,
   "LXT_ERR_UNKNOWN_FIELD" : LXT_ERR_UNKNOWN_FIELD,
   "LXT_ERR_FRM_TOO_SHRT" : LXT_ERR_FRM_TOO_SHRT,
   "LXT_ERR_MISSIN_FIELDS" : LXT_ERR_MISSIN_FIELDS,
   "LXT_ERR_UNEXPECTED_PDU_TYPE" : LXT_ERR_UNEXPECTED_PDU_TYPE,
   "LXT_ERR_UNEXPECTED_PROC" : LXT_ERR_UNEXPECTED_PROC,
   "LXT_ERR_UNEXPECTED_RFCI" : LXT_ERR_UNEXPECTED_RFCI,
   "LXT_ERR_UNEXPECTED_VAL" : LXT_ERR_UNEXPECTED_VAL,
   "LXT_ERR_INIT_FAIL1" : LXT_ERR_INIT_FAIL1,
   "LXT_ERR_INIT_FAIL_NW_ERROR" : LXT_ERR_INIT_FAIL_NW_ERROR,
   "LXT_ERR_INIT_FAIL_TMR_EXP" : LXT_ERR_INIT_FAIL_TMR_EXP,
   "LXT_ERR_INIT_FAIL_FUNC_ERR" : LXT_ERR_INIT_FAIL_FUNC_ERR,
   "LXT_ERR_INIT_FAIL_REP_NACK" : LXT_ERR_INIT_FAIL_REP_NACK,
   "LXT_ERR_RATE_CNTRL_FAIL" : LXT_ERR_RATE_CNTRL_FAIL,
   "LXT_ERR_ERROR_EVNT_FAIL" : LXT_ERR_ERROR_EVNT_FAIL,
   "LXT_ERR_TIME_ALGN_NOT_SUPP" : LXT_ERR_TIME_ALGN_NOT_SUPP,
   "LXT_ERR_TIME_ALGN_NOT_POS" : LXT_ERR_TIME_ALGN_NOT_POS,
   "LXT_IUUP_MODE_VER_NOT_SUPP" : LXT_IUUP_MODE_VER_NOT_SUPP,
   "LXT_CAUSE_INVALID_STATE":LXT_CAUSE_INVALID_STATE,
   "LXT_ERR_DIST0" : LXT_ERR_DIST0,
   "LXT_ERR_DIST1" : LXT_ERR_DIST1,
   "LXT_ERR_DIST2" : LXT_ERR_DIST2,
   "LXAC_PDU_TYPE0" : LXAC_PDU_TYPE0,
   "LXAC_PDU_TYPE1" : LXAC_PDU_TYPE1,
   "LXAC_PDU_TYPE14" : LXAC_PDU_TYPE14,
  
   "SW_PROVIDER_NOTFOUND" : SW_PROVIDER_NOTFOUND,  
   "SW_LISTENER_NOTFOUND" : SW_LISTENER_NOTFOUND,  
   "SW_SESSION_NOTFOUND" : SW_SESSION_NOTFOUND,  
   "SW_SIPMSG_NOTFOUND" : SW_SIPMSG_NOTFOUND,  
   "SW_DLG_NOTFOUND" : SW_DLG_NOTFOUND,  
   "SW_DLGDATA_NOTFOUND" : SW_DLGDATA_NOTFOUND,  
   "SW_DLGSTATE_NOTFOUND" : SW_DLGSTATE_NOTFOUND,  
   "SW_SIPEVENT_INVALID" : SW_SIPEVENT_INVALID,  
   "SW_FORKDLG_CREATED" : SW_FORKDLG_CREATED,  
   "SW_SIPOAENGNE_NOTFOUND" : SW_SIPOAENGNE_NOTFOUND,  
   "SW_SDPSESSION_NOTFOUND" : SW_SDPSESSION_NOTFOUND,  
   "SW_PREV_SDPOA_INCOMPLETE" : SW_PREV_SDPOA_INCOMPLETE,  
   "SW_SDPOA_INCOMPLETE_UPDATE_SEND_491" : SW_SDPOA_INCOMPLETE_UPDATE_SEND_491,
   "SW_SDPOA_INCOMPLETE_UPDATE_SEND_504" : SW_SDPOA_INCOMPLETE_UPDATE_SEND_504, 
   "SW_SEND_LOCALSDP_NULL" : SW_SEND_LOCALSDP_NULL,  
   "SW_APP_SEND_SDP_REQD" : SW_APP_SEND_SDP_REQD,  
   "SW_SIPOA_REJECT_MSG" : SW_SIPOA_REJECT_MSG,  
   "SW_SDP_EINSDP" : SW_SDP_EINSDP,  
   "SW_SDP_EINVAL" : SW_SDP_EINVAL,  
   "SW_SDP_EINVER" : SW_SDP_EINVER,  
   "SW_SDP_EINORIGIN" : SW_SDP_EINORIGIN,  
   "SW_SDP_EINTIME" : SW_SDP_EINTIME,  
   "SW_SDP_EINNAME" : SW_SDP_EINNAME,  
   "SW_SDP_EINCONN" : SW_SDP_EINCONN,  
   "SW_SDP_EMISSINGCONN" : SW_SDP_EMISSINGCONN,  
   "SW_SDP_EINATTR" : SW_SDP_EINATTR,  
   "SW_SDP_EINRTPMAP" : SW_SDP_EINRTPMAP,  
   "SW_SDP_ERTPMAPTOOLONG" : SW_SDP_ERTPMAPTOOLONG,  
   "SW_SDP_EMISSINGRTPMAP" : SW_SDP_EMISSINGRTPMAP,  
   "SW_SDP_EINMEDIA" : SW_SDP_EINMEDIA,  
   "SW_SDP_ENOFMT" : SW_SDP_ENOFMT,  
   "SW_SDP_EINPT" : SW_SDP_EINPT,  
   "SW_SDP_EINFMTP" : SW_SDP_EINFMTP,  
   "SW_SDP_EINRTCP" : SW_SDP_EINRTCP,  
   "SW_SDP_EINPROTO" : SW_SDP_EINPROTO,  
   "SW_SDP_EMISSINGMEDIA" : SW_SDP_EMISSINGMEDIA,  
   "SW_SDPNEG_EINSTATE" : SW_SDPNEG_EINSTATE,  
   "SW_SDPNEG_NO_LOCAL_SDP" : SW_SDPNEG_NO_LOCAL_SDP,  
   "SW_SDPNEG_NO_REMOTE_SDP" : SW_SDPNEG_NO_REMOTE_SDP,  
   "SW_SDPNEG_ENOACTIVE" : SW_SDPNEG_ENOACTIVE,  
   "SW_SDPNEG_ENONEG" : SW_SDPNEG_ENONEG,  
   "SW_SDPNEG_EMISMEDIA" : SW_SDPNEG_EMISMEDIA,  
   "SW_SDPNEG_EINVANSMEDIA" : SW_SDPNEG_EINVANSMEDIA,  
   "SW_SDPNEG_EINVANSTP" : SW_SDPNEG_EINVANSTP,  
   "SW_SDPNEG_EANSNOMEDIA" : SW_SDPNEG_EANSNOMEDIA,  
   "SW_SDPNEG_ENOMEDIA" : SW_SDPNEG_ENOMEDIA,  
   "SW_SDPNEG_NOANSCODEC" : SW_SDPNEG_NOANSCODEC,  
   "SW_SDPNEG_NOANSTELEVENT" : SW_SDPNEG_NOANSTELEVENT,  
   "SW_SDPNEG_NOANSUNKNOWN" : SW_SDPNEG_NOANSUNKNOWN,  
   "SW_SDPNEG_EINVMOD" : SW_SDPNEG_EINVMOD,  
   "SW_SDP_NOMODIFY" : SW_SDP_NOMODIFY,  
   "SW_SDP_DUPLICATE" : SW_SDP_DUPLICATE,  
   "SW_SDPNEG_EDUPSDP" : SW_SDPNEG_EDUPSDP,  
   "SW_SDP_EMEDIANOTEQUAL" : SW_SDP_EMEDIANOTEQUAL,  
   "SW_SDP_EPORTNOTEQUAL" : SW_SDP_EPORTNOTEQUAL,  
   "SW_SDP_ETPORTNOTEQUAL" : SW_SDP_ETPORTNOTEQUAL,  
   "SW_SDP_EFORMATNOTEQUAL" : SW_SDP_EFORMATNOTEQUAL,  
   "SW_SDP_ECONNNOTEQUAL" : SW_SDP_ECONNNOTEQUAL,  
   "SW_SDP_EATTRNOTEQUAL" : SW_SDP_EATTRNOTEQUAL,  
   "SW_SDP_EDIRNOTEQUAL" : SW_SDP_EDIRNOTEQUAL,  
   "SW_SDP_EFMTPNOTEQUAL" : SW_SDP_EFMTPNOTEQUAL,  
   "SW_SDP_ERTPMAPNOTEQUAL" : SW_SDP_ERTPMAPNOTEQUAL,  
   "SW_SDP_ESESSNOTEQUAL" : SW_SDP_ESESSNOTEQUAL,  
   "SW_SDP_EORIGINNOTEQUAL" : SW_SDP_EORIGINNOTEQUAL,  
   "SW_SDP_ENAMENOTEQUAL" : SW_SDP_ENAMENOTEQUAL,  
   "SW_SDP_ETIMENOTEQUAL" : SW_SDP_ETIMENOTEQUAL,  
   "SW_CODEC_EUNSUP" : SW_CODEC_EUNSUP,  
   "SW_CODEC_EFAILED" : SW_CODEC_EFAILED,  
   "SW_CODEC_EFRMTOOSHORT" : SW_CODEC_EFRMTOOSHORT,  
   "SW_CODEC_EPCMTOOSHORT" : SW_CODEC_EPCMTOOSHORT,  
   "SW_CODEC_EFRMINLEN" : SW_CODEC_EFRMINLEN,  
   "SW_CODEC_EPCMFRMINLEN" : SW_CODEC_EPCMFRMINLEN,  
   "SW_CODEC_EINMODE" : SW_CODEC_EINMODE,  
   "SW_EINVALIDIP" : SW_EINVALIDIP,  
   "SW_EASYMCODEC" : SW_EASYMCODEC,  
   "SW_EINVALIDPT" : SW_EINVALIDPT,  
   "SW_EMISSINGRTPMAP" : SW_EMISSINGRTPMAP,  
   "SW_EINVALIMEDIATYPE" : SW_EINVALIMEDIATYPE,  
   "SW_EREMOTENODTMF" : SW_EREMOTENODTMF,  
   "SW_RTP_EINDTMF" : SW_RTP_EINDTMF,  
   "SW_RTP_EREMNORFC2833" : SW_RTP_EREMNORFC2833,  
   "SW_SDP_NOPORT" : SW_SDP_NOPORT,  
   "SW_SDK_ERR_MAX" : SW_SDK_ERR_MAX,  


#cm_xta_py_py_001.main_37: Updated for S1AP 3.1 release
   "ENTSZ"     : ENTSZ,
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   "ENTUZ"     : ENTUZ,
   "SZ_ASSOC_DOWN" : SZ_ASSOC_DOWN,
   "SZAC_LSZ_ENB_PRC0" :  SZAC_LSZ_ENB_PRC0,
   "SZAC_LSZ_MME_PRC1" :  SZAC_LSZ_MME_PRC1,
   "SZAC_LSZ_GW_PRC2" :  SZAC_LSZ_GW_PRC2,
   "SZAC_LSZ_INV_NODE" :  SZAC_LSZ_INV_NODE,
   "SZAC_NODE_MME" :  SZAC_NODE_MME,
   "SZAC_NODE_ENB" :  SZAC_NODE_ENB,
   "SZAC_NODE_GW" :  SZAC_NODE_GW,
   "SZAC_SCTP_DM" :  SZAC_SCTP_DM,
   "SZAC_LSZ_INV_NUM_PEERS" :  SZAC_LSZ_INV_NUM_PEERS,

   "LSZ_USTA_DGNVAL_NONE"  : LSZ_USTA_DGNVAL_NONE,  
   "LSZ_USTA_DGNVAL_MEM"   : LSZ_USTA_DGNVAL_MEM,   
   "LSZ_USTA_DGNVAL_SAPID"  : LSZ_USTA_DGNVAL_SAPID, 
   "LSZ_USTA_DGNVAL_DATA"  : LSZ_USTA_DGNVAL_DATA,  
   "LSZ_USTA_DGNVAL_PEER"  : LSZ_USTA_DGNVAL_PEER,  
   "LSZ_USTA_DGNVAL_CONID"  : LSZ_USTA_DGNVAL_CONID, 

   "LSZ_REASON_PROTCFG_NOT_DONE" : LSZ_REASON_PROTCFG_NOT_DONE,  
   "LSZ_REASON_HASHINIT_FAIL" : LSZ_REASON_HASHINIT_FAIL,     
   "LSZ_REASON_SAP_ASSOC_EXISTS" : LSZ_REASON_SAP_ASSOC_EXISTS,  
   "LSZ_REASON_LSAPCFG_NOT_DONE" : LSZ_REASON_LSAPCFG_NOT_DONE,  
   "LSZ_REASON_DUP_AUDIT_REQ" : LSZ_REASON_DUP_AUDIT_REQ,     

   "LSZ_EVENT_LI_BND_CFM"  : LSZ_EVENT_LI_BND_CFM,       
   "LSZ_EVENT_LI_ENDP_OPEN_CFM"  : LSZ_EVENT_LI_ENDP_OPEN_CFM, 
   "LSZ_EVENT_LI_ENDP_CLOSE_CFM"  : LSZ_EVENT_LI_ENDP_CLOSE_CFM,
   "LSZ_EVENT_LI_ASSOC_IND"  : LSZ_EVENT_LI_ASSOC_IND,     
   "LSZ_EVENT_LI_ASSOC_CFM"  : LSZ_EVENT_LI_ASSOC_CFM,     
   "LSZ_EVENT_LI_TERM_IND"  : LSZ_EVENT_LI_TERM_IND,      
   "LSZ_EVENT_LI_TERM_CFM"  : LSZ_EVENT_LI_TERM_CFM,      
   "LSZ_EVENT_LI_FLC_IND"  : LSZ_EVENT_LI_FLC_IND,       
   "LSZ_EVENT_LI_DAT_IND"  : LSZ_EVENT_LI_DAT_IND,  
   "LSZ_EVENT_LI_STA_IND"  : LSZ_EVENT_LI_STA_IND,  
   "LSZ_EVENT_LI_SEND_FAIL"  : LSZ_EVENT_LI_SEND_FAIL,  
   "LSZ_EVENT_DMEM_ALLOC_PASS"  : LSZ_EVENT_DMEM_ALLOC_PASS,  
   #Iuh 2.1 release
   "RUT_CAUSE_INV_CTXT_DMN_ID"  : RUT_CAUSE_INV_CTXT_DMN_ID,
   "RUT_CAUSE_INV_DMN_ID"       : RUT_CAUSE_INV_DMN_ID,
   "RUT_CAUSE_INV_PDU"          : RUT_CAUSE_INV_PDU,
   "RUT_CAUSE_PC_ABS_SYNTAX_ERR" : RUT_CAUSE_PC_ABS_SYNTAX_ERR,
   "LSZ_CAUSE_CONGESTION_RECV"  : LSZ_CAUSE_CONGESTION_RECV, 
   "LSZ_CAUSE_ASSOC_UP"  : LSZ_CAUSE_ASSOC_UP,        
   "LSZ_CAUSE_ASSOC_DOWN"  : LSZ_CAUSE_ASSOC_DOWN,      
   "LSZ_CAUSE_PEER_DELETED"  : LSZ_CAUSE_PEER_DELETED,    
   "LSZ_CAUSE_ENDP_OPEN"  : LSZ_CAUSE_ENDP_OPEN,       
   "LSZ_CAUSE_EXCEED_CONF_VAL"  : LSZ_CAUSE_EXCEED_CONF_VAL, 
   "LSZ_CAUSE_OUTRES"  : LSZ_CAUSE_OUTRES,          
   "LSZ_CAUSE_SCT_ENPOPEN_SUCC"  : LSZ_CAUSE_SCT_ENPOPEN_SUCC,
   "LSZ_CAUSE_INV_PAR_VAL"  : LSZ_CAUSE_INV_PAR_VAL,     
   "LSZ_CAUSE_EPCLOSE_OK"  : LSZ_CAUSE_EPCLOSE_OK,      

   "SCT_CAUSE_INV_PAR_VAL"    :   SCT_CAUSE_INV_PAR_VAL         ,
   "SCT_CAUSE_ENDP_OPEN"      :   SCT_CAUSE_ENDP_OPEN           ,
   "SCT_CAUSE_EXCEED_CONF_VAL":   SCT_CAUSE_EXCEED_CONF_VAL     ,
   "SCT_CAUSE_OUTRES"         :   SCT_CAUSE_OUTRES              ,

   "LCM_REASON_EXCEED_CONF_VAL"  :  LCM_REASON_EXCEED_CONF_VAL,
   "LCM_CATEGORY_PROTOCOL"  : LCM_CATEGORY_PROTOCOL   ,
   "LCM_CATEGORY_INTERFACE"  : LCM_CATEGORY_INTERFACE  ,
   # Iuh 2.1 release 
   "LHM_TYPE_HNB" : LHM_TYPE_HNB,
   "LHM_TYPE_HNBGW" : LHM_TYPE_HNBGW,
   "LCM_CATEGORY_INTERNAL"  : LCM_CATEGORY_INTERNAL   ,
   "LCM_CATEGORY_RESOURCE"  : LCM_CATEGORY_RESOURCE   ,
   "LCM_CATEGORY_PSF_FTHA"  : LCM_CATEGORY_PSF_FTHA   ,
   "LCM_CATEGORY_PERF_MONIT"  : LCM_CATEGORY_PERF_MONIT ,

   "LSZ_SAP_CFG"      :   LSZ_SAP_CFG     ,
   "LSZ_SAP_ISBOUND"  :   LSZ_SAP_ISBOUND ,
   "LSZ_SAP_BINDING"  :   LSZ_SAP_BINDING ,
   "LSZ_SAP_UBND"     :   LSZ_SAP_UBND    ,
   "STSZGEN"          :   STSZGEN    ,
   "STSZPROT"         :   STSZPROT   ,
   "STSZSZTSAP"       :   STSZSZTSAP ,
   "STSZSCTSAP"       :   STSZSCTSAP ,
   "STSZPEER"         :   STSZPEER   ,
   "STSZSID"          :   STSZSID    ,
   "SZT_ND_ST_IDLE"          :  SZT_ND_ST_IDLE          ,
   "SZT_ND_ST_SETUP_IN_PRG"  :  SZT_ND_ST_SETUP_IN_PRG  ,
   "SZT_ND_ST_NORMAL"        :  SZT_ND_ST_NORMAL        ,
   "SZT_ND_ST_RESET"         :  SZT_ND_ST_RESET         ,
   "SZT_CON_ST_IDLE"         :  SZT_CON_ST_IDLE         ,
   "SZT_CON_ST_CONNECTING"   :  SZT_CON_ST_CONNECTING   ,
   "SZT_CON_ST_ESTBLD"       :  SZT_CON_ST_ESTBLD       ,
   "SZT_CON_ST_RELEASING"    :  SZT_CON_ST_RELEASING    ,
   "SZT_CON_ST_NON_EXST"     :  SZT_CON_ST_NON_EXST     ,
   "SZT_AUD_CONN"            :  SZT_AUD_CONN            ,
   "SZT_AUD_PEER"            :  SZT_AUD_PEER            ,
   "SZT_AUD_FLC"             :  SZT_AUD_FLC             ,
   "SZT_FLC_START"           :  SZT_FLC_START           ,
   "SZT_FLC_DROP"            :  SZT_FLC_DROP            ,
   "SZT_FLC_STOP"            :  SZT_FLC_STOP            ,
   "SZT_FLC_ACTIVE"          :  SZT_FLC_ACTIVE          ,
   "SZT_FLC_INACTIVE"        :  SZT_FLC_INACTIVE        ,
   "SCT_FLC_START"           :  SCT_FLC_START           ,
   "SCT_FLC_DROP"            :  SCT_FLC_DROP            ,
   "SCT_FLC_STOP"            :  SCT_FLC_STOP            ,
   "SCT_FLC_ACTIVE"          :  SCT_FLC_ACTIVE          ,
   "SCT_FLC_INACTIVE"        :  SCT_FLC_INACTIVE        ,

   "SZAC_PRC0" : SZAC_PRC0,
   "SZAC_PRC1" : SZAC_PRC1,
   "SZAC_PRC2" : SZAC_PRC2,
   "SZAC_PRC3" : SZAC_PRC3,
   "SZAC_ENB_PROC" :SZAC_ENB_PROC, 
   "SZAC_XTA_PROC" :SZAC_XTA_PROC, 
   "SZAC_MME_PROC" :SZAC_MME_PROC, 
#cm_xta_py_py_001.main_48: Updated for PSF-S1AP 1.1 release
   "SZAC_SBY_PROC" : SZAC_SBY_PROC,
   "SZAC_ENB_PROC1" : SZAC_ENB_PROC1,
   "SZAC_MME_PROC1" : SZAC_MME_PROC1,
   "YT_YTT_MODE_MANUAL":YT_YTT_MODE_MANUAL,
   "YT_YTT_MODE_AUTO":YT_YTT_MODE_AUTO,
   "YT_YTT_MODE_CHECK":YT_YTT_MODE_CHECK,
   "SCTIF":SCTIF,
   "SZTIF":SZTIF,
   "YTPIF":YTPIF,
   "SZTIFVER":SZTIFVER,
   "SCTIFVER":SCTIFVER,
   "YTPIFVER":YTPIFVER,
   "SHT_REQTYPE_BND_ENA":SHT_REQTYPE_BND_ENA,
   "SHT_REQTYPE_UBND_DIS":SHT_REQTYPE_UBND_DIS,
   "SHT_REQTYPE_GETVER":SHT_REQTYPE_GETVER,
   "SHT_REQTYPE_SETVER":SHT_REQTYPE_SETVER,

   "LCM_CATEGORY_INTERFACE" : LCM_CATEGORY_INTERFACE,
   # Iuh 2.1 release
   "LHM_TYPE_HNB" : LHM_TYPE_HNB,
   "LHM_TYPE_HNBGW" : LHM_TYPE_HNBGW,
   "LSZ_EVENT_LI_ENDP_OPEN_CFM" : LSZ_EVENT_LI_ENDP_OPEN_CFM,
   "LSZ_CAUSE_SCT_ENPOPEN_SUCC" : LSZ_CAUSE_SCT_ENPOPEN_SUCC,
   "LSZ_USTA_DGNVAL_SAPID" : LSZ_USTA_DGNVAL_SAPID,

   "SZT_MSG_ID_SAE_BRR_SETUP_REQ" : SZT_MSG_ID_SAE_BRR_SETUP_REQ,
   "SZT_MSG_ID_SAE_BRR_SETUP_RSP" : SZT_MSG_ID_SAE_BRR_SETUP_RSP,
   "SZT_MSG_ID_SAE_BRR_MOD_REQ" : SZT_MSG_ID_SAE_BRR_MOD_REQ,
   "SZT_MSG_ID_SAE_BRR_MOD_RSP" : SZT_MSG_ID_SAE_BRR_MOD_RSP,
   "SZT_MSG_ID_SAE_BRR_REL_CMD" : SZT_MSG_ID_SAE_BRR_REL_CMD,
   "SZT_MSG_ID_SAE_BRR_REL_CMPLT" : SZT_MSG_ID_SAE_BRR_REL_CMPLT,
   "SZT_MSG_ID_SAE_BRR_REL_REQ" : SZT_MSG_ID_SAE_BRR_REL_REQ,
   "SZT_MSG_ID_ERAB_SETUP_REQ" : SZT_MSG_ID_ERAB_SETUP_REQ,
   "SZT_MSG_ID_ERAB_SETUP_RSP" : SZT_MSG_ID_ERAB_SETUP_RSP,
   "SZT_MSG_ID_ERAB_MOD_REQ" : SZT_MSG_ID_ERAB_MOD_REQ,
   "SZT_MSG_ID_ERAB_MOD_RSP" : SZT_MSG_ID_ERAB_MOD_RSP,
   "SZT_MSG_ID_ERAB_REL_CMD" : SZT_MSG_ID_ERAB_REL_CMD,
   "SZT_MSG_ID_ERAB_REL_CMPLT" : SZT_MSG_ID_ERAB_REL_CMPLT,
   "SZT_MSG_ID_ERAB_REL_REQ" : SZT_MSG_ID_ERAB_REL_REQ,
   "SZT_MSG_ID_CXT_SETUP_REQ" : SZT_MSG_ID_CXT_SETUP_REQ,
   "SZT_MSG_ID_CXT_SETUP_RSP" : SZT_MSG_ID_CXT_SETUP_RSP,
   "SZT_MSG_ID_INIT_CXT_SETUP_FAIL" : SZT_MSG_ID_INIT_CXT_SETUP_FAIL,
   "SZT_MSG_ID_UE_CXT_REL_REQ" : SZT_MSG_ID_UE_CXT_REL_REQ,
   "SZT_MSG_ID_UE_CXT_REL_CMD" : SZT_MSG_ID_UE_CXT_REL_CMD,
   "SZT_MSG_ID_UE_CXT_REL_CMPL" : SZT_MSG_ID_UE_CXT_REL_CMPL,
   "SZT_MSG_ID_UE_CXT_MOD_REQ" : SZT_MSG_ID_UE_CXT_MOD_REQ,
   "SZT_MSG_ID_UE_CXT_MOD_RSP" : SZT_MSG_ID_UE_CXT_MOD_RSP,
   "SZT_MSG_ID_UE_CXT_MOD_FAIL" : SZT_MSG_ID_UE_CXT_MOD_FAIL,
   "SZT_MSG_ID_INIT_UE_MSG" : SZT_MSG_ID_INIT_UE_MSG,
   "SZT_MSG_ID_DL_NAS_TPT" : SZT_MSG_ID_DL_NAS_TPT,
   "SZT_MSG_ID_UL_NAS_TPT" : SZT_MSG_ID_UL_NAS_TPT,
   "SZT_MSG_ID_NAS_NON_DEL_IND" : SZT_MSG_ID_NAS_NON_DEL_IND,
   "SZT_MSG_ID_ERR_IND" : SZT_MSG_ID_ERR_IND,
   "SZT_MSG_ID_NO_DATA" : SZT_MSG_ID_NO_DATA,
   "SZT_MSG_ID_RESET" : SZT_MSG_ID_RESET,
   "SZT_MSG_ID_SETUP_REQ" : SZT_MSG_ID_SETUP_REQ,
   "SZT_MSG_ID_SETUP_RSP" : SZT_MSG_ID_SETUP_RSP,
   "SZT_MSG_ID_RESET_ACK" : SZT_MSG_ID_RESET_ACK,
   "SZT_MSG_ID_SETUP_FAIL" : SZT_MSG_ID_SETUP_FAIL,
   "SZT_MSG_ID_PAGING" : SZT_MSG_ID_PAGING,
   "SZT_MSG_ID_HO_REQD" : SZT_MSG_ID_HO_REQD,
   "SZT_MSG_ID_HO_CMD" : SZT_MSG_ID_HO_CMD,
   "SZT_MSG_ID_HO_PREP_FAIL" : SZT_MSG_ID_HO_PREP_FAIL,
   "SZT_MSG_ID_HO_REQ" : SZT_MSG_ID_HO_REQ,
   "SZT_MSG_ID_HO_REQ_ACK" : SZT_MSG_ID_HO_REQ_ACK,
   "SZT_MSG_ID_HO_FAIL" : SZT_MSG_ID_HO_FAIL,
   "SZT_MSG_ID_HO_NTFY" : SZT_MSG_ID_HO_NTFY,
   "SZT_MSG_ID_PATH_SWTCH_REQ" : SZT_MSG_ID_PATH_SWTCH_REQ,
   "SZT_MSG_ID_PATH_SWTCH_REQ_ACK" : SZT_MSG_ID_PATH_SWTCH_REQ_ACK,
   "SZT_MSG_ID_PATH_SWTCH_REQ_FAIL" : SZT_MSG_ID_PATH_SWTCH_REQ_FAIL,
   "SZT_MSG_ID_HO_CANCEL" : SZT_MSG_ID_HO_CANCEL,
   "SZT_MSG_ID_HO_CANCEL_ACK" : SZT_MSG_ID_HO_CANCEL_ACK,
   "SZT_MSG_ID_ENB_STA_TRFR" : SZT_MSG_ID_ENB_STA_TRFR,
   "SZT_MSG_ID_MME_STA_TRFR" : SZT_MSG_ID_MME_STA_TRFR,
   "SZT_MSG_ID_DEACTV_TRACE" : SZT_MSG_ID_DEACTV_TRACE,
   "SZT_MSG_ID_TRACE_START" : SZT_MSG_ID_TRACE_START,
   "SZT_MSG_ID_TRACE_FAIL_IND" : SZT_MSG_ID_TRACE_FAIL_IND,
   "SZT_MSG_ID_LOC_REPORT_CNTRL" : SZT_MSG_ID_LOC_REPORT_CNTRL,
   "SZT_MSG_ID_LOC_REPORT_FAIL_IND" : SZT_MSG_ID_LOC_REPORT_FAIL_IND,
   "SZT_MSG_ID_LOC_REPORT" : SZT_MSG_ID_LOC_REPORT,
   "SZT_MSG_ID_ENB_CFG_UPD" : SZT_MSG_ID_ENB_CFG_UPD,
   "SZT_MSG_ID_ENB_CFG_UPD_ACK" : SZT_MSG_ID_ENB_CFG_UPD_ACK,
   "SZT_MSG_ID_ENB_CFG_UPD_FAIL" : SZT_MSG_ID_ENB_CFG_UPD_FAIL,
   "SZT_MSG_ID_MME_CFG_UPD" : SZT_MSG_ID_MME_CFG_UPD,
   "SZT_MSG_ID_MME_CFG_UPD_ACK" : SZT_MSG_ID_MME_CFG_UPD_ACK,
   "SZT_MSG_ID_MME_CFG_UPD_FAIL" : SZT_MSG_ID_MME_CFG_UPD_FAIL,
   "SZT_MSG_ID_UPLNK_CDMA_TUNNL" : SZT_MSG_ID_UPLNK_CDMA_TUNNL,
   "SZT_MSG_ID_DNLNK_CDMA_TUNNL" : SZT_MSG_ID_DNLNK_CDMA_TUNNL,
   "SZT_MSG_ID_UE_CAP_INFO" : SZT_MSG_ID_UE_CAP_INFO,
   "SZT_MSG_ID_OVLD_START" : SZT_MSG_ID_OVLD_START,
   "SZT_MSG_ID_OVLD_STOP" : SZT_MSG_ID_OVLD_STOP,
   "SZT_MSG_ID_WARNING_REQ" : SZT_MSG_ID_WARNING_REQ,
   "SZT_MSG_ID_WARNING_RSP" : SZT_MSG_ID_WARNING_RSP,
   "SZT_MSG_ID_ENB_DIR_TRANS" : SZT_MSG_ID_ENB_DIR_TRANS,
   "SZT_MSG_ID_MME_DIR_TRANS" : SZT_MSG_ID_MME_DIR_TRANS,
   "SZT_MSG_ID_PRIVATE_MSG"   : SZT_MSG_ID_PRIVATE_MSG,
   "SZT_MSG_ID_ENB_CONFIG_TRANS" : SZT_MSG_ID_ENB_CONFIG_TRANS,
   "SZT_MSG_ID_MME_CONFIG_TRANS" : SZT_MSG_ID_MME_CONFIG_TRANS,
   "SZT_MSG_ID_CELL_TRAFFIC_TRACE" :  SZT_MSG_ID_CELL_TRAFFIC_TRACE,
#cm_xta_py_py_001.main_37: Updated for S1AP 3.1 release
   "SZT_MSG_ID_KILL_REQ" :  SZT_MSG_ID_KILL_REQ,
   "SZT_MSG_ID_KILL_RSP" :  SZT_MSG_ID_KILL_RSP,                
   "SZT_MSG_ID_DNLNK_UE_ASSOC_LPPA_TPRT" :  SZT_MSG_ID_DNLNK_UE_ASSOC_LPPA_TPRT,     
   "SZT_MSG_ID_UPLNK_UE_ASSOC_LPPA_TPRT" :  SZT_MSG_ID_UPLNK_UE_ASSOC_LPPA_TPRT,     
   "SZT_MSG_ID_DNLNK_NON_UE_ASSOC_LPPA_TPRT" :  SZT_MSG_ID_DNLNK_NON_UE_ASSOC_LPPA_TPRT, 
   "SZT_MSG_ID_UPLNK_NON_UE_ASSOC_LPPA_TPRT" :  SZT_MSG_ID_UPLNK_NON_UE_ASSOC_LPPA_TPRT, 

   "SZT_MSG_ID_NO_MSG" : SZT_MSG_ID_NO_MSG,

   "SZT_STA_TYPE_FLC"   : SZT_STA_TYPE_FLC,  
   "SZT_STA_TYPE_ASSOC" : SZT_STA_TYPE_ASSOC, 

   "SZT_STATUS_ASSOC_DOWN" : SZT_STATUS_ASSOC_DOWN,  
   "SZT_STATUS_ASSOC_UP"   : SZT_STATUS_ASSOC_UP, 
   "SZT_STATUS_FLOW"       : SZT_STATUS_FLOW,

   "SZT_REASON_RCVD_TERMIND" : SZT_REASON_RCVD_TERMIND,
   "SZT_REASON_RCVD_COMM_UP" : SZT_REASON_RCVD_COMM_UP,
   "SZT_REASON_UBND_SAP"     : SZT_REASON_UBND_SAP,
   "SZT_REASON_FLC_START"    : SZT_REASON_FLC_START,
   "SZT_REASON_FLC_STOP"    : SZT_REASON_FLC_STOP,

   "SZT_CAUSE_UNEXP_MSG"     :   SZT_CAUSE_UNEXP_MSG,
   "SZT_CAUSE_NODE_RESET"    :   SZT_CAUSE_NODE_RESET,
   "SZT_CAUSE_MEM_ALLOC_FAIL":   SZT_CAUSE_MEM_ALLOC_FAIL,
   "SZT_CAUSE_INV_CONID"     :   SZT_CAUSE_INV_CONID,
   "SZT_CAUSE_INV_TYPE"      :   SZT_CAUSE_INV_TYPE,
   "SZT_CAUSE_NOT_APPL"      :   SZT_CAUSE_NOT_APPL, 
   "SZT_CAUSE_PC_TX_SYNTAX_ERR" : SZT_CAUSE_PC_TX_SYNTAX_ERR,
   "SZT_CAUSE_PC_ABS_SYNTAX_ERR" : SZT_CAUSE_PC_ABS_SYNTAX_ERR,
   "SZT_CAUSE_MSG_NOT_DELIVERED" : SZT_CAUSE_MSG_NOT_DELIVERED,
   "SZT_CAUSE_LOWER_LAYER_SND_FAILED" : SZT_CAUSE_LOWER_LAYER_SND_FAILED,
   "SZT_CAUSE_INV_STATE"        :  SZT_CAUSE_INV_STATE,
   "SZT_CAUSE_INV_PEERID"       : SZT_CAUSE_INV_PEERID,
   "SZT_CAUSE_RX_ERRONEOUS_RSP"       : SZT_CAUSE_RX_ERRONEOUS_RSP,
   "SZT_CAUSE_RADIONW"  :  SZT_CAUSE_RADIONW,
   "SZT_CAUSE_TRANSPORT"  :  SZT_CAUSE_TRANSPORT,
   "SZT_CAUSE_NAS"  :  SZT_CAUSE_NAS,
   "SZT_CAUSE_PROTOCOL"  :  SZT_CAUSE_PROTOCOL,
   "SZT_CAUSE_MISC"  :  SZT_CAUSE_MISC,
# For Dynamic Peer Allocation Feature -- DPA
   "SZT_STA_TYPE_PEER" : SZT_STA_TYPE_PEER,
   "SZT_REASON_NOT_APPL" : SZT_REASON_NOT_APPL,
   "SZT_STATUS_DYNAM_PEERCFG_OK" : SZT_STATUS_DYNAM_PEERCFG_OK,
   "SZT_STATUS_DYNAM_PEERCFG_NOK" : SZT_STATUS_DYNAM_PEERCFG_NOK,
   "SZT_PRIM_OK" : SZT_PRIM_OK,
   "SZT_PRIM_NOK" : SZT_PRIM_NOK,
   "SZT_CAUSE_NOT_APPL" : SZT_CAUSE_NOT_APPL,
   "LSZ_EVENT_UI_PEERASSOC_RSP" : LSZ_EVENT_UI_PEERASSOC_RSP,
   "LSZ_CAUSE_DYNAM_PEERCFG_OK": LSZ_CAUSE_DYNAM_PEERCFG_OK,
   "LSZ_CAUSE_DYNAM_PEERCFG_NOK" : LSZ_CAUSE_DYNAM_PEERCFG_NOK,
   "SZT_LOCAL_REL" : SZT_LOCAL_REL,
   "SZT_CXT_REL " : SZT_CXT_REL,
   "SZT_CONN_TYPE_SU" : SZT_CONN_TYPE_SU,
   "SZT_CONN_TYPE_SP" : SZT_CONN_TYPE_SP,
#LTE X2AP
   "ENTCZ"     : ENTCZ,
   "CZ_ASSOC_DOWN" : CZ_ASSOC_DOWN,
   "CZAC_LCZ_ENB1_PRC" :  CZAC_LCZ_ENB1_PRC,
   "CZAC_LCZ_ENB2_PRC" :  CZAC_LCZ_ENB2_PRC,
   "CZAC_LCZ_ENB3_PRC" :  CZAC_LCZ_ENB3_PRC,
   "CZAC_LCZ_ENB4_PRC" :  CZAC_LCZ_ENB4_PRC,
   "CZAC_LCZ_INV_NODE" :  CZAC_LCZ_INV_NODE,
   "CZAC_NODE_MME" :  CZAC_NODE_MME,
   "CZAC_NODE_ENB" :  CZAC_NODE_ENB,
   "CZAC_SCTP_DM" :  CZAC_SCTP_DM,
   "CZAC_LCZ_INV_NUM_PEERS" :  CZAC_LCZ_INV_NUM_PEERS,

   "LCZ_USTA_DGNVAL_NONE"  : LCZ_USTA_DGNVAL_NONE,  
   "LCZ_USTA_DGNVAL_MEM"   : LCZ_USTA_DGNVAL_MEM,   
   "LCZ_USTA_DGNVAL_SAPID"  : LCZ_USTA_DGNVAL_SAPID, 
   "LCZ_USTA_DGNVAL_DATA"  : LCZ_USTA_DGNVAL_DATA,  
   "LCZ_USTA_DGNVAL_PEER"  : LCZ_USTA_DGNVAL_PEER,  
   "LCZ_USTA_DGNVAL_UE"  : LCZ_USTA_DGNVAL_UE,  
   "LCZ_USTA_DGNVAL_CONID"  : LCZ_USTA_DGNVAL_CONID, 

   "LCZ_REASON_PROTCFG_NOT_DONE" : LCZ_REASON_PROTCFG_NOT_DONE,  
   "LCZ_REASON_HASHINIT_FAIL" : LCZ_REASON_HASHINIT_FAIL,     
   "LCZ_REASON_SAP_ASSOC_EXISTS" : LCZ_REASON_SAP_ASSOC_EXISTS,  
   "LCZ_REASON_LSAPCFG_NOT_DONE" : LCZ_REASON_LSAPCFG_NOT_DONE,  
   "LCZ_REASON_DUP_AUDIT_REQ" : LCZ_REASON_DUP_AUDIT_REQ,     

   "LCZ_EVENT_LI_BND_CFM"  : LCZ_EVENT_LI_BND_CFM,       
   "LCZ_EVENT_LI_ENDP_OPEN_CFM"  : LCZ_EVENT_LI_ENDP_OPEN_CFM, 
   "LCZ_EVENT_LI_ENDP_CLOSE_CFM"  : LCZ_EVENT_LI_ENDP_CLOSE_CFM,
   "LCZ_EVENT_LI_ASSOC_IND"  : LCZ_EVENT_LI_ASSOC_IND,     
   "LCZ_EVENT_LI_ASSOC_CFM"  : LCZ_EVENT_LI_ASSOC_CFM,     
   "LCZ_EVENT_LI_TERM_IND"  : LCZ_EVENT_LI_TERM_IND,      
   "LCZ_EVENT_LI_TERM_CFM"  : LCZ_EVENT_LI_TERM_CFM,      
   "LCZ_EVENT_LI_FLC_IND"  : LCZ_EVENT_LI_FLC_IND,       
   "LCZ_EVENT_LI_DAT_IND"  : LCZ_EVENT_LI_DAT_IND,  
   "LCZ_EVENT_LI_STA_IND"  : LCZ_EVENT_LI_STA_IND,  
   "LCZ_EVENT_LI_COMM_UP"  : LCZ_EVENT_LI_COMM_UP,  
   "LCZ_EVENT_LI_NET_DOWN"  : LCZ_EVENT_LI_NET_DOWN,  
   "LCZ_EVENT_UI_MSG_PEER"  : LCZ_EVENT_UI_MSG_PEER,  
   "LCZ_EVENT_UI_INV_EVT"  : LCZ_EVENT_UI_INV_EVT,  
   "LCZ_EVENT_UI_PEERASSOC_RSP"  : LCZ_EVENT_UI_PEERASSOC_RSP,  
   "LCZ_EVENT_DMEM_ALLOC_PASS"  : LCZ_EVENT_DMEM_ALLOC_PASS,  

   "LCZ_CAUSE_CONGESTION_RECV"  : LCZ_CAUSE_CONGESTION_RECV, 
   "LCZ_CAUSE_ASSOC_UP"  : LCZ_CAUSE_ASSOC_UP,        
   "LCZ_CAUSE_ASSOC_DOWN"  : LCZ_CAUSE_ASSOC_DOWN,      
   "LCZ_CAUSE_PEER_DELETED"  : LCZ_CAUSE_PEER_DELETED,    
   "LCZ_CAUSE_ENDP_OPEN"  : LCZ_CAUSE_ENDP_OPEN,       
   "LCZ_CAUSE_EXCEED_CONF_VAL"  : LCZ_CAUSE_EXCEED_CONF_VAL, 
   "LCZ_CAUSE_OUTRES"  : LCZ_CAUSE_OUTRES,          
   "LCZ_CAUSE_SCT_ENPOPEN_SUCC"  : LCZ_CAUSE_SCT_ENPOPEN_SUCC,
   "LCZ_CAUSE_INV_PAR_VAL"  : LCZ_CAUSE_INV_PAR_VAL,     
   "LCZ_CAUSE_EPCLOSE_OK"  : LCZ_CAUSE_EPCLOSE_OK,      
   "LCZ_CAUSE_NOT_BIND"  : LCZ_CAUSE_NOT_BIND,      
   "LCZ_CAUSE_INVALID_SAP"  : LCZ_CAUSE_INVALID_SAP,      
   "LCZ_CAUSE_INV_SPID"  : LCZ_CAUSE_INV_SPID,      
   "LCZ_CAUSE_SCT_SEND_FAIL"  : LCZ_CAUSE_SCT_SEND_FAIL,      
   "LCZ_CAUSE_SCT_NOT_APPL"  : LCZ_CAUSE_SCT_NOT_APPL,      

   "SCT_CAUSE_INV_PAR_VAL"    :   SCT_CAUSE_INV_PAR_VAL         ,
   "SCT_CAUSE_ENDP_OPEN"      :   SCT_CAUSE_ENDP_OPEN           ,
   "SCT_CAUSE_EXCEED_CONF_VAL":   SCT_CAUSE_EXCEED_CONF_VAL     ,
   "SCT_CAUSE_OUTRES"         :   SCT_CAUSE_OUTRES              ,

   "LCM_REASON_EXCEED_CONF_VAL"  :  LCM_REASON_EXCEED_CONF_VAL,
   "LCM_CATEGORY_PROTOCOL"  : LCM_CATEGORY_PROTOCOL   ,
   "LCM_CATEGORY_INTERFACE"  : LCM_CATEGORY_INTERFACE  ,
   "LCM_CATEGORY_INTERNAL"  : LCM_CATEGORY_INTERNAL   ,
   "LCM_CATEGORY_RESOURCE"  : LCM_CATEGORY_RESOURCE   ,
   "LCM_CATEGORY_PSF_FTHA"  : LCM_CATEGORY_PSF_FTHA   ,
   "LCM_CATEGORY_PERF_MONIT"  : LCM_CATEGORY_PERF_MONIT ,

   "LCZ_SAP_CFG"      :   LCZ_SAP_CFG     ,
   "LCZ_SAP_ISBOUND"  :   LCZ_SAP_ISBOUND ,
   "LCZ_SAP_BINDING"  :   LCZ_SAP_BINDING ,
   "LCZ_SAP_UBND"     :   LCZ_SAP_UBND    ,
   "STCZGEN"          :   STCZGEN    ,
   "STCZPROT"         :   STCZPROT   ,
   "STCZCZTSAP"       :   STCZCZTSAP ,
   "STCZSCTSAP"       :   STCZSCTSAP ,
   "STCZPEER"         :   STCZPEER   ,
   "STCZSID"          :   STCZSID    ,
   "CM_IPV4ADDR_TYPE"          :   CM_IPV4ADDR_TYPE    ,
   "CZT_ND_ST_IDLE"          :  CZT_ND_ST_IDLE          ,
   "CZT_ND_ST_SETUP_IN_PRG"  :  CZT_ND_ST_SETUP_IN_PRG  ,
   "CZT_ND_ST_NORMAL"        :  CZT_ND_ST_NORMAL        ,
   "CZT_ND_ST_RESET"         :  CZT_ND_ST_RESET         ,
   "CZT_CON_ST_IDLE"         :  CZT_CON_ST_IDLE         ,
   "CZT_CON_ST_CONNECTING"   :  CZT_CON_ST_CONNECTING   ,
   "CZT_CON_ST_ESTBLD"       :  CZT_CON_ST_ESTBLD       ,
   "CZT_CON_ST_RELEASING"    :  CZT_CON_ST_RELEASING    ,
   "CZT_CON_ST_NON_EXST"     :  CZT_CON_ST_NON_EXST     ,
   "CZT_AUD_UNKNOWN"         :  CZT_AUD_UNKNOWN         ,
   "CZT_AUD_PEER"            :  CZT_AUD_PEER            ,
   "CZT_AUD_FLC"             :  CZT_AUD_FLC             ,
   "CZT_STACAUSE_INV_TYPE"   :  CZT_STACAUSE_INV_TYPE   ,
   "CZT_STACAUSE_NOT_APPL"   :  CZT_STACAUSE_NOT_APPL   ,
   
   "CZ_GP_IDLE"              :  CZ_GP_IDLE,
   "CZ_GP_CONNECTING"        :  CZ_GP_CONNECTING,
   "CZ_GP_CONNECTED"         :  CZ_GP_CONNECTED,
   "CZ_GP_STATE_MAX"         :  CZ_GP_STATE_MAX,
   
   "CZT_STATUS_FLC_START"           :  CZT_STATUS_FLC_START           ,
   "CZT_STATUS_FLC_DROP"            :  CZT_STATUS_FLC_DROP            ,
   "CZT_STATUS_FLC_STOP"            :  CZT_STATUS_FLC_STOP            ,
   "CZT_STATUS_FLC_ACTIVE"          :  CZT_STATUS_FLC_ACTIVE          ,
   "CZT_STATUS_FLC_INACTIVE"        :  CZT_STATUS_FLC_INACTIVE        ,
   "SCT_FLC_START"           :  SCT_FLC_START           ,
   "SCT_FLC_DROP"            :  SCT_FLC_DROP            ,
   "SCT_FLC_STOP"            :  SCT_FLC_STOP            ,
   "SCT_FLC_ACTIVE"          :  SCT_FLC_ACTIVE          ,
   "SCT_FLC_INACTIVE"        :  SCT_FLC_INACTIVE        ,

   "CZAC_PRC0" : CZAC_PRC0,
   "CZAC_PRC1" : CZAC_PRC1,
   "CZAC_PRC2" : CZAC_PRC2,
   "CZAC_PRC3" : CZAC_PRC3,
   "CZAC_ENB1_PROC" :CZAC_ENB1_PROC, 
   "CZAC_XTA_PROC" :CZAC_XTA_PROC, 
   "CZAC_ENB2_PROC" :CZAC_ENB2_PROC, 

   "LCM_CATEGORY_INTERFACE" : LCM_CATEGORY_INTERFACE,
   "LCZ_EVENT_LI_ENDP_OPEN_CFM" : LCZ_EVENT_LI_ENDP_OPEN_CFM,
   "LCZ_CAUSE_SCT_ENPOPEN_SUCC" : LCZ_CAUSE_SCT_ENPOPEN_SUCC,
   "LCZ_USTA_DGNVAL_SAPID" : LCZ_USTA_DGNVAL_SAPID,

   "CZT_MSG_HO_REQ" :  CZT_MSG_HO_REQ        ,
   "CZT_MSG_HO_ACK" : CZT_MSG_HO_ACK         ,
   "CZT_MSG_HO_FAIL" : CZT_MSG_HO_FAIL        ,
   "CZT_MSG_HO_CANCEL" : CZT_MSG_HO_CANCEL      ,
   "CZT_MSG_SN_STATUS_TRFR" : CZT_MSG_SN_STATUS_TRFR ,
   "CZT_MSG_UE_CXT_RELEASE" : CZT_MSG_UE_CXT_RELEASE ,
   "CZT_MSG_LOAD_IND" : CZT_MSG_LOAD_IND       ,
   "CZT_MSG_ERR_IND" : CZT_MSG_ERR_IND        ,
   "CZT_MSG_X2_SETUP" : CZT_MSG_X2_SETUP       ,
   "CZT_MSG_X2_SETUP_RSP" : CZT_MSG_X2_SETUP_RSP ,
   "CZT_MSG_X2_SETUP_FAIL" : CZT_MSG_X2_SETUP_FAIL  ,
   "CZT_MSG_RESET" : CZT_MSG_RESET          ,
   "CZT_MSG_RESET_RSP" : CZT_MSG_RESET_RSP      ,
   "CZT_MSG_CFG_UPD_REQ" : CZT_MSG_CFG_UPD_REQ    ,
   "CZT_MSG_CFG_UPD_ACK" : CZT_MSG_CFG_UPD_ACK    ,
   "CZT_MSG_CFG_UPD_FAIL" : CZT_MSG_CFG_UPD_FAIL   ,
   "CZT_MSG_RSRC_ST_REQ" : CZT_MSG_RSRC_ST_REQ    ,
   "CZT_MSG_RSRC_ST_RSP" : CZT_MSG_RSRC_ST_RSP    ,
   "CZT_MSG_RSRC_ST_FAIL" : CZT_MSG_RSRC_ST_FAIL   ,
   "CZT_MSG_RSRC_ST_UPD" : CZT_MSG_RSRC_ST_UPD    ,
   # cm_xta_py_py_001.main_45 : X2AP 3.1
   "CZT_MSG_MOB_CHANGE_REQ" : CZT_MSG_MOB_CHANGE_REQ ,
   "CZT_MSG_MOB_CHANGE_ACK" : CZT_MSG_MOB_CHANGE_ACK ,
   "CZT_MSG_MOB_CHANGE_FAIL" : CZT_MSG_MOB_CHANGE_FAIL ,
   "CZT_MSG_RLF_INDICATION" : CZT_MSG_RLF_INDICATION ,
   "CZT_MSG_HO_REPORT" : CZT_MSG_HO_REPORT ,
   "CZT_MSG_CELL_ACTIVATION_REQ" : CZT_MSG_CELL_ACTIVATION_REQ ,
   "CZT_MSG_CELL_ACTIVATION_RES" : CZT_MSG_CELL_ACTIVATION_RES ,
   "CZT_MSG_CELL_ACTIVATION_FAIL" : CZT_MSG_CELL_ACTIVATION_FAIL ,
   "CZT_MSG_PRIV_MSG" : CZT_MSG_PRIV_MSG       ,

   "CZAC_START": CZAC_START,
   "CZAC_STOP": CZAC_STOP,

   "CZT_STA_TYPE_FLC"   : CZT_STA_TYPE_FLC,  
   "CZT_STA_TYPE_ASSOC" : CZT_STA_TYPE_ASSOC, 
   "CZT_STA_TYPE_TMR_EXPIRY" : CZT_STA_TYPE_TMR_EXPIRY,
   "CZT_STA_TYPE_TMR_START": CZT_STA_TYPE_TMR_START,

   "CZT_STATUS_ASSOC_DOWN" : CZT_STATUS_ASSOC_DOWN,  
   "CZT_STATUS_ASSOC_UP"   : CZT_STATUS_ASSOC_UP, 
   "CZT_STATUS_FLOW"       : CZT_STATUS_FLOW,
   "CZT_STATUS_UE_TRELOCPREP_EXPIRY"     :  CZT_STATUS_UE_TRELOCPREP_EXPIRY,
   "CZT_STATUS_UE_TX2RELOCOVERALL_EXPIRY" : CZT_STATUS_UE_TX2RELOCOVERALL_EXPIRY,
   "CZT_STATUS_CFGUPD_TW_EXPIRY"          : CZT_STATUS_CFGUPD_TW_EXPIRY,
   "CZT_STATUS_SETUPREQ_TW_EXPIRY"        : CZT_STATUS_SETUPREQ_TW_EXPIRY,
   "CZT_STATUS_CFGUPD_TMR_STARTED"        : CZT_STATUS_CFGUPD_TMR_STARTED,
   "CZT_STATUS_SETUPREQ_TMR_STARTED"      : CZT_STATUS_SETUPREQ_TMR_STARTED,

   "CZT_REASON_NOT_APPL" : CZT_REASON_NOT_APPL,
   "CZT_REASON_RCVD_TERMIND" : CZT_REASON_RCVD_TERMIND,
   "CZT_REASON_RCVD_COMM_UP" : CZT_REASON_RCVD_COMM_UP,
   "CZT_REASON_RCVD_NET_UP" : CZT_REASON_RCVD_NET_UP,
   "CZT_REASON_RCVD_NET_DOWN" : CZT_REASON_RCVD_NET_DOWN,
   "CZT_REASON_SCT_SEND_FAIL" : CZT_REASON_SCT_SEND_FAIL,
   "CZT_REASON_UBND_SAP"     : CZT_REASON_UBND_SAP,
   "CZT_REASON_FLC_START"    : CZT_REASON_FLC_START,
   "CZT_REASON_FLC_STOP"    : CZT_REASON_FLC_STOP,
   "CZT_REASON_DYNAM_PEER_NOT_CFG"    : CZT_REASON_DYNAM_PEER_NOT_CFG,

# All Error Cause Types
   "CZT_ERRTYPE_NONE"           :  CZT_ERRTYPE_NONE, 
   "CZT_ERRTYPE_INV_SDU_PARAM"   :  CZT_ERRTYPE_INV_SDU_PARAM,  
   "CZT_ERRTYPE_ENC_FAILED"      : CZT_ERRTYPE_ENC_FAILED,
   "CZT_ERRTYPE_DEC_FAILED"      : CZT_ERRTYPE_DEC_FAILED,
   "CZT_ERRTYPE_INV_PARAM"       : CZT_ERRTYPE_INV_PARAM,
   "CZT_ERRTYPE_MSG_SEND_FAILED"  : CZT_ERRTYPE_MSG_SEND_FAILED,
   "CZT_ERRTYPE_INTERNAL"         : CZT_ERRTYPE_INTERNAL,
   "CZT_ERRTYPE_SYS"              : CZT_ERRTYPE_SYS,
   "CZT_ERRTYPE_FROM_PEER"        : CZT_ERRTYPE_FROM_PEER,

# All Error Cause values set for X2AP
   "CZT_ERRCAUSE_MEM_ALLOC_FAIL"    :      CZT_ERRCAUSE_MEM_ALLOC_FAIL,
   "CZT_ERRCAUSE_HASH_INS_FAIL"     :      CZT_ERRCAUSE_HASH_INS_FAIL,
   "CZT_ERRCAUSE_UE_CB_CREATE_FAILED" :    CZT_ERRCAUSE_UE_CB_CREATE_FAILED,
   "CZT_ERRCAUSE_RSRC_CB_CREATE_FAILED" :  CZT_ERRCAUSE_RSRC_CB_CREATE_FAILED,
   "CZT_ERRCAUSE_TMR_ERR"               :  CZT_ERRCAUSE_TMR_ERR,
   "CZT_ERRCAUSE_PEER_CB_CREATE_FAILED" :  CZT_ERRCAUSE_PEER_CB_CREATE_FAILED,

# Type CZT_ERRTYPE_ENC_FAILED and CZT_ERRTYPE_DEC_FAILED
   "CZT_ERRCAUSE_SYNTAX_ERR"           :   CZT_ERRCAUSE_SYNTAX_ERR,
   "CZT_ERRCAUSE_MAND_PARAM_MISSING"   :   CZT_ERRCAUSE_MAND_PARAM_MISSING,

# CZT_ERRTYPE_INTERNAL */
   "CZT_ERRCAUSE_INV_STATE"           :    CZT_ERRCAUSE_INV_STATE,
   "CZT_ERRCAUSE_UNEXP_MSG"           :    CZT_ERRCAUSE_UNEXP_MSG,
   "CZT_ERRCAUSE_NODE_RESET"          :    CZT_ERRCAUSE_NODE_RESET,
   "CZT_ERRCAUSE_MAX_PEER_CONN"       :    CZT_ERRCAUSE_MAX_PEER_CONN,
   "CZT_ERRCAUSE_MAX_UE_CONN"         :    CZT_ERRCAUSE_MAX_UE_CONN,
   "CZT_ERRCAUSE_WAIT_TMR_ON"         :    CZT_ERRCAUSE_WAIT_TMR_ON,
   "CZT_ERRCAUSE_PARALLEL_CFGUPD_TRANS" :  CZT_ERRCAUSE_PARALLEL_CFGUPD_TRANS,

# For messages coming from UI the errorType will be CZT_ERRTYPE_INV_SDU_PARAM
#  * and for incoming messages it will be CZT_ERRTYPE_INV_PARAM 
   "CZT_ERRCAUSE_INV_PEERID"           :     CZT_ERRCAUSE_INV_PEERID,
   "CZT_ERRCAUSE_INV_OLD_UE_X2AP_ID"   :     CZT_ERRCAUSE_INV_OLD_UE_X2AP_ID,
   "CZT_ERRCAUSE_INV_NEW_UE_X2AP_ID"   :     CZT_ERRCAUSE_INV_NEW_UE_X2AP_ID,
   "CZT_ERRCAUSE_INV_ENB_ID"           :     CZT_ERRCAUSE_INV_ENB_ID,
   "CZT_ERRCAUSE_INV_ENB1_MEAS_ID"     :     CZT_ERRCAUSE_INV_ENB1_MEAS_ID,
   "CZT_ERRCAUSE_INV_ENB2_MEAS_ID"     :     CZT_ERRCAUSE_INV_ENB2_MEAS_ID,
   "CZT_ERRCAUSE_DUPLICATE_PEERID"     :     CZT_ERRCAUSE_DUPLICATE_PEERID,
   "CZT_ERRCAUSE_DUPLICATE_OLD_UE_X2AP_ID"  : CZT_ERRCAUSE_DUPLICATE_OLD_UE_X2AP_ID,
   "CZT_ERRCAUSE_DUPLICATE_ENB1_MEAS_ID"    :  CZT_ERRCAUSE_DUPLICATE_ENB1_MEAS_ID,
   "CZT_ERRCAUSE_DUPLICATE_ENB2_MEAS_ID"    :  CZT_ERRCAUSE_DUPLICATE_ENB2_MEAS_ID,
   "CZT_ERRCAUSE_PARAM_OUT_OF_BOUNDS"       :  CZT_ERRCAUSE_PARAM_OUT_OF_BOUNDS,

# CZT_ERRTYPE_MSG_SEND_FAILED 
   "CZT_ERRCAUSE_SAP_NOTPRST"              :   CZT_ERRCAUSE_SAP_NOTPRST,
   "CZT_ERRCAUSE_SAP_NOT_BOUND"            :   CZT_ERRCAUSE_SAP_NOT_BOUND,
   "CZT_ERRCAUSE_ASSOC_NOTPRST"            :   CZT_ERRCAUSE_ASSOC_NOTPRST,
   "CZT_ERRCAUSE_ENC_FAILED"               :   CZT_ERRCAUSE_ENC_FAILED,
   "CZT_ERRCAUSE_MSG_NOT_DELIVERED"        :   CZT_ERRCAUSE_MSG_NOT_DELIVERED,


   "CAUSE_RADIONW"  :  CAUSE_RADIONW,
   "CAUSE_TRANSPORT"  :  CAUSE_TRANSPORT,
   "CAUSE_PROTOCOL"  :  CAUSE_PROTOCOL,
   "CAUSE_MISC"  :  CAUSE_MISC,
   "CAUSE_ERR"   : CAUSE_ERR,
	# For Dynamic Peer Allocation Feature -- DPA
   "CZT_STA_TYPE_PEER" : CZT_STA_TYPE_PEER,
   "CZT_REASON_NOT_APPL" : CZT_REASON_NOT_APPL,
   "CZT_REASON_INV_PEERID" : CZT_REASON_INV_PEERID,
   "CZT_REASON_INV_RELTYPE" : CZT_REASON_INV_RELTYPE,
   "CZT_REASON_INV_UEID" : CZT_REASON_INV_UEID,
   "CZT_REASON_INV_IDTYPE" : CZT_REASON_INV_IDTYPE,
   "CZT_REASON_INV_RSRCID" : CZT_REASON_INV_RSRCID,
   "CZT_STATUS_DYNAM_PEERCFG_OK" : CZT_STATUS_DYNAM_PEERCFG_OK,
   "CZT_STATUS_DYNAM_PEERCFG_NOK" : CZT_STATUS_DYNAM_PEERCFG_NOK,
   "CZT_PRIM_OK" : CZT_PRIM_OK,
   "CZT_PRIM_NOK" : CZT_PRIM_NOK,
   "CZT_CAUSE_NOT_APPL" : CZT_CAUSE_NOT_APPL,
   "CZT_CAUSE_INV_PEERID" : CZT_CAUSE_INV_PEERID,
   "LCZ_EVENT_UI_PEERASSOC_RSP" : LCZ_EVENT_UI_PEERASSOC_RSP,
   "LCZ_CAUSE_DYNAM_PEERCFG_OK": LCZ_CAUSE_DYNAM_PEERCFG_OK,
   "LCZ_CAUSE_DYNAM_PEERCFG_NOK" : LCZ_CAUSE_DYNAM_PEERCFG_NOK,
   "CZT_LOCAL_REL" : CZT_LOCAL_REL,
   "CZT_CXT_REL " : CZT_CXT_REL,
   "CZT_CONN_TYPE_SU" : CZT_CONN_TYPE_SU,
   "CZT_CONN_TYPE_SP" : CZT_CONN_TYPE_SP,

# LTE X2AP: For various flavours of release
   "CZT_RELTYPE_INVALID" :  CZT_RELTYPE_INVALID,
   "CZT_RELTYPE_RESET" :  CZT_RELTYPE_RESET,
   "CZT_RELTYPE_TERM"  :   CZT_RELTYPE_TERM,
   "CZT_RELTYPE_UE"    :   CZT_RELTYPE_UE,
   "CZT_RELTYPE_RSRC"  :   CZT_RELTYPE_RSRC,

   "CZT_NODETYPE_INVALID" : CZT_NODETYPE_INVALID,
   "CZT_NODETYPE_LOCAL" : CZT_NODETYPE_LOCAL,
   "CZT_NODETYPE_REMOTE" : CZT_NODETYPE_REMOTE,

# For EGTP 
   "LEG_TSAP_TYPE_TUCL" : LEG_TSAP_TYPE_TUCL,
   "LEG_TRC_EVENT_RX" : LEG_TRC_EVENT_RX,
   "LEG_TRC_EVENT_TX" : LEG_TRC_EVENT_TX,
   "LEG_TSAP_TYPE_DTUCL" : LEG_TSAP_TYPE_DTUCL,
   "LEG_GTP_ENT_MME" : LEG_GTP_ENT_MME,
   "LEG_GTP_ENT_SGW" : LEG_GTP_ENT_SGW,
   "LEG_GTP_ENT_PGW" : LEG_GTP_ENT_PGW,
   "LEG_GTP_ENT_SGSN" : LEG_GTP_ENT_SGSN,
   "LEG_GTP_ENT_MBMSGW" : LEG_GTP_ENT_MBMSGW,
#cm_xta_py_py_001.main_56 - S2B and S2A 
   "LEG_GTP_ENT_MSC" : LEG_GTP_ENT_MSC,
   "LEG_GTP_ENT_EPDG" : LEG_GTP_ENT_EPDG,
   "LEG_GTP_ENT_TWAN" : LEG_GTP_ENT_TWAN,
   "LEG_GTP_ENT_UNKNWN" : LEG_GTP_ENT_UNKNWN,
   "LEG_INV_GEN_CNTRL_ACTION" : LEG_INV_GEN_CNTRL_ACTION,
   "LEG_INV_GEN_CNTRL_SUBACTION" : LEG_INV_GEN_CNTRL_SUBACTION,
   "LEG_INV_USAP_CNTRL_ACTION" : LEG_INV_USAP_CNTRL_ACTION,
   "LEG_INV_LSAP_CNTRL_ACTION" : LEG_INV_LSAP_CNTRL_ACTION,
   "LEG_INV_TSRV_CNTRL_ACTION" : LEG_INV_TSRV_CNTRL_ACTION,

   "LEG_EVENT_TPTSRV_ENA" : LEG_EVENT_TPTSRV_ENA,
   "LEG_EVENT_TPTSRV_DIS" : LEG_EVENT_TPTSRV_DIS,
   "LEG_EVENT_USAP_DIS" : LEG_EVENT_USAP_DIS,
   "LEG_EVENT_HIT_BNDCFM" : LEG_EVENT_HIT_BNDCFM,
   "LEG_EVENT_HIT_DISCIND" : LEG_EVENT_HIT_DISCIND,
   "LEG_EVENT_HIT_DISCCFM" : LEG_EVENT_HIT_DISCCFM,
   "LEG_EVENT_HIT_UDATIND" : LEG_EVENT_HIT_UDATIND,
   "LEG_EVENT_HIT_FLCIND" : LEG_EVENT_HIT_FLCIND,
   "LEG_EVENT_DMEM_ALLOC_PASS" : LEG_EVENT_DMEM_ALLOC_PASS,
   "LEG_EVENT_HIT_CONCFM" : LEG_EVENT_HIT_CONCFM,
   "LCM_EVENT_UBND_OK" : LCM_EVENT_UBND_OK,

   "LEG_CAUSE_SAP_BND" : LEG_CAUSE_SAP_BND,
   "LEG_CAUSE_SAP_UBND" : LEG_CAUSE_SAP_UBND,
   "LEG_CAUSE_SAP_BNDDIS" : LEG_CAUSE_SAP_BNDDIS,
   "LEG_CAUSE_SAP_BNDENA" : LEG_CAUSE_SAP_BNDENA,
   "LEG_CAUSE_LI_INITIATED" : LEG_CAUSE_LI_INITIATED,
   "LEG_CAUSE_TPT_FAIL" : LEG_CAUSE_TPT_FAIL,
   "LEG_CAUSE_DST_IP_DEL" : LEG_CAUSE_DST_IP_DEL,
   "LEG_CAUSE_LCL_PORT_NOT_REACHABLE" : LEG_CAUSE_LCL_PORT_NOT_REACHABLE,
   "LEG_CAUSE_DST_IP_NOT_REACHABLE" : LEG_CAUSE_DST_IP_NOT_REACHABLE,
   "LEG_CAUSE_PENDING_CNTRL_OP" : LEG_CAUSE_PENDING_CNTRL_OP,

   "LEG_CAUSE_DST_IP_REACHABLE" : LEG_CAUSE_DST_IP_REACHABLE,
   "LEG_CAUSE_DST_IP_NOT_CONFIG" : LEG_CAUSE_DST_IP_NOT_CONFIG,

   "LEG_PAR_USAP" : LEG_PAR_USAP,
   "LEG_PAR_MEM" : LEG_PAR_MEM,
   "LEG_PAR_TSAP" : LEG_PAR_TSAP,
   "LEG_PAR_IECODE" : LEG_PAR_IECODE,
   "LEG_PAR_TSRV" : LEG_PAR_TSRV,
   "LEG_PAR_GEN" : LEG_PAR_GEN,
   "LEG_PAR_CONNID" : LEG_PAR_CONNID,
   "LEG_PAR_IP" : LEG_PAR_IP,
   "LEG_PAR_PORT" : LEG_PAR_PORT,

   "STEGGEN" : STEGGEN,
   "STEGUSAP" : STEGUSAP,
   "STEGTSAP" : STEGTSAP,
   "STEGSRVR" : STEGSRVR,
   "STEGMSG" : STEGMSG,
   "STEGIE" : STEGIE,
   "STEGSID" : STEGSID,
   "EGT_STATYPE_PATH" : EGT_STATYPE_PATH,
   "EGT_STATYPE_TUNNEL" : EGT_STATYPE_TUNNEL,

   # cm_xta_py_py_001.main_53 : parm for inidcating the creation of dummy tunnel
      "DUMMY" : DUMMY,

# Added for eGTPU
   "LEG_NODE_UMTS" : LEG_NODE_UMTS,
   "LEG_NODE_LTE" : LEG_NODE_LTE,
   "STEGTHRD" : STEGTHRD,
   "STEGSRVR" : STEGSRVR,
   "STEGIPADDR" : STEGIPADDR,
   "STEGTNL" : STEGTNL,
   "EGT_GTPU_MSG_ECHO_REQ" : EGT_GTPU_MSG_ECHO_REQ,
    "EGT_GTPU_MSG_INVALID" : EGT_GTPU_MSG_INVALID,
   "EGT_GTPU_MSG_ECHO_RSP" : EGT_GTPU_MSG_ECHO_RSP,
   "EGT_GTPU_MSG_GPDU" : EGT_GTPU_MSG_GPDU,
   "EGT_GTPU_MSG_END_MARKER" : EGT_GTPU_MSG_END_MARKER,
   "EGT_GTPU_MSG_ERROR_IND" : EGT_GTPU_MSG_ERROR_IND,
   "EGT_GTPU_DEST_UNREACHABLE" : EGT_GTPU_DEST_UNREACHABLE,
   "EGT_GTPU_DEST_REACHABLE" : EGT_GTPU_DEST_REACHABLE,
   "EGT_GTPU_PORT_ACTIVE" : EGT_GTPU_PORT_ACTIVE,
   "EGT_GTPU_PORT_INACTIVE" : EGT_GTPU_PORT_INACTIVE,
   "EGT_GTPU_MSG_SUPP_EXT_HDR_NTF" : EGT_GTPU_MSG_SUPP_EXT_HDR_NTF,
   "EGU_IE_EXT_HDR_LST" : EGU_IE_EXT_HDR_LST,
   "ROKPENDING" : ROKPENDING,
   "EGU_IE_RECOVERY" : EGU_IE_RECOVERY,
   "EGU_IE_TEID" : EGU_IE_TEID,
   "EGU_IE_GSN_ADDR" : EGU_IE_GSN_ADDR,
   "EGU_IE_PVT_EXTN" : EGU_IE_PVT_EXTN,
   "LEG_MOVE_IP" : LEG_MOVE_IP,
   "LEG_REASON_INV_PROTFLAG" : LEG_REASON_INV_PROTFLAG,
   "LEG_REASON_FOUND_IP_ADDR_FAILED" : LEG_REASON_FOUND_IP_ADDR_FAILED,
   "LEG_REASON_DFLT_PORT_NOT_OPEANED" : LEG_REASON_DFLT_PORT_NOT_OPEANED,
   "CM_TPTADDR_NOTPRSNT" : CM_TPTADDR_NOTPRSNT,
   "LEG_REASON_INVALID_IP_TYPE" : LEG_REASON_INVALID_IP_TYPE,
   "LEG_REASON_INVALID_PORT" : LEG_REASON_INVALID_PORT,
   "LEG_REASON_USAPCFG_NOT_DONE" : LEG_REASON_USAPCFG_NOT_DONE,
   "LEG_REASON_IP_EXISTS" : LEG_REASON_IP_EXISTS,
   "LEG_REASON_FOUND_DEST_ADDR_FAILED" : LEG_REASON_FOUND_DEST_ADDR_FAILED,
   "LEG_REASON_FOUND_TEID_FAILED" : LEG_REASON_FOUND_TEID_FAILED,
   "LEG_REASON_FOUND_TPT_ADDR_FAILED" : LEG_REASON_FOUND_TPT_ADDR_FAILED,
   
   
# For LTE RRC 
   "LNH_REASON_PROTCFG_NOT_DONE" : LNH_REASON_PROTCFG_NOT_DONE,
   "LNH_REASON_LSAPCFG_NOT_DONE" : LNH_REASON_LSAPCFG_NOT_DONE,
   "LNH_REASON_USAPCFG_NOT_DONE" : LNH_REASON_USAPCFG_NOT_DONE,
   "LNH_REASON_UE_DOES_NOT_EXIST" : LNH_REASON_UE_DOES_NOT_EXIST,
   "LNH_REASON_DUP_SAP_ENTRY" : LNH_REASON_DUP_SAP_ENTRY,
   "LNH_REASON_SEL_VAL_NOT_ALLOWED" : LNH_REASON_SEL_VAL_NOT_ALLOWED,
   "LNH_REASON_SHUTDOWN_TMR_EXPD" : LNH_REASON_SHUTDOWN_TMR_EXPD,
   "LNH_REASON_CELL_DOES_NOT_EXIST" : LNH_REASON_CELL_DOES_NOT_EXIST,

#For NG Values in DUMMY CRG config for LTE MAC
   "RGAC_RGR_NG_ONESIXTH" : RGAC_RGR_NG_ONESIXTH,
   "RGAC_RGR_NG_HALF" : RGAC_RGR_NG_HALF,
   "RGAC_RGR_NG_ONE" : RGAC_RGR_NG_ONE,
   "RGAC_RGR_NG_TWO" : RGAC_RGR_NG_TWO,
   "RGAC_RGR_NG_ERR_THREE" : RGAC_RGR_NG_ERR_THREE,
   "RGAC_RGR_NG_ERR" : RGAC_RGR_NG_ERR,
#For TxMode Values
   "RGR_UE_TM_1" : RGR_UE_TM_1,
   "RGR_UE_TM_2" : RGR_UE_TM_2,
   "RGAC_RGR_UE_TM_3" : RGAC_RGR_UE_TM_3,
   "RGAC_RGR_UE_TM_4" : RGAC_RGR_UE_TM_4,
   "RGAC_RGR_UE_TM_5" : RGAC_RGR_UE_TM_5,
   "RGAC_RGR_UE_TM_6" : RGAC_RGR_UE_TM_6,
   "RGAC_RGR_UE_TM_7" : RGAC_RGR_UE_TM_7,
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   "RGR_UE_TM_3" : RGR_UE_TM_3,
   "RGR_UE_TM_4" : RGR_UE_TM_4,
   "RGR_UE_TM_5" : RGR_UE_TM_5,
   "RGR_UE_TM_6" : RGR_UE_TM_6,
   "RGR_UE_TM_7" : RGR_UE_TM_7,
   "CRG_UE_TM_1" : CRG_UE_TM_1,
   "CRG_UE_TM_2" : CRG_UE_TM_2,
   "CRG_UE_TM_3" : CRG_UE_TM_3,
   "CRG_UE_TM_4" : CRG_UE_TM_4,
   "CRG_UE_TM_5" : CRG_UE_TM_5,
   "CRG_UE_TM_6" : CRG_UE_TM_6,
   "CRG_UE_TM_7" : CRG_UE_TM_7,
   "TFU_UE_TM_1" : TFU_UE_TM_1,
   "TFU_UE_TM_2" : TFU_UE_TM_2,
   "TFU_UE_TM_3" : TFU_UE_TM_3,
   "TFU_UE_TM_4" : TFU_UE_TM_4,
   "TFU_UE_TM_5" : TFU_UE_TM_5,
   "TFU_UE_TM_6" : TFU_UE_TM_6,
   "TFU_UE_TM_7" : TFU_UE_TM_7,
   "TFU_RPT_CQI" : TFU_RPT_CQI,
   "TFU_RPT_RI" : TFU_RPT_RI,
   "RGAC_RGR_UE_TM_ERR" : RGAC_RGR_UE_TM_ERR,
   "RGAC_ACKNACK_REPFACT_N2_ERR" : RGAC_ACKNACK_REPFACT_N2_ERR,
#For APRD CQI Values   
   "RGAC_RGR_APRD_CQI_MOD12" : RGAC_RGR_APRD_CQI_MOD12,
   "RGAC_RGR_APRD_CQI_MOD20" : RGAC_RGR_APRD_CQI_MOD20,
   "RGAC_RGR_APRD_CQI_MOD22" : RGAC_RGR_APRD_CQI_MOD22,
   "RGAC_RGR_APRD_CQI_MOD30" : RGAC_RGR_APRD_CQI_MOD30,
   "RGAC_RGR_APRD_CQI_MOD31" : RGAC_RGR_APRD_CQI_MOD31,
   "RGAC_RGR_APRD_CQI_MODERR" : RGAC_RGR_APRD_CQI_MODERR,
   "RGAC_RGR_PRD_CQI_MOD10" : RGAC_RGR_PRD_CQI_MOD10, 
   "RGAC_RGR_PRD_CQI_MOD11" :  RGAC_RGR_PRD_CQI_MOD11,
   "RGAC_RGR_PRD_CQI_MOD20" :  RGAC_RGR_PRD_CQI_MOD20,
   "RGAC_RGR_PRD_CQI_MOD21" : RGAC_RGR_PRD_CQI_MOD21,
   "RGAC_RGR_PRD_CQI_MODERR" : RGAC_RGR_PRD_CQI_MODERR,
   "RGAC_RGR_CELL_CFG" : RGAC_RGR_CELL_CFG,
   "RGAC_RGR_UE_CFG" : RGAC_RGR_UE_CFG,
   "RGAC_RGR_LCH_CFG" : RGAC_RGR_LCH_CFG, 
   "RGAC_RGR_LCG_CFG" : RGAC_RGR_LCG_CFG,
   "RGAC_RGR_ENB_CFG" : RGAC_RGR_ENB_CFG,
   "RGAC_CRG_CELL_CFG" : RGAC_CRG_CELL_CFG, 
   "RGAC_CRG_UE_CFG" : RGAC_CRG_UE_CFG,
   "RGAC_CRG_LCH_CFG" : RGAC_CRG_LCH_CFG,
   "CM_LTE_UE_CAT_1" : CM_LTE_UE_CAT_1,
   "CM_LTE_UE_CAT_2" : CM_LTE_UE_CAT_2,
   "CM_LTE_UE_CAT_3" : CM_LTE_UE_CAT_3,
   "CM_LTE_UE_CAT_4" : CM_LTE_UE_CAT_4,
   "CM_LTE_UE_CAT_5" : CM_LTE_UE_CAT_5,
   "RGR_TDD_ACKNACK_MODE_MULT" :  RGR_TDD_ACKNACK_MODE_MULT,
   "RGR_TDD_ACKNACK_MODE_BUNDL" : RGR_TDD_ACKNACK_MODE_BUNDL,
   "RG_ACC_PLUS" : RG_ACC_PLUS,
   "RG_ACC_MINUS" : RG_ACC_MINUS,
   "STTFUSAP" : STTFUSAP,
   "STRGUSAP" : STRGUSAP,
   "STRGRSAP" : STRGRSAP,
   "STCRGSAP" : STCRGSAP,
   "RGR_ACKNACK_REPFACT_N2" : RGR_ACKNACK_REPFACT_N2,
   "RGR_ACKNACK_REPFACT_N4" : RGR_ACKNACK_REPFACT_N4,
   "RGR_ACKNACK_REPFACT_N6" : RGR_ACKNACK_REPFACT_N6,
   "RGAC_RGR_SRS_BWCFG_0" : RGAC_RGR_SRS_BWCFG_0,
   "RGAC_RGR_SRS_BWCFG_1" : RGAC_RGR_SRS_BWCFG_1,
   "RGAC_RGR_SRS_BWCFG_2" : RGAC_RGR_SRS_BWCFG_2,
   "RGAC_RGR_SRS_BWCFG_3" : RGAC_RGR_SRS_BWCFG_3,
   "RGAC_RGR_SRS_BWCFG_4" : RGAC_RGR_SRS_BWCFG_4,
   "RGAC_RGR_SRS_BWCFG_5" : RGAC_RGR_SRS_BWCFG_5,
   "RGAC_RGR_SRS_BWCFG_6" : RGAC_RGR_SRS_BWCFG_6,
   "RGAC_RGR_SRS_BWCFG_7" : RGAC_RGR_SRS_BWCFG_7,
   "RGAC_RGR_SRS_BWCFG_ERR" : RGAC_RGR_SRS_BWCFG_ERR,
   "RGAC_RGR_SRS_CFG_PRD_1" : RGAC_RGR_SRS_CFG_PRD_1,
   "RGAC_RGR_SRS_CFG_PRD_2" : RGAC_RGR_SRS_CFG_PRD_2,
   "RGAC_RGR_SRS_CFG_PRD_5" : RGAC_RGR_SRS_CFG_PRD_5,
   "RGAC_RGR_SRS_CFG_PRD_10": RGAC_RGR_SRS_CFG_PRD_10,
   "RGAC_RGR_SFN_EVEN" : RGAC_RGR_SFN_EVEN,
   "RGAC_RGR_SFN_ANY" : RGAC_RGR_SFN_ANY,
   "RGAC_RGR_SFN_NA" : RGAC_RGR_SFN_NA,
   "RGAC_RGR_SI_CFG_TYPE_MIB" : RGAC_RGR_SI_CFG_TYPE_MIB,
   "RGAC_RGR_SI_CFG_TYPE_SIB1" : RGAC_RGR_SI_CFG_TYPE_SIB1,
   "RGAC_RGR_SI_CFG_TYPE_SI" : RGAC_RGR_SI_CFG_TYPE_SI,
   "RGAC_RGR_SI_CFG_TYPE_INV" : RGAC_RGR_SI_CFG_TYPE_INV,
   "TFU_CQI_MODE20" : TFU_CQI_MODE20,
   "TFU_CQI_MODE30" : TFU_CQI_MODE30, 
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   "TFU_PUSCH_CQI_MODE_12" : TFU_PUSCH_CQI_MODE_12,
   "TFU_PUSCH_CQI_MODE_20" : TFU_PUSCH_CQI_MODE_20,
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   "TFU_PUSCH_CQI_MODE_22" : TFU_PUSCH_CQI_MODE_22,
   "TFU_PUSCH_CQI_MODE_30" : TFU_PUSCH_CQI_MODE_30, 
# cm_xta_py_py_001.main_36 - Changes for MIMO feature addition 
   "TFU_PUSCH_CQI_MODE_31" : TFU_PUSCH_CQI_MODE_31,
   "RGR_TXMODE_RECFG_CMPLT" : RGR_TXMODE_RECFG_CMPLT, 
   "RGR_TXMODE_RECFG_START" : RGR_TXMODE_RECFG_START,
   "TFU_DCI_FORMAT_2"      : TFU_DCI_FORMAT_2,
# cm_xta_py_py_001.main_40 - Changes for TFU Upgrade
   "TFU_HQ_NACK" : TFU_HQ_NACK,
   "TFU_HQ_ACK" : TFU_HQ_ACK,
   "TFU_HQ_DTX" : TFU_HQ_DTX,
   "TFU_HQ_ACK_OR_NACK" :TFU_HQ_ACK_OR_NACK,
   "TFU_HQ_ACK_OR_DTX" :TFU_HQ_ACK_OR_DTX,
   "TFU_HQ_NACK_OR_DTX" : TFU_HQ_NACK_OR_DTX,
   "TFU_HQ_ACK_OR_NACK_OR_DTX" :TFU_HQ_ACK_OR_NACK_OR_DTX,
#Iuh 2.1 release
   "HMAC_SCTP_DM" :  HMAC_SCTP_DM,
   "LHM_TYPE_HNB" : LHM_TYPE_HNB,
   "LHM_TYPE_HNBGW" : LHM_TYPE_HNBGW,
   "LHM_TYPE_INVALID" : LHM_TYPE_INVALID,
   "STHMSCTSAP"       :STHMSCTSAP,
   "STHMPEER"         :STHMPEER,
   "ASHMESTABLISH": ASHMESTABLISH,
   "ASHMTERMINATE" : ASHMTERMINATE, 
   "SAELMNT" : SAELMNT,
   "HMAC_RUA_CONNECT" : HMAC_RUA_CONNECT,
   "HMAC_RUA_DIRECT_TRANSFER" : HMAC_RUA_DIRECT_TRANSFER,
   "HMAC_RUA_DISCONNECT" : HMAC_RUA_DISCONNECT,
   "HMAC_RUA_CONNECTION_LESS" : HMAC_RUA_CONNECTION_LESS,
   "HMAC_RUA_ERR_IND" : HMAC_RUA_ERR_IND,
   "HMAC_HNBAP_HNB_REG_REQ" : HMAC_HNBAP_HNB_REG_REQ,
   "HMAC_HNBAP_HNB_REG_ACC" : HMAC_HNBAP_HNB_REG_ACC,
   "HMAC_HNBAP_HNB_REG_REJ" : HMAC_HNBAP_HNB_REG_REJ,
   "HMAC_HNBAP_UE_REG_REQ" : HMAC_HNBAP_UE_REG_REQ,
   "HMAC_HNBAP_UE_REG_ACC" : HMAC_HNBAP_UE_REG_ACC,
   "HMAC_HNBAP_UE_REG_REJ" : HMAC_HNBAP_UE_REG_REJ,
   "HMAC_HNBAP_HNB_DEREG_REQ" : HMAC_HNBAP_HNB_DEREG_REQ,
   "HMAC_HNBAP_UE_DEREG_REQ" : HMAC_HNBAP_UE_DEREG_REQ,
   "HMAC_HNBAP_ERR_IND_PROC" : HMAC_HNBAP_ERR_IND_PROC,
   "HMAC_HNBAP_CSG_UPD_REQ" : HMAC_HNBAP_CSG_UPD_REQ,
   "HMAC_HNT_LCL_ERR" : HMAC_HNT_LCL_ERR,
   "HMAC_HNT_PEER_ERR" : HMAC_HNT_PEER_ERR,
   "HNT_ERRCAUSE_INV_MSG" : HNT_ERRCAUSE_INV_MSG,
   "HNT_ERRCAUSE_ENC_FAILED" : HNT_ERRCAUSE_ENC_FAILED,
   "HNT_ERRCAUSE_UE_NOT_REG" : HNT_ERRCAUSE_UE_NOT_REG,
   "HNT_ERRCAUSE_HNB_NOT_REG" : HNT_ERRCAUSE_HNB_NOT_REG,
   "HNT_ERRCAUSE_INV_PEERID" : HNT_ERRCAUSE_INV_PEERID,
   "HNT_ERRCAUSE_NO_PEERID" : HNT_ERRCAUSE_NO_PEERID,
   "HNT_ERRCAUSE_UNEXP_MSG" : HNT_ERRCAUSE_UNEXP_MSG,
   "HNT_ERRCAUSE_NO_SDU" : HNT_ERRCAUSE_NO_SDU,
   "HNT_ERRCAUSE_INV_LSAPCB" : HNT_ERRCAUSE_INV_LSAPCB,
   "HNT_ERRCAUSE_NO_UE_CNTXID" : HNT_ERRCAUSE_NO_UE_CNTXID,
   "HNT_ERRCAUSE_ERRONEOUS_RSP" : HNT_ERRCAUSE_ERRONEOUS_RSP,
   "HNT_ERRCAUSE_RADNWHNB_NOT_REG" : HNT_ERRCAUSE_RADNWHNB_NOT_REG,
   "HNT_ACC_STRTM_REL_IND_8_BEYOND" : HNT_ACC_STRTM_REL_IND_8_BEYOND,
   "HNT_ERRCAUSE_PROT_NOT_COMPATBLE_RCVR_STATE" : HNT_ERRCAUSE_PROT_NOT_COMPATBLE_RCVR_STATE,
   "HNT_ERRCAUSE_PROT_TRANSFER_SYNTX_ERR" : HNT_ERRCAUSE_PROT_TRANSFER_SYNTX_ERR,
   "HNT_ERRCAUSE_PROT_ABS_SYNTX_REJ" : HNT_ERRCAUSE_PROT_ABS_SYNTX_REJ,
   "HNT_ERRCAUSE_PROT_ABS_SYNTX_ERR_FALSE_CONST_MSG" : HNT_ERRCAUSE_PROT_ABS_SYNTX_ERR_FALSE_CONST_MSG,
   "HMAC_RUA"                : HMAC_RUA,
   "HMAC_HNBAP"              : HMAC_HNBAP,
   "HMAC_INV"                : HMAC_INV,
   "CUS_RADIONW"             : CUS_RADIONW,
   "HntCusRadNwoverloadEnum" : HntCusRadNwoverloadEnum,
   "RutCusRadNwnormalEnum"   : RutCusRadNwnormalEnum,
   "HMAC_UNKNOWN_IE"         : HMAC_UNKNOWN_IE,
   "HMAC_LOGICVOIL_IE"       : HMAC_LOGICVOIL_IE,
   "HMAC_OUTOFORD_IE"        : HMAC_OUTOFORD_IE,
   "HMAC_MULTOCC_IE"         : HMAC_MULTOCC_IE,
   "LHM_CAUSE_SCT_ENPOPEN_SUCC" : LHM_CAUSE_SCT_ENPOPEN_SUCC,
   "LHM_EVENT_LI_ENDP_OPEN_CFM" : LHM_EVENT_LI_ENDP_OPEN_CFM,
   "LHM_TRC_PNODE" : LHM_TRC_PNODE,
   "LHM_TRC_LSAP_IN" : LHM_TRC_LSAP_IN,
   "LHM_TRC_LSAP_OUT" : LHM_TRC_LSAP_OUT,
   "LHM_TRC_PNODE_IN" : LHM_TRC_PNODE_IN,
   "LHM_TRC_PNODE_OUT" : LHM_TRC_PNODE_OUT,
   "LHM_INV_ZEROSTS" : LHM_INV_ZEROSTS,
   "LHM_CAUSE_CONGESTION_RECV" :LHM_CAUSE_CONGESTION_RECV,
   "LHM_CAUSE_ASSOC_UP"  :   LHM_CAUSE_ASSOC_UP,
   "LHM_CAUSE_ASSOC_DOWN"  :LHM_CAUSE_ASSOC_DOWN,
   "LHM_CAUSE_PEER_DELETED"  :LHM_CAUSE_PEER_DELETED,
   "LHM_CAUSE_ENDP_OPEN"     : LHM_CAUSE_ENDP_OPEN,
   "LHM_CAUSE_EXCEED_CONF_VAL" :LHM_CAUSE_EXCEED_CONF_VAL,
   "LHM_CAUSE_OUTRES"        : LHM_CAUSE_OUTRES,
   "LHM_CAUSE_SCT_ENPOPEN_SUCC" : LHM_CAUSE_SCT_ENPOPEN_SUCC,
   "LHM_CAUSE_EPCLOSE_OK"   :   LHM_CAUSE_EPCLOSE_OK,
   "LHM_CAUSE_SAP_BND"      :   LHM_CAUSE_SAP_BND,
   "LHM_CAUSE_SAP_UBND"      : LHM_CAUSE_SAP_UBND,
   "LHM_CAUSE_INV_PEER"      :LHM_CAUSE_INV_PEER,
   "LHM_CAUSE_INV_UE"        : LHM_CAUSE_INV_UE,
   "LHM_CAUSE_HNB_REG_TMR_EXP" : LHM_CAUSE_HNB_REG_TMR_EXP,
   "LHM_CAUSE_SCT_BND_TMR_EXP" : LHM_CAUSE_SCT_BND_TMR_EXP,
   "LHM_CAUSE_TMR_EXPIRED"     : LHM_CAUSE_TMR_EXPIRED,
   "LHM_CAUSE_RETRY_EXCEED"   :  LHM_CAUSE_RETRY_EXCEED,
   "LHM_CAUSE_FLC_DROP"      :  LHM_CAUSE_FLC_DROP,
   "LHM_EVENT_LI_BND_OK"       : LHM_EVENT_LI_BND_OK,
   "LHM_EVENT_RUT_BND_OK"      : LHM_EVENT_RUT_BND_OK,
   "LHM_EVENT_HNT_BND_OK"     :  LHM_EVENT_HNT_BND_OK,
   "LHM_EVENT_EOPEN_OK"      :   LHM_EVENT_EOPEN_OK,
   "LHM_EVENT_LI_ENDP_CLOSE_CFM": LHM_EVENT_LI_ENDP_CLOSE_CFM,
   "LHM_EVENT_LI_ASSOC_IND"  :   LHM_EVENT_LI_ASSOC_IND,
   "LHM_EVENT_LI_ASSOC_CFM"   :  LHM_EVENT_LI_ASSOC_CFM,
   "LHM_EVENT_LI_TERM_IND"     : LHM_EVENT_LI_TERM_IND,
   "LHM_EVENT_LI_TERM_CFM"      : LHM_EVENT_LI_TERM_CFM,
   "LHM_EVENT_LI_FLC_IND"        : LHM_EVENT_LI_FLC_IND,
   "LHM_EVENT_DMEM_ALLOC_PASS"  : LHM_EVENT_DMEM_ALLOC_PASS,
   "LHM_EVENT_UI_SAP_UBND_SUCC" : LHM_EVENT_UI_SAP_UBND_SUCC,
   "LHM_EVENT_LI_DAT_IND"    :    LHM_EVENT_LI_DAT_IND,
   "LHM_EVENT_LI_STA_IND"    :   LHM_EVENT_LI_STA_IND,
   "LHM_EVENT_MAX_PEERS_REACHED" : LHM_EVENT_MAX_PEERS_REACHED,
   "LHM_EVENT_MAX_UES_REACHED"  :   LHM_EVENT_MAX_UES_REACHED,
   "LHM_EVENT_EOPEN_FAIL"      :  LHM_EVENT_EOPEN_FAIL,
   "LHM_EVENT_TERM_FAIL"        : LHM_EVENT_TERM_FAIL,
   "LHM_EVENT_ECLOSE_OK"        :  LHM_EVENT_ECLOSE_OK,
   "LHM_EVENT_ECLOSE_NOK"       :  LHM_EVENT_ECLOSE_NOK,
   "LHM_EVENT_SCTP_FLCIND"      :  LHM_EVENT_SCTP_FLCIND,
   "LHM_EVENT_SCTP_ASSOC_UP"    : LHM_EVENT_SCTP_ASSOC_UP,
   "LHM_EVENT_SCTP_SND_FAIL"   :   LHM_EVENT_SCTP_SND_FAIL,
   "LHM_EVENT_ERRIND_NOK"      : LHM_EVENT_ERRIND_NOK,
   "LHM_EVENT_REGREQ_OK"       : LHM_EVENT_REGREQ_OK,
   "LHM_EVENT_REGREQ_NOK"      :  LHM_EVENT_REGREQ_NOK,
   "LHM_EVENT_REGRESP_OK"      :   LHM_EVENT_REGRESP_OK,
   "LHM_EVENT_REGRESP_NOK"     : LHM_EVENT_REGRESP_NOK,
   "LHM_EVENT_DEREGREQ_OK"     :   LHM_EVENT_DEREGREQ_OK,
   "LHM_EVENT_DEREGREQ_NOK"    :    LHM_EVENT_DEREGREQ_NOK,
   "LHM_EVENT_TIMEOUT"         : LHM_EVENT_TIMEOUT,
   "LHM_EVENT_LI_STA_CFM"      :LHM_EVENT_LI_STA_CFM,
   "LHM_SAP_CFG"               : LHM_SAP_CFG,
   "LHM_SAP_ISBOUND"           : LHM_SAP_ISBOUND,
   "LHM_SAP_BINDING"           : LHM_SAP_BINDING,
   "LHM_SAP_UBND"              : LHM_SAP_UBND,

   "EG_NORMAL_DATA_TUNN"       : EG_NORMAL_DATA_TUNN,
   "EG_FWD_DATA_TUNN"          : EG_FWD_DATA_TUNN,

   #For RLC and PDCP L2 Measurement
   "LKW_CAUSE_RB_DELETION"      : LKW_CAUSE_RB_DELETION,
   "LKW_CAUSE_INVALID_MEASTYPE" : LKW_CAUSE_INVALID_MEASTYPE,
   "LKW_CAUSE_EXCEED_NUMMEAS"   : LKW_CAUSE_EXCEED_NUMMEAS,
   "LKW_CAUSE_INVALID_NUMQCI"   : LKW_CAUSE_INVALID_NUMQCI,
   "LKW_CAUSE_ZERO_NUMSAM"      : LKW_CAUSE_ZERO_NUMSAM,
   "LKW_CAUSE_INVALID_NUMSAM"   : LKW_CAUSE_INVALID_NUMSAM,
   "LKW_CAUSE_INVALID_UE"       : LKW_CAUSE_INVALID_UE,
   "LKW_CAUSE_INVALID_QCI"      : LKW_CAUSE_INVALID_QCI,
   "LKW_CAUSE_MEAS_ALREADY_ENA" : LKW_CAUSE_MEAS_ALREADY_ENA,
   "LPJ_CAUSE_MEM_FAILED"       : LPJ_CAUSE_MEM_FAILED,
   "LPJ_CAUSE_INVALID_MEASTYPE" : LPJ_CAUSE_INVALID_MEASTYPE,
   "LPJ_CAUSE_EXCEED_MEASREQ"   : LPJ_CAUSE_EXCEED_MEASREQ,
   "LPJ_CAUSE_EXCEED_NUMQCI"    : LPJ_CAUSE_EXCEED_NUMQCI,
   "LPJ_CAUSE_MEAS_ALREADY_ENA" : LPJ_CAUSE_MEAS_ALREADY_ENA,
   "LPJ_CAUSE_INVALID_QCI"      : LPJ_CAUSE_INVALID_QCI,
   "LPJ_CAUSE_ZERO_MEASPERIOD" :  LPJ_CAUSE_ZERO_MEASPERIOD,
#cm_xta_py_py_001.main_37 - Added support for SPS
   "RGR_SPS_E2" : RGR_SPS_E2,
   "RGR_SPS_E3" : RGR_SPS_E3,
   "RGR_SPS_E4" : RGR_SPS_E4,
   "RGR_SPS_E8" : RGR_SPS_E8,
   "RGR_SPS_PRD_10SF" : RGR_SPS_PRD_10SF,
   "RGR_SPS_PRD_20SF" : RGR_SPS_PRD_20SF,
   "RGR_SPS_PRD_32SF" : RGR_SPS_PRD_32SF,
   "RGR_SPS_PRD_40SF" : RGR_SPS_PRD_40SF,
   "RGR_SPS_PRD_64SF" : RGR_SPS_PRD_64SF,
   "RGR_SPS_PRD_80SF" : RGR_SPS_PRD_80SF,
   "RGR_SPS_PRD_128SF" : RGR_SPS_PRD_128SF,
   "RGR_SPS_PRD_160SF" : RGR_SPS_PRD_160SF,
   "RGR_SPS_PRD_320SF" : RGR_SPS_PRD_320SF,
   "RGR_SPS_PRD_640SF" : RGR_SPS_PRD_640SF,
   "RGR_SPS_PRD_INVALID" : RGR_SPS_PRD_INVALID,
   "RGAC_RGR_UE_TX_ANT_OPENLOOP" : RGAC_RGR_UE_TX_ANT_OPENLOOP,
   "RGAC_RGR_UE_TX_ANT_CLOSEDLOOP" : RGAC_RGR_UE_TX_ANT_CLOSEDLOOP,
   "RGRUE_DLPWRCNTRL_PA_DB_6 " : RGRUE_DLPWRCNTRL_PA_DB_6,
   "RGRUE_DLPWRCNTRL_PA_DB_4DOT77 " : RGRUE_DLPWRCNTRL_PA_DB_4DOT77,
   "RGRUE_DLPWRCNTRL_PA_DB_3 " : RGRUE_DLPWRCNTRL_PA_DB_3,
   "RGRUE_DLPWRCNTRL_PA_DB_1DOT77 " : RGRUE_DLPWRCNTRL_PA_DB_1DOT77,
   "RGRUE_DLPWRCNTRL_PA_DB0 " : RGRUE_DLPWRCNTRL_PA_DB0,
   "RGRUE_DLPWRCNTRL_PA_DB1 " : RGRUE_DLPWRCNTRL_PA_DB1,
   "RGRUE_DLPWRCNTRL_PA_DB2 " : RGRUE_DLPWRCNTRL_PA_DB2,
   "RGRUE_DLPWRCNTRL_PA_DB3 " : RGRUE_DLPWRCNTRL_PA_DB3,

   "RGR_REL_8" : RGR_REL_8,
   "RGR_REL_9" : RGR_REL_9,
   "RGR_REL_10" : RGR_REL_10,
   "RGR_REL_SPARE_5" : RGR_REL_SPARE_5,
   "RGR_REL_SPARE_4" : RGR_REL_SPARE_4,
   "RGR_REL_SPARE_3" : RGR_REL_SPARE_3,
   "RGR_REL_SPARE_2" : RGR_REL_SPARE_2,
   "RGR_REL_SPARE_1" : RGR_REL_SPARE_1,

#Support for RRM XTA

      "RMU_CAUSE_CELLID_UNKNOWN" :       RMU_CAUSE_CELLID_UNKNOWN,     
      "RMU_CAUSE_MMEID_UNKNOWN" :       RMU_CAUSE_MMEID_UNKNOWN,      
      "RMU_CAUSE_UEID_UNKNOWN" :       RMU_CAUSE_UEID_UNKNOWN,      
      "RMU_CAUSE_OUT_OF_RESOURCE" :     RMU_CAUSE_OUT_OF_RESOURCE,    
      "RMU_CAUSE_MAX_UE_REACHED" :     RMU_CAUSE_MAX_UE_REACHED,     
      "RMU_CAUSE_CELL_ALREADY_EXISTS" : RMU_CAUSE_CELL_ALREADY_EXISTS,
      "RMU_CAUSE_MME_ALREADY_EXISTS" :  RMU_CAUSE_MME_ALREADY_EXISTS, 
      "RMU_CAUSE_ENB_ALREADY_UP" :      RMU_CAUSE_ENB_ALREADY_UP,
      "RMU_CAUSE_NOT_APP" :             RMU_CAUSE_NOT_APP,
      "RMU_CAUSE_OTHER" :              RMU_CAUSE_OTHER,  
      "RMU_FAILURE" :                  RMU_FAILURE, 
      "RMU_SUCCESS" :                  RMU_SUCCESS, 
      "RMU_REDIRECT" :                  RMU_REDIRECT,
      "RMU_EST_CAUSE_EMERGENCY" :            RMU_EST_CAUSE_EMERGENCY,
      "RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS" :  RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS,
      "RMU_EST_CAUSE_MT_ACCESS" :            RMU_EST_CAUSE_MT_ACCESS, 
      "RMU_EST_CAUSE_MO_SIGNALLING" :        RMU_EST_CAUSE_MO_SIGNALLING, 
      "RMU_EST_CAUSE_MO_DATA" :              RMU_EST_CAUSE_MO_DATA, 
      "RMU_EST_CAUSE_DELAY_TOLERANT" :       RMU_EST_CAUSE_DELAY_TOLERANT, 
      "RMU_MME_REJECT_MODATA" :              RMU_MME_REJECT_MODATA,
      "RMU_MME_REJECT_MOSIG_MODATA" :        RMU_MME_REJECT_MOSIG_MODATA,
      "RMU_MME_PERMITONLY_EMG_MTACCESS" :    RMU_MME_PERMITONLY_EMG_MTACCESS,
      "RMU_MME_PERMITONLY_HIGHPRI_MTACCESS" : RMU_MME_PERMITONLY_HIGHPRI_MTACCESS,
      "RMU_MME_OVLD_STATUS_NORMAL" :         RMU_MME_OVLD_STATUS_NORMAL,
      "RMU_MME_PERMITONLY_EMG_MTACCESS" :    RMU_MME_PERMITONLY_EMG_MTACCESS,
      "RMU_MME_REJECT_DELAY_TOLERNT_ACCESS" : RMU_MME_REJECT_DELAY_TOLERNT_ACCESS,
      "RMU_FSM_STATUS_MME" :                 RMU_FSM_STATUS_MME,  
      "RMU_FSM_STATUS_ENB" :                 RMU_FSM_STATUS_ENB,  
      "RMU_ENB_STATE_UP" :                  RMU_ENB_STATE_UP,   
      "RMU_ENB_STATE_DOWN" :                RMU_ENB_STATE_DOWN,
      "RMU_MME_STATUS_UP" :                  RMU_MME_STATUS_UP,   
      "RMU_MME_STATUS_DOWN" :                RMU_MME_STATUS_DOWN,
      "RMU_ACBTIME_S4" :		RMU_ACBTIME_S4,
      "RMU_ACBTIME_S8" : 		RMU_ACBTIME_S8,
   "RMU_ACBFACTOR_P00" :   RMU_ACBFACTOR_P00,
   "RMU_ACBFACTOR_P05" :   RMU_ACBFACTOR_P05,
   "RMU_ACBFACTOR_P10" :   RMU_ACBFACTOR_P10,
   "RMU_ACBFACTOR_P15" :   RMU_ACBFACTOR_P15,
   "RMU_ACBFACTOR_P20" :   RMU_ACBFACTOR_P20,
   "RMU_ACBFACTOR_P25" :   RMU_ACBFACTOR_P25,
   "RMU_ACBFACTOR_P30" :   RMU_ACBFACTOR_P30,
   "RMU_ACBFACTOR_P40" :   RMU_ACBFACTOR_P40,
   "RMU_ACBFACTOR_P50" :   RMU_ACBFACTOR_P50,
   "RMU_ACBFACTOR_P60" :   RMU_ACBFACTOR_P60,
   "RMU_ACBFACTOR_P70" :   RMU_ACBFACTOR_P70,
   "RMU_ACBFACTOR_P75" :   RMU_ACBFACTOR_P75,
   "RMU_ACBFACTOR_P80" :   RMU_ACBFACTOR_P80,
   "RMU_ACBFACTOR_P85" :   RMU_ACBFACTOR_P85,
   "RMU_ACBFACTOR_P90" :   RMU_ACBFACTOR_P90,
   "RMU_ACBFACTOR_P95" :   RMU_ACBFACTOR_P95,
   "RMU_ACBFACTOR_NA"  :   RMU_ACBFACTOR_NA,
	"RMU_ACBTIME_S16" :		RMU_ACBTIME_S16,
	"RMU_ACBTIME_S32" : 		RMU_ACBTIME_S32,
	"RMU_ACBTIME_S64" :		RMU_ACBTIME_S64,
	"RMU_ACBTIME_S128" :		RMU_ACBTIME_S128,
	"RMU_ACBTIME_S256" :		RMU_ACBTIME_S256,
	"RMU_ACBTIME_S512" :		RMU_ACBTIME_S512,
	"RMU_PCQI_FMT_WIDEBAND" :	RMU_PCQI_FMT_WIDEBAND,
	"RMU_PCQI_FMT_SUBBAND" :	RMU_PCQI_FMT_SUBBAND,
	"RMU_CQI_MODE10" :		RMU_CQI_MODE10,
	"RMU_CQI_MODE11" :		RMU_CQI_MODE11,
	"RMU_CQI_MODE20" :		RMU_CQI_MODE20,
	"RMU_CQI_MODE21" :		RMU_CQI_MODE21,
   "RMU_ADD_ERAB" :        RMU_ADD_ERAB,
   "RMU_MOD_ERAB" :        RMU_MOD_ERAB,
   "RMU_DEL_ERAB" :        RMU_DEL_ERAB,
   "RMU_ACCESS_STRATUM_REL8" :  RMU_ACCESS_STRATUM_REL8,
   "RMU_ACCESS_STRATUM_REL9" :  RMU_ACCESS_STRATUM_REL9,
   "RMU_ACCESS_STRATUM_REL9HIGHER" : RMU_ACCESS_STRATUM_REL9HIGHER,  
   "RMU_SPS_E2"              : RMU_SPS_E2,
   "RMU_SPS_E3"              : RMU_SPS_E3,
   "RMU_SPS_E4"              : RMU_SPS_E4,
   "RMU_SPS_E8"              : RMU_SPS_E8,
   "RMU_SPS_INTERVAL_E10"    : RMU_SPS_INTERVAL_E10,
   "RMU_SPS_INTERVAL_E20"    : RMU_SPS_INTERVAL_E20,
   "RMU_SPS_INTERVAL_E32"    : RMU_SPS_INTERVAL_E32,
   "RMU_SPS_INTERVAL_E40"    : RMU_SPS_INTERVAL_E40,
   "RMU_SPS_INTERVAL_E64"    : RMU_SPS_INTERVAL_E64,
   "RMU_SPS_INTERVAL_E80"    : RMU_SPS_INTERVAL_E80,
   "RMU_SPS_INTERVAL_E128"    : RMU_SPS_INTERVAL_E128,
   "RMU_SPS_INTERVAL_E160"    : RMU_SPS_INTERVAL_E160,
   "RMU_SPS_INTERVAL_E320"    : RMU_SPS_INTERVAL_E320,
   "RMU_SPS_INTERVAL_E640"    : RMU_SPS_INTERVAL_E640,
   "RM_RCM_MAC_MAIN_CFG" :    RM_RCM_MAC_MAIN_CFG,
   "RM_RCM_PHY_DED_RES_CFG" : RM_RCM_PHY_DED_RES_CFG,
   "RM_RCM_MAC_PHY_CFG" :     RM_RCM_MAC_PHY_CFG,

   "RMU_CAUSE_REDUCE_LOAD_IN_SERV_CELL" : RMU_CAUSE_REDUCE_LOAD_IN_SERV_CELL,  
   "RMU_CAUSE_CELL_NOTAVAILABLE" :  RMU_CAUSE_CELL_NOTAVAILABLE,
   "RMU_CAUSE_SUCC_HANDOVER" :   RMU_CAUSE_SUCC_HANDOVER,
   "RMU_CAUSE_REL_EUTRAN_REASON" : RMU_CAUSE_REL_EUTRAN_REASON,
   "RMU_CAUSE_HANDOVER_CANCELLED" : RMU_CAUSE_HANDOVER_CANCELLED,
   "RMU_HO_TYPE_IntraLTE" :   RMU_HO_TYPE_IntraLTE,
   "RMU_HO_TYPE_LTEtoUTRAN" : RMU_HO_TYPE_LTEtoUTRAN,
   "RMU_HO_TYPE_LTEtoGERAN" : RMU_HO_TYPE_LTEtoGERAN,  
   "RMU_HO_TYPE_UTRANtoLTE" : RMU_HO_TYPE_UTRANtoLTE,  
   "RMU_HO_TYPE_GERANtoLTE" : RMU_HO_TYPE_GERANtoLTE,
   "RMU_HO_TYPE_S1" :   RMU_HO_TYPE_S1,
   "RMU_HO_TYPE_X2" :   RMU_HO_TYPE_X2,
   "LRM_SEL_LWLC" :   LRM_SEL_LWLC,
   "LRM_SEL_TC" :   LRM_SEL_TC,
	"LRM_CFG_ADD" :			LRM_CFG_ADD,
	"LRM_CFG_MOD" :			LRM_CFG_MOD,
	"LRM_CFG_DEL" :			LRM_CFG_DEL,
	"LRM_BANDWIDTH_6" :		LRM_BANDWIDTH_6,
	"LRM_BANDWIDTH_15" :		LRM_BANDWIDTH_15,
	"LRM_BANDWIDTH_25" :		LRM_BANDWIDTH_25,
	"LRM_BANDWIDTH_50" :		LRM_BANDWIDTH_50,
	"LRM_BANDWIDTH_75" :		LRM_BANDWIDTH_75,
	"LRM_BANDWIDTH_100" :		LRM_BANDWIDTH_100,
	"LRM_BANDWIDTH_MAX" :		LRM_BANDWIDTH_MAX,
	"LRM_ENB_CONFIG" :		LRM_ENB_CONFIG,
	"LRM_CELL_CONFIG" :		LRM_CELL_CONFIG,

   "LRM_SPL_SF_CONFIG_0" : LRM_SPL_SF_CONFIG_0,
   "LRM_SPL_SF_CONFIG_1" : LRM_SPL_SF_CONFIG_1,
   "LRM_SPL_SF_CONFIG_2" : LRM_SPL_SF_CONFIG_2,
   "LRM_SPL_SF_CONFIG_3" : LRM_SPL_SF_CONFIG_3,
   "LRM_SPL_SF_CONFIG_4" : LRM_SPL_SF_CONFIG_4,
   "LRM_SPL_SF_CONFIG_5" : LRM_SPL_SF_CONFIG_5,
   "LRM_SPL_SF_CONFIG_6" : LRM_SPL_SF_CONFIG_6,
   "LRM_SPL_SF_CONFIG_7" : LRM_SPL_SF_CONFIG_7,
   "LRM_SPL_SF_CONFIG_8" : LRM_SPL_SF_CONFIG_8,

   "LRM_UL_DL_CONFIG_0" : LRM_UL_DL_CONFIG_0,
   "LRM_UL_DL_CONFIG_1" : LRM_UL_DL_CONFIG_1,
   "LRM_UL_DL_CONFIG_2" : LRM_UL_DL_CONFIG_2,
   "LRM_UL_DL_CONFIG_3" : LRM_UL_DL_CONFIG_3,
   "LRM_UL_DL_CONFIG_4" : LRM_UL_DL_CONFIG_4,
   "LRM_UL_DL_CONFIG_5" : LRM_UL_DL_CONFIG_5,
   "LRM_UL_DL_CONFIG_6" : LRM_UL_DL_CONFIG_6,

   "LRM_SR_PRDCTY_5"  : LRM_SR_PRDCTY_5, 
   "LRM_SR_PRDCTY_10" : LRM_SR_PRDCTY_10, 
   "LRM_SR_PRDCTY_20" : LRM_SR_PRDCTY_20, 
   "LRM_SR_PRDCTY_40" : LRM_SR_PRDCTY_40, 
   "LRM_SR_PRDCTY_80" : LRM_SR_PRDCTY_80, 
   "LRM_SR_PRDCTY_2"  : LRM_SR_PRDCTY_2, 
   "LRM_SR_PRDCTY_1"  : LRM_SR_PRDCTY_1, 

   "LRM_CQI_PRDCTY_1" : LRM_CQI_PRDCTY_1,
   "LRM_CQI_PRDCTY_2" : LRM_CQI_PRDCTY_2,
   "LRM_CQI_PRDCTY_5" : LRM_CQI_PRDCTY_5,
   "LRM_CQI_PRDCTY_10" : LRM_CQI_PRDCTY_10,
   "LRM_CQI_PRDCTY_20" : LRM_CQI_PRDCTY_20,
   "LRM_CQI_PRDCTY_40" : LRM_CQI_PRDCTY_40,
   "LRM_CQI_PRDCTY_80" : LRM_CQI_PRDCTY_80,
   "LRM_CQI_PRDCTY_160" : LRM_CQI_PRDCTY_160,
   "LRM_CQI_PRDCTY_32" : LRM_CQI_PRDCTY_32,
   "LRM_CQI_PRDCTY_64" : LRM_CQI_PRDCTY_64,
   "LRM_CQI_PRDCTY_128" : LRM_CQI_PRDCTY_128 ,

   "DSR_TRANS_N4" : DSR_TRANS_N4, 
   "DSR_TRANS_N8" : DSR_TRANS_N8, 
   "DSR_TRANS_N16" : DSR_TRANS_N16,
   "DSR_TRANS_N32" : DSR_TRANS_N32,
   "DSR_TRANS_N64" : DSR_TRANS_N64,
   "KPI_ID_LTE_RRC_ATTCONESTAB_EMERGENCY"  : KPI_ID_LTE_RRC_ATTCONESTAB_EMERGENCY,
   "KPI_ID_LTE_RRC_ATTCONESTAB_HIGHPRIORITYACCES "  : KPI_ID_LTE_RRC_ATTCONESTAB_HIGHPRIORITYACCES ,
   "KPI_ID_LTE_RRC_ATTCONESTAB_MTACCESS" : KPI_ID_LTE_RRC_ATTCONESTAB_MTACCESS,
   "KPI_ID_LTE_RRC_ATTCONESTAB_SUM" : KPI_ID_LTE_RRC_ATTCONESTAB_SUM,
   "KPI_ID_LTE_RRC_SUCCCONESTAB_EMERGENCY" : KPI_ID_LTE_RRC_SUCCCONESTAB_EMERGENCY,
   "KPI_ID_LTE_RRC_ATTCONESTAB_MOSIGNALLING" : KPI_ID_LTE_RRC_ATTCONESTAB_MOSIGNALLING,
   "KPI_ID_LTE_RRC_ATTCONESTAB_MODATA"      : KPI_ID_LTE_RRC_ATTCONESTAB_MODATA,
   "KPI_ID_LTE_RRC_FAILCONESTAB_EMERGENCY"  : KPI_ID_LTE_RRC_FAILCONESTAB_EMERGENCY,
   "KPI_ID_LTE_RRC_SUCCCONESTAB_MODATA"     : KPI_ID_LTE_RRC_SUCCCONESTAB_MODATA,
   "KPI_ID_LTE_RRC_SUCCCONESTAB_MTACCESS"   : KPI_ID_LTE_RRC_SUCCCONESTAB_MTACCESS,
   "KPI_ID_LTE_RRC_SUCCCONESTAB_MOSIGNALLING" : KPI_ID_LTE_RRC_SUCCCONESTAB_MOSIGNALLING,
   "KPI_ID_LTE_RRC_ATTCONESTAB_DE_TO_ACCESS":KPI_ID_LTE_RRC_ATTCONESTAB_DE_TO_ACCESS,
   "KPI_ID_LTE_RRC_SUCCCONESTAB_DE_TO_ACCESS":KPI_ID_LTE_RRC_SUCCCONESTAB_DE_TO_ACCESS,
   "KPI_ID_LTE_RRC_FAILCONESTAB_DE_TO_ACCESS":KPI_ID_LTE_RRC_FAILCONESTAB_DE_TO_ACCESS,
   "KPI_ID_LTE_HO_TOENBATT_SUM"         : KPI_ID_LTE_HO_TOENBATT_SUM,
   "KPI_ID_LTE_HO_TOENBSUCC_SUM"        : KPI_ID_LTE_HO_TOENBSUCC_SUM,
   "KPI_ID_LTE_HO_S1_BASED_HANDOUT_SUCC_SUM" : KPI_ID_LTE_HO_S1_BASED_HANDOUT_SUCC_SUM,
   "KPI_ID_LTE_HO_TOENBFAIL_SUM"        : KPI_ID_LTE_HO_TOENBFAIL_SUM,
   "KPI_ID_LTE_HO_FROMENBATT_SUM"       : KPI_ID_LTE_HO_FROMENBATT_SUM,
   "KPI_ID_LTE_HO_FROMENBSUCC_SUM"      : KPI_ID_LTE_HO_FROMENBSUCC_SUM,
   "KPI_ID_LTE_HO_FROMENBFAIL_SUM"      : KPI_ID_LTE_HO_FROMENBFAIL_SUM,
   "KPI_ID_LTE_HO_S1_BASED_HANDIN_SUCC_SUM" : KPI_ID_LTE_HO_S1_BASED_HANDIN_SUCC_SUM,
   "KPI_ID_LTE_HO_INTERENBOUTPREPATT"   : KPI_ID_LTE_HO_INTERENBOUTPREPATT,
   "KPI_ID_LTE_HO_INTRAFREQOUTATT"      : KPI_ID_LTE_HO_INTRAFREQOUTATT,
   "KPI_ID_LTE_HO_INTRAFREQOUTSUCC"     : KPI_ID_LTE_HO_INTRAFREQOUTSUCC,
   "KPI_ID_LTE_HO_INTERFREQMEASGAPOUTATT" : KPI_ID_LTE_HO_INTERFREQMEASGAPOUTATT,
   "KPI_ID_LTE_HO_INTERFREQMEASGAPOUTSUCC" : KPI_ID_LTE_HO_INTERFREQMEASGAPOUTSUCC,
   "KPI_ID_LTE_HO_NODRXOUTATT"             : KPI_ID_LTE_HO_NODRXOUTATT,
   "KPI_ID_LTE_HO_NODRXOUTSUCC"            : KPI_ID_LTE_HO_NODRXOUTSUCC,
   "KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_CAUSE1" : KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_CAUSE1,
   "KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_CAUSE1" : KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_CAUSE1,
   "KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_CAUSE1_PER_TGT_CELL" : KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_CAUSE1_PER_TGT_CELL,
   "KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_SUM_PER_TGT_CELL" : KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_ATT_SUM_PER_TGT_CELL,
   "KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_CAUSE1_PER_TGT_CELL" : KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_CAUSE1_PER_TGT_CELL,
   "KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_SUM_PER_TGT_CELL"    : KPI_ID_LTE_OUT_INTER_ENB_HO_EXE_SUCC_SUM_PER_TGT_CELL,
   "KPI_ID_LTE_INTER_RAT_UTRA_ATT_SUM"  : KPI_ID_LTE_INTER_RAT_UTRA_ATT_SUM,
   "KPI_ID_LTE_INTER_RAT_UTRA_SUCC_SUM" : KPI_ID_LTE_INTER_RAT_UTRA_SUCC_SUM,
   "KPI_ID_LTE_INTER_RAT_UTRA_FAIL_SUM" : KPI_ID_LTE_INTER_RAT_UTRA_FAIL_SUM,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE1" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE1,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE2" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE2,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE3" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE3,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE4" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_ATT_CAUSE4,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE1" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE1,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE2" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE2,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE3" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE3,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE4" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_SUCC_CAUSE4,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE1" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE1,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE2" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE2,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE3" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE3,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE4" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_HO_EXE_FAIL_CAUSE4,
   "KPI_ID_LTE_RIM_PROC_ATT"  : KPI_ID_LTE_RIM_PROC_ATT,
   "KPI_ID_LTE_RIM_PROC_SUCC" : KPI_ID_LTE_RIM_PROC_SUCC,
   "KPI_ID_LTE_RIM_PROC_FAIL" : KPI_ID_LTE_RIM_PROC_FAIL,
   "KPI_ID_LTE_CSFB_ATT_SUM" : KPI_ID_LTE_CSFB_ATT_SUM,
   "KPI_ID_LTE_CSFB_SUCC_SUM" : KPI_ID_LTE_CSFB_SUCC_SUM,
   "KPI_ID_LTE_CSFB_FAIL_SUM" : KPI_ID_LTE_CSFB_FAIL_SUM,
   "KPI_ID_LTE_CSFB_UTRA_ATT_SUM" : KPI_ID_LTE_CSFB_UTRA_ATT_SUM,
   "KPI_ID_LTE_CSFB_UTRA_SUCC_SUM" : KPI_ID_LTE_CSFB_UTRA_SUCC_SUM,
   "KPI_ID_LTE_CSFB_UTRA_FAIL_SUM" : KPI_ID_LTE_CSFB_UTRA_FAIL_SUM,
   "KPI_ID_LTE_CSFB_UTRA_WITH_REDIR_WITH_SI" : KPI_ID_LTE_CSFB_UTRA_WITH_REDIR_WITH_SI,
   "KPI_ID_LTE_CSFB_UTRA_WITHOUT_REDIR" : KPI_ID_LTE_CSFB_UTRA_WITHOUT_REDIR,
   "KPI_ID_LTE_CSFB_CDMA2000_DUALRX_WO_REDIR" : KPI_ID_LTE_CSFB_CDMA2000_DUALRX_WO_REDIR,
   "KPI_ID_LTE_CSFB_CDMA2000_REDIR" : KPI_ID_LTE_CSFB_CDMA2000_REDIR,
   "KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_SUCC" : KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_SUCC,
   "KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_FAIL" : KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_FAIL,
   "KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_ATT" : KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_ATT,
   "KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_FAIL_REDIR_SUCC" : KPI_ID_LTE_CSFB_CDMA2000_WO_PSHO_FAIL_REDIR_SUCC,
   "KPI_ID_LTE_CSFB_GERAN_ATT_SUM"    : KPI_ID_LTE_CSFB_GERAN_ATT_SUM,
   "KPI_ID_LTE_CSFB_GERAN_SUCC_SUM"   : KPI_ID_LTE_CSFB_GERAN_SUCC_SUM,
   "KPI_ID_LTE_CSFB_GERAN_REDIR"      : KPI_ID_LTE_CSFB_GERAN_REDIR,
   "KPI_ID_LTE_CSFB_GERAN_CCO"        : KPI_ID_LTE_CSFB_GERAN_CCO,
   "KPI_ID_LTE_CSFB_GERAN_FAIL"       : KPI_ID_LTE_CSFB_GERAN_FAIL,
   "KPI_ID_LTE_IRAT_MOB_LAI_1"  : KPI_ID_LTE_IRAT_MOB_LAI_1,
   "KPI_ID_LTE_IRAT_MOB_LAI_2"  : KPI_ID_LTE_IRAT_MOB_LAI_2,
   "KPI_ID_LTE_IRAT_MOB_LAI_3"  : KPI_ID_LTE_IRAT_MOB_LAI_3,
   "KPI_ID_LTE_IRAT_MOB_LAI_4"  : KPI_ID_LTE_IRAT_MOB_LAI_4,
   "KPI_ID_LTE_IRAT_MOB_LAI_5"  : KPI_ID_LTE_IRAT_MOB_LAI_5,
   "KPI_ID_LTE_IRAT_MOB_LAI_6"  : KPI_ID_LTE_IRAT_MOB_LAI_6,
   "KPI_ID_LTE_IRAT_MOB_LAI_7"  : KPI_ID_LTE_IRAT_MOB_LAI_7,
   "KPI_ID_LTE_IRAT_MOB_LAI_8"  : KPI_ID_LTE_IRAT_MOB_LAI_8,
   "KPI_ID_LTE_IRAT_MOB_LAI_9"  : KPI_ID_LTE_IRAT_MOB_LAI_9,
   "KPI_ID_LTE_IRAT_MOB_LAI_10"  : KPI_ID_LTE_IRAT_MOB_LAI_10,
   "KPI_ID_LTE_IRAT_MOB_LAI_11"  : KPI_ID_LTE_IRAT_MOB_LAI_11,
   "KPI_ID_LTE_IRAT_MOB_LAI_12"  : KPI_ID_LTE_IRAT_MOB_LAI_12,
   "KPI_ID_LTE_IRAT_MOB_LAI_13"  : KPI_ID_LTE_IRAT_MOB_LAI_13,
   "KPI_ID_LTE_IRAT_MOB_LAI_14"  : KPI_ID_LTE_IRAT_MOB_LAI_14,
   "KPI_ID_LTE_IRAT_MOB_LAI_15"  : KPI_ID_LTE_IRAT_MOB_LAI_15,
   "KPI_ID_LTE_IRAT_MOB_LAI_16"  : KPI_ID_LTE_IRAT_MOB_LAI_16,
   "KPI_ID_LTE_IRAT_MOB_LAI_17"  : KPI_ID_LTE_IRAT_MOB_LAI_17,
   "KPI_ID_LTE_IRAT_MOB_LAI_18"  : KPI_ID_LTE_IRAT_MOB_LAI_18,
   "KPI_ID_LTE_IRAT_MOB_LAI_19"  : KPI_ID_LTE_IRAT_MOB_LAI_19,
   "KPI_ID_LTE_IRAT_MOB_LAI_20"  : KPI_ID_LTE_IRAT_MOB_LAI_20,
   "KPI_ID_LTE_IRAT_MOB_LAI_21"  : KPI_ID_LTE_IRAT_MOB_LAI_21,
   "KPI_ID_LTE_IRAT_MOB_LAI_22"  : KPI_ID_LTE_IRAT_MOB_LAI_22,
   "KPI_ID_LTE_IRAT_MOB_LAI_23"  : KPI_ID_LTE_IRAT_MOB_LAI_23,
   "KPI_ID_LTE_IRAT_MOB_LAI_24"  : KPI_ID_LTE_IRAT_MOB_LAI_24,
   "KPI_ID_LTE_IRAT_MOB_LAI_25"  : KPI_ID_LTE_IRAT_MOB_LAI_25,
   "KPI_ID_LTE_IRAT_MOB_LAI_26"  : KPI_ID_LTE_IRAT_MOB_LAI_26,
   "KPI_ID_LTE_IRAT_MOB_LAI_27"  : KPI_ID_LTE_IRAT_MOB_LAI_27,
   "KPI_ID_LTE_IRAT_MOB_LAI_28"  : KPI_ID_LTE_IRAT_MOB_LAI_28,
   "KPI_ID_LTE_IRAT_MOB_LAI_29"  : KPI_ID_LTE_IRAT_MOB_LAI_29,
   "KPI_ID_LTE_IRAT_MOB_LAI_30"  : KPI_ID_LTE_IRAT_MOB_LAI_30,
   "KPI_ID_LTE_IRAT_MOB_LAI_31"  : KPI_ID_LTE_IRAT_MOB_LAI_31,
   "KPI_ID_LTE_IRAT_MOB_LAI_32"  : KPI_ID_LTE_IRAT_MOB_LAI_32,
   "KPI_ID_LTE_IRAT_MOB_LAI_OTH" : KPI_ID_LTE_IRAT_MOB_LAI_OTH,
   "KPI_ID_LTE_CSFB_GERAN_CCO_WITH_NACC" : KPI_ID_LTE_CSFB_GERAN_CCO_WITH_NACC,
   "KPI_ID_LTE_CSFB_GERAN_REDIR_WITH_SI" : KPI_ID_LTE_CSFB_GERAN_REDIR_WITH_SI,
   "KPI_ID_LTE_HO_FROMENBSUCC_SUM_AFTR_REEST" : KPI_ID_LTE_HO_FROMENBSUCC_SUM_AFTR_REEST,
   "KPI_ID_LTE_CSFB_CDMA2000_DUALRXTX_REDIR" : KPI_ID_LTE_CSFB_CDMA2000_DUALRXTX_REDIR,
   "KPI_ID_LTE_CSFB_CDMA2000_DUALRXTX_DLNAS" : KPI_ID_LTE_CSFB_CDMA2000_DUALRXTX_DLNAS,
   "KPI_ID_LTE_HO_FROMENB_FULL_RECFG":KPI_ID_LTE_HO_FROMENB_FULL_RECFG,
   "KPI_ID_LTE_RRC_CONNREESTAB_FULL_RECFG":KPI_ID_LTE_RRC_CONNREESTAB_FULL_RECFG,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_ATT_SUM" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_ATT_SUM,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_SUCC_SUM" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_SUCC_SUM,
   "KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_FAIL_SUM" : KPI_ID_LTE_OUT_INTER_RAT_UTRA_SRVCC_FAIL_SUM,
   "KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_ATT_SUM" : KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_ATT_SUM,
   "KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_SUCC_SUM" : KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_SUCC_SUM,
   "KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_FAIL_SUM" : KPI_ID_LTE_OUT_INTER_RAT_GERAN_SRVCC_FAIL_SUM,

   #MultiCell
   "LWR_TRANSID_GEN":LWR_TRANSID_GEN,
   "LWR_TRANSID_CTF":LWR_TRANSID_CTF,
   "LWR_TRANSID_NHU":LWR_TRANSID_NHU,
   "LWR_TRANSID_PJU":LWR_TRANSID_PJU,
   "LWR_TRANSID_EGT":LWR_TRANSID_EGT,
   "LWR_TRANSID_SZT":LWR_TRANSID_SZT,
   "LWR_TRANSID_CZT":LWR_TRANSID_CZT,
   "LWR_TRANSID_RGR":LWR_TRANSID_RGR,
   "LWR_TRANSID_ENBCFG":LWR_TRANSID_ENBCFG,
   "LWR_TRANSID_CELLCFG":LWR_TRANSID_CELLCFG,
   "LWR_TRANSID_MME":LWR_TRANSID_MME,
   "LWR_TRANSID_NHCFG":LWR_TRANSID_NHCFG,
   "LWR_TRANSID_NREUTRAN":LWR_TRANSID_NREUTRAN,
   "LWR_TRANSID_NRUTRAN":LWR_TRANSID_NRUTRAN,
   "LWR_TRANSID_NHCELLCFG":LWR_TRANSID_NHCELLCFG,
   "LWR_TRANSID_NHUTRAN_CELLCFG":LWR_TRANSID_NHUTRAN_CELLCFG,
   "LWR_TRANSID_INTER_NHCELLCFG":LWR_TRANSID_INTER_NHCELLCFG,
   "LWR_TRANSID_CDMA1XRTT_BAND":LWR_TRANSID_CDMA1XRTT_BAND,
   "LWR_TRANSID_CDMA1XRTT_FREQ":LWR_TRANSID_CDMA1XRTT_FREQ,
   "LWR_TRANSID_CDMAHRPD_CLASS":LWR_TRANSID_CDMAHRPD_CLASS,
   "LWR_TRANSID_CDMAHRPD_FREQ":LWR_TRANSID_CDMAHRPD_FREQ,
   "LWR_TRANSID_RMU":LWR_TRANSID_RMU,
   "LWR_TRANSID_MME_DYN_ADDCFG":LWR_TRANSID_MME_DYN_ADDCFG,
   "LWR_TRANSID_MME_DYN_DELCFG":LWR_TRANSID_MME_DYN_DELCFG,
   "LWR_TRANSID_ADD_NGHCELL_MEAS":LWR_TRANSID_ADD_NGHCELL_MEAS,
   "LWR_TRANSID_CDMA1XRTT_CELL":LWR_TRANSID_CDMA1XRTT_CELL,
   "LWR_TRANSID_GERAN_FREQ":LWR_TRANSID_GERAN_FREQ,
   "LWR_TRANSID_GERAN_CELL":LWR_TRANSID_GERAN_CELL,
   "LWR_TRANSID_NLU":LWR_TRANSID_NLU,

   #RRC Event Types
   "C4_CSFBPARAMSRSPCDMA2000" : C4_CSFBPARAMSRSPCDMA2000,
   "C4_DLINFOTFR" : C4_DLINFOTFR,
   "C4_HANDOVERFROMEUTRAPREPRQST" : C4_HANDOVERFROMEUTRAPREPRQST,
   "C4_MOBILITYFROMEUTRACMD" : C4_MOBILITYFROMEUTRACMD,
   "C4_RRCCONRECFGN" : C4_RRCCONRECFGN,
   "C4_RRCCONRLS" : C4_RRCCONRLS,
   "C4_SECURITYMODECMD" : C4_SECURITYMODECMD,
   "C4_UECAPENQUIRY" : C4_UECAPENQUIRY,
   "C4_COUNTERCHECK" : C4_COUNTERCHECK,
   "C4_UEINFORQST_R9" : C4_UEINFORQST_R9,
   "C4_LOGGEDMEASUREMENTCFG_R10" : C4_LOGGEDMEASUREMENTCFG_R10,
   "C4_RNRECFGN_R10" : C4_RNRECFGN_R10,

#CA Changes
   "RG_SCH_UCI_FORMAT1A_1B" : RG_SCH_UCI_FORMAT1A_1B,
   "RG_SCH_UCI_FORMAT1B_CS" : RG_SCH_UCI_FORMAT1B_CS,
   "RG_SCH_UCI_FORMAT3" : RG_SCH_UCI_FORMAT3,
   "RG_SCH_UCI_FORMAT_NON_CA" : RG_SCH_UCI_FORMAT_NON_CA,
   "RGR_SCELLRELEASE" : RGR_SCELLRELEASE,
   "RGR_SCELLADD" : RGR_SCELLADD,
   "RGR_SCELLACT" : RGR_SCELLACT,
   "RGR_SCELLDEACT" : RGR_SCELLDEACT

   }

   if genDef.has_key(key) :
      return genDef[key]
   elif flagDef.has_key(key) :
      return flagDef[key]
   elif entityDef.has_key(key) :
      return entityDef[key]
   else :
      return None


#
#       Fun:   sctgetMsgId
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def sctgetMsgId(node) :
   '''Return the attribute value of  defined by type'''

   # Init the return values
   idVal = [0, 0, 0, 0, 0]

   # Check for the presence of the attribute
   if node.hasAttribute('dstid') :
      val = node.getAttribute('dstid')
      if entityDef.has_key(val) :
         idVal[1] = entityDef[val]

   # Check for the presence of the attribute
   if node.hasAttribute('srcid') :
      val = node.getAttribute('srcid')
      if entityDef.has_key(val) :
         idVal[0] = entityDef[val]

   # Check for the presence of the attribute
   if node.hasAttribute('connid') :

      # Split on dot
      idValList = node.getAttribute('cid').split('.')

      cnt = 2
      for val in idValList :
         idVal[cnt] = int(val[1:])
         cnt = cnt + 1

   return idVal


#
#       Fun:   getMsgId
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getMsgId(node) :
   '''Return the attribute value of  defined by type'''

   # Init the return values
   idVal = [0, 0, 0, 0, 0]

   # Check for the presence of the attribute
   if node.hasAttribute('dstid') :
      val = node.getAttribute('dstid')
      if entityDef.has_key(val) :
         idVal[1] = entityDef[val]

   # Check for the presence of the attribute
   if node.hasAttribute('srcid') :
      val = node.getAttribute('srcid')
      if entityDef.has_key(val) :
         idVal[0] = entityDef[val]

   # Check for the presence of the attribute
   if node.hasAttribute('cid') :

      # Split on dot
      idValList = node.getAttribute('cid').split('.')

      cnt = 2
      for val in idValList :
         idVal[cnt] = int(val[1:])
         cnt = cnt + 1

   return idVal

#
#       Fun:   getRouteList
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getRouteList(node ,attr) :
   '''Return the attribute value of  defined by type'''

   # Init the return values
   idVal = []

   # Check for the presence of the attribute
   if node.hasAttribute(attr) :

      # Split on dot
      idValList = node.getAttribute(attr).split('.')

      for val in idValList :
         if entityDef.has_key(val) :
            idVal.append(entityDef[val])
         else :
            print 'Invalid Entity', val

   return idVal

#
#       Fun:   getExtHdrList
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getExtHdrList(node, verbatim = 0) :
   '''Return the attribute value of  defined by type'''

   hdrList    = ''
   body       = ''
   body2       = ''
   reqUriLine = ''
   entList1   = []
   entList2   = []

   cnt = 0
   if verbatim == 0 :
      if node.hasChildNodes() :
         for node in node.childNodes :
            if node.nodeType == xml.dom.Node.CDATA_SECTION_NODE :

               # The first CDATA is the reqUri and the ext headers
               if cnt == 0 :
                  hdrList = str(node.data)

                  patt = re.compile(r'DUA\d|UA\d|PRX\d|SFP\d|SLP\d|CSP\d|SIPENT\d')

                  rePatt = re.compile(r'\(\?P=(\w+)\)')

                  def regFun1 (matchObj) :
                     if entityDef.has_key(matchObj.group(0)) :
                        entList1.append(entityDef[matchObj.group(0)])
                        return '%s'

                  def regFun2 (matchObj) :
                     if entityDef.has_key(matchObj.group(0)) :
                        entList2.append(entityDef[matchObj.group(0)])
                        return '%s'

                  def regFun3 (matchObj) :
                     # Skip the preceding and postfix for the regex (?P=\w+)
                     if reList.has_key(matchObj.group(1)) :
                        return reList[matchObj.group(1)]

                  hdrList = re.sub('\s*\n\s*', '\r\n', hdrList)

                  # Remove extra space and newlines at the beginning
                  # hdrList.strip()
                  hdrList = re.sub('^\s*', '', hdrList)

                  # Find if there is a req URI given
                  hdrLines = hdrList.splitlines()

                  # Check if request/response line present
                  if len(hdrLines) > 0 and  hdrLines[0].find(r'SIP/2.0') != -1  and \
                     hdrLines[0].find(r'Via') == -1 :
                     reqUriLine = hdrLines[0] + '\r\n'
                     hdrLines = hdrLines[1:]

                  hdrList = ''

                  for hdr in hdrLines :
                     # Check if have to pass verbatim
                     if re.match(r"'''", hdr) :
                        # Strip first three and last three characters
                        hdrList = hdrList + hdr[3:-3]
                     else :
                        hdrList = hdrList + '\r\n' + hdr

                  hdrList = hdrList + '\r\n'

                  # Remove extra space and newlines at the beginning
                  hdrList = re.sub('^\s*', '', hdrList)

                  # Lets do a entity substitution 
                  while patt.search(reqUriLine) :
                    reqUriLine = patt.sub(regFun1, reqUriLine)

                  while patt.search(hdrList) :
                    hdrList = patt.sub(regFun2, hdrList)

                  while rePatt.search(reqUriLine) :
                    reqUriLine = rePatt.sub(regFun3, reqUriLine)

                  while rePatt.search(hdrList) :
                    hdrList = rePatt.sub(regFun3, hdrList)

               elif cnt == 1 :
                  # Body part
                  body = str(node.data)

#                  body = re.sub('\s*\n\s*', '\r\n', body)

                  # Remove extra space and newlines at the beginning
                  body.strip()
                  #body = re.sub('^\s*', '', body)

                  # Find if there is a req URI given
                  bodyLines = body.splitlines()

                  body = ''

                  for line in bodyLines :
                     body = body + '\r\n' + line

#                  body = body + '\r\n\r\n'

                  # Remove extra space and newlines at the beginning
                  body = re.sub('^\s*', '', body)

               elif cnt == 2 :
                  # Body part
                  body2 = str(node.data)

#                  body = re.sub('\s*\n\s*', '\r\n', body)

                  # Remove extra space and newlines at the beginning
                  body2.strip()
                  #body = re.sub('^\s*', '', body)

                  # Find if there is a req URI given
                  bodyLines = body2.splitlines()

                  body2 = ''

                  for line in bodyLines :
                     body2 = body2 + '\r\n' + line

#                  body = body + '\r\n\r\n'

                  # Remove extra space and newlines at the beginning
                  body2 = re.sub('^\s*', '', body2)

               cnt = cnt + 1
               if cnt == 3 :
                  break

   else :
      if node.hasChildNodes() :
         for node in node.childNodes :
            if node.nodeType == xml.dom.Node.CDATA_SECTION_NODE :

               hdrList = str(node.data)

               patt = re.compile(r'DUA\d|UA\d|PRX\d|SFP\d|SLP\d|CSP\d|SIPENT\d')

               rePatt = re.compile(r'\(\?P=(\w+)\)')

               def regFun1 (matchObj) :
                  if entityDef.has_key(matchObj.group(0)) :
                     entList1.append(entityDef[matchObj.group(0)])
                     return '%s'

               def regFun2 (matchObj) :
                  if entityDef.has_key(matchObj.group(0)) :
                     entList2.append(entityDef[matchObj.group(0)])
                     return '%s'

               def regFun3 (matchObj) :
                  # Skip the preceding and postfix for the regex (?P=\w+)
                  if reList.has_key(matchObj.group(1)) :
                     return reList[matchObj.group(1)]

               hdrList = re.sub('\s*\n\s*', '\r\n', hdrList)

               # Remove extra space and newlines at the beginning
               # hdrList.strip()
               hdrList = re.sub('^\s*', '', hdrList)

               # Find if there is a req URI given
               hdrLines = hdrList.splitlines()

               hdrList = ''

               for hdr in hdrLines :
                  # Check if have to pass verbatim
                  if re.match(r"'''", hdr) :
                     hdr = re.sub(r'\\r', '\r', hdr)
                     hdr = re.sub(r'\\n', '\n', hdr)
                     # Strip first three and last three characters
                     hdrList = hdrList + hdr[3:-3]
                  else :
                     hdrList = hdrList + '\r\n' + hdr

               #hdrList = hdrList + '\r\n'

               # Remove extra space and newlines at the beginning
               hdrList = re.sub('^\s*', '', hdrList)

               # Lets do a entity substitution 
               while patt.search(reqUriLine) :
                 reqUriLine = patt.sub(regFun1, reqUriLine)

               while patt.search(hdrList) :
                 hdrList = patt.sub(regFun2, hdrList)

               while rePatt.search(reqUriLine) :
                 reqUriLine = rePatt.sub(regFun3, reqUriLine)

               while rePatt.search(hdrList) :
                 hdrList = rePatt.sub(regFun3, hdrList)


   return [entList1, reqUriLine, entList2, hdrList, body, body2]

#
#       Fun:   getValList
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getValList(node, type, sep, attrib) :
   '''Return the attribute value of  defined by type'''

   ATTRIB_TYPE_INT = 1
   ATTRIB_TYPE_TXT = 2
   ATTRIB_TYPE_ENUM = 3
   ATTRIB_TYPE_S16 = 4
   ATTRIB_TYPE_ENUM_U8 =    5
   ATTRIB_TYPE_ENUM_U32 =   6
   ATTRIB_TYPE_U8 =   7
   ATTRIB_TYPE_U32 =   8
   ATTRIB_TYPE_ENUM_U16  =   9
   ATTRIB_TYPE_FLAG =  10
   ATTRIB_TYPE_BOOL =  11

#cm_xta_py_py_001.main_50 : Added hash as a delimiter for diameter 1.3 release.
   SEP_TYPE_COLON = 1
   SEP_TYPE_DOT   = 2
   SEP_TYPE_HASH  = 3

   sepDef = {
      SEP_TYPE_COLON : ":",
      SEP_TYPE_DOT   : ".",
      SEP_TYPE_HASH  : "#",
   }

   mapFun = {
               ATTRIB_TYPE_INT : int,
               ATTRIB_TYPE_TXT : str,
               ATTRIB_TYPE_ENUM : getValDict,
               ATTRIB_TYPE_ENUM_U8 : getValDict,
               ATTRIB_TYPE_ENUM_U32 : getValDict,
               ATTRIB_TYPE_FLAG : getFlagDict,
               ATTRIB_TYPE_S16 : int,
               ATTRIB_TYPE_U8  : int,
               ATTRIB_TYPE_U32 : int,
               ATTRIB_TYPE_BOOL : getValDict,
               ATTRIB_TYPE_ENUM_U16 : getValDict,
            }

   if not mapFun.has_key(type) :
      return None


   retList = []
   # Get the corresponding string value
   if sepDef.has_key(sep) :
      sep = sepDef[sep]
   else :
      sep = '.'

   # Check for the presence of the attribute
   if (node.hasAttribute(attrib)) :
      totVal = str(node.getAttribute(attrib))
      valList = totVal.split(sep)

      for val in valList :
         retList.append(mapFun[type](val))

   return retList


#
#       Fun:   getVal
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getVal(node, type, attrib) :
   '''Return the attribute value of  defined by type'''

   ATTRIB_TYPE_INT = 1
   ATTRIB_TYPE_TXT = 2
   ATTRIB_TYPE_ENUM = 3
   ATTRIB_TYPE_S16 = 4
   ATTRIB_TYPE_ENUM_U8 =    5
   ATTRIB_TYPE_ENUM_U32 =   6
   ATTRIB_TYPE_U8   =   7
   ATTRIB_TYPE_U32  =   8
   ATTRIB_TYPE_ENUM_U16  =   9
   ATTRIB_TYPE_FLAG =  10
   ATTRIB_TYPE_BOOL =  11


   mapFun = {
               ATTRIB_TYPE_INT : int,
               ATTRIB_TYPE_TXT : str,
               ATTRIB_TYPE_ENUM : getValDict,
               ATTRIB_TYPE_S16 : int,
               ATTRIB_TYPE_ENUM_U8 : getValDict,
               ATTRIB_TYPE_ENUM_U32 : getValDict,
               ATTRIB_TYPE_U8  : int,
               ATTRIB_TYPE_U32 : int,
               ATTRIB_TYPE_ENUM_U16 : getValDict,
               ATTRIB_TYPE_FLAG : getFlagDict,
               ATTRIB_TYPE_BOOL : getValDict,
            }

   # Check for the presence of the attribute
   if node.hasAttribute(attrib) :
      if mapFun.has_key(type) :
         return mapFun[type](node.getAttribute(attrib))

   return None


#
#       Fun:   firstChildOfType
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def firstChildOfType(node, type = xml.dom.Node.ELEMENT_NODE) :
   '''Return the first child of type defined by type'''

   tmpNode = None 

   if node.hasChildNodes() :
      for node in node.childNodes :
         if node.nodeType == type :
            tmpNode = node
            break

   return tmpNode


#
#       Fun:   getTagName
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getTagName(node) :
   '''Return the next sibling of type defined by type'''

   if hasattr(node, 'tagName') :
      return str(node.tagName)

   return None

#

#
#       Fun:   nextSiblingOfType
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def nextSiblingOfType(node, type = xml.dom.Node.ELEMENT_NODE) :
   '''Return the next sibling of type defined by type'''

   tmpNode = node.nextSibling

   while (tmpNode != None) :
      if (tmpNode.nodeType == type) :
         break

      tmpNode = tmpNode.nextSibling


   return tmpNode

#
#
#       Fun:   updateTestCaseForAPI
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def updateTestCaseForAPI(xmlNode) :
   '''Parse the XML files as test case'''

   entityDef = {
      '1' : 'SLP',
      '2' : 'CSP',
      '3' : 'TSP',
   }

   sfpEntityDef = {
      '1' : 'CSP',
      '2' : 'CSP',
      '3' : 'TSP',
   }

   sipEntityDef = {
      '1' : 'SLP',
      '2' : 'CSP',
      '3' : 'TSP',
      '4' : 'UA',
   }
   # Get the tapa.send Nodes
   sendNode = xmlNode.getElementsByTagName('tapa.send')

   for node in sendNode :
      if node.hasChildNodes() :
         for childNode in node.childNodes :
            if childNode.nodeType == xml.dom.Node.ELEMENT_NODE :
               cmdName = str(childNode.tagName)

               # Check if a SIP Response Sending Command
               if childNode.hasAttribute('rspcode'):
                  rspCode = int(childNode.getAttribute('rspcode'))
               else:
                  rspCode = 700

               if rspCode < 200 :
                  cmdName = cmdName + '_P'

               # Check if SIP command
               if cmdMappingDef.has_key(cmdName) :
                  # SIP command

                  # Update the eventType attribute if not present
                  childNode.attributes['eventType'] = cmdMappingDef[cmdName][0]

                  # Update the eventType attribute if not present
                  childNode.attributes['sipMsgType'] = cmdMappingDef[cmdName][1]

                  # Find the source entity and update the tagName
                  # Check for the presence of the attribute
                  if childNode.hasAttribute('srcid') :
                     # Split on dot
                     srcEnt = childNode.getAttribute('srcid')
                  else :
                     srcEnt = 'UA1'

                  # Update source entity PRX according to the environment
                  # variable
                  if srcEnt[0:3] == 'PRX' :
                     # Set the default value based on proxyType 
                     # Default is CSP, my choice
                     srcEnt = entityDef[str(proxyType)] + srcEnt[3:]

                     if os.environ.has_key('PROXYTYPE') :
                        srcEnt = entityDef[os.environ['PROXYTYPE']] + srcEnt[3:]

                  if srcEnt[0:3] == 'SFP' :
                     #Default is CSP
                     srcEnt = sfpEntityDef[str(proxyType)] + srcEnt[3:]

                  if srcEnt[0:6] == 'SIPENT' :
                     #Default is UA
                     srcEnt = sipEntityDef[str(proxyType)] + srcEnt[6:]

                  sendDef = cmdMappingDef[cmdName][2]

                  # Now check the type 
                  if sendDef.has_key(srcEnt[:2]) :
                     childNode.tagName = sendDef[srcEnt[:2]]
                  elif sendDef.has_key(srcEnt[:3]) :
                     childNode.tagName = sendDef[srcEnt[:3]]

   # Get the tapa.expect Nodes
   expNode = xmlNode.getElementsByTagName('tapa.expect') + \
             xmlNode.getElementsByTagName('tapa.expset') + \
             xmlNode.getElementsByTagName('tapa.expopt')

   for node in expNode :
      if node.hasChildNodes() :
         for childNode in node.childNodes :
            if childNode.nodeType == xml.dom.Node.ELEMENT_NODE :
               cmdName = str(childNode.tagName)

               # Check if a SIP Response Sending Command
               if childNode.hasAttribute('rspcode'):
                  rspCode = int(childNode.getAttribute('rspcode'))
               else:
                  rspCode = 700

               if rspCode < 200:
                  cmdName = cmdName+'_P'

               # Check if SIP command
               if cmdMappingDef.has_key(cmdName) :
                  # SIP command

                  # Update the eventType attribute if not present
                  childNode.attributes['eventType'] = cmdMappingDef[cmdName][0]

                  # Update the eventType attribute if not present
                  childNode.attributes['sipMsgType'] = cmdMappingDef[cmdName][1]

                  # Find the source entity and update the tagName
                  # Check for the presence of the attribute
                  if childNode.hasAttribute('srcid') :
                     # Split on dot
                     srcEnt = childNode.getAttribute('srcid')
                  else :
                     srcEnt = 'UA1'

                  # Update source entity PRX according to the environment
                  # variable
                  if srcEnt[0:3] == 'PRX' :
                     # Set the default value based on proxyType 
                     # Default is CSP, my choice
                     srcEnt = entityDef[str(proxyType)] + srcEnt[3:]

                     if os.environ.has_key('PROXYTYPE') :
                        srcEnt = entityDef[os.environ['PROXYTYPE']] + srcEnt[3:]

                  if srcEnt[0:3] == 'SFP' :
                     #Default is CSP
                     srcEnt = sfpEntityDef[str(proxyType)] + srcEnt[3:]

                  if srcEnt[0:6] == 'SIPENT' :
                     #Default is UA
                     srcEnt = sipEntityDef[str(proxyType)] + srcEnt[6:]

                  expDef = cmdMappingDef[cmdName][3]

                  # Now check the type 
                  if expDef.has_key(srcEnt[:2]) :
                     childNode.tagName = expDef[srcEnt[:2]]
                  elif expDef.has_key(srcEnt[:3]) :
                     childNode.tagName = expDef[srcEnt[:3]]

   # Get the tapa.expect Nodes
   reNode = xmlNode.getElementsByTagName('tapa.re')
   for node in reNode :
      if node.hasChildNodes() :
         for childNode in node.childNodes :
            if childNode.nodeType == xml.dom.Node.CDATA_SECTION_NODE :
               reData = childNode.data

               # Remove extra space and newlines at the beginning
               # reData.strip()
               reData = re.sub('^\s*', '', reData)

               # Remove extra space and newlines at the end
               # reData.strip()
               reData = re.sub('\s*$', '', reData)

               # Remove begin and end quotes
               node.attributes['re'] = reData[1:-1]


   return None

#
#
#       Fun:   parseTestCase
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def parseTestCase(testCase = None, tcId = None, tcDict = None) :
   '''Parse the XML files as test case'''

   if testCase == None :
      testCase = tcDict[tcId][3]

   xmlDoc = xml.dom.minidom.parseString(testCase)

   # Validate the test case conforms to the TC syntax
   # notation
   if validateTestCase(xmlDoc) == False :
      return None

   # Update SIP Messages to SOT APIs
   if updTCForAPI == True :
      updateTestCaseForAPI(xmlDoc)

   # Get the tapa.testcase Entity Node
   tcNode = xmlDoc.getElementsByTagName('tapa.testcase')[0]

   # Get the tapa.doc Entity Node
   docNode = tcNode.getElementsByTagName('tapa.doc')[0]

   # Get the tapa.require Entity Node
   reqNode = tcNode.getElementsByTagName('tapa.require')[0]

   # Get the tapa.cfg Entity Node
   cfgNode = tcNode.getElementsByTagName('tapa.cfg')[0]
   cfgFirstChildNode = None

   if cfgNode.hasChildNodes() :
      for node in cfgNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            cfgFirstChildNode = node
            break

   # Get the tapa.test Entity Node
   testNodeList = tcNode.getElementsByTagName('tapa.test')

   if testNodeList.length == 0 :
      testNode = tcNode.getElementsByTagName('tapa.load')[0]
   else :
      testNode = testNodeList[0]

   testFirstChildNode = None

   if testNode.hasChildNodes() :
      for node in testNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            testFirstChildNode = node
            break

   # Get the tapa.cln Entity Node
   clnNode = tcNode.getElementsByTagName('tapa.clean')[0]
   clnFirstChildNode = None

   if clnNode.hasChildNodes() :
      for node in clnNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            clnFirstChildNode = node
            break

   # Get the tapa.shutdown Entity Node
   stNode = tcNode.getElementsByTagName('tapa.shutdown')[0]
   stFirstChildNode = None

   if stNode.hasChildNodes() :
      for node in stNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            stFirstChildNode = node
            break

   return [xmlDoc, tcNode, docNode, reqNode, cfgNode, cfgFirstChildNode,
           testNode, testFirstChildNode, clnNode, clnFirstChildNode,
           stNode, stFirstChildNode]


#
#       Fun:   isLeaf
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def isLeaf(topNode) :
   '''Validate in recursive manner that all the childNodes are only leaf node'''

   # Find all the steps under the top Node
   for node in topNode.childNodes :
      # Skip anything except ELEMENT_NODE
      if node.nodeType != node.ELEMENT_NODE :
         continue

      # Get the tagName for the step
      cmdName = str(node.tagName)

      # Check if compound command
      if compCmdDict.has_key(cmdName) :
         # Compound command inside simple command, flag error
         return False

      elif simCmdDict.has_key(cmdName) :
         # Internal command, an internal command can
         # have only simple commands, call itself
         # recursively to validate the same
         if isLeaf(node) == False :
            return False

      elif intCmdDict.has_key(cmdName) :
         # Internal command, an internal command can
         # have only simple commands, call itself
         # recursively to validate the same
         if isLeaf(node) == False :
            return False

      else :
         # Unknown command, return False
         return False

   return True

#
#       Fun:   validateTestCase
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def validateTestCase(xmlDoc) :
   '''Validate the XML Doc Node for test case syntax compliance'''

   # Get the tapa.testcase Entity Node
   tcNode = xmlDoc.getElementsByTagName('tapa.testcase')
   if (tcNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.testcase section not found\n')
      return False
   elif (tcNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.testcase sections found\n')
      return False

   tcNode = tcNode[0]

   tcSection = {
      'tapa.doc'        : "",
      'tapa.require'    : "",
      'tapa.cfg'        : "",
      'tapa.doc'        : "",
      'tapa.cfg'        : "",
      'tapa.test'       : "",
      'tapa.load'       : "",
      'tapa.clean'      : "",
      'tapa.shutdown'   : "",
      'tapa.attribute'  : "",
   }

   # Check for any invalid XML tags in the test group
   if tcNode.hasChildNodes() :
      for node in tcNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            # Get the tagName for the step
            cmdName = str(node.tagName)

            if not tcSection.has_key(cmdName) :
               raise xml.dom.SyntaxErr ('Invalid section found: ' + cmdName + '\n')
               return False
         elif node.nodeType == node.COMMENT_NODE :
               print node.toxml()
               #raise xml.dom.SyntaxErr ('WARNING', ': *** STEPS COMMENTED HERE ***')
               print 'WARNING', ': *** STEPS COMMENTED HERE ***'
               return False


   # Get the tapa.doc Entity Node
   docNode = tcNode.getElementsByTagName('tapa.doc')
   if (docNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.doc section not found\n')
      return False
   elif (docNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.doc sections found\n')
      return False
   else :
      docNode = docNode[0]

      if validateDocSection(docNode) == False :
         return False

      if docNode.getElementsByTagName('tapa.rfc').length == 0 :
         raise xml.dom.SyntaxErr ('tapa.rfc section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.module').length == 0:
         raise xml.dom.SyntaxErr ('tapa.module section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.desc').length == 0:
         raise xml.dom.SyntaxErr ('tapa.desc section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.desc').length > 1:
         raise xml.dom.SyntaxErr ('extra tapa.desc section found\n')
         return False
      elif docNode.getElementsByTagName('tapa.longdesc').length == 0:
         raise xml.dom.SyntaxErr ('tapa.longdesc section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.longdesc').length > 1:
         raise xml.dom.SyntaxErr ('extra tapa.longdesc section found\n')
         return False

   # Get the tapa.require Entity Node
   reqNode = tcNode.getElementsByTagName('tapa.require')
   if (reqNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.require section not found\n')
      return False
   elif (reqNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.require section found\n')
      return False
   else :
      reqNode = reqNode[0]

      if validatePreSection(reqNode) == False :
         return False

      if reqNode.getElementsByTagName('tapa.ifdef').length == 0 :
         raise xml.dom.SyntaxErr ('tapa.ifdef section not found\n')
         return False
      if reqNode.getElementsByTagName('tapa.ifdef').length > 1 :
         raise xml.dom.SyntaxErr ('extra tapa.ifdef section found\n')
         return False
      elif reqNode.getElementsByTagName('tapa.ifndef').length == 0:
         raise xml.dom.SyntaxErr ('tapa.ifndef section not found\n')
         return False
      elif reqNode.getElementsByTagName('tapa.ifndef').length > 1:
         raise xml.dom.SyntaxErr ('extra tapa.ifndef section found\n')
         return False
      elif reqNode.getElementsByTagName('tapa.mode').length == 0:
         raise xml.dom.SyntaxErr ('tapa.mode section not found\n')
      # Get the TC mode
      # For simplicity, we are assuming that only mode tag is present
      elif not reqNode.getElementsByTagName('tapa.mode')[0].hasAttribute('mode') :
         raise xml.dom.SyntaxErr ('tapa.mode mode attribute not found\n')
         return False
      else :
         tmp = validatePre(reqNode)

   # Get the tapa.cfg Entity Node
   cfgNode = tcNode.getElementsByTagName('tapa.cfg')
   if (cfgNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.cfg section not found\n')
      return False
   elif (cfgNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.cfg section found\n')
      return False

   # Get the tapa.test Entity Node
   testNode = tcNode.getElementsByTagName('tapa.test')
   loadNode = tcNode.getElementsByTagName('tapa.load')
   if testNode.length == 0 and loadNode.length == 0 :
      raise xml.dom.SyntaxErr ('tapa.test|tapa.load section not found\n')
      return False
   elif (testNode.length > 1) or (loadNode.length > 1):
      raise xml.dom.SyntaxErr ('extra tapa.test|tapa.load section found\n')
      return False
   elif (testNode.length == 1) and (loadNode.length == 1):
      raise xml.dom.SyntaxErr ('both tapa.test|tapa.load section found\n')
      return False

   if testNode.length == 0 :
      testNode = loadNode

   # Get the tapa.cln Entity Node
   clnNode = tcNode.getElementsByTagName('tapa.clean')
   if (clnNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.clean section not found\n')
      return False
   elif (clnNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.clean section found\n')
      return False

   # Get the tapa.shutdown Entity Node
   stNode = tcNode.getElementsByTagName('tapa.shutdown')
   if (stNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.shutdown section not found\n')
      return False
   elif (stNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.shutdown section found\n')
      return False

   # Validate each and every step
   topNodeList = [cfgNode[0], testNode[0], clnNode[0], stNode[0]]

   for topNode in topNodeList :
      # Find all the steps under the top Node
      for node in topNode.childNodes :
         # Skip anything except ELEMENT_NODE
         if node.nodeType != node.ELEMENT_NODE :
            continue

         # Get the tagName for the step
         cmdName = str(node.tagName)

         subSteps = []

         # Check if compound command
         if compCmdDict.has_key(cmdName) :
            # Compound command, move ahead
            continue

         elif intCmdDict.has_key(cmdName) :
            # Internal command, an internal command can
            # have only simple commands, call itself
            # recursively to validate the same
            if isLeaf(node) == False :

               dbgPrnt('Error Node Starts')
               dbgPrnt('-----------------')
               xmlStr =  node.toxml()
               dbgPrnt(xmlStr)
               dbgPrnt('Error Node Ends')
               dbgPrnt('---------------')

               raise xml.dom.SyntaxErr (cmdName + ': Not a simple command inside internal command\n')
               return False
         else :
            # Unknown command, return False
            raise xml.dom.SyntaxErr (cmdName + ': Unknown command\n')
            return False

   #for topNode in topNodeList :
   #   if validateAttr(topNode) == False :
   #      # Unknown attribute, return False
   #      raise xml.dom.SyntaxErr (cmdName + ': Unknown attribute\n')
   #      return False

   #dbgPrnt('Validation passed')
   return True


#
#       Fun:   parseTestGroup
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def parseTestGroup(testGroup = None, tgId = None, tgDict = None) :
   '''Parse the XML files as test group'''

   if testGroup == None :
      testGroup = tgDict[tgId][2]

   xmlDoc = xml.dom.minidom.parseString(testGroup)

   # Validate the test group conforms to the TG syntax
   # notation
   if validateTestGroup(xmlDoc) == False :
      return None

   # Get the tapa.testcase Entity Node
   tcNode = xmlDoc.getElementsByTagName('tapa.testgroup')[0]

   # Get the tapa.doc Entity Node
   docNode = tcNode.getElementsByTagName('tapa.doc')[0]

   # Get the tapa.require Entity Node
   reqNode = tcNode.getElementsByTagName('tapa.require')[0]

   # Get the tapa.cfg Entity Node
   cfgNode = tcNode.getElementsByTagName('tapa.cfg')[0]
   cfgFirstChildNode = None

   if cfgNode.hasChildNodes() :
      for node in cfgNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            cfgFirstChildNode = node
            break

   # Get the tapa.shutdown Entity Node
   stNode = tcNode.getElementsByTagName('tapa.shutdown')[0]
   stFirstChildNode = None

   if stNode.hasChildNodes() :
      for node in stNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            stFirstChildNode = node
            break

   return [xmlDoc, tcNode, docNode, reqNode, cfgNode, cfgFirstChildNode, 
           stNode, stFirstChildNode]


#
#       Fun:   validatePreSection
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def validatePreSection(preNode) :
   '''Validate the XML Doc Node for test case syntax compliance'''

   preSection = {
      'tapa.ifdef'      : "",
      'tapa.ifndef'     : "",
      'tapa.mode'       : "",
   }

   # Check for any invalid XML tags in the test group
   if preNode.hasChildNodes() :
      for node in preNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            # Get the tagName for the step
            cmdName = str(node.tagName)

            if not preSection.has_key(cmdName) :
               raise xml.dom.SyntaxErr ('Invalid prerequiste in tapa.require: ' + cmdName)
               return False
         elif node.nodeType == node.COMMENT_NODE :
               print node.toxml()
               #raise xml.dom.SyntaxErr ('WARNING', ': *** STEPS COMMENTED HERE ***')
               print 'WARNING', ': *** STEPS COMMENTED HERE ***'
               return False


   return True


#
#       Fun:   validateDocSection
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def validateDocSection(docNode, type = None) :
   '''Validate the XML Doc Node for test case syntax compliance'''

   if type == 'cmd' :
      docSection = {
         'tapa.desc'       : "",
         'tapa.longdesc'   : "",
      }
   else :
      docSection = {
         'tapa.rfc'        : "",
         'tapa.module'     : "",
         'tapa.desc'       : "",
         'tapa.longdesc'   : "",
      }

   # Check for any invalid XML tags in the test group
   if docNode.hasChildNodes() :
      for node in docNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            # Get the tagName for the step
            cmdName = str(node.tagName)

            if not docSection.has_key(cmdName) :
               raise xml.dom.SyntaxErr ('Invalid tag in tapa.doc: ' + cmdName)
               return False
         elif node.nodeType == node.COMMENT_NODE :
               print node.toxml()
               #raise xml.dom.SyntaxErr ('WARNING', ': *** STEPS COMMENTED HERE ***')
               print 'WARNING', ': *** STEPS COMMENTED HERE ***'
               return False

   return True


#
#       Fun:   validateTestGroup
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def validateTestGroup(xmlDoc) :
   '''Validate the XML Doc Node for test case syntax compliance'''

   # Get the tapa.testGroup Entity Node
   tcNode = xmlDoc.getElementsByTagName('tapa.testgroup')
   if (tcNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.testgroup section not found\n')
      return False
   elif (tcNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.testgroup sections found\n')
      return False

   tcNode = tcNode[0]

   tgSection = {
      'tapa.doc'        : "",
      'tapa.require'    : "",
      'tapa.cfg'        : "",
      'tapa.doc'        : "",
      'tapa.cfg'        : "",
      'tapa.shutdown'   : "",
   }

   # Check for any invalid XML tags in the test group
   if tcNode.hasChildNodes() :
      for node in tcNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            # Get the tagName for the step
            cmdName = str(node.tagName)

            if not tgSection.has_key(cmdName) :
               raise xml.dom.SyntaxErr ('Invalid section found: ' + cmdName + '\n')
               return False
         elif node.nodeType == node.COMMENT_NODE :
               print node.toxml()
               #raise xml.dom.SyntaxErr ('WARNING', ': *** STEPS COMMENTED HERE ***')
               print 'WARNING', ': *** STEPS COMMENTED HERE ***'
               return False

   # Get the tapa.doc Entity Node
   docNode = tcNode.getElementsByTagName('tapa.doc')

   if (docNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.doc section not found\n')
      return False
   elif (docNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.doc sections found\n')
      return False
   else :
      docNode = docNode[0]

      if validateDocSection(docNode) == False :
         return False

      if docNode.getElementsByTagName('tapa.rfc').length == 0 :
         raise xml.dom.SyntaxErr ('tapa.rfc section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.module').length == 0:
         raise xml.dom.SyntaxErr ('tapa.module section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.desc').length == 0:
         raise xml.dom.SyntaxErr ('tapa.desc section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.desc').length > 1:
         raise xml.dom.SyntaxErr ('extra tapa.desc section found\n')
         return False
      elif docNode.getElementsByTagName('tapa.longdesc').length == 0:
         raise xml.dom.SyntaxErr ('tapa.longdesc section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.longdesc').length > 1:
         raise xml.dom.SyntaxErr ('extra tapa.longdesc section found\n')
         return False


   # Get the tapa.require Entity Node
   reqNode = tcNode.getElementsByTagName('tapa.require')
   if (reqNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.require section not found\n')
      return False
   elif (reqNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.require section found\n')
      return False
   else :
      reqNode = reqNode[0]

      if validatePreSection(reqNode) == False :
         return False

      if reqNode.getElementsByTagName('tapa.ifdef').length == 0 :
         raise xml.dom.SyntaxErr ('tapa.ifdef section not found\n')
         return False
      elif reqNode.getElementsByTagName('tapa.ifndef').length == 0:
         raise xml.dom.SyntaxErr ('tapa.ifndef section not found\n')
         return False
      elif reqNode.getElementsByTagName('tapa.mode').length == 0:
         raise xml.dom.SyntaxErr ('tapa.mode section not found\n')
         return False
      # Get the TC mode
      # For simplicity, we are assuming that only mode tag is present
      elif not reqNode.getElementsByTagName('tapa.mode')[0].hasAttribute('mode') :
         raise xml.dom.SyntaxErr ('tapa.mode mode attribute not found\n')
         return False
      else :
         tmp = validatePre(reqNode)

   # Get the tapa.cfg Entity Node
   cfgNode = tcNode.getElementsByTagName('tapa.cfg')
   if (cfgNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.cfg section not found\n')
      return False
   elif (cfgNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.cfg section found\n')
      return False

   # Get the tapa.shutdown Entity Node
   stNode = tcNode.getElementsByTagName('tapa.shutdown')
   if (stNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.shutdown section not found\n')
      return False
   elif (stNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.shutdown section found\n')
      return False

   # Validate each and every step
   topNodeList = [cfgNode[0], stNode[0]]

   for topNode in topNodeList :
      # Find all the steps under the top Node
      for node in topNode.childNodes :
         # Skip anything except ELEMENT_NODE
         if node.nodeType != node.ELEMENT_NODE :
            continue

         # Get the tagName for the step
         cmdName = str(node.tagName)

         subSteps = []

         # Check if compound command
         if compCmdDict.has_key(cmdName) :
            # Compound command, move ahead
            continue

         elif intCmdDict.has_key(cmdName) :
            # Internal command, an internal command can
            # have only simple commands, call itself
            # recursively to validate the same
            if isLeaf(node) == False :

               dbgPrnt('Error Node Starts')
               dbgPrnt('-----------------')
               xmlStr =  node.toxml()
               dbgPrnt(xmlStr)
               dbgPrnt('Error Node Ends')
               dbgPrnt('---------------')

               raise xml.dom.SyntaxErr (cmdName + ': Not a simple command inside internal command\n')
               return False
         else :
            # Unknown command, return False
            raise xml.dom.SyntaxErr (cmdName + ': Unknown command\n')
            return False

   #dbgPrnt('Validation passed')
   return True



#
#       Fun:   parseCommand
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def parseCommand(command, cmdId = None, cmdDict = None) :
   '''Parse the XML files as compound command'''

   if command == None :
      command = cmdDict[cmdId]

   xmlDoc = xml.dom.minidom.parseString(command)

   # Validate the command conforms to the command syntax
   # notation
   if validateCommand(xmlDoc) == False :
      return None

   # Get the tapa.testcase Entity Node
   cmdNode = xmlDoc.getElementsByTagName('tapa.command')[0]

   # Get the tapa.doc Entity Node
   docNode = cmdNode.getElementsByTagName('tapa.doc')[0]

   # Get the tapa.steps Entity Node
   testNode = cmdNode.getElementsByTagName('tapa.steps')[0]

   testFirstChildNode = None
   if testNode.hasChildNodes() :
      for node in testNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            testFirstChildNode = node
            break

   return [xmlDoc, cmdNode, docNode, testNode, testFirstChildNode]


#
#       Fun:   validateCommand
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def validateCommand(xmlDoc) :
   '''Validate the XML Doc Node for command syntax compliance'''

   # Get the tapa.command Entity Node
   tcNode = xmlDoc.getElementsByTagName('tapa.command')
   if (tcNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.command section not found\n')
      return False
   elif (tcNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.command sections found\n')
      return False

   tcNode = tcNode[0]

   cmdSection = {
      'tapa.doc'        : "",
      'tapa.steps'      : "",
   }

   # Check for any invalid XML tags in the test group
   if tcNode.hasChildNodes() :
      for node in tcNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            # Get the tagName for the step
            cmdName = str(node.tagName)

            if not cmdSection.has_key(cmdName) :
               raise xml.dom.SyntaxErr ('Invalid section found: ' + cmdName + '\n')
               return False
         elif node.nodeType == node.COMMENT_NODE :
               print node.toxml()
               #raise xml.dom.SyntaxErr ('WARNING', ': *** STEPS COMMENTED HERE ***')
               print 'WARNING', ': *** STEPS COMMENTED HERE ***'
               return False


   # Get the tapa.doc Entity Node
   docNode = tcNode.getElementsByTagName('tapa.doc')
   if (docNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.doc section not found\n')
      return False
   elif (docNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.doc sections found\n')
      return False
   else :
      docNode = docNode[0]

      if validateDocSection(docNode, 'cmd') == False :
         return False

      if docNode.getElementsByTagName('tapa.desc').length == 0:
         raise xml.dom.SyntaxErr ('tapa.desc section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.desc').length > 1:
         raise xml.dom.SyntaxErr ('extra tapa.desc section found\n')
         return False
      elif docNode.getElementsByTagName('tapa.longdesc').length == 0:
         raise xml.dom.SyntaxErr ('tapa.longdesc section not found\n')
         return False
      elif docNode.getElementsByTagName('tapa.longdesc').length > 1:
         raise xml.dom.SyntaxErr ('extra tapa.longdesc section found\n')
         return False

   # Get the tapa.steps Entity Node
   stepsNode = tcNode.getElementsByTagName('tapa.steps')
   if (stepsNode.length == 0) :
      raise xml.dom.SyntaxErr ('tapa.steps section not found\n')
      return False
   elif (stepsNode.length > 1) :
      raise xml.dom.SyntaxErr ('extra tapa.steps section found\n')
      return False

   # We can not validate all steps inside a compound command, because
   # a compound command itself may have more compound commands and 
   # which may not have been parsed by this time

   return True


#
#       Fun:   loadTestGroups
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def loadTestGroups(fileName = None, removeComment = True) :
   '''Parse all the XML files for test groups, removes
      comments from the test case '''

   tcDict = {}

   # Create patterns for later use
   testIdPatt1 = re.compile(r'<tapa.testgroup\s+id="([^"]+)?"')
   testIdPatt2 = re.compile(r"<tapa.testgroup\s+id='([^\']+)?'")
   testIdPatt3 = re.compile(r'<tapa.testgroup\s+id="([^"]+)?"\s+altid="([^"]+)?"')
   testIdPatt4 = re.compile(r"<tapa.testgroup\s+id='([^\']+)?'\s+altid='([^\']+)?")

   commentPatt = re.compile(r'^\s*#.*$', re.M)

   # If no filename given, do all XML files in the directory
   if (fileName == None) :
      fileLst = glob.glob('*.xml')
   else :
      fileLst = [fileName]

   for elm in fileLst :

      # Read XML file
      data = open(elm, "r").read()

      # Extract all instances of the testcases
      tstList = re.findall('<tapa.testgroup\s+id.+?>.+?</tapa.testgroup>', data, re.S)

      # Check if found any
      for tst in tstList :

         if removeComment == True :
            # Remove all # comments from the testgroup
            tst = commentPatt.sub('', tst)

         # Check if altid is present
         if re.search('altid', tst) :
            # Match pattern
            mobj = testIdPatt3.match(tst)

            # Add to list if match found
            if not mobj :
               mobj = testIdPatt4.match(tst)
         else :
            # Match pattern
            mobj = testIdPatt1.match(tst)

            # Add to list if match found
            if not mobj :
               mobj = testIdPatt2.match(tst)

         # Add to list if match found
         if mobj :
            if tcDict.has_key(mobj.group(1)) :
               raise xml.dom.SyntaxErr ('Temp Usage: Testgroup ' + mobj.group(1) + ' already registered')
               return None
            else :
               # Coerce into int, C code expects that
               #tcDict[mobj.group(1)] = tst

               if len(mobj.groups()) == 2 :
                  altid = str(mobj.group(2))
               else :
                  altid = 'None'

               xmlDoc = xml.dom.minidom.parseString(tst)

               # Get the tapa.testcase Entity Node
               tcNode = xmlDoc.getElementsByTagName('tapa.testgroup')[0]

               # Get the tapa.doc Entity Node
               docNode = tcNode.getElementsByTagName('tapa.doc')[0]

               # Get the tapa.require Entity Node
               reqNode = tcNode.getElementsByTagName('tapa.require')[0]

               doc = getTCDoc(docNode, reqNode)[2]

               # Break doc on first newline
               ind = doc.find('\n')

               if ind != - 1 :
                  doc = doc[:ind]

               # Trim doc
               if len(doc) > 65 :
                  doc = doc[:65]

               tcDict[mobj.group(1)] = [int(mobj.group(1)), altid, tst, doc]


   return tcDict

#
#       Fun:   loadTestCases
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def loadTestCases(fileName = None, removeComment = True) :
   '''Parse all the XML files for test cases, removes
      comments from the test case '''

   tcDict = {}

   # Create patterns for later use
   testIdPatt1 = re.compile(r'<tapa.testcase\s+id="([^"]+)?"')
   testIdPatt2 = re.compile(r"<tapa.testcase\s+id='([^\']+)?'")
   testIdPatt3 = re.compile(r"<tapa.testcase\s+id='([^\']+)?'\s+altid='([^\']+)?'")
   testIdPatt4 = re.compile(r'<tapa.testcase\s+id="([^\"]+)?"\s+altid="([^\"]+)?"')

   commentPatt = re.compile(r'^\s*#.*$', re.M)

   # If no filename given, do all XML files in the directory
   if (fileName == None) :
      fileLst = glob.glob('*.xml')
   else :
      fileLst = [fileName]

   for elm in fileLst :

      # Read XML file
      data = open(elm, "r").read()

      # Extract all instances of the testcases
      tstList = re.findall('<tapa.testcase\s+id.+?>.+?</tapa.testcase>', data, re.S)

      # Check if found any
      for tst in tstList :

         if removeComment == True :
            # Remove all # comments from the testcase
            tst = commentPatt.sub('', tst)

         # Check if altid is present
         if re.search('altid', tst) :
            # Match pattern
            mobj = testIdPatt3.match(tst)

            # Add to list if match found
            if not mobj :
               mobj = testIdPatt4.match(tst)
         else :
            # Match pattern
            mobj = testIdPatt1.match(tst)

            # Add to list if match found
            if not mobj :
               mobj = testIdPatt2.match(tst)

         if mobj :
            tcId = mobj.group(1)

            if tcDict.has_key(tcId) :
               raise xml.dom.SyntaxErr ('Temp Usage: Testcase ' + tcId + ' already registered')
               return None
            else :
               # Get groupId and testCase Id
               (tstGrpId, tstId) = tcId.split('.')

               if len(mobj.groups()) == 2 :
                  altid = str(mobj.group(2))
               else :
                  altid = 'None'

               # Coerce into int, C code expects that
               tcDict[tcId] = [int(tstGrpId), int(tstId), altid, tst]

   return tcDict

#
#       Fun:   loadCommands
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def loadCommands(fileName = None, removeComment = True) :
   '''Parse all the XML files for compound commands, removes
      comments from the commands'''

   tcDict = {}

   # Create patterns for later use
   patt1 = re.compile(r'<tapa.command\s+id="(.+)?"')
   patt2 = re.compile(r"<tapa.command\s+id='(.+)?'")

   commentPatt = re.compile(r'^\s*#.*$', re.M)

   # If no filename given, do all XML files in the directory
   if (fileName == None) :
      fileLst = glob.glob('*.xml')
   else :
      fileLst = [fileName]

   for elm in fileLst :

      # Read XML file
      data = open(elm, "r").read()

      # Extract all instances of the testcases
      tstList = re.findall('<tapa.command\s+id.+?>.+?</tapa.command>', data, re.S)

      # Check if found any
      for tst in tstList :
         if removeComment == True :
            # Remove all # comments from the testcase
            tst = commentPatt.sub('', tst)

         # Match pattern
         mobj = patt1.match(tst)

         # Add to list if match found
         if mobj :
            pass
         else :
            mobj = patt2.match(tst)

         # Add to list if match found
         if mobj :
            if tcDict.has_key(mobj.group(1)) :
               raise xml.dom.SyntaxErr ('Temp Usage: Command ' + mobj.group(1) + ' already registered')
               return None
            else :
               tcDict[mobj.group(1)] = tst

   return tcDict

#
#       Fun:   getCompCommands
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getCompCommands() :
   '''Returns the reference to all compound commands loaded from
      cm_xta_pycmd module'''

   compCmdDict = {}

   # Test loadTestCases
   dictList = loadCommands()

   for elm in dictList :
      list = parseCommand(dictList[elm])

      # Get documentation
      docNode = list[2]
      descNode = docNode.getElementsByTagName('tapa.desc')[0]

      # Get command brief description
      doc = str(descNode.childNodes[0].wholeText).strip()
      compCmdDict[elm] = doc

   return compCmdDict

intCmdDict = cm_xta_pycmd.intCmdDict
simCmdDict = cm_xta_pycmd.simpleCmdDict
compCmdDict = getCompCommands()

#
#       Fun:   getInternalCommands
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getInternalCommands() :
   '''Returns the reference to all internal commands loaded from
      cm_xta_pycmd module'''

   return cm_xta_pycmd.intCmdDict


#
#       Fun:   getSimpleCommands
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getSimpleCommands() :
   '''Returns the reference to all simple commands loaded from
      cm_xta_pycmd module'''

   return cm_xta_pycmd.simpleCmdDict


#
#       Fun:   getTCDoc
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getTCDoc(docNode, reqNode) :
   '''Generate the documentation for the step'''

   # For simplicity, we are assuming that only rfc tag is present
   rfcNode = docNode.getElementsByTagName('tapa.rfc')[0]

   rfcAttr = 'None'
   if rfcNode.hasAttribute('id') :
      attr = str(rfcNode.getAttribute('id'))

      if attr != 'None' :
         attrSec = rfcNode.getAttribute('section')

         rfcAttr = attr + '.' + attrSec

   rfcAttr = str(rfcAttr)

   # For simplicity, we are assuming that only module tag is present
   modNode = docNode.getElementsByTagName('tapa.module')[0]

   module = 'None'
   if modNode.hasAttribute('id') :
      module = str(modNode.getAttribute('id'))

   descNode = docNode.getElementsByTagName('tapa.desc')[0]

   # Split document lines
   doc = str(descNode.childNodes[0].wholeText)

   doc = re.sub('^\s+', '', doc)
   doc = re.sub('\s+$', '', doc)

   docLines = doc.splitlines()

   cnt = 0
   doc = None
   for line in docLines :
      #docLines[cnt] = line.strip()
      line.strip()

      line = re.sub('^\s*"', '', line)
      line = re.sub('^\s+', '', line)

      line = re.sub('\s*"\s*$', '', line)
      line = re.sub('\s+$', '', line)

      #docLines[cnt] = line
      #docLines[cnt] = line

      #doc = doc + line + '\n'
      if doc == None :
         doc = line + '\n'
      else :
         doc = doc + '                ' + line + '\n'

      cnt = cnt + 1

   # Check if no description given for the test case 
   if doc == None :
      doc = 'WARNING : *** TEST DESCRIPTION MISSING ***\n'

   doc.strip()

   doc = doc[:-1]

   # Get List of flags required for the test case
   # For simplicity, we are assuming that only one ifdef tag is present
   ifdefNode = reqNode.getElementsByTagName('tapa.ifdef')[0]
   flagNodeList = ifdefNode.getElementsByTagName('tapa.flag')

   ifdefAttr = 'None'

   for node in flagNodeList :
      if node.hasAttribute('id') :
         if ifdefAttr == 'None' :
            ifdefAttr = str(node.getAttribute('id'))
         else :
            ifdefAttr = ifdefAttr + ', ' + str(node.getAttribute('id'))



   # Get List of exclusive flags for the test case
   # For simplicity, we are assuming that only one ifdef tag is present
   ifndefNode = reqNode.getElementsByTagName('tapa.ifndef')[0]
   flagNodeList = ifndefNode.getElementsByTagName('tapa.flag')

   ifndefAttr = 'None'

   for node in flagNodeList :
      if node.hasAttribute('id') :
         if ifndefAttr == 'None' :
            ifndefAttr = str(node.getAttribute('id'))
         else :
            ifndefAttr = ifndefAttr + ', ' + str(node.getAttribute('id'))


   # Get the TC mode
   # For simplicity, we are assuming that only mode tag is present
   modNode = reqNode.getElementsByTagName('tapa.mode')[0]

   modAttr = 'None'
   if modNode.hasAttribute('mode') :
      modAttr = str(modNode.getAttribute('mode'))

   return [rfcAttr, module, doc, ifdefAttr, ifndefAttr, modAttr]




#
#       Fun:   getDocTCStep
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def getDocTCStep(stepNode) :
   '''Generate the documentation for the step'''

   cmdName = str(stepNode.tagName)

   subSteps = []

   # Check if compound command
   if compCmdDict.has_key(cmdName) :
      # Compound command
      # parse and generate a list

      cmdSteps = []
      cmdSteps.append('Command')

      # Add the compound command name doc
      cmdSteps.append(compCmdDict[cmdName])

      subSteps.append(cmdSteps)

   elif intCmdDict.has_key(cmdName) :
      # Internal command, an internal command can
      # have only simple commands, parse and generate
      # a list for all simple commands

      # Append attributes, if any for the internal command
      docString = ''
      cnt = 0
      for s, t in stepNode.attributes.items() :
         if cnt == 0 :
            docString = docString + ' ' + str(s) + '=' + str(t)
            cnt = 1
         else :
            docString = docString + ', ' + str(s) + '=' + str(t)


      # Add the internal command name doc
      intCmdStr = intCmdDict[cmdName] + docString

      # Find all the substeps in the command
      cnt = 0
      for cmd in stepNode.childNodes :
         # Skip anything except ELEMENT_NODE
         if cmd.nodeType != cmd.ELEMENT_NODE :
            continue

         docString = ''
         cmdSteps = []

         if cnt == 0 :
            cmdSteps.append(intCmdStr)
            cnt = 1
         else :
            # No internal command for subsequent commands and sub commands
            cmdSteps.append(" ")

         # Extra validation that only a simple or internal
         # command is present inside
         if simCmdDict.has_key(str(cmd.tagName)) :
            #docString = docString + str(cmd.tagName) + ': ' + simCmdDict[str(cmd.tagName)]
            docString = docString + simCmdDict[str(cmd.tagName)]

            cnt = 0
            for s, t in cmd.attributes.items() :
               if cnt == 0 :
                  docString = docString + ' with ' + str(s) + '=' + str(t)
                  cnt = 1
               else :
                  docString = docString + ', ' + str(s) + '=' + str(t)

            # Add to the steps
            cmdSteps.append(docString)

            # There may be more nested sub simple commands within simple commands 
            for subCmd in cmd.childNodes :
               # Skip anything except ELEMENT_NODE
               if subCmd.nodeType != subCmd.ELEMENT_NODE :
                  continue

               subCmdSteps = []
               # Use the highest level internal command name doc
               # subCmdSteps.append(intCmdStr)
               # No internal command for subsequent commands and sub commands
               subCmdSteps.append(" ")

               docString = ''
               # Extra validation that only a simple or internal
               # command is present inside
               if simCmdDict.has_key(str(subCmd.tagName)) :
                  #docString = docString + str(subCmd.tagName) + ': ' + simCmdDict[str(subCmd.tagName)]
                  docString = docString + simCmdDict[str(subCmd.tagName)]

                  cnt = 0
                  for s, t in subCmd.attributes.items() :
                     if cnt == 0 :
                        docString = docString + ' with ' + str(s) + '=' + str(t)
                        cnt = 1
                     else :
                        docString = docString + ', ' + str(s) + '=' + str(t)

                  # Add to the steps
                  subCmdSteps.append(docString)
               else :
                  print sys.stderr.write(subCmd.tagName + ": Not a simple command inside internal command\n")

               # Add to the steps
               if len(subCmdSteps) != 0 :
                  cmdSteps.append(subCmdSteps)

            subSteps.append(cmdSteps)

         else :
            print sys.stderr.write(cmd.tagName + ": Not a simple command inside internal command\n")
            print stepNode.toxml()
            print cmd.toxml()
            print simCmdDict[cmd.tagName]

      # In case there are no leaf command inside the internal
      # command, append the internal command atleast
      if len(subSteps) == 0 :
         subSteps.append([intCmdStr])
   else :
      print sys.stderr.write(cmdName + ": Unknown command\n")

   return subSteps



#
#       Fun:   genId
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def genId(fileName = None) :
   '''Parse all the XML files for test cases, test groups and generate id'''

   tcDict = {}

   # Create patterns for later use
   patt1 = re.compile(r'abcgrpxyz=(\d+)')

   # If no filename given, do all XML files in the directory
   if (fileName == None) :
      fileLst = glob.glob('*.xml')
   else :
      fileLst = [fileName]

   for file in fileLst :

      # Read XML file
      inputLines = open(file, "r").readlines()
      outFile = open(file + ".bak", "w")

      grpCnt = 999
      tstCnt = 1

      for line in inputLines :

         # Match pattern
         if re.search(r'abcgrpxyz=', line) :
            mobj = patt1.match(line)
            grpCnt = mobj.group(1)
         # Check if the start of the test case or a test group
         elif re.search(r'tapa.testcase\s+id=\".+?\"', line) :
            repl = 'tapa.testcase id="' + str(grpCnt) + "." + str(tstCnt) + '"'
            line = re.sub(r'tapa.testcase\s+id=\".+?\"',
                          repl, line)
            tstCnt = tstCnt + 1
         elif re.search(r'tapa.testgroup\s+id=\".+?\"', line) :
            repl = 'tapa.testcase id="' + str(grpCnt) + "." + str(tstCnt) + '"'
            line = re.sub(r'tapa.testgroup\s+id=\".+?\"',
                          repl, line)

         outFile.write(line)

      outFile.close()


#
#       Fun:   raise xml.dom.SyntaxErr
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def dbgPrnt(text) :
   '''Print the text'''

   if (dbgMask == True) :
      print text


#
#       Fun:   loadTestGroupsLW
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def loadTestGroupsLW(fileName = None, removeComment = True) :
   '''Parse all the XML files for test groups, removes
      comments from the test case '''

   if newTgList != None :
      return newTgList
   else :
      return loadTestGroups(fileName, removeComment)


#
#       Fun:   loadTestCasesLW
#
#       Desc:  This functions is called from the SSI.
#              It registers the various layers with 
#              SSI.
#
#       Ret:   XX_ERR_NONE
#
#       Notes: None
#              
#       File:  cm_xta_py.py
#
#
def loadTestCasesLW(fileName = None, removeComment = True) :
   '''Parse all the XML files for test cases, removes
      comments from the test case '''

   if newTcList != None :
      return newTcList
   else :
      return loadTestCases(fileName, removeComment)





if __name__ == '__main__' :

   # Acceptance Test suites

   # Test loadTestCases
   dictList = loadTestCases()

   for elm in dictList :
      print elm, "\n", dictList[elm]
      parseTestCase(dictList[elm])

   # Test loadTestCases
   dictList = loadCommands()

   for elm in dictList :
      print elm, "\n", dictList[elm]
      parseCommand(dictList[elm])


#/********************************************************************30**
#
#         End of file:     cm_xta_py.py@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 19:25:43 2013
#
#*********************************************************************31*/
#
#
#/********************************************************************40**
#
#        Notes:
#
#*********************************************************************41*/
#
#/********************************************************************50**
#
#*********************************************************************51*/
#
#
#/********************************************************************60**
#
#        Revision history:
#
#*********************************************************************61*/
#
#/********************************************************************90**
#
#     ver       pat    init                  description
#------------ -------- ---- ----------------------------------------------
#            so001.202  rr
#/main/3      ---      sy  1. Update of sid field
#/main/4     cm_xta_py_py  sk  1. Support for FTHA 
#/main/5      ---      rd  1. Correcting the SID 
#/main/6      ---      rb  1. Updated for PDCP Software release 1.1 
#/main/7      ---      aj  1. Added the support for FTHA Integration
#/main/8      ---      mn  1. ROHC compliance upgrade
#/main/9      ---      vg  1. Updated for SO_AUDIT_LCD feature
#/main/10     ---      nk  1. IuUP release 1.1
#/main/11     ---      sy   1. Updated for SIP sdk  release 1.1.
#/main/13     ---      pc  1. IuUP release 1.2
#/main/15     ---      pc  1. EGTP release 1.1
# /main/16    ---      vk  1. Updated for Release of LTE RRC 1.1.
# /main/17    ---      gk  1. Updated for Release of LTE RLC 1.1.
# /main/18    ---      gk  1. Updated for Release of LTE RLC 1.1.
#/main/19     cm_xta_py_py_001.main_18      st  1. Updated for Release of LTE MAC 1.1.
#/main/24     ---      ak  1. Updation for eGTP 1.2 release
#/main/25     ---#      cm_xta_py_py_001.main_24 mm  1. Updated for cz001.101 patch release
#                                         for X2AP.
#/main/32     ---       ajainx   cm_xta_py_py_001.main_25 1. Updated for S1AP Release 2.2.
#/main/33    cm_xta_py_py_001.main_32   vmg  1. Run Time Debug Control for RoHC/IPHC
#             ---       ms  1. Upadted for DTX Handling
#/main/36     ---      cm_xta_py_py_001.main_34  gjahagirdar 1. Updated for Iuh 2.1 release
#/main/37       ---    cm_xta_py_py_001.main_36   gvj  1. Updated Support for MIMO 2.1 GPR
#/main/38       ---    cm_xta_py_py_001.main_37   pkaX  1. Updated for S1AP 3.1 release.
#/main/39       ---    cm_xta_py_py_001.main_38  rsharon  1. Updated for SPS
#                                                              support.
#/main/40     ---      pmacharla         Initial for eGTP release 2.1
#/main/41       ---    cm_xta_py_py_001.main_40  dv  1. Updated for TFU Upgrade
# /main/43    ---    cm_xta_py_py_001.main_42  asaurabh  1. Updated for EGTP_U_REL_9
#/main/44     ---  cm_xta_py_py_001.main_43   hsingh 1. Updated for Release of LTE RRC 3.1.
#/main/45     ---  cm_xta_py_py_001.main_44   dvasisht 1. Updated for Release of LTE MAC 3.1.
#/main/45     ---  cm_xta_py_py_001.main_44   psingh   1. Updated code for patch eg002.201
#/main/46     ---  cm_xta_py_py_001.main_46   psingh   1. Updated code for patch eg003.201
#/main/49     ---  cm_xta_py_py_001.main_48   pka   1. Updated for PSF-S1AP 1.1 Release.
#/main/49     ---  cm_xta_py_py_001.main_49   magnihotri 1.  eGTP-PSF upgrade parameters
#/main/50     ---  cm_xta_py_py_001.main_50   vvashishthth 1. Added flags for diameter 1.3 release.
#/main/51        ---  cm_xta_py_py_001.main_51   nh     1. Updated for PSF-diameter 1.1 release.
#/main/52     ---  cm_xta_py_py_001.main_52   dvasisht 1.Updated for ULSCH at CRC
#/main/53     ---  cm_xta_py_py_001.main_53   psingh   1. Added definitions for Path mgmt
#                                                      2. Parm for indicating max retry error
#                                                      3. Parm for indicating invalid Seq Num
#/main/53     ---  cm_xta_py_py_001.main_53   va    1. Updated for Transparent
#/main/55     ---  cm_xta_py_py_001.main_54   va    1. Updated for S1 abort request 
#/main/56     ---  cm_xta_py_py_001.main_55   psingh   1. Added definitions for TSap Configuration
#                                                      2. Added definition for multi ip flag
#/main/58     ---  cm_xta_py_py_001.main_56   asaurabh 1. Added for S2A and S2B.
#/main/59     ---  cm_xta_py_py_001.main_57   asaurabh 1. Added for outgoing Piggyback support 
#main/60     ---     cm_xta_py_py_001.main_58   akaranth 1. support for Source RNC to target RNC TC ENC/DEC.
#*********************************************************************91*/
