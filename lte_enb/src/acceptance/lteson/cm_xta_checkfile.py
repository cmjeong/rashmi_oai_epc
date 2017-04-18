#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    cm_xta_checkfile.py
#
#     Sid:      cm_xta_checkfile.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:08 2015
#
#     Prg:      
#
#*********************************************************************21*/
#!/usr/bin/env python


import sys
import glob
import getopt
import cm_xta_py
from cm_xta_py import *

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
   print 'Usage: xx_checkfile.py [-ihv] [file1] [fileN]'
   print '\t[-i]: continue processing on error'
   print '\t[-v]: verbose mode'
   print '\t[-h]: show help'

def printDbgErr (*txt) :
   if verboseMode == False :
      txt = txt[2:]

   for elm in txt :
      if verboseMode == False :
         print elm.lstrip(),
      else :
         print elm,
   print

def printDbgInfo (*txt) :
   if verboseMode == True :
      for elm in txt :
         print elm,
      print

dbgMask = True
ignoreErr = False
verboseMode = False

if __name__ == '__main__' :
   optLst, argLst = getopt.getopt(sys.argv[1:], 'ihv')

   if len(optLst) != 0 :
      for opt in optLst :
         if opt[0] == '-i' :
            ignoreErr = True
         elif opt[0] == '-h' :
            showUsage()
            sys.exit()
         elif opt[0] == '-v' :
            verboseMode = True
            cm_xta_py.dbgMask = True

   argc = len(argLst)

   if argc == 0 :
      fileLst = glob.glob('*.xml')
   else :
      fileLst = argLst

   cnt = 1
   failTG  = []
   failTC  = []
   failCmd = []

   for elm in fileLst :
      # Two step process, load the file, parse the TC

      step = str(cnt)
      if (cnt < 10) :
         printDbgInfo('Step', step, "\t\tInfo: Processing all the test cases in the file " + elm)
      else :
         printDbgInfo('Step', step, "\tInfo: Processing all the test cases in the file " + elm)
      printDbgInfo()

      try :
         dictList = loadTestCases(elm, False)
      except :
         printDbgErr('Step', step, "\tError: loading file " + elm)
         if ignoreErr == False :
            raise
         else :
            printDbgInfo('Step', step, "\tInfo: skipping error, continue with the next file")
            continue

      #Sort the test cases list
      tcList = dictList.keys()
      tcList.sort(listSort)

      subCnt = 0
      # Parse the testcases
      for tst in tcList :
         subCnt = subCnt + 1
         step = str(cnt) + '.' + str(subCnt)
         try :
            printDbgInfo('Step', step, "\tInfo: Parsing test case " + tst + " in the file " + elm)
            parseTestCase(dictList[tst][3])

            printDbgInfo()
         except :
            printDbgErr('Step', step, "\tError: parsing test case " + tst + " in the file " + elm)
            open (tst + ".log", 'w').write(dictList[tst][3])
            printDbgInfo('Step', step, "\tInfo: Test case written in log file " + tst + ".log")
            if ignoreErr == False :
               raise
            else :
               printDbgInfo('Step', step, "\tInfo: skipping testcase, continue with the next testcase")
               printDbgInfo()
               failTC.append(tst)
               continue

      cnt = cnt + 1

   for elm in fileLst :
      # Two step process, load the file, parse the TC/TG/Command
      step = str(cnt)
      printDbgInfo('Step', step, "\tInfo: Processing all the test groups in the file " + elm)
      printDbgInfo()

      try :
         dictList = loadTestGroups(elm, False)
      except :
         printDbgErr('Step', step, "\tError: loading file " + elm)
         if ignoreErr == False :
            raise
         else :
            printDbgInfo('Step', step, "\tInfo: skipping error, continue with the next file")
            printDbgInfo()
            continue

      subCnt = 0
      # Parse the testgroups
      for tst in dictList.keys() :
         subCnt = subCnt + 1
         step = str(cnt) + '.' + str(subCnt)
         try :
            printDbgInfo('Step', step, "\tInfo: Parsing test group " + tst + " in the file " + elm)
            parseTestGroup(dictList[tst][2])
            printDbgInfo()

         except :
            printDbgErr('Step', step, "\tError: parsing test group " + tst + " in the file " + elm)
            open (tst + ".log", 'w').write(dictList[tst][2])
            printDbgInfo('Step', step, "\tInfo: Test group written in log file " + tst + ".log")
            if ignoreErr == False :
               raise
            else :
               printDbgInfo('Step', step, "\tInfo: skipping test group, continue with the next test group")
               printDbgInfo()
               failTG.append(tst)
               continue

      cnt = cnt + 1

   for elm in fileLst :
      # Two step process, load the file, parse the Command
      step = str(cnt)
      printDbgInfo('Step', step, "\tInfo: Processing all the commands in the file " + elm)
      printDbgInfo()

      try :
         dictList = loadCommands(elm, False)
      except :
         printDbgErr('Step', step, "\tError: loading file " + elm)
         if ignoreErr == False :
            raise
         else :
            printDbgInfo('Step', step, "\tInfo: skipping error, continue with the next file")
            printDbgInfo()
            continue

      subCnt = 0
      # Parse the commands
      for tst in dictList.keys() :
         subCnt = subCnt + 1
         step = str(cnt) + '.' + str(subCnt)
         try :
            printDbgInfo('Step', step, "\tInfo: Parsing command " + tst + " in the file " + elm)
            parseCommand(dictList[tst])
            printDbgInfo()

         except :
            printDbgErr('Step', step, "\tError: parsing command " + tst + " in the file " + elm)
            open (tst + ".log", 'w').write(dictList[tst])
            printDbgInfo('Step', step, "\tInfo: Command written in log file " + tst + ".log")
            if ignoreErr == False :
               raise
            else :
               printDbgInfo('Step', step, "\tInfo: skipping command, continue with the next command")
               printDbgInfo()
               failCmd.append(tst)
               continue

      cnt = cnt + 1

   if ignoreErr == True :
      print
      if len(failCmd) != 0 :
         print 'Failed Commands :'
         print '-----------------'

         failCmd.sort()
         for tst in failCmd :
            print '\t', tst

      if len(failTG) != 0 :
         print 'Failed Test Groups :'
         print '--------------------'

         failTG.sort()
         for tst in failTG :
            print '\t', tst

      if len(failTC) != 0 :
         print 'Failed Test Cases :'
         print '-------------------'

         failTC.sort()
         for tst in failTC :
            print '\t', tst



#/********************************************************************30**
#
#         End of file:     cm_xta_checkfile.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:08 2015
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
#/main/5      ---      sk       1. Updated for PSF-SIP 1.1 Release
#*********************************************************************91*/
