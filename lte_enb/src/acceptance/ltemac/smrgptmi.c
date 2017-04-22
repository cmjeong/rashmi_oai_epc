

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      smrgptmi.c@@/main/3 - Sat Jul 30 02:22:23 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_acc.h"        /* MAC error defines */
#include "rgac_lrg.h"        /* MAC error defines */
#include <stdlib.h>

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"        /* MAC error defines */
#include "rgac_lrg.x"        /* MAC error defines */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !(defined(LCSMLILRG)  && defined(RG) && defined(LWLCSMLILRG))
#define PTSMLILRG
#endif


/* MAX Number of Service Providers of SM */
#define SM_MAX_LRG_PROV   3

#ifdef PTSMLILRG
/** @brief This API is used to send a 
Config Request from LM to MAC.*/
EXTERN S16 PtLiLrgCfgReq ARGS((Pst * pst, RgMngmt * cfg));
EXTERN S16 PtLiLrgSchCfgReq ARGS((Pst * pst, RgMngmt * cfg));
#ifdef LTE_L2_MEAS
EXTERN S16 PtLiLrgSchL2MeasReq ARGS((Pst * pst,LrgSchMeasReqInfo *meas));
EXTERN S16 PtLiLrgSchL2SendMeasReq ARGS((Pst * pst,LrgSchMeasSndReqInfo *meas));
EXTERN S16 PtLiLrgSchL2StopMeasReq ARGS((Pst * pst,LrgSchMeasStopReqInfo *meas));
#endif
/** @brief This API is used to send a 
Statistics Request from LM to MAC.*/
EXTERN S16 PtLiLrgStsReq ARGS((Pst * pst, RgMngmt * sts));
/** @brief This API is used to send a 
Status Request from LM to MAC.*/
EXTERN S16 PtLiLrgStaReq ARGS((Pst * pst, RgMngmt * sta));
/** @brief This API is used to send a 
Control Request from LM to MAC.*/
EXTERN S16 PtLiLrgCntrlReq ARGS((Pst * pst, RgMngmt * cntrl));
EXTERN S16 PtLiLrgSchCntrlReq ARGS((Pst * pst, RgMngmt * cntrl));
#endif /*--#ifdef PTSMLILRG--*/

/** @brief This API is used to send a 
Config Request from LM to MAC.*/
PRIVATE CONSTANT LrgCfgReq SmLiLrgCfgReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgCfgReq,
#else
   PtLiLrgCfgReq,
#endif
#ifdef RG
   RgMiLrgCfgReq,
#else
   PtLiLrgCfgReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgCfgReq
#else
   PtLiLrgCfgReq
#endif
};
/** @brief This API is used to send  
Scheduler Config Request from LM to MAC (Scheduler Instance).*/
PRIVATE CONSTANT LrgSchCfgReq SmMiLrgSchCfgReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgSchCfgReq,
#else
   PtLiLrgSchCfgReq,
#endif
#ifdef RG
   RgMiLrgSchCfgReq,
#else
   PtLiLrgSchCfgReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgSchCfgReq
#else
   PtLiLrgSchCfgReq
#endif
};

/** @brief This API is used to send a 
Statistics Request from LM to MAC.*/
PRIVATE CONSTANT LrgStsReq SmLiLrgStsReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgStsReq,
#else
   PtLiLrgStsReq,
#endif
#ifdef RG
   RgMiLrgStsReq,
#else
   PtLiLrgStsReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgStsReq
#else
   PtLiLrgStsReq
#endif
};

/** @brief This API is used to send a 
Status Request from LM to MAC.*/
PRIVATE CONSTANT LrgStaReq SmLiLrgStaReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgStaReq,
#else
   PtLiLrgStaReq,
#endif
#ifdef RG
   RgMiLrgStaReq,
#else
   PtLiLrgStaReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgStaReq
#else
   PtLiLrgStaReq
#endif
};

/** @brief This API is used to send a 
Control Request from LM to MAC.*/
PRIVATE CONSTANT LrgCntrlReq SmLiLrgCntrlReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgCntrlReq,
#else
   PtLiLrgCntrlReq,
#endif
#ifdef RG
   RgMiLrgCntrlReq,
#else
   PtLiLrgCntrlReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgCntrlReq
#else
   PtLiLrgCntrlReq
#endif
};

/** @brief This API is used to send a 
Control Request from LM to MAC (Scheduler Instance).*/
PRIVATE CONSTANT LrgSchCntrlReq SmLiLrgSchCntrlReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgSchCntrlReq,
#else
   PtLiLrgSchCntrlReq,
#endif
#ifdef RG
   RgMiLrgSchCntrlReq,
#else
   PtLiLrgSchCntrlReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgSchCntrlReq
#else
   PtLiLrgSchCntrlReq
#endif
};

#ifdef LTE_L2_MEAS
/** @brief This API is used to send  
L2 Measurement Request from LM to MAC (Scheduler Instance).*/
PRIVATE CONSTANT LrgSchL2MeasReq SmLiLrgSchL2MeasReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgSchL2MeasReq,
#else
   PtLiLrgSchL2MeasReq,
#endif
#ifdef RG
   RgMiLrgSchL2MeasReq,
#else
   PtLiLrgSchL2MeasReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgSchL2MeasReq
#else
   PtLiLrgSchL2MeasReq
#endif
};

/* Anshika Start */
/** @brief This API is used to send  
L2 Measurement Request from LM to MAC (Scheduler Instance).*/
PRIVATE CONSTANT LrgSchL2MeasSendReq SmLiLrgSchL2SendMeasReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgSchL2MeasSendReq,
#else
   PtLiLrgSchL2SendMeasReq,
#endif
#ifdef RG
   RgMiLrgSchL2MeasSendReq,
#else
   PtLiLrgSchL2SendMeasReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgSchL2MeasSendReq
#else
   PtLiLrgSchL2SendMeasReq
#endif
};

/** @brief This API is used to send  
L2 Measurement Request from LM to MAC (Scheduler Instance).*/
PRIVATE CONSTANT LrgSchL2MeasStopReq SmLiLrgSchL2StopMeasReqMt[SM_MAX_LRG_PROV] =
{
#ifdef LCSMLILRG
   cmPkLrgSchL2MeasStopReq,
#else
   PtLiLrgSchL2StopMeasReq,
#endif
#ifdef RG
   RgMiLrgSchL2MeasStopReq,
#else
   PtLiLrgSchL2StopMeasReq,
#endif
#ifdef LWLCSMLILRG
   cmPkLrgSchL2MeasStopReq
#else
   PtLiLrgSchL2StopMeasReq
#endif
};

/* Anshika End */
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef SM



/**
* @brief This API is used to send a 
Config Request from LM to MAC.
*
* @details
*
*     Function : SmLiLrgCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 SmMiLrgCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{

   TRC3(SmMiLrgCfgReq);

   (*SmLiLrgCfgReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);

}

/**
* @brief This API is used to send  
Scheduler Config Request from LM to MAC(Scheduler Instance).
*
* @details
*
*     Function : SmMiLrgSchCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 SmMiLrgSchCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{

   TRC3(SmMiLrgSchCfgReq);

   (*SmMiLrgSchCfgReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);

}


/**
* @brief This API is used to send a 
Statistics Request from LM to MAC.
*
* @details
*
*     Function : SmLiLrgStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgStsReq
(
Pst * pst,
RgMngmt * sts
)
#else
PUBLIC S16 SmMiLrgStsReq(pst, sts)
Pst * pst;
RgMngmt * sts;
#endif
{

   TRC3(SmMiLrgStsReq);

   (*SmLiLrgStsReqMt[pst->selector])(pst, sts);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Status Request from LM to MAC.
*
* @details
*
*     Function : SmLiLrgStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgStaReq
(
Pst * pst,
RgMngmt * sta
)
#else
PUBLIC S16 SmMiLrgStaReq(pst, sta)
Pst * pst;
RgMngmt * sta;
#endif
{

   TRC3(SmMiLrgStaReq);

   (*SmLiLrgStaReqMt[pst->selector])(pst, sta);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Control Request from LM to MAC.
*
* @details
*
*     Function : SmLiLrgCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 SmMiLrgCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{

   TRC3(SmMiLrgCntrlReq);

   (*SmLiLrgCntrlReqMt[pst->selector])(pst, cntrl);

   RETVALUE(ROK);

}

/**
* @brief This API is used to send a 
Control Request from LM to MAC (Scheduler Instance).
*
* @details
*
*     Function : SmLiLrgSchCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 SmMiLrgSchCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{

   TRC3(SmMiLrgSchCntrlReq);

   (*SmLiLrgSchCntrlReqMt[pst->selector])(pst, cntrl);

   RETVALUE(ROK);

}
#ifdef LTE_L2_MEAS

/**
* @brief This API is used to send a 
L2 Measurement Request from LM to MAC (Scheduler Instance).
*
* @details
*
*     Function : SmMiLrgSchL2MeasReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2MeasReq
(
Pst * pst,
LrgSchMeasReqInfo *meas 
)
#else
PUBLIC S16 SmMiLrgSchL2MeasReq(pst, meas)
Pst * pst;
LrgSchMeasReqInfo *meas ;
#endif
{

   TRC3(SmMiLrgSchL2MeasReq);

   (*SmLiLrgSchL2MeasReqMt[pst->selector])(pst, meas);

   RETVALUE(ROK);

}
/* Anshika Start */

/**
* @brief This API is used to send a 
L2 Measurement Request from LM to MAC (Scheduler Instance).
*
* @details
*
*     Function : SmMiLrgSchL2SendMeasReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2SendMeasReq
(
Pst * pst,
LrgSchMeasSndReqInfo *meas 
)
#else
PUBLIC S16 SmMiLrgSchL2SendMeasReq(pst, meas)
Pst * pst;
LrgSchMeasSndReqInfo *meas ;
#endif
{

   TRC3(SmMiLrgSchL2SendMeasReq);

   (*SmLiLrgSchL2SendMeasReqMt[pst->selector])(pst, meas);

   RETVALUE(ROK);

}


/**
* @brief This API is used to send a 
L2 Measurement Request from LM to MAC (Scheduler Instance).
*
* @details
*
*     Function : SmMiLrgSchL2StopMeasReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLrgSchL2StopMeasReq
(
Pst * pst,
LrgSchMeasStopReqInfo *meas 
)
#else
PUBLIC S16 SmMiLrgSchL2StopMeasReq(pst, meas)
Pst * pst;
LrgSchMeasStopReqInfo *meas ;
#endif
{

   TRC3(SmMiLrgSchL2StopMeasReq);

   (*SmLiLrgSchL2StopMeasReqMt[pst->selector])(pst, meas);

   RETVALUE(ROK);

}

/* Anshika End */

#endif /*--ifdef LTE_L2_MEAS --*/
#endif /*--ifdef SM--*/

#ifdef PTSMLILRG



/**
* @brief This API is used to send a 
Config Request from LM to MAC.
*
* @details
*
*     Function : PtLiLrgCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 PtLiLrgCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{

   TRC3(PtLiLrgCfgReq);

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);

}

/**
* @brief This API is used to send a 
Scheduler Config Request from LM to MAC (Scheduler Instance).
*
* @details
*
*     Function : PtLiLrgSchCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgSchCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 PtLiLrgSchCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{

   TRC3(PtLiLrgSchCfgReq);

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Statistics Request from LM to MAC.
*
* @details
*
*     Function : PtLiLrgStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgStsReq
(
Pst * pst,
RgMngmt * sts
)
#else
PUBLIC S16 PtLiLrgStsReq(pst, sts)
Pst * pst;
RgMngmt * sts;
#endif
{

   TRC3(PtLiLrgStsReq);

   UNUSED(pst);
   UNUSED(sts);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Status Request from LM to MAC.
*
* @details
*
*     Function : PtLiLrgStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgStaReq
(
Pst * pst,
RgMngmt * sta
)
#else
PUBLIC S16 PtLiLrgStaReq(pst, sta)
Pst * pst;
RgMngmt * sta;
#endif
{

   TRC3(PtLiLrgStaReq);

   UNUSED(pst);
   UNUSED(sta);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Control Request from LM to MAC.
*
* @details
*
*     Function : PtLiLrgCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 PtLiLrgCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{

   TRC3(PtLiLrgCntrlReq);

   UNUSED(pst);
   UNUSED(cntrl);

   RETVALUE(ROK);

}

/**
* @brief This API is used to send a 
Control Request from LM to MAC(Scheduler Instance).
*
* @details
*
*     Function : PtLiLrgSchCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgSchCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 PtLiLrgSchCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{

   TRC3(PtLiLrgSchCntrlReq);

   UNUSED(pst);
   UNUSED(cntrl);

   RETVALUE(ROK);

}

#ifdef LTE_L2_MEAS

/**
* @brief This API is used to send a 
L2 Measurement  Request from LM to MAC(Scheduler Instance).
*
* @details
*
*     Function : PtLiLrgSchL2MeasReq
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchL2MeasReqInfo *  meas
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgSchL2MeasReq
(
Pst * pst,
LrgSchMeasReqInfo *meas
)
#else
PUBLIC S16 PtLiLrgSchL2MeasReq(pst, meas)
Pst * pst;
LrgSchMeasReqInfo  * meas;
#endif
{

   TRC3(PtLiLrgSchL2MeasReq);

   UNUSED(pst);
   UNUSED(meas);

   RETVALUE(ROK);

}

/* Anshika Start */

/**
* @brief This API is used to send a 
L2 Measurement  Request from LM to MAC(Scheduler Instance).
*
* @details
*
*     Function : PtLiLrgSchL2SendMeasReq
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchL2SendMeasReqInfo *  meas
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgSchL2SendMeasReq
(
Pst * pst,
LrgSchMeasSndReqInfo *meas
)
#else
PUBLIC S16 PtLiLrgSchL2SendMeasReq(pst, meas)
Pst * pst;
LrgSchMeasSndReqInfo  * meas;
#endif
{

   TRC3(PtLiLrgSchL2SendMeasReq);

   UNUSED(pst);
   UNUSED(meas);

   RETVALUE(ROK);

}


/**
* @brief This API is used to send a 
L2 Measurement  Request from LM to MAC(Scheduler Instance).
*
* @details
*
*     Function : PtLiLrgSchL2StopMeasReq
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchL2StopMeasReqInfo *  meas
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiLrgSchL2StopMeasReq
(
Pst * pst,
LrgSchMeasStopReqInfo *meas
)
#else
PUBLIC S16 PtLiLrgSchL2MeasReq(pst, meas)
Pst * pst;
LrgSchMeasStopReqInfo  * meas;
#endif
{

   TRC3(PtLiLrgSchL2StopMeasReq);

   UNUSED(pst);
   UNUSED(meas);

   RETVALUE(ROK);

}
/* Anshika End */

#endif
#endif /*--ifdef PTSMLILRG--*/



/**********************************************************************
 
         End of file:     smrgptmi.c@@/main/3 - Sat Jul 30 02:22:23 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     ps              1. Initial Release.
/main/2      ---     ps              1. LTE MAC 2.1 release
/main/3      ---     dv              1. LTE MAC 3.1 release
*********************************************************************91*/
