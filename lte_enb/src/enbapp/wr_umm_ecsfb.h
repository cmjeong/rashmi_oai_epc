
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_csfb.h

     Sid:      wr_umm_ecsfb.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:28 2014

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_ECSFB_H__
#define __WR_UMM_ECSFB_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */


#define WR_UMM_ECSFB_MAX_NUM_RETX           3
#define WR_UMM_MAX_PILOT_LIST               8
#define WR_UMM_MAX_CDMA_MEAS_RPT            24
#define MAX_CDMA2OOO_PILOT_LIST_MAX_LEN     15
#define WR_UMM_CHNL_RCD_LEN                 3
#define WR_UMM_CELL_ID_INFO                 2

typedef enum wrUmmEcsfbTransState
{
   WR_UMM_ECSFB_TRANS_REL,
   WR_UMM_ECSFB_TRANS_ERROR,
   /* Removed DAT CFM MSG and updated new
   WR_UMM_DAT_CFM_WAIT_HOPREP_REQ,
      */
   WR_UMM_WAIT_AFTER_HOPREP_REQ,/*RRC Rel10 Upgrade*/
   WR_UMM_DAT_CFM_WAIT_DL_CDMA_INFO,
   WR_UMM_DL_CDMA_RECV_HO_WAIT,
   WR_UMM_ECSFB_HO_EXEC,
   /*Removed WR_UMM_ECSFB_RRC_DAT_CFM_RECVD
	as it is not being used*/
   WR_UMM_ECSFB_RRC_DAT_CFM_RECVD_FOR_HOPREP_REQ,/*RRC Rel10 Upgrade*/
   WR_UMM_MEAS_CFGD
} WrUmmEcsfbTransState;

typedef enum ecsfbMsgTransId
{
   WR_UMM_ECSFB_HO_FROM_EUTRA_TRANSID = 1,
   WR_UMM_ECSFB_DL_CDMA_INFO_TRANSID,
   WR_UMM_ECSFB_MOB_EUTRA_CMD_TRANSID
}EcsfbMsgTransId;

/** @brief This structure used to store CSFB Transaction Specific
 * information.
 *
 *  -  U8               recvMeasRptCnt   Total Measuremrent report configured
 *  -  CmTimer          csfbCfgTmr       Timer for CS Fallback
 *  -  TknU32            csFallBackInd   CSFallBack Indicator
 *  -  WrRegLai          regLai          LAI
 *  -  WrUmmCsfbCandCellInfo  candCellInfo   candidate Cell Information
 *  -  WrUmmMeasTransInfo   measTransCb     measurement transaction control block
 **/
typedef  struct wrummEcsfbTransCb
{
   WrUmmEcsfbTransState ecsfbState;
   U32                  cdmaType;
   Bool                 isConCurrHoHrpd;
   U32                  numOfDlTxCnt;
   WrUmmIncMsg          *s1DlCdmaTunnMsg; /* Store the S1 DL tunneling CDMA PDU in transCb */
   TknStrOSXL           *cdmaS1Pdu;
   TknStrOSXL           *encMobilityParamsInfo;
/* GA_3.0 */
   U8                   eCsfbMeasEnbFlag;
   WrUmmTimer           measRptTmr;
   WrUmmMeasTransInfo   measTransCb;
   U8                   recvMeasRptCnt;
   U8                   ratPriority;
   U8                   numOfPilotLst;
   WrCdmaRttPilotLst    *cdmaRttPilotLst[WR_UMM_MAX_CDMA_MEAS_RPT];
   TknStrBSXL           *meId;
}WrUmmEcsfbTransCb;
        
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*End of _WR_UMM_ECSFB_H__*/

