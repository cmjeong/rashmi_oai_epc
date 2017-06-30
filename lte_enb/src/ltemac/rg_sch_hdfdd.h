

/**********************************************************************
     Name:    LTE MAC HD-FDD 

     Type:    C header file

     Desc:    Defines required by HD-FDD 

     File:    rg_sch_hdfdd.h

     Sid:      rg_sch_hdfdd.h@@/main/1 - Sat Jul 30 02:22:05 2011

     Prg:      rbabu 

*********************************************************************21*/


#ifndef __RGSCHHDFDDH__
#define __RGSCHHDFDDH__ 
#ifdef __cplusplus
extern "C" {
#endif

/* Half Duplex Specific defines */
/* Maximum Number of subframes information managed */
#define RG_SCH_HDFDD_MAXSUB_INFO   20 
 
/* Subframe States */
#define RG_SCH_SF_DFLT_STATE    0x00
#define RG_SCH_SF_DLDATA_STATE  0x01
#define RG_SCH_SF_DLCNTRL_STATE 0x02
#define RG_SCH_SF_ULDATA_CNTRL_STATE 0x04
 
/* To get the BCH is present or not at subframe */
#define RG_SCH_BCCH_TRUE_FALSE( _time, _bchTrue)\
{\
  _bchTrue = FALSE;\
  /* Call the API is provided by SI module */ \
}

#ifdef __cplusplus
}
#endif
#endif /* __RGSCHCMNH__ */

/********************************************************************30**

         End of file:     rg_sch_hdfdd.h@@/main/1 - Sat Jul 30 02:22:05 2011

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
/main/1      ---        gvj  1. Created for LTE MAC Rel 3.1
$SID$        ---       rt    1. LTE MAC 4.1 Release.                           
*********************************************************************91*/
