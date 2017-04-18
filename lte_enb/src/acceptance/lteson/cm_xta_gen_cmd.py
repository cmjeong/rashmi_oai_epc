#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    cm_xta_gen_cmd.py
#
#     Sid:      cm_xta_gen_cmd.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:09 2015
#
#     Prg:      
#
#*********************************************************************21*/
#!/usr/bin/env python

import re
import sys
import getopt

overWrite = False


initCmd = r'''
<tapa.command id="tapa.sip.init">

   # Document subsection
   <tapa.doc>

      <tapa.desc>
         "Init SIP Stack"
      </tapa.desc>

      <tapa.longdesc/>

   </tapa.doc>

   # Steps subsection
   <tapa.steps>

      # Send General Configuration Request
      <tapa.send>
         <tapa.lso.cfg.gen/>
      </tapa.send>

      # Expect General Configuration Confirm
      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Configure TSAP (tSapId = 0) 
      <tapa.send>
         <tapa.lso.cfg.tsap tSapId="0" spId="0" type="LSO_TSAP_TYPE_TUCL"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Bind TSAP (tSapId = 0) with TUCL
      <tapa.send>
         <tapa.lso.cntrl.tsap action="ABND_ENA" tSapId="0"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cntrlcfm status="LCM_PRIM_OK"/>
      </tapa.expect>

      # Configure TSAP (tSapId = 1) 
      <tapa.send>
         <tapa.lso.cfg.tsap tSapId="1" spId="1" type="LSO_TSAP_TYPE_TUCL"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Bind TSAP (tSapId = 1) with TUCL
      <tapa.send>
         <tapa.lso.cntrl.tsap action="ABND_ENA" tSapId="1"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cntrlcfm status="LCM_PRIM_OK"/>
      </tapa.expect>

      # Configure TSAP (tSapId = 2) with SCTP
      <tapa.send>
         <tapa.lso.cfg.tsap tSapId="2" spId="2" type="LSO_TSAP_TYPE_SCTP"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Bind TSAP (tSapId = 2) with SCTP
      <tapa.send>
         <tapa.lso.cntrl.tsap action="ABND_ENA" tSapId="2"/>
      </tapa.send> 

      <tapa.expect>
         <tapa.lso.cntrlcfm/>
      </tapa.expect>   

      # Configure TSAP (tSapId = 3) 
      <tapa.send>
         <tapa.lso.cfg.tsap tSapId="3" spId="3" type="LSO_TSAP_TYPE_DTUCL"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Bind TSAP (tSapId = 3) with DTUCL
      <tapa.send>
         <tapa.lso.cntrl.tsap action="ABND_ENA" tSapId="3"/>
      </tapa.send>

      <tapa.expect>
         <tapa.hit.bndreq spId="3"/>
      </tapa.expect>

      <tapa.send>
         <tapa.hit.bndcfm suId="3"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cntrlcfm status="LCM_PRIM_OK"/>
      </tapa.expect>

      # Configure TSAP (tSapId = 4) with DSCTP
      <tapa.send>
         <tapa.lso.cfg.tsap tSapId="4" spId="4" type="LSO_TSAP_TYPE_DSCTP"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Bind TSAP (tSapId = 4) with DSCTP
      <tapa.send>
         <tapa.lso.cntrl.tsap action="ABND_ENA" tSapId="4"/>
      </tapa.send>

      <tapa.expect>
         <tapa.sct.bndreq spId="4"/>
      </tapa.expect>

      <tapa.send>
         <tapa.sct.bndcfm suId="4"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cntrlcfm/>
      </tapa.expect>   


   </tapa.steps>

</tapa.command>


<tapa.command id="tapa.sip.deinit">

   # Document subsection
   <tapa.doc>

      <tapa.desc>
         "Shutdown SIP stack" 
      </tapa.desc>

      <tapa.longdesc/>

   </tapa.doc>

   # Steps subsection
   <tapa.steps>

      # Send Shutdown
      <tapa.send>
         <tapa.lso.cntrl.shutdown/> 
      </tapa.send>

      # Expect Shutdown Control Confirm  
      <tapa.expect>
         <tapa.lso.cntrlcfm/>
      </tapa.expect>

   </tapa.steps>

</tapa.command>

'''


entCmd = r'''
<tapa.command id="tapa.sip.%s.init">

   # Document subsection
   <tapa.doc>

      <tapa.desc>
         "Init SIP Entity %s"
      </tapa.desc>

      <tapa.longdesc/>

   </tapa.doc>

   # Steps subsection
   <tapa.steps>

      # Configure SSAP 
      <tapa.send>
         <tapa.lso.cfg.ssap sSapId="%d"  entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

       # Configure SSAP 
      <tapa.send>
         <tapa.lso.cfg.ssap sSapId="%d"  entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Configure Entity UA (1)
      <tapa.send>
         <tapa.lso.cfg.entity entId="%d" >
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="1"/>
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="1"/>
            <tapa.lso.cfg.endp   endpId  ="%d" tSapId="2"/>
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="1"/>
         </tapa.lso.cfg.entity>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Send Control request for SSAP
      <tapa.send>
         <tapa.sot.bndreq spId="%d"/>
      </tapa.send>

      # Expect Control Confirm
      <tapa.expect>
         <tapa.sot.bndcfm suId="%d"/>
      </tapa.expect>

      # Send Control request for SSAP
      <tapa.send>
         <tapa.sot.bndreq spId="%d"/>
      </tapa.send>

      # Expect Control Confirm
      <tapa.expect>
         <tapa.sot.bndcfm suId="%d"/>
      </tapa.expect>

      # Enable Entity UA1
      <tapa.send>
         <tapa.lso.cntrl.entity action="AENA" entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cntrlcfm/>
      </tapa.expect>

   </tapa.steps>

</tapa.command>



<tapa.command id="tapa.sip.%s.init">

   # Document subsection
   <tapa.doc>

      <tapa.desc>
         "Init SIP Entity Dummy %s"
      </tapa.desc>

      <tapa.longdesc/>

   </tapa.doc>

   # Steps subsection
   <tapa.steps>

       # Configure SSAP  (0)
      <tapa.send>
         <tapa.lso.cfg.ssap sSapId="%d"  entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Configure SSAP  (1)
      <tapa.send>
         <tapa.lso.cfg.ssap sSapId="%d"  entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Configure Entity UA (1)
      <tapa.send>
         <tapa.lso.cfg.entity entId="%d" >
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="3"/>
         </tapa.lso.cfg.entity>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Send Control request for SSAP
      <tapa.send>
         <tapa.sot.bndreq spId="%d"/>
      </tapa.send>

      # Expect Control Confirm
      <tapa.expect>
         <tapa.sot.bndcfm suId="%d"/>
      </tapa.expect>

      # Send Control request for SSAP
      <tapa.send>
         <tapa.sot.bndreq spId="%d"/>
      </tapa.send>

      # Expect Control Confirm
      <tapa.expect>
         <tapa.sot.bndcfm suId="%d"/>
      </tapa.expect>

      # Enable Entity UA1
      <tapa.send>
         <tapa.lso.cntrl.entity action="AENA" entId="%d"/>
      </tapa.send>

      # Expect transport server open request to TUCL
      <tapa.expect> 
         <tapa.hit.servopenreq spId="3" suConId="%d"/>
      </tapa.expect>

      <tapa.send>
         <tapa.hit.concfm suId="3" suConId="%d" /> 
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cntrlcfm/>
      </tapa.expect>

   </tapa.steps>

</tapa.command>


<tapa.command id="tapa.sip.%s.init">

   # Document subsection
   <tapa.doc>

      <tapa.desc>
         "Init SIP Entity %s and Dummy %s"
      </tapa.desc>

      <tapa.longdesc/>

   </tapa.doc>

   # Steps subsection
   <tapa.steps>

      # Configure SSAP  (0)
      <tapa.send>
         <tapa.lso.cfg.ssap sSapId="%d" entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Configure SSAP  (1)
      <tapa.send>
         <tapa.lso.cfg.ssap sSapId="%d"  entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Configure Entity UA (1)
      <tapa.send>
         <tapa.lso.cfg.entity entId="%s" >
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="1"/>
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="1"/>
            <tapa.lso.cfg.endp   endpId  ="%d" tSapId="2"/>
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="1"/>
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="3"/>
         </tapa.lso.cfg.entity>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Send Control request for SSAP
      <tapa.send>
         <tapa.sot.bndreq spId="%d"/>
      </tapa.send>

      # Expect Control Confirm
      <tapa.expect>
         <tapa.sot.bndcfm suId="%d"/>
      </tapa.expect>

      # Send Control request for SSAP
      <tapa.send>
         <tapa.sot.bndreq spId="%d"/>
      </tapa.send>

      # Expect Control Confirm
      <tapa.expect>
         <tapa.sot.bndcfm suId="%d"/>
      </tapa.expect>

      # Enable Entity UA1
      <tapa.send>
         <tapa.lso.cntrl.entity action="AENA" entId="%d"/>
      </tapa.send>

       # Expect transport server open request to TUCL
      <tapa.expect> 
         <tapa.hit.servopenreq suConId="%d"/>
      </tapa.expect>

      <tapa.send>
         <tapa.hit.concfm suConId="%d" /> 
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cntrlcfm/>
      </tapa.expect>

   </tapa.steps>

</tapa.command>

<tapa.command id="tapa.sip.%s.init">

   # Document subsection
   <tapa.doc>

      <tapa.desc>
         "Init SIP Entity Dummy SCTP %s"
      </tapa.desc>

      <tapa.longdesc/>

   </tapa.doc>

   # Steps subsection
   <tapa.steps>

      # Configure Entity UA (1)
      <tapa.send>
         <tapa.lso.cfg.entity entId="%d" >
            <tapa.lso.cfg.tpt    tptSrvId="%d" tSapId="3"/>
            <tapa.lso.cfg.endp   endpId  ="%d" tSapId="4"/>
         </tapa.lso.cfg.entity>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

       # Configure SSAP  (0)
      <tapa.send>
         <tapa.lso.cfg.ssap sSapId="%d"  entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Send Control request for SSAP
      <tapa.send>
         <tapa.sot.bndreq spId="%d"/>
      </tapa.send>

      # Expect Control Confirm
      <tapa.expect>
         <tapa.sot.bndcfm suId="%d"/>
      </tapa.expect>

      # Configure SSAP  (1)
      <tapa.send>
         <tapa.lso.cfg.ssap sSapId="%d"  entId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cfgcfm/>
      </tapa.expect>

      # Send Control request for SSAP
      <tapa.send>
         <tapa.sot.bndreq spId="%d"/>
      </tapa.send>

      # Expect Control Confirm
      <tapa.expect>
         <tapa.sot.bndcfm suId="%d"/>
      </tapa.expect>

      # Enable Entity UA1
      <tapa.send>
         <tapa.lso.cntrl.entity action="AENA" entId="%d"/>
      </tapa.send>

      # Expect transport server open request to TUCL
      <tapa.expect>
         <tapa.hit.servopenreq suConId="%d"/>
      </tapa.expect>

      # Expect endpoint open request to SCTP
      <tapa.expect>
         <tapa.sct.endpopenreq suEndpId="%d"/>
      </tapa.expect>

      <tapa.send>
         <tapa.hit.concfm suConId="%d"/>
      </tapa.send>

      <tapa.send>
         <tapa.sct.endpopencfm suEndpId="%d"/>
      </tapa.send>

      <tapa.expect>
         <tapa.lso.cntrlcfm/>
      </tapa.expect>

   </tapa.steps>

</tapa.command>

'''

#
#       Fun:   writeCommands
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
def writeCommands() :
   '''Generate all the XML commands for SIP'''

   entList = []
   # Generate the list of all UAs/CSPs
   for ent in ['UA', 'SLP', 'CSP', 'TSP', 'PRX', 'SFP', 'DUMMY', 'DUMMY', 'SIPENT'] :
      for cnt in range (5):
         entList.append(ent + str(cnt + 1))

   print initCmd
   entId = 0
   for ent in entList :

      if ent[0:5] == 'DUMMY' :
         # Increment entId
         entId = entId + 1
         continue

      incEnt = entId + 1
      print entCmd % (
                      ent.lower(),
                      ent,

                      entId * 2, entId,
                      entId * 2 + 1, entId,

                      entId,
                      entId * 10 + 1,
                      entId * 10 + 2,
                      entId * 10 + 3,
                      entId * 10 + 4,

                      entId * 2, entId * 2,
                      entId * 2 + 1, entId * 2 + 1,
                      entId,




                      'd' + ent.lower(),
                      ent,

                      entId * 2, entId,
                      entId * 2 + 1, entId,

                      entId,
                      entId * 10 + 5,

                      entId * 2, entId * 2,
                      entId * 2 + 1, entId * 2 + 1,

                      entId,
                      entId * 10 + 5, entId * 10 + 5,



                      ent.lower() + '.d' + ent.lower(),
                      ent, ent,

                      entId * 2, entId,
                      entId * 2 + 1, entId,

                      entId,
                      entId * 10 + 1,
                      entId * 10 + 2,
                      entId * 10 + 3,
                      entId * 10 + 4,
                      entId * 10 + 5,

                      entId * 2, entId * 2,
                      entId * 2 + 1, entId * 2 + 1,

                      entId,
                      entId * 10 + 5,
                      entId * 10 + 5,




                      ent.lower() + '.ds' + ent.lower(),
                      ent, 
                      entId,

                      entId * 10 + 5,
                      entId * 10 + 7,

                      entId * 2, entId,
                      entId * 2, entId * 2,

                      entId * 2 + 1, entId,
                      entId * 2 + 1, entId * 2 + 1,

                      entId,

                      entId * 10 + 5,
                      entId * 10 + 7,

                      entId * 10 + 5,
                      entId * 10 + 7,

                     )

      # Increment entId
      entId = entId + 1

   return None

if __name__ == '__main__' :
   writeCommands()
   # optLst, argLst = getopt.getopt(sys.argv[1:], 'o')

   # if len(optLst) != 0 :
   #    for opt in optLst :
   #       if opt[0] == '-o' :
   #          overWrite = True

   # argc = len(argLst)

   # if argc == 0 :
   #    print "Usage: xx_gen_tc_num.py file1 .. [fileN]"
   #    sys.exit()
   # else :
   #    for elm in argLst :
   #       tstList = readXmlFiles(elm)

   #       updateXmlFiles(tstList)

   #       writeCommands(elm, tstList)



#/********************************************************************30**
#
#         End of file:     cm_xta_gen_cmd.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:09 2015
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
#/main/4      ---      sy  1. Update of sid field
#/main/5      ---      sk       1. Updated for PSF-SIP 1.1 Release
#*********************************************************************91*/
