///////////////////////////////////////////////////////////////////////////////
//
// threadstack.c
//
// See header file for documentation.
//
// Copyright Radisys Limited and David Rowe 8/5/06
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#if defined(BUILD_bfin_uclinux_2006)
# include <bits/local_lim.h>
# include <pthread.h>
//#include <bits/sysnum.h>
# include <internals.h> /* from uClibc libpthread */
#endif

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "threadstack.h"
#include "pthread_utils.h"


///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

u32 threadstack_checkStackAddressValid(u32 ptrToStackValue)
{
#if defined(BUILD_bfin_uclinux_2006)
  pthread_t thread = pthread_self();
  pthread_handle handle = thread_handle(thread);
  // this may be zero at thread start...or something...
  // so assume all is well...until proven otherwise.
  if (handle->h_bottom > 0)
  {
      // NB I couldn't find a way to get the correct stack size so assume the maximum size for now...
      // it'll pick up gross errors and that should be good enough for now.
      if (((u32)ptrToStackValue  >= (u32)handle->h_bottom) && ((u32)ptrToStackValue  <= (u32)(handle->h_bottom + MAXIMUM_THREAD_STACK_SIZE)))
          return 1;
      else
          return 0;
  }
  return 1;
#else
  return 0;
#endif
}

u32 threadstack_getStackBottom(pthread_t *thread)
{
#if defined(BUILD_bfin_uclinux_2006)
  pthread_handle handle = thread_handle(*thread);
  return (u32)(handle->h_bottom);
#else
  return 0;
#endif
}

u32 threadstack_getStackTop(pthread_t *thread)
{
#if defined(BUILD_bfin_uclinux_2006)
  pthread_handle handle = thread_handle(*thread);
  return (u32)(handle->h_descr);
#else
  return 0;
#endif
}

u32 threadstack_free(pthread_t *thread)
{
#if defined(BUILD_bfin_uclinux_2006)
  pthread_handle    handle = thread_handle(*thread);
  pthread_descr     th = handle->h_descr;
  u32               *p;

  for(p=(u32*)handle->h_bottom;
      ((p<(u32*)th) && (*p==0));
      p++);

  return (u32)p - (u32)handle->h_bottom;
#else
  return 0;
#endif
}

u32 threadstack_used(pthread_t *thread)
{
#if defined(BUILD_bfin_uclinux_2006)
  pthread_handle    handle = thread_handle(*thread);
  pthread_descr     th = handle->h_descr;
  u32               *p;

  for(p=(u32*)handle->h_bottom;
      ((p<(u32*)th) && (*p==0));
      p++);

  return (u32)th - (u32)p;
#else
  return 0;
#endif

}

void threadstack_checkStackUsage()
{
#if defined(BUILD_bfin_uclinux_2006)
    pthread_t thread = pthread_self();
    u32 stackUsage;

    stackUsage = threadstack_used(&thread);
    // Warn if blown or close to blowing.
    // TODO - should check against actual size used... can we get this from thread attributes?
    if(stackUsage >= LARGE_DEFAULT_THREAD_STACK_SIZE - 1024) {
        TRACE_PRINTF("********************************");
        TRACE_PRINTF("THREAD STACK WARNING!  Thread ID %" PRIu32, (u32)thread);
        TRACE_PRINTF("  Peak stack usage %" PRIu32, stackUsage);
    }
#endif
}
