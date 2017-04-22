
/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     uz.x

     Sid:      uz.x@@/main/3 - Mon Jan 10 22:16:49 2011

     Prg:      rs

*********************************************************************21*/
#ifndef __UZ_X__
#define __UZ_X__
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*
*   uz.x - S1AP user typedefs and function declarations
*
*   typedefs and function prototypes declared in this file correspond to 
*   typedefs function prototypes used by the following TRILLIUM software:
*     part no.                      description
*     --------    ----------------------------------------------
*     1000XXX                      S1AP
*/

/* function declarations */

#ifdef SS_MULTIPLE_PROCS
EXTERN S16 uzActvInit ARGS((ProcId procId,Ent ent,Inst inst,Region region,Reason reason,
                            Void **xxCb));
#else /*SS_MULTIPLE_PROCS*/
EXTERN S16 uzActvInit       ARGS((Ent ent, Inst inst, Region region, Reason
                                  reason));
#endif /*SS_MULTIPLE_PROCS*/
EXTERN S16 uzInitExt        ARGS((void));
EXTERN S16 uzActvTsk        ARGS((Pst *pst, Buffer *mBuf));


#ifdef __cplusplus
}
#endif /* _cplusplus */
#endif /* __UZ_X__ */

/**********************************************************************

         End of file:     uz.x@@/main/3 - Mon Jan 10 22:16:49 2011

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
/main/3      ---      vvashishth  1. Updated for S1AP release 3.1
*********************************************************************91*/

