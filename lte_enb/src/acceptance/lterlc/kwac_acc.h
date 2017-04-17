

/********************************************************************20**
  
        Name:    RLC Acceptance File
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for and prototypes
                  CKW Interface
 
        File:    kwac_acc.h

        Sid:      kwac_acc.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:21 2014
  
        Prg:     chakrapani
  
*********************************************************************21*/

#ifndef __KWAC_ACC_H__
#define __KWAC_ACC_H__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

/*****************************************************************************
 *                            ACCEPTANCE DEFINITIONS
 *****************************************************************************/
/* PDU SET (NON-MIMO/MIMO) */
#define KWAC_NON_MIMO                     0
#define KWAC_MIMO                         1

#define KWAC_MAX_SIZE         50    /* Maximum Size */

/* kw005.201 Macro value increased from 128 to 1024 for TCs wrt RLC R9 
upgrade.*/
#define KWAC_MAX_CIRCQ_SIZE   1024  /* Maximum Size */
#define KWAC_MAX_CELL         50    /* Maximum Size */
#define KWAC_MAX_UE           50    /* Maximum Size */
#define KWAC_MAX_SRB          5     /* Maximum Size */
#define KWAC_MAX_DRB          35    /* Maximum Size */
#define KWAC_MAX_LC           50    /* Maximum Size */
#define KWAC_MAX_LCTYPE       5     /* Maximum Size */
#define KWAC_MAX_PDU          50    /* Maximum Size */

#define KWAC_PROCID_SINGLE 0

/* Different types of validations in KWU Interface */
#define KWAC_KWU_VALIDATE_NONE       0
#define KWAC_KWU_VALIDATE_SDU        1
#define KWAC_KWU_VALIDATE_SDUSZ      2

/* Different types of validations in RGU Interface */
#define KWAC_RGU_VALIDATE_NONE       0
#define KWAC_RGU_VALIDATE_SKIP       1
#define KWAC_RGU_VALIDATE_LI         2
#define KWAC_RGU_VALIDATE_BO         3

/*-- This shall be equal one more than the last flag value --*/
/* kw005.201 increased value from 5 to 20 after adding L2 Measurement */
#define KWAC_MAX_FLAGS               20

/* LKW Defines */
#define KWAC_LKW_LC                    0
#define KWAC_LKW_TC                    1

/* Validation Types */
#define KWAC_SDU_DISCARD                     1
#define KWAC_PDU_DISCARD                     2
#define KWAC_PDU_RX_TX                       3

/* SAP ID defines */
#define KWAC_NH_SAP              0
#define KWAC_PJ_SAP              1
#define KWAC_CKW_SAP             2
#define KWAC_RG_SAP              3
#define KWAC_CPJ_SAP             4
#define KWAC_NH_PJU_SAP          5
#define KWAC_PX_PJU_SAP          6
/*Pradeep - added UDX SAP macro*/
#define KWAC_UDX_SAP             7

/* Maximum FDs for OBD interface */
#define KWAC_MAX_FD              100
#define KWAC_MAX_CB              10

/*Pradeep - New constants added for acceptance test*/
#define KWAC_DFLTRGN  0 
#define KWAC_DFLTPOOL 0
/*****************************************************************************
 *                            ACCEPTANCE MACROS
 *****************************************************************************/

/*****************************************************************************/
/*Pradeep: New macros introduced for acceptance test*/

#define KW_FREE_ACC(_buf, _size)                                     \
{                                                                    \
   if (_buf != NULLP)                                                \
   {                                                                 \
      (Void) SPutSBuf(KWAC_DFLTRGN, KWAC_DFLTPOOL,                   \
            (Data *) _buf, (Size) _size);                            \
      _buf = NULLP;                                                  \
   }                                                                 \
}

#define KW_ALLOC_ACC(_buf, _size)                                    \
{                                                                    \
 if (SGetSBuf(KWAC_DFLTRGN, KWAC_DFLTPOOL, (Data **)&_buf,           \
                (Size) _size) == ROK)                                \
   {                                                                 \
      cmMemset((U8 *)(_buf), 0, _size);                              \
   }                                                                 \
   else                                                              \
   {                                                                 \
      (_buf) = NULLP;                                                \
   }                                                                 \
}
/*Pradeep - TODO presently using instance and procId as 0. need to change this based on the configuration*/
#if (ERRCLASS & ERRCLS_INT_PAR)
#define KWLOGERROR_ACC(errCls, errCode, errVal, errDesc)                 \
        SLogError(ENTKW, 0/*instance*/, 0 /*procId*/,                 \
                   __FILE__, __LINE__, errCls, errCode, errVal, errDesc)
#endif
/*****************************************************************************/


/* Form the SDU with requested size */
#define KWAC_FORM_SDU(_sdu, _size, _sData, _mBuf)                    \
{                                                                    \
   U16   _idx;                                                       \
   if (_size)                                                        \
   {                                                                 \
      for (_idx = 0; _idx < _size; _idx++)                           \
      {                                                              \
         _sdu[_idx] = (U8)(_idx % 255);                              \
      }                                                              \
                                                                     \
      /* put flat buffer into mBuf */                                \
      if (SAddPreMsgMult((Data *)_sdu, _size , *_mBuf) != ROK)       \
      {                                                              \
         CMXTA_DBG_ERR((_cmxtap, "KWAC_FORM_SDU Failed: resource unavailble \n"));\
         RETVALUE(CMXTA_ERR_RSRC);                                   \
      }                                                              \
   }                                                                 \
}

/* Copy mBuf from one msg to other msg without deleting the source */
#define KWAC_CPY_MBUF(_srcMBuf, _dstMBuf)                            \
{                                                                    \
   if (SCpyMsgMsg(_srcMBuf, KWAC_KWU_DFLTRGN, KWAC_KWU_DFLTPOOL,         \
            &_dstMBuf) != ROK)                                \
   {                                                                 \
      CMXTA_DBG_ERR((_cmxtap, "KWAC_CPY_MBUF Failed: Resource unavailble \n"));\
      RETVALUE(CMXTA_ERR_RSRC);                                      \
   }                                                                 \
}

#define KW_FORM_BITS(_val, _len, _eb, _hdr)                \
{                                                          \
   U16 _pIdx = idx;                                        \
   U16 _cIdx = idx + 1;                                    \
   U8  tPdu;                                               \
   U16 tVal;                                               \
                                                           \
   if (_eb >= _len)                                        \
   {                                                       \
      if (pEb - pLen == 0)\
      {\
         idx++;\
         _pIdx = idx;\
      }\
      tPdu = (_val << (_eb - _len)) | _hdr[_pIdx];         \
      _hdr[_pIdx] = tPdu;                                  \
      pEb = _eb;\
      pLen = _len;\
      _eb = _eb - _len;                              \
   }                                                       \
   else if (_eb < _len)                                    \
   {                                                       \
      tVal = _val;                                         \
      if (_eb != 0)                                        \
      {                                                    \
         tPdu = (tVal >> (_len - _eb)) | _hdr[_pIdx];      \
         _hdr[_pIdx] = tPdu;                               \
      }                                                    \
      if (_len - _eb == KW_BYTE_LEN)                       \
      {                                                    \
         _hdr[_cIdx] = (U8)tVal;                           \
         idx = _cIdx;                                      \
         pEb = _eb;\
         pLen = _len;\
         _eb = KW_BYTE_LEN - (_len - _eb);                 \
      }                                                    \
      else if (_len - _eb < KW_BYTE_LEN)                   \
      {                                                    \
         if (_eb == 0)\
            _hdr[_cIdx] = tVal << (KW_BYTE_LEN - _len);    \
         else\
           _hdr[_cIdx] = tVal << (_len - _eb);            \
         idx = _cIdx;                                      \
         pEb = _eb;\
         pLen = _len;\
         _eb = KW_BYTE_LEN - (_len - _eb);                 \
      }                                                    \
      else                                                 \
      {                                                    \
         _hdr[_cIdx++] = tVal >> ((_len - _eb) - KW_BYTE_LEN); \
         _hdr[_cIdx] = tVal << KW_BYTE_LEN;                \
         idx = _cIdx;                                      \
         pEb = _eb;\
         pLen = _len;\
         _eb = KW_BYTE_LEN - ((_len - _eb) - KW_BYTE_LEN); \
      }                                                    \
   }                                                       \
}

#define KW_CONSTRUCT_AM_HDR(_amHdr, _isSeg, hdr)           \
{                                                          \
   U8  e;                                                  \
   S16 numLi;                                              \
   U8  eb = 0;                                             \
   U8  pEb = 1;                                             \
   U8  pLen = 0;\
                                                           \
   numLi = _amHdr.numLi - 1;                               \
   /* For fixed part of the header */                      \
   hdr[0] = KW_DATA_PDU;                                   \
   hdr[0] = hdr[0] << (KW_BYTE_LEN - KW_DC_LEN);           \
   eb = KW_BYTE_LEN - KW_DC_LEN;                           \
   KW_FORM_BITS(_amHdr.rf,   KW_RF_LEN, eb, hdr);          \
   KW_FORM_BITS(_amHdr.p,    KW_P_LEN, eb, hdr);           \
   KW_FORM_BITS(_amHdr.fi,   KW_FI_LEN, eb, hdr);          \
   e = (numLi > 0) ? 1 : 0;                                \
   KW_FORM_BITS(e,           KW_E_LEN, eb, hdr);           \
   KW_FORM_BITS(_amHdr.sn,   KW_SN_LEN, eb, hdr);          \
   if (_isSeg == TRUE)                                     \
   {                                                       \
      KW_FORM_BITS(_amHdr.lsf,  KW_LSF_LEN, eb, hdr);      \
      KW_FORM_BITS(_amHdr.so,   KW_SO_LEN, eb, hdr);       \
   }                                                       \
   /* For extension part of the header */                  \
   if (numLi > 0)                                          \
   {                                                       \
      U8 count = 0;                                         \
      while (count < (_amHdr.numLi-1))                                \
      {                                                    \
         e = (numLi > 1) ? 1 : 0;                          \
         KW_FORM_BITS(e,     KW_E_LEN, eb, hdr);           \
         KW_FORM_BITS(_amHdr.li[count], KW_LI_LEN, eb, hdr);    \
         count++;\
         numLi--;\
      }                                                    \
   }                                                       \
}

#ifdef KW_PDCP

#define KWAC_FORM_PDCP_AM_7BIT_HDR(_sdu, _sn, _mBuf)              \
{                                                                 \
   _sdu[0] = _sn;                                                  \
   _sdu[0] |= PJ_DRB_7BIT_SN_HDR;                                 \
   /* put flat buffer into mBuf */                                \
   if (SAddPreMsgMult((Data *)_sdu, 1, *_mBuf) != ROK)            \
   {                                                              \
      CMXTA_DBG_ERR((_cmxtap,                                     \
        "KWAC_FORM_PDCP_AM_7BIT_HDR Failed: resource unavailble \n"));\
      RETVALUE(CMXTA_ERR_RSRC);                                   \
   }                                                              \
}

#define KWAC_FORM_PDCP_SRB_5BIT_HDR(_sdu, _sn, _mBuf)             \
{                                                                 \
   /* put flat buffer into mBuf */                                \
   if (SAddPreMsg((Data )_sn,  *_mBuf) != ROK)                    \
   {                                                              \
      CMXTA_DBG_ERR((_cmxtap,                                     \
        "KWAC_FORM_PDCP_SRB_5BIT_HDR Failed: resource unavailble \n"));\
      RETVALUE(CMXTA_ERR_RSRC);                                   \
   }                                                              \
}

#define KWAC_FORM_PDCP_AM_12BIT_HDR(_sdu, _sn, _mBuf)             \
{                                                                 \
   _sdu[0] = (U8)_sn;                                             \
   _sdu[1] = (U8)(((U16)_sn)>>8);                                 \
   _sdu[1] |= 0x80;                                               \
   /* put flat buffer into mBuf */                                \
   if (SAddPreMsgMult((Data *)_sdu, 2, *_mBuf) != ROK)            \
   {                                                              \
      CMXTA_DBG_ERR((_cmxtap,                                     \
        "KWAC_FORM_PDCP_AM_12BIT_HDR Failed: resource unavailble \n"));\
      RETVALUE(CMXTA_ERR_RSRC);                                   \
   }                                                              \
}

#define KWAC_FORM_PDCP_AM_12BIT_INV_HDR(_sdu, _sn, _mBuf)         \
{                                                                 \
   _sdu[1] = (U16)_sn;                                             \
   _sdu[0] = (U16)_sn>>8;                                          \
   _sdu[0] |= 0x70;                                               \
   /* put flat buffer into mBuf */                                \
   if (SAddPreMsgMult((Data *)_sdu, 1, *_mBuf) != ROK)            \
   {                                                              \
      CMXTA_DBG_ERR((_cmxtap,                                     \
        "KWAC_FORM_PDCP_AM_7BIT_HDR Failed: resource unavailble \n"));\
      RETVALUE(CMXTA_ERR_RSRC);                                   \
   }                                                              \
}

#define KWAC_FORM_PDCP_AM_INV_DRB_HDR(_sdu, _sn, _mBuf)         \
{                                                                 \
   _sdu[0] = (U16)_sn;                                             \
   _sdu[1] = (U16)_sn>>8;                                          \
   _sdu[1] |= 0xF0;                                               \
   /* put flat buffer into mBuf */                                \
   if (SAddPreMsgMult((Data *)_sdu, 2, *_mBuf) != ROK)            \
   {                                                              \
      CMXTA_DBG_ERR((_cmxtap,                                     \
        "KWAC_FORM_PDCP_AM_7BIT_HDR Failed: resource unavailble \n"));\
      RETVALUE(CMXTA_ERR_RSRC);                                   \
   }                                                              \
}

#define KWAC_FORM_PDCP_AM_INV_SRB_HDR(_sdu, _sn, _mBuf)                 \
{                                                                       \
   _sdu[0] = (U16)_sn;                                                  \
   _sdu[0] |= 0xA0;                                                     \
   /* put flat buffer into mBuf */                                      \
   if (SAddPreMsg(_sdu[0], *_mBuf) != ROK)                              \
   {                                                                    \
      CMXTA_DBG_ERR((_cmxtap,                                           \
        "KWAC_FORM_PDCP_AM_7BIT_HDR Failed: resource unavailble \n"));  \
      RETVALUE(CMXTA_ERR_RSRC);                                         \
   }                                                                    \
}

#define PJ_CPJ_UTL_SETKEY_BITS(_dstKey, _srcKey, _idx)      \
{                                                           \
   if(_srcKey >= '0' && _srcKey <= '9')                     \
     _dstKey |= ((U8)(_srcKey - '0')) << (_idx % 2? 0: 4);  \
   else if(_srcKey >= 'a' && _srcKey <= 'f')                \
     _dstKey |= ((U8)(_srcKey - 'a') + 10) << (_idx % 2? 0: 4);  \
   else if(_srcKey >= 'A' && _srcKey <= 'F')                \
     _dstKey |= ((U8)(_srcKey - 'A') + 10) << (_idx % 2? 0: 4);  \
}
#endif /* KW_PDCP */

#define KWAC_XML_GET_VALLIST(_parseStr, _strName, _strTok, _dstArray,  _size)       \
{                                                                                   \
   Txt   *_token   =  NULLP;                                                        \
   U8    _i        =  0;                                                            \
   CMXTA_ZERO(_parseStr, sizeof(_parseStr));                                        \
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, _strName, _parseStr);    \
   _token =  strtok(_parseStr, _strTok);                                            \
   for(_i=0;_token != NULLP;(_token =  strtok(NULLP, _strTok)), _i++)               \
      _dstArray[_i]  =  (_size )atoi(_token);                                       \
}


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __KWAC_ACC_H__ */


  
/********************************************************************30**
         End of file:     kwac_acc.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:21 2014
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
/main/2      ---      gk   1. LTE RLC Release 2.1.
/main/3    kw005.201  rd   1. Changed the value for macro
                              "KWAC_MAX_CIRCQ_SIZE" to 1024 for 
                               accomodating TCs wrt RLC R9 upgradation.
*********************************************************************91*/

