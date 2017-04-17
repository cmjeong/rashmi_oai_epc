

/********************************************************************20**

     Name:     hi_ptui.c - SCTP layer portable lower layer interface

     Type:     C source file

     Desc:     C source code for the outgoing lower layer primitives (originating at
               the service provider) used in loosely/tightly coupled systems. The two
               sections of the file is:
               - The setting up of the primitive mapping table
               - Transmission of the primitives using the mapping table.

     File:     hi_ptui.c

     Sid:      hi_ptui.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:09 2015

     Prg:      mrw

*********************************************************************21*/

/*

  hi_ptui.c -

Following public functions are provided in this file:
* HiUiHitBndReq                    -  Bind request
* HiUiHitUbndReq                   -  Unbind request
* HiUiHitServOpenReq               -  Open server request
* HiUiHitUDatReq                   -  Data request
* HiUiHitDiscReq                   -  Disconnect request
*/


/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000163                      SCTP layer
 */

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS  defines */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */
#ifdef SB_ACC
#include "sb_acc.h"
#endif /*SB_ACC*/

/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* common DNS  defines */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#ifdef SB_ACC
#include "sb_acc.x"        /* typedefs for the SCTP test controller */
#endif /*SB_ACC*/


/* local defines */

#define MAXSBUI                2

#ifndef LCHIUIHIT
#define PTHIUIHIT
#else
#ifndef SB
#define PTHIUIHIT
#else
#endif
#endif

/* local typedefs */

/* local externs */

/* forward references */
#ifdef PTHIUIHIT

PRIVATE S16 PtUiHitBndCfm  ARGS((Pst *pst, SuId suId, U8 status ));
PRIVATE S16 PtUiHitConCfm  ARGS((Pst *pst, SuId suId, UConnId suConId, UConnId spConId,
CmTptAddr *localAddr ));
PRIVATE S16 PtUiHitUDatInd ARGS((Pst *pst, SuId suId, UConnId suConId, CmTptAddr *srcAddr,
CmTptAddr *destAddr, CmIpHdrParm *hdrParm, Buffer *mBuf ));
PRIVATE S16 PtUiHitDiscInd  ARGS((Pst *pst, SuId suId, U8 choice, UConnId conId,
Reason  reason ));
PRIVATE S16 PtUiHitDiscCfm  ARGS((Pst *pst, SuId suId, U8 choice, UConnId conId,
Action action ));

#endif
/* functions in other modules */

/* public variable declarations */

/* private variable declarations */


/*
The following matrices define the mapping between the primitives
called by the upper layer interface of SCTP layer and the corresponding
primitives in the SCTP.

The parameter MAXSBLI defines the maximum number of selector options below the upper layer.
There is an array of functions per primitive invoked by the upper layer.
Every array is MAXSBUI long.

The dispatching is performed by the configurable variable: selector.
The selector is configured during general configuration.

The selectors are:

   0 - loosely coupled (#define LCSMSBMILSB)
   1 - Lsb (#define SB)

*/

/* Bind Confirm primitive */

PRIVATE HitBndCfm HiUiHitBndCfmMt[MAXSBUI] =
{
#ifdef LCHIUIHIT
   cmPkHitBndCfm,          /* 0 - loosely coupled - bc */
#else
   PtUiHitBndCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitBndCfm,          /* 1 - tightly coupled, lower layer */
#else
   PtUiHitBndCfm           /* 1 - tightly coupled, portable */
#endif
};

/* Connection Confirm primitive */

PRIVATE HitConCfm HiUiHitConCfmMt[MAXSBUI] =
{
#ifdef LCHIUIHIT
   cmPkHitConCfm,          /* 0 - loosely coupled - bc */
#else
   PtUiHitConCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitConCfm,          /* 1 - tightly coupled, lower layer */
#else
   PtUiHitConCfm           /* 1 - tightly coupled, portable */
#endif
};

/* Unit Data indication primitive */

PRIVATE HitUDatInd HiUiHitUDatIndMt[MAXSBUI] =
{
#ifdef LCHIUIHIT
   cmPkHitUDatInd,          /* 0 - loosely coupled - bc */
#else
   PtUiHitUDatInd,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitUDatInd,          /* 1 - tightly coupled, lower layer */
#else
   PtUiHitUDatInd           /* 1 - tightly coupled, portable */
#endif
};

/* Disconnect confirm primitive */

PRIVATE HitDiscCfm HiUiHitDiscCfmMt[MAXSBUI] =
{
#ifdef LCHIUIHIT
   cmPkHitDiscCfm,          /* 0 - loosely coupled - bc */
#else
   PtUiHitDiscCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitDiscCfm,          /* 1 - tightly coupled, lower layer */
#else
   PtUiHitDiscCfm          /* 1 - tightly coupled, portable */
#endif
};

/* Disconnect indication primitive */

PRIVATE HitDiscInd HiUiHitDiscIndMt[MAXSBUI] =
{
#ifdef LCHIUIHIT
   cmPkHitDiscInd,          /* 0 - loosely coupled - bc */
#else
   PtUiHitDiscInd,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitDiscInd,          /* 1 - tightly coupled, lower layer */
#else
   PtUiHitDiscInd           /* 1 - tightly coupled, portable */
#endif
};


/*
*     lower layer interface functions
*/

/*
*
*       Fun:   Bind Confirm
*
*       Desc:  This function is used to confirm a bind request from the SCTP layer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiHitBndCfm
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user SAP ID */
U8 status                 /* status */
)
#else
PUBLIC S16 HiUiHitBndCfm(pst, suId, status)
Pst *pst;                 /* post structure */
SuId suId;                /* service user SAP ID */
U8 status;                /* status */
#endif
{
   TRC3(HiUiHitBndCfm)
   /* jump to specific primitive depending on configured selector */
   (*HiUiHitBndCfmMt[pst->selector])(pst, suId, status);
   RETVALUE(ROK);
} /* end of HiUiHitBndCfm */

/*
*
*       Fun:   Connect confirm
*
*       Desc:  This function is used to confirm that the listener socket has been opened.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiHitConCfm
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
UConnId spConId,          /* service provider's connection Id */
CmTptAddr *localAddr     /* local transport address */
)
#else
PUBLIC S16 HiUiHitConCfm(pst, suId, suConId, spConId, localAddr)
Pst *pst;                 /* post structure */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
UConnId spConId;          /* service provider's connection Id */
CmTptAddr *localAddr;    /* local transport address */
#endif
{
   TRC3(HiUiHitConCfm)
   /* jump to specific primitive depending on configured selector */
   (*HiUiHitConCfmMt[pst->selector])(pst, suId, suConId, spConId, localAddr);
   RETVALUE(ROK);
} /* end of HiUiHitConCfm */

/*
*
*       Fun:   Unit data indication
*
*       Desc:  This function is used to deliver incoming data to the service user
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

/* sb032.102 :  IPV6 Support Added */
#ifdef LOCAL_INTF
#ifdef ANSI
PUBLIC S16 HiUiHitUDatInd
(
Pst                  *pst,      /* post structure */
SuId                  suId,     /* service user SAP ID */
UConnId               suConId,  /* service user's connection ID */
CmTptAddr            *srcAddr,  /* source transport address */
CmTptAddr            *destAddr, /* dest source transport address */
CmIpHdrParm          *hdrParm,  /* header parameters */
CmTptLocalInf        *localIf,  /* Local interface variable */
Buffer               *mBuf      /* message buffer */
)
#else
PUBLIC S16 HiUiHitUDatInd(pst, suId, suConId, srcAddr, destAddr, hdrParm,localIf, mBuf)
Pst                  *pst;      /* post structure */
SuId                  suId;     /* service user SAP ID */
UConnId               suConId;  /* service user's connection ID */
CmTptAddr            *srcAddr;  /* source transport address */
CmTptAddr            *destAddr; /* dest source transport address */
CmIpHdrParm          *hdrParm;  /* header parameters */
CmTptLocalInf        *localIf;  /* Local interface variable */
Buffer               *mBuf;     /* message buffer */
#endif
#else
#ifdef ANSI
PUBLIC S16 HiUiHitUDatInd
(
Pst                  *pst,      /* post structure */
SuId                  suId,     /* service user SAP ID */
UConnId               suConId,  /* service user's connection ID */
CmTptAddr            *srcAddr,  /* source transport address */
CmTptAddr            *destAddr, /* dest source transport address */
CmIpHdrParm          *hdrParm,  /* header parameters */
Buffer               *mBuf      /* message buffer */
)
#else
PUBLIC S16 HiUiHitUDatInd(pst, suId, suConId, srcAddr, destAddr, hdrParm, mBuf)
Pst                  *pst;      /* post structure */
SuId                  suId;     /* service user SAP ID */
UConnId               suConId;  /* service user's connection ID */
CmTptAddr            *srcAddr;  /* source transport address */
CmTptAddr            *destAddr; /* dest source transport address */
CmIpHdrParm          *hdrParm;  /* header parameters */
Buffer               *mBuf;     /* message buffer */
#endif
#endif
{
   TRC3(HiUiHitUDatInd)
   /* jump to specific primitive depending on configured selector */
   /* sb032.102 :  IPV6 Support Added */
#ifdef LOCAL_INTF
   (*HiUiHitUDatIndMt[pst->selector])(pst, suId, suConId, srcAddr, destAddr, hdrParm, localIf, mBuf); 
#else
   (*HiUiHitUDatIndMt[pst->selector])(pst, suId, suConId, srcAddr, destAddr, hdrParm, mBuf);
#endif
   RETVALUE(ROK);
} /* end of HiUiHitUDatInd */

/*
*
*       Fun:   Disconnection Indication
*
*       Desc:  This function is used to inform the service user that the socket is being
*              closed by the TUCL.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiHitDiscInd
(
Pst *pst,                 /* post strauchire */
SuId suId,                /* service user SAP ID */
U8 choice,                /* choice parameter */
UConnId conId,            /* connection ID */
Reason  reason            /* reason */
)
#else
PUBLIC S16 HiUiHitDiscInd(pst, suId, choice, conId, reason)
Pst *pst;                 /* post strauchire */
SuId suId;                /* service user SAP ID */
U8 choice;                /* choice parameter */
UConnId conId;            /* connection ID */
Reason  reason;           /* reason */
#endif
{
   TRC3(HiUiHitDiscInd)
   /* jump to specific primitive depending on configured selector */
   (*HiUiHitDiscIndMt[pst->selector])(pst, suId, choice, conId, reason);
   RETVALUE(ROK);
} /* end of HiUiHitDiscInd */

/*
*
*       Fun:   Disconnection Confirm
*
*       Desc:  This function is used to indicate that the disconnect request was successful.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 HiUiHitDiscCfm
(
Pst *pst,                 /* post strauchire */
SuId suId,                /* service user SAP ID */
U8 choice,                /* choice parameter */
UConnId conId,            /* connection ID */
Action action             /* action */
)
#else
PUBLIC S16 HiUiHitDiscCfm(pst, suId, choice, conId, action)
Pst *pst;                 /* post strauchire */
SuId suId;                /* service user SAP ID */
U8 choice;                /* choice parameter */
UConnId conId;            /* connection ID */
Action action;            /* action */
#endif
{
   TRC3(HiUiHitDiscCfm)
   /* jump to specific primitive depending on configured selector */
   (*HiUiHitDiscCfmMt[pst->selector])(pst, suId, choice, conId, action);
   RETVALUE(ROK);
} /* end of HiUiHitDiscCfm */

#ifdef PTHIUIHIT
/*
*
*       Fun:   Portable Bind confirm
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PRIVATE S16 PtUiHitBndCfm
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user SAP ID */
U8 status                 /* status */
)
#else
PRIVATE S16 PtUiHitBndCfm(pst, suId, status)
Pst *pst;                 /* post structure */
SuId suId;                /* service user SAP ID */
U8 status;                /* status */
#endif
{
   TRC3(PtUiHitBndCfm);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(suId);
   UNUSED (status);
   RETVALUE(ROK);
} /* end of PtUiHitBndCfm*/


/*
*
*       Fun:   Portable connection confirm
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PRIVATE S16 PtUiHitConCfm
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
UConnId spConId,          /* service provider's connection Id */
CmTptAddr *localAddr     /* local transport address */
)
#else
PRIVATE S16 PtUiHitConCfm(pst, suId, suConId, spConId, localAddr)
Pst *pst;                 /* post structure */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
UConnId spConId;          /* service provider's connection Id */
CmTptAddr *localAddr;    /* local transport address */
#endif
{
   TRC3(PtUiHitConCfm);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suConId);
   UNUSED(spConId);
   UNUSED(localAddr);
   RETVALUE(ROK);
} /* end of PtUiHitConCfm */


/*
*
*       Fun:   Portable Unit data confirm
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PRIVATE S16 PtUiHitUDatInd
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user SAP ID */
UConnId suConId,          /* service user's connection ID */
CmTptAddr *srcAddr,       /* source transport address */
CmTptAddr *destAddr,      /* dest source transport address */
CmIpHdrParm  *hdrParm,    /* header parameters */
Buffer *mBuf              /* message buffer */
)
#else
PRIVATE S16 PtUiHitUDatInd(pst, suId, suConId, srcAddr, destAddr, hdrParm, mBuf)
Pst *pst;                 /* post structure */
SuId suId;                /* service user SAP ID */
UConnId suConId;          /* service user's connection ID */
CmTptAddr *srcAddr;       /* source transport address */
CmTptAddr *destAddr;      /* dest source transport address */
CmIpHdrParm  *hdrParm;    /* header parameters */
Buffer *mBuf;             /* message buffer */
#endif
{
   TRC3(PtUiHitUDatInd);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suConId);
   UNUSED(srcAddr);
   UNUSED(destAddr);
   UNUSED(hdrParm);
   UNUSED(mBuf);
   RETVALUE(ROK);
} /* end of PtUiHitUDatInd */


/*
*
*       Fun:   Portable disconnection indicator
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PRIVATE S16 PtUiHitDiscInd
(
Pst *pst,                 /* post strauchire */
SuId suId,                /* service user SAP ID */
U8 choice,                /* choice parameter */
UConnId conId,            /* connection ID */
Reason  reason            /* reason */
)
#else
PRIVATE S16 PtUiHitDiscInd(pst, suId, choice, conId, reason)
Pst *pst;                 /* post strauchire */
SuId suId;                /* service user SAP ID */
U8 choice;                /* choice parameter */
UConnId conId;            /* connection ID */
Reason  reason;           /* reason */
#endif
{
   TRC3(PtUiHitDiscInd);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(choice);
   UNUSED(conId);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of PtUiHitDiscInd */


/*
*
*       Fun:   Portable disconnection confirm
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PRIVATE S16 PtUiHitDiscCfm
(
Pst *pst,                 /* post strauchire */
SpId suId,                /* service user SAP ID */
U8 choice,                /* choice parameter */
UConnId conId,            /* connection ID */
Action action             /* action */
)
#else
PRIVATE S16 PtUiHitDiscCfm(pst, suId, choice, conId, action)
Pst *pst;                 /* post strauchire */
SpId suId;                /* service user SAP ID */
U8 choice;                /* choice parameter */
UConnId conId;            /* connection ID */
Action action;            /* action */
#endif
{
   TRC3(PtUiHitDiscCfm);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(choice);
   UNUSED(conId);
   UNUSED(action);
   RETVALUE(ROK);
} /* end of PtUiHitDiscCfm */

#endif


/********************************************************************30**

         End of file:     hi_ptui.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:09 2015

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
----------- -------- ---- -----------------------------------------------
/main/3      ---      mrw    1. Initial version
 /main/3     ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
            sb042.102 hl     1. Added change for SHT interface
/main/4      ---   rsr/ag    1. Updated for Release of 1.3
*********************************************************************91*/
