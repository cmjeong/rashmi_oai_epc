
/********************************************************************20**

     Name:    S1AP - acc test file for SCT interface

     Type:    C Include file

     Desc:    This file contains the acc structures and 
              function prototypes

     File:    czac_sct.x

     Sid:      czac_sct.x@@/main/2 - Tue Aug 30 18:35:55 2011

     Prg:     ms

*********************************************************************21*/
#ifndef __CZAC_SCT_X__
#define __CZAC_SCT_X__

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

#include "sct.h"
#include "sct.x"
#ifdef SB
#include "lsb.h"            /* SCTP */
#include "lsb.x"            /* SCTP */
#include "../../sctp/sb_mtu.h"         /* SCTP */
#include "../../sctp/sb_mtu.x"         /* SCTP */
#include "../../sctp/sb.h"             /* SCTP */
#include "../../sctp/sb.x"             /* SCTP */
#endif


/*******************************************************************
                  SCT Handler functions
*******************************************************************/

EXTERN S16 czAcHdlSctBndReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctEndpOpenReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));
       
EXTERN S16 czAcHdlSctEndpCloseReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctAssocReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctTermReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctSetPrimReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctHBeatReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctDatReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctStaReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctBndCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctEndpOpenCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctEndpCloseCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctAssocInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctAssocCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctTermInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctTermCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctSetPriCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctHBeatCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctDatInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctStaCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctStaInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 czAcHdlSctFlcInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctAssocRsp ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 czAcHdlSctSetPriReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN CzAcSctAssocCb* czAcSctAssocFindnCreate ARGS((
CmXtaTCCb    *tcCb,
U32   assocIdx,
UConnId   suAssocId,
UConnId   spAssocId
));

EXTERN CzAcSctAssocCb* czAcSctAssocFind ARGS((
CmXtaTCCb    *tcCb,
U32   assocIdx
));

EXTERN CmXtaTCCb*  czAcSctTstCbFind ARGS((Void));

EXTERN S16 czAcSctInit ARGS(( Void ));

EXTERN S16 czAcSctDeInit ARGS (( Void ));

EXTERN S16 czAcSbActvTsk ARGS((
               Pst    *pst,                /* post */
               Buffer *mBuf                /* message buffer */
               ));

#ifdef SS_MULTIPLE_PROCS
EXTERN S16 czAcSbActvInit ARGS((
               ProcId procId,
               Ent entity,            /* entity */
               Inst inst,             /* instance */
               Region region,         /* region */
               Reason reason,         /* reason */
               Void   **xxCb
               ));
#else
EXTERN S16 czAcSbActvInit ARGS((
               Ent entity,            /* entity */
               Inst inst,             /* instance */
               Region region,         /* region */
               Reason reason          /* reason */
               ));
#endif

/********************************************/

/*EXTERN S16 czAcUtlBuildX2APPdu ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt
         **pdu));*/
EXTERN S16 czAcUtlSctCb ARGS(( CmXtaMsgQElm *qElm));

EXTERN S16 czAcHdlSctAssocInd1 ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

/*******************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */
 
#endif /* __CZAC_SCT_X__ */

/**********************************************************************

         End of file:     czac_sct.x@@/main/2 - Tue Aug 30 18:35:55 2011

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
 LTE-X2AP Initial Release.
     cz001.101 sn  addition feature added
/main/1      ---      ng       1. LTE-X2AP Initial Release.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
