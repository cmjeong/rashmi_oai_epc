/********************************************************************20**

     Name:

     Type:     C File.

     Desc:

     File:     mt_4gmx.h

     Sid:      mt_4gmx.h@@/main/1 - Mon Aug 29 22:31:39 2011

     Prg:

************************************************************************/

#ifndef __MT4GMX_H__
#define __MT4GMX_H__

#ifdef __cplusplus
extern "C" {
#endif

/* SSI Header/Extern include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "cm_gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "ss_err.h"

/* mindpeed specific header files */
#include "osal.h"
#include "icpu.h"
#include "bsp.h"
#include "hostiface.h"
#include "spusched.h"
#include "msgroute.h"
#include "settings.h"
#include "maciface.h"
#include "phyiface.h"
#include "transport.h"
#include "svsr.h"
#include "auxiface.h"
#include "console.h"
#include "c4ktrace.h"
#include "rrciface.h"
#include "rlciface.h"
#include "version.h"
#include "diags.h"
#include "LtePhyL2Api.h"

#define CL_REGION DFLT_REGION
#define CL_POOL DFLT_POOL

#ifdef __cplusplus
}
#endif

#endif


/********************************************************************30**

         End of file:     mt_4gmx.h@@/main/1 - Mon Aug 29 22:31:39 2011

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

   ver        pat        init                  description
---------  ---------  ----------  -------------------------------------
/main/1      --------     ------    1. Initial release
*********************************************************************91*/
