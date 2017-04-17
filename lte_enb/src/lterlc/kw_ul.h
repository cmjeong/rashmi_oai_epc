


/********************************************************************20**
  
        Name:     LTE RLC file for uplink and non real time tasks 
    
        Type:     C include file
  
        Desc:     This file contains helper macros for RLC uplink
                  and non real time tasks
 
        File:     kw_ul.h

        Sid:      kw_ul.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB_GA/5 - Fri Feb 12 12:09:16 2016
  
        Prg:      ag
  
*********************************************************************21*/
/** 
 * @file kw_ul.h
 * @brief RLC uplink helper macros
*/

/** @ingroup uplink_group
*/

#ifndef __KW_ULH__
#define __KW_ULH__

/**
 * @def KW_MEAS_IS_UL_IP_MEAS_ON_FOR_RB
 *
 *    This macro is used to check if UL IP throughput measurement is ON
 *    or off for the passed rb
 *
 *    Returns TRUE(non-zero) if measurement is ON else FALSE (zero)
 *
 * @param[in] _gCb     RLC UL Cb
 * @param[in] _rbCb    RLC uplink control block
 *
*/ 
#define KW_MEAS_IS_UL_IP_MEAS_ON_FOR_RB(_gCb, _rbCb)  \
     ((_rbCb->rlcId.rbType == CM_LTE_DRB) && \
     (_gCb->u.ulCb->kwL2Cb.measOn[_rbCb->qci] & LKW_L2MEAS_UL_IP) && \
     (_rbCb->rbL2Cb.measOn & LKW_L2MEAS_UL_IP))
#endif /* __KW_ULH__ */
  
/********************************************************************30**
  
         End of file:     kw_ul.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB_GA/5 - Fri Feb 12 12:09:16 2016
  
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
/main/1      ---       mn  1. Initial release.
*********************************************************************91*/
