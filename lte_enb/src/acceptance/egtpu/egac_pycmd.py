#
#/********************************************************************20**
#
#     Name:    EGTP
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    egac_pycmd.py
#
#     Sid:      egac_pycmd.py@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:40 2015
#
#     Prg:     ad 
#
#*********************************************************************21*/
intCmdDict = {
   'tapa.timeout' : 'Expect    : No message',
   'tapa.delay' : 'Delay',
   #egac_pycmd_py_001.main_6 loop changes starts
   'tapa.repeat.start' : 'Repeat Start',
   'tapa.repeat.end' : 'Repeat End',
	#loop changes ends 
   'tapa.sip.delay' : 'SIP Delay',
   'tapa.sip.global.directive' : 'SIP Global Directive : Set',
   'tapa.global.directive' : 'Global Directive : Set',
   'tapa.directive' : 'Directive : Set',
   'tapa.memShow' : 'SSI Memory Info : Info show',
   'tapa.memLeak' : 'Memory leak info : Memory leak',
   'tapa.comment' : 'Comment',
   'tapa.mr.directive' : 'Message router Directive',
   'tapa.sip.directive' : 'SIP Directive : Set',
   'tapa.iuup.directive' : 'IUUP Directive : Set',
   'tapa.expect' : 'Expect',
   'tapa.expseq' : 'Expect a sequence of',
   'tapa.expopt' : 'Expect Optional',
   'tapa.expset' : 'Exp Set',
   'tapa.send' : 'Send',
   'tapa.sz.sct.delay'   : 'Delay if Sct interface is loosely coupled',
   'tapa.pdcp.delay' : 'PDCP Delay',
   'tapa.pdcp.global.directive' : 'PDCP Global Directive : Set',   'tapa.pdcp.directive' : 'PDCP Directive : Set',
   'tapa.pdcp.directive' : 'PDCP Directive : Set',
   'tapa.sot.cfgRegDom' : 'SOT Registrar domain configuration',
   'tapa.sot.cfgRegAuth' : 'SOT Registrar third party data base configuration',
   'tapa.sot.uncldPrim' : 'SOT SDK uncalled primitive invocation' 
}

simpleCmdDict = {
   #Added for the egtp EDM STUB module
   'tapa.edm.egmsgind' : 'EDM GTP Message Indication',
   'tapa.edm.egmsgreq' : 'EDM GTP Message Req',
   'tapa.edm.egmsgcfm' : 'EDM GTP Message Cfm',
   'tapa.edm.datind'   : 'Handler for the send the  mBuf to the decoder',
   'tapa.edm.intf.cfg' : 'Handler for configuring both ie and gm msg',
   'tapa.edm.datreq' : 'Handler for the rcv mBuf from the Encoder',
   'tapa.edm.egmsgrsp' : 'EDM GTP Message Rsp',
   'tapa.edm.errind' : 'EDM GTP Error Indication',
   'tapa.edm.cfgcfm' : 'config confirm from LM',
   'tapa.edm.ctrl.shutdown' : 'EDM Shutdown control request',
   'tapa.egt.ControlParameter' : 'set/reset general parameter',
   #Simple commands for EGTP
   'tapa.leg.cfg.gen' : 'General Configuration Request for eGTP',
   'tapa.leg.cfg.lsap' : 'Lower Sap Configuration Request for eGTP',
   'tapa.leg.cfg.usap' : 'Upper Sap Configuration Request for eGTP',
   'tapa.leg.cfg.usap.egtpu' : 'Upper Sap Configuration Request for eGTP_U',
   'tapa.leg.cfg.ipAddr' : 'IP Configuration Request for eGTP_U',
   'tapa.leg.cfg.tserver' : 'Transport server Configuration Request for eGTP',
   'tapa.leg.cfg.msgdb' : 'Message Database Configuration Request for eGTP',
   'tapa.leg.cfg.iedict' : 'IE Dictionary Configuration Request for eGTP',
   'tapa.leg.cfgcfm' : 'Configuration Confirmation from eGTP',
   'tapa.leg.sts.req' : 'Statistics Request for eGTP',
   'tapa.leg.stscfm' : 'Statistics Confirmation from eGTP',
   'tapa.leg.sta.req' : 'Status Request for eGTP',
   'tapa.leg.stacfm' : 'Status Confirmation from eGTP',
   'tapa.leg.staInd' : 'Status Indication from eGTP',
   'tapa.leg.trcInd' : 'Trace Indication from eGTP',
   'tapa.leg.cntrl.gen' : 'General Control Request for eGTP',
   'tapa.leg.cntrl.usap' : 'Upper Sap Control Request for eGTP',
   'tapa.leg.cntrl.lsap' : 'Lower Sap Control Request for eGTP',
   'tapa.leg.cntrl.tptsrv' : 'Transport Server Control Request for eGTP',
   'tapa.leg.cntrl.ipAddr' : 'IP Control Request for eGTP_U',
   'tapa.leg.cntrl.lsapTrc' : 'Lower Sap Trace Control Request for eGTP',
   'tapa.leg.cntrl.debug' : 'Debug Control Request for eGTP',
   'tapa.leg.cntrl.peer' : 'Peer Control Request for eGTP',
   'tapa.leg.cntrl.usta' : 'Unsloicited Status Control Request for eGTP',
   'tapa.leg.cntrl.cfg' : 'Unsloicited Status Control Request for eGTP',
   'tapa.leg.cntrl.shutdown' : 'ShutDown Control Request for eGTP',
   'tapa.leg.cntrlcfm' : 'Control Confirm from eGTP',
   'tapa.hit.egudatind' :'Data indication for TUCL incase of GTP-U',
   'tapa.egt.bndreq' : 'EGT Bind Request',
   'tapa.egt.bndcfm' : 'EGT Bind Confirm',
   'tapa.egt.ubndreq' : 'EGT UnBind Request',
   'tapa.egt.sigreq' : 'EGT Sig Request',
   'tapa.egt.sigrsp' : 'EGT Sig Response',
   'tapa.egt.sigind' : 'EGT Sig Indication',
   'tapa.egt.sigcfm' : 'EGT Sig Confirmation',
   'tapa.egt.stareq' : 'EGT Status Request',
   'tapa.egt.stacfm' : 'EGT Status Confirmation',
   'tapa.egt.staind' : 'EGT Status Indication',
   'tapa.egt.errind' : 'EGT Error Indication',
   'tapa.egt.lcldelreq' : 'EGT LCL Del Request',
   'tapa.egt.lcldelcfm' : 'EGT LCL Del Confirm',
    #Simple commands for eGTP-U Upper Interface(EGT)
   'tapa.egt.egudatreq' : 'Data Request for eGTP-U',
   'tapa.egt.egudatind' : 'Data Indication for eGTP-U',
   'tapa.egt.egutnlmgmtreq' : 'Local TnlMgmt Request for eGTP-U',
   'tapa.egt.egutnlmgmtcfm' : 'Local TnlMgmt Confirm for eGTP-U',
   'tapa.egt.egustareq' : 'Status Request for eGTP-U',
   'tapa.egt.egustacfm' : 'Status Confirm for eGTP-U',
   'tapa.egt.egustaind' : 'Staus Indication for eGTP-U',
   'tapa.egt.eguerrind' : 'Error Indication for eGTP-U',
#egac_pycmd_py_001.main_4 :Updated for eGTP-C PSF
#eGTP-C-PSF command
   'tapa.lhw.cfg.gen'   : 'eGTP-C-PSF General Configuration',
   'tapa.lhw.cfgcfm'   : 'eGTP-C-PSF General Configuration Confirmation',
   'tapa.lhw.psf.shutdown' : 'Send Shutdown Control request',
   'tapa.lhw.cntrlcfm' : 'eGTP-C Control Confirmation',
   'tapa.lhw.cntrl.shutdown' : 'eGTP-C-PSF Shutdown control request',
   'tapa.lhw.shcntrlcfm' : 'eGTP-C-PSF control confirm',
   'tapa.lhw.sta.gen' : 'eGTP-C-PSF Status Request',
   'tapa.lhw.stacfm' : 'eGTP-C-PSF Status Confirm',
   'tapa.lhw.cntrl.usta' : 'Unsolicited Status Request for eGTP-C PSF',
   'tapa.lhw.cntrl.debug' : 'eGTP-C Ctrl Request for Debug',
   'tapa.lhw.cntrl.trc' : 'eGTP-C Ctrl Request for Trace',
   'tapa.lhw.pi.req' : 'eGTP-C PSF PI custom request',
   'tapa.lhw.psf.updrset' : 'eGTP-C PSF validate the Number Rsets with update messages',
   'tapa.lhw.psf.updmval' : 'eGTP-C PSF validate the Number of Update messages for RT WS CS',
   'tapa.lhw.pi.rspCfm' : 'eGTP-C PSF Sending the custom Response confirmation',
   'tapa.lhw.staind' : 'eGTP-C-PSF Alarm Indication',
   'tapa.verify.standby.state' : 'eGTP-C StandBy State Verification',
   'tapa.lhw.sts.gen' : 'General Statistics Request',
   'tapa.lhw.stscfm': 'General Statistics  confirmation',
   'tapa.lhw.trcind' : 'Verify Reception of TraceIndication',
   'tapa.sht.cntrlReq' : 'Send SHT control request',
   'tapa.ManiCustmData' : 'Manipulate Custom Data',
}

#/********************************************************************30**
#
#         End of file:     egac_pycmd.py@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:40 2015
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
#  /main/1    ---     ad            1. Initial creation for EGTP Rel 1.1
#/main/3      ---   akulkarni     1. Initial release for egtpu 1.2
#/main/4      ---      pmacharla   1. Initial for eGTP release 2.1
#/main/4      egac_pycmd_py_001.main_4  magnihotri   1. Updated for eGTP-C PSF
#*********************************************************************91*/

