

/**********************************************************************

     Name:     LTE-CL Layer 
  
     Type:     C souce file
  
     Desc:     SCL for Trillium to Silicon Rx Mapping. 

     File:     ys_rxmap.c 

     Sid:      ys_dft.c@@/main/1 - Thu Dec  2 02:27:13 2010

     Prg:      mraj

**********************************************************************/

#ifndef __YS_DFT_PARAMS_H__
#define __YS_DFT_PARAMS_H__

#define YS_REPEAT_CYCLE      1
#define YS_PERSIST_ENABLE    1

#define ACKNACKREPT          0

#define NOMPDSCHRSEPROFF     0

#define YS_CODING_DESC       TURBOCDR
#define YS_BLK_CODE_CAT      1
#define YS_CRC_SCRAMBLING    0
#define YS_SINGLE_MAPPING    1
#define YS_TX_PWR_CNTRL      0
#define YS_HALF_ITERATIONS  16

/* PUCCH Definitions */
#define YS_PUCCH_CRC_LEN     0
#define YS_PUCCH_COD_DES     0
#define YS_PUCCH_BLK_CAT     0
#define YS_PUCCH_MCS_TYP     0

#endif /* __YS_DFT_PARAMS_H__ */

/********************************************************************30**
  
         End of file:     ys_dft.c@@/main/1 - Thu Dec  2 02:27:13 2010
  
*********************************************************************31*/

/********************************************************************40**
  
        Notes:
 
**********************************************************************/
 
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sgm                   1. eNodeB 1.2 release
*********************************************************************91*/
