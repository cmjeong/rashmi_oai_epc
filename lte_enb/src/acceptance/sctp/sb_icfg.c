
/********************************************************************20**

     Name:     sb_icfg.c -  inop file

     Type:     C source file

     Desc:     C code for inop

     File:     sb_icfg.c

     Sid:      sb_icfg.c@@/main/2 - Thu Jul 26 07:54:22 2007

     Prg:      nct

*********************************************************************21*/




/*
 * header include files -- defines (.h)
 */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* Common timer */
#include "cm_os.h"
#include "cm_hash.h"       /* common hash */
#include "cm_tpt.h"        /* common transport addressing */
#include "cm_dns.h"        /* Common DNS library */
#include "sct.h"           /* SCT Interface */
#include "lsb.h"           /* LSB Interface */
#include "lhi.h"
#include "hit.h"
#include "hi_acc.h"
#include "sb.h"
#include "hi.h"
#include "sb_ibdy.h"
#include "sb_acc.h"

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timer */
#include "cm_os.x"
#include "cm_lib.x"
#include "cm_hash.x"       /* common hash */
#include "cm_tpt.x"        /* common transport addressing */
#include "cm_dns.x"        /* Common DNS library */
#include "sct.x"           /* SCT Interface */
#include "lsb.x"           /* LSB Interface */
#include "lhi.x"
#include "hit.x"
#include "hi_acc.x"
#include "sb_ibdy.x"


/* local defines */

PRIVATE U16 sbNmbSctSaps = 0;
PRIVATE U16 sbNmbTSaps = 0;
PRIVATE U16 sbNmbEndp = 0;
PRIVATE U16 sbNmbAssoc = 0;
PRIVATE U16 sbNmbDstAddr = 0;
PRIVATE U16 sbNmbSrcAddr = 0;
PRIVATE U16 sbNmbTxChunks = 0;
PRIVATE U16 sbNmbRxChunks = 0;
PRIVATE U16 sbNmbInStrms = 0;
PRIVATE U16 sbNmbOutStrms = 0;

/* private variable declarations */

PRIVATE Keys sbSw_kw[]=
{
   {"LSB_SW_RFC_REL0", 1 },
   {"",  MATCH_FAILED }
};


PRIVATE Keys sbGen_kw[]=
{
   {"beginCfg",           0 },
   {"smPst.selector",     1 },
   {"sm.selector",        1 },
   {"selector",           1 },
   {"serviceType",        2 },
   {"maxNmbSctSaps",      3 },
   {"maxNmbTSaps",        4 },
   {"maxNmbEndp",         5 },
   {"maxNmbAssoc",        6 },
   {"maxNmbDstAddr",      7 },
   {"maxNmbSrcAddr",      8 },
   {"maxNmbTxChunks",     9 },
   {"maxNmbRxChunks",     10 },
   {"maxNmbInStrms",      11 },
   {"maxNmbOutStrms",     12 },
   {"initARwnd",          13 },
   {"mtuInitial",         14 },
   {"mtuMinInitial",      15 },
   {"mtuMaxInitial",      16 },
   {"performMtu",         17 },
   {"timeRes",            18 },
   {"maxInitReTx",        19 },
   {"maxAssocReTx",       20 },
   {"maxPathReTx",        21 },
   {"altAcceptFlg",       22 },
   {"keyTm",              23 },
   {"alpha",              24 },
   {"beta",               25 },
   {"hostName",           26 },
   {"hostname",           26 },
   {"useHstName",         27 },
   {"endCfg",             28 },
   {"",         MATCH_FAILED }
};


PRIVATE Keys sbSctSap_kw[]=
{
   {"beginCfg",           0 },
   {"swtch",              1 },
   {"spId",               2 },
   {"sel",                3 },
   {"mem.memregion",      4 },
   {"memregion",          4 },
   {"memRegion",          4 },
   {"mem.mempool",        5 },
   {"mempool",            5 },
   {"memPool",            5 },
   {"prior",              6 },
   {"route",              7 },
   {"maxAckDelayTm",      8 },
   {"maxAckDelayDg",      9 },
   {"initTm",             10 },
   {"shutdownTm",         11 },
   {"rtoInitial",         12 },
   {"rtoMin",             13 },
   {"rtoMax",             14 },
   {"freezeTm",           15 },
   {"cookieLife",         16 },
   {"intervalTm",         17 },
   {"handleInitFlg",      18 },
   {"negAbrtFlg",         19 },
   {"hBeatEnable",        20 },
   {"flcUpThr",           21 },
   {"flcLowThr",          22 },
   {"endCfg",             23 },
   {"",         MATCH_FAILED }
};

PRIVATE Keys sbTSap_kw[]=
{
   {"beginCfg",           0 },
   {"swtch",              1 },
   {"suId",               2 },
   {"sel",                3 },
   {"ent",                4 },
   {"inst",               5 },
   {"procId",             6 },
   {"mem.memregion",      7 },
   {"memregion",          7 },
   {"memRegion",          7 },
   {"mem.mempool",        8 },
   {"mempool",            8 },
   {"memPool",            8 },
   {"prior",              9 },
   {"route",              10 },
   {"srcNAddrLst",        11 },
   {"spId",               12 },
   {"maxBndRetry",        13 },
   {"tIntTmr",            14 },
   {"useDnsLib",          15 },
   {"dnsAddr",            16 },
   {"dnsTmOut",           17 },
   {"maxRtxCnt",          18 },
   {"endCfg",             19 },
   {"",         MATCH_FAILED }
};

PRIVATE Keys sbEndp_kw[]=
{
   {"beginCfg",           0 },
   {"selector",           1 },
   {"spId",               2 },
   {"region",             3 },
   {"pool",               4 },
   {"prior",              5 },
   {"route",              6 },
   {"port",               7 },
   {"suEndpId",           8 },
   {"intfNAddr",          9 },
   {"endCfg",             10 },
   {"",         MATCH_FAILED }
};

PRIVATE Keys sbAssoc_kw[]=
{
   {"beginCfg",           0 },
   {"spId",               1 },
   {"spEndId",            2 },
   {"suAssocId",          3 },
   {"priDstNAddr",        4 },
   {"dstPort",            5 },
   {"outStrms",           6 },
   {"dstNAddrLst",        7 },
   {"srcNAddrLst",        8 },
   {"endCfg",             9 },
   {"",         MATCH_FAILED }
};

PRIVATE Keys sbDataRq_kw[]=
{
   {"beginCfg",           0 },
   {"spId",               1 },
   {"spAssocId",          2 },
   {"dstNAddr",           3 },
   {"strmId",             4 },
   {"unorderFlg",         5 },
   {"nobundleFlg",        6 },
   {"lifeTime",           7 },
   {"protId",             8 },
   {"endCfg",             9 },
   {"",         MATCH_FAILED }
};


PRIVATE Keys sbLoopRq_kw[]=
{
   {"beginCfg",           0 },
   {"times",              1 },
   {"size",               2 },
   {"delay",              3 },
   {"endCfg",             4 },
   {"",         MATCH_FAILED }
};

/*  public variable declarations */

PUBLIC Keys sel_kw[]=
{
   {"SEL_TC", SEL_TC},
   {"SEL_LC", SEL_LC},
   {"", MATCH_FAILED}
};

PUBLIC Keys bool_kw[]=
{
   {"TRUE", TRUE},
   {"true", TRUE},
   {"FALSE", FALSE},
   {"false", FALSE},
   {"", MATCH_FAILED}
};

PUBLIC Keys prior_kw[]=
{
   {"PRIOR0", PRIOR0},
   {"PRIOR1", PRIOR1},
   {"PRIOR2", PRIOR2},
   {"PRIOR3", PRIOR3},
   {"", MATCH_FAILED}
};

PUBLIC Keys route_kw[]=
{
   {"RTESPEC", RTESPEC},
   {"RTEFRST", RTEFRST},
   {"RTEALL", RTEALL},
   {"RTETRNQ", RTETRNQ},
   {"RTEQONLY", RTEQONLY},
   {"", MATCH_FAILED}
};

PUBLIC Keys region_kw[]=
{
   {"DFLT_REGION", DFLT_REGION},
   {"", MATCH_FAILED}
};

PUBLIC Keys entity_kw[]=
{
   {"ENTHI", ENTHI},
   {"", MATCH_FAILED}
};

PUBLIC Keys pool_kw[]=
{
   {"DFLT_POOL", DFLT_POOL},
   {"", MATCH_FAILED}
};

/* extern variable declarations */

PUBLIC Txt prgNme[]="sb_icfg.c";         /* program name */
PUBLIC S8 optDebug;                       /* debug */

PUBLIC Endp endp[MAXBLOCKS];
PUBLIC AssocReq assocReq[MAXBLOCKS];
PUBLIC DataReq dataReq;

/* external public functions defined here */

PUBLIC S16 sbICCfgReq ARGS((U8 id));
PUBLIC S16 sbIChiGenCfg ARGS(( Ent  ent, Inst inst));
PUBLIC S16 sbIChiSapCfg ARGS((SpId inst));


/* private functions */

PRIVATE S16 sbICParsGenCfg ARGS((OsFile *cfin));
PRIVATE S16 sbICParsSctSapCfg ARGS((OsFile *cfin));
PRIVATE S16 sbICParsTSapCfg ARGS((OsFile *cfin));
PRIVATE Void sbICDefCfgReq ARGS((SbCfg *cfg, U8 id));
PRIVATE S16 sbICGenCfg ARGS((U8 id, CfTkn *tkn));
PRIVATE S16 sbICSctSapCfg ARGS((U8 id, CfTkn *tkn));
PRIVATE S16 sbICTSapCfg ARGS((U8 id, CfTkn *tkn));
PRIVATE S16 sbICPrntCfgReq ARGS((U8 id));

/* local public functions */

PUBLIC S16 sbICEndpCfg ARGS((Endp *endpPtr, CfTkn *tkn));
PUBLIC S16 sbICAssocReq ARGS((AssocReq *assocInfo, CfTkn *tkn));
PUBLIC S16 sbICDataReq ARGS((U8 id, CfTkn *tkn));

/* functions in other modules */


/*
*
*       Fun:   sbICCfgReq

*       Desc:  does processing of configure command on command line.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  cfv2_cr2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbICCfgReq
(
U8 id
)
#else
PUBLIC S16 sbICCfgReq (id)
U8 id;
#endif
{
   OsFile *cfin;
   /* set debug off */
   optDebug = 0;


   TRC2 (sbICCfgReq)


   switch(id)
   {

     case STSBGEN:
     {

       SbMgmt sbmgmt;

       if ((cfin = (OsFile*)osFopen("sb.gencfg", "r")) == (S32)NULLP)
       {
         osPrintf("%s(%d): File open error, File=%s\n", __FILE__, __LINE__, "sb.gencfg");
         osExit(-1);
       }

       if (optDebug >= 0)
          osPrintf("\n%s: parsing started", __FILE__);

       if ((sbICParsGenCfg (cfin)) == RFAILED)
       {
            osPrintf("%s(%d): Failed parsing file sb.gencfg\n", __FILE__, __LINE__);
            osExit(-1);
       }
       else
       {
         sbmgmt.hdr.elmId.elmnt         = STSBGEN;
         sbmgmt.hdr.response.selector = 1;
         osMemcpy((OsVoid*)&sbmgmt.t.cfg.s.genCfg,
             (CONST OsVoid *)&cfgReq.genCfg, sizeof(SbGenCfg));
         SbMiLsbCfgReq(&cfgReq.pst, &sbmgmt);
       }
     }
     break;

     case  STSBSCTSAP:
     {

       SbMgmt sbmgmt;

       if ((cfin = (OsFile*)osFopen("sb.sctcfg", "r")) == (S32)NULLP)
       {
         osPrintf("%s(%d): File open error, File=%s\n", __FILE__, __LINE__, "sb.sctcfg");
         osExit(-1);
       }

       if (optDebug >= 0)
          osPrintf("\n%s: parsing started", prgNme);

       if ((sbICParsSctSapCfg (cfin)) == RFAILED)
       {
            osPrintf("%s(%d): Failed parsing sb.sctcfg file\n", __FILE__, __LINE__);
            osExit(-1);
       }
       else
       {
         sbmgmt.hdr.elmId.elmnt         = STSBSCTSAP;
         sbmgmt.hdr.response.selector = 1;
         osMemcpy((OsVoid*)&sbmgmt.t.cfg.s.sctSapCfg,
             (CONST OsVoid *)&cfgReq.sctSapCfg, sizeof(SbSctSapCfg));
          SbMiLsbCfgReq(&cfgReq.pst, &sbmgmt);
       }

     }
     break;

     case STSBTSAP:
     {

       SbMgmt sbmgmt;

       if ((cfin = (OsFile*)osFopen("sb.tsapcfg", "r")) == (S32)NULLP)
       {
         osPrintf("%s(%d): File open error, File=%s\n", __FILE__, __LINE__, "sb.tsapcfg");
         osExit(-1);
       }

       if (optDebug >= 0)
          osPrintf("\n%s: parsing started", prgNme);


       if ((sbICParsTSapCfg (cfin)) == RFAILED)
       {
            osPrintf("%s(%d): Failed parsing sb.tsapcfg file\n", __FILE__, __LINE__);
            osExit(-1);
       }
       else
       {
         sbmgmt.hdr.elmId.elmnt         = STSBTSAP;
         sbmgmt.hdr.response.selector = 1;
         osMemcpy((OsVoid*)&sbmgmt.t.cfg.s.tSapCfg,
             (CONST OsVoid *)&cfgReq.tSapCfg, sizeof(SbTSapCfg));
          SbMiLsbCfgReq(&cfgReq.tPst, &sbmgmt);
       }

     }
     break;

     default:
         break;
   }
   osFclose(cfin);   /* Close file */

   if (optDebug >= 0)
       osPrintf("\n%s: parsing completed", prgNme);

   RETVALUE(OK);
} /* end of cfProcessGenCfgCommand */


/*
*
*       Fun:   sbICParsGenCfg
*
*       Desc:
*
*       Ret:
*
*       Notes:
*
*       File:  cfv2_cr2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbICParsGenCfg
(
OsFile *inFile
)
#else
PUBLIC S16 sbICParsGenCfg (inFile)
OsFile *inFile;
#endif
{

   S8 line[LINELEN];
   S8 *ret;
   CfTkn tkn;

   TRC2(sbICParsGenCfg)

   lineNo=1;

   for(;;)
   {
      ret = osFgets(line, LINELEN, inFile);
      if (ret == (S8*)-1 || ret == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
            osPrintf("%s(%d): sb.gencfg end of file reached. line %d\n", __FILE__, __LINE__, lineNo);
         break;
      }
      if (optDebug >= 2)
         osPrintf("lineNo = %d\n", lineNo);

      if (!osStripBlanks(line))
      {
         lineNo++;
         continue;              /* blank line */
      }

      if (*line == '#')
      {
         lineNo++;
         continue;              /* blank line */
      }

      /* convert line to tokens */
      if (sbISLineToTkn(line, &tkn) == -1)
      {
         osPrintf("%s(%d): syntax error reading file sb.gencfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      if(sbICGenCfg(1,&tkn) == RFAILED)
      {
         osPrintf("%s(%d): syntax error reading file sb.gencfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      lineNo++; /* default case. just increment line number */

   } /* end of for loop */

   RETVALUE(ROK);
} /* end of sbICParsGenCfg */


/*
 *
 *       Fun:   sbICGenCfg
 *
 *       Desc:  parse sb GEN
 *
 *       Ret:   ROK on success
 *              RFAILED on error
 *
 *       Notes:
 *
         File:  cfv2_sb1.c
 *
 */
#ifdef ANSI
PUBLIC S16 sbICGenCfg
(
U8     id,
CfTkn *tkn
)
#else
PUBLIC S16 sbICGenCfg(id, tkn)
U8     id;
CfTkn *tkn;
#endif
{
   PRIVATE SbGenCfg *cfg = NULLP;
   PRIVATE SbCfg defCfg;
   S32 val;
   S32 ret;
   U32 tmp;

   TRC3(sbICGenCfg)

   val = osMatchKeyword(sbGen_kw, (S8*)tkn->tok.val);
   switch(val)
   {
      case 0:                   /* beginCfg */
         /*
          * allocate gen config info
          */
         sbICDefCfgReq(&defCfg, STSBGEN);
         osMemcpy((OsVoid *)&cfgReq.genCfg, (CONST OsVoid *)&defCfg.s.genCfg,
                   sizeof(SbGenCfg));
         cfg = (SbGenCfg *)&cfgReq.genCfg;
         cfg->smPst.selector = SEL_TC;
         break;

      case 1:                   /* smPst.selector */
    /*     ret = PARSE_SELECTOR(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->smPst.selector = (Selector)tmp;
    */ 
         break;

      case 2:                   /* servicetype  */
         ret = sbISParsU32(tkn, 0, MAX_U8, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->serviceType = (U8)tmp;
         break;

      case 3:                   /* maxNmbSctSaps */
         ret = sbISParsU32(tkn, 0, MAX_U16,  &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbSctSaps = (U16)tmp;
         sbNmbSctSaps = cfg->maxNmbSctSaps;
         break;

      case 4:                   /* nmbTSaps */
         ret = sbISParsU32(tkn, 0, MAX_U16,  &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbTSaps = (U16)tmp;
         sbNmbTSaps = cfg->maxNmbTSaps;
         break;

      case 5:                   /* nmbEndp */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbEndp = (U16)tmp;
         sbNmbEndp = cfg->maxNmbEndp;
         break;

      case 6:                   /* nmbAssoc */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbAssoc = (U16)tmp;
         sbNmbAssoc = cfg->maxNmbAssoc;
         break;

      case 7:                   /* nmbDstAddr */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbDstAddr = (U16)tmp;
         sbNmbDstAddr = cfg->maxNmbDstAddr;
         break;

      case 8:                   /* nmbSrcAddr */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbSrcAddr = (U16)tmp;
         sbNmbSrcAddr = cfg->maxNmbSrcAddr;
         break;

      case 9:                   /* nmbTxChunks */
         ret = sbISParsU32(tkn, 0, MAX_U32, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbTxChunks = (U32)tmp;
         sbNmbTxChunks = cfg->maxNmbTxChunks;
         break;

      case 10:                   /* nmbRxChunks */
         ret = sbISParsU32(tkn, 0, MAX_U32, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbRxChunks = (U32)tmp;
         sbNmbRxChunks = cfg->maxNmbRxChunks;
         break;

      case 11:                   /* maxNmbInStrm */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbInStrms = (U16)tmp;
         sbNmbInStrms = cfg->maxNmbInStrms;
         break;

      case 12:                   /* maxNmbOutStrm */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->maxNmbOutStrms = (U16)tmp;
         sbNmbOutStrms = cfg->maxNmbOutStrms;
         break;

      case 13:                  /* initARwnd */
         ret = sbISParsU32(tkn, 0, MAX_U32, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->initARwnd = (U32)tmp;
         break;

      case 14:                   /* mtuInitial */
         ret = sbISParsU32(tkn, 1, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->mtuInitial = (S16)tmp;
         break;

      case 15:                   /* mtuMinInitial */
         ret = sbISParsU32(tkn, 1, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->mtuMinInitial = (S16)tmp;
         break;

      case 16:                   /* mtuMaxInitial */
         ret = sbISParsU32(tkn, 1, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->mtuMaxInitial = (S16)tmp;
         break;

      case 17:                   /* performMtu */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->performMtu = (S16)tmp;
         break;

      case 18:                   /* timRes */
         ret = sbISParsU32(tkn, 1, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->timeRes = (S16)tmp;
         break;

      case 19:                   /* maxInitReTx */
         ret = sbISParsU32(tkn, 1, MAX_U8, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.maxInitReTx = (U8)tmp;
         break;

      case 20:                   /* maxAssocReTx */
         ret = sbISParsU32(tkn, 1, MAX_U8, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.maxAssocReTx = (U8)tmp;
         break;

      case 21:                   /* maxPathReTx */
         ret = sbISParsU32(tkn, 1, MAX_U8, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.maxPathReTx = (U8)tmp;
         break;

      case 22:                   /* altAcceptFlg */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.altAcceptFlg = (Bool)tmp;
         break;

      case 23:                   /* keyTm */
         ret = sbISParsU32(tkn, 1, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.keyTm = (U16)tmp;
         break;

      case 24:                   /* alpha */
         ret = sbISParsU32(tkn, 1, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.alpha = (S16)tmp;
         break;

      case 25:                   /* beta */
         ret = sbISParsU32(tkn, 1, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.beta = (S16)tmp;
         break;

     case 26 :                        /* hostname */
       {
         if (!tkn->args[0].pres || *tkn->args[0].val != '=')
               sbICPrntError("sbISParsU32: equals sign missing\n");
 
         if (!tkn->args[1].pres)
         {
           sbICPrntError("sbISParsU32: arg not present");
           RETVALUE(RFAILED);
         }
         cmMemcpy(cfg->hostname, tkn->args[1].val, cmStrlen(tkn->args[1].val)+1);
      }
        break;
      case 27:                        /* use hostname flag */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->useHstName = (Bool)tmp;
         break;


      case 28:                   /* endCfg */
         if (optDebug >= 1)
         sbICPrntCfgReq(STSBGEN);
         break;

      default:
        sbICPrntError("sbICGenCfg: bad token");
        RETVALUE(RFAILED);

   }

   RETVALUE(ROK);
} /* end of sbICGenCfg */


#ifdef ANSI
PUBLIC S16 sbICParsSctSapCfg
(
OsFile *inFile
)
#else
PUBLIC S16 sbICParsSctSapCfg (inFile)
OsFile *inFile;
#endif
{

   S8 line[LINELEN];
   S8 *ret;
   CfTkn tkn;

   TRC2(sbICParsSctSapCfg)

   lineNo=1;

   for(;;)
   {
      ret = osFgets(line, LINELEN, inFile);
      if (ret == (S8*)-1 || ret == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
            osPrintf("%s(%d): sb.sctcfg end of file reached. line %d\n", __FILE__, __LINE__, lineNo);
         break;
      }
      if (optDebug >= 2)
         osPrintf("lineNo = %d\n", lineNo);

      if (!osStripBlanks(line))
      {
         lineNo++;
         continue;              /* blank line */
      }

      if (*line == '#')
      {
         lineNo++;
         continue;              /* blank line */
      }

      /* convert line to tokens */
      if (sbISLineToTkn(line, &tkn) == -1)
      {
         osPrintf("%s(%d): syntax error reading file sb.sctcfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      if(sbICSctSapCfg(1,&tkn) == RFAILED)
      {
         osPrintf("%s(%d): syntax error reading file sb.sctcfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      lineNo++; /* default case. just increment line number */

   } /* end of for loop */

   RETVALUE(ROK);
} /* end of cfParseSctSapCfgFile */


/*
 *
 *       Fun:   sbICSctSapCfg
 *
 *       Desc:  parse sb SctSap
 *
 *       Ret:   ROK on success
 *              RFAILED on error
 *
 *       Notes:
 *
         File:  cfv2_sb1.c
 *
 */
#ifdef ANSI
PUBLIC S16 sbICSctSapCfg
(
U8     id,
CfTkn *tkn
)
#else
PUBLIC S16 sbICSctSapCfg(id, tkn)
U8     id;
CfTkn *tkn;
#endif
{
   PRIVATE SbSctSapCfg *cfg = NULLP;
   SbCfg defCfg;
   Pst  *pst;
   S32 val;
   S32 ret;
   U32 tmp;

   TRC3(sbICSctSapCfg)

   pst = (Pst *)&cfgReq.pst;

   val=osMatchKeyword(sbSctSap_kw, (S8*)tkn->tok.val);
   switch(val)
   {
      case 0:                   /* beginCfg */

         sbICDefCfgReq(&defCfg, STSBSCTSAP);
         osMemcpy((OsVoid *)&cfgReq.sctSapCfg, (CONST OsVoid *)&defCfg.s.sctSapCfg,
                     sizeof(SbSctSapCfg));

         cfg = (SbSctSapCfg *)&cfgReq.sctSapCfg;
         break;

      case 1:                   /* swtch */
         ret = sbISMatchKw(sbSw_kw, tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->swtch = (Swtch)tmp;
         break;
      case 2:                   /* spId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->spId = (U16)tmp;
         break;
      case 3:                   /* selector */
         ret = PARSE_SELECTOR(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->sel = (Selector)tmp;
         pst->selector= cfg->sel;
         break;
      case 4:                   /* mem.region */
         ret = PARSE_REGION(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->memId.region = (Region)tmp;
         pst->region = cfg->memId.region;
         break;
      case 5:                  /* mem.pool */
         ret = PARSE_POOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->memId.pool = (Pool)tmp;
         pst->pool = cfg->memId.pool;
         break;
      case 6:                  /* prior */
         ret = PARSE_PRIOR(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->prior = (Prior)tmp;
         pst->prior = cfg->prior;
         break;
      case 7:                  /* route */
         ret = PARSE_ROUTE(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->route = (Route)tmp;
         pst->route = cfg->route;
         break;
      case 8:                   /* maxAckDelayTm */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.maxAckDelayTm = (U16)tmp;
         break;
      case 9:                   /* maxAckDelayDg */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.maxAckDelayDg = (U16)tmp;
         break;
      case 10:                   /* initTm */
         break;
      case 11:                   /* shtDwnTm */
         break;
      case 12:                   /* rtoInitial */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.rtoInitial = (SctRTT)tmp;
         break;
      case 13:                  /* rtoMin */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.rtoMin = (SctRTT)tmp;
         break;
      case 14:                  /* rtoMax */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.rtoMax = (SctRTT)tmp;
         break;
      case 15:                  /* freezeTm */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.freezeTm = (U16)tmp;
         break;
      case 16:                  /* cookieLife */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.cookieLife = (U16)tmp;
         break;
      case 17:                  /* intervalTm */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.intervalTm = (U16)tmp;
         break;
      case 18:                  /* handleInitFlg */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.handleInitFlg = (Bool)tmp;
         break;
      case 19:                  /* negAbrtFlg */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.negAbrtFlg = (Bool)tmp;
         break;
      case 20:                  /* hBeatEnable */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.hBeatEnable = (Bool)tmp;
         break;
      case 21:                  /* flcUpThr */
         ret = sbISParsU32(tkn, 0, MAX_U32, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.flcUpThr = (U32)tmp;
         break;
      case 22:                  /* flcLowThr */
         ret = sbISParsU32(tkn, 0, MAX_U32, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.flcLowThr = (U32)tmp;
         break;
      case 23:                   /* endCfg */
         if (optDebug >= 1)
         sbICPrntCfgReq(STSBSCTSAP);
         break;
      default:
        sbICPrntError("sbParseNSapCfg: bad token");
        RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /* end of sbICSctSapCfg */


#ifdef ANSI
PUBLIC S16 sbICParsTSapCfg
(
OsFile *inFile
)
#else
PUBLIC S16 sbICParsTSapCfg (inFile)
OsFile *inFile;
#endif
{

   S8 line[LINELEN];
   S8 *ret;
   CfTkn tkn;

   TRC2(sbICParsTSapCfg)

   lineNo=1;

   for(;;)
   {
      ret = osFgets(line, LINELEN, inFile);
      if (ret == (S8*)-1 || ret == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
            osPrintf("%s(%d): sb.tsapcfg end of file reached. line %d\n", __FILE__, __LINE__, lineNo);
         break;
      }
      if (optDebug >= 2)
         osPrintf("lineNo = %d\n", lineNo);

      if (!osStripBlanks(line))
      {
         lineNo++;
         continue;              /* blank line */
      }

      if (*line == '#')
      {
         lineNo++;
         continue;              /* blank line */
      }

      /* convert line to tokens */
      if (sbISLineToTkn(line, &tkn) == -1)
      {
         osPrintf("%s(%d): syntax error reading file sb.tsapcfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      if(sbICTSapCfg(1,&tkn) == RFAILED)
      {
         osPrintf("%s(%d): syntax error reading file sb.tsapcfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      lineNo++; /* default case. just increment line number */

   } /* end of for loop */

   RETVALUE(ROK);
} /* end of sbICParsTSapCfg */


/*
 *
 *       Fun:   sbICTSapCfg
 *
 *       Desc:  parse sb TSap
 *
 *       Ret:   ROK on success
 *              RFAILED on error
 *
 *       Notes:
 *
         File:  cfv2_sb1.c
 *
 */
#ifdef ANSI
PUBLIC S16 sbICTSapCfg
(
U8     id,
CfTkn *tkn
)
#else
PUBLIC S16 sbICTSapCfg(id, tkn)
U8     id;
CfTkn *tkn;
#endif
{
   PRIVATE SbTSapCfg *cfg = NULLP;
   SbCfg defCfg;
   Pst   *tPst;
   S32 val;
   S32 ret;
   U32 tmp;

   TRC3(sbICTSapCfg)

   tPst=(Pst*)&cfgReq.tPst;

   val = osMatchKeyword(sbTSap_kw, (S8*)tkn->tok.val);
   switch(val)
   {
      case 0:                   /* beginCfg */

         sbICDefCfgReq(&defCfg, STSBTSAP);
         osMemcpy((OsVoid*)&cfgReq.tSapCfg, (CONST OsVoid *)&defCfg.s.tSapCfg,
                     sizeof(SbTSapCfg));
         cfg = (SbTSapCfg*)&cfgReq.tSapCfg;
         break;
      case 1:                   /* swtch */
         ret = sbISMatchKw(sbSw_kw, tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->swtch = (Swtch)tmp;
         break;
      case 2:                   /* suId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->suId = (U16)tmp;
         break;
      case 3:                   /* selector */
         ret = PARSE_SELECTOR(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->sel = (Selector)tmp;
         tPst->selector=cfg->sel;
         break;
      case 4:                   /* ent */
         ret = PARSE_ENTITY(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->ent = (Ent)tmp;
         tPst->dstEnt = (Ent) cfg->ent;
         break;
      case 5:                   /* inst */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->inst = (Inst)tmp;
         tPst->dstInst = cfg->inst;
         break;
      case 6:                   /* ProcId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->procId = (ProcId)tmp;
         tPst->dstProcId = cfg->procId;
         break;
      case 7:                   /* memregion */
         ret = PARSE_REGION(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->memId.region = (Region)tmp;
         tPst->region = cfg->memId.region;
         break;
      case 8:                   /* mem.pool */
         ret = PARSE_POOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->memId.pool = (Pool)tmp;
         tPst->pool = cfg->memId.pool;
         break;
      case 9:                  /* prior */
         ret = PARSE_PRIOR(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->prior = (Prior)tmp;
         tPst->prior = cfg->prior;
         break;
      case 10:                  /* route */
         ret = PARSE_ROUTE(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->route = (Route)tmp;
         tPst->route = cfg->route;
         break;
      case 11:                  /* srcAddr */
         ret = sbISParsSrcAddr(tkn,&cfg->srcNAddrLst);
         if(ret != ROK)
            RETVALUE(ret);
         break;
      case 12:                   /* spId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.spId = (SpId)tmp;
         break;
      case 13:                   /* maxBndRetry */
         ret = sbISParsU32(tkn, 0, MAX_U8, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.maxBndRetry = (U8)tmp;
         break;
      case 14:                   /* tIntTmr */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.tIntTmr = (U16)tmp;
         break;
      case 15 :                        /* use DNS flag */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.sbDnsCfg.useDnsLib = (S16)tmp;
         break;
 
      case 16 :                        /* DNS address */
         ret = sbISParsTptAddr(tkn,&cfg->reConfig.sbDnsCfg.dnsAddr);
         if (ret != ROK)
            RETVALUE(ret);
         break;
      case 17 :                        /* DNS timeout */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.sbDnsCfg.dnsTmOut = (U16)tmp;
         break;
      case 18 :                        /* max RXT timeout */
         ret = sbISParsU32(tkn, 0, MAX_U8, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         cfg->reConfig.sbDnsCfg.maxRtxCnt = (U16)tmp;
         break;
      case 19:                   /* endCfg */
         if (optDebug >= 1)
         sbICPrntCfgReq(STSBTSAP);
         break;
      default:
         sbICPrntError("sbICTSapCfg: bad token");
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /* end of sbICTSapCfg */


/*
*
*       Fun:   sbICPrntCfgReq
*
*       Desc:
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes:
*
*       File:  cfv2_sb1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbICPrntCfgReq
(
U8 id
)
#else
PUBLIC S16 sbICPrntCfgReq(id)
U8 id;
#endif
{
   U16 i;
   TRC2(sbICPrntCfgReq)

   switch(id)
   {
      case STSBGEN:
      {
         SbGenCfg *gen;

         osPrintf("\nSP GEN CFG:\n");

         gen = (SbGenCfg *)&cfgReq.genCfg;

         osPrintf("gen->serviceType = %#x\n", gen->serviceType);
         osPrintf("gen->maxNmbSctSaps = %#x\n", gen->maxNmbSctSaps);
         osPrintf("gen->maxNmbTSaps = %#x\n", gen->maxNmbTSaps);
         osPrintf("gen->maxNmbEndp = %#x\n", gen->maxNmbEndp);
         osPrintf("gen->maxNmbAssoc = %#x\n", gen->maxNmbAssoc);
         osPrintf("gen->maxNmbDstAddr = %#x\n", gen->maxNmbDstAddr);
         osPrintf("gen->maxNmbSrcAddr = %#x\n", gen->maxNmbSrcAddr);
         osPrintf("gen->maxNmbTxChunks = %#x\n", gen->maxNmbTxChunks);
         osPrintf("gen->maxNmbRxChunks = %#x\n", gen->maxNmbRxChunks);
         osPrintf("gen->maxNmbInStrms = %#x\n", gen->maxNmbInStrms);
         osPrintf("gen->maxNmbOutStrms = %#x\n", gen->maxNmbOutStrms);
         osPrintf("gen->initARwd = %#x\n", gen->initARwnd);
         osPrintf("gen->mtuInitial = %#x\n", gen->mtuInitial);
         osPrintf("gen->mtuMinInitial = %#x\n", gen->mtuMinInitial);
         osPrintf("gen->mtuMaxInitial = %#x\n", gen->mtuMaxInitial);
         osPrintf("gen->performMtu = %s\n",(gen->performMtu) ? "TRUE":"FALSE");
         osPrintf("gen->timeRes = %#x\n", gen->timeRes);
         osPrintf("gen->reConfig.maxInitReTx = %#x\n", gen->reConfig.maxInitReTx);
         osPrintf("gen->reConfig.maxAssocReTx = %#x\n", gen->reConfig.maxAssocReTx);
         osPrintf("gen->reConfig.maxPathReTx = %#x\n", gen->reConfig.maxPathReTx);
         osPrintf("gen->reConfig.altAcceptFlg = %s\n", (gen->reConfig.altAcceptFlg) ? "TRUE" : "FALSE");
         osPrintf("gen->reConfig.keyTm = %#x\n", gen->reConfig.keyTm);
         osPrintf("gen->reConfig.alpha = %#x\n", gen->reConfig.alpha);
         osPrintf("gen->reConfig.beta = %#x\n", gen->reConfig.beta);
         osPrintf("gen->hostname = %#x\n", gen->hostname);
         osPrintf("gen->useHstName = %#x\n", gen->useHstName);
         osPrintf("gen->reConfig.altAcceptFlg : %s \n",
                  ((gen->reConfig.altAcceptFlg) ? "TRUE" : "FALSE"));

         break;
      }
      case STSBSCTSAP:
      {
         SbSctSapCfg *sbSctSap;

         osPrintf("\nSP SctSap CFG:\n");

         sbSctSap = (SbSctSapCfg*)&cfgReq.sctSapCfg;


         osPrintf(" sbSctSap->swtch = %#x\n ",sbSctSap->swtch);
         osPrintf(" sbSctSap->spId = %#x\n ",sbSctSap->spId);
         osPrintf(" sbSctSap->sel = %#x\n ",sbSctSap->sel);
         osPrintf(" sbSctSap->memId.region = %#x\n ",sbSctSap->memId.region);
         osPrintf(" sbSctSap->memId.pool = %#x\n ",sbSctSap->memId.pool);
         osPrintf(" sbSctSap->prior = %#x\n ",sbSctSap->prior);
         osPrintf(" sbSctSap->route = %#x\n ",sbSctSap->route);
         osPrintf(" sbSctSap->reConfig.maxAckDelayTm = %#x\n ",sbSctSap->reConfig.maxAckDelayTm);
         osPrintf(" sbSctSap->reConfig.maxAckDelayDg = %#x\n ",sbSctSap->reConfig.maxAckDelayDg);
         osPrintf(" sbSctSap->reConfig.rtoInitial = %#x\n ",sbSctSap->reConfig.rtoInitial);
         osPrintf(" sbSctSap->reConfig.rtoMin = %#x\n ",sbSctSap->reConfig.rtoMin);
         osPrintf(" sbSctSap->reConfig.rtoMax = %#x\n ",sbSctSap->reConfig.rtoMax);
         osPrintf(" sbSctSap->reConfig.freezeTm = %#x\n ",sbSctSap->reConfig.freezeTm);
         osPrintf(" sbSctSap->reConfig.handleInitFlg = %s\n ",(sbSctSap->reConfig.handleInitFlg) ? "TRUE" : "FALSE");
         osPrintf(" sbSctSap->reConfig.negAbrtFlg = %s\n ",(sbSctSap->reConfig.negAbrtFlg) ? "TRUE" : "FALSE");
         osPrintf(" sbSctSap->reConfig.flcUpThr = %#x\n ",sbSctSap->reConfig.flcUpThr);
         osPrintf(" sbSctSap->reConfig.flcLowThr = %#x\n ",sbSctSap->reConfig.flcLowThr);

         break;
      }
      case STSBTSAP:
      {
         SbTSapCfg *sbTSap;

         osPrintf("\nSP Sap CFG:\n");

         sbTSap = (SbTSapCfg*)&cfgReq.tSapCfg;


        osPrintf(" sbTSap->swtch = %#x\n ",sbTSap->swtch);
        osPrintf(" sbTSap->suId = %#x \n",sbTSap->suId);
        osPrintf(" sbTSap->selector = %#x\n ",sbTSap->sel);
        osPrintf(" sbTSap->ent = %#x\n ",sbTSap->ent);
        osPrintf(" sbTSap->inst = %#x\n ",sbTSap->inst);
        osPrintf(" sbTSap->procId = %#x\n ",sbTSap->procId);
        osPrintf(" sbTSap->memId.region = %#x\n ",sbTSap->memId.region);
        osPrintf(" sbTSap->memId.pool = %#x\n ",sbTSap->memId.pool);
        osPrintf(" sbTSap->prior = %#x\n ",sbTSap->prior);
        osPrintf(" sbTSap->route = %#x\n ",sbTSap->route);
        osPrintf(" sbTSap->reConfig.spId = %#x\n ",sbTSap->reConfig.spId);
        osPrintf(" sbTSap->reConfig.maxBndRetry = %#x\n ",sbTSap->reConfig.maxBndRetry);
        osPrintf(" sbTSap->reConfig.tIntTmr = %#x\n ",sbTSap->reConfig.tIntTmr);
        osPrintf(" sbTSap->reConfig.sbDnsCfg.useDnsLib = %#x\n ",sbTSap->reConfig.sbDnsCfg.useDnsLib);
        osPrintf(" sbTSap->reConfig.sbDnsCfg.dnsAddr = %#x\n ",sbTSap->reConfig.sbDnsCfg.dnsAddr);
        osPrintf(" sbTSap->reConfig.sbDnsCfg.dnsTmOut = %#x\n ",sbTSap->reConfig.sbDnsCfg.dnsTmOut);
        osPrintf(" sbTSap->reConfig.sbDnsCfg.maxRtxCnt = %#x\n ",sbTSap->reConfig.sbDnsCfg.maxRtxCnt);
        osPrintf(" sbTSap->srcNAddrLst.nmb = %#x\n ",sbTSap->srcNAddrLst.nmb);
        for(i=0;i<sbTSap->srcNAddrLst.nmb;i++)
        {

          osPrintf(" Type  : %d  - sbTSap->srcNAddrLst.nAddr[i].u.ipv4NetAddr = %#x\n ",sbTSap->srcNAddrLst.nAddr[i].type,sbTSap->srcNAddrLst.nAddr[i].u.ipv4NetAddr);

        }

         break;
      }
      default:
         break;

   }

   RETVALUE(ROK);
} /* end of sbICPrntCfgReq */


/*
*
*       Fun:   sbICDefCfgReq
*
*       Desc:
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes:
*
*       File:  cfv2_sb1.c
*
*/
#ifdef ANSI
PUBLIC Void sbICDefCfgReq
(
SbCfg *cfg,
U8 id
)
#else
PUBLIC Void sbICDefCfgReq(cfg, id)
SbCfg *cfg;
U8 id;
#endif
{

   TRC2(sbICDefCfgReq)

   switch(id)
   {
      case STSBGEN:
      {
         SbGenCfg *gen;
         gen = &cfg->s.genCfg;

        gen->serviceType     = HI_SRVC_RAW_SCTP;
         gen->maxNmbSctSaps   = 1;
        gen->maxNmbTSaps     = 1;
        gen->maxNmbEndp      = 4;
        gen->maxNmbAssoc     = 10;
        gen->maxNmbDstAddr   = 20;
        gen->maxNmbSrcAddr   = 5;
        gen->maxNmbTxChunks  = 256;
        gen->maxNmbRxChunks  = 256;
        gen->maxNmbInStrms   = 10;
        gen->maxNmbOutStrms  = 10;
        gen->initARwnd       = 1000000;
        gen->mtuInitial      = 512;
        gen->mtuMinInitial   = 512;
        gen->mtuMaxInitial   = 1024;
        gen->performMtu      = TRUE;
        gen->timeRes         = 1;
        gen->reConfig.maxInitReTx     = 3;
        gen->reConfig.maxAssocReTx    = 5;
        gen->reConfig.maxPathReTx     = 5;
        gen->reConfig.altAcceptFlg    = FALSE;
        gen->reConfig.keyTm           = 30;
        gen->reConfig.alpha           = 10;
        gen->reConfig.beta            = 10;
        osStrcpy(gen->hostname, "none");
        gen->useHstName      = FALSE;

        break;
      }
      case STSBSCTSAP:
      {
        SbSctSapCfg *sbSctSap;

        sbSctSap = &cfg->s.sctSapCfg;

        sbSctSap->swtch           = LSB_SW_RFC_REL0;
        sbSctSap->spId            = 0;
        sbSctSap->sel             = SEL_LC;
        sbSctSap->memId.region       = DFLT_REGION;
        sbSctSap->memId.pool         = DFLT_POOL;
        sbSctSap->prior           = PRIOR0;
        sbSctSap->route           = RTESPEC;
        sbSctSap->reConfig.maxAckDelayTm   = 2;
        sbSctSap->reConfig.maxAckDelayDg   = 2;
        sbSctSap->reConfig.rtoInitial      = 30;
        sbSctSap->reConfig.rtoMin          = 20;
        sbSctSap->reConfig.rtoMax          = 40;
        sbSctSap->reConfig.freezeTm        = 30;
        sbSctSap->reConfig.cookieLife      = 20;
        sbSctSap->reConfig.intervalTm      = 20;
        sbSctSap->reConfig.handleInitFlg   = FALSE;
        sbSctSap->reConfig.negAbrtFlg      = TRUE;
        sbSctSap->reConfig.flcUpThr        = 75;
        sbSctSap->reConfig.flcLowThr       = 25;

        break;
      }
      case STSBTSAP:
      {
        SbTSapCfg *sbTSap;

        sbTSap = &cfg->s.tSapCfg;

        sbTSap->swtch           = 1; /* LSB_SW_RFC_REL0;*/
        sbTSap->suId            = 0;
        sbTSap->sel             = SEL_LC;
        sbTSap->ent             = ENTHI;
        sbTSap->inst            = 0;
        sbTSap->procId          = 101;
        sbTSap->memId.region    = DFLT_REGION;
        sbTSap->memId.pool      = DFLT_POOL;
        sbTSap->prior           = PRIOR0;
        sbTSap->route           = RTESPEC;
        sbTSap->srcNAddrLst.nmb = 1;
        sbTSap->srcNAddrLst.nAddr[0].type = CM_NETADDR_IPV4;
        sbTSap->srcNAddrLst.nAddr[0].u.ipv4NetAddr=0;
        sbTSap->reConfig.spId        = 0;
        sbTSap->reConfig.maxBndRetry = 3;
        sbTSap->reConfig.tIntTmr     = 20;
        sbTSap->reConfig.sbDnsCfg.useDnsLib   = FALSE;
        sbTSap->reConfig.sbDnsCfg.dnsAddr.u.ipv4TptAddr.address = 0;
        sbTSap->reConfig.sbDnsCfg.dnsTmOut    = 3;
        sbTSap->reConfig.sbDnsCfg.maxRtxCnt   = 1;

        break;
      }
      default:
         break;

   }
   RETVOID;
} /* end of sbICDefCfgReq */



/*********** HI Configuration ****************/


/*
*
*       Fun:   hiAccGenCfg
*
*       Desc:  This function is used to do the General Configuration of
*              TUCL
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbIChiGenCfg
(
Ent     ent,             /* entity id */
Inst    inst             /* instance id */
)
#else
PUBLIC S16 sbIChiGenCfg(ent, inst)
Ent     ent;             /* entity id */
Inst    inst;            /* instance id */
#endif
{

   HiMngmt  cfg;
   Pst   pst;


   TRC2(sbIChiGenCfg)

   /* TUCL intiliazation in progress */

   /* clear the config structure first */
   HI_ZERO((U8 *) &cfg, sizeof(HiMngmt));

   /* prepare header */
   cfg.hdr.entId.ent   = ent;                /* entity */
   cfg.hdr.entId.inst  = inst;               /* instance */
   cfg.hdr.elmId.elmnt = STGEN;              /* general */
   cfg.hdr.transId     = HI_ACC_TRANSID;     /* transaction identifier */

#ifdef LCHIMILHI
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_LC);
#else
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_TC);
#endif

   cfg.t.cfg.s.hiGen.numSaps = HI_ACC_NUMBSAPS;
   cfg.t.cfg.s.hiGen.numCons = HI_ACC_NMBCONS;
#ifdef HI_REL_1_2
   cfg.t.cfg.s.hiGen.numFdsPerSet = HI_MAX_FD_PER_FD_SET;
   cfg.t.cfg.s.hiGen.numFdBins = HI_FD_BLK_NUM_BINS;
#endif /* HI_REL_1_2 */
   cfg.t.cfg.s.hiGen.permTsk = HI_ACC_PERM_TSK_FLAG;
   cfg.t.cfg.s.hiGen.schdTmrVal = HI_ACC_SCHDTMR_VAL;
   cfg.t.cfg.s.hiGen.poolStrtThr = 4;
   cfg.t.cfg.s.hiGen.poolDropThr = 2;
   cfg.t.cfg.s.hiGen.poolStopThr = 5;
   cfg.t.cfg.s.hiGen.timeRes = 0;      /* unused */

   /* Layer Manager */
#ifdef LCHIMILHI
   cfg.t.cfg.s.hiGen.lmPst.selector  = LHI_LC;     /* selector */
#else
   cfg.t.cfg.s.hiGen.lmPst.selector  = LHI_TC;     /* selector */
#endif

   cfg.t.cfg.s.hiGen.lmPst.region    = TSTREG;        /* region */
   cfg.t.cfg.s.hiGen.lmPst.pool      = TSTPOOL;       /* pool */
   cfg.t.cfg.s.hiGen.lmPst.prior     = PRIOR0;        /* priority */
   cfg.t.cfg.s.hiGen.lmPst.route     = RTESPEC;       /* route */

   cfg.t.cfg.s.hiGen.lmPst.dstEnt    = ENTSM;         /* dst entity */
   cfg.t.cfg.s.hiGen.lmPst.dstInst   = TSTINST;       /* dst inst */
   cfg.t.cfg.s.hiGen.lmPst.dstProcId = SFndProcId();  /* dst proc id */

   cfg.t.cfg.s.hiGen.lmPst.srcEnt    = ENTHI;         /* src entity */
   cfg.t.cfg.s.hiGen.lmPst.srcInst   = TSTINST;       /* src inst */
   cfg.t.cfg.s.hiGen.lmPst.srcProcId = SFndProcId();  /* src proc id */

   pst.selector = 1;
   (Void) SmMiLhiCfgReq(&pst, &cfg);

   RETVALUE(ROK);
}/* end of  sbIChiGenCfg()*/


/*
*
*       Fun:   hiAccSapCfg
*
*       Desc:  This function is used to configure a transport SAP
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbIChiSapCfg
(
SpId  spId                /* service provider id for HI SAP */
)
#else
PUBLIC S16 sbIChiSapCfg(spId)
SpId  spId;               /* service provider id for HI SAP */
#endif
{

   HiMngmt   cfg;

   Pst pst;
   TRC2(sbIChiSapCfg)

   /* clear the config structure first */
   HI_ZERO((U8 *) &cfg, sizeof(HiMngmt));

   /* prepare header */
   cfg.hdr.entId.ent   = ENTHI;           /* entity */
   cfg.hdr.entId.inst  = TSTINST;         /* instance */
   cfg.hdr.elmId.elmnt = STTSAP;          /* general */
   cfg.hdr.transId     = HI_ACC_TRANSID;  /* transaction identifier */

#ifdef LCHIMILHI
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_LC);
#else
   HI_ACC_SET_RESP(cfg.hdr.response, 7);
#endif

   cfg.t.cfg.s.hiSap.spId            = spId;
   cfg.t.cfg.s.hiSap.flcEnb          = HI_ACC_SAP_FLC_ENB_FLAG;
   cfg.t.cfg.s.hiSap.txqCongStrtLim  = HI_ACC_SAP_FLC_STRT_LIM;
   cfg.t.cfg.s.hiSap.txqCongDropLim  = HI_ACC_SAP_FLC_DRP_LIM;
   cfg.t.cfg.s.hiSap.txqCongStopLim  = HI_ACC_SAP_FLC_STP_LIM;
   cfg.t.cfg.s.hiSap.numBins         = HI_ACC_SAP_NMB_BINS;

   /* update the upper interface parameters */
#ifdef LCHIUIHIT
   cfg.t.cfg.s.hiSap.uiSel = HI_UISEL_LC;  /* loosely coupled */
#else
   cfg.t.cfg.s.hiSap.uiSel = 6;  /* tightly coupled */
#endif

   cfg.t.cfg.s.hiSap.uiMemId.region = TSTREG;  /* defualt priority */
   cfg.t.cfg.s.hiSap.uiMemId.pool   = TSTPOOL; /* defualt priority */
   cfg.t.cfg.s.hiSap.uiPrior        = PRIOR0;  /* defualt priority */
   cfg.t.cfg.s.hiSap.uiRoute        = RTESPEC; /* default route */

   /* create sample header profiles */

   /* LHI_LEN_INCL_HDR bit should be SET in the flag for headers which
    * include both header and PDU length in the length field (in the
    * header!)
    */

   /* profile_1 : srvcType value = 3 (GTP header format) */
   cfg.t.cfg.s.hiSap.hdrInf[0].hdrLen = 20;
   cfg.t.cfg.s.hiSap.hdrInf[0].offLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[0].lenLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[0].flag   = 0; /* length in the header is
                                            * only PDU length */

   /* profile_2 : srvcType value = 4 (LDP header format) */
   cfg.t.cfg.s.hiSap.hdrInf[1].hdrLen = 10;
   cfg.t.cfg.s.hiSap.hdrInf[1].offLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[1].lenLen = 2;
   cfg.t.cfg.s.hiSap.hdrInf[0].flag   = 0;

   /* profile_3 : srvcType value = 5 */

   /* profile_4 : srvcType value = 6 */

   /* profile_5 : srvcType value = 7 */


   pst.selector = 1;
   /* give configuration request to layer */
   (Void) SmMiLhiCfgReq(&pst, &cfg);

   RETVALUE(ROK);
}/* end of  sbIChiSapCfg()*/


/* functions for endpoint open reqest */

#ifdef ANSI
PUBLIC S16 sbICParsEndpCfg
(
OsFile *inFile,
U16   *idx
)
#else
PUBLIC S16 sbICParsEndpCfg (inFile,idx)
OsFile *inFile;
U16   *idx;
#endif
{

   S8 line[LINELEN];
   S8 *ret;
   CfTkn tkn;
   U16 i;

   TRC2(sbICParsEndpCfg)

   for(i=0;i<MAXBLOCKS;i++)
   {
    if(endp[i].occupied)
       continue;
    else
      break;
   }

   if(i == MAXBLOCKS)
   {
     osPrintf(" Endpoints Limit Reached \n");
     RETVALUE(RFAILED);
   }

   *idx=i;

   lineNo=1;

   for(;;)
   {
      ret = osFgets(line, LINELEN, inFile);
      if (ret == (S8*)-1 || ret == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
            osPrintf("%s(%d): sb.endpcfg end of file reached. line %d\n", __FILE__, __LINE__, lineNo);
         break;
      }
      if (optDebug >= 2)
         osPrintf("lineNo = %d\n", lineNo);

      if (!osStripBlanks(line))
      {
         lineNo++;
         continue;              /* blank line */
      }

      if (*line == '#')
      {
         lineNo++;
         continue;              /* blank line */
      }

      /* convert line to tokens */
      if (sbISLineToTkn(line, &tkn) == -1)
      {
         osPrintf("%s(%d): syntax error reading file sb.endpcfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      if(sbICEndpCfg(&endp[i],&tkn) == RFAILED)
      {
         osPrintf("%s(%d): syntax error reading file sb.endpcfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      lineNo++; /* default case. just increment line number */

   } /* end of for loop */

   endp[i].occupied = TRUE;

   sbICPrntData(ENDPREQ,i);

   RETVALUE(ROK);

} /* end of sbICParsEndpCfg */



#ifdef ANSI
PUBLIC S16 sbICEndpCfg
(
Endp *endpPtr,
CfTkn *tkn
)
#else
PUBLIC S16 sbICEndpCfg(endpPtr, tkn)
Endp *endpPtr;
CfTkn *tkn;
#endif
{
   S32 val;
   Pst  *pst;
   S32 ret;
   U32 tmp;
   pst = (Pst*)&endpPtr->pst;


   TRC3(sbICEndpCfg)


   
   val = osMatchKeyword(sbEndp_kw, (S8*)tkn->tok.val);
   switch(val)
   {
      case 0:                   /* beginCfg */
         cmMemset((U8 *)endpPtr, 0, sizeof(Endp));
         pst->dstProcId = SFndProcId();
          pst->srcProcId = SFndProcId();
          pst->dstEnt = ENTSB;
          pst->srcEnt = ENTIT;
          pst->dstInst = 0;
          pst->srcInst = 0;
          pst->prior = 0;
          pst->route = RTESPEC;
          pst->event = SCT_EVTDATREQ;
          pst->region = 0;
          pst->pool = 0;
          pst->selector = 0;
          pst->spare1 = 0;
          break;
      case 1:                   /* smPst.selector */
        ret = PARSE_SELECTOR(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         pst->selector = (Selector)tmp;
         break;
      case 2:                   /* spId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         endpPtr->spId = (U16)tmp;
         break;
      case 3:                   /* mem.region */
         ret = PARSE_REGION(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         pst->region = (Region)tmp;
         break;
      case 4:                  /* mem.pool */
         ret = PARSE_POOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         pst->pool = (Pool)tmp;
         break;
      case 5:                  /* prior */
         ret = PARSE_PRIOR(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         pst->prior = (Prior)tmp;
         break;
      case 6:                  /* route */
         ret = PARSE_ROUTE(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         pst->route = (Route)tmp;
      case 7:                   /* port */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         endpPtr->port = (U16)tmp;
         break;
      case 8:                   /* suEndpId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         endpPtr->suEndpId = (U16)tmp;
         break;
      case 9:                   /* netaddr */
         ret = sbISParsNetAddr(tkn,&endpPtr->netAddr);
         if (ret != ROK)
            RETVALUE(ret);
         break;
      case 10:                   /* endCfg */
         endpPtr->cfgDone = TRUE;
         break;
      default:
        sbICPrntError("sbICGenCfg: bad token");
        RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}


/* functions for open association request */

#ifdef ANSI
PUBLIC S16 sbICParsAssocReq
(
OsFile *inFile,
U16  *idx
)
#else
PUBLIC S16 sbICParsAssocReq (inFile,idx)
OsFile *inFile;
U16  *idx;
#endif
{

   S8 line[LINELEN];
   S8 *ret;
   CfTkn tkn;
   U16  i;

   TRC2(sbICParsAssocReq)

   for(i=0;i<MAXBLOCKS;i++)
   {
    if(assocReq[i].occupied)
       continue;
    else
      break;
   }

   if(i == MAXBLOCKS)
   {
     osPrintf(" Maximum Association Limit Reached \n");
     RETVALUE(RFAILED);
   }

  *idx=i;

   lineNo=1;

   for(;;)
   {
      ret = osFgets(line, LINELEN, inFile);
      if (ret == (S8*)-1 || ret == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
            osPrintf("%s(%d): sb.assoccfg end of file reached. line %d\n", __FILE__, __LINE__, lineNo);
         break;
      }
      if (optDebug >= 2)
         osPrintf("lineNo = %d\n", lineNo);

      if (!osStripBlanks(line))
      {
         lineNo++;
         continue;              /* blank line */
      }

      if (*line == '#')
      {
         lineNo++;
         continue;              /* blank line */
      }

      /* convert line to tokens */
      if (sbISLineToTkn(line, &tkn) == -1)
      {
         osPrintf("%s(%d): syntax error reading file sb.assoccfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      if(sbICAssocReq(&assocReq[i],&tkn) == RFAILED)
      {
         osPrintf("%s(%d): syntax error reading file sb.assoccfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }

      lineNo++; /* default case. just increment line number */

   } /* end of for loop */
   assocReq[i].occupied = TRUE;
   sbICPrntData(ASSOCREQ,i);

   RETVALUE(ROK);

} /* end of sbICParsAssocReq */

#ifdef ANSI
PUBLIC S16 sbICAssocReq
(
AssocReq *assocInfo,
CfTkn *tkn
)
#else
PUBLIC S16 sbICAssocReq(assocInfo, tkn)
AssocReq *assocInfo;
CfTkn *tkn;
#endif
{
   S32 val;
   S32 ret;
   U32 tmp;


   TRC3(sbICAssocReq)

   val = osMatchKeyword(sbAssoc_kw, (S8*)tkn->tok.val);
   switch(val)
   {
      case 0:                   /* beginCfg */
         cmMemset((U8 *)assocInfo, 0, sizeof(AssocReq));
         break;
      case 1:                   /* spId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         assocInfo->spId = (U16)tmp;
         break;
      case 2:                   /* spEndpId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
          /* Sandeep */
         break;
      case 3:                   /* suAssocId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         assocInfo->suAssocId = (U16)tmp;
         break;
      case 4:                   /* dstNetAddr */
         ret = sbISParsNetAddr(tkn,&assocInfo->dstNetAddr);
         if (ret != ROK)
            RETVALUE(ret);
         break;
      case 5:                   /* dstPort */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         assocInfo->dstPort = (U16)tmp;
         break;
      case 6:                   /* outStrms */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         assocInfo->outStrms = (U16)tmp;
         break;
      case 7:                   /* dstAddrLst */
         ret = sbISParsSrcAddr(tkn,&assocInfo->dstNAddrLst);
         if (ret != ROK)
            RETVALUE(ret);
         break;
      case 8:                   /* srcAddrLst */
         ret = sbISParsSrcAddr(tkn,&assocInfo->srcNAddrLst);
         if (ret != ROK)
            RETVALUE(ret);
         break;
      case 9:                   /* endCfg */
         break;
      default:
        sbICPrntError("sbICAssocReq: bad token");
        RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of sbICAssocReq */


/* functions for data requests */

#ifdef ANSI
PUBLIC S16 sbICParsDataReq
(
OsFile *inFile
)
#else
PUBLIC S16 sbICParsDataReq (inFile)
OsFile *inFile;
#endif
{

   S8 line[LINELEN];
   S8 *ret;
   CfTkn tkn;

   TRC2(sbICParsDataReq)

   lineNo=1;

   for(;;)
   {
      ret = osFgets(line, LINELEN, inFile);
      if (ret == (S8*)-1 || ret == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
            osPrintf("%s(%d): sb.datacfg end of file reached. line %d\n", __FILE__, __LINE__, lineNo);
         break;
      }
      if (optDebug >= 2)
         osPrintf("lineNo = %d\n", lineNo);
      
      if (!osStripBlanks(line)) 
      {
         lineNo++;
         continue;              /* blank line */
      }
      
      if (*line == '#')
      {
         lineNo++;
         continue;              /* blank line */
      }
         
      /* convert line to tokens */
      if (sbISLineToTkn(line, &tkn) == -1)
      {
         osPrintf("%s(%d): syntax error reading file sb.datacfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }
 
      if(sbICDataReq(1,&tkn) == RFAILED)
      {
         osPrintf("%s(%d): syntax error reading file sb.datacfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }
      
      lineNo++; /* default case. just increment line number */
   
   } /* end of for loop */

   RETVALUE(ROK);
} /* end of sbICParsDataReq */

#ifdef ANSI
PUBLIC S16 sbICDataReq
(
U8     id,
CfTkn *tkn
)
#else
PUBLIC S16 sbICDataReq(id, tkn)
U8     id;
CfTkn *tkn;
#endif
{
   S32 val;
   S32 ret;
   U32 tmp;

   
   TRC3(sbICDataReq)

   val = osMatchKeyword(sbDataRq_kw, (S8*)tkn->tok.val);
   switch(val)
   {
      case 0:                   /* beginCfg */
         cmMemset((U8 *)&dataReq, 0, sizeof(DataReq));
         break;
      case 1:                   /* spId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         dataReq.spId = (U16)tmp;
         break;
      case 2:                   /* spAssocId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         break;
      case 3:                   /* dstNetAddr */
         ret = sbISParsNetAddr(tkn,&dataReq.dstNAddr);

         if (dataReq.dstNAddr.u.ipv4NetAddr == 0)
         {
            dataReq.dstNAddr.type = CM_NETADDR_NOTPRSNT; 
         }

         if (ret != ROK)
            RETVALUE(ret);
         break;
      case 4:                   /* StrmId */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         dataReq.strmId = (U16)tmp;
         break;
      case 5:                   /* unorderedFlg */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         dataReq.unorderFlg = (Bool)tmp;
         break;
      case 6:                   /* nobundleFlg */
         ret = PARSE_BOOL(tkn, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         dataReq.nobundleFlg = (Bool)tmp;
         break;
      case 7:                   /* lifeTime */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         dataReq.lifeTime = (U16)tmp;
         break;
      case 8:                   /* protId */
         ret = sbISParsU32(tkn, 0, MAX_U32, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         dataReq.protId = (U32)tmp;
         break;
      case 9:                   /* endCfg */
         if (optDebug >= 1)
         sbICPrntData(DATAREQ,0);
         break;
      default:
        sbICPrntError("sbICDataReq: bad token");
        RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of sbICDataReq */ 


/* function for getting looping information for performance testing */


#ifdef ANSI
PUBLIC S16 sbICParsLoopReq
(
OsFile *inFile
)
#else
PUBLIC S16 sbICParsLoopReq (inFile)
OsFile *inFile;
#endif
{

   S8 line[LINELEN];
   S8 *ret;
   CfTkn tkn;

   TRC2(sbICParsLoopReq)

   lineNo=1;

   for(;;)
   {
      ret = osFgets(line, LINELEN, inFile);
      if (ret == (S8*)-1 || ret == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
           osPrintf("%s(%d): sb.loopcfg end of file reached. line %d\n", __FILE__, __LINE__, lineNo);
         break;
      }
      if (optDebug >= 2)
         osPrintf("lineNo = %d\n", lineNo);
      
      if (!osStripBlanks(line)) 
      {
         lineNo++;
         continue;              /* blank line */
      }
      
      if (*line == '#')
      {
         lineNo++;
         continue;              /* blank line */
      }
         
      /* convert line to tokens */
      if (sbISLineToTkn(line, &tkn) == -1)
      {
         osPrintf("%s(%d): syntax error reading file sb.datacfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }
 
      if(sbICLoopReq(1,&tkn) == RFAILED)
      {
         osPrintf("%s(%d): syntax error reading file sb.datacfg. line %d\n", __FILE__, __LINE__, lineNo);
         RETVALUE(RFAILED);
      }
      
      lineNo++; /* default case. just increment line number */
   
   } /* end of for loop */

   RETVALUE(ROK);
} /* end of sbICParsDataReq */


#ifdef ANSI
PUBLIC S16 sbICLoopReq
(
U8 id,
CfTkn *tkn
)
#else
PUBLIC S16 sbICLoopReq(id, tkn)
U8 id;
CfTkn *tkn;
#endif
{
   S32 val;
   S32 ret;
   U32 tmp;

   
   TRC3(sbICDataReq)

   val = osMatchKeyword(sbLoopRq_kw, (S8*)tkn->tok.val);
   switch(val)
   {
      case 0:                   /* beginCfg */
         cmMemset((U8 *)&loopInfo, 0, sizeof(LoopInfo));
         break;
      case 1:                   /* times */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         loopInfo.times = (U16)tmp;
         break;
      case 2:                   /* size */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         loopInfo.size = (U16)tmp;
         break;
      case 3:                   /* delay */
         ret = sbISParsU32(tkn, 0, MAX_U16, &tmp);
         if (ret != ROK)
            RETVALUE(ret);
         loopInfo.delay = (U16)tmp;
         break;
      case 4 : 
         break; 
      default:                   /* default */
        osPrintf("%s(%d):Default Case for LoopReq \n", __FILE__, __LINE__);
    }
   RETVALUE(ROK);
}

/* function for printing final data */

#ifdef ANSI
PUBLIC S16 sbICPrntData
(
U8 id,
U8 blockIdx
)
#else
PUBLIC S16 sbICPrntData(id,blockIdx)
U8 id;
U8 blockIdx;
#endif
{
   U16   i;

   osPrintf("=====================================================================\n ");
   switch(id)
   {
     case ASSOCREQ :
     {
         osPrintf(" assocReq.spId = %#x\n ",assocReq[blockIdx].spId);
         osPrintf(" assocReq.spEndpId = %#x\n ",assocReq[blockIdx].spEndId);
         osPrintf(" assocReq.suEndpId = %#x\n ",assocReq[blockIdx].suEndId);
         osPrintf(" assocReq.suAssocId = %#x\n ",assocReq[blockIdx].suAssocId);
         osPrintf(" assocReq.dstNetAddr.u.ipv4NetAddr = %#x\n ",assocReq[blockIdx].dstNetAddr.u.ipv4NetAddr);
         osPrintf(" assocReq.dstPort = %#x\n ",assocReq[blockIdx].dstPort);
         osPrintf(" assocReq.outStrms = %#x\n ",assocReq[blockIdx].outStrms);
         osPrintf(" assocReq.inStrms = %#x\n ",assocReq[blockIdx].inStrms);
         osPrintf(" assocReq.occupied = %s\n ",(assocReq[blockIdx].occupied) ? "TRUE" : "FALSE");
         osPrintf(" assocReq.endpIdx = %d\n ",assocReq[blockIdx].endpIdx);
         osPrintf(" assocReq.node = %s\n ",(assocReq[blockIdx].node==1) ? "SERVER" : "CLIENT");

         for(i=0;i<assocReq[blockIdx].srcNAddrLst.nmb;i++)
         {
          osPrintf(" Type  : %d  - assocReq.srcNAddrLst.nAddr[i].u.ipv4NetAddr = %#x\n ", \
                     assocReq[blockIdx].srcNAddrLst.nAddr[i].type,assocReq[blockIdx].srcNAddrLst.nAddr[i].u.ipv4NetAddr);
         }
         for(i=0;i<assocReq[blockIdx].dstNAddrLst.nmb;i++)
         {
          osPrintf(" Type  : %d  - assocReq.dstNAddrLst.nAddr[i].u.ipv4NetAddr = %#x\n ", \
                     assocReq[blockIdx].dstNAddrLst.nAddr[i].type,assocReq[blockIdx].dstNAddrLst.nAddr[i].u.ipv4NetAddr);
         }
     }
     break;

     case ENDPREQ :
     {
         osPrintf(" endp.spId = %#x\n ",endp[blockIdx].spId);
         osPrintf(" endp.pst.selector = %#x\n ",endp[blockIdx].pst.selector);
         osPrintf(" endp.pst.region = %#x\n ",endp[blockIdx].pst.region);
         osPrintf(" endp.pst.pool = %#x\n ",endp[blockIdx].pst.pool);
         osPrintf(" endp.pst.prior = %#x\n ",endp[blockIdx].pst.prior);
         osPrintf(" endp.pst.route = %#x\n ",endp[blockIdx].pst.route);
         osPrintf(" endp.port = %#x\n ",endp[blockIdx].port);
         osPrintf(" endp.netAddr.u.ipv4NetAddr = %#x\n ",endp[blockIdx].netAddr.u.ipv4NetAddr);
         osPrintf(" endp.suEndpId = %#x\n ",endp[blockIdx].suEndpId);
         osPrintf(" endp.spEndpId = %#x\n ",endp[blockIdx].spEndpId);
         osPrintf(" endp.cfgDone = %s\n ",(endp[blockIdx].cfgDone) ? "TRUE" : "FALSE");
         osPrintf(" endp.occupied = %s\n ",(endp[blockIdx].occupied) ? "TRUE" : "FALSE");
     }
     break;

    case DATAREQ :
          {
            osPrintf(" dataReq.spId = %#x\n ",dataReq.spId);
            osPrintf(" dataReq.spAssocId = %#x\n ",dataReq.spAssocId);
            osPrintf(" dataReq.strmId = %#x\n ",dataReq.strmId);
            osPrintf(" dataReq.lifeTime = %#x\n ",dataReq.lifeTime);
            osPrintf(" dataReq.protId = %#x\n ",dataReq.protId);
            osPrintf(" dataReq.netAddr.u.ipv4NetAddr = %#x\n ",dataReq.dstNAddr.u.ipv4NetAddr);
            osPrintf(" dataReq.unorderFlg = %s\n ",(dataReq.unorderFlg) ? "TRUE" : "FALSE");

            osPrintf(" dataReq.nobundleFlg = %s\n ",(dataReq.nobundleFlg) ? "TRUE" : "FALSE");
         }
      break;

      default :
      break;

   }
   osPrintf("=====================================================================\n ");
  RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC Void sbICPrntError
(
Txt *msg
)
#else
PUBLIC Void sbICPrntError(msg)
Txt *msg;
#endif
{

   TRC2(sbICPrntError)

   osPrintf("%s(%d): ERROR %s\n", __FILE__, __LINE__, msg);
   osExit(-1);
} /* end of sbICPrntError */

/********************************************************************30**

         End of file:     sb_icfg.c@@/main/2 - Thu Jul 26 07:54:22 2007

*********************************************************************31*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sb    1. File Added for inter-op SCTP Testing 
/main/2      ---    rsr/ag  1. Updated for Release of 1.3  
*********************************************************************91*/

