

/********************************************************************20**
 
     Name:     System Services -- Task Management
 
     Type:     C include file
 
     Desc:     Various macro definitions required for the task mgmt.
 
     File:     ss_task.h
 
     Sid:      ss_task.h@@/main/2 - Mon Apr  5 18:01:21 2010
 
     Prg:      kp
  
*********************************************************************21*/


#ifndef __SSTASKH__
#define __SSTASKH__

#ifdef __cplusplus
extern "C" {
#endif


/* task types */
#define SS_TSK_UND              0               /* undefined */
#define SS_TSK_NORMAL           1               /* normal task */
#define SS_TSK_PERMANENT        2               /* permanent task */


/* task priorities (these are system task priorities--0 to 31) */
#define SS_NORM_TSK_PRI         13              /* for normal tasks */
#define SS_PERM_TSK_PRI         21              /* for permanent tasks */


#define SS_LOWEST_STSK_PRIOR    31              /* lowest sys task priority */


#ifdef __cplusplus
}
#endif

#endif /* __SSTASKH__ */


/********************************************************************30**
  
         End of file:     ss_task.h@@/main/2 - Mon Apr  5 18:01:21 2010
  
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
