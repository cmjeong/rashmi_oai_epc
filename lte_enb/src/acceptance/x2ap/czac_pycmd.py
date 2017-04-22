#*********************************************************************17*/
#
#/********************************************************************20**
#
#     Name:    LTE X2AP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    czac_pycmd.py
#
#     Sid:     $SID$ 
#
#     Prg:      
#
#*********************************************************************21*/
# cz001.101   : CR Fixes.
intCmdDict = { 
   'tapa.cz.directive' : 'X2AP Directive',
}

simpleCmdDict = {
   'tapa.lcz.sta.lsap' : 'Lower Sap Status Request for LTE-X2AP',
   'tapa.lcz.sta.sys' : 'System ID Status Request for LTE-X2AP',
   'tapa.lcz.cfg.prot' : 'Protocol Configuration Request for LTE-X2AP',
   'tapa.lcz.sta.usap' : 'Upper Sap Status Request for LTE-X2AP',
   'tapa.lcz.stacfm' : 'Status Confirmation for LTE-X2AP',
   'tapa.lcz.staInd' : 'Status Indication for LTE-X2AP',
   'tapa.lcz.sts.gen' : 'General Statistics Request for LTE-X2AP',
   'tapa.lcz.sts.peer' : 'UE Statistics Request for LTE-X2AP',
   'tapa.lcz.cntrl.usta'   : 'Unsloicited Status Control Request for LTE-X2AP',
   'tapa.lcz.cfg.gen' : 'General Configuration Request for LTE-X2AP',
   'tapa.lcz.sta.gen' : 'General Status Request for LTE-X2AP',
   'tapa.lcz.trcind' : 'Trace Indication for LTE-X2AP',
   'tapa.lcz.cfg.cfm' : 'Configuration Confirmation for LTE-X2AP',
   'tapa.lcz.cntrl.debug' : 'Debug Control Request for LTE-X2AP',
   'tapa.lcz.cntrl.lSap' : 'Lsap Control Request for LTE-X2AP',
   'tapa.lcz.cntrl.lsaptrc' : 'LsapTrace Control Request for LTE-X2AP',
   'tapa.lcz.cntrl.usap' : 'Usap Control Request for LTE-X2AP',
   'tapa.lcz.stscfm' : 'Statistics Confirmation for LTE-X2AP',
   'tapa.lcz.cfg.lsap' : 'Lower SAP Configuration Request for LTE-X2AP',
   'tapa.lcz.cntrl.shutdown' : 'ShutDown Control Request for LTE-X2AP',
   'tapa.lcz.cntrl.start' : 'Start Control Request for LTE-X2AP',
   'tapa.lcz.cfg.usap' : 'Upper SAP Configuration Request for LTE-X2AP',
   'tapa.lcz.cntrlcfm' : 'Control Confirmation for LTE-X2AP',

   'tapa.czt.staind' : 'X2AP Status Indication',

   'tapa.czt.bndreq' :  'CZT Bind Request',
   'tapa.czt.bndcfm' : 'CZT Bind Confirm',
   'tapa.czt.ubndreq' : 'CZT Unbind Request',

   'tapa.czt.gpreq' : 'X2AP Global Procedure Request',
   'tapa.czt.gpind' : 'X2AP Global Procedure Indication',
   'tapa.czt.gprsp' : 'X2AP Global Procedure Response',
   'tapa.czt.gpcfm' : 'X2AP Global Procedure Confirm',
   'tapa.czt.gpretxreq' : 'X2AP Global Procedure Retransmission Request',
   'tapa.czt.gperrreq' : 'X2AP Global Procedure Error Request',
   'tapa.czt.gperrind' : 'X2AP Global Procedure Error Indication',

   'tapa.czt.bmpreq' : 'X2AP Basic Mobility Procedure Request',
   'tapa.czt.bmpind' : 'X2AP Basic Mobility Procedure Indication',
   'tapa.czt.bmprsp' : 'X2AP Basic Mobility Procedure Response',
   'tapa.czt.bmpcfm' : 'X2AP Basic Mobility Procedure Confirm',


   'tapa.dummy.sct.datcfm' : 'sct Data Confirm',
   'tapa.dummy.sct.bndreq' : 'sct Bind Request',
   'tapa.dummy.sct.bndcfm' : 'sct Bind Confirm',
   'tapa.dummy.sct.datind' : 'sct Data Indication',
   'tapa.dummy.sct.staind' : 'sct Status Indication',
   'tapa.dummy.sct.unbndreq' : 'sct UnBind Request',
   'tapa.dummy.sct.datreq' : 'sct Data Request',
   
   'tapa.lcz.cfg.peer'  :  'Peer Configuration Request for X2AP',
   'tapa.lcz.cfgcfm'    :  'Configuration Confirmation for X2AP',
   'tapa.lcz.sts.req'   :  'Statistics Request for X2AP',
   'tapa.lcz.sta.req'   :  'Status Request for X2AP',
   'tapa.lcz.cntrl.pNodeTrc'  :  'Peer Node Trace Control Request for X2AP',
   'tapa.lcz.cntrl.peer'   :  'Control Request for X2AP',
   'tapa.lcz.cntrl.assoc'   :  'Assoc Control Request for X2AP',
   'tapa.lcz.cntrl.endPt'   :  'End Point Control Request for X2AP',
   'tapa.czt.errind' :     'CZT Error Indication',
   'tapa.czt.relreq' :     'Release Request',
   'tapa.czt.relcfm' :     'Release Confirmation',
   'tapa.czt.assocind' :     'X2AP Peer Assoc Indication',
   'tapa.czt.assocrsp' :     'X2AP Peer Assoc Response',
   'tapa.czt.audreq' :     'Audit Request',
   'tapa.czt.audcfm' :     'Audit Confirmation'
   
}


#/********************************************************************30**
#
#         End of file: $SID$ 
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
#   $SID$      ---     rer           1. LTE X2AP Initial release. 
#/main/1+   cz001.101  mm       1. CR Fixes.
#   $SID$      ---     pt            1. LTE-X2AP 3.1 release.
#*********************************************************************91*/
