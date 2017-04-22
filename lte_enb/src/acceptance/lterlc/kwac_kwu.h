

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by KWU interface of XTA LTE RLC
 
    File:   kwac_kwu.h
 
    Sid:      kwac_kwu.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:26 2014
 
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

#ifndef __KWAC_KWU_H__
#define __KWAC_KWU_H__

/*Pradeep - changed region and pool to 0*/
#define KWAC_KWU_DFLTRGN  0 
#define KWAC_KWU_DFLTPOOL 0
/*
#define KWAC_KWU_DFLTRGN  kwCb.init.region 
#define KWAC_KWU_DFLTPOOL kwCb.init.pool
*/

#define KWAC_KWU_MAX_FLAT_BUF_SIZE        5000

#define KWAC_KWU_FREE_BNDCFM(_staInd)          /* need to include actual free function*/
#define KWAC_KWU_FREE_CFGCFM(_staInd)          /* need to include actual free function*/

#define KWAC_KWU_DAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(KWAC_KWU_DFLTRGN, KWAC_KWU_DFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}

#define KWAC_UTL_KWU_DATREQ_CQ_ISEMPTY(q)\
   (kwAcUtlKwuDatReqCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define KWAC_UTL_KWU_DATCFM_CQ_ISEMPTY(q)\
   (kwAcUtlKwuDatCfmCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#endif /* __KWAC_KWU_H__ */


/**********************************************************************
         End of file:     kwac_kwu.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:26 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     gk            1. Initial Release.
/main/2      ---     gk            1. LTE RLC Release 2.1.
*********************************************************************91*/

