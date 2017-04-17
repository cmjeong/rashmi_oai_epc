#!/bin/sh 

source tools_cmn.sh

cd $BUILD_PATH
make -f $MAKEFILE $MAKE_PURECOV -j 4

exe_and_log echo "###########################################" 
exe_and_log echo "############## TEST SUMMARY ###############" 
exe_and_log echo "###########################################" 

#output tests passed failed to final log file
cat $GT_REPORT_FILE | sed 's/^<testsuites //' | sed 's/>$//' > /tmp/$GT_REPORT_FILE.tmp
exe_and_log grep "^tests=" /tmp/$GT_REPORT_FILE.tmp

if [ "$OLD_PCV" == "YES" ]
then
   exe_and_log echo "                                           " 
   exe_and_log echo "###########################################" 
   exe_and_log echo "############ PURECOV SUMMARY ##############" 
   exe_and_log echo "###########################################" 

   #output code difference to final log file
   exe_and_log $PURECOV_PATH/pc_diff $1 $PURECOV_PCV
fi

cd - 
