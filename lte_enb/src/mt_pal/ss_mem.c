

/********************************************************************20**

     Name:     System Services -- Memory management interface

     Type:     C source file

     Desc:     Implementation of the memory management interface.

     File:     ss_mem.c

     Sid:      ss_mem.c@@/main/2 - Mon Apr  5 18:01:16 2010

     Prg:      kp

*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "ss_err.h"        /* errors */
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */



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



/*
*     Interface functions
*/
 

/*
*
*       Fun:   SRegRegion
*
*       Desc:  Registers a memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_mem.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegRegion
(
Region region,                  /* region ID */
SRegInfo *regInfo               /* information about the region */
)
#else
PUBLIC S16 SRegRegion(region, regInfo)
Region region;                  /* region ID */
SRegInfo *regInfo;              /* information about the region */
#endif
{
   S16 ret;


   TRC1(SRegRegion);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS667, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate region info pointer */
   if (regInfo == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS668, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the region table */
   SS_ACQUIRE_ALL_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS669, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is not registered */
   if (osCp.regionTbl[region].used == TRUE)
   {
      SS_RELEASE_ALL_SEMA(&osCp.regionTblSem);

      SSLOGERROR(ERRCLS_INT_PAR, ESS670, ERRZERO, "Region ID used");
      RETVALUE(RFAILED);
   }
#endif


   /* fill in the region information */
   osCp.regionTbl[region].used = TRUE;
   osCp.regionTbl[region].regCb = regInfo->regCb;
   osCp.regionTbl[region].flags = regInfo->flags;
   osCp.regionTbl[region].start = regInfo->start;
   osCp.regionTbl[region].size = regInfo->size;
   osCp.regionTbl[region].alloc = regInfo->alloc;
   osCp.regionTbl[region].free = regInfo->free;
   osCp.regionTbl[region].ctl = regInfo->ctl;

   osCp.numRegions++;


   /* unlock the region table */
   SS_RELEASE_ALL_SEMA(&osCp.regionTblSem);


   RETVALUE(ROK);
}


/*
*
*       Fun:   SDeregRegion
*
*       Desc:  Deregisters a memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_mem.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeregRegion
(
Region region                   /* region ID */
)
#else
PUBLIC S16 SDeregRegion(region)
Region region;                  /* region ID */
#endif
{
   S16 ret;


   TRC1(SDeregRegion);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS671, region, "Invalid region");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the region table */
   SS_ACQUIRE_ALL_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS672, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check if this region is registered */
   if (osCp.regionTbl[region].used == FALSE)
   {
      SS_RELEASE_ALL_SEMA(&osCp.regionTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESS673, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif


   /* empty the information about the region */
   osCp.regionTbl[region].used = FALSE;
   osCp.regionTbl[region].start = NULLP;
   osCp.regionTbl[region].size = 0;
   osCp.regionTbl[region].regCb = NULLP;
   osCp.regionTbl[region].flags = 0;
   osCp.regionTbl[region].alloc = NULLP;
   osCp.regionTbl[region].free = NULLP;
   osCp.regionTbl[region].ctl = NULLP;

   osCp.numRegions--;


   /* unlock the region table */
   SS_RELEASE_ALL_SEMA(&osCp.regionTblSem);


   RETVALUE(ROK);
}


/*
*
*       Fun:   SAlloc
*
*       Desc:  Allocates a block of memory of at least the specified
*              size.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_mem.c
*
*/
#ifdef ANSI
PUBLIC S16 SAlloc
(
Region region,                  /* region ID */
Size *size,                     /* size of block required/allocated */
U32 flags,                      /* allocation flags */
Data **ptr                      /* filled with pointer to block */
)
#else
PUBLIC S16 SAlloc(region, size, flags, ptr)
Region region;                  /* region ID */
Size *size;                     /* size of block required/allocated */
U32 flags;                      /* allocation flags */
Data **ptr;                     /* filled with pointer to block */
#endif
{
   S16 ret;


   TRC1(SAlloc);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS674, region, "Invalid region");
      RETVALUE(RFAILED);
   }
#endif

/* ss037.103 Removed the semaphore acquisition for performance enhancement */
#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS675, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }

#endif
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {
/* ss037.103 Removed the semaphore operation for performance enhancement */
#ifndef SS_PERF
#if 0  /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS676, ERRZERO, 
                  "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: deletion */
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS677, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif


   /* call the memory manager, to allocate this memory */
/* ss036.103 - addition for passing memType as dynamic */
#ifdef SSI_DEBUG_LEVEL1
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, size, flags, ptr, SS_DYNAMIC_MEM_FLAG);
#else
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, size, flags, ptr);
#endif /* SSI_DEBUG_LEVEL1 */

/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* release the semaphore we took */
#if 0  /* ss006.13: deletion */
   SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
     SSLOGERROR(ERRCLS_DEBUG, ESS678, ERRZERO, 
                  "Could not release the semaphore");
     RETVALUE(RFAILED);
#endif
   }
#endif /* ss006.13: deletion */
#endif
/* ss036.103 - Addition to handle the memory trampling return value
* This in turn can call SRegMemErrHdlr 
*/
#ifdef SSI_DEBUG_LEVEL1
    if (ret == RTRAMPLINGNOK)
    {
        SRegMemErrHdlr( region,  *ptr,  ret);
    }
#endif /* SSI_DEBUG_LEVEL1 */

   RETVALUE(ret);
}


/*
*
*       Fun:   SFree
*
*       Desc:  Frees a block of memory previously allocated by SAlloc().
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_mem.c
*
*/
#ifdef ANSI
PUBLIC S16 SFree
(
Region region,                  /* region ID */
Data *ptr,                      /* pointer to the allocated block */
Size size                       /* size of block */
)
#else
PUBLIC S16 SFree(region, ptr, size)
Region region;                  /* region ID */
Data *ptr;                      /* pointer to the allocated block */
Size size;                      /* size of block */
#endif
{
   S16 ret;


   TRC1(SFree);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS679, region, "Invalid region");
      RETVALUE(RFAILED);
   }

/* ss021.103 - Addition to validate size and ptr */
   if (size <= NULLD)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS680, region, "Invalid size");
      RETVALUE(RFAILED);
   }

   /* validate ptr */
   if (ptr == (Data *)NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS681, region, "Invalid ptr");
      RETVALUE(RFAILED);
   }

#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS682, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }
#endif
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is around */
   if (osCp.regionTbl[region].used == FALSE)
   {
#ifndef SS_PERF
#if 0  /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS683, ERRZERO, 
                  "Could not release the semaphore");
         RETVALUE(RFAILED);
#endif
       }
#endif /* ss006.13: addition */
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS684, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif


   /* call the memory manager to free this memory */
   ret = (osCp.regionTbl[region].free)(osCp.regionTbl[region].regCb, ptr, size);

/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* release the semaphore we took */
#if 0  /* ss006.13: deletion */
   SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS685, ERRZERO, 
                  "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
    }
#endif /* ss006.13: addition */
#endif
/* ss036.103 - changes to handle double free and trmapling return values
* This in turn may invoke SRegMemErrHdlr 
*/
#ifdef SSI_DEBUG_LEVEL1
    /* handle the double free error here by calling the OS specific error handling function */
    if ((ret == RDBLFREE) || (ret == RTRAMPLINGNOK))
    {
        SRegMemErrHdlr( region,  ptr,  ret);
    }
#endif /* SSI_DEBUG_LEVEL1 */

   RETVALUE(ret);
}



/********************************************************************30**
 
         End of file:     ss_mem.c@@/main/2 - Mon Apr  5 18:01:16 2010
 
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

1.2          ---      kp   1. cosmetic changes, error codes regenerated

1.2+        ss006.13  jn   2. Compile Warning - "Value computed is
                              not used" removed for SS_RELEASE_SEMA.
1.3+        ss021.103 bjp  1. Validate size and ptr for SFree
1.3+        ss029.103 kkj  1. Error codes modified
1.3+        ss036.103 vk   1. Changes for SSI enhancements
1.3+        ss037.103 gs   1. SSI enhancements guarded under SS_PERF
/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
