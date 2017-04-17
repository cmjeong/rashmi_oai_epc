

/**********************************************************************
 
    Name:   LTE CL Layer 
 
    Type:   C include file
 
    Desc:   Defines required by LTE-CL
 
    File:   lys.h
 
    Sid:      lys.h@@/main/1 - Sun Mar 28 18:40:12 2010
 
    Prg:    pk
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*                   LTE-CL 
*
*/
 
#ifndef __LYS_H__
#define __LYS_H__

#define EVTLYSCFGREQ       0      /* Config request */
#define EVTLYSCFGCFM       1      /* Config Confirm */
#define EVTLYSCNTRLREQ     2      /* Control Request */
#define EVTLYSCNTRLCFM     3      /* Control Confirm */
#define EVTLYSSTSREQ       4      /* Statistics Request */
#define EVTLYSSTSCFM       5      /* Statistics Confirm */
#define EVTLYSSSTAREQ      6      /* Solicited Status Request */
#define EVTLYSSSTACFM      7      /* Solicited Status Confirm */
#define EVTLYSUSTAIND      8      /* Unsolicite Status Indication */
#define EVTLYSTRCIND       9      /* Trace Indication */

#define LYS_PT_NUM_SIZE    8

#define LYS_NOT_CFG        0      /* Sap not configured */
#define LYS_UNBND          1      /* Unbound Sap State */
#define LYS_BND            2      /* Bound Sap State */
#define LYS_WAIT_BNDCFM    3      /* Await Bind cofirm state */

#define LYS_PHY_STATE_IDLE 0
#define LYS_PHY_STATE_CFG  1
#define LYS_PHY_STATE_RUN  2

/* Unsolicited status indication events */
/* TFU interface SAP bound with MAC */
#define LYS_EVENT_TFUSAP_ENB      (LCM_EVENT_LYR_SPECIFIC + 0)    
/* CTF interface SAP bound with RRM */
#define LYS_EVENT_CTFSAP_ENB      (LCM_EVENT_LYR_SPECIFIC + 1)  

#define LYS_USTA_DGNVAL_MEM      1
#define LYS_USTA_DGNVAL_SAP      2
#define LYS_USTA_DGNVAL_SFN_SF   3

/* TfuSap need to move to gen.h. This may be removed later */
#define STTFUSAP         STGEN + 4
#define STCTFSAP         STGEN + 2
#define STL1PHY          STGEN + 3

#define SASTOPL1                 30

/* pack unpack error code */
#define ELYSXXX                  0
#define ERRLYS                   0

#endif /* __LYS_H__ */

/**********************************************************************
         End of file:     lys.h@@/main/1 - Sun Mar 28 18:40:12 2010
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      pk  1. Initial Release
*********************************************************************91*/
