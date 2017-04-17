
/********************************************************************20**

     Name:    LTE MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source.

     File:    rgac_rgmhdl.c

     Sid:      rgac_rgmhdl.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Thu May 23 19:17:22 2013

     Prg:     nsadar 
*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgm.h"           /* RGM Interface defines */
#include "rgm.h"           /* RGM Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_rgm.h"
#include "rgac_acc.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgm.x"           /* RGM Interface includes */
#include "rgm.x"           /* RGM Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"
#include "rgac_rgm.x"        /* MAC error defines */

/**
 * @brief XTA Bind Request Handler for RGM interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgmBndReq
 *     
 *     Issues a bindrequest from RGM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlRgmBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRgmBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;             /* service user SAP identifier */
   SpId          spId = 0;             /* service user SAP identifier */
   
   TRC2(rgAcHdlRgmBndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgmBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgmBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaGetPst(&pst, RGAC_RGM_USERENT, RGAC_RGM_USERINST,RGAC_RGM_PROVENT,RGSCH_INST_START, RGAC_RGM_SRCPROC, RGAC_RGM_DSTPROC, RGAC_RGM_MATCHPROC);
   
   pst.event = RGAC_RGM_EVTBNDREQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Send the request to the GCP --*/
   RGAC_RGM_BNDREQ(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlRgmBndReq --*/


/**
 * @brief XTA Bind Confirm Handler for RGM interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgmBndCfm 
 *     
 *     Validates a Bind Confirm from MAC to RGM. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_INT 
 **/

#ifdef ANSI
PUBLIC S16 rgAcHdlRgmBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlRgmBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   Status        status = CM_BND_OK;
 
   TRC2(rgAcHdlRgmBndCfm);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgmBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgmBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlRgmBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   rgMsg = (RgAccMsgQElm *)msg->data;
   
   cmXtaGetPst(&pst, RGAC_RGM_PROVENT, RGSCH_INST_START , RGAC_RGM_USERENT, RGAC_RGM_USERINST,RGAC_RGM_SRCPROC, RGAC_RGM_DSTPROC, RGAC_RGM_MATCHPROC);
   
   pst.event = RGAC_RGM_EVTBNDCFM;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rgMsg->u.rgmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rgMsg->u.rgmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rgAcHdlRgmBndCfm --*/

/**
 * @brief XTA UnBind Request Handler for RGM interface. 
 *
 * @details
 *
 *     Function : rgAcHdlRgmUbndReq 
 *     
 *     Issues an Un-Bind request from RGM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/ 

#ifdef ANSI
PUBLIC S16 rgAcHdlRgmUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rgAcHdlRgmUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   Reason         reason = 0;
   
   TRC2(rgAcHdlRgmUbndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgmUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlRgmUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaGetPst(&pst, RGAC_RGM_USERENT, RGAC_RGM_USERINST, RGAC_RGM_PROVENT, RGSCH_INST_START, RGAC_RGM_SRCPROC, RGAC_RGM_DSTPROC, RGAC_RGM_MATCHPROC);
   
   pst.event = RGAC_RGM_EVTUBNDREQ;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
   /* Send the request to the MAC --*/
   RGAC_RGM_UBNDREQ(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rgAcHdlRgmUbndReq --*/


/**
 * @brief XTA  Periodic Config Request Handler for RGM interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCfgPrdRprt
 *     
 *     Issues PRB usage periodic config request from RGM to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_RSRC
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCfgPrdRprt
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 rgAcHdlCfgPrdRprt(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   RgmPrbRprtCfg  *cfg;
   Pst            pst;
   SpId           spId = 0;

 
   TRC2(rgAcHdlCfgPrdRprt);
 

   CMXTA_ZERO(&pst, sizeof(Pst));
   SGetSBuf(cmXtaCb.init.region, cmXtaCb.init.pool, (Data **)&cfg, sizeof(RgmPrbRprtCfg));
   if (cfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cfg->bCellId = 0;

   pst.event = RGAC_RGM_EVTCFGPRBREPRT;


   cmXtaGetPst(&pst, RGAC_RGM_USERENT, RGAC_RGM_USERINST,RGAC_RGM_PROVENT,RGSCH_INST_START, RGAC_RGM_SRCPROC, RGAC_RGM_DSTPROC, RGAC_RGM_MATCHPROC);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "periodicity",  &(cfg->usPrbAvgPeriodicty));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "cfgType",  &(cfg->bConfigType));
   
   /* Send the request to the LM */
   RGAC_RGM_PRB_RPRT_CONFIG(&pst, spId, cfg);
 
   RETVALUE(CMXTA_ERR_NONE);
}/* rgAcHdlCfgPrdRprt*/

/**
 * @brief Periodic PRB report Indication Handler for RGM interface. 
 *
 * @details
 *
 *     Function : rgAcHdlCfgPrdRprtInd
 *     
 *     Validates Periodic PRB report Indication primitive recieved from MAC SCH
 *     to Dummy-RGM against tester provided input and cached  information.
 *     
 *  @param[in] CmXtaTCCb *tcCb 
 *  @param[in] CmXtaSpCb *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlCfgPrdRprtInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rgAcHdlCfgPrdRprtInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RgAccMsgQElm  *rgMsg = NULLP;
   Pst           pst;

   TRC2(rgAcHdlCfgPrdRprtInd);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCfgPrdRprtInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlCfgPrdRprtInd(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcHdlCfgPrdRprtInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rgMsg = (RgAccMsgQElm *)msg->data;
   cmXtaGetPst(&pst, RGAC_RGM_PROVENT, RGSCH_INST_START , RGAC_RGM_USERENT, RGAC_RGM_USERINST,RGAC_RGM_SRCPROC, RGAC_RGM_DSTPROC, RGAC_RGM_MATCHPROC);

   pst.event = RGAC_RGM_EVTCFGPRBREPRTIND;

   if (cmXtaValidatePst(&(msg->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcHdlCfgPrdRprtInd */
 

/********************************************************************30**

         End of file:     rgac_rgmhdl.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Thu May 23 19:17:22 2013

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
/main/1      ---     ns  1. Initial Release.
/main/2      ---     ns  1. LTE MAC 2.1 release
             rg001.201 sm 1. Added TTI indication towards RGM user.
             rg004.201 rnt 1. Modified for SI Enhancement
/main/3      ---        dvasisht          1. Updated for LTE MAC Release 3.1
*********************************************************************91*/
