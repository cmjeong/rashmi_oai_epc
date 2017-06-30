

/********************************************************************20**
  
        Name:    PDCP service provider - System Services Interface Function
    
        Type:    C file
  
        Desc:    This file Contains the PDCP service provider System Services
                  Interface Functions
 
        File:    pjac_kw_ul_ex_ms.c

        Sid:      pjac_kw_ul_ex_ms.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:51 2015
  
        Prg:     Adarsh
  
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
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* PDCP environment options */
#include "pj.h"            /* PDCP defines */
#include "pj_err.h"        /* Error defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_kwu.h"      /* CKW Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_kwu.x"      /* CKW Acceptance defines */


/***********************************************************************
                      System Service Interface Functions
 ***********************************************************************/
/*
 *
 *     Fun:   kwUlActvInit
 *
 *     Desc:  This function is invoked by system services to initialize 
 *            the RLC layer. This is an entry point used by RLC layer to 
 *            initialize its global variables, before becoming operational.
 *
 *            The first and second parameters (entity, instance)
 *            specify the entity and instance id of the RLC task.
 *
 *            The third parameter (region) specifies the memory region
 *            from which RLC should allocate structures and buffers.
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
       File:  pjac_kw_ul_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 kwUlActvInit
(
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 kwUlActvInit(ent, inst, region, reason)
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
#endif
{
   TRC3(kwUlActvInit)
   /* kw005.201 removed warning */
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
  
   RETVALUE(ROK);
} /* end of kwUlActvInit */

/*
 *
 *       Fun:    kwUlInitExt initialize external
 *
 *       Desc:   Initializes variables used to interface with Upper/Lower
 *               Layer  
 *
 *       Ret:    RETVOID
 *
 *       Notes:  None
 *
         File:   pjac_kw_ul_ex_ms.c
 *
*/
  
#ifdef ANSI
PUBLIC S16 kwUlInitExt
(
void
)
#else
PUBLIC S16 kwUlInitExt()
#endif
{
   TRC2(kwUlInitExt);
   RETVALUE(ROK);

} /* end of kwUlInitExt */


/*
*
*       Fun:    kwUlActvTsk Activation task
*
*       Desc:   Processes events received for RLC layer via System
*               Services from other layers.
*
*       Ret:    ROK
*
*       Notes:  None
*
*       File:   pjac_kw_ul_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 kwUlActvTsk
(
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 kwUlActvTsk(post, mBuf)
Pst *post;              /* post structure */
Buffer *mBuf;           /* message buffer */
#endif
{
   S16 ret = ROK;

   TRC3(kwActvTsk);

   switch(post->srcEnt)
   {
#ifdef LCKWU
      case ENTKW:
      {
         switch(post->event)
         {
#ifdef LCUDX
               case PJAC_UDX_EVT_BND_CFM:              /* Bind request */
                  {
                     ret = cmUnpkUdxBndCfm(KwUlUdxBndCfm, pst, mBuf );
                     break;
                  }
                                                                                                                                                                        
               case PJAC_UDX_EVT_CFG_CFM:             /* Unbind request */
                  {
                     ret = cmUnpkUdxCfgCfm(KwUlUdxCfgCfm, pst, mBuf );
                     break;
                  }
                                                                                                                                                                        
               case PJAC_UDX_EVT_UEIDCHG_CFM:              /* Configuration request */
                  {
                     ret = cmUnpkUdxUeIdChgCfm(KwUlUdxUeIdChgCfm, pst, mBuf);
                     break;
                  }
                                                                                                                                                                        
               case PJAC_UDX_EVT_STA_UPD_CFM:              /* Configuration request */
                  {
                     ret = cmUnpkUdxStaUpdCfm(KwUlUdxStaUpdCfm, pst, mBuf);
                     break;
                  }
                                                                                                                                                                        
#endif  /* LCUDX */

            default:
               ret = RFAILED;
               break;
         }
         break;
      }
#endif  /* LCKWU */

      default:
         break;
   }

   SExitTsk();

   RETVALUE(ret);
}

/********************************************************************30**
         End of file:     pjac_kw_ul_ex_ms.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:51 2015
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
/main/1      ---       av     1. LTE PDCP Initial release 2.1
*********************************************************************91*/
