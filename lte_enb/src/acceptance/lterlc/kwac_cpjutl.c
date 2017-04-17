

/********************************************************************20**
  
        Name:    CPJ user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Utility Primitive code
                  for CPJ Interface
 
        File:    kwac_cpjutl.c

        Sid:      kwac_cpjutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:25 2014
  
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
#include "ckw.h"           /* CKW defines */
#include "lkw.h"           /* LKW defines */
#include "cpj.h"           /* CPJ defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw_err.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_cpj.h"      /* CPJ Acceptance defines */
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
#include "ckw.x"           /* CKW */
#include "lkw.x"           /* LKW */
#include "cpj.x"           /* CPJ */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_cpj.x"      /* CPJ Acceptance defines */


#ifdef KW_PDCP
/**
 * @brief Copy Configuration Request
 *
 * @details
 *
 *     Function : kwAcUtlCpjCpyCfgReq
 *
 *     This function copies CpjCfgInfo structure.
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PRIVATE S16 kwAcUtlCpjCpyCfgReq
(
CpjCfgReqInfo   *cfgReq
)
#else
PRIVATE S16 kwAcUtlCpjCpyCfgReq(cfgReq)
CpjCfgReqInfo   *cfgReq;
#endif
{
   KwAcCpjCfgReq  *tCfgReq;

   TRC2(kwAcUtlCpjCpyCfgReq);

   /* Get the next slot in Circular Q in kwAcCb.nhCpjCb.cfgReq */
   /* Write proper Circular Q for : kwAcCb.nhCpjCb.cfgReq */
   tCfgReq = &kwAcCb.nhCpjCb.cfgReq.node[kwAcUtlCpjCircQEnqueue(&(kwAcCb.nhCpjCb.cfgReq))];

   /* Set isInQ flag TRUE */
   tCfgReq->isInQ = TRUE;

   /* Update Next Transaction ID */
   kwAcCb.nhCpjCb.nxtTransId++;

   cfgReq->transId = kwAcCb.nhCpjCb.nxtTransId;

   /* As kwAcCb.nhCpjCb.cfgReq is array and static,
    * We can use cmMemcpy to copy the structure
    */
   cmMemcpy((U8 *)&(tCfgReq->cfgInfo), (U8 *)cfgReq, sizeof(CpjCfgReqInfo));

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpjCpyCfgReq */


/**
 * @brief Build Configuration Request
 *
 * @details
 *
 *     Function : kwAcUtlCpjBuildCfgReq
 *
 *     This function fills CpjCfgInfo structure and keeps copy in XTA before
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
PUBLIC S16 kwAcUtlCpjBuildCfgReq
(
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjCfgReqInfo   *cfgReq
)
#else
PUBLIC S16 kwAcUtlCpjBuildCfgReq(tcCb, spCb, cfgReq)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
CpjCfgReqInfo   *cfgReq;
#endif
{
   S16            discardTmr[CPJ_MAX_CFG];
   U32            dlCount[CPJ_MAX_CFG];
   U32            ulCount[CPJ_MAX_CFG];
   Txt            ulBitMap[50];
   U16            maxCid[CPJ_MAX_CFG];
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U8             numEnt;
   U8             idx, idxProf;
   U8             numBytes = 0;
   U8             cnt = 0;

   U8             mode[CPJ_MAX_CFG];
   U8             cfgType[CPJ_MAX_CFG];
   U8             rbId[CPJ_MAX_CFG];
   U8             rbType[CPJ_MAX_CFG];

   Bool           discReqd[CPJ_MAX_CFG];
   Bool           cfmReqd[CPJ_MAX_CFG];
   Txt            parseStr[100];

   U8             dir[CPJ_MAX_CFG];

   Bool           statusRepReqd[CPJ_MAX_CFG];
   S8             statusRepReqd0 =  -1;
   U8             pdcpSNSize[CPJ_MAX_CFG];

   Bool           hdrCompUsed[CPJ_MAX_CFG];
   S8             hdrCompUsed0;
   Bool           profile[CPJ_MAX_CFG];
   U8             bitFlag[CPJ_MAX_CFG];
   Bool           isHoPres[CPJ_MAX_CFG];
   U8             numBits[CPJ_MAX_CFG];
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   U8             qci[CPJ_MAX_QCI];
#endif

   TRC2(kwAcUtlCpjBuildCfgReq);

   /* Memset to 0 all local arrays */
   ueId         = 0;
   cellId       = 0;
   numEnt       = 0;
   hdrCompUsed0 = -1;

   CMXTA_ZERO(mode, sizeof(mode));
   CMXTA_ZERO(cfgType, sizeof(cfgType));
   CMXTA_ZERO(rbId, sizeof(rbId));
   CMXTA_ZERO(rbType, sizeof(rbType));

   CMXTA_ZERO(discReqd, sizeof(discReqd));
   CMXTA_ZERO(cfmReqd, sizeof(cfmReqd));
   CMXTA_ZERO(discardTmr, sizeof(discardTmr));

   CMXTA_ZERO(dir, sizeof(dir));

   CMXTA_ZERO(statusRepReqd, sizeof(statusRepReqd));
   CMXTA_ZERO(pdcpSNSize, sizeof(pdcpSNSize));
   CMXTA_ZERO(hdrCompUsed, sizeof(hdrCompUsed));
   CMXTA_ZERO(maxCid, sizeof(maxCid));
   CMXTA_ZERO(profile, sizeof(profile));
   CMXTA_ZERO(bitFlag, sizeof(bitFlag));
   CMXTA_ZERO(isHoPres, sizeof(isHoPres));
   CMXTA_ZERO(dlCount, sizeof(dlCount));
   CMXTA_ZERO(ulCount, sizeof(ulCount));
   CMXTA_ZERO(numBits, sizeof(numBits));
   CMXTA_ZERO(ulBitMap, sizeof(ulBitMap));
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   CMXTA_ZERO(qci, sizeof(qci));
#endif
   /* <tapa.cpj.cfgreq ueId="0" cellId="1" numEnt="5"
    *
    * rbId="1:2:3:4:5"
    * cfgType="1:1:1:1:1"
    *
    * rbType="1:1:2:2:2"
    * discReqd="1:1:1:1:1"
    * cfmReqd="1:1:1:1:1"
    * discardTmr="20:20:20:20:20"
    *
    * dir="1:2:1:2:0"
    * mode="1:1;2:2:3"
    *
    * statusRepReqd="1:1:1:1:1"
    * pdcpSNSize="7:7:7:7:7"
    *
    * hdrCompUsed="1:1:1:1:1"
    * maxCid="15:15:15:15:15"
    * profile="7:1:1:1:1"
    *
    * bitFlag="1:3:3:3:1"
    * isHoPres="1:0:0:0:0"
    * dlCount="12:12:12:12:12"
    * ulCount="12:12:12:12:12"
    * numBits="2:0:0:1:2"
    * ulBitMap="11:0:0:1:11"
    *
    * />
    */

   /* Fill cfgReq from XML */
   /* UE ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(cfgReq->ueId));

   /* CELL ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cfgReq->cellId));

   /* Number of entities */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numEnt", &(cfgReq->numEnt));

   /* RB ID */
   KWAC_XML_GET_VALLIST(parseStr, "rbId", ":", rbId, U8);

   /* Config Type */
   KWAC_XML_GET_VALLIST(parseStr, "cfgType", ":", cfgType, U8);

   /* RB Type */
   KWAC_XML_GET_VALLIST(parseStr, "rbType", ":", rbType, U8);


   /* Discard Required */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "discReqd", discReqd, &numEnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "discReqd0", &(discReqd[0]));

   /* Confirm Required */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "cfmReqd", cfmReqd, &numEnt);

   /* Entity Mode */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "mode", mode, &numEnt);

   /* Discard Timer */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, CMXTA_SEP_COLON,\
         "discardTmr", discardTmr, &numEnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "discardTmr0", &(discardTmr[0]));

   /* Direction */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "dir", dir, &numEnt);

   /* Status Report Requiered */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "statusRepReqd", statusRepReqd, &numEnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "statusRepReqd0", &(statusRepReqd0));
   if(statusRepReqd0 != -1) statusRepReqd[0] = statusRepReqd0;

   /* SN */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "pdcpSNSize", pdcpSNSize, &numEnt);

   /* Header Compression Used */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "hdrCompUsed", hdrCompUsed, &numEnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "hdrCompUsed0", &(hdrCompUsed0));
   if(hdrCompUsed0 != -1) hdrCompUsed[0] = hdrCompUsed0;

   /* Maximum CID */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,\
         "maxCid", maxCid, &numEnt);

   /* Profile */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "profile", profile, &numEnt);

   /* bitFlag */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "bitFlag", bitFlag, &numEnt);

   /* isHoPres */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "isHoPres", isHoPres, &numEnt);

   /* dlCount */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,\
         "dlCount", dlCount, &numEnt);

   /* ulCount */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,\
         "ulCount", ulCount, &numEnt);

   /* numBits */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "numBits", numBits, &numEnt);

   /* ulBitMap */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "ulBitMap", ulBitMap);

   /* qci */
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "qci", qci, &numEnt);
#endif
   cfgReq->transId = kwAcCb.nhCpjCb.nxtTransId;

   numEnt = cfgReq->numEnt;

   for (idx = 0; idx < numEnt; idx++)
   {
      CpjCfgEnt *cfgEnt;
      cfgEnt = &(cfgReq->cfgEnt[idx]);

      cfgEnt->rbId = rbId[idx];
      cfgEnt->rbType = rbType[idx];
      cfgEnt->cfgType = cfgType[idx];

      if (cfgType[idx] == CPJ_CFG_ADD)
      {
         cfgEnt->m.addCfg.discReqd = discReqd[idx];
         cfgEnt->m.addCfg.cfmReqd = cfmReqd[idx];
         cfgEnt->m.addCfg.rlcInfo.dir = dir[idx];
         cfgEnt->m.addCfg.rlcInfo.mode = mode[idx];
         if (mode[idx] == CM_LTE_MODE_AM)
         {
            cfgEnt->m.addCfg.rlcInfo.m.rlcAm.statusRepReqd = statusRepReqd[idx];
         }
         else
         {
            if ((pdcpSNSize[idx] == 7) || (pdcpSNSize[idx] == 12))
               cfgEnt->m.addCfg.rlcInfo.m.rlcUm.pdcpSNSize = pdcpSNSize[idx];
            else
               cfgEnt->m.addCfg.rlcInfo.m.rlcUm.pdcpSNSize = 7;
         }

         cfgEnt->m.addCfg.discardTmr = discardTmr[idx];
         cfgEnt->m.addCfg.hdrCompCfg.hdrCompUsed = hdrCompUsed[idx];
         cfgEnt->m.addCfg.hdrCompCfg.rohcInfo.maxCid = maxCid[idx];

         /* Profile: XML receives as decimal value of 10 bits.
          * Set the profLst[idx] to true if idx bit is set.
          */
         for (idxProf = 0; idxProf < 9; idxProf++)
         {
            if (profile[idx] >> (8 - idxProf))
            {
               cfgEnt->m.addCfg.hdrCompCfg.rohcInfo.profLst[idxProf] = TRUE;
            }
         }
         /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
         cfgEnt->m.addCfg.qci = qci[idx];
#endif
      }
      else if (cfgType[idx] == CPJ_CFG_MODIFY)
      {
         cfgEnt->m.modCfg.bitFlag = bitFlag[idx];

         cfgEnt->m.modCfg.discReqd = discReqd[idx];
         cfgEnt->m.modCfg.cfmReqd = cfmReqd[idx];

         cfgEnt->m.modCfg.hdrCompCfg.hdrCompUsed = hdrCompUsed[idx];
         cfgEnt->m.modCfg.hdrCompCfg.rohcInfo.maxCid = maxCid[idx];
         cfgEnt->m.modCfg.hdrCompCfg.rohcInfo.profLst[profile[idx]] = TRUE;

         cfgEnt->m.modCfg.hoInfo.isHoPres = isHoPres[idx];
         cfgEnt->m.modCfg.hoInfo.dlCount = dlCount[idx];
         cfgEnt->m.modCfg.hoInfo.ulCount = ulCount[idx];
         cfgEnt->m.modCfg.hoInfo.numBits = numBits[idx];

         if (numBits[idx] == 0)
         {
            numBytes = 0;
         }
         else
         {
            numBytes = numBits[idx]/8;
            if(numBits[idx] % 8) numBytes ++;
         }

         if (numBytes)
         {
            KW_ALLOC_ACC(cfgEnt->m.modCfg.hoInfo.ulBitMap, (numBytes) * sizeof(U8));
#if (ERRCLASS & ERRCLS_ADD_RES)
            if (cfgEnt->m.modCfg.hoInfo.ulBitMap == NULLP)
            {
               PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
                     "kwAcUtlCpjBuildCfgReq: ulBitMap allocation Failed.");
            }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

            for (cnt = 0, numBytes = 0; cnt < strlen(ulBitMap); cnt++)
            {
               PJ_CPJ_UTL_SETKEY_BITS(cfgEnt->m.modCfg.hoInfo.ulBitMap[numBytes], ulBitMap[cnt], cnt);

               if (cnt % 2 == 1)
                  numBytes++;
            }
         }

      }
   }

   /* Copy cfgReq to kwAcCb.nhCpjCb.cfgReq */
   if (kwAcUtlCpjCpyCfgReq(cfgReq) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpjBuildCfgReq */


/**
 * @brief Validate Configuration Confirmation
 *
 * @details
 *
 *     Function : kwAcUtlCpjValdtCfgCfm
 *
 *     This function Validates CpjCfgCfm structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *cfgCfm
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlCpjValdtCfgCfm
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
CpjCfgCfmInfo     *cfgCfm
)
#else
PUBLIC S16 kwAcUtlCpjValdtCfgCfm(tcCb, spCb, cfgCfm)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
CpjCfgCfmInfo     *cfgCfm;
#endif
{
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U8             numEnt;
   U8             rbId[CPJ_MAX_CFG];
   U16            status[CPJ_MAX_CFG];
   U16            reason[CPJ_MAX_CFG];
   CpjCfgReqInfo  *tCfgReq = NULLP;
   KwAcCpjCfgReq  *acCfgReq = NULLP;
   U16            idx;
   Txt            parseStr[100];

   TRC2(kwAcUtlCpjValdtCfgCfm);

   /* Memset to 0 all local arrays */
   ueId = 0;
   cellId = 0;
   numEnt = 0;

   CMXTA_ZERO(rbId, sizeof(rbId));
   CMXTA_ZERO(status, sizeof(status));
   CMXTA_ZERO(reason, sizeof(reason));

   /* <tapa.cpj.cfgcfm ueId="0" cellId="1" numEnt="5"
    * rbId="1:2:3:4:5"
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
      /* kw005.201 removed redundant code */
      KWAC_XML_GET_VALLIST(parseStr, "rbId", ":", rbId, U8);
      KWAC_XML_GET_VALLIST(parseStr, "status", ":", status, U16);
      KWAC_XML_GET_VALLIST(parseStr, "reason", ":", reason, U16);
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcUtlCpjValdtCfgCfm(): numEnt = 0.\n"));
   }

   /* Pop the configuration request form circular Q : kwAcCh.cpjCb.cfgReq */
   acCfgReq = &(kwAcCb.nhCpjCb.cfgReq.node[\
         kwAcUtlCpjCircQGetFront(&kwAcCb.nhCpjCb.cfgReq)]);
   tCfgReq = &(acCfgReq->cfgInfo);

   if (cfgCfm->transId != tCfgReq->transId)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlCpjValdtCfgCfm():Failed : transId MisMatch: exp (%ld) rcvd (%ld) \n",\
               tCfgReq->transId, cfgCfm->transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlCpjValdtCfgCfm():Failed : transId MisMatch: exp (%d) rcvd (%d) \n",\
               tCfgReq->transId, cfgCfm->transId), 2);
#endif
      KW_FREE_ACC(cfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (cfgCfm->ueId != tCfgReq->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlCpjValdtCfgCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",\
               tCfgReq->ueId, cfgCfm->ueId), 2);
      KW_FREE_ACC(cfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (cfgCfm->cellId != tCfgReq->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlCpjValdtCfgCfm():Failed : cellID MisMatch: exp (%d) rcvd (%d) \n",\
               tCfgReq->cellId, cfgCfm->cellId), 2);
      KW_FREE_ACC(cfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (cfgCfm->numEnt != tCfgReq->numEnt)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlCpjValdtCfgCfm():Failed : numEnt MisMatch: exp (%d) rcvd (%d) \n",\
               tCfgReq->numEnt, cfgCfm->numEnt), 2);
      KW_FREE_ACC(cfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   for (idx = 0; idx < cfgCfm->numEnt; idx++)
   {
      if (cfgCfm->cfmEnt[idx].rbId != tCfgReq->cfgEnt[idx].rbId)
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlCpjValdtCfgCfm():Failed : rbId MisMatch: idx (%d) exp (%d) rcvd (%d) \n",\
                  idx, tCfgReq->cfgEnt[idx].rbId, cfgCfm->cfmEnt[idx].rbId), 2);
         KW_FREE_ACC(cfgCfm, sizeof(CpjCfgCfm));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (cfgCfm->cfmEnt[idx].status != status[idx])
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlCpjValdtCfgCfm():Failed : Status MisMatch: idx (%d) exp (%d) rcvd (%d) \n",\
                  idx, status[idx], cfgCfm->cfmEnt[idx].status), 2);
         KW_FREE_ACC(cfgCfm, sizeof(CpjCfgCfm));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if ((status[idx] != CPJ_CFG_CFM_NOK) &&\
            (cfgCfm->cfmEnt[idx].reason != reason[idx]))
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlCpjValdtCfgCfm():Failed : Reason MisMatch: idx (%d) exp (%d) rcvd (%d) \n",\
                  idx, reason[idx], cfgCfm->cfmEnt[idx].reason), 2);
         KW_FREE_ACC(cfgCfm, sizeof(CpjCfgCfm));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }
   }

   CMXTA_ZERO(acCfgReq, sizeof(KwAcCpjCfgReq));
   kwAcUtlCpjCircQDequeue(&kwAcCb.nhCpjCb.cfgReq);

   KW_FREE_ACC(cfgCfm, sizeof(CpjCfgCfm));

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlCpjValdtCfgCfm */


/**
 * @brief Build Re-establishment Request
 *
 * @details
 *
 *     Function : kwAcUtlCpjBuildReEstReq
 *
 *     This function fills CpjCfgInfo structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *reEstReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlCpjBuildReEstReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CpjReEstReqInfo  *reEstReq
)
#else
PUBLIC S16 kwAcUtlCpjBuildReEstReq(tcCb, spCb, reEstReq)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CpjReEstReqInfo  *reEstReq;
#endif
{
   U8             intkey[50];
   U8             ctrlplnkey[50];
   U8             usrplnkey[50];
   U8             idx, idx2;
   U16            transId = 0;
   Bool      cipInitFail = FALSE;
   Bool      intInitFail = FALSE;

   TRC2(kwAcUtlCpjBuildReEstReq);

   CMXTA_ZERO(intkey, sizeof(intkey));
   CMXTA_ZERO(ctrlplnkey, sizeof(ctrlplnkey));
   CMXTA_ZERO(usrplnkey, sizeof(usrplnkey));

   /* <tapa.cpj.reestreq ueId="0" cellId="1" rbId="1"
    * rbType="0"
    * intkey=""
    * ctrlplnkey=""
    * usrplnkey=""
    * />
    */

   /* Fill reEstReq from XML */
   /* UE ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",\
         &(reEstReq->pdcpId.ueId));

   /* CELL ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",
         &(reEstReq->pdcpId.cellId));

   /* RB ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId",
         &(reEstReq->pdcpId.rbId));

   /* RB Type */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType",
         &(reEstReq->pdcpId.rbType));

   /* Integrity Key */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "intkey", (intkey));

   /* Control Plane Cipher Key */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "ctrlplnkey", (ctrlplnkey));

   /* Data Plane Cipher Key */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "usrplnkey", (usrplnkey));

   for (idx = 0, idx2 = 0; idx < 2 * CPJ_CIPHER_KEY_LEN; idx++)
   {
      PJ_CPJ_UTL_SETKEY_BITS(reEstReq->usrplnKey[idx2], usrplnkey[idx], idx);
      PJ_CPJ_UTL_SETKEY_BITS(reEstReq->ctrlplnKey[idx2], ctrlplnkey[idx], idx);
      PJ_CPJ_UTL_SETKEY_BITS(reEstReq->intKey[idx2], intkey[idx], idx);

      if (idx % 2 == 1)
         idx2++;
   }

   transId = kwAcCb.nhCpjCb.nxtTransId;
   /*cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "transId", &(transId)); */
   reEstReq->transId = transId;

   /* Security Configuration Fail */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cipInitFail", &(cipInitFail));
   kwAcCb.nhCpjCb.cipInitFail = cipInitFail;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "intInitFail", &(intInitFail));
   kwAcCb.nhCpjCb.intInitFail = intInitFail;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpjBuildReEstReq */


/**
 * @brief Validate Re-establishment Confirmation
 *
 * @details
 *
 *     Function : kwAcUtlValdtReEstCfm
 *
 *     This function Validates CpjCfgCfm structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *reEstCfm
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtReEstCfm
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
CpjReEstCfmInfo   *reEstCfm
)
#else
PUBLIC S16 kwAcUtlValdtReEstCfm(tcCb, spCb, reEstCfm)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
CpjReEstCfmInfo   *reEstCfm;
#endif
{
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U16            status;
   U16            reason;
   U32            transId;

   TRC2(kwAcUtlValdtReEstCfm);

   /* Memset to 0 all local arrays */
   ueId = 0;
   cellId = 0;
   status = 0;
   reason = 0;
   transId = 0;

   /* <tapa.cpj.reestcfm ueId="0" cellId="1"
    * rbId="1"
    * rbType="0"
    * status="1"
    * reason="0"
    * />
    */

   /* Fill cfgReq from XML */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   /* Status */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status", &(status));

   /* TransId */
   /* cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "transId",
    * &(transId)); */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));

   if ((reEstCfm->transId != transId) && ((S32)transId != -1))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtReEstCfm():Failed : transId MisMatch: exp (%ld) rcvd (%ld) \n",\
               reEstCfm->transId, transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtReEstCfm():Failed : transId MisMatch: exp (%d) rcvd (%d) \n",\
               reEstCfm->transId, transId), 2);
#endif
      KW_FREE_ACC(reEstCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (reEstCfm->ueId != ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtReEstCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",\
               reEstCfm->ueId, ueId), 2);
      KW_FREE_ACC(reEstCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (reEstCfm->cellId != cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtReEstCfm():Failed : cellID MisMatch: exp (%d) rcvd (%d) \n",\
               reEstCfm->cellId, cellId), 2);
      KW_FREE_ACC(reEstCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (reEstCfm->status != status)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtReEstCfm():Failed : status MisMatch: exp (%d) rcvd (%d) \n",\
               reEstCfm->status, status), 2);
      KW_FREE_ACC(reEstCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   KW_FREE_ACC(reEstCfm, sizeof(CpjReEstCfmInfo));

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtReEstCfm */


/**
 * @brief Build Security Configuration Request
 *
 * @details
 *
 *     Function : kwAcUtlCpjBuildSecCfgReq
 *
 *     This function fills CpjCfgInfo structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *secCfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlCpjBuildSecCfgReq
(
CmXtaTCCb          *tcCb,
CmXtaSpCb          *spCb,
CpjSecCfgReqInfo   *secCfgReq
)
#else
PUBLIC S16 kwAcUtlCpjBuildSecCfgReq(tcCb, spCb, secCfgReq)
CmXtaTCCb          *tcCb;
CmXtaSpCb          *spCb;
CpjSecCfgReqInfo   *secCfgReq;
#endif
{
   U8        intkey[50];
   U8        ctrlplnkey[50];
   U8        usrplnkey[50];
   U8        idx, idx2;
   Bool      cipInitFail = FALSE;
   Bool      intInitFail = FALSE;
   U16       transId = 0;

   TRC2(kwAcUtlCpjBuildSecCfgReq);

   CMXTA_ZERO(intkey, sizeof(intkey));
   CMXTA_ZERO(ctrlplnkey, sizeof(ctrlplnkey));
   CMXTA_ZERO(usrplnkey, sizeof(usrplnkey));

   /* <tapa.cpj.seccfgreq ueId="0" cellId="1"
    * selSecAct="TRUE"
    * intalgoType="1"
    * intkey=""
    * ciphalgoType="1"
    * ctrlplnkey=""
    * usrplnkey=""
    * cipInitFail="0"
    * intInitFail="0"
    * />
    */

   /* Fill secCfgReq from XML */
   /* UE ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(secCfgReq->ueId));

   /* CELL ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(secCfgReq->cellId));

   /* Selective Security Active */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "selSecAct", &(secCfgReq->secCfg.selSecAct));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "selSecAct0", &(secCfgReq->secCfg.selSecAct));

   /* Integrity algorithm type */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "intalgoType", &(secCfgReq->secCfg.integInfo.algoType));

   /* Integrity Key */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "intkey", (intkey));

   /* Ciphering algorithm type */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ciphalgoType", &(secCfgReq->secCfg.cipherInfo.algoType));

   /* Control Plane Cipher Key */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "ctrlplnkey", (ctrlplnkey));

   /* Data Plane Cipher Key */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "usrplnkey", (usrplnkey));

   for (idx = 0, idx2 = 0; idx < 2 * CPJ_CIPHER_KEY_LEN; idx++)
   {
      PJ_CPJ_UTL_SETKEY_BITS(secCfgReq->secCfg.cipherInfo.usrplnKey[idx2], usrplnkey[idx], idx);
      PJ_CPJ_UTL_SETKEY_BITS(secCfgReq->secCfg.cipherInfo.ctrlplnKey[idx2], ctrlplnkey[idx], idx);
      PJ_CPJ_UTL_SETKEY_BITS(secCfgReq->secCfg.integInfo.intKey[idx2], intkey[idx], idx);

      if (idx % 2 == 1)
         idx2++;
   }

   /* trans ID */
   transId = kwAcCb.nhCpjCb.nxtTransId;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "transId", &(transId));
   secCfgReq->transId = transId;

   /* Security Configuration Fail */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cipInitFail", &(cipInitFail));
   kwAcCb.nhCpjCb.cipInitFail = cipInitFail;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "intInitFail", &(intInitFail));
   kwAcCb.nhCpjCb.intInitFail = intInitFail;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpjBuildSecCfgReq */


/**
 * @brief Validate Security Configuration Confirmation
 *
 * @details
 *
 *     Function : kwAcUtlValdtSecCfgCfm
 *
 *     This function Validates CpjCfgCfm structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *secCfgCfm
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtSecCfgCfm
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
CpjSecCfgCfmInfo  *secCfgCfm
)
#else
PUBLIC S16 kwAcUtlValdtSecCfgCfm(tcCb, spCb, secCfgCfm)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
CpjSecCfgCfmInfo  *secCfgCfm;
#endif
{
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U16            status;
   U16            reason;
   U32            transId;

   TRC2(kwAcUtlValdtSecCfgCfm);

   /* Memset to 0 all local arrays */
   ueId = 0;
   cellId = 0;
   status = 0;
   reason = 0;
   transId = 0;

   /* <tapa.cpj.seccfgcfm ueId="0" cellId="1" numEnt="5"
    * rbId="1:2:3:4:5"
    *
    * status="0:0:0:0:1"
    * reason="0:0:0:0:5"
    * />
    */

   /* Fill cfgReq from XML */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   /* Status */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status", &(status));

   /* Reason */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "reason", &(reason));

   /* TransId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));
   if (secCfgCfm->transId != transId)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSecCfgCfm():Failed : transId MisMatch: exp (%ld) rcvd (%ld) \n",\
               transId, secCfgCfm->transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSecCfgCfm():Failed : transId MisMatch: exp (%d) rcvd (%d) \n",\
               transId, secCfgCfm->transId), 2);
#endif
      KW_FREE_ACC(secCfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (secCfgCfm->ueId != ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSecCfgCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",\
               ueId, secCfgCfm->ueId), 2);
      KW_FREE_ACC(secCfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (secCfgCfm->cellId != cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSecCfgCfm():Failed : cellID MisMatch: exp (%d) rcvd (%d) \n",\
               cellId, secCfgCfm->cellId), 2);
      KW_FREE_ACC(secCfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (secCfgCfm->status != status)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSecCfgCfm():Failed : status MisMatch: exp (%d) rcvd (%d) \n",\
               status, secCfgCfm->status), 2);
      KW_FREE_ACC(secCfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (secCfgCfm->reason != reason)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSecCfgCfm():Failed : reason MisMatch: exp (%d) rcvd (%d) \n",\
               reason, secCfgCfm->reason), 2);
      KW_FREE_ACC(secCfgCfm, sizeof(CpjCfgCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   KW_FREE_ACC(secCfgCfm, sizeof(CpjSecCfgCfm));

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtSecCfgCfm */


/**
 * @brief Build UeId Change Request
 *
 * @details
 *
 *     Function : kwAcUtlCpjBuildUeIdChgReq
 *
 *     This function fills CpjUeInfo structure for old and new
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
PUBLIC S16 kwAcUtlCpjBuildUeIdChgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CpjUeInfo    *ueInfo,
CpjUeInfo    *newUeInfo
)
#else
PUBLIC S16 kwAcUtlCpjBuildUeIdChgReq(tcCb, spCb, ueInfo, newUeInfo)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CpjUeInfo    *ueInfo;
CpjUeInfo    *newUeInfo;
#endif
{
   TRC2(kwAcUtlCpjBuildUeIdChgReq);

   /* <tapa.cpj.ueidchgreq transid="1" ueId="1" cellId="1" newUeId="2" newCellId="1"
    * />
    */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueInfo->ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(ueInfo->cellId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "newUeId", &(newUeInfo->ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "newCellId", &(newUeInfo->cellId));

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpjBuildUeIdChgReq */


/**
 * @brief Build Count Report Request
 *
 * @details
 *
 *     Function : kwAcUtlCpjBuildCountReq
 *
 *     This function fills CpjCountReq structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *countReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlCpjBuildCountReq
(
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjCountReqInfo *countReq
)
#else
PUBLIC S16 kwAcUtlCpjBuildCountReq(tcCb, spCb, countReq)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
CpjCountReqInfo *countReq;
#endif
{

   TRC2(kwAcUtlCpjBuildCountReq);

   /* <tapa.cpj.countreq ueId="0" cellId="1"
    * />
    */

   /* Fill countReq from XML */
   /* UE ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(countReq->ueId));

   /* CELL ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(countReq->cellId));

   countReq->transId = kwAcCb.nhCpjCb.nxtTransId;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpjBuildCountReq */


/**
 * @brief Validate Count Confirmation
 *
 * @details
 *
 *     Function : kwAcUtlValdtCountCfm
 *
 *     This function Validates CpjCountCfmInfo structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *countInfo
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtCountCfm
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
CpjCountCfmInfo  *countCfm
)
#else
PUBLIC S16 kwAcUtlValdtCountCfm(tcCb, spCb, countCfm)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
CpjCountCfmInfo  *countCfm;
#endif
{
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U16            status;
   U16            reason;
   U32            transId;
   U8             idx;
   U8             numRb;
   U8             rbId[CPJ_MAX_DRB];
   U8             dir[CPJ_MAX_DRB];
   U32            ulcount[CPJ_MAX_DRB];
   U32            dlcount[CPJ_MAX_DRB];

   TRC2(kwAcUtlValdtCountCfm);

   /* Memset to 0 all local arrays */
   ueId = 0;
   cellId = 0;
   status = 0;
   reason = 0;
   transId = 0;
   numRb = 0;

   CMXTA_ZERO(rbId, sizeof(rbId));
   CMXTA_ZERO(dir, sizeof(dir));
   CMXTA_ZERO(ulcount, sizeof(ulcount));
   CMXTA_ZERO(dlcount, sizeof(dlcount));

   /* <tapa.cpj.countcfm ueId="0" cellId="1" numRb="5"
    * rbId="1:2:3:4:5"
    * dir="1:1:1:1:1"
    * status="0:0:0:0:1"
    * reason="0:0:0:0:5"
    * transId="1"
    * ulcount="1:1:1:1:1"
    * dlcount="1:1:1:1:1"
    * />
    */

   /* Fill cfgReq from XML */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   /* Status */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status", &(status));

   /* Reason */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "reason", &(reason));

   /* TransId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));

   /* numRb */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numRb", &(numRb));

   /* RB ID */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "rbId", rbId, &numRb);

   /* DIR */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "dir", dir, &numRb);

   /* ulCount */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,\
         "ulcount", ulcount, &numRb);
   /* dlCount */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,\
         "dlcount", dlcount, &numRb);


   if (countCfm->transId != transId)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCountCfm():Failed : transId MisMatch: exp (%ld) rcvd (%ld) \n",\
               countCfm->transId, transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCountCfm():Failed : transId MisMatch: exp (%d) rcvd (%d) \n",\
               countCfm->transId, transId), 2);
#endif
      KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (countCfm->ueId != ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCountCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",\
               countCfm->ueId, ueId), 2);
      KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (countCfm->cellId != cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCountCfm():Failed : cellID MisMatch: exp (%d) rcvd (%d) \n",\
               countCfm->cellId, cellId), 2);
      KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (countCfm->status != status)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCountCfm():Failed : status MisMatch: exp (%d) rcvd (%d) \n",\
               countCfm->status, status), 2);
      KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (countCfm->reason != reason)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCountCfm():Failed : reason MisMatch: exp (%d) rcvd (%d) \n",\
               countCfm->reason, reason), 2);
      KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (countCfm->numRb != numRb)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtCountCfm():Failed : numRb MisMatch: exp (%d) rcvd (%d) \n",\
               countCfm->numRb, numRb), 2);
      KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   for (idx = 0; idx < numRb; idx++)
   {
      if (countCfm->countInfo[idx].rbId != rbId[idx])
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCountCfm():Failed : rbId MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  countCfm->countInfo[idx].rbId, rbId[idx], idx), 2);
         KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (countCfm->countInfo[idx].dir != dir[idx])
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCountCfm():Failed : dir MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  countCfm->countInfo[idx].dir, dir[idx], idx), 2);
         KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (countCfm->countInfo[idx].ulCount != ulcount[idx])
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCountCfm():Failed : ulCount MisMatch: exp (%ld) rcvd (%ld) index (%d)\n",\
                  countCfm->countInfo[idx].ulCount, ulcount[idx], idx), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCountCfm():Failed : ulCount MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  countCfm->countInfo[idx].ulCount, ulcount[idx], idx), 2);
#endif
         KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (countCfm->countInfo[idx].dlCount != dlcount[idx])
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCountCfm():Failed : dlCount MisMatch: exp (%ld) rcvd (%ld) index (%d)\n",\
                  countCfm->countInfo[idx].dlCount, dlcount[idx], idx), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtCountCfm():Failed : dlCount MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  countCfm->countInfo[idx].dlCount, dlcount[idx], idx), 2);
#endif
         KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }
   }

   KW_FREE_ACC(countCfm, sizeof(CpjCountCfm));

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtCountCfm */


/**
 * @brief Build SDU Status Report Request
 *
 * @details
 *
 *     Function : kwAcUtlCpjBuildSduStaReq
 *
 *     This function fills CpjSduStaReq structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *sduStaReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlCpjBuildSduStaReq
(
CmXtaTCCb          *tcCb,
CmXtaSpCb          *spCb,
CpjSduStaReqInfo   *sduStaReq
)
#else
PUBLIC S16 kwAcUtlCpjBuildSduStaReq(tcCb, spCb, sduStaReq)
CmXtaTCCb          *tcCb;
CmXtaSpCb          *spCb;
CpjSduStaReqInfo   *sduStaReq;
#endif
{

   TRC2(kwAcUtlCpjBuildSduStaReq);

   /* <tapa.cpj.sdustareq ueId="0" cellId="1"
    * />
    */

   /* Fill sduStaReq from XML */
   /* UE ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(sduStaReq->ueId));

   /* CELL ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(sduStaReq->cellId));

   sduStaReq->transId = kwAcCb.nhCpjCb.nxtTransId;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpjBuildSduStaReq */


/**
 * @brief Validate SDU Status Report Confirmation
 *
 * @details
 *
 *     Function : kwAcUtlValdtSduStaCfm
 *
 *     This function Validates CpjSduStaCfmInfo structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *sduStaCfm
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtSduStaCfm
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
CpjSduStaCfmInfo  *sduStaCfm
)
#else
PUBLIC S16 kwAcUtlValdtSduStaCfm(tcCb, spCb, sduStaCfm)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
CpjSduStaCfmInfo  *sduStaCfm;
#endif
{
   U8             idx;
   U8             numRb;
   U8             tnumRb;
   U8             rbId[CPJ_MAX_DRB];
   U8             dir[CPJ_MAX_DRB];
   U8             ulnumelm[CPJ_MAX_DRB];
   U8             ulstapdu[CPJ_MAX_DRB][100];
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U16            status;
   U16            reason;
   U32            transId;
   U32            ulcount[CPJ_MAX_DRB];
   U32            dlcount[CPJ_MAX_DRB];
   U8             numBytes;

   TRC2(kwAcUtlValdtSduStaCfm);

   /* Memset to 0 all local arrays */
   ueId = 0;
   cellId = 0;
   status = 0;
   reason = 0;
   transId = 0;
   numRb = 0;
   tnumRb = 0;
   numBytes = 0;

   CMXTA_ZERO(rbId, sizeof(rbId));
   CMXTA_ZERO(dir, sizeof(dir));
   CMXTA_ZERO(ulcount, sizeof(ulcount));
   CMXTA_ZERO(dlcount, sizeof(dlcount));
   CMXTA_ZERO(ulstapdu, sizeof(ulstapdu));

   /* <tapa.cpj.reestcfm ueId="0" cellId="1" numRb="5"
    * rbId="1:2:3:4:5"
    * dir="1:1:1:1:1"
    * status="0:0:0:0:1"
    * reason="0:0:0:0:5"
    * transId="1"
    * ulcount="1:1:1:1:1"
    * dlcount="1:1:1:1:1"
    * />
    */

   /* Fill cfgReq from XML */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   /* numRb */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numRb", &(numRb));

   /* Status */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status", &(status));

   /* Reason */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "reason", &(reason));

   /* TransId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));

   /* RB ID */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "rbId", rbId, &tnumRb);

   /* DIR */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "dir", dir, &tnumRb);

   /* ulnumelm */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "ulnumelm", ulnumelm, &tnumRb);

   /* ulStaPdu */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, CMXTA_SEP_COLON,\
         "ulstapdu", ulstapdu, &tnumRb);

   /* ulcount */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,\
         "ulcount", ulcount, &tnumRb);

   /* dlCount */
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,\
         "dlcount", dlcount, &tnumRb);


   if (sduStaCfm->transId != transId)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSduStaCfm():Failed : transId MisMatch: exp (%ld) rcvd (%ld) \n",\
               sduStaCfm->transId, transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSduStaCfm():Failed : transId MisMatch: exp (%d) rcvd (%d) \n",\
               sduStaCfm->transId, transId), 2);
#endif
      KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (sduStaCfm->ueId != ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSduStaCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",\
               sduStaCfm->ueId, ueId), 2);
      KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (sduStaCfm->cellId != cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSduStaCfm():Failed : cellID MisMatch: exp (%d) rcvd (%d) \n",\
               sduStaCfm->cellId, cellId), 2);
      KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (sduStaCfm->status != status)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSduStaCfm():Failed : status MisMatch: exp (%d) rcvd (%d) \n",\
               status, sduStaCfm->status), 2);
      KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (sduStaCfm->reason != reason)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSduStaCfm():Failed : reason MisMatch: exp (%d) rcvd (%d) \n",\
               sduStaCfm->reason, reason), 2);
      KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if (status == LCM_PRIM_NOK)
   {
      KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
      RETVALUE(CMXTA_ERR_NONE);
   }

   if (sduStaCfm->numRb != numRb)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlValdtSduStaCfm():Failed : numRb MisMatch: exp (%d) rcvd (%d) \n",\
               numRb, sduStaCfm->numRb), 2);
      KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   for (idx = 0; idx < numRb; idx++)
   {
      if (sduStaCfm->sduStaInfo[idx].rbId != rbId[idx])
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtSduStaCfm():Failed : rbId MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  rbId[idx], sduStaCfm->sduStaInfo[idx].rbId, idx), 2);
         KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (sduStaCfm->sduStaInfo[idx].dir != dir[idx])
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtSduStaCfm():Failed : dir MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  dir[idx], sduStaCfm->sduStaInfo[idx].dir, idx), 2);
         KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (sduStaCfm->sduStaInfo[idx].ulSduStaInfo.numBits != ulnumelm[idx])
      {
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtSduStaCfm():Failed : numBits MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  ulnumelm[idx], sduStaCfm->sduStaInfo[idx].ulSduStaInfo.numBits, idx), 2);
         KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      /* Convert ulstapdu to ulBitMap for comparision */
      {
         U8 i;
         U8 cnt = 0;
         U8 ulBitMap[CPJ_MAX_DRB];

         CMXTA_ZERO(ulBitMap, sizeof(ulBitMap));
         if (sduStaCfm->sduStaInfo[idx].ulSduStaInfo.numBits % 8 == 0)
         {
            numBytes = sduStaCfm->sduStaInfo[idx].ulSduStaInfo.numBits / 8;
         }
         else
         {
            numBytes = (sduStaCfm->sduStaInfo[idx].ulSduStaInfo.numBits / 8) + 1;
         }

         for (i = 0, cnt = 0; i < 2 * numBytes; i++)
         {
            PJ_CPJ_UTL_SETKEY_BITS(ulBitMap[cnt], ulstapdu[idx][i], i);

            if (i % 2 == 1)
               cnt++;
         }

         for (i = 0; i < numBytes; i++)
         {
            if (sduStaCfm->sduStaInfo[idx].ulSduStaInfo.ulBitMap[i] != ulBitMap[i])
            {
               CMXTA_DBG_CALLIND((_cmxtap,\
                        "kwAcUtlValdtSduStaCfm():Failed : staPdu MisMatch: exp (%d) rcvd (%d) index (%d) Byet (%d)\n",\
                        ulBitMap[i], sduStaCfm->sduStaInfo[idx].ulSduStaInfo.ulBitMap[i], idx, i), 2);
               KW_FREE_ACC(sduStaCfm->sduStaInfo[idx].ulSduStaInfo.ulBitMap, numBytes);
               KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
               RETVALUE(CMXTA_ERR_NOMATCH);
            }
         }
      }

      if (sduStaCfm->sduStaInfo[idx].ulSduStaInfo.count != ulcount[idx])
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtSduStaCfm():Failed : ulCount MisMatch: exp (%ld) rcvd (%ld) index (%d)\n",\
                  ulcount[idx], sduStaCfm->sduStaInfo[idx].ulSduStaInfo.count, idx), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtSduStaCfm():Failed : ulCount MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  ulcount[idx], sduStaCfm->sduStaInfo[idx].ulSduStaInfo.count, idx), 2);
#endif
         KW_FREE_ACC(sduStaCfm->sduStaInfo[idx].ulSduStaInfo.ulBitMap, numBytes);
         KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      if (sduStaCfm->sduStaInfo[idx].dlSduStaInfo.count != dlcount[idx])
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtSduStaCfm():Failed : dlCount MisMatch: exp (%ld) rcvd (%ld) index (%d)\n",\
                  dlcount[idx], sduStaCfm->sduStaInfo[idx].dlSduStaInfo.count, idx), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,\
                  "kwAcUtlValdtSduStaCfm():Failed : dlCount MisMatch: exp (%d) rcvd (%d) index (%d)\n",\
                  dlcount[idx], sduStaCfm->sduStaInfo[idx].dlSduStaInfo.count, idx), 2);
#endif
         KW_FREE_ACC(sduStaCfm->sduStaInfo[idx].ulSduStaInfo.ulBitMap, numBytes);
         KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));
         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      KW_FREE_ACC(sduStaCfm->sduStaInfo[idx].ulSduStaInfo.ulBitMap, numBytes);
   }

   KW_FREE_ACC(sduStaCfm, sizeof(CpjSduStaCfmInfo));

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtSduStaCfm */


/**
 * @brief XTA Function to free resources aquired by the interface messages
 * received from RLC to Dummy-RRC.
 *
 * @details
 *
 *     Function : kwAcUtlFreeCpjCb
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
PUBLIC S16 kwAcUtlCpjFreeCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 kwAcUtlCpjFreeCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwElm;
   KwAcCpjInfo  *cpjInfo = NULLP; 
 
   TRC2(kwAcUtlCpjFreeCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlCpjFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   kwElm = (KwAcMsgQElm *)qElm->data;
  
   if(kwElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   cpjInfo = &(kwElm->u.cpjInfo);
   
   if (kwElm != NULLP)
   {
      if(kwElm->mBuf != NULLP)
         CMXTA_FREEMBUF(kwElm->mBuf);

      CMXTA_FREE(kwElm, sizeof (KwAcMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of kwAcUtlCpjFreeCb */

/*************************************************************************
 *                CPJ CFG REQ QUEUE PRIMITIVES START
 *************************************************************************/
  
/**
 * @brief Circular Queue for CPJ Interface
 *
 * @details
 *
 *     Function : kwAcUtlCpjCQMakeNull
 *
 *     This function Initializes the CPJ Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlCpjCQMakeNull
(
KwAcCpjCfgReqQ    *queue
)
#else
PUBLIC Void kwAcUtlCpjCQMakeNull(queue)
KwAcCpjCfgReqQ    *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtilCircQMakeNull */

#ifdef ANSI
PUBLIC U16 kwAcUtlCpjCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlCpjCircQAddOne(idx)
U16 idx;
#endif
{
   /* 0xFF below is KWAC_MAX_CIRCQ_SIZE(currently 128) - 1 */
   if (idx == 0x7F)
      RETVALUE(1);
   else
   RETVALUE((idx + 1) & 0x7F);
} /* kwAcUtlCpjCircQAddOne */

#ifdef ANSI
PUBLIC U16 kwAcUtlCpjCircQEnqueue
(
KwAcCpjCfgReqQ *queue
)
#else
PUBLIC U16 kwAcUtlCpjCircQEnqueue(queue)
KwAcCpjCfgReqQ *queue;
#endif
{
   /* Making 3 length difference between rear and front to make
    * sure Q is full
    */
   if(kwAcUtlCpjCircQAddOne(kwAcUtlCpjCircQAddOne(
               kwAcUtlCpjCircQAddOne(queue->rear))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlCpjCircQEnqueue(): CPJ Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlCpjCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlCpjCircQEnqueue */

#ifdef ANSI
PUBLIC U16 kwAcUtlCpjCircQGetFront
(
KwAcCpjCfgReqQ *queue
)
#else
PUBLIC U16 kwAcUtlCpjCircQGetFront(queue)
KwAcCpjCfgReqQ *queue;
#endif
{
   if(KWAC_UTL_CPJ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlCpjCircQGetFront(): CPJ Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlCpjCircQGetFront */

#ifdef ANSI
PUBLIC U16 kwAcUtlCpjCircQGetNext
(
KwAcCpjCfgReqQ   *queue,
U16            idx
)
#else
PUBLIC U16 kwAcUtlCpjCircQGetNext(queue, idx)
KwAcCpjCfgReqQ   *queue;
U16            idx;
#endif
{
   if (kwAcUtlCpjCircQAddOne(idx) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,\
               "kwAcUtlCpjCircQGetNext(): CPJ Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlCpjCircQAddOne(queue->front));
} /* kwAcUtlCpjCircQGetNext */

#ifdef ANSI
PUBLIC Void kwAcUtlCpjCircQDequeue
(
KwAcCpjCfgReqQ *queue
)
#else
PUBLIC Void kwAcUtlCpjCircQDequeue(queue)
KwAcCpjCfgReqQ *queue;
#endif
{
   if(KWAC_UTL_CPJ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlCpjCircQDequeue(): CPJ Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlCpjCircQAddOne(queue->front);
      if(KWAC_UTL_CPJ_CQ_ISEMPTY(queue))
         break;
   }

   RETVOID;
} /* kwAcUtlCpjCircQDequeue */

#endif /* KW_PDCP */
/*************************************************************************
 *                CPJ CFG REQ QUEUE PRIMITIVES END
 *************************************************************************/

/********************************************************************30**
         End of file:     kwac_cpjutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:25 2014
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
/main/1      ---      gk         1. LTERLC Release 2.1.
/main/2    kw005.201  ap         1. Added support for L2 Measurement.
*********************************************************************91*/

