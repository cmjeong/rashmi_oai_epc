#! /bin/sh

import os, sys, re

if __name__ == '__main__' :
   if len(sys.argv) != 3 :
      print "Usage: $0 <view_name> <target dir>"
      print " eg: ngupta_ssi_3.1_rel_dev ~/tmp"
      print "<target dir> shall be present already"
      sys.exit(1)
   else :
      # Get view and local directory path
      viewName = sys.argv[1]
      locaPath = sys.argv[2]


      nsDir = 'ns'
      nsPath = '/vobs/core_prd/ssi/mtss_nt/src/'
      nslocaPath = locaPath + '/' + nsDir 

      ssDir = 'ss'
      ssPath = '/vobs/core_prd/ssi/ssi_cmn/src/'
      sslocaPath = locaPath + '/' + ssDir 

      commPath = '/vobs/core_prd/cm/'

      print r'/bin/rm -rf ' + locaPath + '/*'
      os.system(r'/bin/rm -rf ' + locaPath + '/*')

      # Create directory elements

      print 'Linking File ' + nsDir
      os.system('mkdir ' + nsDir)


      # Link nsSol files from vob
      print 'Linking File ' + 'ns'
      print 'ln -s  /view/' + viewName + nsPath + 'ns/' + '/* ' + nslocaPath + '/. 2>/dev/null'
      os.system('ln -s  /view/' + viewName + nsPath + 'ns/' + '/* ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + nsPath + 'build/' + '/ns_acc.mak ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + nsPath + 'build/' + '/ns_acc1.mak ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + nsPath + 'build/' + '/ns_ptmi.mak ' + nslocaPath + '/. 2>/dev/null')
      # Link ss files from vob
      print 'Linking File ' + 'ss'
      print 'ln -s  /view/' + viewName + ssPath + 'ss/' + '/* ' + nslocaPath + '/. 2>/dev/null'
      os.system('ln -s  /view/' + viewName + ssPath + 'ss/' + '/* ' + nslocaPath + '/. 2>/dev/null')
      print 'Linking File ' + 'ns_acc'
      print 'ln -s  /view/' + viewName + ssPath + 'acc/' + '/* ' + nslocaPath + '/. 2>/dev/null'
      os.system('ln -s  /view/' + viewName + ssPath + 'acc/' + '/* ' + nslocaPath + '/. 2>/dev/null')

      # Link cm files from vob
      os.system('ln -s  /view/' + viewName + commPath + '/lib/mem/src/cm_mem.* ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/lib/timer/src/cm_bdy5.c ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/lib/timer/src/cm5.h ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/lib/timer/src/cm5.x ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/tech/cm_cm/src/gen.x ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/tech/cm_cm/src/gen.h ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/tech/cm_cm/src/envopt.h ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/tech/cm_cm/src/envdep.h ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/tech/cm_cm/src/ssi.h ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/tech/cm_cm/src/ssi.x ' + nslocaPath + '/. 2>/dev/null')
      os.system('ln -s  /view/' + viewName + commPath + '/tech/cm_cm/src/envind.h ' + nslocaPath + '/. 2>/dev/null')
      #removing unwanted files
      print r'/bin/rm -rf ' + nslocaPath + '/ns.h'
      os.system(r'/bin/rm -rf ' + nslocaPath + '/ns.h')
      print r'/bin/rm -rf ' + nslocaPath + '/ns.x'
      os.system(r'/bin/rm -rf ' + nslocaPath + '/ns.x')
      print r'/bin/rm -rf ' + nslocaPath + '/scr'
      os.system(r'/bin/rm -rf ' + nslocaPath + '/scr')
      print r'/bin/rm -rf ' + nslocaPath + '/ss_nssp.c'
      os.system(r'/bin/rm -rf ' + nslocaPath + '/ss_nssp.c')
      print r'/bin/rm -rf ' + nslocaPath + '/ss_version.txt'
      os.system(r'/bin/rm -rf ' + nslocaPath + '/ss_version.txt')
      print r'/bin/rm -rf ' + nslocaPath + '/tmpFile'
      os.system(r'/bin/rm -rf ' + nslocaPath + '/tmpFile')
