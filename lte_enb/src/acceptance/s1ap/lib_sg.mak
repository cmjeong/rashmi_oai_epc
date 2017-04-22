#
#********************************************************************20**
#
#       Name:   lib_sg.mak - makefile
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file.
#
#       Sid:      lib_sg.mak@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:33 2015
#
#       Prg:    aj
#
#********************************************************************21*/

#=======================================================================

#-------------------------------------------------------------#
#Makefile for product sg - script generated.
#Only the $(CCsgFLAGS) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCsgFLAGS=-DSUNOS -DSS -DSS_MT  -DANSI -DSS_LINUX  -DLCSMSGMILSG -DLCSGMILSG -DCMXTA_FTHA_INTEGRATED

#-------------------------------------------------------------#
#File/Obj macros             
#-------------------------------------------------------------#
sgSRCS= \
	$(IN_DIR)/sg_cfn.c\
	$(IN_DIR)/sg_dsp.c\
	$(IN_DIR)/sg_ex_ms.c\
	$(IN_DIR)/sg_fail.c\
	$(IN_DIR)/sg_frame.c\
	$(IN_DIR)/sg_hiabt.c\
	$(IN_DIR)/sg_hialm.c\
	$(IN_DIR)/sg_hicfg.c\
	$(IN_DIR)/sg_hidb.c\
	$(IN_DIR)/sg_hidis.c\
	$(IN_DIR)/sg_hiena.c\
	$(IN_DIR)/sg_hilm.c\
	$(IN_DIR)/sg_himis.c\
	$(IN_DIR)/sg_hista.c\
	$(IN_DIR)/sg_hists.c\
	$(IN_DIR)/sg_hiswp.c\
	$(IN_DIR)/sg_hival.c\
	$(IN_DIR)/sg_id.c\
	$(IN_DIR)/sg_lm.c\
	$(IN_DIR)/sg_loabt.c\
	$(IN_DIR)/sg_loact.c\
	$(IN_DIR)/sg_loalm.c\
	$(IN_DIR)/sg_locfg.c\
	$(IN_DIR)/sg_locmv.c\
	$(IN_DIR)/sg_locso.c\
	$(IN_DIR)/sg_lodb.c\
	$(IN_DIR)/sg_lofmv.c\
	$(IN_DIR)/sg_lofso.c\
	$(IN_DIR)/sg_loft.c\
	$(IN_DIR)/sg_lolm.c\
	$(IN_DIR)/sg_lomis.c\
	$(IN_DIR)/sg_looos.c\
	$(IN_DIR)/sg_lopi.c\
	$(IN_DIR)/sg_losby.c\
	$(IN_DIR)/sg_losta.c\
	$(IN_DIR)/sg_losts.c\
	$(IN_DIR)/sg_ptmi.c\
	$(IN_DIR)/sg_ptpi.c\
	$(IN_DIR)/sg_rback.c\
	$(IN_DIR)/sg_tmr.c\
	$(IN_DIR)/sg_util.c\
	$(IN_DIR)/smsgptmi.c\
	$(IN_DIR)/sgmrptmi.c\
	$(IN_DIR)/sgshptmi.c\
	$(IN_DIR)/smsgbdy1.c\
	$(IN_DIR)/smsgexms.c\
	$(IN_DIR)/lsg.c

sgOBJS= \
	$(OUT_DIR)/sg_cfn.$(OBJ)\
	$(OUT_DIR)/sg_dsp.$(OBJ)\
	$(OUT_DIR)/sg_ex_ms.$(OBJ)\
	$(OUT_DIR)/sg_fail.$(OBJ)\
	$(OUT_DIR)/sg_frame.$(OBJ)\
	$(OUT_DIR)/sg_hiabt.$(OBJ)\
	$(OUT_DIR)/sg_hialm.$(OBJ)\
	$(OUT_DIR)/sg_hicfg.$(OBJ)\
	$(OUT_DIR)/sg_hidb.$(OBJ)\
	$(OUT_DIR)/sg_hidis.$(OBJ)\
	$(OUT_DIR)/sg_hiena.$(OBJ)\
	$(OUT_DIR)/sg_hilm.$(OBJ)\
	$(OUT_DIR)/sg_himis.$(OBJ)\
	$(OUT_DIR)/sg_hista.$(OBJ)\
	$(OUT_DIR)/sg_hists.$(OBJ)\
	$(OUT_DIR)/sg_hiswp.$(OBJ)\
	$(OUT_DIR)/sg_hival.$(OBJ)\
	$(OUT_DIR)/sg_id.$(OBJ)\
	$(OUT_DIR)/sg_lm.$(OBJ)\
	$(OUT_DIR)/sg_loabt.$(OBJ)\
	$(OUT_DIR)/sg_loact.$(OBJ)\
	$(OUT_DIR)/sg_loalm.$(OBJ)\
	$(OUT_DIR)/sg_locfg.$(OBJ)\
	$(OUT_DIR)/sg_locmv.$(OBJ)\
	$(OUT_DIR)/sg_locso.$(OBJ)\
	$(OUT_DIR)/sg_lodb.$(OBJ)\
	$(OUT_DIR)/sg_lofmv.$(OBJ)\
	$(OUT_DIR)/sg_lofso.$(OBJ)\
	$(OUT_DIR)/sg_loft.$(OBJ)\
	$(OUT_DIR)/sg_lolm.$(OBJ)\
	$(OUT_DIR)/sg_lomis.$(OBJ)\
	$(OUT_DIR)/sg_looos.$(OBJ)\
	$(OUT_DIR)/sg_lopi.$(OBJ)\
	$(OUT_DIR)/sg_losby.$(OBJ)\
	$(OUT_DIR)/sg_losta.$(OBJ)\
	$(OUT_DIR)/sg_losts.$(OBJ)\
	$(OUT_DIR)/sg_ptmi.$(OBJ)\
	$(OUT_DIR)/sg_ptpi.$(OBJ)\
	$(OUT_DIR)/sg_rback.$(OBJ)\
	$(OUT_DIR)/sg_tmr.$(OBJ)\
	$(OUT_DIR)/sg_util.$(OBJ)\
	$(OUT_DIR)/smsgptmi.$(OBJ)\
	$(OUT_DIR)/sgmrptmi.$(OBJ)\
	$(OUT_DIR)/sgshptmi.$(OBJ)\
	$(OUT_DIR)/smsgbdy1.$(OBJ)\
	$(OUT_DIR)/smsgexms.$(OBJ)\
	$(OUT_DIR)/lsg.$(OBJ)

#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/sg_cfn.$(OBJ): $(IN_DIR)/sg_cfn.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_cfn.c

$(OUT_DIR)/sg_dsp.$(OBJ): $(IN_DIR)/sg_dsp.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_dsp.c

$(OUT_DIR)/sg_ex_ms.$(OBJ): $(IN_DIR)/sg_ex_ms.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_ex_ms.c

$(OUT_DIR)/sg_fail.$(OBJ): $(IN_DIR)/sg_fail.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_fail.c

$(OUT_DIR)/sg_frame.$(OBJ): $(IN_DIR)/sg_frame.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) -DMR $(IN_DIR)/sg_frame.c

$(OUT_DIR)/sg_hiabt.$(OBJ): $(IN_DIR)/sg_hiabt.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hiabt.c

$(OUT_DIR)/sg_hialm.$(OBJ): $(IN_DIR)/sg_hialm.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hialm.c

$(OUT_DIR)/sg_hicfg.$(OBJ): $(IN_DIR)/sg_hicfg.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hicfg.c

$(OUT_DIR)/sg_hidb.$(OBJ): $(IN_DIR)/sg_hidb.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hidb.c

$(OUT_DIR)/sg_hidis.$(OBJ): $(IN_DIR)/sg_hidis.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hidis.c

$(OUT_DIR)/sg_hiena.$(OBJ): $(IN_DIR)/sg_hiena.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hiena.c

$(OUT_DIR)/sg_hilm.$(OBJ): $(IN_DIR)/sg_hilm.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hilm.c

$(OUT_DIR)/sg_himis.$(OBJ): $(IN_DIR)/sg_himis.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_himis.c

$(OUT_DIR)/sg_hista.$(OBJ): $(IN_DIR)/sg_hista.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hista.c

$(OUT_DIR)/sg_hists.$(OBJ): $(IN_DIR)/sg_hists.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hists.c

$(OUT_DIR)/sg_hiswp.$(OBJ): $(IN_DIR)/sg_hiswp.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hiswp.c

$(OUT_DIR)/sg_hival.$(OBJ): $(IN_DIR)/sg_hival.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_hival.c

$(OUT_DIR)/sg_id.$(OBJ): $(IN_DIR)/sg_id.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_id.c

$(OUT_DIR)/sg_lm.$(OBJ): $(IN_DIR)/sg_lm.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_lm.c

$(OUT_DIR)/sg_loabt.$(OBJ): $(IN_DIR)/sg_loabt.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_loabt.c

$(OUT_DIR)/sg_loact.$(OBJ): $(IN_DIR)/sg_loact.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_loact.c

$(OUT_DIR)/sg_loalm.$(OBJ): $(IN_DIR)/sg_loalm.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_loalm.c

$(OUT_DIR)/sg_locfg.$(OBJ): $(IN_DIR)/sg_locfg.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_locfg.c

$(OUT_DIR)/sg_locmv.$(OBJ): $(IN_DIR)/sg_locmv.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_locmv.c

$(OUT_DIR)/sg_locso.$(OBJ): $(IN_DIR)/sg_locso.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_locso.c

$(OUT_DIR)/sg_lodb.$(OBJ): $(IN_DIR)/sg_lodb.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_lodb.c

$(OUT_DIR)/sg_lofmv.$(OBJ): $(IN_DIR)/sg_lofmv.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_lofmv.c

$(OUT_DIR)/sg_lofso.$(OBJ): $(IN_DIR)/sg_lofso.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_lofso.c

$(OUT_DIR)/sg_loft.$(OBJ): $(IN_DIR)/sg_loft.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_loft.c

$(OUT_DIR)/sg_lolm.$(OBJ): $(IN_DIR)/sg_lolm.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_lolm.c

$(OUT_DIR)/sg_lomis.$(OBJ): $(IN_DIR)/sg_lomis.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_lomis.c

$(OUT_DIR)/sg_looos.$(OBJ): $(IN_DIR)/sg_looos.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_looos.c

$(OUT_DIR)/sg_lopi.$(OBJ): $(IN_DIR)/sg_lopi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_lopi.c

$(OUT_DIR)/sg_losby.$(OBJ): $(IN_DIR)/sg_losby.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_losby.c

$(OUT_DIR)/sg_losta.$(OBJ): $(IN_DIR)/sg_losta.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_losta.c

$(OUT_DIR)/sg_losts.$(OBJ): $(IN_DIR)/sg_losts.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_losts.c

$(OUT_DIR)/sg_ptmi.$(OBJ): $(IN_DIR)/sg_ptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_ptmi.c

$(OUT_DIR)/sg_ptpi.$(OBJ): $(IN_DIR)/sg_ptpi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_ptpi.c

$(OUT_DIR)/sg_rback.$(OBJ): $(IN_DIR)/sg_rback.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_rback.c

$(OUT_DIR)/sg_tmr.$(OBJ): $(IN_DIR)/sg_tmr.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_tmr.c

$(OUT_DIR)/sg_util.$(OBJ): $(IN_DIR)/sg_util.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sg_util.c

$(OUT_DIR)/smsgptmi.$(OBJ): $(IN_DIR)/smsgptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/smsgptmi.c

$(OUT_DIR)/sgmrptmi.$(OBJ): $(IN_DIR)/sgmrptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sgmrptmi.c

$(OUT_DIR)/sgshptmi.$(OBJ): $(IN_DIR)/sgshptmi.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/sgshptmi.c

$(OUT_DIR)/smsgbdy1.$(OBJ): $(IN_DIR)/smsgbdy1.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/smsgbdy1.c

$(OUT_DIR)/smsgexms.$(OBJ): $(IN_DIR)/smsgexms.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/smsgexms.c

$(OUT_DIR)/lsg.$(OBJ): $(IN_DIR)/lsg.c
	$(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCsgFLAGS) $(IN_DIR)/lsg.c


#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libsg_td.a:$(sgOBJS)
	ar -cr libsg_td.a $(sgOBJS) 

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f libsg_td.a $(sgOBJS)

#********************************************************************30**
#
#        End of file:     lib_sg.mak@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:33 2015
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
