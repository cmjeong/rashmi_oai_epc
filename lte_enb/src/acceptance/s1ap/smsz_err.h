

/********************************************************************20**
  
     Name:     smsz_err.h - layer manager error defines for LMG
  
     Type:     C include file
  
     Desc:     #defines and macros for the layer manager interface with 
               S1AP (called LSZ interface)
  
     File:     smsz_err.h
  
     Sid:      smsz_err.h@@/main/3 - Mon Jan 10 22:16:46 2011
  
     Prg:      pk
  
*********************************************************************21*/

#ifndef __SMMGERRH__
#define __SMMGERRH__

/*
*   smmg_err.h - layer manager error defines for LMG
*
*   Defines declared in this file correspond to defines used by the 
*   following TRILLIUM software:
*     part no.                      description
*     --------    ----------------------------------------------
*     1000XXX                   MGCP
*/

/*
*     this software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000XXX                   MGCP
*/
 
/* defines */

/* macros */
#define SMMGLOGERROR(pst, errCls, errCode, errVal, errDesc) \
   SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId, \
             (Txt *)__FILE__, (S32)__LINE__, (ErrCls)errCls, \
             (ErrCode)errCode, (ErrVal)errVal, (Txt *)errDesc)

/* error codes */

#define ESMMGBASE       0                    /* Reserved */
#define ESMMGXXX        (ESMMGBASE + 0)      /* Reserved */
#define ERRSMMG         (ESMMGBASE + 0)      /* Reserved */

#define   ESMMG001      (ERRSMMG +    1)    /*   smmgptmi.c: 560 */
#define   ESMMG002      (ERRSMMG +    2)    /*   smmgptmi.c: 600 */
#define   ESMMG003      (ERRSMMG +    3)    /*   smmgptmi.c: 639 */
#define   ESMMG004      (ERRSMMG +    4)    /*   smmgptmi.c: 677 */

#endif /* __SMMGERRH__ */

/********************************************************************30**
  
         End of file:     smsz_err.h@@/main/3 - Mon Jan 10 22:16:46 2011
  
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
/main/3      ---      vvashishth  1. Updated for S1AP release 3.1
*********************************************************************91*/
