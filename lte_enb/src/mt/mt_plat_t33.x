/********************************************************************20**

     Name:

     Type:     C File.

     Desc:   The upper arm to lower arm and vice versa communication channel

     File:     mt_icc.x

     Sid:      mt_plat_t33.x@@/main/TeNB_Main_BR/1 - Tue Jul  8 12:01:35 2014

     Prg:

************************************************************************/
#ifndef __MTICC_X__
#define __MTICC_X__

#ifdef __cplusplus
extern "C" {
#endif

#define   APP_QUEUE_SIZE                1024   /* number of elements each queue of the UAII being registered will have */
#define   MAX_MESSAGES                  1000   /* per ms */
#define   DEFAULT_MESSAGE_COUNT_PER_MS  10
#define   DEFAULT_MAX_MESSAGE_SIZE      2000
#define   DEFUALT_MIN_MESSAGE_SIZE      100


typedef struct tagAPP_CONTEXT
{
	U32     ExitStatus;
   void*   hUAII_Dl;
   void*   hUAII_Ul;
   U16     RxID_Dl;
   U16     RxID_Ul;
   U16     TxID_Dl;
   U16     TxID_Ul;
	void*   hUAII;
   void*   hUAII_second;
	U16     RxID;
   U16     RxID_second;
#ifdef UL_RLC_NET_CLUSTER
   void*   hUAII_third;
   U16     RxID_third;
#endif
	U16     TxID;
	U16     InitQueueSize; /* for invalid messages test (to trigger UAII blocking) */
	U32     MsgPerMs;
	U32     MaxMsgSize;
	U32     MinMsgSize;

	U32     TxCnt;
	U32     RxCnt;

	U64     nTxMsgs;    /* Messages transmitted */
	U64     nTxOctets;  /* Octets transmitted */
	U64     nRxMsgs;    /* Messages received */
	U64     nRxOcters;  /* Octets received */
	U64     Cycles;     /* number of 1ms cycles */

	int     AppSanityMsgSize;  /* 4 or 8 depending on CRC feature */
	U8      Debug;             /* when TRUE app cycle is 1 sec, otherwise 1ms */
	U8      TrustedDataSource; /* for trusted data sources ICC service removes msg validity checking. */

	void    (*Receive)(void* h);
	void    (*Transmit)(void* h);

	void    (*ThreadReceive)(void* h);
	void    (*ThreadTransmit)(void* h);

	int     (*tl_put)(void* h, void* pMsg, U32 MsgSize, U16 MsgTypeID, U16 Priority);
	void*   (*tl_get)(void* h, U32 *MsgSize);

	U32     TxMsgCnt;
	void*   TxMessages[MAX_MESSAGES];
	U32     TxMessageSizes[MAX_MESSAGES]; /* <-- required for Ping-Pong test to store received sizes */
} APP_CONTEXT, *PAPP_CONTEXT;


#ifdef L2_L3_SPLIT
#ifdef ICC_RECV_TSK_RBUF
typedef struct rxmBufReq
{
  Buffer       *mBuf;
  Pst           pst;
  U8           isDatValid;
}RxmBufReq;
#endif



extern  Void *mtTskHdlrT2kL2(Ptr );
extern  Void *iccPktReceiver(Void *);
extern  U32 iccTtiTick(Void);

extern  S16 iccPstTsk
(
Pst *pst,                       /* post information */
Buffer *mBuf                    /* message to post */
);
extern  void iccIsTsk
(
Inst inst
);
extern  S16 drvrTskInit
(
 Void
);
EXTERN APP_CONTEXT AppContext;
EXTERN S32 mode;

extern void App_SigExitCallback(int signum);
#endif
#if (defined (MAC_FREE_RING_BUF) || defined (RLC_FREE_RING_BUF))
typedef struct rgKwBufFreeInfo
{
   Void    *bufToFree;
   U8      freeType; /* 0- SPutMsg, 1->SPutStaticBuffer*/
}RgKwFreeInfo;


#endif
#ifdef LC_EGTP_THREAD
typedef struct egWrBufFreeInfo
{
   U8      *tmpBuf;
   U8      *buf;        /* message buffer */
   U32     bufLen;      /* bufLen */
}EgWrFreeInfo;
#endif
#ifdef __cplusplus
}
#endif

#endif


/********************************************************************30**

         End of file:     mt_plat_t33.x@@/main/TeNB_Main_BR/1 - Tue Jul  8 12:01:35 2014

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

   ver        pat        init                  description
---------  ---------  ----------  -------------------------------------
/main/1      --------     ------    1. Initial release
*********************************************************************91*/

