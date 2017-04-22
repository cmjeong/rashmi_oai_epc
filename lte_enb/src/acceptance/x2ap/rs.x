
/********************************************************************20**

     Name:     X2AP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     rs.x

     Sid:      rs.x@@/main/2 - Tue Aug 30 18:36:07 2011

     Prg:      sy

*********************************************************************21*/
#ifndef __RS_X__
#define __RS_X__
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*
*   rs.x - X2AP user typedefs and function declarations
*
*   typedefs and function prototypes declared in this file correspond to 
*   typedefs function prototypes used by the following TRILLIUM software:
*     part no.                      description
*     --------    ----------------------------------------------
*     1000XXX                      X2AP
*/

/* function declarations */

#ifdef SS_MULTIPLE_PROCS
EXTERN S16 rsActvInit ARGS((ProcId procId,Ent ent,Inst inst,Region region,Reason reason,
                            Void **xxCb));
#else /*SS_MULTIPLE_PROCS*/
EXTERN S16 rsActvInit       ARGS((Ent ent, Inst inst, Region region, Reason
                                  reason));
#endif /*SS_MULTIPLE_PROCS*/
EXTERN S16 rsInitExt        ARGS((void));
EXTERN S16 rsActvTsk        ARGS((Pst *pst, Buffer *mBuf));


#ifdef __cplusplus
}
#endif /* _cplusplus */
#endif /* __RS_X__ */

/**********************************************************************

         End of file:     rs.x@@/main/2 - Tue Aug 30 18:36:07 2011

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
/main/1      ---      sy             1. LTE-X2AP Initial release.
/main/2      ---      pt             1. LTE-X2AP 3.1 release.
*********************************************************************91*/
