


/**********************************************************************
 
    Name:   LTE MAC DLFS scheduler
 
    Type:   C include file
 
    Desc:   Defines required by DLFS scheduler
 
    File:   rg_sch_dlfs.h
 
    Sid:      rg_sch_dlfs.h@@/main/2 - Sat Jul 30 02:22:03 2011
 
    Prg:    sd
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000372       LTE-MAC
*
*/


#ifdef TFU_UPGRADE
#ifndef __RGDLFSH__
#define __RGDLFSH__

/* DLFS MACROs*/
#define RG_SCH_DLFS_DFLT_CQI 6
#define RG_SCH_DLFS_RETX_TRUE TRUE
#define RG_SCH_DLFS_RETX_FALSE FALSE
#define RG_SCH_DLFS_INVALID_CQI 16


/* DLFS Function MACROs */
#define RG_SCH_DLFS_GET_CELL(_cell) ((RgSchDlfsCellCb *)\
      ((RgSchCmnCell*)((_cell)->sc.sch))->dl.dlfsCell) 
#define RG_SCH_DLFS_GET_UE(_ue, _cell) ((RgSchDlfsUeCb *)((RgSchCmnUe *)((_ue->cellInfo[_ue->cellIdToCellIdxMap\
               [RG_SCH_CELLINDEX(_cell)]])->sch))->dl.dlfsUe)
#define RG_SCH_DLFS_GET_SF(_sf) (RgSchDlfsSf *)((_sf)->dlfsSf)
#define RG_SCH_DLFS_CW1_WEIGHT 40
#define RG_SCH_DLFS_CW0_WEIGHT (100 - RG_SCH_DLFS_CW1_WEIGHT)
#define RG_SCH_DLFS_CQI_TO_MODODR(_x, _y) do {\
   if (_x <= 6) *(_y) = 2; \
   else if (_x <= 9) *(_y) = 4; \
   else *(_y) = 6;\
} while(0)
#define RG_SCH_DLFS_MODODR_TO_RETX_MCS(_x, _y) do {\
   if (_x == 2) *(_y) = 29; \
   else if (_x == 4) *(_y) = 30; \
   else *(_y) = 31;\
} while(0)

#define RG_SCH_DLFS_GET_PRD_SBSIZE(_sbSize, _totDlBw)\
RG_SCH_DLFS_GET_LARGE_SBSIZE(_sbSize, _totDlBw)

#define RG_SCH_DLFS_GET_APRD_MODE30_SBSIZE(_sbSize, _totDlBw)\
RG_SCH_DLFS_GET_LARGE_SBSIZE(_sbSize, _totDlBw)

#define RG_SCH_DLFS_GET_APRD_MODE20_SBSIZE(_sbSize, _totDlBw)\
RG_SCH_DLFS_GET_SMALL_SBSIZE(_sbSize, _totDlBw)

#define RG_SCH_DLFS_GET_SMALL_SBSIZE(_sbSize, _totDlBw)\
{\
   if ((_totDlBw) > 63)\
   {\
      *(_sbSize) = 4;\
   }\
   else if ((_totDlBw) > 26)\
   {\
      *(_sbSize) = 3;\
   }\
   else if ((_totDlBw) > 10)\
   {\
      *(_sbSize) = 2;\
   }\
   else\
   {\
      if ((_totDlBw) > 7)\
      {\
         *(_sbSize) = 2;\
      }\
      else\
      {\
         *(_sbSize) = 0;\
      }\
   }\
}\

#define RG_SCH_DLFS_GET_LARGE_SBSIZE(_sbSize, _totDlBw)\
{\
   if ((_totDlBw) > 63)\
   {\
      *(_sbSize) = 8;\
   }\
   else if ((_totDlBw) > 26)\
   {\
      *(_sbSize) = 6;\
   }\
   else if ((_totDlBw) > 10)\
   {\
      *(_sbSize) = 4;\
   }\
   else\
   {\
      if ((_totDlBw) > 7)\
      {\
         *(_sbSize) = 4;\
      }\
      else\
      {\
         *(_sbSize) = 0;\
      }\
   }\
}\

#ifndef LTE_TDD
#define RG_SCH_DLFS_GET_PRDICITY_AND_OFFST(_idx, _prdicity, _offset)\
{\
   if ((_idx) <= 1)\
   {*(_prdicity) = 2; *(_offset) = (U8)(_idx); }\
   else if ((_idx) <= 6)\
   {*(_prdicity) = 5; *(_offset) = (U8)((_idx) - 2); }\
   else if ((_idx) <= 16)\
   {*(_prdicity) = 10; *(_offset) = (U8)((_idx) -  7);}\
   else if ((_idx) <= 36)\
   {*(_prdicity) = 20; *(_offset) = (U8)((_idx) - 17); }\
   else if ((_idx) <= 76)\
   {*(_prdicity) = 40; *(_offset) = (U8)((_idx) - 37); }\
   else if ((_idx) <= 156)\
   {*(_prdicity) = 80; *(_offset) = (U8)((_idx) - 77); }\
   else if ((_idx) <= 316)\
   {*(_prdicity) = 160; *(_offset) = (U8)((_idx) - 157); }\
   else if ((_idx) == 317)\
   {*(_prdicity) = 0; *(_offset) = 0; }\
   else if ((_idx) <= 349)\
   {*(_prdicity) = 32; *(_offset) = (U8)((_idx) - 318); }\
   else if ((_idx) <= 413)\
   {*(_prdicity) = 64; *(_offset) = (U8)((_idx) - 350); }\
   else if ((_idx) <= 541)\
   {*(_prdicity) = 128; *(_offset) = (U8)((_idx) - 414); }\
   else if ((_idx) <=1023)\
   {*(_prdicity) = 0; *(_offset) = 0;}\
}
#else
#define RG_SCH_DLFS_GET_PRDICITY_AND_OFFST(_idx, _prdicity, _offset)\
{\
   if ((_idx) == 1)\
   {*(_prdicity) = 1; *(_offset) = (U8)(_idx); }\
   else if ((_idx) <= 5)\
   {*(_prdicity) = 5; *(_offset) = (U8)((_idx) - 1); }\
   else if ((_idx) <= 15)\
   {*(_prdicity) = 10; *(_offset) = (U8)((_idx) - 6);}\
   else if ((_idx) <= 35)\
   {*(_prdicity) = 20; *(_offset) = (U8)((_idx) - 16);}\
   else if ((_idx) <= 75)\
   {*(_prdicity) = 40; *(_offset) = (U8)((_idx) - 36);}\
   else if ((_idx) <= 155)\
   {*(_prdicity) = 80; *(_offset) = (U8)((_idx) - 76);}\
   else if ((_idx) <= 315)\
   {*(_prdicity) = 160; *(_offset) = (U8)((_idx) - 156);}\
   else if ((_idx) <=1023)\
   {*(_prdicity) = 0; *(_offset) = 0;}\
}
#endif /* ifndef LTE_TDD */

#define	RG_SCH_DLFS_WEIGH_AVG_SBCQI(_sbCqi,_sbCqi1) { \
  if (_sbCqi1 > 0) \
  _sbCqi = ((_sbCqi * RG_SCH_DLFS_CW0_WEIGHT) + (_sbCqi1 * (RG_SCH_DLFS_CW1_WEIGHT)))/100;	\
}
/* DLFS Error MACROs */
#define RGSCHERR_DLFS_MEMERR 0

#endif /* __RGDLFSH__ */
#endif


/**********************************************************************
         End of file:     rg_sch_dlfs.h@@/main/2 - Sat Jul 30 02:22:03 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      $      ---      sd  1. LTE MAC 2.1 release
/main/2      ---         gvj 1. Updated for LTE MAC Rel 3.1
$SID$        ---     rt      1. LTE MAC 4.1 Release.                           
*********************************************************************91*/
