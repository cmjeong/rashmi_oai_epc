#!/bin/sh
#
# $LastChangedRevision: $
#

ACTION=${1}
RESTART=${2}

/mnt/dbx/serialport /dev/ttyBF0 ${ACTION}

if [ "${?}" == "0" ] && [ "${RESTART}" == "1" ];
then
    /mnt/dbx/shrestart.sh
fi
