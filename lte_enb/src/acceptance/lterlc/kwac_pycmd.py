#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    kwac_pycmd.py
#
#     Sid:      kwac_pycmd.py@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:09:01 2014
#
#     Prg:      
#
#*********************************************************************21*/
intCmdDict = {
   'tapa.obd.directive' : 'OBD Directive : Set',
   'tapa.pj.directive'  : 'Testcase Positive/Negative : Set',
}

simpleCmdDict = {
   'tapa.ckw.bndreq'    : 'CKW Bind Request',
   'tapa.ckw.bndcfm'    : 'CKW Bind Confirmation',
   'tapa.ckw.ubndreq'   : 'CKW Unbind Request',
   'tapa.ckw.cfgreq'    : 'CKW Configuration Request',
   'tapa.ckw.cfgcfm'    : 'CKW Configuration Confirmation',
   'tapa.ckw.ueidchgreq': 'CKW UeId Change Request',
   'tapa.ckw.ueidchgcfm': 'CKW UeId Change Confirmation',
   'tapa.ckw.mapdlul'   : 'CKW DL and UL mapping',

   'tapa.kwu.bndreq'    : 'KWU Bind Request',
   'tapa.kwu.bndcfm'    : 'KWU Bind Confirmation',
   'tapa.kwu.ubndreq'   : 'KWU Unbind Request',
   'tapa.kwu.datreq'    : 'KWU Data Request',
   'tapa.kwu.datind'    : 'KWU Data Indication',
   'tapa.kwu.datcfm'    : 'KWU Data Confirmation',
   'tapa.kwu.discsdu'   : 'KWU Discard SDU',
   'tapa.kwu.staind'    : 'KWU Status Indication',
   'tapa.kwu.discsducfm': 'KWU Sdu discard confirm',
   'tapa.kwu.datackind' : 'KWU Data ack indication',

   'tapa.lkw.gencfg'    : 'General Configuration Request for LTE-RLC',
   'tapa.lkw.sapcfg'    : 'SAP Configuration Request for LTE-RLC',
   'tapa.lkw.cfgcfm'    : 'Configuration Confirmation for LTE-RLC',
   'tapa.lkw.trccntrlreq' : 'Trace Control Request for LTE-RLC',
   'tapa.lkw.dbgcntrlreq' : 'Debug Control Request for LTE-RLC',
   'tapa.lkw.sapcntrlreq' : 'SAP Control Request for LTE-RLC',
   'tapa.lkw.cntrlcfm'    : 'SAP Control Confirm for LTE-RLC',
   'tapa.lkw.stsreq'    :  'Statistics Request for LTE-RLC',
   'tapa.lkw.stscfm'    :  'Statistics Confirmation for LTE-RLC',
   'tapa.lkw.stareq'    :  'Status Request for LTE-RLC',
   'tapa.lkw.stacfm'    :  'Status Confirmation for LTE-RLC',
   'tapa.lkw.staind'    :  'Status Indication for LTE-RLC',
   'tapa.lkw.trcind'    :  'Trace Indication for LTE-RLC',
   'tapa.lkw.cntrlshutdown'      :  'Control Request to Shutdown the RLC',
   'tapa.lkw.ustacntrlreq'    : 'USta control request ',
   'tapa.lkw.l2measreq'    : ' L2 Measurement request',
   'tapa.lkw.l2meascfm'    : ' L2 Measurement confirm',


   'tapa.dummy.rgu.bndreq'          : 'RGU Bind Request',
   'tapa.dummy.rgu.bndcfm'          : 'RGU Bind Confirmation',
   'tapa.dummy.rgu.ubndreq'         : 'RGU Unbind Request',
   'tapa.dummy.rgu.cdatreq'         : 'RGU Common Channel Data Request',
   'tapa.dummy.rgu.cdatind'         : 'RGU Common Channel Data Indication',
   'tapa.dummy.rgu.ddatreq'         : 'RGU Dedicated Channel Data Request',
   'tapa.dummy.rgu.ddatind'         : 'RGU Dedicated Channel Data Indication',
   'tapa.dummy.rgu.cstaind'         : 'RGU Common Channel Status Indication',
   'tapa.dummy.rgu.dstaind'         : 'RGU Dedicated Status Indication',
   'tapa.dummy.rgu.cstarsp'         : 'RGU Common Channel Status Response',
   'tapa.dummy.rgu.dstarsp'         : 'RGU Dedicated Status Response',
   'tapa.dummy.rgu.rxSduCreate'     : 'RGU RX Side SDU Creation',
   'tapa.dummy.rgu.rxPduCreate'     : 'RGU RX Side PDU Creation',
   'tapa.dummy.rgu.rxPdcpPduCreate' : 'RGU RX Side PDCP PDU Creation',
   'tapa.dummy.rgu.hqstaind'        : 'RGU Harq status indication',
   'tapa.dummy.rgu.L2MUlThMeasReq'  : 'RGU L2 Measurement UL Throughput request',
   'tapa.kwac.shutdown'             : 'XTA Shutdown',
   'tapa.kwac.chkvar'               : 'Check given variable vrMs',

   'SKIP'                        : 'Skip the present Step',

   'tapa.cpj.bndreq'    : 'CPJ Bind Request',
   'tapa.cpj.bndcfm'    : 'CPJ Bind Confirmation',
   'tapa.cpj.ubndreq'   : 'CPJ Unbind Request',
   'tapa.cpj.cfgreq'    : 'CPJ Configuration Request',
   'tapa.cpj.cfgcfm'    : 'CPJ Configuration Confirmation',
   'tapa.cpj.reestreq'  : 'CPJ Re-establishment Request',
   'tapa.cpj.reestcfm'  : 'CPJ Re-establishment Confirmation',
   'tapa.cpj.seccfgreq' : 'CPJ Security Configuration Request',
   'tapa.cpj.seccfgcfm' : 'CPJ Security Configuration Confirmation',
   'tapa.cpj.ueidchgreq': 'CPJ UeId Change Request',
   'tapa.cpj.ueidchgcfm': 'CPJ UeId Change Confirmation',
   'tapa.cpj.countreq'  : 'CPJ Count Request',
   'tapa.cpj.countcfm'  : 'CPJ Count Confirmation',
   'tapa.cpj.sdustareq' : 'CPJ SDU Status Report Request',
   'tapa.cpj.sdustacfm' : 'CPJ SDU Status Report Confirmation',

   'tapa.pju.bndreq'    : 'PJU Bind Request',
   'tapa.pju.bndcfm'    : 'PJU Bind Confirmation',
   'tapa.pju.ubndreq'   : 'PJU Unbind Request',
   'tapa.pju.datreq'    : 'PJU Data Request',
   'tapa.pju.datind'    : 'PJU Data Indication',
   'tapa.pju.datcfm'    : 'PJU Data Confirmation',
   'tapa.pju.discsdu'   : 'PJU Discard SDU',
   'tapa.pju.staind'    : 'PJU Status Indication',
   'tapa.pju.datfwdreq' : 'PJU Forward Request',
   'tapa.pju.datfwdind' : 'PJU Forward Indication',

   'tapa.lpj.gencfg'    : 'General Configuration Request for LTE-PDCP',
   'tapa.lpj.sapcfg'    : 'SAP Configuration Request for LTE-PDCP',
   'tapa.lpj.cfgcfm'    : 'Configuration Confirmation for LTE-PDCP',
   'tapa.lpj.trccntrlreq' : 'Trace Control Request for LTE-PDCP',
   'tapa.lpj.dbgcntrlreq' : 'Debug Control Request for LTE-PDCP',
   'tapa.lpj.sapcntrlreq' : 'SAP Control Request for LTE-PDCP',
   'tapa.lpj.cntrlcfm'    : 'SAP Control Confirm for LTE-PDCP',
   'tapa.lpj.stsreq'    :  'Statistics Request for LTE-PDCP',
   'tapa.lpj.stscfm'    :  'Statistics Confirmation for LTE-PDCP',
   'tapa.lpj.stareq'    :  'Status Request for LTE-PDCP',
   'tapa.lpj.stacfm'    :  'Status Confirmation for LTE-PDCP',
   'tapa.lpj.staind'    :  'Status Indication for LTE-PDCP',
   'tapa.lpj.trcind'    :  'Trace Indication for LTE-PDCP',
   'tapa.lpj.cntrlshutdown'      :  'Control Request to Shutdown the PDCP',
   'tapa.lpj.ustacntrlreq'    : 'USta control request PDCP',
   'tapa.lpj.l2measreq'    : ' L2 Measurement request',
   'tapa.lpj.l2meascfm'    : ' L2 Measurement confirm',
   'tapa.obd.directive'    : 'Off Board Directives',
   'tapa.obd.intProt.out'    : 'Off Board Integrity Protection cfm',
   'tapa.obd.intVer.out'    : 'Off Board Integrity Verification cfm',
   'tapa.obd.cipher.out'    : 'Off Board Cipher cfm',
   'tapa.obd.decipher.out'    : 'Off Board De Cipher cfm',
   'tapa.obd.comp.out'    : 'Off Board Compressor cfm',
   'tapa.obd.decomp.out'    : 'Off Board De Compressor cfm',
  

}


#/********************************************************************30**
#
#         End of file:     kwac_pycmd.py@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:09:01 2014
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
#   /main/1   ---      gk      1.Initial release for LTE-RLC 
#   /main/2   ---      gk      1.LTE-RLC release 2.1
#   /main/3  kw005.201 rd      1. Added cmd rgu.L2MUlThMeasReq
#*********************************************************************91*/


