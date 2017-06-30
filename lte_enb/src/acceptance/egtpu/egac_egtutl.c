
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_egtutl.c

     Sid:      egac_egtutl.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:44:27 2014

     Prg:     an 
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */
#include "cm_hash.h"        /* common Hash List  */
/*-- eg004.201: Header files for GTP-C PSF upgrade --*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"
#endif
#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for EG */
#include "leg.h"            /* defines and macros for EG */
#include "egt.h"            /* defines and macros for EG */
#include "eg_err.h"        /* EG error defines */
#include "egac_acc.h"        /* defines for EG acceptance tests */
#if 0
#include "eg_dbutl.h"       /* IE Codes are here */
#include "eg_util.h"            /* typedefs for EG */
#endif
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
#include "cm_xta.h"

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_hash.x"        /* common Hash List  */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "leg.x"           /* layer management typedefs for EG */
#include "egt.x"           /* typedefs for EG */
/*-- eg004.201: Header files for GTP-C PSF upgrade --*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for EG */
#include "eg_tpt.x"            /* EGTP TPT module defines */

#include "eg_util.x"            /* typedefs for EG */
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "cm_xta.x" 
#include "egac_acc.x"      /* typedefs for EG acceptance tests */
#include "egac_egt.x"
#if 0
#include "eg_dbutl.x"       /* defines for the s11 interface sample */
#include "eg_dbs11.x"       /* defines for the s11 interface sample */
#include "eg_dbs5.x"       /* defines for the s5 interface sample */
#endif
/*-- eg004.201: Header files for GTP-C PSF upgrade --*/
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif


PUBLIC EgAccCb egAccCb;

#ifdef EGTP_U

PUBLIC Void eguAcEgtBuildIeHeader ARGS
((
EgUIe   *eguIe,
U8      ieType,
U8      dataType
));

PUBLIC Void  eguMakeAndAddPvtExtIE ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgUMsg         *eguMsg
));

PUBLIC Void eguMakeAndAddRecoveryIe ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
EgUMsg      *eguMsg
));

PUBLIC Void eguMakeAndAddTeidDataIE ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
EgUMsg      *eguMsg
));

PUBLIC Void eguMakeAndAddGtpUPeerAddrIE ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
EgUMsg      *eguMsg
));

PUBLIC Void eguMakeAndAddExtHdrTypeLstIE ARGS
((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
EgUMsg      *eguMsg
));

PUBLIC Void  eguMakeAndAddDelayIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgUMsg         *egMsg
));
#endif /* EGTP_U */

#ifdef EGTP_C 
PRIVATE Void egAcSetFteidFrmTeid ARGS
((
U32     teid,
EgMsg   *egMsg
));

/*
*
*       Fun:   egAcSetFteidFrmTeid
*
*       Desc:  To set the Fteid from the CSESS
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PRIVATE Void egAcSetFteidFrmTeid
(
U32     teid,
EgMsg   *egMsg
)
#else
PRIVATE Void egAcSetFteidFrmTeid(teid, egMsg)
U32   teid;
EgMsg *egMsg;
#endif /* ANSI */
{  

   EgIeInfo     ieInfo;
   EgIe         *egIe=NULLP;
   U16          iePos=0;
   S16          retVal=ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSetFteidFrmTeid)

   cmMemset((U8 *)&ieInfo, 0, sizeof(EgIeInfo));

   ieInfo.ieTypePres = TRUE;
   ieInfo.occrPres = FALSE;
   ieInfo.posPres = FALSE;
   ieInfo.refValue = FALSE;
   ieInfo.ieType   = EG_FTEID_IETYPE;
   ieInfo.ieInst   = 0;
 
   retVal = egUtilGetTrgtIe(&(egMsg->egIeList), &ieInfo, &egIe, &iePos);
   if ( retVal != ROK)
   {
      /* failed then try to get from the instance 1 */
      ieInfo.ieInst   = 1;
      retVal = egUtilGetTrgtIe(&(egMsg->egIeList), &ieInfo, &egIe, &iePos);
      if ( retVal == ROK)
      {
         egIe->t.fTeid.teid = teid;
      }
   }
   else
   {
      egIe->t.fTeid.teid = teid;
   }
   RETVOID;
}

/*
 *
 *       Fun:   egAcUtlEgtBuildMsg
 *
 *       Desc:  Build the EGTP Message
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function used the ABNF decoder to pupulate 
 *              the event structures for text messages
 *
 *       File: egac_egtutl.c 
 *
 */

#ifdef ANSI
PUBLIC S16 egAcUtlEgtBuildMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgBuildMsg        *bldMsg,
EgMsg         **egMsg,
U8             apiType
)
#else
PUBLIC S16 egAcUtlEgtBuildMsg (tcCb, spCb,bldMsg, egMsg, apiType)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgBuildMsg        *bldMsg;
EgMsg         **egMsg;
U8             apiType;
#endif
{
   S16            ret;

   U8             srcEntId =0;
   U8             tptProt;
   U8             eventType;

   U8             egtpMsgType;
#ifdef LEG_FILE_LOG
   U16   nmbLines=0;
#endif /* LEG_FILE_LOG */

#ifdef SS_MULTIPLE_PROCS
   ProcId         srcProcId;
   ProcId         dstProcId;
#endif /* SS_MULTIPLE_PROCS */   
   Bool           useDummy;
   Pst            *pst;
   SpId           *spId;
   U32            teid;
   ProcId         procId = 0;
   /*-- eg006.201: Change type for crtFlag to U16 --*/
   U16            crtFlag=0;

   U32            transId = 0;
   U16            tmrVal = 0;
   Bool           t3Enb;
	Bool           seqNoPres  =  FALSE;
	U32            seqNo = 1; /* sequence number */
#ifdef HW
   Bool SpecHand  = TRUE;
#endif

   
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcUtlEgtBuildMsg)

   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlEgtBuildMsg()\n"));

   *egMsg = NULLP;
   pst = &bldMsg->pst;
   spId = &bldMsg->spId;

   CMXTA_ZERO(pst, sizeof(Pst));
   
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"procId",&dstProcId);
   cmXtaGetPst(pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   /*-- Get Transport: For EGTP UDP is default Protocol --*/
   tptProt = LEG_TPTPROT_UDP;

   eventType = EGT_STATYPE_TUNNEL; /*-- Default is Tunnel Type --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"eventType",  &(eventType));

   bldMsg->eventType = eventType;

   egtpMsgType = EGT_GTPC_MSG_CS_REQ;
   /*-- Get EGTP message type --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"egtpMsgType",  &(egtpMsgType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"transId",&(transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"procId",&(procId));

   teid = egAccCb.egAcMsgInfo[procId][transId].teid;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"teid",&(teid));

   /* Get Local Address */
   if ((ret = egAcEgtGetAddress(tcCb, spCb, bldMsg, EGAC_ADDRTYPE_LCL)) 
         != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /* Get Remote Address */
   if ((ret = egAcEgtGetAddress(tcCb, spCb, bldMsg, EGAC_ADDRTYPE_RMT)) 
         != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- eg006.201: CrtFlag modified to accept new type  --*/
     /* Set the Tunnel creation flag */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16,(Txt  *)"crtFlag",&(crtFlag));
   
   /* Set the T3 Timer Value  */
   bldMsg->T3.enb = FALSE;
   bldMsg->T3.val = 0;
   tmrVal = 10;
   t3Enb = TRUE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"t3Enb",&(t3Enb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"t3TmrVal",&(tmrVal));
   
   bldMsg->crtFlag.pres = PRSNT_NODEF;
   bldMsg->crtFlag.val = crtFlag;
   
   if (t3Enb == TRUE)
   {
      bldMsg->T3.enb = TRUE;
      bldMsg->T3.val = tmrVal;
   }

   bldMsg->lclTeid.pres = PRSNT_NODEF;
   bldMsg->lclTeid.val = teid;



   /* Set useDumy as FALSE */
   useDummy = FALSE;

   /*-- Get transport type (real/dummy --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"dummy",  &(useDummy));

   /*-- Get spId & Update from test case --*/
   *spId = egAcEgtGetSpId(tptProt, srcEntId, useDummy);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  spId);

	/* get the sequence number from the test case */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"seqNoPres",  &seqNoPres);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"seqNo",  &seqNo);

   if ((apiType != EVTEGTLCLDELREQ) && (apiType != EVTEGTSTAREQ) )
   {
   /*-- Generate IEs Structure --*/
      if ((ret = egAcEgtBuildIEs(tcCb, spCb,
                             bldMsg,
                             egMsg, apiType, eventType,
                             egtpMsgType)) != CMXTA_ERR_NONE)
        RETVALUE(ret);

	if(seqNoPres == TRUE)
	{
	  (*egMsg)->msgHdr.seqNumber = seqNo; 
	}
   /*-- eg004.201: Flag for Handling TEID on PSF activation  --*/ 
#ifdef HW 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"SpecHand",  &SpecHand);
   if(SpecHand)
   {
	if(teid != 0)
	{
	  (*egMsg)->msgHdr.teid = teid; 
	  (*egMsg)->msgHdr.teidPres = TRUE; 
	}
   }
#endif
   if ( (*egMsg)->msgHdr.msgType == EGT_GTPC_MSG_CS_RSP)
   {
      egAcSetFteidFrmTeid(teid, (*egMsg));
#ifdef EGAC_LOOP_TEST
      egAcSetFteidFrmTeid(egAccCb.egAcCrtInfo.teid, (*egMsg));
      (*egMsg)->msgHdr.seqNumber = egAccCb.egAcCrtInfo.seqNo;
      (*egMsg)->msgHdr.teid = egAccCb.egAcCrtInfo.rmTeid;
#endif /* EG_LOOP_TEST */
   }
#ifdef EGAC_LOOP_TEST
   else if ( (*egMsg)->msgHdr.msgType == EGT_GTPC_MSG_CS_REQ)
   {
      (*egMsg)->msgHdr.teid = 0;

   }
#endif /* EG_LOOP_TEST */
#ifdef LEG_FILE_LOG
         EgUtilGmDump(*egMsg, stdout, &nmbLines);
#else
         EgUtilGmDump(*egMsg);
#endif /* end of LEG_FILE_LOG */
   }
   cmMemset((U8*)&bldMsg->pathInfo,0,sizeof(EgPathInfo));
   if (apiType == EVTEGTSTAREQ)
   {

      if (bldMsg->eventType == EGT_STATYPE_PATH)
      {
         bldMsg->pathInfo.staType = EGT_STATYPE_PATH; 
         cmMemcpy((U8 *)&bldMsg->pathInfo.u.localAddr,(U8 *)&bldMsg->localAddr, 
                  sizeof(CmTptAddr));
      }
      else if (bldMsg->eventType == EGT_STATYPE_TUNNEL)
      {
         bldMsg->pathInfo.staType = EGT_STATYPE_TUNNEL; 
         bldMsg->pathInfo.u.teid = teid;
      }
      else
      {
         ret = CMXTA_ERR_NOMATCH;
        RETVALUE(ret);

      }

   }


   RETVALUE(CMXTA_ERR_NONE);
} /*-- egAcUtlEgtBuildMsg --*/


/*
 *
 *       Fun:    egAcEgtBuildIEs
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 egAcEgtBuildIEs
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */ 
EgBuildMsg        *bldMsg,
EgMsg         **egMsg,
U8             apiType,
U8        eventType,
U8        egtpMsgType
)
#else
PUBLIC S16 egAcEgtBuildIEs(tcCb, spCb, bldMsg,egMsg, apiType, 
                           eventType, egtpMsgType )
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;     /* spCb data structure  */ 
EgBuildMsg        *bldMsg;
EgMsg         **egMsg;
U8             apiType;
U8        eventType;
U8        egtpMsgType;
#endif /* ANSI */
{
   S16     ret;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEgtBuildIEs)

   CMXTA_DBG_PARAM((_cmxtap, "egAcEgtBuildIEs(): \n"));


   /* Build the IEs : Calling the EDM stub function directly here       * 
    * Enhancement: We can rename this function to common name later on  *
    */
   /* TODO: Check if this function is filling the header also correctly*/
   ret = egAcEdmBuildEgMsg(tcCb,spCb,egtpMsgType,egMsg);
   if ( ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }


   RETVALUE(CMXTA_ERR_NONE);
} /* end of egAcEgtBuildIEs() */

#endif /* EGTP_C */
/*
 *
 *       Fun:    egAcEgtGetSpId -
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   egac_egtutl.c
 *
 */
#ifdef ANSI
PUBLIC SpId egAcEgtGetSpId
(
U8    tptProt,
U8   entityId,
Bool  useDummy
)
#else
PUBLIC SpId egAcEgtGetSpId(tptProt, entityId, useDummy)
U8    tptProt;
U8   entityId;
Bool  useDummy;
#endif /* ANSI */
{
   SpId spId;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEgtGetSpId)

   CMXTA_DBG_PARAM((_cmxtap, "egAcEgtGetSpId(): \n"));

   /* Logic:- Each Entity is having two SSAP, one for Real 
    * Transports and one for Dummy. Ent1 = SSAP0 and SSAP1
    * Ent2 = SSAP2 and SSAP3 and so  on*/

   /*-- Default value --*/
   spId = 0;

   /*-- You may not always be able to decide based on
        transport, remove the code for transport and instead
        ask the user itself from the test case, TA will
        ensure that correct transport is used, but deciding
        on own is not possible, especially when you have
        multiple real entities and one or more dummy entities
        --*/
   if (useDummy == TRUE)
      spId = entityId * 2 + 1;
   else
   {
      switch (tptProt)
      {
         /*-- Real tranport layers --*/
         case LEG_TPTPROT_UDP:
            spId = entityId * 2;
            break;
         default:
            /*-- Dummy TUCL/SCTP being used --*/
            spId = entityId * 2 + 1;
            break;
      }
   }

   RETVALUE(spId);
} /* end of egAcEgtGetSpId() */


/*
 *
 *       Fun:    egAcEgtGetTransport - 
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC U8 egAcEgtGetTransport
(
CmXtaTCCb    *tcCb    /* tcCb data structure  */
)
#else
PUBLIC U8 egAcEgtGetTransport(tcCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
#endif /* ANSI */
{
   EgAcTCCb *egTcCb;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEgtGetTransport)

   CMXTA_DBG_PARAM((_cmxtap, "egAcEgtGetTransport(): \n"));

   egTcCb = (EgAcTCCb *)tcCb->tcCb;

   RETVALUE(egTcCb->directives.tptType);
} /* end of egAcEgtGetTransport() */


/*
 *
 *       Fun:    egAcEgtGetAddress - 
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 egAcEgtGetAddress
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgBuildMsg   *bldMsg,
U8           addrType
)
#else
PUBLIC S16 egAcEgtGetAddress(tcCb, spCb, bldMsg, addrType)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgBuildMsg   *bldMsg;
U8           addrType;
#endif /* ANSI */
{

   U32         tmpAddr;
   char        tmpAddrArr[30];
   U16         port;
   U8          type = 0;                     /* type of transport address */


   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEgtGetAddress)

   CMXTA_DBG_PARAM((_cmxtap, "egAcEgtGetAddress(): \n"));

   switch(addrType)
   {
      case EGAC_ADDRTYPE_LCL:
         {
           cmMemset((U8*)&(bldMsg->localAddr), EGAC_ZERO, sizeof(CmTptAddr));

            bldMsg->localAddr.type = CM_NETADDR_IPV4;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"lclAddrType", 
                  &(type));

            if (type != 0)
            {
               bldMsg->localAddr.type = type;
            }

            port = 8012;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , (Txt  *)"lclPort",  
                  &(port));
            /*-- eg006.201: Corrected updation for port to bldMsg --*/ 
            bldMsg->localAddr.u.ipv4TptAddr.port = port;


            cmMemset ((U8 *)tmpAddrArr,      0, 30);
            strcpy((char *)tmpAddrArr, (char *)"127.0.0.1");

            cmInetAddr(tmpAddrArr, &tmpAddr);
            bldMsg->localAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"lcladdr", (tmpAddrArr) );

            if(strcmp(tmpAddrArr,"\0") == 0)
            {
               /* User has not provided IP, use default one */
            }
            else
            {
               if(bldMsg->localAddr.type == CM_NETADDR_IPV4)
               {
                  bldMsg->localAddr.u.ipv4TptAddr.port = port;
                  cmInetAddr(tmpAddrArr, &tmpAddr);
                  bldMsg->localAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);
               }
#ifdef IPV6_SUPPORTED               
               else
               {
                  bldMsg->localAddr.u.ipv6TptAddr.port = port;
                  cmInetPton6(&bldMsg->localAddr.u.ipv6TptAddr.ipv6NetAddr, tmpAddrArr);
                  /* strcpy((char *)bldMsg->localAddr.u.ipv6TptAddr.ipv6NetAddr, tmpAddrArr);*/
               }
#endif               
            }
         }
         break;
      case EGAC_ADDRTYPE_RMT:
         {
           cmMemset((U8*)&(bldMsg->remAddr), EGAC_ZERO, sizeof(CmTptAddr));
            bldMsg->remAddr.type = CM_NETADDR_IPV4;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"rmtAddrType", 
                  &(bldMsg->remAddr.type) );

            port = 9012;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , (Txt  *)"rmtPort",  
                  &(port));
            /*-- eg006.201: Corrected updation for port to bldMsg --*/
            bldMsg->remAddr.u.ipv4TptAddr.port = port;


            cmMemset ((U8 *)tmpAddrArr,      0, 30);
            strcpy((char *)tmpAddrArr, (char *)"127.0.0.10");

            cmInetAddr(tmpAddrArr, &tmpAddr);
            bldMsg->remAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"rmtaddr", (tmpAddrArr) );

            if(strcmp(tmpAddrArr,"\0") == 0)
            {
               /* User has not provided IP, use default one */
            }
            else
            {
               if(bldMsg->remAddr.type == CM_NETADDR_IPV4)
               {
                  bldMsg->remAddr.u.ipv4TptAddr.port = port;
                  cmInetAddr(tmpAddrArr, &tmpAddr);
                  bldMsg->remAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);
               }
#ifdef IPV6_SUPPORTED               
               else
               {
                  bldMsg->remAddr.u.ipv6TptAddr.port = port;
                  cmInetPton6(&bldMsg->remAddr.u.ipv6TptAddr.ipv6NetAddr, tmpAddrArr);
                  /*strcpy((char *)bldMsg->remAddr.u.ipv6TptAddr.ipv6NetAddr, tmpAddrArr);*/
               }
#endif                
            }
         }
         break;

      case EGAC_ADDRTYPE_FRMRMT:
         {
            cmMemset((U8*)&(bldMsg->remAddr), EGAC_ZERO, sizeof(CmTptAddr));
            bldMsg->remAddr.type = CM_NETADDR_IPV4;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"frmrmtAddrType",
                  &(bldMsg->remAddr.type) );

            port = 9012;
            bldMsg->remAddr.u.ipv4TptAddr.port = port;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , (Txt  *)"frmrmtPort",
                  &(port));


            cmMemset ((U8 *)tmpAddrArr,      0, 30);
            strcpy((char *)tmpAddrArr, (char *)"127.0.0.10");

            cmInetAddr(tmpAddrArr, &tmpAddr);
            bldMsg->remAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"frmrmtaddr", (tmpAddrArr) );

            if(strcmp(tmpAddrArr,"\0") == 0)
            {
               /* User has not provided IP, use default one */
            }
            else
            {
               if(bldMsg->remAddr.type == CM_NETADDR_IPV4)
               {
                  bldMsg->remAddr.u.ipv4TptAddr.port = port;
                  cmInetAddr(tmpAddrArr, &tmpAddr);
                  bldMsg->remAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);
               }
#ifdef IPV6_SUPPORTED
               else
               {
                  bldMsg->remAddr.u.ipv6TptAddr.port = port;
                  cmInetPton6(&bldMsg->remAddr.u.ipv6TptAddr.ipv6NetAddr, tmpAddrArr);
                  /*strcpy((char *)bldMsg->remAddr.u.ipv6TptAddr.ipv6NetAddr, tmpAddrArr);*/
               }
#endif
            }
         }
         break;

      default:
         {
            CMXTA_DBG_ERR((_cmxtap, "egAcEgtGetAddress(): Invalid Address Type\n"));
            RETVALUE(CMXTA_ERR_NOMATCH);
         }
         break;
   }/* switch(addrType)*/

   RETVALUE(CMXTA_ERR_NONE);
} /* egAcEgtGetAddress() */

#ifdef EGTP_U

/*
 *
 *       Fun:    egAcEguGetAddress -
 *
 *       Desc:
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 egAcEguGetAddress
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CmTptAddr   *address,
U8          addrType
)
#else
PUBLIC S16 egAcEguGetAddress(tcCb, spCb, address, addrType)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CmTptAddr   *address;
U8          addrType;
#endif /* ANSI */
{
  U32         tmpAddr;
  char        tmpAddrArr[30];
  U16         lclPort = EGUAC_DFLT_LCL_PORT;
  U16         rmtPort = EGUAC_DFLT_RMT_PORT;

   /*-- eg003.201 : TRC changes from eg006.102--*/
  EG_TRC2(egAcEguGetAddress)

  cmMemset ((U8 *)tmpAddrArr,0, 30);
/*  cmMemset ((U8 *)address, 0, sizeof(CmTptAddr)); */
  strcpy((Txt *)tmpAddrArr, (Txt *)"127.0.0.1");

  address->type = CM_NETADDR_IPV4;

  switch(addrType)
  {
    case EGAC_ADDRTYPE_LCL:
       {
           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"lclAddrType",
                           &(address->type));

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"lclAddr", (tmpAddrArr) );

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"lclPort", &lclPort);

      if(address->type == CM_NETADDR_IPV4)
      {
         address->u.ipv4TptAddr.port = lclPort;
      }
      else
      {
         address->u.ipv6TptAddr.port = lclPort;
      }

           break;
       }
    case EGAC_ADDRTYPE_RMT:
       {
           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"rmtAddrType",
                           &(address->type));

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"rmtAddr", (tmpAddrArr) );

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"rmtPort", &rmtPort);

      if(address->type == CM_NETADDR_IPV4)
      {
         address->u.ipv4TptAddr.port = rmtPort;
      }
      else
      {
         address->u.ipv6TptAddr.port = rmtPort;
      }
           break;
       }
    case EGAC_ADDRTYPE_FRMRMT:  
       {
           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"frmRmtAddrType",
                           &(address->type));

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"frmRmtAddr", (tmpAddrArr) );

           break;
       }
    default:
       {
          CMXTA_DBG_ERR((_cmxtap, "egAcEgtGetAddress(): Invalid Address Type\n"));
          RETVALUE(CMXTA_ERR_NOMATCH);
       }
  }
  if(address->type == CM_NETADDR_IPV4)
  {
     cmInetAddr(tmpAddrArr, &tmpAddr);
     address->u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);
  }
#ifdef IPV6_SUPPORTED
  else
  {
     cmInetPton6(&(address->u.ipv6TptAddr.ipv6NetAddr), tmpAddrArr);
  }
#endif

  RETVALUE(CMXTA_ERR_NONE);

} /* egAcEguGetAddress */

#endif /* EGTP_U */

#ifdef EGTP_C

/*
 *
 *       Fun:    egAcEgGetAddress -
 *
 *       Desc:
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 egAcEgGetAddress
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CmTptAddr   *address,
U8          addrType
)
#else
PUBLIC S16 egAcEgGetAddress(tcCb, spCb, address, addrType)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CmTptAddr   *address;
U8          addrType;
#endif /* ANSI */
{
  U32         tmpAddr;
  char        tmpAddrArr[30];
  U16         lclPort = EGAC_DFLT_PORT;
  U16         rmtPort = EGAC_DFLT_PORT;

   /*-- eg003.201 : TRC changes from eg006.102--*/
  EG_TRC2(egAcEgGetAddress)

  cmMemset ((U8 *)tmpAddrArr,0, 30);
/*  cmMemset ((U8 *)address, 0, sizeof(CmTptAddr)); */
  strcpy((Txt *)tmpAddrArr, (Txt *)"127.0.0.1");

  address->type = CM_NETADDR_IPV4;

  switch(addrType)
  {
    case EGAC_ADDRTYPE_LCL:
       {
           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"lclAddrType",
                           &(address->type));

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"lclAddr", (tmpAddrArr) );

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"lclPort", &lclPort);

      if(address->type == CM_NETADDR_IPV4)
      {
         address->u.ipv4TptAddr.port = lclPort;
      }
      else
      {
         address->u.ipv6TptAddr.port = lclPort;
      }

           break;
       }
    case EGAC_ADDRTYPE_RMT:
       {
           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"rmtAddrType",
                           &(address->type));

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"rmtAddr", (tmpAddrArr) );

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"rmtPort", &rmtPort);

      if(address->type == CM_NETADDR_IPV4)
      {
         address->u.ipv4TptAddr.port = rmtPort;
      }
      else
      {
         address->u.ipv6TptAddr.port = rmtPort;
      }
           break;
       }
    case EGAC_ADDRTYPE_FRMRMT:  
       {
           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"frmRmtAddrType",
                           &(address->type));

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, (Txt  *)"frmRmtAddr", (tmpAddrArr) );

           break;
       }
    default:
       {
          CMXTA_DBG_ERR((_cmxtap, "egAcEgtGetAddress(): Invalid Address Type\n"));
          RETVALUE(CMXTA_ERR_NOMATCH);
       }
  }
  cmInetAddr(tmpAddrArr, &tmpAddr);
  if(address->type == CM_NETADDR_IPV4)
  {
     address->u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpAddr);
  }
#ifdef IPV6_SUPPORTED
  else
  {
     cmInetPton6(&(address->u.ipv6TptAddr.ipv6NetAddr), tmpAddrArr);
  }
#endif

  RETVALUE(CMXTA_ERR_NONE);

} /* egAcEgGetAddress */

/*
*
*       Fun:   egAcGetFteidFrmMsg
*
*       Desc:  To get the Fteid from the CSESS
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  egac_egthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcGetFteidFrmMsg
(
EgMsg   *egMsg
)
#else
PUBLIC S16 egAcGetFteidFrmMsg(egMsg)
EgMsg *egMsg;
#endif /* ANSI */
{  

   EgIeInfo     ieInfo;
   EgIe         *egIe=NULLP;
   U16          iePos=0;
   S16          retVal=ROK;

   EG_TRC2(egAcGetFteidFrmMsg)
   /*-- eg003.201 : TRC changes from eg006.102--*/
   
   cmMemset((U8 *)&ieInfo, 0, sizeof(EgIeInfo));
   ieInfo.ieTypePres = TRUE;
   ieInfo.occrPres = FALSE;
   ieInfo.posPres = FALSE;
   ieInfo.refValue = FALSE;
   ieInfo.ieType   = EG_FTEID_IETYPE;
   ieInfo.ieInst   = 0;
   
   
   retVal = egUtilGetTrgtIe(&(egMsg->egIeList), &ieInfo, &egIe, &iePos);
   if ( retVal != ROK)
   {
      /* failed then try to get from the instance 1 */
      ieInfo.ieInst   = 1;
      retVal = egUtilGetTrgtIe(&(egMsg->egIeList), &ieInfo, &egIe, &iePos);
      if ( retVal != ROK)
      {
         RETVALUE(0);
      }
      else
      {
         RETVALUE(egIe->t.fTeid.teid);
      }
   }
   else
   {

      RETVALUE(egIe->t.fTeid.teid);
   }

}
#endif /* EGTP_C */

#ifdef EGTP_U

/*
 *
 *       Fun:   eguAcUtlEgtBuildDatReq
 *
 *       Desc:  Build the EGTP-U Data Request Message
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function used the ABNF decoder to pupulate
 *              the event structures for text messages
 *
 *       File: egac_egtutl.c
 *
 */

#ifdef ANSI
PUBLIC S16 eguAcUtlEgtBuildDatReq
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgBuildMsg        *bldMsg,
EgtUEvnt          **eguEvtMsg
)
#else
PUBLIC S16 eguAcUtlEgtBuildDatReq(tcCb, spCb, bldMsg, eguEvtMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgBuildMsg        *bldMsg;
EgtUEvnt          **eguEvtMsg;
#endif
{
   S16            ret;
#ifdef LEG_FILE_LOG
   U16            nmbLines=0;
#endif /* LEG_FILE_LOG */
#ifdef SS_MULTIPLE_PROCS
   ProcId         srcProcId;
   ProcId         dstProcId;
#endif /* SS_MULTIPLE_PROCS */
   Pst            *pst;
   SpId           spId = 0;
   Mem            memInfo;
                              
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcUtlEgtBuildDatReq)

   CMXTA_DBG_PARAM((_cmxtap, "eguAcUtlEgtBuildDatReq()\n"));

   *eguEvtMsg = NULLP;
   pst = &(bldMsg->pst);

   CMXTA_ZERO(pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"procId",&dstProcId);
   cmXtaGetPst(pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   memInfo.pool   = DFLT_REGION;
   memInfo.region = DFLT_POOL;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"spId",&(spId));
   bldMsg->spId = spId;

   /*****************************************************************
    * allocate memory for the e-gtpu event message of size EgtUEvnt *
    *****************************************************************/
   if ((ret = SGetSBuf(memInfo.region, memInfo.pool, (Data **)eguEvtMsg, sizeof(EgtUEvnt))) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"eguAcUtlEgtBuildDatReq() : Unable to allocate memory for EGTP-U message\n"));
      RETVALUE(ret);
   }

   cmMemset((U8*)*eguEvtMsg, 0, sizeof(EgtUEvnt));
   /**************************************************************
    * allocate memory for the e-gtpu Data message of size EgUMsg *
    **************************************************************/
   if((ret = EgUUtilAllocGmMsg(&((*eguEvtMsg)->u.egMsg), &memInfo)) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"eguAcUtlEgtBuildDatReq() : Unable to allocate memory for EGTP message\n"));
      RETVALUE(ret);
   }
   /* Get Local Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &((*eguEvtMsg)->u.egMsg->srcAddr), EGAC_ADDRTYPE_LCL))
                                                             != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /* Get Remote Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &((*eguEvtMsg)->u.egMsg->remAddr), EGAC_ADDRTYPE_RMT))
                                                             != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if(egUAcUtlDEdmBuildMsg(tcCb,spCb,&((*eguEvtMsg)->u.egMsg)) != ROK)
   {
       CMXTA_DBG_ERR((_cmxtap,"egAcHdlHitUDatInd() Unable to build the message for GTP-U \n"));
       EgUUtilDeAllocGmMsg(&(*eguEvtMsg)->u.egMsg);
       RETVALUE(CMXTA_ERR_INT);
   } 

   RETVALUE(ret);

} /* eguAcUtlEgtBuildDatReq */

/*
 *
 *       Fun:   eguAcUtlEgtBuildTnlMgmtReq
 *
 *       Desc:  Build the EGTP-U Tunnel Mgmt Request Message
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function used the ABNF decoder to pupulate
 *              the event structures for text messages
 *
 *       File: egac_egtutl.c
 *
 */

#ifdef ANSI
PUBLIC S16 eguAcUtlEgtBuildTnlMgmtReq
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgBuildMsg        *bldMsg,
EgtUEvnt          **eguEvtMsg
)
#else
PUBLIC S16 eguAcUtlEgtBuildTnlMgmtReq(tcCb, spCb, bldMsg, eguEvtMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgBuildMsg        *bldMsg;
EgtUEvnt          **eguEvtMsg;
#endif
{
   S16            ret = CMXTA_ERR_NONE;
#ifdef LEG_FILE_LOG
   U16            nmbLines=0;
#endif /* LEG_FILE_LOG */
#ifdef SS_MULTIPLE_PROCS
   ProcId         srcProcId;
   ProcId         dstProcId;
#endif /* SS_MULTIPLE_PROCS */
   Pst            *pst;
   SpId            spId;
   Mem            memInfo;
   U8             action;                        /**< Action to be taken on tunnel */
   Bool           reOrderPres;                   /**< Reordering present in that tunnel */
   U32            teId;                          /**< Tunnel Id */
   U32            remTeId;                       /**<remote teid */ 
   U8             intfType;                      /**< Interface type */
   U16            expSeqNmb;                     /**< Expected sequence number */
   U16            maxTPduSize;                   /**< MAX T-PDU size */
   U8            reordAlgo;                   /**< Re-ordering Algorithm */
   U8             dscp;
   /*--eg012.201: declaration of tunnel type variable guarded under EGTP_U_REL_9 flag */
#ifdef EGTP_U_REL_9
   U8             tunnelType;
#endif /* EGTP_U_REL_9 */
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcUtlEgtBuildTnlMgmtReq)

   CMXTA_DBG_PARAM((_cmxtap, "eguAcUtlEgtBuildTnlMgmtReq()\n"));

   /**eguEvtMsg = NULLP;*/
   pst = &bldMsg->pst;

   CMXTA_ZERO(pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"procId",&dstProcId);
   cmXtaGetPst(pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   memInfo.pool   = DFLT_REGION;
   memInfo.region = DFLT_POOL;

   /*****************************************************************
    * allocate memory for the e-gtpu event message of size EgtUEvnt *
    *****************************************************************/
   if ((ret = SGetSBuf(memInfo.region, memInfo.pool, (Data **)eguEvtMsg, sizeof(EgtUEvnt))) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"eguAcUtlEgtBuildTnlMgmtReq() : Unable to allocate memory for EGTP-U message\n"));
      RETVALUE(ret);
   }

   cmMemset((U8*)*eguEvtMsg, 0, sizeof(EgtUEvnt));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"spId",&(spId));
   bldMsg->spId = spId;

   action      = EGUAC_DFLT_ACTION;
   reOrderPres = EGUAC_DFLT_REORDER;
/* eg001.201  Assign default value to tunnelType*/
#ifdef EGTP_U_REL_9
   tunnelType  = EG_NORMAL_DATA_TUNN; 
#endif
   teId        = EGUAC_DFLT_TEID;
   intfType    = EGUAC_DFLT_INTFTYPE;
   expSeqNmb   = EGUAC_DFLT_EXPSEQNMB;
   maxTPduSize = EGUAC_DFLT_MAXTPDUSZ;
   reordAlgo = EGUAC_DFLT_REORDALGO;
   dscp      = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt  *)"action",&(action));
   (*eguEvtMsg)->u.tnlMgmt.action = action;

   if(action == EGT_TMGMT_REQTYPE_ADD)
   {

     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, 
           (Txt  *)"intfType",  &(intfType));
      (*eguEvtMsg)->u.tnlMgmt.intfType = intfType;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"reOrderPres",&(reOrderPres));
      (*eguEvtMsg)->u.tnlMgmt.reOrderPres = reOrderPres;

/* eg001.201  Get value for tunnelType from XTA*/
#ifdef EGTP_U_REL_9
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt  *)"tunnelType",&(tunnelType));
      (*eguEvtMsg)->u.tnlMgmt.tunnelType = tunnelType;
#endif
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"expSeqNmb",&(expSeqNmb));
      (*eguEvtMsg)->u.tnlMgmt.expSeqNmb = expSeqNmb;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"maxTPduSize",&(maxTPduSize));
      (*eguEvtMsg)->u.tnlMgmt.maxTPduSize = maxTPduSize;
   }

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"teid",&(teId));
      (*eguEvtMsg)->u.tnlMgmt.teId = teId;

      /*added rmteid */
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"remTeid",&(remTeId));
      (*eguEvtMsg)->u.tnlMgmt.remTeId = remTeId;
      
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"selector",  &(pst->selector));

     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, 
           (Txt  *)"reordAlgo",  &(reordAlgo));
      (*eguEvtMsg)->u.tnlMgmt.reordAlgo = reordAlgo;

     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, 
           (Txt  *)"dscp",  &(dscp));
      (*eguEvtMsg)->u.tnlMgmt.dscp = dscp;
      /* Get Local Address */
      if((ret = egAcEguGetAddress(tcCb, spCb, &((*eguEvtMsg)->u.tnlMgmt.srcAddr), EGAC_ADDRTYPE_LCL))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

      /* Get Remote Address */
      if((ret = egAcEguGetAddress(tcCb, spCb, &((*eguEvtMsg)->u.tnlMgmt.dstIpAddr), EGAC_ADDRTYPE_RMT))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

      /* Get From Remote Address */
      if((ret = egAcEguGetAddress(tcCb, spCb, &((*eguEvtMsg)->u.tnlMgmt.frmDstIpAddr), EGAC_ADDRTYPE_FRMRMT))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);

} /* eguAcUtlEgtBuildTnlMgmtReq */

/*
 *
 *       Fun:   eguAcUtlEgtBuildStaReq
 *
 *       Desc:  Build the EGTP-U Tunnel Mgmt Request Message
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function used the ABNF decoder to pupulate
 *              the event structures for text messages
 *
 *       File: egac_egtutl.c
 *
 */

#ifdef ANSI
PUBLIC S16 eguAcUtlEgtBuildStaReq
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgBuildMsg        *bldMsg,
EgtUEvnt          **eguEvtMsg
)
#else
PUBLIC S16 eguAcUtlEgtBuildStaReq(tcCb, spCb, bldMsg, eguEvtMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgBuildMsg        *bldMsg;
EgtUEvnt          **eguEvtMsg;
#endif
{
   S16            ret = CMXTA_ERR_NONE;
   SpId           spId = 0;
#ifdef LEG_FILE_LOG
   U16            nmbLines=0;
#endif /* LEG_FILE_LOG */
#ifdef SS_MULTIPLE_PROCS
   ProcId         srcProcId;
   ProcId         dstProcId;
#endif /* SS_MULTIPLE_PROCS */
   Pst            *pst;
   Mem            memInfo;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcUtlEgtBuildStaReq)

   CMXTA_DBG_PARAM((_cmxtap, "eguAcUtlEgtBuildStaReq()\n"));

   *eguEvtMsg = NULLP;
   pst = &bldMsg->pst;

   CMXTA_ZERO(pst, sizeof(Pst));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   egAccCb.directives.xtaProcId;
   dstProcId   =   CMXTA_DFLT_PROCID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"procId",&dstProcId);
   cmXtaGetPst(pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(pst, ENTEU, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   memInfo.pool   = DFLT_REGION;
   memInfo.region = DFLT_POOL;

   /*****************************************************************
    * allocate memory for the e-gtpu event message of size EgtUEvnt *
    *****************************************************************/
   if ((ret = SGetSBuf(memInfo.region, memInfo.pool, (Data **)eguEvtMsg, sizeof(EgtUEvnt))) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,"eguAcUtlEgtBuildStaReq() : Unable to allocate memory for EGTP-U message\n"));
      RETVALUE(ret);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"spId",&(spId));
   bldMsg->spId = spId;

   /* Get Local Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &((*eguEvtMsg)->u.status.srcAddr), EGAC_ADDRTYPE_LCL))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);

   /* Get Remote Address */
   if((ret = egAcEguGetAddress(tcCb, spCb, &((*eguEvtMsg)->u.status.dstAddr), EGAC_ADDRTYPE_RMT))
                                                             != CMXTA_ERR_NONE)
          RETVALUE(ret);


   RETVALUE(ret);

} /* eguAcUtlEgtBuildStaReq */

/*
*
*       Fun:   eguAcEgtBuildIeHeader
*
*       Desc:  This function is used to Build eGTP-U Echo Msg's IE Header
*
*       Ret:   None
*
*       Notes: None
*
*       File: egac_egtutl.c
*
*/

#ifdef ANSI
PUBLIC Void eguAcEgtBuildIeHeader
(
EgUIe   *eguIe,
U8      ieType,
U8      dataType
)
#else
PUBLIC Void eguAcEgtBuildIeHeader(eguIe, ieType, dataType)
EgUIe   *eguIe;
U8      ieType;
U8      dataType;
#endif /* ANSI */
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcEgtBuildIeHeader)

   eguIe->ieType = ieType;
   eguIe->dataType = dataType;

   RETVOID;
} /* eguAcEgtBuildIeHeader */

/*
*
*       Fun:   egumakeAndAddDelayIe
*
*       Desc:  This function is used to Build Delay Ie 
*
*       Ret:   None
*
*       Notes: None
*
*       File: egac_egtutl.c
*
*/

#ifdef ANSI
PUBLIC Void  eguMakeAndAddDelayIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgUMsg      *egMsg
)
#else
PUBLIC Void eguMakeAndAddDelayIe(tcCb,spCb,egMsg)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgUMsg      *egMsg;
#endif /* ANSI */
{
   U8     delayVal =  DFLT_DELAY;
   U8     delayPresent = TRUE;
   EgUIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguMakeAndAddDelayIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgUIe));

   eguAcEgtBuildIeHeader(&egIe,EGAC_DELAY_IETYPE,EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, 
                  (Txt *)"delayVal", &delayVal);
   egIe.t.valUnSgnd8 = delayVal;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, 
                  (Txt *)"delayIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"delayPresent",  &delayPresent);

   if( delayPresent == TRUE)
   {
       if(EgUUtilGmAppendIe(egMsg, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,
        "eguMakeAndAddDelayDelayIe() : Unable to Append IE to eGTPU message\n"));
            RETVOID;
       }
  }
}  /* eguMakeAndAddDelayIe  */
/*
*
*       Fun:   eguMakeAndAddPvtExtIE
*
*       Desc:  This function is used to Build eGTP-U Echo Msg's PvtExt IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: egac_egtutl.c
*
*/

#ifdef ANSI
PUBLIC Void  eguMakeAndAddPvtExtIE
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgUMsg         *eguMsg
)
#else
PUBLIC Void eguMakeAndAddPvtExtIE(tcCb,spCb,eguMsg)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgUMsg         *eguMsg;
#endif /* ANSI */
{
   Data   pvtExtnPropVal[200] = DFLT_PVTEXT_PRY_VAL;
   U16    pvtExtnEntId = DFLT_PVTEXT_ENT_ID;
   Bool   pvtExtnPresent = TRUE;
   EgUIe  eguIe;
   /* ccpu00136421:purecov fix */
   Bool  invalidIeType=FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguMakeAndAddPvtExtIE)

   /* Fill the ie properties */
   cmMemset((U8 *)&eguIe, 0 , sizeof(EgUIe));

   eguAcEgtBuildIeHeader(&eguIe, EGU_PVT_EXTN_IETYPE, EG_PVT_EXTN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16,
                  (Txt *)"pvtExtnEntId",  &pvtExtnEntId);

   eguIe.t.pvtExt.entId = pvtExtnEntId;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"pvtExtnPropVal", pvtExtnPropVal);

   eguIe.t.pvtExt.propVal.length = cmStrlen((U8 *)pvtExtnPropVal);

   cmMemcpy((U8 *) eguIe.t.pvtExt.propVal.val, (U8 *)pvtExtnPropVal, eguIe.t.pvtExt.propVal.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pvtExtnIeType", &eguIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"pvtExtnPresent",  &pvtExtnPresent);
   /* ccpu00136421:purecov fix */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"invalidIeType",  &invalidIeType);
   if(invalidIeType==TRUE)
   {
      eguIe.ieType=0;
   }   
   if( pvtExtnPresent == TRUE)
   {
       if(EgUUtilGmAppendIe(eguMsg, &eguIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,
             "eguMakeAndAddPvtExtIE() : Unable to Append IE to eGTP-U message\n"));
       }
   }
  
   RETVOID;
} /* eguMakeAndAddPvtExtIE */

/*
*
*       Fun:   eguMakeAndAddRecoveryIe
*
*       Desc:  This function is used to Build RECOVERY Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: egac_egtutl.c
*
*/
#ifdef ANSI
PUBLIC Void eguMakeAndAddRecoveryIe
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
EgUMsg      *eguMsg
)
#else
PUBLIC Void eguMakeAndAddRecoveryIe(tcCb, spCb, eguMsg)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
EgUMsg      *eguMsg;
#endif /* ANSI */
{
   U8     recvVal = DFLT_RECOVERY_VAL;
   Bool   recvPresent = TRUE;
   EgUIe  eguIe;
   Bool   recoveryDataTypeChange = FALSE;
   Bool   InvalidLenRecoveryIe = FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguMakeAndAddRecoveryIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&eguIe, 0 , sizeof(EgUIe));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                 (Txt *)"recoveryDataTypeChange",  &recoveryDataTypeChange);

   if(recoveryDataTypeChange)
   {
     eguAcEgtBuildIeHeader(&eguIe, EGU_RECOVERY_IETYPE, EG_UNSIGNED_32);
   }
   else
   {
     eguAcEgtBuildIeHeader(&eguIe, EGU_RECOVERY_IETYPE, EG_UNSIGNED_8);
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                 (Txt *)"InvalidLenRecoveryIe",  &InvalidLenRecoveryIe);

   if(InvalidLenRecoveryIe)
   {
        cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                       (Txt *)"recvVal", &recvVal);
        eguIe.t.valUnSgnd32 = recvVal;
   }
   else
   {
        cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                       (Txt *)"recvVal", &recvVal);
        eguIe.t.valUnSgnd8 = recvVal;
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"recvIeType", &eguIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"recvPresent",  &recvPresent);

   if( recvPresent == TRUE)
   {
       if(EgUUtilGmAppendIe(eguMsg, &eguIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,
             "eguMakeAndAddRecoveryIe() : Unable to Append IE to eGTP message\n"));
       }
   }
   
   RETVOID;
} /* eguMakeAndAddRecoveryIe */

/*
*
*       Fun:   eguMakeAndAddTeidDataIE
*
*       Desc:  This function is used to Build TeidData Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: egac_egtutl.c
*
*/
#ifdef ANSI
PUBLIC Void eguMakeAndAddTeidDataIE
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
EgUMsg      *eguMsg
)
#else
PUBLIC Void eguMakeAndAddTeidDataIE(tcCb, spCb, eguMsg)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
EgUMsg      *eguMsg;
#endif /* ANSI */
{
   Bool   teidDataPresent = TRUE;
   U32    teid = EGUAC_DFLT_TEID;
   EgUIe  eguIe;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguMakeAndAddTeidDataIE)

   /* Fill the ie properties */
   cmMemset((U8 *)&eguIe, 0 , sizeof(EgUIe));

   eguAcEgtBuildIeHeader(&eguIe, EGU_TEID_IETYPE, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                  (Txt *)"teid",  &teid);

   eguIe.t.valUnSgnd32 = teid;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"teidDataIeType", &eguIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"teidDataPresent",  &teidDataPresent);

   if(teidDataPresent == TRUE)
   {
       if(EgUUtilGmAppendIe(eguMsg, &eguIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,
             "eguMakeAndAddTeidDataIE() : Unable to Append IE to eGTP message\n"));
       }
   }

   RETVOID;
} /* eguMakeAndAddTeidDataIE */

/*
*
*       Fun:   eguMakeAndAddGtpUPeerAddrIE
*
*       Desc:  This function is used to Build TeidData Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: egac_egtutl.c
*
*/
#ifdef ANSI
PUBLIC Void eguMakeAndAddGtpUPeerAddrIE
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
EgUMsg      *eguMsg
)
#else
PUBLIC Void eguMakeAndAddGtpUPeerAddrIE(tcCb, spCb, eguMsg)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
EgUMsg      *eguMsg;
#endif /* ANSI */
{
   Bool   gtpUPeerAddrPresent = TRUE;
   U8     addrType = CM_IPV4ADDR_TYPE;
   Txt    eguIpAddr[50];
   EgUIe  eguIe;
   S16    ret = 0;
   Bool  invalAddrType = FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguMakeAndAddGtpUPeerAddrIE)

   /* Fill the ie properties */
   cmMemset((U8 *)&eguIe, 0 , sizeof(EgUIe));

   /* Rosh fixes */
   eguAcEgtBuildIeHeader(&eguIe, EGU_GSN_ADDR_IETYPE, EG_IP_ADDR);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"addrType",  &addrType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"invalAddrType",  &invalAddrType);

   if(addrType == CM_IPV4ADDR_TYPE)
   {
      if(invalAddrType)
         eguIe.t.ipAddr.addrType = 10;
      else
         eguIe.t.ipAddr.addrType = addrType;

      ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"address",&(eguIpAddr));
      if(ret == CMXTA_ERR_NO_VALUE)
      {
           cmInetAddr ((S8 *)EGUAC_DFLT_ADDR, &(eguIe.t.ipAddr.u.ipv4));
      }
      else
      {
           cmInetAddr ( (S8 *)eguIpAddr, &(eguIe.t.ipAddr.u.ipv4));
      }
      eguIe.t.ipAddr.u.ipv4 = CM_INET_HTON_U32(eguIe.t.ipAddr.u.ipv4);
   }
#ifdef IPV6_SUPPORTED
   else
   {
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"address",&(eguIpAddr));
      if(ret == CMXTA_ERR_NO_VALUE)
      {
           cmInetPton6((S8 *)EGUAC_DFLT_ADDR_IPV6, &(eguIe.t.ipAddr.u.ipv6));
      }
      else
      {
           cmInetPton6 (&(eguIe.t.ipAddr.u.ipv6), eguIpAddr);
      }
   }
#endif

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"gtpUPeerAddrPresent",  &gtpUPeerAddrPresent);

   if(gtpUPeerAddrPresent == TRUE)
   {
       if(EgUUtilGmAppendIe(eguMsg, &eguIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,
             "eguMakeAndAddGtpUPeerAddrIE() : Unable to Append IE to eGTP message\n"));
       }
   }

   RETVOID;
} /* eguMakeAndAddGtpUPeerAddrIE */

/*
*
*       Fun:   eguMakeAndAddExtHdrTypeLstIE
*
*       Desc:  This function is used to Build Extension Hdr Type List Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: egac_egtutl.c
*
*/
#ifdef ANSI
PUBLIC Void eguMakeAndAddExtHdrTypeLstIE
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
EgUMsg      *eguMsg
)
#else
PUBLIC Void eguMakeAndAddExtHdrTypeLstIE(tcCb, spCb, eguMsg)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
EgUMsg      *eguMsg;
#endif /* ANSI */
{
   Bool   extHdrLstPresent = TRUE;
   U8     nmbExtHdrs = EGT_U_MAX_EXT_TYPES;
   U8     extType = EGUAC_DFLT_EXTTYPE_VAL; 
   U8     idx = 0;
   EgUIe  eguIe;
   U8    invalDataType = FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguMakeAndAddExtHdrTypeLstIE)

   /* Fill the ie properties */
   cmMemset((U8 *)&eguIe, 0 , sizeof(EgUIe));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"invalDataType",  &invalDataType);

   if(invalDataType)
   {
      eguAcEgtBuildIeHeader(&eguIe, EGU_EXT_HDR_LST_IETYPE, EG_UNSIGNED_8);
   }
   else
   {
      eguAcEgtBuildIeHeader(&eguIe, EGU_EXT_HDR_LST_IETYPE, EG_EXT_HDR_TYPE_LST);
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"nmbExtHdrs",  &nmbExtHdrs);

   eguIe.t.extHdrTypeLst.noOfExtHdrs = nmbExtHdrs;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"extType",  &extType);

   if(nmbExtHdrs <= EGT_U_MAX_EXT_TYPES)
   {
     for(idx=0; idx < nmbExtHdrs; idx++)
     {
       eguIe.t.extHdrTypeLst.extType[idx] = extType+idx;
     }
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"extHdrTypLstIeType", &eguIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"extHdrLstPresent",  &extHdrLstPresent);

   if(extHdrLstPresent == TRUE)
   {
       if(EgUUtilGmAppendIe(eguMsg, &eguIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,
             "eguMakeAndAddExtHdrTypeLstIE() : Unable to Append IE to eGTP message\n"));
       }
   }

   RETVOID;
} /* eguMakeAndAddExtHdrTypeLstIE */

/*
 *
 *       Fun:   eguAcEdmBuildEchoReqMsg
 *
 *       Desc:
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 eguAcEdmBuildEchoReqMsg
(
CmXtaTCCb    *tcCb,       /* tcCb data structure  */
CmXtaSpCb    *spCb,       /* spCb data structure  */
U32          msgType,
EgUMsg      **eguMsg,
Mem          *memInfo
)
#else
PUBLIC S16 eguAcEdmBuildEchoReqMsg(tcCb, spCb, msgType, eguMsg, memInfo)
CmXtaTCCb    *tcCb;       /* tcCb data structure  */
CmXtaSpCb    *spCb;       /* spCb data structure  */
U32          msgType;
EgUMsg       **eguMsg;
Mem          *memInfo;
#endif /* ANSI */
{
   Bool        noIEs = FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcEdmBuildEchoReqMsg)

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"noIEs",  &noIEs);
   if(!noIEs)
   {
      eguMakeAndAddPvtExtIE(tcCb, spCb, *eguMsg);
   }

   RETVALUE(ROK);
} /* end of eguAcEdmBuildEchoReqMsg() */

/*
 *
 *       Fun:   eguAcEdmBuildEchoRspMsg
 *
 *       Desc:
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 eguAcEdmBuildEchoRspMsg
(
CmXtaTCCb    *tcCb,       /* tcCb data structure  */
CmXtaSpCb    *spCb,       /* spCb data structure  */
U32          msgType,
EgUMsg       **eguMsg,
Mem          *memInfo
)
#else
PUBLIC S16 eguAcEdmBuildEchoRspMsg(tcCb, spCb, msgType, eguMsg, memInfo)
CmXtaTCCb    *tcCb;       /* tcCb data structure  */
CmXtaSpCb    *spCb;       /* spCb data structure  */
U32          msgType;
EgUMsg       **eguMsg;
Mem          *memInfo;
#endif /* ANSI */
{
   Bool        noIEs = FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcEdmBuildEchoRspMsg)

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"noIEs",  &noIEs);
   if(!noIEs)
   {
      eguMakeAndAddRecoveryIe(tcCb, spCb, *eguMsg);
      eguMakeAndAddPvtExtIE(tcCb, spCb, *eguMsg);
   }

   RETVALUE(ROK);
} /* end of eguAcEdmBuildEchoRspMsg() */

/*
 *
 *       Fun:   eguAcEdmBuildErrIndMsg 
 *
 *       Desc:
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 eguAcEdmBuildErrIndMsg 
(
CmXtaTCCb    *tcCb,       /* tcCb data structure  */
CmXtaSpCb    *spCb,       /* spCb data structure  */
U32          msgType,
EgUMsg       **eguMsg,
Mem          *memInfo
)
#else
PUBLIC S16 eguAcEdmBuildErrIndMsg(tcCb, spCb, msgType, eguMsg, memInfo)
CmXtaTCCb    *tcCb;       /* tcCb data structure  */
CmXtaSpCb    *spCb;       /* spCb data structure  */
U32          msgType;
EgUMsg       **eguMsg;
Mem          *memInfo;
#endif /* ANSI */
{
   Bool        noIEs = FALSE;

   U8          unExpectedTvIe = FALSE;
   U8          unExpectedTlvIe = FALSE;
   U8          unKnownIe = FALSE;
   U8          noAscending = FALSE;
   U8          noOptionalIE = FALSE;
   U8          dupIE = FALSE;
   U8          dupPvtExtIE = FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcEdmBuildErrIndMsg)

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"noIEs",  &noIEs);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unExpectedTvIe",  &unExpectedTvIe);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unExpectedTlvIe",  &unExpectedTlvIe);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unKnownIe",  &unKnownIe);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"noAscending",  &noAscending);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"noOptionalIE",  &noOptionalIE);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"dupIE",  &dupIE);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"dupPvtExtIE",  &dupPvtExtIE);

   if(!noIEs)
   {
      if(unExpectedTvIe)
      {
         eguMakeAndAddRecoveryIe(tcCb, spCb, *eguMsg);
      }

      if(unKnownIe)
      {
         eguMakeAndAddDelayIe(tcCb, spCb, *eguMsg);
      }

      if(noAscending)
      {
         eguMakeAndAddGtpUPeerAddrIE(tcCb, spCb, *eguMsg);
         eguMakeAndAddTeidDataIE(tcCb, spCb, *eguMsg);
      }
      else
      {
         eguMakeAndAddTeidDataIE(tcCb, spCb, *eguMsg);
         eguMakeAndAddGtpUPeerAddrIE(tcCb, spCb, *eguMsg);
         if(dupIE)
         {
            eguMakeAndAddGtpUPeerAddrIE(tcCb, spCb, *eguMsg);
         }
      }

      if(unExpectedTlvIe)
      {
         eguMakeAndAddExtHdrTypeLstIE(tcCb, spCb, *eguMsg);
      }

      if(!noOptionalIE)
      {
         eguMakeAndAddPvtExtIE(tcCb, spCb, *eguMsg);
         if(dupPvtExtIE)
         {
            eguMakeAndAddPvtExtIE(tcCb, spCb, *eguMsg);
         }
      }
   }
   RETVALUE(ROK);   
} /* end of eguAcEdmBuildErrIndMsg() */
 
/*
 *
 *       Fun:    eguAcEdmBuildSuppExtHdrNotMsg 
 *
 *       Desc:
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16  eguAcEdmBuildSuppExtHdrNotMsg 
(
CmXtaTCCb    *tcCb,       /* tcCb data structure  */
CmXtaSpCb    *spCb,       /* spCb data structure  */
U32          msgType,
EgUMsg       **eguMsg,
Mem          *memInfo
)
#else
PUBLIC S16 eguAcEdmBuildSuppExtHdrNotMsg(tcCb, spCb, msgType, eguMsg, memInfo)
CmXtaTCCb    *tcCb;       /* tcCb data structure  */
CmXtaSpCb    *spCb;       /* spCb data structure  */
U32          msgType;
EgUMsg       **eguMsg;
Mem          *memInfo;
#endif /* ANSI */
{
   Bool        noIEs = FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcEdmBuildSuppExtHdrNotMsg)

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"noIEs",  &noIEs);
   if(!noIEs)
   {
      eguMakeAndAddExtHdrTypeLstIE(tcCb, spCb, *eguMsg);
   }

   RETVALUE(ROK);
} /* end of eguAcEdmBuildSuppExtHdrNotMsg() */

/*
 *
 *       Fun:    eguAcEdmBuildEndMarkerMsg 
 *
 *       Desc:
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 eguAcEdmBuildEndMarkerMsg 
(
CmXtaTCCb    *tcCb,       /* tcCb data structure  */
CmXtaSpCb    *spCb,       /* spCb data structure  */
U32          msgType,
EgUMsg       **eguMsg,
Mem          *memInfo
)
#else
PUBLIC S16 eguAcEdmBuildEndMarkerMsg(tcCb, spCb, msgType, eguMsg, memInfo)
CmXtaTCCb    *tcCb;       /* tcCb data structure  */
CmXtaSpCb    *spCb;       /* spCb data structure  */
U32          msgType;
EgUMsg       **eguMsg;
Mem          *memInfo;
#endif /* ANSI */
{
   Bool        noIEs = FALSE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(eguAcEdmBuildEndMarkerMsg)

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"noIEs",  &noIEs);
   if(!noIEs)
   {
      eguMakeAndAddPvtExtIE(tcCb, spCb, *eguMsg);
   }

   RETVALUE(ROK);
} /* end of eguAcEdmBuildEndMarkerMsg() */


/**********************************************************************
*       Fun:   egAcCmpTptAddr 
*
*       Desc:  Compares two CmTptAddr
*
*       Ret:   TRUE = complete match, FALSE = no match or address match
*
*       Notes: Returns _address
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egAcCmpTptAddr
(
CmTptAddr  *one,                               /* Address to compare */
CmTptAddr  *two,                               /* Address to compare */
Bool       *addressMatch    /* Return true atleast _address_ matches */
)
#else
PUBLIC S16 egAcCmpTptAddr( one,  two, addressMatch)
CmTptAddr  *one;                               /* Address to compare */
CmTptAddr  *two;                               /* Address to compare */
Bool       *addressMatch;   /* Return true atleast _address_ matches */
#endif
{
#ifdef IPV6_SUPPORTED
   U16 ipV6AdrSz = 0;                         /* IPV6 Address size */
#endif 

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcCmpTptAddr);

   /***************************
    * Initialize the variable *
    ***************************/
   (*addressMatch) = FALSE;

  /********************************************************
   * If input address type is not unique then return fail *
   ********************************************************/
   if (one->type != two->type)
   {
      EG_RETVALUE(RFAILED);
   }

  /************************************************************
   * Process based on input Addres type.I,e IPV4 or IPV6 type *
   ************************************************************/
   if (one->type == CM_TPTADDR_IPV4)
   {
     /***************************************************
      * If Input address is not unique then return fail *
      ***************************************************/
      if (one->u.ipv4TptAddr.address != two->u.ipv4TptAddr.address)
      {
         EG_RETVALUE(RFAILED);
      }

      /********************************
       * Mark address matched as true *
       ********************************/
      (*addressMatch) = TRUE;

     /***************************************************
      * If Input address Port not unique then return fail *
      ***************************************************/
      if (one->u.ipv4TptAddr.port != two->u.ipv4TptAddr.port)
      {
         EG_RETVALUE(RFAILED);
      }

      EG_RETVALUE(ROK);
   }
#ifdef IPV6_SUPPORTED
   else if (one->type == CM_TPTADDR_IPV6)
   {
      /*********************************************
       * Loop though the size of IPV6 address size *
       * and compare the uniqueness of the address *
       * If it is not unique then return fail      *
       *********************************************/
      while (ipV6AdrSz < (CM_IPV6ADDR_SIZE - 1))
      {
         if (one->u.ipv6TptAddr.ipv6NetAddr[ipV6AdrSz] !=
             two->u.ipv6TptAddr.ipv6NetAddr[ipV6AdrSz])
         {
            EG_RETVALUE(RFAILED);
         }
         ipV6AdrSz++;
      }

      /********************************
       * Mark address matched as true *
       ********************************/
      (*addressMatch) = TRUE;

     /***************************************************
      * If Input address Port not unique then return fail *
      ***************************************************/
      if (one->u.ipv6TptAddr.port != two->u.ipv6TptAddr.port)
      {
         EG_RETVALUE(RFAILED);
      }

      EG_RETVALUE(ROK);
   }
#endif /* IPV6_SUPPORTED */

   /******************************************************
     * If we are reaching here it means there is some    *
     * error. eg type is having wrong value              *                        
     ****************************************************/
   EG_RETVALUE(RFAILED);

}
/*-- # --*/


#endif /* EGTP_U */
/********************************************************************30**

         End of file:     egac_egtutl.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:44:27 2014

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
------------ -------- ---- ----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3  eg001.201    asaurabh    1. Updating for EGTP_U_REL_9
/main/3  eg003.201    psingh      1. Merged code from eg006.102 to Fix 
                                     TRACE5 macro related issue
/main/3  eg004.201    asaurabh    1. Flag for Handling TEID on PSF activation
                                  2. Header files for GTP-C PSF upgrade
/main/3  eg006.201   psingh       1. Update the crtFlag to accept DUMMY flag
                                  2. Corrected port updation for bldMsg
                                  3. Provided egAcEgGetAddress to GTP_C 
/main/3  eg012.201   shpandey     1. In function eguAcUtlEgtBuildTnlMgmtReq:decaration of variable tunnel type guarded 
                                     under EGTP_U_REL_9 flag 
*********************************************************************91*/
