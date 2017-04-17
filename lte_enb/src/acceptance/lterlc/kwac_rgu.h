

/**********************************************************************
 
    Name:   LTE MAC layer
 
    Type:   C include file
 
    Desc:   Defines required by RGU interface of XTA LTE MAC
 
    File:   kwac_rgu.h
 
    Sid:      kwac_rgu.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:41 2014
 
    Prg:    sm 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000372       LTE MAC
*
*/

#ifndef __RGAC_RGU_H__
#define __RGAC_RGU_H__

#define KWAC_RGU_MAX      20
#define KWAC_RGU_TXTLEN   200
#define KWAC_RGU_DFLTRGN  kwCb.init.region 
#define KWAC_RGU_DFLTPOOL kwCb.init.pool

/* In the windows compilation strtok_r is not avaliable.
 * Define strtok_r as strtok
 */
#ifdef NS
#define strtok_r(str, delim, ptrptr)   strtok_s(str, delim, ptrptr)
#endif /* NS */

/****************************************************************************
 *                         RGU INTERFACE EVENTS
 ***************************************************************************/
#define KWAC_RGU_EVT_BND_REQ           EVTRGUBNDREQ
#define KWAC_RGU_EVT_UBND_REQ          EVTRGUUBNDREQ
#define KWAC_RGU_EVT_BND_CFM           EVTRGUBNDCFM
#define KWAC_RGU_EVT_CDAT_REQ          EVTRGUCDATREQ
#define KWAC_RGU_EVT_CDAT_IND          EVTRGUCDATIND
#define KWAC_RGU_EVT_DDAT_REQ          EVTRGUDDATREQ
#define KWAC_RGU_EVT_DDAT_IND          EVTRGUDDATIND
#define KWAC_RGU_EVT_CSTA_RSP          EVTRGUCSTARSP
#define KWAC_RGU_EVT_CSTA_IND          EVTRGUCSTAIND
#define KWAC_RGU_EVT_DSTA_RSP          EVTRGUDSTARSP
#define KWAC_RGU_EVT_DSTA_IND          EVTRGUDSTAIND
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#define KWAC_RGU_EVT_HQSTA_IND         EVTRGUHQSTAIND
#ifdef LTE_RLC_R9
#define KWAC_RGU_EVT_L2MULTHR_REQ      EVTRGUL2MULTHRPMEASREQ
#endif
#endif
#define KWAC_RGUDAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(KWAC_RGUDFLTRGN, KWAC_RGUDFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}

#define KWAC_UTL_RGU_CSTARSP_CQ_ISEMPTY(q)\
    (kwAcUtlRguCStaRspCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define KWAC_UTL_RGU_DSTARSP_CQ_ISEMPTY(q)\
    (kwAcUtlRguDStaRspCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define KWAC_UTL_RGU_DSTAIND_CQ_ISEMPTY(q)\
    (kwAcUtlRguDStaIndCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define KWAC_UTL_RGU_CDATREQ_CQ_ISEMPTY(q)\
    (kwAcUtlRguCDatReqCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define KWAC_UTL_RGU_DDATREQ_CQ_ISEMPTY(q)\
    (kwAcUtlRguDDatReqCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define KWAC_UTL_RGU_CDATIND_CQ_ISEMPTY(q)\
    (kwAcUtlRguCDatIndCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#define KWAC_UTL_RGU_DDATIND_CQ_ISEMPTY(q)\
    (kwAcUtlRguDDatIndCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#endif /* __KWAC_RGU_H__ */


/**********************************************************************
         End of file:     kwac_rgu.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:41 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm      1. Initial Release.
/main/2      ---     gk      1. LTE RLC Release 2.1.
/main/3   kw005.201  rd      1. Moved #define KWAC_RGU_EVT_HQSTA_IND within
                                LTE_L2_MEAS compile switch.
*********************************************************************91*/

