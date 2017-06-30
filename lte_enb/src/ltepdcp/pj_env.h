


/********************************************************************20**
  
        Name:     LTE PDCP file 
    
        Type:     H include file
  
        Desc:     This file contain the hash definations for RLC 
 
        File:     kw.h

        Sid:      pj_env_t2k.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:46 2015
  
        Prg:      na 
  
*********************************************************************21*/
/** @file pj_env_t2k.h
@brief RLC Hash definitions
*/

#ifndef __PJENVT2KH__
#define __PJENVT2KH__

#define PJ_MAX_PDCP_INSTANCES            2 
#define PJ_FWD_MAX_SDU_CNT            1 

#define PJ_ALLOC_BUF(gCb,_buf)                                 \
{                                                          \
   if (SGetMsg(gCb->init.region, gCb->init.pool, (Buffer **)&_buf) != ROK) \
   {                                                       \
      (_buf) = NULLP;                                      \
   }                                                       \
}

#define PJ_CPY_MSG(_cb,_x, _y, _ret)                           \
   _ret =(SAddMsgRef((_x), PJ_GET_MEM_REGION(_cb), PJ_GET_MEM_POOL(_cb), (_y)))                                                                                         

#define PJ_SND_CFM(_cb,_pjRbCb, _txEnt, _cause)                \
{                                                          \
   PjuDatCfmInfo *_datCfm;                                 \
   CmLtePdcpId *_pdcpId;                                   \
   PjPjuSapCb  *_pjuSap;                                   \
   if (_pjRbCb->rbType == PJ_SRB)                          \
      _pjuSap   = &(_cb->u.dlCb->pjuSap[PJ_SRB_SAP]);                  \
   else                                                    \
      _pjuSap   = &(_cb->u.dlCb->pjuSap[PJ_DRB_SAP]);                  \
                                                           \
   PJ_ALLOC(_cb, _datCfm, sizeof(PjuDatCfmInfo));              \
   PJ_ALLOC(_cb,_pdcpId, sizeof(CmLtePdcpId));                \
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
   pjDbmDelTxEnt(_cb, &(pjRbCb->dlCb.txBuf), _txEnt->count);   \
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
#endif /* __PJENVT2KH__ */
/********************************************************************30**
  
         End of file:     pj_env_t2k.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:46 2015
  
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
*********************************************************************91*/
