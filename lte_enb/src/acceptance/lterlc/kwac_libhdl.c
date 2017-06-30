

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_pjuhdl.c

     Sid:      kwac_libhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:29 2014

     Prg:     cp
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
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_lib.h"      /* PJU Acceptance defines */
#include "kwac_acc.h"      /* Acceptance defines */

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
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"
/*#include "kw_pj_lib.x"      LIB */

#include "cm_xta.x"
#include "kwac_lib.x"      /* PJU Acceptance defines */
#include "kwac_acc.x"      /* Acceptance defines */

#ifdef KW_PDCP



/*
*
*       Fun:   kwAcLibHdlDirective
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
PUBLIC S16 kwAcLibHdlDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcLibHdlDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   TRC2(kwAcLibHdlDirective)


#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlDirective(): tcCb (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlDirective(): tcCb (%d)\n", tcCb->tcId));
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
}/* kwAcLibHdlDirective */



#ifdef PJ_SEC_ASYNC

/**
@brief Call handler for command Output of Integrity Protection
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcLibHdlIntProtOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcLibHdlIntProtOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   TRC2(kwAcLibHdlIntProtOut);

   id =  1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlIntProtOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlIntProtOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   kwAcLibUtlGetOutEnt(&libCb.intCb.intOutList, id, &ent);

   /* kwAcUtlObdIntProt(&pst, suId, spId); */
   cmPkLibObdIntProtCfm(&ent->pst, ent->fd, ent->libTrans, ent->macIStatus);

   /* Get the buffer from the queue */
   kwAcLibUtlDelOutEnt(&libCb.intCb.intOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcLibHdlIntProtOut */


/**
@brief Call handler for command Output of Integrity Verification
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcLibHdlIntVerOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcLibHdlIntVerOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   TRC2(kwAcLibHdlIntVerOut);

   id =  1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlIntVerOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlIntVerOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   kwAcLibUtlGetOutEnt(&libCb.intCb.intOutList, id, &ent);

   cmPkLibObdIntVerCfm(&ent->pst, ent->fd, ent->libTrans, ent->macIStatus);

   /* Get the buffer from the queue */
   kwAcLibUtlDelOutEnt(&libCb.intCb.intOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcLibHdlIntVerOut */


/**
@brief Call handler for command Output of Ciphering
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcLibHdlCipherOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcLibHdlCipherOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   TRC2(kwAcLibHdlCipherOut);

   id =  1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlCipherOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlCipherOut(), tcId (%d)\n", tcCb->tcId));
#endif 
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   kwAcLibUtlGetOutEnt(&libCb.cipCb.cipOutList, id, &ent);

   /* kwAcUtlObdIntProt(&pst, suId, spId); */
   cmPkLibObdCipherCfm(&ent->pst, ent->fd, ent->libTrans, ent->mBuf);

   /* Get the buffer from the queue */
   kwAcLibUtlDelOutEnt(&libCb.cipCb.cipOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcLibHdlCipherOut */


/**
@brief Call handler for command Output of Deciphering
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcLibHdlDecipherOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcLibHdlDecipherOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent = NULLP;
   Bool  errorMsg = FALSE;
   Bool  dropMsg  = FALSE;

   id =  1;

   TRC2(kwAcLibHdlDecipherOut);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlDecipherOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlDecipherOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "errorMsg",  &(errorMsg));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "dropMsg",  &(dropMsg));

   /* Get the buffer from the queue */
   kwAcLibUtlGetOutEnt(&libCb.cipCb.cipOutList, id, &ent);

   if(!dropMsg)
   {
      if(!errorMsg)
         cmPkLibObdDecipherCfm(&ent->pst, ent->fd, ent->libTrans, ent->mBuf);
      else
         cmPkLibObdDecipherCfm(&ent->pst, ent->fd, ent->libTrans, NULLP);
   }

   /* Get the buffer from the queue */
   kwAcLibUtlDelOutEnt(&libCb.cipCb.cipOutList, ent);

   kwAcCb.tcCb = tcCb;
   kwAcCb.spCb = spCb;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcLibHdlDecipherOut */

#endif /* PJ_SEC_ASYNC */


#ifdef PJ_CMP_ASYNC
/**
@brief Call handler for command Output of Compressor
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcLibHdlCompOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcLibHdlCompOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   TRC2(kwAcLibHdlCompOut);

   id =  1;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlCompOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlCompOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   kwAcLibUtlGetOutEnt(&libCb.compCb.compOutList, id, &ent);

   /* kwAcUtlObdIntProt(&pst, suId, spId); */
   cmPkLibObdCmpCfm(&ent->pst, ent->fd, ent->libTrans, ent->mBuf);

   /* Get the buffer from the queue */
   kwAcLibUtlDelOutEnt(&libCb.compCb.compOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcLibHdlCompOut */


/**
@brief Call handler for command Output of Decompressor
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcLibHdlDecmpOut
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcLibHdlDecmpOut(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32          id;
   KwAcLibOutEnt *ent;

   id =  1;

   TRC2(kwAcLibHdlDecmpOut);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlDecmpOut(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcLibHdlDecmpOut(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "id",  &(id));

   /* Get the buffer from the queue */
   kwAcLibUtlGetOutEnt(&libCb.compCb.compOutList, id, &ent);

   /* kwAcUtlObdIntProt(&pst, suId, spId); */
   cmPkLibObdDecmpCfm(&ent->pst, ent->fd, ent->libTrans, ent->mBuf, NULLP);

   /* Get the buffer from the queue */
   kwAcLibUtlDelOutEnt(&libCb.compCb.compOutList, ent);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcLibHdlDecmpOut */

#endif /* PJ_CMP_ASYNC */
#endif /* KW_PDCP */


/********************************************************************30**

         End of file:     kwac_libhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:29 2014

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
/main/1      ---   gk         1. Initial Release.
*********************************************************************91*/

