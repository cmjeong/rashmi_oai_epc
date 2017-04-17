

/********************************************************************20**

     Name:     sb_acc.x - Acceptance Tests Typedefs for the SCTP layer

     Type:     C include file

     Desc:     typedefs and function prototypes required by the
               SCTP layer acceptance tests

     File:     sb_acc.x

     Sid:      sb_acc.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:05 2015

     Prg:      nct

*********************************************************************21*/
#ifndef __SBACCX__
#define __SBACCX__

/*

*   sb_acc.x -
*
*   typedefs and function prototypes declared in this file correspond to
*   typedefs function prototypes used by the following TRILLIUM software:
*     part no.                      description
*     --------    ----------------------------------------------
*     1000163                      SCTP layer
*/

/*
*     this software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000163                      SCTP layer
*/

/* typedefs */

/********************************************************************30**/


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _sbOperQElm
{
   struct
        {
          SuId           suId;           /* service user SAP ID */
          SpId           spId;           /* service provider SAP ID */
          UConnId        suEndpId;       /* service user endpoint ID */
          UConnId        spEndpId;        /* service provider endpoint ID */
          U16            port;           /* port number */
          UConnId        spAssocId;      /* service provider association ID */
          UConnId        suAssocId;      /* service user association ID */
          UConnId        assocId;        /* association ID */
          SctStrmId      remInstrms;     /* incoming streams  */
          SctNetAddrLst  peerNAddrLst;   /* dest. IP address list */
          CmNetAddr      priPeerNAddr;   /* primary dest. network address */
		  CmNetAddr      peerNAddr;     /* destination address */
		  SctVSInfo      *vsInfo;        /* vendor specific buildPar */
		  U16            peerPort;        /* dest. port number */
		  SctStrmId      outStrms;       /* incoming streams  */
		  U8             assocIdType;    /* association ID type */
		  SctRtrvInfo    rtrvInfo;      /* Dg retrieval buildPar */
		  SctStrmId      strmId;         /* stream ID */
		  SctDatIndType  indType;       /* data indication type */
		  Buffer         *mBuf;          /* message buffer  */
		  U8             staType;        /* status type */
		  SctStaInfo     staInfo;        /* staInfo */
		  SctResult      result;         /* result */
		  SctCause       cause;          /* cause */
		  SctStatus      status;         /* status*/
		  Reason         reason;         /* reason */
		  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
		  U32           protId;          /* protocol ID */
#endif
		  SctAssocIndParams  assocParams;   /* paramaters for the association indication */
		} it;                           /* upper layer parameters */

   struct
        {
          SuId           suId;           /* service user SAP ID */
          SpId           spId;           /* service provider SAP ID */
          Reason         reason;         /* Reason */
          U8             status;         /* status */
          CmTptAddr      localTAddr;      /* transport address of the server */
          CmTptAddr      peerTAddr;      /* remote address */
          Buffer         *mBuf;          /* message buffer */
          U8             choice;         /* choice parameter */
          UConnId        conId;         /* connection ID */
          UConnId        suConId;       /* service user connection ID */
          UConnId        spConId;       /* service user connection ID */
          U8             srvcType;       /* service type */
          CmIpHdrParm    hdrParm;      /* header parameters */
          Action         action;         /* Action */
        } hi;                            /* lower layer parameters */

   }SbOperQElm;

typedef struct _sbMgmtQElm                /* management structure of sctp */
{
   TranId            transId;            /* id of transaction */
   ElmntId           elmId;              /* which element - for cfg, sts and sta */
   CmStatus          cfm;                /* confirm status */

   union
   {
        struct
        {
          SpId       sapId;              /* Sap Id */
          U16        event;              /* alarm event */
          U16        category;           /* alarm category */
          U16        cause;              /* alarm cause */
#ifdef SB_RUG
          Pst        pst;                /* Pst passed */
#endif /* SB_RUG */
        } usta;                          /* unsolicited status, alarm detail */

        struct
        {
          SuId       sapId;              /* which element */
          U8         evnt;               /* event */
          U16        len;                /* trace length */
          U8         evntParm[PRNTSZE];  /* event parameters */
        } trc;                            /* trace */


        struct
        {
          SpId       sapId;              /* SAP Id */
          U8         action;             /* main action */
          U8         subAction;          /* subaction */
          U32        sbTrc;              /* trace mask */
#ifdef DEBUGP
          U32        sbDbg;              /* debug mask */
#endif
        } cntrl;                         /* control */

        struct
        {
          SpId            sapId;                 /* which element */

          union
          {
              SbGenSts      genSts;     /* overall layer Statistics */
              SbSctSapSts   sctSts;     /* SCTSAP Statistics */
              SbTSapSts     tSts;       /* TSAP Statistics */
          } u;
        } sts;                          /* statistics */

        struct
        {
          union
          {
              SystemId      sysId;    /* system ID */
              SbSapSta      sapSta;   /* SCTP upper/lower Sap status */
              SbGenSta      genSta;   /* General status */
              SbAssocSta    assocSta; /* Association status */
              SbDtaSta      dtaSta;   /* Destination transport address status */
/* sb012.103: Replaced the SB_ACC flag with LSB12 */
#ifdef LSB12
              SbTmrSta      tmrSta;   /* Timer statistics */
#endif  /* LSB12 */
          } s;
        } ssta;                       /* solicited status */
   }s;
}SbMgmtQElm;

/* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
typedef struct _sbShtQElm                /* management structure of sctp */
{
   TranId            transId;            /* id of transaction */
   ElmntId           elmId;              /* which element */
   CmStatus          cfm;                /* confirm status */
   ShtCntrlCfmEvnt   cfmInfo;            /* EVTSHTCNTRLCFM */
}SbShtQElm;
#endif /* SB_RUG */

/* Message Queue Element */
typedef struct _sbAccMsgQElm
{
   U8 evntType;

   union
   {
      SbMgmtQElm    mgmtMsg;
      SbOperQElm    sbMsg;
/* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
      SbShtQElm     shtMsg;
#endif /* SB_RUG */
   }t;

} SbAccMsgQElm;


/*Structure for parameters necessary for building of chunks */
typedef struct _sbAccChunkBld
 {
/* SATELLITE SCTP feature */ 
    /* sb003.103 - addition - flags to indicate if to expect ECNE with SACK
     * and CWR with DATA chunks.
     */
#ifdef SB_ECN 
    Bool           expectEcne;               
    Bool           expectCwr;
    U32            lowestTsn;                /* the lowest tsn number received
                                              *  in CWR/ECNE chunk
                                              */
#endif
   SctCause        cause;                    /* Cause for error */
   SctStatus       status;                   /* Status of chunk check */
   SctResult       result;                   /* Result of chunk check */
   Bool            extLifetimeFlg;           /* Request for extended lifetime */
   SctStrmId       outStrms;                 /* number of desired outStrms */
   SctStrmId       inStrms;                  /* number of desired inStrms */
   Data            cookie[MSG_SIZE];         /* the encryption cookie */
   U32             arwnd;
   U32             rwnd;
   U8              chunkId;                  /* use to differentiate between Abort and ERROR chunks */
   U16             chunkLeng;                /* length of the chunk */
   U16             causeCode;                /* code of the ERROR and ABORT chunk */
   U16             streamId;                 /* stream identifier */
   U32             numMisPar;                /* number of missing parameters for ABORT/ERROR chunk */
   U16             misPar[MAXPARVAL];        /* missing parameter type specified */
   U16             numFrag;                  /* number of fragments acknowledged */
   U16             fragStart[MAXFRAGSACK];   /* TSN number at start of fragment */
   U16             fragEnd[MAXFRAGSACK];     /* TSN number at end of fragment */
   U32             cumTsn;                   /* cumulative TSN Ack */
   U32             tsn;                      /* the initial tsn number received in INIT chunk */
   U16             seqNr;                    /* stream sequence number */
   Bool            unOrderFlg;               /* specify whether datagrams should be received in order */
   Data            hBeatInfo[MSG_SIZE];      /* information for the HBeat chunk */
   U16             hBeatInfoLen;             /* length of the hBeat info */
   Bool            misChunk;                 /* Flag to use when a missing chunk is required */
   Bool            misCookie;
   Bool            newITag;
/* RFC 4460 -- SB_RFC_2, SB_RFC_10 */
   Bool            newAddr;
/* RFC 4460 -- SB_RFC_2, SB_RFC_10 */
   Bool            multHBParam;
   Bool            noData;
   Bool            pkUnknownPar;             /* pack Unknown parameter within INIT with MS 2 bits set to 01 */

   U8              chunkFlg;
   Bool            noBundleFlg;              /* set this flag if no data bundling is expected in the transfer */
   U16             nmbDup;                  /* the number of duplicates received in the SACK */
   Bool            unrecogParFound;
   Bool            hstNamePrsnt;            /* SB_VER13 - hostname present flag  */
  /* sb035.103: modified hostName array length to 264 for testcases 
   * case O.201.26, O.201.27, O.201.28 and O.202.21
   */  
   U8              hostName[264];            /* hostname */
   /* RFC 4460: Acceptance test */
   Bool            ipv4AddrFound;            /* IPv4 Address Found */
   Bool            ipv6AddrFound;            /* IPv6 Address Found */
   Bool            multAddrTypes;            /* Include multiple address types */
   Bool            pkUnrecogPar;             /* Pack unrecognised parameter in INIT */
   U8              suppAddrTypes;            /* Supported address types */
                                             /* 0:none, 1:ipv4, 2:ipv6, 3:ipv4&ipv6 */
   Bool            usrITag;                  /* User specified init Tag */
   SctPort         peerPort;                 /* Peer port */
   U32             iTag;                     /* Init Tag value */
   U32             vTag;                     /* verification Tag */
}SbAccChunkBld;


/* Structure for each association */
typedef struct  _sbAccAssoc
{
   SpId            spId;                    /* Service Provider Id */
   SuId            suId;                    /* Service User Id */
   UConnId         spEndpId;                /* Service Provider Id */
   UConnId         suEndpId;                /* Service User Id */
   UConnId         suAssocId;               /* service user association ID */
   UConnId         spAssocId;               /* service provider association ID */
   UConnId         spConId;                 /* service provider connection ID */
   UConnId         suConId;                 /* service user connection ID */
   SctPort         peerPort;                 /* Destination port number */
   SctPort         localPort;                 /* Source Port of the association */
   SctStrmId       outStrms;                /* Number of outstreams required */
   SctNetAddrLst   localNAddrLst;             /* Dest Network Addres list */
   SctNetAddrLst   peerNAddrLst;             /* Source Network Addres list */
   CmNetAddr       priPeerNAddr;             /* Primary destination address */
   CmNetAddr       localNAddr;               /* Source address to receive data on */
   CmTptAddr       localTAddr;                /* Transport source address of the association  */
   CmTptAddr       peerTAddr;                /* Remote transport address */
   U32             verTagLoc;               /* Store the local verification tag used for chunks in the association */
   U32             verTagPeer;              /* Store the verification tag found with all datagrams from the peer   */
   Data            cookie[SB_MAX_LEN];        /* Cookie associated with this association */
   U16             cookieLeng;
   /* sb032.102 :  IPV6 Support Added */
#ifdef LOCAL_INTF
   CmTptLocalInf   localIf;                 /*Local interface address for TUCL interface change */
#endif
}SbAccAssoc;

/* Message Queue structure */
typedef struct _sbAccMsgQ
{
   SbAccMsgQElm    q[SB_ACC_MSG_QSIZE];     /* Message Queue */
   U16             rdPtr;                   /* Next queue location to read */
   U16             wrPtr;                   /* Next queue location to write in */
}SbAccMsgQ;

/* Test context informative */
typedef struct _sbAccTest
{
   U8             state;                /* State of the test case */
   U8             subTest;              /* Current subtest 108.06 a) of test case */
   U8             numSubTst;            /* The number of subtests in the test +1 */
   U8             subTestsPass;         /* Number of subtest passed */
   U8             subTestsFail;         /* Number of subtest failed */
   Bool           bCompleted;           /* Set when test completed - after cleanup */
   Bool           bTestsCompleted;      /* Set when test or all subtests completed */
   Bool           bBusyPreTestConf;     /* Set for pre-test config */
   Bool           bBusySubtest;         /* Set when test or subtest is busy */
   Bool           bConfigDeleted;       /* Set when config deleted successfully */
   Bool           bBusyCleanup;         /* Busy with cleanup after subtest/test */
   U8             bConfigMask;          /* Complete all Gen - bit 0, Sct Sap - bit 1, TSap = bit 2  configs */
   U8             bSctSapCfgMask;       /* SAPCFG_0 - bit 0, SAPCFG_1 - bit 1, SAPCFG_2 - bit 2 */
   U8             bTSapCfgMask;         /* TSAPCFG_0 - bit 0, TSAPCFG_1 - bit 1 */
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
   U8             bPathProfCfgMask;     /*  */
   U8             bPathProfMask;        /*  */
   U8             bDestAddrCfgMask;     /*  */
   U8             bDestAddrMask;        /*  */
#endif
   U8             bSapMask;             /* Mask of bound SctSAPs */
   U8             bTSapMask;            /* Mask of bound TSAPs */
   U8             bEndpMask;            /* Endpoint 1, Endpoint 2, etc. */
   U8             bAssocMask;           /* Assoc 1, Assoc 2, etc. */
   U8             bAssocSetupMask;      /* set if assocMask has been set up */
   U8             bTraceMask;           /* set if trace mask is deactivated */
   U8             bDebugPMask;          /* if set debug printing have been enabled */
   U8             bTickMask;            /* tick this off if a specific list of events should occur */
   Bool           tickLstDoneFlg;       /* set if all the ticks have been completed or if n/a */
   CmTptAddr      localTAddr;           /* transport address of the server */
   UConnId        suConId;             /* service user connection ID */
   UConnId        spConId;             /* service user connection ID */
   TranId         curTransId;           /* Set when pre test config completed */
   Bool           prntFlag;             /* Prints enable/disable flag */
   Buffer         *gmBuf;               /* Buffer used to check DatInd/ StaInd / UDatReq packets */
   Data           datRcv[SB_MAX_LEN];   /* Array used to build the received data */
   MsgLen         datRcvLen;            /*lenght of the received structure */
   Event          evtType;              /* the type of the return primitive expected */
   U32            delay;                /* user adjustable value of the delay of verify message */
   /* sb032.102 :  IPV6 Support Added */
   U8             addrType;             /* address type to check whether it is IPV4 or IPV6 */

}SbAccTest;

typedef S16 (*SbAccPFS16)    ARGS((Void));


typedef struct _sbTestCb
{
   SbAccPFS16   testFunc;                   /* function pointer to actual test */
   U8           testId[ACC_TSTIDSZE];       /* current test id - ASCIIZ string */
} SbTestCb;


/* static version: size 6,444 bytes */
typedef struct _sbTestCbTbl
{
   SbTestCb     tstMatrix[ACC_TSTTBLROWS][ACC_TSTTBLROWSIZE];
                                            /* 2D Test matrix with variable length rows */
   U32          rowlength[ACC_TSTTBLROWS];  /* length of each row */
   U32          numrows;                    /* number of rows in matrix */
} SbTestCbTbl;


/* Static version */
typedef struct _sbTestSeqLst
{
   SbTestCb   *list[ACC_TSTSEQLEN];
                                /* 1D array of pointers to test control blocks */
   U32        index;            /* Current index in the test sequence list */
   U32        length;           /* length of array  */
} SbTestSeqLst;


/* Acceptance test control block */
/* Static SbAccCb is 747kb */
typedef struct _SbAccCb
{
   TskInit      init;
   Bool         testFlg;                    /* FALSE when all tests are done */
   Bool         tcFlg;                      /* coupling flag */
   U16          testsRun;
   U16          testsPass;
   U16          testsFail;
   U32          cycleCntr;                  /* counter for cycle number */
   Pst          smPst;                      /* From Layer manager to sb */
#ifdef SB_FTHA
   Pst          shtPst;                     /* From SHT to sb */
#endif /* SB_FTHA */
   Pst          itPst;                      /* From upper layer to the sb */
   Pst          hiPst;                      /* From the Lower layer to the sb */
   SbAccMsgQ    msgQ;                       /* message queue */
   SbTestCbTbl  C100tstTbl;                 /* test table structure */
   SbTestCbTbl  O100tstTbl;                 /* test table structure */
   SbTestCbTbl  O200tstTbl;                 /* test table structure */
   SbTestCbTbl  O300tstTbl;                 /* test table structure */
   SbTestCbTbl  O400tstTbl;                 /* test table structure */
   SbTestCbTbl  M100tstTbl;                 /* test table structure */
   SbTestCbTbl  M200tstTbl;                 /* test table structure */
   SbTestCbTbl  M300tstTbl;                 /* test table structure */
   SbTestCbTbl  M400tstTbl;                 /* test table structure */
   SbTestSeqLst tstLst;                     /* sequence list of tests to run */
   SbAccTest    curTst;                     /* Current test context */
   SLockId      qlock;                      /* Message queue semaphore  */
   Bool         snoozeFlg;                  /* Flag that could halt the process until DDD signals */
   SSTskId      sbTskId;                    /* SCTP layer TAPA task ID */
   SSTskId      tstTskId;                   /* Test code TAPA task ID */
   /* sb044.102: added for changes in protocol layer. Now DNS open request *
    * will be called if DNS is configured in TSAP                          */
   Bool         useDnsFlag;
} SbAccCb;

typedef struct _tstRsltStruct
{
   U8           testsPass;         /* Number of subtest passed */
   U8           testsFail;         /* Number of subtest failed */
} TstRsltStruct;

EXTERN SbAccCb sbAccCb;
EXTERN CmIpv4NetAddr localNAddrLst_1[];
EXTERN CmIpv4NetAddr localNAddrLst_2[];
EXTERN CmIpv4NetAddr peerNAddrLst_1[];
EXTERN CmIpv4NetAddr peerNAddrLst_2[];

/* Externs for sb_acc1 */
EXTERN Void sbAccDispErrTstRslt ARGS((char testNr[MSG_SIZE], U8 subTest,
                                      Event evnt, SctStatus status, U16 reason));
EXTERN PUBLIC Void sbGetLmPst ARGS((Pst *lmPst));
EXTERN Void sbAccVfyMsg ARGS((SctStatus *status));
EXTERN Void sbSetTimeoutCntr ARGS((U32 timeout));
EXTERN S16 sbAccPopMsg ARGS((SbAccMsgQElm **msg));
EXTERN S16 sbAccPushMsg ARGS((SbAccMsgQElm *msg));
EXTERN Void sbAccFlushQ ARGS((Void));
EXTERN S16 sbAccPeekMsg ARGS((SbAccMsgQElm  **msg));

#ifdef SS_MULTIPLE_PROCS
EXTERN S16 sbAccActvTmr ARGS((ProcId proc, Ent ent, Inst inst));
#else
EXTERN S16 sbAccActvTmr ARGS(( Void ));
#endif /* SS_MULTIPLE_PROCS */

EXTERN S16 rdConQ ARGS((Data data));
EXTERN S16 sbPermTsk(Pst *pst, Buffer *mBuf);
EXTERN Void sbTblAddTestIndex(SbTestCbTbl *tstTbl);
EXTERN Void sbTblAddTestSubIndex(SbTestCbTbl *tstTbl, SbTestCb *tstCb);
EXTERN Void sbLstAddTest(SbTestCb *tstCb);
EXTERN Void sbInitTstTbl(Void);
EXTERN Void sbRunTest(S8 *test);
EXTERN S16 sbInitAccCb(Void);
EXTERN S16 sbParseCfg(Void);
EXTERN S16 sbParseLine(S8 *line);
EXTERN S16 sbAddAllTst(Void);

/* Externs for sb_acc2 */
EXTERN Void setBit ARGS ((U8 *bitVar, U8 bitMask));
EXTERN U8 isBitSet ARGS ((U8 bitVar, U8 bitMask));
EXTERN S16 sbGetPacket ARGS ((Buffer **mBuf, U16 action, MsgLen par1));
EXTERN Void doCleanup ARGS ((void));
EXTERN Void sbShutdownOper ARGS((void));


EXTERN  S16 chkInitChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkInitAckChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkCookieChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkCookieAckChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkAbortErrChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkDataChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkSHBeatChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkShutdwnAckChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkShutdwnChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkSackChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  S16 chkHBeatChunk ARGS((Buffer  *mBuf,  SbAccChunkBld  *buildPar,  SbAccAssoc *assoc));
/* RFC 4460 */
EXTERN  S16 chkHBeatAckChunk ARGS((Buffer  *mBuf,  SbAccChunkBld  *buildPar,  SbAccAssoc *assoc));
/* SATELLITE SCTP feature */ 
/* sb003.103 - addition - function prototypes to check the ECNE and CWR chunks
 * */
#ifdef SB_ECN
EXTERN  S16 chkEcneChunk ARGS((Buffer  *mBuf,  SbAccChunkBld  *buildPar,  SbAccAssoc *assoc));
EXTERN  S16 chkCwrChunk ARGS((Buffer  *mBuf,  SbAccChunkBld  *buildPar,  SbAccAssoc *assoc));
#endif /* SB_ECN */
EXTERN  Void buildUnrecogChunk  ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));

EXTERN  Void buildInitChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildInitAckChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildCookieChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildCookieAckChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
/* sb028.103: Added a new function to process tha data chunk bundled with
              Cookie chunk */
EXTERN  Void buildCookieWitDatChunk ARGS((Buffer  *mBuf,SbAccChunkBld  *buildPar,SbAccAssoc  *assoc));
/* sb030.103: Added new function to process the ABORT chunk bundled with COOKIE */
EXTERN  Void buildCookieWithAbortChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildAbortErrChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildDataChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
/* sb013.103: New function to build data chunk with size 512 */
EXTERN  Void buildLargeDataChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
/* sb012.103: Added new function to build init chunk for non-unicast address */
EXTERN  Void buildInitChunkUnicast ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
/* SATELLITE SCTP feature */ 
/* sb003.103 - addition - prototype added */
#ifdef SB_ECN
EXTERN  Void buildDataCwrChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildSackEcneChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
/* sb014.103: New function to build ECNE Chunk */
EXTERN  Void buildEcneChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
#endif /* SB_ECN */
EXTERN  Void buildSHBeatChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildShutdwnAckChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildShutdwnChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildShutdwnCmplChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
EXTERN  Void buildSackChunk ARGS ((Buffer  *mBuf,  SbAccChunkBld  *buildPar, SbAccAssoc  *assoc));
PUBLIC  Void buildHBeatAckChunk ARGS ((Buffer  *mBuf, SbAccChunkBld  *buildPar, SbAccAssoc  *assoc ));
/* RFC 4460 */
PUBLIC  Void buildHBeatChunk ARGS ((Buffer  *mBuf, SbAccChunkBld  *buildPar, SbAccAssoc  *assoc ));

EXTERN  S16 sbLsbChkCfm ARGS ((SbMgmtQElm  *mgmtMsg, SctStatus  *status, Reason   *reason, U8    evnt));
EXTERN  S16 sbLsbChkTmr ARGS ((SbMgmtQElm  *mgmtMsg, SctStatus  *status, Reason *reason, U8 tmrType, Bool state));
EXTERN  S16 sbHitChkUDatReq ARGS((SbOperQElm *sbMsg, SbMgmtQElm  *mgmtMsg,SbAccChunkBld  *buildPar,
            SbAccAssoc  *assoc, SctStatus  *status));
EXTERN  S16 sbHitChkMuxUDatReq ARGS((SbOperQElm *sbMsg, SbMgmtQElm  *mgmtMsg,SbAccChunkBld  *buildPar,
            SbAccAssoc  *assoc, SctStatus  *status));
EXTERN S16 sbHitChkReq ARGS((SbOperQElm  *sbMsg, SbMgmtQElm  *mgmtMsg, U8  evnt, SctStatus  *status, Reason *reason));
EXTERN S16 sbSctChkCfm ARGS((SbOperQElm  *sbMsg, SbMgmtQElm  *mgmtMsg, U8 evnt, SctStatus   *status, Reason *reason));
EXTERN Void sbDeleteAllConfig ARGS ((void));
EXTERN Void setResponse ARGS ((Resp *resp));
EXTERN Void sbStdGenCfg ARGS ((SbMgmt *sbCfgPtr));
/* SATELLITE SCTP feature */ 
/* sb003.103 - addition - */
#ifdef SB_SATELLITE
EXTERN Void sbStdPathProfCfg ARGS ((SbMgmt *sbCfgPtr));
EXTERN Void sbStdDstAddrCfg ARGS ((SbMgmt *sbCfgPtr));
#endif /* SB_SATELLITE */
EXTERN Void sbStdSctSapCfg ARGS ((SbMgmt *sbCfgPtr, U8 specCfg));
EXTERN Void sbStdTSapCfg ARGS ((SbMgmt *sbCfgPtr, U8  specCfg));
EXTERN Void sbSendConfigReq ARGS ((SbMgmt *sbCfgPtr, U8 type, U8  specCfg ));
EXTERN Void sbSendSctBndReq ARGS ((SuId suId,SpId spId));
EXTERN Void sbSendHitBndReq ARGS ((SuId suId,SpId spId));
EXTERN Void sbSendEndpOpenReq ARGS ((SbAccAssoc *assoc));
EXTERN Void setupAssocSnd ARGS((SbAccAssoc *assoc, SbAccChunkBld *buildPar));
EXTERN Void sbDisAbleTrace ARGS((SbMgmt   *sbStaPtr));
EXTERN Void sbEnableDebugP ARGS(( U32  dbgMask));
EXTERN Void setupAssoc ARGS((SbAccAssoc *assoc, U8 assocNum));
EXTERN Void sbSendMulEndpOpenReq ARGS(( SbAccAssoc *assoc, U8 endpId));

/* sb014.103: function to calculate number of ticks */
EXTERN S16 sbAccCalcTicks ARGS((S16 resTime));

/* Externs for sb_act1 */
EXTERN S16 sbC100_01 ARGS ((void));
EXTERN S16 sbC100_02 ARGS ((void));
EXTERN S16 sbC100_03 ARGS ((void));
EXTERN S16 sbC100_04 ARGS ((void));
EXTERN S16 sbC100_05 ARGS ((void));
EXTERN S16 sbC100_06 ARGS ((void));
EXTERN S16 sbC100_07 ARGS ((void));
EXTERN S16 sbC100_08 ARGS ((void));
EXTERN S16 sbC100_09 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbC100_10 ARGS ((void));    /* IPV6 test case */
EXTERN S16 sbC101_01 ARGS ((void));
EXTERN S16 sbC101_02 ARGS ((void));
EXTERN S16 sbC101_03 ARGS ((void));
EXTERN S16 sbC101_04 ARGS ((void));
EXTERN S16 sbC101_05 ARGS ((void));
EXTERN S16 sbC101_06 ARGS ((void));
EXTERN S16 sbC101_07 ARGS ((void));
EXTERN S16 sbC101_08 ARGS ((void));
EXTERN S16 sbC101_09 ARGS ((void));
EXTERN S16 sbC101_10 ARGS ((void));
EXTERN S16 sbC101_11 ARGS ((void));
EXTERN S16 sbC101_12 ARGS ((void));
EXTERN S16 sbC101_13 ARGS ((void));
EXTERN S16 sbC102_01 ARGS ((void));
EXTERN S16 sbC102_02 ARGS ((void));
EXTERN S16 sbC102_03 ARGS ((void));
EXTERN S16 sbC102_04 ARGS ((void));
EXTERN S16 sbC102_05 ARGS ((void));
EXTERN S16 sbC102_06 ARGS ((void));
EXTERN S16 sbC102_07 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbC102_08 ARGS ((void));   /* IPV6 test case */
/* SATELLITE SCTP feature */ 
/* sb003.103 - addition - prototypes for new test cases for path profile */
#ifdef SB_SATELLITE
EXTERN S16 sbC103_01 ARGS ((void));
EXTERN S16 sbC103_02 ARGS ((void));
EXTERN S16 sbC103_03 ARGS ((void));
EXTERN S16 sbC103_04 ARGS ((void));
EXTERN S16 sbC103_05 ARGS ((void));
EXTERN S16 sbC103_06 ARGS ((void));
EXTERN S16 sbC103_07 ARGS ((void));
EXTERN S16 sbC103_08 ARGS ((void));
EXTERN S16 sbC103_09 ARGS ((void));
EXTERN S16 sbC103_10 ARGS ((void));
EXTERN S16 sbC103_11 ARGS ((void));
EXTERN S16 sbC103_12 ARGS ((void));
EXTERN S16 sbC103_13 ARGS ((void));
EXTERN S16 sbC103_14 ARGS ((void));
EXTERN S16 sbC103_15 ARGS ((void));
EXTERN S16 sbC103_16 ARGS ((void));
EXTERN S16 sbC103_17 ARGS ((void));

/* sb003.103 - addition - prototypes for new test cases for Destination Address */
EXTERN S16 sbC104_01 ARGS ((void));
EXTERN S16 sbC104_02 ARGS ((void));
#endif /* SB_SATELLITE */

/* Externs for sb_act3 */
EXTERN S16 sbO100_01 ARGS ((void));
EXTERN S16 sbO100_02 ARGS ((void));
EXTERN S16 sbO100_03 ARGS ((void));
EXTERN S16 sbO100_04 ARGS ((void));
EXTERN S16 sbO100_05 ARGS ((void));
EXTERN S16 sbO100_06 ARGS ((void));
EXTERN S16 sbO100_07 ARGS ((void));
EXTERN S16 sbO101_01 ARGS ((void));
EXTERN S16 sbO101_02 ARGS ((void));
EXTERN S16 sbO101_03 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO101_04 ARGS ((void)); /*IPV6 test case */
#ifdef SB_FTHA 
EXTERN S16 sbO101_05 ARGS ((void));
EXTERN S16 sbO101_11 ARGS ((void));
#endif /* SB_FTHA */
#ifdef SB_RUG 
EXTERN S16 sbO101_06 ARGS ((void));
EXTERN S16 sbO101_07 ARGS ((void));
EXTERN S16 sbO101_08 ARGS ((void));
EXTERN S16 sbO101_09 ARGS ((void));
EXTERN S16 sbO101_10 ARGS ((void));
#endif /* SB_RUG */

EXTERN S16 sbO102_01 ARGS ((void));
EXTERN S16 sbO102_02 ARGS ((void));
EXTERN S16 sbO102_03 ARGS ((void));
EXTERN S16 sbO102_04 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO102_05 ARGS ((void)); /* IPV6 test case */
EXTERN S16 sbO102_06 ARGS ((void)); /* IPV6 test case */
#ifdef SB_FTHA 
EXTERN S16 sbO102_07 ARGS ((void)); /* SHT test case */
EXTERN S16 sbO102_08 ARGS ((void)); /* SHT test case */
#endif /* SB_FTHA */


EXTERN S16 sbO200_01 ARGS ((void));
EXTERN S16 sbO200_02 ARGS ((void));
EXTERN S16 sbO200_03 ARGS ((void));
EXTERN S16 sbO200_04 ARGS ((void));
EXTERN S16 sbO200_05 ARGS ((void));
EXTERN S16 sbO200_06 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO200_07 ARGS ((void));/* IPV6 test case */
EXTERN S16 sbO200_08 ARGS ((void));/* IPV6 test case */
/* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 sbO200_09 ARGS ((void));
#endif /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 sbO200_10 ARGS ((void));
EXTERN S16 sbO201_01 ARGS ((void));
EXTERN S16 sbO201_02 ARGS ((void));
EXTERN S16 sbO201_03 ARGS ((void));
EXTERN S16 sbO201_04 ARGS ((void));
EXTERN S16 sbO201_05 ARGS ((void));
EXTERN S16 sbO201_06 ARGS ((void));
EXTERN S16 sbO201_07 ARGS ((void));
EXTERN S16 sbO201_08 ARGS ((void));
EXTERN S16 sbO201_09 ARGS ((void));
EXTERN S16 sbO201_10 ARGS ((void));
EXTERN S16 sbO201_11 ARGS ((void));
EXTERN S16 sbO201_12 ARGS ((void));
EXTERN S16 sbO201_13 ARGS ((void));
EXTERN S16 sbO201_14 ARGS ((void));
EXTERN S16 sbO201_15 ARGS ((void));
EXTERN S16 sbO201_16 ARGS ((void));
/* SB_VER13 - Added for hostname testing */
EXTERN S16 sbO201_17 ARGS ((void));
EXTERN S16 sbO201_18 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO201_19 ARGS ((void));  /*IPV6 test case */
EXTERN S16 sbO201_20 ARGS ((void));  /*IPV6 test case */
EXTERN S16 sbO201_21 ARGS ((void));  /*IPV6 test case */
/* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 sbO201_22 ARGS ((void));
#endif /* SCT_ENDP_MULTI_IPADDR */

/* sb028.103 : Added new test case for multiple TermInd issue */
EXTERN S16 sbO201_23 ARGS ((void));
/* sb029.103: Added test case O.201.24 */
EXTERN S16 sbO201_24 ARGS ((void));
/* sb030.103: Added test case O.201.25. */
EXTERN S16 sbO201_25 ARGS ((void));
/* sb035.103: Added testcases O.201.26, O.201.27 and O.201.28*/
EXTERN S16 sbO201_26 ARGS ((void));
EXTERN S16 sbO201_27 ARGS ((void));
EXTERN S16 sbO201_28 ARGS ((void));

/* sb035.102 TermInd Test */
EXTERN S16 sbO205_01 ARGS ((void));  

EXTERN S16 sbO202_01 ARGS ((void));
EXTERN S16 sbO202_02 ARGS ((void));
EXTERN S16 sbO202_03 ARGS ((void));
EXTERN S16 sbO202_04 ARGS ((void));
EXTERN S16 sbO202_05 ARGS ((void));
/* SB_VER13 - Added for hostname testing */
EXTERN S16 sbO202_06 ARGS ((void));
EXTERN S16 sbO202_07 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO202_08 ARGS ((void)); /* IPV6 test case */
/* RFC 4460: Acceptance Tests */
EXTERN S16 sbO202_09 ARGS ((void));
EXTERN S16 sbO202_10 ARGS ((void));
EXTERN S16 sbO202_11 ARGS ((void));
EXTERN S16 sbO202_12 ARGS ((void));
EXTERN S16 sbO202_13 ARGS ((void));
EXTERN S16 sbO202_14 ARGS ((void));
/* RFC 4460 -- SB_ETSI_1 */
EXTERN S16 sbO202_15 ARGS ((void));
/* sb028.103 : Added new test cases to process the data chunk bundled
               with Cookie */
EXTERN S16 sbO202_16 ARGS ((void));
EXTERN S16 sbO202_17 ARGS ((void));
EXTERN S16 sbO202_18 ARGS ((void));
/* sb029.103: Added test case O.202.19 */
EXTERN S16 sbO202_19 ARGS ((void));
/* sb030.103: Added test case O.202.20 */
EXTERN S16 sbO202_20 ARGS ((void));
/* sb035.103: Added test case O.202.21 */
EXTERN S16 sbO202_21 ARGS ((void));

EXTERN S16 sbO203_01 ARGS ((void));
EXTERN S16 sbO203_02 ARGS ((void));
EXTERN S16 sbO203_03 ARGS ((void));
EXTERN S16 sbO203_04 ARGS ((void));
EXTERN S16 sbO203_05 ARGS ((void));
EXTERN S16 sbO203_06 ARGS ((void));
EXTERN S16 sbO203_07 ARGS ((void));

EXTERN S16 sbO204_01 ARGS ((void));
EXTERN S16 sbO204_02 ARGS ((void));
EXTERN S16 sbO204_03 ARGS ((void));
EXTERN S16 sbO204_04 ARGS ((void));
EXTERN S16 sbO204_05 ARGS ((void));
EXTERN S16 sbO204_06 ARGS ((void));
EXTERN S16 sbO204_07 ARGS ((void));
EXTERN S16 sbO204_08 ARGS ((void));
/* RFC 4460 -- SB_RFC_2, SB_RFC_10 */
EXTERN S16 sbO204_09 ARGS ((void));

EXTERN S16 sbO205_01 ARGS ((void));
EXTERN S16 sbO205_02 ARGS ((void));
EXTERN S16 sbO205_03 ARGS ((void));
EXTERN S16 sbO205_04 ARGS ((void));
EXTERN S16 sbO205_05 ARGS ((void));
EXTERN S16 sbO205_06 ARGS ((void));
EXTERN S16 sbO205_07 ARGS ((void));
EXTERN S16 sbO205_08 ARGS ((void));
EXTERN S16 sbO205_09 ARGS ((void));
EXTERN S16 sbO205_10 ARGS ((void));
EXTERN S16 sbO205_11 ARGS ((void));
EXTERN S16 sbO205_12 ARGS ((void));
EXTERN S16 sbO205_13 ARGS ((void));
EXTERN S16 sbO205_14 ARGS ((void));
EXTERN S16 sbO205_15 ARGS ((void));
EXTERN S16 sbO205_16 ARGS ((void));
EXTERN S16 sbO205_17 ARGS ((void));
EXTERN S16 sbO205_18 ARGS ((void));
EXTERN S16 sbO205_19 ARGS ((void));
EXTERN S16 sbO205_20 ARGS ((void));
EXTERN S16 sbO205_21 ARGS ((void));
EXTERN S16 sbO205_22 ARGS ((void));
EXTERN S16 sbO205_23 ARGS ((void));
EXTERN S16 sbO205_24 ARGS ((void));
/* sb012.103: Added test cases for non-unicast address issue fix */
EXTERN S16 sbO205_25 ARGS ((void));
EXTERN S16 sbO205_26 ARGS ((void));
/* sb029.103: Added test case O.205.27  */
EXTERN S16 sbO205_27 ARGS ((void));
/* sb030.103: Added test cases O.205.28,O.205.29 and O.205.30 */
EXTERN S16 sbO205_28 ARGS ((void));
EXTERN S16 sbO205_29 ARGS ((void));
EXTERN S16 sbO205_30 ARGS ((void));

/* externs for sb_act4.c */
EXTERN S16 sbO300_01 ARGS ((void));
EXTERN S16 sbO300_02 ARGS ((void));
EXTERN S16 sbO300_03 ARGS ((void));
EXTERN S16 sbO300_04 ARGS ((void));
EXTERN S16 sbO300_05 ARGS ((void));
EXTERN S16 sbO300_06 ARGS ((void));
EXTERN S16 sbO300_07 ARGS ((void));
EXTERN S16 sbO300_08 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO300_09 ARGS ((void));/* IPV6 test case */
/* RFC 4460 -- SB_ETSI_2 */
EXTERN S16 sbO300_10 ARGS ((void));

EXTERN S16 sbO301_01 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO301_02 ARGS ((void));/* IPV6 test case */

EXTERN S16 sbO302_01 ARGS ((void));
EXTERN S16 sbO302_02 ARGS ((void));
EXTERN S16 sbO302_03 ARGS ((void));
EXTERN S16 sbO302_04 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO302_05 ARGS ((void));/* IPV6 test case */

EXTERN S16 sbO303_01 ARGS ((void));
EXTERN S16 sbO303_02 ARGS ((void));
EXTERN S16 sbO303_03 ARGS ((void));
EXTERN S16 sbO303_04 ARGS ((void));

EXTERN S16 sbO304_01 ARGS ((void));
EXTERN S16 sbO304_02 ARGS ((void));
EXTERN S16 sbO304_03 ARGS ((void));

EXTERN S16 sbO305_01 ARGS ((void));
EXTERN S16 sbO305_02 ARGS ((void));
EXTERN S16 sbO305_03 ARGS ((void));
EXTERN S16 sbO305_04 ARGS ((void));
EXTERN S16 sbO305_05 ARGS ((void));
EXTERN S16 sbO305_06 ARGS ((void));
EXTERN S16 sbO305_07 ARGS ((void));
EXTERN S16 sbO305_08 ARGS ((void));
EXTERN S16 sbO305_09 ARGS ((void));
/* RFC 4460 -- SB_RFC_7 */
EXTERN S16 sbO305_10 ARGS ((void));
/* sb018.103: Added new test case */
EXTERN S16 sbO305_11 ARGS ((void));

EXTERN S16 sbO306_01 ARGS ((void));
EXTERN S16 sbO306_02 ARGS ((void));
EXTERN S16 sbO306_03 ARGS ((void));
EXTERN S16 sbO306_04 ARGS ((void));
/* SATELLITE SCTP feature */ 
/* sb003.103 - addition - new test cases for ECN */
#ifdef SB_ECN
EXTERN S16 sbO307_01 ARGS ((void));
EXTERN S16 sbO307_02 ARGS ((void));
EXTERN S16 sbO307_03 ARGS ((void));
EXTERN S16 sbO307_04 ARGS ((void));
EXTERN S16 sbO307_05 ARGS ((void));
EXTERN S16 sbO307_06 ARGS ((void));
EXTERN S16 sbO307_07 ARGS ((void));
/* sb014.103: New test case added for ECNE chunk */
EXTERN S16 sbO307_08 ARGS ((void));
#endif /* SB_ECN */
/*externs of sb_act5.c */
EXTERN S16 sbO400_01 ARGS ((void));
EXTERN S16 sbO400_02 ARGS ((void));
EXTERN S16 sbO400_03 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO400_04 ARGS ((void));/* IPV6 test case */
EXTERN S16 sbO401_01 ARGS ((void));
EXTERN S16 sbO401_02 ARGS ((void));
EXTERN S16 sbO401_03 ARGS ((void));
EXTERN S16 sbO401_04 ARGS ((void));
EXTERN S16 sbO401_05 ARGS ((void));
EXTERN S16 sbO401_06 ARGS ((void));
EXTERN S16 sbO401_07 ARGS ((void));
EXTERN S16 sbO401_08 ARGS ((void));
EXTERN S16 sbO401_09 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */

#ifdef IPV6_SUPPORTED
EXTERN S16 sbO401_10 ARGS ((void));/* IPV6 test case */
EXTERN S16 sbO401_11 ARGS ((void));/* IPV6 test case */
#endif
/* RFC 4460 -- SB_RFC_3 */
EXTERN S16 sbO401_10 ARGS ((void));
/* RFC 4460 -- SB_RFC_4 */
EXTERN S16 sbO401_11 ARGS ((void));
/* RFC 4460 -- SB_RFC_5 */
EXTERN S16 sbO401_12 ARGS ((void));
/* sb021.103: Added new testcase */
EXTERN S16 sbO401_13 ARGS ((void));

EXTERN S16 sbO402_01 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbO402_02 ARGS ((void));/* IPV6 test case */

/* externs for sb_act6.c*/
EXTERN S16 sbM100_01 ARGS ((void));
EXTERN S16 sbM100_02 ARGS ((void));
EXTERN S16 sbM101_01 ARGS ((void));
EXTERN S16 sbM101_02 ARGS ((void));
EXTERN S16 sbM101_03 ARGS ((void));
EXTERN S16 sbM102_01 ARGS ((void));
EXTERN S16 sbM102_02 ARGS ((void));
EXTERN S16 sbM102_03 ARGS ((void));

EXTERN S16 sbM200_01 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbM200_02 ARGS ((void));/*IPV6 test case */
EXTERN S16 sbM201_01 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbM201_02 ARGS ((void));/*IPV6 test case */
EXTERN S16 sbM202_01 ARGS ((void));
/* sb032.102 :  IPV6 Support Added */
EXTERN S16 sbM202_02 ARGS ((void));/*IPV6 test case */
EXTERN S16 sbM203_01 ARGS ((void));
EXTERN S16 sbM203_02 ARGS ((void));
EXTERN S16 sbM204_01 ARGS ((void));
EXTERN S16 sbM204_02 ARGS ((void));
EXTERN S16 sbM205_01 ARGS ((void));

/* externs for sb_act6.c */
EXTERN S16 sbM300_01 ARGS ((void));
EXTERN S16 sbM300_02 ARGS ((void));

EXTERN S16 sbM301_01 ARGS ((void));
EXTERN S16 sbM301_02 ARGS ((void));

EXTERN S16 sbM302_01 ARGS ((void));
EXTERN S16 sbM302_02 ARGS ((void));

EXTERN S16 sbM303_01 ARGS ((void));

EXTERN S16 sbM304_01 ARGS ((void));

EXTERN S16 sbM305_01 ARGS ((void));

EXTERN S16 sbM400_01 ARGS ((void));
EXTERN S16 sbM400_02 ARGS ((void));
/* SATELLITE SCTP feature */ 
/* sb003.103 - addition - new test cases for delete control reqeust for
 * path profile and destination address
 */
#ifdef SB_SATELLITE
EXTERN S16 sbM306_01 ARGS ((void));
EXTERN S16 sbM307_01 ARGS ((void));
#endif /* SB_SATELLITE */


/* Other */
EXTERN S16 sdActvTsk  ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 sdActvInit ARGS((Ent ent, Inst inst, Region region, Reason reason));
EXTERN S16 asActvTsk  ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 asActvInit ARGS((Ent ent, Inst inst, Region region, Reason reason));

/* hi_bdy1.c */
EXTERN S16 hiSbActvInit ARGS((Ent ent,Inst inst, Region region, Reason reason));
EXTERN Void hisbPrintCfm ARGS((SctStatus status, Reason  reason));

/* hi_ex_ms.c */
EXTERN S16 hiSbActvTsk ARGS((Pst *pst, Buffer *mBuf));

/*it_bdy1.c */
EXTERN S16 itSbActvInit ARGS((Ent ent,Inst inst, Region region, Reason reason));

/* it_ex_ms.c */
EXTERN S16 itSbActvTsk ARGS((Pst *pst, Buffer *mBuf));

/* in it_ptli.c */
EXTERN S16 ItLiSctDatReq      ARGS((Pst        *pst,
                                    SpId       spId,
                                    UConnId    spAssocId,
                                    CmNetAddr  *dstNAddr,
                                    SctStrmId  strmId,
                                    Bool       unorderFlg,
                                    Bool       nobundleFlg,
                                    U16        lifetime,
                                    U32        protId,
                                    Buffer     *mBuf));

EXTERN S16 ItLiSctStaReq      ARGS((Pst         *pst,
                                    SpId        spId,
                                    UConnId     spAssocId,
                                    CmNetAddr   *dstNAddr,
                                    U8          staType ));

EXTERN S16 ItLiSctTermReq     ARGS((Pst      *pst,
                                    SpId     spId,
                                    UConnId  assocId,
                                    U8       assocIdType,
                                    Bool     abrtFlg));

EXTERN S16 ItLiSctBndReq      ARGS((Pst *pst,
                                    SuId suId,
                                    SpId spId));


/* sb046: multihoming */
#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 ItLiSctEndpOpenReq ARGS((Pst *pst,
                                    SpId spId,
                                    UConnId suEndpId,
                                    SctPort port,
                                    SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 ItLiSctEndpOpenReq ARGS((Pst *pst,
                                    SpId spId,
                                    UConnId suEndpId,
                                    SctPort port,
                                    CmNetAddr *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

/* sb060.102: TOS enhancement */
#ifdef SCT3
EXTERN S16 ItLiSctAssocReq   ARGS((Pst           *pst,
                                    SpId           spId,
                                    UConnId        spEndpId,
                                    UConnId        suAssocId,
                                    CmNetAddr     *priDstNAddr,
                                    SctPort        dstPort,
                                    SctStrmId      outStrms,
                                    SctNetAddrLst *dstNAddrLst,
                                    SctNetAddrLst *srcNAddrLst,
                                    SctTos         tos,
                                    Buffer        *vsInfo));
#else /* SCT3 */
EXTERN S16 ItLiSctAssocReq    ARGS((Pst           *pst,
                                    SpId          spId,
                                    UConnId       spEndpId,
                                    UConnId       suAssocId,
                                    CmNetAddr     *priDstNAddr,
                                    SctPort       dstPort,
                                    SctStrmId     outStrms,
                                    SctNetAddrLst *dstNAddrLst,
                                    SctNetAddrLst *srcNAddrLst,
                                    Buffer        *vsInfo ));
#endif /* SCT3 */

EXTERN S16 ItLiSctEndpCloseReq   ARGS((Pst *pst,
                                       SpId spId,
                                       UConnId endpId,
                                       U8     endpIdType));

/* sb060.102: TOS enhancement */
#ifdef SCT3
EXTERN S16 ItLiSctAssocRsp   ARGS((Pst               *pst,
                                    SpId               spId,
                                    UConnId            spEndpId,
                                    SctAssocIndParams *assocIndParams,
                                    SctTos             tos,
                                    SctResult          result,
                                    Buffer            *vsInfo));
#else /* SCT3 */
EXTERN S16 ItLiSctAssocRsp    ARGS((Pst                 *pst,
                                    SpId                spId,
                                    UConnId             spEndpId,
                                    SctAssocIndParams   *assocIndParams,
                                    SctResult           result,
                                    Buffer             *vsInfo ));
#endif /* SCT3 */

EXTERN S16 ItLiSctHBeatReq    ARGS((Pst        *pst,
                                    SpId       spId,
                                    UConnId    spAssocId,
                                    CmNetAddr  *dstNAddr,
                                    U16        intervalTime,
                                    SctStatus  status));

EXTERN S16 ItLiSctSetPriReq   ARGS((Pst       *pst,
                                    SpId      spId,
                                    UConnId   spAssocId,
                                    CmNetAddr *dstNAddr));

EXTERN S16 HiUiHitDiscCfm     ARGS((Pst *pst,
                                    SuId suId,
                                    U8 choice,
                                    UConnId conId,
                                    Action action));

/* sb032.102 :  IPV6 Support Added */
#ifdef LOCAL_INTF
EXTERN S16 HiUiHitUDatInd     ARGS((Pst *pst,
                                    SuId suId,
                                    UConnId suConId,
                                    CmTptAddr *srcAddr,
                                    CmTptAddr *destAddr,
                                    CmIpHdrParm  *hdrParm,
                                    CmTptLocalInf *localIf,
                                    Buffer *mBuf));
#else
EXTERN S16 HiUiHitUDatInd     ARGS((Pst *pst,
                                    SuId suId,
                                    UConnId suConId,
                                    CmTptAddr *srcAddr,
                                    CmTptAddr *destAddr,
                                    CmIpHdrParm  *hdrParm,
                                    Buffer *mBuf));
#endif

#ifdef SB_FTHA 
EXTERN S16  smShtActvTsk ARGS((Pst *pst, Buffer *mBuf));
#endif /* SB_FTHA */
#ifdef SB_RUG 
EXTERN S16 sbShtCntrlReq ARGS(( U8 reqType,U8 grpType,ProcId  procId, Ent ent,Inst   inst,CmIntfId intfId, CmIntfVer intfVer));
#endif /* SB_RUG */
EXTERN S16 HiUiHitBndCfm      ARGS((Pst *pst,
                                    SuId suId,
                                    U8 status ));

EXTERN S16 HiUiHitConCfm      ARGS((Pst *pst,
                                    SuId suId,
                                    UConnId suConId,
                                    UConnId spConId,
                                    CmTptAddr *localAddr));

EXTERN Void exit      ARGS((int status));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SBACCX__ */
/********************************************************************30**

         End of file:     sb_acc.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:05 2015

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
/main/3      ---      nct  1.Initial version
/main/3      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
          sb042.102   hl   1. Added change for SHT interface and Rolling
                              Up Grade
          sb044.102   rs   1. DNS Call conditioned.
          sb046.102   hl   1. Multiple IP address per endpoint support
          sb057.102   pr   1. Multiple proc ids support added.
          sb060.102   pr   1. TOS enhancement.
/main/4      ---      rsr/ag   1. Updated for Release of 1.3
          sb003.103   ag   1. Satellite SCTP feature (under compile-time
                              flags SB_ECN & SB_SATELLITE).
	  sb012.103   pkaX 1. Non-Unicast Address Fix: Added new function
                              to build init chunk for non-unicast address
                              and test cases.
                           2. Replaced the SB_ACC flag with LSB12.
          sb013.103   pkaX 1. a_rwnd Fix: New function to build data chunk.
          sb014.103   pkaX 1. Memory leak Fix: Added new test case and 
                              function for ECNE chunk.
                           2. New function to calculate number of ticks.
          sb018.103   pkaX 1. BytesOut issue: Added new test case.
/main/4   sb021.103   krkX 1. Added testcase for hBeat timer.
/main/4   sb024.103   ajainx 1. Included protId parameter in status indication.
/main.4   sb028.103   ajainx 1. Added new test case for multiple TermInd issue.
                             2. Added new test cases to process the data 
                                chunk bundled with Cookie.
                             3. Added a new function to process tha data chunk
                                bundled with cookie chunk.
/main.4   sb029.103   krkX   1. Added new testcases O.205.27,O.201.24,O.202.19. 
/main.4   sb030.103   krkX   1. Added new function to process the ABORT chunk
                                bundled with COOKIE-ECHO chunk.
                             2. Added new testcases O.201.25,O.202.20,O.205.28,
                                O.205.29 and O.205.30.
/main.4   sb035.103   vsk    1. Modified hostName array length to 264 in 
                                structure _sbAccChunkBld
                             2. Added new testcases O.201.26, O.201.27,
                                O.201.28 and O.202.21.
*********************************************************************91*/
