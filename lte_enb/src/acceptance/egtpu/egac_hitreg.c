
/********************************************************************20**

     Name:    eGTP layer

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_hitreg.c

     Sid:      egac_hitreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:33 2015

     Prg:     an

*********************************************************************21*/
/* header include files (.h) */
#include "egac_acc.x"
#include "egac_hit.x"

PRIVATE CmXtaCmd egAcHitSimpleCmd[] =
{
   {(Txt *)"tapa.hit.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitBndReq, NULLP,
        (Txt *)"HIT Bind Request"
   },

   {(Txt *)"tapa.hit.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitUbndReq, NULLP,
        (Txt *)"HIT Unbind Request"
   },

   {(Txt *)"tapa.hit.servopenreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitServOpenReq, NULLP,
        (Txt *)"HIT Server Open Request"
   },

   {(Txt *)"tapa.hit.conreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitConReq, NULLP,
        (Txt *)"HIT Connection Request"
   },

   {(Txt *)"tapa.hit.conrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitConRsp, NULLP,
        (Txt *)"HIT Connection Response"
   },

   {(Txt *)"tapa.hit.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitDatReq, NULLP,
      (Txt *)"HIT Tcp Data Request"
    },

   {(Txt *)"tapa.hit.udatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitUDatReq, NULLP,
        (Txt *)"HIT Udp Data Request"
   },

   {(Txt *)"tapa.hit.discreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitDiscReq, NULLP,
        (Txt *)"HIT Disconnect Request"
   },

   {(Txt *)"tapa.hit.conind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitConInd, NULLP,
        (Txt *)"HIT Connection Indication"
   },

   {(Txt *)"tapa.hit.concfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitConCfm, NULLP,
        (Txt *)"HIT Connection Confirm"
   },

   {(Txt *)"tapa.hit.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitBndCfm, NULLP,
        (Txt *)"HIT Bind Confirm"
   },

   {(Txt *)"tapa.hit.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitDatInd, NULLP,
      (Txt *)"HIT Tcp Data Indication"
   },

   {(Txt *)"tapa.hit.udatind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitUDatInd, NULLP,
      (Txt *)"HIT Udp Data Indication"
   },
#ifdef EGTP_U
   {(Txt *)"tapa.hit.egudatind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egUAcHdlHitUDatInd, NULLP,
      (Txt *)"HIT Udp Data Indication for eGTP-U"
   },
#endif

   {(Txt *)"tapa.hit.discind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitDiscInd, NULLP,
      (Txt *)"HIT Disconnection Indication"
   },

   {(Txt *)"tapa.hit.disccfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitDiscCfm, NULLP,
      (Txt *)"HIT Disconnection Confirm"
   },

   {(Txt *)"tapa.hit.flcind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlHitFlcInd, NULLP,
      (Txt *)"HIT Flow Control Indication"
   },
};

/*
*
*       Fun:   egAcHitInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_hitreg.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHitInit
(
Void
)
#else
PUBLIC S16 egAcHitInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(egAcHitInit)

   cnt = sizeof(egAcHitSimpleCmd)/sizeof(egAcHitSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, egAcHitSimpleCmd)) != ROK)
      RETVALUE(ret);

   /*-- Init spId for the Dummy SCTP --*/

   RETVALUE(ROK);
}/* egAcHitInit */

/*
*
*       Fun:   egAcHitDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_hitreg.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHitDeInit
(
Void
)
#else
PUBLIC S16 egAcHitDeInit()
#endif
{
/*   Pst      pst;*/

/*   S16      ret;*/

   TRC2(egAcHitDeInit)

   RETVALUE(ROK);
}/* egAcHitDeInit --*/

/********************************************************************30**

         End of file:     egac_hitreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:33 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rss         1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
*********************************************************************91*/
