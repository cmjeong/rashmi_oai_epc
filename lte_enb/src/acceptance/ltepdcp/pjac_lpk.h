

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by LPK interface of XTA LTE PDCP
 
    File:   pjac_lpk.h
 
    Sid:      pjac_lpk.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:01 2015
 
    Prg:    Adarsh 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*
*/

#ifndef __PJAC_LPK_H__
#define __PJAC_LPK_H__

#ifdef KW_PDCP
#define PJAC_UEID                1
/* kw005.201 added support for L2 Measurement */
#define PJAC_QCI                 2
/* Venki - KW_PDCP */
/* ##################################### */
#else
#define PJAC_UEID                1
/* kw005.201 added support for L2 Measurement */
#define PJAC_QCI                 2

#endif /* KW_PDCP */
#endif /* __PJAC_LPK_H__ */


/**********************************************************************
         End of file:     pjac_lpk.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:01 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vb         1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/
