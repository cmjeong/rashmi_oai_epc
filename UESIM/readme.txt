#Compilation 
#for linux gcc 32 bit
 make -f ue_stack.mak clean BLDENV=lnx_e2e_acc MACHINE=BIT32 acc

#for linux gcc 32 bit (default)
 make -f ue_stack.mak clean BLDENV=lnx_e2e_acc MACHINE=BIT64 acc
