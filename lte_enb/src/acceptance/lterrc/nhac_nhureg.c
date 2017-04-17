/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C file

     Desc:    

     File:  nhac_nhureg.c

     Sid:      nhac_nhureg.c@@/main/3 - Fri Jul  1 01:13:06 2011

     Prg:     rer

*********************************************************************21*/
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
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_acc_nhu.x"
#include "nh.x"

PRIVATE CmXtaCmd nhAcNhuSimpleCmd[] =
{
   /* Bind Procedure */

   {"tapa.nhu.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuBndReq, NULLP,
      "Bind Request"
   },

   {"tapa.nhu.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuBndCfm, NULLP,
      "Bind Confirm"
   },

   {"tapa.nhu.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuUbndReq, NULLP,
      "Unbind Request"
   },

   {"tapa.nhu.cfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuCfgReq, NULLP,
      "Configuration Request"
   },

   {"tapa.nhu.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuCfgCfm, NULLP,
      "Configuration Confirm"
   },

   {"tapa.nhu.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuDatReq, NULLP,
      "RRC Data Request"
   },

   {"tapa.nhu.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuDatInd, NULLP,
      "RRC Data Indication"
   },

   {"tapa.nhu.datrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuDatRsp, NULLP,
      "RRC Data Response"
   },

   {"tapa.nhu.datcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuDatCfm, NULLP,
      "RRC Data Confirm"
   },

   {"tapa.nhu.errind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuErrInd, NULLP,
      "Error Indication "
   },

   {"tapa.nhu.cncluereq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuCnclUeReq, NULLP,
      "Cancel UE Request  Request"
   },

   {"tapa.nhu.cellcfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuCellCfgReq, NULLP,
      "Cell Configuration Request"
   },

   {"tapa.nhu.cellcfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuCellCfgCfm, NULLP,
      "Cell Configuration Confirm"
   },

   {"tapa.nhu.deletetransreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuDeleteTransReq, NULLP,
      "Delete Transaction Request"
   },
   
   {"tapa.nhu.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuStaInd, NULLP,
      "Status Indication"
   },

   {"tapa.nhu.sdustareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuPdcpSduStaReq, NULLP,
      "PDCP SDU Status Request"
   },

   {"tapa.nhu.sdustacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuPdcpSduStaCfm, NULLP,
      "PDCP SDU Status Confirm"
   },

   {"tapa.nhu.countreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuCountReq, NULLP,
      "Count Request"
   },

   {"tapa.nhu.countcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuCountCfm, NULLP,
      "Count Confirm"
   },

   {"tapa.nhu.encodereq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuEncodeReq, NULLP,
      "Encode Request"
   },

   {"tapa.nhu.encodecfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuEncodeCfm, NULLP,
      "Encode Confirm"
   },

   {"tapa.nhu.decodereq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuDecodeReq, NULLP,
      "Decode Request"
   },

   {"tapa.nhu.decodecfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuDecodeCfm, NULLP,
      "Decode Confirm"
   },
   {"tapa.nhu.pdcpdatafwdreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhuPdcpDataFwdReq, NULLP,
      "PDCP Data Forward Request"
   },
   {"tapa.nhu.mcelldatrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlMcellNhuDatRsp, NULLP,
      "RRC Data Response"
   }
};


/*
*
*       Fun:   nhAcNhuInit
*
*       Desc:  Initialization of NHU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_nhureg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcNhuInit
(
Void
)
#else
PUBLIC S16 nhAcNhuInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(nhAcNhuInit)

   cnt = sizeof(nhAcNhuSimpleCmd)/sizeof(nhAcNhuSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nhAcNhuSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* nhAcNhuInit */

/*
*
*       Fun:   nhAcNhuDeInit
*
*       Desc:  De-Initialize NHU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_nhureg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcNhuDeInit
(
Void
)
#else
PUBLIC S16 nhAcNhuDeInit()
#endif
{

   TRC2(nhAcNhuDeInit)

   RETVALUE(ROK);
}/* nhAcNhuDeInit --*/


/**********************************************************************
         End of file:     nhac_nhureg.c@@/main/3 - Fri Jul  1 01:13:06 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer              1. LTE RRC Initial Release.
/main/2      ---     chebli           1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/


