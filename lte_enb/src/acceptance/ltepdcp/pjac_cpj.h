

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by CPJ interface of XTA LTE PDCP
 
    File:   pjac_cpj.h
 
    Sid:      pjac_cpj.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:44 2015
 
    Prg:    adarsh 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000371       LTE PDCP
*
*/

#ifndef __PJAC_CPJ_H__
#define __PJAC_CPJ_H__

#define PJAC_CPJ_DFLTRGN  0
#define PJAC_CPJ_DFLTPOOL 0

#define CPJ_DAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(PJAC_CPJ_DFLTRGN, PJAC_CPJ_DFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}

#define PJAC_UTL_CPJ_CQ_ISEMPTY(q) (pjAcUtlCpjCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#endif /* __PJAC_CPJ_H__ */


/**********************************************************************
         End of file:     pjac_cpj.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:44 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vb       1. LTE PDCP Release 2.1.
*********************************************************************91*/
