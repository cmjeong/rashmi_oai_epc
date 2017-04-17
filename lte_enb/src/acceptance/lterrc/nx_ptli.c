
/**********************************************************************
 
     Name:     RRC User

     Type:     C source file

     Desc:     C source code for upper layer(RX) across NHU interface

     File:     nx_ptli.c

     Sid:      nx_ptli.c@@/main/3 - Fri Jul  1 01:13:25 2011

     Prg:      rer 
  
**********************************************************************/

/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000369     LTE RRC
*
*/

 
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
 
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */

#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_mblk.h"       /* Common Mem Allocation Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_lte.h"       /* Common LTE Defines */
#include "cm_pasn.h"       /* Common Pasn Defines */

#include "nhu_asn.h"       /* NHU interface ASN defines */
#include "nhu.h"           /* NHU Interface defines */
#include "lnh.h"           /* LRR Interface defines */


/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* Common library Definitions */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_mblk.x"       /* Common Mem Allocation */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"       /* Common LTE Defines */
#include "cm_pasn.x"       /* Common Pasn Definitions */

#include "nhu.x"           /* NHU Interface includes */
#include "lnh.x"           /* LRR Interface includes */

/* local defines */
#define MAXNXLI 3     /* Size of matrix used for LC/LWLC/TC/One for Dummy */

#ifdef NX
#if (!(defined(LWLCNXLINHU) && defined(LCNXLINHU)))
#define PTNXLINHU 1
#else
#ifndef NH
#define PTNXLINHU 1
#endif
#endif
#endif

#if (PTNXLINHU)
PRIVATE S16 PtLiNhuBndReq  ARGS(( Pst *pst, SuId suId, SpId spId ));
PRIVATE S16 PtLiNhuUbndReq ARGS(( Pst *pst, SpId spId, Reason reason ));
PRIVATE S16 PtLiNhuDatReq  ARGS(( Pst *pst, SpId spId, NhuDatReqSdus *nhuDatReqSdus ));
PRIVATE S16 PtLiNhuDatRsp  ARGS(( Pst *pst, SpId spId, NhuDatRspSdus *nhuDatRspSdus ));
PRIVATE S16 PtLiNhuCfgReq  ARGS(( Pst *pst, SpId spId, NhuCfgReqSdus *nhuCfgReqSdus ));
PRIVATE S16 PtLiNhuCnclUeReq  ARGS(( Pst *pst, SpId spId, NhuCellId cellId,
                                       NhuCrnti crnti ));
PRIVATE S16 PtLiNhuCellCfgReq  ARGS(( Pst *pst, SpId spId, NhuCellCfgReqSdus *nhuCellCfgReqSdus ));
PRIVATE S16 PtLiNhuDeleteTransReq  ARGS(( Pst *pst, SpId spId, 
                                          NhuCellId cellId, NhuCrnti ueId,      
                                          U32 transId ));
PRIVATE S16 PtLiNhuDecodeReq ARGS(( Pst     *pst,
                                    SuId     suId,
                                    NhuDecodeSduReq *nhuDecodeSduReq));
PRIVATE S16 PtLiNhuCountReq ARGS((  Pst     *pst,
                                    SuId     suId,
                                    NhuHdr *countHdr));
PRIVATE S16 PtLiNhuEncodeReq ARGS(( Pst     *pst,
                                    SuId     suId,
                                    NhuEncReqSdus *nhuEncReqSdus));
PRIVATE S16 PtLiNhuPdcpSduStaReq ARGS((Pst  *pst,
                                       SpId spId,
                                       NhuHdr hdr));
#endif /* PTNXLINHU */


/* Bind Request Primitive */
PUBLIC NhuBndReq NxLiNhuBndReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuBndReq,            /* 0 - loosely coupled */
#else
   PtLiNhuBndReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuBndReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuBndReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuBndReq            /* 1 - light weight loosely coupled */
#else
   PtLiNhuBndReq            /* 1 - light weight loosely coupled,portable */
#endif
};

/* Unbind Request Primitive */
PUBLIC NhuUbndReq NxLiNhuUbndReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuUbndReq,            /* 0 - loosely coupled */
#else
   PtLiNhuUbndReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuUbndReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuUbndReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuUbndReq            /* 1 - light weight loosely coupled */
#else
   PtLiNhuUbndReq            /* 1 - light weight loosely coupled,portable */
#endif
};

/* Data Request Primitive */
PUBLIC NhuDatReq NxLiNhuDatReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuDatReq,            /* 0 - loosely coupled */
#else
   PtLiNhuDatReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuDatReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuDatReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuDatReq            /* 1 - light weight loosely coupled */
#else
   PtLiNhuDatReq            /* 1 - light weight loosely coupled,portable */
#endif
};

/* Data Response Primitive */ 
PUBLIC NhuDatRsp NxLiNhuDatRspMt [MAXNXLI] = 
{ 
#if (defined(LCNXLINHU)) 
   cmPkNhuDatRsp,            /* 0 - loosely coupled */
#else 
   PtLiNhuDatRsp,            /* 0 - loosely coupled,portable */
#endif 
#ifdef NH 
   NhUiNhuDatRsp,            /* 2 - tightly coupled,stub layer */
#else 
   PtLiNhuDatRsp,            /* 2 - tightly coupled,portable */
#endif 
#if (defined(LWLCNXLINHU)) 
   cmPkNhuDatRsp            /* 1 - light weight loosely coupled */
#else 
   PtLiNhuDatRsp            /* 1 - light weight loosely coupled,portable */
#endif 
};

/* Delete Transaction Request Primitive */
PUBLIC NhuDeleteTransReq NxLiNhuDeleteTransReqMt[MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuDeleteTransReq,      /* 0 - loosely coupled */
#else
   PtLiNhuDeleteTransReq,      /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuDeleteTransReq,      /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuDeleteTransReq,      /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuDeleteTransReq,      /* 1 - light weight loosely coupled */
#else
   PtLiNhuDeleteTransReq       /* 1 - light weight loosely coupled,portable */
#endif
};

/* Configuration Request Primitive */
PUBLIC NhuCfgReq NxLiNhuCfgReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuCfgReq,            /* 0 - loosely coupled */
#else
   PtLiNhuCfgReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuCfgReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuCfgReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuCfgReq            /* 1 - light weight loosely coupled */
#else
   PtLiNhuCfgReq            /* 1 - light weight loosely coupled,portable */
#endif
};

/* Cancel UE Request primitive */
PUBLIC NhuCnclUeReq NxLiNhuCnclUeReqMt [MAXNXLI] =
{ 
#if (defined(LCNXLINHU))
   cmPkNhuCnclUeReq,            /* 0 - loosely coupled */
#else 
   PtLiNhuCnclUeReq,            /* 0 - loosely coupled,portable */
#endif 
#ifdef NH
   NhUiNhuCnclUeReq,              /* 2 - tightly coupled,stub layer */
#else 
   PtLiNhuCnclUeReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuCnclUeReq            /* 1 - loosely coupled */
#else 
   PtLiNhuCnclUeReq            /* 1 - loosely coupled,portable */
#endif 
};

/* Cell Config Request primitive */
PUBLIC NhuCellCfgReq NxLiNhuCellCfgReqMt [MAXNXLI] =
{ 
#if (defined(LCNXLINHU))
   cmPkNhuCellCfgReq,            /* 0 - loosely coupled */
#else 
   PtLiNhuCellCfgReq,            /* 0 - loosely coupled,portable */
#endif 
#ifdef NH
   NhUiNhuCellCfgReq,            /* 2 - tightly coupled,stub layer */
#else 
   PtLiNhuCellCfgReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuCellCfgReq            /* 1 - loosely coupled */
#else 
   PtLiNhuCellCfgReq            /* 1 - loosely coupled,portable */
#endif 
};

/* Decode Request Primitive */
PUBLIC NhuDecodeReq NxLiNhuDecodeReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuDecodeReq,            /* 0 - loosely coupled */
#else
   PtLiNhuDecodeReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuDecodeReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuDecodeReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuDecodeReq            /* 1 - light weight loosely coupled */
#else
   PtLiNhuDecodeReq            /* 1 - light weight loosely coupled,portable */
#endif
};

/* Count Request Primitive */
PUBLIC NhuCountReq NxLiNhuCountReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuCountReq,            /* 0 - loosely coupled */
#else
   PtLiNhuCountReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuCountReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuCountReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuCountReq            /* 1 - light weight loosely coupled */
#else
   PtLiNhuCountReq            /* 1 - light weight loosely coupled,portable */
#endif
};

/* Enocde Request Primitive */
PUBLIC NhuEncReq NxLiNhuEncodeReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuEncodeReq,            /* 0 - loosely coupled */
#else
   PtLiNhuEncodeReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuEncodeReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuEncodeReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuEncodeReq            /* 1 - light weight loosely coupled */
#else
   PtLiNhuEncodeReq            /* 1 - light weight loosely coupled,portable */
#endif
};

/* SDU Status Request Primitive */
PUBLIC NhuSduStaReq NxLiNhuPdcpSduStaReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuPdcpSduStaReq,            /* 0 - loosely coupled */
#else
   PtLiNhuPdcpSduStaReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuPdcpSduStaReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuPdcpSduStaReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuPdcpSduStaReq            /* 1 - light weight loosely coupled */
#else
   PtLiNhuPdcpSduStaReq            /* 1 - light weight loosely coupled,portable */
#endif
};

/* Data Forward Request Primitive */
PUBLIC NhuDataFwdReq NxLiNhuPdcpDatFwdReqMt [MAXNXLI] =
{
#if (defined(LCNXLINHU))
   cmPkNhuStartPdcpDataFwdReq,            /* 0 - loosely coupled */
#else
   PtLiNhuPdcpSduStaReq,            /* 0 - loosely coupled,portable */
#endif
#ifdef NH
   NhUiNhuStartPdcpDataFwdReq,            /* 2 - tightly coupled,stub layer */
#else
   PtLiNhuPdcpSduStaReq,            /* 2 - tightly coupled,portable */
#endif
#if (defined(LWLCNXLINHU))
   cmPkNhuStartPdcpDataFwdReq             /* 1 - light weight loosely coupled */
#else
   PtLiNhuPdcpSduStaReq            /* 1 - light weight loosely coupled,portable */
#endif
};



#if (PTNXLINHU)
/**************************************************************************
 *
 *      Fun:   PtLiNhuBndReq
 *
 *      Desc:  Bind Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuBndReq
(
Pst    *pst,     /* post structure */
SuId   suId,     /* NHU serivce user SAP ID */ 
SpId   spId      /* NHU SAP ID */
)
#else
PUBLIC S16 PtLiNhuBndReq(pst, suId, spId)
Pst    *pst;     /* post structure */
SuId   suId;     /* NHU serivce user SAP ID */ 
SpId   spId;     /* NHU SAP ID */
#endif
{
   TRC3(PtLiNhuBndReq)
   RETVALUE(ROK);
} /* PtLiNhuBndReq */

/**************************************************************************
 * 
 *      Fun:   PtLiNhuUbndReq 
 * 
 *      Desc:  UnBind Request from RRC User to RRC
 * 
 *      Ret:   ROK - ok 
 * 
 *      Notes: None 
 * 
 *      File:  nx_ptli.c 
 * 
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuUbndReq
(
Pst          *pst,     /* post structure */
SpId         spId,     /* NHU SAP ID */
Reason       reason    /* Reason for Unbind */
)
#else
PUBLIC S16 PtLiNhuUbndReq(pst, spId, reason)
Pst          *pst;     /* post structure */
SpId         spId;     /* NHU SAP ID */
Reason       reason;   /* Reason for Unbind */
#endif
{ 
   TRC3(PtLiNhuUbndReq) 
 
   RETVALUE(ROK); 
} /* PtLiNhuUbndReq */


/**************************************************************************
 *
 *      Fun:   PtLiNhuDatReq
 *
 *      Desc:  Data Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuDatReq
(
Pst             *pst,            /* post structure */
SpId            spId,            /* RRC Service provider SAP ID */
NhuDatReqSdus   *nhuDatReqSdus   /* SDU */
)
#else
PUBLIC S16 PtLiNhuDatReq(pst, spId, nhuDatReqSdus)
Pst             *pst;             /* post structure */
SpId            spId;             /* RRC Service provider SAP ID */
NhuDatReqSdus   *nhuDatReqSdus;   /* SDU */
#endif
{
   TRC3(PtLiNhuDatReq)

 
   RETVALUE(ROK);

} /* PtLiNhuDatReq */

/**************************************************************************
 *
 *      Fun:   PtLiNhuDatRsp
 *
 *      Desc:  Data Response from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 * 
 *      File:  nx_ptli.c
 * 
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuDatRsp
(
Pst      *pst, 
SpId     spId,  
NhuDatRspSdus *nhuDatRspSdus
)
#else
PUBLIC S16 PtLiNhuDatRsp(pst, spId, nhuDatRspSdus)
Pst      *pst; 
SpId     spId;  
NhuDatRspSdus *nhuDatRspSdus;
#endif
{ 
   TRC3(PtLiNhuDatRsp)
 
   RETVALUE(ROK); 
} /* PtLiNhuDatRsp */

/**************************************************************************
 *
 *      Fun:   PtLiNhuDeleteTransReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtLiNhuDeleteTransReq
(
Pst        *pst,       /* Post Structure */
SpId       spId,       /* Service Provider Id */
NhuCellId  cellId,     /* Cell ID */
NhuCrnti   ueId,       /* Ue Id */
U32        transId     /* transaction id */
)
#else
PRIVATE S16 PtLiNhuDeleteTransReq(pst, spId, cellId, ueId, transId)
Pst        *pst;       /* Post Structure */
SpId       spId;       /* Service Provider Id */
NhuCellId  cellId;     /* Cell ID */
NhuCrnti   ueId;       /* Ue Id */
U32        transId;    /* Trans id */
#endif
{
   TRC3(PtLiNhuDeleteTransReq)
 
   RETVALUE(ROK); 
}
 
/**************************************************************************
 *
 *      Fun:   PtLiNhuCfgReq
 *
 *      Desc:  Config Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
 #ifdef ANSI
PUBLIC S16 PtLiNhuCfgReq
(
Pst             *pst,
SpId            spId,
NhuCfgReqSdus   *nhuCfgReqSdus
)
#else
PUBLIC S16 PtLiNhuCfgReq(pst, spId, nhuCfgReqSdus)
Pst             *pst;
SpId            spId;
NhuCfgReqSdus   *nhuCfgReqSdus;
#endif
{
   TRC3(PtLiNhuCfgReq)
   RETVALUE(ROK); 
} /* PtLiNhuCfgReq */ 

/**************************************************************************
 *
 *      Fun:   PtLiNhuCnclUeReq
 * 
 *      Desc:  Cancel UE Request from RRC User to RRC
 * 
 *      Ret:   ROK - ok 
 * 
 *      Notes: None 
 * 
 *      File:  nx_ptli.c 
 * 
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuCnclUeReq
(
Pst         *pst,
SpId        spId,
NhuCellId   cellId,
NhuCrnti    crnti
)
#else
PUBLIC S16 PtLiNhuCnclUeReq(pst, spId, cellId, crnti)
Pst *pst;
SpId spId;
NhuCellId   cellId;
NhuCrnti    crnti;
#endif
{ 
   TRC3(PtLiNhuCnclUeReq)
 
 
   RETVALUE(ROK); 
 
} /* PtLiNhuCnclUeReq */

/**************************************************************************
 *
 *      Fun:   PtLiNhuCellCfgReq
 * 
 *      Desc:  SCCPCH Config Request from RRC User to RRC
 * 
 *      Ret:   ROK - ok 
 * 
 *      Notes: None 
 * 
 *      File:  nx_ptli.c 
 * 
 *************************************************************************/
 #ifdef ANSI
PUBLIC S16 PtLiNhuCellCfgReq
(
Pst *pst,
SpId spId,
NhuCellCfgReqSdus *nhuCellCfgReqSdus
)
#else
PUBLIC S16 PtLiNhuCellCfgReq(pst, spId, nhuCellCfgReqSdus)
Pst                 *pst;
SpId                spId;
NhuCellCfgReqSdus   *nhuCellCfgReqSdus;
#endif
{ 
   TRC3(PtLiNhuCellCfgReq)
   RETVALUE(ROK); 
} /* PtLiNhuCellCfgReq */


/**************************************************************************
 *
 *      Fun:   PtLiNhuDecodeReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuDecodeReq
(
Pst     *pst,
SuId     suId,
NhuDecodeSduReq *nhuDecodeSduReq
)
#else
PUBLIC S16 PtLiNhuDecodeReq(pst, suId, nhuDecodeSduReq)
Pst     *pst;
SuId     suId;
NhuDecodeSduReq *nhuDecodeSduReq;
#endif
{
   TRC3(PtLiNhuDecodeReq)
   RETVALUE(ROK);
}

/**************************************************************************
 *
 *      Fun:   PtLiNhuCountReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuCountReq
(
Pst     *pst,
SuId     suId,
NhuHdr *countHdr
)
#else
PUBLIC S16 PtLiNhuCountReq(pst, suId, countHdr)
Pst     *pst;
SuId     suId;
NhuHdr *countHdr;
#endif
{
   TRC3(PtLiNhuCountReq)
   RETVALUE(ROK);
}

/**************************************************************************
 *
 *      Fun:   PtLiNhuEncodeReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuEncodeReq
(
Pst     *pst,
SuId     suId,
NhuEncReqSdus *nhuEncReqSdus
)
#else
PUBLIC S16 PtLiNhuEncodeReq(pst, suId, nhuEncReqSdus)
Pst     *pst;
SuId     suId;
NhuEncReqSdus *nhuEncReqSdus;
#endif
{
   TRC3(PtLiNhuEncodeReq)
   RETVALUE(ROK);
}

/**************************************************************************
 *
 *      Fun:   PtLiNhuPdcpSduStaReq
 *
 *      Desc:  PDCP Sdu Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiNhuPdcpSduStaReq
(
Pst     *pst,
SuId    suId,
NhuHdr  nhuHdr
)
#else
PUBLIC S16 PtLiNhuPdcpSduStaReq(pst, suId, nhuHdr)
Pst     *pst;
SuId    suId;
NhuHdr  nhuHdr;
#endif
{
   TRC3(PtLiNhuPdcpSduStaReq)
   RETVALUE(ROK);
}

#endif /* PTNXLINHU */

/* LI primtives for NHU  */

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

EXTERN S16 NxLiNhuBndReq  ARGS(( Pst *pst, SuId suId, SpId spId ));
EXTERN S16 NxLiNhuUbndReq ARGS(( Pst *pst, SpId spId, Reason reason ));
EXTERN S16 NxLiNhuDatReq  ARGS(( Pst *pst, SpId spId, NhuDatReqSdus *nhuDatReqSdus ));
EXTERN S16 NxLiNhuDatRsp  ARGS(( Pst *pst, SpId spId, NhuDatRspSdus *nhuDatRspSdus ));
EXTERN S16 NxLiNhuCfgReq  ARGS(( Pst *pst, SpId spId, NhuCfgReqSdus *nhuCfgReqSdus ));
EXTERN S16 NxLiNhuCnclUeReq  ARGS(( Pst *pst, SpId spId, NhuCellId cellId,
                                       NhuCrnti crnti ));
EXTERN S16 NxLiNhuCellCfgReq  ARGS(( Pst *pst, SpId spId, NhuCellCfgReqSdus *nhuCellCfgReqSdus ));
EXTERN S16 NxLiNhuDeleteTransReq  ARGS(( Pst *pst, SpId spId, 
                                         NhuCellId cellId, NhuCrnti ueId,      
                                         U32 transId ));

EXTERN S16 NxLiNhuDecodeReq ARGS(( Pst     *pst, SuId     suId, NhuDecodeSduReq *nhuDecodeSduReq));
EXTERN S16 NxLiNhuCountReq ARGS(( Pst     *pst, SuId     suId, NhuHdr *countHdr));
EXTERN S16 NxLiNhuEncodeReq ARGS(( Pst     *pst, SuId     suId, NhuEncReqSdus *nhuEncReqSdus));
EXTERN S16 NxLiNhuPdcpSduStaReq ARGS((Pst     *pst, SuId    suId, NhuHdr  nhuHdr));
EXTERN S16 NxLiNhuPdcpDatFwdReq ARGS((Pst     *pst,SuId     suId,NhuHdr   nhuHeader));

/* 
* 
*       Fun:   lower interface - Bind Request
*  
*       Desc:  This function indicates the receipt of a bind request  
*  
*       Ret:   ROK      - ok
* 
*       Notes: None 
* 
*       File:  
*        
*/
#ifdef ANSI
PUBLIC S16 NxLiNhuBndReq
(
Pst    *pst,     /* post structure */
SuId   suId,     /* NHU serivce user SAP ID */ 
SpId   spId      /* NHU SAP ID */
)
#else
PUBLIC S16 NxLiNhuBndReq(pst, suId, spId)
Pst    *pst;     /* post structure */
SuId   suId;     /* NHU serivce user SAP ID */ 
SpId   spId;     /* NHU SAP ID */
#endif
{
   TRC2(NxLiNhuBndReq)

   RETVALUE((*NxLiNhuBndReqMt[pst->selector])(pst, suId, spId));
} /* end of NxLiNhuBndReq */


/* 
* 
*       Fun:   lower interface - Unbind Request
*  
*       Desc:  This function indicates the receipt of a bind request  
*  
*       Ret:   ROK      - ok
* 
*       Notes: None 
* 
*       File:  
*        
*/
#ifdef ANSI
PUBLIC S16 NxLiNhuUbndReq
(
Pst          *pst,     /* post structure */
SpId         spId,     /* NHU SAP ID */
Reason       reason    /* Reason for Unbind */
)
#else
PUBLIC S16 NxLiNhuUbndReq(pst, spId, reason)
Pst          *pst;     /* post structure */
SpId         spId;     /* NHU SAP ID */
Reason       reason;   /* Reason for Unbind */
#endif
{
   TRC2(NxLiNhuUbndReq)

   RETVALUE((*NxLiNhuUbndReqMt[pst->selector])(pst, spId, reason));

} /* end of NxLiNhuUbndReq */

/* 
* 
*       Fun:   lower interface - Dat Request
*  
*       Desc:   
*  
*       Ret:   ROK      - ok
* 
*       Notes: None 
* 
*       File:  
*        
*/
#ifdef ANSI
PUBLIC S16 NxLiNhuDatReq
(
Pst             *pst,            /* post structure */
SpId            spId,            /* RRC Service provider SAP ID */
NhuDatReqSdus   *nhuDatReqSdus   /* SDU */
)
#else
PUBLIC S16 NxLiNhuDatReq(pst, spId, nhuDatReqSdus)
Pst             *pst;             /* post structure */
SpId            spId;             /* RRC Service provider SAP ID */
NhuDatReqSdus   *nhuDatReqSdus;   /* SDU */
#endif
{
   TRC3(NxLiNhuDatReq);

   RETVALUE((*NxLiNhuDatReqMt[pst->selector])(pst, spId, nhuDatReqSdus));
   
} /* end of function NxLiNhuDatReq */

/* 
* 
*       Fun:   lower interface - Dat Response
*  
*       Desc:    
*  
*       Ret:   ROK      - ok
* 
*       Notes: None 
* 
*       File:  
*        
*/
#ifdef ANSI
PUBLIC S16 NxLiNhuDatRsp
(
Pst      *pst, 
SpId     spId,  
NhuDatRspSdus *nhuDatRspSdus
)
#else
PUBLIC S16 NxLiNhuDatRsp(pst, spId, nhuDatRspSdus)
Pst      *pst; 
SpId     spId;  
NhuDatRspSdus *nhuDatRspSdus;
#endif
{
   TRC3(NxLiNhuDatRsp);

   RETVALUE((*NxLiNhuDatRspMt[pst->selector])(pst, spId, nhuDatRspSdus));

} /* end of function NhUiNhuDatRsp */


/* 
* 
*       Fun:   lower interface - Configuration Request
*  
*       Desc:   
*  
*       Ret:   ROK      - ok
* 
*       Notes: None 
* 
*       File:  
*        
*/
#ifdef ANSI
PUBLIC S16 NxLiNhuCfgReq
(
Pst             *pst,
SpId            spId,
NhuCfgReqSdus   *nhuCfgReqSdus
)
#else
PUBLIC S16 NxLiNhuCfgReq(pst, spId, nhuCfgReqSdus)
Pst             *pst;
SpId            spId;
NhuCfgReqSdus   *nhuCfgReqSdus;
#endif
{
   TRC3(NxLiNhuCfgReq);

   RETVALUE((*NxLiNhuCfgReqMt[pst->selector])(pst, spId, nhuCfgReqSdus));

} /* end of function NxLiNhuCfgReq */

/* 
* 
*       Fun:   lower interface - Cancel UE Request
*  
*       Desc:   
*  
*       Ret:   ROK      - ok
* 
*       Notes: None 
* 
*       File:  
*        
*/
#ifdef ANSI
PUBLIC S16 NxLiNhuCnclUeReq
(
Pst         *pst,
SpId        spId,
NhuCellId   cellId,
NhuCrnti    crnti
)
#else
PUBLIC S16 NxLiNhuCnclUeReq(pst, spId, cellId, crnti)
Pst *pst;
SpId spId;
NhuCellId   cellId;
NhuCrnti    crnti;
#endif
{
   TRC3(NxLiNhuCnclUeReq);

   RETVALUE((*NxLiNhuCnclUeReqMt[pst->selector])(pst, spId, cellId, crnti));

} /* end of function NxLiNhuCnclUeReq */

/*
*
*       Fun:   lower interface - Cell Config Request
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:
*
*/
#ifdef ANSI
PUBLIC S16 NxLiNhuCellCfgReq
(
Pst *pst,
SpId spId,
NhuCellCfgReqSdus *nhuCellCfgReqSdus
)
#else
PUBLIC S16 NxLiNhuCellCfgReq(pst, spId, nhuCellCfgReqSdus)
Pst                 *pst;
SpId                spId;
NhuCellCfgReqSdus   *nhuCellCfgReqSdus;
#endif
{
   TRC3(NxLiNhuCellCfgReq);

   RETVALUE((*NxLiNhuCellCfgReqMt[pst->selector])(pst, spId, nhuCellCfgReqSdus));

} /* end of function NxLiNhuCellCfgReq */

/**************************************************************************
 *
 *      Fun:   NxLiNhuDeleteTransReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 NxLiNhuDeleteTransReq
(
Pst        *pst,       /* Post Structure */
SpId       spId,       /* Service Provider Id */
NhuCellId  cellId,     /* Cell ID */
NhuCrnti   ueId,       /* Ue Id */
U32        transId     /* transaction id */
)
#else
PUBLIC S16 NxLiNhuDeleteTransReq(pst, spId, cellId, ueId, transId)
Pst        *pst;       /* Post Structure */
SpId       spId;       /* Service Provider Id */
NhuCellId  cellId;     /* Cell ID */
NhuCrnti   ueId;       /* Ue Id */
U32        transId;    /* Trans id */
#endif
{
   TRC3(NxLiNhuDeleteTransReq)
 
   RETVALUE((*NxLiNhuDeleteTransReqMt[pst->selector])(pst, spId, cellId, ueId, transId)); 
}

/**************************************************************************
 *
 *      Fun:   NxLiNhuDecodeReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 NxLiNhuDecodeReq
(
Pst     *pst,
SuId     suId,
NhuDecodeSduReq *nhuDecodeSduReq
)
#else
PUBLIC S16 NxLiNhuDecodeReq(pst, suId, nhuDecodeSduReq)
Pst     *pst;
SuId     suId;
NhuDecodeSduReq *nhuDecodeSduReq;
#endif
{
   TRC3(NxLiNhuDecodeReq)

   RETVALUE((*NxLiNhuDecodeReqMt[pst->selector])(pst, suId, nhuDecodeSduReq));
}

/**************************************************************************
 *
 *      Fun:   NxLiNhuCountReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 NxLiNhuCountReq
(
Pst     *pst,
SuId     suId,
NhuHdr *countHdr
)
#else
PUBLIC S16 NxLiNhuCountReq(pst, suId, countHdr)
Pst     *pst;
SuId     suId;
NhuHdr *countHdr;
#endif
{
   TRC3(NxLiNhuCountReq)

   RETVALUE((*NxLiNhuCountReqMt[pst->selector])(pst, suId, countHdr));
}

/**************************************************************************
 *
 *      Fun:   NxLiNhuEncodeReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 NxLiNhuEncodeReq
(
Pst     *pst,
SuId     suId,
NhuEncReqSdus *nhuEncReqSdus
)
#else
PUBLIC S16 NxLiNhuEncodeReq(pst, suId, nhuEncReqSdus)
Pst     *pst;
SuId     suId;
NhuEncReqSdus *nhuEncReqSdus;
#endif
{
   TRC3(NxLiNhuEncodeReq)

   RETVALUE((*NxLiNhuEncodeReqMt[pst->selector])(pst, suId, nhuEncReqSdus));
}

/**************************************************************************
 *
 *      Fun:   NxLiNhuPdcpSduStaReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 NxLiNhuPdcpSduStaReq
(
Pst     *pst,
SuId    suId,
NhuHdr  nhuHdr
)
#else
PUBLIC S16 NxLiNhuPdcpSduStaReq(pst, suId, nhuHdr)
Pst     *pst;
SuId    suId;
NhuHdr  nhuHdr;
#endif
{
   TRC3(NxLiNhuPdcpSduStaReq)

   RETVALUE((*NxLiNhuPdcpSduStaReqMt[pst->selector])(pst, suId, nhuHdr));
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
/**************************************************************************
 *
 *      Fun:   NxLiNhuPdcpDatFwdReq
 *
 *      Desc:  Delete Trans Request from RRC User to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ptli.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 NxLiNhuPdcpDatFwdReq
(
Pst     *pst,
SuId     suId,
NhuHdr   nhuHeader
)
#else
PUBLIC S16 NxLiNhuPdcpDatFwdReq(pst, suId, nhuEncReqSdus)
Pst     *pst;
SuId     suId;
NhuHdr   nhuHeader
#endif
{
   TRC3(NxLiNhuEncodeReq)

   RETVALUE((*NxLiNhuPdcpDatFwdReqMt[pst->selector])(pst, suId, nhuHeader));
}


/**********************************************************************
 
         End of file:     nx_ptli.c@@/main/3 - Fri Jul  1 01:13:25 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
    ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer              1. LTE RRC Initial Release.
/main/2      ---     chebli           1. LTE RRC release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

