#*********************************************************************17*/
#
#/********************************************************************20**
#
#     Name:    LTE RRM 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    rmac_pycmd.py
#
#     Sid:      rmac_pycmd.py@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:27 2013
#
#     Prg:      
#
#*********************************************************************21*/
intCmdDict = { }

simpleCmdDict = {
   	'tapa.lrm.genCfgReq'  : 'Generic Config Request',
	'tapa.lrm.sapCfgReq'  : 'SAP Config Request',
	'tapa.lrm.lsapCfgReq'  : 'Lower SAP Config Request',
	'tapa.lrm.enbCfgReq'  : 'eNB Config Request',
	'tapa.lrm.cellcfgreq'  : 'Cell Config Request',
	'tapa.lrm.cpuloadind'  : 'CPU load indicaion',
   'tapa.lrm.cellUpInd'  :  'Cell Up Indication',
	'tapa.lrm.cfgCfm'  : 'Config Confirmation',
   'tapa.rgm.prbind'  : 'PRB usage Indication',
   'tapa.lrm.enbCtrlReq' :  'Control Request',
   'tapa.lrm.enbCtrlCfm' :  'Contrl Confirm',
   'tapa.rgm.prbCfgReq' :  'Prb report Cfg Request',
   'tapa.rgm.bndReq' :  'RGM Bind Request',
   'tapa.rgm.bndCfm' :  'RGM Bind Confirm',
	
	'tapa.rmu.mmeovldstart'  : 'MME Overload Start Indication',
	'tapa.rmu.mmeovldstop'  : 'MME Overload Stop Indication',
	'tapa.rmu.ueadmitreq'  : 'UE Admit Request',
	'tapa.rmu.uehoreq'  : 'UE Handover Request',
	'tapa.rmu.initcontextsetupreq'  : 'UE ICS Request',
	'tapa.rmu.erabrecfgreq'  : 'UE ERAB Reconfiguration Request',
	'tapa.rmu.uecaprecfgreq'  : 'UE Capacity Reconfiguration Request',
	'tapa.rmu.crntirecfgreq'  : 'UE Crnti Reconfiguration Request',
	'tapa.rmu.cellrecfgind'  : 'Cell Re-Configuration Indication',
        'tapa.rmu.uerelind'  : 'UE Release Indication',
        'tapa.rmu.uerelreq'  : 'UE Release Request',
        'tapa.rmu.ueadmitrsp'  : 'UE Admit Response',
        'tapa.rmu.uehorsp'  : 'UE Handover Response',
        'tapa.rmu.uerecfgrsp'  : 'UE Reconfiguration Response',
        'tapa.rmu.uerelrsp'  : 'UE Release Response',
        'tapa.rmu.spsdisind' : 'SPS Disable Indication',
        'tapa.rmu.bndreq' : 'LRM Bind Request',
        'tapa.rmu.bndcfm' : 'LRM Bind Confirm'
                      
}


#/********************************************************************30**
#
#         End of file:     rmac_pycmd.py@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:27 2013
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

