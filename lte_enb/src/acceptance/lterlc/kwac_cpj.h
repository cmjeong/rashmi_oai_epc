

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by CPJ interface of XTA LTE RLC
 
    File:   kwac_cpj.h
 
    Sid:      kwac_cpj.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:24 2014
 
    Prg:    gk 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000371       LTE RLC
*
*/

#ifndef __KWAC_CPJ_H__
#define __KWAC_CPJ_H__

#ifdef KW_PDCP
#define KWAC_CPJ_DFLTRGN  kwCb.init.region 
#define KWAC_CPJ_DFLTPOOL kwCb.init.pool

#define CPJ_DAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(KWAC_CPJ_DFLTRGN, KWAC_CPJ_DFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}

#define KWAC_UTL_CPJ_CQ_ISEMPTY(q) (kwAcUtlCpjCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#endif /* KW_PDCP */
#endif /* __KWAC_CPJ_H__ */


/**********************************************************************
         End of file:     kwac_cpj.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:24 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   gk         1. LTERLC Release 2.1.
*********************************************************************91*/

