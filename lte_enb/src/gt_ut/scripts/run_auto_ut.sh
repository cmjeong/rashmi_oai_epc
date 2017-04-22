#!/bin/sh 


# 0 - Success
# 1 - Only some tests failed
# 2 - Only Coverage reduced
# 4 - Only Purify errors
# 3 - Test failed and Coverage reduced
# 5 - Test failed and Purify errors
# 6 - Test passed but Purify and Coverage problems
# 7 - All failed

source tools_cmn.sh

OLD_PCV="NO"
if [ $# -gt 1 ]
then
   echo "Usage : $0 <ABSOLUTE PATH of old pcv file>"
   echo "           <odl pcv file> is OPTIONAL"
   exit 5
fi

if [ -f $1 ]
then
   echo "$1 old pcv file exists"
   OLD_PCV="YES"
fi

if [ "$#" == "0" ]
then
   OLD_PCV="NO"
fi

export OLD_PCV
cd $BUILD_PATH
#clean up all old log files
rm -f $FIN_LOG_FILE $PURIFY_LOG $PURECOV_PCV $GT_REPORT_FILE $PURIFY_PV
make -f $MAKEFILE $CLEAN
cd - 
check_purecov.sh $1

cd $BUILD_PATH
make -f $MAKEFILE $CLEAN
cd - 
check_purify.sh 


cd $BUILD_PATH

#find if any tests failed
FAILED_TESTS=`grep testsuites $FIN_LOG_FILE | awk -F"\"" '{print $4}'`
if [ "$FAILED_TESTS" != "0" ]
then
   FAILED_TESTS=1
fi
#echo "FAILED_TESTS = $FAILED_TESTS"

#find if purecov coverage reduced
PURECOV_PROB=`grep -A 1 "Files which got worse" $FIN_LOG_FILE | sed '/^$/d' | wc -l`
if [ "$PURECOV_PROB" == "1" ]
then
   PURECOV_PROB=0
else
   PURECOV_PROB=1
fi
#echo "PURECOV_PROB = $PURECOV_PROB"

#find if purify access errors are there
PURIFY_PROB=`grep "access errors" $FIN_LOG_FILE | awk '{print $2}'`

if [ -z $PURIFY_PROB ] || [ "$PURIFY_PROB" == "0" ]
then
   PURIFY_PROB=0
else
   PURIFY_PROB=1
fi
#echo "PURIFY_PROB=$PURIFY_PROB"

EXIT_VAL=`echo $((($PURIFY_PROB << 2) + ($PURECOV_PROB << 1) + ($FAILED_TESTS)))`
#echo "EXIT_VAL=$EXIT_VAL"
exit $EXIT_VAL
cd - 
