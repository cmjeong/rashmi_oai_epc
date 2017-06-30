

/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_main.c 
  
     Sid:      ys_main.c@@/main/2 - Thu Dec  2 02:27:14 2010
  
     Prg:      esingh
  
**********************************************************************/

/** @file ys_main.c 
@brief This sample module includes the main function and does the SSI initialization
*/

#ifdef SS_CAVIUM

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "jz_task.h"       /* tasking */
#include "jz_msg.h"        /* messaging */
#include "jz_mem.h"        /* memory management interface */
#include "jz_gen.h"        /* general */

/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "jz_task.x"       /* tasking */
#include "jz_timer.x"      /* timers */
#include "jz_strm.x"       /* STREAMS */
#include "jz_msg.x"        /* messaging */
#include "jz_mem.x"        /* memory management interface */
#include "jz_gen.x"        /* general */

#include "cvmx-config.h"
#include "cvmx-pow.h"
#include "cvmx-bootmem.h"
#include "cvmx-fpa.h"

#ifdef __cplusplus /* ys004.102:g++ name mangling*/
EXTERN "C" {
#endif  /*__cplusplus*/

#include "cvmx-helper-fpa.h"

#ifdef __cplusplus 
}
#endif  /*__cplusplus*/

#include "cvmx-coremask.h"

/* #define ENB_CPU_MEASUREMENT */
#ifdef ENB_CPU_MEASUREMENT
#define YS_CPU_MEASURE_CYCLES_INTERVAL  10000000000
PRIVATE  U64 ysStartCycle = 0;
PRIVATE  U64 ysEndCycle = 0;
PRIVATE  U64 ysPrStartCycle = 0;
PRIVATE  U64 ysPrEndCycle = 0;
PRIVATE  U64 ysProCycles = 0;
PRIVATE  U64 ysTtlCycles = 0;
PRIVATE  U64 ysIdleCounter = 0;
PUBLIC   U64 ysCpuClkHz;

EXTERN S16 ysCalcCpuMeasurement(void);

inline S16 ysCalcCpuMeasurement()
{
   printf("Ttlcycles = %lld, prcsngCycles = %lld,idlecount = %lld CPU = %d \n",
          (ysTtlCycles), ysProCycles, ysIdleCounter,
          ((ysProCycles * 100) / (ysTtlCycles)));
   ysIdleCounter = 0;
   ysProCycles = 0;
   ysStartCycle = cvmx_get_cycle();
   return (0);
}
#endif /* ENB_CPU_MEASUREMENT */

#define OCTEON_CORE_ENB         0
#define OCTEON_CORE_TTI_GEN     3
#define YS_TTI_DUR              1000

#ifdef __cplusplus /* ys004.102:g++ name mangling*/
EXTERN "C" {
#endif  /*__cplusplus*/

EXTERN  Void ttiHdlr(Void);

#ifdef __cplusplus 
          }
#endif  /*__cplusplus*/

PRIVATE S16 ysSetupFpaPool ARGS((U64 fpaPool, S8 *poolName, U64 blockSize, U64 numBlocks));
PRIVATE S16 ysSimpleExecInit ARGS((void));
PRIVATE S16 ysTtiMain ARGS((Void));
PRIVATE S16 ysEnbMain ARGS((Void));

PRIVATE MtMemCfg myMemoCfg =
{
  SS_MAX_REGS,                                /* number of regions */
  {
    {
      SS_DFLT_REGION,                         /* region id */
      MT_MAX_BKTS,                            /* number of buckets */
      MT_HEAP_SIZE,                           /* heap size */
      {
         {MT_BKT_0_DSIZE, 0, SS_CVMX_POOL_0},  /* block size, no. of blocks, fpa pool id */
         {MT_BKT_1_DSIZE, 0, SS_CVMX_POOL_1},  /* block size, no. of blocks, fpa pool id */
         {MT_BKT_2_DSIZE, 0, SS_CVMX_POOL_2},  /* block size, no. of blocks, fpa pool id */
         {MT_BKT_3_DSIZE, 0, SS_CVMX_POOL_3}   /* block size, no. of blocks, fpa pool id */
      }
    },
    {
      SS_COREMEM_REGION,                      /* region id */
      MT_MAX_BKTS,                            /* number of buckets */
      MT_HEAP_SIZE,                           /* heap size */
      {
         {MT_BKT_0_DSIZE, MT_BKT_0_NUMBLKS, SS_INVALID_POOL},  /* block size, no. of blocks, fpa pool id */
         {MT_BKT_1_DSIZE, MT_BKT_1_NUMBLKS, SS_INVALID_POOL},  /* block size, no. of blocks, fpa pool id */
         {MT_BKT_2_DSIZE, MT_BKT_2_NUMBLKS, SS_INVALID_POOL},  /* block size, no. of blocks, fpa pool id */
         {MT_BKT_3_DSIZE, MT_BKT_3_NUMBLKS, SS_INVALID_POOL}   /* block size, no. of blocks, fpa pool id */
      }
    },
  }
};

/* type declarations */

/* public variable declarations */

/* ys004.102 : g++ compilation,redefined */
EXTERN PUBLIC S16 msArgc;              /* argc */
EXTERN PUBLIC Txt **msArgv;            /* argv */


/*
*
*       Fun:   main
*
*       Desc:  This sample function is the entry point for the final binary.
*              It does simple exec initialization.
*
*       Ret:   none on success
*              exit on failure
*
*       Notes:
*
*       File:  ys_main.c
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
   U16        coreId;

   TRC0(main);


   msArgc = argc;
   msArgv = argv;

   /* initialize the simple executive */
   if (ysSimpleExecInit() != ROK)
   {
      printf("simple exec init failed\n");
   }

   coreId = cvmx_get_core_num();

   switch (coreId)
   {
      case OCTEON_CORE_ENB:
      {
         ysEnbMain();
      }
      break;

      case OCTEON_CORE_TTI_GEN:
      {
         ysTtiMain();
      }
      break;

      default:
      {
         break;
      }
   }

   RETVALUE(0);
}


/*
*  initialization functions
*/
/*
*
*       Fun:   ysEnbMain 
*
*       Desc:  This function is the entry point for the enodeb SE code.
*
*       Ret:   ROK/RFAILED
*
*       Notes:
*
*       File:  ys_main.c
*
*/
#ifdef ANSI
PRIVATE S16 ysEnbMain 
(
Void
)
#else
PRIVATE S16 ysEnbMain(Void)
#endif
{
   cvmx_wqe_t *work;
   S16 ret;
#ifdef ENB_CPU_MEASUREMENT
   cvmx_sysinfo_t  *sys_info_ptr = cvmx_sysinfo_get();
#endif



   TRC1 (ysEnbMain);

#ifdef ENB_CPU_MEASUREMENT
   ysCpuClkHz = sys_info_ptr->cpu_clock_hz;
   printf("ysCpuClkHz = %d\n", (int)ysCpuClkHz);
#endif
   
   /* Do memory configuration */
   ret = ssInitMemCfg (&myMemoCfg);
   if (ret != ROK)
   {
      printf(" Failed memory configuration \n");
      RETVALUE (ROK);
   } 

   ret = ssInit();
   if (ret != ROK)
   {
      printf(" Failed SSI Init code \n");
      RETVALUE (ROK);
   }
   
#ifdef ENB_CPU_MEASUREMENT
   ysStartCycle = cvmx_get_cycle();
   ysProCycles = 0;
#endif
   for(;;)
   {
#ifdef ENB_CPU_MEASUREMENT
    ysEndCycle = cvmx_get_cycle();
    if (ysEndCycle < ysStartCycle) ysEndCycle += ysCpuClkHz;

    ysTtlCycles = ysEndCycle - ysStartCycle;
    if ((ysTtlCycles) > YS_CPU_MEASURE_CYCLES_INTERVAL)
    {
       ysCalcCpuMeasurement();
    }
#endif
      work = cvmx_pow_work_request_sync(CVMX_POW_WAIT);
      if (!work)
      {
#ifdef ENB_CPU_MEASUREMENT
         ysIdleCounter ++;
#endif
         
         continue;
      }

#ifdef ENB_CPU_MEASUREMENT
      ysPrStartCycle = cvmx_get_cycle();
#endif
      switch (work->tag)
      {    
         case SS_CVMX_TTI_TAG:
         {
            ttiHdlr();
         }
         break;

         default:
         {
            ssWorkHndlr((Void *)work);
         }
         break;
      }
#ifdef ENB_CPU_MEASUREMENT
      ysPrEndCycle = cvmx_get_cycle();
      if (ysPrEndCycle < ysPrStartCycle)
      {
         ysPrEndCycle += ysCpuClkHz; 
      }

      ysProCycles += ysPrEndCycle - ysPrStartCycle;
#endif
   }
   /* ys002.102: Added RETVALUE */
   RETVALUE (ROK);
}


/*
*
*       Fun:   ysTtiMain 
*
*       Desc:  This function is the entry point for the TTI generation code.
*
*       Ret:   ROK/RFAILED
*
*       Notes:
*
*       File:  ys_main.c
*
*/
#ifdef ANSI
PRIVATE S16 ysTtiMain 
(
Void
)
#else
PRIVATE S16 ysTtiMain(Void)
#endif
{
   cvmx_wqe_t     *workEntry;

   cvmx_pow_set_group_mask(cvmx_get_core_num(), (1 << cvmx_get_core_num()));
   /* allocate FPA WQE buffer */
   workEntry = (cvmx_wqe_t *)cvmx_fpa_alloc(CVMX_FPA_WQE_POOL);/*ys004.102:g++ compilation, cast */
   if (!workEntry)
   {
      printf("\nfailed to allocate WQE\n");
   }
   printf("\nWQE allocated for TTI\n");

   /* filling work queue entry */
   workEntry->qos      = 0;
   workEntry->grp      = 0;
   workEntry->tag_type = CVMX_POW_TAG_TYPE_NULL;
   workEntry->tag      = SS_CVMX_TTI_TAG;

   printf("\nWQE filled for TTI\n");

   for(;;)
   {
      cvmx_wait_usec(YS_TTI_DUR);  /* 10000=10ms; 1000=1ms */

      /* submit the work so that it can be received by the destined core */
      cvmx_pow_work_submit(workEntry, workEntry->tag, workEntry->tag_type, workEntry->qos, workEntry->grp);
   }

   return(0);
}

                                   
/*
*
*       Fun:   FPA pool setup function
*
*       Desc:  This function initializes the customized FPA pool.
*
*       Ret:   ROK/RFAILED
*
*       Notes:
*
*       File:  ys_main.c
*
*/
#ifdef ANSI
PRIVATE S16 ysSetupFpaPool 
(
U64      fpaPool, 
S8       *poolName,
U64      blockSize,
U64      numBlocks 
)
#else
PRIVATE S16 ysSetupFpaPool(fpaPool, poolName, blockSize, numBlocks)
U64      fpaPool;
S8       *poolName;
U64      blockSize;
U64      numBlocks; 
#endif
{
   void *memArea; 

   TRC0(ysSetupFpaPool);


   if ((blockSize == 0) || (numBlocks == 0))
   {
      RETVALUE(RFAILED);
   }

   if (cvmx_read_csr(CVMX_FPA_QUEX_AVAILABLE(fpaPool)) != 0)
   {
      RETVALUE(RFAILED);
   }

   /* allocated memory for FPA pool */
   /* ys001.102: Support for 32 bit environment */
#ifdef BIT_64
   memArea = cvmx_bootmem_alloc(blockSize * numBlocks, CVMX_CACHE_LINE_SIZE);
#else
   memArea = cvmx_bootmem_alloc_range(blockSize * numBlocks, CVMX_CACHE_LINE_SIZE, cvmx_phys_to_ptr(0x20000000), cvmx_phys_to_ptr(0x40000000));
#endif
   if (memArea == NULL)
   {
      RETVALUE(RFAILED);
   }

   if (cvmx_fpa_setup_pool(fpaPool, poolName, memArea, blockSize, numBlocks) != 0)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   Simple Executive initialization function
*
*       Desc:  This function does default initialization of SE and 
*              initializes common and customized FPA pools.
*
*       Ret:   ROK/RFAILED
*
*       Notes:
*
*       File:  ys_main.c
*
*/
#ifdef ANSI
PRIVATE S16 ysSimpleExecInit
(
)
#else
PRIVATE S16 ysSimpleExecInit()
#endif
{
   cvmx_sysinfo_t *sysinfo;
   U32 coremask_se;

   S16  ret;

   TRC0(ysSimpleExecInit);


   /* do default initialization of the SE */
   if (cvmx_user_app_init() != 0)
   {
      RETVALUE(RFAILED);
   }
  
    /* compute coremask_passthrough on all cores for the first barrier sync below */
    sysinfo = cvmx_sysinfo_get();
    coremask_se = sysinfo->core_mask;

   if (cvmx_coremask_first_core(coremask_se))
   {
      printf("\nCavium SE initialization start.\n");

      /* initialize FPA pools */
      if (cvmx_helper_initialize_fpa(SS_CVMX_NUM_PKT_BUFFERS, 
                                     SS_CVMX_NUM_WQE_BUFFERS, 
                                     SS_CVMX_NUM_PKO_BUFFERS, 
                                     SS_CVMX_NUM_TIM_BUFFERS, 
                                     SS_CVMX_NUM_DFA_BUFFERS) != 0)
      {
         RETVALUE(RFAILED);
      }

#ifdef DEBUGP
      SSDEBUG(("common FPA pools initialization done"));
#endif

      /* set up all custom FPA pools */
      /*ys004.102:g++ compilation */
      ret = ysSetupFpaPool(SS_CVMX_POOL_0,(S8*)& "Pool for bucket 0", SS_CVMX_POOL_0_SIZE, SS_CVMX_POOL_0_NUMBLKS);
      if (ROK != ret)
      {
         RETVALUE(RFAILED);
      }
      /*ys004.102:g++ compilation */
      ret = ysSetupFpaPool(SS_CVMX_POOL_1, (S8*)&"Pool for bucket 1", SS_CVMX_POOL_1_SIZE, SS_CVMX_POOL_1_NUMBLKS);
      if (ROK != ret)
      {
         RETVALUE(RFAILED);
      }
      /*ys004.102:g++ compilation */
      ret = ysSetupFpaPool(SS_CVMX_POOL_2, (S8*)&"Pool for bucket 2", SS_CVMX_POOL_2_SIZE, SS_CVMX_POOL_2_NUMBLKS);
      if (ROK != ret)
      {
         RETVALUE(RFAILED);
      }
      /*ys004.102:g++ compilation */
      ret = ysSetupFpaPool(SS_CVMX_POOL_3, (S8*)&"Pool for bucket 3", SS_CVMX_POOL_3_SIZE, SS_CVMX_POOL_3_NUMBLKS);
      if (ROK != ret)
      {
         RETVALUE(RFAILED);
      }

      printf("\nCavium SE initialization done.\n");
   }

   cvmx_coremask_barrier_sync(coremask_se);

   RETVALUE(ROK);
}
#endif /* SS_CAVIUM */

/**********************************************************************
 
         End of file:     ys_main.c@@/main/2 - Thu Dec  2 02:27:14 2010
 
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
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/2    ys001.102  rk                   1. Support for 32 bit environment
/main/2    ys002.102  rk                   1. Added missed RETVALUE
/main/2    ys004.102  ms                   1. g++ compilation fix.
*********************************************************************91*/
