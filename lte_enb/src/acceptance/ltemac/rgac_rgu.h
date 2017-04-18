


/**********************************************************************
 
    Name:   LTE MAC layer
 
    Type:   C include file
 
    Desc:   Defines required by RGU interface of XTA LTE MAC
 
    File:   rgac_rgu.h
 
    Sid:      rgac_rgu.h@@/main/3 - Sat Jul 30 02:21:04 2011
 
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

#ifndef __RGAC_RGUH__
#define __RGAC_RGUH__

#define RGAC_RGU_USERENT    ENTKW
#define RGAC_RGU_PROVENT    ENTRG
#define RGAC_RGU_USERINST   CMXTA_INST_ID
#define RGAC_RGU_PROVINST   CMXTA_INST_ID
#define RGAC_RGU_SRCPROC    CMXTA_PROC_ID 
#define RGAC_RGU_DSTPROC    CMXTA_PROC_ID
#define RGAC_RGU_MATCHPROC  FALSE


#define RGAC_RGU_EVTBNDCFM   EVTRGUBNDCFM
#define RGAC_RGU_EVTCSTAIND  EVTRGUCSTAIND
#define RGAC_RGU_EVTDSTAIND  EVTRGUDSTAIND
#define RGAC_RGU_EVTCDATIND  EVTRGUCDATIND
#define RGAC_RGU_EVTDDATIND  EVTRGUDDATIND
#define RGAC_RGU_EVTCDATREQ  EVTRGUCDATREQ
#define RGAC_RGU_EVTDDATREQ  EVTRGUDDATREQ
#define RGAC_RGU_EVTCSTARSP  EVTRGUCSTARSP
#define RGAC_RGU_EVTDSTARSP  EVTRGUDSTARSP
#define RGAC_RGU_EVTBNDREQ   EVTRGUBNDREQ
#define RGAC_RGU_EVTUBNDREQ  EVTRGUUBNDREQ
#ifdef LTE_L2_MEAS
#define RGAC_RGU_EVTHQSTAIND  EVTRGUHQSTAIND
#ifdef LTEMAC_R9
#define RGAC_RGU_EVTULTHRMEASREQ EVTRGUL2MULTHRPMEASREQ
#endif
#endif /* LTE_L2_MEAS */

#define RGAC_RGU_BCCH CM_LTE_LCH_BCCH 
#define RGAC_RGU_PCCH CM_LTE_LCH_PCCH 
#define RGAC_RGU_CCCH CM_LTE_LCH_CCCH 

#define RGAC_RGU_MAX      20
#define RGAC_RGU_TXTLEN   200
#define RGAC_RGU_DFLTRGN  cmXtaCb.init.region
#define RGAC_RGU_DFLTPOOL cmXtaCb.init.pool

#define RGAC_RGU_BNDREQ(_pst, _suId, _spId)     KwLiRguBndReq(_pst, _suId, _spId);
#define RGAC_RGU_UBNDREQ(_pst, _spId, _reason)  KwLiRguUbndReq(_pst, _spId, _reason);
#define RGAC_RGU_CDATREQ(_pst, _spId, _datReq)  KwLiRguCDatReq(_pst, _spId, _datReq);
#define RGAC_RGU_DDATREQ(_pst, _spId, _datReq)  KwLiRguDDatReq(_pst, _spId, _datReq);
#define RGAC_RGU_CSTARSP(_pst, _spId, _staRsp)  KwLiRguCStaRsp(_pst, _spId, _staRsp);
#define RGAC_RGU_DSTARSP(_pst, _spId, _staRsp)  KwLiRguDStaRsp(_pst, _spId, _staRsp);
#define RGAC_RGU_FREE_CSTAIND(_staInd)          { SPutSBuf(0, 0, (Data *)_staInd, sizeof(RguCStaIndInfo)); } 
#define RGAC_RGU_FREE_DSTAIND(_staInd)          { SPutSBuf(0, 0, (Data *)_staInd, sizeof(RguDStaIndInfo)); }
#define RGAC_RGU_FREE_CDATIND(_datInd)          { SPutSBuf(0, 0, (Data *)_datInd, sizeof(RguCDatIndInfo)); }
#define RGAC_RGU_FREE_DDATIND(_datInd)          { SPutSBuf(0, 0, (Data *)_datInd, sizeof(RguDDatIndInfo)); }
#define RGAC_RGU_FREE_HFLIND(_hflInd)           { SPutSBuf(0, 0, (Data *)_hflInd, sizeof(RguHarqFailIndInfo)); }
#ifdef LTE_L2_MEAS
#define RGAC_RGU_FREE_HQSTAIND(_staInd)         { SPutSBuf(0, 0, (Data *)_staInd, sizeof(RguHarqStatusInd)); }
#ifdef LTEMAC_R9
#define RGAC_RGU_ULTHRPMEASREQ(_pst, _spId, _measReq)  KwLiRguL2MUlThrpMeasReq(_pst, _spId, _measReq);
#endif
#endif
#define RGAC_RGU_DAT_GETBUF(_buf, _bufSize) \
{\
   /* Updated from 10000 to 20000. Because in 2.2 array size if 20000 */\
   static U8 str[20000];\
   cmMemset(str, 0, 20000);\
   if (SGetMsg(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, &(_buf)) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, (MsgLen)(_bufSize), (_buf));\
}

#ifdef NS
#define strtok_r(str, delimit , part) strtok_s(str, delimit, part)
#endif   

#endif /* __RGAC_RGUH__ */


/**********************************************************************
         End of file:     rgac_rgu.h@@/main/3 - Sat Jul 30 02:21:04 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm            1. Initial Release.
/main/2      ---     sm            1. LTE MAC 2.1 release
           rg007.201   ap  1. Changed Aray size in macro RGAC_RGU_DAT_GETBUF
/main/3      ---        dvasisht          1. Updated for LTE MAC Release 3.1
$SID$        ---       rt          1. LTE MAC 4.1 release
*********************************************************************91*/
