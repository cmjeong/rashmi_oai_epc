

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by CKW interface of XTA LTE RLC
 
    File:   kwac_ckw.h
 
    Sid:      kwac_ckw.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:22 2014
 
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

#ifndef __KWAC_CKW_H__
#define __KWAC_CKW_H__

#define KWAC_CKW_DFLTRGN  kwCb.init.region 
#define KWAC_CKW_DFLTPOOL kwCb.init.pool

#define CKW_DAT_GETBUF(_buf, _bufSize) \
{\
   U8 str[1000];\
   if (SGetMsg(KWAC_CKW_DFLTRGN, KWAC_CKW_DFLTPOOL, &_buf) != ROK)\
      RETVALUE(RFAILED);\
   SAddPstMsgMult((U8 *)str, _bufSize, _buf);\
}

#define KWAC_UTL_CKW_CQ_ISEMPTY(q) (kwAcUtlCkwCircQAddOne(q->rear) == q->front)?TRUE:FALSE

#endif /* __KWAC_CKW_H__ */


/**********************************************************************
         End of file:     kwac_ckw.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:22 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     gk            1. Initial Release.
/main/2      ---     gk            1. LTE RLC Release 2.1.
*********************************************************************91*/

