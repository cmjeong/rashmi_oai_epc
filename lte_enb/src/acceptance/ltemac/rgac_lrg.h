


/**********************************************************************
 
    Name:   LTE MAC layer
 
    Type:   C include file
 
    Desc:   Defines required by LRG interface of XTA LTE MAC
 
    File:   rgac_lrg.h
 
    Sid:      rgac_lrg.h@@/main/3 - Sat Jul 30 02:20:56 2011
 
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

#ifndef __RGAC_LRGH__
#define __RGAC_LRGH__

#define RGAC_LRG_USERENT    ENTSM
#define RGAC_LRG_PROVENT    ENTRG
#define RGAC_LRG_PHYENT     ENTTF 
#define RGAC_LRG_RLCENT     ENTKW 
#define RGAC_LRG_RRCENT     ENTNH 
#define RGAC_LRG_RGRENT     ENTNX 
#define RGAC_LRG_RGMENT     ENTRM
#define RGAC_LRG_USERINST   CMXTA_INST_ID
#define RGAC_LRG_PROVINST   CMXTA_INST_ID
#define RGAC_LRG_PHYINST    CMXTA_INST_ID 
#define RGAC_LRG_RGUINST    CMXTA_INST_ID 
#define RGAC_LRG_CRGINST    CMXTA_INST_ID 
#define RGAC_LRG_RGRINST    CMXTA_INST_ID 
#define RGAC_LRG_RGMINST    CMXTA_INST_ID 
#define RGAC_LRG_SRCPROC    CMXTA_PROC_ID 
#define RGAC_LRG_DSTPROC    CMXTA_PROC_ID
#define RGAC_LRG_MATCHPROC  FALSE

#define RGAC_LRG_ELEMGENCFG       STGEN 
#define RGAC_LRG_ELEMTFUSAPCFG    STTFUSAP 
#define RGAC_LRG_ELEMRGUSAPCFG    STRGUSAP 
#define RGAC_LRG_ELEMCRGSAPCFG    STCRGSAP 
#define RGAC_LRG_ELEMRGRSAPCFG    STRGRSAP 
#define RGAC_LRG_ELEMSCHINSCFG    STSCHINST 
#define RGAC_LRG_ELEMRGMSAPCFG    STRGMSAP 
#define RGAC_LRG_TFUSAPINST    1 
#define RGAC_LRG_RGUSAPINST    2 
#define RGAC_LRG_CRGSAPINST    3 
#define RGAC_LRG_RGRSAPINST    4 
#define RGAC_LRG_RGMSAPINST    5
#define RGAC_LRG_RLCINST       0
#define RGAC_LRG_RRCINST       0
#define RGAC_LRG_RRMINST       0

#define RGAC_LRG_EVTCFGCFM       EVTLRGCFGCFM
#define RGAC_LRG_EVTCNTRLCFM     EVTLRGCNTRLCFM
#define RGAC_LRG_EVTSCHCNTRLCFM  EVTLRGSCHCNTRLCFM
#define RGAC_LRG_EVTSCHCFGCFM       EVTLRGSCHCFGCFM
#define RGAC_LRG_EVTSTSCFM       EVTLRGSTSCFM
#define RGAC_LRG_EVTSTACFM       EVTLRGSSTACFM
#define RGAC_LRG_EVTSTAIND       EVTLRGUSTAIND
#define RGAC_LRG_EVTSCHSTAIND    EVTLRGSCHSTAIND 
#define RGAC_LRG_EVTTRCIND       EVTLRGTRCIND
#ifdef LTE_L2_MEAS
#define RGAC_LRG_EVTL2MEASREQ    EVTLRGSCHL2MEASREQ 
#define RGAC_LRG_EVTL2MEASCFM    EVTLRGSCHL2MEASCFM 
#define RGAC_LRG_EVTL2MEASSTOPCFM    EVTLRGSCHL2MEASSTOPCFM 
#endif
#define RGAC_LRG_SCHCFGREQ(_pst, _mngmt)     SmMiLrgSchCfgReq(_pst, _mngmt);
#define RGAC_LRG_CFGREQ(_pst, _mngmt)        SmMiLrgCfgReq(_pst, _mngmt);
#define RGAC_LRG_CNTRLREQ(_pst, _mngmt)      SmMiLrgCntrlReq(_pst, _mngmt);
#define RGAC_LRG_SCHCNTRLREQ(_pst, _mngmt)   SmMiLrgSchCntrlReq(_pst, _mngmt);
#define RGAC_LRG_STSREQ(_pst, _mngmt)        SmMiLrgStsReq(_pst, _mngmt);
#define RGAC_LRG_STAREQ(_pst, _mngmt)        SmMiLrgStaReq(_pst, _mngmt);
#ifdef LTE_L2_MEAS
#define RGAC_LRG_SCHL2MEASREQ(_pst, _measInfo) SmMiLrgSchL2MeasReq(_pst, _measInfo);
#define RGAC_LRG_SCHL2SENDMEASREQ(_pst, _measInfo) SmMiLrgSchL2SendMeasReq(_pst, _measInfo);
#define RGAC_LRG_SCHL2STOPMEASREQ(_pst, _measInfo) SmMiLrgSchL2StopMeasReq(_pst, _measInfo);
#endif
#endif /* __RGAC_LRGH__ */


/**********************************************************************
         End of file:     rgac_lrg.h@@/main/3 - Sat Jul 30 02:20:56 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm            1. Initial Release.
/main/2      ---     sm            1. LTE MAC 2.1 release
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$      ---       rt    1. LTE MAC 4.1 release
*********************************************************************91*/
