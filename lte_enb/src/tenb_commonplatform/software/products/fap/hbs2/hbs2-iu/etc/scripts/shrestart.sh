#!/bin/sh
#
# $LastChangedRevision: 14548 $
#

PID=`ps -e | grep /bin/sh | head -1 | sed -e 's/^[ ]*\([0-9]*\)[ ]*.*/\1/g'`
echo "killing shell with pid $PID"
kill -9 ${PID}
