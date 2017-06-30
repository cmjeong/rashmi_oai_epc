#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    pjac_pycmd.py
#
#     Sid:      pjac_pycmd.py@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:54 2015
#
#     Prg:      
#
#*********************************************************************21*/
intCmdDict = {
   'tapa.obd.directive' : 'OBD Directive : Set',
   'tapa.pj.directive'  : 'Testcase Positive/Negative : Set',
}

simpleCmdDict = {
   'tapa.dummy.kwu.bndreq'          : 'KWU Bind Request',
   'tapa.dummy.kwu.bndcfm'          : 'KWU Bind Confirmation',
   'tapa.dummy.kwu.ubndreq'         : 'KWU Unbind Request',
   'tapa.dummy.kwu.datreq'          : 'KWU Data Request',
   'tapa.dummy.kwu.datind'          : 'KWU Data Indication',
   'tapa.dummy.kwu.datcfm'          : 'KWU Data Confirmation',
   'tapa.dummy.kwu.reestcmpind'     : 'PJU ReEst Complete Indication',
   'tapa.dummy.kwu.rxSduCreate'     : 'KWU RX Side SDU Creation',
   'tapa.dummy.kwu.rxPduCreate'     : 'KWU RX Side PDU Creation',
   'tapa.dummy.kwu.rxPdcpPduCreate' : 'KWU RX Side PDCP PDU Creation',
   'tapa.dummy.kwu.L2MUlThMeasReq'  : 'KWU L2 Measurement UL Throughput request',
   'tapa.dummy.kwu.shutdown'        : 'Cleaning up RLC buffers',
   'tapa.pjac.shutdown'             : 'XTA Shutdown',
   'tapa.dummy.kwu.discsducfm'      : 'Discard SDU Cfm from RLC',
   'tapa.pjac.chkvar'               : 'Check given variable vrMs',
   'tapa.dummy.kwu.staind'          : 'KWU Status Indication',

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
   'tapa.cpj.datresumereq' : 'CPJ Data Resume Request',
   'tapa.cpj.datresumecfm' : 'CPJ Data Resume Confirmation',
   'tapa.cpj.datforwardreq' : 'CPJ Data Forward Request',
   'tapa.cpj.datforwardcfm' : 'CPJ Data Forward Confirmation',

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
#         End of file:     pjac_pycmd.py@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:54 2015
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
#   /main/1   ---      vb      1.LTE PDCP Initial release 2.1
#*********************************************************************91*/

