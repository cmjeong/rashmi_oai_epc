
#ifndef __WRAC_RMUH__
#define __WRAC_RMUH__

#define WRAC_RMU_REGION  0 
#define WRAC_RMU_POOL    0 


#define WRAC_RMUFREEBUF(ptr, len)\
 SPutSBuf(WRAC_RMU_REGION, WRAC_RMU_POOL, ptr, len) 

#define WRAC_RMUBUFALLOC(ptr, len) \
{ \
  if(ROK != SGetSBuf(WRAC_RMU_REGION, WRAC_RMU_POOL, ptr, len)) \
  { \
    (*ptr) = NULLP; \
  }\
}

#define MTYPE_ADMITREQ 1
#define MTYPE_RELREQ   2
#define MTYPE_RECFGREQ 3
#define MTYPE_HOREQ    4

#define RMAC_RMU_BNDREQ(_pst, _suId, _spId)     WrLiRmuBndReq(_pst, _suId, _spId);

#endif /* __WRAC_RMUH__*/
