

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by PJU interface of XTA LTE RLC
 
    File:   kwac_pju.h
 
    Sid:      kwac_pju.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:37 2014
 
    Prg:    gk 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000371       LTE RLC
*
*/

#ifndef __KWAC_PJU_H__
#define __KWAC_PJU_H__

#ifdef KW_PDCP

#ifndef LCPJUIPJU
#define PTNHLIPJU
#define PTNXLIPJU
#endif

#define KWAC_PJU_DFLTRGN  kwCb.init.region 
#define KWAC_PJU_DFLTPOOL kwCb.init.pool
#define KWAC_PJU_MAX_FLAT_BUF_SIZE        5000

#define KWAC_PJU_FREE_BNDCFM(_staInd)          /* need to include actual free function*/
#define KWAC_PJU_FREE_CFGCFM(_staInd)          /* need to include actual free function*/

#define KWAC_PJU_DAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(KWAC_PJU_DFLTRGN, KWAC_PJU_DFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}

#define KWAC_UTL_PJU_DATREQ_CQ_ISEMPTY(q)\
   (kwAcUtlPjuDatReqCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define KWAC_UTL_PJU_DATCFM_CQ_ISEMPTY(q)\
   (kwAcUtlPjuDatCfmCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#endif /* KW_PDCP */
#endif /* __KWAC_PJU_H__ */


/**********************************************************************
         End of file:     kwac_pju.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:37 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   mn         1. LTERLC Release 2.1.
*********************************************************************91*/

