///////////////////////////////////////////////////////////////////////////////
//
// threadstack.h
//
// Utilities to measure thread stack usage.
// Assumes that the memory used for the stack is initially set to all
// 0's and that when we find a non-zero value that represents the current
// "high water mark" of stack usage.
//
// Copyright Radisys Limited and David Rowe 8/5/06
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __threadstack_h__
#define __threadstack_h__

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <pthread.h>
#include <3waytypes.h>

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

u32 threadstack_checkStackAddressValid(u32 ptrToStackValue);
u32 threadstack_getStackBottom(pthread_t *thread);
u32 threadstack_getStackTop(pthread_t *thread);
u32 threadstack_free(pthread_t *thread);
u32 threadstack_used(pthread_t *thread);

void threadstack_checkStackUsage(void);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif
