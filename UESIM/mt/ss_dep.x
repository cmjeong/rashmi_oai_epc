

/********************************************************************20**
 
     Name:     System Services -- implementation specific definitions
 
     Type:     C include file
 
     Desc:     This file conditionally includes implementation
               specific files.
 
     File:     ss_dep.x
 
     Sid:      ss_dep.x@@/main/2 - Mon Apr  5 18:01:14 2010
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSDEPX__
#define __SSDEPX__

#ifdef __cplusplus
extern "C" {
#endif


#ifdef SS_MT
#include "cm5.x"
#include "mt_ss.x"
#else /* not SS_MT */

#ifdef SS_PS
#include "cm5.x"
#include "ps.x"
#include "ps_ss.x"
#else /* not SS_PS */

#ifdef SS_VW
#include "vw_ss.x"
#else /* not SS_VW */

#ifdef NS
#include "ns_task.x"
#include "ns_timer.x"
#include "ns_gen.x"
#else /* not NS */

#ifdef SS_SK
#include "sk_ss.x"
#else /* not SS_SK */

#error "Specify an implementation"

#endif /* SS_SK */
#endif /* NS */
#endif /* SS_VW */
#endif /* SS_PS */
#endif /* SS_MT */


#ifdef __cplusplus
}
#endif

#endif  /*  __SSDEPX__  */



/********************************************************************30**

         End of file:     ss_dep.x@@/main/2 - Mon Apr  5 18:01:14 2010

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

1.2          ---      kp   1. Added SS_SK includes

1.3          ---      kp   1. Added SS_MT and SS_PS includes

/main/4      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
