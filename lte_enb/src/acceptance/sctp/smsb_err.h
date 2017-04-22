

/********************************************************************20**

     Name:     stack manager - interface with MPC8260 driver - error

     Type:     C include file

     Desc:     Error defines required by the stack manager.

     File:     smsb_err.h

     Sid:      smsb_err.h@@/main/3 - Thu Jul 26 07:53:55 2007

     Prg:      wvdl

*********************************************************************21*/

#ifndef __SMSDERRH_
#define __SMSDERRH_

/* defines */

/* management interface - SCTP error codes */

#define  ESMSBBASE   (ERRSMSB   + 0)   /* reserved */
#define  ESMSBXXX    (ESMSBBASE + 0)   /* reserved */


#define   ESMSB001      (ERRSMSB +    1)    /*   smsbexms.c:  */

#define SLOGERROR SLogError

#define SMSBLOGDEBUGERROR(errVal, errCode, errDesc, pst) \
        SLOGERROR(pst->srcEnt, pst->srcInst, pst->srcProcId,\
                   __FILE__, __LINE__, \
                  ERRCLS_DEBUG, errCode, errVal, errDesc)

#endif /* __SMSDERRH_ */


/********************************************************************30**

         End of file:     smsb_err.h@@/main/3 - Thu Jul 26 07:53:55 2007

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
------------ -------- ---- ----------------------------------------------
/main/2      ---      wvdl 1. Initial version
/main/2      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000
/main/3      ---   rsr/ag  1. Updated for Release of 1.3
*********************************************************************91*/

