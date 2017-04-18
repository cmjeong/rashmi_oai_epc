

/********************************************************************20**
  
        Name:    UDX  Control Interface
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for and prototypes
                  UDX Interface
 
        File:    udx.h

        Sid:      kw_udx.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:51 2014
  
        Prg:     chakrapani
  
*********************************************************************21*/

#ifndef __KW_UDX_H__
#define __KW_UDX_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @file udx.h
    @brief UDX Interface File (ckw.h)
*/
 
/* UDX Interface Hash Defines */

/* Loose Coupling define */
#define UDX_SEL_LC            0     /*!< Loose Coupling Option */
#define UDX_SEL_LWLC          1
#define KW_MAX_UDX 3


/* CKW Interface defines */
#define UDX_MAX_ENT_CFG       24    /*!< Maximum number of entities to configure */

#define   ERRUDX 0
#define   EUDXXXX 0
/* ckw_h_001.main_3 added support for L2 Measurement */   
#ifdef LTE_L2_MEAS
#define UDX_MAX_QCI           10
#endif
/* CKW Interface configuration type */
#define UDX_CFG_ADD           1     /*!< Add RLC Entity */
#define UDX_CFG_MODIFY        2     /*!< Modify RLC Entity */
#define UDX_CFG_DELETE        3     /*!< Delete RLC entity */
#define UDX_CFG_REESTABLISH   4     /*!< Re-establish RLC entity */
#define UDX_CFG_DELETE_UE     5     /*!< Release RLC entities per UE */
#define UDX_CFG_DELETE_CELL   6     /*!< Release RLC entities per Cell */

/* CKW RLC entity direction configuration */
#define UDX_CFG_DIR_UL        1     /*!< Unlink direction */
#define UDX_CFG_DIR_DL        2     /*!< Downlink direction */
#define UDX_CFG_DIR_BOTH      3     /*!< Both Downlink and Unlink */

/* CKW Configuration confirmations */
#define UDX_CFG_CFM_OK        1     /*!< Configuration confirmation success */
#define UDX_CFG_CFM_NOK       2     /*!< Configuration confirmation failed */

#if 0
/* CKW Configuration Failure Reasons */
#define CKW_CFG_REAS_NONE              0  /*!< No Failure */
#define CKW_CFG_REAS_RB_CREAT_FAIL     1  /*!< RB CB creation Failure */
#define CKW_CFG_REAS_UE_CREAT_FAIL     2  /*!< UE CB creation Failure */
#define CKW_CFG_REAS_CELL_CREAT_FAIL   3  /*!< CELL CB creation Failure */
#define CKW_CFG_REAS_RB_PRSNT          4  /*!< RB CB already present */
#define CKW_CFG_REAS_LCHTYPE_MIS       5  /*!< Logical channel type mismatch
                                           with mode */
#define CKW_CFG_REAS_RB_UNKWN          6  /*!< RB Cb unknown */
#define CKW_CFG_REAS_UE_UNKWN          7  /*!< UE Cb unknown */
#define CKW_CFG_REAS_CELL_UNKWN        8  /*!< Cell Cb unknown */
#define CKW_CFG_REAS_RB_DEL_FAIL       9  /*!< RB Cb Deletion Failure */
#define CKW_CFG_REAS_UE_DEL_FAIL      10  /*!< UE Cb Deletion Failure */
#define CKW_CFG_REAS_RB_REEST_FAIL    11  /*!< RB Cb Re establish Failure */
#define CKW_CFG_REAS_RB_MODE_MIS      12  /*!< RB Cb Mode mismatch */
#define CKW_CFG_REAS_REEST_FAIL       13  /*!< RB Cb Re-establishment Failed */
#define CKW_CFG_REAS_RECFG_FAIL       14  /*!< RB Cb Re-configuration Failed */
#define CKW_CFG_REAS_INVALID_CFG      15  /*!< Invalid Configuration Type */
#define CKW_CFG_REAS_SAME_UEID        16  /*!< UE Ids match in ChngUeId Request */
#define CKW_CFG_REAS_CELL_DEL_FAIL    17  /*!< Cell Cb Deletion Failure */
#define CKW_CFG_REAS_INVALID_LCHID    18  /*!< Invalid LChId */
#define CKW_CFG_REAS_INVALID_DIR      19  /*!< Invalid Direction */
#define CKW_CFG_REAS_UE_EXISTS        20  /*!< UE ID already exists */
#endif

/***********************************************************************
        Defines for  CKW Interface Events
 ***********************************************************************/
#define UDX_EVT_BND_REQ       0x01     /*!< Bind Request */
#define UDX_EVT_BND_CFM       0x02     /*!< Bind Confirm */
#define UDX_EVT_UBND_REQ      0x03     /*!< Unbind Request */
#define UDX_EVT_CFG_REQ       0x04     /*!< Config Request */
#define UDX_EVT_CFG_CFM       0x05     /*!< Config Confirm */
#define UDX_EVT_UEIDCHG_REQ   0x06     /*!< UE Id Change Request */
#define UDX_EVT_UEIDCHG_CFM   0x07     /*!< UE Id Change Confirm */
#define UDX_EVT_STA_UPD_REQ   0x08
#define UDX_EVT_STA_UPD_CFM   0x09
#define UDX_EVT_STA_PDU_REQ   0x0A

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

  
/********************************************************************30**
         End of file:     kw_udx.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:51 2014
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
/main/1      ---      cp   1. initial release.
/main/3      ---      gk   1. LTERLC Release 2.1.
/main/4      ckw_h_001.main_3 ap 1. Added support for L2 Measurement.
*********************************************************************91*/

