///////////////////////////////////////////////////////////////////////////////
//
// Expect.h
//
// Branch prediction macros.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Expect_h_
#define __Expect_h_

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////

#if defined(__GNUC__)

/* GCC branch prediction from version 2.96 onwards */
#if !defined(likely) && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96))
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#endif

/** Write memory-barrier.
 * This prevents the compiler from optimising the order of memory writes
 * across the barrier, and if appropriate, may implement a CPU specific
 * memory barrier instruction.
 */
#define wmb()  __asm__ __volatile__("": : :"memory")

/** Read memory-barrier.
 * This prevents the compiler from optimising the order of memory reads
 * across the barrier, and if appropriate, may implement a CPU specific
 * memory barrier instruction.
 */
#define rmb()  __asm__ __volatile__("": : :"memory")

/** Memory-barrier.
 * This prevents the compiler from optimising the order of memory access
 * across the barrier, and if appropriate, may implement a CPU specific
 * memory barrier instruction.
 */
#define mb()  __asm__ __volatile__("": : :"memory")

#endif

///////////////////////////////////////////////////////////////////////////////
// Defaults
///////////////////////////////////////////////////////////////////////////////

#ifndef likely
#define likely(x)    x
#endif

#ifndef unlikely
#define unlikely(x)  x
#endif

#ifndef wmb
#define wmb()
#endif

#ifndef rmb
#define rmb()
#endif

#ifndef mb
#define mb()
#endif

#endif // __Expect_h_
