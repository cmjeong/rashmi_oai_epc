

/********************************************************************20**
  
        Name:    RLC service user (PDCP) - System Services Interface Function.
    
        Type:    C file
  
        Desc:    This file Contains the RLC service user System Services
                  Interface Function
 
        File:    kwac_ob_ex_ms.c

        Sid:      kwac_lib_ex_ms.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:29 2014
  
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
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw_err.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_lib.h"      /* Acceptance defines */
#include "kwac_acc.h"      /* Acceptance defines */

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
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"
/*#include "kw_pj_lib.x"      LIB */

#include "cm_xta.x"
#include "kwac_lib.x"      /* Acceptance defines */
#include "kwac_acc.x"      /* Acceptance defines */

#ifdef KW_PDCP


/*
 *
 *     Fun:   osActvInit
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
       File:  kwac_ob_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 osActvInit
(
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 osActvInit(ent, inst, region, reason)
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
#endif
{
   TRC3(osActvInit)

   RETVALUE(ROK);
} /* end of osActvInit */


/*
 *
 *       Fun:    osInitExt initialize external
 *
 *       Desc:   Initializes variables used to interface with Upper/Lower
 *               Layer  
 *
 *       Ret:    RETVOID
 *
 *       Notes:  None
 *
         File:   kwac_ob_ex_ms.c
 *
*/
  
#ifdef ANSI
PUBLIC S16 osInitExt
(
void
)
#else
PUBLIC S16 osInitExt()
#endif
{
   TRC2(osInitExt);
   RETVALUE(ROK);

} /* end of osInitExt */


/*
*
*       Fun:    osActvTsk Activation task
*
*       Desc:   Processes events received for PDCP layer via System
*               Services from other layers.
*
*       Ret:    ROK
*
*       Notes:  None
*
*       File:   kwac_ob_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 osActvTsk
(
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 osActvTsk(post, mBuf)
Pst *post;              /* post structure */
Buffer *mBuf;           /* message buffer */
#endif
{
   S16 ret = ROK;

   TRC3(osActvTsk);

   switch(post->srcEnt)
   {
#ifdef PJ_SEC_ASYNC
      case ENTPJ:
      {
         switch(post->event)
         {
            /* Integrity Confirmations */
            case OBD_EVT_INT_INIT_REQ:
               ret = cmUnpkLibObdIntInitReq(kwAcLibObdIntInitReq, post, mBuf);
               break;

            case OBD_EVT_INT_PROT_REQ:
               ret = cmUnpkLibObdIntProtReq(kwAcLibObdIntProtReq, post, mBuf);
               break;

            case OBD_EVT_INT_VER_REQ:
               ret = cmUnpkLibObdIntVerReq(kwAcLibObdIntVerReq, post, mBuf);
               break;

            case OBD_EVT_INT_CLOSE_REQ:
               ret = cmUnpkLibObdIntCloseReq(kwAcLibObdIntCloseReq, post, mBuf);
               break;

            /* Ciphering Confirmations */
            case OBD_EVT_CP_INIT_REQ:
               ret = cmUnpkLibObdCpInitReq(kwAcLibObdCpInitReq, post, mBuf);
               break;

            case OBD_EVT_UP_INIT_REQ:
               ret = cmUnpkLibObdUpInitReq(kwAcLibObdUpInitReq, post, mBuf);
               break;

            case OBD_EVT_CIPHER_REQ:
               ret = cmUnpkLibObdCipherReq(kwAcLibObdCipherReq, post, mBuf);
               break;

            case OBD_EVT_DECIPHER_REQ:
               ret = cmUnpkLibObdDecipherReq(kwAcLibObdDecipherReq, post, mBuf);
               break;

            case OBD_EVT_CIPHER_CLOSE_REQ:
               ret = cmUnpkLibObdCipherCloseReq(kwAcLibObdCipherCloseReq, post, mBuf);
               break;

            default:
#if  (ERRCLASS & ERRCLS_DEBUG)
               KWLOGERROR_ACC(ERRCLS_DEBUG, EKWXXX, (ErrVal)post->event,
                          "Invalid  Event from PJ");
#endif /* ERRCLASS & ERRCLS_DEBUG */
               ret = RFAILED;
               break;
         }
         break;
      }
#endif  /* PJ_SEC_ASYNC */

      default:
#if  (ERRCLASS & ERRCLS_DEBUG)
         KWLOGERROR_ACC(ERRCLS_DEBUG, EKWXXX, (ErrVal)post->srcEnt,
                    "Invalid Source Entity ");
#endif /* ERRCLASS & ERRCLS_DEBUG */
         break;
   }

   SExitTsk();

   RETVALUE(ret);
} /* osActvTsk */


/*
 *
 *     Fun:   ocActvInit
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
       File:  kwac_lib_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 ocActvInit
(
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 ocActvInit(ent, inst, region, reason)
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
#endif
{
   TRC3(ocActvInit)

   RETVALUE(ROK);
} /* end of ocActvInit */


/*
 *
 *       Fun:    ocInitExt initialize external
 *
 *       Desc:   Initializes variables used to interface with Upper/Lower
 *               Layer  
 *
 *       Ret:    RETVOID
 *
 *       Notes:  None
 *
         File:   kwac_ob_ex_ms.c
 *
*/
  
#ifdef ANSI
PUBLIC S16 ocInitExt
(
void
)
#else
PUBLIC S16 ocInitExt()
#endif
{
   TRC2(ocInitExt);
   RETVALUE(ROK);

} /* end of ocInitExt */


/*
*
*       Fun:    ocActvTsk Activation task
*
*       Desc:   Processes events received for PDCP layer via System
*               Services from other layers.
*
*       Ret:    ROK
*
*       Notes:  None
*
*       File:   kwac_ob_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 ocActvTsk
(
Pst *post,              /* post structure */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 ocActvTsk(post, mBuf)
Pst *post;              /* post structure */
Buffer *mBuf;           /* message buffer */
#endif
{
   S16 ret = ROK;

   TRC3(ocActvTsk);

   switch(post->srcEnt)
   {
#ifdef PJ_CMP_ASYNC
      case ENTPJ:
      {
         switch(post->event)
         {
            /* Compression Confirmations */
            case OBD_EVT_CMP_INIT_REQ:
               ret = cmUnpkLibObdCmpInitReq(kwAcLibObdCmpInitReq, post, mBuf);
               break;

            case OBD_EVT_CMP_REQ:
               ret = cmUnpkLibObdCmpReq(kwAcLibObdCmpReq, post, mBuf);
               break;

            case OBD_EVT_DECMP_REQ:
               ret = cmUnpkLibObdDecmpReq(kwAcLibObdDecmpReq, post, mBuf);
               break;

            case OBD_EVT_CMP_CLOSE_REQ:
               ret = cmUnpkLibObdCmpCloseReq(kwAcLibObdCmpCloseReq, post, mBuf);
               break;

            case OBD_EVT_CMP_RESET_REQ:
               ret = cmUnpkLibObdCmpResetReq(kwAcLibObdCmpResetReq, post, mBuf);
               break;

            case OBD_EVT_CMP_FB_REQ:
               ret = cmUnpkLibObdCmpFbReq(kwAcLibObdCmpFbReq, post, mBuf);
               break;

            default:
#if  (ERRCLASS & ERRCLS_DEBUG)
               KWLOGERROR_ACC(ERRCLS_DEBUG, EKWXXX, (ErrVal)post->event,
                          "Invalid  Event from PJ");
#endif /* ERRCLASS & ERRCLS_DEBUG */
               ret = RFAILED;
               break;
         }
         break;
      }
#endif  /* PJ_CMP_ASYNC */

      default:
#if  (ERRCLASS & ERRCLS_DEBUG)
         KWLOGERROR_ACC(ERRCLS_DEBUG, EKWXXX, (ErrVal)post->srcEnt,
                    "Invalid Source Entity ");
#endif /* ERRCLASS & ERRCLS_DEBUG */
         break;
   }

   SExitTsk();

   RETVALUE(ret);
} /* ocActvTsk */

#endif /* KW_PDCP */
  
/********************************************************************30**
         End of file:     kwac_lib_ex_ms.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:29 2014
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
/main/1      ---   gk         1. Initial Release.
*********************************************************************91*/

