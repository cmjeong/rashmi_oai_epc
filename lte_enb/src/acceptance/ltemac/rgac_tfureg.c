


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      rgac_tfureg.c@@/main/3 - Sat Jul 30 02:21:09 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/

/* Common include file for all acceptance files */
#include "rgac_acc.x"

PRIVATE CmXtaCmd rgAcTfuSimpleCmd[] =
{
   {"tapa.tfu.directive", CMXTA_TYPE_DIR, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDirective,
      NULLP, "TFU Directive"},

   {"tapa.tfu.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuBndReq,
      NULLP, "TFU Bind request"},

   {"tapa.tfu.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuBndCfm,
      NULLP, "TFU Bind Confirm"},

   {"tapa.tfu.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuUBndReq,
      NULLP, "TFU UnBind request"},

   {"tapa.tfu.sch.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuSchBndReq,
      NULLP, "TFU Scheduler Bind request"},

   {"tapa.tfu.sch.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuSchBndCfm,
      NULLP, "TFU Scheduler Bind Confirm"},

   {"tapa.tfu.sch.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuSchUBndReq,
      NULLP, "TFU Scheduler UnBind request"},

   {"tapa.tfu.rareq.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuRaReqInd,
      NULLP, "TFU Random Access Request Indication"},

   {"tapa.tfu.rareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuRaReq,
      NULLP, "Individual Random Access Request "},

   {"tapa.tfu.recp.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuRecpReq,
      NULLP, "TFU Reception Request"},

   {"tapa.tfu.hq.recp.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuHqRecpReq,
      NULLP, "TFU HARQ Reception Request"},

   #ifdef TFU_UPGRADE
    {"tapa.tfu.dlcqi.recp.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDlCqiRecpReq,
      NULLP, "TFU DLCQI Reception Request"},
  
    {"tapa.tfu.sr.recp.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuSrRecpReq,
         NULLP, "TFU SR Reception Request"},
  
   {"tapa.tfu.srs.recp.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuSrsRecpReq,
         NULLP, "TFU SRS Reception Request"},
   
   #endif 

   {"tapa.tfu.msg3.recp.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuMsg3RecpReq,
      NULLP, "TFU MSG3 Reception Request"},

   {"tapa.tfu.pusch.recp.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuPuschRecpReq,
      NULLP, "TFU PUSCH Reception Request"},

   {"tapa.tfu.cntrl.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuCntrlReq,
      NULLP, "TFU Control Request"},

   {"tapa.tfu.cfi.cntrl.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuCfiCntrlReq,
      NULLP, "TFU CFI Control Request"},

   {"tapa.tfu.phich.cntrl.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuPhichCntrlReq,
      NULLP, "TFU PHICH Control Request"},

   {"tapa.tfu.pdcch.cntrl.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuPdcchCntrlReq,
      NULLP, "TFU PDCCH Control Request"},

   {"tapa.tfu.dat.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDatReq,
      NULLP, "TFU Data Request"},

   {"tapa.tfu.bch.dat.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuBchDatReq,
      NULLP, "TFU BCH Data Request"},

   {"tapa.tfu.rarsp.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuRaRespReq,
      NULLP, "TFU RA Response Data Request"},

   {"tapa.tfu.pdsch.dat.req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuPdschDatReq,
      NULLP, "TFU PDSCH Data Request"},

   {"tapa.tfu.dat.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDatInd,
      NULLP, "TFU Data Indication"},

   {"tapa.tfu.dat", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDat,
      NULLP, "Individual Data Indication"},

   {"tapa.tfu.hq.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuHqInd,
      NULLP, "TFU HARQ Feedback Indication"},

   {"tapa.tfu.hq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuHq,
      NULLP, "Individual HARQ Feedback Indication"},

   {"tapa.tfu.sr.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuSrInd,
      NULLP, "TFU SR Indication"},

   {"tapa.tfu.sr", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuSr,
      NULLP, "Individual SR Indication"},

   {"tapa.tfu.pucchdelta.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuPucchDeltaInd,
      NULLP, "TFU PUCCH Delta Indication"},

   {"tapa.tfu.pucchdelta", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuPucchDelta,
      NULLP, "Individual PUCCH Delta Indication"},

   {"tapa.tfu.crc.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuCrcInd,
      NULLP, "TFU CRC Indication"},

   {"tapa.tfu.crc", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuCrc,
      NULLP, "Individual CRC Indication"},

   {"tapa.tfu.timingadv.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuTimingAdvInd,
      NULLP, "TFU Timing Advance Indication"},

   {"tapa.tfu.timingadv", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuTimingAdv,
      NULLP, "Individual Timing Advance Indication"},

   {"tapa.tfu.dlcqi.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDlCqiInd,
      NULLP, "TFU Downlink CQI Indication"},

   {"tapa.tfu.dlcqi", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDlCqi,
      NULLP, "Individual Downlink CQI Indication"},

#ifdef TFU_UPGRADE      

   {"tapa.tfu.rawdlcqi.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuRawDlCqiInd,
      NULLP, "TFU Downlink Raw CQI Indication"},

   {"tapa.tfu.rawdlcqi", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuRawDlCqi,
     NULLP, "Individual Raw DL CQI Indication"},

   {"tapa.tfu.srs.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuUlSrsInd,
      NULLP, "TFU SRS Indication"},

   {"tapa.tfu.srs", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuUlSrs,
     NULLP, "Individual SRS Indication"},

  
#endif 

   {"tapa.tfu.ulcqi.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuUlCqiInd,
      NULLP, "TFU Downlink CQI Indication"},

   {"tapa.tfu.ulcqi", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuUlCqi,
      NULLP, "Individual Downlink CQI Indication"},
#ifdef LTEMAC_MIMO
   {"tapa.tfu.doa.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDoaInd,
      NULLP, "TFU DOA Indication"},

   {"tapa.tfu.doa", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuDoa,
      NULLP, "Individual DOA Indication"},
#endif
   {"tapa.tfu.tti.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuTtiInd,
      NULLP, "TFU TTI Indication to MAC"},

   {"tapa.tfu.err.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuErrInd,
      NULLP, "TFU ERR Indication to SCH"},

   {"tapa.tfu.start.tti", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuStartTti,
      NULLP, "TFU Starting TTIs"},

   {"tapa.tfu.ul.resetrb", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlTfuResetUlRb,
      NULLP, "Resetting UL RB alloc info"}
};

/**
 * @brief This function loads all the xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcTfuInit 
(
 Void
)
#else
PUBLIC S16 rgAcTfuInit ()
#endif
{
   U16 count;
   S16 ret;

   TRC2(rgAcTfuInit);

   count = sizeof(rgAcTfuSimpleCmd)/sizeof(rgAcTfuSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd (count, rgAcTfuSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);

} /* end of rgAcTfuInit */

/**
 * @brief This function DeInits TFU xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcTfuDeInit 
(
 Void
 )
#else
PUBLIC S16 rgAcTfuDeInit ()
#endif
{
   TRC2(rgAcTfuDeInit)

   RETVALUE(ROK);
} /* end of rgAcTfuDeInit */
   


/**********************************************************************
 
         End of file:     rgac_tfureg.c@@/main/3 - Sat Jul 30 02:21:09 2011
 
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
           rg007.201   ap  1. Added support for MIMO
           rg009.201   dv 1. Added support for TFU_UPGRADE 
/main/3      ---       nu 1. Updated for release LTE-MAC 3.1.
$SID$        ---       rt  1. LTE MAC 4.1 release
*********************************************************************91*/
