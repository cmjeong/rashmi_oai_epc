

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by KWU interface of XTA LTE PDCP
 
    File:   pjac_kwu.h
 
    Sid:      pjac_kwu.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:50 2015
 
    Prg:    av 
 
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

#ifndef __PJAC_KWU_H__
#define __PJAC_KWU_H__

/* In the windows compilation strtok_r is not avaliable.
 * Define strtok_r as strtok
 */
#ifdef NS
#define strtok_r(str, delim, ptrptr)   strtok_s(str, delim, ptrptr)
#endif /* NS */

#define PJAC_KWU_MAX      20
#define PJAC_KWU_TXTLEN   200
#define PJAC_KWU_DFLTRGN  0
#define PJAC_KWU_DFLTPOOL 0

#define PJAC_KWU_MAX_FLAT_BUF_SIZE        5000

#define PJAC_KWU_FREE_BNDCFM(_staInd)          /* need to include actual free function*/
#define PJAC_KWU_FREE_CFGCFM(_staInd)          /* need to include actual free function*/

#define PJAC_KWU_DAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(PJAC_KWU_DFLTRGN, PJAC_KWU_DFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}

#define PJAC_UTL_KWU_DATREQ_CQ_ISEMPTY(q)\
   (pjAcUtlKwuDatReqCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define PJAC_UTL_KWU_DATCFM_CQ_ISEMPTY(q)\
   (pjAcUtlKwuDatCfmCircQAddOne(q->rear) == q->front)?TRUE:FALSE

                                                                                                                                                                        
/****************************************************************************
 *                         KWU INTERFACE EVENTS
 ***************************************************************************/
#define PJAC_KWU_EVT_BND_REQ        KWU_EVT_BND_REQ
#define PJAC_KWU_EVT_UBND_REQ       KWU_EVT_UBND_REQ
#define PJAC_KWU_EVT_BND_CFM        KWU_EVT_BND_CFM
#define PJAC_KWU_EVT_DAT_REQ        KWU_EVT_DAT_REQ
#define PJAC_KWU_EVT_DAT_IND        KWU_EVT_DAT_IND
#define PJAC_KWU_EVT_DAT_CFM        KWU_EVT_DAT_CFM
#define PJAC_KWU_EVT_DISC_SDU_REQ   KWU_EVT_DISC_SDU_REQ
#define PJAC_KWU_EVT_STA_IND        KWU_EVT_STA_IND
#define PJAC_KWU_EVT_REEST_CMP_IND  KWU_EVT_REEST_CMP_IND


#define PJAC_KWUDAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(PJAC_KWUDFLTRGN, PJAC_KWUDFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}
                                                                                                                                                                        
#define PJAC_UTL_KWU_CSTARSP_CQ_ISEMPTY(q)\
    (pjAcUtlRguCStaRspCircQAddOne(q->rear) == q->front)?TRUE:FALSE
                                                                                                                                                                        
#define PJAC_UTL_KWU_DSTARSP_CQ_ISEMPTY(q)\
    (pjAcUtlRguDStaRspCircQAddOne(q->rear) == q->front)?TRUE:FALSE
                                                                                                                                                                        
#define PJAC_UTL_KWU_DSTAIND_CQ_ISEMPTY(q)\
    (pjAcUtlRguDStaIndCircQAddOne(q->rear) == q->front)?TRUE:FALSE
                                                                                                                                                                        
#define PJAC_UTL_KWU_CDATREQ_CQ_ISEMPTY(q)\
    (pjAcUtlRguCDatReqCircQAddOne(q->rear) == q->front)?TRUE:FALSE
                                                                                                                                                                        
#define PJAC_UTL_KWU_DDATREQ_CQ_ISEMPTY(q)\
    (pjAcUtlRguDDatReqCircQAddOne(q->rear) == q->front)?TRUE:FALSE
                                                                                                                                                                        
#define PJAC_UTL_KWU_CDATIND_CQ_ISEMPTY(q)\
    (pjAcUtlRguCDatIndCircQAddOne(q->rear) == q->front)?TRUE:FALSE
                                                                                                                                                                        
#define PJAC_UTL_KWU_DDATIND_CQ_ISEMPTY(q)\
    (pjAcUtlRguDDatIndCircQAddOne(q->rear) == q->front)?TRUE:FALSE


#endif /* __PJAC_KWU_H__ */


/**********************************************************************
         End of file:     pjac_kwu.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:50 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      av            1.  LTE PDCP Initial Release 2.1
*********************************************************************91*/
