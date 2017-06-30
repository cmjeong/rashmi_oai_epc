
/********************************************************************20**

     Name:    EGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_egtreg.c

     Sid:      egac_edmreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:25 2015

     Prg:     pc

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */

#ifdef EG_UTIL
#include "eg_util.h"       /* Egtpeter Utility library */
#endif /* EG_UTIL */
#include "egt.h"           /* Egtpeter Upper Interface */
#include "eg.h"           /* Egtpeter Upper Interface */
#include "eg_edm.h"           /* Egtpeter Upper Interface */
#include "egac_edm.h"           /* Egtpeter Upper Interface */
#include "leg.h"           /* Egtpeter Layer Manager   */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.h"
#include "cm_dns.x"

#ifdef EG_UTIL
#include "eg_util.x"       /* Eg Utility library */
#endif /* EG_UTIL */
#include "egt.x"           /* Eg Upper Interface */
#include "leg.x"           /* Eg layer manager  */

#include "cm_xta.h"
#include "egac_acc.h"
#include "eg.x"
#include "cm_xta.x"
#include "egac_acc.x"
#include "egac_edm.x"
#include "eg_edm.x"


PRIVATE CmXtaCmd egAcEdmSimpleCmd[] =
{
   {(Txt *)"tapa.edm.egmsgind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmSigInd, NULLP,
      (Txt *)"EDM GTP Message Indication"
   },

   {(Txt *)"tapa.edm.egmsgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmSigReq, NULLP,
      (Txt *)"EDM GTP Message Req"
   },
   
   {(Txt *)"tapa.edm.egmsgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmSigCfm, NULLP,
      (Txt *)"EDM GTP Message Cfm"
   },

   {(Txt *)"tapa.edm.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmMsgInd, NULLP,
      (Txt *)"Handler for the send the  mBuf to the decoder"
   },
   {(Txt *)"tapa.edm.intf.cfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmMsgCfg, NULLP,
      (Txt *)"Handler for configuring both ie and gm msg"
   },
   {(Txt *)"tapa.edm.ctrl.shutdown", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmShutDownReq, NULLP,
      (Txt *)"Handler for shutdowning the edm module"
   },

   {(Txt *)"tapa.edm.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmCfgCfm, NULLP,
      (Txt *)"Handler for configuring both ie and gm msg"
   },

   {(Txt *)"tapa.edm.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmMsgReq, NULLP,
      (Txt *)"Handler for the rcv mBuf from the Encoder"
   },

   {(Txt *)"tapa.edm.egmsgrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmSigRsp, NULLP,
      (Txt *)"EDM GTP Message Rsp"
   },

   {(Txt *)"tapa.edm.errind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlEdmErrInd, NULLP,
      (Txt *)"EDM GTP Error Indication"
   }
};


/*
*
*       Fun:   egAcEdmInit
*
*       Desc:  Initialization of EGT Simple Commands 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_egtreg.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmInit
(
Void
)
#else
PUBLIC S16 egAcEdmInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(egAcEdmInit)

   cnt = sizeof(egAcEdmSimpleCmd)/sizeof(egAcEdmSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, egAcEdmSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* egAcEdmInit */

/*
*
*       Fun:   egAcEdmDeInit
*
*       Desc:  De-initialization of EGT Command List 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egAc_egtreg.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmDeInit 
(
Void
)
#else
PUBLIC S16 egAcEdmDeInit()
#endif
{

   TRC2(egAcEdmDeInit)

   RETVALUE(ROK);
}/* egAcEdmDeInit --*/

/********************************************************************30**

         End of file:     egac_edmreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:25 2015

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
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
*********************************************************************91*/



