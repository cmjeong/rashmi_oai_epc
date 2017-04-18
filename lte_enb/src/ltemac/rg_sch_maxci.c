



/************************************************************************
 
     Name:     LTE-MAC layer
 
     Type:     C source file
 
     Desc:     C source code for MAX C/I functions
 
     File:     rg_sch_maxci.c
 
     Sid:      gk_sch_maxci.c@@/main/2 - Sat Jul 30 02:21:44 2011
 
     Prg:     apany
 
**********************************************************************/

/** @file rg_sch_maxci.c
@brief This module handles the MAX C/I scheduler functionality
*/

static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_MODULE_ID=4096;
static int RLOG_FILE_ID=168;

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
#include "rg_sch_maxci.h"
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
#include "rg_sch_maxci.x"        /* typedefs for DLFS Scheduler */


/* local defines */

/* MAX C/I DL allocation functions */
PRIVATE Void rgSCHMaxciDlTaSchd ARGS((
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
));
PRIVATE Void rgSCHMaxciDlTaSchdForUe ARGS((
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc,
RgSchDlSf               *dlSf,
RgSchUeCb               *ue
));
PRIVATE Void rgSCHMaxciDlRetx ARGS((
RgSchCellCb           *cell,
RgSchCmnDlRbAllocInfo *allocInfo
));
PRIVATE Void rgSCHMaxciDlRetxUeSchd ARGS((
RgSchCellCb             *cell,
RgSchUeCb               *ue,
RgSchCmnDlRbAllocInfo   *alloc,
CmLListCp               *retxProcs
));
PRIVATE Void rgSCHMaxciDlNewTx ARGS(( 
RgSchCellCb                *cell,
RgSchCmnDlRbAllocInfo      *alloc
));
PRIVATE Void rgSCHMaxciDlPreSchedNewTx ARGS((
RgSchCellCb *cell
));
PRIVATE Void rgSCHMaxciDlPstSchedNewTx ARGS((
 Inst       schInst
));
PRIVATE S16 rgSCHMaxciDlLcSchd ARGS((
RgSchCellCb           *cell,
RgSchCmnDlRbAllocInfo *alloc,
RgSchDlSf             *dlSf,
RgSchUeCb             *ue,
RgSchDlLcCb           *dlLc,
Bool                  isSrb,
U32                   *allocBytes
));

/* MAX C/I  handlers for post DL allocation */
PRIVATE Void rgSCHMaxciDlOnNewTxAlloc ARGS((
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
));
PRIVATE Void rgSCHMaxciDlOnNewTxAllocForUe ARGS((
RgSchCellCb             *cell,
RgSchUeCb               *ue,
RgSchCmnDlRbAllocInfo   *alloc
));
PRIVATE Void rgSCHMaxciDlAddLcAllocToProc ARGS((
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc,
U32                    allocBytes,
RgSchDlHqTbCb          *tbInfo
));
PRIVATE Void rgSCHMaxciDlLcPartlyAllocd ARGS((
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc,
U32                bytes,
RgSchDlHqTbCb      *tbInfo
));
PRIVATE Void rgSCHMaxciDlLcFullyAllocd ARGS((
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc,
RgSchDlHqTbCb      *tbInfo
));
PRIVATE Void rgSCHMaxciDlNewTxTbDstn ARGS((
RgSchCellCb    *cell,
RgSchUeCb      *ue,
RgSchDlHqTbCb  *tbInfo,
U32            *effAlloc,
CmLList        **node
));
PRIVATE Void rgSCHMaxciDlSprTxTbDstn ARGS((
RgSchCellCb    *cell,
RgSchUeCb      *ue,
RgSchDlHqTbCb  *tbInfo,
U32            *effAlloc,
CmLList        **node
));
PRIVATE Void rgSCHMaxciDlBoUpdOnAlloc ARGS((
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc,
U32                    remBo,
U32                    allocBo
));
PRIVATE Void rgSCHMaxciDlSrbBoUpd ARGS((
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc,
U32                    bo
));
PRIVATE Void rgSCHMaxciDlDrbBoUpd ARGS((
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc,
U32                    bo
));
PRIVATE Void rgSCHMaxciDlOnRetxAlloc ARGS((
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
));
PRIVATE Void rgSCHMaxciDlRmvRetxProcFrmUe ARGS((
RgSchCellCb           *cell,
RgSchUeCb             *ue,
RgSchDlHqProcCb       *proc
));

/* MAX C/I Utitlity functions */
PRIVATE Void rgSCHMaxciDlRlsHqP ARGS((
RgSchDlHqProcCb      *hqProc
));
PRIVATE Void rgSCHMaxciDlReposUeInTxQ ARGS((
RgSchCellCb           *cell,
RgSchUeCb             *ue
));
PRIVATE Void rgSCHMaxciDlReposUeInRetxQ ARGS((
RgSchCellCb           *cell,
RgSchUeCb             *ue
));
PRIVATE Void rgSCHMaxciDlRstUeTmpVars ARGS((
RgSchCellCb             *cell,
RgSchUeCb               *ue,
RgSchDlHqProcCb         *hqP
));
PRIVATE RgSchDlHqProcCb *rgSCHMaxciDlGetAvlProc ARGS((
RgSchCellCb            *cell,
RgSchUeCb              *ue,
Bool                   isSrb
));
PRIVATE Void rgSCHMaxciDlAddUeToRetxUeLst ARGS((
RgSchMaxciDlCell *maxciDlCell,
RgSchMaxciDlUe   *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlAddUeToRetxSrbLst ARGS((
RgSchMaxciDlCell *maxciDlCell,
RgSchMaxciDlUe   *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlAddUeToTxUeLst ARGS((
RgSchMaxciDlCell *maxciDlCell,
RgSchMaxciDlUe   *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlAddUeToTxSrbLst ARGS((
RgSchMaxciDlCell *maxciDlCell,
RgSchMaxciDlUe   *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlDelUeFrmTxSrbLst ARGS((
RgSchMaxciDlUe *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlDelUeFrmTxUeLst ARGS((
RgSchMaxciDlUe *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlDelUeFrmRetxLst ARGS((
RgSchMaxciDlUe *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlAddLcToUe ARGS((
RgSchMaxciDlLc *maxciDlLc,
CmLListCp      *lcLst
));
PRIVATE Void rgSCHMaxciDlDelLcFrmUe ARGS((
RgSchMaxciDlLc *maxciDlLc
));
PRIVATE Void rgSCHMaxciDlAddSrbHqProcToUe ARGS((
RgSchMaxciDlHqProc *maxciDlHqProc, 
RgSchMaxciDlUe     *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlAddDrbHqProcToUe ARGS((
RgSchMaxciDlHqProc *maxciDlHqProc, 
RgSchMaxciDlUe     *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlDelDrbHqProcFrmUe ARGS((
RgSchMaxciDlHqProc *maxciDlHqProc, 
RgSchMaxciDlUe     *maxciDlUe
));
PRIVATE Void rgSCHMaxciDlDelSrbHqProcFrmUe ARGS((
RgSchMaxciDlHqProc *maxciDlHqProc, 
RgSchMaxciDlUe     *maxciDlUe
));

/* Uplink private declarations */
PRIVATE Void rgSCHMaxciUlUtlSchdForContRes ARGS((
         RgSchCellCb               *cell,
         RgSchCmnUlRbAllocInfo     *alloc,
         U8                        *remUe));

PRIVATE Void rgSCHMaxciUlUtlSchdForSrb ARGS((
         RgSchCellCb            *cell,
         RgSchCmnUlRbAllocInfo  *alloc,
         U8                     *remUe));

PRIVATE Void rgSCHMaxciUlUtlSchdForTx ARGS((
         RgSchCellCb            *cell,
         RgSchCmnUlRbAllocInfo  *alloc,
         U8                     *remUe));

PRIVATE Void rgSCHMaxciUlUtlPosUe ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchCmnUlUe     *cmnUe,
         RgSchMaxciUlUe   *maxciUe,
         RgSchCmnLcg      *lcg0));

PRIVATE Void rgSCHMaxciUlUtlFnlzContRes ARGS((
         RgSchCellCb               *cell,
         RgSchCmnUlRbAllocInfo     *alloc));

PRIVATE Void rgSCHMaxciUlUtlFnlzTx ARGS((
         RgSchCellCb               *cell,
         RgSchCmnUlRbAllocInfo     *alloc));

PUBLIC S16 rgSCHMaxciDlUeHqEntInit ARGS((
         RgSchCellCb      *cell,
         RgSchDlHqEnt     *hqEnt
         ));
PUBLIC S16 rgSCHMaxciDlUeHqEntDeInit ARGS((
         RgSchCellCb      *cell,
          RgSchDlHqEnt     *hqE
         ));
PUBLIC Void rgSCHMaxciDlRmvRetxProcFrmList ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgSchDlHqProcCb     *proc
         ));

PUBLIC Void rgSCHMaxciDlScanUpdPdbPrio  ARGS((
         RgSchCellCb *cell
         ));
PUBLIC S16 rgSCHMaxciDlFillFlowCntrlInfo ARGS(( 
         RgSchCellCb    *cell,
         RgInfSfAlloc   *sfAlloc
         ));
/**
 * @brief This function initializes all the data for the DL MAX C/I scheduler
 *
 * @details
 *
 *     Function: rgSCHMaxciDlInit
 *
 *     Invoked by: MAC intialization code.
 *     
 *  @return  Void
 *
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlInit
(
RgDlSchdApis         *apis
)
#else
PUBLIC Void rgSCHMaxciDlInit(apis)
RgDlSchdApis         *apis;
#endif
{
   TRC2(rgSCHMaxciDlInit);

   /* Init the function pointers */
   apis->rgSCHRgrDlCellCfg   = rgSCHMaxciDlCellCfg;
   apis->rgSCHRgrDlCellRecfg = rgSCHMaxciDlCellRecfg; 
   apis->rgSCHFreeDlCell     = rgSCHMaxciDlCellDel;
   apis->rgSCHRgrDlUeCfg     = rgSCHMaxciDlUeCfg;
   apis->rgSCHRgrDlUeRecfg   = rgSCHMaxciDlUeRecfg;
   apis->rgSCHFreeDlUe       = rgSCHMaxciDlUeDel;
   apis->rgSCHRgrDlLcCfg     = rgSCHMaxciDlLcCfg;
   apis->rgSCHRgrDlLcRecfg   = rgSCHMaxciDlLcRecfg;
   apis->rgSCHFreeDlLc       = rgSCHMaxciDlLcDel;
   apis->rgSCHDlNewSched     = rgSCHMaxciDlNewTx;
   apis->rgSCHDlPreSched     = rgSCHMaxciDlPreSchedNewTx;
   apis->rgSCHDlPstSched     = rgSCHMaxciDlPstSchedNewTx;
   apis->rgSCHDlRetxSched    = rgSCHMaxciDlRetx;
   apis->rgSCHDlCeSched      = rgSCHMaxciDlTaSchd;
   apis->rgSCHDlDedBoUpd     = rgSCHMaxciDlDedBoUpd;
   apis->rgSCHDlProcAddToRetx= rgSCHMaxciDlProcAddToRetx;
   apis->rgSCHDlAllocFnlz    = rgSCHMaxciDlAllocFnlz;
   apis->rgSCHDlCqiInd       = rgSCHMaxciDlCqiInd;
   apis->rgSCHDlUeRefresh    = rgSCHMaxciDlUeRefresh;
   apis->rgSCHDlUeReset      = rgSCHMaxciDlUeReset;
   apis->rgSCHDlActvtUe      = rgSCHMaxciDlActvtUe;
   apis->rgSCHDlInactvtUes   = rgSCHMaxciDlHndlInActvUes;
   apis->rgSCHDlUeHqEntInit  = rgSCHMaxciDlUeHqEntInit;
   apis->rgSCHDlUeHqEntDeInit= rgSCHMaxciDlUeHqEntDeInit;
   apis->rgSCHDlProcRmvFrmRetx = rgSCHMaxciDlRmvRetxProcFrmList;
   apis->rgSCHDlTickForPdbTrkng = rgSCHMaxciDlScanUpdPdbPrio;
   apis->rgSCHDlFillFlwCtrlInfo = rgSCHMaxciDlFillFlowCntrlInfo; 

   RETVOID;
}

/**
 * @brief Cell configuration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlCellCfg
 *
 *     Processing Steps:
 *      - Create the maxciDlCell info for DL within passed SchCell
 *      - Update configured values
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[in]  RgrCellCfg          *cellCfg
 *  @param[in]  RgSchErrInfo        *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciDlCellCfg
(
RgSchCellCb          *cell,
RgrCellCfg           *cellCfg,
RgSchErrInfo         *err
)
#else
PUBLIC S16 rgSCHMaxciDlCellCfg(cell, cellCfg, err)
RgSchCellCb          *cell;
RgrCellCfg           *cellCfg;
RgSchErrInfo         *err;
#endif
{
   S16               ret;
   U8 iTbs;
   U32 minEff;
   U32 maxEff;
   U32 priorEff;
   RgSchMaxciDlCell  *maxciDlCell;
   RgSchCmnDlCell    *cmnDlCell = RG_SCH_CMN_GET_DL_CELL(cell);
   RgrSchedEnbCfg    *schCfg = &(RG_SCH_CMN_GET_SCHED_CFG(cell));
   U8                cfi = cmnDlCell->currCfi;
   TRC2(rgSCHMaxciDlCellCfg);

   UNUSED(cellCfg);

   if((ret = rgSCHUtlAllocSBuf(cell->instIdx, 
               (Data**)&cmnDlCell->schSpfc, (sizeof(RgSchMaxciDlCell)))) != ROK)
   {
      RLOG_ARG1(L_ERROR,DBG_CELLID,cellCfg->cellId,  
               "Memory allocation FAILED for MAX C/I DL cell %d",
               cell->cellId);
      err->errCause = RGSCHERR_MAXCI_MEMERR;
      RETVALUE(ret);
   }
   /* Calculation for max eff and min eff and also Calculation 
    * for priority level efficiency
    * MinEff is efficiency for min value of CQI and MaxEff is effenciency
    * for max value of CQI.
    Number priority queue levels made as 16 here (o to 15) */
   if(schCfg->numTxAntPorts == 1)
   {
      iTbs     = (*(RgSchCmnCqiToTbs *)(cmnDlCell->cqiToTbsTbl[0][cfi]))[RG_SCH_MAXCI_MIN_CQI_VAL];
      minEff   = (*(RgSchCmnTbSzEff *)(cmnDlCell->cqiToEffTbl[0][cfi]))[iTbs];
      iTbs     = (*(RgSchCmnCqiToTbs *)(cmnDlCell->cqiToTbsTbl[0][cfi]))[RG_SCH_MAXCI_MAX_CQI_VAL];
      maxEff   = (*(RgSchCmnTbSzEff *)(cmnDlCell->cqiToEffTbl[0][cfi]))[iTbs];
      priorEff = ((maxEff - minEff)/(RG_SCH_MAXCIDL_NUM_CQI_LVLS-1));
   }
   else if(schCfg->numTxAntPorts == 2)
   {
      iTbs     = (*(RgSchCmnCqiToTbs *)(cmnDlCell->cqiToTbsTbl[0][cfi]))[RG_SCH_MAXCI_MIN_CQI_VAL];
      minEff   = (*(RgSchCmnTbSzEff *)(cmnDlCell->cqiToEffTbl[0][cfi]))[iTbs];
      iTbs     = (*(RgSchCmnCqiToTbs *)(cmnDlCell->cqiToTbsTbl[0][cfi]))[RG_SCH_MAXCI_MAX_CQI_VAL];
      maxEff   = (*(RgSchCmnTbSzEff *)(cmnDlCell->cqiToEffTbl[0][cfi]))[iTbs];
      maxEff *= RG_SCH_MAXCI_MAX_CWS_PERUE; /* multiplied by 2 becoz of two TBs */
      priorEff = ((maxEff - minEff)/(RG_SCH_MAXCIDL_NUM_CQI_LVLS-1));
   }
   else /* schCfg->numTxAntPorts == 4 */
   {
      iTbs     = (*(RgSchCmnCqiToTbs *)(cmnDlCell->cqiToTbsTbl[0][cfi]))[RG_SCH_MAXCI_MIN_CQI_VAL];
      minEff   = (*(RgSchCmnTbSzEff *)(cmnDlCell->cqiToEffTbl[0][cfi]))[iTbs];
      iTbs     = (*(RgSchCmnCqiToTbs *)(cmnDlCell->cqiToTbsTbl[1][cfi]))[RG_SCH_MAXCI_MAX_CQI_VAL];
      maxEff   = (*(RgSchCmnTbSzEff *)(cmnDlCell->cqiToEffTbl[1][cfi]))[iTbs];
      maxEff *= RG_SCH_MAXCI_MAX_CWS_PERUE; /* multiplied by 2 becoz of two TBs */
      priorEff = ((maxEff - minEff)/(RG_SCH_MAXCIDL_NUM_CQI_LVLS-1));
   }      

   maxciDlCell = (RgSchMaxciDlCell*)(cmnDlCell->schSpfc);
   maxciDlCell->priorEff = priorEff;
   /* Note: Assuming cellDl is memset to 0 during allocation,
    * no initializations are needed */

   RETVALUE(ROK);
}

/**
 * @brief Cell reconfiguration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlCellRecfg
 *
 *     Processing Steps:
 *     - No preocessing specific to MAX C/I needed
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @param[in]  RgrCellRecfg      *cellRecfg
 *  @param[in]  RgSchErrInfo      *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciDlCellRecfg
(
RgSchCellCb     *cell,
RgrCellRecfg    *cellRecfg,
RgSchErrInfo    *err
)
#else
PUBLIC S16 rgSCHMaxciDlCellRecfg(cell, cellRecfg, err)
RgSchCellCb     *cell;
RgrCellRecfg    *cellRecfg;
RgSchErrInfo    *err;
#endif
{
   TRC2(rgSCHMaxciDlCellRecfg);
   UNUSED(cell);
   UNUSED(cellRecfg);
   UNUSED(err);

   RETVALUE(ROK);
}


/**
 * @brief Cell deletion for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlCellDel
 *
 *     Processing Steps:
 *      - Free Max C/I related information per cell.
 *      - [ Nothing else needs to be done.
 *        Common modules would take care of deleting
 *        each UE in the cell, during which time Max C/I
 *        shall be called for UE deletion.]
 *      - Assumption: The trasmitting and re-transmitting queues per cell
 *        have no entries after deletion of all UEs of the cell.
 *      - Assumption: The API is invoked after deletion of UEs from the cell.
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlCellDel
(
RgSchCellCb          *cell
)
#else
PUBLIC Void rgSCHMaxciDlCellDel(cell)
RgSchCellCb          *cell;
#endif
{
   RgSchCmnDlCell    *cmnDlCell = RG_SCH_CMN_GET_DL_CELL(cell);
   RgSchMaxciDlCell  *maxciDlCell = RG_SCH_MAXCIDL_GET_CELL(cell);
   TRC2(rgSCHMaxciDlCellDel);

   if (maxciDlCell)
   {
       /* ccpu00117052 - MOD - Passing double pointer
       for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(cell->instIdx, (Data**)(&(cmnDlCell->schSpfc)),
            sizeof(RgSchMaxciDlCell));
   }
   cmnDlCell->schSpfc = NULLP;
   RETVOID;
}

/**
 * @brief UE configuration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlUeCfg
 *
 *     Processing Steps:
 *      - Create the maxciUe info
 *      - Validate and update configured values
 *      - [UE specific refresh timer actions to happen
 *        as part of common modules]
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgrUeCfg         *ueCfg
 *  @param[in]  RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciDlUeCfg
(
RgSchCellCb           *cell,
RgSchUeCb             *ue,
RgrUeCfg              *ueCfg,
RgSchErrInfo          *err
)
#else
PUBLIC S16 rgSCHMaxciDlUeCfg(cell, ue, ueCfg, err)
RgSchCellCb           *cell;
RgSchUeCb             *ue;
RgrUeCfg              *ueCfg;
RgSchErrInfo          *err;
#endif
{
   S16                ret;
   RgSchCmnDlUe       *cmnDlUe    = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchMaxciDlUe     *maxciDlUe;
   TRC2(rgSCHMaxciDlUeCfg);


   if((ret = rgSCHUtlAllocSBuf(cell->instIdx, (Data**)&(cmnDlUe->schSpfc),
               (sizeof(RgSchMaxciDlUe)))) != ROK)
   {
      RLOG_ARG1(L_ERROR,DBG_CELLID,cell->cellId, 
               "Memory allocation FAILED for MAX C/I DL CRNTI:%d",
               ue->ueId);
      err->errCause = RGSCHERR_MAXCI_MEMERR;
      RETVALUE(ret);
   }
   maxciDlUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);

   /* Initializations for the UE */
   maxciDlUe->wbCqi = cmnDlUe->mimoInfo.cwInfo[0].cqi;
   if (ueCfg->ueQosCfg.ambrPres)
   {
      maxciDlUe->remAmbr = ue->dl.ambrCfgd;
   }
   maxciDlUe->ambrPres = ueCfg->ueQosCfg.ambrPres;

   /* Initialize link pointers */
   RG_SCH_MAXCIDL_INIT_LNK(&(maxciDlUe->retxLnk), ue);
   RG_SCH_MAXCIDL_INIT_LNK(&(maxciDlUe->prioLnk), ue);
   RG_SCH_MAXCIDL_INIT_LNK(&(maxciDlUe->srbLnk), ue);

   /* Note: Initializations of the lists is not done,
    * assuming maxciDlUe is memset to 0 */

   RETVALUE(ROK);
}


/**
 * @brief Dl Harq Entity initialization for Max-Ci
 *
 * @details
 *
 *     Function : rgSCHMaxciDlUeHqEntInit
 *
 *     Processing Steps:
 *      - Create Maxci related information per Harq Entity
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciDlUeHqEntInit
(
 RgSchCellCb      *cell,
 RgSchDlHqEnt     *hqEnt
 )
#else
PUBLIC S16 rgSCHMaxciDlUeHqEntInit(cell, hqEnt)
   RgSchCellCb      *cell;
   RgSchDlHqEnt     *hqEnt;
#endif
{
   S16                hqProcIdx   = 0;
   RgSchUeCb          *ue         = hqEnt->ue;
   RgSchCmnDlUe       *cmnDlUe    = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchDlHqProcCb    *proc       = NULLP;
   RgSchCmnDlHqProc   *cmnDlProc  = NULLP;

   RgSchMaxciDlHqProc *maxciDlHqProc;

   TRC2(rgSCHMaxciDlUeHqEntInit);
   if (ROK != rgSCHUtlAllocSBuf(cell->instIdx,
               (Data**)&hqEnt->sch, 
               (hqEnt->numHqPrcs * sizeof(RgSchMaxciDlHqProc))))
   {
       /* ccpu00117052 - MOD - Passing double pointer
       for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(cell->instIdx,
            (Data**)(&(cmnDlUe->schSpfc)), (sizeof(RgSchMaxciDlUe)));
      RETVALUE(RFAILED);
   }

   /* Alloc and init sched specific info in each proc */
   for (hqProcIdx = 0; hqProcIdx < hqEnt->numHqPrcs; ++hqProcIdx)
   {
      proc = &hqEnt->procs[hqProcIdx];
      cmnDlProc = (RgSchCmnDlHqProc *)proc->sch;
      cmnDlProc->schSpfc = &((RgSchMaxciDlHqProc *)hqEnt->sch)[hqProcIdx];
      maxciDlHqProc = (RgSchMaxciDlHqProc *)cmnDlProc->schSpfc;
      RG_SCH_MAXCIDL_INIT_LNK(&(maxciDlHqProc->ueLnk), proc);
   }
   RETVALUE(ROK);
}
/**
 * @brief Dl Harq Entity deletion for MaxCi
 *
 * @details
 *
 *     Function : rgSCHMaxciDlUeHqEntDeInit 
 *
 *     Processing Steps:
 *      - Free Maxci related information per Harq Entity
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchDlHqEnt     *hqE 
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciDlUeHqEntDeInit 
(
RgSchCellCb      *cell,
RgSchDlHqEnt     *hqE
)
#else
PUBLIC S16 rgSCHMaxciDlUeHqEntDeInit(cell, hqE)
RgSchCellCb      *cell;
RgSchDlHqEnt     *hqE;
#endif
{
   TRC2(rgSCHMaxciDlUeHqEntDeInit);

   if(hqE->sch)
   {
      rgSCHUtlFreeSBuf(cell->instIdx,
      (Data**)(&(hqE->sch)),
      (hqE->numHqPrcs * sizeof(RgSchMaxciDlHqProc)));
   }
   RETVALUE(ROK);
}

/**
 * @brief UE reconfiguration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlUeRecfg
 *
 *     Processing Steps:
 *      - Update the reconfigured values.
 *      - [Not constraining buffer status for DL and UL
 *        due to changed AMBR info now;
 *        allowing current refresh cycle to misbehave]
 *
 *  @param[in]   RgSchCellCb      *cell
 *  @param[in]   RgSchUeCb        *ue
 *  @param[in]   RgrUeRecfg       *ueRecfg
 *  @param[in]   RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciDlUeRecfg
(
RgSchCellCb       *cell,
RgSchUeCb         *ue,
RgrUeRecfg        *ueRecfg,
RgSchErrInfo      *err
)
#else
PUBLIC S16 rgSCHMaxciDlUeRecfg(cell, ue, ueRecfg, err)
RgSchCellCb       *cell;
RgSchUeCb         *ue;
RgrUeRecfg        *ueRecfg;
RgSchErrInfo      *err;
#endif
{
   RgSchCmnDlUe   *ueCmnDl  = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchMaxciDlUe *maxciDlUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchDlHqEnt          *hqEnt = RG_SCH_CMN_GET_UE_HQE(ue, cell);

   UNUSED(err);
   TRC2(rgSCHMaxciDlUeRecfg);


   maxciDlUe->ambrPres = ueRecfg->ueQosRecfg.ambrPres;

   /* Note: not updating new ambr value over here. It will be taken care as part
    * of refresh cycle */
   /* Discarding TB2's context from scheduling Queues.
    * Since TB2 transmission needs signalling using 
    * TM specific formats. And since during this transient
    * period of UE TM Recfg, SCH always uses Format 1A,
    * the TB2s are discarded. */
   if (ueCmnDl->mimoInfo.forceTD & RG_SCH_CMN_TD_TXMODE_RECFG)
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
               rgSCHMaxciDlRmvRetxProcFrmUe(cell, ue, hqP);
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

/**
 * @brief UE delete for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlUeDel
 *
 *     Processing Steps:
 *       - Remove UE from retx queue if present
 *       - Remove UE from new tx queues (SRB and/or CQI UE queues)
 *       - Free Max C/I specific harq information.
 *       - Dedicated logical channels shall not be deleted here since the common
 *         module shall invoke dedicated LC delete before invoking this API
 *       - Free Max C/I UE info
 *
 *  @param[in]  RgSchCellCb       *cell
 *  @param[in]  RgSchUeCb         *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlUeDel
(
RgSchCellCb          *cell,
RgSchUeCb            *ue
)
#else
PUBLIC Void rgSCHMaxciDlUeDel(cell, ue)
RgSchCellCb          *cell;
RgSchUeCb            *ue;
#endif
{
   RgSchMaxciDlUe    *maxciDlUe   = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchCmnDlUe      *cmnDlUe     = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchDlHqEnt      *dlHqEnt     = RG_SCH_CMN_GET_UE_HQE(ue, cell);
   U8                hqProcIdx    = 0;
   TRC2(rgSCHMaxciDlUeDel);

   
   for (hqProcIdx = 0; hqProcIdx < dlHqEnt->numHqPrcs; hqProcIdx++)
   {
      RgSchDlHqProcCb  *hqP = &dlHqEnt->procs[hqProcIdx];
      if (hqP->subFrm != NULLP)                
      {
         if (hqP->pdcch)
         {
            cmLListDelFrm(&hqP->subFrm->pdcchInfo.pdcchs, 
                  &hqP->pdcch->lnk);
            cmLListAdd2Tail(&cell->pdcchLst, &hqP->pdcch->lnk);
            hqP->pdcch = NULLP;
         }
         if (hqP->hqPSfLnk.node != NULLP)
         {
            rgSCHUtlDlHqPTbRmvFrmTx(hqP->subFrm,hqP,0,FALSE);
         }
      }
   }
   /* Dealloc sched specific info in each proc */
   if (dlHqEnt->sch)
   {
       /* ccpu00117052 - MOD - Passing double pointer
       for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(cell->instIdx,
            (Data**)(&(dlHqEnt->sch)), 
            (dlHqEnt->numHqPrcs * sizeof(RgSchMaxciDlHqProc)));
   }

   if (maxciDlUe == NULLP)
   {
      RETVOID;
   }
   
   /* Removal from  tx and re-tx queues needed for the UE */
   if (maxciDlUe->txSrbLstPtr)
   {
      rgSCHMaxciDlDelUeFrmTxSrbLst(maxciDlUe);
   }
   if (maxciDlUe->txUeLstPtr)
   {
      rgSCHMaxciDlDelUeFrmTxUeLst(maxciDlUe);
   }
   if (maxciDlUe->retxLstPtr)
   {
      rgSCHMaxciDlDelUeFrmRetxLst(maxciDlUe);
   }

   /* Note: The logical channels associated with the UE shall be deleted
    * as part of dedicated logical channel delete for the UE */

    /* ccpu00117052 - MOD - Passing double pointer
    for proper NULLP assignment*/
   rgSCHUtlFreeSBuf(cell->instIdx,
         (Data**)(&(cmnDlUe->schSpfc)), (sizeof(RgSchMaxciDlUe)));
   RETVOID;
}

/**
 * @brief LC configuration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlLcCfg
 *
 *     Processing Steps:
 *      - Do validations
 *      - If DL LC is configured
 *        - Create maxciDlLc info and initialise vars
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchDlLcCb      *dlLc
 *  @param[in]  RgrLchCfg        *lcCfg
 *  @param[in]  RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciDlLcCfg
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc,
RgrLchCfg          *lcCfg,
RgSchErrInfo       *err
)
#else
PUBLIC S16 rgSCHMaxciDlLcCfg(cell, ue, dlLc, lcCfg, err)
RgSchCellCb        *cell;
RgSchUeCb          *ue;
RgSchDlLcCb        *dlLc;
RgrLchCfg          *lcCfg;
RgSchErrInfo       *err;
#endif
{
   S16             ret;
   RgSchMaxciDlLc  *maxciDlLc;
   RgSchCmnDlSvc   *cmnDlLc   = RG_SCH_CMN_GET_DL_SVC(dlLc);
   UNUSED(ue);
   UNUSED(lcCfg);
   TRC2(rgSCHMaxciDlLcCfg);

   
   if((ret = rgSCHUtlAllocSBuf(cell->instIdx, (Data**)&(RG_SCH_CMN_GET_LC_SCH_SPFC(ue,dlLc,cell)),
      (sizeof(RgSchMaxciDlLc)))) != ROK)
   {
      RLOG_ARG2(L_ERROR,DBG_CELLID,cell->cellId,
               "Memory allocation FAILED for MAX C/I DL LCID:%d CRNTI:%d",
               dlLc->lcId,ue->ueId);
      err->errCause = RGSCHERR_MAXCI_MEMERR;
      RETVALUE(ret);
   }

   maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
   
   /* Initializations for the DL LC  */
   maxciDlLc->isGbr = RG_SCH_CMN_SVC_IS_GBR(dlLc);
   if (maxciDlLc->isGbr)
   {
      maxciDlLc->mbr   = cmnDlLc->mbr;
      maxciDlLc->remMbr = maxciDlLc->mbr;
   }

   /* Intialize list nodes */
   RG_SCH_MAXCIDL_INIT_LNK(&(maxciDlLc->schdLnk), dlLc);

   /* Note: Assumed that the rest of the variables shall be memset to 0
    * during allocation */

   RETVALUE(ROK);
} 

/**
 * @brief LC re-configuration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlLcRecfg
 *
 *     Processing Steps:
 *      - If DL LC is re-configured
 *        - If LC type is GBR
 *          - Update mbr
 *      - [Need not do other changes for QoS update,
 *        vars update at refresh cycle shall take
 *        care of things]
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchDlLcCb      *dlLc
 *  @param[in]  RgrLchRecfg      *lcRecfg
 *  @param[in]  RgSchErrInfo     *err
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciDlLcRecfg
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc,
RgrLchRecfg        *lcRecfg,
RgSchErrInfo       *err
)
#else
PUBLIC S16 rgSCHMaxciDlLcRecfg(cell, ue, dlLc, lcRecfg, err)
RgSchCellCb        *cell;
RgSchUeCb          *ue;
RgSchDlLcCb        *dlLc;
RgrLchRecfg        *lcRecfg;
RgSchErrInfo       *err;
#endif
{
   RgSchMaxciDlLc  *maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
   RgSchCmnDlSvc   *cmnDlLc   = RG_SCH_CMN_GET_DL_SVC(dlLc);

   UNUSED(ue);
   UNUSED(lcRecfg);
   UNUSED(err);
   TRC2(rgSCHMaxciDlLcRecfg);


   /* Updations for Qos related DL logical channel are not done right away, will be
    * taken care by refresh cycle: assuming 'no QCI change' has been
    * validated in common module */
   if (RG_SCH_CMN_SVC_IS_GBR(dlLc))
   {
      maxciDlLc->mbr   = cmnDlLc->mbr;
   }

   RETVALUE(ROK);
}

/**
 * @brief LC deletion for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciDlLcDel
 *
 *     Processing Steps:
 *      - If DL LC is deleted
 *        - Delete maxciDlLc info
 *      - Need not do other changes for QoS update for AMBR services,
 *        vars update at refresh cycle shall take care of things
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchDlLcCb      *dlLc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlLcDel
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc
)
#else
PUBLIC Void rgSCHMaxciDlLcDel(cell, ue, dlLc)
RgSchCellCb        *cell;
RgSchUeCb          *ue;
RgSchDlLcCb        *dlLc;
#endif
{
   RgSchMaxciDlLc  *maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell); 
   UNUSED(ue);
   TRC2(rgSCHMaxciDlLcDel);

   
   if (maxciDlLc)
   {
      /* Remove from srb/gbr/non-gbr svcs list */
      if (maxciDlLc->lcLst)
      {
         rgSCHMaxciDlDelLcFrmUe(maxciDlLc);
      }

       /* ccpu00117052 - MOD - Passing double pointer
       for proper NULLP assignment*/
      rgSCHUtlFreeSBuf(cell->instIdx, (Data**)(&(RG_SCH_CMN_GET_LC_SCH_SPFC(ue,dlLc,cell))), 
            sizeof(RgSchMaxciDlLc));
   }

   RETVOID;
}


/**
 * @brief 
 *     Calculate priority level of UE and place in the queue accordingly
 *
 * @details
 *
 *     Function : rgSCHMaxciDlCqiInd
 *
 *     Processing Steps:
 *     - Calculate priority level. The range is from 0 to 15
 *     - The UE having priority level value as 15 is gets highest priority
 *        and UE having priority level value as 0 gets lowest priority
 *     - priority level is calculated and if it is different from earlier
 *       - Change retransmission queue if UE is present in one
 *       - Change new transmission queue if UE is present in one
 *     - CWInfo[0] corresponds single layer CW and CWInfo[1] corresponds 2 layer CW 
 *     else
 *     - Assumption: CQI has been updated for common UE before call to the API.  
 *
 *  @param[in]  RgSchCellCb      *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  TfuDlCqiRpt      *cqiInfo
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlCqiInd
(
RgSchCellCb          *cell,
RgSchUeCb            *ue,
Bool                 isPucchInfo,
Void                 *dlCqi
)
#else
PUBLIC Void rgSCHMaxciDlCqiInd(cell, ue, isPucchInfo, dlCqi)
RgSchCellCb          *cell;
RgSchUeCb            *ue;
Bool                 isPucchInfo;
Void                 *dlCqi;
#endif
{
   RgSchCmnDlUe      *cmnDlUe     = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchMaxciDlUe    *maxciDlUe   = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlCell  *maxciDlCell = RG_SCH_MAXCIDL_GET_CELL(cell);
   U32 cw0Eff = 0;
   U32 cw1Eff = 0;
   U8  numLyr=0;
   U8  priorLvl;

   UNUSED(isPucchInfo);
   UNUSED(dlCqi);
   TRC2(rgSCHMaxciDlCqiInd);
   
   numLyr = cmnDlUe->mimoInfo.cwInfo[0].noLyr;
   cw0Eff = cmnDlUe->mimoInfo.cwInfo[0].eff[numLyr-1];
   if ((numLyr = cmnDlUe->mimoInfo.cwInfo[1].noLyr) != 0)
   {
      cw1Eff = cmnDlUe->mimoInfo.cwInfo[1].eff[numLyr-1];
   }
    
      
   priorLvl = (U8)((cw0Eff + cw1Eff) / maxciDlCell->priorEff);


   if (priorLvl == maxciDlUe->priorLvl)
   {
      RETVOID;
   }
   /* If UE is in the transmitting/ re-transmitting priority queue, 
    * change the position of the UE in queues using priority level*/
   if (maxciDlUe->retxLstPtr == 
         &(maxciDlCell->retxQueues.ueLst[maxciDlUe->priorLvl]))
   {
      rgSCHMaxciDlDelUeFrmRetxLst(maxciDlUe);
      maxciDlUe->priorLvl = priorLvl;
      rgSCHMaxciDlAddUeToRetxUeLst(maxciDlCell, maxciDlUe);
   }

   maxciDlUe->priorLvl = priorLvl;
   if (maxciDlUe->txUeLstPtr)
   {
      rgSCHMaxciDlDelUeFrmTxUeLst(maxciDlUe);
      rgSCHMaxciDlAddUeToTxUeLst(maxciDlCell, maxciDlUe);
   }

   RETVOID;
}
/**
 * @brief Scheduling of UEs for TA
 *
 * @details
 *
 *     Function : rgSCHMaxciDlTaSchd
 *
 *     Processing Steps:
 *     - Schedules UEs for TA
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *alloc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlTaSchd
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHMaxciDlTaSchd(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   RgSchCmnDlCell       *cmnCell = RG_SCH_CMN_GET_DL_CELL(cell);
   RgSchDlSf            *dlSf      = alloc->dedAlloc.dedDlSf;
   CmLList              *lnk;
#ifdef LTEMAC_HDFDD
   Bool                 dlAllowed = FALSE;
#endif
   TRC2(rgSCHMaxciDlTaSchd);

   for (lnk = cmnCell->taLst.first; lnk; lnk = lnk->next)
   {
      RgSchUeCb            *ue = (RgSchUeCb *)lnk->node;
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
      rgSCHMaxciDlTaSchdForUe(cell, alloc, dlSf, ue);
   }

   RETVOID;
}

/**
 * @brief Scheduling of UE for TA
 *
 * @details
 *
 *     Function : rgSCHMaxciDlTaSchdForUe
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
 *  @param[in]  RgSchDlSf              *dlSf
 *  @param[in]  RgSchUeCb              *ue
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlTaSchdForUe
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc,
RgSchDlSf               *dlSf,
RgSchUeCb               *ue
)
#else
PRIVATE Void rgSCHMaxciDlTaSchdForUe(cell, alloc, dlSf, ue)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
RgSchDlSf               *dlSf;
RgSchUeCb               *ue;
#endif
{
   RgSchCmnDlUe         *cmnUe        = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchMaxciDlUe       *maxciDlUe    = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchDlHqProcCb      *proc;
   U32                  bytes         = 0;
   RgSchCmnDlHqProc    *cmnDlProc;

   TRC2(rgSCHMaxciDlTaSchdForUe);

   if (!(RG_SCH_CMN_DL_IS_UE_ACTIVE(ue)))
   {
      RETVOID;
   }

   if ((proc = rgSCHMaxciDlGetAvlProc(cell, ue, TRUE)) == NULLP)
   {
      RETVOID;
   }
   rgSCHCmnDlAllocTxRb(cell, dlSf, ue, RGSCH_TA_SIZE, &bytes, proc, alloc);
   /* TA size is 2 bytes, corresponding to the smallest possible
    * allocation. So check for zero allocation is enough to check
    * if there isn't sufficient allocation for TA. */
   if (bytes == 0)
   {
      rgSCHMaxciDlRlsHqP(proc);
      RETVOID;
   }
   cmnUe->proc = proc;
   maxciDlUe->isTaReq = TRUE;
   cmnDlProc = (RgSchCmnDlHqProc *)proc->sch;
   cmnDlProc->totBytes += bytes;
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlGetAvlProc
 *
 *     Desc : Gets an available HARQ proc by invoking DHM,
 *            and initialises it.
 *            Returns NULL if not proc available.
 *
 *     Ret  : RgSchDlHqProcCb *
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE RgSchDlHqProcCb *rgSCHMaxciDlGetAvlProc
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
Bool                   isSrb
)
#else
PRIVATE RgSchDlHqProcCb *rgSCHMaxciDlGetAvlProc(cell, ue, isSrb)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
Bool                   isSrb;
#endif
{
   RgSchCmnDlCell      *cmnCell = RG_SCH_CMN_GET_DL_CELL(cell);
   RgSchDlHqProcCb     *proc;
   RgSchMaxciDlHqProc  *maxciDlProc;
   RgSchCmnDlHqProc    *cmnDlProc;
   TRC2(rgSCHMaxciDlGetAvlProc);

   if (rgSCHDhmGetAvlHqProc(cell, ue, cmnCell->time, &proc) != ROK)
   {
      RETVALUE(NULLP);
   }
   cmnDlProc = (RgSchCmnDlHqProc *)proc->sch;
   cmnDlProc->totBytes = 0;
   maxciDlProc = RG_SCH_MAXCIDL_GET_HQP(proc);
   maxciDlProc->isSrb = isSrb;
   RETVALUE(proc);
}

/**
 * @brief Scheduling of DL re-transmissions
 *
 * @details
 *
 *     Function : rgSCHMaxciDlRetx
 *
 *     Processing Steps:
 *     - For each UE retx queue in order of SRB
 *       queue and then descending order of CQI queue
 *       - Skip UE if scheduled already
 *       - Pick a HARQ process if present from the SRB queue
 *         within UE (ueDl->retxSrbProcs), else pick from
 *         the other list (ueDl->retxProcs)
 *       - Add UE to 'alloc' retx list with appropriate variables
 *         filled in
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[out] RgSchCmnDlRbAllocInfo  *allocInfo
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlRetx
(
RgSchCellCb           *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)
#else
PRIVATE Void rgSCHMaxciDlRetx(cell, allocInfo)
RgSchCellCb           *cell;
RgSchCmnDlRbAllocInfo *allocInfo;
#endif
{
   RgSchMaxciDlCell   *maxciDlCell = RG_SCH_MAXCIDL_GET_CELL(cell);
   RgSchMaxciDlQueues *retxQs    = &maxciDlCell->retxQueues;
   RgSchUeCb          *ue;
   RgSchMaxciDlUe     *maxciDlUe;
   CmLListCp          *ueRetxProcs;
   CmLList            *lnk;
   S16                 priorLvlIdx;
   TRC2(rgSCHMaxciDlRetx);

   for (lnk = retxQs->srbLst.first; lnk; lnk = lnk->next)
   {
      ue          = (RgSchUeCb *)lnk->node;
      maxciDlUe   = RG_SCH_MAXCIDL_GET_UE(ue, cell);
      ueRetxProcs = &maxciDlUe->retxSrbProcs;
      rgSCHMaxciDlRetxUeSchd(cell, ue, allocInfo, ueRetxProcs);
   }

   /* ueLst[0] is never being used since '0' is considered as invalid CQI
    * value */ 
   for (priorLvlIdx = RG_SCH_MAXCIDL_NUM_CQI_LVLS - 1; priorLvlIdx >= 0; --priorLvlIdx)
   {
      for (lnk = retxQs->ueLst[priorLvlIdx].first; lnk; lnk = lnk->next)
      {
         ue          = (RgSchUeCb *)lnk->node;
         maxciDlUe   = RG_SCH_MAXCIDL_GET_UE(ue, cell);
         ueRetxProcs = &maxciDlUe->retxDrbProcs;
         rgSCHMaxciDlRetxUeSchd(cell, ue, allocInfo, ueRetxProcs);
      }
   }

   RETVOID;
}

/**
 * @brief scheduling for a cell
 *
 * @details
 *
 *     Function : rgSCHMaxciDlPreSchedNewTx
 *
 *     Processing Steps:
 *     - Nothing to be done in case of RR
 *
 *  @param[in]  Inst      schInst
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlPreSchedNewTx
(
 RgSchCellCb *cell
)
#else
PUBLIC Void rgSCHMaxciDlPreSchedNewTx(cell)
 RgSchCellCb *cell;
#endif
{
   TRC2(rgSCHMaxciDlPreSchedNewTx);
   
   RETVOID;
}
/**
 * @brief scheduling for a cell
 *
 * @details
 *
 *     Function : rgSCHMaxciDlPstSchedNewTx
 *
 *     Processing Steps:
 *     - Nothing to be done in case of RR
 *
 *  @param[in]  Inst      schInst
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlPstSchedNewTx
(
 Inst       schInst
)
#else
PUBLIC Void rgSCHMaxciDlPstSchedNewTx(schInst)
 Inst       schInst
#endif
{
   TRC2(rgSCHMaxciDlPstSchedNewTx);
   
   RETVOID;
}
/**
 * @brief Scheduling of DL new transmissions
 *
 * @details
 *
 *     Function : rgSCHMaxciDlNewTx
 *
 *     Processing Steps:
 *     - For each SRB [this part
 *       is to be a common functionality across
 *       all schedulers]
 *       - Skip if UE scheduled for retx
 *       - Schedule SRB
 *     - For each CQI queue in descending order
 *       - For each UE in queue
 *         - Skip if UE scheduled for retx
 *         - For each GBR svc
 *           - Schedule upto min(BO, MBR)
 *         - For each other (non-GBR) svc
 *           - If (AMBR applicable)
 *             - Schedule upto min(BO, AMBR)
 *           - Else
 *             - Schedule upto BO
 *     - While scheduling each UE in the above steps
 *       - If this UE has not yet been scheduled during
 *         this TTI processing
 *         - Get available HARQ process and associate with
 *           current TTI processing
 *       - Add UE to list of scheduled UEs in the 'alloc' structure
 *         with appropriate info filled in (required bytes, RBs etc).
 *         If UE is already added, just update the variables.
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[out] RgSchCmnDlRbAllocInfo  *alloc
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlNewTx
(
RgSchCellCb                *cell,
RgSchCmnDlRbAllocInfo      *alloc
)
#else
PRIVATE Void rgSCHMaxciDlNewTx(cell, alloc)
RgSchCellCb                *cell;
RgSchCmnDlRbAllocInfo      *alloc;
#endif
{
   RgSchDlSf               *dlSf        = alloc->dedAlloc.dedDlSf;
   RgSchDlLcCb             *dlLc;
   RgSchMaxciDlCell        *maxciDlCell = RG_SCH_MAXCIDL_GET_CELL(cell);
   RgSchMaxciDlUe          *maxciDlUe;
   RgSchMaxciDlLc          *maxciDlLc;
   RgSchMaxciDlTxQueues    *txQs        = &maxciDlCell->txQueues;
   CmLListCp               *txUeQ;
   CmLList                 *ueLnk;
   CmLList                 *lcLnk;
   RgSchUeCb               *ue          = NULLP; 
   S16                     priorLvlIdx;
   U32                     allocBytes;
   U32                     effAmbr;
#ifdef LTEMAC_HDFDD
   Bool                 dlAllowed = FALSE;
#endif
   TRC2(rgSCHMaxciDlNewTx);

   txUeQ = &txQs->srbLst;
   for (ueLnk = txUeQ->first; ueLnk; ueLnk = ueLnk->next)
   {
      /* Allocate for SRBs of all the UEs */
      ue = (RgSchUeCb *)ueLnk->node;
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
      maxciDlUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);
      for (lcLnk = maxciDlUe->srbLst.first; lcLnk; )
      {
         dlLc = (RgSchDlLcCb *)(lcLnk->node);
         lcLnk = lcLnk->next;
         maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
         allocBytes = maxciDlLc->bo;
         rgSCHMaxciDlLcSchd(cell, alloc, dlSf, ue,
               dlLc, TRUE, &allocBytes);
         if (!allocBytes)
         {
            /* Bandwidth exhausted */
            RETVOID;
         }
      }
   }

   /* ueLst[0] is never being used since '0' is considered as invalid CQI
    * value */ 
   for (priorLvlIdx = RG_SCH_MAXCIDL_NUM_CQI_LVLS -1; priorLvlIdx >= 0; --priorLvlIdx)
   {
      txUeQ = &txQs->ueLst[priorLvlIdx];
      for (ueLnk = txUeQ->first; ueLnk; ueLnk = ueLnk->next)
      {
         ue = (RgSchUeCb *)ueLnk->node;
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
         maxciDlUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);

         /* Allocate for GBR services */
         for (lcLnk = maxciDlUe->gbrLst.first; lcLnk; )
         {
            dlLc = (RgSchDlLcCb *)(lcLnk->node);
            lcLnk = lcLnk->next;
            maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
            allocBytes = RGSCH_MIN(maxciDlLc->bo, maxciDlLc->remMbr);
            if (allocBytes)
            {
               rgSCHMaxciDlLcSchd(cell, alloc, dlSf, ue,
                     dlLc, FALSE, &allocBytes);
               if (!allocBytes)
               {
                  /* Bandwidth exhausted */
                  RETVOID;
               }
            }
         }
         if (maxciDlUe->ambrPres)
         {
            /* Allocate for AMBR services */ 
            /* effAmbr is used as temp variable to keep track of the ambr
             * allocations in this TTI */
            effAmbr = maxciDlUe->remAmbr;
            for (lcLnk = maxciDlUe->nongbrLst.first; lcLnk && effAmbr;)
            {
               dlLc = (RgSchDlLcCb *)(lcLnk->node);
               lcLnk = lcLnk->next;
               maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
               allocBytes = RGSCH_MIN(maxciDlLc->bo, effAmbr);
               if (allocBytes)
               {
                  rgSCHMaxciDlLcSchd(cell, alloc, dlSf, ue,
                        dlLc, FALSE, &allocBytes);
                  if (!allocBytes)
                  {
                     /* Bandwidth exhausted */
                     RETVOID;
                  }
                  if (effAmbr > allocBytes)
                  {
                     effAmbr = effAmbr - allocBytes;
                  }
                  else
                  {
                     /* effAmbr = 0 */
                     break;
                  }
               }
            }
         }
         else
         {
            /* Allocate for non-gbr and non-ambr services */
            for (lcLnk = maxciDlUe->nongbrLst.first; lcLnk; )
            {
               dlLc = (RgSchDlLcCb *)(lcLnk->node);
               lcLnk = lcLnk->next;
               maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
               allocBytes = maxciDlLc->bo;
               rgSCHMaxciDlLcSchd(cell, alloc, dlSf, ue,
                     dlLc, FALSE, &allocBytes);
               if (!allocBytes)
               {
                  /* Bandwidth exhausted */
                  RETVOID;
               }
            }
         }
      }
   }
   RETVOID;
}

/**
 * @brief Handler for proc requiring re-transmission.
 *
 * @details
 *
 *     Function : rgSCHMaxciDlProcAddToRetx
 *
 *     Processing Steps:
 *     - Append the process in the appropriate priority class (non-SRB
 *       or SRB) queue for pending retransmissions
 *     - If this is the first process, add UE to a retransmitting queue
 *       corresponding to process priority: Either add to SRB queue if
 *       SRB data is carried by the HARQ buffer, or add to CQI queue
 *       corresponding to UE's current wideband CQI
 *     - Else if this process is the highest priority process, move the UE
 *       to the appropriate retransmission queue (move to SRB
 *       retx queue if this is first SRB retx HARQ proc)
 *
 *  @param[in]  RgSchCellCb              *cell
 *  @param[in]  RgSchDlHqProcCb          *hqP
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlProcAddToRetx
(
RgSchCellCb           *cell,
RgSchDlHqProcCb       *hqP
)
#else
PUBLIC Void rgSCHMaxciDlProcAddToRetx(cell, hqP)
RgSchCellCb           *cell;
RgSchDlHqProcCb       *hqP;
#endif
{
   RgSchMaxciDlCell   *maxciDlCell   = RG_SCH_MAXCIDL_GET_CELL(cell);
   RgSchUeCb          *ue            = hqP->hqE->ue;
   RgSchMaxciDlUe     *maxciDlUe     = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlHqProc *maxciDlHqProc = RG_SCH_MAXCIDL_GET_HQP(hqP);
   TRC2(rgSCHMaxciDlProcAddToRetx);

   if (maxciDlHqProc->isSrb)
   {
      /* SRB harq process handling for retransmission */
      rgSCHMaxciDlAddSrbHqProcToUe(maxciDlHqProc, maxciDlUe);
      if ((!maxciDlUe->retxLstPtr) && (RG_SCH_CMN_DL_IS_UE_ACTIVE(ue)))
      {
         rgSCHMaxciDlAddUeToRetxSrbLst(maxciDlCell, maxciDlUe);
      }
      else if (maxciDlUe->retxLstPtr == 
            &(maxciDlCell->retxQueues.ueLst[maxciDlUe->priorLvl]))
      {
         /* First SRB process of the UE:
          * Remove UE from priority list. Add UE to the SRB list */
         rgSCHMaxciDlDelUeFrmRetxLst(maxciDlUe);
         rgSCHMaxciDlAddUeToRetxSrbLst(maxciDlCell, maxciDlUe);
      } 
   }
   else
   {
      /* DRB harq process handling for re-transmission */
      rgSCHMaxciDlAddDrbHqProcToUe(maxciDlHqProc, maxciDlUe);
      if ((!maxciDlUe->retxLstPtr) && (RG_SCH_CMN_DL_IS_UE_ACTIVE(ue)))
      {
         rgSCHMaxciDlAddUeToRetxUeLst(maxciDlCell, maxciDlUe);
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
 *     Function: rgSCHMaxciDlRetxNewTxAlloc
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
PRIVATE Void rgSCHMaxciDlRetxNewTxAlloc 
(
RgSchCellCb           *cell,
RgSchCmnDlRbAllocInfo *alloc
)
#else
PRIVATE Void rgSCHMaxciDlRetxNewTxAlloc(cell, alloc)
RgSchCellCb           *cell;
RgSchCmnDlRbAllocInfo *alloc;
#endif
{
   CmLList              *lnk;
   CmLList              *node;
   RgSchMaxciDlUe       *maxciUe;
   RgSchDlHqTbCb        *newTxTbInfo;   
   RgSchDlRbAlloc       *ueAllocInfo;  
   U32                   effAlloc;
   U32                   remTbBytes;
   

   /* Take action for UEs that are finally scheduled for retx */
   for (lnk = alloc->dedAlloc.schdTxRetxHqPLst.first; lnk;)
   {
      RgSchDlHqProcCb   *proc      = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb         *ue        = proc->hqE->ue;
      lnk                          = lnk->next;
      maxciUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);
      ueAllocInfo = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
      /* Index 0 of ueAllocInfo->tbInfo will always hold the 
       * RETX TB and index 1 will hold the NewTX TB in case of
       * RETX+TX allocation. */
      newTxTbInfo = ueAllocInfo->tbInfo[1].tbCb;
      effAlloc = remTbBytes  =  ueAllocInfo->tbInfo[1].bytesAlloc;     
      node = maxciUe->srbLst.first;
      rgSCHMaxciDlSprTxTbDstn(cell, ue, newTxTbInfo,\
            &remTbBytes, &node);
      node = maxciUe->gbrLst.first;
      rgSCHMaxciDlSprTxTbDstn(cell, ue, newTxTbInfo,\
            &remTbBytes, &node);
      node = maxciUe->nongbrLst.first;
      rgSCHMaxciDlSprTxTbDstn(cell, ue, newTxTbInfo,\
            &remTbBytes, &node);  
      /* Trying to reduce mcs of TX TB to increase reception quality at UE.
       * In case of RETX+TX allocation, TX TB allocation was irrespective
       * of actual requirement by UE, hence in case if consumption is 
       * less than allocation, consider reducing the iMcs of this TX TB. */
      rgSCHCmnRdcImcsTxTb(ueAllocInfo, 1, effAlloc - remTbBytes);
      rgSCHMaxciDlRmvRetxProcFrmUe(cell, ue, proc);
      rgSCHMaxciDlReposUeInRetxQ(cell, ue);
      rgSCHCmnFillHqPPdcch(cell, ueAllocInfo, proc);
#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddUpdDLMark(cell, ue);
      }
#endif
      rgSCHMaxciDlRstUeTmpVars(cell, ue, proc);
   }

   /* Take action for UEs that are finally NOT scheduled for retx */
   for (lnk = alloc->dedAlloc.nonSchdTxRetxHqPLst.first; lnk;)
   {
      RgSchDlHqProcCb   *proc      = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb         *ue        = proc->hqE->ue;
      lnk                          = lnk->next;
      rgSCHMaxciDlRstUeTmpVars(cell, ue, proc);
   }

   RETVOID;

}

/**
 * @brief Invoked on final RB allocation for a DL subframe
 *
 * @details
 *
 *     Function : rgSCHMaxciDlAllocFnlz
 *
 *     Processing Steps:
 *     - For retx UE allocation
 *      - Call  rgSCHMaxciDlOnRetxAlloc
 *     - For tx UE alloction 
 *      - Call rgSCHMaxciDlOnNewTxAlloc
 *   3.1 MIMO
 *     - For retx + tx Ue allocation
 *      - Call rgSCHMaxciDlRetxNewTxAlloc
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *alloc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlAllocFnlz
(
RgSchCellCb            *cell,
RgSchCmnDlRbAllocInfo  *alloc
)
#else
PUBLIC Void rgSCHMaxciDlAllocFnlz(cell, alloc)
RgSchCellCb            *cell;
RgSchCmnDlRbAllocInfo  *alloc;
#endif
{
   TRC2(rgSCHMaxciDlAllocFnlz);
   rgSCHMaxciDlOnRetxAlloc(cell, alloc);

   rgSCHMaxciDlOnNewTxAlloc(cell, alloc);
   /* New Function added to handle TX+RETX 
    * harq process scheduling finalization */
   rgSCHMaxciDlRetxNewTxAlloc(cell, alloc);

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlOnNewTxAlloc
 *
 *     Desc : Do relevant updations corresponding to new
 *             tx allocations and updations for those
 *             which did not receive any allocations
 *             (freeing proc etc)
 *          - For each UE allocation for new transmission
 *           - Call rgSCHMaxciDlOnNewTxAllocForUe.
 *          - For each UE scheduled for 'new transmission' but
 *            for which allocation was not made
 *              - Release resources
 *              - Release HARQ process
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlOnNewTxAlloc
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHMaxciDlOnNewTxAlloc(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   CmLList            *lnk;
   TRC2(rgSCHMaxciDlOnNewTxAlloc);

   /* Take action for UEs that are finally scheduled for Tx */
   for (lnk = alloc->dedAlloc.schdTxHqPLst.first; lnk;)
   {
      RgSchDlHqProcCb    *proc = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb          *ue   = proc->hqE->ue;
      lnk                      = lnk->next;
      rgSCHMaxciDlOnNewTxAllocForUe(cell, ue, alloc);
#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddUpdDLMark(cell, ue);
      }
#endif
      rgSCHMaxciDlRstUeTmpVars(cell, ue, proc);
   }

   /* Take action for UEs that are finally NOT scheduled for Tx */
   for (lnk = alloc->dedAlloc.nonSchdTxHqPLst.first; lnk;)
   {
      RgSchDlHqProcCb    *proc = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb          *ue   = proc->hqE->ue;
      lnk                    = lnk->next;
      rgSCHMaxciDlRlsHqP(proc);
      rgSCHMaxciDlRstUeTmpVars(cell, ue, proc);
   }

   RETVOID;
}  /* rgSCHMaxciDlOnNewTxAlloc */

/***********************************************************
 *
 *     Func : rgSCHMaxciDlOnRetxAlloc
 *
 *     Desc : - Do relevant updations corresponding to retx
 *              allocations (and lack of them)
 *            - Remove alloced harq procs from the UE list of re-transmitting
 *              harq procs.
 *            - Move UE out of queue if no other HARQ proc
 *              needs retx
 *            - Keep UE in same queue or move to/from SRB retx queue
 *              based on another HARQ proc of the UE needing retx.
 *              For SM UEs consider harq state of both TBs in case of MIMO.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlOnRetxAlloc
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHMaxciDlOnRetxAlloc(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   CmLList            *lnk;
   TRC2(rgSCHMaxciDlOnRetxAlloc);

   /* Take action for UEs that are finally scheduled for retx */
   for (lnk = alloc->dedAlloc.schdRetxHqPLst.first; lnk;)
   {
      RgSchDlHqProcCb   *proc      = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb         *ue        = proc->hqE->ue;
      RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
      lnk                          = lnk->next;
      rgSCHCmnFillHqPPdcch(cell, dlAllocCb, proc);
#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddUpdDLMark(cell, ue);
      }
#endif
      /* Extra Check: Retain the hqProc in the RETX Queue if one/more
       * TBs of the HqProc are yet to be scheduled for RETX */
      if ((proc->tbInfo[0].state != HQ_TB_NACKED) && 
            (proc->tbInfo[1].state != HQ_TB_NACKED))     
      {
         rgSCHMaxciDlRmvRetxProcFrmUe(cell, ue, proc);
      }
      rgSCHMaxciDlReposUeInRetxQ(cell, ue);
      rgSCHMaxciDlRstUeTmpVars(cell, ue, proc);
   }

   /* Take action for UEs that are finally NOT scheduled for retx */
   for (lnk = alloc->dedAlloc.nonSchdRetxHqPLst.first; lnk;)
   {
      RgSchDlHqProcCb   *proc   = (RgSchDlHqProcCb *)lnk->node;
      RgSchUeCb         *ue     = proc->hqE->ue;
      lnk                       = lnk->next;
      rgSCHMaxciDlRstUeTmpVars(cell, ue, proc);
   }

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlNewTxTbDstn 
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
PRIVATE Void rgSCHMaxciDlNewTxTbDstn 
(
RgSchCellCb    *cell,
RgSchUeCb      *ue,
RgSchDlHqTbCb  *tbInfo,
U32            *effAlloc,
CmLList        **node
)
#else
PRIVATE Void rgSCHMaxciDlNewTxTbDstn(cell, ue, tbInfo, effAlloc, node)
RgSchCellCb    *cell;
RgSchUeCb      *ue;
RgSchDlHqTbCb  *tbInfo;
U32            *effAlloc;
CmLList        **node;
#endif
{
   RgSchMaxciDlUe     *maxciDlUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);   
   RgSchDlLcCb        *dlLc;
   RgSchMaxciDlLc     *maxciDlLc;
   CmLList            *prev = NULLP;
   U32                bytes;

   if(!tbInfo->schdTa.pres)   
   {
      if (maxciDlUe->isTaReq)                  
      {
         /* This is bound to not underflow. TA requires 2 bytes, and minimum
          * possible allocation is 2 bytes. */
         *effAlloc -= RGSCH_TA_SIZE;
         rgSCHCmnRmvFrmTaLst(cell, ue);
         rgSCHDhmSchdTa(ue, tbInfo);
      }
      if (!*effAlloc)
      {
         RETVOID;
      }
   }
   while(*node)
   {
      prev = *node;
      dlLc = (RgSchDlLcCb *)(*node)->node;
      maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
      *node = (*node)->next;
      bytes = RGSCH_MIN(*effAlloc, maxciDlLc->reqBytes);
      if (bytes <= maxciDlLc->hdrSz)
      {
         break;
      }
      else if (maxciDlLc->reqBytes < *effAlloc)
      {
         rgSCHMaxciDlLcFullyAllocd(cell, ue, dlLc, tbInfo);
         maxciDlLc->reqBytes -= bytes;
         *effAlloc -= bytes;
      }
      else
      {
         rgSCHMaxciDlLcPartlyAllocd(cell, ue, dlLc, *effAlloc, tbInfo);
         maxciDlLc->reqBytes -= *effAlloc;
         *effAlloc = 0;
         break;
      }
   }
   /* 3.1 MIMO refer the previous service to 
    * make sure if not served completely then 
    * the other TB allocation accomodates the same */
   *node = prev;
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlSprTxTbDstn 
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
PRIVATE Void rgSCHMaxciDlSprTxTbDstn
(
RgSchCellCb    *cell,
RgSchUeCb      *ue,
RgSchDlHqTbCb  *tbInfo,
U32            *effAlloc,
CmLList        **node
)
#else
PRIVATE Void rgSCHMaxciDlSprTxTbDstn(cell, ue, tbInfo, effAlloc, node)
RgSchCellCb    *cell;
RgSchUeCb      *ue;
RgSchDlHqTbCb  *tbInfo;
U32            *effAlloc;
CmLList        **node;
#endif
{
   RgSchDlLcCb        *dlLc;
   RgSchMaxciDlLc     *maxciDlLc;
   U32                bytes;
   CmLList            *prev = NULLP;
   U32                effBo;
   U32                rlcHdrEstmt;

   while(*node)
   {
      prev = *node;
      dlLc = (RgSchDlLcCb *)(*node)->node;
      maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
      *node = (*node)->next;
      RG_SCH_CMN_DL_GET_HDR_EST(dlLc, rlcHdrEstmt);
      effBo = maxciDlLc->bo + rlcHdrEstmt;
      bytes = RGSCH_MIN(*effAlloc, effBo);
      if (bytes < *effAlloc)
      {
         rgSCHMaxciDlBoUpdOnAlloc(cell, ue, dlLc, 0,
               (bytes-rlcHdrEstmt));
         rgSCHMaxciDlAddLcAllocToProc(cell, ue, dlLc, 
               bytes, tbInfo);
         *effAlloc -= bytes;
      }
      else if (bytes <= maxciDlLc->hdrSz)
      {
         break;
      }     
      else
      {
         rgSCHMaxciDlBoUpdOnAlloc(cell, ue, dlLc, maxciDlLc->bo 
               - (bytes - rlcHdrEstmt), (bytes - rlcHdrEstmt));
         rgSCHMaxciDlAddLcAllocToProc(cell, ue, dlLc, bytes, tbInfo);
         *effAlloc = 0;
         break;
      }
   }
   /* 3.1 MIMO refer the previous service to 
    * make sure if not served completely then 
    * the other TB allocation accomodates the same */
   *node = prev;
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlOnNewTxAllocForUe
 *
 *     Desc : Do relevant updations corresponding to new
 *            tx allocation for a UE
 *           - For each requested service,
 *            - If allocated bytes less than required bytes
 *              - Reduce allocations starting from last service,
 *                removing service(s) from allocations if required.
 *                (Excess allocation shall be be turned into padding.)
 *              - Update UE's remAmbr if needed
 *              - Update HARQ proc with final LC allocs
 *              - Change UE's position in queue or remove from queue
 *                (both SRB and/or CQI queues) based on if required
 *                bytes becomes zero
 *                - If no more DCCHs are present in queues within
 *                  UE, remove UE from SRB queue if present
 *                - If no more DTCHs are present in queues within
 *                  UE, remove UE from CQI queue if present
 *            - UEs that need to continue to stay in queues,
 *              shall be put at the back of their respective
 *              queues to simulate a round robin behaviour
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlOnNewTxAllocForUe
(
RgSchCellCb             *cell,
RgSchUeCb               *ue,
RgSchCmnDlRbAllocInfo   *alloc
)
#else
PRIVATE Void rgSCHMaxciDlOnNewTxAllocForUe(cell, ue, alloc)
RgSchCellCb             *cell;
RgSchUeCb               *ue;
RgSchCmnDlRbAllocInfo   *alloc;
#endif
{
   RgSchCmnDlUe       *cmnDlUe = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchMaxciDlUe     *maxciDlUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
   CmLList            *node;   
   U32                remTb1Bytes = dlAllocCb->tbInfo[0].bytesAlloc;
   U32                remTb2Bytes = dlAllocCb->tbInfo[1].bytesAlloc;
   U32                effAlloc = 0;
   /*ccpu00120365-ADD-added to code to check if second TB is utilized */
   U32                tb2Bytes = 0;


   TRC2(rgSCHMaxciDlOnNewTxAllocForUe);
   
   
   if (!(remTb1Bytes + remTb2Bytes))
   {
      RETVOID;
   }
   /* 3.1 MIMO Consider the allocation of New TX TB for distribution */
   /* Handle schd services */
   node = maxciDlUe->schdLcs.first;
   if (remTb1Bytes){
      effAlloc += remTb1Bytes;
      rgSCHMaxciDlNewTxTbDstn(cell, ue, &cmnDlUe->proc->tbInfo[0],\
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
      rgSCHMaxciDlNewTxTbDstn(cell, ue, &cmnDlUe->proc->tbInfo[1],\
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
      dlAllocCb->mimoAllocInfo.precIdxInfo = 0;
      dlAllocCb->mimoAllocInfo.numTxLyrs   = 1;
      dlAllocCb->tbInfo[1].schdlngForTb    = FALSE;
      dlAllocCb->tbInfo[1].isDisabled      = TRUE;
   }

   /* In the (rare) event that allocation was too small
    * and we think no LC data can fit (due to headers taking
    * up some space), we need to rollback allocation by
    * releasing PDCCH and proc. */
   if (effAlloc == (remTb1Bytes + remTb2Bytes))
   {
      rgSCHUtlPdcchPut(cell, &dlAllocCb->dlSf->pdcchInfo, 
            dlAllocCb->pdcch);
      rgSCHMaxciDlRlsHqP(cmnDlUe->proc);
      RETVOID;
   }

   /* Re-position the UE in transmitting queues to follow RR pattern */
   rgSCHMaxciDlReposUeInTxQ(cell, ue);


   /* Reset of the LCs have nothing allocated. Need not do anything
    * about them. */
   /* Fill PDCCH and assign it to proc */
   rgSCHCmnFillHqPPdcch(cell, dlAllocCb, cmnDlUe->proc);

   /* Reinit of schdLcs happens later as part of temporary variables
    * reset in function rgSCHMaxciDlRstUeTmpVars() */

   RETVOID;
}

 
/***********************************************************
 *
 *     Func : rgSCHMaxciDlReposUeInTxQ
 *
 *     Desc : - Repositions UE in cell-wide TX queues to follow RR pattern in 
 *              the UEs
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlReposUeInTxQ
(
RgSchCellCb           *cell,
RgSchUeCb             *ue
)
#else
PRIVATE Void rgSCHMaxciDlReposUeInTxQ(cell, ue)
RgSchCellCb           *cell;
RgSchUeCb             *ue;
#endif
{
   RgSchMaxciDlUe     *maxciDlUe    = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlCell   *maxciDlCell  = RG_SCH_MAXCIDL_GET_CELL(cell);
   TRC2(rgSCHMaxciDlReposUeInTxQ);

   if (maxciDlUe->txSrbLstPtr)
   {
      rgSCHMaxciDlDelUeFrmTxSrbLst(maxciDlUe);
      rgSCHMaxciDlAddUeToTxSrbLst(maxciDlCell, maxciDlUe);
   }
   if (maxciDlUe->txUeLstPtr)
   {
      rgSCHMaxciDlDelUeFrmTxUeLst(maxciDlUe);
      rgSCHMaxciDlAddUeToTxUeLst(maxciDlCell, maxciDlUe);
   }

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlBoUpdOnAlloc
 *
 *     Desc : 1.Update the bo post allocation for LC
 *            2.If bo = 0, remove logical channel from the UE list.
 *            3.If the last logical channel has been deleted, remove UE from
 *              the cell-wide trasmitting lists.
 *            3.If GBR logical channel, update remMbr accordingly.
 *            4.If AMBR logical channel, update remAmbr accordingly.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlBoUpdOnAlloc
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc,
U32                    remBo,
U32                    allocBo
)
#else
PRIVATE Void rgSCHMaxciDlBoUpdOnAlloc(cell, ue, dlLc, remBo, allocBo)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *dlLc;
U32                    remBo;
U32                    allocBo;
#endif
{
   RgSchMaxciDlUe      *maxciDlUe   = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlLc      *maxciDlLc   = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
   U32                 allocLimit   = 0;

   TRC2(rgSCHMaxciDlBoUpdOnAlloc);

   maxciDlLc->bo = remBo;
   if (RG_SCH_MAXCIDL_IS_SRB(dlLc))
   {
      /* Handling Bo update for SRB */
      if (!remBo)
      {
         /* Handling for bo = 0 */
         /* LC exists in the to-be scheduled list, remove it now */
         rgSCHMaxciDlDelLcFrmUe(maxciDlLc);
         if (!maxciDlUe->srbLst.count)
         {
            rgSCHMaxciDlDelUeFrmTxSrbLst(maxciDlUe);
         }
      }
      /* Non-zero BO handling */
      /* LC is already added to the list, do nothing */
      RETVOID;
   }

   /* Handling BO for DRB */
   if (RG_SCH_CMN_SVC_IS_GBR(dlLc))
   {
      maxciDlLc->remMbr = maxciDlLc->remMbr > allocBo ? 
         maxciDlLc->remMbr - allocBo : 0;
      allocLimit = maxciDlLc->remMbr;
   }
   else
   {
      if (maxciDlUe->ambrPres)
      {
         maxciDlUe->remAmbr = maxciDlUe->remAmbr > allocBo ? 
            maxciDlUe->remAmbr - allocBo : 0;
         allocLimit = maxciDlUe->remAmbr;
      }
   }
   if ((!remBo) || (!allocLimit))
   {
      /* Handling for bo = 0 for DRBs */
      /* LC exists in the to-be scheduled list, remove it now */
      rgSCHMaxciDlDelLcFrmUe(maxciDlLc);
      if ((!maxciDlUe->gbrLst.count) && (!maxciDlUe->nongbrLst.count))
      {
         rgSCHMaxciDlDelUeFrmTxUeLst(maxciDlUe);
      }
   }
   /* Non-zero BO handling for GBR/NON-GBR services */
   /* LC is already added to the list, do nothing */
   RETVOID;
}
/***********************************************************
 *
 *     Func : rgSCHMaxciDlLcFullyAllocd
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
PRIVATE Void rgSCHMaxciDlLcFullyAllocd
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc,
RgSchDlHqTbCb      *tbInfo
)
#else
PRIVATE Void rgSCHMaxciDlLcFullyAllocd(cell, ue, dlLc, tbInfo)
RgSchCellCb        *cell;
RgSchUeCb          *ue;
RgSchDlLcCb        *dlLc;
RgSchDlHqTbCb      *tbInfo;
#endif
{
   RgSchMaxciDlLc  *maxciDlLc  = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
   rgSCHMaxciDlBoUpdOnAlloc(cell, ue, dlLc, 0,
         (maxciDlLc->reqBytes - maxciDlLc->hdrSz));
   rgSCHMaxciDlAddLcAllocToProc(cell, ue, dlLc, 
         maxciDlLc->reqBytes, tbInfo);
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlLcPartlyAllocd
 *
 *     Desc : This function is called when an LC has
 *            been partly allocated for. The 'bytes'
 *            passed is the total allocated bytes,
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
PRIVATE Void rgSCHMaxciDlLcPartlyAllocd
(
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc,
U32                bytes,
RgSchDlHqTbCb      *tbInfo
)
#else
PRIVATE Void rgSCHMaxciDlLcPartlyAllocd(cell, ue, dlLc, bytes, tbInfo)
RgSchCellCb        *cell;
RgSchUeCb          *ue;
RgSchDlLcCb        *dlLc;
U32                bytes;
RgSchDlHqTbCb      *tbInfo;
#endif
{
   RgSchMaxciDlLc  *maxciDlLc  = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
   rgSCHMaxciDlBoUpdOnAlloc(cell, ue, dlLc, maxciDlLc->bo 
         - (bytes - maxciDlLc->hdrSz), (bytes - maxciDlLc->hdrSz));
   rgSCHMaxciDlAddLcAllocToProc(cell, ue, dlLc, bytes, tbInfo);
   /* Else no allocation is made to the LC. */
   RETVOID;
} 

/**
 * @brief Add LC allocation HARQ Proc
 *
 * @details
 *
 *     Function : rgSCHMaxciDlAddLcAllocToProc
 *
 *     Processing Steps:
 *     - Call common module API to add allocation for a
 *       logical channel to currently scheduled HARQ proc
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchDlLcCb            *dlLc
 *  @param[in]  U32                    allocBytes
 *  @param[in]  RgSchDlHqTbCb          *tbInfo
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlAddLcAllocToProc
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc,
U32                    allocBytes,
RgSchDlHqTbCb          *tbInfo
)
#else
PRIVATE Void rgSCHMaxciDlAddLcAllocToProc(cell, ue, dlLc, allocBytes, tbInfo)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *dlLc;
U32                    allocBytes;
RgSchDlHqTbCb          *tbInfo;
#endif
{
   RgSchLchAllocInfo   lchSchdData;
   lchSchdData.lcId = dlLc->lcId;
   lchSchdData.schdData = allocBytes; 
   rgSCHDhmAddLcData(cell->instIdx, &lchSchdData, tbInfo);

#ifdef LTE_L2_MEAS
   /* L2_COUNTERS */
   /* Increment qciActiveLCs once since this LCs buffer will be present
      in Harq process */
   if (dlLc->lcType == CM_LTE_LCH_DTCH)
   {
      ue->qciActiveLCs[dlLc->qciCb->qci]++;
   }
#endif

   RETVOID;
}
/***********************************************************
 *
 *     Func : rgSCHMaxciDlRmvRetxProcFrmUe
 *
 *     Desc : Remove retx proc from the UE list of re-transmitting procs.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlRmvRetxProcFrmUe
(
RgSchCellCb           *cell,
RgSchUeCb             *ue,
RgSchDlHqProcCb       *proc
)
#else
PRIVATE Void rgSCHMaxciDlRmvRetxProcFrmUe(cell, ue, proc)
RgSchCellCb           *cell;
RgSchUeCb             *ue;
RgSchDlHqProcCb       *proc;
#endif
{
   RgSchMaxciDlHqProc *maxciDlHqP = RG_SCH_MAXCIDL_GET_HQP(proc);
   RgSchMaxciDlUe     *maxciDlUe  = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   
   UNUSED(cell);
   TRC2(rgSCHMaxciDlRmvRetxProcFrmUe);

   if (maxciDlHqP->isSrb)
   {
      rgSCHMaxciDlDelSrbHqProcFrmUe(maxciDlHqP, maxciDlUe);
   }
   else
   {
      rgSCHMaxciDlDelDrbHqProcFrmUe(maxciDlHqP, maxciDlUe);
   }

   RETVOID;
}
/*
* @brief This function removes a HARQ process from the retx
*
* @details
*
*     Function: rgSCHMaxciDlRmvRetxProcFrmCell
*     Purpose:  This function removes a HARQ process from retransmission
*               queue. This may be performed when a HARQ ack is successful
*               for a retransmission or during UE reset
*
*  @param[in]  RgSchCellCb      *cell
*  @param[in]  RgSchDlHqProcCb  *hqP
*  @return  Void
*
**/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlRmvRetxProcFrmCell
(
 RgSchCellCb                *cell,
 RgSchUeCb             *ue,
 RgSchDlHqProcCb            *hqP
 )
#else
PRIVATE Void rgSCHMaxciDlRmvRetxProcFrmCell(cell, hqP)
   RgSchCellCb                *cell;
   RgSchUeCb             *ue;
   RgSchDlHqProcCb            *hqP;
#endif
{
   RgSchCmnCell *schCmnCell = (RgSchCmnCell *)(cell->sc.sch);
   RgSchMaxciDlCell *maxciDlCell = (RgSchMaxciDlCell *)(schCmnCell->dl.schSpfc);
   RgSchMaxciDlHqProc *schMaxciDlHqProc =
      &((RgSchMaxciDlHqProc *)hqP->hqE->sch)[hqP->procId];
   RgSchMaxciDlUe     *maxciDlUe  = RG_SCH_MAXCIDL_GET_UE(ue, cell);

   TRC2(rgSCHMaxciDlRmvRetxProcFrmCell);

   if(schMaxciDlHqProc->ueLnk.node != NULLP)
   {
      if(schMaxciDlHqProc->isSrb)
      {
      cmLListDelFrm(&(maxciDlCell->retxQueues.srbLst),
            &(schMaxciDlHqProc->ueLnk));
      }
      else
      {
      cmLListDelFrm(&(maxciDlCell->retxQueues.ueLst[maxciDlUe->wbCqi]),
            &(schMaxciDlHqProc->ueLnk));
      }
      schMaxciDlHqProc->ueLnk.node = NULLP;
   }

   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlRmvRetxProcFrmList
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
PUBLIC Void rgSCHMaxciDlRmvRetxProcFrmList
(
 RgSchCellCb         *cell,
 RgSchUeCb           *ue,
 RgSchDlHqProcCb     *proc
 )
#else
PUBLIC Void rgSCHMaxciDlRmvRetxProcFrmList(cell, ue, proc)
   RgSchCellCb         *cell;
   RgSchUeCb           *ue;
   RgSchDlHqProcCb     *proc;
#endif
{
   TRC2(rgSCHMaxciDlRmvRetxProcFrmList);

   rgSCHMaxciDlRmvRetxProcFrmCell(cell, ue, proc);
   rgSCHMaxciDlRmvRetxProcFrmUe(cell, ue, proc);
   /* This proc may not be free yet, do nothing else.*/
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlScanUpdPdbPrio
 *
 *     Desc : Increment the pivot and reposition the LCs under the pivot to 
 *            new location according to thieir PDB and elapsed time.
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlScanUpdPdbPrio
(
RgSchCellCb *cell
)
#else
PUBLIC Void rgSCHMaxciDlScanUpdPdbPrio (cell)
RgSchCellCb *cell;
#endif
{
   TRC2(rgSCHMaxciDlScanUpdPdbPrio);
   
   RETVOID;
}

/**
 * @brief Function to update Flow control information 
 *        to be sent to MAC.
 *
 * @details
 *
 *     Function: rgSCHMaxciDlFillFlowCntrlInfo
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
PUBLIC S16 rgSCHMaxciDlFillFlowCntrlInfo
(
RgSchCellCb    *cell,
RgInfSfAlloc   *sfAlloc
)
#else
PUBLIC S16 rgSCHMaxciDlFillFlowCntrlInfo(cell,sfAlloc)
RgSchCellCb    *cell;
RgInfSfAlloc   *sfAlloc;
#endif
{
  TRC2(rgSCHMaxciDlFillFlowCntrlInfo);
  RETVALUE(ROK);
}
/***********************************************************
 *
 *     Func : rgSCHMaxciDlReposUeInRetxQ
 *
 *     Desc : Reposition UE in re-transmitting queues after allocation
 *             - If UE was part of SRB queue
 *                - Remove UE from SRB queue.
 *                - If SRB harq procs still remain to be scheduled, 
 *                   - Add UE to SRB list to follow RR pattern in selection of UEs
 *                - else,
 *                   - If DRB procs are pending to schedule, add UE to DRB queue.
 *             - If UE was part of DRB queue
 *                - Remove UE from DRB queue.
 *                - If DRB harq procs still remain to be scheduled, 
 *                   - Add UE to DRB list to follow RR pattern in selection of UEs
 *
 *     Ret  : Void
 *
 *     Notes:
 *
 *     File :
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlReposUeInRetxQ
(
RgSchCellCb           *cell,
RgSchUeCb             *ue
)
#else
PRIVATE Void rgSCHMaxciDlReposUeInRetxQ(cell, ue)
RgSchCellCb           *cell;
RgSchUeCb             *ue;
#endif
{
   RgSchMaxciDlUe     *maxciDlUe    = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlCell   *maxciDlCell  = RG_SCH_MAXCIDL_GET_CELL(cell);

   TRC2(rgSCHMaxciDlReposUeInRetxQ);

   if (maxciDlUe->retxLstPtr == &(maxciDlCell->retxQueues.srbLst))
   {
      /* UE had been part of cell-wide retx SRB queues, remove if all 
       * the SRB HARQ procs have been scheduled else add to end of the queue */
      rgSCHMaxciDlDelUeFrmRetxLst(maxciDlUe);
      if (maxciDlUe->retxSrbProcs.count)
      {
         rgSCHMaxciDlAddUeToRetxSrbLst(maxciDlCell, maxciDlUe);
      }
      else if (maxciDlUe->retxDrbProcs.count)
      {
         rgSCHMaxciDlAddUeToRetxUeLst(maxciDlCell, maxciDlUe);
      }
   }
   else if (maxciDlUe->retxLstPtr == 
         &(maxciDlCell->retxQueues.ueLst[maxciDlUe->priorLvl]))
   {
      /* UE had been part of cell-wide retx DRB queues, remove if all 
       * the DRB HARQ procs have been scheduled else add to end of the queue */
      /* Note: UE shall never have retx SRB procs at this point, so not checking
       * it */
      rgSCHMaxciDlDelUeFrmRetxLst(maxciDlUe);
      if (maxciDlUe->retxDrbProcs.count)
      {
         rgSCHMaxciDlAddUeToRetxUeLst(maxciDlCell, maxciDlUe);
      }
   }

   /* This proc may not be free yet, do nothing else.*/
   RETVOID;
}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlRstUeTmpVars
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
PRIVATE Void rgSCHMaxciDlRstUeTmpVars
(
RgSchCellCb             *cell,
RgSchUeCb               *ue,
RgSchDlHqProcCb         *hqP
)
#else
PRIVATE Void rgSCHMaxciDlRstUeTmpVars(cell, ue, hqP)
RgSchCellCb             *cell;
RgSchUeCb               *ue;
RgSchDlHqProcCb         *hqP;
#endif
{
   RgSchMaxciDlUe       *maxciDlUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);

   UNUSED(cell);
   TRC2(rgSCHMaxciDlRstUeTmpVars);
   
   /* Reset variables of cmnUe */   
   rgSCHCmnDlUeResetTemp(ue, hqP);

   /* Not explicitly removing LCs from list of
    * scheduled services; just doing a list init.
    * Redundant for retx case.
    */
   cmLListInit(&maxciDlUe->schdLcs);

   maxciDlUe->isTaReq = FALSE;

   RETVOID;
}  /* rgSCHMaxciDlRstUeTmpVars */

/**
 * @brief BO update
 *
 * @details
 *
 *     Function : rgSCHMaxciDlDedBoUpd
 *
 *     Processing Steps:
 *     - If BO update is for DCCH
 *      - Call rgSCHMaxciDlSrbBoUpd
 *     -else
 *       - Call rgSCHMaxciDlDrbBoUpd
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchDlLcCb            *dlLc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlDedBoUpd
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc
)
#else
PUBLIC Void rgSCHMaxciDlDedBoUpd(cell, ue, dlLc)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *dlLc;
#endif
{
   TRC2(rgSCHMaxciDlDedBoUpd);

   /* dlLc->bo shall be set by common module prior to call to this API */
   if (RG_SCH_MAXCIDL_IS_SRB(dlLc))
   {
      /* Handling Bo update for SRB */
      rgSCHMaxciDlSrbBoUpd(cell, ue, dlLc, dlLc->bo);
   }
   else
   {
      /* Handling Bo update for DRB */
      rgSCHMaxciDlDrbBoUpd(cell, ue, dlLc, dlLc->bo);
   }
   RETVOID;
}

/**
 * @brief BO update
 *
 * @details
 *
 *     Function : rgSCHMaxciDlSrbBoUpd
 *
 *     Processing Steps:
 *     - BO update for DCCH
 *       - If BO > 0 and DCCH not UE queue
 *         - Add DCCH to the same (SRB queue)
 *       - If BO == 0 and DCCH is in UE queue,
 *         - Remove it from queue
 *       - If UE has one or more DCCHs in its queues
 *         and is not present in cell wide SRB queue
 *         - Add UE to SRB queue
 *       - If UE has no DCCHs in its queues but
 *         is still present in cell wide SRB queue
 *         - Remove UE from SRB queue
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchDlLcCb            *dlLc
 *  @param[in]  U32                    bo
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlSrbBoUpd
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc,
U32                    bo
)
#else
PRIVATE Void rgSCHMaxciDlSrbBoUpd(cell, ue, dlLc, bo)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *dlLc;
U32                    bo;
#endif
{
   RgSchMaxciDlCell    *maxciDlCell = RG_SCH_MAXCIDL_GET_CELL(cell);
   RgSchMaxciDlUe      *maxciDlUe   = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlLc      *maxciDlLc   = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
   CmLListCp           *lcLst       = NULLP;
   TRC2(rgSCHMaxciDlSrbBoUpd);

   if (bo)
   {
      /* Non-zero BO handling */
      if (!maxciDlLc->lcLst)
      {
         lcLst = &(maxciDlUe->srbLst);
         rgSCHMaxciDlAddLcToUe(maxciDlLc, lcLst);
         if ((!maxciDlUe->txSrbLstPtr) && (RG_SCH_CMN_DL_IS_UE_ACTIVE(ue)))
         {
            rgSCHMaxciDlAddUeToTxSrbLst(maxciDlCell, maxciDlUe);
         }
      }
      maxciDlLc->bo = bo;
      RETVOID;
   }

   /* Handling for bo = 0 */
   if (maxciDlLc->lcLst)
   {
      rgSCHMaxciDlDelLcFrmUe(maxciDlLc);
      if (!maxciDlUe->srbLst.count)
      {
         rgSCHMaxciDlDelUeFrmTxSrbLst(maxciDlUe);
      }
   }
   maxciDlLc->bo = bo;
   RETVOID;
}

/**
 * @brief BO update
 *
 * @details
 *
 *     Function : rgSCHMaxciDlDrbBoUpd
 *
 *     Processing Steps:
 *     - BO update is for DTCH
 *       - If BO > 0 and DTCH is eligible for servicing,
 *         - If DTCH not in gbrLst or nongbrLst
 *           - Add DTCH to gbrLst or nongbrLst based on
 *             DTCH type
 *           - Add UE to CQI queue if not already present
 *       - If BO == 0 and DTCH is present in gbrLst or
 *         nongbrLst
 *         - Remove DTCH from list
 *         - If both gbrLst and nongbrLst are empty
 *           - Remove UE from cell wide CQI queue
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchUeCb              *ue
 *  @param[in]  RgSchDlLcCb            *dlLc
 *  @param[in]  U32                    bo
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlDrbBoUpd
(
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *dlLc,
U32                    bo
)
#else
PRIVATE Void rgSCHMaxciDlDrbBoUpd(cell, ue, dlLc, bo)
RgSchCellCb            *cell;
RgSchUeCb              *ue;
RgSchDlLcCb            *dlLc;
U32                    bo;
#endif
{
   RgSchMaxciDlCell    *maxciDlCell  = RG_SCH_MAXCIDL_GET_CELL(cell);
   RgSchMaxciDlUe      *maxciDlUe    = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlLc      *maxciDlLc    = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
   CmLListCp           *lcLst        = NULLP;
   /* Assigning allocLimit to high value which shall be later re-assigned 
    * in case of GBR services */
   U32                 allocLimit = 0xffff;
   TRC2(rgSCHMaxciDlDrbBoUpd);

   if (RG_SCH_CMN_SVC_IS_GBR(dlLc))
   {
      lcLst = &(maxciDlUe->gbrLst);
      allocLimit = RGSCH_MIN(bo, maxciDlLc->remMbr);
   }
   else
   {
      lcLst = &(maxciDlUe->nongbrLst);
   }

   if (bo && allocLimit)
   {
      /* Non-zero BO handling */
      if ((!maxciDlLc->lcLst))
      {
         rgSCHMaxciDlAddLcToUe(maxciDlLc, lcLst);
         if ((!maxciDlUe->txUeLstPtr) && (RG_SCH_CMN_DL_IS_UE_ACTIVE(ue)))
         {
            rgSCHMaxciDlAddUeToTxUeLst(maxciDlCell, maxciDlUe);
         }
      }
   }
   else if (!bo)
   {
      /* Handling for bo = 0 */
      if (maxciDlLc->lcLst)
      {
         rgSCHMaxciDlDelLcFrmUe(maxciDlLc);
         if ((!maxciDlUe->gbrLst.count) && (!maxciDlUe->nongbrLst.count))
         {
            rgSCHMaxciDlDelUeFrmTxUeLst(maxciDlUe);
         }
      }
   }
   maxciDlLc->bo = bo;
   RETVOID;
}

/**
 * @brief UE refresh
 *
 * @details
 *
 *     Function : rgSCHMaxciDlUeRefresh
 *
 *     Processing Steps:
 *     - For DL
 *       - If AMBR configured
 *         - Set UE's remAmbr = ambr
 *       - For each GBR DTCH
 *         - Set remMbr = mbr
 *       - Invoke BO update for the LCs that might get added to queue due to
 *         above updation
 *       - If UE in not in cell-wide CQI queue
 *         - If the processing above causes at least one
 *           DTCH to be present in one of UE's queues
 *           - Add UE to appropriate CQI queue
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlUeRefresh
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PUBLIC Void rgSCHMaxciDlUeRefresh(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchMaxciDlUe      *maxciDlUe    = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlLc      *maxciDlLc;
   U8                  lcIdx;

   TRC2(rgSCHMaxciDlUeRefresh);

   /* GBR/AMBR related updates */
   maxciDlUe->remAmbr = ue->dl.ambrCfgd;
   for (lcIdx = 0; lcIdx < RGSCH_MAX_LC_PER_UE; ++lcIdx)
   {
      RgSchDlLcCb        *dlLc = ue->dl.lcCb[lcIdx];
      if (!dlLc)
      {
         continue;
      }
      maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
      if (RG_SCH_MAXCIDL_IS_SRB(dlLc))
      {
         continue;
      }
      if (maxciDlLc->isGbr)
      {
         maxciDlLc->remMbr = maxciDlLc->mbr;
      }
      rgSCHMaxciDlDrbBoUpd(cell, ue, dlLc, maxciDlLc->bo);
   }

   RETVOID;
}

/**
 * @brief UE Reset
 *
 * @details
 *
 *     Function : rgSCHMaxciDlUeReset
 *
 *     Processing Steps:
 *     - Remove SRB and DRB harq procs from the UE.
 *     - Remove UE from all scheduling queues.
 *     - Reset bo for all logical channels of UE.
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlUeReset
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PUBLIC Void rgSCHMaxciDlUeReset(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchMaxciDlLc     *maxciDlLc;
   RgSchMaxciDlUe     *maxciDlUe  = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchDlHqEnt          *hqEnt = RG_SCH_CMN_GET_UE_HQE(ue, cell);
   CmLList            *lstLnk;
   RgSchDlHqProcCb    *hqP;
   RgSchMaxciDlHqProc *maxciDlHqProc;
   U8                 idx;
   U8                 tbCnt;
   U8                 hqProcIdx;

   UNUSED(cell);
   TRC2(rgSCHMaxciDlUeReset);

   /* Assuming common module shall reset the bo value to 0 for LCs of the UE */
   for (idx = 0; idx < RGSCH_MAX_LC_PER_UE; ++idx)
   {
      RgSchDlLcCb        *dlLc = ue->dl.lcCb[idx];
      if (!dlLc)
      {
         continue;
      }
      maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
      if (maxciDlLc->lcLst)
      {
         rgSCHMaxciDlDelLcFrmUe(maxciDlLc);
      }
   }

   /* Delete harq procs from the UE */
   for (hqProcIdx = 0; hqProcIdx < hqEnt->numHqPrcs; hqProcIdx++)
   {
      hqP = &hqEnt->procs[hqProcIdx];
      if (hqP->subFrm != NULLP)
      {
         if (hqP->pdcch)
         {
            cmLListDelFrm(&hqP->subFrm->pdcchInfo.pdcchs, 
                  &hqP->pdcch->lnk);
            cmLListAdd2Tail(&cell->pdcchLst, &hqP->pdcch->lnk);
            hqP->pdcch =  NULLP;
         }
         if (hqP->hqPSfLnk.node != NULLP)
         {
            rgSCHUtlDlHqPTbRmvFrmTx(hqP->subFrm,hqP,0,FALSE);
         }
      }
      for (tbCnt = 0; tbCnt < 2; tbCnt++)
      {
         if (hqP->tbInfo[tbCnt].state == HQ_TB_WAITING)
         {
            rgSCHDhmRlsHqpTb(hqP, tbCnt, TRUE);
         }
      }
   }

   /* Delete SRB harq procs from the UE */
   for (lstLnk = maxciDlUe->retxSrbProcs.first; lstLnk; lstLnk = lstLnk->next)
   {
      hqP = (RgSchDlHqProcCb *)lstLnk->node;
      maxciDlHqProc = RG_SCH_MAXCIDL_GET_HQP(hqP);
      rgSCHMaxciDlDelSrbHqProcFrmUe(maxciDlHqProc, maxciDlUe);
      maxciDlHqProc->isSrb = FALSE;
   }

   /* Delete DRB harq procs from the UE */
   for (lstLnk = maxciDlUe->retxDrbProcs.first; lstLnk; lstLnk = lstLnk->next)
   {
      hqP = (RgSchDlHqProcCb *)lstLnk->node;
      maxciDlHqProc = RG_SCH_MAXCIDL_GET_HQP(hqP);
      rgSCHMaxciDlDelDrbHqProcFrmUe(maxciDlHqProc, maxciDlUe);
      maxciDlHqProc->isSrb = FALSE;
   }

   /* Remove UE from cell-wide Tx and Re-tx Ue lists */
   if (maxciDlUe->txSrbLstPtr)
   {
      rgSCHMaxciDlDelUeFrmTxSrbLst(maxciDlUe);
   }
   if (maxciDlUe->txUeLstPtr)
   {
      rgSCHMaxciDlDelUeFrmTxUeLst(maxciDlUe);
   }
   if (maxciDlUe->retxLstPtr)
   {
      rgSCHMaxciDlDelUeFrmRetxLst(maxciDlUe);
   }

   RETVOID;
}

/**
 * @brief Handles UE on activation
 *
 * @details
 *
 *     Function : rgSCHMaxciDlActvtUe
 *
 *     Processing Steps:
 *     - If SRB retransmitting proc exists, add to cell-wide reTx SRB list.
 *     - If DRB retransmitting proc exist, add to cell-wide reTx UE priority
 *       list.
 *     - If SRB service is pending for transmission, add to cell-wide Tx SRB
 *       UE list.
 *     - If GBR/NON-BGR services are pending for transmission, add to cell-wide
 *       Tx UE priority list.
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlActvtUe
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PUBLIC Void rgSCHMaxciDlActvtUe(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchMaxciDlUe   *maxciDlUe   = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlCell *maxciDlCell = RG_SCH_MAXCIDL_GET_CELL(cell);
   TRC2(rgSCHMaxciDlActvtUe);
   
   if (maxciDlUe->retxSrbProcs.count)
   {
      rgSCHMaxciDlAddUeToRetxSrbLst(maxciDlCell, maxciDlUe);
   }
   else if (maxciDlUe->retxDrbProcs.count)
   {
      rgSCHMaxciDlAddUeToRetxUeLst(maxciDlCell, maxciDlUe);
   }
   if (maxciDlUe->srbLst.count)
   {
      rgSCHMaxciDlAddUeToTxSrbLst(maxciDlCell, maxciDlUe);
   }
   if ((maxciDlUe->gbrLst.count) || (maxciDlUe->nongbrLst.count))
   {
      rgSCHMaxciDlAddUeToTxUeLst(maxciDlCell, maxciDlUe);
   }

   RETVOID;
}

/**
 * @brief Handles inactive UEs 
 *
 * @details
 *
 *     Function : rgSCHMaxciDlHndlInActvUes
 *
 *     Processing Steps:
 *     - Remove UE from transmitting/re-transmitting queues, if exist.
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  CmLListCp          *inactvUeLst
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciDlHndlInActvUes
(
RgSchCellCb         *cell,
CmLListCp           *inactvUeLst
)
#else
PUBLIC Void rgSCHMaxciDlHndlInActvUes(cell, inactvUeLst)
RgSchCellCb         *cell;
CmLListCp           *inactvUeLst;
#endif
{
   /* Remove UE from cell-wide Tx and Re-tx Ue lists */
   CmLList          *inactvUeLnk = inactvUeLst->first;
   RgSchMaxciDlUe   *maxciDlUe;
   RgSchUeCb *inactvUe = NULLP;   
   UNUSED(cell);
   TRC2(rgSCHMaxciDlHndlInActvUes);

   for (;inactvUeLnk; inactvUeLnk = inactvUeLnk->next)
   {
      inactvUe = (RgSchUeCb *)inactvUeLnk->node;
      maxciDlUe = RG_SCH_MAXCIDL_GET_UE(inactvUe, cell);
      if (maxciDlUe->txSrbLstPtr)
      {
         rgSCHMaxciDlDelUeFrmTxSrbLst(maxciDlUe);
      }
      if (maxciDlUe->txUeLstPtr)
      {
         rgSCHMaxciDlDelUeFrmTxUeLst(maxciDlUe);
      }
      if (maxciDlUe->retxLstPtr)
      {
         rgSCHMaxciDlDelUeFrmRetxLst(maxciDlUe);
      }
   }

   RETVOID;
}

/**
 * @brief Scheduling of DL re-transmissions corresponding to
 *        a re-transmission queue
 *
 * @details
 *
 *     Function : rgSCHMaxciDlRetxUeSchd
 *
 *     Processing Steps:
 *     - For each proc in queue
 *       - If UE not scheduled, schedule HARQ process
 *
 *  @param[in]      RgSchCellCb            *cell
 *  @param[in]      RgSchUeCb              *ue
 *  @param[in, out] RgSchCmnDlRbAllocInfo  *alloc
 *  @param[in]      CmLListCp              *retxProcs
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlRetxUeSchd
(
RgSchCellCb             *cell,
RgSchUeCb               *ue,
RgSchCmnDlRbAllocInfo   *alloc,
CmLListCp               *retxProcs
)
#else
PRIVATE Void rgSCHMaxciDlRetxUeSchd(cell, ue, alloc, retxProcs)
RgSchCellCb             *cell;
RgSchUeCb               *ue;
RgSchCmnDlRbAllocInfo   *alloc;
CmLListCp               *retxProcs;
#endif
{
   RgSchDlSf          *dlSf      = alloc->dedAlloc.dedDlSf;
   RgSchCmnDlUe       *cmnUe     = RG_SCH_CMN_GET_DL_UE(ue, cell);
   CmLList            *lnk;
   RgSchDlRbAlloc *dlAllocCb = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
#ifdef LTEMAC_SPS
   CmLteTimingInfo    schdTime;
#endif
#ifdef LTEMAC_HDFDD
   Bool                 dlAllowed = FALSE;
#endif
   TRC2(rgSCHMaxciDlRetxUeSchd);
#ifdef LTEMAC_SPS
   schdTime = cell->crntTime;

   /* Increment by DL DELTA to determine the time for which scheduling
    * is done */
   RGSCH_INCR_SUB_FRAME(schdTime, RG_SCH_CMN_DL_DELTA);
   if (RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime))
   {
      RETVOID;
   }
#endif

#ifdef LTEMAC_HDFDD
   if (ue->hdFddEnbld)
   {
      rgSCHCmnHdFddChkDlAllow ( cell, ue, &dlAllowed);
      if (dlAllowed == FALSE)
      {
         RETVOID;
      }
   }
#endif

   if (RG_SCH_CMN_IS_UE_SCHDLD(ue, cell))
   {
      RETVOID;
   }

   for (lnk = retxProcs->first; lnk; lnk = lnk->next)
   {
      /* Allocate for a re-transmitting proc: exit if allocation for 1 proc is
       * successful */
      RgSchDlHqProcCb     *proc = (RgSchDlHqProcCb *)lnk->node;
      U32                  ret  = 0;
      RgSchMaxciDlUe     *maxciUe   = RG_SCH_MAXCIDL_GET_UE(ue, cell);
      /* Extra check: indicate if there is furtherScope for NewTx
       * addition for a HqProc. This information will
       * be utilized by common scheduler, in case of SM
       * UEs with only one of the TBs retransmitting and the 
       * other TB can be used for clubbing new TX. */
      if ((maxciUe->srbLst.first!= NULLP) || (maxciUe->gbrLst.first!= NULLP)\
            || (maxciUe->nongbrLst.first!= NULLP))
      {
         dlAllocCb->mimoAllocInfo.hasNewTxData = TRUE; 
      }
      /* 3.1 MIMO : last parameter changed */
      if(rgSCHCmnDlAllocRetxRb(cell, dlSf, ue, 0, &ret, proc, alloc) !=\
              ROK)
      {
          RETVOID;
      }

      if ((proc->tbInfo[0].state == HQ_TB_ACKED)
              && (proc->tbInfo[1].state == HQ_TB_ACKED))
      {
          rgSCHMaxciDlRmvRetxProcFrmUe(cell, ue, proc);
          continue;
      }

      if (ret == 0)
      {
         continue;
      }
      cmnUe->proc = proc;
      /* 3.1 MIMO moving this call in cmn scheduler */
      /*rgSCHCmnDlRbInfoAddUeRetx(allocInfo, ue);*/
      break;
   }
   RETVOID;
}


/***********************************************************
 *
 *     Func : rgSCHMaxciDlLcSchd
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
PRIVATE S16 rgSCHMaxciDlLcSchd
(
RgSchCellCb           *cell,
RgSchCmnDlRbAllocInfo *alloc,
RgSchDlSf             *dlSf,
RgSchUeCb             *ue,
RgSchDlLcCb           *dlLc,
Bool                  isSrb,
U32                   *allocBytes
)
#else
PRIVATE S16 rgSCHMaxciDlLcSchd(cell, alloc, dlSf, ue, dlLc, isSrb, allocBytes)
RgSchCellCb           *cell;
RgSchCmnDlRbAllocInfo *alloc;
RgSchDlSf             *dlSf;
RgSchUeCb             *ue;
RgSchDlLcCb           *dlLc;
Bool                  isSrb;
U32                   *allocBytes;
#endif
{
   RgSchCmnDlUe       *cmnUe = RG_SCH_CMN_GET_DL_UE(ue, cell);
   RgSchMaxciDlUe     *maxciDlUe = RG_SCH_MAXCIDL_GET_UE(ue, cell);
   RgSchMaxciDlLc     *maxciDlLc = RG_SCH_MAXCIDL_GET_LC(ue,dlLc,cell);
   RgSchDlHqProcCb    *proc;
   RgSchCmnDlHqProc   *cmnDlProc;
   U32                bytes;
#ifdef LTEMAC_SPS
   CmLteTimingInfo    schdTime;
#endif
   S16                ret = ROK;

   TRC2(rgSCHMaxciDlLcSchd);

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
      proc = (RgSchDlHqProcCb *)cmnUe->proc;
      /* Don't do anything if UE already scheduled for retx */
      if ((RG_SCH_CMN_PROC_SLCTD_FOR_RETX(proc)))
      {
         RETVALUE(RFAILED);
      }
   }
   else
   {
      if ((proc = rgSCHMaxciDlGetAvlProc(cell, ue, isSrb)) == NULLP)
      {
         RETVALUE(RFAILED);
      }
   }
   cmnDlProc = (RgSchCmnDlHqProc *)proc->sch;
   RG_SCH_CMN_DL_GET_HDR_EST(dlLc, maxciDlLc->hdrSz);
   maxciDlLc->reqBytes = *allocBytes;
   maxciDlLc->reqBytes += maxciDlLc->hdrSz;
   ret = rgSCHCmnDlAllocTxRb(cell, dlSf, ue, maxciDlLc->reqBytes, &bytes, proc,
            alloc);
      *allocBytes = bytes;
   if ((ret != ROK) || (bytes == 0))
   {
      if (cmnDlProc->totBytes == 0)
      {
         RgSchMaxciDlHqProc   *maxciProc = RG_SCH_MAXCIDL_GET_HQP(proc);
         maxciProc->isSrb = FALSE;
         rgSCHMaxciDlRlsHqP(proc);
         /* Added the handling for removing
          * UE from txHqPLst and resetting the outStndAlloc.*/
         if(proc->reqLnk.node != (PTR)NULLP)
         {
            cmLListDelFrm(&alloc->dedAlloc.txHqPLst, &proc->reqLnk);
            proc->reqLnk.node = (PTR)NULLP;
         }
         /*Re-set the outstanding alloc information.*/
         cmnUe->outStndAlloc = 0;
         /* ccpu00126519: proc should be set to NULLP in UE's DL scratch pad info as well. */
         cmnUe->proc = NULLP;
      }
      /* Return the value returned by DlAllocTxRb */ 
      RETVALUE(ret);
   }
   cmLListAdd2Tail(&maxciDlUe->schdLcs, &maxciDlLc->schdLnk);
   cmnUe->proc = proc;
   cmnDlProc->totBytes += bytes;
   /* This is moved to cmn Scheduler */ 
   /* rgSCHCmnDlRbInfoAddUeTx(alloc, ue); */
   RETVALUE(ROK);
}
/* Correcting NDI manipulation of Harq */
/***********************************************************
 *
 *     Func : rgSCHMaxciDlRlsHqP
 *        
 *     Desc : Toggles the NDI and releases the harq proc.
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlRlsHqP
(
RgSchDlHqProcCb      *hqProc
)
#else
PRIVATE Void rgSCHMaxciDlRlsHqP(hqProc)
RgSchDlHqProcCb      *hqProc;
#endif
{
   rgSCHDhmRlsHqProc(hqProc);

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}
/***********************************************************
 *
 *     Func : rgSCHMaxciDlDelUeFrmTxSrbLst
 *        
 *     Desc : Deletes UE from transmitting SRB list
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlDelUeFrmTxSrbLst
(
RgSchMaxciDlUe *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlDelUeFrmTxSrbLst(maxciDlUe)
RgSchMaxciDlUe *maxciDlUe;
#endif
{
   TRC2(rgSCHMaxciDlDelUeFrmTxSrbLst);
   cmLListDelFrm(maxciDlUe->txSrbLstPtr, &(maxciDlUe->srbLnk));
   maxciDlUe->txSrbLstPtr = NULLP;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}


/***********************************************************
 *
 *     Func : rgSCHMaxciDlDelUeFrmTxUeLst
 *        
 *     Desc : Deletes UE from transmitting UE priority list
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlDelUeFrmTxUeLst
(
RgSchMaxciDlUe *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlDelUeFrmTxUeLst(maxciDlUe)
RgSchMaxciDlUe *maxciDlUe;
#endif
{
   TRC2(rgSCHMaxciDlDelUeFrmTxUeLst);
   cmLListDelFrm(maxciDlUe->txUeLstPtr, &(maxciDlUe->prioLnk));
   maxciDlUe->txUeLstPtr = NULLP;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlDelUeFrmRetxLst
 *        
 *     Desc : Deletes UE from retransmiting list
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlDelUeFrmRetxLst
(
RgSchMaxciDlUe *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlDelUeFrmRetxLst(maxciDlUe)
RgSchMaxciDlUe *maxciDlUe;
#endif
{
   TRC2(rgSCHMaxciDlDelUeFrmRetxLst);

   cmLListDelFrm(maxciDlUe->retxLstPtr, &(maxciDlUe->retxLnk));
   maxciDlUe->retxLstPtr = NULLP;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlAddUeToRetxUeLst
 *        
 *     Desc : Adds Ue to the retx list
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlAddUeToRetxUeLst
(
RgSchMaxciDlCell *maxciDlCell,
RgSchMaxciDlUe   *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlAddUeToRetxUeLst(maxciDlCell, maxciDlUe)
RgSchMaxciDlCell *maxciDlCell;
RgSchMaxciDlUe   *maxciDlUe;
#endif
{
   CmLListCp     *retxLst = &maxciDlCell->retxQueues.ueLst[maxciDlUe->priorLvl];
   TRC2(rgSCHMaxciDlAddUeToRetxUeLst);

   cmLListAdd2Tail(retxLst, &(maxciDlUe->retxLnk));
   maxciDlUe->retxLstPtr = retxLst;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlAddUeToRetxSrbLst
 *        
 *     Desc : Adds Ue to the retx list
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlAddUeToRetxSrbLst
(
RgSchMaxciDlCell *maxciDlCell,
RgSchMaxciDlUe   *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlAddUeToRetxSrbLst(maxciDlCell, maxciDlUe)
RgSchMaxciDlCell *maxciDlCell;
RgSchMaxciDlUe   *maxciDlUe;
#endif
{
   CmLListCp        *retxLst = &(maxciDlCell->retxQueues.srbLst);
   TRC2(rgSCHMaxciDlAddUeToRetxSrbLst);

   cmLListAdd2Tail(retxLst, &(maxciDlUe->retxLnk));
   maxciDlUe->retxLstPtr = retxLst;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlAddUeToTxUeLst
 *        
 *     Desc : Adds UE to transmitting UE priority list
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File ::
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlAddUeToTxUeLst
(
RgSchMaxciDlCell *maxciDlCell,
RgSchMaxciDlUe   *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlAddUeToTxUeLst(maxciDlCell, maxciDlUe)
RgSchMaxciDlCell *maxciDlCell;
RgSchMaxciDlUe   *maxciDlUe;
#endif
{
   CmLListCp     *txUeLst = &maxciDlCell->txQueues.ueLst[maxciDlUe->priorLvl];
   TRC2(rgSCHMaxciDlAddUeToTxUeLst);

   cmLListAdd2Tail(txUeLst, &(maxciDlUe->prioLnk));
   maxciDlUe->txUeLstPtr = txUeLst;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlAddUeToTxSrbLst
 *        
 *     Desc : Adds UE to transmitting SRB list
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlAddUeToTxSrbLst
(
RgSchMaxciDlCell *maxciDlCell,
RgSchMaxciDlUe   *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlAddUeToTxSrbLst(maxciDlCell, maxciDlUe)
RgSchMaxciDlCell *maxciDlCell;
RgSchMaxciDlUe   *maxciDlUe;
#endif
{
   CmLListCp        *txSrbLst = &(maxciDlCell->txQueues.srbLst); 
   TRC2(rgSCHMaxciDlAddUeToTxSrbLst);

   cmLListAdd2Tail(txSrbLst, &(maxciDlUe->srbLnk));
   maxciDlUe->txSrbLstPtr = txSrbLst;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlDelLcFrmUe
 *        
 *     Desc : Deletes logical channel from the UE
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlDelLcFrmUe
(
RgSchMaxciDlLc *maxciDlLc
)
#else
PRIVATE Void rgSCHMaxciDlDelLcFrmUe(maxciDlLc)
RgSchMaxciDlLc *maxciDlLc;
#endif
{
   TRC2(rgSCHMaxciDlDelLcFrmUe);

   cmLListDelFrm(maxciDlLc->lcLst, &(maxciDlLc->schdLnk));
   maxciDlLc->lcLst = NULLP;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlAddLcToUe
 *        
 *     Desc : Adds srb/gbr/non-gbr logical channel to the UE's
 *             list of srb/gbr/non-gbr services.
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlAddLcToUe
(
RgSchMaxciDlLc *maxciDlLc,
CmLListCp      *lcLst
)
#else
PRIVATE Void rgSCHMaxciDlAddLcToUe(maxciDlLc, lcLst)
RgSchMaxciDlLc *maxciDlLc;
CmLListCp      *lcLst;
#endif
{
   TRC2(rgSCHMaxciDlAddLcToUe);
   cmLListAdd2Tail(lcLst, &(maxciDlLc->schdLnk));
   maxciDlLc->lcLst = lcLst;

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlAddSrbHqProcToUe
 *        
 *     Desc : Adds srb harq procs to the UE's list of srb re-tx harq procs.
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlAddSrbHqProcToUe
(
RgSchMaxciDlHqProc *maxciDlHqProc, 
RgSchMaxciDlUe     *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlAddSrbHqProcToUe(maxciDlHqProc, maxciDlUe)
RgSchMaxciDlHqProc *maxciDlHqProc;
RgSchMaxciDlUe     *maxciDlUe;
#endif
{
   TRC2(rgSCHMaxciDlAddSrbHqProcToUe);

   cmLListAdd2Tail(&maxciDlUe->retxSrbProcs, &(maxciDlHqProc->ueLnk));

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlAddDrbHqProcToUe
 *        
 *     Desc : Adds drb harq procs to the UE's list of drb re-tx harq procs.
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlAddDrbHqProcToUe
(
RgSchMaxciDlHqProc *maxciDlHqProc, 
RgSchMaxciDlUe     *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlAddDrbHqProcToUe(maxciDlHqProc, maxciDlUe)
RgSchMaxciDlHqProc *maxciDlHqProc;
RgSchMaxciDlUe     *maxciDlUe;
#endif
{
   TRC2(rgSCHMaxciDlAddDrbHqProcToUe);

   cmLListAdd2Tail(&maxciDlUe->retxDrbProcs, &(maxciDlHqProc->ueLnk));

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlDelDrbHqProcFrmUe
 *        
 *     Desc : Deletes drb harq procs to the UE's list of srb re-tx harq procs.
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlDelDrbHqProcFrmUe
(
RgSchMaxciDlHqProc *maxciDlHqProc, 
RgSchMaxciDlUe     *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlDelDrbHqProcFrmUe(maxciDlHqProc, maxciDlUe)
RgSchMaxciDlHqProc *maxciDlHqProc;
RgSchMaxciDlUe     *maxciDlUe;
#endif
{
   TRC2(rgSCHMaxciDlDelDrbHqProcFrmUe);

   cmLListDelFrm(&maxciDlUe->retxDrbProcs, &(maxciDlHqProc->ueLnk));

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}

/***********************************************************
 *
 *     Func : rgSCHMaxciDlDelSrbHqProcFrmUe
 *        
 *     Desc : Deltes srb harq procs to the UE's list of srb re-tx harq procs.
 *
 *     Ret  : Void
 *
 *     Notes: 
 *
 *     File : 
 *
 **********************************************************/
#ifdef ANSI
PRIVATE Void rgSCHMaxciDlDelSrbHqProcFrmUe
(
RgSchMaxciDlHqProc *maxciDlHqProc, 
RgSchMaxciDlUe     *maxciDlUe
)
#else
PRIVATE Void rgSCHMaxciDlDelSrbHqProcFrmUe(maxciDlHqProc, maxciDlUe)
RgSchMaxciDlHqProc *maxciDlHqProc;
RgSchMaxciDlUe     *maxciDlUe;
#endif
{
   TRC2(rgSCHMaxciDlDelSrbHqProcFrmUe);

   cmLListDelFrm(&maxciDlUe->retxSrbProcs, &(maxciDlHqProc->ueLnk));

  /* Stack Crash problem for TRACE5 changes. Added the return below */
  RETVOID;

}
/**
 * @brief UE Lc Config for RR 
 *
 * @details
 *
 *     Function : rgSCHMaxciUlLchCfg
 *
 *     Processing Steps:  Dummy function
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgrLchCfg        *cfg 
 *  @param[in]  RgSchErrInfo     *err 
 *  @return  S16
 *      -# ROK
 **/
PUBLIC S16 rgSCHMaxciUlLchCfg 
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrLchCfg        *cfg,
RgSchErrInfo     *err
)
{
   RETVALUE(ROK);
}
/**
 * @brief UE Lc Reconfig for RR 
 *
 * @details
 *
 *     Function : rgSCHMaxciUlLchRecfg
 *
 *     Processing Steps:  Dummy function
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgrLchRecfg      *recfg 
 *  @param[in]  RgSchErrInfo     *err 
 *  @return  S16
 *      -# ROK
 **/
PUBLIC S16 rgSCHMaxciUlLchRecfg 
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrLchRecfg      *recfg,
RgSchErrInfo     *err
)
{
   RETVALUE(ROK);
}
/**
 * @brief LC deletion for PFS
 *
 * @details
 *
 *     Function : rgSCHMaxciUlLchDel
 *
 *     Processing Steps: Dummy function
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  CmLteLcId        lcId
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciUlLchDel
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
CmLteLcId        lcId,
U8               lcgId
)
#else
PUBLIC S16 rgSCHRrUlLchDel(cell, ue, lcId, lcgId)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
CmLteLcId        lcId;
U8               lcgId;
#endif
{
  RETVALUE (ROK);
}


/* 
 * UPLINK PROCESSING 
 */

/**
 * @brief This function registers MAX C/I Uplink APIs that would be 
 * called by common scheduler.
 *
 * @details
 *
 *     Function: rgSCHMaxciUlInit
 *
 *     Processing Steps:
 *     - Assigns the various callback APIs
 *  @params[in, out] RgUlSchdApis *apis pointer to the set of APIs that are to
 *  be intialized in this function.
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlInit
(
RgUlSchdApis         *apis
)
#else
PUBLIC Void rgSCHMaxciUlInit(apis)
RgUlSchdApis         *apis;
#endif
{
   TRC2(rgSCHMaxciUlInit);

   apis->rgSCHRgrUlCellCfg   = rgSCHMaxciUlCellCfg;
   apis->rgSCHRgrUlCellRecfg = rgSCHMaxciUlCellRecfg; 
   apis->rgSCHFreeUlCell     = rgSCHMaxciUlCellDel;
   apis->rgSCHRgrUlUeCfg     = rgSCHMaxciUlUeCfg;
   apis->rgSCHRgrUlUeRecfg   = rgSCHMaxciUlUeRecfg;
   apis->rgSCHFreeUlUe       = rgSCHMaxciUlUeDel;
   apis->rgSCHRgrUlLcgCfg    = rgSCHMaxciUlLcgCfg;
   apis->rgSCHRgrUlLcgRecfg  = rgSCHMaxciUlLcgRecfg;
   apis->rgSCHFreeUlLcg      = rgSCHMaxciUlLcgDel;
   apis->rgSCHUlSched        = rgSCHMaxciUlSched;
   apis->rgSCHUpdBsrShort    = rgSCHMaxciUlUpdBsrShort;
   apis->rgSCHUpdBsrTrunc    = rgSCHMaxciUlUpdBsrTrunc;
   apis->rgSCHUpdBsrLong     = rgSCHMaxciUlUpdBsrLong;
   apis->rgSCHContResUlGrant = rgSCHMaxciUlContResReq;
   apis->rgSCHSrRcvd         = rgSCHMaxciUlSrInd;
   apis->rgSCHUlCqiInd       = rgSCHMaxciUlCqiInd;
   apis->rgSCHRgrUlLcgUpd    = rgSCHMaxciUlLcgUpd;
   apis->rgSCHUlUeRefresh    = rgSCHMaxciUlUeRefresh;
   apis->rgSCHUlAllocFnlz    = rgSCHMaxciUlAllocFnlz;
   apis->rgSCHUlInactvtUes   = rgSCHMaxciUlInactvLstInd;
   apis->rgSCHUlActvtUe      = rgSCHMaxciUlActvtUeInd;
   apis->rgSCHUlUeReset      = rgSCHMaxciUlUeReset;
   apis->rgSCHRgrUlLcCfg     = rgSCHMaxciUlLchCfg;
   apis->rgSCHRgrUlLcRecfg   = rgSCHMaxciUlLchRecfg;
   apis->rgSCHRgrUlLchDel    = rgSCHMaxciUlLchDel;

   RETVOID;
}

 
/**
 * @brief Cell configuration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlCellCfg
 *
 *     Processing Steps:
 *      - Create the maxciCell info within passed SchCell
 *      - Initialized the priority Queues 
 *
 *  @param[in]  RgSchCellCb         *cell cellCb
 *  @param[in]  RgrCellCfg          *cfg  configuration structure
 *  @param[out]  RgrSchErrInfo      *err Error information
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciUlCellCfg
(
RgSchCellCb          *cell,
RgrCellCfg           *cfg,
RgSchErrInfo         *err
)
#else
PUBLIC S16 rgSCHMaxciUlCellCfg (cell, cfg, err)
RgSchCellCb          *cell;
RgrCellCfg           *cfg;
RgSchErrInfo         *err;
#endif
{
   RgSchCmnUlCell       *ulCell = RG_SCH_CMN_GET_UL_CELL(cell);
   RgSchMaxciUlCellCb   *maxciUlCell;
   U8                   cqiIdx;

   TRC2(rgSCHMaxciUlCellCfg);


   /* Allocate MAX CI specific UL CellCB */
   if ((rgSCHUtlAllocSBuf(cell->instIdx,
            (Data**)&ulCell->schSpfc, (sizeof(RgSchMaxciUlCellCb)))) != ROK)
   {
      RLOG_ARG0(L_ERROR,DBG_CELLID,cell->cellId,
               "Memory allocation FAILED for MAX-CI UL cell");
      err->errCause = RGSCHERR_MAXCI_MEMERR;
      RETVALUE(RFAILED);
   }

   maxciUlCell = RG_SCH_MAXCIUL_GET_CELL(cell);

   /* Initialize Priority Queues */
   cmLListInit(&(maxciUlCell->contResLst));
   cmLListInit(&(maxciUlCell->srbLst));
   for (cqiIdx = 0; cqiIdx < (RG_SCH_CMN_UL_MAX_CQI - 1); cqiIdx++)
   {
      cmLListInit(&(maxciUlCell->ueLst[cqiIdx]));
   }
   RETVALUE(ROK);
}

/**
 * @brief Cell reconfiguration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlCellRecfg
 *
 *     Processing Steps:
 *      - None
 *
 *  @param[in]  RgSchCellCb       *cell  cell control block
 *  @param[in]  RgrCellRecfg      *recfg reconfiguration structure.
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciUlCellRecfg
(
RgSchCellCb     *cell,
RgrCellRecfg    *recfg,
RgSchErrInfo    *err
)
#else
PUBLIC S16 rgSCHMaxciUlCellRecfg(cell, recfg, err)
RgSchCellCb     *cell;
RgrCellRecfg    *recfg;
RgSchErrInfo    *err;
#endif
{
   TRC2(rgSCHMaxciUlCellRecfg);

   RETVALUE(ROK);
}


/**
 * @brief Cell deletion for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlCellDel
 *
 *     Processing Steps:
 *      - Free Max C/I related information per cell.
 *      - [ Nothing else needs to be done.
 *        Common modules would take care of deleting
 *        each UE in the cell, during which time Max C/I
 *        shall be called for UE deletion.]
 *
 *  @param[in]  RgSchCellCb       *cell  cell control block
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlCellDel
(
RgSchCellCb       *cell
)
#else
PUBLIC Void rgSCHMaxciUlCellDel(cell)
RgSchCellCb       *cell;
#endif
{
   RgSchCmnCell *schCmnCell = (RgSchCmnCell *)(cell->sc.sch);

   TRC2(rgSCHMaxciUlCellDel);

   if (schCmnCell->ul.schSpfc == NULLP)
   {
      RETVOID;
   }
    /* ccpu00117052 - MOD - Passing double pointer
    for proper NULLP assignment*/
   rgSCHUtlFreeSBuf(cell->instIdx,
      (Data**)(&(schCmnCell->ul.schSpfc)), (sizeof(RgSchMaxciUlCellCb)));
   RETVOID;
}

/**
 * @brief UE configuration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlUeCfg
 *
 *     Processing Steps:
 *      - Create the maxciUe info
 *      - Validate and update configured values
 *      - [UE specific refresh timer actions to happen
 *        as part of common modules]
 *
 *  @param[in]  RgrSchCellCb     *cell  cell control block
 *  @param[in]  RgSchUeCb        *ue    UE control block
 *  @param[in]  RgrUeCfg         *cfg   UE configuration structure.
 *  @param[out]  RgrSchErrInfo    *err  Error information.
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciUlUeCfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrUeCfg         *cfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHMaxciUlUeCfg (cell, ue, cfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgrUeCfg         *cfg;
RgSchErrInfo     *err;
#endif
{
   RgSchCmnUlUe      *cmnUlUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchMaxciUlUe    *maxciUe;

   TRC2(rgSCHMaxciUlUeCfg);

   /* Allocate MAX CI specific UL UECB */
   if (rgSCHUtlAllocSBuf(cell->instIdx,
            (Data**)&cmnUlUe->schSpfc, (sizeof(RgSchMaxciUlUe))) != ROK)
   {
      RLOG_ARG1(L_ERROR,DBG_CELLID,cell->cellId,
               "Memory allocation FAILED for MAX-CI UL UE CB Cell CRNTI:%d", 
               ue->ueId);
      err->errCause = RGSCHERR_MAXCI_MEMERR;
      RETVALUE(RFAILED);
   }

   /* Rest of the values would be zeroed out */
   maxciUe = (RgSchMaxciUlUe *)(cmnUlUe->schSpfc);
   maxciUe->prioLnk.node = (PTR)ue;
   maxciUe->crntQ = NULLP;
   RETVALUE(ROK);
}

/**
 * @brief UE reconfiguration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlUeRecfg
 *
 *     Processing Steps:
 *       - None
 *
 *  @param[in]   RgSchCellCb      *cell   cell control block
 *  @param[in]   RgSchUeCb        *ue     UE control block
 *  @param[in]   RgrUeRecfg       *recfg  Re-configuration structure.
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciUlUeRecfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrUeRecfg       *recfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHMaxciUlUeRecfg(cell, ue, recfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgrUeRecfg       *recfg;
RgSchErrInfo     *err;
#endif
{
   TRC2(rgSCHMaxciUlUeRecfg);

   RETVALUE(ROK);
}

/**
 * @brief UE delete for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlUeDel
 *     - For UL
 *       - Remove UE from new tx queues (SRB and/or
 *         CQI UE queues)
 *     - Free Max C/I UE info
 *
 *  @param[in]  RgSchCellCb       *cell   cell control block
 *  @param[in]  RgSchUeCb         *ue     UE control block
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlUeDel
(
RgSchCellCb      *cell,
RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHMaxciUlUeDel(cell, ue)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
#endif
{
   CmLListCp            *priorQ;
   RgSchCmnUlUe         *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);

   TRC2(rgSCHMaxciUlUeDel);

   if (maxciUe == NULLP)
   {
      RETVOID;
   }
   if (maxciUe->crntQ)
   {
      /* Remove from the queue */
      priorQ = maxciUe->crntQ;
      cmLListDelFrm(priorQ, &(maxciUe->prioLnk));
   }

   /* Free the MAX CI UE control block */
    /* ccpu00117052 - MOD - Passing double pointer
    for proper NULLP assignment*/
   rgSCHUtlFreeSBuf(cell->instIdx, (Data**)(&(cmnUe->schSpfc)), 
         sizeof(RgSchMaxciUlUe));
   RETVOID;
}

/**
 * @brief LCG configuration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlLcgCfg
 *
 *     Processing Steps:
 *       - None
 *
 *  @param[in]  RgrSchCellCb     *cell   cell control block
 *  @param[in]  RgSchUeCb        *ue     UE control block
 *  @param[in]  RgSchLcgCb       *ulLcg  LCG control block
 *  @param[in]  RgrLcgCfg        *cfg    LCG configuration structure.
 *  @param[out]  RgrSchErrInfo    *err    Error information
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciUlLcgCfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchLcgCb       *ulLcg,
RgrLcgCfg        *cfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHMaxciUlLcgCfg(cell, ue, ulLcg, cfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchLcgCb       *ulLcg;
RgrLcgCfg        *cfg;
RgSchErrInfo     *err;
#endif
{
   TRC2(rgSCHMaxciUlLcgCfg);

   RETVALUE(ROK);
}

/**
 * @brief LCG configuration for Max C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlLcgRecfg
 *
 *     Processing Steps:
 *       - None
 *
 *  @param[in]  RgrSchCellCb     *cell    cell control block
 *  @param[in]  RgSchUeCb        *ue      UE control block
 *  @param[in]  RgSchLcgCb       *ulLcg   LCG control block
 *  @param[in]  RgrLcgRecfg      *cfg     Re configuration structure
 *  @param[out]  RgrSchErrInfo    *err     Error information
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciUlLcgRecfg
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchLcgCb       *ulLcg,
RgrLcgRecfg      *cfg,
RgSchErrInfo     *err
)
#else
PUBLIC S16 rgSCHMaxciUlLcgRecfg(cell, ue, ulLcg, cfg, err)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchLcgCb       *ulLcg;
RgrLcgRecfg      *cfg;
RgSchErrInfo     *err;
#endif
{
   TRC2(rgSCHMaxciUlLcgRecfg);

   RETVALUE(ROK);
}


/**
 * @brief Ul LCG deletion for MAX C/I
 *
 * @details
 *
 *     Function : rgSCHMaxciUlLcgDel
 *
 *     Processing Steps:
 *     - None
 *
 *  @param[in]  RgrSchCellCb     *cell
 *  @param[in]  RgSchUeCb        *ue
 *  @param[in]  RgSchUlLcgCb     *ulLcg
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlLcgDel
(
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgSchLcgCb       *ulLcg
)
#else
PUBLIC Void rgSCHMaxciUlLcgDel (cell, ue, ulLcg)
RgSchCellCb      *cell;
RgSchUeCb        *ue;
RgSchLcgCb       *ulLcg;
#endif
{
   TRC2(rgSCHMaxciUlLcgDel);

   RETVOID;
}


/**
 * @brief Uplink scheduling function
 *
 * @details
 *
 *     Function : rgSCHMaxciUlSched
 *
 *     Processing Steps:
 *     - First Allocated for Contention resolution
 *     - Allocate for SRBs
 *     - Allocate for UE Transmission queueus.
 *
 *  @param[in]  RgSchCellCb              *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo    *alloc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlSched
(
RgSchCellCb             *cell,
RgSchCmnUlRbAllocInfo   *alloc
)
#else
PUBLIC Void rgSCHMaxciUlSched(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
#endif
{
   RgSchCmnUlCell  *cellUl = RG_SCH_CMN_GET_UL_CELL(cell);
   U8               remUe = cellUl->maxUeNewTxPerTti;

   TRC2(rgSCHMaxciUlSched);

   rgSCHMaxciUlUtlSchdForContRes (cell, alloc, &remUe);
   rgSCHMaxciUlUtlSchdForSrb (cell, alloc, &remUe);
   rgSCHMaxciUlUtlSchdForTx (cell, alloc, &remUe);
   RETVOID;
}
/** @brief This function performs scheduling for Contention resolution.
 *
 * @details
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Loops through the list of UEs present in the maxciCell->contResLst
 *            - While total number of UEs dont exceed the maxUeNewTxPerTti
 *               - Add the UE to the list of scheduled UEs in the common alloc
 *               struct.
 *
 *         - return
 *
 * @param[in]  RgSchCellCb             *cell
 * @param[in, out]  RgSchCmnUlRbAllocInfo   *alloc
 * @param[int, out]  U8                      *remUe The CAP on maximum number of UEs for
 * Transmission in a single TTI. 
 * @return Void
 */
#ifdef ANSI
PRIVATE Void rgSCHMaxciUlUtlSchdForContRes
(
 RgSchCellCb               *cell,
 RgSchCmnUlRbAllocInfo     *alloc,
 U8                        *remUe
)
#else
PRIVATE Void rgSCHMaxciUlUtlSchdForContRes (cell, alloc, remUe)
 RgSchCellCb               *cell;
 RgSchCmnUlRbAllocInfo     *alloc;
 U8                        *remUe;
#endif
{
   CmLList              *node;
   RgSchUeCb            *ue;
   RgSchCmnUlUe         *cmnUe;
   RgSchMaxciUlCellCb   *maxciCell = RG_SCH_MAXCIUL_GET_CELL(cell);
#ifdef LTEMAC_HDFDD
   Bool                ulAllowed = FALSE;
#endif

   TRC2(rgSCHMaxciUlUtlSchdForContRes);

   node = maxciCell->contResLst.first;
   while (node && *remUe)
   {
      ue  = (RgSchUeCb*)node->node;
#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddChkUlAllow (cell, ue, &ulAllowed);
         if (ulAllowed == FALSE)
         {
            continue;
         }
      }
#endif
      cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);

      node = node->next;
      cmnUe->alloc.reqBytes = RG_SCH_CMN_MAX_UL_CONTRES_GRNT;
      rgSCHCmnUlAdd2CntResLst(alloc, ue);
      --(*remUe);
   }
   RETVOID;
} /* end of */ 

/** @brief This function allocates for UEs present in the SRB queue
 *
 * @details
 *
 *     Function: rgSCHMaxciUlUtlSchdForSrb
 *
 *         Processing steps:
 *         - Loops through the list of UEs present in the maxciCell->srbLst
 *            - While total number of UEs dont exceed the maxUeNewTxPerTti
 *               - If the UE hasnt already been scheduled
 *                  - Add the UE to the list of scheduled UEs in the common 
 *                  alloc struct.
 *
 *
 * @param[in]       RgSchCellCb             *cell
 * @param[in, out]  RgSchCmnUlRbAllocInfo   *alloc
 * @param[in, out]  U8                      *remUe
 * @return Void
 */
#ifdef ANSI
PRIVATE Void rgSCHMaxciUlUtlSchdForSrb
(
 RgSchCellCb            *cell,
 RgSchCmnUlRbAllocInfo  *alloc,
 U8                     *remUe
)
#else
PRIVATE Void rgSCHMaxciUlUtlSchdForSrb (cell, alloc, remUe)
 RgSchCellCb            *cell;
 RgSchCmnUlRbAllocInfo  *alloc;
 U8                     *remUe;
#endif
{
   RgSchUeCb            *ue;
   RgSchCmnUlUe         *cmnUe;
   RgSchMaxciUlCellCb   *maxciCell = RG_SCH_MAXCIUL_GET_CELL(cell);
   CmLList              *node;
#ifdef LTEMAC_HDFDD
   Bool                ulAllowed = FALSE;
#endif

   TRC2(rgSCHMaxciUlUtlSchdForSrb);

   node = maxciCell->srbLst.first;
   while (node && *remUe)
   {
      ue = (RgSchUeCb*)node->node;
#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddChkUlAllow (cell, ue, &ulAllowed);
         if (ulAllowed == FALSE)
         {
            continue;
         }
      }
#endif
#ifdef LTEMAC_SPS
      if (RG_SCH_CMN_IS_UL_UE_RETX(ue, cell) || RG_SCH_CMN_IS_SPS_SCHD(ue, cell))
#else
      if (RG_SCH_CMN_IS_UL_UE_RETX(ue, cell))
#endif
      {
         /* Already allocated for ReTx */
         node = node->next;
         continue;
      }
      cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
      cmnUe->alloc.reqBytes = ue->ul.effBsr;
      rgSCHCmnUlAdd2UeLst(cell, alloc, ue);
      node = node->next;
      --(*remUe);
   }   
   RETVOID;
} /* end of rgSCHMaxciUlUtlSchdForSrb */ 

/** @brief This function allocates for UEs present in the UE list
 *
 * @details
 *
 *     Function: rgSCHMaxciUlUtlSchdForTx
 *
 *         Processing steps:
 *         - Loop through the CQI queues in decending order indexing by cqiLvl
 *            - Loops through the list of UEs present in the
 *               maxciCell->cqiLst[cqiLvl]
 *            - While total number of UEs dont exceed the maxUeNewTxPerTti
 *               - If the UE hasnt already been scheduled
 *                  - Add the UE to the list of scheduled UEs in the common alloc
 *                  struct.
 *
 * @param[in]       RgSchCellCb             *cell
 * @param[in, out]  RgSchCmnUlRbAllocInfo   *alloc
 * @param[in, out]  U8                      *remUe tracks the remaining number of UEs.
 * @return Void
 */
#ifdef ANSI
PRIVATE Void rgSCHMaxciUlUtlSchdForTx
(
 RgSchCellCb            *cell,
 RgSchCmnUlRbAllocInfo  *alloc,
 U8                     *remUe
)
#else
PRIVATE Void rgSCHMaxciUlUtlSchdForTx (cell, alloc, remUe)
 RgSchCellCb            *cell;
 RgSchCmnUlRbAllocInfo  *alloc;
 U8                     *remUe;
#endif
{
   RgSchUeCb            *ue;
   RgSchCmnUlUe         *cmnUe;
   RgSchMaxciUlUe       *maxciUe;
   RgSchMaxciUlCellCb   *maxciCell = RG_SCH_MAXCIUL_GET_CELL(cell);
   CmLList              *node;
   S8                   cqiIdx;
   CmLListCp            *queue;
#ifdef LTEMAC_HDFDD
   Bool                ulAllowed = FALSE;
#endif

   TRC2(rgSCHMaxciUlUtlSchdForTx);

   for (cqiIdx = (RG_SCH_CMN_UL_MAX_CQI - 2); 
         ((cqiIdx >= 0 ) && *remUe); cqiIdx--)
   {
      queue = &(maxciCell->ueLst[(U8)cqiIdx]);
      node = queue->first;
      while (node && *remUe)
      {
         ue = (RgSchUeCb*)node->node;
#ifdef LTEMAC_HDFDD
         if (ue->hdFddEnbld)
         {
            rgSCHCmnHdFddChkUlAllow (cell, ue, &ulAllowed);
            if (ulAllowed == FALSE)
            {
               node = node->next;
               continue;
            }
         }
#endif
         /* Check if hqProc is present, if yes then already allocated */
#ifdef LTEMAC_SPS
         if (RG_SCH_CMN_IS_UL_UE_RETX(ue, cell) || RG_SCH_CMN_IS_SPS_SCHD(ue, cell))
#else
         if (RG_SCH_CMN_IS_UL_UE_RETX(ue, cell))
#endif
         {
            /* Already allocated for ReTx */
            node = node->next;
            continue;
         }
         cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
         maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
         /* If SR is received allocate accordingly */
         if (maxciUe->srRcvd)
         {
            cmnUe->alloc.reqBytes = ue->ul.effBsr ? 
               ue->ul.effBsr: RG_SCH_MAXCI_SR_BYTES;
         }
         else
         {
            cmnUe->alloc.reqBytes = ue->ul.effBsr;
         }
         rgSCHCmnUlAdd2UeLst(cell, alloc, ue);
         node = node->next;
         --(*remUe);
      } /* End of while loop */   
   } /* end of For loop */
   RETVOID;
} /* end of rgSCHMaxciUlUtlSchdForTx */ 



/** @brief This function processes a short BSR received from the UE.
 *
 * @details
 *
 *     Function: rgSCHMaxciUlUpdBsrShort
 *
 *         Processing steps:
 *         - If the UE is inactive in Uplink then return.
 *         - Call the rgSCHMaxciUlUtlPosUe function to add or reposition the UE in the
 *         priority queues.
 *
 * @param[in]  RgSchCellCb    *cell
 * @param[in]  RgSchUeCb      *ue
 * @param[in]  RgSchLcgCb     *lcg
 * @param[in]  U8             bsr
 * @return Void
 */
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlUpdBsrShort
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue,
 RgSchLcgCb       *lcg,
 U8               bsr
)
#else
PUBLIC Void rgSCHMaxciUlUpdBsrShort (cell, ue, lcg, bsr)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
 RgSchLcgCb       *lcg;
 U8               bsr;
#endif
{
   RgSchCmnUlUe         *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
   RgSchCmnLcg          *lcg0 = RG_SCH_CMN_GET_UL_LCG(&ue->ul.lcgArr[0]);

   TRC2(rgSCHMaxciUlUpdBsrShort);


   /* This UE could be inactive for Uplink due to Measurement gap 
    * or ack nack repetition. 
    */
   if (ue->ul.ulInactvMask)
   {
      RETVOID;
   }
   rgSCHMaxciUlUtlPosUe(cell, ue, cmnUe, maxciUe, lcg0);
   RETVOID;
} /* end of rgSCHMaxciUlUpdBsrShort */ 

/** @brief This function processes a truncated BSR received from the UE.
 *
 * @details
 *
 *     Function: rgSCHMaxciUlUpdBsrTrunc
 *
 *         Processing steps:
 *         - If the UE is inactive in Uplink then return.
 *         - Call the rgSCHMaxciUlUtlPosUe function to 
 *         add or reposition the UE in the priority queues.
 *
 * @param[in]  RgSchCellCb    *cell
 * @param[in]  RgSchUeCb      *ue
 * @param[in]  RgSchLcgCb     *lcg
 * @param[in]  U8             bsr
 * @return Void
 */
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlUpdBsrTrunc
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue,
 RgSchLcgCb       *lcg,
 U8               bsr
)
#else
PUBLIC Void rgSCHMaxciUlUpdBsrTrunc (cell, ue, lcg, bsr)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
 RgSchLcgCb       *lcg;
 U8               bsr;
#endif
{
   RgSchCmnUlUe         *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
   RgSchCmnLcg          *lcg0 = RG_SCH_CMN_GET_UL_LCG(&ue->ul.lcgArr[0]);

   TRC2(rgSCHMaxciUlUpdBsrTrunc);

   /* This UE could be inactive for Uplink due to Measurement gap and ack nack
    * repetition. In such cases just return.
    */
   if (ue->ul.ulInactvMask)
   {
      RETVOID;
   }
   rgSCHMaxciUlUtlPosUe(cell, ue, cmnUe, maxciUe, lcg0);

   RETVOID;
} /* end of rgSCHMaxciUlUpdBsrTrunc */ 

/** @brief This function processes a Long BSR received from the UE.
 *
 * @details
 *
 *     Function: rgSCHMaxciUlUpdBsrLong
 *
 *         Processing steps:
 *         - If the UE is inactive in Uplink then return.
 *         - Call the rgSCHMaxciUlUtlPosUe function to add or reposition 
 *         the UE in the priority queues.
 *
 * @param[in]  RgSchCellCb    *cell
 * @param[in]  RgSchUeCb      *ue
 * @param[in]  U8             bsArr[]
 * @return Void
 */
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlUpdBsrLong
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue,
 U8               *bsArr
)
#else
PUBLIC Void rgSCHMaxciUlUpdBsrLong (cell, ue, bsArr)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
 U8               *bsArr;
#endif
{
   RgSchCmnUlUe         *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
   RgSchCmnLcg          *lcg0 = RG_SCH_CMN_GET_UL_LCG(&ue->ul.lcgArr[0]);

   TRC2(rgSCHMaxciUlUpdBsrLong);

   /* This UE could be inactive for Uplink due to Measurement gap and ack nack
    * repetition. In such cases just return 
    */
   if (ue->ul.ulInactvMask)
   {
      RETVOID;
   }
   rgSCHMaxciUlUtlPosUe(cell, ue, cmnUe, maxciUe, lcg0);

   RETVOID;
} /* end of rgSCHMaxciUlUpdBsrLong */ 



/** @brief This function adds or removes the UE to the appropriate Queue.
 * Called from upd[Short/Long/Trunc]Bsr, SrInd and finalize. 
 *
 * @details rgSCHMaxciUlUtlPosUe
 *
 *     Function: 
 *
 *         Processing steps:
 *         - If the effBsr (updated by common module) != 0
 *            - Add the UE to the correct UE based on 
 *               - if (LCG0 present)
 *                  - queue = srbLst
 *               - else
 *                  - queue = ueLst[ue->ulCqi]
 *               - if (queue != crntQ)
 *                  - Remove the UE from existing List 
 *                  - Add to new queue
 *         - else if (crntQ != NULLP)
 *           - remove from crntQ 
 *      return
 * @param[in]  RgSchCellCb    *cell
 * @param[in]  RgSchUeCb      *ue
 * @return Void
 */
#ifdef ANSI
PRIVATE Void rgSCHMaxciUlUtlPosUe
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue,
 RgSchCmnUlUe     *cmnUe,
 RgSchMaxciUlUe   *maxciUe,
 RgSchCmnLcg      *lcg0
)
#else
PRIVATE Void rgSCHMaxciUlUtlPosUe (cell, ue, cmnUe, maxciUe, lcg0)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
 RgSchCmnUlUe     *cmnUe;
 RgSchMaxciUlUe   *maxciUe;
 RgSchCmnLcg      *lcg0;
#endif
{

   RgSchMaxciUlCellCb   *maxciCell = RG_SCH_MAXCIUL_GET_CELL(cell);
   CmLListCp            *queue;
   U8                   cqi;
   CmLteUeCategory ueCtg = (CmLteUeCategory)(RG_SCH_CMN_GET_UE_CTGY(ue));
   TRC2(rgSCHMaxciUlUtlPosUe);
    
   cqi = rgSCHCmnUlGetCqi(cell, ue, ueCtg);
   /* Add to correct Queue if effBsr or srRcvd */
   if (ue->ul.effBsr || maxciUe->srRcvd)
   {
      if (lcg0->bs)
      {
         queue = &maxciCell->srbLst;
      }
      else
      {
         RGSCH_ARRAY_BOUND_CHECK_WITH_POS_IDX(cell->instIdx, maxciCell->ueLst, (cqi-1));
         queue = &(maxciCell->ueLst[cqi-1]);
      }

      /* Remove from existing Queue */
      if (maxciUe->crntQ)
      {
         cmLListDelFrm(maxciUe->crntQ, &(maxciUe->prioLnk));
      }
      /* Adding to Tail should be sufficient for RR 
       * behaviour between UEs in a single CQI Queue. 
       */
      cmLListAdd2Tail(queue, &maxciUe->prioLnk);
      maxciUe->crntQ = queue;
   }
   else
   { 
      /* Remove from Queue if its present in some queue */
      if (maxciUe->crntQ)
      {
         cmLListDelFrm(maxciUe->crntQ, &(maxciUe->prioLnk));
         maxciUe->crntQ = NULLP;
      }
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
   }
   RETVOID;
} /* end of rgSCHMaxciUlUtlPosUe */ 

/** @brief This function processes SR indication.
 *
 * @details
 *
 *     Function: rgSCHMaxciUlSrInd
 *
 *         Processing steps:
 *         - Set the boolean srRcvd = TRUE this shall be utilized during
 *         scheduling
 *         - If UE is inactive due to measGap or ANRep 
 *             return
 *         - Call the rgSCHMaxciUlUtlPosUe function to 
 *         add/reposition UE in the priority queues.
 *
 *
 * @param[in]  RgSchCellCb    *cell
 * @param[in]  RgSchUeCb      *ue
 * @return Void
 */
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlSrInd
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHMaxciUlSrInd (cell, ue)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
#endif
{
   RgSchCmnUlUe         *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
   RgSchCmnLcg          *lcg0 = RG_SCH_CMN_GET_UL_LCG(&ue->ul.lcgArr[0]);

   TRC2(rgSCHMaxciUlSrInd);

   maxciUe->srRcvd = TRUE;
   /* This UE could be inactive for Uplink due to Measurement gap and ack nack
    * repetition. In such cases just return after updating srRcvd.
    */
   if (ue->ul.ulInactvMask)
   {
      RETVOID;
   }
   /* Call function to reposition the UE */
   rgSCHMaxciUlUtlPosUe(cell, ue, cmnUe, maxciUe, lcg0);
   RETVOID;
} /* end of rgSCHMaxciUlSrInd */ 

/**
 * @brief UL Lcg received data updation
 *
 * @details
 *
 *     Function : rgSCHMaxciUlLcgUpd
 *
 *     Processing Steps:Maxci Does nothing
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @param[in]  RgInfUeDatInd      *datInd
 *  @return  S16
 **/
#ifdef ANSI
PUBLIC S16 rgSCHMaxciUlLcgUpd
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgInfUeDatInd       *datInd
)
#else
PUBLIC S16 rgSCHMaxciUlLcgUpd(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
RgInfUeDatInd       *datInd;
#endif
{

   TRC2(rgSCHMaxciUlLcgUpd);

   RETVALUE(ROK);  
}

/**
 * @brief Uplink CQI report handling
 *
 * @details
 *
 *     Function : rgSCHMaxciUlCqiInd
 *
 *     Processing Steps:
 *     - [Assumed that wideband CQI is always reported]
 *     - If wideband CQI reported is zero, consider this to be
 *       an error and return
 *     - If wideband CQI has changed
 *       - If the UE is not in the SRB Queue or contResLst
 *          - if UE is in one of the 'new transmission' CQI queues
 *             - Delete from existing Queue
 *             - Append UE to queue corresponding to reported CQI
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @param[in]  TfuUlCqiRpt        *ulCqiInfo
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlCqiInd
(
RgSchCellCb         *cell,
RgSchUeCb           *ue,
TfuUlCqiRpt         *ulCqiInfo
)
#else
PUBLIC Void rgSCHMaxciUlCqiInd(cell, ue, ulCqiInfo)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
TfuUlCqiRpt         *ulCqiInfo;
#endif
{
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
   RgSchMaxciUlCellCb   *maxciCell = RG_SCH_MAXCIUL_GET_CELL(cell);
   U8                   cqi;
   CmLteUeCategory ueCtg = (CmLteUeCategory)(RG_SCH_CMN_GET_UE_CTGY(ue));

   TRC2(rgSCHMaxciUlCqiInd);

   /* if reported CQI is 0 */
   if (!ulCqiInfo->wideCqi) 
   {
      RETVOID;
   }

   /* CQI has changed move the UE Amongst Queues. If the UE is present in the
    * SRB list or contResLst then no movement is needed. */
   if ((NULLP != maxciUe->crntQ) && 
         (maxciUe->crntQ != &(maxciCell->srbLst)) &&
         (maxciUe->crntQ != &(maxciCell->contResLst)))
   {
      cmLListDelFrm(maxciUe->crntQ, &(maxciUe->prioLnk));
      cqi = rgSCHCmnUlGetCqi(cell, ue, ueCtg);
      RGSCH_ARRAY_BOUND_CHECK_WITH_POS_IDX(cell->instIdx, maxciCell->ueLst, (cqi-1) );
      cmLListAdd2Tail(&(maxciCell->ueLst[cqi - 1]), 
            &maxciUe->prioLnk);
      maxciUe->crntQ = &(maxciCell->ueLst[cqi - 1]); 
   }
   RETVOID;
}

/**
 * @brief Contention Resolution allocation request
 *
 * @details
 *
 *     Function : rgSCHMaxciUlContResReq
 *
 *     Processing Steps:
 *     - If UE is present in any queue remove it
 *     - Add UE to cell wide contention resolution
 *       queue (contResLst) 
 *
 *  @param[in]  RgSchCellCb        *cell
 *  @param[in]  RgSchUeCb          *ue
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlContResReq
(
RgSchCellCb         *cell,
RgSchUeCb           *ue
)
#else
PUBLIC Void rgSCHMaxciUlContResReq(cell, ue)
RgSchCellCb         *cell;
RgSchUeCb           *ue;
#endif
{
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
   RgSchMaxciUlCellCb   *maxciCell = RG_SCH_MAXCIUL_GET_CELL(cell);
   CmLListCp            *queue;

   TRC2(rgSCHMaxciUlContResReq);

   /* If UE present in some queue delete from there a more likely case is that
    * it wont be present in the queue. */
   if (maxciUe->crntQ) 
   {
      cmLListDelFrm(maxciUe->crntQ, &(maxciUe->prioLnk));
   }
   /* Add to contResLst */
   queue = &(maxciCell->contResLst);
   cmLListAdd2Tail(queue, &maxciUe->prioLnk);
   maxciUe->crntQ = queue;
   RETVOID;
}


/**
 * @brief Invoked on final RB allocation for a UL subframe
 *
 * @details
 *
 *     Function : rgSCHMaxciUlAllocFnlz
 *
 *     Processing Steps:
 *       - Call utility function for handling finalization for Contention
 *       resolution.
 *       - Call utility function for handling finalization for normal
 *       transmissions.
 *
 *  @param[in]  RgSchCellCb         *cell
 *  @param[in]  RgSchCmnUlRbAllocInfo  *alloc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlAllocFnlz
(
RgSchCellCb         *cell,
RgSchCmnUlRbAllocInfo  *alloc
)
#else
PUBLIC Void rgSCHMaxciUlAllocFnlz(cell, alloc)
RgSchCellCb             *cell;
RgSchCmnUlRbAllocInfo   *alloc;
#endif
{
   TRC2(rgSCHMaxciUlAllocFnlz);

   rgSCHMaxciUlUtlFnlzContRes(cell, alloc);
   rgSCHMaxciUlUtlFnlzTx(cell, alloc);
   RETVOID;
}

/** @brief This function is called to after allocation for contention
 * resolution is done.
 *
 * @details
 *
 *     Function: rgSCHMaxciUlUtlFnlzContRes
 *
 *         Processing steps:
 *         - Loop through all the UEs present in the schdContResLst 
 *         - Fill in the allocation information for this UE
 *         - Remove the UE from crntQ (maxciCell->contResLst
 *
 * @param[in]  RgSchCellCb             *cell
 * @param[in]  RgSchCmnUlRbAllocInfo   *alloc
 * @return Void
 */
#ifdef ANSI
PRIVATE Void rgSCHMaxciUlUtlFnlzContRes
(
 RgSchCellCb               *cell,
 RgSchCmnUlRbAllocInfo     *alloc
)
#else
PRIVATE Void rgSCHMaxciUlUtlFnlzContRes (cell, alloc)
 RgSchCellCb               *cell;
 RgSchCmnUlRbAllocInfo     *alloc;
#endif
{
   RgSchUeCb            *ue;
   RgSchMaxciUlUe       *maxciUe;
   CmLList              *node;

   TRC2(rgSCHMaxciUlUtlFnlzContRes);

   node = alloc->schdContResLst.first;
   while(node)
   {
      ue = (RgSchUeCb*)node->node;
      maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
      cmLListDelFrm(maxciUe->crntQ, &(maxciUe->prioLnk));
      maxciUe->crntQ = NULLP;
#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddUpdULMark (cell,ue);
      }
#endif
      /* reset the UE UL allocation Information */
      rgSCHCmnUlUeResetTemp(cell, ue);
      node = node->next;
   }
   RETVOID;
} /* end of rgSCHMaxciUlUtlFnlzContRes */ 

/** @brief This function is called to after allocation is done.
 *
 * @details
 *
 *     Function: rgSCHMaxciUlUtlFnlzTx
 *
 *         Processing steps:
 *         - Go through the schdUeLst 
 *         - Reset srRcvd to FALSE
 *         - Fill allocation information for this UE.
 *         - Call rgSCHMaxciUlUtlPosUe function that does the following
 *          - if the UE has been completely satified
 *             - remove the corresponding UEs from maxciCell->srbLst 
 *                or maxciCell->ueLst.
 *          - else
 *             - leave the UE in place.
 *
 * @param[in] RgSchCellCb             *cell
 * @param[in]  RgSchCmnUlRbAllocInfo   *alloc
 * @return Void
 */
#ifdef ANSI
PRIVATE Void rgSCHMaxciUlUtlFnlzTx
(
 RgSchCellCb               *cell,
 RgSchCmnUlRbAllocInfo     *alloc
)
#else
PRIVATE Void rgSCHMaxciUlUtlFnlzTx (cell, alloc)
 RgSchCellCb               *cell;
 RgSchCmnUlRbAllocInfo     *alloc;
#endif
{
   RgSchUeCb            *ue;
   RgSchCmnUlUe         *cmnUe;
   RgSchMaxciUlUe       *maxciUe;
   CmLList              *node;
   RgSchCmnLcg          *lcg0;
   RgSchDrxUeCb      *drxUe    = NULLP;
   CmLListCp         ulInactvLst; /* list of UE's becoming UL-inactive */

   TRC2(rgSCHMaxciUlUtlFnlzTx);

   cmLListInit(&ulInactvLst);
   node = alloc->schdUeLst.first;
   while(node)
   {
      ue = (RgSchUeCb*)node->node;
      cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
      maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
      lcg0 = RG_SCH_CMN_GET_UL_LCG(&ue->ul.lcgArr[0]);
      if (ue->isDrxEnabled)
      {
         if(maxciUe->srRcvd == TRUE)
         {
            drxUe = RG_SCH_DRX_GET_UE(ue);
            drxUe->drxUlInactvMask  |= RG_SCH_DRX_SR_BITMASK;

            if ( !RG_SCH_DRX_UL_IS_UE_ACTIVE(drxUe) )
            {
               ue->ul.ulInactvMask |= RG_DRX_INACTIVE;
               /* Add to Ul inactive List */
               ue->ulDrxInactvLnk.node  = (PTR)ue;
               cmLListAdd2Tail(&ulInactvLst,&(ue->ulDrxInactvLnk));
            }
            drxUe->srRcvd = FALSE;
         }
      }
      maxciUe->srRcvd = FALSE;
      /* reposition the UE */
      rgSCHMaxciUlUtlPosUe(cell, ue, cmnUe, maxciUe, lcg0);
#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddUpdULMark (cell,ue);
      }
#endif
      node = node->next;
      /* reset the UE UL allocation Information */
      rgSCHCmnUlUeResetTemp(cell, ue);
   }
   rgSCHMaxciUlInactvLstInd(cell, &ulInactvLst);
   /* Reset the non-scheduled UEs as well */
   node = alloc->nonSchdUeLst.first;
   while(node)
   {
      ue   = (RgSchUeCb *)node->node;
      node = node->next;
      /* reset the UE UL allocation Information */
      rgSCHCmnUlUeResetTemp(cell, ue);
   }

   RETVOID;
} /* end of rgSCHMaxciUlUtlFnlzContRes */ 


/** @brief This function removes the list of UEs inactive for Uplink. This
 * information comes from MeasurementGap or Ack/Nack repetition. 
 *
 * @details
 *
 *     Function: rgSCHMaxciUlInactvLstInd
 *
 *         Processing steps:
 *         - Loop through the inactive UE list removing UEs from the respective
 *         priority queue.
 *
 *
 * @param[in]  RgSchCellCb    *cell
 * @param[in]  CmLListCp      *inactvLst
 * @return Void
 */
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlInactvLstInd
(
 RgSchCellCb      *cell,
 CmLListCp        *inactvLst
)
#else
PUBLIC Void rgSCHMaxciUlInactvLstInd(cell, inactvLst)
 RgSchCellCb      *cell;
 CmLListCp        *inactvLst;
#endif
{
   CmLList              *node;
   RgSchUeCb            *ue;
   RgSchMaxciUlUe       *maxciUe;
   CmLListCp            *priorQ;
   RgSchMaxciUlCellCb   *maxciCell = RG_SCH_MAXCIUL_GET_CELL(cell);

   TRC2(rgSCHMaxciUlInactvLstInd);

   node = inactvLst->first;
   while (node)
   {
      ue = (RgSchUeCb*)node->node;
      maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
      /* Remove from the queue if present in any queue 
       * other than ContResLst. */
      priorQ = maxciUe->crntQ;
      if (priorQ)
      {
         if (priorQ == &(maxciCell->contResLst))
         {
            continue;
         }
         cmLListDelFrm(priorQ, &(maxciUe->prioLnk));
         maxciUe->crntQ = NULLP;
      }
      node = node->next;
   }/* end of while */
   RETVOID;
} /* end of rgSCHMaxciUlInactvLstInd */ 

/** @brief This function is called by Measurement Gap/ACK Nack module to inform
 * the scheduler to add the given UE back into the priority queues.
 *
 * @details
 *
 *     Function: 
 *
 *         Processing steps:
 *         - If srRcvd or effBsr != 0 for this UE then 
 *          - Select an appropriate queue
 *             - If lcg0->bs != 0
 *                - queue = srbLst
 *             - else
 *                - queue = ueLst[crntUlCqi]
 *          - Add to queue.
 *
 * @param RgSchCellCb     *cell 
 * @param RgSchUeCb       *ue
 * @return Void
 */
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlActvtUeInd
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHMaxciUlActvtUeInd (cell, ue)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
#endif
{

   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
   RgSchMaxciUlCellCb   *maxciCell = RG_SCH_MAXCIUL_GET_CELL(cell);
   RgSchCmnLcg          *lcg0 = RG_SCH_CMN_GET_UL_LCG(&ue->ul.lcgArr[0]);
   CmLListCp            *queue;
   U8                   cqi;
   CmLteUeCategory ueCtg = (CmLteUeCategory)(RG_SCH_CMN_GET_UE_CTGY(ue));

   TRC2(rgSCHMaxciUlActvtUeInd);

   if (maxciUe->srRcvd || ue->ul.effBsr)
   {
      if (lcg0->bs)
         queue = &(maxciCell->srbLst);
      else
      {
         cqi = rgSCHCmnUlGetCqi(cell, ue, ueCtg);
         RGSCH_ARRAY_BOUND_CHECK_WITH_POS_IDX(cell->instIdx, maxciCell->ueLst, (cqi-1));
         queue = &(maxciCell->ueLst[cqi - 1]);
      }
      cmLListAdd2Tail(queue, &maxciUe->prioLnk);
      maxciUe->crntQ = queue;
   }
   RETVOID;
} /* end of rgSCHMaxciUlActvtUeInd */ 

/** @brief This function handles the Refresh indication i.e. effBsr of the UE
 * has been changed based on the reseting of effBR of that UE.
 *
 * @details
 *
 *     Function: 
 *
 *         Processing steps:
 *         - If the UE is inactive
 *          return
 *         - We may have to add the UE to the scheduling queue if reset of effBR
 *         has changed the effBsr for this UE. 
 *         - Call rgSCHMaxciUlUtlPosUe to reposition the UE.
 *
 * @param[in]  RgSchCellCb  *cell
 * @param[in]  RgSchUeCb    *ue
 * @return Void
 */
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlUeRefresh
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHMaxciUlUeRefresh (cell, ue)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
#endif
{
   RgSchCmnUlUe         *cmnUe = RG_SCH_CMN_GET_UL_UE(ue, cell);
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);
   RgSchCmnLcg          *lcg0 = RG_SCH_CMN_GET_UL_LCG(&ue->ul.lcgArr[0]);

   TRC2(rgSCHMaxciUlUeRefresh);

   /* Return if inactive */
   if (ue->ul.ulInactvMask)
   {
      RETVOID;
   }
   /* Check if effBsr has changed and possibly add to scheduling queues */
   rgSCHMaxciUlUtlPosUe(cell, ue, cmnUe, maxciUe, lcg0);
   RETVOID;
} /* end of */ 

/** @brief This function is called on UE Reset.
 *
 * @details
 *
 *     Function: 
 *
 *         Processing steps:
 *         - Remove the UE from any scheduling Queue if present.
 *         - Reset srRcvd
 *
 * @param[in]  RgSchCellCb     *cell
 * @param[in]  RgSchUeCb       *ue
 * @return 
 */
#ifdef ANSI
PUBLIC Void rgSCHMaxciUlUeReset
(
 RgSchCellCb      *cell,
 RgSchUeCb        *ue
)
#else
PUBLIC Void rgSCHMaxciUlUeReset (cell, ue)
 RgSchCellCb      *cell;
 RgSchUeCb        *ue;
#endif
{
   RgSchMaxciUlUe       *maxciUe = RG_SCH_MAXCIUL_GET_UE(ue, cell);

   TRC2(rgSCHMaxciUlUeReset);

   /* Remove the UE from any scheduling queue if present. */
   if (maxciUe->crntQ)
   {
      cmLListDelFrm(maxciUe->crntQ, &(maxciUe->prioLnk));
      maxciUe->crntQ = NULLP;
   }
   maxciUe->srRcvd = FALSE;
   RETVOID;
} /* end of rgSCHMaxciUlUeReset */ 



/**********************************************************************
 
         End of file:     gk_sch_maxci.c@@/main/2 - Sat Jul 30 02:21:44 2011
 
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
           rg004.201 ms      1. ccpu00110457: DL DTX Handling
           rg005.201 sm      1. Added Macro to check if UE is picked for Retx 
           rg006.201 sd      1. ccpu00112398: Added periodic BSR timer
           rg007.201   ap  1. Added support for MIMO
           rg008.201 sd      1. Removed dependncy on MIMO compile-time flag
           rg009.201 dv      1.Added changes of TFU_UPGRADE. 
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
           rg001.301 nudupi 1. Added the changes for the ccpu00118350.
           rg002.301 rntiwari 1.ccpu00120941: Added handling for deleting UE
                                 from txUeLst.
$SID$        ---        rt  1. LTE MAC 4.1 release
*********************************************************************91*/
