
/********************************************************************20**

     Name:     acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    eu_ptli.c

     Sid:      egac_ptedm.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:39 2015

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

#include "leg.h"           /* layer management defines for EGCP */
#include "eg.h"            /* defines and macros for EG */
#include "egt.h"            /* defines and macros for EG */
#include "eg_edm.h"            /* defines and macros for EG */
#include "eg_err.h"        /* EG error defines */
#include "egac_acc.h"        /* defines for EG acceptance tests */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#include "cm_xta.h" 
#include "egac_edm.h"        /* typedefs for EGCP acceptance tests */


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

#include "egt.x"           /* EGT Interface Structures */
#include "leg.x"           /* layer management typedefs for EGCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#include "cm_xta.x" 
#include "eg.x"            /* typedefs for EGCP */
#include "eu.x"            /* typedefs for EGCP */
#include "egac_acc.x"        /* typedefs for EGCP acceptance tests */
#include "egac_edm.x"        /* typedefs for EGCP acceptance tests */
#include "egac_leg.x"
#include "eg_edm.x"        /* typedefs for EGCP acceptance tests */
/* ---- eGTP service user lower interface ---- */
/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000XXX                      eGTP v 1.1
 */


/************************************************************************
                              Prototypes  
************************************************************************/
/*
*
*       Fun:   EuLiEdmGMCfg
*
*       Desc:  Gm Cfg req for the EDM stub
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 EuLiEdmGmCfg
(
EgGmDictCfg *cfg        /* Ie Cfg structure for ieDb */
)
#else
PUBLIC S16 EuLiEdmGmCfg(cfg)
EgGmDictCfg *cfg;        /* Ie Cfg structure for ieDb */
#endif
{
   S16  retVal = ROK;
   CmStatus cfm;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(EuLiEdmGmCfg)
   cmMemset((U8 *)&cfm, 0, sizeof(CmStatus));

   /*************************************************
    ****  Call the Load Db directly               ***
   *************************************************/
   
   if( (retVal = egDbCfgGmDict(cfg->intfType, cfg->nmbMsg, cfg->gmEntry)) != ROK)
   {
      /******************************************************
      * If there is any Config error call the Config        *
      *  Confirm with the respective error                  *
      ******************************************************/ 
      cfm.status = LCM_PRIM_NOK;
      cfm.reason = retVal;
   }
   else
   {
      cfm.status = LCM_PRIM_OK;
      cfm.reason = LCM_REASON_NOT_APPL;
   }
   if(cfg->nmbMsg)
   {
      SPutSBuf(DFLT_REGION, DFLT_POOL, (Data* )cfg->gmEntry, sizeof(LegMsgEntry) * cfg->nmbMsg);
      cfg->gmEntry = NULLP;
   }
   EuLiEdmLmCfm(cfm);
   RETVALUE(ROK); 
   
}

/*
*
*       Fun:   EuLiEdmShutdown
*
*       Desc:  Shutdown Control req for EDM
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 EuLiEdmShutdown
EG_(
U8     intfType   /* Interface to delete the GM DICT */
)
#else
PUBLIC S16 EuLiEdmShutdown(intfType)
U8     intfType;   /* Interface to delete the GM DICT */
#endif
{
   S16  retVal = ROK;
   CmStatus cfm;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(EuLiEdmShutdown)
   cmMemset((U8 *)&cfm, 0, sizeof(CmStatus));

   /*************************************************
    ****  Call the Load Db directly               ***
   *************************************************/
   
   if( (retVal = egDbDropGmDict(intfType)) != ROK)
   {
      /******************************************************
      * If there is any Config error call the Config        *
      *  Confirm with the respective error                  *
      ******************************************************/ 
      cfm.status = LCM_PRIM_NOK;
      cfm.reason = retVal;
   }
   else
   {
      cfm.status = LCM_PRIM_OK;
      cfm.reason = LCM_REASON_NOT_APPL;
   }
   RETVALUE(ROK); 
   
}


/*
*
*       Fun:   EuLiEdmIeCfg
*
*       Desc:  Ie Cfg req for the EDM stub
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 EuLiEdmIeCfg
(
EgIeDictCfg *cfg        /* Ie Cfg structure for ieDb */
)
#else
PUBLIC S16 EuLiEdmIeCfg(cfg)
EgIeDictCfg *cfg;        /* Ie Cfg structure for ieDb */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(EuLiEdmIeCfg)

   /*************************************************
    ****  Call the encode message req directly ******
   *************************************************/
   
   egDbCfgIeDict(cfg->nmbIe, cfg->posIdx, cfg->ieEntry);
   RETVALUE(ROK); 
   
}

/*
*
*       Fun:   EuLiEdmDecPthReq
*
*       Desc:  Calls decodePth for the edm stub
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 EuLiEdmDecPthReq
(
EgEvnt *evntMsg        /* Event structure having the egMsg */
)
#else
PUBLIC S16 EuLiEdmDecPthReq( evntMsg)
EgEvnt *evntMsg;        /* Event structure having the egMsg */
#endif
{
   S16  retVal = ROK;
#ifdef LEG_FILE_LOG
   U16 nmbLines =0;
#endif

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(EuLiEdmDecPthReq)

   /*************************************************
    ****  Call the encode message req directly ******
   *************************************************/
   
   if( (retVal = egDecPthReq( evntMsg)) != ROK)
   {
      if(evntMsg)
      {
         /******************************************************
         * If there is any encoding error call the framing     *
         * of error msg and send the message to the app        *
         ******************************************************/
         if (retVal == EGT_ERR_MSG_UNABLE_TO_COMPLY)
            evntMsg->resultType = EGT_ERR_MSG_UNABLE_TO_COMPLY;

         else if (retVal == EGT_ERR_MSG_INV_VERSION)
         {
            egTptProcessMsg(evntMsg);
            RETVALUE(ROK);
         }
      }
       
      /******************************************************
      * If there is any encoding error call the framing     *
      * of error msg and send the message to the app        *
      ******************************************************/
 
      retVal = egAcSndErrMsgToApp( evntMsg);
   }
   else
   {
#ifdef LEG_FILE_LOG
      EgUtilGmDump(evntMsg->u.egMsg, stdout, &nmbLines);
#else
      EgUtilGmDump(evntMsg->u.egMsg);
#endif /* end of LEG_FILE_LOG */
   }
   RETVALUE(ROK); 
   
}


/*
*
*       Fun:   EuLiEdmDecReq
*
*       Desc:  Calls decode for the edm stub
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 EuLiEdmDecReq
(
EgEvnt *evntMsg        /* Event structure having the egMsg */
)
#else
PUBLIC S16 EuLiEdmDecReq( evntMsg)
EgEvnt *evntMsg;        /* Event structure having the egMsg */
#endif
{
   S16  retVal = ROK;
#ifdef LEG_FILE_LOG
   U16 nmbLines =0;
#endif

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(EuLiEdmDecReq)

   /*************************************************
    ****  Call the encode message req directly ******
   *************************************************/
   
   if( (retVal = egDecMsgReq( evntMsg)) != ROK)
   {
      if(evntMsg)
      {
         /******************************************************
         * If there is any encoding error call the framing     *
         * of error msg and send the message to the app        *
         ******************************************************/
         if (retVal == EGT_ERR_MSG_UNABLE_TO_COMPLY)
            evntMsg->resultType = EGT_ERR_MSG_UNABLE_TO_COMPLY;

         else if (retVal == EGT_ERR_MSG_INV_VERSION)
         {
            egTptProcessMsg(evntMsg);
            RETVALUE(ROK);
         }
      }
       
      retVal = egAcSndErrMsgToApp( evntMsg);
   }
   else
   {
#ifdef LEG_FILE_LOG
      EgUtilGmDump(evntMsg->u.egMsg, stdout, &nmbLines);
#else
      EgUtilGmDump(evntMsg->u.egMsg);
#endif /* end of LEG_FILE_LOG */
   }
   RETVALUE(ROK); 
   
}


/*
*
*       Fun:   EuLiEdmEncPthReq
*
*       Desc:  Calls encode PTH for the edm stub
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 EuLiEdmEncPthReq
(
EgEvnt *evntMsg        /* Event structure having the egMsg */
)
#else
PUBLIC S16 EuLiEdmEncPthReq(evntMsg)
EgEvnt *evntMsg;        /* Event structure having the egMsg */
#endif
{
   S16  retVal = ROK;
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(EuLiEdmEncPthReq)

   /*************************************************
    ****  Call the encode message req directly ******
   *************************************************/
   
   if( (retVal = egEncPthReq( evntMsg)) != ROK)
   {
      /******************************************************
      * If there is any encoding error call the framing     *
      * of error msg and send the message to the app        *
      ******************************************************/
 
      retVal = egAcSndErrMsgToApp(evntMsg);
   }
   RETVALUE(ROK); 
   
}
/*
*
*       Fun:   EuLiEdmEncReq
*
*       Desc:  Calls encode for the edm stub
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eu_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 EuLiEdmEncReq
(
EgEvnt *evntMsg        /* Event structure having the egMsg */
)
#else
PUBLIC S16 EuLiEdmEncReq(evntMsg)
EgEvnt *evntMsg;        /* Event structure having the egMsg */
#endif
{
   S16  retVal = ROK;
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(EuLiEdmEncReq)

   /*************************************************
    ****  Call the encode message req directly ******
   *************************************************/
   
   if( (retVal = egEncMsgReq( evntMsg)) != ROK)
   {
      /******************************************************
      * If there is any encoding error call the framing     *
      * of error msg and send the message to the app        *
      ******************************************************/
 
      retVal = egAcSndErrMsgToApp(evntMsg);
   }
   RETVALUE(ROK); 
   
}


/********************************************************************30**

         End of file:     egac_ptedm.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:39 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3    eg003.201  psingh      1. Merged code from eg006.102 to Fix TRACE5
                                     macro related issue
*********************************************************************91*/
