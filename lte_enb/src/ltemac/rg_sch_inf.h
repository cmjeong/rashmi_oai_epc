

/**********************************************************************
     Name:    Scheduler interface - RG_SCH_INF

     Type:    C header file

     Desc:    Constants needed for interface

     File:    rg_sch_inf.h

     Sid:      rg_sch_inf.h@@/main/2 - Sat Jul 30 02:22:06 2011

     Prg:      

*********************************************************************21*/

#ifndef __GKSCH_H__ 
#define __GKSCH_H__

/* Operation type for Harq Rls Req */

#define RGINF_RLS_HQ_NO_ACTION 0x00
#define RGINF_RLS_HQ_SAVE_TB   0x01
#define RGINF_RLS_HQ_DEL_TB    0x02

#define RGINF_MAX_NUM_DED_LC         10
#define RGINF_MAX_TB_PER_UE          2
#define RGINF_MAX_NUM_UE_PER_TTI     1
#define RGINF_MAX_LCG_PER_UE   4
/* RRM_SP1_START */
#define RGINF_MAX_GBR_QCI_REPORTS  4
/* RRM_SP1_END */
#define RGINF_BCH_INFO   (1<<0)
#define RGINF_BCCH_INFO  (1<<1)
#define RGINF_PCCH_INFO  (1<<2) 
/* Event corresponding to each primitive at this interface */
/* SCH interface events values startes from 1 and max up to 49 because 50
   onwards is used between MAC-MAC interface*/
#define EVTINFCELLREGREQ          1
#define EVTINFSFALLOCREQ          2
#define EVTINFRLSHQREQ            3
#define EVTINFRLSRNTIREQ          4
#define EVTINFDEDBOUPDTREQ        5
#define EVTINFCMNBOUPDTREQ        6
#define EVTINFSFRECPIND           7
/* Added support for SPS*/
#ifdef LTEMAC_SPS
#define EVTINFSPSLCREG               8
#define EVTINFSPSLCDEREG             9
#define EVTINFSPSRELIND              10
#define EVTINFSPSRESET               18
#endif /* LTEMAC_SPS */

#ifdef LTE_L2_MEAS
#define EVTINFL2MEASREQ              11
#define EVTINFL2MEASCFM              12
/*Added for radisys oam*/
#define EVTINFL2MEASSENDREQ          14
#define EVTINFL2MEASSTOPREQ          15
#define EVTINFL2MEASSTOPCFM          16
#endif
/*Fix: Inform UE delete to scheduler*/
#define EVTINFUEDELIND               13

#define EVTINFLCGREG                 17

#ifdef LTE_ADV
#define EVTINFHQENTRESET             19
#endif

#define RGSCHINF_FREE_MSG(_buf)\
{\
   if (NULLP != (_buf)) \
   { \
      SPutMsg((_buf)); \
      _buf = NULLP; \
   } \
}
#endif /* __GKSCH_H__ */

/********************************************************************30**

         End of file:     rg_sch_inf.h@@/main/2 - Sat Jul 30 02:22:06 2011

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
/main/1      ---   rr 1. LTE MAC 2.1 release
        rg008.201 rsharon 1. Added support for SPS.
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1
$SID$        ---       rt    1. LTE MAC 4.1 Release.                           
*********************************************************************91*/

