
/********************************************************************20**

     Name:    EGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_egtreg.c

     Sid:      egac_edmutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:26 2015

     Prg:     pc

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */

#include "eg_util.h"       /* Egtpeter Utility library */
#include "egt.h"           /* Egtpeter Upper Interface */
#include "eg.h"           /* Egtpeter Upper Interface */
#include "eg_edm.h"
#include "egac_edm.h"           /* Egtpeter Upper Interface */
#include "leg.h"           /* Egtpeter Layer Manager   */
#if 0
#include "eg_dbs11.h"           /* Egtpeter Upper Interface */
#endif
#ifdef EGTP_C
#include "eg_dbs3.h"           /* Egtpeter Upper Interface */
#include "eg_dbs4.h"           /* Egtpeter Upper Interface */
#include "eg_dbs10.h"           /* Egtpeter Upper Interface */
#include "eg_dbs16.h"           /* Egtpeter Upper Interface */
#endif
#include "egac_acc.h"           /* Egtpeter Upper Interface */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.h"
#include "cm_dns.x"

#include "egt.x"           /* Eg Upper Interface */
#include "leg.x"           /* Eg layer manager  */

#include "cm_xta.h"
#include "egac_acc.h"
#include "eg.x"
#include "cm_xta.x"
#include "egac_acc.x"
#include "egac_edm.x"
#include "eg_edm.x"
#include "eg_util.x"       /* Eg Utility library */
#if 0
#include "eg_dbutl.x"           /* Egtpeter Upper Interface */
#include "eg_dbs11.x"           /* Egtpeter Upper Interface */
#include "eg_dbs5.x"           /* Egtpeter Upper Interface */
#endif
#ifdef EGTP_C
#include "eg_dbs3.x"           /* Egtpeter Upper Interface */
#include "eg_dbs4.x"           /* Egtpeter Upper Interface */
#include "eg_dbs10.x"           /* Egtpeter Upper Interface */
#include "eg_dbs16.x"           /* Egtpeter Upper Interface */
#endif

PUBLIC EgAccCb egAccCb;
PUBLIC EgCb  egCb;



/*
 *
 *       Fun:   egAcUtlEdmBuildMsg
 *
 *       Desc:  Build the EGTP Message
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function Builds the EGTP message to be sent to EG Layer 
 *              
 *
 *       File: egac_egtutl.c 
 *
 */

#ifdef ANSI
PUBLIC S16 egAcUtlEdmBuildMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg      **egMsg
)
#else
PUBLIC S16 egAcUtlEdmBuildMsg (tcCb, spCb,egMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg      **egMsg;
#endif
{
   U8            msgType = 0;
   S16            ret = 0;

   TRC2(egAcUtlEdmBuildMsg)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlEdmBuildMsg(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlEdmBuildMsg(), tcId (%d)\n", tcCb->tcId));
#endif

   *egMsg = NULLP;

   /*  Default CSR*/
   msgType = (U8) EGT_GTPC_MSG_CS_REQ;
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "msgType",  &(msgType));
   if( msgType == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlEdmBuildMsg(), msg Type is needed from xml\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Build the Eg Message   */ 
   ret = egAcEdmBuildEgMsg(tcCb,spCb,msgType,egMsg);
   if ( ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /*-- egAcUtlEdmBuildMsg --*/



/*
*
*       Fun:   egAcSndErrMsgToApp
*
*       Desc:  This function sends a error indication to the application
*              based on eventMsg given
*
*       Ret:   ROK     - ok
*              RFAILED - failure
*
*       Notes: None
*
*       File:  egac_edmutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcSndErrMsgToApp
(
EgEvnt   *eventMsg      /* event message */
)
#else
PUBLIC S16 egAcSndErrMsgToApp(eventMsg)
EgEvnt   *eventMsg;      /* event message */
#endif
{
   /* return value */
   S16        retValue = ROK;

   /* this will hold the error indication details */
   EgErrEvnt  errEvnt;


   cmMemset( (U8* )&errEvnt, 0, sizeof(EgErrEvnt));

   if ( eventMsg)
   {
      /* set the variables in the error event */
      errEvnt.errCause = eventMsg->resultType;

      /* Assign seqNo  only if it is present */
      /* TODO - if(eventMsg->seqNoPres) */
      {
         errEvnt.seqNo = eventMsg->seqNumber;
      } /* end of if seq no present */
#ifdef NEXT
      /* TODO _WILL BE REMOVED LATER */
      /*  Assign the seqNO from egMsg as the enc/dec has assigned the decoded
         seq No in egMsg */
      else
      {
         errEvnt.seqNo = eventMsg->u.egMsg->msgHdr.seqNumber;
      }
#endif /* NEXT */ 
      if (eventMsg->failedIeType)
      {
         errEvnt.failedIeType = eventMsg->failedIeType;
         errEvnt.failedIeInst = eventMsg->failedIeInst;
      } /* end of if failed IE Type is present */

      errEvnt.failedMsgType = eventMsg->failedMsgType;
   }
   else
   {
      errEvnt.errCause = EGT_ERR_MSG_UNABLE_TO_COMPLY;
   }
   /* call the error indication API */
   if ( (retValue = EuLiEdmErrInd(errEvnt)) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlEdmMakeEvntMsg(), sending message to app fails"));
      RETVALUE(CMXTA_ERR_INT);
   } /* end of if sending error indication to application fails */

   if( eventMsg )
   {
      /* de-allocate the eGTP message */
      retValue = EgUtilDeAllocGmMsg(&eventMsg->u.egMsg);
   }
   /* return success */
   RETVALUE(ROK);
} /* end of egAcSndErrMsgToApp */

/*
 *
 *       Fun:   egAcUtlEdmValidateMsg
 *
 *       Desc:  Validate the eGTP Message
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function used to validate the message
 *
 *       File: egac_eguutl.c 
 *
 */


#ifdef ANSI
PUBLIC S16 egAcUtlEdmValidateMsg
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
U8            apiType
)
#else
PUBLIC S16 egAcUtlEdmValidateMsg (tcCb, spCb,apiType)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
U8        apiType;
#endif
{
   S16            ret = 0;
   CmXtaMsgQElm   *msg = NULLP;
   EgAccMsgQElm   *egtpMsg = NULLP;
   EgAcEgtInfo    *egtInfo = NULLP;
   EgIeLevelInfo ieLvlInfo;
   EgMsgHdr       egHdr;  
   EgAcTCCb       *egTcCb = NULLP;
 
   TRC2(egAcUtlEdmValidateMsg)

   cmMemset((U8*)&ieLvlInfo, 0 , sizeof(EgIeLevelInfo));
   cmMemset((U8*)&egHdr, 0 , sizeof(EgMsgHdr));
   egTcCb = (EgAcTCCb *)tcCb->tcCb;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlEdmValidateMsg(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlEdmValidateMsg(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset( (U8* )&ieLvlInfo, 0, sizeof(EgIeLevelInfo));
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcUtlEdmValidateMsg(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   egtpMsg = (EgAccMsgQElm *)msg->data;

   egtInfo    = &(egtpMsg->u.egtInfo);

   if((egtInfo->choice) != apiType)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);   
   }
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   switch(apiType)
   {
      case EVTEDMSIGIND:
      {

         ret = egAcUtlEdmValidateGmMessage(tcCb,spCb,(EgMsg*)(egtInfo->u.egSigIndEvt.egMsg));
         if( ret != CMXTA_ERR_NONE)
         {
            cmXtaFlushMsg(&(tcCb->msgQ[0]), msg);
            RETVALUE(ret);
         }
         break;
      }
      case EVTEDMSIGCFM:
      {
         ret = egAcUtlEdmValidateGmMessage(tcCb,spCb,
                          (EgMsg*)(egtInfo->u.egSigCfmEvt.egMsg));
         if( ret != CMXTA_ERR_NONE)
         {
            cmXtaFlushMsg(&(tcCb->msgQ[0]), msg);
            RETVALUE(ret);
         }

         break;
      }
      case EVTEDMERRIND:
      {
         /* Validate Error Indication */
         ret = egAcUtlEdmValidateErrIndMsg(tcCb,spCb,(&egtInfo->u.errEvt.errInd));
         if( ret != CMXTA_ERR_NONE)
         {
            cmXtaFlushMsg(&(tcCb->msgQ[0]), msg);
            RETVALUE(ret);
         }
         break;
      }
  
      default:
      {
         break;   
      }
   } /* End of switch   */

   cmXtaFlushMsg(&(tcCb->msgQ[0]), msg);

   /* validation of the message is successful */
   RETVALUE(CMXTA_ERR_NONE);
} /*-- egAcUtlEdmValidateMsg --*/


/*
*
*       Fun:   egAcUtlEdmValidateGmMessage
*
*       Desc:  This function is used to validate Gm Msg 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcUtlEdmValidateGmMessage
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg       *egMsg
)
#else
PUBLIC S16 egAcUtlEdmValidateGmMessage(tcCb,spCb,egMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg       *egMsg;
#endif
{
   U16               ret=0;
   U16               ret1=0;
   U16               ret2=0;
   S16               isIePresent = 0;
   EgIeLevelInfo    ieLevelInfo;
   U16               iePresInLevel=0;
   EgIe             *egIe = NULLP;
   U16               iePos = 0;
   U16               ieCntLevel = 0;
   S16               ieCnt = 0;
   U8                ieInst = 0;
   U8                ieTypeInst = 0;
   U8                msgType = 0;
   S16               ieTypeForCnt = 0;
   
   TRC2(egAcUtlEdmValidateGmMsgInd)

   if(egMsg == NULLP)
   {
       RETVALUE(CMXTA_ERR_INT);
   }

   cmMemset( (U8* )&ieLevelInfo, 0, sizeof(EgIeLevelInfo));

   /* Get the type of message you are expecting */
   ret2 =   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"msgType",&msgType);
   if ( ret2 == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"msgType is not provided from the xml's\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   if ( msgType != egMsg->msgHdr.msgType)
   {
      CMXTA_DBG_ERR((_cmxtap,"msgType is not matching with the rcvd msg Type \n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   /* Get the value of IE code whose Occurence needs to be checked from the xml file   */
   ret =   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"isIePresent",&isIePresent);

   /* Get the value of IE Instance whose Occurence needs to be checked from the xml file   */
   ret2 =   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"ieInst",&ieInst);


   /* If the occurence Needs to be checked in a particular level , the test case
   writer should ensure that ieLevel attribute is given, otherwise it checks
   in the level 0 */

   ret1 =   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"iePresInLevel",&iePresInLevel);

   
   /*Validation is done only if the value is given from xml file */
   if( ret != CMXTA_ERR_NO_VALUE)
   {
#ifdef EG_PHASE2
      /* Validate the occurence of the IE*/
      ieLevelInfo.level = iePresInLevel;
      ieLevelInfo.ieInfo[iePresInLevel].ieTypePres= TRUE;      
      ieLevelInfo.ieInfo[iePresInLevel].ieType= isIePresent;
      ieLevelInfo.ieInfo[iePresInLevel].ieInst= ieInst;

      if (EgUtilGmGetIe(egMsg,&ieLevelInfo,&egIe,&iePos) == ROK )
      {
         if (egIe == NULLP)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : mismatch: IE with Type (%d) is not present in level (%d) of the message\n", isIePresent, iePresInLevel),2);

            RETVALUE(CMXTA_ERR_INT);
         } /*End of checking whether the Ie is present or not */

      } /* End of Get Ie */
#endif
   } /* End of validation for the presence of an IE  */


   /* Get the value of IE code whose count at a particular level needs to be checked from the xml file   */
   ret =   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"ieTypeForCnt",&ieTypeForCnt);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"ieTypeInst",&ieTypeInst);
   ret =   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16,"ieCnt",&ieCnt);

/* If the count of IE Needs to be checked in a particular level , the test case
   writer should ensure that ieCntLevel attribute is given, otherwise it checks
   in the level 0 */

   ret1 =   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"ieCntLevel",&ieCntLevel);
   /*Validation is done only if the value is given from xml file */
   if( ret != CMXTA_ERR_NO_VALUE)
   {
#ifdef EG_PHASE2
      /* Validate the count of the IE*/
      ieLevelInfo.level = ieCntLevel;
      ieLevelInfo.ieInfo[iePresInLevel].ieTypePres = TRUE;      
      ieLevelInfo.ieInfo[iePresInLevel].ieType= ieTypeForCnt;      
      ieLevelInfo.ieInfo[iePresInLevel].ieInst= ieTypeInst;      

      if( EgUtilGmGetIeCnt(egMsg,&ieLevelInfo,&ieCnt) == ROK )
      {
           /* */
      } /* End of Get Ie */
#endif
   } /* End of validation for the presence of an IE  */

   RETVALUE(CMXTA_ERR_NONE);

} /* egAcEdmValidateGmMessage  */


/*
*
*       Fun:   egAcUtlEdmValidateErrIndMsg
*
*       Desc:  This function is used to validate Error Indication Message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcUtlEdmValidateErrIndMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgErrEvnt   *eguErrIndEvt
)
#else
PUBLIC S16 egAcUtlEdmValidateErrIndMsg(tcCb,spCb,eguErrIndEvt)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgErrEvnt   *eguErrIndEvt;
#endif
{
   U16         ret = 0;
   U8          xmlErrType = 0;
   U8          xmlIeType = 0;
   U8          xmlIeInst = 0;

   TRC2(egAcUtlEdmValidateErrIndMsg)

   /* Get the value of Error Type from xml file and validate  */
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,"errType",&(xmlErrType));
   if(xmlErrType != eguErrIndEvt->errCause)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlEdmValidateErrIndMsg() Expected Error Type [%d]: Received Error Type [%d]",
                  xmlErrType, eguErrIndEvt->errCause));
      RETVALUE(CMXTA_ERR_INT);
   }
   
   ret= cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8,"ieType",&xmlIeType);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8,"ieInst",&xmlIeInst);
   if(ret != CMXTA_ERR_NO_VALUE)
   {
      if( (xmlIeType != eguErrIndEvt->failedIeType) && (xmlIeInst != eguErrIndEvt->failedIeInst))
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlEdmValidateErrIndMsg() Expected IeType [%d]: Received IeType [%d]",xmlIeType,                                eguErrIndEvt->failedIeType));
         RETVALUE(CMXTA_ERR_INT);
      }
   } /*end of validation of the IE Type */ 


   RETVALUE(CMXTA_ERR_NONE);

} /* egAcUtlEdmValidateErrIndMsg */


/*
*
*       Fun:   egTptProcessMsg
*
*       Desc:  Function to send the message for decoding
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 egTptProcessMsg
(
EgEvnt *evntMsg        /* Event structure having the egMsg */
)
#else
PUBLIC S16 egTptProcessMsg( evntMsg)
EgEvnt *evntMsg;        /* Event structure having the egMsg */
#endif
{
   S16  retVal = ROK;
   TRC3(egTptProcessMsg)

   /************************************************
    ****  Store the mbuf and the interface type  ***
   ************************************************/
   egAccCb.intfType = evntMsg->intfType;
   if ( (retVal = EuLiEdmTptMsg(evntMsg->intfType, evntMsg->u.mBuf))!= ROK)
   
   {
      CMXTA_DBG_ERR((_cmxtap,"egTptProcessMsg(), sending message to app fails"));
      RETVALUE(CMXTA_ERR_INT);
   }
   RETVALUE(ROK);
}



/*
*
*       Fun:   egTunReceive
*
*       Desc:  Function to send the message for decoding
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 egTunReceive
(
EgEvnt *evntMsg        /* Event structure having the egMsg */
)
#else
PUBLIC S16 egTunReceive(evntMsg)
EgEvnt *evntMsg;        /* Event structure having the egMsg */
#endif
{
   S16  retVal = ROK;
   TRC3(egTunReceive)

   /************************************************
    ****  Store the mbuf and the interface type  ***
   ************************************************/
   if ( (retVal = EuLiEdmGmSigInd( evntMsg->u.egMsg))!= ROK)
   
   {
      CMXTA_DBG_ERR((_cmxtap,"egTunReceive(), sending message to app fails"));
      RETVALUE(CMXTA_ERR_INT);
   }
   RETVALUE(ROK);
}

/*
*
*       Fun:   egGetIntfFrmTeid
*
*       Desc:  Function to get the interface from the teid
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC EgtIntf egGetIntfFrmTeid
(
U32       teid
)
#else
PUBLIC EgtIntf egGetIntfFrmTeid(teid)
U32       teid;           /* Teid value */
#endif
{
    
   RETVALUE( egAccCb.intfType);
}



/*
*  
*       Fun:   egAcUtlEgBuildGmCfgReq
*  
*       Desc:  Utility Function to Build General Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcUtlEgBuildGmCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
EgMngmt     *egMngmt
)
#else
PUBLIC S16 egAcUtlEgBuildGmCfgReq(tcCb,spCb,egMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
EgMngmt    *egMngmt;
#endif
{
   /* local variables */
   EgGmDictCfg     *cfg = NULLP;
   U8             intfType = 0;
   S16            ret=ROK;
   U8             invNmbMsg = FALSE; 
   TRC2(egAcUtlEgBuildGmCfgReq)
 
   cfg = &(egMngmt->u.cfg.s.gmDictCfg);

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "intfType", &intfType); 
   if(ret == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"interface type is expected from the xml \n"));
      RETVALUE(CMXTA_ERR_INT);
   } 
   cfg->intfType = intfType;

   /****************************************************
   *       Allocate the memory for th max messages     *
   ****************************************************/

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nmbMsg", &(cfg->nmbMsg));

   if (ret == CMXTA_ERR_NO_VALUE)
   {
      if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&cfg->gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
      {
         CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
         RETVALUE(CMXTA_ERR_INT);
        
      }
      cmMemset ( (U8*)cfg->gmEntry, 0, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))); 

   }
   else
   {

      if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&cfg->gmEntry, (cfg->nmbMsg * sizeof(LegMsgEntry))) != ROK))
      {
         CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
         RETVALUE(CMXTA_ERR_INT);
        
      }
      cmMemset ( (U8*)cfg->gmEntry, 0, (cfg->nmbMsg * sizeof(LegMsgEntry))); 

   }

   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "invNmbMsg",
   &invNmbMsg);

   switch(intfType)
   {
      case EGT_GTP_INT_S3:
      {  
         egMakes3GmDict( cfg->gmEntry, &cfg->nmbMsg);
         populateGmConfigInTA(tcCb, spCb, intfType, FALSE);
         break;
      }
      case EGT_GTP_INT_S4:
      {  
         egMakes4GmDict( cfg->gmEntry, &cfg->nmbMsg);
         populateGmConfigInTA(tcCb, spCb, intfType, FALSE);
         break;
      }
      case EGT_GTP_INT_S10:
      {  
         egMakes10GmDict( cfg->gmEntry, &cfg->nmbMsg);
         populateGmConfigInTA(tcCb, spCb, intfType, FALSE);
         break;
      }
      case EGT_GTP_INT_S5_S8:
      {  
         egMakes5GmDict( cfg->gmEntry, &cfg->nmbMsg);
         populateGmConfigInTA(tcCb, spCb, intfType, FALSE);
         break;
      }
      case EGT_GTP_INT_S11:
      {  
         egMakes11GmDict( cfg->gmEntry, &cfg->nmbMsg);
         populateGmConfigInTA(tcCb, spCb, intfType, FALSE);
         break;
      }
      case EGT_GTP_INT_S16:
      {  
         egMakes16GmDict( cfg->gmEntry, &cfg->nmbMsg);
         populateGmConfigInTA(tcCb, spCb, intfType, FALSE);
         break;
      }
   }

   if(invNmbMsg)
      cfg->nmbMsg = 30;

   RETVALUE(ROK);
}


/********************************************************************
*
*    Fun:    egEdmInitDb
*
*    Desc:   This is to Init the EDM module
*
*    Ret:    ROK - 
*            RFAILED -  
*
*    Notes:  N/A
*
*    File:   eg_util.c
*
***************************************************************************/
#ifdef ANSI
PUBLIC S16 egEdmInitDb
(
Void
)
#else
PUBLIC S16 egEdmInitDb (Void)
#endif
{
   S16 ret = ROK;
   U8  region=0;
   U8  pool =0;
   U8  nmbIntf =2;

   /* Allocate the memory for the intfLst */
   egCb.genCfg.nmbIntfs = 2;
   ret = egAllocIntfLst(nmbIntf);
   if(ret != ROK)
   {
      (Void) SPutSMem(region, pool);
      RETVALUE(RFAILED);
   }
    
   RETVALUE(ROK);
}
/********************************************************************
*
*    Fun:    egCmPrntDbg
*
*    Desc:   This is used to Print the Debug prints
*
*    Ret:    ROK - 
*            RFAILED -  
*
*    Notes:  N/A
*
*    File:   eg_util.c
*
***************************************************************************/
#ifdef ANSI
PUBLIC Void egCmPrntDbg
(
U8    ptrType,
void  *ptr,
S8    *name
)
#else
PUBLIC Void egCmPrntDbg (ptrType, ptr, name)
U8    ptrType;
void  *ptr;
S8    *name;
#endif
{
   /* TODO: Define this fucntion */
   RETVOID;

}



/************************************************************************************
 *
 *       Fun:   egSendLmAlarm
 *
 *       Desc:  This function is used to send an alarm to layer manager
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ************************************************************************************/
#ifdef ANSI
PUBLIC S16 egSendLmAlarm
(
U16           category,            /* category */
U16           event,               /* event */
U16           cause,               /* cause */
EgUstaDgn     *dgn                 /* diagnostics structure */
)
#else
PUBLIC S16 egSendLmAlarm(category, event, cause, dgn)
U16           category;            /* category */
U16           event;               /* event */
U16           cause;               /* cause */
EgUstaDgn     *dgn;                /* diagnostics status */
#endif
{

   RETVALUE(ROK);

}



/***********************************************************************************
 *
 *       Fun:   egAlloc
 *
 *       Desc:  This function allocates a buffer from the static
 *              pool and updates the memory allocated field.
 *
 *       Ret:   Static buffer pointer     - success
 *              NULLP                     - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/
#ifdef ANSI
PUBLIC Data *egAlloc
(
Size size                      /* size of the buffer required */
)
#else
PUBLIC Data *egAlloc (size)
Size size;                     /* size of the buffer required */
#endif
{
   S16        retValue = 0;    /* Return Value */
   Data       *pCb = NULLP;    /* Memory allocation pointer */
   
   TRC3(egAlloc)

   /************************************
    * Return with NULL if size is zero *
    ************************************/
   if (size == 0)
   {
      RETVALUE(pCb);
   }

   /*************************************************** 
    * Allocate memory from the region and pool of the *
    * global control block                            *
    ***************************************************/
   if ( (retValue = SGetSBuf(egCb.init.region, egCb.init.pool, &pCb, size)) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
       EGLOGERROR(ERRCLS_DEBUG, ELEGXXX, ERRZERO,
                 "egAlloc(): Memory Allocation Failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

   }
   else
   {
      /*************************
       * Initialize the Memory *
       *************************/
      (Void)cmMemset((U8 *) pCb, '\0', size);

   }

   /******************************* 
    * Return the allocated buffer *
    *******************************/
   RETVALUE(pCb);

}


/************************************************************************
 *
 *       Fun:   egFree
 *
 *       Desc:  This fuction frees the memory of size bytes from the
 *              data pointer
 *             
 *
 *       Ret:   ROK     - success
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 * 
*****************************************************************************/

#ifdef ANSI
PUBLIC S16 egFree
(
Data    *data,      /* data pointer */
Size    size        /* Number o bytes to be freed */
)
#else
PUBLIC S16 egFree (data, size)
Data    *data;      /* data pointer */
Size    size;       /* Number o bytes to be freed */
#endif
{

   TRC2(egFree)

   /**********************************
    * Validate Data pointer and size *
    **********************************/
   if ((data == NULLP) || (size == 0))
   {
      RETVALUE(ROK);
   }

   /**********************
    * Release the memory *
    **********************/
   (Void) SPutSBuf(egCb.init.region,
                   egCb.init.pool,
                   data,
                   size);

   RETVALUE(ROK);
}


/*
*
*       Fun:   egAcUtlEdmMakeEvntMsg
*
*       Desc:  This function is frame the event message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcUtlEdmMakeEvntMsg
(
EgEvnt **eventMsg,
EgMsg   *egMsg,
U8  intfType,
Buffer  *mBuf,
U8  eventType
)
#else
PUBLIC S16 egAcUtlEdmMakeEvntMsg(eventMsg, egMsg, intfType, mBuf, eventType)
EgEvnt **eventMsg;
EgMsg   *egMsg;
U8  intfType;
Buffer  *mBuf;
U8  eventType;
#endif
{
   S16  retValue = ROK;

   /* allocate memory for the event message */
   if ( (retValue = SGetSBuf(DFLT_REGION, DFLT_POOL, (Data **)eventMsg, sizeof(EgEvnt))) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlEdmMakeEvntMsg(), unable to alloca mem for evntMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   } /* end of if allocating memory fails */
   else
   {
      (Void)cmMemset((U8 *) *eventMsg, '\0', sizeof(EgEvnt));
   } /* end of if allocating memory succeeds */

   /* Frame the event message before calling the encoding or decoding */
   if(eventType == EVTEDMENCREQ)
   {
      (*eventMsg)->u.egMsg = egMsg;
   }
   else 
   {
      (*eventMsg)->u.mBuf = mBuf;
   } 
   (*eventMsg)->intfType = intfType;
   (*eventMsg)->eventType = eventType;

   if ( (retValue = SGetSBuf(DFLT_REGION, DFLT_POOL,  (Data **) &(*eventMsg)->srvCb, sizeof(EgTptSrvCb))) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlEdmMakeEvntMsg(), unable to alloca mem for evntMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   } /* end of if allocating memory fails */
   else
   {
      (Void)cmMemset((U8 *) (*eventMsg)->srvCb, '\0', sizeof(EgTptSrvCb));
   } /* end of if allocating memory succeeds */
   if ( (retValue = SGetSBuf(DFLT_REGION, DFLT_POOL,  (Data **) &(*eventMsg)->srvCb->uSapCb, sizeof(EgUSapCb))) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlEdmMakeEvntMsg(), unable to alloca mem for evntMsg\n"));
      RETVALUE(CMXTA_ERR_INT);
   } /* end of if allocating memory fails */
   else
   {
      (Void)cmMemset((U8 *) (*eventMsg)->srvCb->uSapCb, '\0', sizeof(EgUSapCb));
   } /* end of if allocating memory succeeds */

   (*eventMsg)->srvCb->uSapCb->pst.region = egCb.init.region;
   (*eventMsg)->srvCb->uSapCb->pst.pool = egCb.init.pool;
   RETVALUE(ROK);

}

/*
 *
 *      Fun:    smActvInit
 *
 *     Desc:    Invoked by system services to initialize the stack manager. 
 *              This is an entry point used by the stack manager to initialize 
 *              its global variables, before becoming operational.
 *
 *              The first and second parameters (entity, instance)
 *              specify the entity and instance id of the stack manager task.
 *
 *              The third parameter (region) specifies the memory region
 *              from which the stack manager should allocate structures and 
 *              buffers.
 *
 *              The fourth parameter (reason) specifies the reason for
 *              calling this initialization function.
 *
 *              Allowable values for parameters are specified in ssi.h.
 *
 *      Ret:    ROK - ok
 *
 *      Notes:  None
 *
        File:   sm_bdy1.c
 *
 */
#ifdef SS_MULTIPLE_PROCS  
#ifdef ANSI
PUBLIC S16 smActvInit
(
ProcId procId,              /* Processr */
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason,              /* reason */
Void   **xxCb               /* xxCb pointer */
)
#else
PUBLIC S16 smActvInit(procId, ent, inst, region, reason, xxCb)
ProcId procId;              /* Processor */
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
Void   **xxCb;              /* xxCb Pointer */
#endif

#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 smActvInit
(
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason               /* reason */
)
#else
PUBLIC S16 smActvInit(ent, inst, region, reason)
Ent      ent;                 /* entity */
Inst     inst;                /* instance */
Region   region;              /* region */
Reason   reason;              /* reason */
#endif /* ANSI */
#endif /* SS_MULTIPLE_PROCS */
{
   TRC3(smActvInit)

   RETVALUE(ROK);
}
/********************************************************************30**

         End of file:     egac_edmutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:26 2015

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
*********************************************************************91*/
