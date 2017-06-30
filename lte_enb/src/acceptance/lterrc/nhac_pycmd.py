#*********************************************************************17*/
#
#/********************************************************************20**
#
#     Name:    LTE RRC 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    nhac_pycmd.py
#
#     Sid:      nhac_pycmd.py@@/main/3 - Fri Jul  1 01:13:23 2011
#
#     Prg:      
#
#*********************************************************************21*/
intCmdDict = { }

simpleCmdDict = {
   'tapa.lnh.cfg.prot'  : 'Protocol Configuration request',
   'tapa.lnh.cfg.cfm'  : 'Configuration Confirmation',
   'tapa.lnh.sta.lsap' : 'Lower Sap Status Request for LTE-RRC',
   'tapa.lnh.sta.sys' : 'System ID Status Request for LTE-RRC',
   'tapa.lnh.cfg.prot' : 'Protocol Configuration Request for LTE-RRC',
   'tapa.lnh.sta.usap' : 'Upper Sap Status Request for LTE-RRC',
   'tapa.lnh.stacfm' : 'Status Confirmation for LTE-RRC',
   'tapa.lnh.staind' : 'Status Indication for LTE-RRC',
   'tapa.lnh.sts.gen' : 'General Statistics Request for LTE-RRC',
   'tapa.lnh.sts.peer' : 'UE Statistics Request for LTE-RRC',
   'tapa.lnh.cntrl.usta' : 'Start Control Request for LTE-RRC',
   'tapa.lnh.cfg.gen' : 'General Configuration Request for LTE-RRC',
   'tapa.lnh.sta.gen' : 'General Status Request for LTE-RRC',
   'tapa.lnh.trcind' : 'Trace Indication for LTE-RRC',
   'tapa.lnh.audtreq' : 'Audit Request for LTE-RRC',
   'tapa.lnh.cfg.cfm' : 'Configuration Confirmation for LTE-RRC',
   'tapa.lnh.cntrl.debug' : 'Debug Control Request for LTE-RRC',
   'tapa.lnh.cntrl.lsap' : 'Lsap Control Request for LTE-RRC',
   'tapa.lnh.audtcfm' : 'Audit Confirm for LTE-RRC',
   'tapa.lnh.cntrl.lsaptrc' : 'LsapTrace Control Request for LTE-RRC',
   'tapa.lnh.cntrl.usap' : 'Usap Control Request for LTE-RRC',
   'tapa.lnh.stscfm' : 'Statistics Confirmation for LTE-RRC',
   'tapa.lnh.cfg.lsap' : 'Lower SAP Configuration Request for LTE-RRC',
   'tapa.lnh.cntrl.shutdown' : 'ShutDown Control Request for LTE-RRC',
   'tapa.lnh.cntrl.start' : 'Start Control Request for LTE-RRC',
   'tapa.lnh.cfg.usap' : 'Upper SAP Configuration Request for LTE-RRC',
   'tapa.lnh.sts.cell' : 'Cell Statistics Request for LTE-RRC',
   'tapa.lnh.cntrlcfm' : 'Control Confirmation for LTE-RRC',

   'tapa.nhu.cfgreq' : 'Configuration Request',
   'tapa.nhu.cellcfgreq' : 'Cell Configuration Request',
   'tapa.nhu.cfgcfm' : 'Configuration Confirm',
   'tapa.nhu.cellcfgcfm' : 'Cell Configuration Confirm',
   'tapa.nhu.ubndreq' : 'Unbind Request',
   'tapa.nhu.datreq' : 'RRC Data Request',
   'tapa.nhu.datcfm' : 'RRC Data Confirm',
   'tapa.nhu.bndreq' : 'Bind Request',
   'tapa.nhu.datind' : 'RRC Data Indication',
   'tapa.nhu.deletetransreq' : 'Delete Transaction Request',
   'tapa.nhu.bndcfm' : 'Bind Confirm',
   'tapa.nhu.datrsp' : 'RRC Data Response',
   'tapa.nhu.cncluereq' : 'Cancel UE Request  Request',
   'tapa.nhu.errind' : 'Error Indication ',
   'tapa.nhu.staind' : 'Status Indication ',
   'tapa.nhu.countreq' : 'NHU Count Request',
   'tapa.nhu.countcfm' : 'NHU Count Confirm',
   'tapa.nhu.decodereq' : 'NHU Decode Request',
   'tapa.nhu.decodecfm' : 'NHU Decode Confirm',
   'tapa.nhu.encodereq' : 'NHU Encode Request',
   'tapa.nhu.encodecfm' : 'NHU Encode Confirm',
   'tapa.nhu.sdustareq' : 'NHU SDU Status Request',
   'tapa.nhu.sdustacfm' : 'NHU SDU Status Confirm',
   
   'tapa.dummy.pju.datcfm' : 'PJU Data Confirm',
   'tapa.dummy.pju.bndreq' : 'PJU Bind Request',
   'tapa.dummy.pju.bndcfm' : 'PJU Bind Confirm',
   'tapa.dummy.pju.datind' : 'PJU Data Indication',
   'tapa.dummy.pju.staind' : 'PJU Status Indication',
   'tapa.dummy.pju.unbndreq' : 'PJU UnBind Request',
   'tapa.dummy.pju.datreq' : 'PJU Data Request',
   
   'tapa.dummy.cpj.bndreq' : 'CPJ Bind Request',
   'tapa.dummy.cpj.bndcfm' : 'CPJ Bind Confirm',
   'tapa.dummy.cpj.unbndreq' : 'CPJ UnBind Request',
   'tapa.dummy.cpj.cfgreq' : 'CPJ Config Request',
   'tapa.dummy.cpj.cfgcfm' : 'CPJ Config Confirm',
   'tapa.dummy.cpj.ueidchngreq' : 'CPJ UE ID Change Request',
   'tapa.dummy.cpj.ueidchngcfm' : 'CPJ UE ID Change Confirm',
   'tapa.dummy.cpj.seccfgreq' : 'CPJ Security Config Request',
   'tapa.dummy.cpj.seccfgcfm' : 'CPJ Security Config Confirm',
   'tapa.dummy.cpj.cntreq' : 'CPJ Count Request',
   'tapa.dummy.cpj.cntcfm' : 'CPJ Count Confirm',
   'tapa.dummy.cpj.sdustareq' : 'CPJ SDU Status Request',
   'tapa.dummy.cpj.sdustacfm' : 'CPJ SDU Status Confirm',
   'tapa.dummy.cpj.reestreq' : 'CPJ re-establishment  Request',
   'tapa.dummy.cpj.reestcfm' : 'CPJ re-establishment Confirm',
   'tapa.dummy.cpj.pdcpdatafwdreq':'CPJ Data forward Request',
   
   'tapa.dummy.crg.bndreq' : 'CRG Bind Request',
   'tapa.dummy.crg.bndcfm' : 'CRG Bind Confirm',
   'tapa.dummy.crg.ubndreq' : 'CRG Unbind Request',
   'tapa.dummy.crg.cfgreq' : 'CRG Config Request',
   'tapa.dummy.crg.cfgcfm' : 'CRG Config Confirm',
   
   'tapa.dummy.ckw.bndreq' : 'CKW Bind Request',
   'tapa.dummy.ckw.ubndreq' : 'CKW Unbind Request',
   'tapa.dummy.ckw.bndcfm' : 'CKW Bind Confirm',
   'tapa.dummy.ckw.cfgreq' : 'CKW Config Request',
   'tapa.dummy.ckw.cfgcfm' : 'CKW Config Confirm',
   'tapa.dummy.ckw.ueidchngreq' : 'CKW UE ID Change Request',
   'tapa.dummy.ckw.ueidchngcfm' : 'CKW UE ID Change Confirm',
   
   'tapa.dummy.kwu.bndreq' : 'KWU Bind Request',
   'tapa.dummy.kwu.unbndreq' : 'KWU UnBind Request',
   'tapa.dummy.kwu.bndcfm' : 'KWU Bind Confirm',
   'tapa.dummy.kwu.datreq' : 'KWU Data Request',
   'tapa.dummy.kwu.datind' : 'KWU Data Indication to RRC',
   
   'tapa.dummy.ctf.bndreq' : 'CTF Bind Request',
   'tapa.dummy.ctf.ubndreq' : 'CTF Unbind Request',
   'tapa.dummy.ctf.bndcfm' : 'CTF Bind Confirm',
   'tapa.dummy.ctf.cfgreq' : 'CTF Config Request',
   'tapa.dummy.ctf.cfgcfm' : 'CTF Config Confirm',
   'tapa.dummy.ctf.ueidchngreq' : 'CTF UE ID Change Request',
   'tapa.dummy.ctf.ueidchngcfm' : 'CTF UE ID Change Confirm'
   
}


#/********************************************************************30**
#
#         End of file:     nhac_pycmd.py@@/main/3 - Fri Jul  1 01:13:23 2011
#
#*********************************************************************31*/
#
#/********************************************************************40**
#
#        Notes:
#
#*********************************************************************41*/
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
#   /main/3   ---     rer              1. LTE RRC Initial release. 
#   /main/3   ---     sbc              1. Updated for Release of 3.1.
#*********************************************************************91*/

