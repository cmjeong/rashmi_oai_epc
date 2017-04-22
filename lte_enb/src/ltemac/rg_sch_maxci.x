


/**********************************************************************
 
    Name:   LTE MAC MAX C/I scheduler
 
    Type:   C include file
 
    Desc:   Defines required by Max C/I scheduler
 
    File:   rg_sch_maxci.x
 
    Sid:      rg_sch_maxci.x@@/main/2 - Sat Jul 30 02:22:07 2011
 
    Prg:    apany
 
**********************************************************************/
/** @file rg_sch_maxci.x
@brief This file contains data structures for the MAX C/I scheduler.
*/
 

/*
*     The defines in this file correspond to structures and variables
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000372       LTE-MAC
*
*/

#ifndef __RGMAXCIX__
#define __RGMAXCIX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
  @brief Downlink Logical channel control block for Max C/I scheduling. */
typedef struct rgSchMaxciDlLc
{
   Bool             isGbr;       /*!< TRUE if GBR svc */
   U32              mbr;         /*!< Configured MBR: only for GBR services */
   U32              remMbr;      /*!< MBR remaining in the refresh cycle:
                                      used only for GBR services */
   U32              bo;          /*!< Actual reported BO */
   U32              hdrSz;       /*!< Est header size, valid during 
                                      scheduling */
   U32              reqBytes;    /*!< bo + hdrSz, valid during scheduling */
   CmLListCp        *lcLst;      /*!< Pointer to the list of LCs in UE to which
                                      the service belongs */
   CmLList          schdLnk;     /*!< To link service into UE's list of
                                   scheduled services in a TTI */
} RgSchMaxciDlLc;

/**
  @brief HARQ process DL control block for Max C/I scheduling. */
typedef struct rgSchMaxciDlHqProc
{
   Bool      isSrb;              /*!< Indicates if the harq process contains 
                                   SRB data */
   CmLList   ueLnk;              /*!< Link for the harq processes added to the
                                   UE list of re-transmitting processes */
} RgSchMaxciDlHqProc;

/**
  @brief UE DL control block for Max C/I scheduling. */
typedef struct rgSchMaxciDlUe
{
   Bool             ambrPres;     /*!< TRUE if AMBR configured */
   U32              remAmbr;      /*!< Remaining AMBR in current refresh 
                                       cycle */
   U8               isTaReq;      /*!< Indicates if TA has been requested to 
                                       common allocator module for scheduling */
   U8               wbCqi;        /*!< Current Wideband CQI value */ 
   U8               priorLvl;      /* priority level value. It varies from 0 to 15,So 16 priority levels exist  */                        
   CmLListCp        *txSrbLstPtr; /*!< Pointer to transmitting SRB queue in the
                                       cell to which UE belongs */
   CmLListCp        *txUeLstPtr;  /*!< Pointer to transmitting UE queue
                                       in the cell to which UE belongs*/
   CmLListCp        *retxLstPtr;  /*!< Pointer to re-transmitting queue
                                       to which UE belongs */
   /* The following are list of channels which are eligible for data being
    * sent, lists being divided into (channels) categories. */
   CmLListCp        srbLst;       /*!< List of SRBs (DCCHs) */
   CmLListCp        gbrLst;       /*!< List of GBR services */
   CmLListCp        nongbrLst;    /*!< List of non-GBR services excluding 
                                   * DCCHs */
   CmLListCp        retxSrbProcs; /*!< List of procs for which retx is pending,
                                   * for procs having SRBs */
   CmLListCp        retxDrbProcs; /*!< List of procs for which retx is pending,
                                   * for procs not having SRBs */
   /* The list in HARQ proc cannot be used easily, data struct corresponds to
    * one that is sent over RGU. So having a list of them separately as
    * schedSvcs. */
   CmLListCp        schdLcs;      /*!< Scratchpad to hold LCs scheduled by Max C/I,
                                   * ensuring that any SRB appears first. This is
                                   * maintained to possibly change (reduce)
                                   * byte alloc to LCs after final RB alloc. */
   CmLList          srbLnk;    /*!< To link UE in SRB queues for new tx */
   CmLList          prioLnk;   /*!< To link UE in priority queues for new tx */
   CmLList          retxLnk;   /*!< To link UE in priority queues, for retx */
} RgSchMaxciDlUe;

typedef struct rgSchMaxciDlQueues
{
   CmLListCp     srbLst;              /*!< List of UEs for which one or more
                                       * DCCHs have pending buffer or data
                                       * corresponding to new tx or retx
                                       * respectively */
   CmLListCp     ueLst[RG_SCH_MAXCIDL_NUM_CQI_LVLS]; /*!< Queues for UEs 
                                                          with appropriate 
                                                          CQI */
} RgSchMaxciDlQueues;


typedef RgSchMaxciDlQueues RgSchMaxciDlTxQueues;
typedef RgSchMaxciDlQueues RgSchMaxciDlRetxQueues;

/**
  @brief Cell DL control block for Max C/I scheduling. */
typedef struct rgSchMaxciDlCell
{
   RgSchMaxciDlTxQueues     txQueues;
   RgSchMaxciDlRetxQueues   retxQueues;
   U32                      priorEff;
} RgSchMaxciDlCell;

/* Uplink related structures */
/**
  @brief UE UL control block for Max C/I scheduling */
typedef struct rgSchMaxciUlUe
{
   Bool             srRcvd;   /*!< TRUE if SR was received for this UE. */
   CmLList          prioLnk;   /*!< To link UE in priority queues for new tx */
   CmLListCp        *crntQ;
} RgSchMaxciUlUe;

/**
  @brief Cell control block for Max C/I scheduling. */
typedef struct rgSchMaxciUlCellCb
{
   CmLListCp     contResLst;     /*!< UEs with pending UL alloc for msg4. */
   CmLListCp     srbLst;         /*!< List of UEs for which DCCH LCG(s) 
                                   is/are mapped with pending buffer */
   CmLListCp     ueLst[RG_SCH_CMN_UL_MAX_CQI-1]; /*!< Queues for UEs with 
                                                      appropriate CQI */
} RgSchMaxciUlCellCb;



EXTERN Void rgSCHMaxciDlInit ARGS((
RgDlSchdApis      *apis
));
EXTERN S16 rgSCHMaxciDlCellCfg ARGS((
RgSchCellCb       *cell,
RgrCellCfg        *cellCfg,
RgSchErrInfo      *err
));
EXTERN S16 rgSCHMaxciDlCellRecfg ARGS((
RgSchCellCb     *cell,
RgrCellRecfg    *cellRecfg,
RgSchErrInfo    *err
));
EXTERN Void rgSCHMaxciDlCellDel ARGS((
RgSchCellCb          *cell
));
EXTERN S16 rgSCHMaxciDlUeCfg ARGS((
RgSchCellCb         *cell,
RgSchUeCb           *ue,
RgrUeCfg            *ueCfg,
RgSchErrInfo        *err
));
EXTERN S16 rgSCHMaxciDlUeRecfg ARGS((
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrUeRecfg       *ueRecfg,
RgSchErrInfo     *err
));
EXTERN Void rgSCHMaxciDlUeDel ARGS((
RgSchCellCb          *cell,
RgSchUeCb            *ue
));
EXTERN S16 rgSCHMaxciDlLcCfg ARGS((
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc,
RgrLchCfg          *lcCfg,
RgSchErrInfo       *err
));
EXTERN S16 rgSCHMaxciDlLcRecfg ARGS((
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc,
RgrLchRecfg        *lcRecfg,
RgSchErrInfo       *err
));
EXTERN Void rgSCHMaxciDlLcDel ARGS((
RgSchCellCb        *cell,
RgSchUeCb          *ue,
RgSchDlLcCb        *dlLc
));
EXTERN Void rgSCHMaxciDlCqiInd ARGS((
RgSchCellCb          *cell,
RgSchUeCb            *ue,
Bool                 isPucchInfo,
Void                 *dlCqi
));
EXTERN Void rgSCHMaxciDlProcAddToRetx ARGS((
RgSchCellCb           *cell,
RgSchDlHqProcCb       *hqP
));
EXTERN Void rgSCHMaxciDlDedBoUpd ARGS((
RgSchCellCb            *cell,
RgSchUeCb              *ue,
RgSchDlLcCb            *lc
));
EXTERN Void rgSCHMaxciDlSched ARGS((
RgSchCellCb           *cell,
RgSchCmnDlRbAllocInfo *allocInfo
));
EXTERN Void rgSCHMaxciDlAllocFnlz ARGS((
RgSchCellCb            *cell,
RgSchCmnDlRbAllocInfo  *alloc
));
EXTERN Void rgSCHMaxciDlUeRefresh ARGS((
RgSchCellCb         *cell,
RgSchUeCb           *ue
));
EXTERN Void rgSCHMaxciDlUeReset ARGS((
RgSchCellCb         *cell,
RgSchUeCb           *ue
));
EXTERN Void rgSCHMaxciDlActvtUe ARGS((
RgSchCellCb         *cell,
RgSchUeCb           *ue
));
EXTERN Void rgSCHMaxciDlHndlInActvUes ARGS((
RgSchCellCb         *cell,
CmLListCp           *inactvUeLst
));

/* Uplink Function declarations */
EXTERN S16 rgSCHMaxciUlCellCfg ARGS((
         RgSchCellCb          *cell,
         RgrCellCfg           *cfg,
         RgSchErrInfo         *err));

EXTERN S16 rgSCHMaxciUlCellRecfg ARGS((
         RgSchCellCb     *cell,
         RgrCellRecfg    *recfg,
         RgSchErrInfo    *err));

EXTERN Void rgSCHMaxciUlCellDel ARGS((
         RgSchCellCb       *cell));

EXTERN S16 rgSCHMaxciUlUeCfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgrUeCfg         *cfg,
         RgSchErrInfo     *err));

EXTERN S16 rgSCHMaxciUlUeRecfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgrUeRecfg       *recfg,
         RgSchErrInfo     *err));

EXTERN Void rgSCHMaxciUlUeDel ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue));

EXTERN S16 rgSCHMaxciUlLcgCfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchLcgCb       *ulLcg,
         RgrLcgCfg        *cfg,
         RgSchErrInfo     *err));

EXTERN S16 rgSCHMaxciUlLcgRecfg ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchLcgCb       *ulLcg,
         RgrLcgRecfg      *cfg,
         RgSchErrInfo     *err));

EXTERN Void rgSCHMaxciUlLcgDel ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchLcgCb       *ulLcg));

EXTERN Void rgSCHMaxciUlSched ARGS((
         RgSchCellCb             *cell,
         RgSchCmnUlRbAllocInfo   *alloc));

EXTERN Void rgSCHMaxciUlUpdBsrShort ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchLcgCb       *lcg,
         U8               bsr));


EXTERN Void rgSCHMaxciUlUpdBsrTrunc ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         RgSchLcgCb       *lcg,
         U8               bsr));

EXTERN Void rgSCHMaxciUlUpdBsrLong ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue,
         U8               bsArr[]));

EXTERN Void rgSCHMaxciUlContResReq ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue));

EXTERN Void rgSCHMaxciUlSrInd ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue));

EXTERN Void rgSCHMaxciUlCqiInd ARGS((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         TfuUlCqiRpt         *ulCqiInfo));
EXTERN S16 rgSCHMaxciUlLcgUpd ARGS ((
         RgSchCellCb         *cell,
         RgSchUeCb           *ue,
         RgInfUeDatInd       *datInd));
EXTERN Void rgSCHMaxciUlUeRefresh ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue));

EXTERN Void rgSCHMaxciUlAllocFnlz ARGS((
         RgSchCellCb         *cell,
         RgSchCmnUlRbAllocInfo  *alloc));

EXTERN Void rgSCHMaxciUlInactvLstInd ARGS((
         RgSchCellCb      *cell,
         CmLListCp        *inactvLst));

EXTERN Void rgSCHMaxciUlActvtUeInd ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue));

EXTERN Void rgSCHMaxciUlUeReset ARGS((
         RgSchCellCb      *cell,
         RgSchUeCb        *ue));

EXTERN Void rgSCHMaxciUlInit ARGS((
         RgUlSchdApis         *apis
         ));



EXTERN S16 rgSCHMaxciUlLchCfg ARGS((
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrLchCfg        *cfg,
RgSchErrInfo     *err
));

EXTERN S16 rgSCHMaxciUlLchRecfg ARGS((
RgSchCellCb      *cell,
RgSchUeCb        *ue,
RgrLchRecfg      *recfg,
RgSchErrInfo     *err
));

EXTERN S16 rgSCHMaxciUlLchDel ARGS((
RgSchCellCb      *cell,
RgSchUeCb        *ue,
CmLteLcId        lcId,
U8               lcgId
));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __RGMAXCIX__ */


/**********************************************************************
         End of file:     rg_sch_maxci.x@@/main/2 - Sat Jul 30 02:22:07 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     apany   1. LTE MAC 2.1 release
           rg007.201   ap  1. Added support for MIMO
           rg008.201 sd    1.Removed dependency on MIMO compile-time flag
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
$SID$        ---       rt    1. LTE MAC 4.1 Release.                           
*********************************************************************91*/
