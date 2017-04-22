#
#********************************************************************20**
#
#       Name:   lib_sh.mak - makefile
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file.
#
#       Sid:      lib_sh.mak@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:33 2015
#
#       Prg:    aj
#
#********************************************************************21*/


#-------------------------------------------------------------#
#Makefile for product sh - script generated.
#Only the $(CCshFLAGS) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCshFLAGS= -DSUNOS -DSS -DSS_MT  -DANSI -DSS_LINUX -DCMXTA_FTHA_INTEGRATED -DLCSHMILSH -DLCSMSHMILSH


#-------------------------------------------------------------#
#File/Obj macros             
#-------------------------------------------------------------#
shSRCS= \
	$(IN_DIR)/sh_bdy1.c\
	$(IN_DIR)/sh_bdy2.c\
	$(IN_DIR)/sh_bdy3.c\
	$(IN_DIR)/sh_bdy4.c\
	$(IN_DIR)/sh_bdy5.c\
	$(IN_DIR)/sh_bdy6.c\
	$(IN_DIR)/sh_bdy7.c\
	$(IN_DIR)/sh_bdy8.c\
	$(IN_DIR)/sh_bdy9.c\
	$(IN_DIR)/sh_bdy10.c\
	$(IN_DIR)/sh_ex_ms.c\
	$(IN_DIR)/sh_glob.c\
	$(IN_DIR)/sh_id.c\
	$(IN_DIR)/sh_ptmi.c\
	$(IN_DIR)/sh_ptpi.c\
	$(IN_DIR)/sh_util.c\
	$(IN_DIR)/smshbdy1.c\
	$(IN_DIR)/smshexms.c\
	$(IN_DIR)/smshptmi.c\
	$(IN_DIR)/lsh.c\

shOBJS= \
	$(OUT_DIR)/sh_bdy1.$(OBJ)\
	$(OUT_DIR)/sh_bdy2.$(OBJ)\
	$(OUT_DIR)/sh_bdy3.$(OBJ)\
	$(OUT_DIR)/sh_bdy4.$(OBJ)\
	$(OUT_DIR)/sh_bdy5.$(OBJ)\
	$(OUT_DIR)/sh_bdy6.$(OBJ)\
	$(OUT_DIR)/sh_bdy7.$(OBJ)\
	$(OUT_DIR)/sh_bdy8.$(OBJ)\
	$(OUT_DIR)/sh_bdy9.$(OBJ)\
	$(OUT_DIR)/sh_bdy10.$(OBJ)\
	$(OUT_DIR)/sh_ex_ms.$(OBJ)\
	$(OUT_DIR)/sh_glob.$(OBJ)\
	$(OUT_DIR)/sh_id.$(OBJ)\
	$(OUT_DIR)/sh_ptmi.$(OBJ)\
	$(OUT_DIR)/sh_ptpi.$(OBJ)\
	$(OUT_DIR)/sh_util.$(OBJ)\
	$(OUT_DIR)/smshbdy1.$(OBJ)\
	$(OUT_DIR)/smshexms.$(OBJ)\
	$(OUT_DIR)/smshptmi.$(OBJ)\
	$(OUT_DIR)/lsh.$(OBJ)

shOBJS1= \
	$(OUT_DIR)/sh_bdy1.$(OBJ)\
	$(OUT_DIR)/sh_bdy2.$(OBJ)\
	$(OUT_DIR)/sh_bdy3.$(OBJ)\
	$(OUT_DIR)/sh_bdy4.$(OBJ)\
	$(OUT_DIR)/sh_bdy5.$(OBJ)\
	$(OUT_DIR)/sh_bdy6.$(OBJ)\
	$(OUT_DIR)/sh_bdy7.$(OBJ)\
	$(OUT_DIR)/sh_bdy8.$(OBJ)\
	$(OUT_DIR)/sh_bdy9.$(OBJ)\
	$(OUT_DIR)/sh_bdy10.$(OBJ)\
	$(OUT_DIR)/sh_ex_ms.$(OBJ)\
	$(OUT_DIR)/sh_glob.$(OBJ)\
	$(OUT_DIR)/sh_id.$(OBJ)\
	$(OUT_DIR)/sh_ptmi.$(OBJ)\
	$(OUT_DIR)/sh_ptpi.$(OBJ)\
	$(OUT_DIR)/sh_util.$(OBJ)\
	$(OUT_DIR)/lsh.$(OBJ)
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/sh_bdy1.$(OBJ): $(IN_DIR)/sh_bdy1.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy1.c

$(OUT_DIR)/sh_bdy2.$(OBJ): $(IN_DIR)/sh_bdy2.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy2.c

$(OUT_DIR)/sh_bdy3.$(OBJ): $(IN_DIR)/sh_bdy3.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy3.c

$(OUT_DIR)/sh_bdy4.$(OBJ): $(IN_DIR)/sh_bdy4.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy4.c

$(OUT_DIR)/sh_bdy5.$(OBJ): $(IN_DIR)/sh_bdy5.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy5.c

$(OUT_DIR)/sh_bdy6.$(OBJ): $(IN_DIR)/sh_bdy6.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy6.c

$(OUT_DIR)/sh_bdy7.$(OBJ): $(IN_DIR)/sh_bdy7.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy7.c

$(OUT_DIR)/sh_bdy8.$(OBJ): $(IN_DIR)/sh_bdy8.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy8.c

$(OUT_DIR)/sh_bdy9.$(OBJ): $(IN_DIR)/sh_bdy9.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy9.c

$(OUT_DIR)/sh_bdy10.$(OBJ): $(IN_DIR)/sh_bdy10.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_bdy10.c

$(OUT_DIR)/sh_ex_ms.$(OBJ): $(IN_DIR)/sh_ex_ms.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_ex_ms.c

$(OUT_DIR)/sh_glob.$(OBJ): $(IN_DIR)/sh_glob.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_glob.c

$(OUT_DIR)/sh_id.$(OBJ): $(IN_DIR)/sh_id.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_id.c

$(OUT_DIR)/sh_ptmi.$(OBJ): $(IN_DIR)/sh_ptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_ptmi.c

$(OUT_DIR)/sh_ptpi.$(OBJ): $(IN_DIR)/sh_ptpi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_ptpi.c

$(OUT_DIR)/sh_util.$(OBJ): $(IN_DIR)/sh_util.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/sh_util.c

$(OUT_DIR)/smshbdy1.$(OBJ): $(IN_DIR)/smshbdy1.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/smshbdy1.c

$(OUT_DIR)/smshexms.$(OBJ): $(IN_DIR)/smshexms.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/smshexms.c

$(OUT_DIR)/smshptmi.$(OBJ): $(IN_DIR)/smshptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/smshptmi.c

$(OUT_DIR)/lsh.$(OBJ): $(IN_DIR)/lsh.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCshFLAGS) $(IN_DIR)/lsh.c


#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libsh_td.a:$(shOBJS)
	ar -cr libsh_td.a $(shOBJS) 

$(OUT_DIR)/libsh_slave.a:$(shOBJS1)
	ar -cr libsh_slave.a $(shOBJS1) 
#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f libsh_td.a $(shOBJS)
#********************************************************************30**
#
#        End of file:     lib_sh.mak@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:33 2015
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
