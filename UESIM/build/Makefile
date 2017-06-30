#********************************************************************20**
#
#       Name:   LTE eNodeB Sample Application
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file. 
#
#               This file supports a variety of environments and
#               build targets. The default build target will be the
#               portable target for the Linu 2.4.x with GNU C(gcc)
#
#       Env:    Linux 2.4.x with GNU C (gcc)
#
#               BUILD TARGETS:
#
#               clean            remove all object files
#   
#       File:  stack.mak
#
#
#       Prg:   an
#
#********************************************************************21*/
#=======================================================================

#-----------------------------------------------------------------------
# macro for output file name and makefile name
#

lnxperf:
	make -f ue_stack.mak BLDENV=lnx_perf_acc acc

lnxperfmsstub:
	make -f ue_stack.mak BLDENV=lnx_perf_msstub_acc acc

lnxe2e:
	make -f ue_stack.mak BLDENV=lnx_e2e_acc acc

lnxe2emsstub:
	make -f ue_stack.mak BLDENV=lnx_e2e_msstub_acc acc

lnxe2eperf:
	make -f ue_stack.mak BLDENV=lnx_e2eperf_acc acc

clean:
	make -f ue_stack.mak clean
