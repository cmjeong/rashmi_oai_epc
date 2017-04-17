







typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;



__extension__
typedef long long int int64_t;




typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;





__extension__
typedef unsigned long long int uint64_t;






typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;



__extension__
typedef long long int int_least64_t;



typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;



__extension__
typedef unsigned long long int uint_least64_t;






typedef signed char int_fast8_t;





typedef int int_fast16_t;
typedef int int_fast32_t;
__extension__
typedef long long int int_fast64_t;



typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
__extension__
typedef unsigned long long int uint_fast64_t;
typedef int intptr_t;


typedef unsigned int uintptr_t;
__extension__
typedef long long int intmax_t;
__extension__
typedef unsigned long long int uintmax_t;






typedef long int __gwchar_t;

typedef struct
  {
    __extension__ long long int quot;
    __extension__ long long int rem;
  } imaxdiv_t;





extern intmax_t imaxabs (intmax_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern imaxdiv_t imaxdiv (intmax_t __numer, intmax_t __denom)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern intmax_t strtoimax (const char *__restrict __nptr,
      char **__restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));


extern uintmax_t strtoumax (const char *__restrict __nptr,
       char ** __restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));


extern intmax_t wcstoimax (const __gwchar_t *__restrict __nptr,
      __gwchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));


extern uintmax_t wcstoumax (const __gwchar_t *__restrict __nptr,
       __gwchar_t ** __restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int __strtoll_internal (const char *__restrict __nptr,
      char **__restrict __endptr,
      int __base, int __group)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));

extern __inline __attribute__ ((__gnu_inline__)) intmax_t
__attribute__ ((__nothrow__ , __leaf__)) strtoimax (const char *__restrict nptr, char **__restrict endptr, int base)

{
  return __strtoll_internal (nptr, endptr, base, 0);
}

__extension__
extern unsigned long long int __strtoull_internal (const char *
         __restrict __nptr,
         char **
         __restrict __endptr,
         int __base,
         int __group)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));

extern __inline __attribute__ ((__gnu_inline__)) uintmax_t
__attribute__ ((__nothrow__ , __leaf__)) strtoumax (const char *__restrict nptr, char **__restrict endptr, int base)

{
  return __strtoull_internal (nptr, endptr, base, 0);
}

__extension__
extern long long int __wcstoll_internal (const __gwchar_t *__restrict __nptr,
      __gwchar_t **__restrict __endptr,
      int __base, int __group)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));

extern __inline __attribute__ ((__gnu_inline__)) intmax_t
__attribute__ ((__nothrow__ , __leaf__)) wcstoimax (const __gwchar_t *__restrict nptr, __gwchar_t **__restrict endptr, int base)

{
  return __wcstoll_internal (nptr, endptr, base, 0);
}


__extension__
extern unsigned long long int __wcstoull_internal (const __gwchar_t *
         __restrict __nptr,
         __gwchar_t **
         __restrict __endptr,
         int __base,
         int __group)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));

extern __inline __attribute__ ((__gnu_inline__)) uintmax_t
__attribute__ ((__nothrow__ , __leaf__)) wcstoumax (const __gwchar_t *__restrict nptr, __gwchar_t **__restrict endptr, int base)

{
  return __wcstoull_internal (nptr, endptr, base, 0);
}










typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;




__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;







__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;


__extension__ typedef __u_quad_t __dev_t;
__extension__ typedef unsigned int __uid_t;
__extension__ typedef unsigned int __gid_t;
__extension__ typedef unsigned long int __ino_t;
__extension__ typedef __u_quad_t __ino64_t;
__extension__ typedef unsigned int __mode_t;
__extension__ typedef unsigned int __nlink_t;
__extension__ typedef long int __off_t;
__extension__ typedef __quad_t __off64_t;
__extension__ typedef int __pid_t;
__extension__ typedef struct { int __val[2]; } __fsid_t;
__extension__ typedef long int __clock_t;
__extension__ typedef unsigned long int __rlim_t;
__extension__ typedef __u_quad_t __rlim64_t;
__extension__ typedef unsigned int __id_t;
__extension__ typedef long int __time_t;
__extension__ typedef unsigned int __useconds_t;
__extension__ typedef long int __suseconds_t;

__extension__ typedef int __daddr_t;
__extension__ typedef int __key_t;


__extension__ typedef int __clockid_t;


__extension__ typedef void * __timer_t;


__extension__ typedef long int __blksize_t;




__extension__ typedef long int __blkcnt_t;
__extension__ typedef __quad_t __blkcnt64_t;


__extension__ typedef unsigned long int __fsblkcnt_t;
__extension__ typedef __u_quad_t __fsblkcnt64_t;


__extension__ typedef unsigned long int __fsfilcnt_t;
__extension__ typedef __u_quad_t __fsfilcnt64_t;


__extension__ typedef int __fsword_t;

__extension__ typedef int __ssize_t;


__extension__ typedef long int __syscall_slong_t;

__extension__ typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


__extension__ typedef int __intptr_t;


__extension__ typedef unsigned int __socklen_t;






static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
typedef unsigned int size_t;







typedef __time_t time_t;



struct timespec
  {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
  };


typedef __pid_t pid_t;





struct sched_param
  {
    int __sched_priority;
  };





extern int clone (int (*__fn) (void *__arg), void *__child_stack,
    int __flags, void *__arg, ...) __attribute__ ((__nothrow__ , __leaf__));


extern int unshare (int __flags) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getcpu (void) __attribute__ ((__nothrow__ , __leaf__));


extern int setns (int __fd, int __nstype) __attribute__ ((__nothrow__ , __leaf__));











struct __sched_param
  {
    int __sched_priority;
  };
typedef unsigned long int __cpu_mask;






typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;


extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
  __attribute__ ((__nothrow__ , __leaf__));
extern cpu_set_t *__sched_cpualloc (size_t __count) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern void __sched_cpufree (cpu_set_t *__set) __attribute__ ((__nothrow__ , __leaf__));









extern int sched_setparam (__pid_t __pid, const struct sched_param *__param)
     __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getparam (__pid_t __pid, struct sched_param *__param) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_setscheduler (__pid_t __pid, int __policy,
          const struct sched_param *__param) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getscheduler (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_yield (void) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_get_priority_max (int __algorithm) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_get_priority_min (int __algorithm) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) __attribute__ ((__nothrow__ , __leaf__));
extern int sched_setaffinity (__pid_t __pid, size_t __cpusetsize,
         const cpu_set_t *__cpuset) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getaffinity (__pid_t __pid, size_t __cpusetsize,
         cpu_set_t *__cpuset) __attribute__ ((__nothrow__ , __leaf__));














struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
struct timex
{
  unsigned int modes;
  __syscall_slong_t offset;
  __syscall_slong_t freq;
  __syscall_slong_t maxerror;
  __syscall_slong_t esterror;
  int status;
  __syscall_slong_t constant;
  __syscall_slong_t precision;
  __syscall_slong_t tolerance;
  struct timeval time;
  __syscall_slong_t tick;
  __syscall_slong_t ppsfreq;
  __syscall_slong_t jitter;
  int shift;
  __syscall_slong_t stabil;
  __syscall_slong_t jitcnt;
  __syscall_slong_t calcnt;
  __syscall_slong_t errcnt;
  __syscall_slong_t stbcnt;

  int tai;


  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32;
};




extern int clock_adjtime (__clockid_t __clock_id, struct timex *__utx) __attribute__ ((__nothrow__ , __leaf__));




typedef __clock_t clock_t;



typedef __clockid_t clockid_t;
typedef __timer_t timer_t;


struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  const char *tm_zone;




};








struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };


struct sigevent;



extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));


extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));


extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));





extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));





extern char *strptime (const char *__restrict __s,
         const char *__restrict __fmt, struct tm *__tp)
     __attribute__ ((__nothrow__ , __leaf__));





typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;

extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     const char *__restrict __format,
     const struct tm *__restrict __tp,
     __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));



extern char *strptime_l (const char *__restrict __s,
    const char *__restrict __fmt, struct tm *__tp,
    __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));






extern struct tm *gmtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));





extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));





extern char *asctime (const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern char *ctime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));







extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));


extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));



extern int daylight;
extern long int timezone;





extern int stime (const time_t *__when) __attribute__ ((__nothrow__ , __leaf__));
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int dysize (int __year) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__));






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));


extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));





extern int timespec_get (struct timespec *__ts, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int getdate_err;
extern struct tm *getdate (const char *__string);
extern int getdate_r (const char *__restrict __string,
        struct tm *__restrict __resbufp);




typedef unsigned long int pthread_t;


union pthread_attr_t
{
  char __size[36];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;
typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;





typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;





    int __kind;
    unsigned int __nusers;
    __extension__ union
    {
      struct
      {
 short __espins;
 short __elision;



      } __elision_data;
      __pthread_slist_t __list;
    };

  } __data;
  char __size[24];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;


    unsigned char __flags;
    unsigned char __shared;
    signed char __rwelision;

    unsigned char __pad2;
    int __writer;
  } __data;

  char __size[32];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[20];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
typedef int __jmp_buf[6];



enum
{
  PTHREAD_CREATE_JOINABLE,

  PTHREAD_CREATE_DETACHED

};



enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP

  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL



  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP

};




enum
{
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};





enum
{
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT
};
enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
enum
{
  PTHREAD_INHERIT_SCHED,

  PTHREAD_EXPLICIT_SCHED

};



enum
{
  PTHREAD_SCOPE_SYSTEM,

  PTHREAD_SCOPE_PROCESS

};



enum
{
  PTHREAD_PROCESS_PRIVATE,

  PTHREAD_PROCESS_SHARED

};
struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
};


enum
{
  PTHREAD_CANCEL_ENABLE,

  PTHREAD_CANCEL_DISABLE

};
enum
{
  PTHREAD_CANCEL_DEFERRED,

  PTHREAD_CANCEL_ASYNCHRONOUS

};





extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));





extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));







extern int pthread_join (pthread_t __th, void **__thread_return);




extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) __attribute__ ((__nothrow__ , __leaf__));







extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
     const struct timespec *__abstime);






extern int pthread_detach (pthread_t __th) __attribute__ ((__nothrow__ , __leaf__));



extern pthread_t pthread_self (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int pthread_equal (pthread_t __thread1, pthread_t __thread2)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));







extern int pthread_attr_init (pthread_attr_t *__attr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_destroy (pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getdetachstate (const pthread_attr_t *__attr,
     int *__detachstate)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
     int __detachstate)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getguardsize (const pthread_attr_t *__attr,
          size_t *__guardsize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
          size_t __guardsize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getschedparam (const pthread_attr_t *__restrict __attr,
           struct sched_param *__restrict __param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedparam (pthread_attr_t *__restrict __attr,
           const struct sched_param *__restrict
           __param) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_getschedpolicy (const pthread_attr_t *__restrict
     __attr, int *__restrict __policy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getinheritsched (const pthread_attr_t *__restrict
      __attr, int *__restrict __inherit)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
      int __inherit)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getscope (const pthread_attr_t *__restrict __attr,
      int *__restrict __scope)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getstackaddr (const pthread_attr_t *__restrict
          __attr, void **__restrict __stackaddr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__deprecated__));





extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
          void *__stackaddr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__));


extern int pthread_attr_getstacksize (const pthread_attr_t *__restrict
          __attr, size_t *__restrict __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
          size_t __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getstack (const pthread_attr_t *__restrict __attr,
      void **__restrict __stackaddr,
      size_t *__restrict __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
      size_t __stacksize) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int pthread_attr_setaffinity_np (pthread_attr_t *__attr,
     size_t __cpusetsize,
     const cpu_set_t *__cpuset)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));



extern int pthread_attr_getaffinity_np (const pthread_attr_t *__attr,
     size_t __cpusetsize,
     cpu_set_t *__cpuset)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));


extern int pthread_getattr_default_np (pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_setattr_default_np (const pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int pthread_getattr_np (pthread_t __th, pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));







extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
      const struct sched_param *__param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));


extern int pthread_getschedparam (pthread_t __target_thread,
      int *__restrict __policy,
      struct sched_param *__restrict __param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));


extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     __attribute__ ((__nothrow__ , __leaf__));




extern int pthread_getname_np (pthread_t __target_thread, char *__buf,
          size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int pthread_setname_np (pthread_t __target_thread, const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));





extern int pthread_getconcurrency (void) __attribute__ ((__nothrow__ , __leaf__));


extern int pthread_setconcurrency (int __level) __attribute__ ((__nothrow__ , __leaf__));







extern int pthread_yield (void) __attribute__ ((__nothrow__ , __leaf__));




extern int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize,
       const cpu_set_t *__cpuset)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));


extern int pthread_getaffinity_np (pthread_t __th, size_t __cpusetsize,
       cpu_set_t *__cpuset)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));
extern int pthread_once (pthread_once_t *__once_control,
    void (*__init_routine) (void)) __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_setcancelstate (int __state, int *__oldstate);



extern int pthread_setcanceltype (int __type, int *__oldtype);


extern int pthread_cancel (pthread_t __th);




extern void pthread_testcancel (void);




typedef struct
{
  struct
  {
    __jmp_buf __cancel_jmp_buf;
    int __mask_was_saved;
  } __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t __attribute__ ((__aligned__));
struct __pthread_cleanup_frame
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};
extern void __pthread_register_cancel (__pthread_unwind_buf_t *__buf)
     __attribute__ ((__regparm__ (1)));
extern void __pthread_unregister_cancel (__pthread_unwind_buf_t *__buf)
  __attribute__ ((__regparm__ (1)));
extern void __pthread_register_cancel_defer (__pthread_unwind_buf_t *__buf)
     __attribute__ ((__regparm__ (1)));
extern void __pthread_unregister_cancel_restore (__pthread_unwind_buf_t *__buf)
  __attribute__ ((__regparm__ (1)));



extern void __pthread_unwind_next (__pthread_unwind_buf_t *__buf)
     __attribute__ ((__regparm__ (1))) __attribute__ ((__noreturn__))

     __attribute__ ((__weak__))

     ;



struct __jmp_buf_tag;
extern int __sigsetjmp (struct __jmp_buf_tag *__env, int __savemask) __attribute__ ((__nothrow__));





extern int pthread_mutex_init (pthread_mutex_t *__mutex,
          const pthread_mutexattr_t *__mutexattr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
        const struct timespec *__restrict
        __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_getprioceiling (const pthread_mutex_t *
      __restrict __mutex,
      int *__restrict __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
      int __prioceiling,
      int *__restrict __old_ceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));




extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern int pthread_mutex_consistent_np (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t *
      __restrict __attr,
      int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
      int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_gettype (const pthread_mutexattr_t *__restrict
          __attr, int *__restrict __kind)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *
       __restrict __attr,
       int *__restrict __protocol)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
       int __protocol)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *
          __restrict __attr,
          int *__restrict __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
          int __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getrobust (const pthread_mutexattr_t *__attr,
     int *__robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int pthread_mutexattr_getrobust_np (const pthread_mutexattr_t *__attr,
        int *__robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
     int __robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern int pthread_mutexattr_setrobust_np (pthread_mutexattr_t *__attr,
        int __robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock,
    const pthread_rwlockattr_t *__restrict
    __attr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
       int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getkind_np (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pref)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
       int __pref) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
         const pthread_condattr_t *__restrict __cond_attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_destroy (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_signal (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
         pthread_mutex_t *__restrict __mutex)
     __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
       pthread_mutex_t *__restrict __mutex,
       const struct timespec *__restrict __abstime)
     __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_condattr_init (pthread_condattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_getpshared (const pthread_condattr_t *
     __restrict __attr,
     int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
     int __pshared) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_condattr_getclock (const pthread_condattr_t *
          __restrict __attr,
          __clockid_t *__restrict __clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
          __clockid_t __clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int pthread_barrier_init (pthread_barrier_t *__restrict __barrier,
     const pthread_barrierattr_t *__restrict
     __attr, unsigned int __count)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_getpshared (const pthread_barrierattr_t *
        __restrict __attr,
        int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
        int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_key_create (pthread_key_t *__key,
          void (*__destr_function) (void *))
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_key_delete (pthread_key_t __key) __attribute__ ((__nothrow__ , __leaf__));


extern void *pthread_getspecific (pthread_key_t __key) __attribute__ ((__nothrow__ , __leaf__));


extern int pthread_setspecific (pthread_key_t __key,
    const void *__pointer) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int pthread_getcpuclockid (pthread_t __thread_id,
      __clockid_t *__clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int pthread_atfork (void (*__prepare) (void),
      void (*__parent) (void),
      void (*__child) (void)) __attribute__ ((__nothrow__ , __leaf__));




extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) pthread_equal (pthread_t __thread1, pthread_t __thread2)
{
  return __thread1 == __thread2;
}







struct _IO_FILE;



typedef struct _IO_FILE FILE;





typedef struct _IO_FILE __FILE;




typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
typedef __builtin_va_list __gnuc_va_list;
struct _IO_jump_t; struct _IO_FILE;





typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
  __off64_t _offset;







  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;

  size_t __pad5;
  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);




typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;


typedef struct
{
  __io_read_fn *read;
  __io_write_fn *write;
  __io_seek_fn *seek;
  __io_close_fn *close;
} _IO_cookie_io_functions_t;
typedef _IO_cookie_io_functions_t cookie_io_functions_t;

struct _IO_cookie_file;


extern void _IO_cookie_init (struct _IO_cookie_file *__cfile, int __read_write,
        void *__cookie, _IO_cookie_io_functions_t __fns);







extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));




typedef __gnuc_va_list va_list;
typedef __off_t off_t;






typedef __off64_t off64_t;






typedef __ssize_t ssize_t;







typedef _G_fpos_t fpos_t;





typedef _G_fpos64_t fpos64_t;



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;







extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));




extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));








extern FILE *tmpfile (void) __attribute__ ((__warn_unused_result__));
extern FILE *tmpfile64 (void) __attribute__ ((__warn_unused_result__));



extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));





extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__warn_unused_result__));








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

extern int fflush_unlocked (FILE *__stream);
extern int fcloseall (void);









extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) __attribute__ ((__warn_unused_result__));




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));


extern FILE *fopen64 (const char *__restrict __filename,
        const char *__restrict __modes) __attribute__ ((__warn_unused_result__));
extern FILE *freopen64 (const char *__restrict __filename,
   const char *__restrict __modes,
   FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));




extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));





extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     _IO_cookie_io_functions_t __io_funcs) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));






extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));





extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));








extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));





extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));






extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0))) __attribute__ ((__warn_unused_result__));
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) __attribute__ ((__warn_unused_result__));
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) __attribute__ ((__warn_unused_result__));




extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));








extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) __attribute__ ((__warn_unused_result__));




extern int scanf (const char *__restrict __format, ...) __attribute__ ((__warn_unused_result__));

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));








extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__warn_unused_result__));





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) __attribute__ ((__warn_unused_result__));


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));









extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);

extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream);











extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);

extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);








extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __attribute__ ((__warn_unused_result__));

extern char *fgets_unlocked (char *__restrict __s, int __n,
        FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));







extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));








extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

extern int fputs_unlocked (const char *__restrict __s,
      FILE *__restrict __stream);
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) __attribute__ ((__warn_unused_result__));




extern void rewind (FILE *__stream);

extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) __attribute__ ((__warn_unused_result__));






extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);



extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) __attribute__ ((__warn_unused_result__));
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);




extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));








extern void perror (const char *__s);






extern int sys_nerr;
extern const char *const sys_errlist[];


extern int _sys_nerr;
extern const char *const _sys_errlist[];




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern FILE *popen (const char *__command, const char *__modes) __attribute__ ((__warn_unused_result__));





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));





extern char *cuserid (char *__s);




struct obstack;


extern int obstack_printf (struct obstack *__restrict __obstack,
      const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
       const char *__restrict __format,
       __gnuc_va_list __args)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0)));







extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern __inline __attribute__ ((__gnu_inline__)) int
getchar (void)
{
  return _IO_getc (stdin);
}




extern __inline __attribute__ ((__gnu_inline__)) int
fgetc_unlocked (FILE *__fp)
{
  return (__builtin_expect (((__fp)->_IO_read_ptr >= (__fp)->_IO_read_end), 0) ? __uflow (__fp) : *(unsigned char *) (__fp)->_IO_read_ptr++);
}





extern __inline __attribute__ ((__gnu_inline__)) int
getc_unlocked (FILE *__fp)
{
  return (__builtin_expect (((__fp)->_IO_read_ptr >= (__fp)->_IO_read_end), 0) ? __uflow (__fp) : *(unsigned char *) (__fp)->_IO_read_ptr++);
}


extern __inline __attribute__ ((__gnu_inline__)) int
getchar_unlocked (void)
{
  return (__builtin_expect (((stdin)->_IO_read_ptr >= (stdin)->_IO_read_end), 0) ? __uflow (stdin) : *(unsigned char *) (stdin)->_IO_read_ptr++);
}




extern __inline __attribute__ ((__gnu_inline__)) int
putchar (int __c)
{
  return _IO_putc (__c, stdout);
}




extern __inline __attribute__ ((__gnu_inline__)) int
fputc_unlocked (int __c, FILE *__stream)
{
  return (__builtin_expect (((__stream)->_IO_write_ptr >= (__stream)->_IO_write_end), 0) ? __overflow (__stream, (unsigned char) (__c)) : (unsigned char) (*(__stream)->_IO_write_ptr++ = (__c)));
}





extern __inline __attribute__ ((__gnu_inline__)) int
putc_unlocked (int __c, FILE *__stream)
{
  return (__builtin_expect (((__stream)->_IO_write_ptr >= (__stream)->_IO_write_end), 0) ? __overflow (__stream, (unsigned char) (__c)) : (unsigned char) (*(__stream)->_IO_write_ptr++ = (__c)));
}


extern __inline __attribute__ ((__gnu_inline__)) int
putchar_unlocked (int __c)
{
  return (__builtin_expect (((stdout)->_IO_write_ptr >= (stdout)->_IO_write_end), 0) ? __overflow (stdout, (unsigned char) (__c)) : (unsigned char) (*(stdout)->_IO_write_ptr++ = (__c)));
}





extern __inline __attribute__ ((__gnu_inline__)) __ssize_t
getline (char **__lineptr, size_t *__n, FILE *__stream)
{
  return __getdelim (__lineptr, __n, '\n', __stream);
}





extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) feof_unlocked (FILE *__stream)
{
  return (((__stream)->_flags & 0x10) != 0);
}


extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) ferror_unlocked (FILE *__stream)
{
  return (((__stream)->_flags & 0x20) != 0);
}


extern int __sprintf_chk (char *__restrict __s, int __flag, size_t __slen,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int __vsprintf_chk (char *__restrict __s, int __flag, size_t __slen,
      const char *__restrict __format,
      __gnuc_va_list __ap) __attribute__ ((__nothrow__ , __leaf__));


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) sprintf (char *__restrict __s, const char *__restrict __fmt, ...)
{
  return __builtin___sprintf_chk (__s, 2 - 1,
      __builtin_object_size (__s, 2 > 1), __fmt, __builtin_va_arg_pack ());
}






extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) vsprintf (char *__restrict __s, const char *__restrict __fmt, __gnuc_va_list __ap)

{
  return __builtin___vsprintf_chk (__s, 2 - 1,
       __builtin_object_size (__s, 2 > 1), __fmt, __ap);
}



extern int __snprintf_chk (char *__restrict __s, size_t __n, int __flag,
      size_t __slen, const char *__restrict __format,
      ...) __attribute__ ((__nothrow__ , __leaf__));
extern int __vsnprintf_chk (char *__restrict __s, size_t __n, int __flag,
       size_t __slen, const char *__restrict __format,
       __gnuc_va_list __ap) __attribute__ ((__nothrow__ , __leaf__));


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) snprintf (char *__restrict __s, size_t __n, const char *__restrict __fmt, ...)

{
  return __builtin___snprintf_chk (__s, __n, 2 - 1,
       __builtin_object_size (__s, 2 > 1), __fmt, __builtin_va_arg_pack ());
}






extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) vsnprintf (char *__restrict __s, size_t __n, const char *__restrict __fmt, __gnuc_va_list __ap)

{
  return __builtin___vsnprintf_chk (__s, __n, 2 - 1,
        __builtin_object_size (__s, 2 > 1), __fmt, __ap);
}





extern int __fprintf_chk (FILE *__restrict __stream, int __flag,
     const char *__restrict __format, ...);
extern int __printf_chk (int __flag, const char *__restrict __format, ...);
extern int __vfprintf_chk (FILE *__restrict __stream, int __flag,
      const char *__restrict __format, __gnuc_va_list __ap);
extern int __vprintf_chk (int __flag, const char *__restrict __format,
     __gnuc_va_list __ap);


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
fprintf (FILE *__restrict __stream, const char *__restrict __fmt, ...)
{
  return __fprintf_chk (__stream, 2 - 1, __fmt,
   __builtin_va_arg_pack ());
}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
printf (const char *__restrict __fmt, ...)
{
  return __printf_chk (2 - 1, __fmt, __builtin_va_arg_pack ());
}







extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
vprintf (const char *__restrict __fmt, __gnuc_va_list __ap)
{

  return __vfprintf_chk (stdout, 2 - 1, __fmt, __ap);



}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
vfprintf (FILE *__restrict __stream,
   const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __vfprintf_chk (__stream, 2 - 1, __fmt, __ap);
}


extern int __dprintf_chk (int __fd, int __flag, const char *__restrict __fmt,
     ...) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int __vdprintf_chk (int __fd, int __flag,
      const char *__restrict __fmt, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 3, 0)));


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
dprintf (int __fd, const char *__restrict __fmt, ...)
{
  return __dprintf_chk (__fd, 2 - 1, __fmt,
   __builtin_va_arg_pack ());
}





extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
vdprintf (int __fd, const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __vdprintf_chk (__fd, 2 - 1, __fmt, __ap);
}




extern int __asprintf_chk (char **__restrict __ptr, int __flag,
      const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__printf__, 3, 4))) __attribute__ ((__warn_unused_result__));
extern int __vasprintf_chk (char **__restrict __ptr, int __flag,
       const char *__restrict __fmt, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__printf__, 3, 0))) __attribute__ ((__warn_unused_result__));
extern int __obstack_printf_chk (struct obstack *__restrict __obstack,
     int __flag, const char *__restrict __format,
     ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int __obstack_vprintf_chk (struct obstack *__restrict __obstack,
      int __flag,
      const char *__restrict __format,
      __gnuc_va_list __args)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__printf__, 3, 0)));


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) asprintf (char **__restrict __ptr, const char *__restrict __fmt, ...)
{
  return __asprintf_chk (__ptr, 2 - 1, __fmt,
    __builtin_va_arg_pack ());
}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) __asprintf (char **__restrict __ptr, const char *__restrict __fmt, ...)

{
  return __asprintf_chk (__ptr, 2 - 1, __fmt,
    __builtin_va_arg_pack ());
}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) obstack_printf (struct obstack *__restrict __obstack, const char *__restrict __fmt, ...)

{
  return __obstack_printf_chk (__obstack, 2 - 1, __fmt,
          __builtin_va_arg_pack ());
}
extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) vasprintf (char **__restrict __ptr, const char *__restrict __fmt, __gnuc_va_list __ap)

{
  return __vasprintf_chk (__ptr, 2 - 1, __fmt, __ap);
}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) obstack_vprintf (struct obstack *__restrict __obstack, const char *__restrict __fmt, __gnuc_va_list __ap)

{
  return __obstack_vprintf_chk (__obstack, 2 - 1, __fmt,
    __ap);
}
extern char *__fgets_chk (char *__restrict __s, size_t __size, int __n,
     FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern char *__fgets_alias (char *__restrict __s, int __n, FILE *__restrict __stream) __asm__ ("" "fgets")

                                        __attribute__ ((__warn_unused_result__));
extern char *__fgets_chk_warn (char *__restrict __s, size_t __size, int __n, FILE *__restrict __stream) __asm__ ("" "__fgets_chk")


     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("fgets called with bigger size than length " "of destination buffer")))
                                 ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) char *
fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
{
  if (__builtin_object_size (__s, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__n) || __n <= 0)
 return __fgets_chk (__s, __builtin_object_size (__s, 2 > 1), __n, __stream);

      if ((size_t) __n > __builtin_object_size (__s, 2 > 1))
 return __fgets_chk_warn (__s, __builtin_object_size (__s, 2 > 1), __n, __stream);
    }
  return __fgets_alias (__s, __n, __stream);
}

extern size_t __fread_chk (void *__restrict __ptr, size_t __ptrlen,
      size_t __size, size_t __n,
      FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern size_t __fread_alias (void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __asm__ ("" "fread")


            __attribute__ ((__warn_unused_result__));
extern size_t __fread_chk_warn (void *__restrict __ptr, size_t __ptrlen, size_t __size, size_t __n, FILE *__restrict __stream) __asm__ ("" "__fread_chk")




     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("fread called with bigger size * nmemb than length " "of destination buffer")))
                                 ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) size_t
fread (void *__restrict __ptr, size_t __size, size_t __n,
       FILE *__restrict __stream)
{
  if (__builtin_object_size (__ptr, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__size)
   || !__builtin_constant_p (__n)
   || (__size | __n) >= (((size_t) 1) << (8 * sizeof (size_t) / 2)))
 return __fread_chk (__ptr, __builtin_object_size (__ptr, 0), __size, __n, __stream);

      if (__size * __n > __builtin_object_size (__ptr, 0))
 return __fread_chk_warn (__ptr, __builtin_object_size (__ptr, 0), __size, __n, __stream);
    }
  return __fread_alias (__ptr, __size, __n, __stream);
}


extern char *__fgets_unlocked_chk (char *__restrict __s, size_t __size,
       int __n, FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern char *__fgets_unlocked_alias (char *__restrict __s, int __n, FILE *__restrict __stream) __asm__ ("" "fgets_unlocked")

                                                 __attribute__ ((__warn_unused_result__));
extern char *__fgets_unlocked_chk_warn (char *__restrict __s, size_t __size, int __n, FILE *__restrict __stream) __asm__ ("" "__fgets_unlocked_chk")


     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("fgets_unlocked called with bigger size than length " "of destination buffer")))
                                 ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) char *
fgets_unlocked (char *__restrict __s, int __n, FILE *__restrict __stream)
{
  if (__builtin_object_size (__s, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__n) || __n <= 0)
 return __fgets_unlocked_chk (__s, __builtin_object_size (__s, 2 > 1), __n, __stream);

      if ((size_t) __n > __builtin_object_size (__s, 2 > 1))
 return __fgets_unlocked_chk_warn (__s, __builtin_object_size (__s, 2 > 1), __n, __stream);
    }
  return __fgets_unlocked_alias (__s, __n, __stream);
}




extern size_t __fread_unlocked_chk (void *__restrict __ptr, size_t __ptrlen,
        size_t __size, size_t __n,
        FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern size_t __fread_unlocked_alias (void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __asm__ ("" "fread_unlocked")


                     __attribute__ ((__warn_unused_result__));
extern size_t __fread_unlocked_chk_warn (void *__restrict __ptr, size_t __ptrlen, size_t __size, size_t __n, FILE *__restrict __stream) __asm__ ("" "__fread_unlocked_chk")




     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("fread_unlocked called with bigger size * nmemb than " "length of destination buffer")))
                                        ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) size_t
fread_unlocked (void *__restrict __ptr, size_t __size, size_t __n,
  FILE *__restrict __stream)
{
  if (__builtin_object_size (__ptr, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__size)
   || !__builtin_constant_p (__n)
   || (__size | __n) >= (((size_t) 1) << (8 * sizeof (size_t) / 2)))
 return __fread_unlocked_chk (__ptr, __builtin_object_size (__ptr, 0), __size, __n,
         __stream);

      if (__size * __n > __builtin_object_size (__ptr, 0))
 return __fread_unlocked_chk_warn (__ptr, __builtin_object_size (__ptr, 0), __size, __n,
       __stream);
    }


  if (__builtin_constant_p (__size)
      && __builtin_constant_p (__n)
      && (__size | __n) < (((size_t) 1) << (8 * sizeof (size_t) / 2))
      && __size * __n <= 8)
    {
      size_t __cnt = __size * __n;
      char *__cptr = (char *) __ptr;
      if (__cnt == 0)
 return 0;

      for (; __cnt > 0; --__cnt)
 {
   int __c = (__builtin_expect (((__stream)->_IO_read_ptr >= (__stream)->_IO_read_end), 0) ? __uflow (__stream) : *(unsigned char *) (__stream)->_IO_read_ptr++);
   if (__c == (-1))
     break;
   *__cptr++ = __c;
 }
      return (__cptr - (char *) __ptr) / __size;
    }

  return __fread_unlocked_alias (__ptr, __size, __n, __stream);
}






typedef long int wchar_t;








typedef enum
{
  P_ALL,
  P_PID,
  P_PGID
} idtype_t;


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;







__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;


extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));

extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));

extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));





__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));





extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long int strtol_l (const char *__restrict __nptr,
     char **__restrict __endptr, int __base,
     __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));

extern unsigned long int strtoul_l (const char *__restrict __nptr,
        char **__restrict __endptr,
        int __base, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));

__extension__
extern long long int strtoll_l (const char *__restrict __nptr,
    char **__restrict __endptr, int __base,
    __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));

__extension__
extern unsigned long long int strtoull_l (const char *__restrict __nptr,
       char **__restrict __endptr,
       int __base, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));

extern double strtod_l (const char *__restrict __nptr,
   char **__restrict __endptr, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));

extern float strtof_l (const char *__restrict __nptr,
         char **__restrict __endptr, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));

extern long double strtold_l (const char *__restrict __nptr,
         char **__restrict __endptr,
         __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));





extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) atoi (const char *__nptr)
{
  return (int) strtol (__nptr, (char **) ((void *)0), 10);
}
extern __inline __attribute__ ((__gnu_inline__)) long int
__attribute__ ((__nothrow__ , __leaf__)) atol (const char *__nptr)
{
  return strtol (__nptr, (char **) ((void *)0), 10);
}




__extension__ extern __inline __attribute__ ((__gnu_inline__)) long long int
__attribute__ ((__nothrow__ , __leaf__)) atoll (const char *__nptr)
{
  return strtoll (__nptr, (char **) ((void *)0), 10);
}

extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));


extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));










typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;






typedef __ino64_t ino64_t;




typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;
typedef __id_t id_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
typedef __useconds_t useconds_t;



typedef __suseconds_t suseconds_t;








typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));


typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;



typedef __sigset_t sigset_t;
typedef long int __fd_mask;
typedef struct
  {



    __fd_mask fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];





  } fd_set;






typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);





extern long int __fdelt_chk (long int __d);
extern long int __fdelt_warn (long int __d)
  __attribute__((__warning__ ("bit outside of fd_set selected")));







__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


__extension__ extern __inline __attribute__ ((__gnu_inline__)) __attribute__ ((__const__)) unsigned int
__attribute__ ((__nothrow__ , __leaf__)) gnu_dev_major (unsigned long long int __dev)
{
  return ((__dev >> 8) & 0xfff) | ((unsigned int) (__dev >> 32) & ~0xfff);
}

__extension__ extern __inline __attribute__ ((__gnu_inline__)) __attribute__ ((__const__)) unsigned int
__attribute__ ((__nothrow__ , __leaf__)) gnu_dev_minor (unsigned long long int __dev)
{
  return (__dev & 0xff) | ((unsigned int) (__dev >> 12) & ~0xff);
}

__extension__ extern __inline __attribute__ ((__gnu_inline__)) __attribute__ ((__const__)) unsigned long long int
__attribute__ ((__nothrow__ , __leaf__)) gnu_dev_makedev (unsigned int __major, unsigned int __minor)
{
  return ((__minor & 0xff) | ((__major & 0xfff) << 8)
   | (((unsigned long long int) (__minor & ~0xff)) << 12)
   | (((unsigned long long int) (__major & ~0xfff)) << 32));
}







typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;







extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));






extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));




extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));









extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__warn_unused_result__));

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__warn_unused_result__));










extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));

extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));




extern void cfree (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));










extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));











extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__warn_unused_result__));




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));




extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (2))) __attribute__ ((__warn_unused_result__));




extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));







extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));






extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));





extern char *secure_getenv (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));






extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int mkstemp64 (char *__template) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int mkstemps64 (char *__template, int __suffixlen)
     __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int mkostemp (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int mkostemp64 (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int mkostemps (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));









extern int system (const char *__command) __attribute__ ((__warn_unused_result__));






extern char *canonicalize_file_name (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));






typedef int (*__compar_fn_t) (const void *, const void *);


typedef __compar_fn_t comparison_fn_t;



typedef int (*__compar_d_fn_t) (const void *, const void *, void *);





extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) __attribute__ ((__warn_unused_result__));


extern __inline __attribute__ ((__gnu_inline__)) void *
bsearch (const void *__key, const void *__base, size_t __nmemb, size_t __size,
  __compar_fn_t __compar)
{
  size_t __l, __u, __idx;
  const void *__p;
  int __comparison;

  __l = 0;
  __u = __nmemb;
  while (__l < __u)
    {
      __idx = (__l + __u) / 2;
      __p = (void *) (((const char *) __base) + (__idx * __size));
      __comparison = (*__compar) (__key, __p);
      if (__comparison < 0)
 __u = __idx;
      else if (__comparison > 0)
 __l = __idx + 1;
      else
 return (void *) __p;
    }

  return ((void *)0);
}




extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));

extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
       __compar_d_fn_t __compar, void *__arg)
  __attribute__ ((__nonnull__ (1, 4)));




extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) __attribute__ ((__warn_unused_result__));
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) __attribute__ ((__warn_unused_result__));



__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) __attribute__ ((__warn_unused_result__));







extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) __attribute__ ((__warn_unused_result__));
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) __attribute__ ((__warn_unused_result__));




__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) __attribute__ ((__warn_unused_result__));

extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) __attribute__ ((__warn_unused_result__));




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) __attribute__ ((__warn_unused_result__));




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) __attribute__ ((__warn_unused_result__));




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) __attribute__ ((__warn_unused_result__));
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) __attribute__ ((__warn_unused_result__));
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) __attribute__ ((__warn_unused_result__));




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));






extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));

extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));








extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) __attribute__ ((__warn_unused_result__));





extern void setkey (const char *__key) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int posix_openpt (int __oflag) __attribute__ ((__warn_unused_result__));







extern int grantpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));



extern int unlockpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));




extern char *ptsname (int __fd) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));






extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int getpt (void);






extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern __inline __attribute__ ((__gnu_inline__)) double
__attribute__ ((__nothrow__ , __leaf__)) atof (const char *__nptr)
{
  return strtod (__nptr, (char **) ((void *)0));
}




extern char *__realpath_chk (const char *__restrict __name,
        char *__restrict __resolved,
        size_t __resolvedlen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern char *__realpath_alias (const char *__restrict __name, char *__restrict __resolved) __asm__ ("" "realpath") __attribute__ ((__nothrow__ , __leaf__))

                                                 __attribute__ ((__warn_unused_result__));
extern char *__realpath_chk_warn (const char *__restrict __name, char *__restrict __resolved, size_t __resolvedlen) __asm__ ("" "__realpath_chk") __attribute__ ((__nothrow__ , __leaf__))


                                                __attribute__ ((__warn_unused_result__))
     __attribute__((__warning__ ("second argument of realpath must be either NULL or at " "least PATH_MAX bytes long buffer")))
                                      ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) char *
__attribute__ ((__nothrow__ , __leaf__)) realpath (const char *__restrict __name, char *__restrict __resolved)
{
  if (__builtin_object_size (__resolved, 2 > 1) != (size_t) -1)
    {




      return __realpath_chk (__name, __resolved, __builtin_object_size (__resolved, 2 > 1));
    }

  return __realpath_alias (__name, __resolved);
}


extern int __ptsname_r_chk (int __fd, char *__buf, size_t __buflen,
       size_t __nreal) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int __ptsname_r_alias (int __fd, char *__buf, size_t __buflen) __asm__ ("" "ptsname_r") __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__nonnull__ (2)));
extern int __ptsname_r_chk_warn (int __fd, char *__buf, size_t __buflen, size_t __nreal) __asm__ ("" "__ptsname_r_chk") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (2))) __attribute__((__warning__ ("ptsname_r called with buflen bigger than " "size of buf")))
                   ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) ptsname_r (int __fd, char *__buf, size_t __buflen)
{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__buflen))
 return __ptsname_r_chk (__fd, __buf, __buflen, __builtin_object_size (__buf, 2 > 1));
      if (__buflen > __builtin_object_size (__buf, 2 > 1))
 return __ptsname_r_chk_warn (__fd, __buf, __buflen, __builtin_object_size (__buf, 2 > 1));
    }
  return __ptsname_r_alias (__fd, __buf, __buflen);
}


extern int __wctomb_chk (char *__s, wchar_t __wchar, size_t __buflen)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern int __wctomb_alias (char *__s, wchar_t __wchar) __asm__ ("" "wctomb") __attribute__ ((__nothrow__ , __leaf__))
              __attribute__ ((__warn_unused_result__));

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) int
__attribute__ ((__nothrow__ , __leaf__)) wctomb (char *__s, wchar_t __wchar)
{







  if (__builtin_object_size (__s, 2 > 1) != (size_t) -1 && 16 > __builtin_object_size (__s, 2 > 1))
    return __wctomb_chk (__s, __wchar, __builtin_object_size (__s, 2 > 1));
  return __wctomb_alias (__s, __wchar);
}


extern size_t __mbstowcs_chk (wchar_t *__restrict __dst,
         const char *__restrict __src,
         size_t __len, size_t __dstlen) __attribute__ ((__nothrow__ , __leaf__));
extern size_t __mbstowcs_alias (wchar_t *__restrict __dst, const char *__restrict __src, size_t __len) __asm__ ("" "mbstowcs") __attribute__ ((__nothrow__ , __leaf__))


                                  ;
extern size_t __mbstowcs_chk_warn (wchar_t *__restrict __dst, const char *__restrict __src, size_t __len, size_t __dstlen) __asm__ ("" "__mbstowcs_chk") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__((__warning__ ("mbstowcs called with dst buffer smaller than len " "* sizeof (wchar_t)")))
                        ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) size_t
__attribute__ ((__nothrow__ , __leaf__)) mbstowcs (wchar_t *__restrict __dst, const char *__restrict __src, size_t __len)

{
  if (__builtin_object_size (__dst, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__len))
 return __mbstowcs_chk (__dst, __src, __len,
          __builtin_object_size (__dst, 2 > 1) / sizeof (wchar_t));

      if (__len > __builtin_object_size (__dst, 2 > 1) / sizeof (wchar_t))
 return __mbstowcs_chk_warn (__dst, __src, __len,
         __builtin_object_size (__dst, 2 > 1) / sizeof (wchar_t));
    }
  return __mbstowcs_alias (__dst, __src, __len);
}


extern size_t __wcstombs_chk (char *__restrict __dst,
         const wchar_t *__restrict __src,
         size_t __len, size_t __dstlen) __attribute__ ((__nothrow__ , __leaf__));
extern size_t __wcstombs_alias (char *__restrict __dst, const wchar_t *__restrict __src, size_t __len) __asm__ ("" "wcstombs") __attribute__ ((__nothrow__ , __leaf__))


                                  ;
extern size_t __wcstombs_chk_warn (char *__restrict __dst, const wchar_t *__restrict __src, size_t __len, size_t __dstlen) __asm__ ("" "__wcstombs_chk") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__((__warning__ ("wcstombs called with dst buffer smaller than len")));

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) size_t
__attribute__ ((__nothrow__ , __leaf__)) wcstombs (char *__restrict __dst, const wchar_t *__restrict __src, size_t __len)

{
  if (__builtin_object_size (__dst, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__len))
 return __wcstombs_chk (__dst, __src, __len, __builtin_object_size (__dst, 2 > 1));
      if (__len > __builtin_object_size (__dst, 2 > 1))
 return __wcstombs_chk_warn (__dst, __src, __len, __builtin_object_size (__dst, 2 > 1));
    }
  return __wcstombs_alias (__dst, __src, __len);
}
















extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));






extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


extern void *rawmemchr (const void *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern void *memrchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));






extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int strcoll_l (const char *__s1, const char *__s2, __locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    __locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));




extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));

extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


extern char *strchrnul (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));






extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strcasestr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));







extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)));



extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));

extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__warn_unused_result__));





extern char *strerror_l (int __errnum, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));





extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern void bcopy (const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));





extern int strcasecmp_l (const char *__s1, const char *__s2,
    __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));





extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int strverscmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strfry (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void *memfrob (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *basename (const char *__filename) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void *__rawmemchr (const void *__s, int __c);
extern __inline __attribute__ ((__gnu_inline__)) char *__strtok_r_1c (char *__s, char __sep, char **__nextp);
extern __inline __attribute__ ((__gnu_inline__)) char *
__strtok_r_1c (char *__s, char __sep, char **__nextp)
{
  char *__result;
  if (__s == ((void *)0))
    __s = *__nextp;
  while (*__s == __sep)
    ++__s;
  __result = ((void *)0);
  if (*__s != '\0')
    {
      __result = __s++;
      while (*__s != '\0')
 if (*__s++ == __sep)
   {
     __s[-1] = '\0';
     break;
   }
    }
  *__nextp = __s;
  return __result;
}
extern char *__strsep_g (char **__stringp, const char *__delim);
extern __inline __attribute__ ((__gnu_inline__)) char *__strsep_1c (char **__s, char __reject);
extern __inline __attribute__ ((__gnu_inline__)) char *
__strsep_1c (char **__s, char __reject)
{
  char *__retval = *__s;
  if (__retval != ((void *)0) && (*__s = (__extension__ (__builtin_constant_p (__reject) && !__builtin_constant_p (__retval) && (__reject) == '\0' ? (char *) __rawmemchr (__retval, __reject) : __builtin_strchr (__retval, __reject)))) != ((void *)0))
    *(*__s)++ = '\0';
  return __retval;
}

extern __inline __attribute__ ((__gnu_inline__)) char *__strsep_2c (char **__s, char __reject1, char __reject2);
extern __inline __attribute__ ((__gnu_inline__)) char *
__strsep_2c (char **__s, char __reject1, char __reject2)
{
  char *__retval = *__s;
  if (__retval != ((void *)0))
    {
      char *__cp = __retval;
      while (1)
 {
   if (*__cp == '\0')
     {
       __cp = ((void *)0);
   break;
     }
   if (*__cp == __reject1 || *__cp == __reject2)
     {
       *__cp++ = '\0';
       break;
     }
   ++__cp;
 }
      *__s = __cp;
    }
  return __retval;
}

extern __inline __attribute__ ((__gnu_inline__)) char *__strsep_3c (char **__s, char __reject1, char __reject2,
       char __reject3);
extern __inline __attribute__ ((__gnu_inline__)) char *
__strsep_3c (char **__s, char __reject1, char __reject2, char __reject3)
{
  char *__retval = *__s;
  if (__retval != ((void *)0))
    {
      char *__cp = __retval;
      while (1)
 {
   if (*__cp == '\0')
     {
       __cp = ((void *)0);
   break;
     }
   if (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
     {
       *__cp++ = '\0';
       break;
     }
   ++__cp;
 }
      *__s = __cp;
    }
  return __retval;
}
extern char *__strdup (const char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__));
extern char *__strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__));




extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) void *
__attribute__ ((__nothrow__ , __leaf__)) memcpy (void *__restrict __dest, const void *__restrict __src, size_t __len)

{
  return __builtin___memcpy_chk (__dest, __src, __len, __builtin_object_size (__dest, 0));
}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) void *
__attribute__ ((__nothrow__ , __leaf__)) memmove (void *__dest, const void *__src, size_t __len)
{
  return __builtin___memmove_chk (__dest, __src, __len, __builtin_object_size (__dest, 0));
}


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) void *
__attribute__ ((__nothrow__ , __leaf__)) mempcpy (void *__restrict __dest, const void *__restrict __src, size_t __len)

{
  return __builtin___mempcpy_chk (__dest, __src, __len, __builtin_object_size (__dest, 0));
}
extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) void *
__attribute__ ((__nothrow__ , __leaf__)) memset (void *__dest, int __ch, size_t __len)
{
  return __builtin___memset_chk (__dest, __ch, __len, __builtin_object_size (__dest, 0));
}


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) void
__attribute__ ((__nothrow__ , __leaf__)) bcopy (const void *__src, void *__dest, size_t __len)
{
  (void) __builtin___memmove_chk (__dest, __src, __len, __builtin_object_size (__dest, 0));
}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) void
__attribute__ ((__nothrow__ , __leaf__)) bzero (void *__dest, size_t __len)
{
  (void) __builtin___memset_chk (__dest, '\0', __len, __builtin_object_size (__dest, 0));
}


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) char *
__attribute__ ((__nothrow__ , __leaf__)) strcpy (char *__restrict __dest, const char *__restrict __src)
{
  return __builtin___strcpy_chk (__dest, __src, __builtin_object_size (__dest, 2 > 1));
}


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) char *
__attribute__ ((__nothrow__ , __leaf__)) stpcpy (char *__restrict __dest, const char *__restrict __src)
{
  return __builtin___stpcpy_chk (__dest, __src, __builtin_object_size (__dest, 2 > 1));
}



extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) char *
__attribute__ ((__nothrow__ , __leaf__)) strncpy (char *__restrict __dest, const char *__restrict __src, size_t __len)

{
  return __builtin___strncpy_chk (__dest, __src, __len, __builtin_object_size (__dest, 2 > 1));
}


extern char *__stpncpy_chk (char *__dest, const char *__src, size_t __n,
       size_t __destlen) __attribute__ ((__nothrow__ , __leaf__));
extern char *__stpncpy_alias (char *__dest, const char *__src, size_t __n) __asm__ ("" "stpncpy") __attribute__ ((__nothrow__ , __leaf__))
                                 ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) char *
__attribute__ ((__nothrow__ , __leaf__)) stpncpy (char *__dest, const char *__src, size_t __n)
{
  if (__builtin_object_size (__dest, 2 > 1) != (size_t) -1
      && (!__builtin_constant_p (__n) || __n > __builtin_object_size (__dest, 2 > 1)))
    return __stpncpy_chk (__dest, __src, __n, __builtin_object_size (__dest, 2 > 1));
  return __stpncpy_alias (__dest, __src, __n);
}


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) char *
__attribute__ ((__nothrow__ , __leaf__)) strcat (char *__restrict __dest, const char *__restrict __src)
{
  return __builtin___strcat_chk (__dest, __src, __builtin_object_size (__dest, 2 > 1));
}


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) char *
__attribute__ ((__nothrow__ , __leaf__)) strncat (char *__restrict __dest, const char *__restrict __src, size_t __len)

{
  return __builtin___strncat_chk (__dest, __src, __len, __builtin_object_size (__dest, 2 > 1));
}





typedef __socklen_t socklen_t;
extern int access (const char *__name, int __type) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int euidaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int eaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__warn_unused_result__));
extern __off_t lseek (int __fd, __off_t __offset, int __whence) __attribute__ ((__nothrow__ , __leaf__));
extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     __attribute__ ((__nothrow__ , __leaf__));






extern int close (int __fd);






extern ssize_t read (int __fd, void *__buf, size_t __nbytes) __attribute__ ((__warn_unused_result__));





extern ssize_t write (int __fd, const void *__buf, size_t __n) __attribute__ ((__warn_unused_result__));
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
        __off_t __offset) __attribute__ ((__warn_unused_result__));






extern ssize_t pwrite (int __fd, const void *__buf, size_t __n,
         __off_t __offset) __attribute__ ((__warn_unused_result__));
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
   __off64_t __offset) __attribute__ ((__warn_unused_result__));


extern ssize_t pwrite64 (int __fd, const void *__buf, size_t __n,
    __off64_t __offset) __attribute__ ((__warn_unused_result__));







extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern int pipe2 (int __pipedes[2], int __flags) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned int sleep (unsigned int __seconds);







extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__ , __leaf__));






extern int usleep (__useconds_t __useconds);
extern int pause (void);



extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));






extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__warn_unused_result__));



extern int chdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));



extern int fchdir (int __fd) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));





extern char *get_current_dir_name (void) __attribute__ ((__nothrow__ , __leaf__));







extern char *getwd (char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__)) __attribute__ ((__warn_unused_result__));




extern int dup (int __fd) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));


extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__ , __leaf__));




extern int dup3 (int __fd, int __fd2, int __flags) __attribute__ ((__nothrow__ , __leaf__));



extern char **__environ;

extern char **environ;





extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




extern int execv (const char *__path, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execle (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execl (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execvp (const char *__file, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int execlp (const char *__file, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int execvpe (const char *__file, char *const __argv[],
      char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern int nice (int __inc) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern void _exit (int __status) __attribute__ ((__noreturn__));





enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX,

    _PC_2_SYMLINKS

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG,


    _SC_LEVEL1_ICACHE_SIZE,

    _SC_LEVEL1_ICACHE_ASSOC,

    _SC_LEVEL1_ICACHE_LINESIZE,

    _SC_LEVEL1_DCACHE_SIZE,

    _SC_LEVEL1_DCACHE_ASSOC,

    _SC_LEVEL1_DCACHE_LINESIZE,

    _SC_LEVEL2_CACHE_SIZE,

    _SC_LEVEL2_CACHE_ASSOC,

    _SC_LEVEL2_CACHE_LINESIZE,

    _SC_LEVEL3_CACHE_SIZE,

    _SC_LEVEL3_CACHE_ASSOC,

    _SC_LEVEL3_CACHE_LINESIZE,

    _SC_LEVEL4_CACHE_SIZE,

    _SC_LEVEL4_CACHE_ASSOC,

    _SC_LEVEL4_CACHE_LINESIZE,



    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,

    _SC_RAW_SOCKETS,


    _SC_V7_ILP32_OFF32,

    _SC_V7_ILP32_OFFBIG,

    _SC_V7_LP64_OFF64,

    _SC_V7_LPBIG_OFFBIG,


    _SC_SS_REPL_MAX,


    _SC_TRACE_EVENT_NAME_MAX,

    _SC_TRACE_NAME_MAX,

    _SC_TRACE_SYS_MAX,

    _SC_TRACE_USER_EVENT_MAX,


    _SC_XOPEN_STREAMS,


    _SC_THREAD_ROBUST_PRIO_INHERIT,

    _SC_THREAD_ROBUST_PRIO_PROTECT

  };


enum
  {
    _CS_PATH,


    _CS_V6_WIDTH_RESTRICTED_ENVS,



    _CS_GNU_LIBC_VERSION,

    _CS_GNU_LIBPTHREAD_VERSION,


    _CS_V5_WIDTH_RESTRICTED_ENVS,



    _CS_V7_WIDTH_RESTRICTED_ENVS,



    _CS_LFS_CFLAGS = 1000,

    _CS_LFS_LDFLAGS,

    _CS_LFS_LIBS,

    _CS_LFS_LINTFLAGS,

    _CS_LFS64_CFLAGS,

    _CS_LFS64_LDFLAGS,

    _CS_LFS64_LIBS,

    _CS_LFS64_LINTFLAGS,


    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

    _CS_XBS5_ILP32_OFF32_LDFLAGS,

    _CS_XBS5_ILP32_OFF32_LIBS,

    _CS_XBS5_ILP32_OFF32_LINTFLAGS,

    _CS_XBS5_ILP32_OFFBIG_CFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LIBS,

    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

    _CS_XBS5_LP64_OFF64_CFLAGS,

    _CS_XBS5_LP64_OFF64_LDFLAGS,

    _CS_XBS5_LP64_OFF64_LIBS,

    _CS_XBS5_LP64_OFF64_LINTFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LIBS,

    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LIBS,

    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_LP64_OFF64_CFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LIBS,

    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LIBS,

    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V7_LP64_OFF64_CFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LIBS,

    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,


    _CS_V6_ENV,

    _CS_V7_ENV

  };


extern long int pathconf (const char *__path, int __name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__ , __leaf__));


extern long int sysconf (int __name) __attribute__ ((__nothrow__ , __leaf__));



extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__ , __leaf__));




extern __pid_t getpid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t getppid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t getpgrp (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));

extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));






extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgrp (void) __attribute__ ((__nothrow__ , __leaf__));






extern __pid_t setsid (void) __attribute__ ((__nothrow__ , __leaf__));



extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));



extern __uid_t getuid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __uid_t geteuid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __gid_t getgid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __gid_t getegid (void) __attribute__ ((__nothrow__ , __leaf__));




extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));



extern int group_member (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__));






extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));






extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));





extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     __attribute__ ((__nothrow__ , __leaf__));



extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     __attribute__ ((__nothrow__ , __leaf__));



extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));



extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));






extern __pid_t fork (void) __attribute__ ((__nothrow__));







extern __pid_t vfork (void) __attribute__ ((__nothrow__ , __leaf__));





extern char *ttyname (int __fd) __attribute__ ((__nothrow__ , __leaf__));



extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__warn_unused_result__));



extern int isatty (int __fd) __attribute__ ((__nothrow__ , __leaf__));




extern int ttyslot (void) __attribute__ ((__nothrow__ , __leaf__));




extern int link (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__warn_unused_result__));




extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4))) __attribute__ ((__warn_unused_result__));




extern int symlink (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__warn_unused_result__));




extern ssize_t readlink (const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__warn_unused_result__));




extern int symlinkat (const char *__from, int __tofd,
        const char *__to) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3))) __attribute__ ((__warn_unused_result__));


extern ssize_t readlinkat (int __fd, const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3))) __attribute__ ((__warn_unused_result__));



extern int unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int unlinkat (int __fd, const char *__name, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern int rmdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__ , __leaf__));


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__ , __leaf__));






extern char *getlogin (void);







extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)));




extern int setlogin (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *optarg;
extern int optind;




extern int opterr;



extern int optopt;
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__ , __leaf__));







extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int sethostname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));



extern int sethostid (long int __id) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));





extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int setdomainname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));





extern int vhangup (void) __attribute__ ((__nothrow__ , __leaf__));


extern int revoke (const char *__file) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));







extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int acct (const char *__name) __attribute__ ((__nothrow__ , __leaf__));



extern char *getusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void endusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void setusershell (void) __attribute__ ((__nothrow__ , __leaf__));





extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));






extern int chroot (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));



extern char *getpass (const char *__prompt) __attribute__ ((__nonnull__ (1)));







extern int fsync (int __fd);





extern int syncfs (int __fd) __attribute__ ((__nothrow__ , __leaf__));






extern long int gethostid (void);


extern void sync (void) __attribute__ ((__nothrow__ , __leaf__));





extern int getpagesize (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int getdtablesize (void) __attribute__ ((__nothrow__ , __leaf__));
extern int truncate (const char *__file, __off_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int truncate64 (const char *__file, __off64_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int ftruncate (int __fd, __off_t __length) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern int ftruncate64 (int __fd, __off64_t __length) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern int brk (void *__addr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));





extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__ , __leaf__));
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int lockf (int __fd, int __cmd, __off_t __len) __attribute__ ((__warn_unused_result__));
extern int lockf64 (int __fd, int __cmd, __off64_t __len) __attribute__ ((__warn_unused_result__));
extern int fdatasync (int __fildes);







extern char *crypt (const char *__key, const char *__salt)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern void encrypt (char *__glibc_block, int __edflag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern void swab (const void *__restrict __from, void *__restrict __to,
    ssize_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern ssize_t __read_chk (int __fd, void *__buf, size_t __nbytes,
      size_t __buflen) __attribute__ ((__warn_unused_result__));
extern ssize_t __read_alias (int __fd, void *__buf, size_t __nbytes) __asm__ ("" "read")
                               __attribute__ ((__warn_unused_result__));
extern ssize_t __read_chk_warn (int __fd, void *__buf, size_t __nbytes, size_t __buflen) __asm__ ("" "__read_chk")


     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("read called with bigger length than size of " "the destination buffer")))
                                  ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) ssize_t
read (int __fd, void *__buf, size_t __nbytes)
{
  if (__builtin_object_size (__buf, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__nbytes))
 return __read_chk (__fd, __buf, __nbytes, __builtin_object_size (__buf, 0));

      if (__nbytes > __builtin_object_size (__buf, 0))
 return __read_chk_warn (__fd, __buf, __nbytes, __builtin_object_size (__buf, 0));
    }
  return __read_alias (__fd, __buf, __nbytes);
}


extern ssize_t __pread_chk (int __fd, void *__buf, size_t __nbytes,
       __off_t __offset, size_t __bufsize) __attribute__ ((__warn_unused_result__));
extern ssize_t __pread64_chk (int __fd, void *__buf, size_t __nbytes,
         __off64_t __offset, size_t __bufsize) __attribute__ ((__warn_unused_result__));
extern ssize_t __pread_alias (int __fd, void *__buf, size_t __nbytes, __off_t __offset) __asm__ ("" "pread")

                                 __attribute__ ((__warn_unused_result__));
extern ssize_t __pread64_alias (int __fd, void *__buf, size_t __nbytes, __off64_t __offset) __asm__ ("" "pread64")

                                     __attribute__ ((__warn_unused_result__));
extern ssize_t __pread_chk_warn (int __fd, void *__buf, size_t __nbytes, __off_t __offset, size_t __bufsize) __asm__ ("" "__pread_chk")


     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("pread called with bigger length than size of " "the destination buffer")))
                                  ;
extern ssize_t __pread64_chk_warn (int __fd, void *__buf, size_t __nbytes, __off64_t __offset, size_t __bufsize) __asm__ ("" "__pread64_chk")



     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("pread64 called with bigger length than size of " "the destination buffer")))
                                  ;


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) ssize_t
pread (int __fd, void *__buf, size_t __nbytes, __off_t __offset)
{
  if (__builtin_object_size (__buf, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__nbytes))
 return __pread_chk (__fd, __buf, __nbytes, __offset, __builtin_object_size (__buf, 0));

      if ( __nbytes > __builtin_object_size (__buf, 0))
 return __pread_chk_warn (__fd, __buf, __nbytes, __offset,
     __builtin_object_size (__buf, 0));
    }
  return __pread_alias (__fd, __buf, __nbytes, __offset);
}
extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) ssize_t
pread64 (int __fd, void *__buf, size_t __nbytes, __off64_t __offset)
{
  if (__builtin_object_size (__buf, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__nbytes))
 return __pread64_chk (__fd, __buf, __nbytes, __offset, __builtin_object_size (__buf, 0));

      if ( __nbytes > __builtin_object_size (__buf, 0))
 return __pread64_chk_warn (__fd, __buf, __nbytes, __offset,
       __builtin_object_size (__buf, 0));
    }

  return __pread64_alias (__fd, __buf, __nbytes, __offset);
}




extern ssize_t __readlink_chk (const char *__restrict __path,
          char *__restrict __buf, size_t __len,
          size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__warn_unused_result__));
extern ssize_t __readlink_alias (const char *__restrict __path, char *__restrict __buf, size_t __len) __asm__ ("" "readlink") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__warn_unused_result__));
extern ssize_t __readlink_chk_warn (const char *__restrict __path, char *__restrict __buf, size_t __len, size_t __buflen) __asm__ ("" "__readlink_chk") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("readlink called with bigger length " "than size of destination buffer")))
                                         ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__warn_unused_result__)) ssize_t
__attribute__ ((__nothrow__ , __leaf__)) readlink (const char *__restrict __path, char *__restrict __buf, size_t __len)

{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__len))
 return __readlink_chk (__path, __buf, __len, __builtin_object_size (__buf, 2 > 1));

      if ( __len > __builtin_object_size (__buf, 2 > 1))
 return __readlink_chk_warn (__path, __buf, __len, __builtin_object_size (__buf, 2 > 1));
    }
  return __readlink_alias (__path, __buf, __len);
}



extern ssize_t __readlinkat_chk (int __fd, const char *__restrict __path,
     char *__restrict __buf, size_t __len,
     size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3))) __attribute__ ((__warn_unused_result__));
extern ssize_t __readlinkat_alias (int __fd, const char *__restrict __path, char *__restrict __buf, size_t __len) __asm__ ("" "readlinkat") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__nonnull__ (2, 3))) __attribute__ ((__warn_unused_result__));
extern ssize_t __readlinkat_chk_warn (int __fd, const char *__restrict __path, char *__restrict __buf, size_t __len, size_t __buflen) __asm__ ("" "__readlinkat_chk") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__nonnull__ (2, 3))) __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("readlinkat called with bigger " "length than size of destination " "buffer")))

                ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__nonnull__ (2, 3))) __attribute__ ((__warn_unused_result__)) ssize_t
__attribute__ ((__nothrow__ , __leaf__)) readlinkat (int __fd, const char *__restrict __path, char *__restrict __buf, size_t __len)

{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__len))
 return __readlinkat_chk (__fd, __path, __buf, __len, __builtin_object_size (__buf, 2 > 1));

      if (__len > __builtin_object_size (__buf, 2 > 1))
 return __readlinkat_chk_warn (__fd, __path, __buf, __len,
          __builtin_object_size (__buf, 2 > 1));
    }
  return __readlinkat_alias (__fd, __path, __buf, __len);
}


extern char *__getcwd_chk (char *__buf, size_t __size, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern char *__getcwd_alias (char *__buf, size_t __size) __asm__ ("" "getcwd") __attribute__ ((__nothrow__ , __leaf__))
                                              __attribute__ ((__warn_unused_result__));
extern char *__getcwd_chk_warn (char *__buf, size_t __size, size_t __buflen) __asm__ ("" "__getcwd_chk") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("getcwd caller with bigger length than size of " "destination buffer")))
                              ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) char *
__attribute__ ((__nothrow__ , __leaf__)) getcwd (char *__buf, size_t __size)
{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__size))
 return __getcwd_chk (__buf, __size, __builtin_object_size (__buf, 2 > 1));

      if (__size > __builtin_object_size (__buf, 2 > 1))
 return __getcwd_chk_warn (__buf, __size, __builtin_object_size (__buf, 2 > 1));
    }
  return __getcwd_alias (__buf, __size);
}


extern char *__getwd_chk (char *__buf, size_t buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern char *__getwd_warn (char *__buf) __asm__ ("" "getwd") __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("please use getcwd instead, as getwd " "doesn't specify buffer size")))
                                         ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__)) __attribute__ ((__warn_unused_result__)) char *
__attribute__ ((__nothrow__ , __leaf__)) getwd (char *__buf)
{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    return __getwd_chk (__buf, __builtin_object_size (__buf, 2 > 1));
  return __getwd_warn (__buf);
}


extern size_t __confstr_chk (int __name, char *__buf, size_t __len,
        size_t __buflen) __attribute__ ((__nothrow__ , __leaf__));
extern size_t __confstr_alias (int __name, char *__buf, size_t __len) __asm__ ("" "confstr") __attribute__ ((__nothrow__ , __leaf__))
                             ;
extern size_t __confstr_chk_warn (int __name, char *__buf, size_t __len, size_t __buflen) __asm__ ("" "__confstr_chk") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__((__warning__ ("confstr called with bigger length than size of destination " "buffer")))
            ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) size_t
__attribute__ ((__nothrow__ , __leaf__)) confstr (int __name, char *__buf, size_t __len)
{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__len))
 return __confstr_chk (__name, __buf, __len, __builtin_object_size (__buf, 2 > 1));

      if (__builtin_object_size (__buf, 2 > 1) < __len)
 return __confstr_chk_warn (__name, __buf, __len, __builtin_object_size (__buf, 2 > 1));
    }
  return __confstr_alias (__name, __buf, __len);
}


extern int __getgroups_chk (int __size, __gid_t __list[], size_t __listlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern int __getgroups_alias (int __size, __gid_t __list[]) __asm__ ("" "getgroups") __attribute__ ((__nothrow__ , __leaf__))
                 __attribute__ ((__warn_unused_result__));
extern int __getgroups_chk_warn (int __size, __gid_t __list[], size_t __listlen) __asm__ ("" "__getgroups_chk") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("getgroups called with bigger group count than what " "can fit into destination buffer")))
                                           ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) getgroups (int __size, __gid_t __list[])
{
  if (__builtin_object_size (__list, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__size) || __size < 0)
 return __getgroups_chk (__size, __list, __builtin_object_size (__list, 2 > 1));

      if (__size * sizeof (__gid_t) > __builtin_object_size (__list, 2 > 1))
 return __getgroups_chk_warn (__size, __list, __builtin_object_size (__list, 2 > 1));
    }
  return __getgroups_alias (__size, __list);
}


extern int __ttyname_r_chk (int __fd, char *__buf, size_t __buflen,
       size_t __nreal) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int __ttyname_r_alias (int __fd, char *__buf, size_t __buflen) __asm__ ("" "ttyname_r") __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__nonnull__ (2)));
extern int __ttyname_r_chk_warn (int __fd, char *__buf, size_t __buflen, size_t __nreal) __asm__ ("" "__ttyname_r_chk") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (2))) __attribute__((__warning__ ("ttyname_r called with bigger buflen than " "size of destination buffer")))
                                  ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) ttyname_r (int __fd, char *__buf, size_t __buflen)
{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__buflen))
 return __ttyname_r_chk (__fd, __buf, __buflen, __builtin_object_size (__buf, 2 > 1));

      if (__buflen > __builtin_object_size (__buf, 2 > 1))
 return __ttyname_r_chk_warn (__fd, __buf, __buflen, __builtin_object_size (__buf, 2 > 1));
    }
  return __ttyname_r_alias (__fd, __buf, __buflen);
}



extern int __getlogin_r_chk (char *__buf, size_t __buflen, size_t __nreal)
     __attribute__ ((__nonnull__ (1)));
extern int __getlogin_r_alias (char *__buf, size_t __buflen) __asm__ ("" "getlogin_r")
                     __attribute__ ((__nonnull__ (1)));
extern int __getlogin_r_chk_warn (char *__buf, size_t __buflen, size_t __nreal) __asm__ ("" "__getlogin_r_chk")


     __attribute__ ((__nonnull__ (1))) __attribute__((__warning__ ("getlogin_r called with bigger buflen than " "size of destination buffer")))
                                  ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
getlogin_r (char *__buf, size_t __buflen)
{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__buflen))
 return __getlogin_r_chk (__buf, __buflen, __builtin_object_size (__buf, 2 > 1));

      if (__buflen > __builtin_object_size (__buf, 2 > 1))
 return __getlogin_r_chk_warn (__buf, __buflen, __builtin_object_size (__buf, 2 > 1));
    }
  return __getlogin_r_alias (__buf, __buflen);
}




extern int __gethostname_chk (char *__buf, size_t __buflen, size_t __nreal)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int __gethostname_alias (char *__buf, size_t __buflen) __asm__ ("" "gethostname") __attribute__ ((__nothrow__ , __leaf__))
                   __attribute__ ((__nonnull__ (1)));
extern int __gethostname_chk_warn (char *__buf, size_t __buflen, size_t __nreal) __asm__ ("" "__gethostname_chk") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (1))) __attribute__((__warning__ ("gethostname called with bigger buflen than " "size of destination buffer")))
                                  ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) gethostname (char *__buf, size_t __buflen)
{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__buflen))
 return __gethostname_chk (__buf, __buflen, __builtin_object_size (__buf, 2 > 1));

      if (__buflen > __builtin_object_size (__buf, 2 > 1))
 return __gethostname_chk_warn (__buf, __buflen, __builtin_object_size (__buf, 2 > 1));
    }
  return __gethostname_alias (__buf, __buflen);
}




extern int __getdomainname_chk (char *__buf, size_t __buflen, size_t __nreal)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int __getdomainname_alias (char *__buf, size_t __buflen) __asm__ ("" "getdomainname") __attribute__ ((__nothrow__ , __leaf__))

                     __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__));
extern int __getdomainname_chk_warn (char *__buf, size_t __buflen, size_t __nreal) __asm__ ("" "__getdomainname_chk") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (1))) __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("getdomainname called with bigger " "buflen than size of destination " "buffer")))

                    ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) getdomainname (char *__buf, size_t __buflen)
{
  if (__builtin_object_size (__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__buflen))
 return __getdomainname_chk (__buf, __buflen, __builtin_object_size (__buf, 2 > 1));

      if (__buflen > __builtin_object_size (__buf, 2 > 1))
 return __getdomainname_chk_warn (__buf, __buflen, __builtin_object_size (__buf, 2 > 1));
    }
  return __getdomainname_alias (__buf, __buflen);
}








extern void _dl_mcount_wrapper_check (void *__selfpc) __attribute__ ((__nothrow__ , __leaf__));


typedef long int Lmid_t;











extern void *dlopen (const char *__file, int __mode) __attribute__ ((__nothrow__));



extern int dlclose (void *__handle) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern void *dlsym (void *__restrict __handle,
      const char *__restrict __name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern void *dlmopen (Lmid_t __nsid, const char *__file, int __mode) __attribute__ ((__nothrow__));



extern void *dlvsym (void *__restrict __handle,
       const char *__restrict __name,
       const char *__restrict __version)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));





extern char *dlerror (void) __attribute__ ((__nothrow__ , __leaf__));





typedef struct
{
  const char *dli_fname;
  void *dli_fbase;
  const char *dli_sname;
  void *dli_saddr;
} Dl_info;



extern int dladdr (const void *__address, Dl_info *__info)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int dladdr1 (const void *__address, Dl_info *__info,
      void **__extra_info, int __flags) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




enum
  {

    RTLD_DL_SYMENT = 1,


    RTLD_DL_LINKMAP = 2
  };







extern int dlinfo (void *__restrict __handle,
     int __request, void *__restrict __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));


enum
  {

    RTLD_DI_LMID = 1,



    RTLD_DI_LINKMAP = 2,

    RTLD_DI_CONFIGADDR = 3,






    RTLD_DI_SERINFO = 4,
    RTLD_DI_SERINFOSIZE = 5,



    RTLD_DI_ORIGIN = 6,

    RTLD_DI_PROFILENAME = 7,
    RTLD_DI_PROFILEOUT = 8,




    RTLD_DI_TLS_MODID = 9,





    RTLD_DI_TLS_DATA = 10,

    RTLD_DI_MAX = 10
  };




typedef struct
{
  char *dls_name;
  unsigned int dls_flags;
} Dl_serpath;



typedef struct
{
  size_t dls_size;
  unsigned int dls_cnt;
  Dl_serpath dls_serpath[1];
} Dl_serinfo;






typedef pthread_cond_t bc_cond_t;
typedef pthread_mutex_t bc_mutex_t;
typedef pthread_t bc_thread_t;
typedef uint8_t byte;

typedef int8_t javabyte;
typedef int16_t javashort;
typedef int32_t javaint;
typedef int64_t javalong;

typedef uint16_t javachar;


typedef uint64_t mpw;
typedef uint32_t mphw;


typedef struct
{
 size_t size;
 byte* data;
} memchunk;






memchunk* memchunkAlloc(size_t);

void memchunkWipe(memchunk*);

void memchunkFree(memchunk*);

memchunk* memchunkResize(memchunk*, size_t);

memchunk* memchunkClone(const memchunk*);

void mpzero(size_t size, mpw* data);

void mpfill(size_t size, mpw* data, mpw fill);

int mpodd (size_t size, const mpw* data);

int mpeven(size_t size, const mpw* data);

int mpz (size_t size, const mpw* data);

int mpnz (size_t size, const mpw* data);

int mpeq (size_t size, const mpw* xdata, const mpw* ydata);

int mpne (size_t size, const mpw* xdata, const mpw* ydata);

int mpgt (size_t size, const mpw* xdata, const mpw* ydata);

int mplt (size_t size, const mpw* xdata, const mpw* ydata);

int mpge (size_t size, const mpw* xdata, const mpw* ydata);

int mple (size_t size, const mpw* xdata, const mpw* ydata);

int mpcmp(size_t size, const mpw* xdata, const mpw* ydata);

int mpeqx(size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata);

int mpnex(size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata);

int mpgtx(size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata);

int mpltx(size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata);

int mpgex(size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata);

int mplex(size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata);

int mpcmpx(size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata);

int mpisone(size_t size, const mpw* data);

int mpistwo(size_t size, const mpw* data);

int mpleone(size_t size, const mpw* data);

int mpeqmone(size_t size, const mpw* xdata, const mpw* ydata);

int mpmsbset(size_t size, const mpw* data);

int mplsbset(size_t size, const mpw* data);








void mpsetmsb(size_t size, mpw* data);








void mpsetlsb(size_t size, mpw* data);








void mpclrmsb(size_t size, mpw* data);








void mpclrlsb(size_t size, mpw* data);

void mpand(size_t size, mpw* xdata, const mpw* ydata);

void mpor(size_t size, mpw* xdata, const mpw* ydata);

void mpxor(size_t size, mpw* xdata, const mpw* ydata);







void mpnot(size_t size, mpw* data);

void mpsetw(size_t size, mpw* xdata, mpw y);

void mpsetws(size_t size, mpw* xdata, size_t y);

void mpsetx(size_t xsize, mpw* xdata, size_t ysize, const mpw* ydata);

int mpaddw(size_t size, mpw* xdata, mpw y);

int mpadd (size_t size, mpw* xdata, const mpw* ydata);

int mpaddx(size_t xsize, mpw* xdata, size_t ysize, const mpw* ydata);

int mpsubw(size_t size, mpw* xdata, mpw y);

int mpsub (size_t size, mpw* xdata, const mpw* ydata);

int mpsubx(size_t xsize, mpw* xdata, size_t ysize, const mpw* ydata);


int mpmultwo(size_t size, mpw* data);







void mpneg(size_t size, mpw* data);








size_t mpsize(size_t size, const mpw* data);








size_t mpbits(size_t size, const mpw* data);


size_t mpmszcnt(size_t size, const mpw* data);


size_t mplszcnt(size_t size, const mpw* data);


void mplshift(size_t size, mpw* data, size_t count);


void mprshift(size_t size, mpw* data, size_t count);


size_t mprshiftlsz(size_t size, mpw* data);


size_t mpnorm(size_t size, mpw* data);


void mpdivtwo (size_t size, mpw* data);


void mpsdivtwo(size_t size, mpw* data);

mpw mpsetmul (size_t size, mpw* result, const mpw* data, mpw y);

mpw mpaddmul (size_t size, mpw* result, const mpw* data, mpw y);






void mpaddsqrtrc(size_t size, mpw* result, const mpw* data);





void mpmul(mpw* result, size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata);





void mpsqr(mpw* result, size_t size, const mpw* data);


void mpgcd_w(size_t size, const mpw* xdata, const mpw* ydata, mpw* result, mpw* wksp);


int mpextgcd_w(size_t size, const mpw* xdata, const mpw* ydata, mpw* result, mpw* wksp);


mpw mppndiv(mpw xhi, mpw xlo, mpw y);


void mpmod (mpw* result, size_t xsize, const mpw* xdata, size_t ysize, const mpw*ydata, mpw* wksp);


void mpndivmod(mpw* result, size_t xsize, const mpw* xdata, size_t ysize, const mpw* ydata, mpw* wksp);






void mpprint(size_t size, const mpw* data);


void mpprintln(size_t size, const mpw* data);


void mpfprint(FILE* f, size_t size, const mpw* data);


void mpfprintln(FILE* f, size_t size, const mpw* data);






int i2osp(byte* osdata, size_t ossize, const mpw* idata, size_t isize);


int os2ip(mpw* idata, size_t isize, const byte* osdata, size_t ossize);


int hs2ip(mpw* idata, size_t isize, const char* hsdata, size_t hssize);
struct _mpnumber

{
 size_t size;
 mpw* data;
};


typedef struct _mpnumber mpnumber;

void mpnzero(mpnumber*);

void mpnsize(mpnumber*, size_t);

void mpninit(mpnumber*, size_t, const mpw*);

void mpnfree(mpnumber*);

void mpncopy(mpnumber*, const mpnumber*);

void mpnwipe(mpnumber*);


void mpnset (mpnumber*, size_t, const mpw*);

void mpnsetw (mpnumber*, mpw);


int mpnsetbin(mpnumber*, const byte*, size_t);

int mpnsethex(mpnumber*, const char*);


int mpninv(mpnumber*, const mpnumber*, const mpnumber*);




size_t mpntrbits(mpnumber*, size_t);

size_t mpnbits(const mpnumber*);
typedef int (*entropyNext)(byte*, size_t);
struct _entropySource

{



 const char* name;



 const entropyNext next;
};


typedef struct _entropySource entropySource;

int entropySourceCount(void);

const entropySource* entropySourceGet(int n);







const entropySource* entropySourceFind(const char* name);







const entropySource* entropySourceDefault(void);

int entropyGatherNext(byte*, size_t);
typedef void randomGeneratorParam;

typedef int (*randomGeneratorSetup )(randomGeneratorParam*);
typedef int (*randomGeneratorSeed )(randomGeneratorParam*, const byte*, size_t);
typedef int (*randomGeneratorNext )(randomGeneratorParam*, byte*, size_t);
typedef int (*randomGeneratorCleanup)(randomGeneratorParam*);
struct _randomGenerator

{



 const char* name;





 const size_t paramsize;



 const randomGeneratorSetup setup;



 const randomGeneratorSeed seed;



 const randomGeneratorNext next;



 const randomGeneratorCleanup cleanup;
};


typedef struct _randomGenerator randomGenerator;

int randomGeneratorCount(void);

const randomGenerator* randomGeneratorGet(int);

const randomGenerator* randomGeneratorFind(const char*);

const randomGenerator* randomGeneratorDefault(void);
struct _randomGeneratorContext

{
 const randomGenerator* rng;
 randomGeneratorParam* param;






};


typedef struct _randomGeneratorContext randomGeneratorContext;

int randomGeneratorContextInit(randomGeneratorContext*, const randomGenerator*);

int randomGeneratorContextFree(randomGeneratorContext*);

int randomGeneratorContextNext(randomGeneratorContext*, byte*, size_t);

int randomGeneratorContextSeed(randomGeneratorContext*, const byte*, size_t);
typedef void hashFunctionParam;

typedef int (*hashFunctionReset )(hashFunctionParam*);
typedef int (*hashFunctionUpdate)(hashFunctionParam*, const byte*, size_t);
typedef int (*hashFunctionDigest)(hashFunctionParam*, byte*);
struct _hashFunction

{
 const char* name;
 const size_t paramsize;
 const size_t blocksize;
 const size_t digestsize;
 const hashFunctionReset reset;
 const hashFunctionUpdate update;
 const hashFunctionDigest digest;
};


typedef struct _hashFunction hashFunction;

int hashFunctionCount(void);

const hashFunction* hashFunctionGet(int);

const hashFunction* hashFunctionFind(const char*);

const hashFunction* hashFunctionDefault(void);
struct _hashFunctionContext

{
 const hashFunction* algo;
 hashFunctionParam* param;






};


typedef struct _hashFunctionContext hashFunctionContext;

int hashFunctionContextInit(hashFunctionContext*, const hashFunction*);

int hashFunctionContextFree(hashFunctionContext*);

int hashFunctionContextReset(hashFunctionContext*);

int hashFunctionContextUpdate(hashFunctionContext*, const byte*, size_t);

int hashFunctionContextUpdateMC(hashFunctionContext*, const memchunk*);

int hashFunctionContextUpdateMP(hashFunctionContext*, const mpnumber*);

int hashFunctionContextDigest(hashFunctionContext*, byte*);

int hashFunctionContextDigestMP(hashFunctionContext*, mpnumber*);

int hashFunctionContextDigestMatch(hashFunctionContext*, const mpnumber*);
typedef void keyedHashFunctionParam;

typedef int (*keyedHashFunctionSetup )(keyedHashFunctionParam*, const byte*, size_t);
typedef int (*keyedHashFunctionReset )(keyedHashFunctionParam*);
typedef int (*keyedHashFunctionUpdate )(keyedHashFunctionParam*, const byte*, size_t);
typedef int (*keyedHashFunctionDigest )(keyedHashFunctionParam*, byte*);
struct _keyedHashFunction

{
 const char* name;
 const size_t paramsize;
 const size_t blocksize;
 const size_t digestsize;
 const size_t keybitsmin;
 const size_t keybitsmax;
 const size_t keybitsinc;
 const keyedHashFunctionSetup setup;
 const keyedHashFunctionReset reset;
 const keyedHashFunctionUpdate update;
 const keyedHashFunctionDigest digest;
};


typedef struct _keyedHashFunction keyedHashFunction;

int keyedHashFunctionCount(void);

const keyedHashFunction* keyedHashFunctionGet(int);

const keyedHashFunction* keyedHashFunctionFind(const char*);

const keyedHashFunction* keyedHashFunctionDefault(void);
struct _keyedHashFunctionContext

{
 const keyedHashFunction* algo;
 keyedHashFunctionParam* param;






};


typedef struct _keyedHashFunctionContext keyedHashFunctionContext;

int keyedHashFunctionContextInit(keyedHashFunctionContext*, const keyedHashFunction*);

int keyedHashFunctionContextFree(keyedHashFunctionContext*);

int keyedHashFunctionContextSetup(keyedHashFunctionContext*, const byte*, size_t);

int keyedHashFunctionContextReset(keyedHashFunctionContext*);

int keyedHashFunctionContextUpdate(keyedHashFunctionContext*, const byte*, size_t);

int keyedHashFunctionContextUpdateMC(keyedHashFunctionContext*, const memchunk*);

int keyedHashFunctionContextUpdateMP(keyedHashFunctionContext*, const mpnumber*);

int keyedHashFunctionContextDigest(keyedHashFunctionContext*, byte*);

int keyedHashFunctionContextDigestMP(keyedHashFunctionContext*, mpnumber*);

int keyedHashFunctionContextDigestMatch(keyedHashFunctionContext*, const mpnumber*);
typedef enum
{
 NOCRYPT,
 ENCRYPT,
 DECRYPT
} cipherOperation;






typedef void blockCipherParam;




typedef int (*blockCipherSetup )(blockCipherParam*, const byte*, size_t, cipherOperation);
typedef int (*blockCipherSetIV )(blockCipherParam*, const byte*);
typedef int (*blockCipherSetCTR )(blockCipherParam*, const byte*, size_t);
typedef int (*blockCipherRawcrypt)(blockCipherParam*, uint32_t*, const uint32_t*);
typedef int (*blockCipherModcrypt)(blockCipherParam*, uint32_t*, const uint32_t*, unsigned int);

typedef uint32_t* (*blockCipherFeedback)(blockCipherParam*);

typedef struct
{
 const blockCipherRawcrypt encrypt;
 const blockCipherRawcrypt decrypt;
} blockCipherRaw;

typedef struct
{
 const blockCipherModcrypt encrypt;
 const blockCipherModcrypt decrypt;
} blockCipherMode;
struct _blockCipher

{



 const char* name;



 const size_t paramsize;



 const size_t blocksize;



 const size_t keybitsmin;



 const size_t keybitsmax;




 const size_t keybitsinc;



 const blockCipherSetup setup;



 const blockCipherSetIV setiv;



 const blockCipherSetCTR setctr;



 const blockCipherFeedback getfb;



 const blockCipherRaw raw;



 const blockCipherMode ecb;



 const blockCipherMode cbc;



 const blockCipherMode ctr;
};


typedef struct _blockCipher blockCipher;

int blockCipherCount(void);

const blockCipher* blockCipherGet(int);







const blockCipher* blockCipherFind(const char*);







const blockCipher* blockCipherDefault(void);
struct _blockCipherContext

{



 const blockCipher* algo;



 blockCipherParam* param;


 cipherOperation op;






};


typedef struct _blockCipherContext blockCipherContext;

int blockCipherContextInit(blockCipherContext*, const blockCipher*);


int blockCipherContextSetup(blockCipherContext*, const byte*, size_t, cipherOperation);


int blockCipherContextSetIV(blockCipherContext*, const byte*);


int blockCipherContextSetCTR(blockCipherContext*, const byte*, size_t);


int blockCipherContextFree(blockCipherContext*);


int blockCipherContextECB(blockCipherContext*, uint32_t*, const uint32_t*, int);


int blockCipherContextCBC(blockCipherContext*, uint32_t*, const uint32_t*, int);


int blockCipherContextCTR(blockCipherContext*, uint32_t*, const uint32_t*, int);


int blockCipherContextValidKeylen(blockCipherContext*, size_t);







struct _aesParam

{



 uint32_t k[64];



 uint32_t nr;



 uint32_t fdback[4];
};


typedef struct _aesParam aesParam;
extern const blockCipher aes;

int aesSetup (aesParam* ap, const byte* key, size_t keybits, cipherOperation op);

int aesSetIV (aesParam* ap, const byte* iv);

int aesSetCTR (aesParam* ap, const byte* nivz, size_t counter);

int aesEncrypt (aesParam* ap, uint32_t* dst, const uint32_t* src);

int aesDecrypt (aesParam* ap, uint32_t* dst, const uint32_t* src);


uint32_t* aesFeedback(aesParam* ap);
const uint32_t _aes_mask[4] = {
 0x000000ff,
 0x0000ff00,
 0x00ff0000,
 0xff000000
};

typedef struct
{






 const uint32_t t0[256];
 const uint32_t t1[256];
 const uint32_t t2[256];
 const uint32_t t3[256];

 const uint32_t t4[256];
} _table;

const _table _aes_enc = {
 { 0xa56363c6, 0x847c7cf8, 0x997777ee, 0x8d7b7bf6,
  0x0df2f2ff, 0xbd6b6bd6, 0xb16f6fde, 0x54c5c591,
  0x50303060, 0x03010102, 0xa96767ce, 0x7d2b2b56,
  0x19fefee7, 0x62d7d7b5, 0xe6abab4d, 0x9a7676ec,
  0x45caca8f, 0x9d82821f, 0x40c9c989, 0x877d7dfa,
  0x15fafaef, 0xeb5959b2, 0xc947478e, 0x0bf0f0fb,
  0xecadad41, 0x67d4d4b3, 0xfda2a25f, 0xeaafaf45,
  0xbf9c9c23, 0xf7a4a453, 0x967272e4, 0x5bc0c09b,
  0xc2b7b775, 0x1cfdfde1, 0xae93933d, 0x6a26264c,
  0x5a36366c, 0x413f3f7e, 0x02f7f7f5, 0x4fcccc83,
  0x5c343468, 0xf4a5a551, 0x34e5e5d1, 0x08f1f1f9,
  0x937171e2, 0x73d8d8ab, 0x53313162, 0x3f15152a,
  0x0c040408, 0x52c7c795, 0x65232346, 0x5ec3c39d,
  0x28181830, 0xa1969637, 0x0f05050a, 0xb59a9a2f,
  0x0907070e, 0x36121224, 0x9b80801b, 0x3de2e2df,
  0x26ebebcd, 0x6927274e, 0xcdb2b27f, 0x9f7575ea,
  0x1b090912, 0x9e83831d, 0x742c2c58, 0x2e1a1a34,
  0x2d1b1b36, 0xb26e6edc, 0xee5a5ab4, 0xfba0a05b,
  0xf65252a4, 0x4d3b3b76, 0x61d6d6b7, 0xceb3b37d,
  0x7b292952, 0x3ee3e3dd, 0x712f2f5e, 0x97848413,
  0xf55353a6, 0x68d1d1b9, 0x00000000, 0x2cededc1,
  0x60202040, 0x1ffcfce3, 0xc8b1b179, 0xed5b5bb6,
  0xbe6a6ad4, 0x46cbcb8d, 0xd9bebe67, 0x4b393972,
  0xde4a4a94, 0xd44c4c98, 0xe85858b0, 0x4acfcf85,
  0x6bd0d0bb, 0x2aefefc5, 0xe5aaaa4f, 0x16fbfbed,
  0xc5434386, 0xd74d4d9a, 0x55333366, 0x94858511,
  0xcf45458a, 0x10f9f9e9, 0x06020204, 0x817f7ffe,
  0xf05050a0, 0x443c3c78, 0xba9f9f25, 0xe3a8a84b,
  0xf35151a2, 0xfea3a35d, 0xc0404080, 0x8a8f8f05,
  0xad92923f, 0xbc9d9d21, 0x48383870, 0x04f5f5f1,
  0xdfbcbc63, 0xc1b6b677, 0x75dadaaf, 0x63212142,
  0x30101020, 0x1affffe5, 0x0ef3f3fd, 0x6dd2d2bf,
  0x4ccdcd81, 0x140c0c18, 0x35131326, 0x2fececc3,
  0xe15f5fbe, 0xa2979735, 0xcc444488, 0x3917172e,
  0x57c4c493, 0xf2a7a755, 0x827e7efc, 0x473d3d7a,
  0xac6464c8, 0xe75d5dba, 0x2b191932, 0x957373e6,
  0xa06060c0, 0x98818119, 0xd14f4f9e, 0x7fdcdca3,
  0x66222244, 0x7e2a2a54, 0xab90903b, 0x8388880b,
  0xca46468c, 0x29eeeec7, 0xd3b8b86b, 0x3c141428,
  0x79dedea7, 0xe25e5ebc, 0x1d0b0b16, 0x76dbdbad,
  0x3be0e0db, 0x56323264, 0x4e3a3a74, 0x1e0a0a14,
  0xdb494992, 0x0a06060c, 0x6c242448, 0xe45c5cb8,
  0x5dc2c29f, 0x6ed3d3bd, 0xefacac43, 0xa66262c4,
  0xa8919139, 0xa4959531, 0x37e4e4d3, 0x8b7979f2,
  0x32e7e7d5, 0x43c8c88b, 0x5937376e, 0xb76d6dda,
  0x8c8d8d01, 0x64d5d5b1, 0xd24e4e9c, 0xe0a9a949,
  0xb46c6cd8, 0xfa5656ac, 0x07f4f4f3, 0x25eaeacf,
  0xaf6565ca, 0x8e7a7af4, 0xe9aeae47, 0x18080810,
  0xd5baba6f, 0x887878f0, 0x6f25254a, 0x722e2e5c,
  0x241c1c38, 0xf1a6a657, 0xc7b4b473, 0x51c6c697,
  0x23e8e8cb, 0x7cdddda1, 0x9c7474e8, 0x211f1f3e,
  0xdd4b4b96, 0xdcbdbd61, 0x868b8b0d, 0x858a8a0f,
  0x907070e0, 0x423e3e7c, 0xc4b5b571, 0xaa6666cc,
  0xd8484890, 0x05030306, 0x01f6f6f7, 0x120e0e1c,
  0xa36161c2, 0x5f35356a, 0xf95757ae, 0xd0b9b969,
  0x91868617, 0x58c1c199, 0x271d1d3a, 0xb99e9e27,
  0x38e1e1d9, 0x13f8f8eb, 0xb398982b, 0x33111122,
  0xbb6969d2, 0x70d9d9a9, 0x898e8e07, 0xa7949433,
  0xb69b9b2d, 0x221e1e3c, 0x92878715, 0x20e9e9c9,
  0x49cece87, 0xff5555aa, 0x78282850, 0x7adfdfa5,
  0x8f8c8c03, 0xf8a1a159, 0x80898909, 0x170d0d1a,
  0xdabfbf65, 0x31e6e6d7, 0xc6424284, 0xb86868d0,
  0xc3414182, 0xb0999929, 0x772d2d5a, 0x110f0f1e,
  0xcbb0b07b, 0xfc5454a8, 0xd6bbbb6d, 0x3a16162c },
 { 0x6363c6a5, 0x7c7cf884, 0x7777ee99, 0x7b7bf68d,
  0xf2f2ff0d, 0x6b6bd6bd, 0x6f6fdeb1, 0xc5c59154,
  0x30306050, 0x01010203, 0x6767cea9, 0x2b2b567d,
  0xfefee719, 0xd7d7b562, 0xabab4de6, 0x7676ec9a,
  0xcaca8f45, 0x82821f9d, 0xc9c98940, 0x7d7dfa87,
  0xfafaef15, 0x5959b2eb, 0x47478ec9, 0xf0f0fb0b,
  0xadad41ec, 0xd4d4b367, 0xa2a25ffd, 0xafaf45ea,
  0x9c9c23bf, 0xa4a453f7, 0x7272e496, 0xc0c09b5b,
  0xb7b775c2, 0xfdfde11c, 0x93933dae, 0x26264c6a,
  0x36366c5a, 0x3f3f7e41, 0xf7f7f502, 0xcccc834f,
  0x3434685c, 0xa5a551f4, 0xe5e5d134, 0xf1f1f908,
  0x7171e293, 0xd8d8ab73, 0x31316253, 0x15152a3f,
  0x0404080c, 0xc7c79552, 0x23234665, 0xc3c39d5e,
  0x18183028, 0x969637a1, 0x05050a0f, 0x9a9a2fb5,
  0x07070e09, 0x12122436, 0x80801b9b, 0xe2e2df3d,
  0xebebcd26, 0x27274e69, 0xb2b27fcd, 0x7575ea9f,
  0x0909121b, 0x83831d9e, 0x2c2c5874, 0x1a1a342e,
  0x1b1b362d, 0x6e6edcb2, 0x5a5ab4ee, 0xa0a05bfb,
  0x5252a4f6, 0x3b3b764d, 0xd6d6b761, 0xb3b37dce,
  0x2929527b, 0xe3e3dd3e, 0x2f2f5e71, 0x84841397,
  0x5353a6f5, 0xd1d1b968, 0x00000000, 0xededc12c,
  0x20204060, 0xfcfce31f, 0xb1b179c8, 0x5b5bb6ed,
  0x6a6ad4be, 0xcbcb8d46, 0xbebe67d9, 0x3939724b,
  0x4a4a94de, 0x4c4c98d4, 0x5858b0e8, 0xcfcf854a,
  0xd0d0bb6b, 0xefefc52a, 0xaaaa4fe5, 0xfbfbed16,
  0x434386c5, 0x4d4d9ad7, 0x33336655, 0x85851194,
  0x45458acf, 0xf9f9e910, 0x02020406, 0x7f7ffe81,
  0x5050a0f0, 0x3c3c7844, 0x9f9f25ba, 0xa8a84be3,
  0x5151a2f3, 0xa3a35dfe, 0x404080c0, 0x8f8f058a,
  0x92923fad, 0x9d9d21bc, 0x38387048, 0xf5f5f104,
  0xbcbc63df, 0xb6b677c1, 0xdadaaf75, 0x21214263,
  0x10102030, 0xffffe51a, 0xf3f3fd0e, 0xd2d2bf6d,
  0xcdcd814c, 0x0c0c1814, 0x13132635, 0xececc32f,
  0x5f5fbee1, 0x979735a2, 0x444488cc, 0x17172e39,
  0xc4c49357, 0xa7a755f2, 0x7e7efc82, 0x3d3d7a47,
  0x6464c8ac, 0x5d5dbae7, 0x1919322b, 0x7373e695,
  0x6060c0a0, 0x81811998, 0x4f4f9ed1, 0xdcdca37f,
  0x22224466, 0x2a2a547e, 0x90903bab, 0x88880b83,
  0x46468cca, 0xeeeec729, 0xb8b86bd3, 0x1414283c,
  0xdedea779, 0x5e5ebce2, 0x0b0b161d, 0xdbdbad76,
  0xe0e0db3b, 0x32326456, 0x3a3a744e, 0x0a0a141e,
  0x494992db, 0x06060c0a, 0x2424486c, 0x5c5cb8e4,
  0xc2c29f5d, 0xd3d3bd6e, 0xacac43ef, 0x6262c4a6,
  0x919139a8, 0x959531a4, 0xe4e4d337, 0x7979f28b,
  0xe7e7d532, 0xc8c88b43, 0x37376e59, 0x6d6ddab7,
  0x8d8d018c, 0xd5d5b164, 0x4e4e9cd2, 0xa9a949e0,
  0x6c6cd8b4, 0x5656acfa, 0xf4f4f307, 0xeaeacf25,
  0x6565caaf, 0x7a7af48e, 0xaeae47e9, 0x08081018,
  0xbaba6fd5, 0x7878f088, 0x25254a6f, 0x2e2e5c72,
  0x1c1c3824, 0xa6a657f1, 0xb4b473c7, 0xc6c69751,
  0xe8e8cb23, 0xdddda17c, 0x7474e89c, 0x1f1f3e21,
  0x4b4b96dd, 0xbdbd61dc, 0x8b8b0d86, 0x8a8a0f85,
  0x7070e090, 0x3e3e7c42, 0xb5b571c4, 0x6666ccaa,
  0x484890d8, 0x03030605, 0xf6f6f701, 0x0e0e1c12,
  0x6161c2a3, 0x35356a5f, 0x5757aef9, 0xb9b969d0,
  0x86861791, 0xc1c19958, 0x1d1d3a27, 0x9e9e27b9,
  0xe1e1d938, 0xf8f8eb13, 0x98982bb3, 0x11112233,
  0x6969d2bb, 0xd9d9a970, 0x8e8e0789, 0x949433a7,
  0x9b9b2db6, 0x1e1e3c22, 0x87871592, 0xe9e9c920,
  0xcece8749, 0x5555aaff, 0x28285078, 0xdfdfa57a,
  0x8c8c038f, 0xa1a159f8, 0x89890980, 0x0d0d1a17,
  0xbfbf65da, 0xe6e6d731, 0x424284c6, 0x6868d0b8,
  0x414182c3, 0x999929b0, 0x2d2d5a77, 0x0f0f1e11,
  0xb0b07bcb, 0x5454a8fc, 0xbbbb6dd6, 0x16162c3a },
 { 0x63c6a563, 0x7cf8847c, 0x77ee9977, 0x7bf68d7b,
  0xf2ff0df2, 0x6bd6bd6b, 0x6fdeb16f, 0xc59154c5,
  0x30605030, 0x01020301, 0x67cea967, 0x2b567d2b,
  0xfee719fe, 0xd7b562d7, 0xab4de6ab, 0x76ec9a76,
  0xca8f45ca, 0x821f9d82, 0xc98940c9, 0x7dfa877d,
  0xfaef15fa, 0x59b2eb59, 0x478ec947, 0xf0fb0bf0,
  0xad41ecad, 0xd4b367d4, 0xa25ffda2, 0xaf45eaaf,
  0x9c23bf9c, 0xa453f7a4, 0x72e49672, 0xc09b5bc0,
  0xb775c2b7, 0xfde11cfd, 0x933dae93, 0x264c6a26,
  0x366c5a36, 0x3f7e413f, 0xf7f502f7, 0xcc834fcc,
  0x34685c34, 0xa551f4a5, 0xe5d134e5, 0xf1f908f1,
  0x71e29371, 0xd8ab73d8, 0x31625331, 0x152a3f15,
  0x04080c04, 0xc79552c7, 0x23466523, 0xc39d5ec3,
  0x18302818, 0x9637a196, 0x050a0f05, 0x9a2fb59a,
  0x070e0907, 0x12243612, 0x801b9b80, 0xe2df3de2,
  0xebcd26eb, 0x274e6927, 0xb27fcdb2, 0x75ea9f75,
  0x09121b09, 0x831d9e83, 0x2c58742c, 0x1a342e1a,
  0x1b362d1b, 0x6edcb26e, 0x5ab4ee5a, 0xa05bfba0,
  0x52a4f652, 0x3b764d3b, 0xd6b761d6, 0xb37dceb3,
  0x29527b29, 0xe3dd3ee3, 0x2f5e712f, 0x84139784,
  0x53a6f553, 0xd1b968d1, 0x00000000, 0xedc12ced,
  0x20406020, 0xfce31ffc, 0xb179c8b1, 0x5bb6ed5b,
  0x6ad4be6a, 0xcb8d46cb, 0xbe67d9be, 0x39724b39,
  0x4a94de4a, 0x4c98d44c, 0x58b0e858, 0xcf854acf,
  0xd0bb6bd0, 0xefc52aef, 0xaa4fe5aa, 0xfbed16fb,
  0x4386c543, 0x4d9ad74d, 0x33665533, 0x85119485,
  0x458acf45, 0xf9e910f9, 0x02040602, 0x7ffe817f,
  0x50a0f050, 0x3c78443c, 0x9f25ba9f, 0xa84be3a8,
  0x51a2f351, 0xa35dfea3, 0x4080c040, 0x8f058a8f,
  0x923fad92, 0x9d21bc9d, 0x38704838, 0xf5f104f5,
  0xbc63dfbc, 0xb677c1b6, 0xdaaf75da, 0x21426321,
  0x10203010, 0xffe51aff, 0xf3fd0ef3, 0xd2bf6dd2,
  0xcd814ccd, 0x0c18140c, 0x13263513, 0xecc32fec,
  0x5fbee15f, 0x9735a297, 0x4488cc44, 0x172e3917,
  0xc49357c4, 0xa755f2a7, 0x7efc827e, 0x3d7a473d,
  0x64c8ac64, 0x5dbae75d, 0x19322b19, 0x73e69573,
  0x60c0a060, 0x81199881, 0x4f9ed14f, 0xdca37fdc,
  0x22446622, 0x2a547e2a, 0x903bab90, 0x880b8388,
  0x468cca46, 0xeec729ee, 0xb86bd3b8, 0x14283c14,
  0xdea779de, 0x5ebce25e, 0x0b161d0b, 0xdbad76db,
  0xe0db3be0, 0x32645632, 0x3a744e3a, 0x0a141e0a,
  0x4992db49, 0x060c0a06, 0x24486c24, 0x5cb8e45c,
  0xc29f5dc2, 0xd3bd6ed3, 0xac43efac, 0x62c4a662,
  0x9139a891, 0x9531a495, 0xe4d337e4, 0x79f28b79,
  0xe7d532e7, 0xc88b43c8, 0x376e5937, 0x6ddab76d,
  0x8d018c8d, 0xd5b164d5, 0x4e9cd24e, 0xa949e0a9,
  0x6cd8b46c, 0x56acfa56, 0xf4f307f4, 0xeacf25ea,
  0x65caaf65, 0x7af48e7a, 0xae47e9ae, 0x08101808,
  0xba6fd5ba, 0x78f08878, 0x254a6f25, 0x2e5c722e,
  0x1c38241c, 0xa657f1a6, 0xb473c7b4, 0xc69751c6,
  0xe8cb23e8, 0xdda17cdd, 0x74e89c74, 0x1f3e211f,
  0x4b96dd4b, 0xbd61dcbd, 0x8b0d868b, 0x8a0f858a,
  0x70e09070, 0x3e7c423e, 0xb571c4b5, 0x66ccaa66,
  0x4890d848, 0x03060503, 0xf6f701f6, 0x0e1c120e,
  0x61c2a361, 0x356a5f35, 0x57aef957, 0xb969d0b9,
  0x86179186, 0xc19958c1, 0x1d3a271d, 0x9e27b99e,
  0xe1d938e1, 0xf8eb13f8, 0x982bb398, 0x11223311,
  0x69d2bb69, 0xd9a970d9, 0x8e07898e, 0x9433a794,
  0x9b2db69b, 0x1e3c221e, 0x87159287, 0xe9c920e9,
  0xce8749ce, 0x55aaff55, 0x28507828, 0xdfa57adf,
  0x8c038f8c, 0xa159f8a1, 0x89098089, 0x0d1a170d,
  0xbf65dabf, 0xe6d731e6, 0x4284c642, 0x68d0b868,
  0x4182c341, 0x9929b099, 0x2d5a772d, 0x0f1e110f,
  0xb07bcbb0, 0x54a8fc54, 0xbb6dd6bb, 0x162c3a16 },
 { 0xc6a56363, 0xf8847c7c, 0xee997777, 0xf68d7b7b,
  0xff0df2f2, 0xd6bd6b6b, 0xdeb16f6f, 0x9154c5c5,
  0x60503030, 0x02030101, 0xcea96767, 0x567d2b2b,
  0xe719fefe, 0xb562d7d7, 0x4de6abab, 0xec9a7676,
  0x8f45caca, 0x1f9d8282, 0x8940c9c9, 0xfa877d7d,
  0xef15fafa, 0xb2eb5959, 0x8ec94747, 0xfb0bf0f0,
  0x41ecadad, 0xb367d4d4, 0x5ffda2a2, 0x45eaafaf,
  0x23bf9c9c, 0x53f7a4a4, 0xe4967272, 0x9b5bc0c0,
  0x75c2b7b7, 0xe11cfdfd, 0x3dae9393, 0x4c6a2626,
  0x6c5a3636, 0x7e413f3f, 0xf502f7f7, 0x834fcccc,
  0x685c3434, 0x51f4a5a5, 0xd134e5e5, 0xf908f1f1,
  0xe2937171, 0xab73d8d8, 0x62533131, 0x2a3f1515,
  0x080c0404, 0x9552c7c7, 0x46652323, 0x9d5ec3c3,
  0x30281818, 0x37a19696, 0x0a0f0505, 0x2fb59a9a,
  0x0e090707, 0x24361212, 0x1b9b8080, 0xdf3de2e2,
  0xcd26ebeb, 0x4e692727, 0x7fcdb2b2, 0xea9f7575,
  0x121b0909, 0x1d9e8383, 0x58742c2c, 0x342e1a1a,
  0x362d1b1b, 0xdcb26e6e, 0xb4ee5a5a, 0x5bfba0a0,
  0xa4f65252, 0x764d3b3b, 0xb761d6d6, 0x7dceb3b3,
  0x527b2929, 0xdd3ee3e3, 0x5e712f2f, 0x13978484,
  0xa6f55353, 0xb968d1d1, 0x00000000, 0xc12ceded,
  0x40602020, 0xe31ffcfc, 0x79c8b1b1, 0xb6ed5b5b,
  0xd4be6a6a, 0x8d46cbcb, 0x67d9bebe, 0x724b3939,
  0x94de4a4a, 0x98d44c4c, 0xb0e85858, 0x854acfcf,
  0xbb6bd0d0, 0xc52aefef, 0x4fe5aaaa, 0xed16fbfb,
  0x86c54343, 0x9ad74d4d, 0x66553333, 0x11948585,
  0x8acf4545, 0xe910f9f9, 0x04060202, 0xfe817f7f,
  0xa0f05050, 0x78443c3c, 0x25ba9f9f, 0x4be3a8a8,
  0xa2f35151, 0x5dfea3a3, 0x80c04040, 0x058a8f8f,
  0x3fad9292, 0x21bc9d9d, 0x70483838, 0xf104f5f5,
  0x63dfbcbc, 0x77c1b6b6, 0xaf75dada, 0x42632121,
  0x20301010, 0xe51affff, 0xfd0ef3f3, 0xbf6dd2d2,
  0x814ccdcd, 0x18140c0c, 0x26351313, 0xc32fecec,
  0xbee15f5f, 0x35a29797, 0x88cc4444, 0x2e391717,
  0x9357c4c4, 0x55f2a7a7, 0xfc827e7e, 0x7a473d3d,
  0xc8ac6464, 0xbae75d5d, 0x322b1919, 0xe6957373,
  0xc0a06060, 0x19988181, 0x9ed14f4f, 0xa37fdcdc,
  0x44662222, 0x547e2a2a, 0x3bab9090, 0x0b838888,
  0x8cca4646, 0xc729eeee, 0x6bd3b8b8, 0x283c1414,
  0xa779dede, 0xbce25e5e, 0x161d0b0b, 0xad76dbdb,
  0xdb3be0e0, 0x64563232, 0x744e3a3a, 0x141e0a0a,
  0x92db4949, 0x0c0a0606, 0x486c2424, 0xb8e45c5c,
  0x9f5dc2c2, 0xbd6ed3d3, 0x43efacac, 0xc4a66262,
  0x39a89191, 0x31a49595, 0xd337e4e4, 0xf28b7979,
  0xd532e7e7, 0x8b43c8c8, 0x6e593737, 0xdab76d6d,
  0x018c8d8d, 0xb164d5d5, 0x9cd24e4e, 0x49e0a9a9,
  0xd8b46c6c, 0xacfa5656, 0xf307f4f4, 0xcf25eaea,
  0xcaaf6565, 0xf48e7a7a, 0x47e9aeae, 0x10180808,
  0x6fd5baba, 0xf0887878, 0x4a6f2525, 0x5c722e2e,
  0x38241c1c, 0x57f1a6a6, 0x73c7b4b4, 0x9751c6c6,
  0xcb23e8e8, 0xa17cdddd, 0xe89c7474, 0x3e211f1f,
  0x96dd4b4b, 0x61dcbdbd, 0x0d868b8b, 0x0f858a8a,
  0xe0907070, 0x7c423e3e, 0x71c4b5b5, 0xccaa6666,
  0x90d84848, 0x06050303, 0xf701f6f6, 0x1c120e0e,
  0xc2a36161, 0x6a5f3535, 0xaef95757, 0x69d0b9b9,
  0x17918686, 0x9958c1c1, 0x3a271d1d, 0x27b99e9e,
  0xd938e1e1, 0xeb13f8f8, 0x2bb39898, 0x22331111,
  0xd2bb6969, 0xa970d9d9, 0x07898e8e, 0x33a79494,
  0x2db69b9b, 0x3c221e1e, 0x15928787, 0xc920e9e9,
  0x8749cece, 0xaaff5555, 0x50782828, 0xa57adfdf,
  0x038f8c8c, 0x59f8a1a1, 0x09808989, 0x1a170d0d,
  0x65dabfbf, 0xd731e6e6, 0x84c64242, 0xd0b86868,
  0x82c34141, 0x29b09999, 0x5a772d2d, 0x1e110f0f,
  0x7bcbb0b0, 0xa8fc5454, 0x6dd6bbbb, 0x2c3a1616 },
 { 0x63636363, 0x7c7c7c7c, 0x77777777, 0x7b7b7b7b,
  0xf2f2f2f2, 0x6b6b6b6b, 0x6f6f6f6f, 0xc5c5c5c5,
  0x30303030, 0x01010101, 0x67676767, 0x2b2b2b2b,
  0xfefefefe, 0xd7d7d7d7, 0xabababab, 0x76767676,
  0xcacacaca, 0x82828282, 0xc9c9c9c9, 0x7d7d7d7d,
  0xfafafafa, 0x59595959, 0x47474747, 0xf0f0f0f0,
  0xadadadad, 0xd4d4d4d4, 0xa2a2a2a2, 0xafafafaf,
  0x9c9c9c9c, 0xa4a4a4a4, 0x72727272, 0xc0c0c0c0,
  0xb7b7b7b7, 0xfdfdfdfd, 0x93939393, 0x26262626,
  0x36363636, 0x3f3f3f3f, 0xf7f7f7f7, 0xcccccccc,
  0x34343434, 0xa5a5a5a5, 0xe5e5e5e5, 0xf1f1f1f1,
  0x71717171, 0xd8d8d8d8, 0x31313131, 0x15151515,
  0x04040404, 0xc7c7c7c7, 0x23232323, 0xc3c3c3c3,
  0x18181818, 0x96969696, 0x05050505, 0x9a9a9a9a,
  0x07070707, 0x12121212, 0x80808080, 0xe2e2e2e2,
  0xebebebeb, 0x27272727, 0xb2b2b2b2, 0x75757575,
  0x09090909, 0x83838383, 0x2c2c2c2c, 0x1a1a1a1a,
  0x1b1b1b1b, 0x6e6e6e6e, 0x5a5a5a5a, 0xa0a0a0a0,
  0x52525252, 0x3b3b3b3b, 0xd6d6d6d6, 0xb3b3b3b3,
  0x29292929, 0xe3e3e3e3, 0x2f2f2f2f, 0x84848484,
  0x53535353, 0xd1d1d1d1, 0x00000000, 0xedededed,
  0x20202020, 0xfcfcfcfc, 0xb1b1b1b1, 0x5b5b5b5b,
  0x6a6a6a6a, 0xcbcbcbcb, 0xbebebebe, 0x39393939,
  0x4a4a4a4a, 0x4c4c4c4c, 0x58585858, 0xcfcfcfcf,
  0xd0d0d0d0, 0xefefefef, 0xaaaaaaaa, 0xfbfbfbfb,
  0x43434343, 0x4d4d4d4d, 0x33333333, 0x85858585,
  0x45454545, 0xf9f9f9f9, 0x02020202, 0x7f7f7f7f,
  0x50505050, 0x3c3c3c3c, 0x9f9f9f9f, 0xa8a8a8a8,
  0x51515151, 0xa3a3a3a3, 0x40404040, 0x8f8f8f8f,
  0x92929292, 0x9d9d9d9d, 0x38383838, 0xf5f5f5f5,
  0xbcbcbcbc, 0xb6b6b6b6, 0xdadadada, 0x21212121,
  0x10101010, 0xffffffff, 0xf3f3f3f3, 0xd2d2d2d2,
  0xcdcdcdcd, 0x0c0c0c0c, 0x13131313, 0xecececec,
  0x5f5f5f5f, 0x97979797, 0x44444444, 0x17171717,
  0xc4c4c4c4, 0xa7a7a7a7, 0x7e7e7e7e, 0x3d3d3d3d,
  0x64646464, 0x5d5d5d5d, 0x19191919, 0x73737373,
  0x60606060, 0x81818181, 0x4f4f4f4f, 0xdcdcdcdc,
  0x22222222, 0x2a2a2a2a, 0x90909090, 0x88888888,
  0x46464646, 0xeeeeeeee, 0xb8b8b8b8, 0x14141414,
  0xdededede, 0x5e5e5e5e, 0x0b0b0b0b, 0xdbdbdbdb,
  0xe0e0e0e0, 0x32323232, 0x3a3a3a3a, 0x0a0a0a0a,
  0x49494949, 0x06060606, 0x24242424, 0x5c5c5c5c,
  0xc2c2c2c2, 0xd3d3d3d3, 0xacacacac, 0x62626262,
  0x91919191, 0x95959595, 0xe4e4e4e4, 0x79797979,
  0xe7e7e7e7, 0xc8c8c8c8, 0x37373737, 0x6d6d6d6d,
  0x8d8d8d8d, 0xd5d5d5d5, 0x4e4e4e4e, 0xa9a9a9a9,
  0x6c6c6c6c, 0x56565656, 0xf4f4f4f4, 0xeaeaeaea,
  0x65656565, 0x7a7a7a7a, 0xaeaeaeae, 0x08080808,
  0xbabababa, 0x78787878, 0x25252525, 0x2e2e2e2e,
  0x1c1c1c1c, 0xa6a6a6a6, 0xb4b4b4b4, 0xc6c6c6c6,
  0xe8e8e8e8, 0xdddddddd, 0x74747474, 0x1f1f1f1f,
  0x4b4b4b4b, 0xbdbdbdbd, 0x8b8b8b8b, 0x8a8a8a8a,
  0x70707070, 0x3e3e3e3e, 0xb5b5b5b5, 0x66666666,
  0x48484848, 0x03030303, 0xf6f6f6f6, 0x0e0e0e0e,
  0x61616161, 0x35353535, 0x57575757, 0xb9b9b9b9,
  0x86868686, 0xc1c1c1c1, 0x1d1d1d1d, 0x9e9e9e9e,
  0xe1e1e1e1, 0xf8f8f8f8, 0x98989898, 0x11111111,
  0x69696969, 0xd9d9d9d9, 0x8e8e8e8e, 0x94949494,
  0x9b9b9b9b, 0x1e1e1e1e, 0x87878787, 0xe9e9e9e9,
  0xcececece, 0x55555555, 0x28282828, 0xdfdfdfdf,
  0x8c8c8c8c, 0xa1a1a1a1, 0x89898989, 0x0d0d0d0d,
  0xbfbfbfbf, 0xe6e6e6e6, 0x42424242, 0x68686868,
  0x41414141, 0x99999999, 0x2d2d2d2d, 0x0f0f0f0f,
  0xb0b0b0b0, 0x54545454, 0xbbbbbbbb, 0x16161616 }
};
const _table _aes_dec = {
 { 0x50a7f451, 0x5365417e, 0xc3a4171a, 0x965e273a,
  0xcb6bab3b, 0xf1459d1f, 0xab58faac, 0x9303e34b,
  0x55fa3020, 0xf66d76ad, 0x9176cc88, 0x254c02f5,
  0xfcd7e54f, 0xd7cb2ac5, 0x80443526, 0x8fa362b5,
  0x495ab1de, 0x671bba25, 0x980eea45, 0xe1c0fe5d,
  0x02752fc3, 0x12f04c81, 0xa397468d, 0xc6f9d36b,
  0xe75f8f03, 0x959c9215, 0xeb7a6dbf, 0xda595295,
  0x2d83bed4, 0xd3217458, 0x2969e049, 0x44c8c98e,
  0x6a89c275, 0x78798ef4, 0x6b3e5899, 0xdd71b927,
  0xb64fe1be, 0x17ad88f0, 0x66ac20c9, 0xb43ace7d,
  0x184adf63, 0x82311ae5, 0x60335197, 0x457f5362,
  0xe07764b1, 0x84ae6bbb, 0x1ca081fe, 0x942b08f9,
  0x58684870, 0x19fd458f, 0x876cde94, 0xb7f87b52,
  0x23d373ab, 0xe2024b72, 0x578f1fe3, 0x2aab5566,
  0x0728ebb2, 0x03c2b52f, 0x9a7bc586, 0xa50837d3,
  0xf2872830, 0xb2a5bf23, 0xba6a0302, 0x5c8216ed,
  0x2b1ccf8a, 0x92b479a7, 0xf0f207f3, 0xa1e2694e,
  0xcdf4da65, 0xd5be0506, 0x1f6234d1, 0x8afea6c4,
  0x9d532e34, 0xa055f3a2, 0x32e18a05, 0x75ebf6a4,
  0x39ec830b, 0xaaef6040, 0x069f715e, 0x51106ebd,
  0xf98a213e, 0x3d06dd96, 0xae053edd, 0x46bde64d,
  0xb58d5491, 0x055dc471, 0x6fd40604, 0xff155060,
  0x24fb9819, 0x97e9bdd6, 0xcc434089, 0x779ed967,
  0xbd42e8b0, 0x888b8907, 0x385b19e7, 0xdbeec879,
  0x470a7ca1, 0xe90f427c, 0xc91e84f8, 0x00000000,
  0x83868009, 0x48ed2b32, 0xac70111e, 0x4e725a6c,
  0xfbff0efd, 0x5638850f, 0x1ed5ae3d, 0x27392d36,
  0x64d90f0a, 0x21a65c68, 0xd1545b9b, 0x3a2e3624,
  0xb1670a0c, 0x0fe75793, 0xd296eeb4, 0x9e919b1b,
  0x4fc5c080, 0xa220dc61, 0x694b775a, 0x161a121c,
  0x0aba93e2, 0xe52aa0c0, 0x43e0223c, 0x1d171b12,
  0x0b0d090e, 0xadc78bf2, 0xb9a8b62d, 0xc8a91e14,
  0x8519f157, 0x4c0775af, 0xbbdd99ee, 0xfd607fa3,
  0x9f2601f7, 0xbcf5725c, 0xc53b6644, 0x347efb5b,
  0x7629438b, 0xdcc623cb, 0x68fcedb6, 0x63f1e4b8,
  0xcadc31d7, 0x10856342, 0x40229713, 0x2011c684,
  0x7d244a85, 0xf83dbbd2, 0x1132f9ae, 0x6da129c7,
  0x4b2f9e1d, 0xf330b2dc, 0xec52860d, 0xd0e3c177,
  0x6c16b32b, 0x99b970a9, 0xfa489411, 0x2264e947,
  0xc48cfca8, 0x1a3ff0a0, 0xd82c7d56, 0xef903322,
  0xc74e4987, 0xc1d138d9, 0xfea2ca8c, 0x360bd498,
  0xcf81f5a6, 0x28de7aa5, 0x268eb7da, 0xa4bfad3f,
  0xe49d3a2c, 0x0d927850, 0x9bcc5f6a, 0x62467e54,
  0xc2138df6, 0xe8b8d890, 0x5ef7392e, 0xf5afc382,
  0xbe805d9f, 0x7c93d069, 0xa92dd56f, 0xb31225cf,
  0x3b99acc8, 0xa77d1810, 0x6e639ce8, 0x7bbb3bdb,
  0x097826cd, 0xf418596e, 0x01b79aec, 0xa89a4f83,
  0x656e95e6, 0x7ee6ffaa, 0x08cfbc21, 0xe6e815ef,
  0xd99be7ba, 0xce366f4a, 0xd4099fea, 0xd67cb029,
  0xafb2a431, 0x31233f2a, 0x3094a5c6, 0xc066a235,
  0x37bc4e74, 0xa6ca82fc, 0xb0d090e0, 0x15d8a733,
  0x4a9804f1, 0xf7daec41, 0x0e50cd7f, 0x2ff69117,
  0x8dd64d76, 0x4db0ef43, 0x544daacc, 0xdf0496e4,
  0xe3b5d19e, 0x1b886a4c, 0xb81f2cc1, 0x7f516546,
  0x04ea5e9d, 0x5d358c01, 0x737487fa, 0x2e410bfb,
  0x5a1d67b3, 0x52d2db92, 0x335610e9, 0x1347d66d,
  0x8c61d79a, 0x7a0ca137, 0x8e14f859, 0x893c13eb,
  0xee27a9ce, 0x35c961b7, 0xede51ce1, 0x3cb1477a,
  0x59dfd29c, 0x3f73f255, 0x79ce1418, 0xbf37c773,
  0xeacdf753, 0x5baafd5f, 0x146f3ddf, 0x86db4478,
  0x81f3afca, 0x3ec468b9, 0x2c342438, 0x5f40a3c2,
  0x72c31d16, 0x0c25e2bc, 0x8b493c28, 0x41950dff,
  0x7101a839, 0xdeb30c08, 0x9ce4b4d8, 0x90c15664,
  0x6184cb7b, 0x70b632d5, 0x745c6c48, 0x4257b8d0 },
 { 0xa7f45150, 0x65417e53, 0xa4171ac3, 0x5e273a96,
  0x6bab3bcb, 0x459d1ff1, 0x58faacab, 0x03e34b93,
  0xfa302055, 0x6d76adf6, 0x76cc8891, 0x4c02f525,
  0xd7e54ffc, 0xcb2ac5d7, 0x44352680, 0xa362b58f,
  0x5ab1de49, 0x1bba2567, 0x0eea4598, 0xc0fe5de1,
  0x752fc302, 0xf04c8112, 0x97468da3, 0xf9d36bc6,
  0x5f8f03e7, 0x9c921595, 0x7a6dbfeb, 0x595295da,
  0x83bed42d, 0x217458d3, 0x69e04929, 0xc8c98e44,
  0x89c2756a, 0x798ef478, 0x3e58996b, 0x71b927dd,
  0x4fe1beb6, 0xad88f017, 0xac20c966, 0x3ace7db4,
  0x4adf6318, 0x311ae582, 0x33519760, 0x7f536245,
  0x7764b1e0, 0xae6bbb84, 0xa081fe1c, 0x2b08f994,
  0x68487058, 0xfd458f19, 0x6cde9487, 0xf87b52b7,
  0xd373ab23, 0x024b72e2, 0x8f1fe357, 0xab55662a,
  0x28ebb207, 0xc2b52f03, 0x7bc5869a, 0x0837d3a5,
  0x872830f2, 0xa5bf23b2, 0x6a0302ba, 0x8216ed5c,
  0x1ccf8a2b, 0xb479a792, 0xf207f3f0, 0xe2694ea1,
  0xf4da65cd, 0xbe0506d5, 0x6234d11f, 0xfea6c48a,
  0x532e349d, 0x55f3a2a0, 0xe18a0532, 0xebf6a475,
  0xec830b39, 0xef6040aa, 0x9f715e06, 0x106ebd51,
  0x8a213ef9, 0x06dd963d, 0x053eddae, 0xbde64d46,
  0x8d5491b5, 0x5dc47105, 0xd406046f, 0x155060ff,
  0xfb981924, 0xe9bdd697, 0x434089cc, 0x9ed96777,
  0x42e8b0bd, 0x8b890788, 0x5b19e738, 0xeec879db,
  0x0a7ca147, 0x0f427ce9, 0x1e84f8c9, 0x00000000,
  0x86800983, 0xed2b3248, 0x70111eac, 0x725a6c4e,
  0xff0efdfb, 0x38850f56, 0xd5ae3d1e, 0x392d3627,
  0xd90f0a64, 0xa65c6821, 0x545b9bd1, 0x2e36243a,
  0x670a0cb1, 0xe757930f, 0x96eeb4d2, 0x919b1b9e,
  0xc5c0804f, 0x20dc61a2, 0x4b775a69, 0x1a121c16,
  0xba93e20a, 0x2aa0c0e5, 0xe0223c43, 0x171b121d,
  0x0d090e0b, 0xc78bf2ad, 0xa8b62db9, 0xa91e14c8,
  0x19f15785, 0x0775af4c, 0xdd99eebb, 0x607fa3fd,
  0x2601f79f, 0xf5725cbc, 0x3b6644c5, 0x7efb5b34,
  0x29438b76, 0xc623cbdc, 0xfcedb668, 0xf1e4b863,
  0xdc31d7ca, 0x85634210, 0x22971340, 0x11c68420,
  0x244a857d, 0x3dbbd2f8, 0x32f9ae11, 0xa129c76d,
  0x2f9e1d4b, 0x30b2dcf3, 0x52860dec, 0xe3c177d0,
  0x16b32b6c, 0xb970a999, 0x489411fa, 0x64e94722,
  0x8cfca8c4, 0x3ff0a01a, 0x2c7d56d8, 0x903322ef,
  0x4e4987c7, 0xd138d9c1, 0xa2ca8cfe, 0x0bd49836,
  0x81f5a6cf, 0xde7aa528, 0x8eb7da26, 0xbfad3fa4,
  0x9d3a2ce4, 0x9278500d, 0xcc5f6a9b, 0x467e5462,
  0x138df6c2, 0xb8d890e8, 0xf7392e5e, 0xafc382f5,
  0x805d9fbe, 0x93d0697c, 0x2dd56fa9, 0x1225cfb3,
  0x99acc83b, 0x7d1810a7, 0x639ce86e, 0xbb3bdb7b,
  0x7826cd09, 0x18596ef4, 0xb79aec01, 0x9a4f83a8,
  0x6e95e665, 0xe6ffaa7e, 0xcfbc2108, 0xe815efe6,
  0x9be7bad9, 0x366f4ace, 0x099fead4, 0x7cb029d6,
  0xb2a431af, 0x233f2a31, 0x94a5c630, 0x66a235c0,
  0xbc4e7437, 0xca82fca6, 0xd090e0b0, 0xd8a73315,
  0x9804f14a, 0xdaec41f7, 0x50cd7f0e, 0xf691172f,
  0xd64d768d, 0xb0ef434d, 0x4daacc54, 0x0496e4df,
  0xb5d19ee3, 0x886a4c1b, 0x1f2cc1b8, 0x5165467f,
  0xea5e9d04, 0x358c015d, 0x7487fa73, 0x410bfb2e,
  0x1d67b35a, 0xd2db9252, 0x5610e933, 0x47d66d13,
  0x61d79a8c, 0x0ca1377a, 0x14f8598e, 0x3c13eb89,
  0x27a9ceee, 0xc961b735, 0xe51ce1ed, 0xb1477a3c,
  0xdfd29c59, 0x73f2553f, 0xce141879, 0x37c773bf,
  0xcdf753ea, 0xaafd5f5b, 0x6f3ddf14, 0xdb447886,
  0xf3afca81, 0xc468b93e, 0x3424382c, 0x40a3c25f,
  0xc31d1672, 0x25e2bc0c, 0x493c288b, 0x950dff41,
  0x01a83971, 0xb30c08de, 0xe4b4d89c, 0xc1566490,
  0x84cb7b61, 0xb632d570, 0x5c6c4874, 0x57b8d042 },
 { 0xf45150a7, 0x417e5365, 0x171ac3a4, 0x273a965e,
  0xab3bcb6b, 0x9d1ff145, 0xfaacab58, 0xe34b9303,
  0x302055fa, 0x76adf66d, 0xcc889176, 0x02f5254c,
  0xe54ffcd7, 0x2ac5d7cb, 0x35268044, 0x62b58fa3,
  0xb1de495a, 0xba25671b, 0xea45980e, 0xfe5de1c0,
  0x2fc30275, 0x4c8112f0, 0x468da397, 0xd36bc6f9,
  0x8f03e75f, 0x9215959c, 0x6dbfeb7a, 0x5295da59,
  0xbed42d83, 0x7458d321, 0xe0492969, 0xc98e44c8,
  0xc2756a89, 0x8ef47879, 0x58996b3e, 0xb927dd71,
  0xe1beb64f, 0x88f017ad, 0x20c966ac, 0xce7db43a,
  0xdf63184a, 0x1ae58231, 0x51976033, 0x5362457f,
  0x64b1e077, 0x6bbb84ae, 0x81fe1ca0, 0x08f9942b,
  0x48705868, 0x458f19fd, 0xde94876c, 0x7b52b7f8,
  0x73ab23d3, 0x4b72e202, 0x1fe3578f, 0x55662aab,
  0xebb20728, 0xb52f03c2, 0xc5869a7b, 0x37d3a508,
  0x2830f287, 0xbf23b2a5, 0x0302ba6a, 0x16ed5c82,
  0xcf8a2b1c, 0x79a792b4, 0x07f3f0f2, 0x694ea1e2,
  0xda65cdf4, 0x0506d5be, 0x34d11f62, 0xa6c48afe,
  0x2e349d53, 0xf3a2a055, 0x8a0532e1, 0xf6a475eb,
  0x830b39ec, 0x6040aaef, 0x715e069f, 0x6ebd5110,
  0x213ef98a, 0xdd963d06, 0x3eddae05, 0xe64d46bd,
  0x5491b58d, 0xc471055d, 0x06046fd4, 0x5060ff15,
  0x981924fb, 0xbdd697e9, 0x4089cc43, 0xd967779e,
  0xe8b0bd42, 0x8907888b, 0x19e7385b, 0xc879dbee,
  0x7ca1470a, 0x427ce90f, 0x84f8c91e, 0x00000000,
  0x80098386, 0x2b3248ed, 0x111eac70, 0x5a6c4e72,
  0x0efdfbff, 0x850f5638, 0xae3d1ed5, 0x2d362739,
  0x0f0a64d9, 0x5c6821a6, 0x5b9bd154, 0x36243a2e,
  0x0a0cb167, 0x57930fe7, 0xeeb4d296, 0x9b1b9e91,
  0xc0804fc5, 0xdc61a220, 0x775a694b, 0x121c161a,
  0x93e20aba, 0xa0c0e52a, 0x223c43e0, 0x1b121d17,
  0x090e0b0d, 0x8bf2adc7, 0xb62db9a8, 0x1e14c8a9,
  0xf1578519, 0x75af4c07, 0x99eebbdd, 0x7fa3fd60,
  0x01f79f26, 0x725cbcf5, 0x6644c53b, 0xfb5b347e,
  0x438b7629, 0x23cbdcc6, 0xedb668fc, 0xe4b863f1,
  0x31d7cadc, 0x63421085, 0x97134022, 0xc6842011,
  0x4a857d24, 0xbbd2f83d, 0xf9ae1132, 0x29c76da1,
  0x9e1d4b2f, 0xb2dcf330, 0x860dec52, 0xc177d0e3,
  0xb32b6c16, 0x70a999b9, 0x9411fa48, 0xe9472264,
  0xfca8c48c, 0xf0a01a3f, 0x7d56d82c, 0x3322ef90,
  0x4987c74e, 0x38d9c1d1, 0xca8cfea2, 0xd498360b,
  0xf5a6cf81, 0x7aa528de, 0xb7da268e, 0xad3fa4bf,
  0x3a2ce49d, 0x78500d92, 0x5f6a9bcc, 0x7e546246,
  0x8df6c213, 0xd890e8b8, 0x392e5ef7, 0xc382f5af,
  0x5d9fbe80, 0xd0697c93, 0xd56fa92d, 0x25cfb312,
  0xacc83b99, 0x1810a77d, 0x9ce86e63, 0x3bdb7bbb,
  0x26cd0978, 0x596ef418, 0x9aec01b7, 0x4f83a89a,
  0x95e6656e, 0xffaa7ee6, 0xbc2108cf, 0x15efe6e8,
  0xe7bad99b, 0x6f4ace36, 0x9fead409, 0xb029d67c,
  0xa431afb2, 0x3f2a3123, 0xa5c63094, 0xa235c066,
  0x4e7437bc, 0x82fca6ca, 0x90e0b0d0, 0xa73315d8,
  0x04f14a98, 0xec41f7da, 0xcd7f0e50, 0x91172ff6,
  0x4d768dd6, 0xef434db0, 0xaacc544d, 0x96e4df04,
  0xd19ee3b5, 0x6a4c1b88, 0x2cc1b81f, 0x65467f51,
  0x5e9d04ea, 0x8c015d35, 0x87fa7374, 0x0bfb2e41,
  0x67b35a1d, 0xdb9252d2, 0x10e93356, 0xd66d1347,
  0xd79a8c61, 0xa1377a0c, 0xf8598e14, 0x13eb893c,
  0xa9ceee27, 0x61b735c9, 0x1ce1ede5, 0x477a3cb1,
  0xd29c59df, 0xf2553f73, 0x141879ce, 0xc773bf37,
  0xf753eacd, 0xfd5f5baa, 0x3ddf146f, 0x447886db,
  0xafca81f3, 0x68b93ec4, 0x24382c34, 0xa3c25f40,
  0x1d1672c3, 0xe2bc0c25, 0x3c288b49, 0x0dff4195,
  0xa8397101, 0x0c08deb3, 0xb4d89ce4, 0x566490c1,
  0xcb7b6184, 0x32d570b6, 0x6c48745c, 0xb8d04257 },
 { 0x5150a7f4, 0x7e536541, 0x1ac3a417, 0x3a965e27,
  0x3bcb6bab, 0x1ff1459d, 0xacab58fa, 0x4b9303e3,
  0x2055fa30, 0xadf66d76, 0x889176cc, 0xf5254c02,
  0x4ffcd7e5, 0xc5d7cb2a, 0x26804435, 0xb58fa362,
  0xde495ab1, 0x25671bba, 0x45980eea, 0x5de1c0fe,
  0xc302752f, 0x8112f04c, 0x8da39746, 0x6bc6f9d3,
  0x03e75f8f, 0x15959c92, 0xbfeb7a6d, 0x95da5952,
  0xd42d83be, 0x58d32174, 0x492969e0, 0x8e44c8c9,
  0x756a89c2, 0xf478798e, 0x996b3e58, 0x27dd71b9,
  0xbeb64fe1, 0xf017ad88, 0xc966ac20, 0x7db43ace,
  0x63184adf, 0xe582311a, 0x97603351, 0x62457f53,
  0xb1e07764, 0xbb84ae6b, 0xfe1ca081, 0xf9942b08,
  0x70586848, 0x8f19fd45, 0x94876cde, 0x52b7f87b,
  0xab23d373, 0x72e2024b, 0xe3578f1f, 0x662aab55,
  0xb20728eb, 0x2f03c2b5, 0x869a7bc5, 0xd3a50837,
  0x30f28728, 0x23b2a5bf, 0x02ba6a03, 0xed5c8216,
  0x8a2b1ccf, 0xa792b479, 0xf3f0f207, 0x4ea1e269,
  0x65cdf4da, 0x06d5be05, 0xd11f6234, 0xc48afea6,
  0x349d532e, 0xa2a055f3, 0x0532e18a, 0xa475ebf6,
  0x0b39ec83, 0x40aaef60, 0x5e069f71, 0xbd51106e,
  0x3ef98a21, 0x963d06dd, 0xddae053e, 0x4d46bde6,
  0x91b58d54, 0x71055dc4, 0x046fd406, 0x60ff1550,
  0x1924fb98, 0xd697e9bd, 0x89cc4340, 0x67779ed9,
  0xb0bd42e8, 0x07888b89, 0xe7385b19, 0x79dbeec8,
  0xa1470a7c, 0x7ce90f42, 0xf8c91e84, 0x00000000,
  0x09838680, 0x3248ed2b, 0x1eac7011, 0x6c4e725a,
  0xfdfbff0e, 0x0f563885, 0x3d1ed5ae, 0x3627392d,
  0x0a64d90f, 0x6821a65c, 0x9bd1545b, 0x243a2e36,
  0x0cb1670a, 0x930fe757, 0xb4d296ee, 0x1b9e919b,
  0x804fc5c0, 0x61a220dc, 0x5a694b77, 0x1c161a12,
  0xe20aba93, 0xc0e52aa0, 0x3c43e022, 0x121d171b,
  0x0e0b0d09, 0xf2adc78b, 0x2db9a8b6, 0x14c8a91e,
  0x578519f1, 0xaf4c0775, 0xeebbdd99, 0xa3fd607f,
  0xf79f2601, 0x5cbcf572, 0x44c53b66, 0x5b347efb,
  0x8b762943, 0xcbdcc623, 0xb668fced, 0xb863f1e4,
  0xd7cadc31, 0x42108563, 0x13402297, 0x842011c6,
  0x857d244a, 0xd2f83dbb, 0xae1132f9, 0xc76da129,
  0x1d4b2f9e, 0xdcf330b2, 0x0dec5286, 0x77d0e3c1,
  0x2b6c16b3, 0xa999b970, 0x11fa4894, 0x472264e9,
  0xa8c48cfc, 0xa01a3ff0, 0x56d82c7d, 0x22ef9033,
  0x87c74e49, 0xd9c1d138, 0x8cfea2ca, 0x98360bd4,
  0xa6cf81f5, 0xa528de7a, 0xda268eb7, 0x3fa4bfad,
  0x2ce49d3a, 0x500d9278, 0x6a9bcc5f, 0x5462467e,
  0xf6c2138d, 0x90e8b8d8, 0x2e5ef739, 0x82f5afc3,
  0x9fbe805d, 0x697c93d0, 0x6fa92dd5, 0xcfb31225,
  0xc83b99ac, 0x10a77d18, 0xe86e639c, 0xdb7bbb3b,
  0xcd097826, 0x6ef41859, 0xec01b79a, 0x83a89a4f,
  0xe6656e95, 0xaa7ee6ff, 0x2108cfbc, 0xefe6e815,
  0xbad99be7, 0x4ace366f, 0xead4099f, 0x29d67cb0,
  0x31afb2a4, 0x2a31233f, 0xc63094a5, 0x35c066a2,
  0x7437bc4e, 0xfca6ca82, 0xe0b0d090, 0x3315d8a7,
  0xf14a9804, 0x41f7daec, 0x7f0e50cd, 0x172ff691,
  0x768dd64d, 0x434db0ef, 0xcc544daa, 0xe4df0496,
  0x9ee3b5d1, 0x4c1b886a, 0xc1b81f2c, 0x467f5165,
  0x9d04ea5e, 0x015d358c, 0xfa737487, 0xfb2e410b,
  0xb35a1d67, 0x9252d2db, 0xe9335610, 0x6d1347d6,
  0x9a8c61d7, 0x377a0ca1, 0x598e14f8, 0xeb893c13,
  0xceee27a9, 0xb735c961, 0xe1ede51c, 0x7a3cb147,
  0x9c59dfd2, 0x553f73f2, 0x1879ce14, 0x73bf37c7,
  0x53eacdf7, 0x5f5baafd, 0xdf146f3d, 0x7886db44,
  0xca81f3af, 0xb93ec468, 0x382c3424, 0xc25f40a3,
  0x1672c31d, 0xbc0c25e2, 0x288b493c, 0xff41950d,
  0x397101a8, 0x08deb30c, 0xd89ce4b4, 0x6490c156,
  0x7b6184cb, 0xd570b632, 0x48745c6c, 0xd04257b8 },
 { 0x52525252, 0x09090909, 0x6a6a6a6a, 0xd5d5d5d5,
  0x30303030, 0x36363636, 0xa5a5a5a5, 0x38383838,
  0xbfbfbfbf, 0x40404040, 0xa3a3a3a3, 0x9e9e9e9e,
  0x81818181, 0xf3f3f3f3, 0xd7d7d7d7, 0xfbfbfbfb,
  0x7c7c7c7c, 0xe3e3e3e3, 0x39393939, 0x82828282,
  0x9b9b9b9b, 0x2f2f2f2f, 0xffffffff, 0x87878787,
  0x34343434, 0x8e8e8e8e, 0x43434343, 0x44444444,
  0xc4c4c4c4, 0xdededede, 0xe9e9e9e9, 0xcbcbcbcb,
  0x54545454, 0x7b7b7b7b, 0x94949494, 0x32323232,
  0xa6a6a6a6, 0xc2c2c2c2, 0x23232323, 0x3d3d3d3d,
  0xeeeeeeee, 0x4c4c4c4c, 0x95959595, 0x0b0b0b0b,
  0x42424242, 0xfafafafa, 0xc3c3c3c3, 0x4e4e4e4e,
  0x08080808, 0x2e2e2e2e, 0xa1a1a1a1, 0x66666666,
  0x28282828, 0xd9d9d9d9, 0x24242424, 0xb2b2b2b2,
  0x76767676, 0x5b5b5b5b, 0xa2a2a2a2, 0x49494949,
  0x6d6d6d6d, 0x8b8b8b8b, 0xd1d1d1d1, 0x25252525,
  0x72727272, 0xf8f8f8f8, 0xf6f6f6f6, 0x64646464,
  0x86868686, 0x68686868, 0x98989898, 0x16161616,
  0xd4d4d4d4, 0xa4a4a4a4, 0x5c5c5c5c, 0xcccccccc,
  0x5d5d5d5d, 0x65656565, 0xb6b6b6b6, 0x92929292,
  0x6c6c6c6c, 0x70707070, 0x48484848, 0x50505050,
  0xfdfdfdfd, 0xedededed, 0xb9b9b9b9, 0xdadadada,
  0x5e5e5e5e, 0x15151515, 0x46464646, 0x57575757,
  0xa7a7a7a7, 0x8d8d8d8d, 0x9d9d9d9d, 0x84848484,
  0x90909090, 0xd8d8d8d8, 0xabababab, 0x00000000,
  0x8c8c8c8c, 0xbcbcbcbc, 0xd3d3d3d3, 0x0a0a0a0a,
  0xf7f7f7f7, 0xe4e4e4e4, 0x58585858, 0x05050505,
  0xb8b8b8b8, 0xb3b3b3b3, 0x45454545, 0x06060606,
  0xd0d0d0d0, 0x2c2c2c2c, 0x1e1e1e1e, 0x8f8f8f8f,
  0xcacacaca, 0x3f3f3f3f, 0x0f0f0f0f, 0x02020202,
  0xc1c1c1c1, 0xafafafaf, 0xbdbdbdbd, 0x03030303,
  0x01010101, 0x13131313, 0x8a8a8a8a, 0x6b6b6b6b,
  0x3a3a3a3a, 0x91919191, 0x11111111, 0x41414141,
  0x4f4f4f4f, 0x67676767, 0xdcdcdcdc, 0xeaeaeaea,
  0x97979797, 0xf2f2f2f2, 0xcfcfcfcf, 0xcececece,
  0xf0f0f0f0, 0xb4b4b4b4, 0xe6e6e6e6, 0x73737373,
  0x96969696, 0xacacacac, 0x74747474, 0x22222222,
  0xe7e7e7e7, 0xadadadad, 0x35353535, 0x85858585,
  0xe2e2e2e2, 0xf9f9f9f9, 0x37373737, 0xe8e8e8e8,
  0x1c1c1c1c, 0x75757575, 0xdfdfdfdf, 0x6e6e6e6e,
  0x47474747, 0xf1f1f1f1, 0x1a1a1a1a, 0x71717171,
  0x1d1d1d1d, 0x29292929, 0xc5c5c5c5, 0x89898989,
  0x6f6f6f6f, 0xb7b7b7b7, 0x62626262, 0x0e0e0e0e,
  0xaaaaaaaa, 0x18181818, 0xbebebebe, 0x1b1b1b1b,
  0xfcfcfcfc, 0x56565656, 0x3e3e3e3e, 0x4b4b4b4b,
  0xc6c6c6c6, 0xd2d2d2d2, 0x79797979, 0x20202020,
  0x9a9a9a9a, 0xdbdbdbdb, 0xc0c0c0c0, 0xfefefefe,
  0x78787878, 0xcdcdcdcd, 0x5a5a5a5a, 0xf4f4f4f4,
  0x1f1f1f1f, 0xdddddddd, 0xa8a8a8a8, 0x33333333,
  0x88888888, 0x07070707, 0xc7c7c7c7, 0x31313131,
  0xb1b1b1b1, 0x12121212, 0x10101010, 0x59595959,
  0x27272727, 0x80808080, 0xecececec, 0x5f5f5f5f,
  0x60606060, 0x51515151, 0x7f7f7f7f, 0xa9a9a9a9,
  0x19191919, 0xb5b5b5b5, 0x4a4a4a4a, 0x0d0d0d0d,
  0x2d2d2d2d, 0xe5e5e5e5, 0x7a7a7a7a, 0x9f9f9f9f,
  0x93939393, 0xc9c9c9c9, 0x9c9c9c9c, 0xefefefef,
  0xa0a0a0a0, 0xe0e0e0e0, 0x3b3b3b3b, 0x4d4d4d4d,
  0xaeaeaeae, 0x2a2a2a2a, 0xf5f5f5f5, 0xb0b0b0b0,
  0xc8c8c8c8, 0xebebebeb, 0xbbbbbbbb, 0x3c3c3c3c,
  0x83838383, 0x53535353, 0x99999999, 0x61616161,
  0x17171717, 0x2b2b2b2b, 0x04040404, 0x7e7e7e7e,
  0xbabababa, 0x77777777, 0xd6d6d6d6, 0x26262626,
  0xe1e1e1e1, 0x69696969, 0x14141414, 0x63636363,
  0x55555555, 0x21212121, 0x0c0c0c0c, 0x7d7d7d7d }
};







static const uint32_t _arc[] = {
    0x00000001, 0x00000002, 0x00000004, 0x00000008,
    0x00000010, 0x00000020, 0x00000040, 0x00000080,
    0x0000001b, 0x00000036
};
const blockCipher aes = {
 "AES",
 sizeof(aesParam),
 16,
 128,
 256,
 64,
 (blockCipherSetup) aesSetup,
 (blockCipherSetIV) aesSetIV,
 (blockCipherSetCTR) aesSetCTR,
 (blockCipherFeedback) aesFeedback,

 {
  (blockCipherRawcrypt) aesEncrypt,
  (blockCipherRawcrypt) aesDecrypt
 },

 {



  (blockCipherModcrypt) 0,




  (blockCipherModcrypt) 0,

 },

 {



  (blockCipherModcrypt) 0,




  (blockCipherModcrypt) 0

 },

 {



  (blockCipherModcrypt) 0,




  (blockCipherModcrypt) 0

 }
};

int aesSetup(aesParam* ap, const byte* key, size_t keybits, cipherOperation op)
{
 if ((op != ENCRYPT) && (op != DECRYPT))
  return -1;

 if (((keybits & 63) == 0) && (keybits >= 128) && (keybits <= 256))
 {
  register uint32_t* rk, t, i, j;


  ap->fdback[0] = 0;
  ap->fdback[1] = 0;
  ap->fdback[2] = 0;
  ap->fdback[3] = 0;

  ap->nr = 6 + (keybits >> 5);

  rk = ap->k;

  memcpy(rk, key, keybits >> 3);

  i = 0;

  if (keybits == 128)
  {
   while (1)
   {
    t = rk[3];







    t = (_aes_enc.t4[(t >> 8) & 0xff] & 0x000000ff) ^
     (_aes_enc.t4[(t >> 16) & 0xff] & 0x0000ff00) ^
     (_aes_enc.t4[(t >> 24) ] & 0x00ff0000) ^
     (_aes_enc.t4[(t ) & 0xff] & 0xff000000) ^
      _arc[i];

    rk[4] = (t ^= rk[0]);
    rk[5] = (t ^= rk[1]);
    rk[6] = (t ^= rk[2]);
    rk[7] = (t ^= rk[3]);
    if (++i == 10)
     break;
    rk += 4;
   }
  }
  else if (keybits == 192)
  {
   while (1)
   {
    t = rk[5];







    t = (_aes_enc.t4[(t >> 8) & 0xff] & 0x000000ff) ^
     (_aes_enc.t4[(t >> 16) & 0xff] & 0x0000ff00) ^
     (_aes_enc.t4[(t >> 24) ] & 0x00ff0000) ^
     (_aes_enc.t4[(t ) & 0xff] & 0xff000000) ^
      _arc[i];

    rk[6] = (t ^= rk[0]);
    rk[7] = (t ^= rk[1]);
    rk[8] = (t ^= rk[2]);
    rk[9] = (t ^= rk[3]);
    if (++i == 8)
     break;
    rk[10] = (t ^= rk[4]);
    rk[11] = (t ^= rk[5]);
    rk += 6;
   }
  }
  else if (keybits == 256)
  {
   while (1)
   {
    t = rk[7];







    t = (_aes_enc.t4[(t >> 8) & 0xff] & 0x000000ff) ^
     (_aes_enc.t4[(t >> 16) & 0xff] & 0x0000ff00) ^
     (_aes_enc.t4[(t >> 24) ] & 0x00ff0000) ^
     (_aes_enc.t4[(t ) & 0xff] & 0xff000000) ^
      _arc[i];

    rk[8] = (t ^= rk[0]);
    rk[9] = (t ^= rk[1]);
    rk[10] = (t ^= rk[2]);
    rk[11] = (t ^= rk[3]);
    if (++i == 7)
     break;






    t = (_aes_enc.t4[(t ) & 0xff] & 0x000000ff) ^
     (_aes_enc.t4[(t >> 8) & 0xff] & 0x0000ff00) ^
     (_aes_enc.t4[(t >> 16) & 0xff] & 0x00ff0000) ^
     (_aes_enc.t4[(t >> 24) ] & 0xff000000);

    rk[12] = (t ^= rk[4]);
    rk[13] = (t ^= rk[5]);
    rk[14] = (t ^= rk[6]);
    rk[15] = (t ^= rk[7]);
    rk += 8;
   }
  }

  if (op == DECRYPT)
  {
   rk = ap->k;

   for (i = 0, j = (ap->nr << 2); i < j; i += 4, j -= 4)
   {
    t = rk[i ]; rk[i ] = rk[j ]; rk[j ] = t;
    t = rk[i+1]; rk[i+1] = rk[j+1]; rk[j+1] = t;
    t = rk[i+2]; rk[i+2] = rk[j+2]; rk[j+2] = t;
    t = rk[i+3]; rk[i+3] = rk[j+3]; rk[j+3] = t;
   }
   for (i = 1; i < ap->nr; i++)
   {
    rk += 4;
    rk[0] =
     _aes_dec.t0[_aes_enc.t4[(rk[0] ) & 0xff] & 0xff] ^
     _aes_dec.t1[_aes_enc.t4[(rk[0] >> 8) & 0xff] & 0xff] ^
     _aes_dec.t2[_aes_enc.t4[(rk[0] >> 16) & 0xff] & 0xff] ^
     _aes_dec.t3[_aes_enc.t4[(rk[0] >> 24) ] & 0xff];
    rk[1] =
     _aes_dec.t0[_aes_enc.t4[(rk[1] ) & 0xff] & 0xff] ^
     _aes_dec.t1[_aes_enc.t4[(rk[1] >> 8) & 0xff] & 0xff] ^
     _aes_dec.t2[_aes_enc.t4[(rk[1] >> 16) & 0xff] & 0xff] ^
     _aes_dec.t3[_aes_enc.t4[(rk[1] >> 24) ] & 0xff];
    rk[2] =
     _aes_dec.t0[_aes_enc.t4[(rk[2] ) & 0xff] & 0xff] ^
     _aes_dec.t1[_aes_enc.t4[(rk[2] >> 8) & 0xff] & 0xff] ^
     _aes_dec.t2[_aes_enc.t4[(rk[2] >> 16) & 0xff] & 0xff] ^
     _aes_dec.t3[_aes_enc.t4[(rk[2] >> 24) ] & 0xff];
    rk[3] =
     _aes_dec.t0[_aes_enc.t4[(rk[3] ) & 0xff] & 0xff] ^
     _aes_dec.t1[_aes_enc.t4[(rk[3] >> 8) & 0xff] & 0xff] ^
     _aes_dec.t2[_aes_enc.t4[(rk[3] >> 16) & 0xff] & 0xff] ^
     _aes_dec.t3[_aes_enc.t4[(rk[3] >> 24) ] & 0xff];

   }
  }
  return 0;
 }
 return -1;
}


int aesSetIV(aesParam* ap, const byte* iv)
{
 if (iv)
  memcpy(ap->fdback, iv, 16);
 else
  memset(ap->fdback, 0, 16);

 return 0;
}



int aesSetCTR(aesParam* ap, const byte* nivz, size_t counter)
{
 unsigned int blockwords = ((16) >> 3);

 if (nivz)
 {
  mpw tmp[((16) >> 3)];

  os2ip((mpw*) ap->fdback, blockwords, nivz, 16);
  mpsetws(blockwords, tmp, counter);
  mpadd(blockwords, (mpw*) ap->fdback, tmp);
 }
 else
  mpsetws(blockwords, (mpw*) ap->fdback, counter);

 return 0;
}



int aesEncrypt(aesParam* ap, uint32_t* dst, const uint32_t* src)
{
 register uint32_t s0, s1, s2, s3;
 register uint32_t t0, t1, t2, t3;
 register uint32_t* rk = ap->k;

 s0 = src[0] ^ rk[0];
 s1 = src[1] ^ rk[1];
 s2 = src[2] ^ rk[2];
 s3 = src[3] ^ rk[3];

 t0 = _aes_enc.t0[(s0 ) & 0xff] ^ _aes_enc.t1[(s1 >> 8) & 0xff] ^ _aes_enc.t2[(s2 >> 16) & 0xff] ^ _aes_enc.t3[(s3 >> 24) ] ^ rk[4 +0]; t1 = _aes_enc.t0[(s1 ) & 0xff] ^ _aes_enc.t1[(s2 >> 8) & 0xff] ^ _aes_enc.t2[(s3 >> 16) & 0xff] ^ _aes_enc.t3[(s0 >> 24) ] ^ rk[4 +1]; t2 = _aes_enc.t0[(s2 ) & 0xff] ^ _aes_enc.t1[(s3 >> 8) & 0xff] ^ _aes_enc.t2[(s0 >> 16) & 0xff] ^ _aes_enc.t3[(s1 >> 24) ] ^ rk[4 +2]; t3 = _aes_enc.t0[(s3 ) & 0xff] ^ _aes_enc.t1[(s0 >> 8) & 0xff] ^ _aes_enc.t2[(s1 >> 16) & 0xff] ^ _aes_enc.t3[(s2 >> 24) ] ^ rk[4 +3];;
 s0 = _aes_enc.t0[(t0 ) & 0xff] ^ _aes_enc.t1[(t1 >> 8) & 0xff] ^ _aes_enc.t2[(t2 >> 16) & 0xff] ^ _aes_enc.t3[(t3 >> 24) ] ^ rk[8 +0]; s1 = _aes_enc.t0[(t1 ) & 0xff] ^ _aes_enc.t1[(t2 >> 8) & 0xff] ^ _aes_enc.t2[(t3 >> 16) & 0xff] ^ _aes_enc.t3[(t0 >> 24) ] ^ rk[8 +1]; s2 = _aes_enc.t0[(t2 ) & 0xff] ^ _aes_enc.t1[(t3 >> 8) & 0xff] ^ _aes_enc.t2[(t0 >> 16) & 0xff] ^ _aes_enc.t3[(t1 >> 24) ] ^ rk[8 +2]; s3 = _aes_enc.t0[(t3 ) & 0xff] ^ _aes_enc.t1[(t0 >> 8) & 0xff] ^ _aes_enc.t2[(t1 >> 16) & 0xff] ^ _aes_enc.t3[(t2 >> 24) ] ^ rk[8 +3];;
 t0 = _aes_enc.t0[(s0 ) & 0xff] ^ _aes_enc.t1[(s1 >> 8) & 0xff] ^ _aes_enc.t2[(s2 >> 16) & 0xff] ^ _aes_enc.t3[(s3 >> 24) ] ^ rk[12 +0]; t1 = _aes_enc.t0[(s1 ) & 0xff] ^ _aes_enc.t1[(s2 >> 8) & 0xff] ^ _aes_enc.t2[(s3 >> 16) & 0xff] ^ _aes_enc.t3[(s0 >> 24) ] ^ rk[12 +1]; t2 = _aes_enc.t0[(s2 ) & 0xff] ^ _aes_enc.t1[(s3 >> 8) & 0xff] ^ _aes_enc.t2[(s0 >> 16) & 0xff] ^ _aes_enc.t3[(s1 >> 24) ] ^ rk[12 +2]; t3 = _aes_enc.t0[(s3 ) & 0xff] ^ _aes_enc.t1[(s0 >> 8) & 0xff] ^ _aes_enc.t2[(s1 >> 16) & 0xff] ^ _aes_enc.t3[(s2 >> 24) ] ^ rk[12 +3];;
 s0 = _aes_enc.t0[(t0 ) & 0xff] ^ _aes_enc.t1[(t1 >> 8) & 0xff] ^ _aes_enc.t2[(t2 >> 16) & 0xff] ^ _aes_enc.t3[(t3 >> 24) ] ^ rk[16 +0]; s1 = _aes_enc.t0[(t1 ) & 0xff] ^ _aes_enc.t1[(t2 >> 8) & 0xff] ^ _aes_enc.t2[(t3 >> 16) & 0xff] ^ _aes_enc.t3[(t0 >> 24) ] ^ rk[16 +1]; s2 = _aes_enc.t0[(t2 ) & 0xff] ^ _aes_enc.t1[(t3 >> 8) & 0xff] ^ _aes_enc.t2[(t0 >> 16) & 0xff] ^ _aes_enc.t3[(t1 >> 24) ] ^ rk[16 +2]; s3 = _aes_enc.t0[(t3 ) & 0xff] ^ _aes_enc.t1[(t0 >> 8) & 0xff] ^ _aes_enc.t2[(t1 >> 16) & 0xff] ^ _aes_enc.t3[(t2 >> 24) ] ^ rk[16 +3];;
 t0 = _aes_enc.t0[(s0 ) & 0xff] ^ _aes_enc.t1[(s1 >> 8) & 0xff] ^ _aes_enc.t2[(s2 >> 16) & 0xff] ^ _aes_enc.t3[(s3 >> 24) ] ^ rk[20 +0]; t1 = _aes_enc.t0[(s1 ) & 0xff] ^ _aes_enc.t1[(s2 >> 8) & 0xff] ^ _aes_enc.t2[(s3 >> 16) & 0xff] ^ _aes_enc.t3[(s0 >> 24) ] ^ rk[20 +1]; t2 = _aes_enc.t0[(s2 ) & 0xff] ^ _aes_enc.t1[(s3 >> 8) & 0xff] ^ _aes_enc.t2[(s0 >> 16) & 0xff] ^ _aes_enc.t3[(s1 >> 24) ] ^ rk[20 +2]; t3 = _aes_enc.t0[(s3 ) & 0xff] ^ _aes_enc.t1[(s0 >> 8) & 0xff] ^ _aes_enc.t2[(s1 >> 16) & 0xff] ^ _aes_enc.t3[(s2 >> 24) ] ^ rk[20 +3];;
 s0 = _aes_enc.t0[(t0 ) & 0xff] ^ _aes_enc.t1[(t1 >> 8) & 0xff] ^ _aes_enc.t2[(t2 >> 16) & 0xff] ^ _aes_enc.t3[(t3 >> 24) ] ^ rk[24 +0]; s1 = _aes_enc.t0[(t1 ) & 0xff] ^ _aes_enc.t1[(t2 >> 8) & 0xff] ^ _aes_enc.t2[(t3 >> 16) & 0xff] ^ _aes_enc.t3[(t0 >> 24) ] ^ rk[24 +1]; s2 = _aes_enc.t0[(t2 ) & 0xff] ^ _aes_enc.t1[(t3 >> 8) & 0xff] ^ _aes_enc.t2[(t0 >> 16) & 0xff] ^ _aes_enc.t3[(t1 >> 24) ] ^ rk[24 +2]; s3 = _aes_enc.t0[(t3 ) & 0xff] ^ _aes_enc.t1[(t0 >> 8) & 0xff] ^ _aes_enc.t2[(t1 >> 16) & 0xff] ^ _aes_enc.t3[(t2 >> 24) ] ^ rk[24 +3];;
 t0 = _aes_enc.t0[(s0 ) & 0xff] ^ _aes_enc.t1[(s1 >> 8) & 0xff] ^ _aes_enc.t2[(s2 >> 16) & 0xff] ^ _aes_enc.t3[(s3 >> 24) ] ^ rk[28 +0]; t1 = _aes_enc.t0[(s1 ) & 0xff] ^ _aes_enc.t1[(s2 >> 8) & 0xff] ^ _aes_enc.t2[(s3 >> 16) & 0xff] ^ _aes_enc.t3[(s0 >> 24) ] ^ rk[28 +1]; t2 = _aes_enc.t0[(s2 ) & 0xff] ^ _aes_enc.t1[(s3 >> 8) & 0xff] ^ _aes_enc.t2[(s0 >> 16) & 0xff] ^ _aes_enc.t3[(s1 >> 24) ] ^ rk[28 +2]; t3 = _aes_enc.t0[(s3 ) & 0xff] ^ _aes_enc.t1[(s0 >> 8) & 0xff] ^ _aes_enc.t2[(s1 >> 16) & 0xff] ^ _aes_enc.t3[(s2 >> 24) ] ^ rk[28 +3];;
 s0 = _aes_enc.t0[(t0 ) & 0xff] ^ _aes_enc.t1[(t1 >> 8) & 0xff] ^ _aes_enc.t2[(t2 >> 16) & 0xff] ^ _aes_enc.t3[(t3 >> 24) ] ^ rk[32 +0]; s1 = _aes_enc.t0[(t1 ) & 0xff] ^ _aes_enc.t1[(t2 >> 8) & 0xff] ^ _aes_enc.t2[(t3 >> 16) & 0xff] ^ _aes_enc.t3[(t0 >> 24) ] ^ rk[32 +1]; s2 = _aes_enc.t0[(t2 ) & 0xff] ^ _aes_enc.t1[(t3 >> 8) & 0xff] ^ _aes_enc.t2[(t0 >> 16) & 0xff] ^ _aes_enc.t3[(t1 >> 24) ] ^ rk[32 +2]; s3 = _aes_enc.t0[(t3 ) & 0xff] ^ _aes_enc.t1[(t0 >> 8) & 0xff] ^ _aes_enc.t2[(t1 >> 16) & 0xff] ^ _aes_enc.t3[(t2 >> 24) ] ^ rk[32 +3];;
 t0 = _aes_enc.t0[(s0 ) & 0xff] ^ _aes_enc.t1[(s1 >> 8) & 0xff] ^ _aes_enc.t2[(s2 >> 16) & 0xff] ^ _aes_enc.t3[(s3 >> 24) ] ^ rk[36 +0]; t1 = _aes_enc.t0[(s1 ) & 0xff] ^ _aes_enc.t1[(s2 >> 8) & 0xff] ^ _aes_enc.t2[(s3 >> 16) & 0xff] ^ _aes_enc.t3[(s0 >> 24) ] ^ rk[36 +1]; t2 = _aes_enc.t0[(s2 ) & 0xff] ^ _aes_enc.t1[(s3 >> 8) & 0xff] ^ _aes_enc.t2[(s0 >> 16) & 0xff] ^ _aes_enc.t3[(s1 >> 24) ] ^ rk[36 +2]; t3 = _aes_enc.t0[(s3 ) & 0xff] ^ _aes_enc.t1[(s0 >> 8) & 0xff] ^ _aes_enc.t2[(s1 >> 16) & 0xff] ^ _aes_enc.t3[(s2 >> 24) ] ^ rk[36 +3];;

 if (ap->nr > 10)
 {
  s0 = _aes_enc.t0[(t0 ) & 0xff] ^ _aes_enc.t1[(t1 >> 8) & 0xff] ^ _aes_enc.t2[(t2 >> 16) & 0xff] ^ _aes_enc.t3[(t3 >> 24) ] ^ rk[40 +0]; s1 = _aes_enc.t0[(t1 ) & 0xff] ^ _aes_enc.t1[(t2 >> 8) & 0xff] ^ _aes_enc.t2[(t3 >> 16) & 0xff] ^ _aes_enc.t3[(t0 >> 24) ] ^ rk[40 +1]; s2 = _aes_enc.t0[(t2 ) & 0xff] ^ _aes_enc.t1[(t3 >> 8) & 0xff] ^ _aes_enc.t2[(t0 >> 16) & 0xff] ^ _aes_enc.t3[(t1 >> 24) ] ^ rk[40 +2]; s3 = _aes_enc.t0[(t3 ) & 0xff] ^ _aes_enc.t1[(t0 >> 8) & 0xff] ^ _aes_enc.t2[(t1 >> 16) & 0xff] ^ _aes_enc.t3[(t2 >> 24) ] ^ rk[40 +3];;
  t0 = _aes_enc.t0[(s0 ) & 0xff] ^ _aes_enc.t1[(s1 >> 8) & 0xff] ^ _aes_enc.t2[(s2 >> 16) & 0xff] ^ _aes_enc.t3[(s3 >> 24) ] ^ rk[44 +0]; t1 = _aes_enc.t0[(s1 ) & 0xff] ^ _aes_enc.t1[(s2 >> 8) & 0xff] ^ _aes_enc.t2[(s3 >> 16) & 0xff] ^ _aes_enc.t3[(s0 >> 24) ] ^ rk[44 +1]; t2 = _aes_enc.t0[(s2 ) & 0xff] ^ _aes_enc.t1[(s3 >> 8) & 0xff] ^ _aes_enc.t2[(s0 >> 16) & 0xff] ^ _aes_enc.t3[(s1 >> 24) ] ^ rk[44 +2]; t3 = _aes_enc.t0[(s3 ) & 0xff] ^ _aes_enc.t1[(s0 >> 8) & 0xff] ^ _aes_enc.t2[(s1 >> 16) & 0xff] ^ _aes_enc.t3[(s2 >> 24) ] ^ rk[44 +3];;
  if (ap->nr > 12)
  {
   s0 = _aes_enc.t0[(t0 ) & 0xff] ^ _aes_enc.t1[(t1 >> 8) & 0xff] ^ _aes_enc.t2[(t2 >> 16) & 0xff] ^ _aes_enc.t3[(t3 >> 24) ] ^ rk[48 +0]; s1 = _aes_enc.t0[(t1 ) & 0xff] ^ _aes_enc.t1[(t2 >> 8) & 0xff] ^ _aes_enc.t2[(t3 >> 16) & 0xff] ^ _aes_enc.t3[(t0 >> 24) ] ^ rk[48 +1]; s2 = _aes_enc.t0[(t2 ) & 0xff] ^ _aes_enc.t1[(t3 >> 8) & 0xff] ^ _aes_enc.t2[(t0 >> 16) & 0xff] ^ _aes_enc.t3[(t1 >> 24) ] ^ rk[48 +2]; s3 = _aes_enc.t0[(t3 ) & 0xff] ^ _aes_enc.t1[(t0 >> 8) & 0xff] ^ _aes_enc.t2[(t1 >> 16) & 0xff] ^ _aes_enc.t3[(t2 >> 24) ] ^ rk[48 +3];;
   t0 = _aes_enc.t0[(s0 ) & 0xff] ^ _aes_enc.t1[(s1 >> 8) & 0xff] ^ _aes_enc.t2[(s2 >> 16) & 0xff] ^ _aes_enc.t3[(s3 >> 24) ] ^ rk[52 +0]; t1 = _aes_enc.t0[(s1 ) & 0xff] ^ _aes_enc.t1[(s2 >> 8) & 0xff] ^ _aes_enc.t2[(s3 >> 16) & 0xff] ^ _aes_enc.t3[(s0 >> 24) ] ^ rk[52 +1]; t2 = _aes_enc.t0[(s2 ) & 0xff] ^ _aes_enc.t1[(s3 >> 8) & 0xff] ^ _aes_enc.t2[(s0 >> 16) & 0xff] ^ _aes_enc.t3[(s1 >> 24) ] ^ rk[52 +2]; t3 = _aes_enc.t0[(s3 ) & 0xff] ^ _aes_enc.t1[(s0 >> 8) & 0xff] ^ _aes_enc.t2[(s1 >> 16) & 0xff] ^ _aes_enc.t3[(s2 >> 24) ] ^ rk[52 +3];;
  }
 }

 rk += (ap->nr << 2);

 s0 = (_aes_enc.t4[(t0 ) & 0xff] & _aes_mask[0]) ^ (_aes_enc.t4[(t1 >> 8) & 0xff] & _aes_mask[1]) ^ (_aes_enc.t4[(t2 >> 16) & 0xff] & _aes_mask[2]) ^ (_aes_enc.t4[(t3 >> 24) ] & _aes_mask[3]) ^ rk[0]; s1 = (_aes_enc.t4[(t1 ) & 0xff] & _aes_mask[0]) ^ (_aes_enc.t4[(t2 >> 8) & 0xff] & _aes_mask[1]) ^ (_aes_enc.t4[(t3 >> 16) & 0xff] & _aes_mask[2]) ^ (_aes_enc.t4[(t0 >> 24) ] & _aes_mask[3]) ^ rk[1]; s2 = (_aes_enc.t4[(t2 ) & 0xff] & _aes_mask[0]) ^ (_aes_enc.t4[(t3 >> 8) & 0xff] & _aes_mask[1]) ^ (_aes_enc.t4[(t0 >> 16) & 0xff] & _aes_mask[2]) ^ (_aes_enc.t4[(t1 >> 24) ] & _aes_mask[3]) ^ rk[2]; s3 = (_aes_enc.t4[(t3 ) & 0xff] & _aes_mask[0]) ^ (_aes_enc.t4[(t0 >> 8) & 0xff] & _aes_mask[1]) ^ (_aes_enc.t4[(t1 >> 16) & 0xff] & _aes_mask[2]) ^ (_aes_enc.t4[(t2 >> 24) ] & _aes_mask[3]) ^ rk[3];;

 dst[0] = s0;
 dst[1] = s1;
 dst[2] = s2;
 dst[3] = s3;

 return 0;
}



int aesDecrypt(aesParam* ap, uint32_t* dst, const uint32_t* src)
{
 register uint32_t s0, s1, s2, s3;
 register uint32_t t0, t1, t2, t3;
 register uint32_t* rk = ap->k;

 s0 = src[0] ^ rk[0];
 s1 = src[1] ^ rk[1];
 s2 = src[2] ^ rk[2];
 s3 = src[3] ^ rk[3];

 t0 = _aes_dec.t0[(s0 ) & 0xff] ^ _aes_dec.t1[(s3 >> 8) & 0xff] ^ _aes_dec.t2[(s2 >> 16) & 0xff] ^ _aes_dec.t3[(s1 >> 24) ] ^ rk[4 +0]; t1 = _aes_dec.t0[(s1 ) & 0xff] ^ _aes_dec.t1[(s0 >> 8) & 0xff] ^ _aes_dec.t2[(s3 >> 16) & 0xff] ^ _aes_dec.t3[(s2 >> 24) ] ^ rk[4 +1]; t2 = _aes_dec.t0[(s2 ) & 0xff] ^ _aes_dec.t1[(s1 >> 8) & 0xff] ^ _aes_dec.t2[(s0 >> 16) & 0xff] ^ _aes_dec.t3[(s3 >> 24) ] ^ rk[4 +2]; t3 = _aes_dec.t0[(s3 ) & 0xff] ^ _aes_dec.t1[(s2 >> 8) & 0xff] ^ _aes_dec.t2[(s1 >> 16) & 0xff] ^ _aes_dec.t3[(s0 >> 24) ] ^ rk[4 +3];;
 s0 = _aes_dec.t0[(t0 ) & 0xff] ^ _aes_dec.t1[(t3 >> 8) & 0xff] ^ _aes_dec.t2[(t2 >> 16) & 0xff] ^ _aes_dec.t3[(t1 >> 24) ] ^ rk[8 +0]; s1 = _aes_dec.t0[(t1 ) & 0xff] ^ _aes_dec.t1[(t0 >> 8) & 0xff] ^ _aes_dec.t2[(t3 >> 16) & 0xff] ^ _aes_dec.t3[(t2 >> 24) ] ^ rk[8 +1]; s2 = _aes_dec.t0[(t2 ) & 0xff] ^ _aes_dec.t1[(t1 >> 8) & 0xff] ^ _aes_dec.t2[(t0 >> 16) & 0xff] ^ _aes_dec.t3[(t3 >> 24) ] ^ rk[8 +2]; s3 = _aes_dec.t0[(t3 ) & 0xff] ^ _aes_dec.t1[(t2 >> 8) & 0xff] ^ _aes_dec.t2[(t1 >> 16) & 0xff] ^ _aes_dec.t3[(t0 >> 24) ] ^ rk[8 +3];;
 t0 = _aes_dec.t0[(s0 ) & 0xff] ^ _aes_dec.t1[(s3 >> 8) & 0xff] ^ _aes_dec.t2[(s2 >> 16) & 0xff] ^ _aes_dec.t3[(s1 >> 24) ] ^ rk[12 +0]; t1 = _aes_dec.t0[(s1 ) & 0xff] ^ _aes_dec.t1[(s0 >> 8) & 0xff] ^ _aes_dec.t2[(s3 >> 16) & 0xff] ^ _aes_dec.t3[(s2 >> 24) ] ^ rk[12 +1]; t2 = _aes_dec.t0[(s2 ) & 0xff] ^ _aes_dec.t1[(s1 >> 8) & 0xff] ^ _aes_dec.t2[(s0 >> 16) & 0xff] ^ _aes_dec.t3[(s3 >> 24) ] ^ rk[12 +2]; t3 = _aes_dec.t0[(s3 ) & 0xff] ^ _aes_dec.t1[(s2 >> 8) & 0xff] ^ _aes_dec.t2[(s1 >> 16) & 0xff] ^ _aes_dec.t3[(s0 >> 24) ] ^ rk[12 +3];;
 s0 = _aes_dec.t0[(t0 ) & 0xff] ^ _aes_dec.t1[(t3 >> 8) & 0xff] ^ _aes_dec.t2[(t2 >> 16) & 0xff] ^ _aes_dec.t3[(t1 >> 24) ] ^ rk[16 +0]; s1 = _aes_dec.t0[(t1 ) & 0xff] ^ _aes_dec.t1[(t0 >> 8) & 0xff] ^ _aes_dec.t2[(t3 >> 16) & 0xff] ^ _aes_dec.t3[(t2 >> 24) ] ^ rk[16 +1]; s2 = _aes_dec.t0[(t2 ) & 0xff] ^ _aes_dec.t1[(t1 >> 8) & 0xff] ^ _aes_dec.t2[(t0 >> 16) & 0xff] ^ _aes_dec.t3[(t3 >> 24) ] ^ rk[16 +2]; s3 = _aes_dec.t0[(t3 ) & 0xff] ^ _aes_dec.t1[(t2 >> 8) & 0xff] ^ _aes_dec.t2[(t1 >> 16) & 0xff] ^ _aes_dec.t3[(t0 >> 24) ] ^ rk[16 +3];;
 t0 = _aes_dec.t0[(s0 ) & 0xff] ^ _aes_dec.t1[(s3 >> 8) & 0xff] ^ _aes_dec.t2[(s2 >> 16) & 0xff] ^ _aes_dec.t3[(s1 >> 24) ] ^ rk[20 +0]; t1 = _aes_dec.t0[(s1 ) & 0xff] ^ _aes_dec.t1[(s0 >> 8) & 0xff] ^ _aes_dec.t2[(s3 >> 16) & 0xff] ^ _aes_dec.t3[(s2 >> 24) ] ^ rk[20 +1]; t2 = _aes_dec.t0[(s2 ) & 0xff] ^ _aes_dec.t1[(s1 >> 8) & 0xff] ^ _aes_dec.t2[(s0 >> 16) & 0xff] ^ _aes_dec.t3[(s3 >> 24) ] ^ rk[20 +2]; t3 = _aes_dec.t0[(s3 ) & 0xff] ^ _aes_dec.t1[(s2 >> 8) & 0xff] ^ _aes_dec.t2[(s1 >> 16) & 0xff] ^ _aes_dec.t3[(s0 >> 24) ] ^ rk[20 +3];;
 s0 = _aes_dec.t0[(t0 ) & 0xff] ^ _aes_dec.t1[(t3 >> 8) & 0xff] ^ _aes_dec.t2[(t2 >> 16) & 0xff] ^ _aes_dec.t3[(t1 >> 24) ] ^ rk[24 +0]; s1 = _aes_dec.t0[(t1 ) & 0xff] ^ _aes_dec.t1[(t0 >> 8) & 0xff] ^ _aes_dec.t2[(t3 >> 16) & 0xff] ^ _aes_dec.t3[(t2 >> 24) ] ^ rk[24 +1]; s2 = _aes_dec.t0[(t2 ) & 0xff] ^ _aes_dec.t1[(t1 >> 8) & 0xff] ^ _aes_dec.t2[(t0 >> 16) & 0xff] ^ _aes_dec.t3[(t3 >> 24) ] ^ rk[24 +2]; s3 = _aes_dec.t0[(t3 ) & 0xff] ^ _aes_dec.t1[(t2 >> 8) & 0xff] ^ _aes_dec.t2[(t1 >> 16) & 0xff] ^ _aes_dec.t3[(t0 >> 24) ] ^ rk[24 +3];;
 t0 = _aes_dec.t0[(s0 ) & 0xff] ^ _aes_dec.t1[(s3 >> 8) & 0xff] ^ _aes_dec.t2[(s2 >> 16) & 0xff] ^ _aes_dec.t3[(s1 >> 24) ] ^ rk[28 +0]; t1 = _aes_dec.t0[(s1 ) & 0xff] ^ _aes_dec.t1[(s0 >> 8) & 0xff] ^ _aes_dec.t2[(s3 >> 16) & 0xff] ^ _aes_dec.t3[(s2 >> 24) ] ^ rk[28 +1]; t2 = _aes_dec.t0[(s2 ) & 0xff] ^ _aes_dec.t1[(s1 >> 8) & 0xff] ^ _aes_dec.t2[(s0 >> 16) & 0xff] ^ _aes_dec.t3[(s3 >> 24) ] ^ rk[28 +2]; t3 = _aes_dec.t0[(s3 ) & 0xff] ^ _aes_dec.t1[(s2 >> 8) & 0xff] ^ _aes_dec.t2[(s1 >> 16) & 0xff] ^ _aes_dec.t3[(s0 >> 24) ] ^ rk[28 +3];;
 s0 = _aes_dec.t0[(t0 ) & 0xff] ^ _aes_dec.t1[(t3 >> 8) & 0xff] ^ _aes_dec.t2[(t2 >> 16) & 0xff] ^ _aes_dec.t3[(t1 >> 24) ] ^ rk[32 +0]; s1 = _aes_dec.t0[(t1 ) & 0xff] ^ _aes_dec.t1[(t0 >> 8) & 0xff] ^ _aes_dec.t2[(t3 >> 16) & 0xff] ^ _aes_dec.t3[(t2 >> 24) ] ^ rk[32 +1]; s2 = _aes_dec.t0[(t2 ) & 0xff] ^ _aes_dec.t1[(t1 >> 8) & 0xff] ^ _aes_dec.t2[(t0 >> 16) & 0xff] ^ _aes_dec.t3[(t3 >> 24) ] ^ rk[32 +2]; s3 = _aes_dec.t0[(t3 ) & 0xff] ^ _aes_dec.t1[(t2 >> 8) & 0xff] ^ _aes_dec.t2[(t1 >> 16) & 0xff] ^ _aes_dec.t3[(t0 >> 24) ] ^ rk[32 +3];;
 t0 = _aes_dec.t0[(s0 ) & 0xff] ^ _aes_dec.t1[(s3 >> 8) & 0xff] ^ _aes_dec.t2[(s2 >> 16) & 0xff] ^ _aes_dec.t3[(s1 >> 24) ] ^ rk[36 +0]; t1 = _aes_dec.t0[(s1 ) & 0xff] ^ _aes_dec.t1[(s0 >> 8) & 0xff] ^ _aes_dec.t2[(s3 >> 16) & 0xff] ^ _aes_dec.t3[(s2 >> 24) ] ^ rk[36 +1]; t2 = _aes_dec.t0[(s2 ) & 0xff] ^ _aes_dec.t1[(s1 >> 8) & 0xff] ^ _aes_dec.t2[(s0 >> 16) & 0xff] ^ _aes_dec.t3[(s3 >> 24) ] ^ rk[36 +2]; t3 = _aes_dec.t0[(s3 ) & 0xff] ^ _aes_dec.t1[(s2 >> 8) & 0xff] ^ _aes_dec.t2[(s1 >> 16) & 0xff] ^ _aes_dec.t3[(s0 >> 24) ] ^ rk[36 +3];;

 if (ap->nr > 10)
 {
  s0 = _aes_dec.t0[(t0 ) & 0xff] ^ _aes_dec.t1[(t3 >> 8) & 0xff] ^ _aes_dec.t2[(t2 >> 16) & 0xff] ^ _aes_dec.t3[(t1 >> 24) ] ^ rk[40 +0]; s1 = _aes_dec.t0[(t1 ) & 0xff] ^ _aes_dec.t1[(t0 >> 8) & 0xff] ^ _aes_dec.t2[(t3 >> 16) & 0xff] ^ _aes_dec.t3[(t2 >> 24) ] ^ rk[40 +1]; s2 = _aes_dec.t0[(t2 ) & 0xff] ^ _aes_dec.t1[(t1 >> 8) & 0xff] ^ _aes_dec.t2[(t0 >> 16) & 0xff] ^ _aes_dec.t3[(t3 >> 24) ] ^ rk[40 +2]; s3 = _aes_dec.t0[(t3 ) & 0xff] ^ _aes_dec.t1[(t2 >> 8) & 0xff] ^ _aes_dec.t2[(t1 >> 16) & 0xff] ^ _aes_dec.t3[(t0 >> 24) ] ^ rk[40 +3];;
  t0 = _aes_dec.t0[(s0 ) & 0xff] ^ _aes_dec.t1[(s3 >> 8) & 0xff] ^ _aes_dec.t2[(s2 >> 16) & 0xff] ^ _aes_dec.t3[(s1 >> 24) ] ^ rk[44 +0]; t1 = _aes_dec.t0[(s1 ) & 0xff] ^ _aes_dec.t1[(s0 >> 8) & 0xff] ^ _aes_dec.t2[(s3 >> 16) & 0xff] ^ _aes_dec.t3[(s2 >> 24) ] ^ rk[44 +1]; t2 = _aes_dec.t0[(s2 ) & 0xff] ^ _aes_dec.t1[(s1 >> 8) & 0xff] ^ _aes_dec.t2[(s0 >> 16) & 0xff] ^ _aes_dec.t3[(s3 >> 24) ] ^ rk[44 +2]; t3 = _aes_dec.t0[(s3 ) & 0xff] ^ _aes_dec.t1[(s2 >> 8) & 0xff] ^ _aes_dec.t2[(s1 >> 16) & 0xff] ^ _aes_dec.t3[(s0 >> 24) ] ^ rk[44 +3];;
  if (ap->nr > 12)
  {
   s0 = _aes_dec.t0[(t0 ) & 0xff] ^ _aes_dec.t1[(t3 >> 8) & 0xff] ^ _aes_dec.t2[(t2 >> 16) & 0xff] ^ _aes_dec.t3[(t1 >> 24) ] ^ rk[48 +0]; s1 = _aes_dec.t0[(t1 ) & 0xff] ^ _aes_dec.t1[(t0 >> 8) & 0xff] ^ _aes_dec.t2[(t3 >> 16) & 0xff] ^ _aes_dec.t3[(t2 >> 24) ] ^ rk[48 +1]; s2 = _aes_dec.t0[(t2 ) & 0xff] ^ _aes_dec.t1[(t1 >> 8) & 0xff] ^ _aes_dec.t2[(t0 >> 16) & 0xff] ^ _aes_dec.t3[(t3 >> 24) ] ^ rk[48 +2]; s3 = _aes_dec.t0[(t3 ) & 0xff] ^ _aes_dec.t1[(t2 >> 8) & 0xff] ^ _aes_dec.t2[(t1 >> 16) & 0xff] ^ _aes_dec.t3[(t0 >> 24) ] ^ rk[48 +3];;
   t0 = _aes_dec.t0[(s0 ) & 0xff] ^ _aes_dec.t1[(s3 >> 8) & 0xff] ^ _aes_dec.t2[(s2 >> 16) & 0xff] ^ _aes_dec.t3[(s1 >> 24) ] ^ rk[52 +0]; t1 = _aes_dec.t0[(s1 ) & 0xff] ^ _aes_dec.t1[(s0 >> 8) & 0xff] ^ _aes_dec.t2[(s3 >> 16) & 0xff] ^ _aes_dec.t3[(s2 >> 24) ] ^ rk[52 +1]; t2 = _aes_dec.t0[(s2 ) & 0xff] ^ _aes_dec.t1[(s1 >> 8) & 0xff] ^ _aes_dec.t2[(s0 >> 16) & 0xff] ^ _aes_dec.t3[(s3 >> 24) ] ^ rk[52 +2]; t3 = _aes_dec.t0[(s3 ) & 0xff] ^ _aes_dec.t1[(s2 >> 8) & 0xff] ^ _aes_dec.t2[(s1 >> 16) & 0xff] ^ _aes_dec.t3[(s0 >> 24) ] ^ rk[52 +3];;
  }
 }

 rk += (ap->nr << 2);

 s0 = (_aes_dec.t4[(t0 ) & 0xff] & 0x000000ff) ^ (_aes_dec.t4[(t3 >> 8) & 0xff] & 0x0000ff00) ^ (_aes_dec.t4[(t2 >> 16) & 0xff] & 0x00ff0000) ^ (_aes_dec.t4[(t1 >> 24) ] & 0xff000000) ^ rk[0]; s1 = (_aes_dec.t4[(t1 ) & 0xff] & 0x000000ff) ^ (_aes_dec.t4[(t0 >> 8) & 0xff] & 0x0000ff00) ^ (_aes_dec.t4[(t3 >> 16) & 0xff] & 0x00ff0000) ^ (_aes_dec.t4[(t2 >> 24) ] & 0xff000000) ^ rk[1]; s2 = (_aes_dec.t4[(t2 ) & 0xff] & 0x000000ff) ^ (_aes_dec.t4[(t1 >> 8) & 0xff] & 0x0000ff00) ^ (_aes_dec.t4[(t0 >> 16) & 0xff] & 0x00ff0000) ^ (_aes_dec.t4[(t3 >> 24) ] & 0xff000000) ^ rk[2]; s3 = (_aes_dec.t4[(t3 ) & 0xff] & 0x000000ff) ^ (_aes_dec.t4[(t2 >> 8) & 0xff] & 0x0000ff00) ^ (_aes_dec.t4[(t1 >> 16) & 0xff] & 0x00ff0000) ^ (_aes_dec.t4[(t0 >> 24) ] & 0xff000000) ^ rk[3];;

 dst[0] = s0;
 dst[1] = s1;
 dst[2] = s2;
 dst[3] = s3;

 return 0;
}


uint32_t* aesFeedback(aesParam* ap)
{
 return ap->fdback;
}
