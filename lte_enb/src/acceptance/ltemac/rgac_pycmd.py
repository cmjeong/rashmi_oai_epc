#
#/********************************************************************20**
#
#     Name:    LTEMAC 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    rgac_pycmd.py
#
#     Sid:      rgac_pycmd.py@@/main/3 - Sat Jul 30 02:21:58 2011
#     
#     Prg:      
#
#*********************************************************************21*/
intCmdDict = {
   
}

# cm_xta_pycmd_py_001.main_3:  Updated simple commands for FTHA 
simpleCmdDict = {
   'tapa.rgu.bndcfm' : 'RGU Bind Confirm',
   'tapa.rgu.cdatreq' : 'RGU Common Channel Data Request',
   'tapa.rgu.ddatind' : 'RGU Dedicated Channel Data Indication',
   'tapa.crg.cfgreq.cfg.ue' : 'CRG UE Cfg Request',
   'tapa.tfu.tti.ind' : 'TFU TTI Indication',
   'tapa.tfu.err.ind' : 'TFU ERR Indication',
   'tapa.tfu.recp.req' : 'TFU UL Reception Request',
   'tapa.tfu.hq.recp.req' : 'TFU HARQ Reception Request',
   'tapa.tfu.msg3.recp.req' : 'TFU MSG3 Reception Request',
   'tapa.tfu.pusch.recp.req' : 'TFU PUSCH Reception Request',
   'tapa.crg.cfgcfm' : 'CRG Cfg Confirm',
   'tapa.crg.cfgreq.recfg.lch' : 'CRG Logical Channel Re Cfg Request',
   'tapa.rgr.cfgreq.recfg.lch' : 'RGR Logical Channel Re Cfg Request',
   'tapa.rgr.cfgreq.recfg.lcg' : 'RGR Logical Channel Group Re Cfg Request',
   'tapa.rgr.cfgreq.UeReset' : 'RGR UE Reset Request',
   'tapa.crg.cfgreq.UeReset' : 'CRG UE Reset Request',
   'tapa.invalid' : 'Invalid Command',
   'tapa.lrg.stareq' : 'Status Request for LTE MAC',
   'tapa.rgu.cdatind' : 'RGU Common Channel Data Indication',
   'tapa.tfu.grppwrcntrl.req' : 'TFU Group Power Control Request',
   'tapa.lrg.cfg.rgrsap' : 'RGR SAP Configuration Request for LTE MAC',
   'tapa.lrg.cfg.schins' : 'RGR SAP Configuration Request for LTE MAC',
   'tapa.lrg.schcfgcfm' : 'RGR SAP Configuration Request for LTE MAC',
   'tapa.lrg.trcind' : 'Trace Indication for LTE MAC',
   'tapa.tfu.harqack.req' : 'TFU HARQ Ack Request',
   'tapa.lrg.stacfm' : 'Status Confirmation for LTE MAC',
   'tapa.lrg.staind' : 'Status Indication for LTE MAC',
   'tapa.lrg.sch.staind' : 'Status Indication for Scheduler',
   'tapa.rgr.cfgreq.cfg.cell' : 'RGR Cell Cfg Request',
   'tapa.rgr.cfgreq.cfg.lch' : 'RGR Logical Channel Cfg Request',
   'tapa.rgr.cfgreq.cfg.lcg' : 'RGR Logical Channel Group Cfg Request',
   'tapa.tfu.rareq.ind' : 'TFU Random Access Request Indication',
   'tapa.tfu.rareq' : 'TFU Random Access Request Indication',
   'tapa.tfu.rarsp.req' : 'TFU Random Access Response ',
   'tapa.rgu.dstaind' : 'RGU Dedicated Channel Status Indication',
   'tapa.tfu.raresp.req' : 'TFU Random Access Response Request',
   'tapa.crg.cfgreq.cfg.cell' : 'CRG CELL Cfg Request',
   'tapa.crg.bndreq' : 'CRG Bind Request',
   'tapa.rgm.bndreq' : 'RGM Bind Request',
   'tapa.rgm.cfgprdrprt' : 'RGM Config periodic reporting',
   'tapa.rgm.cfgprdrprtind' : 'RGM Config periodic reporting Indication',
   'tapa.tfu.bndreq' : 'TFU Bind request',
   'tapa.tfu.sch.bndreq' : 'TFU SCH Bind request',
   'tapa.tfu.cntrl.req' : 'TFU Cntrl Request',
   'tapa.tfu.cfi.cntrl.req' : 'TFU Cfi Cntrl Request',
   'tapa.tfu.phich.cntrl.req' : 'TFU PHICH Cntrl Request',
   'tapa.tfu.pdcch.cntrl.req' : 'TFU PDCCH Cntrl Request',
   'tapa.tfu.dat.req' : 'TFU Data Request',
   'tapa.tfu.bch.dat.req' : 'TFU BCH Data Request',
   'tapa.tfu.pdsch.dat.req' : 'TFU PDSCH Data Request',
   'tapa.tfu.hq.ind' : 'TFU HARQ Ack Indication',
   'tapa.tfu.hq' : 'TFU HARQ Ack Indication',
   'tapa.lrg.cntrlreq' : 'Control Request Handling for LTE MAC',
   'tapa.lrg.schcntrlreq' : 'Control Request Handling for Shecduler',
   'tapa.lrg.schcntrlcfm' : 'Control Confirm From Scheduler',
   'tapa.crg.cfgreq.cfg.lch' : 'CRG Logical Channel Cfg Request',
   'tapa.crg.ubndreq' : 'CRG UnBind Request',
   'tapa.rgr.cfgreq.recfg.cell' : 'RGR Cell ReCfg Request',
   'tapa.rgr.cfgreq.recfg.ue' : 'RGR UE ReCfg Request',
   'tapa.crg.bndcfm' : 'CRG Bind Confirm',
   'tapa.lrg.stsreq' : 'Statistics Request for LTE MAC',
   'tapa.tfu.bndcfm' : 'TFU Bind Confirm',
   'tapa.tfu.sch.bndcfm' : 'TFU SCH Bind Confirm',
   'tapa.rgu.dstarsp' : 'RGU Dedicated Channel Status Response',
   'tapa.lrg.cntrlcfm' : 'Control Confirmation for LTE MAC',
   'tapa.rgu.cstaind' : 'RGU Common Channel Status Indication',
   'tapa.re' : 'Validate Regular Expression',
   'tapa.crg.cfgreq.recfg.ue' : 'CRG UE Re Cfg Request',
   'tapa.tfu.dat.ind' : 'TFU Data Indication',
   'tapa.tfu.dat' : 'TFU Data Indication',
   'tapa.crg.cfgreq.recfg.cell' : 'CRG CELL Re Cfg Request',
   'tapa.tfu.ulcqi.ind' : 'TFU UL CQI Indication',
   'tapa.tfu.ulcqi' : 'TFU UL CQI Indication',
   'tapa.tfu.crc.ind' : 'TFU CRC Indication',
   'tapa.tfu.crc' : 'TFU CRC Indication',
   'tapa.lrg.cfgcfm' : 'Configuration Confirmation for LTE MAC',
   'tapa.lrg.stscfm' : 'Statistics Confirmation for LTE MAC',
   'tapa.tfu.dlcqi.ind' : 'TFU Downlink CQI Indication',
   'tapa.tfu.dlcqi' : 'TFU Downlink CQI Indication',
   'tapa.tfu.doa.ind' : 'TFU DOA Indication',
   'tapa.tfu.doa' : 'TFU DOA Indication',
   'tapa.rgu.hqflind' : 'RGU Harq Failure Indication',
   'tapa.tfu.timingadv.ind' : 'TFU Timing Advance Indication',
   'tapa.tfu.timingadv' : 'TFU Timing Advance Indication',
   'SKIP' : 'SKIP Validation for the Latest interface primitive',
   'tapa.tfu.ubndreq' : 'TFU UnBind request',
   'tapa.tfu.sch.ubndreq' : 'TFU SCH UnBind request',
   'tapa.rgu.cstarsp' : 'RGU Common Channel Status Response',
   'tapa.lrg.cfg.tfusap' : 'Tfu SAP Configuration Request for LTE MAC',
   'tapa.crg.cfgreq.del' : 'CRG Delete Request',
   'tapa.rgr.cfgreq.del' : 'RGR Delete Request',
   'tapa.tfu.ulgrant.req' : 'TFU UL Grant Request',
   'tapa.rgr.bndreq' : 'RGR Bind Request',
   'tapa.rgr.ubndreq' : 'RGR UnBind Request',
   'tapa.lrg.cfg.crgsap' : 'CRG SAP Configuration Request for LTE MAC',
   'tapa.rgu.ddatreq' : 'RGU Dedicated Channel Data Request',
   'tapa.rgu.bndreq' : 'RGU Bind Request',
   'tapa.rgu.ubndreq' : 'RGU Unbind Request',
   'tapa.rgr.bndcfm' : 'RGR Bind Confirm',
   'tapa.rgm.bndcfm' : 'RGM Bind Confirm',
   'tapa.lrg.cfg.rgusap' : 'RGU SAP Configuration Request for LTE MAC',
   'tapa.tfu.sr.ind' : 'TFU SR Indication',
   'tapa.tfu.sr' : 'TFU SR Indication',
   'tapa.tfu.pucchdelta.ind' : 'TFU PUCCH Delta Indication',
   'tapa.tfu.pucchdelta' : 'Single TFU PUCCH Delta Indication',
   'tapa.rgr.cfgCfm' : 'RGR Cfg Confirm',
   'tapa.rgr.tti.ind' : 'RGR TTI indication',
   'tapa.lrg.cfg.gen' : 'General Configuration Request for LTE MAC',
   'tapa.lrg.directive' : 'Command to set TC level settings',
   'tapa.tfu.cficfg.req' : 'TFU CFI Configuration Request',
   'tapa.rgr.cfgreq.cfg.ue':'RGR CFG request for UE',
   'tapa.tfu.start.tti' : 'TFU Starting Auto TTIs',
   'tapa.rgr.sicfgreq' : 'RGR SI Cfg Request',
   'tapa.rgr.sicfgcfm' : 'RGR SI Cfg Cfm',
   'tapa.rgr.warningsicfgreq' : 'RGR Warning SI Cfg Request',
   'tapa.rgr.warningsicfgcfm' : 'RGR Warning SI Cfg Cfm',
   'tapa.rgr.warningsistopreq' : 'RGR Warning SI stop req',
   'tapa.tfu.dlcqi.recp.req' : 'TFU DLCQI Reception Request',
   'tapa.tfu.sr.recp.req' : 'TFU SR Reception Request',
   'tapa.tfu.srs.recp.req' : 'TFU SRS Reception Request',
   'tapa.tfu.rawdlcqi.ind' : 'TFU Downlink Raw CQI Indication',
   'tapa.tfu.rawdlcqi' : 'Indvidual Raw CQI Indication',
   'tapa.tfu.srs.ind' : 'TFU UL SRS Indication',
   'tapa.tfu.srs' : 'Indvidual SRS Indication',
   'tapa.tfu.ul.resetrb' : 'Reset UL Rb alloc info',
   'tapa.lrg.schL2measreq':'L2 Measurement Request',
   'tapa.lrg.schL2sendmeasreq':'L2 Measurement Request',
   'tapa.lrg.schL2stopmeasreq':'L2 Measurement Request',
   'tapa.lrg.schL2meascfm':'L2 Measurement Confirm',
   'tapa.lrg.schL2stopmeascfm':'L2 Stop Measurement Confirm',
   'tapa.rgu.hqstaind':'HARQ Status Indication',
   'tapa.rgr.staind':'RGR Status Indication',
   'tapa.rgr.uestaind':'RGR UE Status Indication',
   'tapa.rgu.ulthrpmeasreq':'RGU L2M UL Throughput Meas Req',
	'tapa.rgr.loadInfInd':'RGR LoadInfo Indication',
	'tapa.rgr.loadInfReq':'RGR LoadInfo Request',
	'tapa.rgr.actDeact.scell':'RGR SCell activation Deactivation Request',
   'tapa.pfssim.cqirpt' : 'PFS simulator CQI report',
   'tapa.pfssim.dstarsp' : 'PFS simulator DSta Response',
   'tapa.rg.pfssim.boUpdt' : 'PFS Simulatoin for sending BO Update',
   'tapa.rg.pfssim.cqiCfg' : 'PFS simulator CQI  Config',
   'tapa.rg.pfssim.startsim' : 'PFS Simulation',
   'tapa.rg.pfsSim.lcData.cfg' : 'PFS Simulation LCH configuration',
   'tapa.rg.pfsSim.print' : 'PFS Simulation Print',
   'tapa.rgr.cfgreq.cfg.enb' : 'Enodeb Config Request to SCH'
}

#/********************************************************************30**
#
#         End of file:     rgac_pycmd.py@@/main/3 - Sat Jul 30 02:21:58 2011
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
#    /main/1  --     nsadar          Inital LTMAC 1.1 Release
#           rg007.201   ap  1. Added support for MIMO
#    /main/3  --    dvasisht          1. Updated for LTE MAC Release 3.1
#*********************************************************************91*/

