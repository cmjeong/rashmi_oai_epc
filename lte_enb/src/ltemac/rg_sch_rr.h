


/**********************************************************************
 
    Name:   LTE MAC Round Robin scheduler
 
    Type:   C include file
 
    Desc:   Defines required by Round Robin scheduler
 
    File:   rg_sch_rr.h
 
    Sid:      rg_sch_rr.h@@/main/2 - Sat Jul 30 02:22:09 2011
 
    Prg:    rr
 
**********************************************************************/

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000372       LTE-MAC
*
*/


#ifndef __RGSCHRRH__
#define __RGSCHRRH__

#define RG_RR_MIN_DCCH_LCID 1 /*!< Minimum value for DDCH LCID */
#define RG_RR_MAX_DCCH_LCID 2 /*!< Maximum value for DDCH LCID */
#define RG_RR_SR_GRNT       3 /*!< SR grant in bytes */



#define RG_SCH_RR_ADD_TO_TX_LIST(ue,rrCell,rrUe) \
{\
   if (rrUe->ueTxLnk.node == NULLP)\
   {\
      if(ue->csgMmbrSta == TRUE)\
      {\
         rgSCHRrCListAdd2Tail(&(rrCell->prioUeTxLst), &(rrUe->ueTxLnk));\
      }\
      else\
      {\
         rgSCHRrCListAdd2Tail(&(rrCell->nonPrioUeTxLst), &(rrUe->ueTxLnk));\
      }\
      rrUe->ueTxLnk.node = (PTR)ue;\
   }\
}

#define RG_SCH_RR_DEL_UE_FRM_TX_LIST(ue,rrCell,rrUe) \
{\
   if (rrUe->ueTxLnk.node != NULLP)\
   {\
      if(ue->csgMmbrSta == TRUE)\
      {\
         rgSCHRrCListDelFrm(&(rrCell->prioUeTxLst), &(rrUe->ueTxLnk));\
      }\
      else\
      {\
         rgSCHRrCListDelFrm(&(rrCell->nonPrioUeTxLst), &(rrUe->ueTxLnk));\
      }\
      rrUe->ueTxLnk.node = NULLP;\
   }\
}

#define RG_SCH_RR_DEL_UE_FRM_LIST_AND_ADD_TO_TAIL(ue,rrCell,rrUe) \
{\
   if(ue->csgMmbrSta == TRUE)\
   {\
      rgSCHRrCListDelFrm(&(rrCell->prioUeTxLst), &(rrUe->ueTxLnk));\
      rgSCHRrCListAdd2Tail(&(rrCell->prioUeTxLst), &(rrUe->ueTxLnk));\
   }\
   else\
   {\
      rgSCHRrCListDelFrm(&(rrCell->nonPrioUeTxLst), &(rrUe->ueTxLnk));\
      rgSCHRrCListAdd2Tail(&(rrCell->nonPrioUeTxLst), &(rrUe->ueTxLnk));\
   }\
}

#define RG_SCH_RR_UPD_UE_IN_PRIO_NONPRIO_TX_LIST(oldCSGMbrSta, newCSGMbrSta, rrCell, rrUe) \
{\
   if ((oldCSGMbrSta != newCSGMbrSta) && (rrUe->ueTxLnk.node != NULLP))\
   {\
      if (oldCSGMbrSta == TRUE)\
      {\
         rgSCHRrCListDelFrm(&(rrCell->prioUeTxLst), &(rrUe->ueTxLnk));\
         rgSCHRrCListAdd2Tail(&(rrCell->nonPrioUeTxLst), &(rrUe->ueTxLnk));\
      }\
      else\
      {\
         rgSCHRrCListDelFrm(&(rrCell->nonPrioUeTxLst), &(rrUe->ueTxLnk));\
         rgSCHRrCListAdd2Tail(&(rrCell->prioUeTxLst), &(rrUe->ueTxLnk));\
      }\
      rrUe->ueTxLnk.node = (PTR)ue;\
   }\
}
#endif /* __RGSCHRRH__ */


/**********************************************************************
         End of file:     rg_sch_rr.h@@/main/2 - Sat Jul 30 02:22:09 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rr  1. LTE MAC 2.1 release
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
$SID$        ---       rt    1. LTE MAC 4.1 Release.                           
*********************************************************************91*/
