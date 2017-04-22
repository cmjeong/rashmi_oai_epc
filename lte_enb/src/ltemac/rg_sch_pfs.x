


/**********************************************************************
 
    Name:   LTE MAC PFS scheduler
 
    Type:   C include file
 
    Desc:   Defines required by PFS scheduler
 
    File:   rg_sch_pfs.x
 
    Sid:      rg_sch_pfs.x@@/main/2 - Sat Jul 30 02:22:08 2011
 
    Prg:    apany
 
**********************************************************************/
/** @file rg_sch_pfs.x
@brief This file contains data structures for the Propotional fair scheduler.
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

#ifndef __RGPFSX__
#define __RGPFSX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* MS_WORKAROUND for ccpu00122892  : Temp fix for erroeneous RETX Harq release by rgSCHCmnDlAllocRetxRb */
EXTERN Void rgSCHPfsDlProcRmvFrmRetx ARGS((RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlHqProcCb *hqP));
   /* Fix : Updating PFS to start prio with highest possible value
               and diminishing prio val updates from there on */
/**
  @brief Data structure holding info of frac Prio updates */
typedef struct rgSchPfsFracPrioInfo { 
   U32  fracDataRate;/*!< Amount of data rate to be serviced
                          to move one notch in fracPrio.
                          Precomputed for a given LC Cfg.*/
   U32  achvdFracDataRate; /*!< Amount of data rate serviced
                                till now.
                                achvdFracDataRate < fracDataRate.
                                Reset at every refresh cycle. */ 
   U32  fracPrioLvls; /*!< Number of fracDataRates serviced so far
                           in this refresh cycle. Reset at every
                           refresh cycle. */
}RgSchPfsFracPrioInfo;

typedef struct rgSchPfsCellSpfcDlLc
{
   U32         svccqiPrio;   /*!< svcPrio * cqiPrio */
   U32         achvdFracDataRate; /*!< Amount of data rate serviced
                                   till now.
                                   achvdFracDataRate < fracDataRate.
                                   Reset at every refresh cycle. */ 
   CmLList     favCellLnk;   /*!< Link to add cell in the favourite list 
                               for this LC */
   U32         cellPrio; 
   CmLList     schedSvcLnk; /*!< link to add LCs in the schedSvcs list */
}RgSchPfsCellSpfcDlLc;

/**
  @brief Downlink Logical channel control block for PFS. */
typedef struct rgSchPfsDlLc
{
   U8              qci;        /*!<QCI value of the LC */
   U8              lcType;     /*!< LC type - SRB/DRB0/GRB/AMBR */
   U32             gbr;        /*!< Configured GBR */
   U32             deltaMbr;   /*!< Configured MBR in excess of configured GBR */
   U32             remGbr;     /*!< GBR remaining for current refresh cycle */
   U32             remDeltaMbr;/*!< MBR remaining in excess of GBR */
   U32             bo;         /*!< Buffer occupancy */
   U32             effBo;      /*!< Effective BO */
   U32             hdrSz;      /*!< Est header size, valid during scheduling */
   U32             reqBytes;   /*!< effBo + hdrSz, valid during scheduling */
   CmLListCp      *prioLstCp;    /*!< List pointer to the priority queue */
   CmLListCp      *pdbTrckLstCp; /*!< List pointer to the PDB Tracker queue */
   CmLList         prioLnk;      /*!< To link service into priority queues */
   CmLList         ambrLnk;      /*!< To link AMBR svcs in UE */
   U32             pfsPrio;      /*!< PSF priority */
   U32             svcPrio;      /*!< Service priority */
   U32             pdbLvl;           /*!< PDB Priority */
   Bool            flowCtrlPdbBrchd; /*! TRUE indicates Flow Ctrl PDB breached */
   U32             oldestSduArrTime; /*!< Latest reported oldest SDU arrival time */
   U32             pdb;              /*!< Packet Delay Budget */
   U32             lastPdbLvl;       /*!< Number of PDB levels */ 
   U32             flowCtrlPdbLimit; /*!< PDB level beyond which Flow Ctrl is required */ 
   U32             pdbLvlSz;         /*!< PDB Level size */
   U32             pdbPrio;          /*!< PDB Prio weight for pdbLvl */
   U8              qId;              /*!< Queue ID */
   /* Fix : Updating PFS to start prio with highest possible value
      and diminishing prio val updates from there on. */
   RgSchPfsFracPrioInfo  fracPrioInfo; /*!< Data structure holding 
                                          info of frac Prio updates */
   CmLList         cfgLcLnk;    /*!< To link cfgd GBR/AMBR services */
   CmLList         svcPrioLnk;  /*!< To link service into UE->svcPrioLst */
   CmLList         pdbQLnk;     /*!< Link to LcCb inserted in PDB tracker list in DL*/
   U32             numOccWithinPdb;   /*!< Number of occasions LC is within PDB */
   U32             pktAdmitCnt;       /*!<Number of occassions LC is within PDB */
   U32             prevCnt;           /*Number of Occassions LC is within PDB */
   U32             numOccBreachedPdb; /*Number of Occassions LC breached PDB */
   U32             prbCnt;            /*PRB usage over this flow contrl monitor interval */
   CmLList         lcPdbFbkLnk;  /*!<link to LC in LC flow contrl monitoring lst */
   U32             fcQIdx;    /*!array index to the list of LC under flow control monitoring*/
   U32             maxBo4FlowCtrl; /*!< MAX BO of Queued SDUs at RLC beyond which Flow is Controlled */
   U32             rcvryDurFlowCtrl; /*!< Max wait Per of RLC SDUs beyond which are estimated to 
                                      *   breach PDB */
   U32             initMaxBo4FlowCtrl; 
   U32             pdbFcRcvrd;      /*Flag to indicate the breach recovery for FC */
   Bool            statusScheduled;/*!<Flag to indicate if UE is scheduled for DL status PDU */


   CmLListCp       cellFavLst; /*list of favourite cells in the decreasing 
                                 order of their priority */      
   U32             cellFavLstUpdIdx; /* To maintain the last Index in 
                                        which cell FavLst was updated */
   RgSchPfsCellSpfcDlLc   cellSpfc[CM_LTE_MAX_CELLS]; 
   CmLList         prioChngLnk;
   U32             favCellPrio;
   CmLListCp       *favCellPrioLstCp;
   U32             fracDataRate; /*!< Amount of data rate to be serviced to move 
                                      one notch in fracPrio. Precomputed for a 
                                      given LC Cfg. This parameter is used to 
                                      get favCell list for a LC */
   U32             maxGrantBytes;
} RgSchPfsDlLc;


/**
  @brief Downlink HARQ control block for PFS. */
typedef struct rgSchPfsQciPdbInfo
{
  U32   pdb;           /*!< Packet Delay Budget for current QCI */
  U32   maxNmbPdbLvls; /*!< Number of PDB levels for current QCI */ 
  U32   lastLvl4FullFlow; /*!< Last PDB level beyond which FlowCtrl
                               need to be triggered */ 
  U32   pdbLvlSz;      /*!< PDB Level size for current QCI */
  U32   pdbPrioWgt[RG_SCH_PFS_MAX_PDB_LVLS];    /*!< PDB Prio weight per pdb Lvl */
} RgSchPfsQciPdbInfo;

/**
  @brief Downlink HARQ control block for PFS. */
typedef struct rgSchPfsDlHqProc
{
   CmLList         retxLnk;  /*!< To link together retx procs in cell lists */
   CmLListCp      *retxLstCp; /* This is to hold the retx queue pointer
                               * as soon as HARQ proc has been scheduled. This
                               * is to avoid checks to determine which queue
                               * to add proc to for retx. */
   CmLList         ueRetxLnk;  /*!< To link together retx procs in UE's
                                * list of retx procs */
} RgSchPfsDlHqProc;

typedef struct rgSchPfsUeCmn
{
   U32            remAmbr;   /*!< Remaining AMBR in current refresh cycle */
   CmLListCp      cfgGbrLst;   /*!< Configured GBR services */
   CmLListCp      cfgAmbrLst;  /*!< Configured AMBR services (exluding DRB0) */
   CmLListCp      ambrLst;   /*!< AMBR (except DRB0) services with BO
                              * in priority order */
   RgSchDlLcCb    *ambrSvc;   /*!< Points to the current AMBR service */
   /* Mentaing services at the UE level */
   CmLListCp      svcPriorLst;                           
   /* Fix : Updating PFS to start prio with highest possible value
      and diminishing prio val updates from there on. */
   RgSchPfsFracPrioInfo  fracPrioInfo; /*!< Data structure holding 
                                         info of frac Prio updates
                                         for all AMBR services. */
   Bool            isUeSchd;    /* To restrict addition of UE in toBeSchLst only 
                                   for one cell during estimation phase */
   RgSchDlLcCb     *highestPrioLc; /* !< link to LC with highest PFS priority */
   U32             fracDataRate;
}RgSchPfsUeCmn;

/**
  @brief UE DL control block for PFS. */
typedef struct rgSchPfsDlUe
{
   U8             cqi;       /*!< DL CQI (wideband) */
   U32            cqiPrio;   /*!< CQI priority */
   CmLList        retxLnk;   /*!< To link UE into priority queues, for retx */
   CmLListCp      *retxLstCp; /*!< Cp for retx priority queue */
   CmLListCp      retxProcs; /*!< List of procs in retx queues */
   Bool           taReq;      /*!< While scheduling during a TTI,
                               * this indicates if TA was scheduled */
   U32            totalPrbReqd;  /* !< Total PRB required for all services */
   U32            totalPfsPrio;  /* !< Total PFS Priority of all services */
   U32            totalHdrSz;  /* !< Total header size of all services */
   U32            totalEffBo;  /*!< Total effective BO for this UE */
   CmLList        toBeSchedLnk;   /*!< To link UE into toBeSchedulinglist for
                                    each cell */
   U32            maxPfsPrio; /* Maximum PFS priority among all the LCs of 
                                 this UE*/
   RgSchPfsUeCmn  *cmnParam; /* Structure for UE parameters which are common 
                                  for all the cells */ 
#ifdef LTE_ADV
   Bool                   schdSCellActCe;   /*!< Set if SCell Act CE is considered in this
                                              scheduling occassion. */
#endif
   CmLListCp      schedSvcs; /*!< list of LCs added in the increasing order 
                                  of their requested bytes */  
} RgSchPfsDlUe;

/**
  @brief Lc Info. */
typedef struct rgSchPfsUlLc 
{
   U8             qci;      /*!< QCI for a particular LC */
   U8             lcId; 
   CmLList        nodeLnk;
}RgSchPfsUlLc;

/**
  @brief Lcg Info. */
typedef struct rgSchPfsLcgInfo  
{
   U8             prioLch;  /*!< Lc which corresponds to lcg priority in a particular Lcg */ 
   U32            lcgPrio;  /*!< Lcg priority */ 
   RgSchPfsFracPrioInfo  fracPrioInfo; /*!< Data structure holding 
                                          info of frac Prio updates */
   CmLListCp      lcQciInfo;  /*!< List containing lc's and corresponding qci
                                   per Lcg */ 
}RgSchPfsLcgInfo;

/**
  @brief UE UL control block for PFS. */
typedef struct rgSchPfsUlUe
{
   U8             cqi;     /*!< UL CQI (wideband) */
   U32            cqiPrio;   /*!< CQI priority */
   U32            lcgPrio;   /*!< LCG priority */
   U32            fracPrio;  /*!< Remaining fraction priority */
   U32            pfsPrio;   /*!< PFS priority */
   U8             qId;       /*!< PFS queue ID - not applicable when in LCG0
                               *  or contention resolution queue */
   CmLListCp     *lstCp;     /*!< Priority Q that the UE is in */
   CmLList        prioLnk;   /*!< To link into priority queues */
   Bool           srRcvd;    /*!< Set to TRUE when SR is rcvd, set
                              *   to FALSE once allocation has been made */
   /* Added the new parameter below to maintain a context
    * that whether the UE has been scheduled in current UL SF.*/
   Bool           schedInCrntUlSf; /*!< Set to TRUE if UE is scheduled
                                    in the current UL SF scheduled.*/
   /* Fix : Updating PFS to start prio with highest possible value
      and diminishing prio val updates from there on. */
   RgSchPfsFracPrioInfo  fracPrioInfo; /*!< Data structure holding 
                                          info of frac Prio updates */
   RgSchPfsLcgInfo       schedLcgInfo[RGSCH_MAX_LCG_PER_UE];   /*!< Lcg Info */
   Bool                  schedSinceRefresh;
} RgSchPfsUlUe;

/**
  @brief PFS Queues. */
typedef struct rgSchPfsDlQueues
{
   CmLListCp     srbLst;            /*!< List of DCCHs [to be moved to common part] */
   CmLListCp     drb0Lst;           /*!< List of priority 0 svcs */
   CmLListCp     gbrLst[RG_SCH_PFS_DL_NUM_GBR_QUEUES]; /*!< List of GBR svcs for which
                                             * GBR not yet satisfied */

   CmLListCp     prioMbrLst[RG_SCH_PFS_DL_NUM_MBR_QUEUES]; /*!< List of CSG GBR svcs for which
                                             * GBR already satisfied */
   CmLListCp     normMbrLst[RG_SCH_PFS_DL_NUM_MBR_QUEUES]; /*!< List of non-CSG GBR svcs for which
                                             * GBR already satisfied */
   CmLListCp     prioAmbrLst[RG_SCH_PFS_DL_NUM_AMBR_QUEUES];/*!< List of other non-GBR CSG svcs */
   CmLListCp     normAmbrLst[RG_SCH_PFS_DL_NUM_AMBR_QUEUES];/*!< List of other non-GBR non-CSG svcs */

} RgSchPfsDlQueues;


/**
  @brief PFS Queues. */
typedef struct rgSchPfsDlRetxQueues
{
   CmLListCp   srbLst;            /*!< List of DCCHs [to be moved to common part] */
   CmLListCp   drb0Lst;           /*!< List of priority 0 svcs */
   CmLListCp   gbrLst[RG_SCH_PFS_DL_NUM_GBR_QUEUES]; /*!< List of GBR svcs for which
                                             * GBR not yet satisfied */
   CmLListCp   retxMbrLst[RG_SCH_PFS_DL_NUM_MBR_QUEUES]; /*!< List of GBR svcs for which
                                             * GBR already satisfied */
   CmLListCp   retxAmbrLst[RG_SCH_PFS_DL_NUM_AMBR_QUEUES];/*!< List of other non-GBR CSG svcs */
} RgSchPfsDlRetxQueues;
/**
  @brief PFS Queues for new transmission - each list is a list of LCs. */
typedef RgSchPfsDlQueues RgSchPfsDlTxQueues;


/**
  @brief PFS UL Queues. */
typedef struct rgSchPfsUlQueues
{
   CmLListCp     contResLst;     /*!< UEs with pending UL alloc for msg4
                                  *  [to be moved to common part] */
   CmLListCp     sigLst;        /*!< UEs with buffer pending on LCG0 */
   CmLListCp     gbrLst[RG_SCH_PFS_UL_NUM_GBR_QUEUES]; /*!< UEs with buffer pending 
                                             * on GBR LCGs and GBR not yet satisfied */
   CmLListCp     normMbrLst[RG_SCH_PFS_UL_NUM_MBR_QUEUES]; /*!< UEs with buffer pending 
                                             * on GBR LCGs and GBR already satisfied */
   CmLListCp     normAmbrLst[RG_SCH_PFS_UL_NUM_AMBR_QUEUES];/*!< UEs with buffer pending
                                             * on non-GBR LCGs */
   CmLListCp     prioMbrLst[RG_SCH_PFS_UL_NUM_MBR_QUEUES]; /*!< Csg UEs with buffer pending 
                                             * on GBR LCGs and GBR already satisfied */
   CmLListCp     prioAmbrLst[RG_SCH_PFS_UL_NUM_AMBR_QUEUES];/*!< Csg UEs with buffer pending
                                             * on non-GBR LCGs */

} RgSchPfsUlQueues;

/**
  @brief PFS DL tables. */
typedef struct rgSchPfsTbls
{
   U32         tpPrios[RG_SCH_PFS_TP_FACTOR_LVLS]; /*!< Throughput priorities */
   U32         svcQciPrios[RG_SCH_CMN_MAX_QCI]; /*!< QCI priorities mapped to priorities
                                                   * to be used in PFS */
   U32         fairPrios[RG_SCH_PFS_FAIRNESS_FACTOR_LVLS]; /*!< Fairness  priorities */
} RgSchPfsTbls;


/**
  @brief Priority value range and distribution. */
typedef struct rgSchPfsPrioRange
{
   U32      min;         /*!< Minimum value for queue class */
   U32      max;         /*!< Maximum value for queue class */
   /* Fix : syed For small range and large number of Queues
    * precalculated numElemPerQ can be highly inaccurate. It
    * was leading to a crash.  */
   U32      numQs;       /*!< Number of Prio Queues for this class */
   U32      maxDiff;     /*!< maxPrio - minPrio + 1 */
} RgSchPfsPrioRange;

/**
  @brief Indicates priority ranges for each class. */
typedef struct rgSchPfsDlPrioRanges
{
   RgSchPfsPrioRange  gbrRange;
   RgSchPfsPrioRange  mbrRange;
   RgSchPfsPrioRange  ambrRange;
} RgSchPfsDlPrioRanges;

/**
  @brief Indicates priority ranges for each class. */
typedef struct rgSchPfsUlPrioRanges
{
   RgSchPfsPrioRange  gbrRange;
   RgSchPfsPrioRange  mbrRange;
   RgSchPfsPrioRange  ambrRange;
} RgSchPfsUlPrioRanges;

/**
  * @brief
  * PDB Pivot parameters.
  */
typedef struct rgSchPfsPdbCb
{
   U32               pdbPivot;        /*!< Pivot value within the 280 indices */
   CmLListCp         pdbTrckLst[RG_SCH_MAX_PDB_TIME]; /*!< Pivot value within
                                                         the 280 indices */
} RgSchPfsPdbCb;

typedef struct rgSchPfsDlLcSchdInfo
{
   CmLListCp               ceLcLst;
   CmLListCp               otherUeLcLst;
   CmLListCp               ueLst;
   U32                     ceTotPfsPrio;
   U32                     totPfsPrio;
   U32                     totPrbReq;
   U32                     totPrioBwReq;    /*!< Total bandwidth required for GBR+non-GBR LCs of priority UE(CSG/nCSG) */
   U32                     totNonPrioBwReq; /*!< Total bandwidth required for GBR+non-GBR LCs of non-priority UE(CSG/nCSG) */
   U32                     prioUeBwAvail;    /*!< Bandwidth available for non-GBR priority UE(CSG/nCSG) */
   U32                     nonPrioUeBwAvail; /*!< Bandwidth available for non-GBR+ nonpriority UE(CSG/nCSG) */
   U32                     numPrioUe;        /*!< Number of non-GBR LCs in priority UE(CSG/nCSG) */
   U32                     prioUeTotPfsPrio; /*!< total priority for current priority UEs */
   RgSchDlSf               *sf;
   RgSchCellCb             *cell;
   RgSchCmnDlRbAllocInfo   *alloc;
} RgSchPfsDlLcSchdInfo;

/**
  @brief Cell DL control block for PFS. */
typedef struct rgSchEnbPfsDl
 {
   RgSchPfsDlTxQueues   txQueues;         /*!< Queues for new transmission */
   RgSchPfsTbls       tbls;             /*!< Tables for mapping individual
                                           * values to priorities */
   RgSchPfsDlPrioRanges ranges;           /*!< PFS priority ranges for various classes */
   U8                   cfgdTpFact;       /*!< Configured Throughput coefficient */
   U32                  prioScaleFact;    /*!< Scaling factor for tp x fair metrics */
   U32                  maxSrbDrb0PrioVal;/*!< Max Prio value for SRB/DRB0 service */
   U32                  maxPrioValGbr;    /*!< Initial prio value assigned to the 
                                           * schedulable entity */
   U32                  maxPrioValAmbr;   /*!< Initial prio value assigned to the 
                                           * schedulable entity */
   RgSchPfsPdbCb        pdbInfo;          /*!< PDB Config Information */
   U32                  pdbPrioVal[RG_SCH_PFS_MAX_PDB_LVLS][RGSCH_NUM_PDB_SEV_LEVELS]; /*!< PDB level granularity.*/
   U32                  pdbLevel;          /* PDB Levels */
   CmLListCp            flowCntrlUeLst;    /* Flow Control UE List */
   U32                  flowCntrlTickCnt;  /* Tick count to trigger flow control */
   Bool                 isSchdDone;        /* To avoid traversing of priority queue for every cell*/
   U32                  cellLoad[CM_LTE_MAX_CELLS];
   U32                  lastCellLoadUpdIdx; /* Maintain the current index 
                                               in which cell load was updated*/
   U8                   remCellCnt;       /* To maintain the count of cells in 
                                             each TTI for which scheduling is done*/
   Bool                 currPrioMmbrSta;  /*!< this flag will be set to true when current priority is for CSG UEs */
   CmLListCp            prioChngLcLst;    /* List of Lcs which could not be scheduled in in its fav cell 
                                             and their PFS priority changed due to next fav cell and 
                                             has been reorderd in priority queue */
} RgSchEnbPfsDl;

/**
  @brief Cell DL control block for PFS. */
typedef struct rgSchPfsDlCell
{
   RgSchCellCb          *cell;            /*!< Cell to which this UE belongs */
   RgSchPfsDlRetxQueues retxQueues;       /*!< Queues for retransmission */
   U32                  numDlActvUes;    /*!< It is reqrd for rgu dynamic delta*/
   U32                  totalPrbUse;       /* Average of PRB used over the period */
   U16                  *prbUsage;       /* Array for PRB Usage Samples */
   U8                   prevSampleIdx;
   U16                  prbSample;                 
   Bool                 isFnlzDone;
   RgSchPfsDlLcSchdInfo rgSchPfsLcSchdInfo;
   U16                  ttiCnt;
} RgSchPfsDlCell;

/**
  @brief Cell UL control block for PFS. */
typedef struct rgSchPfsUlCell
{
   RgSchPfsUlQueues     txQueues; /*!< Queues for new transmission */
   RgSchPfsTbls         tbls;     /*!< Tables to map PFS params to priorities */
   RgSchPfsUlPrioRanges range;    /*!< PFS priority range information */
   U32                  prioScaleFact; /*!< Scaling factor for tp x fair metrics */
   /* Fix : syed MAX Initial Priority Value to be used for prio initialization. */
   U32                  maxSrbDrb0PrioVal;/*!< Max Prio value for SRB/DRB0 service */
   U32                  maxPrioValGbr; /*!< Max prio value assigned to the GBR service entity */
   U32                  maxPrioValAmbr; /*!< Max prio value assigned to the AMBR service entity */
} RgSchPfsUlCell;

typedef struct rgSchPfsLcSchdInfo
{
   CmLListCp               ceLcLst;
   CmLListCp               otherUeLcLst;
   U32                     ceTotPfsPrio;
   U32                     otherUeTotPfsPrio;
   U32                     totBwReq;
   Bool                    currPrioMmbrSta;  /*!< this flag will be set to true when current priority is for CSG UEs */
   U32                     totPrioBwReq;    /*!< Total bandwidth required for GBR+non-GBR LCs of priority UE(CSG/nCSG) */
   U32                     totNonPrioBwReq; /*!< Total bandwidth required for GBR+non-GBR LCs of non-priority UE(CSG/nCSG) */
   U32                     prioUeBwAvail;    /*!< Bandwidth available for non-GBR priority UE(CSG/nCSG) */
   U32                     nonPrioUeBwAvail; /*!< Bandwidth available for non-GBR+ nonpriority UE(CSG/nCSG) */
   U32                     numPrioUe;        /*!< Number of non-GBR LCs in priority UE(CSG/nCSG) */
   U32                     prioUeTotPfsPrio; /*!< total priority for current priority UEs */
} RgSchPfsLcSchdInfo;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __RGPFSX__ */


/**********************************************************************
         End of file:     rg_sch_pfs.x@@/main/2 - Sat Jul 30 02:22:08 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     apany   1. LTE MAC 2.1 release
              rg007.201   ap  1. Added support for MIMO
           rg008.201      sd  1.Removed dependency on MIMO compile-time flag
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
$SID$        ---       rt    1. LTE MAC 4.1 Release.                           
*********************************************************************91*/
