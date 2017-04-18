/********************************************************************20**

     Name:     SON Application

     Type:     

     Desc:     This file contains 
               

     File:     nl_txpower_sel.c

     Sid:      bk_txpower_sel.c@@/main/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:56 2016

     Prg:       

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="SON";
static int RLOG_FILE_ID=256;
static int RLOG_MODULE_ID=256;

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
#include "rl_common.h"     /* RLOG defines */   
#include "rl_interface.h"   
#include "lnl.h"           /* NL Interface defines */
#include "nlu.h"
#include "nl.h"            /* SON defines */
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

#include "lnl.x"           /* NL Interface includes */
#include "nlu.x"
#include "nl.x"            /* SON includes */

/* local defines */

/* local typedefs */
 
/* local externs */
/* forward references */


/**
 * @brief configure the Tx power received from SM
 *
 * @details
 *
 *     Function : nlCellStoreTxPowerCfg
 *
 *     This function will configure the Tx Power in cell control block
 *     received from SM.
 *
 *  @param[in]  cellCb    : cell control block
 *  @param[in]  cellCfg   : cell configuration
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlCellStoreTxPowerCfg
(
NlCellCb     *cellCb,
LnlCellCfg   *cellCfg
)
#else
PUBLIC S16 nlCellStoreTxPowerCfg(cellCb, cellCfg)
(
NlCellCb     *cellCb;
LnlCellCfg   *cellCfg;
)
#endif
{
   U32   count;
   TRC3(nlCellStoreTxPowerCfg);
   cellCb->txPowerCfg.refSignalPwrCnt = cellCfg->txPwrCfg.refSignalPwrCnt;
  
   cellCb->tgtRsrp        = cellCfg->tpmCfg.tgtRsrp;
   cellCb->attnConstIdx   = cellCfg->tpmCfg.attnConstIdx; 
   cellCb->rsysTpmRsrpMin = cellCfg->tpmCfg.minRsrp; 
   cellCb->rsysTpmRsrpMax = cellCfg->tpmCfg.maxRsrp;
   cellCb->txPowerSel.refSignalTxPwr = NL_INVALID_RSRP;

   for(count = 0; count < cellCb->txPowerCfg.refSignalPwrCnt; count++)
   {
      cellCb->txPowerCfg.referenceSignalPwr[count] = cellCfg->txPwrCfg.referenceSignalPwr[count];
   }
   cellCb->txPowerCfg.pBCnt = cellCfg->txPwrCfg.pBCnt;
   for(count = 0; count < cellCb->txPowerCfg.pBCnt; count ++)
   {
      cellCb->txPowerCfg.pB[count] = cellCfg->txPwrCfg.pB[count];
   } 
   cellCb->txPowerCfg.pACnt = cellCfg->txPwrCfg.pACnt;
   for(count = 0; count < cellCb->txPowerCfg.pACnt; count ++)
   {
      cellCb->txPowerCfg.pA[count] = cellCfg->txPwrCfg.pA[count];
   }
   cellCb->txPowerCfg.pschPowerOffCnt = cellCfg->txPwrCfg.pschPowerOffCnt;
   for(count = 0; count < cellCb->txPowerCfg.pschPowerOffCnt; count ++)
   {
      cellCb->txPowerCfg.pschPowerOffset[count] = cellCfg->txPwrCfg.pschPowerOffset[count];
   }
   cellCb->txPowerCfg.sschPowerOffCnt = cellCfg->txPwrCfg.sschPowerOffCnt;
   for(count = 0; count < cellCb->txPowerCfg.sschPowerOffCnt; count ++)
   {
      cellCb->txPowerCfg.sschPowerOffset[count] = cellCfg->txPwrCfg.sschPowerOffset[count];
   }
   cellCb->txPowerCfg.pbchPowerOffCnt = cellCfg->txPwrCfg.pbchPowerOffCnt;
   for(count = 0; count < cellCb->txPowerCfg.pbchPowerOffCnt; count ++)
   {
      cellCb->txPowerCfg.pbchPowerOffset[count] = cellCfg->txPwrCfg.pbchPowerOffset[count];
   }
   RETVALUE(ROK);
}

/**
 * @brief Layer Manager cell TxPower Configuration request handler.
 *
 * @details
 *
 *     Function : nlCellSelectTxPower
 *
 *     This function handles the SON cell TxPower configuration
 *     request received from the Layer Manager.
 *
 *  @param[in]  cellCb    : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlCellSelectTxPower
(
NlCellCb      *cellCb   /* cell control block */
)
#else
PUBLIC S16 nlCellSelectTxPower(cellCb)
(
NlCellCb     *cellCb;     /* cell control block*/
)
#endif
{
   TRC3(nlCellSelectTxPower);

   switch(nlCb.genCfg.txPowerSelType)
   {
      case NL_TXPOWER_SEL_DISABLE :
      {
         /*select TX Power */
         cellCb->txPowerSel.refSignalTxPwr = cellCb->txPowerCfg.referenceSignalPwr[0]; 
         cellCb->txPowerSel.pssPowerOffset = cellCb->txPowerCfg.pschPowerOffset[0]; 
         cellCb->txPowerSel.sssPowerOffset = cellCb->txPowerCfg.sschPowerOffset[0]; 
         cellCb->txPowerSel.pbchPowerOffset = cellCb->txPowerCfg.pbchPowerOffset[0]; 
         //cellCb->txPowerSel.pBCnt = cellCb->txPowerCfg.pBCnt; 
         //cellCb->txPowerSel.pACnt = cellCb->txPowerCfg.pACnt;
         cellCb->txPowerSel.pB = cellCb->txPowerCfg.pB[0];
         cellCb->txPowerSel.pout = cellCb->txPowerCfg.pA[0];
         RLOG4(L_INFO, "SON selected RefSigTxPwr: %d pssPowerOffse:t %d sssPowerOffset: %d pbchPowerOffset: %d \n",
                        cellCb->txPowerSel.refSignalTxPwr, cellCb->txPowerSel.pssPowerOffset, cellCb->txPowerSel.sssPowerOffset,
                         cellCb->txPowerSel.pbchPowerOffset); 
         nlHandleCellSelectedTxPower(cellCb);
         RETVALUE(ROK);
      }
      break;
      case NL_TXPOWER_SEL_DSON :
      {
         NL_UPDATE_CELL_STATE(cellCb, NL_CELL_STATE_WAIT_TXPOWER_CFG);
         nlCellSelectTxPowerByDSon(cellCb);
         RETVALUE(ROK);
      }
      break;
      case NL_TXPOWER_SEL_CSON :
      {

      }
      break;
      default :
      break;
   }
   RETVALUE(RFAILED);
}


/* Periodic REM for TPM */
/**
 * @brief Layer Manager cell TxPower Configuration request handler.
 *
 * @details
 *
 *     Function : nlHdlPeriodicRemCellSrchRsp
 *
 *     This function handles the SON cell TxPower configuration
 *     request received from the Layer Manager.
 *
 *  @param[in]  cellCb    : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlHdlPeriodicRemCellSrchRsp
(
NluPeriodicRemCellSearchRsp  *cellSrchRsp   /* cell Info */
)
#else
PUBLIC S16 nlHdlPeriodicRemCellSrchRsp(cellCb)
(
NluPeriodicRemCellSearchRsp  *cellSrchRsp;   /* cell Info */
)
#endif
{
   TRC3(nlHdlPeriodicRemCellSrchRsp);

   switch(nlCb.genCfg.txPowerSelType)
   {
      case NL_TXPOWER_SEL_DISABLE :
      {
         RLOG0(L_INFO,"TxPower Selection Disbaled, Drop message");
         RETVALUE(ROK);
      }
      break;
      case NL_TXPOWER_SEL_DSON :
      {
         nlBuildPeriodicRemResultInd(cellSrchRsp);
         RETVALUE(ROK);
      }
      break;
      case NL_TXPOWER_SEL_CSON :
      {

      }
      break;
      default :
      break;
   }
   RETVALUE(RFAILED);
}


/********************************************************************30**

           End of file:     bk_txpower_sel.c@@/main/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:56 2016

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
*********************************************************************91*/

