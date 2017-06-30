

/********************************************************************20**

     Name:     it_ptli.c - SCTP layer portable upper layer interface

     Type:     C source file

     Desc:     C source code for the outgoing upper layer primitives (originating at
               the service user) used in loosely/tightly coupled systems. The two sections
               of the file is:
               - The setting up of the primitive mapping table
               - Transmission of the primitives using the mapping table.

     File:     it_ptli.c

     Sid:      it_ptli.c@@/main/4 - Thu Jul 26 07:53:52 2007

     Prg:      mrw

*********************************************************************21*/

/*

  it_ptli.c -

Following public functions are provided in this file:
 * ItLiSctBndReq            - Bind request
 * ItLiSctEndpOpenReq       - Open endpoint request
 * ItLiSctEndpCloseReq      - Close endpoint request
 * ItLiSctAssocReq          - Association Establish request
 * ItLiSctAssocRsp          - Association Establish response
 * ItLiSctTermReq           - Association Termination request
 * ItLiSctSetPriReq         - Set Primary Destination Network Address request
 * ItLiSctHBeatReq          - Enable/Disable Heartbeat request
 * ItLiSctDatReq            - Data request
 * ItLiSctStaReq            - Status request
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
#ifdef SB_INOP
#include "cm_os.h"       /* common hashing */
#endif
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */
#ifdef SB_ACC 
#include "sb_acc.h"
#endif
#ifdef SB_INOP
#include "sb_ibdy.h"
#endif


/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#ifdef SB_INOP
#include "cm_os.x"       /* common hashing */
#endif
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* Common DNS library */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#ifdef SB_ACC 
#include "sb_acc.x"
#endif
#ifdef SB_INOP
#include "sb_ibdy.x"    /* Typedefs for Inter-Op testing */
#endif

/* local defines */

#define MAXSBLI  2

#ifndef LCITLISCT
#define PTITLISCT
#else
#ifndef SB
#define PTITLISCT
#else
#endif
#endif

/* local typedefs */

/* local externs */

/* forward references */
#ifdef PTITLISCT
PRIVATE S16 PtLiSctBndReq   ARGS((Pst *pst, SuId suId, SpId spId ));
/* sb046: multihoming */
#ifdef SCT_ENDP_MULTI_IPADDR
PRIVATE S16 PtLiSctEndpOpenReq   ARGS((Pst *pst, SpId spId, UConnId suEndpId, SctPort port,
                                 SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
PRIVATE S16 PtLiSctEndpOpenReq   ARGS((Pst *pst, SpId spId, UConnId suEndpId, SctPort port,
                                 CmNetAddr *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */
PRIVATE S16 PtLiSctEndpCloseReq   ARGS((Pst *pst, SpId spId, UConnId endpId, U8 endpIdType ));
/* sb060.102: TOS changes */
#ifdef SCT3
PRIVATE S16 PtLiSctAssocReq ARGS((Pst *pst, SpId spId, UConnId spEndpId,
                         UConnId suAssocId, CmNetAddr *priDstNAddr,
                         SctPort dstPort, SctStrmId outStrms,
                         SctNetAddrLst *dstNAddrLst, SctNetAddrLst *srcNAddrLst,
                         SctTos tos, Buffer *vsInfo));
#else
PRIVATE S16 PtLiSctAssocReq ARGS((Pst *pst, SpId spId, UConnId spEndpId,
                         UConnId suAssocId, CmNetAddr *priDstNAddr,
                         SctPort dstPort, SctStrmId outStrms,
                         SctNetAddrLst *dstNAddrLst, SctNetAddrLst *srcNAddrLst,
                         Buffer *vsInfo));
#endif /* SCT3 */

/* sb060.102: TOS changes */
#ifdef SCT3
PRIVATE S16 PtLiSctAssocRsp   ARGS((Pst *pst, SpId spId,
                                    UConnId spEndpId,
                                    SctAssocIndParams *assocIndParams,
                                    SctTos tos, SctResult result, 
                                    Buffer *vsInfo));
#else
PRIVATE S16 PtLiSctAssocRsp   ARGS((Pst *pst, SpId spId,
                                    UConnId spEndpId,
                                    SctAssocIndParams *assocIndParams,
                                    SctResult result, Buffer *vsInfo));
#endif /* SCT3 */

PRIVATE S16 PtLiSctTermReq   ARGS((Pst *pst, SpId spId, UConnId assocId,
                             U8 assocIdType, Bool abrtFlg));
PRIVATE S16 PtLiSctSetPriReq   ARGS((Pst *pst, SpId spId, UConnId spAssocId,
                               CmNetAddr *dstNAddr ));
PRIVATE S16 PtLiSctHBeatReq ARGS((Pst *pst, SpId spId, UConnId spAssocId,
                            CmNetAddr *dstNAddr, U16 intervalTime, SctStatus status ));
PRIVATE S16 PtLiSctDatReq   ARGS((Pst *pst, SpId spId, UConnId spAssocId,
                            CmNetAddr *dstNAddr, SctStrmId strmId, Bool unorderFlg,
                            Bool nobundleFlg, U16 lifetime, U32 protId, Buffer *mBuf));
PRIVATE S16 PtLiSctStaReq   ARGS((Pst *pst, SpId spId, UConnId spAssocId,
                            CmNetAddr *dstNAddr, U8 staType ));
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
Every array is MAXSBLI long.

The dispatching is performed by the configurable variable: selector.
The selector is configured during general configuration.

The selectors are:

   0 - loosely coupled (#define LCITLISCT)
   1 - Lsb (#define SB)

The selectors are:

   0 - loosely coupled (#define LCITLISCT)
   1 - Lsb (#define SB)

*/

 /* Bind request Primitive */
PRIVATE SctBndReq ItLiSctBndReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
  cmPkSctBndReq,         /* 0 - loosely coupled  */
#else
   PtLiSctBndReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctBndReq,          /* 1 - tightly coupled, layer management */
#else
   PtLiSctBndReq           /* 1 - tightly coupled, portable */
#endif
};

/* Open endpoint request primitive */

PRIVATE SctEndpOpenReq ItLiSctEndpOpenReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctEndpOpenReq,     /* 0 - loosely coupled */
#else
   PtLiSctEndpOpenReq,     /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctEndpOpenReq,     /* 1 - tightly coupled, layer management */
#else
   PtLiSctEndpOpenReq      /* 1 - tightly coupled, portable */
#endif
};

/* Close endpoint request primitive */

PRIVATE SctEndpCloseReq ItLiSctEndpCloseReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctEndpCloseReq,     /* 0 - loosely coupled */
#else
   PtLiSctEndpCloseReq,     /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctEndpCloseReq,     /* 1 - tightly coupled, layer management */
#else
   PtLiSctEndpCloseReq      /* 1 - tightly coupled, portable */
#endif
};

/* Association request primitive */

PRIVATE SctAssocReq ItLiSctAssocReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctAssocReq,        /* 0 - loosely coupled */
#else
   PtLiSctAssocReq,        /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctAssocReq,        /* 1 - tightly coupled, layer management */
#else
   PtLiSctAssocReq        /* 1 - tightly coupled, portable */
#endif
};

/* Association response primitive */

PRIVATE SctAssocRsp ItLiSctAssocRspMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctAssocRsp,        /* 0 - loosely coupled */
#else
   PtLiSctAssocRsp,        /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctAssocRsp,        /* 1 - tightly coupled, layer management */
#else
   PtLiSctAssocRsp         /* 1 - tightly coupled, portable */
#endif
};

/* Association termination request primitive */

PRIVATE SctTermReq ItLiSctTermReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctTermReq,        /* 0 - loosely coupled */
#else
   PtLiSctTermReq,        /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctTermReq,        /* 1 - tightly coupled, layer management */
#else
   PtLiSctTermReq         /* 1 - tightly coupled, portable */
#endif
};

/* Set primary address request primitive */

PRIVATE SctSetPriReq ItLiSctSetPriReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctSetPriReq,       /* 0 - loosely coupled */
#else
   PtLiSctSetPriReq,       /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctSetPriReq,       /* 1 - tightly coupled, layer management */
#else
   PtLiSctSetPriReq        /* 1 - tightly coupled, portable */
#endif
};

/* Heartbeat request primitive */

PRIVATE SctHBeatReq ItLiSctHBeatReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctHBeatReq,        /* 0 - loosely coupled */
#else
   PtLiSctHBeatReq,        /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctHBeatReq,        /* 1 - tightly coupled, layer management */
#else
   PtLiSctHBeatReq         /* 1 - tightly coupled, portable */
#endif
};

/* Data request primitive */

PRIVATE SctDatReq ItLiSctDatReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctDatReq,          /* 0 - loosely coupled */
#else
   PtLiSctDatReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctDatReq,          /* 1 - tightly coupled, layer management */
#else
   PtLiSctDatReq          /* 1 - tightly coupled, portable */
#endif
};


/* Status request primitive */

PRIVATE SctStaReq ItLiSctStaReqMt[MAXSBLI] =
{
#ifdef LCITLISCT
   cmPkSctStaReq,         /* 0 - loosely coupled */
#else
   PtLiSctStaReq,         /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctStaReq,        /* 1 - tightly coupled, layer management */
#else
   PtLiSctStaReq         /* 1 - tightly coupled, portable */
#endif
};


/*
*     Upper layer interface functions
*/

/*
*
*       Fun:   Bind request
*
*       Desc:  This function is used to bind two upper SAPs.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  It_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 ItLiSctBndReq
(
Pst *pst,                 /* post structure */
SuId suId,                /* Su SAP Id */
SpId spId                 /* Sp SAP Id */
)
#else
PUBLIC S16 ItLiSctBndReq(pst, suId, spId)
Pst *pst;                 /* post structure */
SuId suId;                /* Su SAP Id */
SpId spId;                /* Sp SAP Id */
#endif
{
   TRC3(ItLiSctBndReq);
   /* jump to specific primitive depending on configured selector */
   /* (*ItLiSctBndReqMt[pst->selector])(pst, suId, spId); */
   (*ItLiSctBndReqMt[pst->selector])(pst, suId, spId);
   RETVALUE(ROK);
} /* end of ItLiSctBndReq */

/*
*
*       Fun:   Opening of endpoint request
*
*       Desc:  This function is used to request the opening of
*              an endpoint at the SCTP layer.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef ANSI
PUBLIC S16 ItLiSctEndpOpenReq
(
Pst *pst,                        /* post structure */
SpId spId,                       /* Service provider SAP Id */
UConnId suEndpId,                /* Service user Endpoint Id */
SctPort port,                    /* SCTP Port number */
SctNetAddrLst *intfNAddrLst      /* Interface IP address list */
)
#else
PUBLIC S16 ItLiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddrLst)
Pst *pst;                        /* post structure */
SpId spId;                       /* Service provider SAP Id */
UConnId suEndpId;                /* Service user Endpoint Id */
SctPort port;                    /* SCTP Port number */
SctNetAddrLst *intfNAddrLst;     /* Interface IP address list */
#endif
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef ANSI
PUBLIC S16 ItLiSctEndpOpenReq
(
Pst *pst,                        /* post structure */
SpId spId,                       /* Service provider SAP Id */
UConnId suEndpId,                /* Service user Endpoint Id */
SctPort port,                    /* SCTP Port number */
CmNetAddr *intfNAddr             /* Interface IP address   */
)
#else
PUBLIC S16 ItLiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddr)
Pst *pst;                        /* post structure */
SpId spId;                       /* Service provider SAP Id */
UConnId suEndpId;                /* Service user Endpoint Id */
SctPort port;                    /* SCTP Port number */
CmNetAddr *intfNAddr;            /* Interface IP address   */
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */
{
   TRC3(ItLiSctEndpOpenReq)
   /* jump to specific primitive depending on configured selector */
#ifdef SCT_ENDP_MULTI_IPADDR
   (*ItLiSctEndpOpenReqMt[pst->selector])(pst, spId, suEndpId, port, intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
   (*ItLiSctEndpOpenReqMt[pst->selector])(pst, spId, suEndpId, port, intfNAddr);
#endif /* SCT_ENDP_MULTI_IPADDR */
   RETVALUE(ROK);
} /* end of ItLiSctEndpOpenReq */

/*
*
*       Fun:   Endpoint closing request
*
*       Desc:  This function is used to send a request for the closing of the SCTP endpoint
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 ItLiSctEndpCloseReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAPID */
UConnId endpId,        /* service provider endpoint ID */
U8     endpIdType
)
#else
PUBLIC S16 ItLiSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAPID */
UConnId endpId;       /* service provider endpoint ID */
U8     endpIdType;
#endif
{
   TRC3(ItLiSctEndpCloseReq)
   /* jump to specific primitive depending on configured selector */
   (*ItLiSctEndpCloseReqMt[pst->selector])(pst, spId, endpId, endpIdType);
   RETVALUE(ROK);
} /* end of ItLiSctEndpCloseReq */

/*
*
*       Fun:   Association establishment request
*
*       Desc:  This function is used to send a request for the closing of the SCTP endpoint
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

/* sb060.102: TOS changes */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 ItLiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,          /* service provider endpoint ID */
UConnId suAssocId,         /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
SctPort dstPort,           /* destination port number */
SctStrmId outStrms,        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
SctTos tos,                 /* type of service */
Buffer *vsInfo              /* vendor specific info */
)
#else
PUBLIC S16 ItLiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, dstPort,
outStrms, dstNAddrLst, srcNAddrLst, tos, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;          /* service provider endpoint ID */
UConnId suAssocId;         /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
SctPort dstPort;           /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
SctTos tos;                 /* type of service */
Buffer *vsInfo;             /* vendor specific info */
#endif
#else /* SCT3 */
#ifdef ANSI
PUBLIC S16 ItLiSctAssocReq
(
Pst           *pst,                  /* post structure */
SpId          spId,                  /* service provider SAP ID */
UConnId       spEndpId,              /* service provider endpoint ID */
UConnId       suAssocId,             /* service userassociation ID */
CmNetAddr     *priDstNAddr,          /* primary destination network address */
SctPort       dstPort,               /* destination port number */
SctStrmId     outStrms,              /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst,          /* dest. network address list */
SctNetAddrLst *srcNAddrLst,         /* src. network address list */
Buffer        *vsInfo                /* VsInfo - not used any more */
)
#else
PUBLIC S16 ItLiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, dstPort,
                           outStrms, dstNAddrLst, srcNAddrLst, vsInfo)
Pst           *pst;                  /* post structure */
SpId          spId;                  /* service provider SAP ID */
UConnId       spEndpId;              /* service provider endpoint ID */
UConnId       suAssocId;             /* service userassociation ID */
CmNetAddr     *priDstNAddr;          /* primary destination network address */
SctPort       dstPort;               /* destination port number */
SctStrmId     outStrms;              /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst;          /* dest. network address list */
SctNetAddrLst *srcNAddrLst;          /* src. network address list */
Buffer        *vsInfo;               /* VsInfo - not used any more */
#endif
#endif /* SCT3 */
{
   TRC3(ItLiSctAssocReq)
   /* jump to specific primitive depending on configured selector */
/* sb060.102: TOS changes */
#ifdef SCT3
    (*ItLiSctAssocReqMt[pst->selector])(pst, spId, spEndpId, suAssocId,
                                        priDstNAddr, dstPort, outStrms,
                                        dstNAddrLst, srcNAddrLst,
                                        tos, vsInfo);
#else /* SCT3 */
    (*ItLiSctAssocReqMt[pst->selector])(pst, spId, spEndpId, suAssocId,
                                        priDstNAddr, dstPort, outStrms,
                                        dstNAddrLst, srcNAddrLst,
                                        vsInfo);
#endif /* SCT3 */
   RETVALUE(ROK);
} /* end of ItLiSctAssocReq */

/*
*
*       Fun:   Association Establishment response
*
*       Desc:  This function is used by the service user to respond to an association
*       initialization indication by accepting the association.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

/* sb060.102: TOS changes */
/*sb083.102: changes for non-ansi*/

#ifdef SCT3
#ifdef ANSI
PUBLIC S16 ItLiSctAssocRsp
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,         /* service provider association ID */
SctAssocIndParams *assocIndParams, /* association parameters */
SctTos tos,                /* type of service */
SctResult result,          /* result */
Buffer *vsInfo             /* vendor specific info */
)
#else
PUBLIC S16 ItLiSctAssocRsp(pst, spId, spEndpId, assocIndParams, tos, result, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctTos tos;                /* type of service */
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif
#else /* SCT3 */
#ifdef ANSI
PUBLIC S16 ItLiSctAssocRsp
(
Pst                 *pst,                   /* post structure */
SpId                spId,                   /* service provider SAP ID */
UConnId             spEndpId,               /* service provider endpoint ID */
SctAssocIndParams   *assocIndParams,        /*association indication parameters */
SctResult           result,                 /* results */
Buffer              *vsInfo                /* VsInfo - not used any more */
)
#else
PUBLIC S16 ItLiSctAssocRsp(pst, spId, spEndpId, assocIndParams, result, vsInfo)
Pst                 *pst;                   /* post structure */
SpId                spId;                   /* service provider SAP ID */
UConnId             spEndpId;               /* service provider endpoint ID */
SctAssocIndParams   *assocIndParams;        /*association indication parameters */
SctResult           result;                 /* results */
Buffer              *vsInfo;               /* VsInfo - not used any more */
#endif
#endif /* SCT3 */
{
   TRC3(ItLiSctAssocRsp)
   /* jump to specific primitive depending on configured selector */
/* sb060.102: TOS changes */
#ifdef SCT3
   (*ItLiSctAssocRspMt[pst->selector])(pst, spId, spEndpId,
                                       assocIndParams, tos,
                                       result, vsInfo);
#else /* SCT3 */
   (*ItLiSctAssocRspMt[pst->selector])(pst, spId, spEndpId,
                                       assocIndParams, result,
                                       vsInfo);
#endif /* SCT3 */
   RETVALUE(ROK);
} /* end of ItLiSctAssocRsp */

/*
*
*       Fun:   Association Termination Request
*
*       Desc:  This function is used to request the termination of an association
 *             which is either established or being established.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 ItLiSctTermReq
(
Pst      *pst,                  /* post structure */
SpId     spId,                  /* service provider SAP ID */
UConnId  assocId,               /* association ID */
U8       assocIdType,           /* association ID type */
Bool     abrtFlg                /* abort flag */
)
#else
PUBLIC S16 ItLiSctTermReq(pst, spId, assocId, assocIdType, abrtFlg)
Pst      *pst;                  /* post structure */
SpId     spId;                  /* service provider SAP ID */
UConnId  assocId;               /* association ID */
U8       assocIdType;           /* association ID type */
Bool     abrtFlg;               /* abort flag */
#endif
{
   TRC3(ItLiSctTermReq)

   /* jump to specific primitive depending on configured selector */
   (*ItLiSctTermReqMt[pst->selector])(pst, spId, assocId, assocIdType, abrtFlg);
   RETVALUE(ROK);
} /* end of ItLiSctTermReq */

/*
*
*       Fun:   Set primary Destination Network Address Request
*
*       Desc:  This function is used by the service user to set a destination network
 *             address as primary if multiple destination addresses are available.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 ItLiSctSetPriReq
(
Pst       *pst,                 /* post structure */
SpId      spId,                 /* service provider ID */
UConnId   spAssocId,            /* service provider association ID */
CmNetAddr *dstNAddr             /* dest. network address */
)
#else
PUBLIC S16 ItLiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst       *pst;                 /* post structure */
SpId      spId;                 /* service provider ID */
UConnId   spAssocId;            /* service provider association ID */
CmNetAddr *dstNAddr;            /* dest. network address */
#endif
{
   TRC3(ItLiSctSetPriReq)
   /* jump to specific primitive depending on configured selector */
   (*ItLiSctSetPriReqMt[pst->selector])(pst, spId, spAssocId, dstNAddr);
   RETVALUE(ROK);
} /* end of ItLiSctSetPriReq */

/*
*
*       Fun:   Enable/Disable Heartbeat request
*
*       Desc:  This function is used by the service user to enable/disable
*              heartbeat either on an association or on a destination transport
*              address in an association.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 ItLiSctHBeatReq
(
Pst        *pst,             /* post structure */
SpId       spId,             /* service provider SAP ID */
UConnId    spAssocId,        /* service provider association ID */
CmNetAddr  *dstNAddr,        /* dest. network address */
U16        intervalTime,     /* heartbeat periodicity value */
SctStatus  status            /* status */
)
#else
PUBLIC S16 ItLiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime, status)
Pst        *pst;            /* post structure */
SpId       spId;            /* service provider SAP ID */
UConnId    spAssocId;       /* service provider association ID */
CmNetAddr  *dstNAddr;       /* dest. network address */
U16        intervalTime;    /* heartbeat periodicity value */
SctStatus  status;          /* status */
#endif
{
   TRC3(ItLiSctHBeatReq)
   /* jump to specific primitive depending on configured selector */
   (*ItLiSctHBeatReqMt[pst->selector])(pst, spId, spAssocId, dstNAddr, intervalTime, status);
   RETVALUE(ROK);
} /* end of ItLiSctHBeatReq */


/*
*
*       Fun:   Data request
*
*       Desc:  This function is used to request the service provider to send a
*              user datagram to the destination.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 ItLiSctDatReq
(
Pst        *pst,                /* post structure */
SpId       spId,                /* service provider SAP ID */
UConnId    spAssocId,           /* service provider association ID */
CmNetAddr  *dstNAddr,           /* dest. network address */
SctStrmId  strmId,              /* stream ID */
Bool       unorderFlg,          /* unordered delivery flag */
Bool       nobundleFlg,         /* nobundleFlg */
U16        lifetime,            /* datagram lifetime */
U32        protId,              /*protocol ID */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 ItLiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg,
                         nobundleFlg, lifetime, protId, mBuf)
Pst        *pst;                 /* post structure */
SpId       spId;                 /* service provider SAP ID */
UConnId    spAssocId;            /* service provider association ID */
CmNetAddr  *dstNAddr;            /* dest. network address */
SctStrmId  strmId;               /* stream ID */
Bool       unorderFlg;           /* unordered delivery flag */
Bool       nobundleFlg;          /* nobundleFlg */
U16        lifetime;             /* datagram lifetime */
U32        protId;               /*protocol ID */
Buffer     *mBuf;                /* message buffer */
#endif
{
   TRC3(ItLiSctDatReq)
   /* jump to specific primitive depending on configured selector */
   (*ItLiSctDatReqMt[pst->selector])(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg,
    nobundleFlg, lifetime, protId, mBuf);
   RETVALUE(ROK);
} /* end of ItLiSctDatReq */


/*
*
*       Fun:   Status request
*
*       Desc:  This function is used to retrieve unsent/unacknowledged/undelivered
*             datagrams from the service provider and to get statistical information
*             from the service provider.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 ItLiSctStaReq
(
Pst         *pst,                 /* post structure */
SpId        spId,                 /* service provider SAP ID */
UConnId     spAssocId,            /* service provider association ID */
CmNetAddr   *dstNAddr,            /* dest. network address */
U8          staType               /* status type */
)
#else
PUBLIC S16 ItLiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst         *pst;                 /* post structure */
SpId        spId;                 /* service provider SAP ID */
UConnId     spAssocId;            /* service provider association ID */
CmNetAddr   *dstNAddr;            /* dest. network address */
U8          staType;              /* status type */
#endif
{
   TRC3(ItLiSctStaReq)
   /* jump to specific primitive depending on configured selector */
   (*ItLiSctStaReqMt[pst->selector])(pst, spId, spAssocId, dstNAddr, staType);

   RETVALUE(ROK);
} /* end of ItLiSctStaReq */


#ifdef PTITLISCT

/*
*
*       Fun:   Portable bind Request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctBndReq
(
Pst *pst,                 /* post structure */
SuId suId,                /* Service user SAP Id */
SpId spId                /* Service provider SAP Id */
)
#else
PRIVATE S16 PtLiSctBndReq(pst, suId, spId)
Pst *pst;                 /* post structure */
SuId suId;                /* Service user SAP Id */
SpId spId;                /* Service provider SAP Id */
#endif
{
   TRC3(PtLiSctBndReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);
   RETVALUE(ROK);
} /* end of PtLiSctBndReq */



/*
*
*       Fun:   Portable open endpoint request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef ANSI
PRIVATE S16 PtLiSctEndpOpenReq
(
Pst       *pst,                /* post structure */
SpId      spId,                /* Service provider SAP Id */
UConnId   suEndpId,            /* Service user Endpoint Id */
SctPort   port,                /* SCTP Port number */
SctNetAddrLst *intfNAddrLst      /* Interface IP address list */
)
#else
PRIVATE S16 PtLiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddrLst)
Pst       *pst;                /* post structure */
SpId      spId;                /* Service provider SAP Id */
UConnId   suEndpId;            /* Service user Endpoint Id */
SctPort   port;                /* SCTP Port number */
SctNetAddrLst *intfNAddrLst;     /* Interface IP address list */
#endif
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef ANSI
PRIVATE S16 PtLiSctEndpOpenReq
(
Pst       *pst,                /* post structure */
SpId      spId,                /* Service provider SAP Id */
UConnId   suEndpId,            /* Service user Endpoint Id */
SctPort   port,                /* SCTP Port number */
CmNetAddr *intfNAddr           /* Interface IP address   */
)
#else
PRIVATE S16 PtLiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddr)
Pst       *pst;                /* post structure */
SpId      spId;                /* Service provider SAP Id */
UConnId   suEndpId;            /* Service user Endpoint Id */
SctPort   port;                /* SCTP Port number */
CmNetAddr *intfNAddr;          /* Interface IP address   */
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */
{
   TRC3(PtLiSctEndpOpenReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(suEndpId);
   UNUSED(port);
#ifdef SCT_ENDP_MULTI_IPADDR
   UNUSED(intfNAddrLst);
#else /* SCT_ENDP_MULTI_IPADDR */
   UNUSED(intfNAddr);
#endif /* SCT_ENDP_MULTI_IPADDR */

   RETVALUE(ROK);
} /* end of PtLiSctEndpOpenReq */


/*
*
*       Fun:   Portable close endpoint request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctEndpCloseReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId endpId,          /* service provider endpoint ID */
U8     endpIdType
)
#else
PRIVATE S16 PtLiSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId endpId;         /* service provider endpoint ID */
U8     endpIdType;
#endif
{
   TRC3(PtLiSctEndpCloseReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(endpId);
   UNUSED(endpIdType);
   RETVALUE(ROK);
} /* end of PtLiSctEndpCloseReq */

/*
*
*       Fun:   Portable Association request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

/* sb060.102: TOS changes */
#ifdef SCT3
#ifdef ANSI
PRIVATE S16 PtLiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,        /* service provider endpoint ID */
UConnId suAssocId,      /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
U16 dstPort,               /* destination port number */
SctStrmId outStrms,        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
SctTos tos,                 /* type of service */
Buffer *vsInfo          /* vendor specific info */
)
#else
PRIVATE S16 PtLiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr,
                            dstPort, outStrms, dstNAddrLst, srcNAddrLst, tos, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;        /* service provider endpoint ID */
UConnId suAssocId;      /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
U16 dstPort;               /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
SctTos tos;                 /* type of service */
Buffer *vsInfo;          /* vendor specific info */
#endif
#else /* SCT3 */
#ifdef ANSI
PRIVATE S16 PtLiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,        /* service provider endpoint ID */
UConnId suAssocId,      /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
SctPort dstPort,               /* destination port number */
SctStrmId outStrms,         /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
Buffer        *vsInfo       /* VsInfo - not used any more */
)
#else
PRIVATE S16 PtLiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, dstPort, outStrms,
                            dstNAddrLst, srcNAddrLst, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;        /* service provider endpoint ID */
UConnId suAssocId;      /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
SctPort dstPort;               /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
Buffer        *vsInfo;      /* VsInfo - not used any more */
#endif
#endif /* SCT3 */
{
   TRC3(PtLiSctAssocReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spEndpId);
   UNUSED(suAssocId);
   UNUSED(priDstNAddr);
   UNUSED(dstPort);
   UNUSED(outStrms);
   UNUSED(dstNAddrLst);
   UNUSED(srcNAddrLst);
   UNUSED(vsInfo);
/* sb060.102: TOS changes */
#ifdef SCT3
   UNUSED(tos);
#endif /* SCT3 */

   RETVALUE(ROK);
} /* end of PtLiSctAssocReq */


/*
*
*       Fun:   Portable association response
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

/* sb060.102: TOS changes */
#ifdef SCT3
#ifdef ANSI
PRIVATE S16 PtLiSctAssocRsp
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,         /* service provider association ID */
SctAssocIndParams *assocIndParams, /* association parameters */
SctTos tos,                /* type of service */
SctResult result,          /* result */
Buffer *vsInfo             /* vendor specific info */
)
#else
PRIVATE S16 PtLiSctAssocRsp(pst, spId, spEndpId, assocIndParams, tos, result,
                            vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctTos tos;                /* type of service */
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif
#else /* SCT3 */
#ifdef ANSI
PRIVATE S16 PtLiSctAssocRsp
(
Pst                 *pst,                   /* post structure */
SpId                spId,                   /* service provider SAP ID */
UConnId             spEndpId,               /* service provider endpoint ID */
SctAssocIndParams   *assocIndParams,        /* assoc. indication parameters */
SctResult           result,                 /* result */
Buffer              *vsInfo                 /* VsInfo - not used any more */
)
#else
PRIVATE S16 PtLiSctAssocRsp(pst, spId, spEndpId, assocIndParams, result, vsInfo)
Pst                *pst;                    /* post structure */
SpId                spId;                   /* service provider SAP ID */
UConnId             spEndpId;               /* service provider endpoint ID */
SctAssocIndParams  *assocIndParams;         /* assoc. indication parameters */
SctResult           result;                 /* result */
Buffer             *vsInfo;                 /* VsInfo - not used any more */
#endif
#endif /* SCT3 */
{
   TRC3(PtLiSctAssocRsp);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spEndpId);
   UNUSED(result);
   UNUSED(assocIndParams);
   UNUSED(vsInfo);
/* sb060.102: TOS changes */
#ifdef SCT3
   UNUSED(tos);
#endif /* SCT3 */
   RETVALUE(ROK);
} /* end of PtLiSctAssocRsp */

/*
*
*       Fun:   Portable termination request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctTermReq
(
Pst       *pst,                 /* post structure */
SpId      spId,                 /* service provider SAP ID */
UConnId   assocId,              /* association ID */
U8        assocIdType,          /* association ID type */
Bool      abrtFlg               /* abort flag */
)
#else
PRIVATE S16 PtLiSctTermReq(pst, spId, assocId, assocIdType, abrtFlg)
Pst      *pst;                  /* post structure */
SpId     spId;                  /* service provider SAP ID */
UConnId  assocId;               /* association ID */
U8       assocIdType;           /* association ID type */
Bool     abrtFlg;               /* abort flag */
#endif
{
   TRC3(PtLiSctTermReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(assocId);
   UNUSED(assocIdType);
   UNUSED(abrtFlg);
   RETVALUE(ROK);
} /* end of PtLiSctTermReq */


/*
*
*       Fun:   Portable set primary address request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctSetPriReq
(
Pst       *pst,                /* post structure */
SpId      spId,                /* service provider ID */
UConnId   spAssocId,           /* service provider association ID */
CmNetAddr *dstNAddr            /* dest. network address */
)
#else
PRIVATE S16 PtLiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst       *pst;                 /* post structure */
SpId      spId;                 /* service provider ID */
UConnId   spAssocId;            /* service provider association ID */
CmNetAddr *dstNAddr;            /* dest. network address */
#endif
{
   TRC3(PtLiSctSetPriReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);

   RETVALUE(ROK);
} /* end of PtLiSctSetPriReq */

/*
*
*       Fun:   Portable heart beat request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctHBeatReq
(
Pst       *pst,           /* post structure */
SpId      spId,           /* service provider SAP ID */
UConnId   spAssocId,      /* service provider association ID */
CmNetAddr *dstNAddr,      /* dest. network address */
U16       intervalTime,   /* heartbeat periodicity value */
SctStatus status          /* status */
)
#else
PRIVATE S16 PtLiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime, status)
Pst       *pst;           /* post structure */
SpId      spId;           /* service provider SAP ID */
UConnId   spAssocId;      /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
U16       intervalTime;   /* heartbeat periodicity value */
SctStatus status;         /* status */
#endif
{
   TRC3(PtLiSctHBeatReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   UNUSED(intervalTime);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtLiSctHBeatReq */


/*
*
*       Fun:   Portable data Request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctDatReq
(
Pst        *pst,                 /* post structure */
SpId       spId,                 /* service provider SAP ID */
UConnId    spAssocId,            /* service provider association ID */
CmNetAddr  *dstNAddr,            /* dest. network address */
SctStrmId  strmId,               /* stream ID */
Bool       unorderFlg,           /* unordered delivery flag */
Bool       nobundleFlg,          /* nobundleFlg */
U16        lifetime,             /* datagram lifetime */
U32        protId,               /* protocol ID */
Buffer     *mBuf                 /* message buffer */
)
#else
PRIVATE S16 PtLiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg, nobundleFlg, lifetime, protId, mBuf)
Pst *pst;                        /* post structure */
SpId spId;                       /* service provider SAP ID */
UConnId spAssocId;               /* service provider association ID */
CmNetAddr *dstNAddr;             /* dest. network address */
SctStrmId strmId;                /* stream ID */
Bool unorderFlg;                 /* unordered delivery flag */
Bool nobundleFlg;                /* nobundleFlg */
U16 lifetime;                    /* datagram lifetime */
U32 protId;                      /* protocol ID */
Buffer *mBuf;                    /* message buffer */
#endif
{
   TRC3(PtLiSctDatReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   UNUSED(strmId);
   UNUSED(unorderFlg);
   UNUSED(nobundleFlg);
   UNUSED(lifetime);
   UNUSED(protId);
   UNUSED(mBuf);

   RETVALUE(ROK);
} /* end of PtLiSctDatReq */

/*
*
*       Fun:   Portable status request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctStaReq
(
Pst        *pst,                 /* post structure */
SpId       spId,                 /* service provider SAP ID */
UConnId    spAssocId,            /* service provider association ID */
CmNetAddr  *dstNAddr,            /* dest. network address */
U8         staType               /* status type */
)
#else
PRIVATE S16 PtLiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst        *pst;                 /* post structure */
SpId       spId;                 /* service provider SAP ID */
UConnId    spAssocId;            /* service provider association ID */
CmNetAddr  *dstNAddr;            /* dest. network address */
U8         staType;              /* status type */
#endif
{
   TRC3(PtLiSctStaReq);
   SBLOGINVSEL;
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   UNUSED(staType);
   RETVALUE(ROK);
} /* end of PtLiSctStaReq */

#endif /* PTITLISCT */

/********************************************************************30**

         End of file:     it_ptli.c@@/main/4 - Thu Jul 26 07:53:52 2007

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
1.1          ---      mrw  1. Initial version
/main/3      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
         sb046.102    hl   1. Multiple IP address per endpoint support
         sb060.102    pr   1. TOS changes.
         sb083.102    kp   1. Non-ANSI changes
/main/4      ---   rsr/ag  1. Updated for Release of 1.3
*********************************************************************91*/
