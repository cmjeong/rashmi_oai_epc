

/**********************************************************************
 
    Name:   LTE CL layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE CL
 
    File:   lys.x
 
    Sid:      lys.x@@/main/4 - Tue Aug 30 18:13:51 2011
 
    Prg:    sm
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*                   LTE CL 
*
*/
 
#ifndef __LYS_X__
#define __LYS_X__
/* lys_x_001.main_2: Fix for CID- 1622-02-01 DefectId- 116522 */
/* added preprocessor to check cplusplus support */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ysGenCfg
{
   Pst      lmPst;            /* Layer manager post structure. */
   U16      maxTfuSaps;       /* max number of upper TFU SAPs */
   U16      nmbUe;            /* max number of UEs per Cell */
} YsGenCfg;

typedef enum
{
   LYS_TFU_USR_SAP,
   LYS_TFU_SCH_SAP
} YsTfuSapType;

typedef struct ysTfuSapCfg
{
   Selector     selector;   /* Selector. */
   MemoryId     mem;        /* Region and pool ID. */
   Priority     prior;      /* Priority. */
   ProcId       procId;     /* Processor ID. */
   Ent          ent;        /* Entity ID. */
   Inst         inst;       /* Instance ID. */
   Route        route;      /* Route. */
   SpId         spId;       /* Service provider ID. */
   SuId         suId;       /* Service user ID. */
   YsTfuSapType type;       /* type of the SAP */
   CmLteCellId  cellId;     /* Cell ID */
} YsTfuSapCfg;

typedef struct ysCtfSapCfg
{
   Selector selector;   /* Selector. */
   MemoryId mem;        /* Region and pool ID. */
   Priority prior;      /* Priority. */
   ProcId   procId;     /* Processor ID. */
   Ent      ent;        /* Entity ID. */
   Inst     inst;       /* Instance ID. */
   Route    route;      /* Route. */
   SpId     spId;       /* Service provider ID. */
   SuId     suId;       /* Service user ID. */
} YsCtfSapCfg;

/* This structure holds configuration parameters for CL. */
typedef struct ysCfg
{
   union
   {
      YsGenCfg    genCfg;  /*!< General Configuration. */
      YsTfuSapCfg tfuSap;  /*!< TFU interface SAP. */
      YsCtfSapCfg ctfSap;  /*!< CTF interface SAP. */
   }s;
}YsCfg;

/* This structure holds General statistical information of CL. */
typedef struct ysCtfSapSts
{
   U32 numUeCfg;         /*!< Number of UEs configured. */
   U16 numCellCfg;       /*!< Number of Cells configured. */
}YsCtfSapSts;

typedef struct ysTfuSapSts
{
   U32 numCntrlReqRcvd;     /*!< Number of control request recvd from MAC */
   U32 numDatReqRcvd;       /*!< Number of data request recvd from MAC */
   U32 numRecpReqRcvd;      /*!< Number of reception request recvd from MAC */
}YsTfuSapSts;

/* This structure holds General statistical information of CL. */
typedef struct ysL1PhySts
{
   /* lys_x_001.main_1 */
#ifdef YS_MSPD
   StsCntr          numTxStartReq;    /* Number of PHY_TXSTART.req Txed */
   StsCntr          numTxStartCfm;    /* Number of PHY_TXSTART.cfm Rcvd */
   StsCntr          numTxStartInd;    /* Number of PHY_TXSTART.ind Rcvd */
   StsCntr          numTxSduReq;      /* Number of PHY_TXSDU.req Txed */
   StsCntr          numTxSduCfm;      /* Number of PHY_TXSDU.cfm Rcvd */
   StsCntr          numTxEndInd;      /* Number of PHY_TXEND.ind Rcvd */
   StsCntr          numRxStartReq;    /* Number of PHY_RXSTART.req Txed */
   StsCntr          numRxStartCfm;    /* Number of PHY_RXSTART.cfm Rcvd */
   StsCntr          numRxStartInd;    /* Number of PHY_RXSTART.ind Rcvd */
   StsCntr          numRxSduInd;      /* Number of PHY_RXSDU.ind Rcvd */
   StsCntr          numRxEndInd;      /* Number of PHY_RXEND.ind Rcvd */
   StsCntr          numRxStatusInd;   /* Number of PHY_RXSTATUS.ind Rcvd */
#else
   StsCntr          numSfReqTx;       /* Number of SUBFRAME.request Txed */
   StsCntr          numSfIndRx;       /* Number of SUBFRAME.indication received */
   StsCntr          numHiDciReqTx;    /* Number of HI_DCI.request Txed */
   StsCntr          numTxReqTx;       /* Number of TX.request Txed */
   StsCntr          numHarqIndRx;     /* Number of HARQ.indication received */
   StsCntr          numCrcIndRx;      /* Number of CRC.indication received */
   StsCntr          numRxIndRx;       /* Number of RX.indication received */
   StsCntr          numRachIndRx;     /* Number of RACH.indication received */
   StsCntr          numSrsIndRx;      /* Number of SRS.indication received */
#endif
}YsL1PhySts;

/* This structure holds CL's solicited status information. */
typedef struct ysSts
{
   DateTime dt;             /*!< Date and time. */
   U8       sapInst;        /*!< SAP instance. */
   Action   action;        /*!< ARST : To reset the statistic values. */
   union
   {
      YsCtfSapSts ctfSts;   /*!< CTF SAP statistics. */
      YsTfuSapSts tfuSts;   /*!< TFU SAP statistics. */
      YsL1PhySts  phySts;  /*!< message related statistics */
   }s;
}YsSts;

/* This structure holds a SAP's status information. */
typedef struct ysSapSta
{
   U8 sapState;         /*!< SAP state. */
}YsSapSta;

/* This structure holds CL's solicited status information. */
typedef struct ysSsta
{
   DateTime dt;             /*!< Date and time. */
   U8       sapInst;        /*!< SAP instance. */
   union
   {
      SystemId sysId;       /*!< System information. */
      YsSapSta tfuSapSta;   /*!< TFU SAP state. */
      YsSapSta ctfSapSta;   /*!< CTF SAP state. */
      State    phyState;    /*!< State of PHY */
   }s;
}YsSsta;

/* Alarm diagnostics structure. */
typedef struct ysUstaDgn     /* Alarm diagnostics structure */
{
   U8 type;
   union
   {
      MemoryId          mem;          /* Memory pool and region */
      SpId              sapId;        /* SAP ID on which event received */
      CmLteTimingInfo   timingInfo;   /* Timing information */
   }u;
} YsUstaDgn;

/* This structure holds CL's Unsolicited status information. */
typedef struct ysUsta
{
   CmAlarm   cmAlarm;      /*!< Alarms. */
   YsUstaDgn dgn;          /*!< Alarm diagnostics. */
}YsUsta;

/* This structure holds CL's Trace Indication information. */
typedef struct ysTrc
{
   DateTime dt;          /*!< Date and time. */
   U8       evnt;        /*!< Event. */
}YsTrc;

/* This structure holds CL's Debug Control information. */
typedef struct ysDbgCntrl
{
   U32 dbgMask;          /*!< Debugging mask. */
}YsDbgCntrl;

/* This structure holds CL's SAP Control information. */
typedef struct ysSapCntrl
{
   SuId suId;            /*!< Service user ID. */
   SpId spId;            /*!< Service provider ID. */
}YsSapCntrl;

/* This structure holds CL's Control information. */
typedef struct ysCntrl
{
   DateTime      dt;          /*!< Date and Time. */
   U8            action;      /*!< Action. */
   U8            subAction;   /*!< Sub-action. */
   union
   {
      YsDbgCntrl ysDbgCntrl; /*!< Debug Control. */
      S16        trcLen;     /*!< Trace Length. */
      YsSapCntrl ysSapCntrl; /*!< SAP control. */
      CmLteCellId cellId;    /*!< Cell ID */
   }s;
}YsCntrl; 

/* This structure holds CL Configuration and Control Management Information. */
typedef struct ysMngmt
{
   Header     hdr;       /* Header. */
   CmStatus   cfm;       /* Confirmation. */
   union
   {
      YsCfg   cfg;       /* Configuration. */
      YsSts   sts;       /* Statistics. */
      YsSsta  ssta;      /* Solicited Status. */
      YsUsta  usta;      /* Unsolicited Status. */
      YsTrc   trc;       /* Trace. */
      YsCntrl cntrl;     /* Control. */
   }t;
}YsMngmt;

/* 
   Function Prototype Typedefs 
. */
typedef S16 (*LysCfgReq)     ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *cfg                /* Management Structure. */
     ));


typedef S16 (*LysCfgCfm)     ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *cfg                /* Management Structure. */
     ));

typedef S16 (*LysCntrlReq)   ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *cntrl              /* Management Structure. */
     ));

typedef S16 (*LysCntrlCfm)   ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *cntrl              /* Management Structure. */
     ));

typedef S16 (*LysStaReq)     ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *sta                /* Management Structure. */
     ));

typedef S16 (*LysStaCfm)     ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *sta                /* Management Structure. */
     ));

typedef S16 (*LysStaInd)     ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *sta                /* Management Structure. */
     ));

typedef S16 (*LysStsReq)     ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *sts                /* Management Structure. */
     ));

typedef S16 (*LysStsCfm)     ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *sts                /* Management Structure. */
     ));

typedef S16 (*LysTrcInd)     ARGS((
        Pst        *pst,               /* Post Structure. */
        YsMngmt    *trc,               /* Management Structure. */
        Buffer     *mBuf               /* Message Buffer. */
     ));

/* 
   Function Prototypes 
. */
#ifdef YS
EXTERN S16 YsMiLysCfgReq ARGS((Pst *pst, YsMngmt *cfg));
EXTERN S16 YsMiLysCfgCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 YsMiLysStsReq ARGS((Pst *pst, YsMngmt *sts));
EXTERN S16 YsMiLysStsCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 YsMiLysStaReq ARGS((Pst *pst, YsMngmt *sta));
EXTERN S16 YsMiLysStaCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 YsMiLysStaInd ARGS((Pst *pst, YsMngmt *usta));
EXTERN S16 YsMiLysCntrlReq ARGS((Pst *pst, YsMngmt *cntrl));
EXTERN S16 YsMiLysCntrlCfm ARGS(( Pst *pst, YsMngmt *cfm));
EXTERN S16 YsMiLysTrcInd ARGS((Pst *pst, YsMngmt *trc, Buffer *mBuf));
#endif /* YS. */

#ifdef SM 
EXTERN S16 smYsActvTsk ARGS((Pst *pst, Buffer *mBuf));
/*-- stack manager initialization function ---*/
EXTERN S16 smYsActvInit  ARGS ((Ent ent, Inst inst,
                                Region region, Reason reason));
EXTERN S16 SmMiLysCfgReq ARGS((Pst *pst, YsMngmt *cfg));
EXTERN S16 SmMiLysCfgCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 SmMiLysStsReq ARGS((Pst *pst, YsMngmt *sts));
EXTERN S16 SmMiLysStsCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 SmMiLysStaReq ARGS((Pst *pst, YsMngmt *sta));
EXTERN S16 SmMiLysStaCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 SmMiLysStaInd ARGS((Pst *pst, YsMngmt *usta));
EXTERN S16 SmMiLysCntrlReq ARGS((Pst *pst, YsMngmt *cntrl));
EXTERN S16 SmMiLysCntrlCfm ARGS(( Pst *pst, YsMngmt *cfm));
EXTERN S16 SmMiLysTrcInd ARGS((Pst *pst, YsMngmt *trc, Buffer *mBuf));
#endif /* SM. */

/*
   Function Prototypes for Packing and unpacking the primitives
. */
#ifdef LCLYS
EXTERN S16 cmPkLysCfgReq ARGS((Pst *pst, YsMngmt *cfg));
EXTERN S16 cmPkLysCfgCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 cmPkLysStsReq ARGS((Pst *pst, YsMngmt *sts));
EXTERN S16 cmPkLysStsCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 cmPkLysStaReq ARGS((Pst *pst, YsMngmt *sta));
EXTERN S16 cmPkLysStaCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 cmPkLysStaInd ARGS((Pst *pst, YsMngmt *usta));
EXTERN S16 cmPkLysCntrlReq ARGS((Pst *pst, YsMngmt *cntrl));
EXTERN S16 cmPkLysCntrlCfm ARGS(( Pst *pst, YsMngmt *cfm));
EXTERN S16 cmPkLysTrcInd ARGS((Pst *pst, YsMngmt *trc, Buffer *mBuf));


EXTERN S16 cmUnpkLysCfgReq ARGS((LysCfgReq ,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLysCfgCfm ARGS((LysCfgCfm ,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLysStsReq ARGS((LysStsReq,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLysStsCfm ARGS((LysStsCfm,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLysStaReq ARGS((LysStaReq,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLysStaCfm ARGS((LysStaCfm,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLysStaInd ARGS((LysStaInd,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLysCntrlReq ARGS((LysCntrlReq,Pst *pst,Buffer *mBuf));
EXTERN S16 cmUnpkLysCntrlCfm ARGS((LysCntrlCfm,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLysTrcInd ARGS((LysTrcInd,Pst *pst,Buffer *mBuf));

/*
   Prototypes for Packing and Unpacking the definitions 
. */

EXTERN S16 cmPkYsMngmt ARGS((Pst *pst, YsMngmt *req,U8 eventType, Buffer *mBuf));
EXTERN S16 cmPkYsGenCfg ARGS((YsGenCfg *cfg,Buffer *mBuf));
EXTERN S16 cmPkYsTfuSapCfg ARGS(( YsTfuSapCfg *cfg, Buffer *mBuf));
EXTERN S16 cmPkYsCtfSapCfg ARGS((YsCtfSapCfg *cfg, Buffer *mBuf));
EXTERN S16 cmPkYsCfg ARGS((YsCfg *cfg, S16 elmnt, Buffer *mBuf));
EXTERN S16 cmPkYsCtfSapSts ARGS((YsCtfSapSts *sts, Buffer *mBuf));
EXTERN S16 cmPkYsTfuSapSts ARGS((YsTfuSapSts *sts, Buffer *mBuf));
EXTERN S16 cmPkYsPhySts ARGS((YsL1PhySts *cfg, Buffer *mBuf));
EXTERN S16 cmPkYsSts ARGS((YsSts *sts, S16 elmnt,Buffer *mBuf));
EXTERN S16 cmPkYsSapSta ARGS((YsSapSta *sta, Buffer *mBuf));
/* lys_x_001.main_3: ccpu00118324 eventtype passed as arg */
EXTERN S16 cmPkYsSsta ARGS((Pst *pst, YsSsta *ssta,S16 elmnt,U8 eventType, Buffer *mBuf));
EXTERN S16 cmPkYsUstaDgn ARGS((YsUstaDgn *param, Buffer *mBuf));
EXTERN S16 cmPkYsUsta ARGS((YsUsta *usta, Buffer *mBuf));
EXTERN S16 cmPkYsTrc ARGS((YsTrc *trc,Buffer *mBuf));
EXTERN S16 cmPkYsDbgCntrl ARGS((YsDbgCntrl *cntrl, Buffer *mBuf));
EXTERN S16 cmPkYsSapCntrl ARGS((YsSapCntrl *cntrl, Buffer *mBuf));
EXTERN S16 cmPkYsCntrl ARGS((YsCntrl *cntrl, S16 elmnt, Buffer *mBuf));

EXTERN S16 cmUnpkYsMngmt ARGS((Pst *pst, YsMngmt *req,U8 eventType, Buffer *mBuf));
EXTERN S16 cmUnpkYsGenCfg ARGS((YsGenCfg *cfg,Buffer *mBuf));
EXTERN S16 cmUnpkYsTfuSapCfg ARGS(( YsTfuSapCfg *cfg, Buffer *mBuf));
EXTERN S16 cmUnpkYsCtfSapCfg ARGS((YsCtfSapCfg *cfg, Buffer *mBuf));
EXTERN S16 cmUnpkYsCfg ARGS((YsCfg *cfg, S16 elmnt, Buffer *mBuf));
EXTERN S16 cmUnpkYsCtfSapSts ARGS((YsCtfSapSts *sts, Buffer *mBuf));
EXTERN S16 cmUnpkYsTfuSapSts ARGS((YsTfuSapSts *sts, Buffer *mBuf));
EXTERN S16 cmUnpkYsPhySts ARGS((YsL1PhySts *cfg, Buffer *mBuf));
EXTERN S16 cmUnpkYsSts ARGS((YsSts *sts, S16 elmnt,Buffer *mBuf));
EXTERN S16 cmUnpkYsSapSta ARGS((YsSapSta *sta, Buffer *mBuf));
EXTERN S16 cmUnpkYsSsta ARGS((Pst *pst, YsSsta *ssta,S16 elmnt, Buffer *mBuf));
EXTERN S16 cmUnpkYsUstaDgn ARGS(( YsUstaDgn *param, Buffer *mBuf));
EXTERN S16 cmUnpkYsUsta ARGS((YsUsta *usta, Buffer *mBuf));
EXTERN S16 cmUnpkYsTrc ARGS((YsTrc *trc,Buffer *mBuf));
EXTERN S16 cmUnpkYsDbgCntrl ARGS((YsDbgCntrl *cntrl, Buffer *mBuf));
EXTERN S16 cmUnpkYsSapCntrl ARGS((YsSapCntrl *cntrl, Buffer *mBuf));
EXTERN S16 cmUnpkYsCntrl ARGS((YsCntrl *cntrl, S16 elmnt, Buffer *mBuf));
#endif 
#ifdef __cplusplus
}
#endif
#endif /* __LYS_X__. */


/**********************************************************************
         End of file:     lys.x@@/main/4 - Tue Aug 30 18:13:51 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     ys               1. Initial Release.
/main/2      ---      lys_x_001.main_1 apany      1. Additional PHY stats info
/main/3      ---      lys_x_001.main_2 ms  1. added preprocessor to support cplusplus
/main/4      ---    lys_x_001.main_3   ms  1. eventtype passed as arg.
*********************************************************************91*/

