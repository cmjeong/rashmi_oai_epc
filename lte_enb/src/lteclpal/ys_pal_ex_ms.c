/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_ex_ms.c
  
     Sid:      yw_ex_ms.c@@/main/2 - Thu Dec  2 02:27:25 2010
  
     Prg:      pk
  
**********************************************************************/

/** @file ys_ex_ms.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* Trillium Includes */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer defines */
#include "cm_tkns.h"       /* Common tokens defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_llist.h"      /* Common link list defines  */
#include "cm_hash.h"       /* Common hashlist defines */
#include "cm_lte.h"        /* Common LTEE defines */
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"


#ifdef YS_MSPD
#else
#include <sys/time.h>
#include "ys_pal.h"
#endif /* YS_MSPD*/
#include "ys_pal_err.h"        /* CL error header file */


#include "gen.x"           /* General */
#include "ssi.x"           /* System services */

#include "cm5.x"           /* Common timer library */
#include "cm_tkns.x"       /* Common tokens */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_llist.x"      /* Common link list */
#include "cm_hash.x"       /* Common hashlist */
#include "cm_lte.x"        /* Common LTE includes */
#include "ctf.x"
#include "cm_lib.x"
#include "tfu.x"
#include "lys.x"

#ifdef TIP_LOWER_L2
#include "tip_cmn.h"
#endif

#ifdef YS_MSPD
#else
#include "ys_pal.x"            /* typedefs for CL */
#endif /* YS_MSPD */
/*ys004.102 MSPD merge for PHY 1.7*/
/** @brief This is the activation task of the CL layer. 
 * @param pst pointer to the Pst structure
 * @param mBuf pointer to the Buffer. 
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 ysActvTsk
(
Pst     *pst,
Buffer  *mBuf
)
#else
PUBLIC S16 ysActvTsk (pst, mBuf)
Pst     *pst;
Buffer  *mBuf;
#endif
{
   S16       ret   = ROK;
#ifdef MSPD
   U8        ptr[1000];
#endif

   TRC3(ysActvTsk)

   ret = ROK;

   switch(pst->srcEnt)
   {
#if defined(YS_MSPD) || defined(YS_PICO)
      /* The originator of this message is the stack manager,
       * unpack and go to the respective primitive processing function */
      case ENTSM:
         switch(pst->event)
         {
#ifdef LCYSMILYS
            case EVTLYSCFGREQ:
               /* Process a config. request */
               cmUnpkLysCfgReq(YsMiLysCfgReq, pst, mBuf);
               break;
            case EVTLYSCNTRLREQ:
               /* Process a control request */
               cmUnpkLysCntrlReq(YsMiLysCntrlReq, pst, mBuf);
               break;
            case EVTLYSSSTAREQ:
               /* Process a status request  */
               cmUnpkLysStaReq(YsMiLysStaReq, pst, mBuf);
               break;
            case EVTLYSSTSREQ:
               /* Process a statistics request */
               cmUnpkLysStsReq(YsMiLysStsReq, pst, mBuf);
               break;
#endif /* LCYSMILYS */
            default:
               YS_DBG_ERR((_ysp, "ysActvTsk(): Invalid event (%d)! \n",
                           pst->event));
               SPutMsg(mBuf);
               break;
         }
         break;

      case ENTRG:
         switch (pst->event)
         {
#ifdef LCYSUITFU
            case EVTTFUBNDREQ:
               ret = cmUnpkTfuBndReq (YsUiTfuBndReq, pst, mBuf);
               break;
#ifdef MSPD
            case EVTTFUSCHBNDREQ:
               ret = cmUnpkTfuBndReq (YsUiTfuSchBndReq, pst, mBuf);
               break;
#endif
            case EVTTFUUBNDREQ:
               ret = cmUnpkTfuUbndReq (YsUiTfuUbndReq, pst, mBuf);
               break;
            case EVTTFUCNTRLREQ:
               ret = cmUnpkTfuCntrlReq (YsUiTfuCntrlReq, pst, mBuf);
               break;
            case EVTTFUDATREQ:
               ret = cmUnpkTfuDatReq (YsUiTfuDatReq, pst, mBuf);
               break;
            case EVTTFURECPREQ:
               ret = cmUnpkTfuRecpReq (YsUiTfuRecpReq, pst, mBuf);
               break;
#endif
            default:
               YS_DBG_ERR((_ysp, "ysActvTsk(): Invalid event (%d)! \n",
                           pst->event));
               SPutMsg(mBuf);
               break;

         } /* end of switch (evnt) */
         break;
#endif /* YS_MSPD or YS_PICO */

#if (defined(YS_PICO) || (defined(YS_LTE_PAL) && defined (LTE_PAL_ENB)) || defined(YS_MSPD))
      case ENTVE:
      case ENTNH:
         switch (pst->event)
         {
#ifdef LCYSUICTF
            case EVTCTFBNDREQ:
               ret = cmUnpkCtfBndReq (YsUiCtfBndReq, pst, mBuf);
               break;
            case EVTCTFUBNDREQ:
               ret = cmUnpkCtfUbndReq (YsUiCtfUbndReq, pst, mBuf);
               break;
            case EVTCTFCFGREQ:
               ret = cmUnpkCtfCfgReq (YsUiCtfCfgReq, pst, mBuf);
               break;
#ifdef TIP_LOWER_L2
           case EVTL1TIPPMSG:
               ret = tipUnpkAppL1Msg(pst, mBuf); 
               break;
#endif
#endif
            default:
               YS_DBG_ERR((_ysp, "ysActvTsk(): Invalid event (%d)! \n",
                           pst->event));
               SPutMsg(mBuf);
               break;

         } /* end of switch (evnt) */
         break;
#endif

      case ENTTF:
#ifdef MSPD
         /* self post: there can be only one event coming from the receiver thread
          * which is the uplink data
          */
         ret = ysReceivePHYMsg(mBuf);
         break;
#else
         switch(pst->event)
         {
#ifdef LTE_PAL_ENB
            case EVTTFURAREQIND:
               cmUnpkTfuRaReqInd(YsUiTfuRaReqInd, pst, mBuf);
               break;
            case EVTTFUHQIND:
               cmUnpkTfuHqInd(YsUiTfuHqInd, pst, mBuf);
               break;
            case EVTTFUSRIND:
               cmUnpkTfuSrInd(YsUiTfuSrInd, pst, mBuf);
               break;
            case EVTTFUDATIND:
               cmUnpkTfuDatInd(YsUiTfuDatInd, pst, mBuf);
               break;
            case EVTTFUTTIIND:
               ysPrcTmrExpiry(NULLP, YS_TTI_TMR_EVNT);
               SPutMsg(mBuf);
               break;
            case EVTTFUTIMINGADVIND:
               cmUnpkTfuTimingAdvInd(YsUiTfuTimingAdvInd, pst, mBuf);
               break;
            case EVTTFUDLCQIIND:
               cmUnpkTfuDlCqiInd(YsUiTfuDlCqiInd, pst, mBuf);
               break;
#else /* LTE_PAL_ENB */
            case EVTTFUCNTRLREQ:
               cmUnpkTfuCntrlReq(YsUiTfuCntrlReq, pst, mBuf);
               break;
            case EVTTFUDATREQ:
               cmUnpkTfuDatReq(YsUiTfuDatReq, pst, mBuf);
               break;
            case EVTTFURECPREQ:
               ret = cmUnpkTfuRecpReq(YsUiTfuRecpReq, pst, mBuf);
               break;
#endif /* LTE_PAL_ENB */
            default:
               YS_DBG_ERR((_ysp, "ysActvTsk(): Invalid event (%d)! \n",pst->event));
               SPutMsg(mBuf);
               break;
         }
         break;
#endif

      default:
         YS_DBG_ERR((_ysp, "ysActvTsk(): Message from an invalid \
                              entity (%d)! \n", pst->srcEnt));
         SPutMsg(mBuf);
         ret = RFAILED;

   } /* end of switch */

   SExitTsk();
   RETVALUE (ret);
} /* end of ysActvTsk */

/********************************************************************30**
  
         End of file:     yw_ex_ms.c@@/main/2 - Thu Dec  2 02:27:25 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/1      ys004.102     vr              1. MSPD merge for PHY 1.7
*********************************************************************91*/
