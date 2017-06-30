


/********************************************************************20**
  
        Name:     LTE RLC file 
    
        Type:     C include file
  
        Desc:     This file contain the hash definations for RLC 
 
        File:     kw.h

        Sid:      pj_ul.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:53 2015
  
        Prg:      na 
  
*********************************************************************21*/
/** @file kw.h
@brief RLC Hash definitions
*/

#ifndef __PJ_ULH__
#define __PJ_ULH__
#define PJ_MAX_NUM_OF_BITS 4096

#define PJ_DBM_FETCH_UL_RBCB(_rbId, _rbType, _ueCb, _rbCb)     \
{                                                           \
   _rbCb = (_rbType==CM_LTE_SRB)?_ueCb->srbCb[_rbId]:_ueCb->drbCb[_rbId];\
}

/* HO_FIX: Changed the success value to ROK as RRC expects
           ROK or RFAILED */
#define  PJ_FILL_UL_SDU_CFM_INFO(_cb,_cfmInfo,_tempDlStaInfo,_ueCb)                    \
{                                                                 \
   U8 _rbCnt;                                                     \
   U8 _numRb = 0;                                                 \
   PjUlHoCfmInfo *_hoCfmInfo;                                       \
   CpjSduStaInfo  *_staInfo;                                      \
   Bool _rbPres;                                                  \
   _cfmInfo->ueId    = _ueCb->key.ueId;                           \
   _cfmInfo->cellId  = _ueCb->key.cellId;                         \
   _cfmInfo->transId = _ueCb->hoInfo->transId;                    \
   for(_rbCnt = 0; _rbCnt < PJ_MAX_DRB_PER_UE && _numRb < CPJ_MAX_DRB; _rbCnt++)          \
   {                                                              \
       _rbPres     = FALSE;                                       \
      _hoCfmInfo   =  &_ueCb->hoInfo->hoCfmInfo[_rbCnt];          \
      _staInfo     =  &_cfmInfo->sduStaInfo[_numRb];              \
      if(_hoCfmInfo->pres == TRUE)                                \
      {                                                           \
      _rbPres = TRUE;                                             \
      _staInfo->rbId  =  _hoCfmInfo->rbId;                        \
      _staInfo->dir   |= _hoCfmInfo->dir;                         \
      _staInfo->ulSduStaInfo.numBits   =  _hoCfmInfo->numBits; \
      _staInfo->ulSduStaInfo.ulBitMap  =  _hoCfmInfo->ulBitMap;\
      _staInfo->ulSduStaInfo.count     =  _hoCfmInfo->count;   \
      _hoCfmInfo->ulBitMap          =  NULLP;                  \
      }                                                        \
      if(tempDlStaInfo[_rbCnt].dlSduStaInfo.hoPres == TRUE)  \
      {                                                                \
       _rbPres = TRUE;                                                 \
       _staInfo->rbId  =  _tempDlStaInfo[_rbCnt].rbId;        \
       _staInfo->dir   |= _tempDlStaInfo[_rbCnt].dir;                         \
       _staInfo->dlSduStaInfo.count = _tempDlStaInfo[_rbCnt].dlSduStaInfo.count; \
      }                                                        \
      if(_rbPres != TRUE)                                      \
      {                                                        \
         continue;                                             \
      }                                                        \
      else                                                     \
      {                                                        \
        _numRb++;                                              \
      }                                                        \
  }                                                              \
   _cfmInfo->numRb = _numRb;                                   \
   _cfmInfo->status = ROK;                                     \
   _cfmInfo->reason = CPJ_CFG_REAS_NONE;                          \
   PJ_FREE(_cb,_ueCb->hoInfo->hoCfmInfo,                          \
              (PJ_MAX_DRB_PER_UE * sizeof(PjUlHoCfmInfo)));       \
   PJ_FREE(_cb,_ueCb->hoInfo, sizeof(PjUlHoInfo));                \
}

#define PJ_DBM_DELETE_UL_RBCB(_cb, _rbCb)                           \
{                                                           \
   /* Free memory for rbCb */                               \
   PJ_FREE(_cb, _rbCb, sizeof(PjUlRbCb));                            \
   PJ_LMM_RB_STS_DEC(_cb);                                     \
}

#endif /* __PJH__ */
  
/********************************************************************30**
  
         End of file:     pj_ul.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:53 2015
  
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
