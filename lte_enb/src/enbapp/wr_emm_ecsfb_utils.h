
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_emm_ecsfb_utils.h

     Sid:      wr_emm_ecsfb_utils.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:09 2014

     Prg:      Sriky 

*********************************************************************21*/



#ifndef __WR_EMM_ECSFB_UTILS_H__
#define __WR_EMM_ECSFB_UTILS_H__

#include "wr_cmn.h"
#include "wr_emm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WR_MSEC_DIFF                   315964800000
#define WR_EMM_INVALID_RAT_PRIORITY    0xFFFF

/* Start Fix for SIB8 */
#define WR_FILL_BIT_STR_VAR_LEN(_ptr, _len, _val, _pdu) {\
   S16      i;                                           \
   U8     _byteCnt = 0;                                  \
   U8     _reminder = 0;                          \
   U32    _val2= _val; \
   _ptr.pres = PRSNT_NODEF;                            \
   _ptr.len =  _len;                                   \
   if((_len % 8) > 0)                                     \
   {                                                    \
      _byteCnt = (_len/8)+1;                             \
   }                                                     \
   else                                                  \
   {                                                     \
      _byteCnt = _len/8;                                 \
   }                                                     \
   _reminder = ((_byteCnt * 8) - _len);                  \
   _val2 = _val2 << _reminder;                             \
   WR_GET_MEM(_pdu, _byteCnt * sizeof(U8), (Ptr *) & (_ptr.val));  \
                                                         \
   if(_ptr.val != NULLP)                                 \
   {                                                     \
      for(i = _byteCnt - 1; i >= 0; i--)                 \
      {                                                  \
         _ptr.val[i] = (U8)(0x000000FF & _val2);          \
         _val2 = _val2 >> 8;                               \
      }                                                  \
   }                                                     \
}
#define WR_FILL_BIT_STR_LEN15(_ptr, _len, _val, _pdu) {\
   S16      i;                                    \
   U16     _tmpLen;                             \
   U32    _val2= _val; \
   _ptr.pres = PRSNT_NODEF;                     \
   _ptr.len =  _len;                            \
   _tmpLen = _len;                              \
   if((_len%8) > 0)                              \
   {                                             \
      _tmpLen = (_len/8)+1;                         \
   }                                             \
   else                                          \
   {                                             \
      _tmpLen = _len/8;                             \
   }                                             \
   WR_GET_MEM(_pdu, _tmpLen * sizeof(U8), (Ptr *)&(_ptr.val));  \
                      \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = _tmpLen - 1; i >= 0; i--)                  \
      {                                          \
         _ptr.val[i] = (U8)(0x000000ff & _val2);                  \
         _val2 = _val2>>7;\
      }                                          \
   }                                             \
}
 
#define WR_FILL_BIT_STR_LEN12(_ptr, _len, _val, _pdu) {\
   S16      i;                                    \
   U16     _tmpLen;                             \
   U32    _val2= _val; \
   _ptr.pres = PRSNT_NODEF;                     \
   _ptr.len =  _len;                            \
   _tmpLen = _len;                              \
   if((_len%8) > 0)                              \
   {                                             \
      _tmpLen = (_len/8)+1;                         \
   }                                             \
   else                                          \
   {                                             \
      _tmpLen = _len/8;                             \
   }                                             \
   WR_GET_MEM(_pdu, _tmpLen * sizeof(U8), (Ptr *)&(_ptr.val));  \
                      \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = _tmpLen - 1; i >= 0; i--)                  \
      {                                          \
         _ptr.val[i] = (U8)(0x000000ff & _val2);                  \
         _val2 = _val2>>4;\
      }                                          \
   }                                             \
}
#define WR_EMM_GET_CEIL_POS_VALUE(X) ((X-(U64)(X)) > 0 ? (U64)(X+1) : (U64)(X))
#define WR_EMM_GET_CEIL_NEG_VALUE(X) ((U64)(X))
#define WR_EMM_GET_CEILING_VALUE(X) (((X) > 0) ? WR_EMM_GET_CEIL_POS_VALUE(X) : WR_EMM_GET_CEIL_NEG_VALUE(X))

EXTERN S16 wrEmmGetRatPriority(WrPlmnId *plmn, WrRatPriorityList *ratPriority, WrCellId cellId);
EXTERN Bool wrEmmIsDualRxSupported(WrCellId cellId);
EXTERN S16 wrEmmIsCsfbOrEcsfbMeasSup
(
WrCellId                    cellId, 
Bool                        csfbOrEcsfbSup,
U8                          *csfbOreCsfbSup
);
EXTERN Bool wrEmmIs1xcCdmaBandCfg(U32  bandClass, WrCellId cellId);
EXTERN S16 wrFillTknBStr64
(
TknStrBSXL                   *ie,
U16                          len,
U64                          val,
CmMemListCp                  *mem
);
EXTERN S16 wrEmmAnrGetCdma1xRttCell
(
   U8                     cellId,
   WrCdmaRttPilotLst      *cdmaRttPilotLst
);
EXTERN S16 wrEmmAnrGetCdma1xRttCellByPnOffset
(
   U8                     cellId,
   WrCdma1xRttPnOffset    *cdmaRttPnOffset,
   WrCdma1xRttPilotInfo   *cdmaPilotInfo
);
EXTERN Bool wrEmmIsDualRxTxSupported(WrCellId cellId);
EXTERN Bool wrEmmGetEcsfbAndDualRxTxSuppCfgs(WrCellId cellId);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_EMM_ECSFB_UTILS_H__ */


/********************************************************************30**

           End of file:     wr_emm_ecsfb_utils.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:09 2014

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
/main/1        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
