
/********************************************************************20**
  
     Name:    TCP UDP Convergence Layer (TUCL)
  
     Type:    C source file
  
     Desc:    C source Code used for testing TUCL in Trillium 
              Development environment.
              
              
     File:    hi_acc1.c
  
     Sid:      tl_acc1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:54 2015

     Prg:     asa
  
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */

/* external headers */
#ifdef HI_TLS
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#endif

#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common sockets */
#include "cm_tpt.h"        /* common transport defines */
#ifdef FTHA
#include "sht.h"           /* SHT Interface header files */
#endif
#include "lhi.h"           /* layer management, TUCL  */
#include "hit.h"           /* HIT interface */
#ifdef HI_LKSCTP
#include "sct.h"           /* SCT interface */
#endif
#include "hi.h"            /* TUCL internal defines */
#include "hi_err.h"        /* TUCL error */
#include "hi_accen.h"      /* TUCL environment dependent test defines */
#include "hi_acc.h"        /* TUCL test defines */
 
/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common sockets */
#include "cm_tpt.x"        /* common transport typedefs */
#ifdef FTHA
#include "sht.x"           /* SHT Interface defines */
#endif
#include "lhi.x"           /* layer management TUCL */
#ifdef HI_LKSCTP
#include "sct.h"           /* SCT interface */
#include "sct.x"           /* SCT interface */
#endif
#include "hit.x"           /* HIT interface */
#include "hi.x"            /* TUCL internal typedefs */
#include "hi_acc.x"        /* TUCL test  typedefs */
 
#ifndef WIN32
#include <signal.h> 
#endif

/* Global Variable */
/* Public variable declarations */

#ifdef HI_RUG
PUBLIC Bool remIntfValid = TRUE;
PUBLIC CmIntfVer remLhiIntfVer = LHIIFVER;
PUBLIC CmIntfVer remHitIntfVer = HITIFVER;
#endif /* HI_RUG */


/*
*
*       Fun:   hiAccMsgLstInit  
*
*       Desc:  This function is used to initialize the message database
*              in ACC Control Block
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
PUBLIC  S16 hiAccMsgLstInit
(
U16 len 
)
#else
PUBLIC  S16 hiAccMsgLstInit(len)
U16 len;
#endif
{

   Buffer *msg;
   U16     data;
   MsgLen  msgLen;
   MsgLen  msgIdx;
   U8      hdr[4];
   U16     len1,len2;
   Bool    flag;

   TRC2(hiAccMsgLstInit)

   if(!hiAccCb.msgLstInit)
   {
      flag = TRUE;

      /* Initialize the test message array in the control block */
      for (msgIdx  = 0; msgIdx < HI_ACC_NUM_TST_MSGS; msgIdx++)
      {
         hiAccCb.tstMsgs[msgIdx].id = msgIdx;  
         hiAccCb.tstMsgs[msgIdx].len = len;

         /* allocate message */
         if (SGetMsg(hiAccCb.init.region, hiAccCb.init.pool, &msg) != ROK)
            RETVALUE(RFAILED);
         if(flag)
            len1 = len - 4;
         else
            len1 = len;
         /* pre add payload */
         for (msgLen = 0; msgLen < len1; msgLen++)
         {  
            if (SRandom(&data) != ROK)
            {
               SPutMsg(msg);
               RETVALUE(RFAILED);
            }
            if (SAddPstMsg((U8)data, msg) != ROK)
            {
               SPutMsg(msg);
               RETVALUE(RFAILED);
            }
         }

         if(flag)
         {
            len2 = len;
            hdr[0] = GetLoByte(len2);
            hdr[1] = GetHiByte(len2);
            hdr[2] = HI_TPKT_HDR_RESERVED;
            hdr[3] = HI_TPKT_HDR_VERSION;
                
            /* The order of bytes is reversed upon addition,
             * so the message becomes like:
             * 0300<len1><len2>... */
            SAddPreMsgMult(hdr, HI_TPKT_HDR_LEN, msg);
         }
         
         hiAccCb.tstMsgs[msgIdx].msg = msg;
      }
      
      hiAccCb.bigMsg.id = HI_ACC_NUM_TST_MSGS;
      hiAccCb.bigMsg.len = HI_ACC_SIZEOF_BIG_MSG;

      len = HI_ACC_SIZEOF_BIG_MSG;

       /* allocate message */
      if (SGetMsg(hiAccCb.init.region, hiAccCb.init.pool, &msg) != ROK)
         RETVALUE(RFAILED);

      if(flag) 
         len1 = len - 4;
      else
         len1 = len;
       
      /* pre add payload */
      for (msgLen = 0; msgLen < len1; msgLen++)
      {
         if (SRandom(&data) != ROK)
         {
            SPutMsg(msg);
            RETVALUE(RFAILED);
         }

         if (SAddPstMsg((U8)data, msg) != ROK)
         { 
            SPutMsg(msg);
            RETVALUE(RFAILED);
         }
      }
       
      if(flag)
      {
          len2 = len;
          hdr[0]=GetLoByte(len2);
          hdr[1]=GetHiByte(len2);
          hdr[2]=HI_TPKT_HDR_RESERVED;
          hdr[3]=HI_TPKT_HDR_VERSION;
              
          /* The order of bytes is reversed upon addition,
           * so the message becomes like:
           * 0300<len1><len2>... */
          SAddPreMsgMult(hdr, HI_TPKT_HDR_LEN, msg);
      }
      
      hiAccCb.bigMsg.msg = msg;

      hiAccCb.msgLstInit = TRUE;
   }

   RETVALUE(ROK);
}/* end of hiAccMsgLstInit()*/


/*
*
*       Fun:   hiAccDeInitMsgLst
*
*       Desc:  This function is used to de initialize the messge list
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
PUBLIC S16 hiAccDeInitMsgLst
(
Void
)
#else
PUBLIC S16 hiAccDeInitMsgLst()
#endif
{

    U16 msgIdx;
    Status status;
    Txt prntBuf[100];

    if(hiAccCb.msgLstInit)
    {
         /* Initialize the test message array in the control block */
         for (msgIdx  = 0; msgIdx < HI_ACC_NUM_TST_MSGS; msgIdx++)
         {
             SPutMsg(hiAccCb.tstMsgs[msgIdx].msg);
         }
         SPutMsg(hiAccCb.bigMsg.msg);
    }

   SChkRes(hiAccCb.init.region, hiAccCb.init.pool, &status);
   sprintf(prntBuf, "Status (After Tests) - %d\n", status);
   SPrint(prntBuf);

   RETVALUE(ROK);
}/* end of hiAccDeInitMsgLst()*/


/*
*
*       Fun: hiAccInitTstTbl  
*
*       Desc:  Initialize the Test Case Table
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
PRIVATE S16 hiAccInitTstTbl
(
HiAccPFS16  *tstTbl         /* Test Table */
)
#else
PRIVATE S16 hiAccInitTstTbl(tstTbl)
HiAccPFS16  *tstTbl;        /* Test Table */
#endif
{
   TRC2(hiAccInitTstTbl)

   tstTbl[0] = hiAccTst0;
   tstTbl[1] = hiAccTst1;
#ifndef HI_DISABLE_GENSOCKET
   tstTbl[2] = hiAccTst2;
#else 
   tstTbl[2] = NULLP;
#endif /* HI_DISABLE_GENSOCKET */
 
#ifndef HI_DISABLE_GENSOCKET   
   tstTbl[3] = hiAccTst3; 
#else 
   tstTbl[3] = NULLP;
#endif /* HI_DISABLE_GENSOCKET */
 
   tstTbl[4] = hiAccTst4;
   tstTbl[5] = hiAccTst5;
   tstTbl[6] = hiAccTst6;

#ifdef HI_ACC_RAW_ENB
   tstTbl[7] = hiAccTst7;
#else
   tstTbl[7] = NULLP;
#endif 

#if (defined(IPV4_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))
   tstTbl[8] = hiAccTst8;
#else
   tstTbl[8] = NULLP;
#endif 

#ifdef IPV6_SUPPORTED
   tstTbl[9] = hiAccTst9;       
/* hi005.201 Test case 10 is guarded under HI_ACC_MCAST_ENB */
#ifdef HI_ACC_MCAST_ENB
   tstTbl[10] = hiAccTst10;       
#else 
   tstTbl[10] = NULLP;       
#endif /* HI_ACC_MCAST_ENB */
   tstTbl[11] = hiAccTst11;
#else
   tstTbl[9] = NULLP;       
   tstTbl[10] = NULLP;       
   tstTbl[11] = NULLP;
#endif /* IPV6_SUPPORTED */

#if (defined(IPV6_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))
   tstTbl[12] = hiAccTst12;
   tstTbl[13] = hiAccTst13;
#else
   tstTbl[12] = NULLP;
   tstTbl[13] = NULLP;
#endif 

#ifdef HI_RUG
   tstTbl[14] = hiAccTst14;
   tstTbl[15] = hiAccTst15;
   tstTbl[16] = hiAccTst16;
   tstTbl[17] = hiAccTst17;      
#else
   tstTbl[14] = NULLP;
   tstTbl[15] = NULLP;
   tstTbl[16] = NULLP;
   tstTbl[17] = NULLP;
#endif /* HI_RUG */   

#ifdef HI_TLS
   tstTbl[18] = hiAccTst18;
   tstTbl[19] = hiAccTst19;
#else
   tstTbl[18] = NULLP;
   tstTbl[19] = NULLP;
#endif  /* HI_TLS */
   /* hi002.105 (hi029.104) - addition hiAccTst20 */
   tstTbl[20] = hiAccTst20;
#ifdef HI_LKSCTP
   tstTbl[21] = hiAccTst21;
   tstTbl[22] = hiAccTst22;
   tstTbl[23] = hiAccTst23;
   tstTbl[24] = hiAccTst24;
   tstTbl[25] = hiAccTst25;
   tstTbl[26] = hiAccTst26;
   tstTbl[27] = hiAccTst27;
   tstTbl[28] = hiAccTst28;
   tstTbl[29] = hiAccTst29;
   tstTbl[30] = hiAccTst30;
   tstTbl[31] = hiAccTst31;
   tstTbl[32] = hiAccTst32;
   tstTbl[33] = hiAccTst33;
   tstTbl[34] = hiAccTst34;
   tstTbl[35] = hiAccTst35;
   tstTbl[36] = hiAccTst36;
   tstTbl[37] = hiAccTst37;
   tstTbl[38] = hiAccTst38;
   tstTbl[39] = hiAccTst39;
   tstTbl[40] = hiAccTst40;
   tstTbl[41] = hiAccTst41;
   tstTbl[42] = hiAccTst42;
   tstTbl[43] = hiAccTst43;
#ifdef HI_LKSCTP_USER_CONFIG
   tstTbl[44] = hiAccTst44;
#endif  /* HI_LKSCTP_USER_CONFIG */
#endif  /* HI_LKSCTP */

#ifdef HI_CONG_CHECK_TMR
   /*hi005.201 *Added hiAccTst45 test case to check 
	            *resource based conjestion timer */
   tstTbl[45] = hiAccTst45;
#else 
   tstTbl[45] = NULLP;
#endif /*HI_CONG_CHECK_TMR*/
#ifdef HI_LKSCTP
#ifdef HI_LKSCTP_USER_CONFIG
   /* hi012.201: outStream socket option test cases */
   tstTbl[46] = hiAccTst46;
   tstTbl[47] = hiAccTst47; 
#endif  /* HI_LKSCTP_USER_CONFIG */
#endif  /* HI_LKSCTP */
/* hi023.201: Trace indication for KSCTP test case */
#ifdef HI_LKSCTP
   tstTbl[48] = hiAccTst48;
#ifdef IPV6_SUPPORTED
   tstTbl[49] = hiAccTst49;
#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef SS_LINUX
   tstTbl[50] = hiAccTst50;
#else
   tstTbl[50] = NULLP;
#endif 
#else 
   tstTbl[50] = NULLP;
#endif /* SCT_ENDP_MULTI_IPADDR */
   tstTbl[51] = hiAccTst51;
   tstTbl[52] = hiAccTst52;
   tstTbl[53] = hiAccTst53;
   tstTbl[54] = hiAccTst54;
#endif /* IPV6_SUPPORTED */
   /* hi028.201: Added new test cases hiAccTst55 and hiAccTst56 */
   tstTbl[55] = hiAccTst55;
#ifndef CM_LKSCTP_NONBLOCK
   tstTbl[56] = hiAccTst56;
#else
   tstTbl[56] = NULLP;
#endif
#endif  /* HI_LKSCTP */

   /* hi028.201: Added new test cases hiAccTst57*/
#ifdef HI_ACC_GEN_RECONFIG
   tstTbl[57] = hiAccTst57;
#else
   tstTbl[57] = NULLP;
#endif

   RETVALUE(ROK);
}/*
    end of hiAccInitTstTbl()*/


/*
*
*       Fun:   hiInitTstSeqTbl   
*
*       Desc:  Reads the Test Sequence Table
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: Tests are executed in the order defined by this table.
*
*       File:  hi_acc1.c
*
*/
 
#ifdef ANSI
PRIVATE S16 hiAccInitTstSeqTbl 
(
U16      *tstSeqTbl         /* Test Sequence Table */
)
#else
PRIVATE S16 hiAccInitTstSeqTbl(tstSeqTbl) 
U16      *tstSeqTbl;        /* Test Sequence Table */
#endif
{
   S16 i = 0;

   TRC2(hiAccInitTstSeqTbl)

   tstSeqTbl[i++] = HI_TSTID_0;
   tstSeqTbl[i++] = HI_TSTID_1;

#ifndef HI_DISABLE_GENSOCKET   
   tstSeqTbl[i++] = HI_TSTID_2;
#endif 
   
#ifndef HI_DISABLE_GENSOCKET
#ifdef HI_ACC_MCAST_ENB
   tstSeqTbl[i++] = HI_TSTID_3;
#endif
#endif
   
   tstSeqTbl[i++] = HI_TSTID_4;
   tstSeqTbl[i++] = HI_TSTID_5;

   tstSeqTbl[i++] = HI_TSTID_6;

#ifdef HI_ACC_RAW_ENB
   tstSeqTbl[i++] = HI_TSTID_7;
#endif /* HI_ACC_RAW_ENB */

#if (defined(IPV4_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))
   tstSeqTbl[i++] = HI_TSTID_8;
#endif /* IPV4_OPTS_SUPPORTED && HI_RSVP_SUPPORT */

#ifdef IPV6_SUPPORTED
   tstSeqTbl[i++] = HI_TSTID_9;
#ifdef HI_ACC_MCAST_ENB
   tstSeqTbl[i++] = HI_TSTID_10;
#endif
   tstSeqTbl[i++] = HI_TSTID_11;

#if (defined(IPV6_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))
   tstSeqTbl[i++] = HI_TSTID_12;
   tstSeqTbl[i++] = HI_TSTID_13;
#endif /* IPV6_OPTS_SUPPORTED && HI_RSVP_SUPPORT */

#endif /* IPV6_SUPPORTED */

#ifdef HI_RUG
   tstSeqTbl[i++] = HI_TSTID_14;
   tstSeqTbl[i++] = HI_TSTID_15;
   tstSeqTbl[i++] = HI_TSTID_16;
   tstSeqTbl[i++] = HI_TSTID_17;     
#endif /* HI_RUG */

#ifdef HI_TLS
   tstSeqTbl[i++] = HI_TSTID_18;
   tstSeqTbl[i++] = HI_TSTID_19;
#endif
   tstSeqTbl[i++] = HI_TSTID_20;
#ifdef HI_LKSCTP
   tstSeqTbl[i++] = HI_TSTID_21;
   tstSeqTbl[i++] = HI_TSTID_22;
   tstSeqTbl[i++] = HI_TSTID_23;
   tstSeqTbl[i++] = HI_TSTID_24;
   tstSeqTbl[i++] = HI_TSTID_25;
   tstSeqTbl[i++] = HI_TSTID_26;
   tstSeqTbl[i++] = HI_TSTID_27;
   tstSeqTbl[i++] = HI_TSTID_28;
   tstSeqTbl[i++] = HI_TSTID_29;
   tstSeqTbl[i++] = HI_TSTID_30;
   tstSeqTbl[i++] = HI_TSTID_31;
   tstSeqTbl[i++] = HI_TSTID_32;
   tstSeqTbl[i++] = HI_TSTID_33;
   tstSeqTbl[i++] = HI_TSTID_34;
   tstSeqTbl[i++] = HI_TSTID_35;
   tstSeqTbl[i++] = HI_TSTID_36;
   tstSeqTbl[i++] = HI_TSTID_37;
   tstSeqTbl[i++] = HI_TSTID_38;
   tstSeqTbl[i++] = HI_TSTID_39;
   tstSeqTbl[i++] = HI_TSTID_40;
   tstSeqTbl[i++] = HI_TSTID_41;
   tstSeqTbl[i++] = HI_TSTID_42;
   tstSeqTbl[i++] = HI_TSTID_43;
#ifdef HI_LKSCTP_USER_CONFIG
   tstSeqTbl[i++] = HI_TSTID_44;
#endif
#endif
#ifdef HI_CONG_CHECK_TMR
   /*hi005.201 *Added hiAccTst45 test case to check 
	            *resource based conjestion timer */
   tstSeqTbl[i++] = HI_TSTID_45;
#endif /*HI_CONG_CHECK_TMR*/
   /* hi012.201: outStream socket option test cases */
#ifdef HI_LKSCTP
#ifdef HI_LKSCTP_USER_CONFIG
   tstSeqTbl[i++] = HI_TSTID_46;
   tstSeqTbl[i++] = HI_TSTID_47; 
#endif  /* HI_LKSCTP_USER_CONFIG */
#endif  /* HI_LKSCTP */
/* hi023.201: Trace indication for KSCTP test case */
	/* hi026.201  rss  1. Added IPV6 test case for ksctp */
#ifdef HI_LKSCTP
   tstSeqTbl[i++] = HI_TSTID_48; 
#ifdef IPV6_SUPPORTED
   tstSeqTbl[i++] = HI_TSTID_49; 
#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef SS_LINUX
   tstSeqTbl[i++] = HI_TSTID_50; 
#endif /* SS_LINUX */
#endif /* SCT_ENDP_MULTI_IPADDR */
   tstSeqTbl[i++] = HI_TSTID_51; 
   tstSeqTbl[i++] = HI_TSTID_52; 
   tstSeqTbl[i++] = HI_TSTID_53; 
   tstSeqTbl[i++] = HI_TSTID_54; 
#endif /* IPV6_SUPPORTED */
   /* hi028.201: Added new test cases hiAccTst55 and hiAccTst56 */
   tstSeqTbl[i++] = HI_TSTID_55; 
#ifndef CM_LKSCTP_NONBLOCK
   tstSeqTbl[i++] = HI_TSTID_56; 
#endif
#endif  /* HI_LKSCTP */

   /* hi028.201: Added new test cases hiAccTst57*/
#ifdef HI_ACC_GEN_RECONFIG
   tstSeqTbl[i++] = HI_TSTID_57; 
#endif
   tstSeqTbl[i++] = 0xffff;

   RETVALUE(ROK);
}


/*
*
*       Fun:   hiInitAccCb 
*
*       Desc:  This function is used to initialize the acceptance test
*              control block
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
PUBLIC S16 hiInitAccCb 
(
CmInetMemInfo *info
)
#else
PUBLIC S16 hiInitAccCb(info) 
CmInetMemInfo *info;
#endif
{

   TRC2(hiInitAccCb)

   /* install all the Test Handlers in the Test Table */
   hiAccInitTstTbl(hiAccCb.tstTbl);

   /* read the Test Sequence Table */
   hiAccInitTstSeqTbl(hiAccCb.tstSeqTbl);
 

   /* initialize the current test context */
   HI_ACC_INIT_CUR_TST;

   hiAccCb.curTst.id = hiAccCb.tstSeqTbl[0];
   hiAccCb.nxtIdx = 0;

   /* initialize the post structure for sending requests from the 
    * service user to the TUCL */

#ifdef LCHCLIHIT
   hiAccCb.uiPst.selector  = HIT_LC;
#else
   hiAccCb.uiPst.selector  = HIT_TC;
#endif

   hiAccCb.uiPst.region    = TSTREG;
   hiAccCb.uiPst.pool      = TSTPOOL;
   hiAccCb.uiPst.prior     = PRIOR0;
   hiAccCb.uiPst.route     = RTESPEC;
   hiAccCb.uiPst.dstEnt    = ENTHI;
   hiAccCb.uiPst.dstInst   = (TSTINST);
   hiAccCb.uiPst.dstProcId = SFndProcId(); 
   hiAccCb.uiPst.srcEnt    = ENTHC;
   hiAccCb.uiPst.srcInst   = TSTINST;
   hiAccCb.uiPst.srcProcId = SFndProcId();

   /* initialize the post structure for sending requests 
    * to TUCL from SM */

#ifdef LCHIMILHI
   hiAccCb.smPst.selector  = LHI_LC;
#else
   hiAccCb.smPst.selector  = LHI_TC;
#endif


   hiAccCb.smPst.region    = TSTREG;
   hiAccCb.smPst.pool      = TSTPOOL;
   hiAccCb.smPst.prior     = PRIOR0;
   hiAccCb.smPst.route     = RTESPEC;

   hiAccCb.smPst.dstEnt    = ENTHI;
   hiAccCb.smPst.dstInst   = TSTINST;
   hiAccCb.smPst.dstProcId = SFndProcId();

   hiAccCb.smPst.srcEnt    = ENTSM;
   hiAccCb.smPst.srcInst   = TSTINST;
   hiAccCb.smPst.srcProcId = SFndProcId();

   /* initialize the region and pool ids */
   hiAccCb.init.region = info->region;
   hiAccCb.init.pool   = info->pool;

   hiAccCb.info.region = info->region;
   hiAccCb.info.pool = info->pool;

   RETVALUE(ROK);
}/* end of hiInitAccCb ()*/


/*
*
*       Fun:   hiDispBanner 
*
*       Desc:  This function is used to display the test banner
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
PUBLIC S16 hiDispBanner 
(
Void
)
#else
PUBLIC S16 hiDispBanner() 
#endif
{

   Txt   prntBuf[HI_PRNTBUF_SIZE];

   TRC2(hiDispBanner)
 
   sprintf(prntBuf, "\n\n\n\n\n           TCP UDP CONVERGENCE LAYER \n\n");
   SPrint(prntBuf);
   sprintf(prntBuf, "          WELCOME TO THE ACCEPTANCE TESTS\n\n");
   SPrint(prntBuf);

   RETVALUE(ROK);
}/* end of  hiDispBanner()*/


/*
*
*       Fun:   hiInitAcc
*
*       Desc:  This function is used to initialize the acceptance test
*              module.
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
PUBLIC S16 hiInitAcc
(
CmInetMemInfo *info
)
#else
PUBLIC S16 hiInitAcc(info)
CmInetMemInfo *info;
#endif
{

   S16  ret;

   TRC2(hiInitAcc)

   cmMemset((U8*)&hiAccCb, 0, sizeof(HiAccCb));

   /* mark the Acceptance Test is ON */
   hiAccCb.testFlg = TRUE;

   /* initialise the loop counter */
   hiAccCb.nmbLoops = 0;

   /* initialize the acceptance control block */
   ret = hiInitAccCb(info);

   /* message list needs to be initialized only once even for acceptance
    * tests running in "forever" mode
    */
   hiAccCb.msgLstInit = FALSE;

   /* display the test banner */
   hiDispBanner();

   RETVALUE(ret);
}/* end of hiInitAcc()*/


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
PUBLIC S16 hiAccGenCfg 
(
Ent     ent,             /* entity id */
Inst    inst             /* instance id */
)
#else
PUBLIC S16 hiAccGenCfg(ent, inst) 
Ent     ent;             /* entity id */
Inst    inst;            /* instance id */
#endif
{
   HiMngmt      cfg;
#if (defined(HI_TLS)  &&  !defined(HI_ACC_TLS_PRNG_FILE))
   S16          i;
   Random       rnd;
#endif

   TRC2(hiAccGenCfg)

   /* TUCL intiliazation in progress */
   hiAccCb.cfgDone = FALSE;
   
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
   cfg.t.cfg.s.hiGen.numFdsPerSet = HI_ACC_MAX_FD_PER_FD_SET;
   cfg.t.cfg.s.hiGen.numFdBins = HI_ACC_FD_BLK_NUM_BINS;
   cfg.t.cfg.s.hiGen.selTimeout = HI_ACC_SEL_TIMEOUT;
#ifdef HI_LKSCTP
   cfg.t.cfg.s.hiGen.numAssocBins = HI_ACC_SCTP_ASSOC_NUM_BINS;
/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/
#ifdef HI_LKSCTP_USER_CONFIG
   if(hiAccCb.curTst.id == HI_TSTID_44)
   {
      HIACCPRINT((hiAccCb.prntBuf, "\n\t ************ Test case 44, In hiAccGenCfg, Configuring the Reconfigurable Values ************\n"));
      HIACCPRINT((hiAccCb.prntBuf, "\n\t\t  Values of, MAX Init ReTx = %d : Max Assoc ReTx = %d : Max Path Retx = %d\n", \
                 HI_ACC_SCTP_MAX_INIT_RETX, HI_ACC_SCTP_MAX_ASSOC_RETX, HI_ACC_SCTP_MAX_PATH_RETX));
      cfg.t.cfg.s.hiGen.maxInitReTx =  HI_ACC_SCTP_MAX_INIT_RETX;
      cfg.t.cfg.s.hiGen.maxAssocReTx = HI_ACC_SCTP_MAX_ASSOC_RETX;
      cfg.t.cfg.s.hiGen.maxPathReTx = HI_ACC_SCTP_MAX_PATH_RETX;
   }
#endif

#endif
   cfg.t.cfg.s.hiGen.numRawMsgsToRead = HI_ACC_RAW_MSGS_TOREAD;
   cfg.t.cfg.s.hiGen.numUdpMsgsToRead = HI_ACC_UDP_MSGS_TOREAD;
   cfg.t.cfg.s.hiGen.numClToAccept = HI_ACC_CL_TO_ACCEPT;
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
   cfg.t.cfg.s.hiGen.lmPst.dstInst   = TSTINST; 
   cfg.t.cfg.s.hiGen.lmPst.dstProcId = SFndProcId();  /* src proc id */

   cfg.t.cfg.s.hiGen.lmPst.srcEnt    = ENTHI;         /* src entity */
   cfg.t.cfg.s.hiGen.lmPst.srcInst   = TSTINST;       /* src inst */
   cfg.t.cfg.s.hiGen.lmPst.srcProcId = SFndProcId();  /* src proc id */

#ifdef HI_RUG
   cfg.t.cfg.s.hiGen.lmPst.intfVer = remLhiIntfVer;  /* LM intfc version num */
#endif /* HI_RUG */   

   cmMemcpy((U8 *) &hiAccCb.init.lmPst, (U8 *) &cfg.t.cfg.s.hiGen.lmPst, 
         (U32)sizeof(Pst));

#ifdef HI_SPECIFY_GENSOCK_ADDR
   cfg.t.cfg.s.hiGen.ipv4GenSockAddr.address = CM_INET_INADDR_ANY;
   cfg.t.cfg.s.hiGen.ipv4GenSockAddr.port = 0;
#ifdef IPV6_SUPPORTED
   cfg.t.cfg.s.hiGen.ipv6GenSockAddr.address = CM_INET_INADDR6_ANY;
   cfg.t.cfg.s.hiGen.ipv6GenSockAddr.port = 0;
#endif /* IPV6_SUPPORTED */
#endif /* HI_SPECIFY_GENSOCK_ADDR */

#ifdef HI_TLS
   cfg.t.cfg.s.hiGen.initOpenSSL = TRUE;
   cfg.t.cfg.s.hiGen.numContexts = 2;
#ifdef HI_ACC_TLS_PRNG_FILE
   cfg.t.cfg.s.hiGen.prng.option = LHI_OSSL_PRNG_FILE;
   cmMemcpy((U8 *)cfg.t.cfg.s.hiGen.prng.u.file, (U8 *)"/dev/urandom", 13);
#else
   cfg.t.cfg.s.hiGen.prng.option =  LHI_OSSL_PRNG_SEED;
   for (i = 0;  i < LHI_OSSL_PRNG_SEED_LEN;  i++)
   {
      SRandom(&rnd);
      cfg.t.cfg.s.hiGen.prng.u.seed[i] = (U8)rnd;
   }
#endif /* HI_ACC_TLS_PRNG_FILE */
#endif /* HI_TLS */

   (Void) SmMiLhiCfgReq(&hiAccCb.smPst, &cfg);

   RETVALUE(ROK);
}/* end of  hiAccGenCfg()*/


/*hi028.201: Added new function hiAccGenCfg_1()*/
/*
*
*       Fun:   hiAccGenCfg_1 
*
*       Desc:  This function is used to do reconfiguration of General 
*              Configuration in TUCL.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc1.c
*
*/
#ifdef HI_ACC_GEN_RECONFIG
#ifdef ANSI
PUBLIC S16 hiAccGenCfg_1 
(
Ent     ent,             /* entity id */
Inst    inst,             /* instance id */
Inst    lmInst           /* layer manager instance id */
)
#else
PUBLIC S16 hiAccGenCfg_1(ent, inst, lmInst) 
Ent     ent;             /* entity id */
Inst    inst;            /* instance id */
Inst    lmInst;          /* layer manager instance id */
#endif
{
   HiMngmt      cfg;
#if (defined(HI_TLS)  &&  !defined(HI_ACC_TLS_PRNG_FILE))
   S16          i;
   Random       rnd;
#endif

   TRC2(hiAccGenCfg_1)

   /* TUCL intiliazation in progress */
   hiAccCb.cfgDone = FALSE;
   
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
   cfg.t.cfg.s.hiGen.numFdsPerSet = HI_ACC_MAX_FD_PER_FD_SET;
   cfg.t.cfg.s.hiGen.numFdBins = HI_ACC_FD_BLK_NUM_BINS;
   cfg.t.cfg.s.hiGen.selTimeout = HI_ACC_SEL_TIMEOUT;
#ifdef HI_LKSCTP
   cfg.t.cfg.s.hiGen.numAssocBins = HI_ACC_SCTP_ASSOC_NUM_BINS;
/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/
#ifdef HI_LKSCTP_USER_CONFIG
   if(hiAccCb.curTst.id == HI_TSTID_44)
   {
      HIACCPRINT((hiAccCb.prntBuf, "\n\t ************ Test case 44, In hiAccGenCfg_1, Configuring the Reconfigurable Values ************\n"));
      HIACCPRINT((hiAccCb.prntBuf, "\n\t\t  Values of, MAX Init ReTx = %d : Max Assoc ReTx = %d : Max Path Retx = %d\n", \
                 HI_ACC_SCTP_MAX_INIT_RETX, HI_ACC_SCTP_MAX_ASSOC_RETX, HI_ACC_SCTP_MAX_PATH_RETX));
      cfg.t.cfg.s.hiGen.maxInitReTx =  HI_ACC_SCTP_MAX_INIT_RETX;
      cfg.t.cfg.s.hiGen.maxAssocReTx = HI_ACC_SCTP_MAX_ASSOC_RETX;
      cfg.t.cfg.s.hiGen.maxPathReTx = HI_ACC_SCTP_MAX_PATH_RETX;
   }
#endif

#endif
   cfg.t.cfg.s.hiGen.numRawMsgsToRead = HI_ACC_RAW_MSGS_TOREAD;
   cfg.t.cfg.s.hiGen.numUdpMsgsToRead = HI_ACC_UDP_MSGS_TOREAD;
   cfg.t.cfg.s.hiGen.numClToAccept = HI_ACC_CL_TO_ACCEPT;
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
   cfg.t.cfg.s.hiGen.lmPst.dstInst   = lmInst;       /* dst inst */
   cfg.t.cfg.s.hiGen.lmPst.dstProcId = SFndProcId();  /* src proc id */

   cfg.t.cfg.s.hiGen.lmPst.srcEnt    = ENTHI;         /* src entity */
   cfg.t.cfg.s.hiGen.lmPst.srcInst   = TSTINST;       /* src inst */
   cfg.t.cfg.s.hiGen.lmPst.srcProcId = SFndProcId();  /* src proc id */

#ifdef HI_RUG
   cfg.t.cfg.s.hiGen.lmPst.intfVer = remLhiIntfVer;  /* LM intfc version num */
#endif /* HI_RUG */   

   cmMemcpy((U8 *) &hiAccCb.init.lmPst, (U8 *) &cfg.t.cfg.s.hiGen.lmPst, 
         (U32)sizeof(Pst));

#ifdef HI_SPECIFY_GENSOCK_ADDR
   cfg.t.cfg.s.hiGen.ipv4GenSockAddr.address = CM_INET_INADDR_ANY;
   cfg.t.cfg.s.hiGen.ipv4GenSockAddr.port = 0;
#ifdef IPV6_SUPPORTED
   cfg.t.cfg.s.hiGen.ipv6GenSockAddr.address = CM_INET_INADDR6_ANY;
   cfg.t.cfg.s.hiGen.ipv6GenSockAddr.port = 0;
#endif /* IPV6_SUPPORTED */
#endif /* HI_SPECIFY_GENSOCK_ADDR */

#ifdef HI_TLS
   cfg.t.cfg.s.hiGen.initOpenSSL = TRUE;
   cfg.t.cfg.s.hiGen.numContexts = 2;
#ifdef HI_ACC_TLS_PRNG_FILE
   cfg.t.cfg.s.hiGen.prng.option = LHI_OSSL_PRNG_FILE;
   cmMemcpy((U8 *)cfg.t.cfg.s.hiGen.prng.u.file, (U8 *)"/dev/urandom", 13);
#else
   cfg.t.cfg.s.hiGen.prng.option =  LHI_OSSL_PRNG_SEED;
   for (i = 0;  i < LHI_OSSL_PRNG_SEED_LEN;  i++)
   {
      SRandom(&rnd);
      cfg.t.cfg.s.hiGen.prng.u.seed[i] = (U8)rnd;
   }
#endif /* HI_ACC_TLS_PRNG_FILE */
#endif /* HI_TLS */

   hiAccCb.smPst.srcInst = lmInst;
   (Void) SmMiLhiCfgReq(&hiAccCb.smPst, &cfg);

   RETVALUE(ROK);
}/* end of  hiAccGenCfg_1()*/

#endif

/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/
#ifdef HI_LKSCTP
/*
*
*       Fun:   hiAccGenReCfg 
*
*       Desc:  This function is used to do the Reconfigure the reconfigurable 
*              parameters in General Configuration of TUCL
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
PUBLIC S16 hiAccGenReCfg 
(
Ent     ent,             /* entity id */
Inst    inst             /* instance id */
)
#else
PUBLIC S16 hiAccGenReCfg(ent, inst) 
Ent     ent;             /* entity id */
Inst    inst;            /* instance id */
#endif
{
   HiMngmt      cfg;
#if (defined(HI_TLS)  &&  !defined(HI_ACC_TLS_PRNG_FILE))
   S16          i;
   Random       rnd;
#endif

   TRC2(hiAccGenReCfg)

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
   cfg.t.cfg.s.hiGen.numFdsPerSet = HI_ACC_MAX_FD_PER_FD_SET;
   cfg.t.cfg.s.hiGen.numFdBins = HI_ACC_FD_BLK_NUM_BINS;
   cfg.t.cfg.s.hiGen.selTimeout = HI_ACC_SEL_TIMEOUT;
#ifdef HI_LKSCTP
   cfg.t.cfg.s.hiGen.numAssocBins = HI_ACC_SCTP_ASSOC_NUM_BINS;
#ifdef HI_LKSCTP_USER_CONFIG
   if(hiAccCb.curTst.id == HI_TSTID_44)
   {
      HIACCPRINT((hiAccCb.prntBuf, "\n\t ************ Test case 44, In hiAccGenReCfg, Reconfiguring the Reconfigurable Values ************\n"));
      HIACCPRINT((hiAccCb.prntBuf, "\n\t\t  Values of, MAX Init ReTx = %d : Max Assoc ReTx = %d : Max Path Retx = %d\n", \
                 HI_ACC_SCTP_MAX_INIT_RETX+1, HI_ACC_SCTP_MAX_ASSOC_RETX+1, HI_ACC_SCTP_MAX_PATH_RETX+1));
      cfg.t.cfg.s.hiGen.maxInitReTx =  HI_ACC_SCTP_MAX_INIT_RETX+1;
      cfg.t.cfg.s.hiGen.maxAssocReTx = HI_ACC_SCTP_MAX_ASSOC_RETX+1;
      cfg.t.cfg.s.hiGen.maxPathReTx = HI_ACC_SCTP_MAX_PATH_RETX+1;
   }
#endif

#endif
   cfg.t.cfg.s.hiGen.numRawMsgsToRead = HI_ACC_RAW_MSGS_TOREAD;
   cfg.t.cfg.s.hiGen.numUdpMsgsToRead = HI_ACC_UDP_MSGS_TOREAD;
   cfg.t.cfg.s.hiGen.numClToAccept = HI_ACC_CL_TO_ACCEPT;
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
   cfg.t.cfg.s.hiGen.lmPst.dstProcId = SFndProcId();  /* src proc id */

   cfg.t.cfg.s.hiGen.lmPst.srcEnt    = ENTHI;         /* src entity */
   cfg.t.cfg.s.hiGen.lmPst.srcInst   = TSTINST;       /* src inst */
   cfg.t.cfg.s.hiGen.lmPst.srcProcId = SFndProcId();  /* src proc id */

#ifdef HI_RUG
   cfg.t.cfg.s.hiGen.lmPst.intfVer = remLhiIntfVer;  /* LM intfc version num */
#endif /* HI_RUG */   

   cmMemcpy((U8 *) &hiAccCb.init.lmPst, (U8 *) &cfg.t.cfg.s.hiGen.lmPst, 
         (U32)sizeof(Pst));

#ifdef HI_SPECIFY_GENSOCK_ADDR
   cfg.t.cfg.s.hiGen.ipv4GenSockAddr.address = CM_INET_INADDR_ANY;
   cfg.t.cfg.s.hiGen.ipv4GenSockAddr.port = 0;
#ifdef IPV6_SUPPORTED
   cfg.t.cfg.s.hiGen.ipv6GenSockAddr.address = CM_INET_INADDR6_ANY;
   cfg.t.cfg.s.hiGen.ipv6GenSockAddr.port = 0;
#endif /* IPV6_SUPPORTED */
#endif /* HI_SPECIFY_GENSOCK_ADDR */

#ifdef HI_TLS
   cfg.t.cfg.s.hiGen.initOpenSSL = TRUE;
   cfg.t.cfg.s.hiGen.numContexts = 2;
#ifdef HI_ACC_TLS_PRNG_FILE
   cfg.t.cfg.s.hiGen.prng.option = LHI_OSSL_PRNG_FILE;
   cmMemcpy((U8 *)cfg.t.cfg.s.hiGen.prng.u.file, (U8 *)"/dev/urandom", 13);
#else
   cfg.t.cfg.s.hiGen.prng.option =  LHI_OSSL_PRNG_SEED;
   for (i = 0;  i < LHI_OSSL_PRNG_SEED_LEN;  i++)
   {
      SRandom(&rnd);
      cfg.t.cfg.s.hiGen.prng.u.seed[i] = (U8)rnd;
   }
#endif /* HI_ACC_TLS_PRNG_FILE */
#endif /* HI_TLS */

   (Void) SmMiLhiCfgReq(&hiAccCb.smPst, &cfg);

   RETVALUE(ROK);
}/* end of  hiAccGenReCfg()*/
#endif





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
#ifdef HI_LKSCTP 
#ifdef ANSI
PUBLIC S16 hiAccSapCfg 
(
SpId  spId,                /* service provider id for HI SAP */
U8 sap_type               /* Type of SAP : SCT or HIT */
)
#else
PUBLIC S16 hiAccSapCfg(spId, sap_type) 
SpId  spId;               /* service provider id for HI SAP */
U8 sap_type;               /* Type of SAP : SCT or HIT */
#endif
#else
#ifdef ANSI
PUBLIC S16 hiAccSapCfg 
(
SpId  spId                 /* service provider id for HI SAP */
)
#else
PUBLIC S16 hiAccSapCfg(spId) 
SpId  spId;               /* service provider id for HI SAP */
#endif
#endif
{

   HiMngmt   cfg;

   TRC2(hiAccSapCfg)

   /* clear the config structure first */
   HI_ZERO((U8 *) &cfg, sizeof(HiMngmt));

   /* prepare header */
   cfg.hdr.entId.ent   = ENTHI;           /* entity */
   cfg.hdr.entId.inst  = (TSTINST);       /* instance */
   cfg.hdr.elmId.elmnt = STTSAP;          /* general */
   cfg.hdr.transId     = HI_ACC_TRANSID;  /* transaction identifier */

#ifdef LCHIMILHI
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_LC);
#else
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_TC);
#endif
   
   cfg.t.cfg.s.hiSap.spId            = spId;
   cfg.t.cfg.s.hiSap.flcEnb          = HI_ACC_SAP_FLC_ENB_FLAG;
   cfg.t.cfg.s.hiSap.txqCongStrtLim  = HI_ACC_SAP_FLC_STRT_LIM;
   cfg.t.cfg.s.hiSap.txqCongDropLim  = HI_ACC_SAP_FLC_DRP_LIM;
   cfg.t.cfg.s.hiSap.txqCongStopLim  = HI_ACC_SAP_FLC_STP_LIM;
   cfg.t.cfg.s.hiSap.numBins         = HI_ACC_SAP_NMB_BINS;
#ifdef HI_LKSCTP
   if (sap_type == HI_HIT_SAP)
   {
        cfg.t.cfg.s.hiSap.type = HI_HIT_SAP;
   }
   else if(sap_type == HI_SCT_SAP)
   { 
        cfg.t.cfg.s.hiSap.type = HI_SCT_SAP;
   }
   else 
   {
        cfg.t.cfg.s.hiSap.type = sap_type;
        /*Print Error*/
   }

#ifdef HI_LKSCTP_USER_CONFIG
   /* hi012.201: outStream socket option test cases */
   cfg.t.cfg.s.hiSap.maxNmbInStrms = HI_MAX_INSTREAMS;
   cfg.t.cfg.s.hiSap.maxNmbOutStrms = HI_MAX_OUTSTREAMS;
#endif

/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/
#ifdef HI_LKSCTP_USER_CONFIG
   if(hiAccCb.curTst.id == HI_TSTID_44)
   {
        HIACCPRINT((hiAccCb.prntBuf, "\n\t ************ Test case 44, In hiAccSapCfg, Configuring the Reconfigurable Values ************\n"));
        HIACCPRINT((hiAccCb.prntBuf, "\n\t\t  Values of, RTO Initial = %d : RTO Min = %d : RTO Max = %d\n", \
                   HI_ACC_SCTP_RTO_INITIAL, HI_ACC_SCTP_RTO_MIN, HI_ACC_SCTP_RTO_MAX));
        HIACCPRINT((hiAccCb.prntBuf, "\n\t\t  Values of, T1 Init Value = %d : COOKIE LIFE = %d : HB INTERVAL = %d\n\n", \
                   HI_ACC_SCTP_T1_INIT, HI_ACC_SCTP_COOKIE_LIFE, HI_ACC_SCTP_HB_INTERVAL));
        cfg.t.cfg.s.hiSap.rtoInitial = HI_ACC_SCTP_RTO_INITIAL;
        cfg.t.cfg.s.hiSap.rtoMin = HI_ACC_SCTP_RTO_MIN;
        cfg.t.cfg.s.hiSap.rtoMax = HI_ACC_SCTP_RTO_MAX;
        cfg.t.cfg.s.hiSap.t1Init = HI_ACC_SCTP_T1_INIT;
        cfg.t.cfg.s.hiSap.cookieLife = HI_ACC_SCTP_COOKIE_LIFE;
        cfg.t.cfg.s.hiSap.intervalTm = HI_ACC_SCTP_HB_INTERVAL;
        cfg.t.cfg.s.hiSap.hBeatEnable = TRUE;
   }
#endif /*HI_LKSCTP_USER_CONFIG*/

#endif

   /* update the upper interface parameters */
#ifdef LCHIUIHIT
   cfg.t.cfg.s.hiSap.uiSel = HI_UISEL_LC;  /* loosely coupled */
#else
   cfg.t.cfg.s.hiSap.uiSel = HI_UISEL_TC;  /* tightly coupled */
#endif

   cfg.t.cfg.s.hiSap.uiMemId.region = TSTREG;  /* defualt priority */
   cfg.t.cfg.s.hiSap.uiMemId.pool   = TSTPOOL; /* defualt priority */
   cfg.t.cfg.s.hiSap.uiPrior        = PRIOR0;  /* defualt priority */
   cfg.t.cfg.s.hiSap.uiRoute        = RTESPEC; /* default route */

#ifdef HI_RUG
   cfg.t.cfg.s.hiSap.remIntfValid = remIntfValid;         
   cfg.t.cfg.s.hiSap.remIntfVer = remHitIntfVer;         
#endif /* HI_RUG */
   
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

   /* give configuration request to layer */
   (Void) SmMiLhiCfgReq(&hiAccCb.smPst, &cfg);

   RETVALUE(ROK);
}/* end of  hiAccSapCfg()*/

/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/

/*
*
*       Fun:   hiAccSapReCfg 
*
*       Desc:  This function is used to reconfigure the reconfigurable
*              parameters of a transport SAP
*              
*       Ret:   ROK
*              RFAILED
*
*       Notes: None
*
*       File:  hi_acc1.c
*
*/
#ifdef HI_LKSCTP
#ifdef ANSI
PUBLIC S16 hiAccSapReCfg 
(
SpId  spId,                /* service provider id for HI SAP */
U8 sap_type               /* Type of SAP : SCT or HIT */
)
#else
PUBLIC S16 hiAccSapReCfg(spId, sap_type) 
SpId  spId;               /* service provider id for HI SAP */
U8 sap_type;               /* Type of SAP : SCT or HIT */
#endif
#else
#ifdef ANSI
PUBLIC S16 hiAccSapReCfg 
(
SpId  spId                 /* service provider id for HI SAP */
)
#else
PUBLIC S16 hiAccSapReCfg(spId) 
SpId  spId;               /* service provider id for HI SAP */
#endif
#endif
{

   HiMngmt   cfg;

   TRC2(hiAccSapReCfg)

   /* clear the config structure first */
   HI_ZERO((U8 *) &cfg, sizeof(HiMngmt));

   /* prepare header */
   cfg.hdr.entId.ent   = ENTHI;           /* entity */
   cfg.hdr.entId.inst  = (TSTINST);       /* instance */
   cfg.hdr.elmId.elmnt = STTSAP;          /* general */
   cfg.hdr.transId     = HI_ACC_TRANSID;  /* transaction identifier */

#ifdef LCHIMILHI
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_LC);
#else
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_TC);
#endif
   
   cfg.t.cfg.s.hiSap.spId            = spId;
   cfg.t.cfg.s.hiSap.flcEnb          = HI_ACC_SAP_FLC_ENB_FLAG;
   cfg.t.cfg.s.hiSap.txqCongStrtLim  = HI_ACC_SAP_FLC_STRT_LIM;
   cfg.t.cfg.s.hiSap.txqCongDropLim  = HI_ACC_SAP_FLC_DRP_LIM;
   cfg.t.cfg.s.hiSap.txqCongStopLim  = HI_ACC_SAP_FLC_STP_LIM;
   cfg.t.cfg.s.hiSap.numBins         = HI_ACC_SAP_NMB_BINS;
#ifdef HI_LKSCTP
   if (sap_type == HI_HIT_SAP)
   {
        cfg.t.cfg.s.hiSap.type = HI_HIT_SAP;
   }
   else if(sap_type == HI_SCT_SAP)
   { 
        cfg.t.cfg.s.hiSap.type = HI_SCT_SAP;
   }
   else 
   {
        cfg.t.cfg.s.hiSap.type = sap_type;
        /*Print Error*/
   }
/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/
#ifdef HI_LKSCTP_USER_CONFIG
   if(hiAccCb.curTst.id == HI_TSTID_44)
   {
        HIACCPRINT((hiAccCb.prntBuf, "\n\t *********** Test case 44, In hiAccSapReCfg, Reconfiguring the Reconfigurable Values **********\n"));
        HIACCPRINT((hiAccCb.prntBuf, "\n\t\t   Values of, RTO Initial = %d : RTO Min = %d : RTO Max = %d\n", \
                   HI_ACC_SCTP_RTO_INITIAL+1, HI_ACC_SCTP_RTO_MIN+1, HI_ACC_SCTP_RTO_MAX+1));
        HIACCPRINT((hiAccCb.prntBuf, "\n\t\t   Values of, COOKIE LIFE = %d : HB INTERVAL = %d\n\n", \
                   HI_ACC_SCTP_COOKIE_LIFE+1, HI_ACC_SCTP_HB_INTERVAL+1));
        cfg.t.cfg.s.hiSap.rtoInitial = HI_ACC_SCTP_RTO_INITIAL+1;
        cfg.t.cfg.s.hiSap.rtoMin = HI_ACC_SCTP_RTO_MIN+1;
        cfg.t.cfg.s.hiSap.rtoMax = HI_ACC_SCTP_RTO_MAX+1;
        cfg.t.cfg.s.hiSap.cookieLife = HI_ACC_SCTP_COOKIE_LIFE+1;
        cfg.t.cfg.s.hiSap.intervalTm = HI_ACC_SCTP_HB_INTERVAL+1;
   }
#endif /*HI_LKSCTP_USER_CONFIG*/

#endif

   /* update the upper interface parameters */
#ifdef LCHIUIHIT
   cfg.t.cfg.s.hiSap.uiSel = HI_UISEL_LC;  /* loosely coupled */
#else
   cfg.t.cfg.s.hiSap.uiSel = HI_UISEL_TC;  /* tightly coupled */
#endif

   cfg.t.cfg.s.hiSap.uiMemId.region = TSTREG;  /* defualt priority */
   cfg.t.cfg.s.hiSap.uiMemId.pool   = TSTPOOL; /* defualt priority */
   cfg.t.cfg.s.hiSap.uiPrior        = PRIOR0;  /* defualt priority */
   cfg.t.cfg.s.hiSap.uiRoute        = RTESPEC; /* default route */

#ifdef HI_RUG
   cfg.t.cfg.s.hiSap.remIntfValid = remIntfValid;         
   cfg.t.cfg.s.hiSap.remIntfVer = remHitIntfVer;         
#endif /* HI_RUG */
   
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

   /* give configuration request to layer */
   (Void) SmMiLhiCfgReq(&hiAccCb.smPst, &cfg);

   RETVALUE(ROK);
}/* end of  hiAccSapReCfg()*/

#ifdef HI_TLS

/*
*
*       Fun:   hiAccCtx1Cfg 
*
*       Desc:  This function is used to configure a TLS/OpenSSL
*              context.
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
PUBLIC S16 hiAccCtx1Cfg 
(
Void
)
#else
PUBLIC S16 hiAccCtx1Cfg() 
#endif
{
   HiMngmt      cfg;
   HiCtxCfg     *cc;

   TRC2(hiAccCtx1Cfg);

   /* clear the config structure first */
   HI_ZERO((U8 *)&cfg, sizeof(HiMngmt));

   /* prepare header */
   cfg.hdr.entId.ent   = ENTHI;
   cfg.hdr.entId.inst  = (TSTINST);
   cfg.hdr.elmId.elmnt = STCTX;
   cfg.hdr.transId     = HI_ACC_TRANSID;

#ifdef LCHIMILHI
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_LC);
#else
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_TC);
#endif

   cc = &cfg.t.cfg.s.hiCtx;
   cc->ctxId = 0;
   cc->caPath[0] = '\0';
   cmMemcpy((U8 *)cc->caFile,
            (CONSTANT U8 *)HI_ACC_TLSSERVER_CAFILE, 13);
   cmMemcpy((U8 *)cc->certFile,
            (CONSTANT U8 *)HI_ACC_TLSSERVER_CERTFILE, 11);
   cmMemcpy((U8 *)cc->privKeyFile,
            (CONSTANT U8 *)HI_ACC_TLSSERVER_PRIVKEYFILE, 11);
   cc->privKeyFileType = SSL_FILETYPE_PEM;
   cc->verifyMode = SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
   cmMemcpy((U8 *)cc->ciphers,
            (CONSTANT U8 *)"ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH", 34);
/* hi008.105 : To make verification depth configurable */
#ifdef HI_VERIFY_DEPTH  
   cc->verifyDepth  = 5;
#endif
/* hi008.105 : To make TLS method configurable */ 
#ifdef HI_TLS_METHOD
   cc->method       = HI_TLS_SSLV23_METHOD;
#endif   
   /* give configuration request to layer */
   (Void) SmMiLhiCfgReq(&hiAccCb.smPst, &cfg);

   RETVALUE(ROK);
}


/*
*
*       Fun:   hiAccCtx2Cfg 
*
*       Desc:  This function is used to configure a TLS/OpenSSL
*              context.
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
PUBLIC S16 hiAccCtx2Cfg 
(
Void
)
#else
PUBLIC S16 hiAccCtx2Cfg() 
#endif
{
   HiMngmt      cfg;
   HiCtxCfg     *cc;

   TRC2(hiAccCtx2Cfg);

   /* clear the config structure first */
   HI_ZERO((U8 *)&cfg, sizeof(HiMngmt));

   /* prepare header */
   cfg.hdr.entId.ent   = ENTHI;
   cfg.hdr.entId.inst  = (TSTINST);
   cfg.hdr.elmId.elmnt = STCTX;
   cfg.hdr.transId     = HI_ACC_TRANSID;

#ifdef LCHIMILHI
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_LC);
#else
   HI_ACC_SET_RESP(cfg.hdr.response, LHI_TC);
#endif

   cc = &cfg.t.cfg.s.hiCtx;
   cc->ctxId = 1;
   cc->caPath[0] = '\0';
   cmMemcpy((U8 *)cc->caFile,
            (CONSTANT U8 *)HI_ACC_TLSCLIENT_CAFILE, 13);
   cmMemcpy((U8 *)cc->certFile,
            (CONSTANT U8 *)HI_ACC_TLSCLIENT_CERTFILE, 11);
   cmMemcpy((U8 *)cc->privKeyFile,
            (CONSTANT U8 *)HI_ACC_TLSCLIENT_PRIVKEYFILE, 11);
   cc->privKeyFileType = SSL_FILETYPE_PEM;
   cc->verifyMode = SSL_VERIFY_PEER;
   cmMemcpy((U8 *)cc->ciphers,
            (CONSTANT U8 *)"ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH", 34);
/* hi008.105 : To make verification depth configurable */
#ifdef HI_VERIFY_DEPTH  
   cc->verifyDepth  = 6;
#endif
/* hi008.105 : To make TLS method configurable */ 
#ifdef HI_TLS_METHOD
   cc->method       = HI_TLS_SSLV3_METHOD;
#endif   
   /* give configuration request to layer */
   (Void) SmMiLhiCfgReq(&hiAccCb.smPst, &cfg);

   RETVALUE(ROK);
}
#endif  /* HI_TLS */


/*
*
*       Fun:   hiCntrlReq 
*
*       Desc:  This function is used to send Control Request to the
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
PUBLIC S16 hiAccCntrlReq 
(
SpId  spId,               /* service provider Id of HI SAP */
Elmnt  elmnt,             /* element id */
U8  action,               /* action */
U8  subAction,            /* sub action */
U32  param                /* debug mask */
)
#else
PUBLIC S16 hiAccCntrlReq(spId, elmnt, action, subAction, param) 
SpId  spId;               /* service provider Id of HI SAP */
Elmnt  elmnt;             /* element id */
U8  action;               /* action */
U8  subAction;            /* sub action */
U32  param;             /* debug mask */
#endif
{

   HiMngmt   ctl;
   TRC2(hiCntrlReq)

   /* clear the config structure first */
   HI_ZERO((U8 *) &ctl, sizeof(HiMngmt));

   /* prepare header */
   ctl.hdr.entId.ent   = ENTHI;           /* entity */
   ctl.hdr.entId.inst  = TSTINST;         /* instance */
   ctl.hdr.elmId.elmnt = elmnt;           /* element */

   if (action == ASHUTDOWN)
      ctl.hdr.transId  = HI_ACC_SHUTDOWN_TRANSID;
   else
      ctl.hdr.transId  = HI_ACC_TRANSID;

#ifdef LCHIMILHI
   HI_ACC_SET_RESP(ctl.hdr.response, LHI_LC);
#else
   HI_ACC_SET_RESP(ctl.hdr.response, LHI_TC);
#endif
   
   ctl.t.cntrl.action = action;
   ctl.t.cntrl.subAction = subAction;

#ifdef DEBUGP
   if (subAction == SADBG)
   {
      ctl.t.cntrl.ctlType.hiDbg.dbgMask = param;
   }
#endif

   /* parse the param appropriately */
   switch (elmnt)
   {
      case STTSAP:
         if(subAction == SAELMNT)
            ctl.t.cntrl.ctlType.sapId = spId;  /* sap id */
         if(subAction == SATRC)
         {
           ctl.t.cntrl.ctlType.trcDat.trcLen = (S16)param;
           ctl.t.cntrl.ctlType.trcDat.sapId = spId;
         }
         break;

      case STGRTSAP:
         if(subAction == SAGR_PRIORITY)
            ctl.t.cntrl.ctlType.priority = param;
         else if(subAction == SAGR_DSTPROCID)
            ctl.t.cntrl.ctlType.dstProcId = param;
         else if(subAction == SAGR_ROUTE)
            ctl.t.cntrl.ctlType.route = param;
         break;

      default:
         break;
   } /* end of switch */

   /* give Control request to layer */
   (Void) SmMiLhiCntrlReq(&hiAccCb.smPst, &ctl);

   RETVALUE(ROK);
}/* end of  hiAccCntrlReq()*/


/*
*
*       Fun:   hiAccStsReq 
*
*       Desc:  This function is used to send Statistics Request to the
*              TUCL.
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
PUBLIC S16 hiAccStsReq 
(
SpId  spId,               /* service provider Id of HI SAP */
Elmnt  elmnt              /* element id */
)
#else
PUBLIC S16 hiAccStsReq(spId, elmnt)
SpId  spId;               /* service provider Id of HI SAP */
Elmnt  elmnt;             /* element id */
#endif
{

   HiMngmt   sts;
   TRC2(hiCntrlReq)

   /* clear the config structure first */
   HI_ZERO((U8 *) &sts, sizeof(HiMngmt));

   /* Prepare header */

   sts.hdr.entId.ent   = ENTHI;      /* entity */
   sts.hdr.entId.inst  = TSTINST;    /* instance */
   sts.hdr.elmId.elmnt = elmnt;                 /* element */
   sts.hdr.transId     = HI_ACC_TRANSID;        /* transaction identifier */

#ifdef LCHIMILHI
   HI_ACC_SET_RESP(sts.hdr.response, LHI_LC);
#else
   HI_ACC_SET_RESP(sts.hdr.response, LHI_TC);
#endif

   switch (elmnt)
   {
      case STTSAP:
         sts.t.sts.s.sapSts.sapId = spId;
         break;

      default:
         break;
   } /* end of switch */

   /* give Control request to layer */
   (Void) SmMiLhiStsReq(&hiAccCb.smPst, (Action)NOZEROSTS, &sts);

   RETVALUE(ROK);
}/* end of  hiAccStsReq()*/


/*
*
*       Fun:   hiDispTstInfo
*
*       Desc:  Display information about the test case
*
*       Ret:   None
*
*       Notes: None
*
*       File:  hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC  S16 hiDispTstInfo
(
U16    tstId       /* Test Case Id */
)
#else
PUBLIC  S16 hiDispTstInfo(tstId)
U16    tstId;      /* Test Case Id */
#endif
{

   TRC2(hiDispTstInfo)
 
   switch(tstId)
   {
      case HI_TSTID_0:
       HIACCPRINT((hiAccCb.prntBuf,"\n *** TEST CASE #0 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf,"\nTO SETUP A TCP SERVER AND SEND DATA\n"));
       break;

      case HI_TSTID_1:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #1 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\nTO SETUP A TCP CLIENT AND SEND DATA\n"));
         break;

      case HI_TSTID_2:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #2 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\nTO SETUP A UDP SERVER AND SEND DATA\n"));
         break;

      case HI_TSTID_3:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #3 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\nTO TUCL UDP MCAST SERVER AND SEND DATA\n"));
         break;

      case HI_TSTID_4:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #4 *** \n"));
       break;

      case HI_TSTID_5:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #5 *** \n"));
       break;

      case HI_TSTID_6:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #6 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n UDP TPKT Header processing test. \n"));
       break;

      case HI_TSTID_7:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #7 *** \n"));
       break;

      case HI_TSTID_8:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #8 *** \n"));
       break;
#ifdef IPV6_SUPPORTED      
      case HI_TSTID_9:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #9 *** \n"));
       break;

      case HI_TSTID_10:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #10 *** \n"));
       break;

      case HI_TSTID_11:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #11 *** \n"));
       break;
       
#if (defined(IPV6_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))
      case HI_TSTID_12:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #12 *** \n"));
       break;

      case HI_TSTID_13:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #13 *** \n"));
       break;
#endif /* IPV6_OPTS_SUPPORTED */       
#endif /* IPV6_SUPPORTED */
#ifdef HI_RUG
      case HI_TSTID_14:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #14 *** \n"));
       break;
       
      case HI_TSTID_15:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #15 *** \n"));
       break;

      case HI_TSTID_16:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #16 *** \n"));
       break;       

      case HI_TSTID_17:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #17 *** \n"));
       break;       
#endif /* HI_RUG */

#ifdef HI_TLS
      case HI_TSTID_18:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #18 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n TLS server test. \n"));
       break;       
#endif  /* HI_TLS */

#ifdef HI_TLS
      case HI_TSTID_19:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #19 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n TLS client test. \n"));
       break;       
#endif  /* HI_TLS */
       /* hi002.105 (hi029.104) - added new test case */
      case HI_TSTID_20:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #20 *** \n"));
       break;       

#ifdef HI_CONG_CHECK_TMR
      case HI_TSTID_45:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #45 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n TIMER BASED RESOURCE CHECKING \n"));
       break;       
#endif /*HI_CONJ_CHECK_TMR*/

#ifdef HI_LKSCTP
      case HI_TSTID_50:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #50 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n IPV6 + IPV4 test \n"));
       break;

      case HI_TSTID_51:
       HIACCPRINT((hiAccCb.prntBuf, "\n\t *** TEST CASE #51 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n\tIPV6 Set Primary Address  \n"));
       break;
      case HI_TSTID_52:
       HIACCPRINT((hiAccCb.prntBuf, "\n\t *** TEST CASE #52 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n\t IPV6 Hbeat   \n"));
       break;
      case HI_TSTID_53:
       HIACCPRINT((hiAccCb.prntBuf, "\n\t *** TEST CASE #53 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n\t IPV6 Sta req test   \n"));
       break;

      case HI_TSTID_54:
       HIACCPRINT((hiAccCb.prntBuf, "\n\t *** TEST CASE #54 *** \n"));
       HIACCPRINT((hiAccCb.prntBuf, "\n\t IPV6 Sta req test   \n"));
       break;

      case HI_TSTID_55:
       /* hi028.201: Added new test cases HI_TSTID_55 */
       HIACCPRINT((hiAccCb.prntBuf, "\n\t *** TEST CASE #55 *** \n"));
       break;

#ifndef CM_LKSCTP_NONBLOCK
      case HI_TSTID_56:
       /* hi028.201: Added new test cases HI_TSTID_56 */
       HIACCPRINT((hiAccCb.prntBuf, "\n\t *** TEST CASE #56 *** \n"));
       break;
#endif

#endif /* HI_LKSCTP */
       
   /* hi028.201: Added new test cases hiAccTst57*/
#ifdef HI_ACC_GEN_RECONFIG
      case HI_TSTID_57:
       HIACCPRINT((hiAccCb.prntBuf, "\n *** TEST CASE #57 *** \n"));
       break;
#endif
      default:
       HIACCPRINT((hiAccCb.prntBuf, "\n\t *** TEST CASE # %d  *** \n",tstId ));
   }

   RETVALUE(ROK);
}  /* End of hiDispTstInfo */


/*
*
*       Fun:   hiAccChkMsg
*
*       Desc:  This function is used to compare two messages
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
PUBLIC S16 hiAccChkMsg
(
Buffer *msg1,
Buffer *msg2
)
#else
PUBLIC S16 hiAccChkMsg(msg1, msg2)
Buffer *msg1;
Buffer *msg2;
#endif
{

   MsgLen len1;
   MsgLen len2;
   MsgLen i; 
   U8     byte1;
   U8     byte2;
   Txt    prntBuf[HIACC_PRNTBUF_SIZE]; /* Buffer to print */
   
   TRC2(hiAccChkMsg)

      
   byte1 = 0;
   byte2 = 0;

   /* check message length */
   if (SFndLenMsg(msg1, &len1) != ROK)
   {
      sprintf(prntBuf, "Invalid message length message 1 \n");
      SPrint(prntBuf);
      RETVALUE(RFAILED);
   }
   if (SFndLenMsg(msg2, &len2) != ROK)
   {
      sprintf(prntBuf, "Invalid message length message 2 \n");
      SPrint(prntBuf);
      RETVALUE(RFAILED);
   }
   if (len1 != len2)
   {
      sprintf(prntBuf, "message lengths not equal len1 = %d and len2 = %d \n", 
              len1, len2);
      SPrint(prntBuf);
      RETVALUE(RFAILED);
   }

   /* check data */
   for (i = 0; i < len1; i++)
   {
      if (SExamMsg(&byte1, msg1, i) != ROK)
      {
         sprintf(prntBuf, "hiAccChksg - SExambyte msg failed \n");
         SPrint(prntBuf);
         RETVALUE(RFAILED);
      }
      if (SExamMsg(&byte2, msg2, i) != ROK)
      {
         sprintf(prntBuf, "hiAccChksg - SExambyte msg2 failed \n");
         SPrint(prntBuf);
         RETVALUE(RFAILED);
      }
      if (byte1 != byte2)
      {
         sprintf(prntBuf, "hiAccChksg - byte1 != byte2 \n");
         SPrint(prntBuf);
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ROK);
}/* end of hiAccChkMsg()*/

/* Support functions used by the Layer Manager */
#ifdef HI_ACC

/*
*
*       Fun:   hiAccProcCfgCfm
*
*       Desc:  This function is called in the sample stack manager to
*              process HiMiLhiCfgCfm primitive received from TUCL
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccProcCfgCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 hiAccProcCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
#endif
{
   /* hi002.105 (hi029.104) - Used to prevent the call to HcLiHitBndReq for all other saps
    * except the fisrt sap. As we don't know the spId here, we need
    * static */
   static int i = 0;
   
   Txt   prntBuf[HIACC_PRNTBUF_SIZE];   /* Buffer to print */

   TRC2(hiAccProcCfgCfm)

   UNUSED(pst);

   SPrint("\n\t************* Configuration Confirm Received *************\n");
   /* print the information */
   sprintf(prntBuf, "\telmnt     = %d", cfm->hdr.elmId.elmnt);
   SPrint(prntBuf);
   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   sprintf(prntBuf, "\ttransId   = %ld\n", cfm->hdr.transId);
#else
   sprintf(prntBuf, "\ttransId   = %d\n", cfm->hdr.transId);
#endif
   SPrint(prntBuf);
   if (cfm->cfm.status != LCM_PRIM_OK)
   {
      sprintf(prntBuf,"\tConfiguration Failed. Reason %d\n", cfm->cfm.reason);
      SPrint(prntBuf);
   }
   else
   {
      if(cfm->hdr.elmId.elmnt == STTSAP)
      {
         i++;
         SPrint("\tSAP Configuration Successful.\n");
         SPrint("\t-----SAP Configuration Confirm Information -----\n");
      }
      else if(cfm->hdr.elmId.elmnt == STGEN)
      {   
         SPrint("\tGeneral Configuration Successful.\n");
         SPrint("\t----- General Configuration Confirm Information -----\n");
      }
      
      /* Issue a Bind request only after getting the config confirm for
       * TSAP */
      /* hi002.105 (hi029.104) - added.  Issue Bind Req only for first sap */
      if(cfm->hdr.elmId.elmnt == STTSAP && i == 1)

         HcLiHitBndReq(&hiAccCb.uiPst, (SuId)HI_ACC_SAP_0, 
                       (SpId)HI_ACC_SAP_0); 
#ifdef HI_LKSCTP_USER_CONFIG
      else if(cfm->hdr.elmId.elmnt == STTSAP && i > 1  && hiAccCb.curTst.id == HI_TSTID_44 && hiAccCb.curTst.state == 14)
         hiAccCb.curTst.state++;
#endif
   }
   
   RETVALUE(ROK);
}/* end of hiAccProcCfgCfm() */


/*
*
*       Fun:   hiAccProcCntrlCfm
*
*       Desc:  This function is called in the sample stack manager to
*              process HiMiLhiCntrlCfm primitive received from TUCL
*
*       Ret:   ROK
*
*       Notes: None 
*
*       File:  hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccProcCntrlCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* control */
)
#else
PUBLIC S16 hiAccProcCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* control */
#endif
{

   Txt   prntBuf[HIACC_PRNTBUF_SIZE];   /* Buffer to print */

   TRC2(hiAccProcCntrlCfm)

   UNUSED(pst);

   SPrint("\n\tControl Confirm Received \n");
   /* print the information */
   SPrint("\t----- Control Confirm Information -----\n");
   sprintf(prntBuf, "\telmnt     = %d", cfm->hdr.elmId.elmnt);
   SPrint(prntBuf);
   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   sprintf(prntBuf, "\ttransId   = %ld\n", cfm->hdr.transId);
#else
   sprintf(prntBuf, "\ttransId   = %d\n", cfm->hdr.transId);
#endif
   SPrint(prntBuf);
   if (cfm->cfm.status == LCM_PRIM_NOK)
   {
      sprintf(prntBuf, "\tControl Primitive Failed. Reason %d\n", 
              cfm->cfm.reason);
      SPrint(prntBuf);
   }
#ifdef HI_MULTI_THREADED
   else if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
   {
      SPrint("\tControl Request Successful. Operation in progress \n");
      SPrint("\t----- Control Confirm Information -----\n");
   }
#endif /* HI_MULTI_THREADED */
   else
   {
      SPrint("\tControl Primitive Successful.\n");
   }
 
   SPrint("\t----- Control Confirm Information -----\n");

#ifdef HI_RUG
   if (hiAccCb.curTst.id == HI_TSTID_17)
     hiAccCb.curTst.state++;
#endif /* HI_RUG */

/* hi023.201: Control confirm for enabling trace indication */
#ifdef HI_LKSCTP
   if (hiAccCb.curTst.id == HI_TSTID_48 && cfm->hdr.elmId.elmnt == STTSAP)
   {
      hiAccCb.curTst.state++;
   }

   if (hiAccCb.curTst.id == HI_TSTID_49 && cfm->hdr.elmId.elmnt == STTSAP)
   {
      hiAccCb.curTst.state++;
   }
   if (hiAccCb.curTst.id == HI_TSTID_50 && cfm->hdr.elmId.elmnt == STTSAP)
   {
      hiAccCb.curTst.state++;
   }
#endif

#ifdef HI_LKSCTP
   if (cfm->cfm.status == LCM_PRIM_OK
       && cfm->hdr.transId == HI_ACC_SHUTDOWN_TRANSID
       && hiAccCb.curTst.id >= HI_TSTID_21)
      hiAccCb.curTst.state++;
#endif

#ifndef HI_LKSCTP 
#if (!defined(HI_TEST_FOREVER))
   if (cfm->cfm.status == LCM_PRIM_OK
       &&  cfm->hdr.transId == HI_ACC_SHUTDOWN_TRANSID)
      exit(0);
#endif 
#endif

   RETVALUE(ROK);
}/* end of hiAccProcCntrlCfm() */


/*
*
*       Fun:   hiAccProcStaInd
*
*       Desc:  This function is called in the sample stack manager to
*              process HiMiLhiStaInd primitive received from TUCL
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccProcStaInd
(
Pst     *pst,           /* post structure */
HiMngmt *usta           /* unsolicited status */
)
#else
PUBLIC S16 hiAccProcStaInd(pst, usta)
Pst     *pst;           /* post structure */
HiMngmt *usta;          /* unsolicited status */
#endif
{

   Txt          prntBuf[HIACC_PRNTBUF_SIZE];   /* Buffer to print */
   DateTime     *dt;                      /* date and time when alarm rxd */
   CmAlarm      *alm;                     /* alarm */
   HiAlarmInfo  *info;                    /* status information */

   TRC2(hiAccProcStaInd)

   UNUSED(pst);

   SPrint("\n\tUnsolicited Status Indication Received \n");
   alm  = &usta->t.usta.alarm;

   /* print the date and time */
   dt   = &alm->dt;

   SPrint("\t");
   HIACCPRNTDT(dt);
  
   sprintf(prntBuf, "\tCategory = %d, Event = %d, Cause = %d\n",
           alm->category, alm->event, alm->cause);
   SPrint(prntBuf);

   /* print the unsolicited status */
   info = &usta->t.usta.info;
   SPrint("\t----- Unsolicited Status Information -----\n");
   sprintf(prntBuf, "\tsapId     = %d\n", info->spId);
   SPrint(prntBuf);
   sprintf(prntBuf, "\ttype      = %d\n", info->type);
   SPrint(prntBuf);

   if(info->type == LHI_ALARMINFO_TYPE_NTPRSNT)
   {
      sprintf(prntBuf, "\tNO Further info available\n");
      SPrint(prntBuf);
   }   
   else if(info->type == LHI_ALARMINFO_SAP_STATE)
   {
      sprintf(prntBuf, "\tstate     = %d\n", info->inf.state);
      SPrint(prntBuf);
   }
   else if(info->type == LHI_ALARMINFO_CON_STATE)
   {
      sprintf(prntBuf, "\tconState  = %d\n", info->inf.conState);
      SPrint(prntBuf);
   }
   else if(info->type == LHI_ALARMINFO_MEM_ID)
   {
      sprintf(prntBuf, "\tregion    = %d\n", info->inf.mem.region);
      SPrint(prntBuf);
      sprintf(prntBuf, "\tpool      = %d\n", info->inf.mem.pool);
      SPrint(prntBuf);
   }
   else if (info->type == LHI_ALARMINFO_PAR_TYPE)
   {
      /* Verify the interface version info on the alarm recvd from
       * TUCL and also check the version number TUCL used to send
       * these alarms to LM */
#ifdef HI_RUG
      if(hiCb.init.lmPst.intfVer != LHIIFVER)
         SPrint("\tTUCL has used wrong intf ver num in the alarms to LM!\n");
      else
         SPrint("\tTUCL has used correct intf ver num in the alarms to LM!\n");
#else      
      sprintf(prntBuf, "\tregion    = %d\n", info->inf.parType);
#endif /* HI_RUG */
      SPrint(prntBuf);
      
   }
#ifdef HI_TLS
   else if (info->type == LHI_ALARMINFO_OSSL_ERR)
   {
      sprintf(prntBuf, "\terror     = %ld\n", info->inf.osslError);
      SPrint(prntBuf);
   }
#endif
   else
   {
      sprintf(prntBuf, "UNKNOWN INFO\n");
      SPrint(prntBuf);
   }

   SPrint("\t----- Unsolicited Status Information -----\n");
#ifdef HI_CONG_CHECK_TMR
   /*hi005.201 *Added hiAccTst45 test case to check 
	            *resource based conjestion timer */
	/* In case of conjestion depending upon the alarm 
	 *event the status of the variable hiAccCb.conjestionStatus
	 * will be changed and will be reflected in test case 
	 * hiAccTst45*/ 
	if ( 271 == (alm->event) )
	{
		hiAccCb.conjestionStatus = CONJESTION_START;
		sprintf (prntBuf, "conjestion start\n");
      SPrint(prntBuf);
	}
	if ( 272 == (alm->event) )
	{
	   hiAccCb.conjestionStatus = CONJESTION_DROP;
		sprintf (prntBuf, "conjestion drop\n");
      SPrint(prntBuf);
	}
	if ( 273 == (alm->event) )
	{
		hiAccCb.conjestionStatus = NO_CONJESTION;
		sprintf (prntBuf, "conjestion stop\n");
      SPrint(prntBuf);
	}
#endif /*HI_CONG_CHECK_TMR*/
   RETVALUE(ROK);
}/* end of hiAccProcStaInd() */


/*
*
*       Fun:   hiAccProcTrcInd
*
*       Desc:  This function is called in the sample stack manager to
*              process HiMiLhiTrcInd primitive received from TUCL
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
PUBLIC S16 hiAccProcTrcInd
(
Pst *pst,               /* post structure */
HiMngmt *trc,           /* trace */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 hiAccProcTrcInd(pst, trc, mBuf)
Pst *pst;               /* post structure */
HiMngmt *trc;           /* trace */
Buffer *mBuf;           /* message buffer */
#endif
{

   Txt         prntBuf[HIACC_PRNTBUF_SIZE];  /* buffer to print */
   DateTime    *dt;  /* date and time */

   TRC2(hiAccProcTrcInd)

   UNUSED(pst);

   dt  = &trc->t.trc.dt;
   HIACCPRNTDT(dt);

   SPrint("\n----- Trace Indication -----\n");
   sprintf(prntBuf, "Trace Indication: Event = %d\n",trc->t.trc.evnt);
   SPrint(prntBuf);
   
   /* hi002.105 (hi023.104)Sap Id in Trace Information */
#ifdef HI_ENB_SAP_TRC
   sprintf(prntBuf, "Trace Indication: Sap = %d\n",trc->t.trc.sap);
   SPrint(prntBuf);
#endif

   if (trc->t.trc.evnt == LHI_TCP_TXED)
   {
      SPrint("\t----- TCP Data Transmitted -----\n");
   }
   else if (trc->t.trc.evnt == LHI_UDP_TXED)
   {
      SPrint("\t----- UDP Data Transmitted -----\n");
   }
   else if (trc->t.trc.evnt == LHI_TCP_RXED)
   {
      SPrint("\t----- TCP Data Received --------\n");
   }
   else if (trc->t.trc.evnt == LHI_UDP_RXED)
   {
      SPrint("\t----- UDP Data Received --------\n");
   }
   /* hi023.201: Trace Indication for KSCTP messages */
#ifdef HI_LKSCTP
   else if (trc->t.trc.evnt == LHI_KSCTP_TXED)
   {
      SPrint("\t----- KSCTP Data Transmitted --------\n");
   }
   else if (trc->t.trc.evnt == LHI_KSCTP_RXED)
   {
      SPrint("\t----- KSCTP Data Received --------\n");
   }
#endif
   else
   {
      SPrint("\t----- NULL Data -----\n");
   }

   /* hi023.201: Increment state for trace indication of KSCTP messages */
   hiAccCb.curTst.state++;

   SPrntMsg(mBuf, 0, 0);
   (Void)SPutMsg(mBuf);

   RETVALUE(ROK);
}/* end of hiAccProcTrcInd() */


/*
*
*       Fun:   hiAccProcStsCfm
*
*       Desc:  This function is called in the sample stack manager to
*              process HiMiLhiStsCfm primitive received from TUCL
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
PUBLIC S16 hiAccProcStsCfm
(
Pst       *pst,         /* post structure */
HiMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 hiAccProcStsCfm(pst, sts)
Pst       *pst;         /* post structure */
HiMngmt   *sts;         /* confirmed statistics */
#endif
{

   Txt        prntBuf[PRNTSZE];      /* print buffer */
   DateTime   *dt;                   /* date and time when status is rxd */
   Duration   *dura;                 /* duration */

   TRC2(hiAccProcStsCfm)

   UNUSED(pst);
  
   dt   = &sts->t.sts.dt;
   HIACCPRNTDT(dt);
  
   dura = &sts->t.sts.dura;
   HIACCPRNTDURATION(dura);

   if (sts->cfm.status != LCM_PRIM_OK)
   {
      sprintf(prntBuf, "Failed to get statistics info:( Reason %d )\n", 
              sts->cfm.reason);
      SPrint(prntBuf);

      RETVALUE(RFAILED);
   }

   SPrint("\n----- Statistics Confirm -----\n");

   switch (sts->hdr.elmId.elmnt)
   {
      case STGEN:
      {
         HiGenSts       *gen;          /* General statistics */

   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
         SPrint("----- General statistics -----\n");
         gen = &sts->t.sts.s.genSts;
         sprintf(prntBuf, "numCons             =  %ld\n", gen->numCons);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockTxErr           =  %ld\n", gen->sockTxErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockRxErr           =  %ld\n", gen->sockRxErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockOpenErr         =  %ld\n", gen->sockOpenErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockBindErr         =  %ld\n", gen->sockBindErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockCnctErr         =  %ld\n", gen->sockCnctErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockLstnErr         =  %ld\n", gen->sockLstnErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockSOptErr         =  %ld\n", gen->sockSOptErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockClosErr         =  %ld\n", gen->sockClosErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockShutErr         =  %ld\n", gen->sockShutErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockrxMsgVerErr     =  %ld\n", gen->rxMsgVerErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "numFlcInd           =  %ld\n", gen->numFlcInd);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxTcpMsg         =  %ld\n", gen->numTxTcpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxTcpMsg         =  %ld\n", gen->numRxTcpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxUdpMsg         =  %ld\n", gen->numTxUdpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxUdpMsg         =  %ld\n", gen->numRxUdpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxbytes          =  %ld\n", gen->numTxbytes);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxbytes          =  %ld\n", gen->numRxbytes);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxRawMsg         =  %ld\n", gen->numTxRawMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxRawMsg         =  %ld\n", gen->numRxRawMsg);
         SPrint(prntBuf);
         SPrint("----- End of General statistics -----\n");
#else

         SPrint("----- General statistics -----\n");
         gen = &sts->t.sts.s.genSts;
         sprintf(prntBuf, "numCons             =  %d\n", gen->numCons);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockTxErr           =  %d\n", gen->sockTxErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockRxErr           =  %d\n", gen->sockRxErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockOpenErr         =  %d\n", gen->sockOpenErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockBindErr         =  %d\n", gen->sockBindErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockCnctErr         =  %d\n", gen->sockCnctErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockLstnErr         =  %d\n", gen->sockLstnErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockSOptErr         =  %d\n", gen->sockSOptErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockClosErr         =  %d\n", gen->sockClosErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockShutErr         =  %d\n", gen->sockShutErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "sockrxMsgVerErr     =  %d\n", gen->rxMsgVerErr);
         SPrint(prntBuf);
         sprintf(prntBuf, "numFlcInd           =  %d\n", gen->numFlcInd);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxTcpMsg         =  %d\n", gen->numTxTcpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxTcpMsg         =  %d\n", gen->numRxTcpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxUdpMsg         =  %d\n", gen->numTxUdpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxUdpMsg         =  %d\n", gen->numRxUdpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxbytes          =  %d\n", gen->numTxbytes);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxbytes          =  %d\n", gen->numRxbytes);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxRawMsg         =  %d\n", gen->numTxRawMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxRawMsg         =  %d\n", gen->numRxRawMsg);
         SPrint(prntBuf);
         SPrint("----- End of General statistics -----\n");
#endif
         break;
      }
 
      case STTSAP:
      {
         HiSapSts      *sap;         /* transport SAP statistics */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
         SPrint("----- TRANSPORT SAP statistics -----\n");
         sap = &sts->t.sts.s.sapSts;
         /* hi028.201 :Printing all the statistics collected at TUCL layer*/ 
         sprintf(prntBuf, "numCons             =  %ld\n", sap->numCons);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxTcpMsg         =  %ld\n", sap->numTxTcpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxTcpMsg         =  %ld\n", sap->numRxTcpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxUdpMsg         =  %ld\n", sap->numTxUdpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxUdpMsg         =  %ld\n", sap->numRxUdpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxbytes          =  %ld\n", sap->numTxbytes);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxbytes          =  %ld\n", sap->numRxbytes);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxRawMsg         =  %ld\n", sap->numTxRawMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxRawMsg         =  %ld\n", sap->numRxRawMsg);
         SPrint(prntBuf);
         SPrint("----- TRANSPORT SAP statistics -----\n");
#else

         SPrint("----- TRANSPORT SAP statistics -----\n");
         sap = &sts->t.sts.s.sapSts;
         /* hi028.201 :Printing all the statistics collected at TUCL layer*/ 
         sprintf(prntBuf, "numCons             =  %d\n", sap->numCons);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxTcpMsg         =  %d\n", sap->numTxTcpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxTcpMsg         =  %d\n", sap->numRxTcpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxUdpMsg         =  %d\n", sap->numTxUdpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxUdpMsg         =  %d\n", sap->numRxUdpMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxbytes          =  %d\n", sap->numTxbytes);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxbytes          =  %d\n", sap->numRxbytes);
         SPrint(prntBuf);
         sprintf(prntBuf, "numTxRawMsg         =  %d\n", sap->numTxRawMsg);
         SPrint(prntBuf);
         sprintf(prntBuf, "numRxRawMsg         =  %d\n", sap->numRxRawMsg);
         SPrint(prntBuf);
         SPrint("----- TRANSPORT SAP statistics -----\n");
#endif
         break;
      }
/* hi014.105 1. Modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
      case STHITHR:
      {
         HiThrSts      *thrSts;         /* Thread conneciton statistics */
         U32 iCount, jCount;
         SPrint("----- Thread connection statistics -----\n");
         thrSts = &sts->t.sts.s.thrSts;
         sprintf(prntBuf, "Num of Receive threads =  %ld\n", thrSts->numRcvThrds);
         SPrint(prntBuf);

         for(iCount = 0; iCount < thrSts->numRcvThrds; iCount++)
         {
            sprintf(prntBuf, "Num of Connections in thread (%ld) = %ld \n",
                          (iCount+1), thrSts->thrConSts[iCount].numCons);
            SPrint(prntBuf);
            
            for(jCount = 0; jCount < thrSts->thrConSts[iCount].numCons; jCount++)
            {
              sprintf(prntBuf, "Msg received on connection (%ld) in bytes = %ld\n",(jCount+1),
                             thrSts->thrConSts[iCount].conSts[jCount].numRxBytes ); 
              SPrint(prntBuf);
              sprintf(prntBuf, "Msg transmitted on connection (%ld) in bytes = %ld\n",(jCount+1),
                             thrSts->thrConSts[iCount].conSts[jCount].numTxBytes ); 
              SPrint(prntBuf);

            } 
      
            SPutSBuf(pst->region, pst->pool, (Data* )thrSts->thrConSts[iCount].conSts,
                    (Size)(sizeof(HiConSts) * thrSts->thrConSts[iCount].numCons));
            thrSts->thrConSts[iCount].conSts = NULLP;
 
         }
      
         SPutSBuf(pst->region, pst->pool, (Data* )thrSts->thrConSts,
                       (Size)(sizeof(HiThrConSts) * thrSts->numRcvThrds));
         thrSts->thrConSts = NULLP;

         break;
      }
#endif /*LHI_THR_STS*/
 
      default:
      SPrint("Unknown statistics\n");
      break;
   } /* end of switch */

   /* hi028.201: Incrementing test case step to next*/ 
   hiAccCb.curTst.state++;

   RETVALUE(ROK);
}/* end of hiAccProcStsCfm() */


/*
*
*       Fun:   hiAccProcStaCfm
*
*       Desc:  This function is called in the sample stack manager to
*              process HiMiLhiStaCfm primitive received from TUCL
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
PUBLIC S16 hiAccProcStaCfm
(
Pst     *pst,           /* post structure */
HiMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 hiAccProcStaCfm(pst, sta)
Pst     *pst;           /* post structure */
HiMngmt *sta;            /* confirmed status */
#endif
{

   Txt        prntBuf[32];   /* Buffer to print */
   DateTime   *dt;           /* date and time when status is rxd */
#ifdef HI_RUG
   U8         i = 0;
#endif /* HI_RUG */   

   TRC2(hiAccProcStaCfm)

   UNUSED(pst);

   SPrint("\n\t----- Status Confirm -----\n");
   dt = &sta->t.ssta.dt;

   SPrint("\t");
   HIACCPRNTDT(dt);
   switch (sta->hdr.elmId.elmnt)
   {
      case STSID:
      {
         SystemId *n = &sta->t.ssta.s.sysId;
 
         SPrint("----- SYSTEM ID Status ----- \n");
         sprintf(prntBuf, "mVer %d\n", n->mVer);
         SPrint(prntBuf);
         sprintf(prntBuf, "mRev %d\n", n->mRev);
         SPrint(prntBuf);
         sprintf(prntBuf, "bVer %d\n", n->bVer);
         SPrint(prntBuf);
         sprintf(prntBuf, "bRev %d\n", n->bRev);
         SPrint(prntBuf);
         sprintf(prntBuf, "ptNmb %s\n", n->ptNmb);
         SPrint(prntBuf);
         SPrint("----- SYSTEM ID Status ----- \n");
         RETVALUE(ROK);
      }

      case STTSAP:
      {
         HiSapSta *status = &sta->t.ssta.s.sapSta;
 
         SPrint(" \t---- Transport Sap Status ----- \n");
         sprintf(prntBuf, "\tspId %d\n", status->spId);
         SPrint(prntBuf);
         switch(status->state)
         {
            case HI_ST_UBND:
               SPrint("\tTSAP State is CONFIGURED\n");

#ifdef HI_RUG
               SPrint("\tVerifying Version Info on this SAP .....\n");
               if (sta->t.ssta.s.sapSta.remIntfValid != TRUE)
               {
                  SPrint("\tRemote interface version NOT valid!\n");
                  i++;
               }
               if (sta->t.ssta.s.sapSta.selfIfVer != HITIFVER)
               {                  
                  SPrint("\tInvalid Self Interface version number present!\n");
                  i++;
               }
               if (sta->t.ssta.s.sapSta.remIfVer != HITIFVER)
               {
                  SPrint("\tInvalid Remote Interface version number present!\n");
                  i++;
               }
               if(i == 0)
                  SPrint("\tAll Version Info stored on this SAP is OK!\n");
#endif /* HI_RUG */               
               break;

            case HI_ST_BND:
               SPrint("TSAP State is BOUND and ENABLED\n");
               break;

            default:
               SPrint("TSAP State is INVALID\n");
               break;
         } /* end of switch */

         SPrint("\t---- Transport Sap Status ----- \n");
         break;
      }
   }

   RETVALUE(ROK);
}/* end of hiAccProcStaCfm() */

#endif /* HI_ACC */


#ifdef HI_RUG
/*
 *
 *      Fun:   hiAccSendShCntrl
 *
 *      Desc:  This function sends a System agent control request
 *
 *      Ret:   RETVOID  - successful,
 *
 *      Notes: None.
 *
        File:  hi_acc1.c
 *
 */

#ifdef ANSI
PUBLIC Void hiAccSendShCntrl
(
U8 reqType,           /* request type */
U8 grpType,           /* group type */
ProcId procId,        /* procId */
Ent ent,              /* entity id */
Inst inst,            /* instance id */
CmIntfId intfId,      /* interface id */
CmIntfVer intfVer    /* interface version */
)
#else
PUBLIC Void hiAccSendShCntrl(reqType, grpType, procId, ent, inst, 
                             intfId, intfVer)
U8 reqType;           /* request type */
U8 grpType;           /* group type */
ProcId procId;        /* procId */
Ent ent;              /* entity id */
Inst inst;            /* instance id */
CmIntfId intfId;      /* interface id */
CmIntfVer intfVer;    /* interface version */
#endif
{
   Pst pst;
   ShtCntrlReqEvnt cntrl;

   TRC2(hiAccSendShCntrl)

   cntrl.hdr.transId = HI_ACC_TRANSID;   
   cntrl.hdr.response.selector = 0;
   cntrl.hdr.response.prior = 0;
   cntrl.hdr.response.route = 0;
   cntrl.hdr.response.mem.region = 0;
   cntrl.hdr.response.mem.pool = 0;

   cntrl.reqType = reqType;
      
   switch (reqType)
   {
      case SHT_REQTYPE_BND_ENA:
         cntrl.s.bndEna.grpType = grpType;
         cntrl.s.bndEna.dstProcId = procId;
         cntrl.s.bndEna.dstEnt.ent = ent;
         cntrl.s.bndEna.dstEnt.inst = inst;
         break;
      case SHT_REQTYPE_UBND_DIS:
         cntrl.s.ubndDis.grpType = grpType;
         cntrl.s.ubndDis.dstProcId = procId;
         cntrl.s.ubndDis.dstEnt.ent = ent;
         cntrl.s.ubndDis.dstEnt.inst = inst;
         break;
      case SHT_REQTYPE_GETVER:
         break;
      case SHT_REQTYPE_SETVER:
         cntrl.s.svReq.grpType = grpType;
         cntrl.s.svReq.dstProcId = procId;
         cntrl.s.svReq.dstEnt.ent = ent;
         cntrl.s.svReq.dstEnt.inst = inst;
         cntrl.s.svReq.intf.intfId = intfId;
         cntrl.s.svReq.intf.intfVer = intfVer;
         break;
   }

   /* fill up the pst structure */
   pst.selector = 0;               /* always */
   
   pst.region = TSTREG;            /* region */
   pst.pool = TSTPOOL;             /* pool */
   pst.prior = 0;                  /* priority */
   pst.route = 0;                  /* route */

   pst.dstProcId = SFndProcId();   /* destination processor id */
   pst.srcProcId = SFndProcId();   /* source processor id */
   
   pst.srcEnt = ENTSH;             /* source entity */
   pst.srcInst = TSTINST;          /* src instance (unused) */   

   pst.dstEnt = ENTHI;             /* dst entity   (always ENTSP) */
   pst.dstInst = TSTINST;          /* dst instance (unused) */
   
   pst.event = EVTSHTCNTRLREQ;     /* set event type in pst */
   
   cmPkMiShtCntrlReq(&pst, &cntrl);

   RETVOID;
   
} /* end of hiAccSendShCntrl */
#endif /* HI_RUG */


#ifdef HI_TLS

/*
*
*       Fun:    hiOSSLPasswdCb
*
*       Desc:   Called from OpenSSL to provide a password to
*               decrypt the private key file. Must be implemented
*               by the customer.
*
*       Ret:    password length - ok
*
*       Notes:  None
*
*       File:   hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC int hiOSSLPasswdCb
(
char            *buf,           /* buffer for password */
int             size,           /* available buffer size */
int             rwflag,         /* reading or writing */
Void            *userdata       /* specified at time of cb registration */
)
#else
PUBLIC int hiOSSLPasswdCb(buf, size, rwflag, userdata)
char            *buf;           /* buffer for password */
int             size;           /* available buffer size */
int             rwflag;         /* reading or writing */
Void            *userdata;      /* specified at time of cb registration */
#endif
{
   TRC2(hiOSSLPasswdCb);

   cmMemcpy((U8 *)buf, (CONSTANT U8 *)"yabbadabbadoo", 14);

   return 13;
}


/*
*
*       Fun:    hiOSSLPostConCheck
*
*       Desc:   Called from TUCL to perform TLS post connection
*               verification. Typically ensures that the peer's
*               FQDN is present in the certificate it provides.
*               Must be implemented by the customer.
*
*       Ret:    X509_V_OK                               - ok
*               X509_V_ERR_APPLICATION_VERIFICATION     - failed
*
*       Notes:  None
*
*       File:   hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC long hiOSSLPostConCheck
(
SSL             *ssl,           /* TLS connection */
CmTptAddr       *peerAddr       /* peer's address */
)
#else
PUBLIC long hiOSSLPostConCheck(ssl, peerAddr)
SSL             *ssl;           /* TLS connection */
CmTptAddr       *peerAddr;      /* peer's address */
#endif
{
   TRC2(hiOSSLPostConCheck);


   return X509_V_OK;
}


/*
*
*       Fun:   hiAccTLSPasswd
*
*       Desc:  This function is called from the OpenSSL library to
*              retrieve the password needed to decrypt the private
*              key file.
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
PUBLIC int hiAccTLSPasswd
(
char *buf,                      /* buffer for password */
int size,                       /* available buffer size */
int rwflag,                     /* reading or writing */
Void *userdata                  /* specified at time of cb registration */
)
#else
PUBLIC int hiAccTLSPasswd(buf, size, rwflag, userdata)
char *buf;                      /* buffer for password */
int size;                       /* available buffer size */
int rwflag;                     /* reading or writing */
Void *userdata;                 /* specified at time of cb registration */
#endif
{
   TRC2(hiAccTLSPasswd);

   cmMemcpy((U8 *)buf, (CONSTANT U8 *)"yabbadabbadoo", 14);

   return 13;
}
/* hi008.105 : Added more SSL callback function */
#ifdef HI_TLS_EXT_CALLBACK
/*
*
*       Fun:    hiOSSLGetInfo
*
*       Desc:   Called from the OpenSSL library 
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   tl_acc1.c
*
*/
#ifdef ANSI
PUBLIC Void hiOSSLGetInfo
(
CONSTANT SSL  *ssl, 
int        where, 
int        ret
)
#else 
PUBLIC Void hiOSSLGetInfo(ssl, where, ret)
CONSTANT SSL  *ssl;
int        where;
int        ret;
#endif /* ANSI */
{

   CONSTANT char *str;
   int w;
   Txt   prntBuf[HIACC_PRNTBUF_SIZE];
   
   TRC2(hiOSSLGetInfo)
   
   w=where& ~SSL_ST_MASK;

   if (w & SSL_ST_CONNECT) str="SSL_connect";
   else if (w & SSL_ST_ACCEPT) str="SSL_accept";
   else str="undefined";

   if (where & SSL_CB_LOOP)
   {
      sprintf(prntBuf,"%s:%s\n",str,SSL_state_string_long(ssl));
      SPrint(prntBuf);
   }
   else if (where & SSL_CB_ALERT)
   {
      str=(where & SSL_CB_READ)?"read":"write";
      sprintf(prntBuf,"SSL3 alert %s:%s:%s\n",
            str,
            SSL_alert_type_string_long(ret),
            SSL_alert_desc_string_long(ret));
      SPrint(prntBuf);
   }
   else if (where & SSL_CB_EXIT)
   {
      if (ret == 0)
      {
         sprintf(prntBuf,"%s:failed in %s\n",
               str,SSL_state_string_long(ssl));
         SPrint(prntBuf);
      }
      else if (ret < 0)
      {
         sprintf(prntBuf,"%s:error in %s\n",
               str,SSL_state_string_long(ssl));
         SPrint(prntBuf);
      }
   }   
   return;
}

/*
*
*       Fun:    hiOSSLGetMsg
*
*       Desc:   Called from the OpenSSL library 
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   tl_acc1.c
*
*/

#ifdef ANSI
PUBLIC Void hiOSSLGetMsg
(
int         write_p,
int         version,
int         content_type,
CONSTANT Void  *buf,
size_t      len,
SSL         *ssl,
Void        *arg
)
#else
PUBLIC Void hiOSSLGetMsg( write_p, version, content_type, buf, len, ssl, arg)
int         write_p;
int         version;
int         content_type;
CONSTANT Void  *buf;
size_t      len;
SSL         *ssl;
Void        *arg;
#endif
{
   TRC2(hiOSSLGetMsg)

   return; 
}

/*
*
*       Fun:    hiOSSLVerifyCb
*
*       Desc:   Called from the OpenSSL library 
*
*       Ret:    int
*
*       Notes:  None
*
*       File:   tl_acc1.c
*
*/
#ifdef ANSI
PUBLIC int hiOSSLVerifyCb
(
int             ok,             /* OpenSSL verification status */
X509_STORE_CTX  *store          /* certificate store */
)
#else
PUBLIC int hiOSSLVerifyCb(ok, store)
int             ok;             /* OpenSSL verification status */
X509_STORE_CTX  *store;         /* certificate store */
#endif
{
   int          err;
   HiAlarmInfo  alInfo;


   /* was there a verification error? */
   if (!ok)
   {
      /* get the error */
      err = X509_STORE_CTX_get_error(store);

      /* send an alarm */
      alInfo.spId = -1;
      alInfo.type = LHI_ALARMINFO_OSSL_ERR;
      alInfo.inf.osslError = err;
      hiSendAlarm(LCM_CATEGORY_PROTOCOL, LCM_EVENT_PI_INV_EVT,
                  LCM_CAUSE_DECODE_ERR, &alInfo); 
   }


   return ok;
} /* hiOSSLVerifyCb() */
#endif /* HI_TLS_EXT_CALLBACK */

/*
*
*       Fun:   hiAccConnectTLS
*
*       Desc:  This function is called from the acceptance test to
*              establish a TLS client connection to the remote address
*              in hiAccCb.curTst.
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
PUBLIC S16 hiAccConnectTLS
(
Void
)
#else
PUBLIC S16 hiAccConnectTLS()
#endif
{
   S16          ret, numSet;
   S32          r, e;
   U32          timeout, optVal;
   CmInetFd     fd;
   CmTptAddr    remAddr;
   CmInetFdSet  wFds, rFds;
   SSL_CTX      *ctx;
   BIO          *bio;
   SSL          *ssl;

   TRC2(hiAccConnectTLS);

 
   ctx = SSL_CTX_new(SSLv23_method());
   SSL_CTX_set_default_passwd_cb(ctx, hiAccTLSPasswd);
   if (SSL_CTX_load_verify_locations(ctx, HI_ACC_TLSCLIENT_CAFILE,
                                       HI_ACC_TLSCLIENT_CAPATH) != 1)
   {
      ERR_print_errors_fp(stderr);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }
   if (SSL_CTX_use_certificate_chain_file(ctx, HI_ACC_TLSCLIENT_CERTFILE) != 1)
   {
      ERR_print_errors_fp(stderr);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }
   if (SSL_CTX_use_PrivateKey_file(ctx, HI_ACC_TLSCLIENT_PRIVKEYFILE,
                                       SSL_FILETYPE_PEM) != 1)
   {
      ERR_print_errors_fp(stderr);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }
   SSL_CTX_set_verify_depth(ctx, 4);
   SSL_CTX_set_options(ctx, SSL_OP_ALL|SSL_OP_NO_SSLv2);
   SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);
   if (SSL_CTX_set_cipher_list(ctx, HI_ACC_TLSCLIENT_CIPHERS) != 1)
   {
      ERR_print_errors_fp(stderr);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   ret = HI_OPEN_SOCKET(CM_INET_STREAM, &fd, 0, HI_IPV4);
   if (ret != ROK)
   {
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   HI_SET_SOCKOPT_REUSEADDR(&fd);
   HI_SET_SOCKOPT_TCP_NODELAY(&fd);

   optVal = CM_INET_OPT_ENABLE;
   ret = cmInetSetOpt(&fd, SOL_SOCKET, CM_INET_OPT_BLOCK, (Ptr)&optVal);
   if (ret != ROK)
   {
      HI_CLOSE_SOCKET(&fd);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   remAddr.type = CM_TPTADDR_IPV4;
   remAddr.u.ipv4TptAddr.address = HI_ACC_SERV_ADDR;
   remAddr.u.ipv4TptAddr.port = HI_ACC_TLSCLIENT_REMPORT;
   ret = HI_CONNECT(&fd, &remAddr);
   if (ret == RFAILED)
   {
      HI_CLOSE_SOCKET(&fd);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   if (ret != ROK)
   {
      for (; ;)
      {
         timeout = 0;
         CM_INET_FD_ZERO(&rFds);
         CM_INET_FD_ZERO(&wFds);
         CM_INET_FD_SET(&fd, &wFds);
         CM_INET_FD_SET(&fd, &rFds);
         cmInetSelect(&rFds, &wFds, &timeout, &numSet);
         if (CM_INET_FD_ISSET(&fd, &wFds))
         {
            if (CM_INET_FD_ISSET(&fd, &rFds))
            {
               HI_CLOSE_SOCKET(&fd);
               SSL_CTX_free(ctx);
               RETVALUE(RFAILED);
            }
            break;
         }
      }
   }

   bio = BIO_new_socket(fd.fd, BIO_CLOSE);
   if (!bio)
   {
      ERR_print_errors_fp(stderr);
      HI_CLOSE_SOCKET(&fd);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   ssl = SSL_new(ctx);
   if (!ssl)
   {
      ERR_print_errors_fp(stderr);
      BIO_free(bio);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }
   SSL_set_connect_state(ssl);
   SSL_set_bio(ssl, bio, bio);
   for (; ;)
   {
      r = SSL_connect(ssl);
      if (r <= 0)
      {
         e = SSL_get_error(ssl, r);
         if (e != SSL_ERROR_WANT_READ  &&  e != SSL_ERROR_WANT_WRITE)
         {
            ERR_print_errors_fp(stderr);
            SSL_free(ssl);
            SSL_CTX_free(ctx);
            RETVALUE(RFAILED);
         }
         SThreadYield();
      }
      else
         break;
   }

   hiAccCb.curTst.ctx = ctx;
   hiAccCb.curTst.ssl = ssl;

   RETVALUE(ROK);
}


/*
*
*       Fun:   hiAccPrepareTLS
*
*       Desc:  This function is called from the acceptance test to
*              set up a TLS server that listens on the address/port
*              in hiAccCb.curTst.
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
PUBLIC S16 hiAccPrepareTLS
(
Void
)
#else
PUBLIC S16 hiAccPrepareTLS()
#endif
{
   S16          ret;
   U32          optVal;
   CmInetFd     fd;
   CmTptAddr    locAddr;
   SSL_CTX      *ctx;


   TRC2(hiAccPrepareTLS);


   ctx = SSL_CTX_new(SSLv23_method());
   SSL_CTX_set_default_passwd_cb(ctx, hiAccTLSPasswd);
   if (SSL_CTX_load_verify_locations(ctx, HI_ACC_TLSSERVER_CAFILE,
                                       HI_ACC_TLSSERVER_CAPATH) != 1)
   {
      ERR_print_errors_fp(stderr);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }
   if (SSL_CTX_use_certificate_chain_file(ctx, HI_ACC_TLSSERVER_CERTFILE) != 1)
   {
      ERR_print_errors_fp(stderr);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }
   if (SSL_CTX_use_PrivateKey_file(ctx, HI_ACC_TLSSERVER_PRIVKEYFILE,
                                       SSL_FILETYPE_PEM) != 1)
   {
      ERR_print_errors_fp(stderr);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }
   SSL_CTX_set_verify_depth(ctx, 4);
   SSL_CTX_set_options(ctx, SSL_OP_ALL|SSL_OP_NO_SSLv2);
   SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);
   if (SSL_CTX_set_cipher_list(ctx, HI_ACC_TLSSERVER_CIPHERS) != 1)
   {
      ERR_print_errors_fp(stderr);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   ret = HI_OPEN_SOCKET(CM_INET_STREAM, &fd, 0, HI_IPV4);
   if (ret != ROK)
   {
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   HI_SET_SOCKOPT_REUSEADDR(&fd);
   HI_SET_SOCKOPT_TCP_NODELAY(&fd);

   optVal = CM_INET_OPT_ENABLE;
   ret = cmInetSetOpt(&fd, SOL_SOCKET, CM_INET_OPT_BLOCK, (Ptr)&optVal);
   if (ret != ROK)
   {
      HI_CLOSE_SOCKET(&fd);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   locAddr.type = CM_TPTADDR_IPV4;
   locAddr.u.ipv4TptAddr.address = HI_ACC_SERV_ADDR;
   locAddr.u.ipv4TptAddr.port = HI_ACC_TLSSERVER_LOCPORT;
   ret = HI_BIND_SOCKET(&fd, &locAddr);
   if (ret != ROK)
   {
      ERR_print_errors_fp(stderr);
      HI_CLOSE_SOCKET(&fd);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

#ifdef WIN32
   ret = HI_LISTEN(&fd, 1);
#else
   ret = HI_LISTEN(&fd, 5);
#endif
   if (ret != ROK)
   {
      ERR_print_errors_fp(stderr);
      HI_CLOSE_SOCKET(&fd);
      SSL_CTX_free(ctx);
      RETVALUE(RFAILED);
   }

   hiAccCb.curTst.ctx = ctx;
   cmMemcpy((U8 *)&hiAccCb.curTst.srvFd, (U8 *)&fd, sizeof (CmInetFd));


   RETVALUE(ROK);
}


/*
*
*       Fun:   hiAccAcceptTLS
*
*       Desc:  This function is called from the acceptance test to
*              accept a connection on the open TLS server.
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
PUBLIC S16 hiAccAcceptTLS
(
Void
)
#else
PUBLIC S16 hiAccAcceptTLS()
#endif
{
   S16          ret, numSet;
   S32          r, e;
   U32          timeout;
   CmInetFd     fd;
   CmTptAddr    peerAddr;
   CmInetFdSet  wFds, rFds;
   BIO          *bio;
   SSL          *ssl;


   TRC2(hiAccAcceptTLS);


   for (; ;)
   {
      timeout = 0;
      CM_INET_FD_ZERO(&rFds);
      CM_INET_FD_ZERO(&wFds);
      CM_INET_FD_SET(&hiAccCb.curTst.srvFd, &wFds);
      CM_INET_FD_SET(&hiAccCb.curTst.srvFd, &rFds);
      cmInetSelect(&rFds, &wFds, &timeout, &numSet);
      if (CM_INET_FD_ISSET(&hiAccCb.curTst.srvFd, &rFds))
         break;
   }

   ret = HI_ACCEPT(&hiAccCb.curTst.srvFd, &peerAddr, &fd);
   if (ret != ROK)
   {
      HI_CLOSE_SOCKET(&hiAccCb.curTst.srvFd);
      SSL_CTX_free(hiAccCb.curTst.ctx);
      hiAccCb.curTst.ctx = NULLP;
      RETVALUE(RFAILED);
   }
   HI_CLOSE_SOCKET(&hiAccCb.curTst.srvFd);

   bio = BIO_new_socket(fd.fd, BIO_CLOSE);
   if (!bio)
   {
      ERR_print_errors_fp(stderr);
      HI_CLOSE_SOCKET(&fd);
      SSL_CTX_free(hiAccCb.curTst.ctx);
      hiAccCb.curTst.ctx = NULLP;
      RETVALUE(RFAILED);
   }

   ssl = SSL_new(hiAccCb.curTst.ctx);
   if (!ssl)
   {
      ERR_print_errors_fp(stderr);
      BIO_free(bio);
      SSL_CTX_free(hiAccCb.curTst.ctx);
      hiAccCb.curTst.ctx = NULLP;
      RETVALUE(RFAILED);
   }
   SSL_set_accept_state(ssl);
   SSL_set_bio(ssl, bio, bio);

   for (; ;)
   {
      r = SSL_accept(ssl);
      if (r <= 0)
      {
         e = SSL_get_error(ssl, r);
         if (e != SSL_ERROR_WANT_READ  &&  e != SSL_ERROR_WANT_WRITE)
         {
            ERR_print_errors_fp(stderr);
            SSL_free(ssl);
            SSL_CTX_free(hiAccCb.curTst.ctx);
            hiAccCb.curTst.ctx = NULLP;
            RETVALUE(RFAILED);
         }
         SThreadYield();
      }
      else
         break;
   }

   hiAccCb.curTst.ssl = ssl;


   RETVALUE(ROK);
}


/*
*
*       Fun:   hiAccDisconnectTLS
*
*       Desc:  This function is called from the acceptance test to
*              tear down the TLS connection in hiAccCb.curTst.
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
PUBLIC S16 hiAccDisconnectTLS
(
Void
)
#else
PUBLIC S16 hiAccDisconnectTLS()
#endif
{
   TRC2(hiAccDisconnectTLS);


   if (hiAccCb.curTst.ssl)
   {
      SSL_shutdown(hiAccCb.curTst.ssl);
      SSL_free(hiAccCb.curTst.ssl);
      hiAccCb.curTst.ssl = NULLP;
   }
   if (hiAccCb.curTst.ctx)
   {
      SSL_CTX_free(hiAccCb.curTst.ctx);
      hiAccCb.curTst.ctx = NULLP;
   }


   RETVALUE(ROK);
}


/*
*
*       Fun:   hiAccSendTLS
*
*       Desc:  This function is called from the acceptance test to
*              transmit data on a TLS connection using the context
*              and connection in hiAccCb.curTst.
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
PUBLIC S16 hiAccSendTLS
(
Buffer *mBuf,           /* message to send */
MsgLen mLen             /* message length */
)
#else
PUBLIC S16 hiAccSendTLS(mBuf, mLen)
Buffer *mBuf;           /* message to send */
MsgLen mLen;            /* message length */
#endif
{
   S16          ret;
   Buffer       *dBuf;
   Data         *dPtr;
   MsgLen       txLen, dLen;
   S32          r;


   TRC2(hiAccSendTLS);


   ret = SInitNxtDBuf(mBuf);
   if (ret != ROK)
      RETVALUE(RFAILED);

   txLen = 0;
   while (txLen < mLen)
   {
      ret = SGetNxtDBuf(mBuf, &dBuf);
      if (ret == ROKDNA)
         RETVALUE(ROK);
      else if (ret != ROK)
         RETVALUE(RFAILED);

      ret = SGetDataTx(dBuf, &dPtr, &dLen);
      if (ret != ROK)
         RETVALUE(RFAILED);

      r = SSL_write(hiAccCb.curTst.ssl, dPtr, dLen);
      if (r != dLen)
         RETVALUE(RFAILED);

      txLen += r;
   }

   hiAccCb.curTst.sentLen += mLen;


   RETVALUE(ROK);
}


/*
*
*       Fun:   hiAccRecvTLS
*
*       Desc:  This function is called from the acceptance test to
*              receive data on a TLS connection using the context
*              and connection in hiAccCb.curTst.
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
PUBLIC S16 hiAccRecvTLS
(
Buffer **recvBuf,       /* received message */
MsgLen *recvLen         /* message length */
)
#else
PUBLIC S16 hiAccRecvTLS(recvBuf, recvLen)
Buffer **recvBuf;       /* received message */
MsgLen *recvLen;        /* message length */
#endif
{
   S16          ret;
   S32          r, e;
   Buffer       *mBuf;
   Data         *rBuf;
   MsgLen       rBufLen;


   TRC2(hiAccRecvTLS);


   ret = SGetMsg(hiAccCb.init.region, hiAccCb.init.pool, &mBuf);
   if (ret != ROK)
      RETVALUE(RFAILED);

   rBufLen = HI_TLS_RECORD_SIZE;
   ret = SGetSBuf(hiAccCb.init.region, hiAccCb.init.pool, &rBuf, rBufLen);
   if (ret != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   for (; ;)
   {
      r = SSL_read(hiAccCb.curTst.ssl, rBuf, rBufLen);
      if (r <= 0)
      {
         e = SSL_get_error(hiAccCb.curTst.ssl, r);
         if (e == 0)
         {
            SPutSBuf(hiAccCb.init.region, hiAccCb.init.pool, rBuf, rBufLen);
            SPutMsg(mBuf);
            SThreadYield();
            RETVALUE(ROKDNA);
         }
         if (e != SSL_ERROR_WANT_READ  &&  e != SSL_ERROR_WANT_WRITE)
         {
            ERR_print_errors_fp(stderr);
            SPutSBuf(hiAccCb.init.region, hiAccCb.init.pool, rBuf, rBufLen);
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         SThreadYield();
      }
      else
         break;
   }
   
   ret = SAddPstMsgMult(rBuf, (MsgLen)r, mBuf);
   if (ret != ROK)
   {
      SPutMsg(mBuf);
      mBuf = NULLP;
      r = 0;
   }

   SPutSBuf(hiAccCb.init.region, hiAccCb.init.pool, rBuf, rBufLen);

   *recvBuf = mBuf;
   *recvLen = r;

   hiAccCb.curTst.recvLen += *recvLen;

   RETVALUE(ROK);
}


/*
*
*       Fun:   hiAccCheckTLSMsg
*
*       Desc:  This function is called from the acceptance test to
*              receive data on a TLS connection using the context
*              and connection in hiAccCb.curTst.
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
PUBLIC S16 hiAccCheckTLSMsg
(
Buffer *msg1,           /* original message */
Buffer *msg2            /* echoed message */
)
#else
PUBLIC S16 hiAccCheckTLSMsg(msg1, msg2)
Buffer *msg1;           /* original message */
Buffer *msg2;           /* echoed message */
#endif
{
   S32          i;
   MsgLen       len1, len2;
   U8           byte1, byte2;


   TRC2(hiAccCheckTLSMsg);


   if (SFndLenMsg(msg1, &len1) != ROK)
      RETVALUE(RFAILED);
   if (SFndLenMsg(msg2, &len2) != ROK)
      RETVALUE(RFAILED);

   if (len1 < len2)
      RETVALUE(RFAILED);

   for (i = 0;  i < len2;  i++)
   {
      if (SExamMsg((Data *)&byte1, msg1, (MsgLen)(i + hiAccCb.curTst.cnt))
          != ROK)
         RETVALUE(RFAILED);
      if (SExamMsg((Data *)&byte2, msg2, (MsgLen)i) != ROK)
         RETVALUE(RFAILED);
      if (byte1 != byte2)
         RETVALUE(RFAILED);
   }

   if (len1 > len2)
      hiAccCb.curTst.cnt += len2;

   RETVALUE (len1 == hiAccCb.curTst.cnt) ? ROK : ROKDNA;
}

#endif /* HI_TLS */


/********************************************************************30**
 
         End of file:     tl_acc1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:54 2015

*********************************************************************31*/
 
/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 
/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/
/********************************************************************70**
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
 
*********************************************************************71*/
 
/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
    ver       pat     init                  description
----------- --------- ---- ----------------------------------------------
1.1         ---       asa  1. initial release.
1.1+        hi002.11  asa  1. changes for loopback mode.
                           2. initializing HiAccCb in hiInitAcc().
                           3. created sample TCP application header 
                              profiles in TSAP configuration.
/main/2     ---       cvp  1. added HI_ACC_MCAST_ENB flag to enable 
                              multicast test case.
                           2. changed the copyright header.
            /main/4   sb   1. change for Raw socket interface.
                           2. Flag added for backward compatibility.
                      cvp  3. sht header file included.
/main/4+    hi005.13  cvp  1. Added new configuration parameters 
/main/4     ---       cvp  1. Added IPV6 testcases.
                           2. Changed the copyright header.
/main/4     hi003.104 mmh  1. Skip acceptance test case 3 if
                              HI_ACC_MCAST_ENB is not enabled.
                           2. Add acceptance test case 7 if
                              HI_ACC_RAW_ENB is enabled.
/main/4+    hi009.104 mmh  1. added new test case for ipv4 options
                           2. added new test cases for ipv6 extension headers.
                           3. move up ipv6 test cases and reorganize test
                              table and sequence number.
                           4. replace printf with sprintf and SPrint call
                              in function hiAccChkMsg.
                           5. init variables to 0 in function hiAccChkMsg.
                           6. added new test cases in hiDispTstInfo()
                           7. added tab char before printing some string
                           8. Added Rolling Upgrade support
                              - added public variables for remote interface 
                                version
                              - fill LM interface version number in function
                                hiAccGenCfg
                              - fill interface version info in function 
                                hiAccSapCfg
                              - added new function hiAccSendShCntrl() which 
                                sends a System agent control request
                              - modify the test initialization function and the
                                test sequence table by adding RUG test cases.
                              - added check for correctness of version info on
                                SAP configured by LM.
                              - increase state in hiAccProcCntrlCfm when test 
                                case mumber is 17.
/main/5      ---       kp   1. Updated for release 1.5.
/main/5+    hi002.105  ss   1. Add Sap Id in Trace.
                            2. SS_MULTIPLE_PROCS flag added.
                            3. Added TestCase hiAccTst20.
/main/5+    hi008.105  ss   1. Added some more callback function.
/main/5+    hi014.105 svp  1. Modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+     hi002.201  cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/6+    hi005.201  rss  1. Added Test case to check conjestion timer changes.
                            2. Test case 10 is Gaurded under HI_ACC_MCAST_ENB
/main/6+    hi012.201  rcs 1. Test case 46 and 47 for handling outstream socket option 
                               in AssocReq.
/main/6+    hi023.201  rcs 1. Test case 48 added for testing trace
                              indication for KSCTP.
/main/6+    hi025.201  rss  1. ccpu00107195  changes
/main/6+    hi026.201  rss  1. Added IPV6 test case for ksctp 
/main/6+    hi028.201 ragrawal 1. Printed all the statistics collected at TUCL 
                                  layer and incremented test case step to next 
                                  in hiAccProcStsCfm().
                               2. Added new test cases HI_TSTID_55, HI_TSTID_56
                                  and HI_TSTID_57.
                               3. Added new function hiAccGenCfg_1() for 
                                  reconfiguration of LM pst structure and
                                  protected under HI_ACC_GEN_RECONFIG flag.
/main/6+   hi029.201  ragrawal 1. Fix for 64 bit compilation warnings.
*********************************************************************91*/
