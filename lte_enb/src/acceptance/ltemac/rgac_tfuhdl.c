


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      rgac_tfuhdl.c@@/main/3 - Sat Jul 30 02:21:08 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/

#include "rg.h"
#include "rg_env.h"
#include "rgac_acc.x"
#include "rgac_acc.h"

EXTERN S16 rgAcUtlPfsSimSendBoUpdt();
EXTERN Bool startPfsSim;

PUBLIC S16 rgAcUtlTfuGetToSchPst ARGS((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb,
         Pst         *pst));


/** @brief This function is the handler function for the TFU bind request.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuBndReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuBndReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   Pst            pst;
   SuId           suId;
   SpId           spId;
   ProcId         srcProcId;
   ProcId         dstProcId;
   CmXtaMsgQElm   *qElm;
   RgAccMsgQElm   *rgQElm;
   S16            ret;
   U8             instId=0;

   TRC2 (rgAcHdlTfuBndReq)

   qElm     = NULLP;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuBndReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuBndReq(), tcId(%d)\n", tcCb->tcId));
#endif

   /* This function shall validate the Bind Request received from MAC. It should
    * check things like SAP id and PST 
    */
   if (ROK != cmXtaPeekMsg (&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlTfuBndReq() cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /* Extract the stored message from the tcCb message queue */

   rgQElm = (RgAccMsgQElm *)qElm->data;

   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId", &instId);
   /* Now get the value of the pst based on the profile selected */
   cmXtaGetPst(&pst, ENTRG, instId, ENTTF, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   suId = 0;
   spId = 0;
   pst.event = EVTTFUBNDREQ;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &spId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId", &suId);

   ret = cmXtaValidatePst (&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /* Remove the msg from the tcCb message queue */
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
   if (spId != rgQElm->u.tfuInfo.spId)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuBndReq() : Failed spId MisMatch: exp (%d) received (%d) \n", 
            spId, rgQElm->u.tfuInfo.spId));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Flush the message in the test case queue */
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuBndReq */

/** @brief This function is the handler function for the TFU bind request.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuSchBndReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuSchBndReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   Pst            pst;
   SuId           suId;
   SpId           spId;
   ProcId         srcProcId;
   ProcId         dstProcId;
   CmXtaMsgQElm   *qElm;
   RgAccMsgQElm   *rgQElm;
   S16            ret;
   U8             instId;

   TRC2 (rgAcHdlTfuSchBndReq)

   qElm     = NULLP;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSchBndReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSchBndReq(), tcId(%d)\n", tcCb->tcId));
#endif

   /* This function shall validate the Bind Request received from MAC. It should
    * check things like SAP id and PST 
    */
   if (ROK != cmXtaPeekMsg (&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlTfuSchBndReq() cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /* Extract the stored message from the tcCb message queue */

   rgQElm = (RgAccMsgQElm *)qElm->data;

   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);

   instId = RGSCH_INST_START;
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId", &instId);

   /* Now get the value of the pst based on the profile selected */
   cmXtaGetPst(&pst, ENTRG, instId, ENTTF, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   suId = 0;
   spId = 0;
   pst.event = EVTTFUSCHBNDREQ;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &spId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId", &suId);

   ret = cmXtaValidatePst (&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuSchBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /* Remove the msg from the tcCb message queue */
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
   if (spId != rgQElm->u.tfuInfo.spId)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuSchBndReq() : Failed spId MisMatch: exp (%d) received (%d) \n", 
            spId, rgQElm->u.tfuInfo.spId));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Flush the message in the test case queue */
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuSchBndReq */


/** @brief This function is the handler function for the TFU bind Confirm.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuBndCfm
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuBndCfm (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   Pst            pst;
   SuId           suId;      /* service user SAP identifier */
   ProcId         srcProcId;
   ProcId         dstProcId;
   U8             status;
   Inst           instId = 0;

   TRC2(rgAcHdlTfuBndCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   /* Get the procId values from the xml test step */
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId", &instId);

   cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTRG, instId, srcProcId, dstProcId, FALSE);

   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   status = CM_BND_OK;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",  &(status));

   /* Now call the interface API towards MAC */
   TfUiTfuBndCfm (&pst, suId, status);
   RETVALUE(CMXTA_ERR_NONE);

} /* end of rgAcHdlTfuBndCfm */

/** @brief This function is the handler function for the TFU bind Confirm.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuSchBndCfm
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuSchBndCfm (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   Pst            pst;
   SuId           suId;      /* service user SAP identifier */
   ProcId         srcProcId;
   ProcId         dstProcId;
   U8             status;
   U8             instId;

   TRC2(rgAcHdlTfuSchBndCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSchBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSchBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   /* Get the procId values from the xml test step */
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   instId = RGSCH_INST_START;
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId", &instId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);
   cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTRG, instId, srcProcId, dstProcId, FALSE);

   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   status = CM_BND_OK;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",  &(status));

   /* Now call the interface API towards MAC */
   TfUiTfuSchBndCfm (&pst, suId, status);
   RETVALUE(CMXTA_ERR_NONE);

} /* end of rgAcHdlTfuSchBndCfm */


/** @brief This function is the handler function for the TFU unBind request.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuUBndReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuUBndReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   Pst            pst;
   SuId           suId;
   SpId           spId;
   ProcId         srcProcId;
   ProcId         dstProcId;
   CmXtaMsgQElm   *qElm;
   RgAccMsgQElm   *rgQElm;
   S16            ret;
   Inst           instId=0;

   TRC2 (rgAcHdlTfuUBndReq)

   qElm     = NULLP;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuUBndReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuUBndReq(), tcId(%d)\n", tcCb->tcId));
#endif

   /* This function shall validate the Bind Request received from MAC. It should
    * check things like SAP id and PST 
    */
   if (ROK != cmXtaPeekMsg (&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlTfuUBndReq() cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /* Extract the stored message from the tcCb message queue */
   rgQElm = (RgAccMsgQElm *)qElm->data;

   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId", &instId);

   /* Now get the value of the pst based on the profile selected */
   cmXtaGetPst(&pst, ENTRG, instId, ENTTF, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   pst.event = EVTTFUUBNDREQ; 

   suId = 0;
   spId = 0;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &spId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId", &suId);

   ret = cmXtaValidatePst (&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuUBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /* Remove the msg from the tcCb message queue */
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
   if (spId != rgQElm->u.tfuInfo.spId)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuUBndReq() : Failed spId MisMatch: exp (%d) received (%d) \n",
            spId, rgQElm->u.tfuInfo.spId));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Flush the message in the test case queue */
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuUBndReq */

/** @brief This function is the handler function for the TFU unBind request.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuSchUBndReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuSchUBndReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   Pst            pst;
   SuId           suId;
   SpId           spId;
   ProcId         srcProcId;
   ProcId         dstProcId;
   U8             instId=RGSCH_INST_START;
   CmXtaMsgQElm   *qElm;
   RgAccMsgQElm   *rgQElm;
   S16            ret;

   TRC2 (rgAcHdlTfuSchUBndReq)

   qElm     = NULLP;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSchUBndReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSchUBndReq(), tcId(%d)\n", tcCb->tcId));
#endif

   /* This function shall validate the Bind Request received from MAC. It should
    * check things like SAP id and PST 
    */
   if (ROK != cmXtaPeekMsg (&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlTfuSchUBndReq() cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /* Extract the stored message from the tcCb message queue */
   rgQElm = (RgAccMsgQElm *)qElm->data;

   CMXTA_ZERO(&pst, sizeof(Pst));

   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId", &instId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "srcProc", &srcProcId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "dstProc", &dstProcId);

   /* Now get the value of the pst based on the profile selected */
   cmXtaGetPst(&pst, ENTRG, instId, ENTTF, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   pst.event = EVTTFUSCHUBNDREQ; 

   suId = 0;
   spId = 0;

   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &spId);
   cmXtaXmlGetVal (tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId", &suId);

   ret = cmXtaValidatePst (&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuSchUBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /* Remove the msg from the tcCb message queue */
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
   if (spId != rgQElm->u.tfuInfo.spId)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuSchUBndReq() : Failed spId MisMatch: exp (%d) received (%d) \n",
            spId, rgQElm->u.tfuInfo.spId));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Flush the message in the test case queue */
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuUBndReq */


/** @brief This handler generates a Random Access Request indication towards the
 * scheduler. 
 *
 * @details
 * For TDD it is possible that multiple RA-RNTIs can arrive in a single
 * Subframe, a maximum of 6 RA-RNTIs per subframe is possible. This Handler
 * function is the top level handler for a Random access requests. Multiple
 * low-level RaReqs per RA-RNTIs shall help filling the whole structure. 
 * The final XML shall look something like this. 
 * 
 * <tapa.send>
 *    <tapa.tfu.rareq.ind numRaRntis="3">
 *       <tapa.tfu.rareq raRnti="22" numRapId="2" rapId="1:2" timingAdvs="2:2" tcps="3:1"/>
 *       <tapa.tfu.rareq raRnti="33" numRapId="1" rapId="5" timingAdvs="0" tcps="1"/>
 *       <tapa.tfu.rareq raRnti="44" numRapId="3" rapId="7:8:9" timingAdvs="2:2" tcps="3:1"/>
 *    </tapa.tfu.rareq.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - This is a high level handler function i.e. there shall be low-level
 *         commands embedded within this. Please look at the example of the
 *         usage given above. The idea here is that this handler shall call the
 *         low-level commands one by one, while passing a pointer to the commaon
 *         data structure to the low-level commands. The low level commands
 *         shall fill up data structure incrementally. Finally once all the
 *         low-level commands are done the structure should be fully filled and
 *         this handler shall call the interface primitive. 
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuRaReqInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuRaReqInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   Pst                  pst;
   SuId                 suId;      /* service user SAP identifier */
   TfuRaReqIndInfo      *raReqInd;
   S16                  ret;
   U8                   saveTime;

   TRC2(rgAcHdlTfuRaReqInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuRaReqInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuRaReqInd(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   if ((ret = rgAcUtlAllocEvnt ((Data**)&raReqInd, sizeof(TfuRaReqIndInfo))) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlTfuRaReqInd() Allocation failed.\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /* We call the utility function to populate the RaReqIndInfo structure. */
   if ((ret = rgAcUtlTfuBuildRaReqIndMsg (tcCb, spCb, &pst, 
               &suId, raReqInd)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)raReqInd);
      RETVALUE(ret);
   }

   /* At this point we have the structure filled and we are ready to call the
    * interface API.
    */
   TfUiTfuRaReqInd (&pst, suId, raReqInd);

   RETVALUE (CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuRaReqInd */

/** @brief This handler fills in TfuRaReqIndInfo structure for a single RA-RNTI
 *
 * @details
 * For TDD it is possible that multiple RA-RNTIs can arrive in a single
 * Subframe, a maximum of 6 RA-RNTIs per subframe is possible. This Handler
 * function is the top level handler for a Random access requests. Multiple
 * low-level RaReqs per RA-RNTIs shall help filling the whole structure. 
 * The final XML shall look something like this. 
 * 
 * <tapa.send>
 *    <tapa.tfu.rareq.ind numRaRntis="3">
 *       <tapa.tfu.rareq raRnti="22" numRapId="2" rapId="1:2" timingAdvs="2:2" tcps="3:1"/>
 *       <tapa.tfu.rareq raRnti="33" numRapId="1" rapId="5" timingAdvs="0" tcps="1"/>
 *       <tapa.tfu.rareq raRnti="44" numRapId="3" rapId="7:8:9" timingAdvs="2:2" tcps="3:1"/>
 *    </tapa.tfu.rareq.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - This is a low level handler function i.e. this is embedded within a
 *         higher level command <tapa.tfu.rareq.ind>.
 *         This hander must read one RA-RNTI and fill up the TfuRachInfo
 *         structure for that RA-RNTI. This would typically be a list of RAPIDs
 *         and corresponding to each RAP-ID there may be timing Advance values
 *         etc. 
 *         - This handler would get the RaReqInd structure from the tcCb.
 *         - Would fill in the valid values into the correct part of the data
 *         structure. 
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuRaReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuRaReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16                  ret;
   TfuRaReqIndInfo      *raReqInd;          

   TRC2(rgAcHdlTfuRaReq);

   ret = CMXTA_ERR_NONE;

   raReqInd = (TfuRaReqIndInfo *)tcCb->data;
   /* We call the utility function to populate the RaReqIndInfo structure. */
   if ((ret = rgAcUtlTfuBuildRaReq (tcCb, spCb, raReqInd)) != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }
   RETVALUE(ret);
} /* end of rgAcHdlTfuRaReq */





/** @brief This function is the lower-level handler meant to validate the PDCCH
 * control part of the control request sent from Scheduler to physical layer.
 *
 * @details
 * Validates the PDCCH value in the TfuCntrlReqInfo structure received from
 * scheduler.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the validate function for PDCCH.
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuPdcchCntrlReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuPdcchCntrlReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuCntrlReqInfo   *cntrlReq;

   TRC2(rgAcHdlTfuPdcchCntrlReq)

#ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPdcchCntrlReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPdcchCntrlReq(), tcId(%d)\n", tcCb->tcId));
#endif
   cntrlReq = (TfuCntrlReqInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuValidatePdcch (tcCb, spCb, 
               cntrlReq)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuPdcchCntrlReq */


/** @brief This function is the lower-level handler meant to validate the PHICH
 * control part of the control request sent from Scheduler to physical layer.
 *
 * @details
 * Validates the PHICH value in the TfuCntrlReqInfo structure received from
 * scheduler.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the validate function for PHICH.
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuPhichCntrlReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuPhichCntrlReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuCntrlReqInfo   *cntrlReq;

   TRC2(rgAcHdlTfuPhichCntrlReq)

#ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPhichCntrlReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPhichCntrlReq(), tcId(%d)\n", tcCb->tcId));
#endif
   cntrlReq = (TfuCntrlReqInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuValidatePhich (tcCb, spCb, 
               cntrlReq)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuPhichCntrlReq */


/** @brief This function is the lower-level handler meant to validate the CFI
 * control part of the control request sent from Scheduler to physical layer.
 *
 * @details
 * Validate the cfi value in the TfuCntrlReqInfo structure received from
 * scheduler.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the validate function for CFI.
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuCfiCntrlReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuCfiCntrlReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   TfuCntrlReqInfo   *cntrlReq;
   U8                cfi;

   TRC2(rgAcHdlTfuCfiCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuCfiCntrlReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuCfiCntrlReq(), tcId(%d)\n", tcCb->tcId));
#endif

   cntrlReq = (TfuCntrlReqInfo *)tcCb->data;
   cfi = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cfi",  &cfi);
   if (cfi != cntrlReq->cfi )
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcHdlTfuCfiCfgReq() : Failed CFI MisMatch: exp (%d) received (%d) \n", 
            cfi, cntrlReq->cfi));
      RETVALUE(CMXTA_ERR_INT);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuCfiCntrlReq */


/** @brief This function is the handler for TFU's control request from scheduler
 * to the physical layer.
 *
 * @details
 * This function is the high level handler for control request. Lower-level
 * handler functions would be responsible for filling in the structure. 
 *
 *     Function: 
 *
 *         Processing steps:
 *         - This is a high level handler function i.e. there shall be low-level
 *         commands embedded within this. Please look at the example of the
 *         usage given above. The idea here is that this handler shall call the
 *         low-level commands one by one, while passing a pointer to the commaon
 *         data structure to the low-level commands. The low level commands
 *         shall fill up data structure incrementally. Finally once all the
 *         low-level commands are done the structure should be fully filled and
 *         this handler shall call the interface primitive. 
 *
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuCntrlReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuCntrlReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16   ret;
   U8    saveTime;

   TRC2(rgAcHdlTfuCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuCntrlReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuCntrlReq(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   /* Fairly simple we shall call the single validation function from here with
    * the event type */
   if ((ret = rgAcUtlTfuValidateMsg (tcCb, spCb, 
               EVTTFUCNTRLREQ)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuCntrlReq */

/** @brief This function is the handler for TFU's Recpeption request from scheduler
 * to the physical layer.
 *
 * @details
 * This function is the high level handler for control request. Lower-level
 * handler functions would be responsible for validating the whole structure.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - This is a high level handler function i.e. there shall be low-level
 *         commands embedded within this. Please look at the example of the
 *         usage given above. The idea here is that this handler shall call the
 *         low-level commands one by one, while passing a pointer to the commaon
 *         data structure to the low-level commands. The low level commands
 *         shall fill up data structure incrementally. Finally once all the
 *         low-level commands are done the structure should be fully filled and
 *         this handler shall call the interface primitive. 
 *
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuRecpReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuRecpReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16   ret;
   U8    saveTime;

   TRC2(rgAcHdlTfuRecpReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuRecpReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuRecpReq(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   /* Fairly simple we shall call the single validation function from here with
    * the event type */
   if ((ret = rgAcUtlTfuValidateMsg (tcCb, spCb, 
               EVTTFURECPREQ)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuRecpReq */

/** @brief This function is the lower-level handler meant to validate the PUCCH
 * Reception request.
 *
 * @details
 * Validates the PUCCH Reception request from the Reception Request received
 * from the scheduler. 
 *
 *     Function: 
 *         Processing steps:
 *         - Calls the validate function for PUCCH
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuHqRecpReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuHqRecpReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuRecpReqInfo    *recpReq;

   TRC2(rgAcHdlTfuHqRecpReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuHqRecpReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuHqRecpReq(), tcId(%d)\n", tcCb->tcId));
#endif
#ifdef TFU_UPGRADE
   {
      RgAcTfuUeRecpReqInfo *recpReqInfo;
      recpReqInfo = (RgAcTfuUeRecpReqInfo *)tcCb->data;
      recpReq = recpReqInfo->recpReq;
   }
#else
   recpReq = (TfuRecpReqInfo*)tcCb->data;
#endif
   if ((ret = rgAcUtlTfuValidateHqRecpReq (tcCb, spCb, 
               recpReq)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuHqRecpReq */

#ifdef TFU_UPGRADE
/** @brief This function is the lower-level handler meant to validate the PUCCH
 * Reception request.
 *
 * @details
 * Validates the PUCCH Reception request for DLCQI from the Reception Request 
 * received from the scheduler. 
 *
 *     Function: 
 *         Processing steps:
 *         - Calls the validate function for PUCCH
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDlCqiRecpReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDlCqiRecpReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuRecpReqInfo    *recpReq;

   TRC2(rgAcHdlTfuDlCqiRecpReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDlCqiRecpReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDlCqiRecpReq(), tcId(%d)\n", tcCb->tcId));
#endif
#ifdef TFU_UPGRADE
   {
      RgAcTfuUeRecpReqInfo *recpReqInfo;
      recpReqInfo = (RgAcTfuUeRecpReqInfo *)tcCb->data;
      recpReq = recpReqInfo->recpReq;
      if ((ret = rgAcUtlTfuValidateDlCqiRecpReq (tcCb, spCb, 
               recpReq)) != CMXTA_ERR_NONE)
      {
         RETVALUE(ret);
      }
   }
#else
   recpReq = (TfuRecpReqInfo*)tcCb->data;
#endif
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDlCqiRecpReq */

/** @brief This function is the lower-level handler meant to validate the PUCCH
 * Reception request.
 *
 * @details
 * Validates the PUCCH Reception request for SR from the Reception Request 
 * received from the scheduler. 
 *
 *     Function: 
 *         Processing steps:
 *         - Calls the validate function for PUCCH
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuSrRecpReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuSrRecpReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuRecpReqInfo    *recpReq;

   TRC2(rgAcHdlTfuSrRecpReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSrRecpReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSrRecpReq(), tcId(%d)\n", tcCb->tcId));
#endif
   {
      RgAcTfuUeRecpReqInfo *recpReqInfo;
      recpReqInfo = (RgAcTfuUeRecpReqInfo *)tcCb->data;
      recpReq = recpReqInfo->recpReq;
      if ((ret = rgAcUtlTfuValidateSrRecpReq (tcCb, spCb, 
               recpReq)) != CMXTA_ERR_NONE)
      {
         RETVALUE(ret);
      }
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuSrRecpReq */

/** @brief This function is the lower-level handler meant to validate the PUCCH
 * Reception request.
 *
 * @details
 * Validates the PUCCH Reception request for SRS from the Reception Request 
 * received from the scheduler. 
 *
 *     Function: 
 *         Processing steps:
 *         - Calls the validate function for PUCCH
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuSrsRecpReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuSrsRecpReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuRecpReqInfo    *recpReq;

   TRC2(rgAcHdlTfuSrsRecpReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSrsRecpReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSrsRecpReq(), tcId(%d)\n", tcCb->tcId));
#endif
   {
      RgAcTfuUeRecpReqInfo *recpReqInfo;
      recpReqInfo = (RgAcTfuUeRecpReqInfo *)tcCb->data;
      recpReq = recpReqInfo->recpReq;
      if ((ret = rgAcUtlTfuValidateSrsRecpReq (tcCb, spCb, 
               recpReq)) != CMXTA_ERR_NONE)
      {
         RETVALUE(ret);
      }
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuSrsRecpReq */

#endif 

/** @brief This function is the lower-level handler meant to validate the MSG3
 * Reception request.
 *
 * @details
 * Validates the Reception request received for RACH's MSG3.
 *
 *     Function: 
 *         Processing steps:
 *         - Calls the validate function for MSG3
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuMsg3RecpReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuMsg3RecpReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuRecpReqInfo    *recpReq;

   TRC2(rgAcHdlTfuMsg3RecpReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuMsg3RecpReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuMsg3RecpReq(), tcId(%d)\n", tcCb->tcId));
#endif
#ifdef TFU_UPGRADE
   {
      RgAcTfuUeRecpReqInfo *recpReqInfo;
      recpReqInfo = (RgAcTfuUeRecpReqInfo *)tcCb->data;
      recpReq = recpReqInfo->recpReq;
   }
#else
   recpReq = (TfuRecpReqInfo*)tcCb->data;
#endif
   if ((ret = rgAcUtlTfuValidateMsg3RecpReq (tcCb, spCb, 
               recpReq)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuMsg3RecpReq */

/** @brief This function is the lower-level handler meant to validate the PUSCH
 * Reception request.
 *
 * @details
 * Validates the Reception request for PUSCH data.
 *
 *     Function: 
 *         Processing steps:
 *         - Calls the validate function for PUSCH
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuPuschRecpReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuPuschRecpReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuRecpReqInfo    *recpReq;

   TRC2(rgAcHdlTfuPuschRecpReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPuschRecpReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPuschRecpReq(), tcId(%d)\n", tcCb->tcId));
#endif
#ifdef TFU_UPGRADE
   {
      RgAcTfuUeRecpReqInfo *recpReqInfo;
      recpReqInfo = (RgAcTfuUeRecpReqInfo *)tcCb->data;
      recpReq = recpReqInfo->recpReq;
   }
#else
   recpReq = (TfuRecpReqInfo*)tcCb->data;
#endif
   if ((ret = rgAcUtlTfuValidatePuschRecpReq (tcCb, spCb, 
               recpReq)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuPuschRecpReq */






   
/** @brief This function is the handler function for the TFU Dat request.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDatReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDatReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16   ret;
   U8                   saveTime;

   TRC2(rgAcHdlTfuDatReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDatReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDatReq(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   /* Fairly simple we shall call the single validation function from here with
    * the event type */
   if ((ret = rgAcUtlTfuValidateMsg (tcCb, spCb, 
               EVTTFUDATREQ)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDatReq */

  
/** @brief This function is the lower-level handler meant to validate the BCH
 * data part of the Data request sent from MAC to physical layer.
 *
 * @details
 * Validates the BCH data received as part of the data request from MAC
 * scheduler.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the validate function for BCH
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuBchDatReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuBchDatReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuDatReqInfo     *datReq;

   TRC2(rgAcHdlTfuBchDatReq)

#ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuBchDatReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuBchDatReq(), tcId(%d)\n", tcCb->tcId));
#endif
   datReq = (TfuDatReqInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuValidateBch (tcCb, spCb, 
               datReq)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuBchDatReq */
  
/** @brief This function is the lower-level handler meant to validate the PDSCH
 * data part of the Data request sent from MAC to physical layer.
 *
 * @details
 * Validates the PDSCH data received as part of the data request from MAC
 * scheduler.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the validate function for PDSCH data for one UE
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuPdschDatReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuPdschDatReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuDatReqInfo     *datReq;

   TRC2(rgAcHdlTfuPdschDatReq)

#ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPdschDatReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPdschDatReq(), tcId(%d)\n", tcCb->tcId));
#endif
   datReq = (TfuDatReqInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuValidatePdsch (tcCb, spCb, 
               datReq)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuPdschDatReq */

/** @brief This function is the lower-level handler meant to validate RA
 * Response PDU sent from MAC to physical layer.
 *
 * @details
 * Validates the RaReponse sent as part of the data request from MAC to Physical
 * layer.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the validate function for RA Response
 *
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return CMXTA_ERR_NONE/CMXTA_ERR_INT/CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuRaRespReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuRaRespReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   TfuDatReqInfo     *datReq;

   TRC2(rgAcHdlTfuRaRespReq)

#ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuRaRespReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuRaRespReq(), tcId(%d)\n", tcCb->tcId));
#endif
   datReq = (TfuDatReqInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuValidateRaRsp (tcCb, spCb, 
               datReq)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuRaRespReq */




  

  

#ifdef RG_PHASE_2
/** @brief This function is the handler function for the TFU group power
 * control Request.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuGrpPwrCntrlReq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuGrpPwrCntrlReq (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16   ret;

   TRC2(rgAcHdlTfuGrpPwrCntrlReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuGrpPwrCntrlReq(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuGrpPwrCntrlReq(), tcId(%d)\n", tcCb->tcId));
#endif

   /* Fairly simple we shall call the single validation function from here with
    * the event type */
   if ((ret = rgAcUtlTfuValidateMsg (tcCb, spCb, 
               EVTTFUGRPPWRCNTRLREQ)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuGrpPwrCntrlReq */
#endif


  

/** @brief This is the higher level handler for UL CQI Indication. 
 *
 * @details
 * This handler would call the lower-level handlers for individual UL CQI
 * Indications.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls Build UL CQI Indication utility function.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuUlCqiInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuUlCqiInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   SuId              suId;
   TfuUlCqiIndInfo   *ulCqiIndInfo;
   U8                saveTime;

   TRC2(rgAcHdlTfuUlCqiInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuUlCqiInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuUlCqiInd(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&ulCqiIndInfo, sizeof(TfuUlCqiIndInfo));
   if ((ret = rgAcUtlTfuBuildUlCqiIndMsg (tcCb, spCb, &pst, 
               &suId, ulCqiIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)ulCqiIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuUlCqiInd (&pst, suId, ulCqiIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuUlCqiInd */ 
  
/** @brief This function is the lower-level handler to TfUiTfuUlCqiInd primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuUlCqiIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.ulcqi.ind >
 *       <tapa.tfu.ulcqi ueId="1" use="3"/>
 *       <tapa.tfu.ulcqi ueId="3" use="5"/>
 *       <tapa.tfu.ulcqi ueId="2" use="4"/>
 *    </tapa.tfu.ulcqi.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the ulCqiIndInfo i.e. pointer to the TfuUlCqiIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC Pdu based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuUlCqi
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuUlCqi(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuUlCqiIndInfo   *ulCqiIndInfo;

   TRC2(rgAcHdlTfuUlCqi);

   ulCqiIndInfo = (TfuUlCqiIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildUlCqi (tcCb, spCb, ulCqiIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuUlCqi */ 

#ifdef LTEMAC_MIMO
/** @brief This is the higher level handler for DOA Indication. 
 *
 * @details
 * This handler would call the lower-level handlers for individual DOA
 * Indications.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls Build DOA Indication utility function.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDoaInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDoaInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   SuId              suId;
   TfuDoaIndInfo   *doaIndInfo;
   U8                saveTime;

   TRC2(rgAcHdlTfuDoaInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDoaInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDoaInd(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&doaIndInfo, sizeof(TfuDoaIndInfo));
   if ((ret = rgAcUtlTfuBuildDoaIndMsg (tcCb, spCb, &pst, 
               &suId, doaIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)doaIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuDoaInd (&pst, suId, doaIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDoaInd */

/** @brief This function is the lower-level handler to TfUiTfuDoaInd primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuDoaIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.doa.ind >
 *       <tapa.tfu.doa ueId="1" use="3"/>
 *       <tapa.tfu.doa ueId="3" use="5"/>
 *       <tapa.tfu.doa ueId="2" use="4"/>
 *    </tapa.tfu.doa.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the doaIndInfo i.e. pointer to the TfuDoaIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC Pdu based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDoa
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDoa(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuDoaIndInfo   *doaIndInfo;

   TRC2(rgAcHdlTfuDoa);

   doaIndInfo = (TfuDoaIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildDoa (tcCb, spCb, doaIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDoa */ 
#endif

/** @brief This is the higher level handler for DL CQI Indication. 
 *
 * @details
 * This handler would call the lower-level handlers for individual DL CQI
 * Indications.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls Build DL CQI Indication utility function.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDlCqiInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDlCqiInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   SuId              suId;
   TfuDlCqiIndInfo   *dlCqiIndInfo;
   U8                saveTime;

   TRC2(rgAcHdlTfuDlCqiInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDlCqiInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDlCqiInd(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&dlCqiIndInfo, sizeof(TfuDlCqiIndInfo));
   if ((ret = rgAcUtlTfuBuildDlCqiIndMsg (tcCb, spCb, &pst, 
               &suId, dlCqiIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)dlCqiIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuDlCqiInd (&pst, suId, dlCqiIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDlCqiInd */ 
  
/** @brief This function is the lower-level handler to TfUiTfuDlCqiInd primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuDlCqiIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.dlcqi.ind >
 *       <tapa.tfu.dlcqi ueId="1" use="3"/>
 *       <tapa.tfu.dlcqi ueId="3" use="5"/>
 *       <tapa.tfu.dlcqi ueId="2" use="4"/>
 *    </tapa.tfu.dlcqi.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the dlCqiIndInfo i.e. pointer to the TfuDlCqiIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC Pdu based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDlCqi
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDlCqi(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuDlCqiIndInfo   *dlCqiIndInfo;

   TRC2(rgAcHdlTfuDlCqi);

   dlCqiIndInfo = (TfuDlCqiIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildDlCqi (tcCb, spCb, dlCqiIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDlCqi */ 
#ifdef TFU_UPGRADE

/** @brief This is the higher level handler for Raw DL CQI Indication. 
 *
 * @details
 * This handler would call the lower-level handlers for individual Raw DL CQI
 * Indications.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls Build Raw DL CQI Indication utility function.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuRawDlCqiInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuRawDlCqiInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   SuId              suId;
   TfuRawCqiIndInfo   *rawDlCqiIndInfo;
   U8                saveTime;

   TRC2(rgAcHdlTfuRawDlCqiInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuRawDlCqiInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuRawDlCqiInd(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&rawDlCqiIndInfo, sizeof(TfuRawCqiIndInfo));
   if ((ret = rgAcUtlTfuBuildRawDlCqiIndMsg (tcCb, spCb, &pst, 
               &suId, rawDlCqiIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)rawDlCqiIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuRawCqiInd(&pst, suId, rawDlCqiIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuRawDlCqiInd */ 

/** @brief This function is the lower-level handler to rgAcHdlTfuRawDlCqi primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuRawCqiIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.rawdlcqi.ind >
 *       <tapa.tfu.rawdlcqi ueId="1" use="3"/>
 *       <tapa.tfu.rawdlcqi ueId="3" use="5"/>
 *       <tapa.tfu.rawdlcqi ueId="2" use="4"/>
 *    </tapa.tfu.rawdlcqi.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the rawDlCqiIndInfo i.e. pointer to the TfuRawCqiIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC Pdu based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuRawDlCqi
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuRawDlCqi(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuRawCqiIndInfo   *rawDlCqiIndInfo;

   TRC2(rgAcHdlTfuRawDlCqi);

   rawDlCqiIndInfo = (TfuRawCqiIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildRawDlCqi (tcCb, spCb, rawDlCqiIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuRawDlCqi */ 

/** @brief This is the higher level handler for UL SRS Indication. 
 *
 * @details
 * This handler would call the lower-level handlers for individual SRS
 * Indications.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls Build SRS Indication utility function.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuUlSrsInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuUlSrsInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   SuId              suId;
   TfuSrsIndInfo* srsIndInfo;
   U8                saveTime;

   TRC2(rgAcHdlTfuUlSrsInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuUlSrsInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuUlSrsInd(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&srsIndInfo, sizeof(TfuSrsIndInfo));
   if ((ret = rgAcUtlTfuBuildSrsIndMsg (tcCb, spCb, &pst, 
               &suId, srsIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)srsIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuSrsInd(&pst, suId, srsIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuUlSrsInd */ 

/** @brief This function is the lower-level handler to rgAcHdlTfuUlSrs primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuSrsIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.srs.ind >
 *       <tapa.tfu.srs ueId="1" use="3"/>
 *       <tapa.tfu.srs ueId="3" use="5"/>
 *       <tapa.tfu.srs ueId="2" use="4"/>
 *    </tapa.tfu.srs.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the srsIndInfo i.e. pointer to the TfuSrsIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC PDU based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuUlSrs
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuUlSrs(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuSrsIndInfo* srsIndInfo;

   TRC2(rgAcHdlTfuUlSrs);

   srsIndInfo = (TfuSrsIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildSrs (tcCb, spCb, srsIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuUlSrs */ 

#endif 



/** @brief This is the higher level handler for HARQ Feedback Indication. 
 *
 * @details
 * This handler would call the lower-level handlers for individual HARQ
 * feedbacks.
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls Build harq feedback Indication utility function.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuHqInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuHqInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   SuId              suId;
   TfuHqIndInfo      *hqIndInfo;
   U8                saveTime;

   TRC2(rgAcHdlTfuHqInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuHqInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuHqInd(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&hqIndInfo, sizeof(TfuHqIndInfo));
   if ((ret = rgAcUtlTfuBuildHqIndMsg (tcCb, spCb, &pst, 
               &suId, hqIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)hqIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuHqInd (&pst, suId, hqIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuHqInd */ 
  
/** @brief This function is the lower-level handler to TfUiTfuHqInd primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuHqIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.hq.ind >
 *       <tapa.tfu.hq ueId="1" use="3"/>
 *       <tapa.tfu.hq ueId="3" use="5"/>
 *       <tapa.tfu.hq ueId="2" use="4"/>
 *    </tapa.tfu.hq.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the hqIndInfo i.e. pointer to the TfuHqIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC Pdu based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuHq
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuHq(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuHqIndInfo   *hqIndInfo;

   TRC2(rgAcHdlTfuHq);

   hqIndInfo = (TfuHqIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildHq (tcCb, spCb, hqIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuHq */ 




   


/** @brief This is the high level handler for SR indications.
 *
 * @details
 * This would be responsible for calling the lower level handler embedded within
 * this command.
 *
 * <tapa.send>
 *    <tapa.tfu.pucchdelta.ind >
 *       <tapa.tfu.pucchdelta ueId="1" />
 *       <tapa.tfu.pucchdelta ueId="3" />
 *       <tapa.tfu.pucchdelta ueId="2" />
 *    </tapa.tfu.pucchdelta.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the utility function responsible for calling the embedded
 *         handlers.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuPucchDeltaInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuPucchDeltaInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16                        ret;
   Pst                        pst;
   SuId                       suId;
   TfuPucchDeltaPwrIndInfo   *pucchDeltaIndInfo;
   U8                         saveTime;

   TRC2(rgAcHdlTfuPucchDeltaInd);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPucchDeltaInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuPucchDeltaInd(), tcId(%d)\n", tcCb->tcId));
#endif
   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&pucchDeltaIndInfo, sizeof(TfuPucchDeltaPwrIndInfo));
   if ((ret = rgAcUtlTfuBuildPucchDeltaIndMsg (tcCb, spCb, &pst, &suId, pucchDeltaIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)pucchDeltaIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuPucchDeltaPwrInd (&pst, suId, pucchDeltaIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuPucchDeltaInd */


/** @brief This function is the lower-level handler to TfUiTfuPucchDeltaInd primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuPucchDeltaPwrIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.hq.ind >
 *       <tapa.tfu.hq ueId="1" use="3"/>
 *       <tapa.tfu.hq ueId="3" use="5"/>
 *       <tapa.tfu.hq ueId="2" use="4"/>
 *    </tapa.tfu.hq.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the pucchDeltaIndInfo i.e. pointer to the TfuPucchDeltaPwrIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC Pdu based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuPucchDelta
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuPucchDelta(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuPucchDeltaPwrIndInfo   *pucchDeltaIndInfo;

   TRC2(rgAcHdlTfuPucchDelta);

   pucchDeltaIndInfo = (TfuPucchDeltaPwrIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildPucchDelta (tcCb, spCb, pucchDeltaIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuPucchDelta */ 




/** @brief This is the high level handler for SR indications.
 *
 * @details
 * This would be responsible for calling the lower level handler embedded within
 * this command.
 *
 * <tapa.send>
 *    <tapa.tfu.sr.ind >
 *       <tapa.tfu.sr ueId="1" />
 *       <tapa.tfu.sr ueId="3" />
 *       <tapa.tfu.sr ueId="2" />
 *    </tapa.tfu.sr.ind>
 * </tapa.send>

 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the utility function responsible for calling the embedded
 *         handlers.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuSrInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuSrInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   SuId              suId;
   TfuSrIndInfo      *srIndInfo;
   U8                saveTime;

   TRC2(rgAcHdlTfuSrInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSrInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuSrInd(), tcId(%d)\n", tcCb->tcId));
#endif
   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&srIndInfo, sizeof(TfuSrIndInfo));
   if ((ret = rgAcUtlTfuBuildSrIndMsg (tcCb, spCb, &pst, &suId, srIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)srIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuSrInd (&pst, suId, srIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuSrInd */

/** @brief This function is the lower-level handler to TfUiTfuSrInd primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuSrIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.sr.ind >
 *       <tapa.tfu.sr ueId="1" />
 *       <tapa.tfu.sr ueId="3" />
 *       <tapa.tfu.sr ueId="2" />
 *    </tapa.tfu.sr.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the srIndInfo i.e. pointer to the TfuSrIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC Pdu based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuSr
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuSr (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuSrIndInfo   *srIndInfo;

   TRC2(rgAcHdlTfuSr);

   srIndInfo = (TfuSrIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildSr (tcCb, spCb, srIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuSr */ 


/** @brief This is the high level handler for Decode failure indications.
 *
 * @details
 * This would be responsible for calling the lower level handler embedded within
 * this command.
 *
 * <tapa.send>
 *    <tapa.tfu.crcind.ind >
 *       <tapa.tfu.crcind ueId="1" />
 *       <tapa.tfu.crcind ueId="3" />
 *       <tapa.tfu.crcind ueId="2" />
 *    </tapa.tfu.crcind.ind>
 * </tapa.send>

 *
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the utility function responsible for calling the embedded
 *         handlers.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuCrcInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuCrcInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16                  ret;
   Pst                  pst;
   SuId                 suId;
   TfuCrcIndInfo    *crcIndInfo;
   U8                   saveTime;

   TRC2(rgAcHdlTfuCrcInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuCrcInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuCrcInd(), tcId(%d)\n", tcCb->tcId));
#endif
   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&crcIndInfo, sizeof(TfuCrcIndInfo));
   if ((ret = rgAcUtlTfuBuildCrcIndMsg (tcCb, spCb, &pst, &suId, crcIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)crcIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuCrcInd (&pst, suId, crcIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuCrcInd */

/** @brief This function is the lower-level handler to TfUiTfuCrcInd primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuCrcIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.crcind.ind >
 *       <tapa.tfu.crcind ueId="1" />
 *       <tapa.tfu.crcind ueId="3" />
 *       <tapa.tfu.crcind ueId="2" />
 *    </tapa.tfu.crcind.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the crcIndInfo i.e. pointer to the TfuCrcIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of CRC indications
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuCrc
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuCrc (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16                  ret;
   TfuCrcIndInfo   *crcIndInfo;

   TRC2(rgAcHdlTfuCrc);

   crcIndInfo = (TfuCrcIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildCrc (tcCb, spCb, crcIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuCrc */ 

/** @brief This is the high level handler for timing advance indication.
 *
 * @details
 * This would be responsible for calling the lower level handler embedded within
 * this command.
 *
 * <tapa.send>
 *    <tapa.tfu.timingadv.ind >
 *       <tapa.tfu.timingadv ueId="1" ta="2" />
 *       <tapa.tfu.timingadv ueId="3" ta="2" />
 *       <tapa.tfu.timingadv ueId="2" ta="2" />
 *    </tapa.tfu.timingadv.ind>
 * </tapa.send>
 *     Function: 
 *
 *         Processing steps:
 *         - Calls the utility function responsible for calling the embedded
 *         handlers.
 *
 * @param  tcCb CmXtaTCCb
 * @param  spCb CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuTimingAdvInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuTimingAdvInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16                  ret;
   Pst                  pst;
   SuId                 suId;
   TfuTimingAdvIndInfo    *timingAdvIndInfo;
   U8                   saveTime;

   TRC2(rgAcHdlTfuTimingAdvInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuTimingAdvInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuTimingAdvInd(), tcId(%d)\n", tcCb->tcId));
#endif
   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&timingAdvIndInfo, sizeof(TfuTimingAdvIndInfo));
   if ((ret = rgAcUtlTfuBuildTimingAdvIndMsg (tcCb, spCb, &pst, &suId, timingAdvIndInfo)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)timingAdvIndInfo);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuTimingAdvInd (&pst, suId, timingAdvIndInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuTimingAdvInd */

/** @brief This function is the lower-level handler to TfUiTfuTimingAdvInd primitive.
 *
 * @details
 * This handler is responsible for filling up the tfuTimingAdvIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.timingadv.ind >
 *       <tapa.tfu.timingadv ueId="1" />
 *       <tapa.tfu.timingadv ueId="3" />
 *       <tapa.tfu.timingadv ueId="2" />
 *    </tapa.tfu.timingadv.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the timingAdvIndInfo i.e. pointer to the 
 *         TfuTimingAdvIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of Decode failures 
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuTimingAdv
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuTimingAdv (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16                  ret;
   TfuTimingAdvIndInfo   *timingAdvIndInfo;

   TRC2(rgAcHdlTfuTimingAdv);

   timingAdvIndInfo = (TfuTimingAdvIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildTimingAdv (tcCb, spCb, timingAdvIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuTimingAdv */ 



  

/** @brief This function is the high level handler for the TFU primitive
 * TfUiTfuDatInd.
 *
 * @details
 * This function is the high level handler for datIndication it is responsible
 * for calling the lower-level handlers for individual UE's PDUs.
 * The final command would look something like this -
 *
 * <tapa.send>
 *    <tapa.tfu.dat.ind datInds="3">
 *       <tapa.tfu.dat ueId="1" use="3"/>
 *       <tapa.tfu.dat ueId="3" use="5"/>
 *       <tapa.tfu.dat ueId="2" use="4"/>
 *    </tapa.tfu.dat.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - This is a low level handler function i.e. this is embedded within a
 *         higher level command <tapa.tfu.dat.ind>.
 *         This hander must read one RNTI and fill up the TfuDatInfo
 *         structure for that RNTI. 
 *         - This handler would get the TfuDatInfo structure from the tcCb.
 *         - Would fill in the valid values into the correct part of the data
 *         structure. 
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 * -# CMXTA_ERR_NOMATCH
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDatInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDatInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   SuId              suId;
   TfuDatIndInfo     *datInd;
   U8                saveTime;

   TRC2(rgAcHdlTfuDatInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDatInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuDatInd(), tcId(%d)\n", tcCb->tcId));
#endif

   if (rgAccCb.directives.autoTti)
   {
      /* Need to check timing */
      if ((ret = rgAcUtlCheckTime (tcCb, spCb)) == CMXTA_ERR_PENDING)
         RETVALUE(CMXTA_ERR_PENDING);
   }
   saveTime = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "saveTime",  &saveTime);
   RGCPYTIMEINFO(rgAcTfCb.crntTime, rgAccCb.timeList[saveTime]);
   rgAcUtlAllocEvnt ((Data**)&datInd, sizeof(TfuDatIndInfo));
   if ((ret = rgAcUtlTfuBuildDatIndMsg (tcCb, spCb, &pst, 
               &suId, datInd)) != CMXTA_ERR_NONE)
   {
      rgAcUtlFreeEvnt ((Data*)datInd);
      RETVALUE(ret);
   }

   /* Lets call the TFU interface primitive. */
   TfUiTfuDatInd (&pst, suId, datInd);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDatInd */ 
  
/** @brief This function is the lower-level handler to TfUiTfuDatInd primitive.
 *
 * @details
 * This handler is responsible for filling up the TfuDatIndInfo structure for a
 * single RNTI i.e. UE. Multiple such commands may comprise the actual command.
 * <tapa.send>
 *    <tapa.tfu.dat.ind datInds="3">
 *       <tapa.tfu.dat ueId="1" use="3"/>
 *       <tapa.tfu.dat ueId="3" use="5"/>
 *       <tapa.tfu.dat ueId="2" use="4"/>
 *    </tapa.tfu.dat.ind>
 * </tapa.send>
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Pick up the datInd i.e. pointer to the TfuDatIndInfo structure from
 *         the tcCb
 *         - Add a new node to the list of PDUs 
 *         - Create the MAC Pdu based on the given inputs
 *         - Return to the main handler
 * @param  tcCb pointer to CmXtaTCCb
 * @param  spCb pointer to CmXtaSpCb
 * @return 
 * -# CMXTA_ERR_NONE
 * -# CMXTA_ERR_INT
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDat
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDat(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   S16            ret;
   TfuDatIndInfo  *datIndInfo;

   TRC2(rgAcHdlTfuDat);

   datIndInfo = (TfuDatIndInfo *)tcCb->data;
   if ((ret = rgAcUtlTfuBuildDat (tcCb, spCb, datIndInfo)) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDat */ 


/** @brief This function is the handler function for the TFU TTI indication from
 * PHY to MAC.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PRIVATE S16 rgAcHdlMultiInstTfuTtiInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PRIVATE S16 rgAcHdlMultiInstTfuTtiInd(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   Pst               schPst;
   SuId              suId = 0; /* Service User Identifier */
   U16               numTti;
   U8                oper;
   U8                numDlDelta;
   U8                numTfuDelta;
   TfuTtiIndInfo     ttiInd;
   TfuTtiIndInfo     schTtiInd;
   U16               num;
   U16               i;
#ifdef LTEMAC_HDFDD
   U8                idx;
#endif
   Bool              isMeasGap;
   U8                ueId;
   U8                advance;
#ifdef LTEMAC_HDFDD
   U8                idxUe;
#endif
   Bool              isAdd;
   U8                numInst = 1;
   U8                macSuId[5] ={0,}; /* replace 5 by MAX_INST macro */
   U8                macSuIdCount = 0;
   U8                schSuId[5] ={0,}; /* replace 5 by MAX_INST macro */
   U8                schSuIdCount = 0;
   Inst              schInstId[5] ={0,}; /* replace 5 by MAX_INST macro */
   U8                schInstCount = 0;
   U8                macInstCount = 0;
   Inst              macInstId[5] ={0,}; /* replace 5 by MAX_INST macro */
   CmLteCellId       cellId[5] ={0,};
   U8                cellIdCount = 0;
   ProcId               srcProcId;
   ProcId               dstProcId;

   TRC2(rgAcHdlMultiInstTfuTtiInd)
   numTti          = 1;
   oper            = 0;
   numDlDelta      = 0;
   numTfuDelta     = 0;
   isMeasGap       = FALSE;
   ueId            = 0;
   advance         = 0;
   isAdd           = FALSE;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuTtiInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuTtiInd(), tcId(%d)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numTti",  &numTti);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numInst",  &numInst);
   /*CA dev Start*/
   U8 instIdx = 0;
   if(CMXTA_ERR_NO_VALUE == ret)
   {
      numInst = 1;
   }
   /*CA dev End*/

   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
         "macSuId", macSuId, &macSuIdCount);
   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
         "schSuId", schSuId, &schSuIdCount);


   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
         "macInstId", macInstId, &macInstCount);
   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON, 
         "schInstId", schInstId, &schInstCount);


   cmXtaXmlGetValList (tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON, 
         "cellId", cellId, &cellIdCount);


   num = numTti;

   for (i = 0; i < num; i++)
   {
      if (rgAcTfCb.crntTime.subframe > RG_NUM_SUB_FRAMES)
      {
         CMXTA_ZERO(&(rgAcTfCb.crntTime), sizeof(CmLteTimingInfo));
      }
      else
      {
         RGADDTOCRNTTIME(rgAcTfCb.crntTime, rgAcTfCb.crntTime, 1);
      }
#if 0
      printf("\n XTA::(%d %d)\n",
            rgAcTfCb.crntTime.sfn,
            rgAcTfCb.crntTime.subframe);
#endif
      /*CA dev Start*/
      for(instIdx = 0; instIdx < numInst; instIdx++)
      {   

         if ((ret = rgAcUtlTfuBuildMultiInstTtiIndMsg (tcCb, spCb, &pst, &suId, &schTtiInd, instIdx)) != CMXTA_ERR_NONE)
         {
            RETVALUE(ret);
         }  

         CMXTA_ZERO(&pst, sizeof(Pst));
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;
         cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTRG, macInstId[instIdx], srcProcId, dstProcId, FALSE);

         schTtiInd.cells[instIdx].schTickDelta  = 0;
         schTtiInd.cells[instIdx].dlBlankSf     = 0;
         schTtiInd.cells[instIdx].ulBlankSf     = 0;
         schTtiInd.cells[instIdx].cellId        = cellId[instIdx];

         CMXTA_ZERO(&schPst, sizeof(Pst));
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;

         cmXtaGetPst(&schPst, ENTTF, CMXTA_INST_ID, ENTRG, schInstId[0], srcProcId, dstProcId, FALSE);
      }

      schTtiInd.numCells = numInst;
      TfUiTfuSchTtiInd (&schPst, schSuId[0], &schTtiInd);

      for(instIdx = 0; instIdx < numInst; instIdx++)
      {   

         if ((ret = rgAcUtlTfuBuildMultiInstTtiIndMsg (tcCb, spCb, &pst, &suId, &ttiInd, 0)) != CMXTA_ERR_NONE)
         {
            RETVALUE(ret);
         }  

         CMXTA_ZERO(&pst, sizeof(Pst));
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;
         cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTRG, macInstId[instIdx], srcProcId, dstProcId, FALSE);


         ttiInd.numCells  = 1;/*CA dev Start*/
         ttiInd.cells[0].schTickDelta  = 0;
         ttiInd.cells[0].dlBlankSf     = 0;
         ttiInd.cells[0].ulBlankSf     = 0;
         ttiInd.cells[0].cellId        = cellId[instIdx];

         CMXTA_ZERO(&schPst, sizeof(Pst));
         srcProcId = CMXTA_PROCID_MASTER;
         dstProcId = CMXTA_PROCID_MASTER;

         cmXtaGetPst(&schPst, ENTTF, CMXTA_INST_ID, ENTRG, schInstId[0], srcProcId, dstProcId, FALSE);

         /*ccpu00136020 - Modify - To avod segmentation fault while running LTA test cases with common codebase */
         /*TfUiTfuSchTtiInd moved outside the loop*/
         TfUiTfuTtiInd (&pst, macSuId[instIdx], &ttiInd);
      }
      /*CA dev End*/
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuTtiInd */


 /** @brief This function is the handler function for the TFU ERR IND
 * PHY to MAC.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuErrInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuErrInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   Pst               schPst;
   SuId              suId = 0; /* Service User Identifier */
   TfuErrIndInfo     errInd;

   TRC2(rgAcHdlTfuErrInd)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuTtiInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuTtiInd(), tcId(%d)\n", tcCb->tcId));
#endif


   errInd.cellId = RG_ACC_CELL_ID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(errInd.cellId));
   RGCPYTIMEINFO(rgAcTfCb.crntTime, errInd.timingInfo);   

   rgAcUtlTfuGetToSchPst (tcCb, spCb, &schPst);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "schSuId",  &suId);
   TfUiTfuErrInd (&schPst, (suId), &errInd);

   RETVALUE(CMXTA_ERR_NONE);
} 

  
EXTERN Void SIncrementTtiCount(Void);
/** @brief This function is the handler function for the TFU TTI indication from
 * PHY to MAC.
 * @param tcCb A pointer to the Test Case control block
 * @param spCb A pointer to the Test Step Stack control block.
 * @return CMXTA_ERR_NONE if successful
 */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuTtiInd
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuTtiInd (tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{

   S16               ret;
   Pst               pst;
   Pst               schPst;
   SuId              suId = 0; /* Service User Identifier */
   U16               numTti;
   U8                oper;
   U8                numDlDelta;
   U8                numTfuDelta;
   TfuTtiIndInfo     ttiInd;
   TfuTtiIndInfo     schTtiInd;
   U16               num;
   U16               i;
#ifdef LTEMAC_HDFDD
   U8                idx;
#endif
   Bool              isMeasGap;
   U8                ueId;
   RgAcUeCb          *ueCb;
   U8                advance;
   U16               crntTime;
#ifdef LTEMAC_HDFDD
   U8                idxUe;
#endif
   Bool              isAdd;
   U8                numInst = 1;
   U8                multInstFlag = 0;

   TRC2(rgAcHdlTfuTtiInd)
   numTti          = 1;
   oper            = 0;
   numDlDelta      = 0;
   numTfuDelta     = 0;
   isMeasGap       = FALSE;
   ueId            = 0;
   advance         = 0;
   isAdd           = FALSE;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuTtiInd(), tcId(%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlTfuTtiInd(), tcId(%d)\n", tcCb->tcId));
#endif


   if (rgAccCb.directives.autoTti == TRUE)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }
   SIncrementTtiCount();
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numInst",  &numInst);
   /*CA dev Start*/
   if(CMXTA_ERR_NO_VALUE == ret)
   {
      numInst = 1;
   }
   /*CA dev End*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "multiInstEna",  &multInstFlag);

   if(multInstFlag != 0)
   {
      RETVALUE(rgAcHdlMultiInstTfuTtiInd(tcCb,spCb));
   }
   SIncrementTtiCount();
   /* Plan is to let the user provide a number of TTIs in a single command and
    * not be required to provide a list of TTI indications separately. 
    * <tapa.send>
    *    <tapa.tfu.ttiInd numTti="4" op="PLUS" numDlDelta="2"
    *    numTfuDelta="1"/>
    * <tapa.send>
    */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numTti",  &numTti);
   /* Increasing numTti by 1 for Test case 6.17, 6.18 and 6.19 under MIMO only */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isAdd",  &isAdd);
   if((isAdd == TRUE)&&
      ((tcCb->tstId == 16)||
      (tcCb->tstId == 17)||
      (tcCb->tstId == 18)))
   {
      numTti++;
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "op",  &oper);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numDlDelta",  &numDlDelta);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numTfuDelta",  &numTfuDelta);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isMeasGap",  &isMeasGap);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId",  &ueId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "advance",  &advance);

   if (TRUE == isMeasGap)
   {
      ueCb = &(rgAccCb.acUeCb[ueId]);
      crntTime = ((rgAcTfCb.crntTime.sfn * 10) + rgAcTfCb.crntTime.subframe) % ueCb->gapPrd;
      if (crntTime > (ueCb->gapOffst - advance))
      {
         if (crntTime < ueCb->gapOffst)
         {
            num = (ueCb->gapPrd + (ueCb->gapOffst - crntTime)); 
         }
         else
         {
            num = (ueCb->gapPrd - crntTime + ueCb->gapOffst); 
         }
      }
      else
      {
         num = (ueCb->gapOffst - crntTime) % ueCb->gapPrd;
      }
      num = num - advance;
   }
   else
   {

      if (oper == RG_ACC_PLUS)
      {
         /* Introduced timing delta for DL control */
#ifdef LTE_TDD
         num = numTti + ((numDlDelta * RG_ENV_DL_DELTA) + (numTfuDelta * TFU_DELTA));
#else
         num = numTti + ((numDlDelta * RG_ENV_DL_DELTA) + (numTfuDelta * TFU_DLCNTRL_DLDELTA));
#endif
      }
      else if (oper == RG_ACC_MINUS)
      {
#ifdef LTE_TDD
         num = numTti - ((numDlDelta * RG_ENV_DL_DELTA) + (numTfuDelta * TFU_DELTA));
#else
         num = numTti - ((numDlDelta * RG_ENV_DL_DELTA) + (numTfuDelta * TFU_DLCNTRL_DLDELTA));
#endif
      }
      else
      {
         num = numTti;
      }
   }

   for (i = 0; i < num; i++)
   {
#ifdef LTEMAC_HDFDD
      /* Update the stotred SF direction infroamtion 
       for all HDFDD UEs */
      for (idxUe = 0; idxUe < RG_ACC_MAX_UE; idxUe++)
      {
         if (rgAccCb.acUeCb[idxUe].isHdFddEnbld)
         {
            for(idx = 0; idx < RGAC_HDFDD_SF_HIST - 1; idx++)
            {
               rgAccCb.ueSfInfo[idxUe].sfDir[idx] = rgAccCb.ueSfInfo[idxUe].sfDir[idx+1];
               rgAccCb.ueSfInfo[idxUe].sfDir[idx+1] = RGAC_HDFDD_NOSCHD;
            }
         }
      }
#endif
      if (rgAcTfCb.crntTime.subframe > RG_NUM_SUB_FRAMES)
      {
         CMXTA_ZERO(&(rgAcTfCb.crntTime), sizeof(CmLteTimingInfo));
      }
      else
      {
         RGADDTOCRNTTIME(rgAcTfCb.crntTime, rgAcTfCb.crntTime, 1);
      }

      if ((ret = rgAcUtlTfuBuildTtiIndMsg (tcCb, spCb, &pst, &suId, &ttiInd)) != CMXTA_ERR_NONE)
      {
         RETVALUE(ret);
      }  
      /* 4UEPerTti:Initilizing rgu dynamic delta parameters */ 
         ttiInd.numCells  = 1;
         ttiInd.cells[0].schTickDelta  = 0;
         ttiInd.cells[0].dlBlankSf     = 0;
         ttiInd.cells[0].ulBlankSf     = 0;

      schTtiInd = ttiInd;
      /* Lets call the TFU interface primitive. */
      rgAcUtlTfuGetToSchPst (tcCb, spCb, &schPst);
     /*ccpu00136020 - Modify - To avod segmentation fault while running LTA test cases with common codebase */
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "schSuId",  &suId);
      TfUiTfuSchTtiInd (&schPst, (suId), &schTtiInd);
      TfUiTfuTtiInd (&pst, suId, &ttiInd);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuTtiInd */

 /** @brief This function handles setting of directives, note these are
  * applicable and survive only a single test case and arent global. 
  *
  * @details
  *
  *     Function: 
  *
  *         Processing steps:
  *         - 
  *
  *
  * @param  
  * @param 
  * @return 
  */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuDirective
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuDirective (tcCb, spCb)
 CmXtaTCCb  *tcCb;
 CmXtaSpCb  *spCb;
#endif
{

   RgAcDirectives *directives;

   TRC2(rgAcHdlTfuDirective);

   directives = &(rgAccCb.directives);

   directives->ulDeltaPrsnt = FALSE;
   cmXtaXmlGetVal (tcCb, spCb->curStep, CMXTA_ATTRIB_BOOL, "ulDeltaPrsnt", &(directives->ulDeltaPrsnt));
   directives->noTimeValidation = FALSE;
   cmXtaXmlGetVal (tcCb, spCb->curStep, CMXTA_ATTRIB_BOOL, "noTimeValidation",
   &(directives->noTimeValidation));
   directives->autoTti = FALSE;
   cmXtaXmlGetVal (tcCb, spCb->curStep, CMXTA_ATTRIB_BOOL, "autoTti",
   &(directives->autoTti));
   directives->validateCfi = FALSE;
   cmXtaXmlGetVal (tcCb, spCb->curStep, CMXTA_ATTRIB_BOOL, "validateCfi",
   &(directives->validateCfi));
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuDirective */ 

 /** @brief This function 
  *
  * @details
  *
  *     Function: 
  *
  *         Processing steps:
  *         - 
  *
  *
  * @param  
  * @param 
  * @return 
  */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuStartTti
(
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuStartTti (tcCb, spCb)
 CmXtaTCCb        *tcCb;
 CmXtaSpCb        *spCb;
#endif
{
   Buffer      *msgBuf;
   Pst         pst;
   TRC2(rgAcHdlTfuStartTti);
   
   UNUSED(tcCb);
   UNUSED(spCb);

   /* Here we need to post a message to the dummy PHY layer to start the timer.
    * */
   if (SGetMsg (cmXtaCb.init.region, cmXtaCb.init.pool, &msgBuf) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlTfuStartTti() allocation failed\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
   cmXtaGetPst(&pst, ENTTST, CMXTA_INST_ID, ENTTF, CMXTA_INST_ID, CMXTA_PROCID_MASTER, CMXTA_PROCID_MASTER, FALSE);
   RETVALUE(SPstTsk(&pst,msgBuf));
} /* end of rgAcHdlTfuStartTti  */ 

/** @brief This function 
  *
  * @details
  *
  *     Function: 
  *
  *         Processing steps:
  *         - 
  *
  *
  * @param  
  * @param 
  * @return 
  */
#ifdef ANSI
PUBLIC S16 rgAcHdlTfuResetUlRb
(
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb
 )
#else
PUBLIC S16 rgAcHdlTfuResetUlRb(tcCb, spCb)
 CmXtaTCCb        *tcCb;
 CmXtaSpCb        *spCb;
#endif
{
   TRC2(rgAcHdlTfuResetUlRb)
   
   UNUSED(tcCb);
   UNUSED(spCb);

   for (U8 rb = 0; rb < 110; rb++)
   {
      rgAccCb.ulRbMap[rb] = RGAC_RB_FREE;
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of rgAcHdlTfuResetUlRb*/ 



/**********************************************************************
 
         End of file:     rgac_tfuhdl.c@@/main/3 - Sat Jul 30 02:21:08 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm              1. Initial Release.
/main/2      ---     sm              1. LTE MAC 2.1 release
           rg007.201 ap  1. Added support for MIMO
           rg008.201 sd  Removed dependency on MIMO flag
           rg009.201 dv  1. Added changes of TFU_UPGRADE 
/main/3      ---     nu  1. Updated for release.
           rg002.301 asehgal 1. ccpu00118351: timing delta for DL control 
$SID$        ---     rt      1. LTE MAC 4.1 release
*********************************************************************91*/
