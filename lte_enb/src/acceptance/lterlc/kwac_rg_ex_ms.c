

/********************************************************************20**
  
        Name:    RLC service provider (MAC) - System Services Interface Function
    
        Type:    C file
  
        Desc:    This file Contains the RLC service provider System Services
                  Interface Functions
 
        File:    kwac_rg_ex_ms.c

        Sid:      kwac_rg_ex_ms.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:40 2014
  
        Prg:     chakrapani
  
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
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "kw_err.h"        /* Error defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_rgu.h"      /* CKW Acceptance defines */

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
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_rgu.x"      /* CKW Acceptance defines */


U32  rgMacGT;


/***********************************************************************
                      System Service Interface Functions
 ***********************************************************************/
/*
 *
 *     Fun:   rgActvInit
 *
 *     Desc:  This function is invoked by system services to initialize 
 *            the MAC layer. This is an entry point used by MAC layer to 
 *            initialize its global variables, before becoming operational.
 *
 *            The first and second parameters (entity, instance)
 *            specify the entity and instance id of the MAC task.
 *
 *            The third parameter (region) specifies the memory region
 *            from which MAC should allocate structures and buffers.
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
       File:  kwac_rg_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 rgActvInit
(
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 rgActvInit(ent, inst, region, reason)
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
#endif
{
   TRC3(rgActvInit)
   /* kw005.201 removed warning */
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
  
   RETVALUE(ROK);
} /* end of rgActvInit */


/*
 *
 *       Fun:    rgInitExt initialize external
 *
 *       Desc:   Initializes variables used to interface with Upper/Lower
 *               Layer  
 *
 *       Ret:    RETVOID
 *
 *       Notes:  None
 *
         File:   kwac_rg_ex_ms.c
 *
*/
  
#ifdef ANSI
PUBLIC S16 rgInitExt
(
void
)
#else
PUBLIC S16 rgInitExt()
#endif
{
   TRC2(rgInitExt);
   RETVALUE(ROK);

} /* end of rgInitExt */


/*
*
*       Fun:    rgActvTsk Activation task
*
*       Desc:   Processes events received for MAC layer via System
*               Services from other layers.
*
*       Ret:    ROK
*
*       Notes:  None
*
*       File:   kwac_rg_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 rgActvTsk
(
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 rgActvTsk(post, mBuf)
Pst *post;              /* post structure */
Buffer *mBuf;           /* message buffer */
#endif
{
   S16 ret = ROK;

   TRC3(rgActvTsk);

   switch(post->srcEnt)
   {
#ifdef LCRGU
      case ENTKW:
      {
         switch(post->event)
         {
            case KWAC_RGU_EVT_BND_REQ:             /* RGU Bind Request */
               {
                  ret = cmUnpkRguBndReq(RgUiRguBndReq, post, mBuf);
                  break;
               }

            case KWAC_RGU_EVT_UBND_REQ:             /* RGU Bind Request */
               {
                  ret = cmUnpkRguUbndReq(RgUiRguUbndReq, post, mBuf);
                  break;
               }

            case KWAC_RGU_EVT_CDAT_REQ:             /* Data Request */
               {
                  ret = cmUnpkRguCDatReq(RgUiRguCDatReq, post, mBuf);
                  break;
               }

            case KWAC_RGU_EVT_DDAT_REQ:             /* Data Request */
               {
                  ret = cmUnpkRguDDatReq(RgUiRguDDatReq, post, mBuf);
                  break;
               }

            case KWAC_RGU_EVT_CSTA_RSP:             /* Data Request */
               {
                  ret = cmUnpkRguCStaRsp(RgUiRguCStaRsp, post, mBuf);
                  break;
               }

            case KWAC_RGU_EVT_DSTA_RSP:             /* Data Request */
               {
                  ret = cmUnpkRguDStaRsp(RgUiRguDStaRsp, post, mBuf);
                  break;
               }
            /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
            case KWAC_RGU_EVT_L2MULTHR_REQ:             /* UL IP throughput request */
               {
                  ret = cmUnpkRguL2MUlThrpMeasReq(RgUiRguL2MUlThrpMeasReq , post, mBuf);
                  break;
               }
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */

            default:
#if  (ERRCLASS & ERRCLS_DEBUG)
               KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, (ErrVal)post->event,
                     "Invalid  Event from HI");
#endif /* ERRCLASS & ERRCLS_DEBUG */
               ret = RFAILED;
               break;
         }
         break;
      }
#endif  /* LCRGU */

      default:
#if  (ERRCLASS & ERRCLS_DEBUG)
         KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, (ErrVal)post->srcEnt,
                    "Invalid Source Entity ");
#endif /* ERRCLASS & ERRCLS_DEBUG */
         break;
   }

   SExitTsk();

   RETVALUE(ret);
}

  
/********************************************************************30**
         End of file:     kwac_rg_ex_ms.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:40 2014
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
/main/1      ---       cp     1. Initial release.
/main/2      ---       gk     1. LTE RLC Release 2.1.
/main/3      kw005.201 ap     1. Removed compilation warning
                       rd     2. Added support for L2 Measurement.
*********************************************************************91*/

