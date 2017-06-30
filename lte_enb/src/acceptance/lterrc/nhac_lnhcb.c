
/********************************************************************20**

     Name:     nhac_lnhcb.c - Dummy Stack Manager (Layer Manager) for the
               RRC layer.
     Type:     C source file

     Desc:     C code for layer manager service provider primitives that
               are usually supplied by the customer.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     nhac_lnhcb.c

     Sid:      nhac_lnhcb.c@@/main/3 - Fri Jul  1 01:13:03 2011

     Prg:      dm

*********************************************************************21*/

/* header include files (.h) */
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
/* external headers */


/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhac_asn.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"

/*
*
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_lnhcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnhCfgCfm
(
Pst     *pst,          /* post structure */
NhMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLnhCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
NhMngmt *cfm;          /* configuration */
#endif
{
   TRC2(nhAcSmMiLnhCfgCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLNHCFGCFM;

   nhAcUtlLnhSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* end of nhAcSmMiLnhCfgCfm */


/*
*
*       Fun:   Control Confirm
*
*       Desc:  This function is used by to present control confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_lnhcb.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLnhCntrlCfm
(
Pst     *pst,          /* post structure */
NhMngmt *cfm           /* control */
)
#else
PUBLIC S16 SmMiLnhCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
NhMngmt *cfm;          /* control */
#endif
{

   TRC2(nhAcSmMiLnhCntrlCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLNHCNTRLCFM;

   /*-- Drop the message if the status is OK_NDONE --*/
   if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
      RETVALUE(ROK);

   nhAcUtlLnhSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* end of nhAcSmMiLnhCntrlCfm */


/*
*
*       Fun:   Status Indication
*
*       Desc:  This function is used by to present  unsolicited status 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_lnhcb.c
*
*/
#ifdef ANSI
PUBLIC S16 SmMiLnhStaInd
(
Pst     *pst,           /* post structure */
NhMngmt *usta           /* unsolicited status */
)
#else
PUBLIC S16 SmMiLnhStaInd(pst, usta)
Pst     *pst;           /* post structure */
NhMngmt *usta;          /* unsolicited status */
#endif
{

   TRC2(nhAcSmMiLnhStaInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhStaInd(): txnId(%ld)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhStaInd(): txnId(%d)\n", usta->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLNHSTAIND;

   nhAcUtlLnhSendMsg(pst, usta, NULLP);

   RETVALUE(ROK);
} /* end of nhAcSmMiLnhStaInd */



/*
*
*       Fun:   Trace Indication
*
*       Desc:  This function is used to present trace
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_lnhcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnhTrcInd
(
Pst *pst,               /* post structure */
NhMngmt *trc           /* trace */
)
#else
PUBLIC S16 SmMiLnhTrcInd(pst, trc)
Pst *pst;               /* post structure */
NhMngmt *trc;           /* trace */
#endif
{
   TRC2(nhAcSmMiLnhTrcInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhTrcInd(): txnId(%d)\n", trc->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLNHTRCIND;

   nhAcUtlLnhSendMsg(pst, trc, NULLP);

   RETVALUE(ROK);
} /* end of nhAcSmMiLnhTrcInd */


/*
*
*       Fun:   Statistics Confirm
*
*       Desc:  This function is used to present solicited statistics 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_lnhcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnhStsCfm
(
Pst       *pst,         /* post structure */
NhMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 SmMiLnhStsCfm(pst, sts)
Pst       *pst;         /* post structure */
NhMngmt   *sts;         /* confirmed statistics */
#endif
{
   TRC2(nhAcSmMiLnhStsCfm)

#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhStsCfm(): txnId(%d)\n", sts->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLNHSTSCFM;

   nhAcUtlLnhSendMsg(pst, sts, NULLP);

   RETVALUE(ROK);
} /* end of nhAcSmMiLnhStsCfm */

/*
*
*       Fun:   Status Confirm
*
*       Desc:  This function is used to present status 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_lnhcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnhStaCfm
(
Pst     *pst,           /* post structure */
NhMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 SmMiLnhStaCfm(pst, sta)
Pst     *pst;           /* post structure */
NhMngmt *sta;            /* confirmed status */
#endif
{
   TRC2(nhAcSmMiLnhStaCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcSmMiLnhStaCfm(): txnId(%d)\n", sta->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = EVTLNHSTACFM;

   nhAcUtlLnhSendMsg(pst, sta, NULLP);

   RETVALUE(ROK);
} /* end of nhAcSmMiLnhStaCfm */




/********************************************************************30**

         End of file:     nhac_lnhcb.c@@/main/3 - Fri Jul  1 01:13:03 2011

*********************************************************************31*/
/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**

   ver       pat     init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---     dm               1. LTE RRC Initial Release.
/main/2      ---     chebli           1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
