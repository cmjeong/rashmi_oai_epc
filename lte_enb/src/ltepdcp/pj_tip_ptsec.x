


/********************************************************************20**
  
        Name:    LTE PDCP-TIP Interface file 
    
        Type:    C include file
  
        Desc:    This file contains all the data structures and 
                 prototypes for LTE PDCP - TIP.
 
        File:    pj_tip_ptsec.x

        Sid:      pj_mspdt2k_ptsec.x@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:43:05 2014
  
        Prg:     N/A 
  
*********************************************************************21*/
/** @file pj_mspdt2k_ptsec.x
@brief PDCP Product Structures, prototypes
*/

#ifndef __PJTIPPTSECX__
#define __PJTIPPTSECX__


/*
 *     The structures and variables declared in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000371      LTE-PDCP
 *
*/
 
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/******************************************************************************
*                     EXTERN Declarations 
******************************************************************************/

EXTERN S16 pjTipSendToCipher ARGS ((
PjLibTrans  *libTrans, 
Buffer *mBuf,
Buffer **opSdu
));

EXTERN S16 pjTipSendToDeCipher ARGS ((
PjLibTrans  *libTrans, 
Buffer *mBuf,
Buffer **opSdu
));

EXTERN S16 pjSendToTipKeyDeriveFunc ARGS ((
PjLibTrans  libTrans, 
U8 *key
));

EXTERN S16 pjTipKDF ARGS ((
PjLibTrans  libTrans, 
U8 *key
));

EXTERN S16 pjTipIntegProtPkt ARGS ((
PjLibTrans  *libTrans,
Buffer **mBuf
));

EXTERN S16 pjTipIntegProtVerifyPkt ARGS ((
PjLibTrans  *libTrans,
Buffer **mBuf,
U32 macI
));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PJTIPPTSECX__ */

  
/********************************************************************30**
  
         End of file:     pj_mspdt2k_ptsec.x@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:43:05 2014
         End of file:     pj_mspdt2k_ptsec.x@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:43:05 2014
  
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
/main/1      ---       nm  1. Initial release.
*********************************************************************91*/
