
/********************************************************************20**

     Name:    EGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_egtreg.c

     Sid:      smeg_s11utl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:19:12 2015

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
#include "eg_dbs11.h"           /* Egtpeter Layer Manager   */
#include "eg_dbutl.h"           /* Egtpeter Layer Manager   */
#endif
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
/*eg004.201 Header files added for eGTPC PSF Upgrade*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.h"
#include "egac_acc.h"
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"
#include "cm_xta.x"
#include "egac_acc.x"
#include "egac_edm.x"
#include "eg_util.x"       /* Eg Utility library */
#if 0
#include "eg_dbutl.x" 
#include "eg_dbs11.x" 
#endif
#include "smeg_ieutl.x" 


#ifdef EGTP_C

/*
*
*       Fun:   egEgtBuildCrtSesReqMsg
*
*       Desc:  This function is used to Build CSR message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildCrtSesReqMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg **egMsg,
U8     intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildCrtSesReqMsg(tcCb,spCb,egMsg,intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg **egMsg;
U8     intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;
   U8                      noIEs= FALSE;
   Bool                  unknownIe=FALSE;
   U8     brercntxRepeat = FALSE;
   U8    rattypeRepeat = FALSE;
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildCrtSesReqMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildCrtSesReqMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_CS_REQ, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_CS_REQ);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);
   if(!noIEs)
   {
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_IMSI_IETYPE:         
         { 
            /*****************
        * Add IMSI code *
        ****************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddImsiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_MSISDN_IETYPE:                
         {
            /* Add MSISDN */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddMsisdnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_MEI_IETYPE:                       
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddMeiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_ULI_IETYPE:        
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddUsrLocInfoIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_SERVING_NWK_IETYPE:              
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddServNwIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RAT_TYPE_IETYPE:
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRatTypeIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);

				cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"rattypeRepeat",  &rattypeRepeat);
            if(rattypeRepeat)
				{
				  cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
				  egLvlInfo.ieInfo[0].occrPres = TRUE;
				  egLvlInfo.ieInfo[0].occr = 2;

				  /* Common function which frame message based on instance value */
				  makeAndAddRatTypeIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
				}

            break;
         }
         case EG_INDICATION_IETYPE:           
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddIndicationIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_FTEID_IETYPE:         
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddFTeidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_APN_IETYPE:             
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddAccessPntNameIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_SEL_MODE_IETYPE: 
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddSelModeIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PDN_TYPE_IETYPE:
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPdnTypeIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_APN_RESTRICT_IETYPE:
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddMaxApnRestIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_BEARER_CNTX_IETYPE: 
         {
       /*  Based on instance */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"brercntxRepeat",  &brercntxRepeat);
            if(brercntxRepeat)
            {
               cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               egLvlInfo.ieInfo[0].occrPres = TRUE;
               egLvlInfo.ieInfo[0].occr = 2;
             
               /* Common function which frame message based on instance value */
               makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            }
            break;
         }

         case EG_PAA_IETYPE:
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPaaIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         
         case  EG_AMBR_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddAmbrIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }

        case  EG_PCO_IETYPE:
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }

         case  EG_TRACE_INFO_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddTrcIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_RECOVERY_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
    }   
         case  EG_CSID_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddCsidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
    }   
         case  EG_PRIVATE_EXT_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
    }   
 
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */
   } /* end of if */
   /* Handle the unknown IE here */
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);
    if (unknownIe)
    {
        cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
        /* Common function which frame message based on instance value */
        makeAndAddUnknownIe(tcCb,spCb,*egMsg,&egLvlInfo);
    }
    
}  /*  egEgtBuildCrtSesReqMsg     */ 

/*
*
*       Fun:   egEgtBuildCrtSesRspMsg
*
*       Desc:  This function is used to Build CSR message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildCrtSesRspMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildCrtSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                     idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildCrtSesRspMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildCrtSesRspMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_CS_RSP, intfType);

   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_CS_RSP);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*****************
        * Add IMSI code *
        ****************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,
                         gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_FTEID_IETYPE:         
         {
       /*  Based on instance */
            /*   Add User Name AVP      */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddFTeidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PAA_IETYPE:
         {
            /* Add Proxy Info AVP    */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPaaIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_APN_RESTRICT_IETYPE:
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddMaxApnRestIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_AMBR_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddAmbrIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_PCO_IETYPE:
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_BEARER_CNTX_IETYPE: 
         {
       /*  Based on instance */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_TRACE_INFO_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddTrcIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case  EG_RECOVERY_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
    }   
         case  EG_CSID_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddCsidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
    }   
         case  EG_PRIVATE_EXT_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
    }   
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildSesRspMsg     */ 

/*
*
*       Fun:   egEgtBuildCrtBreReqMsg
*
*       Desc:  This function is used to Create Bearer Request message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildCrtBreReqMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildCrtBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildCrtBreReqMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildCrtBreReqMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_CB_REQ, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_CB_REQ);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_PROCEDURE_TID_IETYPE:         
         { 
            /*********************************
        * Add Procedure Transaction     *
        ********************************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPTidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_EBI_IETYPE:                
         {
            /* Add LBI */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddEbiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_AMBR_IETYPE:                        
         {
            /*   Add APN AMBR */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddAmbrIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PCO_IETYPE:        
         {
            /*   Add Protocol configuration option */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_CSID_IETYPE:                
         {
            /*   Add CSID */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCsidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildCrtBreReqMsg     */ 

/*
*
*       Fun:   egEgtBuildCrtBreRspMsg
*
*       Desc:  This function is used to Create Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildCrtBreRspMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildCrtBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildCrtBreRspMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildCrtBreRspMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_CB_RSP, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_CB_RSP);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
       /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_CSID_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCsidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
			}
			case EG_PCO_IETYPE:
			{
			  /*   Add Protocol configuration option */
			  cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
			  makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
			  break;
			}
			case EG_ULI_IETYPE:
			{
			  /* Add User location info */
			  cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
			  makeAndAddUsrLocInfoIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
			  break;
			}
			case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildCrtBreRspMsg     */ 

/*
*
*       Fun:   egEgtBuildBreResCmdMsg
*
*       Desc:  This function is used to Build CSR message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildBreResCmdMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildBreResCmdMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildBreResCmdMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildBreResCmdMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_BR_CMND, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_BR_CMND);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_EBI_IETYPE:         
         { 
            /****************************
        * Add Linked EPS Bearer ID *
        ***************************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddEbiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_PROCEDURE_TID_IETYPE:                
         {
            /* Add Procedure Transaction ID */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPTidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_FLOW_QOS_IETYPE:                       
         {
            /*   Add Flow Quality of Services */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddFlowQosIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_TAD_IETYPE:        
         {
            /*   Add Traffic Aggregation Description */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddTadIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildBreResCmdMsg     */ 


/*
*
*       Fun:   egEgtBuildBreResFlrIndMsg
*
*       Desc:  This function is used to Build Modify Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildBreResFlrIndMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildBreResFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildBreResFlrIndMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildBreResFlrIndMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_BR_FAIL_IND, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_BR_FAIL_IND);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_EBI_IETYPE:                
         {
            /* Add LBI */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddEbiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PROCEDURE_TID_IETYPE:                        
         {
            /*   Add Procedure transaction ID */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPTidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RECOVERY_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildBreResFlrIndMsg     */ 

/*
*
*       Fun:   egEgtBuildModBreReqMsg
*
*       Desc:  This function is used to Build Modify Bearer Request message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildModBreReqMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildModBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildModBreReqMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildModBreReqMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_MB_REQ, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_MB_REQ);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_MEI_IETYPE:         
         { 
            /*********************************
        * Add Mobile Equipment identity *
        ********************************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddMeiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_ULI_IETYPE:                
         {
            /* Add User location info */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddUsrLocInfoIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_SERVING_NWK_IETYPE:                        
         {
            /*   Add Serving Network */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddServNwIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RAT_TYPE_IETYPE:        
         {
            /*   Add RAT Type */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRatTypeIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_INDICATION_IETYPE:              
         {
            /*   Add Indication flags */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddIndicationIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_FTEID_IETYPE:              
         {
            /*   Add Fteid */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddFTeidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_AMBR_IETYPE:              
         {
            /*   Add Aggregate Maximum Bit Rate */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddAmbrIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_DELAY_IETYPE:              
         {
            /*   Add delay value */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddDelayIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildModBreReqMsg     */ 

/*
*
*       Fun:   egEgtBuildModBreRspMsg
*
*       Desc:  This function is used to Build Modify Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildModBreRspMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildModBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildModBreRspMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildModBreRspMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_MB_RSP, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_MB_RSP);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_MSISDN_IETYPE:                
         {
            /* Add MSISDN */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddMsisdnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_FTEID_IETYPE:                        
         {
            /*   Add Fteid */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddFTeidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PCO_IETYPE:        
         {
            /*   Add Protocol configuration option */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RECOVERY_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildModBreRspMsg     */ 

/*
*
*       Fun:   egEgtBuildDelSesReqMsg
*
*       Desc:  This function is used to Build Delete Session Request message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDelSesReqMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDelSesReqMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDelSesReqMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDelSesReqMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DS_REQ, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DS_REQ);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_EBI_IETYPE:         
         { 
            /****************************
        * Add Linked EPS Bearer ID *
        ***************************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddEbiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_INDICATION_IETYPE:                
         {
            /* Add Indication Flags */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddIndicationIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PCO_IETYPE:                        
         {
            /*   Add protocol configuration options */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildDelSesReqMsg     */ 
/*
*
*       Fun:   egEgtBuildDelBreReqMsg
*
*       Desc:  This function is used to Build Modify Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDelBreReqMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDelBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDelBreReqMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDelBreReqMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DB_REQ, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DB_REQ);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_EBI_IETYPE:         
         { 
            /****************************
        * Add Linked EPS bearer ID *
        ***************************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddEbiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PROCEDURE_TID_IETYPE:                
         {
            /*   Add Procedure Transaction ID */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPTidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_AMBR_IETYPE:                
         {
            /*   Add APN AMBR */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddAmbrIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PCO_IETYPE:        
         {
            /*   Add Protocol configuration option */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_CSID_IETYPE:                
         {
            /*   Add CSID */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCsidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildDelBreReqMsg     */

/*
*
*       Fun:   egEgtBuildDwLnkDatNotFlrIndMsg
*
*       Desc:  This function is used to Build Downlink Data Notification Failure Indication
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDwLnkDatNotFlrIndMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDwLnkDatNotFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDwLnkDatNotFlrIndMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDwLnkDatNotFlrIndMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DD_NOTFN_FAIL_IND, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DD_NOTFN_FAIL_IND);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
             * Add Cause *
             ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildDwLnkDatNotFlrIndMsg */ 

/*
*
*       Fun:   egEgtBuildDelSesRspMsg
*
*       Desc:  This function is used to Build Modify Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDelSesRspMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDelSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                     idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDelSesRspMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDelSesRspMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DS_RSP, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DS_RSP);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_RECOVERY_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PCO_IETYPE:        
         {
            /*   Add Protocol configuration option */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildDelSesRspMsg     */ 
/*
*
*       Fun:   egEgtBuildDelBreRspMsg
*
*       Desc:  This function is used to Build Modify Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDelBreRspMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDelBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                     idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDelBreRspMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDelBreRspMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DB_RSP, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DB_RSP);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_EBI_IETYPE:                
         {
            /* Add LBI */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddEbiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RECOVERY_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_CSID_IETYPE:                
         {
            /*   Add CSID */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCsidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildDelBreRspMsg     */ 

/*
*
*       Fun:   egEgtBuildDwLnkDatNotMsg
*
*       Desc:  This function is used to Build Modify Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDwDatLnkNotMsg 
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDwDatLnkNotMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                     idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDwDatLnkNotMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDwDatLnkNotMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DWN_DATA_NOTFN, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DWN_DATA_NOTFN);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildDwDatLnkNotMsg     */ 

/*
*
*       Fun:   egEgtBuildDwDatLnkNotAckMsg
*
*       Desc:  This function is used to Build Modify Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDwDatLnkNotAckMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDwDatLnkNotAckMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb     *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                     idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDwDatLnkNotAckMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDwDatLnkNotAckMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_DELAY_IETYPE:                
         {
            /* Add Data Notifictaion Delay */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddDelayIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RECOVERY_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildDwLnkDatNotAckMsg     */ 


/*
*
*       Fun:   egEgtBuildModBreCmdMsg
*
*       Desc:  This function is used to Build Modify Bearer Command
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildModBreCmdMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildModBreCmdMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildModBreCmdMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildModBreCmdMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_MB_CMND, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_MB_CMND);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case  EG_AMBR_IETYPE:  
         {
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddAmbrIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }

         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }

         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildModBreCmdMsg     */ 

/*
*
*       Fun:   egEgtBuildModBreFlrIndMsg
*
*       Desc:  This function is used to Build Modify Bearer Failure Indication
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildModBreFlrIndMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildModBreFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                     idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildModBreFlrIndMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildModBreFlrIndMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_MBFAIL_IND, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_MBFAIL_IND);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RECOVERY_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /* egEgtBuildModBreFlrIndMsg     */ 

/*
*
*       Fun:   egEgtBuildUpdBreReqMsg
*
*       Desc:  This function is used to Build Update Bearer Request message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildUpdBreReqMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildUpdBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                     idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildUpdBreReqMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildUpdBreReqMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_UB_REQ, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_UB_REQ);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_IMSI_IETYPE:
         {
            /*****************
        * Add IMSI code *
        ****************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddImsiIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_BEARER_CNTX_IETYPE:
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PROCEDURE_TID_IETYPE:
         {
            /*********************************
        * Add Procedure Transaction     *
        ********************************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPTidIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PCO_IETYPE:        
         {
            /*   Add Protocol configuration option */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_AMBR_IETYPE:
         {
            /*   Add Aggregate Maximum Bit Rate */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddAmbrIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_TRACE_INFO_IETYPE:
         {
            /*   Add Trace Information */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddTrcIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildUpdBreReqMsg     */ 
/*
*
*       Fun:   egEgtBuildUpdBreRspMsg
*
*       Desc:  This function is used to Build Update Bearer Response message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildUpdBreRspMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildUpdBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildUpdBreRspMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildUpdBreRspMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_UB_RSP, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_UB_RSP);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PCO_IETYPE:        
         {
            /*   Add Protocol configuration option */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPCOIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RECOVERY_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /* egEgtBuildUpdBreRspMsg */ 
/*
*
*       Fun:   egEgtBuildDeActvBreCmdMsg
*
*       Desc:  This function is used to Build Deactivate Bearer Command
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDeActvBreCmdMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDeActvBreCmdMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                    idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDeActvBreCmdMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDeActvBreCmdMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DB_CMND, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DB_CMND);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /*  egEgtBuildDeActvBreCmdMsg     */ 
/*
*
*       Fun:   egEgtBuildDeActvBreFlrIndMsg
*
*       Desc:  This function is used to Build Deactivate Bearer Failure Indication
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildDeActvBreFlrIndMsg
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg **egMsg,
U8      intfType,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildDeActvBreFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg **egMsg;
U8      intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo           egLvlInfo;
   LegMsgEntry              *gmEntry= NULLP;
   U16                     idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildDeActvBreFlrIndMsg)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildDeActvBreFlrIndMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   gmEntry  = egGetMsgFrmGmDict(EGT_GTPC_MSG_DB_FAIL_IN, intfType);
   if(gmEntry == NULLP)
   {
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_DB_FAIL_IN);
   
   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case EG_CAUSE_IETYPE:         
         { 
            /*************
        * Add Cause *
        ************/
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }    
         case EG_BEARER_CNTX_IETYPE:              
         {
            /*   Add Bearer Context */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddBrerCntxIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_RECOVERY_IETYPE:                
         {
            /*   Add Recovery */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         case EG_PRIVATE_EXT_IETYPE:              
         {
            /*   Add Private Extension */
            cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,gmEntry->ieProperties[idx]);
            break;
         }
         default:
         {
            break;
         }
      } /*end of switch  */
    } /* end of for */

}  /* egEgtBuildDeActvBreFlrIndMsg     */ 

/*
*
*       Fun:   egEgtBuildS11SuspendNotMsg
*
*       Desc:  This function is used to Build Suspend Notification message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildS11SuspendNotMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11SuspendNotMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildS11SuspendNotMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildS11SuspendNotMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_SUSPENDNOT_CMD_CODE, intfType)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildS11SuspendNotMsg: Unable to get EGTP message signature\n"));
      RETVOID;
   }

   cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_SUSPENDNOT_CMD_CODE);

   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case  EG_IMSI_IETYPE:
         {
            cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddImsiIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);

            break;
         } /* end of case */

         case  EG_PRIVATE_EXT_IETYPE:
         {
            cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);

            break;
         } /* end of case */

         default:
         {
            break;
         } /* end of case */
      } /*end of switch  */
   } /* end of for */

   RETVOID;
} /* end of egEgtBuildS11SuspendNotMsg */ 


/*
*
*       Fun:   egEgtBuildS11SuspendAckMsg
*
*       Desc:  This function is used to Build Suspend Acknowledgement message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildS11SuspendAckMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11SuspendAckMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildS11SuspendAckMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildS11SuspendAckMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_SUSPENDACK_CMD_CODE, intfType)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildS11SuspendAckMsg: Unable to get EGTP message signature\n"));
      RETVOID;
   }

   cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_SUSPENDACK_CMD_CODE);

   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case  EG_CAUSE_IETYPE:
         {
            cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddCauseIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);

            break;
         } /* end of case */

         case  EG_PRIVATE_EXT_IETYPE:
         {
            cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);

            break;
         } /* end of case */

         default:
         {
            break;
         } /* end of case */
      } /*end of switch  */
   } /* end of for */

   RETVOID;
} /* end of egEgtBuildS11SuspendAckMsg */ 


/*
*
*       Fun:   egEgtBuildS11ResumeNotMsg
*
*       Desc:  This function is used to Build Resume Notification message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildS11ResumeNotMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11ResumeNotMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildS11ResumeNotMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildS11ResumeNotMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_RESUMENOT_CMD_CODE, intfType)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildS11ResumeNotMsg: Unable to get EGTP message signature\n"));
      RETVOID;
   }

   cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_RESUMENOT_CMD_CODE);

   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case  EG_IMSI_IETYPE:
         {
            cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddImsiIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);

            break;
         } /* end of case */

         case  EG_PRIVATE_EXT_IETYPE:
         {
            cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);

            break;
         } /* end of case */

         default:
         {
            break;
         } /* end of case */
      } /*end of switch  */
   } /* end of for */

   RETVOID;
} /* end of egEgtBuildS11ResumeNotMsg */ 


/*
*
*       Fun:   egEgtBuildS11ResumeAckMsg
*
*       Desc:  This function is used to Build Resume Acknowledgement message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildS11ResumeAckMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11ResumeAckMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildS11ResumeAckMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildS11ResumeAckMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_RESUMEACK_CMD_CODE, intfType)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egEgtBuildS11ResumeAckMsg: Unable to get EGTP message signature\n"));
      RETVOID;
   }

   cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_RESUMEACK_CMD_CODE);

   for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
   {
      switch(gmEntry->ieProperties[idx].ieType)
      {
         case  EG_CAUSE_IETYPE:
         {

            /* Add Cause code */
            cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            makeAndAddCauseIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);

            break;
         } /* end of case */

         case  EG_PRIVATE_EXT_IETYPE:
         {
            cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
            /* Common function which frame message based on instance value */
            makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);

            break;
         } /* end of case */

         default:
         {
            break;
         } /* end of case */
      } /*end of switch  */
   } /* end of for */

   RETVOID;
} /* end of egEgtBuildS11ResumeAckMsg */ 

#ifdef ANSI
PUBLIC Void  egEgtBuildS11TraceSessActvMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11TraceSessActvMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   TRC2(egEgtBuildS11TraceSessActvMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11TraceSessActvMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_TRACESESSACTV_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_TRACESESSACTV_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11TraceSessActvMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_IMSI_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddImsiIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_TRACE_INFO_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddTrcIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_MEI_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddMeiIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}



#ifdef ANSI
PUBLIC Void  egEgtBuildS11TraceSessDeactvMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11TraceSessDeactvMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   TRC2(egEgtBuildS11TraceSessDeactvMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11TraceSessDeactvMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_TRACESESSDEACTV_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_TRACESESSDEACTV_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11TraceSessDeactvMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_TRACE_REF_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddTraceRefIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}


#ifdef ANSI
PUBLIC Void  egEgtBuildS11DelPdnConSetReqMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11DelPdnConSetReqMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   TRC2(egEgtBuildS11DelPdnConSetReqMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11DelPdnConSetReqMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_DELPDNCONSETREQ_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_DELPDNCONSETREQ_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11DelPdnConSetReqMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_CSID_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddCsidIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_PRIVATE_EXT_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}

#ifdef ANSI
PUBLIC Void  egEgtBuildS11DelPdnConSetRspMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11DelPdnConSetRspMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   TRC2(egEgtBuildS11DelPdnConSetRspMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11DelPdnConSetRspMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_DELPDNCONSETRSP_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_DELPDNCONSETRSP_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11DelPdnConSetRspMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_CAUSE_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddCauseIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_PRIVATE_EXT_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}


#ifdef ANSI
PUBLIC Void  egEgtBuildS11CrtFwdTunReqMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11CrtFwdTunReqMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildS11CrtFwdTunReqMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11CrtFwdTunReqMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_CRTFWDTUNREQ_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_CRTFWDTUNREQ_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11CrtFwdTunReqMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_S103_PDN_FW_INFO_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddS103PdnFwInfoIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_PRIVATE_EXT_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}



#ifdef ANSI
PUBLIC Void  egEgtBuildS11CrtFwdTunRspMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11CrtFwdTunRspMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egEgtBuildS11CrtFwdTunRspMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11CrtFwdTunRspMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_CRTFWDTUNRSP_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_CRTFWDTUNRSP_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11CrtFwdTunRspMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_CAUSE_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddCauseIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_S1U_DATA_FW_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddS1UDatFwIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_PRIVATE_EXT_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}



#ifdef ANSI
PUBLIC Void  egEgtBuildS11DelIndDatFwdTunReqMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11DelIndDatFwdTunReqMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   TRC2(egEgtBuildS11DelIndDatFwdTunReqMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11DelIndDatFwdTunReqMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_DELINDDATFWDTUNREQ_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_DELINDDATFWDTUNREQ_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11DelIndDatFwdTunReqMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_PRIVATE_EXT_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}


#ifdef ANSI
PUBLIC Void  egEgtBuildS11DelIndDatFwdTunRspMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11DelIndDatFwdTunRspMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   TRC2(egEgtBuildS11DelIndDatFwdTunRspMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11DelIndDatFwdTunRspMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_DELINDDATFWDTUNRSP_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_DELINDDATFWDTUNRSP_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11DelIndDatFwdTunRspMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_CAUSE_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddCauseIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_RECOVERY_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddRecoveryIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_PRIVATE_EXT_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}


#ifdef ANSI
PUBLIC Void  egEgtBuildS11RelAccBreReqMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11RelAccBreReqMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   TRC2(egEgtBuildS11RelAccBreReqMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11RelAccBreReqMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_RELACCBREREQ_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_RELACCBREREQ_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11RelAccBreReqMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_PRIVATE_EXT_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}


#ifdef ANSI
PUBLIC Void  egEgtBuildS11RelAccBreRspMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg             **egMsg,
U8                intfType,
Mem               *memInfo
)
#else
PUBLIC Void egEgtBuildS11RelAccBreRspMsg(tcCb, spCb, egMsg, intfType, memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg             **egMsg;
U8                intfType;
Mem               *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo  egLvlInfo;
   LegMsgEntry    *gmEntry= NULLP;
   U16            idx = 0;
   U8             noIEs= FALSE;
   Bool           unknownIe=FALSE;

   TRC2(egEgtBuildS11RelAccBreRspMsg)

   if (EgUtilAllocGmMsg(egMsg,memInfo) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11RelAccBreRspMsg: Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb, spCb, &((*egMsg)->msgHdr), EG_S11_RELACCBRERSP_CMD_CODE);

   /* if no IEs are to be appended, only unknown will be appended */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noIEs",  &noIEs);

   if (!noIEs)
   {
      if ( (gmEntry  = egGetMsgFrmGmDict(EG_S11_RELACCBRERSP_CMD_CODE, intfType)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "egEgtBuildS11RelAccBreRspMsg: Unable to message signature\n"));
         RETVOID;
      }

      for(idx = 0; idx < gmEntry->nmbIeProp; idx++)
      {
         switch(gmEntry->ieProperties[idx].ieType)
         {
            case EG_CAUSE_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddCauseIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_RECOVERY_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddRecoveryIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_PRIVATE_EXT_IETYPE:
            {
               cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
               makeAndAddPvtExtnIe(tcCb, spCb, *egMsg, &egLvlInfo, gmEntry->ieProperties[idx]);
               break;
            } /* end of case */

            default:
            {
               break;
            } /* end of case */
         } /*end of switch  */
      } /* end of for */
   } /* end of if */

   /* Handle the unknown IE here */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownIe", &unknownIe);

   if (unknownIe)
   {
      cmMemset( (U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

      /* Common function which frame message based on instance value */
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }

   RETVOID;
}



#endif /* EGTP_C */
/**********************************************************************

         End of file:     smeg_s11utl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:19:12 2015

**********************************************************************/

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
/main/1      ---      an   1. Initial Release
/main/2      ---      rss               1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla         Initial for eGTP release 2.1
/main/3     eg003.201 psingh            1. Merged code from eg006.102 to Fix TRACE5
                                           macro related issue
/main/3     eg004.201 magnihotri        1.Header files added for eGTPC PSF Upgrade 
*********************************************************************91*/

