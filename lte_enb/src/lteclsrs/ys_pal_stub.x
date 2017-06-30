

/********************************************************************20**
  
        Name:    Convergence Layer Picochup specific
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for CL PC
 
        File:    ys_pc.h

        Sid:      ys_stub.x@@/main/2 - Thu Dec  2 02:27:25 2010
  
        Prg:     pkumar
  
*********************************************************************21*/

#ifndef __YS_STUB_X__
#define __YS_STUB_X__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*__cplusplus*/

#ifdef YS_TST_STUB

typedef struct ysStubTlvArray
{
  L1TlvTag_e   tag : 8;
  U16          val;
} YsStubTlvArray;

EXTERN Void ysStubSendCfgRsp ARGS ((Void));
EXTERN Void ysStubSendParamRsp ARGS ((Void));
EXTERN Void ysStubSendTtiInd ARGS ((CmLteTimingInfo  *timingInfo));
EXTERN Void ysStubSendCrcInd ARGS ((CmLteTimingInfo  *timingInfo));
EXTERN Void ysStubSendRachInd ARGS ((CmLteTimingInfo  *timingInfo));
EXTERN S16 ysStubDumpMsg ARGS ((YsPcL1Msg *l1Msg));

#endif /* YS_TST_STUB */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __YS_STUB_X__ */

/********************************************************************30**
  
         End of file:     ys_stub.x@@/main/2 - Thu Dec  2 02:27:25 2010
  
*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**

     ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
*********************************************************************91*/
