

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by PJU interface of XTA LTE PDCP
 
    File:   pjac_pju.h
 
    Sid:      pjac_pju.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:05 2015
 
    Prg:    Adarsh 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000371       LTE PDCP
*
*/

#ifndef __PJAC_PJU_H__
#define __PJAC_PJU_H__

/* Venki */
#ifndef KW_PDCP

#ifndef LCPJUIPJU
#define PTNHLIPJU
#define PTNXLIPJU
#endif

#define PJAC_PJU_DFLTRGN  kwCb.init.region 
#define PJAC_PJU_DFLTPOOL kwCb.init.pool
#define PJAC_PJU_MAX_FLAT_BUF_SIZE        5000

#define PJAC_PJU_FREE_BNDCFM(_staInd)          /* need to include actual free function*/
#define PJAC_PJU_FREE_CFGCFM(_staInd)          /* need to include actual free function*/

#define PJAC_PJU_DAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(PJAC_PJU_DFLTRGN, PJAC_PJU_DFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}

#define PJAC_UTL_PJU_DATREQ_CQ_ISEMPTY(q)\
   (pjAcUtlPjuDatReqCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define PJAC_UTL_PJU_DATCFM_CQ_ISEMPTY(q)\
   (pjAcUtlPjuDatCfmCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#endif /* KW_PDCP */
#endif /* __PJAC_PJU_H__ */


/**********************************************************************
         End of file:     pjac_pju.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:05 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vb       1. LTE PDCP Release 2.1.
*********************************************************************91*/
