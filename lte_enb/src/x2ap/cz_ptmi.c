
 
/********************************************************************20**
  
     Name:     X2AP - Management Interface
  
     Type:     C source file
  
     Desc:     C source code for the management interface primitives of
               X2AP
 
     File:     cz_ptmi.c
  
     Sid:      tr_ptmi.c@@/main/2 - Tue Aug 30 18:36:14 2011
  
     Prg:      sy
  
*********************************************************************21*/
  
/*
  
Layer management provides the necessary functions to control and
monitor the condition of each protocol layer.
 
The following functions are provided in this file:

     CzMiLczStaInd      Status Indication
     CzMiLczStaCfm      Status Confirm
     CzMiLczStsCfm      Statistics Confirm
     CzMiLczTrcInd      Trace Indication
     CzMiLczCfgCfm      Configure confirm 
     CzMiLczCntrlCfm    Control confirm 
 
It is assumed that the following functions are provided in the
X2AP protocol file:
  
     CzMiLczCfgReq      Configure Request
     CzMiLczStaReq      Status Request
     CzMiLczStsReq      Statistics Request
     CzMiLczCntrlReq    Control Request
 
*/
  
/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000361     X2AP
*
*/
 
/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "sct.h"           /* SCT interface defines           */
#include "czt.h"           /* CZT interface defines           */
#include "lcz.h"           /* X2AP Layer management           */
#include "cz.h"            /* X2AP layer defines              */
#include "cz_err.h"        /* X2AP - error */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_inet.x"       /* Common socket library           */
#include "cm_pasn.x"       /* Common ASn.1 Library           */
#include "sct.x"           /* SCT interface defines           */
#include "czt.x"           /* CZT interface structures        */
#include "lcz.x"           /* X2AP Layer management           */
#include "cz.x"            /* X2AP layer structures           */



/* local typedefs */
  
/* local externs */
  
/* forward references */
 
#if !(defined(LCCZMILCZ)  && defined(SM) && defined(LWLCCZMILCZ))
#define PTCZMILCZ
#endif


/* MAX Number of Service Users of CZ */
#define CZ_MAX_LCZ_USR   3
#ifdef __cplusplus
extern "C" {
#endif


#ifdef PTCZMILCZ
/** @brief This API is used to send a 
Config Cfm from X2AP to LM.*/
EXTERN S16 PtMiLczCfgCfm ARGS((Pst * pst, CzMngmt * cfm));
/** @brief This API is used to send a 
statistics Confirm from X2AP to LM.*/
EXTERN S16 PtMiLczStsCfm ARGS((Pst * pst, CzMngmt * cfm));
/** @brief This API is used to send a 
status Confirm from X2AP to LM.*/
EXTERN S16 PtMiLczStaCfm ARGS((Pst * pst, CzMngmt * cfm));
/** @brief This API is used to send a 
status Indication from X2AP to LM.*/
EXTERN S16 PtMiLczStaInd ARGS((Pst * pst, CzMngmt * usta));
/** @brief This API is used to send a 
control Confirm from X2AP to LM.*/
EXTERN S16 PtMiLczCntrlCfm ARGS((Pst * pst, CzMngmt * cfm));
/** @brief This API is used to send a 
trace Indication from X2AP to LM.*/
EXTERN S16 PtMiLczTrcInd ARGS((Pst * pst, CzMngmt * trc, Buffer * trcBuf));
#endif /*--#ifdef PTCZMILCZ--*/

#ifdef __cplusplus
}
#endif

/* functions in other modules */
  
/* public variable declarations */
  
/* private variable declarations */
 
/* cz001.101 : CR Fixes */
/*

   The following matrices define the mapping between the primitives 
   called by the layer management interface of X2AP and the 
   corresnonding primitives of the X2AP service user.
 
   The parameter MAXCZMI defines the maximum number of service users on
   top of X2AP. There is an array of functions per primitive invoked by 
   X2AP. Every array is MAXCZMI long (i.e. there are as many functions 
   as the number of service users).
 
   The disnatching is performed by the configurable variable: selector.
   The selector is configured during genECZl configuration.
 
   The selectors are:
 
   0 - loosely coupled - forawrd compatibility (#define LCCZMILCZ)
   1 - Tightly Coupled  (#define SM)
*/

/** @brief This API is used to send a 
Config Cfm from X2AP to LM.*/
PRIVATE CONSTANT LczCfgCfm CzMiLczCfgCfmMt[CZ_MAX_LCZ_USR] =
{
#ifdef LCCZMILCZ
   cmPkLczCfgCfm,
#else
   PtMiLczCfgCfm,
#endif
#ifdef SM
   SmMiLczCfgCfm,
#else
   PtMiLczCfgCfm,
#endif
#ifdef LWLCCZMILCZ
   cmPkLczCfgCfm
#else
   PtMiLczCfgCfm
#endif
};

/** @brief This API is used to send a 
statistics Confirm from X2AP to LM.*/
PRIVATE CONSTANT LczStsCfm CzMiLczStsCfmMt[CZ_MAX_LCZ_USR] =
{
#ifdef LCCZMILCZ
   cmPkLczStsCfm,
#else
   PtMiLczStsCfm,
#endif
#ifdef SM
   SmMiLczStsCfm,
#else
   PtMiLczStsCfm,
#endif
#ifdef LWLCCZMILCZ
   cmPkLczStsCfm
#else
   PtMiLczStsCfm
#endif
};

/** @brief This API is used to send a 
status Confirm from X2AP to LM.*/
PRIVATE CONSTANT LczStaCfm CzMiLczStaCfmMt[CZ_MAX_LCZ_USR] =
{
#ifdef LCCZMILCZ
   cmPkLczStaCfm,
#else
   PtMiLczStaCfm,
#endif
#ifdef SM
   SmMiLczStaCfm,
#else
   PtMiLczStaCfm,
#endif
#ifdef LWLCCZMILCZ
   cmPkLczStaCfm
#else
   PtMiLczStaCfm
#endif
};

/** @brief This API is used to send a 
status Indication from X2AP to LM.*/
PRIVATE CONSTANT LczStaInd CzMiLczStaIndMt[CZ_MAX_LCZ_USR] =
{
#ifdef LCCZMILCZ
   cmPkLczStaInd,
#else
   PtMiLczStaInd,
#endif
#ifdef SM
   SmMiLczStaInd,
#else
   PtMiLczStaInd,
#endif
#ifdef LWLCCZMILCZ
   cmPkLczStaInd
#else
   PtMiLczStaInd
#endif
};

/** @brief This API is used to send a 
control Confirm from X2AP to LM.*/
PRIVATE CONSTANT LczCntrlCfm CzMiLczCntrlCfmMt[CZ_MAX_LCZ_USR] =
{
#ifdef LCCZMILCZ
   cmPkLczCntrlCfm,
#else
   PtMiLczCntrlCfm,
#endif
#ifdef SM
   SmMiLczCntrlCfm,
#else
   PtMiLczCntrlCfm,
#endif
#ifdef LWLCCZMILCZ
   cmPkLczCntrlCfm
#else
   PtMiLczCntrlCfm
#endif
};

/** @brief This API is used to send a 
trace Indication from X2AP to LM.*/
PRIVATE CONSTANT LczTrcInd CzMiLczTrcIndMt[CZ_MAX_LCZ_USR] =
{
#ifdef LCCZMILCZ
   cmPkLczTrcInd,
#else
   PtMiLczTrcInd,
#endif
#ifdef SM
   SmMiLczTrcInd,
#else
   PtMiLczTrcInd,
#endif
#ifdef LWLCCZMILCZ
   cmPkLczTrcInd
#else
   PtMiLczTrcInd
#endif
};


#ifdef CZ



/**
* @brief This API is used to send a 
Config Cfm from X2AP to LM.
*
* @details
*
*     Function : CzMiLczCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 CzMiLczCfgCfm
(
Pst * pst,
CzMngmt * cfm
)
#else
PUBLIC S16 CzMiLczCfgCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif
{

   CZ_TRC3(CzMiLczCfgCfm)

   (*CzMiLczCfgCfmMt[pst->selector])(pst, cfm);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
statistics Confirm from X2AP to LM.
*
* @details
*
*     Function : CzMiLczStsCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   Action  action
*  @param[in]   CzMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 CzMiLczStsCfm
(
Pst * pst,
CzMngmt *cfm
)
#else
PUBLIC S16 CzMiLczStsCfm(pst, cfm)
Pst * pst;
CzMngmt *cfm;
#endif
{

   CZ_TRC3(CzMiLczStsCfm)

   (*CzMiLczStsCfmMt[pst->selector])(pst,cfm);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
status Confirm from X2AP to LM.
*
* @details
*
*     Function : CzMiLczStaCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 CzMiLczStaCfm
(
Pst * pst,
CzMngmt * cfm
)
#else
PUBLIC S16 CzMiLczStaCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif
{

   CZ_TRC3(CzMiLczStaCfm)

   (*CzMiLczStaCfmMt[pst->selector])(pst, cfm);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
status Indication from X2AP to LM.
*
* @details
*
*     Function : CzMiLczStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 CzMiLczStaInd
(
Pst * pst,
CzMngmt * usta
)
#else
PUBLIC S16 CzMiLczStaInd(pst, usta)
Pst * pst;
CzMngmt * usta;
#endif
{

   CZ_TRC3(CzMiLczStaInd)

   (*CzMiLczStaIndMt[pst->selector])(pst, usta);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
control Confirm from X2AP to LM.
*
* @details
*
*     Function : CzMiLczCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 CzMiLczCntrlCfm
(
Pst * pst,
CzMngmt * cfm
)
#else
PUBLIC S16 CzMiLczCntrlCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif
{

   CZ_TRC3(CzMiLczCntrlCfm)

   (*CzMiLczCntrlCfmMt[pst->selector])(pst, cfm);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
trace Indication from X2AP to LM.
*
* @details
*
*     Function : CzMiLczTrcInd
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  trc
*  @param[in]   Buffer *  trcBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 CzMiLczTrcInd
(
Pst * pst,
CzMngmt * trc,
Buffer * trcBuf
)
#else
PUBLIC S16 CzMiLczTrcInd(pst, trc, trcBuf)
Pst * pst;
CzMngmt * trc;
Buffer * trcBuf;
#endif
{

   CZ_TRC3(CzMiLczTrcInd)

   (*CzMiLczTrcIndMt[pst->selector])(pst, trc, trcBuf);

   CZ_RETVALUE(ROK);

}


#endif /*--ifdef CZ--*/

#ifdef PTCZMILCZ



/**
* @brief This API is used to send a 
Config Cfm from X2AP to LM.
*
* @details
*
*     Function : PtMiLczCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczCfgCfm
(
Pst * pst,
CzMngmt * cfm
)
#else
PUBLIC S16 PtMiLczCfgCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif
{

   CZ_TRC3(PtMiLczCfgCfm)

   UNUSED(pst);
   UNUSED(cfm);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
statistics Confirm from X2AP to LM.
*
* @details
*
*     Function : PtMiLczStsCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczStsCfm
(
Pst * pst,
CzMngmt * cfm
)
#else
PUBLIC S16 PtMiLczStsCfm(pst,  cfm)
Pst * pst;
CzMngmt * cfm;
#endif
{

   CZ_TRC3(PtMiLczStsCfm)

   UNUSED(pst);
   UNUSED(cfm);

   CZ_RETVALUE(ROK);
}



/**
* @brief This API is used to send a 
status Confirm from X2AP to LM.
*
* @details
*
*     Function : PtMiLczStaCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczStaCfm
(
Pst * pst,
CzMngmt * cfm
)
#else
PUBLIC S16 PtMiLczStaCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif
{

   CZ_TRC3(PtMiLczStaCfm)

   UNUSED(pst);
   UNUSED(cfm);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
status Indication from X2AP to LM.
*
* @details
*
*     Function : PtMiLczStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczStaInd
(
Pst * pst,
CzMngmt * usta
)
#else
PUBLIC S16 PtMiLczStaInd(pst, usta)
Pst * pst;
CzMngmt * usta;
#endif
{

   CZ_TRC3(PtMiLczStaInd)

   UNUSED(pst);
   UNUSED(usta);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
control Confirm from X2AP to LM.
*
* @details
*
*     Function : PtMiLczCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczCntrlCfm
(
Pst * pst,
CzMngmt * cfm
)
#else
PUBLIC S16 PtMiLczCntrlCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif
{

   CZ_TRC3(PtMiLczCntrlCfm)

   UNUSED(pst);
   UNUSED(cfm);

   CZ_RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
trace Indication from X2AP to LM.
*
* @details
*
*     Function : PtMiLczTrcInd
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  trc
*  @param[in]   Buffer *  trcBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczTrcInd
(
Pst * pst,
CzMngmt * trc,
Buffer * trcBuf
)
#else
PUBLIC S16 PtMiLczTrcInd(pst, trc, trcBuf)
Pst * pst;
CzMngmt * trc;
Buffer * trcBuf;
#endif
{

   CZ_TRC3(PtMiLczTrcInd)

   UNUSED(pst);
   UNUSED(trc);
   UNUSED(trcBuf);

   CZ_RETVALUE(ROK);

}
#endif /*--ifdef PTCZMILCZ--*/

/**********************************************************************

         End of file:     tr_ptmi.c@@/main/2 - Tue Aug 30 18:36:14 2011

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---        sy              1. LTE-X2AP Initial Release.
            cz001.101   mm              1. CR Fixes, Memory Leak fixes.
/main/2      ---        pt              1. LTE-X2AP 3.1 release.
*********************************************************************91*/
