
/********************************************************************20**

     Name:    S1AP - acc test file for SCT interface

     Type:    C Include file

     Desc:    This file contains the acc structures and 
              function prototypes

     File:    szac_sct.x

     Sid:      szac_sct.x@@/main/3 - Mon Jan 10 22:15:56 2011

     Prg:     ms

*********************************************************************21*/
#ifndef __SZAC_SCT_X__
#define __SZAC_SCT_X__

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
#include "sb_mtu.h"         /* SCTP */
#include "sb_mtu.x"         /* SCTP */
#include "sb.h"             /* SCTP */
#include "sb.x"             /* SCTP */
#endif


/*******************************************************************
                  SCT Handler functions
*******************************************************************/

EXTERN S16 szAcHdlSctBndReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctEndpOpenReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));
       
EXTERN S16 szAcHdlSctEndpCloseReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctAssocReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctTermReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctSetPrimReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctHBeatReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctDatReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctStaReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctBndCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctEndpOpenCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctEndpCloseCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctAssocInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctAssocCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctTermInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctTermCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctSetPriCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctHBeatCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctDatInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctStaCfm ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctStaInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));


EXTERN S16 szAcHdlSctFlcInd ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctAssocRsp ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN S16 szAcHdlSctSetPriReq ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

EXTERN SzAcSctAssocCb* szAcSctAssocFindnCreate ARGS((
CmXtaTCCb    *tcCb,
U32   assocIdx,
UConnId   suAssocId,
UConnId   spAssocId
));

EXTERN SzAcSctAssocCb* szAcSctAssocFind ARGS((
CmXtaTCCb    *tcCb,
U32   assocIdx
));

EXTERN CmXtaTCCb*  szAcSctTstCbFind ARGS((Void));

EXTERN S16 szAcSctInit ARGS(( Void ));

EXTERN S16 szAcSctDeInit ARGS (( Void ));

EXTERN S16 szAcSbActvTsk ARGS((
               Pst    *pst,                /* post */
               Buffer *mBuf                /* message buffer */
               ));

#ifdef SS_MULTIPLE_PROCS
EXTERN S16 szAcSbActvInit ARGS((
               ProcId procId,
               Ent entity,            /* entity */
               Inst inst,             /* instance */
               Region region,         /* region */
               Reason reason,         /* reason */
               Void   **xxCb
               ));
#else
EXTERN S16 szAcSbActvInit ARGS((
               Ent entity,            /* entity */
               Inst inst,             /* instance */
               Region region,         /* region */
               Reason reason          /* reason */
               ));
#endif

/********************************************/

EXTERN S16 szAcUtlBuildS1APPdu_r9 ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, Buffer **mBuf));
EXTERN S16 szAcUtlBuildS1APPdu_r11 ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, Buffer **mBuf));
EXTERN S16 szAcUtlSctCb ARGS(( CmXtaMsgQElm *qElm));

EXTERN S16 szAcHdlSctAssocInd1 ARGS((
    CmXtaTCCb    *tcCb,
    CmXtaSpCb    *spCb));

/*******************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */
 
#endif /* __SZAC_SCT_X__ */

/**********************************************************************

         End of file:     szac_sct.x@@/main/3 - Mon Jan 10 22:15:56 2011

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
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
*********************************************************************91*/
