#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    cm_xta_gen_tc_num.py
#
#     Sid:      cm_xta_gen_tc_num.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:10 2015
#
#     Prg:      
#
#*********************************************************************21*/
#!/usr/bin/env python

import re
import sys
import getopt
from cm_xta_py import *

overWrite = False
path = 'bak/'
#
#       Fun:   readXmlFiles
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
def readXmlFiles(fileName = None) :
   '''Parse all the XML files for test groups'''

   # Read XML file
   data = open(fileName, "r").read()

   # Extract all blocks of the testcases/testgroups/commands
   pattern = r'xyzabcstart.+?xyzabcend'
   blocks = re.findall(pattern, data, re.S)

   #Raise exception if no block found
   if len(blocks) == 0 :
      raise AssertionError("No xyzabcstart block defined")

   # Create patterns for later use
   testIdPatt1 = re.compile(r'xyzabcstart=(\d+)?:(.+)?:(.+)?')

   # Extract all instances of the testcases/testgroups/commands
   tcPattern  = r'<tapa.testcase\s+id.+?>.+?</tapa.testcase>'
   tgPattern  = r'<tapa.testgroup\s+id.+?>.+?</tapa.testgroup>'
   cmdPattern = r'<tapa.command\s+id.+?>.+?</tapa.command>'

   fileDict = {}
   prgDict  = {}

   for block in blocks :
      # Match pattern
      mobj = testIdPatt1.match(block)

      # Add to fileDict if match found
      if mobj :

         tcList = re.findall(tcPattern,   block, re.S)
         tgList = re.findall(tgPattern,   block, re.S)
         cmdList = re.findall(cmdPattern, block, re.S)

         # There can be only one programmer name per file, as per standard
         # TAPA file description, take care not to move the TCs from different
         # engineers into the same file
         prgDict[mobj.group(3)] = mobj.group(2)
         if fileDict.has_key(mobj.group(3)) :
            fileDict[mobj.group(3)].append([mobj.group(1), tcList, tgList, cmdList])
         else :
            fileDict[mobj.group(3)] = [[mobj.group(1), tcList, tgList, cmdList]]
      else :
         raise AssertionError("Error in matching xyzabcstart block, RE failed")

   return [fileDict, prgDict]


#
#       Fun:   updateXmlFiles
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
def updateXmlFiles(fileDict) :
   '''Parse all the XML files for test groups'''

   for file in fileDict :

      # Find the list of blocks for this file
      list = fileDict[file]
      for block in list :
         # Get groupId and testCase Id
         #(tstGrpId, tstId) = block[0].split('.')
         #tstId = int(tstId)

         tstGrpId = block[0]

         tcList = block[1]
         tgList = block[2]

         cnt = 0
         tstId = 1

         for tst in tgList :
            
            string = r'<tapa.testgroup id="' + str(tstGrpId) + '" '
            #tst = re.sub('<tapa.testgroup\s+id\s*=\d+?\.\d+?', string, tst)
            tst = re.sub(r'<tapa.testgroup\s+id\s*=\s*"\d+?"', string, tst)

            tcList[cnt] = tst
            cnt = cnt + 1

         for tst in tcList :
            
            string = r'<tapa.testcase id="' + str(tstGrpId) + '.' + str(tstId) + '">'
            tst = re.sub(r'<tapa.testcase\s+id\s*=\s*\"\d+?\.\d+?"', string, tst)
            #tst = re.sub('<tapa.testcase\s+id.+?>', string, tst)
            #string = '<tapa.testgroup id="' + str(tstGrpId) + '">'
            #tst = re.sub('<tapa.testgroup\s+id.+?>', string, tst)
            tcList[cnt] = tst
            cnt = cnt + 1

            tstId = tstId + 1

   #print list
   return fileDict


#
#       Fun:   writeXmlFiles
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
def writeXmlFiles(fileName, tstDict) :
   '''Parse all the XML files for test groups'''

   fileDict = tstDict[0]
   prgDict  = tstDict[1]

   for file in fileDict :

      # write XML file
      if overWrite == False :
         data = open(path + file + ".bak", "w")
      else :
         data = open(path + file, "w")

      # Find the list of blocks for this file
      list = fileDict[file]

      data.write(getHeader(file, prgDict[file]))
      
      for block in list :
         tstGrpId = block[0]

         tcList = block[1]
         tgList = block[2]
         cmdList = block[3]

         data.write('\n')
         data.write('# DO NOT DELETE THIS LINE -- TC number generation script depends on it.\n')
         stri = '# xyzabcstart=' + tstGrpId + ':' + prgDict[file] + ':' + file + '\n'
         data.write(stri)

         for tst in tgList :
            
            xmlDoc = parseTestGroup(tst)

            id = str(xmlDoc[1].getAttribute('id'))

            doc = getTCDoc(xmlDoc[2])
            doc[2] = re.sub('                ', '#                ', doc[2])

            data.write(getFuncHdr(id, file, doc[1], doc[2]))
            data.write(tst)
            data.write('\n\n')

         for tst in tcList :

            xmlDoc = parseTestCase(tst)

            id = str(xmlDoc[1].getAttribute('id'))

            doc = getTCDoc(xmlDoc[2], xmlDoc[3])
            doc[2] = re.sub('                ', '#                ', doc[2])

            data.write(getFuncHdr(id, file, doc[1], doc[2]))
            data.write(tst)
            data.write('\n\n')

         for cmd in cmdList :

            xmlDoc = parseCommand(cmd)

            id = str(xmlDoc[1].getAttribute('id'))

            #doc = getTCDoc(xmlDoc[2], xmlDoc[3])
            descNode = xmlDoc[2].getElementsByTagName('tapa.desc')[0]

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

               #doc = doc + line + '\n'
               if doc == None :
                  doc = line + '\n'
               else :
                  doc = doc + '#                ' + line + '\n'
               cnt = cnt + 1

            doc.strip()
            doc = doc[:-1]

            data.write(getFuncHdr(id, file, 'None', doc))
            data.write(cmd)
            data.write('\n\n')

         data.write('\n')
         data.write('# DO NOT DELETE THIS LINE -- TC number generation script depends on it.\n')
         stri = '# xyzabcend' + '\n'
         data.write(stri)

      data.write(getFooter())

   return None 

#
#       Fun:   getFuncHdr
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
def getFuncHdr(id, file, module, desc) :
   '''Parse all the XML files for test groups'''

   funcHdr = r'''
#
#
#       Test:    %s
#
#       Desc:    %s
#
#       Notes:   None
#              
#       Module:  %s
#
#       File:    %s
#
#
''' % (id, desc, module, file)

   return funcHdr 




   

#
#       Fun:   getHeader
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
def getHeader(fileName, prgName) :
   '''Parse all the XML files for test groups'''

   fileHdr = r'''#/********************************************************************16**
#
#                         (c) COPYRIGHT 1989-2005 by 
#                         Continuous Computing Corporation.
#                         All rights reserved.
#
#     This software is confidential and proprietary to Continuous Computing 
#     Corporation (CCPU).  No part of this software may be reproduced,
#     stored, transmitted, disclosed or used in any form or by any means
#     other than as expressly provided by the written Software License 
#     Agreement between CCPU and its licensee.
#
#     CCPU warrants that for a period, as provided by the written
#     Software License Agreement between CCPU and its licensee, this
#     software will perform substantially to CCPU specifications as
#     published at the time of shipment, exclusive of any updates or 
#     upgrades, and the media used for delivery of this software will be 
#     free from defects in materials and workmanship.  CCPU also warrants 
#     that has the corporate authority to enter into and perform under the   
#     Software License Agreement and it is the copyright owner of the software 
#     as originally delivered to its licensee.
#
#     CCPU MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
#     WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
#     A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED
#     MATERIALS.
#
#     IN NO EVENT SHALL CCPU BE LIABLE FOR ANY INDIRECT, SPECIAL,
#     CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
#     OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
#     ON BREACH OF CONTRACT, TORT (INCLUDING NEGLIGENCE), PRODUCT
#     LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED
#     OF THE POSSIBILITY OF SUCH DAMAGE.
#
#                       Restricted Rights Legend
#
#     This software and all related materials licensed hereby are
#     classified as "restricted computer software" as defined in clause
#     52.227-19 of the Federal Acquisition Regulation ("FAR") and were
#     developed entirely at private expense for nongovernmental purposes,
#     are commercial in nature and have been regularly used for
#     nongovernmental purposes, and, to the extent not published and
#     copyrighted, are trade secrets and confidential and are provided
#     with all rights reserved under the copyright laws of the United
#     States.  The government's rights to the software and related
#     materials are limited and restricted as provided in clause
#     52.227-19 of the FAR.
#
#                    IMPORTANT LIMITATION(S) ON USE
#
#     The use of this software is limited to the use set
#     forth in the written Software License Agreement between CCPU and
#     its Licensee. Among other things, the use of this software
#     may be limited to a particular type of Designated Equipment, as 
#     defined in such Software License Agreement.
#     Before any installation, use or transfer of this software, please
#     consult the written Software License Agreement or contact CCPU at
#     the location set forth below in order to confirm that you are
#     engaging in a permissible use of the software.
#
#                    Continuous Computing Corporation
#                    9380, Carroll Park Drive
#                    San Diego, CA-92121, USA
#
#                    Tel: +1 (858) 882 8800
#                    Fax: +1 (858) 777 3388
#
#                    Email: support@trillium.com
#                    Web: http://www.ccpu.com
#
#*********************************************************************17*/
#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    XML Test File
#
#     Desc:    XML Based Test Cases
#
#     File:    %s
#
#     Sid:      cm_xta_gen_tc_num.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:10 2015
#
#     Prg:     %s 
#
#*********************************************************************21*/
''' % (fileName, prgName)

   return fileHdr

#
#       Fun:   getFooter
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
def getFooter() :
   '''Parse all the XML files for test groups'''

   fileFooter = r'''
#/********************************************************************30**
#
#         End of file:     cm_xta_gen_tc_num.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:10 2015
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
#/main/5      ---      sy  1. Update of sid field
#*********************************************************************91*/
'''

   return fileFooter


if __name__ == '__main__' :
   optLst, argLst = getopt.getopt(sys.argv[1:], 'o')

   if len(optLst) != 0 :
      for opt in optLst :
         if opt[0] == '-o' :
            overWrite = True

   argc = len(argLst)

   if argc == 0 :
      print "Usage: xx_gen_tc_num.py file1 .. [fileN]"
      sys.exit()
   else :
      for elm in argLst :
         tstDict = readXmlFiles(elm)

         updateXmlFiles(tstDict[0])

         writeXmlFiles(elm, tstDict)

#/********************************************************************30**
#
#         End of file:     cm_xta_gen_tc_num.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:10 2015
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
#/main/4      ---      sy  1. Update of sid field
#*********************************************************************91*/
