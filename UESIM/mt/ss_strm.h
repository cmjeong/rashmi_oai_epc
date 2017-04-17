

/********************************************************************20**
 
     Name:     System Services -- STREAMS
 
     Type:     C include file
 
     Desc:     Various macro definitions required for STREAMS.
 
     File:     ss_strm.h
 
     Sid:      ss_strm.h@@/main/2 - Mon Apr  5 18:01:20 2010
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSSTRMH__
#define __SSSTRMH__

#ifdef __cplusplus
extern "C" {
#endif



/* STREAMS message types */
#define SS_M_DATA       0
#define SS_M_PROTO      1
#define SS_M_BREAK      2
#define SS_M_CTL        3
#define SS_M_DELAY      4
#define SS_M_IOCTL      5
#define SS_M_PASSFP     6
#define SS_M_RSE        7
#define SS_M_SETOPTS    8
#define SS_M_SIG        9


/* message initialization macro */
#define SS_STRM_INITB(mp, dp, dat, size, frtn) \
   (mp)->b_next = NULLP; \
   (mp)->b_prev = NULLP; \
   (mp)->b_cont = NULLP; \
   (mp)->b_rptr = (dat); \
   (mp)->b_wptr = (dat); \
   (mp)->b_datap = (dp); \
   (dp)->db_frtnp = (frtn); \
   (dp)->db_base = (dat); \
   (dp)->db_lim = (dat) == NULLP ? (dat) : ((dat) + (size)); \
   (dp)->db_ref = 1; \
   (dp)->db_type = SS_M_DATA;


#ifdef __cplusplus
}
#endif

#endif  /*  __SSSTRMH__  */


  
/********************************************************************30**

         End of file:     ss_strm.h@@/main/2 - Mon Apr  5 18:01:20 2010

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
1.1          ---      kp   1. initial release

1.2          ---      kp   1. C++ compilable, cosmetic changes

/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
