

/********************************************************************20**

     Name:     Upper interface for DAM-Enbapp

     Type:     C source file

     Desc:     C source code for common packing and un-packing
               functions for upper interface.

     File:    wr_ifm_dam_utils.c

     Sid:      fc_ifm_dam_utils.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:51:47 2014

     Prg:      MM

*********************************************************************21*/


/***********************************************************************
 *
 *     This software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *
 *
 ***********************************************************************/

static const char* RLOG_MODULE_NAME="IFM";
static int RLOG_MODULE_ID=4;
static int RLOG_FILE_ID=110;
/***********************************************************************
 *        H E A D E R  I N C L U D E  F I L E S (.h)                   *
 ***********************************************************************/
#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */
#include "gen.h"              /* General */
#include "ssi.h"              /* System Services */
#include "cm_tkns.h"          /* common tokens */
#include "cm_hash.h"          /* common structs 1 */
#include "cm_mblk.h"          /* common memory */
#include "cm_llist.h"         /* cm link list */
#include "cm5.h"              /* common structs 3 */
#include "cm_inet.h"          /* common tokens  */
#include "cm_tkns.h"          /* common tokens */
#include "cm_tpt.h"           /* common transport */
#include "cm_dns.h"           /* common transport */
#include "wr_ifm_dam_utils.h" /*DAM Upper Interface */
#include "wr_dam_ifm_app.h"   /*ccpu00138576*/


/***********************************************************************
 *     H E A D E R / E X T E R N   I N C L U D E  F I L E S (.h)       *
 ***********************************************************************/
#include "gen.x"               /* General */
#include "ssi.x"               /* System Services */
#include "cm_tkns.x"           /* common tokens */
#include "cm_hash.x"           /* common structs 1 */
#include "cm_lib.x"            /* common library */
#include "cm_mblk.x"           /* common memory */
#include "cm_llist.x"          /* cm link list */
#include "cm5.x"               /* common structs 3 */
#include "cm_inet.x"           /* common transport */
#include "cm_tpt.x"            /* common transport */
#include "cm_dns.x"            /* common transport */
#include "wr_ifm_dam_utils.h"  /* DMA Upper Interface */
#include "wr_ifm_dam_utils.x"

#define WR_DAM_FREE_BUFFER(_region,_buf) \
{                                        \
   SPutMsg(_buf);                        \
}                                        

#define cmPkDamTnlType SPkU32
#define cmPkDamEgtpTeid SPkU32
#define cmUnpkDamTnlType SUnpkU32
#define cmUnpkDamEgtpTeid SUnpkU32

/*
  Defines for the packing and unpacking
*/

/**
* @brief This API is used to pack the function for 
* the Alarm Indication 
*
* @details
*
* Function: cmPkDamSendAlarmInd
*
* @param[in] Pst *pst
* @param[in] U16 category :For what operation the alarm is being generated
* @param[in] U16 event    :alarm is generated during this event.
* @param[in] U16 cause    :Cause for the event and alarm generation.
* @return   S16
*  /RFAILED
**/
PUBLIC S16 cmPkDamSendAlarmInd
(
Pst *pst,
U16                          category,
U16                          event,
U16                          cause
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamSendAlarmInd)

   if (SGetMsg(pst->region,pst->pool,&mBuf) != ROK) 
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU16,category,mBuf,0,pst);
   CMCHKPKLOG(SPkU16,event,mBuf,0,pst);
   CMCHKPKLOG(SPkU16,cause,mBuf,0,pst);

   pst->event = (Event)EVTDAMALARMIND;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamSendAlarmInd */

/**
* @brief This API is used to unpack the 
* Alarm Indication.In turn it calls the Dam Interface 
* function to send the Alarm Indication. 
*
* @details
*
* Function: cmUnpkDamSendAlarmInd 
*
* @param[in] Pst    *pst
* @param[in] Buffer *mBuf 
* @return   S16
*  /RFAILED
**/
PUBLIC S16 cmUnpkDamSendAlarmInd
(
DamSendAlarmInd func,
Pst *pst,
Buffer *mBuf
)
{
   U16  cause;
   U16  event;
   U16  category;

   TRC3(cmUnpkDamSendAlarmInd)

   CMCHKUNPKLOG(SUnpkU16,&cause,mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU16,&event,mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU16,&category,mBuf,0, pst);

   WR_DAM_FREE_BUFFER (pst->region,mBuf);

   RETVALUE((*func)(pst,category,event,cause));
}/* cmUnpkDamSendAlarmInd */


/*
*
*  Fun: cmPkWrDamGenCfg 
*
*  Desc:  This function packs the DAM General configuration.
*
*  Ret:   ROK
*
*  Notes: None
*
*  File:  wr_ifm_dam_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkWrDamGenCfg 
(
LwrMngmt           *cfg,
Buffer             *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkWrDamGenCfg(cfg, mBuf)
LwrMngmt           *cfg;
Buffer             *mBuf;        /* message buffer */
#endif
{
   TRC3(cmPkWrDamGenCfg)
      
      switch (cfg->hdr.elmId.elmnt)
      {
         case STWRGEN:
            {
               LwrGenCfg *genCfg = &cfg->t.cfg.t.genCfg;
               CMCHKPK(SPkU32,genCfg->inactvTmrVal,mBuf);
               CMCHKPK(SPkU16,genCfg->expiryCnt,mBuf);
               CMCHKPK(SPkU32,genCfg->endMrkTmrVal,mBuf);
               CMCHKPK(cmPkTicks,genCfg->timeRes,mBuf);
               break;
            }
         case STWRDAMSAP:
         case STWREGTSAP:
         case STWRPJUSAP:
            {
                LwrLSapCfg *lSap = &cfg->t.cfg.t.lSap;
                CMCHKPK(cmPkWrLSapCfg,lSap,mBuf);
                break;
            }
         default:
            {
               RLOG0(L_ERROR, "cmPkWrDamGenCfg: Invalid Element");
               RETVALUE(RFAILED);
            }
      }
      
      CMCHKPK(cmPkHeader, &cfg->hdr,mBuf);

   RETVALUE(ROK);

}/* End of cmPkWrDamGenCfg */


/*
*
*  Fun: cmUnpkWrDamGenCfg
*
*  Desc:  This function unpacks the DAM General configuration
*
*  Ret:   None
*
*  Notes: None
*
*  File:  wr_ifm_dam_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkWrDamGenCfg 
(
LwrMngmt           *cfg,
Buffer             *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkWrDamGenCfg(cfg, mBuf)
LwrMngmt           *cfg;
Buffer             *mBuf        /* message buffer */
#endif
{
   TRC3(cmUnpkWrDamGenCfg)

   CMCHKUNPK(cmUnpkHeader,&(cfg->hdr),mBuf);
   switch (cfg->hdr.elmId.elmnt)
   {
      case STWRGEN:
         {
            CMCHKUNPK(cmUnpkTicks,&(cfg->t.cfg.t.genCfg.timeRes),mBuf);
            CMCHKUNPK(SUnpkU32,&(cfg->t.cfg.t.genCfg.endMrkTmrVal),mBuf);
            CMCHKUNPK(SUnpkU16,&(cfg->t.cfg.t.genCfg.expiryCnt),mBuf);
            CMCHKUNPK(SUnpkU32,&(cfg->t.cfg.t.genCfg.inactvTmrVal),mBuf);
            break;
         }
      case STWRDAMSAP:
      case STWREGTSAP:
      case STWRPJUSAP:
         {
            CMCHKUNPK(cmUnpkWrLSapCfg,&(cfg->t.cfg.t.lSap),mBuf);
            break;
         }
      default:
         {
            RLOG0(L_ERROR, "cmUnpkWrDamGenCfg: Invalid Element");
         }
   }
  RETVALUE(ROK);
}/* End of cmUnpkWrDamGenCfg */


/**
* @brief This API is used to pack the Dam Configuration Request 
*         and post it.
*
* @details
*
* Function: cmPkDamCfgReq
*
* @param[in] Pst      *pst
* @param[in] LwrMngmt *cfg 
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamCfgReq
(
Pst *pst,
LwrMngmt *cfg
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

#ifndef WR_DAM_LC
   CMCHKPKLOG(cmPkPtr,(PTR)cfg,mBuf,0,pst);
#else
   CMCHKPKLOG(cmPkWrDamGenCfg,cfg,mBuf,0,pst);
#endif
   pst->event = (Event)EVTDAMCFGREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamCfgReq */

/**
* @brief This API is used to pack Dam Control Confirm
*       and also it post the message.
*
* @details
*
* Function: cmPkDamCntrlCfm
*
* @param[in] Pst      *pst
* @param[in] CmStatus *cmStatus 
* @param[in] LwrMngmt *cntrl 
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamCntrlCfm
(
Pst *pst,
CmStatus *cmStatus,
LwrMngmt *cntrl
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamCntrlCfm);

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

#ifndef WR_DAM_LC
   CMCHKPKLOG(cmPkPtr,(PTR)cntrl,mBuf,0,pst);
#else
   cmPkWrMngmt(cntrl,EVTLWRCNTRLCFM,mBuf);
#endif
   CMCHKPKLOG(cmPkCmStatus,cmStatus,mBuf,0,pst);

   pst->event = (Event)EVTDAMCNTRLCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamCntrlCfm */



/**
* @brief This API is used to pack Dam Context Rel
*       and also posts the message.
*
* @details
*
* Function: cmPkDamSendCtxtRel 
*
* @param[in] Pst      *pst
* @param[in] U16      crnti  
* @param[in] U16      CellId 
* @param[in] U8       Event 
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamSendCtxtRel 
(
Pst *pst,
U16 crnti,
U16 cellId,
U8  event
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamSendCtxtRel);

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU16,crnti,mBuf,0,pst);
   CMCHKPKLOG(SPkU16,cellId,mBuf,0,pst);
   CMCHKPKLOG(SPkU8,event,mBuf,0,pst);

   pst->event = (Event)EVTDAMCTXTRELREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/*cmPkDamSendCtxtRel*/

/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation confirm  function in DAM module. 
*
* @details
*
*     Function: cmUnPkDamSendCtxtRel
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return  Void 
**/

#ifdef ANSI
PUBLIC S16 cmUnPkDamSendCtxtRel 
(
DamSendCtxtRel func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkDamSendCtxtRel(pst, mBuf)
DamSendCtxtRel func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16 crnti;
   U16 cellId;
   U8  event;
 
   TRC3(cmUnPkDamSendCtxtRel)
      
   CMCHKUNPKLOG(SUnpkU8,&event,mBuf,0,pst);
   CMCHKUNPKLOG(SUnpkU16,(&cellId),mBuf,0,pst);
   CMCHKUNPKLOG(SUnpkU16,(&crnti),mBuf,0,pst);

   WR_DAM_FREE_BUFFER(pst->region,mBuf);
   RETVALUE((*func)(pst,crnti,cellId,event));
}/* cmUnPkDamSendCtxtRel */

/**
* @brief This API is used to pack the Dam Control Request 
* post the message.
*
* @details
*
* Function: cmPkDamCntrlReq 
*
* @param[in] Pst *  pst
* @param[in] LwrMngmt *cntrl 
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamCntrlReq
(
Pst *pst,
LwrMngmt *cntrl
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamCntrlReq)

   if (SGetMsg(pst->region,pst->pool,&mBuf)!= ROK) 
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

#ifndef WR_DAM_LC
   CMCHKPKLOG(cmPkPtr,(PTR)cntrl,mBuf,0,pst);
#else
   cmPkWrMngmt(cntrl,EVTLWRCNTRLREQ,mBuf);
#endif

   pst->event = (Event)EVTDAMCNTRLREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamCntrlReq */

/**
* @brief This API is used to pack the Dam Config Confirm
* and send the message.
*
* @details
*
* Function: cmPkDamCfgCfm
*
* @param[in] Pst *  pst
* @param[in] LwrMngmt *cfg
* @param[in] CmStatus *cmStatus
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamCfgCfm
(
Pst *pst,
LwrMngmt *cfg,
CmStatus *cmStatus
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

#ifndef WR_DAM_LC
   CMCHKPKLOG(cmPkPtr,(PTR)cfg,mBuf,0,pst);
#else
   CMCHKPKLOG(cmPkWrDamGenCfg,cfg,mBuf,0,pst);
#endif
   CMCHKPKLOG(cmPkCmStatus, cmStatus,mBuf,0,pst);

   pst->event = (Event)EVTDAMCFGCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamCfgCfm */


/**
* @brief This API is used unpack the message and calls the 
* Dam Configuration function. 
*
* @details
*
*     Function: cmUnpkDamCfgReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

PUBLIC S16 cmUnpkDamCfgReq
(
DamCfgReq func,
Pst *pst,
Buffer *mBuf
)
{
   LwrMngmt *cfg;

   TRC3(cmUnpkDamCfgReq)

#ifndef WR_DAM_LC
   CMCHKUNPKLOG(cmUnpkPtr,(PTR *)&cfg, mBuf, 0, pst);
#else
   SGetStaticBuffer (0,0,(Data **)&cfg, sizeof(LwrMngmt), 1);
   CMCHKUNPKLOG(cmUnpkWrDamGenCfg,(cfg), mBuf, 0, pst);
#endif

   WR_DAM_FREE_BUFFER(pst->region,mBuf);

   RETVALUE((*func)(pst, cfg));
   WR_FREE_DATA_APP_SHAREBLE_BUF( cfg, sizeof(LwrMngmt));
}/* cmUnpkDamCfgReq */

/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* Dam Control Request function in DAM module. 
*
* @details
*
*     Function: cmUnpkDamCntrlReq 
*
*
*  @param[in]  Pst *pst 
*  @param[in]  buf *mBuf
*  @return   Void 
**/

PUBLIC S16 cmUnpkDamCntrlReq
(
DamCntrlReq func,
Pst *pst,
Buffer *mBuf
)
{
   LwrMngmt *cntrl;

   TRC3(cmUnPkDamCntrlReq)

#ifndef WR_DAM_LC
   CMCHKUNPKLOG(cmUnpkPtr,(PTR *)&cntrl, mBuf, 0, pst);
#else
   SGetStaticBuffer (0,0,(Data **)&cntrl, sizeof(LwrMngmt), 1);
   cmUnpkWrMngmt(cntrl,EVTLWRCNTRLREQ,NULL, mBuf, pst);
#endif

   WR_DAM_FREE_BUFFER(pst->region,mBuf);

   RETVALUE((*func)(pst, cntrl));

   WR_FREE_DATA_APP_SHAREBLE_BUF( cntrl, sizeof(LwrMngmt));
}/* cmUnpkDamCntrlReq */

/**
* @brief This API is used unpack the function and call the 
*  config confirm function.
*
*  @details
*
*  Function: cmUnpkDamCfgCfm 
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

PUBLIC S16 cmUnpkDamCfgCfm
(
DamCfgCfm func,
Pst *pst,
Buffer *mBuf
)
{
   LwrMngmt *cfg;
   CmStatus status;

   TRC3(cmUnpkDamCfgCfm)

   CMCHKUNPKLOG(cmUnpkCmStatus,&status, mBuf, 0, pst);
#ifndef WR_DAM_LC
   CMCHKUNPKLOG(cmUnpkPtr,(PTR *)&cfg, mBuf, 0, pst);
#else
   SGetStaticBuffer (0,0,(Data **)&cfg, sizeof(LwrMngmt), 1);
   CMCHKUNPKLOG(cmUnpkWrDamGenCfg,(cfg), mBuf, 0, pst);
#endif

   WR_DAM_FREE_BUFFER(pst->region,mBuf);

   RETVALUE((*func)(pst,cfg,&status));

} /* cmUnpkDamCfgCfm */

/**
* @brief This API is used unpacks the message  and calls 
*        control confirm function in DAM module. 
*
* @details
*
* Function:cmUnpkDamCntrlCfm 
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

PUBLIC S16 cmUnpkDamCntrlCfm
(
DamCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
{
   LwrMngmt *cntrl;
   CmStatus  status;

   TRC3(cmUnPkDamCntrlCfm)

   CMCHKUNPKLOG(cmUnpkCmStatus,(&status), mBuf, 0, pst);
#ifndef WR_DAM_LC
   CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&cntrl), mBuf, 0, pst);
#else
   SGetStaticBuffer (0,0,(Data **)&cntrl, sizeof(LwrMngmt), 1);
   cmUnpkWrMngmt(cntrl,EVTLWRCNTRLCFM,NULL, mBuf, pst);
#endif

   WR_DAM_FREE_BUFFER(pst->region,mBuf);

   RETVALUE((*func)(pst, cntrl,&status));

}/* cmUnpkDamCntrlCfm */



/**
* @brief This API is used to send a 
* Print Throughput  Request from EnbApp to DAM.
*
* @details
*
* Function: cmPkPrnThptReq
*
* @param[in]   Pst *  pst
* @param[in]   
* @return   Void
*  -# ROK /RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkPrnThptReq
(
Pst *pst
)
#else
PUBLIC S16 cmPkPrnThptReq(pst)
Pst * pst;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkPrnThptReq)

   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {

      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   pst->event = (Event)EVTDAMPRNTTHPTREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkPrnThptReq */

/**
* @brief This API is used to unpack the message and 
* call the throughput printing function in DAM module. 
*
* @details
*
*     Function: cmUnPkPrnThptReq
*
*
*  @param[in]   Pst *pst 
*  @param[in]   Buffer *mbuf
*  @return  Void 
**/

#ifdef ANSI
PUBLIC S16 cmUnpkPrnThptReq
(
DamPrnThptReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPrnThptReq(pst, mBuf)
DamPrnThptReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkPrnThptReq)

   WR_DAM_FREE_BUFFER(pst->region,mBuf);

/*   wrDamPrintThroughput();*/
  RETVALUE(ROK);
}/* cmUnpkPrnThptReq */


/**
* @brief This API is used to send a 
* Tunnel Create  Request from EnbApp to DAM.
*
* @details
*
* Function: cmPkTnlCreatReq
* 
* @param[in]  Pst *  pst
* @param[in]  U32 transId 
* @param[in]  WrDamTnlInfo *tnlInfo
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTnlCreatReq
(
Pst *pst,
U32 transId,
WrDamTnlInfo *tnlInfo
)
#else
PUBLIC S16 cmPkTnlCreatReq(pst,transId,*tnlInfo)
Pst * pst;
U32 transId;
WrDamTnlInfo *tnlInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTnlCreatReq)
  
   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   
   CMCHKPKLOG(SPkU32,(transId),mBuf,0,pst);

#ifndef WR_DAM_LC
   /* LWLC Packing */
   if (pst->selector == DAM_SEL_LWLC) 
   {
      CMCHKPKLOG(cmPkPtr,((PTR)tnlInfo),mBuf,0,pst);
   }
   else
#endif
   {
      SAddPstMsgMult((Data *)tnlInfo, sizeof (WrDamTnlInfo), mBuf);
   }

   WR_FREE_DATA_APP_SHAREBLE_BUF(tnlInfo, sizeof(WrDamTnlInfo));
   pst->event = (Event)EVTDAMTNLCRETREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkTnlCreatReq */

/**
* @brief This API is used to send a 
* Tunnel Create  Request from EnbApp to DAM.
*
* @details
*
* Function: cmPkTnlModReq
* 
* @param[in]  Pst *  pst
* @param[in]  U32 transId 
* @param[in]  WrDamTnlModInfo *tnlInfo
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTnlModReq
(
Pst *pst,
U32 transId,
WrDamTnlModInfo *tnlModInfo
)
#else
PUBLIC S16 cmPkTnlModReq(pst,transId,*tnlModInfo)
Pst * pst;
U32 transId;
WrDamTnlModInfo *tnlModInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTnlModReq)
  
   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   
   CMCHKPKLOG(SPkU32,(transId), mBuf,0, pst);
#ifndef WR_DAM_LC
   CMCHKPKLOG(cmPkPtr,((PTR)tnlModInfo),mBuf,0,pst);
#else
   SAddPstMsgMult((Data *)tnlModInfo, sizeof (WrDamTnlModInfo), mBuf);
#endif
 
   pst->event = (Event)EVTDAMTNLMODREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkTnlCreatReq */



/**
* @brief This API is used to send a 
* tunnel create confirm  from EnbApp to DAM.
*
* @details
*
* Function:cmPkTnlModCfm
* 
* @param[in] Pst *  pst
* @param[in] U32 transId 
* @param[in] U8 status
* @param[in] U32 lclTeid
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTnlModCfm 
(
Pst *pst,
U32 transId,
U8 status,
U32 lclTeid
)
#else
PUBLIC S16 cmPkTnlModCfm(pst,transId,status,lclTeid)
Pst * pst;
U32 transId;
U8 status;
U32 lclTeid;
#endif
{
   Buffer *mBuf = NULLP
   TRC3(cmPkTnlModCfm)

   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU32,(transId),mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU8,(status),mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU32,(lclTeid),mBuf,EDAM001, pst);
  
   pst->event = (Event)EVTDAMTNLMODCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* End of cmPkTnlCreatCfm*/



/**
* @brief This API is used to send a 
* tunnel create confirm  from EnbApp to DAM.
*
* @details
*
* Function:cmPkTnlCreatCfm
* 
* @param[in] Pst *  pst
* @param[in] U32 transId 
* @param[in] U8 status
* @param[in] U32 lclTeid
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTnlCreatCfm 
(
Pst *pst,
U32 transId,
U8 status,
U32 lclTeid
)
#else
PUBLIC S16 cmPkTnlCreatCfm(pst,transId,status,lclTeid)
Pst * pst;
U32 transId;
U8 status;
U32 lclTeid;
#endif
{
   Buffer *mBuf = NULLP
   TRC3(cmPkTnlCreatCfm)

   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   //printf("\n DAM tnl cfm: %ld %d %ld\n", transId, status, lclTeid);
   CMCHKPKLOG(SPkU32,(transId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU8,(status ), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU32,(lclTeid), mBuf,EDAM001, pst);
  
   pst->event = (Event)EVTDAMTNLCRETCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* End of cmPkTnlCreatCfm*/


/**
* @brief This API is used to send a 
* Tunnel Delete Req from Enbapp to DAM.
*
* @details
*
* Function:cmPkTnlDelReq
* 
* @param[in]   Pst *  pst
* @param[in]   U32 transID 
* @param[in]   WrDamTnlId *tnlId
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTnlDelReq 
(
Pst *pst,
U32 transId,
WrDamTnlId *tnlId
)
#else
PUBLIC S16 cmPkTnlDelReq(pst,transId,*tnlId)
Pst * pst;
U32 transId;
WrDamTnlId *tnlId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTnlDelReq)

   /* Buffer Allocation */ 
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   
   CMCHKPKLOG(SPkU32,(transId), mBuf,EDAM001, pst);
#ifndef WR_DAM_LC
   /* LWLC Packing*/
   if (pst->selector == DAM_SEL_LWLC) {
     CMCHKPKLOG(cmPkPtr,((PTR)tnlId), mBuf, EEGT014, pst);
   }
   else
#endif
   {
      SAddPstMsgMult((Data *)tnlId, sizeof (WrDamTnlId), mBuf);
   }
   
   pst->event = (Event)EVTDAMTNLDELTREQ;
   RETVALUE(SPstTsk(pst, mBuf));

} /* cmPkTnlDelReq */ 

/**
* @brief This API is used to send a 
* Print Throughput  Request from EnbApp to DAM.
*
* @details
*
* Function:cmPkTnlStChngReq 
* 
* @param[in]  Pst *  pst
* @param[in]  WrDamTnlStInfo *tnlStInfo 
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTnlStChngReq 
(
Pst *pst,
WrDamTnlStInfo *tnlStInfo
)
#else
PUBLIC S16 cmPkTnlStChngReq(pst,*tnlStInfo)
Pst * pst;
WrDamTnlStInfo *tnlStInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTnlStChngReq)

   /* Buffer Allocaton */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
#ifndef WR_DAM_LC
   if (pst->selector == DAM_SEL_LWLC) {
      CMCHKPKLOG(cmPkPtr,((PTR)tnlStInfo),mBuf,EEGT014,pst);
   }
   else
#endif
   {
      SAddPstMsgMult((Data *)tnlStInfo, sizeof (WrDamTnlStInfo), mBuf);
   }
 
   pst->event = (Event)EVTDAMTNLSTCHNGREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkTnlStChngReq */

/**
* @brief This API is used to send a 
* Ue Delete request from Enbapp to DAM.
*
* @details
*
* Function:cmPkUeDelReq 
* 
* @param[in]   Pst *  pst
* @param[in]   U32 transID 
* @param[in]   U16 cellId
* @param[in]   U16 crnti
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkUeDelReq 
(
Pst *pst,
U32 transId,
U16 cellId,
U16 crnti
)
#else
PUBLIC S16 cmPkUeDelReq(pst,transId,cellId,crnti)
Pst * pst;
U32 transId;
U16 cellId;
U16 crnti;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkUeDelReq)

   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(SPkU32,transId, mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,cellId, mBuf,EDAM002, pst);
   CMCHKPKLOG(SPkU16,crnti, mBuf,EDAM003, pst);

   
   pst->event = (Event)EVTDAMUEDELTREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkUeDelReq */

/**
* @brief This API is used to initate a 
* Ue Delete Confirm  from DAM to EnbApp. 
*
* @details
*
* Function:cmPkUeDelCfm 
* 
* @param[in]   Pst *  pst
* @param[in]   U32 transID 
* @param[in]   U16 cellId
* @param[in]   U16 crnti
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkUeDelCfm 
(
Pst *pst,
U32 transId,
U16 cellId,
U16 crnti
)
#else
PUBLIC S16 cmPkUeDelCfm(pst,transId,cellId,crnti)
Pst * pst;
U32 transId;
U16 cellId;
U16 crnti;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkUeDelCfm)

   /* Buffer Allocation */ 
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   
   CMCHKPKLOG(SPkU32,(transId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,(cellId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,(crnti), mBuf,EDAM001, pst);
   
   pst->event = (Event)EVTDAMUEDELTCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkUeDelCfm */ 


/**
* @brief This API is used to send a 
* Cell Add Request from Enbapp to DAM.
*
* @details
*
* Function:cmPkCellAddReq 
* 
* @param[in]   Pst *  pst
* @param[in]   WrDamCellInfo *cellInfo 
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCellAddReq
(
Pst *pst,
WrDamCellInfo *cellInfo
)
#else
PUBLIC S16 cmPkCellAddReq(pst,*cellInfo)
Pst * pst;
WrDamCellInfo *cellInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCellAddReq)

   printf("Cell Add REq \n");
   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   /* LWLC */
#ifndef WR_DAM_LC
   if (pst->selector == DAM_SEL_LWLC) {
      CMCHKPKLOG(cmPkPtr,((PTR)cellInfo), mBuf, EEGT014, pst);
   }
   else
#endif
   {
      SAddPstMsgMult((Data *)cellInfo, sizeof (WrDamCellInfo), mBuf);
   }
    
   WR_FREE_DATA_APP_SHAREBLE_BUF(cellInfo, sizeof(WrDamCellInfo));
   pst->event = (Event)EVTDAMCELLADDREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkCellAddReq */

/**
* @brief This API is used to send a 
* Ue Re-establishment request from Enbapp to DAM.
*
* @details
*
* Function: cmPkReestabReq
* 
* @param[in]   Pst *  pst
* @param[in]   U32 transID 
* @param[in]   U16 cellId 
* @param[in]   U16 oldcrnti
* @param[in]   U16 newcrnti
* @return   S16
*  -# ROK/RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkReestabReq 
(
Pst *pst,
U32 transId,
U16 cellId,
U16 oldcrnti,
U16  newcrnti
)
#else
PUBLIC S16 cmPkReestabReq(pst,transId,cellId,oldcrnti,newcrnti)
Pst * pst;
U32 transId;
U16 cellId;
U16 oldcrnti;
U16  newcrnti;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkReestabReq)

   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU32,(transId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,(cellId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,(oldcrnti), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,(newcrnti), mBuf,EDAM001, pst);

   pst->event = (Event)EVTDAMRESTREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkReestabReq */

/**
* @brief This API is used to send a 
* Re-establishment Confirm from DAM to EnbApp.
*
* @details
*
* Function:cmPkReestabCfm
* 
* @param[in] Pst *  pst
* @param[in] U32 transId 
* @param[in] U8 status
* @param[in] U32 lclTeid
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkReestabCfm 
(
Pst *pst,
U32 transId,
U8 status
)
#else
PUBLIC S16 cmPkReestabCfm(pst,transId,status)
Pst * pst;
U32 transId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP
   TRC3(cmPkReestabCfm)
   /* Buffer Allocation */

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU32,(transId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU8,(status ), mBuf,EDAM001, pst);

   pst->event = (Event)EVTDAMREESTABCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/*cmPkReestabCfm */


/**
* @brief This API is used to send a 
* Ue Delete request from Enbapp to DAM.
*
* @details
*
* Function:cmPkReCfgReq 
* 
* @param[in]   Pst *  pst
* @param[in]   U32 transID 
* @param[in]   U16 cellId 
* @param[in]   U16 crnti
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkReCfgReq 
(
Pst *pst,
U32 transId,
U16 cellId,
U16 crnti
)
#else
PUBLIC S16 cmPkReCfgReq(pst,transId,cellId,crnti)
Pst * pst;
U32 transId;
U16 cellId;
U16 crnti;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkReCfgReq)

   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU32,(transId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,(cellId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,(crnti), mBuf,EDAM001, pst);
   
   pst->event = (Event)EVTDAMRECFGREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkReCfgReq */

/**
* @brief This API is used to send a 
* Ue Delete request from Enbapp to DAM.
*
* @details
*
* Function :  cmPkHdlHoFailure
* 
* @param[in]   Pst *  pst
* @param[in]   U16 cellId 
* @param[in]   U16 ueId 
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkHdlHoFailure 
(
Pst *pst,
U16 cellId,
U16 crnti 
)
#else
PUBLIC S16 cmPkHdlHoFailure(pst,cellId,crnti)
Pst * pst;
U16 cellId;
U16 crnti;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkHdlHoFailure)
   /*  Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, " Memory allocation failed. ");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU16,(cellId), mBuf,EDAM001, pst);
   /* HO_FIX: Changed SPkU32 to SPkU16 as we are unpacking
              U16 only */
   CMCHKPKLOG(SPkU16,(crnti), mBuf,EDAM001, pst);
   pst->event = (Event)EVTDAMHDLHOFAIL;
   RETVALUE(SPstTsk(pst, mBuf));

}

/**
* @brief This API is used to send a 
* Ue Delete request from Enbapp to DAM.
*
* @details
*
* Function:cmPkStartInactivityTimer
* 
* @param[in]   Pst *  pst
* @param[in]   U16 cellId 
* @param[in]   U16 crnti 
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkStartInactivityTimer 
(
Pst *pst,
U16 cellId,
U16 crnti
)
#else
PUBLIC S16 cmPkStartInactivityTimer(pst,cellId,crnti)
Pst * pst;
U16 cellId;
U16 crnti;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkStartInactivityTimer)
   /*  Buffer Allocation */

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU16,(cellId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU16,(crnti), mBuf,EDAM001, pst);
   
   pst->event = (Event)EVTDAMINACTIVITYTMR;
   RETVALUE(SPstTsk(pst, mBuf));

} /* cmPkStartInactivityTimer */

/**
* @brief This API is used to send a 
* Ue Delete request from Enbapp to DAM.
*
* @details
*
* Function:cmPkStopUeTmr
* 
* @param[in]   Pst *  pst
* @param[in]   U16 cellId 
* @param[in]   U16 ueId 
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkStopUeTmr 
(
Pst *pst,
U16 cellId,
U16 ueId 
)
#else
PUBLIC S16 cmPkStopUeTmr(pst,cellId,ueId)
Pst * pst;
U16 cellId;
U16 ueId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkStopUeTmr)
   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU16,(cellId), mBuf,EDAM001, pst);
   CMCHKPKLOG(SPkU32,(ueId), mBuf,EDAM001, pst);
   
   pst->event = (Event)EVTDAMUESTOPTMR;
   RETVALUE(SPstTsk(pst, mBuf));

} /* cmPkStopUeTmr */

/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation function in DAM module. 
*
* @details
*
*     Function: cmUnPkTnlCreatReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkTnlCreatReq
(
DamTnlCreatReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkTnlCreatReq(func, pst, mBuf)
DamTnlCreatReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    U32 transId = 0;
    WrDamTnlInfo *tnlInfo = NULLP;
    MsgLen len;

    TRC3(cmUnPkTnlCreatReq)

#ifndef WR_DAM_LC
    CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&tnlInfo), mBuf, EEGT014, pst);
#endif
    CMCHKUNPKLOG(SUnpkU32,(&transId), mBuf,EDAM001, pst);
#ifdef WR_DAM_LC
    SGetStaticBuffer (0,0,(Data **)&tnlInfo, sizeof(WrDamTnlInfo), 1);
    SCpyMsgFix(mBuf,0,sizeof(WrDamTnlInfo),(Data *)tnlInfo,&len);
#endif

    WR_DAM_FREE_BUFFER (pst->region,mBuf);

    RETVALUE((*func)(pst, transId,tnlInfo));

}/* cmUnPkTnlCreatReq */


/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation confirm  function in DAM module. 
*
* @details
*
*     Function: cmUnPkTnlCreatCfm
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkTnlCreatCfm
(
DamTnlCreatCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkTnlCreatCfm(func, pst, mBuf)
DamTnlCreatCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U32 transId = 0;
   U8 status   = 0;
   U32 lclTeid = 0;
 
   TRC3(cmUnPkTnlCreatCfm)
      
   CMCHKUNPKLOG(SUnpkU32,(&lclTeid), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU8,&status, mBuf,EDAM002, pst);
   CMCHKUNPKLOG(SUnpkU32,(&transId), mBuf,EDAM001, pst);
  
   WR_DAM_FREE_BUFFER (pst->region,mBuf);
   //printf("\n tnl cfm: %ld %d %ld\n", transId, status, lclTeid);

   RETVALUE((*func)(pst,transId, status, lclTeid));

}/* cmUnPkTnlCreatCfm */

/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation function in DAM module. 
*
* @details
*
*     Function: cmUnPkTnlCreatReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnpkTnlModReq
(
DamTnlModReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTnlModReq(pst, mBuf)
DamTnlModReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    U32 transId = 0;
    WrDamTnlModInfo *tnlModInfo = NULLP;
    MsgLen len;

    TRC3(cmUnPkTnlCreatReq)


#ifndef WR_DAM_LC
    CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&tnlModInfo), mBuf, 0, pst);
#endif
    CMCHKUNPKLOG(SUnpkU32,(&transId), mBuf,EDAM001, pst);
#ifdef WR_DAM_LC
    SGetStaticBuffer (0,0,(Data **)&tnlModInfo, sizeof(WrDamTnlModInfo), 1);
    SCpyMsgFix(mBuf,0,sizeof(WrDamTnlModInfo),(Data *)tnlModInfo,&len);
#endif
 
    WR_DAM_FREE_BUFFER (pst->region,mBuf);
    
    RETVALUE((*func)(pst, transId,tnlModInfo));
}/* cmUnPkTnlCreatReq */


/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation confirm  function in DAM module. 
*
* @details
*
*     Function: cmUnPkTnlCreatCfm
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnpkTnlModCfm
(
DamTnlModCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTnlModCfm(pst, mBuf)
DamTnlModCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U32 transId = 0;
   U8 status   = 0;
   U32 lclTeid = 0;
 
   TRC3(cmUnpkTnlModCfm)
      
   CMCHKUNPKLOG(SUnpkU32,(&lclTeid), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU8,&status, mBuf,EDAM002, pst);
   CMCHKUNPKLOG(SUnpkU32,(&transId), mBuf,EDAM001, pst);
  
   WR_DAM_FREE_BUFFER (pst->region,mBuf);
  
    RETVALUE((*func)(pst, transId, status, lclTeid));
}/* cmUnpkTnlModCfm */


/**
* @brief This API is used to call the function directly
* in DAM interface file.The function in turn will call the
* tunnel deletion fucntion in DAM module. 
*
* @details
*
*     Function:cmUnPkTnlDelReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkTnlDelReq 
(
DamTnlDelReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkTnlDelReq(func, pst, mBuf)
DamTnlDelReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    U32 transId = 0;
    WrDamTnlId *tnlId = NULLP;
    MsgLen len;

    TRC3(cmUnPkTnlDelReq)

#ifndef WR_DAM_LC
    if (pst->selector == DAM_SEL_LWLC) 
    {
       CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&tnlId), mBuf, EEGT014, pst);
    }
#endif

    CMCHKUNPKLOG(SUnpkU32,(&transId), mBuf,EDAM001, pst);

#ifdef WR_DAM_LC
    SGetStaticBuffer (0,0,(Data **)&tnlId, sizeof(WrDamTnlId), 1);
    SCpyMsgFix(mBuf,0,sizeof(WrDamTnlId),(Data *)tnlId,&len);
#endif
  
    WR_DAM_FREE_BUFFER (pst->region,mBuf);
    if(NULLP == tnlId)
    {
      RLOG0(L_ERROR, "cmUnPkTnlDelReq(): WrDamTnlId is NULL.");
      RETVALUE(RFAILED);
    }


    RETVALUE((*func)(pst, transId, tnlId));

} /* cmUnPkTnlDelReq */

/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for the deleting the UE in wr_dam.c.
*
* @details
*
*     Function: cmUnPkUeDelReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkUeDelReq 
(
DamUeDelReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkUeDelReq(func, pst, mBuf)
DamUeDelReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    U32 transId = 0;
    U16 cellId  = 0;
    U16 crnti = 0;
   
    TRC3(cmUnPkUeDelReq)
 
   CMCHKUNPKLOG(SUnpkU16,(&crnti),mBuf,EDAM006, pst);
   CMCHKUNPKLOG(SUnpkU16,(&cellId),mBuf,EDAM007, pst);
   CMCHKUNPKLOG(SUnpkU32,(&transId),mBuf,EDAM008, pst);

   WR_DAM_FREE_BUFFER (pst->region,mBuf);
    RETVALUE((*func)(pst, transId,cellId,crnti));
}/* cmUnPkUeDelReq */

/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for sending the confirmation
* for deleting the UE in wr_dam.c.
*
* @details
*
*     Function: cmUnPkUeDelCfm
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkUeDelCfm 
(
DamUeDelCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkUeDelCfm(func, pst, mBuf)
DamUeDelCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    U32 transId = 0;
    U16 cellId = 0;
    U16 crnti = 0;
 
    TRC3(cmUnPkUeDelCfm)

    CMCHKUNPKLOG(SUnpkU16,(&crnti), mBuf,EDAM001, pst);
    CMCHKUNPKLOG(SUnpkU16,(&cellId), mBuf,EDAM001, pst);
    CMCHKUNPKLOG(SUnpkU32,(&transId), mBuf,EDAM001, pst);
 
    WR_DAM_FREE_BUFFER (pst->region,mBuf);
 
    RETVALUE((*func)(pst, transId, cellId, crnti));

}/* cmUnPkUeDelCfm */


/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for the deleting the UE in wr_dam.c.
*
* @details
*
*     Function:cmUnPkCellAddReq 
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkCellAddReq 
(
DamCellAddReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkCellAddReq(pst, mBuf)
DamCellAddReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   WrDamCellInfo *cellInfo = NULLP;
   MsgLen len;
 
   TRC3(cmUnPkCellAddReq)
   
#ifndef WR_DAM_LC
   if (pst->selector == DAM_SEL_LWLC) {
      CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&cellInfo), mBuf, EEGT014, pst);
   }
   else
#endif
   {
       SGetStaticBuffer (0,0,(Data **)&cellInfo, sizeof(WrDamCellInfo), 1);
       SCpyMsgFix(mBuf,0,sizeof(WrDamCellInfo),(Data *)cellInfo,&len);
   }

    WR_DAM_FREE_BUFFER (pst->region,mBuf);
    if(NULLP == cellInfo)
    {
      RLOG0(L_ERROR, " cmUnPkTnlDelReq(): cellInfo is NULL.");
      RETVALUE(RFAILED);
    } 
  
    RETVALUE((*func)(pst, cellInfo));

}/* cmUnPkCellAddReq  */


/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for the deleting the UE in wr_dam.c.
*
* @details
*
*     Function: cmUnPkReestabReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkReestabReq 
(
DamReestabReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkReestabReq(func, pst, mBuf)
DamReestabReq func,
Pst *pst;
Buffer *mBuf;
#endif
{
   U32 transId  = 0;
   U16 cellId   = 0;
   U16 oldcrnti = 0;
   U16 newcrnti = 0;

   TRC3(cmUnPkReestabReq)

   CMCHKUNPKLOG(SUnpkU16,(&newcrnti), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU16,(&oldcrnti), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU16,(&cellId), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU32,(&transId), mBuf,EDAM001, pst);

   WR_DAM_FREE_BUFFER (pst->region,mBuf);

    RETVALUE((*func)(pst, transId, cellId, oldcrnti, newcrnti));

} /* cmUnPkReestabReq */


/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for the deleting the UE in wr_dam.c.
*
* @details
*
*     Function:cmUnPkHdlHoFailure
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkHdlHoFailure
(
DamHoFailure func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkHdlHoFailure(pst, mBuf)
DamHoFailure func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16 cellId   = 0;
   U16 crnti = 0;

   TRC3(cmUnPkHdlHoFailure)
   

   CMCHKUNPKLOG(SUnpkU16,(&crnti), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU16,(&cellId), mBuf,EDAM001, pst);

   WR_DAM_FREE_BUFFER (pst->region,mBuf);
    RETVALUE((*func)(pst, cellId,crnti));
}

/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for the deleting the UE in wr_dam.c.
*
* @details
*
*     Function:cmUnPkStartInactivityTmr
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC S16 cmUnPkStartInactivityTmr  
(
DamStartInactivityTmr func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkStartInactivityTmr(funcm, pst, mBuf)
DamStartInactivityTmr func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16 cellId   = 0;
   U16 crnti = 0;

   TRC3(cmUnPkStartInactivityTmr)

   CMCHKUNPKLOG(SUnpkU16,(&crnti), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU16,(&cellId), mBuf,EDAM001, pst);

   WR_DAM_FREE_BUFFER (pst->region,mBuf);
    RETVALUE((*func)(pst, cellId,crnti));

}/* cmUnPkStartInactivityTmr */

/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for the deleting the UE in wr_dam.c.
*
* @details
*
*     Function:cmUnPkStopUeTmr
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

#ifdef ANSI
PUBLIC S16 cmUnPkStopUeTmr 
(
DamStopUeTmr func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkStopUeTmr(func, pst, mBuf)
DamStopUeTmr func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16 cellId   = 0;
   U16 ueId = 0;

   TRC3(cmUnPkStopUeTmr)

   CMCHKUNPKLOG(SUnpkU16,(&ueId), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU16,(&cellId), mBuf,EDAM001, pst);

    WR_DAM_FREE_BUFFER (pst->region,mBuf);
    RETVALUE((*func)(pst, cellId,ueId));

}/* cmUnPkStopUeTmr */


/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation confirm  function in DAM module. 
*
* @details
*
*     Function:cmUnPkReestabCfm 
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

#ifdef ANSI
PUBLIC S16 cmUnPkReestabCfm 
(
DamReestabCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkReestabCfm(pst, mBuf)
DamReestabCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U32 transId = 0;
   U8 status   = 0;
 
   TRC3(cmUnPkReestabCfm)
      

   CMCHKUNPKLOG(SUnpkU8,&status,mBuf,EDAM002, pst);
   CMCHKUNPKLOG(SUnpkU32,&transId,mBuf,EDAM001, pst);
  
   WR_DAM_FREE_BUFFER (pst->region,mBuf);
    RETVALUE((*func)(pst, transId, status));

}/* cmUnPkReestabCfm */


/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for the deleting the UE in wr_dam.c.
*
* @details
*
*     Function:cmUnPkReCfgReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

#ifdef ANSI
PUBLIC S16 cmUnPkReCfgReq 
(
DamReCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkReCfgReq(func, pst, mBuf)
DamReCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U32 transId = 0;
   U16 cellId  = 0;
   U16 crnti   = 0;
   
   TRC3(cmUnPkReCfgReq)
  

   CMCHKUNPKLOG(SUnpkU16,(&crnti), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU16,(&cellId), mBuf,EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU32,(&transId), mBuf,EDAM001, pst);
 
   WR_DAM_FREE_BUFFER (pst->region,mBuf);

    RETVALUE((*func)(pst, transId, cellId, crnti));

}/* cmUnPkReCfgReq */

/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation function in DAM module. 
*
* @details
*
*     Function:cmUnPkTnlStChngReq 
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

#ifdef ANSI
PUBLIC S16 cmUnPkTnlStChngReq 
(
DamTnlStChngReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkTnlStChngReq(func, pst, mBuf)
DamTnlStChngReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    WrDamTnlStInfo *tnlStInfo = NULLP;
   MsgLen len;

    TRC3(cmUnPkTnlStChngReq)

#ifndef WR_DAM_LC
   if (pst->selector == DAM_SEL_LWLC) {
      CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&tnlStInfo), mBuf, EEGT014, pst);
   }
   else
#endif
   {
      SGetStaticBuffer (0,0,(Data **)&tnlStInfo, sizeof(WrDamTnlStInfo), 1);
      SCpyMsgFix(mBuf,0,sizeof(WrDamTnlStInfo),(Data *)tnlStInfo,&len);
   }
  
   WR_DAM_FREE_BUFFER (pst->region,mBuf);
    RETVALUE((*func)(pst, tnlStInfo));

}/* cmUnPkTnlStChngReq */

/* Element packing */


/*
*
*  Fun:  cmPkCmTnlInfo
*
*  Desc:  This function packs the DAM Tunnel Info.
*
*  Ret:   ROK
*
*  Notes: None
*
*  File:  wr_ifm_dam_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkDamTnlId 
(
WrDamTnlId         *tnlId,
Buffer             *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkDamTnlId(tnlId, mBuf)
WrDamTnlId         *tnlId;
Buffer             *mBuf;        /* message buffer */
#endif
{
   CMCHKPK(SPkU16,tnlId->cellId,mBuf);
   CMCHKPK(SPkU16,tnlId->crnti,mBuf);
   CMCHKPK(SPkU8,tnlId->drbId,mBuf);
   CMCHKPK(cmPkDamTnlType,tnlId->tnlType,mBuf);

   RETVALUE(ROK);

}/* End of cmPkDamTnlId */

/*
*
*    Fun:  cmPkCmTnlInfo 
*
*    Desc:  This function packs the DAM Tunnel Info. 
*
*    Ret:   ROK
*
*    Notes: None
*
*    File:  wr_ifm_dam_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCmTnlInfo 
(
WrDamTnlInfo             *tnlInfo,     
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkCmTnlInfo(tnlInfo,mBuf)
WrDamTnlInfo             *tnlInfo;     
Buffer                   *mBuf;        /* message buffer */
#endif
{
  TRC3(cmPkCmTnlInfo)
  CMCHKPK(SPkU32,tnlInfo->transId,mBuf);
  CMCHKPK(cmPkDamTnlId,&tnlInfo->tnlId,mBuf);
  CMCHKPK(SPkU32,tnlInfo->dscp,mBuf);
  CMCHKPK(cmPkDamTnlType,tnlInfo->tnlType,mBuf);
  CMCHKPK(cmPkCmTptAddr,&tnlInfo->dstAddr,mBuf);
  CMCHKPK(cmPkCmTptAddr,&tnlInfo->srcAddr,mBuf);
  CMCHKPK(cmPkDamEgtpTeid,tnlInfo->remTeid,mBuf);

  RETVALUE(ROK);
}/* End of cmPkCmTnlInfo*/


/*
*
*    Fun:  cmPkDamCellInfo 
*
*    Desc:  This function packs the DAM Cell Info. 
*
*    Ret:   ROK
*
*    Notes: None
*
*    File:  wr_ifm_dam_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkDamCellInfo 
(
WrDamCellInfo  *cellInfo,
Buffer         *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkDamCellInfo(cellInfo,mBuf)
WrDamCellInfo  *cellInfo;
Buffer         *mBuf;        /* message buffer */
#endif
{
  TRC3(cmPkDamCellInfo)
  CMCHKPK(SPkU16,cellInfo->cellId,mBuf);
  CMCHKPK(SPkU16,cellInfo->startRnti,mBuf);
  CMCHKPK(SPkU16,cellInfo->maxRntis,mBuf);

  RETVALUE(ROK);

}/* cmPkDamCellInfo */

/*
*
*    Fun:  cmPkDamPdcpDatCfm 
*
*    Desc:  This function packs the DAM Tunnel Info. 
*
*    Ret:   ROK
*
*    Notes: None
*
*    File:  wr_ifm_dam_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkDamPdcpDatCfm
(
Pst         *pst,
CmLtePdcpId  pdcpId
)
#else
PUBLIC S16 cmPkDamPdcpDatCfm(pst,pdcp)
Pst         *pst;
CmLtePdcpId  pdcpId
#endif
{
  Buffer *mBuf = NULLP;

  TRC3(cmPkDamPdcpDatCfm)

  if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkLtePdcpId,&pdcpId,mBuf,0,pst);
   pst->event = (Event)EVTDAMPDCPDATCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamPdcpDatCfm */

/*
*
*    Fun:  cmUnpkDamPdcpDatCfm 
*
*    Desc:  This function packs the DAM Tunnel Info. 
*
*    Ret:   ROK
*
*    Notes: None
*
*    File:  wr_ifm_dam_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkDamPdcpDatCfm
(
DamPdcpDatCfm func,
Pst    *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkDamPdcpDatCfm(pst,pdcp)
DamPdcpDatCfm func;
Pst         *pst;
Buffer *mBuf;
#endif
{

  CmLtePdcpId  pdcpId;

  TRC3(cmUnpkDamPdcpDatCfm)

  CMCHKUNPKLOG(cmUnpkLtePdcpId,&pdcpId,mBuf,0,pst);

  WR_DAM_FREE_BUFFER (pst->region,mBuf);
    RETVALUE((*func)(pst, pdcpId));

}/* End of cmUnpkDamPdcpDatCfm*/

/**
* @brief This API is used to pack the EGTP-U error indication
*
* @details
*
* Function: cmPkEgtpErrInd
*
* @param[in] Pst *  pst
* @param[in] U32 lclTeid
* @param[in] U32 numDrbs
* @param[in] U16 crnti
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkEgtpErrInd
(
Pst *pst,
U32 lclTeid, 
U32                          numDrbs,
U16                          crnti
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtpErrInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU32,lclTeid,mBuf);
   CMCHKPK(SPkU32,numDrbs,mBuf);
   CMCHKPK(SPkU16,crnti,mBuf);

   pst->event = (Event)EVTDAMEGTERRIND;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkEgtpErrInd */

/*
*
*    Fun:  cmUnpkEgtpErrInd
*
*    Desc:  This function packs the DAM Tunnel Info. 
*
*    Ret:   ROK
*
*    Notes: None
*
*    File:  wr_ifm_dam_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtpErrInd
(
DamEgtpErrInd func,
Pst    *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtpErrInd(pst,mBuf)
DamEgtpErrInd func;
Pst         *pst;
Buffer *mBuf;
#endif
{

  U32 lclTeid = 0;
  U32 numDrbs = 0;
  U16 crnti = 0;

  TRC3(cmUnpkEgtpErrInd)

  CMCHKUNPK(SUnpkU16,&crnti, mBuf);
  CMCHKUNPK(SUnpkU32,&numDrbs, mBuf);
  CMCHKUNPK(SUnpkU32,&lclTeid, mBuf);

  WR_DAM_FREE_BUFFER (pst->region,mBuf);
    RETVALUE((*func)(pst,lclTeid,numDrbs,crnti));

}/* End of cmUnpkEgtpErrInd */


/**
* @brief This API is used to  
* send Bind request to DAM module 
*
* @details
*
* Function:cmPkDamBndReq
* 
* @param[in]   Pst *  pst
* @param[in]   SuId suId 
* @param[in]   SpId spId 
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkDamBndReq 
(
Pst    *pst,
SuId   suId,
SpId   spId
)
#else
PUBLIC S16 cmPkDamBndReq(pst,suId,spId)
Pst * pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamBndReq)
   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU16,suId, mBuf,0, pst);
   CMCHKPKLOG(SPkU32,spId, mBuf,0, pst);
   
   pst->event = (Event) EVTDAMBNDREQ;
   RETVALUE(SPstTsk(pst, mBuf));

} /* end of cmPkDamBndReq*/

/**
* @brief This API is used for  unpacking the function
* DAM bind request
*
* @details
*
*     Function:cmUnpkDamBndReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

#ifdef ANSI
PUBLIC S16 cmUnpkDamBndReq 
(
DamBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkDamBndReq(func, pst, mBuf)
DamBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId  = 0;
   SpId spId = 0;

   TRC3(cmUnpkDamBndReq)

   CMCHKUNPKLOG(SUnpkU16,(U16*)(&spId), mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU16,(U16*)(&suId), mBuf,0, pst);

   WR_DAM_FREE_BUFFER (pst->region,mBuf);
   RETVALUE((*func)(pst, suId, spId));
}/* end of cmUnpkDamBndReq*/

/**
* @brief This API is used to  
* send Bind Cfm to application
*
* @details
*
* Function:cmPkDamBndCfm
* 
* @param[in]   Pst *  pst
* @param[in]   SuId suId 
* @param[in]   U8   status 
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkDamBndCfm
(
Pst    *pst,
SuId   suId,
U8     status
)
#else
PUBLIC S16 cmPkDamBndCfm(pst,suId,status)
Pst * pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamBndCfm)
   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(SPkU8,status, mBuf,0, pst);
   CMCHKPKLOG(SPkU16,suId, mBuf,0, pst);
   
   pst->event = (Event)EVTDAMBNDCFM;
   RETVALUE(SPstTsk(pst, mBuf));

} /* end of cmPkDamBndCfm*/

/**
* @brief This API is used for  unpacking the function
* DAM bind confirm
*
* @details
*
*     Function:cmUnpkDamBndCfm
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

#ifdef ANSI
PUBLIC S16 cmUnpkDamBndCfm
(
DamBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkDamBndCfm(func, pst, mBuf)
DamBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId  = 0;
   U8 status = 0;

   TRC3(cmUnpkDamBndCfm)

   CMCHKUNPKLOG(SUnpkU16,(U16*)(&suId), mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU8,(&status), mBuf,0, pst);

   WR_DAM_FREE_BUFFER (pst->region,mBuf);
   RETVALUE((*func)(pst, suId, status));
}/* end of cmUnpkDamBndCfm*/


/*ccpu00138576 start*/
/**
* @brief This API is used to  
* set Data rcvd flag from Enbapp to DAM.
*
* @details
*
* Function:cmPkSetDataRcvdFlag
* 
* @param[in]   Pst *  pst
* @param[in]   U16 cellId 
* @param[in]   U16 ueId 
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkSetDataRcvdFlag 
(
Pst *pst,
U16 cellId,
U16 ueId 
)
#else
PUBLIC S16 cmPkSetDataRcvdFlag(pst,cellId,ueId)
Pst * pst;
U16 cellId;
U16 ueId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkSetDataRcvdFlag)
   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU16,(cellId), mBuf,0, pst);
   CMCHKPKLOG(SPkU32,(ueId), mBuf,0, pst);
   
   pst->event = (Event)EVTDAMDATRCVDFLAG;
   RETVALUE(SPstTsk(pst, mBuf));

} /* end of cmPkSetDataRcvdFlag */

/**
* @brief This API is used for  unpacking the function
* Set Data Rcvd Flag
*
* @details
*
*     Function:cmUnPkSetDataRcvdFlag
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

#ifdef ANSI
PUBLIC S16 cmUnPkSetDataRcvdFlag 
(
DamSetDataRcvdFlag func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkSetDataRcvdFlag(func, pst, mBuf)
DamSetDataRcvdFlag func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16 cellId   = 0;
   U16 ueId = 0;

   TRC3(cmUnPkSetDataRcvdFlag)

   CMCHKUNPKLOG(SUnpkU16,(&ueId), mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU16,(&cellId), mBuf,0, pst);

   WR_DAM_FREE_BUFFER (pst->region,mBuf);
   RETVALUE((*func)(pst, cellId, ueId));
}/* end of cmUnPkSetDataRcvdFlag */
/*ccpu00138576 end*/

/********************************************************************30**

           End of file:     fc_ifm_dam_utils.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:51:47 2014

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
/main/1        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
