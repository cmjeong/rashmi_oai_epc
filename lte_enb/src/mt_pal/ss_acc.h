/********************************************************************20**

     Name:

     Type:     C File.

     Desc:

     File:     ss_acc.h

     Sid:      ss_acc.h@@/main/1 - Mon Aug 29 22:31:39 2011

     Prg:

************************************************************************/
/* header/extern include files (.h) */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "ss_dep.h"        /* implementation-specific */
#include "ss_err.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_dep.h"       /* tasking */
#include "ss_msg.h"       /* tasking */
#include "ss_mem.h"       /* tasking */
#include "ss_gen.h"       /* tasking */
#include <assert.h>       /* tasking */
/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */


/* local defines */
#define PERMENT      6
#define PERMENT1     5
#define PERMENT2     6
#define MAXTSTCNT    0
#define TSTTIMES     10         /* number of test for certain function */
#define BSIZE        100
#define MAXMSGLEN    256        /* maximum message length */
#define MAXSMEMLEN   0x20       /* maximum static memory length */
#define TMR_TICKS    10
#define NMBTMRTSKS   2
#define TSKCNT       1000


#define SMSTASID     0
#define SMSTASPOOL   1
#define SMSTADPOOL   2
#define SMSTADQ      3
#define SMSTAENT     4
#define SMSTSLOOP    5
#define SMSTSDQ      6
#define SMSTSENT     7
#define NMBPRIOR     1
#define REFAILED     0
#define NMBTSKS      4

/* local typedefs */
#define MAX_TESTS   50
#define PASS        0
#define MAX_STR     64
#define MAX_STR_DIS 16
#define DEFAULT_TEST_INIT(tc, id, name, func, prefunc, pstFunc)   do {\
    (tc)->tcId = (U64) (id);                           \
    strncpy(&((tc)->tcName[0]), name, MAX_STR_DIS);    \
    (tc)->preReq = prefunc;                            \
    (tc)->testFunc = func;                             \
    (tc)->postReq = pstFunc;                           \
    (tc)->result = FAIL;                               \
} while (0)
#define RB_ACC_MAX_MSG    1000
#define MAX_QUEUE_LENGTH  50


/********************************************************************30**

         End of file:     ss_acc.h@@/main/1 - Mon Aug 29 22:31:39 2011

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
