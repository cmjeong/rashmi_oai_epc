#!/bin/sh 

source tools_cmn.sh

cd $BUILD_PATH

#do the purify build
make -f $MAKEFILE $MAKE_PURIFY -j 4

#execute the test binary
./$EXE

if [ ! -f $PURIFY_LOG ]
then
   echo "Purify log file does not exist"
   exit 5
fi
exe_and_log echo " " 
exe_and_log echo " " 
exe_and_log echo "###########################################" 
exe_and_log echo "######### PURIFY RESULT SNIPPET ###########" 
exe_and_log echo "###########################################" 
exe_and_log echo "## For more information look into #########" 
exe_and_log echo "$BUILD_PATH/$PURIFY_LOG" 
exe_and_log echo " " 

exe_and_log grep -A 3 "exited" $PURIFY_LOG 

cd - 
