

/********************************************************************20**
  
        Name:    CKW user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Utility Primitive code
                  for CKW Interface
 
        File:    kwac_ckwutl.c

        Sid:      kwac_ckwutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:23 2014
  
        Prg:     chakrapani
  
*********************************************************************21*/


/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_ckw.h"      /* CKW Acceptance defines */
#include <stdlib.h>

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_ckw.x"      /* CKW Acceptance defines */


/**
 * @brief Copy Configuration Request
 *
 * @details
 *
 *     Function : kwAcUtlCkwCpyCfgReq
 *
 *     This function copies CkwCfgInfo structure.
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PRIVATE S16 kwAcUtlCkwCpyCfgReq
(
CkwCfgInfo   *cfgReq
)
#else
PRIVATE S16 kwAcUtlCkwCpyCfgReq(cfgReq)
CkwCfgInfo   *cfgReq;
#endif
{
   KwAcCkwCfgReq  *tCfgReq;

   TRC2(kwAcUtlCkwCpyCfgReq);

   /* Get the next slot in Circular Q in kwAcCb.ckwCb.cfgReq */
   /* Write proper Circular Q for : kwAcCb.ckwCb.cfgReq */
   tCfgReq = &kwAcCb.ckwCb.cfgReq.node[kwAcUtlCkwCircQEnqueue(&(kwAcCb.ckwCb.cfgReq))];

   /* Set isInQ flag TRUE */
   tCfgReq->isInQ = TRUE;

   /* Update Next Transaction ID */
   kwAcCb.ckwCb.nxtTransId++;

   cfgReq->transId = kwAcCb.ckwCb.nxtTransId;

   /* As kwAcCb.ckwCb.cfgReq is array and static,
    * We can use cmMemcpy to copy the structure
    */
   cmMemcpy((U8 *)&(tCfgReq->cfgInfo), (U8 *)cfgReq, sizeof(CkwCfgInfo));
/*   KW_MEM_CPY(tCfgReq, cfgReq, sizeof(CkwCfgInfo));*/

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCkwCpyCfgReq */


/**
 * @brief Build Configuration Request
 *
 * @details
 *
 *     Function : kwAcUtlCkwBuildCfgReq
 *
 *     This function fills CkwCfgInfo structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlCkwBuildCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CkwCfgInfo   *cfgReq
)
#else
PUBLIC S16 kwAcUtlCkwBuildCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CkwCfgInfo   *cfgReq;
#endif
{
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U8             numEnt;
   U8             idx;

   U8             cfgType[CKW_MAX_ENT_CFG];
   U8             rbId[CKW_MAX_ENT_CFG];
   U8             rbType[CKW_MAX_ENT_CFG];

   /* Logical channel Id Info */
   U8             logChId0Id[CKW_MAX_ENT_CFG];
   U8             logChId0Type[CKW_MAX_ENT_CFG];
   U8             logChId1Id[CKW_MAX_ENT_CFG];
   U8             logChId1Type[CKW_MAX_ENT_CFG];

   CmLteRlcMode   entMode[CKW_MAX_ENT_CFG];
   U8             dir[CKW_MAX_ENT_CFG];

   /* UM Mode Dl and UL */
   U8             umDlSnLen[CKW_MAX_ENT_CFG];
   U8             umUlSnLen[CKW_MAX_ENT_CFG];
   U8             umUlReOrdTmr[CKW_MAX_ENT_CFG];
   Txt            parseStr[100];

   /* AM Mode Dl and UL */
   U16            amDlPollRetxTmr[CKW_MAX_ENT_CFG];
   U16            amDlPollPdu[CKW_MAX_ENT_CFG];
   U16            amDlPollByte[CKW_MAX_ENT_CFG];
   U8             amDlMaxRetx[CKW_MAX_ENT_CFG];
   U16            amUlStaProhTmr[CKW_MAX_ENT_CFG];
   U8             amUlReOrdTmr[CKW_MAX_ENT_CFG];
   /* kw005.201, changed the data type */
   S16            amUlReOrdTmr0 = -1;
   /* L2 Measurement values */
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   U8             qci[CKW_MAX_QCI];
#endif

   TRC2(kwAcUtlCkwBuildCfgReq);

   /* Memset to 0 all local arrays */
   ueId = 0;
   cellId = 0;
   numEnt = 0;

   CMXTA_ZERO(cfgType, sizeof(cfgType));
   CMXTA_ZERO(rbId, sizeof(rbId));
   CMXTA_ZERO(rbType, sizeof(rbType));

   CMXTA_ZERO(logChId0Id, sizeof(logChId0Id));
   CMXTA_ZERO(logChId0Type, sizeof(logChId0Type));
   CMXTA_ZERO(logChId1Id, sizeof(logChId1Id));
   CMXTA_ZERO(logChId1Type, sizeof(logChId1Type));

   CMXTA_ZERO(entMode, sizeof(entMode));
   CMXTA_ZERO(dir, sizeof(dir));

   CMXTA_ZERO(umDlSnLen, sizeof(umDlSnLen));
   CMXTA_ZERO(umUlSnLen, sizeof(umUlSnLen));
   CMXTA_ZERO(umUlReOrdTmr, sizeof(umUlReOrdTmr));

   CMXTA_ZERO(amDlPollRetxTmr, sizeof(amDlPollRetxTmr));
   CMXTA_ZERO(amDlPollPdu, sizeof(amDlPollPdu));
   CMXTA_ZERO(amDlPollByte, sizeof(amDlPollByte));
   CMXTA_ZERO(amDlMaxRetx, sizeof(amDlMaxRetx));
   CMXTA_ZERO(amUlStaProhTmr, sizeof(amUlStaProhTmr));
   CMXTA_ZERO(amUlReOrdTmr, sizeof(amUlReOrdTmr));
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   CMXTA_ZERO(qci, sizeof(qci));
#endif

   /* <tapa.ckw.cfgreq ueId="0" cellId="1" numEnt="5"
    * cfgType="1:1:1:1:1"
    * rbId="1:2:3:4:5"
    * rbType="0:1:1:1:1"
    *
    * logChId0Id="1:2:3:4:0"
    * logChId0Type="1:1:2:2:0"
    * logChId1Id="0:0:0:0:5"
    * logChId1Type="0:0:0:0:3"
    *
    * entMode="1:1;2:2:3"
    * dir="1:2:1:2:0"
    * 
    * umDlSnLen="0:0:5:0:0"
    *
    * umUlSnLen="0:0:0:5:0"
    * umUlReOrdTmr="0:0:0:10:0"
    *
    * amDlPollRetxTmr="0:0:0:0:0"
    * amDlPollPdu="0:0:0:0:0"
    * amDlPollByte="0:0:0:0:0"
    * amDlMaxRetx="0:0:0:0:0"
    *
    * amUlStaProhTmr="0:0:0:0:0"
    * amUlReOrdTmr="0:0:0:0:0"
    * />
    */

   /* Fill cfgReq from XML */
   /* UE ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(cfgReq->ueId));

   /* CELL ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cfgReq->cellId));

   /* Number of entities */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numEnt", &(cfgReq->numEnt));

   KWAC_XML_GET_VALLIST(parseStr, "rbId", ":", rbId, U8);
   KWAC_XML_GET_VALLIST(parseStr, "cfgType", ":", cfgType, U8);
   KWAC_XML_GET_VALLIST(parseStr, "rbType", ":", rbType, U8);

   /* Logica Channel DL - 0 ID */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "logChId0Id", logChId0Id, &numEnt);

   /* Logica Channel DL - 0 ID */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "logChId0Type", logChId0Type, &numEnt);

   /* Logica Channel DL - 1 ID */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "logChId1Id", logChId1Id, &numEnt);

   /* Logica Channel DL - 1 ID */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "logChId1Type", logChId1Type, &numEnt);

   /* Entity Mode */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "entMode", entMode, &numEnt);

   /* Direction */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "dir", dir, &numEnt);

   /* UM DL SnLen */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "umDlSnLen", umDlSnLen, &numEnt);

   /* UM UL SnLen */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "umUlSnLen", umUlSnLen, &numEnt);

   /* UM UL ReOrdTmr */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "umUlReOrdTmr", umUlReOrdTmr, &numEnt);

   /* AM DL PollRetx */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,\
         "amDlPollRetxTmr", amDlPollRetxTmr, &numEnt);

   /* AM DL PollPdu */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,\
         "amDlPollPdu", amDlPollPdu, &numEnt);

   /* AM DL PollByte */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,\
         "amDlPollByte", amDlPollByte, &numEnt);

   /* AM DL MaxRetx */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "amDlMaxRetx", amDlMaxRetx, &numEnt);

   /* AM UL StaProhTmr */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,\
         "amUlStaProhTmr", amUlStaProhTmr, &numEnt);

   /* AM UL ReOrdTmr */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "amUlReOrdTmr", amUlReOrdTmr, &numEnt);
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   /* Qci */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "qci", qci, &numEnt);
#endif
   /* kw005.201 changed the data type */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,  "amUlReOrdTmr0", &amUlReOrdTmr0);
   if(amUlReOrdTmr0 != -1) amUlReOrdTmr[0] = amUlReOrdTmr0;

   cfgReq->transId = kwAcCb.ckwCb.nxtTransId;

   numEnt = cfgReq->numEnt;

   for (idx = 0; idx < numEnt; idx++)
   {
      CkwEntCfgInfo *entCfg;
      entCfg = &(cfgReq->entCfg[idx]);

      entCfg->rguSapId = kwAcCb.rguCb.spId;
      entCfg->cfgType = cfgType[idx];
      entCfg->rbId = rbId[idx];
      entCfg->rbType = rbType[idx];

      entCfg->entMode = entMode[idx];
      entCfg->dir = dir[idx];
      switch (entCfg->entMode)
      {
         case CM_LTE_MODE_TM:
            {
               entCfg->lCh[0].lChId = logChId0Id[idx];
               entCfg->lCh[0].type = logChId0Type[idx];
               break;
            }
         case CM_LTE_MODE_UM:
            {
               entCfg->lCh[0].lChId = logChId0Id[idx];
               entCfg->lCh[0].type = logChId0Type[idx];

               switch (entCfg->dir)
               {
                  case CKW_CFG_DIR_DL:
                     {
                        entCfg->m.umInfo.dl.snLen = umDlSnLen[idx];
                        break;
                     }
                  case CKW_CFG_DIR_UL:
                     {
                        entCfg->m.umInfo.ul.snLen = umUlSnLen[idx];
                        entCfg->m.umInfo.ul.reOrdTmr = umUlReOrdTmr[idx];
                        break;
                     }
                  /* Patch kw004.201 */
                  case CKW_CFG_DIR_BOTH:
                     {
                        entCfg->m.umInfo.dl.snLen = umDlSnLen[idx];
                        entCfg->m.umInfo.ul.snLen = umUlSnLen[idx];
                        entCfg->m.umInfo.ul.reOrdTmr = umUlReOrdTmr[idx];
                        break;
                     }
               }
               break;
            }
         case CM_LTE_MODE_AM:
            {
               entCfg->lCh[0].lChId = logChId0Id[idx];
               entCfg->lCh[0].type = logChId0Type[idx];
               entCfg->lCh[1].lChId = logChId1Id[idx];
               entCfg->lCh[1].type = logChId1Type[idx];

               /*switch (entCfg->dir)
               {
                  case CKW_CFG_DIR_DL:
                     {*/
                        entCfg->m.amInfo.dl.pollRetxTmr = amDlPollRetxTmr[idx];
                        entCfg->m.amInfo.dl.pollPdu = amDlPollPdu[idx];
                        entCfg->m.amInfo.dl.pollByte = amDlPollByte[idx];
                        entCfg->m.amInfo.dl.maxRetx = amDlMaxRetx[idx];
                     /*}
                  case CKW_CFG_DIR_UL:
                     {*/
                        entCfg->m.amInfo.ul.staProhTmr = amUlStaProhTmr[idx];
                        entCfg->m.amInfo.ul.reOrdTmr = amUlReOrdTmr[idx];
                        break;
                     /*}
               }*/
               break;
            }
      }
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
      entCfg->qci = qci[idx];
#endif
   }

   /* Copy cfgReq to kwAcCb.ckwCb.cfgReq */
   if (kwAcUtlCkwCpyCfgReq(cfgReq) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);

   /* Store tcCb and spCb to fetch Off-board attributes in
    * Off-board acceptance code kwac_libcb.c in DL
    */
   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCkwBuildCfgReq */


/**
 * @brief Validate Configuration Confirmation
 *
 * @details
 *
 *     Function : kwAcUtlValdtCfgCfm
 *
 *     This function Validates CkwCfgCfmInfo structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *cfgCfm
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtCfgCfm
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
CkwCfgCfmInfo     *cfgCfm
)
#else
PUBLIC S16 kwAcUtlValdtCfgCfm(tcCb, spCb, cfgCfm)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
CkwCfgCfmInfo     *cfgCfm;
#endif
{
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U8             numEnt;
   U8             rbId[CKW_MAX_ENT_CFG];
   U8             rbType[CKW_MAX_ENT_CFG];
   U16            status[CKW_MAX_ENT_CFG];
   U16            reason[CKW_MAX_ENT_CFG];
   CkwCfgInfo     *tCfgReq = NULLP;
   KwAcCkwCfgReq  *acCfgReq = NULLP;
   U16            idx;
   Txt            parseStr[100];

   TRC2(kwAcUtlValdtCfgCfm);

   /* Memset to 0 all local arrays */
   ueId = 0;
   cellId = 0;
   numEnt = 0;

   CMXTA_ZERO(rbId, sizeof(rbId));
   CMXTA_ZERO(rbType, sizeof(rbType));
   CMXTA_ZERO(status, sizeof(status));
   CMXTA_ZERO(reason, sizeof(reason));

   /* <tapa.ckw.cfgcfm ueId="0" cellId="1" numEnt="5"
    * rbId="1:2:3:4:5"
    * rbType="0:1:1:1:1"
    *
    * status="0:0:0:0:1"
    * reason="0:0:0:0:5"
    * />
    */

   /* Fill cfgReq from XML */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   /* Number of entities */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numEnt", &(numEnt));
   if (numEnt != 0)
   {
      KWAC_XML_GET_VALLIST(parseStr, "rbId", ":", rbId, U8);
      KWAC_XML_GET_VALLIST(parseStr, "status", ":", status, U16);
      KWAC_XML_GET_VALLIST(parseStr, "reason", ":", reason, U16);
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcUtlValdtCfgCfm(): numEnt = 0.\n"));
   }

   /* Pop the configuration request form circular Q : kwAcCh.ckwCb.cfgReq */
   acCfgReq = &(kwAcCb.ckwCb.cfgReq.node[\
         kwAcUtlCkwCircQGetFront(&kwAcCb.ckwCb.cfgReq)]);
   tCfgReq = &(acCfgReq->cfgInfo);

   if (cfgCfm->transId != tCfgReq->transId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCfgCfm():Failed : transId MisMatch: exp (%d) rcvd (%d) \n",\
               tCfgReq->transId, cfgCfm->transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCfgCfm():Failed : transId MisMatch: exp (%ld) rcvd (%ld) \n",\
               tCfgReq->transId, cfgCfm->transId), 2);
#endif
      KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (cfgCfm->ueId != tCfgReq->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCfgCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",\
               tCfgReq->ueId, cfgCfm->ueId), 2);
      KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (cfgCfm->cellId != tCfgReq->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCfgCfm():Failed : cellID MisMatch: exp (%d) rcvd (%d) \n",\
               tCfgReq->cellId, cfgCfm->cellId), 2);
      KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (cfgCfm->numEnt != tCfgReq->numEnt)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCfgCfm():Failed : numEnt MisMatch: exp (%d) rcvd (%d) \n",\
               tCfgReq->numEnt, cfgCfm->numEnt), 2);
      KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   for (idx = 0; idx < cfgCfm->numEnt; idx++)
   {
      if (cfgCfm->entCfgCfm[idx].rbId != tCfgReq->entCfg[idx].rbId)
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCfgCfm():Failed : rbId MisMatch: idx (%d) exp (%d) rcvd (%d) \n",\
                  idx, tCfgReq->entCfg[idx].rbId, cfgCfm->entCfgCfm[idx].rbId), 2);
         KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (cfgCfm->entCfgCfm[idx].rbType != tCfgReq->entCfg[idx].rbType)
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCfgCfm():Failed : rbType MisMatch: idx (%d) exp (%d) rcvd (%d) \n",\
                  idx, tCfgReq->entCfg[idx].rbType, cfgCfm->entCfgCfm[idx].rbType), 2);
         KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (cfgCfm->entCfgCfm[idx].status.status != status[idx])
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCfgCfm():Failed : Status MisMatch: idx (%d) exp (%d) rcvd (%d) \n",\
                  idx, status[idx], cfgCfm->entCfgCfm[idx].status.status), 2);
         KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if ((status[idx] != CKW_CFG_CFM_NOK) &&\
            (cfgCfm->entCfgCfm[idx].status.reason != reason[idx]))
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCfgCfm():Failed : Reason MisMatch: idx (%d) exp (%d) rcvd (%d) \n",\
                  idx, reason[idx], cfgCfm->entCfgCfm[idx].status.reason), 2);
         KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }
   }

   CMXTA_ZERO(acCfgReq, sizeof(KwAcCkwCfgReq));
   kwAcUtlCkwCircQDequeue(&kwAcCb.ckwCb.cfgReq);

   KW_FREE_ACC(cfgCfm, sizeof(CkwCfgCfmInfo));

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtCfgCfm */


/**
 * @brief Build UeId Change Request
 *
 * @details
 *
 *     Function : kwAcUtlCkwBuildUeIdChgReq
 *
 *     This function fills CkwUeInfo structure for old and new
 *     and sends to RLC.
 *     
 *  @param[in]  tcCb          -  TC Control Block
 *  @param[in]  spCb          -  SP Control Block
 *  @param[in]  ueInfo        -  UE Information
 *  @param[in]  newUeInfo     -  New UE Information
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlCkwBuildUeIdChgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CkwUeInfo    *ueInfo,
CkwUeInfo    *newUeInfo
)
#else
PUBLIC S16 kwAcUtlCkwBuildUeIdChgReq(tcCb, spCb, ueInfo, newUeInfo)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CkwUeInfo    *ueInfo;
CkwUeInfo    *newUeInfo;
#endif
{
   TRC2(kwAcUtlCkwBuildCfgReq);

   /* <tapa.ckw.ueidchgreq transid="1" ueId="1" cellId="1" newUeId="2" newCellId="1"
    * />
    */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueInfo->ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(ueInfo->cellId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "newUeId", &(newUeInfo->ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "newCellId", &(newUeInfo->cellId));

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCkwBuildUeIdChgReq */


/**
 * @brief XTA Function to free resources aquired by the interface messages
 * received from RLC to Dummy-RRC.
 *
 * @details
 *
 *     Function : kwAcUtlFreeCkwCb
 *     
 *     A pointer to this function is registered with each 
 *     Queue element that gets enqueued as part of its call
 *     handler functionality. After the interface primitive 
 *     validation is done by the validation handler, the queue
 *     element is flushed, this function gets invoked as part
 *     of this flushing. Based on type of primitive, the memory
 *     freeing takes place.
 *     
 *  @param[in]  *qElm 
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlCkwFreeCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 kwAcUtlCkwFreeCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwElm;
   KwAcCkwInfo  *ckwInfo = NULLP; 
 
   TRC2(kwAcUtlCkwFreeCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlCkwFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   kwElm = (KwAcMsgQElm *)qElm->data;
  
   if(kwElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   ckwInfo = &(kwElm->u.ckwInfo);
   
   if (kwElm != NULLP)
   {
      if(kwElm->mBuf != NULLP)
         CMXTA_FREEMBUF(kwElm->mBuf);

      CMXTA_FREE(kwElm, sizeof (KwAcMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of kwAcUtlCkwFreeCb */

/*************************************************************************
 *                CKW CFG REQ QUEUE PRIMITIVES START
 *************************************************************************/
  
/**
 * @brief Circular Queue for CKW Interface
 *
 * @details
 *
 *     Function : kwAcUtlCkwCQMakeNull
 *
 *     This function Initializes the CKW Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlCkwCQMakeNull
(
KwAcCkwCircQ      *queue
)
#else
PUBLIC Void kwAcUtlCkwCQMakeNull(queue)
KwAcCkwCircQ      *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtilCircQMakeNull */

#ifdef ANSI
PUBLIC U16 kwAcUtlCkwCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlCkwCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases */
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
   RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlCkwCircQAddOne */

#ifdef ANSI
PUBLIC U16 kwAcUtlCkwCircQEnqueue
(
KwAcCkwCircQ *queue
)
#else
PUBLIC U16 kwAcUtlCkwCircQEnqueue(queue)
KwAcCkwCircQ *queue;
#endif
{
   /* Making 3 length difference between rear and front to make
    * sure Q is full
    */
   if(kwAcUtlCkwCircQAddOne(kwAcUtlCkwCircQAddOne(
               kwAcUtlCkwCircQAddOne(queue->rear))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlCkwCircQEnqueue(): CKW Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlCkwCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlCkwCircQEnqueue */

#ifdef ANSI
PUBLIC U16 kwAcUtlCkwCircQGetFront
(
KwAcCkwCircQ *queue
)
#else
PUBLIC U16 kwAcUtlCkwCircQGetFront(queue)
KwAcCkwCircQ *queue;
#endif
{
   if(KWAC_UTL_CKW_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlCkwCircQGetFront(): CKW Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlCkwCircQGetFront */

#ifdef ANSI
PUBLIC U16 kwAcUtlCkwCircQGetNext
(
KwAcCkwCircQ   *queue,
U16            idx
)
#else
PUBLIC U16 kwAcUtlCkwCircQGetNext(queue, idx)
KwAcCkwCircQ   *queue;
U16            idx;
#endif
{
   if (kwAcUtlCkwCircQAddOne(idx) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,\
               "kwAcUtlCkwCircQGetNext(): CKW Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlCkwCircQAddOne(queue->front));
} /* kwAcUtlCkwCircQGetNext */

#ifdef ANSI
PUBLIC Void kwAcUtlCkwCircQDequeue
(
KwAcCkwCircQ *queue
)
#else
PUBLIC Void kwAcUtlCkwCircQDequeue(queue)
KwAcCkwCircQ *queue;
#endif
{
   if(KWAC_UTL_CKW_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlCkwCircQDequeue(): CKW Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlCkwCircQAddOne(queue->front);
      if(KWAC_UTL_CKW_CQ_ISEMPTY(queue))
         break;
   }

   RETVOID;
} /* kwAcUtlCkwCircQDequeue */

/*************************************************************************
 *                CKW CFG REQ QUEUE PRIMITIVES END
 *************************************************************************/

/********************************************************************30**
         End of file:     kwac_ckwutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:23 2014
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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
/main/3     kw004.201 ap      1. Added support for CKW_CFG_DIR_BOTH in 
                                 kwAcUtlCkwBuildCfgReq
/main/4     kw005.201 rd      1. Changes done in func kwAcUtlCkwCircQAddOne
                                 wrt macro KWAC_MAX_CIRCQ_SIZE for TCs added
                                 for RLC R9 upgrade.
                      ap      2. Added support for L2 Measurement.
*********************************************************************91*/

