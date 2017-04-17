
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_lclctxtrel.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_UMM_LCLCTXTREL_H__
#define __WR_UMM_LCLCTXTREL_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/** 
 * @brief This structure contains the control parameters to perform local
 *        context release successfully.
 *
 * @details These are the structure members
 * - U8 schdCfmRcvd   Flag to indicate scheduler UE release confirm status
 * - U8 l1CfmRcvd     Flag to indicate L1 UE release confirm status
 * - U8 damCfmRcvd    Flag to indicate DAM UE release confirm status
 * - U8 rrcCfmRcvd    Flag to indicate RRC data TX confirm status
 * - U8 rrmRespRcvd   Flag to indicate RRM UE Relese Response status
 */
typedef struct wrUmmLclCtxtRelTrans
{
   U8                        schdCfmRcvd;
   U8                        l1CfmRcvd;
   U8                        damCfmRcvd;
   U8                        rrcCfmRcvd;
   U8                        rrmRespRcvd;
} WrUmmLclCtxtRelTrans;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_UMM_LCLCTXTREL_H__ */

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
