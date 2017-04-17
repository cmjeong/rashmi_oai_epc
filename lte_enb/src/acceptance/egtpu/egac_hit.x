
/********************************************************************20**

     Name:    eGTP layer

     Type:    C Include file

     Desc:    This file contains the acc structures and 
              function prototypes

     File:    egac_hit.x

     Sid:      egac_hit.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:34 2015

     Prg:     an

*********************************************************************21*/
#ifndef __EGAC_HIT_X__
#define __EGAC_HIT_X__

#ifdef __cplusplus
extern "C" {
#endif
#include "ss_err.h"        /* errors --*/
#include "ss_dep.h"        /* implementation-specific --*/
#include "ss_queue.h"      /* queues --*/
#include "ss_task.h"       /* tasking --*/
#include "ss_msg.h"        /* messaging --*/
#include "ss_mem.h"        /* memory management interface --*/
#include "ss_gen.h"        /* general --*/

#include "ss_dep.x"        /* implementation-specific --*/
#include "ss_queue.x"      /* queues --*/
#include "ss_task.x"       /* tasking --*/
#include "ss_timer.x"      /* timers --*/
#include "ss_strm.x"       /* STREAMS --*/
#include "ss_msg.x"        /* messaging --*/
#include "ss_mem.x"        /* memory management interface --*/
#include "ss_drvr.x"       /* driver tasks --*/
#include "ss_gen.x"


/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.h"



/*******************************************************************
                  HIT Handler functions
*******************************************************************/



EXTERN S16 egAcHitDeInit ARGS((
Void
));

EXTERN S16 egAcHitInit ARGS((
Void
));

EXTERN S16 egAcHdlHitBndReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHitUbndReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHitServOpenReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 egAcHdlHitConReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 egAcHdlHitConRsp ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 egAcHdlHitDatReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 egAcHdlHitUDatReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHitDiscReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHitConInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 egAcHdlHitConCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));



EXTERN S16 egAcHdlHitBndCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 egAcHdlHitDatInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 egAcHdlHitUDatInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

#ifdef EGTP_U
EXTERN S16 egUAcHdlHitUDatInd ARGS((
CmXtaTCCb        *tcCb, 
CmXtaSpCb        *spCb));
#endif /* EGTP_U */

EXTERN S16 egAcHdlHitDiscInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 egAcHdlHitDiscCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHitFlcInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN CmXtaTCCb*  egAcHitTstCbFind ARGS ((Void));

EXTERN EgAcHitAssocCb* egAcHitAssocFindnCreate ARGS ((CmXtaTCCb    *tcCb, U32 assocIdx,
                                 UConnId suAssocId, UConnId spAssocId));

EXTERN EgAcHitAssocCb* egAcHitAssocFind ARGS ((CmXtaTCCb    *tcCb, U32 assocIdx));

EXTERN S16 egAcUtlHitCb ARGS((
CmXtaMsgQElm *qElm
));

/*-- eg003.201 : Added egAcSetAddr & Removed egAcHitAssocFind & egAcHitAssocFindnCreate, from eg006.102--*/
EXTERN S16  egAcSetAddr ARGS((CmXtaSpCb *spCb, CmTptAddr *lclAddr, CmTptAddr *remAddr ));


/**********************************************************************************
 DUMMY TUCL PRIMITIVES
**********************************************************************************/
EXTERN SpId egAcDmSmGetTSapIdFromProt ARGS((
U8    protType
));


EXTERN S16 DHiLiHitBndReq ARGS((
Pst *pst,
SuId suId,
SpId spId
));

EXTERN S16 DHiLiHitUbndReq ARGS((
Pst *pst,
SpId spId,
Reason reason
));

EXTERN S16 DHiLiHitServOpenReq ARGS((
Pst *pst,
SpId spId,
UConnId servConId,
CmTptAddr *servTAddr,
CmTptParam *tPar,
CmIcmpFilter *icmpFilter,
U8 srvcType
));

EXTERN S16 DHiLiHitConReq ARGS((
Pst *pst,
SpId spId,
UConnId suConId,
CmTptAddr *remAddr,
CmTptAddr *localAddr,
CmTptParam *tPar,
U8 srvcType
));

EXTERN S16 DHiLiHitConRsp ARGS((
Pst *pst,
SpId spId,
UConnId suConId,
UConnId spConId
));

EXTERN S16 DHiLiHitDatReq ARGS((
Pst *pst,
SpId spId,
UConnId spConId,
Buffer *mBuf
));

EXTERN S16 DHiLiHitUDatReq ARGS((
Pst *pst,
SpId spId,
UConnId spConId,
CmTptAddr *remAddr,
CmTptAddr *srcAddr,
CmIpHdrParm *hdrParm,
CmTptParam *tPar,
Buffer *mBuf
));

EXTERN S16 DHiLiHitDiscReq ARGS((
Pst *pst,
SpId spId,
U8 choice,
UConnId conId,
Action action,
CmTptParam *tPar
));

EXTERN U8 egAcDHiUpdSrvType ARGS((
U8 srvcType
));

#ifdef __cplusplus
}
#endif /* extern "C" */
 
#endif /* __EGAC_HIT_X__ */

/**********************************************************************

         End of file:     egac_hit.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:34 2015

**********************************************************************/

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
------------ -------- ---- ----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rss     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg003.201 psingh      1. Merged code from eg006.102 to Fix warnings 
*********************************************************************91*/
