

/********************************************************************20**

     Name:     X2AP Layer

     Type:     C source file

     Desc:     C Source code for error definitions

     File:     cz_err.h

     Sid:      cz_err.h@@/main/2 - Tue Aug 30 18:36:04 2011

     Prg:      sy

*********************************************************************21*/

#ifndef __CZERRH__
#define __CZERRH__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef SLOGERROR
#define SLOGERROR  SLogError
#endif /* SLOGERROR */

#ifdef SS_MULTIPLE_PROCS

#define CZLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(czCbPtr->init.ent, czCbPtr->init.inst, czCbPtr->init.procId, \
                   __FILE__, __LINE__, errCls, errCode, errVal, errDesc)

#if (ERRCLASS & ERRCLS_DEBUG)    
#define CZLOGERROR_DEBUG(errCode, errVal, errDesc) \
        SLogError(czCbPtr->init.ent, czCbPtr->init.inst, czCbPtr->init.procId, \
                   __FILE__, __LINE__, ERRCLS_DEBUG, errCode, errVal, errDesc)
#else /* (ERRCLASS & ERRCLS_DEBUG) */
#define CZLOGERROR_DEBUG(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

#if (ERRCLASS & ERRCLS_INT_PAR)    
#define CZLOGERROR_INTFC(errCode, errVal, errDesc) \
        SLogError(czCbPtr->init.ent, czCbPtr->init.inst, czCbPtr->init.procId, \
                   __FILE__, __LINE__, ERRCLS_INT_PAR, errCode, errVal, errDesc)
#else /* (ERRCLASS & ERRCLS_INT_PAR) */
#define CZLOGERROR_INTFC(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#if (ERRCLASS & ERRCLS_ADD_RES)    
#define CZLOGERROR_ADD_RES(errCode, errVal, errDesc) \
        SLogError(czCbPtr->init.ent, czCbPtr->init.inst, czCbPtr->init.procId, \
                   __FILE__, __LINE__, ERRCLS_ADD_RES, errCode, errVal, errDesc)
#else /* (ERRCLASS & ERRCLS_INT_PAR) */
#define CZLOGERROR_ADD_RES(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#else /* SS_MULTIPLE_PROCS */

#define CZLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(czCb.init.ent, czCb.init.inst, czCb.init.procId, \
                   __FILE__, __LINE__, errCls, errCode, errVal, errDesc)

#if (ERRCLASS & ERRCLS_DEBUG)    
#define CZLOGERROR_DEBUG(errCode, errVal, errDesc) \
        SLogError(czCb.init.ent, czCb.init.inst, czCb.init.procId, \
                   __FILE__, __LINE__, ERRCLS_DEBUG, errCode, errVal, errDesc)
#else /* (ERRCLASS & ERRCLS_DEBUG) */
#define CZLOGERROR_DEBUG(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

#if (ERRCLASS & ERRCLS_INT_PAR)    
#define CZLOGERROR_INTFC(errCode, errVal, errDesc) \
        SLogError(czCb.init.ent, czCb.init.inst, czCb.init.procId, \
                   __FILE__, __LINE__, ERRCLS_INT_PAR, errCode, errVal, errDesc)
#else /* (ERRCLASS & ERRCLS_INT_PAR) */
#define CZLOGERROR_INTFC(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#if (ERRCLASS & ERRCLS_ADD_RES)    
#define CZLOGERROR_ADD_RES(errCode, errVal, errDesc) \
        SLogError(czCb.init.ent, czCb.init.inst, czCb.init.procId, \
                   __FILE__, __LINE__, ERRCLS_ADD_RES, errCode, errVal, errDesc)
#else /* (ERRCLASS & ERRCLS_INT_PAR) */
#define CZLOGERROR_ADD_RES(errCode, errVal, errDesc) 
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#endif /* SS_MULTIPLE_PROCS */

#define   ERRCZ       0
#define   ECZXXX      ERRCZ

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CZERRH__ */

/**********************************************************************

         End of file:     cz_err.h@@/main/2 - Tue Aug 30 18:36:04 2011

**********************************************************************/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sy    1. LTE-X2AP Initial Release
/main/2      ---      pt    1. LTE-X2AP 3.1 release.
*********************************************************************91*/
