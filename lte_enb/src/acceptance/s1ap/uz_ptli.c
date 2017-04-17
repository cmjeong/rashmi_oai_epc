
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszhdl.c

     Sid:      uz_ptli.c@@/main/4 - Mon Jan 10 22:16:50 2011

     Prg:     pk 
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

#include "sct.h"           /* SB (SCTP) layer */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for SZCP */
#include "sz.h"            /* defines and macros for SZ */
#include "szt.h"            /* defines and macros for SZ */
/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"

#include "sz_err.h"        /* SZ error defines */
#include "szac_acc.h"        /* defines for SZ acceptance tests */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "sb_mtu.h"
#include "sb.h"
#endif    /* SB */
#include "cm_pasn.h"

#include "cm_xta.h" 
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif


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

#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Interface Structures */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SZT Interface Structures */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA 
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for SZCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "sb_mtu.x"
#include "sb.x"
#endif    /* SB */
#include "cm_pasn.x"

#include "cm_xta.x" 
#include "sz.x"            /* typedefs for SZCP */
#include "uz.x"            /* typedefs for SZCP */
#include "szac_acc.x"        /* typedefs for SZCP acceptance tests */
#include "szac_lsz.x"
/* ---- S1AP service user lower interface ---- */
/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000XXX                      S1AP v 1.1
 */


/************************************************************************
                              Prototypes  
************************************************************************/
#if !(defined(LCUZLISZT) && defined(LWLCUZLISZT) && defined(SZ))
#undef PTUZLISZT
#define PTUZLISZT
#endif

#ifdef PTUZLISZT 
PRIVATE S16 PtLiSztBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
PRIVATE S16 PtLiSztUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
PRIVATE S16 PtLiSztUDatReq      ARGS((Pst *pst, SpId spId, SztUDatEvnt *uDatEvnt));
PRIVATE S16 PtLiSztConReq       ARGS((Pst *pst, SpId spId, SztConReq *conReq));
PRIVATE S16 PtLiSztConRsp       ARGS((Pst *pst, SpId spId, SztConRsp *conRsp));
PRIVATE S16 PtLiSztRelReq       ARGS((Pst *pst, SpId spId, SztRelReq *relReq));
PRIVATE S16 PtLiSztRelRsp       ARGS((Pst *pst, SpId spId, SztRelRsp *relRsp));
PRIVATE S16 PtLiSztDatReq       ARGS((Pst *pst, SpId spId, SztDatEvntReq *datEvnt));
PRIVATE S16 PtLiSztEncDecReq    ARGS((Pst *pst, SpId spId, SztEncDecEvnt *sztEncDecEvnt));
PRIVATE S16 PtLiSztAudReq       ARGS((Pst *pst, SpId spId, SztAudEvnt *audEvnt));
/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
PRIVATE S16 PtLiSztAborts1Req   ARGS((Pst *pst, SpId spId, SztAbortS1 *abortS1));
#endif /* SZTV2 */
#ifdef SZ_MME
PRIVATE S16 PtLiSztPeerAssocRsp ARGS((Pst *pst, SpId spId, SztPeerAssocRsp *peerAssocRsp));
#endif
#endif /* PTUZLISZT */


/* Following matrices define the mapping between the primitives called by the
 * S1AP user (as UzLiSztXXXReq) and the corresponding primitives of the 
 * S1AP layer (service provider) (as SzUiSztXXXReq).
 * The mapping is based on pst->selector.
 * Selector          #define     Coupling      Primitive
 * 0 (SEL_LC_NEW)   LCUZLISZT    loose         cmPkSztXXXReq
 * 1                 SZ          tight         SzUiSztXXXReq
 * 2                LWLCUZLISZT  LW loose      cmPkSztXXXReq
 */


PUBLIC SztBndReq UzLiSztBndReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztBndReq,        /* 0 - loosely coupled */
#else
   PtLiSztBndReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztBndReq,        /* 1 - light weight loosely coupled */
#else
   PtLiSztBndReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztBndReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztBndReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC SztUbndReq UzLiSztUbndReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztUbndReq,        /* 0 - loosely coupled */
#else
   PtLiSztUbndReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztUbndReq,        /* 1 - light weight loosely coupled */
#else
   PtLiSztUbndReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztUbndReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztUbndReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC SztUDatReq UzLiSztUDatReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztUDatReq,        /* 0 - loosely coupled */
#else
   PtLiSztUDatReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztUDatReq,        /* 1 - light weight loosely coupled */
#else
   PtLiSztUDatReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztUDatReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztUDatReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC SztConnReq UzLiSztConReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztConReq,        /* 0 - loosely coupled */
#else
   PtLiSztConReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztConReq,        /* 1 - light weight loosely coupled */
#else
   PtLiSztConReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztConReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztConReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC SztConnRsp UzLiSztConRspMt [] =
{
#ifdef LCUZLISZT
   cmPkSztConRsp,        /* 0 - loosely coupled */
#else
   PtLiSztConRsp,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztConRsp,        /* 1 - light weight loosely coupled */
#else
   PtLiSztConRsp,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztConRsp,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztConRsp,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC SztRelsReq UzLiSztRelReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztRelReq,        /* 0 - loosely coupled */
#else
   PtLiSztRelReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztRelReq,        /* 1 - light weight loosely coupled */
#else
   PtLiSztRelReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztRelReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztRelReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC SztRelsRsp UzLiSztRelRspMt [] =
{
#ifdef LCUZLISZT
   cmPkSztRelRsp,        /* 0 - loosely coupled */
#else
   PtLiSztRelRsp,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztRelRsp,        /* 1 - light weight loosely coupled */
#else
   PtLiSztRelRsp,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztRelRsp,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztRelRsp,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC SztDatReq UzLiSztDatReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztDatReq,        /* 0 - loosely coupled */
#else
   PtLiSztDatReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztDatReq,        /* 1 - light weight loosely coupled */
#else
   PtLiSztDatReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztDatReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztDatReq,        /* 2 - tightly coupled, portable */
#endif
};


PUBLIC SztEncDecReq UzLiSztEncDecReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztEncDecReq,        /* 0 - loosely coupled */
#else
   PtLiSztEncDecReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztEncDecReq,        /* 1 - light weight loosely coupled */
#else
   PtLiSztEncDecReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztEncDecReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztEncDecReq,        /* 2 - tightly coupled, portable */
#endif
};

PUBLIC SztAudReq UzLiSztAudReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztAudReq,        /* 0 - loosely coupled */
#else
   PtLiSztAudReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztAudReq,        /* 1 - light weight loosely coupled */
#else
   PtLiSztAudReq,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztAudReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztAudReq,        /* 2 - tightly coupled, portable */
#endif
};

#ifdef SZ_MME
PUBLIC SztDynamPeerAssocRsp UzLiSztPeerAssocRspMt [] =
{
#ifdef LCUZLISZT
   cmPkSztPeerAssocRsp,        /* 0 - loosely coupled */
#else
   PtLiSztPeerAssocRsp,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztPeerAssocRsp,        /* 1 - light weight loosely coupled */
#else
   PtLiSztPeerAssocRsp,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztPeerAssocRsp,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztPeerAssocRsp,        /* 2 - tightly coupled, portable */
#endif
};
#endif

/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
PUBLIC SztAbortS1Req UzLiSztAbortS1ReqMt [] =
{
#ifdef LCUZLISZT
   cmPkSztAbortS1Req,        /* 0 - loosely coupled */
#else
   PtLiSztAbortS1Req,        /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCUZLISZT
   cmPkSztAbortS1Req,        /* 1 - light weight loosely coupled */
#else
   PtLiSztAbortS1Req,        /* 1 - light weight loosely coupled, portable */
#endif
#ifdef SZ
   SzUiSztAbortS1Req,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSztAbortS1Req,        /* 2 - tightly coupled, portable */
#endif
};
#endif /* SZTV2 */

/************************************************************************
                       SZT Interface Functions
************************************************************************/

/*
 *
 *       Fun:   UzLiSztBndReq
 *
 *       Desc:  This function resolves the SztBndReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else 
PUBLIC S16 UzLiSztBndReq (pst, suId, spId)
Pst *pst;
SuId suId; 
SpId spId;
#endif
{
   TRC3(UzLiSztBndReq)

   (*UzLiSztBndReqMt[pst->selector])
      (pst, suId, spId);

   RETVALUE(ROK);
} /* UzLiSztBndReq */

/*
 *
 *       Fun:   UzLiSztUbndReq
 *
 *       Desc:  This function resolves the SztUbndReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else 
PUBLIC S16 UzLiSztUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   TRC3(UzLiSztUbndReq)

   (*UzLiSztUbndReqMt[pst->selector])
      (pst, spId, reason);

   RETVALUE(ROK);
} /* UzLiSztUbndReq */

/*
 *
 *       Fun:   UzLiSztUDatReq
 *
 *       Desc:  This function resolves the SztUDatReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztUDatReq
(
Pst *pst,
SpId spId,
SztUDatEvnt *uDatEvnt
)
#else 
PUBLIC S16 UzLiSztUDatReq (pst, spId, uDatEvnt)
Pst *pst;
SpId spId;
SztUDatEvnt *uDatEvnt;
#endif
{
   TRC3(UzLiSztUDatReq)

   (*UzLiSztUDatReqMt[pst->selector])
      (pst, spId, uDatEvnt);

   RETVALUE(ROK);
} /* UzLiSztUDatReq */

/*
 *
 *       Fun:   UzLiSztConReq
 *
 *       Desc:  This function resolves the SztConReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztConReq
(
Pst *pst,
SpId spId,
SztConReq *conReq
)
#else 
PUBLIC S16 UzLiSztConReq (pst, spId, conReq)
Pst *pst;
SpId spId;
SztConReq *conReq;
#endif
{
   TRC3(UzLiSztConReq)

   (*UzLiSztConReqMt[pst->selector])
      (pst, spId, conReq);

   RETVALUE(ROK);
} /* UzLiSztConReq */

/*
 *
 *       Fun:   UzLiSztConRsp
 *
 *       Desc:  This function resolves the SztConRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztConRsp
(
Pst *pst,
SpId spId,
SztConRsp *conRsp
)
#else 
PUBLIC S16 UzLiSztConRsp (pst, spId, conRsp)
Pst *pst;
SpId spId;
SztConRsp *conRsp;
#endif
{
   TRC3(UzLiSztConRsp)

   (*UzLiSztConRspMt[pst->selector])
      (pst, spId, conRsp);

   RETVALUE(ROK);
} /* UzLiSztConRsp */

/*
 *
 *       Fun:   UzLiSztRelReq
 *
 *       Desc:  This function resolves the SztRelReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztRelReq
(
Pst *pst,
SpId spId,
SztRelReq *relReq
)
#else 
PUBLIC S16 UzLiSztRelReq (pst, spId, relReq)
Pst *pst;
SpId spId;
SztRelReq *relReq;
#endif
{
   TRC3(UzLiSztRelReq)

   (*UzLiSztRelReqMt[pst->selector])
      (pst, spId, relReq);

   RETVALUE(ROK);
} /* UzLiSztRelReq */

/*
 *
 *       Fun:   UzLiSztRelRsp
 *
 *       Desc:  This function resolves the SztRelRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztRelRsp
(
Pst *pst,
SpId spId,
SztRelRsp *relRsp
)
#else 
PUBLIC S16 UzLiSztRelRsp (pst, spId, relRsp)
Pst *pst;
SpId spId;
SztRelRsp *relRsp;
#endif
{
   TRC3(UzLiSztRelRsp)

   (*UzLiSztRelRspMt[pst->selector])
      (pst, spId, relRsp);

   RETVALUE(ROK);
} /* UzLiSztRelRsp */

/*
 *
 *       Fun:   UzLiSztDatReq
 *
 *       Desc:  This function resolves the SztDatReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztDatReq
(
Pst *pst,
SpId spId,
SztDatEvntReq *datEvnt
)
#else 
PUBLIC S16 UzLiSztDatReq (pst, spId, datEvnt)
Pst *pst;
SpId spId;
SztDatEvntReq *datEvnt;
#endif
{
   TRC3(UzLiSztDatReq)

   (*UzLiSztDatReqMt[pst->selector])
      (pst, spId, datEvnt);

   RETVALUE(ROK);
} /* UzLiSztDatReq */

/*
 *
 *       Fun:   UzLiSztEncDecReq
 *
 *       Desc:  This function resolves the SztEncDecReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztEncDecReq
(
Pst *pst,
SpId spId,
SztEncDecEvnt *sztEncDecEvnt
)
#else 
PUBLIC S16 UzLiSztEncDecReq (pst, spId, sztEncDecEvnt)
Pst *pst;
SpId spId;
SztEncDecEvnt *sztEncDecEvnt;
#endif
{
   TRC3(UzLiSztEncDecReq)

   (*UzLiSztEncDecReqMt[pst->selector])
      (pst, spId, sztEncDecEvnt);

   RETVALUE(ROK);
} /* UzLiSztEncDecReq */

/*
 *
 *       Fun:   UzLiSztAudReq
 *
 *       Desc:  This function resolves the SztAudReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztAudReq
(
Pst *pst,
SpId spId,
SztAudEvnt *audEvnt
)
#else 
PUBLIC S16 UzLiSztAudReq (pst, spId, audEvnt)
Pst *pst;
SpId spId;
SztAudEvnt *audEvnt;
#endif
{
   TRC3(UzLiSztAudReq)

   (*UzLiSztAudReqMt[pst->selector])
      (pst, spId, audEvnt);

   RETVALUE(ROK);
} /* UzLiSztAudReq */

#ifdef SZ_MME
/*
 *
 *       Fun:   UzLiSztPeerAssocRsp
 *
 *       Desc:  This function resolves the SztPeerAssocRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztPeerAssocRsp
(
Pst *pst,
SpId spId,
SztPeerAssocRsp *peerAssocRsp
)
#else 
PUBLIC S16 UzLiSztPeerAssocRsp (pst, spId, peerAssocRsp)
Pst *pst;
SpId spId;
SztPeerAssocRsp *peerAssocRsp;
#endif
{
   TRC3(UzLiSztPeerAssocRsp)

   (*UzLiSztPeerAssocRspMt[pst->selector])
      (pst, spId, peerAssocRsp);

   RETVALUE(ROK);
} /* UzLiSztPeerAssocRsp */
#endif

/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
/*
 *
 *       Fun:   UzLiSztAbortS1Req
 *
 *       Desc:  This function resolves the SztAbortS1Req primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PUBLIC S16 UzLiSztAbortS1Req
(
Pst         *pst,
SuId        suId,
SztAbortS1  *abortS1
)
#else 
PUBLIC S16 UzLiSztAbortS1Req (pst, suId, abortS1)
Pst        *pst;
SuId       suId; 
SztAbortS1 *abortS1;
#endif
{
   TRC3(UzLiSztAbortS1Req)

   (*UzLiSztAbortS1ReqMt[pst->selector])
      (pst, suId, abortS1);

   RETVALUE(ROK);
} /* UzLiSztAbortS1Req */
#endif /* SZTV2 */

/************************************************************************
                       Portable Functions
************************************************************************/

#ifdef PTUZLISZT
/*
 *
 *       Fun:   PtLiSztBndReq
 *
 *       Desc:  Portable version of SztBndReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else 
PRIVATE S16 PtLiSztBndReq (pst, suId, spId)
Pst *pst;
SuId suId; 
SpId spId;
#endif
{
   TRC3(PtLiSztBndReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztBndReq() called");
#endif
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(RFAILED);
} /* PtLiSztBndReq */

/*
 *
 *       Fun:   PtLiSztUbndReq
 *
 *       Desc:  Portable version of SztUbndReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else 
PRIVATE S16 PtLiSztUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   TRC3(PtLiSztUbndReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztUbndReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);

   RETVALUE(RFAILED);
} /* PtLiSztUbndReq */

/*
 *
 *       Fun:   PtLiSztUDatReq
 *
 *       Desc:  Portable version of SztUDatReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztUDatReq
(
Pst *pst,
SpId spId,
SztUDatEvnt *uDatEvnt
)
#else 
PRIVATE S16 PtLiSztUDatReq (pst, spId, uDatEvnt)
Pst *pst;
SpId spId;
SztUDatEvnt *uDatEvnt;
#endif
{
   TRC3(PtLiSztUDatReq)


#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztUDatReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(uDatEvnt);

   RETVALUE(RFAILED);
} /* PtLiSztUDatReq */

/*
 *
 *       Fun:   PtLiSztConReq
 *
 *       Desc:  Portable version of SztConReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztConReq
(
Pst *pst,
SpId spId,
SztConReq *conReq
)
#else 
PRIVATE S16 PtLiSztConReq (pst, spId, conReq)
Pst *pst;
SpId spId;
SztConReq *conReq;
#endif
{
   TRC3(PtLiSztConReq)


#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztConReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(conReq);

   RETVALUE(RFAILED);
} /* PtLiSztConReq */

/*
 *
 *       Fun:   PtLiSztConRsp
 *
 *       Desc:  Portable version of SztConRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztConRsp
(
Pst *pst,
SpId spId,
SztConRsp *conRsp
)
#else 
PRIVATE S16 PtLiSztConRsp (pst, spId, conRsp)
Pst *pst;
SpId spId;
SztConRsp *conRsp;
#endif
{
   TRC3(PtLiSztConRsp)


#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztConRsp() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(conRsp);

   RETVALUE(RFAILED);
} /* PtLiSztConRsp */

/*
 *
 *       Fun:   PtLiSztRelReq
 *
 *       Desc:  Portable version of SztRelReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztRelReq
(
Pst *pst,
SpId spId,
SztRelReq *relReq
)
#else 
PRIVATE S16 PtLiSztRelReq (pst, spId, relReq)
Pst *pst;
SpId spId;
SztRelReq *relReq;
#endif
{
   TRC3(PtLiSztRelReq)


#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztRelReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(relReq);

   RETVALUE(RFAILED);
} /* PtLiSztRelReq */

/*
 *
 *       Fun:   PtLiSztRelRsp
 *
 *       Desc:  Portable version of SztRelRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztRelRsp
(
Pst *pst,
SpId spId,
SztRelRsp *relRsp
)
#else 
PRIVATE S16 PtLiSztRelRsp (pst, spId, relRsp)
Pst *pst;
SpId spId;
SztRelRsp *relRsp;
#endif
{
   TRC3(PtLiSztRelRsp)


#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztRelRsp() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(relRsp);

   RETVALUE(RFAILED);
} /* PtLiSztRelRsp */

/*
 *
 *       Fun:   PtLiSztDatReq
 *
 *       Desc:  Portable version of SztDatReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztDatReq
(
Pst *pst,
SpId spId,
SztDatEvntReq *datEvnt
)
#else 
PRIVATE S16 PtLiSztDatReq (pst, spId, datEvnt)
Pst *pst;
SpId spId;
SztDatEvntReq *datEvnt;
#endif
{
   TRC3(PtLiSztDatReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztDatReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(datEvnt);

   RETVALUE(RFAILED);
} /* PtLiSztDatReq */

/*
 *
 *       Fun:   PtLiSztEncDecReq
 *
 *       Desc:  Portable version of SztEncDecReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztEncDecReq
(
Pst *pst,
SpId spId,
SztEncDecEvnt *sztEncDecEvnt
)
#else 
PRIVATE S16 PtLiSztEncDecReq (pst, spId, sztEncDecEvnt)
Pst *pst;
SpId spId;
SztEncDecEvnt *sztEncDecEvnt;
#endif
{
   TRC3(PtLiSztEncDecReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztEncDecReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(sztEncDecEvnt);

   RETVALUE(RFAILED);
} /* PtLiSztEncDecReq */

/*
 *
 *       Fun:   PtLiSztAudReq
 *
 *       Desc:  Portable version of SztAudReq primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztAudReq
(
Pst *pst,
SpId spId,
SztAudEvnt *audEvnt
)
#else 
PRIVATE S16 PtLiSztAudReq (pst, spId, audEvnt)
Pst *pst;
SpId spId;
SztAudEvnt *audEvnt;
#endif
{
   TRC3(PtLiSztAudReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztAudReq() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(audEvnt);

   RETVALUE(RFAILED);
} /* PtLiSztAudReq */

#ifdef SZ_MME
/*
 *
 *       Fun:   PtLiSztPeerAssocRsp
 *
 *       Desc:  Portable version of SztPeerAssocRsp primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztPeerAssocRsp
(
Pst *pst,
SpId spId,
SztPeerAssocRsp *peerAssocRsp
)
#else 
PRIVATE S16 PtLiSztPeerAssocRsp (pst, spId, peerAssocRsp)
Pst *pst;
SpId spId;
SztPeerAssocRsp *peerAssocRsp;
#endif
{
   TRC3(PtLiSztPeerAssocRsp)


#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztPeerAssocRsp() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(peerAssocRsp);

   RETVALUE(RFAILED);
} /* PtLiSztPeerAssocRsp */
#endif

/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
/*
 *
 *       Fun:   PtLiSztAbortS1Req
 *
 *       Desc:  Portable version of SztAbortS1Req primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  uz_ptli.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtLiSztAbortS1Req
(
Pst         *pst,
SpId        spId,
SztAbortS1  *abortS1
)
#else 
PRIVATE S16 PtLiSztAbortS1Req (pst, spId, abortS1)
Pst         *pst;
SpId        spId;
SztAbortS1  *abortS1;
#endif
{
   TRC3(PtLiSztAbortS1Req)


#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZXXX, (ErrVal) 0, 
              "PtLiSztAbortS1Req() called");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(abortS1);

   RETVALUE(RFAILED);
} /* PtLiSztAbortS1Req */
#endif /* SZTV2 */

#endif /* PTUZLISZT */
/********************************************************************30**

         End of file:     uz_ptli.c@@/main/4 - Mon Jan 10 22:16:50 2011

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
/main/4      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz005.301   va    1. Updated for S1 Abort request support by UI
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth1. Support for source RNC to target RNC.
*********************************************************************91*/
