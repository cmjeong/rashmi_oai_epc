



/************************************************************************
 
     Name:     LTE-MAC layer
 
     Type:     C source file
 
     Desc:     C source code for PFS functions
 
     File:     rg_sch_pfs.c
 
     Sid:      gk_sch_pfs.c@@/main/2 - Sat Jul 30 02:21:46 2011
 
     Prg:     apany
 
**********************************************************************/

/** @file rg_sch_pfs.c
@brief This module handles the proportional fair scheduler functionality
*/

static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_MODULE_ID=2;
static int RLOG_FILE_ID=170;

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm5.h"           /* common timers */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#include "lrg.h"
#include "rgr.h"
#include "rgm.h"
#include "tfu.h"
#include "rg_env.h"
#include "rg_sch_inf.h"
#include "rg_sch_err.h"
#include "rg_sch.h"
#include "rg_sch_cmn.h"
#include "rg_sch_pfs.h"
#include "rl_interface.h"
#include "rl_common.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"        /* common tokens */
#include "tfu.x"           /* RGU types */
#include "lrg.x"           /* layer management typedefs for MAC */
#include "rgr.x"           /* layer management typedefs for MAC */
#include "rgm.x"           /* layer management typedefs for MAC */
#include "rg_sch_inf.x"    /* typedefs for Scheduler */
#include "rg_sch.x"        /* typedefs for Scheduler */
#include "rg_sch_cmn.x"
#include "rg_sch_pfs.x"


/* Putting declarations in 'extern_ "C"' */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

EXTERN Ticks SGetTtiCount(Void);

/* Declarations for common functions (specific neither
 * to downlink, no uplink) */

PRIVATE Void rgSCHPfsInitFracPrioInfo ARGS((
         RgSchPfsFracPrioInfo   *fracPrioInfo,
         U32                    cfgdRate
         ));
PRIVATE Void rgSCHPfsUpdFracPrioInfo ARGS((
         RgSchPfsFracPrioInfo   *fracPrioInfo,
         U32                    allocd 
         ));
PRIVATE Void rgSCHPfsUlUpdPfsPrio ARGS((
         RgSchPfsUlCell        *pfsCell,
         RgSchPfsUlUe          *pfsUe,
         RgSchLcgCb            *lcg,
         Bool                  *prioChngd
         ));
PRIVATE Void rgSCHPfsDlUpdPfsPrio ARGS(( 
         RgSchEnbPfsDl         *pfsDl,
         RgSchPfsDlLc          *pfsLc,
         RgSchUeCb             *ue,
         RgSchPfsFracPrioInfo  *fracPrioInfo,
         Bool                  *prioChngd
         ));
PRIVATE Void rgSCHPfsFillRange ARGS((
        RgSchPfsPrioRange    *range,
        U32                   minPrios,
        U32                   maxPrios,
        U8                    numQs
        ));

/* Declarations for downlink functions */

PUBLIC S16 rgSCHEnbPfsDlCfg ARGS((
         Inst                instIdx,
         RgSchErrInfo       *err
         ));
PUBLIC Void rgSCHPfsDlInit ARGS((
         RgDlSchdApis       *apis
         ));

PUBLIC S16 rgSCHPfsDlCellCfg ARGS((
         RgSchCellCb        *cell,
         RgrCellCfg         *cfg,
         RgSchErrInfo       *err
         ));

PUBLIC S16 rgSCHPfsDlCellRecfg ARGS((
         RgSchCellCb        *cell,
         RgrCellRecfg       *recfg,
         RgSchErrInfo       *err
         ));
PUBLIC Void rgSCHEnbPfsDlDel ARGS((
         Inst              inst
         ));
PUBLIC Void rgSCHPfsDlCellDel ARGS((
         RgSchCellCb       *cell
         ));
PUBLIC S16 rgSCHPfsDlUeCfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgrUeCfg         *cfg,
         RgSchErrInfo     *err
         ));
#ifdef LTE_ADV
PUBLIC S16 rgSCHPfsSCellDlUeCfg ARGS((
         RgSchCellCb      *sCell,
         RgSchUeCb        *ue,
         RgSchErrInfo     *err
         ));

PUBLIC S16 rgSCHPfsSCellDlUeDel ARGS((
         RgSchUeCellInfo *sCellInfo,
         RgSchUeCb       *ue
         ));
PUBLIC S16 rgSCHPfsDlSCellDeactv ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC S16 rgSCHPfsDlSCellActv ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
#endif
PUBLIC S16 rgSCHPfsDlUeRecfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgrUeRecfg       *recfg,
         RgSchErrInfo     *err
         ));
PUBLIC Void rgSCHPfsDlUeDel ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC Void rgSCHPfsDlUeReset ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC S16 rgSCHPfsDlLcCfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchDlLcCb      *lc,
         RgrLchCfg        *cfg,
         RgSchErrInfo     *err
         ));
PUBLIC S16 rgSCHPfsDlLcRecfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchDlLcCb      *lc,
         RgrLchRecfg      *recfg,
         RgSchErrInfo     *err
         ));
PUBLIC Void rgSCHPfsDlLcDel ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchDlLcCb      *lc
         ));
PUBLIC Void rgSCHPfsDlInactvLstInd ARGS((
         RgSchCellCb      *cell,
         CmLListCp        *lst
         ));
PRIVATE Void rgSCHPfsDlUeInactv ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC Void rgSCHPfsDlActvUeInd ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC Void rgSCHPfsDlCqiInd ARGS((
         RgSchCellCb          *cell,
         RgSchUeCb            *ue,
         Bool                 isPucchInfo,
         Void                 *dlCqi
         ));
PRIVATE Void rgSCHPfsDlSchedTa ARGS((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc
         ));
PRIVATE S16 rgSCHPfsDlSchedTaForUe ARGS((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc,
         RgSchDlSf               *sf,
         RgSchUeCb               *ue
         ));
PRIVATE Void rgSCHPfsDlSchedRetx ARGS((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc
         ));
PRIVATE Void rgSCHPfsDlSchedNewTx ARGS((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc
         ));
PRIVATE Void rgSCHPfsDlPreSchedNewTx ARGS((
    RgSchCellCb *cell
         ));
PRIVATE Void rgSCHPfsDlNewTxInQ ARGS((
         CmLListCp               *txQ,
         U8                      *remCellCnt,
         U8                      qId
         ));
PRIVATE Void rgSCHPfsDlRetxInQ ARGS((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc,
         CmLListCp               *retxQ
         ));
PUBLIC Void rgSCHPfsDlProcRetx ARGS((
         RgSchCellCb         *cell,
         RgSchDlHqProcCb     *proc
         ));
PRIVATE Void rgSCHPfsDlProcAddToRetx ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgSchDlHqProcCb     *proc
         ));
PRIVATE Void rgSCHPfsDlProcAddToCellRetx ARGS((
         RgSchCellCb         *cell,
         RgSchDlHqProcCb     *proc
         ));
PRIVATE Void rgSCHPfsDlProcRmvFrmCellRetx ARGS((
         RgSchCellCb         *cell,
         RgSchDlHqProcCb     *proc
         ));
PRIVATE Void rgSCHPfsDlProcRmvFrmUeRetx ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgSchDlHqProcCb     *proc
         ));
PUBLIC Void rgSCHPfsDlOnAlloc ARGS((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc
         ));
PRIVATE Void rgSCHPfsDlOnRetxAlloc ARGS((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc
         ));
PRIVATE Void rgSCHPfsDlOnNewTxAlloc ARGS((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc
         ));
PRIVATE Void rgSCHPfsDlOnNewTxAllocForUe ARGS((
         RgSchCellCb             *cell,
         RgSchUeCb               *ue,
         RgSchCmnDlRbAllocInfo   *alloc
         ));
PRIVATE Void rgSCHPfsDlLcPartlyAllocd ARGS((
         RgSchCellCb        *cell,
         RgSchUeCb          *ue,
         RgSchDlLcCb        *lc,
         U32                 diff,
         RgSchDlHqTbCb      *tbInfo
         ));
PRIVATE Void rgSCHPfsDlLcFullyAllocd ARGS((
         RgSchCellCb        *cell,
         RgSchUeCb          *ue,
         RgSchDlLcCb        *lc,
         RgSchDlHqTbCb      *tbInfo
         ));
PRIVATE Void rgSCHPfsDlNewTxTbDstn ARGS((
         RgSchCellCb    *cell,
         RgSchUeCb      *ue,
         RgSchDlHqTbCb  *tbInfo,
         U32            *effAlloc,
         CmLList        **node
         ));
PRIVATE Void rgSCHPfsDlSprTxTbDstn ARGS((
         RgSchCellCb    *cell,
         RgSchUeCb      *ue,
         RgSchDlHqTbCb  *tbInfo,
         U32            *effAlloc,
         CmLList        *node
));
PUBLIC Void rgSCHPfsDlBoUpd ARGS((
         RgSchCellCb            *cell,
         RgSchUeCb              *ue,
         RgSchDlLcCb            *lc
         ));
PRIVATE Void rgSCHPfsDlBoUpdInt ARGS((
         RgSchCellCb            *cell,
         RgSchUeCb              *ue,
         RgSchDlLcCb            *lc,
         U32                     bo,
         U32                     allocd
         ));
PRIVATE Void rgSCHPfsDlAddLcAllocToProc ARGS((
         RgSchCellCb            *cell,
         RgSchUeCb              *ue,
         RgSchDlLcCb            *lc,
         U32                     bytes,
         RgSchDlHqTbCb          *tbInfo
         ));
/* Modified the prototype of the below function
 * to add a new parmater allocd*/
PRIVATE Void rgSCHPfsDlPrioAmbrSvcUpd ARGS((
         RgSchCellCb        *cell,
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         U32                allocd
         ));
PRIVATE Void rgSCHPfsDlLcAddToSrbQ ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchPfsDlLc       *pfsLc
         ));
PRIVATE Void rgSCHPfsDlLcAddToDrb0Q ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchPfsDlLc       *pfsLc
         ));
PRIVATE Void rgSCHPfsDlLcAddToGbrQ ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchPfsDlLc       *pfsLc,
         Bool               prioChngd,
         U32                allocd
         ));
PRIVATE Void rgSCHPfsDlLcAddToMbrQ ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchPfsDlLc       *pfsLc,
         Bool               prioChngd,
         U32                allocd
         ));
PRIVATE Void rgSCHPfsDlLcAddToAmbrQ ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchPfsDlLc       *pfsLc,
         U32                allocd
         ));
PRIVATE Void rgSCHPfsDlLcAddToQ ARGS((
         RgSchCellCb            *cell,
         RgSchPfsDlUe       *pfsUe,
         CmLListCp          *cp,
         RgSchPfsDlLc       *pfsLc
         ));
PRIVATE Void rgSCHPfsDlLcAmbrBoUpd ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchDlLcCb        *lc,
         U32                 bo,
         U32                 allocd
         ));
PRIVATE Void rgSCHPfsDlRemAmbrZero ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchPfsDlUe       *pfsUe
         ));
PRIVATE Void rgSCHPfsDlLcGbrBoUpd ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchDlLcCb        *lc,
         U32                 bo,
         U32                 allocd
         ));
PRIVATE Void rgSCHPfsDlLcAmbrActv ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchDlLcCb        *lc,
         U32                 bo,
         U32                 allocd
         ));
PRIVATE Void rgSCHPfsDlLcAmbrInactv ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchUeCb          *ue,
         RgSchDlLcCb        *lc
         ));
PRIVATE Void rgSCHPfsDlLcInsInUeAmbrLst ARGS((
         RgSchCellCb         *cell,
         RgSchPfsDlUe       *pfsUe,
         RgSchDlLcCb        *lc
         ));
PRIVATE U8 rgSCHPfsDlGetQId ARGS((
         RgSchPfsDlLc       *pfsLc,
         RgSchPfsPrioRange  *range,
         U32                 prioVal,
         U8                  maxQId
         ));
PRIVATE Void rgSCHPfsDlLcRmvFrmPrioQ ARGS((
         RgSchEnbPfsDl      *pfsDl,
         RgSchPfsDlUe       *pfsUe,
         RgSchPfsDlLc       *pfsLc
         ));
PRIVATE Void rgSCHPfsDlLcRmvFrmPdbTrckQ ARGS((
         RgSchPfsDlLc       *pfsLc
         ));
PUBLIC Void rgSCHPfsDlUeRefresh ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue
         ));
PRIVATE Void rgSCHPfsDlLcGbrRefresh ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgSchDlLcCb         *lc
         ));
PRIVATE U32 rgSchPfsDlGetSvcPrio ARGS((
         RgSchEnbPfsDl       *pfsDl,
         U8                   qci
         ));
PRIVATE U32 rgSCHPfsDlGetTpPrio ARGS((
         RgSchEnbPfsDl       *pfsDl,
         U8                   iTbs
         ));
PRIVATE S16 rgSCHPfsDlUeSched ARGS((
         RgSchCellCb           *cell,
         RgSchCmnDlRbAllocInfo *alloc,
         RgSchDlSf             *sf,
         RgSchUeCb             *ue
         ));
PRIVATE RgSchDlHqProcCb *rgSCHPfsDlGetAvlProc ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         CmLListCp           *retxQ
         ));
PRIVATE Void rgSCHPfsDlRlsHqProc ARGS((
         RgSchUeCb           *ue,
         RgSchDlHqProcCb     *proc
         ));
PRIVATE Void rgSCHPfsDlResetProcs ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue
         ));
PRIVATE Void rgSCHPfsDlUeSfResetTemp ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
        RgSchDlHqProcCb      *hqP
         ));
PRIVATE S16 rgSchPfsCreateLcSchedLst ARGS ((
         CmLListCp            *txQ,
         U8                   *remCellCnt,
         U8                   qId
        ));
#if RG_UNUSED
PRIVATE U8 rgSchPfsCreateSfrAbsDlLcLst ARGS ((
        RgSchCellCb             *cell,
        CmLListCp               *txQ,
        CmLListCp               *retxQ,
        RgSchCmnDlRbAllocInfo   *alloc,
        RgSchPfsDlLcSchdInfo    *toBeSchedInfo
        ));
PRIVATE U8 rgSchPfsCreateNonAbsUeDlLcLst ARGS ((
        RgSchCellCb            *cell,
        CmLListCp              *txQ,
        CmLListCp              *retxQ,
        RgSchDlSf              *sf,
        RgSchPfsDlLcSchdInfo   *toBeSchedInfo
        ));
#endif

PRIVATE Void rgSCHPfsAddLcToSchedLst ARGS ((
        RgSchDlLcCb        *lc,
        CmLListCp          *lcToBeSchedLst
        ));
PRIVATE Void rgSCHPfsRlsSchedRes ARGS ((
        RgSchCellCb     *cell,
        RgSchUeCb               *ue,
        RgSchCmnDlRbAllocInfo   *alloc
        ));
#if RG_UNUSED
PRIVATE Void rgSCHPfsDlNewTxInSfrAbsQ ARGS ((
        RgSchCellCb             *cell,
        RgSchCmnDlRbAllocInfo   *alloc,
        CmLListCp               *txQ,
        CmLListCp               *retxQ,
        Bool                    *isBwLeftRef,
        RgSchPfsDlLcSchdInfo    *toBeSchedInfo
        ));
PRIVATE Void rgSCHPfsDlNewTxInNonAbsQ ARGS ((
        RgSchCellCb             *cell,
        RgSchCmnDlRbAllocInfo   *alloc,
        CmLListCp               *txQ,
        CmLListCp               *retxQ,
        Bool                    *isBwLeftRef,
        RgSchPfsDlLcSchdInfo    *toBeSchedInfo
        ));
#endif
PRIVATE Void rgSCHPfsDlNewTxInNormQ ARGS ((
        CmLListCp               *txQ,
        U8                      *remCellCnt,
        U8                      qId
        ));
PRIVATE Void rgSCHPfsScheduleUes ARGS ((
         RgSchCellCb             *cell,
         RgSchCmnDlRbAllocInfo   *alloc,
         RgSchPfsDlLcSchdInfo    *lcToBeSchedInfo
         ));
/* Declarations for uplink functions */

PUBLIC Void rgSCHPfsUlInit ARGS((
         RgUlSchdApis         *apis
         ));
PUBLIC S16 rgSCHPfsUlCellCfg ARGS((
         RgSchCellCb          *cell,
         RgrCellCfg           *cfg,
         RgSchErrInfo         *err
         ));
PUBLIC S16 rgSCHPfsUlCellRecfg ARGS((
         RgSchCellCb     *cell,
         RgrCellRecfg    *recfg,
         RgSchErrInfo    *err
         ));
PUBLIC Void rgSCHPfsUlCellDel ARGS((
         RgSchCellCb       *cell
         ));
PUBLIC S16 rgSCHPfsUlUeCfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgrUeCfg         *cfg,
         RgSchErrInfo     *err
         ));
PUBLIC S16 rgSCHPfsUlUeRecfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgrUeRecfg       *recfg,
         RgSchErrInfo     *err
         ));
PUBLIC Void rgSCHPfsUlUeDel ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC Void rgSCHPfsUlUeReset ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC S16 rgSCHPfsUlLchCfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgrLchCfg        *cfg,
         RgSchErrInfo     *err
         ));
PUBLIC S16 rgSCHPfsUlLchRecfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgrLchRecfg      *recfg,
         RgSchErrInfo     *err
         ));
PUBLIC S16 rgSCHPfsUlLchDel ARGS ((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         CmLteLcId        lcId,
         U8               lcgId
         ));
PUBLIC S16 rgSCHPfsUlLcgCfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchLcgCb       *lcg,
         RgrLcgCfg        *cfg,
         RgSchErrInfo     *err
         ));
PUBLIC S16 rgSCHPfsUlLcgRecfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchLcgCb       *lcg,
         RgrLcgRecfg      *recfg,
         RgSchErrInfo     *err
         ));
PUBLIC Void rgSCHPfsUlLcgDel ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchLcgCb       *lcg
         ));
PUBLIC Void rgSCHPfsUlUeRefresh ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue
         ));
PUBLIC S16 rgSCHPfsUlLcgUpd ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgInfUeDatInd       *datInd
         ));
PUBLIC Void rgSCHPfsUlSched ARGS((
         RgSchCellCb             *cell,
         RgSchCmnUlRbAllocInfo   *alloc
         ));
PRIVATE Void rgSCHPfsUlSchedNewTx ARGS((
         RgSchCellCb             *cell,
         RgSchCmnUlRbAllocInfo   *alloc,
         U8                       remUe
         ));
PRIVATE Void rgSCHPfsUlSchedContRes ARGS((
         RgSchCellCb             *cell,
         RgSchCmnUlRbAllocInfo   *alloc,
         U8                      *remUeRef,
         U32                     *numCntResSbs
         ));
PRIVATE Void rgSCHPfsUlSchedSig ARGS((
         RgSchCellCb             *cell,
         RgSchCmnUlRbAllocInfo   *alloc,
         U8                      *remUeRef,
         RgSchPfsLcSchdInfo      *toBeSchedInfo
         ));
PRIVATE Void rgSCHPfsUlSchedDat ARGS((
         RgSchCellCb             *cell,
         RgSchCmnUlRbAllocInfo   *alloc,
         CmLListCp               *txQ,
         U8                      *remUeRef,
         RgSchPfsLcSchdInfo      *toBeSchedInfo
         ));
PRIVATE S16 rgSCHPfsUlSchedUeForContRes ARGS((
         RgSchCellCb             *cell,
         RgSchCmnUlRbAllocInfo   *alloc,
         RgSchUeCb               *ue
         ));
PRIVATE S16 rgSCHPfsUlSchedUeForSigDat ARGS((
         RgSchCellCb             *cell,
         RgSchCmnUlRbAllocInfo   *alloc,
         RgSchUeCb               *ue,
         RgSchPfsLcSchdInfo      *toBeSchedInfo
         ));
PUBLIC Void rgSCHPfsUlUpdBsrShort ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgSchLcgCb          *lcg,
         U8                   bsr
         ));
PUBLIC Void rgSCHPfsUlUpdBsrTrunc ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgSchLcgCb          *lcg,
         U8                   bsr
         ));
PUBLIC Void rgSCHPfsUlUpdBsrLong ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         U8                   bsrArr[]
         ));
PRIVATE Void rgSCHPfsUlMngUeInQ ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         U32                 allocd
         ));
PUBLIC Void rgSCHPfsUlInactvLstInd ARGS((
         RgSchCellCb      *cell,
         CmLListCp        *lst
         ));
PRIVATE Void rgSCHPfsUlUeInactv ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC Void rgSCHPfsUlActvUeInd ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue
         ));
PUBLIC Void rgSCHPfsUlCqiInd ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         TfuUlCqiRpt         *cqiInfo
         ));
PRIVATE Void rgSCHPfsUlAddUeToSigQ ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue
         ));
PRIVATE Void rgSCHPfsUlAddUeToPfsQ ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgSchLcgCb          *lcg,
         Bool                prioChngd
         ));
PUBLIC Void rgSCHPfsUlSrInd ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue
         ));
PRIVATE Void rgSCHPfsUlRmvUeFrmQ ARGS((
         RgSchCellCb        *cell,
         RgSchUeCb          *ue
         ));
PRIVATE Void rgSCHPfsUlAddUeToQ ARGS((
         RgSchCellCb         *cell,
         CmLListCp           *cp,
         RgSchUeCb           *ue
         ));
PUBLIC Void rgSCHPfsUlContResReq ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue
         ));
PUBLIC Void rgSCHPfsUlOnAlloc ARGS((
         RgSchCellCb           *cell,
         RgSchCmnUlRbAllocInfo *alloc
         ));
PRIVATE Void rgSCHPfsUlUeSfResetTemp ARGS((
         RgSchCellCb             *cell,
         RgSchUeCb               *ue,
         CmLListCp               *ulInactvLst
         ));
PRIVATE U32 rgSCHPfsUlGetTpPrio ARGS((
         RgSchPfsUlCell      *pfsCell,
         U8                   cqiPrioIdx
         ));
PRIVATE U32 rgSCHPfsUlGetQId ARGS((
         RgSchPfsUlCell      *pfsCell,
         RgSchPfsPrioRange   *range,
         U32                  pfsPrio
         ));
PUBLIC S16 rgSCHPfsDlUeHqEntInit ARGS((
         RgSchCellCb      *cell,
         RgSchDlHqEnt     *hqEnt
         ));
PUBLIC S16 rgSCHPfsDlUeHqEntDeInit ARGS((
         RgSchCellCb      *cell,
         RgSchDlHqEnt     *hqE
         ));
PUBLIC Void rgSCHPfsDlProcRmvFrmRetx ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgSchDlHqProcCb     *proc
         ));
PRIVATE Void rgSCHPfsFillTbl ARGS((
         U32               *src,
         U32               *dst,
         U32               numEntries,
         U32               *minVal,
         U32               *maxVal
));
PRIVATE Void rgSCHPfsDlSvcFillTbl ARGS((
         U32               *src,
         U32               *dst,
         U32               strtEntry,
         U32               endEntry,
         U32               *minVal,
         U32               *maxVal
));

PUBLIC Void rgSCHPfsDlScanUpdPdbPrio ARGS((
RgSchCellCb *cell
));
PRIVATE Void rgSCHPfsDlCalcPdbMetric ARGS((
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *lc
));

PRIVATE Void rgSchPfsResetPdbCbCntxt ARGS((
RgSchCellCb            *cell,
RgSchDlLcCb            *lc
));

PRIVATE Void rgSCHPfsDlLcAddToPdbTrckQ ARGS((
RgSchEnbPfsDl        *pfsDl,
RgSchDlLcCb          *lc,
U32                  qId
));

PUBLIC S16 rgSCHPfsDlFillFlowCntrlInfo ARGS((
RgSchCellCb    *cell,
RgInfSfAlloc   *sfAlloc
));

PRIVATE Void rgSCHPfsAddDlLcToAmbrLst ARGS((
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchPfsDlLc       *pfsLc,
U32                qId
));

PRIVATE Void rgSCHPfsDlLcUpdPrioRepos ARGS((
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchPfsDlLc       *pfsLc
));

PUBLIC Void RgSchPfsUpdMaxPrbCnt ARGS((
RgSchCellCb          *cell
));

PRIVATE Void rgSchPfsUpdPrioQ ARGS((
 RgSchCellCb     *cell,
 RgSchUeCb       *ue,
 RgSchPfsDlLc    *pfsLc
 ));



PUBLIC Void rgSCHPfsDlRmvFrmPrioChngLst ARGS((
  Inst      schInst
  ));

PRIVATE Void rgSCHPfsDlLcUpdQ ARGS((
  CmLListCp          *cp,
  RgSchPfsDlLc       *pfsLc
  ));

PRIVATE S16 rgSchPfsGetRetxQ ARGS((
  RgSchPfsDlCell   *pfsCell, 
  RgSchPfsDlLc     *pfsLc,
  U8               qId,
  CmLListCp        **retxQ
  ));

PRIVATE Void rgSchPfsToBeSchedInit ARGS((
  RgSchCellCb             *cell
  ));

#ifdef LTE_ADV
PRIVATE U8 rgSchPfsGetDlRetxQId ARGS((
 RgSchCellCb     *cell,
 RgSchUeCb       *ue,
 RgSchPfsDlLc    *pfsLc,
 U32             pfsPrio
 ));
PRIVATE S16  rgSCHAddUeToNextCell ARGS((
 RgSchPfsDlLcSchdInfo  *lcToBeSchedInfo,
 RgSchUeCb             *ue,
 U32                   pfsPrioInNextCell,
 RgSchUeCb             *nextCellDlUe
 ));

PRIVATE S16 rgSCHPfsSchedLcInNextFavCell ARGS((
  RgSchCellCb            *cell,
  RgSchUeCb              *prevCellUe,
  RgSchDlLcCb            *lc
  ));

PRIVATE Void rgSchPfsGetLcFavCellLst ARGS((
RgSchDlLcCb       *lc
));

PRIVATE S16 rgSCHPfsDlSchdSecCellActCe ARGS((
  RgSchCellCb             *cell,
  RgSchCmnDlRbAllocInfo   *allocInfo
  ));

#endif

PUBLIC Void rgSCHPfsDlCeSchd ARGS((
  RgSchCellCb             *cell,
  RgSchCmnDlRbAllocInfo   *allocInfo
  ));

PRIVATE Void rgSchPfsCalcUePrbAndPrio ARGS((
  RgSchCellCb        *cell,
  RgSchUeCb          *ue,
  RgSchDlHqProcCb    *proc
  ));
#ifdef __cplusplus
}
#endif /* __cplusplus */

U32 rgSchPfsScalingFactor[RG_SCH_PFS_MAX_FACTOR_LVLS]= {100,100,100,100,100,10,10,10,10,1,1};
U32 rgSchPfsTpFactorSelector[RG_SCH_PFS_MAX_FACTOR_LVLS][RG_SCH_PFS_TP_FACTOR_LVLS]= 
   { RG_SCH_PFS_TP_FACTOR_0,RG_SCH_PFS_TP_FACTOR_1,RG_SCH_PFS_TP_FACTOR_2,
     RG_SCH_PFS_TP_FACTOR_3,RG_SCH_PFS_TP_FACTOR_4,RG_SCH_PFS_TP_FACTOR_5,
     RG_SCH_PFS_TP_FACTOR_6,RG_SCH_PFS_TP_FACTOR_7,RG_SCH_PFS_TP_FACTOR_8,
     RG_SCH_PFS_TP_FACTOR_9,RG_SCH_PFS_TP_FACTOR_10};
U32 rgSchPfsFairnessFactorSelector[RG_SCH_PFS_MAX_FACTOR_LVLS][RG_SCH_PFS_FAIRNESS_FACTOR_LVLS]= 
   { RG_SCH_PFS_FAIR_FACTOR_0,RG_SCH_PFS_FAIR_FACTOR_1,RG_SCH_PFS_FAIR_FACTOR_2,
     RG_SCH_PFS_FAIR_FACTOR_3,RG_SCH_PFS_FAIR_FACTOR_4,RG_SCH_PFS_FAIR_FACTOR_5,
     RG_SCH_PFS_FAIR_FACTOR_6,RG_SCH_PFS_FAIR_FACTOR_7,RG_SCH_PFS_FAIR_FACTOR_8,
     RG_SCH_PFS_FAIR_FACTOR_9,RG_SCH_PFS_FAIR_FACTOR_10};

/* PDB details for each QCI */
RgSchPfsQciPdbInfo rgSchPfsQciPdbInfo[RG_SCH_CMN_MAX_QCI] = { 
/* pdb  maxNmbPdbLvls lastLvl4FullFlow pdbLvlSz=pdb/maxNmbPdbLvls  pdbPrioWgt */
  {80,  3,            2,               26,                         {11,12,14,0}},
  {130, 3,            2,               43,                         {11,12,14,0}},
  {30,  2,            1,               15,                         {11,14,0,0}},
  {280, 4,            3,               70,                         {11,12,13,14}},
  {80,  3,            2,               26,                         {11,12,14,0}},
  {280, 4,            3,               70,                         {11,12,13,14}},
  {80,  3,            2,               26,                         {11,12,14,0}},
  {280, 4,            3,               70,                         {11,12,13,14}},
  {280, 4,            3,               70,                         {11,12,13,14}},
};
#define RG_SCH_PFS_FCTRL_MIN_RCVRY_TIME 50 

/**** DOWNLINK functions ****/

/**
 * @brief This function initializes all the data for the scheduler
 *
 * @details
 *
 *     Function: rgSCHPfsDlInit
 *
 *     Processing Steps:
 *     - Assigns the various callback APIs
 *
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlInit
(
RgDlSchdApis         *apis
)
#else
PUBLIC Void rgSCHPfsDlInit(apis)
RgDlSchdApis         *apis;
#endif
{
   TRC2(rgSCHPfsDlInit);

   apis->rgSCHRgrDlUeCfg        = rgSCHPfsDlUeCfg;
   apis->rgSCHRgrDlUeRecfg      = rgSCHPfsDlUeRecfg;
   apis->rgSCHFreeDlUe          = rgSCHPfsDlUeDel;
   apis->rgSCHRgrDlCellCfg      = rgSCHPfsDlCellCfg;
   apis->rgSCHRgrDlCellRecfg    = rgSCHPfsDlCellRecfg; 
   apis->rgSCHFreeDlCell        = rgSCHPfsDlCellDel;
   apis->rgSCHRgrDlLcCfg        = rgSCHPfsDlLcCfg;
   apis->rgSCHRgrDlLcRecfg      = rgSCHPfsDlLcRecfg;
   apis->rgSCHFreeDlLc          = rgSCHPfsDlLcDel;
   apis->rgSCHDlNewSched        = rgSCHPfsDlSchedNewTx;
   apis->rgSCHDlPreSched        = rgSCHPfsDlPreSchedNewTx;
   apis->rgSCHDlPstSched        = rgSCHPfsDlRmvFrmPrioChngLst;
   apis->rgSCHDlRetxSched       = rgSCHPfsDlSchedRetx;
   apis->rgSCHDlCeSched         = rgSCHPfsDlCeSchd;
   apis->rgSCHDlDedBoUpd        = rgSCHPfsDlBoUpd;
   apis->rgSCHDlProcAddToRetx   = rgSCHPfsDlProcRetx;
   apis->rgSCHDlAllocFnlz       = rgSCHPfsDlOnAlloc;
   apis->rgSCHDlCqiInd          = rgSCHPfsDlCqiInd;
   apis->rgSCHDlUeRefresh       = rgSCHPfsDlUeRefresh;
   apis->rgSCHDlUeReset         = rgSCHPfsDlUeReset;
   apis->rgSCHDlActvtUe         = rgSCHPfsDlActvUeInd;
   apis->rgSCHDlInactvtUes      = rgSCHPfsDlInactvLstInd;
   apis->rgSCHDlUeHqEntInit     = rgSCHPfsDlUeHqEntInit;
   apis->rgSCHDlUeHqEntDeInit   = rgSCHPfsDlUeHqEntDeInit;
   apis->rgSCHDlProcRmvFrmRetx  = rgSCHPfsDlProcRmvFrmRetx;
   apis->rgSCHDlTickForPdbTrkng = rgSCHPfsDlScanUpdPdbPrio;
   apis->rgSCHDlFillFlwCtrlInfo = rgSCHPfsDlFillFlowCntrlInfo; 
#ifdef LTE_ADV
   apis->rgSCHRgrSCellDlUeCfg   = rgSCHPfsSCellDlUeCfg;
   apis->rgSCHRgrSCellDlUeDel   = rgSCHPfsSCellDlUeDel;
   apis->rgSCHDlSCellDeactv     = rgSCHPfsDlSCellDeactv;
   apis->rgSCHDlSCellActv       = rgSCHPfsDlSCellActv;
#endif
   RETVOID;
}

/**
 * @brief This function calculates and updates the maximum
 * PRB count at which PDB based flow control is allowed to
 * get triggered.
 * @details
 *
 *     Function: RgSchPfsUpdMaxPrbCnt
 *
 *     Processing Steps:
 *     - Updates the maxPrbCnt value based on BW and 
 *       config mode
 *
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void   RgSchPfsUpdMaxPrbCnt
(
RgSchCellCb          *cell
)
#else
PUBLIC Void   RgSchPfsUpdMaxPrbCnt(cell)
RgSchCellCb          *cell;
#endif
{
   U32  numDlSf = 0;
  
   TRC2(RgSchPfsUpdMaxPrbCnt);
  
#ifdef LTE_TDD
   numDlSf = (RG_SCH_PFS_FLW_CTRL_TRIG_TIME/RGSCH_NUM_SUB_FRAMES) * rgSchTddNumDlSubfrmTbl[cell->ulDlCfgIdx][RGSCH_NUM_SUB_FRAMES-1];
#else
   numDlSf = RG_SCH_PFS_FLW_CTRL_TRIG_TIME * RGSCH_NUM_SUB_FRAMES; 
#endif
   
   /*printf("numDlSf=%ld, bw=%ld , numDlSfTBl=%d,maxPrbCnt=%ld\n",
           numDlSf,cell->bwCfg.dlTotalBw,
          rgSchTddNumDlSubfrmTbl[cell->ulDlCfgIdx][RGSCH_NUM_SUB_FRAMES-1],
             cell->maxPrbCnt); */
   RETVOID;
}
/**
 * @brief Cell configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlCellCfg
 *
 *     Processing Steps:
 *      - Create the pfsCell info within passed SchCell
 *      - Update priority tables
 *      - Determine the min, max and priority ranges per
 *        PFS queue and store them
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[in]  RgrCellCfg          *cfg
 *  @param[out] RgSchErrInfo        *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlCellCfg
(
RgSchCellCb          *cell,
RgrCellCfg           *cfg,
RgSchErrInfo         *err
)
#else
PUBLIC S16 rgSCHPfsDlCellCfg(cell, cfg, err)
RgSchCellCb          *cell;
RgrCellCfg           *cfg;
RgSchErrInfo         *err;
#endif
{
   RgSchCmnDlCell      *cmnCell = RG_SCH_CMN_GET_DL_CELL(cell);
   RgSchPfsDlCell      *pfsCell;
   U8                   numSamples;

   UNUSED(err);
   TRC2(rgSCHPfsDlCellCfg);

   if (rgSCHUtlAllocSBuf(cell->instIdx,
            (Data**)&cmnCell->schSpfc, (sizeof(RgSchPfsDlCell))) != ROK)
   {
      RETVALUE(RFAILED);
   }
   pfsCell = (RgSchPfsDlCell *)(cmnCell->schSpfc);
   pfsCell->cell = cell;

   numSamples = RG_SCH_PFS_DL_PRB_USE_PRD/RG_SCH_PFS_DL_PRB_SAMPLE_SIZE;

   if (rgSCHUtlAllocSBuf(cell->instIdx,
          (Data**)&pfsCell->prbUsage, (sizeof(U16) * numSamples)) != ROK)
   {
      rgSCHUtlFreeSBuf(cell->instIdx,
         (Data**)(&(cmnCell->schSpfc)), (sizeof(RgSchPfsDlCell)));
      RETVALUE(RFAILED);
   }

   pfsCell->totalPrbUse = 0;
   pfsCell->prevSampleIdx = 0;
   pfsCell->prbSample = 0;
   pfsCell->ttiCnt = 0;
   RETVALUE(ROK);
}

/**
 * @brief Cell configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHEnbPfsDlCfg
 *
 *     Processing Steps:
 *      - Create the pfsDl info within passed SchCell
 *      - Update priority tables
 *      - Determine the min, max and priority ranges per
 *        PFS queue and store them
 *
 *  @param[in]  Inst                 inst
 *  @param[out] RgSchErrInfo        *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHEnbPfsDlCfg
(
Inst                  inst,
RgSchErrInfo         *err
)
#else
PUBLIC S16 rgSCHEnbPfsDlCfg(inst, err)
Inst                  inst;
RgSchErrInfo         *err;
#endif
{
   RgrEnbPfs            *dlPfsCfg = &rgSchCb[inst].rgrSchedEnbCfg.dlSchInfo.dlPfs;
   RgSchEnbPfsDl       *pfsDl;
   U32                  minTpPrio;
   U32                  maxTpPrio;
   U32                  minFairPrio;
   U32                  maxFairPrio;
   U32                  maxSvcPrio;
   U32                  minGbrPrio;
   U32                  maxGbrPrio;
   U32                  minAmbrPrio;
   U32                  maxAmbrPrio;
   U32                  minPrio;
   U32                  maxPrio;

   UNUSED(err);
   TRC2(rgSCHEnbPfsDlCfg);

   if (rgSCHUtlAllocSBuf(inst, 
        (Data**)(&(rgSchCb[inst].rgSchEnbPfsDl)), (sizeof(RgSchEnbPfsDl))) != ROK)
   {
      RETVALUE(RFAILED);
   }
   pfsDl = (RgSchEnbPfsDl *)rgSchCb[inst].rgSchEnbPfsDl;

   pfsDl->cfgdTpFact = dlPfsCfg->tptCoeffi; 
   pfsDl->prioScaleFact = (rgSchPfsScalingFactor[dlPfsCfg->tptCoeffi] * \
        rgSchPfsScalingFactor[dlPfsCfg->fairCoeffi]);

   /* Derive TP priority values based on TP factor */
   rgSCHPfsFillTbl(rgSchPfsTpFactorSelector[dlPfsCfg->tptCoeffi],
                   pfsDl->tbls.tpPrios, RG_SCH_PFS_TP_FACTOR_LVLS, 
                   &minTpPrio, &maxTpPrio);
   /* Consider Rank in min/maxTpPrio determination */
   if(pfsDl->cfgdTpFact !=  RG_SCH_PFS_NO_TP_WEIGHT_FACTOR)
   {
      minTpPrio = RGSCH_CEIL(minTpPrio, 
            rgSchCb[inst].rgrSchedEnbCfg.numTxAntPorts); 
   }

   /* Derive Fairness priority values based on Fairness factor */
   rgSCHPfsFillTbl(rgSchPfsFairnessFactorSelector[dlPfsCfg->fairCoeffi],  
                   pfsDl->tbls.fairPrios, RG_SCH_PFS_FAIRNESS_FACTOR_LVLS, 
                   &minFairPrio, &maxFairPrio);

   /* GBR/MBR service priorities */
   rgSCHPfsDlSvcFillTbl(&dlPfsCfg->qciWgt[RG_SCH_CMN_GBR_QCI_START - 1],
                        &pfsDl->tbls.svcQciPrios[RG_SCH_CMN_GBR_QCI_START - 1],
                        RG_SCH_CMN_GBR_QCI_START-1, RG_SCH_CMN_GBR_QCI_END-1,
                         &minGbrPrio, &maxGbrPrio);

   /* QCI 5 Service Priority */
   pfsDl->tbls.svcQciPrios[4] = dlPfsCfg->qciWgt[4];

   /* AMBR (except priority 0) service priorities */
   rgSCHPfsDlSvcFillTbl(&dlPfsCfg->qciWgt[RG_SCH_CMN_NGBR_QCI_START - 1],
                        &pfsDl->tbls.svcQciPrios[RG_SCH_CMN_NGBR_QCI_START - 1],
                        RG_SCH_CMN_NGBR_QCI_START-1, RG_SCH_CMN_NGBR_QCI_END-1,
         &minAmbrPrio, &maxAmbrPrio);
   maxSvcPrio = RGSCH_MAX(maxAmbrPrio, maxGbrPrio);
   /* Priority zero service is not considered in calculating PFS priority */

   /* Make sure that there are non-zero priority values */
   if ((maxTpPrio == 0) || (maxFairPrio == 0) || (maxSvcPrio == 0))
   {
      /*RLOG_ARG0(L_ERROR,DBG_CELLID,cell->cellId, 
               "rgSCHEnbPfsDlCfg(): Priority values are all zero");*/
     /* ccpu00117052 - MOD - Passing double pointer
      for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(inst,
         (Data**)(&(rgSchCb[inst].rgSchEnbPfsDl)), (sizeof(RgSchEnbPfsDl)));
      RETVALUE(RFAILED);
   }

   /* Make sure that the product of maximum priority values dooes
    * not overflow a U32 */
   if ((maxTpPrio > ((U32)0xffffffff) / maxFairPrio)
         || (maxTpPrio * maxFairPrio > ((U32)-1) / maxSvcPrio))
   {
      /*RLOG_ARG0(L_ERROR,DBG_CELLID,cell->cellId, 
               "rgSCHEnbPfsDlCfg(): Priority values too large");*/
     /* ccpu00117052 - MOD - Passing double pointer
      for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(inst,
         (Data**)(&(rgSchCb[inst].rgSchEnbPfsDl)), (sizeof(RgSchEnbPfsDl)));
      RETVALUE(RFAILED);
   }

   minPrio = (minTpPrio * minFairPrio * minGbrPrio)/
              pfsDl->prioScaleFact;

   maxPrio = (maxTpPrio * maxFairPrio * maxGbrPrio)/
              pfsDl->prioScaleFact;

   rgSCHPfsFillRange(&pfsDl->ranges.gbrRange, minPrio, maxPrio,
                                       RG_SCH_PFS_DL_NUM_GBR_QUEUES);
   rgSCHPfsFillRange(&pfsDl->ranges.mbrRange, minPrio, maxPrio,
                                       RG_SCH_PFS_DL_NUM_MBR_QUEUES);
   
   pfsDl->maxPrioValGbr = maxPrio;
  
   /* SRB is set to highest priority, corresponding to QCI5 */ 
   maxPrio = (maxTpPrio * maxFairPrio * dlPfsCfg->qciWgt[4] * rgSchPfsQciPdbInfo[4]. \
              pdbPrioWgt[rgSchPfsQciPdbInfo[4].maxNmbPdbLvls - 1])/
              pfsDl->prioScaleFact;

   pfsDl->maxSrbDrb0PrioVal = maxPrio;
    
   minPrio = (minTpPrio * minFairPrio * minAmbrPrio)/
              pfsDl->prioScaleFact;
   maxPrio = (maxTpPrio * maxFairPrio * maxAmbrPrio )/
              pfsDl->prioScaleFact;

   rgSCHPfsFillRange(&pfsDl->ranges.ambrRange, minPrio, maxPrio,
                                       RG_SCH_PFS_DL_NUM_AMBR_QUEUES);
   pfsDl->maxPrioValAmbr = maxPrio;

   /* Initialize total Cell count to 0 */
   pfsDl->remCellCnt = 0;
   /* Initializes the max PRB usage after which Flow 
      cntrol can be triggered */  
   //RgSchPfsUpdMaxPrbCnt(cell);
   cmLListInit(&(pfsDl->prioChngLcLst));
   RETVALUE(ROK);
}

/**
 * @brief Cell reconfiguration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlCellRecfg
 *
 *     Processing Steps:
 *      - [NONE - no reconfig for PFS]
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @param[in]  RgrCellRecfg      *recfg
 *  @param[out] RgSchErrInfo      *err
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlCellRecfg
(
RgSchCellCb     *cell,
RgrCellRecfg    *recfg,
RgSchErrInfo    *err
)
#else
PUBLIC S16 rgSCHPfsDlCellRecfg(cell, recfg, err)
RgSchCellCb     *cell;
RgrCellRecfg    *recfg;
RgSchErrInfo    *err;
#endif
{
   /* No reconfig for PFS, so just return ROK */
   UNUSED(cell);
   UNUSED(recfg);
   UNUSED(err);
   TRC2(rgSCHPfsDlCellRecfg);

   RETVALUE(ROK);
}


/**
 * @brief Cell deletion for PFS
 *
 * @details
 *
 *     Function : rgSCHEnbPfsDlDel
 *
 *     Processing Steps:
 *      - Free PFS related information eNB.
 *      - [ Nothing else needs to be done.
 *        Common modules would take care of deleting
 *        each UE in the cell, during which time PFS
 *        shall be called for UE deletion. ]
 *
 *  @param[in]  Inst       *inst
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHEnbPfsDlDel
(
Inst              inst
)
#else
PUBLIC Void rgSCHEnbPfsDlDel()
Inst              inst
#endif
{
   RgSchEnbPfsDl *pfsDl = (RgSchEnbPfsDl *)rgSchCb[inst].rgSchEnbPfsDl;
   TRC2(rgSCHEnbPfsDlDel);

   if (pfsDl == NULLP)
   {
      RETVOID;
   }
   /* ccpu00117052 - MOD - Passing double pointer
   for proper NULLP assignment*/
   rgSCHUtlFreeSBuf(inst,
      (Data**) (&(rgSchCb[inst].rgSchEnbPfsDl)), (sizeof(RgSchEnbPfsDl)));
   RETVOID;
}
/**
 * @brief Cell deletion for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlCellDel
 *
 *     Processing Steps:
 *      - Free PFS related information per cell.
 *      - [ Nothing else needs to be done.
 *        Common modules would take care of deleting
 *        each UE in the cell, during which time PFS
 *        shall be called for UE deletion. ]
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlCellDel
(
RgSchCellCb       *cell
)
#else
PUBLIC Void rgSCHPfsDlCellDel(cell)
RgSchCellCb       *cell;
#endif
{
   RgSchCmnCell    *cmnCell = (RgSchCmnCell *)(cell->sc.sch);
   RgSchPfsDlCell  *pfsCell = (RgSchPfsDlCell *)(cmnCell->dl.schSpfc); 
   U8              numSamples;
   TRC2(rgSCHPfsDlCellDel);

   if (pfsCell == NULLP)
   {
      RETVOID;
   }

   if(pfsCell->prbUsage)
   {
      numSamples = RG_SCH_PFS_DL_PRB_USE_PRD/RG_SCH_PFS_DL_PRB_SAMPLE_SIZE;

      rgSCHUtlFreeSBuf(cell->instIdx,
          (Data**)&pfsCell->prbUsage, (sizeof(U16) * numSamples));
   }

   /* ccpu00117052 - MOD - Passing double pointer
   for proper NULLP assignment*/
   rgSCHUtlFreeSBuf(cell->instIdx,
      (Data**)(&(cmnCell->dl.schSpfc)), (sizeof(RgSchPfsDlCell)));
   RETVOID;
}

/**
 * @brief Dl Harq Entity initialization for PFS 
 *
 * @details
 *
 *     Function : rgSCHPfsDlUeHqEntInit
 *
 *     Processing Steps:
 *      - Create PFS related information per Harq Entity
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlUeHqEntInit
(
RgSchCellCb      *cell,
RgSchDlHqEnt     *hqEnt
)
#else
PUBLIC S16 rgSCHPfsDlUeHqEntInit(cell, hqEnt)
RgSchCellCb      *cell;
RgSchDlHqEnt     *hqEnt;
#endif
{
   S16                 ret;
   S16                 idx;

   TRC2(rgSCHPfsDlUeHqEntInit);

   /* Alloc and init sched specific info for each proc */
   ret = rgSCHUtlAllocSBuf(cell->instIdx, (Data**)&hqEnt->sch,
         (hqEnt->numHqPrcs * sizeof(RgSchPfsDlHqProc)));
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
   for (idx = 0; idx < hqEnt->numHqPrcs; ++idx)
   {
      RgSchDlHqProcCb    *proc = &hqEnt->procs[idx];
      RgSchCmnDlHqProc   *cmnProc = (RgSchCmnDlHqProc *)proc->sch;
      cmnProc->schSpfc = &((RgSchPfsDlHqProc *)hqEnt->sch)[idx];
      /* ueRetxLnk.node and prioLnk.node indicate presence
       * in list and so are not set here */
   }
   
   RETVALUE(ROK);
}

/**
 * @brief UE configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlUeCfg
 *
 *     Processing Steps:
 *      - Create the pfsUeCb
 *      - Validate and update configured values
 *      - [UE specific refresh timer actions to happen
 *        as part of common modules]
 *      - Allocate and initialise scheduler specific info
 *        for each HARQ proc
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgrUeCfg         *cfg
 *  @param[out] RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlUeCfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrUeCfg         *cfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsDlUeCfg(cell, ue, cfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgrUeCfg         *cfg;
RgSchErrInfo     *err;
#endif
{
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchCmnDlUe       *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchPfsDlUe       *pfsUe;

   UNUSED(cfg);
   UNUSED(err);

   TRC2(rgSCHPfsDlUeCfg);


   if (rgSCHUtlAllocSBuf(cell->instIdx,
            (Data**)&cmnUe->schSpfc, (sizeof(RgSchPfsDlUe))) != ROK)
   {
      RETVALUE(RFAILED);
   }

   pfsUe = (RgSchPfsDlUe *)cmnUe->schSpfc;
   /* Placing UE into timing queue done by common */
   pfsUe->cqi     = cmnUe->mimoInfo.cwInfo[0].cqi;
   pfsUe->cqiPrio = rgSCHPfsDlGetTpPrio(pfsDl, RG_SCH_PFS_DL_MAX_ITBS);
   pfsUe->retxLnk.node = (PTR)ue;
   RLOG_ARG3(L_DEBUG,DBG_CELLID,cell->cellId,"UEID:%d cqi(%d) "
            "ambrCfgd(%lu)", ue->ueId, pfsUe->cqi, ue->dl.ambrCfgd);

   /* Fix : Updating PFS to start prio with highest possible value
               and diminishing prio val updates from there on */
   if(cell->cellId == ue->cell->cellId)
   {   
      if (rgSCHUtlAllocSBuf(cell->instIdx,
               (Data**)&pfsUe->cmnParam, (sizeof(RgSchPfsUeCmn))) != ROK)
      {
         rgSCHUtlFreeSBuf(cell->instIdx, 
               (Data**)&cmnUe->schSpfc, (sizeof(RgSchPfsDlUe)));
         RETVALUE(RFAILED);
      }

      pfsUe->cmnParam->remAmbr = ue->dl.ambrCfgd;
      rgSCHPfsInitFracPrioInfo(&pfsUe->cmnParam->fracPrioInfo, ue->dl.ambrCfgd);

      /* Updating the fracData Rate based on AMBR. it will be used to 
       * get priority level of served data throgh a specific cell */
      pfsUe->cmnParam->fracDataRate = 
            RGSCH_CEIL(ue->dl.ambrCfgd, RG_SCH_PFS_FAIRNESS_FACTOR_LVLS);

      pfsUe->cmnParam->isUeSchd = FALSE;
   }
   else
   {
      /* memory for cmnParam structure in pfsUe is allocated only once 
       * when pfsUE is added for its primary cell. later all other 
       * secondary cells uses the primary cell cmnParam structure */
      RgSchPfsDlUe  *primPfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);
      pfsUe->cmnParam = primPfsUe->cmnParam;  
   }   

   pfsUe->totalPrbReqd = 0;
   pfsUe->totalPfsPrio = 0;
   pfsUe->totalHdrSz = 0;
   pfsUe->totalEffBo = 0;
   pfsUe->maxPfsPrio = 0;
#ifdef LTE_ADV
   pfsUe->schdSCellActCe = FALSE;
#endif
   pfsUe->toBeSchedLnk.node = (PTR)ue;
   cmLListInit(&(pfsUe->schedSvcs));
   /* Since pfsUe was memset to zero at the time of memory allocation,
    * not initialising lists. */

   RETVALUE(ROK);
}

/**
 * @brief UE reconfiguration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlUeRecfg
 *
 *     Processing Steps:
 *      - [Not taking updated AMBR now;
 *        allowing current refresh cycle to misbehave]
 *
 *  @param[in]   RgSchCellCb      *cell
 *  @param[in]   RgSchUeCb        *ue
 *  @param[in]   RgrUeRecfg       *recfg
 *  @param[out]  RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlUeRecfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrUeRecfg       *recfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsDlUeRecfg(cell, ue, recfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgrUeRecfg       *recfg;
RgSchErrInfo     *err;
#endif
{
   CmLListCp      *cp;
   RgSchEnbPfsDl  *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(cell);
   RgSchPfsDlUe   *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   CmLList        *lnk;
   RgSchCmnDlUe   *cmnUe = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchDlHqEnt   *hqEnt = RG_SCH_CMN_GET_UE_HQE(ue, cell);

   UNUSED(err);

   if ((recfg->ueRecfgTypes & RGR_UE_QOS_RECFG) &&
         (recfg->ueQosRecfg.ambrPres))
   {      
      /* Updating the fracData Rate based on AMBR. it will be used to 
       * get priority level of served data throgh a specific cell */
      pfsUe->cmnParam->fracDataRate = 
         RGSCH_CEIL(ue->dl.ambrCfgd, RG_SCH_PFS_FAIRNESS_FACTOR_LVLS); 

      cp = &pfsUe->cmnParam->cfgAmbrLst;
      for (lnk = cp->first; lnk; lnk = lnk->next)
      {
         RgSchDlLcCb        *lc    = (RgSchDlLcCb *)lnk->node;
         RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
         /*  For GBR LCs, LcCfg would update this field */
         pfsLc->initMaxBo4FlowCtrl = (ue->dl.ambrCfgd * pfsLc->rcvryDurFlowCtrl)/
            (RG_SCH_CMN_REFRESH_TIME*10); 
      }
   }
   if ((rgSchCb[cell->instIdx].rgrSchedEnbCfg.accsMode == RGR_CELL_ACCS_HYBRID) &&
         (recfg->ueRecfgTypes & RGR_UE_CSG_PARAM_RECFG))
   {
      RgSchDlLcCb    *lc;
      RgSchPfsDlLc   *pfsLc;
      U8             qId;

      if (!RG_SCH_CMN_DL_IS_UE_ACTIVE(ue))
      {
         RETVALUE(ROK);
      }
      if (pfsUe->cmnParam->ambrSvc)
      {
         lc = pfsUe->cmnParam->ambrSvc;
         pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc); 
         qId = rgSCHPfsDlGetQId(pfsLc,&pfsEnbDl->ranges.ambrRange,
               pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_AMBR_QUEUES-1);
         rgSCHPfsDlLcRmvFrmPrioQ(pfsEnbDl, pfsUe, pfsLc);   
         RGSCH_PFS_AMBR_ARRAY_BOUND_CHECK(0, pfsEnbDl, qId, ue);
         rgSCHPfsAddDlLcToAmbrLst(pfsEnbDl,ue, pfsLc, qId);
         pfsLc->qId = qId;
      }
      /* GBR related updates */
      cp = &pfsUe->cmnParam->cfgGbrLst;
      for (lnk = cp->first; lnk; lnk = lnk->next)
      {
         lc = (RgSchDlLcCb *)lnk->node;
         pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
         rgSCHPfsDlLcRmvFrmPrioQ(pfsEnbDl, pfsUe, pfsLc);
         if (pfsLc->remGbr)
         {
            rgSCHPfsDlLcAddToGbrQ(pfsEnbDl, ue, pfsLc, TRUE, 0);
         }
         else if (pfsLc->remDeltaMbr)
         {
            rgSCHPfsDlLcAddToMbrQ(pfsEnbDl, ue, pfsLc, TRUE, 0);
         }
      }
   }

   /* Discarding TB2's context from scheduling Queues.
    * Since TB2 transmission needs signalling using 
    * TM specific formats. And since during this transient
    * period of UE TM Recfg, SCH always uses Format 1A,
    * the TB2s are discarded. */
   if (cmnUe->mimoInfo.forceTD & RG_SCH_CMN_TD_TXMODE_RECFG)
   {
      /* If HqP is in retx queue only for TB2 retx scheduling
       * then remove the harp proc from retx Queue */

      /* If Hqp is in retx queue for retx allocation of 
       * both TB1 and TB2, then reset TB2's state as ACKED */
      RgSchDlHqProcCb    *hqP;
      Pst                pst;
      RgInfRlsHqInfo     *rlsHqBufs = &(cell->rlsHqArr[cell->crntHqIdx]);
      U8                 i;

      /* Prepare TB2 release information to be sent to MAC */
      rlsHqBufs->numUes = 0;
      for(i = 0; i < hqEnt->numHqPrcs; i++)
      {
         hqP = &hqEnt->procs[i];
         rlsHqBufs->ueHqInfo[rlsHqBufs->numUes].rnti = ue->ueId;
         rlsHqBufs->ueHqInfo[rlsHqBufs->numUes].hqProcId = hqP->procId;
         if (hqP->tbInfo[1].state == HQ_TB_NACKED)
         {
            if (hqP->tbInfo[0].state != HQ_TB_NACKED)
            {
               /* Remove the HqP from retx Queue.
                  Release HqP.*/
               rgSCHPfsDlProcRmvFrmRetx(cell, ue, hqP);
            }
            rgSCHDhmRlsHqpTb(hqP, 1, TRUE);
            rlsHqBufs->ueHqInfo[rlsHqBufs->numUes].tbId[0] = 2;
            rlsHqBufs->ueHqInfo[rlsHqBufs->numUes].numOfTBs = 1;
         }
         rlsHqBufs->numUes++;
      }
      /* Send the hqProc list for MAC to clear TB1 contents */
      if (rlsHqBufs->numUes)
      {
         rgSCHUtlGetPstToLyr(&pst, &rgSchCb[cell->instIdx], cell->macInst);
         RgSchMacRlsHq (&pst, rlsHqBufs);
      }
   }
   RETVALUE(ROK);
}

#ifdef LTE_ADV
/**
 * @brief UE configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsSCellDlUeCfg
 *
 *     Processing Steps:
 *      - Create PFS related information per UE.
 *      - Initialize signalling and data lists.
 *
 *  @param[in]  RgrSchCellCb     *sCell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsSCellDlUeCfg
(
RgSchCellCb      *sCell,
RgSchUeCb        *ue,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsSCellDlUeCfg(sCell, ue, err)
RgSchCellCb      *sCell;
RgSchUeCb        *ue;
RgSchErrInfo     *err;
#endif
{
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(sCell);
   RgSchCmnDlUe       *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,sCell);
   RgSchPfsDlUe       *pfsUe;
   RgSchPfsDlUe       *primPfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);
   U32                lcId = 0;

   UNUSED(err);

   TRC2(rgSCHPfsSCellDlUeCfg);

   if (rgSCHUtlAllocSBuf(sCell->instIdx,
            (Data**)&cmnUe->schSpfc, (sizeof(RgSchPfsDlUe))) != ROK)
   {
      RETVALUE(RFAILED);
   }

   pfsUe = (RgSchPfsDlUe *)cmnUe->schSpfc;
   /* Placing UE into timing queue done by common */
   pfsUe->cqi     = cmnUe->mimoInfo.cwInfo[0].cqi;
   pfsUe->cqiPrio = rgSCHPfsDlGetTpPrio(pfsDl, RG_SCH_PFS_DL_MAX_ITBS);
   pfsUe->retxLnk.node = (PTR)ue;

   /* memory for cmnParam structure in pfsUe is allocated only once 
    * when pfsUE is added for its primary cell. later all other 
    * secondary cells uses the primary cell cmnParam structure */
   pfsUe->cmnParam = primPfsUe->cmnParam;

   pfsUe->totalPrbReqd = 0;
   pfsUe->totalPfsPrio = 0;
   pfsUe->totalHdrSz = 0;
   pfsUe->totalEffBo = 0;
   pfsUe->maxPfsPrio = 0;
   pfsUe->toBeSchedLnk.node = (PTR)ue;
   cmLListInit(&(pfsUe->schedSvcs));
   /* Since pfsUe was memset to zero at the time of memory allocation,
    * not initialising lists. */
   for (lcId = 0; lcId < RGSCH_MAX_LC_PER_UE;lcId++)
   {
      if (ue->dl.lcCb[lcId])
      {
         rgSCHPfsDlLcCfg(sCell, ue, ue->dl.lcCb[lcId], NULLP, err);
      }
   }
#ifdef RG_PFS_STATS
   ue->pfsStats.isCaUe = TRUE;
#endif

   RETVALUE(ROK);
}

/**
 * @brief UE configuration for Round Robin
 *
 * @details
 *
 *     Function : rgSCHPfsSCellDlUeDel
 *
 *     Processing Steps:
 *      - Delete PFS SCell UE Record.
 *
 *  @param[in]  RgSchUeCellInfo  *sCellInfo
 *  @param[in]  RgSchUeCb        *ue
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsSCellDlUeDel
(
 RgSchUeCellInfo *sCellInfo,
 RgSchUeCb       *ue
)
#else
PUBLIC S16 rgSCHPfsSCellDlUeDel(sCellInfo, ue)
 RgSchUeCellInfo *sCellInfo;
 RgSchUeCb       *ue;
#endif
{
   RgSchCmnUe     *schCmnUe = sCellInfo->sch;
   U32            lcId = 0;

   TRC2(rgSCHPfsSCellDlUeDel);

   for (lcId = 0; lcId < RGSCH_MAX_LC_PER_UE; lcId++)
   {
      if (ue->dl.lcCb[lcId])
      {
         rgSCHPfsDlLcDel(sCellInfo->cell, ue, ue->dl.lcCb[lcId]);
      }
   }
   rgSCHUtlFreeSBuf(sCellInfo->cell->instIdx,
         (Data**)(&(schCmnUe->dl.schSpfc)), (sizeof(RgSchPfsDlUe)));

   RETVALUE(ROK);
}

/**
 * @brief Scell Deactivation function for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlSCellDeactv
 *
 *     Processing Steps:
 *      - Rearrange the LC favCell lst is required.
 *
 *  @param[in]  RgSchUeCellInfo  *sCellInfo
 *  @param[in]  RgSchUeCb        *ue
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlSCellDeactv
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue
)
#else
PUBLIC S16 rgSCHPfsDlSCellDeactv(cell, ue)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
#endif
{
   RgSchEnbPfsDl         *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(cell);
   RgSchPfsDlUe          *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   RgSchPfsDlLc          *pfsLc;
   RgSchCellCb           *favCell;
   CmLList               *node  = NULLP;
   U8                    favCellIdx = 0;

   TRC2(rgSCHPfsDlSCellDeactv); 

   node = pfsUe->cmnParam->cfgGbrLst.first;
   while(node)
   {
      RgSchDlLcCb   *lc = (RgSchDlLcCb *) node->node; 
      CmLList       *cellNode;
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      cellNode = pfsLc->cellFavLst.first;
      favCell = (RgSchCellCb *)cellNode->node;
      favCellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(favCell)];

      /* If favcell has got deactivated then need to recalcualte the 
       * PFS priority and Q position based on next best cell */
      if(favCell == cell)
      {
          RgSchCellCb   *nxtFavCell = (RgSchCellCb *)cellNode->next;
          U8            cellIdx   = ue->cellIdToCellIdxMap\
                                    [RG_SCH_CELLINDEX(nxtFavCell)];

          if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
          {
             pfsLc->pfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
                   pfsEnbDl->tbls.fairPrios[pfsUe->cmnParam->fracPrioInfo.fracPrioLvls] *
                   (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
                (pfsEnbDl->prioScaleFact); 
          }
          else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
          {
             pfsLc->pfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
                   pfsEnbDl->tbls.fairPrios[pfsLc->fracPrioInfo.fracPrioLvls] *
                   (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
                (pfsEnbDl->prioScaleFact); 
          } 

          /* Updating the priority Q only if LC is already added in some Q
           * it means LC has some data to serve */
          if(pfsLc->prioLstCp)
          {   
             rgSchPfsUpdPrioQ(cell, ue, pfsLc);
          }

          /* Resetting the cell Priority of this LC to 0 and adding this 
           * cell in favCell list at the end */
          pfsLc->cellSpfc[favCellIdx].cellPrio = 0;

          cmLListDelFrm(&pfsLc->cellFavLst, 
                &(pfsLc->cellSpfc[favCellIdx].favCellLnk));
          cmLListAdd2Tail(&pfsLc->cellFavLst, 
                &(pfsLc->cellSpfc[favCellIdx].favCellLnk));
      }   
      node = node->next;
   }

   node = pfsUe->cmnParam->cfgAmbrLst.first;
   while(node)
   {
      RgSchDlLcCb   *lc = (RgSchDlLcCb *) node->node; 
      CmLList       *cellNode;
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      cellNode = pfsLc->cellFavLst.first;
      favCell = (RgSchCellCb *)cellNode->node;
      favCellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(favCell)];

      /* If favcell has got deactivated then need to recalcualte the 
       * PFS priority and Q position based on next best cell */
      if(favCell == cell)
      {
          RgSchCellCb   *nxtFavCell = (RgSchCellCb *)cellNode->next;
          U8            cellIdx   = ue->cellIdToCellIdxMap\
                                    [RG_SCH_CELLINDEX(nxtFavCell)];

          if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
          {
             pfsLc->pfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
                   pfsEnbDl->tbls.fairPrios[pfsUe->cmnParam->fracPrioInfo.fracPrioLvls] *
                   (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
                (pfsEnbDl->prioScaleFact); 
          }
          else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
          {
             pfsLc->pfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
                   pfsEnbDl->tbls.fairPrios[pfsLc->fracPrioInfo.fracPrioLvls] *
                   (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
                (pfsEnbDl->prioScaleFact); 
          } 

          /* Updating the priority Q only if LC is already added in some Q
           * it means LC has some data to serve */
          if(pfsLc->prioLstCp)
          {   
             rgSchPfsUpdPrioQ(cell, ue, pfsLc);
          }

          /* Resetting the cell Priority of this LC to 0 and adding this 
           * cell in favCell list at the end */
          pfsLc->cellSpfc[favCellIdx].cellPrio = 0;

          cmLListDelFrm(&pfsLc->cellFavLst, 
                &(pfsLc->cellSpfc[favCellIdx].favCellLnk));
          cmLListAdd2Tail(&pfsLc->cellFavLst, 
                &(pfsLc->cellSpfc[favCellIdx].favCellLnk));
      }   
      node = node->next;
   }
   RETVALUE(ROK);
}   

/**
 * @brief Scell Activation function for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlSCellActv
 *
 *     Processing Steps:
 *      - Rearrange the LC favCell lst if required.
 *
 *  @param[in]  RgSchUeCellInfo  *sCellInfo
 *  @param[in]  RgSchUeCb        *ue
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlSCellActv
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue
)
#else
PUBLIC S16 rgSCHPfsDlSCellActv(cell, ue)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
#endif
{
   RgSchPfsDlUe          *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   RgSchPfsDlLc          *pfsLc;
   U8                    cellIdx = ue->cellIdToCellIdxMap\
                                   [RG_SCH_CELLINDEX(cell)];      
   RgSchPfsCellSpfcDlLc  *cellSpfcDlLc;
   CmLList               *node  = NULLP;
   CmLList               *cellNode;

   TRC2(rgSCHPfsDlSCellActv);

   node = pfsUe->cmnParam->cfgGbrLst.first;
   while(node)
   {
      RgSchDlLcCb   *lc = (RgSchDlLcCb *) node->node; 
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      cellSpfcDlLc  = &(pfsLc->cellSpfc[cellIdx]);

      /* deleting it from its old postion and will add into the favCell list
       * according to its priority */
      cmLListDelFrm(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));

      CM_LLIST_FIRST_NODE(&pfsLc->cellFavLst, cellNode);

      while(cellNode)
      {
         RgSchCellCb *cellCb = (RgSchCellCb *)(cellNode->node);
         U8          tempIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cellCb)];                  

         if(ue->cellInfo[tempIdx]->sCellState != RG_SCH_SCELL_ACTIVE)
         {
            cmLListInsCrnt(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));
            break;
         }   
         CM_LLIST_NEXT_NODE(&pfsLc->cellFavLst, cellNode);
      }

      if(!cellNode)
      {
         cmLListAdd2Tail(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));
      }   

      node = node->next;
   }

   node = pfsUe->cmnParam->cfgAmbrLst.first;
   while(node)
   {
      RgSchDlLcCb   *lc = (RgSchDlLcCb *) node->node; 
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      cellSpfcDlLc  = &(pfsLc->cellSpfc[cellIdx]);

      /* deleting it from its old postion and will add into the favCell list
       * according to its priority */
      cmLListDelFrm(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));

      CM_LLIST_FIRST_NODE(&pfsLc->cellFavLst, cellNode);

      while(cellNode)
      {
         RgSchCellCb *cellCb = (RgSchCellCb *)(cellNode->node);
         U8          tempIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cellCb)];                  

         if(ue->cellInfo[tempIdx]->sCellState != RG_SCH_SCELL_ACTIVE)
         {
            cmLListInsCrnt(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));
            break;
         }   
         CM_LLIST_NEXT_NODE(&pfsLc->cellFavLst, cellNode);
      }

      if(!cellNode)
      {
         cmLListAdd2Tail(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));
      }   

      node = node->next;
   }

   RETVALUE(ROK);
}   
#endif

/**
 * @brief Dl Harq Entity deletion for Round Robin
 *
 * @details
 *
 *     Function : rgSCHPfsDlUeHqEntDeInit 
 *
 *     Processing Steps:
 *      - Free PFS related information per Harq Entity
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchDlHqEnt     *hqE 
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlUeHqEntDeInit 
(
RgSchCellCb      *cell,
RgSchDlHqEnt     *hqE
)
#else
PUBLIC S16 rgSCHPfsDlUeHqEntDeInit(cell, hqE)
RgSchCellCb      *cell;
RgSchDlHqEnt     *hqE;
#endif
{
   TRC2(rgSCHPfsDlUeHqEntDeInit);

   if (hqE->sch != NULLP)
   {
      rgSCHUtlFreeSBuf(cell->instIdx, (Data**)(&(hqE->sch)), 
            (hqE->numHqPrcs * sizeof(RgSchPfsDlHqProc)));
   }

   RETVALUE(ROK);
}

/**
 * @brief UE delete for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlUeDel
 *
 *     Processing Steps:
 *     - Free scheduler specific HARQ proc info for each proc
 *     - Free UE sched info
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @param[in]  RgSchUeCb         *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlUeDel
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHPfsDlUeDel(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   RgSchCmnDlUe        *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchDlHqEnt        *hqEnt = RG_SCH_CMN_GET_UE_HQE(ue, cell);
   TRC2(rgSCHPfsDlUeDel);

   if (cmnUe->schSpfc == NULLP)
   {
      RETVOID;
   }


   if ((hqEnt != NULLP) && (hqEnt->sch != NULLP))
   {
      rgSCHPfsDlResetProcs(cell, ue);
   }

   /* No need to free logical channels from queues or to delete
    * their scheduler specific info since lc del would get
    * called as part of UE del */

   if(cell->cellId == ue->cell->cellId)
   {   
      RgSchPfsDlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
      rgSCHUtlFreeSBuf(cell->instIdx, 
            (Data**)&(pfsUe->cmnParam), (sizeof(RgSchPfsUeCmn)));
   }

   rgSCHUtlFreeSBuf(cell->instIdx,
      (Data**)(&(cmnUe->schSpfc)), (sizeof(RgSchPfsDlUe)));

   RETVOID;
}

/**
 * @brief Function to update Flow control information 
 *        to be sent to MAC.
 *
 * @details
 *
 *     Function: rgSCHPfsDlFillFlowCntrlInfo
 *
 *              update Flow control information 
 *
 *     Invoked by: 
 *         SCHD
 *
 *     Processing Steps:
 *           
 *  @param[in] RgSchCellCb       *cell
               RgInfSfAlloc    *sfAlloc;
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlFillFlowCntrlInfo
(
RgSchCellCb    *cell,
RgInfSfAlloc   *sfAlloc
)
#else
PUBLIC S16 rgSCHPfsDlFillFlowCntrlInfo(cell,sfAlloc)
RgSchCellCb    *cell;
RgInfSfAlloc   *sfAlloc;
#endif
{
   U32                ueIdx;
   U32                lcIdx;
   RgSchUeCb          *ue;
   CmLList            *lcNode;
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   CmLList            *ueNode = pfsDl->flowCntrlUeLst.first;

   for (ueIdx = 0; (ueIdx < RGINF_MAX_NUM_UE_PER_TTI);ueIdx++)
   {
      if (ueNode == NULLP)
      {
         /* No more entries in the flowCntrlUelst */
         break;
      }
      ue     = (RgSchUeCb *)ueNode->node;
      ueNode = ueNode->next;

      sfAlloc->flowCntrlInfo.ueFlowCntrlInfo[ueIdx].ueId = ue->ueId;
      lcNode = ue->flowCntrlLcLst.first;

      for (lcIdx = 0; lcIdx < RGINF_MAX_NUM_DED_LC; lcIdx++)
      {
         if (lcNode == NULLP)
         {
            /* No more LCs for this UEs in the flowCntrlLcLst */
            break;
         }

         RgSchDlLcCb    *lcCb = (RgSchDlLcCb *)lcNode->node;
         RgSchPfsDlLc   *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lcCb);

         lcNode = lcNode->next;
         /* Fill the sfAlloc information to be sent to MAC */
         sfAlloc->flowCntrlInfo.ueFlowCntrlInfo[ueIdx].lcInfo[lcIdx].lcId        = lcCb->lcId;
         sfAlloc->flowCntrlInfo.ueFlowCntrlInfo[ueIdx].lcInfo[lcIdx].pktAdmitCnt = pfsLc->pktAdmitCnt;
         sfAlloc->flowCntrlInfo.ueFlowCntrlInfo[ueIdx].lcInfo[lcIdx].maxBo4FlowCtrl = pfsLc->maxBo4FlowCtrl;
         /* Remove the LC after it is updated in the sfAlloc */
         cmLListDelFrm(&ue->flowCntrlLcLst,&lcCb->lcFlowCntrlEnt);
         lcCb->lcFlowCntrlEnt.node = NULLP;
      }
      /* Remove the UE from the flowCntrlUeLst */
      sfAlloc->flowCntrlInfo.ueFlowCntrlInfo[ueIdx].numLcs = lcIdx;

      cmLListDelFrm(&pfsDl->flowCntrlUeLst,&ue->ueFlowCntrlEnt);
      ue->ueFlowCntrlEnt.node = NULLP;
   }
   sfAlloc->flowCntrlInfo.numUes = ueIdx;
   RETVALUE(ROK);
}

/**
 * @brief UE reset for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlUeReset
 *
 *     Processing Steps:
 *      - Remove UEs from whichever queues its LCs might be
 *        present in. B0s set to zero by the common module.
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlUeReset
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHPfsDlUeReset(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   S16                 idx;
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   TRC2(rgSCHPfsDlUeReset);

   rgSCHPfsDlResetProcs(cell, ue);
   
   if(cell->cellId == ue->cell->cellId)
   {   
      if(ue->ueFlowCntrlEnt.node != NULLP)
      {
         cmLListDelFrm(&pfsDl->flowCntrlUeLst,&ue->ueFlowCntrlEnt);
         ue->ueFlowCntrlEnt.node = NULLP;
      }

      /* Could use a list of LCs that are in queues. This one could
       * navigate now to reset their BOs and take them out
       * of queues. 
       * BUT, for LCs not in queues, need to
       * reset BOs (they may not be in queues due to effBo being
       * zero while BO is still positive). So just go through
       * all LCs. */
      for (idx = 0; idx < RGSCH_MAX_LC_PER_UE; ++idx)
      {
         RgSchDlLcCb        *lc = ue->dl.lcCb[idx];

         if (lc == NULLP)
         {
            continue;
         }
         rgSCHPfsDlBoUpdInt(cell, ue, lc, 0, 0);
      }
   }

   RETVOID;
}

/**
 * @brief LC configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlLcCfg
 *
 *     Processing Steps:
 *     - Create pfsDlLc info and initialise vars
 *     - Add to cfgGbrLst if this is a gbr service
 *     - Add to cfgAmbrLst if this is an AMBR (barring
 *       DRB0) service
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchDlLcCb      *lc
 *  @param[in]  RgrLchCfg        *cfg
 *  @param[out] RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlLcCfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchDlLcCb      *lc,
RgrLchCfg        *cfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsDlLcCfg(cell, ue, lc, cfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchDlLcCb      *lc;
RgrLchCfg        *cfg;
RgSchErrInfo     *err;
#endif
{
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   RgSchCmnDlSvc      *cmnLc = (RgSchCmnDlSvc *)lc->sch;
   RgSchPfsDlLc       *pfsLc;
   U8                 cellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];      

   UNUSED(err);
   TRC2(rgSCHPfsDlLcCfg);

   if(cell->cellId == ue->cell->cellId)
   { 
      if (rgSCHUtlAllocSBuf(cell->instIdx,
               (Data**)&cmnLc->schSpfc, (sizeof(RgSchPfsDlLc))) != ROK)
      {
         RETVALUE(RFAILED);
      }
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      pfsLc->prioLnk.node = (PTR)lc;
      pfsLc->svcPrioLnk.node = (PTR)lc;
      pfsLc->pdbQLnk.node = (PTR)lc;

      pfsLc->qci = cfg->dlInfo.dlQos.qci;
      pfsLc->pdb = rgSchPfsQciPdbInfo[pfsLc->qci-1].pdb; 
      pfsLc->pdbLvlSz = rgSchPfsQciPdbInfo[pfsLc->qci-1].pdbLvlSz; 
      pfsLc->lastPdbLvl = rgSchPfsQciPdbInfo[pfsLc->qci-1].maxNmbPdbLvls - 1; 

      pfsLc->flowCtrlPdbLimit = rgSchPfsQciPdbInfo[pfsLc->qci-1].lastLvl4FullFlow; 
      pfsLc->rcvryDurFlowCtrl = RGSCH_MAX(pfsLc->pdbLvlSz, RG_SCH_PFS_FCTRL_MIN_RCVRY_TIME); 
      /*pfsLc->inQLnk.node = (PTR)lc;*/
      /* ambrLnk.node should be NULLP. It is set only when lc
       * is in pfs UE's AMBR list, which happens when it has
       * non-zero BO. */

      //if (lc->lcId == 1 || lc->lcId == 2)
      if(lc->lcType == CM_LTE_LCH_DCCH)
      {
         /* For SRBs svcPrio is set same as QCI5s */
         pfsLc->svcPrio    = rgSchPfsDlGetSvcPrio(pfsDl, 5);
      }
      else
      {
         pfsLc->svcPrio    = rgSchPfsDlGetSvcPrio(pfsDl, cmnLc->qci);
      } 
      /* Fix : Updating PFS to start prio with highest possible value
         and diminishing prio val updates from there on. */

      pfsLc->statusScheduled = TRUE;

      if (RG_SCH_CMN_DL_SVC_IS_GBR(lc))
      {
         pfsLc->pfsPrio = pfsDl->maxPrioValGbr;
         pfsLc->gbr           = cmnLc->gbr;
         pfsLc->remGbr        = pfsLc->gbr;
         pfsLc->deltaMbr      = (cmnLc->mbr > cmnLc->gbr)?(cmnLc->mbr - cmnLc->gbr):0;
         pfsLc->remDeltaMbr   = pfsLc->deltaMbr;
         pfsLc->lcType        = RG_SCH_PFS_LC_TYPE_GBR;
         pfsLc->cfgLcLnk.node = (PTR)lc;
         cmLListAdd2Tail(&pfsUe->cmnParam->cfgGbrLst, &pfsLc->cfgLcLnk);
         /* Fix : Updating PFS to start prio with highest possible value
            and diminishing prio val updates from there on */
         rgSCHPfsInitFracPrioInfo(&pfsLc->fracPrioInfo, pfsLc->gbr); 
         pfsLc->initMaxBo4FlowCtrl = (cmnLc->mbr * pfsLc->rcvryDurFlowCtrl)/
                                     (RG_SCH_CMN_REFRESH_TIME*10); 
         /* Updating the fracData Rate based on MBR. it will be used to 
          * get priority level of served data throgh a specific cell 
          * while creating favCellList */
         pfsLc->fracDataRate = 
            RGSCH_CEIL(cmnLc->mbr, RG_SCH_PFS_FAIRNESS_FACTOR_LVLS);
      }
      else if(lc->lcType == CM_LTE_LCH_DCCH)
      {
         pfsLc->lcType = RG_SCH_PFS_LC_TYPE_SRB;
         pfsLc->pfsPrio = pfsDl->maxSrbDrb0PrioVal;
      }
      else if (cmnLc->qci == 5)
      {
         pfsLc->lcType = RG_SCH_PFS_LC_TYPE_DRB0;
         pfsLc->pfsPrio = pfsDl->maxSrbDrb0PrioVal;
      }
      else
      {
         pfsLc->pfsPrio = pfsDl->maxPrioValAmbr;
         pfsLc->lcType = RG_SCH_PFS_LC_TYPE_AMBR;
         pfsLc->cfgLcLnk.node = (PTR)lc;
         cmLListAdd2Tail(&pfsUe->cmnParam->cfgAmbrLst, &pfsLc->cfgLcLnk);
         pfsLc->initMaxBo4FlowCtrl = (ue->dl.ambrCfgd * pfsLc->rcvryDurFlowCtrl)/
            (RG_SCH_CMN_REFRESH_TIME*10); 
      }
      rgSchPfsResetPdbCbCntxt(cell,lc);

      pfsLc->cellFavLstUpdIdx = 0;

      pfsLc->favCellPrio = 0;
      pfsLc->favCellPrioLstCp = NULLP;

      if((pfsLc->lcType == RG_SCH_PFS_LC_TYPE_SRB) ||
         (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_DRB0)) 
      {   
         pfsLc->cellSpfc[cellIdx].favCellLnk.node = (PTR)cell;
         cmLListAdd2Tail(&(pfsLc->cellFavLst), &(pfsLc->cellSpfc[cellIdx].favCellLnk));
      }
   }
   else
   {
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   }

   pfsLc->cellSpfc[cellIdx].svccqiPrio = pfsLc->svcPrio * pfsUe->cqiPrio;
   pfsLc->cellSpfc[cellIdx].achvdFracDataRate = 0;
   pfsLc->cellSpfc[cellIdx].cellPrio = 0;
   
   if((pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR) ||
      (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR))   
   {   
      pfsLc->cellSpfc[cellIdx].favCellLnk.node = (PTR)cell;
      cmLListAdd2Tail(&(pfsLc->cellFavLst), &(pfsLc->cellSpfc[cellIdx].favCellLnk));
   }

   pfsLc->cellSpfc[cellIdx].schedSvcLnk.node = (PTR)lc; 

   RETVALUE(ROK);
}

/**
 * @brief LC re-configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlLcRecfg
 *
 *     Processing Steps:
 *      - If DL LC is re-configured
 *        - If LC type is GBR
 *          - Update gbr
 *          - Update deltaMbr
 *      - [Need not do other changes for QoS update,
 *        vars update at refresh cycle shall take
 *        care of things]
 *      - [Not supporting LC QCI which is common with other
 *        schedulers]
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchDlLcCb      *lc
 *  @param[in]  RgrLchRecfg      *recfg
 *  @param[out] RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsDlLcRecfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchDlLcCb      *lc,
RgrLchRecfg      *recfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsDlLcRecfg(cell, ue, lc, recfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchDlLcCb      *lc;
RgrLchRecfg      *recfg;
RgSchErrInfo     *err;
#endif
{
   RgSchCmnDlSvc      *cmnLc = (RgSchCmnDlSvc *)lc->sch;

   UNUSED(ue);
   UNUSED(recfg);
   UNUSED(err);
   TRC2(rgSCHPfsDlLcRecfg);

   if(cell->cellId == ue->cell->cellId)
   {   
      RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      /* Common module is not supporting QCI change, so
       * don't bother about that */

      pfsLc->qci = recfg->dlRecfg.dlQos.qci;
      pfsLc->pdb = rgSchPfsQciPdbInfo[pfsLc->qci-1].pdb; 
      pfsLc->pdbLvlSz = rgSchPfsQciPdbInfo[pfsLc->qci-1].pdbLvlSz; 
      pfsLc->lastPdbLvl = rgSchPfsQciPdbInfo[pfsLc->qci-1].maxNmbPdbLvls - 1; 
      pfsLc->flowCtrlPdbLimit = rgSchPfsQciPdbInfo[pfsLc->qci-1].lastLvl4FullFlow; 
      pfsLc->rcvryDurFlowCtrl = RGSCH_MAX(pfsLc->pdbLvlSz, RG_SCH_PFS_FCTRL_MIN_RCVRY_TIME); 

      if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
      {
         pfsLc->gbr           = cmnLc->gbr;
         pfsLc->deltaMbr      = (cmnLc->mbr > cmnLc->gbr)?(cmnLc->mbr - cmnLc->gbr):0;
         pfsLc->remDeltaMbr   = pfsLc->deltaMbr;
         pfsLc->initMaxBo4FlowCtrl = (cmnLc->mbr * pfsLc->rcvryDurFlowCtrl)/
                                     (RG_SCH_CMN_REFRESH_TIME*10); 
         /* These shall automatically be in effect in the next refresh cycle */
      }
      else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
      {
         pfsLc->initMaxBo4FlowCtrl = (ue->dl.ambrCfgd * pfsLc->rcvryDurFlowCtrl)/
            (RG_SCH_CMN_REFRESH_TIME*10); 
      }
      rgSchPfsResetPdbCbCntxt(cell,lc);
   }
   RETVALUE(ROK);
}

/**
 * @brief LC deletion for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsDlLcDel
 *
 *     Processing Steps:
 *     - Remove LC from queues if present
 *     - Delete pfsDlLc info
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchDlLcCb      *lc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlLcDel
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchDlLcCb      *lc
)
#else
PUBLIC Void rgSCHPfsDlLcDel(cell, ue, lc)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchDlLcCb      *lc;
#endif
{
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   RgSchCmnDlSvc      *cmnLc = (RgSchCmnDlSvc *)lc->sch;
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   U8                 cellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];      

   TRC2(rgSCHPfsDlLcDel);

   if (pfsLc == NULLP)
   {
      RETVOID;
   }

   if((pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR) ||
      (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR))   
   {   
      cmLListDelFrm(&(pfsLc->cellFavLst), &(pfsLc->cellSpfc[cellIdx].favCellLnk));
   }

   if(cell->cellId == ue->cell->cellId)
   {   
      if (lc->lcFlowCntrlEnt.node != NULLP)
      {
         cmLListDelFrm(&ue->flowCntrlLcLst,&lc->lcFlowCntrlEnt);
         lc->lcFlowCntrlEnt.node = NULLP;
      }
      if(pfsLc->lcPdbFbkLnk.node != NULLP)
      {
         cmLListDelFrm(&pfsDl->pdbInfo.pdbTrckLst[pfsLc->fcQIdx], &pfsLc->lcPdbFbkLnk);
         pfsLc->lcPdbFbkLnk.node = NULLP;
      } 

      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
      rgSchPfsResetPdbCbCntxt(cell,lc);
      if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
      {
         rgSCHPfsDlLcAmbrInactv(pfsDl, ue, lc);
         cmLListDelFrm(&pfsUe->cmnParam->cfgAmbrLst, &pfsLc->cfgLcLnk);
         pfsLc->cfgLcLnk.node = NULLP;
      }
      else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
      {
         cmLListDelFrm(&pfsUe->cmnParam->cfgGbrLst, &pfsLc->cfgLcLnk);
         pfsLc->cfgLcLnk.node = NULLP;
      }
      lc->schdLnk.node = NULLP;

      if((pfsLc->lcType == RG_SCH_PFS_LC_TYPE_SRB) ||
         (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_DRB0)) 
      {   
         cmLListDelFrm(&(pfsLc->cellFavLst), &(pfsLc->cellSpfc[cellIdx].favCellLnk));
      }

      /* ccpu00117052 - MOD - Passing double pointer
         for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(cell->instIdx,
            (Data**)(&(cmnLc->schSpfc)), (sizeof(RgSchPfsDlLc)));
   }
   RETVOID;
}

/**
 * @brief Indication of list of UEs which should not be
 *        scheduled
 *
 * @details
 *
 *     Function : rgSCHPfsDlInactvLstInd
 *
 *     Processing Steps:
 *      - Indication for set of UEs for which downlink
 *        scheduling should not be done.
 *        Triggers removal of logical channels of UEs
 *        from queues.
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlInactvLstInd
(
RgSchCellCb      *cell,
CmLListCp        *lst
)
#else
PUBLIC Void rgSCHPfsDlInactvLstInd(cell, lst)
RgSchCellCb      *cell;
CmLListCp        *lst;
#endif
{
   CmLList         *lnk;
   TRC2(rgSCHPfsDlInactvLstInd);

   for (lnk = lst->first; lnk; lnk = lnk->next)
   {
      RgSchUeCb       *ue = (RgSchUeCb *)lnk->node;
      rgSCHPfsDlUeInactv(cell, ue);
   }
   RETVOID;
}

/**
 * @brief Indication for an inactive (not to be scheduled) UE
 *
 * @details
 *
 *     Function : rgSCHPfsDlUeInactv
 *
 *     Processing Steps:
 *      - Triggers temporary removal of logical channels of UEs
 *        from queues.
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlUeInactv
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PRIVATE Void rgSCHPfsDlUeInactv(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   CmLList            *lnk;
   S16                 idx;
   TRC2(rgSCHPfsDlUeInactv);

   for (lnk = pfsUe->retxProcs.first; lnk; lnk = lnk->next)
   {
      RgSchDlHqProcCb    *proc = (RgSchDlHqProcCb *)lnk->node;

      /* Remove from cell retx list only, leaving it in UE retx list */
      rgSCHPfsDlProcRmvFrmCellRetx(cell, proc);
   }

   /*for (lnk = &pfsUe->inQLcLst; lnk; lnk = lnk->next)*/
   for (idx = 0; idx < RGSCH_MAX_LC_PER_UE; ++idx)
   {
      RgSchDlLcCb        *lc = ue->dl.lcCb[idx];
      RgSchPfsDlLc       *pfsLc;

      if (lc == NULLP)
      {
         continue;
      }
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
      /* Could have remembered original cell queue,
       * and put it back if BO has
       * not changed. This can be quicker, but has more
       * complexity (which might increase if reconfig
       * of certain priorities are considered).
       */
   }
   /* Fix : syed Resetting ambrSvc with ambrLst.count>0 is invalid.
    * Note: rgSCHPfsDlLcRmvFrmPrioQ() does not alter ambrLst.count. It was
    * leading to a crash during activation. */
   /*pfsUe->ambrSvc = NULLP;*/

   RETVOID;
}

/**
 * @brief Indication that a UE is allowed to be scheduled
 *
 * @details
 *
 *     Function : rgSCHPfsDlActvUeInd
 *
 *     Processing Steps:
 *      - [This is an indication for UE for which downlink
 *        scheduling can now be done, since the last
 *        time it was not allowed.]
 *      - Triggers addition of HARQ procs for which retx
 *        is pending to be added back to the cell wide
 *        retx queues.
 *      - Triggers addition of logical channels to queues
 *        when needed.
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlActvUeInd
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHPfsDlActvUeInd(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   CmLList            *lnk;
   S16                 idx;
   TRC2(rgSCHPfsDlActvUeInd);

   for (lnk = pfsUe->retxProcs.first; lnk; lnk = lnk->next)
   {
      RgSchDlHqProcCb    *proc = (RgSchDlHqProcCb *)lnk->node;

      /* Add to cell retx list only (it is already in UE retx list) */
      rgSCHPfsDlProcAddToCellRetx(cell, proc);
   }

   /*for (lnk = &pfsUe->inQLcLst; lnk; lnk = lnk->next)*/
   for (idx = 0; idx < RGSCH_MAX_LC_PER_UE; ++idx)
   {
      RgSchDlLcCb         *lc = ue->dl.lcCb[idx];
#ifdef LTEMAC_SPS 
      RgSchCmnDlUeSpsInfo *dlSpsUe = RG_SCH_CMN_SPS_GET_DL_UE(ue);
#endif

      if ((lc == NULLP)
#ifdef LTEMAC_SPS 
       || (dlSpsUe->spsSvc == lc)
#endif
    )
      {
         continue;
      }
      rgSCHPfsDlBoUpdInt(cell, ue, lc, lc->bo, 0);
   }
   /* ambrSvc shall be set correctly as part of BoUpdInt for each
    * AMBR svc */

   RETVOID;
}

/**
 * @brief Downlink CQI Indication handler
 *
 * @details
 *
 *     Function : rgSCHPfsDlCqiInd
 *
 *     Processing Steps:
 *     - If CQI priority has changed due to wideband CQI change
 *       - Update CQI component of priority (specific to UE)
 *       - [Not doing proc updates] For each of UE's non SRB retx HARQ proc
 *         - Update HARQ retx PFS priority and corresponding positions
 *           in queues
 *       - For each DTCH
 *         - Update precomputed non BO component of PFS
 *           priority (svccqiPrio)
 *       - For each DTCH in cell-wide queues
 *         - Update priority
 *         - Position in different queue if needed
 *
 *  @param[in]  RgSchCellCb      *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  TfuDlCqiRpt      *cqiInfo
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlCqiInd
(
RgSchCellCb          *cell,
RgSchUeCb            *ue,
Bool                 isPucchInfo,
Void                 *dlCqi
)
#else
PUBLIC Void rgSCHPfsDlCqiInd(cell, ue, isPucchInfo, dlCqi)
RgSchCellCb          *cell;
RgSchUeCb            *ue;
Bool                 isPucchInfo;
Void                 *dlCqi;
#endif
{
   RgSchEnbPfsDl       *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchCmnDlUe        *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchPfsDlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   U8                   iTbs;
   U32                  cqiPrio;
   CmLList             *lnk;
   Bool                prioChngd = FALSE;
   Bool                statusScheduled = TRUE;

   UNUSED(isPucchInfo);
   UNUSED(dlCqi);

   TRC2(rgSCHPfsDlCqiInd);

   /* Considering Itbs instead of CQI to include represent actual
    * channel quality */
   iTbs = ((cmnUe->mimoInfo.cwInfo[0].noLyr * cmnUe->mimoInfo.cwInfo[0].iTbs[0]) + 
          (cmnUe->mimoInfo.cwInfo[1].noLyr * cmnUe->mimoInfo.cwInfo[1].iTbs[0]))/
     (cmnUe->mimoInfo.cwInfo[0].noLyr + cmnUe->mimoInfo.cwInfo[1].noLyr);

   cqiPrio = rgSCHPfsDlGetTpPrio(pfsDl, iTbs);
   /* Considering RI and CW1's CQI */
   if(pfsDl->cfgdTpFact !=  RG_SCH_PFS_NO_TP_WEIGHT_FACTOR)
   {
      cqiPrio = RGSCH_CEIL(cqiPrio, cmnUe->mimoInfo.ri);
   }
   pfsUe->cqiPrio = cqiPrio;

   /* Update GBR/MBR LCs */
   for (lnk = pfsUe->cmnParam->cfgGbrLst.first; lnk; lnk = lnk->next)
   {
      RgSchDlLcCb       *lc = (RgSchDlLcCb *)lnk->node;
      RgSchPfsDlLc      *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      RgSchCellCb       *favCell = (RgSchCellCb *)(pfsLc->cellFavLst.first->node);     
      U8                cellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];      

      pfsLc->cellSpfc[cellIdx].svccqiPrio = pfsLc->svcPrio * cqiPrio;
      /* Updating the PFS priority of a LC only when CQI indication is received 
       * for its favCell */
      if((cell == favCell) && (pfsLc->statusScheduled == TRUE))
      {
         /* Fix : Updating PFS to start prio with highest possible value
            and diminishing prio val updates from there on */
         rgSCHPfsDlUpdPfsPrio(pfsDl, pfsLc, ue, &pfsLc->fracPrioInfo, &prioChngd);
      }   
      else
      {
         continue;
      }   

      /* Fix: Updating LC/UEs position in scheduling Queues should be
       * done only if UE is Active */
      if ((RG_SCH_CMN_DL_IS_UE_ACTIVE(ue)) && pfsLc->bo)
      {
         if (pfsLc->remGbr)
         {
            /* Takes care of updating/retaining queue */
            rgSCHPfsDlLcAddToGbrQ(pfsDl, ue, pfsLc, prioChngd, 0);
         }
         else if (pfsLc->remDeltaMbr)
         {
            /* Takes care of updating/retaining queue */
            rgSCHPfsDlLcAddToMbrQ(pfsDl, ue, pfsLc, prioChngd, 0);
         }
      }
   }

   /* Update AMBR LCs */
   for (lnk = pfsUe->cmnParam->cfgAmbrLst.first; lnk; lnk = lnk->next)
   {
      RgSchDlLcCb     *lc = (RgSchDlLcCb *)lnk->node;
      RgSchPfsDlLc    *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      U8              cellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];      

      pfsLc->cellSpfc[cellIdx].svccqiPrio = pfsLc->svcPrio * cqiPrio;

      if (pfsLc->statusScheduled != TRUE)
      {
          statusScheduled = FALSE;
      }   
   }
   if (RG_SCH_CMN_DL_IS_UE_ACTIVE(ue) && (statusScheduled == TRUE))
   {
      if (pfsUe->cmnParam->ambrSvc)
      {
         RgSchDlLcCb         *lc = pfsUe->cmnParam->ambrSvc;
         RgSchPfsDlLc        *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
         rgSCHPfsDlLcAddToAmbrQ(pfsDl, ue, pfsLc, 0);
      }
   }

   RETVOID;
}

/**
 * @brief Scheduling of UEs for TA
 *
 * @details
 *
 *     Function : rgSCHPfsDlSchedTa
 *
 *     Processing Steps:
 *     - Schedules UEs for TA
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *alloc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlSchedTa
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHPfsDlSchedTa(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   RgSchCmnDlCell       *cmnCell = RG_SCH_CMN_GET_DL_CELL(cell);
   RgSchDlSf            *sf        = alloc->dedAlloc.dedDlSf;
   CmLList              *lnk;
#ifdef LTEMAC_HDFDD
   Bool                 dlAllowed = FALSE;
#endif
   U8                   remUe; 

   TRC2(rgSCHPfsDlSchedTa);

   /* Fix: MUE_PERTTI_DL syed Limiting number of TA scheduling. Please
    * check in remUeCnt handling in oher schedulers as well. */
   if (sf->remUeCnt < cmnCell->maxUeNewTxPerTti)
   {
      remUe = sf->remUeCnt;      
   }
   else
   {
      remUe = cmnCell->maxUeNewTxPerTti;     
   }
   for (lnk = cmnCell->taLst.first; (lnk && remUe); lnk = lnk->next)
   {
      RgSchUeCb            *ue = (RgSchUeCb *)lnk->node;
#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddChkDlAllow ( cell, ue, &dlAllowed);
         if (dlAllowed == FALSE)
         {
            continue;
         }
      }
#endif
      if (rgSCHPfsDlSchedTaForUe(cell, alloc, sf, ue) != ROK)
      {
         continue;         
      }
      remUe--;
   }
   /* Fix: MUE_PERTTI_DL syed Limiting number of TA scheduling. 
    * This check is to handle both TA->RETX and RETX->TA sched order. */
   if (sf->remUeCnt < cmnCell->maxUeNewTxPerTti)
   {
      sf->remUeCnt = remUe;
   }
   else
   {
      sf->remUeCnt -=(cmnCell->maxUeNewTxPerTti - remUe);
   }
   RETVOID;
}

/**
 * @brief Scheduling of UE for TA
 *
 * @details
 *
 *     Function : rgSCHPfsDlSchedTaForUe
 *
 *     Processing Steps:
 *     - Schedules UE for TA.
 *     - This relies on the fact that TA is scheduled
 *       before anything else (even before retx), and
 *       hence does not perform checks such as if
 *       UE is already scheduled in the subframe.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *alloc
 *  @param[in]  RgSchDlSf              *sf
 *  @param[in]  RgSchUeCb              *ue
 *  @return  S16
 **/
#ifdef ANSI
PRIVATE S16 rgSCHPfsDlSchedTaForUe
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc,
RgSchDlSf               *sf,
RgSchUeCb               *ue
)
#else
PRIVATE S16 rgSCHPfsDlSchedTaForUe(cell, alloc, sf, ue)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
RgSchDlSf               *sf;
RgSchUeCb               *ue;
#endif
{
   /* [Later] Returning a value may not really be needed */
   RgSchEnbPfsDl        *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlCell       *pfsCell = RG_SCH_PFS_GET_PFSCELLDL(cell);
   RgSchCmnDlUe         *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   RgSchDlHqProcCb      *proc;
   RgSchCmnDlHqProc     *cmnProc;
   CmLListCp            *retxQ   = &pfsCell->retxQueues.srbLst;
#ifdef LTEMAC_SPS
   CmLteTimingInfo      schdTime;
#endif
   U32                  macCeBo = 0;
   U32                  bytes = 0;
   TRC2(rgSCHPfsDlSchedTaForUe);

#ifdef LTEMAC_SPS
   schdTime = cell->crntTime;

   /* Increment by DL DELTA to determine the time for which scheduling
    * is done */
   RGSCH_INCR_SUB_FRAME(schdTime, RG_SCH_CMN_DL_DELTA);
   if (RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime))
   {
      RETVALUE(RFAILED);
   }
#endif
   if (RG_SCH_CMN_IS_UE_SCHDLD(ue, cell))
   {
      /*RLOG_ARG1(L_ERROR,DBG_CELLID,cell->cellId,"CRNTI:%d "
         "rgSCHPfsDlSchedTaForUe(): UE already scheduled for this SF even "
         "though TA for UE is being scheduled", ue->ueId);*/
      RETVALUE(RFAILED);
   }

   if (!RG_SCH_CMN_DL_IS_UE_ACTIVE(ue))
   {
      RETVALUE(RFAILED);
   }

   if ((proc = rgSCHPfsDlGetAvlProc(cell, ue, retxQ)) == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cmnUe->proc = proc;

   macCeBo = RGSCH_TA_SIZE;

#ifdef LTE_ADV
   if(RG_SCH_IS_CELL_SEC(ue, cell))
   {
      U8   tpcIdx = 0;
      if(ROK != rgSchGetAvlTpcIdx(ue, &tpcIdx, 
               sf, cell))
      {
         rgSCHPfsDlRlsHqProc(ue, proc);
         cmnUe->proc = NULLP;
         RETVALUE(RFAILED);
      }
      cmnUe->proc->tpc = tpcIdx;
   } 

   /* Consider SCell Act CE also if the same UE is in the
    * SCellAct list also */

   if(ue->sCellActLnk.node != NULLP)
   {
      macCeBo += RGSCH_SCELL_ACT_CE_SIZE;
      pfsUe->schdSCellActCe = TRUE;
   }
#endif
   
   /*ccpu00131191 and ccpu00131317 - Fix for RRC Reconfig failure
    * issue for VoLTE call */
   proc->hasDcch = TRUE;

   rgSCHCmnDlAllocTxRb(cell, sf, ue, macCeBo, &bytes, proc, alloc);
   /* TA size is 2 bytes, corresponding to the smallest possible
    * allocation. So check for zero allocation is enough to check
    * if there isn't sufficient allocation for TA. */
   if (bytes == 0)
   {
#ifdef LTE_ADV
      rgSchFreeTpcIdxForSCell(ue, cmnUe->proc, alloc->dedAlloc.dedDlSf);
#endif
      rgSCHPfsDlRlsHqProc(ue, proc);
      RETVALUE(RFAILED);
   } 

   cmnProc = RG_SCH_CMN_GET_DL_HQP(proc);
   cmnProc->totBytes += bytes;


   pfsUe->taReq = TRUE;

   /* Schduling other LCs also of this UE along with TA */
   pfsUe->totalEffBo += macCeBo;


   /* calling this function to calcualte UE's total PFS priority 
    * and Total PRB required */
   rgSchPfsCalcUePrbAndPrio(cell, ue, proc);

   /* Assigning the maxPfsPrio to SRB priority value if it is 
    * greater than the other LCs priority of this UE */
   if(pfsDl->maxSrbDrb0PrioVal > pfsUe->maxPfsPrio)
   {   
      pfsUe->maxPfsPrio = pfsDl->maxSrbDrb0PrioVal;
   }

   RETVALUE(ROK);
}

/**
 * @brief Resetting the toBeSched structure in cell
 *
 * @details
 *
 *     Function : rgSchPfsToBeSchedInit
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSchPfsToBeSchedInit
(
RgSchCellCb             *cell
)
#else
PRIVATE Void rgSchPfsToBeSchedInit(cell)
RgSchCellCb             *cell;
#endif
{
   RgSchEnbPfsDl         *pfsDl = RG_SCH_PFS_GET_PFSDL(cell); 
   RgSchPfsDlCell        *pfsCell = RG_SCH_PFS_GET_PFSCELLDL(cell);
   RgSchCmnCell          *cellSch = RG_SCH_CMN_GET_CELL(cell);
   RgSchPfsDlLcSchdInfo  *lcToBeSchedPerCell = &pfsCell->rgSchPfsLcSchdInfo;
   RgSchDlSf             *sf;

   lcToBeSchedPerCell->cell = cell;

   RG_SCH_PFS_SET_CELL_SCHD_STATE(cell, FALSE);

   sf = cellSch->allocInfo.dedAlloc.dedDlSf;
   lcToBeSchedPerCell->sf = sf;

   sf->remUeCnt = (sf->remUeCnt < cellSch->dl.maxUeNewTxPerTti)? 
      sf->remUeCnt : cellSch->dl.maxUeNewTxPerTti;

   /* resetting the tem count of LC scheduled count
    * and total number of LC's selected UE's in this TTI*/
   sf->totalLcCntOfSlctdUes = 0; 
   sf->schedLcCount         = 0;
   /* Updating numOfActive UEs in DL SF for rgu dynamic delta*/
   /* TODO: need to see numDlActvUes */ 
   sf->numDlActvUes         =  pfsCell->numDlActvUes;

   cmLListInit(&lcToBeSchedPerCell->ceLcLst);
   cmLListInit(&lcToBeSchedPerCell->otherUeLcLst);
   cmLListInit(&lcToBeSchedPerCell->ueLst);
   lcToBeSchedPerCell->ceTotPfsPrio = 0;
   lcToBeSchedPerCell->totPfsPrio = 0;
   lcToBeSchedPerCell->totPrbReq    = 0;
   lcToBeSchedPerCell->totPrioBwReq       = 0;
   lcToBeSchedPerCell->totNonPrioBwReq       = 0;
   lcToBeSchedPerCell->numPrioUe           = 0;
   lcToBeSchedPerCell->prioUeTotPfsPrio    = 0;

   pfsDl->remCellCnt++; 
}

#ifdef LTE_ADV
/**
 * @brief Scheduling of SCell Act Ce's
 *
 * @details
 *
 *     Function : rgSCHPfsDlSchdSecCellActCe
 *
 *     Processing Steps:
 *     - Traverse the scell act ce list  and do resource allocation
 *       for the UEs.
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @return  Void
 **/

#ifdef ANSI
PRIVATE S16 rgSCHPfsDlSchdSecCellActCe
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *allocInfo
)
#else
PRIVATE S16 rgSCHPfsDlSchdSecCellActCe(cell, allocInfo)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *allocInfo;
#endif
{
   RgSchEnbPfsDl    *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlCell   *pfsCell = RG_SCH_PFS_GET_PFSCELLDL(cell);
   RgSchCmnCell     *schCmnCell = (RgSchCmnCell *)(cell->sc.sch);
   RgSchDlSf        *dlSf = allocInfo->dedAlloc.dedDlSf;
   CmLListCp        *retxQ = &pfsCell->retxQueues.srbLst;
   RgSchUeCb        *ue;
   RgSchCmnUe       *schCmnUe;
   RgSchPfsDlUe     *pfsUe;
   CmLList          *secCellCeNode;
   RgSchDlHqProcCb  *proc;
   RgSchCmnDlHqProc *cmnProc;
   U32              bytes = 0;
#ifdef LTEMAC_SPS
   CmLteTimingInfo  schdTime;
#endif
#ifdef LTEMAC_HDFDD
   Bool             dlAllowed = FALSE;
#endif
    U8              tpcIdx;  
   TRC2(rgSCHPfsDlSchdSecCellActCe);

#ifdef LTEMAC_SPS
   schdTime = cell->crntTime;

   /* Increment by DL DELTA to determine the time for which scheduling
    * is done */
   RGSCH_INCR_SUB_FRAME(schdTime, RG_SCH_CMN_DL_DELTA);
#endif
      
   secCellCeNode = schCmnCell->dl.secCellActCeLst.first;
   /* Fix [ccpu00126870]: MUE_PERTTI_DL: Limiting number of TA scheduling */
   while(secCellCeNode && dlSf->remUeCnt)
   {
      ue = (RgSchUeCb *)(secCellCeNode->node);
      secCellCeNode = secCellCeNode->next;
#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddChkDlAllow ( cell, ue, &dlAllowed);
         if (dlAllowed == FALSE)
         {
            continue;
         }
      }
#endif
      if((ue->dl.dlInactvMask)
#ifdef LTEMAC_SPS
            ||(RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime))
#endif
        )
      {
         continue;
      }
      schCmnUe = RG_SCH_CMN_GET_UE(ue, cell); 

      pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);

      /* Skip it Scell Act Ce is already scheduled
       * as part of TA Scheduling */
      if ((pfsUe->schdSCellActCe == TRUE) ||
          (schCmnUe->dl.proc != NULLP))
      {
         continue;
      }

      if ((proc = rgSCHPfsDlGetAvlProc(cell, ue, retxQ)) == NULLP)
      {
         RETVALUE(RFAILED);
      }

      schCmnUe->dl.proc = proc;

      if(RG_SCH_IS_CELL_SEC(ue, cell))
      {
         if(ROK != rgSchGetAvlTpcIdx(ue, &tpcIdx, 
                   dlSf, cell))
         {
            rgSCHPfsDlRlsHqProc(ue, proc);
            schCmnUe->dl.proc = NULLP;
            continue;
         }
         schCmnUe->dl.proc->tpc = tpcIdx;
      } 

      /*ccpu00131191 and ccpu00131317 - Fix for RRC Reconfig failure
       * issue for VoLTE call */
      schCmnUe->dl.proc->hasDcch = TRUE;

      rgSCHCmnDlAllocTxRb(cell, dlSf, ue, RGSCH_SCELL_ACT_CE_SIZE, 
                   &bytes, proc, allocInfo);

      if (bytes == 0)
      {
         rgSchFreeTpcIdxForSCell(ue, schCmnUe->dl.proc, allocInfo->dedAlloc.dedDlSf);
         rgSCHPfsDlRlsHqProc(ue, proc);
         RETVALUE(RFAILED);
      } 

      cmnProc = RG_SCH_CMN_GET_DL_HQP(proc);
      cmnProc->totBytes += bytes;

      /* Schduling other LCs also of this UE along with TA */
      pfsUe->totalEffBo += RGSCH_SCELL_ACT_CE_SIZE;

      pfsUe->schdSCellActCe = TRUE;


      /* calling this function to calcualte UE's total PFS priority 
       * and Total PRB required */
      rgSchPfsCalcUePrbAndPrio(cell, ue, proc);

      /* Assigning the maxPfsPrio to SRB priority value if it is 
       * greater than the other LCs priority of this UE */
      if(pfsDl->maxSrbDrb0PrioVal > pfsUe->maxPfsPrio)
      {   
         pfsUe->maxPfsPrio = pfsDl->maxSrbDrb0PrioVal;
      }

      dlSf->remUeCnt--;
   }       

   RETVALUE(ROK);
}
#endif  

/**
 * @brief PFS related scheduling for a cell
 *
 * @details
 *
 *     Function : rgSCHPfsDlCeSchd
 *
 *     Processing Steps:
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *allocInfo
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlCeSchd
(
 RgSchCellCb             *cell,
 RgSchCmnDlRbAllocInfo   *allocInfo
 )
#else
PUBLIC Void rgSCHPfsDlCeSchd(cell, allocInfo)
   RgSchCellCb             *cell;
   RgSchCmnDlRbAllocInfo   *allocInfo;
#endif
{
   RgSchEnbPfsDl   *pfsDl = RG_SCH_PFS_GET_PFSDL(cell); 
   RgSchDlSf       *sf        = allocInfo->dedAlloc.dedDlSf;

   TRC2(rgSCHPfsDlCeSchd);

   rgSchPfsToBeSchedInit(cell);

   rgSCHPfsDlSchedTa(cell, allocInfo);
#ifdef LTE_ADV
   rgSCHPfsDlSchdSecCellActCe(cell, allocInfo);
#endif

   /* Subtracting the remCellCnt if max UEs are scheduled in 
    * this subframe */
   if(!(sf->remUeCnt))
   {
      pfsDl->remCellCnt--; 
   }   

   RETVOID;
} 

/**
 * @brief Scheduling of DL re-transmissions
 *
 * @details
 *
 *     Function : rgSCHPfsDlSchedRetx
 *
 *     Processing Steps:
 *     - Traverse queues in same order as for new transmissions
 *       (this time, there shall be HARQ procs instead of services)
 *       - For each proc in the current queue
 *         - Skip if proc is already scheduled
 *         - Invoke common module to make a tentative allocation
 *           for proc
 *         - Add UE to alloc retx list with appropriate variables
 *           filled in
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[out] RgSchCmnDlRbAllocInfo  *alloc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlSchedRetx
(
 RgSchCellCb             *cell,
 RgSchCmnDlRbAllocInfo   *alloc
 )
#else
PRIVATE Void rgSCHPfsDlSchedRetx(cell, alloc)
   RgSchCellCb             *cell;
   RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   RgSchPfsDlCell         *pfsCell = RG_SCH_PFS_GET_PFSCELLDL(cell);
   RgSchPfsDlRetxQueues   *retxQs  = &pfsCell->retxQueues;
   CmLListCp              *retxQ;
   S16                 idx;
   TRC2(rgSCHPfsDlSchedRetx);
   

   retxQ = &retxQs->srbLst;
   rgSCHPfsDlRetxInQ(cell, alloc, retxQ);

   retxQ = &retxQs->drb0Lst;
   rgSCHPfsDlRetxInQ(cell, alloc, retxQ);

   for (idx = RG_SCH_PFS_DL_NUM_GBR_QUEUES-1; idx >= 0; --idx)
   {
      retxQ = &retxQs->gbrLst[idx];
      rgSCHPfsDlRetxInQ(cell, alloc, retxQ);
   }

   retxQ = retxQs->retxMbrLst;
   for (idx = RG_SCH_PFS_DL_NUM_MBR_QUEUES-1; idx >= 0; --idx)
   {
      rgSCHPfsDlRetxInQ(cell, alloc, &retxQ[idx]);
   }

   retxQ = retxQs->retxAmbrLst;
   for (idx = RG_SCH_PFS_DL_NUM_AMBR_QUEUES-1; idx >= 0; --idx)
   {
      rgSCHPfsDlRetxInQ(cell, alloc, &retxQ[idx]);
   }

   RETVOID;
}

/**
 * @brief Scheduling of DL new transmissions
 *
 * @details
 *
 *     Function : rgSCHPfsDlPreSchedNewTx
 *
 *     Processing Steps:
 *     - For each SRB in SRB queue
 *       - Skip if UE scheduled for retx
 *       - Schedule SRB
 *     - In DRB 0 queue
 *       - For each svc in queue
 *         - Skip if UE scheduled for retx
 *         - Schedule upto BO
 *     - For each GBR queue (in decreasing order of priority)
 *       - For each svc in queue
 *         - Skip if UE scheduled for retx
 *         - Schedule upto min(BO, GBR)
 *     - For each MBR queue (in decreasing order of priority)
 *       - For each svc in queue
 *         - Skip if UE scheduled for retx
 *         - Schedule upto min(BO, MBR)
 *     - For each AMBR queue (in decreasing order of priority)
 *       - For each svc in queue
 *         - If (AMBR applicable)
 *           - Schedule upto min(BO, AMBR)
 *         - Else
 *           - Schedule upto BO
 *
 *  @param[in]  Inst   schInst
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlPreSchedNewTx
(
 RgSchCellCb *cell
)
#else
PRIVATE Void rgSCHPfsDlPreSchedNewTx(cell)
 RgSchCellCb *cell;
#endif
{
   RgSchEnbPfsDl         *pfsEnbDl = rgSchCb[cell->instIdx].rgSchEnbPfsDl;
   RgSchPfsDlTxQueues    *txQs  = &pfsEnbDl->txQueues;
   CmLListCp             *txQ;
   S16                    idx;
   CmLListCp             *txQLstAmbr1;
   CmLListCp             *txQLstAmbr2;
   CmLListCp             *txQLstMbr1;
   CmLListCp             *txQLstMbr2;
   U8                     remCellCnt = pfsEnbDl->remCellCnt;
  
   TRC2(rgSCHPfsDlPreSchedNewTx);

   /* Getting the priority for scheduling csg or non-csg */
   /* this is just a workaround to make thus work with current csg implementation
    * later it needs to be changed when CA feature interaction with CSG is done */
   pfsEnbDl->currPrioMmbrSta = rgSCHCmnIsDlCsgPrio(cell);

   if (pfsEnbDl->currPrioMmbrSta == TRUE)
   {
      txQLstMbr1 = txQs->prioMbrLst;
      txQLstMbr2 = txQs->normMbrLst;
      txQLstAmbr1 = txQs->prioAmbrLst;
      txQLstAmbr2 = txQs->normAmbrLst;
   }
   else
   {
      txQLstMbr1 = txQs->normMbrLst;
      txQLstMbr2 = txQs->prioMbrLst;
      txQLstAmbr1 = txQs->normAmbrLst;
      txQLstAmbr2 = txQs->prioAmbrLst;
   } 

   txQ = &txQs->srbLst;

   rgSCHPfsDlNewTxInQ(txQ, &remCellCnt, 0);

   if (remCellCnt)
   {
      txQ = &txQs->drb0Lst;
      rgSCHPfsDlNewTxInQ(txQ, &remCellCnt, 0);
   }

   for (idx = RG_SCH_PFS_DL_NUM_GBR_QUEUES-1; remCellCnt && (idx >= 0); --idx)
   {
      txQ = &txQs->gbrLst[idx];
      rgSCHPfsDlNewTxInQ(txQ, &remCellCnt, idx);
   }

   for (idx = RG_SCH_PFS_DL_NUM_MBR_QUEUES-1; remCellCnt && (idx >= 0); --idx)
   {
      rgSCHPfsDlNewTxInQ(&txQLstMbr1[idx], &remCellCnt, idx);
   }
   for (idx = RG_SCH_PFS_DL_NUM_MBR_QUEUES-1; remCellCnt && (idx >= 0); --idx)
   {
      rgSCHPfsDlNewTxInQ(&txQLstMbr2[idx], &remCellCnt, idx);
   }

   for (idx = RG_SCH_PFS_DL_NUM_AMBR_QUEUES-1; remCellCnt && (idx >= 0); --idx)
   {
      rgSCHPfsDlNewTxInQ(&txQLstAmbr1[idx], &remCellCnt, idx);
   }
   for (idx = RG_SCH_PFS_DL_NUM_AMBR_QUEUES-1; remCellCnt && (idx >= 0); --idx)
   {
      rgSCHPfsDlNewTxInQ(&txQLstAmbr2[idx], &remCellCnt, idx);
   }

   pfsEnbDl->remCellCnt = 0;
   RETVOID;
}

/**
 * @brief Scheduling of DL new transmissions
 *
 * @details
 *
 *     Function : rgSCHPfsDlSchedNewTx
 *
 *     Processing Steps:
 *     - While processing each svc in the above steps, add
 *       UE to list of scheduled UEs in the 'alloc' structure
 *       with appropriate info filled in.
 *
 *  @param[in]  RgSchCellCb             *cell
 *  @param[out] RgSchCmnDlRbAllocInfo   *alloc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlSchedNewTx
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHPfsDlSchedNewTx(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   RgSchEnbPfsDl         *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(cell);
   RgSchPfsDlCell        *pfsCell = RG_SCH_PFS_GET_PFSCELLDL(cell);
   RgSchPfsDlLcSchdInfo  *lcToBeSchedInfo = &pfsCell->rgSchPfsLcSchdInfo;
   RgSchDlSf             *sf = alloc->dedAlloc.dedDlSf;
   U32                   prioUesBwLimit; /* bandwidth limit for priority UEs in case of a mix of CSG & nCSG UEs */
   U32                   bwAvailable;

   bwAvailable = sf->bw - sf->bwAssigned;

   if(pfsEnbDl->currPrioMmbrSta == TRUE)
   {
      prioUesBwLimit = (bwAvailable  * (100 - cell->minDlResNonCsg))/100;
   }
   else
   {
      prioUesBwLimit = (bwAvailable * cell->minDlResNonCsg)/100;
   }
   lcToBeSchedInfo->prioUeBwAvail = bwAvailable; 

   /* Allot the remaining PRBs to the non-priority UEs in case the priority UEs
      are not using up bandwidth reserved for them */
   if (lcToBeSchedInfo->numPrioUe == 0)
   {
      prioUesBwLimit = 0;
      lcToBeSchedInfo->prioUeBwAvail = 0;
   }
   else if (lcToBeSchedInfo->numPrioUe < (lcToBeSchedInfo->ceLcLst.count + 
                   lcToBeSchedInfo->ueLst.count)) 
   {
      /* This case will hit only when there is a mix of CSG and nCSG UEs
         to be scheduled */
      if (lcToBeSchedInfo->totPrioBwReq > prioUesBwLimit)
      {
         if (lcToBeSchedInfo->totNonPrioBwReq < (bwAvailable - prioUesBwLimit))
         {
            lcToBeSchedInfo->prioUeBwAvail = bwAvailable - lcToBeSchedInfo->totNonPrioBwReq;
         }
         else
         {
            lcToBeSchedInfo->prioUeBwAvail = prioUesBwLimit;
         }
      }
      else
      {
         lcToBeSchedInfo->prioUeBwAvail = lcToBeSchedInfo->totPrioBwReq;
      }
   }
   else
   {
      lcToBeSchedInfo->prioUeBwAvail = bwAvailable;
   }
   lcToBeSchedInfo->nonPrioUeBwAvail = bwAvailable - lcToBeSchedInfo->prioUeBwAvail; 

   /* Reset the isBwLeft to TRUE for PRB distibution */
   /* Schedule Cell Edge UEs first for SFR and ABS UEs */
#if RG_UNUSED
   if((RGR_ENABLE == cell->lteAdvCb.sfrCfg.status)||          \
         (RG_SCH_ABS_ENABLED_ABS_SF == cell->lteAdvCb.absDlSfInfo))
   {
      /* Schedule CE UEs first */
      rgSCHPfsScheduleLcs(cell, alloc, txQ, retxQ, &isBwLeft, &lcToBeSchedInfo->ceLcLst,
         &lcToBeSchedInfo->ceTotPfsPrio,&lcToBeSchedInfo->totPrbReq);

      /* Schedule CC UEs */
      rgSCHPfsScheduleLcs(cell, alloc, txQ, retxQ, &isBwLeft, &lcToBeSchedInfo->otherUeLcLst,
         &lcToBeSchedInfo->totPfsPrio,&lcToBeSchedInfo->totPrbReq);
   }
   else
#endif
   {
      /* Schedule these UEs */
      rgSCHPfsScheduleUes(cell, alloc, lcToBeSchedInfo);
   }
}
/**
 * @brief Scheduling of DL new transmissions in a queue
 *
 * @details
 *
 *     Function : rgSCHPfsDlNewTxInQ
 *
 *     Processing Steps:
 *    
 *      - Schedule cell edge UEs first for SFR UEs. Schedule ABS UEs if its an
 *        ABS subframe..
 *      - Schedule cell centre UEs next. Schedule non ABS UEs if its a non ABS
 *        subframe. 
 *      - If ABS and SFR is disabled, schedule all the LCs like before. 
 *
 *  @param[in]  CmLListCp              *txQ
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlNewTxInQ
(
CmLListCp               *txQ,
U8                      *remCellCnt,
U8                      qId
)
#else
PRIVATE Void rgSCHPfsDlNewTxInQ(txQ, remCellCnt, qId)
CmLListCp               *txQ;
U8                      *remCellCnt;
U8                      qId;  
#endif
{
   TRC2(rgSCHPfsDlNewTxInQ);

   if(*remCellCnt)
   {
#if RG_UNUSED
      /* Schedule Cell Edge UEs first for SFR and ABS UEs */   
      if((RGR_ENABLE == cell->lteAdvCb.sfrCfg.status)||          \
         (RG_SCH_ABS_ENABLED_ABS_SF == cell->lteAdvCb.absDlSfInfo))
      {
         rgSCHPfsDlNewTxInSfrAbsQ(cell, alloc, txQ, retxQ, isBwLeftRef,
            toBeSchedInfo);
      }
      /* Next, schedule Cell Centre UEs in non ABS subframes */
      else if(RG_SCH_ABS_ENABLED_NONABS_SF == cell->lteAdvCb.absDlSfInfo)
      {
         rgSCHPfsDlNewTxInNonAbsQ(cell, alloc, txQ, retxQ, isBwLeftRef,
            toBeSchedInfo);
      }  
      /* Schedule normal UEs */
      else
#endif
      {
         rgSCHPfsDlNewTxInNormQ(txQ, remCellCnt, qId);
      }
   }
   RETVOID;
}
/***********************************************************
 *
 *     Func : rgSCHPfsDlUeSched
 *
 *     Desc : Schedule LC. Takes care of doing appropriate
 *            processing to check if UE was already scheduled
 *            for this subframe, and if it was, it wasn't
 *            a retx that it was scheduled for.
 *            Calls common module to figure out number of
 *            bytes tentatively allocd. [One drawback is that
 *            this may cut down allocation in some cases as
 *            it figures out an appropriate TB size match
 *            close to needed bytes. But it is good since
 *            the numbers are taken as is when DLFS is not
 *            invoked.]
 *            Also if the LC was scheduled, adds it to the
 *            scratchpad of list of svcs to be scheduled
 *            in this subframe.
 *            Also adds UE to alloc's newTx list if not
 *            already added.
 *
 *     Ret  : ROK/RFAILED
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE S16 rgSCHPfsDlUeSched
(
RgSchCellCb           *cell,
RgSchCmnDlRbAllocInfo *alloc,
RgSchDlSf             *sf,
RgSchUeCb             *ue
)
#else
PRIVATE S16 rgSCHPfsDlUeSched(cell, alloc, sf, ue)
RgSchCellCb           *cell;
RgSchCmnDlRbAllocInfo *alloc;
RgSchDlSf             *sf;
RgSchUeCb             *ue;
#endif
{
   RgSchCmnDlUe       *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   RgSchDlHqProcCb    *proc;
   RgSchCmnDlHqProc   *cmnProc;
   U32                 bytes;
   U32                reqBytes;
   TRC2(rgSCHPfsDlUeSched);

   proc = (RgSchDlHqProcCb *)cmnUe->proc;

   cmnProc = RG_SCH_CMN_GET_DL_HQP(proc);

   reqBytes = pfsUe->totalEffBo + pfsUe->totalHdrSz; 

   if (rgSCHCmnDlAllocTxRb(cell, sf, ue, reqBytes, &bytes, proc, alloc)
         != ROK)
   {
      RETVALUE(RFAILED);
   }

   if (bytes == 0)
   {
      RETVALUE(RFAILED);
   }

   cmnProc->totBytes += bytes;

   RETVALUE(ROK);
}


/**
 * @brief Scheduling of DL re-transmissions corresponding to
 *        a re-transmission queue
 *
 * @details
 *
 *     Function : rgSCHPfsDlRetxInQ
 *
 *     Processing Steps:
 *     - For each proc in queue
 *       - If UE not scheduled, schedule HARQ process
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *alloc
 *  @param[in]  CmLListCp              *retxQ
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlRetxInQ
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc,
CmLListCp               *retxQ
)
#else
PRIVATE Void rgSCHPfsDlRetxInQ(cell, alloc, retxQ)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
CmLListCp               *retxQ;
#endif
{
   RgSchDlSf          *sf      = alloc->dedAlloc.dedDlSf;
   CmLList            *lnk;      
#ifdef LTEMAC_HDFDD
   Bool               dlAllowed = FALSE;
#endif
#ifdef LTEMAC_SPS
   CmLteTimingInfo      schdTime;
#endif
   /* Fix: MUE_PERTTI_DL */
   U32 remUe = sf->remUeCnt;

   TRC2(rgSCHPfsDlRetxInQ);
#ifdef LTEMAC_SPS
      schdTime = cell->crntTime;

      /* Increment by DL DELTA to determine the time for which scheduling
       * is done */
      RGSCH_INCR_SUB_FRAME(schdTime, RG_SCH_CMN_DL_DELTA);
#endif
   /* LTE_ADV_FLAG_REMOVED_START */
   /* Schedule all the Cell edge UEs in ReTx first */     
   if((TRUE == cell->lteAdvCb.sfrCfg.status)||(RG_SCH_ABS_ENABLED_ABS_SF == cell->lteAdvCb.absDlSfInfo))
   {    
      for (lnk = retxQ->first; lnk && remUe; lnk = lnk->next)
      {
         RgSchDlHqProcCb     *proc = (RgSchDlHqProcCb *)lnk->node;
         RgSchUeCb           *ue = proc->hqE->ue;
         RgSchCmnDlUe        *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
         U32                  ret = 0;
         RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
         RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);


#ifdef LTEMAC_HDFDD
         if (RG_SCH_HDFDD_UE_ENBLD(ue))
         {
            rgSCHCmnHdFddChkDlAllow ( cell, ue, &dlAllowed);
            if (dlAllowed == FALSE)
            {
               continue;
            }
         }
#endif

         if ((RG_SCH_CMN_IS_UE_SCHDLD(ue, cell))
#ifdef LTEMAC_SPS
               || (RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime)) 
#endif
            )
         {
            continue;
         }
         /* Extra check: indicate if there is furtherScope for NewTx
          * addition for a HqProc. This information will
          * be utilized by common scheduler, in case of SM
          * UEs with only one of the TBs retransmitting and the 
          * other TB can be used for clubbing new TX. */
         if (pfsUe->cmnParam->svcPriorLst.first != NULLP)
         {
            dlAllocCb->mimoAllocInfo.hasNewTxData = TRUE; 
         }
         if((RGR_ENABLE == cell->lteAdvCb.sfrCfg.status) && (TRUE == ue->lteAdvUeCb.rgrLteAdvUeCfg.isUeCellEdge))
         {
            alloc->dedAlloc.dedDlSf->sfrTotalPoolInfo.isUeCellEdge = TRUE;
         }
         if (((RGR_ENABLE == cell->lteAdvCb.sfrCfg.status) && \
                  (TRUE == alloc->dedAlloc.dedDlSf->sfrTotalPoolInfo.isUeCellEdge)) || \
               ((RGR_ENABLE == cell->lteAdvCb.absCfg.status) && \
                (TRUE == ue->lteAdvUeCb.rgrLteAdvUeCfg.isAbsUe)))
         {
            /* 3.1 MIMO : last parameter changed */
            rgSCHCmnDlAllocRetxRb(cell, sf, ue, 0, &ret, proc, alloc);

            cmnUe->proc = proc;
            --remUe;
         }  

         if (ret == 0)
         {
            continue;
         }
         /* 3.1 MIMO moving this call in cmn scheduler */
         /*rgSCHCmnDlRbInfoAddUeRetx(allocInfo, ue);*/
      }
      /* schedule now the cell centre UEs */   
      for (lnk = retxQ->first; lnk && remUe; lnk = lnk->next)
      {
         RgSchDlHqProcCb     *proc = (RgSchDlHqProcCb *)lnk->node;
         RgSchUeCb           *ue = proc->hqE->ue;
         RgSchCmnDlUe        *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
         U32                  ret = 0;
         RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
         RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);


#ifdef LTEMAC_HDFDD
         if (RG_SCH_HDFDD_UE_ENBLD(ue))
         {
            rgSCHCmnHdFddChkDlAllow ( cell, ue, &dlAllowed);
            if (dlAllowed == FALSE)
            {
               continue;
            }
         }
#endif

         if ((RG_SCH_CMN_IS_UE_SCHDLD(ue, cell))
#ifdef LTEMAC_SPS
               || (RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime)) 
#endif
            )
         {
            continue;
         }
         /* Extra check: indicate if there is furtherScope for NewTx
          * addition for a HqProc. This information will
          * be utilized by common scheduler, in case of SM
          * UEs with only one of the TBs retransmitting and the 
          * other TB can be used for clubbing new TX. */
         if (pfsUe->cmnParam->svcPriorLst.first != NULLP)
         {
            dlAllocCb->mimoAllocInfo.hasNewTxData = TRUE; 
         }
         if (((RGR_ENABLE == cell->lteAdvCb.sfrCfg.status) && \
               (FALSE == ue->lteAdvUeCb.rgrLteAdvUeCfg.isUeCellEdge)) || \
               ((RGR_ENABLE == cell->lteAdvCb.absCfg.status) && \
                (FALSE == ue->lteAdvUeCb.rgrLteAdvUeCfg.isAbsUe)))
         {    
            /* 3.1 MIMO : last parameter changed */
            rgSCHCmnDlAllocRetxRb(cell, sf, ue, 0, &ret, proc, alloc);

            cmnUe->proc = proc;
            --remUe;
         }  

         if (ret == 0)
         {
            continue;
         }
         /* 3.1 MIMO moving this call in cmn scheduler */
         /*rgSCHCmnDlRbInfoAddUeRetx(allocInfo, ue);*/
      }
   }
   else if(RG_SCH_ABS_ENABLED_NONABS_SF == cell->lteAdvCb.absDlSfInfo)
   {   
      for (lnk = retxQ->first; lnk && remUe; lnk = lnk->next)
      {
         RgSchDlHqProcCb     *proc = (RgSchDlHqProcCb *)lnk->node;
         RgSchUeCb           *ue = proc->hqE->ue;
         RgSchCmnDlUe        *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
         U32                  ret = 0;
         RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
         RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);


#ifdef LTEMAC_HDFDD
         if (RG_SCH_HDFDD_UE_ENBLD(ue))
         {
            rgSCHCmnHdFddChkDlAllow ( cell, ue, &dlAllowed);
            if (dlAllowed == FALSE)
            {
               continue;
            }
         }
#endif

         if ((RG_SCH_CMN_IS_UE_SCHDLD(ue, cell))
#ifdef LTEMAC_SPS
               || (RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime)) 
#endif
            )
         {
            continue;
         }
         /* Extra check: indicate if there is furtherScope for NewTx
          * addition for a HqProc. This information will
          * be utilized by common scheduler, in case of SM
          * UEs with only one of the TBs retransmitting and the 
          * other TB can be used for clubbing new TX. */
         if (pfsUe->cmnParam->svcPriorLst.first != NULLP)
         {
            dlAllocCb->mimoAllocInfo.hasNewTxData = TRUE; 
         }
         /* 3.1 MIMO : last parameter changed */
         if(cell->lteAdvCb.absCfg.absPatternType & RGR_ABS_TRANSMIT)
         {
            if(TRUE == ue->lteAdvUeCb.rgrLteAdvUeCfg.isAbsUe)
            {
               continue;
            }
         }
         rgSCHCmnDlAllocRetxRb(cell, sf, ue, 0, &ret, proc, alloc);
         if (ret == 0)
         {
            continue;
         }
         cmnUe->proc = proc;
         --remUe;
         /* 3.1 MIMO moving this call in cmn scheduler */
         /*rgSCHCmnDlRbInfoAddUeRetx(allocInfo, ue);*/
      }
   } 
   else
   {
      for (lnk = retxQ->first; lnk && remUe; lnk = lnk->next)
      {
         RgSchDlHqProcCb     *proc = (RgSchDlHqProcCb *)lnk->node;
         RgSchUeCb           *ue = proc->hqE->ue;
         RgSchCmnDlUe        *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
         U32                  ret = 0;
         RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
         RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);


#ifdef LTEMAC_HDFDD
         if (RG_SCH_HDFDD_UE_ENBLD(ue))
         {
            rgSCHCmnHdFddChkDlAllow ( cell, ue, &dlAllowed);
            if (dlAllowed == FALSE)
            {
               continue;
            }
         }
#endif

         if ((RG_SCH_CMN_IS_UE_SCHDLD(ue, cell))
#ifdef LTEMAC_SPS
               || (RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime)) 
#endif
            )
         {
            continue;
         }
         /* Extra check: indicate if there is furtherScope for NewTx
          * addition for a HqProc. This information will
          * be utilized by common scheduler, in case of SM
          * UEs with only one of the TBs retransmitting and the 
          * other TB can be used for clubbing new TX. */
         if (pfsUe->cmnParam->svcPriorLst.first != NULLP)
         {
            dlAllocCb->mimoAllocInfo.hasNewTxData = TRUE; 
         }
         /* 3.1 MIMO : last parameter changed */
         rgSCHCmnDlAllocRetxRb(cell, sf, ue, 0, &ret, proc, alloc);
         if (ret == 0)
         {
            continue;
         }
         cmnUe->proc = proc;
         --remUe;
         /* 3.1 MIMO moving this call in cmn scheduler */
         /*rgSCHCmnDlRbInfoAddUeRetx(allocInfo, ue);*/
      }
   }     
   /* LTE_ADV_FLAG_REMOVED_END */
   sf->remUeCnt = remUe;
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlGetAvlProc
 *
 *     Desc : Gets an available HARQ proc by invoking DHM,
 *            and initialises it.
 *            Returns NULL if no proc available.
 *
 *     Ret  : RgSchDlHqProcCb *
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE RgSchDlHqProcCb *rgSCHPfsDlGetAvlProc
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
CmLListCp           *retxQ
)
#else
PRIVATE RgSchDlHqProcCb *rgSCHPfsDlGetAvlProc(cell, ue, retxQ)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
CmLListCp           *retxQ;
#endif
{
   RgSchCmnDlCell       *cmnCell = RG_SCH_CMN_GET_DL_CELL(cell);
   RgSchDlHqProcCb      *proc;
   RgSchPfsDlHqProc     *pfsProc;
   RgSchCmnDlHqProc     *cmnProc;
   TRC2(rgSCHPfsDlGetAvlProc);

   if (rgSCHDhmGetAvlHqProc(cell, ue, cmnCell->time, &proc) != ROK)
   {
      RETVALUE(NULLP);
   }
   cmnProc = (RgSchCmnDlHqProc *)proc->sch;
   cmnProc->totBytes = 0;
   pfsProc = RG_SCH_PFS_GET_PFSPROCDL(proc);
   pfsProc->retxLstCp = retxQ;
   RETVALUE(proc);
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlResetProcs
 *
 *     Desc : Manages removing procs from queues and
 *            releasing them. Called during UE reset
 *            and delete.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlResetProcs
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PRIVATE Void rgSCHPfsDlResetProcs(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{

   RgSchDlHqEnt          *hqEnt = RG_SCH_CMN_GET_UE_HQE(ue, cell);
   S16                  idx;
   TRC2(rgSCHPfsDlResetProcs);

   if((!(ue->dl.dlInactvMask & RG_HQENT_INACTIVE)) && (hqEnt))
   {
      for(idx = 0; idx < hqEnt->numHqPrcs; idx++)
      {
         RgSchDlHqProcCb  *proc    = &hqEnt->procs[idx];
         RgSchPfsDlHqProc *pfsProc = RG_SCH_PFS_GET_PFSPROCDL(proc);
         rgSCHPfsDlProcRmvFrmRetx(cell, ue, proc);
         /*MS_WORKAROUND for ccpu00122892 */
         if ((proc->subFrm != NULLP) &&
               (proc->hqPSfLnk.node != NULLP))
         {

            if (proc->pdcch)
            {
               cmLListDelFrm(&proc->subFrm->pdcchInfo.pdcchs,
                     &proc->pdcch->lnk);
               cmLListAdd2Tail(&cell->pdcchLst, &proc->pdcch->lnk);
               proc->pdcch = NULLP;
            }
            /* Fix */
            rgSCHUtlDlHqPTbRmvFrmTx(proc->subFrm, proc, 0, FALSE);
         }
         pfsProc->retxLstCp = NULLP;
      }
   }
   RGSCHDBGINFONEW(cell->instIdx,(rgSchPBuf(cell->instIdx),"<RESET> Done\n"));

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlRlsHqProc
 *
 *     Desc : Does a (premature) release of a HARQ process.
 *
 *     Ret  : Void
 *
 *     Notes: This is not to be used when the HARQ process
 *            has already been used at least once for
 *            transmission. (The ndi toggling is not
 *            necessary in that case.)
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlRlsHqProc
(
RgSchUeCb           *ue,
RgSchDlHqProcCb     *proc
)
#else
PRIVATE Void rgSCHPfsDlRlsHqProc(ue, proc)
RgSchUeCb           *ue;
RgSchDlHqProcCb     *proc;
#endif
{
   RgSchPfsDlHqProc   *pfsProc = RG_SCH_PFS_GET_PFSPROCDL(proc);
   UNUSED(ue);
   TRC2(rgSCHPfsDlRlsHqProc);

   pfsProc->retxLstCp = NULLP;
   rgSCHDhmRlsHqProc(proc);
   RETVOID;
}


/**
 * @brief Indication of HARQ proc pending for retransmission
 *
 * @details
 *
 *     Function : rgSCHPfsDlProcRetx
 *
 *     Processing Steps:
 *     - The corresponding HARQ proc has to be queued up
 *       for retx
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchDlHqProcCb        *proc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlProcRetx
(
RgSchCellCb         *cell,
RgSchDlHqProcCb     *proc
)
#else
PUBLIC Void rgSCHPfsDlProcRetx(cell, proc)
RgSchCellCb         *cell;
RgSchDlHqProcCb     *proc;
#endif
{
   RgSchUeCb          *ue  = proc->hqE->ue;
   RgSchPfsDlUe *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   RgSchPfsDlHqProc *pfsProc = RG_SCH_PFS_GET_PFSPROCDL(proc);
   
   TRC2(rgSCHPfsDlProcRetx);
   
   cmLListAdd2Tail(&pfsUe->retxProcs, &pfsProc->ueRetxLnk);
   pfsProc->ueRetxLnk.node = (PTR)proc;

   /* Add only if the UE is active */
   if (RG_SCH_CMN_DL_IS_UE_ACTIVE(ue))
   {
      rgSCHPfsDlProcAddToRetx(cell, ue, proc);
   }
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlProcAddToRetx
 *
 *     Desc : Add HARQ proc to cell and ue retx list.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlProcAddToRetx
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgSchDlHqProcCb     *proc
)
#else
PRIVATE Void rgSCHPfsDlProcAddToRetx(cell, ue, proc)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgSchDlHqProcCb     *proc;
#endif
{
   UNUSED(cell);

   TRC2(rgSCHPfsDlProcAddToRetx);

   rgSCHPfsDlProcAddToCellRetx(cell, proc);
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlProcAddToCellRetx
 *
 *     Desc : Add retx HARQ proc only to cell retx list.
 *            Not adding to UE list of retx procs. This is
 *            used in the case when scheduling gap for UE
 *            is over and UE can again be considered for
 *            scheduling.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlProcAddToCellRetx
(
RgSchCellCb         *cell,
RgSchDlHqProcCb     *proc
)
#else
PRIVATE Void rgSCHPfsDlProcAddToCellRetx(cell, proc)
RgSchCellCb         *cell;
RgSchDlHqProcCb     *proc;
#endif
{
   RgSchPfsDlHqProc   *pfsProc = RG_SCH_PFS_GET_PFSPROCDL(proc);

   UNUSED(cell);

   TRC2(rgSCHPfsDlProcAddToCellRetx);

   cmLListAdd2Tail(pfsProc->retxLstCp, &pfsProc->retxLnk);
   pfsProc->retxLnk.node = (PTR)proc;
   RETVOID;
}

/* MS_WORKAROUND for ccpu00122892 : Temp fix for erroeneous RETX Harq release by rgSCHCmnDlAllocRetxRb */
/***********************************************************
 *
 *     Func : rgSCHPfsDlProcRmvFrmRetx
 *
 *     Desc : Remove retx HARQ proc from cell retx list.
 *            Since retx procs are tracked in UE, remove
 *            from UE list also.
 *
 *     Ret  : Void
 *
 *     Notes: Not setting retxLstCp to NULL here. Proc
 *            may again need to be added to retx queues due
 *            to NACK.
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlProcRmvFrmRetx
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgSchDlHqProcCb     *proc
)
#else
PUBLIC Void rgSCHPfsDlProcRmvFrmRetx(cell, ue, proc)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgSchDlHqProcCb     *proc;
#endif
{
   TRC2(rgSCHPfsDlProcRmvFrmRetx);

   rgSCHPfsDlProcRmvFrmCellRetx(cell, proc);
   rgSCHPfsDlProcRmvFrmUeRetx(cell, ue, proc);
   /* This proc may not be free yet, do nothing else.*/
   RETVOID;
}
/***********************************************************
 *
 *     Func : rgSCHPfsDlUpdLcPdbMetric
 *
 *     Desc : Increment the pivot and reposition the LCs under the pivot to 
 *            new location based on its PDB and elapsed time.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlScanUpdPdbPrio
(
RgSchCellCb *cell
)
#else
PUBLIC Void rgSCHPfsDlScanUpdPdbPrio(cell)
RgSchCellCb *cell;
#endif
{
   CmLListCp         *lcLst   = NULLP;
   CmLList           *lnkEnt  = NULLP;
   RgSchDlLcCb       *lcCb    = NULLP;     
   RgSchPfsDlLc      *pfsLc;
   U16                qIdx;
   RgSchEnbPfsDl     *pfsDl = RG_SCH_PFS_GET_PFSDL(cell); 

   TRC2(rgSCHPfsDlScanUpdPdbPrio);

   pfsDl->pdbInfo.pdbPivot = (pfsDl->pdbInfo.pdbPivot + 1) % RG_SCH_MAX_PDB_TIME; 
   lcLst = &(pfsDl->pdbInfo.pdbTrckLst[pfsDl->pdbInfo.pdbPivot]); 
   lnkEnt = lcLst->first;

   while(lnkEnt != NULLP)
   {
      CmLList *pdbQLnk;
      CmLList *lnkNxtEnt;
      lcCb = (RgSchDlLcCb *)lnkEnt->node;
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(lcCb->ue, lcCb);

      lnkNxtEnt = lnkEnt->next;
      pdbQLnk = &pfsLc->pdbQLnk;

      if (lnkEnt == pdbQLnk)
      {
         /* Need to move to the next PDB level */
         pfsLc->pdbLvl = pfsLc->pdbLvl + 1;
         if (pfsLc->pdbLvl > pfsLc->flowCtrlPdbLimit)
         {
            pfsLc->flowCtrlPdbBrchd = TRUE;
         }
         if (pfsLc->pdbLvl > pfsLc->lastPdbLvl)
         {
            /* Remove from pdb tracking queue */ 
            rgSCHPfsDlLcRmvFrmPdbTrckQ(pfsLc); 
            pfsLc->pdbLvl = pfsLc->lastPdbLvl; 
            pfsLc->pdbPrio = rgSchPfsQciPdbInfo[pfsLc->qci-1].pdbPrioWgt[pfsLc->pdbLvl]; 
            rgSCHPfsDlLcUpdPrioRepos(pfsDl, lcCb->ue, pfsLc);
#ifdef TENB_STATS
            lcCb->ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].dlPdbLvl[4] ++;  
#endif
            lnkEnt = lnkEnt->next;
            continue; 
         }
         pfsLc->pdbPrio = rgSchPfsQciPdbInfo[pfsLc->qci-1].pdbPrioWgt[pfsLc->pdbLvl]; 
         qIdx = (pfsDl->pdbInfo.pdbPivot + pfsLc->pdbLvlSz) % \
                RG_SCH_MAX_PDB_TIME;
         /* Repositioning lc in pdb tracking Queues */
         rgSCHPfsDlLcRmvFrmPdbTrckQ(pfsLc);
         rgSCHPfsDlLcAddToPdbTrckQ(pfsDl, lcCb, qIdx);
         rgSCHPfsDlLcUpdPrioRepos(pfsDl, lcCb->ue, pfsLc);
#ifdef TENB_STATS
         lcCb->ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].dlPdbLvl[4] ++;  
#endif
      }
      lnkEnt = lnkNxtEnt;
   }

   RETVOID;
}
/***********************************************************
 *
 *     Func : rgSCHPfsDlProcRmvFrmCellRetx
 *
 *     Desc : Remove retx HARQ proc only from cell retx
 *            list (and not from UE's list of retx procs).
 *            This is done during a gap indication.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlProcRmvFrmCellRetx
(
RgSchCellCb         *cell,
RgSchDlHqProcCb     *proc
)
#else
PRIVATE Void rgSCHPfsDlProcRmvFrmCellRetx(cell, proc)
RgSchCellCb         *cell;
RgSchDlHqProcCb     *proc;
#endif
{
   RgSchPfsDlHqProc   *pfsProc = RG_SCH_PFS_GET_PFSPROCDL(proc);

   UNUSED(cell);
   TRC2(rgSCHPfsDlProcRmvFrmCellRetx);

   if (pfsProc->retxLnk.node)
   {
      cmLListDelFrm(pfsProc->retxLstCp, &pfsProc->retxLnk);
      pfsProc->retxLnk.node = NULLP;
   }

   /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;
 
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlProcRmvFrmUeRetx
 *
 *     Desc : Remove retx HARQ proc only from ue retx
 *            list (and not from cell's list of retx procs).
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlProcRmvFrmUeRetx
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgSchDlHqProcCb     *proc
)
#else
PRIVATE Void rgSCHPfsDlProcRmvFrmUeRetx(cell, ue, proc)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgSchDlHqProcCb     *proc;
#endif
{
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   RgSchPfsDlHqProc   *pfsProc = RG_SCH_PFS_GET_PFSPROCDL(proc);

   UNUSED(cell);
   TRC2(rgSCHPfsDlProcRmvFrmUeRetx);

   if (pfsProc->ueRetxLnk.node)
   {
      cmLListDelFrm(&pfsUe->retxProcs, &pfsProc->ueRetxLnk);
      pfsProc->ueRetxLnk.node = NULLP;
   }
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlNewTxTbDstn 
 *        
 *     Desc : Perform Actual allocation distribution among
 *     UEs schd svcs and TA for a given TB "tbInfo" allocation.
 *     Assumption: TA is given higher priority in Alloc Distribution.
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlNewTxTbDstn 
(
RgSchCellCb    *cell,
RgSchUeCb      *ue,
RgSchDlHqTbCb  *tbInfo,
U32            *effAlloc,
CmLList        **node
)
#else
PRIVATE Void rgSCHPfsDlNewTxTbDstn(cell, ue, tbInfo, effAlloc, node)
RgSchCellCb    *cell;
RgSchUeCb      *ue;
RgSchDlHqTbCb  *tbInfo;
U32            *effAlloc;
CmLList        **node;
#endif
{

   RgSchDlLcCb        *lc;
   RgSchPfsDlLc       *pfsLc = NULLP;
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);  
   CmLList            *prev = NULLP;
   U32                bytes;
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);

   TRC2(rgSCHPfsDlNewTxTbDstn);

   if (!tbInfo->schdTa.pres)
   {
      if (pfsUe->taReq)                  
      {
         /* This is bound to not underflow. TA requires 2 bytes, and minimum
          * possible allocation is 2 bytes. */
         *effAlloc -= RGSCH_TA_SIZE; 

         /* removing RGSCH_TA_SIZE from totalEffBo as it has been schduled */
         pfsUe->totalEffBo -= RGSCH_TA_SIZE;

         rgSCHCmnRmvFrmTaLst(cell, ue);
         rgSCHDhmSchdTa(ue, tbInfo);
         /* Fix : syed Crash due to double delete from TaLst */
         pfsUe->taReq = FALSE;
      }
   }
   
#ifdef LTE_ADV
   if(!tbInfo->schdSCellActCe.pres)
   {
      if(pfsUe->schdSCellActCe == TRUE)
      {
         if(*effAlloc >= RGSCH_SCELL_ACT_CE_SIZE)
         {
            *effAlloc -= RGSCH_SCELL_ACT_CE_SIZE;

            /* removing RGSCH_SCELL_ACT_CE_SIZE from totalEffBo as it has been schduled */
            pfsUe->totalEffBo -= RGSCH_SCELL_ACT_CE_SIZE;

            rgSCHSCellRmvFrmActLst(cell, ue);
            rgSCHSCellSchdActDeactCe(ue, tbInfo);
         }
         pfsUe->schdSCellActCe = FALSE;
      }
   }
#endif

   while(*node)
   {
      prev = *node;
      lc = (RgSchDlLcCb *)(*node)->node;
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      *node = (*node)->next;
      /*
       * if this is the last LC 
       * No need to limit, allocate as much as possible 
       * else
       * Limit the allocation to the max Grant for this LC based
       * on the LC's PFS priority distribution
       */
      bytes = (NULLP != *node) ? \
              (RGSCH_MIN(pfsLc->maxGrantBytes, pfsLc->reqBytes)): pfsLc->reqBytes; 
      bytes = RGSCH_MIN(*effAlloc, bytes);
      if (bytes < RGSCH_MIN_ALLOC_PER_LC)
      {
         break;
      }
      else if (bytes == pfsLc->reqBytes)
      {
         rgSCHPfsDlLcFullyAllocd(cell, ue, lc, tbInfo);
         *effAlloc -= bytes; 
         pfsLc->reqBytes -= bytes;
         pfsLc->maxGrantBytes -= bytes;
      }
      else if (*effAlloc > pfsLc->hdrSz)
      {
         rgSCHPfsDlLcPartlyAllocd(cell, ue, lc, bytes, tbInfo);
         pfsLc->reqBytes -= bytes;
         *effAlloc -= bytes;
         pfsLc->maxGrantBytes -= bytes;
      }

      if(pfsLc->prioChngLnk.node)
      {
         cmLListDelFrm(&(pfsDl->prioChngLcLst), &(pfsLc->prioChngLnk));
         pfsLc->prioChngLnk.node = NULLP;
         pfsLc->favCellPrio = 0;
         pfsLc->favCellPrioLstCp = NULLP;
      }   

      if(!(*effAlloc))
      {
         /* if effalloc has become zero */
         break;
      }   
   }

#if RG_UNUSED
   /* If no more scheduled LCs for TB data distribution
    * then distribute the spare TB data among the LCs
    * of the UE with non-zero BO. This is effective for 
    * schedulers work on LC level priorities rather than
    * UE level. */
   if ((*node == NULLP) && (pfsLc) && (pfsLc->reqBytes == 0))
   {
      rgSCHPfsDlSprTxTbDstn(cell, ue, tbInfo, effAlloc,
                            pfsUe->cmnParam->svcPriorLst.first);
      *node = NULLP;
      RETVOID;
   }
#endif
   /* 3.1 MIMO refer the previous service to 
    * make sure if not served completely then 
    * the other TB allocation accomodates the same */
   *node = prev;
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlSprTxTbDstn 
 *        
 *     Desc : Perform Actual allocation distribution among
 *     UEs schd svcs and TA for a given spare TB "tbInfo" allocation.
 *     spare TB allocation is as a result of 1 RETX TB allocation, when
 *     conditions are favourable for 2 TB spatial multiplexing. 
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlSprTxTbDstn
(
RgSchCellCb    *cell,
RgSchUeCb      *ue,
RgSchDlHqTbCb  *tbInfo,
U32            *effAlloc,
CmLList        *node
)
#else
PRIVATE Void rgSCHPfsDlSprTxTbDstn(cell, ue, tbInfo, effAlloc, node)
RgSchCellCb    *cell;
RgSchUeCb      *ue;
RgSchDlHqTbCb  *tbInfo;
U32            *effAlloc;
CmLList        *node;
#endif
{

  RgSchDlLcCb        *lc;
  RgSchPfsDlLc       *pfsLc;
  U32                bytes;
  U32                effBo;
  U32                rlcHdrEstmt;

   TRC2(rgSCHPfsDlSprTxTbDstn);

   while (node)
   {
      lc = (RgSchDlLcCb *)node->node;
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      node = node->next;
      RG_SCH_CMN_DL_GET_HDR_EST(lc, rlcHdrEstmt);
      effBo = pfsLc->effBo + rlcHdrEstmt;
      bytes = RGSCH_MIN(*effAlloc, effBo);
      if (bytes < *effAlloc)
      {
         /* MS_REMOVE */     
         rgSCHPfsDlBoUpdInt(cell, ue, lc, 0, bytes-rlcHdrEstmt);
         rgSCHPfsDlAddLcAllocToProc(cell, ue, lc, bytes, tbInfo);
         *effAlloc -= bytes;
      }
      else if (bytes <= rlcHdrEstmt)
      {
         break;
      }
      else
      {
         rgSCHPfsDlBoUpdInt(cell, ue, lc, pfsLc->bo - (bytes-rlcHdrEstmt), 
               bytes-rlcHdrEstmt);
         rgSCHPfsDlAddLcAllocToProc(cell, ue, lc, bytes, tbInfo);
         *effAlloc = 0;
         break;
      }
   }
   RETVOID;
}

/* Added new function to handle TX+RETX alloc fnlz'n */
/**
 * @brief This function Processes the Final Allocations
 *        made by the RB Allocator against the requested
 *        RETX+New TX allocations. The NewTx TB allocation
 *        is considered for distribution among LCs.
 *
 * @details
 *
 *     Function: rgSCHPfsDlRetxNewTxAllocFnlz 
 *     Purpose : 1. Reached here due to 1 RETX TB allocation for a 
 *                  SM UE, which is capable to accomodate a newTX
 *                  in the other TB.
 *               2. Distribute NewTX TB allocation among the
 *                  SVCs present in lcsWithData list of UE.
 *
 *
 *     Invoked by: Common Scheduler 
 *     
 *  @param[in]  RgSchCellCb           *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo *alloc
 *  @return  Void
 *
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlRetxNewTxAllocFnlz 
(
RgSchCellCb           *cell,
RgSchCmnDlRbAllocInfo *alloc
)
#else
PRIVATE Void rgSCHPfsDlRetxNewTxAllocFnlz(cell, alloc)
RgSchCellCb           *cell;
RgSchCmnDlRbAllocInfo *alloc;
#endif
{
   CmLList              *lnk;
   RgSchPfsDlUe         *pfsUe;
   RgSchDlHqTbCb        *newTxTbInfo;   
   RgSchDlRbAlloc       *ueAllocInfo;  
   U32                   effAlloc;
   U32                   remTbBytes;
   

   /* Take action for HqPs that are finally scheduled for retx */
   for (lnk = alloc->dedAlloc.schdTxRetxHqPLst.first; lnk; )
   {
      RgSchDlHqProcCb    *proc    = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb          *ue      = proc->hqE->ue;
     
      lnk = lnk->next;     
      pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
      ueAllocInfo = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
      /* Index 0 of ueAllocInfo->tbInfo will always hold the 
          * RETX TB and index 1 will hold the NewTX TB in case of
          * RETX+TX allocation. */
      newTxTbInfo = ueAllocInfo->tbInfo[1].tbCb;
      effAlloc = remTbBytes  =  ueAllocInfo->tbInfo[1].bytesAlloc;     
      rgSCHPfsDlSprTxTbDstn(cell, ue, newTxTbInfo,\
                            &remTbBytes, pfsUe->cmnParam->svcPriorLst.first);
      /* Trying to reduce mcs of TX TB to increase reception quality at UE.
       * In case of RETX+TX allocation, TX TB allocation was irrespective
       * of actual requirement by UE, hence in case if consumption is 
       * less than allocation, consider reducing the iMcs of this TX TB. */
      rgSCHCmnRdcImcsTxTb(ueAllocInfo, 1, effAlloc - remTbBytes);
      rgSCHPfsDlProcRmvFrmRetx(cell, ue, proc);
      rgSCHCmnFillHqPPdcch(cell, ueAllocInfo, proc);
#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddUpdDLMark(cell, ue);
      }
#endif
      rgSCHPfsDlUeSfResetTemp(cell, ue, proc);
#ifdef TENB_STATS
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(proc->hqE->cell)].dlRetxOccns ++; 
#endif
   }

   /* Take action for UEs that are finally NOT scheduled for retx */
   for (lnk = alloc->dedAlloc.nonSchdTxRetxHqPLst.first; lnk; )
   {
      RgSchDlHqProcCb    *proc    = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb          *ue      = proc->hqE->ue;
      lnk = lnk->next;
      /* Fix: syed To update Retx Alloc failure counter.
       * Need to do the same in other schedulers as well. */
      rgSCHDhmDlRetxAllocFail(ue, proc);
      rgSCHPfsDlUeSfResetTemp(cell, ue, proc);
   }
   RETVOID;
}

/**
 * @brief This Function calcualte the cell load for cell based 
 * on PRB Usage
 *
 * @details
 *
 *     Function: rgSCHPfsDlCellLoadCalc 
 *  @param[in]  RgSchCellCb           *cell
 *  @return  Void
 *
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlCellLoadCalc
(
RgSchCellCb           *cell
)
#else
PRIVATE Void rgSCHPfsDlCellLoadCalc(cell)
RgSchCellCb           *cell;
#endif
{
   RgSchDlSf       *dlSf;
   RgSchCmnCell    *cellSch  = RG_SCH_CMN_GET_CELL(cell);
   RgSchPfsDlCell  *pfsCell  = (RgSchPfsDlCell *)(cellSch->dl.schSpfc); 
   RgSchEnbPfsDl   *enbDlPfs = RG_SCH_PFS_GET_PFSDL(cell);
   U8              cellIdx   = RG_SCH_CELLINDEX(cell);      
   U16             ttiMod;
   U8              sampleIdx;

   TRC2(rgSCHPfsDlCellLoadCalc);

   dlSf = rgSCHUtlSubFrmGet(cell, cellSch->dl.time);

   pfsCell->prbSample += dlSf->bwAssigned;
   pfsCell->totalPrbUse += dlSf->bwAssigned;

   ttiMod = pfsCell->ttiCnt % RG_SCH_PFS_DL_PRB_USE_PRD;  

   sampleIdx = ttiMod/RG_SCH_PFS_DL_PRB_SAMPLE_SIZE;

   if(sampleIdx != pfsCell->prevSampleIdx)
   {
      enbDlPfs->cellLoad[cellIdx] = 
           pfsCell->totalPrbUse/RG_SCH_PFS_DL_PRB_USE_PRD;

      pfsCell->totalPrbUse -= pfsCell->prbUsage[sampleIdx];
      pfsCell->prbUsage[pfsCell->prevSampleIdx] = pfsCell->prbSample;
      pfsCell->prevSampleIdx = sampleIdx;
      enbDlPfs->lastCellLoadUpdIdx++;
      pfsCell->prbSample = 0;
   }   

   if(ttiMod == 0)
   {
      pfsCell->ttiCnt = 0;
   }   

   pfsCell->ttiCnt++;
}

/**
 *
 * @details
 *
 *     Function : rgSCHPfsDlRmvFrmPrioChngLst
 *
 *
 *  @param[in]  RgSchCellCb            *cell
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlRmvFrmPrioChngLst
(
 Inst      schInst
)
#else
PUBLIC Void rgSCHPfsDlRmvFrmPrioChngLst(schInst)
 Inst      schInst
#endif
{
   RgSchEnbPfsDl  *pfsDl = rgSchCb[schInst].rgSchEnbPfsDl;
   CmLList        *node;

   TRC2(rgSCHPfsDlRmvFrmPrioChngLst);

   /* changing the priorities of all those LCs which were rearranged in the 
    * prio queue due to unavailability of thier favCell and could not be
    * scheduled later through their next fav cell */
   node = pfsDl->prioChngLcLst.first;

   while(node)
   {
      RgSchDlLcCb   *lc = (RgSchDlLcCb *) node->node;
      RgSchPfsDlLc  *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);

      node = node->next;

      pfsLc->pfsPrio = pfsLc->favCellPrio; 

      rgSCHPfsDlLcUpdQ(pfsLc->favCellPrioLstCp, pfsLc);

      cmLListDelFrm(&(pfsDl->prioChngLcLst), &(pfsLc->prioChngLnk));
      pfsLc->prioChngLnk.node = NULLP;

      pfsLc->favCellPrio = 0;
      pfsLc->favCellPrioLstCp = NULLP;
   }   
} 

/**
 * @brief Invoked on final RB allocation for a DL subframe
 *
 * @details
 *
 *     Function : rgSCHPfsDlOnAlloc
 *
 *     Processing Steps:
 *     - Update for retx allocations (and lack of them)
 *     - Update for new allocations (and lack of them)
 *    3.1 MIMO
 *     - Update for retx + new allocations (and lack of them)
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *alloc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlOnAlloc
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PUBLIC Void rgSCHPfsDlOnAlloc(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   TRC2(rgSCHPfsDlOnAlloc);

   /* Set the isFnlzDone flag for PFSCell */
   RG_SCH_PFS_SET_CELL_SCHD_STATE(cell, TRUE);
   rgSCHPfsDlOnRetxAlloc(cell, alloc);

   rgSCHPfsDlOnNewTxAlloc(cell, alloc);

   /* New Function added to handle TX+RETX 
    * harq process scheduling finalization */
   rgSCHPfsDlRetxNewTxAllocFnlz(cell, alloc);

   rgSCHPfsDlCellLoadCalc(cell);

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlOnRetxAlloc
 *
 *     Desc : Do relevant updations corresponding to retx
 *             allocations (and lack of them)
 *             For SM UEs consider harq state of both TBs
 *             in case of MIMO.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlOnRetxAlloc
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHPfsDlOnRetxAlloc(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   CmLList              *lnk;
   TRC2(rgSCHPfsDlOnRetxAlloc);

   /* Take action for UEs that are finally scheduled for retx */
   for (lnk = alloc->dedAlloc.schdRetxHqPLst.first; lnk; )
   {
      RgSchDlHqProcCb    *proc    = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb          *ue      = proc->hqE->ue;
      RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
      lnk = lnk->next;
      rgSCHCmnFillHqPPdcch(cell, dlAllocCb, proc);
#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddUpdDLMark(cell, ue);
      }
#endif
      /* Extra Check: Retain the hqProc in the RETX Queue if one/more
       * TBs of the HqProc are yet to be scheduled for RETX */
      if ((proc->tbInfo[0].state != HQ_TB_NACKED) && 
            (proc->tbInfo[1].state != HQ_TB_NACKED))     
      {
         rgSCHPfsDlProcRmvFrmRetx(cell, ue, proc);
      }     
      rgSCHPfsDlUeSfResetTemp(cell, ue, proc);
#ifdef TENB_STATS
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(proc->hqE->cell)].dlRetxOccns ++; 
#endif
   }

   /* Take action for UEs that are finally NOT scheduled for retx */
   for (lnk = alloc->dedAlloc.nonSchdRetxHqPLst.first; lnk; )
   {
      RgSchDlHqProcCb    *proc    = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb          *ue      = proc->hqE->ue;
      lnk = lnk->next;
      /* Fix: syed To update Retx Alloc failure counter.
       * Need to do the same in other schedulers as well. */
      rgSCHDhmDlRetxAllocFail(ue, proc);
      rgSCHPfsDlUeSfResetTemp(cell, ue, proc);
   }

   RETVOID;
}  /* rgSCHPfsDlOnRetxAlloc */

/***********************************************************
 *
 *     Func : rgSCHPfsDlOnNewTxAlloc
 *
 *     Desc : Do relevant updations corresponding to new
 *             tx allocations and updations for those
 *             which did not receive any allocations
 *             (freeing proc etc)
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlOnNewTxAlloc
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHPfsDlOnNewTxAlloc(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   CmLList            *lnk;
   TRC2(rgSCHPfsDlOnNewTxAlloc);

   /* Take action for UEs that are finally scheduled for retx */
   for (lnk = alloc->dedAlloc.schdTxHqPLst.first; lnk; )
   {
      RgSchDlHqProcCb    *proc    = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb          *ue      = proc->hqE->ue;
      lnk = lnk->next;
      rgSCHPfsDlOnNewTxAllocForUe(cell, ue, alloc);
#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddUpdDLMark(cell, ue);
      }
#endif
      rgSCHPfsDlUeSfResetTemp(cell, ue, proc);
#ifdef TENB_STATS
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(proc->hqE->cell)].dlTxOccns ++; 
#endif
   }

   /* Take action for UEs that are finally NOT scheduled for retx */
   for (lnk = alloc->dedAlloc.nonSchdTxHqPLst.first; lnk; )
   {
      RgSchDlHqProcCb    *proc    = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb          *ue      = proc->hqE->ue;
#ifdef LTE_ADV
      RgSchDlSf          *sf = alloc->dedAlloc.dedDlSf;
      rgSchFreeTpcIdxForSCell(ue, proc, sf);
#endif
      lnk = lnk->next;
      rgSCHPfsDlRlsHqProc(ue, proc);
      rgSCHPfsDlUeSfResetTemp(cell, ue, proc);
   }

   RETVOID;
}  /* rgSCHPfsDlOnNewTxAlloc */

/***********************************************************
 *
 *     Func : rgSCHPfsDlTxTbDstnOnPfsPrio
 *
 *     Desc : Do relevant updations corresponding to new
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/

#ifdef ANSI
PRIVATE Void rgSCHPfsDlTxTbDstnOnPfsPrio 
(
RgSchCellCb             *cell,
RgSchUeCb               *ue
)
#else
PRIVATE Void rgSCHPfsDlTxTbDstnOnPfsPrio(cell, ue)
RgSchCellCb             *cell;
RgSchUeCb               *ue;
#endif
{
   RgSchCmnDlUe         *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   CmLList              *node;
   RgSchDlRbAlloc       *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
   RgSchDlLcCb          *lc;
   RgSchPfsDlLc         *pfsLc = NULLP;
   U32                  lcTbShare = 0;
   /* 3.1 MIMO Distribute data of each TB across services */
   U32                  totalBytes = dlAllocCb->tbInfo[0].bytesAlloc +
                                     dlAllocCb->tbInfo[1].bytesAlloc;
   if ((!(cmnUe->proc->tbInfo[0].schdTa.pres)||
        !(cmnUe->proc->tbInfo[1].schdTa.pres)) && pfsUe->taReq)
   {
      totalBytes -= RGSCH_TA_SIZE;
   }

#ifdef LTE_ADV
   if((!(cmnUe->proc->tbInfo[0].schdSCellActCe.pres)||
       !(cmnUe->proc->tbInfo[1].schdSCellActCe.pres)) && 
       (pfsUe->schdSCellActCe == TRUE))
   {
      totalBytes -= RGSCH_SCELL_ACT_CE_SIZE;
   }
#endif

   node = pfsUe->schedSvcs.first;
   while(node)
   {
      lc = (RgSchDlLcCb *)(node)->node;
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      node = (node)->next;
      /* Limit the share only if the allocation is the 
       * lesses than the total required number of bytes
       */
      if(totalBytes < pfsUe->totalEffBo)
      {
         lcTbShare = (((U64)totalBytes * pfsLc->pfsPrio))/(pfsUe->totalPfsPrio); 
         /* If lcTbShare is 0, allot atleast 10% of total Tb Size */
         lcTbShare = RGSCH_MAX(lcTbShare, RGSCH_CEIL((totalBytes), 10));
         pfsLc->maxGrantBytes = lcTbShare;
      }
      else
      {
         pfsLc->maxGrantBytes = pfsLc->reqBytes; 
      }
   }
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlOnNewTxAllocForUe
 *
 *     Desc : Do relevant updations corresponding to new
 *             tx allocation for a UE from the Scheduled TB
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlOnNewTxAllocForUe
(
RgSchCellCb             *cell,
RgSchUeCb               *ue,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHPfsDlOnNewTxAllocForUe(cell, ue, alloc)
RgSchCellCb             *cell;
RgSchUeCb               *ue;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   RgSchCmnDlUe         *cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   CmLList              *node;
   /* 3.1 MIMO Distribute data of each TB across services */
   RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
   U32                remTb1Bytes = dlAllocCb->tbInfo[0].bytesAlloc;
   U32                remTb2Bytes = dlAllocCb->tbInfo[1].bytesAlloc;
   U32                effAlloc = 0;
   /*ccpu00120365-ADD-added to code to check if second TB is utilized */
   U32                tb2Bytes = 0;
   RgSchPfsDlLc       *pfsLc;
   RgSchDlLcCb        *highestPrioLc = NULLP;
   U32                maxPfsPrio = 0;

   TRC2(rgSCHPfsDlOnNewTxAllocForUe);

   if (!(remTb1Bytes + remTb2Bytes))
   {
      RETVOID;
   }

   rgSCHPfsDlTxTbDstnOnPfsPrio(cell, ue);
   /* 3.1 MIMO Consider the allocation of New TX TB for distribution */
   /* Handle schd services */
   node = pfsUe->schedSvcs.first;
   if (remTb1Bytes){
      effAlloc += remTb1Bytes;
      rgSCHPfsDlNewTxTbDstn(cell, ue, &cmnUe->proc->tbInfo[0],\
            &remTb1Bytes, &node);
      /* In the event that TB1 is not completely filled by the DL LCs
       * BO, consider the reducing the iMcs for increasing redundancy
       * and hence reception quality at UE */
      rgSCHCmnRdcImcsTxTb(dlAllocCb, 0, 
            dlAllocCb->tbInfo[0].bytesAlloc - remTb1Bytes);
   }
   
   /*ccpu00120365-ADD-assigning value of remTb2Bytes before utilization */
   tb2Bytes = remTb2Bytes;
   
   /* Extra check for a non SM UE allocation */
   if (remTb2Bytes){
      effAlloc += remTb2Bytes;
      rgSCHPfsDlNewTxTbDstn(cell, ue, &cmnUe->proc->tbInfo[1],\
            &remTb2Bytes, &node);
      /* In the event that TB2 is not completely filled by the DL LCs
       * BO, consider the reducing the iMcs for increasing redundancy
       * and hence reception quality at UE */
      rgSCHCmnRdcImcsTxTb(dlAllocCb, 1, 
            dlAllocCb->tbInfo[1].bytesAlloc - remTb2Bytes);
   }
   
   /* ccpu00120365-ADD-Disable the second TB as the second TB is not
    * utilized */
   if ( remTb2Bytes && ( tb2Bytes == remTb2Bytes) )
   {
      /* If few byte allocation satisfied within TB1
       * then single layer Transmit Diversity is chosen
       * for TM3 and TM4 */
      dlAllocCb->mimoAllocInfo.precIdxInfo = 0;
      dlAllocCb->mimoAllocInfo.numTxLyrs   = 1;
      dlAllocCb->tbInfo[1].schdlngForTb    = FALSE;
      dlAllocCb->tbInfo[1].isDisabled      = TRUE;
   }

   /* recalculating the highest priority LC and max PFS priority
    * as after finalization they may change */
   node = pfsUe->cmnParam->svcPriorLst.first;
   while(node)
   {
      RgSchDlLcCb *lc = (RgSchDlLcCb *)node->node;
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);

      if(maxPfsPrio < pfsLc->pfsPrio) 
      {
         highestPrioLc = lc;
         maxPfsPrio    = pfsLc->pfsPrio;
      }
      node = node->next;
   }   

   pfsUe->cmnParam->highestPrioLc = highestPrioLc;
   pfsUe->maxPfsPrio = maxPfsPrio;

   /* In case if for any LC partial allocation is done, then try to add this UE
    * to its next favorite cell only if its a CA UE and highest priority LC is
    * either GBR or AMBR */
#ifdef LTE_ADV
   if(pfsUe->cmnParam->highestPrioLc) 
   {
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, pfsUe->cmnParam->highestPrioLc);

      if(pfsLc->cellFavLst.count > 1)
      {
         rgSCHPfsSchedLcInNextFavCell(cell, ue, pfsUe->cmnParam->highestPrioLc);
      }
   }
#endif

   /* In the (rare) event that allocation was too small
    * and we think no LC data can fit (due to headers taking
    * up some space), we need to rollback allocation by
    * releasing PDCCH and proc. */
   if (effAlloc == (remTb1Bytes + remTb2Bytes))
   {
      rgSCHUtlPdcchPut(cell, &dlAllocCb->dlSf->pdcchInfo, 
            dlAllocCb->pdcch);

#ifdef LTE_ADV
      rgSchFreeTpcIdxForSCell(ue, cmnUe->proc, dlAllocCb->dlSf);
#endif
      rgSCHPfsDlRlsHqProc(ue, cmnUe->proc);
      RETVOID;
   }

   /* Rest of the LCs have nothing allocated. Need not do anything
    * about them. */

   /* Fill PDCCH and assign it to proc */
   rgSCHCmnFillHqPPdcch(cell, dlAllocCb, cmnUe->proc);

   /* Reinit of schedSvcs happens later as part of temporary variables
    * reset in function rgSCHPfsDlUeSfResetTemp() */

   RETVOID;
}  /* rgSCHPfsDlOnNewTxAllocForUe */
/***********************************************************
 *
 *     Func : rgSCHPfsDlLcPartlyAllocd
 *
 *     Desc : This function is called when an LC has
 *            been partly allocated for. The 'bytes'
 *            passed is the total allocated bytes,
 *            including header.
 *            1. Update LC BO and do appropriate
 *               repositioning by calling the BO
 *               update function.
 *            2. Add the allocation details to HARQ proc
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcPartlyAllocd
(
 RgSchCellCb        *cell,
 RgSchUeCb          *ue,
 RgSchDlLcCb        *lc,
 U32                 bytes,
 RgSchDlHqTbCb      *tbInfo
 )
#else
PRIVATE Void rgSCHPfsDlLcPartlyAllocd(cell, ue, lc, bytes, tbInfo)
   RgSchCellCb        *cell;
   RgSchUeCb          *ue;
   RgSchDlLcCb        *lc;
   U32                 bytes;
   RgSchDlHqTbCb      *tbInfo;
#endif
{
   RgSchPfsDlLc       *pfsLc  = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   U32                 sduBytes = bytes - pfsLc->hdrSz;
   if (pfsLc->bo < sduBytes)
   {
      RLOG_ARG3(L_ERROR,DBG_CELLID,cell->cellId,"bo(%ld) < "
         "sduBytes(%ld) CRNTI:%d", pfsLc->bo, sduBytes,ue->ueId);        
      sduBytes = pfsLc->bo;
   }        
   rgSCHPfsDlBoUpdInt(cell, ue, lc, pfsLc->bo - sduBytes, sduBytes);
   rgSCHPfsDlAddLcAllocToProc(cell, ue, lc, bytes, tbInfo);
   /* Else no allocation is made to the LC. */
   RETVOID;
}  /* rgSCHPfsDlLcPartlyAllocd */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcFullyAllocd
 *
 *     Desc : 1. Update LC BO with the appropriate
 *               repositioning by calling the BO
 *               update function.
 *            2. Add the allocation details to HARQ proc
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcFullyAllocd
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *lc,
RgSchDlHqTbCb      *tbInfo
)
#else
PRIVATE Void rgSCHPfsDlLcFullyAllocd(cell, ue, lc, tbInfo)
RgSchCellCb        *cell;
RgSchUeCb          *ue;
RgSchDlLcCb        *lc;
RgSchDlHqTbCb      *tbInfo;
#endif
{
   RgSchPfsDlLc       *pfsLc  = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   U32                 sduBytes = pfsLc->reqBytes - pfsLc->hdrSz;

   rgSCHPfsDlBoUpdInt(cell, ue, lc, 0, sduBytes);
   rgSCHPfsDlAddLcAllocToProc(cell, ue, lc, pfsLc->reqBytes, tbInfo);
   RETVOID;
}  /* rgSCHPfsDlLcFullyAllocd */
/**
 * @brief Add LC allocation HARQ Proc
 *
 * @details
 *
 *     Function : rgSCHPfsDlAddLcAllocToProc
 *
 *     Processing Steps:
 *     - Call common module API to add allocation for a
 *       logical channel to currently scheduled HARQ proc
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchDlLcCb            *lc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlAddLcAllocToProc
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *lc,
U32                     bytes,
RgSchDlHqTbCb          *tbInfo
)
#else
PRIVATE Void rgSCHPfsDlAddLcAllocToProc(cell, ue, lc, bytes, tbInfo)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *lc;
U32                     bytes;
RgSchDlHqTbCb          *tbInfo;
#endif
{
   RgSchLchAllocInfo   lchSchdData;

   lchSchdData.lcId = lc->lcId;
   lchSchdData.schdData = bytes;
   /*TODO: add lc data to a specific TB */
   rgSCHDhmAddLcData(cell->instIdx, &lchSchdData, tbInfo);

#ifdef LTE_L2_MEAS
   /* L2_COUNTERS */
   /* Increment qciActiveLCs once since this LCs buffer will be present
      in Harq process */
   if (lc->lcType == CM_LTE_LCH_DTCH)
   {
      if(!(ue->qciActiveLCs[lc->qciCb->qci]))
      {
         lc->qciCb->dlUeCount++;
      }
      ue->qciActiveLCs[lc->qciCb->qci]++;
   }
#endif
   RETVOID;
}
/***********************************************************
 *
 *     Func : rgSCHPfsDlUeSfResetTemp
 *
 *     Desc : Reset whatever variables where temporarily used
 *            during UE scheduling.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlUeSfResetTemp
(
RgSchCellCb             *cell,
RgSchUeCb               *ue,
RgSchDlHqProcCb         *hqP
)
#else
PRIVATE Void rgSCHPfsDlUeSfResetTemp(cell, ue, hqP)
RgSchCellCb             *cell;
RgSchUeCb               *ue;
RgSchDlHqProcCb         *hqP;
#endif
{
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);

   UNUSED(cell);

   TRC2(rgSCHPfsDlUeSfResetTemp);

   /* Fix :syed  Need to reset this field even in failure case.*/
   pfsUe->taReq = FALSE;
#ifdef LTE_ADV
   pfsUe->schdSCellActCe = FALSE;
#endif
   /* Not explicitly removing LCs from list of
    * scheduled services; just doing a list init.
    * Redundant for retx case.
    */
   cmLListInit(&(pfsUe->schedSvcs));

   pfsUe->totalPrbReqd = 0;
   pfsUe->totalPfsPrio = 0;
   pfsUe->totalHdrSz = 0;
   pfsUe->totalEffBo = 0;
   pfsUe->maxPfsPrio = 0;
   pfsUe->cmnParam->isUeSchd = FALSE;

   /* Re-init of ue->dl.dlAllocCb and setting cmnUe->proc to NULL etc happens
    * in the common function below */
   rgSCHCmnDlUeResetTemp(ue, hqP);

   RETVOID;
}  /* rgSCHPfsDlUeSfResetTemp */

/**
 * @Brief Reset the PDB context
 *
 * @details
 *
 *     Function : rgSchPfsResetPdbCbCntxt  
 *                           
 *
 *     Processing Steps: Reset the PDB context
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchDlLcCb            *lc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSchPfsResetPdbCbCntxt
(
RgSchCellCb            *cell,
RgSchDlLcCb            *lc
)
#else
PRIVATE Void rgSchPfsResetPdbCbCntxt(cell,lc)
RgSchCellCb            *cell;
RgSchDlLcCb            *lc;
#endif
{
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
   TRC2(rgSchPfsResetPdbCbCntxt);

   if (pfsLc->pdbTrckLstCp != NULLP)
   {
      rgSCHPfsDlLcRmvFrmPdbTrckQ(pfsLc); 
   } 
   pfsLc->pdbLvl  = 0;
   pfsLc->pdbPrio = rgSchPfsQciPdbInfo[pfsLc->qci-1].pdbPrioWgt[pfsLc->pdbLvl]; 
   pfsLc->flowCtrlPdbBrchd = FALSE;
   pfsLc->maxBo4FlowCtrl = pfsLc->initMaxBo4FlowCtrl; 
   
   RETVOID;
}

/**
 * @Brief Recalculate DL LC's PFS Prio and repostion in Prio Qs 
 *
 * @details
 *
 *     Function : rgSCHPfsDlLcUpdPrioRepos
 *                           
 *
 *     Processing Steps: Reset the PDB context
 *
 *  @param[in]  RgSchEnbPfsDl          *pfsDl
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchPfsDlLc           *pfsLc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcUpdPrioRepos
(
RgSchEnbPfsDl          *pfsDl,
RgSchUeCb              *ue,
RgSchPfsDlLc           *pfsLc
)
#else
PRIVATE Void rgSCHPfsDlLcUpdPrioRepos(pfsDl, ue, pfsLc)
RgSchEnbPfsDl          *pfsDl;
RgSchUeCb              *ue;
RgSchPfsDlLc           *pfsLc;
#endif
{
   TRC2(rgSchPfsDlLcUpdPrioRepos);

   if (RG_SCH_CMN_DL_IS_UE_ACTIVE(ue))
   {
      switch (pfsLc->lcType)
      {
         case RG_SCH_PFS_LC_TYPE_GBR:
         {
            Bool  prioChngd = FALSE;
            rgSCHPfsDlUpdPfsPrio(pfsDl, pfsLc, ue, &pfsLc->fracPrioInfo, &prioChngd);
            if (pfsLc->effBo)
            {
               if (pfsLc->remGbr)
               {
                  /* Takes care of updating/retaining queue */
                  rgSCHPfsDlLcAddToGbrQ(pfsDl, ue, pfsLc, prioChngd, 0);
               }
               else if (pfsLc->remDeltaMbr)
               { 
                  /* Takes care of updating/retaining queue */
                  rgSCHPfsDlLcAddToMbrQ(pfsDl, ue, pfsLc, prioChngd, 0);
               }
            }
            break;
         }
         case RG_SCH_PFS_LC_TYPE_AMBR:
         {
            rgSCHPfsDlLcAddToAmbrQ(pfsDl, ue, pfsLc, 0);
            break;
         }
         default:
           /* ignore */
         break;
      }
   }
   RETVOID;
}

/**
 * @Brief update the PDB tracking Queue
 *
 * @details
 *
 *     Function : rgSCHPfsDlCalcPdbMetric
 *
 *     Processing Steps:
 *     - If the oldest sdu delay for the LC has not crossed the PDB,
 *       obtain the index based on the oldest sdu delay. Position 
 *       the LC at the tail of the list indexed with the obtained index
 *       in the PDB tracking Queue.
 *     - If the oldest sdu delay for the LC has breached the PDB, 
 *       position LC at the list indexed with the pivot in the 
 *       PDB tracking Queue.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchDlLcCb            *lc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlCalcPdbMetric
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *lc
)
#else
PRIVATE Void rgSCHPfsDlCalcPdbMetric(cell, ue, lc)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *lc;
#endif
{
   U8             qIdx;
   U32            currTime;
   U32            currPdbLvl;
   U32            offst; 
   U32            sduDelay;
   RgSchEnbPfsDl  *pfsDl = RG_SCH_PFS_GET_PFSDL(cell); 
   RgSchPfsDlLc   *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);

   TRC2(rgSCHPfsDlCalcPdbMetric)

   if (lc->oldestSduArrTime == pfsLc->oldestSduArrTime)
   {
#ifdef TENB_STATS
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].dlPdbLvl[pfsLc->pdbLvl] ++;  
#endif
      RETVOID;
   }
   if (lc->bo == 0)
   {
     /*BO is 0 so reset the PDB context and 
      * remove the LC from the pdbTrackLst */
     rgSchPfsResetPdbCbCntxt(cell,lc);
     RETVOID;
   }
   currTime = SGetTtiCount(); 
   sduDelay = RG_TIME_DIFF(currTime, lc->oldestSduArrTime);
   pfsLc->oldestSduArrTime = lc->oldestSduArrTime; 

   currPdbLvl = pfsLc->pdbLvl;
   if (pfsLc->pdbTrckLstCp != NULLP)
   {
      rgSCHPfsDlLcRmvFrmPdbTrckQ(pfsLc);
   }
   pfsLc->pdbLvl = sduDelay / pfsLc->pdbLvlSz; 
   if (pfsLc->pdbLvl > pfsLc->flowCtrlPdbLimit)
   {
      pfsLc->flowCtrlPdbBrchd = TRUE;
   }
   else
   {
      pfsLc->flowCtrlPdbBrchd = FALSE;
   }
   if(pfsLc->pdbLvl > pfsLc->lastPdbLvl)
   {
      pfsLc->pdbLvl = pfsLc->lastPdbLvl;
#ifdef TENB_STATS
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].dlPdbLvl[4] ++;  
#endif
   }
   else
   {
      offst = pfsLc->pdbLvlSz - (sduDelay % pfsLc->pdbLvlSz); 
      qIdx = (pfsDl->pdbInfo.pdbPivot + offst) % RG_SCH_MAX_PDB_TIME;   
      rgSCHPfsDlLcAddToPdbTrckQ(pfsDl, lc, qIdx);
#ifdef TENB_STATS
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].dlPdbLvl[pfsLc->pdbLvl]++;  
#endif
   }

   if (currPdbLvl != pfsLc->pdbLvl)
   {
      pfsLc->pdbPrio = rgSchPfsQciPdbInfo[pfsLc->qci-1].pdbPrioWgt[pfsLc->pdbLvl]; 
      rgSCHPfsDlLcUpdPrioRepos(pfsDl, ue, pfsLc);
   }
   RETVOID;
}


/**
 * @brief set UL UE priority to max for RLC status Tx
 *
 * @details
 *
 *     Function : rgSCHPfsUlSetUeMaxPrio
 *
 *     Processing Steps: 
 *           1. Reset the poll bit
 *           2. remove the UE from the pfs UE list 
 *           3. set pfs prio to max
 *           4. Add the UE back to the list 
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlSetUeMaxPrio
(
RgSchCellCb            *cell,
RgSchUeCb              *ue
)
#else
PRIVATE Void rgSCHPfsUlSetUeMaxPrio (cell, ue)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
#endif
{
#if !(defined(TENB_T2K3K_SPECIFIC_CHANGES) && (defined(LTE_TDD)))
   RgSchPfsUlCell *pfsUlCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchPfsUlUe   *pfsUlUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   Bool           prioChngd = FALSE;
#endif
   //U32            qId;
#if !(defined(TENB_T2K3K_SPECIFIC_CHANGES) && (defined(LTE_TDD)))
   if ((ue->repLcg != NULLP) && (pfsUlUe->lstCp != NULLP))
   {
      /*Setting schedSinceRefresh to false to avoid
        priority overriding by CQI report */
      if(ue->repLcg->lcgId == RG_SCH_PFS_LC_TYPE_AMBR)
      { 
         pfsUlUe->pfsPrio = pfsUlCell->maxPrioValAmbr;
         pfsUlUe->schedSinceRefresh = FALSE;
         prioChngd = TRUE;
      }
      else if (ue->repLcg->lcgId == RG_SCH_PFS_LC_TYPE_GBR)
      {
         pfsUlUe->pfsPrio = pfsUlCell->maxPrioValGbr;
         pfsUlUe->schedSinceRefresh = FALSE;
         prioChngd = TRUE;
      }
      rgSCHPfsUlAddUeToPfsQ(cell, ue, ue->repLcg, prioChngd);
   }
#endif
   RETVOID;
}


/**
 * @brief set DL UE priority to max for RLC status Tx
 *
 * @details
 *
 *     Function : rgSCHPfsDlSetUeMaxPrio
 *
 *     Processing Steps: 
 *           1. remove the UE from the pfs UE list 
 *           2. set pfs prio to max
 *           3. Add the UE back to the list 
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlSetUeMaxPrio
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *lc
)
#else
PRIVATE Void rgSCHPfsDlSetUeMaxPrio (cell, ue, lc)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *lc;
#endif
{
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   U32                qId;

   TRC2(rgSCHPfsDlSetUeMaxPrio);

   rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
   pfsLc->statusScheduled = FALSE;
   if (RG_SCH_CMN_DL_SVC_IS_GBR(lc))
   {
      pfsLc->pfsPrio = pfsDl->ranges.gbrRange.max;
      qId = rgSCHPfsDlGetQId(pfsLc,&pfsDl->ranges.gbrRange,
      pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_GBR_QUEUES-1);
      rgSCHPfsDlLcAddToQ(cell, pfsUe, &pfsDl->txQueues.gbrLst[qId], pfsLc);
      pfsLc->qId = qId;
   }
   else
   {
      pfsLc->pfsPrio = pfsDl->ranges.ambrRange.max;
      qId = rgSCHPfsDlGetQId(pfsLc,&pfsDl->ranges.ambrRange,
            pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_AMBR_QUEUES-1);
      rgSCHPfsAddDlLcToAmbrLst(pfsDl,ue, pfsLc, qId);
      pfsLc->qId = qId;
   }
    
   RETVOID;
}
/**
 * @brief BO update
 *
 * @details
 *
 *     Function : rgSCHPfsDlBoUpd
 *
 *     Processing Steps:
 *     - Call the internal BO update function rgSCHPfsDlBoUpdInt()
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchDlLcCb            *lc
 *  @param[in]  RguDBoReport           *boRpt
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlBoUpd
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *lc
)
#else
PUBLIC Void rgSCHPfsDlBoUpd(cell, ue, lc)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *lc;
#endif
{
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   TRC2(rgSCHPfsDlBoUpd)

   /* If BO Update function is called for secondary cell then 
    * return from here. Do not update the BO */
   if(cell->cellId != ue->cell->cellId)
   {
      RETVOID;
   }   

   if ((pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR) ||
       (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR))
   {
      rgSCHPfsDlCalcPdbMetric(cell,ue,lc);   
   }
   if (lc->setMaxUlPrio == TRUE)
   {
      /* Poll bit is set. Prioretize the UE in UL 
       for AM mode RLC ACK. Poll not set for UM*/
      lc->setMaxUlPrio = FALSE;
      rgSCHPfsUlSetUeMaxPrio(cell,ue);
   }
   if (lc->setMaxDlPrio == TRUE)
   {
      /* Poll bit is set. Prioretize the UE in UL 
       for AM mode RLC ACK. Poll not set for UM*/
      lc->setMaxDlPrio = FALSE;
      rgSCHPfsDlSetUeMaxPrio(cell,ue,lc);
   }
   if ((pfsLc->bo == lc->bo) || !RG_SCH_CMN_DL_IS_UE_ACTIVE(ue))
   {
      RETVOID;
   }
#ifdef RG_PFS_STATS
   ue->pfsStats.lcStats[lc->lcId-1].isRecvdBo = TRUE;
#endif

#ifdef LTE_ADV
   if((pfsLc->lcType != RG_SCH_PFS_LC_TYPE_SRB) &&
      (pfsLc->lcType != RG_SCH_PFS_LC_TYPE_DRB0)) 
   {   
      rgSchPfsGetLcFavCellLst(lc);
   }
#endif

   rgSCHPfsDlBoUpdInt(cell, ue, lc, lc->bo, 0);
   RETVOID;
}

/**
 * @brief Internal BO update
 *
 * @details
 *
 *     Function : rgSCHPfsDlBoUpdInt
 *
 *     Processing Steps:
 *     - Based on type of LC, do appropriate BO+alloc update
 *       - If type is AMBR
 *         - rgSCHPfsDlLcAmbrBoUpd()
 *       - Else If type is GBR
 *         - rgSCHPfsDlLcGbrBoUpd()
 *       - Else if bo is zeo
 *         - Remove from whatever queue LC might be in
 *       - Else if SRB
 *         - Add to SRB queue
 *       - Else (if DRB0)
 *         - Add to DRB0 queue
 *
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchDlLcCb            *lc
 *  @param[in]  U32                     bo
 *  @param[in]  U32                     allocd
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlBoUpdInt
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *lc,
U32                     bo,
U32                     allocd
)
#else
PRIVATE Void rgSCHPfsDlBoUpdInt(cell, ue, lc, bo, allocd)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *lc;
U32                     bo;
U32                     allocd;
#endif
{
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   U8                  cellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];
   TRC2(rgSCHPfsDlBoUpdInt);

   /* L2_COUNTERS */
#ifdef LTE_L2_MEAS
   if ((lc->bo != 0) && (bo == 0) && (lc->lcType == CM_LTE_LCH_DTCH)) 
   {
      if (ue->qciActiveLCs[lc->qciCb->qci])
      {
         ue->qciActiveLCs[lc->qciCb->qci]--;
      }
      if (!(ue->qciActiveLCs[lc->qciCb->qci]))
      {
         lc->qciCb->dlUeCount--;
      }
   }
#endif

   lc->bo = bo;
   pfsLc->bo = bo;

   if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
   {
      rgSCHPfsDlLcAmbrBoUpd(pfsDl, ue, lc, bo, allocd);

      if(allocd)
      {
         /* served data rate for a LC in a particular cell */
         pfsLc->cellSpfc[cellIdx].achvdFracDataRate += allocd;
#ifdef RG_PFS_STATS
         ue->pfsStats.lcStats[lc->lcId-1].achvdFracDataRate += allocd;
#endif
      }   

      RETVOID;
   }

   if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
   {
      rgSCHPfsDlLcGbrBoUpd(pfsDl, ue, lc, bo, allocd);

      if(allocd)
      {
         /* served data rate for a LC in a particular cell */
         pfsLc->cellSpfc[cellIdx].achvdFracDataRate += allocd;
#ifdef RG_PFS_STATS
         ue->pfsStats.lcStats[lc->lcId-1].achvdFracDataRate += allocd;
#endif
      }   

      RETVOID;
   }

   if (bo == 0)
   {
      pfsLc->effBo   = 0;
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
      RETVOID;
   }

   if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_SRB)
   {
      pfsLc->effBo = bo;
      rgSCHPfsDlLcAddToSrbQ(pfsDl, ue, pfsLc);
   }
   else
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      if (pfsLc->lcType != RG_SCH_PFS_LC_TYPE_DRB0)
      {
      }
#endif
      pfsLc->effBo = bo;
      rgSCHPfsDlLcAddToDrb0Q(pfsDl, ue, pfsLc);
   }

   RETVOID;
}
/***********************************************************
 *
 *     Func : rgSCHPfsDlPrioAmbrSvcUpd
 *
 *     Desc : This is called when there is now a new
 *            highest priority AMBR svc with BO
 *            (i.e. pfsUe->ambrSvc has just been
 *            updated)
 *
 *     Ret  : Void
 *
 *     Notes: It is assumed that if there was
 *            an earlier 'ambrSvc', caller would
 *            have taken appropriate actions for
 *            its removal.
 *            It is also assumed that since this
 *            service is not in cell wide queues as
 *            it is just been realised to be the
 *            highest prio ambr svc. Its remRate,
 *            effBo etc need to be computed.
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlPrioAmbrSvcUpd
(
RgSchCellCb        *cell,
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
U32                allocd
)
#else
PRIVATE Void rgSCHPfsDlPrioAmbrSvcUpd(cell, pfsDl, ue, allocd)
RgSchCellCb        *cell;
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
U32                allocd;
#endif
{
   RgSchCmnDlUe       *cmnUe;
   RgSchPfsDlUe       *pfsUe;
   RgSchDlLcCb        *lc;
   RgSchPfsDlLc       *pfsLc;
   TRC2(rgSCHPfsDlPrioAmbrSvcUpd);

   cmnUe = RG_SCH_CMN_GET_DL_UE(ue,cell);
   pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   lc = pfsUe->cmnParam->ambrSvc;
   pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);

   if (ue->dl.ambrCfgd)
   {
      /* remAmbr > 0 here. Allocation triggers reduction
       * of remAmbr where the appropriate check and action
       * on it becoming zero takes place.
       */
      /* Fix : Correcting Fairness logic */     
      pfsLc->effBo = RGSCH_MIN(pfsLc->bo, pfsUe->cmnParam->remAmbr);
   }
   else
   {
      pfsLc->effBo = pfsLc->bo;
   }
   rgSCHPfsDlLcAddToAmbrQ(pfsDl, ue, pfsLc, allocd);
   RETVOID;
}  /* rgSCHPfsDlPrioAmbrSvcUpd */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAddToSrbQ
 *
 *     Desc : Add a DL LC to SRB queue, if not already
 *            present.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAddToSrbQ
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchPfsDlLc       *pfsLc
)
#else
PRIVATE Void rgSCHPfsDlLcAddToSrbQ(pfsDl, pfsUe, pfsLc)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchPfsDlLc       *pfsLc;
#endif
{
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);

   TRC2(rgSCHPfsDlLcAddToSrbQ);
   if (pfsLc->prioLstCp == NULLP)
   {
      rgSCHPfsDlLcAddToQ(ue->cell, pfsUe, &pfsDl->txQueues.srbLst, pfsLc);
   }
   RETVOID;
}  /* rgSCHPfsDlLcAddToSrbQ */


/***********************************************************
 *
 *     Func : rgSCHPfsDLLcAddToUe
 *
 *     Desc :  Purpose:  This function adds a service to the list of
 *                   services
 *               of UE based on the priority of the services.
 *               Order of Priority of services are SRB,DRB,GBR and AMBR
 *            
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDLLcAddToUe
(
RgSchCellCb        *cell,
CmLListCp          *cp,
RgSchPfsDlLc       *pfsLc
)
#else
PRIVATE Void rgSCHPfsDLLcAddToUe(cell, cp, pfsLc)
RgSchCellCb        *cell;
CmLListCp          *cp;
RgSchPfsDlLc       *pfsLc;
#endif
{
   CmLList *lnk;
   RgSchDlLcCb        *lc;
   RgSchPfsDlLc       *pfsSvc;
   /* Added change for rgu dyna delta for 4 ue/tti*/
   RgSchPfsDlCell     *pfsCell;

   /* Calculating num of active UEs for rgu dyna delta for 4 ue/tti*/
   if(!cp->count)
   {/* This is the first LC for this UE
       Hence incrementing the activeUeCount */
      lc = (RgSchDlLcCb *)(pfsLc->svcPrioLnk.node);
      pfsCell = RG_SCH_PFS_GET_PFSCELLDL(cell);
      pfsCell->numDlActvUes++;
   }
   if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_SRB)
   {
      lnk = cp->first;
      cp->crnt = lnk;
      cmLListInsCrnt(cp, &pfsLc->svcPrioLnk);
   }
   else if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_DRB0)
   {
      lnk = cp->first;
      while(lnk)
      {
         lc = (RgSchDlLcCb *)lnk->node;
         pfsSvc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
         if(pfsSvc->lcType == RG_SCH_PFS_LC_TYPE_SRB)
         {
            lnk = lnk->next;
            continue;
         }
         break;
      }
      if (lnk== NULLP)
      {
         cmLListAdd2Tail(cp, &pfsLc->svcPrioLnk);
      }
      else
      {
         cp->crnt = lnk;
         cmLListInsCrnt(cp, &pfsLc->svcPrioLnk);
      }
   }  
   else if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
   {
      lnk = cp->first;
      while(lnk)
      {
         lc = (RgSchDlLcCb *)lnk->node;
         pfsSvc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
         if((pfsSvc->lcType == RG_SCH_PFS_LC_TYPE_SRB) || (pfsSvc->lcType == RG_SCH_PFS_LC_TYPE_DRB0))
         {
             lnk = lnk->next;
             continue;
         }
         break;
      }
      if (lnk== NULLP)
      {
         cmLListAdd2Tail(cp, &pfsLc->svcPrioLnk);
      }
      else
      {
         cp->crnt = lnk;
         cmLListInsCrnt(cp, &pfsLc->svcPrioLnk);
      }
   
   }   
   else
   {
      cmLListAdd2Tail(cp, &pfsLc->svcPrioLnk);
   }
       
   RETVOID;
}


/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAddToDrb0Q
 *
 *     Desc : Add a DL LC to DRB0 queue, if not already
 *            present.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAddToDrb0Q
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchPfsDlLc       *pfsLc
)
#else
PRIVATE Void rgSCHPfsDlLcAddToDrb0Q(pfsDl, ue, pfsLc)
RgSchEnbPfsDl     *pfsDl;
RgSchUeCb          *ue;
RgSchPfsDlLc       *pfsLc;
#endif
{
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);

   TRC2(rgSCHPfsDlLcAddToDrb0Q);

   if (pfsLc->prioLstCp == NULLP)
   {
      rgSCHPfsDlLcAddToQ(ue->cell, pfsUe, &pfsDl->txQueues.drb0Lst, pfsLc);
   }
   RETVOID;
}  /* rgSCHPfsDlLcAddToDrb0Q */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAddToGbrQ
 *
 *     Desc : Add a DL LC to GBR queue, assuming that
 *            'remRate' and 'svccqiPrio' have been
 *            determined. This further updates
 *            pfsLc->pfsPrio before updating in
 *            queue. Does not affect queue positions
 *            if LC was already in correct queue.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAddToGbrQ
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchPfsDlLc       *pfsLc,
Bool               prioChngd, 
U32                allocd
)
#else
PRIVATE Void rgSCHPfsDlLcAddToGbrQ(pfsDl, pfsUe, pfsLc, prioChngd, allocd)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchPfsDlLc       *pfsLc;
Bool               prioChngd;
U32                allocd;
#endif
{
   U8                  qId;
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);

   TRC2(rgSCHPfsDlLcAddToGbrQ);

   if (pfsLc->prioLstCp && (!prioChngd) && (allocd == 0))
   {
      RETVOID;
   }
   qId = rgSCHPfsDlGetQId(pfsLc, &pfsDl->ranges.gbrRange,
                  pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_GBR_QUEUES - 1);

   rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);

   RGSCH_ARRAY_BOUND_CHECK(0, pfsDl->txQueues.gbrLst, qId);

   rgSCHPfsDlLcAddToQ(ue->cell, pfsUe, 
                 &pfsDl->txQueues.gbrLst[qId], pfsLc);
   pfsLc->qId = qId;

   RETVOID;
}  /* rgSCHPfsDlLcAddToGbrQ */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAddToMbrQ
 *
 *     Desc : Add a DL LC to MBR queue, assuming that
 *            'remRate' and 'svccqiPrio' have been
 *            determined. This further updates
 *            pfsLc->pfsPrio before updating in
 *            queue. Does not affect queue positions
 *            if LC was already in correct queue.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAddToMbrQ
(
RgSchEnbPfsDl     *pfsDl,
RgSchUeCb          *ue,
RgSchPfsDlLc       *pfsLc,
Bool               prioChngd, 
U32                allocd
)
#else
PRIVATE Void rgSCHPfsDlLcAddToMbrQ(pfsDl, ue, pfsLc, prioChngd, allocd)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchPfsDlLc       *pfsLc;
Bool               prioChngd;
U32                allocd;
#endif
{
   U8                  qId;
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);

   TRC2(rgSCHPfsDlLcAddToMbrQ);

   if (pfsLc->prioLstCp && (!prioChngd) && (allocd == 0))
   {
      RETVOID;
   }
   qId = rgSCHPfsDlGetQId(pfsLc, &pfsDl->ranges.mbrRange,
                   pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_MBR_QUEUES - 1);
   rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
 
   if (ue->csgMmbrSta == TRUE)
   {
      RGSCH_ARRAY_BOUND_CHECK(0, pfsDl->txQueues.prioMbrLst, qId);
      rgSCHPfsDlLcAddToQ(ue->cell, pfsUe, 
                         &pfsDl->txQueues.prioMbrLst[qId], pfsLc);
   }
   else
   {
      RGSCH_ARRAY_BOUND_CHECK(0, pfsDl->txQueues.normMbrLst, qId);
      rgSCHPfsDlLcAddToQ(ue->cell, pfsUe, 
                         &pfsDl->txQueues.normMbrLst[qId], pfsLc);
   } 
   pfsLc->qId = qId;

   RETVOID;
}  /* rgSCHPfsDlLcAddToMbrQ */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAddToAmbrQ
 *
 *     Desc : Add a DL LC to AMBR queue, assuming that
 *            'remRate' and 'svccqiPrio' have been
 *            determined. This further updates
 *            pfsLc->pfsPrio before updating in
 *            queue. Does not affect queue positions
 *            if LC was already in correct queue.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAddToAmbrQ
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchPfsDlLc       *pfsLc,
U32                allocd
)
#else
PRIVATE Void rgSCHPfsDlLcAddToAmbrQ(pfsDl, ue, pfsUe, pfsLc, allocd)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchPfsDlLc       *pfsLc;
U32                allocd;
#endif
{
   U8                  qId;
   Bool                prioChngd = FALSE;
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);

   TRC2(rgSCHPfsDlLcAddToAmbrQ);

   /* [Later] Can have a common func for AddTo gbr/mbr/ambr q with
    * the following passed
    *   NUM_QUEUES
    *   &pfsDl->ranges.ambrRange
    *   &pfsDl->txQueues.ambrLst
    * reuse1
    */
   /* Fix : Updating PFS to start prio with highest possible value
               and diminishing prio val updates from there on */
   /* Fix : Each Priority Queue should be
    * sorted in descending order of pfsPrio. */
   rgSCHPfsUpdFracPrioInfo(&pfsUe->cmnParam->fracPrioInfo, allocd); 
   rgSCHPfsDlUpdPfsPrio(pfsDl, pfsLc, ue, &pfsUe->cmnParam->fracPrioInfo, &prioChngd);
   /* This check should be made specifically at the callers
    * of this function */
   if (pfsLc->effBo == 0)
   {
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
      RETVOID;
   }
   if (pfsLc->prioLstCp && (!prioChngd) && (allocd == 0))
   {
      RETVOID;
   }
   qId = rgSCHPfsDlGetQId(pfsLc,&pfsDl->ranges.ambrRange,
                 pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_AMBR_QUEUES - 1);

   rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
   RGSCH_PFS_AMBR_ARRAY_BOUND_CHECK(0, pfsDl, qId, ue);
   
   rgSCHPfsAddDlLcToAmbrLst(pfsDl, ue, pfsLc, qId);
   pfsLc->qId = qId;

   RETVOID;
}  /* rgSCHPfsDlLcAddToAmbrQ */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAddToQ
 *
 *     Desc : Insert LC in sorted Prio Queue. 
 *            Set lc's cp to that of queue.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAddToQ
(
RgSchCellCb        *cell,
RgSchPfsDlUe       *pfsUe,
CmLListCp          *cp,
RgSchPfsDlLc       *pfsLc
)
#else
PRIVATE Void rgSCHPfsDlLcAddToQ(cell, pfsUe, cp, pfsLc)
RgSchCellCb        *cell;
RgSchPfsDlUe       *pfsUe;
CmLListCp          *cp;
RgSchPfsDlLc       *pfsLc;
#endif
{
   RgSchDlLcCb        *lLc;
   RgSchPfsDlLc       *lPfsLc;
   CmLList            *node;

   TRC2(rgSCHPfsDlLcAddToQ);

   /* Add to priority Queues only if data and data rate 
    * available to be scheduled */      
   if (pfsLc->effBo == 0)
   {
      RETVOID;    
   }
   /* Fix : syed Each Priority Queue should be
    * sorted in descending order of pfsPrio. */
   /* Insertion can be improved by not always starting
    * from first node */
   node = cp->first;
   while(node)
   {
      lLc = (RgSchDlLcCb *)(node->node);
      lPfsLc = RG_SCH_PFS_GET_PFSDLLC(lLc->ue, lLc);
      if (lPfsLc->pfsPrio < pfsLc->pfsPrio)
      {
         break;
      }
      node = node->next;
   }
   if (node == NULLP)
   {
      /* We have come to the end of the queue, so Append */
      cmLListAdd2Tail(cp, &pfsLc->prioLnk);
   }
   else
   {
      cp->crnt = node;
      cmLListInsCrnt(cp, &pfsLc->prioLnk);
   }

   pfsLc->prioLstCp = cp;

   /* Add to LC's to UE */
   rgSCHPfsDLLcAddToUe(cell, &pfsUe->cmnParam->svcPriorLst,pfsLc);
   RETVOID;
}  /* rgSCHPfsDlLcAddToQ */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAmbrBoUpd
 *
 *     Desc : Remove AMBR Svc from PFS UE's list of
 *            AMBR services if present in it
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAmbrBoUpd
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchDlLcCb        *lc,
U32                 bo,
U32                 allocd
)
#else
PRIVATE Void rgSCHPfsDlLcAmbrBoUpd(pfsDl, ue, lc, bo, allocd)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchDlLcCb        *lc;
U32                 bo;
U32                 allocd;
#endif
{
   RgSchPfsDlUe       *pfsUe   = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);

   TRC2(rgSCHPfsDlLcAmbrBoUpd);

   /* If there is no more AMBR in this refresh cycle,
    * just update BO and get out */
   if (ue->dl.ambrCfgd && !pfsUe->cmnParam->remAmbr)
   {
      RETVOID;
   }

   /* If there is a BO update due to allocation, there
    * is an impact on remaining AMBR which should be
    * taken care of here */
   if (allocd && ue->dl.ambrCfgd)
   {
      RgSchPfsDlLc       *pfsLc;

      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      if (allocd >= pfsUe->cmnParam->remAmbr)
      {
         pfsLc->effBo   = 0;
         pfsUe->cmnParam->remAmbr = 0;
         rgSCHPfsDlRemAmbrZero(pfsDl, pfsUe);
         RETVOID;
      }
      else
      {
         pfsUe->cmnParam->remAmbr -= allocd;
      }
   }

   if (bo == 0)
   {
      rgSCHPfsDlLcAmbrInactv(pfsDl, ue, lc);
   }
   else
   {
      rgSCHPfsDlLcAmbrActv(pfsDl, ue, lc, bo, allocd);
   }
   RETVOID;
}  /* rgSCHPfsDlLcAmbrBoUpd */

/***********************************************************
 *
 *     Func : rgSCHPfsDlRemAmbrZero
 *
 *     Desc : Takes care of the condition when remAmbr
 *            becomes zero (due to allocation).
 *            Essetially, it removes all 'active'
 *            AMBR services from UE's list of active
 *            AMBR services.
 *
 *     Ret  : Void
 *
 *     Notes: By the description, this is obviously
 *            applicable only for UEs for which AMBR
 *            is configured.
 *            This is called only when remAmbr becomes
 *            zero. In theory this could have been
 *            called from other places (such as UE
 *            reset, in which case this is not only
 *            applicable for the case of UE's with
 *            configured AMBR). If that is done, this
 *            function may be renamed accordingly.
 *            Also, not setting effBo and remRate
 *            of any LC to zero. They are going to
 *            come back to queues only during refresh,
 *            when these variables will be freshly set.
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlRemAmbrZero
(
RgSchEnbPfsDl      *pfsDl,
RgSchPfsDlUe       *pfsUe
)
#else
PRIVATE Void rgSCHPfsDlRemAmbrZero(pfsDl, pfsUe)
RgSchEnbPfsDl      *pfsDl;
RgSchPfsDlUe       *pfsUe;
#endif
{
   CmLListCp          *cp;
   RgSchDlLcCb        *lc;
   RgSchPfsDlLc       *pfsLc;

   TRC2(rgSCHPfsDlRemAmbrZero);

   if ((lc = pfsUe->cmnParam->ambrSvc) == NULLP)
   {
      RETVOID;
   }

   /* Remove the highest priority AMBR service from
    * cell-wide queues */
   pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
   rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);

   /* Now remove all AMBR services from UE's list of active AMBR
    * services */
   cp = &pfsUe->cmnParam->ambrLst;
   /* Fix from syed for mulitple bearer with same qci */
   do
   {
      lc = (RgSchDlLcCb *)(cp->first->node);    
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
      /* Deemed unnecessry to set effBo to zero */
      cmLListDelFrm(cp, &pfsLc->ambrLnk);
      pfsLc->ambrLnk.node = NULLP;
   } while ((cp->first) != NULLP);
   /* Reset ambrSvc to NULLP when the AMBR Lst is empty. If we dont then upon 
    * BoUpd we check for the presence of ambrSvc andi assume that LC is also 
    * present in pfsUe->ambrLst. But when we come back to this function we always 
    * assume pfsUe->ambrLst is non-empty and we crash. */
   pfsUe->cmnParam->ambrSvc = NULLP;

   RETVOID;
}  /* rgSCHPfsDlRemAmbrZero */


/***********************************************************
 *
 *     Func : rgSCHPfsDlLcGbrBoUpd
 *
 *     Desc : Remove AMBR Svc from PFS UE's list of
 *            AMBR services if present in it
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcGbrBoUpd
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchDlLcCb        *lc,
U32                 bo,
U32                 allocd
)
#else
PRIVATE Void rgSCHPfsDlLcGbrBoUpd(pfsDl, ue, lc, bo, allocd)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchDlLcCb        *lc;
U32                 bo;
U32                 allocd;
#endif
{
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   Bool                prioChngd = FALSE;
   TRC2(rgSCHPfsDlLcGbrBoUpd);

   /* Do allocation related updations */
   if (allocd)
   {
      if (pfsLc->remGbr)
      {
         if (allocd >= pfsLc->remGbr)
         {
            pfsLc->remGbr = 0;
            /* Could consider calling RmvFrmPrioQ to remove from the GBR queue
             * that this LC might be in */
            /* From this point onwards, this LC would play in MBR Queues.
             * Hence resetting fracPrio as per MBR */
            rgSCHPfsInitFracPrioInfo(&pfsLc->fracPrioInfo, pfsLc->deltaMbr); 
            rgSCHPfsDlUpdPfsPrio(pfsDl, pfsLc, ue, &pfsLc->fracPrioInfo, &prioChngd);
         }
         else
         {
            pfsLc->remGbr -= allocd;
            /* Fix : Updating PFS to start prio with highest possible value
                        and diminishing prio val updates from there on */
            rgSCHPfsUpdFracPrioInfo(&pfsLc->fracPrioInfo, allocd); 
            rgSCHPfsDlUpdPfsPrio(pfsDl, pfsLc, ue, &pfsLc->fracPrioInfo, &prioChngd);
         }
      }
      else if (pfsLc->remDeltaMbr)
      {
         if (allocd >= pfsLc->remDeltaMbr)
         {
            pfsLc->remDeltaMbr = 0;
            /* Could consider calling RmvFrmPrioQ to remove from the MBR queue
             * that this LC might be in */
         }
         else
         {
            pfsLc->remDeltaMbr -= allocd;
            /* Fix : Updating PFS to start prio with highest possible value
                        and diminishing prio val updates from there on */
            rgSCHPfsUpdFracPrioInfo(&pfsLc->fracPrioInfo, allocd); 
            rgSCHPfsDlUpdPfsPrio(pfsDl, pfsLc, ue, &pfsLc->fracPrioInfo, &prioChngd);
         }
      }
   }

   if (bo == 0)
   {
      pfsLc->effBo   = 0;
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
      RETVOID;
   }

   if (pfsLc->remGbr)
   {
      pfsLc->effBo = RGSCH_MIN(bo, pfsLc->remGbr);
      rgSCHPfsDlLcAddToGbrQ(pfsDl, ue, pfsLc, prioChngd, allocd);
   }
   else if (pfsLc->remDeltaMbr)
   {
      pfsLc->effBo = RGSCH_MIN(bo, pfsLc->remDeltaMbr);
      rgSCHPfsDlLcAddToMbrQ(pfsDl, ue, pfsLc, prioChngd, allocd);
   }
   else
   {
      /* No MBR left, LC is not in, and will not be in any
       * queue until expiry of current refresh cycle */
      pfsLc->effBo = 0;
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
   }

   RETVOID;
}  /* rgSCHPfsDlLcGbrBoUpd */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAmbrActv
 *
 *     Desc : Take all necessary action when positive BO
 *            is reported for an AMBR service.
 *
 *     Ret  : Void
 *
 *     Notes: Nothing is assumed about the service (such
 *            as whether it is in the UE's AMBR list or not).
 *            It is assumed though that the case of remAmbr
 *            being zero is handled earlier and such cases
 *            therefore need not be considered here.
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAmbrActv
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchDlLcCb        *lc,
U32                 bo,
U32                 allocd
)
#else
PRIVATE Void rgSCHPfsDlLcAmbrActv(pfsDl, ue, lc, bo, allocd)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchDlLcCb        *lc;
U32                 bo;
U32                 allocd;
#endif
{
   RgSchCellCb        *cell = ue->cell;
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue,cell);
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   RgSchDlLcCb        *oldLc = pfsUe->cmnParam->ambrSvc;
   RgSchPfsDlLc       *oldPfsLc;

   TRC2(rgSCHPfsDlLcAmbrActv);

   pfsLc->bo = bo;

   if (lc == pfsUe->cmnParam->ambrSvc)
   {
      /* Added the handling to update the effBo, remRate.
       * Deleted the invocation of function rgSCHPfsDlLcAddToAmbrQ as this
       * is being called from function rgSCHPfsDlPrioAmbrSvcUpd.*/
      rgSCHPfsDlPrioAmbrSvcUpd(cell, pfsDl, ue, allocd);
      RETVOID;
   }
   rgSCHPfsDlLcInsInUeAmbrLst(cell, pfsUe, lc);
   if (oldLc == NULLP)
   {
      rgSCHPfsDlPrioAmbrSvcUpd(cell, pfsDl, ue, 0);
   }
   else if (oldLc != pfsUe->cmnParam->ambrSvc)
   {
      oldPfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, oldLc);
      /* This lc has displaced oldLc to become the
       * UE's highest priority AMBR svc. So remove
       * oldLc from cell wide queues. */
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, oldPfsLc);
      rgSCHPfsDlPrioAmbrSvcUpd(cell, pfsDl, ue, 0);
   }
   else
   {
      pfsLc->effBo   = 0;
   }
   RETVOID;
}  /* rgSCHPfsDlLcAmbrActv */

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcAmbrInactv
 *
 *     Desc : Take all necessary action when BO=0 is reported
 *            for an AMBR service
 *
 *     Ret  : Void
 *
 *     Notes: It is assumed that the case of remAmbr being
 *            zero is handled earlier.
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAmbrInactv
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchDlLcCb        *lc
)
#else
PRIVATE Void rgSCHPfsDlLcAmbrInactv(pfsDl, ue, lc)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchDlLcCb        *lc;
#endif
{
   RgSchCellCb        *cell  = ue->cell;
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);

   UNUSED(pfsDl);

   TRC2(rgSCHPfsDlLcAmbrInactv);

   pfsLc->effBo   = 0;
   pfsLc->bo      = 0;

   if (pfsLc->ambrLnk.node == NULLP)
   {
      RETVOID;
   }
   cmLListDelFrm(&pfsUe->cmnParam->ambrLst, &pfsLc->ambrLnk);
   pfsLc->ambrLnk.node = NULLP;
   if (pfsUe->cmnParam->ambrSvc == lc)
   {
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
      if (pfsUe->cmnParam->ambrLst.first)
      {
         pfsUe->cmnParam->ambrSvc = 
            (RgSchDlLcCb *)pfsUe->cmnParam->ambrLst.first->node;
         rgSCHPfsDlPrioAmbrSvcUpd(cell, pfsDl, ue, 0);
      }
      else
      {
         pfsUe->cmnParam->ambrSvc = NULLP;
      }
   }
   RETVOID;
}  /* rgSCHPfsDlLcAmbrInactv */


/***********************************************************
 *
 *     Func : rgSCHPfsDlLcInsInUeAmbrLst
 *
 *     Desc : If LC is not already in list, 
 *            add DL AMBR LC into UE's list of AMBR LCs
 *            maintaining correct priority order.
 *            Update pfsUe->ambrSvc also if needed.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcInsInUeAmbrLst
(
RgSchCellCb         *cell,
RgSchPfsDlUe       *pfsUe,
RgSchDlLcCb        *lc
)
#else
PRIVATE Void rgSCHPfsDlLcInsInUeAmbrLst(cell, pfsUe, lc)
RgSchCellCb         *cell,
RgSchPfsDlUe       *pfsUe;
RgSchDlLcCb        *lc;
#endif
{
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
   CmLListCp          *cp = &pfsUe->cmnParam->ambrLst;
   CmLList            *lnk;
   TRC2(rgSCHPfsDlLcInsInUeAmbrLst);

   if (pfsLc->ambrLnk.node == (PTR)lc)
   {
      pfsUe->cmnParam->ambrSvc = (RgSchDlLcCb *)cp->first->node;
      RETVOID;
   }
   pfsLc->ambrLnk.node = (PTR)lc;
   for (lnk = cp->first; lnk; lnk = lnk->next)
   {
      RgSchDlLcCb   *tmpLc = (RgSchDlLcCb *)lnk->node;
      RgSchPfsDlLc  *tmpPfsLc = RG_SCH_PFS_GET_PFSDLLC(tmpLc->ue, lc);
      /* svcPrio Lower value should have higher priority to process */
      if (pfsLc->svcPrio <= tmpPfsLc->svcPrio)
      {
         cp->crnt = lnk;
         cmLListInsCrnt(cp, &pfsLc->ambrLnk);
         pfsUe->cmnParam->ambrSvc = (RgSchDlLcCb *)cp->first->node;
         RETVOID;
      }
   }
   cmLListAdd2Tail(cp, &pfsLc->ambrLnk);
   pfsUe->cmnParam->ambrSvc = (RgSchDlLcCb *)cp->first->node;
   RETVOID;
}  /* rgSCHPfsDlLcInsInUeAmbrLst */

/***********************************************************
 *
 *     Func : rgSCHPfsDlGetQId
 *
 *     Desc : Return the queue Id appropriate for the passed
 *            priority value.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE U8 rgSCHPfsDlGetQId
(
RgSchPfsDlLc       *pfsLc,
RgSchPfsPrioRange  *range,
U32                 prioVal,
U8                  maxQId
)
#else
PRIVATE U8 rgSCHPfsDlGetQId(range, prioVal, maxQId)
RgSchPfsDlLc       *pfsLc;
RgSchPfsPrioRange  *range;
U32                 prioVal;
U8                  maxQId;
#endif
{
   U32      qId;
   TRC2(rgSCHPfsDlGetQId);

   /*ccpu00128290 - ADD - Protection to avoid prioVal going out of range */
   if (prioVal < range->min)
   {
      prioVal = range->min;
   }
   /* Fix : syed For small range and large number of Queues
    * precalculated numElemPerQ can be highly inaccurate. It
    * was leading to a crash.  */
   qId = ((prioVal - range->min) * range->numQs)/range->maxDiff;
   RETVALUE(qId);
}  /* rgSCHPfsDlGetQId */



/***********************************************************
 *
 *     Func : rgSCHPfsDlLcRmvFrmPrioQ
 *
 *     Desc : Remove DL LC from cell wide priority queue
 *            if present.
 *            Since LCs which are in cell wide queues are
 *            kept track of in ue (pfsUe->inQLcLst), remove
 *            from this list as well.
 *            Remove DL LC from UE wide priority queue if present
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcRmvFrmPrioQ
(
RgSchEnbPfsDl      *pfsDl,
RgSchPfsDlUe       *pfsUe,
RgSchPfsDlLc       *pfsLc
)
#else
PRIVATE Void rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc)
RgSchEnbPfsDl      *pfsDl;
RgSchPfsDlUe       *pfsUe;
RgSchPfsDlLc       *pfsLc;
#endif
{
   UNUSED(pfsDl);
   TRC2(rgSCHPfsDlLcRmvFrmPrioQ);

   if (pfsLc->prioLstCp)
   {
      cmLListDelFrm(pfsLc->prioLstCp, &pfsLc->prioLnk);
      /*cmLListDelFrm(&pfsUe->inQLcLst, &pfsLc->inQLnk);*/
      pfsLc->prioLstCp = NULLP;
      /* TODO: You cannot use same link "prioLnk" to manipulate 
       * LC in 2 different lists */
      cmLListDelFrm(&pfsUe->cmnParam->svcPriorLst, &pfsLc->svcPrioLnk); 
      /* Calculating num of active UEs for rgu dyna delta for 4 ue/tti*/
      if(!(pfsUe->cmnParam->svcPriorLst.count))
      {/* As no more LC's of this UE is not present in the list
          decrementing the activeUeCount */
/* Amit */
#if RG_UNUSED
         pfsCell->numDlActvUes--;
#endif
      }
   }

   /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;
 
}  /* rgSCHPfsDlLcRmvFrmPrioQ */


/***********************************************************
 *
 *     Func : rgSCHPfsDlLcRmvFrmPdbTrckQ
 *
 *     Desc : Remove DL LC from pdb Tracking queue
 *            if present.
 *            Since LCs which are in cell wide queues are
 *            kept track of in ue (pfsUe->inQLcLst), remove
 *            from this list as well.
 *            Remove DL LC from UE wide priority queue if present
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcRmvFrmPdbTrckQ
(
RgSchPfsDlLc       *pfsLc
)
#else
PRIVATE Void rgSCHPfsDlLcRmvFrmPdbTrckQ (pfsLc)
RgSchPfsDlLc       *pfsLc;
#endif
{
   TRC2(rgSCHPfsDlLcRmvFrmPdbTrckQ);

   cmLListDelFrm(pfsLc->pdbTrckLstCp, &pfsLc->pdbQLnk);
   pfsLc->pdbTrckLstCp = NULLP;

   RETVOID;
 
}  /* rgSCHPfsDlLcRmvFrmPdbTrckQ */


/**
 * @brief DL UE refresh
 *
 * @details
 *
 *     Function : rgSCHPfsDlUeRefresh
 *
 *     Processing Steps:
 *     - If AMBR configured
 *       - Set UE's remAmbr = ambr
 *       - Set effBo of highest priority AMBR svc
 *         with non zero BO to min(BO, remAmbr)
 *       - Compute PFS priority
 *       - Update position of the svc in queues
 *     - For each GBR DTCH
 *       - Refresh remGbr and remDeltaMbr
 *       - Set effBo = min(BO, remGbr)
 *       - Compute PFS priority
 *       - Update in cell-wide queues appropriately
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsDlUeRefresh
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PUBLIC Void rgSCHPfsDlUeRefresh(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
#ifdef SCH_STATS
   RgSchCmnDlUe        *cmnUe = RG_SCH_CMN_GET_DL_UE(ue, cell);
#endif
   CmLListCp          *cp;
   CmLList            *lnk;
   U32                srvdAmbr; 
   TRC2(rgSCHPfsDlUeRefresh);

   pfsUe->cqiPrio = rgSCHPfsDlGetTpPrio(pfsDl, RG_SCH_PFS_DL_MAX_ITBS);
   /* GBR related updates */
   cp = &pfsUe->cmnParam->cfgGbrLst;
   for (lnk = cp->first; lnk; lnk = lnk->next)
   {
      RgSchDlLcCb     *lc = (RgSchDlLcCb *)lnk->node;
      RgSchPfsDlLc    *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      U8              cellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];      
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);
      /* Fix : Updating PFS to start prio with highest possible value
         and diminishing prio val updates from there on. */
      pfsLc->cellSpfc[cellIdx].svccqiPrio = pfsLc->svcPrio * pfsUe->cqiPrio;
      rgSCHPfsDlLcGbrRefresh(cell, ue, lc);
      pfsLc->cellSpfc[cellIdx].achvdFracDataRate = 0;
   }

#ifdef RG_PFS_STATS
   ue->pfsStats.refreshCycleCnt++;
#endif
   /* AMBR related updates */
   if (!ue->dl.ambrCfgd)
   {
      RETVOID;
   }
#ifdef SCH_STATS
   cmnUe->remAmbrForStats = pfsUe->cmnParam->remAmbr;
#endif
   if (pfsUe->cmnParam->ambrSvc)
   {
      RgSchPfsDlLc *pfsLc = 
         RG_SCH_PFS_GET_PFSDLLC(ue, pfsUe->cmnParam->ambrSvc);
      rgSCHPfsDlLcRmvFrmPrioQ(pfsDl, pfsUe, pfsLc);   
   }
   srvdAmbr = ue->dl.ambrCfgd - pfsUe->cmnParam->remAmbr;
   pfsUe->cmnParam->remAmbr = ue->dl.ambrCfgd;
   rgSCHPfsInitFracPrioInfo(&pfsUe->cmnParam->fracPrioInfo, ue->dl.ambrCfgd);
   cp = &pfsUe->cmnParam->cfgAmbrLst;
   for (lnk = cp->first; lnk; lnk = lnk->next)
   {
      RgSchDlLcCb        *lc    = (RgSchDlLcCb *)lnk->node;
      RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      U8                 cellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];      
      pfsLc->cellSpfc[cellIdx].svccqiPrio = pfsLc->svcPrio * pfsUe->cqiPrio;
      pfsLc->maxBo4FlowCtrl = (srvdAmbr * pfsLc->rcvryDurFlowCtrl)/
                               (RG_SCH_CMN_REFRESH_TIME * 10);
      if (pfsLc->bo)
      {
         rgSCHPfsDlLcInsInUeAmbrLst(cell, pfsUe, lc);
      }
      pfsLc->cellSpfc[cellIdx].achvdFracDataRate = 0;
   }
   if (pfsUe->cmnParam->ambrSvc)
   {
      if (RG_SCH_CMN_DL_IS_UE_ACTIVE(ue))
      {
         rgSCHPfsDlPrioAmbrSvcUpd(cell, pfsDl, ue, 0);
      }
   }

   /* Updates for others (SRBs and DRB0) not required */

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcGbrRefresh
 *
 *     Desc : Does refresh handling for a GBR LCG.
 *            Right now, just calls the BO update
 *            function which works fine but may not
 *            be very efficient.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcGbrRefresh
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgSchDlLcCb         *lc
)
#else
PRIVATE Void rgSCHPfsDlLcGbrRefresh(cell, ue, lc)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgSchDlLcCb         *lc;
#endif
{
   /* Could optimise slightly later */
   RgSchEnbPfsDl      *pfsDl = RG_SCH_PFS_GET_PFSDL(cell);
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   Bool               prioChngd = FALSE;
   RgSchCmnDlSvc      *cmnLc = (RgSchCmnDlSvc *)lc->sch;
   U32                srvdMbr;

   TRC2(rgSCHPfsDlLcGbrRefresh);

#ifdef RG_PFS_STATS
   if(ue->pfsStats.lcStats[lc->lcId-1].ignoredFirstRefresh == TRUE)
   {
      if (ue->pfsStats.lcStats[lc->lcId-1].isRecvdBo == TRUE) /* This check is the case when there 
                                                                 is no data from RLC for that refresh cycle */
      {
         if(!pfsLc->remGbr)
         {
            ue->pfsStats.lcStats[lc->lcId-1].gbrSatisfiedCnt++;          
         }
         ue->pfsStats.lcStats[lc->lcId-1].gbrRefreshCycleCnt++;
         printf("\nrgSCHPfsDlLcGbrRefresh: Refresh Cycle expire for UE %d lcId %d remGbr %lu gbr %lu gbrSatisfiedCnt %lu gbrRefreshCycleCnt %lu\n",
               ue->ueId, lc->lcId, pfsLc->remGbr, pfsLc->gbr, \
               ue->pfsStats.lcStats[lc->lcId-1].gbrSatisfiedCnt, ue->pfsStats.lcStats[lc->lcId-1].gbrRefreshCycleCnt);
      }
   }
   else if (ue->pfsStats.lcStats[lc->lcId-1].isRecvdBo == TRUE) /* Ignore the refresh cycles till 1st ever BO is received 
                                                                   including the cycle in which it is received for the 1st time */
   {
      /* Ignore 1st refresh cycle coz we dnt know when UE has been added 
         and it had enough chance to be satisfied during 1st refresh cycle */
      ue->pfsStats.lcStats[lc->lcId-1].ignoredFirstRefresh = TRUE;
      printf("\nrgSCHPfsDlLcGbrRefresh: UE %d lcId %d \n", ue->ueId, lc->lcId);
   }
   ue->pfsStats.lcStats[lc->lcId-1].isRecvdBo = FALSE;
   ue->pfsStats.lcStats[lc->lcId-1].lastIdx = (ue->pfsStats.lcStats[lc->lcId-1].lastIdx+1)%RGSCH_NUM_STATS_PER_REFRESH;
   if (ue->pfsStats.lcStats[lc->lcId-1].lastIdx == ue->pfsStats.lcStats[lc->lcId-1].startIdx)
   {
      ue->pfsStats.lcStats[lc->lcId-1].startIdx = (ue->pfsStats.lcStats[lc->lcId-1].startIdx+1)%RGSCH_NUM_STATS_PER_REFRESH;
   }
   ue->pfsStats.lcStats[lc->lcId-1].totGbrBytesSchd += (pfsLc->gbr - pfsLc->remGbr);
   ue->pfsStats.lcStats[lc->lcId-1].totMbrBytesSchd += (pfsLc->deltaMbr - pfsLc->remDeltaMbr);
   ue->pfsStats.lcStats[lc->lcId-1].perRefresh[ue->pfsStats.lcStats[lc->lcId-1].lastIdx].remGbr = pfsLc->remGbr;
   ue->pfsStats.lcStats[lc->lcId-1].perRefresh[ue->pfsStats.lcStats[lc->lcId-1].lastIdx].remDeltaMbr = pfsLc->remDeltaMbr;
   ue->pfsStats.lcStats[lc->lcId-1].perRefresh[ue->pfsStats.lcStats[lc->lcId-1].lastIdx].totByteSchd = (pfsLc->gbr - pfsLc->remGbr) + \
                                                                                                       (pfsLc->deltaMbr - pfsLc->remDeltaMbr);
   printf("\n\nPFS: Refresh Cycle expire for UE %d lcId %d remGbr %lu gbr %lu remDeltaMbr %lu startIdx %lu lastIdx %lu\n",
         ue->ueId, lc->lcId, pfsLc->remGbr, pfsLc->gbr, pfsLc->remDeltaMbr, ue->pfsStats.lcStats[lc->lcId-1].startIdx, ue->pfsStats.lcStats[lc->lcId-1].lastIdx);
#endif

   srvdMbr = cmnLc->mbr - pfsLc->remGbr - pfsLc->remDeltaMbr;
   
   pfsLc->maxBo4FlowCtrl = (srvdMbr * pfsLc->rcvryDurFlowCtrl) / 
                            (RG_SCH_CMN_REFRESH_TIME * 10);
   pfsLc->remGbr = pfsLc->gbr;
   pfsLc->remDeltaMbr = pfsLc->deltaMbr;
   /* Fix : Updating PFS to start prio with highest possible value
               and diminishing prio val updates from there on */
   rgSCHPfsInitFracPrioInfo(&pfsLc->fracPrioInfo, pfsLc->gbr); 
   rgSCHPfsDlUpdPfsPrio(pfsDl, pfsLc, ue, &pfsLc->fracPrioInfo, &prioChngd);

#ifdef RG_PFS_STATS
   printf("pfsPrio %lu\n\n",(unsigned long)pfsLc->pfsPrio);
#endif

   /* Fix: Updating LC/UEs position in scheduling Queues should be
    * done only if UE is Active */
   if ((RG_SCH_CMN_DL_IS_UE_ACTIVE(ue)) && pfsLc->bo)
   {
      if (pfsLc->remGbr)
      {
         /* Takes care of updating/retaining queue */
         pfsLc->effBo = RGSCH_MIN(pfsLc->bo, pfsLc->remGbr);
         rgSCHPfsDlLcAddToGbrQ(pfsDl, ue, pfsLc, prioChngd, 0);
      }
   }
   RETVOID;
}  /* rgSCHPfsDlLcGbrRefresh */


/***********************************************************
 *
 *     Func : rgSchPfsDlGetSvcPrio
 *
 *     Desc : Obtains SVC PFS priority from SVC QCI priority
 *            using the mapping table configured for cell.
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE U32 rgSchPfsDlGetSvcPrio
(
RgSchEnbPfsDl       *pfsDl,
U8                   qci
)
#else
PRIVATE U32 rgSchPfsDlGetSvcPrio(pfsDl, qci)
RgSchEnbPfsDl       *pfsDl;
U8                   qci;
#endif
{
   TRC2(rgSchPfsDlGetSvcPrio);

   RETVALUE(pfsDl->tbls.svcQciPrios[qci-1]);
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlGetTpPrio
 *
 *     Desc : Obtains TP PFS priority from TP priority
 *            table.
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE U32 rgSCHPfsDlGetTpPrio
(
RgSchEnbPfsDl       *pfsDl,
U8                   iTbs
)
#else
PRIVATE U32 rgSCHPfsDlGetTpPrio(pfsDl, iTbs)
RgSchEnbPfsDl      *pfsDl;
U8                   iTbs;
#endif
{
   TRC2(rgSCHPfsDlGetTpPrio);

   RETVALUE(pfsDl->tbls.tpPrios[iTbs]);
}




/**** UPLINK functions ****/

/**
 * @brief Uplink intiatialisation for PFS
 *
 * @details
 *
 *     Function: rgSCHPfsUlInit
 *
 *     Processing Steps:
 *     - Assigns the various callback APIs
 *
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlInit
(
RgUlSchdApis         *apis
)
#else
PUBLIC Void rgSCHPfsUlInit(apis)
RgUlSchdApis         *apis;
#endif
{
   TRC2(rgSCHPfsUlInit);

   apis->rgSCHRgrUlUeCfg     = rgSCHPfsUlUeCfg;
   apis->rgSCHRgrUlUeRecfg   = rgSCHPfsUlUeRecfg;
   apis->rgSCHFreeUlUe       = rgSCHPfsUlUeDel;
   apis->rgSCHRgrUlCellCfg   = rgSCHPfsUlCellCfg;
   apis->rgSCHRgrUlCellRecfg = rgSCHPfsUlCellRecfg; 
   apis->rgSCHFreeUlCell     = rgSCHPfsUlCellDel;
   apis->rgSCHRgrUlLcCfg     = rgSCHPfsUlLchCfg;
   apis->rgSCHRgrUlLcRecfg   = rgSCHPfsUlLchRecfg;
   apis->rgSCHRgrUlLcgCfg    = rgSCHPfsUlLcgCfg;
   apis->rgSCHRgrUlLcgRecfg  = rgSCHPfsUlLcgRecfg;
   apis->rgSCHFreeUlLcg      = rgSCHPfsUlLcgDel;
   apis->rgSCHRgrUlLchDel    = rgSCHPfsUlLchDel;
   apis->rgSCHUlSched        = rgSCHPfsUlSched;
   apis->rgSCHUpdBsrShort    = rgSCHPfsUlUpdBsrShort;
   apis->rgSCHUpdBsrTrunc    = rgSCHPfsUlUpdBsrTrunc;
   apis->rgSCHUpdBsrLong     = rgSCHPfsUlUpdBsrLong;
   apis->rgSCHContResUlGrant = rgSCHPfsUlContResReq;
   apis->rgSCHSrRcvd         = rgSCHPfsUlSrInd;
   apis->rgSCHUlCqiInd       = rgSCHPfsUlCqiInd;
   apis->rgSCHRgrUlLcgUpd    = rgSCHPfsUlLcgUpd;
   apis->rgSCHUlUeRefresh    = rgSCHPfsUlUeRefresh;
   apis->rgSCHUlAllocFnlz    = rgSCHPfsUlOnAlloc;
   apis->rgSCHUlInactvtUes   = rgSCHPfsUlInactvLstInd;
   apis->rgSCHUlActvtUe      = rgSCHPfsUlActvUeInd;
   apis->rgSCHUlUeReset      = rgSCHPfsUlUeReset;

   RETVOID;
}


/**
 * @brief Cell configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlCellCfg
 *
 *     Processing Steps:
 *      - Create the pfsDl info within passed SchCell
 *      - Update priority tables
 *      - Determine the min, max and priority ranges per
 *        PFS queue and store them
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[in]  RgrCellCfg          *cfg
 *  @param[out] RgSchErrInfo        *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlCellCfg
(
RgSchCellCb          *cell,
RgrCellCfg           *cfg,
RgSchErrInfo         *err
)
#else
PUBLIC S16 rgSCHPfsUlCellCfg(cell, cfg, err)
RgSchCellCb          *cell;
RgrCellCfg           *cfg;
RgSchErrInfo         *err;
#endif
{
   RgrEnbPfs           *pfsCfg;
   RgSchCmnUlCell      *cmnCell = RG_SCH_CMN_GET_UL_CELL(cell);
   RgSchPfsUlCell      *pfsCell;
   U32                  minTpPrio;
   U32                  maxTpPrio;
   U32                  minFairPrio;
   U32                  maxFairPrio;
   U32                  minPrio;
   U32                  maxPrio;
   U32                  maxSvcPrio;
   U32                  minGbrPrio;
   U32                  maxGbrPrio;
   U32                  minAmbrPrio;
   U32                  maxAmbrPrio;

   UNUSED(err);
   TRC2(rgSCHPfsUlCellCfg);

   pfsCfg = &rgSchCb[cell->instIdx].rgrSchedEnbCfg.ulSchInfo.ulPfs;

   if (rgSCHUtlAllocSBuf(cell->instIdx,
            (Data**)&cmnCell->schSpfc, (sizeof(RgSchPfsUlCell))) != ROK)
   {
      RETVALUE(RFAILED);
   }

   pfsCell = (RgSchPfsUlCell *)(cmnCell->schSpfc);

   pfsCell->prioScaleFact = (rgSchPfsScalingFactor[pfsCfg->tptCoeffi] * \
        rgSchPfsScalingFactor[pfsCfg->fairCoeffi]);

   /* Derive TP priority values based on TP factor */
   rgSCHPfsFillTbl(rgSchPfsTpFactorSelector[pfsCfg->tptCoeffi],
        pfsCell->tbls.tpPrios,RG_SCH_PFS_TP_FACTOR_LVLS, 
        &minTpPrio, &maxTpPrio);

   /* Derive Fairness priority values based on Fairness factor */
   rgSCHPfsFillTbl(rgSchPfsFairnessFactorSelector[pfsCfg->fairCoeffi],  
        pfsCell->tbls.fairPrios,RG_SCH_PFS_FAIRNESS_FACTOR_LVLS, 
        &minFairPrio, &maxFairPrio);

   rgSCHPfsFillTbl(&pfsCfg->qciWgt[RG_SCH_CMN_GBR_QCI_START - 1],
         &pfsCell->tbls.svcQciPrios[RG_SCH_CMN_GBR_QCI_START - 1],
         RG_SCH_CMN_GBR_QCI_END - RG_SCH_CMN_GBR_QCI_START + 1, 
         &minGbrPrio, &maxGbrPrio);

   pfsCell->tbls.svcQciPrios[4] = pfsCfg->qciWgt[4];

   rgSCHPfsFillTbl(&pfsCfg->qciWgt[RG_SCH_CMN_NGBR_QCI_START - 1],
         &pfsCell->tbls.svcQciPrios[RG_SCH_CMN_NGBR_QCI_START - 1],
         RG_SCH_CMN_NGBR_QCI_END - RG_SCH_CMN_NGBR_QCI_START + 1, 
         &minAmbrPrio, &maxAmbrPrio);

   maxSvcPrio = RGSCH_MAX(maxAmbrPrio, maxGbrPrio);
   /* Make sure that there are non-zero priority values */
   if ((maxTpPrio == 0) || (maxSvcPrio == 0) || (maxFairPrio == 0))
   {
      RLOG_ARG0(L_ERROR,DBG_CELLID,cell->cellId,
         "rgSCHPfsDlCellCfg(): Priority values are all zero");
      /* ccpu00117052 - MOD - Passing double pointer
      for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(cell->instIdx,
         (Data**)(&(cmnCell->schSpfc)), (sizeof(RgSchPfsUlCell)));
      RETVALUE(RFAILED);
   }

   /* Make sure that the product of maximum priority values dooes
    * not overflow a U32 */
   if ((maxTpPrio > ((U32)0xffffffff) / maxFairPrio)
         || (maxTpPrio * maxFairPrio > ((U32)-1) / maxSvcPrio))
   {
      RLOG_ARG0(L_ERROR,DBG_CELLID,cell->cellId, 
         "rgSCHPfsUlCellCfg(): Priority values too large");
      /* ccpu00117052 - MOD - Passing double pointer
      for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(cell->instIdx,
         (Data**)(&(cmnCell->schSpfc)), (sizeof(RgSchPfsUlCell)));
      RETVALUE(RFAILED);
   }
   minPrio = (minTpPrio * minFairPrio * minGbrPrio)/
              pfsCell->prioScaleFact;

   maxPrio = (maxTpPrio * maxFairPrio * maxGbrPrio)/
              pfsCell->prioScaleFact;


   rgSCHPfsFillRange(&pfsCell->range.gbrRange, minPrio, maxPrio,
         RG_SCH_PFS_UL_NUM_GBR_QUEUES);
   rgSCHPfsFillRange(&pfsCell->range.mbrRange, minPrio, maxPrio,
         RG_SCH_PFS_UL_NUM_MBR_QUEUES);
   /* Fix : syed MAX Initial Priority Value to be used for prio initialization. */
   pfsCell->maxPrioValGbr = maxPrio;

   /* Priority weight for QCI5  
    * is assigned with the MAX Weight factor (9)
    * this is only for SRB LC's
    */ 
   maxPrio = (maxTpPrio * maxFairPrio * pfsCell->tbls.svcQciPrios[4]) / 
              pfsCell->prioScaleFact;

   pfsCell->maxSrbDrb0PrioVal = maxPrio;

   minPrio = (minTpPrio * minFairPrio * minAmbrPrio)/
              pfsCell->prioScaleFact;
   maxPrio = (maxTpPrio * maxFairPrio * maxAmbrPrio )/
              pfsCell->prioScaleFact;

   rgSCHPfsFillRange(&pfsCell->range.ambrRange, minPrio, maxPrio,
         RG_SCH_PFS_UL_NUM_AMBR_QUEUES);
   pfsCell->maxPrioValAmbr = maxPrio;


   RETVALUE(ROK);
}

/**
 * @brief Cell reconfiguration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlCellRecfg
 *
 *     Processing Steps:
 *      - [NONE - no reconfig for PFS]
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @param[in]  RgrCellRecfg      *recfg
 *  @param[out] RgSchErrInfo      *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlCellRecfg
(
RgSchCellCb     *cell,
RgrCellRecfg    *recfg,
RgSchErrInfo    *err
)
#else
PUBLIC S16 rgSCHPfsUlCellRecfg(cell, recfg, err)
RgSchCellCb     *cell;
RgrCellRecfg    *recfg;
RgSchErrInfo    *err;
#endif
{
   /* No reconfig for PFS, so just return ROK */
   UNUSED(cell);
   UNUSED(recfg);
   UNUSED(err);
   TRC2(rgSCHPfsUlCellRecfg);

   RETVALUE(ROK);
}

/**
 * @brief Cell deletion for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlCellDel
 *
 *     Processing Steps:
 *      - Free PFS related information per cell.
 *      - [ Nothing else needs to be done.
 *        Common modules would take care of deleting
 *        each UE in the cell, during which time PFS
 *        shall be called for UE deletion. ]
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlCellDel
(
RgSchCellCb       *cell
)
#else
PUBLIC Void rgSCHPfsUlCellDel(cell)
RgSchCellCb       *cell;
#endif
{
   RgSchCmnCell *cmnCell = (RgSchCmnCell *)(cell->sc.sch);
   TRC2(rgSCHPfsUlCellDel);

   if (cmnCell->ul.schSpfc == NULLP)
   {
      RETVOID;
   }
   /* ccpu00117052 - MOD - Passing double pointer
   for proper NULLP assignment*/
   rgSCHUtlFreeSBuf(cell->instIdx,
      (Data**)(&(cmnCell->ul.schSpfc)), (sizeof(RgSchPfsUlCell)));
   RETVOID;
}

/**
 * @brief UE configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlUeCfg
 *
 *     Processing Steps:
 *      - Create the pfsUeCb
 *      - Initialise variables
 *      - [UE specific refresh timer actions to happen
 *        as part of common modules]
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgrUeCfg         *cfg
 *  @param[out] RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlUeCfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrUeCfg         *cfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsUlUeCfg(cell, ue, cfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgrUeCfg         *cfg;
RgSchErrInfo     *err;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchCmnUlUe        *cmnUe  = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchPfsUlUe        *pfsUe;
   CmLteUeCategory ueCtg = (CmLteUeCategory)(RG_SCH_CMN_GET_UE_CTGY(ue));

   UNUSED(cfg);
   UNUSED(err);

   TRC2(rgSCHPfsUlUeCfg);

   if (rgSCHUtlAllocSBuf(cell->instIdx,
            (Data**)&cmnUe->schSpfc, (sizeof(RgSchPfsUlUe))) != ROK)
   {
      RETVALUE(RFAILED);
   }
   pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   pfsUe->cqi = rgSCHCmnUlGetCqi(cell, ue, ueCtg);
   pfsUe->cqiPrio = rgSCHPfsUlGetTpPrio(pfsCell, RG_SCH_PFS_UL_MAX_ITBS);
   pfsUe->prioLnk.node = (PTR)ue;
   /* Fix : Updating PFS to start prio with highest possible value
      and diminishing prio val updates from there on. */
   pfsUe->pfsPrio = pfsCell->maxPrioValAmbr;
   rgSCHPfsInitFracPrioInfo(&pfsUe->fracPrioInfo, ue->ul.cfgdAmbr); 

   RETVALUE(ROK);
}

/**
 * @brief UE reconfiguration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlUeRecfg
 *
 *     Processing Steps:
 *     - [NONE]
 *
 *  @param[in]   RgSchCellCb      *cell
 *  @param[in]   RgSchUeCb        *ue
 *  @param[in]   RgrUeRecfg       *recfg
 *  @param[out]  RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlUeRecfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrUeRecfg       *recfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsUlUeRecfg(cell, ue, recfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgrUeRecfg       *recfg;
RgSchErrInfo     *err;
#endif
{
   /* Updation of max bitrate etc is done by common.
      Ue state(csg/non-csg) is updated in common, 
      here we are updating s queue */
   TRC2(rgSCHPfsUlUeRecfg);
   if ((rgSchCb[cell->instIdx].rgrSchedEnbCfg.accsMode == RGR_CELL_ACCS_HYBRID) &&
      (recfg->ueRecfgTypes & RGR_UE_CSG_PARAM_RECFG))
   {
      rgSCHPfsUlRmvUeFrmQ(cell, ue);
      rgSCHPfsUlMngUeInQ(cell, ue, 0);
   }
   RETVALUE(ROK);
}

/**
 * @brief UE delete for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlUeDel
 *
 *     Processing Steps:
 *     - [Removal of UE allocs to happen as part
 *       of common modules]
 *     - Remove UE from any queue if present
 *     - Free UE sched info
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @param[in]  RgSchUeCb         *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlUeDel
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHPfsUlUeDel(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   RgSchCmnUlUe       *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchPfsUlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);

   TRC2(rgSCHPfsUlUeDel);

   if (pfsUe == NULLP)
   {
      RETVOID;
   }
   rgSCHPfsUlRmvUeFrmQ(cell, ue);
   /* ccpu00117052 - MOD - Passing double pointer
   for proper NULLP assignment*/
   rgSCHUtlFreeSBuf(cell->instIdx,
      (Data**)(&(cmnUe->schSpfc)), (sizeof(RgSchPfsUlUe)));
   RETVOID;
}

/**
 * @brief UE reset for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlUeReset
 *
 *     Processing Steps:
 *      - [Common is expected to remove retx HARQ procs and invoke API]
 *      - Remove UE from queue if present
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlUeReset
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHPfsUlUeReset(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);

   TRC2(rgSCHPfsUlUeReset);

   pfsUe->srRcvd = FALSE;
   rgSCHPfsUlRmvUeFrmQ(cell, ue);
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsUlAddLcToLcg
 *        
 *     Desc : Insert Lc to Lc queue present in Lcg in descending order of 
 *               Qci Priority
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlAddLcToLcg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
U8               lcgId,
RgSchPfsUlLc     *pfsUlLc
)
#else
PRIVATE Void rgSCHPfsUlAddLcToLcg(cell, ue, lcgId, pfsUlLc)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
U8               lcgId;
RgSchPfsUlLc     *pfsUlLc;
#endif
{
   RgSchCmnUlCell      *cmnCell = RG_SCH_CMN_GET_UL_CELL(ue->cell);
   RgSchPfsUlCell      *pfsCell = (RgSchPfsUlCell *)(cmnCell->schSpfc);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   RgSchPfsUlLc        *pfsUlLcTmp;
   CmLList             *node;
   U32                 nodePrio;
   U32                 qciPrio;
   CmLListCp           *cp;

   TRC2(rgSCHPfsUlAddLcToLcg);

   qciPrio = pfsCell->tbls.svcQciPrios[pfsUlLc->qci - 1];
   cp = &pfsUe->schedLcgInfo[lcgId].lcQciInfo;
   node = cp->first;
   while(node)
   {
      pfsUlLcTmp = (RgSchPfsUlLc *)(node->node);
	     nodePrio = pfsCell->tbls.svcQciPrios[pfsUlLcTmp->qci - 1];
      if (nodePrio <= qciPrio)
      {
         break;
      }
      node = node->next;
   }
   if (NULLP == node)
   {
      cmLListAdd2Tail(cp, &pfsUlLc->nodeLnk);
   }
   else
   {
      cp->crnt = node;
      cmLListInsCrnt(cp, &pfsUlLc->nodeLnk);
   }

   RETVOID;
}

/**
 * @brief UE Lc Config for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlLchCfg
 *
 *     Processing Steps:
 *      - Configure Lc in Lcg and update lcg priority if required 
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgrLchCfg        *cfg 
 *  @param[in]  RgSchErrInfo     *err 
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlLchCfg 
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrLchCfg        *cfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsUlLchCfg(cell, ue, cfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgrLchCfg        *cfg;
RgSchErrInfo     *err;
#endif
{
   RgSchCmnUlCell      *cmnCell = RG_SCH_CMN_GET_UL_CELL(cell);
   RgSchPfsUlCell      *pfsCell = (RgSchPfsUlCell *)(cmnCell->schSpfc);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   U8                  cfgLcgId = cfg->ulLchQciInfo.lcgId; 
   U8                  cfgLcId = cfg->ulLchQciInfo.lcId;
   U8                  cfgQci = cfg->ulLchQciInfo.qci;
   RgSchPfsUlLc        *pfsUlLc;
   CmLListCp           *cp;


   TRC2(rgSCHPfsUlLchCfg);
   
   if (rgSCHUtlAllocSBuf(cell->instIdx,
            (Data**)&pfsUlLc, (sizeof(RgSchPfsUlLc))) != ROK)
   {
      RETVALUE(RFAILED);
   }
   
   /*
    * Setting the qci value to higest value of qci5
    * for lcg0.grouping:lcg0->srb's,drb0  
    */
   if(RG_SCH_LCG0 == cfgLcgId)
   {
      cfgQci = RG_SCH_QCI5;
   }
   
   cp = &pfsUe->schedLcgInfo[cfgLcgId].lcQciInfo;
   
   pfsUlLc->lcId = cfgLcId;
   pfsUlLc->qci = cfgQci;
   pfsUlLc->nodeLnk.node = (PTR)pfsUlLc;

   rgSCHPfsUlAddLcToLcg(cell, ue, cfgLcgId, pfsUlLc);
   
   pfsUe->schedLcgInfo[cfgLcgId].lcgPrio = pfsCell->tbls.svcQciPrios[\
                           ((RgSchPfsUlLc *)(cp->first->node))->qci - 1];

   RETVALUE(ROK);
}
 
/**
 * @brief UE Lc Reconfig for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlLchRecfg
 *
 *     Processing Steps:
 *      - Reconfigure Lc in Lcg and update lcg priority if required 
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgrLchRecfg      *recfg 
 *  @param[in]  RgSchErrInfo     *err 
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlLchRecfg 
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrLchRecfg      *recfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsUlLchRecfg(cell, ue, recfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgrLchRecfg      *recfg;
RgSchErrInfo     *err;
#endif
{
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   U8                  reCfgLcgId = recfg->ulLchQciInfo.lcgId; 
   U8                  reCfgLcId = recfg->ulLchQciInfo.lcId;
   U8                  reCfgQci = recfg->ulLchQciInfo.qci;
   CmLListCp           *cp;
   CmLList             *node;
   RgSchPfsUlLc        *pfsUlLcTmp;

   TRC2(rgSCHPfsUlLchRecfg);
   
   /*
    * Setting the qci value to higest value of qci5
    * for lcg0.grouping:lcg0->srb's,drb0  
    */

   if(RG_SCH_LCG0 == reCfgLcgId)
   {
      reCfgQci= RG_SCH_QCI5;
   }

   cp = &pfsUe->schedLcgInfo[reCfgLcgId].lcQciInfo;
   node = cp->first;
   while(node)
   {
      pfsUlLcTmp = (RgSchPfsUlLc *)(node->node);
      if(reCfgLcId == pfsUlLcTmp->lcId)
      {
         if(reCfgQci == pfsUlLcTmp->qci)
         {
            RETVALUE(ROK);
         }
         cmLListDelFrm(cp, &pfsUlLcTmp->nodeLnk);
         pfsUlLcTmp->qci = reCfgQci;
         rgSCHPfsUlAddLcToLcg(cell, ue, reCfgLcgId, pfsUlLcTmp);
         break;
      }
      node = node->next;
   }
   
   RETVALUE(ROK);
}

/**
 * @brief LC configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlLcgCfg
 *
 *     Processing Steps:
 *     - NONE
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchUlLcCb      *lcg
 *  @param[in]  RgrLcgCfg        *cfg
 *  @param[out] RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlLcgCfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchLcgCb       *lcg,
RgrLcgCfg        *cfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsUlLcgCfg(cell, ue, lcg, cfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchLcgCb       *lcg;
RgrLcgCfg        *cfg;
RgSchErrInfo     *err;
#endif
{
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   RgSchCmnLcg *cmnLcg = ((RgSchCmnLcg *)(ue->ul.lcgArr[lcg->lcgId].sch));
   TRC2(rgSCHPfsUlLcgCfg);

   if (RGSCH_IS_GBR_BEARER(cmnLcg->cfgdGbr))
   {
      rgSCHPfsInitFracPrioInfo(&pfsUe->schedLcgInfo[lcg->lcgId].fracPrioInfo, cmnLcg->cfgdGbr);	  
   }

   RETVALUE(ROK);
}

/**
 * @brief LC re-configuration for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlLcgRecfg
 *
 *     Processing Steps:
 *     - NONE
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchLcgCb       *lcg
 *  @param[in]  RgrLcgRecfg      *recfg
 *  @param[out] RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlLcgRecfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchLcgCb       *lcg,
RgrLcgRecfg      *recfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHPfsUlLcgRecfg(cell, ue, lcg, recfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchLcgCb       *lcg;
RgrLcgRecfg      *recfg;
RgSchErrInfo     *err;
#endif
{
   /* Need not do anything */
   UNUSED(cell);
   UNUSED(ue);
   UNUSED(lcg);
   UNUSED(recfg);
   UNUSED(err);
   TRC2(rgSCHPfsUlLcgRecfg);

   RETVALUE(ROK);
}

/**
 * @brief LC deletion for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlLchDel
 *
 *     Processing Steps:
 *     - Delete Lc from Lcg 
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  CmLteLcId        lcId
 *  @param[in]  U8               lcgId 
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlLchDel
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
CmLteLcId        lcId,
U8               lcgId
)
#else
PUBLIC S16 rgSCHPfsUlLchDel(cell, ue, lcId, lcgId)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
CmLteLcId        lcId;
U8               lcgId;
#endif
{
   RgSchCmnUlCell      *cmnCell = RG_SCH_CMN_GET_UL_CELL(cell);
   RgSchPfsUlCell      *pfsCell = (RgSchPfsUlCell *)(cmnCell->schSpfc);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   RgSchPfsUlLc        *pfsUlLc;
   CmLList             *node;
   CmLListCp           *cp;

   TRC2(rgSCHPfsUlLchDel);

   cp = &pfsUe->schedLcgInfo[lcgId].lcQciInfo;
   node = cp->first;
   while(node)
   {
      pfsUlLc = (RgSchPfsUlLc *)(node->node);
      if(lcId == pfsUlLc->lcId)
      {
         cmLListDelFrm(cp, &pfsUlLc->nodeLnk);
         pfsUlLc->nodeLnk.node = NULLP;
         rgSCHUtlFreeSBuf(cell->instIdx,
               (Data**)(&pfsUlLc), (sizeof(RgSchPfsUlLc)));
         break;
      }
      node = node->next;
   }
   if(cp->first)
   {
      pfsUe->schedLcgInfo[lcgId].lcgPrio = pfsCell->tbls.svcQciPrios[\
                         ((RgSchPfsUlLc *)(cp->first->node))->qci - 1];
   }
   
   RETVALUE(ROK);
}

/**
 * @brief LC deletion for PFS
 *
 * @details
 *
 *     Function : rgSCHPfsUlLcgDel
 *
 *     Processing Steps:
 *     - Update UE's position in queues if needed
 *       [Assumed that lcg's bs has been set to zero]
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchLcgCb       *lcg
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlLcgDel
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchLcgCb       *lcg
)
#else
PUBLIC Void rgSCHPfsUlLcgDel(cell, ue, lcg)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchLcgCb       *lcg;
#endif
{
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);

   TRC2(rgSCHPfsUlLcgDel);

   rgSCHPfsUlMngUeInQ(cell, ue, 0);
   cmLListInit(&(pfsUe->schedLcgInfo[lcg->lcgId].lcQciInfo));

   RETVOID;
}


/**
 * @brief UL UE refresh
 *
 * @details
 *
 *     Function : rgSCHPfsUlUeRefresh
 *
 *     Processing Steps:
 *     - Update UE's position in queues if needed
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlUeRefresh
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PUBLIC Void rgSCHPfsUlUeRefresh(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   U8                  lcgId;
   TRC2(rgSCHPfsUlUeRefresh);
  
   /* Fix : Updating PFS to start prio with highest possible value
      and diminishing prio val updates from there on. */
   pfsUe->cqiPrio = rgSCHPfsUlGetTpPrio(pfsCell, RG_SCH_PFS_UL_MAX_ITBS);
   pfsUe->schedSinceRefresh = FALSE;
   rgSCHPfsInitFracPrioInfo(&pfsUe->fracPrioInfo, ue->ul.cfgdAmbr); 
   /* Max bitrate being refreshed would happen as part of common processing,
    * which would also update effBsr */
   for (lcgId = 1; lcgId < RGSCH_MAX_LCG_PER_UE; lcgId++)
   {
      if (RGSCH_LCG_ISCFGD(&ue->ul.lcgArr[lcgId]))
      {
         RgSchCmnLcg *cmnLcg = ((RgSchCmnLcg *)(ue->ul.lcgArr[lcgId].sch));
         if (RGSCH_IS_GBR_BEARER(cmnLcg->cfgdGbr))
         {
            rgSCHPfsInitFracPrioInfo(&pfsUe->schedLcgInfo[lcgId].fracPrioInfo, cmnLcg->cfgdGbr); 
         }
      }
   }

   rgSCHPfsUlMngUeInQ(cell, ue, 0);
   RETVOID;
}

/**
 * @brief UL Lcg received data updation
 *
 * @details
 *
 *     Function : rgSCHPfsUlLcgUpd
 *
 *     Processing Steps:
 *     - Update fractional prio as well as position of UE in respective 
 *        Queues
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @param[in]  RgInfUeDatInd      *datInd
 *  @return  S16
 **/
#ifdef ANSI
PUBLIC S16 rgSCHPfsUlLcgUpd
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgInfUeDatInd       *datInd
)
#else
PUBLIC S16 rgSCHPfsUlLcgUpd(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgInfUeDatInd       *datInd;
#endif
{
   U8 idx = 0;
   U8  lcgId;
   RgSchPfsUlUe   *pfsUe   = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   
   TRC2(rgSCHPfsUlLcgUpd);
   
   for (idx = 0; (idx < RGINF_MAX_LCG_PER_UE - 1); idx++)
   {
      if (datInd->lcgInfo[idx].bytesRcvd != 0)
      {
         lcgId = datInd->lcgInfo[idx].lcgId;
         RgSchCmnLcg *cmnLcg = ((RgSchCmnLcg *)(ue->ul.lcgArr[lcgId].sch));
         if (RGSCH_LCG_ISCFGD(&ue->ul.lcgArr[lcgId]))
         {
            if (RGSCH_IS_GBR_BEARER(cmnLcg->cfgdGbr))
            {
               if((0 == cmnLcg->effGbr) && (((0 != cmnLcg->deltaMbr ) && 
                  (datInd->lcgInfo[idx].bytesRcvd > (cmnLcg->deltaMbr - cmnLcg->effDeltaMbr)))))
               {
                  rgSCHPfsInitFracPrioInfo(&pfsUe->schedLcgInfo[lcgId].fracPrioInfo, 
                     cmnLcg->deltaMbr); 
                  rgSCHPfsUpdFracPrioInfo(&pfsUe->schedLcgInfo[lcgId].fracPrioInfo, 
                     cmnLcg->deltaMbr-cmnLcg->effDeltaMbr);
               }
               else
               { 
                  rgSCHPfsUpdFracPrioInfo(&pfsUe->schedLcgInfo[lcgId].fracPrioInfo, 
                    datInd->lcgInfo[idx].bytesRcvd);
               }
	    }
	    else
	    {
               rgSCHPfsUpdFracPrioInfo(&pfsUe->fracPrioInfo, datInd->lcgInfo[idx].bytesRcvd); 
	    }
            rgSCHPfsUlMngUeInQ(cell, ue, 0);
         }
         else
         {
            printf("ERROR:Data on LcgId=%u\n",lcgId);  
         }
      }
      else
      {
         break;
      }
   }
   RETVALUE(ROK);  
}

/**
 * @brief  Utility function to insert the UE node into UE Lst based on the
 *         number of subband share allocated for the UE for the current TTI.
 *
 * @details
 *
 *     Function : rgSCHPfsSortInsUeLst
 *
 *     If subbandShare < Min, then insert at head
 *     Else If subbandShare > Max, then insert at tail
 *     Else, traverse the list and place the node at the appropriate place
 *
 *  @param[in]  RgSchCellCb  *cell
 *  @param[in]  RgSchUeCb    *ue
 *  @return     U8
 **/
#ifdef ANSI
PRIVATE U8 rgSCHPfsSortInsUeLst
(
RgSchCellCb  *cell,
CmLListCp    *ueLst,               /* list control point */
RgSchUeCb    *ue
)
#else
PRIVATE U8 rgSCHPfsSortInsUeLst (cell, ueLst, ue)
RgSchCellCb  *cell;
CmLListCp    *ueLst;
RgSchUeCb    *ue;
#endif
{
   CmLList      *ueInLst;
   CmLList      *firstUeInLst;
   RgSchUeCb    *tempUe;
   RgSchCmnUe   *schCmnUe = RG_SCH_CMN_GET_UE(ue,cell);
   RgSchCmnUlUe *ueUl = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchCmnUlUe *tmpUeUl;
   RgSchCmnUeUlAlloc  *schCmnUeUlAlloc = &(schCmnUe->ul.alloc);

   firstUeInLst = cmLListFirst(ueLst);
   if(NULLP == firstUeInLst)
   {
      /* first node to be added to the list */
      cmLListAdd2Tail(ueLst,&(schCmnUeUlAlloc->reqLnk));
      RETVALUE(ROK);
   }

   if(0 == ueUl->subbandShare)
   {
      /* add the UE's who doesnt get the BW at the end
       * This is done to handle the leftover Sb's during 
       * RB allocation */
      cmLListAdd2Tail(ueLst, &(schCmnUeUlAlloc->reqLnk));
      RETVALUE(ROK);
   }


   /* This ue needs to be in the middle
    * Search and insert the Ue
    */
   ueInLst = cmLListFirst(ueLst);
   do
   {
      tempUe = (RgSchUeCb *)(ueInLst->node);

      tmpUeUl = RG_SCH_CMN_GET_UL_UE(tempUe, cell);

      if(ueUl->subbandShare <= tmpUeUl->subbandShare)
      {
         cmLListInsCrnt(ueLst, &(schCmnUeUlAlloc->reqLnk));
         break;
      }

      if(0 == tmpUeUl->subbandShare)
      {
         cmLListInsCrnt(ueLst, &(schCmnUeUlAlloc->reqLnk));
         break;
      }

      if((NULLP == ueInLst->next) || (ueInLst->next == firstUeInLst))
      {/* this is the last non zero ue in the list*/
         cmLListInsAfterCrnt(ueLst, &(schCmnUeUlAlloc->reqLnk));
         break;
      }
      ueInLst = cmLListNext(ueLst);

   } while(NULLP != ueInLst && ueInLst != firstUeInLst);

   RETVALUE(ROK);
}

/**
 * @brief 
 *
 * @details
 *
 *     Function : 
 *
 *     Processing Steps:
 *
 *  @param[in]  RgSchCellCb             *cell
 *  @param[in]  RgSchPfsLcSchdInfo      *lcToBeSchedInfo
 *  @param[in]  CmLListCp               *toBeSchedUeLst
 *  @param[in]  RgSchCmnUlRbAllocInfo   *alloc
 *  @param[in]  U32                     *numUsedSbs
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDistributeSbs
(
RgSchCellCb                  *cell,
RgSchPfsLcSchdInfo           *lcToBeSchedInfo,
CmLListCp                    *toBeSchedUeLst,
RgSchCmnUlRbAllocInfo        *alloc,
U32                          *numUsedSbs
)
#else
PRIVATE Void rgSCHPfsDistributeSbs(cell, lcToBeSchedInfo, toBeSchedUeLst, alloc, numUsedSbs)
RgSchCellCb                  *cell;
RgSchPfsLcSchdInfo           *lcToBeSchedInfo;
CmLListCp                    *toBeSchedUeLst;
RgSchCmnUlRbAllocInfo        *alloc;
U32                          *numUsedSbs;
#endif
{
   CmLList          *lnk;
   U8               remUeCount;
   U8               availSbs;                /* Total available Sub-bands */
   U8               sbSharePerUe;            /* Sub-band share for per UE */
   U8               leftOverSbShare;         /* Left over sub-band share from scheduled UEs */
   U8               leftOverSbShareForNxtUe; /* Left over sub-band share for UE to be scheduled next */
   U8               freeSbs;                 /* Remaining Sub-bands available for scheduling */ 
   U8               sbAvailForUe;            /* Total Subband available for all same UEs categorized by CSG membership */
   U32              currTotPfsPrio;          /* Total Pfs priority for all UEs based on CSG Membership */

   TRC2(rgSCHPfsDistributeSbs);

   availSbs    = (alloc->sf->availSubbands - (*numUsedSbs));
   freeSbs     = availSbs;
   remUeCount  = toBeSchedUeLst->count;
   leftOverSbShare         = 0;
   leftOverSbShareForNxtUe = 0;

   /* if there are no UE available for scheduling or 
    * if there are no SBs available for distribution */
   if((!remUeCount) || (alloc->sf->availSubbands < (*numUsedSbs)))
   {
      RETVOID;
   }

   /* Perform distribtion and do insertion sort to ueLst*/
   for (lnk = toBeSchedUeLst->first; lnk ; lnk = lnk->next)
   {
      RgSchUeCb          *ue = (RgSchUeCb *)lnk->node;
      RgSchCmnUlUe       *ueUl = RG_SCH_CMN_GET_UL_UE(ue, cell);
      RgSchCmnUeUlAlloc  *ulAllocInfo = &((RG_SCH_CMN_GET_UL_UE(ue, cell))->alloc);
      RgSchPfsUlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);

      /* calculate Sb's required */
      if(remUeCount > 1)
      {
         if ((lcToBeSchedInfo->currPrioMmbrSta == TRUE) && (ue->csgMmbrSta == TRUE))
         {
            sbAvailForUe   = lcToBeSchedInfo->prioUeBwAvail;
            currTotPfsPrio = lcToBeSchedInfo->prioUeTotPfsPrio;
         }
         else
         {
            sbAvailForUe   = lcToBeSchedInfo->nonPrioUeBwAvail;
            currTotPfsPrio = lcToBeSchedInfo->otherUeTotPfsPrio - lcToBeSchedInfo->prioUeTotPfsPrio;
         }

         sbSharePerUe        = ((pfsUe->pfsPrio * sbAvailForUe) / currTotPfsPrio) + 
                                leftOverSbShare + leftOverSbShareForNxtUe;

         ueUl->subbandShare = RGSCH_MAX(RGSCH_MIN(sbSharePerUe, ueUl->subbandRequired), 1);

         leftOverSbShare        += ((sbSharePerUe - ueUl->subbandShare)/
                                    (remUeCount - 1));
         leftOverSbShareForNxtUe = ((sbSharePerUe - ueUl->subbandShare)%
                                    (remUeCount -1));
      }
      else
      {/* remUeCount == 1*//* to handle left overs due to integer division*/
         ueUl->subbandShare = RGSCH_MIN(freeSbs, ueUl->subbandRequired);
      }

      *numUsedSbs        += ueUl->subbandShare;

      freeSbs -= ueUl->subbandShare;
      /* handle the left over case */
      /* add to UeLst in the in descending order */
      /* Ue's with 0 share should be added at the end */
      if (ulAllocInfo->reqLnk.node == NULLP)
      {
         if(ROK == rgSCHPfsSortInsUeLst(cell, &alloc->ueLst, ue))
         {
            ulAllocInfo->reqLnk.node = (PTR)ue;
         }
      }
      if(!(--remUeCount))
      {
         break;
      }

   }

   RETVOID;
}

/**
 * @brief Uplink scheduling function
 *
 * @details
 *
 *     Function : rgSCHPfsUlSched
 *
 *     Processing Steps:
 *     - Schedule for new transmissions
 *
 *  @param[in]  RgSchCellCb             *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo   *alloc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlSched
(
RgSchCellCb             *cell,
RgSchCmnUlRbAllocInfo   *alloc
)
#else
PUBLIC Void rgSCHPfsUlSched(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
#endif
{
   RgSchCmnUlCell  *cmnCell = RG_SCH_CMN_GET_UL_CELL(cell);
   U8               remUe = cmnCell->maxUeNewTxPerTti;
   TRC2(rgSCHPfsUlSched);

   rgSCHPfsUlSchedNewTx(cell, alloc, remUe);
   RETVOID;
}

/**
 * @brief Uplink scheduling function
 *
 * @details
 *
 *     Function : rgSCHPfsUlSchedNewTx
 *
 *     Processing Steps:
 *     - Schedule new tranmissions upto the limit of
 *       maximum UEs that can be considered for new tx
 *       in a TTI. Go through cell wide uplink
 *       queues in the following order:
 *       - Schedule UEs in contResLst for contention
 *         resolution (schedule for small TB size)
 *       - Schedule UEs corresponding to appearance
 *         in SRB queue: If BO is zero (SR case)
 *         schedule the smallest TB possible
 *       - Schedule UEs corresponding to appearance
 *         in other queues
 *     - Note: During each step of scheduling a UE
 *       - Verify that UE has not been scheduled for
 *         retx already
 *       - Set HARQ process contents corresponding to
 *         new transmission and allocation
 *       - Add UE to queue in 'alloc' and update 'alloc'
 *         info
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo  *alloc
 *  @param[in]  U8                      remUe
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlSchedNewTx
(
RgSchCellCb             *cell,
RgSchCmnUlRbAllocInfo   *alloc,
U8                       remUe
)
#else
PRIVATE Void rgSCHPfsUlSchedNewTx(cell, alloc, remUe)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
U8                       remUe;
#endif
{
   RgSchPfsUlCell      *pfsCell;
   RgSchCmnCell        *schCmnCell;
   CmLListCp         *txQMbr1, *txQMbr2, *txQAmbr1, *txQAmbr2;
   U8                  remAllocs;
   U32                 usedSbs;        /* Allocated Subbands */
   U32                 availSbs;       /* Available Subbands for allocation */
   U32                 prioUesSbLimit; /* Subband limit for priority UEs in case of a mix of CSG & nCSG UEs */
   CmLListCp         *txQ;
   S16               idx;
   RgSchPfsLcSchdInfo  lcToBeSchedInfo;

   TRC2(rgSCHPfsUlSchedNewTx);

   pfsCell     = RG_SCH_PFS_GET_PFSCELLUL(cell);
   schCmnCell  = (RgSchCmnCell *)(cell->sc.sch);
   usedSbs     = 0;
   availSbs    = alloc->sf->availSubbands;
   remAllocs   = schCmnCell->ul.maxAllocPerUlSf - *alloc->sf->allocCountRef;
   cmLListInit(&lcToBeSchedInfo.ceLcLst);
   cmLListInit(&lcToBeSchedInfo.otherUeLcLst);
   lcToBeSchedInfo.ceTotPfsPrio = 0;
   lcToBeSchedInfo.otherUeTotPfsPrio = 0;
   lcToBeSchedInfo.totBwReq            = 0;
   lcToBeSchedInfo.totPrioBwReq        = 0;
   lcToBeSchedInfo.totNonPrioBwReq     = 0;
   lcToBeSchedInfo.numPrioUe           = 0;
   lcToBeSchedInfo.prioUeTotPfsPrio    = 0;

   /* Getting the priority for scheduling csg or non-csg */
   lcToBeSchedInfo.currPrioMmbrSta = rgSCHCmnIsUlCsgPrio(cell);
   if (lcToBeSchedInfo.currPrioMmbrSta == TRUE)
   {
      txQMbr1 = pfsCell->txQueues.prioMbrLst;
      txQMbr2 = pfsCell->txQueues.normMbrLst;
      txQAmbr1 = pfsCell->txQueues.prioAmbrLst;
      txQAmbr2 = pfsCell->txQueues.normAmbrLst;
      prioUesSbLimit = (availSbs  * (100 - cell->minUlResNonCsg))/100;
   }
   else
   {
      txQMbr1 = pfsCell->txQueues.normMbrLst;
      txQMbr2 = pfsCell->txQueues.prioMbrLst;
      txQAmbr1 = pfsCell->txQueues.normAmbrLst;
      txQAmbr2 = pfsCell->txQueues.prioAmbrLst;
      prioUesSbLimit = (availSbs * cell->minUlResNonCsg)/100;
   }
   lcToBeSchedInfo.prioUeBwAvail = availSbs;
   

   /* Fix:ccpu00120610 consider remaining allocs in a subframe, because allocs may
    * have been consumed earlier as part of msg3 allocation.
    * Note: this needs to be carried over to other schedulers. */
   if (remUe > remAllocs)
   {
      remUe = remAllocs;
   }
   /* MS_WORKAROUND : Limiting one PUSCH per UL SF */
   /* MUE_PERTTI_UL: TODO: Remove this workaround and test */

   rgSCHPfsUlSchedContRes(cell, alloc, &remUe, &usedSbs);

   rgSCHPfsUlSchedSig(cell, alloc, &remUe, &lcToBeSchedInfo);
   
   for (idx = RG_SCH_PFS_UL_NUM_GBR_QUEUES-1; remUe && (idx >= 0); --idx)
   {
      txQ = &pfsCell->txQueues.gbrLst[idx];
      rgSCHPfsUlSchedDat(cell, alloc, txQ, &remUe, &lcToBeSchedInfo);
   }

   for (idx = RG_SCH_PFS_UL_NUM_MBR_QUEUES-1; remUe && (idx >= 0); --idx)
   {
      txQ = &txQMbr1[idx];
      rgSCHPfsUlSchedDat(cell, alloc, txQ, &remUe, &lcToBeSchedInfo);
   }

   for (idx = RG_SCH_PFS_UL_NUM_MBR_QUEUES-1; remUe && (idx >= 0); --idx)
   {
      txQ = &txQMbr2[idx];
      rgSCHPfsUlSchedDat(cell, alloc, txQ, &remUe, &lcToBeSchedInfo);
   }

   for (idx = RG_SCH_PFS_UL_NUM_AMBR_QUEUES-1; remUe && (idx >= 0); --idx)
   {
      txQ = &txQAmbr1[idx];
      rgSCHPfsUlSchedDat(cell, alloc, txQ, &remUe, &lcToBeSchedInfo);
   }

   for (idx = RG_SCH_PFS_UL_NUM_AMBR_QUEUES-1; remUe && (idx >= 0); --idx)
   {
      txQ = &txQAmbr2[idx];
      rgSCHPfsUlSchedDat(cell, alloc, txQ, &remUe, &lcToBeSchedInfo);
   }
    /* Allot the remaining SBs to the non-priority UEs in case the priority UEs
      are not using up bandwidth reserved for them */
   if (lcToBeSchedInfo.numPrioUe == 0)
   {
      prioUesSbLimit = 0;
      lcToBeSchedInfo.prioUeBwAvail = 0;
   }
   else if (lcToBeSchedInfo.numPrioUe < (lcToBeSchedInfo.ceLcLst.count +
                   lcToBeSchedInfo.otherUeLcLst.count))
   {
      /* This case will hit only when there is a mix of CSG and nCSG UEs
         to be scheduled */
      if (lcToBeSchedInfo.totPrioBwReq > prioUesSbLimit)
      {
         if (lcToBeSchedInfo.totNonPrioBwReq < (availSbs - prioUesSbLimit))
         {
            lcToBeSchedInfo.prioUeBwAvail = availSbs - lcToBeSchedInfo.totNonPrioBwReq;
         }
         else
         {
            lcToBeSchedInfo.prioUeBwAvail = prioUesSbLimit;
         }
      }
      else
      {
         lcToBeSchedInfo.prioUeBwAvail = lcToBeSchedInfo.totPrioBwReq;
      }
   }
   else
   {
      lcToBeSchedInfo.prioUeBwAvail = availSbs;
   }
   lcToBeSchedInfo.nonPrioUeBwAvail = availSbs - lcToBeSchedInfo.prioUeBwAvail;

   rgSCHPfsDistributeSbs(cell, &lcToBeSchedInfo, &lcToBeSchedInfo.otherUeLcLst, alloc, &usedSbs);
   RETVOID;
}


/**
 * @brief Uplink scheduling function
 *
 * @details
 *
 *     Function : rgSCHPfsUlSchedContRes
 *
 *     Processing Steps:
 *     - Schedule for UEs for which contention resolution
 *       is pending. Small allocations are scheduled
 *       for such UEs (enough to hold BSR), independent
 *       of current BSR status.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo  *alloc
 *  @param[in,out]  U8                 *remUeRef
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlSchedContRes
(
RgSchCellCb             *cell,
RgSchCmnUlRbAllocInfo   *alloc,
U8                      *remUeRef,
U32                     *numCntResSbs
)
#else
PRIVATE Void rgSCHPfsUlSchedContRes(cell, alloc, remUeRef, numCntResSbs)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
U8                      *remUeRef;
U32                     *numCntResSbs;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   CmLListCp           *q       = &pfsCell->txQueues.contResLst;
   CmLList             *lnk;
#ifdef LTEMAC_HDFDD
   Bool                ulAllowed = FALSE;
#endif
   U8        subBandsReqd = 0;

   TRC2(rgSCHPfsUlSchedContRes);

   for (lnk = q->first; lnk && *remUeRef; lnk = lnk->next)
   {
      RgSchUeCb          *ue = (RgSchUeCb *)lnk->node;

#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddChkUlAllow (cell, ue, &ulAllowed);
         if (ulAllowed == FALSE)
         {
            continue;
         }
      }
#endif
      if (rgSCHPfsUlSchedUeForContRes(cell, alloc, ue) == ROK)
      {
         --*remUeRef;
      }
      rgSchUtlGetNumSbs(cell, ue, numCntResSbs);
      subBandsReqd += *numCntResSbs;
   }
   *numCntResSbs = subBandsReqd;

   RETVOID;
}

/**
 * @brief Uplink scheduling function
 *
 * @details
 *
 *     Function : rgSCHPfsUlSchedSig
 *
 *     Processing Steps:
 *     - Schedule for UEs for which SR is pending or
 *       which have data pending on LCG 0 (expected
 *       to correspond to signaling information)
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo  *alloc
 *  @param[in,out]  U8                 *remUeRef
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlSchedSig
(
RgSchCellCb             *cell,
RgSchCmnUlRbAllocInfo   *alloc,
U8                      *remUeRef,
RgSchPfsLcSchdInfo      *toBeSchedInfo
)
#else
PRIVATE Void rgSCHPfsUlSchedSig(cell, alloc, remUeRef, toBeSchedInfo)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
U8                      *remUeRef;
RgSchPfsLcSchdInfo      *toBeSchedInfo;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   CmLListCp           *q       = &pfsCell->txQueues.sigLst;
   CmLList             *lnk;
#ifdef LTEMAC_HDFDD
   Bool                ulAllowed = FALSE;
#endif

   TRC2(rgSCHPfsUlSchedSig);

   for (lnk = q->first; lnk && *remUeRef; lnk = lnk->next)
   {
      RgSchUeCb          *ue = (RgSchUeCb *)lnk->node;
#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddChkUlAllow (cell, ue, &ulAllowed);
         if (ulAllowed == FALSE)
         {
            continue;
         }
      }
#endif
      if (ROK == rgSCHPfsUlSchedUeForSigDat(cell, alloc, ue,
               toBeSchedInfo))
      {
         --*remUeRef;
      }
   }

   RETVOID;
}

/**
 * @brief Uplink scheduling function
 *
 * @details
 *
 *     Function : rgSCHPfsUlSchedDat
 *
 *     Processing Steps:
 *     - Schedule for UEs which have data pending
 *       on LCG 1/2/3
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo  *alloc
 *  @param[in,out]  U8                 *remUeRef
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlSchedDat
(
RgSchCellCb             *cell,
RgSchCmnUlRbAllocInfo   *alloc,
CmLListCp               *txQ,
U8                      *remUeRef,
RgSchPfsLcSchdInfo      *toBeSchedInfo
)
#else
PRIVATE Void rgSCHPfsUlSchedDat(cell, alloc, txQ, remUeRef, toBeSchedInfo)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
CmLListCp               *txQ,
U8                      *remUeRef;
RgSchPfsLcSchdInfo      *toBeSchedInfo;
#endif
{
   CmLList             *lnk;
#ifdef LTEMAC_HDFDD
   Bool                ulAllowed = FALSE;
#endif

   TRC2(rgSCHPfsUlSchedDat);

   for (lnk = txQ->first; lnk && *remUeRef; lnk = lnk->next)
   {
      RgSchUeCb          *ue = (RgSchUeCb *)lnk->node;
#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddChkUlAllow (cell, ue, &ulAllowed);
         if (ulAllowed == FALSE)
         {
            continue;
         }
      }
#endif
      if (ROK == rgSCHPfsUlSchedUeForSigDat(cell, alloc, ue,
               toBeSchedInfo))
      {
         --*remUeRef;
      }
   }

   RETVOID;
}

/**
 * @brief Uplink scheduling function
 *
 * @details
 *
 *     Function : rgSCHPfsUlSchedUeForContRes
 *
 *     Processing Steps:
 *     - Schedule a UE for contention resolution
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo  *alloc
 *  @param[in]  RgSchUeCb              *ue
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PRIVATE S16 rgSCHPfsUlSchedUeForContRes
(
RgSchCellCb             *cell,
RgSchCmnUlRbAllocInfo   *alloc,
RgSchUeCb               *ue
)
#else
PRIVATE S16 rgSCHPfsUlSchedUeForContRes(cell, alloc, ue)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
RgSchUeCb               *ue;
#endif
{
   RgSchCmnUlUe       *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   UNUSED(cell);
   TRC2(rgSCHPfsUlSchedUeForContRes);

   /* Fix : syed If UE is already scheduled for RETX then 
    * avoid scheduling for newTx */
#ifdef LTEMAC_SPS
   if ((ue->ul.ulInactvMask) || (RG_SCH_CMN_IS_UL_UE_RETX(ue, cell)) || (RG_SCH_CMN_IS_SPS_SCHD(ue, cell)))
#else
   /* Fix : syed ccpu00129054. Added check for inactivity. */ 
   if ((ue->ul.ulInactvMask) || (RG_SCH_CMN_IS_UL_UE_RETX(ue, cell)))
#endif
   {
      /* UE already scheduled in this subframe (for retx) */
      RETVALUE(RFAILED);
   }
   /* ccpu00130982: Grant will be give for BSR, if any, received along with 
    * CRNTI MAC CE*/
   if (!ue->ul.effBsr)
   {
      cmnUe->alloc.reqBytes = RG_SCH_CMN_MAX_UL_CONTRES_GRNT;
   }
   else
   {
      cmnUe->alloc.reqBytes = ue->ul.effBsr;
   }
   rgSCHCmnUlAdd2CntResLst(alloc, ue);
   RETVALUE(ROK);
}

/**
 * @brief Uplink scheduling function
 *
 * @details
 *
 *     Function : rgSCHPfsUlSchedUeForSigDat
 *
 *     Processing Steps:
 *     - Schedule a UE for signaling+data
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo  *alloc
 *  @param[in]  RgSchUeCb              *ue
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PRIVATE S16 rgSCHPfsUlSchedUeForSigDat
(
RgSchCellCb             *cell,
RgSchCmnUlRbAllocInfo   *alloc,
RgSchUeCb               *ue,
RgSchPfsLcSchdInfo      *toBeSchedInfo
)
#else
PRIVATE S16 rgSCHPfsUlSchedUeForSigDat(cell, alloc, ue, toBeSchedInfo)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
RgSchUeCb               *ue;
RgSchPfsLcSchdInfo      *toBeSchedInfo;
#endif
{
   RgSchCmnUlCell      *cmnCell = RG_SCH_CMN_GET_UL_CELL(cell);
   RgSchCmnUlUe        *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   RgSchCmnUe          *schCmnUe = RG_SCH_CMN_GET_UE(ue,cell);
   RgSchCmnUeUlAlloc   *schCmnUeUlAlloc = &(schCmnUe->ul.alloc);
   RgSchCmnUlUe       *ueUl = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchUlHqProcCb     *proc;
   UNUSED(cell);

   TRC2(rgSCHPfsUlSchedUeForSigDat);

   proc = rgSCHUhmGetUlHqProc(cell, ue, cmnCell->schdHqProcIdx);
#ifdef LTEMAC_SPS
   if (RG_SCH_CMN_IS_UL_UE_RETX(ue, cell) || RG_SCH_CMN_IS_SPS_SCHD(ue, cell))
#else
   if (RG_SCH_CMN_IS_UL_UE_RETX(ue, cell))
#endif
   {
      RGSCH_NULL_CHECK(cell->instIdx, proc);
      /* UE already scheduled in this subframe (for retx) */
      RETVALUE(RFAILED);
   }

   cmnUe->alloc.reqBytes = ue->ul.effBsr; /* cmn considers maxBytesPerUe */
   if (cmnUe->alloc.reqBytes < 4)
   {
      cmnUe->alloc.reqBytes = 4;
      schCmnUeUlAlloc->reqBytes = 4;
   }
   /* calculate the sbs required */
   rgSchUtlGetNumSbs(cell, ue, &ueUl->subbandRequired);

   toBeSchedInfo->otherUeTotPfsPrio += pfsUe->pfsPrio;
   if ((toBeSchedInfo->currPrioMmbrSta == TRUE) && (ue->csgMmbrSta == TRUE))
   {
      toBeSchedInfo->prioUeTotPfsPrio += pfsUe->pfsPrio;
      toBeSchedInfo->totPrioBwReq += ueUl->subbandRequired;
      toBeSchedInfo->numPrioUe += 1;
   }
   else
   {
      toBeSchedInfo->totNonPrioBwReq += ueUl->subbandRequired;
   }


   if(ROK == rgSchUtlSortInsUeLst(cell, &(toBeSchedInfo->otherUeLcLst), &ueUl->ulSchedLnk,
            ueUl->subbandRequired))
   {
      ueUl->ulSchedLnk.node = (PTR)ue;
   }
   RETVALUE(ROK);
}

/**
 * @brief Short BSR reception handling
 *
 * @details
 *
 *     Function : rgSCHPfsUlUpdBsrShort
 *
 *     Processing Steps:
 *     - BSR updates for each LCG (and UE) would have happened
 *       as part of common processing. Now only call the
 *       function rgSCHPfsUlMngUeInQ() that looks at
 *       the updated common variables to correctly
 *       (re)position UEs.
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @param[in]  RgSchLcgCb         *lcg
 *  @param[in]  U8                  bsr
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlUpdBsrShort
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgSchLcgCb          *lcg,
U8                   bsr
)
#else
PUBLIC Void rgSCHPfsUlUpdBsrShort(cell, ue, lcg, bsr)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgSchLcgCb          *lcg;
U8                   bsr;
#endif
{
   UNUSED(lcg);
   UNUSED(bsr);

   TRC2(rgSCHPfsUlUpdBsrShort);

   rgSCHPfsUlMngUeInQ(cell, ue, 0);
   RETVOID;
}

/**
 * @brief Truncated BSR reception handling
 *
 * @details
 *
 *     Function : rgSCHPfsUlUpdBsrTrunc
 *
 *     Processing Steps:
 *     - BSR updates for each LCG (and UE) would have happened
 *       as part of common processing. Now only call the
 *       function rgSCHPfsUlMngUeInQ() that looks at
 *       the updated common variables to correctly
 *       (re)position UEs.
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @param[in]  RgSchLcgCb         *lcg
 *  @param[in]  U8                  bsr
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlUpdBsrTrunc
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgSchLcgCb          *lcg,
U8                   bsr
)
#else
PUBLIC Void rgSCHPfsUlUpdBsrTrunc(cell, ue, lcg, bsr)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgSchLcgCb          *lcg;
U8                   bsr;
#endif
{
   UNUSED(lcg);
   UNUSED(bsr);

   TRC2(rgSCHPfsUlUpdBsrTrunc);

   rgSCHPfsUlMngUeInQ(cell, ue, 0);
   RETVOID;
}

/**
 * @brief Long BSR reception handling
 *
 * @details
 *
 *     Function : rgSCHPfsUlUpdBsrLong
 *
 *     Processing Steps:
 *     - BSR updates for each LCG (and UE) would have happened
 *       as part of common processing. Now only call the
 *       function rgSCHPfsUlMngUeInQ() that looks at
 *       the updated common variables to correctly
 *       (re)position UEs.
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @param[in]  U8                  bsArr[]
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlUpdBsrLong
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
U8                  *bsArr
)
#else
PUBLIC Void rgSCHPfsUlUpdBsrLong(cell, ue, bsArr)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
U8                  *bsArr;
#endif
{
   UNUSED(bsArr);

   TRC2(rgSCHPfsUlUpdBsrLong);

   rgSCHPfsUlMngUeInQ(cell, ue, 0);
   RETVOID;
}

/* Fix : Updating PFS to start prio with highest possible value
            and diminishing prio val updates from there on */
/***********************************************************
 *
 *     Func : rgSCHPfsUlMngUeInQ
 *        
 *     Desc : This function looks at the current
 *            list of LCGs with pending data,
 *            and updates UE position in uplink
 *            queues accordingly.
 *
 *     Ret  : Void 
 *
 *     Notes: It assumes that BS of each LCG is correctly
 *            updated, and UE's remaining max bit rate
 *            (cmnUe->effUeBR) is also correctly updated.
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlMngUeInQ
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
U32                 allocd
)
#else
PRIVATE Void rgSCHPfsUlMngUeInQ(cell, ue, allocd)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
U32                 allocd;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   RgSchLcgCb          *lcg = NULLP;
   RgSchCmnLcg         *cmnLcg;
   S16                  idx;
   Bool                 prioChngd = FALSE;
   RgSchLcgCb          *prioLcg   = NULLP;

   TRC2(rgSCHPfsUlMngUeInQ);

   if (!RG_SCH_CMN_UL_IS_UE_ACTIVE(ue))
   {
      RETVOID;
   }

   /* ccpu00130982: If CRNTI MAC CE and Short BSR are came together then
    * not adding UE to any other prio Queue and the UE will be processed 
    * from ContRes Queue*/
   if(pfsUe->lstCp == &pfsCell->txQueues.contResLst)
   {
      RETVOID;
   }
 
   cmnLcg = (RgSchCmnLcg *)ue->ul.lcgArr[0].sch;
   if (cmnLcg->bs || pfsUe->srRcvd)
   {
      /* As long as UE has SRB data to be scheduled, highest 
       * prio is assigned to this UE */
      pfsUe->pfsPrio = pfsCell->maxSrbDrb0PrioVal;
      rgSCHPfsUlAddUeToSigQ(cell, ue);
      RETVOID;
   }
   else if((!cmnLcg->bs) && (!pfsUe->srRcvd))
   {
      /* Added the else-if conditional to do the handling of
       * removing the UE from the sigLst (if it exists) if no SR grant is pending 
       * and BS for lcg[0] is 0.*/
      if ((pfsUe->lstCp) && (pfsUe->lstCp == &pfsCell->txQueues.sigLst))
      {
         rgSCHPfsUlRmvUeFrmQ(cell, ue);
      }
   }

   if (!ue->ul.effBsr)
   {
      rgSCHPfsUlRmvUeFrmQ(cell, ue);
#ifdef RGR_V1
      if(ue->ul.totalBsr != 0)
      {
         if (ue->bsrTmr.tmrEvnt != TMR_NONE)
         {
            rgSCHTmrStopTmr(cell, ue->bsrTmr.tmrEvnt, ue); 
         }
         if (ue->ul.bsrTmrCfg.isPrdBsrTmrPres)
         {
            rgSCHTmrStartTmr(cell, ue, RG_SCH_TMR_BSR, 
                  ue->ul.bsrTmrCfg.prdBsrTmr);
         }
      }
#endif
      RETVOID;
   }
   /* Below logic assumes that services will be added in the 
      LCG groups in increasing order of priority
      ie: LCG1 will be having GBR followed by LCG2 having lower prio GBR 
          and LCG3 will be having any AMBR */

   /* Find First LCG with unsatisfied GBR, 
      else find first LCG with unsatisfied MBR 
      else find first non-GBR LCG with BS */
   for (idx = 1; idx < RGSCH_MAX_LCG_PER_UE; ++idx)
   {
      lcg = &ue->ul.lcgArr[idx];
      cmnLcg = (RgSchCmnLcg *)lcg->sch;
      if(cmnLcg->bs)
      {
         if(RGSCH_IS_GBR_BEARER(cmnLcg->cfgdGbr))
         {
            if (cmnLcg->effGbr)
            {
               prioLcg = lcg;
               break;
            }
            else           /*if(cmnLcg->effMbr)*/
            {
               prioLcg = lcg;
               continue;
            }
         }
         else 
         {
            if(prioLcg)
            {
               break;
            }
            else
            {
               prioLcg = lcg;
               break;
            }
         }
      }
   }
   
   /* LCG to be chosen in order GBR-MBR-AMBR */
   /* Due to non-zero cmnUe->effBsr, there should be at least one LCG
    * with non-zero BS, and this is what cmnLcg points to */

   if(NULLP != prioLcg)
   {
      pfsUe->lcgPrio = pfsUe->schedLcgInfo[prioLcg->lcgId].lcgPrio;  
      /* Fix : Updating PFS to start prio with highest possible value
               and diminishing prio val updates from there on */
      rgSCHPfsUlUpdPfsPrio(pfsCell, pfsUe, prioLcg, &prioChngd);
      rgSCHPfsUlAddUeToPfsQ(cell, ue, prioLcg, prioChngd);
   }
   else
   {
      rgSCHPfsUlRmvUeFrmQ(cell, ue);
   }

   RETVOID;
}

/**
 * @brief Indication of list of UEs which should not be
 *        scheduled
 *
 * @details
 *
 *     Function : rgSCHPfsUlInactvLstInd
 *
 *     Processing Steps:
 *      - Indication for set of UEs for which downlink
 *        scheduling should not be done.
 *        Triggers removal of logical channels of UEs
 *        from queues.
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlInactvLstInd
(
RgSchCellCb      *cell,
CmLListCp        *lst
)
#else
PUBLIC Void rgSCHPfsUlInactvLstInd(cell, lst)
RgSchCellCb      *cell;
CmLListCp        *lst;
#endif
{
   CmLList         *lnk;
   TRC2(rgSCHPfsUlInactvLstInd);

   for (lnk = lst->first; lnk; lnk = lnk->next)
   {
      RgSchUeCb       *ue = (RgSchUeCb *)lnk->node;
      rgSCHPfsUlUeInactv(cell, ue);
   }
   RETVOID;
}

/**
 * @brief Indication of list of UEs which should not be
 *        scheduled
 *
 * @details
 *
 *     Function : rgSCHPfsUlUeInactv
 *
 *     Processing Steps:
 *      - Triggers (temporary) removal of UEs
 *        from queues.
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlUeInactv
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PRIVATE Void rgSCHPfsUlUeInactv(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   TRC2(rgSCHPfsUlUeInactv);

   /* If UE is waiting for contention resolution, it keeps
    * monitoring PDCCH irrespective of there being gaps.
    * So don't take out of contention resolution queue. */
   if (pfsUe->lstCp == &pfsCell->txQueues.contResLst)
   {
      RETVOID;
   }

   rgSCHPfsUlRmvUeFrmQ(cell, ue);

   /* Managing of retx HARQ procs of UE is expected to be
    * done as part of common processing */

   RETVOID;
}

/**
 * @brief Indication that a UE is allowed to be scheduled
 *
 * @details
 *
 *     Function : rgSCHPfsUlActvUeInd
 *
 *     Processing Steps:
 *      - [This is an indication for UE for which uplink
 *        scheduling can now be done, since the last
 *        time it was not allowed.]
 *      - Triggers addition of UE to queue if needed.
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlActvUeInd
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHPfsUlActvUeInd(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   TRC2(rgSCHPfsUlActvUeInd);
   /* It is expected that managing retx HARQ procs of UE
    * is taken care of as part of common processing */
   rgSCHPfsUlMngUeInQ(cell, ue, 0);
   RETVOID;
}


/**
 * @brief Uplink CQI report handling
 *
 * @details
 *
 *     Function : rgSCHPfsUlCqiInd
 *
 *     Processing Steps:
 *     - If wideband CQI reported is zero, consider this to be
 *       an error and return
 *     - If wideband CQI has changed
 *       - Update CQI component of priority (specific to UE)
 *       - If UE was present in a PFS queue, update its position
 *         appropriately
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @param[in]  TfuUlCqiRpt        *cqiInfo
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlCqiInd
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
TfuUlCqiRpt         *cqiInfo
)
#else
PUBLIC Void rgSCHPfsUlCqiInd(cell, ue, cqiInfo)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
TfuUlCqiRpt         *cqiInfo;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   U8                   iTbs=0;

   UNUSED(cqiInfo);

   TRC2(rgSCHPfsUlCqiInd);

   /* Retrieve UL CQI based on UE Category  */
   iTbs  = rgSCHCmnUlGetITbs(cell, ue, cell->isCpUlExtend);
   pfsUe->cqiPrio = rgSCHPfsUlGetTpPrio(pfsCell, iTbs);
   if (pfsUe->lstCp == NULLP) /* UE is not in any queue */
   {
      RETVOID;
   }
   if ((pfsUe->lstCp == &pfsCell->txQueues.sigLst) ||
       (pfsUe->schedSinceRefresh == FALSE))
   {
      RETVOID;
   }
   /* Fix : Updating PFS to start prio with highest possible value
               and diminishing prio val updates from there on */
   rgSCHPfsUlMngUeInQ(cell, ue, 0);

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsUlAddUeToSigQ
 *
 *     Desc : This function is called to add UE to LCG0
 *            queue
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlAddUeToSigQ
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PRIVATE Void rgSCHPfsUlAddUeToSigQ(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);

   TRC2(rgSCHPfsUlAddUeToSigQ);

   if (pfsUe->lstCp)
   {
      if ((pfsUe->lstCp == &pfsCell->txQueues.sigLst) && (!pfsUe->schedInCrntUlSf))
      {
         RETVOID;       
      }        
      rgSCHPfsUlRmvUeFrmQ(cell, ue);
   }
   rgSCHPfsUlAddUeToQ(cell, &pfsCell->txQueues.sigLst, ue);
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsUlAddUeToPfsQ
 *        
 *     Desc : This function is called when PFS priority
 *            has changed. It does not update UE position
 *            if UE is in LCG0 queue. It leaves the UE
 *            in the same PFS queue if it is to map
 *            to the same queue now. Removes from old
 *            queue and adds to end of new queue if PFS
 *            queue has changed.
 *
 *     Ret  : Void 
 *
 *     Notes: There is no check for contention resolution
 *            queue because it is not expected that UE
 *            transmits anything before contention is
 *            resolved, and hence trigger for this function
 *            should not have arisen.
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlAddUeToPfsQ
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgSchLcgCb          *lcg,
Bool                prioChngd
)
#else
PRIVATE Void rgSCHPfsUlAddUeToPfsQ(cell, ue, lcg, prioChngd)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgSchLcgCb          *lcg;
Bool                prioChngd;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   RgSchCmnLcg         *cmnLcg;
   U8                   qId;

   TRC2(rgSCHPfsUlAddUeToPfsQ);

   /* Fix: Updating LC/UEs position in scheduling Queues should be
    * done only if UE is Active */
   if (!RG_SCH_CMN_UL_IS_UE_ACTIVE(ue))
   {
      RETVOID;
   }
   if (pfsUe->lstCp)
   {
      if ((!prioChngd) && (!pfsUe->schedInCrntUlSf))
      {
         RETVOID;
      }
      rgSCHPfsUlRmvUeFrmQ(cell, ue);
   }
   cmnLcg = (RgSchCmnLcg *)ue->ul.lcgArr[lcg->lcgId].sch;
   if(cmnLcg->effGbr)
   {
      qId  = rgSCHPfsUlGetQId(pfsCell, &pfsCell->range.gbrRange, pfsUe->pfsPrio);
      pfsUe->qId = qId;
      pfsUe->lstCp = &pfsCell->txQueues.gbrLst[qId];
   }
   else if(cmnLcg->effDeltaMbr)
   {
      qId  = rgSCHPfsUlGetQId(pfsCell, &pfsCell->range.mbrRange,pfsUe->pfsPrio);
      pfsUe->qId = qId;
      if (ue->csgMmbrSta == TRUE)
      {
         pfsUe->lstCp = &pfsCell->txQueues.prioMbrLst[qId];
      }
      else
      {
         pfsUe->lstCp = &pfsCell->txQueues.normMbrLst[qId];
      }
   }
   else
   {
      qId  = rgSCHPfsUlGetQId(pfsCell, &pfsCell->range.ambrRange, pfsUe->pfsPrio);	
      pfsUe->qId = qId;
      if (ue->csgMmbrSta == TRUE)
      {
         pfsUe->lstCp = &pfsCell->txQueues.prioAmbrLst[qId];
      }
      else
      {
         pfsUe->lstCp = &pfsCell->txQueues.normAmbrLst[qId];
      }
   }
   ue->repLcg = lcg;
   rgSCHPfsUlAddUeToQ(cell, pfsUe->lstCp, ue);
   RETVOID;
}


/**
 * @brief SR reception handling
 *
 * @details
 *
 *     Function : rgSCHPfsUlSrInd
 *
 *     Processing Steps:
 *     - Add UE to LCG0 queue
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlSrInd
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PUBLIC Void rgSCHPfsUlSrInd(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   TRC2(rgSCHPfsUlSrInd);

   pfsUe->srRcvd = TRUE;

   rgSCHPfsUlMngUeInQ(cell, ue, 0);
   /* Could instead check for if UE is active, and
    * call rgSCHPfsUlAddUeToSigQ(). This would be
    * a little quicker, albeit less maintainable.
    */

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsUlRmvUeFrmQ
 *        
 *     Desc : Remove UE from cell wide uplink tx queue
 *            if present
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlRmvUeFrmQ
(
RgSchCellCb         *cell,
RgSchUeCb          *ue
)
#else
PRIVATE Void rgSCHPfsUlRmvUeFrmQ(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb       *ue;
#endif
{
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);

   TRC2(rgSCHPfsUlRmvUeFrmQ);

   if (pfsUe->lstCp)
   {
      ue->repLcg = NULLP;
      cmLListDelFrm(pfsUe->lstCp, &pfsUe->prioLnk);
      pfsUe->lstCp = NULLP;
   }
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsUlAddUeToQ
 *        
 *     Desc : Insert UE to queue in descending order of pfsPrio
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlAddUeToQ
(
RgSchCellCb         *cell,
CmLListCp           *cp,
RgSchUeCb           *ue
)
#else
PRIVATE Void rgSCHPfsUlAddUeToQ(cell, cp, ue)
RgSchCellCb         *cell,
CmLListCp           *cp;
RgSchUeCb           *ue;
#endif
{
   RgSchUeCb           *lUe;
   RgSchPfsUlUe        *lPfsUe;
   CmLList             *node;
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);

   TRC2(rgSCHPfsUlAddUeToQ);

   /* Fix : syed Each Priority Queue should be
    * sorted in descending order of pfsPrio. */
   /* Insertion can be improved by not always starting
    * from first node */
   node = cp->first;
   while(node)
   {
      lUe = (RgSchUeCb *)(node->node);
      lPfsUe = RG_SCH_PFS_GET_PFSUEUL(lUe, cell);
      if (lPfsUe->pfsPrio < pfsUe->pfsPrio)
      {
         break;
      }
      node = node->next;
   }
   if (node == NULLP)
   {
      /* We have come to the end of the queue, so Append */
      cmLListAdd2Tail(cp, &pfsUe->prioLnk);
   }
   else
   {
      cp->crnt = node;
      cmLListInsCrnt(cp, &pfsUe->prioLnk);
   }

   pfsUe->lstCp = cp;
   RETVOID;
}

/**
 * @brief Contention Resolution allocation request
 *
 * @details
 *
 *     Function : rgSCHPfsUlContResReq
 *
 *     Processing Steps:
 *     - Add UE to cell wide contention resolution
 *       queue (contResLst) if not already present
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlContResReq
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PUBLIC Void rgSCHPfsUlContResReq(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchPfsUlCell      *pfsCell = RG_SCH_PFS_GET_PFSCELLUL(cell);
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   TRC2(rgSCHPfsUlContResReq);

   if (pfsUe->lstCp == &pfsCell->txQueues.contResLst)
   {
      RETVOID;
   }
   rgSCHPfsUlRmvUeFrmQ(cell, ue);
   rgSCHPfsUlAddUeToQ(cell, &pfsCell->txQueues.contResLst, ue);
   RETVOID;
}


/**
 * @brief Invoked on final RB allocation for a UL subframe
 *
 * @details
 *
 *     Function : rgSCHPfsUlOnAlloc
 *
 *     Processing Steps:
 *     - For each UE allocation for new transmission
 *       - Remove UE from contention resolution queue if present
 *       - For each other UE, call the rgSCHPfsUlMngUeInQ()
 *         function to keep the UEs updated in correct queues.
 *     - Need not do anything about unallocated new transmissions.
 *     - Need not do anything about allocated or unallocated
 *       retransmissions.
 *
 *  @param[in]  RgSchCellCb           *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo *alloc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsUlOnAlloc
(
RgSchCellCb           *cell,
RgSchCmnUlRbAllocInfo *alloc
)
#else
PUBLIC Void rgSCHPfsUlOnAlloc(cell, alloc)
RgSchCellCb           *cell;
RgSchCmnUlRbAllocInfo *alloc;
#endif
{
   CmLListCp           *cp;
   CmLList             *lnk;
   CmLListCp         ulInactvLst; /* list of UE's becoming UL-inactive */

   cmLListInit(&ulInactvLst);
   TRC2(rgSCHPfsUlOnAlloc);

   /* Go through UE's scheduled for contention resolution and remove
    * them from contention resolution queue */
   for (cp = &alloc->schdContResLst, lnk = cp->first; lnk; )
   {
      RgSchUeCb           *ue = (RgSchUeCb *)lnk->node;
      RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddUpdULMark (cell,ue);
      }
#endif
      lnk = lnk->next;
      rgSCHPfsUlUeSfResetTemp(cell, ue, &ulInactvLst);
      rgSCHPfsUlRmvUeFrmQ(cell, ue);
      pfsUe->schedSinceRefresh = TRUE;
   }

   /* Go through other scheduled UEs and update */
   for (cp = &alloc->schdUeLst, lnk = cp->first; lnk; )
   {
      RgSchUeCb           *ue = (RgSchUeCb *)lnk->node;
      RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
      RgSchCmnUlUe        *ueUl  = RG_SCH_CMN_GET_UL_UE(ue, cell);
      U32                 allocd;
#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(ue))
      {
         rgSCHCmnHdFddUpdULMark (cell,ue);
      }
#endif
      lnk = lnk->next;
      allocd = ueUl->alloc.allocdBytes;
      rgSCHPfsUlUeSfResetTemp(cell, ue, &ulInactvLst);
      pfsUe->schedInCrntUlSf = TRUE;
      /* This is added to remove Ue from the PFS queue if
       * the effBsr is 0 ie: UE does not have any BSR to be 
       * served. Also, it repositions the UE once scheduled 
       * in this TTI.
       */
      rgSCHPfsUlMngUeInQ(cell, ue,0);
      pfsUe->schedInCrntUlSf = FALSE;
      pfsUe->schedSinceRefresh = TRUE;
   }

   /* Go through non-scheduled UEs and reset ul alloc cb. Right
    * now, don't see a need to reset anything except reqLnk.node. */
   for (cp = &alloc->nonSchdContResLst, lnk = cp->first; lnk; )
   {
      RgSchUeCb           *ue = (RgSchUeCb *)lnk->node;
      lnk = lnk->next;
      rgSCHPfsUlUeSfResetTemp(cell, ue, &ulInactvLst);
   }
   for (cp = &alloc->nonSchdUeLst, lnk = cp->first; lnk; )
   {
      RgSchUeCb           *ue = (RgSchUeCb *)lnk->node;
      lnk = lnk->next;
      rgSCHPfsUlUeSfResetTemp(cell, ue, &ulInactvLst);
   }

      /*PDCCH for SR scheduled, now inactivate the UE if not active for other
       * reasons.*/
   rgSCHPfsUlInactvLstInd(cell, &ulInactvLst);

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsUlUeSfResetTemp
 *
 *     Desc : Reset whatever variables where temporarily used
 *            during UE scheduling.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlUeSfResetTemp
(
RgSchCellCb             *cell,
RgSchUeCb               *ue,
CmLListCp               *ulInactvLst /* list of UE's becoming UL-inactive */
)
#else
PRIVATE Void rgSCHPfsUlUeSfResetTemp(cell, ue, ulInactvLst)
RgSchCellCb             *cell;
RgSchUeCb               *ue;
CmLListCp               *ulInactvLst; /* list of UE's becoming UL-inactive */
#endif
{
   RgSchPfsUlUe        *pfsUe = RG_SCH_PFS_GET_PFSUEUL(ue, cell);
   RgSchDrxUeCb      *drxUe    = NULLP;
   UNUSED(cell);

   TRC2(rgSCHPfsUlUeSfResetTemp);

   /*cmnUe->alloc.reqLnk.node = NULLP;*/
   rgSCHCmnUlUeResetTemp(cell, ue);
   if (ue->isDrxEnabled)
   {
      /* The srRcvd is set to TRUE in case of BSR timer expiry case also. 
       * In such case, the DRX mask should not be changed. Hence replacing with 
       * the srGrant flag. 
       * TODO: We should remove the duplicate flag srRcvd from both RR and PFS 
       *       schedulers 
       */   
 
      if(ue->isSrGrant == TRUE)
      {
         drxUe = RG_SCH_DRX_GET_UE(ue);
         drxUe->drxUlInactvMask  |= RG_SCH_DRX_SR_BITMASK;

         if(!RG_SCH_DRX_UL_IS_UE_ACTIVE(drxUe))
         {
            ue->ul.ulInactvMask |= RG_DRX_INACTIVE;
            /* Add to Ul inactive List */
            ue->ulDrxInactvLnk.node  = (PTR)ue;
            cmLListAdd2Tail(ulInactvLst,&(ue->ulDrxInactvLnk));
         }
         drxUe->srRcvd = FALSE;
      }
   }
   pfsUe->srRcvd = FALSE;
   ue->isSrGrant = FALSE;
   RETVOID;
}  /* rgSCHPfsUlUeSfResetTemp */

/***********************************************************
 *
 *     Func : rgSCHPfsUlGetTpPrio
 *        
 *     Desc : Obtains TP PFS priority from iTbs value
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE U32 rgSCHPfsUlGetTpPrio
(
RgSchPfsUlCell      *pfsCell,
U8                  iTbs
)
#else
PRIVATE U32 rgSCHPfsUlGetTpPrio(pfsCell, iTbs)
RgSchPfsUlCell      *pfsCell;
U8                  iTbs;
#endif
{
   TRC2(rgSCHPfsUlGetTpPrio);
   RGSCH_ARRAY_BOUND_CHECK(0, pfsCell->tbls.tpPrios, iTbs);
   RETVALUE(pfsCell->tbls.tpPrios[iTbs]);
}

/***********************************************************
 *
 *     Func : rgSCHPfsUlGetQId
 *        
 *     Desc : For uplink,obtains queue ID for dataLst
 *            given a PFS priority
 *
 *     Ret  : Void 
 *
 *     Notes:
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE U32 rgSCHPfsUlGetQId
(
RgSchPfsUlCell      *pfsCell,
RgSchPfsPrioRange   *range,
U32                  pfsPrio
)
#else
PRIVATE U32 rgSCHPfsUlGetQId(pfsCell, range, pfsPrio)
RgSchPfsUlCell      *pfsCell;
RgSchPfsPrioRange   *range;
U32                  pfsPrio;
#endif
{
   U32 qId; 
   TRC2(rgSCHPfsUlGetQId);

   /*ccpu00128290 - ADD - Protection to avoid prioVal going out of range */
   if (pfsPrio < range->min)
   {
      pfsPrio = range->min;
   }
   /* Fix : syed For small range and large number of Queues
    * precalculated numElemPerQ can be highly inaccurate. It
    * was leading to a crash.  */
   qId = ((pfsPrio - range->min) * range->numQs) / 
      range->maxDiff;
   RETVALUE(qId);
}

/**** COMMON functions (specific neither to uplink, nor downlink) ****/


/***********************************************************
 *
 *     Func : rgSCHPfsFillTbl
 *
 *     Desc : Used to fill various PFS tables during
 *            configuration. Also determines minimum
 *            and maximum values in the passed table.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsFillTbl
(
U32                  *src,
U32                  *dst,
U32                  numEntries,
U32                  *minVal,
U32                  *maxVal
)
#else
PRIVATE Void rgSCHPfsFillTbl(src, dst, numEntries, minVal, maxVal)
U32                  *src;
U32                  *dst;
U32                  numEntries;
U32                  *minVal;
U32                  *maxVal;
#endif
{
   U32             min;
   U32             max;
   U16             idx;
   U32             val;
   TRC2(rgSCHPfsFillTbl);

   min = src[0];
   max = src[0];
   dst[0] = min;
   for (idx = 1; idx < numEntries; ++idx)
   {
      val = src[idx];
      if (val < min)
      {
         min = val;
      }
      if (val > max)
      {
         max = val;
      }
      dst[idx] = val;
   }
   *minVal = min;
   *maxVal = max;

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsDlSvcFillTbl
 *
 *     Desc : Used to fill various PFS tables during
 *            configuration. Also determines minimum
 *            and maximum values in the passed table.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlSvcFillTbl
(
U32                  *src,
U32                  *dst,
U32                  strtEntry,
U32                  endEntry,
U32                  *minVal,
U32                  *maxVal
)
#else
PRIVATE Void rgSCHPfsDlSvcFillTbl(src, dst, strtEntry, endEntry, minVal, maxVal)
U32                  *src;
U32                  *dst;
U32                  strtEntry;
U32                  endEntry;
U32                  *minVal;
U32                  *maxVal;
#endif
{
   U32             min;
   U32             max;
   U16             idx;
   U16             numEntries;
   U32             minPdbLvl;
   U32             maxPdbLvl;
   TRC2(rgSCHPfsDlSvcFillTbl);

   numEntries = endEntry - strtEntry + 1;
   min = src[0] * rgSchPfsQciPdbInfo[strtEntry].pdbPrioWgt[0];
   max = src[0] * rgSchPfsQciPdbInfo[strtEntry].pdbPrioWgt[rgSchPfsQciPdbInfo[strtEntry].maxNmbPdbLvls - 1];
   for (idx = 0; idx < numEntries; ++idx)
   {
      minPdbLvl = rgSchPfsQciPdbInfo[idx+strtEntry].pdbPrioWgt[0];  
      maxPdbLvl = rgSchPfsQciPdbInfo[idx+strtEntry].pdbPrioWgt[rgSchPfsQciPdbInfo[idx+strtEntry].maxNmbPdbLvls - 1];  
      if ((src[idx] * minPdbLvl) < min)
      {
         min = src[idx] * minPdbLvl;
      }
      if ((src[idx] * maxPdbLvl) > max)
      {
         max = src[idx] * maxPdbLvl;
      }
      dst[idx] = src[idx];

   }
   *minVal = min;
   *maxVal = max;

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHPfsFillRange
 *
 *     Desc : Fill RgSchPfsPrioRange information
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsFillRange
(
RgSchPfsPrioRange    *range,
U32                   minPrio,
U32                   maxPrio,
U8                    numQs
)
#else
PRIVATE Void rgSCHPfsFillRange(range, minPrio, maxPrio, numQs)
RgSchPfsPrioRange    *range;
U32                   minPrio;
U32                   maxPrio;
U8                    numQs;
#endif
{
   TRC2(rgSCHPfsFillRange);

   range->min = minPrio;
   range->max = maxPrio;
   /* Fix : syed For small range and large number of Queues
    * precalculated numElemPerQ can be highly inaccurate. It
    * was leading to a crash.  */
   range->maxDiff = maxPrio + 1 - minPrio;
   range->numQs = numQs;

   RETVOID;
}

/**
 * @brief Initialize Fraction Priority related Info 
 *
 * @details
 *
 *     Function : rgSCHPfsInitFracPrioInfo 
 *
 *     Processing Steps:
 *     - Initialize Fraction Priority related Info.
 *
 *  @param[in]  RgSchPfsFracPrioInfo   *fracPrioInfo,
 *  @param[in]  U32                    cfgdRate
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsInitFracPrioInfo 
(
RgSchPfsFracPrioInfo   *fracPrioInfo,
U32                    cfgdRate
)
#else
PRIVATE Void rgSCHPfsInitFracPrioInfo(fracPrioInfo, cfgdRate)
RgSchPfsFracPrioInfo   *fracPrioInfo;
U32                    cfgdRate;
#endif
{
   TRC2(rgSCHPfsInitFracPrioInfo);

   fracPrioInfo->achvdFracDataRate = 0;
   fracPrioInfo->fracPrioLvls = 0;
   fracPrioInfo->fracDataRate = RGSCH_CEIL(cfgdRate, RG_SCH_PFS_FAIRNESS_FACTOR_LVLS);

   RETVOID;
}

/**
 * @brief Updates Fraction Priority related Info for every allocation
 *
 * @details
 *
 *     Function : rgSCHPfsUpdFracPrioInfo 
 *
 *     Processing Steps:
 *     - Updates Fraction Priority related Info for every allocation.
 *
 *  @param[in]  RgSchPfsFracPrioInfo   *fracPrioInfo,
 *  @param[in]  U32                    allocd 
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsUpdFracPrioInfo 
(
RgSchPfsFracPrioInfo   *fracPrioInfo,
U32                    allocd 
)
#else
PRIVATE Void rgSCHPfsUpdFracPrioInfo(fracPrioInfo, allocd)
RgSchPfsFracPrioInfo   *fracPrioInfo;
U32                    allocd;
#endif
{
   TRC2(rgSCHPfsUpdFracPrioInfo);

   if ((allocd == 0) || (fracPrioInfo->fracDataRate == 0))
   {
      RETVOID;    
   }

   fracPrioInfo->fracPrioLvls += (fracPrioInfo->achvdFracDataRate +
         allocd) / fracPrioInfo->fracDataRate;
   fracPrioInfo->achvdFracDataRate = (fracPrioInfo->achvdFracDataRate +
         allocd) % fracPrioInfo->fracDataRate;
   if(fracPrioInfo->fracPrioLvls >= RG_SCH_PFS_FAIRNESS_FACTOR_LVLS)
   {
      fracPrioInfo->fracPrioLvls = RG_SCH_PFS_FAIRNESS_FACTOR_LVLS - 1;
   }
   RETVOID;

}

/**
 * @brief Compute and update UL PFS Priority 
 *
 * @details
 *
 *     Function : rgSCHPfsUlUpdPfsPrio 
 *
 *     Processing Steps:
 *     - Compute and update UL PFS Priority.
 *
 *  @param[in]  RgSchPfsUlCell        *pfsCell,
 *  @param[in]  RgSchPfsUlUe          *pfsUe,
 *  @param[out] Bool                  *prioChngd 
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsUlUpdPfsPrio 
(
RgSchPfsUlCell        *pfsCell,
RgSchPfsUlUe          *pfsUe,
RgSchLcgCb            *lcg,
Bool                  *prioChngd
)
#else
PRIVATE Void rgSCHPfsUlUpdPfsPrio(pfsCell, pfsUe, lcg, prioChngd)
RgSchPfsUlCell        *pfsCell;  
RgSchPfsUlUe          *pfsUe;
RgSchLcgCb            *lcg;
Bool                  *prioChngd;
#endif
{
   U32 prevPfsPrio = pfsUe->pfsPrio;   
   U32 fairPrioIdx;
   RgSchCmnLcg *cmnLcg = ((RgSchCmnLcg *)(lcg->sch));
   TRC2(rgSCHPfsUlUpdPfsPrio);

   if (RGSCH_IS_GBR_BEARER(cmnLcg->cfgdGbr))
   {
      fairPrioIdx = pfsUe->schedLcgInfo[lcg->lcgId].fracPrioInfo.fracPrioLvls;
   }
   else
   { 
      fairPrioIdx = pfsUe->fracPrioInfo.fracPrioLvls;
   } 
  
   pfsUe->pfsPrio = (pfsUe->lcgPrio * pfsUe->cqiPrio * pfsCell->tbls.fairPrios[fairPrioIdx]) / pfsCell->prioScaleFact;
   if (prevPfsPrio != pfsUe->pfsPrio)
   {
      *prioChngd = TRUE;      
   }
   RETVOID;
}

/**
 * @brief Compute and update DL PFS Priority 
 *
 * @details
 *
 *     Function : rgSCHPfsDlUpdPfsPrio 
 *
 *     Processing Steps:
 *     - Compute and update DL PFS Priority.
 *
 *  @param[in]  RgSchEnbPfsDl         *pfsDl,
 *  @param[in]  RgSchPfsDlLc          *pfsLc,
 *  @param[in]  RgSchPfsFracPrioInfo  *fracPrioInfo
 *  @param[out] Bool                  *prioChngd
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlUpdPfsPrio 
(
RgSchEnbPfsDl         *pfsDl,
RgSchPfsDlLc          *pfsLc,
RgSchUeCb             *ue,
RgSchPfsFracPrioInfo  *fracPrioInfo,
Bool                  *prioChngd
)
#else
PRIVATE Void rgSCHPfsDlUpdPfsPrio(pfsDl, pfsLc, ue, fracPrioInfo, prioChngd)
RgSchEnbPfsDl         *pfsDl;
RgSchPfsDlLc          *pfsLc;
RgSchUeCb             *ue;
RgSchPfsFracPrioInfo  *fracPrioInfo;
Bool                  *prioChngd;
#endif
{
      RgSchCellCb  *favCell = (RgSchCellCb *)(pfsLc->cellFavLst.first->node);     
      U8            cellIdx =  ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(favCell)];
   U32          prevPfsPrio = pfsLc->pfsPrio;   

   TRC2(rgSCHPfsDlUpdPfsPrio);

      pfsLc->pfsPrio = 
         (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
          pfsDl->tbls.fairPrios[fracPrioInfo->fracPrioLvls] * 
          (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
          (pfsDl->prioScaleFact);

   if (prevPfsPrio != pfsLc->pfsPrio)
   {
      *prioChngd = TRUE;      
   }
   RETVOID;
}

#ifdef LTE_ADV
/**
 * @brief Create the favCell list for a LC
 *
 * @details
 *     create favCell list for a LC based on the priority 
 *     comes out for the cell
 *
 *     Function : rgSchPfsGetLcFavCellLst
 *
 *  @param[in]  RgSchDlLcCb          *lc,
 **/
#ifdef ANSI
PRIVATE Void rgSchPfsGetLcFavCellLst
(
  RgSchDlLcCb       *lc
)
#else
PRIVATE Void rgSchPfsGetLcFavCellLst(lc) 
RgSchDlLcCb       *lc;
#endif
{
   RgSchPfsDlLc            *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
   RgSchEnbPfsDl           *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(lc->ue->cell);
   RgSchPfsCellSpfcDlLc    *cellSpfcDlLc;
   RgSchCellCb             *oldFavCell;
   RgSchCellCb             *newFavCell;
   RgSchCellCb             *cell;
   U8                      cellIdx;      
   CmLList                 *cellInst = NULLP;
   U32                     cellLoad;             
   U32                     lowPrio = 0;
   U8                      idx;
   U32                     fracPrioLvls;
   U32                     cellLoadPrio;

   TRC2(rgSchPfsGetLcFavCellLst);
   
   if((pfsLc->cellFavLst.count > 1) && 
      (pfsLc->cellFavLstUpdIdx != pfsEnbDl->lastCellLoadUpdIdx)) 
   {   
      oldFavCell = (RgSchCellCb *)pfsLc->cellFavLst.first->node;
      cmLListInit(&(pfsLc->cellFavLst));

      for(idx = 0; idx <= RG_SCH_MAX_SCELL; idx++)
      {
         if(lc->ue->cellInfo[idx] != NULLP)
         {
            cell          = lc->ue->cellInfo[idx]->cell;
            cellIdx       = lc->ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];      
            cellLoad      = pfsEnbDl->cellLoad[RG_SCH_CELLINDEX(cell)];
            cellSpfcDlLc  = &(pfsLc->cellSpfc[cellIdx]);

            /* Calculating the priority levels based on the data served and 
             * adding 1 to avoid the possibility of being zero */
            if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
            {   
               RgSchPfsDlUe  *pfsUe = RG_SCH_PFS_GET_PFSUEDL(lc->ue, cell);
               fracPrioLvls = (cellSpfcDlLc->achvdFracDataRate / 
                               pfsUe->cmnParam->fracDataRate) + 1; 
            }
            else
            {
               fracPrioLvls = (cellSpfcDlLc->achvdFracDataRate / pfsLc->fracDataRate) + 1; 
            }   

            /* Calculating the cellLoad priority based on the average PRB
             *  usage and adding 1 to avoid the possibility of being zero */
            cellLoadPrio = ((100 - cellLoad) / RG_SCH_PFS_CELL_LOAD_FACTOR) + 1;

            cellSpfcDlLc->cellPrio = cellLoadPrio * fracPrioLvls;    

            if(pfsLc->cellFavLst.count == 0)
            {     
               lowPrio = cellSpfcDlLc->cellPrio;
               cmLListAdd2Tail(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));
            }
            else
            {
               if(cellSpfcDlLc->cellPrio <= lowPrio)
               {
                  cmLListAdd2Tail(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));
                  lowPrio = cellSpfcDlLc->cellPrio;
               }   
               else
               { 
                  CM_LLIST_FIRST_NODE(&pfsLc->cellFavLst, cellInst);
                  do
                  {  
                     cell       = (RgSchCellCb *)(cellInst->node);
                     U8 tempIdx = lc->ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];                  

                     if(cellSpfcDlLc->cellPrio > 
                           pfsLc->cellSpfc[tempIdx].cellPrio)
                     {
                        cmLListInsCrnt(&pfsLc->cellFavLst, &(cellSpfcDlLc->favCellLnk));
                        break;
                     }   
                     CM_LLIST_NEXT_NODE(&pfsLc->cellFavLst, cellInst);
                  }while(cellInst);
               }   
            }   
         }
      }
      pfsLc->cellFavLstUpdIdx = pfsEnbDl->lastCellLoadUpdIdx;

      newFavCell = (RgSchCellCb *)pfsLc->cellFavLst.first->node;

      /* Recalculating the PFS priority if favCell is changed for the LC 
       * and LC was already added in the prioLstCp (having some data to 
       * serve)*/
      if((oldFavCell != newFavCell) && (pfsLc->prioLstCp))
      {
         cellIdx  = lc->ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(newFavCell)];      

         if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
         {
            RgSchPfsDlUe     *pfsUe = RG_SCH_PFS_GET_PFSUEDL(lc->ue, newFavCell);
            pfsLc->pfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
                  pfsEnbDl->tbls.fairPrios[pfsUe->cmnParam->fracPrioInfo.fracPrioLvls] *
                  (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
               (pfsEnbDl->prioScaleFact); 
         }
         else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
         {
            pfsLc->pfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
                  pfsEnbDl->tbls.fairPrios[pfsLc->fracPrioInfo.fracPrioLvls] *
                  (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
               (pfsEnbDl->prioScaleFact); 
         }

         rgSchPfsUpdPrioQ(newFavCell, lc->ue, pfsLc);
      }   
   }
}
#endif

/***********************************************************
 *
 *     Func : rgSCHPfsDlLcUpdQ
 *
 *     Desc : Insert LC in sorted Prio Queue. 
 *            Set lc's cp to that of queue.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcUpdQ
(
CmLListCp          *cp,
RgSchPfsDlLc       *pfsLc
)
#else
PRIVATE Void rgSCHPfsDlLcUpdQ(cp, pfsLc)
CmLListCp          *cp;
RgSchPfsDlLc       *pfsLc;
#endif
{
   RgSchDlLcCb        *lLc;
   RgSchPfsDlLc       *lPfsLc;
   CmLList            *node;

   TRC2(rgSCHPfsDlLcUpdQ);

   if(pfsLc->prioLstCp)
   {
      cmLListDelFrm(pfsLc->prioLstCp, &pfsLc->prioLnk);
      pfsLc->prioLstCp = NULLP;
   }

   node = cp->first;
   while(node)
   {
      lLc = (RgSchDlLcCb *)(node->node);
      lPfsLc = RG_SCH_PFS_GET_PFSDLLC(lLc->ue, lLc);
      if (lPfsLc->pfsPrio < pfsLc->pfsPrio)
      {
         break;
      }
      node = node->next;
   }
   if (node == NULLP)
   {
      /* We have come to the end of the queue, so Append */
      cmLListAdd2Tail(cp, &pfsLc->prioLnk);
   }
   else
   {
      cp->crnt = node;
      cmLListInsCrnt(cp, &pfsLc->prioLnk);
   }

   pfsLc->prioLstCp = cp;

   RETVOID;
}  

/**
 * @brief  
 *
 * @details
 *
 *     Function : rgSchPfsUpdPrioQ
 *
 *  @param[in]  RgSchCellCb     *cell
 **/
#ifdef ANSI
PRIVATE Void rgSchPfsUpdPrioQ
(
 RgSchCellCb     *cell,
 RgSchUeCb       *ue,
 RgSchPfsDlLc    *pfsLc
 )
#else
PRIVATE Void rgSchPfsUpdPrioQ(cell, Ue, pfsLc) 
 RgSchCellCb     *cell
 RgSchUeCb       *ue;
 RgSchPfsDlLc    *pfsLc;
#endif
{
   RgSchEnbPfsDl   *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(cell);
   U8               qId;

   TRC2(rgSchPfsUpdPrioQ);

   if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
   {
      qId = rgSCHPfsDlGetQId(pfsLc,&pfsEnbDl->ranges.ambrRange,
            pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_AMBR_QUEUES-1);
      RGSCH_PFS_AMBR_ARRAY_BOUND_CHECK(0, pfsEnbDl, qId, ue);

      if (ue->csgMmbrSta == TRUE)
      {
         rgSCHPfsDlLcUpdQ(&pfsEnbDl->txQueues.prioAmbrLst[qId], pfsLc);
      }
      else
      {
         rgSCHPfsDlLcUpdQ(&pfsEnbDl->txQueues.normAmbrLst[qId], pfsLc);
      }
   }
   else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
   {
      if (pfsLc->remGbr)
      {
         qId = rgSCHPfsDlGetQId(pfsLc,&pfsEnbDl->ranges.gbrRange,
               pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_GBR_QUEUES-1);
         RGSCH_ARRAY_BOUND_CHECK(0, pfsEnbDl->txQueues.gbrLst, qId);
         rgSCHPfsDlLcUpdQ(&pfsEnbDl->txQueues.gbrLst[qId], pfsLc);
      }
      else if (pfsLc->remDeltaMbr)
      {
         qId = rgSCHPfsDlGetQId(pfsLc,&pfsEnbDl->ranges.mbrRange,
               pfsLc->pfsPrio, RG_SCH_PFS_DL_NUM_MBR_QUEUES-1);
         if (ue->csgMmbrSta == TRUE)
         {
            RGSCH_ARRAY_BOUND_CHECK(0, pfsEnbDl->txQueues.prioMbrLst, qId);
            rgSCHPfsDlLcUpdQ(&pfsEnbDl->txQueues.prioMbrLst[qId], pfsLc);
         }
         else
         {
            RGSCH_ARRAY_BOUND_CHECK(0, pfsEnbDl->txQueues.normMbrLst, qId);
            rgSCHPfsDlLcUpdQ(&pfsEnbDl->txQueues.normMbrLst[qId], pfsLc);
         } 
      }
   }
}  

#ifdef LTE_ADV
/**
 * @brief  
 *
 * @details
 *
 *     Function : rgSchPfsGetDlRetxQId
 *
 *  @param[in]  RgSchCellCb     *cell
 *  @param[in]  RgSchUeCb       *ue
 *  @param[in]  RgSchPfsDlLc    *pfsLc
 **/
#ifdef ANSI
PRIVATE U8 rgSchPfsGetDlRetxQId
(
 RgSchCellCb     *cell,
 RgSchUeCb       *ue,
 RgSchPfsDlLc    *pfsLc,
 U32             pfsPrio
 )
#else
PRIVATE U8 rgSchPfsGetDlRetxQId(cell, Ue, pfsLc, pfsPrio) 
 RgSchCellCb     *cell
 RgSchUeCb       *ue;
 RgSchPfsDlLc    *pfsLc;
 U32             pfsPrio;
#endif
{
   U8              qId  = 0;
   RgSchEnbPfsDl   *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(cell);

   TRC2(rgSchPfsGetDlRetxQId);

   if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
   {
      qId = rgSCHPfsDlGetQId(pfsLc,&pfsEnbDl->ranges.ambrRange,
            pfsPrio, RG_SCH_PFS_DL_NUM_AMBR_QUEUES-1);
      RGSCH_PFS_AMBR_ARRAY_BOUND_CHECK(0, pfsEnbDl, qId, ue);

   }
   else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
   {
      if (pfsLc->remGbr)
      {
         qId = rgSCHPfsDlGetQId(pfsLc,&pfsEnbDl->ranges.gbrRange,
               pfsPrio, RG_SCH_PFS_DL_NUM_GBR_QUEUES-1);
         RGSCH_ARRAY_BOUND_CHECK(0, pfsEnbDl->txQueues.gbrLst, qId);
      }
      else if (pfsLc->remDeltaMbr)
      {
         qId = rgSCHPfsDlGetQId(pfsLc,&pfsEnbDl->ranges.mbrRange,
               pfsPrio, RG_SCH_PFS_DL_NUM_MBR_QUEUES-1);
         if (ue->csgMmbrSta == TRUE)
         {
            RGSCH_ARRAY_BOUND_CHECK(0, pfsEnbDl->txQueues.prioMbrLst, qId);
         }
         else
         {
            RGSCH_ARRAY_BOUND_CHECK(0, pfsEnbDl->txQueues.normMbrLst, qId);
         } 
      }
   }
   RETVALUE(qId);
}  
#endif
/**
 * @brief  
 *
 * @details
 *
 *     Function : rgSchPfsGetRetxQ
 *
 *  @param[in]  RgSchPfsDlCell   *pfsCel
 *  @param[in]  RgSchPfsDlLc     *pfsLc
 *  @param[in]  U8               qId
 **/
#ifdef ANSI
PRIVATE S16 rgSchPfsGetRetxQ
(
 RgSchPfsDlCell   *pfsCell, 
 RgSchPfsDlLc     *pfsLc,
 U8               qId,
 CmLListCp        **retxQ
)
#else
PRIVATE S16 rgSchPfsGetRetxQ(pfsCell, pfsLc, qId, reTxQ) 
   RgSchPfsDlCell   *pfsCell; 
   RgSchPfsDlLc     *pfsLc;
   U8               qId;
   CmLListCp        **retxQ;
#endif
{
   TRC2(rgSchPfsGetRetxQ);

   if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_SRB)
   {
      *retxQ = &pfsCell->retxQueues.srbLst;
   }   
   else if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_DRB0)
   {
      *retxQ = &pfsCell->retxQueues.drb0Lst;
   } 
   else if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
   {
      if(pfsLc->remGbr)
      {
         if(qId < RG_SCH_PFS_DL_NUM_GBR_QUEUES)
         {
            *retxQ = &pfsCell->retxQueues.gbrLst[qId];
         }
      }   
      else if(pfsLc->remDeltaMbr)
      {
         if(qId < RG_SCH_PFS_DL_NUM_MBR_QUEUES)
         {
            *retxQ = &pfsCell->retxQueues.retxMbrLst[qId];
         }
      }   
   }
   else if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
   {
      if(qId < RG_SCH_PFS_DL_NUM_AMBR_QUEUES)
      {
         *retxQ = &pfsCell->retxQueues.retxAmbrLst[qId];
      }
   }  

   RETVALUE(ROK);
}

/**
 * @brief  Utility function to create an UE list in increasing order of PRBs
 * needed. 
 *
 * @details
 *
 *     Function : rgSCHPfsAddUeToSchedLst
 *
 *     If PRBs needed are less than minimum, insert at the head,
 *     Else if PRBs needed are greater than max, insert at the tail,
 *     Else traverse through the list and insert at the appropriate place.
 *
 *  @param[in]  RgSchCmnDlUe   *cmnUe
 *  @param[in]  RgSchDlLcCb    *lc
 *  @param[in]  CmLListCp      *lcToBeSchedLst
 *  @return     Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsAddUeToSchedLst
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
CmLListCp          *cp
)
#else
PRIVATE Void rgSCHPfsAddUeToSchedLst (cell, ue, cp)
RgSchCellCb        *cell;   
RgSchUeCb          *ue;
CmLListCp          *cp;
#endif
{
   
   RgSchPfsDlUe    *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   CmLList         *ueInLst; 
   CmLList         *lastUeInLst;
   RgSchPfsDlUe    *lPfsUe; 
   RgSchUeCb       *lUe;

   CM_LLIST_FIRST_NODE(cp, ueInLst);
   if(NULLP == ueInLst)
   {
      /* first node to be added to the list */
      cmLListAdd2Tail(cp, &(pfsUe->toBeSchedLnk));
      RETVOID;
   }

   lastUeInLst = cp->last;
   lUe = (RgSchUeCb *)(lastUeInLst->node);
   lPfsUe = RG_SCH_PFS_GET_PFSUEDL(lUe, cell);

   /* If the last UE in the sorted list needs lesser PRBs that the current,
    * insert at the end. */
   if(pfsUe->totalPrbReqd >= lPfsUe->totalPrbReqd)
   {
      cmLListAdd2Tail(cp, &(pfsUe->toBeSchedLnk));
   }
   else
   {
      /* Scan through the sorted list and insert at the appropriate position */
      do
      {
         lUe = (RgSchUeCb *)(ueInLst->node);
         lPfsUe = RG_SCH_PFS_GET_PFSUEDL(lUe, cell);

         if(pfsUe->totalPrbReqd <= lPfsUe->totalPrbReqd)
         {
            cmLListInsCrnt(cp, &(pfsUe->toBeSchedLnk));
            break;
         }

         CM_LLIST_NEXT_NODE(cp, ueInLst);
      }while(NULLP != ueInLst);
   }
   RETVOID;
} 

/**
 * @brief  Utility function to check if UE can be scheduled throgh this cell. 
 *
 * @details
 *
 *     Function : rgSchPfsChkUeSched
 *
 *  @param[in]  RgSchcellCb    *cell
 *  @param[in]  RgSchUeCb      *ue
 *  @return     Bool
 **/
#ifdef ANSI
PRIVATE Bool rgSchPfsChkUeSched
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlSf          *sf
)
#else
PRIVATE Void rgSchPfsChkUeSched(cell, ue, sf)
RgSchCellCb        *cell;   
RgSchUeCb          *ue;
RgSchDlSf          *sf;
#endif
{ 
   TRC2(rgSchPfsChkUeSched);

   if(!sf->remUeCnt)
   {
      RETVALUE(FALSE); 
   }

#ifdef LTEMAC_HDFDD
   if (RG_SCH_HDFDD_UE_ENBLD(ue))
   {
      Bool    dlAllowed = FALSE;
      rgSCHCmnHdFddChkDlAllow (cell, ue, &dlAllowed);
      if (dlAllowed == FALSE)
      {
         RETVALUE(FALSE); 
      }
   }
#endif

#ifdef LTEMAC_SPS
   CmLteTimingInfo      schdTime;
   schdTime = cell->crntTime;

   /* Increment by DL DELTA to determine the time for which scheduling
    * is done */
   RGSCH_INCR_SUB_FRAME(schdTime, RG_SCH_CMN_DL_DELTA);
   if (RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime))
   {
      RETVALUE(FALSE); 
   }
#endif

   if (RG_SCH_CMN_IS_UE_SCHDLD(ue, cell))
   {
      RgSchCmnDlUe  *ueDl = RG_SCH_CMN_GET_DL_UE(ue, cell);
      RgSchDlHqProcCb *proc  = (RgSchDlHqProcCb *)ueDl->proc;
      /* Don't do anything if UE already scheduled for retx */
      if (RG_SCH_CMN_PROC_SLCTD_FOR_RETX(proc) ||
            (proc->hqE->ccchSduProc == proc))
      {
         RETVALUE(FALSE); 
      }
      /* UE is scheduled for either other services or TA */
      /* pfsProc->retxLstCp would have been set the first
       * time proc was obtained */
   } 

   RETVALUE(TRUE);
}

/**
 * @brief  Function to change the LC priority according to next favCell
 *         and move in to the priority queue if required. 
 *
 * @details
 *
 *     Function : rgSchPfsChngLcPrio
 *
 *  @param[in]  RgSchcellCb        *cell
 *  @param[in]  RgSchDlLcCb        *lc
 *  @param[in]  RgSchPfsDlLc       *pfsLc
 *  @param[in]  RgSchDlLcCb        *nxtLc
 *  @param[in]  CmLListCp          *txQ
 *  @return     Bool
 **/
#ifdef ANSI
PRIVATE Bool rgSchPfsChngLcPrio
(
RgSchCellCb        *cell,
RgSchDlLcCb        *lc,
RgSchPfsDlLc       *pfsLc,
RgSchDlLcCb        *nxtLc,
CmLListCp          *txQ
)
#else
PRIVATE Bool rgSchPfsChngLcPrio(cell, lc, pfsLc, nxtLc, txQ)
RgSchCellCb        *cell;
RgSchDlLcCb        *lc;
RgSchPfsDlLc       *pfsLc;
RgSchDlLcCb        *nxtLc;
CmLListCp          *txQ;
#endif
{ 
   RgSchEnbPfsDl   *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(cell);
   U8              cellIdx   = lc->ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(cell)];

   TRC2(rgSchPfsChngLcPrio);

   /* maintaining the favCell priority of this LC so that
    * if LC is not scheduled it can be used to reset the 
    * LC priority based on itf favCell  */
   if(!pfsLc->prioChngLnk.node)
   {   
      pfsLc->favCellPrio = pfsLc->pfsPrio;
      pfsLc->favCellPrioLstCp = txQ;

      /* Adding this LC in the list because LC priority has got 
       * changed due to cell change and later we need to push this
       * LC back in the prio queue based on its favCell */
      pfsLc->prioChngLnk.node = (PTR)lc;
      cmLListAdd2Tail(&(pfsEnbDl->prioChngLcLst), &(pfsLc->prioChngLnk)); 
   }

   if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
   {
      RgSchPfsDlUe     *pfsUe = RG_SCH_PFS_GET_PFSUEDL(lc->ue, cell);
      pfsLc->pfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
            pfsEnbDl->tbls.fairPrios[pfsUe->cmnParam->fracPrioInfo.fracPrioLvls] *
            (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
         (pfsEnbDl->prioScaleFact); 
   }
   else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
   {
      pfsLc->pfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
            pfsEnbDl->tbls.fairPrios[pfsLc->fracPrioInfo.fracPrioLvls] *
            (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
         (pfsEnbDl->prioScaleFact); 
   }

   if(nxtLc != NULLP)
   {
      RgSchPfsDlLc   *nxtPfsLc = RG_SCH_PFS_GET_PFSDLLC(nxtLc->ue, nxtLc);
      /* This is the case when LC is being added for first time 
       * during estimation phase */
      /* Comparing the priority of this LC with the next lc in the list 
       * to check if this LC needs to be repositioned in the prio queue 
       * */
      if(pfsLc->pfsPrio < nxtPfsLc->pfsPrio)  
      {
         rgSchPfsUpdPrioQ(cell, lc->ue, pfsLc);
         RETVALUE(FALSE);
      }
   }
   else
   {
      /* This is the case when UE is moving to next fav cell 
       * after finalization */
      rgSchPfsUpdPrioQ(cell, lc->ue, pfsLc);
   }

   RETVALUE(TRUE);
}

/**
 * @brief  Function to calculate total PFS priority and number of 
 *         PRBs required for an UE. 
 *
 * @details
 *
 *     Function : rgSchPfsCalcUePrbAndPrio
 *
 *  @param[in]  RgSchcellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @param[in]  U32                totalBo
 *  @return     Bool
 **/
#ifdef ANSI
PRIVATE Void rgSchPfsCalcUePrbAndPrio
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlHqProcCb    *proc
)
#else
PRIVATE Bool rgSchPfsCalcUePrbAndPrio(cell, ue, proc)
RgSchCellCb        *cell;
RgSchUeCb          *ue;
RgSchDlHqProcCb    *proc;
#endif
{
   RgSchEnbPfsDl         *pfsEnbDl = rgSchCb[cell->instIdx].rgSchEnbPfsDl;
   RgSchPfsDlUe          *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
   RgSchPfsDlCell        *pfsCell = RG_SCH_PFS_GET_PFSCELLDL(cell);
   RgSchPfsDlLcSchdInfo  *toBeSchedInfoPerCell = &pfsCell->rgSchPfsLcSchdInfo;
   RgSchPfsDlLc          *pfsLc;
   CmLList               *node  = NULLP;
   U32                    prbReqrd = 0;

   TRC2(rgSchPfsCalcUePrbAndPrio);

   node = pfsUe->cmnParam->svcPriorLst.first;
   while(node)
   {
      RgSchDlLcCb *lc = (RgSchDlLcCb *) node->node; 
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
      pfsUe->totalPfsPrio += pfsLc->pfsPrio;

      if(pfsUe->maxPfsPrio < pfsLc->pfsPrio)
      {
         pfsUe->maxPfsPrio = pfsLc->pfsPrio;
         pfsUe->cmnParam->highestPrioLc = lc;
      }   
      if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_SRB)
      {
         proc->hasDcch = TRUE;
      }

      RG_SCH_CMN_DL_GET_HDR_EST(lc, pfsLc->hdrSz);
      pfsLc->reqBytes = pfsLc->effBo + pfsLc->hdrSz;
      pfsUe->totalEffBo += pfsLc->effBo;
      pfsUe->totalHdrSz += pfsLc->hdrSz;

      rgSCHPfsAddLcToSchedLst(lc, &(pfsUe->schedSvcs));

      node = node->next;
   }  

   /* Calc number of PRBs needed for this LC*/
   rgSchUtlCalcTotalPrbReq(cell, ue, pfsUe->totalEffBo, &prbReqrd);

   pfsUe->totalPrbReqd = prbReqrd;
   pfsUe->cmnParam->isUeSchd = TRUE;

   /* Adding this UE into the schedLst only if there is atleast one LC
    * to be scheduled for this UE because this function can be called even 
    * in the case where TA or sCell Act CE is scheduled for this UE.
    * By not adding in this list, if TA alone is scheduled for this UE,we 
    * will ignore calling function rgSCHCmnDlAllocTxRb twice. which is already 
    * called in case of TA amd sCell Act CE scheduling from the caller funciton*/
   if(pfsUe->cmnParam->svcPriorLst.count)
   {   
      rgSCHPfsAddUeToSchedLst(cell, ue, &(toBeSchedInfoPerCell->ueLst));
      toBeSchedInfoPerCell->totPrbReq += pfsUe->totalPrbReqd;
      toBeSchedInfoPerCell->totPfsPrio += pfsUe->totalPfsPrio;

      if ((pfsEnbDl->currPrioMmbrSta == TRUE) && (ue->csgMmbrSta == TRUE))
      {
         toBeSchedInfoPerCell->prioUeTotPfsPrio += pfsUe->totalPfsPrio;
         toBeSchedInfoPerCell->totPrioBwReq += pfsUe->totalPrbReqd;
         toBeSchedInfoPerCell->numPrioUe += 1;
      }
      else
      {
         toBeSchedInfoPerCell->totNonPrioBwReq += pfsUe->totalPrbReqd;
      } 
   }
}

/**
 * @brief  Utility function to schedule the UEs based on 
 * their highest  prio LC. 
 *
 * @details
 *
 *     Function : rgSchPfsCreateLcSchedLst
 *  this function schdeuled the UEs for all the cells based on 
 *  the highest priority LC of an UE. 
 *
 *  @param[in]  CmLListCp             *txQ 
 *  @param[in]  U8                    *remCellCnt
 *  @param[in]  U8                     qId
 *  @return     S16 
 **/
#ifdef ANSI
PRIVATE S16 rgSchPfsCreateLcSchedLst
(
 CmLListCp             *txQ,
 U8                    *remCellCnt,
 U8                    qId
 )
#else
PRIVATE S16 rgSchPfsCreateLcSchedLst(txQ, remCellCnt, qId) 
   CmLListCp             *txQ;
   U8                    *remCellCnt;
   U8                    qId;
#endif
{
   CmLList               *lnk;
   RgSchPfsDlCell        *pfsCell;
   RgSchPfsDlLcSchdInfo  *toBeSchedInfoPerCell;
   RgSchDlSf             *sf;
   RgSchCmnDlUe          *ueDl;

   TRC2(rgSchPfsCreateLcSchedLst);

   for (lnk = txQ->first; lnk; )
   {
      RgSchDlLcCb        *lc    = (RgSchDlLcCb *)lnk->node;
      RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
      RgSchDlHqProcCb    *proc  = NULLP;
      CmLList            *cellNode  = pfsLc->cellFavLst.first;
      RgSchCellCb        *favCell  = (RgSchCellCb *)(cellNode->node);
      RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(lc->ue, lc->ue->cell);
      CmLListCp          *retxQ = NULLP;

      lnk = lnk->next;

      if((!RG_SCH_CMN_DL_IS_UE_ACTIVE(lc->ue)) || (pfsUe->cmnParam->isUeSchd))
      {
         /* This UE is already scheduled throgh one cell, no need to 
          * add this UE for other cell scheduling list*/
         continue;
      }   

      /* Will scen through the list of cells of an UE in the order of 
       * their favourablilty to schedule the UE */
      for (;cellNode; cellNode = cellNode->next)
      {   
#ifdef TENB_ACC
         RgSchCellCb  *cell = (RgSchCellCb *)(cellNode->node);     
#else
         RgSchCellCb  *cell = lc->ue->cell;     
#endif
         RgSchUeCb    *ue   = lc->ue;  
#ifdef LTE_ADV
         U8           cellIdx = ue->cellIdToCellIdxMap\
                                [RG_SCH_CELLINDEX(cell)];
#endif
         pfsCell   =  RG_SCH_PFS_GET_PFSCELLDL(cell);
         ueDl      = RG_SCH_CMN_GET_DL_UE(ue, cell);
         pfsUe     = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
         toBeSchedInfoPerCell = &pfsCell->rgSchPfsLcSchdInfo;
         sf        = toBeSchedInfoPerCell->sf;

#ifdef LTE_ADV
         /* If we find a cell in deactivate state then no need to traverse 
          * throgh the cell list as all other further cells in the list 
          * will also be in deactivated state */
         if(ue->cellInfo[cellIdx]->sCellState != RG_SCH_SCELL_ACTIVE)  
         {
            break;
         }   
#endif

         /* checking if UE can be schduled throgh this cell. if not,
          * go to the next cell in the favourablilty list of cells */
         if((rgSchPfsChkUeSched(cell, ue, sf)) == FALSE)
         {
            continue;
         }

         /* if this LC is not scheduled throgh its favCell then need to recalculate 
          * the priority of this LC as per this cell. Based on its new priority,  
          * LC can be scheduled immediately or it will be schduled later as per
          * its new position in prioriy queue. */
         if(cell != favCell)
         {
            /* If this LC is already added in prioChngLcLst and there is no 
             * more favCell available, it means this LC was added in this 
             * list for this cell only. Skip calling this function and
             * continue for scheduling */
            if((!(pfsLc->prioChngLnk.node))|| 
               ((pfsLc->prioChngLnk.node) && (cellNode->next)))
            {
               /* if there is next lc present then compare the current LC 
                * priority with the next lc prioroty */
               if(lnk)
               {   
                  RgSchDlLcCb  *nxtLc = (RgSchDlLcCb *)lnk->node;
                  if(rgSchPfsChngLcPrio(cell, lc, pfsLc, nxtLc, txQ) == FALSE)
                  {
                     break;                  
                  }
               }   
            }   
         }

#ifdef LTE_ADV
#ifdef RG_PFS_STATS
         {
            U8   favCellIdx = ue->cellIdToCellIdxMap[RG_SCH_CELLINDEX(favCell)];
            ue->pfsStats.lcStats[lc->lcId-1].favCellCnt[favCellIdx]++;
         }
#endif
#endif

         rgSchPfsGetRetxQ(pfsCell, pfsLc, qId, &retxQ);

         if ((proc = rgSCHPfsDlGetAvlProc(cell, ue, retxQ)) == NULLP)
         {
            continue;
         }
         ueDl->proc = proc;

#ifdef LTE_ADV
         if(RG_SCH_IS_CELL_SEC(ue, cell))
         {
            U8   tpcIdx = 0;
            if(ROK != rgSchGetAvlTpcIdx(ue, &tpcIdx, 
                                         sf, cell))
            {
               rgSCHPfsDlRlsHqProc(ue, proc);
               ueDl->proc = NULLP;
               continue;
            }
            ueDl->proc->tpc = tpcIdx;
         }
#endif

         /* calling this function to calcualte UE's total PFS priority 
          * and Total PRB required */
         rgSchPfsCalcUePrbAndPrio(cell, ue, proc);

         if(!(--sf->remUeCnt))
         {
            (*remCellCnt)--; 

            if(!(*remCellCnt))
            {
               RETVALUE(ROK);
            }   
         }   
         break;
      }
   }
   RETVALUE(ROK);
}
#if RG_UNUSED
/**
 * @brief  Utility function to create two separate lists for DL Lcs of cell 
 * edge and cell centre UEs. 
 *
 * @details
 *
 *     Function : rgSchPfsCreateSfrAbsDlLcLst
 *
 *     This API creates two separate lists for Dl Lcs of cell edge and cell
 *     centre UEs. It also calculates separately the total Cqi of cell edge UEs
 *     and cell centre UEs.
 *
 *       - For each LC in queue
 *       - If UE is not scheduled for retx
 *         - Schedule for new tx
 *       - Else if UE already scheduled for new tx
 *         - Add to existing allocation
 *
 *  @param[in]  RgSchCellCb           *cell
 *  @param[in]  CmLListCp             *txQ 
 *  @param[in]  CmLListCp             *retxQ 
 *  @param[in]  RgSchCmnDlRbAllocInfo *alloc
 *  @param[in]  CmLListCp             *ceLcLst
 *  @param[in]  CmLListCp             *otherUeLcLst
 *  @param[in]  U32                   *ceTotPfsPrio
 *  @param[in]  U32                   *totPfsPrio
 *  @param[in]  U32                   *lcCntForSlctdUes
 *  @return     U8
 **/
#ifdef ANSI
PRIVATE U8 rgSchPfsCreateSfrAbsDlLcLst
(
RgSchCellCb             *cell,
CmLListCp               *txQ,
CmLListCp               *retxQ,
RgSchCmnDlRbAllocInfo   *alloc,
RgSchPfsDlLcSchdInfo      *toBeSchedInfo
)
#else
PRIVATE U8 rgSchPfsCreateSfrAbsDlLcLst(cell, txQ,retxQ, alloc,toBeSchedInfo)
RgSchCellCb             *cell;
CmLListCp               *txQ;
CmLListCp               *retxQ;
RgSchCmnDlRbAllocInfo   *alloc;
RgSchPfsDlLcSchdInfo      *toBeSchedInfo;
#endif
{
   CmLList            *lnk;
   Bool               isCellEdgeUe = FALSE;
   RgSchDlSf          *sf      = alloc->dedAlloc.dedDlSf;
   U32                prbReqrd;
#ifdef LTEMAC_HDFDD
   Bool                 dlAllowed = FALSE;
#endif

   for (lnk = txQ->first; lnk; lnk = lnk->next)
   {      
      RgSchDlLcCb        *lc = (RgSchDlLcCb *)lnk->node;
      RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
      RgSchCmnDlUe       *ueDl = RG_SCH_CMN_GET_DL_UE(lc->ue, cell);
      RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(lc->ue, cell);
      RgSchDlHqProcCb    *proc  = NULLP;

#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(lc->ue))
      {
         rgSCHCmnHdFddChkDlAllow ( cell, lc->ue, &dlAllowed);
         if (dlAllowed == FALSE)
         {
            continue;
         }
      }
#endif

#ifdef LTEMAC_SPS
      CmLteTimingInfo      schdTime;
      schdTime = cell->crntTime;

      /* Increment by DL DELTA to determine the time for which scheduling
       * is done */
      RGSCH_INCR_SUB_FRAME(schdTime, RG_SCH_CMN_DL_DELTA);
      if (RG_SCH_CMN_IS_UE_SPS_SCHDLD(lc->ue, cell, schdTime) || !RG_SCH_CMN_DL_IS_UE_ACTIVE(lc->ue))
      {
         continue;
      }
#endif

      /* Mark the UE as cell edge in alloc info */
      if((RGR_ENABLE == cell->lteAdvCb.sfrCfg.status) &&
         (TRUE == lc->ue->lteAdvUeCb.rgrLteAdvUeCfg.isUeCellEdge))
      {
         alloc->dedAlloc.dedDlSf->sfrTotalPoolInfo.isUeCellEdge = TRUE;
      }

      /* Turn on the cell edge UE flag for inserting the the cell edge list */
      if (((RGR_ENABLE == cell->lteAdvCb.sfrCfg.status) && \
           (TRUE == alloc->dedAlloc.dedDlSf->sfrTotalPoolInfo.isUeCellEdge)) || \
           ((RGR_ENABLE == cell->lteAdvCb.absCfg.status) && \
           (TRUE == lc->ue->lteAdvUeCb.rgrLteAdvUeCfg.isAbsUe)))
    
      {
         isCellEdgeUe = TRUE;
      }
      
      /* Turn off the cell edge UE flag for inserting the the cell edge list */
      else if (((RGR_ENABLE == cell->lteAdvCb.sfrCfg.status) && \
         (FALSE == lc->ue->lteAdvUeCb.rgrLteAdvUeCfg.isUeCellEdge)) || \
         ((RGR_ENABLE == cell->lteAdvCb.absCfg.status) && \
         (FALSE == lc->ue->lteAdvUeCb.rgrLteAdvUeCfg.isAbsUe)))
      {
         isCellEdgeUe = FALSE;
      }
      /* This means SFR and ABS is disabled */
      else
      {
         continue;
      }

      if (RG_SCH_CMN_IS_UE_SCHDLD(lc->ue, cell))
      {
         proc = (RgSchDlHqProcCb *)ueDl->proc;
         /* Don't do anything if UE already scheduled for retx */
         if (RG_SCH_CMN_PROC_SLCTD_FOR_RETX(proc) ||
             (proc->hqE->ccchSduProc == proc))
         {
            continue;
         }
         /* UE is scheduled for either other services or TA */
         /* pfsProc->retxLstCp would have been set the first
          * time proc was obtained */
      }
      else
      {
         if (sf->remUeCnt == 0)
         {
            if((toBeSchedInfo->ceLcLst.count + toBeSchedInfo->otherUeLcLst.count) >= 
                  sf->totalLcCntOfSlctdUes)
            {
              /* All LC's of the the selected UE's
               * are served. No need to scan further
               * priority queue in this TTI*/
               RETVALUE(RFAILED);
            }

            continue;
         }
 
         /* Assign the Harq Proc here */
         if ((proc = rgSCHPfsDlGetAvlProc(cell, lc->ue, retxQ)) == NULLP)
         {
            continue;
         }
         --sf->remUeCnt;
         ueDl->proc = proc;
         
         /* Update the number of Lcs to be served for each UE */
         sf->totalLcCntOfSlctdUes += pfsUe->cmnParam->svcPriorLst.count;
      }
  
      /* Calc number of PRBs needed for each UE */
      rgSchUtlCalcTotalPrbReq(cell, lc->ue, pfsLc->effBo, &prbReqrd);
      lc->prbsReqd = prbReqrd;
 
      /* Store the CQI sum of all the UEs to distribute the bandwidth later for
       * MUE. Insert the LCs in these two lists in the final list in ascending
       * order of the PRBs needed - first cell edge UEs and then cell centre
       * UEs. */
      toBeSchedInfo->totPrbReq += prbReqrd;

      if(isCellEdgeUe)
      {
         toBeSchedInfo->ceTotPfsPrio += pfsLc->pfsPrio;
         rgSCHPfsAddLcToSchedLst(lc,&(toBeSchedInfo->ceLcLst));
      }
      else
      {
         toBeSchedInfo->totPfsPrio += pfsLc->pfsPrio;
         rgSCHPfsAddLcToSchedLst(lc,&(toBeSchedInfo->otherUeLcLst));
      }   
      if (sf->remUeCnt == 0)
      {
         if((toBeSchedInfo->ceLcLst.count + toBeSchedInfo->otherUeLcLst.count) >= 
               sf->totalLcCntOfSlctdUes)
         {
            /* All LC's of the the selected UE's
             * are served. No need to scan further
             * priority queue in this TTI*/
            RETVALUE(RFAILED);
         }
      }

   }
   RETVALUE(ROK);
}

/**
 * @brief  Utility function to keep a count of the LCs of selected UEs. 
 *
 * @details
 *
 *     Function : rgSchPfsCreateNonAbsUeDlLcLst
 *
 *     This API creates a list for Dl Lcs of cell centre UEs and of UEs to be
 *     scheduled in the non ABS subframes. It also calculates the total Cqi of
 *     the UEs added in this list.
 *
 *       - For each LC in queue
 *       - If UE is not scheduled for retx
 *         - Schedule for new tx
 *       - Else if UE already scheduled for new tx
 *         - Add to existing allocation
 *
 *  @param[in]  RgSchCellCb     *cell
 *  @param[in]  CmLListCp       *txQ 
 *  @param[in]  RgSchDlSf       *sf
 *  @param[in]  CmLListCp       *lcToBeSchedLst
 *  @param[in]  U32             *totPfsPrio
 *  @param[in]  U32             *lcCntForSlctdUes
 *  @return     U8
 **/
#ifdef ANSI
PRIVATE U8 rgSchPfsCreateNonAbsUeDlLcLst
(
RgSchCellCb     *cell,
CmLListCp       *txQ,
CmLListCp       *retxQ,
RgSchDlSf       *sf,
RgSchPfsDlLcSchdInfo      *toBeSchedInfo
)
#else
PRIVATE U8 rgSchPfsCreateNonAbsUeDlLcLst(cell, txQ,retxQ, sf, toBeSchedInfo)
RgSchCellCb     *cell;
CmLListCp       *txQ;
CmLListCp       *retxQ;
RgSchDlSf       *sf;
RgSchPfsDlLcSchdInfo      *toBeSchedInfo;
#endif
{
   CmLList            *lnk;
   U32                prbReqrd;
#ifdef LTEMAC_HDFDD
   Bool                 dlAllowed = FALSE;
#endif


   for (lnk = txQ->first; lnk; lnk = lnk->next)
   {      
      RgSchDlLcCb        *lc = (RgSchDlLcCb *)lnk->node;
      RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
      RgSchDlHqProcCb    *proc  = NULLP;
      
      if(cell->lteAdvCb.absCfg.absPatternType & RGR_ABS_TRANSMIT)
      {
         if(TRUE == lc->ue->lteAdvUeCb.rgrLteAdvUeCfg.isAbsUe)
         {
            continue;
         }
      }
      
      RgSchCmnDlUe       *ueDl = RG_SCH_CMN_GET_DL_UE(lc->ue, cell);
      RgSchPfsDlUe       *pfsUe = RG_SCH_PFS_GET_PFSUEDL(lc->ue, cell);

#ifdef LTEMAC_HDFDD
      if (RG_SCH_HDFDD_UE_ENBLD(lc->ue))
      {
         rgSCHCmnHdFddChkDlAllow ( cell, lc->ue, &dlAllowed);
         if (dlAllowed == FALSE)
         {
            continue;
         }
      }
#endif

#ifdef LTEMAC_SPS
      CmLteTimingInfo      schdTime;
      schdTime = cell->crntTime;
 
      /* Increment by DL DELTA to determine the time for which scheduling
       * is done */
      RGSCH_INCR_SUB_FRAME(schdTime, RG_SCH_CMN_DL_DELTA);
      if (RG_SCH_CMN_IS_UE_SPS_SCHDLD(lc->ue, cell, schdTime) || !RG_SCH_CMN_DL_IS_UE_ACTIVE(lc->ue))
      {
         continue;
      }
#endif

      if (RG_SCH_CMN_IS_UE_SCHDLD(lc->ue, cell))
      {
         proc = (RgSchDlHqProcCb *)ueDl->proc;
         /* Don't do anything if UE already scheduled for retx */
         if (RG_SCH_CMN_PROC_SLCTD_FOR_RETX(proc) ||
             (proc->hqE->ccchSduProc == proc))
         {
            continue;
         }
         /* UE is scheduled for either other services or TA */
         /* pfsProc->retxLstCp would have been set the first
          * time proc was obtained */
      }
      else
      { 
         if (sf->remUeCnt == 0)
         {
            if(toBeSchedInfo->otherUeLcLst.count >= sf->totalLcCntOfSlctdUes)
            {
              /* All LC's of the the selected UE's
               * are served. No need to scan further
               * priority queue in this TTI*/
               RETVALUE(RFAILED);
            }

            continue;
         }
  
         /* Assign the Harq Proc here */
         if ((proc = rgSCHPfsDlGetAvlProc(cell, lc->ue, retxQ)) == NULLP)
         {
            continue;
         }
         --sf->remUeCnt;
         ueDl->proc = proc;
         
         /* Update the number of Lcs to be served for each UE */
         sf->totalLcCntOfSlctdUes += pfsUe->cmnParam->svcPriorLst.count;
      }
  
      /* Calc number of PRBs needed for each UE */
      rgSchUtlCalcTotalPrbReq(cell, lc->ue, pfsLc->effBo, &prbReqrd);
      lc->prbsReqd = prbReqrd;

      /* Sort the created list in increasing order of PRBs needed */
      toBeSchedInfo->totPrbReq += prbReqrd; 
      /* Store the Pfs Prio sum of all the UEs to distribute the bandwidth later for
       * MUE */
      toBeSchedInfo->totPfsPrio += pfsLc->pfsPrio;
      rgSCHPfsAddLcToSchedLst(lc, &(toBeSchedInfo->otherUeLcLst));
      if (sf->remUeCnt == 0)
      {
         if(toBeSchedInfo->otherUeLcLst.count >= sf->totalLcCntOfSlctdUes)
         {
            /* All LC's of the the selected UE's
	     * are served. No need to scan further
	     * priority queue in this TTI*/
            RETVALUE(RFAILED);
         }
      }
  }
  RETVALUE(ROK);
}
#endif

/**
 * @brief  Utility function to create an LC list in increasing order of PRBs
 * needed. 
 *
 * @details
 *
 *     Function : rgSCHPfsAddLcToSchedLst
 *
 *     If PRBs needed are less than minimum, insert at the head,
 *     Else if PRBs needed are greater than max, insert at the tail,
 *     Else traverse through the list and insert at the appropriate place.
 *
 *  @param[in]  RgSchCmnDlUe   *cmnUe
 *  @param[in]  RgSchDlLcCb    *lc
 *  @param[in]  CmLListCp      *lcToBeSchedLst
 *  @return     Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsAddLcToSchedLst
(
RgSchDlLcCb        *lc,
CmLListCp          *lcToBeSchedLst
)
#else
PRIVATE Void rgSCHPfsAddLcToSchedLst (lc, lcToBeSchedLst)
RgSchDlLcCb        *lc;
CmLListCp          *lcToBeSchedLst;
#endif
{
   
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
   CmLList            *lcInLst; 
   CmLList            *lastLcInLst;
   RgSchDlLcCb        *lc2;
   RgSchPfsDlLc       *pfsLc2; 

   CM_LLIST_FIRST_NODE(lcToBeSchedLst,lcInLst);
   
   pfsLc->statusScheduled = TRUE;
   if(NULLP == lcInLst)
   {
      /* first node to be added to the list */
      cmLListAdd2Tail((lcToBeSchedLst),&(lc->schdLnk));
      lc->schdLnk.node = (PTR)lc;
      RETVOID;
   }

   lastLcInLst = lcToBeSchedLst->last;
   lc2 = (RgSchDlLcCb *)(lastLcInLst->node);
   pfsLc2 = RG_SCH_PFS_GET_PFSDLLC(lc2->ue, lc2);

   /* If the last LC in the sorted list have lesser reqBytes than the current,
    * insert at the end. */
   if(pfsLc->reqBytes >= pfsLc2->reqBytes)
   {
      cmLListAdd2Tail((lcToBeSchedLst),&(lc->schdLnk));
      lc->schdLnk.node = (PTR)lc;
   }
   else
   {
      /* Scan through the sorted list and insert at the appropriate position */
      do
      {
         lc2 = (RgSchDlLcCb *)(lcInLst->node);
         pfsLc2 = RG_SCH_PFS_GET_PFSDLLC(lc2->ue, lc2);

         if(pfsLc->reqBytes <= pfsLc2->reqBytes)
         {
            cmLListInsCrnt((lcToBeSchedLst),&(lc->schdLnk));
            lc->schdLnk.node = (PTR)lc;
            break;
         }

         CM_LLIST_NEXT_NODE(lcToBeSchedLst, lcInLst);
      }while(NULLP != lcInLst);
   }
   RETVOID;
}

/**
 * @brief This function releases the harq process and 
 * resets the required params as a part of scheduling failure 
 *
 * @details
 *
 *     Function : rgSCHPfsRlsSchedRes
 *
 *     This function releases the harq process and 
 *     resets the required params as a part of scheduling failure 
 *
 *  @param[in]  RgSchUeCb             *ue
 *  @param[in]  RgSchCmnDlRbAllocInfo *alloc
 *  @return     Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsRlsSchedRes
(
RgSchCellCb     *cell,
RgSchUeCb *ue,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHPfsRlsSchedRes(cell, ue,alloc)
RgSchCellCb             *cell;
RgSchUeCb               *ue;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   RgSchCmnDlUe       *ueDl    = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchPfsDlUe       *pfsUe   = RG_SCH_PFS_GET_PFSUEDL(ue, cell);

   if(ueDl->proc)
   {
      RgSchCmnDlHqProc   *cmnProc = (RgSchCmnDlHqProc *)ueDl->proc->sch;

      if (cmnProc->totBytes == 0)
      {
         /* None of the LC for this UE got scheduled
          * Release the harq and reset the values*/
#ifdef LTE_ADV
         rgSchFreeTpcIdxForSCell(ue, ueDl->proc, alloc->dedAlloc.dedDlSf);
#endif
       
         rgSCHPfsDlRlsHqProc(ue, ueDl->proc);

         if(ueDl->proc->reqLnk.node != (PTR)NULLP)
         {
            cmLListDelFrm(&alloc->dedAlloc.txHqPLst, &ueDl->proc->reqLnk);
            ueDl->proc->reqLnk.node = (PTR)NULLP;
         }
         /*Re-set the outstanding alloc information.*/
         ueDl->outStndAlloc = 0;
         ueDl->proc = NULLP;

         /* Resetting the pfsUe parameters */
         pfsUe->taReq = FALSE;
#ifdef LTE_ADV
         pfsUe->schdSCellActCe = FALSE;
#endif
         pfsUe->totalPrbReqd = 0;
         pfsUe->totalPfsPrio = 0;
         pfsUe->totalHdrSz = 0;
         pfsUe->totalEffBo = 0;
         pfsUe->maxPfsPrio = 0;
         pfsUe->cmnParam->isUeSchd = FALSE; 
         cmLListInit(&(pfsUe->schedSvcs));
      }
   }
   RETVOID;
}

#if RG_UNUSED
/**
 * @brief Scheduling of DL new transmissions for SFR and ABS UEs
 *
 * @details
 *
 *     Function : rgSCHPfsDlNewTxInSfrAbsQ
 *
 *     Create two separate lists for storing the LCs of cell edge and cell
 *     centre UEs.
 *     Schedule Cell Edge UEs first.
 *     If bandwidth remains, schedule Cell Centre UEs if any.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *alloc
 *  @param[in]  CmLListCp              *txQ
 *  @param[in]  CmLListCp              *retxQ
 *  @param[in]  Bool                   *isBwLeftRef
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlNewTxInSfrAbsQ
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc,
CmLListCp               *txQ,
CmLListCp               *retxQ,
Bool                    *isBwLeftRef,
RgSchPfsDlLcSchdInfo      *toBeSchedInfo
)
#else
PRIVATE Void rgSCHPfsDlNewTxInSfrAbsQ(cell, alloc, txQ, retxQ, isBwLeftRef,
      toBeSchedInfo)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
CmLListCp               *txQ;
CmLListCp               *retxQ;
Bool                    *isBwLeftRef;
RgSchPfsDlLcSchdInfo      *toBeSchedInfo;
#endif
{
   S16                ret;
   
   /* Select the LC list for CE and CC Ues*/
   ret = rgSchPfsCreateSfrAbsDlLcLst(cell, txQ,retxQ, alloc,toBeSchedInfo);
  
   if(ret == RFAILED)
   {
      /* All LC's of the the selected UE's
       * are served. No need to scan further
       * priority queue in this TTI*/
     *isBwLeftRef = FALSE;
   }

   RETVOID;
}

/**
 * @brief Scheduling of DL new transmissions for cell centre or Non ABS UEs
 *
 * @details
 *
 *     Function : rgSCHPfsDlNewTxInNonAbsQ
 *
 *     Creates a list for storing the LCs of cell centre or non ABS UEs and
 *     schedules them.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo   *alloc
 *  @param[in]  CmLListCp              *txQ
 *  @param[in]  CmLListCp              *retxQ
 *  @param[in]  Bool                   *isBwLeftRef
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlNewTxInNonAbsQ
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc,
CmLListCp               *txQ,
CmLListCp               *retxQ,
Bool                    *isBwLeftRef,
RgSchPfsDlLcSchdInfo      *toBeSchedInfo
)
#else
PRIVATE Void rgSCHPfsDlNewTxInNonAbsQ(cell, alloc, txQ, retxQ, isBwLeftRef,toBeSchedInfo)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
CmLListCp               *txQ;
CmLListCp               *retxQ;
Bool                    *isBwLeftRef;
RgSchPfsDlLcSchdInfo      *toBeSchedInfo;
#endif
{
   RgSchDlSf          *sf      = alloc->dedAlloc.dedDlSf;
   S16                ret;
  
   /* Create the LC list for cell centre or non ABS UEs */
   ret = rgSchPfsCreateNonAbsUeDlLcLst(cell, txQ,retxQ, sf,toBeSchedInfo);

   if(ret == RFAILED)
   {
      /* All LC's of the the selected UE's
       * are served. No need to scan further
       * priority queue in this TTI*/
     *isBwLeftRef = FALSE;
   }

   RETVOID;
}
#endif
/**
 * @brief Scheduling of DL new transmissions for cell centre or Non ABS UEs
 *
 * @details
 *
 *     Function : rgSCHPfsDlNewTxInNormQ
 *
 *     Creates a list of all the UEs when SFR and ABS are disabled and schedules
 *     them.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in] RgSchCmnDlRbAllocInfo  *alloc
 *  @param[in]  CmLListCp              *txQ
 *  @param[in]  CmLListCp              *retxQ
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlNewTxInNormQ
(
CmLListCp               *txQ,
U8                      *remCellCnt,
U8                      qId
)
#else
PRIVATE Void rgSCHPfsDlNewTxInNormQ(txQ, remCellCnt, qId)
CmLListCp               *txQ;
U8                      *remCellCnt;
U8                      qId;
#endif
{
   rgSchPfsCreateLcSchedLst(txQ, remCellCnt, qId);
  
   RETVOID;
}

#ifdef LTE_ADV
/**
 * @brief Deleting UE from its current favorite cell scheduling List
 *
 * @details
 *
 *     Function : rgSCHDelUeFromCellSchdLst
 *
 *     Removing UE from its current faqvorite cell UeLst and also releasing Harq
 *     Proc and N1PUCCH resource
 *
 *  @param[in]  RgSchPfsDlLcSchdInfo     *lcToBeSchedInfo
 *  @param[in]  RgSchUeCb              *nextCellDlUe
 *  @return   S16
 **/

#ifdef ANSI
PRIVATE S16 rgSCHDelUeFromCellSchdLst
(
 RgSchPfsDlLcSchdInfo  *lcToBeSchedInfo,  
 RgSchUeCb             *nextCellDlUe
)
#else
PRIVATE S16 rgSCHDelUeFromCellSchdLst(lcToBeSchedInfo, nextCellDlUe)
 RgSchPfsDlLcSchdInfo  *lcToBeSchedInfo;  
 RgSchUeCb             *nextCellDlUe;
#endif 
{
   RgSchCmnDlUe    *cmnUe = RG_SCH_CMN_GET_DL_UE(nextCellDlUe, lcToBeSchedInfo->cell);
   RgSchPfsDlUe    *pfsUe = RG_SCH_PFS_GET_PFSUEDL(nextCellDlUe, lcToBeSchedInfo->cell);

   /* Delete the UE from toBe shceduled List as higher PFS
    * priority UE is selected in this cell*/
   cmLListDelFrm(&(lcToBeSchedInfo->ueLst), &(pfsUe->toBeSchedLnk));
   lcToBeSchedInfo->totPrbReq  -= pfsUe->totalPrbReqd;

   lcToBeSchedInfo->totPfsPrio -= pfsUe->totalPfsPrio;

   rgSchFreeTpcIdxForSCell(nextCellDlUe, cmnUe->proc, lcToBeSchedInfo->sf);

   rgSCHPfsDlRlsHqProc(nextCellDlUe, cmnUe->proc);
   cmnUe->proc = NULLP;

   pfsUe->totalPrbReqd = 0;
   pfsUe->totalPfsPrio = 0;
   pfsUe->totalHdrSz = 0;
   pfsUe->totalEffBo = 0;
   pfsUe->maxPfsPrio = 0;
   pfsUe->cmnParam->isUeSchd = FALSE;

   cmLListInit(&(pfsUe->schedSvcs));

   RETVALUE(ROK);
}

/**
 * @brief Adding UE to its next favorite cell scheduling List
 *
 * @details
 *
 *     Function : rgSCHAddUeToCellSchdLst
 *
 *     Add UE and its all LCs to the next faqvorite cell.
 *
 *  @param[in]  RgSchPfsDlLcSchdInfo     *lcToBeSchedInfo
 *  @param[in]  RgSchDlLcCb            *lc
 *  @param[in]  RgSchUeCb              *ue
 *  @return   S16
 **/
#ifdef ANSI
PRIVATE S16  rgSCHAddUeToCellSchdLst
(
 RgSchPfsDlLcSchdInfo  *lcToBeSchedInfo,
 RgSchDlLcCb           *lc,
 RgSchUeCb             *ue,
 U32                   pfsPrioInNextCell
)
#else
PRIVATE S16  rgSCHAddUeToCellSchdLst(lcToBeSchedInfo, lc, ue, pfsPrioInNextCell)
 RgSchPfsDlLcSchdInfo  *lcToBeSchedInfo;
 RgSchDlLcCb         *lc;
 RgSchUeCb           *ue;
 U32                 pfsPrioInNextCell;
#endif
{
   RgSchDlHqProcCb      *proc;
   RgSchCmnDlUe         *cmnUe    = RG_SCH_CMN_GET_DL_UE(ue,lcToBeSchedInfo->cell);
   CmLList              *node  = NULLP;
   RgSchPfsDlLc         *pfsLc;
   RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, lcToBeSchedInfo->cell);
   U32                  maxPfsPrio = 0;
   U32                  prbReqrd;
   U8                   qId;
   CmLListCp            *retxQ = NULLP;
   RgSchPfsDlCell       *pfsCell = RG_SCH_PFS_GET_PFSCELLDL(lcToBeSchedInfo->cell);;

   /*[TODO]: Pick the retxQ from cell instead of rgschCb */
   if(cmnUe->proc != NULLP)
   {
      RETVALUE(RFAILED);
   }
   pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, lc);
   qId = rgSchPfsGetDlRetxQId(lcToBeSchedInfo->cell, ue, pfsLc, pfsPrioInNextCell);
   rgSchPfsGetRetxQ(pfsCell, pfsLc, qId, &retxQ);

   if ((proc = rgSCHPfsDlGetAvlProc(lcToBeSchedInfo->cell,
               lc->ue, retxQ)) == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cmnUe->proc = proc;
#ifdef LTE_ADV
   if(RG_SCH_IS_CELL_SEC(ue,lcToBeSchedInfo->cell))
   {
      U8  tpcIdx = 0;
      if(ROK != rgSchGetAvlTpcIdx(ue, &tpcIdx, 
               lcToBeSchedInfo->sf,lcToBeSchedInfo->cell))
      {
         rgSCHPfsDlRlsHqProc(ue, proc);
         cmnUe->proc = NULLP;
         RETVALUE(RFAILED);
      }
      cmnUe->proc->tpc = tpcIdx;
   }
#endif

   node = pfsUe->cmnParam->svcPriorLst.first;

   pfsUe->totalPfsPrio = 0;
   pfsUe->totalPrbReqd = 0;
   while(node)
   {
      lc = (RgSchDlLcCb *) node->node; 
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);

      if(pfsLc->favCellPrioLstCp != NULLP)
      {
         rgSchPfsChngLcPrio(lcToBeSchedInfo->cell, lc, pfsLc, NULLP, pfsLc->favCellPrioLstCp);
      }
      else
      {
         rgSchPfsChngLcPrio(lcToBeSchedInfo->cell, lc, pfsLc, NULLP, pfsLc->prioLstCp);
      }
      pfsUe->totalPfsPrio += pfsLc->pfsPrio;
      if(maxPfsPrio < pfsLc->pfsPrio)
      {
         maxPfsPrio = pfsLc->pfsPrio;
      }   

      RG_SCH_CMN_DL_GET_HDR_EST(lc, pfsLc->hdrSz);
      pfsLc->reqBytes = pfsLc->effBo + pfsLc->hdrSz;
      pfsUe->totalEffBo += pfsLc->effBo; 
      pfsUe->totalHdrSz += pfsLc->hdrSz;

      rgSCHPfsAddLcToSchedLst(lc, &(pfsUe->schedSvcs));

      node = node->next;
   }

   /* Set the highest Pfs Priority of LC in current Cell as PfsUe->maxPfsPrio.
    * It will be used to compare with the current Cell UeLst which is already 
    * prepared during Estimation */
   pfsUe->maxPfsPrio = maxPfsPrio;

   rgSchUtlCalcTotalPrbReq(lcToBeSchedInfo->cell, ue, pfsUe->totalEffBo, &prbReqrd);
   pfsUe->totalPrbReqd  = prbReqrd;

   lcToBeSchedInfo->totPfsPrio += pfsUe->totalPfsPrio;
   lcToBeSchedInfo->totPrbReq += pfsUe->totalPrbReqd;

   rgSCHPfsAddUeToSchedLst(lcToBeSchedInfo->cell, ue, &(lcToBeSchedInfo->ueLst));

   lcToBeSchedInfo->sf->remUeCnt--;
   RETVALUE(ROK);
}

/**
 * @brief Adding UE to its next favorite cell scheduling List
 *
 * @details
 *
 *     Function : rgSCHAddUeToNextCell
 *
 *     Add UE and its all LCs to the next faqvorite cell and also returns the
 *     next favorite Cell
 *
 *  @param[in]  RgSchPfsDlLcSchdInfo     *lcToBeSchedInfo
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchUeCb              *nextCellDlUe
 *  @return   S16
 **/
#ifdef ANSI
PRIVATE S16  rgSCHAddUeToNextCell
(
 RgSchPfsDlLcSchdInfo  *lcToBeSchedInfo,
 RgSchUeCb             *ue,
 U32                   pfsPrioInNextCell,
 RgSchUeCb             *nextCellDlUe
 )
#else
PRIVATE S16  rgSCHAddUeToNextCell(lcToBeSchedInfo, ue, pfsPrioInNextCell, nextCellDlUe)
   RgSchPfsDlLcSchdInfo *lcToBeSchedInfo;
   RgSchUeCb            *ue;
   U32                  pfsPrioInNextCell;
   RgSchUeCb            *nextCellDlUe;
#endif
{
   RgSchDlHqProcCb      *proc;
   RgSchCmnDlUe         *cmnUe    = RG_SCH_CMN_GET_DL_UE(ue,lcToBeSchedInfo->cell);
   RgSchDlLcCb          *lc;
   RgSchPfsDlLc         *pfsLc;
   RgSchPfsDlUe         *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, lcToBeSchedInfo->cell);
   CmLList              *node  = NULLP;
   U32                  maxPfsPrio = 0;
   U32                  prbReqrd;
   U8                   tpcIdx = 0;
   U8                   qId;
   CmLListCp            *retxQ=NULLP;
   U8                    cellIdx = RG_SCH_CELLINDEX(lcToBeSchedInfo->cell);
   U8                    lcCellIdx;
   RgSchPfsDlCell       *pfsCell = RG_SCH_PFS_GET_PFSCELLDL(lcToBeSchedInfo->cell);;

   if(cmnUe->proc != NULLP)
      RETVALUE(RFAILED);

   pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, pfsUe->cmnParam->highestPrioLc);
   qId = rgSchPfsGetDlRetxQId(lcToBeSchedInfo->cell, ue, pfsLc, pfsPrioInNextCell);

   rgSchPfsGetRetxQ(pfsCell, pfsLc, qId, &retxQ);

   if ((proc = rgSCHPfsDlGetAvlProc(lcToBeSchedInfo->cell, ue, retxQ)) == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cmnUe->proc = proc;

   if(RG_SCH_IS_CELL_SEC(ue, lcToBeSchedInfo->cell))
   {
      if(ROK != rgSchGetAvlTpcIdx(ue, &tpcIdx, lcToBeSchedInfo->sf,lcToBeSchedInfo->cell))
      {
         rgSCHPfsDlRlsHqProc(ue, proc);
         cmnUe->proc = NULLP;
         RETVALUE(RFAILED);
      }
      cmnUe->proc->tpc = tpcIdx;
   }

   node = pfsUe->cmnParam->svcPriorLst.first;

   pfsUe->totalPfsPrio = 0;
   pfsUe->totalPrbReqd = 0;
   while(node)
   {
      lc = (RgSchDlLcCb *) node->node; 
      lcCellIdx = lc->ue->cellIdToCellIdxMap[cellIdx];
      pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);

      if(pfsLc->favCellPrioLstCp != NULLP)
      {
         rgSchPfsChngLcPrio(lcToBeSchedInfo->cell, lc, pfsLc, NULLP, pfsLc->favCellPrioLstCp);
      }
      else
      {
         rgSchPfsChngLcPrio(lcToBeSchedInfo->cell, lc, pfsLc, NULLP, pfsLc->prioLstCp);
      }
      pfsUe->totalPfsPrio += pfsLc->pfsPrio;
      if(maxPfsPrio < pfsLc->pfsPrio)
      {
         maxPfsPrio = pfsLc->pfsPrio;
      }   

      RG_SCH_CMN_DL_GET_HDR_EST(lc, pfsLc->hdrSz);
      pfsLc->reqBytes = pfsLc->effBo + pfsLc->hdrSz;
      pfsUe->totalEffBo += pfsLc->effBo;
      pfsUe->totalHdrSz += pfsLc->hdrSz;

      rgSCHPfsAddLcToSchedLst(lc, &(pfsUe->schedSvcs));

      node = node->next;
   }

   /* Set the highest Pfs Priority of LC in current Cell as PfsUe->maxPfsPrio.
    * It will be used to compare with the current Cell UeLst which is already 
    * prepared during Estimation */
   pfsUe->maxPfsPrio = maxPfsPrio;
   rgSchUtlCalcTotalPrbReq(lcToBeSchedInfo->cell, ue, pfsUe->totalEffBo, &prbReqrd);
   pfsUe->totalPrbReqd  = prbReqrd;

   lcToBeSchedInfo->totPfsPrio += pfsUe->totalPfsPrio;
   lcToBeSchedInfo->totPrbReq += pfsUe->totalPrbReqd;

   rgSCHPfsAddUeToSchedLst(lcToBeSchedInfo->cell, ue, &(lcToBeSchedInfo->ueLst));

   /* Deleting the UE which has to be knocked out first from current Cell. */
   rgSCHDelUeFromCellSchdLst(lcToBeSchedInfo, nextCellDlUe);

   /* Select the LC which has highest PFS priority and which
    * was party allocd. Favorite cell of this LC will only be
    * used to select the next cell */
   pfsUe  = RG_SCH_PFS_GET_PFSUEDL(nextCellDlUe, lcToBeSchedInfo->cell);
   lc   = pfsUe->cmnParam->highestPrioLc;
   pfsLc  = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);

   /* remove the PfsUe from UeLst. Add this node in next
    * favCell UeLst is bandwidth is available */
   RETVALUE(ROK);
}/*rgSCHAddUeToNextCell*/

#ifdef LTE_ADV
/**
 * @brief Getting UE with lowest PFS priority from a Scheduling List
 *
 * @details
 *
 *     Function : rgSCHPfsGetMinPfsPrioUe
 *
 *     Compare UEs in ToBeScheduling UeLst and return the RgSchUe with lowest
 *     PFS Priority
 *
 *  @param[in]  RgSchCellCb            *favCell
 *  @param[in]  CmLListCp              *lst
 *  @param[out] RgSchUeCb              **nextCellDlUe
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsGetMinPfsPrioUe
(
 RgSchCellCb  *favCell,
 CmLListCp    *lst,
 RgSchUeCb    **nextCellDlUe
)
#else
PRIVATE Void rgSCHPfsGetMinPfsPrioUe(favCell, lst, nextCellDlUe)
 RgSchCellCb  *favCell;
 CmLListCp    *lst;
 RgSchUeCb   **nextCellDlUe;
#endif
{
   CmLList       *ueLnk;
   U32            minPfsPrio = 0;
   RgSchPfsDlUe  *pfsUe;
   RgSchUeCb     *ue;

   ueLnk = lst->first;
   ue  =  (RgSchUeCb *)ueLnk->node;
   pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, favCell);
   minPfsPrio     = pfsUe->maxPfsPrio;
   *nextCellDlUe =  ue;

   ueLnk = ueLnk->next;
   while(ueLnk != NULLP)
   {
      ue  =  (RgSchUeCb *)ueLnk->node;
      pfsUe         = RG_SCH_PFS_GET_PFSUEDL(ue, favCell);
      if(pfsUe->maxPfsPrio < minPfsPrio)
      {
         minPfsPrio     = pfsUe->maxPfsPrio;
         *nextCellDlUe =  ue;
      }
      ueLnk = ueLnk->next;
   }
   RETVOID;
}
#endif
/**
 * @brief Scheduling of DL new transmissions for cell centre or Non ABS UEs
 *
 * @details
 *
 *     Function : rgSCHPfsSchedLcInNextFavCell
 *
 *     Creates a list of all the UEs when SFR and ABS are disabled and schedules
 *     them.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *prevCellUe
 *  @param[in]  RgSchDlLcCb            *lc
 *  @return   S16
 **/
#ifdef ANSI
PRIVATE S16 rgSCHPfsSchedLcInNextFavCell
(
  RgSchCellCb            *cell,
  RgSchUeCb              *prevCellUe,
  RgSchDlLcCb            *lc
)
#else
PRIVATE S16 rgSCHPfsSchedLcInNextFavCell(cell, prevCellUe, lc)
  RgSchCellCb            *cell;
  RgSchUeCb              *prevCellUe;
  RgSchDlLcCb            *lc;
#endif
{
   RgSchPfsDlLc       *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);
   CmLList            *lnk;
   RgSchCellCb        *favCell;
   RgSchPfsDlLcSchdInfo *lcToBeSchedInfo;
   RgSchPfsDlUe       *nextCellPfsUe;
   RgSchUeCb          *nextCellDlUe;
   U32                 uePfsPrio = 0;

   /* Movement of UE to next Cell happen only when UE is a CA-UE. For NON-CA UE
    * case we can't schedule UE in other than Primary Cell */
   if(pfsLc->cellFavLst.count > 1)
   {
      lnk   = pfsLc->cellFavLst.first;
      while(lnk != NULLP)
      {
         favCell = (RgSchCellCb *)(lnk->node);
         RgSchPfsDlCell     *pfsFavCell = RG_SCH_PFS_GET_PFSCELLDL(favCell);
         if((!(pfsFavCell->isFnlzDone)) && (cell != favCell))
         {
            RgSchPfsDlUe     *pfsUe    = RG_SCH_PFS_GET_PFSUEDL(lc->ue, favCell);
            RgSchPfsDlCell   *pfsCell  = RG_SCH_PFS_GET_PFSCELLDL(favCell);
            RgSchEnbPfsDl    *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(favCell);
            U8               cellIdx   = prevCellUe->cellIdToCellIdxMap[RG_SCH_CELLINDEX(favCell)];      

            lcToBeSchedInfo            = &pfsCell->rgSchPfsLcSchdInfo;
            /* In this Cell remUeCnt is NON-ZERO i.e a UE can be added for
             * scheduling */
            if(pfsLc->lcType == RG_SCH_PFS_LC_TYPE_AMBR)
            {
               uePfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
                     pfsEnbDl->tbls.fairPrios[pfsUe->cmnParam->fracPrioInfo.fracPrioLvls] *
                     (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
                  (pfsEnbDl->prioScaleFact); 
            }
            else if (pfsLc->lcType == RG_SCH_PFS_LC_TYPE_GBR)
            {
               uePfsPrio = (pfsLc->cellSpfc[cellIdx].svccqiPrio * 
                     pfsEnbDl->tbls.fairPrios[pfsLc->fracPrioInfo.fracPrioLvls] *
                     (rgSchPfsQciPdbInfo[pfsLc->qci - 1].pdbPrioWgt[pfsLc->pdbLvl])) /
                  (pfsEnbDl->prioScaleFact); 
            }

            if(lcToBeSchedInfo->sf->remUeCnt > 0)
            {
               if(ROK == rgSCHAddUeToCellSchdLst(lcToBeSchedInfo, lc, prevCellUe, uePfsPrio))
               {
                  RETVALUE(ROK);
               }
               else
               {
                  lnk = lnk->next;
                  continue;
               }
            }
            else
            {
               RgSchPfsDlLc  *nextCellPfsLc;

               /* Because of re-transmission if there wont be any UE in ueLst. 
                * Don't consider this cell. Move to next cell */
               if(lcToBeSchedInfo->ueLst.count == 0)
               {
                  lnk = lnk->next;
                  continue;
               }

               /* Compare the total PFS priority of UE with existing UE in
                * to be scheduled List. If any UE has lesser PFS priority
                * then knock out that UE and move that UE to its next
                * favourite cell */ 
               rgSCHPfsGetMinPfsPrioUe(favCell, &lcToBeSchedInfo->ueLst, &nextCellDlUe);
               nextCellPfsUe  = RG_SCH_PFS_GET_PFSUEDL(nextCellDlUe, favCell);

               /* If the selected UE is scheduled for TA or Scell activation
                * CE then do not remove this UE from this cell scheduling */
               if((nextCellPfsUe->taReq) ||  
#ifdef LTE_ADV
                  (nextCellPfsUe->schdSCellActCe)
#endif   
                 )
               {
                  lnk = lnk->next;
                  continue;
               }

               nextCellPfsLc = RG_SCH_PFS_GET_PFSDLLC(nextCellDlUe, 
                               nextCellPfsUe->cmnParam->highestPrioLc);

               /* Comparing the lcType of highest priority LCs. based on the LCtype 
                * (GBR or AMBR) of the highest priority LC of this incoming UE, it is 
                * decided that incoming UE will be added in the next cell or not */
               if((pfsLc->lcType < nextCellPfsLc->lcType) ||
                  ((pfsLc->lcType == nextCellPfsLc->lcType) &&
                   (uePfsPrio > nextCellPfsUe->maxPfsPrio)))
               {
	                 /* nextCellDlLc   = nextCellPfsUe->highestPrioLc; */
                  if(ROK == rgSCHAddUeToNextCell(lcToBeSchedInfo, prevCellUe, uePfsPrio, nextCellDlUe))
                  {
                     rgSCHPfsSchedLcInNextFavCell(favCell, nextCellDlUe, nextCellPfsUe->cmnParam->highestPrioLc);
                     RETVALUE(ROK);
                  }
                  else
                  {
                     /* Move to next favorite Cell for pfsUe, because this
                      * UE can't be added in its current favorite cell */
                     lnk = lnk->next;
                     continue;
                  }
               }
            }
         }
         lnk = lnk->next;
      }
   }
   RETVALUE(ROK);
}
#endif

/**
 * @brief Scheduling of DL new transmissions in a queue
 *
 * @details
 *
 *     Function : rgSCHPfsScheduleUes
 *
 *     This function derives the max number of PRBS that can be allocated
 *     to each LC. Total PRB is calculated using CQI proprotrion.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *alloc
 *  @param[in]  CmLListCp              *txQ
 *  @param[in]  CmLListCp              *retxQ
 *  @param[in]  Bool                   *isBwLeftRef
 *  @param[in]  CmLListCp              *dlLcLst
 *  @param[in]  U32                    *totPfsPrio
 *  @param[in]  U32                    *totPrbReq
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsScheduleUes
(
 RgSchCellCb             *cell,
 RgSchCmnDlRbAllocInfo   *alloc,
 RgSchPfsDlLcSchdInfo    *lcToBeSchedInfo
 )
#else
PRIVATE Void rgSCHPfsScheduleUes(cell, alloc, lcToBeSchedInfo)
   RgSchCellCb             *cell;
   RgSchCmnDlRbAllocInfo   *alloc;
   RgSchPfsDlLcSchdInfo      *lcToBeSchedInfo;
#endif
{
   CmLList            *lnk;
   RgSchDlSf          *sf  = alloc->dedAlloc.dedDlSf;
   U8                 tempMaxRb;
   U32                uePfsPrio;
   U32                prbShare;
   U16                bwAvailable = sf->bw - sf->bwAssigned;
   U8                 toBeSchdUecount = lcToBeSchedInfo->ueLst.count;
   U32                leftOverPrbShare = 0;
   U32                leftOverPrbShareForNxtUe = 0;
   U32                totalRbReq = 0;
   RgSchDlRbAlloc     *allocInfo;       
   U32                bwAvailForUe;     /* Total bandwidth available for all UEs priority based on CSG membership */
   U32                currTotPfsPrio;   /* Total Pfs priority of all UEs based on CSG Membership */
   RgSchEnbPfsDl      *pfsEnbDl = RG_SCH_PFS_GET_PFSDLENB(cell);

   TRC2(rgSCHPfsScheduleUes);

   for (lnk = lcToBeSchedInfo->ueLst.first; lnk; lnk = lnk->next)
   {
      RgSchUeCb     *ue    = (RgSchUeCb *) lnk->node;
      RgSchPfsDlUe  *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, cell);
      RgSchCmnDlUe  *ueDl  = RG_SCH_CMN_GET_DL_UE(ue, cell);
      allocInfo            = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);

      tempMaxRb = ueDl->maxRb;
      /* Do the sharing only if total PRB's req is > bwAvailable */
      if(lcToBeSchedInfo->totPrbReq > bwAvailable)
      {
         /* This takes care of dividing the bandwidth proportionally
          * amongst the remaining UEs */
         uePfsPrio = pfsUe->totalPfsPrio;

         if ((pfsEnbDl->currPrioMmbrSta == TRUE) && (ue->csgMmbrSta == TRUE))
         {
            bwAvailForUe = lcToBeSchedInfo->prioUeBwAvail;
            currTotPfsPrio = lcToBeSchedInfo->prioUeTotPfsPrio;
         }
         else
         {
            bwAvailForUe = lcToBeSchedInfo->nonPrioUeBwAvail;
            currTotPfsPrio = lcToBeSchedInfo->totPfsPrio - lcToBeSchedInfo->prioUeTotPfsPrio;
         }   

         prbShare = ((uePfsPrio * bwAvailForUe) / (currTotPfsPrio)) + 
            leftOverPrbShare + leftOverPrbShareForNxtUe;

         /* This is to handle prbs' left due to integer division 
          * Allocate complete if prbShare to 0 or if it is the last 
          * Lc in the list.*/
         if (toBeSchdUecount == 1)
         {
            prbShare = sf->bw - sf->bwAssigned;
         }
         else
         {
            /* If prbShare is 0, allot atleast 10% of available BW */
            prbShare = RGSCH_MAX(prbShare, RGSCH_CEIL((sf->bw - sf->bwAssigned), 10));
         }

         totalRbReq = prbShare;
         /* Max rb for each UE is limited according to the PFS division for MUE */
         ueDl->maxRb = RGSCH_MIN(ueDl->maxRb, totalRbReq);
      }
      /* Schedule the UEs.*/ 
      if(ROK != rgSCHPfsDlUeSched(cell, alloc, sf, ue))
      {
         /* Release the resources in case of failure */
         rgSCHPfsRlsSchedRes(cell, ue, alloc); 
      }

      ueDl->maxRb = tempMaxRb;

      /* Left over PRBs would be equally distributed amongst the remaining UEs
       * */
      if(toBeSchdUecount > 1)
      {
         leftOverPrbShare         += ((totalRbReq - allocInfo->rbsReq)/
               (toBeSchdUecount - 1));
         leftOverPrbShareForNxtUe = ((totalRbReq - allocInfo->rbsReq)%
               (toBeSchdUecount - 1));
      }

      toBeSchdUecount--;
   }
   RETVOID;
}


/**
 * @brief Adding LC node from the PDB Tracking Queue
 *
 * @details
 *
 *     Function : rgSCHPfsDlLcAddToPdbTrckQ
 *
 *     This function adds the LC entry from the PDB Tracking Queue
 *
 *  @param[in]  RgSchEnbPfsDl          *pfsDl
 *  @param[in]  RgSchDlLcCb            *lc
 *  @param[in]  U32                    qId
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsDlLcAddToPdbTrckQ
(
 RgSchEnbPfsDl        *pfsDl,
 RgSchDlLcCb          *lc,
 U32                  qId
 )
#else
PRIVATE Void rgSCHPfsDlLcAddToPdbTrckQ(pfsDl, pfsLc, lstCp)
   RgSchEnbPfsDl        *pfsDl;
   RgSchDlLcCb          *lc;
   U32                  qId;
#endif
{
   RgSchPfsDlLc *pfsLc = RG_SCH_PFS_GET_PFSDLLC(lc->ue, lc);

   TRC2(rgSCHPfsDlLcAddToPdbTrckQ)
      //printf("rgSCHPfsDlLcAddToPdbTrckQ %p Link %p \n", &(pfsCell->pdbInfo.pdbTrckLst[qId]), &pfsLc->pdbQLnk);

      cmLListAdd2Tail(&(pfsDl->pdbInfo.pdbTrckLst[qId]), &pfsLc->pdbQLnk);
   pfsLc->pdbTrckLstCp = &(pfsDl->pdbInfo.pdbTrckLst[qId]);

   RETVOID;
}

/**
 * @brief Adding LC node from the normal AMBR List
 *
 * @details
 *
 *     Function : rgSCHPfsAddDlLcToAmbrLst
 *
 *     This function adds the LC entry from the AMBR list
 *
 *  @param[in]  RgSchEnbPfsDl         *pfsDl
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchPfsDlLc           *pfsLc
 *  @param[in]  U32                    qId
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHPfsAddDlLcToAmbrLst
(
RgSchEnbPfsDl      *pfsDl,
RgSchUeCb          *ue,
RgSchPfsDlLc       *pfsLc,
U32                qId
)
#else
PRIVATE Void rgSCHPfsAddDlLcToAmbrLst (pfsDl, ue, pfsLc, qId)
RgSchEnbPfsDl      *pfsDl;
RgSchUeCb          *ue;
RgSchPfsDlLc       *pfsLc;
U32                qId;
#endif
{
   RgSchPfsDlUe      *pfsUe = RG_SCH_PFS_GET_PFSUEDL(ue, ue->cell);

   TRC2(rgSCHPfsAddDlLcToAmbrLst)
   /* rgSCHPfsDlLcRmvFrmPrioQ(pfsCell, pfsUe, pfsLc); */
   if (ue->csgMmbrSta == TRUE)
   {
      rgSCHPfsDlLcAddToQ(ue->cell, pfsUe, &pfsDl->txQueues.prioAmbrLst[qId], pfsLc);
   }
   else
   {
      rgSCHPfsDlLcAddToQ(ue->cell, pfsUe, &pfsDl->txQueues.normAmbrLst[qId], pfsLc);
   }
} /* rgSCHPfsAddDlLcToAmbrLst */

#ifdef RG_PFS_STATS
/**
 * @brief Finding number of cells and 
 *        and calling Function to Copy PFS priority of LCs
 *
 * @details
 *
 *     Function : rgSchPfsSimCpyStat
 *
 *     This function adds the LC entry from the AMBR list
 *
 *  @param[in]  TfuTtiIndInfo          *ttiInd
 *  @param[in]  Inst                   schInst
 *  @param[in]  FILE                   *pfsSimFileptr
 *  @return  Void
 **/
PUBLIC Void rgSchPfsSimCpyStat
(
   TfuTtiIndInfo      *ttiInd,
   Inst               schInst,
   FILE               *pfsSimFileptr
)
{
   U8                nCell = 0;
   RgSchCellCb       *cells[CM_LTE_MAX_CELLS];
   U8             i = 0;
   U8             strtCellId;
   TfuTtiCellInfo *cellInfo;
   U32            Idx1; 
   RgSchCellCb    *cell; 

   for (i = 0; i < ttiInd->numCells; i++)
   {
      cellInfo   = &ttiInd->cells[i];
      strtCellId = rgSchCb[schInst].genCfg.startCellId;
      Idx1 = (U8)((cellInfo->cellId - strtCellId)&(CM_LTE_MAX_CELLS-1));
      cell = rgSchCb[schInst].cells[Idx1];
      /* Validate the cell */
      if (cell == NULLP) 
      {
         /* Use SCH inst 0 print buff */
         RGSCHDBGERRNEW(schInst,(rgSchPBuf(schInst),
                  "RgLiTfuTtiInd()No cell exists for cellId %d\n", 
                  cellInfo->cellId));
         continue;
      }
      nCell = nCell + 1;
      cells[i] = (RgSchCellCb *)cell;
   }
   rgSchPfsSimStatsPrc(nCell, cells, pfsSimFileptr);
   RETVOID;
}
/**
 * @brief Copying PFS priority of LCs for each configured UEs to output file
 *
 * @details
 *
 *     Function : rgSchPfsSimStatsPrc
 *
 *     This function adds the LC entry from the AMBR list
 *
 *  @param[in]  U8                     nCell
 *  @param[in]  RgSchCellCb            cellLst
 *  @param[in]  FILE                   *pfsSimFileptr
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSchPfsSimStatsPrc
(
 U8            nCell,
 RgSchCellCb   **cellLst,
 FILE          *pfsSimFileptr
)
#else
PUBLIC Void rgSchPfsSimStatsPrc(nCell, cellLst)
   U8            nCell;
   RgSchCellCb   **cellLst;
   FILE          *pfsSimFileptr;
#endif
{
   RgSchUeCb       *ue;
   RgSchDlLcCb     *dlLc;
   U8               idx;
   RgSchCellCb     *cell;
   RgSchPfsDlCell  *pfsCell;
   RgSchPfsDlLc    *pfsLc;
   RgrSchedEnbCfg   schedEnbCfg = rgSchCb[0].rgrSchedEnbCfg;
   static  Bool     header = TRUE;

   TRC2(rgSchPfsSimStatsPrc)

      for(idx=0; idx<nCell; idx++)
      {
         cell = cellLst[idx];
         if(cell != NULLP)
         {
            if(schedEnbCfg.dlSchdType == 1)
            {   
               ue = rgSCHDbmGetNextUeCb(cell, NULLP);

               while (ue != NULLP)
               {
                  dlLc = rgSCHDbmGetNextDlDedLcCb(ue, NULLP);

                  while(dlLc != NULLP)
                  {
                     if(header)
                     {
                        fprintf(pfsSimFileptr, "%u%c%u",(unsigned int)ue->ueId,':',(unsigned int)dlLc->lcId);
                        dlLc = rgSCHDbmGetNextDlDedLcCb(ue, dlLc);
                     }
                     else
                     {
                        pfsCell = RG_SCH_PFS_GET_PFSCELLDL(cell);
                        pfsLc = RG_SCH_PFS_GET_PFSDLLC(ue, dlLc);
                        fprintf(pfsSimFileptr, "%u",pfsLc->pfsPrio);
                        dlLc = rgSCHDbmGetNextDlDedLcCb(ue, dlLc);
                     }
                     fprintf(pfsSimFileptr, "%c",',');
                  }

                  ue = rgSCHDbmGetNextUeCb(cell, ue);
               }
            }
         }    
      }
   fprintf(pfsSimFileptr, "\n");
   if(header)
   {
      header = FALSE;
   }

   RETVOID;
} 
/**
 * @brief Printing PFS Algo output
 *
 * @details
 *
 *     Function : rgSCHPfsPrint
 *
 *
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHPfsPrint
(
 RgSchCellCb       *cell
)
#else
PUBLIC Void rgSCHPfsPrint (cell)
RgSchCellCb       *cell;
#endif
{
   RgSchUeCb        *ue;
   RgSchDlLcCb      *dlLc;
   RgrSchedEnbCfg   schEnbCfg = rgSchCb[0].rgrSchedEnbCfg;
   U32              qosSatisfyPerc = 0;
   U32              gbr;
   U32              mbr;
   U32              ambr;
   U8               avgCqi = 0;
   U8               idx = 0;
   U8               numUe = 0;
   U8               numCaUe = 0;
   U8               numNonCaUe = 0;
   Bool             sCellStats = FALSE;
   U8               str1[10000];
   U8               str2[10000];
   U8               str3[100000];
   U16              strLen = 0;
   U32              prbUsePerc;
   U32              schdOccCnt = 0;
   U32              count, idx1;
   U8               isCaUe;

   TRC2(rgSCHPfsPrint)

   if(schEnbCfg.dlSchdType == 1)
   {   
      ue = rgSCHDbmGetNextUeCb(cell, NULLP);

      if(ue != NULLP)
      {   
         sprintf(str1,"\n<-----------------CELL stats:: CELLID %d:: TEST PERIOD %lu ms----------------------->\n", 
               cell->cellId, cell->totalTime);
         strLen = strlen(str1);
         sprintf(str1+strLen,"--------------------------------------------------------------------------------------------------------------------------------------------\n");
         strLen = strlen(str1);
         sprintf(str1+strLen,"|  UE  | isCaUe | LCID | QCI |\t\tGBR\t\t|\t\tMBR\t\t|\t\tAMBR\t| SvcSchdOcc | GBR % | GbrBytesSchd | MbrBytesSchd | AchvdFracDataRate |\n");
         strLen = strlen(str1);
         sprintf(str1+strLen,"--------------------------------------------------------------------------------------------------------------------------------------------\n");

         sprintf(str3,"\nUE PER LC PER REFRESH CYCLE STATS::\n");
         strLen = strlen(str3);
         sprintf(str3+strLen,"------------------------------------------------------------------------------------------------------------------------------------\n");
         strLen = strlen(str3);
         sprintf(str3+strLen,"| Refresh Cycle |\tUEID\t|\tLCID\t| RefreshCycleGbr | RefreshCycleMbr | lcSchdOcc |\t\tremGbr | remDeltaMbr | totByteSchd |\n");
         strLen = strlen(str3);
         sprintf(str3+strLen,"------------------------------------------------------------------------------------------------------------------------------------\n");
      }
      else
      {
         RETVALUE(ROK);
      }   

      while (ue != NULLP)
      {
         numUe++;

         strLen = strlen(str1);

         //sprintf(str1+strLen,"\t%3d", ue->ueId);   

         dlLc = rgSCHDbmGetNextDlDedLcCb(ue, NULLP);

         while(dlLc != NULLP)
         {
            if(ue->pfsStats.lcStats[dlLc->lcId-1].gbrRefreshCycleCnt)
            {
               qosSatisfyPerc = (ue->pfsStats.lcStats[dlLc->lcId-1].gbrSatisfiedCnt * 100)/
                  (ue->pfsStats.lcStats[dlLc->lcId-1].gbrRefreshCycleCnt); /* Ignore 1st refresh cycle coz we dnt know when UE has been added 
                                                                              and it had enough chance to be satisfied during 1st refresh cycle */
            }

            if(RG_SCH_CMN_SVC_IS_GBR(dlLc))
            {   
               gbr = (((RgSchCmnDlSvc *)(dlLc->sch))->gbr * 100)/RG_SCH_CMN_REFRESH_TIME;
               mbr = (((RgSchCmnDlSvc *)(dlLc->sch))->mbr * 100)/RG_SCH_CMN_REFRESH_TIME;
               ambr = 0;
            }
            else
            {   
               ambr = (ue->dl.ambrCfgd * 100)/RG_SCH_CMN_REFRESH_TIME;
               gbr = 0;
               mbr = 0;
            }
            for (idx = 0; idx < CM_LTE_MAX_CELLS; idx++)
            {
               schdOccCnt += ue->pfsStats.lcStats[dlLc->lcId-1].ueSchdOcc[idx];
            }

            if(ue->pfsStats.isCaUe)
            {
               isCaUe = 'T';
            }   
            else
            {
               isCaUe = 'F'; 
            }   
            strLen = strlen(str1);

            sprintf(str1+strLen,"| %4d |  %2c\t | %2d   | %2d  | %10lu\t| %10lu\t| %10lu\t| \t%4lu\t |  %3lu  | %10lu   | %10lu   | %10lu        |\n", 
                  ue->ueId, isCaUe, dlLc->lcId, dlLc->qciCb->qci, gbr, mbr, ambr, schdOccCnt, qosSatisfyPerc, \
                  ue->pfsStats.lcStats[dlLc->lcId-1].totGbrBytesSchd, ue->pfsStats.lcStats[dlLc->lcId-1].totMbrBytesSchd,\
                  ue->pfsStats.lcStats[dlLc->lcId-1].achvdFracDataRate);

            count = 0;
            idx1 = ue->pfsStats.lcStats[dlLc->lcId-1].startIdx;
            do
            {
               idx1 = idx1 % RGSCH_NUM_STATS_PER_REFRESH;
               strLen = strlen(str3);
               sprintf(str3+strLen,"| \t\t%u\t\t|\t%u\t\t|\t%u\t\t| %10lu\t  | %10lu\t\t| %3lu\t\t|\t%10lu | %10lu  | %10lu  |\n",
                     idx1, ue->ueId, dlLc->lcId, \
                     ((RgSchCmnDlSvc *)(dlLc->sch))->gbr, \
                     ((RgSchCmnDlSvc *)(dlLc->sch))->mbr, \
                     ue->pfsStats.lcStats[dlLc->lcId-1].perRefresh[idx1].lcSchdOcc, \
                     ue->pfsStats.lcStats[dlLc->lcId-1].perRefresh[idx1].remGbr, \
                     ue->pfsStats.lcStats[dlLc->lcId-1].perRefresh[idx1].remDeltaMbr,
                     ue->pfsStats.lcStats[dlLc->lcId-1].perRefresh[idx1].totByteSchd);
               idx1++;
               count++;
            } while(idx1 != (ue->pfsStats.lcStats[dlLc->lcId-1].lastIdx+1));
            strLen = strlen(str3);
            sprintf(str3+strLen,"------------------------------------------------------------------------------------------------------------------------------------\n");

            ue->pfsStats.lcStats[dlLc->lcId-1].gbrSatisfiedCnt = 0;
            schdOccCnt = 0;
            qosSatisfyPerc = 0;
            ue->pfsStats.lcStats[dlLc->lcId-1].gbrRefreshCycleCnt = 0;

            dlLc = rgSCHDbmGetNextDlDedLcCb(ue, dlLc);
         }

         ue->pfsStats.refreshCycleCnt = 0;

         if(!sCellStats)
         {
            sprintf(str2,"\nUE PER LC PER SCELL STATS::\n");
            strLen = strlen(str2);
            sprintf(str2+strLen,"-----------------------------------------------------------------------------------\n");
            strLen = strlen(str2);
            sprintf(str2+strLen,"|\tUEID\t|\tLCID\t|  sCellIdx |\tsCellId  |\tAVG_CQI\t|\tueSchdOcc |\tfavCellCnt |\n");
            strLen = strlen(str2);
            sprintf(str2+strLen,"-----------------------------------------------------------------------------------\n");
            sCellStats = TRUE;
         }   

         strLen = strlen(str2);
         //sprintf(str2+strLen,"%d", ue->ueId);   
         for(idx = 0; idx < CM_LTE_MAX_CELLS; idx++)
         {
            if(ue->cellInfo[idx])
            {
               if(ue->pfsStats.cqiStats[idx].totalCqiOcc)
               {   
                  avgCqi = ue->pfsStats.cqiStats[idx].avgCqi/
                     ue->pfsStats.cqiStats[idx].totalCqiOcc;
               }
               dlLc = rgSCHDbmGetNextDlDedLcCb(ue, NULLP);
               while(dlLc != NULLP)
               {
                  strLen = strlen(str2);
                  sprintf(str2+strLen,"|\t%u\t\t|\t%u\t\t|\t%3d\t\t|\t%d\t\t\t|\t%2d\t\t\t|\t\t%5d  |\t\t%5d  |\n",
                        ue->ueId, dlLc->lcId, ue->cellInfo[idx]->sCellIdx, ue->cellInfo[idx]->sCellId, avgCqi, \
                        ue->pfsStats.lcStats[dlLc->lcId-1].ueSchdOcc[idx], \
                        ue->pfsStats.lcStats[dlLc->lcId-1].favCellCnt[idx]); 

                  ue->pfsStats.lcStats[dlLc->lcId-1].ueSchdOcc[idx] = 0;
                  dlLc = rgSCHDbmGetNextDlDedLcCb(ue, dlLc);
               }   
            }
            avgCqi = 0;
            ue->pfsStats.cqiStats[idx].avgCqi = 0;
            ue->pfsStats.cqiStats[idx].totalCqiOcc = 0;
         }
         strLen = strlen(str2);
         sprintf(str2+strLen,"-------------------------------------------------------------------------------------\n");

         if(ue->pfsStats.isCaUe)
         {
            numCaUe++;
         }   
         else
         {
            numNonCaUe++;
         }   

         strLen = strlen(str1);
         sprintf(str1+strLen,"--------------------------------------------------------------------------------------------------------------------------------------------\n");

         ue = rgSCHDbmGetNextUeCb(cell, ue);
      }    

      printf("%s",str1);
      printf("%s",str2);
      printf("%s",str3);
      prbUsePerc = (cell->totalPrb * 100)/(cell->totalTime * cell->bwCfg.dlTotalBw);
      printf("\nCELL STATS: numActUes = %d, numCaUe = %d, numNonCaUe = %d, prbUsePerc = %lu\n\n", numUe, numCaUe, numNonCaUe, prbUsePerc);

      cell->totalTime = 0;
      cell->totalPrb = 0;
   }

} 
#endif

/**********************************************************************
 
         End of file:     gk_sch_pfs.c@@/main/2 - Sat Jul 30 02:21:46 2011
 
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
/main/1      ---     apany   1. LTE MAC 2.1 release
           rg003.201 ns      1. Trace added to functions.
           rg004.201 ms      1. DL DTX Handling
           rg006.201 sd      1. ccpu00112398: Added periodic BSR timer
           rg007.201   ap  1. Added support for MIMO
           rg008.201   sd  1. Removed dependncy on MIMO compile-time flag
           rg009.201   dv  1. Added changes of TFU_UPGRADE. 
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
           rg001.301  nudupi 1. ccpu00118350:Correcting NDI manipulation of Harq.
$SID$        ---        rt  1. LTE MAC 4.1 release
*********************************************************************91*/
