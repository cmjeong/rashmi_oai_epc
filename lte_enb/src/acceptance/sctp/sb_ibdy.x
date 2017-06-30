

/********************************************************************20**
  
     Name:     SCTP Test
  
     Type:     C header file
  
     Desc:     C structures and externs for keyword matching.
  
     File:     sctpTest.x
  
     Sid:      sb_ibdy.x@@/main/2 - Thu Jul 26 07:54:19 2007
  
     Prg:      nj
  
*********************************************************************21*/

#ifndef __SCTPINOPX__
#define __SCTPINOPX__

/* typedefs */

typedef struct _tstTkn
{
   TknStr    tok;
   U16       nmbArgs;
   TknStr    args[MAXARGS];
} TstTkn;

typedef struct cfTkn
{
   TknStrM tok;
   U16 nmbArgs;
   TknStrM args[MAXARGS];
}CfTkn;

typedef struct _endp
{
   Pst         pst;
   SctPort     port;
   CmNetAddr   netAddr;
   UConnId     suEndpId;
   UConnId     spEndpId;
   SpId        spId;
   Bool        cfgDone;
   Bool        occupied;
}Endp;

EXTERN Endp endp[];

typedef struct configReq 
{
  SbGenCfg      genCfg;         /* General Configuration */
  SbSctSapCfg   sctSapCfg;      /* SCT SAP Configuration */
  SbTSapCfg     tSapCfg;        /* Transport SAP Configuration */
  Pst           pst;             /* Pst structure */
  Pst           tPst;            /* Transport Sap Pst */
} ConfigReq;

ConfigReq cfgReq;

EXTERN Keys cf_kw[];
EXTERN Keys proc_kw[];
EXTERN Keys sel_kw[];
EXTERN Keys bool_kw[];
EXTERN Keys prior_kw[];
EXTERN Keys route_kw[];
EXTERN Keys region_kw[];
EXTERN Keys pool_kw[];
EXTERN Keys swtch_kw[];
EXTERN Keys entity_kw[];

EXTERN S32 lineNo;

EXTERN S16 cfNewConfigReq ARGS((U32 size, ConfigReq *cf, U8 id));


typedef struct _assocReq
{
   SpId          spId; 
   UConnId       spEndId; 
   UConnId       suEndId; 
   UConnId       suAssocId; 
   CmNetAddr     dstNetAddr;
   SctPort       dstPort;
   SctStrmId     outStrms;
   SctStrmId     inStrms;
   SctNetAddrLst dstNAddrLst;
   SctNetAddrLst srcNAddrLst;
   UConnId       spAssocId; 
   Bool          assocDone;
   U8            node;
   Bool          occupied;
   U8            endpIdx;
}AssocReq;

EXTERN AssocReq assocReq[];

Bool FLCpause;
U32 MTdataCount;
U32 MTassocIdx;
U32 MTstreamId;
U32 MTsize;

typedef struct _dataReq
{
   SpId          spId; 
   UConnId       spAssocId; 
   CmNetAddr     dstNAddr;
   SctStrmId     strmId;
   Bool          unorderFlg;
   Bool          nobundleFlg;
   U16           lifeTime;
   U32           protId;
   Buffer        *mBuf;
}DataReq;

EXTERN DataReq  dataReq;

typedef struct _loopInfo
{
   S16           times; 
   S16           size; 
   S16           delay; 
}LoopInfo;

EXTERN LoopInfo loopInfo;

typedef struct _tstInput
{
   SctPort        srcPort;
   SctPort        dstPort;
   SctNetAddrLst  dstAddrLst;
   SctStrmId      outStrms;
   SctStrmId      defStrms;
} TstInput;

TstInput tstinput;

/* Main functions */

EXTERN  S16  sbPermTskInit ARGS((Ent ent, Inst inst, Region region, Reason reason));
EXTERN  S16 sbPermTsk ARGS((Pst *pst, Buffer *mBuf));

/* Support Functions */

EXTERN S16 sbISParsU32 ARGS((CfTkn *tkn, U32 low, U32 high, U32 *ret));
EXTERN S16 sbISMatchKw ARGS((Keys *kw, CfTkn *tkn, U32 *ret));
EXTERN S16 sbISMatchU32 ARGS((Keys *kw, CfTkn *tkn, U32 low, U32 high, U32 *ret));
EXTERN S16 sbISLineToTkn  ARGS((S8 *line,CfTkn *tkn));
EXTERN S16 sbISParsNetAddr ARGS((CfTkn *tkn, CmNetAddr *srcAddr));
EXTERN S16 sbISParsTptAddr ARGS((CfTkn *tkn, CmTptAddr *srcAddr));
EXTERN S16 sbISParsSrcAddr ARGS((CfTkn *tkn, SctNetAddrLst *srcAddr));
EXTERN Void sbISPrntTkn  ARGS((CfTkn *tkn));
EXTERN Void sbICPrntError  ARGS((Txt *msg));
EXTERN U32  sbISStrtoul ARGS((CONSTANT S8 *str, S8 **ptr, S32 base));


/* Primitive Functions */

EXTERN S16 sbIPInitSctp ARGS ((Void));
EXTERN S16 sbIPEndpOpenReq ARGS((Void));
EXTERN S16 sbIPAssocReq ARGS((U8 endpIdx));
EXTERN S16 sbIPDataReq ARGS((U8 *strng, U16 length, U8 assocIdx));
EXTERN S16 sbIPBulkDataReq ARGS((U16 length, U8 assocIdx, U8 type));
EXTERN S16 sbIPSendFile ARGS((Txt filename[], U8 assocIdx));
EXTERN S16 sbIPPerfDataReq ARGS((U8 assocIdx));
EXTERN S16 sbICLoopReq ARGS(( U8 id, CfTkn *tkn));
 
/* Configuration Functions */

EXTERN S16 sbICParsAssocReq ARGS((OsFile *inFile,U16 *idx));
EXTERN S16 sbICParsDataReq ARGS((OsFile *inFile));
EXTERN S16 sbICParsEndpCfg ARGS((OsFile *inFile,U16 *idx));
EXTERN S16 sbICPrntData ARGS((U8 id,U8 blockIdx));
EXTERN S16 sbICCfgReq ARGS((U8 id)); 
EXTERN S16 sbIChiGenCfg ARGS(( Ent  ent, Inst inst));
EXTERN S16 sbIChiSapCfg ARGS((SpId inst));
EXTERN S16 sbIBDsplAssocInfo ARGS ((U16 assocIdx));
EXTERN Void sbIBGetLmPst ARGS (( Pst *lmPst ));
EXTERN S16 sbICParsLoopReq ARGS(( OsFile *inFile));


/* MACROS */

#define PARSE_PCLASS(tk, ret) \
   sbISMatchKw(proc_kw, tk, ret)

#define PARSE_THRESH(tk, ret) \
   sbISMatchU32(thrsh_kw, tk, 0, 9, ret)

#define PARSE_SELECTOR(tk, ret) \
   sbISMatchU32(sel_kw, tk, 0, 0xff, ret)

#define PARSE_BOOL(tk, ret) \
   sbISMatchU32(bool_kw, tk, FALSE, TRUE, ret)

#define PARSE_PRIOR(tk, ret) \
   sbISMatchU32(prior_kw, tk, PRIOR0, PRIOR3, ret)

#define PARSE_ROUTE(tk, ret) \
   sbISMatchU32(route_kw, tk, RTESPEC, RTESPEC, ret)

#define PARSE_REGION(tk, ret) \
   sbISMatchU32(region_kw, tk, DFLT_REGION, DFLT_REGION, ret)

#define PARSE_ENTITY(tk, ret) \
   sbISMatchU32(entity_kw, tk, 0, MAX_U8, ret)

#define PARSE_POOL(tk, ret) \
   sbISMatchU32(pool_kw, tk, DFLT_POOL, DFLT_POOL, ret)

#define PARSE_SWTCH(tk, ret) \
   sbISMatchU32(swtch_kw, tk, SW_CCITT88, SW_Q767, ret)


#endif /* __SCTPINOPX__ */


/********************************************************************30**

         End of file:     sb_ibdy.x@@/main/2 - Thu Jul 26 07:54:19 2007

*********************************************************************31*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sb    1. File Added for inter-op SCTP Testing 
/main/2      ---   rsr/ag   1. Updated for Release of 1.3  
*********************************************************************91*/


