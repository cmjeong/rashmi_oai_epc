

/********************************************************************20**

     Name:     X2AP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     cz_ptui.c

     Sid:      tr_ptui.c@@/main/2 - Tue Aug 30 18:36:15 2011

     Prg:      rs

*********************************************************************21*/

/* ---- CZT interface ---- */
/*

the following Matrices define the mapping between the primitives
called by the upper interface of X2AP and the corresponding
primitives of the X2AP service user(s).

The parameter MAXCZUICZT defines the maximum number of service users on
top of X2AP. There is an array of functions per primitive
invoked by X2AP.

The dispatching is performed by the configurable variable: selector.
The selectors are:

   0 - loosely coupled (#define LCRSLICZT)
   1 - application (#define CZ)
   3 - Light weight loosely coupled

*/
/* header include files (.h) --*/
#include "envopt.h"        /* environment options --*/
#include "envdep.h"        /* environment dependent --*/
#include "envind.h"        /* environment independent --*/
#include "gen.h"           /* general --*/
#include "ssi.h"           /* system services --*/
#include "cm5.h"           /* common timer library --*/
#include "cm_hash.h"       /* common hash library --*/
#include "cm_llist.h"      /* common linked list library --*/
#include "cm_inet.h"       /* common socket library --*/
#include "cm_tpt.h"        /* common transport library --*/
#include "cm_tkns.h"       /* common tokens --*/
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "sct.h"           /* SCT interface defines           */
#include "czt.h"           /* CZT interface defines           */
#include "lcz.h"           /* X2AP Layer management           */
#include "cz.h"            /* X2AP layer defines              */
#include "cz_err.h"            /* X2AP layer defines              */


/* header/extern include files (.x) --*/
#include "gen.x"           /* general --*/
#include "ssi.x"           /* system services --*/
#include "cm5.x"           /* common timer library --*/
#include "cm_hash.x"       /* common hash library --*/
#include "cm_llist.x"      /* common linked list library --*/
#include "cm_inet.x"       /* common socket library --*/
#include "cm_mblk.x"       /* common mem alloc defines --*/
#include "cm_tkns.x"       /* common tokens --*/
#include "cm_tpt.x"        /* common transport library --*/
#include "cm_lib.x"
#include "cm_inet.x"       /* Common socket library           */
#include "cm_pasn.x"       /* Common ASn.1 Library           */
#include "sct.x"           /* SCT interface defines           */
#include "czt.x"           /* CZT interface structures        */
#include "lcz.x"           /* X2AP Layer management           */
#include "cz.x"            /* X2AP layer structures           */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !(defined(LCCZUICZT)  && defined(RS) && defined(LWLCCZUICZT))
#ifdef PTCZUICZT
#undef PTCZUICZT
#define PTCZUICZT
#else
#define PTCZUICZT
#endif
#endif


/* MAX Number of Service Users of CZ */
#define CZ_MAX_CZT_USR   3

#ifdef PTCZUICZT

EXTERN S16 PtUiCztBndCfm ARGS((Pst * pst, SuId suId, U8 status));

EXTERN S16 PtUiCztGpInd ARGS((Pst * pst, SuId suId, CztEvnt * gpInd));

EXTERN S16 PtUiCztGpCfm ARGS((Pst * pst, SuId suId, CztEvnt * gpCfm));

EXTERN S16 PtUiCztBmpInd ARGS((Pst * pst, SuId suId, CztEvnt * bmpEvnt));

EXTERN S16 PtUiCztBmpCfm ARGS((Pst * pst, SuId suId, CztEvnt * bmpCfm));

EXTERN S16 PtUiCztGpErrInd ARGS((Pst * pst, SuId suId, CztEvnt * gpErrInd));

EXTERN S16 PtUiCztLclErrorInd ARGS((Pst * pst, SuId suId, CztLclErrInd * cztLclErrInd));

EXTERN S16 PtUiCztRelCfm ARGS((Pst * pst, SuId suId, CztRlsCfm *rlsCfm));

EXTERN S16 PtUiCztStatusInd ARGS((Pst * pst, SuId suId, CztStaInd * cztSta));

EXTERN S16 PtUiCztDynamPeerAssocInd ARGS((Pst * pst, SuId suId, CztPeerAssocInd * peerAssocInd));

EXTERN S16 PtUiCztAudCfm       ARGS((Pst *pst, SuId suId, CztAudEvnt *audEvnt));

#endif /*--#ifdef PTCZUICZT--*/


PRIVATE CONSTANT CztBndCfm CzUiCztBndCfmMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztBndCfm,
#else
   PtUiCztBndCfm,
#endif
#ifdef LWLCCZUICZT
   cmPkCztBndCfm,
#else
   PtUiCztBndCfm,
#endif
#ifdef RS
   RsLiCztBndCfm
#else
   PtUiCztBndCfm
#endif

};


PRIVATE CONSTANT CztGpInd CzUiCztGpIndMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztGpInd,
#else
   PtUiCztGpInd,
#endif
#ifdef LWLCCZUICZT
   cmPkCztGpInd,
#else
   PtUiCztGpInd,
#endif
#ifdef RS
   RsLiCztGpInd
#else
   PtUiCztGpInd
#endif
};


PRIVATE CONSTANT CztGpCfm CzUiCztGpCfmMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztGpCfm,
#else
   PtUiCztGpCfm,
#endif
#ifdef LWLCCZUICZT
   cmPkCztGpCfm,
#else
   PtUiCztGpCfm,
#endif
#ifdef RS
   RsLiCztGpCfm
#else
   PtUiCztGpCfm
#endif
};


PRIVATE CONSTANT CztBmpInd CzUiCztBmpIndMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztBmpInd,
#else
   PtUiCztBmpInd,
#endif
#ifdef LWLCCZUICZT
   cmPkCztBmpInd,
#else
   PtUiCztBmpInd,
#endif
#ifdef RS
   RsLiCztBmpInd
#else
   PtUiCztBmpInd
#endif
};


PRIVATE CONSTANT CztBmpCfm CzUiCztBmpCfmMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztBmpCfm,
#else
   PtUiCztBmpCfm,
#endif
#ifdef LWLCCZUICZT
   cmPkCztBmpCfm,
#else
   PtUiCztBmpCfm,
#endif
#ifdef RS
   RsLiCztBmpCfm
#else
   PtUiCztBmpCfm
#endif
};


PRIVATE CONSTANT CztGpErrInd CzUiCztGpErrIndMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztGpErrInd,
#else
   PtUiCztGpErrInd,
#endif
#ifdef LWLCCZUICZT
   cmPkCztGpErrInd,
#else
   PtUiCztGpErrInd,
#endif
#ifdef RS
   RsLiCztGpErrInd
#else
   PtUiCztGpErrInd
#endif
};


PRIVATE CONSTANT CztLclErrorInd CzUiCztLclErrorIndMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztLclErrorInd,
#else
   PtUiCztLclErrorInd,
#endif
#ifdef LWLCCZUICZT
   cmPkCztLclErrorInd,
#else
   PtUiCztLclErrorInd,
#endif
#ifdef RS
   RsLiCztLclErrorInd
#else
   PtUiCztLclErrorInd
#endif
};


PRIVATE CONSTANT CztRelCfm CzUiCztRelCfmMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztRelCfm,
#else
   PtUiCztRelCfm,
#endif
#ifdef LWLCCZUICZT
   cmPkCztRelCfm,
#else
   PtUiCztRelCfm,
#endif
#ifdef RS
   RsLiCztRelCfm
#else
   PtUiCztRelCfm
#endif
};


PRIVATE CONSTANT CztStatusInd CzUiCztStaIndMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztStatusInd,
#else
   PtUiCztStatusInd,
#endif
#ifdef LWLCCZUICZT
   cmPkCztStatusInd,
#else
   PtUiCztStatusInd,
#endif
#ifdef RS
   RsLiCztStatusInd
#else
   PtUiCztStatusInd
#endif
};


PRIVATE CONSTANT CztDynamPeerAssocInd CzUiCztDynamPeerAssocIndMt[CZ_MAX_CZT_USR] =
{
#ifdef LCCZUICZT
   cmPkCztDynamPeerAssocInd,
#else
   PtUiCztDynamPeerAssocInd,
#endif
#ifdef LWLCCZUICZT
   cmPkCztDynamPeerAssocInd,
#else
   PtUiCztDynamPeerAssocInd,
#endif
#ifdef RS
   RsLiCztDynamPeerAssocInd
#else
   PtUiCztDynamPeerAssocInd
#endif
};

PUBLIC CztAudCfm czUiCztAudCfmMt [] =
{
#ifdef LCCZUICZT
   cmPkCztAudCfm,        /* 0 - loosely coupled */
#else
   PtUiCztAudCfm,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCCZUICZT
   cmPkCztAudCfm,        /* 1 - light weight loosely coupled */
#else
   PtUiCztAudCfm,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef RS
   RsLiCztAudCfm,        /* 2 - tightly coupled, stub layer */
#else
   PtUiCztAudCfm,        /* 2 - tightly coupled, portable */
#endif
};


#ifdef __cplusplus
}
#endif /* __cplusplus */

/* cz001.101 : CR Fixes */

#ifdef CZ


#ifdef ANSI
PUBLIC S16 CzUiCztBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 CzUiCztBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{

   CZ_TRC3(CzUiCztBndCfm)

   (*CzUiCztBndCfmMt[pst->selector])(pst, suId, status);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztGpInd
(
Pst * pst,
SuId suId,
CztEvnt * gpInd
)
#else
PUBLIC S16 CzUiCztGpInd(pst, suId, gpInd)
Pst * pst;
SuId suId;
CztEvnt * gpInd;
#endif
{

   CZ_TRC3(CzUiCztGpInd)

   (*CzUiCztGpIndMt[pst->selector])(pst, suId, gpInd);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztGpCfm
(
Pst * pst,
SuId suId,
CztEvnt * gpCfm
)
#else
PUBLIC S16 CzUiCztGpCfm(pst, suId, gpCfm)
Pst * pst;
SuId suId;
CztEvnt * gpCfm;
#endif
{

   CZ_TRC3(CzUiCztGpCfm)

   (*CzUiCztGpCfmMt[pst->selector])(pst, suId, gpCfm);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztBmpInd
(
Pst * pst,
SuId suId,
CztEvnt * bmpEvnt
)
#else
PUBLIC S16 CzUiCztBmpInd(pst, suId, bmpEvnt)
Pst * pst;
SuId suId;
CztEvnt * bmpEvnt;
#endif
{

   CZ_TRC3(CzUiCztBmpInd)

   (*CzUiCztBmpIndMt[pst->selector])(pst, suId, bmpEvnt);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztBmpCfm
(
Pst * pst,
SuId suId,
CztEvnt * bmpCfm
)
#else
PUBLIC S16 CzUiCztBmpCfm(pst, suId, bmpCfm)
Pst * pst;
SuId suId;
CztEvnt * bmpCfm;
#endif
{

   CZ_TRC3(CzUiCztBmpCfm)

   (*CzUiCztBmpCfmMt[pst->selector])(pst, suId, bmpCfm);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztGpErrInd
(
Pst * pst,
SuId suId,
CztEvnt * gpErrInd
)
#else
PUBLIC S16 CzUiCztGpErrInd(pst, suId, gpErrInd)
Pst * pst;
SuId suId;
CztEvnt * gpErrInd;
#endif
{

   CZ_TRC3(CzUiCztGpErrInd)

   (*CzUiCztGpErrIndMt[pst->selector])(pst, suId, gpErrInd);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztLclErrorInd
(
Pst * pst,
SuId suId,
CztLclErrInd * cztLclErrInd
)
#else
PUBLIC S16 CzUiCztLclErrorInd(pst, suId, cztLclErrInd)
Pst * pst;
SuId suId;
CztLclErrInd * cztLclErrInd;
#endif
{

   CZ_TRC3(CzUiCztLclErrorInd)

   (*CzUiCztLclErrorIndMt[pst->selector])(pst, suId, cztLclErrInd);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztRelCfm
(
Pst * pst,
SuId suId,
CztRlsCfm *rlsCfm
)
#else
PUBLIC S16 CzUiCztRelCfm(pst, suId, rlsCfm)
Pst * pst;
SuId suId;
CztRlsCfm *rlsCfm;
#endif
{

   CZ_TRC3(CzUiCztRelCfm)

   (*CzUiCztRelCfmMt[pst->selector])(pst, suId, rlsCfm);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztStaInd
(
Pst * pst,
SuId suId,
CztStaInd * cztSta
)
#else
PUBLIC S16 CzUiCztStaInd(pst, suId, cztSta)
Pst * pst;
SuId suId;
CztStaInd * cztSta;
#endif
{

   CZ_TRC3(CzUiCztStaInd)

   (*CzUiCztStaIndMt[pst->selector])(pst, suId, cztSta);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 CzUiCztDynamPeerAssocInd
(
Pst * pst,
SuId suId,
CztPeerAssocInd * peerAssocInd
)
#else
PUBLIC S16 CzUiCztDynamPeerAssocInd(pst, suId, peerAssocInd)
Pst * pst;
SuId suId;
CztPeerAssocInd * peerAssocInd;
#endif
{

   CZ_TRC3(CzUiCztDynamPeerAssocInd)

   (*CzUiCztDynamPeerAssocIndMt[pst->selector])(pst, suId, peerAssocInd);

   CZ_RETVALUE(ROK);

}

/*
 *
 *       Fun:   CzUiCztAudCfm
 *
 *       Desc:  This function resolves the SztAudCfm primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cz_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 CzUiCztAudCfm
(
Pst *pst,
SuId suId,
CztAudEvnt *audEvnt
)
#else 
PUBLIC S16 CzUiCztAudCfm (pst, suId, audEvnt)
Pst *pst;
SuId suId;
CztAudEvnt *audEvnt;
#endif
{
   CZ_TRC3(CzUiCztAudCfm)

   (*czUiCztAudCfmMt[pst->selector]) (pst, suId, audEvnt);

   CZ_RETVALUE(ROK);
} /* CzUiCztAudCfm */

#endif /*--ifdef CZ--*/

#ifdef PTCZUICZT
#ifdef ANSI
PUBLIC S16 PtUiCztBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 PtUiCztBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{

   CZ_TRC3(PtUiCztBndCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztGpInd
(
Pst * pst,
SuId suId,
CztEvnt * gpInd
)
#else
PUBLIC S16 PtUiCztGpInd(pst, suId, gpInd)
Pst * pst;
SuId suId;
CztEvnt * gpInd;
#endif
{

   CZ_TRC3(PtUiCztGpInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(gpInd);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztGpCfm
(
Pst * pst,
SuId suId,
CztEvnt * gpCfm
)
#else
PUBLIC S16 PtUiCztGpCfm(pst, suId, gpCfm)
Pst * pst;
SuId suId;
CztEvnt * gpCfm;
#endif
{

   CZ_TRC3(PtUiCztGpCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(gpCfm);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztBmpInd
(
Pst * pst,
SuId suId,
CztEvnt * bmpEvnt
)
#else
PUBLIC S16 PtUiCztBmpInd(pst, suId, bmpEvnt)
Pst * pst;
SuId suId;
CztEvnt * bmpEvnt;
#endif
{

   CZ_TRC3(PtUiCztBmpInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(bmpEvnt);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztBmpCfm
(
Pst * pst,
SuId suId,
CztEvnt * bmpCfm
)
#else
PUBLIC S16 PtUiCztBmpCfm(pst, suId, bmpCfm)
Pst * pst;
SuId suId;
CztEvnt * bmpCfm;
#endif
{

   CZ_TRC3(PtUiCztBmpCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(bmpCfm);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztGpErrInd
(
Pst * pst,
SuId suId,
CztEvnt * gpErrInd
)
#else
PUBLIC S16 PtUiCztGpErrInd(pst, suId, gpErrInd)
Pst * pst;
SuId suId;
CztEvnt * gpErrInd;
#endif
{

   CZ_TRC3(PtUiCztGpErrInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(gpErrInd);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztLclErrorInd
(
Pst * pst,
SuId suId,
CztLclErrInd * cztLclErrInd
)
#else
PUBLIC S16 PtUiCztLclErrorInd(pst, suId, cztLclErrInd)
Pst * pst;
SuId suId;
CztLclErrInd * cztLclErrInd;
#endif
{

   CZ_TRC3(PtUiCztLclErrorInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cztLclErrInd);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztRelCfm
(
Pst * pst,
SuId suId,
CztRlsCfm *rlsCfm
)
#else
PUBLIC S16 PtUiCztRelCfm(pst, suId, rlsCfm)
Pst * pst;
SuId suId;
CztRlsCfm *rlsCfm;
#endif
{

   CZ_TRC3(PtUiCztRelCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(rlsCfm);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztStatusInd
(
Pst * pst,
SuId suId,
CztStaInd * cztSta
)
#else
PUBLIC S16 PtUiCztStatusInd(pst, suId, cztSta)
Pst * pst;
SuId suId;
CztStaInd * cztSta;
#endif
{

   CZ_TRC3(PtUiCztStatusInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cztSta);

   CZ_RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtUiCztDynamPeerAssocInd
(
Pst * pst,
SuId suId,
CztPeerAssocInd * peerAssocInd
)
#else
PUBLIC S16 PtUiCztDynamPeerAssocInd(pst, suId, peerAssocInd)
Pst * pst;
SuId suId;
CztPeerAssocInd * peerAssocInd;
#endif
{

   CZ_TRC3(PtUiCztDynamPeerAssocInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(peerAssocInd);

   CZ_RETVALUE(ROK);

}

/*
 *
 *       Fun:   PtUiCztAudCfm
 *
 *       Desc:  Portable version of CztAudCfm primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  sz_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 PtUiCztAudCfm
(
Pst *pst,
SuId suId,
CztAudEvnt *audEvnt
)
#else 
PUBLIC S16 PtUiCztAudCfm (pst, suId, audEvnt)
Pst *pst;
SuId suId;
CztAudEvnt *audEvnt;
#endif
{
   CZ_TRC3(PtUiCztAudCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(audEvnt);

   CZ_RETVALUE(ROK);

} /* PtUiCztAudCfm */


#endif /*--ifdef PTCZUICZT--*/

/**********************************************************************

         End of file:     tr_ptui.c@@/main/2 - Tue Aug 30 18:36:15 2011

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sy              1. LTE-X2AP Initial Release.
           cz001.101 mm              1. CR Fixes, Memory Leak fixes.
/main/2      ---     pt              1. LTE-X2AP 3.1 release.
*********************************************************************91*/
