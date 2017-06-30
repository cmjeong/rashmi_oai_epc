

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by CKW interface of XTA LTE RLC
 
    File:   kwac_lpj.h
 
    Sid:      kwac_lpj.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:34 2014
 
    Prg:    gk 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*
*/

#ifndef __KWAC_LPJ_H__
#define __KWAC_LPJ_H__

#ifdef KW_PDCP
#define KWAC_UEID                1
/* kw005.201 added support for L2 Measurement */
#define KWAC_QCI                 2

#endif /* KW_PDCP */
#endif /* __KWAC_LPJ_H__ */


/**********************************************************************
         End of file:     kwac_lpj.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:34 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   gk         1. LTERLC Release 2.1.
/main/2     kw005.201 ap      1. Added support for L2 Measurement.
*********************************************************************91*/

