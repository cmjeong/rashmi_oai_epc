
/********************************************************************20**

     Name:    X2AP

     Type:    C source file

     Desc:    Functions required for scheduling and initialization.

     File:    czac_sb_ex_ms.c

     Sid:      czac_sb_ex_ms.c@@/main/2 - Tue Aug 30 18:36:05 2011

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
#endif /* HI */

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
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* CZT Interface Structures */
#include "lcz.x"           /* layer management typedefs for CZCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif /* HI */

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "../../sctp/sb_mtu.x"
#include "../../sctp/sb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for CZCP */
#include "czac_acc.x"        /* typedefs for CZCP acceptance tests */
#include "czac_lcz.x"

#ifdef DM
#include "czac_sct.x"
#endif /*(defined(DM) && defined(GCP_PROV_SCTP))*/


#ifdef DM



/* local defines */

/* local typedefs */

/* local externs */

/* functions in other modules */

/* public variable declarations */

/* private variable declarations */


/*
*     support functions
*/

/* ------------------------------------------------------------ */


/*
*
*       Fun:    activation task
*
*       Desc:   Processes received event from Upper/Lower Layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   xx_sb_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcSbActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else /* ANSI */
PUBLIC S16 czAcSbActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif /* ANSI */
{
   S16 ret;

   TRC3(czAcSbActvTsk)

   ret = ROK;

   /* call the unpacking function, depending on source entity and event type */

   switch(pst->srcEnt)
   {
      case ENTCZ:
      {

#ifdef LCSBUISCT          /* loosely coupled SCT interface */
         /* BETA_EXTN_AD: */
         switch(pst->event)
         {
            case  SCT_EVTBNDREQ:                 /* bind request */
               ret = cmUnpkSctBndReq(DmUiSctBndReq, pst, mBuf);
               break;

            case  SCT_EVTASSOCREQ:               /* association request */
               ret = cmUnpkSctAssocReq(DmUiSctAssocReq, pst, mBuf);
               break;

            case  SCT_EVTASSOCRSP:               /* association responce */
               ret = cmUnpkSctAssocRsp(DmUiSctAssocRsp, pst, mBuf);
               break;

            case  SCT_EVTTERMREQ:                /* termination request */
               ret = cmUnpkSctTermReq(DmUiSctTermReq, pst, mBuf);
               break;

            case  SCT_EVTSETPRIREQ:              /* set primary DTA request */
               ret = cmUnpkSctSetPriReq(DmUiSctSetPriReq, pst, mBuf);
               break;

            case  SCT_EVTHBEATREQ:               /* heartbeat request */
               ret = cmUnpkSctHBeatReq(DmUiSctHBeatReq, pst, mBuf);
               break;

            case  SCT_EVTDATREQ:                 /* data request */
               ret = cmUnpkSctDatReq(DmUiSctDatReq, pst, mBuf);
               break;

            case  SCT_EVTSTAREQ:                 /* status request */
               ret = cmUnpkSctStaReq(DmUiSctStaReq, pst, mBuf);
               break;

            case  SCT_EVTENDPOPENREQ:            /* endpoint open request */
               ret = cmUnpkSctEndpOpenReq(DmUiSctEndpOpenReq, pst, mBuf);
               break;

            case  SCT_EVTENDPCLOSEREQ:           /* endpoint close request */
               ret = cmUnpkSctEndpCloseReq(DmUiSctEndpCloseReq, pst, mBuf);
               break;

            default:
               (Void)SPutMsg(mBuf);
               CMXTA_DBG_ERR((_cmxtap, "czAcSbActvTsk(): Invalid Event(%d) from"
                                 "service user", pst->event));
               ret = RFAILED;
               break;

         }/* end switch */
         break;

#endif /* LCSBUISCT */
      }
      break;

      case ENTSM:
      {
#ifdef LCSBMILSB     /* loosely coupled layer manager */

         switch(pst->event)
         {
            case LSB_EVTCFGREQ:       /* Configuration Request */
               ret = cmUnpkLsbCfgReq(SbMiLsbCfgReq, pst, mBuf);
               break;

            case LSB_EVTSTSREQ:       /* Statistics Request */
               ret = cmUnpkLsbStsReq(SbMiLsbStsReq, pst, mBuf);
               break;

            case LSB_EVTCNTRLREQ:     /* Control Request */
               ret = cmUnpkLsbCntrlReq(SbMiLsbCntrlReq, pst, mBuf);
               break;

            case LSB_EVTSTAREQ:       /* Status Request */
               ret = cmUnpkLsbStaReq(SbMiLsbStaReq, pst, mBuf);
               break;

            default:
               (Void)SPutMsg(mBuf);
               CMXTA_DBG_ERR((_cmxtap, "czAcSbActvTsk(): Invalid Event(%d) from\
                                 service user", pst->event));
               ret = RFAILED;

         }/* end of switch */
         break;
#endif /* LCSBMILSB */
      }
      break;

      default:
         (Void)SPutMsg(mBuf);
         CMXTA_DBG_ERR((_cmxtap, "czAcSbActvTsk(): Invalid source entity (%d)",
                                       pst->srcEnt));
         ret = RFAILED;
         break;

   }/* end of switch */

   SExitTsk();
   RETVALUE(ret);
} /* end of czAcSbActvTsk */

/*
*
*      Fun:   Activate Task - initialize
* 
*      Desc:  Invoked by system services to initialize a task.
* 
*      Ret:   ROK
* 
*      Notes: None
* 
*      File:  xx_sb_ex_ms.c
* 
*/
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 czAcSbActvInit
(
ProcId prcId,
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,         /* reason */
Void   **xxCb
)
#else /* ANSI */
PUBLIC S16 czAcSbActvInit(prcId, entity, inst, region, reason, xxCb)
ProcId prcId;
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
Void   **xxCb;
#endif /* ANSI */
#else /*SS_MULTIPLE_PROCS*/
#ifdef ANSI
PUBLIC S16 czAcSbActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else /* ANSI */
PUBLIC S16 czAcSbActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif /* ANSI */
#endif/*SS_MULTIPLE_PROCS*/
{

   TRC2(czAcSbActvInit)
   UNUSED(entity);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);

   /* SB_ZERO((Data *)&sbGlobalCbLst[0],(S32)sizeof(SbGlobalCb));
   sbGlobalCbPtr = &sbGlobalCbLst[0]; */
 
      
   RETVALUE(ROK);
}/* end of czAcSbActvInit --*/

#endif /*(defined(DM) && defined(GCP_PROV_SCTP))*/ 

/********************************************************************30**

         End of file:     czac_sb_ex_ms.c@@/main/2 - Tue Aug 30 18:36:05 2011

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
/main/2      ---      pt       1. LTE-X2AP 3.1 release.
*********************************************************************91*/
