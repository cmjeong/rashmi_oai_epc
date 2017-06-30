
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_ctxtmod.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_UMM_CTXTMOD_H__
#define __WR_UMM_CTXTMOD_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */



#define WR_CTXT_MOD_UE_TRANS_ID           0x01

#define WR_CTXT_MOD_WAIT                  0x01
#define WR_CTXT_MOD_SEND_SUCC             0x02
#define WR_CTXT_MOD_SEND_FAIL             0x03

typedef struct wrUmmCtxtModTrans
{
   Bool                 secCfg;
   Bool                 ambrCfg;
   Bool                 updSecCap;
   Bool                 updLai;
   Bool                 schdUeCfgCfmRcvd;
   WrRegLai             regLai;
   U32                  dlAmbr;
   U32                  ulAmbr;
   TknU32               subscProfileId;
   TknU32               csFallBackInd;
   TknU32               csgMembrSta;
   U32                  status;
   WrUmmMsgCause        cause;
} WrUmmCtxtModTrans;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_UMM_CTXTMOD_H__ */

/********************************************************************30**

           End of file:    $SID$

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
------------ -------- ---- ----------------------------------------------
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
