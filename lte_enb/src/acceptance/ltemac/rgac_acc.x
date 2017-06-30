


/**********************************************************************
 
    Name:   LTE MAC layer
 
    Type:   C include file
 
    Desc:   Defines required by XTA LTE MAC
 
    File:   rgac_acc.x
 
    Sid:      rgac_acc.x@@/main/3 - Sat Jul 30 02:20:50 2011
 
    Prg:    sm 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000372       LTE MAC
*
*/
 
#ifndef __RGAC_ACCX__
#define __RGAC_ACCX__

/* List of common include files */
/* Header files */
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"       /* common tokens */
#include "rgu.h"           /* RGU defines */
#include "tfu.h"           /* RGU defines */
#include "lrg.h"           /* layer management defines for LTE-MAC */
#include "crg.h"           /* layer management defines for LTE-MAC */
#include "rgr.h"           /* layer management defines for LTE-MAC */
#include "cm_xta.h"
#include "rgac_acc.h"


/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"       /* common tokens */
#include "rgu.x"           /* RGU types */
#include "tfu.x"           /* RGU types */
#include "lrg.x"           /* layer management typedefs for MAC */
#include "crg.x"           /* layer management typedefs for MAC */
#include "rgr.x"           /* layer management typedefs for MAC */
#include "cm_xta.x"            /* typedefs for MAC */
/* ccpu00134393 */
#include "rgm.x"           /* layer management typedefs for MAC */


#ifdef __cplusplus
extern "C" {
#endif 

   /* Following section includes the declarations for the handlers and utilitity
    * functions used by the testing framework. 
    */

   EXTERN S16 rgAcHdlTfuDirective ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuBndReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuBndCfm ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuUBndReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
 EXTERN S16 rgAcHdlTfuSchBndReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuSchBndCfm ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuSchUBndReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuRaReqInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuUlCqiInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
#ifdef LTEMAC_MIMO
   EXTERN S16 rgAcHdlTfuDoaInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcUtlTfuBuildDoaIndMsg ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb,
            Pst         *pst,
            SuId        *suId,
            TfuDoaIndInfo *doaIndInfo));
#endif
   EXTERN S16 rgAcHdlTfuHqInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuPucchDeltaInd ARGS ((
            CmXtaTCCb  *tcCb,
            CmXtaSpCb  *spCb));
   EXTERN S16 rgAcHdlTfuSrInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuDlCqiInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuDatInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuCrcInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuTimingAdvInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuDatReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuTtiInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuErrInd ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcHdlTfuStartTti ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuResetUlRb ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   /* Following are the declarations for the lower-level xml commands i.e. the
    * ones embedded within the higher-level command.
    */
   EXTERN S16 rgAcHdlTfuRaReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuPdcchCntrlReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuPhichCntrlReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuCfiCntrlReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuCntrlReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuRecpReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuHqRecpReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
/* Added TFU_UPGRADE Support */
#ifdef TFU_UPGRADE
   EXTERN S16 rgAcHdlTfuDlCqiRecpReq ARGS ((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuSrRecpReq ARGS ((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuSrsRecpReq ARGS ((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuRawDlCqiInd ARGS ((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb));

  EXTERN S16 rgAcHdlTfuRawDlCqi ARGS ((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb));

  EXTERN S16 rgAcUtlTfuBuildRawDlCqi ARGS((
        CmXtaTCCb        *tcCb,
        CmXtaSpCb        *spCb,
        TfuRawCqiIndInfo* rawDlCqiInfo));

  EXTERN S16 rgAcUtlTfuBuildRawDlCqiIndMsg ARGS ((
         CmXtaTCCb         *tcCb,
         CmXtaSpCb         *spCb,
         Pst               *pst,
         SuId              *suId,
         TfuRawCqiIndInfo* rawDlCqiInfo));

  EXTERN S16 rgAcHdlTfuUlSrsInd ARGS ((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb));

  EXTERN S16 rgAcHdlTfuUlSrs ARGS ((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb));

 EXTERN S16 rgAcUtlTfuBuildSrs ARGS((
        CmXtaTCCb        *tcCb,
        CmXtaSpCb        *spCb,
        TfuSrsIndInfo* srsInfo));

EXTERN S16 rgAcUtlTfuBuildSrsIndMsg ARGS ((
         CmXtaTCCb         *tcCb,
         CmXtaSpCb         *spCb,
         Pst               *pst,
         SuId              *suId,
         TfuSrsIndInfo* srsInfo));
        

#endif 

   EXTERN S16 rgAcHdlTfuMsg3RecpReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuPuschRecpReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuBchDatReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuPdschDatReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuRaRespReq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuUlCqi ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
#ifdef LTEMAC_MIMO
   EXTERN S16 rgAcHdlTfuDoa ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));
   EXTERN S16 rgAcUtlTfuBuildDoa ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb,
            TfuDoaIndInfo *doaIndInfo));
#endif
   EXTERN S16 rgAcHdlTfuDlCqi ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuHq ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuPucchDelta ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuSr ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuCrc ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuTimingAdv ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   EXTERN S16 rgAcHdlTfuDat ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb));

   /* The following section contains the declarations for the utility functions
    * used by the handler functions.
    */
   EXTERN S16 rgAcUtlTfuBuildRaReqIndMsg ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            Pst               *pst,
            SuId              *suId,
            TfuRaReqIndInfo   *raReqInd));
   EXTERN S16 rgAcUtlTfuGetToSchPst ARGS((
         CmXtaTCCb   *tcCb,
         CmXtaSpCb   *spCb,
         Pst         *pst));

   EXTERN S16 rgAcUtlTfuBuildRaReq ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            TfuRaReqIndInfo   *raReqInd));

   EXTERN S16 rgAcUtlTfuValidateMsg ARGS ((
            CmXtaTCCb   *tcCb,
            CmXtaSpCb   *spCb,
            U8          event));

PUBLIC S16  rgAcUtlTfuValidatePdcch ARGS((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuCntrlReqInfo     *cntrlReq));

EXTERN S16  rgAcUtlTfuValidatePhich ARGS((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuCntrlReqInfo     *cntrlReq
 ));

EXTERN S16  rgAcUtlTfuValidateMsg3RecpReq ARGS((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuRecpReqInfo      *recpReq));

EXTERN S16  rgAcUtlTfuValidateBch ARGS ((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuDatReqInfo       *datReq));

EXTERN S16  rgAcUtlTfuValidatePdsch ARGS ((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuDatReqInfo       *datReq));

EXTERN S16  rgAcUtlTfuValidateRaRsp ARGS ((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuDatReqInfo       *datReq));

EXTERN S16 rgAcUtlTfuBuildUlCqi ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 TfuUlCqiIndInfo     *ulCqiIndInfo));

EXTERN S16 rgAcUtlTfuBuildDlCqi ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 TfuDlCqiIndInfo     *dlCqiIndInfo));

EXTERN S16 rgAcUtlTfuBuildPucchDeltaIndMsg ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 Pst              *pst,
 SuId             *suId,
 TfuPucchDeltaPwrIndInfo     *pucchDeltaPwrIndInfo));

EXTERN S16 rgAcUtlTfuBuildPucchDelta ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 TfuPucchDeltaPwrIndInfo *pucchDeltaIndInfo));

EXTERN S16 rgAcUtlTfuBuildHqIndMsg ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 Pst              *pst,
 SuId             *suId,
 TfuHqIndInfo     *hqIndInfo));

EXTERN S16 rgAcUtlTfuBuildHq ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 TfuHqIndInfo     *hqIndInfo));

EXTERN S16 rgAcUtlTfuBuildSr ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 TfuSrIndInfo     *srIndInfo));

EXTERN S16 rgAcUtlTfuBuildCrc ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 TfuCrcIndInfo     *crcIndInfo));

EXTERN S16 rgAcUtlTfuBuildTimingAdv ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 TfuTimingAdvIndInfo     *timingAdvIndInfo));

EXTERN S16 rgAcUtlTfuBuildDat ARGS((
 CmXtaTCCb        *tcCb,
 CmXtaSpCb        *spCb,
 TfuDatIndInfo    *datInd));

EXTERN S16  rgAcUtlTfuValidatePuschRecpReq ARGS((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuRecpReqInfo      *recpReq));

EXTERN S16  rgAcUtlTfuValidateHqRecpReq ARGS((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuRecpReqInfo      *recpReq));

/* Added TFU_UPGRADE Support */
 #ifdef TFU_UPGRADE
 EXTERN S16  rgAcUtlTfuValidateDlCqiRecpReq ARGS((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuRecpReqInfo      *recpReq));

 EXTERN S16  rgAcUtlTfuValidateSrRecpReq ARGS((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuRecpReqInfo      *recpReq));

 EXTERN S16  rgAcUtlTfuValidateSrsRecpReq ARGS((
 CmXtaTCCb           *tcCb,
 CmXtaSpCb           *spCb,
 TfuRecpReqInfo      *recpReq));
 #endif 

   EXTERN S16 rgAcUtlTfuBuildUlCqiIndMsg ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            Pst               *pst,
            SuId              *suId,
            TfuUlCqiIndInfo   *ulCqiInd));

   EXTERN S16 rgAcUtlTfuBuildSrIndMsg ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            Pst               *pst,
            SuId              *suId,
            TfuSrIndInfo      *srInd));

   EXTERN S16 rgAcUtlTfuBuildDlCqiIndMsg ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            Pst               *pst,
            SuId              *suId,
            TfuDlCqiIndInfo   *dlCqiInd));

   EXTERN S16 rgAcUtlTfuBuildDatIndMsg ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            Pst               *pst,
            SuId              *suId,
            TfuDatIndInfo     *datInd));

   EXTERN S16 rgAcUtlTfuBuildCrcIndMsg ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            Pst               *pst,
            SuId              *suId,
            TfuCrcIndInfo *crcIndInfo));

   EXTERN S16 rgAcUtlTfuBuildTimingAdvIndMsg ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            Pst               *pst,
            SuId              *suId,
            TfuTimingAdvIndInfo *timingAdvInd));

   EXTERN S16 rgAcUtlTfuBuildTtiIndMsg ARGS ((
            CmXtaTCCb         *tcCb,
            CmXtaSpCb         *spCb,
            Pst               *pst,
            SuId              *suId,
            TfuTtiIndInfo     *ttiInd));
   EXTERN S16 rgAcUtlTfuBuildMultiInstTtiIndMsg ARGS ((
            CmXtaTCCb           *tcCb,
            CmXtaSpCb           *spCb,
            Pst                 *pst,
            SuId                *suId,
            TfuTtiIndInfo       *ttiInd,
            U8                  instIdx));

/* Adding preamble format to length mapping table */
typedef U8 RgAccSchRaPrmFmtToRaPrmLenTbl[RG_ACC_MAX_PREAMBLE_FORMATS];
EXTERN RgAccSchRaPrmFmtToRaPrmLenTbl rgAccSchRaPrmFmtToRaPrmLenTbl;


/**
 * @struct rgAcTfuInfo
 * Holds interface primitives received from MAC to Dummy-PHY.
 */
typedef struct rgAcTfuInfo 
{
   SpId                       spId; /*!< Will store the spId for the request */
   SuId                       suId; /*!< Will store the suId for the request */
   U8                         event; /*!< Will store the event for this primitive */
   Reason                     reason;   /*!< Will store reason */
   CmLteTimingInfo            timingInfo;   /*!< Will store the timing info
                                                received with the primitive. */
   U8      type;   /*!< Stores the type of the primitive */
   union 
   {
      /* Phase 2 begins */
      /* The following pointers are used to store the event structure sent by
       * MAC/scheduler. Freeing up happens at flush message. 
       */
      TfuRecpReqInfo         *recpReqInfo;
      TfuCntrlReqInfo        *cntrlReqInfo;
      TfuDatReqInfo          *datReqInfo;
      /* following are the lower-level structures not pointers hence survive
       * after flushing 
       */
      TfuPdcchInfo            pdcchInfo;
      TfuUeRecpReqInfo        ueRecpReqInfo;
      TfuDatReqPduInfo        pduInfo;
   }u;
   Buffer                  mBuf;   /*!< Stores the buffer received */
} RgAcTfuInfo;

/**
 * @struct rgAcRguInfo
 * Holds interface primitives received from MAC to Dummy-RLC.
 */
typedef struct rgAcRguInfo
{
   SuId              suId;   /*!< Stores the SuId */
   SpId              spId;   /*!< Stores the SpId */
   Reason            status;   /*!< Stores the Status */
   Event             event;  /*!< Event */
   union 
   {
      RguCDatIndInfo     *rguCDatInd;
      RguDDatIndInfo     *rguDDatInd;
      RguCStaIndInfo     *rguCStaInd;
      RguDStaIndInfo     *rguDStaInd;
#ifdef LTE_L2_MEAS
      RguHarqStatusInd   *rguHqStaInd;
#endif /* LTE_L2_MEAS */
   }u;
}RgAcRguInfo;
/**
 * @struct rgAcCrgInfo
 * Holds interface primitives received from MAC to Dummy-RRC.
 */
typedef struct rgAcCrgInfo
{
   SuId              suId;
   U8                status;
}RgAcCrgInfo;
/**
 * @struct rgAcRgrInfo
 * Holds interface primitives received from MAC to RGR.
 */
typedef struct rgAcRgrInfo
{
   SuId              suId;
   U8                status;
   /* Added for sending TTI tick to RRM */
   RgrTtiIndInfo     ttiInd;
#ifdef RGR_CQI_REPT
   RgrStaIndInfo     staInd;
#endif
   RgrUeStaIndInfo ueStaInd;
   /* LTE_ADV_FLAG_REMOVED_START */
   RgrLoadInfIndInfo loadInfInd;
   /* LTE_ADV_FLAG_REMOVED_END */
}RgAcRgrInfo;

/**
 * @struct rgAcRgmInfo
 * Holds interface primitives received from MAC to RGR.
 */
typedef struct rgAcRgmInfo
{
   SuId              suId;
   U8                status;
   /* ccpu00134393 */
   Event             event;  /*!< Event */
   union
   {   
       RgmPrbRprtInd     *prbRprtInd; /*!< PRB Report Ind from MAC */
   }u;
}RgAcRgmInfo;




/**
 * @struct rgAccMsgQElm 
 * LTE MAC's Test Engine queue element structure.
 */
typedef struct rgAccMsgQElm {
   union
   {
      RgAcTfuInfo tfuInfo;    /* Dummy TFU information goes here */
      RgAcRguInfo rguInfo;    /* Dummy RGU information goes here */
      RgMngmt     rgMngmt;    /* Dummy LRG information goes here */
      RgAcCrgInfo crgInfo;    /* Dummy CRG information goes here */
      RgAcRgrInfo rgrInfo;    /* RGR information goes here */
      RgAcRgmInfo rgmInfo;    /* RGR information goes here */
#ifdef LTE_L2_MEAS
      LrgSchMeasCfmInfo l2MeasInfo; /* L2 Measurement Information goes here */
#endif
   } u;
   PMSGFREEFS16   msgFreeFun;    /* Function to free this message */
} RgAccMsgQElm;

/**
 * @struct rgAcRguCStaInfo 
 * Structure to cache necessary information from Common Channel
 * staRsp/staInd/datReq primitives.
 */
typedef struct rgAcRguCStaInfo{
   U32          transId;
   U32          totBufSize;
   U8           state;
   CmLteCellId  cellId;
   CmLteLcId    lcId;
   CmLteLcType  lcType;
   CmLteRnti    rnti;
   S32          bo;
   union
   {
      CmLteTimingInfo timeToTx;
      CmLteRnti       rnti;
   }u;
} RgAcRguCStaInfo;

/**
 * @struct rgAcRguDStaLchInfo 
 * Structure to cache necessary information for each dedicated Channel
 * staRsp/staInd/datReq primitives.
 */
typedef struct rgAcRguDStaLchInfo{
   U32          totBufSize;
   CmLteLcId    lcId;
   RguDBoReport boReport;
   U32          dataId;
} RgAcRguDStaLchInfo;

/**
 * @struct rgAcRguDStaInfo 
 * Structure to cache necessary information from Dedicated Channel
 * staRsp/staInd/datReq primitives.
 */
typedef struct rgAcRguDStaInfo{
   U32                transId;
   CmLteCellId        cellId;
   CmLteRnti          rnti;
   U8                 numLch;
   RgAcRguDStaLchInfo lchInfo[RGAC_RGU_MAXARR];
} RgAcRguDStaInfo;

/**
 * @struct rgAcRguCb  
 * Structure to cache necessary information from Common/Dedicated Channel
 * staRsp/staInd/datReq primitives.
 */
typedef struct rgAcRguCb{
   U32 nmbCSta;
   RgAcRguCStaInfo rguCStaInfo[RGAC_RGU_MAXARR];
   U32 nmbDSta;
   RgAcRguDStaInfo rguDStaInfo[RGAC_RGU_MAXARR];
} RgAcRguCb;

#ifdef LTE_ADV
typedef struct rgAcLrgCb{
   Bool forceCntrlSrbBoOnPCel;
} RgAcLrgCb;
#endif


/** @brief  RACH Info stored in RgAcc Control Block */
typedef struct rgAcRachCfgCb
{
   U8  preambleDur;           /*!< Preamble Duration in TTIs */
   U8  raWinSize;             /*!< ra_window_size */
   struct
   {
      U8       size;
      RgrRaSfn sfnEnum;      /*!< System Frame Number */
      U8       subFrameNum[RGR_MAX_SUBFRAME_NUM];
   } raOccasion;
   U8  maxMsg3Tx;            /*!< Maximum number of message 3 transmissions */
   U8  numRaPreamble;        /*!< Number of RA Preambles */
   U8  sizeRaPreambleGrpA;   /*!< Size of RA preamble in Group A */
   U16 msgSizeGrpA;          /*!< MESSAGE_SIZE_GROUP_A */ 
   U8  prachResource;        /*!< N^RA_PRB: PRACH resource for random access */
} RgAcRachCfgCb;


/** @brief  Downlink CQI reporting related configuration per UE */
typedef struct rgAcUeDlCqiCb
{
   RgrUeAprdDlCqiCfg aprdCqiCfg;  /* Aperiodic cqi related information */
   RgrUePrdDlCqiCfg  prdCqiCfg;   /* Periodic cqi related configuration */
} RgAcUeDlCqiCb;

/** @brief Information neede ofr validating DatReq/DatInd */
typedef struct rgAcUeDatCb
{
   CmLteTimingInfo    timingInfo;
   TfuDciInfo       dciInfo;
   U32              tBSize;   /* Length of mBuf of TfuDatReqInfo */
   U8               taAdvance;
} RgAcUeDatCb;

/** @brief Data stored per logical channel */
typedef struct rgAcDlLcCb
{
   U8               lcId;
   U32              bo;
   Bool             done; 
/* Amit */
   S32              schdBo;
   U32 gbr;         /*!< GBR value for a logical channel (bytes/sec). */
   U32 mbr;         /*!< MBR value for a logical channel (bytes/sec). */
} RgAcDlLcCb;

#ifdef LTEMAC_HDFDD
/** @brief Subframe information histofry for a UE */
typedef struct rgAcHdFddUeSfInfo
{
   /* For DL subframe dir info */
   U8                 sfDir[RGAC_HDFDD_SF_HIST];
}RgAcHdFddUeSfInfo;
#endif

#if (defined (TFU_UPGRADE)) || (defined (RGR_CQI_REPT))
typedef struct rgAcDlPwrCntrlInfo
{
#ifdef TFU_UPGRADE 
   RgrUeDlPwrCntrlPaCfg pA;
#endif
#ifdef RGR_CQI_REPT
   RgrUeCqiRept         cqiRept[RGAC_DLPWR_CQIMAXN];
   U8                   cqiReptCount;
   U8                   cqiSentCount;
#endif
}RgAcDlPwrCntrlInfo;
#endif

/** @brief  Data Stored per UE configured */
typedef struct rgAcUeCb
{
   CmLteRnti         crnti;       /*!< CRNTI */
   U32               lastUlGrant;
   U8                rbStart[RG_ACC_MAX_SUBFRAMES]; /*!< This would be utilized 
                                                      to validate the PHICHs. */
   U8                nDmrs[RG_ACC_MAX_SUBFRAMES];   /*!< This would be utilized
                                                      to validate the PHICHs */
   RgAcUeDatCb       datCbList[RG_ACC_MAX_DAT_REQS];   /*!< List to store data
                                                      requests/per CB */
   RgAcUeDlCqiCb     cqiCb;   /*!< To store the CQI information */ 
   U32               ulGrantRcvd;
   RgAcDlLcCb        lcs[RGU_MAX_LC+1]; /*!< LCs from 0 to 10 are possible */
   CmLListCp         staIndLst; /*!< Each staInd is stored here */
   U8                gapPrd;             /*!< Gap period 40ms/80ms */
   U8                gapOffst;           /*!< Gap offset - Vaue is 0 to 1*/
#ifdef TFU_UPGRADE
   RgrUePuschDedCfg  puschDedCfg;  /*!< PUSCH-ConfigDedicated. Ref 36.331 */
#endif
   /* Added support for SPS*/
/* combine compilation fixes */
#ifdef LTEMAC_SPS
    CmLteRnti         SPScrnti; /*!< SPS RNTI */
   U16                dlSpsPrd; /*!< DL SPS Prd */
   U8                 NumSPSProc; /*!< Number of SPS HARQ procs */
   U32                ulPacketSize; 
   U32                numPucchVal;
   #endif /*LTEMAC_SPS*/
#ifdef LTEMAC_HDFDD
   Bool               isHdFddEnbld;
#endif
#if (defined (TFU_UPGRADE)) || (defined (RGR_CQI_REPT))
   RgAcDlPwrCntrlInfo dlpcInfo;
#endif
   CmLteUeCategory    ueCatEnum;
#ifdef LTE_ADV
   RgrUeSCellAckPucchCfg   sCellAckN1ResCfg; /*!< N1ResCfg for SCell ack feedback */
   RgrAccessStratumRls    accessStratumRls; /*!< UE Access Stratum Release */
   CmLteCellId            cellId;
#endif
} RgAcUeCb;

/** @brief  logical channel  configuration */
typedef struct rgAclogchCb
{
   U32   totBufSize; /*!< Total buffer size in bytes scheduled by MAC*/
   U32   transId;  /*!< Transaction ID */
   U32   timetoTx;
   U32   dataId;
} RgAcLogchCb;

typedef struct rgAcPhyRaCb
{
   CmLteRnti         raRnti;                                  /*!< RA RNTI */
   U8                numRaReqInfo;                            /*!< number of RAP
                                                                Ids present */
   TfuRaReqInfo      raReqInfoArr[TFU_MAX_RAPID_IN_SUBFRAME]; /*!< RA requests */
} RgAcPhyRaCb;

typedef struct rgAcPhyCb
{
   CmLteRnti    raRnti;   /*!< Stores the RA-RNTI */
   CmLteTimingInfo  crntTime;   /*!< crnt timing information, frame and subframe
                                numbers */
   CmLteTimingInfo  timingInfoPhySends;
   CmLteTimingInfo  timingInfoPhyMsg3Recp;
} RgAcPhyCb;
 /** @struct RgAcDirectives
  * This contains the directives that can be set per test. 
  */
typedef struct rgAcDirectives
{
   Bool     ulDeltaPrsnt;   /*!< True if UL delta is to be accounted for */
   Bool     noTimeValidation;   /*!< True if UL delta is to be accounted for */
   Bool     validateCfi;
   Bool     autoTti;

   U8        tptType; /*-- CMXTA_ENHANCEMENT: to remove --*/
   U32       baseIp; /*-- CMXTA_ENHANCEMENT: to remove --*/
   Bool      samePort;
   Bool      sameIp;
   U16       basePort;
} RgAcDirectives;

/* Amit */
typedef struct rgAcBoUpdtUeLst
{
   U8                ueId;                                  /*!< RA RNTI */
   S32               remData;
   U32               sduArrvlTime;
}RgAcUeLst;

typedef struct rgAcBoUpdtCb
{
   CmLteCellId       cellId;
   CmLteLcId         lcId;
   S32               boData;
   U8                ttiInterval;
   U8                numOfUe;
   RgAcUeLst         ueLst[RG_ACC_MAX_UE];
   CmLList           boLstEnt;
}RgAcBoUpdtCb;

typedef struct rgAcPfsCqiVal
{
   U8    numOfCqiVal;
   U8    cqiBits[10];
   U8    currCqiIndx;
}RgAcPfsCqiVal;

typedef struct RgAcCqiUeLst
{
   U8                ueId;                                  /*!< RA RNTI */
}RgAcCqiUeLst;

typedef struct rgAcCqiCb
{
   CmLteCellId       cellId;
   U16               sCellIdx;
   U8                numOfPattern;
   RgAcPfsCqiVal     cqiVal[10];
   U32               cqiPatternPer[10];
   U8                numOfUe;
   RgAcCqiUeLst      ueLst[RG_ACC_MAX_UE];
   CmLList           cqiEnt;
}RgAcCqiCb;
/**
 * @struct rgAccCb  
 * Structure to cache necessary information from various primitives
 * of RGU/TFU/CRG interfaces.
 * Global Struct To store information needed for LTE MAC testing
 * This structure goes into the CmXtaTCCb->tcCb Void pointer and is per test
 * case only. 
 */
typedef struct rgAcCb {
   U8                nmbOfUes;
   U16               dedCrnti; /* DED PREAMBLE COUNTER*/
   RgAcDirectives    directives;
   RgAcRguCb         rgAcRguCb;   
   RgAcRachCfgCb     acRachCfg;   /*!< Stores the RACH configuration */
   U8                dlTotalBw;
   U8                ulTotalBw; 
   CmLteTimingInfo   timeList[RG_ACC_MAX_SUBFRAMES];   /*!< This stores the
   timing information of received messages */
   CmLListCp         boUpdtLst[5][320]; /* List of RgAcBoUpdtCb configuration for 5 cells*/
   CmLListCp         rgacCqiLst[5][320]; /* List of RgAcCqiCb configuration for 5 cells*/
   RgAcUeCb          acUeCb[RG_ACC_MAX_UE];
   RgAcLogchCb       acLogchCb[RG_ACC_MAX_UE];
   RgAcPhyCb         acPhyCb[RG_ACC_MAX_SUBFRAMES];   /*!< Stores information
                                                        for some subframes */
   U8                nmbOfRaCb;   /*!< Number of RaCbs */
   RgAcPhyRaCb       acRaCb[RG_ACC_MAX_RARNTI];    /*!< Stores RA request
                                                     information */
   RgAcTfuInfo       savedMsgs[RG_ACC_MAX_SAVES];   /*!< This is the list of
                                                         saved messages to be used later on */
   U8                ngEnum; /* For calculating NDRMS in RGR Cell Config */
   Buffer            *bcchBuf[RG_ACC_MAX_BCCH];
   Buffer            *dedBuf[RG_ACC_MAX_UE];
   U32               transId[RG_ACC_MAX_UE];      /*!< Transaction ID */
   U8                numRbgs;       /*!< Total number of RBGs */    
   U8                rbgSize;       /*!< RBG size for a configured DL bandwidth
                                      */
   U8                lastRbgSize;   /*!< Size of last RBG */
   U8                dlSchedType;   /*!< Downlink Scheduler Type -s <1,..4> */
   U8                ulSchedType;   /*!< Uplink Scheduler Type -s <1,..4> */
   /*  Added for sending TTI tick to RRM */
   CmLteTimingInfo   rgrCrntTime;
   U8                rrmTtiIndPrd;    /*!< RRM TTI indication periodicity */
/* Added TFU_UPGRADE Support */
#ifdef TFU_UPGRADE
   U8  n1PucchAn;                   /*!< N^(1)_PUCCH */
   U8  n2PucchCqi;           /*!< N^(2)_PUCCH*/
   U8  n2RB;                 /*!< N RB CQI */  
   U8  cp;                   /*!< cyclic prefix */
   U8  nCsAn;                /*!< parameter n1Cs */
   U8  deltaPucchShift;      /*!< parameter delta pucch shift */   
#endif

#ifdef LTEMAC_HDFDD
   RgAcHdFddUeSfInfo   ueSfInfo[RG_ACC_MAX_UE];
#endif
#ifdef RGU_INF_OPTIMIZATION
   RguDDatReqInfo  *datReq;
   U8              nmbOfUeDatReqToBeSent;
#endif
#ifdef LTE_TDD
   U8  ulDlCfgIdx;           /*!< TDD UL/DL Configuration Index */
#endif   
   U8  ulRbMap[110];         /*!< Used for validating PUCCH/PUSCH RB 
                                  overlap while validating the Recp Req */ 
#ifdef LTE_ADV
RgAcLrgCb lrgCb;
U8                  numTxAntPorts;  /*!< Number of Transmission antenna ports
                                            Currently this is unused parameter */
#endif
} RgAcCb;

EXTERN RgAcCb     rgAccCb;

/** @struct RgAcTfuCb
 * This structure holds the current subframe and system frame number and also
 * the timers needed by dummy PHY. 
 * This is a global structure accessible to all. 
 */
typedef struct rgAcTfCb 
{
   CmLteTimingInfo   crntTime;
   CmTqCp            tqCp;                            /*!< timer queue control point */ 
   CmTqType          tq[RG_ACC_TFU_TQ_SIZE];          /*!< timer queue */
   CmTimer           timers[RG_ACC_TFU_MAX_TIMERS];   /*!< Timers */
} RgAcTfCb;

EXTERN RgAcTfCb   rgAcTfCb;
/* following are structures needed exclusively by the encoder/decoder that is
 * used by the test framework.
 */

 /** @struct RgAcPwrHdr 
  * This structure contains the Power headroom Control
  * element's information.
  */
typedef struct rgAcPwrHdr
{
   U8          pwrHdr;   /*!< This is the Power headroom reported by the UE. */
} RgAcPwrHdr;

 /** @struct RgAcTimingAdv 
  * This contains Timing Advance control element's
  * information. 
  */
typedef struct rgAcTimingAdv
{
   U8          timingAdv;   /*!< The timing advance to be sent to the UE */
} RgAcTimingAdv;

#ifdef LTE_ADV
typedef struct rgAcSCellAct
{
   U8          sCellAct;   /*!< The SCEll activation CE to UE */
}RgAcSCellAct;
#endif


 /** @struct RgContRes 
  * This structure contains the Contention resolution control
  * element's information.
  */
typedef struct rgAcContRes
{
   U8          contRes[6]; /*!< 48 bit contention resolution Identity  */
} RgAcContRes;

 /** @struct RgAcCrnti 
  * This structure contains the C-RNTI control element's
  * information.
  */
typedef struct rgAcCrnti
{
   U16         crnti;   /*!< The CRNTI sent by the UE */
} RgAcCrnti;

 /** @struct RgAcLongBSR 
  * This structure contains the Long BSR reported by the
  * UE. 
  */
typedef struct rgAcLongBSR
{
   U8          bufferSize1;   /*!< Buffer Size # 1 */
   U8          bufferSize2;   /*!< Buffer Size # 2 */
   U8          bufferSize3;   /*!< Buffer Size # 3 */
   U8          bufferSize4;   /*!< Buffer Size # 4 */

} RgAcLongBSR;

 /** @struct RgAcShortBSR 
  * This structure contains the Short/truncated BSR
  * reported by the UE. 
  */
typedef struct rgAcShortBSR
{
   U8          lcgId;         /*!< The logical channel group ID */
   U8          bufferSize;    /*!< The buffer size reported */
} RgAcShortBSR;

 /** @struct RgAcExtPhr 
  * This structure contains the Extended PHR Info
  * reported by the UE. 
  */
typedef struct RgAcPhrInfo
{
   U8 phr;
   U8 pBackOff;
   U8 pCMax;
}RgAcPhrInfo;

typedef struct rgAcExtPhr
{
   U8 numServCells;
   RgAcPhrInfo phrInfo[8];
} RgAcExtPhr;


 /** @struct RgAcCE 
  * This structure contains the MAC control elements.
  */
typedef struct rgAcCE
{
   U8       type;       /*!< Type of the control element */
   union
   {
      RgAcShortBSR     rgAcShortBSR;      /*!< The Short BSR CE */
      RgAcLongBSR      rgAcLongBSR;       /*!<  The Long BSR CE */
      RgAcCrnti        rgAcCrnti;         /*!< The CRNTI CE */
      RgAcContRes      rgAcContRes;       /*!< The Contention resolution identity CE */
      RgAcTimingAdv    rgAcTimingAdv;     /*!< The Timing advance CE */
      RgAcPwrHdr       rgAcPwrHdr;        /*!< The powerhead room CE */
#ifdef LTE_ADV
      RgAcSCellAct     rgSCellAct;        /*!< SCell activation CE */
      RgAcExtPhr       rgAcExtPhr;          /*!< Ext phr ce info */
#endif
   } u;
} RgAcCE;

 /** @struct RgAcCEorSDU 
  * This structure contains information for a MAC control
  * element of a MAC SDU.
  */
typedef struct rgAcCEorSDU
{
   CmLList    lnk;
   Bool       isCE; /*!< Is true if it is a control element */
   union 
   {
      RgAcCE  rgAcCE;   /*!< A MAC control element. */
      U16     pduSize;     /*!< A MAC PDU */
   } u;
} RgAcCEorSDU;

/** @struct RgAcRaSubHdr 
 * This structure contains the RA Subheaders.
 */
typedef struct rgAcRaSubHdr
{
   CmLList        lnk;
   Bool           isBi; /*!< Set if the header contains a Back off indicator */
   union
   {
      U8             rapId; /*!< Random access preamble ID */
      U8             bi;    /*!< Back off indicator */
   } u;
} RgAcRaSubHdr;

 /** @struct RgAcLongSubHdr 
  * This structure contains the information present in
  * the Sub header with a 15 bit lenght field.
  */
typedef struct rgAcLongSubHdr
{
   U16         length;   /*!< Lenght field of the corresponding PDU */
} RgAcLongSubHdr;

 /** @struct RgAcShortSubHdr 
  * This structure contains the information present in
  * the sub header with a 7 bit lenght field. 
  */
typedef struct rgAcShortSubHdr
{
   U8          length;   /*!< Lenght field of the corresponding PDU */
} RgAcShortSubHdr;

 /** @struct RgAcLastSubHdr 
  * This structure contains the information present in
  * the last sub header/ the sub header for a fixed lenght CE. 
  */
typedef struct rgAcLastSubHdr
{
   Bool        isLast;  /*!< This is set for the last header only */
} RgAcLastSubHdr;

 /** @struct RgAcSubHeader 
  * This header is a union of all the sub headers. 
  */
typedef struct rgAcSubHeader
{
   CmLList     lnk;
   U8          lcId;                   /*!< Logical channel Id */
   U8          type;                   /*!< Type of the sub Header */
   union 
   {
      RgAcLastSubHdr      lastSubHdr;    /*!< This it one that is meant for the Last
                                          subheader or the fixed size CE. */
      RgAcShortSubHdr     shortSubHdr;   /*!< This is the 7 bit Length field */
      RgAcLongSubHdr      longSubHdr;    /*!< This is the 15 bit Length field */
      RgAcRaSubHdr        raSubHdr;      /*!< This is the SubHeader for RA RAPId */
   } u;

} RgAcSubHeader;

 /** @struct RgAcRarPdu 
  * This contains the RAR PDU structure. 
  */
typedef struct rgAcRarHdrs
{
   CmLList        lnk;
   U16            timingAdv;     /*!< Timing Advance for the UE. */
   U32            ulGrant;       /*!< Uplink grant for the UE. */
   U16            tempCrnti;     /*!< The temporary CRNTI allocated to the UE */
} RgAcRarHdrs;

/** @brief This structure corresponds to the decoded RAR PDU received from MAC.
 * It has a list of RA sub Headers and a list of RAR PDUs.
 */
typedef struct rgAcRarPdu
{
   CmLListCp         raSubHdrs; /*!< Linked list of RA Subheaders */
   CmLListCp         rarPdus;   /*!< Linked list of PDUs */
} RgAcRarPdu;


 /** @struct RgAcDatPdu 
  * This structure contains the information needed for a
  * Data PDU construction.
  */
typedef struct rgAcDatPdu
{
   CmLListCp         subHdrs;   /*!< Linked list of Subheaders */
   CmLListCp         ceOrSdus;  /*!< Linked list of CE/SDUs */
} RgAcDatPdu;

/** @brief This is the structure that is used by the Test engine to encode from
 * and decode into the MAC PDU.
 * It uses a CmMemListCp hence takes care of all the allocations and the final
 * deallocation, and hence requires a call to the cmAllocEvnt function for
 * allocation. 
 */
typedef struct rgAcEdEvent
{
   CmMemListCp    memCp;   /*!<  Memory control point to manage memory */
   U8             type;    /*!<  Either a RAR PDU or any other */
   union 
   {
      RgAcRarPdu  rarPdu;  /*!< RAR PDU information */
      RgAcDatPdu  datPdu;  /*!< Data PDU information */
   } u;
} RgAcEdEvent;

/* Added TFU_UPGRADE Support */
#ifdef TFU_UPGRADE
/** @brief This structure will be used to maintain the linked
  * list for handling of Reception request.
  *  */
typedef struct rgAcTfuUeRecpReqNode
{
   CmLList    lnk;          /*!< Link to next node */
   U16    recpTypeBitMsk;   /*!< Bit Mask to indicate Recp type */
   TfuUeRecpReqInfo  *node; /*!< Pointer to node in ueRecpReqLst */
} RgAcTfuUeRecpReqNode;

/** @brief This structure will be used in the handling of the 
  *  Reception request primitive.
  *  */
typedef struct rgAcTfuRecpReqInfo
{
   TfuRecpReqInfo   *recpReq;        /*!< Reception request structure*/
   CmLListCp         ueRecpReqNdLst; /*!< Linked List of nodes of type RgAcTfuUeRecpReqNode */
} RgAcTfuUeRecpReqInfo;
#endif /*TFU_UPGRADE*/

typedef struct lchData
{
   CmLteLcId     lcId; 
   U8            qci;
   U8            dir;
   CmLteLcType   lcType;
   U32           gbr;
   U32           mbr;
}LchData; 

/* Global control block declarations go here */
EXTERN RgAcTfCb rgAcTfCb;
EXTERN U8 junkData[RG_ACC_MAX_PDU_SIZE];
/* The declarations of the functions follow */
EXTERN S16 rgAcTfActvInit ARGS((
         Ent   ent,
         Inst  inst,
         Region region,
         Reason reason));

EXTERN S16 rgAcTfActvTsk ARGS((
         Pst      *pst,
         Buffer   *mBuf));

EXTERN S16 rgAcNhActvInit ARGS((
         Ent   ent,
         Inst  inst,
         Region region,
         Reason reason));

EXTERN S16 rgAcNhActvTsk ARGS((
         Pst      *pst,
         Buffer   *mBuf));

EXTERN S16 rgAcNxActvInit ARGS((
         Ent   ent,
         Inst  inst,
         Region region,
         Reason reason));

EXTERN S16 rgAcNxActvTsk ARGS((
         Pst      *pst,
         Buffer   *mBuf));

EXTERN S16 rgAcKwActvInit ARGS((
         Ent   ent,
         Inst  inst,
         Region region,
         Reason reason));
EXTERN S16 rgAcRmActvInit ARGS((
         Ent   ent,
         Inst  inst,
         Region region,
         Reason reason));


EXTERN S16 rgAcKwActvTsk ARGS((
         Pst      *pst,
         Buffer   *mBuf));

EXTERN S16 rgAcRmActvTsk ARGS((
         Pst      *pst,
         Buffer   *mBuf));

EXTERN S16 rgAcTfActvTmr ARGS((Void));

EXTERN S16 rgAcLrgInit     ARGS ((Void)); 
EXTERN S16 rgAcLrgDeInit   ARGS ((Void)); 
EXTERN S16 rgAcTfuInit ARGS ((Void)); 
EXTERN S16 rgAcTfuDeInit ARGS ((Void)); 
EXTERN S16 rgAcRguInit ARGS ((Void)); 
EXTERN S16 rgAcRguDeInit ARGS ((Void)); 
EXTERN S16 rgAcCrgInit ARGS ((Void)); 
EXTERN S16 rgAcCrgDeInit ARGS ((Void)); 
EXTERN S16 rgAcRgrInit ARGS ((Void)); 
EXTERN S16 rgAcRgrDeInit ARGS ((Void)); 
EXTERN S16 rgAcDcfiStubSimpleCmdInit ARGS ((Void)); 
EXTERN S16 rgAcDcfiStubSimpleCmdDeInit ARGS ((Void)); 
EXTERN S16 rgAcRgmInit ARGS ((Void));
EXTERN S16 rgAcRgmDeInit ARGS ((Void));
/* Free functions declarations come here */
EXTERN S16 rgAcUtlTfuFreeFunc ARGS((CmXtaMsgQElm *qElm));

EXTERN S16 rgAcUtlCheckTime ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));

/* Find function declarations go here */
EXTERN CmXtaTCCb* rgAcUtlFindTcCb ARGS((Void));

/* Encoder decoder utility functions */
EXTERN S16 rgAcUtlDecodeDataPdu ARGS((
         Buffer        *inBuf,
         RgAcEdEvent   **outEvnt,
         U16           *padBytes));

EXTERN S16 rgAcUtlDecodeCEorPDU ARGS((
         CmMemListCp      *memCp,
         RgAcDatPdu       *datPdu,
         Buffer           *inBuf,
         U16              *padBytes));

EXTERN S16 rgAcUtlDecodeRarPdu ARGS((
         Buffer        *inBuf,
         RgAcEdEvent   **outEvnt,
         Bool          *biPres
         ));

EXTERN S16 rgAcUtlDecodeRarHdrs ARGS((
         CmMemListCp      *memCp,
         RgAcRarPdu       *rarPdu,
         Buffer           *inBuf));

EXTERN S16 rgAcUtlEncodeDatPdu ARGS((
         RgAcEdEvent   *inEvnt,
         Buffer        **outBuf,
         Bool          swpCESDU,
         Bool          invEBit,
         Bool          invLen,
         S16           dedBufIdx));

EXTERN S16 rgAcUtlAllocMem ARGS((
         Data      **ptr,
         Size      size));

EXTERN S16 rgAcUtlAllocEvnt ARGS((
 Data      **ptr,
 Size      size));

EXTERN S16 rgAcUtlFreeEvnt ARGS((
 Data         *ptr));

EXTERN S16 rgAcUtlTfuCompareBuf ARGS((
 Buffer        *buf1,
 Buffer        *buf2));

EXTERN S16 rgAcUtlFreeMem ARGS((
         Data      *ptr,
         Size      size));

#ifdef __cplusplus
}
#endif
#endif /* __RGAC_ACCX__ */


/**********************************************************************
         End of file:     rgac_acc.x@@/main/3 - Sat Jul 30 02:20:50 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm            1. Initial Release.
/main/2      ---     sm            1. LTE MAC 2.1 release
             rg001.201 sm          1. Added TTI indication towards 
                                        RGR user.
             rg002.201 sm          1. Adding preamble format to lenght mapping
                                      table.
           rg007.201   ap  1. Added support for MIMO
      rg008.201 rsharon 1.Added support for SPS.
      rg009.201 dv  1.Added support for TFU_UPGRADE.
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$      ---     rt      1. LTE MAC 4.1 release
*********************************************************************91*/
