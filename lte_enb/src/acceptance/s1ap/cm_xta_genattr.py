#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    cm_xta_genattr.py
#
#     Sid:      cm_xta_genattr.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:09 2015
#
#     Prg:      
#
#*********************************************************************21*/
#!/usr/bin/env python

import re
import sys
import glob
import getopt

def showUsage () :
   print 'Usage: xx_checkfile.py [-ihv] [file1] [fileN]'
   print '\t[-i]: continue processing on error'
   print '\t[-v]: verbose mode'
   print '\t[-h]: show help'

def loadAttr(files = None) :
   '''Parse all the XML files for test cases, removes
      comments from the test case '''

   attr = {}

   # Create patterns for later use
   attrPatt1 = re.compile(r'xxPyWrap_getVal.*"([^"]+)"')
   attrPatt2 = re.compile(r'xxPyWrap_GetRouteList.*"([^"]+)"')
#attrPatt = re.compile(r'xxPyWrap_getVal')

   # If no filename given, do all XML files in the directory
   if (files == None) :
      fileLst = glob.glob('soac*.c')
   else :
      fileLst = files

   for elm in fileLst :

      # Read XML file
      lines = open(elm, "r").readlines()

      # Extract all instances of the testcases
      for line in lines :
         # Search pattern
         mobj = attrPatt1.search(line)

         # Add to list if search found
         if mobj :
            attr[mobj.group(1)] = mobj.group(1)
         else :
            # Search pattern
            mobj = attrPatt2.search(line)

            # Add to list if search found
            if mobj :
               attr[mobj.group(1)] = mobj.group(1)

   return attr

if __name__ == '__main__' :
   optLst, argLst = getopt.getopt(sys.argv[1:], 'hv')

   if len(optLst) != 0 :
      for opt in optLst :
         if opt[0] == '-h' :
            showUsage()
            sys.exit()

   argc = len(argLst)

   if argc == 0 :
      fileLst = glob.glob('soac*.c')
   else :
      fileLst = argLst

   attrs = loadAttr(fileLst)

   if attrs != None :
      print "\nattrDict = {"

      print "'%s'        :        '%s'," % ('srcid', 'srcid')
      print "'%s'        :        '%s'," % ('dstid', 'dstid')
      print "'%s'        :        '%s'," % ('cid',   'cid')

      for attr in attrs :
         print "'%s'        :        '%s'," % (attr, attr)

      print "}"




#/********************************************************************30**
#
#         End of file:     cm_xta_genattr.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:09 2015
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
#/main/3      ---      sy  1. Update of sid field
#/main/4      ---      sk       1. Updated for PSF-SIP 1.1 Release
#*********************************************************************91*/
