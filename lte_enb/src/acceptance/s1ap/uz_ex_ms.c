
/********************************************************************20**

     Name:    S1AP

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    uz_ex_ms.c

     Sid:     @/main/4 - Mon Jan 10 22:16:50 2011

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
#include "szt.h"           /* defines and macros for SZ */
#include "szac_asn.h"
/* sz006.301: Removed un-necessary include files  */
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

#include "sz_err.h"        /* SZ error defines */
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
#include "uz.x"

#include "sz_err.h"        /* SZ error defines */
/* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
PRIVATE S16 UzMiShtCntrlReq ARGS((Pst *pst, ShtCntrlReqEvnt *reqInfo));
#endif /* SZ_FTHA */
/*
 *
 *       Fun:    uzActvInit - S1AP user initialization function
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   uz_ex_ms.c
 *
 */
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 uzActvInit
(
ProcId   procId,
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason,               /* reason */
Void   **xxCb               /* xxCb pointer */
)
#else
PUBLIC S16 uzActvInit(procId, ent, inst, region, reason, xxCb)
ProcId   procId;
Ent      ent;                 /* entity */
Inst     inst;                /* instance */
Region   region;              /* region */
Reason   reason;              /* reason */
Void   **xxCb;
#endif /*ANSI*/
#else /*SS_MULTIPLE_PROCS*/
#ifdef ANSI
PUBLIC S16 uzActvInit
(
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason               /* reason */
)
#else
PUBLIC S16 uzActvInit(ent, inst, region, reason)
Ent      ent;                 /* entity */
Inst     inst;                /* instance */
Region   region;              /* region */
Reason   reason;              /* reason */
#endif /* ANSI */
#endif /*SS_MULTIPLE_PROCS */
{
   TRC3(uzActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   (Void)uzInitExt();
   RETVALUE(ROK);
} /* end of uzActvInit() */

/*
 *
 *       Fun:    uzInitExt - external initialization
 *
 *       Desc:   performs additional initializations as required
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  to be changed by the customer if required
 *
         File:   uz_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 uzInitExt
(
void
)
#else
PUBLIC S16 uzInitExt()
#endif /* ANSI */
{
   TRC2(uzInitExt)
   RETVALUE(ROK);
} /* end of uzInitExt()*/


/*
 *
 *       Fun:    uzActvTsk - S1AP user activation
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   uz_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 uzActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else
PUBLIC S16 uzActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   Mem sMem;

   TRC3(uzActvTsk)
#if (ERRCLASS & ERRCLS_DEBUG)
   if (pst == (Pst *)NULLP)
   {
      if (mBuf != (Buffer *)NULLP)
      {
         (Void)SPutMsg(mBuf);
      }
      RETVALUE(RFAILED);
   }
   if (mBuf == (Buffer *)NULLP)
   {
      SZLOGERROR(ERRCLS_DEBUG, ESZXXX, ERRZERO, 
         "Null mBuf in uzActvTsk\n");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;

   switch (pst->event)
   {
#if ((defined(LCUZLISZT)) || ((defined(LWLCUZLISZT))))
      case EVTSZTBNDCFM:
      {
         (Void)cmUnpkSztBndCfm(UzLiSztBndCfm, pst, mBuf);
         break;
      }

      case EVTSZTAUDCFM:
      {
         (Void)cmUnpkSztAudCfm(UzLiSztAudCfm, pst, mBuf, &sMem); 
         break;
      }

      case EVTSZTSTAIND:
      {
         (Void)cmUnpkSztStaInd(UzLiSztStaInd, pst, mBuf); 
         break;
      }

      case EVTSZTFLCIND:
      {
         (Void)cmUnpkSztFlcInd(UzLiSztFlcInd, pst, mBuf); 
         break;
      }

      case EVTSZTERRIND:
      {
         (Void)cmUnpkSztLclErrInd(UzLiSztErrInd, pst, mBuf); 
         break;
      }

      case EVTSZTUDATIND:
      {
         (Void)cmUnpkSztUDatInd(UzLiSztUDatInd, pst, mBuf, &sMem);
         break;
      }
 
      case EVTSZTCONIND:
      {
         (Void)cmUnpkSztConInd(UzLiSztConInd, pst, mBuf, &sMem);
         break;
      }
 
      case EVTSZTCONCFM:
      {
         (Void)cmUnpkSztConCfm(UzLiSztConCfm, pst, mBuf, &sMem);
         break;
      }
 
      case EVTSZTRELIND:
      {
         (Void)cmUnpkSztRelInd(UzLiSztRelInd, pst, mBuf, &sMem);
         break;
      }
 
      case EVTSZTRELCFM:
      {
         (Void)cmUnpkSztRelCfm(UzLiSztRelCfm, pst, mBuf, &sMem);
         break;
      }
 
      case EVTSZTDATIND:
      {
         (Void)cmUnpkSztDatInd(UzLiSztDatInd, pst, mBuf, &sMem);
         break;
      }
 
      case EVTSZTENCDECCFM:
      {
         (Void)cmUnpkSztEncDecCfm(UzLiSztEncDecCfm, pst, mBuf, &sMem);
         break;
      }
 
#ifdef SZ_MME
      case EVTSZTPEERASSOCIND:
      {
         (Void)cmUnpkSztPeerAssocInd(UzLiSztPeerAssocInd, pst, mBuf, &sMem);
         break;
      }
#endif
/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
      case EVTSZTABORTS1CFM:
      {
         (Void)cmUnpkSztAbortS1Cfm(UzLiSztAbortS1Cfm, pst, mBuf);
         break;
      }
#endif /* SZTV2 */
#endif /* LCUZLISZT */
      /* sz003.301: Updted for PSF-S1AP 3.1 release. Added SHT control request
       * for UZ */
#ifdef SZ_FTHA
      case EVTSHTCNTRLREQ:
      {
         cmUnpkMiShtCntrlReq(UzMiShtCntrlReq, pst, mBuf);
      }
      break;
#endif /* SZ_FTHA */
      default:
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SZLOGERROR(ERRCLS_DEBUG, ESZXXX, ERRZERO, 
            "invalid pst->event in uzActvTsk\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
         (Void)SPutMsg(mBuf);
         break;
      }
   }
   (Void)SExitTsk();
   RETVALUE(ROK);
} /* end of uzActvTsk() */
          
/* sz003.301: Updted for PSF-S1AP 3.1 release. Added SHT cntrol request
 * for UZ */
#ifdef SZ_FTHA
#ifdef SZ_RUG

/************************************************************************
*
*       Fun  :  Get Interface Version handling
*
*       Desc :  Processes system agent control request 
*               primitive to get interface version for all
*               intefaces implemented by the protocol
*
*       Ret  :  ROK  - ok
*
*       Notes:  None
*
*       File :  uz_ex_ms.c
*
***********************************************************************/
#ifdef ANSI
PRIVATE S16 uzGetVer
(
ShtGetVerCfm *getVerCfmInfo   /* to return intf ver info */
)
#else
PRIVATE S16 uzGetVer(getVerCfmInfo)
ShtGetVerCfm *getVerCfmInfo;  /* to return intrf ver info */
#endif
{
   TRC2(szGetVer);

   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf, 
            " In uzGetVer: Getting the version \n"));

              
   /* Fill list of upper interfaces IDs and their ver number */
   getVerCfmInfo->numUif = 0;
   getVerCfmInfo->uifList[0].intfId  = 0;
   getVerCfmInfo->uifList[0].intfVer = 0;
              
   /* Fill list of lower interfaces IDs and their ver number */
   getVerCfmInfo->numLif = 1;
   getVerCfmInfo->lifList[0].intfId  = SZTIF;
   getVerCfmInfo->lifList[0].intfVer = SZTIFVER;
   
   RETVALUE(ROK);
}/* End of uzGetVer */
#endif /* SZ_RUG */
          


/**********************************************************
*
*       Fun:   UzMiShtCntrlReq - System Agent Control Request
*
*       Desc:  Processes system agent control request primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  uz_ex_ms.c
*
**********************************************************/ 
#ifdef ANSI
PRIVATE S16 UzMiShtCntrlReq
(
Pst               *pst,         /* post structure */
ShtCntrlReqEvnt   *reqInfo      /* system agent control request event */
)
#else
PRIVATE S16 UzMiShtCntrlReq(pst, reqInfo)
Pst               *pst;         /* post structure */
ShtCntrlReqEvnt   *reqInfo;     /* system agent control request event */
#endif
{
   Pst               repPst;    /* reply post structure */
   ShtCntrlCfmEvnt   cfmInfo;   /* system agent control confirm event */

   TRC3(UzMiShtCntrlReq);

   cmMemset((U8*)&cfmInfo, 0, sizeof(ShtCntrlCfmEvnt));

   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
            "-----S1AP User-----(proc(%d), entt(%d), inst(%d))------\
            \n Mi System Agent Control Req\n", 
            pst->dstProcId, pst->dstEnt, pst->dstInst));
    
   /* fill reply post structure */
   repPst.dstProcId = pst->srcProcId;
   repPst.dstEnt    = pst->srcEnt;
   repPst.dstInst   = pst->srcInst;
   repPst.prior     = reqInfo->hdr.response.prior;
   repPst.route     = reqInfo->hdr.response.route;
   repPst.selector  = reqInfo->hdr.response.selector;
   repPst.event     = EVTSHTCNTRLCFM;
   repPst.srcProcId = SFndProcId();
   repPst.srcEnt    = ENTUZ;
   repPst.srcInst   = 0;
   repPst.region    = pst->region;
   repPst.pool      = pst->pool;
    
   cfmInfo.transId = reqInfo->hdr.transId;

#ifdef SZ_RUG
   cfmInfo.reqType = reqInfo->reqType;
#endif /* SZ_RUG */

   /* fill reason and status value */
   cfmInfo.status.reason = LCM_REASON_NOT_APPL;
   cfmInfo.status.status = LCM_PRIM_OK;

   switch (reqInfo->reqType)
   {
#ifdef SZ_RUG
      case SHT_REQTYPE_GETVER:  /* system agent control get interface version */
         uzGetVer(&cfmInfo.t.gvCfm);
         break;

      case SHT_REQTYPE_SETVER:  /* system agent control set interface version */
         break;
#endif /* SZ_RUG */

      default:
         SZDBGP(DBGMASK_MI, (szCb.init.prntBuf, "Invalid parameter value\n"));
         cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
         break;
   }

   SzMiShtCntrlCfm(&repPst, &cfmInfo); /* send the response */

   RETVALUE(ROK);
} /* end UzMiShtCntrlReq */ 
#endif /* SZ_FTHA */

/********************************************************************30**

         End of file:     uz_ex_ms.c@@/main/4 - Mon Jan 10 22:16:50 2011

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
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz005.301   va    1. Updated for S1 Abort request support by UI
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth1. Support for source RNC to target RNC.
*********************************************************************91*/
