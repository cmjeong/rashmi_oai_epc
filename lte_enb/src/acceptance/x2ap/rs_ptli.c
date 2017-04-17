
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_lczhdl.c

     Sid:      rs_ptli.c@@/main/2 - Tue Aug 30 18:36:07 2011

     Prg:     sy 
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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* layer management defines for CZCP */
#include "cz.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for CZ acceptance tests */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "../../sctp/sb_mtu.h"
#include "../../sctp/sb.h"
#endif    /* SB */

#include "cm_xta.h" 


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
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czt_asn.x"           /* CZT Interface Structures */
#include "czt.x"           /* CZT Interface Structures */
#include "lcz.x"           /* layer management typedefs for CZCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "../../sctp/sb_mtu.x"
#include "../../sctp/sb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for CZCP */
#include "rs.x"            /* typedefs for CZCP */
#include "czac_acc.x"        /* typedefs for CZCP acceptance tests */
#include "czac_lcz.x"
/* ---- X2AP service user lower interface ---- */
/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000XXX                      X2AP v 1.1
 */

/* cz001.101 : CR Fixes */

/************************************************************************
                              Prototypes  
************************************************************************/
#if (!defined(LWLCRSLICZT) || !defined(LCRSLICZT))
#define PTRSLICZT
#else
#ifndef CZ
#define PTRSLICZT
#else
#endif
#endif

#ifdef PTRSLICZT

PRIVATE S16 PtLiCztBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
PRIVATE S16 PtLiCztUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
PRIVATE S16 PtLiCztGpReq       ARGS((Pst *pst, SpId spId, CztEvnt *cztEvnt));
PRIVATE S16 PtLiCztRelReq       ARGS((Pst *pst, SpId spId, CztRlsReq *cztRlsReq));
PRIVATE S16 PtLiCztGpRsp       ARGS((Pst *pst, SpId spId, CztEvnt *conRsp));
PRIVATE S16 PtLiCztGpErrReq    ARGS((Pst *pst, SpId spId, CztEvnt *cztEvnt));
PRIVATE S16 PtLiCztBmpReq       ARGS((Pst *pst, SpId spId, CztEvnt *cztEvnt));
PRIVATE S16 PtLiCztBmpRsp       ARGS((Pst *pst, SpId spId, CztEvnt *cztEvnt));
PRIVATE S16 PtLiCztPeerAssocRsp ARGS((Pst *pst, SpId spId, CztPeerAssocRsp *peerAssocRsp));
PRIVATE S16 PtLiCztGpRetxReq    ARGS((Pst *pst, SpId spId, CztReTxInfo *retxInfo));
PRIVATE S16 PtLiCztAudReq       ARGS((Pst *pst, SpId spId, CztAudEvnt  *audEvnt));


#endif


/* Following matrices define the mapping between the primitives called by the
 * X2AP user (as RsLiCztXXXReq) and the corresponding primitives of the 
 * X2AP layer (service provider) (as CzUiCztXXXReq).
 * The mapping is based on pst->selector.
 * Selector          #define     Coupling      Primitive
 * 0 (SEL_LC_NEW)   LCRSLICZT    loose         cmPkCztXXXReq
 * 1                 CZ          tight         CzUiCztXXXReq
 * 2                LWLCRSLICZT  LW loose      cmPkCztXXXReq
 */


PUBLIC CztBndReq RsLiCztBndReqMt [] =
{
#ifdef LCRSLICZT
   cmPkCztBndReq,        /* 0 - loosely coupled */
#else
   PtLiCztBndReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztBndReq,        /* 1 - light weight loosely coupled */
#else
   PtLiCztBndReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztBndReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztBndReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC CztUbndReq RsLiCztUbndReqMt [] =
{
#ifdef LCRSLICZT
   cmPkCztUbndReq,        /* 0 - loosely coupled */
#else
   PtLiCztUbndReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztUbndReq,        /* 1 - light weight loosely coupled */
#else
   PtLiCztUbndReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztUbndReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztUbndReq,        /* 2 - tightly coupled, portable */
#endif
};



PUBLIC CztGpReq RsLiCztGpReqMt [] =
{
#ifdef LCRSLICZT
   cmPkCztGpReq,        /* 0 - loosely coupled */
#else
   PtLiCztGpReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztGpReq,        /* 1 - light weight loosely coupled */
#else
   PtLiCztGpReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztGpReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztGpReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC CztGpRsp RsLiCztGpRspMt [] =
{
#ifdef LCRSLICZT
   cmPkCztGpRsp,        /* 0 - loosely coupled */
#else
   PtLiCztGpRsp,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztGpRsp,        /* 1 - light weight loosely coupled */
#else
   PtLiCztGpRsp,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztGpRsp,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztGpRsp,        /* 2 - tightly coupled, portable */
#endif
};

PUBLIC CztGpErrReq RsLiCztGpErrReqMt [] =
{
#ifdef LCRSLICZT
   cmPkCztGpErrReq,        /* 0 - loosely coupled */
#else
   PtLiCztGpErrReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztGpErrReq,        /* 1 - light weight loosely coupled */
#else
   PtLiCztGpErrReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztGpErrReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztGpErrReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC CztGpRetxReq RsLiCztGpRetxReqMt [] =
{
#ifdef LCRSLICZT
   cmPkCztGpRetxReq,        /* 0 - loosely coupled */
#else
   PtLiCztGpRetxReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztGpRetxReq,        /* 1 - light weight loosely coupled */
#else
   PtLiCztGpRetxReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztGpRetxReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztGpRetxReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC CztRelReq RsLiCztRelReqMt [] =
{
#ifdef LCRSLICZT
   cmPkCztRelReq,        /* 0 - loosely coupled */
#else
   PtLiCztRelReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztRelReq,        /* 1 - light weight loosely coupled */
#else
   PtLiCztRelReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztRelReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztRelReq,        /* 2 - tightly coupled, portable */
#endif
};




PUBLIC CztBmpReq RsLiCztBmpReqMt [] =
{
#ifdef LCRSLICZT
   cmPkCztBmpReq,        /* 0 - loosely coupled */
#else
   PtLiCztBmpReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztBmpReq,        /* 1 - light weight loosely coupled */
#else
   PtLiCztBmpReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztBmpReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztBmpReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC CztBmpRsp RsLiCztBmpRspMt [] =
{
#ifdef LCRSLICZT
   cmPkCztBmpRsp,        /* 0 - loosely coupled */
#else
   PtLiCztBmpRsp,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztBmpRsp,        /* 1 - light weight loosely coupled */
#else
   PtLiCztBmpRsp,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztBmpRsp,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztBmpRsp,        /* 2 - tightly coupled, portable */
#endif
};



PUBLIC CztDynamPeerAssocRsp RsLiCztDynamPeerAssocRspMt [] =
{
#ifdef LCRSLICZT
   cmPkCztDynamPeerAssocRsp,   /* 0 - loosely coupled */
#else
   PtLiCztPeerAssocRsp,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztDynamPeerAssocRsp,   /* 1 - light weight loosely coupled */
#else
   PtLiCztPeerAssocRsp,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztDynamPeerAssocRsp,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztPeerAssocRsp,        /* 2 - tightly coupled, portable */
#endif
};

PUBLIC CztAudReq RsLiCztAudReqMt [] =
{
#ifdef LCRSLICZT
   cmPkCztAudReq,        /* 0 - loosely coupled */
#else
   PtLiCztAudReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCRSLICZT
   cmPkCztAudReq,        /* 1 - light weight loosely coupled */
#else
   PtLiCztAudReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef CZ
   CzUiCztAudReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiCztAudReq,        /* 2 - tightly coupled, portable */
#endif
};

/************************************************************************
                       CZT Interface Functions
************************************************************************/

/*
 *
 *       Fun:   RsLiCztBndReq
 *
 *       Desc:  This function resolves the CztBndReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else 
PUBLIC S16 RsLiCztBndReq (pst, suId, spId)
Pst *pst;
SuId suId; 
SpId spId;
#endif
{
   TRC3(RsLiCztBndReq)

   (*RsLiCztBndReqMt[pst->selector])
      (pst, suId, spId);

   RETVALUE(ROK);
} /* RsLiCztBndReq */

/*
 *
 *       Fun:   RsLiCztUbndReq
 *
 *       Desc:  This function resolves the CztUbndReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else 
PUBLIC S16 RsLiCztUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   TRC3(RsLiCztUbndReq)

   (*RsLiCztUbndReqMt[pst->selector])
      (pst, spId, reason);

   RETVALUE(ROK);
} /* RsLiCztUbndReq */


/*
 *
 *       Fun:   RsLiCztGpRetxReq
 *
 *       Desc:  This function resolves the CztGpRetxReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztGpRetxReq
(
Pst *pst,
SpId spId,
CztReTxInfo *cztReTxInfo
)
#else 
PUBLIC S16 RsLiCztGpRetxReq (pst, spId, cztReTxInfo)
Pst *pst;
SpId spId;
CztReTxInfo *cztReTxInfo;
#endif
{
   TRC3(RsLiCztGpRetxReq)

   (*RsLiCztGpRetxReqMt[pst->selector])
      (pst, spId, cztReTxInfo);

   RETVALUE(ROK);
} /* RsLiCztGpRetxReq */


/*
 *
 *       Fun:   RsLiCztGpReq
 *
 *       Desc:  This function resolves the CztGpReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztGpReq
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PUBLIC S16 RsLiCztGpReq (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(RsLiCztGpReq)

   (*RsLiCztGpReqMt[pst->selector])
      (pst, spId, cztEvnt);

   RETVALUE(ROK);
} /* RsLiCztGpReq */

/*
 *
 *       Fun:   RsLiCztGpRsp
 *
 *       Desc:  This function resolves the CztGpRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztGpRsp
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PUBLIC S16 RsLiCztGpRsp (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(RsLiCztGpRsp)

   (*RsLiCztGpRspMt[pst->selector])
      (pst, spId, cztEvnt);

   RETVALUE(ROK);
} /* RsLiCztGpRsp */
/*
 *
 *       Fun:   RsLiCztGpErrReq
 *
 *       Desc:  This function resolves the CztGpErrReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztGpErrReq
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PUBLIC S16 RsLiCztGpErrReq (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(RsLiCztGpErrReq)

   (*RsLiCztGpErrReqMt[pst->selector])
      (pst, spId, cztEvnt);

   RETVALUE(ROK);
} /* RsLiCztGpReq */


/*
 *
 *       Fun:   RsLiCztRelReq
 *
 *       Desc:  This function resolves the CztRlsReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztRelReq
(
Pst *pst,
SpId spId,
CztRlsReq *relReq
)
#else 
PUBLIC S16 RsLiCztRelReq (pst, spId, relReq)
Pst *pst;
SpId spId;
CztRlsReq *relReq;
#endif
{
   TRC3(RsLiCztRelReq)

   (*RsLiCztRelReqMt[pst->selector])
      (pst, spId, relReq);

   RETVALUE(ROK);
} /* RsLiCztRelReq */

/*
 *
 *       Fun:   RsLiCztBmpReq
 *
 *       Desc:  This function resolves the CztBmpReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztBmpReq
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PUBLIC S16 RsLiCztBmpReq (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(RsLiCztBmpReq)

   (*RsLiCztBmpReqMt[pst->selector])
      (pst, spId, cztEvnt);

   RETVALUE(ROK);
} /* RsLiCztBmpReq */

/*
 *
 *       Fun:   RsLiCztBmpRsp
 *
 *       Desc:  This function resolves the CztBmpRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztBmpRsp
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PUBLIC S16 RsLiCztBmpRsp (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(RsLiCztBmpRsp)

   (*RsLiCztBmpRspMt[pst->selector])
      (pst, spId, cztEvnt);

   RETVALUE(ROK);
} /* RsLiCztBmpRsp */

/*
 *
 *       Fun:   RsLiCztPeerAssocRsp
 *
 *       Desc:  This function resolves the CztPeerAssocRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztDynamPeerAssocRsp
(
Pst *pst,
SpId spId,
CztPeerAssocRsp *peerAssocRsp
)
#else 
PUBLIC S16 RsLiCztDynamPeerAssocRsp (pst, spId, peerAssocRsp)
Pst *pst;
SpId spId;
CztPeerAssocRsp *peerAssocRsp;
#endif
{
   TRC3(RsLiCztPeerAssocRsp)

   (*RsLiCztDynamPeerAssocRspMt[pst->selector])
      (pst, spId, peerAssocRsp);

   RETVALUE(ROK);
} /* RsLiCztPeerAssocRsp */


/*
 *
 *       Fun:   RsLiCztAudReq
 *
 *       Desc:  This function resolves the CztAudReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 RsLiCztAudReq
(
Pst *pst,
SpId spId,
CztAudEvnt          *audEvnt
)
#else 
PUBLIC S16 RsLiCztAudReq (pst, spId, audEvnt)
Pst *pst;
SpId spId;
CztAudEvnt          *audEvnt;
#endif
{
   TRC3(RsLiCztAudReq)

   (*RsLiCztAudReqMt[pst->selector]) (pst, spId, audEvnt);

   RETVALUE(ROK);
} /* RsLiCztAudReq */



/************************************************************************
                       Portable Functions
************************************************************************/

#ifdef PTRSLICZT
/*
 *
 *       Fun:   PtLiCztBndReq
 *
 *       Desc:  Portable version of CztBndReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else 
PRIVATE S16 PtLiCztBndReq (pst, suId, spId)
Pst *pst;
SuId suId; 
SpId spId;
#endif
{
   TRC3(PtLiCztBndReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztBndReq() called");
#endif
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(RFAILED);
} /* PtLiCztBndReq */

/*
 *
 *       Fun:   PtLiCztUbndReq
 *
 *       Desc:  Portable version of CztUbndReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else 
PRIVATE S16 PtLiCztUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   TRC3(PtLiCztUbndReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztUbndReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);

   RETVALUE(RFAILED);
} /* PtLiCztUbndReq */


/*
 *
 *       Fun:   PtLiCztGpErrReq
 *
 *       Desc:  Portable version of CztGpErrReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztGpErrReq
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PRIVATE S16 PtLiCztGpErrReq (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(PtLiCztGpErrReq)


#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztGpReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(cztEvnt);

   RETVALUE(RFAILED);
} /* PtLiCztGpReq */


/*
 *
 *       Fun:   PtLiCztGpReq
 *
 *       Desc:  Portable version of CztGpReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztGpReq
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PRIVATE S16 PtLiCztGpReq (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(PtLiCztGpReq)


#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztGpReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(cztEvnt);

   RETVALUE(RFAILED);
} /* PtLiCztGpReq */

/*
 *
 *       Fun:   PtLiCztGpRsp
 *
 *       Desc:  Portable version of CztGpRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztGpRsp
(
Pst *pst,
SpId spId,
CztEvnt *conRsp
)
#else 
PRIVATE S16 PtLiCztGpRsp (pst, spId, conRsp)
Pst *pst;
SpId spId;
CztEvnt *conRsp;
#endif
{
   TRC3(PtLiCztGpRsp)


#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztGpRsp() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(conRsp);

   RETVALUE(RFAILED);
} /* PtLiCztGpRsp */

/*
 *
 *       Fun:   PtLiCztRelReq
 *
 *       Desc:  Portable version of CztRlsReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztRelReq
(
Pst *pst,
SpId spId,
CztRlsReq *relReq
)
#else 
PRIVATE S16 PtLiCztRelReq (pst, spId, relReq)
Pst *pst;
SpId spId;
CztRlsReq *relReq;
#endif
{
   TRC3(PtLiCztRelReq)


#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztRelReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(relReq);

   RETVALUE(RFAILED);
} /* PtLiCztRelReq */


/*
 *
 *       Fun:   PtLiCztBmpReq
 *
 *       Desc:  Portable version of CztBmpReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztBmpReq
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PRIVATE S16 PtLiCztBmpReq (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(PtLiCztBmpReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztBmpReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(cztEvnt);

   RETVALUE(RFAILED);
} /* PtLiCztBmpReq */

/*
 *
 *       Fun:   PtLiCztBmpRsp
 *
 *       Desc:  Portable version of CztBmpRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztBmpRsp
(
Pst *pst,
SpId spId,
CztEvnt *cztEvnt
)
#else 
PRIVATE S16 PtLiCztBmpRsp (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztEvnt *cztEvnt;
#endif
{
   TRC3(PtLiCztBmpRsp)

#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztBmpRsp() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(cztEvnt);

   RETVALUE(RFAILED);
} /* PtLiCztBmpRsp */

/*
 *
 *       Fun:   PtLiCztPeerAssocRsp
 *
 *       Desc:  Portable version of CztPeerAssocRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztPeerAssocRsp
(
Pst *pst,
SpId spId,
CztPeerAssocRsp *peerAssocRsp
)
#else 
PRIVATE S16 PtLiCztPeerAssocRsp (pst, spId, peerAssocRsp)
Pst *pst;
SpId spId;
CztPeerAssocRsp *peerAssocRsp;
#endif
{
   TRC3(PtLiCztPeerAssocRsp)


#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztPeerAssocRsp() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(peerAssocRsp);

   RETVALUE(RFAILED);
} /* PtLiCztPeerAssocRsp */

/*
 *
 *       Fun:   PtLiCztGpRetxReq
 *
 *       Desc:  This function resolves the CztGpRetxReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 PtLiCztGpRetxReq
(
Pst *pst,
SpId spId,
CztReTxInfo *cztReTxInfo
)
#else 
PUBLIC S16 PtLiCztGpRetxReq (pst, spId, cztReTxInfo)
Pst *pst;
SpId spId;
CztReTxInfo *cztReTxInfo;
#endif
{
   TRC3(PtLiCztGpRetxReq)


   RETVALUE(ROK);
} /* PtLiCztGpRetxReq */


/*
 *
 *       Fun:   PtLiCztAudReq
 *
 *       Desc:  Portable version of CztAudReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  rs_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiCztAudReq
(
Pst *pst,
SpId spId,
CztAudEvnt *cztEvnt
)
#else 
PRIVATE S16 PtLiCztAudReq (pst, spId, cztEvnt)
Pst *pst;
SpId spId;
CztAudEvnt *cztEvnt;
#endif
{
   TRC3(PtLiCztAudReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   CZLOGERROR(ERRCLS_DEBUG, ECZXXX, (ErrVal) 0, 
              "PtLiCztAudReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(cztEvnt);

   RETVALUE(RFAILED);
} /* PtLiCztAudReq */


#endif /* PTRSLICZT */
/********************************************************************30**

         End of file:     rs_ptli.c@@/main/2 - Tue Aug 30 18:36:07 2011

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
/main/1      ---      sy       1. Updated for Release X2AP
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
