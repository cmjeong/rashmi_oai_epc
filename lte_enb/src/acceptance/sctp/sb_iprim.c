/********************************************************************20**

     Name:     sb_iprim.c - inop file

     Type:     C source file

     Desc:     C code for inop 

     File:     sb_iprim.c

     Sid:      sb_iprim.c@@/main/2 - Thu Jul 26 07:54:26 2007

     Prg:      nct

*********************************************************************21*/

/* header include files -- defines (.h) */

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
#include "sb.h"
#include "sb_acc.h"
#include "sb_ibdy.h"


/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timer */
#include "cm_os.x"
#include "cm_hash.x"       /* common hash */
#include "cm_lib.x"
#include "cm_tpt.x"        /* common transport addressing */
#include "cm_dns.x"        /* Common DNS library */
#include "sct.x"           /* SCT Interface */
#include "lsb.x"           /* LSB Interface */
#include "sb_ibdy.x"


/* local defines */

/* these should be defined in lsn.h */


PRIVATE S32 lineNo = 1;                 /* crnt lno in cfg file scan */
EXTERN PUBLIC S8 optDebug;              /* debug */
PUBLIC LoopInfo loopInfo;               /* LoopInfo structure  */


/*
*
*       Fun:   sbIPInitSctp
*
*       Desc:  Initialize the SCT layer
*
*       Ret:   Number of arguments on success
*              RFAILED on error
*
*       Notes:
*
*       File:  cfv2_cr1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbIPInitSctp
(
)
#else
PUBLIC S16 sbIPInitSctp(Void)
#endif
{
   SbMgmt sbMgmt;
   Pst pst;

   TRC2(sbIPInitSctp)

   printf("sbICCfgReq(STSBGEN)\n");
   sbICCfgReq(STSBGEN);
   printf("sbICCfgReq(STSBSCTSAP)\n");
   sbICCfgReq(STSBSCTSAP);
   printf("sbICCfgReq(STSBTSAP)\n");
   sbICCfgReq(STSBTSAP);


   printf("sbIChiGenCfg(ENTHI, 0)\n");
   sbIChiGenCfg(ENTHI,0);
   sbIChiSapCfg(0);

   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
   pst.dstEnt = ENTSB;
   pst.srcEnt = ENTIT;
   pst.dstInst = 0;
   pst.srcInst = 0;
   pst.prior = 2;
   pst.route = RTESPEC;
   pst.event = SCT_EVTDATREQ;
   pst.region = 0;
   pst.pool = 0;
   pst.selector = 1;
   pst.spare1 = 0;


   ItLiSctBndReq(&pst,0, cfgReq.sctSapCfg.spId);

   sbMgmt.t.cntrl.sapId =  0;
   sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
   sbMgmt.hdr.response.selector = 1;
   sbMgmt.t.cntrl.action =  ABND_ENA;
   pst.selector = 1;
   (Void) SmMiLsbCntrlReq(&pst, &sbMgmt);

   RETVALUE(ROK);

} /* end of sbIPInitSctp */


#ifdef ANSI
PUBLIC S16 sbIPEndpOpenReq
(
)
#else
PUBLIC S16 sbIPEndpOpenReq()
#endif
{

   OsFile *cfin;
   U16     idx;

   if ((cfin = (OsFile*)osFopen("sb.endpcfg", "r")) == (S32)NULLP)
   {
     osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "sb.endpcfg");
     RETVALUE(RFAILED);
   }

   if ((sbICParsEndpCfg (cfin,&idx)) == RFAILED)
   {
      osPrintf("%s(%d): Failed parsing file sb.endpcfg\n", __FILE__, __LINE__);
      osExit(-1);
   }
   else
   {

     ItLiSctEndpOpenReq(&endp[idx].pst,endp[idx].spId,endp[idx].suEndpId,
                                   endp[idx].port,&endp[idx].netAddr);

    /* Increment number of Open Endpoints */
   }
   osFclose(cfin);   /* Close file */
   RETVALUE(ROK);
}/* end of sbIPEndpOpenReq */




/**** Association Request Primitive ***********/


#ifdef ANSI
PUBLIC S16 sbIPAssocReq
(
U8 endpIdx
)
#else
PUBLIC S16 sbIPAssocReq(endpIdx)
U8 endpIdx;
#endif
{

   OsFile *cfin;
   U16   idx;

   if(!(endp[endpIdx].occupied))
   {
     osPrintf("%s(%d): Assoc establishment failed, endpoint not occupied\n", __FILE__, __LINE__);
     RETVALUE(RFAILED);
   }

   if ((cfin = (OsFile*)osFopen("sb.assoccfg", "r")) == (S32)NULLP)
   {
     osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "sb.asoccfg");
     RETVALUE(RFAILED);
   }

   if ((sbICParsAssocReq (cfin,&idx)) == RFAILED)
   {
      osPrintf("%s(%d): Failed parsing file sb.assoccfg\n", __FILE__, __LINE__);
      osExit(-1);
   }
   else
   {

     if(endp[endpIdx].cfgDone != TRUE)
     {
      osPrintf("%s(%d): AssocReq Fail, Endp Not Created\n", __FILE__, __LINE__);
      osExit(-1);
     }
     assocReq[idx].spEndId = endp[endpIdx].spEndpId;
     assocReq[idx].endpIdx = endpIdx;
#ifdef SCT3
    ItLiSctAssocReq(&endp[endpIdx].pst, assocReq[idx].spId,
      assocReq[idx].spEndId, assocReq[idx].suAssocId, &assocReq[idx].dstNetAddr,
      assocReq[idx].dstPort, assocReq[idx].outStrms, &assocReq[idx].dstNAddrLst,
      &assocReq[idx].srcNAddrLst, SB_ACC_SCT_TOS, (Buffer *)NULLP);
#else
    ItLiSctAssocReq(&endp[endpIdx].pst, assocReq[idx].spId,
      assocReq[idx].spEndId, assocReq[idx].suAssocId, &assocReq[idx].dstNetAddr,
      assocReq[idx].dstPort, assocReq[idx].outStrms, &assocReq[idx].dstNAddrLst,
      &assocReq[idx].srcNAddrLst, (Buffer *)NULLP);
#endif /* SCT3 */

     /* Increment the number of Established Association */

   }
   osFclose(cfin);   /* Close file */
   RETVALUE(ROK);
}


  /************ DataRequest for SCTP ************/

#ifdef ANSI
PUBLIC S16 sbIPDataReq
(
U8 *strng,
U16 length,
U8 assocIdx
)
#else
PUBLIC S16 sbIPDataReq(strng,length,assocIdx)
U8 *strng;
U16 length;
U8 assocIdx;
#endif
{
   S16  ret;
   OsFile *cfin;

   if(!(assocReq[assocIdx].occupied))
   {
     osPrintf("%s(%d): Data request failed, association not done\n", __FILE__, __LINE__);
     RETVALUE(RFAILED);
   }

   if ((cfin = (OsFile*)osFopen("sb.datacfg", "r")) == (S32)NULLP)
   {
     osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "sb.datacfg");
     RETVALUE(RFAILED);
   }

   if ((sbICParsDataReq (cfin)) == RFAILED)
   {
      osPrintf("%s(%d): Failed parsing file sb.datacfg\n", __FILE__, __LINE__);
      osExit(-1);
   }
   else
   {
     if(!(assocReq[assocIdx].assocDone))
     {
      osPrintf("%s(%d): Assoc Not Done, DataReq Fail\n", __FILE__, __LINE__);
      osExit(-1);
     }

    ret = SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &dataReq.mBuf);
    if(ret != ROK)
    {
      osPrintf("\n%s(%d): Message Buffer Allocation Fails\n", __FILE__, __LINE__);
      osExit(-1);
    }
    (Void) SAddPstMsgMult(strng,(MsgLen)length,dataReq.mBuf);

    /* this is a normal data so add NORMAL_DATA as a first byte of data */
    (Void) SAddPreMsg(NORMAL_DATA,dataReq.mBuf);

     dataReq.spAssocId = assocReq[assocIdx].spAssocId;

     ItLiSctDatReq(&endp[assocReq[assocIdx].endpIdx].pst, dataReq.spId,
        dataReq.spAssocId, &dataReq.dstNAddr, dataReq.strmId,
                     dataReq.unorderFlg, dataReq.nobundleFlg,
                     dataReq.lifeTime, dataReq.protId,
                     dataReq.mBuf);

   }
   osFclose(cfin);   /* Close file */
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 sbIPBulkDataReq
(
U16 length,
U8 assocIdx,
U8 type
)
#else
PUBLIC S16 sbIPBulkDataReq(length,assocIdx,type)
U16 length;
U8 assocIdx;
U8 type;
#endif
{
   S16  ret;
   S8  *dataRet;
   U8  line[10000];
   OsFile *cfin, *cfileData;


  if(!(assocReq[assocIdx].occupied))
   {
     osPrintf("%s(%d): Bulkdata request failed, association not done\n", __FILE__, __LINE__);
     RETVALUE(RFAILED);
   }

   if ((cfin = (OsFile*)osFopen("sb.datacfg", "r")) == (S32)NULLP)
   {
     osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "sb.datacfg");
     RETVALUE(RFAILED);
   }

   if ((sbICParsDataReq (cfin)) == RFAILED)
   {
      osPrintf("%s(%d): Failed parsing file sb.datacfg\n", __FILE__, __LINE__);
      osExit(-1);
   }
   else
   {
     if(!(assocReq[assocIdx].assocDone))
     {
      osPrintf("%s(%d): Assoc Not Done, BulkDataReq Fail\n", __FILE__, __LINE__);
      osExit(-1);
     }

     if ((cfileData = (OsFile*)osFopen("data.file", "r")) == (S32)NULLP)
     {
       osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "data.file");
       osFclose(cfin);   /* Close file */
       osExit(-1);
     }
      dataRet = osFgets((S8*)line,length, cfileData);
      if (dataRet == (S8*)-1 || dataRet == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
           osPrintf("%s(%d): Error reading file data.file, line %d\n", lineNo);
         osFclose(cfileData);   /* Close file */
         osFclose(cfin);   /* Close file */
         osExit(-1);
      }

    ret = SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &dataReq.mBuf);
    if(ret != ROK)
    {
      osPrintf("\n%s(%d): Message Buffer Allocation Fails \n", __FILE__, __LINE__);
      osExit(-1);
    }
    (Void) SAddPstMsgMult(line,(MsgLen)length,dataReq.mBuf);

    (Void) SAddPreMsg(type,dataReq.mBuf);

    dataReq.spAssocId = assocReq[assocIdx].spAssocId;

    ItLiSctDatReq(&endp[assocReq[assocIdx].endpIdx].pst, dataReq.spId,
        dataReq.spAssocId, &dataReq.dstNAddr, dataReq.strmId,
                     dataReq.unorderFlg, dataReq.nobundleFlg,
                     dataReq.lifeTime, dataReq.protId,
                     dataReq.mBuf);

   }
   osFclose(cfin);   /* Close file */
   osFclose(cfileData);   /* Close file */
   RETVALUE(ROK);
}




#ifdef ANSI
PUBLIC S16 sbIPSendFile
(
Txt *filename,
U8 assocIdx
)
#else
PUBLIC S16 sbIPSendFile(filename,assocIdx)
Txt *filename;
U8 assocIdx;
#endif
{
   S16  ret;
   U8  readBuf[10000];
   U16 length;
   OsFile *cfin, *readfp;


  if(!(assocReq[assocIdx].occupied))
   {
     osPrintf("%s(%d): Sendfile request failed, association not done\n", __FILE__, __LINE__);
     RETVALUE(RFAILED);
   }

   if ((cfin = (OsFile*)osFopen("sb.datacfg", "r")) == (S32)NULLP)
   {
       osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "sb.datacfg");
       RETVALUE(RFAILED);
   }

   if ((sbICParsDataReq (cfin)) == RFAILED)
   {
       osPrintf("%s(%d): Failed parsing file sb.datacfg\n", __FILE__, __LINE__);
       osExit(-1);
   }
   else
   {
     if(!(assocReq[assocIdx].assocDone))
     {
      osPrintf("%s(%d): Assoc Not Done, DataReq For SendFile Fail\n", __FILE__, __LINE__);
      osExit(-1);
     }

    ret = SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &dataReq.mBuf);
    if(ret != ROK)
    {
      osPrintf("\n%s(%d): Message Buffer Allocation Fails \n", __FILE__, __LINE__);
      osExit(-1);
    }

    /* send filename first */
    length = cmStrlen((U8*)filename);
    (Void) SAddPstMsg(FILE_START, dataReq.mBuf);
    (Void) SAddPstMsgMult((U8*)filename,(MsgLen)length+1,dataReq.mBuf);
    dataReq.spAssocId = assocReq[assocIdx].spAssocId;
    dataReq.strmId = 9;

    ItLiSctDatReq(&endp[assocReq[assocIdx].endpIdx].pst, dataReq.spId,
          dataReq.spAssocId, &dataReq.dstNAddr, dataReq.strmId,
          dataReq.unorderFlg, dataReq.nobundleFlg,
          dataReq.lifeTime, dataReq.protId, dataReq.mBuf);

    /* read file and send file data */
    if ((readfp = (OsFile*)osFopen(filename, "r")) == (S32)NULLP)
    {
           osPrintf("%s(%d): File open error,  File:=%s\n",filename);
        RETVALUE(RFAILED);
    }

    while(1)
    {
          cmMemset((U8 *)readBuf, 0, 1249);
               length = osFread(readBuf, 1, 1249, readfp);

           ret = SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &dataReq.mBuf);
        if(ret != ROK)
        {
                osPrintf("\n%s(%d): Message Buffer Allocation Fails \n", __FILE__, __LINE__);
                osExit(-1);
        }
        (Void) SAddPstMsg(FILE_DATA, dataReq.mBuf);
        (Void) SAddPstMsgMult(readBuf,(MsgLen)length,dataReq.mBuf);
        ItLiSctDatReq(&endp[assocReq[assocIdx].endpIdx].pst, dataReq.spId,
                dataReq.spAssocId, &dataReq.dstNAddr, dataReq.strmId,
                dataReq.unorderFlg, dataReq.nobundleFlg,
                dataReq.lifeTime, dataReq.protId, dataReq.mBuf);

        printf("before length<1249; length is %d\n",length);
        if(length < 1249)
           break;
    }
    osFclose(readfp); /* Close data file */
  }
  osFclose(cfin);   /* Close file */

  RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 sbIPPerfDataReq
(
U8 assocIdx
)
#else
PUBLIC S16 sbIPPerfDataReq(assocIdx)
U8 assocIdx;
#endif
{
   S16  ret;
   PRIVATE U16  length=0;
   U16 i=0;
   S8  *dataRet;
   PRIVATE U8  line[3000];
   OsFile *cfin, *cfileData, *cfinLoopFile;
   PRIVATE U8  Once=0;
   Buffer   *mBuf;
   PRIVATE Bool infinite=FALSE;
   U16    cnt=0;


  if(! Once  )
  {
    if(!(assocReq[assocIdx].occupied))
    {
     osPrintf("%s(%d): Performance data request failed, association not done\n", __FILE__, __LINE__);
     RETVALUE(RFAILED);
    }
  
    if ((cfinLoopFile = (OsFile*)osFopen("sb.loopcfg", "r")) == (S32)NULLP)
    {
      osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "sb.loopcfg");
      RETVALUE(RFAILED);
    }

    if ((sbICParsLoopReq (cfinLoopFile)) == RFAILED)
    {
       osPrintf("%s(%d): Failed parsing file sb.loopcfg\n", __FILE__, __LINE__);
       osExit(-1);
    }

    if ((cfin = (OsFile*)osFopen("sb.datacfg", "r")) == (S32)NULLP)
    {
      osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "sb.datacfg");
      osFclose(cfinLoopFile);   /* Close file */
      RETVALUE(RFAILED);
    }

    if ((sbICParsDataReq (cfin)) == RFAILED)
    {
       osPrintf("%s(%d): Failed parsing file sb.datacfg\n", __FILE__, __LINE__);
       osFclose(cfinLoopFile);   /* Close file */
       osExit(-1);
    }
    else
    {
      if(!(assocReq[assocIdx].assocDone))
      {
       osPrintf("%s(%d): Assoc Not Done, BulkDataReq Fail\n", __FILE__, __LINE__);
       osFclose(cfin);           /* Close file */
       osFclose(cfinLoopFile);   /* Close file */
       osExit(-1);
      }

     if ((cfileData = (OsFile*)osFopen("data.file", "r")) == (S32)NULLP)
     {
       osPrintf("%s(%d): File open error, File=:%s\n", __FILE__, __LINE__, "data.file");
       osFclose(cfin);   /* Close file */
       osFclose(cfinLoopFile);   /* Close file */
       osExit(-1);
     }
      length = loopInfo.size;
      dataRet = osFgets((S8*)line,length, cfileData);
      if (dataRet == (S8*)-1 || dataRet == NULLD) /* eof or NULL */
      {
         if (optDebug >= 1)
           osPrintf("%s(%d): Error reading file data.file, line %d\n", lineNo);
         osFclose(cfileData);   /* Close file */
         osFclose(cfin);   /* Close file */
         osFclose(cfinLoopFile);   /* Close file */
         osExit(-1);
      }

    ret = SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &dataReq.mBuf);
    if(ret != ROK)
    {
      osPrintf("\n%s(%d): Message Buffer Allocation Fails \n", __FILE__, __LINE__);
      osExit(-1);
    }
    (Void) SAddPstMsgMult(line,(MsgLen)length,dataReq.mBuf);

    (Void) SAddPreMsg(PKTCNT_DATA,dataReq.mBuf);

   }
   osFclose(cfin);   /* Close file */
   osFclose(cfileData);   /* Close file */
   osFclose(cfinLoopFile);   /* Close file */

   if(loopInfo.times == 0)
       infinite=TRUE;
   Once = 1; 
  } 


  for(i=0; (((loopInfo.times >= 0) || (infinite == TRUE)) &&
             (i < loopInfo.delay) && ( FLCpause == FALSE ) ) ;i++)
  { 
    ret = SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **)&mBuf);
    if( ret != ROK)
    {
     osPrintf("\n%s(%d): Message Allocation  Fails : RetValue %d \n", __FILE__, __LINE__, ret);
     osExit(-1);
    }
    
    (Void) SAddPstMsgMult(line,(MsgLen)length,mBuf);

    (Void) SAddPreMsg(PKTCNT_DATA,mBuf);

    dataReq.spAssocId = assocReq[assocIdx].spAssocId;

    ItLiSctDatReq(&endp[assocReq[assocIdx].endpIdx].pst, dataReq.spId,
      dataReq.spAssocId, &dataReq.dstNAddr, dataReq.strmId,
      dataReq.unorderFlg, dataReq.nobundleFlg,
      dataReq.lifeTime, dataReq.protId, mBuf);
  }

  if ((loopInfo.times >= 0 ) && ( FLCpause == FALSE ) && (infinite != TRUE))
  {
     loopInfo.times -= loopInfo.delay;
  }

   RETVALUE(ROK);
}  /* sbIPPerfDatReq */



/********************************************************************30**

         End of file:     sb_iprim.c@@/main/2 - Thu Jul 26 07:54:26 2007

*********************************************************************31*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sb    1. File Added for inter-op SCTP Testing 
 sb060.102   ---      pr    1. TOS changes.  
/main/2      ---    rsr/ag  1. Updated for Release of 1.3
*********************************************************************91*/

