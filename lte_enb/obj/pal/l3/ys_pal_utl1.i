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







extern U32 YS_TTI_TMR_VAL_CFG;
extern U16 YS_PORT_ENB;
extern U16 YS_PORT_UE;
extern U8 YS_IP_ADDR_ENB[];
extern U8 YS_IP_ADDR_UE[];


struct timezone
  {
    int tz_minuteswest;
    int tz_dsttime;
  };

typedef struct timezone *__restrict __timezone_ptr_t;
extern int gettimeofday (struct timeval *__restrict __tv,
    __timezone_ptr_t __tz) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int settimeofday (const struct timeval *__tv,
    const struct timezone *__tz)
     __attribute__ ((__nothrow__ , __leaf__));





extern int adjtime (const struct timeval *__delta,
      struct timeval *__olddelta) __attribute__ ((__nothrow__ , __leaf__));




enum __itimer_which
  {

    ITIMER_REAL = 0,


    ITIMER_VIRTUAL = 1,



    ITIMER_PROF = 2

  };



struct itimerval
  {

    struct timeval it_interval;

    struct timeval it_value;
  };




typedef enum __itimer_which __itimer_which_t;






extern int getitimer (__itimer_which_t __which,
        struct itimerval *__value) __attribute__ ((__nothrow__ , __leaf__));




extern int setitimer (__itimer_which_t __which,
        const struct itimerval *__restrict __new,
        struct itimerval *__restrict __old) __attribute__ ((__nothrow__ , __leaf__));




extern int utimes (const char *__file, const struct timeval __tvp[2])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int lutimes (const char *__file, const struct timeval __tvp[2])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int futimes (int __fd, const struct timeval __tvp[2]) __attribute__ ((__nothrow__ , __leaf__));






extern int futimesat (int __fd, const char *__file,
        const struct timeval __tvp[2]) __attribute__ ((__nothrow__ , __leaf__));







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

typedef struct cmHashListCp CmHashListCp;




typedef S16 (* CmHashFunc) (CmHashListCp *hashListCp, U8 *key, U16 keyLen, U16 *idx)
                                                        ;


typedef struct cmListEnt CmListEnt;

struct cmListEnt
{
   CmListEnt *next;
   CmListEnt *prev;
};
typedef struct cmHashListEnt
{
   CmListEnt list;
   U8 *key;
   U16 keyLen;
   U16 hashVal;
} CmHashListEnt;



struct cmHashListCp
{

   CmListEnt *hl;



   Region region;
   Pool pool;
   U16 nmbBins;
   U16 binBitMask;
   U8 nmbBinBits;

   U16 nmbEnt;

   U16 offset;
   Bool dupFlg;
   U16 keyType;
   CmHashFunc hashFunc;
};




extern S16 cmHashListInit ( CmHashListCp *hashListCp, U16 nmbBins, U16 offset, Bool dupFlg, U16 keyType, Region region, Pool pool)






                                 ;

extern S16 cmHashListDeinit ( CmHashListCp *hashListCp)
                                        ;

extern S16 cmHashListInsert ( CmHashListCp *hashListCp, U32 entry, U8 *key, U16 keyLen)



                                   ;

extern S16 cmHashListDelete ( CmHashListCp *hashListCp, U32 entry)

                                  ;

extern S16 cmHashListFind ( CmHashListCp *hashListCp, U8 *key, U16 keyLen, U16 seqNmb, U32 *entry)




                                   ;

extern S16 cmHashListGetNext ( CmHashListCp *hashListCp, U32 prevEnt, U32 *entry)


                                   ;
extern S16 cmHashListQuery ( CmHashListCp *hashListCp, U8 queryType, U16 *result)


                                    ;



extern S16 cmHashListOAInsert ( CmHashListCp *hashListCp, U32 entry, U8 *key, U16 keyLen)



                                   ;
 U8 *cmMemcpy (U8 *tgt, const U8 *src, U32 len);
 S16 cmMemcmp (const U8 *s1, const U8 *s2, U32 len);
 U8 *cmMemset (U8 *src, U8 val, U32 len);

 S16 cmStrcmp (const U8 *s1, const U8 *s2);

 S16 cmStrncmp (const U8 *s1, const U8 *s2, MsgLen len);
 MsgLen cmStrlen (const U8 *s);
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










typedef unsigned long int nfds_t;


struct pollfd
  {
    int fd;
    short int events;
    short int revents;
  };



extern int poll (struct pollfd *__fds, nfds_t __nfds, int __timeout);
extern int ppoll (struct pollfd *__fds, nfds_t __nfds,
    const struct timespec *__timeout,
    const __sigset_t *__ss);









extern int __poll_alias (struct pollfd *__fds, nfds_t __nfds, int __timeout) __asm__ ("" "poll")
                               ;
extern int __poll_chk (struct pollfd *__fds, nfds_t __nfds, int __timeout,
         unsigned int __fdslen);
extern int __poll_chk_warn (struct pollfd *__fds, nfds_t __nfds, int __timeout, unsigned int __fdslen) __asm__ ("" "__poll_chk")


  __attribute__((__warning__ ("poll called with fds buffer too small file nfds entries")));

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
poll (struct pollfd *__fds, nfds_t __nfds, int __timeout)
{
  if (__builtin_object_size (__fds, 2 > 1) != (unsigned int) -1)
    {
      if (! __builtin_constant_p (__nfds))
 return __poll_chk (__fds, __nfds, __timeout, __builtin_object_size (__fds, 2 > 1));
      else if (__builtin_object_size (__fds, 2 > 1) / sizeof (*__fds) < __nfds)
 return __poll_chk_warn (__fds, __nfds, __timeout, __builtin_object_size (__fds, 2 > 1));
    }

  return __poll_alias (__fds, __nfds, __timeout);
}



extern int __ppoll_alias (struct pollfd *__fds, nfds_t __nfds, const struct timespec *__timeout, const __sigset_t *__ss) __asm__ ("" "ppoll")

                                          ;
extern int __ppoll_chk (struct pollfd *__fds, nfds_t __nfds,
   const struct timespec *__timeout,
   const __sigset_t *__ss, unsigned int __fdslen);
extern int __ppoll_chk_warn (struct pollfd *__fds, nfds_t __nfds, const struct timespec *__timeout, const __sigset_t *__ss, unsigned int __fdslen) __asm__ ("" "__ppoll_chk")




  __attribute__((__warning__ ("ppoll called with fds buffer too small file nfds entries")));

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
ppoll (struct pollfd *__fds, nfds_t __nfds, const struct timespec *__timeout,
       const __sigset_t *__ss)
{
  if (__builtin_object_size (__fds, 2 > 1) != (unsigned int) -1)
    {
      if (! __builtin_constant_p (__nfds))
 return __ppoll_chk (__fds, __nfds, __timeout, __ss, __builtin_object_size (__fds, 2 > 1));
      else if (__builtin_object_size (__fds, 2 > 1) / sizeof (*__fds) < __nfds)
 return __ppoll_chk_warn (__fds, __nfds, __timeout, __ss,
     __builtin_object_size (__fds, 2 > 1));
    }

  return __ppoll_alias (__fds, __nfds, __timeout, __ss);
}






struct rpcent
{
  char *r_name;
  char **r_aliases;
  int r_number;
};

extern void setrpcent (int __stayopen) __attribute__ ((__nothrow__ , __leaf__));
extern void endrpcent (void) __attribute__ ((__nothrow__ , __leaf__));
extern struct rpcent *getrpcbyname (const char *__name) __attribute__ ((__nothrow__ , __leaf__));
extern struct rpcent *getrpcbynumber (int __number) __attribute__ ((__nothrow__ , __leaf__));
extern struct rpcent *getrpcent (void) __attribute__ ((__nothrow__ , __leaf__));


extern int getrpcbyname_r (const char *__name, struct rpcent *__result_buf,
      char *__buffer, size_t __buflen,
      struct rpcent **__result) __attribute__ ((__nothrow__ , __leaf__));

extern int getrpcbynumber_r (int __number, struct rpcent *__result_buf,
        char *__buffer, size_t __buflen,
        struct rpcent **__result) __attribute__ ((__nothrow__ , __leaf__));

extern int getrpcent_r (struct rpcent *__result_buf, char *__buffer,
   size_t __buflen, struct rpcent **__result) __attribute__ ((__nothrow__ , __leaf__));














typedef union sigval
  {
    int sival_int;
    void *sival_ptr;
  } sigval_t;
typedef struct sigevent
  {
    sigval_t sigev_value;
    int sigev_signo;
    int sigev_notify;

    union
      {
 int _pad[((64 / sizeof (int)) - 3)];



 __pid_t _tid;

 struct
   {
     void (*_function) (sigval_t);
     pthread_attr_t *_attribute;
   } _sigev_thread;
      } _sigev_un;
  } sigevent_t;






enum
{
  SIGEV_SIGNAL = 0,

  SIGEV_NONE,

  SIGEV_THREAD,


  SIGEV_THREAD_ID = 4

};




struct netent
{
  char *n_name;
  char **n_aliases;
  int n_addrtype;
  uint32_t n_net;
};








extern int *__h_errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern void herror (const char *__str) __attribute__ ((__nothrow__ , __leaf__));


extern const char *hstrerror (int __err_num) __attribute__ ((__nothrow__ , __leaf__));




struct hostent
{
  char *h_name;
  char **h_aliases;
  int h_addrtype;
  int h_length;
  char **h_addr_list;



};






extern void sethostent (int __stay_open);





extern void endhostent (void);






extern struct hostent *gethostent (void);






extern struct hostent *gethostbyaddr (const void *__addr, __socklen_t __len,
          int __type);





extern struct hostent *gethostbyname (const char *__name);
extern struct hostent *gethostbyname2 (const char *__name, int __af);
extern int gethostent_r (struct hostent *__restrict __result_buf,
    char *__restrict __buf, size_t __buflen,
    struct hostent **__restrict __result,
    int *__restrict __h_errnop);

extern int gethostbyaddr_r (const void *__restrict __addr, __socklen_t __len,
       int __type,
       struct hostent *__restrict __result_buf,
       char *__restrict __buf, size_t __buflen,
       struct hostent **__restrict __result,
       int *__restrict __h_errnop);

extern int gethostbyname_r (const char *__restrict __name,
       struct hostent *__restrict __result_buf,
       char *__restrict __buf, size_t __buflen,
       struct hostent **__restrict __result,
       int *__restrict __h_errnop);

extern int gethostbyname2_r (const char *__restrict __name, int __af,
        struct hostent *__restrict __result_buf,
        char *__restrict __buf, size_t __buflen,
        struct hostent **__restrict __result,
        int *__restrict __h_errnop);
extern void setnetent (int __stay_open);





extern void endnetent (void);






extern struct netent *getnetent (void);






extern struct netent *getnetbyaddr (uint32_t __net, int __type);





extern struct netent *getnetbyname (const char *__name);
extern int getnetent_r (struct netent *__restrict __result_buf,
   char *__restrict __buf, size_t __buflen,
   struct netent **__restrict __result,
   int *__restrict __h_errnop);

extern int getnetbyaddr_r (uint32_t __net, int __type,
      struct netent *__restrict __result_buf,
      char *__restrict __buf, size_t __buflen,
      struct netent **__restrict __result,
      int *__restrict __h_errnop);

extern int getnetbyname_r (const char *__restrict __name,
      struct netent *__restrict __result_buf,
      char *__restrict __buf, size_t __buflen,
      struct netent **__restrict __result,
      int *__restrict __h_errnop);




struct servent
{
  char *s_name;
  char **s_aliases;
  int s_port;
  char *s_proto;
};






extern void setservent (int __stay_open);





extern void endservent (void);






extern struct servent *getservent (void);






extern struct servent *getservbyname (const char *__name, const char *__proto);






extern struct servent *getservbyport (int __port, const char *__proto);
extern int getservent_r (struct servent *__restrict __result_buf,
    char *__restrict __buf, size_t __buflen,
    struct servent **__restrict __result);

extern int getservbyname_r (const char *__restrict __name,
       const char *__restrict __proto,
       struct servent *__restrict __result_buf,
       char *__restrict __buf, size_t __buflen,
       struct servent **__restrict __result);

extern int getservbyport_r (int __port, const char *__restrict __proto,
       struct servent *__restrict __result_buf,
       char *__restrict __buf, size_t __buflen,
       struct servent **__restrict __result);




struct protoent
{
  char *p_name;
  char **p_aliases;
  int p_proto;
};






extern void setprotoent (int __stay_open);





extern void endprotoent (void);






extern struct protoent *getprotoent (void);





extern struct protoent *getprotobyname (const char *__name);





extern struct protoent *getprotobynumber (int __proto);
extern int getprotoent_r (struct protoent *__restrict __result_buf,
     char *__restrict __buf, size_t __buflen,
     struct protoent **__restrict __result);

extern int getprotobyname_r (const char *__restrict __name,
        struct protoent *__restrict __result_buf,
        char *__restrict __buf, size_t __buflen,
        struct protoent **__restrict __result);

extern int getprotobynumber_r (int __proto,
          struct protoent *__restrict __result_buf,
          char *__restrict __buf, size_t __buflen,
          struct protoent **__restrict __result);
extern int setnetgrent (const char *__netgroup);







extern void endnetgrent (void);
extern int getnetgrent (char **__restrict __hostp,
   char **__restrict __userp,
   char **__restrict __domainp);
extern int innetgr (const char *__netgroup, const char *__host,
      const char *__user, const char *__domain);







extern int getnetgrent_r (char **__restrict __hostp,
     char **__restrict __userp,
     char **__restrict __domainp,
     char *__restrict __buffer, size_t __buflen);
extern int rcmd (char **__restrict __ahost, unsigned short int __rport,
   const char *__restrict __locuser,
   const char *__restrict __remuser,
   const char *__restrict __cmd, int *__restrict __fd2p);
extern int rcmd_af (char **__restrict __ahost, unsigned short int __rport,
      const char *__restrict __locuser,
      const char *__restrict __remuser,
      const char *__restrict __cmd, int *__restrict __fd2p,
      sa_family_t __af);
extern int rexec (char **__restrict __ahost, int __rport,
    const char *__restrict __name,
    const char *__restrict __pass,
    const char *__restrict __cmd, int *__restrict __fd2p);
extern int rexec_af (char **__restrict __ahost, int __rport,
       const char *__restrict __name,
       const char *__restrict __pass,
       const char *__restrict __cmd, int *__restrict __fd2p,
       sa_family_t __af);
extern int ruserok (const char *__rhost, int __suser,
      const char *__remuser, const char *__locuser);
extern int ruserok_af (const char *__rhost, int __suser,
         const char *__remuser, const char *__locuser,
         sa_family_t __af);
extern int iruserok (uint32_t __raddr, int __suser,
       const char *__remuser, const char *__locuser);
extern int iruserok_af (const void *__raddr, int __suser,
   const char *__remuser, const char *__locuser,
   sa_family_t __af);
extern int rresvport (int *__alport);
extern int rresvport_af (int *__alport, sa_family_t __af);






struct addrinfo
{
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  socklen_t ai_addrlen;
  struct sockaddr *ai_addr;
  char *ai_canonname;
  struct addrinfo *ai_next;
};



struct gaicb
{
  const char *ar_name;
  const char *ar_service;
  const struct addrinfo *ar_request;
  struct addrinfo *ar_result;

  int __return;
  int __glibc_reserved[5];
};
extern int getaddrinfo (const char *__restrict __name,
   const char *__restrict __service,
   const struct addrinfo *__restrict __req,
   struct addrinfo **__restrict __pai);


extern void freeaddrinfo (struct addrinfo *__ai) __attribute__ ((__nothrow__ , __leaf__));


extern const char *gai_strerror (int __ecode) __attribute__ ((__nothrow__ , __leaf__));





extern int getnameinfo (const struct sockaddr *__restrict __sa,
   socklen_t __salen, char *__restrict __host,
   socklen_t __hostlen, char *__restrict __serv,
   socklen_t __servlen, int __flags);
extern int getaddrinfo_a (int __mode, struct gaicb *__list[__restrict],
     int __ent, struct sigevent *__restrict __sig);
extern int gai_suspend (const struct gaicb *const __list[], int __ent,
   const struct timespec *__timeout);


extern int gai_error (struct gaicb *__req) __attribute__ ((__nothrow__ , __leaf__));


extern int gai_cancel (struct gaicb *__gaicbp) __attribute__ ((__nothrow__ , __leaf__));







typedef CmIpAddr CmInetIpAddr;




typedef struct cmInetIpAddrTbl
{
   U16 count;
   CmInetIpAddr netAddr[16];
}CmInetIpAddrTbl;

typedef CmInetIpAddrTbl CmInetIpv4AddrArr;
typedef struct cmInetIpAddrArr
{
   U8 type;
   union
   {
      CmInetIpv4AddrArr ipv4AddrArr;



   } u;

} CmInetIpAddrArr;



typedef struct cmInetCmnSockAddr
{
   U32 type;
   U32 len;
   union
   {
      struct sockaddr_in addr;



   }u;
}CmInetCmnSockAddr;
typedef S32 CmInetFdType;
typedef struct pollfd CmInetPollFd;

typedef struct cmInetFd
{
   CmInetFdType fd;
   U8 blocking;
   U8 type;




}CmInetFd;

typedef fd_set CmInetFdSet;
typedef struct cmInetAddr1
{
   U16 port;
   CmInetIpAddr address;
} CmInetAddr;
typedef CmInetAddr CmInetIpv4Addr;


typedef struct cmInetMemInfo
{
   Region region;
   Pool pool;
} CmInetMemInfo;

typedef struct cmInetMCastInf
{
   CmInetIpAddr mCastAddr;
   CmInetIpAddr localAddr;
}CmInetMCastInf;



typedef struct cmInetNetAddr
{
   U8 type;
   union
   {
      CmInetIpAddr ipv4NetAddr;



   }u;
} CmInetNetAddr;
typedef struct cmInetIpv4HdrParm
{
   TknU8 proto;
   TknU8 dfBit;
   TknU8 tos;
   TknU8 ttl;




} CmInetIpv4HdrParm;
typedef struct cmInetIpHdrParm
{
   U8 type;
   union
   {
      CmInetIpv4HdrParm hdrParmIpv4;



   } u;
} CmInetIpHdrParm;
typedef struct cmInetFdSetInfo
{
   Bool initDone;
   Bool bigEndian;
   U16 arIdx;
   U32 numArElems;
   U8 ar[256];
} CmInetFdSetInfo;
typedef struct iovec CmInetIovec;



typedef struct sockaddr CmInetSockAddr;
typedef struct sockaddr_in6 CmInet6SockAddr;
typedef struct sockaddr_in CmInet4SockAddr;




typedef struct addrinfo CmInetAddrInfo;
extern S16 cmInetSocket (U8 type, CmInetFd *sockFd, U8 protocol);
extern S16 cmInetBind (CmInetFd *sockFd, CmInetAddr *myAddr);
extern S16 cmInetConnect (CmInetFd *sockFd, CmInetAddr *servAddr);
extern S16 cmInetListen (CmInetFd *sockFd, S16 backLog);
extern S16 cmInetAccept (CmInetFd *sockFd, CmInetAddr *fromAddr, CmInetFd *newSockFd)
                                                   ;
extern S16 cmInetRecvMsg (CmInetFd *sockFd, CmInetAddr *dstAddr, CmInetMemInfo *info, Buffer **mPtr, MsgLen *len, S32 flags)

                                                       ;


extern S16 cmInetSendDscpMsg (CmInetFd *sockFd, CmInetAddr *dstAddr, CmInetMemInfo *info, Buffer *mBuf, MsgLen *len, CmInetIpHdrParm *ipHdrParams, S16 flags)

                                                                        ;






extern S16 cmInetSendMsg (CmInetFd *sockFd, CmInetAddr *dstAddr, CmInetMemInfo *info, Buffer *mBuf, MsgLen *len, S16 flags)

                                          ;

extern S16 cmInetPeek (CmInetFd *sockFd, CmInetAddr *fromAddr, CmInetMemInfo *info, MsgLen dataPos, MsgLen dataLen, U8 *data)

                                                      ;

extern S16 cmInetPeekNew (CmInetFd *sockFd, CmInetAddr *fromAddr, CmInetMemInfo *info, MsgLen dataPos, MsgLen dataLen, U8 *data)

                                                      ;
extern S16 cmInetClose (CmInetFd *sockFd);
extern S16 cmInetShutdown (CmInetFd *sockFd, S32 howTo);
extern S16 cmInetSelect (CmInetFdSet *readFdS, CmInetFdSet *writeFdS, U32 *mSecTimeout, S16 *numFdS)
                                                             ;
extern S16 cmInetSetOpt (CmInetFd *sockFd, U32 level, U32 type, Ptr value)
                                        ;
extern S16 cmInetGetNumRead (CmInetFd *sockFd, U32 *dataLen);

extern S16 cmInetGetHostByName (S8 *hostName, CmInetIpAddrTbl *addrTbl);
extern S16 cmInetGetIpNodeByName (S8 *hostName, CmInetIpAddrArr *addrArr);
extern S16 cmInetAddr (S8 *asciiAddr, CmInetIpAddr *address);
extern S16 cmInetNtoa (CmInetIpAddr address, S8 **asciiAddr);
extern S16 cmInetPton (CmInetIpAddr *address, S8 *asciiAddr);







extern S16 cmInetFdSetInfoInit (CmInetFdSetInfo *fdSetInfo);
extern S16 cmInetGetFd (CmInetFdSetInfo *fdSetInfo, CmInetFdSet *fdSet, CmInetFdType *sockFd)
                                                   ;


extern S16 cmInetGetMemSize (S32 *size);
extern S16 cmInetInit (Void);
extern S16 cmInetDeInit (Void);
extern S16 cmInetGetSockName (CmInetFd *sockFd, CmInetAddr *locAddr);

extern S16 cmInetConvertStrToIpAddr (U16 len, U8 *val, CmInetNetAddr *address)
                                                                  ;
extern S16 cmInetAsciiToIpv4 (U8 numBytes, U8 *ipv4Addr, U16 len, U8 *val)
                                                     ;



extern S16 cmInetPoll (CmInetPollFd *pollFdArr,U32 idx,S16 *numFdS,U32 timeout);
extern S16 cmInetPollSetFd (CmInetFd *sockFd,CmInetPollFd *pollFdArr,S16 idx, U16 eventMask);
extern S16 cmInetPollFdIsSet (CmInetPollFd *pollFdArr, S16 idx, U16 eventMask);
extern S16 cmInetPollClearFdREvent (CmInetPollFd *pollFdArr, S16 idx, U16 eventMask);
extern S16 cmInetPollClearFdEvent (CmInetPollFd *pollFdArr,S16 idx, U16 eventMask);
extern S16 cmInetPollDelFd (CmInetPollFd *pollFdArr, S16 delIdx, S16 crntIdx);
extern S16 cmInetPollInitFdArr (CmInetPollFd *pollFdArr);
extern S16 cmInetNtop (U8 type,Void *address,S8 *asciiAddr,U32 len);





extern S32 cmInetGetAddrInfo (const S8* node, const S8* service, const CmInetAddrInfo *hints, CmInetAddrInfo **res)
                                                                                         ;
extern Void cmInetFreeAddrInfo (CmInetAddrInfo *res);
typedef U8 CmLteRbId;


typedef U16 CmLteCellId;


typedef U16 CmLteRnti;


typedef U8 CmLteRlcMode;


typedef U8 CmLteLcId;


typedef U8 CmLteLcType;


typedef U8 CmLteTrchType;


typedef U8 CmLteContResId[6];


typedef struct cmLteRlcId
{
  CmLteRbId rbId;
  U8 rbType;
  CmLteRnti ueId;
  CmLteCellId cellId;
}CmLteRlcId;


typedef struct cmLteTimingInfo
{
   U16 sfn;
   U8 subframe;
} CmLteTimingInfo;


typedef struct cmLtePdcpId
{
   CmLteCellId cellId;
   CmLteRnti ueId;
   CmLteRbId rbId;
   U8 rbType;
} CmLtePdcpId;


typedef struct cmLtePoolInfo
{
   U32 poolSize;
   U32 totAvailable;
   U32 crntUsed;
   U32 maxUsed;
} CmLtePoolInfo;

typedef struct cmLteRegionInfo
{
   U8 regionType;
   U8 regionId;
   U8 numPools;
   U8 isGenMemInfoUpdated;
   CmLtePoolInfo poolInfo[6];
}CmLteRegionInfo;

typedef struct cmLteMemInfo
{
   U8 numRegions;
   U8 idx;
   CmLteRegionInfo regInfo[5];
}CmLteMemInfo;


typedef struct cmLteCpuUtilInfo
{
   U32 avgCpuUtil;
   U32 maxCpuUtil;
}CmLteCpuUtilInfo;


typedef struct cmLteCpuInfo
{
   U8 numCores;
   CmLteCpuUtilInfo cpuUtil[10];
}CmLteCpuInfo;

typedef struct cmCpuUtilStatsInfo
{
   U32 numSamples;
   U32 maxCpuUtil;
   U32 totCpuUtil;
}CmCpuUtilStatsInfo;


typedef struct cmCpuStatsInfo
{
   U8 numCores;
   CmCpuUtilStatsInfo cpuUtil[10];
}CmCpuStatsInfo;





typedef U32 CntrSts;


typedef enum cmLteAggrLvl
{
   CM_LTE_AGGR_LVL1 = 1,
   CM_LTE_AGGR_LVL2 = 2,
   CM_LTE_AGGR_LVL4 = 3,
   CM_LTE_AGGR_LVL8 = 4
} CmLteAggrLvl;


typedef enum cmLteUeCategory
{
   CM_LTE_UE_CAT_1 = 1,
   CM_LTE_UE_CAT_2,
   CM_LTE_UE_CAT_3,
   CM_LTE_UE_CAT_4,
   CM_LTE_UE_CAT_5,
   CM_LTE_UE_CAT_6,
   CM_LTE_UE_CAT_7,
   CM_LTE_UE_CAT_8
} CmLteUeCategory;





extern S16 cmUpdateSsiMemInfo(CmLteMemInfo *mInfo);

extern S16 cmFillMemUtilizationMeas(CmLteMemInfo *memoryInfo,CmLteMemInfo *memInfo);

extern S16 cmClearMemUtilizationCounter(CmLteMemInfo *memInfo);
extern S16 UpdateSocMemInfo(U8 area , CmLteMemInfo *mInfo);

extern S16 cmFillCpuUtilizationMeas(CmLteCpuInfo *cpuMeasInfo,CmCpuStatsInfo *cpuInfo);

extern S16 cmClearCpuUtilizationCounter(CmCpuStatsInfo *cpuInfo);
extern Void UpdateSocCpuInfo(CmCpuStatsInfo *cpuInfo,U8 Idx);

extern S16 SGetRegPoolInfo(U8* numRegion, U8* numPool);


extern S16 cmPkLteRlcId ( CmLteRlcId *param, Buffer *mBuf )


  ;

extern S16 cmPkLteTimingInfo ( CmLteTimingInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkLtePdcpId ( CmLtePdcpId *param, Buffer *mBuf )


  ;


extern S16 cmUnpkLteRlcId ( CmLteRlcId *param, Buffer *mBuf )


  ;

extern S16 cmUnpkLteTimingInfo ( CmLteTimingInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkLtePdcpId ( CmLtePdcpId *param, Buffer *mBuf )


  ;



typedef struct cmTtiProc
{
 U32 totTtiProcessingTime;
 U32 numOfTti;
 U32 maxTtiProcessingTime;
 U32 ttiStretchCount;
 U32 ttiThresholdExceedCount;

 U32 phyReptTtiStretchCount;
}CmTtiProc;

extern CmTtiProc ttiProc;

extern Void cmUpdateTtiCounters(U32 ttiProcessingTime);
extern Void cmResetTtiCounters(Void);
typedef struct ctfCfgTransId {
   U8 trans[9];
} CtfCfgTransId;






typedef enum {
   CTF_BW_RB_6,
   CTF_BW_RB_15,
   CTF_BW_RB_25,
   CTF_BW_RB_50,
   CTF_BW_RB_75,
   CTF_BW_RB_100
} CtfBandwidth;





typedef enum {
   CTF_DUPMODE_FDD=1,
   CTF_DUPMODE_TDD
} CtfDuplexMode;





typedef enum {
   CTF_SC_SPACING_15KHZ,
   CTF_SC_SPACING_7DOT5KHZ
} CtfSCSpacing;





typedef enum {
   CTF_CP_NORMAL,
   CTF_CP_EXTENDED
} CtfCPCfg;





typedef enum {
   CTF_AP_CNT_1 = 1,
   CTF_AP_CNT_2 = 2,
   CTF_AP_CNT_4 = 4
} CtfAntennaPortsCount;





typedef enum {
   CTF_PHICH_DUR_NORMAL,
   CTF_PHICH_DUR_EXTENDED
} CtfPhichDuration;





typedef enum {
   CTF_PHICH_RSRC_ONESIXTH,
   CTF_PHICH_RSRC_HALF,
   CTF_PHICH_RSRC_ONE,
   CTF_PHICH_RSRC_TWO
} CtfPhichResource;





typedef enum {
   CTF_PUSCH_HOPMODE_INTER_SUBFRM,
   CTF_PUSCH_HOPMODE_INTRAANDINTERSUBFRM
} CtfPuschHoppingMode;





typedef enum {
   CTF_PUCCH_DELTASHIFT1,
   CTF_PUCCH_DELTASHIFT2,
   CTF_PUCCH_DELTASHIFT3
} CtfPucchDeltaShift;






typedef enum {
   CTF_PDSCH_PA_MINUS_6,
   CTF_PDSCH_PA_MINUS_4DOT77,
   CTF_PDSCH_PA_MINUS_3,
   CTF_PDSCH_PA_MINUS_1DOT77,
   CTF_PDSCH_PA_ZERO,
   CTF_PDSCH_PA_ONE,
   CTF_PDSCH_PA_TWO,
   CTF_PDSCH_PA_THREE
} CtfPdschPaParam;





typedef enum {
   CTF_CQI_RPT_MODE_APERIODIC_RM12,
   CTF_CQI_RPT_MODE_APERIODIC_RM20,
   CTF_CQI_RPT_MODE_APERIODIC_RM22,
   CTF_CQI_RPT_MODE_APERIODIC_RM30,
   CTF_CQI_RPT_MODE_APERIODIC_RM31
} CtfCqiRptModeAperiodic;





typedef enum {
   CTF_UE_TX_ANT_SELECT_CLOSEDLOOP,
   CTF_UE_TX_ANT_SELECT_OPENLOOP
} CtfUeTxAntSelectType;





typedef enum {
   CTF_PUCCH_REP_FACTOR_N2,
   CTF_PUCCH_REP_FACTOR_N4,
   CTF_PUCCH_REP_FACTOR_N6
} CtfPucchRepFactor;
 typedef enum {
    CTF_PUCCH_TDD_ACKNACK_FB_MODE_BUNDLING,
    CTF_PUCCH_TDD_ACKNACK_FB_MODE_MUXING
 } CtfTddAckNackFBMode;






typedef enum {
   CTF_UE_TX_ANT_MODE_TM1,
   CTF_UE_TX_ANT_MODE_TM2,
   CTF_UE_TX_ANT_MODE_TM3,
   CTF_UE_TX_ANT_MODE_TM4,
   CTF_UE_TX_ANT_MODE_TM5,
   CTF_UE_TX_ANT_MODE_TM6,
   CTF_UE_TX_ANT_MODE_TM7




} CtfUeTxAntMode;





typedef enum {
   CTF_MAJOR_RECFG,
   CTF_MINOR_RECFG
} CtfReCfgType;





typedef struct ctfUeInfo {
   CmLteCellId cellId;
   CmLteRnti ueId;
}CtfUeInfo;







typedef struct ctfBwCfgInfo {
   Bool pres;
   CtfBandwidth dlBw;
   CtfBandwidth ulBw;
   U8 eUtraBand;

} CtfBwCfgInfo;





typedef struct ctfTxSchemeCfg {
   Bool pres;
   CtfDuplexMode duplexMode;
   CtfSCSpacing scSpacing;
   CtfCPCfg cycPfx;
} CtfTxSchemeCfg;






typedef struct ctfAntennaCfgInfo {
   CtfAntennaPortsCount antPortsCnt;
} CtfAntennaCfgInfo;
typedef struct ctfPrachCfgInfo {
   Bool pres;
   U16 rootSequenceIndex;
   U8 prachCfgIndex;
   U8 zeroCorrelationZoneCfg;

   Bool highSpeedFlag;

   U8 prachFreqOffset;
} CtfPrachCfgInfo;






typedef struct ctfPdschCfgInfo {
   Bool pres;
   S16 refSigPwr;

   U8 p_b;
} CtfPdschCfgInfo;






typedef struct ctfPuschCfgBasic {
   U8 noOfsubBands;
   CtfPuschHoppingMode hoppingMode;
   U8 hoppingOffset;
   Bool enable64QAM;

} CtfPuschCfgBasic;






typedef struct ctfPuschUlRS {
   Bool grpHopEnabled;
   Bool seqHopEnabled;
   U8 grpNum;
   U8 cycShift;
} CtfPuschUlRS;






typedef struct ctfPuschCfgInfo {
   Bool pres;
   CtfPuschCfgBasic puschBasicCfg;
   CtfPuschUlRS puschUlRS;
} CtfPuschCfgInfo;






typedef struct ctfPhichCfgInfo {
   Bool pres;

   CtfPhichDuration duration;

   CtfPhichResource resource;
} CtfPhichCfgInfo;






typedef struct ctfPucchCfgInfo {
   Bool pres;
   U8 nRB;

   U8 nCS;
   U16 n1PUCCH;
   CtfPucchDeltaShift deltaShift;
} CtfPucchCfgInfo;






typedef struct ctfSrsUlCfgInfo {
   Bool pres;
   U8 srsCfgType;

   struct srsSetupS
   {
      U8 srsBw;
      U8 sfCfg;
      Bool srsANSimultTx;

      Bool srsMaxUpPts;

   } srsSetup;
} CtfSrsUlCfgInfo;






typedef struct ctfTddSfCfgInfo {
   Bool pres;
   U8 sfAssignment;

   U8 spclSfPatterns;

} CtfTddSfCfgInfo;
typedef struct ctfVendorSpecific{
  U16 buffLen ;
  U8 *paramBuffer ;
} CtfVendorSpecific;
typedef struct ctfCellCfgInfo {
   CmLteCellId cellId;
   U8 cellIdGrpId;
   SpId macSapId;
   SpId schSapId;

   Bool physCellIdPres ;
   U8 physCellId;
   CtfBwCfgInfo bwCfg;
   CtfTxSchemeCfg txCfg;

   CtfAntennaCfgInfo antennaCfg;
   CtfPrachCfgInfo prachCfg;
   CtfPdschCfgInfo pdschCfg;
   CtfPuschCfgInfo puschCfg;
   CtfPhichCfgInfo phichCfg;
   CtfPucchCfgInfo pucchCfg;
   CtfSrsUlCfgInfo srsUlCfg;
   CtfTddSfCfgInfo tddSfCfg;


   U16 syncSigPowOs;
   Bool syncSigPowOsPres;
   U16 cfiPowOs;
   Bool cfiPowOsPres;
   U16 dciPowOs;
   Bool dciPowOsPres;
   U16 extWinMargin;
   Bool extWinMarginPres;
   U16 pucchNoiseGamma;
   Bool pucchNoiseGammaPres;
   U16 prachPkRatio4;
   Bool prachPkRatio4Pres;
   U16 prachPkRatio0;
   Bool prachPkRatio0Pres;
   U16 srsDopEstFactor;
   Bool srsDopEstFactorPres;
   U16 puschProbDtxAck;
   Bool puschProbDtxAckPres;
   U16 pucchProbDtxAck;
   Bool pucchProbDtxAckPres;

   U16 txAntennaPorts ;
   Bool txAntennaPortsPres;
   U16 rxAntennaPorts ;
   Bool rxAntennaPortsPres ;

   U16 phySyncMode;
   Bool phySyncModePres;
   U16 dataRepMode;
   Bool dataRepModePres ;
   U16 rachSrRepMode;
   Bool rachSrRepModePres;

   U16 opMode;
   U32 counter;
   U32 period;
   S16 priSigPwr;
   S16 secSigPwr;
   U16 dlEarfcn;
   U16 ulEarfcn;

   S16 pilotSigPwr;


   U8 numDlUePerTti;




} CtfCellCfgInfo;





typedef enum {
   CTF_CELL_DOWN,
   CTF_CELL_UP
} CtfCellStatus;






typedef struct ctfCellRecfgInfo {
   CtfReCfgType ctfReCfgType ;
   CmLteCellId cellId;

   U8 cellIdGrpId;
   Bool physCellIdPres ;
   U8 physCellId;
   CtfBwCfgInfo bwCfg;
   CtfTxSchemeCfg txCfg;

   CtfAntennaCfgInfo antennaCfg;
   CmLteTimingInfo actvnTime;
   CtfPrachCfgInfo prachCfg;
   CtfPdschCfgInfo pdschCfg;
   CtfPuschCfgInfo puschCfg;
   CtfPhichCfgInfo phichCfg;
   CtfPucchCfgInfo pucchCfg;
   CtfSrsUlCfgInfo srsUlCfg;
   CtfTddSfCfgInfo tddSfCfg;

   U16 syncSigPowOs;
   Bool syncSigPowOsPres;
   U16 cfiPowOs;
   Bool cfiPowOsPres;
   U16 dciPowOs;
   Bool dciPowOsPres;
   U16 extWinMargin;
   Bool extWinMarginPres;
   U16 pucchNoiseGamma;
   Bool pucchNoiseGammaPres;
   U16 prachPkRatio4;
   Bool prachPkRatio4Pres;
   U16 prachPkRatio0;
   Bool prachPkRatio0Pres;
   U16 srsDopEstFactor;
   Bool srsDopEstFactorPres;
   U16 puschProbDtxAck;
   Bool puschProbDtxAckPres;
   U16 pucchProbDtxAck;
   Bool pucchProbDtxAckPres;

   U16 txAntennaPorts ;
   Bool txAntennaPortsPres;
   U16 rxAntennaPorts ;
   Bool rxAntennaPortsPres ;

   U16 phySyncMode;
   Bool phySyncModePres;
   U16 dataRepMode;
   Bool dataRepModePres ;
   U16 rachSrRepMode;
   Bool rachSrRepModePres;

   S16 pilotSigPwr;
   S16 priSigPwr;
   S16 secSigPwr;

   CtfCellStatus ctfCellStatus;
} CtfCellRecfgInfo;
typedef struct ctfDedPdschCfgInfo {
   Bool pres;
   CtfPdschPaParam pA;
} CtfDedPdschCfgInfo;






typedef struct ctfDedPucchCfgInfo {
   Bool pres;
   U8 dedPucchCfgType;
   struct pucchSetupS
   {


      Bool repFactPres;


      CtfPucchRepFactor repFact;
      U16 n1PUCCHRep;


   } pucchSetup;


    Bool tddAckNackCfgPres;

    CtfTddAckNackFBMode tddAckNackFBMode;


} CtfDedPucchCfgInfo;






typedef struct ctfDedPuschCfgInfo {
   Bool pres;
   U8 betaOffsetAckIdx;

   U8 betaOffsetRiIdx;

   U8 betaOffsetCqiIdx;

} CtfDedPuschCfgInfo;
typedef struct ctfDedAntCfgInfo {
   Bool pres;
   CtfUeTxAntMode txMode;
   struct ueTxAntSelectionS
   {
      U8 cfgType;
      CtfUeTxAntSelectType txAntSelect;

   } ueTxAntSelection;




} CtfDedAntCfgInfo;






typedef struct ctfUeCatCfgInfo {
   Bool pres;
   CmLteUeCategory ueCategory;
} CtfUeCatCfgInfo;


typedef struct ctfHdr{
   CmLteCellId cellId;
   CmLteRnti ueId;
}CtfHdr;






typedef struct ctfKenbCfgInfo{
           U8 pres;
           U8 algoType;
           U8 secKey[32];
}CtfKenbCfgInfo;
typedef struct ctfDedCfgInfo {
   CmLteCellId cellId;
   CmLteRnti ueId;
   CtfUeCatCfgInfo ueCatCfg;
   CtfDedPdschCfgInfo pdschCfg;
   CtfDedPucchCfgInfo pucchCfg;
   CtfDedPuschCfgInfo puschCfg;





   CtfDedAntCfgInfo antInfo;
} CtfDedCfgInfo;


typedef struct ctfUeSecCellCfgInfo
{
  U8 sCellIdx;
  U16 sCellId;
}CtfUeSecCellCfgInfo;


typedef enum ctfScellAction
{
   CTF_SCELL_ADD,
   CTF_SCELL_MOD_COMMON,
   CTF_SCELL_MOD_DEDICATED,
   CTF_SCELL_RELEASE
}CtfScellAction;


typedef struct ctfSecCellCfgInfo
{
  U8 numSCells;
  CtfScellAction sCellAction;
  CtfUeSecCellCfgInfo ueSCellDedCfg[7];
}CtfSecCellCfgInfo;






typedef struct ctfDedRecfgInfo {
   CmLteCellId cellId;
   CmLteRnti ueId;


   CmLteRnti newUeId;
   CtfUeCatCfgInfo ueCatCfg;
   CtfDedPdschCfgInfo pdschCfg;
   CtfDedPucchCfgInfo pucchCfg;
   CtfDedPuschCfgInfo puschCfg;






   CtfDedAntCfgInfo antInfo;

   CtfSecCellCfgInfo sCellInfo;
} CtfDedRecfgInfo;






typedef struct ctfCellReleaseInfo {
   CmLteCellId cellId;
} CtfCellReleaseInfo;






typedef struct ctfDedReleaseInfo {
   CmLteCellId cellId;
   CmLteRnti ueId;
   CtfSecCellCfgInfo sCellInfo;
} CtfDedReleaseInfo;






typedef struct ctfCfgInfo {
   U8 cfgElem;
   union
   {
      CtfCellCfgInfo cellCfg;
      CtfDedCfgInfo dedCfg;
   } u;
} CtfCfgInfo;






typedef struct ctfReCfgInfo {
   U8 cfgElem;
   union
   {
      CtfCellRecfgInfo cellRecfg;
      CtfDedRecfgInfo dedRecfg;
   } u;
} CtfReCfgInfo;






typedef struct ctfReleaseInfo {
   U8 cfgElem;
   union
   {
      CtfCellReleaseInfo cellRel;
      CtfDedReleaseInfo dedRel;
   } u;
} CtfReleaseInfo;
typedef struct ctfCfgReqInfo {
   U8 cfgType;
   union
   {
      CtfCfgInfo cfg;
      CtfReCfgInfo reCfg;
      CtfReleaseInfo release;
   } u;


   CtfVendorSpecific vendorParams ;

} CtfCfgReqInfo;







typedef struct ctfAsKeyInfo{
           U8 intgAlgoType;
           U8 ciphAlgoType;
           U8 secKey[32];
}CtfAsKeyInfo;


typedef struct ctfKenbStarInfo{
           U16 dlCarrFreq;
           U16 physCellId;
           U8 secKey[32];
}CtfKenbStarInfo;


typedef struct ctfNhKeyInfo{
           U16 dlCarrFreq;
           U16 physCellId;
           U8 secKey[32];
}CtfNhKeyInfo;

typedef struct ctfKdfReqInfo {
   U8 keyDerType;
   union
   {
      CtfAsKeyInfo kEnbInf;
      CtfKenbStarInfo kEnbStarInf;
      CtfNhKeyInfo nhKeyInf;
   } u;
} CtfKdfReqInfo;
typedef struct ctfAskeyCfmInfo{
          U8 intKey[32];
          U8 upCiphKey[32];
          U8 cpCiphKey[32];
}CtfAskeyCfmInfo;


typedef struct ctfKenbStarCfmInfo{
           U8 secKey[32];
}CtfKenbStarCfmInfo;


typedef struct ctfNhKeyCfmInfo{
           U8 secKey[32];
}CtfNhKeyCfmInfo;

typedef struct ctfKdfCfmInfo {
   U8 keyDerType;
   union
   {
      CtfAskeyCfmInfo kEnbInf;
      CtfKenbStarCfmInfo kEnbStarInf;
      CtfNhKeyCfmInfo nhKeyInf;
   } u;
} CtfKdfCfmInfo;






typedef struct ctfCnmVendorSpecificInfo{
 U16 numOfVendorSpecifcParam;
 U32 vendorSpecifcParam[8];
}CtfCnmVendorSpecificInfo;



typedef struct ctfCnmCellSyncReq {
 U16 nbrEarfcn;
 U16 nbrPCellId;
 U8 nbrTxAntCount;

    U8 nbrCellCp;

    U8 nbrCellNRb;

    U8 nbrSpecSfCfg;
    CtfCnmVendorSpecificInfo ctfCnmVendorSpecificInfo;
}CtfCnmCellSyncReq;


typedef struct ctfCnmInitSyncReq {
 U8 searchType;


 U8 mibRequest;


 U16 earfcn;
 U8 measBandWidth;
 U16 numOfPciList;
 CtfCnmCellSyncReq pciList[16];
}CtfCnmInitSyncReq;







typedef struct ctfCnmMibInfo {
 U16 sfn;
 U8 numTxAntennas;
 U8 phichDuration;
 U8 phichResource;
 U8 dlSystemBandWidht;

}CtfCnmMibInfo;


typedef struct ctfCnmInitSyncInfo {
 U16 pci;
 U8 rsrp;
 U8 mibValidFlag;
 U16 localSfn;
 CtfCnmMibInfo ctfCnmMibInfo;
    CtfCnmVendorSpecificInfo ctfCnmVendorSpecificInfo;
}CtfCnmInitSyncInfo;


typedef struct ctfCnmInitSyncRsp {
 U8 status;
 U16 earfcn;
 U8 numOfNeighbourInfo;
 CtfCnmInitSyncInfo ctfCnmInitSyncInfo[16];
}CtfCnmInitSyncRsp;

typedef struct ctfCnmCellSyncRsp {
 U8 status;
}CtfCnmCellSyncRsp;

typedef struct ctfCnmCellSyncInd {
 U8 status;
    CtfCnmVendorSpecificInfo ctfCnmVendorSpecificInfo;
}CtfCnmCellSyncInd;


typedef struct ctfPeriodicRemCellInfo {
   U16 pci;
   U8 rsrp;
   U8 dlBw;
   U8 numTx;
}CtfPeriodicRemCellInfo;

typedef struct ctfPeriodicRemCellSearchRsp {
   U8 numCells;
   CtfPeriodicRemCellInfo cellInfo[16];
}CtfPeriodicRemCellSearchRsp;
typedef S16 (*CtfBndReq) ( Pst* pst, SuId suId, SpId spId)


                              ;



typedef S16 (*CtfBndCfm) ( Pst* pst, SuId suId, U8 status)


                                ;


typedef S16 (*CtfUbndReq) ( Pst* pst, SpId spId, Reason reason)


                                ;



typedef S16 (*CtfCfgReq) ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfCfgReqInfo* cfgReqInfo)



                                    ;


typedef S16 (*CtfCfgCfm) ( Pst* pst, SuId suId, CtfCfgTransId transId, U8 status)



                                ;


typedef S16 (*CtfEnbStopInd) ( Pst* pst, SuId suId, CtfCfgTransId transId)


                                 ;


typedef S16 (*CtfKdfReq) ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfKdfReqInfo* cfgReqInfo)



                                    ;


typedef S16 (*CtfKdfCfm) ( Pst* pst, SuId suId, CtfCfgTransId transId, CtfKdfCfmInfo* kdfCfmInfo, U8 status)




                                ;


typedef S16 (*CtfCnmInitSyncReqMsg) ( Pst* pst, SpId spId, CtfCfgTransId* transId, CtfCnmInitSyncReq* cnmInitSyncReq)



                                         ;

typedef S16 (*CtfCnmInitSyncRspMsg) ( Pst* pst, SpId spId, CtfCfgTransId* transId, CtfCnmInitSyncRsp* cnmInitSyncRsp)



                                        ;

typedef S16 (*CtfCnmCellSyncReqMsg) ( Pst* pst, SpId spId, CtfCfgTransId* transId, CtfCnmCellSyncReq* cnmCellSyncReq)



                                        ;

typedef S16 (*CtfCnmCellSyncRspMsg) ( Pst* pst, SpId spId, CtfCfgTransId* transId, CtfCnmCellSyncRsp* cnmCellSyncRsp)



                                        ;

typedef S16 (*CtfCnmCellSyncIndMsg) ( Pst* pst, SpId spId, CtfCfgTransId* transId, CtfCnmCellSyncInd* cnmCellSyncInd)



                                        ;




typedef S16 (*CtfUeIdChgReq) ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfUeInfo * ueInfo, CtfUeInfo * newUeInfo)




                                   ;


typedef S16 (*CtfUeIdChgCfm) ( Pst* pst, SuId suId, CtfCfgTransId transId, CtfUeInfo * ueInfo, CmStatus status)




                                ;
extern S16 TfUiCtfBndReq ( Pst* pst, SuId suId, SpId spId )



  ;
extern S16 TfUiCtfBndCfm ( Pst* pst, SuId suId, U8 status )



  ;
extern S16 TfUiCtfUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;
extern S16 TfUiCtfCfgReq ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfCfgReqInfo* cfgReqInfo )




  ;
extern S16 TfUiCtfCfgCfm ( Pst* pst, SuId suId, CtfCfgTransId transId, U8 status )




  ;
extern S16 TfUiCtfCnmCellSyncReq ( Pst* pst, SpId spId, CtfCfgTransId * transId, CtfCnmCellSyncReq* cfgReq )




  ;
extern S16 TfUiCtfCnmCellSyncRsp ( Pst* pst, SuId suId, CtfCfgTransId * transId, CtfCnmCellSyncRsp * cnmCellSyncRsp )




  ;
extern S16 TfUiCtfCnmInitSyncReq ( Pst* pst, SpId spId, CtfCfgTransId * transId, CtfCnmInitSyncReq* cfgReq )




  ;
extern S16 TfUiCtfCnmInitSyncRsp ( Pst* pst, SuId suId, CtfCfgTransId * transId, CtfCnmInitSyncRsp * cnmInitSyncRsp )




  ;
extern S16 TfUiCtfCnmCellSyncInd ( Pst* pst, SuId suId, CtfCfgTransId * transId, CtfCnmCellSyncInd * cnmCellSyncInd )




  ;
extern S16 TfUiCtfUeIdChgReq ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfUeInfo * ueInfo, CtfUeInfo * newUeInfo )





  ;
extern S16 TfUiCtfUeIdChgCfm ( Pst* pst, SuId suId, CtfCfgTransId transId, CtfUeInfo * ueInfo, CmStatus status )





  ;
extern S16 cmPkCtfBndReq ( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 cmUnpkCtfBndReq ( CtfBndReq func, Pst* pst, Buffer *mBuf )



  ;



extern S16 cmPkCtfBndCfm ( Pst* pst, SuId suId, U8 status )



  ;



extern S16 cmUnpkCtfBndCfm ( CtfBndCfm func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;

extern S16 cmUnpkCtfUbndReq ( CtfUbndReq func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkCtfCnmCellSyncReq ( Pst* pst, SpId spId, CtfCfgTransId * transId, CtfCnmCellSyncReq * ctfCnmCellSyncreq )




  ;

extern S16 cmUnpkCnmCellSyncReq ( CtfCnmCellSyncReqMsg func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfCnmCellSyncRsp ( Pst* pst, SpId spId, CtfCfgTransId * transId, CtfCnmCellSyncRsp * ctfCnmCellSyncrsp )




  ;

extern S16 cmUnpkCnmCellSyncRsp ( CtfCnmCellSyncRspMsg func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkCtfCnmCellSyncInd ( Pst* pst, SpId spId, CtfCfgTransId * transId, CtfCnmCellSyncInd * ctfCnmCellSyncind )




  ;

extern S16 cmUnpkCnmCellSyncInd ( CtfCnmCellSyncIndMsg func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfCnmInitSyncReq ( Pst* pst, SpId spId, CtfCfgTransId * transId, CtfCnmInitSyncReq * ctfCnmInitSyncreq )




  ;
extern S16 cmUnpkCnmInitSyncReq ( CtfCnmInitSyncReqMsg func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfCnmInitSyncRsp ( Pst* pst, SpId spId, CtfCfgTransId * transId, CtfCnmInitSyncRsp * ctfCnmInitSyncrsp )




  ;

extern S16 cmUnpkCnmInitSyncRsp ( CtfCnmInitSyncRspMsg func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkCtfKdfReq ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfKdfReqInfo * kdfReqInfo )




  ;



extern S16 cmUnpkCtfKdfReq ( CtfKdfReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfkdfCfm ( Pst* pst, SuId suId, CtfCfgTransId transId, CtfKdfCfmInfo *kdfCfmInfo, U8 status )





  ;

extern S16 cmUnpkCtfKdfCfm ( CtfKdfCfm func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkCtfCfgReq ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfCfgReqInfo * cfgReqInfo )




  ;



extern S16 cmUnpkCtfCfgReq ( CtfCfgReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfCfgCfm ( Pst* pst, SuId suId, CtfCfgTransId transId, U8 status )




  ;

extern S16 cmPkCtfEnbStopInd ( Pst* pst, SuId suId, CtfCfgTransId transId )



  ;

extern S16 cmUnpkCtfCfgCfm ( CtfCfgCfm func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCtfEnbStopInd ( CtfEnbStopInd func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfUeIdChgReq ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfUeInfo * ueInfo, CtfUeInfo * newUeInfo )





  ;

extern S16 cmUnpkCtfUeIdChgReq ( CtfUeIdChgReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfUeIdChgCfm ( Pst* pst, SuId suId, CtfCfgTransId transId, CtfUeInfo * ueInfo, CmStatus status )





  ;

extern S16 cmUnpkCtfUeIdChgCfm ( CtfUeIdChgCfm func, Pst* pst, Buffer *mBuf )



  ;



typedef S16 (*CtfPerRemCellSrchRsp) ( Pst* pst, SpId spId, CtfCfgTransId* transId, CtfPeriodicRemCellSearchRsp* sniffCellRsp)



                                               ;

extern S16 cmUnpkPerRemCellSrchRsp ( CtfPerRemCellSrchRsp func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCtfPerRemCellSrch ( CtfPeriodicRemCellSearchRsp *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfPerRemScanCellInfo ( CtfPeriodicRemCellInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfPeriodicCellSearchRsp ( CtfPeriodicRemCellSearchRsp *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfPeriodicRemCellSearchRsp ( Pst* pst, SpId spId, CtfCfgTransId *transId, CtfPeriodicRemCellSearchRsp *CellCfgRsp )




  ;

extern S16 cmPkPerRemScanCellInfo ( CtfPeriodicRemCellInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfCfgTransId ( CtfCfgTransId *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfCfgTransId ( CtfCfgTransId *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfUeInfo ( CtfUeInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfUeInfo ( CtfUeInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfBwCfgInfo ( CtfBwCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfBwCfgInfo ( CtfBwCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfTxSchemeCfg ( CtfTxSchemeCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfTxSchemeCfg ( CtfTxSchemeCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfAntennaCfgInfo ( CtfAntennaCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfAntennaCfgInfo ( CtfAntennaCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfPrachCfgInfo ( CtfPrachCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfPrachCfgInfo ( CtfPrachCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfPdschCfgInfo ( CtfPdschCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfPdschCfgInfo ( CtfPdschCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfPuschCfgBasic ( CtfPuschCfgBasic *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfPuschCfgBasic ( CtfPuschCfgBasic *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfPuschUlRS ( CtfPuschUlRS *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfPuschUlRS ( CtfPuschUlRS *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfPuschCfgInfo ( CtfPuschCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfPuschCfgInfo ( CtfPuschCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfPhichCfgInfo ( CtfPhichCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfPhichCfgInfo ( CtfPhichCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfPucchCfgInfo ( CtfPucchCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfPucchCfgInfo ( CtfPucchCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfSrsUlCfgInfo ( CtfSrsUlCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfSrsUlCfgInfo ( CtfSrsUlCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfTddSfCfgInfo ( CtfTddSfCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfTddSfCfgInfo ( CtfTddSfCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfCellCfgInfo ( CtfCellCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfCellCfgInfo ( CtfCellCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfCellRecfgInfo ( CtfCellRecfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfCellRecfgInfo ( CtfCellRecfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfDedPdschCfgInfo ( CtfDedPdschCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfDedPdschCfgInfo ( CtfDedPdschCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfDedPucchCfgInfo ( CtfDedPucchCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfDedPucchCfgInfo ( CtfDedPucchCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfDedPuschCfgInfo ( CtfDedPuschCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfDedPuschCfgInfo ( CtfDedPuschCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfDedAntCfgInfo ( CtfDedAntCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfDedAntCfgInfo ( CtfDedAntCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfUeSecCellCfgInfo ( CtfUeSecCellCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfSecCellCfgInfo ( CtfSecCellCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfUeSecCellCfgInfo ( CtfUeSecCellCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfSecCellCfgInfo ( CtfSecCellCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfUeCatCfgInfo ( CtfUeCatCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfUeCatCfgInfo ( CtfUeCatCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfDedCfgInfo ( CtfDedCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfDedCfgInfo ( CtfDedCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfDedRecfgInfo ( CtfDedRecfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfDedRecfgInfo ( CtfDedRecfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfCellReleaseInfo ( CtfCellReleaseInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfCellReleaseInfo ( CtfCellReleaseInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfDedReleaseInfo ( CtfDedReleaseInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfDedReleaseInfo ( CtfDedReleaseInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfCfgInfo ( CtfCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfCfgInfo ( CtfCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfReCfgInfo ( CtfReCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfReCfgInfo ( CtfReCfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfReleaseInfo ( CtfReleaseInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfReleaseInfo ( CtfReleaseInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkCtfCfgReqInfo ( CtfCfgReqInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfCfgReqInfo ( Pst *pst, CtfCfgReqInfo *param, Buffer *mBuf )



  ;


extern S16 cmPkCtfVendorSpecParams ( CtfVendorSpecific *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfVendorSpecParams ( Pst* pst, CtfVendorSpecific *param, Buffer *mBuf )



  ;



extern S16 cmPkCtfCellPwrcfgInfo ( CtfCellRecfgInfo *param, Buffer *mBuf )



  ;

extern S16 cmPkCtfCellStop ( CtfCellRecfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfCellPwrcfgInfo ( CtfCellRecfgInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCtfCellStop ( CtfCellRecfgInfo *param, Buffer *mBuf )


  ;


extern S16 cmPkCtfNhKeyInfo ( CtfNhKeyInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkCtfKenbStarInfo ( CtfKenbStarInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkCtfAskeyInfo ( CtfAsKeyInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkCtfKdfReqInfo ( CtfKdfReqInfo *param, Buffer *mBuf )



   ;
extern S16 cmPkCtfKdfReq ( Pst* pst, SpId spId, CtfCfgTransId transId, CtfKdfReqInfo* kdfReqInfo )





  ;
extern S16 cmUnpkCtfNhKeyInfo ( CtfNhKeyInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkCtfKenbStarInfo ( CtfKenbStarInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkCtfAskeyInfo ( CtfAsKeyInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkCtfKdfReqInfo ( CtfKdfReqInfo *param, Buffer *mBuf )



   ;
extern S16 cmUnpkCtfKdfReq ( CtfKdfReq func, Pst *pst, Buffer *mBuf )




  ;
extern S16 cmPkCtfNhKeyCfmInfo ( CtfNhKeyCfmInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkCtfKenbStarCfmInfo ( CtfKenbStarCfmInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkCtfAskeyCfmInfo ( CtfAskeyCfmInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkCtfKdfCfmInfo ( CtfKdfCfmInfo *param, Buffer *mBuf )



   ;
extern S16 cmPkCtfKdfCfm ( Pst* pst, SuId suId, CtfCfgTransId transId, CtfKdfCfmInfo *kdfCfmInfo, U8 status )






  ;
extern S16 cmUnpkCtfNhKeyCfmInfo ( CtfNhKeyCfmInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkCtfKenbStarCfmInfo ( CtfKenbStarCfmInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkCtfAskeyCfmInfo ( CtfAskeyCfmInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkCtfKdfCfmInfo ( CtfKdfCfmInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkCtfKdfCfm ( CtfKdfCfm func, Pst *pst, Buffer *mBuf )




  ;



extern S16 UrUiCtfHandleSnfMsgs ( Pst* pst, Buffer* mBuf )


  ;

extern S16 cmPkCtfCnmVendorSpecificInfo ( CtfCnmVendorSpecificInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfCtfCnmCellSyncReq ( CtfCnmCellSyncReq *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfCnmVendorSpecificInfo ( CtfCnmVendorSpecificInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfCtfCnmCellSyncReq ( CtfCnmCellSyncReq *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfCnmCellSyncReq ( Pst* pst, SpId spId, CtfCfgTransId *transId, CtfCnmCellSyncReq * cfgReqInfo )




  ;

extern S16 cmUnpkCtfCnmCellSyncReq ( CtfCnmCellSyncReqMsg func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfCnmInitSyncReq ( Pst* pst, SpId spId, CtfCfgTransId *transId, CtfCnmInitSyncReq * cfgReqInfo )




  ;

extern S16 cmUnpkCtfCnmInitSyncReq ( CtfCnmInitSyncReqMsg func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfctfCnmMibInfo ( CtfCnmMibInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfctfCnmInitSyncInfo ( CtfCnmInitSyncInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfCnmInitSyncRsp ( Pst* pst, SpId spId, CtfCfgTransId *transId, CtfCnmInitSyncRsp * cfgRspInfo )




  ;

extern S16 cmUnpkCtfctfCnmMibInfo ( CtfCnmMibInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkctfCnmInitSyncInfo ( CtfCnmInitSyncInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfCnmInitSyncRspMsg ( CtfCnmInitSyncRsp *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfCnmInitSyncRsp ( CtfCnmInitSyncRspMsg func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfCnmCellSyncRsp ( Pst* pst, SpId spId, CtfCfgTransId *transId, CtfCnmCellSyncRsp * cfgRspInfo )




  ;

extern S16 cmUnpkCtfCnmSyncRspMsg ( CtfCnmCellSyncRsp *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfCnmCellSyncRsp ( CtfCnmCellSyncRspMsg func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfCnmCellSyncInd ( Pst* pst, SpId spId, CtfCfgTransId *transId, CtfCnmCellSyncInd * cfgIndInfo )




  ;

extern S16 cmUnpkCtfCnmSyncIndMsg ( CtfCnmCellSyncInd *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfCnmCellSyncInd ( CtfCnmCellSyncIndMsg func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkCtfcfgReqInfo ( CtfCnmInitSyncReq *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCtfsyncReqInfo ( CtfCnmInitSyncReq *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfcfgRspInfo ( CtfCnmInitSyncRsp *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfCellSyncRsp ( CtfCnmCellSyncRsp *param, Buffer *mBuf )


  ;

extern S16 cmPkCtfcfgIndInfo ( CtfCnmCellSyncInd *param, Buffer *mBuf )


  ;

extern S16 cmRelCtfCfgReq ( Pst *pst, CtfCfgReqInfo *cfgReqInfo )


  ;
typedef struct ysGenCfg
{
   Pst lmPst;
   U16 maxTfuSaps;
   U16 nmbUe;
   U16 freqSyncPci;
   U16 freqSyncEarfcn;




   Bool enblSIAndPagngLog;
} YsGenCfg;

typedef enum
{
   LYS_TFU_USR_SAP,
   LYS_TFU_SCH_SAP
} YsTfuSapType;

typedef struct ysTfuSapCfg
{
   Selector selector;
   MemoryId mem;
   Priority prior;
   ProcId procId;
   Ent ent;
   Inst inst;
   Route route;
   SpId spId;
   SuId suId;
   YsTfuSapType type;
   CmLteCellId cellId;
} YsTfuSapCfg;

typedef struct ysCtfSapCfg
{
   Selector selector;
   MemoryId mem;
   Priority prior;
   ProcId procId;
   Ent ent;
   Inst inst;
   Route route;
   SpId spId;
   SuId suId;
} YsCtfSapCfg;
typedef struct ysCfg
{
   union
   {
      YsGenCfg genCfg;
      YsTfuSapCfg tfuSap;
      YsCtfSapCfg ctfSap;




   }s;
}YsCfg;


typedef struct ysCtfSapSts
{
   U32 numUeCfg;
   U16 numCellCfg;
}YsCtfSapSts;

typedef struct ysTfuSapSts
{
   U32 numCntrlReqRcvd;
   U32 numDatReqRcvd;
   U32 numRecpReqRcvd;
}YsTfuSapSts;


typedef struct ysL1PhySts
{
   StsCntr numSfReqTx;
   StsCntr numSfIndRx;
   StsCntr numHiDciReqTx;
   StsCntr numTxReqTx;
   StsCntr numHarqIndRx;
   StsCntr numCrcIndRx;
   StsCntr numRxIndRx;
   StsCntr numRachIndRx;
   StsCntr numSrsIndRx;

}YsL1PhySts;
typedef struct ysSts
{
   DateTime dt;
   U8 sapInst;
   Action action;
   union
   {
      YsCtfSapSts ctfSts;
      YsTfuSapSts tfuSts;
      YsL1PhySts phySts;
   }s;
}YsSts;


typedef struct ysSapSta
{
   U8 sapState;
}YsSapSta;


typedef struct ysSsta
{
   DateTime dt;
   U8 sapInst;
   union
   {
      SystemId sysId;
      YsSapSta tfuSapSta;
      YsSapSta ctfSapSta;
      State phyState;
   }s;
}YsSsta;


typedef struct ysUstaDgn
{
   U8 type;
   union
   {
      MemoryId mem;
      SpId sapId;
      CmLteTimingInfo timingInfo;
   }u;
} YsUstaDgn;


typedef struct ysUsta
{
   CmAlarm cmAlarm;
   YsUstaDgn dgn;
}YsUsta;


typedef struct ysTrc
{
   DateTime dt;
   U8 evnt;
}YsTrc;


typedef struct ysDbgCntrl
{
   U32 dbgMask;
}YsDbgCntrl;


typedef struct ysSapCntrl
{
   SuId suId;
   SpId spId;
}YsSapCntrl;


typedef struct ysCntrl
{
   DateTime dt;
   U8 action;
   U8 subAction;
   union
   {
      YsDbgCntrl ysDbgCntrl;
      S16 trcLen;
      YsSapCntrl ysSapCntrl;
      CmLteCellId cellId;
      U32 logMask;

      U32 statsPer;

   }s;
}YsCntrl;


typedef struct ysMngmt
{
   Header hdr;
   CmStatus cfm;
   union
   {
      YsCfg cfg;
      YsSts sts;
      YsSsta ssta;
      YsUsta usta;
      YsTrc trc;
      YsCntrl cntrl;
   }t;
}YsMngmt;

typedef S16 (*LysTPMRefSigPwrChangeReq) ( Pst *pst, S16 refSigPwr )


  ;




typedef S16 (*LysCfgReq) ( Pst *pst, YsMngmt *cfg )


       ;


typedef S16 (*LysCfgCfm) ( Pst *pst, YsMngmt *cfg )


       ;

typedef S16 (*LysCntrlReq) ( Pst *pst, YsMngmt *cntrl )


       ;

typedef S16 (*LysCntrlCfm) ( Pst *pst, YsMngmt *cntrl )


       ;

typedef S16 (*LysStaReq) ( Pst *pst, YsMngmt *sta )


       ;

typedef S16 (*LysStaCfm) ( Pst *pst, YsMngmt *sta )


       ;

typedef S16 (*LysStaInd) ( Pst *pst, YsMngmt *sta )


       ;

typedef S16 (*LysStsReq) ( Pst *pst, YsMngmt *sts )


       ;

typedef S16 (*LysStsCfm) ( Pst *pst, YsMngmt *sts )


       ;

typedef S16 (*LysTrcInd) ( Pst *pst, YsMngmt *trc, Buffer *mBuf )



       ;
typedef S16 (*LysRlInd) ( Pst *pst, U8 rlLogLvl )


       ;

typedef S16 (*LysREMScanCfgReq) ( Pst *pst, U16 remScanInterval, U16 remScanCount )



       ;






extern S16 YsMiLysCfgReq (Pst *pst, YsMngmt *cfg);
extern S16 YsMiLysCfgCfm (Pst *pst, YsMngmt *cfm);
extern S16 YsMiLysStsReq (Pst *pst, YsMngmt *sts);
extern S16 YsMiLysStsCfm (Pst *pst, YsMngmt *cfm);
extern S16 YsMiLysStaReq (Pst *pst, YsMngmt *sta);
extern S16 YsMiLysStaCfm (Pst *pst, YsMngmt *cfm);
extern S16 YsMiLysStaInd (Pst *pst, YsMngmt *usta);
extern S16 YsMiLysCntrlReq (Pst *pst, YsMngmt *cntrl);
extern S16 YsMiLysCntrlCfm ( Pst *pst, YsMngmt *cfm);
extern S16 YsMiLysTrcInd (Pst *pst, YsMngmt *trc, Buffer *mBuf);




extern S16 YsMiLysRlInd (Pst *pst, U8 rlLogLvl);
extern S16 YsMiLysREMScanCfgReq (Pst *pst,U16 remScanInterval, U16 remScanCount);
extern S16 YsTPMRefSigPwrChangeReq (Pst *pst,S16 refSigPwr);
extern S16 cmPkLysCfgReq (Pst *pst, YsMngmt *cfg);
extern S16 cmPkLysCfgCfm (Pst *pst, YsMngmt *cfm);
extern S16 cmPkLysStsReq (Pst *pst, YsMngmt *sts);
extern S16 cmPkLysStsCfm (Pst *pst, YsMngmt *cfm);
extern S16 cmPkLysStaReq (Pst *pst, YsMngmt *sta);
extern S16 cmPkLysStaCfm (Pst *pst, YsMngmt *cfm);
extern S16 cmPkLysStaInd (Pst *pst, YsMngmt *usta);
extern S16 cmPkLysCntrlReq (Pst *pst, YsMngmt *cntrl);
extern S16 cmPkLysCntrlCfm ( Pst *pst, YsMngmt *cfm);
extern S16 cmPkLysTrcInd (Pst *pst, YsMngmt *trc, Buffer *mBuf);
extern S16 cmPkLysRlInd (Pst *pst, U8 rlLogLvl);
extern S16 cmPkLysREMScanCfgReq ( Pst *pst, U16 remScanInterval, U16 remScanCount )




  ;

extern S16 cmPkLysTPMRefSigPwrChangeReq ( Pst *pst, S16 refSigPwr )


  ;



extern S16 cmUnpkLysCfgReq (LysCfgReq ,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysCfgCfm (LysCfgCfm ,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysStsReq (LysStsReq,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysStsCfm (LysStsCfm,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysStaReq (LysStaReq,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysStaCfm (LysStaCfm,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysStaInd (LysStaInd,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysCntrlReq (LysCntrlReq,Pst *pst,Buffer *mBuf);
extern S16 cmUnpkLysCntrlCfm (LysCntrlCfm,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysTrcInd (LysTrcInd,Pst *pst,Buffer *mBuf);
extern S16 cmUnpkLysRlInd (LysRlInd ,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLysREMScanCfgReq (LysREMScanCfgReq, Pst *pst, Buffer *mBuf);
extern S16 cmUnPkLysTPMRefSigPwrChangeReq (LysTPMRefSigPwrChangeReq CfgReq, Pst *pst, Buffer *mBuf);





extern S16 cmPkYsMngmt (Pst *pst, YsMngmt *req,U8 eventType, Buffer *mBuf);
extern S16 cmPkYsGenCfg (YsGenCfg *cfg,Buffer *mBuf);
extern S16 cmPkYsTfuSapCfg ( YsTfuSapCfg *cfg, Buffer *mBuf);
extern S16 cmPkYsCtfSapCfg (YsCtfSapCfg *cfg, Buffer *mBuf);
extern S16 cmPkYsCfg (YsCfg *cfg, S16 elmnt, Buffer *mBuf);
extern S16 cmPkYsCtfSapSts (YsCtfSapSts *sts, Buffer *mBuf);
extern S16 cmPkYsTfuSapSts (YsTfuSapSts *sts, Buffer *mBuf);
extern S16 cmPkYsPhySts (YsL1PhySts *cfg, Buffer *mBuf);
extern S16 cmPkYsSts (YsSts *sts, S16 elmnt,Buffer *mBuf);
extern S16 cmPkYsSapSta (YsSapSta *sta, Buffer *mBuf);

extern S16 cmPkYsSsta (Pst *pst, YsSsta *ssta,S16 elmnt,U8 eventType, Buffer *mBuf);
extern S16 cmPkYsUstaDgn (YsUstaDgn *param, Buffer *mBuf);
extern S16 cmPkYsUsta (YsUsta *usta, Buffer *mBuf);
extern S16 cmPkYsTrc (YsTrc *trc,Buffer *mBuf);
extern S16 cmPkYsDbgCntrl (YsDbgCntrl *cntrl, Buffer *mBuf);
extern S16 cmPkYsSapCntrl (YsSapCntrl *cntrl, Buffer *mBuf);
extern S16 cmPkYsCntrl (YsCntrl *cntrl, S16 elmnt, Buffer *mBuf);

extern S16 cmUnpkYsMngmt (Pst *pst, YsMngmt *req,U8 eventType, Buffer *mBuf);
extern S16 cmUnpkYsGenCfg (YsGenCfg *cfg,Buffer *mBuf);
extern S16 cmUnpkYsTfuSapCfg ( YsTfuSapCfg *cfg, Buffer *mBuf);
extern S16 cmUnpkYsCtfSapCfg (YsCtfSapCfg *cfg, Buffer *mBuf);
extern S16 cmUnpkYsCfg (YsCfg *cfg, S16 elmnt, Buffer *mBuf);
extern S16 cmUnpkYsCtfSapSts (YsCtfSapSts *sts, Buffer *mBuf);
extern S16 cmUnpkYsTfuSapSts (YsTfuSapSts *sts, Buffer *mBuf);
extern S16 cmUnpkYsPhySts (YsL1PhySts *cfg, Buffer *mBuf);
extern S16 cmUnpkYsSts (YsSts *sts, S16 elmnt,Buffer *mBuf);
extern S16 cmUnpkYsSapSta (YsSapSta *sta, Buffer *mBuf);
extern S16 cmUnpkYsSsta (Pst *pst, YsSsta *ssta,S16 elmnt, Buffer *mBuf);
extern S16 cmUnpkYsUstaDgn ( YsUstaDgn *param, Buffer *mBuf);
extern S16 cmUnpkYsUsta (YsUsta *usta, Buffer *mBuf);
extern S16 cmUnpkYsTrc (YsTrc *trc,Buffer *mBuf);
extern S16 cmUnpkYsDbgCntrl (YsDbgCntrl *cntrl, Buffer *mBuf);
extern S16 cmUnpkYsSapCntrl (YsSapCntrl *cntrl, Buffer *mBuf);
extern S16 cmUnpkYsCntrl (YsCntrl *cntrl, S16 elmnt, Buffer *mBuf);
typedef enum
{
   TFU_DCI_FORMAT_0,
   TFU_DCI_FORMAT_1,
   TFU_DCI_FORMAT_1A,
   TFU_DCI_FORMAT_1B,
   TFU_DCI_FORMAT_1C,
   TFU_DCI_FORMAT_1D,
   TFU_DCI_FORMAT_2,
   TFU_DCI_FORMAT_2A,
   TFU_DCI_FORMAT_3,
   TFU_DCI_FORMAT_3A


   ,TFU_DCI_FORMAT_INVALID

} TfuDciFormat;




typedef enum
{
   TFU_MOD_BPSK = 1,
   TFU_MOD_QPSK = 2,
   TFU_MOD_16QAM = 4,
   TFU_MOD_64QAM = 6
} TfuModScheme;





typedef enum
{
   TFU_PUCCH_CQI_MODE10,
   TFU_PUCCH_CQI_MODE11,
   TFU_PUCCH_CQI_MODE20,
   TFU_PUCCH_CQI_MODE21
} TfuDlCqiPucchMode;




typedef enum
{
   TFU_RPT_CQI,
   TFU_RPT_RI
} TfuRptType;
typedef struct tfuDciFormat0Info
{
   Bool isSrGrant;
   Bool isMsg4PdcchWithCrnti;

   Bool hoppingEnbld;
   U8 rbStart;
   U8 numRb;

   U32 riv;



   U8 hoppingBits;
   U8 mcs;
   Bool ndi;
   U8 tpcCmd;







   U8 nDmrs;
   U8 cqiReq;
   U8 numCqiBit;
   U8 txAntenna;


   U8 hqProcId;
} TfuDciFormat0Info;




typedef enum
{
   TFU_ALLOC_TYPE_MAP= 1,
   TFU_ALLOC_TYPE_RIV
} TfuAllocType;




typedef struct tfuAllocMapOrRiv
{
   TfuAllocType type;
   union
   {

      U32 riv;


      U8 resAllocMap[4];





   }u;
} TfuAllocMapOrRiv;




typedef enum
{
   TFU_ALLOC_TYPE_0= 1,
   TFU_ALLOC_TYPE_1
} TfuAllocSubType;
typedef struct tfuAllocMap
{
   TfuAllocSubType type;
  union
  {
     struct
     {
        U32 allocMask;
     } allocType0;
     struct
     {
        U8 rbgSubset;

        U8 shift;

        U32 allocMask;
     } allocType1;
  } u;
} TfuAllocMap;
typedef struct tfuDciFormat1AllocInfo
{
   Bool isAllocType0;
   U8 resAllocMap[4];


   U8 harqProcId;
   Bool ndi;
   U8 mcs;
   U8 rv;
} TfuDciFormat1AllocInfo;







typedef struct tfuDciFormat1Info
{
   TfuDciFormat1AllocInfo allocInfo;






   U8 tpcCmd;
} TfuDciFormat1Info;



typedef struct tfuDciFormatTbInfo
{
   Bool ndi;
   U8 rv;
   U8 mcs;
}TfuDciFormatTbInfo;
typedef struct tfuDciFormat2AAllocInfo
{
   Bool isAllocType0;


   U8 resAllocMap[4];





   U8 harqProcId;
   TfuDciFormatTbInfo tbInfo[2];
   U8 precoding;
   Bool transSwap;
} TfuDciFormat2AAllocInfo;





typedef struct tfuDciFormat2AInfo
{
   TfuDciFormat2AAllocInfo allocInfo;






   U8 tpcCmd;
} TfuDciFormat2AInfo;
typedef struct tfuDciFormat2AllocInfo
{
   Bool isAllocType0;

   U8 resAllocMap[4];
   Bool transSwap;

   U8 precoding;
   U8 harqProcId;
   TfuDciFormatTbInfo tbInfo[2];
} TfuDciFormat2AllocInfo;
typedef struct tfuDciFormat2Info
{
   TfuDciFormat2AllocInfo allocInfo;

   U8 tpcCmd;
} TfuDciFormat2Info;



typedef struct tfuDciFormat3Info
{
   U8 tpcCmd[16];


   U8 isPucch;

} TfuDciFormat3Info;



typedef struct tfuDciFormat3AInfo
{
   U8 tpcCmd[32];


   U8 isPucch;
} TfuDciFormat3AInfo;
typedef struct tfuDciFormat1dAllocInfo
{
   Bool isLocal;
   TknU8 nGap2;
   TfuAllocMapOrRiv alloc;
   U8 mcs;
   U8 rv;
   U8 tPmi;
} TfuDciFormat1dAllocInfo;







typedef struct tfuDciFormat1dInfo
{
   TfuDciFormat1dAllocInfo allocInfo;
   U8 harqProcId;
   Bool ndi;
   U8 tpcCmd;






   U8 dlPwrOffset;
} TfuDciFormat1dInfo;
typedef struct tfuDciFormat1cInfo
{
   TknU8 nGap2;
   TfuAllocMapOrRiv alloc;
   U8 iTbs;
} TfuDciFormat1cInfo;
typedef struct tfuDciFormat1bAllocInfo
{
   Bool isLocal;
   TknU8 nGap2;
   TfuAllocMapOrRiv alloc;
   U8 mcs;
   U8 rv;
   U8 harqProcId;
   Bool ndi;
   U8 tPmi;
   Bool pmiCfm;
} TfuDciFormat1bAllocInfo;





typedef struct tfuPdcchOrderInfo
{
   U8 preambleIdx;
   U8 prachMaskIdx;

} TfuPdcchOrderInfo;
typedef struct tfuDciFormat1aAllocInfo
{
   Bool isLocal;
   TknU8 nGap2;
   TfuAllocMapOrRiv alloc;
   U8 mcs;
   U8 rv;
   TknU8 harqProcId;

   Bool ndi;
} TfuDciFormat1aAllocInfo;




typedef struct tfudciformat1aPdsch
{
   TfuDciFormat1aAllocInfo allocInfo;







   U8 tpcCmd;
   Bool isTBMsg4;
} Tfudciformat1aPdsch;






typedef struct tfuDciFormat1aInfo
{

   Bool isPdcchOrder;
   union
   {
      TfuPdcchOrderInfo pdcchOrder;
      Tfudciformat1aPdsch pdschInfo;

   }t;
} TfuDciFormat1aInfo;







typedef struct tfuDciFormat1bInfo
{
   TfuDciFormat1bAllocInfo allocInfo;






   U8 tpcCmd;
} TfuDciFormat1bInfo;
typedef struct tfuDciInfo
{
   TfuDciFormat dciFormat;
   union
   {
      TfuDciFormat0Info format0Info;
      TfuDciFormat1Info format1Info;
      TfuDciFormat1aInfo format1aInfo;
      TfuDciFormat1bInfo format1bInfo;
      TfuDciFormat1cInfo format1cInfo;
      TfuDciFormat1dInfo format1dInfo;
      TfuDciFormat2Info format2Info;
      TfuDciFormat2AInfo format2AInfo;
      TfuDciFormat3Info format3Info;
      TfuDciFormat3AInfo format3AInfo;
   } u;
} TfuDciInfo;




typedef struct tfuSubbandInfo
{
   U8 rbStart;
   U8 numRb;
} TfuSubbandInfo;



typedef struct tfuSubbandDlCqiInfo
{
   TfuSubbandInfo subband;
   U8 cqiIdx[2];
} TfuSubbandDlCqiInfo;





typedef struct tfuSubbandCqiInfo
{
   TfuSubbandInfo subband;
   U8 cqiIdx;
} TfuSubbandCqiInfo;


typedef struct tfuPdcchCceInfo
{
   U8 cceIdx;
   CmLteAggrLvl aggrLvl;
} TfuPdcchCceInfo;




typedef struct tfuCqiPucchMode10
{
   TfuRptType type;
   union
   {
      U8 ri;
      U8 cqi;
   }u;
} TfuCqiPucchMode10;





typedef struct tfuCqiMode11Cqi
{
   U8 cqi;
   U8 pmi;
   TknU8 wideDiffCqi;
} TfuCqiMode11Cqi;




typedef struct tfuCqiPucchMode11
{
   TfuRptType type;
   union
   {
      U8 ri;
      TfuCqiMode11Cqi cqi;
   }u;
} TfuCqiPucchMode11;



typedef struct tfuCqiMode20SubCqi
{
   U8 cqi;
   U8 l;
} TfuCqiMode20SubCqi;




typedef struct tfuCqiMode20Cqi
{
   Bool isWideband;
   union
   {
      U8 wideCqi;
      TfuCqiMode20SubCqi subCqi;
   }u;
} TfuCqiMode20Cqi;





typedef struct tfuCqiPucchMode20
{
   TfuRptType type;
   union
   {
      U8 ri;
      TfuCqiMode20Cqi cqi;
   }u;
} TfuCqiPucchMode20;




typedef struct tfuCqiMode21SubCqi
{
   U8 cqi;
   U8 l;
   TknU8 diffCqi;
} TfuCqiMode21SubCqi;





typedef struct tfuCqiMode21WideCqi
{
   U8 cqi;
   U8 pmi;
   TknU8 diffCqi;
} TfuCqiMode21WideCqi;





typedef struct tfuCqiMode21Cqi
{
   Bool isWideband;
   union
   {
      TfuCqiMode21WideCqi wideCqi;
      TfuCqiMode21SubCqi subCqi;
   }u;
} TfuCqiMode21Cqi;





typedef struct tfuCqiPucchMode21
{
   TfuRptType type;
   union
   {
      U8 ri;
      TfuCqiMode21Cqi cqi;
   }u;
} TfuCqiPucchMode21;




typedef struct tfuDlCqiPucch
{
   U8 cellIdx;
   TfuDlCqiPucchMode mode;
   union
   {
      TfuCqiPucchMode10 mode10Info;
      TfuCqiPucchMode11 mode11Info;
      TfuCqiPucchMode20 mode20Info;
      TfuCqiPucchMode21 mode21Info;
   }u;
} TfuDlCqiPucch;





typedef struct tfuSubbandMode12
{
   U8 pmi;
   TfuSubbandInfo subBand;
} TfuSubbandMode12;




typedef struct tfuCqiPuschMode12
{
   U8 numSubband;
   U8 cqiIdx[2];

   TfuSubbandMode12 subbandArr[110];
} TfuCqiPuschMode12;





typedef struct tfuCqiPuschMode20
{
   U8 cqiIdx;

   U8 wideBandCqi;

   U8 numSubband;
   TfuSubbandInfo subbandArr[110];
} TfuCqiPuschMode20;




typedef struct tfuCqiPuschMode22
{
   U8 cqi[2];

   U8 pmi;

   U8 wideBandCqi[2];
   U8 wideBandPmi;
   U8 numSubband;
   TfuSubbandInfo subbandArr[110];
} TfuCqiPuschMode22;




typedef struct tfuSubbandMode30
{
   U8 cqi;
   TfuSubbandInfo subBand;
} TfuSubbandMode30;





typedef struct tfuCqiPuschMode30
{
   U8 wideBandCqi;
   U8 numSubband;
   TfuSubbandMode30 subbandArr[110];
} TfuCqiPuschMode30;



typedef struct tfuSubbandMode31
{
   U8 cqi[2];
   TfuSubbandInfo subBand;
} TfuSubbandMode31;





typedef struct tfuCqiPuschMode31
{
   U8 pmi;
   U8 wideBandCqi[2];
   U8 numSubband;
   TfuSubbandDlCqiInfo subbandCqiArr[110];


} TfuCqiPuschMode31;




typedef enum
{
   TFU_PUSCH_CQI_MODE_12,
   TFU_PUSCH_CQI_MODE_20,
   TFU_PUSCH_CQI_MODE_22,
   TFU_PUSCH_CQI_MODE_30,
   TFU_PUSCH_CQI_MODE_31
} TfuDlCqiPuschMode;





typedef struct tfuDlCqiPusch
{
   U8 cellIdx;
   TfuDlCqiPuschMode mode;
   TknU8 ri;
   union
   {
      TfuCqiPuschMode12 mode12Info;
      TfuCqiPuschMode20 mode20Info;
      TfuCqiPuschMode22 mode22Info;
      TfuCqiPuschMode30 mode30Info;
      TfuCqiPuschMode31 mode31Info;
   }u;
} TfuDlCqiPusch;




typedef struct tfuDlCqiPuschInfo
{
   TfuDlCqiPuschMode mode;
   union
   {
      TfuCqiPuschMode12 mode12Info;
      TfuCqiPuschMode22 mode22Info;
      TfuCqiPuschMode31 mode31Info;
   }u;
} TfuDlCqiPuschInfo;
typedef enum
{
   TFU_UCI_FORMAT_1A_1B,
   TFU_UCI_FORMAT_1B_CS,
   TFU_UCI_FORMAT_3
} TfuAckNackMode;
typedef struct tfuSrsRpt
{
   CmLList lnk;
   CmLteRnti ueId;
   U16 dopEst;
   U16 ta;
   U8 numRbs;
   U8 rbStart;
   U8 snr[110];
   Bool wideCqiPres;
   U8 wideCqi;
} TfuSrsRpt;
typedef struct tfuSrsIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp srsRpt;
} TfuSrsIndInfo;
typedef struct tfuRawCqiRpt
{
   CmLList lnk;
   CmLteRnti crnti;
   U8 numBits;
   U8 cqiBits[9];

   U8 ri[8];
} TfuRawCqiRpt;






typedef struct tfuRawCqiIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp rawCqiRpt;
} TfuRawCqiIndInfo;


typedef enum
{
   TFU_PUCCH_HARQ,
   TFU_PUCCH_SR,
   TFU_PUCCH_SRS,
   TFU_PUCCH_CQI,
   TFU_PUCCH_HARQ_SR,
   TFU_PUCCH_HARQ_SRS,
   TFU_PUCCH_HARQ_CQI,
   TFU_PUCCH_HARQ_SR_SRS,
   TFU_PUCCH_HARQ_SR_CQI,
   TFU_PUCCH_SR_SRS,
   TFU_PUCCH_SR_CQI,


   TFU_PUCCH_HARQ_SR_CQI_SRS,
   TFU_PUCCH_SR_CQI_SRS
} TfuUePucchRecpType;




typedef struct tfuUePucchHqRecpInfo
{
   TfuAckNackMode hqFdbkMode;
   U8 hqSz;
   U8 pucchResCnt;

   U16 hqRes[4];

   U8 a;
} TfuUePucchHqRecpInfo;




typedef struct tfuUePucchSrRecpInfo
{
   U16 n1PucchIdx;
} TfuUePucchSrRecpInfo;




typedef struct tfuUePucchCqiRecpInfo
{
   U16 n2PucchIdx;
   U8 cqiPmiSz;
} TfuUePucchCqiRecpInfo;


typedef enum tfuUlSrsBwInfo
{
   TFU_ULSRS_BW_0 = 0,
   TFU_ULSRS_BW_1 = 1,
   TFU_ULSRS_BW_2 = 2,
   TFU_ULSRS_BW_3 = 3
} TfuUlSrsBwInfo;



typedef enum tfuUlSrsHoBwInfo
{
   TFU_ULSRS_HOP_BW_0 = 0,
   TFU_ULSRS_HOP_BW_1 = 1,
   TFU_ULSRS_HOP_BW_2 = 2,
   TFU_ULSRS_HOP_BW_3 = 3
} TfuUlSrsHoBwInfo;


typedef enum tfuUlSrsCycShiftInfo
{
   TFU_ULSRS_CYSHIFT_0 = 0,
   TFU_ULSRS_CYSHIFT_1 = 1,
   TFU_ULSRS_CYSHIFT_2 = 2,
   TFU_ULSRS_CYSHIFT_3 = 3,
   TFU_ULSRS_CYSHIFT_4 = 4,
   TFU_ULSRS_CYSHIFT_5 = 5,
   TFU_ULSRS_CYSHIFT_6 = 6,
   TFU_ULSRS_CYSHIFT_7 = 7
} TfuUlSrsCycShiftInfo;





typedef struct tfuUePucchSrsRecpInfo
{
   TfuUlSrsBwInfo srsBw;

   U8 nRrc;

   TfuUlSrsHoBwInfo srsHopBw;

   U8 transComb;

   U16 srsCfgIdx;


   TfuUlSrsCycShiftInfo srsCyclicShft;

} TfuUePucchSrsRecpInfo;
typedef struct tfuUePucchRecpReq
{
   TfuUePucchRecpType uciInfo;

   TfuUePucchCqiRecpInfo cqiInfo;

   TfuUePucchSrRecpInfo srInfo;

   TfuUePucchHqRecpInfo hqInfo;

   TfuUePucchSrsRecpInfo srsInfo;

} TfuUePucchRecpReq;

typedef enum
{
   TFU_PUSCH_DATA,
   TFU_PUSCH_DATA_SRS,
   TFU_PUSCH_DATA_HARQ,
   TFU_PUSCH_DATA_HARQ_SRS,
   TFU_PUSCH_DATA_CQI,
   TFU_PUSCH_DATA_CQI_SRS,
   TFU_PUSCH_DATA_CQI_HARQ,
   TFU_PUSCH_DATA_CQI_HARQ_SRS
} TfuUePuschRecpType;




typedef struct tfuUeUlSchRecpInfo
{
   U16 size;
   U8 rbStart;

   U8 numRb;
   TfuModScheme modType;
   U8 nDmrs;
   Bool hoppingEnbld;
   U8 hoppingBits;

   Bool isRtx;
   Bool ndi;
   U8 rv;
   U8 harqProcId;
   U8 txMode;

   U8 crntTxNb;


   Bool nSrs;


   U8 mcs;
} TfuUeUlSchRecpInfo;




typedef struct tfuUePuschCqiRecpInfo
{
   U8 reportType;


   U8 cCNum;

   U8 cqiPmiSzR1[8];

   U8 cqiPmiSzRn1[8];

   TknU8 riSz[8];


   U8 cqiBetaOff;

   U8 riBetaOff;

} TfuUePuschCqiRecpInfo;




typedef struct tfuUePuschHqRecpInfo
{
   U8 hqSz;

   U8 hqBetaOff;






} TfuUePuschHqRecpInfo;

typedef TfuUePucchSrsRecpInfo TfuUePuschSrsRecpInfo;
typedef struct tfuUePuschRecpReq
{
   TfuUePuschRecpType rcpInfo;

   TfuUeUlSchRecpInfo ulSchInfo;


   TfuUePuschCqiRecpInfo cqiRiInfo;


   TfuUePuschHqRecpInfo hqInfo;


   TfuUePuschSrsRecpInfo srsInfo;

   TknU8 initialNSrs;



   TknU8 initialNumRbs;


} TfuUePuschRecpReq;




typedef enum
{
   TFU_RECP_REQ_PUCCH,
   TFU_RECP_REQ_PUSCH,
   TFU_RECP_REQ_INVLD
} TfuRecpReqType;





typedef struct tfuUeRecpReqInfo
{
   CmLList lnk;
   CmLteRnti rnti;
   TfuRecpReqType type;
   union
   {
      TfuUePucchRecpReq pucchRecpReq;
      TfuUePuschRecpReq puschRecpReq;
   }t;
} TfuUeRecpReqInfo;
typedef union tfuDlCqiInfo
{
   TfuDlCqiPucch pucchCqi;
   struct {
      U8 numOfCells;
      TfuDlCqiPusch puschCqi[8];
   }pusch;
} TfuDlCqiInfo;
typedef struct tfuRecpReqInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp ueRecpReqLst;




   Bool srsPres;




} TfuRecpReqInfo;




 typedef struct tfuPdcchInfo
{
   CmLList lnk;
   CmLteRnti rnti;

   Bool isSpsRnti;
   CmLteRnti crnti;

   U16 nCce;
   CmLteAggrLvl aggrLvl;

   U8 dciNumOfBits;
   TfuDciInfo dci;
} TfuPdcchInfo;
typedef struct tfuPhichInfo
{
   CmLList lnk;
   U8 rbStart;
   U8 nDmrs;
   Bool isAck;
   Bool isForMsg3;






   U16 txPower;

} TfuPhichInfo;







typedef struct tfuCntrlReqInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo ulTiming;
   CmLteTimingInfo dlTiming;
   U8 cfi;
   U32 numDlActvUes;
   CmLListCp ulPdcchLst;
   CmLListCp dlPdcchLst;
   CmLListCp phichLst;

   Bool isSPSOcc;


} TfuCntrlReqInfo;




typedef struct tfuPdschDciInfo
{
   TfuDciFormat format;
   union
   {
      TfuDciFormat1AllocInfo format1AllocInfo;
      TfuDciFormat1aAllocInfo format1aAllocInfo;
      TfuDciFormat1bAllocInfo format1bAllocInfo;
      TfuDciFormat1cInfo format1cAllocInfo;
      TfuDciFormat1dAllocInfo format1dAllocInfo;
      TfuDciFormat2AllocInfo format2AllocInfo;
      TfuDciFormat2AAllocInfo format2AAllocInfo;
   } u;
} TfuPdschDciInfo;



typedef enum tfuTxMode
{
   TFU_UE_TM_1 = 1,
   TFU_UE_TM_2,
   TFU_UE_TM_3,
   TFU_UE_TM_4,
   TFU_UE_TM_5,
   TFU_UE_TM_6,
   TFU_UE_TM_7
} TfuTxMode;






 typedef struct tfuBfVectorInfo
 {
   U8 sbIndex;
   U8 numPhyAnt;
   U16 bfValue[4];

 }TfuBfVectorInfo;
typedef struct tfuDatReqPduInfo
{
   CmLList lnk;
   CmLteRnti rnti;
   TfuPdschDciInfo dciInfo;

   U8 nmbOfTBs;


   Buffer *mBuf[2];



   Bool puschRptUsd;
   TfuDlCqiPuschInfo puschPmiInfo;


   TfuTxMode transMode;
   TknU32 doa;
   Bool isTApres;


   U8 numLayers;


   U8 deltaPowOffIdx;


   U8 numBfPrbPerSb;



   U8 numBfVectors;



   TfuBfVectorInfo bfVector[110];




   U16 txPwrOffset;




 U8 pa;


   U8 isEnbSFR;
} TfuDatReqPduInfo;







typedef struct tfuDatReqInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   TknBuf bchDat;

   CmLListCp pdus;
} TfuDatReqInfo;



typedef struct tfuDatInfo
{
   CmLList lnk;
   CmLteRnti rnti;
   Buffer *mBuf;
} TfuDatInfo;





typedef struct tfuDatIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp datIndLst;
} TfuDatIndInfo;






typedef struct tfuSrInfo
{
   CmLList lnk;
   CmLteRnti rnti;
} TfuSrInfo;




typedef struct tfuSrIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp srLst;
} TfuSrIndInfo;






typedef enum
{
   TFU_HQ_ACK=1,
   TFU_HQ_NACK,
   TFU_HQ_ACK_OR_NACK,
   TFU_HQ_DTX,
   TFU_HQ_ACK_OR_DTX,
   TFU_HQ_NACK_OR_DTX,
   TFU_HQ_ACK_OR_NACK_OR_DTX,
   TFU_HQ_INVALID = 255
} TfuHqFdbk;
typedef struct tfuHqInfo
{
   CmLList lnk;
   CmLteRnti rnti;
   TfuAckNackMode hqFdbkMode;
   U8 noOfTbs;



   TfuHqFdbk isAck[2];
   Bool isPusch;



} TfuHqInfo;





typedef struct tfuHqIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp hqIndLst;
} TfuHqIndInfo;




typedef struct tfuUlCqiInfo
{
   TfuSubbandCqiInfo subbandCqi;
} TfuUlCqiInfo;




typedef struct tfuUlCqiRpt
{
   CmLList lnk;
   CmLteRnti rnti;
   Bool isTxPort0;

   U8 wideCqi;
   U8 numSubband;
   TfuUlCqiInfo ulCqiInfoArr[110];
} TfuUlCqiRpt;







typedef struct tfuUlCqiIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp ulCqiRpt;
} TfuUlCqiIndInfo;




typedef struct tfuDoaRpt
{
   CmLList lnk;
   CmLteRnti rnti;
   U32 doa;
} TfuDoaRpt;







typedef struct tfuDoaIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLListCp doaRpt;
} TfuDoaIndInfo;





typedef struct tfuDlCqiRpt
{
   CmLList lnk;
   CmLteRnti rnti;
   Bool isPucchInfo;
   TfuDlCqiInfo dlCqiInfo;
} TfuDlCqiRpt;





typedef struct tfuDlCqiIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp dlCqiRptsLst;
} TfuDlCqiIndInfo;




typedef struct tfuCrcInfo
{
   CmLList lnk;
   CmLteRnti rnti;
   Bool isFailure;
   TknU8 rv;
   Bool isDtx;
} TfuCrcInfo;






typedef struct tfuCrcIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp crcLst;
} TfuCrcIndInfo;




 typedef struct tfuTimingAdvInfo
{
   CmLList lnk;
   CmLteRnti rnti;
   U8 timingAdv;
} TfuTimingAdvInfo;







typedef struct tfuTimingAdvIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp timingAdvLst;
} TfuTimingAdvIndInfo;




typedef struct tfuTtiCellInfo
{
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   Bool isDummyTti;

   U8 schTickDelta;

   U8 dlBlankSf;
   U8 ulBlankSf;

} TfuTtiCellInfo;




typedef struct tfuTtiIndInfo
{
   U8 numCells;
   TfuTtiCellInfo cells[8];

} TfuTtiIndInfo;
typedef struct tfuRaReqInfo
{
   U8 rapId;
   U16 ta;

   U8 tpc;

   Bool cqiPres;
   U8 cqiIdx;


} TfuRaReqInfo;



typedef struct tfuRachInfo
{
   CmLteRnti raRnti;
   U8 numRaReqInfo;
   TfuRaReqInfo *raReqInfoArr;
} TfuRachInfo;
typedef struct tfuRaReqIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   U8 nmbOfRaRnti;

   TfuRachInfo *rachInfoArr;


} TfuRaReqIndInfo;



typedef struct tfuPucchDeltaPwr
{
   CmLList lnk;
   CmLteRnti rnti;
   S8 pucchDeltaPwr;
} TfuPucchDeltaPwr;






typedef struct tfuPucchDeltaPwrIndInfo
{
   CmMemListCp memCp;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
   CmLListCp pucchDeltaPwrLst;

} TfuPucchDeltaPwrIndInfo;




typedef struct tfuErrIndInfo
{
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
} TfuErrIndInfo;

typedef S16 (*TfuBndReq) ( Pst* pst, SuId suId, SpId spId)


                              ;
typedef S16 (*TfuBndCfm) ( Pst* pst, SuId suId, U8 status)


                                ;
typedef S16 (*TfuUbndReq) ( Pst* pst, SpId spId, Reason reason)


                                ;

typedef S16 (*TfuSchBndReq) ( Pst* pst, SuId suId, SpId spId)


                              ;
typedef S16 (*TfuSchBndCfm) ( Pst* pst, SuId suId, U8 status)


                                ;
typedef S16 (*TfuSchUbndReq) ( Pst* pst, SpId spId, Reason reason)


                                ;

typedef S16 (*TfuRaReqInd) ( Pst * pst, SuId suId, TfuRaReqIndInfo *raReqInd)


                                   ;

typedef S16 (*TfuRecpReq) ( Pst * pst, SpId spId, TfuRecpReqInfo *recpReq)


                              ;

typedef S16 (*TfuUlCqiInd) ( Pst * pst, SuId suId, TfuUlCqiIndInfo * ulCqiInd)


                                  ;

typedef S16 (*TfuDoaInd) ( Pst * pst, SuId suId, TfuDoaIndInfo * doaInd)


                                ;
typedef S16 (*TfuHqInd) ( Pst * pst, SuId suId, TfuHqIndInfo * hqInd)


                          ;

typedef S16 (*TfuSrInd) ( Pst * pst, SuId suId, TfuSrIndInfo * srInd)


                               ;

typedef S16 (*TfuDlCqiInd) ( Pst * pst, SuId suId, TfuDlCqiIndInfo * dlCqiInd)


                                  ;


typedef S16 (*TfuRawCqiInd) ( Pst *pst, SuId suId, TfuRawCqiIndInfo *rawCqiInd)


                                       ;

typedef S16 (*TfuSrsInd) ( Pst *pst, SuId suId, TfuSrsIndInfo *srsInd)


                                    ;


typedef S16 (*TfuDatInd) ( Pst * pst, SuId suId, TfuDatIndInfo * datInd)


                                ;

typedef S16 (*TfuCrcInd) ( Pst * pst, SuId suId, TfuCrcIndInfo * crcInd)


                            ;

typedef S16 (*TfuTimingAdvInd) ( Pst * pst, SuId suId, TfuTimingAdvIndInfo * timingAdvInd)


                                       ;

typedef S16 (*TfuDatReq) ( Pst * pst, SpId spId, TfuDatReqInfo * datReq)


                                ;

typedef S16 (*TfuCntrlReq) ( Pst *pst, SpId spId, TfuCntrlReqInfo *cntrlReq)


                                         ;

typedef S16 (*TfuTtiCell) ( Pst * pst, SuId suId, TfuTtiCellInfo * ttiInd)


                                 ;

typedef S16 (*TfuTtiInd) ( Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd)


                                ;







typedef S16 (*TfuSchTtiInd) ( Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd)


                                ;

typedef S16 (*TfuPucchDeltaPwrInd) ( Pst * pst, SuId suId, TfuPucchDeltaPwrIndInfo * pucchDeltaPwr)


                                             ;


typedef S16 (*TfuErrInd) ( Pst * pst, SuId suId, TfuErrIndInfo * errInd)


                            ;







extern S16 TfUiTfuBndReq (Pst *pst, SuId suId, SpId spId);







extern S16 TfUiTfuSchBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 TfUiTfuBndCfm (Pst *pst, SuId suId, U8 status);







extern S16 TfUiTfuSchBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 TfUiTfuUbndReq (Pst *pst, SpId spId, Reason reason);







extern S16 TfUiTfuSchUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 TfUiTfuRaReqInd (Pst *pst, SuId suId, TfuRaReqIndInfo *raReqInd)
                    ;
extern S16 TfUiTfuRecpReq (Pst *pst, SpId spId, TfuRecpReqInfo *recpReq);
extern S16 TfUiTfuCntrlReq (Pst *pst, SpId spId, TfuCntrlReqInfo *cntrlReq);
extern S16 TfUiTfuDatReq (Pst *pst, SpId spId, TfuDatReqInfo *datReq);
extern S16 TfUiTfuDatInd (Pst *pst, SuId suId, TfuDatIndInfo *datInd);
extern S16 TfUiTfuHqInd (Pst *pst, SuId suId, TfuHqIndInfo *hqInd);
extern S16 TfUiTfuSrInd (Pst *pst, SuId suId, TfuSrIndInfo *srInd);
extern S16 TfUiTfuUlCqiInd (Pst *pst, SuId suId, TfuUlCqiIndInfo *ulCqiInd)
                                    ;
extern S16 TfUiTfuCrcInd (Pst *pst, SuId suId, TfuCrcIndInfo *crcIndInfo)
                                    ;
extern S16 TfUiTfuTimingAdvInd (Pst *pst, SuId suId, TfuTimingAdvIndInfo *timingAdvInd)
                                            ;
extern S16 TfUiTfuTtiCell (Pst *pst, SuId suId, TfuTtiCellInfo *ttiInd)
                                 ;
extern S16 TfUiTfuTtiInd (Pst *pst, SuId suId, TfuTtiIndInfo *ttiInd)
                                ;
extern S16 TfUiTfuSchTtiInd (Pst *pst, SuId suId, TfuTtiIndInfo *ttiInd)
                                ;
extern S16 TfUiTfuDlCqiInd (Pst *pst, SuId suId, TfuDlCqiIndInfo *dlCqiInd)
                                    ;
extern S16 TfUiTfuDoaInd (Pst *pst, SuId suId, TfuDoaIndInfo *doaInd)
                                ;
extern S16 TfUiTfuPucchDeltaPwrInd (Pst *pst, SuId suId, TfuPucchDeltaPwrIndInfo *pucchDeltaPwr)
                                                 ;
extern S16 TfUiTfuErrInd (Pst *pst, SuId suId, TfuErrIndInfo *errInd)
                                ;
extern S16 TfUiTfuSrsInd (Pst *pst, SuId suId, TfuSrsIndInfo *srsInd)
                                ;
extern S16 TfUiTfuRawCqiInd (Pst *pst, SuId suId, TfuRawCqiIndInfo *cqiInd)
                                   ;




extern S16 RgLiTfuBndReq ( Pst* pst, SuId suId, SpId spId )



  ;
extern S16 RgLiTfuBndCfm ( Pst* pst, SuId suId, U8 status )



  ;
extern S16 RgLiTfuUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;

extern S16 RgLiTfuSchBndReq ( Pst* pst, SuId suId, SpId spId )



  ;
extern S16 RgLiTfuSchBndCfm ( Pst* pst, SuId suId, U8 status )



  ;
extern S16 RgLiTfuSchUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;

extern S16 RgLiTfuRaReqInd ( Pst * pst, SpId spId, TfuRaReqIndInfo * raReq )



  ;


extern S16 RgLiTfuRecpReq ( Pst * pst, SpId spId, TfuRecpReqInfo * recpReq )



  ;

extern S16 RgLiTfuUlCqiInd ( Pst * pst, SuId suId, TfuUlCqiIndInfo * ulCqiInd )



  ;

extern S16 RgLiTfuDoaInd ( Pst * pst, SuId suId, TfuDoaIndInfo * doaInd )



  ;

extern S16 RgLiTfuHqInd ( Pst * pst, SuId suId, TfuHqIndInfo * hqInd )



  ;

extern S16 RgLiTfuSrInd ( Pst * pst, SuId suId, TfuSrIndInfo * srInd )



  ;

extern S16 RgLiTfuDlCqiInd ( Pst * pst, SuId suId, TfuDlCqiIndInfo * dlCqiInd )



  ;



extern S16 RgLiTfuRawCqiInd ( Pst *pst, SuId suId, TfuRawCqiIndInfo *rawCqiInd )



           ;
extern S16 RgLiTfuSrsInd ( Pst *pst, SuId suId, TfuSrsIndInfo *srsIndInfo )



           ;

extern S16 RgLiTfuDatInd ( Pst * pst, SuId suId, TfuDatIndInfo * datInd )



  ;

extern S16 RgLiTfuCrcInd ( Pst * pst, SuId suId, TfuCrcIndInfo * crcInd )



  ;

extern S16 RgLiTfuTimingAdvInd ( Pst * pst, SuId suId, TfuTimingAdvIndInfo * timingAdvInd )



  ;

extern S16 RgLiTfuDatReq ( Pst * pst, SpId spId, TfuDatReqInfo * datReq )



  ;

extern S16 RgLiTfuCntrlReq ( Pst * pst, SpId spId, TfuCntrlReqInfo * cntrlReq )



  ;

extern S16 RgLiTfuTtiInd ( Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd )



  ;

extern S16 RgLiTfuSchTtiInd ( Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd )



  ;
extern S16 RgLiTfuPucchDeltaPwrInd ( Pst * pst, SuId suId, TfuPucchDeltaPwrIndInfo *pucchDeltaPwr )



     ;
extern S16 RgLiTfuErrInd (Pst *pst, SuId suId, TfuErrIndInfo *errInd);




extern S16 cmPkTfuBndReq ( Pst* pst, SuId suId, SpId spId )



  ;


extern S16 cmUnpkTfuBndReq ( TfuBndReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuBndCfm ( Pst* pst, SuId suId, U8 status )



  ;


extern S16 cmUnpkTfuBndCfm ( TfuBndCfm func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;


extern S16 cmUnpkTfuUbndReq ( TfuUbndReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuSchBndReq ( Pst* pst, SuId suId, SpId spId )



  ;


extern S16 cmUnpkTfuSchBndReq ( TfuSchBndReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuSchBndCfm ( Pst* pst, SuId suId, U8 status )



  ;


extern S16 cmUnpkTfuSchBndCfm ( TfuSchBndCfm func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuSchUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;


extern S16 cmUnpkTfuSchUbndReq ( TfuSchUbndReq func, Pst* pst, Buffer *mBuf )



  ;



extern S16 cmPkTfuRaReqInd ( Pst * pst, SuId suId, TfuRaReqIndInfo * raReqInd )



  ;



extern S16 cmUnpkTfuRaReqInd ( TfuRaReqInd func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkTfuRecpReq ( Pst * pst, SpId spId, TfuRecpReqInfo * recpReq )



  ;



extern S16 cmUnpkTfuRecpReq ( TfuRecpReq func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuUlCqiInd ( Pst * pst, SuId suId, TfuUlCqiIndInfo * ulCqiInd )



  ;


extern S16 cmUnpkTfuUlCqiInd ( TfuUlCqiInd func, Pst * pst, Buffer *mBuf )



  ;

extern S16 cmPkTfuHqInd ( Pst * pst, SuId suId, TfuHqIndInfo * hqInd )



  ;

extern S16 cmUnpkTfuHqInd ( TfuHqInd func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuSrInd ( Pst * pst, SuId suId, TfuSrIndInfo * srInd )



  ;


extern S16 cmUnpkTfuSrInd ( TfuSrInd func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkTfuDlCqiInd ( Pst * pst, SuId suId, TfuDlCqiIndInfo * dlCqiInd )



  ;



extern S16 cmUnpkTfuDlCqiInd ( TfuDlCqiInd func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmUnpkTfuDoaInd ( TfuDoaInd func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkTfuDoaInd ( Pst * pst, SuId suId, TfuDoaIndInfo * doaInd )



     ;



extern S16 cmPkTfuDatInd ( Pst * pst, SuId suId, TfuDatIndInfo * datInd )



  ;


extern S16 cmUnpkTfuDatInd ( TfuDatInd func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuCrcInd ( Pst * pst, SuId suId, TfuCrcIndInfo * crcInd )



  ;


extern S16 cmUnpkTfuCrcInd ( TfuCrcInd func, Pst * pst, Buffer *mBuf )



  ;

extern S16 cmPkTfuCntrlReq ( Pst * pst, SpId spId, TfuCntrlReqInfo * cntrlReq )



  ;

extern S16 cmUnpkTfuCntrlReq ( TfuCntrlReq func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuTimingAdvInd ( Pst * pst, SuId suId, TfuTimingAdvIndInfo * timingAdvInd )



  ;


extern S16 cmUnpkTfuTimingAdvInd ( TfuTimingAdvInd func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkTfuDatReq ( Pst * pst, SpId spId, TfuDatReqInfo * datReq )



  ;


extern S16 cmUnpkTfuDatReq ( TfuDatReq func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkTfuTtiCell ( Pst * pst, SuId suId, TfuTtiCellInfo * ttiInd )



  ;


extern S16 cmUnpkTfuTtiCell ( TfuTtiCell func, Pst * pst, Buffer *mBuf )



  ;




extern S16 cmPkTfuTtiInd ( Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd )



  ;


extern S16 cmUnpkTfuTtiInd ( TfuTtiInd func, Pst * pst, Buffer *mBuf )



  ;
extern S16 cmPkTfuSchTtiInd ( Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd )



  ;


extern S16 cmUnpkTfuSchTtiInd ( TfuSchTtiInd func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkTfuPucchDeltaPwrInd ( Pst * pst, SuId suId, TfuPucchDeltaPwrIndInfo * pucchDeltaPwr )



  ;


extern S16 cmUnpkTfuPucchDeltaPwrInd ( TfuPucchDeltaPwrInd func, Pst * pst, Buffer *mBuf )



  ;
extern S16 cmPkTfuDciFormat0Info ( TfuDciFormat0Info *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat0Info ( TfuDciFormat0Info *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuAllocMapOrRiv ( TfuAllocMapOrRiv *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuAllocMapOrRiv ( TfuAllocMapOrRiv *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1AllocInfo ( TfuDciFormat1AllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1AllocInfo ( TfuDciFormat1AllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1Info ( TfuDciFormat1Info *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1Info ( TfuDciFormat1Info *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuDciFormatTbInfo ( TfuDciFormatTbInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormatTbInfo ( TfuDciFormatTbInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuDciFormat2AAllocInfo ( TfuDciFormat2AAllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat2AAllocInfo ( TfuDciFormat2AAllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat2AInfo ( TfuDciFormat2AInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat2AInfo ( TfuDciFormat2AInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat2AllocInfo ( TfuDciFormat2AllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat2AllocInfo ( TfuDciFormat2AllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat2Info ( TfuDciFormat2Info *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat2Info ( TfuDciFormat2Info *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat3Info ( TfuDciFormat3Info *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat3Info ( TfuDciFormat3Info *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat3AInfo ( TfuDciFormat3AInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat3AInfo ( TfuDciFormat3AInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1dAllocInfo ( TfuDciFormat1dAllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1dAllocInfo ( TfuDciFormat1dAllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1dInfo ( TfuDciFormat1dInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1dInfo ( TfuDciFormat1dInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1cInfo ( TfuDciFormat1cInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1cInfo ( TfuDciFormat1cInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1bAllocInfo ( TfuDciFormat1bAllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1bAllocInfo ( TfuDciFormat1bAllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuPdcchOrderInfo ( TfuPdcchOrderInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuPdcchOrderInfo ( TfuPdcchOrderInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1aAllocInfo ( TfuDciFormat1aAllocInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1aAllocInfo ( TfuDciFormat1aAllocInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkTfudciformat1aPdsch ( Tfudciformat1aPdsch *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfudciformat1aPdsch ( Tfudciformat1aPdsch *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1aInfo ( TfuDciFormat1aInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1aInfo ( TfuDciFormat1aInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciFormat1bInfo ( TfuDciFormat1bInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciFormat1bInfo ( TfuDciFormat1bInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDciInfo ( TfuDciInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDciInfo ( TfuDciInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuSubbandInfo ( TfuSubbandInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSubbandInfo ( TfuSubbandInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuSubbandDlCqiInfo ( TfuSubbandDlCqiInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSubbandDlCqiInfo ( TfuSubbandDlCqiInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuSubbandCqiInfo ( TfuSubbandCqiInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSubbandCqiInfo ( TfuSubbandCqiInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuPdcchCceInfo ( TfuPdcchCceInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuPdcchCceInfo ( TfuPdcchCceInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPucchMode10 ( TfuCqiPucchMode10 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPucchMode10 ( TfuCqiPucchMode10 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiMode11Cqi ( TfuCqiMode11Cqi *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiMode11Cqi ( TfuCqiMode11Cqi *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPucchMode11 ( TfuCqiPucchMode11 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPucchMode11 ( TfuCqiPucchMode11 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiMode20SubCqi ( TfuCqiMode20SubCqi *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiMode20SubCqi ( TfuCqiMode20SubCqi *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiMode20Cqi ( TfuCqiMode20Cqi *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiMode20Cqi ( TfuCqiMode20Cqi *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPucchMode20 ( TfuCqiPucchMode20 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPucchMode20 ( TfuCqiPucchMode20 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiMode21SubCqi ( TfuCqiMode21SubCqi *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiMode21SubCqi ( TfuCqiMode21SubCqi *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiMode21WideCqi ( TfuCqiMode21WideCqi *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiMode21WideCqi ( TfuCqiMode21WideCqi *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiMode21Cqi ( TfuCqiMode21Cqi *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiMode21Cqi ( TfuCqiMode21Cqi *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPucchMode21 ( TfuCqiPucchMode21 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPucchMode21 ( TfuCqiPucchMode21 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDlCqiPucch ( TfuDlCqiPucch *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDlCqiPucch ( TfuDlCqiPucch *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuSubbandMode12 ( TfuSubbandMode12 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSubbandMode12 ( TfuSubbandMode12 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPuschMode12 ( TfuCqiPuschMode12 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPuschMode12 ( TfuCqiPuschMode12 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPuschMode20 ( TfuCqiPuschMode20 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPuschMode20 ( TfuCqiPuschMode20 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPuschMode22 ( TfuCqiPuschMode22 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPuschMode22 ( TfuCqiPuschMode22 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuSubbandMode30 ( TfuSubbandMode30 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSubbandMode30 ( TfuSubbandMode30 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPuschMode30 ( TfuCqiPuschMode30 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPuschMode30 ( TfuCqiPuschMode30 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuSubbandMode31 ( TfuSubbandMode31 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSubbandMode31 ( TfuSubbandMode31 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCqiPuschMode31 ( TfuCqiPuschMode31 *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCqiPuschMode31 ( TfuCqiPuschMode31 *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDlCqiPusch ( TfuDlCqiPusch *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDlCqiPusch ( TfuDlCqiPusch *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuDlCqiPuschInfo ( TfuDlCqiPuschInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDlCqiPuschInfo ( TfuDlCqiPuschInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuDoaRpt ( TfuDoaRpt *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDoaRpt ( TfuDoaRpt *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDoaIndInfo ( TfuDoaIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDoaIndInfo ( TfuDoaIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;

extern S16 cmPkTfuDlCqiInfo ( U8 selector, TfuDlCqiInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkTfuDlCqiInfo ( U8 selector, TfuDlCqiInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkTfuUePuschRecpReq ( TfuUePuschRecpReq *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUePuschRecpReq ( TfuUePuschRecpReq *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuUePucchRecpReq ( TfuUePucchRecpReq *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUePucchRecpReq ( TfuUePucchRecpReq *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuRecpReqInfo ( TfuRecpReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuRecpReqInfo ( TfuRecpReqInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuPdcchInfo ( TfuPdcchInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuPdcchInfo ( TfuPdcchInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuPhichInfo ( TfuPhichInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuPhichInfo ( TfuPhichInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCntrlReqInfo ( TfuCntrlReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCntrlReqInfo ( TfuCntrlReqInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuPdschDciInfo ( TfuPdschDciInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuPdschDciInfo ( TfuPdschDciInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDatReqPduInfo ( TfuDatReqPduInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDatReqPduInfo ( TfuDatReqPduInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDatReqInfo ( TfuDatReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDatReqInfo ( TfuDatReqInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuDatInfo ( TfuDatInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDatInfo ( TfuDatInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDatIndInfo ( TfuDatIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDatIndInfo ( TfuDatIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuSrInfo ( TfuSrInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSrInfo ( TfuSrInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuSrIndInfo ( TfuSrIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSrIndInfo ( TfuSrIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuHqInfo ( TfuHqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuHqInfo ( TfuHqInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuHqIndInfo ( TfuHqIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuHqIndInfo ( TfuHqIndInfo *param, Ptr memCpm, Buffer *mBuf )



  ;
extern S16 cmPkTfuUlCqiInfo ( TfuUlCqiInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUlCqiInfo ( TfuUlCqiInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuUlCqiRpt ( TfuUlCqiRpt *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUlCqiRpt ( TfuUlCqiRpt *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuUlCqiIndInfo ( TfuUlCqiIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUlCqiIndInfo ( TfuUlCqiIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuDlCqiRpt ( TfuDlCqiRpt *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDlCqiRpt ( TfuDlCqiRpt *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuDlCqiIndInfo ( TfuDlCqiIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuDlCqiIndInfo ( TfuDlCqiIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuPucchDeltaPwr ( Pst * pst, SuId suId, TfuPucchDeltaPwrIndInfo * pucchDeltaPwr)


                                            ;

extern S16 cmPkTfuPucchDeltaPwrInfo ( TfuPucchDeltaPwr *param, Buffer *mBuf )


  ;

extern S16 cmUnpkTfuPucchDeltaPwr ( TfuPucchDeltaPwrInd func, Pst * pst, Buffer *mBuf )



  ;
extern S16 cmUnpkTfuPucchDeltaPwrInfo ( TfuPucchDeltaPwr *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuCrcInfo ( TfuCrcInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCrcInfo ( TfuCrcInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuCrcIndInfo ( TfuCrcIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuCrcIndInfo ( TfuCrcIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;

extern S16 cmPkTfuPucchDeltaPwrIndInfo ( TfuPucchDeltaPwrIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuPucchDeltaPwrIndInfo ( TfuPucchDeltaPwrIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuTimingAdvInfo ( TfuTimingAdvInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuTimingAdvInfo ( TfuTimingAdvInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuTimingAdvIndInfo ( TfuTimingAdvIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuTimingAdvIndInfo ( TfuTimingAdvIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;

extern S16 cmPkTfuTtiCellInfo ( TfuTtiCellInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuTtiCellInfo ( TfuTtiCellInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuTtiIndInfo ( TfuTtiIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuTtiIndInfo ( TfuTtiIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuRaReqInfo ( TfuRaReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuRaReqInfo ( TfuRaReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuRachInfo ( CmMemListCp memCp, TfuRachInfo *param, Buffer *mBuf )



  ;
extern S16 cmUnpkTfuRachInfo ( CmMemListCp memCp, TfuRachInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkTfuRaReqIndInfo ( TfuRaReqIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuRaReqIndInfo ( TfuRaReqIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkBuffer ( Buffer **param, Buffer *mBuf )


  ;
extern S16 cmUnpkBuffer ( Buffer **param, Buffer *mBuf )


  ;



extern S16 cmPkTfuSrsRpt ( TfuSrsRpt *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSrsRpt ( TfuSrsRpt *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuSrsIndInfo ( TfuSrsIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuSrsIndInfo ( TfuSrsIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuRawCqiRpt ( TfuRawCqiRpt *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuRawCqiRpt ( TfuRawCqiRpt *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuRawCqiIndInfo ( TfuRawCqiIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuRawCqiIndInfo ( TfuRawCqiIndInfo *param, Ptr memCp, Buffer *mBuf )



  ;
extern S16 cmPkTfuUePucchHqRecpInfo ( TfuUePucchHqRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUePucchHqRecpInfo ( TfuUePucchHqRecpInfo *param, Buffer *mBuf )


  ;



extern S16 cmPkTfuUePucchSrRecpInfo ( TfuUePucchSrRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUePucchSrRecpInfo ( TfuUePucchSrRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuUePucchCqiRecpInfo ( TfuUePucchCqiRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUePucchCqiRecpInfo ( TfuUePucchCqiRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuUePucchSrsRecpInfo ( TfuUePucchSrsRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUePucchSrsRecpInfo ( TfuUePucchSrsRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuUeUlSchRecpInfo ( TfuUeUlSchRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUeUlSchRecpInfo ( TfuUeUlSchRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuUePuschCqiRecpInfo ( TfuUePuschCqiRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUePuschCqiRecpInfo ( TfuUePuschCqiRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuUePuschHqRecpInfo ( TfuUePuschHqRecpInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUePuschHqRecpInfo ( TfuUePuschHqRecpInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkTfuBfVectorInfo ( TfuBfVectorInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkTfuBfVectorInfo ( TfuBfVectorInfo *param, Buffer *mBuf )


  ;


extern S16 cmPkTfuUeRecpReqInfo ( TfuUeRecpReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuUeRecpReqInfo ( TfuUeRecpReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkTfuRawCqiInd ( Pst * pst, SuId suId, TfuRawCqiIndInfo * rawCqiInd )



  ;
extern S16 cmUnpkTfuRawCqiInd ( TfuRawCqiInd func, Pst * pst, Buffer *mBuf )



  ;
extern S16 cmPkTfuSrsInd ( Pst * pst, SuId suId, TfuSrsIndInfo * srsInd )



  ;
extern S16 cmUnpkTfuSrsInd ( TfuSrsInd func, Pst * pst, Buffer *mBuf )



  ;




extern S16 cmPkTfuAllocMap ( TfuAllocMap *param, Buffer *mBuf )


  ;
extern S16 cmUnpkTfuAllocMap ( TfuAllocMap *param, Buffer *mBuf )


  ;



extern S16 cmPkTfuErrInd ( Pst * pst, SuId suId, TfuErrIndInfo * errInd )



  ;

extern S16 cmUnpkTfuErrInd ( TfuErrInd func, Pst * pst, Buffer *mBuf )



  ;

typedef struct ysCb YsCb;
typedef struct ysCellCb YsCellCb;
typedef struct ysUeCb YsUeCb;
typedef struct ysCtfSapCb
{
   Pst sapPst;
   SpId spId;
   SuId suId;
   State sapState;
   YsCtfSapSts ctfSts;
}YsCtfSapCb;

typedef struct ysTfuSapCb
{
   YsTfuSapCfg tfuSapCfg;
   Pst sapPst;
   SpId spId;
   SuId suId;
   YsCellCb *cellCb;
   State sapState;
   YsTfuSapSts tfuSts;
   YsL1PhySts phySts;
}YsTfuSapCb;
typedef struct ysTxMsgInfo
{
   Event event;
   Void *tfuMsg;
} YsTxMsgInfo;

typedef struct ysTxMsgArr
{
   U8 num;
   YsTxMsgInfo txMsgInfo[10];
} YsTxMsgArr;
struct ysUeCb
{
   CmLteRnti ueId;
   CtfDedCfgInfo ueCfg;
   YsCellCb *cellCb;
   CmLList lnkUeLst;
};




typedef struct ysUeListCb
{
   CmLListCp ueLst;

}YsUeListCb;




typedef struct ysUeLst
{
   U16 numUe;
   YsUeCb *ueLst[2];
}YsUeLst;



typedef struct YsPicoSpecific
{
   U16 syncSigPowOs;
   Bool syncSigPowOsPres;
   U16 cfiPowOs;
   Bool cfiPowOsPres;
   U16 dciPowOs;
   Bool dciPowOsPres;
   U16 extWinMargin;
   Bool extWinMarginPres;
   U16 pucchNoiseGamma;
   Bool pucchNoiseGammaPres;
   U16 prachPkRatio4;
   Bool prachPkRatio4Pres;
   U16 prachPkRatio0;
   Bool prachPkRatio0Pres;
   U16 srsDopEstFactor;
   Bool srsDopEstFactorPres;
   U16 puschProbDtxAck;
   Bool puschProbDtxAckPres;
   U16 pucchProbDtxAck;
   Bool pucchProbDtxAckPres;

   U16 txAntennaPorts ;
   Bool txAntennaPortsPres;
   U16 rxAntennaPorts ;
   Bool rxAntennaPortsPres ;

   U16 phySyncMode;
   Bool phySyncModePres;
   U16 dataRepMode;
   Bool dataRepModePres ;
   U16 rachSrRepMode;
   Bool rachSrRepModePres;

   U8 ctfReCfgType;
   Bool bwCfgPres;
   Bool txCfgPres;
   Bool phyCellIdPres;
   U8 phyCellId;
   CtfBwCfgInfo bwCfg;
   CtfTxSchemeCfg txCfg;
   CtfAntennaCfgInfo antennaCfg;

}YsPicoSpecific;


struct ysCellCb
{
   CmLteCellId cellId;
   CtfCellCfgInfo cellCfg;
   U8 dlBw;
   U8 ulBw;
   CmLteTimingInfo timingInfo;
   YsTfuSapCb *tfuSap;
   YsTfuSapCb *schTfuSap;
   YsUeListCb ueLstCb;
   YsTxMsgArr txMsgArr[10];

   Pst peerPst;

   State phyState;

   U8 nCceInfo[10];




   YsPicoSpecific vendorParams ;


};





struct ysCb
{
   TskInit ysInit;
   S16 trcLen;
   YsCtfSapCb ctfSap;
   YsTfuSapCb *tfuSapLst[2];
   YsTfuSapCb *schTfuSapLst[2];
   YsCellCb *cellCb[2];

   Txt apb[10000];
   YsGenCfg genCfg;



   CmTqCp tmrTqCp;
   CmTqType tmrTq[2];
   CmTimer tmr;


   U32 sockfd;


   Bool ttiReady;


};


extern YsCb ysCb;
extern S16 ysActvInit (Ent entity, Inst inst, Region region, Reason reason)
                              ;
extern S16 ysActvTsk (Pst *pst, Buffer *mBuf);

extern Void ysGetSId (SystemId *s);

extern S16 ysLMMStaInd ( U16 category, U16 event, U16 cause, YsUstaDgn *dgn )




  ;

extern Data * ysUtlMalloc ( Size size )

  ;

extern Void ysUtlDeAlloc ( Data *buf, Size size )


  ;

extern S16 ysUtlAllocEventMem ( Ptr *memPtr, Size memSize )


  ;

extern S16 ysUtlFreeEventMem ( Ptr memPtr )

  ;

extern YsCellCb *ysUtlGetCellCfg ( CmLteCellId cellId )

  ;

extern YsUeCb *ysUtlGetUe ( YsCellCb *cellCb, CmLteRnti ueId )


  ;

 S16 ysUtlDelCellCfg ( CmLteCellId cellId )

  ;

 S16 ysUiChkAndGetCtfSap ( SpId spId, YsCtfSapCb **ctfSapCb )


  ;

extern S16 ysUtlDeAllocUeCb ( YsCellCb *cellCb, YsUeCb *ueCb )


  ;


extern S16 ysPalInitTti ( Void )

  ;

extern S16 ysPalDeinitTti ( Void )

  ;

extern S16 ysPalPrcCntrlReq ( YsCellCb *cellCb, TfuCntrlReqInfo *cntrlReq )


  ;

extern S16 ysPalPrcDatReq ( YsCellCb *cellCb, TfuDatReqInfo *datReq )


  ;

extern S16 ysPalPrcRecpReq ( YsCellCb *cellCb, TfuRecpReqInfo *recpReq )


  ;
extern S16 ysPalUtlSetTfuMsg ( YsCellCb *cellCb, Void *tfuMsg, Event event, CmLteTimingInfo *timingInfo )




  ;


extern Void ysPalHdlTtiInd ( CmLteTimingInfo *timingInfo )

  ;






extern Void ysPalHdlDlMsg ( CmLteTimingInfo *timingInfo, YsCellCb *cellCb )


  ;


extern S16 ysPalInitRcvrTsk (Void);
extern S16 ysPalInitTtiTmrTsk (Void);
extern S16 ysPalSend2Peer ( Buffer *mBuf, U8 cellId);




extern S16 YsRecvMsg (Void *buf);

extern Void ysUtlFreeDatReq (TfuDatReqInfo *datReq);



extern Void ysPrcTmrExpiry (Ptr cb, S16 tmrEvnt);


extern S16 ysInitCfg (Void);


extern S16 TfUiTfuBndCfm (Pst* pst, SuId suId, U8 status);
extern S16 TfUiTfuSchBndCfm (Pst* pst, SuId suId, U8 status);
extern S16 TfUiTfuRaReqInd (Pst * pst, SuId suId, TfuRaReqIndInfo * raReqInd);
extern S16 TfUiTfuUlCqiInd (Pst * pst, SuId suId, TfuUlCqiIndInfo * ulCqiInd);
extern S16 TfUiTfuHqInd (Pst * pst, SuId suId, TfuHqIndInfo *hqInd);
extern S16 TfUiTfuSrInd (Pst * pst, SuId suId, TfuSrIndInfo * srInd);
extern S16 TfUiTfuDlCqiInd (Pst * pst, SuId suId, TfuDlCqiIndInfo * dlCqiInd);
extern S16 TfUiTfuDatInd (Pst * pst, SuId suId, TfuDatIndInfo * datInd);
extern S16 TfUiTfuCrcInd (Pst * pst, SuId suId, TfuCrcIndInfo * crcInd);
extern S16 TfUiTfuTimingAdvInd (Pst * pst, SuId suId, TfuTimingAdvIndInfo * timingAdvInd);
extern S16 TfUiTfuTtiInd (Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd);
extern S16 TfUiTfuSchTtiInd (Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd);
extern S16 TfUiCtfBndCfm (Pst* pst, SuId suId, U8 status);
extern S16 TfUiCtfCfgCfm (Pst* pst, SuId suId, CtfCfgTransId transId, U8 status);

extern S16 ysUtlAllocEventMem1 (Ptr *memPtr,Size memSize);
extern Void postToApp (Buffer *mBuf, U8 radioType, U8 direction, U8 rntiType, U16 rnti,U16 ueid, U16 subframe, U8 isPredefinedData, U8 retx, U8 crcStatus)

                                                                         ;
 Data * ysUtlMalloc
(
Size size
)




{
   TskInit *ysInit;
   Data *buf;

   ;

   buf = 0L;
   ysInit = &(ysCb.ysInit);
   if((SGetSBuf(ysInit->region, ysInit->pool, &buf, size) != 0) ||
      (buf == 0L))
   {
      return(0L);
   }


   cmMemset (buf, 0, size);

   return(buf);

}
 Void ysUtlDeAlloc
(
Data *buf,
Size size
)





{
   TskInit *ysInit;

   ;
   ysInit = &(ysCb.ysInit);


   SPutSBuf (ysInit->region, ysInit->pool, buf, size);

   return;

}
 S16 ysUtlAllocEventMem
(
Ptr *memPtr,
Size memSize
)





{
   Mem sMem;

   ;

   sMem.region = ysCb.ysInit.region;
   sMem.pool = ysCb.ysInit.pool;
   if(0 != cmAllocEvnt(memSize, 1500, &sMem, memPtr))
   {
      { if (ysCb.ysInit.dbgMask >= (2)) { { if ((&ysCb.ysInit)->dbgMask & (2)) { snprintf((&ysCb.ysInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Ys", (&ysCb.ysInit)->procId, (&ysCb.ysInit)->ent, (&ysCb.ysInit)->inst,
                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lteclpal/ys_pal_utl1.c"
      ,
                                                    218
      ); SPrint((&ysCb.ysInit)->prntBuf); sprintf (ysCb.apb, "%s", "Failed: "); SPrint((&ysCb.ysInit)->prntBuf); } }; { if ((&ysCb.ysInit)->dbgMask & (2)) { snprintf((&ysCb.ysInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Ys", (&ysCb.ysInit)->procId, (&ysCb.ysInit)->ent, (&ysCb.ysInit)->inst,
                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lteclpal/ys_pal_utl1.c"
      ,
                                                    218
      ); SPrint((&ysCb.ysInit)->prntBuf); sprintf (ysCb.apb, "Returning RFAILED form ysUtlAllocEventMem because                     cmAllocEvnt returned RFAILED\n"); SPrint((&ysCb.ysInit)->prntBuf); } }; } }
                                                     ;
      *memPtr = 0L;
      return(1);
   }

   return(0);

}



 S16 ysUtlAllocEventMem1
(
Ptr *memPtr,
Size memSize
)





{
   Mem sMem;

   ;

   sMem.region = ysCb.ysInit.region;
   sMem.pool = ysCb.ysInit.pool;
   if(0 != cmAllocEvnt(memSize, 1500, &sMem, memPtr))
   {
      { if (ysCb.ysInit.dbgMask >= (2)) { { if ((&ysCb.ysInit)->dbgMask & (2)) { snprintf((&ysCb.ysInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Ys", (&ysCb.ysInit)->procId, (&ysCb.ysInit)->ent, (&ysCb.ysInit)->inst,
                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lteclpal/ys_pal_utl1.c"
      ,
                                                    258
      ); SPrint((&ysCb.ysInit)->prntBuf); sprintf (ysCb.apb, "%s", "Failed: "); SPrint((&ysCb.ysInit)->prntBuf); } }; { if ((&ysCb.ysInit)->dbgMask & (2)) { snprintf((&ysCb.ysInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Ys", (&ysCb.ysInit)->procId, (&ysCb.ysInit)->ent, (&ysCb.ysInit)->inst,
                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lteclpal/ys_pal_utl1.c"
      ,
                                                    258
      ); SPrint((&ysCb.ysInit)->prntBuf); sprintf (ysCb.apb, "Returning RFAILED form ysUtlAllocEventMem because                     cmAllocEvnt returned RFAILED\n"); SPrint((&ysCb.ysInit)->prntBuf); } }; } }
                                                     ;
      *memPtr = 0L;
      return(1);
   }

   return(0);

}
 S16 ysUtlFreeEventMem
(
Ptr memPtr
)




{
   ;
   cmFreeMem(memPtr);

   return(0);
}
 Void ysUtlFreeDatReq
(
TfuDatReqInfo *datReq
)




{
   U8 idx;
   TfuDatReqPduInfo *pduInfo;
   CmLList *cmLstEnt;
   if (datReq->bchDat.pres == 1)
   {
      SPutMsg (datReq->bchDat.val);
      datReq->bchDat.val = 0L;
   }
   cmLstEnt = datReq->pdus.first;
   while (cmLstEnt != 0L)
   {
      pduInfo = (TfuDatReqPduInfo *)cmLstEnt->node;
      for (idx = 0; idx < 2; idx++)
      {
         if((pduInfo) && (pduInfo->mBuf[idx] != 0L))
         {
            SPutMsg (pduInfo->mBuf[idx]);
            pduInfo->mBuf[idx] = 0L;
         }
      }
      cmLstEnt = cmLstEnt->next;
   }
   ysUtlFreeEventMem((Ptr)datReq);
}
 YsCellCb *ysUtlGetCellCfg
(
CmLteCellId cellId
)




{
   YsCellCb *cellCb;
   U16 indx;

   ;

   cellCb = 0L;
   for(indx = 0; indx < 2; indx++)
   {
      if((ysCb.cellCb[indx] != 0L) && (cellId == ysCb.cellCb[indx]->cellId))
      {
         cellCb = ysCb.cellCb[indx];
         break;
      }
   }




   return(cellCb);
}
 YsUeCb *ysUtlGetUe
(
YsCellCb *cellCb,
CmLteRnti ueId
)





{
   YsUeCb *ueCb;
   CmLList *cmLstEnt;

   ;

   ueCb = 0L;

   cmLstEnt = cellCb->ueLstCb.ueLst.first;
   while (cmLstEnt != 0L)
   {
      if (((YsUeCb *)cmLstEnt->node)->ueId == ueId)
      {
         ueCb = (YsUeCb *)(cmLstEnt->node);
         break;
      }


      cmLstEnt = cmLstEnt->next;
   }

   return(ueCb);
}
 S16 ysUtlDelCellCfg
(
CmLteCellId cellId
)




{
   S16 ret;
   YsCellCb *cellCb;
   YsUeCb *ueCb;

   ;

   { if (ysCb.ysInit.dbgMask >= (3)) { { if ((&ysCb.ysInit)->dbgMask & (3)) { snprintf((&ysCb.ysInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Ys", (&ysCb.ysInit)->procId, (&ysCb.ysInit)->ent, (&ysCb.ysInit)->inst, "/home/mrehwald/Desktop/Radisys/lte_enb/src/lteclpal/ys_pal_utl1.c", 491); SPrint((&ysCb.ysInit)->prntBuf); sprintf (ysCb.apb, "%s", "Param : "); SPrint((&ysCb.ysInit)->prntBuf); } }; { if ((&ysCb.ysInit)->dbgMask & (3)) { snprintf((&ysCb.ysInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Ys", (&ysCb.ysInit)->procId, (&ysCb.ysInit)->ent, (&ysCb.ysInit)->inst, "/home/mrehwald/Desktop/Radisys/lte_enb/src/lteclpal/ys_pal_utl1.c", 491); SPrint((&ysCb.ysInit)->prntBuf); sprintf (ysCb.apb, "ysUtlDelCellCfg(): cellId = %d \n", cellId); SPrint((&ysCb.ysInit)->prntBuf); } }; } };

   ret = 0;
   cellCb = 0L;
   ueCb = 0L;

   if((cellCb = ysUtlGetCellCfg(cellId)) == 0L)
   {
      { if (ysCb.ysInit.dbgMask >= (2)) { { if ((&ysCb.ysInit)->dbgMask & (2)) { snprintf((&ysCb.ysInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Ys", (&ysCb.ysInit)->procId, (&ysCb.ysInit)->ent, (&ysCb.ysInit)->inst,
                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/lteclpal/ys_pal_utl1.c"
      ,
                                                        500
      ); SPrint((&ysCb.ysInit)->prntBuf); sprintf (ysCb.apb, "%s", "Failed: "); SPrint((&ysCb.ysInit)->prntBuf); } }; { if ((&ysCb.ysInit)->dbgMask & (2)) { snprintf((&ysCb.ysInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Ys", (&ysCb.ysInit)->procId, (&ysCb.ysInit)->ent, (&ysCb.ysInit)->inst,
                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/lteclpal/ys_pal_utl1.c"
      ,
                                                        500
      ); SPrint((&ysCb.ysInit)->prntBuf); sprintf (ysCb.apb, "Cell Configuration doesnt exist for cell (%d).                      ysUtlDelCellCfg Failed \n", cellId); SPrint((&ysCb.ysInit)->prntBuf); } }; } }
                                                         ;
      return(1);
   }



   return(ret);
}
 S16 ysUtlDeAllocUeCb
(
YsCellCb *cellCb,
YsUeCb *ueCb
)





{

   ;


   cmLListDelFrm(&(cellCb->ueLstCb.ueLst), &(ueCb->lnkUeLst));


   ysUtlDeAlloc((Data *)ueCb, sizeof(YsUeCb));

   return(0);
}
void postToApp(Buffer *mBuf, U8 radioType, U8 direction, U8 rntiType,
                       U16 rnti, U16 ueid, U16 subframe,
                       U8 isPredefinedData, U8 retx, U8 crcStatus)
{
}
