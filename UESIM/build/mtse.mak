#-------------------------------------------------------------#
#Makefile for product mt - script generated.
#Only the $(CCmtFLAGS) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCmtFLAGS=-DBIT_64 -DSS_MT_TMR#<---Insert mt specific defines here
#CCmtFLAGS=-DSS_MT_TMR#<---Insert mt specific defines here:32BIT_CAV

#-------------------------------------------------------------#
#File/Obj macros             
#-------------------------------------------------------------#
mtSRCS= \
	$(IN_DIR)/jz_mem.c\
	$(IN_DIR)/jz_cmem.c\
	$(IN_DIR)/jz_id.c\
	$(IN_DIR)/jz_ss.c\
	$(IN_DIR)/jz_gen.c\
	$(IN_DIR)/jz_msg.c\
	$(IN_DIR)/jz_pack.c\
	$(IN_DIR)/jz_queue.c\
	$(IN_DIR)/jz_strm.c\
	$(IN_DIR)/jz_task.c\
	$(IN_DIR)/jz_timer.c

mtOBJS= \
	$(OUT_DIR)/jz_mem.$(OBJ)\
	$(OUT_DIR)/jz_cmem.$(OBJ)\
	$(OUT_DIR)/jz_id.$(OBJ)\
	$(OUT_DIR)/jz_ss.$(OBJ)\
	$(OUT_DIR)/jz_gen.$(OBJ)\
	$(OUT_DIR)/jz_msg.$(OBJ)\
	$(OUT_DIR)/jz_pack.$(OBJ)\
	$(OUT_DIR)/jz_queue.$(OBJ)\
	$(OUT_DIR)/jz_strm.$(OBJ)\
	$(OUT_DIR)/jz_task.$(OBJ)\
	$(OUT_DIR)/jz_timer.$(OBJ)

MT_INC=\
   $(IN_DIR)/jz_timer.x  \
   $(IN_DIR)/jz_task.h $(IN_DIR)/jz_task.x  \
   $(IN_DIR)/jz_mem.h $(IN_DIR)/jz_mem.x $(IN_DIR)/jz_msg.h $(IN_DIR)/jz_msg.x \
   $(IN_DIR)/jz_gen.h $(IN_DIR)/jz_gen.x $(IN_DIR)/jz_dep.x $(IN_DIR)/jz_dep.h  \
   $(IN_DIR)/jz_err.h $(IN_DIR)/jz_ss.x $(IN_DIR)/jz_cmem.h $(IN_DIR)/jz_cmem.x \
   $(IN_DIR)/jz_strm.h $(IN_DIR)/jz_strm.x  \
   $(IN_DIR)/jz_ss.h $(IN_DIR)/jz_ss.x


ALL_INC=$(MT_INC) $(CM_INC)

#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/jz_mem.$(OBJ): $(IN_DIR)/jz_mem.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_mem.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_mem.c
$(OUT_DIR)/jz_cmem.$(OBJ): $(IN_DIR)/jz_cmem.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_cmem.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_cmem.c
$(OUT_DIR)/jz_id.$(OBJ): $(IN_DIR)/jz_id.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_id.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_id.c
$(OUT_DIR)/jz_ss.$(OBJ): $(IN_DIR)/jz_ss.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_ss.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_ss.c
$(OUT_DIR)/jz_gen.$(OBJ): $(IN_DIR)/jz_gen.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_gen.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_gen.c
$(OUT_DIR)/jz_msg.$(OBJ): $(IN_DIR)/jz_msg.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_msg.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_msg.c
$(OUT_DIR)/jz_pack.$(OBJ): $(IN_DIR)/jz_pack.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_pack.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_pack.c
$(OUT_DIR)/jz_queue.$(OBJ): $(IN_DIR)/jz_queue.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_queue.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_queue.c
$(OUT_DIR)/jz_strm.$(OBJ): $(IN_DIR)/jz_strm.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_strm.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_strm.c
$(OUT_DIR)/jz_task.$(OBJ): $(IN_DIR)/jz_task.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_task.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_task.c
$(OUT_DIR)/jz_timer.$(OBJ): $(IN_DIR)/jz_timer.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/jz_timer.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/jz_timer.c

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libmt.a:$(mtOBJS)
	ar -cr $(OUT_DIR)/libmt.a $(mtOBJS)	

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f libmt.a $(mtOBJS)

