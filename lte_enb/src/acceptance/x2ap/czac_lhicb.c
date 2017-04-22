
/********************************************************************20**
  
     Name:     X2AP
  
     Type:     C source file
  
     Desc:     Sample code for Management Interface primitives supplied 
               by TRILLIUM
              
     File:     czac_lhicb.c
  
     Sid:      czac_lhicb.c@@/main/2 - Tue Aug 30 18:35:48 2011

     Prg:      sy
  
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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* LCZ defines */

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#ifdef HI
#include "lhi.h"
#endif

#include "cm_xta.h"

#include "cz.h"            /* defines and macros for X2AP */
#include "czt.h"            /* defines and macros for X2AP */
#include "cz_err.h"        /* X2AP error defines */
#include "czac_acc.h"        /* defines for X2AP acceptance tests */
#include <stdlib.h>

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
#include "czac_czt_inf.x"           /* SCTP Interface Structures */
#include "lcz.x"           /* X2AP types */

#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x"
#include "cz.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */
#include "czac_lhi.x"


#ifdef HI
/*
*     interface functions to layer management service user
*/
/*
*
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by Layer to present configuration confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  aqac_lhicb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SmMiLhiCfgCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLhiCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLhiCfgCfm)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLHICFGCFM;

   czAcUtlLhiSendMsg(pst, cfm, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLhiCfgCfm */


/*
*
*       Fun:   Control Confirm
*
*       Desc:  This function is used by  Layer to present control confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  aqac_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLhiCntrlCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* control */
)
#else
PUBLIC S16 SmMiLhiCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* control */
#endif
{
   TRC2(SmMiLhiCntrlCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLHICNTRLCFM;

   /*-- Drop the message if the status is OK_NDONE --*/
   if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
      RETVALUE(ROK);

   czAcUtlLhiSendMsg(pst, cfm, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLhiCntrlCfm */

/*
*
*       Fun:   Status Indication
*
*       Desc:  This function is used by Layer to present  unsolicited status 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  aqac_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLhiStaInd
(
Pst     *pst,           /* post structure */
HiMngmt *usta           /* unsolicited status */
)
#else
PUBLIC S16 SmMiLhiStaInd(pst, usta)
Pst     *pst;           /* post structure */
HiMngmt *usta;          /* unsolicited status */
#endif
{
   TRC2(SmMiLhiStaInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiStaInd(): txnId(%ld)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiStaInd(): txnId(%d)\n", usta->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLHISTAIND;

   czAcUtlLhiSendMsg(pst, usta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLhiStaInd */


/*
*
*       Fun:   Trace Indication
*
*       Desc:  This function is used by  Layer to present trace
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  aqac_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLhiTrcInd
(
Pst *pst,               /* post structure */
HiMngmt *trc,           /* trace */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 SmMiLhiTrcInd(pst, trc, mBuf)
Pst *pst;               /* post structure */
HiMngmt *trc;           /* trace */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(SmMiLhiTrcInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiTrcInd(): txnId(%d)\n", trc->hdr.transId));
#endif
   /*-- Update Event ----*/
   pst->event = EVTLHITRCIND;

   czAcUtlLhiSendMsg(pst, trc, mBuf);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLhiTrcInd */

/*
*
*       Fun:   Statistics Confirm
*
*       Desc:  This function is used by Layer to present solicited statistics 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  aqac_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLhiStsCfm
(
Pst       *pst,         /* post structure */
HiMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 SmMiLhiStsCfm(pst, sts)
Pst       *pst;         /* post structure */
HiMngmt   *sts;         /* confirmed statistics */
#endif
{
   TRC2(SmMiLhiStsCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiStsCfm(): txnId(%d)\n", sts->hdr.transId));
#endif 
   /*-- Update Event --*/
   pst->event = EVTLHISTSCFM;

   czAcUtlLhiSendMsg(pst, sts, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLhiStsCfm */

/*
*
*       Fun:   Status Confirm
*
*       Desc:  This function is used by Layer to present solicited status 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  aqac_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLhiStaCfm
(
Pst     *pst,           /* post structure */
HiMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 SmMiLhiStaCfm(pst, sta)
Pst     *pst;           /* post structure */
HiMngmt *sta;            /* confirmed status */
#endif
{
   TRC2(SmMiLhiStaCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLhiStaCfm(): txnId(%d)\n", sta->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLHISTACFM;

   czAcUtlLhiSendMsg(pst, sta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of SmMiLhiStaCfm */

#endif /* ifdef HI */
/********************************************************************30**

         End of file:     czac_lhicb.c@@/main/2 - Tue Aug 30 18:35:48 2011

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
/main/1      ---       sy       1. LTE-X2AP Initial Release.
/main/2      ---      pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
