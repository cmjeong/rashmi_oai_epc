


/**********************************************************************

     Name:     LTE-RRC Layer 
  
     Type:     C Source file
  
     Desc:     Broadcast and Multicast Module.

     File:     nh_brm.c

     Sid:      ni_brm.c@@/main/3 - Fri Jul  1 01:13:13 2011

     Prg:      rer 

**********************************************************************/
/** @defgroup brm_group Broadcast Multicast Module
 *  @{
 */
/* Header include files (.h) */
static const char* RLOG_MODULE_NAME="RRC";
static int RLOG_FILE_ID=112;
static int RLOG_MODULE_ID=512;
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm_tkns.h"       /* Common Token defines */
#include "cm_llist.h"      /* Common Link List defines */
#include "cm_hash.h"       /* Common Hashlist defines */
#include "cm_lte.h"        /* Common LTE defines */
#include "lnh.h"           /* LNH Interface defines */
#include "nhu.h"           /* NHU Interface defines */
#include "cpj.h"           /* CPJ Interface includes */
#include "nh.h"            /* RRC defines */

/* Header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm_lib.x"        /* Common library definitions */
#include "cm_tkns.x"       /* Common Token definitions */
#include "cm_llist.x"      /* Common Link List definitions */
#include "cm_hash.x"       /* Common Hashlist definitions */
#include "cm5.x"           /* Common timer definitions */
#include "cm_lte.x"        /* Common LTE includes */
#include "lnh.x"           /* LNH Interface includes */
#include "nhu.x"           /* NHU Interface includes */
#include "cpj.x"           /* CPJ Interface includes */
#include "nh.x"            /* RRC includes */


EXTERN U32 NhBcchPcchTbSzTbl[NH_BCCH_PCCH_TBSZTBL_SIZE];


/* local defines */

/* local typedefs */
 
/* local externs */
 
/* forward references */


/**
 * @brief Sends MIBs, SI messages to lower layers.
 * 
 * @details 
 * 
 *
 * This function is a state machine handler for sending MIB/SIB1/SI messages.
 
 * @param[in] datReqRspSdu    Data request/response SDU 
 * @param[in] cellAndUeCb     Container of cell and UE control block
 * @param[in] msgTransId      RRC message transaction identifier (not used here)
 * @param[in] errInfo         Error information used for sending error indication
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
*/
#ifdef ANSI
PUBLIC S16 nhBRMSysInfoTx
(
NhDatReqRspSdu   *datReqRspSdu,
NhCellAndUeCb    *cellAndUeCb,
U8               msgTransId,
NhuErrorInfo     *errInfo
)
#else /* ANSI */
PUBLIC S16 nhBRMSysInfoTx(datReqRspSdu, cellAndUeCb, msgTransId, errInfo)
NhDatReqRspSdu   *datReqRspSdu;
NhCellAndUeCb    *cellAndUeCb;
U8               msgTransId;
NhuErrorInfo     *errInfo;
#endif /* ANSI */
{
   NhDatReqParam        datReqParam;
   Void                 *pdu;
   NhuCmnMsg            *cmnMsg;
   Buffer               *encBuf;
   U32                  length;
   U32                  msgOctets;
   S32                  padOctets;
   S16                  ret;
   S32                  idx;
   NhuSysInfoBlockTyp1  *sib1;
#ifdef NH_ASN_COND_VALIDATE
   U8                   msgType = 0;
#endif /* NH_ASN_COND_VALIDATE */
   U32                  tbSize;

   TRC2(nhBRMSysInfoTx);

   RLOG0(L_DEBUG, "nhBRMSysInfoTx");

   UNUSED(msgTransId);

   ret = ROK;
   encBuf = NULLP;
   length = 0;
   NH_SET_ZERO(&(datReqParam), sizeof(NhDatReqParam));

   cmnMsg = &(datReqRspSdu->sdu.datReqSdu->sdu.ueMsg.msg.cmnMsg);
   /* Check is CSG Identity is present. If present it is CSG cell */
   if (C1_SYSTEMINFOBLOCKTYP1 == 
                    cmnMsg->cmn.bcchDlSchMsg.message.val.c1.choice.val)
   {
      sib1 = &(cmnMsg->cmn.bcchDlSchMsg.message.val.c1.val.systemInfoBlockTyp1);
      if (NH_IS_TKN_PRSNT(sib1->cellAccessRelatedInfo.csg_Identity))
      {
         cellAndUeCb->cellCb->crntCellCfgInfo.isCSGCell = TRUE;
      }
      else
      {
         cellAndUeCb->cellCb->crntCellCfgInfo.isCSGCell = FALSE;
      }
   }
/* Conditional IE validation */
#ifdef NH_ASN_COND_VALIDATE
   if(C1_SYSTEMINFOBLOCKTYP1 == 
            cmnMsg->cmn.bcchDlSchMsg.message.val.c1.choice.val)
      msgType = NH_MSGTYPE_SIB1;
   else if(C1_SYSTEMINFO == cmnMsg->cmn.bcchDlSchMsg.message.val.c1.choice.val)
      msgType = NH_MSGTYPE_SI;

   if(ROK != nhUTLValidateAsnCondIes((Void *)datReqRspSdu->sdu.datReqSdu,
                         msgType, errInfo, EVTNHUDATREQ))
   {
      RLOG0(L_ERROR, "conditional IE validation failed");
      RETVALUE(RFAILED);
   }
#endif /* NH_ASN_COND_VALIDATE */

   /* Encode the System info */
   if (NHU_MSG_DLBCCHBCH == cmnMsg->cmnMsgCategory)
   {
      pdu = (Void *) &(cmnMsg->cmn.bcchBchMsg);
   }
   else
   {
      pdu = (Void *) &(cmnMsg->cmn.bcchDlSchMsg);
   }

   ret = nhEDMEncReq(pdu, cmnMsg->cmnMsgCategory, &encBuf, &length);
   if ((ROK != ret) || (NULLP == encBuf))
   {
      /* Handle encode error here */
      NH_FILL_NHU_ERROR(*errInfo, NHU_ERRTYPE_ENC_FAILED, NHU_ERRCAUSE_NONE);
      RETVALUE(ret);
   }

   /* MOD ccpu00125691 do padding only for SIB's.
      For MIB padding is not required*/
   if(NHU_MSG_DLBCCHBCH != cmnMsg->cmnMsgCategory)
   {
      /* Address padding requirement */
      msgOctets = (length/8) + ((length%8)==0? 0:1);

      /* nh001.301 : Correction made in the padding bytes 
       *             calculation for the TB size of BCCH SDU.
       */

      if (length > NhBcchPcchTbSzTbl[NH_BCCH_PCCH_TBSZTBL_SIZE - 1])
      {
         RLOG0(L_ERROR, "encoded length is more than max TB size");

         NH_FILL_NHU_ERROR(*errInfo, NHU_ERRTYPE_MSG_SEND_FAILED, 
               NHU_ERRCAUSE_INVALID_TBS_SIZE);
         NH_FREEMBUF(encBuf);
         RETVALUE(RFAILED);
      }

      NH_GET_BCCH_PCCH_TBSZ((msgOctets * 8), tbSize);

      padOctets = (tbSize / 8) - msgOctets;

      for (idx=0; idx < padOctets; idx++)
      {
         SAddPstMsg(0, encBuf);
      }
   }
   /* Fill data request parameters */
   NH_FORM_NHID_FRM_DATREQ(datReqParam.nhId, datReqRspSdu->sdu.datReqSdu);
   datReqParam.isPdcpDatReq = FALSE;
   datReqParam.u.rlcParam.lcType = CM_LTE_LCH_BCCH;
   NH_COPY_TMG_INFO(datReqParam.u.rlcParam.u.timingInfo, 
                   cmnMsg->cmnMsgInfo.timingInfo);

   /* Send the Sys Info for transmission via KWU(RLC) interface */
   ret = nhPIMSendUeMsg(cellAndUeCb, &datReqParam, encBuf);
   if (ROK != ret)
   {
      /* Handle the send error */
      RLOG1(L_ERROR, "Send to lower layer failed ret[%d]", ret);
      RETVALUE(ret);
   }

   RETVALUE(ROK);
} /* nhBRMSysInfoTx */

/** @} */
/**********************************************************************
  
         End of file:     ni_brm.c@@/main/3 - Fri Jul  1 01:13:13 2011
   
**********************************************************************/
 
/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rer              1. LTE-RRC Initial Release.
/main/2      ---      ch               1. RRC Release 2.1.
/main/3      ---      sbalakrishna     1. Updated for Release of 3.1.
           nh001.301  hsingh           1. Correction made in the padding 
                                          bytes calculation for the TB size 
                                          of BCCH SDU.
**********************************************************************/

