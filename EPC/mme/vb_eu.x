
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     C Upper Interface structures

     File:     eu.x

     Sid:      vb_eu.x@@/main/1 - Mon Jun 28 19:35:35 2010

     Prg:      rs

*********************************************************************21*/
#ifndef __EU_X__
#define __EU_X__
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*
*   eu.x - eGTP user typedefs and function declarations
*
*   typedefs and function prototypes declared in this file correspond to 
*   typedefs function prototypes used by the following TRILLIUM software:
*     part no.                      description
*     --------    ----------------------------------------------
*     1000XXX                      eGTP
*/

/* function declarations */

#ifdef SS_MULTIPLE_PROCS
EXTERN S16 euActvInit ARGS((ProcId procId,Ent ent,Inst inst,Region region,Reason reason,
                            Void **xxCb));
#else /*SS_MULTIPLE_PROCS*/
EXTERN S16 euActvInit       ARGS((Ent ent, Inst inst, Region region, Reason
                                  reason));
#endif /*SS_MULTIPLE_PROCS*/
EXTERN S16 euInitExt        ARGS((void));
EXTERN S16 euActvTsk        ARGS((Pst *pst, Buffer *mBuf));


#ifdef __cplusplus
}
#endif /* _cplusplus */
#endif /* __EU_X__ */

/**********************************************************************

         End of file:     vb_eu.x@@/main/1 - Mon Jun 28 19:35:35 2010

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
/main/1      ---      ad              1. Initial Release for LTE-MME 1.1
*********************************************************************91*/

