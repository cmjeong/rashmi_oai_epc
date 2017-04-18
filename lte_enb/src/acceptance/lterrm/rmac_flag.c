

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_flag.c

     Sid:      rmac_flag.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:25 2013

     Prg:      vprabhu 

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
#include "cm_dns.h"         /* common DNS libraru defines */


#include "cm_xta.h" 
#include "cm_pasn.h"
#include "rm.h"
#include "rmac_acc.h"


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
#include "cm_dns.x"         /* common DNS libraru defines */

#include "cm_xta.x" 



Bool cmXtaFlag[WRAC_MAX_FLAGS] = 
{
   FALSE,
   TRUE,

#ifdef DEBUGP
   TRUE,
#else
   FALSE
#endif

};

Txt  cmXtaFlagStr[WRAC_MAX_FLAGS][50] =
{
   "Unknown Ifdef",
   "Unknown Ifndef",
   "SZ_DBG"
};



