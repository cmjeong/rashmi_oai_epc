
#ifndef __NLAC_NLUH__
#define __NLAC_NLUH__

#define NLAC_NLU_REGION  0 
#define NLAC_NLU_POOL    0 


#define NLAC_NLUFREEBUF(ptr, len)\
 SPutSBuf(NLAC_NLU_REGION, NLAC_NLU_POOL, ptr, len) 

#define NLAC_NLUBUFALLOC(ptr, len) \
{ \
  if(ROK != SGetSBuf(NLAC_NLU_REGION, NLAC_NLU_POOL, ptr, len)) \
  { \
    (*ptr) = NULLP; \
  }\
}

#if 0
#define MTYPE_ADMITREQ 1
#define MTYPE_RELREQ   2
#define MTYPE_RECFGREQ 3
#define MTYPE_HOREQ    4
#endif
#endif /* __NLAC_NLUH__*/
