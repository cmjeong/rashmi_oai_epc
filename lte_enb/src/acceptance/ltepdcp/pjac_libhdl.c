

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_pjuhdl.c

     Sid:      pjac_libhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:55 2015

     Prg:     Adarsh
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
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_lib.h"      /* PJU Acceptance defines */
#include "pjac_acc.h"      /* Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "pj_lib.x"     /* LIB */

#include "cm_xta.x"
#include "pjac_lib.x"      /* PJU Acceptance defines */
#include "pjac_acc.x"      /* Acceptance defines */


/*
*
*       Fun:   pjAcLibHdlDirective
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_libcb.c
*
*/
#ifdef ANSI
PUBLIC S16 pjAcLibHdlDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcLibHdlDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   TRC2(pjAcLibHdlDirective)


#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlDirective(): tcCb (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlDirective(): tcCb (%d)\n", tcCb->tcId));
#endif


   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U32, "id",            &kwAcCb.directive.id);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "feedback",     &kwAcCb.directive.feedback);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "seqStart",     &kwAcCb.directive.seqStart);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "seqOn",        &kwAcCb.directive.seqOn);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "cmpInitFail",  &kwAcCb.directive.cmpInitFail);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "intInitFail",  &kwAcCb.directive.intInitFail);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "cmpFail",      &kwAcCb.directive.cmpFail);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "intProtFail",  &kwAcCb.directive.intProtFail);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "cipFail",      &kwAcCb.directive.cipFail);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "decmpFail",    &kwAcCb.directive.decmpFail);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "intVerFail",   &kwAcCb.directive.intVerFail);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "decipFail",    &kwAcCb.directive.decipFail);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "saveCmpMsg",   &kwAcCb.directive.saveCmpMsg);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "saveIntMsg",   &kwAcCb.directive.saveIntMsg);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "saveCpMsg",    &kwAcCb.directive.saveCpMsg);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "saveDecmpMsg", &kwAcCb.directive.saveDecmpMsg);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "saveIntVerMsg",&kwAcCb.directive.saveIntVerMsg);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "saveDecpMsg",  &kwAcCb.directive.saveDecpMsg);


   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcLibHdlDirective */



#ifdef PJ_SEC_ASYNC

/**
@brief Call handler for command Output of Integrity Protection
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcLibHdlIntProtOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcLibHdlIntProtOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   TRC2(pjAcLibHdlIntProtOut);

   id =  1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlIntProtOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlIntProtOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   pjAcLibUtlGetOutEnt(&libCb.intCb.intOutList, id, &ent);

   /* pjAcUtlObdIntProt(&pst, suId, spId); */
   cmPkLibObdIntProtCfm(&ent->pst, ent->fd, ent->libTrans, ent->macIStatus);

   /* Get the buffer from the queue */
   pjAcLibUtlDelOutEnt(&libCb.intCb.intOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcLibHdlIntProtOut */


/**
@brief Call handler for command Output of Integrity Verification
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcLibHdlIntVerOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcLibHdlIntVerOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   TRC2(pjAcLibHdlIntVerOut);

   id =  1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlIntVerOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlIntVerOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   pjAcLibUtlGetOutEnt(&libCb.intCb.intOutList, id, &ent);

   cmPkLibObdIntVerCfm(&ent->pst, ent->fd, ent->libTrans, ent->macIStatus);

   /* Get the buffer from the queue */
   pjAcLibUtlDelOutEnt(&libCb.intCb.intOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcLibHdlIntVerOut */


/**
@brief Call handler for command Output of Ciphering
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcLibHdlCipherOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcLibHdlCipherOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   TRC2(pjAcLibHdlCipherOut);

   id =  1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlCipherOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlCipherOut(), tcId (%d)\n", tcCb->tcId));
#endif 
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   pjAcLibUtlGetOutEnt(&libCb.cipCb.cipOutList, id, &ent);

   /* pjAcUtlObdIntProt(&pst, suId, spId); */
   cmPkLibObdCipherCfm(&ent->pst, ent->fd, ent->libTrans, ent->mBuf);

   /* Get the buffer from the queue */
   pjAcLibUtlDelOutEnt(&libCb.cipCb.cipOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcLibHdlCipherOut */


/**
@brief Call handler for command Output of Deciphering
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcLibHdlDecipherOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcLibHdlDecipherOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent = NULLP;
   Bool  errorMsg = FALSE;
   Bool  dropMsg  = FALSE;

   id =  1;

   TRC2(pjAcLibHdlDecipherOut);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlDecipherOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlDecipherOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "errorMsg",  &(errorMsg));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "dropMsg",  &(dropMsg));

   /* Get the buffer from the queue */
   pjAcLibUtlGetOutEnt(&libCb.cipCb.cipOutList, id, &ent);

   if(!dropMsg)
   {
      if(!errorMsg)
         cmPkLibObdDecipherCfm(&ent->pst, ent->fd, ent->libTrans, ent->mBuf);
      else
         cmPkLibObdDecipherCfm(&ent->pst, ent->fd, ent->libTrans, NULLP);
   }

   /* Get the buffer from the queue */
   pjAcLibUtlDelOutEnt(&libCb.cipCb.cipOutList, ent);

   kwAcCb.tcCb = tcCb;
   kwAcCb.spCb = spCb;

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcLibHdlDecipherOut */

#endif /* PJ_SEC_ASYNC */


#ifdef PJ_CMP_ASYNC
/**
@brief Call handler for command Output of Compressor
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcLibHdlCompOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcLibHdlCompOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   TRC2(pjAcLibHdlCompOut);

   id =  1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlCompOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlCompOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   pjAcLibUtlGetOutEnt(&libCb.compCb.compOutList, id, &ent);

   /* pjAcUtlObdIntProt(&pst, suId, spId); */
   cmPkLibObdCmpCfm(&ent->pst, ent->fd, ent->libTrans, ent->mBuf);

   /* Get the buffer from the queue */
   pjAcLibUtlDelOutEnt(&libCb.compCb.compOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcLibHdlCompOut */


/**
@brief Call handler for command Output of Decompressor
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcLibHdlDecmpOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcLibHdlDecmpOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   id =  1;

   TRC2(pjAcLibHdlDecmpOut);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlDecmpOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcLibHdlDecmpOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   pjAcLibUtlGetOutEnt(&libCb.compCb.compOutList, id, &ent);

   /* pjAcUtlObdIntProt(&pst, suId, spId); */
   cmPkLibObdDecmpCfm(&ent->pst, ent->fd, ent->libTrans, ent->mBuf, NULLP);

   /* Get the buffer from the queue */
   pjAcLibUtlDelOutEnt(&libCb.compCb.compOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcLibHdlDecmpOut */

#endif /* PJ_CMP_ASYNC */

/********************************************************************30**

         End of file:     pjac_libhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:55 2015

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
/main/1      ---       vb         1. LTE PDCP Initial Release 2.1
*********************************************************************91*/
