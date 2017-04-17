#!/bin/sh

echo "                                                             "
echo "                                                             "
echo "                                                             "
echo "                           ((       ))                       "
echo "                            ((     ))                        "
echo "                             ((   ))                         "
echo "   / ::::  /::::::         ||   *   :::::: ::    :: ::::::   "
echo "  : /      ||   ||     ....||  | |  ||      ::  ::  ||       "
echo "  | |      ||   ||    ||   ||  | |  ::::::    ||    ::::::   "
echo "  | |      ||   ::    ||   ||  | |      ||    ||        ||   "
echo "  | |      ::::::,,,  ||:::::  | |  ::::::    ||    ::::::   "

echo "                                                             "
echo "                                                             "
echo "                                                             "
echo "   TotaleNodeB Solution                                      "
echo "                                                             "
echo "                                                             "
echo "                                                             "

sleep 3
ulimit -c unlimited
SSI_CONFIG_FILE="../config/ssi_mem"
echo "RADISYS:Launching enodeb with $SSI_CONFIG_FILE"
./enodeb -f $SSI_CONFIG_FILE
