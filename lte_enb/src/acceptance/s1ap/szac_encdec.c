
/**********************************************************************
     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the C-based acc test cases source code
              for encoder/decoder library

     File:    szac_encdec.c

     Sid:      szac_encdec.c@@/main/Tenb_Intg_Branch_CC/1 - Mon Jan  7 19:23:20 2013

     Prg:     vvashishth 
*********************************************************************21*/
 
/* Header include files (.h) */ 
#include "envopt.h"
#include "envdep.h"
#include "envind.h"
#include "ssi.h"
#include "gen.h"
/* sz006.301: Removed un-necessary include files  */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_tkns.h"
#include "cm_mblk.h"
#include "cm_tpt.h"
#include "szt.h"
#include "szt_asn.h"

#include <stdlib.h>
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

/* Header include files (.x) */ 
#include "gen.x"
#include "ssi.x"
#include "cm_lib.x"
#include "cm_llist.x"      /* Common link list library        */
#include "cm_tpt.x"
#include"cm_tkns.x"       /* common tokens */
#include"cm_mblk.x"
#include"szt_asn.x"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"
#include "szac_szt.x"
#include "sz_encdec.x"
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif

#ifndef S1AP_REL_890       
/* sz008.301 : Increasing test case no 89,
 * to support Source RNC to target RNC TC */
#define SZ_ACC_MAX_TST 89   /* S1AP Specification 9.2.2 */
#else                      
#define SZ_ACC_MAX_TST 82   /* S1AP Specification 8.9.0 */
#endif

#define SZ_ACC_MAX_CMD_LEN 10

#define SZ_MEM_SDU_SIZE 2048

Txt   prntBuf[512];  /* Print buffer for debug print */

#define SZ_PRINT(_func, _stng, _val)     \
{                                        \
   sprintf(prntBuf, "\n%s:", _stng);     \
   SPrint(prntBuf);                      \
   _func(_val);                          \
}

#ifdef DEBUGP
#define SZAC_DBG(_stng)                  \
{                                        \
   sprintf _stng;                        \
   SPrint(prntBuf);                      \
}

#else

#define SZAC_DBG(_stng) 

#endif /* DEBUGP */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef S16 (*SzAccTbl) ARGS((Void));

PRIVATE SzAccTbl szAccTstTbl[SZ_ACC_MAX_TST];
PRIVATE U8 szAccExecLst[SZ_ACC_MAX_TST];


PRIVATE Void szAccInitTabl ARGS((Void));
PRIVATE Void szAccParseCmdLine ARGS((Void));
PRIVATE Void szAccExec ARGS((Void));
PRIVATE S16 szAccParse ARGS((S16 len,S8 *str));
PRIVATE S16 szAcPrntSts ARGS((SztEncDecMsgSts *sts));
PRIVATE Void SPrintU32 ARGS((U32 val));

PRIVATE S16 szAccTst0 ARGS((Void));
PRIVATE S16 szAccTst1 ARGS((Void));
PRIVATE S16 szAccTst2 ARGS((Void));
PRIVATE S16 szAccTst3 ARGS((Void));
PRIVATE S16 szAccTst4 ARGS((Void));
PRIVATE S16 szAccTst5 ARGS((Void));
PRIVATE S16 szAccTst6 ARGS((Void));
PRIVATE S16 szAccTst7 ARGS((Void));
PRIVATE S16 szAccTst8 ARGS((Void));
PRIVATE S16 szAccTst9 ARGS((Void));
PRIVATE S16 szAccTst10 ARGS((Void));
PRIVATE S16 szAccTst11 ARGS((Void));
PRIVATE S16 szAccTst12 ARGS((Void));
PRIVATE S16 szAccTst13 ARGS((Void));
PRIVATE S16 szAccTst14 ARGS((Void));
PRIVATE S16 szAccTst15 ARGS((Void));
PRIVATE S16 szAccTst16 ARGS((Void));
PRIVATE S16 szAccTst17 ARGS((Void));
PRIVATE S16 szAccTst18 ARGS((Void));
PRIVATE S16 szAccTst19 ARGS((Void));
PRIVATE S16 szAccTst20 ARGS((Void));
PRIVATE S16 szAccTst21 ARGS((Void));
PRIVATE S16 szAccTst22 ARGS((Void));
PRIVATE S16 szAccTst23 ARGS((Void));
PRIVATE S16 szAccTst24 ARGS((Void));
PRIVATE S16 szAccTst25 ARGS((Void));
PRIVATE S16 szAccTst26 ARGS((Void));
PRIVATE S16 szAccTst27 ARGS((Void));
PRIVATE S16 szAccTst28 ARGS((Void));
PRIVATE S16 szAccTst29 ARGS((Void));
PRIVATE S16 szAccTst30 ARGS((Void));
PRIVATE S16 szAccTst31 ARGS((Void));
PRIVATE S16 szAccTst32 ARGS((Void));
PRIVATE S16 szAccTst33 ARGS((Void));
PRIVATE S16 szAccTst34 ARGS((Void));
PRIVATE S16 szAccTst35 ARGS((Void));
PRIVATE S16 szAccTst36 ARGS((Void));
PRIVATE S16 szAccTst37 ARGS((Void));
PRIVATE S16 szAccTst38 ARGS((Void));
PRIVATE S16 szAccTst39 ARGS((Void));
PRIVATE S16 szAccTst40 ARGS((Void));
PRIVATE S16 szAccTst41 ARGS((Void));
PRIVATE S16 szAccTst42 ARGS((Void));
PRIVATE S16 szAccTst43 ARGS((Void));
PRIVATE S16 szAccTst44 ARGS((Void));
PRIVATE S16 szAccTst45 ARGS((Void));
PRIVATE S16 szAccTst46 ARGS((Void));
PRIVATE S16 szAccTst47 ARGS((Void));
PRIVATE S16 szAccTst48 ARGS((Void));
PRIVATE S16 szAccTst49 ARGS((Void));
PRIVATE S16 szAccTst50 ARGS((Void));
PRIVATE S16 szAccTst51 ARGS((Void));
PRIVATE S16 szAccTst52 ARGS((Void));
PRIVATE S16 szAccTst53 ARGS((Void));
PRIVATE S16 szAccTst54 ARGS((Void));
PRIVATE S16 szAccTst55 ARGS((Void));
PRIVATE S16 szAccTst56 ARGS((Void));
PRIVATE S16 szAccTst57 ARGS((Void));
PRIVATE S16 szAccTst58 ARGS((Void));
PRIVATE S16 szAccTst59 ARGS((Void));
PRIVATE S16 szAccTst60 ARGS((Void));
PRIVATE S16 szAccTst61 ARGS((Void));
PRIVATE S16 szAccTst62 ARGS((Void));
PRIVATE S16 szAccTst63 ARGS((Void));
PRIVATE S16 szAccTst64 ARGS((Void));
PRIVATE S16 szAccTst65 ARGS((Void));
PRIVATE S16 szAccTst66 ARGS((Void));
/* Selective IE Encode/Decode Test cases */
PRIVATE S16 szAccTst67 ARGS((Void));
PRIVATE S16 szAccTst68 ARGS((Void));
PRIVATE S16 szAccTst69 ARGS((Void));
PRIVATE S16 szAccTst70 ARGS((Void));
PRIVATE S16 szAccTst71 ARGS((Void));
PRIVATE S16 szAccTst72 ARGS((Void));
PRIVATE S16 szAccTst73 ARGS((Void));
PRIVATE S16 szAccTst74 ARGS((Void));
PRIVATE S16 szAccTst75 ARGS((Void));
PRIVATE S16 szAccTst76 ARGS((Void));
PRIVATE S16 szAccTst77 ARGS((Void));
PRIVATE S16 szAccTst78 ARGS((Void));
PRIVATE S16 szAccTst79 ARGS((Void));
PRIVATE S16 szAccTst80 ARGS((Void));

#ifndef S1AP_REL8A0 
PRIVATE S16 szAccTst81 ARGS((Void));
PRIVATE S16 szAccTst82 ARGS((Void));
PRIVATE S16 szAccTst83 ARGS((Void));
PRIVATE S16 szAccTst84 ARGS((Void));
PRIVATE S16 szAccTst85 ARGS((Void));
PRIVATE S16 szAccTst86 ARGS((Void));
#endif
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
PRIVATE S16 szAccTst87 ARGS((Void));
#endif  /* SZTV1 */
/*sz008.301 : Support for Src RNC to target RNC */
#ifdef SZTV3
PRIVATE S16 szAccTst88 ARGS((Void));
#endif  /* SZTV1 */

EXTERN S16 szGetIE  ARGS((SztS1AP_PDU *pdu, U32 id, TknU8 **ie));
EXTERN S16 SzUiSztEncIE ARGS((SztEncDecIE *encIE, Buffer *mBuf, U16 szIeId, SztReqStatus *status));
EXTERN S16 SzUiSztDecIE ARGS((SztEncDecIE *encIE, Buffer *mBuf, U16 szIeId, SztReqStatus *status));
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
EXTERN S16 SzUiSztEncTcIeReq ARGS((SzMsgParamsIe *encIE, Buffer *mBuf, SztReqStatus *status));
EXTERN S16 SzUiSztDecTcIeReq ARGS((SzMsgParamsIe *encIE, Buffer *mBuf, SztReqStatus *status));
#endif   /* SZTV1 */
#ifdef __cplusplus
}
#endif /* __cplusplus */

/*
*
*       Fun:     tst
*
*       Desc:    This function initializes the test table, 
*                and parses the command line arguments
*              
*       Ret:     ROK    - success
*                Exits  - on failure
*              
*       Notes:   None
*
*       File:    szac_encdec.c
*
*/ 
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst()
#endif
{
   TRC2(tst)

   szAccInitTabl();
   szAccParseCmdLine();

   szAccExec();

   exit(0);
   RETVALUE(ROK);
}


/*
 *
 *       Fun:     szAccInitTabl
 *
 *       Desc:    This function initializes the acc test table, 
 *                to map each test case with specific function
 * 
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */ 

#ifdef ANSI
PUBLIC Void szAccInitTabl
(
Void
)
#else
PUBLIC Void szAccInitTabl(Void)
#endif
{
   szAccTstTbl[0] = szAccTst0;
   szAccTstTbl[1] = szAccTst1;
   szAccTstTbl[2] = szAccTst2;
   szAccTstTbl[3] = szAccTst3;
   szAccTstTbl[4] = szAccTst4;
   szAccTstTbl[5] = szAccTst5;
   szAccTstTbl[6] = szAccTst6;
   szAccTstTbl[7] = szAccTst7;
   szAccTstTbl[8] = szAccTst8;
   szAccTstTbl[9] = szAccTst9;
   szAccTstTbl[10] = szAccTst10;
   szAccTstTbl[11] = szAccTst11;
   szAccTstTbl[12] = szAccTst12;
   szAccTstTbl[13] = szAccTst13;
   szAccTstTbl[14] = szAccTst14;
   szAccTstTbl[15] = szAccTst15;
   szAccTstTbl[16] = szAccTst16;
   szAccTstTbl[17] = szAccTst17;
   szAccTstTbl[18] = szAccTst18;
   szAccTstTbl[19] = szAccTst19;
   szAccTstTbl[20] = szAccTst20;
   szAccTstTbl[21] = szAccTst21;
   szAccTstTbl[22] = szAccTst22;
   szAccTstTbl[23] = szAccTst23;
   szAccTstTbl[24] = szAccTst24;
   szAccTstTbl[25] = szAccTst25;
   szAccTstTbl[26] = szAccTst26;
   szAccTstTbl[27] = szAccTst27;
   szAccTstTbl[28] = szAccTst28;
   szAccTstTbl[29] = szAccTst29;
   szAccTstTbl[30] = szAccTst30;
   szAccTstTbl[31] = szAccTst31;
   szAccTstTbl[32] = szAccTst32;
   szAccTstTbl[33] = szAccTst33;
   szAccTstTbl[34] = szAccTst34;
   szAccTstTbl[35] = szAccTst35;
   szAccTstTbl[36] = szAccTst36;
   szAccTstTbl[37] = szAccTst37;
   szAccTstTbl[38] = szAccTst38;
   szAccTstTbl[39] = szAccTst39;
   szAccTstTbl[40] = szAccTst40;
   szAccTstTbl[41] = szAccTst41;
   szAccTstTbl[42] = szAccTst42;
   szAccTstTbl[43] = szAccTst43;
   szAccTstTbl[44] = szAccTst44;
   szAccTstTbl[45] = szAccTst45;
   szAccTstTbl[46] = szAccTst46;
   szAccTstTbl[47] = szAccTst47;
   szAccTstTbl[48] = szAccTst48;
   szAccTstTbl[49] = szAccTst49;
   szAccTstTbl[50] = szAccTst50;
   szAccTstTbl[51] = szAccTst51;
   szAccTstTbl[52] = szAccTst52;
   szAccTstTbl[53] = szAccTst53;
   szAccTstTbl[54] = szAccTst54;
   szAccTstTbl[55] = szAccTst55;
   szAccTstTbl[56] = szAccTst56;
   szAccTstTbl[57] = szAccTst57;
   szAccTstTbl[58] = szAccTst58;
   szAccTstTbl[59] = szAccTst59;
   szAccTstTbl[60] = szAccTst60;
   szAccTstTbl[61] = szAccTst61;
   szAccTstTbl[62] = szAccTst62;
   szAccTstTbl[63] = szAccTst63;
   szAccTstTbl[64] = szAccTst64;
   szAccTstTbl[65] = szAccTst65;
   szAccTstTbl[66] = szAccTst66;
   /* Selective IE encode/decode test cases */
   szAccTstTbl[67] = szAccTst67;
   szAccTstTbl[68] = szAccTst68;
   szAccTstTbl[69] = szAccTst69;
   szAccTstTbl[70] = szAccTst70;
   szAccTstTbl[71] = szAccTst71;
   szAccTstTbl[72] = szAccTst72;
   szAccTstTbl[73] = szAccTst73;
   szAccTstTbl[74] = szAccTst74;
   szAccTstTbl[75] = szAccTst75;
   szAccTstTbl[76] = szAccTst76;
   szAccTstTbl[77] = szAccTst77;
   szAccTstTbl[78] = szAccTst78;
   szAccTstTbl[79] = szAccTst79;
   szAccTstTbl[80] = szAccTst80;
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
   szAccTstTbl[81] = szAccTst87;
#endif /* SZTV1 */
#ifndef S1AP_REL8A0 
   szAccTstTbl[82] = szAccTst81;
   szAccTstTbl[83] = szAccTst82;
   szAccTstTbl[84] = szAccTst83;
   szAccTstTbl[85] = szAccTst84;
   szAccTstTbl[86] = szAccTst85;
   szAccTstTbl[87] = szAccTst86;
#endif

   /*sz008.301: Support fo src RNC to Tget RNC transparent container */
#ifdef SZTV3
   szAccTstTbl[88] = szAccTst88;
#endif
}

/*
 *
 *       Fun:     szAccParseCmdLine
 *
 *       Desc:    This function parses the command line arguments specified by user
 *                to invoke the required test cases
 *      
 * 
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */ 

#ifdef ANSI
PUBLIC Void szAccParseCmdLine
(
Void
)
#else
PUBLIC Void szAccParseCmdLine(Void)
#endif
{
    S16 ret;
    U8  val;
    S8  line[SZ_ACC_MAX_CMD_LEN];
    U16 len;
    U16 i;

    TRC2(szAccParseCmdLine)

    while ((ret = SGetOpt(msArgc, msArgv, "znasculpdkgxvt:h")) != EOF)
    {
       switch(ret)
       {
          case 'a':
             for(i = 0; i < SZ_ACC_MAX_TST; i++)
             {
               szAccExecLst[i] = TRUE; 
             }
             break;

          case 't':
             len = cmStrlen((CONSTANT U8 *)msOptArg);
             if(len > SZ_ACC_MAX_CMD_LEN)
             {
                RETVOID;
             }

             cmMemcpy((U8 *)line, (U8 *)msOptArg, len);
             val = szAccParse(len,line);
             break;

          default:
             break;
       }
    }
   RETVOID;
}


/*
 *
 *       Fun:     szAccParse
 *
 *       Desc:    This function prepares the list of test cases to be executed.
 * 
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */ 

#ifdef ANSI
PRIVATE S16 szAccParse
(
S16   len,
S8    *str
)
#else
PRIVATE S16 szAccParse (len, str)
S16   len;
S8    *str;
#endif
{
   U16 idx1, idx2;
   S8 tmp[SZ_ACC_MAX_CMD_LEN];

   for(idx1 = 0, idx2 = 0; idx1 <= (len); idx1++,idx2++)
   {
      if((str[idx1] == ' ') || (str[idx1] == '\0'))
      {
         if(atoi(tmp) < SZ_ACC_MAX_TST)
         {
            szAccExecLst[atoi(tmp)] = TRUE;
            idx2 = 0;
         }
      }
      else
      {
      /*   if(atoi(&str[i]) <= SZ_ACC_MAX_TST)
         {
            szAccExecLst[atoi(&str[i])] = TRUE;
         }*/
         tmp[idx2] = str[idx1];
      }
   }

   RETVALUE(ROK);
}

/*
 *
 *       Fun:    szAccExec
 *
 *       Desc:   This function executes the test case/cases and prints the result of test case/cases.
 * 
 *       
 *       Notes:  None
 * 
 *       File:   szac_encdec
 * 
 */ 

#ifdef ANSI
PUBLIC Void szAccExec
(
 Void
)
#else
PUBLIC Void szAccExec(Void)
#endif
{
   U16 i;
   S16 ret;
   U8  result[SZ_ACC_MAX_TST];

   cmMemset(result, 0, sizeof(result));

   for(i = 0; i < SZ_ACC_MAX_TST; i++)
   {
      if( (szAccExecLst[i] == TRUE) && (szAccTstTbl[i]))
      {
         ret = (*szAccTstTbl[i])();
         if(ret == ROK)
         {
            SZAC_DBG((prntBuf,"\n Test Case Passed ******** Test Id = %d\n\n",i));
         }
         else
         {
            result[i] = TRUE;
            SZAC_DBG((prntBuf,"\n Test Case Failed ******** Test Id = %d\n\n",i));
         }
      }
   }

   ret = FALSE;
   SZAC_DBG((prntBuf,"**************** Test Result ******************\n"));
   /* Pring the result */
   for(i = 0; i < SZ_ACC_MAX_TST; i++)
   {
      if(result[i])
      {
         ret = TRUE;
         SZAC_DBG((prntBuf,"\t\t Test Case %d Failed \n",(i+1)));
      }
   }

   if(!(ret))
   {
      SZAC_DBG((prntBuf," \t    All Test Cases Passed \n"));
   }
   SZAC_DBG((prntBuf,"**********************************************\n"));
}

/*
*
*       Fun:     SPrintU32
*
*       Desc:    Function to fill print buffer with Unsigned 32 bit value
* 
* 
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/

#ifdef ANSI
PRIVATE Void SPrintU32
(
U32 val
)
#else
PRIVATE Void SPrintU32(val)
U32 val;
#endif
{

   Txt buf[100];

#ifdef ALIGN_64BIT
   sprintf(buf, "%d\n", val);
#else
   sprintf(buf, "%ld\n", val);
#endif /* ALIGN_64BIT */
   SPrint(buf);
}

/*
 *
 *       Fun:     szAcPrntSts
 *
 *       Desc:    Function to print encode/decode statistics
 * 
 *       Ret:     ROK
 * 
 *       Notes:   None
 * 
 *       File:    sz_encdec.c
 * 
 */

#ifdef ANSI
PRIVATE S16 szAcPrntSts
(
SztEncDecMsgSts *sts
)
#else
PRIVATE S16 szAcPrntSts(sts)
SztEncDecMsgSts *sts;
#endif
{
   TRC3(szAcPrntSts)

   SZ_PRINT(SPrintU32, " \n\n---Stats Structure printing Begin---\n E-RAB setup request  ", sts->eRABSetupReq);
   SZ_PRINT(SPrintU32, " E-RAB setup response  ", sts->eRABSetupResp);
   SZ_PRINT(SPrintU32, " E-RAB modify request  ", sts->eRABModReq);
   SZ_PRINT(SPrintU32, " E-RAB modify response  ", sts->eRABModResp);
   SZ_PRINT(SPrintU32, " E-RAB release command  ", sts->eRABRelCmd);
   SZ_PRINT(SPrintU32, " E-RAB release complete  ", sts->eRABRelComp);
   SZ_PRINT(SPrintU32, " E-RAB release request  ", sts->eRABRelReq);
   SZ_PRINT(SPrintU32, " Initial Context setup request  ", sts->initCxtSetup);
   SZ_PRINT(SPrintU32, " Initial Context setup response  ", sts->initCxtSetupResp);
   SZ_PRINT(SPrintU32, " Initial Context setup failure  ", sts->initCxtSetupFail);
   SZ_PRINT(SPrintU32, " UE Context release request  ", sts->ueCxtRelReq);
   SZ_PRINT(SPrintU32, " UE Context release command  ", sts->ueCxtRelCmd);
   SZ_PRINT(SPrintU32, " UE Context release complete  ", sts->ueCxtRelComp);
   SZ_PRINT(SPrintU32, " UE Context Modification request  ", sts->ueCxtModReq);
   SZ_PRINT(SPrintU32, " UE Context Modification response  ", sts->ueCxtModResp);
   SZ_PRINT(SPrintU32,   " UE Context Modification failure  ", sts->ueCxtModFail);
   SZ_PRINT(SPrintU32, " Initial UE Message  ", sts->initUEMsg);
   SZ_PRINT(SPrintU32, " Downlink NAS transport  ", sts->dwnNASTpt);
   SZ_PRINT(SPrintU32, " Uplink NAS transport  ", sts->upNASTpt);
   SZ_PRINT(SPrintU32, " NAS non delivery indication  ", sts->nonDelIndNAS);
   SZ_PRINT(SPrintU32, " Error Indication  ", sts->errInd);
   SZ_PRINT(SPrintU32, " No Data  ", sts->noData);
   SZ_PRINT(SPrintU32, " Reset  ", sts->reset);
   SZ_PRINT(SPrintU32, " Reset Acknowledge  ", sts->resetAck);
   SZ_PRINT(SPrintU32, " S1 Setup request  ", sts->setupReq);
   SZ_PRINT(SPrintU32, " S1 Setup response  ", sts->setupResp);
   SZ_PRINT(SPrintU32, " S1 Setup Failure  ", sts->setupFail);
   SZ_PRINT(SPrintU32, " Paging  ", sts->paging);
   SZ_PRINT(SPrintU32, " Handover required  ", sts->handReqd);
   SZ_PRINT(SPrintU32, " Handover command  ", sts->handCmd);
   SZ_PRINT(SPrintU32, " Handover preparation failure  ", sts->handPrepFail);
   SZ_PRINT(SPrintU32, " Handover Request  ", sts->handReq);
   SZ_PRINT(SPrintU32, " Handover Request Acknowledge  ", sts->handReqAck);
   SZ_PRINT(SPrintU32, " Handover Failure  ", sts->handFail);
   SZ_PRINT(SPrintU32, " Handover notify  ", sts->handNtfy);
   SZ_PRINT(SPrintU32, " Path Switch request  ", sts->pathSwchReq);
   SZ_PRINT(SPrintU32, " Path Switch request acknowledge  ", sts->pathSwchReqAck);
   SZ_PRINT(SPrintU32, " Path Switch request failure  ", sts->pathSwchReqFail);
   SZ_PRINT(SPrintU32, " Handover cancel  ", sts->handCan);
   SZ_PRINT(SPrintU32, " Handover cancel acknowledge  ", sts->handCanAck);
   SZ_PRINT(SPrintU32, " eNB status transfer  ", sts->eNBStaTrans);
   SZ_PRINT(SPrintU32, " MME status transfer  ", sts->mmeStaTrans);
   SZ_PRINT(SPrintU32, " De activate Trace  ", sts->deactTrace);
   SZ_PRINT(SPrintU32, " Trace Start ", sts->traceStart);
   SZ_PRINT(SPrintU32, " Trace Failure Indication ", sts->traceFailInd);
   SZ_PRINT(SPrintU32, " Location Report Control  ", sts->locReportCntrl);
   SZ_PRINT(SPrintU32, " Location Report Failure Indication  ", sts->locReportFailInd);
   SZ_PRINT(SPrintU32, " Location Report  ", sts->locReport);
   SZ_PRINT(SPrintU32, " ENB Configuration Update  ", sts->enbCfgUpd);
   SZ_PRINT(SPrintU32, " ENB Configuration Update Ack  ", sts->enbCfgUpdAck);
   SZ_PRINT(SPrintU32, " ENB Configuration Update Fail  ", sts->enbCfgUpdFail);
   SZ_PRINT(SPrintU32, " MME Configuration Update  ", sts->mmeCfgUpd);
   SZ_PRINT(SPrintU32, " MME Configuration Update Ack  ", sts->mmeCfgUpdAck);
   SZ_PRINT(SPrintU32, " MME Configuration Update Fail  ", sts->mmeCfgUpdFail);
   SZ_PRINT(SPrintU32, " Uplink S1 CDMA2000 Tunneling  ", sts->upS1CDMA2000Tunn);
   SZ_PRINT(SPrintU32, " Downlink S1 CDMA2000 Tunneling  ", sts->dnS1CDMA2000Tunn);
   SZ_PRINT(SPrintU32, " UE Capability Info Indication  ", sts->ueCapInfoInd);
   SZ_PRINT(SPrintU32, " Overload Start  ", sts->overloadStart);
   SZ_PRINT(SPrintU32, " Overload Stop  ", sts->overloadStop);
   SZ_PRINT(SPrintU32, " Write Replace Warning Request  ", sts->writeRepWarnReq);
   SZ_PRINT(SPrintU32, " Write Replace Warning Responst  ", sts->writeRepWarnRsp);
   SZ_PRINT(SPrintU32, " eNB direct Information Transfer  ", sts->enbDirInfoTrans);
   SZ_PRINT(SPrintU32, " mme Direct Information Transfer  ", sts->mmeDirInfoTrans);
   SZ_PRINT(SPrintU32, " Private message  ", sts->pvtMsg);
   SZ_PRINT(SPrintU32, " ENB Config Transfer  ", sts->enbCfgTrans);
   SZ_PRINT(SPrintU32, " MME Config Transfer  ", sts->mmeCfgTrans);
   SZ_PRINT(SPrintU32, " Cell Traffic Trace  ", sts->cellTraffTrc);
#ifndef S1AP_REL8A0 
   SZ_PRINT(SPrintU32, " Kill Request  ", sts->killReq);
   SZ_PRINT(SPrintU32, " Kill Response  ", sts->killResp);
   SZ_PRINT(SPrintU32, " Downlink UE Associated LPPa Transport  ", sts->dwlnkUeAssocLPPaTprt);
   SZ_PRINT(SPrintU32, " Uplink UE Associated LPPa Transport  ", sts->uplnkUeAssocLPPaTprt);
   SZ_PRINT(SPrintU32, " Downlink Non-UE Associated LPPa Transport  ", sts->dwlnkNonUeAssocLPPaTprt);
   SZ_PRINT(SPrintU32, " Uplink Non-UE Associated LPPa Transport  ", sts->uplnkNonUeAssocLPPaTprt);
#endif
   SZ_PRINT(SPrintU32, " Total Number of decode errors  ", sts->numDecErr);

   RETVALUE(ROK);
}

/*
 *
 *       Fun:     szAccTst0
 *
 *       Desc:    Test case for E-Rab setup request
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */ 

#ifdef ANSI
PUBLIC S16 szAccTst0
(
Void
)
#else
PUBLIC S16 szAccTst0(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 1 -- E-RAB Setup Request \n"));

   szAcUtlSztFillE_RABSetupRqst(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst1
 *
 *       Desc:    Test case for E-Rab setup response
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */  

#ifdef ANSI
PUBLIC S16 szAccTst1
(
Void
)
#else
PUBLIC S16 szAccTst1(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 2 -- E-RAB Setup Response \n"));

   szAcUtlSztFillE_RABSetupResp(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst2
 *
 *       Desc:    Test case for E-Rab modification request
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */   

#ifdef ANSI
PUBLIC S16 szAccTst2
(
Void
)
#else
PUBLIC S16 szAccTst2(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 3 -- E-RAB modification Request \n"));

   szAcUtlSztFillE_RABMdfyRqst(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst3
 *
 *       Desc:    Test case for E-Rab modification response
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */    

#ifdef ANSI
PUBLIC S16 szAccTst3
(
Void
)
#else
PUBLIC S16 szAccTst3(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 4 -- E-RAB modification Response \n"));

   szAcUtlSztFillE_RABMdfyResp(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst4
 *
 *       Desc:    Test case for E-Rab release command
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */     

#ifdef ANSI
PUBLIC S16 szAccTst4
(
Void
)
#else
PUBLIC S16 szAccTst4(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 5 -- E-Rab Release Command \n"));

   szAcUtlSztFillE_RABRlsCmmd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst5
 *
 *       Desc:    Test case for E-Rab release indication
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */      

#ifdef ANSI
PUBLIC S16 szAccTst5
(
Void
)
#else
PUBLIC S16 szAccTst5(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 6 -- E-Rab Release Indication \n"));

   szAcUtlSztFillE_RABRlsInd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst6
 *
 *       Desc:    Test case for E-Rab release response
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */       

#ifdef ANSI
PUBLIC S16 szAccTst6
(
Void
)
#else
PUBLIC S16 szAccTst6(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 7 -- E-Rab Release Response \n"));

   szAcUtlSztFillE_RABRlsResp(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst7
 *
 *       Desc:    Test case for Initial context setup request
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */        

#ifdef ANSI
PUBLIC S16 szAccTst7
(
Void
)
#else
PUBLIC S16 szAccTst7(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 8 -- Initial Context Setup Request \n"));

   szAcUtlSztFillInitCxtSetupReq(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst8
 *
 *       Desc:    Test case for Initial context setup response
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */         

#ifdef ANSI
PUBLIC S16 szAccTst8
(
Void
)
#else
PUBLIC S16 szAccTst8(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 9 -- Initial Context Setup Rsp \n"));

   szAcUtlSztFillInitCxtSetupRsp(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst9
 *
 *       Desc:    Test case for Initial context setup failure
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */          

#ifdef ANSI
PUBLIC S16 szAccTst9
(
Void
)
#else
PUBLIC S16 szAccTst9(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 10 -- Initial context Setup Fail \n"));

   szAcUtlSztFillInitCxtSetupFail(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst10
 *
 *       Desc:    Test case for UE context release request
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */           

#ifdef ANSI
PUBLIC S16 szAccTst10
(
Void
)
#else
PUBLIC S16 szAccTst10(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 11 -- UE Context Release Request \n"));

   szAcUtlSztFillUeCxtRlsReq(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst11
 *
 *       Desc:    Test case for UE context release command
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */            

#ifdef ANSI
PUBLIC S16 szAccTst11
(
Void
)
#else
PUBLIC S16 szAccTst11(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 12 -- UE Context Release Command \n"));

   szAcUtlSztFillUeCxtRlsCmd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst12
 *
 *       Desc:    Test case for UE context release complete response
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */             

#ifdef ANSI
PUBLIC S16 szAccTst12
(
Void
)
#else
PUBLIC S16 szAccTst12(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 13 -- UE Context Release Complete Response \n"));

   szAcUtlSztFillUeCxtRlsCmpl(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst13
 *
 *       Desc:    Test case for UE context modification request
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */              

#ifdef ANSI
PUBLIC S16 szAccTst13
(
Void
)
#else
PUBLIC S16 szAccTst13(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 14 -- UE Context Modification Request \n"));

   szAcUtlSztFillUECntxtModRqst(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst14
 *
 *       Desc:    Test case for UE context modification response
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */               

#ifdef ANSI
PUBLIC S16 szAccTst14
(
Void
)
#else
PUBLIC S16 szAccTst14(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo = FALSE;

   SZAC_DBG((prntBuf," Executing Test 15 -- UE Context Modification Response \n"));

   szAcUtlSztFillUECntxtModResp(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst15
 *
 *       Desc:    Test case for UE context modification fail
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                

#ifdef ANSI
PUBLIC S16 szAccTst15
(
Void
)
#else
PUBLIC S16 szAccTst15(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 16 -- UE Context Modification Fail \n"));

   szAcUtlSztFillUeCxtModFail(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst16
 *
 *       Desc:    Test case for Initial UE message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                 

#ifdef ANSI
PUBLIC S16 szAccTst16
(
Void
)
#else
PUBLIC S16 szAccTst16(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 17 -- Initial UE Message \n"));

   szAcUtlSztFillInitUeMsg(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst17
 *
 *       Desc:    Test case for Downlink NAS transport message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                  

#ifdef ANSI
PUBLIC S16 szAccTst17
(
Void
)
#else
PUBLIC S16 szAccTst17(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 18 -- Downlink NAS Transport Message \n"));

   szAcUtlSztFillDwnlnkNasTpt(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst18
 *
 *       Desc:    Test case for Uplink NAS transport message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                   

#ifdef ANSI
PUBLIC S16 szAccTst18
(
Void
)
#else
PUBLIC S16 szAccTst18(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 19 -- Uplink NAS Transport Message \n"));

   szAcUtlSztFillUplnkNasTpt(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst19
 *
 *       Desc:    Test case for NAS non-delivery indication message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                    

#ifdef ANSI
PUBLIC S16 szAccTst19
(
Void
)
#else
PUBLIC S16 szAccTst19(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 20 -- NAS Non-delivery Indication Message \n"));

   szAcUtlSztFillNasNonDlvryInd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst20
 *
 *       Desc:    Test case for Error Indication
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                     

#ifdef ANSI
PUBLIC S16 szAccTst20
(
Void
)
#else
PUBLIC S16 szAccTst20(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 21 -- Error Indication \n"));

   szAcUtlSztFillErrInd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst21
 *
 *       Desc:    Test case for No data indication
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                      

#ifdef ANSI
PUBLIC S16 szAccTst21
(
Void
)
#else
PUBLIC S16 szAccTst21(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 22 -- No Data Indication \n"));

   szAcUtlSztFillInvalidPdu(&encPdu);

   SGetMsg(0, 0, &mBuf);

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret == ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}


/*
 *
 *       Fun:     szAccTst22
 *
 *       Desc:    Test case for Reset message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                       

#ifdef ANSI
PUBLIC S16 szAccTst22
(
Void
)
#else
PUBLIC S16 szAccTst22(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 23 -- Reset \n"));

   szAcUtlSztFillReset(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst23
 *
 *       Desc:    Test case for Reset Acknowledge
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                        

#ifdef ANSI
PUBLIC S16 szAccTst23
(
Void
)
#else
PUBLIC S16 szAccTst23(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 24 -- Reset Acknowledge \n"));

   szAcUtlSztFillResetAck(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst24
 *
 *       Desc:    Test case for S1 setup request
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                         

#ifdef ANSI
PUBLIC S16 szAccTst24
(
Void
)
#else
PUBLIC S16 szAccTst24(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 25 -- S1 Setup Req \n"));

   szAcUtlSztFillS1SetupReq(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst25
 *
 *       Desc:    Test case for S1 setup response
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                          

#ifdef ANSI
PUBLIC S16 szAccTst25
(
Void
)
#else
PUBLIC S16 szAccTst25(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 26 -- S1 Setup Rsp \n"));

   szAcUtlSztFillS1SetupRsp(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst26
 *
 *       Desc:    Test case for S1 setup fail message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                           

#ifdef ANSI
PUBLIC S16 szAccTst26
(
Void
)
#else
PUBLIC S16 szAccTst26(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 27 -- S1 Setup Fail \n"));

   szAcUtlSztFillS1SetupFail(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d\n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}



/*
 *
 *       Fun:     szAccTst27
 *
 *       Desc:    Test case for Paging message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                            

#ifdef ANSI
PUBLIC S16 szAccTst27
(
Void
)
#else
PUBLIC S16 szAccTst27(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 28 -- Paging Message\n"));

   szAcUtlSztFillPaging(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst28
 *
 *       Desc:    Test case for Handover required message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                             

#ifdef ANSI
PUBLIC S16 szAccTst28
(
Void
)
#else
PUBLIC S16 szAccTst28(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 29 -- Handover Required \n"));

   szAcUtlSztFillHovrReqd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed\n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst29
 *
 *       Desc:    Test case for Handover command message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                              

#ifdef ANSI
PUBLIC S16 szAccTst29
(
Void
)
#else
PUBLIC S16 szAccTst29(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 30 -- Handover Command \n"));

   szAcUtlSztFillHovrCmmd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst30
 *
 *       Desc:    Test case for Handover preparation failed message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                               

#ifdef ANSI
PUBLIC S16 szAccTst30
(
Void
)
#else
PUBLIC S16 szAccTst30(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 31 -- Handover Preparation Failed \n"));

   szAcUtlSztFillHovrPrepFail(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst31
 *
 *       Desc:    Test case for Handover request message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                

#ifdef ANSI
PUBLIC S16 szAccTst31
(
Void
)
#else
PUBLIC S16 szAccTst31(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 32 -- Handover Request \n"));

   szAcUtlSztFillHovrRqst(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst32
 *
 *       Desc:    Test case for Handover request acknowledge message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                 

#ifdef ANSI
PUBLIC S16 szAccTst32
(
Void
)
#else
PUBLIC S16 szAccTst32(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 33 -- Handover Request Ack \n"));

   szAcUtlSztFillHovrRqstAckg(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst33
 *
 *       Desc:    Test case for Handover failed message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                  

#ifdef ANSI
PUBLIC S16 szAccTst33
(
Void
)
#else
PUBLIC S16 szAccTst33(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 34 -- Handover Fail \n"));

   szAcUtlSztFillHovrFail(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst34
 *
 *       Desc:    Test case for Handover notify message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                   

#ifdef ANSI
PUBLIC S16 szAccTst34
(
Void
)
#else
PUBLIC S16 szAccTst34(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 35 -- Handover Notify \n"));

   szAcUtlSztFillHovrNtfy(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst35
 *
 *       Desc:    Test case for Path switch request message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                    

#ifdef ANSI
PUBLIC S16 szAccTst35
(
Void
)
#else
PUBLIC S16 szAccTst35(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 36 -- Path Switch Request \n"));

   szAcUtlSztFillPathSwRqst(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst36
 *
 *       Desc:    Test case for Path switch request acknowledge message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                     

#ifdef ANSI
PUBLIC S16 szAccTst36
(
Void
)
#else
PUBLIC S16 szAccTst36(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 37 -- Path Switch Request Ack \n"));

   szAcUtlSztFillPathSwRqstAckg(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst37
 *
 *       Desc:    Test case for Path switch request fail message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                      

#ifdef ANSI
PUBLIC S16 szAccTst37
(
Void
)
#else
PUBLIC S16 szAccTst37(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 38 -- Path Switch Request Fail \n"));

   szAcUtlSztFillPathSwRqstFail(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst38
 *
 *       Desc:    Test case for Handover cancel message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                       

#ifdef ANSI
PUBLIC S16 szAccTst38
(
Void
)
#else
PUBLIC S16 szAccTst38(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 39 -- Handover Cancel \n"));

   szAcUtlSztFillHovrCancel(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst39
 *
 *       Desc:    Test case for Handover cancel acknowledge message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                        

#ifdef ANSI
PUBLIC S16 szAccTst39
(
Void
)
#else
PUBLIC S16 szAccTst39(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 40 -- Handover Cancel Acknowledge \n"));

   szAcUtlSztFillHovrCancelAckg(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst40
 *
 *       Desc:    Test case for Enb status transfer message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                         

#ifdef ANSI
PUBLIC S16 szAccTst40
(
Void
)
#else
PUBLIC S16 szAccTst40(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 41 -- Enb Status Transfer \n"));

   szAcUtlSztFillENBStatusTfr(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst41
 *
 *       Desc:    Test case for Mme status transfer message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                          

#ifdef ANSI
PUBLIC S16 szAccTst41
(
Void
)
#else
PUBLIC S16 szAccTst41(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 42 -- MME Status Transfer \n"));

   szAcUtlSztFillMMEStatusTfr(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst42
 *
 *       Desc:    Test case for Deactivate trace message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                           

#ifdef ANSI
PUBLIC S16 szAccTst42
(
Void
)
#else
PUBLIC S16 szAccTst42(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 43 -- Deactivate Trace \n"));

   szAcUtlSztFillDeactvTrace(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst43
 *
 *       Desc:    Test case for Trace start message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                            

#ifdef ANSI
PUBLIC S16 szAccTst43
(
Void
)
#else
PUBLIC S16 szAccTst43(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 44 -- Trace Start \n"));

   szAcUtlSztFillTraceStart(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst44
 *
 *       Desc:    Test case for Trace fail indication
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                             

#ifdef ANSI
PUBLIC S16 szAccTst44
(
Void
)
#else
PUBLIC S16 szAccTst44(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 45 -- Trace Fail Indication \n"));

   szAcUtlSztFillTraceFailInd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst45
 *
 *       Desc:    Test case for Location reporting control message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                              

#ifdef ANSI
PUBLIC S16 szAccTst45
(
Void
)
#else
PUBLIC S16 szAccTst45(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 46 -- Location Reporting Control \n"));

   szAcUtlSztFillLocRprtngCntrl(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst46
 *
 *       Desc:    Test case for Location report fail indication message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                               

#ifdef ANSI
PUBLIC S16 szAccTst46
(
Void
)
#else
PUBLIC S16 szAccTst46(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 47 -- Location Report Fail Indication \n"));

   szAcUtlSztFillLocRprtngFailInd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst47
 *
 *       Desc:    Test case for Location report message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                

#ifdef ANSI
PUBLIC S16 szAccTst47
(
Void
)
#else
PUBLIC S16 szAccTst47(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 48 -- Location Report \n"));

   szAcUtlSztFillLocReport(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst48
 *
 *       Desc:    Test case for Enb configuration update message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                 

#ifdef ANSI
PUBLIC S16 szAccTst48
(
Void
)
#else
PUBLIC S16 szAccTst48(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 49 -- ENB Configure Update \n"));

   szAcUtlSztFillENBConfigUpd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst49
 *
 *       Desc:    Test case for Enb configuration update Acknowledge message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                  

#ifdef ANSI
PUBLIC S16 szAccTst49
(
Void
)
#else
PUBLIC S16 szAccTst49(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 50 -- ENB Configure Update Acknowledgement\n"));

   szAcUtlSztFillENBConfigUpdAckg(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst50
 *
 *       Desc:    Test case for Enb configuration update fail message
 *              
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                   

#ifdef ANSI
PUBLIC S16 szAccTst50
(
Void
)
#else
PUBLIC S16 szAccTst50(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 51 -- ENB Configure Update Fail \n"));

   szAcUtlSztFillENBConfigUpdFail(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst51
 *
 *       Desc:    Test case for Mme configuration update message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                    

#ifdef ANSI
PUBLIC S16 szAccTst51
(
Void
)
#else
PUBLIC S16 szAccTst51(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 52 -- MME Configure Update \n"));

   szAcUtlSztFillMMEConfigUpd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst52
 *
 *       Desc:    Test case for Mme configuration update acknowledgement message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                     

#ifdef ANSI
PUBLIC S16 szAccTst52
(
Void
)
#else
PUBLIC S16 szAccTst52(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 53 -- MME Configure Update Acknowledgement \n"));

   szAcUtlSztFillMMEConfigUpdAckg(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst53
 *
 *       Desc:    Test case for Mme configuration update fail message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                      

#ifdef ANSI
PUBLIC S16 szAccTst53
(
Void
)
#else
PUBLIC S16 szAccTst53(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 54 -- MME Configure Update Fail \n"));

   szAcUtlSztFillMMEConfigUpdFail(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst54
 *
 *       Desc:    Test case for Uplink S1 CDMA2000 tunneling message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                       

#ifdef ANSI
PUBLIC S16 szAccTst54
(
Void
)
#else
PUBLIC S16 szAccTst54(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 55 -- Uplink S1 CDMA2000 Tunneling \n"));

   szAcUtlSztFillUlnkS1cdma2000tunneling(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst55
 *
 *       Desc:    Test case for Downlink S1 CDMA2000 tunneling message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                        

#ifdef ANSI
PUBLIC S16 szAccTst55
(
Void
)
#else
PUBLIC S16 szAccTst55(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 56 -- Downlink S1 CDMA2000 Tunneling \n"));

   szAcUtlSztFillDlnkS1cdma2000tunneling(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst56
 *
 *       Desc:    Test case for UE capability info message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                         

#ifdef ANSI
PUBLIC S16 szAccTst56
(
Void
)
#else
PUBLIC S16 szAccTst56(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 57 -- UE Capability Information \n"));

   szAcUtlSztFillUECapbltyInfoInd(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst57
 *
 *       Desc:    Test case for Overload start message 
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                          

#ifdef ANSI
PUBLIC S16 szAccTst57
(
Void
)
#else
PUBLIC S16 szAccTst57(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 58 -- Overload Start \n"));

   szAcUtlSztFillOverloadStart(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst58
 *
 *       Desc:    Test case for Overload stop message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                           

#ifdef ANSI
PUBLIC S16 szAccTst58
(
Void
)
#else
PUBLIC S16 szAccTst58(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 59 -- Overload Stop \n"));

   szAcUtlSztFillOverloadStop(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst59
 *
 *       Desc:    Test case for Write replace warning request message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                            

#ifdef ANSI
PUBLIC S16 szAccTst59
(
Void
)
#else
PUBLIC S16 szAccTst59(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 60 -- Write Replace Warning Request \n"));

   szAcUtlSztFillWriteReplaceWarningRqst(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst60
 *
 *       Desc:    Test case for Write replace warning response message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                             

#ifdef ANSI
PUBLIC S16 szAccTst60
(
Void
)
#else
PUBLIC S16 szAccTst60(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 61 -- Write Replace Warning Response \n"));

   szAcUtlSztFillWriteReplaceWarningResp(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst61
 *
 *       Desc:    Test case for Enb direct information transfer message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                              

#ifdef ANSI
PUBLIC S16 szAccTst61
(
Void
)
#else
PUBLIC S16 szAccTst61(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 62 -- ENB Direct Information Transfer \n"));

   szAcUtlSztFillENBDirectInformTfr(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst62
 *
 *       Desc:    Test case for Mme direct information transfer message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                               

#ifdef ANSI
PUBLIC S16 szAccTst62
(
Void
)
#else
PUBLIC S16 szAccTst62(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 63 -- MME Direct Information Transfer \n"));

   szAcUtlSztFillMMEDirectInformTfr(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst63
 *
 *       Desc:    Test case for Private message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                


#ifdef ANSI
PUBLIC S16 szAccTst63
(
Void
)
#else
PUBLIC S16 szAccTst63(Void)
#endif
{
   
   S16           ret = ROK;
   
   SZAC_DBG((prntBuf," Executing Test 64 -- Private Message \n"));
   
   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst64
 *
 *       Desc:    Test case for Enb configuration transfer message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                 

#ifdef ANSI
PUBLIC S16 szAccTst64
(
Void
)
#else
PUBLIC S16 szAccTst64(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 65 -- ENB Config Transfer \n"));

   szAcUtlSztFillENBConfigTfr(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst65
 *
 *       Desc:    Test case for Mme configuration transfer message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                  

#ifdef ANSI
PUBLIC S16 szAccTst65
(
Void
)
#else
PUBLIC S16 szAccTst65(Void)
#endif
{
   S1apPdu       *encPdu;
   Buffer        *mBuf;
   S16           ret;
   SztEncDecStatus status;
   U8            dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 66 -- MME Config Transfer \n"));

   szAcUtlSztFillMMEConfigTfr(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &status, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
 *
 *       Fun:     szAccTst66
 *
 *       Desc:    Test case for Cell traffic trace message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                  
 

#ifdef ANSI
PUBLIC S16 szAccTst66
(
Void
)
#else
PUBLIC S16 szAccTst66(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   SztEncDecStatus encStatus;
   U8              dbgInfo;
#ifdef S1AP_REL8A0   
   SztReqStatus    stsStatus;
   SztSts          msgSts;
#endif

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 67 -- Cell Trafic Trace \n"));

   dbgInfo = TRUE;

   szAcUtlSztFillCellTrafficTrace(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }
   
#ifdef S1AP_REL8A0   
   
   /* If S1AP_REL8A0 flag is defined print the statistics here */
   
   msgSts.stsType = SZT_ENC_STS;
   ret = SzUiSztStsReq(&msgSts, ZEROSTS, &stsStatus);
   if(ret == ROK)
   {
      szAcPrntSts(&msgSts.msgSts);
   }

   msgSts.stsType = SZT_DEC_STS;
   ret = SzUiSztStsReq(&msgSts, ZEROSTS, &stsStatus);
   if(ret == ROK)
   {
      szAcPrntSts(&msgSts.msgSts);
   }
   
#endif   /* S1AP_REL8A0 */
 
   RETVALUE(ret);
}

#ifndef S1AP_REL8A0  /* Test Cases For S1AP Specification 9.2.2 */

/*
 *
 *       Fun:     szAccTst81
 *
 *       Desc:    Test case for Kill Request message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                  
 

#ifdef ANSI
PUBLIC S16 szAccTst81
(
Void
)
#else
PUBLIC S16 szAccTst81(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   SztEncDecStatus encStatus;
   U8              dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 68 -- Kill Request \n"));

   dbgInfo = TRUE;

   szAcUtlSztFillKillRqst(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst82
 *
 *       Desc:    Test case for Kill Response message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                  
 

#ifdef ANSI
PUBLIC S16 szAccTst82
(
Void
)
#else
PUBLIC S16 szAccTst82(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   SztEncDecStatus encStatus;
   U8              dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 69 -- Kill Response \n"));

   dbgInfo = TRUE;

   szAcUtlSztFillKillResp(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

  RETVALUE(ret);
}
 
/*
 *
 *       Fun:     szAccTst83
 *
 *       Desc:    Test case for Downlink UE Associated LPPa Transport message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                  
 

#ifdef ANSI
PUBLIC S16 szAccTst83
(
Void
)
#else
PUBLIC S16 szAccTst83(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   SztEncDecStatus encStatus;
   U8              dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 70 -- Downlink UE Associated LPPa Transport \n"));

   dbgInfo = TRUE;

   szAcUtlSztFillDlnkUeAssocLppaTprt(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst84
 *
 *       Desc:    Test case for Uplink UE Associated LPPa Transport message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                  
 

#ifdef ANSI
PUBLIC S16 szAccTst84
(
Void
)
#else
PUBLIC S16 szAccTst84(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   SztEncDecStatus encStatus;
   U8              dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 71 -- Uplink UE Associated LPPa Transport \n"));

   dbgInfo = TRUE;

   szAcUtlSztFillUlnkUeAssocLppaTprt(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst85
 *
 *       Desc:    Test case for Downlink Non UE Associated LPPa Transport message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                  
 

#ifdef ANSI
PUBLIC S16 szAccTst85
(
Void
)
#else
PUBLIC S16 szAccTst85(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   SztEncDecStatus encStatus;
   U8              dbgInfo;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 72 -- Downlink Non UE Associated LPPa Transport \n"));

   dbgInfo = TRUE;

   szAcUtlSztFillDlnkNonUeAssocLppaTprt(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &encStatus, dbgInfo);

   RETVALUE(ret);
}

/*
 *
 *       Fun:     szAccTst86
 *
 *       Desc:    Test case for Uplink Non UE Associated LPPa Transport message
 *       
 *       Ret:     ROK     - Success
 *                RFAILED - Failure
 *       
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */                                                                  
 

#ifdef ANSI
PUBLIC S16 szAccTst86
(
Void
)
#else
PUBLIC S16 szAccTst86(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   SztEncDecStatus encStatus;
   SztReqStatus    stsStatus;
   U8              dbgInfo;
   SztSts          msgSts;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 73 -- Uplink Non UE Associated LPPa Transport \n"));

   dbgInfo = TRUE;

   szAcUtlSztFillUlnkNonUeAssocLppaTprt(&encPdu);

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = SzUiSztEncReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecReq(encPdu, mBuf, &encStatus, dbgInfo);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",encStatus.cause));
      RETVALUE(ret);
   }

   msgSts.stsType = SZT_ENC_STS;
   ret = SzUiSztStsReq(&msgSts, ZEROSTS, &stsStatus);
   if(ret == ROK)
   {
      szAcPrntSts(&msgSts.msgSts);
   }

   msgSts.stsType = SZT_DEC_STS;
   ret = SzUiSztStsReq(&msgSts, ZEROSTS, &stsStatus);
   if(ret == ROK)
   {
      szAcPrntSts(&msgSts.msgSts);
   }


   RETVALUE(ret);
}

#endif      /* ifndef S1AP_REL_890 */

/*
*
*       Fun:     szAccTst67
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst67
(
Void
)
#else
PUBLIC S16 szAccTst67(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 67 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillCellTrafficTrace(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   szGetIE(&(encPdu->pdu), Sztid_MME_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   szGetIE(&(encPdu->pdu), Sztid_TraceCollectionEntityIPAddr, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_TraceCollectionEntityIPAddr, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_TraceCollectionEntityIPAddr, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   szGetIE(&(encPdu->pdu), Sztid_E_UTRAN_Trace_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_E_UTRAN_Trace_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_E_UTRAN_Trace_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   szGetIE(&(encPdu->pdu), Sztid_EUTRAN_CGI, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_EUTRAN_CGI, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_EUTRAN_CGI, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst68
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst68
(
Void
)
#else
PUBLIC S16 szAccTst68(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 68 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillHovrReqd(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_Src_ToTget_TprntCont, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_Src_ToTget_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_Src_ToTget_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_HovrTyp, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_HovrTyp, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_HovrTyp, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_TgetID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_TgetID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_TgetID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst69
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst69
(
Void
)
#else
PUBLIC S16 szAccTst69(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 69 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillHovrCmmd(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_Tget_ToSrc_TprntCont, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_Tget_ToSrc_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_Tget_ToSrc_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_HovrTyp, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_HovrTyp, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_HovrTyp, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_MME_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst70
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst70
(
Void
)
#else
PUBLIC S16 szAccTst70(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 70 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillHovrRqst(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_Cause, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_Cause, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_Cause, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_Src_ToTget_TprntCont, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_Src_ToTget_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_Src_ToTget_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_UESecurCapabilities, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_UESecurCapabilities, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_UESecurCapabilities, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_SecurCntxt, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_SecurCntxt, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_SecurCntxt, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_E_RABToBeSetupLstHOReq, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_E_RABToBeSetupLstHOReq, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_E_RABToBeSetupLstHOReq, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_UESecurCapabilities, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_UESecurCapabilities, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_UESecurCapabilities, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst71
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst71
(
Void
)
#else
PUBLIC S16 szAccTst71(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 71 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillHovrRqstAckg(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_E_RABAdmtdLst, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_E_RABAdmtdLst, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_E_RABAdmtdLst, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_Tget_ToSrc_TprntCont, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_Tget_ToSrc_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_Tget_ToSrc_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_MME_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst72
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst72
(
Void
)
#else
PUBLIC S16 szAccTst72(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 72 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillENBStatusTfr(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_StatusTfr_TprntCont, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_StatusTfr_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_StatusTfr_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_MME_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst73
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst73
(
Void
)
#else
PUBLIC S16 szAccTst73(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 73 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   szAcUtlSztFillMMEStatusTfr(&encPdu);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_StatusTfr_TprntCont, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_StatusTfr_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_StatusTfr_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_StatusTfr_TprntCont, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_StatusTfr_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_StatusTfr_TprntCont, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_MME_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}

/*
*
*       Fun:     szAccTst74
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst74
(
Void
)
#else
PUBLIC S16 szAccTst74(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 74 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillS1SetupReq(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_DefaultPagDRX, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_DefaultPagDRX, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_DefaultPagDRX, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_SuppTAs, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_SuppTAs, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_SuppTAs, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_Global_ENB_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_Global_ENB_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_Global_ENB_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNBname, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNBname, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNBname, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst75
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst75
(
Void
)
#else
PUBLIC S16 szAccTst75(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 75 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillE_RABSetupRqst(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_E_RABToBeSetupLstBrSUReq, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_E_RABToBeSetupLstBrSUReq, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_E_RABToBeSetupLstBrSUReq, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNB_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNB_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_MME_UE_S1AP_ID, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_MME_UE_S1AP_ID, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst76
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst76
(
Void
)
#else
PUBLIC S16 szAccTst76(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 76 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillDwnlnkNasTpt(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_NAS_PDU, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_NAS_PDU, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_NAS_PDU, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst77
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst77
(
Void
)
#else
PUBLIC S16 szAccTst77(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 77 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillInitCxtSetupReq(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_uEaggregateMaxBitrate, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_uEaggregateMaxBitrate, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_uEaggregateMaxBitrate, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_SecurKey, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_SecurKey, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_SecurKey, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_E_RABToBeSetupLstCtxtSUReq, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_E_RABToBeSetupLstCtxtSUReq, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_E_RABToBeSetupLstCtxtSUReq, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_UESecurCapabilities, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_UESecurCapabilities, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_UESecurCapabilities, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst78
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst78
(
Void
)
#else
PUBLIC S16 szAccTst78(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 78 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillInitUeMsg(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_TAI, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_TAI, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_TAI, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_EUTRAN_CGI, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_EUTRAN_CGI, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_EUTRAN_CGI, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_NAS_PDU, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_NAS_PDU, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_NAS_PDU, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst79
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst79
(
Void
)
#else
PUBLIC S16 szAccTst79(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 79 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillENBConfigUpd(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_CSG_IdLst, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_CSG_IdLst, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_CSG_IdLst, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_eNBname, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_eNBname, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_eNBname, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }  

   RETVALUE(ret);
}


/*
*
*       Fun:     szAccTst80
*
*       Desc:    Test case for Selective IE encode/decode
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst80
(
Void
)
#else
PUBLIC S16 szAccTst80(Void)
#endif
{
   S1apPdu         *encPdu;
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SztEncDecIE     *encDecIE;
   Mem             mem;
   SztReqStatus    status;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 80 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   szAcUtlSztFillENBDirectInformTfr(&encPdu);

   ret = cmAllocEvnt(sizeof(SztEncDecIE), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&encDecIE);

   /* Get the IE, call encode/decode */
   szGetIE(&(encPdu->pdu), Sztid_Inter_SystemInformTfrTypEDT, (TknU8**)&(encDecIE->iePtr));

   ret = SzUiSztEncIE(encDecIE, mBuf, Sztid_Inter_SystemInformTfrTypEDT, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecIE(encDecIE, mBuf, Sztid_Inter_SystemInformTfrTypEDT, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   RETVALUE(ret);
}
 

/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1

/*
*
*       Fun:     szAccTst87
*
*       Desc:    Test case for Selective IE encode/decode (TC SrcToTget &
*                TgetToSrc)
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst87
(
Void
)
#else
PUBLIC S16 szAccTst87(Void)
#endif
{
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SzMsgParamsIe   encDecIE;
   Mem             mem;
   SztReqStatus    status;
   U8              type;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 87 -- Selective IE encode/decode \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   /* SrcToTget Ie */

   type = 1;

   szAcUtlSztFillSrcToTget(type, &encDecIE.ieSdu);

   encDecIE.type = SZT_REQ_TYPE_ENCDEC_IE_SRCTGET;

   ret = SzUiSztEncTcIeReq(&encDecIE, mBuf, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecTcIeReq(&encDecIE, mBuf, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }


   /* TgetToSrc IE */

   szAcUtlSztFillTgetToSrc(&encDecIE.ieSdu);


   encDecIE.type = SZT_REQ_TYPE_ENCDEC_IE_TGETSRC;

   ret = SzUiSztEncTcIeReq(&encDecIE, mBuf, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecTcIeReq(&encDecIE, mBuf, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }
 

   RETVALUE(ret);
}

#endif  /* SZTV1 */

 /* sz008.301: Support for SRC RNC to Target RNC transparent container */
#ifdef SZTV3

/*
*
*       Fun:     szAccTst88
*
*       Desc:    Test case for Selective IE encode/decode (Src_RNC to &
*                Tget_RNC Transparent container) 
*       
*       Ret:     ROK     - Success
*                RFAILED - Failure
*       
*       Notes:   None
* 
*       File:    szac_encdec.c
* 
*/                                                                  
#ifdef ANSI
PUBLIC S16 szAccTst88
(
Void
)
#else
PUBLIC S16 szAccTst88(Void)
#endif
{
   Buffer          *mBuf;
   S16             ret;
   U8              dbgInfo;
   SzMsgParamsIe   encDecIE;
   Mem             mem;
   SztReqStatus    status;
   U8              type;

   /* Initialize the mem stracture */
   mem.region = 0;
   mem.pool = 0;

#ifdef DEBUGP
   dbgInfo = TRUE;
#endif

   SZAC_DBG((prntBuf," Executing Test 88 -- Enc/Dec of Src RNC to target RNC TC \n"));

   SGetMsg(0, 0, &mBuf);

   if(mBuf == NULLP)
   {
      SZAC_DBG((prntBuf," Allocation failed \n"));
      RETVALUE(RFAILED);
   }

   /* SrcToTget Ie */

   szAcUtlSztFillSrcRncToTgetRnc(&encDecIE.ieSdu);

   encDecIE.type = SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC;

   ret = SzUiSztEncTcIeReq(&encDecIE, mBuf, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecTcIeReq(&encDecIE, mBuf, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }


   /* TgetToSrc IE */

   szAcUtlSztFillTgetRncToSrcRnc(&encDecIE.ieSdu);


   encDecIE.type = SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC;

   ret = SzUiSztEncTcIeReq(&encDecIE, mBuf, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Encoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }

   ret = SzUiSztDecTcIeReq(&encDecIE, mBuf, &status);

   if(ret != ROK)
   {
      SZAC_DBG((prntBuf," Decoding failed cause = %d \n",status.cause));
      RETVALUE(ret);
   }
 

   RETVALUE(ret);
}

#endif  /* SZTV3 */


/*
 *
 *       Fun:     rdConQ
 *
 *       Desc:    Function to read console queue
 * 
 *      
 * 
 *       Notes:   None
 * 
 *       File:    szac_encdec.c
 * 
 */

#ifdef ANSI
PUBLIC S16 rdConQ
(
 Data data
)
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   UNUSED(data);
   RETVALUE(ROK);

}

/**********************************************************************

         End of file:     szac_encdec.c@@/main/Tenb_Intg_Branch_CC/1 - Mon Jan  7 19:23:20 2013

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz004.301   va          1. Updated for Transparent Container 
                                     Enc/Dec 
/main/1   sz006.301   ve    1. Removed un-necessary include files                                      
/main/1   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
