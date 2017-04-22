
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_tst.c

     Sid:      czac_tst.c@@/main/2 - Tue Aug 30 18:36:00 2011

     Prg:     sy 
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "czt.h"           /* CZT defines */
#include "lcz.h"           /* layer management defines for X2AP */
#include "sct.h"           /* SB (SCTP) layer */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h"

#include "cz.h"            /* defines and macros for X2AP */
#include "czac_acc.h"      /* defines for X2AP acceptance tests */
#include <stdlib.h>

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* CZT types */
#include "lcz.x"           /* layer management typedefs for X2AP */
#include "cm_xta.x"

#ifdef HI
#include "lhi.x"
#include "czac_lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "czac_lsb.x"
#endif    /* SB */

#include "cz.x"            /* typedefs for CZCP */
#include "czac_acc.x"        /* typedefs for CZCP acceptance tests */
#include "czac_lcz.x"
#include "czac_czt.x"

#ifdef DM
#include "czac_sct.x"
#endif /*DM*/


/* cz001.101 : CR Fixes.*/
PUBLIC CzAccCb czAccCb;
/*
*
*       Fun:   cmXtaAppTst
*
*       Desc:  This functions is called from the SSI.
*              It registers the various layers with
*              SSI.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  tq_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppTst
(
)
#else
PUBLIC S16 cmXtaAppTst(Void)
#endif
{
   TRC2(cmXtaAppTst)

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTst */

#ifdef CMXTA_MASTER
/*
*
*       Fun:   cmXtaAppMasterInit
*
*       Desc:  Initialization function for acceptance test
*
*       Ret:   Void
*
*       Notes: None
*
*ilps       File:  tq_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterInit
(
Void
)
#else
PUBLIC S16 cmXtaAppMasterInit(Void)
#endif
{
   S16      ret = 0;
  U8 i;

   CzProtCfg     *protCfg;
   CzPeerCfg     *peerCfg;
#ifdef SCT_ENDP_MULTI_IPADDR   
   CmInetIpAddr  tempDstAddr;
#endif   
   TRC2(cmXtaAppMasterInit)
   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Initializing the Test Architecture\n"));
/* fill the protocol and peer profile */
#ifdef SB_IPV6_SUPPORTED
   cmInetAddr("::1", &czAccCb.directives.baseIp);
#else
   cmInetAddr("127.0.0.1", &czAccCb.directives.baseIp);
#endif
#ifdef SCT_ENDP_MULTI_IPADDR   
   cmInetAddr(IPADDR_2, &tempDstAddr);
#endif   
 for (i=0;i < CZ_MAX_ENODEB;i++)
 { 
    protCfg = &czENodeB[i].protCfg;
    peerCfg = &czENodeB[i].peerCfg;
#ifdef SB_IPV6_SUPPORTED
    protCfg->srcAddr.ipAddr.nAddr[0].type  =   CM_IPV6ADDR_TYPE;
    cmInetPton6(&protCfg->srcAddr.ipAddr.nAddr[0].u.ipv6NetAddr, "::1");
    protCfg->srcAddr.ipAddr.nmb  =   1;
#else
    protCfg->srcAddr.ipAddr.nAddr[0].type  =   CM_IPV4ADDR_TYPE;
    protCfg->srcAddr.ipAddr.nAddr[0].u.ipv4NetAddr   =  ntohl(czAccCb.directives.baseIp);
#ifdef SCT_ENDP_MULTI_IPADDR   
    protCfg->srcAddr.ipAddr.nAddr[1].type  =   CM_IPV4ADDR_TYPE;
    protCfg->srcAddr.ipAddr.nAddr[1].u.ipv4NetAddr   =  ntohl(tempDstAddr);
    protCfg->srcAddr.ipAddr.nmb  =   2;
#else
    protCfg->srcAddr.ipAddr.nmb  =   1;
#endif
#endif
    protCfg->eNbId     =   5000 + i;
    protCfg->tRELOCprep     =   CMXTA_CZ_500_MSECONDS;
    protCfg->tX2RELOCOverall=   CMXTA_CZ_4_SECONDS;
    protCfg->timeToWait     =   CMXTA_CZ_4_SECONDS;
    protCfg->dynamPeerFlag     = FALSE;
    protCfg->defDPeerUSapId     = 0;
    protCfg->srcAddr.sctPort =   czAccCb.directives.basePort + i+2;


    peerCfg->peerId    =  i; 
    peerCfg->uSapId     =  0;  
    peerCfg->tSapId     =  0; 
    peerCfg->eAValue     =CZAC_LCZ_ENC_ALGO;  
    peerCfg->iPAValue     = CZAC_LCZ_INTG_ALGO; 

    peerCfg->assocCfg.locOutStrms        =  CZAC_LCZ_OUT_STRMS;
    peerCfg->globalProcStrmId.pres        =  1;
    peerCfg->globalProcStrmId.val        =  CZAC_LCZ_GLOBAL_STRM_ID;
#ifdef SB_IPV6_SUPPORTED
    peerCfg->assocCfg.priDstAddr.type    =  CM_IPV6ADDR_TYPE;
    cmInetPton6(&peerCfg->assocCfg.priDstAddr.u.ipv6NetAddr, "::1");
    peerCfg->assocCfg.dstAddrLst.nAddr[0].type   =  CM_IPV6ADDR_TYPE;
    cmInetPton6(&peerCfg->assocCfg.dstAddrLst.nAddr[0].u.ipv6NetAddr, "::1");
    peerCfg->assocCfg.dstAddrLst.nmb     =  1;
#else
    peerCfg->assocCfg.priDstAddr.type    =  CM_IPV4ADDR_TYPE;
    peerCfg->assocCfg.priDstAddr.u.ipv4NetAddr   =  ntohl(czAccCb.directives.baseIp);
    peerCfg->assocCfg.dstAddrLst.nAddr[0].type   =  CM_IPV4ADDR_TYPE;
    peerCfg->assocCfg.dstAddrLst.nAddr[0].u.ipv4NetAddr   =  ntohl(czAccCb.directives.baseIp);
#ifdef SCT_ENDP_MULTI_IPADDR   
    peerCfg->assocCfg.dstAddrLst.nAddr[1].type   =  CM_IPV4ADDR_TYPE;
    peerCfg->assocCfg.dstAddrLst.nAddr[1].u.ipv4NetAddr   =  ntohl(tempDstAddr);
    peerCfg->assocCfg.dstAddrLst.nmb     =  2;
#else
    peerCfg->assocCfg.dstAddrLst.nmb     =  1;
#endif
#endif
    if ( i < 1) 
    {
    peerCfg->assocCfg.dstPort            = czAccCb.directives.basePort  + 3;
    }
    else
    {
    peerCfg->assocCfg.dstPort            = czAccCb.directives.basePort  +2;

    }

 }
   
#ifdef HI
   /*-- HI module init function --*/
   if ((ret = czAcLhiInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif

   /*-- SB module init function --*/
#ifdef SB 
   if ((ret = czAcLsbInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif

   /*-- CZ  module init function --*/
   if ((ret = czAcLczInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- CMXTA_ENHANCE:  Put Init functions for rest of the
        modules here, this will happen only once --*/

#ifdef DM
   /*-- SCT module init function --*/
   if ((ret = czAcSctInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);
#endif /*DM*/

   /*-- AQU module init function --*/
   if ((ret = czAcCztInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterInit(): Test Architecture Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterInit */


/*
*
*       Fun:   cmXtaAppMasterDeInit
*
*       Desc:  This functions is called from the SSI.
*              It registers the various layers with
*              SSI.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  tq_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppMasterDeInit()
#endif
{
   TRC2(cmXtaAppMasterDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterDeInit(): Shutting down the Test Architecture\n"));

   /*-- Opposite of the steps done in aqAcInit --*/

   /*-- Put DeInit functions for rest of the
        modules here, this will happen only once --*/

   /*-- AQU module deInit function --*/
   (Void)czAcCztDeInit();

#ifdef DM 

   /*-- SCT module deInit function --*/
#ifdef SB 
   (Void)czAcSctDeInit();
#endif /* end of SB*/
#endif /*DM*/

   /*-- LAQ module deInit function --*/
   (Void)czAcLczDeInit();

   /*-- LSB module deInit function --*/
#ifdef SB
   (Void)czAcLsbDeInit();
#endif

#ifdef HI
   /*-- LHI module deInit function --*/
   (Void)czAcLhiDeInit();
#endif

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppMasterDeInit(): Test Architecture Shutdown Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterDeInit */


/*
*
*      Fun  : cmXtaAppMasterParseCmdLine
*
*      Desc : This function parses the command line to set
*             the test usage options.
*
*      Ret  : Void
*
*      Notes: None
*
*      File : tq_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppMasterParseCmdLine
(
Void
)
#else
PUBLIC S16 cmXtaAppMasterParseCmdLine()
#endif
{
   S16          ret = 0;                        /* return value         */
   ProcId       procId;
   U16          prof=0;
   U8             i = 0;


   TRC2(cmXtaAppMasterParseCmdLine)

   while ((ret = SGetOpt(msArgc, msArgv, "ab:c:d:f:b:hi:o:p:r:t:")) != EOF)
   {
      switch(ret)
      {
         /*-- SSI specific --*/
         case 'f':
            break;
        case 't':
            prof = atoi(msOptArg);
            czAccCb.directives.tptType = prof;
            break;
         case 'o':
            /* we ignore the output specifier and specifiers used by TA command
               line parser --*/
            break;

         case 'd':
            /*-- Set debug level --*/
            cmXtaCb.dbgMask = atoi(msOptArg);
            break;
         case 'b':   
            /* Set the base Port No.Change the base Port for the Peer Cfg */
            czAccCb.directives.basePort = atoi(msOptArg);
            for(i=0;i < CZ_MAX_ENODEB;i++)
            {
               czENodeB[i].protCfg.srcAddr.sctPort  = czAccCb.directives.basePort + i +2;
               czENodeB[i].peerCfg.assocCfg.dstPort = czAccCb.directives.basePort + i +2;
            }
            break;
         case 'i':   
            /* Set the base Port No.Change the base Port for the Peer Cfg */
            cmInetAddr(msOptArg, &czAccCb.directives.baseIp);
            for(i=0;i < CZ_MAX_ENODEB;i++)
            {
               czENodeB[i].protCfg.srcAddr.ipAddr.nAddr[0].u.ipv4NetAddr = \
                  ntohl(czAccCb.directives.baseIp);;
               czENodeB[i].peerCfg.assocCfg.dstAddrLst.nAddr[0].u.ipv4NetAddr = \
                  ntohl(czAccCb.directives.baseIp);;
               czENodeB[i].peerCfg.assocCfg.priDstAddr.u.ipv4NetAddr   =  \
                  ntohl(czAccCb.directives.baseIp);
            }
            break;

         case 'h':
            /* help and unknown options display help message    */
            cmXtaMasterUsage();
            RETVALUE(RFAILED);
            break;

         case 'r':
            /* Xta Proc Id */
            procId = atoi(msOptArg);
            czAccCb.directives.xtaProcId = procId;
            czAccCb.directives.eNb1ProcId = procId;
            czAccCb.directives.eNb2ProcId = procId;
            break;

         case '?':
         default:
            /* help and unknown options display help message    */
            cmXtaMasterUsage();
            RETVALUE(RFAILED);
            break;
      }
   }

   czAccCb.directives.eNb1IpAddr =   cmXtaCb.localIpcIpAddr; 
   czAccCb.directives.eNb2IpAddr =   cmXtaCb.remoteIpcIpAddr;

   if((cmXtaCb.curTopId == 6))
   {
      czAccCb.directives.xtaProcId = CMXTA_PROCID_MASTER;
      czAccCb.directives.eNb1IpAddr =   cmXtaCb.remoteIpcIpAddr; 
      czAccCb.directives.eNb2IpAddr =   cmXtaCb.remoteIpcIpAddr;
   }



   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppMasterParseCmdLine */

/*
*
*      Fun  : cmXtaAppMasterUsage
*
*      Desc : This function displays an acceptance test usage message.
*
*      Ret  : Void
*
*      Notes: None.
*
*      File : aqac_tst.c
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppMasterUsage
(
Void
)
#else
PUBLIC Void cmXtaAppMasterUsage()
#endif
{
   Txt   pBuf[100];  /* output string buffer */

   TRC2(cmXtaAppUsage);

   cmMemset((U8*)&pBuf, 0 , 100);
   sprintf(pBuf, "X2AP Options:\n============\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-d 0-9 dbgMask     ]   - Enable Debug Masks \n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-r xtaProcId       ]   - Set the xtaProcId\n");
   SPrint(pBuf);

   RETVOID;
} /* cmXtaAppMasterUsage */
#endif /* CMXTA_MASTER */

/*
*
*       Fun:   cmXtaAppSlaveInit
*
*       Desc:  Initialization function for acceptance test
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  aqac_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveInit
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveInit(Void)
#endif
{
   TRC2(cmXtaAppSlaveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Initializing the slave\n"));
#ifndef SS_MULTIPLE_PROCS
   czActvInit(ENTCZ, 0, 0, 0);
#endif
   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveInit */


/*
*
*       Fun:   cmXtaAppSlaveDeInit
*
*       Desc:  This functions is called from the SSI.
*              It registers the various layers with
*              SSI.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  aqac_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveDeInit()
#endif
{
   TRC2(cmXtaAppSlaveDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveDeInit(): Shutting down the Test Architecture\n"));

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveDeInit(): Test Architecture Shutdown Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveDeInit */

/*
*
*      Fun  : cmXtaAppSlaveParseCmdLine
*
*      Desc : This function parses the command line to set
*             the test usage options.
*
*      Ret  : Void
*
*      Notes: None
*
*      File : aqac_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveParseCmdLine
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveParseCmdLine()
#endif
{

   TRC2(cmXtaAppSlaveParseCmdLine)

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveParseCmdLine */

/*
*
*      Fun  : cmXtaAppSlaveUsage
*
*      Desc : This function displays an acceptance test usage message.
*
*      Ret  : Void
*
*      Notes: None.
*
*      File : aqac_tst.c
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppSlaveUsage
(
Void
)
#else
PUBLIC Void cmXtaAppSlaveUsage()
#endif
{
   TRC2(cmXtaAppSlaveUsage);

   RETVOID;
} /* cmXtaAppSlaveUsage */

/*
*
*       Fun:   cmXtaAppDirectiveInit
*
*       Desc:  Call handler for Command Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  aqac_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppDirectiveInit
(
Void
)
#else
PUBLIC S16 cmXtaAppDirectiveInit()
#endif
{

   TRC2(cmXtaAppDirectiveInit)


   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppDirectiveInit(): Init done\n"));

   cmXtaCb.directives.capAlarm  =   TRUE;
   cmXtaCb.directives.capTrc  =   TRUE;

#ifdef SS_MULTIPLE_PROCS
   czAccCb.directives.xtaProcId =   CZAC_PROCID_SINGLE;
   czAccCb.directives.eNb1ProcId =   CZAC_PROCID_SINGLE;
   czAccCb.directives.eNb2ProcId =   CZAC_PROCID_ONE;
#endif /* SS_MULTIPLE_PROCS */
#ifdef CZAC_INTG_TEST
   czAccCb.directives.xtaProcId =   CMXTA_PROCID_MASTER;
   czAccCb.directives.eNbProcId =   CMXTA_PROCID_MASTER;
   czAccCb.directives.mmeProcId =   CMXTA_PROCID_SLAVE;
#endif /* CZAC_INTG_TEST */

   czAccCb.directives.eNb1IpAddr =   cmXtaCb.localIpcIpAddr; 
   czAccCb.directives.eNb2IpAddr =   cmXtaCb.remoteIpcIpAddr;
   czAccCb.directives.basePort   =   CZAC_LCZ_ENB_SCTPORT;
#ifndef CZAC_SCTP
   czAccCb.directives.tptType   =   CZAC_TPT_KSCTP;
#else
   czAccCb.directives.tptType   =   CZAC_TPT_SCTP;
#endif 
   RETVALUE(ROK);
}/* cmXtaAppDirectiveInit */
 
/*
*
*       Fun: 
*  
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppInitQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC S16 cmXtaAppInitQ(msgQ)
CmXtaMsgQ   *msgQ;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppInitQ */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppFlushQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC Void cmXtaAppFlushQ(msgQ)
CmXtaMsgQ *msgQ;
#endif
{
   RETVOID;
} /* cmXtaAppFlushQ */

/*
 *
 *       Fun:    cmXtaAppTCCreate
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaAppTCCreate
(
CmXtaTCCb         *tcCb
)
#else
PUBLIC S16 cmXtaAppTCCreate(tcCb)
CmXtaTCCb    *tcCb;
#endif
{

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppTCCreate() */

/*
*
*       Fun:   cmXtaAppTCDelete
*
*       Desc:  This function deletes an existing transaction.
*
*       Ret:   If success, return CMXTA_ERR_NONE
*              If failure, return error Code
*
*       Notes: None
*
*       File:  ag_txn.c
*
*/
#ifdef ANSI
PUBLIC S16  cmXtaAppTCDelete
(
CmXtaTCCb         *tcCb       /* Transaction Block   */
)
#else
PUBLIC S16  cmXtaAppTCDelete (tcCb)
CmXtaTCCb      *tcCb;         /* Transaction Block   */
#endif
{
   czAccCb.hitCb.nxtConnId = 0;
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTCDelete */

#ifdef NOT_USED
#if (!defined(CZAC_INTG_TEST) && !defined(SS_VW))
/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppIpcInit
(
Void
)
#else
PUBLIC S16 cmXtaAppIpcInit(Void)
#endif
{

   TRC2(cmXtaAppIpcInit)
   /*-- Part of support for multiple slaves. In order to talk to 
        multiple slaves we need to have relay configured for each of the 
        nodes. The following code if the relay flag is enabled will use the 
        common relay product else it will used the minmial relay that we have as 
        part of CM_XTA. --*/

   RETVALUE(ROK);

}/* cmXtaAppIpcInit()*/

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppIpcDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppIpcDeInit(Void)
#endif
{
   TRC2(cmXtaAppIpcDeInit)

   RETVALUE(ROK);
}/* cmXtaAppIpcDeInit()*/
#endif /* (!defined(CZAC_INTG_TEST) && !defined(SS_VW))*/
#endif /* NOT_USED */


/*
*       Fun:   cmXtaAppPyInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  aqac_py.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppPyInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}/* aqacPyInit */

/*
*
*       Fun:   cmXtaAppPyDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  aqac_py.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppPyDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyDeInit()
#endif
{
   TRC2(cmXtaAppPyDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppPyDeInit():  Shutting down python interpreter\n"));

   RETVALUE(CMXTA_ERR_NONE);
}/* aqacPyDeInit */
/********************************************************************30**

         End of file:     czac_tst.c@@/main/2 - Tue Aug 30 18:36:00 2011

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sy       1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
