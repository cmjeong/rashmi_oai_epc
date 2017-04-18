/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_pal_ptui.c
  
     Sid:      ys_pal_ptui.c@@/main/2 - Thu Dec  2 02:27:19 2010
  
     Prg:      hsingh
  
**********************************************************************/

/** @file ys_pal_ptui.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"
#include "lys.h"           /* layer management typedefs for CL */
#include "tfu.h"
#include "ys_pal_err.h"        /* YS error defines */
#include "ys_pal.h" 

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#include "ys_pal.x" 

/* header include files -- defines (.h) */

/* header/extern include files (.x) */

#ifndef LTE_PAL_ENB

#if !(defined(LCYSUITFU)  && defined(RG) && defined(LWLCYSUITFU))
#define PTYSUITFU
#endif


/* MAX Number of Service Users of YS at TFU interface */
#define YS_MAX_TFU_USR   3

#ifdef PTYSUITFU
EXTERN S16 PtLiTfuDatReq ARGS((Pst * pst, SpId spId, TfuDatReqInfo * datReq));
EXTERN S16 PtLiTfuCntrlReq ARGS((Pst * pst, SpId spId, TfuCntrlReqInfo * datReq));
EXTERN S16 PtLiTfuRecpReq ARGS((Pst * pst, SpId spId, TfuRecpReqInfo * recpReq)); 
#endif /*--#ifdef PTYSUITFU--*/


/** @brief This API is used to send Data Request from MAC to PHY.
 */
PRIVATE CONSTANT TfuDatReq YsUiTfuDatReqMt[YS_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuDatReq,
#else
   PtLiTfuDatReq,
#endif
#ifdef RG
   RgLiTfuDatReq,
#else
   PtLiTfuDatReq,
#endif
#ifdef LWLCYSUITFU
   cmPkTfuDatReq,
#else
   PtLiTfuDatReq,
#endif
};

/** @brief This API is used to send Data Request from MAC to PHY.
 */
PRIVATE CONSTANT TfuCntrlReq YsUiTfuCntrlReqMt[YS_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuCntrlReq,
#else
   PtLiTfuCntrlReq,
#endif
#ifdef RG
   RgLiTfuCntrlReq,
#else
   PtLiTfuCntrlReq,
#endif
#ifdef LWLCYSUITFU
   cmPkTfuCntrlReq,
#else
   PtLiTfuCntrlReq,
#endif
};

/** @brief This API is used to send a Data Reception request from MAC to PHY
 */
PRIVATE CONSTANT TfuRecpReq YsUiTfuRecpReqMt[YS_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuRecpReq,
#else
   PtLiTfuRecpReq,
#endif
#ifdef RG
   RgLiTfuRecpReq,
#else
   PtLiTfuRecpReq,
#endif
#ifdef LWLCYSUITFU
   cmPkTfuRecpReq,
#else
   PtLiTfuRecpReq,
#endif
};

#ifdef YS

/**
* @brief This API is used to send Data Request from PAL to MAC.
*
* @details
*
*     Function : YsUiTfuDatReq
*
*  @param[in]   Pst *  pst
*  @param[in]   SpId  spId
*  @param[in]   TfuDatReqInfo *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 YsUiTfuDatReq
(
Pst * pst,
SpId spId,
TfuDatReqInfo * datReq
)
#else
PUBLIC S16 YsUiTfuDatReq(pst, spId, datReq)
Pst * pst;
SpId spId;
TfuDatReqInfo * datReq;
#endif
{

   TRC3(YsUiTfuDatReq)

   pst->selector = YS_SELECTOR_TC;
   (*YsUiTfuDatReqMt[pst->selector])(pst, spId, datReq);

   RETVALUE(ROK);
}


/**
* @brief This API is used to send Data Request from PAL to MAC.
*
* @details
*
*     Function : YsUiTfuCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   SpId  spId
*  @param[in]   TfuCntrlReqInfo *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 YsUiTfuCntrlReq
(
Pst * pst,
SpId spId,
TfuCntrlReqInfo * cntrlReq
)
#else
PUBLIC S16 YsUiTfuCntrlReq(pst, spId, cntrlReq)
Pst * pst;
SpId spId;
TfuCntrlReqInfo * cntrlReq;
#endif
{
   CmLteTimingInfo timingInfo;

   TRC3(YsUiTfuCntrlReq)

   cmMemcpy((U8 *)&timingInfo, (U8 *)&cntrlReq->dlTiming, sizeof(CmLteTimingInfo));

   pst->selector = YS_SELECTOR_TC;
   (*YsUiTfuCntrlReqMt[pst->selector])(pst, spId, cntrlReq);

   ysPalHdlDlMsg(&timingInfo);

   RETVALUE(ROK);
}


/**
* @brief This API is used to send a Data Reception request from PAL to MAC
*
* @details
*
*     Function : YsUiTfuDatRecpReq
*
*  @param[in]   Pst *  pst
*  @param[in]   SpId  spId
*  @param[in]   TfuRecpReqInfo *  recpReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 YsUiTfuRecpReq
(
Pst * pst,
SpId spId,
TfuRecpReqInfo * recpReq
)
#else
PUBLIC S16 YsUiTfuRecpReq(pst, spId, recpReq)
Pst * pst;
SpId spId;
TfuRecpReqInfo * recpReq;
#endif
{
   CmLteTimingInfo timingInfo;

   TRC3(YsUiTfuRecpReq)

   cmMemcpy((U8 *)&timingInfo, (U8 *)&recpReq->timingInfo, sizeof(CmLteTimingInfo));
   
   pst->selector = YS_SELECTOR_TC;
   (*YsUiTfuRecpReqMt[pst->selector])(pst, spId, recpReq);

   ysPalHdlDlMsg(&timingInfo);

   RETVALUE(ROK);
}

#endif /*--ifdef YS--*/


#ifdef PTYSUITFU

/**
* @brief This API is used to send Data Request from PAL to MAC.
*
* @details
*
*     Function : PtLiTfuDatReq
*
*  @param[in]   Pst *  pst
*  @param[in]   SpId  spId
*  @param[in]   TfuDatReqInfo *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiTfuDatReq
(
Pst * pst,
SpId spId,
TfuDatReqInfo * datReq
)
#else
PUBLIC S16 PtLiTfuDatReq(pst, spId, datReq)
Pst * pst;
SpId spId;
TfuDatReqInfo * datReq;
#endif
{

   TRC3(PtLiTfuDatReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(datReq);

   RETVALUE(ROK);

}


/**
* @brief This API is used to send Data Request from PAL to MAC.
*
* @details
*
*     Function : PtLiTfuCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   SpId  spId
*  @param[in]   TfuCntrlReqInfo *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiTfuCntrlReq
(
Pst * pst,
SpId spId,
TfuCntrlReqInfo * datReq
)
#else
PUBLIC S16 PtLiTfuCntrlReq(pst, spId, datReq)
Pst * pst;
SpId spId;
TfuCntrlReqInfo * datReq;
#endif
{

   TRC3(PtLiTfuCntrlReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(datReq);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a Data Reception request from PAL to MAC
*
* @details
*
*     Function : PtLiTfuRecpReq
*
*  @param[in]   Pst *  pst
*  @param[in]   SpId  spId
*  @param[in]   TfuRecpReqInfo *  recpReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiTfuRecpReq
(
Pst * pst,
SpId spId,
TfuRecpReqInfo * recpReq
)
#else
PUBLIC S16 PtLiTfuRecpReq(pst, spId, recpReq)
Pst * pst;
SpId spId;
TfuRecpReqInfo * recpReq;
#endif
{

   TRC3(PtLiTfuRecpReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(recpReq);

   RETVALUE(ROK);

}

#endif /*--ifdef PTTFUITFU--*/

#endif /* LTE_PAL_ENB */ 
/********************************************************************30**
  
         End of file:     ys_pal_ptui.c@@/main/2 - Thu Dec  2 02:27:19 2010
  
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
*********************************************************************91*/
