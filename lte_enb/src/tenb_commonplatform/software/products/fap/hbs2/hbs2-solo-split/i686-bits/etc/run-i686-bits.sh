#!/bin/bash

# To be run from i686-bits/distro AS ROOT!

export LD_LIBRARY_PATH=.

./rrc --trace-dir ./ > /dev/null &
./nas-hlr --trace-dir ./ > /dev/null &
./nas-smsc --trace-dir ./ > /dev/null &
./nas-core --trace-dir ./ > /dev/null &
./oam-snmp --trace-dir ./ > /dev/null &
