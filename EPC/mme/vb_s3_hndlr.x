/******************************************************************************

     Name:    vb_mme_s3_hndlr.x
     
     Desc:    Trillium LTE CNE - S3 Interface Handler functions

******************************************************************************/

#ifndef _VB_MME_S3_HNDLR_X_
#define _VB_MME_S3_HNDLR_X_

#ifdef __cplusplus
EXTERN "C" 
{
#endif
/**************************************************************************//**
 *
 * @brief 
 *    Handles Handover Preparation Message received from eNodeB
 *             
 * @param[in]  pUeCb
 *    Pointer to UE Control Block for which handover required is received
 * @param[in]  tgtMmeIpAddr
 *    Pointer to Target MME's IP Address
 * 
 * @return
 *    SUCCESS if Forward Relocation Request is send to MME successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeSndS3FRReq
(
VbMmeUeCb      *pUeCb,
CmTptAddr      *pTgtMmeIpAddr
);


/**************************************************************************//**
 *
 * @brief 
 *    Handles Fowrard Relocation Request received from MME over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Forward Relocation Request
 * 
 * @return
 *    SUCCESS if Forward Relocation Request is handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3FRReq
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);



/**************************************************************************//**
 *
 * @brief 
 *    Handles Fowrard Relocation Response received from MME over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Forward Relocation Response
 * 
 * @return
 *    SUCCESS if Forward Relocation Response is handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3FRRsp
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);


/**************************************************************************//**
 *
 * @brief 
 *    Builds and Sends a forward relocation response to MME
 *             
 * @param[in]  pUeCb
 *    Pointer to UE Control Block for which S1 Handover is being handled
 * @param[in]  cause
 *    GTP Cause Value to be sent to MME
 * 
 * @return
 *    SUCCESS if Forward Relocation Response is send to MME successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeSndS3FRRsp
(
VbMmeUeCb      *pUeCb,
U32            cause
);


/**************************************************************************//**
 *
 * @brief 
 *    Sends Forward Relocation Complete notification message to MME
 *             
 * @param[in]  pUeCb
 *    Pointer to UE Control Block for which handover required is received
 * 
 * @return
 *    SUCCESS if Forward Relocation Complete Notification is sen3 to MME 
 *    successfully otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeSndS3FRCmplNotif
(
VbMmeUeCb      *pUeCb
);


/**************************************************************************//**
 *
 * @brief 
 *    Handles Fowrard Relocation Complete Notification
 *    received from MME over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Forward Relocation Complete
 *    Notification
 * 
 * @return
 *    SUCCESS if Forward Relocation Complete Notification is
 *    handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3FRCmplNotif
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);

/**************************************************************************//**
 *
 * @brief 
 *    Builds and Sends a forward relocation Compelete Ack to MME
 *             
 * @param[in]  pUeCb
 *    Pointer to UE Control Block for which S1 Handover is being handled
 * @param[in]  cause
 *    GTP Cause Value to be sent to MME
 * 
 * @return
 *    SUCCESS if Forward Relocation Complete Ack is send to MME successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeSndS3FRCmplAck
(
VbMmeUeCb      *pUeCb,
U32            cause
);


/**************************************************************************//**
 *
 * @brief 
 *    Handles Fowrard Relocation Complete Acknowledge
 *    received from MME over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Forward Relocation Complete
 *    Acknowledge
 * 
 * @return
 *    SUCCESS if Forward Relocation Complete Acknowledge is
 *    handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3FRCmplAck
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);


/**************************************************************************//**
 *
 * @brief 
 *    Handles Fowrard Relocation Response received from MME over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Forward Relocation Response
 * 
 * @return
 *    SUCCESS if Forward Relocation Response is handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3FRRsp
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);


/**************************************************************************//**
 *
 * @brief 
 *    Handles Fowrard Relocation Complete Acknowledge
 *    received from MME over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Forward Relocation Complete
 *    Acknowledge
 * 
 * @return
 *    SUCCESS if Forward Relocation Complete Acknowledge is
 *    handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3FRCmplAck
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);


/**************************************************************************//**
 *
 * @brief 
 *    Handles Fowrard Relocation Request received from MME over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Forward Relocation Request
 * 
 * @return
 *    SUCCESS if Forward Relocation Request is handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3FRReq
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);

/**************************************************************************//**
 *
 * @brief 
 *    Handles Fowrard Relocation Complete Notification
 *    received from MME over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Forward Relocation Complete
 *    Notification
 * 
 * @return
 *    SUCCESS if Forward Relocation Complete Notification is
 *    handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3FRCmplNotif
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);

/**************************************************************************//**
 *
 * @brief 
 *    Sends Relocation Cancel Request message to SGSN
 *             
 * @param[in]  pUeCb
 *    Pointer to UE Control Block for which handover Cancel is received
 * 
 * @return
 *    SUCCESS if Relocation Cancel Request is sent to SGSN 
 *    successfully otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeSndS3RCReq
(
VbMmeUeCb      *pUeCb
);

/**************************************************************************//**
 *
 * @brief 
 *    Handles Relocation Cancel Request
 *    received from SGSN over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Relocation Release Request
 * 
 * @return
 *    SUCCESS if Relocation Release Request is
 *    handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3RCReq
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);

/**************************************************************************//**
 *
 * @brief 
 *    Sends Relocation Cancel Response message to SGSN
 *             
 * @param[in]  pUeCb
 *    Pointer to UE Control Block for which handover Cancel is received
 * @param[in]  cause
 *    Cause value to be sent in Relocation Cancel Response
 * 
 * @return
 *    SUCCESS if Relocation Cancel Response is sent to MME 
 *    successfully otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeSndS3RCRsp
(
VbMmeUeCb      *pUeCb,
U32            cause
);

/**************************************************************************//**
 *
 * @brief 
 *    Handles Relocation Cancel Response received from SGSN over S3 interface
 *             
 * @param[in]  pLocAddr
 *    Pointer to local address at which the request is received
 * @param[in]  pRemAddr
 *    Pointer to remote address from where the request is received
 * @param[in]  locTeid
 *    Local Teid of S3 tunnel
 * @param[in]  transId
 *    Transaction ID
 * @param[in]  pEgMsg
 *    Pointer to EgMsg structure containing Relocation Cancel Response
 * 
 * @return
 *    SUCCESS if Relocation Cancel Response is handled successfully
 *    otherwise FAILURE
 *
 *****************************************************************************/
PUBLIC S16 vbMmeIncS3RCRsp
(
CmTptAddr   *pLocAddr,
CmTptAddr   *pRemAddr,
TknU32      locTeid,
TknU32      transId,
EgMsg       *pEgMsg 
);


#ifdef __cplusplus
}
#endif
#endif
