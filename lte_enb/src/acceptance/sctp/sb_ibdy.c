
/********************************************************************20**

     Name:     sb_ibdy.c - Acceptance Tests Controller for the SCTP layer

     Type:     C source file

     Desc:     C code for controlling acceptance tests execution

     File:     sb_ibdy.c

     Sid:      sb_ibdy.c@@/main/2 - Thu Jul 26 07:54:13 2007

     Prg:      nct

*********************************************************************21*/

/*

  sb_ibdy.c - Acceptance Tests Controller for the SCTP layer

Following functions are provided in this file:
         tst                  - main test function

*/

/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000163                      SCTP layer */

/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_os.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb_mtu.h"        /* mtu defines */
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */
#include "sb_acc.h"        /* defines for SCTP layer */
#include "lhi.h"
#include "hi.h"
#include "sb.h"
#include "sb_ibdy.h"

#include <arpa/inet.h> /* for inet_addr() */
#include <unistd.h>    /* for sleep() */


/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_os.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* Common DNS library */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_mtu.x"        /* mtu typedefs  */
/* #include "it.x"          defines for dummy it layer */
#include "lhi.x"
#include "hi.x"            /* defines for dummy hi layer */
#include "sb.x"            /* SCTP internal typedefs */
#include "sb_acc.x"        /* defines for SCTP layer */
#include "sb_ibdy.x"

#include<sys/time.h>   /* SANDEEP */

#ifndef TSTINST
#define TSTINST 0
#endif

U8      sbCmdArgs[MAXCMDLEN];
U16     sbCmdLen;
TstInput  sctpInput;
EXTERN PUBLIC S8 optDebug;                       /* debug */
U8       filedata=FALSE;
U16      messagerate;

EXTERN  U32 pktCount;
EXTERN  U32 pktThousand;
EXTERN  SbGlobalCb  sbGlobalCb;

PRIVATE Keys sbMenuKw[]=
{
   {"abort",              0 },   
   {"addrstatus",         1 },   
   {"assoc",              2 },   
   {"assoclist",          3 },   
   {"assocstatus",        4 },   
   {"bulkdata",           5 },   
   {"loopdata",           6 },   
   {"data",               7 },   
   {"endplist",           8 },   
   {"endpclose",          9 },   
   {"filedata",          10 },   
   {"help",              11 },   
   {"hbeat",             12 },   
   {"hbaddr",            13 },
   {"initsctp",          14 },   
   {"openendp",          15 },   
   {"ping",              16 },
   {"rtrvstatus",        17 },   
   {"sendfile",          18 },   
   {"showpktcnt",        19 },   
   {"setfreq",           20 },   
   {"setpri",            21 },   
   {"shutdown",          22 },   
   {"trace",             23 },   
   {"verbose",           24 },   
   {"displinfo",         25 },   
   {"stats",             26 },   
   {"quit",              27 },   
   {"",        MATCH_FAILED }    
};


/*
*
*       Fun:   tst
*
*       Desc:  This routine is called by MOS to configure the layers
*              and run the acceptance test.
*
*       Ret:   ROK       - ok
*
*       Notes: This function name is required by MOS, and is invoked
*              just before the main scheduling loop, in order to
*              register tasks, configure and bind.
*
*       File:  sb_ibdy.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
void
)
#else
PUBLIC S16 tst()
#endif
{

#ifndef MSVER2 
   SSTskId   tskId;
   SSTskId   tuclTskId;
   SSTskId   testTskId;
   SSTskId   hiPermTskId;
#endif


   TRC1(tst)
   UNUSED(hiPermTskId);
   UNUSED(testTskId);
   UNUSED(tuclTskId);

#ifdef MSVER2 
   /* Trillium MOS */

#ifdef SB
   SRegInit(ENTSB, TSTINST, sbActvInit);
   SRegActvTsk(ENTSB, TSTINST, TTNORM, 0, sbActvTsk);
#endif

#ifdef HI
   SRegInit(ENTHI, TSTINST, hiActvInit);
   SRegActvTsk(ENTHI, TSTINST, TTNORM, 0, hiActvTsk);
   SRegActvTsk(ENTHI, TSTINST+1, TTPERM, 0, hiScanPermTsk);
#endif

#ifdef IT
   SRegInit(ENTIT, TSTINST, itSbActvInit);
   SRegActvTsk(ENTIT, TSTINST, TTNORM, 0, itSbActvTsk);
#endif

#ifdef SM
   SRegInit(ENTSM, TSTINST, smActvInit);
   SRegActvTsk(ENTSM, TSTINST, TTNORM, 0, smActvTsk);
#endif

#if (SB_PRFM_SNDR) || (SB_PRFM_RCVR)
   /* This task will be added for Performance Testing purpose */
   SRegActvTsk(ENTSB, TSTINST+1, TTPERM, 0, sbPermTsk);
#endif

#else 
   /* MTSS  */

   /* create all tapa tasks */
#ifdef SB
   SRegTTsk(ENTSB, TSTINST, TTNORM, 0, sbActvInit, sbActvTsk);
#endif
#ifdef HI
   SRegTTsk(ENTHI, TSTINST, TTNORM, 0, hiActvInit, hiActvTsk);
   SRegTTsk(ENTHI, (TSTINST+1), TTPERM, 1, NULLP, hiScanPermTsk);
#endif
#ifdef IT
   SRegTTsk(ENTIT, TSTINST, TTNORM, 0, itSbActvInit, itSbActvTsk);
#endif
#ifdef SM
   SRegTTsk(ENTSM, TSTINST, TTNORM, 0, smActvInit, smActvTsk);
#endif

#if defined (SB_PRFM_SNDR) || (SB_PRFM_RCVR)
   /* This task will be added for Performance Testing purpose */
   SRegTTsk(ENTSB, 1, TTPERM, 1, sbPermTskInit, sbPermTsk);
#endif

      /* create a single system thread */
      SCreateSTsk(0, &tskId);
      /* create a second TUCL system thread */
#ifdef SS_SINGLE_THREADED 
      /* create a second TUCL system thread */
      SCreateSTsk(0, &tuclTskId);
      SCreateSTsk(0, &testTskId);
      SCreateSTsk(1, &hiPermTskId);
#endif

      /* attach all TAPA tasks to the same system thread */
#ifdef SB
      SAttachTTsk(ENTSB, TSTINST, tskId);
#endif
#ifdef HI
      SAttachTTsk(ENTHI, TSTINST, tskId);
      SAttachTTsk(ENTHI, TSTINST+1, tskId);
#endif
#ifdef IT
      SAttachTTsk(ENTIT, TSTINST, tskId);
#endif
#ifdef SM
      SAttachTTsk(ENTSM, TSTINST, tskId);
#endif
#if defined (SB_PRFM_SNDR) || (SB_PRFM_RCVR)
      SAttachTTsk(ENTSB, 1, tskId);
#endif
#endif

   RETVALUE(ROK);
} /* tst */







/*
*
*       Fun:   sbIBPrintMenu
*
*       Desc:  Print Menu
*
*       Ret:   None.
*
*       Notes: None
*
*       File:  sb_acc1.c
*
*/
#ifdef ANSI
PRIVATE Void sbIBPrintMenu
(
Void
)
#else
PRIVATE Void sbIBPrintMenu()
#endif
{
   Txt pBuf[100];

   TRC2(sbIBPrintMenu);

    sprintf(pBuf, "Available commands are:\n");
    SPrint(pBuf);
    sprintf(pBuf, " abort assocIdx\t\t\t\t - Abort the association\n");
    SPrint(pBuf);
    sprintf(pBuf, " addrstatus address assocIdx\t\t - return destination address status\n");
    SPrint(pBuf);
    sprintf(pBuf, " assoc endpIdx\t\t\t\t - open association with the set destination\n");
    SPrint(pBuf);
    sprintf(pBuf, " assoclist \t\t\t\t - List of All Current Established Associations\n");
    SPrint(pBuf);
    sprintf(pBuf, " assocstatus assocIdx\t\t\t - return association status\n");
    SPrint(pBuf);
    sprintf(pBuf, " bulkdata size assocIdx\t\t\t - send data from file on established association\n");
    SPrint(pBuf);
    sprintf(pBuf, " data string assocIdx\t\t\t - send string on established association\n");
    SPrint(pBuf);
    sprintf(pBuf, " endplist \t\t\t\t - List of All Current Open End Points\n");
    SPrint(pBuf);
    sprintf(pBuf, " endpclose endpIdx\t\t\t - Close a particualar End Point\n");
    SPrint(pBuf);
    sprintf(pBuf, " filedata on/off\t\t\t - send received data to file (datarx.file) \n");
    SPrint(pBuf);
    sprintf(pBuf, " help\t\t\t\t\t - print the command menu\n");
    SPrint(pBuf);
    sprintf(pBuf, " hbeat on/off assocIdx [interval]\t - Turn HB on or off  to the destination\n");
    SPrint(pBuf);
    sprintf(pBuf, " hbaddr on/off assocIdx dstAdr [interval]- Turn HB on or off  to the destination addr\n");
    SPrint(pBuf);
    sprintf(pBuf, " initsctp\t\t\t\t - Initialize the SCTP layer\n");
    SPrint(pBuf);
    sprintf(pBuf, " loopdata size assocIdx times\t\t - send data on an association from data.file\n");
    SPrint(pBuf);
    sprintf(pBuf, " openendp\t\t\t\t - open a socket with well known port\n");
    SPrint(pBuf);
    sprintf(pBuf, " ping assocIdx\t\t\t\t - send ping-echo on established assocation\n");
    SPrint(pBuf);
    sprintf(pBuf, " quit\t\t\t\t\t - exit the program\n");
    SPrint(pBuf);
    sprintf(pBuf, " rtrvstatus assocIdx\t\t\t - return inqueue data status\n");
    SPrint(pBuf);
    sprintf(pBuf, " sendfile filename assocIdx\t\t - Send file to peer\n");
    SPrint(pBuf);
    sprintf(pBuf, " showpktcnt\t\t\t\t - Show the Current Packet count \n");
    SPrint(pBuf);
    sprintf(pBuf, " setpri address assocIdx\t\t - Set primary destination address\n");
    SPrint(pBuf);
    sprintf(pBuf, " shutdown assocIdx\t\t\t - gracefully shutdown the association\n");
    SPrint(pBuf);
    sprintf(pBuf, " trace on/off\t\t\t\t - Turn on or off message trace\n");
    SPrint(pBuf);
    sprintf(pBuf, " verbose on/off\t\t\t\t - Turn on or off debug prints on display\n");
    SPrint(pBuf);
#ifdef SB_DETAILED_INFO
    sprintf(pBuf, " displinfo assocIdx\t\t\t - Display Information about association\n");
    SPrint(pBuf);
#endif
    sprintf(pBuf, " stats {gen/tsap/sctsap}\t\t - Display General Statistical Information\n");
    SPrint(pBuf);


   RETVOID;

} /* sbIBPrintMenu */


/*
 *
 *      Fun:   sbIBParseMenu
 *
 *      Desc:  This function parses the menu option selected
 *
 *      Ret:   RETVOID,
 *
 *      Notes: None.
 *
 *      File:  sb_acc1.c
 *
 */

#ifdef ANSI
PRIVATE Void sbIBParseMenu
(
TstTkn     *tkn             /* Command Name */
)
#else
PRIVATE Void sbIBParseMenu(tkn)
TstTkn     *tkn;            /* Command Name */
#endif
{
   Txt  pBuf[100];
   S32  cmd;
   CmNetAddr   nAddr;
   U16  length,i,tmp;
   Bool assocFlag=FALSE;
   Bool addrFlag=FALSE;
   U16    assocIdx,times;


   TRC2(sbIBParseMenu)

   cmd = osMatchKeyword(sbMenuKw, (S8 *)tkn->tok.val);

   switch (cmd)
   {
      case  0:   /* abort */
         if (tkn->nmbArgs == 0 )
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** abort assocIdx **\n");
           SPrint(pBuf);
           break;
         }
         tmp = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);

         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }
         if(endp[assocReq[tmp].endpIdx].cfgDone != TRUE)
         {
           sprintf(pBuf, "Error : ** EndPoint Configuration Not Done **\n");
           SPrint(pBuf);
         }
         else
         {
          ItLiSctTermReq(&endp[assocReq[tmp].endpIdx].pst,assocReq[tmp].spId,
               assocReq[tmp].spAssocId, SCT_ASSOCID_SP,TRUE);
         }
         break;

      case  1:   /* addrstatus */
         if(tkn->nmbArgs != 2)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** addrstatus destinationAddr assocIndex **\n");
           SPrint(pBuf);
           break;
         }

         tmp = sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);

         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }

         nAddr.type= assocReq[tmp].dstNetAddr.type;
         nAddr.u.ipv4NetAddr = ntohl(inet_addr((CONSTANT S8*)tkn->args[0].val));
         ItLiSctStaReq(&endp[assocReq[tmp].endpIdx].pst, assocReq[tmp].spId,
                assocReq[tmp].spAssocId, &nAddr, SCT_GET_ADDR_INFO);
         break;

      case  2:   /* assoc */
         if (tkn->nmbArgs == 0 )
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** assoc endpIdx **\n");
           SPrint(pBuf);
           break;
         }
         tmp = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);

         if((tmp > MAXBLOCKS) || (!endp[tmp].occupied))
         {
           sprintf(pBuf, " Error : ** Index Invalid/End Point Unoccupied **\n");
           SPrint(pBuf);
         }
         sbIPAssocReq(tmp);
         break;

      case  3:   /* assoclist */
       { 
         Bool assocFnd=FALSE;

         for(i=0;i<MAXBLOCKS;i++)
         {
             if(assocReq[i].occupied)
             {
                assocFnd = TRUE;
                sprintf(pBuf, "**** Association block %d ****\n",i);
                SPrint(pBuf);
                sbICPrntData(ASSOCREQ,i);
             }
         }
         if(assocFnd != TRUE )
         {
          sprintf(pBuf, " No Association Exists \n");
          SPrint(pBuf);
         } 
       }
        break;

      case  4:   /* assocstatus */
         if(tkn->nmbArgs == 0)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** assocstatus assocIndex **\n");
           SPrint(pBuf);
           break;
         }
         tmp = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);

         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }

         nAddr.type= assocReq[tmp].dstNetAddr.type;
         nAddr.u.ipv4NetAddr = assocReq[tmp].dstNetAddr.u.ipv4NetAddr;
         ItLiSctStaReq(&endp[assocReq[tmp].endpIdx].pst, assocReq[tmp].spId,
                assocReq[tmp].spAssocId, &nAddr, SCT_GET_ASSOC_INFO);
         break;

      case  5:   /* bulkdata */
         if (tkn->nmbArgs != 2 )
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** bulkdata size assocIdx [strmId]  **\n");
           SPrint(pBuf);
           break;
         }
         length = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);
         tmp = sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);

         if((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }
         sbIPBulkDataReq(length,tmp,NORMAL_DATA);
         break;

     case  6:   /* loopdata */
         if (tkn->nmbArgs != 3 )
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** loopdata size assocIdx times  **\n");
           SPrint(pBuf);
           break;
         }
         length = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);
         tmp = sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);
         times = sbISStrtoul((S8*)tkn->args[2].val, NULLP, NULLP);
        
         if((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }

         for(i=0; i<times; i++) 
         {
           sbIPBulkDataReq(length,tmp,PKTCNT_DATA);
           sleep(0);
         }

         /* If times is 0 then send data infinite times. */
         if(times == 0 )
         {
           while(1)
           {
             sbIPBulkDataReq(length,tmp,PKTCNT_DATA);
             sleep(0);
           }          
         }
         break;

      case  7:   /* data */
         if(tkn->nmbArgs != 2)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** data String assocIndex **\n");
           SPrint(pBuf);
           break;
         }
         tmp = sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);
         if((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }
         sbIPDataReq((U8*)tkn->args[0].val,tkn->args[0].len,tmp);
         break;

      case  8:   /* endplist */
       {
         Bool endpFnd=FALSE;
         for(i=0;i<MAXBLOCKS;i++)
         {
             if(endp[i].occupied)
             {
                sprintf(pBuf,"**** End Point block %d ****\n",i);
                SPrint(pBuf);
                sbICPrntData(ENDPREQ,i);
             }
         }
         if(endpFnd != TRUE )
         {
          sprintf(pBuf, " No End Point  Exists \n");
          SPrint(pBuf);
         } 
       }
       break;

      case  9:   /* endpclose */
         if (tkn->nmbArgs == 0 )
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** endpclose endpIdx **\n");
           SPrint(pBuf);
           break;
        }
         tmp = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);

         if((tmp > MAXBLOCKS) || (!endp[tmp].occupied))
         {
           sprintf(pBuf, " Error : ** Index Invalid/End Point Unoccupied **\n");
           SPrint(pBuf);
           break;
         }
         for(i=0;i<MAXBLOCKS;i++)
         {
          if((assocReq[i].occupied)  && (assocReq[i].endpIdx == tmp))
          {
           sprintf(pBuf, "**** Association block %d Exist for EndPoint ****\n",i);
           SPrint(pBuf);
           assocFlag = TRUE;
          }
         }
         if(assocFlag)
         {
            assocFlag=FALSE;
            break;
         }

         ItLiSctEndpCloseReq(&endp[tmp].pst, endp[tmp].spId, endp[tmp].spEndpId,
                                       SCT_ENDPID_SP);
         break;

      case 10:   /* filedata */
         if(tkn->nmbArgs != 1)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** filedata on/off **\n");
           SPrint(pBuf);
           break;
         }

         if ((osStrncmp((S8 *)tkn->args[0].val, "on", tkn->args[0].len) == 0))
         {
            filedata = TRUE;
         }
         else if ((osStrncmp((S8 *)tkn->args[0].val, "off", tkn->args[0].len) == 0))
         {
            filedata = FALSE;
         }
         else
         {
           sprintf(pBuf, " Error : ** Incorrect input **\n");
           SPrint(pBuf);
         }
         break;

      case 11:   /* help */
         sbIBPrintMenu();
         break;

      case 12:   /* hbeat */
         if(tkn->nmbArgs < 2 || tkn->nmbArgs > 3)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** heartbeat on/off  assocIndex [interval] **\n");
           SPrint(pBuf);
           break;
         }

         tmp = sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);

         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }

         if (!assocReq[tmp].assocDone)
         {
           sprintf(pBuf, " Error : ** Assocication Not Done **\n");
           SPrint(pBuf);
           break;
         }

         nAddr.type= assocReq[tmp].dstNetAddr.type;
         nAddr.u.ipv4NetAddr = assocReq[tmp].dstNetAddr.u.ipv4NetAddr;

         if (nAddr.u.ipv4NetAddr == 0)
         {
            nAddr.type = CM_NETADDR_NOTPRSNT;
            assocFlag = TRUE;
         }

         if(tkn->nmbArgs == 2)
         i = 5;
         else if(tkn->nmbArgs == 3)
            i = sbISStrtoul((S8*)tkn->args[2].val, NULLP, NULLP);
   
         if ((osStrncmp((S8 *)tkn->args[0].val, "on", tkn->args[0].len) == 0))
         {
           ItLiSctHBeatReq(&endp[assocReq[tmp].endpIdx].pst,assocReq[tmp].spId,
              assocReq[tmp].spAssocId, &nAddr, i, SCT_HBEAT_ENB_ASSOC);
           sprintf(pBuf, " HeartBeat Enabled\n");
           SPrint(pBuf);
           break;
         }
         else if ((osStrncmp((S8 *)tkn->args[0].val, "off", tkn->args[0].len) == 0))
        {
           ItLiSctHBeatReq(&endp[assocReq[tmp].endpIdx].pst,assocReq[tmp].spId,
                 assocReq[tmp].spAssocId, &nAddr, i, SCT_HBEAT_DIS_ASSOC);
           sprintf(pBuf, " HeartBeat Disabled\n");
           SPrint(pBuf);

           break;
         }
         else
         {
           sprintf(pBuf, " Error : ** Incorrect input **\n");
           SPrint(pBuf);
         }
         break;

      case 13:   /* hbaddr */
         if(tkn->nmbArgs < 2 || tkn->nmbArgs > 3)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** hbaddr on/off  asocIdx dstAdr [interval] **\n");
           SPrint(pBuf);
           break;
         }

         tmp = sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);
         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }
         if (!assocReq[tmp].assocDone)
         {
           sprintf(pBuf, " Error : ** Association Not Done **\n");
           SPrint(pBuf);
           break;
         }
         nAddr.type= assocReq[tmp].dstNetAddr.type;
         nAddr.u.ipv4NetAddr = ntohl(inet_addr((CONSTANT S8*)tkn->args[2].val));

         /* search for given IP address in destination IP address list */
         addrFlag = FALSE;
         for(i=0; i<assocReq[tmp].dstNAddrLst.nmb; i++)
         {
             if(nAddr.u.ipv4NetAddr == assocReq[tmp].dstNAddrLst.nAddr[i].u.ipv4NetAddr)
             {
                 addrFlag = TRUE;
                 nAddr.type = assocReq[tmp].dstNAddrLst.nAddr[i].type;
                 break;
             }
         }
         if(addrFlag == FALSE)
         {
             SPrint("sb_ibdy.c : Can't find entered IP address in destination IP address list\n");
             break;
         }
         if(tkn->nmbArgs == 3)
             i = 5;
        else if(tkn->nmbArgs == 4)
            i = sbISStrtoul((S8*)tkn->args[2].val, NULLP, NULLP);
   
         if ((osStrncmp((S8 *)tkn->args[0].val, "on", tkn->args[0].len) == 0))
         {
           sprintf(pBuf, " Enable HeartBeat\n");
           SPrint(pBuf);

           ItLiSctHBeatReq(&endp[assocReq[tmp].endpIdx].pst,assocReq[tmp].spId,
              assocReq[tmp].spAssocId, &nAddr, i, SCT_HBEAT_ENB_DTA);
           break;
         }
         else if ((osStrncmp((S8 *)tkn->args[0].val, "off", tkn->args[0].len) == 0))
        {
           sprintf(pBuf, " Disable HeartBeat\n");
           SPrint(pBuf);

          ItLiSctHBeatReq(&endp[assocReq[tmp].endpIdx].pst,assocReq[tmp].spId,
                 assocReq[tmp].spAssocId, &nAddr, i, SCT_HBEAT_DIS_DTA);
           break;
         }
         else
         {
           sprintf(pBuf, " Error : ** Incorrect input **\n");
           SPrint(pBuf);
         }
         break;

      case 14:   /* initsctp */
         sbIPInitSctp();
         break;

      case 15:   /* openendp */
         sbIPEndpOpenReq();
         break;

      case 16:   /* ping */
         if(tkn->nmbArgs != 1)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** ping assocIndex **\n");
           SPrint(pBuf);
           break;
        }
         tmp = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);
         if((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }
        length = 100;
         sbIPBulkDataReq(length,tmp,PING_REQ);
         break;

      case 17:   /* rtrvstatus */
         if(tkn->nmbArgs != 1)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** rtrvstatus assocIndex **\n");
           SPrint(pBuf);
           break;
        }
         tmp = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);

         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }
         nAddr.type= assocReq[tmp].dstNetAddr.type;
         nAddr.u.ipv4NetAddr = assocReq[tmp].dstNetAddr.u.ipv4NetAddr;
         ItLiSctStaReq(&endp[assocReq[tmp].endpIdx].pst, assocReq[tmp].spId,
              assocReq[tmp].spAssocId, &nAddr, SCT_GET_RTRV_INFO);
         break;

      case 18: /* sendfile */
         if (tkn->nmbArgs != 2 )
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** sendfile Filename assocIndex**\n");
           SPrint(pBuf);
           break;
        }

         assocIdx = sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);
         if((assocIdx > MAXBLOCKS) || (!assocReq[assocIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }

        sbIPSendFile((Txt)tkn->args[0].val, assocIdx);
        break;

     case 19:   /* showpktcnt */
         sprintf(pBuf,"*PkT Count is %ld -Million : %ld *\n", pktCount, pktThousand);
         SPrint(pBuf);
         break;

     case 20:   /* setfreq */
         break;

      case 21:   /* setpri */
         if(tkn->nmbArgs != 2)
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** setpri destAddr  assocIndex **\n");
           SPrint(pBuf);
           break;
        }

         tmp = sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);

         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }

         nAddr.type= assocReq[tmp].dstNetAddr.type;
         nAddr.u.ipv4NetAddr = ntohl(inet_addr((CONSTANT S8*)tkn->args[0].val));


         if (!assocReq[tmp].assocDone)
         {
           sprintf(pBuf, " Error : ** Assocication Not Done **\n");
           SPrint(pBuf);
           break;
         }

         ItLiSctSetPriReq(&endp[assocReq[tmp].endpIdx].pst, assocReq[tmp].spId,
                  assocReq[tmp].spAssocId, &nAddr);
         break;

      case 22:   /*shutdown */
         if (tkn->nmbArgs == 0 )
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** shutdown assocIdx **\n");
           SPrint(pBuf);
           break;
        }
         tmp = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);

         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }
        if(endp[assocReq[tmp].endpIdx].cfgDone != TRUE)
        {
           sprintf(pBuf, "Error : ** EndPoint Configuration Not Done **\n");
           SPrint(pBuf);
         }
        else
         {
          ItLiSctTermReq(&endp[assocReq[tmp].endpIdx].pst,assocReq[tmp].spId,
               assocReq[tmp].spAssocId, SCT_ASSOCID_SP,FALSE);
         }
         break;

      case 23:   /* trace */
         if(tkn->nmbArgs == 0 )
         {
           sprintf(pBuf, " Error : ** Enter ON/OFF status **\n");
           SPrint(pBuf);
           break;
        }

         if ((osStrncmp((S8 *)tkn->args[0].val, "on", tkn->args[0].len) == 0))
        {
            Pst   pst;
            SbMgmt  sbMgmt;

            sprintf(pBuf, " Enable Message Trace \n");
            SPrint(pBuf);

            sbIBGetLmPst(&pst); 
            sbMgmt.hdr.elmId.elmnt =  STSBGEN;
            sbMgmt.hdr.response.selector = 1;
            sbMgmt.t.cntrl.action = AENA;
            sbMgmt.t.cntrl.subAction = SATRC;
            (Void) SmMiLsbCntrlReq(&pst, &sbMgmt);
            break;
         }
         else if ((osStrncmp((S8 *)tkn->args[0].val, "off", tkn->args[0].len) == 0))
        {
            Pst   pst;
            SbMgmt  sbMgmt;

            sprintf(pBuf, " Disable Message Trace\n");
            SPrint(pBuf);

            sbIBGetLmPst(&pst); 
            sbMgmt.hdr.elmId.elmnt =  STSBGEN;
            sbMgmt.hdr.response.selector = 1;
            sbMgmt.t.cntrl.action = ADISIMM;
            sbMgmt.t.cntrl.subAction = SATRC;
            (Void) SmMiLsbCntrlReq(&pst, &sbMgmt);
            break;
         }
         else
         {
           sprintf(pBuf, " Error : ** Incorrect input **\n");
           SPrint(pBuf);
         }
         break;

      case 24:   /* verbose */
         if(tkn->nmbArgs == 0 )
         {
           sprintf(pBuf, " Error : ** Enter ON/OFF status **\n");
           SPrint(pBuf);
           break;
        }

         if ((osStrncmp((S8 *)tkn->args[0].val, "on", tkn->args[0].len) == 0))
        {
            Pst   pst;
            SbMgmt  sbMgmt;

           optDebug = 1;

           sprintf(pBuf, " Enable Debug prints\n");
           SPrint(pBuf);

           sbIBGetLmPst(&pst); 
           sbMgmt.hdr.elmId.elmnt =  STSBGEN;
           sbMgmt.hdr.response.selector = 1;
           sbMgmt.t.cntrl.action = AENA;
           sbMgmt.t.cntrl.subAction = SADBG;
#ifdef DEBUGP
           sbMgmt.t.cntrl.dbgMask = 0xFFFFFFFF;
#endif
           (Void) SmMiLsbCntrlReq(&pst, &sbMgmt);
           break;
         }
         else if ((osStrncmp((S8 *)tkn->args[0].val, "off", tkn->args[0].len) == 0))
        {
            Pst   pst;
            SbMgmt  sbMgmt;

           optDebug = -1;

           sprintf(pBuf, " Disable Debug prints\n");
           SPrint(pBuf);
           
           sbIBGetLmPst(&pst); 
           sbMgmt.hdr.elmId.elmnt =  STSBGEN;
           sbMgmt.hdr.response.selector = 1;
           sbMgmt.t.cntrl.action = ADISIMM;
           sbMgmt.t.cntrl.subAction = SADBG;
#ifdef DEBUGP
           sbMgmt.t.cntrl.dbgMask = 0xFFFFFFFF;
#endif
           (Void) SmMiLsbCntrlReq(&pst, &sbMgmt);
           break;
         }
         else
         {
           sprintf(pBuf, " Error : ** Incorrect input **\n");
           SPrint(pBuf);
         }
         break;

      case 25:   /* displinfo */

#ifdef SB_DETAILED_INFO
         if (tkn->nmbArgs == 0 )
         {
           sprintf(pBuf, " Error : ** Token Missing **\n");
           SPrint(pBuf);
           sprintf(pBuf, " Usage : ** displinfo assocIdx **\n");
           SPrint(pBuf);
           break;
        }
         tmp = sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);

         if ((tmp > MAXBLOCKS) || (!assocReq[tmp].occupied) ||
                                  (!endp[assocReq[tmp].endpIdx].occupied))
         {
           sprintf(pBuf, " Error : ** assocIdx out of Range/AssocBlock Empty **\n");
           SPrint(pBuf);
           break;
         }
         sbIBDsplAssocInfo(tmp);
#endif

         break;

      case 26:   /* stats */
         { 
           Pst   pst;
           SbMgmt  sbMgmt;

           if (tkn->nmbArgs == 0 )
           {
             sprintf(pBuf, " Error : ** Token Missing **\n");
             SPrint(pBuf);
             sprintf(pBuf, " Usage : ** stats {gen/tsap/sctsap} **\n");
             SPrint(pBuf);
             break;
          }

           sbIBGetLmPst(&pst);

           if( osStrcmp((S8*)tkn->args[0].val, "gen") == 0)
              sbMgmt.hdr.elmId.elmnt =  STSBGEN;
           else if( osStrcmp((S8*)tkn->args[0].val, "tsap") == 0)
              sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
           else if( osStrcmp((S8*)tkn->args[0].val, "sctsap") == 0)
              sbMgmt.hdr.elmId.elmnt =  STSBSCTSAP;
           else
           {
              sprintf(pBuf, " Error : ** Incorrect input **\n");
              SPrint(pBuf);
              break;
           }

#ifdef LCSBMILSB
           sbMgmt.hdr.response.selector = SEL_LC;
#else
           sbMgmt.hdr.response.selector = SEL_TC;
#endif
           (Void) SmMiLsbStsReq(&pst, 0, &sbMgmt);
           break;
         }
      case 27:   /* quit */
         exit(0);

      default:
         sprintf(pBuf, " Unknown Command : Type help For Menu  \n");
         SPrint(pBuf);
         break;
   }

   RETVOID;
} /* end of sbIBParseMenu */


/*
*
*       Fun:   sbIBLineToTkn
*
*       Desc:  Convert Line format to Token Format
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
PRIVATE S16 sbIBLineToTkn
(
S8           *line,
TstTkn       *tkn
)
#else
PRIVATE S16 sbIBLineToTkn(line, tkn)
S8           *line;
TstTkn       *tkn;
#endif
{
   S8 *lPtr;
   S8 word[20];
   S32 i;

   TRC2(sbIBLineToTkn)

   lPtr = osGetWord(line, word);

   if (osStrlen(word) >= sizeof(tkn->tok.val)) /* make sure there's room */
      RETVALUE(-1);

   osStrcpy((S8*)tkn->tok.val, word);

   tkn->tok.pres = TRUE;
   tkn->tok.len = osStrlen((S8 *)tkn->tok.val);
   tkn->nmbArgs = 0;

   for (i = 0; i < MAXARGS; i++)
   {
      lPtr = osGetWord(lPtr, word);

      if (osStrlen(word) >= sizeof(tkn->tok.val)) /* make sure there's room */
         RETVALUE(-1);

      if (*word == '\0' || *word == '#') /* end of line or comment */
      {
         tkn->args[i].pres = FALSE;
         break;
      }

      osStrcpy((S8 *)tkn->args[i].val, word);
      tkn->args[i].pres = TRUE;
      tkn->args[i].len = osStrlen((S8*)tkn->args[i].val);
      tkn->nmbArgs++;
   }

   RETVALUE(tkn->nmbArgs);

} /* end of sbIBLineToTkn */


/*
*
*       Fun:   rdConQ
*
*       Desc:  Reads the console queue.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  sb_acc1.c
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
   TstTkn    tkn;

   TRC2(rdConQ)

#ifdef DOS
   /* check if control-c */
   if (data == 0x03)
      exit(0);
#else
#ifdef UNIX
   sbCmdArgs[sbCmdLen++] = data;
  
   if ((data == '\n') || (data == '\0'))
   {
      sbIBLineToTkn((S8*)sbCmdArgs, &tkn);
      sbIBParseMenu(&tkn);
      sbCmdLen = 0;
      cmMemset((U8 *)sbCmdArgs, 0, MAXCMDLEN);
   }
#else
#endif
#endif

   RETVALUE(OK);
} /* end of rdConQ */



/*
*
*       Fun:   sbIBGetLmPst
*
*       Desc:  Fills the lmPst structure. For alarms addressed to the layer manager.
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_ibdy.c
*
*/

#ifdef ANSI
PUBLIC  Void  sbIBGetLmPst
(
Pst *lmPst
)
#else
PUBLIC  Void sbIBGetLmPst(lmPst)
Pst  *lmPst;          /* pointer to lmPst structure */
#endif
{
   TRC2(sbIBGetLmPst)

   
   lmPst->dstProcId = SFndProcId();  /* dst proc id */
   lmPst->srcProcId = SFndProcId();  /* src proc id */
   lmPst->dstEnt    = ENTSB;         /* dst entity */
   lmPst->dstInst   = 0;             /* dst inst */
   lmPst->srcEnt    = ENTSM;         /* src entity */
   lmPst->srcInst   = 0;             /* src inst */
   
   lmPst->region    = 0;              /* region */
   lmPst->pool      = 0;              /* pool */
   lmPst->prior     = 0;             /* priority */
   lmPst->route     = 0;              /* route */

#ifdef LCSMSBMILSB
   lmPst->selector  = SEL_LC;
#else
   lmPst->selector  = SEL_TC;
#endif

   RETVOID;

} /* sbIBGetLmPst */

/*
*
*       Fun:   sbIBGetLmPst
*
*       Desc:  Fills the lmPst structure. For alarms addressed to the layer manager.
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  sb_ibdy.c
*
*/

#define DUMP_FILE(_tskInit, _layerName, _msgClass, _arg) \
        { \
          OsFile    *cfin; \
          sprintf((_tskInit)->prntBuf, "[%s 0x%x:%x] %s:%d ", \
                 _layerName, (_tskInit)->ent, (_tskInit)->inst, \
                 __FILE__, __LINE__); \
          sprintf _arg; \
         if ((cfin = (OsFile*)osFopen("debug.log", "a+")) == (S32)NULLP) \
         {   \
           osPrintf("%s(%d): Can't open file for write ,File=:%s\n", __FILE__, __LINE__, "debug.log");\
         }   \
         if ((len = osFwrite((_tskInit->prntBuf), 1, cmStrlen(_tskInit->prntBuf), cfin)) != cmStrlen(_tskInit->prntBuf))  \
         {   \
           osPrintf("%s(%d): File write error ,File=:%s\n", __FILE__, __LINE__, "debug.log"); \
         }  \
        }


/*
*
*       Fun:   Activate Task - initialize
*
*       Desc:  Invoked by system services to initialize a task.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ibdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbPermTskInit
(
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason               /* reason */
)
#else
PUBLIC S16 sbPermTskInit(ent, inst, region, reason)
Ent      ent;                 /* entity */
Inst     inst;                /* instance */
Region   region;              /* region */
Reason   reason;              /* reason */
#endif
{
   TRC3(sbPermTskInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);

   /* save initialization parameters */

   RETVALUE(ROK);

} /* end of sbPermTskInit */


/*
*
*       Fun:    activate permanent task
*
*       Desc:   Processes received primitives from the SCTP layer.
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   sb_ibdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbPermTsk
(
Pst       *pst,         /* post */
Buffer    *mBuf         /* message buffer */
)
#else
PUBLIC S16 sbPermTsk(pst, mBuf)
Pst       *pst;         /* post */
Buffer    *mBuf;        /* message buffer */
#endif
{
   Txt    prntBuf[SB_PRNTBUF_SIZE];
  
  PRIVATE U8 start=0;
  U16    assocIdx;

   TRC3(sbPermTsk)

   /* Initialise SCTP layer */
   if(start == 0)
   {
     sbIPInitSctp();
     start =1;
     sleep(2);
     RETVALUE(ROK);
   }
   if (start == 1)
   {
     sbIPEndpOpenReq();
     start =2;
     sleep(1);  
     RETVALUE(ROK);
   }
   if (start == 2)
   {
     Pst   lmPst;
     SbMgmt  sbMgmt;
     sbIBGetLmPst(&lmPst); 
     sbMgmt.hdr.elmId.elmnt =  STSBGEN;
     sbMgmt.hdr.response.selector = 1;
     sbMgmt.t.cntrl.action = ADISIMM;
     sbMgmt.t.cntrl.subAction = SADBG;
#ifdef DEBUGP
     sbMgmt.t.cntrl.dbgMask = 0xFFFFFFFF;
#endif
     (Void) SmMiLsbCntrlReq(&lmPst, &sbMgmt);
     start =3;
     sleep(1);  
     RETVALUE(ROK);
   }

   if(endp[0].cfgDone != TRUE)
   {
    sprintf(prntBuf, "EndpOpen Not Done \n");
    SPrint(prntBuf);
    RETVALUE(ROK);
   }

#ifdef SB_PRFM_SNDR

   if((start == 3) && (assocReq[0].occupied != TRUE))
   {
     sbIPAssocReq(0);
     sleep(2);
     start = 4;
   }

   assocIdx =0; 
   
   if(assocReq[assocIdx].assocDone != TRUE )
   {
    if(start == 5)
     exit(0); 
    sprintf(prntBuf, "Assoc Not Done \n");
    SPrint(prntBuf);
    RETVALUE(ROK);
   }
   
   if( FLCpause != TRUE)
     sbIPPerfDataReq(assocIdx);
    
   start=5;

#endif

/* 
   if(messagerate == 0)
   {
      sprintf(prntBuf, "Entering Termination Message Rate : %d \n",messagerate);
      SPrint(prntBuf);

      ItLiSctTermReq(&endp[0].pst,assocReq[0].spId,
              assocReq[0].spAssocId, SCT_ASSOCID_SP, FALSE);
     
      ItLiSctEndpCloseReq(&endp[0].pst, endp[0].spId, endp[0].spEndpId,
                                     SCT_ENDPID_SP);
      exit(0);
   }
*/ 
   
   RETVALUE(ROK);
} /* End of sbPermTsk */


#ifdef SB_DETAILED_INFO


/*
*
*       Fun:   sbIBDsplAssocInfo
*
*       Desc:  Display Association Information from AssocCb.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  sb_ibdy.c
*
*/

#ifdef ANSI
PUBLIC S16 sbIBDsplAssocInfo 
(
U16 assocIdx 
)
#else
PUBLIC S16 sbIBDsplAssocInfo(assocIdx)
U16 assocIdx;
#endif
{
   SbSctAssocCb         *assocCb;
   CmLListCp            *l1;
   CmLListCp            *l;
   CmLListCp            *l2;
   CmLList              *n;                    /* linked list */
   SbAddrCb             *tmpAddrCb;            /* temporary pointer */
   Txt pBuf[100];


   /* get the association control block */
   assocCb = sbGlobalCb.assocCb[assocReq[assocIdx].spAssocId];
   l1 = &(assocCb->sbDbCb.congestionQ);
   l2 = &(assocCb->sbDbCb.tsnWaitingQOrd);

   sprintf(pBuf, "===========================================================\n");
   SPrint(pBuf);
   sprintf(pBuf, "Number of OutStreams: %d \n", assocCb->sbSqCb.nmbOutStreams);
   SPrint(pBuf);
   sprintf(pBuf, "Number of InStreams: %d \n", assocCb->sbSqCb.nmbInStreams);
   SPrint(pBuf);
   sprintf(pBuf, "Recvr Window Size(rwnd): %d \n", assocCb->sbAcCb.rwnd);
   SPrint(pBuf);
   sprintf(pBuf, "Bytes Out on Association(rwnd): %d \n", assocCb->sbAcCb.bytesOut);
   SPrint(pBuf);
   sprintf(pBuf, "Own Recvr Window Size(ownRwnd): %d \n", assocCb->sbAcCb.ownRWnd);
   SPrint(pBuf);
   sprintf(pBuf, "Length of congestionQ: %d \n", cmLListLen( l1 ));
   SPrint(pBuf);
   sprintf(pBuf, "Length of TSN-Waiting Q: %d \n", cmLListLen( l2 ));
   SPrint(pBuf);

   l = &(assocCb->sbAcCb.addrLst);
   n = cmLListFirst(l);
   while ( n != NULLP )
   {
      tmpAddrCb = (SbAddrCb *) n->node;
      
      sprintf(pBuf, "----------------------------------------\n");
      SPrint(pBuf);
      sprintf(pBuf, " Addrs Info for Addr: %x\n",tmpAddrCb->addr.u.ipv4NetAddr);
      SPrint(pBuf);
      sprintf(pBuf, " Congestion window Size: %ld \n", (U32) tmpAddrCb->cwnd);
      SPrint(pBuf);
      sprintf(pBuf, " Ss-Threshold Value: %ld \n", (U32) tmpAddrCb->ssthresh);
      SPrint(pBuf);
      sprintf(pBuf, " Addrs status : %s\n",tmpAddrCb->active ? "ACTIVE" : "INACTIVE");
      SPrint(pBuf);
      sprintf(pBuf, " Addr RtxCount : %d\n",tmpAddrCb->rtxCnt);
      SPrint(pBuf);
      sprintf(pBuf, " Addr bytesOut : %d\n",tmpAddrCb->bytesOut);
      SPrint(pBuf);
      sprintf(pBuf, " Addr bytesAcked : %d\n",tmpAddrCb->bytesAcked);
      SPrint(pBuf);
      sprintf(pBuf, " Addrs RTO Timer : %s\n",
            ((tmpAddrCb->t3rtx.tmrEvnt != TMR_NONE) ? "RUNNING" : "NOT RUNNING"));
      SPrint(pBuf);
      n = cmLListNext(l);
   }      
   sprintf(pBuf, "===========================================================\n");
   SPrint(pBuf);
   
   RETVALUE(ROK);

}


#endif


/********************************************************************30**

         End of file:     sb_ibdy.c@@/main/2 - Thu Jul 26 07:54:13 2007

*********************************************************************31*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sb    1. File Added for inter-op SCTP Testing 
/main/2      ---    rsr/ag  1. Updated for Release of 1.3  
*********************************************************************91*/
