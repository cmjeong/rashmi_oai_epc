

/********************************************************************20**
  
        Name:    Convergence Layer Picochup specific
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for CL PC
 
        File:    ys_pc.h

        Sid:      ys_stub.h@@/main/2 - Thu Dec  2 02:27:24 2010
  
        Prg:     pkumar
  
*********************************************************************21*/

#ifndef __YS_STUB_H__
#define __YS_STUB_H__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*__cplusplus*/

#ifdef YS_TST_STUB

#define YS_STUB_NUM_PARAM_RESP_TLVs 6
#define YS_STUB_PARAM_RESP_TLVS { \
    {DlBwSupp, 8}, \
    {UlBwSupp, 8}, \
    {DlModSupp, 7}, \
    {UlModSupp, 7}, \
    {NumAntSupp, 2}, \
    {PhyState, 0} }

#define YS_STUB_NUM_CONFIG_RESP_TLVs 0

#define YS_STUB_NUM_CRCS 3

#define YS_STUB_NUM_RACH_PREAMBLES 3

#endif /* YS_TST_STUB */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __YS_STUB_H__ */

/********************************************************************30**
  
         End of file:     ys_stub.h@@/main/2 - Thu Dec  2 02:27:24 2010
  
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
