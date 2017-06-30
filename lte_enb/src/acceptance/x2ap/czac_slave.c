

/********************************************************************20**

     Name:    X2AP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    czac_slave.c

     Sid:      czac_slave.c@@/main/tenb_main_ccb/1 - Wed Jul 22 20:08:33 2015

     Prg:     rp 

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "czt.h"           /* CZT defines */
#include "lcz.h"           /* layer management defines for X2AP */
#include "sct.h"           /* SB (SCTP) layer */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h"

#include "cz.h"            /* defines and macros for X2AP */
#include "czac_acc.h"      /* defines for X2AP acceptance tests */

#include <stdlib.h>

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czt.x"           /* CZT types */
#include "lcz.x"           /* layer management typedefs for X2AP */
#include "cm_xta.x"

#ifdef HI
#include "lhi.x"
#include "czac_lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "czac_lsb.x"
#endif    /* SB */

#include "cz.x"            /* typedefs for CZCP */
#include "czac_acc.x"        /* typedefs for CZCP acceptance tests */
#include "czac_lcz.x"
#include "czac_czt.x"

#ifdef DM
#include "czac_sct.x"
#endif /*DM*/


/*
*
*       Fun:   cmXtaAppTst
*
*       Desc:  This functions is called from the SSI.
*              It rczisters the various layers with 
*              SSI.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  czac_slave.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppTst
(
Void
)
#else
PUBLIC S16 cmXtaAppTst()
#endif
{
   TRC2(cmXtaAppTst)

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTst */

/*
*
*       Fun:   cmXtaAppSlaveInit
*
*       Desc:  Initialization function for acceptance test
*
*       Ret:   Void
*
*       Notes: None
*              
*       File:  czac_slave.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveInit
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveInit(Void)
#endif
{
   TRC2(cmXtaAppSlaveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Initializing the slave\n"));
#ifdef SS_MULTIPLE_PROCS
   czCbPtr = &czCbLst[0];
#else
   czActvInit( ENTCZ, 0, 0, 0 );
#endif

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveInit(): Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveInit */

/*
*
*       Fun:   cmXtaAppSlaveDeInit
*
*       Desc:  This functions is called from the SSI.
*              It rczisters the various layers with 
*              SSI.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  czac_slave.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveDeInit()
#endif
{
   TRC2(cmXtaAppSlaveDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveDeInit(): Shutting down the Test Architecture\n"));

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppSlaveDeInit(): Test Architecture Shutdown Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveDeInit */

/*
*
*      Fun  : cmXtaAppSlaveParseCmdLine
*
*      Desc : This function parses the command line to set
*             the test usage options.
*
*      Ret  : Void
*
*      Notes: None
*
*      File : czac_slave.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppSlaveParseCmdLine
(
Void
)
#else
PUBLIC S16 cmXtaAppSlaveParseCmdLine()
#endif
{
   TRC2(cmXtaAppSlaveParseCmdLine)

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppSlaveParseCmdLine */

/*
*
*      Fun  : cmXtaAppSlaveUsage
*
*      Desc : This function displays an acceptance test usage message.
*
*      Ret  : Void
*
*      Notes: None.
*
*      File : czac_slave.c
*
*/
#ifdef ANSI
PUBLIC Void cmXtaAppSlaveUsage
(
Void
)
#else
PUBLIC Void cmXtaAppSlaveUsage()
#endif
{
   TRC2(cmXtaAppSlaveUsage);

   RETVOID;
} /* cmXtaAppSlaveUsage */
/*
*
*       Fun:   cmXtaAppDirectiveInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_slave.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppDirectiveInit
(
Void
)
#else
PUBLIC S16 cmXtaAppDirectiveInit()
#endif
{
   TRC2(cmXtaAppDirectiveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppDirectiveInit(): Init\n"));
   RETVALUE(ROK);
}/* cmXtaAppDirectiveInit */

/********************************************************************30**

         End of file:     czac_slave.c@@/main/tenb_main_ccb/1 - Wed Jul 22 20:08:33 2015

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
/main/1      ---      rp          1. Created for Initial release 1.1
/main/2      ---      pt          1. LTE-X2AP 3.1 release.
*********************************************************************91*/
