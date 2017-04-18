
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_egthdl.c

     Sid:      egac_edmhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:25 2015

     Prg:     an
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "eg.h"            /* defines and macros for EG */
#include "leg.h"            /* defines and macros for EG */
#include "egt.h"            /* defines and macros for EG */
#include "eg_err.h"        /* EG error defines */
#include "egac_acc.h"        /* defines for EG acceptance tests */
#include "cm_xta.h" 
#if 0
#include "eg_dbs11.h"
#include "egac_edm.h"
#endif
/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
#include "eg_util.h"

#include "cm_xta.x" 
#include "leg.x"           /* layer management typedefs for EGCP */
#include "egt.x"           /* typedefs for EGCP */
#include "eg.x"            /* typedefs for EGCP */
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "egac_acc.x"      /* typedefs for EGCP acceptance tests */
#include "egac_egt.x"
#include "egac_edm.x"
#include "eg_util.x"
#if 0
#include "eg_dbs11.x"
#include "eg_dbs5.x"
#endif



/*
*
*       Fun:   egAcHdlEdmSigReq
*
*       Desc:  Handler function for Signalling Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmSigReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmSigReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   EgMsg         *egMsg = NULLP;
   U8             intfType=EGT_GTP_INT_S11; 
   Bool           evntMsgPres = TRUE;
   Bool           pthMsg = FALSE;
   Bool           invalidPst = FALSE;
   Bool           egMsgPres = TRUE;
   EgEvnt        *evntMsg = NULLP;
 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmSigReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmSigReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmSigReq(), tcId (%ld)\n", tcCb->tcId));
#endif

   /* Provide the flesible whether to fill the event message or not */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "invalidPst", &invalidPst);
   if ( invalidPst )
   {
      egCb.init.region = 100;
      egCb.init.pool = 100;
   }
   
   /* Provide the flesible whether to fill the event message or not */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "evntMsgPres", &evntMsgPres);
   if (evntMsgPres)
   {

      /* Provide the flesible whether to frame the egtp message or not */
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "egMsgPres", &egMsgPres);
      if(egMsgPres)
      {
         /* If egMsgPres is true, then only fill the message else send the empty egMsg */
         if ((ret = egAcUtlEdmBuildMsg(tcCb, spCb,
                                  &egMsg)) != CMXTA_ERR_NONE)
         RETVALUE(ret);

      }
      else
      {
         egMsg= NULLP;
      }
      /*******************************************************
       **  Expect from the xml to get the interface **********
      *******************************************************/
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
            "evntIntfType", &intfType); 

      ret = egAcUtlEdmMakeEvntMsg(&evntMsg, egMsg, intfType, NULLP, EVTEDMENCREQ);
    
   }
   /* Send the message to the EDM module for encoding the message */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "pthMsg", &pthMsg
);
   if (!pthMsg)
      EuLiEdmEncReq(evntMsg);
   else
      EuLiEdmEncPthReq(evntMsg);
  

      /* eg006.201: fix for mem leak --*/
      EgUtilDeAllocGmMsg(&egMsg)

   RETVALUE(CMXTA_ERR_NONE);
} /* egAcHdlEdmSigReq*/


/*
*
*       Fun:   egAcHdlEdmErrInd
*
*       Desc:  Handler function for error Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmErrInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmErrInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmErrInd);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmErrInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmErrInd(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if ((ret = egAcUtlEdmValidateMsg(tcCb, spCb, EVTEDMERRIND)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
 
   RETVALUE(CMXTA_ERR_NONE);
} /* egAcHdlEdmErrInd */


/*
*
*       Fun:   egAcHdlEdmSigInd
*
*       Desc:  Handler function for Signalling Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmSigInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmSigInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmSigInd);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmSigInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmSigInd(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if ((ret = egAcUtlEdmValidateMsg(tcCb, spCb, EVTEDMSIGIND)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
 
   RETVALUE(CMXTA_ERR_NONE);
} /* egAcHdlEdmSigInd */


/*
*
*       Fun:   egAcHdlEdmSigRsp
*
*       Desc:  Handler function for Signalling Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmSigRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmSigRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   EgMsg  *egMsg;
   Bool          evntMsgPres=TRUE;
   U8        intfType=0; 
   Bool          egMsgPres = TRUE;
   EgEvnt *evntMsg = NULLP;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmSigRsp)

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmSigRsp(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmSigRsp(), tcId (%ld)\n", tcCb->tcId));
#endif

   /* Provide the flesible whether to fill the event message or not */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "evntMsgPres", &evntMsgPres);

   if (evntMsgPres)
   {

      /* Provide the flesible whether to frame the egtp message or not */
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "egMsgPres", &egMsgPres);
      if(egMsgPres)
      {
         /* If egMsgPres is true, then only fill the message else send the empty egMsg */
         if ((ret = egAcUtlEdmBuildMsg(tcCb, spCb,
                     &egMsg)) != CMXTA_ERR_NONE)
            RETVALUE(ret);

      }
      else
      {
         egMsg = NULLP;
      }
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "intfType", &intfType); 
      if(ret == CMXTA_ERR_NO_VALUE)
      {
         CMXTA_DBG_ERR((_cmxtap,"interface type is expected from the xml \n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      ret = egAcUtlEdmMakeEvntMsg(&evntMsg, egMsg, intfType, NULLP, EVTEDMENCREQ);
   }
   /* Send the message to the EDM module for encoding the message */
   EuLiEdmEncReq(evntMsg);


   RETVALUE(ROK);
}/* egAcHdlEdmStaInd */


/*
*
*       Fun:   egAcHdlEdmSigCfm
*
*       Desc:  Handler function for Signalling Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmSigCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmSigCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmSigCfm);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmSigCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmSigCfm(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if ((ret = egAcUtlEdmValidateMsg(tcCb, spCb, EVTEDMSIGCFM)) != CMXTA_ERR_NONE)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* egAcHdlEdmSigCfm*/

/*
*
*       Fun:   egAcHdlEdmShutDownReq
*
*       Desc:  Handler function for shutdowning the edm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmShutDownReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmShutDownReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   U8             intfType=0;
   
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmShutDownReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmShutDownReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmShutDownReq(), tcId (%ld)\n", tcCb->tcId));
#endif

  
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "intfType", &intfType); 
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"interface type is expected from the xml \n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   EuLiEdmShutdown(intfType);   
   RETVALUE(ROK);

}

/*
*
*       Fun:   egAcHdlEdmMsgCfg
*
*       Desc:  Handler function for Signalling Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmMsgCfg
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmMsgCfg(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            retVal = ROK;
   EgMngmt        cfg;
   EgIeDictCfg    *ieCfg = NULLP;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmMsgCfg);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmMsgCfg(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmMsgCfg(), tcId (%ld)\n", tcCb->tcId));
#endif

   /*-- Initialise the Cfg structure */
   CMXTA_ZERO(&cfg, sizeof(EgMngmt));

   /**************************************************
   *               INITIALIZE THE EDMCB              *
   **************************************************/
   retVal = egEdmInitDb();
   if(retVal != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"INIT THE DB FAILED\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   /********************************************
    *          Make the IE entries             *
   ********************************************/
   ieCfg = &(cfg.u.cfg.s.ieDictCfg);
   cmMemset((U8 *)ieCfg->posIdx, 0, LEG_MAX_IES);
   cmMemset((U8 *)ieCfg->ieEntry, 0, LEG_MAX_IES_ALL_MSGS * sizeof(LegIeEntry));
   egMakeIeDict( ieCfg->ieEntry,  &ieCfg->nmbIe, ieCfg->posIdx);
   populateIeConfigInTA(tcCb, spCb, FALSE);
   EuLiEdmIeCfg(ieCfg);

   /********************************************
    *          Make the GTP MSG  entries       *
   ********************************************/
   retVal = egAcUtlEgBuildGmCfgReq(tcCb, spCb, &cfg);
   if(retVal != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"Building the gm msg dict failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   EuLiEdmGmCfg(&cfg.u.cfg.s.gmDictCfg);
   RETVALUE(CMXTA_ERR_NONE);
}



/*
*
*       Fun:   egAcHdlEdmMsgInd
*
*       Desc:  Handler function for Msg Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmMsgInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmMsgInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   CmXtaMsgQElm   *msg = NULLP;
   EgAccMsgQElm   *egtpMsg = NULLP;
   EgAcTCCb       *egTcCb = NULLP;
   Bool           trueMbuf=TRUE;
   Bool           pthMsg=FALSE;
   Bool           mBufPres=TRUE;
   Bool           evntMsgPres=TRUE;
   Bool           egMsgPres=TRUE;
   Bool           invalidPst=FALSE;
   Bool           invalMsgLen=FALSE;
   Bool           invalMsgLen1=FALSE;
   EgMsg          *egMsg=NULLP;
   EgEvnt         *evntMsg = NULLP;
   Buffer         *mBuf;
   U8             spare[30];

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmMsgInd);
 
  
#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmMsgInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmMsgInd(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   egTcCb = (EgAcTCCb *)tcCb->tcCb;

      ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "invalMsgLen", &invalMsgLen);

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcUtlEdmValidateMsg(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;
   
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "invalidPst", &invalidPst);
   if ( invalidPst )
   {
      egCb.init.region = 100;
      egCb.init.pool = 100;
   }

   /**************************************************
    *  Get the info whether to send the real mBuf or *
   **************************************************/
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "trueMbuf", &trueMbuf); 
   if( trueMbuf )
   {
      /************************************************************
       *   Frame the event message and then pass it to the decode *
      ************************************************************/
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "intfType", &egtpMsg->u.edmInfo.intfType); 
      if(ret == CMXTA_ERR_NO_VALUE)
      {
         CMXTA_DBG_ERR((_cmxtap,"interface type is expected from the xml \n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      /*********************************************
      *  To test the negative scenarios            *
      *********************************************/
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "evntMsgPres", &evntMsgPres);
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "egMsgPres", &egMsgPres);
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "mBufPres", &mBufPres);
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "invalMsgLen1", &invalMsgLen1);
      if(!mBufPres)
      {
         egtpMsg->u.edmInfo.mBuf = NULLP;
      }

      /*******************************************************
       **  Expect from the xml to get the interface **********
      *******************************************************/
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
            "evntIntfType", &egtpMsg->u.edmInfo.intfType); 

      cmMemset((U8 *)spare,0,10);
      if(invalMsgLen)
      {
         SGetMsg(0, 0, &mBuf);
         SRemPreMsgMult(spare, 6, egtpMsg->u.edmInfo.mBuf); 
         SAddPstMsgMult((U8 *)spare, 6, mBuf);
         ret = egAcUtlEdmMakeEvntMsg(&evntMsg, NULLP, egtpMsg->u.edmInfo.intfType, mBuf, EVTEDMDECREQ);  
      }
      else if(invalMsgLen1)
      {
         SGetMsg(0, 0, &mBuf);
         SRemPreMsgMult(spare, 25, egtpMsg->u.edmInfo.mBuf); 
         SAddPstMsgMult((U8 *)spare, 25, mBuf);
         ret = egAcUtlEdmMakeEvntMsg(&evntMsg, NULLP, egtpMsg->u.edmInfo.intfType, mBuf, EVTEDMDECREQ); 
      } 
      else
      {
         ret = egAcUtlEdmMakeEvntMsg(&evntMsg, NULLP, egtpMsg->u.edmInfo.intfType, egtpMsg->u.edmInfo.mBuf, EVTEDMDECREQ);  
      }

      if(!evntMsgPres)
      {
         evntMsg = NULLP;
      }
      else if(!egMsgPres)
      {
         evntMsg->u.mBuf = NULLP;
      }
   }
   else
   {
      if( (ret = egAcUtlDEdmBuildMsg(tcCb, spCb, &egMsg)) != CMXTA_ERR_NONE)
      {
         RETVALUE(ret);
      }
      /*********************************************
      *  Dump the dummy msg framed                 *
      *********************************************/
      EgUtilGmDump(egMsg);
      
      if(egMsg)
      {
         if( egAcEncEgMsg(tcCb, spCb, egMsg, &mBuf) !=  ROK)
         {
            CMXTA_DBG_ERR((_cmxtap,"Unable to encode the message"));
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      else
      {
         CMXTA_DBG_ERR((_cmxtap,"Unable to build the dummy message"));
         RETVALUE(CMXTA_ERR_INT);
      }
      ret = egAcUtlEdmMakeEvntMsg(&evntMsg, NULLP, egtpMsg->u.edmInfo.intfType, mBuf, EVTEDMDECREQ);
   }
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   cmMemset((U8 *)spare,0,10);
   if(invalMsgLen)
   {
      SGetMsg(0, 0, &mBuf);
      SRemPreMsgMult(spare, 6, egtpMsg->u.edmInfo.mBuf); 
      SAddPstMsgMult((U8 *)spare, 6, mBuf);
      evntMsg->u.mBuf = mBuf;
   }
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "pthMsg", &pthMsg);
   if (!pthMsg)
      EuLiEdmDecReq(evntMsg);
   else
      EuLiEdmDecPthReq(evntMsg);

   RETVALUE(CMXTA_ERR_NONE);
} /* egAcHdlEdmMsgInd */


/*
*
*       Fun:   egAcHdlEdmMsgReq
*
*       Desc:  Handler function for Msg Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmMsgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmMsgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   CmXtaMsgQElm   *msg = NULLP;
   EgAccMsgQElm   *egtpMsg = NULLP;
   EgAcTCCb       *egTcCb = NULLP;
   Bool           mBufVal = FALSE;
 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmMsgReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmMsgReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmMsgReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   egTcCb = (EgAcTCCb *)tcCb->tcCb;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcUtlEdmValidateMsg(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;

   if ( egtpMsg->u.edmInfo.choice != EVTEDMENCREQ )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Msg MisMatch: exp (%d) recvd (%d) \n", 1 , egtpMsg->u.edmInfo.choice), 2);
   
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "mBufVal", &mBufVal); 
   if (mBufVal)
   {
      if ((ret = egAcUtlDEdmValidateMsg(tcCb, spCb, egtpMsg->u.edmInfo.mBuf)) != 
                                                                  CMXTA_ERR_NONE)
      {
         cmXtaFlushMsg(&(tcCb->msgQ[0]), msg);
         RETVALUE(ret);
      }
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* egAcHdlEdmMsgInd */


/*
*
*       Fun:   egAcHdlEdmCfgCfm
*
*       Desc:  Handler function for Config Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcHdlEdmCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 egAcHdlEdmCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   CmXtaMsgQElm   *msg=NULLP;
   EgAccMsgQElm   *egtpMsg = NULLP;
   CmStatus        status;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHdlEdmCfgCfm);
 
   cmMemset((U8*)&status, 0 , sizeof(CmStatus));
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
   egtpMsg = (EgAccMsgQElm *)msg->data;
#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmCfgCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEdmCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#endif
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);
   
   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(egtpMsg->u.egtInfo.u.egMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcHdlEdmCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function--*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}

/********************************************************************30**

         End of file:     egac_edmhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:25 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3    eg003.201  psingh      1. Merged code from eg006.102 to Fix
                                     TRACE5 macro related issue
/main/3    eg006.201  psingh      1. Fixed mem leak by freeing unused egMsg pointer
*********************************************************************91*/
