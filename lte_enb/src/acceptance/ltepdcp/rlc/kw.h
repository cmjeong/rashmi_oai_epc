

/********************************************************************20**
  
        Name:     LTE RLC file 
    
        Type:     C include file
  
        Desc:     This file contain the hash definations for RLC 
 
        File:     kw.h

        Sid:      kw.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:47 2014
  
        Prg:      na 
  
*********************************************************************21*/
/** @file kw.h
@brief RLC Hash definitions
*/

#ifndef __KWH__
#define __KWH__

 
#define KWLAYERNAME   "LTE RLC"     /* Layer Name */

#define EKWxxx 1
#define EMG099 1
#define EMG102 2
#define EMG103 3
#define EMG104 4


 
/************************************************************************
 *                            SAP States
 ************************************************************************/

#define KW_SAP_NOT_CFG        0     /*!< SAP Not Configured */
#define KW_SAP_CFG            1     /*!< SAP Configured but not not bound */
#define KW_SAP_BND            2     /*!< SAP Bound */
#define KW_SAP_BINDING        3     /*!< SAP Bind initiated */
#define KW_SAP_UBND           4     /*!< SAP Unbind */

#define KW_MAX_SAP_BND_RETRY  3     /*!< Maximum SAP Bin Retries */

#define KW_MAX_UE             0xffffffff  /*!< Maximum number of UEs. */
#define KW_MAX_UDXSAPS        1     /*!< Maximum number of UDX Saps */
#define KW_MAX_KWUSAPS        2     /*!< Maximum number of KWU Saps. */
#define KW_MAX_CKWSAPS        1     /*!< Maximum number of CKW Saps. */
#if 0
#define KW_MAX_RGUSAPS        1     /*!< Maximum number of RGU Saps. */
#else
#define KW_MAX_RGUSAPS        2     /*!< Maximum number of RGU Saps. */
#endif

#ifdef KW_PDCP
#define PJ_MAX_CPJSAPS        1     /*!< Maximum number of CPJ Saps. */
#define PJ_MAX_PJUSAPS        2     /*!< Maximum number of PJU Saps. */

#define KW_LMM_GENCFG_DONE    1     /*!< RLC LM general configuration done. */
#define PJ_LMM_GENCFG_DONE    2     /*!< PDCP LM general configuraiton done. */
/* venki - #ifndef KW_PDCP */
#else
#define PJ_MAX_CPJSAPS        1     /*!< Maximum number of CPJ Saps. */
#define PJ_MAX_PJUSAPS        2     /*!< Maximum number of PJU Saps. */

#define KW_LMM_GENCFG_DONE    1     /*!< RLC LM general configuration done. */
#define PJ_LMM_GENCFG_DONE    2     /*!< PDCP LM general configuraiton done. */
#endif /* KW_PDCP */

#define KW_MAX_RGUSAP_TMR     1     /*!< Maximum number of RGU SAP Timers. */

#define KW_TMR_LEN            10    /*!< Timer length. */

/* Maximum number of Saps */

#define KW_UI_RRC             0     /*!< Upper interface RRC sap Id. */
#define KW_UI_PDCP            1     /*!< Upper interface PDCP sap Id. */

#define KW_MAX_SDU_FAIL       10    /*!< Maximum SDUs Failed. */
#define KW_MAX_PDU_MAP        30    /*!< Maximum PDU Map. */

#define KW_ADD_SDU            1     /*!< Add SDU. */
#define KW_DEL_SDU            2     /*!< Delete SDU. */

#define KW_CFM_NOK            0     /*!< Do not send DatCfm */
#define KW_CFM_OK             1     /*!< Send DatCfm */

#define KW_MIN(x,y) (x) < (y) ? (x) : (y)

#define KW_GET_KWCB(_inst) kwCb[_inst];
/* Allocate function */
#define KW_ALLOC(_cb,_buf, _size)                                        \
{                                                                    \
 if (SGetSBuf(_cb->init.region, _cb->init.pool, (Data **)&_buf,      \
                (Size) _size) == ROK)                                \
   {                                                                 \
      cmMemset((U8 *)(_buf), 0, _size);                             \
   }                                                                 \
   else                                                              \
   {                                                                 \
      (_buf) = NULLP;                                               \
   }                                                                 \
}

#define KW_FREE(_cb,_buf, _size)                                         \
{                                                                    \
   if (_buf != NULLP)                                                \
   {                                                                 \
      (Void) SPutSBuf(_cb->init.region, _cb->init.pool,              \
            (Data *) _buf, (Size) _size);                            \
      _buf = NULLP;                                                \
   }                                                                 \
}
/* kw002.201 Freeing from region of pst */
#define KW_PST_FREE(_region, _pool, _buf, _size)          \
{                                                         \
   if (_buf != NULLP)                                     \
   {                                                      \
      (Void) SPutSBuf(_region, _pool,                     \
                      (Data *) _buf, (Size) _size);       \
      _buf = NULLP;                                       \
   }                                                      \
}

#define KW_FREE_BUF(_buf)           \
{                                   \
   if (_buf != NULLP)               \
   {\
      SPutMsg(_buf);                \
   }\
      _buf = NULLP;\
}

#define KW_MEM_CPY(_dst, _src, _size) \
{ \
   cmMemcpy((U8*)_dst, (U8 *)_src, _size); \
}

#define KW_MEM_ZERO(_buf, _size)                        \
{                                                       \
   cmMemset((U8 *)(_buf), 0, _size);                    \
}

#define KW_GET_MEM_REGION(_cb) (_cb->init.region)

#define KW_GET_MEM_POOL(_cb) (_cb->init.pool)

#define KW_GET_MEM_POOL_ADDRESS(_cb) (&_cb->init.pool)

#define KW_SET_KWU_SAP_CB(_cb, _size) \
{ \
   _cb.kwuSap = (KwKwuSapCb *) rlAlloc (_size); \
}

#define KW_RMV_SDU(_cb,_sduQ,_sdu)\
{\
   if(_sdu->mBuf)\
      KW_FREE_BUF(_sdu->mBuf);\
   _sdu->mBuf  = NULLP;\
   cmLListDelFrm(_sduQ,&_sdu->lstEnt);\
   KW_FREE(_cb,_sdu, sizeof(KwSdu));\
}

#define KW_RMV_SDU_LST(_cb,_sduQ,_sdu, _rlsPduLst)\
{\
   cmLListDelFrm(_sduQ,&_sdu->lstEnt);\
   cmLListAdd2Tail(&(rlsPduLst->rlsSduLst), &(_sdu->lstEnt));\
}

#define KW_ADD_PRE_MSG(_pduPtr,_liValue, _liSize)\
{\
   Data liByte;\
   U16  size;\
   size = 0;\
   while (_liSize > size )\
   {\
   liByte = (U8) (_liValue >> (8*size));\
   SAddPreMsg((Data )liByte, _pduPtr);\
   size++;\
   }\
}

#define KW_ADD_PRE_MSG_AM(_pduPtr,_hdr, _liSize)\
{\
   Data liByte;\
   S16  size;\
   size = _liSize - 1;\
   while (size >= 0 )\
   {\
   liByte = (U8) (_hdr[size]);\
   SAddPreMsg((Data )liByte, _pduPtr);\
   size--;\
   }\
}

/* Alarms */
/* Send an alarm for sapId events */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#define KW_SEND_SAPID_ALARM(_cb,_sapId, _evnt, _cause) \
{ \
   kwLmmSendAlarm(_cb,LCM_CATEGORY_INTERFACE, _evnt, _cause, _sapId, 0, 0); \
}
#define KW_SEND_UEID_ALARM(_cb,_ueId, _qci, _evnt, _cause) \
{ \
   kwLmmSendAlarm(_cb,LCM_CATEGORY_INTERFACE, _evnt, _cause, 0, _ueId, _qci); \
}
#else /* LTE_L2_MEAS_RLC */
#define KW_SEND_SAPID_ALARM(_cb,_sapId, _evnt, _cause) \
{ \
   kwLmmSendAlarm(_cb,LCM_CATEGORY_INTERFACE, _evnt, _cause, _sapId, 0); \
}
#define KW_SEND_UEID_ALARM(_cb,_ueId, _evnt, _cause) \
{ \
   kwLmmSendAlarm(_cb,LCM_CATEGORY_INTERFACE, _evnt, _cause, 0, _ueId); \
}
#endif /* LTE_L2_MEAS_RLC */
/* RLC Configuration parameters */
#define KW_MAX_LI                   KW_MAXIMUM_LI
#define KW_MAX_DAT                  KW_MAXIMUM_DAT
#define KW_MAX_PDU                  RGU_MAX_PDU
/* kw001.201: Changed the maximum number of RBs to 10 */
#define KW_MAX_RB_PER_CELL          10
#define KW_MAX_SRB_PER_UE           3
#define KW_MAX_DRB_PER_UE           32
/*ccpu00122594:Changed value from 12 to 10*/
#define KW_MAX_LCH_PER_UE           10
#define KW_MAX_LCH_PER_CELL         6
#define KW_MAX_NUM_RB               24
#define KW_MAX_UE                   0xffffffff 
#define KW_UE_LIST_BUCKET_SIZE      128 
#define KW_CELL_LIST_BUCKET_SIZE    10 
#define KW_TRANS_ID_LST_BKT_SIZE   10 
#define KW_MAX_RB                   32

/* Direction defines */
#define KW_DIR_UL        1     /*!< Unlink direction */
#define KW_DIR_DL        2     /*!< Downlink direction */
#define KW_DIR_BOTH      3     /*!< Both Downlink and Unlink */

/* Memset to value */
#define KW_MEM_SET(_arg, _val, _size) \
{ \
  cmMemset((U8 *)_arg, (U8)_val, _size); \
}

/* Set the unsolictated Status flag */
#define KW_SET_USTA_FLAG(_kwCb, _value) \
{ \
   _kwCb->init.usta = _value; \
}

/* Macros to get the init parameters */
#define KW_GET_DBG_MASK(_kwCb) (_kwCb->init.dbgMask)
#define KW_GET_LMPST_MEM_POOL(_kwCb) (_kwCb->init.lmPst.pool)
#define KW_GET_LMPST_MEM_REGION(_kwCb) (_kwCb->init.lmPst.region)

/* Macros for Checking */
/* Check whether direciton is Downlink or not */
#define KW_VALIDATE_DIR_DL(_dir)                 \
{                                           \
   if (!(_dir & KW_DIR_DL))             \
   {                                        \
      KWLOGERROR(ERRCLS_DEBUG, EKWxxx, (ErrVal) RFAILED,\
            "KwUiCkwCfgReq: Sap Id Validation Failed.");\
      RETVALUE(RFAILED);                    \
   }                                        \
}

/* Check whether direciton is Uplink or not */
#define KW_VALIDATE_DIR_UL(_dir)                 \
{                                           \
   if (!(_dir & KW_DIR_UL))             \
   {                                        \
      KWLOGERROR(ERRCLS_DEBUG, EKWxxx, (ErrVal) RFAILED,\
            "KwUiCkwCfgReq: Sap Id Validation Failed.");\
      RETVALUE(RFAILED);                    \
   }                                        \
}

/* Macros for configuration module */
#define KW_CFG_FILL_CFG_CFM(_entCfm, _rbId, _rbType, _status, _reason)  \
{                                                              \
   _entCfm->rbId  = _rbId;                                     \
   _entCfm->rbType = _rbType;                                  \
   _entCfm->status.status = _status;                           \
   _entCfm->status.reason = _reason;                           \
}

/* Valid Sap State */ 

/* Local RLC Definitions */
#define KW_SDU_ADD      1
#define KW_SDU_REMOVE   0 
#define KW_DEF_SEQ_NUM 0

/* PDU Types */
#define KW_DATA_PDU  1
#define KW_CNTRL_PDU 0

/* UIM defines */
#if (ERRCLASS & ERRCLS_INT_PAR)
#define KW_VALDATE_SAP(_cb,_chkSpId, _sap, _ret)                         \
{                                                                    \
   if (_chkSpId != _sap->spId)                                       \
   {                                                                 \
      KWLOGERROR(_cb,ERRCLS_DEBUG, EKWxxx, (ErrVal) RFAILED,             \
            "Sap Id Validation Failed.");                            \
      _ret = RFAILED;                                                \
   }                                                                 \
   /* SAP state validation */                                        \
   if(_sap->state != KW_SAP_BND)                                     \
   {                                                                 \
      KWLOGERROR(_cb,ERRCLS_INT_PAR, EKWXXX, (ErrVal) RFAILED,           \
            "Sap State Invalid.");                                   \
      KW_SEND_SAPID_ALARM(_cb,0, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_STATE); \
      _ret = RFAILED;                                                \
   }                                                                 \
}
#else /* ERRCLASS & ERRCLS_INT_PAR */
#define KW_VALDATE_SAP(_cb,_chkSpId, _sap, _ret)                         \
{                                                                    \
   /* SAP state validation */                                        \
   if(_sap->state != KW_SAP_BND)                                     \
   {                                                                 \
      KWLOGERROR(_cb,ERRCLS_INT_PAR, EKWXXX, (ErrVal) RFAILED,           \
            "Sap State Invalid.");                                   \
      KW_SEND_SAPID_ALARM(_cb,0, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_STATE); \
      _ret = RFAILED;                                                \
   }                                                                 \
}
#endif /* ERRCLASS & ERRCLS_INT_PAR */

#define KW_VALIDATE_LCHID(_LChId)                               \
{                                                               \
   if (_LChId <= 0)                                             \
   {                                                            \
      /* Fill entCfm structure */                               \
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_INVALID_LCHID);                        \
                                                                \
      RETVALUE(RFAILED);                                        \
   }                                                            \
}

#define KW_FI_FIRST_SEG                0x02
#define KW_FI_LAST_SEG                 0x01

/* TMR module defines */
#define KW_TMR_LEN                     10
#define KW_MAX_UM_TMR                  1
#define KW_MAX_AM_TMR                  3
#define KW_EVT_UMUL_REORD_TMR          1
#define KW_EVT_AMUL_REORD_TMR          2
#define KW_EVT_AMUL_STA_PROH_TMR       3
#define KW_EVT_AMDL_POLL_RETX_TMR      4
#define KW_EVT_WAIT_BNDCFM             5
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#define KW_EVT_L2_TMR                  6
#endif /* LTE_L2_MEAS_RLC */

/* kw006.201, optmization change ccpu00111716 */
#ifdef KW_BG_DL_PROC
#define EVTKWSELFMSGDL                 1
#endif /* KW_BG_DL_PROC */
/* kw006.201, optmization change ccpu00117290 */
#ifdef KW_BG_UL_PROC
#define EVTKWSELFMSGUL                 2
#endif /* KW_BG_UL_PROC */

/* UMM defines */
#define UMDL                           rbCb->m.umDl 
#define UMUL                           rbCb->m.umUl 

/* Sequence Number defines */
#define KW_UM_CFG_SN_5           5
#define KW_UM_CFG_SN_10          10

#define KW_UM_SN_5               1
#define KW_UM_SN_10              2

#define  KW_RMV_MAC_HDR_SZ(pduSz) \
{\
   if (pduSz > 127)\
      pduSz -= 3;\
   else\
      pduSz -= 2;\
}

#define  KW_RMV_RLC_HDR_SZ(pduSz,snLen)\
{\
   if ( snLen == 1 ) \
      pduSz -= 1;\
   else if ( snLen == 2 )\
      pduSz -= 2; \
}

#define KW_CREATE_UM_PDU(_rbCb,_pdu,_fi,_pduInfo,_ret)\
{\
   MsgLen bytesSent = 0;\
   _ret = kwUmmCreatePdu(_rbCb,&(_pdu),_fi);\
   if (_ret == ROK )\
   {\
      SFndLenMsg(pdu, &bytesSent);\
      _pduInfo->mBuf[(_pduInfo->numPdu)++] = _pdu;\
      kwCb.genSts.bytesSent += bytesSent;\
      _pdu = NULLP;\
   }\
}


#define KW_UM_CHK_DUP_PDU(_rbCb,_curSn,_ret)\
{\
   KwSn winSz = _rbCb->m.umUl.umWinSz << 1; \
   KwSn _umReOrdWinSz = _rbCb->m.umUl.umWinSz;\
   KwSn _vrUh = _rbCb->m.umUl.vrUh;\
   KwSn _vrUr = _rbCb->m.umUl.vrUr;\
   KwSn ur    =   KW_UM_GET_VALUE(_vrUr,_vrUh,_umReOrdWinSz,winSz);\
   KwSn uh    =   KW_UM_GET_VALUE(_vrUh,_vrUh,_umReOrdWinSz,winSz);\
   KwSn sn      = KW_UM_GET_VALUE(_curSn,_vrUh,_umReOrdWinSz,winSz);\
   if ( ((ur < sn) && (sn < uh) && \
         (_rbCb->m.umUl.recBuf[_curSn] != NULLP)) || \
         (sn < ur)) \
   {\
       _ret = TRUE;\
   }\
   else\
   {\
      _ret = FALSE;\
   }\
}


#define KW_UM_GET_VALUE(_val,_uh,_umReOrdWinSz,_umWinSz)  ((_val-(_uh - \
            (_umReOrdWinSz)) + _umWinSz) % (_umWinSz))

#define KW_CHK_SN_IN_REORD_WIN(_curSn,_rbCb,_ret)  \
{\
   KwSn _umWinSz      = _rbCb->m.umUl.umWinSz << 1;\
   KwSn _vrUh         = _rbCb->m.umUl.vrUh;\
   KwSn _umReOrdWinSz = _rbCb->m.umUl.umWinSz;\
   if ((KW_UM_GET_VALUE(_curSn,_vrUh,_umReOrdWinSz,_umWinSz) < \
            KW_UM_GET_VALUE (_vrUh,_vrUh,_umReOrdWinSz,_umWinSz))) \
   {\
      _ret = TRUE;\
   }\
   else\
   {\
      _ret = FALSE;\
   }\
}
#define KW_UM_FIND_NEXT_VRUR(_umUl,_prevVrUr,_vrUr)\
{\
   KwUmRecBuf **umRecBuf = _umUl->recBuf;\
   KwSn _umWinSz      = _umUl->umWinSz << 1;\
   KwSn _vrUh         = _umUl->vrUh;\
   KwSn _umReOrdWinSz = _umUl->umWinSz;\
   KwSn ur = KW_UM_GET_VALUE(_vrUr,_vrUh,_umReOrdWinSz,_umWinSz);\
   KwSn prvUr = KW_UM_GET_VALUE(_prevVrUr,_vrUh,_umReOrdWinSz,_umWinSz);\
   while (ur < prvUr )\
   {\
      if ( umRecBuf[_prevVrUr] == NULLP )\
      {\
         _vrUr = _prevVrUr;\
         break;\
      }\
      _prevVrUr = (_prevVrUr + 1) % _umWinSz;\
      prvUr = KW_UM_GET_VALUE(_prevVrUr,_vrUh,_umReOrdWinSz,_umWinSz);\
   }\
}


#define KW_UM_CHK_REORD_TMR(_rbCb) TRUE 

/* AMM defines */
#define AMDL                           rbCb->m.amDl 
#define AMUL                           rbCb->m.amUl

#define KW_POLL_SET                    0x20 /* 00100000 */
#define KW_POLL_UNSET                  0xdf /* 11011111 */
#define KW_AM_WIN_SZ                   512
#define KW_MAX_CNTRL_FIELDS            100
#define KW_MAX_HDRSZ                   100
#define KW_AM_PDU_FIXED_HDRSZ          2
#define KW_AM_SEG_FIXED_HDRSZ          4
#define KW_EXTN_HDRSZ                  2
#define KW_CNTRL_PDU_FIXED_HDRSZ       2
#define KW_MAC_HDR_SZ2                 2
#define KW_MAC_HDR_SZ3                 3
#define KW_BYTE_LEN                    8
#define KW_2BYTE_LEN                   16
#define KW_E1_LEN                      1
#define KW_NACK_E1E2_LEN               12
#define KW_SO_LEN                      15
/*ccpu00121123: status pdu creation logic correction*/
#define KW_SEGNACK_E1E2_SO_LEN         (KW_NACK_E1E2_LEN + KW_SO_LEN + KW_SO_LEN)
#define KW_DC_LEN                      1
#define KW_CPT_LEN                     3
#define KW_RF_LEN                      1
#define KW_P_LEN                       1
#define KW_FI_LEN                      2
#define KW_E_LEN                       1
#define KW_SN_LEN                      10
#define KW_LSF_LEN                     1
#define KW_LI_LEN                      11

#define KW_DC_POS                      0x80
#define KW_RF_POS                      0x40
#define KW_POLL_POS                    0x20
#define KW_FI_POS                      0x18
#define KW_E_POS                       0x04
#define KW_SN_POS                      0x03

#define KW_SDU_LST                     1
#define KW_SEG_LST                     2
#define KW_RETX_LST                    3
#define KW_ALL_BYTES_MISSING           0x7ff

#define KW_LLIST_FIRST_SDU(lstCp, nod)                     \
{                                                          \
   CmLList *tmpNode;                                       \
   CM_LLIST_FIRST_NODE(&(lstCp), tmpNode);                 \
   if (tmpNode != NULLP)                                   \
      nod = (KwSdu *)tmpNode->node;                        \
   else                                                    \
      nod = NULLP;                                         \
}                                                          
                                                           
#define KW_LLIST_FIRST_SEG(lstCp, nod)                     \
{                                                          \
   CmLList *tmpNode;                                       \
   CM_LLIST_FIRST_NODE(&(lstCp), tmpNode);                 \
   if (tmpNode != NULLP)                                   \
      nod = (KwSeg *)tmpNode->node;                        \
   else                                                    \
      nod = NULLP;                                         \
}                                                          
                                                           
#define KW_LLIST_FIRST_RETX(lstCp, nod)                    \
{                                                          \
   CmLList *tmpNode;                                       \
   CM_LLIST_FIRST_NODE(&(lstCp), tmpNode);                 \
   if (tmpNode != NULLP)                                   \
      nod = (KwRetx *)tmpNode->node;                       \
   else                                                    \
      nod = NULLP;                                         \
}

#define KW_LLIST_NEXT_SDU(lstCp, nod)                      \
{                                                          \
   CmLList *tmpNode;                                       \
   CM_LLIST_NEXT_NODE(&(lstCp), tmpNode);                  \
   if (tmpNode != NULLP)                                   \
      nod = (KwSdu *)tmpNode->node;                        \
   else                                                    \
      nod = NULLP;                                         \
}                                                          
                                                           
#define KW_LLIST_NEXT_SEG(lstCp, nod)                      \
{                                                          \
   CmLList *tmpNode;                                       \
   (lstCp).crnt = &((nod)->lstEnt);                        \
   CM_LLIST_NEXT_NODE(&(lstCp), tmpNode);                  \
   if (tmpNode != NULLP)                                   \
      nod = (KwSeg *)tmpNode->node;                        \
   else                                                    \
      nod = NULLP;                                         \
}                                                          
                                                           
#define KW_LLIST_NEXT_RETX(lstCp, nod)                     \
{                                                          \
   CmLList *tmpNode;                                       \
   CM_LLIST_NEXT_NODE(&(lstCp), tmpNode);                  \
   if (tmpNode != NULLP)                                   \
      nod = (KwRetx *)tmpNode->node;                       \
   else                                                    \
      nod = NULLP;                                         \
}

#define KW_LLIST_LAST_RETX(lstCp, nod)                      \
{                                                          \
   CmLList *tempNode = NULLP;                              \
   cmLListLast(&lstCp);                                    \
   tempNode = cmLListCrnt(&lstCp);                         \
   if (tempNode != NULLP)                                  \
      nod = (KwRetx *)tempNode->node;                      \
   else                                                    \
      nod = NULLP;                                         \
}

#define KW_LLIST_LAST_SEG(lstCp, nod)                      \
{                                                          \
   CmLList *tempNode = NULLP;                              \
   cmLListLast(&lstCp);                                    \
   tempNode = cmLListCrnt(&lstCp);                         \
   if (tempNode != NULLP)                                  \
      nod = (KwSeg *)tempNode->node;                       \
   else                                                    \
      nod = NULLP;                                         \
}

#define KW_LLIST_LAST_SDU(lstCp, nod)                      \
{                                                          \
   CmLList *tempNode = NULLP;                              \
   cmLListLast(&lstCp);                                    \
   tempNode = cmLListCrnt(&lstCp);                         \
   if (tempNode != NULLP)                                  \
      nod = (KwSdu *)tempNode->node;                       \
   else                                                    \
      nod = NULLP;                                         \
}

#define CM_LLIST_INS_AFT_CRNT(lstCp, nod)                  \
{                                                          \
   CmLList *nodeToIns = &nod->lstEnt;\
   nodeToIns->node = (PTR) nod;\
   cmLListInsAfterCrnt(&lstCp, nodeToIns);                 \
}

#define CM_LLIST_INS_BEF_CRNT(lstCp, nod)                  \
{                                                          \
   CmLList *nodeToIns = &nod->lstEnt;                      \
   nodeToIns->node = (PTR) nod;                            \
   cmLListInsCrnt(&lstCp, nodeToIns);                      \
}

#define KW_LLIST_DEL_RECBUF(_recBuf)                       \
{                                                          \
   KwSeg  *_seg = NULLP;                                   \
   KW_LLIST_FIRST_SEG(_recBuf->segLst, _seg);              \
   while (_seg)                                            \
   {                                                       \
      cmLListDelFrm(&_recBuf->segLst, &_seg->lstEnt);      \
      KW_FREE(_seg, sizeof(KwSeg));                        \
      KW_LLIST_NEXT_SEG(_recBuf->segLst, _seg);            \
   }                                                       \
}


#define MODAMT(x, y, z)                                    \
{                                                          \
   y = ((x - z) + 1024) % 1024;                            \
}                                                         

#define MODAMR(x, y, z)                                    \
{                                                          \
   y = ((x - z) + 1024) % 1024;                            \
}

/* Accumulate bo */
#define KW_UPD_AMBO(_amDl, _bo)                            \
{                                                          \
   Bool winStall = FALSE;                                  \
   KwAmDl  *tamDl  = NULLP;                                \
   tamDl = &_amDl;                                         \
                                                           \
   if (_amDl.bo < 0) _amDl.bo = 0;                         \
   if (_amDl.cntrlBo < 0) _amDl.cntrlBo = 0;               \
   if (_amDl.retxBo < 0) _amDl.retxBo = 0;                 \
   KW_AM_CHK_WINDOW_STALL(tamDl->vtS, tamDl, winStall);    \
   if (!winStall)                                          \
   {                                                       \
      _bo = _amDl.bo + _amDl.cntrlBo + _amDl.retxBo;       \
   }                                                       \
   else                                                    \
   {                                                       \
      _bo = _amDl.cntrlBo + _amDl.retxBo;                  \
   }                                                       \
} 

#define KW_FILL_CNTRL_INFO(cntrlInfo, _val, _len, _idx, _eb)\
{                                                           \
   cntrlInfo.val = _val;                                    \
   cntrlInfo.len = _len;                                    \
   cntrlInfo.idx = _idx;                                    \
   cntrlInfo.emtBits = _eb;                                 \
}
#define KW_FILL_PREV_IDX(cntrlInfo, _e1Idx, _e2Idx, _e1eb, _idx, _eb)\
{\
  _e1Idx = cntrlInfo.e1Idx;\
  _e2Idx = cntrlInfo.e2Idx;\
  _e1eb  = cntrlInfo.e1eb;\
  _idx   = cntrlInfo.idx;\
  _eb    = cntrlInfo.emtBits;\
}

#define KW_FILL_HDR_ARGS(hdrInfo, _val, _len)\
{\
   hdrInfo.val = _val;\
   hdrInfo.len = _len;\
}

#define KW_COPY_STAPDU(_i, _j)                             \
{                                                          \
  U16 tmpPdu;                                              \
  tmpPdu = staPdu[_i];                                     \
  cntrlPdu[_j++] = (U8)(tmpPdu >> KW_BYTE_LEN);            \
  cntrlPdu[_j++] = (U8)staPdu[_i];                             \
}

/* kw003.201 - This macro provides the header size other than the */
/*             fixed header of 2 bytes for each AMD PDU or 4 bytes*/
/*             for an AM PDU segment                              */
#define KW_AM_EXTN_HDRSZ(_numLi, _eHdrSz)                  \
{                                                          \
   if ((_numLi - 1) % 2)\
   {\
      _eHdrSz = ((3 * (_numLi - 2)) >> 1) + 2;\
   }\
   else\
   {\
      _eHdrSz = (3 * (_numLi - 1)) >> 1;\
   }\
}

#define KW_DBG_SUB_MASK   DBGMASK_MI               /* Use for sub-mask */
#define KW_DBGMASK_DETAIL (KW_DBG_SUB_MASK << 0)   /* Parameters, It will give
                                                      in depth info */
#define KW_DBGMASK_BRIEF  (KW_DBG_SUB_MASK << 1)   /* Info, It will give info at
                                                      entry and exit places along
                                                      with certain state changes */
#define KW_DBGMASK_ERROR  (KW_DBG_SUB_MASK << 2)   /* Error information */
#define KW_DBGMASK_FATAL  (KW_DBG_SUB_MASK << 3)   /* FATAL errors like memory
                                                      resource failure etc., */

#define KW_DBG_MDL_MASK (KW_DBG_SUB_MASK << 4)

#define KW_DBGMASK_TM             (KW_DBG_MDL_MASK << 0)    /* TM */
#define KW_DBGMASK_UM             (KW_DBG_MDL_MASK << 1)    /* UM */
#define KW_DBGMASK_AM             (KW_DBG_MDL_MASK << 2)    /* AM */
#define KW_DBGMASK_DL             (KW_DBG_MDL_MASK << 3)    /* DL */
#define KW_DBGMASK_UL             (KW_DBG_MDL_MASK << 4)    /* UL */
#define KW_DBGMASK_CFG            (KW_DBG_MDL_MASK << 5)    /* CFG */
#define KW_DBGMASK_LMM            (KW_DBG_MDL_MASK << 6)    /* LMM */
#define KW_DBGMASK_INF            (KW_DBG_MDL_MASK << 7)    /* UI, LI */
#define KW_DBGMASK_DUT            (KW_DBG_MDL_MASK << 8)    /* DBM, UTL, TMR */
#define KW_DBGMASK_MBUF_PRNT      (KW_DBG_MDL_MASK << 9)    /* MBUF, useful in
                                                               integrated testing */
#define KW_DBGMASK_MEM_INFO       (KW_DBG_MDL_MASK << 10)   /* Memory Info useful
                                                               in integrated testing */
#define KW_PJ_DBG_MDL_MASK (KW_DBG_MDL_MASK << 11)

#define KW_PJ_DBGMASK_DLM         (KW_PJ_DBG_MDL_MASK << 0) /* DL */
#define KW_PJ_DBGMASK_ULM         (KW_PJ_DBG_MDL_MASK << 1) /* UL */
#define KW_PJ_DBGMASK_UTL         (KW_PJ_DBG_MDL_MASK << 2) /* DBM, UTL, TMR */
#define KW_PJ_DBGMASK_CFG         (KW_PJ_DBG_MDL_MASK << 3) /* LMM and CFG */
#define KW_PJ_DBGMASK_LIB         (KW_PJ_DBG_MDL_MASK << 4) /* LIB - means software
                                                               or offboard hooks */
#define KW_PJ_DBGMASK_INF         (KW_PJ_DBG_MDL_MASK << 5)
#define KW_PJ_DBGMASK_LMM         (KW_PJ_DBG_MDL_MASK << 6)

#ifdef DEBUGP
#define KW_PRNT_BORDER                                              \
do                                                                  \
{                                                                   \
   KW_PRNT((_kwPBuf, "\n==========================\n"));            \
}while(0)

#define KW_PRNT_HLINE(_cb,_pMsg)                                 \
{                                                                   \
   sprintf((_cb)->init.prntBuf, "[RLC_LAYER: %s:%d]::", __FILE__, __LINE__);  \
   SPrint((_cb)->init.prntBuf);                     \
   KW_PRNT_TSTAMP(_cb);                                                  \
   sprintf((_cb)->init.prntBuf, _pMsg);                                \
   SPrint((_cb)->init.prntBuf);                                        \
}


#define KW_PRNT(_cb,_prntbuf)      \
{                              \
   sprintf _prntbuf;           \
   SPrint(_cb->init.prntBuf);            \
}


#define KW_PRNT_TSTAMP(_cb)                      \
{                                           \
   S8 _buf[60];                            \
   DateTime dt;                             \
   cmMemset((U8 *)(&dt), 0, sizeof(DateTime));\
   SGetDateTime(&dt);                       \
   sprintf(_buf, "date: %02d/%02d/%04d time: %02d:%02d:%02d", \
     (int)dt.month,(int)dt.day,(int)dt.year + 1900, \
     (int)dt.hour,(int)dt.min,(int)dt.sec);  \
   KW_PRNT(_cb,(_cb->init.prntBuf,("[%s]", _buf)));       \
}

#define KW_PRNT_MBUF(_cb,_mBufPtr)                              \
do                                                          \
{                                                           \
   if(_cb->init.dbgMask & (KW_DBGMASK_MBUF_PRNT))           \
   {                                                        \
     KW_PRNT_HLINE(_cb,("\nMessage Buffer Contents:\n"));       \
     SPrntMsg ((Buffer *)_mBufPtr, 0, 0);                   \
   }                                                        \
}while(0)

#define KW_PRNT_MEMINFO(_cb)                                       \
do                                                            \
{                                                             \
   U32  _memInfo;                                             \
   if(_cb->init.dbgMask & (KW_DBGMASK_MEM_INFO))              \
   {                                                          \
     KW_PRNT_HLINE(_cb,("\nMemory Information:\n"));              \
     SRegInfoShow(0, &_memInfo);                              \
   }                                                          \
}while(0)

#define KWDBGP(_cb,_mask,_arg)                                   \
do                                                            \
{                                                             \
   if (!((_cb->init.dbgMask & _mask) ^ _mask))                \
   {                                                          \
      KW_PRNT(_cb, _arg);                                          \
   }                                                          \
}while(0)

/*ccpu00120364: Fix provided by removing extra formatting*/
#define KWDBGP(_mask, _arg)                                   \
   DBGP(&kwCb.init, KWLAYERNAME, _mask, _arg)

#else  /* DEBUGP */ 
#define KW_PRNT_HLINE(_cb,_pMsg)
#define KW_PRNT(_cb,_prntbuf)
#define KW_PRNT_TSTAMP(_cb)
#define KW_PRNT_MBUF(_cb,_mBufPtr)
#define KW_PRNT_MEMINFO(_cb)
#define KWDBGP(_cb,_mask, _arg)
#endif /* DEBUGP */

#ifdef KW_PDCP 
#define PJLAYERNAME   "LTE PDCP"     /* Layer Name */

#ifdef DEBUGP
/*ccpu00120364: Fix for debug logs*/
#define _pjPBuf   kwCb.pjInit.prntBuf

/*ccpu00120364: Fix provided by removing extra formatting*/
#define PJDBGP(_mask, _arg)                                   \
   DBGP(&kwCb.pjInit, PJLAYERNAME, _mask, _arg)

#else /* DEBUGP */
#define PJDBGP(_mask, _arg)
#endif /* DEBUGP */

#define PJ_SEND_SAPID_ALARM   KW_SEND_SAPID_ALARM
#define PJ_SEND_UEID_ALARM    KW_SEND_UEID_ALARM 
/* ################################################################ */
/* Venki - #ifndef */
#else
#if 0
#define PJLAYERNAME   "LTE PDCP"     /* Layer Name */

#ifdef DEBUGP
/*ccpu00120364: Fix for debug logs*/
#define _pjPBuf   kwCb.pjInit.prntBuf

/*ccpu00120364: Fix provided by removing extra formatting*/
#define PJDBGP(_mask, _arg)                                   \
   DBGP(&kwCb.pjInit, PJLAYERNAME, _mask, _arg)

#else /* DEBUGP */
#define PJDBGP(_mask, _arg)
#endif /* DEBUGP */

#define PJ_SEND_SAPID_ALARM   KW_SEND_SAPID_ALARM
#define PJ_SEND_UEID_ALARM    KW_SEND_UEID_ALARM
#endif
#endif /* KW_PDCP */

/* Update poll bit in the buffer */
#define KW_UPD_POLL_BIT(_retx, _poll)                      \
{                                                          \
   U8 fHdr = 0x00;                                         \
                                                           \
   if (_poll != _retx->amHdr.p)                            \
   {                                                       \
      /* Get the first byte of the buffer */               \
      SRemPreMsg ((Data *)&fHdr, _retx->seg);              \
      if (_poll == TRUE)                                   \
      {                                                    \
         fHdr = fHdr | KW_POLL_SET;                        \
      }                                                    \
      else                                                 \
      {                                                    \
         fHdr = fHdr & KW_POLL_UNSET;                      \
      }                                                    \
      /* Concatenated updated hdr to the mBuf */           \
      SAddPreMsg ((Data)fHdr, _retx->seg);                 \
   }                                                       \
   /* Update poll bit in the hdrInfo */                    \
   _retx->amHdr.p = _poll;                                 \
}

#define KW_AM_ELIMINATE_EXTN_HDR(_pduSz, _sduSz, _numLi)   \
{                                                          \
   if ( (_pduSz > _sduSz) && (_sduSz < 2048) )             \
   {                                                       \
      _pduSz -= (_numLi % 2) ? 1 : 2;                      \
   }                                                       \
}

/* Check if SN falls within reordering window */
#define KW_AM_CHK_SN_IN_WINDOW(sn, amUl, snInWin)          \
{                                                          \
   if (amUl->vrR > amUl->vrMr)                             \
   {                                                       \
      if ((sn >= amUl->vrR) || (sn < amUl->vrMr))          \
      {                                                    \
         snInWin = TRUE;                                   \
      }                                                    \
   }                                                       \
   else                                                    \
   {                                                       \
      if ((sn >= amUl->vrR) && (sn < amUl->vrMr))          \
      {                                                    \
         snInWin = TRUE;                                   \
      }                                                    \
   }                                                       \
}

/* Check conditions for window stalling */
#define KW_AM_CHK_WINDOW_STALL(_sn, _amDl, _winStall)      \
{                                                          \
   KwSn   _mSn    = 0;                                     \
   KwSn   _vtA    = 0;                                     \
   KwSn   _vtMs   = 0;                                     \
   _winStall      = FALSE;                                 \
                                                           \
   MODAMT(_amDl->vtA, _vtA, _amDl->vtA);                   \
   MODAMT(_sn, _mSn, _amDl->vtA);                          \
   MODAMT(_amDl->vtMs, _vtMs, _amDl->vtA);                 \
                                                           \
   if (! ((_vtA <= _mSn) && (_mSn < _vtMs)) )              \
   {                                                       \
      _winStall = TRUE;                                    \
   }                                                       \
}
/*
#define KW_CHK_FOR_POLLSN(_rbCb, _mAckSn)                            \
{                                                                    \
   KwSn _mSn   = 0;                                                  \
   KwSn _mVtA  = 0;                                                  \
                                                                     \
   MODAMT(_rbCb->m.am.amDl.pollSn, mSn, _rbCb->m.am.amDl.vtA);       \
   MODAMT(_rbCb->m.am.amDl.vtA, mVtA, _rbCb->m.am.amDl.vtA);         \
                                                                     \
   if ( (_mSn >= _mVtA) && (_mSn <= _mAckSn) )                       \
   {                                                                 \
      Bool _tmrRunning = FALSE;                                      \
      _tmrRunning = kwChkTmr((PTR)_rbCb, KW_EVT_AMDL_POLL_RETX_TMR); \
                                                                     \
      if (_tmrRunning)                                               \
      {                                                              \
         kwStopTmr((PTR)_rbCb, KW_EVT_AMDL_POLL_RETX_TMR);           \
      }                                                              \
   }                                                                 \
}                                                                    \
*/
/* Venki - changing for stopping poll retx timer */
#define KW_CHK_FOR_POLLSN(_cb, _rbCb, _mAckSn)                            \
{                                                                    \
   KwSn _mSn   = 0;                                                  \
   KwSn _mVtA  = 0;                                                  \
                                                                     \
   MODAMT(_rbCb->m.amDl.pollSn, mSn, _rbCb->m.amDl.vtA);       \
   MODAMT(_rbCb->m.amDl.vtA, mVtA, _rbCb->m.amDl.vtA);         \
                                                                     \
   if ( (_mSn >= _mVtA) && (_mSn <= _mAckSn) )                       \
   {                                                                 \
      Bool _tmrRunning = FALSE;                                      \
      _tmrRunning = kwChkTmr(_cb, (PTR)_rbCb, KW_EVT_AMDL_POLL_RETX_TMR); \
                                                                     \
      if (_tmrRunning)                                               \
      {                                                              \
         kwStopTmr(_cb,(PTR)_rbCb, KW_EVT_AMDL_POLL_RETX_TMR);           \
      }                                                              \
   }                                                                 \
}                                                                    \

#define KW_POWER(x, y)  x << (y-1); 

/* DBM Module Macros */
#define KW_DBM_FETCH_RBCB(_rbId, _rbType, _ueCb, _rbCb)     \
{                                                           \
   RbCb  **_rbCbLst;                                         \
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

#define KW_DBM_FETCH_CELL_RBCB(_rbId, _rbCbLst, _rbCb)      \
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

#if (ERRCLASS & ERRCLS_DEBUG)
#ifdef DEBUGP
#define KW_DBM_CREATE_RBCB(_rbId, _rbType, _ueCb, _rbCb)    \
{                                                           \
   RbCb   **_rbCbLst;                                        \
   /* Allocate memory for rbCb */                           \
   KW_ALLOC(_rbCb, sizeof(RbCb));                           \
                                                            \
   if ( rbCb == NULLP)                                      \
   {                                                        \
      /* Fill entCfm structure */                           \
      KW_CFG_FILL_CFG_CFM(entCfm, _rbId, _rbType,CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_CREAT_FAIL);                    \
                                                            \
      KWDBGP((KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (_kwPBuf, \
               "kwCfgAddRb -- kwDbmCreateRbCb Failed, rbId(%d)\n", rbId));\
      RETVALUE(RFAILED);                                    \
   }                                                        \
      /* Assign rbId */                                     \
   _rbCb->kwRbCb.rlcId.rbId = _rbId;                        \
   _rbCbLst = (_rbType==CM_LTE_SRB)?_ueCb->srbCb:_ueCb->drbCb;\
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
   /* kw005.201 ccpu00117318, updating the statistics */   \
   KW_LMM_RB_STS_INC()                                    \
}
#define KW_DBM_CREATE_CELL_RBCB(_rbId, _rbCbLst, _rbCb)     \
{                                                           \
   /* Allocate memory for rbCb */                           \
   KW_ALLOC(_rbCb, sizeof(RbCb));                           \
                                                            \
   if ( rbCb == NULLP)                                      \
   {                                                        \
      /* Fill entCfm structure */                           \
      KW_CFG_FILL_CFG_CFM(entCfm, _rbId, CM_LTE_SRB, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_CREAT_FAIL);                    \
                                                            \
      KWDBGP((KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (_kwPBuf, \
               "kwCfgAddRb -- kwDbmCreateRbCb Failed, rbId(%d)\n", rbId));\
      RETVALUE(RFAILED);                                    \
   }                                                        \
      /* Assign rbId */                                     \
   _rbCb->kwRbCb.rlcId.rbId = _rbId;                        \
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
   /* kw005.201 ccpu00117318, updating the statistics */   \
   KW_LMM_RB_STS_INC()                                    \
}
#else /* DEBUGP */
#define KW_DBM_CREATE_RBCB(_rbId, _rbType, _ueCb, _rbCb)    \
{                                                           \
   RbCb **_rbCbLst;                                          \
   /* Allocate memory for rbCb */                           \
   KW_ALLOC(_rbCb, sizeof(RbCb));                           \
                                                            \
   if ( rbCb == NULLP)                                      \
   {                                                        \
      /* Fill entCfm structure */                           \
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, _rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_CREAT_FAIL);                    \
                                                            \
      RETVALUE(RFAILED);                                    \
   }                                                        \
      /* Assign rbId */                                     \
   _rbCb->kwRbCb.rlcId.rbId = _rbId;                        \
   _rbCbLst = (_rbType==CM_LTE_SRB)?_ueCb->srbCb:_ueCb->drbCb;\
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
   /* kw005.201 ccpu00117318, updating the statistics */   \
   KW_LMM_RB_STS_INC()                                    \
}
#define KW_DBM_CREATE_CELL_RBCB(_rbId, _rbCbLst, _rbCb)     \
{                                                           \
   /* Allocate memory for rbCb */                           \
   KW_ALLOC(_rbCb, sizeof(RbCb));                           \
                                                            \
   if ( rbCb == NULLP)                                      \
   {                                                        \
      /* Fill entCfm structure */                           \
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, CM_LTE_SRB,CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_CREAT_FAIL);                    \
                                                            \
      RETVALUE(RFAILED);                                    \
   }                                                        \
      /* Assign rbId */                                     \
   _rbCb->kwRbCb.rlcId.rbId = _rbId;                        \
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
   /* kw005.201 ccpu00117318, updating the statistics */   \
   KW_LMM_RB_STS_INC()                                    \
}
#endif /* DEBUGP */
#else /* ERRCLASS & ERRCLS_DEBUG */
#ifdef DEBUGP
#define KW_DBM_CREATE_RBCB(_rbId, _rbType, _ueCb, _rbCb)    \
{                                                           \
   RbCb  **_rbCbLst;                                         \
   /* Allocate memory for rbCb */                           \
   KW_ALLOC(_rbCb, sizeof(RbCb));                           \
                                                            \
   if ( rbCb == NULLP)                                      \
   {                                                        \
      /* Fill entCfm structure */                           \
      KW_CFG_FILL_CFG_CFM(entCfm, _rbId, _rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_CREAT_FAIL);                    \
                                                            \
      KWDBGP((KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (_kwPBuf, \
               "kwCfgAddRb -- kwDbmCreateRbCb Failed, rbId(%d)\n", rbId));\
      RETVALUE(RFAILED);                                    \
   }                                                        \
      /* Assign rbId */                                     \
   _rbCb->kwRbCb.rlcId.rbId = _rbId;                        \
   _rbCbLst = (_rbType==CM_LTE_SRB)?_ueCb->srbCb:_ueCb->drbCb;\
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
   /* kw005.201 ccpu00117318, updating the statistics */   \
   KW_LMM_RB_STS_INC()                                    \
}
#define KW_DBM_CREATE_CELL_RBCB(_rbId, _rbCbLst, _rbCb)     \
{                                                           \
   /* Allocate memory for rbCb */                           \
   KW_ALLOC(_rbCb, sizeof(RbCb));                           \
                                                            \
   if ( rbCb == NULLP)                                      \
   {                                                        \
      /* Fill entCfm structure */                           \
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, CM_LTE_SRB, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_CREAT_FAIL);                    \
                                                            \
      KWDBGP((KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (_kwPBuf, \
               "kwCfgAddRb -- kwDbmCreateRbCb Failed, rbId(%d)\n", rbId));\
      RETVALUE(RFAILED);                                    \
   }                                                        \
      /* Assign rbId */                                     \
   _rbCb->kwRbCb.rlcId.rbId = _rbId;                        \
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
   /* kw005.201 ccpu00117318, updating the statistics */   \
   KW_LMM_RB_STS_INC()                                    \
}
#else /* DEBUGP */
#define KW_DBM_CREATE_RBCB(_rbId, _rbType, _ueCb, _rbCb)    \
{                                                           \
   RbCb **_rbCbLst;                                          \
   /* Allocate memory for rbCb */                           \
   KW_ALLOC(_rbCb, sizeof(RbCb));                           \
                                                            \
   /* Assign rbId */                                        \
   _rbCb->kwRbCb.rlcId.rbId = _rbId;                        \
   _rbCbLst = (_rbType==CM_LTE_SRB)?_ueCb->srbCb:_ueCb->drbCb;\
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
   /* kw005.201 ccpu00117318, updating the statistics */   \
   KW_LMM_RB_STS_INC()                                    \
}
#define KW_DBM_CREATE_CELL_RBCB(_rbId, _rbCbLst, _rbCb)     \
{                                                           \
   /* Allocate memory for rbCb */                           \
   KW_ALLOC(_rbCb, sizeof(RbCb));                           \
                                                            \
   /* Assign rbId */                                        \
   _rbCb->kwRbCb.rlcId.rbId = _rbId;                        \
                                                            \
   /* Assign rbCb to proper index in rbCbLst */             \
   _rbCbLst[_rbId] = (_rbCb);                               \
   /* kw005.201 ccpu00117318, updating the statistics */   \
   KW_LMM_RB_STS_INC()                                    \
}
#endif /* DEBUGP */
#endif /* ERRCLASS & ERRCLS_DEBUG */

/*Optimization change for ccpu00111716, ccpu00117290*/
#if ((defined KW_BG_DL_PROC) || (defined KW_BG_UL_PROC))
/*If bit 2 and bit 3 of rbOp flag is 00, then it means that delete RB request*
 *was received and the deletion of DL/UL PDUs are either complete or there   *
 *was nothing to be deleted. So, now the RbCb can be freed. Otherwise, only  *
 *rbCb pointer is assigned NULL and freeing will be done in kwUtlRbDeletion. */
#define KW_DBM_DELETE_RBCB(_rbCb)                           \
{                                                           \
   if(0 == (_rbCb->kwRbCb.rbOp & 0x0c) )                    \
   {                                                        \
      /* Free memory for rbCb */                            \
      KW_FREE(_rbCb, sizeof(RbCb));                         \
   }                                                        \
   else                                                     \
   {                                                        \
      _rbCb = NULLP;                                        \
   }                                                        \
   KW_LMM_RB_STS_DEC();                                     \
}
#else /* ((defined KW_BG_DL_PROC) || (defined KW_BG_UL_PROC)) */
#define KW_DBM_DELETE_RBCB(_rbCb)                           \
{                                                           \
   /* Free memory for rbCb */                               \
   KW_FREE(_rbCb, sizeof(RbCb));                            \
   KW_LMM_RB_STS_DEC();                                     \
}
#endif /* ((defined KW_BG_DL_PROC) || (defined KW_BG_UL_PROC)) */


#define kwCpyMsg(_cb,x, y) \
      (SAddMsgRef((x), KW_GET_MEM_REGION(_cb), KW_GET_MEM_POOL(_cb), (y)))

/* Upper Interface Module Macros */
#define KW_VALIDATE_RBID(_ueId, _rbId, _rbType, _ret)          \
{                                                              \
   _ret = ROK;                                                 \
   if (_ueId == 0)                                             \
   {                                                           \
      if (_rbId >= KW_MAX_RB_PER_CELL)                         \
      {                                                        \
         _ret = RFAILED;                                       \
      }                                                        \
   }                                                           \
   else                                                        \
   {                                                           \
      if ((_rbType != CM_LTE_SRB) && (_rbType != CM_LTE_DRB))  \
      {                                                        \
         _ret = RFAILED;                                       \
      }                                                        \
      else if (_rbType == CM_LTE_SRB &&_rbId >= KW_MAX_SRB_PER_UE)  \
      {                                                        \
         _ret = RFAILED;                                       \
      }                                                        \
      else if (_rbType == CM_LTE_DRB &&_rbId >= KW_MAX_DRB_PER_UE)  \
      {                                                        \
         _ret = RFAILED;                                       \
      }                                                        \
   }                                                           \
}

/* LMM Module Macros */
#define KW_LMM_RB_STS_INC(_cb)                                    \
{                                                              \
   _cb->genSts.numOfRb++;                                      \
}

#define KW_LMM_RB_STS_DEC(_cb)                                    \
{                                                              \
   _cb->genSts.numOfRb--;                                      \
}

#define KW_FREE_DAT_IND_BUF(_datIndInfo)                        \
{\
   U8 pduCount = 0;                                            \
   U8 lchCount = 0;                                            \
   RguPduInfo _pduInfo;                                        \
   U8   numLch = _datIndInfo->numLch;                          \
                                                               \
   for( lchCount = 0; lchCount < numLch; lchCount++ )          \
   {                                                           \
      _pduInfo = _datIndInfo->lchData[lchCount].pdu;           \
      for ( pduCount = 0;pduCount < _pduInfo.numPdu; pduCount++)\
      {                                                        \
         KW_FREE_BUF(_pduInfo.mBuf[pduCount]);                 \
      }                                                        \
   }                                                            \
}

#define KW_GET_DL_SAPCB(_cb, _rbCb) (_cb->u.dlCb->udxDlSap + _rbCb->udxSapId)
#define KW_GET_UL_SAPCB(_cb, _rbCb) (_cb->u.ulCb->udxUlSap + _rbCb->udxSapId)
#define KW_GET_UDX_SAP(_cb) (_cb->u.ulCb->udxUlSap)

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#define KW_L2_MAX_TIMERS        1
#define KW_QCI_LIST_BUCKET_SIZE 10
#define KW_TB_LIST_BUCKET_SIZE  10
#define KW_MAX_L2MEAS_EVT       10
/* L2 Measurement index to be used in rbCb to store measData */                                       
#define KW_L2MEAS_ACT_UE       0                                       
#define KW_L2MEAS_DL_DELAY     1                                       
#define KW_L2MEAS_DL_DISC      2
#define KW_L2MEAS_UU_LOSS      3
#define KW_L2MEAS_DL_IP        4
#define KW_L2MEAS_UL_IP        5
#endif /* LTE_L2_MEAS_RLC */
 
/* ############################PDCP DEFINES ############################# */
/* Venki - #ifndef */
#ifndef KW_PDCP
/*Fix for ccpu00121586*/
#define PJ_SRB1_ID   1
#define PJ_SRB2_ID   2

#define PJ_SAP_NOT_CFG        0     /*!< SAP Not Configured */
#define PJ_SAP_CFG            1     /*!< SAP Configured but not not bound */
#define PJ_SAP_BND            2     /*!< SAP Bound */
#define PJ_SAP_BINDING        3     /*!< SAP Bind initiated */
#define PJ_SAP_UBND           4     /*!< SAP Unbind */

/* Times related */
#define PJ_RB_MAX_TIMERS       1       /* No of timers */
#define PJ_MAX_OBD_TMR         3       /* Number of OBD Timers */
#define PJ_MAX_DISC_TMR        1       /* Number of Discard Timers */
#define PJ_EVT_DISC_TMR        0x10    /* DISC Event */
#define PJ_EVT_DL_OBD_TMR      0x11
#define PJ_EVT_UL_OBD_TMR      0x12
#define PJ_EVT_OBD_TMR         0x13
#define PJ_EVT_TMR_NONE        0x14
#define PJ_EVT_OBD_WAIT_TMR    0x15
#define PJ_EVT_UE_DEL_WAIT_TMR 0x16
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#define PJ_EVT_L2_TMR          0x17
#endif /* LTE_L2_MEAS_RLC */
#define PJ_DRB_7BIT_SN_HDR     0x0080
#define PJ_DRB_12BIT_SN_HDR    0x8000
#define PJ_ROHC_FEEDBACK_HDR   0x0010
#define PJ_FIRST_BIT           0x80

#define PJ_DATA_PDU            0x01
#define PJ_ROHC_FEEDBACK       0x02
#define PJ_STA_PDU             0x03

#define PJ_INTG_KEY_LEN        16
#define PJ_CIPHER_KEY_LEN      16

#define PJ_MAX_DAT_CFM         50

#define PJ_SDU_RECEIVED        0x01
#define PJ_WAIT_FOR_INTPROT    0x02
#define PJ_WAIT_FOR_CMP        0x03
#define PJ_WAIT_FOR_CIPHER     0x04
#define PJ_PDU_CONSTRUCTED     0x05
#define PJ_PDU_SUBMITTED       0x06

#define PJ_7_BIT_SN            7
#define PJ_12_BIT_SN           12

#define PJ_TX_BUF_LEN          256
#define PJ_MAX_SDU_SIZE        8188

#define PJ_SRB                 PJ_SRB_SAP
#define PJ_DRB                 PJ_DRB_SAP

#define PJ_SRB_SAP             0
#define PJ_DRB_SAP             1

#define PJ_DRB_UM              2
#define PJ_DRB_AM              3

#define PJ_CFM_NOK             1
#define PJ_CFM_OK              0

#define PJ_BYTE_LEN            8
/*
#define PJ_DIR_UL              KW_DIR_UL
#define PJ_DIR_DL              KW_DIR_DL
*/
#define PJ_SEC_DIR_UL          0
#define PJ_SEC_DIR_DL          1

#define PJ_PDU_CONSTRUCT_FAILED  1
#define PJ_HDR_COMP_FAILED       2
#define PJ_INTG_PROT_FAILED      3
#define PJ_CIPHER_FAILED         4
#define PJ_CPY_MSG_FAILED        5
#define PJ_REM_MSG_FAILED        6
#define PJ_DISC_TMR_EXP          7
#define PJ_OBD_TIMEOUT           8

#define PJ_CFG_RLC             1
#define PJ_CFG_PDCP            2
#define PJ_CFG_BOTH            3

/* kw005.201 moved the definition from kw_pj_dlm.c file */
#define KW_PJ_ASYNC_WIN        16
#ifdef LTE_L2_MEAS_RLC
/* L2 Measurement index to be used in rbCb to store measData */                                       
#define KW_L2MEAS_ACT_UE       0                                       
#define KW_L2MEAS_DL_DELAY     1                                       
#define KW_L2MEAS_DL_DISC      2
#define KW_L2MEAS_UU_LOSS      3
#define KW_L2MEAS_DL_IP        4
#define KW_L2MEAS_UL_IP        5

#define PJ_L2_MAX_TIMERS        1
/* L2 Measurement index to be used in pjRbCb to store measData */                                       
#define PJ_L2MEAS_ACT_UE        0
#define PJ_L2MEAS_DL_DELAY      1
#define PJ_L2MEAS_DL_DISC       2
#define PJ_L2MEAS_UL_LOSS       3

#define PJ_MAX_L2MEAS_EVT       10
#define PJ_MAX_L2MEAS_INRB      3
#define PJ_INIT_RB_L2CB(_measVal, _measCb, _pjRbCb)                       \
{                                                                         \
   cmLListAdd2Tail(&_measCb->rbList, &_pjRbCb->rbL2Cb.listNode[_measVal]);\
   _pjRbCb->rbL2Cb.l2Sts[_measVal] = &_measCb->measData[_pjRbCb->qci];    \
}

#define PJ_RMV_RB_FRM_L2LIST(_measVal, _measCb, _pjRbCb)          \
cmLListDelFrm(&_measCb->rbList,                                    \
     &_pjRbCb->rbL2Cb.listNode[_measVal]);

#define PJ_UPD_L2_DLDELAY_STS(_pjRbCb, _val)                      \
{                                                                 \
   _pjRbCb->rbL2Cb.l2Sts[PJ_L2MEAS_DL_DELAY]->dlDelay.numPkts++;          \
   _pjRbCb->rbL2Cb.l2Sts[PJ_L2MEAS_DL_DELAY]->dlDelay.val += _val;        \
}                                          

#define PJ_UPD_L2_ULLOSS_PKT_STS(_pjRbCb)                         \
{                                                                 \
   if(_pjRbCb->rbL2Cb.measOn & LPJ_L2MEAS_UL_LOSS)                \
      _pjRbCb->rbL2Cb.l2Sts[PJ_L2MEAS_UL_LOSS]->ulLoss.numPkts++;     \
}                                              

#define PJ_UPD_L2_ULLOSS_STS(_pjRbCb)                             \
{                                                                 \
   if(_pjRbCb->rbL2Cb.measOn & LPJ_L2MEAS_UL_LOSS)                \
   {                                                              \
      _pjRbCb->rbL2Cb.l2Sts[PJ_L2MEAS_UL_LOSS]->ulLoss.numPkts++;     \
      _pjRbCb->rbL2Cb.l2Sts[PJ_L2MEAS_UL_LOSS]->ulLoss.val++;      \
   }                                                              \
}                                              

#define PJ_UPD_L2_DLDISC_PKT_STS(_pjRbCb)                         \
{                                                                 \
   if((_pjRbCb->rbType == PJ_DRB) &&                              \
      (_pjRbCb->rbL2Cb.measOn & LPJ_L2MEAS_DL_DISC))              \
   {                                                              \
      _pjRbCb->rbL2Cb.l2Sts[PJ_L2MEAS_DL_DISC]->dlDisc.numPkts++;     \
   }                                                              \
}                                              

#define PJ_UPD_L2_DLDISC_STS(_pjRbCb)                             \
{                                                                 \
   if((_pjRbCb->rbType == PJ_DRB) &&                              \
      (_pjRbCb->rbL2Cb.measOn & LPJ_L2MEAS_DL_DISC))              \
   {                                                              \
      _pjRbCb->rbL2Cb.l2Sts[PJ_L2MEAS_DL_DISC]->dlDisc.val++;      \
   }                                                              \
}                                              

#else /* LTE_L2_MEAS_RLC */
#define PJ_UPD_L2_DLDELAY_STS(_pjRbCb, _val)
#define PJ_UPD_L2_ULLOSS_PKT_STS(_pjRbCb) 
#define PJ_UPD_L2_ULLOSS_STS(_pjRbCb)
#define PJ_UPD_L2_DLDISC_PKT_STS(_pjRbCb)  
#define PJ_UPD_L2_DLDISC_STS(_pjRbCb)      
#endif /* LTE_L2_MEAS_RLC */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC 
#if (ERRCLASS & ERRCLS_INT_PAR)
#define PJ_VALDATE_SAP(_chkSpId, _sap, _ret)                         \
{                                                                    \
   if (_chkSpId != _sap->spId)                                       \
   {                                                                 \
      PJLOGERROR(ERRCLS_DEBUG, EKWxxx, (ErrVal) RFAILED,             \
            "Sap Id Validation Failed.");                            \
      _ret = RFAILED;                                                \
   }                                                                 \
   /* SAP state validation */                                        \
   if(_sap->state != PJ_SAP_BND)                                     \
   {                                                                 \
      PJLOGERROR(ERRCLS_INT_PAR, EKWXXX, (ErrVal) RFAILED,           \
            "Sap State Invalid.");                                   \
      pjLmmSendAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,   \
            LCM_CAUSE_INV_STATE, 0, 0, 0);                              \
      _ret = RFAILED;                                                \
   }                                                                 \
}
#else /* ERRCLASS & ERRCLS_INT_PAR */
#define PJ_VALDATE_SAP(_chkSpId, _sap, _ret)                         \
{                                                                    \
   /* SAP state validation */                                        \
   if(_sap->state != PJ_SAP_BND)                                     \
   {                                                                 \
      PJLOGERROR(ERRCLS_INT_PAR, EKWXXX, (ErrVal) RFAILED,           \
            "Sap State Invalid.");                                   \
      pjLmmSendAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,   \
            LCM_CAUSE_INV_STATE, 0, 0, 0);                              \
      _ret = RFAILED;                                                \
   }                                                                 \
}
#endif /* ERRCLASS & ERRCLS_INT_PAR */                              
#else /* LTE_L2_MEAS_RLC */
#if (ERRCLASS & ERRCLS_INT_PAR)
#define PJ_VALDATE_SAP(_chkSpId, _sap, _ret)                         \
{                                                                    \
   if (_chkSpId != _sap->spId)                                       \
   {                                                                 \
      PJLOGERROR(ERRCLS_DEBUG, EKWxxx, (ErrVal) RFAILED,             \
            "Sap Id Validation Failed.");                            \
      _ret = RFAILED;                                                \
   }                                                                 \
   /* SAP state validation */                                        \
   if(_sap->state != PJ_SAP_BND)                                     \
   {                                                                 \
      PJLOGERROR(ERRCLS_INT_PAR, EKWXXX, (ErrVal) RFAILED,           \
            "Sap State Invalid.");                                   \
      pjLmmSendAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,   \
            LCM_CAUSE_INV_STATE, 0, 0);                              \
      _ret = RFAILED;                                                \
   }                                                                 \
}
#else /* ERRCLASS & ERRCLS_INT_PAR */
#define PJ_VALDATE_SAP(_chkSpId, _sap, _ret)                         \
{                                                                    \
   /* SAP state validation */                                        \
   if(_sap->state != PJ_SAP_BND)                                     \
   {                                                                 \
      PJLOGERROR(ERRCLS_INT_PAR, EKWXXX, (ErrVal) RFAILED,           \
            "Sap State Invalid.");                                   \
      pjLmmSendAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,   \
            LCM_CAUSE_INV_STATE, 0, 0);                              \
      _ret = RFAILED;                                                \
   }                                                                 \
}
#endif /* ERRCLASS & ERRCLS_INT_PAR */
#endif/* LTE_L2_MEAS_RLC */

#define KW_PJDBM_CREATE_RBCB(_rbCb,_rbCbLst, _rbId, _rbType)    \
{                                                               \
    /* Allocate memory for rbCb */                              \
   KW_ALLOC(_rbCb, sizeof(RbCb));                               \
                                                                \
   if ( rbCb != NULLP)                                          \
   {                                                            \
      _rbCbLst[_rbId] = (_rbCb);                                \
      _rbCb->kwRbCb.rlcId.rbId = _rbId;                         \
   }                                                            \
}                                                               

/* Macros for configuration module */
#define PJ_CFG_FILL_CFG_CFM(_entCfm, _rbId, _rbType, _status, _reason)   \
{                                                                        \
   _entCfm->rbId  = _rbId;                                               \
   _entCfm->rbType  = _rbType;                                           \
   _entCfm->status = _status;                                            \
   _entCfm->reason = _reason;                                            \
}

#define PJ_CFG_FILL_SECCFG_CFM(_entCfm, _ueId, _cellId, _transId, _status, _reason)  \
{                                                               \
   _entCfm->ueId   = _ueId;                                     \
   _entCfm->cellId = _cellId;                                   \
   _entCfm->transId = _transId;                                 \
   _entCfm->status = _status;                                   \
   _entCfm->reason = _reason;                                   \
}

#define PJ_CFG_FILL_SDUSTA_CFM(_entCfm, _ueId, _cellId, _transId, _status, _reason)  \
{                                                               \
   _entCfm->ueId   = _ueId;                                     \
   _entCfm->cellId = _cellId;                                   \
   _entCfm->transId = _transId;                                 \
   _entCfm->status = _status;                                   \
   _entCfm->reason = _reason;                                   \
}

#define PJ_CFG_FILL_REESTREQ_CFM(_entCfm, _ueId, _cellId, _transId, _status)  \
{                                                               \
   _entCfm->ueId   = _ueId;                                     \
   _entCfm->cellId = _cellId;                                   \
   _entCfm->transId = _transId;                                 \
   _entCfm->status = _status;                                   \
}

#define PJ_UPD_COUNT(_pjRbCb, _sn, _txHfn, _count)         \
{                                                          \
   _count = _sn;                                           \
   _txHfn = _txHfn << (_pjRbCb->snLen);                    \
   _count |= _txHfn;                                       \
} 

#define PJ_ADD_PRE_MSG(_pdu, _hdr, _numBytes, _ret)        \
{                                                          \
   Data _liByte;                                           \
   U16  _bytes;                                            \
   _bytes = 0;                                             \
   while (_numBytes > _bytes )                             \
   {                                                       \
      _liByte = (U8) (_hdr >> (8*_bytes));                 \
      _ret = SAddPreMsg((Data )_liByte, _pdu);             \
      if ( _ret != ROK )                                   \
      {                                                    \
         break;                                            \
      }                                                    \
      _bytes++;                                            \
   }                                                       \
}

#define PJ_RESET_ALL_VAR(_pjRbCb)                          \
{                                                          \
   _pjRbCb->dlCb.nxtTxSn  = 0;                             \
   _pjRbCb->dlCb.txHfn    = 0;                             \
   _pjRbCb->dlCb.nxtToSub = 0;                             \
   _pjRbCb->dlCb.cfmExp   = 0;                             \
   _pjRbCb->dlCb.count    = 0;                             \
}

#define PJ_ALLOC(_buf, _size)                              \
{                                                          \
 if (SGetSBuf(kwCb.init.region, kwCb.init.pool, (Data **)&_buf,\
                (Size) _size) == ROK)                      \
   {                                                       \
      cmMemset((U8 *)(_buf), 0, _size);                    \
   }                                                       \
   else                                                    \
   {                                                       \
      (_buf) = NULLP;                                      \
   }                                                       \
}

#define PJ_ALLOC_BUF(_buf)                                 \
{                                                          \
   if (SGetMsg(kwCb.init.region, kwCb.init.pool, (Buffer **)&_buf) != ROK) \
   {                                                       \
      (_buf) = NULLP;                                      \
   }                                                       \
}

#define PJ_FREE_BUF(_buf)                                  \
{                                                          \
   if (_buf != NULLP)                                      \
   {                                                       \
      SPutMsg(_buf);                                       \
   }                                                       \
   _buf = NULLP;                                           \
}

#define PJ_FREE(_buf, _size)                               \
{                                                          \
   if (_buf != NULLP)                                      \
   {                                                       \
      (Void) SPutSBuf(kwCb.init.region, kwCb.init.pool,    \
                         (Data *) _buf, (Size) _size);     \
      _buf = NULLP;                                        \
   }                                                       \
}     

#define PJ_PST_FREE(_region, _pool, _buf, _size)           \
{                                                          \
   if (_buf != NULLP)                                      \
   {                                                       \
      (Void) SPutSBuf(_region, _pool,                      \
                      (Data *) _buf, (Size) _size);        \
      _buf = NULLP;                                        \
   }                                                       \
}     

#define PJ_CPY_MSG(_x, _y, _ret)                           \
   _ret =(SAddMsgRef((_x), KW_GET_MEM_REGION(kwCb), KW_GET_MEM_POOL(kwCb), (_y)))                                                                                         
#define PJ_MEM_CPY(_dst, _src, _size)                      \
{                                                          \
   cmMemcpy((U8*)_dst, (U8 *)_src, _size);                 \
}

#define PJ_DLM_UPD_VAR(_pjRbCb, _sn, _txHfn)               \
{                                                          \
   PjDlCb    *_dlCb;                                       \
   U32        _maxTxSn;                                    \
                                                           \
   _dlCb   = &_pjRbCb->dlCb;                                \
   _sn    = _dlCb->nxtTxSn;                                 \
   _txHfn = _dlCb->txHfn;                                   \
   _maxTxSn = (1 << _pjRbCb->snLen);                        \
   if ( (++_dlCb->nxtTxSn) ==  _maxTxSn)                 \
   {                                                       \
      _dlCb->txHfn++;                                       \
      _dlCb->nxtTxSn = 0;                                   \
   }                                                       \
}

#define PJ_FILL_CFM_OK(_pjRbCb, _fms, _datCfm)             \
{                                                          \
   U32     _startCount = _pjRbCb->dlCb.cfmExp;             \
   U32     _stopCount  = _pjRbCb->dlCb.cfmExp;             \
   PjTxEnt *_ent;                                          \
   _ent = (PjTxEnt *)pjDbmGetTxEntSn( &(_pjRbCb->dlCb.txBuf), _fms); \
   if ( _ent != NULLP )                                    \
   {                                                       \
      _stopCount = _ent->count;                            \
      _pjRbCb->dlCb.cfmExp = _ent->count;                  \
      _pjRbCb->dlCb.nxtToSub = _ent->count;                \
   }                                                       \
   while ( _startCount < _stopCount )                      \
   {                                                       \
      _ent = (PjTxEnt *)pjDbmGetTxEnt( &(_pjRbCb->dlCb.txBuf), _startCount);\
      if ( _ent != NULLP )                                 \
      {                                                    \
         if ( _pjRbCb->dlCb.cfmReqd)                       \
         {                                                 \
            _datCfm->cfmSta[_datCfm->numSdus].sduId  = _ent->sduId;\
            _datCfm->cfmSta[_datCfm->numSdus].status = PJ_CFM_OK;\
            _datCfm->numSdus++;                            \
         }                                                 \
         pjDbmDelTxEnt( &(pjRbCb->dlCb.txBuf), _ent->count);\
      }                                                    \
      _startCount++;                                       \
   }                                                       \
}

#define PJ_UPD_CFM_EXP(_dlCb)                              \
{                                                          \
   U32 _curCount = _dlCb->count;                            \
   U32 _count    = _dlCb->cfmExp;                           \
   PjTxEnt *_txEnt = NULLP;                                \
   while ( _count <= _curCount )                           \
   {                                                       \
      _txEnt = (PjTxEnt *)pjDbmGetTxEnt(&(_dlCb->txBuf), _count);\
      if ( _txEnt != NULLP )                               \
      {                                                    \
         break;                                            \
      }                                                    \
      _count++;                                            \
   }                                                       \
   _dlCb->cfmExp = _count;                                  \
}
#define PJ_SND_CFM(_pjRbCb, _txEnt, _cause)                \
{                                                          \
   PjuDatCfmInfo *_datCfm;                                 \
   CmLtePdcpId *_pdcpId;                                   \
   KwPjuSapCb  *_pjuSap;                                   \
   if (_pjRbCb->rbType == PJ_SRB)                          \
      _pjuSap   = &(kwCb.pjuSap[PJ_SRB_SAP]);                  \
   else                                                    \
      _pjuSap   = &(kwCb.pjuSap[PJ_DRB_SAP]);                  \
                                                           \
   PJ_ALLOC( _datCfm, sizeof(PjuDatCfmInfo));              \
   PJ_ALLOC( _pdcpId, sizeof(CmLtePdcpId));                \
   if ( _datCfm != NULLP && _pdcpId != NULLP )             \
   {                                                       \
      _datCfm->cfmSta[_datCfm->numSdus].sduId = _txEnt->sduId;\
      _datCfm->cfmSta[_datCfm->numSdus].status = _cause;   \
      _datCfm->numSdus++;                                  \
      _pdcpId->rbId   = _pjRbCb->rbId;                     \
      _pdcpId->rbType = _pjRbCb->rbType;                   \
      _pdcpId->ueId   = _pjRbCb->ueCb->key.ueId;           \
      _pdcpId->cellId = _pjRbCb->ueCb->key.cellId;         \
      PjUiPjuDatCfm(&(_pjuSap->pst), _pjuSap->suId, _pdcpId, _datCfm);\
   }                                                       \
   pjDbmDelTxEnt( &(pjRbCb->dlCb.txBuf), _txEnt->count);   \
}

#define PJ_UPD_DL_VAR(_pjRbCb, _curCnt)                    \
{                                                          \
   U32   _count = _curCnt + 1;                             \
   if ( _pjRbCb->dlCb.nxtToSub == _curCnt )                \
   {                                                       \
      _pjRbCb->dlCb.nxtToSub = _count;                     \
   }                                                       \
   if ( _pjRbCb->dlCb.cfmExp  == _curCnt )                 \
   {                                                       \
      _pjRbCb->dlCb.cfmExp = _count;                       \
   }                                                       \
}

#define PJ_CREATE_NEW_LIST(_pjRbCb, _tmpTxBuf, _ret)       \
{                                                          \
   _tmpTxBuf.datQ  = _pjRbCb->dlCb.txBuf.datQ;             \
   _tmpTxBuf.numEntries =  pjRbCb->dlCb.txBuf.numEntries;  \
   _tmpTxBuf.numBins =  pjRbCb->dlCb.txBuf.numBins;        \
   pjDbmBufInit(&pjRbCb->dlCb.txBuf,kwCb.pjGenCfg.nmbDlBins);\
   if ( _pjRbCb->dlCb.txBuf.datQ == NULLP )                \
   {                                                       \
      PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED, \
         "PJ_CREATE_NEW_LIST: PJ_ALLOC Failed.");          \
      _ret = RFAILED;                                      \
   }                                                       \
}

#define PJ_SND_ROHC_FDB(_pjRbCb, _rohcFdbPdu, _ret)        \
{                                                          \
   Data _hdr = 0;                                          \
   U8   _rbCfgStat = 0;                                    \
   U32  _count = 0;                                        \
   _hdr |= PJ_ROHC_FEEDBACK_HDR;                           \
   _ret = SAddPreMsg((Data) _hdr, _rohcFdbPdu);            \
   if ( _ret != ROK )                                      \
   {                                                       \
      PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal)0,        \
         "PJ_SND__ROHC_FDB: SAddPreMsg failed for pdu \n");\
      PJ_FREE_BUF(_rohcFdbPdu);                            \
      _ret  =  RFAILED;                                    \
   }                                                       \
   if (_pjRbCb->rbType == CM_LTE_SRB )                              \
   {                                                                \
       _rbCfgStat = _pjRbCb->ueCb->srbCb[pjRbCb->rbId]->rbCfgStat;  \
   }                                                                \
   else                                                             \
   {                                                                \
      _rbCfgStat = _pjRbCb->ueCb->drbCb[pjRbCb->rbId]->rbCfgStat;   \
   }                                                                \
   if ( !(_rbCfgStat & PJ_CFG_RLC) )                       \
   {                                                       \
      PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal)0,        \
         "PJ_SND__ROHC_FDB: RLC is not configured \n");    \
      PJ_FREE_BUF(_rohcFdbPdu);                            \
      _ret = RFAILED;                                      \
   }                                                       \
   if ( _pjRbCb->mode == PJ_DRB_UM )                       \
   {                                                       \
      _count = _pjRbCb->dlCb.nxtToSub - 1;                 \
   }                                                       \
   else                                                    \
   {                                                       \
      _count = _pjRbCb->dlCb.cfmExp - 1;                   \
   }                                                       \
   if ( _ret == ROK )                                      \
   {                                                       \
      kwUimDatReq(_pjRbCb, _count, _rohcFdbPdu);           \
   }                                                       \
}

/* Defines used in gp_pj_dbm.c */
#define PJ_HASH_FN(_buf, _cnt) (_cnt % _buf->numBins)

/* Defines used in gp_pj_ulm.c */
#define MAX_BMAP_SIZE         2048
#define PJ_DRB_AM_WINSIZE     2048
#define PJ_U16_BIT_SIZE       16
#define PJ_BYTE_SIZE          8
#define PJ_SRB_SN_LEN         5
#define PJ_DRBAM_SN_LEN       12
#define PJ_TYPE_DRB_DATA      0x80
#define PJ_TYPE_STATUS_REPORT  0x00
#define PJ_TYPE_ROHC_FEEDBACK 0x01
#define PJ_PDU_BIT_MASK       0x70
#define PJ_12_BIT_SN_MSB_MASK 0x0F
#define PJ_CPDU_RES_VAL_MASK       0x0F
#define PJ_MACI_LEN           4

#define PJ_RDY_TO_DCIPHER      1
#define PJ_SENT_TO_DCIPHER     2
#define PJ_RDY_TO_INTVER       3
#define PJ_SENT_TO_INTVER      4
#define PJ_RDY_TO_DCOMP        5
#define PJ_SENT_TO_DCOMP       6
#define PJ_RDY_TO_SUBMIT       7

#define PJ_STATE_NORMAL       1
#define PJ_STATE_REEST        2
#define PJ_STATE_REEST_HO     3
#define PJ_TMR_ULM_OBD        10

/* Defines used in gp_pj_utl.c */
#define PJ_LIB_COMP_BIT_MASK     0x00000001
#define PJ_LIB_INT_BIT_MASK      0x00000002
#define PJ_LIB_CP_CIP_BIT_MASK   0x00000004
#define PJ_LIB_UP_CIP_BIT_MASK   0x00000008

/* Defines used for multi cfg confirms */
#define PJ_MAX_ASYNC_CFM   2

#define PJ_SEC_ASYNC_CFM         0x01
#define PJ_CFG_ASYNC_CFM         0x02
#define PJ_CFG_REEST_ASYNC_CFM   0x04
#define PJ_CFG_UEDEL_ASYNC_CFM   0x08
#define PJ_REEST_ASYNC_CFM       0x10

#define  PJ_SEC_INIT_CFM   1
#define  PJ_CMP_INIT_CFM   2


#define PJ_CHK_RESTART_OBD_TIMER(_ueCb, _cfgTxId)                             \
{                                                                             \
   U16 _idx;                                                                  \
   if(_ueCb->libInfo.crntTmrTxId == _cfgTxId)                                 \
   {                                                                          \
      pjStopTmr((PTR)_ueCb, PJ_EVT_OBD_WAIT_TMR);                             \
   }                                                                          \
                                                                              \
   if(pjChkTmr((PTR)_ueCb, PJ_EVT_OBD_WAIT_TMR) == FALSE)                     \
   {                                                                          \
      for(_idx = 0; _idx < (PJ_MAX_ASYNC_CFM - 1) ; _idx++)                   \
      {                                                                       \
         _ueCb->libInfo.crntTmrTxId =                                         \
                (_ueCb->libInfo.crntTmrTxId + 1) % PJ_MAX_ASYNC_CFM;          \
         if((_ueCb->libInfo.asyncCfm[_ueCb->libInfo.crntTmrTxId] != NULLP) && \
            (_ueCb->libInfo.asyncCfm[_ueCb->libInfo.crntTmrTxId]->startTmr    \
                                                      == TRUE))               \
         {                                                                    \
            pjStartTmr((PTR)_ueCb, PJ_EVT_OBD_WAIT_TMR);                      \
            break;                                                            \
         }                                                                    \
      }                                                                       \
   }                                                                          \
}                                                                             \

#define PJ_CLEAN_AND_UPD_ASYNCINFO(_ueCb, _txIdx)                 \
{                                                                 \
   PJ_FREE(_ueCb->libInfo.asyncCfm[_txIdx], sizeof(PjAsyncCfm));  \
   _ueCb->libInfo.asyncCfm[_txIdx]=NULLP;                         \
   if(_ueCb->libInfo.nxtAvlbTxId  == PJ_MAX_ASYNC_CFM)            \
   {                                                              \
      _ueCb->libInfo.nxtAvlbTxId  = _txIdx;                       \
   }                                                              \
}                                                                 \

#define PJ_FILL_TIMEOUT_CFG_CFM_INFO(_cfgCfm, _asyncCfm)                     \
{                                                                            \
      U16 _idx;                                                              \
      PJ_ALLOC(_cfgCfm, sizeof(CpjCfgCfmInfo));                              \
      if (_cfgCfm != NULLP)                                                  \
      {                                                                      \
         for ( _idx = 0; _idx < _asyncCfm->numEnt ; _idx++)                  \
         {                                                                   \
            if ( _asyncCfm->cmpInitBitMask &                                 \
                           (1 << (_asyncCfm->cfmEnt[_idx].rbId - 1)))        \
            {                                                                \
               _cfgCfm->cfmEnt[_idx].status =  CPJ_CFG_CFM_NOK;              \
               _cfgCfm->cfmEnt[_idx].reason = CPJ_CFG_REAS_OBD_TIMEOUT;      \
            }                                                                \
            else                                                             \
            {                                                                \
               _cfgCfm->cfmEnt[_idx].status = _asyncCfm->cfmEnt[_idx].status;\
               _cfgCfm->cfmEnt[_idx].reason = _asyncCfm->cfmEnt[_idx].reason;\
            }                                                                \
            _cfgCfm->cfmEnt[_idx].rbId   = _asyncCfm->cfmEnt[_idx].rbId;     \
            _cfgCfm->cfmEnt[_idx].rbType = _asyncCfm->cfmEnt[_idx].rbType;   \
         }                                                                   \
         _cfgCfm->ueId    = _asyncCfm->ueId;                                 \
         _cfgCfm->cellId  = _asyncCfm->cellId;                               \
         _cfgCfm->transId = _asyncCfm->transId;                              \
         _cfgCfm->numEnt  = _asyncCfm->numEnt;                               \
      }                                                                      \
}                                                                            \

/* kw006.201, ccpu00120574, fixed the warning */
/* In the case when all the elements in the reception buffer have already
 * been sent to the dcomp unit or sent up, our nxtSubDcomp will be pointing to 
 * NEXT_PDCP_RX_SN. So if there is a jump, this has to be updated accordingly */
#define PJ_ULM_UPD_NXT2DCOMP(_ulCb, _snLen, _sn, _oldRxCnt)        \
{                                                                  \
   if(_oldRxCnt == _ulCb->nxtSubDeCmp)                             \
   {                                                               \
      PJ_GET_COUNT(_ulCb->nxtSubCnt, _snLen, _sn, _ulCb->rxHfn);   \
   }                                                               \
}

#if (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC))
/* There can be a case where the first PDU that you receive *
 * does not match with the NEXT_PDCP_RX_SN. If nxtSubCnt is also
 * pointing to NETX_PDCP_RX_SN, it has to be updated. */
#define PJ_ULM_UPD_NXT2SUB(_ulCb, _cnt)                      \
{                                                            \
   if(_ulCb->recBuf.numEntries == 0)                         \
   {                                                         \
      _ulCb->nxtSubCnt = _cnt;                               \
      _ulCb->nxtSubDeCmp = _cnt;                             \
   }                                                         \
}
#define PJ_INC_OBD_COUNT(_pjRbCb, _count)                                \
{                                                                        \
   if(_pjRbCb->state == PJ_STATE_REEST ||                                \
         _pjRbCb->state == PJ_STATE_REEST_HO)                            \
   {                                                                     \
      _pjRbCb->ulCb.obdCnt ++;                                           \
   }                                                                     \
}

/* Notes: This will be called only for DRBs */
#define PJ_DEC_OBD_COUNT(_pjRbCb, _count)                                \
{                                                                        \
   if(_pjRbCb->state == PJ_STATE_REEST ||                                \
         _pjRbCb->state == PJ_STATE_REEST_HO)                            \
   {                                                                     \
      if((_count >= _pjRbCb->ulCb.firstReEstCnt)&&                       \
         (_pjRbCb->mode = PJ_DRB_AM))                                    \
      {                                                                  \
         _pjRbCb->ulCb.obdCnt --;                                        \
      }                                                                  \
   }                                                                     \
}
#else /* (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC)) */
/* Dummy defines */
#define PJ_ULM_UPD_NXT2SUB(_ulCb, _cnt)    
#define PJ_INC_OBD_COUNT(_pjRbCb, _count)  
#define PJ_DEC_OBD_COUNT(_pjRbCb, _count)  
#endif /* (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC)) */

#define PJ_ULM_UPD_RX_VAR(_sn, _pjRbCb)                          \
{                                                                \
   if(_sn < _pjRbCb->ulCb.nxtRxSn)                               \
   {                                                             \
      _pjRbCb->ulCb.rxHfn++;                                     \
   }                                                             \
                                                                 \
   _pjRbCb->ulCb.nxtRxSn = (_sn + 1) % (1 << _pjRbCb->snLen);    \
   if(_pjRbCb->ulCb.nxtRxSn == 0)                                \
   {                                                             \
      _pjRbCb->ulCb.rxHfn ++;                                    \
   }                                                             \
}

#define PJ_INC_SN(_sn, _snLen) ((++_sn) % (1 << _snLen))                      \

#define PJ_GET_SN_HFN(_count, _snLen, _sn, _hfn)             \
{                                                            \
   _sn   =  _count % (1 << _snLen);                          \
   _hfn  =  (_count >> _snLen);                              \
}                                                            \

#define PJ_GET_SN(_count, _snLen, _sn)  (_sn   =  _count % (1 << _snLen));

#define PJ_ULM_REEST_DRB_AM(_pjRbCb)                         \
{                                                            \
   _pjRbCb->frstReEstCnt =  _pjRbCb->lastSubCnt + 1;         \
   _pjRbCb->obdCnt  =  0;                                    \
                                                             \
}                                                            

#define PJ_ULM_UPD_HFN(_sn, _pjRbCb, _ulCb, _hfn)              \
{                                                              \
   if(_sn < _pjRbCb->ulCb.nxtRxSn)                             \
   {                                                           \
      _hfn  = (_ulCb->rxHfn + 1 );                             \
   }                                                           \
   else                                                        \
   {                                                           \
      _hfn  = _ulCb->rxHfn;                                    \
   }                                                           \
}

#define PJ_ULM_SRB_UPD_COUNT(_sn, _pjRbCb, _ulCb, _count)      \
{                                                              \
   if(_sn < _ulCb->nxtRxSn)                                    \
   {                                                           \
      _count  = ((_ulCb->rxHfn + 1 ) << _pjRbCb->snLen) | _sn; \
   }                                                           \
   else                                                        \
   {                                                           \
      _count  = (_ulCb->rxHfn  << _pjRbCb->snLen) | _sn;       \
   }                                                           \
}

/* Check for wrap around */                                      
#define PJ_ULM_UPD_RXHFN(_ulCb, _sn)                             \
{                                                                \
   if(_sn < _ulCb->nxtRxSn)  ulCb->rxHfn ++;                     \
}

/* kw005.201,replaced macro with function */

#define  PJ_FILL_SDU_CFM_INFO(_cfmInfo, _ueCb)                    \
{                                                                 \
   U8 _rbCnt;                                                     \
   U8 _numRb = 0;                                                 \
   PjHoCfmInfo *_hoCfmInfo;                                       \
   CpjSduStaInfo  *_staInfo;                                      \
   _cfmInfo->ueId    = _ueCb->key.ueId;                           \
   _cfmInfo->cellId  = _ueCb->key.cellId;                         \
   _cfmInfo->transId = _ueCb->hoInfo->transId;                    \
   for(_rbCnt = 0; _rbCnt < KW_MAX_DRB_PER_UE; _rbCnt++)          \
   {                                                              \
      _hoCfmInfo   =  &_ueCb->hoInfo->hoCfmInfo[_rbCnt];          \
      _staInfo     =  &_cfmInfo->sduStaInfo[_numRb];              \
      if(_hoCfmInfo->pres != TRUE)                                \
      {                                                           \
         continue;                                                \
      }                                                           \
                                                                  \
      _staInfo->rbId  =  _hoCfmInfo->rbId;                        \
      _staInfo->dir   =  _hoCfmInfo->dir;                         \
      _staInfo->ulSduStaInfo.numBits   =  _hoCfmInfo->ul.numBits; \
      _staInfo->ulSduStaInfo.ulBitMap  =  _hoCfmInfo->ul.ulBitMap;\
      _staInfo->ulSduStaInfo.count     =  _hoCfmInfo->ul.count;   \
      _staInfo->dlSduStaInfo.count     =  _hoCfmInfo->dl.count;   \
                                                                  \
      _hoCfmInfo->ul.ulBitMap          =  NULLP;                  \
      _numRb++;                                                   \
   }                                                              \
   _cfmInfo->numRb = _numRb;                                      \
   PJ_FREE(_ueCb->hoInfo->hoCfmInfo, (KW_MAX_DRB_PER_UE * sizeof(PjHoCfmInfo))) \
   PJ_FREE(_ueCb->hoInfo, sizeof(PjHoInfo));                      \
}

#define  PJ_FILL_REEST_CFM_INFO(_reEstCfm, _asyncCfm, _status)  \
{                                                               \
   _reEstCfm->ueId    =  _asyncCfm->ueId;                       \
   _reEstCfm->cellId  =  _asyncCfm->cellId;                     \
   _reEstCfm->transId =  _asyncCfm->transId;                    \
   _reEstCfm->status  =  _status;                               \
}

#define  PJ_FILL_SEC_CFM_INFO(_secCfgCfm, _asyncCfm)  \
{                                                     \
   _secCfgCfm->ueId    =  _asyncCfm->ueId;            \
   _secCfgCfm->cellId  =  _asyncCfm->cellId;          \
   _secCfgCfm->transId =  _asyncCfm->transId;         \
   _secCfgCfm->status  =  CPJ_CFG_CFM_OK;             \
   _secCfgCfm->reason  =  CPJ_CFG_REAS_NONE;          \
}

#define PJ_GET_COUNT(_count, _snLen, _sn, _hfn)              \
{                                                            \
   _count   =  (_hfn << _snLen) | _sn;                       \
}                                                            

#define PJ_GET_DATFWD_CNT(_pjRbCb, _datFwdSn, _count)                               \
{                                                                                   \
   if((_pjRbCb->ulCb.nxtRxSn == 0) && (_pjRbCb->ulCb.rxHfn == 0))                   \
   {                                                                                \
      PJ_GET_COUNT(_count, PJ_DRBAM_SN_LEN, _datFwdSn, 0);                          \
   }                                                                                \
   else if(_datFwdSn >= _pjRbCb->ulCb.nxtRxSn)                                      \
   {                                                                                \
      PJ_GET_COUNT(_count, PJ_DRBAM_SN_LEN, _datFwdSn, (_pjRbCb->ulCb.rxHfn));      \
   }                                                                                \
   else                                                                             \
   {                                                                                \
      PJ_GET_COUNT(_count, PJ_DRBAM_SN_LEN, _datFwdSn, (_pjRbCb->ulCb.rxHfn + 1));  \
   }                                                                                \
}

/* kw006.201 ccpu00118629, Replaced macro with function */

#define PJ_ULM_DRBUM_REEST(_pjRbCb)       \
{                                         \
   _pjRbCb->ulCb.nxtRxSn   =  0;          \
   _pjRbCb->ulCb.rxHfn    =  0;           \
   pjUlmDecReEstCnt(_pjRbCb);         \
}

#define PJ_CHK_SN_OUTSIDE_WIN(_ulCb, _sn)                                       \
(                                                                               \
 (((_sn - (_ulCb->lastSubCnt % (1 << PJ_DRBAM_SN_LEN ))) % (1 << PJ_DRBAM_SN_LEN )) > PJ_DRB_AM_WINSIZE) || \
 ((((_ulCb->lastSubCnt % (1 << PJ_DRBAM_SN_LEN )) - _sn) >= 0) &&               \
  (((_ulCb->lastSubCnt % (1 << PJ_DRBAM_SN_LEN )) - _sn) < PJ_DRB_AM_WINSIZE))  \
)   

/* kw006.201 ccpu00118629, Replaced macro with function */
 
/* There is case that all PDUs in the recv Buf can be back from off board 
 * but not sent up. In that case, though the the recvBuf has entries the 
 * obd timer should not be restarted. This works with the PJ_ULM_GET_DRBAM_SUBCNT
 * macro to acheive this. */
#define PJ_DRBAM_ALL_PDU_RECVD(_pjRbCb)\
((pjRbCb->rbType == PJ_DRB) &&         \
 (pjRbCb->mode == PJ_DRB_AM) &&        \
 (ulCb->lastSubCnt == ulCb->obdPdu))   \

/* kw006.201 ccpu00118629, Replaced macro with function */
#define PJ_STS_INC_GEN_CNT(_cntr)            \
{                                            \
   kwCb.pjGenSts._cntr++;                    \
}                                            \

#define PJ_STS_INC_PJU_CNT(_rbType, _cntr)   \
{                                            \
   if (_rbType == PJ_SRB)                    \
      kwCb.pjuSap[PJ_SRB_SAP].sts._cntr++;   \
   else                                      \
      kwCb.pjuSap[PJ_DRB_SAP].sts._cntr++;   \
}                                            \

#define PJ_PK_U8(_msg, _val, _ret)                                     \
{                                                                      \
   (_ret) = SAddPstMsg((Data) (_val), (_msg));                         \
}

#define PJ_PK_U16(_msg, _val, _ret)                                    \
{                                                                      \
   PJ_PK_U8(_msg, (U8) GetHiByte(_val), _ret)                          \
   if ((_ret) == ROK)                                                  \
      PJ_PK_U8(_msg, (U8) GetLoByte(_val), _ret)                       \
}

#define PJ_PK_U32(_msg, _val, _ret)                                    \
{                                                                      \
   U16 _tmp16;                                                         \
   _tmp16 = (U16) GetHiWord(_val);                                     \
   PJ_PK_U16(_msg, _tmp16, _ret)                                       \
   if ((_ret) == ROK)                                                  \
   {                                                                   \
      _tmp16 = (U16) GetLoWord(_val);                                  \
      PJ_PK_U16(_msg, _tmp16, _ret)                                    \
   }                                                                   \
}

#define PJ_PACK_MACI(_mBuf, _macI)              \
{                                               \
   U16 _tmp;                                    \
   Data _pkArray[4];                            \
   _tmp = (U16) GetHiWord(_macI);               \
   _pkArray[0] = (Data) GetHiByte(_tmp);        \
   _pkArray[1] = (Data) GetLoByte(_tmp);        \
   _tmp = (U16) GetLoWord(_macI);               \
   _pkArray[2] = (Data) GetHiByte(_tmp);        \
   _pkArray[3] = (Data) GetLoByte(_tmp);        \
   SAddPstMsgMult(_pkArray, (MsgLen) 4, _mBuf); \
}

#define PJ_UNPK_MACI(_mBuf, _macI)                          \
{                                                           \
   U16 _tmp16 = 0;                                          \
   Data _unPkArray[4];                                      \
   SRemPstMsgMult(_unPkArray, (MsgLen)4, _mBuf);            \
   _tmp16 = (U16) PutHiByte(_tmp16, (U8) _unPkArray[3]);    \
   _tmp16 = (U16) PutLoByte(_tmp16, (U8) _unPkArray[2]);    \
   _macI  = (U32) PutHiWord(_macI, (U16) _tmp16);           \
   _tmp16 = (U16) PutHiByte(_tmp16, (U8) _unPkArray[1]);    \
   _tmp16 = (U16) PutLoByte(_tmp16, (U8) _unPkArray[0]);    \
   _macI  = (U32) PutLoWord(_macI, (U16) _tmp16);           \
}

#endif /* KW_PDCP */

#endif /* __KWH__ */
  
/********************************************************************30**
  
         End of file:     kw.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:47 2014
  
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
/main/7     kw006.201  ap  1. Replaced macro with function.
                           2. Optimization change ccpu00111716.
                           3. Warning removal, fix for ccpu00120574.
                       rd  4. Optimization change ccpu00117290.
                           5. ccpu00117290/ccpu00111716:Added code in
                              KW_DBM_DELETE_RBCB macro.
                           6. ccpu00121123:Added a macro for status pdu
                              creation logic correction.
                           7. ccpu00120364: Fix provided by removing extra
                              formatting.
                           8. ccpu00121586: PJ_SRB1_ID and PJ_SRB2_ID are
                              added.
                           9. ccpu00122594:Changed value of KW_MAX_LCH_PER_UE
                              from 12 to 10.
*********************************************************************91*/

