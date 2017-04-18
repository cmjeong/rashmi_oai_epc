

/********************************************************************20**
  
        Name:    LTE-RLC Layer - System Services Interface Functions
    
        Type:    C file
  
        Desc:    C source code for the interface to System Services
                  of LTE-RLC
 
        File:    kw_ex_ms.c

        Sid:      kw_dl_ex_ms.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:45 2014
  
        Prg:     gk
  
*********************************************************************21*/

/** @file gp_ex_ms.c
@brief RLC System Services Interface
*/


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
#include "kw_err.h"        /* Err defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "kw_dl.h"
#include "kw_udx.h"

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
#include "kw.x"
#include "kw_dl.x"
#include "kw_udx.x"

PUBLIC S16 kwDlInitExt ARGS (( Void ));

/**
 *
 * @brief
 *
 *  <b> Initialize External </b>
 *
 *  @b Description:
 *  Initializes variables used to interface with Upper/Lower Layer  
 *
 *  @return  S16
 *      -# ROK 
 *
*/
  
#ifdef ANSI
PUBLIC S16 kwDlInitExt 
(
)
#else
PUBLIC S16 kwDlInitExt()
#endif
{
   TRC2(kwDlInitExt);

   RETVALUE(ROK);
} /* kwInitExt */



/***********************************************************************
                      System Service Interface Functions
 ***********************************************************************/
/**
 *
 * @brief
 *
 *    <b> Activates Initialization </b>
 *
 *    @b Description:
 *    This function is invoked by system services to initialize the LTE-RLC
 *    layer. This is an entry point used by LTE_RLC layer to initialize its
 *    global variables, before becoming operational.
 *
 *    Allowable values for parameters are specified in ssi.h.
 *
 *    @param[in] ent    - Specify the entity id of the LTE-RLC task.
 *    @param[in] inst   - Specify the entity id of the LTE-RLC task.
 *    @param[in] region - Specifies the memory region from which
 *                         LTE-RLC should allocate structures and buffers.
 *    @param[in] reason - Specifies the reason for calling this
 *                         initialization function.
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwDlActvInit
(
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 kwDlActvInit(ent, inst, region, reason)
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
#endif
{
   KwCb    *tKwCb;
   TRC3(kwDlActvInit)

   if (inst >= KW_MAX_RLC_INSTANCES)
   {
       /* intance greater than MAX instances */ 
       RETVALUE(RFAILED); 
   }

   if (kwCb[inst] != NULLP)
   {
       RETVALUE (RFAILED);
   }
  
   if (SGetSBuf(region, 0, (Data **)&tKwCb,
                (Size)sizeof (KwCb)) != ROK)    
   {                     
      RETVALUE(RFAILED);
   }
   /* Initialize kwCb */
   KW_MEM_SET(tKwCb, 0, sizeof(KwCb));

   /* Initialize task configuration parameters */
   tKwCb->init.ent     = ent;           /* entity */
   tKwCb->init.inst    = inst;          /* instance */
   tKwCb->init.region  = region;        /* static region */
   tKwCb->init.pool    = 0;             /* static pool */
   tKwCb->init.reason  = reason;        /* reason */
   tKwCb->init.cfgDone = FALSE;         /* configuration done */
   tKwCb->init.acnt    = TRUE;          /* enable accounting */
   tKwCb->init.usta    = TRUE;          /* enable unsolicited status */
   tKwCb->init.trc     = FALSE;         /* enable trace */
   tKwCb->init.procId  = SFndProcId();

   kwCb[inst] = tKwCb;

   /* call external function for intialization */
   /*
   kwInitExt();
   */

   

   RETVALUE(ROK);
} /* kwActvInit */


/**
 *
 * @brief
 *
 *  <b> Activation Task </b>
 *
 *  @b Description:
 *  Processes events received for MLTE-RLC layer via System Services from
 *  other layers.
 *
 *  @param[in] pst   - Pst Structure
 *  @param[in] mBuf  - Message Buffer
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwDlActvTsk
(
Pst *pst,              /* pst structure */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 kwDlActvTsk(pst, mBuf)
Pst *pst;              /* pst structure */
Buffer *mBuf;           /* message buffer */
#endif
{
   S16 ret = ROK;

   TRC3(kwDlActvTsk);

   switch(pst->srcEnt)
   {
      case ENTSM:
         {
            switch(pst->event)
            {
#ifdef LCLKW
               case LKW_EVT_CFG_REQ:
                  {
                     ret = cmUnpkLkwCfgReq(KwMiLkwCfgReq, pst, mBuf);
                     break;
                  }

               case LKW_EVT_CNTRL_REQ:
                  {
                     ret = cmUnpkLkwCntrlReq(KwMiLkwCntrlReq, pst, mBuf);
                     break;
                  }

               case LKW_EVT_STS_REQ:
                  {
                     ret = cmUnpkLkwStsReq(KwMiLkwStsReq, pst, mBuf);
                     break;
                  }

               case LKW_EVT_STA_REQ:
                  {
                     ret = cmUnpkLkwStaReq(KwMiLkwStaReq, pst, mBuf);
                     break;
                  }
                  /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
               case LKW_EVT_L2MEAS_REQ:
                  {
                     ret = cmUnpkLkwL2MeasReq(KwMiLkwL2MeasReq, pst, mBuf);
                     break;
                  }
#endif
#endif  /* LCLKW */
               default:
                  KW_FREE_BUF(mBuf);
#if  (ERRCLASS & ERRCLS_DEBUG)
                  if (pst->dstInst < KW_MAX_RLC_INSTANCES)
                  {
                      KwCb *tKwCb = KW_GET_KWCB(pst->dstInst);
                      KWLOGERROR(tKwCb,ERRCLS_DEBUG, EKW029, (ErrVal)pst->event,
                        "Invalid Event");
                  }
#endif /* ERRCLASS & ERRCLS_DEBUG */
                  ret = RFAILED;
                  break;

            }
            break;
         }

      case ENTKW:
         {
            switch(pst->event)
            {
#ifdef LCUDX
               case UDX_EVT_BND_REQ:              /* Bind request */
                  {
                     ret = cmUnpkUdxBndReq(KwDlUdxBndReq, pst, mBuf );
                     break;
                  }

               case UDX_EVT_UBND_REQ:              /* Bind request */
                  {
                     ret = cmUnpkUdxUbndReq(KwDlUdxUbndReq, pst, mBuf );
                     break;
                  }
               case UDX_EVT_CFG_REQ:             /* Unbind request */
                  {
                     ret = cmUnpkUdxCfgReq(KwDlUdxCfgReq, pst, mBuf );
                     break;
                  }

               case UDX_EVT_UEIDCHG_REQ:              /* Configuration request */
                  {
                     ret = cmUnpkUdxUeIdChgReq(KwDlUdxUeIdChgReq, pst, mBuf);
                     break;
                  }

               case UDX_EVT_STA_UPD_REQ:              /* Configuration request */
                  {
                     ret = cmUnpkUdxStaUpdReq(KwDlUdxStaUpdReq, pst, mBuf);
                     break;
                  }

               case UDX_EVT_STA_PDU_REQ:              /* Configuration request */
                  {
                     ret = cmUnpkUdxStaPduReq(KwDlUdxStaPduReq, pst, mBuf);
                     break;
                  }


#endif  /* LCCKW */

               default:
                  KW_FREE_BUF(mBuf);
#if  (ERRCLASS & ERRCLS_DEBUG)
                  if (pst->dstInst < KW_MAX_RLC_INSTANCES)
                  {
                      KwCb *tKwCb = KW_GET_KWCB(pst->dstInst);
                      KWLOGERROR(tKwCb,ERRCLS_DEBUG, EKW030, (ErrVal)pst->event,
                        "Invalid Event");
                  }
#endif /* ERRCLASS & ERRCLS_DEBUG */
                  ret = RFAILED;
                  break;

            }
            break;
         }

      case ENTNH:
         {
            switch(pst->event)
            {
#ifdef LCKWU
               case KWU_EVT_BND_REQ:              /* Bind request */
                  {
                     ret = cmUnpkKwuBndReq(KwUiKwuBndReq, pst, mBuf );
                     break;
                  }

               case KWU_EVT_UBND_REQ:             /* Unbind request */
                  {
                     ret = cmUnpkKwuUbndReq(KwUiKwuUbndReq, pst, mBuf );
                     break;
                  }

               case KWU_EVT_DAT_REQ:              /* Data request */
                  {
                     ret = cmUnpkKwuDatReq(KwUiKwuDatReq, pst, mBuf);
                     break;
                  }

               case KWU_EVT_DISC_SDU_REQ:         /* Discard SDU request */
                  {
                     ret = cmUnpkKwuDiscSduReq(KwUiKwuDiscSduReq, pst, mBuf);
                     break;
                  }

#endif  /* LCKWU */
               default:
                  KW_FREE_BUF(mBuf);
#if  (ERRCLASS & ERRCLS_DEBUG)
                  if (pst->dstInst < KW_MAX_RLC_INSTANCES)
                  {
                      KwCb *tKwCb = KW_GET_KWCB(pst->dstInst);
                      KWLOGERROR(tKwCb,ERRCLS_DEBUG, EKW030, (ErrVal)pst->event,
                        "Invalid Event");
                  }
#endif /* ERRCLASS & ERRCLS_DEBUG */
                  ret = RFAILED;
                  break;

            }
            break;
         }

      case ENTPJ:
         {
            switch(pst->event)
            {
#ifdef LCKWU
               case KWU_EVT_BND_REQ:              /* Bind request */
                  {
                     ret = cmUnpkKwuBndReq(KwUiKwuBndReq, pst, mBuf );
                     break;
                  }

               case KWU_EVT_UBND_REQ:             /* Unbind request */
                  {
                     ret = cmUnpkKwuUbndReq(KwUiKwuUbndReq, pst, mBuf );
                     break;
                  }

               case KWU_EVT_DAT_REQ:              /* Data request */
                  {
                     ret = cmUnpkKwuDatReq(KwUiKwuDatReq, pst, mBuf);
                     break;
                  }

               case KWU_EVT_DISC_SDU_REQ:         /* Discard SDU request */
                  {
                     ret = cmUnpkKwuDiscSduReq(KwUiKwuDiscSduReq, pst, mBuf);
                     break;
                  }

               default:
                  KW_FREE_BUF(mBuf);
#if  (ERRCLASS & ERRCLS_DEBUG)
                  if (pst->dstInst < KW_MAX_RLC_INSTANCES)
                  {
                      KwCb *tKwCb = KW_GET_KWCB(pst->dstInst);
                      KWLOGERROR(tKwCb,ERRCLS_DEBUG, EKW031, (ErrVal)pst->event,
                        "Invalid Event");
                  }
#endif /* ERRCLASS & ERRCLS_DEBUG */
                  ret = RFAILED;
                  break;
#endif  /* LCKWU */
            }
            break;
         }

      case ENTRG:
         {
            switch(pst->event)
            {
#ifdef LCRGU
               case EVTRGUBNDCFM:     /* Bind request */
                  {
                     ret = cmUnpkRguBndCfm(KwLiRguBndCfm, pst, mBuf );
                     break;
                  }

               case EVTRGUCSTAIND:    /* Coomon Channel Status Response */
                  {
                     ret = cmUnpkRguCStaInd(KwLiRguCStaInd, pst, mBuf);
                     break;
                  }

               case EVTRGUDSTAIND:    /* Dedicated Channel Status Response */
                  {
                     ret = cmUnpkRguDStaInd(KwLiRguDStaInd, pst, mBuf);
                     break;
                  }
                  /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
               case EVTRGUHQSTAIND:    /* Harq status indication */
                  {
                     ret = cmUnpkRguHqStaInd(KwLiRguHqStaInd, pst, mBuf);
                     break;
                  }
#endif

#endif  /* LCRGU */

               default:
                  KW_FREE_BUF(mBuf);
#if  (ERRCLASS & ERRCLS_DEBUG)
                  if (pst->dstInst < KW_MAX_RLC_INSTANCES)
                  {
                      KwCb *tKwCb = KW_GET_KWCB(pst->dstInst);
                      KWLOGERROR(tKwCb,ERRCLS_DEBUG, EKW032, (ErrVal)pst->event,
                        "Invalid Event");
                  }
#endif /* ERRCLASS & ERRCLS_DEBUG */
                  ret = RFAILED;
                  break;
            }
            break;
         }

      default:
         {
#if  (ERRCLASS & ERRCLS_DEBUG)
            if (pst->dstInst < KW_MAX_RLC_INSTANCES)
            {
               KwCb *tKwCb = KW_GET_KWCB(pst->dstInst);
               KWLOGERROR(tKwCb,ERRCLS_DEBUG, EKW033, (ErrVal)pst->srcEnt,
                     "Invalid Source Entity ");
            }
#endif /* ERRCLASS & ERRCLS_DEBUG */
            KW_FREE_BUF(mBuf);
            ret = RFAILED;
            break;
         }
    }
   SExitTsk();

   RETVALUE(ret);
} /* kwActvTsk */


  
/********************************************************************30**
         End of file:     kw_dl_ex_ms.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:45 2014
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
/main/1      ---      gk   1. Initial release.
/main/2      ---      gk   1. LTERLC Release 2.1
/main/3     kw005.201 ap   1. Added support for L2 Measurement.
*********************************************************************91*/

