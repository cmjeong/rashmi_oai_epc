#
#********************************************************************20**
#
#       Name:   lib_mr.mak - makefile
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file.
#
#       Sid:      lib_mr.mak@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:32 2015
#
#       Prg:    aj
#
#********************************************************************21*/

#=======================================================================

#-------------------------------------------------------------#
#Makefile for product mr - script generated.
#Only the $(CCmrFLAGS) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCmrFLAGS=-DSUNOS -DSS -DSS_MT  -DANSI -DSS_LINUX  -DCMXTA_FTHA_INTEGRATED -DLCSMMRMILMR -DLCMRMILMR -DLCMRSMMILMR

#-------------------------------------------------------------#
#File/Obj macros             
#-------------------------------------------------------------#
mrSRCS= \
	$(IN_DIR)/mr_bdy1.c\
	$(IN_DIR)/mr_bdy2.c\
	$(IN_DIR)/mr_bdy3.c\
	$(IN_DIR)/mr_bdy4.c\
	$(IN_DIR)/mr_ex_ms.c\
	$(IN_DIR)/mr_id.c\
	$(IN_DIR)/mr_ptmi.c\
	$(IN_DIR)/mr_ptmrs.c\
	$(IN_DIR)/lmr.c\
	$(IN_DIR)/smmrbdy1.c\
	$(IN_DIR)/smmrexms.c\
	$(IN_DIR)/smmrptmi.c\
	$(IN_DIR)/mr_ptpi.c

mrOBJS= \
	$(OUT_DIR)/mr_bdy1.$(OBJ)\
	$(OUT_DIR)/mr_bdy2.$(OBJ)\
	$(OUT_DIR)/mr_bdy3.$(OBJ)\
	$(OUT_DIR)/mr_bdy4.$(OBJ)\
	$(OUT_DIR)/mr_ex_ms.$(OBJ)\
	$(OUT_DIR)/mr_id.$(OBJ)\
	$(OUT_DIR)/mr_ptmi.$(OBJ)\
	$(OUT_DIR)/mr_ptmrs.$(OBJ)\
	$(OUT_DIR)/lmr.$(OBJ)\
	$(OUT_DIR)/smmrbdy1.$(OBJ)\
	$(OUT_DIR)/smmrexms.$(OBJ)\
	$(OUT_DIR)/smmrptmi.$(OBJ)\
	$(OUT_DIR)/mr_ptpi.$(OBJ)

mrOBJS1= \
	$(OUT_DIR)/mr_bdy1.$(OBJ)\
	$(OUT_DIR)/mr_bdy2.$(OBJ)\
	$(OUT_DIR)/mr_bdy3.$(OBJ)\
	$(OUT_DIR)/mr_bdy4.$(OBJ)\
	$(OUT_DIR)/mr_ex_ms.$(OBJ)\
	$(OUT_DIR)/mr_id.$(OBJ)\
	$(OUT_DIR)/mr_ptmi.$(OBJ)\
	$(OUT_DIR)/mr_ptpi.$(OBJ)\
	$(OUT_DIR)/mr_ptmrs.$(OBJ)\
	$(OUT_DIR)/lmr.$(OBJ)\
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/mr_bdy1.$(OBJ): $(IN_DIR)/mr_bdy1.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_bdy1.c

$(OUT_DIR)/mr_bdy2.$(OBJ): $(IN_DIR)/mr_bdy2.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_bdy2.c

$(OUT_DIR)/mr_bdy3.$(OBJ): $(IN_DIR)/mr_bdy3.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_bdy3.c

$(OUT_DIR)/mr_bdy4.$(OBJ): $(IN_DIR)/mr_bdy4.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_bdy4.c

$(OUT_DIR)/mr_ex_ms.$(OBJ): $(IN_DIR)/mr_ex_ms.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_ex_ms.c

$(OUT_DIR)/mr_id.$(OBJ): $(IN_DIR)/mr_id.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_id.c

$(OUT_DIR)/mr_ptmi.$(OBJ): $(IN_DIR)/mr_ptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_ptmi.c

$(OUT_DIR)/lmr.$(OBJ): $(IN_DIR)/lmr.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/lmr.c

$(OUT_DIR)/mr_ptmrs.$(OBJ): $(IN_DIR)/mr_ptmrs.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_ptmrs.c

$(OUT_DIR)/smmrbdy1.$(OBJ): $(IN_DIR)/smmrbdy1.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/smmrbdy1.c

$(OUT_DIR)/smmrexms.$(OBJ): $(IN_DIR)/smmrexms.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/smmrexms.c

$(OUT_DIR)/smmrptmi.$(OBJ): $(IN_DIR)/smmrptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/smmrptmi.c

$(OUT_DIR)/mr_ptpi.$(OBJ): $(IN_DIR)/mr_ptpi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCmrFLAGS) $(IN_DIR)/mr_ptpi.c



#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libmr_td.a:$(mrOBJS)
	ar -cr libmr_td.a $(mrOBJS) 

$(OUT_DIR)/libmr_slave.a:$(mrOBJS1)
	ar -cr libmr_slave.a $(mrOBJS1) 
#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f libmr_td.a $(mrOBJS)

#********************************************************************30**
#
#        End of file:     lib_mr.mak@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:32 2015
#
#********************************************************************31*/
#
#********************************************************************40**
#
#        Notes:
#
#********************************************************************41*/
#
#********************************************************************50**
#
#********************************************************************51*/
#
#********************************************************************60**
#
#       Revision history:
#
#********************************************************************61*/
#
#********************************************************************90**
#
#   ver       pat    init                  description
#---------- -------- ---- -----------------------------------------------
#/main/1      ---      aj  1. Created for PSF-SIP 1.1 Release
#********************************************************************91*/

# DO NOT DELETE THIS LINE -- make depend depends on it.
