These boost files have been copied over from tools/boost so that we don't need to install
and build boost on all build machines just to get the smart pointer implementations which
are wholly contained within header files (no linking to boost libs required).

If we start to use boost libraries, then we'll probably delete this directory and install
boost on all build machines.

Boost version 1_33_1 (I think)
