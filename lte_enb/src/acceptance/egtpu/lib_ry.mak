#
#********************************************************************20**
#
#       Name:   lib_ry.mak - makefile
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file.
#
#       Sid:      lib_ry.mak@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:32 2015
#
#       Prg:    aj
#
#********************************************************************21*/


#-------------------------------------------------------------#
#Makefile for product ry - script generated.
#Only the $(CCryFLAGS) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCryFLAGS=-DSUNOS -DSS -DSS_MT  -DANSI -DSS_LINUX -USS_MULTIPLE_PROCS -ULCSMRYMILRY  -ULCLRY -ULCRYMILRY -DCMXTA_FTHA_INTEGRATED -DSS_DRVR_SUPPORT -DSM -DRY_ENBUDPSOCK -DCM_INET2 -URY_TU_BLK -DCMSOCKFLATBUF

#-------------------------------------------------------------#
#File/Obj macros             
#-------------------------------------------------------------#
rySRCS= \
	$(IN_DIR)/ry_bdy1.c\
	$(IN_DIR)/ry_bdy2.c\
	$(IN_DIR)/ry_bdy3.c\
	$(IN_DIR)/ry_bdy4.c\
	$(IN_DIR)/ry_ex_ms.c\
	$(IN_DIR)/ry_id.c\
	$(IN_DIR)/ry_ptmi.c\
	$(IN_DIR)/lry.c\
	$(IN_DIR)/ry_sock.c\
	$(IN_DIR)/cm_sock.c\
	$(IN_DIR)/cm_os.c\
	$(IN_DIR)/smrybdy1.c\
	$(IN_DIR)/smryexms.c\
	$(IN_DIR)/smryptmi.c\

ryOBJS= \
	$(OUT_DIR)/ry_bdy1.$(OBJ)\
	$(OUT_DIR)/ry_bdy2.$(OBJ)\
	$(OUT_DIR)/ry_bdy3.$(OBJ)\
	$(OUT_DIR)/ry_bdy4.$(OBJ)\
	$(OUT_DIR)/ry_ex_ms.$(OBJ)\
	$(OUT_DIR)/ry_id.$(OBJ)\
	$(OUT_DIR)/ry_ptmi.$(OBJ)\
	$(OUT_DIR)/lry.$(OBJ)\
	$(OUT_DIR)/smrybdy1.$(OBJ)\
	$(OUT_DIR)/ry_sock.$(OBJ)\
	$(OUT_DIR)/cm_sock.$(OBJ)\
	$(OUT_DIR)/cm_os.$(OBJ)\
	$(OUT_DIR)/smryexms.$(OBJ)\
	$(OUT_DIR)/smryptmi.$(OBJ)\

#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/ry_bdy1.$(OBJ): $(IN_DIR)/ry_bdy1.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/ry_bdy1.c

$(OUT_DIR)/ry_bdy2.$(OBJ): $(IN_DIR)/ry_bdy2.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/ry_bdy2.c

$(OUT_DIR)/ry_bdy3.$(OBJ): $(IN_DIR)/ry_bdy3.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/ry_bdy3.c

$(OUT_DIR)/ry_bdy4.$(OBJ): $(IN_DIR)/ry_bdy4.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/ry_bdy4.c


$(OUT_DIR)/ry_ex_ms.$(OBJ): $(IN_DIR)/ry_ex_ms.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/ry_ex_ms.c

$(OUT_DIR)/ry_id.$(OBJ): $(IN_DIR)/ry_id.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/ry_id.c

$(OUT_DIR)/lry.$(OBJ): $(IN_DIR)/lry.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/lry.c


$(OUT_DIR)/ry_ptmi.$(OBJ): $(IN_DIR)/ry_ptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/ry_ptmi.c

$(OUT_DIR)/cm_os.$(OBJ): $(IN_DIR)/cm_os.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/cm_os.c

$(OUT_DIR)/cm_sock.$(OBJ): $(IN_DIR)/cm_sock.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/cm_sock.c

$(OUT_DIR)/ry_sock.$(OBJ): $(IN_DIR)/ry_sock.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/ry_sock.c

$(OUT_DIR)/smrybdy1.$(OBJ): $(IN_DIR)/smrybdy1.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/smrybdy1.c

$(OUT_DIR)/smryptmi.$(OBJ): $(IN_DIR)/smryptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/smryptmi.c

$(OUT_DIR)/smryexms.$(OBJ): $(IN_DIR)/smryexms.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCryFLAGS) $(IN_DIR)/smryexms.c


#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libry_td.a:$(ryOBJS)
	ar -r libry_td.a $(ryOBJS) 

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f libry_td.a $(ryOBJS)
#********************************************************************30**
#
#        End of file:     lib_ry.mak@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:32 2015
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
