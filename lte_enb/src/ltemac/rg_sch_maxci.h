


/**********************************************************************
 
    Name:   LTE MAC MAX C/I scheduler
 
    Type:   C include file
 
    Desc:   Defines required by MAX C/I scheduler
 
    File:   rg_sch_maxci.h
 
    Sid:      rg_sch_maxci.h@@/main/2 - Sat Jul 30 02:22:07 2011
 
    Prg:    apany
 
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


#ifndef __RGSCHMAXCIH__
#define __RGSCHMAXCIH__

#define RG_SCH_MAXCIUL_NUM_CQI_LVLS 16 /* Num of queues is one less than this */
#define RG_SCH_MAXCIDL_NUM_CQI_LVLS 16 /* Num of queues is one less than this */

/* SR Grant */
#define RG_SCH_MAXCI_SR_BYTES 4
/* maximium priority levels,it varies from 0 to 15 */
#define RG_SCH_MAXCI_MIN_CQI_VAL    0
#define RG_SCH_MAXCI_MAX_CQI_VAL    15
#define RG_SCH_MAXCI_MAX_CWS_PERUE  2
/* ERROR CODES */
#define RGSCHERR_MAXCI_MEMERR          1   /* MEMORY ERROR */

/* MACROS */
#define RG_SCH_MAXCIUL_GET_UE(_ue, _cell) (RgSchMaxciUlUe*)((RgSchCmnUe *)((_ue->cellInfo[_ue->cellIdToCellIdxMap\
                           [RG_SCH_CELLINDEX(_cell)]])->sch))->ul.schSpfc
#define RG_SCH_MAXCIUL_GET_CELL(cell) (RgSchMaxciUlCellCb*)((RgSchCmnCell*)((cell)->sc.sch))->ul.schSpfc


#define RG_SCH_MAXCIDL_GET_CELL(_cell) (RgSchMaxciDlCell *)((RgSchCmnCell*)((_cell)->sc.sch))->dl.schSpfc

#define RG_SCH_MAXCIDL_GET_UE(_ue, _cell) (RgSchMaxciDlUe *)((RgSchCmnUe *)((_ue->cellInfo[_ue->cellIdToCellIdxMap\
                           [RG_SCH_CELLINDEX(_cell)]])->sch))->dl.schSpfc
#define RG_SCH_MAXCIDL_GET_HQP(hqP) (RgSchMaxciDlHqProc *)((RgSchCmnDlHqProc *)((hqP)->sch))->schSpfc

#define RG_SCH_MAXCIDL_GET_LC(_ue,_svc,_cell) RG_SCH_CMN_GET_LC_SCH_SPFC(_ue,_svc,_cell)
#define RG_SCH_MAXCIDL_IS_SRB(_lc) (_lc->lcId  == 1 || _lc->lcId == 2)
#define RG_SCH_MAXCIDL_INIT_LNK(_lstLnk, _node)\
{\
      (_lstLnk)->node = (PTR)_node;\
      (_lstLnk)->prev = NULLP;\
      (_lstLnk)->next = NULLP;\
}

#endif /* __RGSCHMAXCIH__ */


/**********************************************************************
         End of file:     rg_sch_maxci.h@@/main/2 - Sat Jul 30 02:22:07 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      apany  1. LTE MAC 2.1 release
             rg001.201 sm 1. Removed extra comments. 
           rg007.201   ap  1. Added support for MIMO
           rg008.201   sd  1.Removed dependency on MIMO compile-time flag
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
$SID$        ---       rt    1. LTE MAC 4.1 Release.                           
*********************************************************************91*/
