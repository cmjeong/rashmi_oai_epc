
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_egtreg.c

     Sid:      egac_egtreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:29 2015

     Prg:    an 
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
#include "cm_dns.h"         /* common DNS libraru defines */

#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for EG */
#include "leg.h"            /* defines and macros for EG */
#include "egt.h"            /* defines and macros for EG */
#include "eg_err.h"        /* EG error defines */
#include "egac_acc.h"        /* defines for EG acceptance tests */
#include "cm_xta.h" 
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/

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
#include "cm_dns.x"         /* common DNS libraru defines */
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.x" 
#include "leg.x"           /* layer management typedefs for EG */
#include "egt.x"           /* typedefs for EGT */
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for EG */
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "egac_acc.x"      /* typedefs for EG acceptance tests */
#include "egac_egt.x"

PRIVATE CmXtaCmd egAcEgtSimpleCmd[] =
{
   /* -- eGTP Bind and Unbind Requests --*/
   {(Txt *)"tapa.egt.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtBndReq, NULLP,
      (Txt *)"EGT Bind Request"
   },
 
   {(Txt *)"tapa.egt.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtBndCfm, NULLP,
      (Txt *)"EGT Bind Confirm"
   },
 
   {(Txt *)"tapa.egt.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtUbndReq, NULLP,
      (Txt *)"EGT Unbind Request"
   },

#ifdef EGTP_C
   /* -- eGTP Signalling Request/Response/Indication  --*/
   {(Txt *)"tapa.egt.sigreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtSigReq, NULLP,
      (Txt *)"EGT Signalling Request"
   },

   {(Txt *)"tapa.egt.sigind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtSigInd, NULLP,
      (Txt *)"EGT Signalling Indication"
   },

   {(Txt *)"tapa.egt.sigrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtSigRsp, NULLP,
      (Txt *)"EGT Signalling Response"
   },

   {(Txt *)"tapa.egt.sigcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtSigCfm, NULLP,
      (Txt *)"EGT Signalling Confirm"
   },

   /* -- eGTP Solicited Status --*/
   {(Txt *)"tapa.egt.stareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtStaReq, NULLP,
      (Txt *)"EGT Status Request"
   },

   {(Txt *)"tapa.egt.stacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtStaCfm, NULLP,
      (Txt *)"EGT Status Confirm"
   },

   {(Txt *)"tapa.egt.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtStaInd, NULLP,
      (Txt *)"EGT Status Indication"
   },
   
   {(Txt *)"tapa.egt.errind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtErrInd, NULLP,
      (Txt *)"EGT Error Indication"
   },

   {(Txt *)"tapa.egt.lcldelreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtLclDelReq, NULLP,
      (Txt *)"EGT LCL Del Request"
   },

   {(Txt *)"tapa.egt.lcldelcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEgtLclDelCfm, NULLP,
      (Txt *)"EGT LCL Del Confirm"
   },
#endif /* EGTP_C */
#ifdef EGTP_U
   {(Txt *)"tapa.egt.egudatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlEgtDatReq, NULLP,
      (Txt *)"EGT-U Data Request"
   },
/* eg001.201 Procedure for reseting Config confirm value */
   {(Txt *)"tapa.egt.ControlParameter", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlEgtControlParameter, NULLP,
      (Txt *)"EGT-U Modify Control Parameter"
   },
   {(Txt *)"tapa.egt.egudatind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlEgtDatInd, NULLP,
      (Txt *)"EGT-U Data Indication"
   },
   {(Txt *)"tapa.egt.egutnlmgmtreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlLclTnlMgmtReq, NULLP,
      (Txt *)"EGT-U Local TnlMgmt Request"
   },
   {(Txt *)"tapa.egt.egutnlmgmtcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlLclTnlMgmtCfm, NULLP,
      (Txt *)"EGT-U Local TnlMgmt Confirm"
   },
   {(Txt *)"tapa.egt.egustareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlEgtStaReq, NULLP,
      (Txt *)"EGT-U Status Request"
   },
   {(Txt *)"tapa.egt.egustacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlEgtStaCfm, NULLP,
      (Txt *)"EGT-U Status Confirm"
   },
   {(Txt *)"tapa.egt.egustaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlEgtUStaInd, NULLP,
      (Txt *)"EGT-U Status Indication"
   },
   {(Txt *)"tapa.egt.eguerrind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, eguAcHdlEgtErrInd, NULLP,
      (Txt *)"EGT-U Error Indication"
   },
#endif
};


/*
*
*       Fun:   egAcEgtInit
*
*       Desc:  Function which initializes the Simple commands 
*              of upper interface of eGTP.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egtreg.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcEgtInit
(
Void
)
#else
PUBLIC S16 egAcEgtInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(egAcEgtInit);
 
   cnt = sizeof(egAcEgtSimpleCmd)/sizeof(egAcEgtSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, egAcEgtSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* egAcEgtInit */
 
/*
*
*       Fun:   egAcEgtDeInit
*
*       Desc:  De-initialization of the Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egtreg.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcEgtDeInit
(
Void
)
#else
PUBLIC S16 egAcEgtDeInit()
#endif
{
 
   TRC2(egAcEgtDeInit);
 
   RETVALUE(ROK);
}/* egAcEgtDeInit --*/


/********************************************************************30**

         End of file:     egac_egtreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:29 2015

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
------------ -------- ---- ----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg001.201   asaurabh    1. Changes for EGTP_U_REL_9    
/main/3     eg004.201   magnihotri  1. Header files added for eGTP-C PSF
*********************************************************************91*/
