

/********************************************************************20**

     Name:    PDCP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    pjac_py.c

     Sid:      pjac_py.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:09 2015

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
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_kwu.h"      /* Acceptance defines */
#include "pjac_cpj.h"      /* Acceptance defines */
#include "pjac_pju.h"      /* Acceptance defines */

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

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_kwu.x"      /* Acceptance defines */
#include "pjac_cpj.x"      /* Acceptance defines */
#include "pjac_pju.x"      /* Acceptance defines */

/*
*       Fun:   cmXtaAppPyInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  kwac_py.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppPyInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}/* kwacPyInit */


/*
*
*       Fun:   cmXtaAppPyDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  kwac_py.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppPyDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyDeInit()
#endif
{
   TRC2(cmXtaAppPyDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppPyDeInit(): Shutting down python interpreter\n"));

   RETVALUE(CMXTA_ERR_NONE);
}/* kwacPyDeInit */


/*
*
*       Fun:   cmXtaAppInitQ
*  
*       Desc:  Initializes the cmXta Queue
*              
*       Ret:   CMXTA_ERR_NONE
*              
*       Notes: None
*
*       File:  kwac_py.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppInitQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC S16 cmXtaAppInitQ(msgQ)
CmXtaMsgQ   *msgQ;
#endif
{
   /* kw005.201 removed warning */
   UNUSED(msgQ);
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppInitQ */


/*
*
*       Fun:   cmXtaAppFlushQ
*
*       Desc:  This primitive will flush the cmXta Queue
*              
*       Ret:   Void
*              
*       Notes: None
*
*       File:  kwac_py.c
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppFlushQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC Void cmXtaAppFlushQ(msgQ)
CmXtaMsgQ *msgQ;
#endif
{
   /* kw005.201 removed warning */
   UNUSED(msgQ);
   RETVOID;
} /* cmXtaAppFlushQ */


/*
 *
 *       Fun:    cmXtaAppTCCreate
 *
 *       Desc:   Creates Test Cases
 *
 *       Ret:    CMXTA_ERR_NONE
 *
 *       Notes:  None
 *
 *       File:   kwac_py.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaAppTCCreate
(
CmXtaTCCb         *tcCb
)
#else
PUBLIC S16 cmXtaAppTCCreate(tcCb)
CmXtaTCCb    *tcCb;
#endif
{
#ifdef KW_PDCP   
   U32   numPosTc;
   U32   numNegTc;

   numPosTc = 0;
   numNegTc = 0;
   /************************************************************************
    *                   MEMSET kwAcCb to ZERO
    ***********************************************************************/
   numPosTc =  kwAcCb.directive.numPosTc;
   numNegTc =  kwAcCb.directive.numNegTc;
#endif
   CMXTA_ZERO(&kwAcCb, sizeof(KwAcCb));
#ifdef KW_PDCP
   kwAcCb.directive.numPosTc =  numPosTc;
   kwAcCb.directive.numNegTc =  numNegTc ;
#endif

   /* Initialize KWUCB Queue for ENTNH and ENTPJ */
   pjAcUtlKwuDatReqCQMakeNull(&(kwAcCb.pjKwuCb.datReq));

   /* Initialize CPJCB Queue */
   pjAcUtlCpjCQMakeNull(&(kwAcCb.nhCpjCb.cfgReq));

   /* Initialize PJUCB Queue */
   pjAcUtlPjuDatReqCQMakeNull(&(kwAcCb.nhPjuCb.datReq));
   pjAcUtlPjuDatReqCQMakeNull(&(kwAcCb.pxPjuCb.datReq));

   UNUSED(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppTCCreate() */


/*
*
*       Fun:   cmXtaAppTCDelete
*
*       Desc:  This function deletes an existing test case
*
*       Ret:   If success, return CMXTA_ERR_NONE
*              If failure, return error Code
*
*       Notes: None
*
*       File:  kwac_py.c
*
*/
#ifdef ANSI
PUBLIC S16  cmXtaAppTCDelete
(
CmXtaTCCb         *tcCb       /* Test Case Control Block */
)
#else
PUBLIC S16  cmXtaAppTCDelete (tcCb)
CmXtaTCCb      *tcCb;         /* Test Case Control Block */
#endif
{
   /* kw005.201 removed warning */
   UNUSED(tcCb);
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTCDelete */


/********************************************************************30**

         End of file:     pjac_py.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:09 2015

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
/main/2      ---      vb        1. LTE PDCP Release 2.1.
*********************************************************************91*/
