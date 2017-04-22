
/********************************************************************20**

     Name:    S1AP

     Type:    C source file

     Desc:    Functions required for scheduling and initialization.

     File:    szac_sb_ex_ms.c

     Sid:      szac_sb_ex_ms.c@@/main/3 - Mon Jan 10 22:16:48 2011

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
#include "szac_acc.x"        /* typedefs for SZCP acceptance tests */
#include "szac_lsz.x"

#ifdef DM
#include "szac_sct.x"
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
PUBLIC S16 szAcSbActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 szAcSbActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   TRC3(szAcSbActvTsk)

   ret = ROK;

   /* call the unpacking function, depending on source entity and event type */

   switch(pst->srcEnt)
   {
      case ENTSZ:
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
               CMXTA_DBG_ERR((_cmxtap, "szAcSbActvTsk(): Invalid Event(%d) from"
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
               CMXTA_DBG_ERR((_cmxtap, "szAcSbActvTsk(): Invalid Event(%d) from\
                                 service user", pst->event));
               ret = RFAILED;

         }/* end of switch */
         break;
#endif /* LCSBMILSB */
      }
      break;

      default:
         (Void)SPutMsg(mBuf);
         CMXTA_DBG_ERR((_cmxtap, "szAcSbActvTsk(): Invalid source entity (%d)",
                                       pst->srcEnt));
         ret = RFAILED;
         break;

   }/* end of switch */

   SExitTsk();
   RETVALUE(ret);
} /* end of szAcSbActvTsk */

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
PUBLIC S16 szAcSbActvInit
(
ProcId procId,
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,         /* reason */
Void   **xxCb
)
#else
PUBLIC S16 szAcSbActvInit(procId, entity, inst, region, reason, xxCb)
ProcId procId;
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
Void   **xxCb;
#endif
#else /*SS_MULTIPLE_PROCS*/
#ifdef ANSI
PUBLIC S16 szAcSbActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 szAcSbActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
#endif/*SS_MULTIPLE_PROCS*/
{

   TRC2(szAcSbActvInit)
   UNUSED(entity);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);

   /* SB_ZERO((Data *)&sbGlobalCbLst[0],(S32)sizeof(SbGlobalCb));
   sbGlobalCbPtr = &sbGlobalCbLst[0]; */
 
      
   RETVALUE(ROK);
}/* end of szAcSbActvInit --*/

#endif /*(defined(DM) && defined(GCP_PROV_SCTP))*/ 

/********************************************************************30**

         End of file:     szac_sb_ex_ms.c@@/main/3 - Mon Jan 10 22:16:48 2011

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
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz006.301   ve    1. Removed un-necessary include files
/main/3   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
