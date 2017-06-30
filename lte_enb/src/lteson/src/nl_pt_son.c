/********************************************************************20**

     Name:     SON Application

     Type:     

     Desc:     This file contains 
               

     File:     

     Sid:      bk_pt_son.c@@/main/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:56 2016

     Prg:       

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="SON";
static int RLOG_FILE_ID=252;
static int RLOG_MODULE_ID=256;

#include <stdlib.h>
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
#include "nl_rsystpm.h"    /* Rsys TPM tables */

/* local defines */

/* local typedefs */
 
/* local externs */
/* forward references */
PRIVATE S8 nlCellSelectTxPowerRsysTpm ARGS((
   NlCellCb *cellCb
));

/**
 * @brief DSON Rem result indication message handler.
 *
 * @details
 *
 *     Function : nlBuildRemResultInd
 *
 *     This function build the rem result indication and send to vendor DSON.
 *
 *  @param[in]  cellCB  : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlBuildRemResultInd
(
NlCellCb               *cellCb
)
#else
PUBLIC S16 nlBuildRemResultInd(cellCb)
(
NlCellCb               *cellCb;
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlBuildRemResultInd");
   RETVALUE(ROK);
}

/**
 * @brief DSON Rem result indication message handler.
 *
 * @details
 *
 *     Function : nlBuildPeriodicRemResultInd
 *
 *     This function build the periodic rem result indication and send to vendor DSON.
 *
 *  @param[in]  cellCB  : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlBuildPeriodicRemResultInd
(
NluPeriodicRemCellSearchRsp  *cellSrchRsp
)
#else
PUBLIC S16 nlBuildPeriodicRemResultInd(cellSrchRsp)
(
NluPeriodicRemCellSearchRsp  *cellSrchRsp;
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlBuildPeriodicRemResultInd");
   RETVALUE(ROK);
}

/**
 * @brief Layer Manager cell TxPower Configuration request handler.
 *
 * @details
 *
 *     Function : nlCellSelectTxPowerByDSon
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
PUBLIC S16 nlCellSelectTxPowerByDSon
(
NlCellCb      *cellCb   /* cell control block */
)
#else
PUBLIC S16 nlCellSelectTxPowerByDSon(cellCb)
(
NlCellCb     *cellCb;     /* cell control block*/
)
#endif
{
   S8   servCellRsrp;
   
   RLOG0(L_INFO,"In SON PT nlCellSelectTxPowerByDSon");
   
   cellCb->txPowerSel.pssPowerOffset = cellCb->txPowerCfg.pschPowerOffset[0];
   cellCb->txPowerSel.sssPowerOffset = cellCb->txPowerCfg.sschPowerOffset[0];
   cellCb->txPowerSel.pbchPowerOffset = cellCb->txPowerCfg.pbchPowerOffset[0];
   //cellCb->txPowerSel.pBCnt = cellCb->txPowerCfg.pBCnt;
   //cellCb->txPowerSel.pACnt = cellCb->txPowerCfg.pACnt;
   cellCb->txPowerSel.pB = cellCb->txPowerCfg.pB[0];
   cellCb->txPowerSel.pout = cellCb->txPowerCfg.pA[0];
   
   /* Select TX Power */
   servCellRsrp = nlCellSelectTxPowerRsysTpm(cellCb);

   if (servCellRsrp != cellCb->txPowerSel.refSignalTxPwr)
   {
      cellCb->txPowerSel.refSignalTxPwr = servCellRsrp;
      if (cellCb->state == NL_CELL_STATE_INIT)
      {
         nlHandleCellSelectedTxPower(cellCb);
      }
      else
      {
         nlSendTxPwrUpdateInd(cellCb);
      }
   }
   RLOG4(L_INFO, "RSYS SON selected RefSigTxPwr: %d pssPowerOffset %d" 
         " sssPowerOffset: %d pbchPowerOffset: %d \n",
         cellCb->txPowerSel.refSignalTxPwr, cellCb->txPowerSel.pssPowerOffset, 
         cellCb->txPowerSel.sssPowerOffset,
         cellCb->txPowerSel.pbchPowerOffset);

   RETVALUE(ROK);
}

/**
 * @brief DSON message request handler.
 *
 * @details
 *
 *     Function : NlVendorDSonDatInd
 *
 *     This function handles the messages
 *     received from the vendor DSON.
 *
 *  @param[in]  pst     : the post structure
 *  @param[in]  evtMsg  : the message structure received from DSON
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 NlVendorDSonDatInd
(
Pst                   *pst,      /* post structure  */
NlVendorDSonEventMsg  *evtMsg    /* message structure from DSON */
)
#else
PUBLIC S16 NlVendorDSonDatInd(pst, evtMsg)
(
Pst                   *pst;      /* post structure */
NlVendorDSonEventMsg  *evtMsg;   /* message structure from DSON */
)
#endif
{
   RLOG0(L_INFO,"In SON PT NlVendorDSonDatInd");
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack message from DSON
*
* @details
*
*     Function: nlUnpkVendorDSonDatInd
*
*  @param[in]   func      : primitive to be called 
*  @param[in]   pst       : post structure
*  @param[in]   mBuf      : message recv from DSON
*  @return   S16
*      -# Success         : ROK
*      -# Failure         : RFAILED
**/
#ifdef ANSI
PUBLIC S16 nlUnpkVendorDSonDatInd
(
NlVendorDSonDatIndFp func,    /* primitive to call after unpacking */
Pst                  *pst,    /* post structure */
Buffer               *mBuf    /* message buffer which will be unpacked */
)
#else
PUBLIC S16 nlUnpkVendorDSonDatInd(func, pst, mBuf)
NlVendorDSonDatIndFp func;    /* primitive to call after unpacking */
Pst                  *pst;    /* post structure */
Buffer               *mBuf;   /* message buffer which will be unpacked */
#endif
{
   RLOG0(L_INFO,"In SON PT nlUnpkVendorDSonDatInd");
   RETVALUE(ROK);
}

/**
* @brief This API is used to send connection establishment request to BRDCM DSON.
*
* @details
*
*  Function: nlVendorDSonConnEstReq
*
*  @param[in]   Void     : post structure
*  @return      S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 nlVendorDSonConnEstReq
(
Void
)
#else
PUBLIC S16 nlVendorDSonConnEstReq(Void)
(
Void ;
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlVendorDSonConnEstReq");
   RETVALUE(ROK);
}

/**
 * @brief Initialise the BRDCM SON DB information
 *
 * @details
 *
 *     This function will initialise the BRDCM-SON DB information
 *     with proper value
 *
 *  @param[in]  Void
 *  @return  Void
 *
 **/
#ifdef ANSI
PUBLIC Void nlInitSonDB
(
Void
)
#else
PUBLIC Void nlInitSonDB(Void)
(
Void
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlInitSonDB");
   RETVOID;
}

/**
 * @brief sending number of neighbor connected with this cell to BRDCM-SON
 *
 * @details
 *
 *     This function sends the number of neighbors connected with
 *     serving cell with same operator to BRDCM-SON.
 *
 *  @param[in]  numNgh  : number of neighbors connected with this cell
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlReportNumNghToSon
(
U16   numNgh
)
#else
PUBLIC S16 nlReportNumNghToSon(numNgh)
(
U16   numNgh;
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlReportNumNghToSon");
   RETVALUE(ROK);
}
/**
 * @brief handle the storing of UE information in SON DB when
 *  UE attached in eNB
 *
 * @details
 *  This function will check whether the corresponding UE already present
 *  or not in SON DB. If the UE is not present in DB then insert into SON DB.
 *
 *  @param[in]  evtMsg  : UE added information
 *  @param[in]  cellCb  : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *
 **/
#ifdef ANSI
PUBLIC S16 nlConfigUeAddEvtHndlr
(
NlEventMsg       *evtMsg,      /*!< UE added message structure  */
NlCellCb         *cellCb       /*!< cell control block*/
)
#else
PUBLIC S16 nlConfigUeAddEvtHndlr(evtMsg, cellCb)
(
NlEventMsg      *evtMsg;       /*!< UE added message structure */
NlCellCb        *cellCb;       /*!< cell control block*/
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlConfigUeAddEvtHndlr");
   RETVALUE(ROK);       
}

/**
 * @brief handle the deactivation of UE information in SON DB when
 *  UE detached from eNB
 *
 * @details
 *   This function will delete the UE information form SON DB.
 *
 *  @param[in]  evtMsg  : UE deleted information
 *  @param[in]  cellCb  : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *
 **/
#ifdef ANSI
PUBLIC S16 nlConfigUeDeleteEvtHndlr
(
NlEventMsg       *evtMsg,      /*!< UE deleted message structure  */
NlCellCb         *cellCb       /*!< cell control block*/
)
#else
PUBLIC S16 nlConfigUeDeleteEvtHndlr(evtMsg, cellCb)
(
NlEventMsg      *evtMsg;       /*!< UE deleted message structure */
NlCellCb        *cellCb;       /*!< cell control block*/
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlConfigUeDeleteEvtHndlr");
   RETVALUE(ROK);  
}
/**
 * @brief handle the UE measurement report received from eNB-APP
 *
 * @details
 *
 *  TODO
 *
 *
 *  @param[in]  evtMsg  : UE measurement report information
 *  @param[in]  cellCb  : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlConfigUeMeasRptEvtHndlr
(
NlEventMsg       *evtMsg,      /*!< UE measurement report message structure */
NlCellCb         *cellCb       /*!< cell control block*/
)
#else
PUBLIC S16 nlConfigUeMeasRptEvtHndlr(evtMsg, cellCb)
(
NlEventMsg      *evtMsg;       /*!< UE measurement report message structure */
NlCellCb        *cellCb;       /*!< cell control block*/
)
#endif
{
  // RLOG0(L_INFO,"In SON PT nlConfigUeMeasRptEvtHndlr");
   RETVALUE(ROK);
}

/**
 * @brief handle the UE CQI report received from eNB-APP
 *
 * @details
 *
 *  TODO
 *
 *
 *  @param[in]  evtMsg  : UE CQI report information
 *  @param[in]  cellCb  : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlConfigUeCqiRptEvtHndlr
(
NlEventMsg       *evtMsg,      /*!< UE CQI report message structure */
NlCellCb         *cellCb       /*!< cell control block*/
)
#else
PUBLIC S16 nlConfigUeCqiRptEvtHndlr(evtMsg, cellCb)
(
NlEventMsg      *evtMsg;       /*!< UE CQI report message structure */
NlCellCb        *cellCb;       /*!< cell control block*/
)
#endif
{
   //RLOG0(L_INFO,"In SON PT nlConfigUeCqiRptEvtHndlr");
   RETVALUE(ROK);
}

/**
 * @brief handle the modification of UE CRNTI value in SON DB
 *
 * @details
 *  This function will search the UE with old CRNTI value from SON DB.
 *  If UE is present in SON DB then update the CRNTI value with new
 *  CRNTI value and store in SON DB.
 *
 *  @param[in]  evtMsg  : UE added information
 *  @param[in]  cellCb  : cell control block
 *  @return  S16
 *     -# Success       : ROK
 *
 **/
#ifdef ANSI
PUBLIC S16 nlConfigUeModEvtHndlr
(
NlEventMsg       *evtMsg,      /*!< UE added message structure  */
NlCellCb         *cellCb       /*!< cell control block*/
)
#else
PUBLIC S16 nlConfigUeModEvtHndlr(evtMsg, cellCb)
(
NlEventMsg      *evtMsg;       /*!< UE added message structure */
NlCellCb        *cellCb;       /*!< cell control block*/
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlConfigUeModEvtHndlr");
   RETVALUE(ROK);
}
/**
 * @brief DSON Shutdown message triggering
 *
 * @details
 *
 *     Function : nlShutDownVendorDSon
 *
 *     This function will inform BRDCM SON about shutdown of eNB stack
 *
 *  @param[in]  Void :
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlShutDownVendorDSon
(
Void
)
#else
PUBLIC S16 nlShutDownVendorDSon(Void)
(
Void;
)
#endif
{
   RLOG0(L_INFO,"In SON PT nlShutDownVendorDSon");
   RETVALUE(ROK);
}
/**
 * @brief Rsys TPM function.
 *
 * @details
 *
 *     Function : nlCellSelectTxPowerRsysTpm
 *
 *     This function calculates the TX power configuration
 *     for the cell based on the strongest neighbour cell RSRP power.
 *
 *  @param[in/out]  cellCb     : cell control block
 *  @return         rsrpPwr    : Reference Sig power        
 *
 **/
#ifdef ANSI
PRIVATE S8 nlCellSelectTxPowerRsysTpm
(
NlCellCb          *cellCb    /* cell control block */
)
#else
PRIVATE S8 nlCellSelectTxPowerRsysTpm (cellCb)
(
NlCellCb          *cellCb;   
)
#endif
{
   NlNghServCellCb    *strngstNghCell = NULLP; 
   S8                  rsrpDiff;
   S8                  rsrpPwr;  
   S16                 remRsrp;

   TRC3(nlCellSelectTxPowerRsysTpm);

   /* Find out the strongest Neighbour */
   nlUtlFindStrongestNghCell(cellCb, &strngstNghCell); 
   
   /* No neighbours */
   if (strngstNghCell == NULLP)
   {
      rsrpPwr = cellCb->txPowerCfg.referenceSignalPwr[0]; 
      RETVALUE(rsrpPwr);
   }
   remRsrp = strngstNghCell->servCellInfo.rsrp-NL_RSRP_OFFSET;

   if (remRsrp >= cellCb->tgtRsrp)
   {
      RLOG2(L_INFO, "RSYS SON TPM Rem Rsrp(%d) of Neigh > Tgt Rsrp %d\n", 
             remRsrp, cellCb->tgtRsrp);
      
      rsrpPwr = cellCb->rsysTpmRsrpMin; 
   }
   else
   {
      rsrpDiff = cellCb->tgtRsrp - remRsrp; 

      RLOG3(L_INFO, "RSYS SON TPM rsrpDiff %d, Target Rsrp %d" 
            " Rem Rsrp %d \n",
            rsrpDiff, cellCb->tgtRsrp, remRsrp);

      if (rsrpDiff <= NL_MAX_RSRP_DIFF)
      {
         rsrpPwr = rsysTpmTable[cellCb->attnConstIdx][rsrpDiff-1] +
            strngstNghCell->servCellInfo.RSTxPower - NL_NGH_REF_POWER; 

         NL_TPM_RSRP_CHK_RANGE(cellCb, rsrpPwr);
      }
      else /* No strong cell nearby. Use the Max value */
      {
         rsrpPwr = cellCb->rsysTpmRsrpMax; 
      }
   }
   RETVALUE(rsrpPwr);
}

/**
 * @brief Utility function to find out the strongest Neighbour cell
 *
 * @details
 *
 *     Function : nlUtlFindStrongestNghCell
 *
 *     This function loops through the Neighbour list and returns
 *     the strongest neighbour cell based on RSRP power.
 *
 *  @param[in]  cellCb          : cell control block
 *  @param[out] strngstNghCell  : Strongest Neighbor cell
 *  @return     Void
 *
 **/
#ifdef ANSI
PUBLIC Void nlUtlFindStrongestNghCell
(
NlCellCb          *cellCb,    /* cell control block */
NlNghServCellCb   **strngstNghCell 
)
#else
PUBLIC Void nlUtlFindStrongestNghCell (cellCb, strngstNghCell)
(
NlCellCb          *cellCb;   
NlNghServCellCb   **strngstNghCell; 
)
#endif
{
   NlNeighCellCb      *nghEnbCb;
   CmLListCp          *servCellList;
   CmLList            *servLink;
   NlNghServCellCb    *nghCellCb; 
   PTR                 prevEntry = NULLP;
   S16                 nghRsrp   = NL_MIN_RSRP; 
   
   TRC3(nlUtlFindStrongestNghCell);
   
   /* Find out the strongest Neighbour */
   while(ROK == cmHashListGetNext(&(cellCb->neighEnbCb.nghEnbListCp),
            prevEntry, (PTR *) &nghEnbCb))
   {     
      servCellList = &(nghEnbCb->servCellLst);
      CM_LLIST_FIRST_NODE(servCellList, servLink);
      while(NULLP != servLink)
      {
         nghCellCb = (NlNghServCellCb *)servLink->node;

         if ((nghCellCb->servCellInfo.dlEarfcn == cellCb->cellInfo.dlEarfcn) &&
             (nghCellCb->servCellInfo.rsrp > nghRsrp)
            )
         {
            nghRsrp = nghCellCb->servCellInfo.rsrp;
            *strngstNghCell = nghCellCb;
         }
         CM_LLIST_NEXT_NODE(servCellList, servLink);
      }
      prevEntry = (PTR)nghEnbCb;
   }
   RETVOID;
}

/********************************************************************30**

           End of file:     bk_pt_son.c@@/main/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:56 2016

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

