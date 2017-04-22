/********************************************************************20**

     Name:

     Type:     C File.

     Desc:   The upper arm to lower arm and vice versa communication channel

     File:     mt_4gmx.x

     Sid:      mt_4gmx.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:09:30 2014

     Prg:

************************************************************************/
#ifndef __MT4GMX_X__
#define __MT4GMX_X__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SS_4GMX_UCORE

typedef struct ssRegIcpuCfg
{
   U32 Ent;                      /* Entity ID */
   U32 Inst;                     /* Instance ID */
   U32 CoreId;                   /* Core instance ID */
} SsRegIcpuCfg;

extern S16 uarmInit(void);
extern S16 uarmDrvrInit(void);
extern S16 uarmPstTsk(Pst *pst, Buffer *mbuf);
extern S16 uarmIsTsk(Inst inst);
#endif   /* SS_4GMX_UCORE */
#ifdef TENB_RTLIN_CHANGES

#define SS_MEMLOG_SIZE          (1024*1024)
#define SS_MEMLOG_OUTFILE       "ccpu.log"
/* Taken from rb_log.x with minor changes */
typedef struct ssMemlogCb
{
   U32       wPtr;
   U32       dummy[3];
   U8        buf[SS_MEMLOG_SIZE]; /* The actual storage */
   SLockId   lock;
} SsMemlogCb;

SsMemlogCb ssMemlogCb; 

EXTERN Void ssMemlogInit(Void);
EXTERN Void ysMsSndPhyShutDown(Void);
EXTERN Void ssMlogPrint(Void);
EXTERN Void ssMemlogWrite(Void);
EXTERN void mtSigSegvHndlr ARGS((void));
EXTERN void mtSigUsr2Hndlr ARGS((void));
#endif

#ifdef __cplusplus
}
#endif

#endif


/********************************************************************30**

         End of file:     mt_4gmx.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:09:30 2014

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

