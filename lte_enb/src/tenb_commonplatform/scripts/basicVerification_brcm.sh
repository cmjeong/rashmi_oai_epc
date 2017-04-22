##########################################################################################################
# 
#  Note:- This script will verfify whether necessary directories and binary files
#         are there in the path or not board
#
#  Usage:   ./basicVerification.sh  <binaries_path>
#  Example:  ./basicVerification.sh /root/rsys/bin
#
##########################################################################################################
logger "RADISYS:Inside basicVerification.sh"
FILENAME="basicVerfication.sh"
OAM=$1/oam
TENPIN=$1/tenpin
TeNB=$1/enb_cpuh
FILE_TRANS_MGR=$1/fileTransMgr
TR069=$1/tr069-v2
POSTOFFICE=$1/post-office
REM=$1/rem
CLI=$1/cli
WATCHDOG=$1/watchdogd
if [ -d $1 ] && [ -d $1/../scripts ] && [ -d $1/../config ] && [ -d $1/../l1 ] && [ -d $1/../lib ] && [ -f $OAM ] && [ -f $TENPIN ] && [ -f $TeNB ] && [ -f $FILE_TRANS_MGR ] && [ -f $TR069 ] && [ -f $POSTOFFICE ] && [ -f $REM ] && [ -f $CLI ] && [ -f $WATCHDOG ]
then
logger "RADISYS:$FILENAME:Basic Verification Passed"
exit 0
else
logger "RADISYS:$FILENAME:Basic Verification Failed"
exit 1
fi
