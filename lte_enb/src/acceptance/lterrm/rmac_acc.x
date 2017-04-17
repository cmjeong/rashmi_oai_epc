

/********************************************************************20**

     Name:     RRM - acc test file

     Type:     

     Desc:     This file contains the acc source
               

     File:     rmac_acc.x

     Sid:      rmac_acc.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:24 2013

     Prg:      vprabhu

*********************************************************************21*/

#ifndef __RMUACX__
#define __RMUACX__

#ifdef __cplusplus
extern "C" {
#endif

/*RMU interface element*/
typedef struct rmAcRmuInfo
{
  Void*              data;
  MsgLen             len;
  SuId               suId;
  SpId               spId;
  U8                 status;
} RmAcRmuInfo;


/*LRM interface element*/
typedef struct rmAcLrmInfo
{
  Void*              data;
  MsgLen             len;
  SpId               spId;
} RmAcLrmInfo;

/*RGM interface element */

typedef struct rmAcRgmInfo
{
     Void*              data;
     MsgLen             len;
     SpId               spId;
} RmAcRgmInfo;


 /* Message queue element */
typedef struct rmAccMsgQElm
{  
   Pst           pst;                   /* pst structure         */
   Buffer        *mBuf;
   union
   {
      RmAcRmuInfo   rmuInfo;
      RmAcLrmInfo   lrmInfo;
      RmAcRgmInfo   rgmInfo;
    }u;

}RmAccMsgQElm;


EXTERN S16 rmDmActvTsk       ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 rmAcUtlFreeCb ARGS ((CmXtaMsgQElm   *qElm));

EXTERN S16 rmDmActvInit      ARGS((Ent ent, Inst inst, Region region,
                                 Reason reason));

EXTERN S16 rmDmActvTsk ARGS ((Pst *pst, Buffer *mBuf));

EXTERN S16 smRgActvInit      ARGS((Ent ent, Inst inst, Region region,
                                 Reason reason));

EXTERN S16 smRgActvTsk 	ARGS((Pst      *pst, Buffer   *mBuf));


#if 0 
EXTERN S16 DmUiLrmCfgCfm ARGS((Pst *pst, RmMngmt *cfgCfmInfo));
EXTERN S16 DmUiRmuMmeOverloadStartInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo));
EXTERN S16 DmUiRmuMmeOverloadStopInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStopInd  *stopInfo));
EXTERN S16 DmUiRmuUeAdmitReq ARGS((Pst *pst, SuId suId, RmuUeAdmitReq *admitInfo));
EXTERN S16 DmUiRmuUeAdmitRsp ARGS((Pst *pst, SuId suId, RmuUeAdmitRsp *admitInfo));
EXTERN S16 DmUiRmuUeHoReq ARGS((Pst *pst, SuId suId, RmuUeHoReq *hoInfo));
EXTERN S16 DmUiRmuUeHoRsp ARGS((Pst *pst, SuId suId, RmuUeHoRsp *hoInfo));
EXTERN S16 DmUiRmuUeRelReq ARGS((Pst *pst, SuId suId, RmuUeRelReq *relInfo));
EXTERN S16 DmUiRmuUeRelRsp ARGS((Pst *pst, SuId suId, RmuUeRelRsp *relInfo));
EXTERN S16 DmUiRmuUeRecfgReq ARGS((Pst *pst, SuId suId, RmuUeRecfgReq *reconfigInfo));
EXTERN S16 DmUiRmuUeRecfgRsp ARGS((Pst *pst, SuId suId, RmuUeRecfgRsp *reconfigInfo));

#endif
#ifdef __cplusplus
}
#endif
#endif
