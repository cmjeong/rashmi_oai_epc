

/********************************************************************20**
  
        Name:     LTE RLC file 
    
        Type:     C include file
  
        Desc:     This file contain the hash definations for RLC 
 
        File:     kw.h

        Sid:      kw_dl.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:45 2014
  
        Prg:      na 
  
*********************************************************************21*/
/** @file kw.h
@brief RLC Hash definitions
*/

#ifndef __KW_DLH__
#define __KW_DLH__

/* DBM Module Macros */
#define KW_DBM_FETCH_DL_RBCB(_rbId, _rbType, _ueCb, _rbCb)     \
{                                                           \
   KwDlRbCb  **_rbCbLst;                                         \
   _rbCbLst = (_rbType==CM_LTE_SRB)?_ueCb->srbCb:_ueCb->drbCb;\
   if (_rbCbLst[_rbId] != NULLP)                            \
   {                                                        \
      _rbCb = _rbCbLst[_rbId];                              \
   }                                                        \
   else                                                     \
   {                                                        \
      _rbCb = NULLP;                                        \
   }                                                        \
}

#define KW_DBM_FETCH_CELL_DL_RBCB(_rbId, _rbCbLst, _rbCb)      \
{                                                           \
   if (_rbCbLst[_rbId] != NULLP)                            \
   {                                                        \
      _rbCb = _rbCbLst[_rbId];                              \
   }                                                        \
   else                                                     \
   {                                                        \
      _rbCb = NULLP;                                        \
   }                                                        \
}

#define KW_DBM_FILL_UE_DL_RBCB(_rbCb,_ueCb,_rbId, _rbType)    \
{                                                           \
   KwDlRbCb **_rbCbLst;                     \
   _rbCb->rlcId.rbId = _rbId;                        \
   _rbCbLst = (_rbType==CM_LTE_SRB)?_ueCb->srbCb:_ueCb->drbCb;\
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
}
#define KW_DBM_FILL_CELL_DL_RBCB(_rbCb, _rbCbLst, _rbId)     \
{                                                           \
   _rbCb->rlcId.rbId = _rbId;                        \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
}

#define KW_DBM_DELETE_DL_RBCB(_cb,_rbCb)                           \
{                                                           \
   /* Free memory for rbCb */                               \
   KW_FREE(_cb,_rbCb, sizeof(KwDlRbCb));                            \
   KW_LMM_RB_STS_DEC(_cb);                                     \
}

#define KW_CREATE_UM_PDU(_cb,_rbCb,_pdu,_fi,_pduInfo,_ret)\
{\
   MsgLen bytesSent = 0;\
   _ret = kwUmmCreatePdu(_cb,_rbCb,&(_pdu),_fi);\
   if (_ret == ROK )\
   {\
      SFndLenMsg(pdu, &bytesSent);\
      _pduInfo->mBuf[(_pduInfo->numPdu)++] = _pdu;\
      _cb->genSts.bytesSent += bytesSent;\
      _pdu = NULLP;\
   }\
}



#endif /* __KW_DLH__ */
  
/********************************************************************30**
  
         End of file:     kw_dl.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:45 2014
  
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
/main/2      ---       nm  1. LTERLC Release 2.1
/main/3      kw001.201 vp  1. Patch  for HENB, changes for max RBs
                           in cell and avoidance of float variables.
/main/4      kw002.201 vp  1. Patch for optimization,fixes for multi-region
                              and retransmission.
/main/5      kw003.201 vp  1. Fixes for re-segmentation, segement offset
                               value and optimization 
/main/6      kw005.201 ap  1. Moved definition of KW_PJ_ASYNC_WIN from
                              kw_pj_dlm.c file.
                           2. Updated statistics in the code.
                           3. Added support for L2 Measurement.
                       mr  4. Updated prvUr calculation 
                       rd  5. Incorporated the important Avtecs comments.
*********************************************************************91*/

