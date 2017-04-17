----------------------------------------
-- script-name: tip.lua
----------------------------------------

----------------------------------------
-- creates a Proto object, but doesn't register it yet
local TIP = Proto("TIP","TIP Message")

----------------------------------------
local mId = { 
      [100] = "MAC_INIT_IND",
      [101] = "MAC_INIT_REQ",
      [102] = "MAC_INIT_RSP",
      [103] = "RLC_INIT_IND",
      [104] = "RLC_INIT_REQ",
      [105] = "RLC_INIT_RSP",
      [106] = "PDCP_INIT_IND",
      [107] = "PDCP_INIT_REQ",
      [108] = "PDCP_INIT_RSP",
      [109] = "HEARTBEAT_REQ",
      [110] = "HEARTBEAT_RSP",
      [301] = "MAC_CELLCONFIG_REQ",
      [302] = "MAC_CELLCONFIG_RSP",
      [303] = "MAC_CELLRECONFIG_REQ",
      [304] = "MAC_CELLRECONFIG_RSP",
      [305] = "MAC_CELLDELETE_REQ",
      [306] = "MAC_CELLDELETE_RSP",
      [307] = "MAC_BROADCASTMSG_REQ",
      [308] = "MAC_BROADCASTMSG_RSP",
      [309] = "MAC_UECONFIG_REQ",
      [310] = "MAC_UECONFIG_RSP",
      [311] = "MAC_UERECONFIG_REQ",
      [312] = "MAC_UERECONFIG_RSP",
      [313] = "MAC_UEDELETE_REQ",
      [314] = "MAC_UEDELETE_RSP",
      [315] = "MAC_CELLSTART_IND",
      [331] = "RLC_CMNCHNL_CONFIG_REQ",
      [332] = "RLC_CMNCHNL_CONFIG_RSP",
      [333] = "RLC_CMNCHNL_DELETE_REQ",
      [334] = "RLC_CMNCHNL_DELETE_RSP",
      [335] = "RLC_UECONFIG_REQ",
      [336] = "RLC_UECONFIG_RSP",
      [337] = "RLC_UERECONFIG_REQ",
      [338] = "RLC_UERECONFIG_RSP",
      [339] = "RLC_UEDELETE_REQ",
      [340] = "RLC_UEDELETE_RSP",
      [341] = "RLC_CCCHMSG_IND",
      [342] = "RLC_CCCHMSG_REQ",
      [343] = "RLC_PCCHMSG_REQ",
      [344] = "RLC_UEIDENTITYCHANGE_REQ",
      [345] = "RLC_UEIDENTITYCHANGE_RSP",
      [371] = "PHY_CELLCONFIG_REQ",
      [372] = "PHY_CELLCONFIG_RSP",
      [373] = "PHY_CELLDELETE_REQ",
      [374] = "PHY_CELLDELETE_RSP",
      [375] = "L3_TTI_IND" ,
      [381] = "L2_UERELEASE_IND" ,
      [701] = "RLC_SDU_STATUS_IND",
      [702] = "PDCP_MSG_IND",
      [703] = "RLC_DATAMSG_REQ",
      [704] = "RLC_DATADISCARD_REQ" }

local modId = {
      [100] = "RRC_MOD_ID",
      [200] = "PDCP_MOD_ID",
      [210] = "DATARELAY_MOD_ID",
      [300] = "RLC_MOD_ID",
      [310] = "MAC_MOD_ID",
      [320] = "PHY_MOD_ID" }

local duplexMode = {
       [0] =  "TDD",
       [1] =  "FDD",
       [2] =  "HD_FDD" }

local phichResEle = {
       [0] = "PHICH_R_ONE_SIXTH",
       [1] = "PHICH_R_HALF ",
       [2] = "PHICH_R_ONE ",
       [3] = "PHICH_R_TWO" }

local phichDur = {
      [0] = "PHICH_DUR_NORMAL",
      [1] = "PHICH_DUR_EXTENDED" }

local srsBwCfg = {
      [0] = "SRS_BANDWIDTH_0",
      [1] = "SRS_BANDWIDTH_1",
      [2] = "SRS_BANDWIDTH_2",
      [3] = "SRS_BANDWIDTH_3",
      [4] = "SRS_BANDWIDTH_4",
      [5] = "SRS_BANDWIDTH_5",
      [6] = "SRS_BANDWIDTH_6",
      [7] = "SRS_BANDWIDTH_7" }

local alpha = {
      [0] = "POWER_ALPHA0",
      [4] = "POWER_ALPHA4",
      [5] = "POWER_ALPHA5",
      [6] = "POWER_ALPHA6",
      [7] = "POWER_ALPHA7",
      [8] = "POWER_ALPHA8",
      [9] = "POWER_ALPHA9",
      [10] = "POWER_ALPHAALL" }

local siWinLen = {
      [1] = "SI_WINDOW_LENGTH_1",
      [2] = "SI_WINDOW_LENGTH_2",
      [5] = "SI_WINDOW_LENGTH_5",
      [10] = "SI_WINDOW_LENGTH_10",
      [15] = "SI_WINDOW_LENGTH_15",
      [20] = "SI_WINDOW_LENGTH_20",
      [40] = "SI_WINDOW_LENGTH_40" }

local siModPrd = {
      [64] = "SI_MODIFICATION_PERD_64",
      [128] = "SI_MODIFICATION_PERD_128",
      [256] = "SI_MODIFICATION_PERD_256",
      [512] = "SI_MODIFICATION_PERD_512",
      [1024] = "SI_MODIFICATION_PERD_1024" }

local siBrdcstChnTime = {
      [1] = "SI_CHANGE_NORMAL",
      [2] = "SI_CHANGE_IMMEDIATE" }

local siPrd = {
      [8] = "SI_PERD_8",
      [16] = "SI_PERD_16",
      [32] = "SI_PERD_32",
      [64] = "SI_PERD_64",
      [128] = "SI_PERD_128",
      [256] = "SI_PERD_256",
      [512] = "SI_PERD_512" }

local bwEnum = {
      [6] = "BW_RB_6",
      [15] = "BW_RB_15",
      [25] = "BW_RB_25",
      [50] = "BW_RB_50",
      [75] = "BW_RB_75",
      [100] = "BW_RB_100" }

local delPucchShftEnum = {
      [1] = "PUCCH_DELTASHIFT1",
      [2] = "PUCCH_DELTASHIFT2",
      [3] = "PUCCH_DELTASHIFT3" }

local rlcEntType = {
      [1] = "RLC_ENTITY_DL_BCCH",
      [2] = "RLC_ENTITY_DL_CCCH",
      [3] = "RLC_ENTITY_UL_CCCH",
      [4] = "RLC_ENTITY_DL_PCCH" }

local CqiTransmodeAPrd = {
      [0] = "APERIODIC_CQI_MOD12",
      [1] = "APERIODIC_CQI_MOD20",
      [2] = "APERIODIC_CQI_MOD22",
      [3] = "APERIODIC_CQI_MOD30",
      [4] = "APERIODIC_CQI_MOD31"  }

local CqiTransmodePrd = {
      [0] = "PERIODIC_CQI_MOD10",
      [1] = "PERIODIC_CQI_MOD11",
      [2] = "PERIODIC_CQI_MOD20",
      [3] = "PERIODIC_CQI_MOD21" }

local ueRelEnum = {
      [0] = "UE_REL_8",
      [1] = "UE_REL_9",
      [2] = "UE_REL_10" }

local dirEnum = {
      [1] = "UPLINK",
      [2] = "DOWNLINK",
      [3] = "BOTH" }

local cfgTypeEnum = {
      [1] = "RLC_RB_ADD",
      [2] = "RLC_RB_MODIFY",
      [3] = "RLC_RB_DELETE",
      [4] = "RLC_RB_RESET" }

local entModeEnum = {
      [1] = "TM",
      [2] = "UM",
      [3] = "AM" }

local l2UeRelEnum = {
      [1] = "L2_UEREL_CAUSE_MAXRETX",
      [2] = "L2_UEREL_CAUSE_ULSYNC_LOSS",
      [3] = "L2_UEREL_CAUSE_UEINACTIVITY" }
-- header fileds start
local header = {
--srcModuleId         = ProtoField.uint16("TIP.srcModuleId", "Source Module ID", nil, modId, 0x0FFF),
srcModuleId         = "Source Module ID: ",
--dstModuleId         = ProtoField.uint16("TIP.dstModuleId", "Destinatioon Module ID", nil, modId, 0x0FFF),
dstModuleId         = "Destinatioon Module ID: ",
cellId	            = ProtoField.uint16("TIP.cellId", "Cell ID"),
--msgId               = ProtoField.uint16("TIP.MsgId", "Message ID", nil, mId, 0x0FFF),
msgId               = "Message ID: ",
transId             = ProtoField.uint32("TIP.TransId", "Trnasaction ID"),
payloadLen          = ProtoField.uint16("TIP.payloadLen", "Payload Length")
}
-- header fields end 

--payload fields  start
local macCellCfgReq = {
mac_cell_cfg_req  = "MAC Cell Config Request",
cyclic_prefix     = ProtoField.uint8("TIP.cyc_prefix", "DL/UL Cyclic Prefix"),
qam_support	  = ProtoField.uint8("TIP.enb_64QAM", "Enable 64 QAM"),
cfi_value	  = ProtoField.uint8("TIP.cfi_value", "CFI value"),
dyn_cfi_enb	  = ProtoField.uint8("TIP.dyn_cfi_enb", "Dynamic CFI enable flag"),
dlfsEnb		  = ProtoField.uint8("TIP.dlfsEnb", "DLFS Scheduling enable flag"),
ulfsEnb		  = ProtoField.uint8("TIP.ulfsEnb", "ULFS Scheduling enable flag"),
pMax		     = ProtoField.int8("TIP.pMax", "pMax"),
nB		        = ProtoField.uint8("TIP.nB", "NB"),
defaultPagingCycle  = ProtoField.uint16("TIP.default_paging_cycle", "Default Paging Cycle"),
numTxAntenna	     = ProtoField.uint8("TIP.numTxAntenna", "Number of Tx Antenna"),
l3SfPeriodicity     = ProtoField.uint16("TIP.l3SfPeriodicity", "L3 SF Periodicity")
}
local harqCfg = {
harqConfig	        = "HARQ Config",
maxDlHarqTrans      = ProtoField.uint8("TIP.maxDlHarqTrans","Max DL HARQ Transmissions"),
maxMsg4HarqTrans    = ProtoField.uint8("TIP.maxMsg4HarqTrans", "Max Msg4 HARQ transmissions")
}
local rntiCfg = {
rntiConfig	  = "RNTI Config",
startRnti	  = ProtoField.uint16("TIP.start_rnti", "start RNTI"),
endRnti		  = ProtoField.uint16("TIP.end_rnti", "end RNTI")
}
local BWInfo = {
BWCfg	     = "B/W Config",
dlBw		  = "DL Bandwidth: ", --, nil, bwEnum, 0xFF),
ulBw		  = "UL Bandwidth: ",-- nil, bwEnum, 0xFF),
duplex_mode	  = "Duplex Mode: "--, nil, duplexMode, 0x0F)
}
local phichInfo = {
PhichCfg	     = "PHICH Config",
PhichRsrc     = "PHICH Resource: ",--, nil, phichResEle, 0x0F),
phichDuration = "PHICH duration: "--, nil, phichDur, 0x0F)
}
local pucchInfo = {
PucchCfg  	  = "PUCCH Config",
resSize		  = ProtoField.uint8("TIP.res_size", "Resource Size"),
deltaShift	  = ProtoField.uint8("TIP.delta_shift", "Delta Shift"),
n1PucchAckNack	  = ProtoField.uint16("TIP.n1_pucch_ack_nack", "N1 PUCCH ACK/NACK"),
cyclShift	  = ProtoField.uint8("TIP.cyclic_shift", "Cyclic Shift")
}
local srsInfo = {
SrsCfg		  = "SRS Config",
cellSpecSrsEnb= ProtoField.uint8("TIP.cell_spec_srs_enb", "Cell Specific SRS Enable"),
srsSFConfig	  = ProtoField.uint8("TIP.srs_sf_cfg", "SRS Subframe Config"),
simAckNackSrs = ProtoField.uint8("TIP.sim_ack_nack_srs", "Simulataneous ACK/NACK and SRS enable"),
srsBwCfg	     = "SRS B/W config: "--, nil, srsBwCfg, 0x0F) 
}
local rachInfo = {
RACHCfg 	  = "RACH Config",
raWindowSize	  = ProtoField.uint8("TIP.ra_window_size", "RA Window Size"),
maxMsg3HarqTrans  = ProtoField.uint8("TIP.max_msg3_harq_trans", "Max Msg3 HARQ Transmissions"),
raPreambles	  = ProtoField.uint8("TIP.ra_preambles", "Number of RA Preambles"),
RaPreambleSizeinGrpA  = ProtoField.uint8("TIP.ra_preamble_size_in_grpA", "Size of RA Preambles in Group A"),
msgSizeGrpA	  = ProtoField.uint16("TIP.msg_size_grpA", "Message Size Group A"),
prachCfgIdx       = ProtoField.uint8("TIP.prach_cfg_idx", "PRACH Configuration Index"),
prachFreqOff      = ProtoField.uint8("TIP.prach_freq_offset", "PRACH Frequency Offset"),
contentionResTimer    = ProtoField.uint8("TIP.contention_res_timer", "Contention resolution Timer")
}
ulPwrInfo = {
ULPowerCtrlCfg 	     = "UL Power Control Config",
P0nominalPusch         = ProtoField.int8("TIP.p0_nominal_pusch", "P0 Nominal PUSCH"),
P0nominalPucch         = ProtoField.int8("TIP.p0_nominal_pucch", "P0 Nominal PUCCH"),
delPreamblMsg3	        = ProtoField.int8("TIP.delta_preamble_msg3", "Delta Preamble Message3"),
ulPowAlpha	           = "UL Power Aplha: ",-- nil, alpha, 0x0F),
frmt3PucchStrtTpcRnti  = ProtoField.uint16("TIP.frmt3PucchStrtTpcRnti", "Format3 PUCCH Start TPC RNTI"),
frmt3PucchEndTpcRnti   = ProtoField.uint16("TIP.frmt3PucchEndTpcRnti", "Format3 PUCCH End TPC RNTI"),
frmt3APucchStrtTpcRnti = ProtoField.uint16("TIP.frmt3APucchStrtTpcRnti", "Format3A PUCCH Start TPC RNTI"),
frmt3APucchEndTpcRnti  = ProtoField.uint16("TIP.frmt3APucchEndTpcRnti", "Format3A PUCCH End TPC RNTI"),
frmt3PuschStrtTpcRnti  = ProtoField.uint16("TIP.frmt3PuschStrtTpcRnti", "Format3 PUSCH Start TPC RNTI"),
frmt3PuschEndTpcRnti   = ProtoField.uint16("TIP.frmt3PuschEndTpcRnti", "Format3 PUSCH End TPC RNTI"),
frmt3APuschStrtTpcRnti = ProtoField.uint16("TIP.frmt3APuschStrtTpcRnti", "Format3A PUSCH Start TPC RNTI"),
frmt3APuschEndTpcRnti  = ProtoField.uint16("TIP.frmt3APuschEndTpcRnti", "Format3A PUSCH End TPC RNTI")
}
local puschInfo = { 
PuschCfg  	     = "PUSCH Config",
numSubBands	     = ProtoField.uint16("TIP.numSubBands", "Number of sub bands"),
hoppingMode	     = ProtoField.uint16("TIP.hoppingMode", "Hopping Mode"),
hopOffset  	     = ProtoField.uint8("TIP.hopOffset", "Hop Offset")
}
local ttiUserInfo = {
numUsersPerTTI	  = "Number of users per TTI",
numDLUsers	     = ProtoField.uint8("TIP.numDlUsers", "Number of DL users per TTI"),
numULUsers	     = ProtoField.uint8("TIP.numUlUsers", "Number of UL users per TTI")
}
local schSpecCfgInfo = {
schSpecCfg	     = "Scheduler Specific Configuration",
dlSchType	     = ProtoField.uint8("TIP.dlSCHType", "Dl Scheduling Type"),
ulSchType	     = ProtoField.uint8("TIP.ulSCHType", "Ul Scheduling Type")
}
local dlPwrInfo = {
DLPowerCtrlCfg 	  = "DL Power Control Config",
pcfichPwrOffset	  = ProtoField.uint16("TIP.pcfich_pwr_off","PCFICH Power Offset"),
phichPwrOffset	     = ProtoField.uint16("TIP.phich_pwr_off","PHICH Power Offset"),
pdcchPwrOffset	     = ProtoField.uint16("TIP.pdcch_pwr_off","PDCCH Power Offset"),
pbchPwrOffset	     = ProtoField.uint16("TIP.pbch_pwr_off","PBCH Power Offset"),
pchPwrOffset	     = ProtoField.uint16("TIP.pch_pwr_off","PCH Power Offset")
}

local mac_cell_cfg_rsp       = "MAC Cell Config Response"
local status          	     = ProtoField.uint16("TIP.status", "Response status")

local broadcastMsgReq = {
mac_brdcst_msg_req = "MAC Broadcast Msg Request",
siWindowLen  	    = "SI Window Length: ",-- nil, siWinLen, 0x0F),
siModPeriod	       = "SI Modification Period: ",-- nil, siModPrd, 0x0FFF),
siBrdcstChgTime    = "SI Broadcast Change Time: ",-- nil, siBrdcstChnTime, 0x0F),
siCfgBitMask	    = ProtoField.uint16("TIP.siCfgBitMask", "SI Config bit mask"),
mibPduLen	       = ProtoField.uint16("TIP.mibPduLen", "MIB PDU Len"),
sib1PduLen	       = ProtoField.uint16("TIP.sib1PduLen", "SIB1 PDU Len"),
siRetxCnt	       = ProtoField.uint8("TIP.siRetxCnt", "SI Retransmission Count"),
numSiPdus	       = ProtoField.uint8("TIP.numSiPdus", "Num SI PDUs"),
mibPdu		       = "MIB PDU:",
sib1Pdu		       = "SIB1 PDU:",
siCfgInfo	       = "SI Config",
siId		          = ProtoField.uint16("TIP.siId", "SI ID"),
numSeg		       = ProtoField.uint8("TIP.numSeg", "Num Segments"),
siPeriod	          = "SI Periodicity: ",-- nil, siPrd, 0x0FFF),
siPduList	       = ProtoField.string("TIP.SiPduList", "SI PDU List"),
pduLen		       = ProtoField.uint16("TIP.pduLen", "PDU Length"),
siPdu		          = "SI PDU:"
}

local broadcastMsgRsp = "MAC Broadcast Msg Response"

local phyCellCfgReq = {
phy_cell_cfg_req = "PHY Cell Config Request",
pci		        = ProtoField.uint16("TIP.pci", "PCI"),
pcfichPwrOff	  = ProtoField.uint16("TIP.pcfichPwrOff", "PCFICH Power Offset"),
bwCfg 		     = "PHY BW Config",
dlBw	   	     = "DL BW: ",-- nil, bwEnum , 0xFF),
ulBw	   	     = "UL BW: ", --nil, bwEnum , 0xFF),
freqBand	        = ProtoField.uint16("TIP.freqBand", "Frequency Band"),
dlFreq		     = ProtoField.uint16("TIP.dlFreq", "DL EARFCN"),
ulFreq		     = ProtoField.uint16("TIP.ulFreq", "UL EARFCN"),
txSchemeCfg      = "Tx Scheme Config",
duplex_mode	     = "Duplex Mode: ",--, nil, duplexMode, 0x0F),
subCarSpac	     = ProtoField.uint16("TIP.subCarSpac", "SubCarrier Spacing"),
cycPrefix	     = ProtoField.uint16("TIP.cycPrefix", "Cyclic Prefix"),
AntCfg		     = "Antenna Config",
antPort		     = ProtoField.uint16("TIP.antPort", "Tx Antenna Port"),
prachCfg	        = "PRACH Config",
rootSeqIdx	     = ProtoField.uint16("TIP.rootSeqIdx", "Root Sequence Index"),
cfgIdx		     = ProtoField.uint16("TIP.cfgIdx", "Config Index"),
zeroCorrZoneCfg  = ProtoField.uint16("TIP.zeroCorrZoneCfg", "Zero Corr Zone Config"),
highSpdFlag	     = ProtoField.uint16("TIP.highSpdFlag", "High Speed Flag"),
freqoff		     = ProtoField.uint16("TIP.freqOff", "Frequency Offset"),
pdschCfg	        = "PDSCH Config",
pB		           = ProtoField.uint16("TIP.pB", "pB"),
puschCfg	        = "PUSCH Config",
hopMode		     = ProtoField.uint16("TIP.hopMode", "Hopping Mode"),
hopOff		     = ProtoField.uint16("TIP.hopOff", "Hopping Offset"),
numSubBnd	     = ProtoField.uint16("TIP.numSubBnd", "Number Of Subbands"),
enb64Qam	        = ProtoField.uint8("TIP.enb64Qam", "Enable 64QAM"),
ulRefSigCfg	     = "UL Reference Signal Config",
grpHopEnb	     = ProtoField.uint8("TIP.grpHopEnb", "Group Hop Enable"),
seqHopEnb	     = ProtoField.uint8("TIP.seqHopEnb", "Sequence Hop Enable"),
grpAssn		     = ProtoField.uint16("TIP.grpAssn", "Group Assignment"),
cycShift	        = ProtoField.uint16("TIP.cycShift", "Cyclic Shift"),
phichCfg	        = "PHICH Config",
phichPwrOffset	  = ProtoField.uint16("TIP.phich_pwr_off","PHICH Power Offset"),
pucchCfg	        = "PUCCH Config",
nRb		        = ProtoField.uint16("TIP.nRb","Number RBs"),
nCs		        = ProtoField.uint16("TIP.nCs","Number Cyclic Shifts"),
n1PucchAN	     = ProtoField.uint16("TIP.n1_pucch_ack_nack", "N1 PUCCH ACK/NACK"),
delPucchShft	  = "Delta PUCCH Shift: ",-- nil, delPucchShftEnum, 0x0F),
srsCfg		     = "SRS Config",
srsBw		        = ProtoField.uint16("TIP.srsBw","SRS BW"),
sfCfg		        = ProtoField.uint16("TIP.sfCfg","SF Config"),
anSimTx		     = ProtoField.uint16("TIP.anSimTx","Simultaneous ACK/NACK"),
sigCfg		     = "SIG Config",
priSynSig	     = ProtoField.uint16("TIP.priSynSig","Primary Sync Signal"),
secSynSig	     = ProtoField.uint16("TIP.secSynSig","Secondary Sync Signal"),
refSignPwr	     = ProtoField.uint16("TIP.refSignPwr","Reference Signal Power")
}
local phyCellCfgRsp = "PHY Cell Config Response"

local rlcChnReq = 
{
rlc_cmn_chn_req     = "RLC Common Channel Config Request",
rlc_cmn_chn_del_req = "RLC Common Channel Delete Request",
numEnt 		        = ProtoField.uint8("TIP.numEnt", "Number of Entities"),
entType		        = "Entity Type: " -- , nil, rlcEntType, 0x0F)
}

local rlcChnRsp = 
{
rlc_cmn_chn_rsp	  = "RLC Common Channel Config Response",
rlc_cmn_chn_del_rsp = "RLC Common Channel Delete Response",
cfgStatus	        = ProtoField.uint8("TIP.cfgStatus", "Config Status"),
numEnt 		        = ProtoField.uint8("TIP.numEnt", "Number of Entities"),
failedEntType	     = "Failed Entity: "--, nil, rlcEntType, 0x0F)
}

local ttiInd =
{
l3TtiInd	   = "L3 TTI Ind",
timinginfo	= "Timing Info",
sfn		   = ProtoField.uint16("TIP.sfn","SFN"),
sf		      = ProtoField.uint8("TIP.sf","SF")
}

-- mac_ue_cfg_req
local macUeCfgReq = {
mac_ue_cfg_req = "MAC UE Config Request",
ueCfgPres      = ProtoField.uint8("TIP.ueCfgPres", "UE Config Present"),
ueCat 	      = ProtoField.uint8("TIP.ueCat", "UE Category"),
ttiBundleEnb   = ProtoField.uint8("TIP.ttiBundleEnb", "TTI Bundling Enable"),
numLcs	      = ProtoField.uint8("TIP.numLcs", "Number of Lcs"),
ueRel	         = "ue Rel: "--, nil, ueRelEnum, 0x0F)
}
local ueId = {
ueInfo = "UE Info",
ueIdx  = ProtoField.uint16("TIP.ueIndex", "UE Index"),
crnti	 = ProtoField.uint16("TIP.crnti", "CRNTI")
}
local TxCfg = { 
TransModeCfg	= "Transmission Mode Config",
TransModePres	= ProtoField.uint8("TIP.trans_mode_pres", "Transmission Mode Presence"),
TransMode	   = ProtoField.uint8("TIP.trans_mode", "Transmission Mode")
}
local dlCqiConfig = {
dlCqiCfg	       = "DL CQI Config",
aperiodicCqiCfg = "Aperiodic CQI Config",
-- re-use below presence field in other structures
present		    = ProtoField.uint8("TIP.pres", "Presence"),
aperiodicCqiTransMode = "Aperiodic CQI Transmission mode: ", --nil, CqiTransmodeAPrd, 0x0F),
periodicCqiCfg	       = "Periodic CQI Config",
-- re-use above presence field
cqiPucchResIdx	  = ProtoField.uint8("TIP.cqiPucchResIdx", "CQI PUCCH Resource Index"),
cqiPmiCfgIdx	  = ProtoField.uint8("TIP.cqiPmiCfgIdx", "CQI PMI Configuration Index"),
k 		           = ProtoField.uint8("TIP.k", "k"),
periodicCqiTransMode = "periodic CQI Transmission mode: ",-- nil, CqiTransmodePrd, 0x0F),
simulAckNackAndCqi   = ProtoField.uint8("TIP.simulAckNackAndCqi", "Simultaneous ACK/NACK and CQI"),
riEnbFlag	     = ProtoField.uint8("TIP.riEnbFlag", "Rank Indication Enable Flag"),
riCfgIdx 	     = ProtoField.uint16("TIP.riCfgIdx", "Rank Indication Config Index")
}
local ulHarqConfig = {
ulHarqCfg	     = "UL HARQ Config",
maxUlHarqTrans	  = ProtoField.uint8("TIP.maxUlHarqTrans", "max UL HARQ Transmissions")
}
local ulPwrCtrl = {
UeUlPwrCtrlCfg    = "UE UL Power Control Config",
UePuschPwrCtrlCfg = "UE PUSCH Power Control Config",
present		      = ProtoField.uint8("TIP.pres", "Presence"),
index		         = ProtoField.uint8("TIP.idx", "Index of TPC used"),
tpcRnti		      = ProtoField.uint16("TIP.tpcRnti", "TPC RNTI"),
UePucchPwrCtrlCfg = "UE PUCCH Power Control Config",
-- we will be reusing present, index and tpcRnti field for PUCCH Pwr ctrl from PUSCH pwr ctrl
accFlag		      = ProtoField.uint8("TIP.accFlag", "Accumulated mode flag"),
deltaMcsFlag	   = ProtoField.uint8("TIP.deltaMcsFlag", "Delta MCS in UL PC"),
p0UePusch	      = ProtoField.int8("TIP.p0UePusch", " P0 UE PUSCH"),
p0UePucch	      = ProtoField.int8("TIP.p0UePucch", " P0 UE PUCCH")
}
local qosCfg = {
UeQosCfg	     = "UE QoS Config",
ambrPres	     = ProtoField.uint8("TIP.ambrPresent", "AMBR presence"),
dlAmbr		  = ProtoField.uint32("TIP.dlAmbr", "DL AMBR"),
ulByteRate	  = ProtoField.uint32("TIP.ulByteRate", "UL byte Rate")
}
local tmrCfg = {
UeTaTmrCfg	     = "UE TA Timer Config",
present		     = ProtoField.uint8("TIP.pres", "Presence"),
taTimer		     = ProtoField.uint16("TIP.taTimer", "TA TIMER")
}
local drxCfg = {
UeDrxCfg	          = "UE DRX Config",
drxEnb		       = ProtoField.uint8("TIP.drxEnb", "drx Enable flag"),
cqiMask		       = ProtoField.uint8("TIP.cqiMask", "CQI Mask"),
drxInactivityTmr   = ProtoField.uint16("TIP.drxInactivityTmr", "DRX Inactivity Timer"),
drxOnDurationTmr   = ProtoField.uint8("TIP.drxOnDurationTmr", "DRX On-duration Timer"),
drxReTransTmr	    = ProtoField.uint8("TIP.drxReTransTmr", "DRX Re-transmission Timer"),
longDrxCycle	    = ProtoField.uint16("TIP.longDrxCycle", "Long DRX cycle value"),
longDrxCycStartOff = ProtoField.uint16("TIP.longDrxCycStartOff", "Long DRX cycle start offset"),
shortDrxPres	    = ProtoField.uint8("TIP.shortDrxPres", "Short DRX Presence"),
shortDrxCycle	    = ProtoField.uint16("TIP.shortDrxCycle", "Short DRX cycle"),
shortDrxCycleTmr   = ProtoField.uint16("TIP.shortDrxCycleTmr", "Short DRX cycle timer"),
}
local measCfg = {
ueMeasGapCfg     = "UE Measurement Gap Config",
ueMeasGapCfgPres = ProtoField.uint8("TIP.ueMeasGapCfgPres", "UE Measurement Gap Flag"),
gapPeriod	     = ProtoField.uint8("TIP.gapPeriod", "Gap Period"),
gapOff		     = ProtoField.uint8("TIP.gapOffset", "Gap Offset")
}
local cbsrCfg = {
CbSubsetRestrictionCfg = "CbSubsetRestrictionConfig",
CbSubsetRestrictionFlg = ProtoField.uint8("TIP.cbFlag", "CbSubsetRestrictionFlag"),
cBitmap0	              = ProtoField.uint32("TIP.cBitmap0", "cBitMap[0]"),
cBitmap1	              = ProtoField.uint32("TIP.cBitmap1", "cBitMap[1]")
}
local srsCfg = {
srsUeCfg	     = "SRSUeConfig",
srsCfgFlag	  = ProtoField.uint8("TIP.srsCfgFlag", "srsConfigFlag"),
srsCfgIndex	  = ProtoField.uint8("TIP.srsCfgIndex", "srsConfigIndex"),
srsBw		     = ProtoField.uint8("TIP.srsBw", "srsBandwidth"),
srsHopBw	     = ProtoField.uint8("TIP.srsHopBw", "srsHoppingBandwidth"),
srsCycShift	  = ProtoField.uint8("TIP.srsCycShift", "srsCyclicShift"),
duration	     = ProtoField.uint8("TIP.duration", "duration"),
transComb	  = ProtoField.uint8("TIP.transComb", "transmissionComb"),
freqPos		  = ProtoField.uint8("TIP.freqPos", "FrequencyDomainPosition")
}
local srConfig = {
srCfg		     = "SRConfig",
srCfgFlag     = ProtoField.uint8("TIP.srCfgFlag", "srConfigFlag"),
srCfgIdx	     = ProtoField.uint8("TIP.srCfgIdx", "srConfigIndex"),
srResIdx	     = ProtoField.uint16("TIP.srResIdx", "srResourceIndex")
}
local puschConfig = {
puschCfg	       = "UE PUSCH Config",
puschCfgSupport = ProtoField.uint8("TIP.puschCfgSupport", "UE PUSCH Config Support"),
harqBetaOff	    = ProtoField.uint8("TIP.harqBetaOff", "HARQ Beta Offset"),
riBetaOff	    = ProtoField.uint8("TIP.riBetaOff", "RI Beta Offset"),
cqiBetaOff      = ProtoField.uint8("TIP.cqiBetaOff", "CQI Beta Offset")
}
local pdschConfig = {
pdschCfg	      = "UE PDSCH Config",
pdschPaCfgFlag = ProtoField.uint8("TIP.pdschPaCfgFlag", "PDSCH PA Config Flag"),
pA	            = ProtoField.uint8("TIP.pA", "pA")
}
local lcCfg = {
lcConfig	     = "LC Config",
lcCfgType	  = ProtoField.uint8("TIP.lcCfgType", "Lc Config Type"),
lchId		     = ProtoField.uint8("TIP.lchId", "Lch Id"),
dir		     = "direction info: ",-- nil, dirEnum, 0x0F),
ulLcCfg		  = "UL LC Config",
lcgId		     = ProtoField.uint8("TIP.lcgId", "Lcg Id"),
dlLcCfg		  = "DL LC Config",
lchPrio		  = ProtoField.uint8("TIP.lchPrio", "Lch Priority"),
qosCfg		  = "QoS Config",
qci		     = ProtoField.uint8("TIP.qci", "QCI"),
GbrQos		  = "GBR QoS info",
eRabMaxBitRateDl = ProtoField.uint32("TIP.eRabMaxBitRateDl", "ERAB Max Bit Rate DL"),
eRabMaxBitRateUl = ProtoField.uint32("TIP.eRabMaxBitRateUl", "ERAB Max Bit Rate UL"),
eRabGrBitRateDl  = ProtoField.uint32("TIP.eRabGrBitRateDl", "ERAB Guaranteed Bit Rate DL"),
eRabGrBitRateUl  = ProtoField.uint32("TIP.eRabGrBitRateUl", "ERAB Guaranteed Bit Rate UL")
}

-- mac_ue_cfg_rsp
local mac_ue_cfg_rsp = "MAC UE Config Response"
local numFailedEnt   = ProtoField.uint16("TIP.numFailedEnt", "Num Failed Entities")
local failEnt = {
failedEnt	  = "Failed Entities",
lchCfgType	  = ProtoField.uint8("TIP.lchCfgType", "Lch Cfg Type"),
lchId		     = ProtoField.uint8("TIP.lchId", "Lch Id")
}

-- mac_ue_recfg_req
local macUeRecfgReq = {
mac_ue_recfg_req = "MAC UE Re-Config Request",
oldCrnti      = ProtoField.uint16("TIP.oldCrnti", "Old CRNTI"),
newCrnti      = ProtoField.uint16("TIP.newCrnti", "New CRNTI"),
bitMask       = ProtoField.uint16("TIP.bitMask", "Bit Mask")
}
local mac_ue_recfg_rsp = "MAC UE Re-Config Response"

-- rlc_ue_cfg_req
local rlc_ue_cfg_req = "RLC UE Config Request"
local nEnt	     = ProtoField.uint8("TIP.nEnt", "Number of Entities")
local rlcEntCfg = {
entCfg      = "RLC Entity Config",
cfgType	    = "Config Type: ", --nil, cfgTypeEnum, 0x0F),
rbIdentity  = "RB Identity",
rbId	    = ProtoField.uint8("TIP.rbId", "RB ID"),
lcId	    = ProtoField.uint8("TIP.lcId", "LC ID"),
qci	    = ProtoField.uint8("TIP.qci", "QCI"),
entMode	 = "Entity Mode: ",-- nil, entModeEnum, 0x0F),
dir	    = "direction info: ",-- nil, dirEnum, 0x0F),
unAckModeCfg = "UnAck Mode Config",
dlSn	     = ProtoField.uint8("TIP.dlSn", "DL SN"),
ulSn	     = ProtoField.uint8("TIP.ulSn", "UL SN"),
reOrdTmr     = ProtoField.uint8("TIP.reOrdTmr", "ReOrdering Timer"),
ackModeCfg   = "Ack Mode Config",
pollReTxTmr  = ProtoField.uint16("TIP.pollReTxTmr", "Poll Retransmit Timer"),
pollPdu	     = ProtoField.int16("TIP.pollPdu", "Poll PDU"),
pollByte     = ProtoField.uint16("TIP.pollByte", "Poll Byte"),
maxReTx      = ProtoField.uint8("TIP.maxReTx", "Max Retransmissions"),
statusTmr    = ProtoField.uint16("TIP.statusProhibitTmr", "status prohibit Timer"),
reorderTmr   = ProtoField.uint8("TIP.reorderTmr", "reordering Timer"),
reCfgBitMask = ProtoField.uint16("TIP.reCfgBitMask", "Reconfig Bit Mask")
}

local rlc_ue_cfg_rsp = "RLC UE Config Response"
local entCfm  = "RLC Entity Confirmation"

local rlc_ue_recfg_req = "RLC UE Re-Config Request"
local rlc_ue_recfg_rsp = "RLC UE Re-Config Response"

local rlc = {
rlcCcchMsgInd      = "RLC CCCH Msg IND",
msgLen 	          = ProtoField.uint16("TIP.msgLen", "Msg Len"),
ccchMsg	          = "CCCH Msg:",
pcchMsg	          = "PCCH Msg:",
rlcCcchMsgReq      = "RLC CCCH Msg REQ",
rlcCcchMsgUeRejReq = ProtoField.string("TIP.rlcCcchMsgUeRejReq", "RLC CCCH Msg UE REJ REQ"),
rlcPcchMsgReq      = "RLC PCCH Msg REQ",
numSfn 	          = ProtoField.uint16("TIP.numSfn", "Number of SFN"),
ueIdChngReq	       = "UE ID Change Request",
newCrnti	          = ProtoField.uint16("TIP.newCrnti", "new CRNTI"),
ueIdChngRsp	       = "UE ID Change Response",
status		       = ProtoField.uint16("TIP.status", "status"),
ovrWrtMsg          = ProtoField.uint8("TIP.ovrWrtMsg", "ovrWrtMsg"),
l2UeRelInd         = "L2 UE Release Ind",
relCause           = "Cause: " 
}

local l2ul2l = {
rbIdentity      = "RB Identity",
rbId	          = ProtoField.uint8("TIP.rbId", "RB ID"),
lcId	          = ProtoField.uint8("TIP.lcId", "LC ID"),
sduStatus       = "SDU status",
sduId	          = ProtoField.uint32("TIP.sduId", "SDU ID"),
status	       = ProtoField.uint8("TIP.status", "Status"),
sduStatusInd    = "SDU Status Ind",
numSdu	       = ProtoField.uint32("TIP.numSdu", "Number of SDU"),
pdcpMsgInd      = "PDCP Msg Ind",
bufLen	       = ProtoField.uint32("TIP.bufLen", "Data Buffer Len"),
reEstFlag       = ProtoField.uint8("TIP.reEstFlag", "Re-establishment Flag"),
dataBuf         = "Data Buffer:",
rlcDatMsgReq    = "RLC Data Msg Request",
rlcDatDiscReq   = "RLC Data Discard Request",
}

local cellUeDel = {
macUeDelReq    = "MAC UE Delete Request",
macUeDelRsp    = "MAC UE Delete Response",
rlcUeDelReq    = "RLC UE Delete Request",
rlcUeDelRsp    = "RLC UE Delete Response",
macCellDelRsp  = "MAC Cell Delete Response",
phyCellDelRsp  = "PHY Cell Delete Response"
}
--payload fields end

-- this actually registers the ProtoFields above, into our new Protocol
TIP.fields = {
		header.transId, header.payloadLen, header.cellId,
		macCellCfgReq.cyclic_prefix, macCellCfgReq.qam_support,
		macCellCfgReq.cfi_value, macCellCfgReq.dyn_cfi_enb,
      harqCfg.maxDlHarqTrans, harqCfg.maxMsg4HarqTrans,
		rntiCfg.startRnti, rntiCfg.endRnti,
		macCellCfgReq.dlfsEnb, macCellCfgReq.ulfsEnb, 
		macCellCfgReq.pMax, macCellCfgReq.defaultPagingCycle,
		pucchInfo.resSize, pucchInfo.deltaShift, pucchInfo.n1PucchAckNack, pucchInfo.cyclShift, 
		srsInfo.cellSpecSrsEnb, srsInfo.srsSFConfig, srsInfo.simAckNackSrs, 
		rachInfo.raWindowSize, rachInfo.maxMsg3HarqTrans, rachInfo.raPreambles, 
      rachInfo.RaPreambleSizeinGrpA, rachInfo.msgSizeGrpA, rachInfo.prachCfgIdx, rachInfo.prachFreqOff, rachInfo.contentionResTimer, 
      ulPwrInfo.P0nominalPusch, ulPwrInfo.P0nominalPucch, ulPwrInfo.delPreamblMsg3,
      ulPwrInfo.frmt3PucchStrtTpcRnti, ulPwrInfo.frmt3PucchEndTpcRnti, ulPwrInfo.frmt3APucchStrtTpcRnti,
		ulPwrInfo.frmt3APucchEndTpcRnti, ulPwrInfo.frmt3PuschStrtTpcRnti, ulPwrInfo.frmt3PuschEndTpcRnti, 
      ulPwrInfo.frmt3APuschStrtTpcRnti, ulPwrInfo.frmt3APuschEndTpcRnti, 
      puschInfo.numSubBands, puschInfo.hoppingMode, puschInfo.hopOffset, 
		ttiUserInfo.numDLUsers,ttiUserInfo.numULUsers, 
		schSpecCfgInfo.dlSchType, schSpecCfgInfo.ulSchType, 
      dlPwrInfo.pcfichPwrOffset, dlPwrInfo.phichPwrOffset, dlPwrInfo.pdcchPwrOffset,
		dlPwrInfo.pbchPwrOffset, dlPwrInfo.pchPwrOffset, 
      macCellCfgReq.numTxAntenna, macCellCfgReq.nB, macCellCfgReq.l3SfPeriodicity, 
		status,
 		broadcastMsgReq.siCfgBitMask, broadcastMsgReq.mibPduLen,
		broadcastMsgReq.sib1PduLen, broadcastMsgReq.siRetxCnt,
		broadcastMsgReq.numSiPdus, 
		broadcastMsgReq.siId, broadcastMsgReq.numSeg, broadcastMsgReq.siPduList,
		broadcastMsgReq.pduLen, broadcastMsgReq.pdu,
		phyCellCfgReq.pci, phyCellCfgReq.pcfichPwrOff, 
      phyCellCfgReq.freqBand,
		phyCellCfgReq.dlFreq, phyCellCfgReq.ulFreq,
      phyCellCfgReq.subCarSpac, phyCellCfgReq.cycPrefix,
		phyCellCfgReq.antPort, phyCellCfgReq.rootSeqIdx,
		phyCellCfgReq.cfgIdx, phyCellCfgReq.zeroCorrZoneCfg, phyCellCfgReq.highSpdFlag, phyCellCfgReq.freqoff,
		phyCellCfgReq.pB,
		phyCellCfgReq.hopMode, phyCellCfgReq.hopOff, phyCellCfgReq.numSubBnd, phyCellCfgReq.enb64Qam,
		phyCellCfgReq.grpHopEnb, phyCellCfgReq.seqHopEnb, phyCellCfgReq.grpAssn, phyCellCfgReq.cycShift,
  		phyCellCfgReq.phichPwrOffset,
 		phyCellCfgReq.nRb, phyCellCfgReq.nCs, phyCellCfgReq.n1PucchAN, 
		phyCellCfgReq.srsBw, phyCellCfgReq.sfCfg, phyCellCfgReq.anSimTx,
		phyCellCfgReq.priSynSig, phyCellCfgReq.secSynSig, phyCellCfgReq.refSignPwr,
		rlcChnReq.numEnt, 
		rlcChnRsp.cfgStatus, rlcChnRsp.numEnt, 
		ttiInd.sfn, ttiInd.sf,
		ueId.ueIdx, ueId.crnti, 
		macUeCfgReq.ueCfgPres, macUeCfgReq.ueCat,
		TxCfg.TransModePres, TxCfg.TransMode,
		dlCqiConfig.aperiodicCqiCfgPres, dlCqiConfig.present,
		dlCqiConfig.cqiPucchResIdx,
		dlCqiConfig.cqiPmiCfgIdx, dlCqiConfig.k, 
		dlCqiConfig.simulAckNackAndCqi, dlCqiConfig.riEnbFlag, dlCqiConfig.riCfgIdx,
		ulHarqConfig.maxUlHarqTrans,
		ulPwrCtrl.present, ulPwrCtrl.index, ulPwrCtrl.tpcRnti,
		ulPwrCtrl.accFlag, ulPwrCtrl.deltaMcsFlag,
		ulPwrCtrl.p0UePusch, ulPwrCtrl.p0UePucch,
		qosCfg.ambrPres, qosCfg.dlAmbr, qosCfg.ulByteRate,
		tmrCfg.taTimer, tmrCfg.present,
		drxCfg.drxEnb, drxCfg.cqiMask, drxCfg.drxInactivityTmr,
		drxCfg.drxOnDurationTmr, drxCfg.drxReTransTmr, drxCfg.longDrxCycle, drxCfg.longDrxCycStartOff,
		drxCfg.shortDrxPres, drxCfg.shortDrxCycle, drxCfg.shortDrxCycleTmr,
		measCfg.ueMeasGapCfgPres, measCfg.gapPeriod, measCfg.gapOff,
		cbsrCfg.CbSubsetRestrictionFlg, cbsrCfg.cBitmap0, cbsrCfg.cBitmap1,
		srsCfg.srsCfgFlag, srsCfg.srsCfgIndex,srsCfg.srsBw, srsCfg.srsHopBw, 
		srsCfg.srsCycShift, srsCfg.duration, srsCfg.transComb, srsCfg.freqPos,
		srConfig.srCfgFlag, srConfig.srCfgIdx, srConfig.srResIdx,
		puschConfig.puschCfgSupport, puschConfig.harqBetaOff, 
		puschConfig.riBetaOff, puschConfig.cqiBetaOff,
		pdschConfig.pdschPaCfgFlag, pdschConfig.pA,
		macUeCfgReq.ttiBundleEnb, macUeCfgReq.numLcs, 
		lcCfg.lcCfgType, lcCfg.lchId, 
		lcCfg.lcgId, lcCfg.lchPrio,
		lcCfg.qci, lcCfg.eRabMaxBitRateDl,
		lcCfg.eRabMaxBitRateUl, lcCfg.eRabGrBitRateDl, lcCfg.eRabGrBitRateUl,
		numFailedEnt, 
		failEnt.lchCfgType, failEnt.lchId,
		macUeRecfgReq.oldCrnti,
		macUeRecfgReq.newCrnti, macUeRecfgReq.bitMask,
		nEnt, 
		rlcEntCfg.rbId, rlcEntCfg.lcId,
		rlcEntCfg.qci, 
		rlcEntCfg.dlSn, rlcEntCfg.ulSn, rlcEntCfg.reOrdTmr,
		rlcEntCfg.pollReTxTmr, rlcEntCfg.pollPdu, rlcEntCfg.reCfgBitMask, 
		rlcEntCfg.pollByte, rlcEntCfg.maxReTx, rlcEntCfg.statusTmr, rlcEntCfg.reorderTmr,
		rlc.msgLen, rlc.numSfn, rlc.ovrWrtMsg, 
		rlc.rlcCcchMsgUeRejReq,
		rlc.newCrnti, rlc.status,
		l2ul2l.rbId, l2ul2l.lcId, 
		l2ul2l.sduId, l2ul2l.status, 
		l2ul2l.numSdu, 
		l2ul2l.bufLen, l2ul2l.reEstFlag, 
	  }

--[[
local ef_too_short      = ProtoExpert.new("TIP.too_short.expert", "TIP packet too short",
                                      expert.group.MALFORMED, expert.severity.ERROR)    
local ef_too_long       = ProtoExpert.new("TIP.too_long.expert", "TIP packet size exceeds \"pktLen\" in header",
                                          expert.group.MALFORMED, expert.severity.ERROR)    
--]]
local PROTO_HDR_LEN = 16

function addMacCellCfgReqToTree(tvbuf, tree, offset, payLen, endianness)

      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local cellCfgTree = tree:add(info, macCellCfgReq.mac_cell_cfg_req)

	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.cyclic_prefix,info, endianness)
    	offset = offset + 1
	
	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.qam_support,info, endianness)
    	offset = offset + 1	

	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.cfi_value,info, endianness)
    	offset = offset + 1	

	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.dyn_cfi_enb,info, endianness)
    	offset = offset + 1

        --  HARQ Configuration 
      local harqCfgTree = cellCfgTree:add(tvbuf:range(offset,4), harqCfg.harqConfig)

	      info = tvbuf:range(offset,1)
	      harqCfgTree:add_packet_field(harqCfg. maxDlHarqTrans,info, endianness)
    	   offset = offset + 1
	 
	      info = tvbuf:range(offset,1)
	      harqCfgTree:add_packet_field(harqCfg.maxMsg4HarqTrans, info, endianness)
    	   offset = offset + 1
    	   offset = offset + 2 -- no need to display spare bytes

        --  RNTI Configuration 
	   local rntiCfgTree = cellCfgTree:add(tvbuf:range(offset,4), rntiCfg.rntiConfig)

	      info = tvbuf:range(offset,2)
	      rntiCfgTree:add_packet_field(rntiCfg.startRnti,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      rntiCfgTree:add_packet_field(rntiCfg.endRnti,info, endianness)
    	   offset = offset + 2

	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.dlfsEnb,info, endianness)
    	offset = offset + 1

	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.ulfsEnb,info, endianness)
    	offset = offset + 1

	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.pMax,info, endianness)
    	offset = offset + 1
    	offset = offset + 1 --spare

	   info = tvbuf:range(offset,2)
	   cellCfgTree:add_packet_field(macCellCfgReq.defaultPagingCycle,info, endianness)
    	offset = offset + 2
    	offset = offset + 2 --spare

	   --  Bandwidth Configuration  
	   local bwCfgTree = cellCfgTree:add(tvbuf:range(offset,12),BWInfo.BWCfg)

	      info = tvbuf:range(offset,4):le_uint()
         local enumRep = tostring(bwEnum[info]) .. " (" .. tostring(info) ..")"
	      bwCfgTree:add(tvbuf:range(offset,4), BWInfo.dlBw .. enumRep)
    	   offset = offset + 4
 
	      info = tvbuf:range(offset,4):le_uint()
         enumRep = tostring(bwEnum[info]) .. " (" .. tostring(info) ..")"
	      bwCfgTree:add(tvbuf:range(offset,4), BWInfo.ulBw .. enumRep)
    	   offset = offset + 4

	      info = tvbuf:range(offset,4):le_uint()
         enumRep = tostring(duplexMode[info]) .. " (" .. tostring(info) ..")"
	      bwCfgTree:add(tvbuf:range(offset,4), BWInfo.duplex_mode .. enumRep)
         offset = offset + 4

	   -- PHICH Configuration 
	   local phichCfgTree = cellCfgTree:add(tvbuf:range(offset,8),phichInfo.PhichCfg)

	      info = tvbuf:range(offset,4):le_uint()
         local phichRes = tostring(phichResEle[info]) .. " (" .. tostring(info) ..")"
	      phichCfgTree:add(tvbuf:range(offset,4), phichInfo.PhichRsrc .. phichRes)
    	   offset = offset + 4

	      info = tvbuf:range(offset,4):le_uint()
         local duration = tostring(phichDur[info]) .. " (" .. tostring(info) .. ")"
	      phichCfgTree:add(tvbuf:range(offset,4), phichInfo.phichDuration .. duration)
    	   offset = offset + 4
	
	   --   PUCCH Configuration  
	   local pucchCfgTree = cellCfgTree:add(tvbuf:range(offset,8), pucchInfo.PucchCfg)

	      info = tvbuf:range(offset,1)
	      pucchCfgTree:add_packet_field(pucchInfo.resSize,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      pucchCfgTree:add_packet_field(pucchInfo.deltaShift,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,2)
	      pucchCfgTree:add_packet_field(pucchInfo.n1PucchAckNack,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,1)
	      pucchCfgTree:add_packet_field(pucchInfo.cyclShift,info, endianness)
    	   offset = offset + 1

         offset = offset + 3  -- no need to display spare bytes
	
 	   --  SRS Configuration 
	   local srsCfgTree = cellCfgTree:add(tvbuf:range(offset,8) ,srsInfo.SrsCfg)

	      info = tvbuf:range(offset,1)
	      srsCfgTree:add_packet_field(srsInfo.cellSpecSrsEnb,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      srsCfgTree:add_packet_field(srsInfo.srsSFConfig,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      srsCfgTree:add_packet_field(srsInfo.simAckNackSrs,info, endianness)
    	   offset = offset + 1

    	   offset = offset + 1 -- no need to display spare bytes

	      info = tvbuf:range(offset,4):le_uint()
         local bw = tostring(srsBwCfg[info]) .. " (" .. tostring(info) .. ")"
	      srsCfgTree:add(tvbuf:range(offset,4), srsInfo.srsBwCfg .. bw)
    	   offset = offset + 4

	   -- RACH Configuration 
	   local rachCfgTree = cellCfgTree:add(tvbuf:range(offset,12) ,rachInfo.RACHCfg)

	      info = tvbuf:range(offset,1)
	      rachCfgTree:add_packet_field(rachInfo.raWindowSize,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      rachCfgTree:add_packet_field(rachInfo.maxMsg3HarqTrans,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      rachCfgTree:add_packet_field(rachInfo.raPreambles,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      rachCfgTree:add_packet_field(rachInfo.RaPreambleSizeinGrpA,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,2)
	      rachCfgTree:add_packet_field(rachInfo.msgSizeGrpA,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,1)
	      rachCfgTree:add_packet_field(rachInfo.prachCfgIdx,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      rachCfgTree:add_packet_field(rachInfo.prachFreqOff,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      rachCfgTree:add_packet_field(rachInfo.contentionResTimer,info, endianness)
    	   offset = offset + 1

    	   offset = offset + 3 -- no need to display spare bytes

	   -- UL Power Control Configuration 
	   local ulPwrCtrlCfgTree = cellCfgTree:add(tvbuf:range(offset,24), ulPwrInfo.ULPowerCtrlCfg)

	      info = tvbuf:range(offset,1)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.P0nominalPusch,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.P0nominalPucch,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.delPreamblMsg3,info, endianness)
    	   offset = offset + 1

    	   offset = offset + 1 -- no need to display spare bytes

	      info = tvbuf:range(offset,4):le_uint()
         local alph = tostring(alpha[info]) .. " (" .. tostring(info) ..")"
	      ulPwrCtrlCfgTree:add(tvbuf:range(offset,4), ulPwrInfo.ulPowAlpha .. alph)
    	   offset = offset + 4

	      info = tvbuf:range(offset,2)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.frmt3PucchStrtTpcRnti,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.frmt3PucchEndTpcRnti,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.frmt3APucchStrtTpcRnti,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.frmt3APucchEndTpcRnti,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.frmt3PuschStrtTpcRnti,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.frmt3PuschEndTpcRnti,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.frmt3APuschStrtTpcRnti,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      ulPwrCtrlCfgTree:add_packet_field(ulPwrInfo.frmt3APuschEndTpcRnti,info, endianness)
    	   offset = offset + 2

	   -- PUSCH Configuration 
	   local puschCfgTree = cellCfgTree:add(tvbuf:range(offset,8), puschInfo.PuschCfg)

	      info = tvbuf:range(offset,2)
	      puschCfgTree:add_packet_field(puschInfo.numSubBands,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      puschCfgTree:add_packet_field(puschInfo.hoppingMode,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,1)
	      puschCfgTree:add_packet_field(puschInfo.hopOffset,info, endianness)
    	   offset = offset + 1
	
    	   offset = offset + 3 -- no need to display spare bytes

	   -- Number of Users Per TTI 
	   local numUsersTree = cellCfgTree:add(tvbuf:range(offset,4), ttiUserInfo.numUsersPerTTI)

	      info = tvbuf:range(offset,1)
	      numUsersTree:add_packet_field(ttiUserInfo.numDLUsers,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      numUsersTree:add_packet_field(ttiUserInfo.numULUsers,info, endianness)
    	   offset = offset + 1

    	   offset = offset + 2

	   -- Scheduler Specific Configuration 
	   local schCfgTree = cellCfgTree:add(tvbuf:range(offset,4),schSpecCfgInfo.schSpecCfg)

	      info = tvbuf:range(offset,1)
	      schCfgTree:add_packet_field(schSpecCfgInfo.dlSchType,info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      schCfgTree:add_packet_field(schSpecCfgInfo.ulSchType,info, endianness)
    	   offset = offset + 1

    	   offset = offset + 2 -- no need to display spare bytes

	   -- DL Power Control Configuration
	   local dlPwrCtrlCfgTree = cellCfgTree:add(tvbuf:range(offset,12),dlPwrInfo.DLPowerCtrlCfg)

	      info = tvbuf:range(offset,2)
	      dlPwrCtrlCfgTree:add_packet_field(dlPwrInfo.pcfichPwrOffset,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      dlPwrCtrlCfgTree:add_packet_field(dlPwrInfo.phichPwrOffset,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      dlPwrCtrlCfgTree:add_packet_field(dlPwrInfo.pdcchPwrOffset,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      dlPwrCtrlCfgTree:add_packet_field(dlPwrInfo.pbchPwrOffset,info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,2)
	      dlPwrCtrlCfgTree:add_packet_field(dlPwrInfo.pchPwrOffset,info, endianness)
    	   offset = offset + 2

    	   offset = offset + 2 -- no need to display spare bytes

	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.numTxAntenna, info, endianness)
    	offset = offset + 1	

	   info = tvbuf:range(offset,1)
	   cellCfgTree:add_packet_field(macCellCfgReq.nB, info, endianness)
    	offset = offset + 1	

	   info = tvbuf:range(offset,2)
	   cellCfgTree:add_packet_field(macCellCfgReq.l3SfPeriodicity, info, endianness)
    	offset = offset + 2	


end

function addMacCellCfgRspToTree(tvbuf, tree, offset, payLen,  endianness)

      local info = tvbuf:range(offset,4)
      local cellCfgRspTree = tree:add(tvbuf:range(offset,4), mac_cell_cfg_rsp)

	   info = tvbuf:range(offset,2)
	   cellCfgRspTree:add_packet_field(status, info, endianness)
    	offset = offset + 2	

    	offset = offset + 2	-- no need to display spare bytes

end

function addBcastMsgToTree(tvbuf, tree, offset, payLen, endianness)

     local bMsgTree = tree:add(tvbuf:range(offset,payLen - offset),broadcastMsgReq.mac_brdcst_msg_req)

        info = tvbuf:range(offset,4):le_uint()
        local siWin = tostring(siWinLen[info]) .. " (" .. tostring(info) ..")"
        bMsgTree:add(tvbuf:range(offset,4), broadcastMsgReq.siWindowLen .. siWin)
        offset = offset + 4
 
        info = tvbuf:range(offset,4):le_uint()
        local siMPrd = tostring(siModPrd[info]) .. " (" .. tostring(info) ..")"
        bMsgTree:add(tvbuf:range(offset,4), broadcastMsgReq.siModPeriod .. siMPrd)
        offset = offset + 4
 
        info = tvbuf:range(offset,4):le_uint()
        local siChnTime = tostring(siBrdcstChnTime[info]) .. " (" .. tostring(info) ..")"
        bMsgTree:add(tvbuf:range(offset,4), broadcastMsgReq.siBrdcstChgTime .. siChnTime)
        offset = offset + 4
 
        info = tvbuf:range(offset,2)
        bMsgTree:add_packet_field(broadcastMsgReq.siCfgBitMask, info, endianness)
        offset = offset + 2

        info = tvbuf:range(offset,2)
        local mibPDULen = tvbuf:range(offset,2):le_uint()  
        bMsgTree:add_packet_field(broadcastMsgReq.mibPduLen, info, endianness)
        offset = offset + 2
 
        info = tvbuf:range(offset,2)
        local sib1PDULen = tvbuf:range(offset,2):le_uint()  
        bMsgTree:add_packet_field(broadcastMsgReq.sib1PduLen, info, endianness)
        offset = offset + 2

        offset = offset + 2 --spare

        info = tvbuf:range(offset,1)
        bMsgTree:add_packet_field(broadcastMsgReq.siRetxCnt, info, endianness)
        offset = offset + 1

        info = tvbuf:range(offset,1)
        local numSiPDU = tvbuf:range(offset,1):le_uint()  
        bMsgTree:add_packet_field(broadcastMsgReq.numSiPdus, info, endianness)
        offset = offset + 1

	     --mibPdu
	     local saveOffset = offset;
        while offset < (saveOffset + mibPDULen) do
           info = tvbuf:range(offset,1):uint()
           local hexfmt = string.format("%x", tostring(info))
	        stream = stream .. " " .. tostring(hexfmt)
           offset = offset + 1
        end
        bMsgTree:add(tvbuf:range(saveOffset,mibPDULen), broadcastMsgReq.mibPdu..stream)

        --sib1Pdu
        saveOffset = offset;
	     stream = " "
        while offset < (saveOffset + sib1PDULen) do
           info = tvbuf:range(offset,1):uint()
           local hexfmt = string.format("%x", tostring(info))
	        stream = stream .. " " .. hexfmt 
           offset = offset + 1
        end
           
        bMsgTree:add(tvbuf:range(saveOffset,sib1PDULen), broadcastMsgReq.sib1Pdu..stream)

	     --siCfgInfo
	     while offset < (payLen) do
        local siCfgTree = bMsgTree:add(broadcastMsgReq.siCfgInfo)
	
           info = tvbuf:range(offset,2)
           siCfgTree:add_packet_field(broadcastMsgReq.siId, info, endianness)
           offset = offset + 2
           offset = offset + 2 --spare

	        info = tvbuf:range(offset,1)
	        local numsgmnt = tvbuf:range(offset,1):le_uint()  
	        siCfgTree:add_packet_field(broadcastMsgReq.numSeg, info, endianness)
	        offset = offset + 1
	        offset = offset + 3 --spare

           info = tvbuf:range(offset,4):le_uint()
           local siP = tostring(siPrd[info]) .. " (" .. tostring(info) ..")"
           siCfgTree:add(tvbuf:range(offset,4), broadcastMsgReq.siPeriod .. siP)
           offset = offset + 4
 
           local siPduTree = siCfgTree:add_packet_field(broadcastMsgReq.siPduList, endianness)--, tvbuf:range(offset,(payLen -15) - offset))

	           info = tvbuf:range(offset,2)
	           local pduL = tvbuf:range(offset,2):le_uint()  

              local origOffset = offset;
              while offset < (origOffset + (numsgmnt + pduL + 4)) do
		           stream = " "
	              siPduTree:add_packet_field(broadcastMsgReq.pduLen, info, endianness)
	              offset = offset + 2
                 offset = offset + 2 --spare
                 offset = offset + 3 --spare

                 saveOffset = offset;
		           info = tvbuf:range(offset,pduL)
                 while offset < (saveOffset + pduL) do
		              info = tvbuf:range(offset,1):uint()
           	        local hexfmt = string.format("%x", tostring(info))
	   	           stream = stream .. " " .. tostring(hexfmt)
           	        offset = offset + 1
	              end --pduL while
                 siPduTree:add(tvbuf:range(saveOffset,pduL),broadcastMsgReq.siPdu .. stream)

		           if offset < payLen then
	                 info = tvbuf:range(offset,2)
	                 pduL = tvbuf:range(offset,2):le_uint()  
		           end -- if
	
                end --numSgmnt while

        end -- SI config while

end

function addBcastRspToTree(tvbuf, tree, offset, payLen, endianness) 

    local bMsgRspTree = tree:add(tvbuf:range(offset,4), broadcastMsgRsp)

	   info = tvbuf:range(offset,2)
	   bMsgRspTree:add_packet_field(status, info, endianness)
    	offset = offset + 2	

    	offset = offset + 2	-- no need to display spare bytes

end

function addPhyCellCfgReqToTree(tvbuf, tree, offset, payLen, endianness)

      local phycellCfgTree = tree:add(tvbuf:range(offset,payLen - PROTO_HDR_LEN), phyCellCfgReq.phy_cell_cfg_req)

	   info = tvbuf:range(offset,2)
      phycellCfgTree:add_packet_field(phyCellCfgReq.pci, info, endianness)
      offset = offset + 2

	   info = tvbuf:range(offset,2)
      phycellCfgTree:add_packet_field(phyCellCfgReq.pcfichPwrOff, info, endianness)
      offset = offset + 2

	   -- B/W Configuration 
      local phyBwCfgTree = phycellCfgTree:add(tvbuf:range(offset,16), phyCellCfgReq.bwCfg)
		   info = tvbuf:range(offset,4):le_uint()
         local bw = tostring(bwEnum[info]) .. " (" .. tostring(info) ..")"
		   phyBwCfgTree:add(tvbuf:range(offset,4), phyCellCfgReq.dlBw .. bw)
		   offset = offset + 4

		   info = tvbuf:range(offset,4):le_uint()
         bw = tostring(bwEnum[info]) .. " (" .. tostring(info) ..")"
		   phyBwCfgTree:add(tvbuf:range(offset,4), phyCellCfgReq.ulBw .. bw)
		   offset = offset + 4

		   info = tvbuf:range(offset,2)
		   phyBwCfgTree:add_packet_field(phyCellCfgReq.freqBand, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   phyBwCfgTree:add_packet_field(phyCellCfgReq.dlFreq, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   phyBwCfgTree:add_packet_field(phyCellCfgReq.ulFreq, info, endianness)
		   offset = offset + 2

		   offset = offset + 2 --spare

	   -- Tx Scheme Configuration 
      local txSchemeCfgTree = phycellCfgTree:add(tvbuf:range(offset,8), phyCellCfgReq.txSchemeCfg)

		   info = tvbuf:range(offset,4):le_uint()
         local mode = tostring(duplexMode[info]) .. " (" .. tostring(info) ..")"
		   txSchemeCfgTree:add(tvbuf:range(offset,4), phyCellCfgReq.duplex_mode .. mode)
		   offset = offset + 4

		   info = tvbuf:range(offset,2)
		   txSchemeCfgTree:add_packet_field(phyCellCfgReq.subCarSpac, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   txSchemeCfgTree:add_packet_field(phyCellCfgReq.cycPrefix, info, endianness)
		   offset = offset + 2

	   -- Antenna Configuration
      local antCfgTree = phycellCfgTree:add(tvbuf:range(offset,4), phyCellCfgReq.AntCfg)

		   info = tvbuf:range(offset,2)
		   antCfgTree:add_packet_field(phyCellCfgReq.antPort, info, endianness)
		   offset = offset + 2

		   offset = offset + 2 --spare

	   -- PRACH Configuration  
      local prachCfgTree = phycellCfgTree:add(tvbuf:range(offset,12), phyCellCfgReq.prachCfg)

		   info = tvbuf:range(offset,2)
		   prachCfgTree:add_packet_field(phyCellCfgReq.rootSeqIdx, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   prachCfgTree:add_packet_field(phyCellCfgReq.cfgIdx, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   prachCfgTree:add_packet_field(phyCellCfgReq.zeroCorrZoneCfg, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   prachCfgTree:add_packet_field(phyCellCfgReq.highSpdFlag, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   prachCfgTree:add_packet_field(phyCellCfgReq.freqoff, info, endianness)
		   offset = offset + 2

		   offset = offset + 2 --spare

	   -- PDSCH Configuration 
      local pdschCfgTree = phycellCfgTree:add(tvbuf:range(offset,4), phyCellCfgReq.pdschCfg)

		   info = tvbuf:range(offset,2)
		   pdschCfgTree:add_packet_field(phyCellCfgReq.pB, info, endianness)
		   offset = offset + 2

		   offset = offset + 2 --spare

	   -- PUSCH Configuration 
      local puschCfgTree = phycellCfgTree:add(tvbuf:range(offset,16), phyCellCfgReq.puschCfg)

		   info = tvbuf:range(offset,2)
		   puschCfgTree:add_packet_field(phyCellCfgReq.hopMode, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   puschCfgTree:add_packet_field(phyCellCfgReq.hopOff, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   puschCfgTree:add_packet_field(phyCellCfgReq.numSubBnd, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,1)
		   puschCfgTree:add_packet_field(phyCellCfgReq.enb64Qam, info, endianness)
		   offset = offset + 1

		   offset = offset + 1 --spare

	      -- UL Reference Signal Configuration 
         local ulRefSigCfgTree = puschCfgTree:add(tvbuf:range(offset,8),phyCellCfgReq.ulRefSigCfg)

			   info = tvbuf:range(offset,1)
			   ulRefSigCfgTree:add_packet_field(phyCellCfgReq.grpHopEnb, info, endianness)
			   offset = offset + 1

			   info = tvbuf:range(offset,1)
			   ulRefSigCfgTree:add_packet_field(phyCellCfgReq.seqHopEnb, info, endianness)
			   offset = offset + 1

			   info = tvbuf:range(offset,2)
		 	   ulRefSigCfgTree:add_packet_field(phyCellCfgReq.grpAssn, info, endianness)
			   offset = offset + 2

			   info = tvbuf:range(offset,2)
		 	   ulRefSigCfgTree:add_packet_field(phyCellCfgReq.cycShift, info, endianness)
			   offset = offset + 2

			   offset = offset + 2 --spare

	   -- PHICH Configuration 
      local phichCfgTree = phycellCfgTree:add(tvbuf:range(offset,12), phyCellCfgReq.phichCfg)

	      info = tvbuf:range(offset,4):le_uint()
         local duration = tostring(phichDur[info]) .. " (" .. tostring(info) .. ")"
	      phichCfgTree:add(tvbuf:range(offset,4), phichInfo.phichDuration .. duration)
    	   offset = offset + 4

		   info = tvbuf:range(offset,2)
		   phichCfgTree:add_packet_field(phyCellCfgReq.phichPwrOffset, info, endianness)
		   offset = offset + 2

	      offset = offset + 2 --spare

	      info = tvbuf:range(offset,4):le_uint()
         local phichRes = tostring(phichResEle[info]) .. " (" .. tostring(info) ..")"
		   phichCfgTree:add(tvbuf:range(offset,4), phichInfo.PhichRsrc .. phichRes)
		   offset = offset + 4

	   -- PUCCH Configuration 
      local pucchCfgTree = phycellCfgTree:add(tvbuf:range(offset,12), phyCellCfgReq.pucchCfg)

		   info = tvbuf:range(offset,2)
		   pucchCfgTree:add_packet_field(phyCellCfgReq.nRb, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   pucchCfgTree:add_packet_field(phyCellCfgReq.nCs, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   pucchCfgTree:add_packet_field(phyCellCfgReq.n1PucchAN, info, endianness)
		   offset = offset + 2

	      offset = offset + 2 --spare

		   info = tvbuf:range(offset,4):le_uint()
         local delShift = tostring(delPucchShftEnum[info]) .. " (" .. tostring(info) ..")"
		   pucchCfgTree:add(tvbuf:range(offset,4), phyCellCfgReq.delPucchShft .. delShift)
		   offset = offset + 4

	   -- SRS Configuration 
      local srsCfgTree = phycellCfgTree:add(tvbuf:range(offset,8), phyCellCfgReq.srsCfg)

		   info = tvbuf:range(offset,2)
		   srsCfgTree:add_packet_field(phyCellCfgReq.srsBw, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   srsCfgTree:add_packet_field(phyCellCfgReq.sfCfg, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   srsCfgTree:add_packet_field(phyCellCfgReq.anSimTx, info, endianness)
	   	offset = offset + 2

	      offset = offset + 2 --spare

	   -- Signal Configuration 
      local sigCfgTree = phycellCfgTree:add(tvbuf:range(offset,8), phyCellCfgReq.sigCfg)

		   info = tvbuf:range(offset,2)
		   sigCfgTree:add_packet_field(phyCellCfgReq.priSynSig, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   sigCfgTree:add_packet_field(phyCellCfgReq.secSynSig, info, endianness)
		   offset = offset + 2

		   info = tvbuf:range(offset,2)
		   sigCfgTree:add_packet_field(phyCellCfgReq.refSignPwr, info, endianness)
		   offset = offset + 2
		   offset = offset + 2 --spare

end

function addPhyCellCfgRspToTree(tvbuf, tree, offset, payLen, endianness) 

      local phyCellCfgRspTree = tree:add(tvbuf:range(offset,4), phyCellCfgRsp)

	   info = tvbuf:range(offset,2)
	   phyCellCfgRspTree:add_packet_field(status, info, endianness)
    	offset = offset + 2	
    	offset = offset + 2	-- no need to display spare bytes

end

function addRlcCellCfgReqToTree(tvbuf, tree, offset, payLen, endianness) 

      local rlcCellCfgReqTree = tree:add(tvbuf:range(offset,payLen- PROTO_HDR_LEN), rlcChnReq.rlc_cmn_chn_req)

      info = tvbuf:range(offset,1)
      local nEnt = tvbuf:range(offset,1):le_uint()
      rlcCellCfgReqTree:add_packet_field(rlcChnReq.numEnt, info, endianness)

      offset = offset + 4 -- spare

      local saveOffset = offset
      if nEnt > 0 then 
	      local entTree = rlcCellCfgReqTree:add(tvbuf:range(offset,4*nEnt), rlcChnReq.entType)-- .. ent)
         while(offset < payLen) do
            if ENC_BIG_ENDIAN ~= endianness then
	            info = tvbuf:range(offset,4):le_uint()
            else
	            info = tvbuf:range(offset,4)
            end
            local ent = tostring(rlcEntType[info]) .. " (" .. tostring(info) ..")"
            local entity = entTree:add(tvbuf:range(offset,4), ent)
            offset = offset + 4	
         end --while
      end --if

end

function addRlcCellCfgRspToTree(tvbuf, tree, offset, payLen, endianness) 

      local rlcCellCfgRspTree = tree:add(tvbuf:range(offset,payLen- PROTO_HDR_LEN), rlcChnRsp.rlc_cmn_chn_rsp)

      info = tvbuf:range(offset,1)
      rlcCellCfgRspTree:add_packet_field(rlcChnRsp.cfgStatus, info, endianness)
      offset = offset + 1 

      info = tvbuf:range(offset,1)
      local nEnt = tvbuf:range(offset,1):le_uint()
      rlcCellCfgRspTree:add_packet_field(rlcChnRsp.numEnt, info, endianness)
      offset = offset + 1 

      offset = offset + 2 -- spare

      if nEnt > 0 then
        local saveOffset = offset
        --while(offset < ((saveOffset + (4*nEnt)))) do
	     local entTree = rlcCellCfgRspTree:add(tvbuf:range(offset,4*nEnt), rlcChnRsp.failedEntType)
        while(offset < payLen) do
            if ENC_BIG_ENDIAN ~= endianness then
	            info = tvbuf:range(offset,4):le_uint()
            else
	            info = tvbuf:range(offset,4)
            end
           local ent = tostring(rlcEntType[info]) .. " (" .. tostring(info) ..")"
           entTree:add(tvbuf:range(offset,4), ent)
           offset = offset + 4	
        end --while
      end --if

end

function addRlcChnDelReqToTree(tvbuf, tree, offset, payLen, endianness) 

      local rlcChnDelReqTree = tree:add(tvbuf:range(offset,payLen- PROTO_HDR_LEN), rlcChnReq.rlc_cmn_chn_del_req)

      info = tvbuf:range(offset,1)
      local nEnt = tvbuf:range(offset,1):le_uint()
      rlcChnDelReqTree:add_packet_field(rlcChnReq.numEnt, info, endianness)

      offset = offset + 4 -- spare

      local saveOffset = offset
      if nEnt > 0 then
        --while(offset < ((saveOffset + (4*nEnt)))) do
	     local entTree = rlcChnDelReqTree:add(tvbuf:range(offset,4*nEnt), rlcChnReq.entType)
        while(offset < payLen) do
            if ENC_BIG_ENDIAN ~= endianness then
	            info = tvbuf:range(offset,4):le_uint()
            else
	            info = tvbuf:range(offset,4)
            end
           local ent = tostring(rlcEntType[info]) .. " (" .. tostring(info) ..")"
           entTree:add(tvbuf:range(offset,4),ent)
           offset = offset + 4	
        end --while
     end --if

end

function addRlcChnDelRspToTree(tvbuf, tree, offset, payLen, endianness) 

      local rlcChnDelRspTree = tree:add(tvbuf:range(offset,payLen- PROTO_HDR_LEN), rlcChnRsp.rlc_cmn_chn_del_rsp)

         info = tvbuf:range(offset,1)
         rlcChnDelRspTree:add_packet_field(rlcChnRsp.cfgStatus, info, endianness)
         offset = offset + 1 

         info = tvbuf:range(offset,1)
         local nEnt = tvbuf:range(offset,1):le_uint()
         rlcChnDelRspTree:add_packet_field(rlcChnRsp.numEnt, info, endianness)
         offset = offset + 1 

         offset = offset + 2 -- spare

         if nEnt > 0 then
            local saveOffset = offset
            local entTree = rlcChnDelRspTree:add(tvbuf:range(offset,4*nEnt), rlcChnRsp.failedEntType)
            --while(offset < ((saveOffset + (4*nEnt)))) do
            while(offset < payLen) do
               if ENC_BIG_ENDIAN ~= endianness then
	               info = tvbuf:range(offset,4):le_uint()
               else
	               info = tvbuf:range(offset,4)
               end
               local ent = tostring(rlcEntType[info]) .. " (" .. tostring(info) ..")"
               entTree:add(tvbuf:range(offset,4), ent)
               offset = offset + 4	
            end --while
         end --if

end

function addTtiIndToTree(tvbuf, tree, offset, payLen, endianness) 

      local ttiIndTree = tree:add(tvbuf:range(offset,4), ttiInd.l3TtiInd)
	      local timeInfoTree = ttiIndTree:add(tvbuf:range(offset,4),ttiInd.timinginfo)
	         info = tvbuf:range(offset,2)
	         timeInfoTree:add_packet_field(ttiInd.sfn, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,1)
	         timeInfoTree:add_packet_field(ttiInd.sf, info, endianness)
    	      offset = offset + 1	

    	      offset = offset + 1 --spare	

end

function addMacUeCfgReqToTree(tvbuf, tree, offset, payLen, endianness)

      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local ueCfgTree = tree:add(info, macUeCfgReq.mac_ue_cfg_req)

         local ueInfoTree = ueCfgTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	      info = tvbuf:range(offset,2)
	      ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	   offset = offset + 2	

	      info = tvbuf:range(offset,2)
	      ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	   offset = offset + 2

      info = tvbuf:range(offset,1)
	   ueCfgTree:add_packet_field(macUeCfgReq.ueCfgPres, info, endianness)   	 
    	offset = offset + 1
	
      info = tvbuf:range(offset,1)
	   ueCfgTree:add_packet_field(macUeCfgReq.ueCat, info, endianness)   	 
    	offset = offset + 1
	
      info = tvbuf:range(offset,1)
	   ueCfgTree:add_packet_field(macUeCfgReq.ttiBundleEnb, info, endianness)   	 
    	offset = offset + 1
	
    	offset = offset + 1 --spare
	
      local txModeCfgTree = ueCfgTree:add(tvbuf:range(offset,4),TxCfg.TransModeCfg)

	      info = tvbuf:range(offset,1)
	      txModeCfgTree:add_packet_field(TxCfg.TransModePres, info, endianness)
    	   offset = offset + 1

         if(1 == info:uint())
         then
	         info = tvbuf:range(offset,1)
	         txModeCfgTree:add_packet_field(TxCfg.TransMode, info, endianness)
    	      offset = offset + 1

    	      offset = offset + 2 --spare
         else
    	      offset = offset + 3
         end
      local cqiCfgTree = ueCfgTree:add(tvbuf:range(offset,20), dlCqiConfig.dlCqiCfg)

         local aPrdCfgTree = cqiCfgTree:add(tvbuf:range(offset,8), dlCqiConfig.aperiodicCqiCfg)

	         info = tvbuf:range(offset,1)
	         aPrdCfgTree:add_packet_field(dlCqiConfig.present, info, endianness)
    	      offset = offset + 1

    	      offset = offset + 3 --spare

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,4):le_uint()
             local transMode = tostring(CqiTransmodeAPrd[info]) .. " (" .. tostring(info) ..")"
	          aPrdCfgTree:add(tvbuf:range(offset,4), dlCqiConfig.aperiodicCqiTransMode .. transMode)
            end
    	      offset = offset + 4

         local prdCfgTree = cqiCfgTree:add(tvbuf:range(offset,12), dlCqiConfig.periodicCqiCfg)

	         info = tvbuf:range(offset,1)
	         prdCfgTree:add_packet_field(dlCqiConfig.present, info, endianness)
    	      offset = offset + 1

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          prdCfgTree:add_packet_field(dlCqiConfig.cqiPucchResIdx, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          prdCfgTree:add_packet_field(dlCqiConfig.cqiPmiCfgIdx, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          prdCfgTree:add_packet_field(dlCqiConfig.k, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,4):le_uint()
             local transMode = tostring(CqiTransmodePrd[info]) .. " (" .. tostring(info) ..")"
	          prdCfgTree:add(tvbuf:range(offset,4), dlCqiConfig.periodicCqiTransMode .. transMode)
    	       offset = offset + 4

	          info = tvbuf:range(offset,1)
	          prdCfgTree:add_packet_field(dlCqiConfig.simulAckNackAndCqi, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          prdCfgTree:add_packet_field(dlCqiConfig.riEnbFlag, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,2)
	          prdCfgTree:add_packet_field(dlCqiConfig.riCfgIdx, info, endianness)
    	       offset = offset + 2
            else
    	       offset = offset + 11 
            end

      -- UL HARQ Cfg 
      local ulHarqCfgTree = ueCfgTree:add(tvbuf:range(offset,4), ulHarqConfig.ulHarqCfg)

	      info = tvbuf:range(offset,1)
	      ulHarqCfgTree:add_packet_field(ulHarqConfig.maxUlHarqTrans, info, endianness)
    	   offset = offset + 1

    	   offset = offset + 3 --spare

      -- UE UL Power Control Cfg 
      local ulPwrCfgTree = ueCfgTree:add(tvbuf:range(offset,12), ulPwrCtrl.UeUlPwrCtrlCfg)

         --  UE PUSCH Power Control Cfg 
         local puschPwrCfgTree = ulPwrCfgTree:add(tvbuf:range(offset,4), ulPwrCtrl.UePuschPwrCtrlCfg)

	         info = tvbuf:range(offset,1)
	         puschPwrCfgTree:add_packet_field(ulPwrCtrl.present, info, endianness)
    	      offset = offset + 1

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          puschPwrCfgTree:add_packet_field(ulPwrCtrl.index, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,2)
	          puschPwrCfgTree:add_packet_field(ulPwrCtrl.tpcRnti, info, endianness)
    	       offset = offset + 2
            else
             offset = offset + 3
            end

         -- UE PUCCH Power Control Cfg 
         local pucchPwrCfgTree = ulPwrCfgTree:add(tvbuf:range(offset,8), ulPwrCtrl.UePucchPwrCtrlCfg)

	         info = tvbuf:range(offset,1)
	         pucchPwrCfgTree:add_packet_field(ulPwrCtrl.present, info, endianness)
    	      offset = offset + 1

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          pucchPwrCfgTree:add_packet_field(ulPwrCtrl.index, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,2)
	          pucchPwrCfgTree:add_packet_field(ulPwrCtrl.tpcRnti, info, endianness)
    	       offset = offset + 2

	          info = tvbuf:range(offset,1)
	          pucchPwrCfgTree:add_packet_field(ulPwrCtrl.accFlag, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          pucchPwrCfgTree:add_packet_field(ulPwrCtrl.deltaMcsFlag, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          pucchPwrCfgTree:add_packet_field(ulPwrCtrl.p0UePusch, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          pucchPwrCfgTree:add_packet_field(ulPwrCtrl.p0UePucch, info, endianness)
    	       offset = offset + 1
            else
             offset = offset + 7
            end

         --  UE Qos Cfg 
         local qosCfgTree = ueCfgTree:add(tvbuf:range(offset,12), qosCfg.UeQosCfg)

	         info = tvbuf:range(offset,1)
	         qosCfgTree:add_packet_field(qosCfg.ambrPres, info, endianness)
    	      offset = offset + 1

    	      offset = offset + 3 --spare

	         info = tvbuf:range(offset,4)
	         qosCfgTree:add_packet_field(qosCfg.dlAmbr, info, endianness)
    	      offset = offset + 4

	         info = tvbuf:range(offset,4)
	         qosCfgTree:add_packet_field(qosCfg.ulByteRate, info, endianness)
    	      offset = offset + 4

	      -- UE Ta Timer Cfg 
         local tmrCfgTree = ueCfgTree:add(tvbuf:range(offset,4), tmrCfg.UeTaTmrCfg)

	         info = tvbuf:range(offset,1)
	         tmrCfgTree:add_packet_field(tmrCfg.present, info, endianness)
    	      offset = offset + 1

    	      offset = offset + 1 --spare

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,2)
	          tmrCfgTree:add_packet_field(tmrCfg.taTimer, info, endianness)
    	       offset = offset + 2
            else
             offset = offset + 2
            end

	      -- UE Drx Cfg 
         local drxCfgTree = ueCfgTree:add(tvbuf:range(offset,20), drxCfg.UeDrxCfg)

	         info = tvbuf:range(offset,1)
	         drxCfgTree:add_packet_field(drxCfg.drxEnb, info, endianness)
    	      offset = offset + 1

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          drxCfgTree:add_packet_field(drxCfg.cqiMask, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,2)
	          drxCfgTree:add_packet_field(drxCfg.drxInactivityTmr, info, endianness)
    	       offset = offset + 2

	          info = tvbuf:range(offset,1)
	          drxCfgTree:add_packet_field(drxCfg.drxOnDurationTmr, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          drxCfgTree:add_packet_field(drxCfg.drxReTransTmr, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,2)
	          drxCfgTree:add_packet_field(drxCfg.longDrxCycle, info, endianness)
    	       offset = offset + 2

	          info = tvbuf:range(offset,2)
	          drxCfgTree:add_packet_field(drxCfg.longDrxCycStartOff, info, endianness)
    	       offset = offset + 2

    	       offset = offset + 2  --spare

	          info = tvbuf:range(offset,1)
	          drxCfgTree:add_packet_field(drxCfg.shortDrxPres, info, endianness)
    	       offset = offset + 1

    	       offset = offset + 3  --spare

	          info = tvbuf:range(offset,2)
	          drxCfgTree:add_packet_field(drxCfg.shortDrxCycle, info, endianness)
    	       offset = offset + 2

	          info = tvbuf:range(offset,2)
	          drxCfgTree:add_packet_field(drxCfg.shortDrxCycleTmr, info, endianness)
    	       offset = offset + 2
            else
             offset = offset + 19
            end

	      -- UE Meas Gap Cfg 
         local measCfgTree = ueCfgTree:add(tvbuf:range(offset,4), measCfg.ueMeasGapCfg)

	         info = tvbuf:range(offset,1)
	         measCfgTree:add_packet_field(measCfg.ueMeasGapCfgPres, info, endianness)
    	      offset = offset + 1

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          measCfgTree:add_packet_field(measCfg.gapPeriod, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          measCfgTree:add_packet_field(measCfg.gapOff, info, endianness)
    	       offset = offset + 1

    	       offset = offset + 1 --spare
            else
             offset = offset + 3
            end

	      -- Cb Subset Restrict Cfg 
         local cbsrCfgTree = ueCfgTree:add(tvbuf:range(offset,12), cbsrCfg.CbSubsetRestrictionCfg)

	         info = tvbuf:range(offset,1)
	         cbsrCfgTree:add_packet_field(cbsrCfg.CbSubsetRestrictionFlg, info, endianness)
    	      offset = offset + 1

    	      offset = offset + 3 --spare

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,4)
	          cbsrCfgTree:add_packet_field(cbsrCfg.cBitmap0, info, endianness)
    	       offset = offset + 4

	          info = tvbuf:range(offset,4)
	          cbsrCfgTree:add_packet_field(cbsrCfg.cBitmap1, info, endianness)
    	       offset = offset + 4
            else
             offset = offset + 8
            end

	      -- SRS UE Cfg 
         local srsCfgTree = ueCfgTree:add(tvbuf:range(offset,8), srsCfg.srsUeCfg)

	         info = tvbuf:range(offset,1)
	         srsCfgTree:add_packet_field(srsCfg.srsCfgFlag, info, endianness)
    	      offset = offset + 1

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          srsCfgTree:add_packet_field(srsCfg.srsCfgIndex, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          srsCfgTree:add_packet_field(srsCfg.srsBw, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          srsCfgTree:add_packet_field(srsCfg.srsHopBw, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          srsCfgTree:add_packet_field(srsCfg.srsCycShift, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          srsCfgTree:add_packet_field(srsCfg.duration, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          srsCfgTree:add_packet_field(srsCfg.transComb, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          srsCfgTree:add_packet_field(srsCfg.freqPos, info, endianness)
    	       offset = offset + 1
            else
             offset = offset + 7
            end

	      -- SR Cfg 
         local srCfgTree = ueCfgTree:add(tvbuf:range(offset,4), srConfig.srCfg)

	         info = tvbuf:range(offset,1)
	         srCfgTree:add_packet_field(srConfig.srCfgFlag, info, endianness)
    	      offset = offset + 1

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          srCfgTree:add_packet_field(srConfig.srCfgIdx, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,2)
	          srCfgTree:add_packet_field(srConfig.srResIdx, info, endianness)
    	       offset = offset + 2
            else
             offset = offset + 3
            end

	      -- Ue PUSCH Cfg 
         local puschCfgTree = ueCfgTree:add(tvbuf:range(offset,4), puschConfig.puschCfg)

	         info = tvbuf:range(offset,1)
	         puschCfgTree:add_packet_field(puschConfig.puschCfgSupport, info, endianness)
    	      offset = offset + 1
            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          puschCfgTree:add_packet_field(puschConfig.harqBetaOff, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          puschCfgTree:add_packet_field(puschConfig.riBetaOff, info, endianness)
    	       offset = offset + 1

	          info = tvbuf:range(offset,1)
	          puschCfgTree:add_packet_field(puschConfig.cqiBetaOff, info, endianness)
    	       offset = offset + 1
            else
             offset = offset + 3
            end

	      -- Ue PDSCH Cfg 
         local pdschCfgTree = ueCfgTree:add(tvbuf:range(offset,4), pdschConfig.pdschCfg)

	         info = tvbuf:range(offset,1)
	         pdschCfgTree:add_packet_field(pdschConfig.pdschPaCfgFlag, info, endianness)
    	      offset = offset + 1

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,1)
	          pdschCfgTree:add_packet_field(pdschConfig.pA, info, endianness)
    	       offset = offset + 1
            else
             offset = offset + 1
            end
    	      offset = offset + 2  --spare

         info = tvbuf:range(offset,4):le_uint()
         local rel = tostring(ueRelEnum[info]) .. " (" .. tostring(info) ..")"
	      ueCfgTree:add(tvbuf:range(offset,4), macUeCfgReq.ueRel .. rel)   	 
    	   offset = offset + 4
	
         info = tvbuf:range(offset,1)
	      ueCfgTree:add_packet_field(macUeCfgReq.numLcs, info, endianness)   	 
         local numEnt = tvbuf:range(offset,1):le_uint()
    	   offset = offset + 1
	
    	   offset = offset + 3  --spare
         if numEnt > 0 then
         -- LC Cfg 
            local lcCfgTree = ueCfgTree:add(tvbuf:range(offset,payLen-offset), lcCfg.lcConfig)
	         while (offset < payLen) do

	            info = tvbuf:range(offset,1)
	            lcCfgTree:add_packet_field(lcCfg.lcCfgType, info, endianness)
    	         offset = offset + 1

	            info = tvbuf:range(offset,1)
	            lcCfgTree:add_packet_field(lcCfg.lchId, info, endianness)
    	         offset = offset + 1

    	         offset = offset + 2  -- spare

	            info = tvbuf:range(offset,4):le_uint()
               local direction = tostring(dirEnum[info]) .. " (" .. tostring(info) ..")"
	            lcCfgTree:add(tvbuf:range(offset,4), lcCfg.dir .. direction)
    	         offset = offset + 4

	            -- UL LC Cfg 
               local ulLcCfgTree = lcCfgTree:add(tvbuf:range(offset,4),lcCfg.ulLcCfg)

	               info = tvbuf:range(offset,1)
	               ulLcCfgTree:add_packet_field(lcCfg.lcgId, info, endianness)
    	            offset = offset + 1

    	            offset = offset + 3  -- spare

	            -- DL LC Cfg 
               local dlLcCfgTree = lcCfgTree:add(tvbuf:range(offset,4), lcCfg.dlLcCfg)

	               info = tvbuf:range(offset,1)
	               dlLcCfgTree:add_packet_field(lcCfg.lchPrio, info, endianness)
    	            offset = offset + 1

    	            offset = offset + 3  -- spare

	            -- QoS Info 
               local qosInfoTree = lcCfgTree:add(tvbuf:range(offset,20), lcCfg.qosCfg)

	               info = tvbuf:range(offset,1)
	               qosInfoTree:add_packet_field(lcCfg.qci, info, endianness)
    	            offset = offset + 1

    	            offset = offset + 3  -- spare

	               -- GBR QoS Info 
                  local gbrInfoTree = qosInfoTree:add(tvbuf:range(offset,16), lcCfg.GbrQos)

	                  info = tvbuf:range(offset,4)
	                  gbrInfoTree:add_packet_field(lcCfg.eRabMaxBitRateDl, info, endianness)
    	               offset = offset + 4

	                  info = tvbuf:range(offset,4)
	                  gbrInfoTree:add_packet_field(lcCfg.eRabMaxBitRateUl, info, endianness)
    	               offset = offset + 4

	                  info = tvbuf:range(offset,4)
	                  gbrInfoTree:add_packet_field(lcCfg.eRabGrBitRateDl, info, endianness)
    	               offset = offset + 4

	                  info = tvbuf:range(offset,4)
	                  gbrInfoTree:add_packet_field(lcCfg.eRabGrBitRateUl, info, endianness)
    	               offset = offset + 4
         end --while
       end --if
end

function addMacUeCfgRspToTree(tvbuf, tree, offset, payLen, endianness)

      local info = tvbuf:range(offset,payLen - offset)
      local ueCfgRspTree = tree:add(info, mac_ue_cfg_rsp)

	   -- UE Info 
      local ueInfoTree = ueCfgRspTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	      info = tvbuf:range(offset,2)
	      ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	   offset = offset + 2	

	      info = tvbuf:range(offset,2)
	      ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	   offset = offset + 2

	   info = tvbuf:range(offset,2)
	   ueCfgRspTree:add_packet_field(status, info, endianness)
    	offset = offset + 2

    	offset = offset + 2 --spare

	   info = tvbuf:range(offset,1)
	   ueCfgRspTree:add_packet_field(numFailedEnt, info, endianness)
	   local numEnt = info:le_uint()
    	offset = offset + 1

    	offset = offset + 3 --spare
	
	   if numEnt > 0 then
         -- Failed Entities 
         local failEntTree = ueCfgRspTree:add(tvbuf:range(offset,payLen-offset), failEnt.failedEnt)
	      while (offset < payLen) do
	         info = tvbuf:range(offset,1)
	         failEntTree:add_packet_field(failEnt.lchCfgType, info, endianness)
    	      offset = offset + 1

	         info = tvbuf:range(offset,1)
	         failEntTree:add_packet_field(failEnt.lchId, info, endianness)
    	      offset = offset + 1

    	      offset = offset + 2 --spare
	      end -- while
      end -- if
end

function addMacUeReCfgReqToTree(tvbuf, tree, offset, payLen, endianness)

      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local ueReCfgTree = tree:add(info, macUeRecfgReq.mac_ue_recfg_req)


	     info = tvbuf:range(offset,2)
	     ueReCfgTree:add_packet_field(ueId.ueIdx, info, endianness)
    	  offset = offset + 2	


        info = tvbuf:range(offset,2)
	     ueReCfgTree:add_packet_field(macUeRecfgReq.oldCrnti, info, endianness)   	 
    	  offset = offset + 2

        info = tvbuf:range(offset,1)
	     ueReCfgTree:add_packet_field(macUeCfgReq.ueCat, info, endianness)   	 
    	  offset = offset + 1

        offset = offset + 1 --spare

        info = tvbuf:range(offset,2)
	     ueReCfgTree:add_packet_field(macUeRecfgReq.newCrnti, info, endianness)   	 
    	  offset = offset + 2

        info = tvbuf:range(offset,4)
	     ueReCfgTree:add_packet_field(macUeRecfgReq.bitMask, info, endianness)   	 
        offset = offset + 4

        -- Transmission Mode Cfg
        local txModeCfgTree = ueReCfgTree:add(tvbuf:range(offset,4),TxCfg.TransModeCfg)

	       info = tvbuf:range(offset,1)
	         txModeCfgTree:add_packet_field(TxCfg.TransModePres, info, endianness)
    	      offset = offset + 1

          if(1 == info:uint())
          then
	         info = tvbuf:range(offset,1)
	         txModeCfgTree:add_packet_field(TxCfg.TransMode, info, endianness)
          end
    	      offset = offset + 1
    	      offset = offset + 2 --spare

        -- DL CQI Cfg 
        local cqiCfgTree = ueReCfgTree:add(tvbuf:range(offset,20), dlCqiConfig.dlCqiCfg)

          --  Aperiodic CQI Cfg 
          local aPrdCfgTree = cqiCfgTree:add(tvbuf:range(offset,8), dlCqiConfig.aperiodicCqiCfg)

	         info = tvbuf:range(offset,1)
	         aPrdCfgTree:add_packet_field(dlCqiConfig.present, info, endianness)
    	      offset = offset + 1

    	      offset = offset + 3 --spare

            if(1 == info:uint())
            then
	          info = tvbuf:range(offset,4):le_uint()
             local transMode = tostring(CqiTransmodeAPrd[info]) .. " (" .. tostring(info) ..")"
	          aPrdCfgTree:add(tvbuf:range(offset,4), dlCqiConfig.aperiodicCqiTransMode .. transMode)
            end
    	       offset = offset + 4

          --  Periodic CQI Cfg 
          local prdCfgTree = cqiCfgTree:add(tvbuf:range(offset,12), dlCqiConfig.periodicCqiCfg)

	          info = tvbuf:range(offset,1)
	          prdCfgTree:add_packet_field(dlCqiConfig.present, info, endianness)
    	       offset = offset + 1

             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,1)
	           prdCfgTree:add_packet_field(dlCqiConfig.cqiPucchResIdx, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           prdCfgTree:add_packet_field(dlCqiConfig.cqiPmiCfgIdx, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           prdCfgTree:add_packet_field(dlCqiConfig.k, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,4):le_uint()
              local transMode = tostring(CqiTransmodePrd[info]) .. " (" .. tostring(info) ..")"
	           prdCfgTree:add(tvbuf:range(offset,4), dlCqiConfig.periodicCqiTransMode .. transMode)
    	        offset = offset + 4

	           info = tvbuf:range(offset,1)
	           prdCfgTree:add_packet_field(dlCqiConfig.simulAckNackAndCqi, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           prdCfgTree:add_packet_field(dlCqiConfig.riEnbFlag, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,2)
	           prdCfgTree:add_packet_field(dlCqiConfig.riCfgIdx, info, endianness)
    	        offset = offset + 2
             else
              offset = offset + 11
             end

         -- UL HARQ Cfg 
         local ulHarqCfgTree = ueReCfgTree:add(tvbuf:range(offset,4), ulHarqConfig.ulHarqCfg)

	          info = tvbuf:range(offset,1)
	          ulHarqCfgTree:add_packet_field(ulHarqConfig.maxUlHarqTrans, info, endianness)
    	       offset = offset + 1

    	       offset = offset + 3 --spare

         -- UE UL Power Control Cfg 
         local ulPwrCfgTree = ueReCfgTree:add(tvbuf:range(offset,12), ulPwrCtrl.UeUlPwrCtrlCfg)

             --  UE PUSCH Power Control Cfg 
             local puschPwrCfgTree = ulPwrCfgTree:add(tvbuf:range(offset,4), ulPwrCtrl.UePuschPwrCtrlCfg)

	             info = tvbuf:range(offset,1)
	             puschPwrCfgTree:add_packet_field(ulPwrCtrl.present, info, endianness)
    	          offset = offset + 1

                if(1 == info:uint())
                then
	                info = tvbuf:range(offset,1)
	                puschPwrCfgTree:add_packet_field(ulPwrCtrl.index, info, endianness)
    	             offset = offset + 1

	                info = tvbuf:range(offset,2)
	                puschPwrCfgTree:add_packet_field(ulPwrCtrl.tpcRnti, info, endianness)
    	             offset = offset + 2
                else
    	             offset = offset + 3
                end

             -- UE PUCCH Power Control Cfg 
             local pucchPwrCfgTree = ulPwrCfgTree:add(tvbuf:range(offset,8), ulPwrCtrl.UePucchPwrCtrlCfg)

	             info = tvbuf:range(offset,1)
	             pucchPwrCfgTree:add_packet_field(ulPwrCtrl.present, info, endianness)
    	          offset = offset + 1

                if(1 == info:uint())
                then
	              info = tvbuf:range(offset,1)
	              pucchPwrCfgTree:add_packet_field(ulPwrCtrl.index, info, endianness)
    	           offset = offset + 1

	              info = tvbuf:range(offset,2)
	              pucchPwrCfgTree:add_packet_field(ulPwrCtrl.tpcRnti, info, endianness)
    	           offset = offset + 2

	              info = tvbuf:range(offset,1)
	              pucchPwrCfgTree:add_packet_field(ulPwrCtrl.accFlag, info, endianness)
    	           offset = offset + 1

	              info = tvbuf:range(offset,1)
	              pucchPwrCfgTree:add_packet_field(ulPwrCtrl.deltaMcsFlag, info, endianness)
    	           offset = offset + 1

	              info = tvbuf:range(offset,1)
	              pucchPwrCfgTree:add_packet_field(ulPwrCtrl.p0UePusch, info, endianness)
    	           offset = offset + 1

	              info = tvbuf:range(offset,1)
	              pucchPwrCfgTree:add_packet_field(ulPwrCtrl.p0UePucch, info, endianness)
    	           offset = offset + 1
                else
                 offset = offset + 7
                end

         --  UE Qos Cfg 
         local qosCfgTree = ueReCfgTree:add(tvbuf:range(offset,12), qosCfg.UeQosCfg)

	          info = tvbuf:range(offset,1)
	          qosCfgTree:add_packet_field(qosCfg.ambrPres, info, endianness)
    	       offset = offset + 1

    	       offset = offset + 3 --spare

	          info = tvbuf:range(offset,4)
	          qosCfgTree:add_packet_field(qosCfg.dlAmbr, info, endianness)
    	       offset = offset + 4

	          info = tvbuf:range(offset,4)
	          qosCfgTree:add_packet_field(qosCfg.ulByteRate, info, endianness)
    	       offset = offset + 4

	      -- UE Ta Timer Cfg 
         local tmrCfgTree = ueReCfgTree:add(tvbuf:range(offset,4), tmrCfg.UeTaTmrCfg)

	          info = tvbuf:range(offset,1)
	          tmrCfgTree:add_packet_field(tmrCfg.present, info, endianness)
    	       offset = offset + 1
    	       offset = offset + 1 --spare

             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,2)
	           tmrCfgTree:add_packet_field(tmrCfg.taTimer, info, endianness)
             end 
    	       offset = offset + 2

	      -- UE Drx Cfg 
         local drxCfgTree = ueReCfgTree:add(tvbuf:range(offset,20), drxCfg.UeDrxCfg)
	          info = tvbuf:range(offset,1)
	          drxCfgTree:add_packet_field(drxCfg.drxEnb, info, endianness)
    	       offset = offset + 1
            
             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,1)
	           drxCfgTree:add_packet_field(drxCfg.cqiMask, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,2)
	           drxCfgTree:add_packet_field(drxCfg.drxInactivityTmr, info, endianness)
    	        offset = offset + 2

	           info = tvbuf:range(offset,1)
	           drxCfgTree:add_packet_field(drxCfg.drxOnDurationTmr, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           drxCfgTree:add_packet_field(drxCfg.drxReTransTmr, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,2)
	           drxCfgTree:add_packet_field(drxCfg.longDrxCycle, info, endianness)
    	        offset = offset + 2

	           info = tvbuf:range(offset,2)
	           drxCfgTree:add_packet_field(drxCfg.longDrxCycStartOff, info, endianness)
    	        offset = offset + 2

    	        offset = offset + 2  --spare

	           info = tvbuf:range(offset,1)
	           drxCfgTree:add_packet_field(drxCfg.shortDrxPres, info, endianness)
    	        offset = offset + 1

    	        offset = offset + 3  --spare

	           info = tvbuf:range(offset,2)
	           drxCfgTree:add_packet_field(drxCfg.shortDrxCycle, info, endianness)
    	        offset = offset + 2

	           info = tvbuf:range(offset,2)
	           drxCfgTree:add_packet_field(drxCfg.shortDrxCycleTmr, info, endianness)
    	        offset = offset + 2
             else
              offset = offset + 19
             end

	      -- UE Meas Gap Cfg 
         local measCfgTree = ueReCfgTree:add(tvbuf:range(offset,4), measCfg.ueMeasGapCfg)

	          info = tvbuf:range(offset,1)
	          measCfgTree:add_packet_field(measCfg.ueMeasGapCfgPres, info, endianness)
    	       offset = offset + 1

             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,1)
	           measCfgTree:add_packet_field(measCfg.gapPeriod, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           measCfgTree:add_packet_field(measCfg.gapOff, info, endianness)
    	        offset = offset + 1
    	        offset = offset + 1 --spare
             else
              offset = offset + 3
             end

	      -- Cb Subset Restrict Cfg 
         local cbsrCfgTree = ueReCfgTree:add(tvbuf:range(offset,12), cbsrCfg.CbSubsetRestrictionCfg)

	          info = tvbuf:range(offset,1)
	          cbsrCfgTree:add_packet_field(cbsrCfg.CbSubsetRestrictionFlg, info, endianness)
    	       offset = offset + 1
    	       offset = offset + 3 --spare

             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,4)
	           cbsrCfgTree:add_packet_field(cbsrCfg.cBitmap0, info, endianness)
    	        offset = offset + 4

	           info = tvbuf:range(offset,4)
	           cbsrCfgTree:add_packet_field(cbsrCfg.cBitmap1, info, endianness)
    	        offset = offset + 4
             else
              offset = offset + 8
             end

	      -- SRS UE Cfg 
         local srsCfgTree = ueReCfgTree:add(tvbuf:range(offset,8), srsCfg.srsUeCfg)

	          info = tvbuf:range(offset,1)
	          srsCfgTree:add_packet_field(srsCfg.srsCfgFlag, info, endianness)
    	       offset = offset + 1

             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,1)
	           srsCfgTree:add_packet_field(srsCfg.srsCfgIndex, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           srsCfgTree:add_packet_field(srsCfg.srsBw, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           srsCfgTree:add_packet_field(srsCfg.srsHopBw, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           srsCfgTree:add_packet_field(srsCfg.srsCycShift, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           srsCfgTree:add_packet_field(srsCfg.duration, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           srsCfgTree:add_packet_field(srsCfg.transComb, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           srsCfgTree:add_packet_field(srsCfg.freqPos, info, endianness)
    	        offset = offset + 1
             else
              offset = offset + 7
             end

	      -- SR Cfg 
         local srCfgTree = ueReCfgTree:add(tvbuf:range(offset,4), srConfig.srCfg)

	          info = tvbuf:range(offset,1)
	          srCfgTree:add_packet_field(srConfig.srCfgFlag, info, endianness)
    	       offset = offset + 1

             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,1)
	           srCfgTree:add_packet_field(srConfig.srCfgIdx, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,2)
	           srCfgTree:add_packet_field(srConfig.srResIdx, info, endianness)
    	        offset = offset + 2
             else
              offset = offset + 3
             end

	      -- Ue PUSCH Cfg 
         local puschCfgTree = ueReCfgTree:add(tvbuf:range(offset,4), puschConfig.puschCfg)

	          info = tvbuf:range(offset,1)
	          puschCfgTree:add_packet_field(puschConfig.puschCfgSupport, info, endianness)
    	       offset = offset + 1

             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,1)
	           puschCfgTree:add_packet_field(puschConfig.harqBetaOff, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           puschCfgTree:add_packet_field(puschConfig.riBetaOff, info, endianness)
    	        offset = offset + 1

	           info = tvbuf:range(offset,1)
	           puschCfgTree:add_packet_field(puschConfig.cqiBetaOff, info, endianness)
    	        offset = offset + 1
             else
              offset = offset + 3
             end

	      -- Ue PDSCH Cfg 
         local pdschCfgTree = ueReCfgTree:add(tvbuf:range(offset,4), pdschConfig.pdschCfg)

	          info = tvbuf:range(offset,1)
	          pdschCfgTree:add_packet_field(pdschConfig.pdschPaCfgFlag, info, endianness)
    	       offset = offset + 1

             if(1 == info:uint())
             then
	           info = tvbuf:range(offset,1)
	           pdschCfgTree:add_packet_field(pdschConfig.pA, info, endianness)
             end
    	       offset = offset + 1
    	       offset = offset + 2  --spare

         info = tvbuf:range(offset,1)
      	ueReCfgTree:add_packet_field(macUeCfgReq.ttiBundleEnb, info, endianness)   	 
      	offset = offset + 1
	
         info = tvbuf:range(offset,1)
      	ueReCfgTree:add_packet_field(macUeCfgReq.numLcs, info, endianness)   	 
         local numEnt = tvbuf:range(offset,1):le_uint()
      	offset = offset + 1
	
      	offset = offset + 2  --spare

         if numEnt > 0 then
            -- LC Cfg 
            local lcCfgTree = ueReCfgTree:add(tvbuf:range(offset,payLen-offset), lcCfg.lcConfig)

	          while (offset < payLen) do
	             info = tvbuf:range(offset,1)
	             lcCfgTree:add_packet_field(lcCfg.lcCfgType, info, endianness)
    	          offset = offset + 1

	             info = tvbuf:range(offset,1)
	             lcCfgTree:add_packet_field(lcCfg.lchId, info, endianness)
    	          offset = offset + 1
    	          offset = offset + 2  -- spare

	             info = tvbuf:range(offset,4):le_uint()
                local direction = tostring(dirEnum[info]) .. " (" .. tostring(info) ..")"
	             lcCfgTree:add(tvbuf:range(offset,4), lcCfg.dir .. direction)
    	          offset = offset + 4

	            -- UL LC Cfg 
               local ulLcCfgTree = lcCfgTree:add(tvbuf:range(offset,4),lcCfg.ulLcCfg)

	               info = tvbuf:range(offset,1)
	               ulLcCfgTree:add_packet_field(lcCfg.lcgId, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 3  -- spare

	            -- DL LC Cfg 
               local dlLcCfgTree = lcCfgTree:add(tvbuf:range(offset,4), lcCfg.dlLcCfg)

	               info = tvbuf:range(offset,1)
	               dlLcCfgTree:add_packet_field(lcCfg.lchPrio, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 3  -- spare

	            -- QoS Info 
               local qosInfoTree = lcCfgTree:add(tvbuf:range(offset,20), lcCfg.qosCfg)

	               info = tvbuf:range(offset,1)
	               qosInfoTree:add_packet_field(lcCfg.qci, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 3  -- spare

	               -- GBR QoS Info 
                  local gbrInfoTree = qosInfoTree:add(tvbuf:range(offset,16), lcCfg.GbrQos)

	                  info = tvbuf:range(offset,4)
	                  gbrInfoTree:add_packet_field(lcCfg.eRabMaxBitRateDl, info, endianness)
    	               offset = offset + 4

	                  info = tvbuf:range(offset,4)
	                  gbrInfoTree:add_packet_field(lcCfg.eRabMaxBitRateUl, info, endianness)
    	               offset = offset + 4

	                  info = tvbuf:range(offset,4)
	                  gbrInfoTree:add_packet_field(lcCfg.eRabGrBitRateDl, info, endianness)
    	               offset = offset + 4

	                  info = tvbuf:range(offset,4)
	                  gbrInfoTree:add_packet_field(lcCfg.eRabGrBitRateUl, info, endianness)
    	               offset = offset + 4
           end --while
        end --if
end

function addMacUeReCfgRspToTree(tvbuf, tree, offset, payLen, endianness)

      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local ueReCfgRspTree = tree:add(info, mac_ue_recfg_rsp)

         --  pktinfo.cols.info:set("(  UE Info  )")
         local ueInfoTree = ueReCfgRspTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

	      info = tvbuf:range(offset,2)
	      ueReCfgRspTree:add_packet_field(status, info, endianness)
    	   offset = offset + 2

    	   offset = offset + 2 --spare

	      info = tvbuf:range(offset,1)
	      ueReCfgRspTree:add_packet_field(numFailedEnt, info, endianness)
	      local numEnt = tvbuf:range(offset,1):le_uint()
    	   offset = offset + 1

    	   offset = offset + 3 --spare
	
	      if numEnt > 0 then
	         --  Failed Entities 
            local failEntTree = ueReCfgRspTree:add(tvbuf:range(offset,payLen - offset), failEnt.failedEnt)
	         while (offset < payLen) do
	            info = tvbuf:range(offset,1)
	            failEntTree:add_packet_field(failEnt.lchCfgType, info, endianness)
    	         offset = offset + 1

	            info = tvbuf:range(offset,1)
	            failEntTree:add_packet_field(failEnt.lchId, info, endianness)
    	         offset = offset + 1
    	         offset = offset + 2 --spare
	         end -- while
        end -- if
end

function addRlcUeCfgReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local rlcUeCfgTree = tree:add(info, rlc_ue_cfg_req)

         -- UE Info
         local ueInfoTree = rlcUeCfgTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

	      info = tvbuf:range(offset,1)
	      local numEnt = tvbuf:range(offset,1):le_uint()
	      rlcUeCfgTree:add_packet_field(nEnt, info, endianness)
    	   offset = offset + 1

    	   offset = offset + 3 --spare
	
	      if numEnt > 0 then
            local entInfoTree = rlcUeCfgTree:add(tvbuf:range(offset,payLen -offset), rlcEntCfg.entCfg)
	         while (offset < payLen) do

	            info = tvbuf:range(offset,4):le_uint()
               local configType = (cfgTypeEnum[info]) .. " (" .. tostring(info) ..")"
	            entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.cfgType .. configType)
    	         offset = offset + 4

               local rbInfoTree = entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.rbIdentity)
	    
	               info = tvbuf:range(offset,1)
	               rbInfoTree:add_packet_field(rlcEntCfg.rbId, info, endianness)
    	            offset = offset + 1

	               info = tvbuf:range(offset,1)
	               rbInfoTree:add_packet_field(rlcEntCfg.lcId, info, endianness)
    	            offset = offset + 1

    	            offset = offset + 2 --spare

	            info = tvbuf:range(offset,1)
	            entInfoTree:add_packet_field(rlcEntCfg.qci, info, endianness)
    	         offset = offset + 1

	            info = tvbuf:range(offset,1):le_uint()
               local mode = tostring(entModeEnum[info]) .. " (" .. tostring(info) ..")"
	            entInfoTree:add(tvbuf:range(offset,1), rlcEntCfg.entMode .. mode)
    	         offset = offset + 1

    	         offset = offset + 2 --spare

	            info = tvbuf:range(offset,4):le_uint()
               local direction = tostring(dirEnum[info]) .. " (" .. tostring(info) ..")"
	            entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.dir .. direction)
    	         offset = offset + 4

               local umModeTree = entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.unAckModeCfg)
	    
	               info = tvbuf:range(offset,1)
	               umModeTree:add_packet_field(rlcEntCfg.dlSn, info, endianness)
    	            offset = offset + 1

	               info = tvbuf:range(offset,1)
	               umModeTree:add_packet_field(rlcEntCfg.ulSn, info, endianness)
    	            offset = offset + 1

	               info = tvbuf:range(offset,1)
	               umModeTree:add_packet_field(rlcEntCfg.reOrdTmr, info, endianness)
    	            offset = offset + 1

    	            offset = offset + 1 --spare

               local amModeTree = entInfoTree:add(tvbuf:range(offset,12), rlcEntCfg.ackModeCfg)
	    
	               info = tvbuf:range(offset,2)
	               amModeTree:add_packet_field(rlcEntCfg.pollReTxTmr, info, endianness)
    	            offset = offset + 2

	               info = tvbuf:range(offset,2)
	               amModeTree:add_packet_field(rlcEntCfg.pollPdu, info, endianness)
    	            offset = offset + 2

	               info = tvbuf:range(offset,1)
	               amModeTree:add_packet_field(rlcEntCfg.maxReTx, info, endianness)
    	            offset = offset + 1

    	            offset = offset + 1 --spare

	               info = tvbuf:range(offset,2)
	               amModeTree:add_packet_field(rlcEntCfg.pollByte, info, endianness)
    	            offset = offset + 2

	               info = tvbuf:range(offset,1)
	               amModeTree:add_packet_field(rlcEntCfg.reorderTmr, info, endianness)
    	            offset = offset + 1

    	            offset = offset + 1 --spare

	               info = tvbuf:range(offset,2)
	               amModeTree:add_packet_field(rlcEntCfg.statusTmr, info, endianness)
    	            offset = offset + 2
	         end -- while
	      end --if
end

function addRlcUeCfgRspToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local rlcUeCfgRspTree = tree:add(info, rlc_ue_cfg_rsp)

         local ueInfoTree = rlcUeCfgRspTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

	      info = tvbuf:range(offset,1)
	      rlcUeCfgRspTree:add_packet_field(status, info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      local numEnt = tvbuf:range(offset,1):le_uint()
	      rlcUeCfgRspTree:add_packet_field(nEnt, info, endianness)
    	   offset = offset + 1

    	   offset = offset + 2 --spare

	      if numEnt > 0 then
            local entInfoTree = rlcUeCfgRspTree:add(tvbuf:range(offset,payLen-offset), entCfm)
	         while (offset < payLen) do
               local rbInfoTree = entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.rbIdentity)
	    
	               info = tvbuf:range(offset,1)
	               rbInfoTree:add_packet_field(rlcEntCfg.rbId, info, endianness)
    	            offset = offset + 1

	               info = tvbuf:range(offset,1)
	               rbInfoTree:add_packet_field(rlcEntCfg.lcId, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 2 --spare

	         info = tvbuf:range(offset,1):le_uint()
            local configType = (cfgTypeEnum[info]) .. " (" .. tostring(info) ..")"
	         entInfoTree:add(tvbuf:range(offset,1), rlcEntCfg.cfgType .. configType)
    	      offset = offset + 1
    	      offset = offset + 3 --spare
	      end -- while
	   end -- if
end

function addRlcUeReCfgReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local rlcUeReCfgTree = tree:add(info, rlc_ue_recfg_req)

         -- UE Info
         local ueInfoTree = rlcUeReCfgTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

         info = tvbuf:range(offset,2)
         rlcUeReCfgTree:add_packet_field(rlcEntCfg.reCfgBitMask, info, endianness)
    	   offset = offset + 2

         info = tvbuf:range(offset,2)
         rlcUeReCfgTree:add_packet_field(rlc.newCrnti, info, endianness)
    	   offset = offset + 2

	      info = tvbuf:range(offset,1)
	      local numEnt = tvbuf:range(offset,1):le_uint()
	      rlcUeReCfgTree:add_packet_field(nEnt, info, endianness)
    	   offset = offset + 1

    	   offset = offset + 3 --spare
	
	      if numEnt > 0 then
	      while (offset < payLen) do
            local entInfoTree = rlcUeReCfgTree:add(tvbuf:range(offset,payLen -offset), rlcEntCfg.entCfg)

	            info = tvbuf:range(offset,4):le_uint()
               local configType = (cfgTypeEnum[info]) .. " (" .. tostring(info) ..")"
	            entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.cfgType .. configType)
    	         offset = offset + 4

               local rbInfoTree = entInfoTree:add(rlcEntCfg.rbIdentity)
	    
	               info = tvbuf:range(offset,1)
	               rbInfoTree:add_packet_field(rlcEntCfg.rbId, info, endianness)
    	            offset = offset + 1

	               info = tvbuf:range(offset,1)
	               rbInfoTree:add_packet_field(rlcEntCfg.lcId, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 2 --spare

	            info = tvbuf:range(offset,1)
	            entInfoTree:add_packet_field(rlcEntCfg.qci, info, endianness)
    	         offset = offset + 1

	            info = tvbuf:range(offset,1):le_uint()
               local mode = tostring(entModeEnum[info]) .. " (" .. tostring(info) ..")"
	            entInfoTree:add(tvbuf:range(offset,1), rlcEntCfg.entMode .. mode)
    	         offset = offset + 1
    	         offset = offset + 2 --spare

	            info = tvbuf:range(offset,4):le_uint()
               local direction = tostring(dirEnum[info]) .. " (" .. tostring(info) ..")"
	            entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.dir .. direction)
    	         offset = offset + 4

               local umModeTree = entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.unAckModeCfg)
	    
	               info = tvbuf:range(offset,1)
	               umModeTree:add_packet_field(rlcEntCfg.dlSn, info, endianness)
    	            offset = offset + 1

	               info = tvbuf:range(offset,1)
	               umModeTree:add_packet_field(rlcEntCfg.ulSn, info, endianness)
    	            offset = offset + 1

	               info = tvbuf:range(offset,1)
	               umModeTree:add_packet_field(rlcEntCfg.reOrdTmr, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 1 --spare

               local amModeTree = entInfoTree:add(tvbuf:range(offset,12), rlcEntCfg.ackModeCfg)
	    
	               info = tvbuf:range(offset,2)
	               amModeTree:add_packet_field(rlcEntCfg.pollReTxTmr, info, endianness)
    	            offset = offset + 2

	               info = tvbuf:range(offset,2)
	               amModeTree:add_packet_field(rlcEntCfg.pollPdu, info, endianness)
    	            offset = offset + 2

	               info = tvbuf:range(offset,1)
	               amModeTree:add_packet_field(rlcEntCfg.maxReTx, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 1 --spare

	               info = tvbuf:range(offset,2)
	               amModeTree:add_packet_field(rlcEntCfg.pollByte, info, endianness)
    	            offset = offset + 2

	               info = tvbuf:range(offset,1)
	               amModeTree:add_packet_field(rlcEntCfg.reorderTmr, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 1 --spare

	               info = tvbuf:range(offset,2)
	               amModeTree:add_packet_field(rlcEntCfg.statusTmr, info, endianness)
    	            offset = offset + 2
	      end -- while
	   end --if
end
function addRlcUeReCfgRspToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local rlcUeReCfgRspTree = tree:add(info, rlc_ue_recfg_rsp)

         -- UE Info 
         local ueInfoTree = rlcUeReCfgRspTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

	      info = tvbuf:range(offset,1)
	      rlcUeReCfgRspTree:add_packet_field(status, info, endianness)
    	   offset = offset + 1

	      info = tvbuf:range(offset,1)
	      local numEnt = tvbuf:range(offset,1):le_uint()
	      rlcUeReCfgRspTree:add_packet_field(nEnt, info, endianness)
    	   offset = offset + 1

    	   offset = offset + 2 --spare

	      if numEnt > 0 then
            local entInfoTree = rlcUeReCfgRspTree:add(tvbuf:range(offset,payLen-offset), entCfm)

	         while (offset < payLen) do
               local rbInfoTree = entInfoTree:add(tvbuf:range(offset,4), rlcEntCfg.rbIdentity)
	    
	               info = tvbuf:range(offset,1)
	               rbInfoTree:add_packet_field(rlcEntCfg.rbId, info, endianness)
    	            offset = offset + 1

	               info = tvbuf:range(offset,1)
	               rbInfoTree:add_packet_field(rlcEntCfg.lcId, info, endianness)
    	            offset = offset + 1
    	            offset = offset + 2 --spare

	            info = tvbuf:range(offset,1):le_uint()
               local configType = (cfgTypeEnum[info]) .. " (" .. tostring(info) ..")"
	            entInfoTree:add(tvbuf:range(offset,1), rlcEntCfg.cfgType .. configType)
    	         offset = offset + 1
    	         offset = offset + 3 --spare
	        end -- while
	      end -- if
end

function addCcchMsgIndToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local ccchMsgIndTree = tree:add(info, rlc.rlcCcchMsgInd)

         local ueInfoTree = ccchMsgIndTree:add(tvbuf:range(offset,4),ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

	      info = tvbuf:range(offset,2)
	      local msgLen = tvbuf:range(offset,2):le_uint()
	      ccchMsgIndTree:add_packet_field(rlc.msgLen, info, endianness)
  	      offset = offset + 2

    	   offset = offset + 1 --spare

	      if msgLen > 0 then
            stream = " "	
	         local saveOffset = offset
	         while offset < payLen do
	            info = tvbuf:range(offset,1):uint()
               local hexfmt = string.format("%x", tostring(info))
	            stream = stream .. " " .. tostring(hexfmt)
               offset = offset + 1
	         end -- while
	         ccchMsgIndTree:add(tvbuf:range(saveOffset, msgLen),rlc.ccchMsg .. stream)
	      end -- if
end

function addCcchMsgReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local ccchMsgReqTree = tree:add(info, rlc.rlcCcchMsgReq)

         local ueInfoTree = ccchMsgReqTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

	      info = tvbuf:range(offset,2)
	      local msgLen = tvbuf:range(offset,2):le_uint()
	      ccchMsgReqTree:add_packet_field(rlc.msgLen, info, endianness)
  	      offset = offset + 2

    	   offset = offset + 1 --spare

	      if msgLen > 0 then
            stream = " "	
            local saveOffset = offset
	         while offset < payLen do
	            info = tvbuf:range(offset,1):uint()
               local hexfmt = string.format("%x", tostring(info))
	            stream = stream .. " " .. tostring(hexfmt)
               offset = offset + 1
	         end -- while
	         ccchMsgReqTree:add(tvbuf:range(saveOffset, msgLen),rlc.ccchMsg .. stream)
	      end -- if
end

function addPcchMsgReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local pcchMsgReqTree = tree:add(info, rlc.rlcPcchMsgReq)

	      local timeInfoTree = pcchMsgReqTree:add(tvbuf:range(offset,4),ttiInd.timinginfo)
	         info = tvbuf:range(offset,2)
	         timeInfoTree:add_packet_field(ttiInd.sfn, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,1)
	         timeInfoTree:add_packet_field(ttiInd.sf, info, endianness)
    	      offset = offset + 1	

    	      offset = offset + 1 --spare	--sri

	      info = tvbuf:range(offset,2)
	      local msgLen = tvbuf:range(offset,2):le_uint()
	      pcchMsgReqTree:add_packet_field(rlc.msgLen, info, endianness)
  	      offset = offset + 2

	      info = tvbuf:range(offset,2)
	      pcchMsgReqTree:add_packet_field(rlc.numSfn, info, endianness)
  	      offset = offset + 2

         info = tvbuf:range(offset,1)
         pcchMsgReqTree:add_packet_field(rlc.ovrWrtMsg, info, endianness) 
  	      offset = offset + 1

         offset = offset + 3  --spare

	      if msgLen > 0 then
            stream = " "	
            local saveOffset = offset
	         while offset < payLen do
	            info = tvbuf:range(offset,1)
               local hexfmt = string.format("%x", tostring(info))
	            stream = stream .. " " .. tostring(hexfmt)
               offset = offset + 1
	         end -- while
	         pcchMsgReqTree:add(tvbuf:range(saveOffset, msgLen),rlc.pcchMsg .. stream)
	      end -- if
end

function addUeIdChgReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local ueIdChgTree = tree:add(info, rlc.ueIdChngReq)

         local ueInfoTree = ueIdChgTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

         info = tvbuf:range(offset,2)
	      ueIdChgTree:add_packet_field(rlc.newCrnti, info, endianness)
    	   offset = offset + 2
    	   offset = offset + 2 --spare
end

function addUeIdChgRspToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local ueIdChgTree = tree:add(info, rlc.ueIdChngRsp)

        local ueInfoTree = ueIdChgTree:add(tvbuf:range(offset,4),ueId.ueInfo)

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	     offset = offset + 2	

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	     offset = offset + 2

      info = tvbuf:range(offset,2)
	   ueIdChgTree:add_packet_field(rlc.status, info, endianness)
    	offset = offset + 2
    	offset = offset + 2 --spare
end

function addSduStatusIndToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local sduStatusIndTree = tree:add(info, l2ul2l.sduStatusInd)

        local ueInfoTree = sduStatusIndTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	     offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

        local rbInfoTree = sduStatusIndTree:add(tvbuf:range(offset,4), l2ul2l.rbIdentity)
	    
	        info = tvbuf:range(offset,1)
	        rbInfoTree:add_packet_field(l2ul2l.rbId, info, endianness)
    	     offset = offset + 1

	        info = tvbuf:range(offset,1)
	        rbInfoTree:add_packet_field(l2ul2l.lcId, info, endianness)
    	     offset = offset + 1

    	     offset = offset + 2 --spare

        info = tvbuf:range(offset,4)
	     local nSdu = info:le_uint()
        sduStatusIndTree:add_packet_field(l2ul2l.numSdu, info, endianness)
	     offset = offset + 4

	     if nSdu > 0 then
	        while (offset < payLen) do
              local sduStatusTree = sduStatusIndTree:add(tvbuf:range(offset,8), l2ul2l.sduStatus)

	              info = tvbuf:range(offset,4)
	              sduStatusTree:add_packet_field(l2ul2l.sduId, info, endianness)
	              offset = offset + 4

	              info = tvbuf:range(offset,1)
	              sduStatusTree:add_packet_field(l2ul2l.status, info, endianness)
	              offset = offset + 1
	               offset = offset + 3 --spare
	        end -- while
	     end -- if
end

function addPdcpMsgIndToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local pdcpMsgIndTree = tree:add(info, l2ul2l.pdcpMsgInd)

        local ueInfoTree = pdcpMsgIndTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	     offset = offset + 2	

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	     offset = offset + 2

        local rbInfoTree = pdcpMsgIndTree:add(tvbuf:range(offset,4), l2ul2l.rbIdentity)
	    
	        info = tvbuf:range(offset,1)
	        rbInfoTree:add_packet_field(l2ul2l.rbId, info, endianness)
    	     offset = offset + 1

	        info = tvbuf:range(offset,1)
	        rbInfoTree:add_packet_field(l2ul2l.lcId, info, endianness)
    	     offset = offset + 1
    	     offset = offset + 2 --spare

        info = tvbuf:range(offset,4)
	     local bLen = info:le_uint()
        pdcpMsgIndTree:add_packet_field(l2ul2l.bufLen, info, endianness)
	     offset = offset + 4

        info = tvbuf:range(offset,1)
	     pdcpMsgIndTree:add_packet_field(l2ul2l.reEstFlag, info, endianness)
	     offset = offset + 1
	     offset = offset + 3 --spare
	
	     if bLen > 0 then
        --[[
           if offset+bLen > payLen  then
           tree:add_le_proto_expert_info(ef_too_short)
           return
           end --if
        --]]
         stream = " "	
         local saveOffset = offset
	      while offset < payLen do
	         info = tvbuf:range(offset,1):uint()
            local hexfmt = string.format("%x", tostring(info))
	         stream = stream .. " " .. tostring(hexfmt)
            offset = offset + 1
	      end -- while
	      pdcpMsgIndTree:add(tvbuf:range(saveOffset, bLen), l2ul2l.dataBuf .. stream)
        end  --if
end

function addrlcDataMsgReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local rlcDatMsgReqTree = tree:add(info, l2ul2l.rlcDatMsgReq)

        local ueInfoTree = rlcDatMsgReqTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

        local rbInfoTree = rlcDatMsgReqTree:add(tvbuf:range(offset,4), l2ul2l.rbIdentity)
	    
	         info = tvbuf:range(offset,1)
	         rbInfoTree:add_packet_field(l2ul2l.rbId, info, endianness)
    	      offset = offset + 1

	         info = tvbuf:range(offset,1)
	         rbInfoTree:add_packet_field(l2ul2l.lcId, info, endianness)
    	      offset = offset + 1

    	      offset = offset + 2 --spare

	     info = tvbuf:range(offset,4)
	     rlcDatMsgReqTree:add_packet_field(l2ul2l.sduId, info, endianness)
    	  offset = offset + 4

	     info = tvbuf:range(offset,4)
	     rlcDatMsgReqTree:add_packet_field(l2ul2l.bufLen, info, endianness)
	     local bLen = info:le_uint()
        offset = offset + 4

        local saveOffset = offset
	     if bLen > 0 then
           stream = " "	
	        while offset < payLen do
	           info = tvbuf:range(offset,1):uint()
              local hexfmt = string.format("%x", tostring(info))
	           stream = stream .. " " .. tostring(hexfmt)
              offset = offset + 1
	        end -- while
	     end -- if
	     rlcDatMsgReqTree:add(tvbuf:range(saveOffset, bLen),l2ul2l.dataBuf .. stream)
end

function addrlcDataDiscReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local rlcDatDiscReqTree = tree:add(info, l2ul2l.rlcDatDiscReq)

        local ueInfoTree = rlcDatDiscReqTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	      offset = offset + 2	

	         info = tvbuf:range(offset,2)
	         ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	      offset = offset + 2

        local rbInfoTree = rlcDatDiscReqTree:add(tvbuf:range(offset,4), l2ul2l.rbIdentity)
	    
	         info = tvbuf:range(offset,1)
	         rbInfoTree:add_packet_field(l2ul2l.rbId, info, endianness)
    	      offset = offset + 1

	         info = tvbuf:range(offset,1)
	         rbInfoTree:add_packet_field(l2ul2l.lcId, info, endianness)
    	      offset = offset + 1
    	      offset = offset + 2 --spare

        info = tvbuf:range(offset,4)
	     local nSdu = info:le_uint()
        rlcDatDiscReqTree:add(l2ul2l.numSdu, info, endianness)
	     offset = offset + 4

	     if nSdu > 0 then
	        while (offset < payLen) do
             local sduStatusTree = rlcDatDiscReqTree:add(tvbuf:range(offset,8), l2ul2l.sduStatus)

	            info = tvbuf:range(offset,4)
	            sduStatusTree:add_packet_field(l2ul2l.sduId, info, endianness)
	            offset = offset + 4

	            info = tvbuf:range(offset,1)
	            sduStatusTree:add_packet_field(l2ul2l.status, info, endianness)
	            offset = offset + 1
	            offset = offset + 3 --spare
	        end -- while
	     end -- if
end

function addMacUeDelReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local macUeDelReqTree = tree:add(info, cellUeDel.macUeDelReq)

        local ueInfoTree = macUeDelReqTree:add(tvbuf:range(offset,4),ueId.ueInfo)

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	     offset = offset + 2	

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	     offset = offset + 2
end

function addMacUeDelRspToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local macUeDelRspTree = tree:add(info, cellUeDel.macUeDelRsp)

        local ueInfoTree = macUeDelRspTree:add(tvbuf:range(offset,4), ueId.ueInfo)

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	     offset = offset + 2	

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	     offset = offset + 2

       info = tvbuf:range(offset,2)
       macUeDelRspTree:add_packet_field(status, info, endianness)
       offset = offset + 2
       offset = offset + 2 --spare
end

function addRlcUeDelReqToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local rlcUeDelReqTree = tree:add(info, cellUeDel.rlcUeDelReq)

        local ueInfoTree = rlcUeDelReqTree:add(tvbuf:range(offset,4),ueId.ueInfo)

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	     offset = offset + 2	

	        info = tvbuf:range(offset,2)
	        ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	     offset = offset + 2
end

function addRlcUeDelRspToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local rlcUeDelRspTree = tree:add(info, cellUeDel.rlcUeDelRsp)

        local ueInfoTree = rlcUeDelRspTree:add(tvbuf:range(offset,4),ueId.ueInfo)

	       info = tvbuf:range(offset,2)
	       ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	    offset = offset + 2	

	       info = tvbuf:range(offset,2)
	       ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	    offset = offset + 2

       info = tvbuf:range(offset,2)
       rlcUeDelRspTree:add_packet_field(status, info, endianness)
       offset = offset + 2
       offset = offset + 2 --spare
end

function addMacCellDelRspToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local macCellDelRspTree = tree:add(info, cellUeDel.macCellDelRsp)

        info = tvbuf:range(offset,2)
        macCellDelRspTree:add_packet_field(status, info, endianness)
        offset = offset + 2
        offset = offset + 2 --spare
end

function addPhyCellDelRspToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local phyCellDelRspTree = tree:add(info, cellUeDel.phyCellDelRsp)

       info = tvbuf:range(offset,2)
       phyCellDelRspTree:add(status, info, endianness)
       offset = offset + 2
       offset = offset + 2 --spare
end

function addL2UeRelIndToTree(tvbuf, tree, offset, payLen, endianness)
      local info = tvbuf:range(offset,payLen - PROTO_HDR_LEN)
      local ueRelIndTree = tree:add(info, rlc.l2UeRelInd)

        local ueInfoTree = ueRelIndTree:add(tvbuf:range(offset,4),ueId.ueInfo)

	       info = tvbuf:range(offset,2)
	       ueInfoTree:add_packet_field(ueId.ueIdx, info, endianness)
    	    offset = offset + 2	

	       info = tvbuf:range(offset,2)
	       ueInfoTree:add_packet_field(ueId.crnti, info, endianness)
    	    offset = offset + 2

        info = tvbuf:range(offset,4):le_uint()
        local cause = tostring(l2UeRelEnum[info]) .. " (" .. tostring(info) ..")"
	     ueRelIndTree:add(tvbuf:range(offset,4), rlc.relCause .. cause)   	 
    	  offset = offset + 4
	
end
  
----------------------------------------
-- The following creates the callback function for the dissector.
-- The 'tvbuf' is a Tvb object, 'pktinfo' is a Pinfo object, and 'root' is a TreeItem object.
-- Whenever Wireshark dissects a packet that our Protocol is hooked into, it will call
-- this function and pass it these arguments for the packet it's dissecting.
function TIP.dissector(tvbuf,pktinfo,root)

    -- set the protocol column to show our protocol name
    pktinfo.cols.protocol:set("TIP")

    -- We want to check that the packet size is rational during dissection, so let's get the length of the
    -- packet buffer (Tvb).
    local pktlen = tvbuf:reported_length_remaining()

    -- We start by adding our protocol to the dissection display tree.
    -- A call to tree:add_packet_field() returns the child created, so we can add more "under" it using that return value.
    -- The second argument is how much of the buffer/packet this added tree item covers/represents
    local offset = 0
    stream = " "
    local endianness = string.byte(string.dump(function() end),7)
    local tree = root:add(TIP, tvbuf:range(offset,pktlen))

    -- now let's check it's not too short
    if pktlen < PROTO_HDR_LEN then
        -- since we're going to add this protocol to a specific UDP port, we're going to
        -- assume packets in this port are our protocol, so the packet being too short is an error
        tree:add_le_proto_expert_info(ef_too_short)
        return
    end

    -- Now let's add our protocol header fields under the protocol tree we just created.
   
    local moduleId = tvbuf:range(offset,2):le_uint()
    local strId = tostring(modId[moduleId]) .. " (" .. tostring(moduleId) ..")"
    tree:add(tvbuf:range(offset,2), header.srcModuleId .. strId)
    offset = offset + 2	

    moduleId = tvbuf:range(offset,2):le_uint()
    local strId = tostring(modId[moduleId]) .. " (" .. tostring(moduleId) ..")"
    tree:add(tvbuf:range(offset,2), header.dstModuleId .. strId)
    offset = offset + 2	

    tree:add_packet_field(header.cellId, tvbuf:range(offset,2), endianness)
    offset = offset + 2	

    local apiId = tvbuf:range(offset,2):le_uint()
    strId = tostring(mId[apiId]) .. " (" .. tostring(apiId) ..")"
    tree:add(tvbuf:range(offset,2), header.msgId .. strId)
    offset = offset + 2	

    tree:add_packet_field(header.transId, tvbuf:range(offset,4), endianness)
    offset = offset + 4	

    tree:add_packet_field(header.payloadLen, tvbuf:range(offset,2), endianness)
    local payLen = tvbuf:range(offset,2):le_uint()
    offset = offset + 2	
    offset = offset + 2	 --spare

    -- display Message name
    pktinfo.cols.info:set(" " .. mId[apiId] .. " ")

    -- Now let's add our protocol fields under the protocol tree we just created.
    if (apiId == 301) then
      addMacCellCfgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end

    if (apiId == 302) then
      addMacCellCfgRspToTree(tvbuf, tree, offset, payLen, endianness)
    end

    if (apiId == 307) then
      addBcastMsgToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 308) then
      addBcastRspToTree(tvbuf, tree, offset, payLen, endianness) 
    end 

    if (apiId == 371) then
      addPhyCellCfgReqToTree(tvbuf, tree, offset, payLen, endianness)
   end -- if apiId == 371

   if (apiId == 372) then
      addPhyCellCfgRspToTree(tvbuf, tree, offset, payLen, endianness) 
   end

   if (apiId == 331) then
      addRlcCellCfgReqToTree(tvbuf, tree, offset, payLen, endianness) 
   end 

   if (apiId == 332) then
      addRlcCellCfgRspToTree(tvbuf, tree, offset, payLen, endianness) 
   end 

   if (apiId == 333) then
      addRlcChnDelReqToTree(tvbuf, tree, offset, payLen, endianness) 
   end 

   if (apiId == 334) then
      addRlcChnDelRspToTree(tvbuf, tree, offset, payLen, endianness) 
   end 

   if (apiId == 375) then
      addTtiIndToTree(tvbuf, tree, offset, payLen, endianness) 
    end 

    if (apiId == 309) then
      addMacUeCfgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 
  
    if (apiId == 310) then
      addMacUeCfgRspToTree(tvbuf, tree, offset, payLen, endianness)
   end 
  
    if (apiId == 311) then
      addMacUeReCfgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 312) then
      addMacUeReCfgRspToTree(tvbuf, tree, offset, payLen, endianness)
    end 
  
    if (apiId == 335) then
      addRlcUeCfgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 
  
    if (apiId == 336) then
      addRlcUeCfgRspToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 337) then
      addRlcUeReCfgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 338) then
      addRlcUeReCfgRspToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 341) then
      addCcchMsgIndToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 342) then
      addCcchMsgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 343) then
      addPcchMsgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 344) then
      addUeIdChgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 345) then
      addUeIdChgRspToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 701) then
      addSduStatusIndToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 702) then
      addPdcpMsgIndToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 703) then
      addrlcDataMsgReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 704) then
      addrlcDataDiscReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 313) then
      addMacUeDelReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 314) then
      addMacUeDelRspToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 339) then
      addRlcUeDelReqToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 340) then
      addRlcUeDelRspToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 306) then
      addMacCellDelRspToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 374) then
      addPhyCellDelRspToTree(tvbuf, tree, offset, payLen, endianness)
    end 

    if (apiId == 381) then
      addL2UeRelIndToTree(tvbuf, tree, offset, payLen, endianness)
    end 


end -- end of dissector funciton

	----------------------------------------
	-- we want to have our protocol dissection invoked for a specific UDP port,
	-- so get the udp dissector table and add our protocol to it
	DissectorTable.get("udp.port"):add(38000, TIP)
	DissectorTable.get("udp.port"):add(35000, TIP)
	DissectorTable.get("udp.port"):add(34000, TIP)
	DissectorTable.get("udp.port"):add(10140, TIP)

	-- our protocol (Proto) gets automatically registered after this script finishes loading
	----------------------------------------
