
/********************************************************************20**
  
     Name:     smczptmi.c - Layer Management Interface for X2AP
  
     Type:     C source file
  
     Desc:     C code for SmMiLczXxxReq functions
  
     File:    smczptmi.c
  
     Sid:      smczptmi.c@@/main/2 - Tue Aug 30 18:36:09 2011
  
     Prg:      sy
  
*********************************************************************21*/
/*

  smczptmi.c - Layer Management Interface for X2AP - SmMiLczXxxReq functions

Following functions are provided in this file:
         prUnpkMiLprCfgReq    - Unpack configuration request
*/
/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000XXX                      X2AP v 1.1
 */

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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* layer management defines for CZCP */
#include "cz.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for CZ acceptance tests */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "../../sctp/sb_mtu.h"
#include "../../sctp/sb.h"
#endif    /* SB */

#include "cm_xta.h" 
#include "smcz_err.h"


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
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* CZT Interface Structures */
#include "lcz.x"           /* layer management typedefs for CZCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "../../sctp/sb_mtu.x"
#include "../../sctp/sb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for CZCP */
#include "czac_acc.x"        /* typedefs for CZCP acceptance tests */
#include "czac_lcz.x"



#if !(defined(LCSMMILCZ)  && defined(CZ) && defined(LWLCSMMILCZ))
#define PTSMMILCZ
#endif


/* MAX Number of Service Providers of SM */
#define SM_MAX_LCZ_PROV   3

#ifdef PTSMMILCZ
/** @brief This API is used to send a 
Config Request from LM to X2AP.*/
EXTERN S16 PtMiLczCfgReq ARGS((Pst * pst, CzMngmt * cfg));
/** @brief This API is used to send a 
Statistics Request from LM to X2AP.*/
EXTERN S16 PtMiLczStsReq ARGS((Pst * pst, Action action, CzMngmt * sts));
/** @brief This API is used to send a 
Status Request from LM to X2AP.*/
EXTERN S16 PtMiLczStaReq ARGS((Pst * pst, CzMngmt * sta));
/** @brief This API is used to send a 
Control Request from LM to X2AP.*/
EXTERN S16 PtMiLczCntrlReq ARGS((Pst * pst, CzMngmt * cntrl));
#endif /*--#ifdef PTSMMILCZ--*/

/** @brief This API is used to send a 
Config Request from LM to X2AP.*/
PRIVATE CONSTANT LczCfgReq SmMiLczCfgReqMt[SM_MAX_LCZ_PROV] =
{
#ifdef LCSMMILCZ
   cmPkLczCfgReq,
#else
   PtMiLczCfgReq,
#endif
#ifdef CZ
   CzMiLczCfgReq,
#else
   PtMiLczCfgReq,
#endif
#ifdef LWLCSMMILCZ
   cmPkLczCfgReq
#else
   PtMiLczCfgReq
#endif
};

/** @brief This API is used to send a 
Statistics Request from LM to X2AP.*/
PRIVATE CONSTANT LczStsReq SmMiLczStsReqMt[SM_MAX_LCZ_PROV] =
{
#ifdef LCSMMILCZ
   cmPkLczStsReq,
#else
   PtMiLczStsReq,
#endif
#ifdef CZ
   CzMiLczStsReq,
#else
   PtMiLczStsReq,
#endif
#ifdef LWLCSMMILCZ
   cmPkLczStsReq
#else
   PtMiLczStsReq
#endif
};

/** @brief This API is used to send a 
Status Request from LM to X2AP.*/
PRIVATE CONSTANT LczStaReq SmMiLczStaReqMt[SM_MAX_LCZ_PROV] =
{
#ifdef LCSMMILCZ
   cmPkLczStaReq,
#else
   PtMiLczStaReq,
#endif
#ifdef CZ
   CzMiLczStaReq,
#else
   PtMiLczStaReq,
#endif
#ifdef LWLCSMMILCZ
   cmPkLczStaReq
#else
   PtMiLczStaReq
#endif
};

/** @brief This API is used to send a 
Control Request from LM to X2AP.*/
PRIVATE CONSTANT LczCntrlReq SmMiLczCntrlReqMt[SM_MAX_LCZ_PROV] =
{
#ifdef LCSMMILCZ
   cmPkLczCntrlReq,
#else
   PtMiLczCntrlReq,
#endif
#ifdef CZ
   CzMiLczCntrlReq,
#else
   PtMiLczCntrlReq,
#endif
#ifdef LWLCSMMILCZ
   cmPkLczCntrlReq
#else
   PtMiLczCntrlReq
#endif
};


#ifdef SM



/**
* @brief This API is used to send a 
Config Request from LM to X2AP.
*
* @details
*
*     Function : SmMiLczCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLczCfgReq
(
Pst * pst,
CzMngmt * cfg
)
#else
PUBLIC S16 SmMiLczCfgReq(pst, cfg)
Pst * pst;
CzMngmt * cfg;
#endif
{

   TRC3(SmMiLczCfgReq)

   (*SmMiLczCfgReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Statistics Request from LM to X2AP.
*
* @details
*
*     Function : SmMiLczStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   Action  action
*  @param[in]   CzMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLczStsReq
(
Pst * pst,
Action action,
CzMngmt * sts
)
#else
PUBLIC S16 SmMiLczStsReq(pst, action, sts)
Pst * pst;
Action action;
CzMngmt * sts;
#endif
{

   TRC3(SmMiLczStsReq)

   (*SmMiLczStsReqMt[pst->selector])(pst, action, sts);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Status Request from LM to X2AP.
*
* @details
*
*     Function : SmMiLczStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLczStaReq
(
Pst * pst,
CzMngmt * sta
)
#else
PUBLIC S16 SmMiLczStaReq(pst, sta)
Pst * pst;
CzMngmt * sta;
#endif
{

   TRC3(SmMiLczStaReq)

   (*SmMiLczStaReqMt[pst->selector])(pst, sta);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Control Request from LM to X2AP.
*
* @details
*
*     Function : SmMiLczCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 SmMiLczCntrlReq
(
Pst * pst,
CzMngmt * cntrl
)
#else
PUBLIC S16 SmMiLczCntrlReq(pst, cntrl)
Pst * pst;
CzMngmt * cntrl;
#endif
{

   TRC3(SmMiLczCntrlReq)

   (*SmMiLczCntrlReqMt[pst->selector])(pst, cntrl);

   RETVALUE(ROK);

}

#endif /*--ifdef SM--*/

#ifdef PTSMMILCZ



/**
* @brief This API is used to send a 
Config Request from LM to X2AP.
*
* @details
*
*     Function : PtMiLczCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczCfgReq
(
Pst * pst,
CzMngmt * cfg
)
#else
PUBLIC S16 PtMiLczCfgReq(pst, cfg)
Pst * pst;
CzMngmt * cfg;
#endif
{

   TRC3(PtMiLczCfgReq)

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Statistics Request from LM to X2AP.
*
* @details
*
*     Function : PtMiLczStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   Action  action
*  @param[in]   CzMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczStsReq
(
Pst * pst,
Action action,
CzMngmt * sts
)
#else
PUBLIC S16 PtMiLczStsReq(pst, action, sts)
Pst * pst;
Action action;
CzMngmt * sts;
#endif
{

   TRC3(PtMiLczStsReq)

   UNUSED(pst);
   UNUSED(action);
   UNUSED(sts);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Status Request from LM to X2AP.
*
* @details
*
*     Function : PtMiLczStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczStaReq
(
Pst * pst,
CzMngmt * sta
)
#else
PUBLIC S16 PtMiLczStaReq(pst, sta)
Pst * pst;
CzMngmt * sta;
#endif
{

   TRC3(PtMiLczStaReq)

   UNUSED(pst);
   UNUSED(sta);

   RETVALUE(ROK);

}



/**
* @brief This API is used to send a 
Control Request from LM to X2AP.
*
* @details
*
*     Function : PtMiLczCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   CzMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtMiLczCntrlReq
(
Pst * pst,
CzMngmt * cntrl
)
#else
PUBLIC S16 PtMiLczCntrlReq(pst, cntrl)
Pst * pst;
CzMngmt * cntrl;
#endif
{

   TRC3(PtMiLczCntrlReq)

   UNUSED(pst);
   UNUSED(cntrl);

   RETVALUE(ROK);

}
#endif /*--ifdef PTSMMILCZ--*/

/********************************************************************30**
  
         End of file:     smczptmi.c@@/main/2 - Tue Aug 30 18:36:09 2011
  
*********************************************************************31*/

/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**
 
    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---     sy              1. LTE-X2AP Initial Release.
/main/2      ---     pt              1. LTE-X2AP 3.1 release.
*********************************************************************91*/
