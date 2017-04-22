

/********************************************************************20**

     Name:     SON - acc test file

     Type:     

     Desc:     This file contains the acc source
               

     File:     nlac_acc.x

     Sid:      nlac_acc.x@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:02:46 2014

     Prg:      subhamay 

*********************************************************************21*/

#ifndef __NLACCX__
#define __NLACCX__

#ifdef __cplusplus
extern "C" {
#endif

/*NLU interface element*/
typedef struct nlAcNluInfo
{
  Void*              data;
  MsgLen             len;
  SuId               suId;
  SpId               spId;
} NlAcNluInfo;


/*LNL interface element*/
typedef struct nlAcLnlInfo
{
  Void               *data;
  MsgLen             len;
  SpId               spId;
} NlAcLnlInfo;

 /* Message queue element */
typedef struct nlAccMsgQElm
{  
   Pst           pst;                   /* pst structure         */
   Buffer        *mBuf;
   union
   {
      NlAcNluInfo   nluInfo;
      NlAcLnlInfo   lnlInfo;
    }u;

}NlAccMsgQElm;

typedef struct nlAcCb
{
   CmTqCp          tqCp;       /* Timing Queue Control point    */
   CmTqType        tq[NLAC_NUM_TQENTRY]; /* Timing Queue for a resln. */
   CmTimer         sonServerInitTimer;  /* SON server init timer */
   CmTimer         nluBindTimer;        /* NLU SAP binding timer */
}NlAcCb;

EXTERN NlAcCb nlAcCb;

EXTERN S16 smNlActvTsk       ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 nlAcUtlFreeCb     ARGS ((CmXtaMsgQElm   *qElm));

EXTERN S16 smNlActvInit      ARGS((Ent ent, Inst inst, Region region,
                                 Reason reason));

#ifdef __cplusplus
}
#endif
#endif /*__NLACCX__*/

