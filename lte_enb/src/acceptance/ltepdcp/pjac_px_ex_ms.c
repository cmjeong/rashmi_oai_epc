

/********************************************************************20**
  
        Name:    PDCP service user - System Services Interface Function.
    
        Type:    C file
  
        Desc:    This file Contains the RLC service user System Services
                  Interface Function
 
        File:    pjac_pj_ex_ms.c

        Sid:      pjac_px_ex_ms.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:08 2015
  
        Prg:     adarsh
  
*********************************************************************21*/

/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "pju.h"           /* PJU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */
#include "pj_err.h"        /* Error defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_kwu.h"      /* CKW Acceptance defines */
#include "pjac_pju.h"      /* CKW Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "pju.x"           /* PJU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_kwu.x"      /* CKW Acceptance defines */
#include "pjac_pju.x"      /* CKW Acceptance defines */

/*
 *
 *     Fun:   pxActvInit
 *
 *     Desc:  This function is invoked by system services to initialize 
 *            the PDCP layer. This is an entry point used by PDCP layer to 
 *            initialize its global variables, before becoming operational.
 *
 *            The first and second parameters (entity, instance)
 *            specify the entity and instance id of the PDCP task.
 *
 *            The third parameter (region) specifies the memory region
 *            from which PDCP should allocate structures and buffers.
 *
 *            The fourth parameter (reason) specifies the reason for
 *            calling this initialization function.
 *
 *            Allowable values for parameters are specified in ssi.h.
 *
 *     Ret:   ROK   - ok
 *
 *     Notes: None
 *
       File:  kwac_pj_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 pxActvInit
(
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 pxActvInit(ent, inst, region, reason)
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
#endif
{
   TRC3(pxActvInit)

   RETVALUE(ROK);
} /* end of pxActvInit */


/*
 *
 *       Fun:    nxInitExt initialize external
 *
 *       Desc:   Initializes variables used to interface with Upper/Lower
 *               Layer  
 *
 *       Ret:    RETVOID
 *
 *       Notes:  None
 *
         File:   kwac_pj_ex_ms.c
 *
*/
  
#ifdef ANSI
PUBLIC S16 nxInitExt
(
void
)
#else
PUBLIC S16 nxInitExt()
#endif
{
   TRC2(nxInitExt);
   RETVALUE(ROK);

} /* end of nxInitExt */


/*
*
*       Fun:    pxActvTsk Activation task
*
*       Desc:   Processes events received for PDCP layer via System
*               Services from other layers.
*
*       Ret:    ROK
*
*       Notes:  None
*
*       File:   kwac_pj_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 pxActvTsk
(
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 pxActvTsk(post, mBuf)
Pst *post;              /* post structure */
Buffer *mBuf;           /* message buffer */
#endif
{
   S16 ret = ROK;

   TRC3(pxActvTsk);

   switch(post->srcEnt)
   {
#ifdef LCPJU
      case ENTPJ:
      {
         switch(post->event)
         {
            case EVTPJUBNDCFM:             /* PJU Bind confirm */
               /*
                * Unpack the bind confirm primitive. */
               ret = cmUnpkPjuBndCfm(PxLiPjuBndCfm, post, mBuf);
               break;

            case EVTPJUDATIND:             /* Data indication */
               /*
                * Unpack the Data Indication primitive. */
               ret = cmUnpkPjuDatInd(PxLiPjuDatInd, post, mBuf);
               break;

            case EVTPJUDATCFM:            /* Data confirm */
               /*
                * Unpack the data confirm primitive. */
               ret = cmUnpkPjuDatCfm(PxLiPjuDatCfm, post, mBuf);
               break;

            case EVTPJUSTAIND:            /* Status indication */
               /*
                * Unpack the status indication primitive. */
               ret = cmUnpkPjuStaInd(PxLiPjuStaInd, post, mBuf);
               break;

            case EVTPJUDATFWDIND:         /* Data Forward indication */
               /*
                * Unpack the status indication primitive. */
               ret = cmUnpkPjuDatFwdInd(PxLiPjuDatFwdInd, post, mBuf);
               break;

            default:
               ret = RFAILED;
               break;
         }
         break;
      }
#endif  /* LCPJU */

      default:
         break;
   }

   SExitTsk();

   RETVALUE(ret);
}

/********************************************************************30**
         End of file:     pjac_px_ex_ms.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:08 2015
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
/main/1      ---     av         1. LTE  PDCP Initial Release 2.1.
*********************************************************************91*/
