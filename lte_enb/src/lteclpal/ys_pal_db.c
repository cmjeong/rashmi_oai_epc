
/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for tables lookup  
     File:     ys_db.c
  
     Sid:      yw_db.c@@/main/1 - Thu Dec  2 02:27:25 2010
  
     Prg:      pk
  
**********************************************************************/

/** @file ys_db.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files -- defines (.h) */

/* header/extern include files (.x) */
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"

#ifdef YS_MSPD
#else
#include "ys_pal.h"            /* defines and macros for CL */
#endif /* YS_MSPD */
#include "ys_pal_err.h"        /* YS error defines */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"

#ifdef YS_MSPD
#else
#include "ys_pal.x"            /* typedefs for CL */
#endif /* YS_MSPD */




PUBLIC Bool               ysPrachPresDb[YS_NUM_PRACH_PRES_ARR];
PUBLIC YsSrCfgInfo        ysSrCfgDb[YS_NUM_SR_CFG];
PUBLIC YsSrsCfgInfo       ysSrsCfgDb[YS_NUM_SRS_CFG];
PUBLIC YsCqiPmiCfgIdxInfo ysCqiPmiCfgDb[YS_NUM_CQI_CFG];

/********************************************************************30**
  
         End of file:     yw_db.c@@/main/1 - Thu Dec  2 02:27:25 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/1      ---     sgm                   1. eNodeB 1.2 release
/main/1      ys004.102    vr               1. MSPD Merge for PHY ver 1.7 
*********************************************************************91*/
