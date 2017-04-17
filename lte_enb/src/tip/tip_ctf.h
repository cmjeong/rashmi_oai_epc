
/**********************************************************************
     Name:     LTE-PHY layer 
  
     Type:     C include file 
  
     Desc:     Defines required by the LTE PHY-RRC control (CTF) interface.

     File:     ctf.h 

     Sid:      ctf.h@@/main/3 - Thu Feb 16 19:38:59 2012

     Prg:      vkulkarni

**********************************************************************/
#ifndef __TIP_CTF_H__
#define __TIP_CTF_H__

EXTERN S16 tipSendCtfCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfCfgReqInfo  *     cfgReqInfo
));
/* Configuration Request from User to PHY for 
 * cell or dedicated configuration.
*/
EXTERN S16 tipProcCtfCfgReq ARGS((
   CtfCfgReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
 
EXTERN S16 tipSendCtfCfgRsp ARGS((
Pst* pst,
SuId suId,
CtfCfgTransId transId,
U8 status
));

EXTERN S16 tipProcCtfCfgCfm ARGS((
CtfCfgCfm func,
Pst *pst,
Buffer *mBuf
));


EXTERN S16 tipStartCell(U16 cellId);

#endif /* __TIP_CTF_H__ */


/**********************************************************************
  
         End of file:     ctf.h@@/main/3 - Thu Feb 16 19:38:59 2012
  
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************

**********************************************************************/


/**********************************************************************
  
        Revision history:
  
**********************************************************************/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   vkulkarni         1. Initial release.
/main/1     ctf_h_001.main_1   sgm   1. Wireshark compilation fix. 
/main/3      ---      ctf_h_001.main_2   ragrawal  1. Added new error code.
*********************************************************************91*/
