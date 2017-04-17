

/********************************************************************20**
  
     Name:     smcz_err.h - layer manager error defines for LCZ
  
     Type:     C include file
  
     Desc:     #defines and macros for the layer manager interface with 
               X2AP (called LCZ interface)
  
     File:     smcz_err.h
  
     Sid:      smcz_err.h@@/main/2 - Tue Aug 30 18:36:08 2011
  
     Prg:      sy
  
*********************************************************************21*/

#ifndef __SMCZERRH__
#define __SMCZERRH__

/*
*   smmg_err.h - layer manager error defines for LCZ
*
*   Defines declared in this file correspond to defines used by the 
*   following TRILLIUM software:
*     part no.                      description
*     --------    ----------------------------------------------
*     1000XXX                   CZCP
*/

/*
*     this software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000XXX                   CZCP
*/
 
/* defines */

/* macros */
#define SMCZLOGERROR(pst, errCls, errCode, errVal, errDesc) \
   SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId, \
             (Txt *)__FILE__, (S32)__LINE__, (ErrCls)errCls, \
             (ErrCode)errCode, (ErrVal)errVal, (Txt *)errDesc)

/* error codes */

#define ESMCZBASE       0                    /* Reserved */
#define ESMCZXXX        (ESMCZBASE + 0)      /* Reserved */
#define ERRSMCZ         (ESMCZBASE + 0)      /* Reserved */

#endif /* __SMCZERRH__ */

/********************************************************************30**
  
         End of file:     smcz_err.h@@/main/2 - Tue Aug 30 18:36:08 2011
  
*********************************************************************31*/

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
----------- -------- ---- -----------------------------------------------
/main/1      ----     sy              1. LTE-X2AP Initial release.
/main/2      ---      pt              1. LTE-X2AP 3.1 release.
*********************************************************************91*/
