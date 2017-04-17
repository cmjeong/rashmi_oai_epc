typedef void *Ptr;
typedef unsigned char Bool;


typedef char S8;




typedef unsigned char U8;

typedef short S16;
typedef unsigned short U16;


typedef long S32;
typedef unsigned long U32;





__extension__ typedef long long S64;
__extension__ typedef unsigned long long U64;
typedef float F32;
typedef double F64;
typedef void Void;



typedef S8 (*PFS8) (void );
typedef S16 (*PFS16) (void );
typedef S32 (*PFS32) (void );
typedef Void (*PFVOID) (void );
typedef Void ( *PIF) (void );
typedef U32 MFTYPE;




typedef S8 *ARGTYPE;









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





typedef __off_t off_t;






typedef __off64_t off64_t;
typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
typedef __useconds_t useconds_t;



typedef __suseconds_t suseconds_t;








typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


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







typedef union
{
  char __size[16];
  long int __align;
} sem_t;






extern int sem_init (sem_t *__sem, int __pshared, unsigned int __value)
     __attribute__ ((__nothrow__ , __leaf__));

extern int sem_destroy (sem_t *__sem) __attribute__ ((__nothrow__ , __leaf__));


extern sem_t *sem_open (const char *__name, int __oflag, ...) __attribute__ ((__nothrow__ , __leaf__));


extern int sem_close (sem_t *__sem) __attribute__ ((__nothrow__ , __leaf__));


extern int sem_unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__));





extern int sem_wait (sem_t *__sem);






extern int sem_timedwait (sem_t *__restrict __sem,
     const struct timespec *__restrict __abstime);



extern int sem_trywait (sem_t *__sem) __attribute__ ((__nothrow__));


extern int sem_post (sem_t *__sem) __attribute__ ((__nothrow__));


extern int sem_getvalue (sem_t *__restrict __sem, int *__restrict __sval)
     __attribute__ ((__nothrow__ , __leaf__));







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
   if (__c == 
             (-1)
                )
     break;
   *__cptr++ = __c;
 }
      return (__cptr - (char *) __ptr) / __size;
    }

  return __fread_unlocked_alias (__ptr, __size, __n, __stream);
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




extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__warn_unused_result__));

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__warn_unused_result__));






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







struct iovec
  {
    void *iov_base;
    size_t iov_len;
  };



extern ssize_t process_vm_readv (pid_t __pid, const struct iovec *__lvec,
     unsigned long int __liovcnt,
     const struct iovec *__rvec,
     unsigned long int __riovcnt,
     unsigned long int __flags)
  __attribute__ ((__nothrow__ , __leaf__));


extern ssize_t process_vm_writev (pid_t __pid, const struct iovec *__lvec,
      unsigned long int __liovcnt,
      const struct iovec *__rvec,
      unsigned long int __riovcnt,
      unsigned long int __flags)
  __attribute__ ((__nothrow__ , __leaf__));


extern ssize_t readv (int __fd, const struct iovec *__iovec, int __count)
  __attribute__ ((__warn_unused_result__));
extern ssize_t writev (int __fd, const struct iovec *__iovec, int __count)
  __attribute__ ((__warn_unused_result__));
extern ssize_t preadv (int __fd, const struct iovec *__iovec, int __count,
         __off_t __offset) __attribute__ ((__warn_unused_result__));
extern ssize_t pwritev (int __fd, const struct iovec *__iovec, int __count,
   __off_t __offset) __attribute__ ((__warn_unused_result__));
extern ssize_t preadv64 (int __fd, const struct iovec *__iovec, int __count,
    __off64_t __offset) __attribute__ ((__warn_unused_result__));
extern ssize_t pwritev64 (int __fd, const struct iovec *__iovec, int __count,
     __off64_t __offset) __attribute__ ((__warn_unused_result__));


















typedef __socklen_t socklen_t;




enum __socket_type
{
  SOCK_STREAM = 1,


  SOCK_DGRAM = 2,


  SOCK_RAW = 3,

  SOCK_RDM = 4,

  SOCK_SEQPACKET = 5,


  SOCK_DCCP = 6,

  SOCK_PACKET = 10,







  SOCK_CLOEXEC = 02000000,


  SOCK_NONBLOCK = 00004000


};
typedef unsigned short int sa_family_t;


struct sockaddr
  {
    sa_family_t sa_family;
    char sa_data[14];
  };
struct sockaddr_storage
  {
    sa_family_t ss_family;
    char __ss_padding[(128 - (sizeof (unsigned short int)) - sizeof (unsigned long int))];
    unsigned long int __ss_align;
  };



enum
  {
    MSG_OOB = 0x01,

    MSG_PEEK = 0x02,

    MSG_DONTROUTE = 0x04,



    MSG_TRYHARD = MSG_DONTROUTE,


    MSG_CTRUNC = 0x08,

    MSG_PROXY = 0x10,

    MSG_TRUNC = 0x20,

    MSG_DONTWAIT = 0x40,

    MSG_EOR = 0x80,

    MSG_WAITALL = 0x100,

    MSG_FIN = 0x200,

    MSG_SYN = 0x400,

    MSG_CONFIRM = 0x800,

    MSG_RST = 0x1000,

    MSG_ERRQUEUE = 0x2000,

    MSG_NOSIGNAL = 0x4000,

    MSG_MORE = 0x8000,

    MSG_WAITFORONE = 0x10000,

    MSG_BATCH = 0x40000,

    MSG_FASTOPEN = 0x20000000,


    MSG_CMSG_CLOEXEC = 0x40000000



  };




struct msghdr
  {
    void *msg_name;
    socklen_t msg_namelen;

    struct iovec *msg_iov;
    size_t msg_iovlen;

    void *msg_control;
    size_t msg_controllen;




    int msg_flags;
  };


struct cmsghdr
  {
    size_t cmsg_len;




    int cmsg_level;
    int cmsg_type;

    __extension__ unsigned char __cmsg_data [];

  };
extern struct cmsghdr *__cmsg_nxthdr (struct msghdr *__mhdr,
          struct cmsghdr *__cmsg) __attribute__ ((__nothrow__ , __leaf__));




extern __inline __attribute__ ((__gnu_inline__)) struct cmsghdr *
__attribute__ ((__nothrow__ , __leaf__)) __cmsg_nxthdr (struct msghdr *__mhdr, struct cmsghdr *__cmsg)
{
  if ((size_t) __cmsg->cmsg_len < sizeof (struct cmsghdr))

    return (struct cmsghdr *) 0;

  __cmsg = (struct cmsghdr *) ((unsigned char *) __cmsg
          + (((__cmsg->cmsg_len) + sizeof (size_t) - 1) & (size_t) ~(sizeof (size_t) - 1)));
  if ((unsigned char *) (__cmsg + 1) > ((unsigned char *) __mhdr->msg_control
     + __mhdr->msg_controllen)
      || ((unsigned char *) __cmsg + (((__cmsg->cmsg_len) + sizeof (size_t) - 1) & (size_t) ~(sizeof (size_t) - 1))
   > ((unsigned char *) __mhdr->msg_control + __mhdr->msg_controllen)))

    return (struct cmsghdr *) 0;
  return __cmsg;
}




enum
  {
    SCM_RIGHTS = 0x01


    , SCM_CREDENTIALS = 0x02


  };



struct ucred
{
  pid_t pid;
  uid_t uid;
  gid_t gid;
};



struct linger
  {
    int l_onoff;
    int l_linger;
  };




struct osockaddr
  {
    unsigned short int sa_family;
    unsigned char sa_data[14];
  };




enum
{
  SHUT_RD = 0,

  SHUT_WR,

  SHUT_RDWR

};
typedef union { struct sockaddr *__restrict __sockaddr__; struct sockaddr_at *__restrict __sockaddr_at__; struct sockaddr_ax25 *__restrict __sockaddr_ax25__; struct sockaddr_dl *__restrict __sockaddr_dl__; struct sockaddr_eon *__restrict __sockaddr_eon__; struct sockaddr_in *__restrict __sockaddr_in__; struct sockaddr_in6 *__restrict __sockaddr_in6__; struct sockaddr_inarp *__restrict __sockaddr_inarp__; struct sockaddr_ipx *__restrict __sockaddr_ipx__; struct sockaddr_iso *__restrict __sockaddr_iso__; struct sockaddr_ns *__restrict __sockaddr_ns__; struct sockaddr_un *__restrict __sockaddr_un__; struct sockaddr_x25 *__restrict __sockaddr_x25__;
       } __SOCKADDR_ARG __attribute__ ((__transparent_union__));


typedef union { const struct sockaddr *__restrict __sockaddr__; const struct sockaddr_at *__restrict __sockaddr_at__; const struct sockaddr_ax25 *__restrict __sockaddr_ax25__; const struct sockaddr_dl *__restrict __sockaddr_dl__; const struct sockaddr_eon *__restrict __sockaddr_eon__; const struct sockaddr_in *__restrict __sockaddr_in__; const struct sockaddr_in6 *__restrict __sockaddr_in6__; const struct sockaddr_inarp *__restrict __sockaddr_inarp__; const struct sockaddr_ipx *__restrict __sockaddr_ipx__; const struct sockaddr_iso *__restrict __sockaddr_iso__; const struct sockaddr_ns *__restrict __sockaddr_ns__; const struct sockaddr_un *__restrict __sockaddr_un__; const struct sockaddr_x25 *__restrict __sockaddr_x25__;
       } __CONST_SOCKADDR_ARG __attribute__ ((__transparent_union__));





struct mmsghdr
  {
    struct msghdr msg_hdr;
    unsigned int msg_len;

  };






extern int socket (int __domain, int __type, int __protocol) __attribute__ ((__nothrow__ , __leaf__));





extern int socketpair (int __domain, int __type, int __protocol,
         int __fds[2]) __attribute__ ((__nothrow__ , __leaf__));


extern int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)
     __attribute__ ((__nothrow__ , __leaf__));


extern int getsockname (int __fd, __SOCKADDR_ARG __addr,
   socklen_t *__restrict __len) __attribute__ ((__nothrow__ , __leaf__));
extern int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);



extern int getpeername (int __fd, __SOCKADDR_ARG __addr,
   socklen_t *__restrict __len) __attribute__ ((__nothrow__ , __leaf__));






extern ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);






extern ssize_t recv (int __fd, void *__buf, size_t __n, int __flags);






extern ssize_t sendto (int __fd, const void *__buf, size_t __n,
         int __flags, __CONST_SOCKADDR_ARG __addr,
         socklen_t __addr_len);
extern ssize_t recvfrom (int __fd, void *__restrict __buf, size_t __n,
    int __flags, __SOCKADDR_ARG __addr,
    socklen_t *__restrict __addr_len);







extern ssize_t sendmsg (int __fd, const struct msghdr *__message,
   int __flags);







extern int sendmmsg (int __fd, struct mmsghdr *__vmessages,
       unsigned int __vlen, int __flags);







extern ssize_t recvmsg (int __fd, struct msghdr *__message, int __flags);







extern int recvmmsg (int __fd, struct mmsghdr *__vmessages,
       unsigned int __vlen, int __flags,
       struct timespec *__tmo);






extern int getsockopt (int __fd, int __level, int __optname,
         void *__restrict __optval,
         socklen_t *__restrict __optlen) __attribute__ ((__nothrow__ , __leaf__));




extern int setsockopt (int __fd, int __level, int __optname,
         const void *__optval, socklen_t __optlen) __attribute__ ((__nothrow__ , __leaf__));





extern int listen (int __fd, int __n) __attribute__ ((__nothrow__ , __leaf__));
extern int accept (int __fd, __SOCKADDR_ARG __addr,
     socklen_t *__restrict __addr_len);






extern int accept4 (int __fd, __SOCKADDR_ARG __addr,
      socklen_t *__restrict __addr_len, int __flags);
extern int shutdown (int __fd, int __how) __attribute__ ((__nothrow__ , __leaf__));




extern int sockatmark (int __fd) __attribute__ ((__nothrow__ , __leaf__));







extern int isfdtype (int __fd, int __fdtype) __attribute__ ((__nothrow__ , __leaf__));





extern ssize_t __recv_chk (int __fd, void *__buf, size_t __n, size_t __buflen,
      int __flags);
extern ssize_t __recv_alias (int __fd, void *__buf, size_t __n, int __flags) __asm__ ("" "recv")
                          ;
extern ssize_t __recv_chk_warn (int __fd, void *__buf, size_t __n, size_t __buflen, int __flags) __asm__ ("" "__recv_chk")


     __attribute__((__warning__ ("recv called with bigger length than size of destination " "buffer")))
            ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) ssize_t
recv (int __fd, void *__buf, size_t __n, int __flags)
{
  if (__builtin_object_size (__buf, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__n))
 return __recv_chk (__fd, __buf, __n, __builtin_object_size (__buf, 0), __flags);

      if (__n > __builtin_object_size (__buf, 0))
 return __recv_chk_warn (__fd, __buf, __n, __builtin_object_size (__buf, 0), __flags);
    }
  return __recv_alias (__fd, __buf, __n, __flags);
}

extern ssize_t __recvfrom_chk (int __fd, void *__restrict __buf, size_t __n,
          size_t __buflen, int __flags,
          __SOCKADDR_ARG __addr,
          socklen_t *__restrict __addr_len);
extern ssize_t __recvfrom_alias (int __fd, void *__restrict __buf, size_t __n, int __flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) __asm__ ("" "recvfrom")


                                                   ;
extern ssize_t __recvfrom_chk_warn (int __fd, void *__restrict __buf, size_t __n, size_t __buflen, int __flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) __asm__ ("" "__recvfrom_chk")




     __attribute__((__warning__ ("recvfrom called with bigger length than size of " "destination buffer")))
                        ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) ssize_t
recvfrom (int __fd, void *__restrict __buf, size_t __n, int __flags,
   __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len)
{
  if (__builtin_object_size (__buf, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__n))
 return __recvfrom_chk (__fd, __buf, __n, __builtin_object_size (__buf, 0), __flags,
          __addr, __addr_len);
      if (__n > __builtin_object_size (__buf, 0))
 return __recvfrom_chk_warn (__fd, __buf, __n, __builtin_object_size (__buf, 0), __flags,
        __addr, __addr_len);
    }
  return __recvfrom_alias (__fd, __buf, __n, __flags, __addr, __addr_len);
}



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







typedef uint32_t in_addr_t;
struct in_addr
  {
    in_addr_t s_addr;
  };


struct ip_opts
  {
    struct in_addr ip_dst;
    char ip_opts[40];
  };


struct ip_mreqn
  {
    struct in_addr imr_multiaddr;
    struct in_addr imr_address;
    int imr_ifindex;
  };


struct in_pktinfo
  {
    int ipi_ifindex;
    struct in_addr ipi_spec_dst;
    struct in_addr ipi_addr;
  };


enum
  {
    IPPROTO_IP = 0,

    IPPROTO_ICMP = 1,

    IPPROTO_IGMP = 2,

    IPPROTO_IPIP = 4,

    IPPROTO_TCP = 6,

    IPPROTO_EGP = 8,

    IPPROTO_PUP = 12,

    IPPROTO_UDP = 17,

    IPPROTO_IDP = 22,

    IPPROTO_TP = 29,

    IPPROTO_DCCP = 33,

    IPPROTO_IPV6 = 41,

    IPPROTO_RSVP = 46,

    IPPROTO_GRE = 47,

    IPPROTO_ESP = 50,

    IPPROTO_AH = 51,

    IPPROTO_MTP = 92,

    IPPROTO_BEETPH = 94,

    IPPROTO_ENCAP = 98,

    IPPROTO_PIM = 103,

    IPPROTO_COMP = 108,

    IPPROTO_SCTP = 132,

    IPPROTO_UDPLITE = 136,

    IPPROTO_MPLS = 137,

    IPPROTO_RAW = 255,

    IPPROTO_MAX
  };





enum
  {
    IPPROTO_HOPOPTS = 0,

    IPPROTO_ROUTING = 43,

    IPPROTO_FRAGMENT = 44,

    IPPROTO_ICMPV6 = 58,

    IPPROTO_NONE = 59,

    IPPROTO_DSTOPTS = 60,

    IPPROTO_MH = 135

  };



typedef uint16_t in_port_t;


enum
  {
    IPPORT_ECHO = 7,
    IPPORT_DISCARD = 9,
    IPPORT_SYSTAT = 11,
    IPPORT_DAYTIME = 13,
    IPPORT_NETSTAT = 15,
    IPPORT_FTP = 21,
    IPPORT_TELNET = 23,
    IPPORT_SMTP = 25,
    IPPORT_TIMESERVER = 37,
    IPPORT_NAMESERVER = 42,
    IPPORT_WHOIS = 43,
    IPPORT_MTP = 57,

    IPPORT_TFTP = 69,
    IPPORT_RJE = 77,
    IPPORT_FINGER = 79,
    IPPORT_TTYLINK = 87,
    IPPORT_SUPDUP = 95,


    IPPORT_EXECSERVER = 512,
    IPPORT_LOGINSERVER = 513,
    IPPORT_CMDSERVER = 514,
    IPPORT_EFSSERVER = 520,


    IPPORT_BIFFUDP = 512,
    IPPORT_WHOSERVER = 513,
    IPPORT_ROUTESERVER = 520,


    IPPORT_RESERVED = 1024,


    IPPORT_USERRESERVED = 5000
  };
struct in6_addr
  {
    union
      {
 uint8_t __u6_addr8[16];

 uint16_t __u6_addr16[8];
 uint32_t __u6_addr32[4];

      } __in6_u;





  };


extern const struct in6_addr in6addr_any;
extern const struct in6_addr in6addr_loopback;
struct sockaddr_in
  {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;


    unsigned char sin_zero[sizeof (struct sockaddr) -
      (sizeof (unsigned short int)) -
      sizeof (in_port_t) -
      sizeof (struct in_addr)];
  };



struct sockaddr_in6
  {
    sa_family_t sin6_family;
    in_port_t sin6_port;
    uint32_t sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t sin6_scope_id;
  };




struct ip_mreq
  {

    struct in_addr imr_multiaddr;


    struct in_addr imr_interface;
  };

struct ip_mreq_source
  {

    struct in_addr imr_multiaddr;


    struct in_addr imr_interface;


    struct in_addr imr_sourceaddr;
  };




struct ipv6_mreq
  {

    struct in6_addr ipv6mr_multiaddr;


    unsigned int ipv6mr_interface;
  };




struct group_req
  {

    uint32_t gr_interface;


    struct sockaddr_storage gr_group;
  };

struct group_source_req
  {

    uint32_t gsr_interface;


    struct sockaddr_storage gsr_group;


    struct sockaddr_storage gsr_source;
  };



struct ip_msfilter
  {

    struct in_addr imsf_multiaddr;


    struct in_addr imsf_interface;


    uint32_t imsf_fmode;


    uint32_t imsf_numsrc;

    struct in_addr imsf_slist[1];
  };





struct group_filter
  {

    uint32_t gf_interface;


    struct sockaddr_storage gf_group;


    uint32_t gf_fmode;


    uint32_t gf_numsrc;

    struct sockaddr_storage gf_slist[1];
};
extern uint32_t ntohl (uint32_t __netlong) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern uint16_t ntohs (uint16_t __netshort)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern uint32_t htonl (uint32_t __hostlong)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern uint16_t htons (uint16_t __hostshort)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int bindresvport (int __sockfd, struct sockaddr_in *__sock_in) __attribute__ ((__nothrow__ , __leaf__));


extern int bindresvport6 (int __sockfd, struct sockaddr_in6 *__sock_in)
     __attribute__ ((__nothrow__ , __leaf__));
struct cmsghdr;



struct in6_pktinfo
  {
    struct in6_addr ipi6_addr;
    unsigned int ipi6_ifindex;
  };


struct ip6_mtuinfo
  {
    struct sockaddr_in6 ip6m_addr;
    uint32_t ip6m_mtu;
  };



extern int inet6_option_space (int __nbytes)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
extern int inet6_option_init (void *__bp, struct cmsghdr **__cmsgp,
         int __type) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
extern int inet6_option_append (struct cmsghdr *__cmsg,
    const uint8_t *__typep, int __multx,
    int __plusy) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
extern uint8_t *inet6_option_alloc (struct cmsghdr *__cmsg, int __datalen,
        int __multx, int __plusy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
extern int inet6_option_next (const struct cmsghdr *__cmsg,
         uint8_t **__tptrp)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
extern int inet6_option_find (const struct cmsghdr *__cmsg,
         uint8_t **__tptrp, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));



extern int inet6_opt_init (void *__extbuf, socklen_t __extlen) __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_opt_append (void *__extbuf, socklen_t __extlen, int __offset,
        uint8_t __type, socklen_t __len, uint8_t __align,
        void **__databufp) __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_opt_finish (void *__extbuf, socklen_t __extlen, int __offset)
     __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_opt_set_val (void *__databuf, int __offset, void *__val,
         socklen_t __vallen) __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_opt_next (void *__extbuf, socklen_t __extlen, int __offset,
      uint8_t *__typep, socklen_t *__lenp,
      void **__databufp) __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_opt_find (void *__extbuf, socklen_t __extlen, int __offset,
      uint8_t __type, socklen_t *__lenp,
      void **__databufp) __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_opt_get_val (void *__databuf, int __offset, void *__val,
         socklen_t __vallen) __attribute__ ((__nothrow__ , __leaf__));



extern socklen_t inet6_rth_space (int __type, int __segments) __attribute__ ((__nothrow__ , __leaf__));
extern void *inet6_rth_init (void *__bp, socklen_t __bp_len, int __type,
        int __segments) __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_rth_add (void *__bp, const struct in6_addr *__addr) __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_rth_reverse (const void *__in, void *__out) __attribute__ ((__nothrow__ , __leaf__));
extern int inet6_rth_segments (const void *__bp) __attribute__ ((__nothrow__ , __leaf__));
extern struct in6_addr *inet6_rth_getaddr (const void *__bp, int __index)
     __attribute__ ((__nothrow__ , __leaf__));





extern int getipv4sourcefilter (int __s, struct in_addr __interface_addr,
    struct in_addr __group, uint32_t *__fmode,
    uint32_t *__numsrc, struct in_addr *__slist)
     __attribute__ ((__nothrow__ , __leaf__));


extern int setipv4sourcefilter (int __s, struct in_addr __interface_addr,
    struct in_addr __group, uint32_t __fmode,
    uint32_t __numsrc,
    const struct in_addr *__slist)
     __attribute__ ((__nothrow__ , __leaf__));



extern int getsourcefilter (int __s, uint32_t __interface_addr,
       const struct sockaddr *__group,
       socklen_t __grouplen, uint32_t *__fmode,
       uint32_t *__numsrc,
       struct sockaddr_storage *__slist) __attribute__ ((__nothrow__ , __leaf__));


extern int setsourcefilter (int __s, uint32_t __interface_addr,
       const struct sockaddr *__group,
       socklen_t __grouplen, uint32_t __fmode,
       uint32_t __numsrc,
       const struct sockaddr_storage *__slist) __attribute__ ((__nothrow__ , __leaf__));




enum CmPAsnTknTypes
{
   CM_PASN_TET_BOOL,
   CM_PASN_TET_SINT8,
   CM_PASN_TET_SINT16,
   CM_PASN_TET_SINT32,
   CM_PASN_TET_UINT8,
   CM_PASN_TET_UINT16,
   CM_PASN_TET_UINT32,
   CM_PASN_TET_ENUM,
   CM_PASN_TET_BITSTR,
   CM_PASN_TET_BITSTRXL,
   CM_PASN_TET_OCTSTR,
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_TET_NULL,
   CM_PASN_TET_SEQ,
   CM_PASN_TET_SET,
   CM_PASN_TET_SEQOF,
   CM_PASN_TET_SETOF,
   CM_PASN_TET_CHOICE,
   CM_PASN_TET_OID,
   CM_PASN_TET_IA5STR,
   CM_PASN_TET_IA5STRXL,
   CM_PASN_TET_PRNSTR,
   CM_PASN_TET_PRNSTRXL,
   CM_PASN_TET_NUMSTR,
   CM_PASN_TET_NUMSTRXL,
   CM_PASN_TET_VISSTR,
   CM_PASN_TET_VISSTRXL,
   CM_PASN_TET_GENSTR,
   CM_PASN_TET_GENSTRXL,
   CM_PASN_TET_BMPSTR,
   CM_PASN_TET_BMPSTRXL,
   CM_PASN_TET_UNISTR,
   CM_PASN_TET_UNISTRXL,
   CM_PASN_TET_OCTSTRBUF,
   CM_PASN_TET_SETSEQ_TERM,
   CM_PASN_TET_EXT_MKR,
   CM_PASN_TET_TKNBUF,
   CM_PASN_TET_CLASSIE,
   CM_PASN_TET_SEQNULL,
   CM_PASN_TET_UINTXL
};



typedef S8 Txt;

typedef U8 Ent;

typedef U8 Inst;

typedef struct entityId
{
   Ent ent;
   Inst inst;
} EntityId;



typedef S16 Elmnt;

typedef S16 ElmntInst1;

typedef S16 ElmntInst2;

typedef S16 ElmntInst3;

typedef struct elmntId
{
   Elmnt elmnt;
   ElmntInst1 elmntInst1;
   ElmntInst2 elmntInst2;
   ElmntInst3 elmntInst3;
} ElmntId;

typedef U8 Region;

typedef U8 Pool;

typedef U8 Prior;

typedef Prior Priority;

typedef U8 Route;

typedef U8 Data;

typedef U8 Selector;

typedef S16 Reason;

typedef U16 ProcId;

typedef U8 Event;

typedef U32 TranId;

typedef S16 IntNum;

typedef U16 TranNum;

typedef U16 CmIntfId;
typedef U16 CmIntfVer;
typedef struct pst
{
   ProcId dstProcId;
   ProcId srcProcId;

   Ent dstEnt;
   Inst dstInst;
   Ent srcEnt;
   Inst srcInst;

   Prior prior;
   Route route;
   Event event;
   Region region;

   Pool pool;
   Selector selector;
   CmIntfVer intfVer;
} Pst;



typedef struct systemId
{
   S16 mVer;
   S16 mRev;
   S16 bVer;
   S16 bRev;
   Txt *ptNmb;
} SystemId;





typedef struct protAddr
{
   U16 protType;
   U8 len;
   U8 preLen;
   U8 address[16];





}ProtAddr;

typedef struct protAddrTbl
{
   U8 count;
   ProtAddr addr[4];
}ProtAddrTbl;



typedef struct addrs
{
   U8 length;
   U8 strg[20];
} Addrs;

typedef struct shrtAddr
{
   U8 length;
   U8 strg[32];
} ShrtAddrs;

typedef struct lngAddr
{
   U8 length;
   U8 strg[64];
} LngAddrs;



typedef struct bndCfg
{
   Txt *usrId;
   U8 bufOwnshp;
   U8 flcTyp;
   U8 wdw;
   Ent ent;
   Inst inst;
   Region region;
   Pool pool;
   Prior prior;
   Route route;
   Addrs sapAdr;
   Selector selector;
} BndCfg;
typedef struct tskInit
{



   Ent ent;
   Inst inst;
   Region region;
   Pool pool;
   Reason reason;
   Bool cfgDone;
   Bool acnt;
   Bool usta;
   Bool trc;

   U32 dbgMask;
   Txt prntBuf[255];

   Txt *prntCirBuf;




   BndCfg lmBnd;
   ProcId procId;
   Pst lmPst;
} TskInit;


typedef S32 Cntr;

typedef U32 StsCntr;

typedef S16 LnkNmb;

typedef S8 VBit;

typedef S16 SuId;

typedef S16 SpId;

typedef S16 SuInstId;

typedef S16 SpInstId;

typedef U16 PortId;

typedef U8 Sapi;

typedef U8 Tei;

typedef U8 Ces;

typedef U32 Dlci;

typedef U16 CalRef;

typedef S16 Origin;

typedef U16 NwId;

typedef S16 Swtch;

typedef U8 Cause;

typedef U8 Dgn;

typedef S16 Action;

typedef S16 SeqS16;

typedef U16 SeqU16;

typedef S32 SeqS24;

typedef U32 SeqU24;

typedef U8 SetUpArb;

typedef U8 EvntType;

typedef U8 State;

typedef U8 Mode;

typedef S32 ConnId;

typedef U32 UConnId;

typedef U16 ProtId;

typedef U16 ChannelId;

typedef U8 Arr64U8[64];

typedef U16 Efa;

typedef U32 BitState;

typedef U8 CChanId;

typedef U16 MibOpCode;


typedef U16 MibStatus;

typedef U16 MibTblType;

typedef S32 MibReqId;

typedef U8 UstaType;
typedef S8 ChannelNo;
typedef S16 Baud;

typedef S16 PhysIntType;

typedef S16 PathConnType;

typedef S16 Parity;

typedef S16 CharLength;

typedef S16 StopBits;



typedef U32 IpAddr;

typedef U16 Port;

typedef U8 Cmd;

typedef U8 Flags;

typedef U8 Ttl;

typedef U8 Prec;

typedef U32 Window;

typedef U8 MtpStatus;

typedef U8 Credit;



typedef U32 CirId;

typedef U16 Cic;

typedef U32 SiInstId;



typedef U32 BiInstId;



typedef U32 TpInstId;



typedef U32 Oui;
typedef U16 Pid;
typedef U32 LlcId;
typedef struct octStrg
{
   S32 length;
   U8 val[132];
} OctStrg;

typedef struct tknHdr
{
   U8 pres;
   U8 spare1;
   U16 spare2;



} TknHdr;

typedef struct elmtHdr
{
   U8 pres;
   U8 actnInd;
   U16 compInd;



} ElmtHdr;



typedef struct tknU8
{
   U8 pres;
   U8 val;
   U16 spare1;



} TknU8;

typedef struct tknS8
{
   U8 pres;
   S8 val;
   U16 spare1;



} TknS8;

typedef struct tknU16
{
   U8 pres;
   U8 spare1;
   U16 val;



} TknU16;

typedef struct tknU32
{
   U8 pres;
   U8 spare1;
   U16 spare2;
   U32 val;
} TknU32;

typedef struct tknS32
{
   U8 pres;
   U8 spare1;
   U16 spare2;
   S32 val;
} TknS32;

typedef struct tknStrS
{
   U8 pres;
   U8 len;
   U16 spare1;




   U8 val[(22 + 3) & 0xffc];

} TknStrS;

typedef struct tknStrM
{
   U8 pres;
   U8 len;
   U16 spare1;




   U8 val[(32 + 3) & 0xffc];

} TknStrM;

typedef struct tknStr
{
   U8 pres;
   U8 len;
   U16 spare1;




   U8 val[(132 + 3) & 0xffc];

} TknStr;

typedef struct tknStrE
{
   U8 pres;
   U8 len;
   U16 spare1;




   U8 val[(255 + 3) & 0xffc];

} TknStrE;

typedef struct tknStrXL
{
   U16 len;
   U8 pres;
   U8 spare1;



   U8 *val;
} TknStrXL;

typedef struct tknStr4
{
   U8 pres;
   U8 len;
   U16 spare1;




   U8 val[4];

} TknStr4;

typedef struct tknStr12
{
   U8 pres;
   U8 len;
   U16 spare1;




   U8 val[12];

} TknStr12;

typedef struct tknStr32
{
   U8 pres;
   U8 len;
   U16 spare1;



   U8 val[32];
} TknStr32;

typedef struct tknStr64
{
   U8 pres;
   U8 len;
   U16 spare1;



   U8 val[64];
} TknStr64;

typedef struct tknStr132
{
   U8 pres;
   U8 len;
   U16 spare1;




   U8 val[132];

} TknStr132;

typedef struct tknStr256
{
   U8 pres;
   U8 len;
   U16 spare1;



   U8 val[256];
} TknStr256;

typedef struct tknOid
{
   U8 pres;
   U8 len;
   U16 spare1;






   U32 val[32];



} TknOid;

typedef struct tknBits
{
   U8 pres;
   U8 len;
   U16 spare1;




   U8 val[(7 + 3) & 0xffc];

} TknBits;

typedef struct elmtStr
{
   ElmtHdr eh;
   TknStr str;
} ElmtStr;

typedef struct cdPtyNmb
{
   ElmtHdr eh;
   TknU8 nmbPlanId;
   TknU8 typeNmb0;



   TknStrS nmbDigits;

} CdPtyNmb;

typedef struct redirNmb
{
   ElmtHdr eh;
   TknU8 nmbPlanId;
   TknU8 typeNmb;
   TknU8 screenInd;
   TknU8 presInd;
   TknU8 rsnRedirect;
   TknStrS nmbDigits;
} RedirNmb;

typedef struct srvClass
{
   U8 type;
   union
   {
      struct
      {
         Bool cr;
         Bool de;
      } fr;
      struct
      {
         Prior prior;
      } ma;
   } s;
} SrvClass;



typedef struct _ip
{
   U8 ip_hl;
   Prec ip_tos;
   U16 ip_len;
   U16 ip_id;
   U16 ip_off;
   Ttl ip_ttl;
   U8 ip_p;
   U16 ip_sum;
   IpAddr ip_src;
   IpAddr ip_dst;
} Ip;
typedef struct smCfg
{
   Ent ent;
   Inst inst;
   Region region;
   Pool pool;
   Priority prior;
   Route route;
   Selector selector;
} SmCfg;

typedef struct mem
{
   Region region;
   Pool pool;
   U16 spare;
} Mem;

typedef Mem MemoryId;


typedef struct resp
{
   Selector selector;
   Priority prior;
   Route route;
   MemoryId mem;
}Resp;

typedef struct tds_header
{
   U16 msgLen;
   U8 msgType;
   U8 version;
   U16 seqNmb;
   EntityId entId;
   ElmntId elmId;

   TranId transId;
   Resp response;

} Header;

typedef struct tmrCfg
{
   Bool enb;
   U16 val;
} TmrCfg;

typedef struct asyncCfg
{
   StopBits stopBits;
   CharLength charLength;
   Parity rxParity;
   Parity txParity;
} AsyncCfg;




typedef struct dateTime
{
   U8 month;
   U8 day;
   U8 year;
   U8 hour;
   U8 min;
   U8 sec;
   U8 tenths;




} DateTime;


typedef U64 EpcTime;


typedef struct cmStatus
{
   U16 status;
   U16 reason;
}CmStatus;


typedef struct cmAlarm
{
   DateTime dt;
   U16 category;
   U16 event;
   U16 cause;
}CmAlarm;



typedef struct duration
{
   U8 days;
   U8 hours;
   U8 mins;
   U8 secs;
   U8 tenths;
} Duration;
typedef struct ssmsgb Buffer;
typedef struct tknBuf
{
   U8 pres;
   U8 spare1;
   U16 spare2;



   Buffer *val;
} TknBuf;



typedef U32 CmIpAddr;







extern S16 cmPkDateTime (DateTime *dateTime, Buffer *mBuf);
extern S16 cmPkDuration (Duration *duration, Buffer *mBuf);
extern S16 cmPkPtr (U32 ptr, Buffer *mBuf);
extern S16 cmPkEntityId (EntityId *entityId, Buffer *mBuf);
extern S16 cmPkElmntId (ElmntId *elmntId, Buffer *mBuf);
extern S16 cmPkMemoryId (MemoryId *memoryId, Buffer *mBuf);


extern S16 cmPkSystemId (SystemId *systemId, Buffer *mBuf);
extern S16 cmPkAddrs (Addrs *addrs, Buffer *mBuf);
extern S16 cmPkProtAddr (ProtAddr *protAddr, Buffer *mBuf);
extern S16 cmPkProtAddrTbl (ProtAddrTbl *protAddr, Buffer *mBuf);
extern S16 cmPkShrtAddrs (ShrtAddrs *addrs, Buffer *mBuf);
extern S16 cmPkAddrMask (U8 *mask, Buffer *mBuf);
extern S16 cmPkBndCfg (BndCfg *bndCfg, Buffer *mBuf);
extern S16 cmPkPst (Pst *pst, Buffer *mBuf);
extern S16 cmPkElmtHdr (ElmtHdr *m, Buffer *mBuf);
extern S16 cmPkTknU8 (TknU8 *tknU8, Buffer *mBuf);
extern S16 cmPkTknS8 (TknS8 *tknS8, Buffer *mBuf);
extern S16 cmPkTknU16 (TknU16 *tknU16, Buffer *mBuf);
extern S16 cmPkTknU32 (TknU32 *tknU32, Buffer *mBuf);
extern S16 cmPkTknStr (TknStr *tknStr, Buffer *mBuf);
extern S16 cmPkTknStrM (TknStrM *tknStr, Buffer *mBuf);
extern S16 cmPkTknStrS (TknStrS *tknStr, Buffer *mBuf);
extern S16 cmPkTknStrE (TknStrE *tknStr, Buffer *mBuf);

extern S16 cmPkTknStr4 (TknStr4 *tknStr, Buffer *mBuf);
extern S16 cmPkTknStr12 (TknStr12 *tknStr, Buffer *mBuf);
extern S16 cmPkTknStr32 (TknStr32 *tknStr, Buffer *mBuf);
extern S16 cmPkTknStr64 (TknStr64 *tknStr, Buffer *mBuf);
extern S16 cmPkTknStr132 (TknStr132 *tknStr, Buffer *mBuf);
extern S16 cmPkTknStr256 (TknStr256 *tknStr, Buffer *mBuf);

 S16 cmPkTknS32 (TknS32 *tknS32, Buffer *mBuf);
 S16 cmPkTknOid (TknOid *tknOid, Buffer *mBuf);
 S16 cmPkTknBuf (TknBuf *tknBuf, Buffer *mBuf);






extern S16 cmPkHeader (Header *header, Buffer *mBuf);
extern S16 cmPkSmCfg (SmCfg *smCfg, Buffer *mBuf);
extern S16 cmPkTmrCfg (TmrCfg *tmrCfg, Buffer *mBuf);
extern S16 cmPkCmStatus (CmStatus *status, Buffer *mBuf);
extern S16 cmPkCmAlarm (CmAlarm *alrm, Buffer *mBuf);





extern S16 cmUnpkDateTime (DateTime *dateTime, Buffer *mBuf);
extern S16 cmUnpkDuration (Duration *duration, Buffer *mBuf);
extern S16 cmUnpkPtr (U32 *ptr, Buffer *mBuf);
extern S16 cmUnpkEntityId (EntityId *entityId, Buffer *mBuf);
extern S16 cmUnpkElmntId (ElmntId *elmntId, Buffer *mBuf);
extern S16 cmUnpkMemoryId (MemoryId *memoryId, Buffer *mBuf);


extern S16 cmUnpkSystemId (SystemId *systemId, Buffer *mBuf);
extern S16 cmUnpkAddrs (Addrs *addrs, Buffer *mBuf);
extern S16 cmUnpkProtAddr (ProtAddr *protAddr, Buffer *mBuf);
extern S16 cmUnpkProtAddrTbl (ProtAddrTbl *protAddr, Buffer *mBuf);
extern S16 cmUnpkShrtAddrs (ShrtAddrs *addrs, Buffer *mBuf);
extern S16 cmUnpkAddrMask (U8 *mask, Buffer *mBuf);
extern S16 cmUnpkBndCfg (BndCfg *bndCfg, Buffer *mBuf);
extern S16 cmUnpkPst (Pst *pst, Buffer *mBuf);
extern S16 cmUnpkElmtHdr (ElmtHdr *m, Buffer *mBuf);
extern S16 cmUnpkTknU8 (TknU8 *tknU8, Buffer *mBuf);
extern S16 cmUnpkTknS8 (TknS8 *tknS8, Buffer *mBuf);
extern S16 cmUnpkTknU16 (TknU16 *tknU16, Buffer *mBuf);
extern S16 cmUnpkTknU32 (TknU32 *tknU32, Buffer *mBuf);
extern S16 cmUnpkTknStr (TknStr *tknStr, Buffer *mBuf);
extern S16 cmUnpkTknStrM (TknStrM *tknStr, Buffer *mBuf);
extern S16 cmUnpkTknStrS (TknStrS *tknStr, Buffer *mBuf);
extern S16 cmUnpkTknStrE (TknStrE *tknStr, Buffer *mBuf);

extern S16 cmUnpkTknStr4 (TknStr4 *tknStr, Buffer *mBuf);
extern S16 cmUnpkTknStr12 (TknStr12 *tknStr, Buffer *mBuf);
extern S16 cmUnpkTknStr32 (TknStr32 *tknStr, Buffer *mBuf);
extern S16 cmUnpkTknStr64 (TknStr64 *tknStr, Buffer *mBuf);
extern S16 cmUnpkTknStr132 (TknStr132 *tknStr, Buffer *mBuf);
extern S16 cmUnpkTknStr256 (TknStr256 *tknStr, Buffer *mBuf);

 S16 cmUnpkTknS32 (TknS32 *tknS32, Buffer *mBuf);
 S16 cmUnpkTknOid (TknOid *tknOid, Buffer *mBuf);
 S16 cmUnpkTknBuf (TknBuf *tknBuf, Buffer **mBuf);






extern S16 cmUnpkHeader (Header *header, Buffer *mBuf);
extern S16 cmUnpkSmCfg (SmCfg *smCfg, Buffer *mBuf);
extern S16 cmUnpkTmrCfg (TmrCfg *tmrCfg, Buffer *mBuf);
extern S16 cmUnpkCmStatus (CmStatus *status, Buffer *mBuf);
extern S16 cmUnpkCmAlarm (CmAlarm *alrm, Buffer *mBuf);
typedef S16 Status;

typedef U32 Ticks;




typedef S16 MsgLen;


typedef S16 Order;




typedef U32 Size;
typedef S32 PtrOff;


typedef U32 QLen;

typedef QLen BufQLen;

typedef S16 RegSize;

typedef S16 DPoolSize;

typedef U16 Random;

typedef S16 Seq;

typedef U32 CoreId;


typedef U32 ErrCls;

typedef U32 ErrCode;

typedef U32 ErrVal;

typedef S16 VectNmb;

typedef S16 Ttype;

typedef S8 Sema;
extern S16 msOptInd;
extern S8 *msOptArg;
extern Txt **msArgv;
extern S16 msArgc;




typedef U8 SSTskId;




typedef S32 SSTskPrior;
struct ssmsgb
{
   S8 refCnt;
   struct ssmsgb *b_next;
   struct ssmsgb *b_prev;
   struct ssmsgb *b_cont;
   U8 *b_rptr;
   U8 *b_wptr;
   struct ssdatab *b_datap;
};


typedef struct ssQueue
{
   Buffer *head;
   Buffer *tail;
   QLen crntSize;

} Queue;



typedef struct sMemCtl
{
   U8 op;

   union
   {
      struct
      {
         Data *vaddr;
         Data **paddr;
      } vtop;

      struct
      {
         Size size;
         Status *status;
      } chkres;
   } u;

} SMemCtl;
typedef S16 (*SsAlloc) (Void *, Size *, U32, Data **);





typedef S16 (*SsFree) (Void *, Data *, Size);

typedef S16 (*SsCtl) (Void *, Event, SMemCtl *);




typedef struct sRegInfo
{
   Void *regCb;
   U32 flags;




   Data *start;
   Size size;
   SsAlloc alloc;
   SsFree free;
   SsCtl ctl;

} SRegInfo;
typedef struct cmTimer
{
   S16 tmrEvnt;
   U32 tqExpire;
   U32 cb;
   struct cmTimer *next;
   struct cmTimer *prev;
   U8 ent2bUpd;

   U16 entIdx;
} CmTimer;

typedef struct cmTqCp
{
   U32 nxtEnt;
   U32 tmrLen;
   CmTimer *tmp;
} CmTqCp;

typedef struct cmTqType
{
   CmTimer *first;
   CmTimer *tail;
} CmTqType;

typedef struct cmTmrArg
{
   CmTqCp *tqCp;
   CmTqType *tq;
   CmTimer *timers;
   U32 cb;
   S16 evnt;
   U32 wait;
   U8 tNum;
   U8 max;
} CmTmrArg;




typedef Void (*PFV) (U32, S16);

extern Void cmInitTimers (CmTimer* timers, U8 max);
extern Void cmPlcCbTq (CmTmrArg* arg);
extern Void cmRmvCbTq (CmTmrArg* arg);
extern Void cmPrcTmr (CmTqCp* tqCp, CmTqType* tq, PFV func);
extern Void cmRstCbTq (CmTmrArg* arg);
typedef S8 SsdTTskEntry;



typedef struct ssdSTskEntry
{
   pthread_t tId;
   Ent ent;
   Inst inst;
   pthread_mutex_t lock;


   U32 lwpId;

} SsdSTskEntry;




typedef struct ssdDrvrTskEntry
{
   Bool flag;

} SsdDrvrTskEntry;




typedef struct ssdTmrEntry
{
   CmTimer timers[1];

} SsdTmrEntry;



typedef S8 SsdDPoolEntry;



typedef S8 SsdSPoolEntry;



typedef S8 SsdPoolEntry;



typedef S8 SsdRegionEntry;





typedef struct ssdOs
{
   unsigned randSeed;

   Ticks sysTicks;

   pthread_t tmrHdlrTID;
   CmTqCp tmrTqCp;
   CmTqType tmrTq[45];

   sem_t ssStarted;

   FILE *conInFp;
   FILE *conOutFp;
   pthread_t conHdlrTID;



   FILE *fileOutFp;



   pthread_t isTskHdlrTID;
   int isFildes[2];

   Bool sigEvnt;

} SsdOs;


typedef struct mtBktCfg
{
   Size blkSize;
   U32 numBlks;
} MtBktCfg;

typedef struct mtRegCfg
{
   Region regionId;
   U16 numBkts;
   Size heapsize;
   MtBktCfg bkt[5];
} MtRegCfg;

typedef struct mtMemCfg
{
   U8 numRegions;
   MtRegCfg region[8];
} MtMemCfg;
extern U32 gt[128];
typedef S16 (*PAIFS16) (Ent ent,Inst inst,Region region,Reason reason );





typedef S16 (*PAIFTMRS16) (Ent ent, Inst inst);
typedef S16 (*PATFS16) (Prior prior,Route route,Ent ent,Inst inst,Buffer *mBuf);



typedef S16 (*ActvTsk) (Pst *pst, Buffer *mBuf);

typedef struct uProc UProc;

typedef void (*ISTsk) (Inst inst);




struct uProc
{
   Inst inst;
   ProcId low;
   ProcId high;
   ActvTsk actvTsk;
   U16 isFlag;
   ISTsk isTsk;
};






extern S16 SChekMemUtilization (Region region,Bool *memAlarm);

extern Void prntMem (Data *strtAdr,S16 len);
extern Void prntMsg (Buffer *mBuf);
extern Void prntMsg1 (Buffer *mBuf,S16 src,S16 dst);
extern S16 tst (void );
extern S16 rdConQ (Data data);

extern S16 SPkS8 (S8 val,Buffer *mBuf);
extern S16 SPkU8 (U8 val,Buffer *mBuf);
extern S16 SPkS16 (S16 val,Buffer *mBuf);
extern S16 SPkU16 (U16 val,Buffer *mBuf);
extern S16 SPkS32 (S32 val,Buffer *mBuf);
extern S16 SPkU32 (U32 val,Buffer *mBuf);


extern S16 SPkF32 (F32 val,Buffer *mBuf);
extern S16 SPkF64 (F64 val,Buffer *mBuf);

extern S16 SUnpkS8 (S8 *val,Buffer *mBuf);
extern S16 SUnpkU8 (U8 *val,Buffer *mBuf);
extern S16 SUnpkS16 (S16 *val,Buffer *mBuf);
extern S16 SUnpkU16 (U16 *val,Buffer *mBuf);
extern S16 SUnpkS32 (S32 *val,Buffer *mBuf);
extern S16 SUnpkU32 (U32 *val,Buffer *mBuf);


extern S16 SUnpkF32 (F32 *val,Buffer *mBuf);
extern S16 SUnpkF64 (F64 *val,Buffer *mBuf);

extern S16 SPrint (Txt *buf);
extern S16 SDisplay (S16 chan,Txt *buf);
extern S16 SPrntMsg (Buffer *mBuf,S16 src,S16 dst);
extern S16 SInitQueue (Queue *q);

extern S16 SQueueFirst (Buffer *buf,Queue *q);
extern S16 SQueueLast (Buffer *buf,Queue *q);
extern S16 SDequeueFirst (Buffer * *bufPtr,Queue *q);
extern S16 SDequeueLast (Buffer * *bufPtr,Queue *q);

extern S16 SFlushQueue (Queue *q);
extern S16 SCatQueue (Queue *q1,Queue *q2,Order order);
extern S16 SFndLenQueue (Queue *q,QLen *lngPtr);
extern S16 SExamQueue (Buffer **bufPtr,Queue *q,QLen idx);
extern S16 SAddQueue (Buffer *buf,Queue *q,QLen idx);
extern S16 SRemQueue (Buffer **bufPtr,Queue *q,QLen idx);
extern S16 SGetDBuf (Region region,Pool pool,Buffer * *bufPtr);
extern S16 SPutDBuf (Region region,Pool pool,Buffer *buf);
extern S16 SPutMsgToRegion (Region region, Buffer *buf);
extern S16 SPutMsg (Buffer *mBuf);
extern S16 SGetMsg (Region region, Pool pool, Buffer * *mBufPtr);
extern S16 SGetSBuf (Region region,Pool pool, Data * *bufPtr, Size size);
extern S16 SPutSBuf (Region region, Pool pool, Data *buf, Size size);
extern S16 SGetStaticBuffer (Region region,Pool pool, Data * *bufPtr, Size size, U8 memType);
extern S16 SPutStaticBuffer (Region region, Pool pool, Data *buf, Size size, U8 memType);
extern S16 SGetSMem (Region region,Size size,Pool *poolPtr);
extern S16 SPutSMem (Region region,Pool pool);
extern S16 SInitMsg (Buffer *mBuf);
extern S16 SAddPreMsg (Data data,Buffer *mBuf);
extern S16 SAddPstMsg (Data data,Buffer *mBuf);

extern S16 SAddPreMsgMultInOrder (Data *src,MsgLen cnt,Buffer *mBuf);
extern S16 SRemPreMsg (Data *dataPtr,Buffer *mBuf);
extern S16 SRemPreMsgRegion (Region region, Data *dataPtr,Buffer *mBuf);
extern S16 SCatMsgRegion (Region region, Buffer *mBuf1,Buffer *mBuf2,Order order);
extern S16 SSegMsgRegion (Region region, Buffer *mBuf1,MsgLen idx,Buffer **mBuf2);
extern int SCreatePThread (pthread_t* tid, pthread_attr_t* attr, void *(*start_routine) (void *), void* arg);
extern S16 SRemPstMsg (Data *dataPtr,Buffer *mBuf);







extern S16 SAddPreMsgMult (Data *src,MsgLen cnt,Buffer *mBuf);
extern S16 SAddPstMsgMult (Data *src,MsgLen cnt,Buffer *mBuf);

extern S16 SGetPstMsgMult (MsgLen cnt,Buffer *mBuf);
extern S16 SRemPreMsgMult (Data *dst,MsgLen cnt,Buffer *mBuf);
extern S16 SRemPstMsgMult (Data *dst,MsgLen cnt,Buffer *mBuf);
extern S16 SRepMsg (Data data,Buffer *mBuf,MsgLen idx);
extern S16 SExamMsg (Data *dataPtr,Buffer *mBuf,MsgLen idx);

extern S16 SGetDataFrmMsg (Buffer *mBuf, Data *dataPtr, MsgLen idx, MsgLen dataLen);
extern S16 SFndLenMsg (Buffer *mBuf,MsgLen *lngPtr);
extern S16 SCatMsg (Buffer *mBuf1,Buffer *mBuf2,Order order);




extern S16 SSegMsg (Buffer *mBuf1,MsgLen idx,Buffer **mBuf2);

extern S16 SSwapMsg (Buffer *mBuf1, Buffer *mBuf2);
extern S16 SCpyMsgFix (Buffer *srcMbuf,MsgLen srcIdx,MsgLen cnt, Data *dstBuf,MsgLen *cCnt)
                                       ;
extern S16 SCpyFixMsg (Data *srcBuf,Buffer *dstMbuf, MsgLen dstIdx,MsgLen cnt,MsgLen *cCnt)
                                                   ;
extern S16 SCompressMsg (Buffer *mBuf);
extern S16 SCpyMsgMsg (Buffer *mBuf, Region region, Pool pool, Buffer **dstBuf)
                             ;
extern S16 SAddMsgRef (Buffer *mBuf, Region region, Pool pool, Buffer **dstBuf)
                             ;
extern S16 SIncMsgRef(Buffer *srcBuf, Region dstRegion, Pool dstPool, Buffer **dstBuf);






extern S16 SChkRes (Region region,Pool pool,Status *status);
extern S16 SChkResUtl (Region region,U8 *wSum);
extern S16 SSetDateTime (DateTime *dt);
extern S16 SGetDateTime (DateTime *dt);






extern S16 SGetEpcTime (EpcTime *et);

extern S16 SGetTimeStamp ( S8 *ts);
extern S16 SGetSysTime (Ticks *sysTime);
extern S16 SGetRefTime (U32 refTime, U32 *sec, U32 *usec);
extern S16 SRandom (Random *value);
extern S16 SError (Seq seq,Reason reason);
extern Void SLogError (Ent ent, Inst inst, ProcId procId, Txt *file, S32 line, ErrCls errCls, ErrCode errCode, ErrVal errVal, Txt *errDesc)

                                                    ;

extern U32 SGetSystemTsk (Void);




extern S16 SRegInit (Ent ent,Inst inst,PAIFS16 initFnct);
extern S16 SRegActvTsk (Ent ent,Inst inst,Ttype ttype,Prior prior, ActvTsk actvTsk)
                                               ;




extern S16 SRegCfgTmr (Ent ent, Inst inst, S16 period, S16 units, PFS16 tmrFnct)



                                            ;


extern S16 SRegCfgTmrMt (Ent ent, Inst inst, S16 period, S16 units, PAIFTMRS16 tmrFnctMt)



                                                     ;

extern S16 SDeregCfgTmr (Ent ent, Inst inst, S16 period, S16 units, PFS16 tmrFnct)



                                              ;


extern S16 SDeregCfgTmrMt (Ent ent, Inst inst, S16 period, S16 units, PAIFTMRS16 tmrFnctMt)



                                                       ;
extern S16 SPstTsk (Pst *pst, Buffer *mBuf);






extern S16 SRegDrvrTsk (Inst inst, ProcId low, ProcId high, ActvTsk actvTsk, ISTsk isTsk)
                                                            ;

extern S16 SDeregDrvrTsk (Inst channel);



extern S16 SRegRtrTsk (Route *, Cntr, ActvTsk);
extern S16 SDeregRtrTsk (Route *, Cntr);



extern S16 SAttachPtrToBuf ( Region region, Pool pool, Data *ptr, MsgLen totalLen, Buffer** mBuf )





  ;





typedef S8 SsAffinityMode;


typedef struct {
  U32 numCores;
  U32 threadsPerCore;
  U32 threadRegister[64];
} SCpuInfo;

extern S16 SRegCpuInfo (SCpuInfo *cpuInfo);
extern S16 SSetAffinity (SSTskId *tskId, SsAffinityMode mode, U32 coreId, SSTskId *tskAssociatedTskId);
extern S16 SGetAffinity (SSTskId *tskId, U32 *coreId);







extern S16 SAddDBufPst (Buffer *mBuf, Buffer *dBuf);
extern S16 SAddDBufPre (Buffer *mBuf, Buffer *dBuf);
extern S16 SRemDBufPst (Buffer *mBuf, Buffer **dBuf);
extern S16 SRemDBufPre (Buffer *mBuf, Buffer **dBuf);
extern S16 SGetDataRx (Buffer *dBuf, MsgLen pad, Data **dat, MsgLen *mLen);
extern S16 SGetDataTx (Buffer *dBuf, Data **dat, MsgLen *mLen);
extern S16 SUpdMsg (Buffer *mBuf, Buffer *dBuf, MsgLen mLen);
extern S16 SCacheFlush (U16 cache_type, Data *addr, Size size);
extern S16 SCacheInvalidate (U16 cache_type, Data *addr, Size size);
extern S16 SAlignDBufEven (Buffer *dBuf);
extern S16 SAlignDBuf (Buffer *dBuf, U32 align);
extern S16 SInitNxtDBuf (Buffer *mBuf);
extern S16 SGetNxtDBuf (Buffer *mBuf, Buffer **dBuf);
extern S16 SChkNxtDBuf (Buffer *mBuf);
extern S16 SSetIntPend (U16 id, Bool flag);
extern S16 SChkMsg (Buffer *mBuf);
extern S16 SDeregInitTskTmr (Ent ent,Inst inst);
extern S16 SExitTsk (void );
extern S16 SExitInt (void );
extern S16 SHoldInt (void );
extern S16 SRelInt (void );
extern S16 SEnbInt (void );
extern S16 SDisInt (void );
extern S16 SGetVect (VectNmb vectNmb,PIF *vectFnct);
extern S16 SPutVect (VectNmb vectNmb,PIF vectFnct);






extern S16 SInitSema (Region region, Sema *sema);
extern S16 SRelSema (Region region, Sema sema);
extern S16 SGetSema (Region region, Sema sema);
extern S16 SActvInit (Ent ent,Inst inst,Region region,Reason reason);
extern S16 SActvTsk (Prior prior,Route route,Ent srcEnt, Inst srcInst,Buffer *mBuf)
                                       ;
extern S16 SActvTmr (void );
extern S16 SGetOpt (int argc,char **argv,char *opts);



extern S16 SGetEntInst (Ent *ent, Inst *inst);
extern S16 SSetEntInst (Ent ent, Inst inst);
extern ProcId SFndProcId (void);
extern Void SSetProcId (ProcId pId);


extern S16 SGetDBufSiz (Region region, Pool pool, S16 *size);
extern S16 SGetStrtIdx (Region region, Pool pool, S16 *idx);
extern S16 SGetEndIdx (Region region, Pool pool, S16 *idx);
extern S16 SGetStrtPad (Region region, Pool pool, S16 *pad);
extern Void SExit (Void);




extern S16 SRegTTsk (Ent ent, Inst inst, Ttype type, Prior prior, PAIFS16 initTsk, ActvTsk actvTsk)




                                           ;

extern S16 SRegCbTsk (Ent ent, Inst inst, ActvTsk actvTsk)

                                           ;
extern S16 SDeregTTsk (Ent ent, Inst inst);
extern S16 SCreateSTsk (SSTskPrior tskPrior, SSTskId *tskId);
extern S16 SDestroySTsk (SSTskId tskId);



extern S16 SAttachTTsk (Ent ent, Inst inst, SSTskId tskId);
extern S16 SDetachTTsk (Ent ent, Inst inst);







extern S16 SRegRegion (Region region, SRegInfo *regInfo);
extern S16 SDeregRegion (Region region);
extern S16 SRegDynRegion (Region region, SRegInfo *regInfo);
extern S16 SAlloc (Region region, Size *size, U32 flags, Data **ptr);
extern S16 SFree (Region region, Data *ptr, Size size);


extern S16 SGetBufRegionPool (Buffer *mBuf, Region *region, Pool *pool);
extern S16 SThreadYield (void);


extern S16 SInitLock (pthread_mutex_t *lock,U8 type);
extern S16 SLock (pthread_mutex_t *lock);
extern S16 SUnlock (pthread_mutex_t *lock);
extern S16 SDestroyLock (pthread_mutex_t *lock);


extern S16 SInitSemaphore (sem_t *sem, U8 value);
extern S16 SWaitSemaphore (sem_t *sem);
extern S16 SPostSemaphore (sem_t *sem);
extern S16 SDestroySemaphore (sem_t *sem);
extern S16 smActvInit (Ent ent, Inst inst, Region region, Reason reason);
extern S16 smInitExt (void);


extern S16 smActvTsk (Pst *pst, Buffer *mBuf);
extern S8* SGetConfigPath (Void);


extern S16 SCpyPartMsg (Buffer *srcBuf, MsgLen idx, MsgLen cnt, Buffer *dstBuf);
extern S16 SRepPartMsg (Buffer *srcBuf, MsgLen idx, MsgLen cnt, Buffer *dstBuf);
extern S16 SMovPartMsg (Buffer *srcBuf, MsgLen idx, Buffer *dstBuf);
extern S16 SPkMsgMult (Data *src, MsgLen cnt, Buffer *mBuf);
extern S16 SGetReadPtr (Buffer *mBuf, U8** data, MsgLen *len);

typedef enum
{
   SS_SHARABLE_MEMORY,
   SS_NON_SHARABLE_MEMORY
}ssMemoryType;
extern S16 SStartTask (volatile U32 *startTime, U32 tarkId);
extern S16 SStopTask (volatile U32 startTime,U32 taskId);
extern Void SIncrementTtiCount(Void);
extern Ticks SGetTtiCount(Void);
extern Void ysPrntBkTrace(Void);
extern Void ssMlogInit(Void);
extern Void ssMlogIncrCounter(Void);


extern Void ssRegMainThread(Void);






extern S16 ssGetDBufOfSize(Region region,Size size,Buffer **dBuf);

typedef TknU8 TknPres;


typedef TknU8 TknBool;

typedef struct tknS16
{
   U8 pres;
   U8 spare1;
   S16 val;



} TknS16;


typedef struct tknStr8
{
   U8 pres;
   U8 len;
   U16 spare1;



   U8 val[8];
} TknStr8;


typedef struct tknStr16
{
   U8 pres;
   U8 len;
   U16 spare1;



   U8 val[16];
} TknStr16;

typedef struct tknStrOSXL
{
   U8 pres;
   U8 spare1;
   U16 len;



   U8 *val;
} TknStrOSXL;


typedef TknStr4 TknBStr32;


typedef TknStrOSXL TknStrBSXL;







typedef struct tknStrBMP4
{
   U8 pres;
   U8 len;
   U16 spare1;



   U16 val[4];
} TknStrBMP4;


typedef struct tknStrBMPXL
{
   U8 pres;
   U8 spare1;
   U16 len;



   U16 *val;
} TknStrBMPXL;







typedef struct tknStrUNI4
{
   U8 pres;
   U8 len;
   U16 spare1;



   U32 val[4];
} TknStrUNI4;

typedef struct tknStrUNIXL
{
   U8 pres;
   U8 spare1;
   U16 len;



   U32 *val;
} TknStrUNIXL;


extern S16 cmPkTknPres (TknPres *tknPres, Buffer *mBuf);
extern S16 cmPkTknS16 (TknS16 *tknS16, Buffer *mBuf);
extern S16 cmPkTknBStr32 (TknBStr32 *tknbStr32, Buffer *mBuf);
extern S16 cmPkTknStr8 (TknStr8 *tknStr8, Buffer *mBuf);
extern S16 cmPkTknStr16 (TknStr16 *tknStr16, Buffer *mBuf);
extern S16 cmPkTknStrOSXL (TknStrOSXL *tknStrOSXL, Buffer *mBuf);
extern S16 cmPkTknStrBSXL (TknStrBSXL *tknStrBSXL, Buffer *mBuf);
extern S16 cmPkTknStrBMP4 (TknStrBMP4 *tknStrBMP4, Buffer *mBuf);
extern S16 cmPkTknStrBMPXL (TknStrBMPXL *tknStrBMPXL, Buffer *mBuf);
extern S16 cmPkTknStrUNI4 (TknStrUNI4 *tknStrUNI4, Buffer *mBuf);
extern S16 cmPkTknStrUNIXL (TknStrUNIXL *tknStrUNIXL, Buffer *mBuf);




extern S16 cmUnpkTknPres (TknPres *tknPres, Buffer *mBuf);
extern S16 cmUnpkTknS16 (TknS16 *tknS16, Buffer *mBuf);
extern S16 cmUnpkTknBStr32 (TknBStr32 *tknBStr32, Buffer *mBuf);
extern S16 cmUnpkTknStr8 (TknStr8 *tknStr8, Buffer *mBuf);
extern S16 cmUnpkTknStr16 (TknStr16 *tknStr16, Buffer *mBuf);
extern S16 cmUnpkTknStrOSXL (TknStrOSXL *tknStrOSXL, Buffer *mBuf, Ptr ptr)
                                                ;
extern S16 cmUnpkTknStrBSXL (TknStrBSXL *tknStrBSXL, Ptr ptr, Buffer *mBuf)
                                                     ;
extern S16 cmUnpkTknStrBMP4 (TknStrBMP4 *tknStrBMP4, Buffer *mBuf);
extern S16 cmUnpkTknStrBMPXL (TknStrBMPXL *tknStrBMPXL, Buffer *mBuf, Ptr ptr)
                                                ;
extern S16 cmUnpkTknStrUNI4 (TknStrUNI4 *tknStrUNI4, Buffer *mBuf);
extern S16 cmUnpkTknStrUNIXL (TknStrUNIXL *tknStrUNIXL, Buffer *mBuf, Ptr ptr)
                                                ;
typedef struct cmMemCb
{
   Size maxSize;
   Mem sMem;
   U32 memAllocated;
   U32 initPtr;
   U32 runPtr;
} CmMemCb;




typedef struct cmMemList CmMemList;

struct cmMemList
{
   CmMemList *next;
   CmMemList *prev;

   Size size;
};





typedef struct cmMemListCp
{
   CmMemList *first;
   CmMemList *last;
   U32 count;
   CmMemCb memCb;
}CmMemListCp;




typedef struct cmMemStatus
{
   Mem sMem;
   U32 memBlkCnt;
   Size maxBlkSize;
   Size memAllocated;
} CmMemStatus;
extern S16 cmAllocEvnt ( Size evntSize, Size maxBlkSize, Mem *sMem, Ptr *ptr)



                                              ;

extern Void cmInitMemCp ( CmMemListCp *memCp, Size maxBlkSize, Mem *sMem )


                                                 ;







extern S16 cmGetMem ( Ptr memPtr, Size size, Ptr *allocPtr)


                                               ;

extern Void cmFreeMem ( Ptr memPtr)
                                            ;

extern Void cmGetMemStatus ( Ptr memPtr, CmMemStatus *status)

                                                       ;
typedef struct cmLList CmLList;
typedef struct cmLListCp CmLListCp;


struct cmLList
{
   CmLList *next;
   CmLList *prev;
   U32 node;
};

struct cmLListCp
{
   CmLList *first;
   CmLList *last;
   CmLList *crnt;
   U32 count;
};

extern Void cmLListInit (CmLListCp *lList);
extern Void cmLListAdd2Head (CmLListCp *lList, CmLList *node);
extern Void cmLListAdd2Tail (CmLListCp *lList, CmLList *node);
extern Void cmLListInsCrnt (CmLListCp *lList, CmLList *node);

extern Void cmLListInsAfterCrnt (CmLListCp *lList, CmLList *node);
extern CmLList *cmLListDelFrm (CmLListCp *lList, CmLList *node);
extern Void cmLListCatLList ( CmLListCp *list1, CmLListCp *list2);
typedef struct cmPAsnMsgCp CmPAsnMsgCp;


typedef U8 CmPAsnTknEnum;







typedef struct cmPAsnEnumDef
{



  CmPAsnTknEnum *enumLst;
  CmPAsnTknEnum *enumExtLst;
} CmPAsnEnumDef;



typedef struct cmPAsnBitStrDef
{



  U32 min;
  U32 max;
} CmPAsnBitStrDef;


typedef struct cmPAsnOctStrDef
{



  U32 min;
  U32 max;
} CmPAsnOctStrDef;


typedef struct cmPAsnSIntDef
{



  S32 min;
  S32 max;
} CmPAsnSIntDef;


typedef struct cmPAsnUIntXLDef
{



  struct
  {
     U32 len;
     U8 val[8];
  }min;

  struct
  {
     U32 len;
     U8 val[8];
  }max;
} CmPAsnUIntXLDef;


typedef struct cmPAsnUIntDef
{



  U32 min;
  U32 max;
} CmPAsnUIntDef;

typedef struct cmPAsnElmDef
{



   U8 type;
   Bool extMkr;
   U32 evSize;
   U32 *flagp;
   S16 (*func) (CmPAsnMsgCp *msgCp);

   U8 *typeSpecDef;
   void *defVal;
} CmPAsnElmDef;


typedef struct cmPAsnSetSeqOfDef
{



  U32 min;
  U32 max;
  U8 dbSize;
} CmPAsnSetSeqOfDef;


typedef struct cmPAsnSetSeqDef
{



  U32 preAmLen;
  U32 nmbExtMkrs;
  U32 extMkrEvOff;
  U16 extMkrDbOff;
  CmPAsnElmDef **ft;

  Bool allocEvnt;
} CmPAsnSetSeqDef;


typedef struct cmPAsnChoiceDef
{



 U16 nmbAltRoot;
 U16 nmbAltExt;
 CmPAsnElmDef **ft;

} CmPAsnChoiceDef;


typedef struct cmPAsnMulStrDef
{



  U32 *effAlp;
  U32 max;
  U32 min;
  U32 ub;
  U32 lb;
} CmPAsnMulStrDef;


typedef struct cmPAsnClassInfo
{

  U16 maxInstances;
  U32 *instIDs;
} CmPAsnClassInfo;


typedef struct cmPAsnClassIEDef
{



  CmPAsnClassInfo *classInf;

  U16 idEvntOffSet;
  CmPAsnElmDef **ieInst;



} CmPAsnClassIEDef;
typedef struct cmPAsnErr
{
   S16 errCode;







} CmPAsnErr;





typedef struct cmPAsnFBufInfo
{
   Data *bufP;
   U32 crntIdx;
   Size size;
} CmPAsnFBufInfo;






typedef struct cmPAsnBitHldr
{
   U8 byte;
   U8 nxtBitPos;
} CmPAsnBitHldr;





struct cmPAsnMsgCp
{
   U8 protType;
   U8 mMgmt;
   U8 perType;
   U8 cfg;
   Buffer *mBuf;
   CmPAsnFBufInfo fBuf;
   CmPAsnBitHldr bhldr;
   TknU8 *evntStr;
   CmPAsnElmDef **elmDef;
   Bool updEvnt;
   CmPAsnErr *err;
   CmMemListCp *memCp;





   Bool igExtMand;
   Buffer *unknownBuf;
};



extern S16 cmPAsnEncMsg (Void *event, U8 mMgmt, Void *outMPtr, U8 protocol, CmPAsnElmDef **msgDef, CmPAsnErr *err, U32 *fLen,Bool dbgFlag, Bool igExtMand)


                                               ;

extern S16 cmPAsnDecMsg (Void *event, U8 mMgmt, Void **inMPtr, U32 *numDecOct, U8 protocol, CmPAsnElmDef **msgDef, U8 cfg, CmPAsnErr *err, U32 fLen, CmMemListCp *lcp,Bool dbgFlag)



                                                              ;

extern S16 cmPAsnEncMsgUalign (Void *event, U8 mMgmt, Void *outMPtr, U8 protocol, CmPAsnElmDef **msgDef, CmPAsnErr *err, U32 *fLen,Bool dbgFlag, Bool igExtMand)


                                               ;

extern S16 cmPAsnDecMsgUalign (Void *event, U8 mMgmt, Void **inMPtr, U32 *numDecOct, U8 protocol, CmPAsnElmDef **msgDef, U8 cfg, CmPAsnErr *err, U32 fLen, CmMemListCp *lcp,Bool dbgFlag)



                                                              ;


extern S16 cmPAsnEncBitField (CmPAsnMsgCp *msgCp, U8 value, U8 size);

extern S16 cmPAsnRepAndEncBitField (CmPAsnMsgCp *msgCp, MsgLen lenIdx, U8 bitPos, U8 value)
                                                        ;

extern Void cmPAsnUpdDefVal ( TknU8 *evntStr, CmPAsnElmDef *temp_elm);
typedef enum enumCztCriticality
{
 CztCriticalityrejectEnum,
 CztCriticalityignoreEnum,
 CztCriticalitynotifyEnum
} EnumCztCriticality;
typedef TknU32 CztCriticality;


typedef enum enumCztPresence
{
 CztPresenceoptionalEnum,
 CztPresenceconditionalEnum,
 CztPresencemandatoryEnum
} EnumCztPresence;
typedef TknU32 CztPresence;


typedef TknU32 CztPrivIE_IDlocal;

typedef struct x2apPrivIE_ID
{
 TknU8 choice;
 union {
  CztPrivIE_IDlocal local;
 } val;
} CztPrivIE_ID;


typedef TknU32 CztProcedureCode;


typedef TknU32 CztProtIE_ID;


typedef enum enumCztTrgMsg
{
 CztTrgMsginitiating_messageEnum,
 CztTrgMsgsuccessful_outcomeEnum,
 CztTrgMsgunsuccessful_outcomeEnum
} EnumCztTrgMsg;
typedef TknU32 CztTrgMsg;


typedef TknStrBSXL CztABSInformFDDabs_pattern_info;

typedef enum enumCztABSInformFDDnumberOfCellSpecificAntennaPorts
{
 CztABSInformFDDnumberOfCellSpecificAntennaPortsoneEnum,
 CztABSInformFDDnumberOfCellSpecificAntennaPortstwoEnum,
 CztABSInformFDDnumberOfCellSpecificAntennaPortsfourEnum
} EnumCztABSInformFDDnumberOfCellSpecificAntennaPorts;
typedef TknU32 CztABSInformFDDnumberOfCellSpecificAntennaPorts;


typedef TknStrBSXL CztABSInformFDDmeasurement_subset;
typedef struct x2ap_ExtnABSInformFDD_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnABSInformFDD_ExtIEsCls;
typedef struct x2apProtExtnField_ABSInformFDD_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnABSInformFDD_ExtIEsCls extensionValue;
} CztProtExtnField_ABSInformFDD_ExtIEs;

typedef struct x2apProtExtnCont_ABSInformFDD_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_ABSInformFDD_ExtIEs *member;
}CztProtExtnCont_ABSInformFDD_ExtIEs;

typedef struct x2apABSInformFDD
{
 TknPres pres;
 CztABSInformFDDabs_pattern_info abs_pattern_info;
 CztABSInformFDDnumberOfCellSpecificAntennaPorts numberOfCellSpecificAntennaPorts;
 CztABSInformFDDmeasurement_subset measurement_subset;
 CztProtExtnCont_ABSInformFDD_ExtIEs iE_Extns;
} CztABSInformFDD;


typedef TknStrBSXL CztABSInformTDDabs_pattern_info;

typedef enum enumCztABSInformTDDnumberOfCellSpecificAntennaPorts
{
 CztABSInformTDDnumberOfCellSpecificAntennaPortsoneEnum,
 CztABSInformTDDnumberOfCellSpecificAntennaPortstwoEnum,
 CztABSInformTDDnumberOfCellSpecificAntennaPortsfourEnum
} EnumCztABSInformTDDnumberOfCellSpecificAntennaPorts;
typedef TknU32 CztABSInformTDDnumberOfCellSpecificAntennaPorts;


typedef TknStrBSXL CztABSInformTDDmeasurement_subset;
typedef struct x2ap_ExtnABSInformTDD_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnABSInformTDD_ExtIEsCls;
typedef struct x2apProtExtnField_ABSInformTDD_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnABSInformTDD_ExtIEsCls extensionValue;
} CztProtExtnField_ABSInformTDD_ExtIEs;

typedef struct x2apProtExtnCont_ABSInformTDD_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_ABSInformTDD_ExtIEs *member;
}CztProtExtnCont_ABSInformTDD_ExtIEs;

typedef struct x2apABSInformTDD
{
 TknPres pres;
 CztABSInformTDDabs_pattern_info abs_pattern_info;
 CztABSInformTDDnumberOfCellSpecificAntennaPorts numberOfCellSpecificAntennaPorts;
 CztABSInformTDDmeasurement_subset measurement_subset;
 CztProtExtnCont_ABSInformTDD_ExtIEs iE_Extns;
} CztABSInformTDD;

typedef struct x2apABSInform
{
 TknU8 choice;
 union {
  CztABSInformFDD fdd;
  CztABSInformTDD tdd;
 } val;
} CztABSInform;


typedef TknU32 CztDL_ABS_status;


typedef TknStrBSXL CztUsableABSInformFDDusable_abs_pattern_info;
typedef struct x2ap_ExtnUsableABSInformFDD_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnUsableABSInformFDD_ExtIEsCls;
typedef struct x2apProtExtnField_UsableABSInformFDD_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnUsableABSInformFDD_ExtIEsCls extensionValue;
} CztProtExtnField_UsableABSInformFDD_ExtIEs;

typedef struct x2apProtExtnCont_UsableABSInformFDD_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_UsableABSInformFDD_ExtIEs *member;
}CztProtExtnCont_UsableABSInformFDD_ExtIEs;

typedef struct x2apUsableABSInformFDD
{
 TknPres pres;
 CztUsableABSInformFDDusable_abs_pattern_info usable_abs_pattern_info;
 CztProtExtnCont_UsableABSInformFDD_ExtIEs iE_Extns;
} CztUsableABSInformFDD;


typedef TknStrBSXL CztUsableABSInformTDDusaable_abs_pattern_info;
typedef struct x2ap_ExtnUsableABSInformTDD_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnUsableABSInformTDD_ExtIEsCls;
typedef struct x2apProtExtnField_UsableABSInformTDD_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnUsableABSInformTDD_ExtIEsCls extensionValue;
} CztProtExtnField_UsableABSInformTDD_ExtIEs;

typedef struct x2apProtExtnCont_UsableABSInformTDD_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_UsableABSInformTDD_ExtIEs *member;
}CztProtExtnCont_UsableABSInformTDD_ExtIEs;

typedef struct x2apUsableABSInformTDD
{
 TknPres pres;
 CztUsableABSInformTDDusaable_abs_pattern_info usaable_abs_pattern_info;
 CztProtExtnCont_UsableABSInformTDD_ExtIEs iE_Extns;
} CztUsableABSInformTDD;

typedef struct x2apUsableABSInform
{
 TknU8 choice;
 union {
  CztUsableABSInformFDD fdd;
  CztUsableABSInformTDD tdd;
 } val;
} CztUsableABSInform;

typedef struct x2ap_ExtnABS_Status_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnABS_Status_ExtIEsCls;
typedef struct x2apProtExtnField_ABS_Status_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnABS_Status_ExtIEsCls extensionValue;
} CztProtExtnField_ABS_Status_ExtIEs;

typedef struct x2apProtExtnCont_ABS_Status_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_ABS_Status_ExtIEs *member;
}CztProtExtnCont_ABS_Status_ExtIEs;

typedef struct x2apABS_Status
{
 TknPres pres;
 CztDL_ABS_status dL_ABS_status;
 CztUsableABSInform usableABSInform;
 CztProtExtnCont_ABS_Status_ExtIEs iE_Extns;
} CztABS_Status;


typedef enum enumCztAdditionalSpecialSubframePatterns
{
 CztAdditionalSpecialSubframePatternsssp0Enum,
 CztAdditionalSpecialSubframePatternsssp1Enum,
 CztAdditionalSpecialSubframePatternsssp2Enum,
 CztAdditionalSpecialSubframePatternsssp3Enum,
 CztAdditionalSpecialSubframePatternsssp4Enum,
 CztAdditionalSpecialSubframePatternsssp5Enum,
 CztAdditionalSpecialSubframePatternsssp6Enum,
 CztAdditionalSpecialSubframePatternsssp7Enum,
 CztAdditionalSpecialSubframePatternsssp8Enum,
 CztAdditionalSpecialSubframePatternsssp9Enum
} EnumCztAdditionalSpecialSubframePatterns;
typedef TknU32 CztAdditionalSpecialSubframePatterns;


typedef enum enumCztCyclicPrefixDL
{
 CztCyclicPrefixDLnormalEnum,
 CztCyclicPrefixDLextendedEnum
} EnumCztCyclicPrefixDL;
typedef TknU32 CztCyclicPrefixDL;


typedef enum enumCztCyclicPrefixUL
{
 CztCyclicPrefixULnormalEnum,
 CztCyclicPrefixULextendedEnum
} EnumCztCyclicPrefixUL;
typedef TknU32 CztCyclicPrefixUL;

typedef struct x2ap_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls;
typedef struct x2apProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls extensionValue;
} CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs;

typedef struct x2apProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs *member;
}CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs;

typedef struct x2apAdditionalSpecialSubframe_Info
{
 TknPres pres;
 CztAdditionalSpecialSubframePatterns additionalspecialSubframePatterns;
 CztCyclicPrefixDL cyclicPrefixDL;
 CztCyclicPrefixUL cyclicPrefixUL;
 CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs iE_Extns;
} CztAdditionalSpecialSubframe_Info;


typedef TknStrBSXL CztKey_eNodeB_Star;

typedef TknU32 CztNextHopChainingCount;

typedef struct x2ap_ExtnAS_SecurInform_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnAS_SecurInform_ExtIEsCls;
typedef struct x2apProtExtnField_AS_SecurInform_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnAS_SecurInform_ExtIEsCls extensionValue;
} CztProtExtnField_AS_SecurInform_ExtIEs;

typedef struct x2apProtExtnCont_AS_SecurInform_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_AS_SecurInform_ExtIEs *member;
}CztProtExtnCont_AS_SecurInform_ExtIEs;

typedef struct x2apAS_SecurInform
{
 TknPres pres;
 CztKey_eNodeB_Star key_eNodeB_star;
 CztNextHopChainingCount nextHopChainingCount;
 CztProtExtnCont_AS_SecurInform_ExtIEs iE_Extns;
} CztAS_SecurInform;


typedef TknU32 CztPriorityLvl;


typedef enum enumCztPre_emptionCapblty
{
 CztPre_emptionCapbltyshall_not_trigger_pre_emptionEnum,
 CztPre_emptionCapbltymay_trigger_pre_emptionEnum
} EnumCztPre_emptionCapblty;
typedef TknU32 CztPre_emptionCapblty;


typedef enum enumCztPre_emptionVulnerability
{
 CztPre_emptionVulnerabilitynot_pre_emptableEnum,
 CztPre_emptionVulnerabilitypre_emptableEnum
} EnumCztPre_emptionVulnerability;
typedef TknU32 CztPre_emptionVulnerability;

typedef struct x2ap_ExtnAllocnAndRetentionPriority_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls;
typedef struct x2apProtExtnField_AllocnAndRetentionPriority_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls extensionValue;
} CztProtExtnField_AllocnAndRetentionPriority_ExtIEs;

typedef struct x2apProtExtnCont_AllocnAndRetentionPriority_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_AllocnAndRetentionPriority_ExtIEs *member;
}CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs;

typedef struct x2apAllocnAndRetentionPriority
{
 TknPres pres;
 CztPriorityLvl priorityLvl;
 CztPre_emptionCapblty pre_emptionCapblty;
 CztPre_emptionVulnerability pre_emptionVulnerability;
 CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs iE_Extns;
} CztAllocnAndRetentionPriority;


typedef TknStrOSXL CztPLMN_Identity;

typedef TknBStr32 CztEUTRANCellIdentifier;
typedef struct x2ap_ExtnECGI_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnECGI_ExtIEsCls;
typedef struct x2apProtExtnField_ECGI_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnECGI_ExtIEsCls extensionValue;
} CztProtExtnField_ECGI_ExtIEs;

typedef struct x2apProtExtnCont_ECGI_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_ECGI_ExtIEs *member;
}CztProtExtnCont_ECGI_ExtIEs;

typedef struct x2apECGI
{
 TknPres pres;
 CztPLMN_Identity pLMN_Identity;
 CztEUTRANCellIdentifier eUTRANcellIdentifier;
 CztProtExtnCont_ECGI_ExtIEs iE_Extns;
} CztECGI;

typedef struct x2apCellIdLstforMDT
{
 TknU16 noComp;
 CztECGI *member;
}CztCellIdLstforMDT;

typedef struct x2ap_ExtnCellBasedMDT_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCellBasedMDT_ExtIEsCls;
typedef struct x2apProtExtnField_CellBasedMDT_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCellBasedMDT_ExtIEsCls extensionValue;
} CztProtExtnField_CellBasedMDT_ExtIEs;

typedef struct x2apProtExtnCont_CellBasedMDT_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CellBasedMDT_ExtIEs *member;
}CztProtExtnCont_CellBasedMDT_ExtIEs;

typedef struct x2apCellBasedMDT
{
 TknPres pres;
 CztCellIdLstforMDT cellIdLstforMDT;
 CztProtExtnCont_CellBasedMDT_ExtIEs iE_Extns;
} CztCellBasedMDT;


typedef TknStr4 CztTAC;
typedef struct x2apTALstforMDT
{
 TknU16 noComp;
 CztTAC *member;
}CztTALstforMDT;

typedef struct x2ap_ExtnTABasedMDT_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnTABasedMDT_ExtIEsCls;
typedef struct x2apProtExtnField_TABasedMDT_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnTABasedMDT_ExtIEsCls extensionValue;
} CztProtExtnField_TABasedMDT_ExtIEs;

typedef struct x2apProtExtnCont_TABasedMDT_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_TABasedMDT_ExtIEs *member;
}CztProtExtnCont_TABasedMDT_ExtIEs;

typedef struct x2apTABasedMDT
{
 TknPres pres;
 CztTALstforMDT tALstforMDT;
 CztProtExtnCont_TABasedMDT_ExtIEs iE_Extns;
} CztTABasedMDT;

typedef struct x2ap_ExtnTAI_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnTAI_Item_ExtIEsCls;
typedef struct x2apProtExtnField_TAI_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnTAI_Item_ExtIEsCls extensionValue;
} CztProtExtnField_TAI_Item_ExtIEs;

typedef struct x2apProtExtnCont_TAI_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_TAI_Item_ExtIEs *member;
}CztProtExtnCont_TAI_Item_ExtIEs;

typedef struct x2apTAI_Item
{
 TknPres pres;
 CztTAC tAC;
 CztPLMN_Identity pLMN_Identity;
 CztProtExtnCont_TAI_Item_ExtIEs iE_Extns;
} CztTAI_Item;

typedef struct x2apTAILstforMDT
{
 TknU16 noComp;
 CztTAI_Item *member;
}CztTAILstforMDT;

typedef struct x2ap_ExtnTAIBasedMDT_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnTAIBasedMDT_ExtIEsCls;
typedef struct x2apProtExtnField_TAIBasedMDT_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnTAIBasedMDT_ExtIEsCls extensionValue;
} CztProtExtnField_TAIBasedMDT_ExtIEs;

typedef struct x2apProtExtnCont_TAIBasedMDT_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_TAIBasedMDT_ExtIEs *member;
}CztProtExtnCont_TAIBasedMDT_ExtIEs;

typedef struct x2apTAIBasedMDT
{
 TknPres pres;
 CztTAILstforMDT tAILstforMDT;
 CztProtExtnCont_TAIBasedMDT_ExtIEs iE_Extns;
} CztTAIBasedMDT;

typedef struct x2apAreaScopeOfMDT
{
 TknU8 choice;
 union {
  CztCellBasedMDT cellBased;
  CztTABasedMDT tABased;
  CztTAIBasedMDT tAIBased;
 } val;
} CztAreaScopeOfMDT;


typedef TknStrOSXL CztBitRate;

typedef struct x2apBroadcastPLMNs_Item
{
 TknU16 noComp;
 CztPLMN_Identity *member;
}CztBroadcastPLMNs_Item;


typedef TknU32 CztCapacityValue;


typedef TknU32 CztCellCapacityClassValue;


typedef enum enumCztCauseRadioNw
{
 CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum,
 CztCauseRadioNwtime_critical_handoverEnum,
 CztCauseRadioNwresource_optimisation_handoverEnum,
 CztCauseRadioNwreduce_load_in_serving_cellEnum,
 CztCauseRadioNwpartial_handoverEnum,
 CztCauseRadioNwunknown_new_eNB_UE_X2AP_IDEnum,
 CztCauseRadioNwunknown_old_eNB_UE_X2AP_IDEnum,
 CztCauseRadioNwunknown_pair_of_UE_X2AP_IDEnum,
 CztCauseRadioNwho_target_not_allowedEnum,
 CztCauseRadioNwtx2relocoverall_expiryEnum,
 CztCauseRadioNwtrelocprep_expiryEnum,
 CztCauseRadioNwcell_not_availableEnum,
 CztCauseRadioNwno_radio_resources_available_in_target_cellEnum,
 CztCauseRadioNwinvalid_MME_GroupIDEnum,
 CztCauseRadioNwunknown_MME_CodeEnum,
 CztCauseRadioNwencryption_and_or_integrity_protection_algorithms_not_supportedEnum,
 CztCauseRadioNwreportCharacteristicsEmptyEnum,
 CztCauseRadioNwnoReportPeriodicityEnum,
 CztCauseRadioNwexistingMeasurementIDEnum,
 CztCauseRadioNwunknown_eNB_Measurement_IDEnum,
 CztCauseRadioNwmeasurement_temporarily_not_availableEnum,
 CztCauseRadioNwunspecifiedEnum,
 CztCauseRadioNwload_balancingEnum,
 CztCauseRadioNwhandover_optimisationEnum,
 CztCauseRadioNwvalue_out_of_allowed_rangeEnum,
 CztCauseRadioNwmultiple_E_RAB_ID_instancesEnum,
 CztCauseRadioNwswitch_off_ongoingEnum,
 CztCauseRadioNwnot_supported_QCI_valueEnum,
 CztCauseRadioNwmeasurement_not_supported_for_the_objectEnum
} EnumCztCauseRadioNw;
typedef TknU32 CztCauseRadioNw;


typedef enum enumCztCauseTport
{
 CztCauseTporttransport_resource_unavailableEnum,
 CztCauseTportunspecifiedEnum
} EnumCztCauseTport;
typedef TknU32 CztCauseTport;


typedef enum enumCztCauseProt
{
 CztCauseProttransfer_syntax_errorEnum,
 CztCauseProtabstract_syntax_error_rejectEnum,
 CztCauseProtabstract_syntax_error_ignore_and_notifyEnum,
 CztCauseProtmessage_not_compatible_with_receiver_stateEnum,
 CztCauseProtsemantic_errorEnum,
 CztCauseProtunspecifiedEnum,
 CztCauseProtabstract_syntax_error_falsely_constructed_messageEnum
} EnumCztCauseProt;
typedef TknU32 CztCauseProt;


typedef enum enumCztCauseMisc
{
 CztCauseMisccontrol_processing_overloadEnum,
 CztCauseMischardware_failureEnum,
 CztCauseMiscom_interventionEnum,
 CztCauseMiscnot_enough_user_plane_processing_resourcesEnum,
 CztCauseMiscunspecifiedEnum
} EnumCztCauseMisc;
typedef TknU32 CztCauseMisc;

typedef struct x2apCause
{
 TknU8 choice;
 union {
  CztCauseRadioNw radioNw;
  CztCauseTport transport;
  CztCauseProt protocol;
  CztCauseMisc misc;
 } val;
} CztCause;


typedef enum enumCztCell_Size
{
 CztCell_SizeverysmallEnum,
 CztCell_SizesmallEnum,
 CztCell_SizemediumEnum,
 CztCell_SizelargeEnum
} EnumCztCell_Size;
typedef TknU32 CztCell_Size;

typedef struct x2ap_ExtnCellTyp_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCellTyp_ExtIEsCls;
typedef struct x2apProtExtnField_CellTyp_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCellTyp_ExtIEsCls extensionValue;
} CztProtExtnField_CellTyp_ExtIEs;

typedef struct x2apProtExtnCont_CellTyp_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CellTyp_ExtIEs *member;
}CztProtExtnCont_CellTyp_ExtIEs;

typedef struct x2apCellTyp
{
 TknPres pres;
 CztCell_Size cell_Size;
 CztProtExtnCont_CellTyp_ExtIEs iE_Extns;
} CztCellTyp;

typedef struct x2ap_ExtnCompositeAvailableCapacity_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCompositeAvailableCapacity_ExtIEsCls;
typedef struct x2apProtExtnField_CompositeAvailableCapacity_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCompositeAvailableCapacity_ExtIEsCls extensionValue;
} CztProtExtnField_CompositeAvailableCapacity_ExtIEs;

typedef struct x2apProtExtnCont_CompositeAvailableCapacity_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CompositeAvailableCapacity_ExtIEs *member;
}CztProtExtnCont_CompositeAvailableCapacity_ExtIEs;

typedef struct x2apCompositeAvailableCapacity
{
 TknPres pres;
 CztCellCapacityClassValue cellCapacityClassValue;
 CztCapacityValue capacityValue;
 CztProtExtnCont_CompositeAvailableCapacity_ExtIEs iE_Extns;
} CztCompositeAvailableCapacity;

typedef struct x2ap_ExtnCompositeAvailableCapacityGroup_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls;
typedef struct x2apProtExtnField_CompositeAvailableCapacityGroup_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls extensionValue;
} CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs;

typedef struct x2apProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs *member;
}CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs;

typedef struct x2apCompositeAvailableCapacityGroup
{
 TknPres pres;
 CztCompositeAvailableCapacity dL_CompositeAvailableCapacity;
 CztCompositeAvailableCapacity uL_CompositeAvailableCapacity;
 CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs iE_Extns;
} CztCompositeAvailableCapacityGroup;


typedef TknU32 CztPDCP_SN;


typedef TknU32 CztHFN;

typedef struct x2ap_ExtnCOUNTvalue_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCOUNTvalue_ExtIEsCls;
typedef struct x2apProtExtnField_COUNTvalue_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCOUNTvalue_ExtIEsCls extensionValue;
} CztProtExtnField_COUNTvalue_ExtIEs;

typedef struct x2apProtExtnCont_COUNTvalue_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_COUNTvalue_ExtIEs *member;
}CztProtExtnCont_COUNTvalue_ExtIEs;

typedef struct x2apCOUNTvalue
{
 TknPres pres;
 CztPDCP_SN pDCP_SN;
 CztHFN hFN;
 CztProtExtnCont_COUNTvalue_ExtIEs iE_Extns;
} CztCOUNTvalue;


typedef TknU32 CztPDCP_SNExtended;


typedef TknU32 CztHFNMdfd;

typedef struct x2ap_ExtnCOUNTValueExtended_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCOUNTValueExtended_ExtIEsCls;
typedef struct x2apProtExtnField_COUNTValueExtended_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCOUNTValueExtended_ExtIEsCls extensionValue;
} CztProtExtnField_COUNTValueExtended_ExtIEs;

typedef struct x2apProtExtnCont_COUNTValueExtended_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_COUNTValueExtended_ExtIEs *member;
}CztProtExtnCont_COUNTValueExtended_ExtIEs;

typedef struct x2apCOUNTValueExtended
{
 TknPres pres;
 CztPDCP_SNExtended pDCP_SNExtended;
 CztHFNMdfd hFNMdfd;
 CztProtExtnCont_COUNTValueExtended_ExtIEs iE_Extns;
} CztCOUNTValueExtended;


typedef enum enumCztTypOfErr
{
 CztTypOfErrnot_understoodEnum,
 CztTypOfErrmissingEnum
} EnumCztTypOfErr;
typedef TknU32 CztTypOfErr;

typedef struct x2ap_ExtnCriticalityDiag_IE_Lst_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls;
typedef struct x2apProtExtnField_CriticalityDiag_IE_Lst_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls extensionValue;
} CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs;

typedef struct x2apProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs *member;
}CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs;

typedef struct x2apCriticalityDiag_IE_LstMember
{
 TknPres pres;
 CztCriticality iECriticality;
 CztProtIE_ID iE_ID;
 CztTypOfErr typeOfErr;
 CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs iE_Extns;
} CztCriticalityDiag_IE_LstMember;

typedef struct x2apCriticalityDiag_IE_Lst
{
 TknU16 noComp;
 CztCriticalityDiag_IE_LstMember *member;
}CztCriticalityDiag_IE_Lst;

typedef struct x2ap_ExtnCriticalityDiag_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCriticalityDiag_ExtIEsCls;
typedef struct x2apProtExtnField_CriticalityDiag_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCriticalityDiag_ExtIEsCls extensionValue;
} CztProtExtnField_CriticalityDiag_ExtIEs;

typedef struct x2apProtExtnCont_CriticalityDiag_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CriticalityDiag_ExtIEs *member;
}CztProtExtnCont_CriticalityDiag_ExtIEs;

typedef struct x2apCriticalityDiag
{
 TknPres pres;
 CztProcedureCode procedureCode;
 CztTrgMsg triggeringMsg;
 CztCriticality procedureCriticality;
 CztCriticalityDiag_IE_Lst iEsCriticalityDiag;
 CztProtExtnCont_CriticalityDiag_ExtIEs iE_Extns;
} CztCriticalityDiag;


typedef TknBStr32 CztCRNTI;

typedef enum enumCztCSGMembershipStatus
{
 CztCSGMembershipStatusmemberEnum,
 CztCSGMembershipStatusnot_memberEnum
} EnumCztCSGMembershipStatus;
typedef TknU32 CztCSGMembershipStatus;


typedef TknBStr32 CztCSG_Id;

typedef enum enumCztDeactivationInd
{
 CztDeactivationInddeactivatedEnum
} EnumCztDeactivationInd;
typedef TknU32 CztDeactivationInd;


typedef enum enumCztDL_Fwding
{
 CztDL_FwdingdL_forwardingProposedEnum
} EnumCztDL_Fwding;
typedef TknU32 CztDL_Fwding;


typedef TknU32 CztDL_GBR_PRB_usage;


typedef TknU32 CztDL_non_GBR_PRB_usage;


typedef TknU32 CztDL_Total_PRB_usage;


typedef TknU32 CztEARFCN;


typedef TknU32 CztEARFCNExtn;


typedef enum enumCztTransmission_Bandwidth
{
 CztTransmission_Bandwidthbw6Enum,
 CztTransmission_Bandwidthbw15Enum,
 CztTransmission_Bandwidthbw25Enum,
 CztTransmission_Bandwidthbw50Enum,
 CztTransmission_Bandwidthbw75Enum,
 CztTransmission_Bandwidthbw100Enum
} EnumCztTransmission_Bandwidth;
typedef TknU32 CztTransmission_Bandwidth;

typedef struct x2ap_ExtnFDD_Info_ExtIEsCls{
 union {
  CztEARFCNExtn cztid_UL_EARFCNExtn;
  CztEARFCNExtn cztid_DL_EARFCNExtn;
 } u;
} Czt_ExtnFDD_Info_ExtIEsCls;
typedef struct x2apProtExtnField_FDD_Info_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnFDD_Info_ExtIEsCls extensionValue;
} CztProtExtnField_FDD_Info_ExtIEs;

typedef struct x2apProtExtnCont_FDD_Info_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_FDD_Info_ExtIEs *member;
}CztProtExtnCont_FDD_Info_ExtIEs;

typedef struct x2apFDD_Info
{
 TknPres pres;
 CztEARFCN uL_EARFCN;
 CztEARFCN dL_EARFCN;
 CztTransmission_Bandwidth uL_Transmission_Bandwidth;
 CztTransmission_Bandwidth dL_Transmission_Bandwidth;
 CztProtExtnCont_FDD_Info_ExtIEs iE_Extns;
} CztFDD_Info;


typedef enum enumCztSubframeAssignment
{
 CztSubframeAssignmentsa0Enum,
 CztSubframeAssignmentsa1Enum,
 CztSubframeAssignmentsa2Enum,
 CztSubframeAssignmentsa3Enum,
 CztSubframeAssignmentsa4Enum,
 CztSubframeAssignmentsa5Enum,
 CztSubframeAssignmentsa6Enum
} EnumCztSubframeAssignment;
typedef TknU32 CztSubframeAssignment;


typedef enum enumCztSpecialSubframePatterns
{
 CztSpecialSubframePatternsssp0Enum,
 CztSpecialSubframePatternsssp1Enum,
 CztSpecialSubframePatternsssp2Enum,
 CztSpecialSubframePatternsssp3Enum,
 CztSpecialSubframePatternsssp4Enum,
 CztSpecialSubframePatternsssp5Enum,
 CztSpecialSubframePatternsssp6Enum,
 CztSpecialSubframePatternsssp7Enum,
 CztSpecialSubframePatternsssp8Enum
} EnumCztSpecialSubframePatterns;
typedef TknU32 CztSpecialSubframePatterns;

typedef struct x2ap_ExtnSpecialSubframe_Info_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnSpecialSubframe_Info_ExtIEsCls;
typedef struct x2apProtExtnField_SpecialSubframe_Info_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnSpecialSubframe_Info_ExtIEsCls extensionValue;
} CztProtExtnField_SpecialSubframe_Info_ExtIEs;

typedef struct x2apProtExtnCont_SpecialSubframe_Info_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_SpecialSubframe_Info_ExtIEs *member;
}CztProtExtnCont_SpecialSubframe_Info_ExtIEs;

typedef struct x2apSpecialSubframe_Info
{
 TknPres pres;
 CztSpecialSubframePatterns specialSubframePatterns;
 CztCyclicPrefixDL cyclicPrefixDL;
 CztCyclicPrefixUL cyclicPrefixUL;
 CztProtExtnCont_SpecialSubframe_Info_ExtIEs iE_Extns;
} CztSpecialSubframe_Info;

typedef struct x2ap_ExtnTDD_Info_ExtIEsCls{
 union {
  CztAdditionalSpecialSubframe_Info cztAdditionalSpecialSubframe_Info;
  CztEARFCNExtn cztEARFCNExtn;
 } u;
} Czt_ExtnTDD_Info_ExtIEsCls;
typedef struct x2apProtExtnField_TDD_Info_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnTDD_Info_ExtIEsCls extensionValue;
} CztProtExtnField_TDD_Info_ExtIEs;

typedef struct x2apProtExtnCont_TDD_Info_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_TDD_Info_ExtIEs *member;
}CztProtExtnCont_TDD_Info_ExtIEs;

typedef struct x2apTDD_Info
{
 TknPres pres;
 CztEARFCN eARFCN;
 CztTransmission_Bandwidth transmission_Bandwidth;
 CztSubframeAssignment subframeAssignment;
 CztSpecialSubframe_Info specialSubframe_Info;
 CztProtExtnCont_TDD_Info_ExtIEs iE_Extns;
} CztTDD_Info;

typedef struct x2apEUTRA_Mode_Info
{
 TknU8 choice;
 union {
  CztFDD_Info fDD;
  CztTDD_Info tDD;
 } val;
} CztEUTRA_Mode_Info;


typedef TknBStr32 CztENB_IDmacro_eNB_ID;

typedef TknBStr32 CztENB_IDhome_eNB_ID;
typedef struct x2apENB_ID
{
 TknU8 choice;
 union {
  CztENB_IDmacro_eNB_ID macro_eNB_ID;
  CztENB_IDhome_eNB_ID home_eNB_ID;
 } val;
} CztENB_ID;


typedef TknBStr32 CztEncryptionAlgorithms;
typedef struct x2apEPLMNs
{
 TknU16 noComp;
 CztPLMN_Identity *member;
}CztEPLMNs;


typedef TknU32 CztE_RAB_ID;


typedef TknU32 CztQCI;

typedef struct x2ap_ExtnGBR_QosInform_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnGBR_QosInform_ExtIEsCls;
typedef struct x2apProtExtnField_GBR_QosInform_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnGBR_QosInform_ExtIEsCls extensionValue;
} CztProtExtnField_GBR_QosInform_ExtIEs;

typedef struct x2apProtExtnCont_GBR_QosInform_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_GBR_QosInform_ExtIEs *member;
}CztProtExtnCont_GBR_QosInform_ExtIEs;

typedef struct x2apGBR_QosInform
{
 TknPres pres;
 CztBitRate e_RAB_MaxBitrateDL;
 CztBitRate e_RAB_MaxBitrateUL;
 CztBitRate e_RAB_GuaranteedBitrateDL;
 CztBitRate e_RAB_GuaranteedBitrateUL;
 CztProtExtnCont_GBR_QosInform_ExtIEs iE_Extns;
} CztGBR_QosInform;

typedef struct x2ap_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls;
typedef struct x2apProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls extensionValue;
} CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs;

typedef struct x2apProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs *member;
}CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs;

typedef struct x2apE_RAB_Lvl_QoS_Params
{
 TknPres pres;
 CztQCI qCI;
 CztAllocnAndRetentionPriority allocationAndRetentionPriority;
 CztGBR_QosInform gbrQosInform;
 CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs iE_Extns;
} CztE_RAB_Lvl_QoS_Params;

typedef struct x2ap_ExtnE_RAB_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnE_RAB_Item_ExtIEsCls;
typedef struct x2apProtExtnField_E_RAB_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnE_RAB_Item_ExtIEsCls extensionValue;
} CztProtExtnField_E_RAB_Item_ExtIEs;

typedef struct x2apProtExtnCont_E_RAB_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_E_RAB_Item_ExtIEs *member;
}CztProtExtnCont_E_RAB_Item_ExtIEs;

typedef struct x2apE_RAB_Item
{
 TknPres pres;
 CztE_RAB_ID e_RAB_ID;
 CztCause cause;
 CztProtExtnCont_E_RAB_Item_ExtIEs iE_Extns;
} CztE_RAB_Item;

typedef struct x2ap_ValueE_RAB_ItemIEsCls{
 union {
  CztE_RAB_Item cztE_RAB_Item;
 } u;
} Czt_ValueE_RAB_ItemIEsCls;
typedef struct x2apProtIE_Field_E_RAB_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueE_RAB_ItemIEsCls value;
} CztProtIE_Field_E_RAB_ItemIEs;


typedef CztProtIE_Field_E_RAB_ItemIEs CztProtIE_Single_Cont_E_RAB_ItemIEs;
typedef struct x2apE_RAB_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_E_RAB_ItemIEs *member;
}CztE_RAB_Lst;


typedef TknStrOSXL CztEUTRANTraceID;

typedef enum enumCztEventTyp
{
 CztEventTypchange_of_serving_cellEnum
} EnumCztEventTyp;
typedef TknU32 CztEventTyp;


typedef enum enumCztForbiddenInterRATs
{
 CztForbiddenInterRATsallEnum,
 CztForbiddenInterRATsgeranEnum,
 CztForbiddenInterRATsutranEnum,
 CztForbiddenInterRATscdma2000Enum,
 CztForbiddenInterRATsgeranandutranEnum,
 CztForbiddenInterRATscdma2000andutranEnum
} EnumCztForbiddenInterRATs;
typedef TknU32 CztForbiddenInterRATs;

typedef struct x2apForbiddenTACs
{
 TknU16 noComp;
 CztTAC *member;
}CztForbiddenTACs;

typedef struct x2ap_ExtnForbiddenTAs_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnForbiddenTAs_Item_ExtIEsCls;
typedef struct x2apProtExtnField_ForbiddenTAs_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnForbiddenTAs_Item_ExtIEsCls extensionValue;
} CztProtExtnField_ForbiddenTAs_Item_ExtIEs;

typedef struct x2apProtExtnCont_ForbiddenTAs_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_ForbiddenTAs_Item_ExtIEs *member;
}CztProtExtnCont_ForbiddenTAs_Item_ExtIEs;

typedef struct x2apForbiddenTAs_Item
{
 TknPres pres;
 CztPLMN_Identity pLMN_Identity;
 CztForbiddenTACs forbiddenTACs;
 CztProtExtnCont_ForbiddenTAs_Item_ExtIEs iE_Extns;
} CztForbiddenTAs_Item;

typedef struct x2apForbiddenTAs
{
 TknU16 noComp;
 CztForbiddenTAs_Item *member;
}CztForbiddenTAs;


typedef TknStr4 CztLAC;
typedef struct x2apForbiddenLACs
{
 TknU16 noComp;
 CztLAC *member;
}CztForbiddenLACs;

typedef struct x2ap_ExtnForbiddenLAs_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnForbiddenLAs_Item_ExtIEsCls;
typedef struct x2apProtExtnField_ForbiddenLAs_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnForbiddenLAs_Item_ExtIEsCls extensionValue;
} CztProtExtnField_ForbiddenLAs_Item_ExtIEs;

typedef struct x2apProtExtnCont_ForbiddenLAs_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_ForbiddenLAs_Item_ExtIEs *member;
}CztProtExtnCont_ForbiddenLAs_Item_ExtIEs;

typedef struct x2apForbiddenLAs_Item
{
 TknPres pres;
 CztPLMN_Identity pLMN_Identity;
 CztForbiddenLACs forbiddenLACs;
 CztProtExtnCont_ForbiddenLAs_Item_ExtIEs iE_Extns;
} CztForbiddenLAs_Item;

typedef struct x2apForbiddenLAs
{
 TknU16 noComp;
 CztForbiddenLAs_Item *member;
}CztForbiddenLAs;


typedef TknBStr32 CztFourframes;

typedef TknU32 CztFreqBandIndicator;

typedef struct x2ap_ExtnGlobalENB_ID_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnGlobalENB_ID_ExtIEsCls;
typedef struct x2apProtExtnField_GlobalENB_ID_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnGlobalENB_ID_ExtIEsCls extensionValue;
} CztProtExtnField_GlobalENB_ID_ExtIEs;

typedef struct x2apProtExtnCont_GlobalENB_ID_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_GlobalENB_ID_ExtIEs *member;
}CztProtExtnCont_GlobalENB_ID_ExtIEs;

typedef struct x2apGlobalENB_ID
{
 TknPres pres;
 CztPLMN_Identity pLMN_Identity;
 CztENB_ID eNB_ID;
 CztProtExtnCont_GlobalENB_ID_ExtIEs iE_Extns;
} CztGlobalENB_ID;


typedef TknStrBSXL CztTportLyrAddr;

typedef TknStrOSXL CztGTP_TEI;
typedef struct x2ap_ExtnGTPtunnelEndpoint_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnGTPtunnelEndpoint_ExtIEsCls;
typedef struct x2apProtExtnField_GTPtunnelEndpoint_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnGTPtunnelEndpoint_ExtIEsCls extensionValue;
} CztProtExtnField_GTPtunnelEndpoint_ExtIEs;

typedef struct x2apProtExtnCont_GTPtunnelEndpoint_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_GTPtunnelEndpoint_ExtIEs *member;
}CztProtExtnCont_GTPtunnelEndpoint_ExtIEs;

typedef struct x2apGTPtunnelEndpoint
{
 TknPres pres;
 CztTportLyrAddr transportLyrAddr;
 CztGTP_TEI gTP_TEID;
 CztProtExtnCont_GTPtunnelEndpoint_ExtIEs iE_Extns;
} CztGTPtunnelEndpoint;


typedef TknStr4 CztMME_Group_ID;
typedef struct x2ap_ExtnGU_Group_ID_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnGU_Group_ID_ExtIEsCls;
typedef struct x2apProtExtnField_GU_Group_ID_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnGU_Group_ID_ExtIEsCls extensionValue;
} CztProtExtnField_GU_Group_ID_ExtIEs;

typedef struct x2apProtExtnCont_GU_Group_ID_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_GU_Group_ID_ExtIEs *member;
}CztProtExtnCont_GU_Group_ID_ExtIEs;

typedef struct x2apGU_Group_ID
{
 TknPres pres;
 CztPLMN_Identity pLMN_Identity;
 CztMME_Group_ID mME_Group_ID;
 CztProtExtnCont_GU_Group_ID_ExtIEs iE_Extns;
} CztGU_Group_ID;

typedef struct x2apGUGroupIDLst
{
 TknU16 noComp;
 CztGU_Group_ID *member;
}CztGUGroupIDLst;


typedef TknStr4 CztMME_Code;
typedef struct x2ap_ExtnGUMMEI_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnGUMMEI_ExtIEsCls;
typedef struct x2apProtExtnField_GUMMEI_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnGUMMEI_ExtIEsCls extensionValue;
} CztProtExtnField_GUMMEI_ExtIEs;

typedef struct x2apProtExtnCont_GUMMEI_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_GUMMEI_ExtIEs *member;
}CztProtExtnCont_GUMMEI_ExtIEs;

typedef struct x2apGUMMEI
{
 TknPres pres;
 CztGU_Group_ID gU_Group_ID;
 CztMME_Code mME_Code;
 CztProtExtnCont_GUMMEI_ExtIEs iE_Extns;
} CztGUMMEI;


typedef enum enumCztHovrReportTyp
{
 CztHovrReportTyphoTooEarlyEnum,
 CztHovrReportTyphoToWrongCellEnum,
 CztHovrReportTypinterRATpingpongEnum
} EnumCztHovrReportTyp;
typedef TknU32 CztHovrReportTyp;

typedef struct x2ap_ExtnHovrRestrnLst_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnHovrRestrnLst_ExtIEsCls;
typedef struct x2apProtExtnField_HovrRestrnLst_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnHovrRestrnLst_ExtIEsCls extensionValue;
} CztProtExtnField_HovrRestrnLst_ExtIEs;

typedef struct x2apProtExtnCont_HovrRestrnLst_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_HovrRestrnLst_ExtIEs *member;
}CztProtExtnCont_HovrRestrnLst_ExtIEs;

typedef struct x2apHovrRestrnLst
{
 TknPres pres;
 CztPLMN_Identity servingPLMN;
 CztEPLMNs equivalentPLMNs;
 CztForbiddenTAs forbiddenTAs;
 CztForbiddenLAs forbiddenLAs;
 CztForbiddenInterRATs forbiddenInterRATs;
 CztProtExtnCont_HovrRestrnLst_ExtIEs iE_Extns;
} CztHovrRestrnLst;


typedef enum enumCztLoadIndicator
{
 CztLoadIndicatorlowLoadEnum,
 CztLoadIndicatormediumLoadEnum,
 CztLoadIndicatorhighLoadEnum,
 CztLoadIndicatoroverLoadEnum
} EnumCztLoadIndicator;
typedef TknU32 CztLoadIndicator;

typedef struct x2ap_ExtnHWLoadIndicator_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnHWLoadIndicator_ExtIEsCls;
typedef struct x2apProtExtnField_HWLoadIndicator_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnHWLoadIndicator_ExtIEsCls extensionValue;
} CztProtExtnField_HWLoadIndicator_ExtIEs;

typedef struct x2apProtExtnCont_HWLoadIndicator_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_HWLoadIndicator_ExtIEs *member;
}CztProtExtnCont_HWLoadIndicator_ExtIEs;

typedef struct x2apHWLoadIndicator
{
 TknPres pres;
 CztLoadIndicator dLHWLoadIndicator;
 CztLoadIndicator uLHWLoadIndicator;
 CztProtExtnCont_HWLoadIndicator_ExtIEs iE_Extns;
} CztHWLoadIndicator;


typedef enum enumCztInvokeInd
{
 CztInvokeIndabs_informationEnum
} EnumCztInvokeInd;
typedef TknU32 CztInvokeInd;


typedef TknBStr32 CztIntegrityProtectionAlgorithms;

typedef TknBStr32 CztIntfsToTrace;

typedef TknU32 CztTime_UE_StayedInCell;


typedef TknU32 CztTime_UE_StayedInCell_EnhancedGranularity;

typedef struct x2ap_ExtnLastVisitedEUTRANCellInform_ExtIEsCls{
 union {
  CztTime_UE_StayedInCell_EnhancedGranularity cztTime_UE_StayedInCell_EnhancedGranularity;
  CztCause cztCause;
 } u;
} Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls;
typedef struct x2apProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls extensionValue;
} CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs;

typedef struct x2apProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *member;
}CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs;

typedef struct x2apLastVisitedEUTRANCellInform
{
 TknPres pres;
 CztECGI global_Cell_ID;
 CztCellTyp cellTyp;
 CztTime_UE_StayedInCell time_UE_StayedInCell;
 CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs iE_Extns;
} CztLastVisitedEUTRANCellInform;


typedef TknStrOSXL CztLastVisitedUTRANCellInform;
typedef struct x2apLastVisitedGERANCellInform
{
 TknU8 choice;
} CztLastVisitedGERANCellInform;

typedef struct x2apLastVisitedCell_Item
{
 TknU8 choice;
 union {
  CztLastVisitedEUTRANCellInform e_UTRAN_Cell;
  CztLastVisitedUTRANCellInform uTRAN_Cell;
  CztLastVisitedGERANCellInform gERAN_Cell;
 } val;
} CztLastVisitedCell_Item;


typedef enum enumCztLinks_to_log
{
 CztLinks_to_loguplinkEnum,
 CztLinks_to_logdownlinkEnum,
 CztLinks_to_logboth_uplink_and_downlinkEnum
} EnumCztLinks_to_log;
typedef TknU32 CztLinks_to_log;


typedef enum enumCztReportArea
{
 CztReportAreaecgiEnum
} EnumCztReportArea;
typedef TknU32 CztReportArea;

typedef struct x2ap_ExtnLocRprtngInform_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnLocRprtngInform_ExtIEsCls;
typedef struct x2apProtExtnField_LocRprtngInform_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnLocRprtngInform_ExtIEsCls extensionValue;
} CztProtExtnField_LocRprtngInform_ExtIEs;

typedef struct x2apProtExtnCont_LocRprtngInform_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_LocRprtngInform_ExtIEs *member;
}CztProtExtnCont_LocRprtngInform_ExtIEs;

typedef struct x2apLocRprtngInform
{
 TknPres pres;
 CztEventTyp eventTyp;
 CztReportArea reportArea;
 CztProtExtnCont_LocRprtngInform_ExtIEs iE_Extns;
} CztLocRprtngInform;


typedef enum enumCztM3period
{
 CztM3periodms100Enum,
 CztM3periodms1000Enum,
 CztM3periodms10000Enum
} EnumCztM3period;
typedef TknU32 CztM3period;

typedef struct x2ap_ExtnM3Config_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnM3Config_ExtIEsCls;
typedef struct x2apProtExtnField_M3Config_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnM3Config_ExtIEsCls extensionValue;
} CztProtExtnField_M3Config_ExtIEs;

typedef struct x2apProtExtnCont_M3Config_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_M3Config_ExtIEs *member;
}CztProtExtnCont_M3Config_ExtIEs;

typedef struct x2apM3Config
{
 TknPres pres;
 CztM3period m3period;
 CztProtExtnCont_M3Config_ExtIEs iE_Extns;
} CztM3Config;


typedef enum enumCztM4period
{
 CztM4periodms1024Enum,
 CztM4periodms2048Enum,
 CztM4periodms5120Enum,
 CztM4periodms10240Enum,
 CztM4periodmin1Enum
} EnumCztM4period;
typedef TknU32 CztM4period;

typedef struct x2ap_ExtnM4Config_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnM4Config_ExtIEsCls;
typedef struct x2apProtExtnField_M4Config_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnM4Config_ExtIEsCls extensionValue;
} CztProtExtnField_M4Config_ExtIEs;

typedef struct x2apProtExtnCont_M4Config_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_M4Config_ExtIEs *member;
}CztProtExtnCont_M4Config_ExtIEs;

typedef struct x2apM4Config
{
 TknPres pres;
 CztM4period m4period;
 CztLinks_to_log m4_links_to_log;
 CztProtExtnCont_M4Config_ExtIEs iE_Extns;
} CztM4Config;


typedef enum enumCztM5period
{
 CztM5periodms1024Enum,
 CztM5periodms2048Enum,
 CztM5periodms5120Enum,
 CztM5periodms10240Enum,
 CztM5periodmin1Enum
} EnumCztM5period;
typedef TknU32 CztM5period;

typedef struct x2ap_ExtnM5Config_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnM5Config_ExtIEsCls;
typedef struct x2apProtExtnField_M5Config_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnM5Config_ExtIEsCls extensionValue;
} CztProtExtnField_M5Config_ExtIEs;

typedef struct x2apProtExtnCont_M5Config_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_M5Config_ExtIEs *member;
}CztProtExtnCont_M5Config_ExtIEs;

typedef struct x2apM5Config
{
 TknPres pres;
 CztM5period m5period;
 CztLinks_to_log m5_links_to_log;
 CztProtExtnCont_M5Config_ExtIEs iE_Extns;
} CztM5Config;


typedef enum enumCztMDT_Actvn
{
 CztMDT_Actvnimmediate_MDT_onlyEnum,
 CztMDT_Actvnimmediate_MDT_and_TraceEnum
} EnumCztMDT_Actvn;
typedef TknU32 CztMDT_Actvn;


typedef TknBStr32 CztMeasurementsToActivate;

typedef enum enumCztM1RprtngTrigger
{
 CztM1RprtngTriggerperiodicEnum,
 CztM1RprtngTriggera2eventtriggeredEnum,
 CztM1RprtngTriggera2eventtriggered_periodicEnum
} EnumCztM1RprtngTrigger;
typedef TknU32 CztM1RprtngTrigger;


typedef TknU32 CztThreshold_RSRP;


typedef TknU32 CztThreshold_RSRQ;

typedef struct x2apMeasurementThresholdA2
{
 TknU8 choice;
 union {
  CztThreshold_RSRP threshold_RSRP;
  CztThreshold_RSRQ threshold_RSRQ;
 } val;
} CztMeasurementThresholdA2;

typedef struct x2ap_ExtnM1ThresholdEventA2_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnM1ThresholdEventA2_ExtIEsCls;
typedef struct x2apProtExtnField_M1ThresholdEventA2_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnM1ThresholdEventA2_ExtIEsCls extensionValue;
} CztProtExtnField_M1ThresholdEventA2_ExtIEs;

typedef struct x2apProtExtnCont_M1ThresholdEventA2_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_M1ThresholdEventA2_ExtIEs *member;
}CztProtExtnCont_M1ThresholdEventA2_ExtIEs;

typedef struct x2apM1ThresholdEventA2
{
 TknPres pres;
 CztMeasurementThresholdA2 measurementThreshold;
 CztProtExtnCont_M1ThresholdEventA2_ExtIEs iE_Extns;
} CztM1ThresholdEventA2;


typedef enum enumCztReportIntervalMDT
{
 CztReportIntervalMDTms120Enum,
 CztReportIntervalMDTms240Enum,
 CztReportIntervalMDTms480Enum,
 CztReportIntervalMDTms640Enum,
 CztReportIntervalMDTms1024Enum,
 CztReportIntervalMDTms2048Enum,
 CztReportIntervalMDTms5120Enum,
 CztReportIntervalMDTms10240Enum,
 CztReportIntervalMDTmin1Enum,
 CztReportIntervalMDTmin6Enum,
 CztReportIntervalMDTmin12Enum,
 CztReportIntervalMDTmin30Enum,
 CztReportIntervalMDTmin60Enum
} EnumCztReportIntervalMDT;
typedef TknU32 CztReportIntervalMDT;


typedef enum enumCztReportAmountMDT
{
 CztReportAmountMDTr1Enum,
 CztReportAmountMDTr2Enum,
 CztReportAmountMDTr4Enum,
 CztReportAmountMDTr8Enum,
 CztReportAmountMDTr16Enum,
 CztReportAmountMDTr32Enum,
 CztReportAmountMDTr64Enum,
 CztReportAmountMDTrinfinityEnum
} EnumCztReportAmountMDT;
typedef TknU32 CztReportAmountMDT;

typedef struct x2ap_ExtnM1PeriodicRprtng_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnM1PeriodicRprtng_ExtIEsCls;
typedef struct x2apProtExtnField_M1PeriodicRprtng_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnM1PeriodicRprtng_ExtIEsCls extensionValue;
} CztProtExtnField_M1PeriodicRprtng_ExtIEs;

typedef struct x2apProtExtnCont_M1PeriodicRprtng_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_M1PeriodicRprtng_ExtIEs *member;
}CztProtExtnCont_M1PeriodicRprtng_ExtIEs;

typedef struct x2apM1PeriodicRprtng
{
 TknPres pres;
 CztReportIntervalMDT reportInterval;
 CztReportAmountMDT reportAmount;
 CztProtExtnCont_M1PeriodicRprtng_ExtIEs iE_Extns;
} CztM1PeriodicRprtng;


typedef TknBStr32 CztMDT_Loc_Info;
typedef struct x2apMDTPLMNLst
{
 TknU16 noComp;
 CztPLMN_Identity *member;
}CztMDTPLMNLst;

typedef struct x2ap_ExtnMDT_Config_ExtIEsCls{
 union {
  CztM3Config cztM3Config;
  CztM4Config cztM4Config;
  CztM5Config cztM5Config;
  CztMDT_Loc_Info cztMDT_Loc_Info;
  CztMDTPLMNLst cztMDTPLMNLst;
 } u;
} Czt_ExtnMDT_Config_ExtIEsCls;
typedef struct x2apProtExtnField_MDT_Config_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnMDT_Config_ExtIEsCls extensionValue;
} CztProtExtnField_MDT_Config_ExtIEs;

typedef struct x2apProtExtnCont_MDT_Config_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_MDT_Config_ExtIEs *member;
}CztProtExtnCont_MDT_Config_ExtIEs;

typedef struct x2apMDT_Config
{
 TknPres pres;
 CztMDT_Actvn mdt_Actvn;
 CztAreaScopeOfMDT areaScopeOfMDT;
 CztMeasurementsToActivate measurementsToActivate;
 CztM1RprtngTrigger m1reportingTrigger;
 CztM1ThresholdEventA2 m1thresholdeventA2;
 CztM1PeriodicRprtng m1periodicRprtng;
 CztProtExtnCont_MDT_Config_ExtIEs iE_Extns;
} CztMDT_Config;


typedef TknU32 CztMeasurement_ID;


typedef TknStr4 CztMBMS_Service_Area_Identity;
typedef struct x2apMBMS_Service_Area_Identity_Lst
{
 TknU16 noComp;
 CztMBMS_Service_Area_Identity *member;
}CztMBMS_Service_Area_Identity_Lst;


typedef enum enumCztRadioframeAllocnPeriod
{
 CztRadioframeAllocnPeriodn1Enum,
 CztRadioframeAllocnPeriodn2Enum,
 CztRadioframeAllocnPeriodn4Enum,
 CztRadioframeAllocnPeriodn8Enum,
 CztRadioframeAllocnPeriodn16Enum,
 CztRadioframeAllocnPeriodn32Enum
} EnumCztRadioframeAllocnPeriod;
typedef TknU32 CztRadioframeAllocnPeriod;


typedef TknU32 CztRadioframeAllocnOffset;


typedef TknBStr32 CztOneframe;
typedef struct x2apSubframeAllocn
{
 TknU8 choice;
 union {
  CztOneframe oneframe;
  CztFourframes fourframes;
 } val;
} CztSubframeAllocn;

typedef struct x2ap_ExtnMBSFN_Subframe_Info_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls;
typedef struct x2apProtExtnField_MBSFN_Subframe_Info_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls extensionValue;
} CztProtExtnField_MBSFN_Subframe_Info_ExtIEs;

typedef struct x2apProtExtnCont_MBSFN_Subframe_Info_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_MBSFN_Subframe_Info_ExtIEs *member;
}CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs;

typedef struct x2apMBSFN_Subframe_Info
{
 TknPres pres;
 CztRadioframeAllocnPeriod radioframeAllocnPeriod;
 CztRadioframeAllocnOffset radioframeAllocnOffset;
 CztSubframeAllocn subframeAllocn;
 CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs iE_Extns;
} CztMBSFN_Subframe_Info;

typedef struct x2apMBSFN_Subframe_Infolist
{
 TknU16 noComp;
 CztMBSFN_Subframe_Info *member;
}CztMBSFN_Subframe_Infolist;


typedef enum enumCztManagementBasedMDTallowed
{
 CztManagementBasedMDTallowedallowedEnum
} EnumCztManagementBasedMDTallowed;
typedef TknU32 CztManagementBasedMDTallowed;


typedef TknS32 CztMobilityParamsModificationRangehandoverTriggerChangeLowerLimit;


typedef TknS32 CztMobilityParamsModificationRangehandoverTriggerChangeUpperLimit;

typedef struct x2apMobilityParamsModificationRange
{
 TknPres pres;
 CztMobilityParamsModificationRangehandoverTriggerChangeLowerLimit handoverTriggerChangeLowerLimit;
 CztMobilityParamsModificationRangehandoverTriggerChangeUpperLimit handoverTriggerChangeUpperLimit;
} CztMobilityParamsModificationRange;


typedef TknS32 CztMobilityParamsInformhandoverTriggerChange;

typedef struct x2apMobilityParamsInform
{
 TknPres pres;
 CztMobilityParamsInformhandoverTriggerChange handoverTriggerChange;
} CztMobilityParamsInform;

typedef struct x2ap_ExtnBandInfo_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnBandInfo_ExtIEsCls;
typedef struct x2apProtExtnField_BandInfo_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnBandInfo_ExtIEsCls extensionValue;
} CztProtExtnField_BandInfo_ExtIEs;

typedef struct x2apProtExtnCont_BandInfo_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_BandInfo_ExtIEs *member;
}CztProtExtnCont_BandInfo_ExtIEs;

typedef struct x2apBandInfo
{
 TknPres pres;
 CztFreqBandIndicator freqBandIndicator;
 CztProtExtnCont_BandInfo_ExtIEs iE_Extns;
} CztBandInfo;

typedef struct x2apMultibandInfoLst
{
 TknU16 noComp;
 CztBandInfo *member;
}CztMultibandInfoLst;


typedef TknU32 CztPCI;

typedef struct x2ap_ExtnNeighbour_Inform_ExtIEsCls{
 union {
  CztTAC cztTAC;
  CztEARFCNExtn cztEARFCNExtn;
 } u;
} Czt_ExtnNeighbour_Inform_ExtIEsCls;
typedef struct x2apProtExtnField_Neighbour_Inform_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnNeighbour_Inform_ExtIEsCls extensionValue;
} CztProtExtnField_Neighbour_Inform_ExtIEs;

typedef struct x2apProtExtnCont_Neighbour_Inform_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_Neighbour_Inform_ExtIEs *member;
}CztProtExtnCont_Neighbour_Inform_ExtIEs;

typedef struct x2apNeighbour_InformMember
{
 TknPres pres;
 CztECGI eCGI;
 CztPCI pCI;
 CztEARFCN eARFCN;
 CztProtExtnCont_Neighbour_Inform_ExtIEs iE_Extns;
} CztNeighbour_InformMember;

typedef struct x2apNeighbour_Inform
{
 TknU16 noComp;
 CztNeighbour_InformMember *member;
}CztNeighbour_Inform;


typedef enum enumCztNumber_of_Antennaports
{
 CztNumber_of_Antennaportsan1Enum,
 CztNumber_of_Antennaportsan2Enum,
 CztNumber_of_Antennaportsan4Enum
} EnumCztNumber_of_Antennaports;
typedef TknU32 CztNumber_of_Antennaports;


typedef TknU32 CztPRACH_ConfigrootSequenceIdx;


typedef TknU32 CztPRACH_ConfigzeroCorrelationIdx;


typedef TknU8 CztPRACH_ConfighighSpeedFlag;


typedef TknU32 CztPRACH_Configprach_FreqOffset;


typedef TknU32 CztPRACH_Configprach_ConfigIdx;

typedef struct x2ap_ExtnPRACH_Config_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnPRACH_Config_ExtIEsCls;
typedef struct x2apProtExtnField_PRACH_Config_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnPRACH_Config_ExtIEsCls extensionValue;
} CztProtExtnField_PRACH_Config_ExtIEs;

typedef struct x2apProtExtnCont_PRACH_Config_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_PRACH_Config_ExtIEs *member;
}CztProtExtnCont_PRACH_Config_ExtIEs;

typedef struct x2apPRACH_Config
{
 TknPres pres;
 CztPRACH_ConfigrootSequenceIdx rootSequenceIdx;
 CztPRACH_ConfigzeroCorrelationIdx zeroCorrelationIdx;
 CztPRACH_ConfighighSpeedFlag highSpeedFlag;
 CztPRACH_Configprach_FreqOffset prach_FreqOffset;
 CztPRACH_Configprach_ConfigIdx prach_ConfigIdx;
 CztProtExtnCont_PRACH_Config_ExtIEs iE_Extns;
} CztPRACH_Config;


typedef TknU32 CztUL_GBR_PRB_usage;


typedef TknU32 CztUL_non_GBR_PRB_usage;


typedef TknU32 CztUL_Total_PRB_usage;

typedef struct x2ap_ExtnRadioResStatus_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnRadioResStatus_ExtIEsCls;
typedef struct x2apProtExtnField_RadioResStatus_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnRadioResStatus_ExtIEsCls extensionValue;
} CztProtExtnField_RadioResStatus_ExtIEs;

typedef struct x2apProtExtnCont_RadioResStatus_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_RadioResStatus_ExtIEs *member;
}CztProtExtnCont_RadioResStatus_ExtIEs;

typedef struct x2apRadioResStatus
{
 TknPres pres;
 CztDL_GBR_PRB_usage dL_GBR_PRB_usage;
 CztUL_GBR_PRB_usage uL_GBR_PRB_usage;
 CztDL_non_GBR_PRB_usage dL_non_GBR_PRB_usage;
 CztUL_non_GBR_PRB_usage uL_non_GBR_PRB_usage;
 CztDL_Total_PRB_usage dL_Total_PRB_usage;
 CztUL_Total_PRB_usage uL_Total_PRB_usage;
 CztProtExtnCont_RadioResStatus_ExtIEs iE_Extns;
} CztRadioResStatus;


typedef TknStrBSXL CztReceiveStatusofULPDCPSDUs;

typedef TknStrBSXL CztReceiveStatusOfULPDCPSDUsExtended;

typedef enum enumCztRegistration_Rqst
{
 CztRegistration_RqststartEnum,
 CztRegistration_RqststopEnum
} EnumCztRegistration_Rqst;
typedef TknU32 CztRegistration_Rqst;


typedef enum enumCztRNTP_Threshold
{
 CztRNTP_ThresholdminusInfinityEnum,
 CztRNTP_ThresholdminusElevenEnum,
 CztRNTP_ThresholdminusTenEnum,
 CztRNTP_ThresholdminusNineEnum,
 CztRNTP_ThresholdminusEightEnum,
 CztRNTP_ThresholdminusSevenEnum,
 CztRNTP_ThresholdminusSixEnum,
 CztRNTP_ThresholdminusFiveEnum,
 CztRNTP_ThresholdminusFourEnum,
 CztRNTP_ThresholdminusThreeEnum,
 CztRNTP_ThresholdminusTwoEnum,
 CztRNTP_ThresholdminusOneEnum,
 CztRNTP_ThresholdzeroEnum,
 CztRNTP_ThresholdoneEnum,
 CztRNTP_ThresholdtwoEnum,
 CztRNTP_ThresholdthreeEnum
} EnumCztRNTP_Threshold;
typedef TknU32 CztRNTP_Threshold;


typedef TknStrBSXL CztRelativeNarrowbandTxPowerrNTP_PerPRB;

typedef enum enumCztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts
{
 CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortsoneEnum,
 CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortstwoEnum,
 CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortsfourEnum
} EnumCztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts;
typedef TknU32 CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts;


typedef TknU32 CztRelativeNarrowbandTxPowerp_B;


typedef TknU32 CztRelativeNarrowbandTxPowerpDCCH_InterferenceImpact;

typedef struct x2ap_ExtnRelativeNarrowbandTxPower_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls;
typedef struct x2apProtExtnField_RelativeNarrowbandTxPower_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls extensionValue;
} CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs;

typedef struct x2apProtExtnCont_RelativeNarrowbandTxPower_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs *member;
}CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs;

typedef struct x2apRelativeNarrowbandTxPower
{
 TknPres pres;
 CztRelativeNarrowbandTxPowerrNTP_PerPRB rNTP_PerPRB;
 CztRNTP_Threshold rNTP_Threshold;
 CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts numberOfCellSpecificAntennaPorts;
 CztRelativeNarrowbandTxPowerp_B p_B;
 CztRelativeNarrowbandTxPowerpDCCH_InterferenceImpact pDCCH_InterferenceImpact;
 CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs iE_Extns;
} CztRelativeNarrowbandTxPower;


typedef TknBStr32 CztReportCharacteristics;

typedef TknStrOSXL CztRRC_Cntxt;

typedef enum enumCztRRCConnReestabIndicator
{
 CztRRCConnReestabIndicatorreconfigurationFailEnum,
 CztRRCConnReestabIndicatorhandoverFailEnum,
 CztRRCConnReestabIndicatorotherFailEnum
} EnumCztRRCConnReestabIndicator;
typedef TknU32 CztRRCConnReestabIndicator;


typedef enum enumCztRRCConnSetupIndicator
{
 CztRRCConnSetupIndicatorrrcConnSetupEnum
} EnumCztRRCConnSetupIndicator;
typedef TknU32 CztRRCConnSetupIndicator;

typedef struct x2ap_ExtnS1TNLLoadIndicator_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnS1TNLLoadIndicator_ExtIEsCls;
typedef struct x2apProtExtnField_S1TNLLoadIndicator_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnS1TNLLoadIndicator_ExtIEsCls extensionValue;
} CztProtExtnField_S1TNLLoadIndicator_ExtIEs;

typedef struct x2apProtExtnCont_S1TNLLoadIndicator_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_S1TNLLoadIndicator_ExtIEs *member;
}CztProtExtnCont_S1TNLLoadIndicator_ExtIEs;

typedef struct x2apS1TNLLoadIndicator
{
 TknPres pres;
 CztLoadIndicator dLS1TNLLoadIndicator;
 CztLoadIndicator uLS1TNLLoadIndicator;
 CztProtExtnCont_S1TNLLoadIndicator_ExtIEs iE_Extns;
} CztS1TNLLoadIndicator;

typedef struct x2ap_ExtnSrvdCell_Inform_ExtIEsCls{
 union {
  CztNumber_of_Antennaports cztNumber_of_Antennaports;
  CztPRACH_Config cztPRACH_Config;
  CztMBSFN_Subframe_Infolist cztMBSFN_Subframe_Infolist;
  CztCSG_Id cztCSG_Id;
  CztMBMS_Service_Area_Identity_Lst cztMBMS_Service_Area_Identity_Lst;
  CztMultibandInfoLst cztMultibandInfoLst;
 } u;
} Czt_ExtnSrvdCell_Inform_ExtIEsCls;
typedef struct x2apProtExtnField_SrvdCell_Inform_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnSrvdCell_Inform_ExtIEsCls extensionValue;
} CztProtExtnField_SrvdCell_Inform_ExtIEs;

typedef struct x2apProtExtnCont_SrvdCell_Inform_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_SrvdCell_Inform_ExtIEs *member;
}CztProtExtnCont_SrvdCell_Inform_ExtIEs;

typedef struct x2apSrvdCell_Inform
{
 TknPres pres;
 CztPCI pCI;
 CztECGI cellId;
 CztTAC tAC;
 CztBroadcastPLMNs_Item broadcastPLMNs;
 CztEUTRA_Mode_Info eUTRA_Mode_Info;
 CztProtExtnCont_SrvdCell_Inform_ExtIEs iE_Extns;
} CztSrvdCell_Inform;

typedef struct x2ap_ExtnSrvdCell_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnSrvdCell_ExtIEsCls;
typedef struct x2apProtExtnField_SrvdCell_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnSrvdCell_ExtIEsCls extensionValue;
} CztProtExtnField_SrvdCell_ExtIEs;

typedef struct x2apProtExtnCont_SrvdCell_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_SrvdCell_ExtIEs *member;
}CztProtExtnCont_SrvdCell_ExtIEs;

typedef struct x2apSrvdCellsMember
{
 TknPres pres;
 CztSrvdCell_Inform servedCellInfo;
 CztNeighbour_Inform neighbour_Info;
 CztProtExtnCont_SrvdCell_ExtIEs iE_Extns;
} CztSrvdCellsMember;

typedef struct x2apSrvdCells
{
 TknU16 noComp;
 CztSrvdCellsMember *member;
}CztSrvdCells;


typedef TknBStr32 CztShortMAC_I;

typedef enum enumCztSRVCCOperationPossible
{
 CztSRVCCOperationPossiblepossibleEnum
} EnumCztSRVCCOperationPossible;
typedef TknU32 CztSRVCCOperationPossible;


typedef TknU32 CztSubscriberProfileIDforRFP;


typedef TknStrOSXL CztTgetCellInUTRAN;

typedef TknStrOSXL CztTgeteNBtoSrc_eNBTprntCont;

typedef enum enumCztTimeToWait
{
 CztTimeToWaitv1sEnum,
 CztTimeToWaitv2sEnum,
 CztTimeToWaitv5sEnum,
 CztTimeToWaitv10sEnum,
 CztTimeToWaitv20sEnum,
 CztTimeToWaitv60sEnum
} EnumCztTimeToWait;
typedef TknU32 CztTimeToWait;


typedef enum enumCztTraceDepth
{
 CztTraceDepthminimumEnum,
 CztTraceDepthmediumEnum,
 CztTraceDepthmaximumEnum,
 CztTraceDepthminimumWithoutVendorSpecificExtnEnum,
 CztTraceDepthmediumWithoutVendorSpecificExtnEnum,
 CztTraceDepthmaximumWithoutVendorSpecificExtnEnum
} EnumCztTraceDepth;
typedef TknU32 CztTraceDepth;


typedef TknStrBSXL CztTraceCollectionEntityIPAddr;
typedef struct x2ap_ExtnTraceActvn_ExtIEsCls{
 union {
  CztMDT_Config cztMDT_Config;
 } u;
} Czt_ExtnTraceActvn_ExtIEsCls;
typedef struct x2apProtExtnField_TraceActvn_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnTraceActvn_ExtIEsCls extensionValue;
} CztProtExtnField_TraceActvn_ExtIEs;

typedef struct x2apProtExtnCont_TraceActvn_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_TraceActvn_ExtIEs *member;
}CztProtExtnCont_TraceActvn_ExtIEs;

typedef struct x2apTraceActvn
{
 TknPres pres;
 CztEUTRANTraceID eUTRANTraceID;
 CztIntfsToTrace interfacesToTrace;
 CztTraceDepth traceDepth;
 CztTraceCollectionEntityIPAddr traceCollectionEntityIPAddr;
 CztProtExtnCont_TraceActvn_ExtIEs iE_Extns;
} CztTraceActvn;

typedef struct x2apUE_HistoryInform
{
 TknU16 noComp;
 CztLastVisitedCell_Item *member;
}CztUE_HistoryInform;


typedef TknU32 CztUE_S1AP_ID;


typedef TknU32 CztUE_X2AP_ID;

typedef struct x2ap_ExtnUEAgg_MaxBitrate_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls;
typedef struct x2apProtExtnField_UEAgg_MaxBitrate_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls extensionValue;
} CztProtExtnField_UEAgg_MaxBitrate_ExtIEs;

typedef struct x2apProtExtnCont_UEAgg_MaxBitrate_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_UEAgg_MaxBitrate_ExtIEs *member;
}CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs;

typedef struct x2apUEAggMaxBitRate
{
 TknPres pres;
 CztBitRate uEaggregateMaxBitRateDlnk;
 CztBitRate uEaggregateMaxBitRateUlnk;
 CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs iE_Extns;
} CztUEAggMaxBitRate;

typedef struct x2ap_ExtnUESecurCapabilities_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnUESecurCapabilities_ExtIEsCls;
typedef struct x2apProtExtnField_UESecurCapabilities_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnUESecurCapabilities_ExtIEsCls extensionValue;
} CztProtExtnField_UESecurCapabilities_ExtIEs;

typedef struct x2apProtExtnCont_UESecurCapabilities_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_UESecurCapabilities_ExtIEs *member;
}CztProtExtnCont_UESecurCapabilities_ExtIEs;

typedef struct x2apUESecurCapabilities
{
 TknPres pres;
 CztEncryptionAlgorithms encryptionAlgorithms;
 CztIntegrityProtectionAlgorithms integrityProtectionAlgorithms;
 CztProtExtnCont_UESecurCapabilities_ExtIEs iE_Extns;
} CztUESecurCapabilities;


typedef enum enumCztUL_InterferenceOverloadInd_Item
{
 CztUL_InterferenceOverloadInd_Itemhigh_interferenceEnum,
 CztUL_InterferenceOverloadInd_Itemmedium_interferenceEnum,
 CztUL_InterferenceOverloadInd_Itemlow_interferenceEnum
} EnumCztUL_InterferenceOverloadInd_Item;
typedef TknU32 CztUL_InterferenceOverloadInd_Item;

typedef struct x2apUL_InterferenceOverloadInd
{
 TknU16 noComp;
 CztUL_InterferenceOverloadInd_Item *member;
}CztUL_InterferenceOverloadInd;


typedef TknStrBSXL CztUL_HighInterferenceInd;
typedef struct x2ap_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls;
typedef struct x2apProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls extensionValue;
} CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs;

typedef struct x2apProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs *member;
}CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs;

typedef struct x2apUL_HighInterferenceIndInfo_Item
{
 TknPres pres;
 CztECGI target_Cell_ID;
 CztUL_HighInterferenceInd ul_interferenceindication;
 CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs iE_Extns;
} CztUL_HighInterferenceIndInfo_Item;

typedef struct x2apUL_HighInterferenceIndInfo
{
 TknU16 noComp;
 CztUL_HighInterferenceIndInfo_Item *member;
}CztUL_HighInterferenceIndInfo;


typedef TknStrOSXL CztUE_RLF_Report_Cont;
typedef struct x2ap_ExtnE_RABs_ToBeSetup_ItemExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls;
typedef struct x2apProtExtnField_E_RABs_ToBeSetup_ItemExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls extensionValue;
} CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs;

typedef struct x2apProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs
{
 TknU16 noComp;
 CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs *member;
}CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs;

typedef struct x2apE_RABs_ToBeSetup_Item
{
 TknPres pres;
 CztE_RAB_ID e_RAB_ID;
 CztE_RAB_Lvl_QoS_Params e_RAB_Lvl_QoS_Params;
 CztDL_Fwding dL_Fwding;
 CztGTPtunnelEndpoint uL_GTPtunnelEndpoint;
 CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs iE_Extns;
} CztE_RABs_ToBeSetup_Item;

typedef struct x2ap_ValueE_RABs_ToBeSetup_ItemIEsCls{
 union {
  CztE_RABs_ToBeSetup_Item cztE_RABs_ToBeSetup_Item;
 } u;
} Czt_ValueE_RABs_ToBeSetup_ItemIEsCls;
typedef struct x2apProtIE_Field_E_RABs_ToBeSetup_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueE_RABs_ToBeSetup_ItemIEsCls value;
} CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs;


typedef CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs CztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs;
typedef struct x2apE_RABs_ToBeSetup_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs *member;
}CztE_RABs_ToBeSetup_Lst;

typedef struct x2ap_ExtnUE_CntxtInform_ExtIEsCls{
 union {
  CztManagementBasedMDTallowed cztManagementBasedMDTallowed;
  CztMDTPLMNLst cztMDTPLMNLst;
 } u;
} Czt_ExtnUE_CntxtInform_ExtIEsCls;
typedef struct x2apProtExtnField_UE_CntxtInform_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnUE_CntxtInform_ExtIEsCls extensionValue;
} CztProtExtnField_UE_CntxtInform_ExtIEs;

typedef struct x2apProtExtnCont_UE_CntxtInform_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_UE_CntxtInform_ExtIEs *member;
}CztProtExtnCont_UE_CntxtInform_ExtIEs;

typedef struct x2apUE_CntxtInform
{
 TknPres pres;
 CztUE_S1AP_ID mME_UE_S1AP_ID;
 CztUESecurCapabilities uESecurCapabilities;
 CztAS_SecurInform aS_SecurInform;
 CztUEAggMaxBitRate uEaggregateMaxBitRate;
 CztSubscriberProfileIDforRFP subscriberProfileIDforRFP;
 CztE_RABs_ToBeSetup_Lst e_RABs_ToBeSetup_Lst;
 CztRRC_Cntxt rRC_Cntxt;
 CztHovrRestrnLst handoverRestrnLst;
 CztLocRprtngInform locationRprtngInform;
 CztProtExtnCont_UE_CntxtInform_ExtIEs iE_Extns;
} CztUE_CntxtInform;


typedef TknBStr32 CztMobilityInform;
typedef struct x2ap_ValueHovrRqst_IEsCls{
 union {
  CztUE_X2AP_ID cztUE_X2AP_ID;
  CztCause cztCause;
  CztECGI cztECGI;
  CztGUMMEI cztGUMMEI;
  CztUE_CntxtInform cztUE_CntxtInform;
  CztUE_HistoryInform cztUE_HistoryInform;
  CztTraceActvn cztTraceActvn;
  CztSRVCCOperationPossible cztSRVCCOperationPossible;
  CztCSGMembershipStatus cztCSGMembershipStatus;
  CztMobilityInform cztMobilityInform;
 } u;
} Czt_ValueHovrRqst_IEsCls;
typedef struct x2apProtIE_Field_HovrRqst_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueHovrRqst_IEsCls value;
} CztProtIE_Field_HovrRqst_IEs;

typedef struct x2apProtIE_Cont_HovrRqst_IEs
{
 TknU16 noComp;
 CztProtIE_Field_HovrRqst_IEs *member;
}CztProtIE_Cont_HovrRqst_IEs;

typedef struct x2apHovrRqst
{
 TknPres pres;
 CztProtIE_Cont_HovrRqst_IEs protocolIEs;
} CztHovrRqst;

typedef struct x2ap_ExtnE_RABs_Admtd_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls;
typedef struct x2apProtExtnField_E_RABs_Admtd_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls extensionValue;
} CztProtExtnField_E_RABs_Admtd_Item_ExtIEs;

typedef struct x2apProtExtnCont_E_RABs_Admtd_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_E_RABs_Admtd_Item_ExtIEs *member;
}CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs;

typedef struct x2apE_RABs_Admtd_Item
{
 TknPres pres;
 CztE_RAB_ID e_RAB_ID;
 CztGTPtunnelEndpoint uL_GTP_TunnelEndpoint;
 CztGTPtunnelEndpoint dL_GTP_TunnelEndpoint;
 CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs iE_Extns;
} CztE_RABs_Admtd_Item;

typedef struct x2ap_ValueE_RABs_Admtd_ItemIEsCls{
 union {
  CztE_RABs_Admtd_Item cztE_RABs_Admtd_Item;
 } u;
} Czt_ValueE_RABs_Admtd_ItemIEsCls;
typedef struct x2apProtIE_Field_E_RABs_Admtd_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueE_RABs_Admtd_ItemIEsCls value;
} CztProtIE_Field_E_RABs_Admtd_ItemIEs;


typedef CztProtIE_Field_E_RABs_Admtd_ItemIEs CztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs;
typedef struct x2apE_RABs_Admtd_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs *member;
}CztE_RABs_Admtd_Lst;

typedef struct x2ap_ValueHovrRqstAckg_IEsCls{
 union {
  CztUE_X2AP_ID cztid_Old_eNB_UE_X2AP_ID;
  CztUE_X2AP_ID cztid_New_eNB_UE_X2AP_ID;
  CztE_RABs_Admtd_Lst cztE_RABs_Admtd_Lst;
  CztE_RAB_Lst cztE_RAB_Lst;
  CztTgeteNBtoSrc_eNBTprntCont cztTgeteNBtoSrc_eNBTprntCont;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueHovrRqstAckg_IEsCls;
typedef struct x2apProtIE_Field_HovrRqstAckg_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueHovrRqstAckg_IEsCls value;
} CztProtIE_Field_HovrRqstAckg_IEs;

typedef struct x2apProtIE_Cont_HovrRqstAckg_IEs
{
 TknU16 noComp;
 CztProtIE_Field_HovrRqstAckg_IEs *member;
}CztProtIE_Cont_HovrRqstAckg_IEs;

typedef struct x2apHovrRqstAckg
{
 TknPres pres;
 CztProtIE_Cont_HovrRqstAckg_IEs protocolIEs;
} CztHovrRqstAckg;

typedef struct x2ap_ValueHovrPrepFail_IEsCls{
 union {
  CztUE_X2AP_ID cztUE_X2AP_ID;
  CztCause cztCause;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueHovrPrepFail_IEsCls;
typedef struct x2apProtIE_Field_HovrPrepFail_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueHovrPrepFail_IEsCls value;
} CztProtIE_Field_HovrPrepFail_IEs;

typedef struct x2apProtIE_Cont_HovrPrepFail_IEs
{
 TknU16 noComp;
 CztProtIE_Field_HovrPrepFail_IEs *member;
}CztProtIE_Cont_HovrPrepFail_IEs;

typedef struct x2apHovrPrepFail
{
 TknPres pres;
 CztProtIE_Cont_HovrPrepFail_IEs protocolIEs;
} CztHovrPrepFail;

typedef struct x2ap_ValueHovrReport_IEsCls{
 union {
  CztHovrReportTyp cztHovrReportTyp;
  CztCause cztCause;
  CztECGI cztid_SrcCellECGI;
  CztECGI cztid_FailCellECGI;
  CztECGI cztid_Re_establishmentCellECGI;
  CztTgetCellInUTRAN cztTgetCellInUTRAN;
  CztCRNTI cztCRNTI;
  CztMobilityInform cztMobilityInform;
  CztUE_RLF_Report_Cont cztUE_RLF_Report_Cont;
 } u;
} Czt_ValueHovrReport_IEsCls;
typedef struct x2apProtIE_Field_HovrReport_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueHovrReport_IEsCls value;
} CztProtIE_Field_HovrReport_IEs;

typedef struct x2apProtIE_Cont_HovrReport_IEs
{
 TknU16 noComp;
 CztProtIE_Field_HovrReport_IEs *member;
}CztProtIE_Cont_HovrReport_IEs;

typedef struct x2apHovrReport
{
 TknPres pres;
 CztProtIE_Cont_HovrReport_IEs protocolIEs;
} CztHovrReport;

typedef struct x2ap_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls{
 union {
  CztReceiveStatusOfULPDCPSDUsExtended cztReceiveStatusOfULPDCPSDUsExtended;
  CztCOUNTValueExtended cztid_ULCOUNTValueExtended;
  CztCOUNTValueExtended cztid_DLCOUNTValueExtended;
 } u;
} Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls;
typedef struct x2apProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls extensionValue;
} CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs;

typedef struct x2apProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs
{
 TknU16 noComp;
 CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs *member;
}CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs;

typedef struct x2apE_RABs_SubjToStatusTfr_Item
{
 TknPres pres;
 CztE_RAB_ID e_RAB_ID;
 CztReceiveStatusofULPDCPSDUs receiveStatusofULPDCPSDUs;
 CztCOUNTvalue uL_COUNTvalue;
 CztCOUNTvalue dL_COUNTvalue;
 CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs iE_Extns;
} CztE_RABs_SubjToStatusTfr_Item;

typedef struct x2ap_ValueE_RABs_SubjToStatusTfr_ItemIEsCls{
 union {
  CztE_RABs_SubjToStatusTfr_Item cztE_RABs_SubjToStatusTfr_Item;
 } u;
} Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls;
typedef struct x2apProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls value;
} CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs;


typedef CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs CztProtIE_Single_Cont_E_RABs_SubjToStatusTfr_ItemIEs;
typedef struct x2apE_RABs_SubjToStatusTfr_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_E_RABs_SubjToStatusTfr_ItemIEs *member;
}CztE_RABs_SubjToStatusTfr_Lst;

typedef struct x2ap_ValueSNStatusTfr_IEsCls{
 union {
  CztUE_X2AP_ID cztid_Old_eNB_UE_X2AP_ID;
  CztUE_X2AP_ID cztid_New_eNB_UE_X2AP_ID;
  CztE_RABs_SubjToStatusTfr_Lst cztE_RABs_SubjToStatusTfr_Lst;
 } u;
} Czt_ValueSNStatusTfr_IEsCls;
typedef struct x2apProtIE_Field_SNStatusTfr_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueSNStatusTfr_IEsCls value;
} CztProtIE_Field_SNStatusTfr_IEs;

typedef struct x2apProtIE_Cont_SNStatusTfr_IEs
{
 TknU16 noComp;
 CztProtIE_Field_SNStatusTfr_IEs *member;
}CztProtIE_Cont_SNStatusTfr_IEs;

typedef struct x2apSNStatusTfr
{
 TknPres pres;
 CztProtIE_Cont_SNStatusTfr_IEs protocolIEs;
} CztSNStatusTfr;

typedef struct x2ap_ValueUECntxtRls_IEsCls{
 union {
  CztUE_X2AP_ID cztid_Old_eNB_UE_X2AP_ID;
  CztUE_X2AP_ID cztid_New_eNB_UE_X2AP_ID;
 } u;
} Czt_ValueUECntxtRls_IEsCls;
typedef struct x2apProtIE_Field_UECntxtRls_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueUECntxtRls_IEsCls value;
} CztProtIE_Field_UECntxtRls_IEs;

typedef struct x2apProtIE_Cont_UECntxtRls_IEs
{
 TknU16 noComp;
 CztProtIE_Field_UECntxtRls_IEs *member;
}CztProtIE_Cont_UECntxtRls_IEs;

typedef struct x2apUECntxtRls
{
 TknPres pres;
 CztProtIE_Cont_UECntxtRls_IEs protocolIEs;
} CztUECntxtRls;

typedef struct x2ap_ValueHovrCancel_IEsCls{
 union {
  CztUE_X2AP_ID cztid_Old_eNB_UE_X2AP_ID;
  CztUE_X2AP_ID cztid_New_eNB_UE_X2AP_ID;
  CztCause cztCause;
 } u;
} Czt_ValueHovrCancel_IEsCls;
typedef struct x2apProtIE_Field_HovrCancel_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueHovrCancel_IEsCls value;
} CztProtIE_Field_HovrCancel_IEs;

typedef struct x2apProtIE_Cont_HovrCancel_IEs
{
 TknU16 noComp;
 CztProtIE_Field_HovrCancel_IEs *member;
}CztProtIE_Cont_HovrCancel_IEs;

typedef struct x2apHovrCancel
{
 TknPres pres;
 CztProtIE_Cont_HovrCancel_IEs protocolIEs;
} CztHovrCancel;

typedef struct x2ap_ValueErrInd_IEsCls{
 union {
  CztUE_X2AP_ID cztid_Old_eNB_UE_X2AP_ID;
  CztUE_X2AP_ID cztid_New_eNB_UE_X2AP_ID;
  CztCause cztCause;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueErrInd_IEsCls;
typedef struct x2apProtIE_Field_ErrInd_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueErrInd_IEsCls value;
} CztProtIE_Field_ErrInd_IEs;

typedef struct x2apProtIE_Cont_ErrInd_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ErrInd_IEs *member;
}CztProtIE_Cont_ErrInd_IEs;

typedef struct x2apErrInd
{
 TknPres pres;
 CztProtIE_Cont_ErrInd_IEs protocolIEs;
} CztErrInd;

typedef struct x2ap_ValueResetRqst_IEsCls{
 union {
  CztCause cztCause;
 } u;
} Czt_ValueResetRqst_IEsCls;
typedef struct x2apProtIE_Field_ResetRqst_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueResetRqst_IEsCls value;
} CztProtIE_Field_ResetRqst_IEs;

typedef struct x2apProtIE_Cont_ResetRqst_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ResetRqst_IEs *member;
}CztProtIE_Cont_ResetRqst_IEs;

typedef struct x2apResetRqst
{
 TknPres pres;
 CztProtIE_Cont_ResetRqst_IEs protocolIEs;
} CztResetRqst;

typedef struct x2ap_ValueResetResp_IEsCls{
 union {
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueResetResp_IEsCls;
typedef struct x2apProtIE_Field_ResetResp_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueResetResp_IEsCls value;
} CztProtIE_Field_ResetResp_IEs;

typedef struct x2apProtIE_Cont_ResetResp_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ResetResp_IEs *member;
}CztProtIE_Cont_ResetResp_IEs;

typedef struct x2apResetResp
{
 TknPres pres;
 CztProtIE_Cont_ResetResp_IEs protocolIEs;
} CztResetResp;

typedef struct x2ap_ValueX2SetupRqst_IEsCls{
 union {
  CztGlobalENB_ID cztGlobalENB_ID;
  CztSrvdCells cztSrvdCells;
  CztGUGroupIDLst cztGUGroupIDLst;
 } u;
} Czt_ValueX2SetupRqst_IEsCls;
typedef struct x2apProtIE_Field_X2SetupRqst_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueX2SetupRqst_IEsCls value;
} CztProtIE_Field_X2SetupRqst_IEs;

typedef struct x2apProtIE_Cont_X2SetupRqst_IEs
{
 TknU16 noComp;
 CztProtIE_Field_X2SetupRqst_IEs *member;
}CztProtIE_Cont_X2SetupRqst_IEs;

typedef struct x2apX2SetupRqst
{
 TknPres pres;
 CztProtIE_Cont_X2SetupRqst_IEs protocolIEs;
} CztX2SetupRqst;

typedef struct x2ap_ValueX2SetupResp_IEsCls{
 union {
  CztGlobalENB_ID cztGlobalENB_ID;
  CztSrvdCells cztSrvdCells;
  CztGUGroupIDLst cztGUGroupIDLst;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueX2SetupResp_IEsCls;
typedef struct x2apProtIE_Field_X2SetupResp_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueX2SetupResp_IEsCls value;
} CztProtIE_Field_X2SetupResp_IEs;

typedef struct x2apProtIE_Cont_X2SetupResp_IEs
{
 TknU16 noComp;
 CztProtIE_Field_X2SetupResp_IEs *member;
}CztProtIE_Cont_X2SetupResp_IEs;

typedef struct x2apX2SetupResp
{
 TknPres pres;
 CztProtIE_Cont_X2SetupResp_IEs protocolIEs;
} CztX2SetupResp;

typedef struct x2ap_ValueX2SetupFail_IEsCls{
 union {
  CztCause cztCause;
  CztTimeToWait cztTimeToWait;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueX2SetupFail_IEsCls;
typedef struct x2apProtIE_Field_X2SetupFail_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueX2SetupFail_IEsCls value;
} CztProtIE_Field_X2SetupFail_IEs;

typedef struct x2apProtIE_Cont_X2SetupFail_IEs
{
 TknU16 noComp;
 CztProtIE_Field_X2SetupFail_IEs *member;
}CztProtIE_Cont_X2SetupFail_IEs;

typedef struct x2apX2SetupFail
{
 TknPres pres;
 CztProtIE_Cont_X2SetupFail_IEs protocolIEs;
} CztX2SetupFail;

typedef struct x2ap_ExtnCellInform_Item_ExtIEsCls{
 union {
  CztABSInform cztABSInform;
  CztInvokeInd cztInvokeInd;
 } u;
} Czt_ExtnCellInform_Item_ExtIEsCls;
typedef struct x2apProtExtnField_CellInform_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCellInform_Item_ExtIEsCls extensionValue;
} CztProtExtnField_CellInform_Item_ExtIEs;

typedef struct x2apProtExtnCont_CellInform_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CellInform_Item_ExtIEs *member;
}CztProtExtnCont_CellInform_Item_ExtIEs;

typedef struct x2apCellInform_Item
{
 TknPres pres;
 CztECGI cell_ID;
 CztUL_InterferenceOverloadInd ul_InterferenceOverloadInd;
 CztUL_HighInterferenceIndInfo ul_HighInterferenceIndInfo;
 CztRelativeNarrowbandTxPower relativeNarrowbandTxPower;
 CztProtExtnCont_CellInform_Item_ExtIEs iE_Extns;
} CztCellInform_Item;

typedef struct x2ap_ValueCellInform_ItemIEsCls{
 union {
  CztCellInform_Item cztCellInform_Item;
 } u;
} Czt_ValueCellInform_ItemIEsCls;
typedef struct x2apProtIE_Field_CellInform_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueCellInform_ItemIEsCls value;
} CztProtIE_Field_CellInform_ItemIEs;


typedef CztProtIE_Field_CellInform_ItemIEs CztProtIE_Single_Cont_CellInform_ItemIEs;
typedef struct x2apCellInform_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_CellInform_ItemIEs *member;
}CztCellInform_Lst;

typedef struct x2ap_ValueLoadInform_IEsCls{
 union {
  CztCellInform_Lst cztCellInform_Lst;
 } u;
} Czt_ValueLoadInform_IEsCls;
typedef struct x2apProtIE_Field_LoadInform_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueLoadInform_IEsCls value;
} CztProtIE_Field_LoadInform_IEs;

typedef struct x2apProtIE_Cont_LoadInform_IEs
{
 TknU16 noComp;
 CztProtIE_Field_LoadInform_IEs *member;
}CztProtIE_Cont_LoadInform_IEs;

typedef struct x2apLoadInform
{
 TknPres pres;
 CztProtIE_Cont_LoadInform_IEs protocolIEs;
} CztLoadInform;

typedef struct x2ap_ExtnSrvdCellsToMdfy_Item_ExtIEsCls{
 union {
  CztDeactivationInd cztDeactivationInd;
 } u;
} Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls;
typedef struct x2apProtExtnField_SrvdCellsToMdfy_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls extensionValue;
} CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs;

typedef struct x2apProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs *member;
}CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs;

typedef struct x2apSrvdCellsToMdfy_Item
{
 TknPres pres;
 CztECGI old_ecgi;
 CztSrvdCell_Inform servedCellInfo;
 CztNeighbour_Inform neighbour_Info;
 CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs iE_Extns;
} CztSrvdCellsToMdfy_Item;

typedef struct x2apSrvdCellsToMdfy
{
 TknU16 noComp;
 CztSrvdCellsToMdfy_Item *member;
}CztSrvdCellsToMdfy;

typedef struct x2apOld_ECGIs
{
 TknU16 noComp;
 CztECGI *member;
}CztOld_ECGIs;

typedef struct x2ap_ValueENBConfigUpd_IEsCls{
 union {
  CztSrvdCells cztSrvdCells;
  CztSrvdCellsToMdfy cztSrvdCellsToMdfy;
  CztOld_ECGIs cztOld_ECGIs;
  CztGUGroupIDLst cztid_GUGroupIDToAddLst;
  CztGUGroupIDLst cztid_GUGroupIDToDeleteLst;
 } u;
} Czt_ValueENBConfigUpd_IEsCls;
typedef struct x2apProtIE_Field_ENBConfigUpd_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueENBConfigUpd_IEsCls value;
} CztProtIE_Field_ENBConfigUpd_IEs;

typedef struct x2apProtIE_Cont_ENBConfigUpd_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ENBConfigUpd_IEs *member;
}CztProtIE_Cont_ENBConfigUpd_IEs;

typedef struct x2apENBConfigUpd
{
 TknPres pres;
 CztProtIE_Cont_ENBConfigUpd_IEs protocolIEs;
} CztENBConfigUpd;

typedef struct x2ap_ValueENBConfigUpdAckg_IEsCls{
 union {
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueENBConfigUpdAckg_IEsCls;
typedef struct x2apProtIE_Field_ENBConfigUpdAckg_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueENBConfigUpdAckg_IEsCls value;
} CztProtIE_Field_ENBConfigUpdAckg_IEs;

typedef struct x2apProtIE_Cont_ENBConfigUpdAckg_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ENBConfigUpdAckg_IEs *member;
}CztProtIE_Cont_ENBConfigUpdAckg_IEs;

typedef struct x2apENBConfigUpdAckg
{
 TknPres pres;
 CztProtIE_Cont_ENBConfigUpdAckg_IEs protocolIEs;
} CztENBConfigUpdAckg;

typedef struct x2ap_ValueENBConfigUpdFail_IEsCls{
 union {
  CztCause cztCause;
  CztTimeToWait cztTimeToWait;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueENBConfigUpdFail_IEsCls;
typedef struct x2apProtIE_Field_ENBConfigUpdFail_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueENBConfigUpdFail_IEsCls value;
} CztProtIE_Field_ENBConfigUpdFail_IEs;

typedef struct x2apProtIE_Cont_ENBConfigUpdFail_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ENBConfigUpdFail_IEs *member;
}CztProtIE_Cont_ENBConfigUpdFail_IEs;

typedef struct x2apENBConfigUpdFail
{
 TknPres pres;
 CztProtIE_Cont_ENBConfigUpdFail_IEs protocolIEs;
} CztENBConfigUpdFail;

typedef struct x2ap_ExtnCellToReport_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCellToReport_Item_ExtIEsCls;
typedef struct x2apProtExtnField_CellToReport_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCellToReport_Item_ExtIEsCls extensionValue;
} CztProtExtnField_CellToReport_Item_ExtIEs;

typedef struct x2apProtExtnCont_CellToReport_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CellToReport_Item_ExtIEs *member;
}CztProtExtnCont_CellToReport_Item_ExtIEs;

typedef struct x2apCellToReport_Item
{
 TknPres pres;
 CztECGI cell_ID;
 CztProtExtnCont_CellToReport_Item_ExtIEs iE_Extns;
} CztCellToReport_Item;

typedef struct x2ap_ValueCellToReport_ItemIEsCls{
 union {
  CztCellToReport_Item cztCellToReport_Item;
 } u;
} Czt_ValueCellToReport_ItemIEsCls;
typedef struct x2apProtIE_Field_CellToReport_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueCellToReport_ItemIEsCls value;
} CztProtIE_Field_CellToReport_ItemIEs;


typedef CztProtIE_Field_CellToReport_ItemIEs CztProtIE_Single_Cont_CellToReport_ItemIEs;
typedef struct x2apCellToReport_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_CellToReport_ItemIEs *member;
}CztCellToReport_Lst;


typedef enum enumCztRprtngPeriodicity
{
 CztRprtngPeriodicityone_thousand_msEnum,
 CztRprtngPeriodicitytwo_thousand_msEnum,
 CztRprtngPeriodicityfive_thousand_msEnum,
 CztRprtngPeriodicityten_thousand_msEnum
} EnumCztRprtngPeriodicity;
typedef TknU32 CztRprtngPeriodicity;


typedef enum enumCztPartialSuccessIndicator
{
 CztPartialSuccessIndicatorpartial_success_allowedEnum
} EnumCztPartialSuccessIndicator;
typedef TknU32 CztPartialSuccessIndicator;

typedef struct x2ap_ValueResStatusRqst_IEsCls{
 union {
  CztMeasurement_ID cztid_ENB1_Measurement_ID;
  CztMeasurement_ID cztid_ENB2_Measurement_ID;
  CztRegistration_Rqst cztRegistration_Rqst;
  CztReportCharacteristics cztReportCharacteristics;
  CztCellToReport_Lst cztCellToReport_Lst;
  CztRprtngPeriodicity cztRprtngPeriodicity;
  CztPartialSuccessIndicator cztPartialSuccessIndicator;
 } u;
} Czt_ValueResStatusRqst_IEsCls;
typedef struct x2apProtIE_Field_ResStatusRqst_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueResStatusRqst_IEsCls value;
} CztProtIE_Field_ResStatusRqst_IEs;

typedef struct x2apProtIE_Cont_ResStatusRqst_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ResStatusRqst_IEs *member;
}CztProtIE_Cont_ResStatusRqst_IEs;

typedef struct x2apResStatusRqst
{
 TknPres pres;
 CztProtIE_Cont_ResStatusRqst_IEs protocolIEs;
} CztResStatusRqst;

typedef struct x2ap_ExtnMeasurementFailCause_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnMeasurementFailCause_Item_ExtIEsCls;
typedef struct x2apProtExtnField_MeasurementFailCause_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnMeasurementFailCause_Item_ExtIEsCls extensionValue;
} CztProtExtnField_MeasurementFailCause_Item_ExtIEs;

typedef struct x2apProtExtnCont_MeasurementFailCause_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_MeasurementFailCause_Item_ExtIEs *member;
}CztProtExtnCont_MeasurementFailCause_Item_ExtIEs;

typedef struct x2apMeasurementFailCause_Item
{
 TknPres pres;
 CztReportCharacteristics measurementFailedReportCharacteristics;
 CztCause cause;
 CztProtExtnCont_MeasurementFailCause_Item_ExtIEs iE_Extns;
} CztMeasurementFailCause_Item;

typedef struct x2ap_ValueMeasurementFailCause_ItemIEsCls{
 union {
  CztMeasurementFailCause_Item cztMeasurementFailCause_Item;
 } u;
} Czt_ValueMeasurementFailCause_ItemIEsCls;
typedef struct x2apProtIE_Field_MeasurementFailCause_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueMeasurementFailCause_ItemIEsCls value;
} CztProtIE_Field_MeasurementFailCause_ItemIEs;


typedef CztProtIE_Field_MeasurementFailCause_ItemIEs CztProtIE_Single_Cont_MeasurementFailCause_ItemIEs;
typedef struct x2apMeasurementFailCause_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_MeasurementFailCause_ItemIEs *member;
}CztMeasurementFailCause_Lst;

typedef struct x2ap_ExtnMeasurementInitiationResult_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls;
typedef struct x2apProtExtnField_MeasurementInitiationResult_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls extensionValue;
} CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs;

typedef struct x2apProtExtnCont_MeasurementInitiationResult_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs *member;
}CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs;

typedef struct x2apMeasurementInitiationResult_Item
{
 TknPres pres;
 CztECGI cell_ID;
 CztMeasurementFailCause_Lst measurementFailCause_Lst;
 CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs iE_Extns;
} CztMeasurementInitiationResult_Item;

typedef struct x2ap_ValueMeasurementInitiationResult_ItemIEsCls{
 union {
  CztMeasurementInitiationResult_Item cztMeasurementInitiationResult_Item;
 } u;
} Czt_ValueMeasurementInitiationResult_ItemIEsCls;
typedef struct x2apProtIE_Field_MeasurementInitiationResult_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueMeasurementInitiationResult_ItemIEsCls value;
} CztProtIE_Field_MeasurementInitiationResult_ItemIEs;


typedef CztProtIE_Field_MeasurementInitiationResult_ItemIEs CztProtIE_Single_Cont_MeasurementInitiationResult_ItemIEs;
typedef struct x2apMeasurementInitiationResult_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_MeasurementInitiationResult_ItemIEs *member;
}CztMeasurementInitiationResult_Lst;

typedef struct x2ap_ValueResStatusResp_IEsCls{
 union {
  CztMeasurement_ID cztid_ENB1_Measurement_ID;
  CztMeasurement_ID cztid_ENB2_Measurement_ID;
  CztCriticalityDiag cztCriticalityDiag;
  CztMeasurementInitiationResult_Lst cztMeasurementInitiationResult_Lst;
 } u;
} Czt_ValueResStatusResp_IEsCls;
typedef struct x2apProtIE_Field_ResStatusResp_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueResStatusResp_IEsCls value;
} CztProtIE_Field_ResStatusResp_IEs;

typedef struct x2apProtIE_Cont_ResStatusResp_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ResStatusResp_IEs *member;
}CztProtIE_Cont_ResStatusResp_IEs;

typedef struct x2apResStatusResp
{
 TknPres pres;
 CztProtIE_Cont_ResStatusResp_IEs protocolIEs;
} CztResStatusResp;

typedef struct x2ap_ExtnCompleteFailCauseInform_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls;
typedef struct x2apProtExtnField_CompleteFailCauseInform_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls extensionValue;
} CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs;

typedef struct x2apProtExtnCont_CompleteFailCauseInform_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs *member;
}CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs;

typedef struct x2apCompleteFailCauseInform_Item
{
 TknPres pres;
 CztECGI cell_ID;
 CztMeasurementFailCause_Lst measurementFailCause_Lst;
 CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs iE_Extns;
} CztCompleteFailCauseInform_Item;

typedef struct x2ap_ValueCompleteFailCauseInform_ItemIEsCls{
 union {
  CztCompleteFailCauseInform_Item cztCompleteFailCauseInform_Item;
 } u;
} Czt_ValueCompleteFailCauseInform_ItemIEsCls;
typedef struct x2apProtIE_Field_CompleteFailCauseInform_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueCompleteFailCauseInform_ItemIEsCls value;
} CztProtIE_Field_CompleteFailCauseInform_ItemIEs;


typedef CztProtIE_Field_CompleteFailCauseInform_ItemIEs CztProtIE_Single_Cont_CompleteFailCauseInform_ItemIEs;
typedef struct x2apCompleteFailCauseInform_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_CompleteFailCauseInform_ItemIEs *member;
}CztCompleteFailCauseInform_Lst;

typedef struct x2ap_ValueResStatusFail_IEsCls{
 union {
  CztMeasurement_ID cztid_ENB1_Measurement_ID;
  CztMeasurement_ID cztid_ENB2_Measurement_ID;
  CztCause cztCause;
  CztCriticalityDiag cztCriticalityDiag;
  CztCompleteFailCauseInform_Lst cztCompleteFailCauseInform_Lst;
 } u;
} Czt_ValueResStatusFail_IEsCls;
typedef struct x2apProtIE_Field_ResStatusFail_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueResStatusFail_IEsCls value;
} CztProtIE_Field_ResStatusFail_IEs;

typedef struct x2apProtIE_Cont_ResStatusFail_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ResStatusFail_IEs *member;
}CztProtIE_Cont_ResStatusFail_IEs;

typedef struct x2apResStatusFail
{
 TknPres pres;
 CztProtIE_Cont_ResStatusFail_IEs protocolIEs;
} CztResStatusFail;

typedef struct x2ap_ExtnCellMeasurementResult_Item_ExtIEsCls{
 union {
  CztCompositeAvailableCapacityGroup cztCompositeAvailableCapacityGroup;
  CztABS_Status cztABS_Status;
 } u;
} Czt_ExtnCellMeasurementResult_Item_ExtIEsCls;
typedef struct x2apProtExtnField_CellMeasurementResult_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnCellMeasurementResult_Item_ExtIEsCls extensionValue;
} CztProtExtnField_CellMeasurementResult_Item_ExtIEs;

typedef struct x2apProtExtnCont_CellMeasurementResult_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_CellMeasurementResult_Item_ExtIEs *member;
}CztProtExtnCont_CellMeasurementResult_Item_ExtIEs;

typedef struct x2apCellMeasurementResult_Item
{
 TknPres pres;
 CztECGI cell_ID;
 CztHWLoadIndicator hWLoadIndicator;
 CztS1TNLLoadIndicator s1TNLLoadIndicator;
 CztRadioResStatus radioResStatus;
 CztProtExtnCont_CellMeasurementResult_Item_ExtIEs iE_Extns;
} CztCellMeasurementResult_Item;

typedef struct x2ap_ValueCellMeasurementResult_ItemIEsCls{
 union {
  CztCellMeasurementResult_Item cztCellMeasurementResult_Item;
 } u;
} Czt_ValueCellMeasurementResult_ItemIEsCls;
typedef struct x2apProtIE_Field_CellMeasurementResult_ItemIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueCellMeasurementResult_ItemIEsCls value;
} CztProtIE_Field_CellMeasurementResult_ItemIEs;


typedef CztProtIE_Field_CellMeasurementResult_ItemIEs CztProtIE_Single_Cont_CellMeasurementResult_ItemIEs;
typedef struct x2apCellMeasurementResult_Lst
{
 TknU16 noComp;
 CztProtIE_Single_Cont_CellMeasurementResult_ItemIEs *member;
}CztCellMeasurementResult_Lst;

typedef struct x2ap_ValueResStatusUpd_IEsCls{
 union {
  CztMeasurement_ID cztid_ENB1_Measurement_ID;
  CztMeasurement_ID cztid_ENB2_Measurement_ID;
  CztCellMeasurementResult_Lst cztCellMeasurementResult_Lst;
 } u;
} Czt_ValueResStatusUpd_IEsCls;
typedef struct x2apProtIE_Field_ResStatusUpd_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueResStatusUpd_IEsCls value;
} CztProtIE_Field_ResStatusUpd_IEs;

typedef struct x2apProtIE_Cont_ResStatusUpd_IEs
{
 TknU16 noComp;
 CztProtIE_Field_ResStatusUpd_IEs *member;
}CztProtIE_Cont_ResStatusUpd_IEs;

typedef struct x2apResStatusUpd
{
 TknPres pres;
 CztProtIE_Cont_ResStatusUpd_IEs protocolIEs;
} CztResStatusUpd;

typedef struct x2ap_ValuePrivMsg_IEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ValuePrivMsg_IEsCls;
typedef struct x2apPrivIE_Field_PrivMsg_IEs
{
 TknPres pres;
 CztPrivIE_ID id;
 CztCriticality criticality;
 Czt_ValuePrivMsg_IEsCls value;
} CztPrivIE_Field_PrivMsg_IEs;

typedef struct x2apPrivIE_Cont_PrivMsg_IEs
{
 TknU16 noComp;
 CztPrivIE_Field_PrivMsg_IEs *member;
}CztPrivIE_Cont_PrivMsg_IEs;

typedef struct x2apPrivMsg
{
 TknPres pres;
 CztPrivIE_Cont_PrivMsg_IEs privateIEs;
} CztPrivMsg;

typedef struct x2ap_ValueMobilityChangeRqst_IEsCls{
 union {
  CztECGI cztid_ENB1_Cell_ID;
  CztECGI cztid_ENB2_Cell_ID;
  CztMobilityParamsInform cztid_ENB1_Mobility_Params;
  CztMobilityParamsInform cztid_ENB2_Proposed_Mobility_Params;
  CztCause cztCause;
 } u;
} Czt_ValueMobilityChangeRqst_IEsCls;
typedef struct x2apProtIE_Field_MobilityChangeRqst_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueMobilityChangeRqst_IEsCls value;
} CztProtIE_Field_MobilityChangeRqst_IEs;

typedef struct x2apProtIE_Cont_MobilityChangeRqst_IEs
{
 TknU16 noComp;
 CztProtIE_Field_MobilityChangeRqst_IEs *member;
}CztProtIE_Cont_MobilityChangeRqst_IEs;

typedef struct x2apMobilityChangeRqst
{
 TknPres pres;
 CztProtIE_Cont_MobilityChangeRqst_IEs protocolIEs;
} CztMobilityChangeRqst;

typedef struct x2ap_ValueMobilityChangeAckg_IEsCls{
 union {
  CztECGI cztid_ENB1_Cell_ID;
  CztECGI cztid_ENB2_Cell_ID;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueMobilityChangeAckg_IEsCls;
typedef struct x2apProtIE_Field_MobilityChangeAckg_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueMobilityChangeAckg_IEsCls value;
} CztProtIE_Field_MobilityChangeAckg_IEs;

typedef struct x2apProtIE_Cont_MobilityChangeAckg_IEs
{
 TknU16 noComp;
 CztProtIE_Field_MobilityChangeAckg_IEs *member;
}CztProtIE_Cont_MobilityChangeAckg_IEs;

typedef struct x2apMobilityChangeAckg
{
 TknPres pres;
 CztProtIE_Cont_MobilityChangeAckg_IEs protocolIEs;
} CztMobilityChangeAckg;

typedef struct x2ap_ValueMobilityChangeFail_IEsCls{
 union {
  CztECGI cztid_ENB1_Cell_ID;
  CztECGI cztid_ENB2_Cell_ID;
  CztCause cztCause;
  CztMobilityParamsModificationRange cztMobilityParamsModificationRange;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueMobilityChangeFail_IEsCls;
typedef struct x2apProtIE_Field_MobilityChangeFail_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueMobilityChangeFail_IEsCls value;
} CztProtIE_Field_MobilityChangeFail_IEs;

typedef struct x2apProtIE_Cont_MobilityChangeFail_IEs
{
 TknU16 noComp;
 CztProtIE_Field_MobilityChangeFail_IEs *member;
}CztProtIE_Cont_MobilityChangeFail_IEs;

typedef struct x2apMobilityChangeFail
{
 TknPres pres;
 CztProtIE_Cont_MobilityChangeFail_IEs protocolIEs;
} CztMobilityChangeFail;

typedef struct x2ap_ValueRLFInd_IEsCls{
 union {
  CztPCI cztPCI;
  CztECGI cztECGI;
  CztCRNTI cztCRNTI;
  CztShortMAC_I cztShortMAC_I;
  CztUE_RLF_Report_Cont cztUE_RLF_Report_Cont;
  CztRRCConnSetupIndicator cztRRCConnSetupIndicator;
  CztRRCConnReestabIndicator cztRRCConnReestabIndicator;
 } u;
} Czt_ValueRLFInd_IEsCls;
typedef struct x2apProtIE_Field_RLFInd_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueRLFInd_IEsCls value;
} CztProtIE_Field_RLFInd_IEs;

typedef struct x2apProtIE_Cont_RLFInd_IEs
{
 TknU16 noComp;
 CztProtIE_Field_RLFInd_IEs *member;
}CztProtIE_Cont_RLFInd_IEs;

typedef struct x2apRLFInd
{
 TknPres pres;
 CztProtIE_Cont_RLFInd_IEs protocolIEs;
} CztRLFInd;

typedef struct x2ap_ExtnSrvdCellsToActivate_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls;
typedef struct x2apProtExtnField_SrvdCellsToActivate_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls extensionValue;
} CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs;

typedef struct x2apProtExtnCont_SrvdCellsToActivate_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs *member;
}CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs;

typedef struct x2apSrvdCellsToActivate_Item
{
 TknPres pres;
 CztECGI ecgi;
 CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs iE_Extns;
} CztSrvdCellsToActivate_Item;

typedef struct x2apSrvdCellsToActivate
{
 TknU16 noComp;
 CztSrvdCellsToActivate_Item *member;
}CztSrvdCellsToActivate;

typedef struct x2ap_ValueCellActvnRqst_IEsCls{
 union {
  CztSrvdCellsToActivate cztSrvdCellsToActivate;
 } u;
} Czt_ValueCellActvnRqst_IEsCls;
typedef struct x2apProtIE_Field_CellActvnRqst_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueCellActvnRqst_IEsCls value;
} CztProtIE_Field_CellActvnRqst_IEs;

typedef struct x2apProtIE_Cont_CellActvnRqst_IEs
{
 TknU16 noComp;
 CztProtIE_Field_CellActvnRqst_IEs *member;
}CztProtIE_Cont_CellActvnRqst_IEs;

typedef struct x2apCellActvnRqst
{
 TknPres pres;
 CztProtIE_Cont_CellActvnRqst_IEs protocolIEs;
} CztCellActvnRqst;

typedef struct x2ap_ExtnActivatedCellLst_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Czt_ExtnActivatedCellLst_Item_ExtIEsCls;
typedef struct x2apProtExtnField_ActivatedCellLst_Item_ExtIEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ExtnActivatedCellLst_Item_ExtIEsCls extensionValue;
} CztProtExtnField_ActivatedCellLst_Item_ExtIEs;

typedef struct x2apProtExtnCont_ActivatedCellLst_Item_ExtIEs
{
 TknU16 noComp;
 CztProtExtnField_ActivatedCellLst_Item_ExtIEs *member;
}CztProtExtnCont_ActivatedCellLst_Item_ExtIEs;

typedef struct x2apActivatedCellLst_Item
{
 TknPres pres;
 CztECGI ecgi;
 CztProtExtnCont_ActivatedCellLst_Item_ExtIEs iE_Extns;
} CztActivatedCellLst_Item;

typedef struct x2apActivatedCellLst
{
 TknU16 noComp;
 CztActivatedCellLst_Item *member;
}CztActivatedCellLst;

typedef struct x2ap_ValueCellActvnResp_IEsCls{
 union {
  CztActivatedCellLst cztActivatedCellLst;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueCellActvnResp_IEsCls;
typedef struct x2apProtIE_Field_CellActvnResp_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueCellActvnResp_IEsCls value;
} CztProtIE_Field_CellActvnResp_IEs;

typedef struct x2apProtIE_Cont_CellActvnResp_IEs
{
 TknU16 noComp;
 CztProtIE_Field_CellActvnResp_IEs *member;
}CztProtIE_Cont_CellActvnResp_IEs;

typedef struct x2apCellActvnResp
{
 TknPres pres;
 CztProtIE_Cont_CellActvnResp_IEs protocolIEs;
} CztCellActvnResp;

typedef struct x2ap_ValueCellActvnFail_IEsCls{
 union {
  CztCause cztCause;
  CztCriticalityDiag cztCriticalityDiag;
 } u;
} Czt_ValueCellActvnFail_IEsCls;
typedef struct x2apProtIE_Field_CellActvnFail_IEs
{
 TknPres pres;
 CztProtIE_ID id;
 CztCriticality criticality;
 Czt_ValueCellActvnFail_IEsCls value;
} CztProtIE_Field_CellActvnFail_IEs;

typedef struct x2apProtIE_Cont_CellActvnFail_IEs
{
 TknU16 noComp;
 CztProtIE_Field_CellActvnFail_IEs *member;
}CztProtIE_Cont_CellActvnFail_IEs;

typedef struct x2apCellActvnFail
{
 TknPres pres;
 CztProtIE_Cont_CellActvnFail_IEs protocolIEs;
} CztCellActvnFail;

typedef struct x2ap_InitiatingMsgCls{
 union {
  CztHovrRqst cztHovrRqst;
  CztResetRqst cztResetRqst;
  CztX2SetupRqst cztX2SetupRqst;
  CztResStatusRqst cztResStatusRqst;
  CztENBConfigUpd cztENBConfigUpd;
  CztMobilityChangeRqst cztMobilityChangeRqst;
  CztCellActvnRqst cztCellActvnRqst;
  CztSNStatusTfr cztSNStatusTfr;
  CztUECntxtRls cztUECntxtRls;
  CztHovrCancel cztHovrCancel;
  CztErrInd cztErrInd;
  CztResStatusUpd cztResStatusUpd;
  CztLoadInform cztLoadInform;
  CztPrivMsg cztPrivMsg;
  CztRLFInd cztRLFInd;
  CztHovrReport cztHovrReport;
 } u;
} Czt_InitiatingMsgCls;
typedef struct x2apInitiatingMsg
{
 TknPres pres;
 CztProcedureCode procedureCode;
 CztCriticality criticality;
 Czt_InitiatingMsgCls value;
} CztInitiatingMsg;

typedef struct x2ap_SuccessfulOutcomeCls{
 union {
  CztHovrRqstAckg cztHovrRqstAckg;
  CztResetResp cztResetResp;
  CztX2SetupResp cztX2SetupResp;
  CztResStatusResp cztResStatusResp;
  CztENBConfigUpdAckg cztENBConfigUpdAckg;
  CztMobilityChangeAckg cztMobilityChangeAckg;
  CztCellActvnResp cztCellActvnResp;
 } u;
} Czt_SuccessfulOutcomeCls;
typedef struct x2apSuccessfulOutcome
{
 TknPres pres;
 CztProcedureCode procedureCode;
 CztCriticality criticality;
 Czt_SuccessfulOutcomeCls value;
} CztSuccessfulOutcome;

typedef struct x2ap_UnsuccessfulOutcomeCls{
 union {
  CztHovrPrepFail cztHovrPrepFail;
  CztX2SetupFail cztX2SetupFail;
  CztResStatusFail cztResStatusFail;
  CztENBConfigUpdFail cztENBConfigUpdFail;
  CztMobilityChangeFail cztMobilityChangeFail;
  CztCellActvnFail cztCellActvnFail;
 } u;
} Czt_UnsuccessfulOutcomeCls;
typedef struct x2apUnsuccessfulOutcome
{
 TknPres pres;
 CztProcedureCode procedureCode;
 CztCriticality criticality;
 Czt_UnsuccessfulOutcomeCls value;
} CztUnsuccessfulOutcome;

typedef struct x2apX2AP_PDU
{
 TknU8 choice;
 union {
  CztInitiatingMsg initiatingMsg;
  CztSuccessfulOutcome successfulOutcome;
  CztUnsuccessfulOutcome unsuccessfulOutcome;
 } val;
} CztX2AP_PDU;


U32 flagCz3O = 0x1 | 0x80000000;
U32 flagCz3M = 0x2 | 0x80000000;
U32 flagCz3D = 0x4 | 0x80000000;
CmPAsnElmDef czConstTerm =
{



   CM_PASN_TET_SETSEQ_TERM,
   0,
   0,
   &flagCz3M,
   0,
   0L
};
 CmPAsnElmDef czNull =
{



  CM_PASN_TET_NULL,
  0,
  0,
  &flagCz3M,
  0,
  0L
};
CmPAsnElmDef czExtMkr =
{



  CM_PASN_TET_EXT_MKR,
  0,
  0,
  &flagCz3M,
  0,
  0L
};

CmPAsnTknEnum czCriticalityLst[4] =
{
 3,
 CztCriticalityrejectEnum,
 CztCriticalityignoreEnum,
 CztCriticalitynotifyEnum
};
CmPAsnEnumDef czCriticalityspec =
{



 czCriticalityLst,
 0L
};
CmPAsnElmDef czOptCriticality =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztCriticality),
 &flagCz3O,
 0,
 (U8 *)(&czCriticalityspec),
 0L
};
CmPAsnElmDef czCriticality =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztCriticality),
 &flagCz3M,
 0,
 (U8 *)(&czCriticalityspec),
 0L
};


CmPAsnTknEnum czPresenceLst[4] =
{
 3,
 CztPresenceoptionalEnum,
 CztPresenceconditionalEnum,
 CztPresencemandatoryEnum
};
CmPAsnEnumDef czPresencespec =
{



 czPresenceLst,
 0L
};
CmPAsnElmDef czPresence =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztPresence),
 &flagCz3M,
 0,
 (U8 *)(&czPresencespec),
 0L
};


CmPAsnUIntDef czPrivIE_IDlocalspec =
{



 0,
 65535
};
CmPAsnElmDef czPrivIE_IDlocal =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztPrivIE_IDlocal),
 &flagCz3M,
 0,
 (U8 *)(&czPrivIE_IDlocalspec),
 0L
};

 CmPAsnElmDef *czPrivIE_IDTkn[] =
{
 &czPrivIE_IDlocal,
 &czConstTerm
};
CmPAsnChoiceDef czPrivIE_IDspec =
{



 2,
 0,
 &czPrivIE_IDTkn[0]
};
CmPAsnElmDef czPrivIE_ID =
{



 CM_PASN_TET_CHOICE,
 0,
 sizeof(CztPrivIE_ID),
 &flagCz3M,
 0L,
 (U8 *)(&czPrivIE_IDspec),
 0L
};

CmPAsnUIntDef czProcedureCodespec =
{



 0,
 255UL
};
CmPAsnElmDef czProcedureCode =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztProcedureCode),
 &flagCz3M,
 0,
 (U8 *)(&czProcedureCodespec),
 0L
};
CmPAsnElmDef czOptProcedureCode =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztProcedureCode),
 &flagCz3O,
 0,
 (U8 *)(&czProcedureCodespec),
 0L
};


CmPAsnUIntDef czProtIE_IDspec =
{



 0,
 65535
};
CmPAsnElmDef czProtIE_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztProtIE_ID),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_IDspec),
 0L
};


CmPAsnTknEnum czTrgMsgLst[4] =
{
 3,
 CztTrgMsginitiating_messageEnum,
 CztTrgMsgsuccessful_outcomeEnum,
 CztTrgMsgunsuccessful_outcomeEnum
};
CmPAsnEnumDef czTrgMsgspec =
{



 czTrgMsgLst,
 0L
};
CmPAsnElmDef czOptTrgMsg =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztTrgMsg),
 &flagCz3O,
 0,
 (U8 *)(&czTrgMsgspec),
 0L
};

CmPAsnBitStrDef czABSInformFDDabs_pattern_infospec =
{



 40,
 40
};
CmPAsnElmDef czABSInformFDDabs_pattern_info =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(CztABSInformFDDabs_pattern_info),
 &flagCz3M,
 0,
 (U8 *) (&czABSInformFDDabs_pattern_infospec),
 0L
};

CmPAsnTknEnum czABSInformFDDnumberOfCellSpecificAntennaPortsLst[4] =
{
 3,
 CztABSInformFDDnumberOfCellSpecificAntennaPortsoneEnum,
 CztABSInformFDDnumberOfCellSpecificAntennaPortstwoEnum,
 CztABSInformFDDnumberOfCellSpecificAntennaPortsfourEnum
};
CmPAsnEnumDef czABSInformFDDnumberOfCellSpecificAntennaPortsspec =
{



 czABSInformFDDnumberOfCellSpecificAntennaPortsLst,
 0L
};
CmPAsnElmDef czABSInformFDDnumberOfCellSpecificAntennaPorts =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztABSInformFDDnumberOfCellSpecificAntennaPorts),
 &flagCz3M,
 0,
 (U8 *)(&czABSInformFDDnumberOfCellSpecificAntennaPortsspec),
 0L
};

CmPAsnBitStrDef czABSInformFDDmeasurement_subsetspec =
{



 40,
 40
};
CmPAsnElmDef czABSInformFDDmeasurement_subset =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(CztABSInformFDDmeasurement_subset),
 &flagCz3M,
 0,
 (U8 *) (&czABSInformFDDmeasurement_subsetspec),
 0L
};
 CmPAsnElmDef *cz_ExtnABSInformFDD_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnABSInformFDD_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnABSInformFDD_ExtIEsClsInfo =
{
 0,
 &cz_ExtnABSInformFDD_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnABSInformFDD_ExtIEsClsSpec =
{



 &cz_ExtnABSInformFDD_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnABSInformFDD_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnABSInformFDD_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnABSInformFDD_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnABSInformFDD_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_ABSInformFDD_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnABSInformFDD_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_ABSInformFDD_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_ABSInformFDD_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_ABSInformFDD_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_ABSInformFDD_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_ABSInformFDD_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_ABSInformFDD_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_ABSInformFDD_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ABSInformFDD_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_ABSInformFDD_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_ABSInformFDD_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ABSInformFDD_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_ABSInformFDD_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czABSInformFDDTkn[] =
{
 &czABSInformFDDabs_pattern_info,
 &czABSInformFDDnumberOfCellSpecificAntennaPorts,
 &czABSInformFDDmeasurement_subset,
 &czOptProtExtnCont_ABSInformFDD_ExtIEs,
  &czProtExtnField_ABSInformFDD_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czABSInformFDDspec =
{



 1,
 0,
 0L,
 0L,
 &czABSInformFDDTkn[0],
 0
};
 CmPAsnElmDef czABSInformFDD =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztABSInformFDD),
 &flagCz3M,
 0,
 (U8 *)(&czABSInformFDDspec),
 0L
};
CmPAsnBitStrDef czABSInformTDDabs_pattern_infospec =
{



 1,
 70
};
CmPAsnElmDef czABSInformTDDabs_pattern_info =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(CztABSInformTDDabs_pattern_info),
 &flagCz3M,
 0,
 (U8 *) (&czABSInformTDDabs_pattern_infospec),
 0L
};

CmPAsnTknEnum czABSInformTDDnumberOfCellSpecificAntennaPortsLst[4] =
{
 3,
 CztABSInformTDDnumberOfCellSpecificAntennaPortsoneEnum,
 CztABSInformTDDnumberOfCellSpecificAntennaPortstwoEnum,
 CztABSInformTDDnumberOfCellSpecificAntennaPortsfourEnum
};
CmPAsnEnumDef czABSInformTDDnumberOfCellSpecificAntennaPortsspec =
{



 czABSInformTDDnumberOfCellSpecificAntennaPortsLst,
 0L
};
CmPAsnElmDef czABSInformTDDnumberOfCellSpecificAntennaPorts =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztABSInformTDDnumberOfCellSpecificAntennaPorts),
 &flagCz3M,
 0,
 (U8 *)(&czABSInformTDDnumberOfCellSpecificAntennaPortsspec),
 0L
};

CmPAsnBitStrDef czABSInformTDDmeasurement_subsetspec =
{



 1,
 70
};
CmPAsnElmDef czABSInformTDDmeasurement_subset =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(CztABSInformTDDmeasurement_subset),
 &flagCz3M,
 0,
 (U8 *) (&czABSInformTDDmeasurement_subsetspec),
 0L
};
 CmPAsnElmDef *cz_ExtnABSInformTDD_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnABSInformTDD_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnABSInformTDD_ExtIEsClsInfo =
{
 0,
 &cz_ExtnABSInformTDD_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnABSInformTDD_ExtIEsClsSpec =
{



 &cz_ExtnABSInformTDD_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnABSInformTDD_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnABSInformTDD_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnABSInformTDD_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnABSInformTDD_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_ABSInformTDD_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnABSInformTDD_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_ABSInformTDD_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_ABSInformTDD_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_ABSInformTDD_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_ABSInformTDD_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_ABSInformTDD_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_ABSInformTDD_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_ABSInformTDD_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ABSInformTDD_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_ABSInformTDD_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_ABSInformTDD_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ABSInformTDD_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_ABSInformTDD_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czABSInformTDDTkn[] =
{
 &czABSInformTDDabs_pattern_info,
 &czABSInformTDDnumberOfCellSpecificAntennaPorts,
 &czABSInformTDDmeasurement_subset,
 &czOptProtExtnCont_ABSInformTDD_ExtIEs,
  &czProtExtnField_ABSInformTDD_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czABSInformTDDspec =
{



 1,
 0,
 0L,
 0L,
 &czABSInformTDDTkn[0],
 0
};
 CmPAsnElmDef czABSInformTDD =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztABSInformTDD),
 &flagCz3M,
 0,
 (U8 *)(&czABSInformTDDspec),
 0L
};
 CmPAsnElmDef *czABSInformTkn[] =
{
 &czABSInformFDD,
 &czABSInformTDD,
 &czNull,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czABSInformspec =
{



 3,
 0,
 &czABSInformTkn[0]
};
CmPAsnElmDef czABSInform =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztABSInform),
 &flagCz3M,
 0L,
 (U8 *)(&czABSInformspec),
 0L
};

CmPAsnUIntDef czDL_ABS_statusspec =
{



 0,
 100UL
};
CmPAsnElmDef czDL_ABS_status =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztDL_ABS_status),
 &flagCz3M,
 0,
 (U8 *)(&czDL_ABS_statusspec),
 0L
};

CmPAsnBitStrDef czUsableABSInformFDDusable_abs_pattern_infospec =
{



 40,
 40
};
CmPAsnElmDef czUsableABSInformFDDusable_abs_pattern_info =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(CztUsableABSInformFDDusable_abs_pattern_info),
 &flagCz3M,
 0,
 (U8 *) (&czUsableABSInformFDDusable_abs_pattern_infospec),
 0L
};
 CmPAsnElmDef *cz_ExtnUsableABSInformFDD_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnUsableABSInformFDD_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnUsableABSInformFDD_ExtIEsClsInfo =
{
 0,
 &cz_ExtnUsableABSInformFDD_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnUsableABSInformFDD_ExtIEsClsSpec =
{



 &cz_ExtnUsableABSInformFDD_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnUsableABSInformFDD_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnUsableABSInformFDD_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnUsableABSInformFDD_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnUsableABSInformFDD_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_UsableABSInformFDD_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnUsableABSInformFDD_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_UsableABSInformFDD_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_UsableABSInformFDD_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_UsableABSInformFDD_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_UsableABSInformFDD_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_UsableABSInformFDD_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_UsableABSInformFDD_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_UsableABSInformFDD_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UsableABSInformFDD_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_UsableABSInformFDD_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_UsableABSInformFDD_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UsableABSInformFDD_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_UsableABSInformFDD_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czUsableABSInformFDDTkn[] =
{
 &czUsableABSInformFDDusable_abs_pattern_info,
 &czOptProtExtnCont_UsableABSInformFDD_ExtIEs,
  &czProtExtnField_UsableABSInformFDD_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czUsableABSInformFDDspec =
{



 1,
 0,
 0L,
 0L,
 &czUsableABSInformFDDTkn[0],
 0
};
 CmPAsnElmDef czUsableABSInformFDD =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztUsableABSInformFDD),
 &flagCz3M,
 0,
 (U8 *)(&czUsableABSInformFDDspec),
 0L
};
CmPAsnBitStrDef czUsableABSInformTDDusaable_abs_pattern_infospec =
{



 1,
 70
};
CmPAsnElmDef czUsableABSInformTDDusaable_abs_pattern_info =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(CztUsableABSInformTDDusaable_abs_pattern_info),
 &flagCz3M,
 0,
 (U8 *) (&czUsableABSInformTDDusaable_abs_pattern_infospec),
 0L
};
 CmPAsnElmDef *cz_ExtnUsableABSInformTDD_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnUsableABSInformTDD_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnUsableABSInformTDD_ExtIEsClsInfo =
{
 0,
 &cz_ExtnUsableABSInformTDD_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnUsableABSInformTDD_ExtIEsClsSpec =
{



 &cz_ExtnUsableABSInformTDD_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnUsableABSInformTDD_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnUsableABSInformTDD_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnUsableABSInformTDD_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnUsableABSInformTDD_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_UsableABSInformTDD_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnUsableABSInformTDD_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_UsableABSInformTDD_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_UsableABSInformTDD_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_UsableABSInformTDD_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_UsableABSInformTDD_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_UsableABSInformTDD_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_UsableABSInformTDD_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_UsableABSInformTDD_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UsableABSInformTDD_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_UsableABSInformTDD_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_UsableABSInformTDD_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UsableABSInformTDD_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_UsableABSInformTDD_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czUsableABSInformTDDTkn[] =
{
 &czUsableABSInformTDDusaable_abs_pattern_info,
 &czOptProtExtnCont_UsableABSInformTDD_ExtIEs,
  &czProtExtnField_UsableABSInformTDD_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czUsableABSInformTDDspec =
{



 1,
 0,
 0L,
 0L,
 &czUsableABSInformTDDTkn[0],
 0
};
 CmPAsnElmDef czUsableABSInformTDD =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztUsableABSInformTDD),
 &flagCz3M,
 0,
 (U8 *)(&czUsableABSInformTDDspec),
 0L
};
 CmPAsnElmDef *czUsableABSInformTkn[] =
{
 &czUsableABSInformFDD,
 &czUsableABSInformTDD,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czUsableABSInformspec =
{



 2,
 0,
 &czUsableABSInformTkn[0]
};
CmPAsnElmDef czUsableABSInform =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztUsableABSInform),
 &flagCz3M,
 0L,
 (U8 *)(&czUsableABSInformspec),
 0L
};
 CmPAsnElmDef *cz_ExtnABS_Status_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnABS_Status_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnABS_Status_ExtIEsClsInfo =
{
 0,
 &cz_ExtnABS_Status_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnABS_Status_ExtIEsClsSpec =
{



 &cz_ExtnABS_Status_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnABS_Status_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnABS_Status_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnABS_Status_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnABS_Status_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_ABS_Status_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnABS_Status_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_ABS_Status_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_ABS_Status_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_ABS_Status_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_ABS_Status_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_ABS_Status_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_ABS_Status_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_ABS_Status_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ABS_Status_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_ABS_Status_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_ABS_Status_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ABS_Status_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_ABS_Status_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czABS_StatusTkn[] =
{
 &czDL_ABS_status,
 &czUsableABSInform,
 &czOptProtExtnCont_ABS_Status_ExtIEs,
  &czProtExtnField_ABS_Status_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czABS_Statusspec =
{



 1,
 0,
 0L,
 0L,
 &czABS_StatusTkn[0],
 0
};
 CmPAsnElmDef czABS_Status =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztABS_Status),
 &flagCz3M,
 0,
 (U8 *)(&czABS_Statusspec),
 0L
};

CmPAsnTknEnum czAdditionalSpecialSubframePatternsLst[11] =
{
 10,
 CztAdditionalSpecialSubframePatternsssp0Enum,
 CztAdditionalSpecialSubframePatternsssp1Enum,
 CztAdditionalSpecialSubframePatternsssp2Enum,
 CztAdditionalSpecialSubframePatternsssp3Enum,
 CztAdditionalSpecialSubframePatternsssp4Enum,
 CztAdditionalSpecialSubframePatternsssp5Enum,
 CztAdditionalSpecialSubframePatternsssp6Enum,
 CztAdditionalSpecialSubframePatternsssp7Enum,
 CztAdditionalSpecialSubframePatternsssp8Enum,
 CztAdditionalSpecialSubframePatternsssp9Enum
};
CmPAsnEnumDef czAdditionalSpecialSubframePatternsspec =
{



 czAdditionalSpecialSubframePatternsLst,
 0L
};
CmPAsnElmDef czAdditionalSpecialSubframePatterns =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztAdditionalSpecialSubframePatterns),
 &flagCz3M,
 0,
 (U8 *)(&czAdditionalSpecialSubframePatternsspec),
 0L
};


CmPAsnTknEnum czCyclicPrefixDLLst[3] =
{
 2,
 CztCyclicPrefixDLnormalEnum,
 CztCyclicPrefixDLextendedEnum
};
CmPAsnEnumDef czCyclicPrefixDLspec =
{



 czCyclicPrefixDLLst,
 0L
};
CmPAsnElmDef czCyclicPrefixDL =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztCyclicPrefixDL),
 &flagCz3M,
 0,
 (U8 *)(&czCyclicPrefixDLspec),
 0L
};


CmPAsnTknEnum czCyclicPrefixULLst[3] =
{
 2,
 CztCyclicPrefixULnormalEnum,
 CztCyclicPrefixULextendedEnum
};
CmPAsnEnumDef czCyclicPrefixULspec =
{



 czCyclicPrefixULLst,
 0L
};
CmPAsnElmDef czCyclicPrefixUL =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztCyclicPrefixUL),
 &flagCz3M,
 0,
 (U8 *)(&czCyclicPrefixULspec),
 0L
};

 CmPAsnElmDef *cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsClsInfo =
{
 0,
 &cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsClsSpec =
{



 &cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_AdditionalSpecialSubframe_Info_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_AdditionalSpecialSubframe_Info_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_AdditionalSpecialSubframe_Info_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_AdditionalSpecialSubframe_Info_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czAdditionalSpecialSubframe_InfoTkn[] =
{
 &czAdditionalSpecialSubframePatterns,
 &czCyclicPrefixDL,
 &czCyclicPrefixUL,
 &czOptProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs,
  &czProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czAdditionalSpecialSubframe_Infospec =
{



 1,
 0,
 0L,
 0L,
 &czAdditionalSpecialSubframe_InfoTkn[0],
 0
};
 CmPAsnElmDef czAdditionalSpecialSubframe_Info =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztAdditionalSpecialSubframe_Info),
 &flagCz3M,
 0,
 (U8 *)(&czAdditionalSpecialSubframe_Infospec),
 0L
};
CmPAsnBitStrDef czKey_eNodeB_Starspec =
{



 256,
 256
};
CmPAsnElmDef czKey_eNodeB_Star =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(CztKey_eNodeB_Star),
 &flagCz3M,
 0,
 (U8 *) (&czKey_eNodeB_Starspec),
 0L
};

CmPAsnUIntDef czNextHopChainingCountspec =
{



 0,
 7UL
};
CmPAsnElmDef czNextHopChainingCount =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztNextHopChainingCount),
 &flagCz3M,
 0,
 (U8 *)(&czNextHopChainingCountspec),
 0L
};

 CmPAsnElmDef *cz_ExtnAS_SecurInform_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnAS_SecurInform_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnAS_SecurInform_ExtIEsClsInfo =
{
 0,
 &cz_ExtnAS_SecurInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnAS_SecurInform_ExtIEsClsSpec =
{



 &cz_ExtnAS_SecurInform_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnAS_SecurInform_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnAS_SecurInform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnAS_SecurInform_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnAS_SecurInform_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_AS_SecurInform_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnAS_SecurInform_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_AS_SecurInform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_AS_SecurInform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_AS_SecurInform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_AS_SecurInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_AS_SecurInform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_AS_SecurInform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_AS_SecurInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_AS_SecurInform_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_AS_SecurInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_AS_SecurInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_AS_SecurInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_AS_SecurInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czAS_SecurInformTkn[] =
{
 &czKey_eNodeB_Star,
 &czNextHopChainingCount,
 &czOptProtExtnCont_AS_SecurInform_ExtIEs,
  &czProtExtnField_AS_SecurInform_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czAS_SecurInformspec =
{



 1,
 0,
 0L,
 0L,
 &czAS_SecurInformTkn[0],
 0
};
 CmPAsnElmDef czAS_SecurInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztAS_SecurInform),
 &flagCz3M,
 0,
 (U8 *)(&czAS_SecurInformspec),
 0L
};

CmPAsnUIntDef czPriorityLvlspec =
{



 0,
 15UL
};
CmPAsnElmDef czPriorityLvl =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztPriorityLvl),
 &flagCz3M,
 0,
 (U8 *)(&czPriorityLvlspec),
 0L
};


CmPAsnTknEnum czPre_emptionCapbltyLst[3] =
{
 2,
 CztPre_emptionCapbltyshall_not_trigger_pre_emptionEnum,
 CztPre_emptionCapbltymay_trigger_pre_emptionEnum
};
CmPAsnEnumDef czPre_emptionCapbltyspec =
{



 czPre_emptionCapbltyLst,
 0L
};
CmPAsnElmDef czPre_emptionCapblty =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztPre_emptionCapblty),
 &flagCz3M,
 0,
 (U8 *)(&czPre_emptionCapbltyspec),
 0L
};


CmPAsnTknEnum czPre_emptionVulnerabilityLst[3] =
{
 2,
 CztPre_emptionVulnerabilitynot_pre_emptableEnum,
 CztPre_emptionVulnerabilitypre_emptableEnum
};
CmPAsnEnumDef czPre_emptionVulnerabilityspec =
{



 czPre_emptionVulnerabilityLst,
 0L
};
CmPAsnElmDef czPre_emptionVulnerability =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztPre_emptionVulnerability),
 &flagCz3M,
 0,
 (U8 *)(&czPre_emptionVulnerabilityspec),
 0L
};

 CmPAsnElmDef *cz_ExtnAllocnAndRetentionPriority_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnAllocnAndRetentionPriority_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnAllocnAndRetentionPriority_ExtIEsClsInfo =
{
 0,
 &cz_ExtnAllocnAndRetentionPriority_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnAllocnAndRetentionPriority_ExtIEsClsSpec =
{



 &cz_ExtnAllocnAndRetentionPriority_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnAllocnAndRetentionPriority_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnAllocnAndRetentionPriority_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnAllocnAndRetentionPriority_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_AllocnAndRetentionPriority_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnAllocnAndRetentionPriority_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_AllocnAndRetentionPriority_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_AllocnAndRetentionPriority_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_AllocnAndRetentionPriority_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_AllocnAndRetentionPriority_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_AllocnAndRetentionPriority_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_AllocnAndRetentionPriority_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_AllocnAndRetentionPriority_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czAllocnAndRetentionPriorityTkn[] =
{
 &czPriorityLvl,
 &czPre_emptionCapblty,
 &czPre_emptionVulnerability,
 &czOptProtExtnCont_AllocnAndRetentionPriority_ExtIEs,
  &czProtExtnField_AllocnAndRetentionPriority_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czAllocnAndRetentionPriorityspec =
{



 1,
 0,
 0L,
 0L,
 &czAllocnAndRetentionPriorityTkn[0],
 0
};
 CmPAsnElmDef czAllocnAndRetentionPriority =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztAllocnAndRetentionPriority),
 &flagCz3M,
 0,
 (U8 *)(&czAllocnAndRetentionPriorityspec),
 0L
};
CmPAsnOctStrDef czPLMN_Identityspec =
{



 3,
 3
};
CmPAsnElmDef czPLMN_Identity =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(CztPLMN_Identity),
 &flagCz3M,
 0,
 (U8 *) (&czPLMN_Identityspec),
 0L
};
CmPAsnBitStrDef czEUTRANCellIdentifierspec =
{



 28,
 28
};
CmPAsnElmDef czEUTRANCellIdentifier =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztEUTRANCellIdentifier),
 &flagCz3M,
 0,
 (U8 *) (&czEUTRANCellIdentifierspec),
 0L
};
 CmPAsnElmDef *cz_ExtnECGI_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnECGI_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnECGI_ExtIEsClsInfo =
{
 0,
 &cz_ExtnECGI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnECGI_ExtIEsClsSpec =
{



 &cz_ExtnECGI_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnECGI_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnECGI_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnECGI_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnECGI_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_ECGI_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnECGI_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_ECGI_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_ECGI_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_ECGI_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_ECGI_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_ECGI_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_ECGI_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_ECGI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ECGI_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_ECGI_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_ECGI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ECGI_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_ECGI_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czECGITkn[] =
{
 &czPLMN_Identity,
 &czEUTRANCellIdentifier,
 &czOptProtExtnCont_ECGI_ExtIEs,
  &czProtExtnField_ECGI_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czECGIspec =
{



 1,
 0,
 0L,
 0L,
 &czECGITkn[0],
 0
};
 CmPAsnElmDef czECGI =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztECGI),
 &flagCz3M,
 0,
 (U8 *)(&czECGIspec),
 0L
};
CmPAsnSetSeqOfDef czCellIdLstforMDTspec =
{



 1,
 32,
 3*sizeof(U32)
};
 CmPAsnElmDef czCellIdLstforMDT =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztCellIdLstforMDT),
 &flagCz3M,
 0,
 (U8 *) (&czCellIdLstforMDTspec),
 0L
};
 CmPAsnElmDef *cz_ExtnCellBasedMDT_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCellBasedMDT_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCellBasedMDT_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCellBasedMDT_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCellBasedMDT_ExtIEsClsSpec =
{



 &cz_ExtnCellBasedMDT_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCellBasedMDT_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCellBasedMDT_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCellBasedMDT_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCellBasedMDT_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CellBasedMDT_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCellBasedMDT_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CellBasedMDT_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CellBasedMDT_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CellBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CellBasedMDT_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CellBasedMDT_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CellBasedMDT_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CellBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellBasedMDT_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CellBasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CellBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellBasedMDT_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CellBasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCellBasedMDTTkn[] =
{
 &czCellIdLstforMDT,
  &czECGI,
  &czConstTerm,
 &czOptProtExtnCont_CellBasedMDT_ExtIEs,
  &czProtExtnField_CellBasedMDT_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCellBasedMDTspec =
{



 1,
 0,
 0L,
 0L,
 &czCellBasedMDTTkn[0],
 0
};
 CmPAsnElmDef czCellBasedMDT =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCellBasedMDT),
 &flagCz3M,
 0,
 (U8 *)(&czCellBasedMDTspec),
 0L
};
CmPAsnOctStrDef czTACspec =
{



 2,
 2
};
CmPAsnElmDef czTAC =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(CztTAC),
 &flagCz3M,
 0,
 (U8 *) (&czTACspec),
 0L
};
CmPAsnSetSeqOfDef czTALstforMDTspec =
{



 1,
 8,
 3*sizeof(U32)
};
 CmPAsnElmDef czTALstforMDT =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztTALstforMDT),
 &flagCz3M,
 0,
 (U8 *) (&czTALstforMDTspec),
 0L
};
 CmPAsnElmDef *cz_ExtnTABasedMDT_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnTABasedMDT_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnTABasedMDT_ExtIEsClsInfo =
{
 0,
 &cz_ExtnTABasedMDT_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnTABasedMDT_ExtIEsClsSpec =
{



 &cz_ExtnTABasedMDT_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnTABasedMDT_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnTABasedMDT_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnTABasedMDT_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnTABasedMDT_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_TABasedMDT_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnTABasedMDT_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_TABasedMDT_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_TABasedMDT_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_TABasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_TABasedMDT_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_TABasedMDT_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_TABasedMDT_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_TABasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TABasedMDT_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_TABasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_TABasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TABasedMDT_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_TABasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czTABasedMDTTkn[] =
{
 &czTALstforMDT,
  &czTAC,
  &czConstTerm,
 &czOptProtExtnCont_TABasedMDT_ExtIEs,
  &czProtExtnField_TABasedMDT_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czTABasedMDTspec =
{



 1,
 0,
 0L,
 0L,
 &czTABasedMDTTkn[0],
 0
};
 CmPAsnElmDef czTABasedMDT =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztTABasedMDT),
 &flagCz3M,
 0,
 (U8 *)(&czTABasedMDTspec),
 0L
};
 CmPAsnElmDef *cz_ExtnTAI_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnTAI_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnTAI_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnTAI_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnTAI_Item_ExtIEsClsSpec =
{



 &cz_ExtnTAI_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnTAI_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnTAI_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnTAI_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnTAI_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_TAI_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnTAI_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_TAI_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_TAI_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_TAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_TAI_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_TAI_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_TAI_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_TAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TAI_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_TAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_TAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TAI_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_TAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czTAI_ItemTkn[] =
{
 &czTAC,
 &czPLMN_Identity,
 &czOptProtExtnCont_TAI_Item_ExtIEs,
  &czProtExtnField_TAI_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czTAI_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czTAI_ItemTkn[0],
 0
};
 CmPAsnElmDef czTAI_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztTAI_Item),
 &flagCz3M,
 0,
 (U8 *)(&czTAI_Itemspec),
 0L
};
CmPAsnSetSeqOfDef czTAILstforMDTspec =
{



 1,
 8,
 3*sizeof(U32)
};
 CmPAsnElmDef czTAILstforMDT =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztTAILstforMDT),
 &flagCz3M,
 0,
 (U8 *) (&czTAILstforMDTspec),
 0L
};
 CmPAsnElmDef *cz_ExtnTAIBasedMDT_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnTAIBasedMDT_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnTAIBasedMDT_ExtIEsClsInfo =
{
 0,
 &cz_ExtnTAIBasedMDT_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnTAIBasedMDT_ExtIEsClsSpec =
{



 &cz_ExtnTAIBasedMDT_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnTAIBasedMDT_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnTAIBasedMDT_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnTAIBasedMDT_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnTAIBasedMDT_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_TAIBasedMDT_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnTAIBasedMDT_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_TAIBasedMDT_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_TAIBasedMDT_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_TAIBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_TAIBasedMDT_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_TAIBasedMDT_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_TAIBasedMDT_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_TAIBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TAIBasedMDT_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_TAIBasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_TAIBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TAIBasedMDT_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_TAIBasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czTAIBasedMDTTkn[] =
{
 &czTAILstforMDT,
  &czTAI_Item,
  &czConstTerm,
 &czOptProtExtnCont_TAIBasedMDT_ExtIEs,
  &czProtExtnField_TAIBasedMDT_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czTAIBasedMDTspec =
{



 1,
 0,
 0L,
 0L,
 &czTAIBasedMDTTkn[0],
 0
};
 CmPAsnElmDef czTAIBasedMDT =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztTAIBasedMDT),
 &flagCz3M,
 0,
 (U8 *)(&czTAIBasedMDTspec),
 0L
};
 CmPAsnElmDef *czAreaScopeOfMDTTkn[] =
{
 &czCellBasedMDT,
 &czTABasedMDT,
 &czNull,
 &czExtMkr,
 &czTAIBasedMDT,
 &czConstTerm
};
CmPAsnChoiceDef czAreaScopeOfMDTspec =
{



 3,
 1,
 &czAreaScopeOfMDTTkn[0]
};
CmPAsnElmDef czAreaScopeOfMDT =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztAreaScopeOfMDT),
 &flagCz3M,
 0L,
 (U8 *)(&czAreaScopeOfMDTspec),
 0L
};

CmPAsnUIntXLDef czBitRatespec =
{



 {
  1,
  {0}
 },
 {
  5,
  {2, 84, 11, 228, 0}
 }
};
CmPAsnElmDef czBitRate =
{



 CM_PASN_TET_UINTXL,
 0,
 sizeof(CztBitRate),
 &flagCz3M,
 0,
 (U8 *)(&czBitRatespec),
 0L
};

CmPAsnSetSeqOfDef czBroadcastPLMNs_Itemspec =
{



 1,
 6,
 3*sizeof(U32)
};
 CmPAsnElmDef czBroadcastPLMNs_Item =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztBroadcastPLMNs_Item),
 &flagCz3M,
 0,
 (U8 *) (&czBroadcastPLMNs_Itemspec),
 0L
};

CmPAsnUIntDef czCapacityValuespec =
{



 0,
 100UL
};
CmPAsnElmDef czCapacityValue =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztCapacityValue),
 &flagCz3M,
 0,
 (U8 *)(&czCapacityValuespec),
 0L
};


CmPAsnUIntDef czCellCapacityClassValuespec =
{



 1,
 100UL
};
CmPAsnElmDef czOptCellCapacityClassValue =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztCellCapacityClassValue),
 &flagCz3O,
 0,
 (U8 *)(&czCellCapacityClassValuespec),
 0L
};


CmPAsnTknEnum czCauseRadioNwExtLst[8] =
{
 7,
 CztCauseRadioNwload_balancingEnum,
 CztCauseRadioNwhandover_optimisationEnum,
 CztCauseRadioNwvalue_out_of_allowed_rangeEnum,
 CztCauseRadioNwmultiple_E_RAB_ID_instancesEnum,
 CztCauseRadioNwswitch_off_ongoingEnum,
 CztCauseRadioNwnot_supported_QCI_valueEnum,
 CztCauseRadioNwmeasurement_not_supported_for_the_objectEnum
};
CmPAsnTknEnum czCauseRadioNwLst[23] =
{
 22,
 CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum,
 CztCauseRadioNwtime_critical_handoverEnum,
 CztCauseRadioNwresource_optimisation_handoverEnum,
 CztCauseRadioNwreduce_load_in_serving_cellEnum,
 CztCauseRadioNwpartial_handoverEnum,
 CztCauseRadioNwunknown_new_eNB_UE_X2AP_IDEnum,
 CztCauseRadioNwunknown_old_eNB_UE_X2AP_IDEnum,
 CztCauseRadioNwunknown_pair_of_UE_X2AP_IDEnum,
 CztCauseRadioNwho_target_not_allowedEnum,
 CztCauseRadioNwtx2relocoverall_expiryEnum,
 CztCauseRadioNwtrelocprep_expiryEnum,
 CztCauseRadioNwcell_not_availableEnum,
 CztCauseRadioNwno_radio_resources_available_in_target_cellEnum,
 CztCauseRadioNwinvalid_MME_GroupIDEnum,
 CztCauseRadioNwunknown_MME_CodeEnum,
 CztCauseRadioNwencryption_and_or_integrity_protection_algorithms_not_supportedEnum,
 CztCauseRadioNwreportCharacteristicsEmptyEnum,
 CztCauseRadioNwnoReportPeriodicityEnum,
 CztCauseRadioNwexistingMeasurementIDEnum,
 CztCauseRadioNwunknown_eNB_Measurement_IDEnum,
 CztCauseRadioNwmeasurement_temporarily_not_availableEnum,
 CztCauseRadioNwunspecifiedEnum
};
CmPAsnEnumDef czCauseRadioNwspec =
{



 czCauseRadioNwLst,
 czCauseRadioNwExtLst
};
CmPAsnElmDef czCauseRadioNw =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztCauseRadioNw),
 &flagCz3M,
 0,
 (U8 *)(&czCauseRadioNwspec),
 0L
};


CmPAsnTknEnum czCauseTportLst[3] =
{
 2,
 CztCauseTporttransport_resource_unavailableEnum,
 CztCauseTportunspecifiedEnum
};
CmPAsnEnumDef czCauseTportspec =
{



 czCauseTportLst,
 0L
};
CmPAsnElmDef czCauseTport =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztCauseTport),
 &flagCz3M,
 0,
 (U8 *)(&czCauseTportspec),
 0L
};


CmPAsnTknEnum czCauseProtLst[8] =
{
 7,
 CztCauseProttransfer_syntax_errorEnum,
 CztCauseProtabstract_syntax_error_rejectEnum,
 CztCauseProtabstract_syntax_error_ignore_and_notifyEnum,
 CztCauseProtmessage_not_compatible_with_receiver_stateEnum,
 CztCauseProtsemantic_errorEnum,
 CztCauseProtunspecifiedEnum,
 CztCauseProtabstract_syntax_error_falsely_constructed_messageEnum
};
CmPAsnEnumDef czCauseProtspec =
{



 czCauseProtLst,
 0L
};
CmPAsnElmDef czCauseProt =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztCauseProt),
 &flagCz3M,
 0,
 (U8 *)(&czCauseProtspec),
 0L
};


CmPAsnTknEnum czCauseMiscLst[6] =
{
 5,
 CztCauseMisccontrol_processing_overloadEnum,
 CztCauseMischardware_failureEnum,
 CztCauseMiscom_interventionEnum,
 CztCauseMiscnot_enough_user_plane_processing_resourcesEnum,
 CztCauseMiscunspecifiedEnum
};
CmPAsnEnumDef czCauseMiscspec =
{



 czCauseMiscLst,
 0L
};
CmPAsnElmDef czCauseMisc =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztCauseMisc),
 &flagCz3M,
 0,
 (U8 *)(&czCauseMiscspec),
 0L
};

 CmPAsnElmDef *czCauseTkn[] =
{
 &czCauseRadioNw,
 &czCauseTport,
 &czCauseProt,
 &czCauseMisc,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czCausespec =
{



 4,
 0,
 &czCauseTkn[0]
};
CmPAsnElmDef czCause =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztCause),
 &flagCz3M,
 0L,
 (U8 *)(&czCausespec),
 0L
};

CmPAsnTknEnum czCell_SizeLst[5] =
{
 4,
 CztCell_SizeverysmallEnum,
 CztCell_SizesmallEnum,
 CztCell_SizemediumEnum,
 CztCell_SizelargeEnum
};
CmPAsnEnumDef czCell_Sizespec =
{



 czCell_SizeLst,
 0L
};
CmPAsnElmDef czCell_Size =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztCell_Size),
 &flagCz3M,
 0,
 (U8 *)(&czCell_Sizespec),
 0L
};

 CmPAsnElmDef *cz_ExtnCellTyp_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCellTyp_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCellTyp_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCellTyp_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCellTyp_ExtIEsClsSpec =
{



 &cz_ExtnCellTyp_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCellTyp_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCellTyp_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCellTyp_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCellTyp_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CellTyp_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCellTyp_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CellTyp_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CellTyp_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CellTyp_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CellTyp_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CellTyp_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CellTyp_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CellTyp_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellTyp_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CellTyp_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CellTyp_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellTyp_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CellTyp_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCellTypTkn[] =
{
 &czCell_Size,
 &czOptProtExtnCont_CellTyp_ExtIEs,
  &czProtExtnField_CellTyp_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCellTypspec =
{



 1,
 0,
 0L,
 0L,
 &czCellTypTkn[0],
 0
};
 CmPAsnElmDef czCellTyp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCellTyp),
 &flagCz3M,
 0,
 (U8 *)(&czCellTypspec),
 0L
};
 CmPAsnElmDef *cz_ExtnCompositeAvailableCapacity_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCompositeAvailableCapacity_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCompositeAvailableCapacity_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCompositeAvailableCapacity_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCompositeAvailableCapacity_ExtIEsClsSpec =
{



 &cz_ExtnCompositeAvailableCapacity_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCompositeAvailableCapacity_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCompositeAvailableCapacity_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCompositeAvailableCapacity_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCompositeAvailableCapacity_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CompositeAvailableCapacity_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCompositeAvailableCapacity_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CompositeAvailableCapacity_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CompositeAvailableCapacity_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CompositeAvailableCapacity_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CompositeAvailableCapacity_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CompositeAvailableCapacity_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CompositeAvailableCapacity_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CompositeAvailableCapacity_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CompositeAvailableCapacity_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CompositeAvailableCapacity_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CompositeAvailableCapacity_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CompositeAvailableCapacity_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CompositeAvailableCapacity_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCompositeAvailableCapacityTkn[] =
{
 &czOptCellCapacityClassValue,
 &czCapacityValue,
 &czOptProtExtnCont_CompositeAvailableCapacity_ExtIEs,
  &czProtExtnField_CompositeAvailableCapacity_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCompositeAvailableCapacityspec =
{



 2,
 0,
 0L,
 0L,
 &czCompositeAvailableCapacityTkn[0],
 0
};
 CmPAsnElmDef czCompositeAvailableCapacity =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCompositeAvailableCapacity),
 &flagCz3M,
 0,
 (U8 *)(&czCompositeAvailableCapacityspec),
 0L
};
 CmPAsnElmDef *cz_ExtnCompositeAvailableCapacityGroup_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCompositeAvailableCapacityGroup_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCompositeAvailableCapacityGroup_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCompositeAvailableCapacityGroup_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCompositeAvailableCapacityGroup_ExtIEsClsSpec =
{



 &cz_ExtnCompositeAvailableCapacityGroup_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCompositeAvailableCapacityGroup_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCompositeAvailableCapacityGroup_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCompositeAvailableCapacityGroup_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CompositeAvailableCapacityGroup_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCompositeAvailableCapacityGroup_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CompositeAvailableCapacityGroup_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CompositeAvailableCapacityGroup_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CompositeAvailableCapacityGroup_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CompositeAvailableCapacityGroup_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CompositeAvailableCapacityGroup_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CompositeAvailableCapacityGroup_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CompositeAvailableCapacityGroup_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCompositeAvailableCapacityGroupTkn[] =
{
 &czCompositeAvailableCapacity,
 &czCompositeAvailableCapacity,
 &czOptProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs,
  &czProtExtnField_CompositeAvailableCapacityGroup_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCompositeAvailableCapacityGroupspec =
{



 1,
 0,
 0L,
 0L,
 &czCompositeAvailableCapacityGroupTkn[0],
 0
};
 CmPAsnElmDef czCompositeAvailableCapacityGroup =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCompositeAvailableCapacityGroup),
 &flagCz3M,
 0,
 (U8 *)(&czCompositeAvailableCapacityGroupspec),
 0L
};

CmPAsnUIntDef czPDCP_SNspec =
{



 0,
 4095UL
};
CmPAsnElmDef czPDCP_SN =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztPDCP_SN),
 &flagCz3M,
 0,
 (U8 *)(&czPDCP_SNspec),
 0L
};


CmPAsnUIntDef czHFNspec =
{



 0,
 1048575UL
};
CmPAsnElmDef czHFN =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztHFN),
 &flagCz3M,
 0,
 (U8 *)(&czHFNspec),
 0L
};

 CmPAsnElmDef *cz_ExtnCOUNTvalue_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCOUNTvalue_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCOUNTvalue_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCOUNTvalue_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCOUNTvalue_ExtIEsClsSpec =
{



 &cz_ExtnCOUNTvalue_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCOUNTvalue_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCOUNTvalue_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCOUNTvalue_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCOUNTvalue_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_COUNTvalue_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCOUNTvalue_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_COUNTvalue_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_COUNTvalue_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_COUNTvalue_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_COUNTvalue_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_COUNTvalue_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_COUNTvalue_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_COUNTvalue_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_COUNTvalue_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_COUNTvalue_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_COUNTvalue_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_COUNTvalue_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_COUNTvalue_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCOUNTvalueTkn[] =
{
 &czPDCP_SN,
 &czHFN,
 &czOptProtExtnCont_COUNTvalue_ExtIEs,
  &czProtExtnField_COUNTvalue_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCOUNTvaluespec =
{



 1,
 0,
 0L,
 0L,
 &czCOUNTvalueTkn[0],
 0
};
 CmPAsnElmDef czCOUNTvalue =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCOUNTvalue),
 &flagCz3M,
 0,
 (U8 *)(&czCOUNTvaluespec),
 0L
};

CmPAsnUIntDef czPDCP_SNExtendedspec =
{



 0,
 32767UL
};
CmPAsnElmDef czPDCP_SNExtended =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztPDCP_SNExtended),
 &flagCz3M,
 0,
 (U8 *)(&czPDCP_SNExtendedspec),
 0L
};


CmPAsnUIntDef czHFNMdfdspec =
{



 0,
 131071UL
};
CmPAsnElmDef czHFNMdfd =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztHFNMdfd),
 &flagCz3M,
 0,
 (U8 *)(&czHFNMdfdspec),
 0L
};

 CmPAsnElmDef *cz_ExtnCOUNTValueExtended_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCOUNTValueExtended_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCOUNTValueExtended_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCOUNTValueExtended_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCOUNTValueExtended_ExtIEsClsSpec =
{



 &cz_ExtnCOUNTValueExtended_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCOUNTValueExtended_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCOUNTValueExtended_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCOUNTValueExtended_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCOUNTValueExtended_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_COUNTValueExtended_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCOUNTValueExtended_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_COUNTValueExtended_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_COUNTValueExtended_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_COUNTValueExtended_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_COUNTValueExtended_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_COUNTValueExtended_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_COUNTValueExtended_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_COUNTValueExtended_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_COUNTValueExtended_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_COUNTValueExtended_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_COUNTValueExtended_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_COUNTValueExtended_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_COUNTValueExtended_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCOUNTValueExtendedTkn[] =
{
 &czPDCP_SNExtended,
 &czHFNMdfd,
 &czOptProtExtnCont_COUNTValueExtended_ExtIEs,
  &czProtExtnField_COUNTValueExtended_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCOUNTValueExtendedspec =
{



 1,
 0,
 0L,
 0L,
 &czCOUNTValueExtendedTkn[0],
 0
};
 CmPAsnElmDef czCOUNTValueExtended =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCOUNTValueExtended),
 &flagCz3M,
 0,
 (U8 *)(&czCOUNTValueExtendedspec),
 0L
};

CmPAsnTknEnum czTypOfErrLst[3] =
{
 2,
 CztTypOfErrnot_understoodEnum,
 CztTypOfErrmissingEnum
};
CmPAsnEnumDef czTypOfErrspec =
{



 czTypOfErrLst,
 0L
};
CmPAsnElmDef czTypOfErr =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztTypOfErr),
 &flagCz3M,
 0,
 (U8 *)(&czTypOfErrspec),
 0L
};

 CmPAsnElmDef *cz_ExtnCriticalityDiag_IE_Lst_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCriticalityDiag_IE_Lst_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCriticalityDiag_IE_Lst_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCriticalityDiag_IE_Lst_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCriticalityDiag_IE_Lst_ExtIEsClsSpec =
{



 &cz_ExtnCriticalityDiag_IE_Lst_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCriticalityDiag_IE_Lst_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCriticalityDiag_IE_Lst_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCriticalityDiag_IE_Lst_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CriticalityDiag_IE_Lst_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCriticalityDiag_IE_Lst_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CriticalityDiag_IE_Lst_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CriticalityDiag_IE_Lst_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CriticalityDiag_IE_Lst_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CriticalityDiag_IE_Lst_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CriticalityDiag_IE_Lst_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CriticalityDiag_IE_Lst_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CriticalityDiag_IE_Lst_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCriticalityDiag_IE_LstMemberTkn[] =
{
 &czCriticality,
 &czProtIE_ID,
 &czTypOfErr,
 &czOptProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs,
  &czProtExtnField_CriticalityDiag_IE_Lst_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCriticalityDiag_IE_LstMemberspec =
{



 1,
 0,
 0L,
 0L,
 &czCriticalityDiag_IE_LstMemberTkn[0],
 0
};
 CmPAsnElmDef czCriticalityDiag_IE_LstMember =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCriticalityDiag_IE_LstMember),
 &flagCz3M,
 0,
 (U8 *)(&czCriticalityDiag_IE_LstMemberspec),
 0L
};
CmPAsnSetSeqOfDef czCriticalityDiag_IE_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptCriticalityDiag_IE_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztCriticalityDiag_IE_Lst),
 &flagCz3O,
 0,
 (U8 *) (&czCriticalityDiag_IE_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ExtnCriticalityDiag_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCriticalityDiag_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCriticalityDiag_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCriticalityDiag_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCriticalityDiag_ExtIEsClsSpec =
{



 &cz_ExtnCriticalityDiag_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCriticalityDiag_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCriticalityDiag_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCriticalityDiag_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCriticalityDiag_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CriticalityDiag_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCriticalityDiag_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CriticalityDiag_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CriticalityDiag_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CriticalityDiag_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CriticalityDiag_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CriticalityDiag_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CriticalityDiag_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CriticalityDiag_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CriticalityDiag_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CriticalityDiag_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CriticalityDiag_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CriticalityDiag_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CriticalityDiag_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCriticalityDiagTkn[] =
{
 &czOptProcedureCode,
 &czOptTrgMsg,
 &czOptCriticality,
 &czOptCriticalityDiag_IE_Lst,
  &czCriticalityDiag_IE_LstMember,
  &czConstTerm,
 &czOptProtExtnCont_CriticalityDiag_ExtIEs,
  &czProtExtnField_CriticalityDiag_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCriticalityDiagspec =
{



 5,
 0,
 0L,
 0L,
 &czCriticalityDiagTkn[0],
 0
};
 CmPAsnElmDef czCriticalityDiag =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCriticalityDiag),
 &flagCz3M,
 0,
 (U8 *)(&czCriticalityDiagspec),
 0L
};
CmPAsnBitStrDef czCRNTIspec =
{



 16,
 16
};
CmPAsnElmDef czCRNTI =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztCRNTI),
 &flagCz3M,
 0,
 (U8 *) (&czCRNTIspec),
 0L
};

CmPAsnTknEnum czCSGMembershipStatusLst[3] =
{
 2,
 CztCSGMembershipStatusmemberEnum,
 CztCSGMembershipStatusnot_memberEnum
};
CmPAsnEnumDef czCSGMembershipStatusspec =
{



 czCSGMembershipStatusLst,
 0L
};
CmPAsnElmDef czCSGMembershipStatus =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztCSGMembershipStatus),
 &flagCz3M,
 0,
 (U8 *)(&czCSGMembershipStatusspec),
 0L
};

CmPAsnBitStrDef czCSG_Idspec =
{



 27,
 27
};
CmPAsnElmDef czCSG_Id =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztCSG_Id),
 &flagCz3M,
 0,
 (U8 *) (&czCSG_Idspec),
 0L
};

CmPAsnTknEnum czDeactivationIndLst[2] =
{
 1,
 CztDeactivationInddeactivatedEnum
};
CmPAsnEnumDef czDeactivationIndspec =
{



 czDeactivationIndLst,
 0L
};
CmPAsnElmDef czDeactivationInd =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztDeactivationInd),
 &flagCz3M,
 0,
 (U8 *)(&czDeactivationIndspec),
 0L
};


CmPAsnTknEnum czDL_FwdingLst[2] =
{
 1,
 CztDL_FwdingdL_forwardingProposedEnum
};
CmPAsnEnumDef czDL_Fwdingspec =
{



 czDL_FwdingLst,
 0L
};
CmPAsnElmDef czOptDL_Fwding =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztDL_Fwding),
 &flagCz3O,
 0,
 (U8 *)(&czDL_Fwdingspec),
 0L
};


CmPAsnUIntDef czDL_GBR_PRB_usagespec =
{



 0,
 100UL
};
CmPAsnElmDef czDL_GBR_PRB_usage =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztDL_GBR_PRB_usage),
 &flagCz3M,
 0,
 (U8 *)(&czDL_GBR_PRB_usagespec),
 0L
};


CmPAsnUIntDef czDL_non_GBR_PRB_usagespec =
{



 0,
 100UL
};
CmPAsnElmDef czDL_non_GBR_PRB_usage =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztDL_non_GBR_PRB_usage),
 &flagCz3M,
 0,
 (U8 *)(&czDL_non_GBR_PRB_usagespec),
 0L
};


CmPAsnUIntDef czDL_Total_PRB_usagespec =
{



 0,
 100UL
};
CmPAsnElmDef czDL_Total_PRB_usage =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztDL_Total_PRB_usage),
 &flagCz3M,
 0,
 (U8 *)(&czDL_Total_PRB_usagespec),
 0L
};


CmPAsnUIntDef czEARFCNspec =
{



 0,
 65535
};
CmPAsnElmDef czEARFCN =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztEARFCN),
 &flagCz3M,
 0,
 (U8 *)(&czEARFCNspec),
 0L
};


CmPAsnUIntDef czEARFCNExtnspec =
{



 154550280,
 262143
};
CmPAsnElmDef czEARFCNExtn =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztEARFCNExtn),
 &flagCz3M,
 0,
 (U8 *)(&czEARFCNExtnspec),
 0L
};


CmPAsnTknEnum czTransmission_BandwidthLst[7] =
{
 6,
 CztTransmission_Bandwidthbw6Enum,
 CztTransmission_Bandwidthbw15Enum,
 CztTransmission_Bandwidthbw25Enum,
 CztTransmission_Bandwidthbw50Enum,
 CztTransmission_Bandwidthbw75Enum,
 CztTransmission_Bandwidthbw100Enum
};
CmPAsnEnumDef czTransmission_Bandwidthspec =
{



 czTransmission_BandwidthLst,
 0L
};
CmPAsnElmDef czTransmission_Bandwidth =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztTransmission_Bandwidth),
 &flagCz3M,
 0,
 (U8 *)(&czTransmission_Bandwidthspec),
 0L
};

 CmPAsnElmDef *cz_ExtnFDD_Info_ExtIEsClsInst[] =
{
 &czEARFCNExtn,
 &czEARFCNExtn
};
 U32 cz_ExtnFDD_Info_ExtIEsClsInstId[] =
{
 95,
 96
};
 CmPAsnClassInfo cz_ExtnFDD_Info_ExtIEsClsInfo =
{
 2,
 &cz_ExtnFDD_Info_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnFDD_Info_ExtIEsClsSpec =
{



 &cz_ExtnFDD_Info_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnFDD_Info_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnFDD_Info_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnFDD_Info_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnFDD_Info_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_FDD_Info_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnFDD_Info_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_FDD_Info_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_FDD_Info_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_FDD_Info_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_FDD_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_FDD_Info_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_FDD_Info_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_FDD_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_FDD_Info_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_FDD_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_FDD_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_FDD_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_FDD_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czFDD_InfoTkn[] =
{
 &czEARFCN,
 &czEARFCN,
 &czTransmission_Bandwidth,
 &czTransmission_Bandwidth,
 &czOptProtExtnCont_FDD_Info_ExtIEs,
  &czProtExtnField_FDD_Info_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czFDD_Infospec =
{



 1,
 0,
 0L,
 0L,
 &czFDD_InfoTkn[0],
 0
};
 CmPAsnElmDef czFDD_Info =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztFDD_Info),
 &flagCz3M,
 0,
 (U8 *)(&czFDD_Infospec),
 0L
};

CmPAsnTknEnum czSubframeAssignmentLst[8] =
{
 7,
 CztSubframeAssignmentsa0Enum,
 CztSubframeAssignmentsa1Enum,
 CztSubframeAssignmentsa2Enum,
 CztSubframeAssignmentsa3Enum,
 CztSubframeAssignmentsa4Enum,
 CztSubframeAssignmentsa5Enum,
 CztSubframeAssignmentsa6Enum
};
CmPAsnEnumDef czSubframeAssignmentspec =
{



 czSubframeAssignmentLst,
 0L
};
CmPAsnElmDef czSubframeAssignment =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztSubframeAssignment),
 &flagCz3M,
 0,
 (U8 *)(&czSubframeAssignmentspec),
 0L
};


CmPAsnTknEnum czSpecialSubframePatternsLst[10] =
{
 9,
 CztSpecialSubframePatternsssp0Enum,
 CztSpecialSubframePatternsssp1Enum,
 CztSpecialSubframePatternsssp2Enum,
 CztSpecialSubframePatternsssp3Enum,
 CztSpecialSubframePatternsssp4Enum,
 CztSpecialSubframePatternsssp5Enum,
 CztSpecialSubframePatternsssp6Enum,
 CztSpecialSubframePatternsssp7Enum,
 CztSpecialSubframePatternsssp8Enum
};
CmPAsnEnumDef czSpecialSubframePatternsspec =
{



 czSpecialSubframePatternsLst,
 0L
};
CmPAsnElmDef czSpecialSubframePatterns =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztSpecialSubframePatterns),
 &flagCz3M,
 0,
 (U8 *)(&czSpecialSubframePatternsspec),
 0L
};

 CmPAsnElmDef *cz_ExtnSpecialSubframe_Info_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnSpecialSubframe_Info_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnSpecialSubframe_Info_ExtIEsClsInfo =
{
 0,
 &cz_ExtnSpecialSubframe_Info_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnSpecialSubframe_Info_ExtIEsClsSpec =
{



 &cz_ExtnSpecialSubframe_Info_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnSpecialSubframe_Info_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnSpecialSubframe_Info_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnSpecialSubframe_Info_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnSpecialSubframe_Info_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_SpecialSubframe_Info_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnSpecialSubframe_Info_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_SpecialSubframe_Info_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_SpecialSubframe_Info_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_SpecialSubframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_SpecialSubframe_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_SpecialSubframe_Info_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_SpecialSubframe_Info_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_SpecialSubframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SpecialSubframe_Info_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_SpecialSubframe_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_SpecialSubframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SpecialSubframe_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_SpecialSubframe_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czSpecialSubframe_InfoTkn[] =
{
 &czSpecialSubframePatterns,
 &czCyclicPrefixDL,
 &czCyclicPrefixUL,
 &czOptProtExtnCont_SpecialSubframe_Info_ExtIEs,
  &czProtExtnField_SpecialSubframe_Info_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czSpecialSubframe_Infospec =
{



 1,
 0,
 0L,
 0L,
 &czSpecialSubframe_InfoTkn[0],
 0
};
 CmPAsnElmDef czSpecialSubframe_Info =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztSpecialSubframe_Info),
 &flagCz3M,
 0,
 (U8 *)(&czSpecialSubframe_Infospec),
 0L
};
 CmPAsnElmDef *cz_ExtnTDD_Info_ExtIEsClsInst[] =
{
 &czAdditionalSpecialSubframe_Info,
 &czEARFCNExtn
};
 U32 cz_ExtnTDD_Info_ExtIEsClsInstId[] =
{
 97,
 94
};
 CmPAsnClassInfo cz_ExtnTDD_Info_ExtIEsClsInfo =
{
 2,
 &cz_ExtnTDD_Info_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnTDD_Info_ExtIEsClsSpec =
{



 &cz_ExtnTDD_Info_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnTDD_Info_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnTDD_Info_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnTDD_Info_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnTDD_Info_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_TDD_Info_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnTDD_Info_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_TDD_Info_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_TDD_Info_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_TDD_Info_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_TDD_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_TDD_Info_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_TDD_Info_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_TDD_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TDD_Info_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_TDD_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_TDD_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TDD_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_TDD_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czTDD_InfoTkn[] =
{
 &czEARFCN,
 &czTransmission_Bandwidth,
 &czSubframeAssignment,
 &czSpecialSubframe_Info,
 &czOptProtExtnCont_TDD_Info_ExtIEs,
  &czProtExtnField_TDD_Info_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czTDD_Infospec =
{



 1,
 0,
 0L,
 0L,
 &czTDD_InfoTkn[0],
 0
};
 CmPAsnElmDef czTDD_Info =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztTDD_Info),
 &flagCz3M,
 0,
 (U8 *)(&czTDD_Infospec),
 0L
};
 CmPAsnElmDef *czEUTRA_Mode_InfoTkn[] =
{
 &czFDD_Info,
 &czTDD_Info,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czEUTRA_Mode_Infospec =
{



 2,
 0,
 &czEUTRA_Mode_InfoTkn[0]
};
CmPAsnElmDef czEUTRA_Mode_Info =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztEUTRA_Mode_Info),
 &flagCz3M,
 0L,
 (U8 *)(&czEUTRA_Mode_Infospec),
 0L
};
CmPAsnBitStrDef czENB_IDmacro_eNB_IDspec =
{



 20,
 20
};
CmPAsnElmDef czENB_IDmacro_eNB_ID =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztENB_IDmacro_eNB_ID),
 &flagCz3M,
 0,
 (U8 *) (&czENB_IDmacro_eNB_IDspec),
 0L
};
CmPAsnBitStrDef czENB_IDhome_eNB_IDspec =
{



 28,
 28
};
CmPAsnElmDef czENB_IDhome_eNB_ID =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztENB_IDhome_eNB_ID),
 &flagCz3M,
 0,
 (U8 *) (&czENB_IDhome_eNB_IDspec),
 0L
};
 CmPAsnElmDef *czENB_IDTkn[] =
{
 &czENB_IDmacro_eNB_ID,
 &czENB_IDhome_eNB_ID,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czENB_IDspec =
{



 2,
 0,
 &czENB_IDTkn[0]
};
CmPAsnElmDef czENB_ID =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztENB_ID),
 &flagCz3M,
 0L,
 (U8 *)(&czENB_IDspec),
 0L
};
CmPAsnBitStrDef czEncryptionAlgorithmsspec =
{



 16,
 16
};
CmPAsnElmDef czEncryptionAlgorithms =
{



 CM_PASN_TET_BITSTR,
 1,
 sizeof(CztEncryptionAlgorithms),
 &flagCz3M,
 0,
 (U8 *) (&czEncryptionAlgorithmsspec),
 0L
};
CmPAsnSetSeqOfDef czEPLMNsspec =
{



 1,
 15,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptEPLMNs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztEPLMNs),
 &flagCz3O,
 0,
 (U8 *) (&czEPLMNsspec),
 0L
};

CmPAsnUIntDef czE_RAB_IDspec =
{



 0,
 15UL
};
CmPAsnElmDef czE_RAB_ID =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztE_RAB_ID),
 &flagCz3M,
 0,
 (U8 *)(&czE_RAB_IDspec),
 0L
};


CmPAsnUIntDef czQCIspec =
{



 0,
 255UL
};
CmPAsnElmDef czQCI =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztQCI),
 &flagCz3M,
 0,
 (U8 *)(&czQCIspec),
 0L
};

 CmPAsnElmDef *cz_ExtnGBR_QosInform_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnGBR_QosInform_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnGBR_QosInform_ExtIEsClsInfo =
{
 0,
 &cz_ExtnGBR_QosInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnGBR_QosInform_ExtIEsClsSpec =
{



 &cz_ExtnGBR_QosInform_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnGBR_QosInform_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnGBR_QosInform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnGBR_QosInform_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnGBR_QosInform_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_GBR_QosInform_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnGBR_QosInform_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_GBR_QosInform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_GBR_QosInform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_GBR_QosInform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_GBR_QosInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_GBR_QosInform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_GBR_QosInform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_GBR_QosInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GBR_QosInform_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_GBR_QosInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_GBR_QosInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GBR_QosInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_GBR_QosInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czGBR_QosInformTkn[] =
{
 &czBitRate,
 &czBitRate,
 &czBitRate,
 &czBitRate,
 &czOptProtExtnCont_GBR_QosInform_ExtIEs,
  &czProtExtnField_GBR_QosInform_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czGBR_QosInformspec =
{



 1,
 0,
 0L,
 0L,
 &czGBR_QosInformTkn[0],
 0
};
 CmPAsnElmDef czGBR_QosInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztGBR_QosInform),
 &flagCz3M,
 0,
 (U8 *)(&czGBR_QosInformspec),
 0L
};
 CmPAsnElmDef czOptGBR_QosInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztGBR_QosInform),
 &flagCz3O,
 0,
 (U8 *)(&czGBR_QosInformspec),
 0L
};
 CmPAsnElmDef *cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsClsInfo =
{
 0,
 &cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsClsSpec =
{



 &cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czE_RAB_Lvl_QoS_ParamsTkn[] =
{
 &czQCI,
 &czAllocnAndRetentionPriority,
 &czOptGBR_QosInform,
 &czOptProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs,
  &czProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czE_RAB_Lvl_QoS_Paramsspec =
{



 2,
 0,
 0L,
 0L,
 &czE_RAB_Lvl_QoS_ParamsTkn[0],
 0
};
 CmPAsnElmDef czE_RAB_Lvl_QoS_Params =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztE_RAB_Lvl_QoS_Params),
 &flagCz3M,
 0,
 (U8 *)(&czE_RAB_Lvl_QoS_Paramsspec),
 0L
};
 CmPAsnElmDef *cz_ExtnE_RAB_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnE_RAB_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnE_RAB_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnE_RAB_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnE_RAB_Item_ExtIEsClsSpec =
{



 &cz_ExtnE_RAB_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnE_RAB_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnE_RAB_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnE_RAB_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnE_RAB_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_E_RAB_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnE_RAB_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_E_RAB_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_E_RAB_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_E_RAB_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_E_RAB_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_E_RAB_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_E_RAB_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_E_RAB_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RAB_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_E_RAB_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_E_RAB_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RAB_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_E_RAB_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czE_RAB_ItemTkn[] =
{
 &czE_RAB_ID,
 &czCause,
 &czOptProtExtnCont_E_RAB_Item_ExtIEs,
  &czProtExtnField_E_RAB_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czE_RAB_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czE_RAB_ItemTkn[0],
 0
};
 CmPAsnElmDef czE_RAB_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztE_RAB_Item),
 &flagCz3M,
 0,
 (U8 *)(&czE_RAB_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueE_RAB_ItemIEsClsInst[] =
{
 &czE_RAB_Item
};
 U32 cz_ValueE_RAB_ItemIEsClsInstId[] =
{
 2
};
 CmPAsnClassInfo cz_ValueE_RAB_ItemIEsClsInfo =
{
 1,
 &cz_ValueE_RAB_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueE_RAB_ItemIEsClsSpec =
{



 &cz_ValueE_RAB_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueE_RAB_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueE_RAB_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueE_RAB_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueE_RAB_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_E_RAB_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueE_RAB_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_E_RAB_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_E_RAB_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_E_RAB_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_E_RAB_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_E_RAB_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czE_RAB_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czE_RAB_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztE_RAB_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czE_RAB_Lstspec),
 0L
};
CmPAsnOctStrDef czEUTRANTraceIDspec =
{



 8,
 8
};
CmPAsnElmDef czEUTRANTraceID =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(CztEUTRANTraceID),
 &flagCz3M,
 0,
 (U8 *) (&czEUTRANTraceIDspec),
 0L
};

CmPAsnTknEnum czEventTypLst[2] =
{
 1,
 CztEventTypchange_of_serving_cellEnum
};
CmPAsnEnumDef czEventTypspec =
{



 czEventTypLst,
 0L
};
CmPAsnElmDef czEventTyp =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztEventTyp),
 &flagCz3M,
 0,
 (U8 *)(&czEventTypspec),
 0L
};


CmPAsnTknEnum czForbiddenInterRATsExtLst[3] =
{
 2,
 CztForbiddenInterRATsgeranandutranEnum,
 CztForbiddenInterRATscdma2000andutranEnum
};
CmPAsnTknEnum czForbiddenInterRATsLst[5] =
{
 4,
 CztForbiddenInterRATsallEnum,
 CztForbiddenInterRATsgeranEnum,
 CztForbiddenInterRATsutranEnum,
 CztForbiddenInterRATscdma2000Enum
};
CmPAsnEnumDef czForbiddenInterRATsspec =
{



 czForbiddenInterRATsLst,
 czForbiddenInterRATsExtLst
};
CmPAsnElmDef czOptForbiddenInterRATs =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztForbiddenInterRATs),
 &flagCz3O,
 0,
 (U8 *)(&czForbiddenInterRATsspec),
 0L
};

CmPAsnSetSeqOfDef czForbiddenTACsspec =
{



 1,
 4096,
 3*sizeof(U32)
};
 CmPAsnElmDef czForbiddenTACs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztForbiddenTACs),
 &flagCz3M,
 0,
 (U8 *) (&czForbiddenTACsspec),
 0L
};
 CmPAsnElmDef *cz_ExtnForbiddenTAs_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnForbiddenTAs_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnForbiddenTAs_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnForbiddenTAs_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnForbiddenTAs_Item_ExtIEsClsSpec =
{



 &cz_ExtnForbiddenTAs_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnForbiddenTAs_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnForbiddenTAs_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnForbiddenTAs_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnForbiddenTAs_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_ForbiddenTAs_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnForbiddenTAs_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_ForbiddenTAs_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_ForbiddenTAs_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_ForbiddenTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_ForbiddenTAs_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_ForbiddenTAs_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_ForbiddenTAs_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_ForbiddenTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ForbiddenTAs_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_ForbiddenTAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_ForbiddenTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ForbiddenTAs_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_ForbiddenTAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czForbiddenTAs_ItemTkn[] =
{
 &czPLMN_Identity,
 &czForbiddenTACs,
  &czTAC,
  &czConstTerm,
 &czOptProtExtnCont_ForbiddenTAs_Item_ExtIEs,
  &czProtExtnField_ForbiddenTAs_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czForbiddenTAs_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czForbiddenTAs_ItemTkn[0],
 0
};
 CmPAsnElmDef czForbiddenTAs_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztForbiddenTAs_Item),
 &flagCz3M,
 0,
 (U8 *)(&czForbiddenTAs_Itemspec),
 0L
};
CmPAsnSetSeqOfDef czForbiddenTAsspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptForbiddenTAs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztForbiddenTAs),
 &flagCz3O,
 0,
 (U8 *) (&czForbiddenTAsspec),
 0L
};
CmPAsnOctStrDef czLACspec =
{



 2,
 2
};
CmPAsnElmDef czLAC =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(CztLAC),
 &flagCz3M,
 0,
 (U8 *) (&czLACspec),
 0L
};
CmPAsnSetSeqOfDef czForbiddenLACsspec =
{



 1,
 4096,
 3*sizeof(U32)
};
 CmPAsnElmDef czForbiddenLACs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztForbiddenLACs),
 &flagCz3M,
 0,
 (U8 *) (&czForbiddenLACsspec),
 0L
};
 CmPAsnElmDef *cz_ExtnForbiddenLAs_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnForbiddenLAs_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnForbiddenLAs_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnForbiddenLAs_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnForbiddenLAs_Item_ExtIEsClsSpec =
{



 &cz_ExtnForbiddenLAs_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnForbiddenLAs_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnForbiddenLAs_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnForbiddenLAs_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnForbiddenLAs_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_ForbiddenLAs_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnForbiddenLAs_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_ForbiddenLAs_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_ForbiddenLAs_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_ForbiddenLAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_ForbiddenLAs_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_ForbiddenLAs_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_ForbiddenLAs_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_ForbiddenLAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ForbiddenLAs_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_ForbiddenLAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_ForbiddenLAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ForbiddenLAs_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_ForbiddenLAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czForbiddenLAs_ItemTkn[] =
{
 &czPLMN_Identity,
 &czForbiddenLACs,
  &czLAC,
  &czConstTerm,
 &czOptProtExtnCont_ForbiddenLAs_Item_ExtIEs,
  &czProtExtnField_ForbiddenLAs_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czForbiddenLAs_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czForbiddenLAs_ItemTkn[0],
 0
};
 CmPAsnElmDef czForbiddenLAs_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztForbiddenLAs_Item),
 &flagCz3M,
 0,
 (U8 *)(&czForbiddenLAs_Itemspec),
 0L
};
CmPAsnSetSeqOfDef czForbiddenLAsspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptForbiddenLAs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztForbiddenLAs),
 &flagCz3O,
 0,
 (U8 *) (&czForbiddenLAsspec),
 0L
};
CmPAsnBitStrDef czFourframesspec =
{



 24,
 24
};
CmPAsnElmDef czFourframes =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztFourframes),
 &flagCz3M,
 0,
 (U8 *) (&czFourframesspec),
 0L
};

CmPAsnUIntDef czFreqBandIndicatorspec =
{



 1,
 256UL
};
CmPAsnElmDef czFreqBandIndicator =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztFreqBandIndicator),
 &flagCz3M,
 0,
 (U8 *)(&czFreqBandIndicatorspec),
 0L
};

 CmPAsnElmDef *cz_ExtnGlobalENB_ID_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnGlobalENB_ID_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnGlobalENB_ID_ExtIEsClsInfo =
{
 0,
 &cz_ExtnGlobalENB_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnGlobalENB_ID_ExtIEsClsSpec =
{



 &cz_ExtnGlobalENB_ID_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnGlobalENB_ID_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnGlobalENB_ID_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnGlobalENB_ID_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnGlobalENB_ID_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_GlobalENB_ID_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnGlobalENB_ID_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_GlobalENB_ID_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_GlobalENB_ID_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_GlobalENB_ID_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_GlobalENB_ID_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_GlobalENB_ID_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_GlobalENB_ID_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_GlobalENB_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GlobalENB_ID_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_GlobalENB_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_GlobalENB_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GlobalENB_ID_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_GlobalENB_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czGlobalENB_IDTkn[] =
{
 &czPLMN_Identity,
 &czENB_ID,
 &czOptProtExtnCont_GlobalENB_ID_ExtIEs,
  &czProtExtnField_GlobalENB_ID_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czGlobalENB_IDspec =
{



 1,
 0,
 0L,
 0L,
 &czGlobalENB_IDTkn[0],
 0
};
 CmPAsnElmDef czGlobalENB_ID =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztGlobalENB_ID),
 &flagCz3M,
 0,
 (U8 *)(&czGlobalENB_IDspec),
 0L
};
CmPAsnBitStrDef czTportLyrAddrspec =
{



 1,
 160
};
CmPAsnElmDef czTportLyrAddr =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(CztTportLyrAddr),
 &flagCz3M,
 0,
 (U8 *) (&czTportLyrAddrspec),
 0L
};
CmPAsnOctStrDef czGTP_TEIspec =
{



 4,
 4
};
CmPAsnElmDef czGTP_TEI =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(CztGTP_TEI),
 &flagCz3M,
 0,
 (U8 *) (&czGTP_TEIspec),
 0L
};
 CmPAsnElmDef *cz_ExtnGTPtunnelEndpoint_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnGTPtunnelEndpoint_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnGTPtunnelEndpoint_ExtIEsClsInfo =
{
 0,
 &cz_ExtnGTPtunnelEndpoint_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnGTPtunnelEndpoint_ExtIEsClsSpec =
{



 &cz_ExtnGTPtunnelEndpoint_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnGTPtunnelEndpoint_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnGTPtunnelEndpoint_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnGTPtunnelEndpoint_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnGTPtunnelEndpoint_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_GTPtunnelEndpoint_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnGTPtunnelEndpoint_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_GTPtunnelEndpoint_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_GTPtunnelEndpoint_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_GTPtunnelEndpoint_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_GTPtunnelEndpoint_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_GTPtunnelEndpoint_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_GTPtunnelEndpoint_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_GTPtunnelEndpoint_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GTPtunnelEndpoint_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_GTPtunnelEndpoint_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_GTPtunnelEndpoint_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GTPtunnelEndpoint_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_GTPtunnelEndpoint_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czGTPtunnelEndpointTkn[] =
{
 &czTportLyrAddr,
 &czGTP_TEI,
 &czOptProtExtnCont_GTPtunnelEndpoint_ExtIEs,
  &czProtExtnField_GTPtunnelEndpoint_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czGTPtunnelEndpointspec =
{



 1,
 0,
 0L,
 0L,
 &czGTPtunnelEndpointTkn[0],
 0
};
 CmPAsnElmDef czGTPtunnelEndpoint =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztGTPtunnelEndpoint),
 &flagCz3M,
 0,
 (U8 *)(&czGTPtunnelEndpointspec),
 0L
};
 CmPAsnElmDef czOptGTPtunnelEndpoint =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztGTPtunnelEndpoint),
 &flagCz3O,
 0,
 (U8 *)(&czGTPtunnelEndpointspec),
 0L
};
CmPAsnOctStrDef czMME_Group_IDspec =
{



 2,
 2
};
CmPAsnElmDef czMME_Group_ID =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(CztMME_Group_ID),
 &flagCz3M,
 0,
 (U8 *) (&czMME_Group_IDspec),
 0L
};
 CmPAsnElmDef *cz_ExtnGU_Group_ID_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnGU_Group_ID_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnGU_Group_ID_ExtIEsClsInfo =
{
 0,
 &cz_ExtnGU_Group_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnGU_Group_ID_ExtIEsClsSpec =
{



 &cz_ExtnGU_Group_ID_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnGU_Group_ID_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnGU_Group_ID_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnGU_Group_ID_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnGU_Group_ID_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_GU_Group_ID_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnGU_Group_ID_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_GU_Group_ID_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_GU_Group_ID_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_GU_Group_ID_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_GU_Group_ID_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_GU_Group_ID_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_GU_Group_ID_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_GU_Group_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GU_Group_ID_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_GU_Group_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_GU_Group_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GU_Group_ID_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_GU_Group_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czGU_Group_IDTkn[] =
{
 &czPLMN_Identity,
 &czMME_Group_ID,
 &czOptProtExtnCont_GU_Group_ID_ExtIEs,
  &czProtExtnField_GU_Group_ID_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czGU_Group_IDspec =
{



 1,
 0,
 0L,
 0L,
 &czGU_Group_IDTkn[0],
 0
};
 CmPAsnElmDef czGU_Group_ID =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztGU_Group_ID),
 &flagCz3M,
 0,
 (U8 *)(&czGU_Group_IDspec),
 0L
};
CmPAsnSetSeqOfDef czGUGroupIDLstspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef czGUGroupIDLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztGUGroupIDLst),
 &flagCz3M,
 0,
 (U8 *) (&czGUGroupIDLstspec),
 0L
};
CmPAsnOctStrDef czMME_Codespec =
{



 1,
 1
};
CmPAsnElmDef czMME_Code =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(CztMME_Code),
 &flagCz3M,
 0,
 (U8 *) (&czMME_Codespec),
 0L
};
 CmPAsnElmDef *cz_ExtnGUMMEI_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnGUMMEI_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnGUMMEI_ExtIEsClsInfo =
{
 0,
 &cz_ExtnGUMMEI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnGUMMEI_ExtIEsClsSpec =
{



 &cz_ExtnGUMMEI_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnGUMMEI_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnGUMMEI_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnGUMMEI_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnGUMMEI_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_GUMMEI_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnGUMMEI_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_GUMMEI_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_GUMMEI_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_GUMMEI_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_GUMMEI_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_GUMMEI_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_GUMMEI_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_GUMMEI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GUMMEI_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_GUMMEI_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_GUMMEI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_GUMMEI_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_GUMMEI_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czGUMMEITkn[] =
{
 &czGU_Group_ID,
 &czMME_Code,
 &czOptProtExtnCont_GUMMEI_ExtIEs,
  &czProtExtnField_GUMMEI_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czGUMMEIspec =
{



 1,
 0,
 0L,
 0L,
 &czGUMMEITkn[0],
 0
};
 CmPAsnElmDef czGUMMEI =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztGUMMEI),
 &flagCz3M,
 0,
 (U8 *)(&czGUMMEIspec),
 0L
};

CmPAsnTknEnum czHovrReportTypExtLst[2] =
{
 1,
 CztHovrReportTypinterRATpingpongEnum
};
CmPAsnTknEnum czHovrReportTypLst[3] =
{
 2,
 CztHovrReportTyphoTooEarlyEnum,
 CztHovrReportTyphoToWrongCellEnum
};
CmPAsnEnumDef czHovrReportTypspec =
{



 czHovrReportTypLst,
 czHovrReportTypExtLst
};
CmPAsnElmDef czHovrReportTyp =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztHovrReportTyp),
 &flagCz3M,
 0,
 (U8 *)(&czHovrReportTypspec),
 0L
};

 CmPAsnElmDef *cz_ExtnHovrRestrnLst_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnHovrRestrnLst_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnHovrRestrnLst_ExtIEsClsInfo =
{
 0,
 &cz_ExtnHovrRestrnLst_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnHovrRestrnLst_ExtIEsClsSpec =
{



 &cz_ExtnHovrRestrnLst_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnHovrRestrnLst_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnHovrRestrnLst_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnHovrRestrnLst_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnHovrRestrnLst_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_HovrRestrnLst_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnHovrRestrnLst_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_HovrRestrnLst_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_HovrRestrnLst_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_HovrRestrnLst_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_HovrRestrnLst_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_HovrRestrnLst_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_HovrRestrnLst_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_HovrRestrnLst_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_HovrRestrnLst_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_HovrRestrnLst_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_HovrRestrnLst_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_HovrRestrnLst_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_HovrRestrnLst_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czHovrRestrnLstTkn[] =
{
 &czPLMN_Identity,
 &czOptEPLMNs,
  &czPLMN_Identity,
  &czConstTerm,
 &czOptForbiddenTAs,
  &czForbiddenTAs_Item,
  &czConstTerm,
 &czOptForbiddenLAs,
  &czForbiddenLAs_Item,
  &czConstTerm,
 &czOptForbiddenInterRATs,
 &czOptProtExtnCont_HovrRestrnLst_ExtIEs,
  &czProtExtnField_HovrRestrnLst_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czHovrRestrnLstspec =
{



 5,
 0,
 0L,
 0L,
 &czHovrRestrnLstTkn[0],
 0
};
 CmPAsnElmDef czHovrRestrnLst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHovrRestrnLst),
 &flagCz3M,
 0,
 (U8 *)(&czHovrRestrnLstspec),
 0L
};
 CmPAsnElmDef czOptHovrRestrnLst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHovrRestrnLst),
 &flagCz3O,
 0,
 (U8 *)(&czHovrRestrnLstspec),
 0L
};

CmPAsnTknEnum czLoadIndicatorLst[5] =
{
 4,
 CztLoadIndicatorlowLoadEnum,
 CztLoadIndicatormediumLoadEnum,
 CztLoadIndicatorhighLoadEnum,
 CztLoadIndicatoroverLoadEnum
};
CmPAsnEnumDef czLoadIndicatorspec =
{



 czLoadIndicatorLst,
 0L
};
CmPAsnElmDef czLoadIndicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztLoadIndicator),
 &flagCz3M,
 0,
 (U8 *)(&czLoadIndicatorspec),
 0L
};

 CmPAsnElmDef *cz_ExtnHWLoadIndicator_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnHWLoadIndicator_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnHWLoadIndicator_ExtIEsClsInfo =
{
 0,
 &cz_ExtnHWLoadIndicator_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnHWLoadIndicator_ExtIEsClsSpec =
{



 &cz_ExtnHWLoadIndicator_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnHWLoadIndicator_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnHWLoadIndicator_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnHWLoadIndicator_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnHWLoadIndicator_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_HWLoadIndicator_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnHWLoadIndicator_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_HWLoadIndicator_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_HWLoadIndicator_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_HWLoadIndicator_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_HWLoadIndicator_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_HWLoadIndicator_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_HWLoadIndicator_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_HWLoadIndicator_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_HWLoadIndicator_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_HWLoadIndicator_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_HWLoadIndicator_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_HWLoadIndicator_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_HWLoadIndicator_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czHWLoadIndicatorTkn[] =
{
 &czLoadIndicator,
 &czLoadIndicator,
 &czOptProtExtnCont_HWLoadIndicator_ExtIEs,
  &czProtExtnField_HWLoadIndicator_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czHWLoadIndicatorspec =
{



 1,
 0,
 0L,
 0L,
 &czHWLoadIndicatorTkn[0],
 0
};
 CmPAsnElmDef czHWLoadIndicator =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHWLoadIndicator),
 &flagCz3M,
 0,
 (U8 *)(&czHWLoadIndicatorspec),
 0L
};
 CmPAsnElmDef czOptHWLoadIndicator =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHWLoadIndicator),
 &flagCz3O,
 0,
 (U8 *)(&czHWLoadIndicatorspec),
 0L
};

CmPAsnTknEnum czInvokeIndLst[2] =
{
 1,
 CztInvokeIndabs_informationEnum
};
CmPAsnEnumDef czInvokeIndspec =
{



 czInvokeIndLst,
 0L
};
CmPAsnElmDef czInvokeInd =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztInvokeInd),
 &flagCz3M,
 0,
 (U8 *)(&czInvokeIndspec),
 0L
};

CmPAsnBitStrDef czIntegrityProtectionAlgorithmsspec =
{



 16,
 16
};
CmPAsnElmDef czIntegrityProtectionAlgorithms =
{



 CM_PASN_TET_BITSTR,
 1,
 sizeof(CztIntegrityProtectionAlgorithms),
 &flagCz3M,
 0,
 (U8 *) (&czIntegrityProtectionAlgorithmsspec),
 0L
};
CmPAsnBitStrDef czIntfsToTracespec =
{



 8,
 8
};
CmPAsnElmDef czIntfsToTrace =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztIntfsToTrace),
 &flagCz3M,
 0,
 (U8 *) (&czIntfsToTracespec),
 0L
};

CmPAsnUIntDef czTime_UE_StayedInCellspec =
{



 0,
 4095UL
};
CmPAsnElmDef czTime_UE_StayedInCell =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztTime_UE_StayedInCell),
 &flagCz3M,
 0,
 (U8 *)(&czTime_UE_StayedInCellspec),
 0L
};


CmPAsnUIntDef czTime_UE_StayedInCell_EnhancedGranularityspec =
{



 0,
 40950UL
};
CmPAsnElmDef czTime_UE_StayedInCell_EnhancedGranularity =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztTime_UE_StayedInCell_EnhancedGranularity),
 &flagCz3M,
 0,
 (U8 *)(&czTime_UE_StayedInCell_EnhancedGranularityspec),
 0L
};

 CmPAsnElmDef *cz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInst[] =
{
 &czTime_UE_StayedInCell_EnhancedGranularity,
 &czCause
};
 U32 cz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInstId[] =
{
 77,
 80
};
 CmPAsnClassInfo cz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInfo =
{
 2,
 &cz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsSpec =
{



 &cz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnLastVisitedEUTRANCellInform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_LastVisitedEUTRANCellInform_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnLastVisitedEUTRANCellInform_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_LastVisitedEUTRANCellInform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_LastVisitedEUTRANCellInform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_LastVisitedEUTRANCellInform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_LastVisitedEUTRANCellInform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czLastVisitedEUTRANCellInformTkn[] =
{
 &czECGI,
 &czCellTyp,
 &czTime_UE_StayedInCell,
 &czOptProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs,
  &czProtExtnField_LastVisitedEUTRANCellInform_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czLastVisitedEUTRANCellInformspec =
{



 1,
 0,
 0L,
 0L,
 &czLastVisitedEUTRANCellInformTkn[0],
 0
};
 CmPAsnElmDef czLastVisitedEUTRANCellInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztLastVisitedEUTRANCellInform),
 &flagCz3M,
 0,
 (U8 *)(&czLastVisitedEUTRANCellInformspec),
 0L
};
CmPAsnOctStrDef czLastVisitedUTRANCellInformspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef czLastVisitedUTRANCellInform =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(CztLastVisitedUTRANCellInform),
 &flagCz3M,
 0,
 (U8 *) (&czLastVisitedUTRANCellInformspec),
 0L
};
 CmPAsnElmDef *czLastVisitedGERANCellInformTkn[] =
{
 &czNull,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czLastVisitedGERANCellInformspec =
{



 1,
 0,
 &czLastVisitedGERANCellInformTkn[0]
};
CmPAsnElmDef czLastVisitedGERANCellInform =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztLastVisitedGERANCellInform),
 &flagCz3M,
 0L,
 (U8 *)(&czLastVisitedGERANCellInformspec),
 0L
};
 CmPAsnElmDef *czLastVisitedCell_ItemTkn[] =
{
 &czLastVisitedEUTRANCellInform,
 &czLastVisitedUTRANCellInform,
 &czLastVisitedGERANCellInform,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czLastVisitedCell_Itemspec =
{



 3,
 0,
 &czLastVisitedCell_ItemTkn[0]
};
CmPAsnElmDef czLastVisitedCell_Item =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztLastVisitedCell_Item),
 &flagCz3M,
 0L,
 (U8 *)(&czLastVisitedCell_Itemspec),
 0L
};

CmPAsnTknEnum czLinks_to_logLst[4] =
{
 3,
 CztLinks_to_loguplinkEnum,
 CztLinks_to_logdownlinkEnum,
 CztLinks_to_logboth_uplink_and_downlinkEnum
};
CmPAsnEnumDef czLinks_to_logspec =
{



 czLinks_to_logLst,
 0L
};
CmPAsnElmDef czLinks_to_log =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztLinks_to_log),
 &flagCz3M,
 0,
 (U8 *)(&czLinks_to_logspec),
 0L
};


CmPAsnTknEnum czReportAreaLst[2] =
{
 1,
 CztReportAreaecgiEnum
};
CmPAsnEnumDef czReportAreaspec =
{



 czReportAreaLst,
 0L
};
CmPAsnElmDef czReportArea =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztReportArea),
 &flagCz3M,
 0,
 (U8 *)(&czReportAreaspec),
 0L
};

 CmPAsnElmDef *cz_ExtnLocRprtngInform_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnLocRprtngInform_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnLocRprtngInform_ExtIEsClsInfo =
{
 0,
 &cz_ExtnLocRprtngInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnLocRprtngInform_ExtIEsClsSpec =
{



 &cz_ExtnLocRprtngInform_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnLocRprtngInform_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnLocRprtngInform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnLocRprtngInform_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnLocRprtngInform_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_LocRprtngInform_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnLocRprtngInform_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_LocRprtngInform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_LocRprtngInform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_LocRprtngInform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_LocRprtngInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_LocRprtngInform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_LocRprtngInform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_LocRprtngInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_LocRprtngInform_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_LocRprtngInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_LocRprtngInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_LocRprtngInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_LocRprtngInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czLocRprtngInformTkn[] =
{
 &czEventTyp,
 &czReportArea,
 &czOptProtExtnCont_LocRprtngInform_ExtIEs,
  &czProtExtnField_LocRprtngInform_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czLocRprtngInformspec =
{



 1,
 0,
 0L,
 0L,
 &czLocRprtngInformTkn[0],
 0
};
 CmPAsnElmDef czLocRprtngInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztLocRprtngInform),
 &flagCz3M,
 0,
 (U8 *)(&czLocRprtngInformspec),
 0L
};
 CmPAsnElmDef czOptLocRprtngInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztLocRprtngInform),
 &flagCz3O,
 0,
 (U8 *)(&czLocRprtngInformspec),
 0L
};

CmPAsnTknEnum czM3periodLst[4] =
{
 3,
 CztM3periodms100Enum,
 CztM3periodms1000Enum,
 CztM3periodms10000Enum
};
CmPAsnEnumDef czM3periodspec =
{



 czM3periodLst,
 0L
};
CmPAsnElmDef czM3period =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztM3period),
 &flagCz3M,
 0,
 (U8 *)(&czM3periodspec),
 0L
};

 CmPAsnElmDef *cz_ExtnM3Config_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnM3Config_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnM3Config_ExtIEsClsInfo =
{
 0,
 &cz_ExtnM3Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnM3Config_ExtIEsClsSpec =
{



 &cz_ExtnM3Config_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnM3Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnM3Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnM3Config_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnM3Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_M3Config_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnM3Config_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_M3Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_M3Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_M3Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_M3Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_M3Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_M3Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_M3Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M3Config_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_M3Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_M3Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M3Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_M3Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czM3ConfigTkn[] =
{
 &czM3period,
 &czOptProtExtnCont_M3Config_ExtIEs,
  &czProtExtnField_M3Config_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czM3Configspec =
{



 1,
 0,
 0L,
 0L,
 &czM3ConfigTkn[0],
 0
};
 CmPAsnElmDef czM3Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztM3Config),
 &flagCz3M,
 0,
 (U8 *)(&czM3Configspec),
 0L
};

CmPAsnTknEnum czM4periodLst[6] =
{
 5,
 CztM4periodms1024Enum,
 CztM4periodms2048Enum,
 CztM4periodms5120Enum,
 CztM4periodms10240Enum,
 CztM4periodmin1Enum
};
CmPAsnEnumDef czM4periodspec =
{



 czM4periodLst,
 0L
};
CmPAsnElmDef czM4period =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztM4period),
 &flagCz3M,
 0,
 (U8 *)(&czM4periodspec),
 0L
};

 CmPAsnElmDef *cz_ExtnM4Config_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnM4Config_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnM4Config_ExtIEsClsInfo =
{
 0,
 &cz_ExtnM4Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnM4Config_ExtIEsClsSpec =
{



 &cz_ExtnM4Config_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnM4Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnM4Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnM4Config_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnM4Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_M4Config_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnM4Config_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_M4Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_M4Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_M4Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_M4Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_M4Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_M4Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_M4Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M4Config_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_M4Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_M4Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M4Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_M4Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czM4ConfigTkn[] =
{
 &czM4period,
 &czLinks_to_log,
 &czOptProtExtnCont_M4Config_ExtIEs,
  &czProtExtnField_M4Config_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czM4Configspec =
{



 1,
 0,
 0L,
 0L,
 &czM4ConfigTkn[0],
 0
};
 CmPAsnElmDef czM4Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztM4Config),
 &flagCz3M,
 0,
 (U8 *)(&czM4Configspec),
 0L
};

CmPAsnTknEnum czM5periodLst[6] =
{
 5,
 CztM5periodms1024Enum,
 CztM5periodms2048Enum,
 CztM5periodms5120Enum,
 CztM5periodms10240Enum,
 CztM5periodmin1Enum
};
CmPAsnEnumDef czM5periodspec =
{



 czM5periodLst,
 0L
};
CmPAsnElmDef czM5period =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztM5period),
 &flagCz3M,
 0,
 (U8 *)(&czM5periodspec),
 0L
};

 CmPAsnElmDef *cz_ExtnM5Config_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnM5Config_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnM5Config_ExtIEsClsInfo =
{
 0,
 &cz_ExtnM5Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnM5Config_ExtIEsClsSpec =
{



 &cz_ExtnM5Config_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnM5Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnM5Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnM5Config_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnM5Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_M5Config_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnM5Config_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_M5Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_M5Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_M5Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_M5Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_M5Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_M5Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_M5Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M5Config_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_M5Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_M5Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M5Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_M5Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czM5ConfigTkn[] =
{
 &czM5period,
 &czLinks_to_log,
 &czOptProtExtnCont_M5Config_ExtIEs,
  &czProtExtnField_M5Config_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czM5Configspec =
{



 1,
 0,
 0L,
 0L,
 &czM5ConfigTkn[0],
 0
};
 CmPAsnElmDef czM5Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztM5Config),
 &flagCz3M,
 0,
 (U8 *)(&czM5Configspec),
 0L
};

CmPAsnTknEnum czMDT_ActvnLst[3] =
{
 2,
 CztMDT_Actvnimmediate_MDT_onlyEnum,
 CztMDT_Actvnimmediate_MDT_and_TraceEnum
};
CmPAsnEnumDef czMDT_Actvnspec =
{



 czMDT_ActvnLst,
 0L
};
CmPAsnElmDef czMDT_Actvn =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztMDT_Actvn),
 &flagCz3M,
 0,
 (U8 *)(&czMDT_Actvnspec),
 0L
};

CmPAsnBitStrDef czMeasurementsToActivatespec =
{



 8,
 8
};
CmPAsnElmDef czMeasurementsToActivate =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztMeasurementsToActivate),
 &flagCz3M,
 0,
 (U8 *) (&czMeasurementsToActivatespec),
 0L
};

CmPAsnTknEnum czM1RprtngTriggerExtLst[2] =
{
 1,
 CztM1RprtngTriggera2eventtriggered_periodicEnum
};
CmPAsnTknEnum czM1RprtngTriggerLst[3] =
{
 2,
 CztM1RprtngTriggerperiodicEnum,
 CztM1RprtngTriggera2eventtriggeredEnum
};
CmPAsnEnumDef czM1RprtngTriggerspec =
{



 czM1RprtngTriggerLst,
 czM1RprtngTriggerExtLst
};
CmPAsnElmDef czM1RprtngTrigger =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztM1RprtngTrigger),
 &flagCz3M,
 0,
 (U8 *)(&czM1RprtngTriggerspec),
 0L
};


CmPAsnUIntDef czThreshold_RSRPspec =
{



 0,
 97UL
};
CmPAsnElmDef czThreshold_RSRP =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztThreshold_RSRP),
 &flagCz3M,
 0,
 (U8 *)(&czThreshold_RSRPspec),
 0L
};


CmPAsnUIntDef czThreshold_RSRQspec =
{



 0,
 34UL
};
CmPAsnElmDef czThreshold_RSRQ =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztThreshold_RSRQ),
 &flagCz3M,
 0,
 (U8 *)(&czThreshold_RSRQspec),
 0L
};

 CmPAsnElmDef *czMeasurementThresholdA2Tkn[] =
{
 &czThreshold_RSRP,
 &czThreshold_RSRQ,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czMeasurementThresholdA2spec =
{



 2,
 0,
 &czMeasurementThresholdA2Tkn[0]
};
CmPAsnElmDef czMeasurementThresholdA2 =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztMeasurementThresholdA2),
 &flagCz3M,
 0L,
 (U8 *)(&czMeasurementThresholdA2spec),
 0L
};
 CmPAsnElmDef *cz_ExtnM1ThresholdEventA2_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnM1ThresholdEventA2_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnM1ThresholdEventA2_ExtIEsClsInfo =
{
 0,
 &cz_ExtnM1ThresholdEventA2_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnM1ThresholdEventA2_ExtIEsClsSpec =
{



 &cz_ExtnM1ThresholdEventA2_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnM1ThresholdEventA2_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnM1ThresholdEventA2_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnM1ThresholdEventA2_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnM1ThresholdEventA2_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_M1ThresholdEventA2_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnM1ThresholdEventA2_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_M1ThresholdEventA2_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_M1ThresholdEventA2_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_M1ThresholdEventA2_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_M1ThresholdEventA2_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_M1ThresholdEventA2_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_M1ThresholdEventA2_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_M1ThresholdEventA2_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M1ThresholdEventA2_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_M1ThresholdEventA2_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_M1ThresholdEventA2_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M1ThresholdEventA2_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_M1ThresholdEventA2_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czM1ThresholdEventA2Tkn[] =
{
 &czMeasurementThresholdA2,
 &czOptProtExtnCont_M1ThresholdEventA2_ExtIEs,
  &czProtExtnField_M1ThresholdEventA2_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czM1ThresholdEventA2spec =
{



 1,
 0,
 0L,
 0L,
 &czM1ThresholdEventA2Tkn[0],
 0
};
 CmPAsnElmDef czM1ThresholdEventA2 =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztM1ThresholdEventA2),
 &flagCz3M,
 0,
 (U8 *)(&czM1ThresholdEventA2spec),
 0L
};
 CmPAsnElmDef czOptM1ThresholdEventA2 =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztM1ThresholdEventA2),
 &flagCz3O,
 0,
 (U8 *)(&czM1ThresholdEventA2spec),
 0L
};

CmPAsnTknEnum czReportIntervalMDTLst[14] =
{
 13,
 CztReportIntervalMDTms120Enum,
 CztReportIntervalMDTms240Enum,
 CztReportIntervalMDTms480Enum,
 CztReportIntervalMDTms640Enum,
 CztReportIntervalMDTms1024Enum,
 CztReportIntervalMDTms2048Enum,
 CztReportIntervalMDTms5120Enum,
 CztReportIntervalMDTms10240Enum,
 CztReportIntervalMDTmin1Enum,
 CztReportIntervalMDTmin6Enum,
 CztReportIntervalMDTmin12Enum,
 CztReportIntervalMDTmin30Enum,
 CztReportIntervalMDTmin60Enum
};
CmPAsnEnumDef czReportIntervalMDTspec =
{



 czReportIntervalMDTLst,
 0L
};
CmPAsnElmDef czReportIntervalMDT =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztReportIntervalMDT),
 &flagCz3M,
 0,
 (U8 *)(&czReportIntervalMDTspec),
 0L
};


CmPAsnTknEnum czReportAmountMDTLst[9] =
{
 8,
 CztReportAmountMDTr1Enum,
 CztReportAmountMDTr2Enum,
 CztReportAmountMDTr4Enum,
 CztReportAmountMDTr8Enum,
 CztReportAmountMDTr16Enum,
 CztReportAmountMDTr32Enum,
 CztReportAmountMDTr64Enum,
 CztReportAmountMDTrinfinityEnum
};
CmPAsnEnumDef czReportAmountMDTspec =
{



 czReportAmountMDTLst,
 0L
};
CmPAsnElmDef czReportAmountMDT =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(CztReportAmountMDT),
 &flagCz3M,
 0,
 (U8 *)(&czReportAmountMDTspec),
 0L
};

 CmPAsnElmDef *cz_ExtnM1PeriodicRprtng_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnM1PeriodicRprtng_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnM1PeriodicRprtng_ExtIEsClsInfo =
{
 0,
 &cz_ExtnM1PeriodicRprtng_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnM1PeriodicRprtng_ExtIEsClsSpec =
{



 &cz_ExtnM1PeriodicRprtng_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnM1PeriodicRprtng_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnM1PeriodicRprtng_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnM1PeriodicRprtng_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnM1PeriodicRprtng_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_M1PeriodicRprtng_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnM1PeriodicRprtng_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_M1PeriodicRprtng_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_M1PeriodicRprtng_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_M1PeriodicRprtng_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_M1PeriodicRprtng_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_M1PeriodicRprtng_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_M1PeriodicRprtng_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_M1PeriodicRprtng_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M1PeriodicRprtng_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_M1PeriodicRprtng_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_M1PeriodicRprtng_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_M1PeriodicRprtng_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_M1PeriodicRprtng_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czM1PeriodicRprtngTkn[] =
{
 &czReportIntervalMDT,
 &czReportAmountMDT,
 &czOptProtExtnCont_M1PeriodicRprtng_ExtIEs,
  &czProtExtnField_M1PeriodicRprtng_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czM1PeriodicRprtngspec =
{



 1,
 0,
 0L,
 0L,
 &czM1PeriodicRprtngTkn[0],
 0
};
 CmPAsnElmDef czM1PeriodicRprtng =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztM1PeriodicRprtng),
 &flagCz3M,
 0,
 (U8 *)(&czM1PeriodicRprtngspec),
 0L
};
 CmPAsnElmDef czOptM1PeriodicRprtng =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztM1PeriodicRprtng),
 &flagCz3O,
 0,
 (U8 *)(&czM1PeriodicRprtngspec),
 0L
};
CmPAsnBitStrDef czMDT_Loc_Infospec =
{



 8,
 8
};
CmPAsnElmDef czMDT_Loc_Info =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztMDT_Loc_Info),
 &flagCz3M,
 0,
 (U8 *) (&czMDT_Loc_Infospec),
 0L
};
CmPAsnSetSeqOfDef czMDTPLMNLstspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef czMDTPLMNLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztMDTPLMNLst),
 &flagCz3M,
 0,
 (U8 *) (&czMDTPLMNLstspec),
 0L
};
 CmPAsnElmDef *cz_ExtnMDT_Config_ExtIEsClsInst[] =
{
 &czM3Config,
 &czM4Config,
 &czM5Config,
 &czMDT_Loc_Info,
 &czMDTPLMNLst,
  &czPLMN_Identity,
  &czConstTerm,

};
 U32 cz_ExtnMDT_Config_ExtIEsClsInstId[] =
{
 85,
 86,
 87,
 88,
 90,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ExtnMDT_Config_ExtIEsClsInfo =
{
 7,
 &cz_ExtnMDT_Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnMDT_Config_ExtIEsClsSpec =
{



 &cz_ExtnMDT_Config_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnMDT_Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnMDT_Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnMDT_Config_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnMDT_Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_MDT_Config_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnMDT_Config_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_MDT_Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_MDT_Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_MDT_Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_MDT_Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_MDT_Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_MDT_Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_MDT_Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_MDT_Config_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_MDT_Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_MDT_Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_MDT_Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_MDT_Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czMDT_ConfigTkn[] =
{
 &czMDT_Actvn,
 &czAreaScopeOfMDT,
 &czMeasurementsToActivate,
 &czM1RprtngTrigger,
 &czOptM1ThresholdEventA2,
 &czOptM1PeriodicRprtng,
 &czOptProtExtnCont_MDT_Config_ExtIEs,
  &czProtExtnField_MDT_Config_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMDT_Configspec =
{



 3,
 0,
 0L,
 0L,
 &czMDT_ConfigTkn[0],
 0
};
 CmPAsnElmDef czMDT_Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMDT_Config),
 &flagCz3M,
 0,
 (U8 *)(&czMDT_Configspec),
 0L
};

CmPAsnUIntDef czMeasurement_IDspec =
{



 1,
 4095UL
};
CmPAsnElmDef czMeasurement_ID =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztMeasurement_ID),
 &flagCz3M,
 0,
 (U8 *)(&czMeasurement_IDspec),
 0L
};

CmPAsnOctStrDef czMBMS_Service_Area_Identityspec =
{



 2,
 2
};
CmPAsnElmDef czMBMS_Service_Area_Identity =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(CztMBMS_Service_Area_Identity),
 &flagCz3M,
 0,
 (U8 *) (&czMBMS_Service_Area_Identityspec),
 0L
};
CmPAsnSetSeqOfDef czMBMS_Service_Area_Identity_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czMBMS_Service_Area_Identity_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztMBMS_Service_Area_Identity_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czMBMS_Service_Area_Identity_Lstspec),
 0L
};

CmPAsnTknEnum czRadioframeAllocnPeriodLst[7] =
{
 6,
 CztRadioframeAllocnPeriodn1Enum,
 CztRadioframeAllocnPeriodn2Enum,
 CztRadioframeAllocnPeriodn4Enum,
 CztRadioframeAllocnPeriodn8Enum,
 CztRadioframeAllocnPeriodn16Enum,
 CztRadioframeAllocnPeriodn32Enum
};
CmPAsnEnumDef czRadioframeAllocnPeriodspec =
{



 czRadioframeAllocnPeriodLst,
 0L
};
CmPAsnElmDef czRadioframeAllocnPeriod =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztRadioframeAllocnPeriod),
 &flagCz3M,
 0,
 (U8 *)(&czRadioframeAllocnPeriodspec),
 0L
};


CmPAsnUIntDef czRadioframeAllocnOffsetspec =
{



 0,
 7UL
};
CmPAsnElmDef czRadioframeAllocnOffset =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztRadioframeAllocnOffset),
 &flagCz3M,
 0,
 (U8 *)(&czRadioframeAllocnOffsetspec),
 0L
};

CmPAsnBitStrDef czOneframespec =
{



 6,
 6
};
CmPAsnElmDef czOneframe =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztOneframe),
 &flagCz3M,
 0,
 (U8 *) (&czOneframespec),
 0L
};
 CmPAsnElmDef *czSubframeAllocnTkn[] =
{
 &czOneframe,
 &czFourframes,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czSubframeAllocnspec =
{



 2,
 0,
 &czSubframeAllocnTkn[0]
};
CmPAsnElmDef czSubframeAllocn =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztSubframeAllocn),
 &flagCz3M,
 0L,
 (U8 *)(&czSubframeAllocnspec),
 0L
};
 CmPAsnElmDef *cz_ExtnMBSFN_Subframe_Info_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnMBSFN_Subframe_Info_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnMBSFN_Subframe_Info_ExtIEsClsInfo =
{
 0,
 &cz_ExtnMBSFN_Subframe_Info_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnMBSFN_Subframe_Info_ExtIEsClsSpec =
{



 &cz_ExtnMBSFN_Subframe_Info_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnMBSFN_Subframe_Info_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnMBSFN_Subframe_Info_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnMBSFN_Subframe_Info_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_MBSFN_Subframe_Info_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnMBSFN_Subframe_Info_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_MBSFN_Subframe_Info_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_MBSFN_Subframe_Info_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_MBSFN_Subframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_MBSFN_Subframe_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_MBSFN_Subframe_Info_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_MBSFN_Subframe_Info_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_MBSFN_Subframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_MBSFN_Subframe_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_MBSFN_Subframe_Info_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_MBSFN_Subframe_Info_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czMBSFN_Subframe_InfoTkn[] =
{
 &czRadioframeAllocnPeriod,
 &czRadioframeAllocnOffset,
 &czSubframeAllocn,
 &czOptProtExtnCont_MBSFN_Subframe_Info_ExtIEs,
  &czProtExtnField_MBSFN_Subframe_Info_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMBSFN_Subframe_Infospec =
{



 1,
 0,
 0L,
 0L,
 &czMBSFN_Subframe_InfoTkn[0],
 0
};
 CmPAsnElmDef czMBSFN_Subframe_Info =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMBSFN_Subframe_Info),
 &flagCz3M,
 0,
 (U8 *)(&czMBSFN_Subframe_Infospec),
 0L
};
CmPAsnSetSeqOfDef czMBSFN_Subframe_Infolistspec =
{



 1,
 8,
 3*sizeof(U32)
};
 CmPAsnElmDef czMBSFN_Subframe_Infolist =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztMBSFN_Subframe_Infolist),
 &flagCz3M,
 0,
 (U8 *) (&czMBSFN_Subframe_Infolistspec),
 0L
};

CmPAsnTknEnum czManagementBasedMDTallowedLst[2] =
{
 1,
 CztManagementBasedMDTallowedallowedEnum
};
CmPAsnEnumDef czManagementBasedMDTallowedspec =
{



 czManagementBasedMDTallowedLst,
 0L
};
CmPAsnElmDef czManagementBasedMDTallowed =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztManagementBasedMDTallowed),
 &flagCz3M,
 0,
 (U8 *)(&czManagementBasedMDTallowedspec),
 0L
};


CmPAsnSIntDef czMobilityParamsModificationRangehandoverTriggerChangeLowerLimitspec =
{



 -20,
 20UL
};
CmPAsnElmDef czMobilityParamsModificationRangehandoverTriggerChangeLowerLimit =
{



 CM_PASN_TET_SINT32,
 0,
 sizeof(CztMobilityParamsModificationRangehandoverTriggerChangeLowerLimit),
 &flagCz3M,
 0,
 (U8 *)(&czMobilityParamsModificationRangehandoverTriggerChangeLowerLimitspec),
 0L
};


CmPAsnSIntDef czMobilityParamsModificationRangehandoverTriggerChangeUpperLimitspec =
{



 -20,
 20UL
};
CmPAsnElmDef czMobilityParamsModificationRangehandoverTriggerChangeUpperLimit =
{



 CM_PASN_TET_SINT32,
 0,
 sizeof(CztMobilityParamsModificationRangehandoverTriggerChangeUpperLimit),
 &flagCz3M,
 0,
 (U8 *)(&czMobilityParamsModificationRangehandoverTriggerChangeUpperLimitspec),
 0L
};

 CmPAsnElmDef *czMobilityParamsModificationRangeTkn[] =
{
 &czMobilityParamsModificationRangehandoverTriggerChangeLowerLimit,
 &czMobilityParamsModificationRangehandoverTriggerChangeUpperLimit,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMobilityParamsModificationRangespec =
{



 0,
 0,
 0L,
 0L,
 &czMobilityParamsModificationRangeTkn[0],
 0
};
 CmPAsnElmDef czMobilityParamsModificationRange =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMobilityParamsModificationRange),
 &flagCz3M,
 0,
 (U8 *)(&czMobilityParamsModificationRangespec),
 0L
};

CmPAsnSIntDef czMobilityParamsInformhandoverTriggerChangespec =
{



 -20,
 20UL
};
CmPAsnElmDef czMobilityParamsInformhandoverTriggerChange =
{



 CM_PASN_TET_SINT32,
 0,
 sizeof(CztMobilityParamsInformhandoverTriggerChange),
 &flagCz3M,
 0,
 (U8 *)(&czMobilityParamsInformhandoverTriggerChangespec),
 0L
};

 CmPAsnElmDef *czMobilityParamsInformTkn[] =
{
 &czMobilityParamsInformhandoverTriggerChange,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMobilityParamsInformspec =
{



 0,
 0,
 0L,
 0L,
 &czMobilityParamsInformTkn[0],
 0
};
 CmPAsnElmDef czMobilityParamsInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMobilityParamsInform),
 &flagCz3M,
 0,
 (U8 *)(&czMobilityParamsInformspec),
 0L
};
 CmPAsnElmDef *cz_ExtnBandInfo_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnBandInfo_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnBandInfo_ExtIEsClsInfo =
{
 0,
 &cz_ExtnBandInfo_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnBandInfo_ExtIEsClsSpec =
{



 &cz_ExtnBandInfo_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnBandInfo_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnBandInfo_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnBandInfo_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnBandInfo_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_BandInfo_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnBandInfo_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_BandInfo_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_BandInfo_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_BandInfo_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_BandInfo_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_BandInfo_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_BandInfo_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_BandInfo_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_BandInfo_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_BandInfo_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_BandInfo_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_BandInfo_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_BandInfo_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czBandInfoTkn[] =
{
 &czFreqBandIndicator,
 &czOptProtExtnCont_BandInfo_ExtIEs,
  &czProtExtnField_BandInfo_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czBandInfospec =
{



 1,
 0,
 0L,
 0L,
 &czBandInfoTkn[0],
 0
};
 CmPAsnElmDef czBandInfo =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztBandInfo),
 &flagCz3M,
 0,
 (U8 *)(&czBandInfospec),
 0L
};
CmPAsnSetSeqOfDef czMultibandInfoLstspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef czMultibandInfoLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztMultibandInfoLst),
 &flagCz3M,
 0,
 (U8 *) (&czMultibandInfoLstspec),
 0L
};

CmPAsnUIntDef czPCIspec =
{



 0,
 503UL
};
CmPAsnElmDef czPCI =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztPCI),
 &flagCz3M,
 0,
 (U8 *)(&czPCIspec),
 0L
};

 CmPAsnElmDef *cz_ExtnNeighbour_Inform_ExtIEsClsInst[] =
{
 &czTAC,
 &czEARFCNExtn
};
 U32 cz_ExtnNeighbour_Inform_ExtIEsClsInstId[] =
{
 76,
 94
};
 CmPAsnClassInfo cz_ExtnNeighbour_Inform_ExtIEsClsInfo =
{
 2,
 &cz_ExtnNeighbour_Inform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnNeighbour_Inform_ExtIEsClsSpec =
{



 &cz_ExtnNeighbour_Inform_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnNeighbour_Inform_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnNeighbour_Inform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnNeighbour_Inform_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnNeighbour_Inform_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_Neighbour_Inform_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnNeighbour_Inform_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_Neighbour_Inform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_Neighbour_Inform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_Neighbour_Inform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_Neighbour_Inform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_Neighbour_Inform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_Neighbour_Inform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_Neighbour_Inform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_Neighbour_Inform_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_Neighbour_Inform_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_Neighbour_Inform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_Neighbour_Inform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_Neighbour_Inform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czNeighbour_InformMemberTkn[] =
{
 &czECGI,
 &czPCI,
 &czEARFCN,
 &czOptProtExtnCont_Neighbour_Inform_ExtIEs,
  &czProtExtnField_Neighbour_Inform_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czNeighbour_InformMemberspec =
{



 1,
 0,
 0L,
 0L,
 &czNeighbour_InformMemberTkn[0],
 0
};
 CmPAsnElmDef czNeighbour_InformMember =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztNeighbour_InformMember),
 &flagCz3M,
 0,
 (U8 *)(&czNeighbour_InformMemberspec),
 0L
};
CmPAsnSetSeqOfDef czNeighbour_Informspec =
{



 0,
 512,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptNeighbour_Inform =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztNeighbour_Inform),
 &flagCz3O,
 0,
 (U8 *) (&czNeighbour_Informspec),
 0L
};

CmPAsnTknEnum czNumber_of_AntennaportsLst[4] =
{
 3,
 CztNumber_of_Antennaportsan1Enum,
 CztNumber_of_Antennaportsan2Enum,
 CztNumber_of_Antennaportsan4Enum
};
CmPAsnEnumDef czNumber_of_Antennaportsspec =
{



 czNumber_of_AntennaportsLst,
 0L
};
CmPAsnElmDef czNumber_of_Antennaports =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztNumber_of_Antennaports),
 &flagCz3M,
 0,
 (U8 *)(&czNumber_of_Antennaportsspec),
 0L
};


CmPAsnUIntDef czPRACH_ConfigrootSequenceIdxspec =
{



 0,
 837UL
};
CmPAsnElmDef czPRACH_ConfigrootSequenceIdx =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztPRACH_ConfigrootSequenceIdx),
 &flagCz3M,
 0,
 (U8 *)(&czPRACH_ConfigrootSequenceIdxspec),
 0L
};


CmPAsnUIntDef czPRACH_ConfigzeroCorrelationIdxspec =
{



 0,
 15UL
};
CmPAsnElmDef czPRACH_ConfigzeroCorrelationIdx =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztPRACH_ConfigzeroCorrelationIdx),
 &flagCz3M,
 0,
 (U8 *)(&czPRACH_ConfigzeroCorrelationIdxspec),
 0L
};

CmPAsnElmDef czPRACH_ConfighighSpeedFlag =
{



 CM_PASN_TET_BOOL,
 0,
 sizeof(TknU8),
 &flagCz3M,
 0,
 0L,
 (U8 *) 0L
};


CmPAsnUIntDef czPRACH_Configprach_FreqOffsetspec =
{



 0,
 94UL
};
CmPAsnElmDef czPRACH_Configprach_FreqOffset =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztPRACH_Configprach_FreqOffset),
 &flagCz3M,
 0,
 (U8 *)(&czPRACH_Configprach_FreqOffsetspec),
 0L
};


CmPAsnUIntDef czPRACH_Configprach_ConfigIdxspec =
{



 0,
 63UL
};
CmPAsnElmDef czOptPRACH_Configprach_ConfigIdx =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztPRACH_Configprach_ConfigIdx),
 &flagCz3O,
 0,
 (U8 *)(&czPRACH_Configprach_ConfigIdxspec),
 0L
};

 CmPAsnElmDef *cz_ExtnPRACH_Config_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnPRACH_Config_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnPRACH_Config_ExtIEsClsInfo =
{
 0,
 &cz_ExtnPRACH_Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnPRACH_Config_ExtIEsClsSpec =
{



 &cz_ExtnPRACH_Config_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnPRACH_Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnPRACH_Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnPRACH_Config_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnPRACH_Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_PRACH_Config_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnPRACH_Config_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_PRACH_Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_PRACH_Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_PRACH_Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_PRACH_Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_PRACH_Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_PRACH_Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_PRACH_Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_PRACH_Config_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_PRACH_Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_PRACH_Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_PRACH_Config_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_PRACH_Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czPRACH_ConfigTkn[] =
{
 &czPRACH_ConfigrootSequenceIdx,
 &czPRACH_ConfigzeroCorrelationIdx,
 &czPRACH_ConfighighSpeedFlag,
 &czPRACH_Configprach_FreqOffset,
 &czOptPRACH_Configprach_ConfigIdx,
 &czOptProtExtnCont_PRACH_Config_ExtIEs,
  &czProtExtnField_PRACH_Config_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czPRACH_Configspec =
{



 2,
 0,
 0L,
 0L,
 &czPRACH_ConfigTkn[0],
 0
};
 CmPAsnElmDef czPRACH_Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztPRACH_Config),
 &flagCz3M,
 0,
 (U8 *)(&czPRACH_Configspec),
 0L
};

CmPAsnUIntDef czUL_GBR_PRB_usagespec =
{



 0,
 100UL
};
CmPAsnElmDef czUL_GBR_PRB_usage =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztUL_GBR_PRB_usage),
 &flagCz3M,
 0,
 (U8 *)(&czUL_GBR_PRB_usagespec),
 0L
};


CmPAsnUIntDef czUL_non_GBR_PRB_usagespec =
{



 0,
 100UL
};
CmPAsnElmDef czUL_non_GBR_PRB_usage =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztUL_non_GBR_PRB_usage),
 &flagCz3M,
 0,
 (U8 *)(&czUL_non_GBR_PRB_usagespec),
 0L
};


CmPAsnUIntDef czUL_Total_PRB_usagespec =
{



 0,
 100UL
};
CmPAsnElmDef czUL_Total_PRB_usage =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztUL_Total_PRB_usage),
 &flagCz3M,
 0,
 (U8 *)(&czUL_Total_PRB_usagespec),
 0L
};

 CmPAsnElmDef *cz_ExtnRadioResStatus_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnRadioResStatus_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnRadioResStatus_ExtIEsClsInfo =
{
 0,
 &cz_ExtnRadioResStatus_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnRadioResStatus_ExtIEsClsSpec =
{



 &cz_ExtnRadioResStatus_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnRadioResStatus_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnRadioResStatus_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnRadioResStatus_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnRadioResStatus_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_RadioResStatus_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnRadioResStatus_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_RadioResStatus_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_RadioResStatus_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_RadioResStatus_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_RadioResStatus_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_RadioResStatus_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_RadioResStatus_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_RadioResStatus_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_RadioResStatus_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_RadioResStatus_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_RadioResStatus_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_RadioResStatus_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_RadioResStatus_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czRadioResStatusTkn[] =
{
 &czDL_GBR_PRB_usage,
 &czUL_GBR_PRB_usage,
 &czDL_non_GBR_PRB_usage,
 &czUL_non_GBR_PRB_usage,
 &czDL_Total_PRB_usage,
 &czUL_Total_PRB_usage,
 &czOptProtExtnCont_RadioResStatus_ExtIEs,
  &czProtExtnField_RadioResStatus_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czRadioResStatusspec =
{



 1,
 0,
 0L,
 0L,
 &czRadioResStatusTkn[0],
 0
};
 CmPAsnElmDef czRadioResStatus =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztRadioResStatus),
 &flagCz3M,
 0,
 (U8 *)(&czRadioResStatusspec),
 0L
};
 CmPAsnElmDef czOptRadioResStatus =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztRadioResStatus),
 &flagCz3O,
 0,
 (U8 *)(&czRadioResStatusspec),
 0L
};
CmPAsnBitStrDef czReceiveStatusofULPDCPSDUsspec =
{



 4096,
 4096
};
CmPAsnElmDef czOptReceiveStatusofULPDCPSDUs =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(CztReceiveStatusofULPDCPSDUs),
 &flagCz3O,
 0,
 (U8 *) (&czReceiveStatusofULPDCPSDUsspec),
 0L
};
CmPAsnElmDef czReceiveStatusofULPDCPSDUs =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(CztReceiveStatusofULPDCPSDUs),
 &flagCz3M,
 0,
 (U8 *) (&czReceiveStatusofULPDCPSDUsspec),
 0L
};
CmPAsnBitStrDef czReceiveStatusOfULPDCPSDUsExtendedspec =
{



 1,
 16384
};
CmPAsnElmDef czReceiveStatusOfULPDCPSDUsExtended =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(CztReceiveStatusOfULPDCPSDUsExtended),
 &flagCz3M,
 0,
 (U8 *) (&czReceiveStatusOfULPDCPSDUsExtendedspec),
 0L
};

CmPAsnTknEnum czRegistration_RqstLst[3] =
{
 2,
 CztRegistration_RqststartEnum,
 CztRegistration_RqststopEnum
};
CmPAsnEnumDef czRegistration_Rqstspec =
{



 czRegistration_RqstLst,
 0L
};
CmPAsnElmDef czRegistration_Rqst =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztRegistration_Rqst),
 &flagCz3M,
 0,
 (U8 *)(&czRegistration_Rqstspec),
 0L
};


CmPAsnTknEnum czRNTP_ThresholdLst[17] =
{
 16,
 CztRNTP_ThresholdminusInfinityEnum,
 CztRNTP_ThresholdminusElevenEnum,
 CztRNTP_ThresholdminusTenEnum,
 CztRNTP_ThresholdminusNineEnum,
 CztRNTP_ThresholdminusEightEnum,
 CztRNTP_ThresholdminusSevenEnum,
 CztRNTP_ThresholdminusSixEnum,
 CztRNTP_ThresholdminusFiveEnum,
 CztRNTP_ThresholdminusFourEnum,
 CztRNTP_ThresholdminusThreeEnum,
 CztRNTP_ThresholdminusTwoEnum,
 CztRNTP_ThresholdminusOneEnum,
 CztRNTP_ThresholdzeroEnum,
 CztRNTP_ThresholdoneEnum,
 CztRNTP_ThresholdtwoEnum,
 CztRNTP_ThresholdthreeEnum
};
CmPAsnEnumDef czRNTP_Thresholdspec =
{



 czRNTP_ThresholdLst,
 0L
};
CmPAsnElmDef czRNTP_Threshold =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztRNTP_Threshold),
 &flagCz3M,
 0,
 (U8 *)(&czRNTP_Thresholdspec),
 0L
};

CmPAsnBitStrDef czRelativeNarrowbandTxPowerrNTP_PerPRBspec =
{



 6,
 110
};
CmPAsnElmDef czRelativeNarrowbandTxPowerrNTP_PerPRB =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(CztRelativeNarrowbandTxPowerrNTP_PerPRB),
 &flagCz3M,
 0,
 (U8 *) (&czRelativeNarrowbandTxPowerrNTP_PerPRBspec),
 0L
};

CmPAsnTknEnum czRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortsLst[4] =
{
 3,
 CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortsoneEnum,
 CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortstwoEnum,
 CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortsfourEnum
};
CmPAsnEnumDef czRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortsspec =
{



 czRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortsLst,
 0L
};
CmPAsnElmDef czRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts),
 &flagCz3M,
 0,
 (U8 *)(&czRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPortsspec),
 0L
};


CmPAsnUIntDef czRelativeNarrowbandTxPowerp_Bspec =
{



 0,
 3UL
};
CmPAsnElmDef czRelativeNarrowbandTxPowerp_B =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztRelativeNarrowbandTxPowerp_B),
 &flagCz3M,
 0,
 (U8 *)(&czRelativeNarrowbandTxPowerp_Bspec),
 0L
};


CmPAsnUIntDef czRelativeNarrowbandTxPowerpDCCH_InterferenceImpactspec =
{



 0,
 4UL
};
CmPAsnElmDef czRelativeNarrowbandTxPowerpDCCH_InterferenceImpact =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(CztRelativeNarrowbandTxPowerpDCCH_InterferenceImpact),
 &flagCz3M,
 0,
 (U8 *)(&czRelativeNarrowbandTxPowerpDCCH_InterferenceImpactspec),
 0L
};

 CmPAsnElmDef *cz_ExtnRelativeNarrowbandTxPower_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnRelativeNarrowbandTxPower_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnRelativeNarrowbandTxPower_ExtIEsClsInfo =
{
 0,
 &cz_ExtnRelativeNarrowbandTxPower_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnRelativeNarrowbandTxPower_ExtIEsClsSpec =
{



 &cz_ExtnRelativeNarrowbandTxPower_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnRelativeNarrowbandTxPower_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnRelativeNarrowbandTxPower_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnRelativeNarrowbandTxPower_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_RelativeNarrowbandTxPower_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnRelativeNarrowbandTxPower_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_RelativeNarrowbandTxPower_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_RelativeNarrowbandTxPower_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_RelativeNarrowbandTxPower_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_RelativeNarrowbandTxPower_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_RelativeNarrowbandTxPower_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_RelativeNarrowbandTxPower_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_RelativeNarrowbandTxPower_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_RelativeNarrowbandTxPower_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_RelativeNarrowbandTxPower_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czRelativeNarrowbandTxPowerTkn[] =
{
 &czRelativeNarrowbandTxPowerrNTP_PerPRB,
 &czRNTP_Threshold,
 &czRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts,
 &czRelativeNarrowbandTxPowerp_B,
 &czRelativeNarrowbandTxPowerpDCCH_InterferenceImpact,
 &czOptProtExtnCont_RelativeNarrowbandTxPower_ExtIEs,
  &czProtExtnField_RelativeNarrowbandTxPower_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czRelativeNarrowbandTxPowerspec =
{



 1,
 0,
 0L,
 0L,
 &czRelativeNarrowbandTxPowerTkn[0],
 0
};
 CmPAsnElmDef czRelativeNarrowbandTxPower =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztRelativeNarrowbandTxPower),
 &flagCz3M,
 0,
 (U8 *)(&czRelativeNarrowbandTxPowerspec),
 0L
};
 CmPAsnElmDef czOptRelativeNarrowbandTxPower =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztRelativeNarrowbandTxPower),
 &flagCz3O,
 0,
 (U8 *)(&czRelativeNarrowbandTxPowerspec),
 0L
};
CmPAsnBitStrDef czReportCharacteristicsspec =
{



 32,
 32
};
CmPAsnElmDef czReportCharacteristics =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztReportCharacteristics),
 &flagCz3M,
 0,
 (U8 *) (&czReportCharacteristicsspec),
 0L
};
CmPAsnOctStrDef czRRC_Cntxtspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef czRRC_Cntxt =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(CztRRC_Cntxt),
 &flagCz3M,
 0,
 (U8 *) (&czRRC_Cntxtspec),
 0L
};

CmPAsnTknEnum czRRCConnReestabIndicatorLst[4] =
{
 3,
 CztRRCConnReestabIndicatorreconfigurationFailEnum,
 CztRRCConnReestabIndicatorhandoverFailEnum,
 CztRRCConnReestabIndicatorotherFailEnum
};
CmPAsnEnumDef czRRCConnReestabIndicatorspec =
{



 czRRCConnReestabIndicatorLst,
 0L
};
CmPAsnElmDef czRRCConnReestabIndicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztRRCConnReestabIndicator),
 &flagCz3M,
 0,
 (U8 *)(&czRRCConnReestabIndicatorspec),
 0L
};


CmPAsnTknEnum czRRCConnSetupIndicatorLst[2] =
{
 1,
 CztRRCConnSetupIndicatorrrcConnSetupEnum
};
CmPAsnEnumDef czRRCConnSetupIndicatorspec =
{



 czRRCConnSetupIndicatorLst,
 0L
};
CmPAsnElmDef czRRCConnSetupIndicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztRRCConnSetupIndicator),
 &flagCz3O,
 0,
 (U8 *)(&czRRCConnSetupIndicatorspec),
 0L
};

 CmPAsnElmDef *cz_ExtnS1TNLLoadIndicator_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnS1TNLLoadIndicator_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnS1TNLLoadIndicator_ExtIEsClsInfo =
{
 0,
 &cz_ExtnS1TNLLoadIndicator_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnS1TNLLoadIndicator_ExtIEsClsSpec =
{



 &cz_ExtnS1TNLLoadIndicator_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnS1TNLLoadIndicator_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnS1TNLLoadIndicator_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnS1TNLLoadIndicator_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnS1TNLLoadIndicator_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_S1TNLLoadIndicator_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnS1TNLLoadIndicator_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_S1TNLLoadIndicator_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_S1TNLLoadIndicator_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_S1TNLLoadIndicator_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_S1TNLLoadIndicator_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_S1TNLLoadIndicator_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_S1TNLLoadIndicator_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_S1TNLLoadIndicator_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_S1TNLLoadIndicator_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_S1TNLLoadIndicator_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_S1TNLLoadIndicator_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_S1TNLLoadIndicator_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_S1TNLLoadIndicator_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czS1TNLLoadIndicatorTkn[] =
{
 &czLoadIndicator,
 &czLoadIndicator,
 &czOptProtExtnCont_S1TNLLoadIndicator_ExtIEs,
  &czProtExtnField_S1TNLLoadIndicator_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czS1TNLLoadIndicatorspec =
{



 1,
 0,
 0L,
 0L,
 &czS1TNLLoadIndicatorTkn[0],
 0
};
 CmPAsnElmDef czS1TNLLoadIndicator =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztS1TNLLoadIndicator),
 &flagCz3M,
 0,
 (U8 *)(&czS1TNLLoadIndicatorspec),
 0L
};
 CmPAsnElmDef czOptS1TNLLoadIndicator =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztS1TNLLoadIndicator),
 &flagCz3O,
 0,
 (U8 *)(&czS1TNLLoadIndicatorspec),
 0L
};
 CmPAsnElmDef *cz_ExtnSrvdCell_Inform_ExtIEsClsInst[] =
{
 &czNumber_of_Antennaports,
 &czPRACH_Config,
 &czMBSFN_Subframe_Infolist,
  &czMBSFN_Subframe_Info,
  &czConstTerm,
 &czCSG_Id,
 &czMBMS_Service_Area_Identity_Lst,
  &czMBMS_Service_Area_Identity,
  &czConstTerm,
 &czMultibandInfoLst,
  &czBandInfo,
  &czConstTerm,

};
 U32 cz_ExtnSrvdCell_Inform_ExtIEsClsInstId[] =
{
 41,
 55,
 56,
  0xffffffff,
  0xffffffff,
 70,
 79,
  0xffffffff,
  0xffffffff,
 84,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ExtnSrvdCell_Inform_ExtIEsClsInfo =
{
 12,
 &cz_ExtnSrvdCell_Inform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnSrvdCell_Inform_ExtIEsClsSpec =
{



 &cz_ExtnSrvdCell_Inform_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnSrvdCell_Inform_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnSrvdCell_Inform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnSrvdCell_Inform_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnSrvdCell_Inform_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_SrvdCell_Inform_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnSrvdCell_Inform_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_SrvdCell_Inform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_SrvdCell_Inform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_SrvdCell_Inform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_SrvdCell_Inform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_SrvdCell_Inform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_SrvdCell_Inform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_SrvdCell_Inform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SrvdCell_Inform_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_SrvdCell_Inform_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_SrvdCell_Inform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SrvdCell_Inform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_SrvdCell_Inform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czSrvdCell_InformTkn[] =
{
 &czPCI,
 &czECGI,
 &czTAC,
 &czBroadcastPLMNs_Item,
  &czPLMN_Identity,
  &czConstTerm,
 &czEUTRA_Mode_Info,
 &czOptProtExtnCont_SrvdCell_Inform_ExtIEs,
  &czProtExtnField_SrvdCell_Inform_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czSrvdCell_Informspec =
{



 1,
 0,
 0L,
 0L,
 &czSrvdCell_InformTkn[0],
 0
};
 CmPAsnElmDef czSrvdCell_Inform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztSrvdCell_Inform),
 &flagCz3M,
 0,
 (U8 *)(&czSrvdCell_Informspec),
 0L
};
 CmPAsnElmDef *cz_ExtnSrvdCell_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnSrvdCell_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnSrvdCell_ExtIEsClsInfo =
{
 0,
 &cz_ExtnSrvdCell_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnSrvdCell_ExtIEsClsSpec =
{



 &cz_ExtnSrvdCell_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnSrvdCell_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnSrvdCell_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnSrvdCell_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnSrvdCell_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_SrvdCell_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnSrvdCell_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_SrvdCell_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_SrvdCell_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_SrvdCell_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_SrvdCell_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_SrvdCell_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_SrvdCell_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_SrvdCell_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SrvdCell_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_SrvdCell_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_SrvdCell_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SrvdCell_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_SrvdCell_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czSrvdCellsMemberTkn[] =
{
 &czSrvdCell_Inform,
 &czOptNeighbour_Inform,
  &czNeighbour_InformMember,
  &czConstTerm,
 &czOptProtExtnCont_SrvdCell_ExtIEs,
  &czProtExtnField_SrvdCell_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czSrvdCellsMemberspec =
{



 2,
 0,
 0L,
 0L,
 &czSrvdCellsMemberTkn[0],
 0
};
 CmPAsnElmDef czSrvdCellsMember =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztSrvdCellsMember),
 &flagCz3M,
 0,
 (U8 *)(&czSrvdCellsMemberspec),
 0L
};
CmPAsnSetSeqOfDef czSrvdCellsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czSrvdCells =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztSrvdCells),
 &flagCz3M,
 0,
 (U8 *) (&czSrvdCellsspec),
 0L
};
CmPAsnBitStrDef czShortMAC_Ispec =
{



 16,
 16
};
CmPAsnElmDef czShortMAC_I =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztShortMAC_I),
 &flagCz3O,
 0,
 (U8 *) (&czShortMAC_Ispec),
 0L
};

CmPAsnTknEnum czSRVCCOperationPossibleLst[2] =
{
 1,
 CztSRVCCOperationPossiblepossibleEnum
};
CmPAsnEnumDef czSRVCCOperationPossiblespec =
{



 czSRVCCOperationPossibleLst,
 0L
};
CmPAsnElmDef czSRVCCOperationPossible =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztSRVCCOperationPossible),
 &flagCz3M,
 0,
 (U8 *)(&czSRVCCOperationPossiblespec),
 0L
};


CmPAsnUIntDef czSubscriberProfileIDforRFPspec =
{



 1,
 256UL
};
CmPAsnElmDef czOptSubscriberProfileIDforRFP =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztSubscriberProfileIDforRFP),
 &flagCz3O,
 0,
 (U8 *)(&czSubscriberProfileIDforRFPspec),
 0L
};

CmPAsnOctStrDef czTgetCellInUTRANspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef czTgetCellInUTRAN =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(CztTgetCellInUTRAN),
 &flagCz3M,
 0,
 (U8 *) (&czTgetCellInUTRANspec),
 0L
};
CmPAsnOctStrDef czTgeteNBtoSrc_eNBTprntContspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef czTgeteNBtoSrc_eNBTprntCont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(CztTgeteNBtoSrc_eNBTprntCont),
 &flagCz3M,
 0,
 (U8 *) (&czTgeteNBtoSrc_eNBTprntContspec),
 0L
};

CmPAsnTknEnum czTimeToWaitLst[7] =
{
 6,
 CztTimeToWaitv1sEnum,
 CztTimeToWaitv2sEnum,
 CztTimeToWaitv5sEnum,
 CztTimeToWaitv10sEnum,
 CztTimeToWaitv20sEnum,
 CztTimeToWaitv60sEnum
};
CmPAsnEnumDef czTimeToWaitspec =
{



 czTimeToWaitLst,
 0L
};
CmPAsnElmDef czTimeToWait =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztTimeToWait),
 &flagCz3M,
 0,
 (U8 *)(&czTimeToWaitspec),
 0L
};


CmPAsnTknEnum czTraceDepthLst[7] =
{
 6,
 CztTraceDepthminimumEnum,
 CztTraceDepthmediumEnum,
 CztTraceDepthmaximumEnum,
 CztTraceDepthminimumWithoutVendorSpecificExtnEnum,
 CztTraceDepthmediumWithoutVendorSpecificExtnEnum,
 CztTraceDepthmaximumWithoutVendorSpecificExtnEnum
};
CmPAsnEnumDef czTraceDepthspec =
{



 czTraceDepthLst,
 0L
};
CmPAsnElmDef czTraceDepth =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztTraceDepth),
 &flagCz3M,
 0,
 (U8 *)(&czTraceDepthspec),
 0L
};

CmPAsnBitStrDef czTraceCollectionEntityIPAddrspec =
{



 1,
 160
};
CmPAsnElmDef czTraceCollectionEntityIPAddr =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(CztTraceCollectionEntityIPAddr),
 &flagCz3M,
 0,
 (U8 *) (&czTraceCollectionEntityIPAddrspec),
 0L
};
 CmPAsnElmDef *cz_ExtnTraceActvn_ExtIEsClsInst[] =
{
 &czMDT_Config
};
 U32 cz_ExtnTraceActvn_ExtIEsClsInstId[] =
{
 72
};
 CmPAsnClassInfo cz_ExtnTraceActvn_ExtIEsClsInfo =
{
 1,
 &cz_ExtnTraceActvn_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnTraceActvn_ExtIEsClsSpec =
{



 &cz_ExtnTraceActvn_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnTraceActvn_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnTraceActvn_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnTraceActvn_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnTraceActvn_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_TraceActvn_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnTraceActvn_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_TraceActvn_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_TraceActvn_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_TraceActvn_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_TraceActvn_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_TraceActvn_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_TraceActvn_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_TraceActvn_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TraceActvn_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_TraceActvn_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_TraceActvn_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_TraceActvn_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_TraceActvn_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czTraceActvnTkn[] =
{
 &czEUTRANTraceID,
 &czIntfsToTrace,
 &czTraceDepth,
 &czTraceCollectionEntityIPAddr,
 &czOptProtExtnCont_TraceActvn_ExtIEs,
  &czProtExtnField_TraceActvn_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czTraceActvnspec =
{



 1,
 0,
 0L,
 0L,
 &czTraceActvnTkn[0],
 0
};
 CmPAsnElmDef czTraceActvn =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztTraceActvn),
 &flagCz3M,
 0,
 (U8 *)(&czTraceActvnspec),
 0L
};
CmPAsnSetSeqOfDef czUE_HistoryInformspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef czUE_HistoryInform =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztUE_HistoryInform),
 &flagCz3M,
 0,
 (U8 *) (&czUE_HistoryInformspec),
 0L
};

CmPAsnUIntDef czUE_S1AP_IDspec =
{



 0,
 4294967295UL
};
CmPAsnElmDef czUE_S1AP_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztUE_S1AP_ID),
 &flagCz3M,
 0,
 (U8 *)(&czUE_S1AP_IDspec),
 0L
};


CmPAsnUIntDef czUE_X2AP_IDspec =
{



 0,
 4095UL
};
CmPAsnElmDef czUE_X2AP_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(CztUE_X2AP_ID),
 &flagCz3M,
 0,
 (U8 *)(&czUE_X2AP_IDspec),
 0L
};

 CmPAsnElmDef *cz_ExtnUEAgg_MaxBitrate_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnUEAgg_MaxBitrate_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnUEAgg_MaxBitrate_ExtIEsClsInfo =
{
 0,
 &cz_ExtnUEAgg_MaxBitrate_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnUEAgg_MaxBitrate_ExtIEsClsSpec =
{



 &cz_ExtnUEAgg_MaxBitrate_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnUEAgg_MaxBitrate_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnUEAgg_MaxBitrate_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnUEAgg_MaxBitrate_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_UEAgg_MaxBitrate_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnUEAgg_MaxBitrate_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_UEAgg_MaxBitrate_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_UEAgg_MaxBitrate_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_UEAgg_MaxBitrate_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_UEAgg_MaxBitrate_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_UEAgg_MaxBitrate_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_UEAgg_MaxBitrate_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_UEAgg_MaxBitrate_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_UEAgg_MaxBitrate_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_UEAgg_MaxBitrate_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_UEAgg_MaxBitrate_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czUEAggMaxBitRateTkn[] =
{
 &czBitRate,
 &czBitRate,
 &czOptProtExtnCont_UEAgg_MaxBitrate_ExtIEs,
  &czProtExtnField_UEAgg_MaxBitrate_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czUEAggMaxBitRatespec =
{



 1,
 0,
 0L,
 0L,
 &czUEAggMaxBitRateTkn[0],
 0
};
 CmPAsnElmDef czUEAggMaxBitRate =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztUEAggMaxBitRate),
 &flagCz3M,
 0,
 (U8 *)(&czUEAggMaxBitRatespec),
 0L
};
 CmPAsnElmDef *cz_ExtnUESecurCapabilities_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnUESecurCapabilities_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnUESecurCapabilities_ExtIEsClsInfo =
{
 0,
 &cz_ExtnUESecurCapabilities_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnUESecurCapabilities_ExtIEsClsSpec =
{



 &cz_ExtnUESecurCapabilities_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnUESecurCapabilities_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnUESecurCapabilities_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnUESecurCapabilities_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnUESecurCapabilities_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_UESecurCapabilities_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnUESecurCapabilities_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_UESecurCapabilities_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_UESecurCapabilities_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_UESecurCapabilities_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_UESecurCapabilities_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_UESecurCapabilities_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_UESecurCapabilities_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_UESecurCapabilities_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UESecurCapabilities_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_UESecurCapabilities_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_UESecurCapabilities_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UESecurCapabilities_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_UESecurCapabilities_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czUESecurCapabilitiesTkn[] =
{
 &czEncryptionAlgorithms,
 &czIntegrityProtectionAlgorithms,
 &czOptProtExtnCont_UESecurCapabilities_ExtIEs,
  &czProtExtnField_UESecurCapabilities_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czUESecurCapabilitiesspec =
{



 1,
 0,
 0L,
 0L,
 &czUESecurCapabilitiesTkn[0],
 0
};
 CmPAsnElmDef czUESecurCapabilities =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztUESecurCapabilities),
 &flagCz3M,
 0,
 (U8 *)(&czUESecurCapabilitiesspec),
 0L
};

CmPAsnTknEnum czUL_InterferenceOverloadInd_ItemLst[4] =
{
 3,
 CztUL_InterferenceOverloadInd_Itemhigh_interferenceEnum,
 CztUL_InterferenceOverloadInd_Itemmedium_interferenceEnum,
 CztUL_InterferenceOverloadInd_Itemlow_interferenceEnum
};
CmPAsnEnumDef czUL_InterferenceOverloadInd_Itemspec =
{



 czUL_InterferenceOverloadInd_ItemLst,
 0L
};
CmPAsnElmDef czUL_InterferenceOverloadInd_Item =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztUL_InterferenceOverloadInd_Item),
 &flagCz3M,
 0,
 (U8 *)(&czUL_InterferenceOverloadInd_Itemspec),
 0L
};

CmPAsnSetSeqOfDef czUL_InterferenceOverloadIndspec =
{



 1,
 110,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptUL_InterferenceOverloadInd =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztUL_InterferenceOverloadInd),
 &flagCz3O,
 0,
 (U8 *) (&czUL_InterferenceOverloadIndspec),
 0L
};
CmPAsnBitStrDef czUL_HighInterferenceIndspec =
{



 1,
 110
};
CmPAsnElmDef czUL_HighInterferenceInd =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(CztUL_HighInterferenceInd),
 &flagCz3M,
 0,
 (U8 *) (&czUL_HighInterferenceIndspec),
 0L
};
 CmPAsnElmDef *cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsClsSpec =
{



 &cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czUL_HighInterferenceIndInfo_ItemTkn[] =
{
 &czECGI,
 &czUL_HighInterferenceInd,
 &czOptProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs,
  &czProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czUL_HighInterferenceIndInfo_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czUL_HighInterferenceIndInfo_ItemTkn[0],
 0
};
 CmPAsnElmDef czUL_HighInterferenceIndInfo_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztUL_HighInterferenceIndInfo_Item),
 &flagCz3M,
 0,
 (U8 *)(&czUL_HighInterferenceIndInfo_Itemspec),
 0L
};
CmPAsnSetSeqOfDef czUL_HighInterferenceIndInfospec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptUL_HighInterferenceIndInfo =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztUL_HighInterferenceIndInfo),
 &flagCz3O,
 0,
 (U8 *) (&czUL_HighInterferenceIndInfospec),
 0L
};
CmPAsnOctStrDef czUE_RLF_Report_Contspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef czUE_RLF_Report_Cont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(CztUE_RLF_Report_Cont),
 &flagCz3O,
 0,
 (U8 *) (&czUE_RLF_Report_Contspec),
 0L
};
 CmPAsnElmDef *cz_ExtnE_RABs_ToBeSetup_ItemExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnE_RABs_ToBeSetup_ItemExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnE_RABs_ToBeSetup_ItemExtIEsClsInfo =
{
 0,
 &cz_ExtnE_RABs_ToBeSetup_ItemExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnE_RABs_ToBeSetup_ItemExtIEsClsSpec =
{



 &cz_ExtnE_RABs_ToBeSetup_ItemExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnE_RABs_ToBeSetup_ItemExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnE_RABs_ToBeSetup_ItemExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnE_RABs_ToBeSetup_ItemExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_E_RABs_ToBeSetup_ItemExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnE_RABs_ToBeSetup_ItemExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_E_RABs_ToBeSetup_ItemExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_E_RABs_ToBeSetup_ItemExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_E_RABs_ToBeSetup_ItemExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_E_RABs_ToBeSetup_ItemExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_E_RABs_ToBeSetup_ItemExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_E_RABs_ToBeSetup_ItemExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_E_RABs_ToBeSetup_ItemExtIEsspec),
 0L
};
 CmPAsnElmDef *czE_RABs_ToBeSetup_ItemTkn[] =
{
 &czE_RAB_ID,
 &czE_RAB_Lvl_QoS_Params,
 &czOptDL_Fwding,
 &czGTPtunnelEndpoint,
 &czOptProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs,
  &czProtExtnField_E_RABs_ToBeSetup_ItemExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czE_RABs_ToBeSetup_Itemspec =
{



 2,
 0,
 0L,
 0L,
 &czE_RABs_ToBeSetup_ItemTkn[0],
 0
};
 CmPAsnElmDef czE_RABs_ToBeSetup_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztE_RABs_ToBeSetup_Item),
 &flagCz3M,
 0,
 (U8 *)(&czE_RABs_ToBeSetup_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueE_RABs_ToBeSetup_ItemIEsClsInst[] =
{
 &czE_RABs_ToBeSetup_Item
};
 U32 cz_ValueE_RABs_ToBeSetup_ItemIEsClsInstId[] =
{
 4
};
 CmPAsnClassInfo cz_ValueE_RABs_ToBeSetup_ItemIEsClsInfo =
{
 1,
 &cz_ValueE_RABs_ToBeSetup_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueE_RABs_ToBeSetup_ItemIEsClsSpec =
{



 &cz_ValueE_RABs_ToBeSetup_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueE_RABs_ToBeSetup_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueE_RABs_ToBeSetup_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueE_RABs_ToBeSetup_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueE_RABs_ToBeSetup_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_E_RABs_ToBeSetup_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueE_RABs_ToBeSetup_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_E_RABs_ToBeSetup_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_E_RABs_ToBeSetup_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_E_RABs_ToBeSetup_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_E_RABs_ToBeSetup_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czE_RABs_ToBeSetup_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czE_RABs_ToBeSetup_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztE_RABs_ToBeSetup_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czE_RABs_ToBeSetup_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ExtnUE_CntxtInform_ExtIEsClsInst[] =
{
 &czManagementBasedMDTallowed,
 &czMDTPLMNLst,
  &czPLMN_Identity,
  &czConstTerm,

};
 U32 cz_ExtnUE_CntxtInform_ExtIEsClsInstId[] =
{
 74,
 89,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ExtnUE_CntxtInform_ExtIEsClsInfo =
{
 4,
 &cz_ExtnUE_CntxtInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnUE_CntxtInform_ExtIEsClsSpec =
{



 &cz_ExtnUE_CntxtInform_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnUE_CntxtInform_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnUE_CntxtInform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnUE_CntxtInform_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnUE_CntxtInform_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_UE_CntxtInform_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnUE_CntxtInform_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_UE_CntxtInform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_UE_CntxtInform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_UE_CntxtInform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_UE_CntxtInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_UE_CntxtInform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_UE_CntxtInform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_UE_CntxtInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UE_CntxtInform_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_UE_CntxtInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_UE_CntxtInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_UE_CntxtInform_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_UE_CntxtInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czUE_CntxtInformTkn[] =
{
 &czUE_S1AP_ID,
 &czUESecurCapabilities,
 &czAS_SecurInform,
 &czUEAggMaxBitRate,
 &czOptSubscriberProfileIDforRFP,
 &czE_RABs_ToBeSetup_Lst,
  &czProtIE_Field_E_RABs_ToBeSetup_ItemIEs,
  &czConstTerm,
 &czRRC_Cntxt,
 &czOptHovrRestrnLst,
 &czOptLocRprtngInform,
 &czOptProtExtnCont_UE_CntxtInform_ExtIEs,
  &czProtExtnField_UE_CntxtInform_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czUE_CntxtInformspec =
{



 4,
 0,
 0L,
 0L,
 &czUE_CntxtInformTkn[0],
 0
};
 CmPAsnElmDef czUE_CntxtInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztUE_CntxtInform),
 &flagCz3M,
 0,
 (U8 *)(&czUE_CntxtInformspec),
 0L
};
CmPAsnBitStrDef czMobilityInformspec =
{



 32,
 32
};
CmPAsnElmDef czMobilityInform =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(CztMobilityInform),
 &flagCz3M,
 0,
 (U8 *) (&czMobilityInformspec),
 0L
};
 CmPAsnElmDef *cz_ValueHovrRqst_IEsClsInst[] =
{
 &czUE_X2AP_ID,
 &czCause,
 &czECGI,
 &czGUMMEI,
 &czUE_CntxtInform,
 &czUE_HistoryInform,
  &czLastVisitedCell_Item,
  &czConstTerm,
 &czTraceActvn,
 &czSRVCCOperationPossible,
 &czCSGMembershipStatus,
 &czMobilityInform
};
 U32 cz_ValueHovrRqst_IEsClsInstId[] =
{
 10,
 5,
 11,
 23,
 14,
 15,
  0xffffffff,
  0xffffffff,
 13,
 36,
 71,
 82
};
 CmPAsnClassInfo cz_ValueHovrRqst_IEsClsInfo =
{
 12,
 &cz_ValueHovrRqst_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueHovrRqst_IEsClsSpec =
{



 &cz_ValueHovrRqst_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueHovrRqst_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueHovrRqst_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueHovrRqst_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueHovrRqst_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_HovrRqst_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueHovrRqst_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_HovrRqst_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_HovrRqst_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_HovrRqst_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_HovrRqst_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_HovrRqst_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_HovrRqst_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_HovrRqst_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_HovrRqst_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_HovrRqst_IEsspec),
 0L
};
 CmPAsnElmDef *czHovrRqstTkn[] =
{
 &czProtIE_Cont_HovrRqst_IEs,
  &czProtIE_Field_HovrRqst_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czHovrRqstspec =
{



 0,
 0,
 0L,
 0L,
 &czHovrRqstTkn[0],
 0
};
 CmPAsnElmDef czHovrRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHovrRqst),
 &flagCz3M,
 0,
 (U8 *)(&czHovrRqstspec),
 0L
};
 CmPAsnElmDef *cz_ExtnE_RABs_Admtd_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnE_RABs_Admtd_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnE_RABs_Admtd_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnE_RABs_Admtd_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnE_RABs_Admtd_Item_ExtIEsClsSpec =
{



 &cz_ExtnE_RABs_Admtd_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnE_RABs_Admtd_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnE_RABs_Admtd_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnE_RABs_Admtd_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_E_RABs_Admtd_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnE_RABs_Admtd_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_E_RABs_Admtd_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_E_RABs_Admtd_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_E_RABs_Admtd_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_E_RABs_Admtd_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_E_RABs_Admtd_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_E_RABs_Admtd_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_E_RABs_Admtd_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_E_RABs_Admtd_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_E_RABs_Admtd_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_E_RABs_Admtd_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czE_RABs_Admtd_ItemTkn[] =
{
 &czE_RAB_ID,
 &czOptGTPtunnelEndpoint,
 &czOptGTPtunnelEndpoint,
 &czOptProtExtnCont_E_RABs_Admtd_Item_ExtIEs,
  &czProtExtnField_E_RABs_Admtd_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czE_RABs_Admtd_Itemspec =
{



 3,
 0,
 0L,
 0L,
 &czE_RABs_Admtd_ItemTkn[0],
 0
};
 CmPAsnElmDef czE_RABs_Admtd_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztE_RABs_Admtd_Item),
 &flagCz3M,
 0,
 (U8 *)(&czE_RABs_Admtd_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueE_RABs_Admtd_ItemIEsClsInst[] =
{
 &czE_RABs_Admtd_Item
};
 U32 cz_ValueE_RABs_Admtd_ItemIEsClsInstId[] =
{
 0
};
 CmPAsnClassInfo cz_ValueE_RABs_Admtd_ItemIEsClsInfo =
{
 1,
 &cz_ValueE_RABs_Admtd_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueE_RABs_Admtd_ItemIEsClsSpec =
{



 &cz_ValueE_RABs_Admtd_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueE_RABs_Admtd_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueE_RABs_Admtd_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueE_RABs_Admtd_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueE_RABs_Admtd_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_E_RABs_Admtd_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueE_RABs_Admtd_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_E_RABs_Admtd_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_E_RABs_Admtd_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_E_RABs_Admtd_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_E_RABs_Admtd_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_E_RABs_Admtd_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czE_RABs_Admtd_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czE_RABs_Admtd_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztE_RABs_Admtd_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czE_RABs_Admtd_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ValueHovrRqstAckg_IEsClsInst[] =
{
 &czUE_X2AP_ID,
 &czUE_X2AP_ID,
 &czE_RABs_Admtd_Lst,
  &czProtIE_Field_E_RABs_Admtd_ItemIEs,
  &czConstTerm,
 &czE_RAB_Lst,
  &czProtIE_Field_E_RAB_ItemIEs,
  &czConstTerm,
 &czTgeteNBtoSrc_eNBTprntCont,
 &czCriticalityDiag
};
 U32 cz_ValueHovrRqstAckg_IEsClsInstId[] =
{
 10,
 9,
 1,
  0xffffffff,
  0xffffffff,
 3,
  0xffffffff,
  0xffffffff,
 12,
 17
};
 CmPAsnClassInfo cz_ValueHovrRqstAckg_IEsClsInfo =
{
 10,
 &cz_ValueHovrRqstAckg_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueHovrRqstAckg_IEsClsSpec =
{



 &cz_ValueHovrRqstAckg_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueHovrRqstAckg_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueHovrRqstAckg_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueHovrRqstAckg_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueHovrRqstAckg_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_HovrRqstAckg_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueHovrRqstAckg_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_HovrRqstAckg_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_HovrRqstAckg_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_HovrRqstAckg_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_HovrRqstAckg_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_HovrRqstAckg_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_HovrRqstAckg_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_HovrRqstAckg_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_HovrRqstAckg_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_HovrRqstAckg_IEsspec),
 0L
};
 CmPAsnElmDef *czHovrRqstAckgTkn[] =
{
 &czProtIE_Cont_HovrRqstAckg_IEs,
  &czProtIE_Field_HovrRqstAckg_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czHovrRqstAckgspec =
{



 0,
 0,
 0L,
 0L,
 &czHovrRqstAckgTkn[0],
 0
};
 CmPAsnElmDef czHovrRqstAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHovrRqstAckg),
 &flagCz3M,
 0,
 (U8 *)(&czHovrRqstAckgspec),
 0L
};
 CmPAsnElmDef *cz_ValueHovrPrepFail_IEsClsInst[] =
{
 &czUE_X2AP_ID,
 &czCause,
 &czCriticalityDiag
};
 U32 cz_ValueHovrPrepFail_IEsClsInstId[] =
{
 10,
 5,
 17
};
 CmPAsnClassInfo cz_ValueHovrPrepFail_IEsClsInfo =
{
 3,
 &cz_ValueHovrPrepFail_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueHovrPrepFail_IEsClsSpec =
{



 &cz_ValueHovrPrepFail_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueHovrPrepFail_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueHovrPrepFail_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueHovrPrepFail_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueHovrPrepFail_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_HovrPrepFail_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueHovrPrepFail_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_HovrPrepFail_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_HovrPrepFail_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_HovrPrepFail_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_HovrPrepFail_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_HovrPrepFail_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_HovrPrepFail_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_HovrPrepFail_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_HovrPrepFail_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_HovrPrepFail_IEsspec),
 0L
};
 CmPAsnElmDef *czHovrPrepFailTkn[] =
{
 &czProtIE_Cont_HovrPrepFail_IEs,
  &czProtIE_Field_HovrPrepFail_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czHovrPrepFailspec =
{



 0,
 0,
 0L,
 0L,
 &czHovrPrepFailTkn[0],
 0
};
 CmPAsnElmDef czHovrPrepFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHovrPrepFail),
 &flagCz3M,
 0,
 (U8 *)(&czHovrPrepFailspec),
 0L
};
 CmPAsnElmDef *cz_ValueHovrReport_IEsClsInst[] =
{
 &czHovrReportTyp,
 &czCause,
 &czECGI,
 &czECGI,
 &czECGI,
 &czTgetCellInUTRAN,
 &czCRNTI,
 &czMobilityInform,
 &czUE_RLF_Report_Cont
};
 U32 cz_ValueHovrReport_IEsClsInstId[] =
{
 54,
 5,
 52,
 53,
 49,
 81,
 83,
 82,
 60
};
 CmPAsnClassInfo cz_ValueHovrReport_IEsClsInfo =
{
 9,
 &cz_ValueHovrReport_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueHovrReport_IEsClsSpec =
{



 &cz_ValueHovrReport_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueHovrReport_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueHovrReport_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueHovrReport_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueHovrReport_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_HovrReport_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueHovrReport_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_HovrReport_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_HovrReport_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_HovrReport_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_HovrReport_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_HovrReport_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_HovrReport_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_HovrReport_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_HovrReport_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_HovrReport_IEsspec),
 0L
};
 CmPAsnElmDef *czHovrReportTkn[] =
{
 &czProtIE_Cont_HovrReport_IEs,
  &czProtIE_Field_HovrReport_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czHovrReportspec =
{



 0,
 0,
 0L,
 0L,
 &czHovrReportTkn[0],
 0
};
 CmPAsnElmDef czHovrReport =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHovrReport),
 &flagCz3M,
 0,
 (U8 *)(&czHovrReportspec),
 0L
};
 CmPAsnElmDef *cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsClsInst[] =
{
 &czReceiveStatusOfULPDCPSDUsExtended,
 &czCOUNTValueExtended,
 &czCOUNTValueExtended
};
 U32 cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsClsInstId[] =
{
 91,
 92,
 93
};
 CmPAsnClassInfo cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsClsInfo =
{
 3,
 &cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsClsSpec =
{



 &cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEsspec),
 0L
};
 CmPAsnElmDef *czE_RABs_SubjToStatusTfr_ItemTkn[] =
{
 &czE_RAB_ID,
 &czOptReceiveStatusofULPDCPSDUs,
 &czCOUNTvalue,
 &czCOUNTvalue,
 &czOptProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs,
  &czProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czE_RABs_SubjToStatusTfr_Itemspec =
{



 2,
 0,
 0L,
 0L,
 &czE_RABs_SubjToStatusTfr_ItemTkn[0],
 0
};
 CmPAsnElmDef czE_RABs_SubjToStatusTfr_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztE_RABs_SubjToStatusTfr_Item),
 &flagCz3M,
 0,
 (U8 *)(&czE_RABs_SubjToStatusTfr_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueE_RABs_SubjToStatusTfr_ItemIEsClsInst[] =
{
 &czE_RABs_SubjToStatusTfr_Item
};
 U32 cz_ValueE_RABs_SubjToStatusTfr_ItemIEsClsInstId[] =
{
 19
};
 CmPAsnClassInfo cz_ValueE_RABs_SubjToStatusTfr_ItemIEsClsInfo =
{
 1,
 &cz_ValueE_RABs_SubjToStatusTfr_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueE_RABs_SubjToStatusTfr_ItemIEsClsSpec =
{



 &cz_ValueE_RABs_SubjToStatusTfr_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueE_RABs_SubjToStatusTfr_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueE_RABs_SubjToStatusTfr_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueE_RABs_SubjToStatusTfr_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueE_RABs_SubjToStatusTfr_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czE_RABs_SubjToStatusTfr_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czE_RABs_SubjToStatusTfr_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztE_RABs_SubjToStatusTfr_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czE_RABs_SubjToStatusTfr_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ValueSNStatusTfr_IEsClsInst[] =
{
 &czUE_X2AP_ID,
 &czUE_X2AP_ID,
 &czE_RABs_SubjToStatusTfr_Lst,
  &czProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs,
  &czConstTerm,

};
 U32 cz_ValueSNStatusTfr_IEsClsInstId[] =
{
 10,
 9,
 18,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ValueSNStatusTfr_IEsClsInfo =
{
 5,
 &cz_ValueSNStatusTfr_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueSNStatusTfr_IEsClsSpec =
{



 &cz_ValueSNStatusTfr_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueSNStatusTfr_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueSNStatusTfr_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueSNStatusTfr_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueSNStatusTfr_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_SNStatusTfr_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueSNStatusTfr_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_SNStatusTfr_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_SNStatusTfr_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_SNStatusTfr_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_SNStatusTfr_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_SNStatusTfr_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_SNStatusTfr_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_SNStatusTfr_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_SNStatusTfr_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_SNStatusTfr_IEsspec),
 0L
};
 CmPAsnElmDef *czSNStatusTfrTkn[] =
{
 &czProtIE_Cont_SNStatusTfr_IEs,
  &czProtIE_Field_SNStatusTfr_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czSNStatusTfrspec =
{



 0,
 0,
 0L,
 0L,
 &czSNStatusTfrTkn[0],
 0
};
 CmPAsnElmDef czSNStatusTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztSNStatusTfr),
 &flagCz3M,
 0,
 (U8 *)(&czSNStatusTfrspec),
 0L
};
 CmPAsnElmDef *cz_ValueUECntxtRls_IEsClsInst[] =
{
 &czUE_X2AP_ID,
 &czUE_X2AP_ID
};
 U32 cz_ValueUECntxtRls_IEsClsInstId[] =
{
 10,
 9
};
 CmPAsnClassInfo cz_ValueUECntxtRls_IEsClsInfo =
{
 2,
 &cz_ValueUECntxtRls_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueUECntxtRls_IEsClsSpec =
{



 &cz_ValueUECntxtRls_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueUECntxtRls_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueUECntxtRls_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueUECntxtRls_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueUECntxtRls_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_UECntxtRls_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueUECntxtRls_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_UECntxtRls_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_UECntxtRls_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_UECntxtRls_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_UECntxtRls_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_UECntxtRls_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_UECntxtRls_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_UECntxtRls_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_UECntxtRls_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_UECntxtRls_IEsspec),
 0L
};
 CmPAsnElmDef *czUECntxtRlsTkn[] =
{
 &czProtIE_Cont_UECntxtRls_IEs,
  &czProtIE_Field_UECntxtRls_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czUECntxtRlsspec =
{



 0,
 0,
 0L,
 0L,
 &czUECntxtRlsTkn[0],
 0
};
 CmPAsnElmDef czUECntxtRls =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztUECntxtRls),
 &flagCz3M,
 0,
 (U8 *)(&czUECntxtRlsspec),
 0L
};
 CmPAsnElmDef *cz_ValueHovrCancel_IEsClsInst[] =
{
 &czUE_X2AP_ID,
 &czUE_X2AP_ID,
 &czCause
};
 U32 cz_ValueHovrCancel_IEsClsInstId[] =
{
 10,
 9,
 5
};
 CmPAsnClassInfo cz_ValueHovrCancel_IEsClsInfo =
{
 3,
 &cz_ValueHovrCancel_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueHovrCancel_IEsClsSpec =
{



 &cz_ValueHovrCancel_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueHovrCancel_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueHovrCancel_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueHovrCancel_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueHovrCancel_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_HovrCancel_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueHovrCancel_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_HovrCancel_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_HovrCancel_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_HovrCancel_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_HovrCancel_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_HovrCancel_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_HovrCancel_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_HovrCancel_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_HovrCancel_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_HovrCancel_IEsspec),
 0L
};
 CmPAsnElmDef *czHovrCancelTkn[] =
{
 &czProtIE_Cont_HovrCancel_IEs,
  &czProtIE_Field_HovrCancel_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czHovrCancelspec =
{



 0,
 0,
 0L,
 0L,
 &czHovrCancelTkn[0],
 0
};
 CmPAsnElmDef czHovrCancel =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztHovrCancel),
 &flagCz3M,
 0,
 (U8 *)(&czHovrCancelspec),
 0L
};
 CmPAsnElmDef *cz_ValueErrInd_IEsClsInst[] =
{
 &czUE_X2AP_ID,
 &czUE_X2AP_ID,
 &czCause,
 &czCriticalityDiag
};
 U32 cz_ValueErrInd_IEsClsInstId[] =
{
 10,
 9,
 5,
 17
};
 CmPAsnClassInfo cz_ValueErrInd_IEsClsInfo =
{
 4,
 &cz_ValueErrInd_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueErrInd_IEsClsSpec =
{



 &cz_ValueErrInd_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueErrInd_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueErrInd_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueErrInd_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueErrInd_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ErrInd_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueErrInd_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ErrInd_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ErrInd_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ErrInd_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ErrInd_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ErrInd_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ErrInd_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ErrInd_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ErrInd_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ErrInd_IEsspec),
 0L
};
 CmPAsnElmDef *czErrIndTkn[] =
{
 &czProtIE_Cont_ErrInd_IEs,
  &czProtIE_Field_ErrInd_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czErrIndspec =
{



 0,
 0,
 0L,
 0L,
 &czErrIndTkn[0],
 0
};
 CmPAsnElmDef czErrInd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztErrInd),
 &flagCz3M,
 0,
 (U8 *)(&czErrIndspec),
 0L
};
 CmPAsnElmDef *cz_ValueResetRqst_IEsClsInst[] =
{
 &czCause
};
 U32 cz_ValueResetRqst_IEsClsInstId[] =
{
 5
};
 CmPAsnClassInfo cz_ValueResetRqst_IEsClsInfo =
{
 1,
 &cz_ValueResetRqst_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueResetRqst_IEsClsSpec =
{



 &cz_ValueResetRqst_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueResetRqst_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueResetRqst_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueResetRqst_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueResetRqst_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ResetRqst_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueResetRqst_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ResetRqst_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ResetRqst_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ResetRqst_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ResetRqst_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ResetRqst_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ResetRqst_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ResetRqst_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ResetRqst_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ResetRqst_IEsspec),
 0L
};
 CmPAsnElmDef *czResetRqstTkn[] =
{
 &czProtIE_Cont_ResetRqst_IEs,
  &czProtIE_Field_ResetRqst_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czResetRqstspec =
{



 0,
 0,
 0L,
 0L,
 &czResetRqstTkn[0],
 0
};
 CmPAsnElmDef czResetRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztResetRqst),
 &flagCz3M,
 0,
 (U8 *)(&czResetRqstspec),
 0L
};
 CmPAsnElmDef *cz_ValueResetResp_IEsClsInst[] =
{
 &czCriticalityDiag
};
 U32 cz_ValueResetResp_IEsClsInstId[] =
{
 17
};
 CmPAsnClassInfo cz_ValueResetResp_IEsClsInfo =
{
 1,
 &cz_ValueResetResp_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueResetResp_IEsClsSpec =
{



 &cz_ValueResetResp_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueResetResp_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueResetResp_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueResetResp_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueResetResp_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ResetResp_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueResetResp_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ResetResp_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ResetResp_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ResetResp_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ResetResp_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ResetResp_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ResetResp_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ResetResp_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ResetResp_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ResetResp_IEsspec),
 0L
};
 CmPAsnElmDef *czResetRespTkn[] =
{
 &czProtIE_Cont_ResetResp_IEs,
  &czProtIE_Field_ResetResp_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czResetRespspec =
{



 0,
 0,
 0L,
 0L,
 &czResetRespTkn[0],
 0
};
 CmPAsnElmDef czResetResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztResetResp),
 &flagCz3M,
 0,
 (U8 *)(&czResetRespspec),
 0L
};
 CmPAsnElmDef *cz_ValueX2SetupRqst_IEsClsInst[] =
{
 &czGlobalENB_ID,
 &czSrvdCells,
  &czSrvdCellsMember,
  &czConstTerm,
 &czGUGroupIDLst,
  &czGU_Group_ID,
  &czConstTerm,

};
 U32 cz_ValueX2SetupRqst_IEsClsInstId[] =
{
 21,
 20,
  0xffffffff,
  0xffffffff,
 24,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ValueX2SetupRqst_IEsClsInfo =
{
 7,
 &cz_ValueX2SetupRqst_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueX2SetupRqst_IEsClsSpec =
{



 &cz_ValueX2SetupRqst_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueX2SetupRqst_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueX2SetupRqst_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueX2SetupRqst_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueX2SetupRqst_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_X2SetupRqst_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueX2SetupRqst_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_X2SetupRqst_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_X2SetupRqst_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_X2SetupRqst_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_X2SetupRqst_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_X2SetupRqst_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_X2SetupRqst_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_X2SetupRqst_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_X2SetupRqst_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_X2SetupRqst_IEsspec),
 0L
};
 CmPAsnElmDef *czX2SetupRqstTkn[] =
{
 &czProtIE_Cont_X2SetupRqst_IEs,
  &czProtIE_Field_X2SetupRqst_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czX2SetupRqstspec =
{



 0,
 0,
 0L,
 0L,
 &czX2SetupRqstTkn[0],
 0
};
 CmPAsnElmDef czX2SetupRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztX2SetupRqst),
 &flagCz3M,
 0,
 (U8 *)(&czX2SetupRqstspec),
 0L
};
 CmPAsnElmDef *cz_ValueX2SetupResp_IEsClsInst[] =
{
 &czGlobalENB_ID,
 &czSrvdCells,
  &czSrvdCellsMember,
  &czConstTerm,
 &czGUGroupIDLst,
  &czGU_Group_ID,
  &czConstTerm,
 &czCriticalityDiag
};
 U32 cz_ValueX2SetupResp_IEsClsInstId[] =
{
 21,
 20,
  0xffffffff,
  0xffffffff,
 24,
  0xffffffff,
  0xffffffff,
 17
};
 CmPAsnClassInfo cz_ValueX2SetupResp_IEsClsInfo =
{
 8,
 &cz_ValueX2SetupResp_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueX2SetupResp_IEsClsSpec =
{



 &cz_ValueX2SetupResp_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueX2SetupResp_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueX2SetupResp_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueX2SetupResp_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueX2SetupResp_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_X2SetupResp_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueX2SetupResp_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_X2SetupResp_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_X2SetupResp_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_X2SetupResp_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_X2SetupResp_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_X2SetupResp_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_X2SetupResp_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_X2SetupResp_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_X2SetupResp_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_X2SetupResp_IEsspec),
 0L
};
 CmPAsnElmDef *czX2SetupRespTkn[] =
{
 &czProtIE_Cont_X2SetupResp_IEs,
  &czProtIE_Field_X2SetupResp_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czX2SetupRespspec =
{



 0,
 0,
 0L,
 0L,
 &czX2SetupRespTkn[0],
 0
};
 CmPAsnElmDef czX2SetupResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztX2SetupResp),
 &flagCz3M,
 0,
 (U8 *)(&czX2SetupRespspec),
 0L
};
 CmPAsnElmDef *cz_ValueX2SetupFail_IEsClsInst[] =
{
 &czCause,
 &czTimeToWait,
 &czCriticalityDiag
};
 U32 cz_ValueX2SetupFail_IEsClsInstId[] =
{
 5,
 22,
 17
};
 CmPAsnClassInfo cz_ValueX2SetupFail_IEsClsInfo =
{
 3,
 &cz_ValueX2SetupFail_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueX2SetupFail_IEsClsSpec =
{



 &cz_ValueX2SetupFail_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueX2SetupFail_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueX2SetupFail_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueX2SetupFail_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueX2SetupFail_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_X2SetupFail_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueX2SetupFail_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_X2SetupFail_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_X2SetupFail_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_X2SetupFail_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_X2SetupFail_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_X2SetupFail_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_X2SetupFail_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_X2SetupFail_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_X2SetupFail_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_X2SetupFail_IEsspec),
 0L
};
 CmPAsnElmDef *czX2SetupFailTkn[] =
{
 &czProtIE_Cont_X2SetupFail_IEs,
  &czProtIE_Field_X2SetupFail_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czX2SetupFailspec =
{



 0,
 0,
 0L,
 0L,
 &czX2SetupFailTkn[0],
 0
};
 CmPAsnElmDef czX2SetupFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztX2SetupFail),
 &flagCz3M,
 0,
 (U8 *)(&czX2SetupFailspec),
 0L
};
 CmPAsnElmDef *cz_ExtnCellInform_Item_ExtIEsClsInst[] =
{
 &czABSInform,
 &czInvokeInd
};
 U32 cz_ExtnCellInform_Item_ExtIEsClsInstId[] =
{
 61,
 62
};
 CmPAsnClassInfo cz_ExtnCellInform_Item_ExtIEsClsInfo =
{
 2,
 &cz_ExtnCellInform_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCellInform_Item_ExtIEsClsSpec =
{



 &cz_ExtnCellInform_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCellInform_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCellInform_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCellInform_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCellInform_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CellInform_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCellInform_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CellInform_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CellInform_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CellInform_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CellInform_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CellInform_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CellInform_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CellInform_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellInform_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CellInform_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CellInform_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellInform_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CellInform_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCellInform_ItemTkn[] =
{
 &czECGI,
 &czOptUL_InterferenceOverloadInd,
  &czUL_InterferenceOverloadInd_Item,
  &czConstTerm,
 &czOptUL_HighInterferenceIndInfo,
  &czUL_HighInterferenceIndInfo_Item,
  &czConstTerm,
 &czOptRelativeNarrowbandTxPower,
 &czOptProtExtnCont_CellInform_Item_ExtIEs,
  &czProtExtnField_CellInform_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCellInform_Itemspec =
{



 4,
 0,
 0L,
 0L,
 &czCellInform_ItemTkn[0],
 0
};
 CmPAsnElmDef czCellInform_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCellInform_Item),
 &flagCz3M,
 0,
 (U8 *)(&czCellInform_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueCellInform_ItemIEsClsInst[] =
{
 &czCellInform_Item
};
 U32 cz_ValueCellInform_ItemIEsClsInstId[] =
{
 7
};
 CmPAsnClassInfo cz_ValueCellInform_ItemIEsClsInfo =
{
 1,
 &cz_ValueCellInform_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueCellInform_ItemIEsClsSpec =
{



 &cz_ValueCellInform_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueCellInform_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueCellInform_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueCellInform_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueCellInform_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_CellInform_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueCellInform_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_CellInform_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_CellInform_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_CellInform_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_CellInform_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_CellInform_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czCellInform_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czCellInform_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztCellInform_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czCellInform_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ValueLoadInform_IEsClsInst[] =
{
 &czCellInform_Lst,
  &czProtIE_Field_CellInform_ItemIEs,
  &czConstTerm,

};
 U32 cz_ValueLoadInform_IEsClsInstId[] =
{
 6,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ValueLoadInform_IEsClsInfo =
{
 3,
 &cz_ValueLoadInform_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueLoadInform_IEsClsSpec =
{



 &cz_ValueLoadInform_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueLoadInform_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueLoadInform_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueLoadInform_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueLoadInform_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_LoadInform_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueLoadInform_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_LoadInform_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_LoadInform_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_LoadInform_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_LoadInform_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_LoadInform_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_LoadInform_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_LoadInform_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_LoadInform_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_LoadInform_IEsspec),
 0L
};
 CmPAsnElmDef *czLoadInformTkn[] =
{
 &czProtIE_Cont_LoadInform_IEs,
  &czProtIE_Field_LoadInform_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czLoadInformspec =
{



 0,
 0,
 0L,
 0L,
 &czLoadInformTkn[0],
 0
};
 CmPAsnElmDef czLoadInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztLoadInform),
 &flagCz3M,
 0,
 (U8 *)(&czLoadInformspec),
 0L
};
 CmPAsnElmDef *cz_ExtnSrvdCellsToMdfy_Item_ExtIEsClsInst[] =
{
 &czDeactivationInd
};
 U32 cz_ExtnSrvdCellsToMdfy_Item_ExtIEsClsInstId[] =
{
 59
};
 CmPAsnClassInfo cz_ExtnSrvdCellsToMdfy_Item_ExtIEsClsInfo =
{
 1,
 &cz_ExtnSrvdCellsToMdfy_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnSrvdCellsToMdfy_Item_ExtIEsClsSpec =
{



 &cz_ExtnSrvdCellsToMdfy_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnSrvdCellsToMdfy_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnSrvdCellsToMdfy_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnSrvdCellsToMdfy_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_SrvdCellsToMdfy_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnSrvdCellsToMdfy_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_SrvdCellsToMdfy_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_SrvdCellsToMdfy_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_SrvdCellsToMdfy_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_SrvdCellsToMdfy_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_SrvdCellsToMdfy_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_SrvdCellsToMdfy_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_SrvdCellsToMdfy_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czSrvdCellsToMdfy_ItemTkn[] =
{
 &czECGI,
 &czSrvdCell_Inform,
 &czOptNeighbour_Inform,
  &czNeighbour_InformMember,
  &czConstTerm,
 &czOptProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs,
  &czProtExtnField_SrvdCellsToMdfy_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czSrvdCellsToMdfy_Itemspec =
{



 2,
 0,
 0L,
 0L,
 &czSrvdCellsToMdfy_ItemTkn[0],
 0
};
 CmPAsnElmDef czSrvdCellsToMdfy_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztSrvdCellsToMdfy_Item),
 &flagCz3M,
 0,
 (U8 *)(&czSrvdCellsToMdfy_Itemspec),
 0L
};
CmPAsnSetSeqOfDef czSrvdCellsToMdfyspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czSrvdCellsToMdfy =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztSrvdCellsToMdfy),
 &flagCz3M,
 0,
 (U8 *) (&czSrvdCellsToMdfyspec),
 0L
};
CmPAsnSetSeqOfDef czOld_ECGIsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czOld_ECGIs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztOld_ECGIs),
 &flagCz3M,
 0,
 (U8 *) (&czOld_ECGIsspec),
 0L
};
 CmPAsnElmDef *cz_ValueENBConfigUpd_IEsClsInst[] =
{
 &czSrvdCells,
  &czSrvdCellsMember,
  &czConstTerm,
 &czSrvdCellsToMdfy,
  &czSrvdCellsToMdfy_Item,
  &czConstTerm,
 &czOld_ECGIs,
  &czECGI,
  &czConstTerm,
 &czGUGroupIDLst,
  &czGU_Group_ID,
  &czConstTerm,
 &czGUGroupIDLst,
  &czGU_Group_ID,
  &czConstTerm,

};
 U32 cz_ValueENBConfigUpd_IEsClsInstId[] =
{
 25,
  0xffffffff,
  0xffffffff,
 26,
  0xffffffff,
  0xffffffff,
 27,
  0xffffffff,
  0xffffffff,
 34,
  0xffffffff,
  0xffffffff,
 35,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ValueENBConfigUpd_IEsClsInfo =
{
 15,
 &cz_ValueENBConfigUpd_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueENBConfigUpd_IEsClsSpec =
{



 &cz_ValueENBConfigUpd_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueENBConfigUpd_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueENBConfigUpd_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueENBConfigUpd_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueENBConfigUpd_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ENBConfigUpd_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueENBConfigUpd_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ENBConfigUpd_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ENBConfigUpd_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ENBConfigUpd_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ENBConfigUpd_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ENBConfigUpd_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ENBConfigUpd_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ENBConfigUpd_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ENBConfigUpd_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ENBConfigUpd_IEsspec),
 0L
};
 CmPAsnElmDef *czENBConfigUpdTkn[] =
{
 &czProtIE_Cont_ENBConfigUpd_IEs,
  &czProtIE_Field_ENBConfigUpd_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czENBConfigUpdspec =
{



 0,
 0,
 0L,
 0L,
 &czENBConfigUpdTkn[0],
 0
};
 CmPAsnElmDef czENBConfigUpd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztENBConfigUpd),
 &flagCz3M,
 0,
 (U8 *)(&czENBConfigUpdspec),
 0L
};
 CmPAsnElmDef *cz_ValueENBConfigUpdAckg_IEsClsInst[] =
{
 &czCriticalityDiag
};
 U32 cz_ValueENBConfigUpdAckg_IEsClsInstId[] =
{
 17
};
 CmPAsnClassInfo cz_ValueENBConfigUpdAckg_IEsClsInfo =
{
 1,
 &cz_ValueENBConfigUpdAckg_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueENBConfigUpdAckg_IEsClsSpec =
{



 &cz_ValueENBConfigUpdAckg_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueENBConfigUpdAckg_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueENBConfigUpdAckg_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueENBConfigUpdAckg_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueENBConfigUpdAckg_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ENBConfigUpdAckg_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueENBConfigUpdAckg_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ENBConfigUpdAckg_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ENBConfigUpdAckg_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ENBConfigUpdAckg_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ENBConfigUpdAckg_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ENBConfigUpdAckg_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ENBConfigUpdAckg_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ENBConfigUpdAckg_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ENBConfigUpdAckg_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ENBConfigUpdAckg_IEsspec),
 0L
};
 CmPAsnElmDef *czENBConfigUpdAckgTkn[] =
{
 &czProtIE_Cont_ENBConfigUpdAckg_IEs,
  &czProtIE_Field_ENBConfigUpdAckg_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czENBConfigUpdAckgspec =
{



 0,
 0,
 0L,
 0L,
 &czENBConfigUpdAckgTkn[0],
 0
};
 CmPAsnElmDef czENBConfigUpdAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztENBConfigUpdAckg),
 &flagCz3M,
 0,
 (U8 *)(&czENBConfigUpdAckgspec),
 0L
};
 CmPAsnElmDef *cz_ValueENBConfigUpdFail_IEsClsInst[] =
{
 &czCause,
 &czTimeToWait,
 &czCriticalityDiag
};
 U32 cz_ValueENBConfigUpdFail_IEsClsInstId[] =
{
 5,
 22,
 17
};
 CmPAsnClassInfo cz_ValueENBConfigUpdFail_IEsClsInfo =
{
 3,
 &cz_ValueENBConfigUpdFail_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueENBConfigUpdFail_IEsClsSpec =
{



 &cz_ValueENBConfigUpdFail_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueENBConfigUpdFail_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueENBConfigUpdFail_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueENBConfigUpdFail_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueENBConfigUpdFail_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ENBConfigUpdFail_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueENBConfigUpdFail_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ENBConfigUpdFail_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ENBConfigUpdFail_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ENBConfigUpdFail_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ENBConfigUpdFail_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ENBConfigUpdFail_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ENBConfigUpdFail_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ENBConfigUpdFail_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ENBConfigUpdFail_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ENBConfigUpdFail_IEsspec),
 0L
};
 CmPAsnElmDef *czENBConfigUpdFailTkn[] =
{
 &czProtIE_Cont_ENBConfigUpdFail_IEs,
  &czProtIE_Field_ENBConfigUpdFail_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czENBConfigUpdFailspec =
{



 0,
 0,
 0L,
 0L,
 &czENBConfigUpdFailTkn[0],
 0
};
 CmPAsnElmDef czENBConfigUpdFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztENBConfigUpdFail),
 &flagCz3M,
 0,
 (U8 *)(&czENBConfigUpdFailspec),
 0L
};
 CmPAsnElmDef *cz_ExtnCellToReport_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCellToReport_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCellToReport_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCellToReport_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCellToReport_Item_ExtIEsClsSpec =
{



 &cz_ExtnCellToReport_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCellToReport_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCellToReport_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCellToReport_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCellToReport_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CellToReport_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCellToReport_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CellToReport_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CellToReport_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CellToReport_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CellToReport_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CellToReport_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CellToReport_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CellToReport_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellToReport_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CellToReport_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CellToReport_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellToReport_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CellToReport_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCellToReport_ItemTkn[] =
{
 &czECGI,
 &czOptProtExtnCont_CellToReport_Item_ExtIEs,
  &czProtExtnField_CellToReport_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCellToReport_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czCellToReport_ItemTkn[0],
 0
};
 CmPAsnElmDef czCellToReport_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCellToReport_Item),
 &flagCz3M,
 0,
 (U8 *)(&czCellToReport_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueCellToReport_ItemIEsClsInst[] =
{
 &czCellToReport_Item
};
 U32 cz_ValueCellToReport_ItemIEsClsInstId[] =
{
 31
};
 CmPAsnClassInfo cz_ValueCellToReport_ItemIEsClsInfo =
{
 1,
 &cz_ValueCellToReport_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueCellToReport_ItemIEsClsSpec =
{



 &cz_ValueCellToReport_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueCellToReport_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueCellToReport_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueCellToReport_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueCellToReport_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_CellToReport_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueCellToReport_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_CellToReport_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_CellToReport_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_CellToReport_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_CellToReport_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_CellToReport_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czCellToReport_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czCellToReport_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztCellToReport_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czCellToReport_Lstspec),
 0L
};

CmPAsnTknEnum czRprtngPeriodicityLst[5] =
{
 4,
 CztRprtngPeriodicityone_thousand_msEnum,
 CztRprtngPeriodicitytwo_thousand_msEnum,
 CztRprtngPeriodicityfive_thousand_msEnum,
 CztRprtngPeriodicityten_thousand_msEnum
};
CmPAsnEnumDef czRprtngPeriodicityspec =
{



 czRprtngPeriodicityLst,
 0L
};
CmPAsnElmDef czRprtngPeriodicity =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztRprtngPeriodicity),
 &flagCz3M,
 0,
 (U8 *)(&czRprtngPeriodicityspec),
 0L
};


CmPAsnTknEnum czPartialSuccessIndicatorLst[2] =
{
 1,
 CztPartialSuccessIndicatorpartial_success_allowedEnum
};
CmPAsnEnumDef czPartialSuccessIndicatorspec =
{



 czPartialSuccessIndicatorLst,
 0L
};
CmPAsnElmDef czPartialSuccessIndicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(CztPartialSuccessIndicator),
 &flagCz3M,
 0,
 (U8 *)(&czPartialSuccessIndicatorspec),
 0L
};

 CmPAsnElmDef *cz_ValueResStatusRqst_IEsClsInst[] =
{
 &czMeasurement_ID,
 &czMeasurement_ID,
 &czRegistration_Rqst,
 &czReportCharacteristics,
 &czCellToReport_Lst,
  &czProtIE_Field_CellToReport_ItemIEs,
  &czConstTerm,
 &czRprtngPeriodicity,
 &czPartialSuccessIndicator
};
 U32 cz_ValueResStatusRqst_IEsClsInstId[] =
{
 39,
 40,
 28,
 38,
 29,
  0xffffffff,
  0xffffffff,
 30,
 64
};
 CmPAsnClassInfo cz_ValueResStatusRqst_IEsClsInfo =
{
 9,
 &cz_ValueResStatusRqst_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueResStatusRqst_IEsClsSpec =
{



 &cz_ValueResStatusRqst_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueResStatusRqst_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueResStatusRqst_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueResStatusRqst_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueResStatusRqst_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ResStatusRqst_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueResStatusRqst_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ResStatusRqst_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ResStatusRqst_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ResStatusRqst_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ResStatusRqst_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ResStatusRqst_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ResStatusRqst_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ResStatusRqst_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ResStatusRqst_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ResStatusRqst_IEsspec),
 0L
};
 CmPAsnElmDef *czResStatusRqstTkn[] =
{
 &czProtIE_Cont_ResStatusRqst_IEs,
  &czProtIE_Field_ResStatusRqst_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czResStatusRqstspec =
{



 0,
 0,
 0L,
 0L,
 &czResStatusRqstTkn[0],
 0
};
 CmPAsnElmDef czResStatusRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztResStatusRqst),
 &flagCz3M,
 0,
 (U8 *)(&czResStatusRqstspec),
 0L
};
 CmPAsnElmDef *cz_ExtnMeasurementFailCause_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnMeasurementFailCause_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnMeasurementFailCause_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnMeasurementFailCause_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnMeasurementFailCause_Item_ExtIEsClsSpec =
{



 &cz_ExtnMeasurementFailCause_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnMeasurementFailCause_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnMeasurementFailCause_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnMeasurementFailCause_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnMeasurementFailCause_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_MeasurementFailCause_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnMeasurementFailCause_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_MeasurementFailCause_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_MeasurementFailCause_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_MeasurementFailCause_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_MeasurementFailCause_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_MeasurementFailCause_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_MeasurementFailCause_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_MeasurementFailCause_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_MeasurementFailCause_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_MeasurementFailCause_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_MeasurementFailCause_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_MeasurementFailCause_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_MeasurementFailCause_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czMeasurementFailCause_ItemTkn[] =
{
 &czReportCharacteristics,
 &czCause,
 &czOptProtExtnCont_MeasurementFailCause_Item_ExtIEs,
  &czProtExtnField_MeasurementFailCause_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMeasurementFailCause_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czMeasurementFailCause_ItemTkn[0],
 0
};
 CmPAsnElmDef czMeasurementFailCause_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMeasurementFailCause_Item),
 &flagCz3M,
 0,
 (U8 *)(&czMeasurementFailCause_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueMeasurementFailCause_ItemIEsClsInst[] =
{
 &czMeasurementFailCause_Item
};
 U32 cz_ValueMeasurementFailCause_ItemIEsClsInstId[] =
{
 67
};
 CmPAsnClassInfo cz_ValueMeasurementFailCause_ItemIEsClsInfo =
{
 1,
 &cz_ValueMeasurementFailCause_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueMeasurementFailCause_ItemIEsClsSpec =
{



 &cz_ValueMeasurementFailCause_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueMeasurementFailCause_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueMeasurementFailCause_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueMeasurementFailCause_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueMeasurementFailCause_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_MeasurementFailCause_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueMeasurementFailCause_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_MeasurementFailCause_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_MeasurementFailCause_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_MeasurementFailCause_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_MeasurementFailCause_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_MeasurementFailCause_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czMeasurementFailCause_Lstspec =
{



 1,
 32,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptMeasurementFailCause_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztMeasurementFailCause_Lst),
 &flagCz3O,
 0,
 (U8 *) (&czMeasurementFailCause_Lstspec),
 0L
};
 CmPAsnElmDef czMeasurementFailCause_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztMeasurementFailCause_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czMeasurementFailCause_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ExtnMeasurementInitiationResult_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnMeasurementInitiationResult_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnMeasurementInitiationResult_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnMeasurementInitiationResult_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnMeasurementInitiationResult_Item_ExtIEsClsSpec =
{



 &cz_ExtnMeasurementInitiationResult_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnMeasurementInitiationResult_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnMeasurementInitiationResult_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnMeasurementInitiationResult_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_MeasurementInitiationResult_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnMeasurementInitiationResult_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_MeasurementInitiationResult_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_MeasurementInitiationResult_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_MeasurementInitiationResult_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_MeasurementInitiationResult_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_MeasurementInitiationResult_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_MeasurementInitiationResult_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_MeasurementInitiationResult_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_MeasurementInitiationResult_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_MeasurementInitiationResult_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czMeasurementInitiationResult_ItemTkn[] =
{
 &czECGI,
 &czOptMeasurementFailCause_Lst,
  &czProtIE_Field_MeasurementFailCause_ItemIEs,
  &czConstTerm,
 &czOptProtExtnCont_MeasurementInitiationResult_Item_ExtIEs,
  &czProtExtnField_MeasurementInitiationResult_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMeasurementInitiationResult_Itemspec =
{



 2,
 0,
 0L,
 0L,
 &czMeasurementInitiationResult_ItemTkn[0],
 0
};
 CmPAsnElmDef czMeasurementInitiationResult_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMeasurementInitiationResult_Item),
 &flagCz3M,
 0,
 (U8 *)(&czMeasurementInitiationResult_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueMeasurementInitiationResult_ItemIEsClsInst[] =
{
 &czMeasurementInitiationResult_Item
};
 U32 cz_ValueMeasurementInitiationResult_ItemIEsClsInstId[] =
{
 66
};
 CmPAsnClassInfo cz_ValueMeasurementInitiationResult_ItemIEsClsInfo =
{
 1,
 &cz_ValueMeasurementInitiationResult_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueMeasurementInitiationResult_ItemIEsClsSpec =
{



 &cz_ValueMeasurementInitiationResult_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueMeasurementInitiationResult_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueMeasurementInitiationResult_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueMeasurementInitiationResult_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueMeasurementInitiationResult_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_MeasurementInitiationResult_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueMeasurementInitiationResult_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_MeasurementInitiationResult_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_MeasurementInitiationResult_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_MeasurementInitiationResult_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_MeasurementInitiationResult_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_MeasurementInitiationResult_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czMeasurementInitiationResult_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czMeasurementInitiationResult_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztMeasurementInitiationResult_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czMeasurementInitiationResult_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ValueResStatusResp_IEsClsInst[] =
{
 &czMeasurement_ID,
 &czMeasurement_ID,
 &czCriticalityDiag,
 &czMeasurementInitiationResult_Lst,
  &czProtIE_Field_MeasurementInitiationResult_ItemIEs,
  &czConstTerm,

};
 U32 cz_ValueResStatusResp_IEsClsInstId[] =
{
 39,
 40,
 17,
 65,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ValueResStatusResp_IEsClsInfo =
{
 6,
 &cz_ValueResStatusResp_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueResStatusResp_IEsClsSpec =
{



 &cz_ValueResStatusResp_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueResStatusResp_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueResStatusResp_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueResStatusResp_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueResStatusResp_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ResStatusResp_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueResStatusResp_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ResStatusResp_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ResStatusResp_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ResStatusResp_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ResStatusResp_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ResStatusResp_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ResStatusResp_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ResStatusResp_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ResStatusResp_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ResStatusResp_IEsspec),
 0L
};
 CmPAsnElmDef *czResStatusRespTkn[] =
{
 &czProtIE_Cont_ResStatusResp_IEs,
  &czProtIE_Field_ResStatusResp_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czResStatusRespspec =
{



 0,
 0,
 0L,
 0L,
 &czResStatusRespTkn[0],
 0
};
 CmPAsnElmDef czResStatusResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztResStatusResp),
 &flagCz3M,
 0,
 (U8 *)(&czResStatusRespspec),
 0L
};
 CmPAsnElmDef *cz_ExtnCompleteFailCauseInform_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnCompleteFailCauseInform_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnCompleteFailCauseInform_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnCompleteFailCauseInform_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCompleteFailCauseInform_Item_ExtIEsClsSpec =
{



 &cz_ExtnCompleteFailCauseInform_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCompleteFailCauseInform_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCompleteFailCauseInform_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCompleteFailCauseInform_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CompleteFailCauseInform_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCompleteFailCauseInform_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CompleteFailCauseInform_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CompleteFailCauseInform_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CompleteFailCauseInform_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CompleteFailCauseInform_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CompleteFailCauseInform_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CompleteFailCauseInform_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CompleteFailCauseInform_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CompleteFailCauseInform_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CompleteFailCauseInform_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCompleteFailCauseInform_ItemTkn[] =
{
 &czECGI,
 &czMeasurementFailCause_Lst,
  &czProtIE_Field_MeasurementFailCause_ItemIEs,
  &czConstTerm,
 &czOptProtExtnCont_CompleteFailCauseInform_Item_ExtIEs,
  &czProtExtnField_CompleteFailCauseInform_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCompleteFailCauseInform_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czCompleteFailCauseInform_ItemTkn[0],
 0
};
 CmPAsnElmDef czCompleteFailCauseInform_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCompleteFailCauseInform_Item),
 &flagCz3M,
 0,
 (U8 *)(&czCompleteFailCauseInform_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueCompleteFailCauseInform_ItemIEsClsInst[] =
{
 &czCompleteFailCauseInform_Item
};
 U32 cz_ValueCompleteFailCauseInform_ItemIEsClsInstId[] =
{
 69
};
 CmPAsnClassInfo cz_ValueCompleteFailCauseInform_ItemIEsClsInfo =
{
 1,
 &cz_ValueCompleteFailCauseInform_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueCompleteFailCauseInform_ItemIEsClsSpec =
{



 &cz_ValueCompleteFailCauseInform_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueCompleteFailCauseInform_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueCompleteFailCauseInform_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueCompleteFailCauseInform_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueCompleteFailCauseInform_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_CompleteFailCauseInform_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueCompleteFailCauseInform_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_CompleteFailCauseInform_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_CompleteFailCauseInform_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_CompleteFailCauseInform_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_CompleteFailCauseInform_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_CompleteFailCauseInform_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czCompleteFailCauseInform_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czCompleteFailCauseInform_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztCompleteFailCauseInform_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czCompleteFailCauseInform_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ValueResStatusFail_IEsClsInst[] =
{
 &czMeasurement_ID,
 &czMeasurement_ID,
 &czCause,
 &czCriticalityDiag,
 &czCompleteFailCauseInform_Lst,
  &czProtIE_Field_CompleteFailCauseInform_ItemIEs,
  &czConstTerm,

};
 U32 cz_ValueResStatusFail_IEsClsInstId[] =
{
 39,
 40,
 5,
 17,
 68,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ValueResStatusFail_IEsClsInfo =
{
 7,
 &cz_ValueResStatusFail_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueResStatusFail_IEsClsSpec =
{



 &cz_ValueResStatusFail_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueResStatusFail_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueResStatusFail_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueResStatusFail_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueResStatusFail_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ResStatusFail_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueResStatusFail_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ResStatusFail_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ResStatusFail_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ResStatusFail_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ResStatusFail_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ResStatusFail_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ResStatusFail_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ResStatusFail_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ResStatusFail_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ResStatusFail_IEsspec),
 0L
};
 CmPAsnElmDef *czResStatusFailTkn[] =
{
 &czProtIE_Cont_ResStatusFail_IEs,
  &czProtIE_Field_ResStatusFail_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czResStatusFailspec =
{



 0,
 0,
 0L,
 0L,
 &czResStatusFailTkn[0],
 0
};
 CmPAsnElmDef czResStatusFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztResStatusFail),
 &flagCz3M,
 0,
 (U8 *)(&czResStatusFailspec),
 0L
};
 CmPAsnElmDef *cz_ExtnCellMeasurementResult_Item_ExtIEsClsInst[] =
{
 &czCompositeAvailableCapacityGroup,
 &czABS_Status
};
 U32 cz_ExtnCellMeasurementResult_Item_ExtIEsClsInstId[] =
{
 42,
 63
};
 CmPAsnClassInfo cz_ExtnCellMeasurementResult_Item_ExtIEsClsInfo =
{
 2,
 &cz_ExtnCellMeasurementResult_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnCellMeasurementResult_Item_ExtIEsClsSpec =
{



 &cz_ExtnCellMeasurementResult_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnCellMeasurementResult_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnCellMeasurementResult_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnCellMeasurementResult_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnCellMeasurementResult_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_CellMeasurementResult_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnCellMeasurementResult_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_CellMeasurementResult_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_CellMeasurementResult_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_CellMeasurementResult_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_CellMeasurementResult_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_CellMeasurementResult_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_CellMeasurementResult_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_CellMeasurementResult_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellMeasurementResult_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_CellMeasurementResult_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_CellMeasurementResult_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_CellMeasurementResult_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_CellMeasurementResult_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czCellMeasurementResult_ItemTkn[] =
{
 &czECGI,
 &czOptHWLoadIndicator,
 &czOptS1TNLLoadIndicator,
 &czOptRadioResStatus,
 &czOptProtExtnCont_CellMeasurementResult_Item_ExtIEs,
  &czProtExtnField_CellMeasurementResult_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCellMeasurementResult_Itemspec =
{



 4,
 0,
 0L,
 0L,
 &czCellMeasurementResult_ItemTkn[0],
 0
};
 CmPAsnElmDef czCellMeasurementResult_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCellMeasurementResult_Item),
 &flagCz3M,
 0,
 (U8 *)(&czCellMeasurementResult_Itemspec),
 0L
};
 CmPAsnElmDef *cz_ValueCellMeasurementResult_ItemIEsClsInst[] =
{
 &czCellMeasurementResult_Item
};
 U32 cz_ValueCellMeasurementResult_ItemIEsClsInstId[] =
{
 33
};
 CmPAsnClassInfo cz_ValueCellMeasurementResult_ItemIEsClsInfo =
{
 1,
 &cz_ValueCellMeasurementResult_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueCellMeasurementResult_ItemIEsClsSpec =
{



 &cz_ValueCellMeasurementResult_ItemIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueCellMeasurementResult_ItemIEsClsInst[0],



};
 CmPAsnElmDef cz_ValueCellMeasurementResult_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueCellMeasurementResult_ItemIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueCellMeasurementResult_ItemIEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_CellMeasurementResult_ItemIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueCellMeasurementResult_ItemIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_CellMeasurementResult_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_CellMeasurementResult_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_CellMeasurementResult_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_CellMeasurementResult_ItemIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_CellMeasurementResult_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef czCellMeasurementResult_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czCellMeasurementResult_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztCellMeasurementResult_Lst),
 &flagCz3M,
 0,
 (U8 *) (&czCellMeasurementResult_Lstspec),
 0L
};
 CmPAsnElmDef *cz_ValueResStatusUpd_IEsClsInst[] =
{
 &czMeasurement_ID,
 &czMeasurement_ID,
 &czCellMeasurementResult_Lst,
  &czProtIE_Field_CellMeasurementResult_ItemIEs,
  &czConstTerm,

};
 U32 cz_ValueResStatusUpd_IEsClsInstId[] =
{
 39,
 40,
 32,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ValueResStatusUpd_IEsClsInfo =
{
 5,
 &cz_ValueResStatusUpd_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueResStatusUpd_IEsClsSpec =
{



 &cz_ValueResStatusUpd_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueResStatusUpd_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueResStatusUpd_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueResStatusUpd_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueResStatusUpd_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_ResStatusUpd_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueResStatusUpd_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_ResStatusUpd_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_ResStatusUpd_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_ResStatusUpd_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_ResStatusUpd_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_ResStatusUpd_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_ResStatusUpd_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_ResStatusUpd_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_ResStatusUpd_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_ResStatusUpd_IEsspec),
 0L
};
 CmPAsnElmDef *czResStatusUpdTkn[] =
{
 &czProtIE_Cont_ResStatusUpd_IEs,
  &czProtIE_Field_ResStatusUpd_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czResStatusUpdspec =
{



 0,
 0,
 0L,
 0L,
 &czResStatusUpdTkn[0],
 0
};
 CmPAsnElmDef czResStatusUpd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztResStatusUpd),
 &flagCz3M,
 0,
 (U8 *)(&czResStatusUpdspec),
 0L
};
 CmPAsnElmDef *cz_ValuePrivMsg_IEsClsInst[] =
{
 0L
};
 U32 cz_ValuePrivMsg_IEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ValuePrivMsg_IEsClsInfo =
{
 0,
 &cz_ValuePrivMsg_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValuePrivMsg_IEsClsSpec =
{



 &cz_ValuePrivMsg_IEsClsInfo,
 0,
 &cz_ValuePrivMsg_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValuePrivMsg_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValuePrivMsg_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValuePrivMsg_IEsClsSpec)
};
 CmPAsnElmDef *czPrivIE_Field_PrivMsg_IEsTkn[] =
{
 &czPrivIE_ID,
 &czCriticality,
 &cz_ValuePrivMsg_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czPrivIE_Field_PrivMsg_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czPrivIE_Field_PrivMsg_IEsTkn[0],
 0
};
 CmPAsnElmDef czPrivIE_Field_PrivMsg_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztPrivIE_Field_PrivMsg_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czPrivIE_Field_PrivMsg_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czPrivIE_Cont_PrivMsg_IEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czPrivIE_Cont_PrivMsg_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztPrivIE_Cont_PrivMsg_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czPrivIE_Cont_PrivMsg_IEsspec),
 0L
};
 CmPAsnElmDef *czPrivMsgTkn[] =
{
 &czPrivIE_Cont_PrivMsg_IEs,
  &czPrivIE_Field_PrivMsg_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czPrivMsgspec =
{



 0,
 0,
 0L,
 0L,
 &czPrivMsgTkn[0],
 0
};
 CmPAsnElmDef czPrivMsg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztPrivMsg),
 &flagCz3M,
 0,
 (U8 *)(&czPrivMsgspec),
 0L
};
 CmPAsnElmDef *cz_ValueMobilityChangeRqst_IEsClsInst[] =
{
 &czECGI,
 &czECGI,
 &czMobilityParamsInform,
 &czMobilityParamsInform,
 &czCause
};
 U32 cz_ValueMobilityChangeRqst_IEsClsInstId[] =
{
 43,
 44,
 46,
 45,
 5
};
 CmPAsnClassInfo cz_ValueMobilityChangeRqst_IEsClsInfo =
{
 5,
 &cz_ValueMobilityChangeRqst_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueMobilityChangeRqst_IEsClsSpec =
{



 &cz_ValueMobilityChangeRqst_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueMobilityChangeRqst_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueMobilityChangeRqst_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueMobilityChangeRqst_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueMobilityChangeRqst_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_MobilityChangeRqst_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueMobilityChangeRqst_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_MobilityChangeRqst_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_MobilityChangeRqst_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_MobilityChangeRqst_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_MobilityChangeRqst_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_MobilityChangeRqst_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_MobilityChangeRqst_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_MobilityChangeRqst_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_MobilityChangeRqst_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_MobilityChangeRqst_IEsspec),
 0L
};
 CmPAsnElmDef *czMobilityChangeRqstTkn[] =
{
 &czProtIE_Cont_MobilityChangeRqst_IEs,
  &czProtIE_Field_MobilityChangeRqst_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMobilityChangeRqstspec =
{



 0,
 0,
 0L,
 0L,
 &czMobilityChangeRqstTkn[0],
 0
};
 CmPAsnElmDef czMobilityChangeRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMobilityChangeRqst),
 &flagCz3M,
 0,
 (U8 *)(&czMobilityChangeRqstspec),
 0L
};
 CmPAsnElmDef *cz_ValueMobilityChangeAckg_IEsClsInst[] =
{
 &czECGI,
 &czECGI,
 &czCriticalityDiag
};
 U32 cz_ValueMobilityChangeAckg_IEsClsInstId[] =
{
 43,
 44,
 17
};
 CmPAsnClassInfo cz_ValueMobilityChangeAckg_IEsClsInfo =
{
 3,
 &cz_ValueMobilityChangeAckg_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueMobilityChangeAckg_IEsClsSpec =
{



 &cz_ValueMobilityChangeAckg_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueMobilityChangeAckg_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueMobilityChangeAckg_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueMobilityChangeAckg_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueMobilityChangeAckg_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_MobilityChangeAckg_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueMobilityChangeAckg_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_MobilityChangeAckg_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_MobilityChangeAckg_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_MobilityChangeAckg_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_MobilityChangeAckg_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_MobilityChangeAckg_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_MobilityChangeAckg_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_MobilityChangeAckg_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_MobilityChangeAckg_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_MobilityChangeAckg_IEsspec),
 0L
};
 CmPAsnElmDef *czMobilityChangeAckgTkn[] =
{
 &czProtIE_Cont_MobilityChangeAckg_IEs,
  &czProtIE_Field_MobilityChangeAckg_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMobilityChangeAckgspec =
{



 0,
 0,
 0L,
 0L,
 &czMobilityChangeAckgTkn[0],
 0
};
 CmPAsnElmDef czMobilityChangeAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMobilityChangeAckg),
 &flagCz3M,
 0,
 (U8 *)(&czMobilityChangeAckgspec),
 0L
};
 CmPAsnElmDef *cz_ValueMobilityChangeFail_IEsClsInst[] =
{
 &czECGI,
 &czECGI,
 &czCause,
 &czMobilityParamsModificationRange,
 &czCriticalityDiag
};
 U32 cz_ValueMobilityChangeFail_IEsClsInstId[] =
{
 43,
 44,
 5,
 47,
 17
};
 CmPAsnClassInfo cz_ValueMobilityChangeFail_IEsClsInfo =
{
 5,
 &cz_ValueMobilityChangeFail_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueMobilityChangeFail_IEsClsSpec =
{



 &cz_ValueMobilityChangeFail_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueMobilityChangeFail_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueMobilityChangeFail_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueMobilityChangeFail_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueMobilityChangeFail_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_MobilityChangeFail_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueMobilityChangeFail_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_MobilityChangeFail_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_MobilityChangeFail_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_MobilityChangeFail_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_MobilityChangeFail_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_MobilityChangeFail_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_MobilityChangeFail_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_MobilityChangeFail_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_MobilityChangeFail_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_MobilityChangeFail_IEsspec),
 0L
};
 CmPAsnElmDef *czMobilityChangeFailTkn[] =
{
 &czProtIE_Cont_MobilityChangeFail_IEs,
  &czProtIE_Field_MobilityChangeFail_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czMobilityChangeFailspec =
{



 0,
 0,
 0L,
 0L,
 &czMobilityChangeFailTkn[0],
 0
};
 CmPAsnElmDef czMobilityChangeFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztMobilityChangeFail),
 &flagCz3M,
 0,
 (U8 *)(&czMobilityChangeFailspec),
 0L
};
 CmPAsnElmDef *cz_ValueRLFInd_IEsClsInst[] =
{
 &czPCI,
 &czECGI,
 &czCRNTI,
 &czShortMAC_I,
 &czUE_RLF_Report_Cont,
 &czRRCConnSetupIndicator,
 &czRRCConnReestabIndicator
};
 U32 cz_ValueRLFInd_IEsClsInstId[] =
{
 48,
 49,
 50,
 51,
 60,
 75,
 78
};
 CmPAsnClassInfo cz_ValueRLFInd_IEsClsInfo =
{
 7,
 &cz_ValueRLFInd_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueRLFInd_IEsClsSpec =
{



 &cz_ValueRLFInd_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueRLFInd_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueRLFInd_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueRLFInd_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueRLFInd_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_RLFInd_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueRLFInd_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_RLFInd_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_RLFInd_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_RLFInd_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_RLFInd_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_RLFInd_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_RLFInd_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_RLFInd_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_RLFInd_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_RLFInd_IEsspec),
 0L
};
 CmPAsnElmDef *czRLFIndTkn[] =
{
 &czProtIE_Cont_RLFInd_IEs,
  &czProtIE_Field_RLFInd_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czRLFIndspec =
{



 0,
 0,
 0L,
 0L,
 &czRLFIndTkn[0],
 0
};
 CmPAsnElmDef czRLFInd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztRLFInd),
 &flagCz3M,
 0,
 (U8 *)(&czRLFIndspec),
 0L
};
 CmPAsnElmDef *cz_ExtnSrvdCellsToActivate_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnSrvdCellsToActivate_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnSrvdCellsToActivate_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnSrvdCellsToActivate_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnSrvdCellsToActivate_Item_ExtIEsClsSpec =
{



 &cz_ExtnSrvdCellsToActivate_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnSrvdCellsToActivate_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnSrvdCellsToActivate_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnSrvdCellsToActivate_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_SrvdCellsToActivate_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnSrvdCellsToActivate_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_SrvdCellsToActivate_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_SrvdCellsToActivate_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_SrvdCellsToActivate_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_SrvdCellsToActivate_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_SrvdCellsToActivate_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_SrvdCellsToActivate_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_SrvdCellsToActivate_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_SrvdCellsToActivate_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_SrvdCellsToActivate_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czSrvdCellsToActivate_ItemTkn[] =
{
 &czECGI,
 &czOptProtExtnCont_SrvdCellsToActivate_Item_ExtIEs,
  &czProtExtnField_SrvdCellsToActivate_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czSrvdCellsToActivate_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czSrvdCellsToActivate_ItemTkn[0],
 0
};
 CmPAsnElmDef czSrvdCellsToActivate_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztSrvdCellsToActivate_Item),
 &flagCz3M,
 0,
 (U8 *)(&czSrvdCellsToActivate_Itemspec),
 0L
};
CmPAsnSetSeqOfDef czSrvdCellsToActivatespec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czSrvdCellsToActivate =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztSrvdCellsToActivate),
 &flagCz3M,
 0,
 (U8 *) (&czSrvdCellsToActivatespec),
 0L
};
 CmPAsnElmDef *cz_ValueCellActvnRqst_IEsClsInst[] =
{
 &czSrvdCellsToActivate,
  &czSrvdCellsToActivate_Item,
  &czConstTerm,

};
 U32 cz_ValueCellActvnRqst_IEsClsInstId[] =
{
 57,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo cz_ValueCellActvnRqst_IEsClsInfo =
{
 3,
 &cz_ValueCellActvnRqst_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueCellActvnRqst_IEsClsSpec =
{



 &cz_ValueCellActvnRqst_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueCellActvnRqst_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueCellActvnRqst_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueCellActvnRqst_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueCellActvnRqst_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_CellActvnRqst_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueCellActvnRqst_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_CellActvnRqst_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_CellActvnRqst_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_CellActvnRqst_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_CellActvnRqst_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_CellActvnRqst_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_CellActvnRqst_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_CellActvnRqst_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_CellActvnRqst_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_CellActvnRqst_IEsspec),
 0L
};
 CmPAsnElmDef *czCellActvnRqstTkn[] =
{
 &czProtIE_Cont_CellActvnRqst_IEs,
  &czProtIE_Field_CellActvnRqst_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCellActvnRqstspec =
{



 0,
 0,
 0L,
 0L,
 &czCellActvnRqstTkn[0],
 0
};
 CmPAsnElmDef czCellActvnRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCellActvnRqst),
 &flagCz3M,
 0,
 (U8 *)(&czCellActvnRqstspec),
 0L
};
 CmPAsnElmDef *cz_ExtnActivatedCellLst_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 cz_ExtnActivatedCellLst_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo cz_ExtnActivatedCellLst_Item_ExtIEsClsInfo =
{
 0,
 &cz_ExtnActivatedCellLst_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef cz_ExtnActivatedCellLst_Item_ExtIEsClsSpec =
{



 &cz_ExtnActivatedCellLst_Item_ExtIEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ExtnActivatedCellLst_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef cz_ExtnActivatedCellLst_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ExtnActivatedCellLst_Item_ExtIEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ExtnActivatedCellLst_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *czProtExtnField_ActivatedCellLst_Item_ExtIEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ExtnActivatedCellLst_Item_ExtIEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtExtnField_ActivatedCellLst_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtExtnField_ActivatedCellLst_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef czProtExtnField_ActivatedCellLst_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtExtnField_ActivatedCellLst_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtExtnField_ActivatedCellLst_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtExtnCont_ActivatedCellLst_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czOptProtExtnCont_ActivatedCellLst_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ActivatedCellLst_Item_ExtIEs),
 &flagCz3O,
 0,
 (U8 *) (&czProtExtnCont_ActivatedCellLst_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef czProtExtnCont_ActivatedCellLst_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtExtnCont_ActivatedCellLst_Item_ExtIEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtExtnCont_ActivatedCellLst_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *czActivatedCellLst_ItemTkn[] =
{
 &czECGI,
 &czOptProtExtnCont_ActivatedCellLst_Item_ExtIEs,
  &czProtExtnField_ActivatedCellLst_Item_ExtIEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czActivatedCellLst_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &czActivatedCellLst_ItemTkn[0],
 0
};
 CmPAsnElmDef czActivatedCellLst_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztActivatedCellLst_Item),
 &flagCz3M,
 0,
 (U8 *)(&czActivatedCellLst_Itemspec),
 0L
};
CmPAsnSetSeqOfDef czActivatedCellLstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef czActivatedCellLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztActivatedCellLst),
 &flagCz3M,
 0,
 (U8 *) (&czActivatedCellLstspec),
 0L
};
 CmPAsnElmDef *cz_ValueCellActvnResp_IEsClsInst[] =
{
 &czActivatedCellLst,
  &czActivatedCellLst_Item,
  &czConstTerm,
 &czCriticalityDiag
};
 U32 cz_ValueCellActvnResp_IEsClsInstId[] =
{
 58,
  0xffffffff,
  0xffffffff,
 17
};
 CmPAsnClassInfo cz_ValueCellActvnResp_IEsClsInfo =
{
 4,
 &cz_ValueCellActvnResp_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueCellActvnResp_IEsClsSpec =
{



 &cz_ValueCellActvnResp_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueCellActvnResp_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueCellActvnResp_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueCellActvnResp_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueCellActvnResp_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_CellActvnResp_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueCellActvnResp_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_CellActvnResp_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_CellActvnResp_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_CellActvnResp_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_CellActvnResp_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_CellActvnResp_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_CellActvnResp_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_CellActvnResp_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_CellActvnResp_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_CellActvnResp_IEsspec),
 0L
};
 CmPAsnElmDef *czCellActvnRespTkn[] =
{
 &czProtIE_Cont_CellActvnResp_IEs,
  &czProtIE_Field_CellActvnResp_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCellActvnRespspec =
{



 0,
 0,
 0L,
 0L,
 &czCellActvnRespTkn[0],
 0
};
 CmPAsnElmDef czCellActvnResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCellActvnResp),
 &flagCz3M,
 0,
 (U8 *)(&czCellActvnRespspec),
 0L
};
 CmPAsnElmDef *cz_ValueCellActvnFail_IEsClsInst[] =
{
 &czCause,
 &czCriticalityDiag
};
 U32 cz_ValueCellActvnFail_IEsClsInstId[] =
{
 5,
 17
};
 CmPAsnClassInfo cz_ValueCellActvnFail_IEsClsInfo =
{
 2,
 &cz_ValueCellActvnFail_IEsClsInstId[0]
};
CmPAsnClassIEDef cz_ValueCellActvnFail_IEsClsSpec =
{



 &cz_ValueCellActvnFail_IEsClsInfo,
 (sizeof(CztProtIE_ID) + sizeof(CztCriticality)),
 &cz_ValueCellActvnFail_IEsClsInst[0],



};
 CmPAsnElmDef cz_ValueCellActvnFail_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_ValueCellActvnFail_IEsCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_ValueCellActvnFail_IEsClsSpec)
};
 CmPAsnElmDef *czProtIE_Field_CellActvnFail_IEsTkn[] =
{
 &czProtIE_ID,
 &czCriticality,
 &cz_ValueCellActvnFail_IEsCls,
 &czConstTerm
};
CmPAsnSetSeqDef czProtIE_Field_CellActvnFail_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &czProtIE_Field_CellActvnFail_IEsTkn[0],
 0
};
 CmPAsnElmDef czProtIE_Field_CellActvnFail_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztProtIE_Field_CellActvnFail_IEs),
 &flagCz3M,
 0,
 (U8 *)(&czProtIE_Field_CellActvnFail_IEsspec),
 0L
};
CmPAsnSetSeqOfDef czProtIE_Cont_CellActvnFail_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef czProtIE_Cont_CellActvnFail_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(CztProtIE_Cont_CellActvnFail_IEs),
 &flagCz3M,
 0,
 (U8 *) (&czProtIE_Cont_CellActvnFail_IEsspec),
 0L
};
 CmPAsnElmDef *czCellActvnFailTkn[] =
{
 &czProtIE_Cont_CellActvnFail_IEs,
  &czProtIE_Field_CellActvnFail_IEs,
  &czConstTerm,
 &czExtMkr,
 &czConstTerm
};
CmPAsnSetSeqDef czCellActvnFailspec =
{



 0,
 0,
 0L,
 0L,
 &czCellActvnFailTkn[0],
 0
};
 CmPAsnElmDef czCellActvnFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(CztCellActvnFail),
 &flagCz3M,
 0,
 (U8 *)(&czCellActvnFailspec),
 0L
};
 CmPAsnElmDef *cz_InitiatingMsgClsInst[] =
{
 &czHovrRqst,
 &czResetRqst,
 &czX2SetupRqst,
 &czResStatusRqst,
 &czENBConfigUpd,
 &czMobilityChangeRqst,
 &czCellActvnRqst,
 &czSNStatusTfr,
 &czUECntxtRls,
 &czHovrCancel,
 &czErrInd,
 &czResStatusUpd,
 &czLoadInform,
 &czPrivMsg,
 &czRLFInd,
 &czHovrReport
};
 U32 cz_InitiatingMsgClsInstId[] =
{
 0,
 7,
 6,
 9,
 8,
 12,
 15,
 4,
 5,
 1,
 3,
 10,
 2,
 11,
 13,
 14
};
 CmPAsnClassInfo cz_InitiatingMsgClsInfo =
{
 16,
 &cz_InitiatingMsgClsInstId[0]
};
CmPAsnClassIEDef cz_InitiatingMsgClsSpec =
{



 &cz_InitiatingMsgClsInfo,
 (sizeof(CztProcedureCode) + sizeof(CztCriticality)),
 &cz_InitiatingMsgClsInst[0],



};
 CmPAsnElmDef cz_InitiatingMsgCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_InitiatingMsgCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_InitiatingMsgClsSpec)
};
 CmPAsnElmDef *czInitiatingMsgTkn[] =
{
 &czProcedureCode,
 &czCriticality,
 &cz_InitiatingMsgCls,
 &czConstTerm
};
CmPAsnSetSeqDef czInitiatingMsgspec =
{



 0,
 0,
 0L,
 0L,
 &czInitiatingMsgTkn[0],
 0
};
 CmPAsnElmDef czInitiatingMsg =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztInitiatingMsg),
 &flagCz3M,
 0,
 (U8 *)(&czInitiatingMsgspec),
 0L
};
 CmPAsnElmDef *cz_SuccessfulOutcomeClsInst[] =
{
 &czHovrRqstAckg,
 &czResetResp,
 &czX2SetupResp,
 &czResStatusResp,
 &czENBConfigUpdAckg,
 &czMobilityChangeAckg,
 &czCellActvnResp
};
 U32 cz_SuccessfulOutcomeClsInstId[] =
{
 0,
 7,
 6,
 9,
 8,
 12,
 15
};
 CmPAsnClassInfo cz_SuccessfulOutcomeClsInfo =
{
 7,
 &cz_SuccessfulOutcomeClsInstId[0]
};
CmPAsnClassIEDef cz_SuccessfulOutcomeClsSpec =
{



 &cz_SuccessfulOutcomeClsInfo,
 (sizeof(CztProcedureCode) + sizeof(CztCriticality)),
 &cz_SuccessfulOutcomeClsInst[0],



};
 CmPAsnElmDef cz_SuccessfulOutcomeCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_SuccessfulOutcomeCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_SuccessfulOutcomeClsSpec)
};
 CmPAsnElmDef *czSuccessfulOutcomeTkn[] =
{
 &czProcedureCode,
 &czCriticality,
 &cz_SuccessfulOutcomeCls,
 &czConstTerm
};
CmPAsnSetSeqDef czSuccessfulOutcomespec =
{



 0,
 0,
 0L,
 0L,
 &czSuccessfulOutcomeTkn[0],
 0
};
 CmPAsnElmDef czSuccessfulOutcome =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztSuccessfulOutcome),
 &flagCz3M,
 0,
 (U8 *)(&czSuccessfulOutcomespec),
 0L
};
 CmPAsnElmDef *cz_UnsuccessfulOutcomeClsInst[] =
{
 &czHovrPrepFail,
 &czX2SetupFail,
 &czResStatusFail,
 &czENBConfigUpdFail,
 &czMobilityChangeFail,
 &czCellActvnFail
};
 U32 cz_UnsuccessfulOutcomeClsInstId[] =
{
 0,
 6,
 9,
 8,
 12,
 15
};
 CmPAsnClassInfo cz_UnsuccessfulOutcomeClsInfo =
{
 6,
 &cz_UnsuccessfulOutcomeClsInstId[0]
};
CmPAsnClassIEDef cz_UnsuccessfulOutcomeClsSpec =
{



 &cz_UnsuccessfulOutcomeClsInfo,
 (sizeof(CztProcedureCode) + sizeof(CztCriticality)),
 &cz_UnsuccessfulOutcomeClsInst[0],



};
 CmPAsnElmDef cz_UnsuccessfulOutcomeCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Czt_UnsuccessfulOutcomeCls),
 &flagCz3M,
 0,
 (U8 *)(&cz_UnsuccessfulOutcomeClsSpec)
};
 CmPAsnElmDef *czUnsuccessfulOutcomeTkn[] =
{
 &czProcedureCode,
 &czCriticality,
 &cz_UnsuccessfulOutcomeCls,
 &czConstTerm
};
CmPAsnSetSeqDef czUnsuccessfulOutcomespec =
{



 0,
 0,
 0L,
 0L,
 &czUnsuccessfulOutcomeTkn[0],
 0
};
 CmPAsnElmDef czUnsuccessfulOutcome =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(CztUnsuccessfulOutcome),
 &flagCz3M,
 0,
 (U8 *)(&czUnsuccessfulOutcomespec),
 0L
};
 CmPAsnElmDef *czX2AP_PDUTkn[] =
{
 &czInitiatingMsg,
 &czSuccessfulOutcome,
 &czUnsuccessfulOutcome,
 &czExtMkr,
 &czConstTerm
};
CmPAsnChoiceDef czX2AP_PDUspec =
{



 3,
 0,
 &czX2AP_PDUTkn[0]
};
CmPAsnElmDef czX2AP_PDU =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(CztX2AP_PDU),
 &flagCz3M,
 0L,
 (U8 *)(&czX2AP_PDUspec),
 0L
};
 CmPAsnElmDef *czMsgDb[] =
{
   &czX2AP_PDU,
   0L
};
