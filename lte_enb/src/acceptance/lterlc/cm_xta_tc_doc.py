#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    cm_xta_tc_doc.py
#
#     Sid:      cm_xta_tc_doc.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:12 2015
#
#     Prg:      
#
#*********************************************************************21*/
#!/usr/bin/env python

import sys
import re
import glob
import xml.dom.minidom
import cm_xta_py
import getopt


glInd = [1 for i in range(10)]

def printIndent (indent) :
   val = ''

   for cnt in range(indent + 1) :
      if val == '' :
         val = str(glInd[cnt])
      else :
         val = val + '.' + str(glInd[cnt])

   glInd[indent] = glInd[indent] + 1

   return val

def resetIndent (indent) :
   for cnt in range(indent, 10) :
      glInd[cnt] = 1

   return None


def printStep (steps, indent) :
   for step in steps :
      # Get the first step length
      length = len(step)

      if length == 1 :
         print "%-10s%-10s" % (printIndent(indent), step[0])

      elif length == 2 :
         print "%-10s%-10s: %s" % (printIndent(indent), step[0], step[1])

      elif length > 2 :
         print "%-10s%-10s: %s" % (printIndent(indent), step[0], step[1])
         #print "%-10s%-10s" % (printIndent(indent), step[0])

         miniStep = step[2:]
         subCmdLen = len(miniStep)

         # Decrement by one as the subStep shall use the same number as the simple
         # command printed above
         glInd[indent] = glInd[indent] - 1

         for st in miniStep :
            # Get the first st length
            length = len(st)

            if length == 1 :
               print "%-10s%-10s" % (printIndent(indent + 1), st[0])

            elif length == 2 :
               print "%-10s%-10s: %s" % (printIndent(indent + 1), st[0], st[1])

         # Reset the same
         glInd[indent] = glInd[indent] + 1
         glInd[indent + 1] = 1

      # Decrement by one as the subStep shall use the same number as the simple
      # command printed above
      glInd[indent] = glInd[indent] - 1

   # Reset the same
   glInd[indent] = glInd[indent] + 1
   glInd[indent + 1] = 1

def printCmd (xmlNode, indent) :
   if xmlNode == None :
      print "%-10s%-10s%10s" % (" ", 'Info', ': No steps, skip')
   elif xmlNode.hasChildNodes() :
      for node in xmlNode.childNodes :
         if node.nodeType == node.ELEMENT_NODE :
            # Check if internal command or compound command
            if intCmdDict.has_key(str(node.tagName)) :
               steps = cm_xta_py.getDocTCStep(node)
               printStep(steps, indent)

            elif comXmlCmdDict.has_key(str(node.tagName)) :
               steps = cm_xta_py.getDocTCStep(node)
               printStep(steps, indent)

               if commandMode == True :

                  xmlCmdNode = comXmlCmdDict[str(node.tagName)][3]

                  glInd[indent] = glInd[indent] - 1
                  printCmd(xmlCmdNode, indent + 1)
                  glInd[indent] = glInd[indent] + 1

                  if indent != 0 : 
                     resetIndent(indent)
            else :
               print "%-10s%-10s%10s[%s]" % (printIndent(indent), 'FATAL', ': *** UNKNOWN STEP ***', str(node.tagName))
         elif node.nodeType == node.COMMENT_NODE :
            print "%-10s%-10s%10s" % (printIndent(indent), 'WARNING', ': *** STEPS COMMENTED HERE ***')
   else :
      print "%-10s%-10s%10s" % (" ", 'Info', ': No steps, skip')

   if indent != 0 : 
      resetIndent(indent)



def listSort (a, b) :
   # Split on dot
   aList = a.split('.')
   bList = b.split('.')

   val1 = int (aList[1])
   val2 = int (bList[1])

   if val1 < val2 :
      return -1
   elif val1 > val2 :
      return 1
   else :
      return 0

def showUsage () :
   print 'Usage: xx_tc_doc.py [-ihvn] [file1] [fileN]'
   print '\t[-i]: continue processing on error'
   print '\t[-v]: verbose mode'
   print '\t[-n]: do not restart numbering'
   print '\t[-h]: show help'

commandMode = True
restartNumber = True













if __name__ == '__main__' :

   optLst, argLst = getopt.getopt(sys.argv[1:], 'nhq')

   if len(optLst) != 0 :
      for opt in optLst :
         if opt[0] == '-q' :
            commandMode = False
         elif opt[0] == '-n' :
            restartNumber = False
         elif opt[0] == '-h' :
            showUsage()
            sys.exit()

   argc = len(argLst)

   if argc == 0 :
      tcDict = cm_xta_py.loadTestCases()
      tgDict = cm_xta_py.loadTestGroups()
      commandDict = cm_xta_py.loadCommands()
   else :
      tcDict = cm_xta_py.loadTestCases(argLst[0])
      tgDict = cm_xta_py.loadTestGroups(argLst[0])
      commandDict = cm_xta_py.loadCommands(argLst[0])

   #Sort the test cases list
   tcList = tcDict.keys()
   tcList.sort(listSort)

   #Sort the test group list
   tgList = tgDict.keys()
   tgList.sort()

   #Sort the test cases list
   cmdList = commandDict.keys()
   cmdList.sort()

   simCmdDict = cm_xta_py.getSimpleCommands()
   intCmdDict = cm_xta_py.getInternalCommands()
   comCmdDict = cm_xta_py.getCompCommands()

   cmdDict = cm_xta_py.loadCommands()

   comXmlCmdDict = {}

   for cmd in comCmdDict :
      xmlcmd = cm_xta_py.parseCommand(cmdDict[cmd])
      comXmlCmdDict[cmd] = xmlcmd


   # Generate documentation for test case
   for test in tcList :

      resetIndent(0)

      cm_xta_py.updTCForAPI = False
      xmltest = cm_xta_py.parseTestCase(tcDict[test][3])

      [rfcAttr, module, strdoc, ifdefAttr, ifndefAttr, modAttr] = cm_xta_py.getTCDoc(xmltest[2], xmltest[3])

      print 
      print '================================================================\n'
      print 'Test Case     : %s.%s' % (tcDict[test][0], tcDict[test][1])
      print 'Alternate Id  : %s'    % (tcDict[test][2],)
      print 'RFC           : %s'    % (rfcAttr, )
      print 'Module        : %s'    % (module, )
      print 'Flags         : %s'    % (ifdefAttr, )
      print 'Flags Exclude : %s'    % (ifndefAttr, )
      print 'Mode          : %s'    % (modAttr, )
      print 'Description   : %s'    % (strdoc, )
      print '================================================================\n'

      xmlTcNode =  [xmltest[4], xmltest[6], xmltest[8], xmltest[10]]
      xmlDocNode = ['Configuration:\n--------------', 'Test:\n-----', 'Cleanup:\n--------', 'Shutdown:\n---------']

      cnt = 0
      for xmlNode in xmlTcNode :

         if restartNumber == True :
            resetIndent(0)

         print '\n', xmlDocNode[cnt], '\n'
         cnt = cnt + 1
         printCmd(xmlNode, 0)

   # Generate documentation for test group
   for test in tgList :

      resetIndent(0)

      cm_xta_py.updTCForAPI = False
      xmltest = cm_xta_py.parseTestGroup(tgDict[test][2])

      [rfcAttr, module, strdoc, ifdefAttr, ifndefAttr, modAttr] = cm_xta_py.getTCDoc(xmltest[2], xmltest[3])

      print
      print '================================================================\n'
      print 'Test Group    : %s'    % (tgDict[test][0], )
      print 'Alternate Id  : %s'    % (tgDict[test][1], )
      print 'RFC           : %s'    % (rfcAttr, )
      print 'Module        : %s'    % (module, )
      print 'Flags         : %s'    % (ifdefAttr, )
      print 'Flags Exclude : %s'    % (ifndefAttr, )
      print 'Mode          : %s'    % (modAttr, )
      print 'Description   : %s'    % (strdoc, )
      print '================================================================\n'

      xmlTcNode =  [xmltest[4], xmltest[6]]
      xmlDocNode = ['Configuration:\n--------------', 'Shutdown:\n---------']

      cnt = 0
      for xmlNode in xmlTcNode :

         if restartNumber == True :
            resetIndent(0)

         print '\n', xmlDocNode[cnt], '\n'
         cnt = cnt + 1
         printCmd(xmlNode, 0)


   # Generate documentation for compound command
   for test in cmdList :

      resetIndent(0)

      cm_xta_py.updTCForAPI = False
      xmltest = comXmlCmdDict[test]

      strdoc = comCmdDict[test]

      print 
      print '================================================================\n'
      print 'Command       : %s'    % (test, )
      print 'Description   : %s'    % (strdoc, )
      print '================================================================\n'

      xmlTcNode =  [xmltest[3]]
      xmlDocNode = ['Steps:\n------']

      cnt = 0
      for xmlNode in xmlTcNode :

         if restartNumber == True :
            resetIndent(0)

         print '\n', xmlDocNode[cnt], '\n'
         cnt = cnt + 1
         printCmd(xmlNode, 0)

#/********************************************************************30**
#
#         End of file:     cm_xta_tc_doc.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:12 2015
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
