/********************************************************************20**

     Name:     SON Application

     Type:     

     Desc:     This file contains 
               

     File:     nl_earfcn_sel.c

     Sid:      bk_earfcn_sel.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 19:05:35 2014

     Prg:       

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="SON";
static int RLOG_FILE_ID=246;
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

PRIVATE S16 nlCellSelectEarfcnByDSon ARGS((
NlCellCb      *cellCb,   /* cell control block */
LnlCellCfg    *cellCfg  /* cell config structure  */
));


/**
 * @brief validate the EARFCN configuration received from SM
 *
 * @details
 *
 *     Function : nlValidateCellEarfcnCfg
 *
 *     This function will validate EARFCN configuration
 *     received from SM
 *
 *  @param[in]  cellCfg   : cell configuration parameter structure
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlValidateCellEarfcnCfg
(
LnlCellCfg    *cellCfg  /* cell config structure  */
)
#else
PUBLIC S16 nlValidateCellEarfcnCfg(cellCfg)
(
LnlCellCfg   *cellCfg;    /* cell config structure */
)
#endif
{
   S16 ret = ROK;
   TRC3(nlValidateCellEarfcnCfg);
   do
   {
      if(cellCfg->numDlEarfcn == 0) 
      {
         RLOG0(L_ERROR, "Empty DL-Earfcn list received");
         ret = RFAILED;
         break;
      }
      if(cellCfg->numUlEarfcn == 0) 
      {
         RLOG0(L_ERROR, "Empty UL-Earfcn list received");
         ret = RFAILED;
         break;
      }
      if(cellCfg->numDlEarfcn != cellCfg->numUlEarfcn)
      {
         RLOG0(L_ERROR, "number of DL-Earfcn and UL-Earfcn mismatched");
         ret = RFAILED;
         break;
      }
   }while(0);

   RETVALUE(ret);
}

/**
 * @brief select a EARFCN from EARFCN List.
 *
 * @details
 *
 *     Function : nlCellSelectEarfcnByDSon
 *
 *     This function selects a unique EARFCN from EARFCN list
 *     received from SM.
 *
 *  @param[in]  cellCb    : cell control block
 *  @param[in]  cellCfg   : cell configuration parameter structure
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PRIVATE S16 nlCellSelectEarfcnByDSon
(
NlCellCb      *cellCb,   /* cell control block */
LnlCellCfg    *cellCfg  /* cell config structure  */
)
#else
PRIVATE S16 nlCellSelectEarfcnByDSon(cellCb, cellCfg)
(
NlCellCb     *cellCb;     /* cell control block*/
LnlCellCfg   *cellCfg;    /* cell config structure */
)
#endif
{
   Bool                 earfcnSel = FALSE;
   U32                  earfcnCount;
   U32                  remEarfcnCount;
   NlRemScanEarfcnSel   remScanEarfcnSel[LNL_MAX_NUM_EARFCN];
   NlRemScanEarfcnSel   *dlEarfcnSel = NULLP;
   U8                   earfcnSelCount = 0;
   U8                   count;

   TRC3(nlCellSelectEarfcnByDSon);

   for(earfcnCount = 0; earfcnCount < cellCfg->numDlEarfcn; earfcnCount ++)
   {
      earfcnSel = TRUE;
      for(remEarfcnCount = 0; remEarfcnCount <
                  cellCfg->numRemScanEarfcn; remEarfcnCount ++)
      {
         if(cellCfg->dlEarfcnList[earfcnCount] ==
                     cellCfg->remScanEarfcn[remEarfcnCount].dlEarfcn)
         {
            remScanEarfcnSel[earfcnSelCount].rssi =
                     cellCfg->remScanEarfcn[remEarfcnCount].rssi;
            remScanEarfcnSel[earfcnSelCount].dlEarfcnIdx = earfcnCount;
            earfcnSelCount ++;
            earfcnSel = FALSE;
            break;
         }
      }
      if(FALSE !=earfcnSel)
      {
         cellCb->cellInfo.dlEarfcn = cellCfg->dlEarfcnList[earfcnCount];
         cellCb->cellInfo.ulEarfcn = cellCfg->ulEarfcnList[earfcnCount];
         break;
      }
   }
   if(TRUE != earfcnSel)
   {
      dlEarfcnSel = &remScanEarfcnSel[0];
      /*select the EARFCN from REMSCAN list with least RSSI value*/
      for(count = 1; count < earfcnSelCount; count ++)
      {
         if(dlEarfcnSel->rssi > remScanEarfcnSel[count].rssi)
         {
            dlEarfcnSel = &(remScanEarfcnSel[count]);
         }
      }
      /*Update the DL/UL EARFCN in cell control block*/
      cellCb->cellInfo.dlEarfcn = cellCfg->dlEarfcnList[dlEarfcnSel->dlEarfcnIdx];
      cellCb->cellInfo.ulEarfcn = cellCfg->ulEarfcnList[dlEarfcnSel->dlEarfcnIdx];
   }
   RETVALUE(ROK);
}

/**
 * @brief Layer Manager cell Earfcn Configuration request handler.
 *
 * @details
 *
 *     Function : nlCellSelectEarfcn
 *
 *     This function handles the SON cell Earfcn configuration
 *     request received from the Layer Manager.
 *
 *  @param[in]  cellCb    : cell control block
 *  @param[in]  cellCfg   : cell configuration parameter structure
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlCellSelectEarfcn
(
NlCellCb      *cellCb,   /* cell control block */
LnlCellCfg    *cellCfg  /* cell config structure  */
)
#else
PUBLIC S16 nlCellSelectEarfcn(cellCb, cellCfg)
(
NlCellCb     *cellCb;     /* cell control block*/
LnlCellCfg   *cellCfg;    /* cell config structure */
)
#endif
{
   TRC3(nlCellSelectEarfcn);

   switch(nlCb.genCfg.earfcnSelType)
   {
      case NL_PCI_SEL_DISABLE :
      {
         cellCb->cellInfo.dlEarfcn = cellCfg->dlEarfcnList[0]; 
         cellCb->cellInfo.ulEarfcn = cellCfg->ulEarfcnList[0];
         RLOG2(L_INFO, "SON selected DL-Earfcn : %d UL-earfcn : %d",
           cellCb->cellInfo.dlEarfcn, cellCb->cellInfo.ulEarfcn);
         /*send selected ERAFCN Indication to SM */
         nlSendEarfcnUpdateInd(cellCb);
      }
      break;
      case NL_PCI_SEL_DSON :
      {
         nlCellSelectEarfcnByDSon(cellCb, cellCfg);
         RLOG2(L_INFO, "SON selected DL-Earfcn : %d UL-earfcn : %d",
           cellCb->cellInfo.dlEarfcn, cellCb->cellInfo.ulEarfcn);
         /*send selected ERAFCN Indication to SM */
         nlSendEarfcnUpdateInd(cellCb);
      }
      break;
      case NL_PCI_SEL_CSON :
      {

      }
      break;
      default :
      break;
   }
   RETVALUE(ROK);
}

/********************************************************************30**

           End of file:     bk_earfcn_sel.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 19:05:35 2014

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

