
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_csfb_geran.h

     Sid:      /main/

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_UMM_CSFB_GERAN_H__
#define __WR_UMM_CSFB_GERAN_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/*Transaction Choice*/
#define WR_CSFB_GERAN_REDIR    0x00
#define WR_CSFB_GERAN_CCO      0x01
#define WR_CSFB_GERAN_MEAS     0x10
#define WR_CSFB_GERAN_CCO_MEAS 0x11
/*trans IDs for DAT_CFM*/
#define WR_UMM_CSFB_GERAN_CCO_TRANSID          1


#if 0
#define WR_CSFB_GERAN_CONV_T304VAL_TO_ENUM(_val,_enum){\
   /*Need to sutract WR_TMR_T304_GERAN_DELAY from _val as this is the   
    * procedure delay*/                                \
   switch(_val)                                        \
   {                                                   \
      case 100:                                        \
         {                                             \
            _enum = 0;                                 \
            break;                                     \
         }                                             \
      case 200:                                        \
         {                                             \
            _enum = 1;                                 \
            break;                                     \
         }                                             \
      case 500:                                        \
         {                                             \
            _enum = 2;                                 \
            break;                                     \
         }                                             \
      case 1000:                                       \
         {                                             \
            _enum = 3;                                 \
            break;                                     \
         }                                             \
      case 2000:                                       \
         {                                             \
            _enum = 4;                                 \
            break;                                     \
         }                                             \
      case 4000:                                       \
         {                                             \
            _enum = 5;                                 \
            break;                                     \
         }                                             \
      case 8000:                                       \
         {                                             \
            _enum = 6;                                 \
            break;                                     \
         }                                             \
      default: _enum = 3;                              \
               break;                                  \
   }                                                   \
}                                                      
#endif
                                                       
#ifdef __cplusplus                                     
}                                                      
#endif /* __cplusplus */

#endif /*End of _WR_UMM_CSFB_GERAN_H__*/
/********************************************************************30**

           End of file:   /main/ 

*********************************************************************31*/

