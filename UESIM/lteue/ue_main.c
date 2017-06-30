#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#ifdef SS_LINUX
#include <sys/time.h>
#endif
#include <errno.h>                 



/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "cm5.h"           /* common timers */

#include "jz_ss.h"         /* MTSS specific */
#include "jz_err.h"        /* MTSS error defines */

#include "jz_task.h"       /* tasking */
#include "jz_msg.h"        /* messaging */
#include "jz_mem.h"        /* memory management interface */
#include "jz_gen.h"        /* general */

#include "cm_mem.h"        /* common memory manager */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timers */

#include "jz_ss.x"         /* MTSS specific */

#include "jz_task.x"       /* tasking */
#include "jz_timer.x"      /* timers */
#include "jz_strm.x"       /* STREAMS */
#include "jz_msg.x"        /* messaging */
#include "jz_mem.x"        /* memory management interface */
#include "jz_gen.x"        /* general */

#include "cm_mem.x"        /* common memory manager */

/* cvmx header files */
#include "cvmx-config.h"
#include "cvmx-pow.h"
#include "cvmx-tim.h"
#include "cvmx-bootmem.h"
#include "cvmx-fpa.h"
#include "cvmx-helper-fpa.h"
#include "cvmx-coremask.h"
#include "cvmx-pko.h"

#include "ue_app.h"
#include "ue_err.h"

EXTERN Void ueAppPktReceiver ARGS((Void *arg));
EXTERN S16 simpleExecInit ARGS ((Void));


/************************************************************************
 
     Name:     LTE UE Simulator
  
     Type:     C source file
  
     Desc:     C source code for Utilities
  
     File:     ue_main.c
  
     Sid:      ue_main.c@@/main/1 - Sun Mar 28 22:59:24 2010
  
     Prg:      vp
  
**********************************************************************/


/*
*
*       Fun:   main
*
*       Desc:  This function is the entry point for the final binary. It
*              calls SInit() in the common code. It can be replaced by a
*              user function if required (SInit() must still be called).
*
*       Ret:   none on success
*              exit on failure
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC int main
(
int argc,                       /* argument count */
char **argv                     /* argument vector */
)
#else
PUBLIC int main(argc, argv)
int argc;                       /* argument count */
char **argv;                    /* argument vector */
#endif
{
   cvmx_wqe_t *work;
   S16        ret;
   cvmx_ipd_ctl_status_t ipd_reg;
   cvmx_pip_port_tag_cfg_t tag_config;
   U16 coreId;
   U16 intercept_port;
   

   TRC0(main);

   msArgc = argc;
   msArgv = argv;

   intercept_port = UE_APP_BASE_PORT + UE_APP_MAC_PORT_ID; 

   if (simpleExecInit() != ROK)
   {
      SExit();
   }

   do
   {
      ipd_reg.u64 = cvmx_read_csr(CVMX_IPD_CTL_STATUS);
   } while (!ipd_reg.s.ipd_en);

   cvmx_cmd_queue_initialize(0, 0, -1, 0);
  
   /* Change the group for only the port we're interested in */
   tag_config.u64 = cvmx_read_csr(CVMX_PIP_PRT_TAGX(intercept_port));
   tag_config.s.grp = UE_PCAP_PORT_GROUP;
   cvmx_write_csr(CVMX_PIP_PRT_TAGX(intercept_port), tag_config.u64);

 
   /* Setup scratch registers used to prefetch output queue buffers for packet output */
   cvmx_pko_initialize_local();

   ret = ssInit();
   if (ret != ROK)
   {
      /* ue007.101: Compilation error fix in cavium */
#ifdef DEBUGP
      SSDEBUG(("Failed to do SInit"));
#endif
      RETVALUE(ret);
   }

   coreId = cvmx_get_core_num();

   cvmx_pow_set_group_mask(coreId, 
    ((1 << coreId) | (1 << UE_PCAP_PORT_GROUP)));

   /* 
    * Do get_work here to receive WQE and 
    * processing of WQE will be done depending upon the tag value
    */
   for(;;)
   {
      work = cvmx_pow_work_request_sync(CVMX_POW_WAIT);
      if (!work)
      {
         continue;
      }

#ifdef DEBUGP
      SSDEBUG(("Got work"));
#endif

      if ((work->grp) == coreId)
      {
#ifdef DEBUGP
          SSDEBUG(("work received for this core"));
#endif
             
          /* invoke SSI handler function */
          ssWorkHndlr((void *)work);
       }

       else if ((work->grp) == UE_PCAP_PORT_GROUP)
       {
#ifdef DEBUGP
          SSDEBUG(("packet received"));
#endif
/* ue007.101: Changes for Cavium end to end performance */
          ueAppPktReceiver((void *)work); 
/* ue006.101: Changes for end to end performance */
        }
        else
        {
           /* ue007.101: Compilation error fix in cavium */
#ifdef DEBUGP
           SSDEBUG(("Invalid work group received:%d", work->grp));
#endif
           /* free the work queue entry buffer */
           cvmx_fpa_free(work, CVMX_FPA_WQE_POOL, 0);

        }
   }

   RETVALUE(0);
}



/**********************************************************************
 
         End of file:     ue_main.c@@/main/1 - Sun Mar 28 22:59:24 2010
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     vp                  1. Initial Release.
/main/1    ue006.101 sriky             1. Performance tuning
/main/1    ue007.101 Ekpal             1. Changes for Cavium end to end performance
/main/1    ue007.101 rk                1. Compilation error fix for cavium
*********************************************************************91*/






