#!/bin/sh
cliExitCode=0

# For 3.5 and 4.0, we're interested in the last line of buddyinfo.
mem=`cat /proc/buddyinfo | tail -n 1 | awk '{printf $18 $17 $16 $15 $14}' -`
if [ $mem -gt 1 ];
then
  /mnt/dbx/cli $@
  cliExitCode=${?}
else
  echo "CLI not run: insufficient memory."
  cliExitCode=1
fi

exit $cliExitCode

