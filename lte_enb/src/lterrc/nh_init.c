


/**********************************************************************
  
     Name:     RRC Layer
 
     Type:     C source file
  
     Desc:     Initialisation of RRC task

     File:     nh_init.c
  
     Sid:      ni_init.c@@/main/3 - Fri Jul  1 01:13:19 2011
   
     Prg:      dsahoo
  
**********************************************************************/




/* Header include files (.h) */



#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"

#include "cm_tkns.h"       /* Common Token defines */
#include "cm_mblk.h"       /* Common Mem Allocation defines */
#include "cm_llist.h"      /* Common Link List defines */
#include "cm_hash.h"       /* Common Hashlist defines */
#include "cm_pasn.h"       /* Common Pasn defines */
#include "cm_lte.h"        /* Common Pasn defines */

#include "nhu.h"           /* RRU Interface defines */
#include "lnh.h"           /* LRR Interface defines */

#include "nh.h"            /* RRC defines */

/* Header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm5.x"
#include "cm_tkns.x"       /* Common Token definitions */
#include "cm_mblk.x"       /* Common Memory Allocation */
#include "cm_llist.x"      /* Common Link List definitions */
#include "cm_hash.x"       /* Common Hashlist definitions */
#include "cm_lib.x"        /* Common Library definitions */
#include "cm_pasn.x"       /* Common Hashlist definitions */
#include "cm_lte.x"       /* Common Pasn defines */

#include "nhu.x"           /* RRU Interface includes */
#include "lnh.x"           /* LRR Interface includes */

#include "nh.x"            /* RRC includes */

#ifdef LTE_RRC_DISSECTOR
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include "cm_inet.h"
#include "cm_inet.x"
/*#include "brcm_tx_fastpath.h"*/
#endif /* LTE_RRC_DISSECTOR */



/* local defines */

/* local typedefs */
 
/* local externs */
 
/* forward references */


#ifdef LTE_RRC_DISSECTOR
PUBLIC S16 nhDissectrInit(Void);
#endif /* LTE_RRC_DISSECTOR */

/**
 *
 *     @brief This function is the RRC Layer's Init task and is called
 *            during RRC task's registration
 *
 *     @details 
 *              
 *
 *     @param[in] entity     RRC Entity
 *     @param[in] inst       RRC Instance
 *     @param[in] region     Memory Region
 *     @param[in] reason     Reason
 *
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/

#ifdef ANSI
PUBLIC S16 nhActvInit
(
Ent entity,            /* Entity */
Inst inst,             /* Instance */
Region region,         /* Region */
Reason reason          /* Reason */
)
#else /* ANSI */
PUBLIC S16 nhActvInit(entity, inst, region, reason)
Ent entity;            /* Entity */
Inst inst;             /* Instance */
Region region;         /* Region */
Reason reason;         /* Reason */
#endif /* ANSI */
{
   S16   i;
   
   TRC3(nhActvInit);

   /* memset the full control block to null */
   cmMemset ((U8 *)&nhCb, 0, sizeof(NhCb));

   nhCb.init.procId = SFndProcId();
   nhCb.init.ent = entity;
   nhCb.init.inst = inst;
   nhCb.init.region = region;
   nhCb.init.reason = reason;
   nhCb.init.cfgDone = FALSE;
   nhCb.init.pool = 0;
   nhCb.init.acnt = FALSE;
   nhCb.init.trc = FALSE;
   
   /* Set the default status to "No Un solicited Status Indication" */
   nhCb.init.usta = FALSE;

   /* Timing queue control point */
   nhCb.nhGenTqCp.nxtEnt = 0;
   nhCb.nhGenTqCp.tmrLen = NH_TQNUMENT;

   /* Initialise the timing queue */
   for (i = 0; i < NH_TQNUMENT; i++)
   {
     nhCb.nhGenTq[i].first = NULLP;
     nhCb.nhGenTq[i].tail = NULLP;
   }

   /* Initialize timing queues for Lower Layer Cfg */
   nhCb.nhLLyrCfgTqCp.nxtEnt = 0;
   nhCb.nhLLyrCfgTqCp.tmrLen = NH_TQNUMENT;

   for (i = 0; i < NH_TQNUMENT; i++)
   {
      nhCb.nhLLyrCfgTq[i].first = NULLP;
      nhCb.nhLLyrCfgTq[i].tail = NULLP;
   }


#ifdef NH_LOG_TO_FILE
   nhCb.dbgFp = NULLP;
   nhCb.fileLogEnb = FALSE;
   nhCb.nmbDbgLines = 0;
   nhCb.cfgDbgLines = 0;
   cmMemset( (U8* )nhCb.filePath, NH_ZERO_VAL, LNH_MAX_FILE_PATH);
#endif /* NH_LOG_TO_FILE */

#ifdef LTE_RRC_DISSECTOR
   if(nhCb.genCfg.rrcLogEnable)
   {
      nhDissectrInit();
   }
#endif

   RETVALUE(ROK);

} /* end of function rrActvInit */

#ifdef LTE_RRC_DISSECTOR
/**
 * @brief Initialization function for LTERRC Dissector
 *
 * @details
 *
 *     Function : nhDissectrInit
 *     
 *     This function is responsible for doing CL initialization pertaining
 *     to Freescale physical layer.
 *     
 *  @param[in]  Void
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 nhDissectrInit
(
 Void  
)
#else
PUBLIC S16 nhDissectrInit(Void)
#endif
{
   S16 ret = ROK;
   ret = ROK;
   struct hostent * hp;
   
   nhCb.udpSock = socket(AF_INET, SOCK_DGRAM, 0);
   if(nhCb.udpSock < 0)
   {
      nhCb.udpSock = 0;
      perror("Socket cant be created");
      ret = RFAILED;
   } 
   nhCb.server.sin_family = AF_INET;
   hp = gethostbyname((const char*)nhCb.genCfg.ipAddress);
   if ( hp == 0){
      perror("Unknown Host");
      ret = RFAILED;
   }
   cmMemcpy((U8 *)&nhCb.server.sin_addr,
   		(CONSTANT U8 *)hp->h_addr,
         	hp->h_length);

   nhCb.server.sin_port = htons(nhCb.genCfg.portNumber);

   RETVALUE(ret);
}

/**
 * @brief This function sends message to configured IP addr using UDP socket.
 *
 * @details
 *
 *     Function : nhDissectrSndMsg
 *     
 *     This function is responsible for sending msg to a configured IP addr.
 *     
 *  @param[in]  Void
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
PUBLIC S16 nhDissectrSndMsg
(
 Buffer *mBuf,
 U8      msgCategory
)
#else
PUBLIC S16 nhDissectrSndMsg(mBuf, msgCategory)
Buffer *mBuf;
U8      msgCategory;
#endif
{
   //unsigned int i;
  // struct msghdr msg;
   //CmInetIovec  txArr[76];
   S16 ret = ROK;
  // Buffer* tmp;
   Data buf[2000] = {0};
   Data *bufPtr = NULLP;
   MsgLen msgLen=0, cpLen=0;
   unsigned int socklen=0;
#ifdef BRDCM
   //tx_fpath_ctl_t tx_fpath_ctl;
#endif

#if 0
#else
   socklen=sizeof(struct sockaddr_in);
   msgLen = 0;
   cpLen =0;
   SFndLenMsg(mBuf, &msgLen);
   if(msgLen >= 1999)
   {
      printf("\n ERROR: Msg length is > 1000 can not send msg \n");
      RETVALUE(RFAILED);
   }

   if(mBuf->b_cont == NULLP)
   {
      printf("\n ERROR: mBuf B_cont is NULLP and not sending rrc msg \n");
      RETVALUE(RFAILED);
   }
 
   buf[0] = msgCategory;
   bufPtr = buf;
   bufPtr++;
   SCpyMsgFix(mBuf, 0, msgLen,(Data *)bufPtr, &cpLen);

   ret = sendto(nhCb.udpSock,(U8 *)buf, msgLen+1,
         0,
         (const struct sockaddr *)&nhCb.server,
         socklen);
   if (ret < 0)
   {
      printf("\n Error in Sending Request to dissector\n") ;
   }
#endif
   if(ret < 0 )
   {
      printf("\n Error:  sendMsg is failed file=%s line=%u\n",__FILE__, __LINE__);
   }
   RETVALUE(ret);
}
#endif /*LTE_RRC_DISSECTOR */

/**********************************************************************
  
         End of file:     ni_init.c@@/main/3 - Fri Jul  1 01:13:19 2011
   
**********************************************************************/
 
/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      ds               1. LTE RRC Release 1.1.
/main/2      ---      ch               1. RRC Release 2.1.
/main/3      ---      sbalakrishna     1. Updated for Release of 3.1.
/main/4      ---      njha             1. Added SS_DIAG flag.
*********************************************************************91*/
