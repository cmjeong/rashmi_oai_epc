
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_emm.h

     Sid:      wr_emm_s1_flex.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:56:10 2015

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_EMM_S1_FLEX_H__
#define __WR_EMM_S1_FLEX_H__ 

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _wrGuGrupCbList
{
   CmHashListEnt guGrupHashEnt;
   WrGuGrpIdLst  grupId;
   U8       guGrupIdArr[8];
  /* This is the list of MMECBs supported by particular GUMMEI.*/
   CmLListCp mmeList;
}WrGuGrupCbList; 

#define WR_UMM_MAX_MME_CB_LIST 100
#define CB_KEY_LEN 9
#define GU_GRUP_KEY_LEN 8

typedef struct _wrGummeiMmeInfo
{
   CmLList                   lnk;
   Bool                      isLoaded;
   WrMmeCb                   *mmePtr;
}WrGummeiMmeInfo;
 /** This structure contains
 - mmeIdList list of MMECbs supported by GUMMEI gummeiId used for RRC procedure with GUMMEI present in it.
 */
typedef struct _wrGummeiCbList
{
   CmHashListEnt gummeiHashEnt;
   U8 gummeiId[CB_KEY_LEN];
  /* This is the list of MMECBs supported by particular GUMMEI.*/
   CmLListCp mmeIdList;
}WrGummeicbList;

typedef struct  _wrGuGrupMmeInfo
{
   CmLList                   lnk;
   WrMmeCb                   *mmePtr;
}WrGuGrupMmeInfo; 


 #define WR_EMM_GET_GUGRUP_ARR(_grupId, _grupArr){\
    _grupArr[0]= (_grupId.mmeGrpId & 0xFF); \
    _grupArr[1]= ((_grupId.mmeGrpId >> 8) & 0xFF); \
    _grupArr[2]= _grupId.plmnId.mcc[0]; \
    _grupArr[3]= _grupId.plmnId.mcc[1]; \
    _grupArr[4]= _grupId.plmnId.mcc[2]; \
    _grupArr[5]= _grupId.plmnId.mnc[0]; \
    _grupArr[6]= _grupId.plmnId.mnc[1]; \
    if(_grupId.plmnId.numMncDigits == 3)  \
    _grupArr[7]= _grupId.plmnId.mnc[2];  \
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__WR_EMM_S1_FLEX_H__  */


