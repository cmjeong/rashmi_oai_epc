
/********************************************************************20**

     Name:    eGTP

     Type:    C source file

     Desc:    C code for defining the array of simple commands at the
              Layer manager interface of TUCL.

     File:    egac_lhireg.c

     Sid:      egac_lhireg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:38 2015

     Prg:     an

*********************************************************************21*/

/* header include files (.h) */
#include "egac_acc.x"
#include "egac_lhi.x"

PRIVATE CmXtaCmd egAcHiSimpleCmd[] =
{
   /*-- TUCL Cfg APIs --*/
   {(Txt *)"tapa.lhi.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiGenCfgReq, NULLP,
        (Txt *)"General Configuration Request for TUCL" },

   {(Txt *)"tapa.lhi.cfg.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiTSapCfgReq, NULLP,
      (Txt *)"Tsap Configuration Request for TUCL"
   },

   {(Txt *)"tapa.lhi.cfg.ctxt",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiCtxtCfgReq, NULLP,
      (Txt *)"Context Configuration Request for TUCL" },

   {(Txt *)"tapa.lhi.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiCfgCfm, NULLP,
      (Txt *)"Configuration Confirmation for TUCL" },

   /*-- TUCL Control APIs --*/
   {(Txt *)"tapa.lhi.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiUstaCntrlReq, NULLP,
      (Txt *)"Unsolicited Status Control Request for TUCL"      },

   {(Txt *)"tapa.lhi.cntrl.trc",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiTrcCntrlReq, NULLP,
      (Txt *)"Trace Control Request for TUCL"                    },

   {(Txt *)"tapa.lhi.cntrl.tsap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiTsapCntrlReq, NULLP,
      (Txt *)"TSAP Control Request for TUCL"                    },

   {(Txt *)"tapa.lhi.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiDbgCntrlReq, NULLP,
      (Txt *)"Debug Control Request for TUCL"                    },

   {(Txt *)"tapa.lhi.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiShutDownCntrlReq, NULLP,
      (Txt *)"Shutdown Control Request for TUCL"                 },

   {(Txt *)"tapa.lhi.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiCntrlCfm, NULLP,
      (Txt *)"Control Confirmation for TUCL"                     },

   /*-- TUCL Statistics APIs --*/
   {(Txt *)"tapa.lhi.sts.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiGenStsReq, NULLP,
      (Txt *)"General Statistics for TUCL"                       },

   {(Txt *)"tapa.lhi.sts.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiTsapStsReq, NULLP,
      (Txt *)"TSAP Statistics for TUCL"                          },

   {(Txt *)"tapa.lhi.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiStsCfm, NULLP,
      (Txt *)"Statistics Confirmation for TUCL"                  },

   /*-- TUCL Solicited Status APIs --*/
   {(Txt *)"tapa.lhi.sta.sys",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiSysStaReq, NULLP,
      (Txt *)"System Status Request for TUCL"                    },

   {(Txt *)"tapa.lhi.sta.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiTsapStaReq, NULLP,
      (Txt *)"TSAP Status Request for TUCL"                      },

   {(Txt *)"tapa.lhi.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     egAcHdlHiStaCfm, NULLP,
      (Txt *)"Status Confirmation for TUCL"                      },

   /*-- TUCL Alarm APIs --*/
   {(Txt *)"tapa.lhi.staind",          CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,   egAcHdlHiStaInd, NULLP,
      (Txt *)"Unsolicited Indication for TUCL "                  },

   /*-- TUCL Trace Indication APIs --*/
   {(Txt *)"tapa.lhi.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,    egAcHdlHiTrcInd, NULLP,
      (Txt *)"Trace Indication for TUCL"                        },
};

/*
*
*       Fun:   egAcLhiInit
*
*       Desc:  Initialization and Loading of Simple Commands
*              of TUCL.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhireg.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcLhiInit
(
Void
)
#else
PUBLIC S16 egAcLhiInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(egAcLhiInit)

   cnt = 0;
   ret = 0;

   cnt = sizeof(egAcHiSimpleCmd)/sizeof(egAcHiSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, egAcHiSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* egAcLhiInit */

/*
*
*       Fun:   egAcLhiDeInit
*
*       Desc:  Deinitialization of the Simple Commands of Layer
*              manager interface of TUCL.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_lhireg.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcLhiDeInit
(
Void
)
#else
PUBLIC S16 egAcLhiDeInit()
#endif
{
   TRC2(egAcLhiDeInit)

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* egAcLhiDeInit */


/********************************************************************30**

         End of file:     egac_lhireg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:38 2015

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
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
*********************************************************************91*/
