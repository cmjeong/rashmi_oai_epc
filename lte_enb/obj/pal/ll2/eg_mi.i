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
 U8 *cmMemcpy (U8 *tgt, const U8 *src, U32 len);
 S16 cmMemcmp (const U8 *s1, const U8 *s2, U32 len);
 U8 *cmMemset (U8 *src, U8 val, U32 len);

 S16 cmStrcmp (const U8 *s1, const U8 *s2);

 S16 cmStrncmp (const U8 *s1, const U8 *s2, MsgLen len);
 MsgLen cmStrlen (const U8 *s);
enum EG_DBG_PTR_TYPE
{
  EG_DBG_NONE,
  EG_DBG_UI,
  EG_DBG_CPM,
  EG_DBG_TUNN,
  EG_DBG_TSAP,
  EG_DBG_SSAP,
  EG_DBG_ENT,
  EG_DBG_CMTPTADDR,
  EG_DBG_CMNETADDR,
  EG_DBG_CMTNETDDRLST,
  EG_DBG_TPTSERV,
  EG_DBG_MNGMT,
  EG_DBG_BUF,
  EG_DBG_EVNT,
  EG_DBG_LI,
  EG_DBG_TPT
};





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
typedef CmInetIpv4Addr CmIpv4TptAddr;
typedef CmInetIpAddr CmIpv4NetAddr;


typedef U8 CmInetIpAddr6[16];


typedef struct cmInetIpv6Addr
{
   U16 port;
   CmInetIpAddr6 ipv6NetAddr;
} CmInetIpv6Addr;



typedef CmInetIpv6Addr CmIpv6TptAddr;
typedef CmInetIpAddr6 CmIpv6NetAddr;




typedef struct cmNetAddr
{
   U8 type;
   union
   {
      CmIpv4NetAddr ipv4NetAddr;
      CmIpv6NetAddr ipv6NetAddr;
   }u;
} CmNetAddr;


typedef struct _cmNetAddrTbl
{
   U16 count;
   CmNetAddr netAddr[16];
}CmNetAddrTbl;
typedef struct cmNetMCastInf
{
   CmNetAddr mCastAddr;
   CmNetAddr localAddr;
} CmNetMCastInf;







typedef struct cmTptAddr
{
   U8 type;
   union
   {
      CmIpv4TptAddr ipv4TptAddr;
      CmIpv6TptAddr ipv6TptAddr;



   }u;
} CmTptAddr;
typedef struct cmSockOpts
{
   U32 level;
   U32 option;
   union
   {





      CmNetMCastInf mCastInfo;



      CmNetAddr lclAddr;
      U32 value;
   }optVal;
}CmSockOpts;


typedef struct cmSockParam
{
   U8 listenQSize;
   U8 numOpts;
   CmSockOpts sockOpts[8];
} CmSockParam;
typedef struct cmTptParam
{
   U8 type;

   union
   {
      CmSockParam sockParam;
   } u;

} CmTptParam;



typedef struct cmIpv4HdrParm
{
   TknU8 proto;
   TknU8 dfBit;
   TknU8 tos;
   TknU8 ttl;




} CmIpv4HdrParm;
typedef struct cmIpHdrParm
{
   U8 type;
   union
   {
      CmIpv4HdrParm hdrParmIpv4;



   }u;

} CmIpHdrParm;


typedef struct cmIpv4Hdr
{
   U8 hdrVer;
   U8 tos;
   S16 length;
   U16 id;
   S16 off;
   U8 ttl;
   U8 proto;
   U16 chkSum;
   U32 srcAddr;
   U32 destAddr;

} CmIpv4Hdr;
typedef struct cmIcmpError
{
   U8 errType;
   U32 errCodeMask;

} CmIcmpError;


typedef struct cmIcmpv4Filter
{
   U8 icmpMsgFlag;
   U8 allMsg;
   U8 protocol;
   U8 num;

   CmIcmpError icmpError[5];

}CmIcmpv4Filter;
typedef struct cmIcmpFilter
{
  U8 type;
  union
  {
    CmIcmpv4Filter icmpv4Filter;



  }u;

} CmIcmpFilter;


typedef struct cmIcmpv4Hdr
{
   U8 icmpType;
   U8 icmpCode;
   U16 chkSum;

   union
   {
      U8 ihPptr;
      U32 rdrctAddr;
      struct idSeq
      {
         S16 icdId;
         S16 icdSeq;
      } u1;
      U32 ihVoid;
   } u2;

   union
   {
      struct idTime
      {
         U32 itOtime;
         U32 itRtime;
         U32 itTtime;
      } s;
      CmIpv4Hdr icmpIpHdr;
      U32 id_mask;
   } u3;

} CmIcmpv4Hdr;
extern S16 cmPkCmIpv4TptAddr (CmIpv4TptAddr *pkParam, Buffer *mBuf);
extern S16 cmPkCmNetAddrTbl (CmNetAddrTbl *pkParam, Buffer *mBuf);
extern S16 cmPkCmNetAddr (CmNetAddr *pkParam, Buffer *mBuf);
extern S16 cmPkCmTptAddr (CmTptAddr *pkParam, Buffer *mBuf);



extern S16 cmPkCmTptParam (CmTptParam *pkParam, Buffer *mBuf);
extern S16 cmUnpkCmNetAddrTbl (CmNetAddrTbl *unpkParam, Buffer *mBuf);
extern S16 cmUnpkCmIpv4TptAddr (CmIpv4TptAddr *unpkParam, Buffer *mBuf);
extern S16 cmUnpkCmNetAddr (CmNetAddr *unpkParam, Buffer *mBuf);
extern S16 cmUnpkCmTptAddr (CmTptAddr *unpkParam, Buffer *mBuf);




extern S16 cmUnpkCmTptParam (CmTptParam *unpkParam, Buffer *mBuf);


extern S16 cmPkCmIpHdrParm (CmIpHdrParm *pkParam, Buffer *mBuf);







extern S16 cmUnpkCmIpHdrParm (CmIpHdrParm *unpkParam, Buffer *mBuf);
extern S16 cmPkCmIcmpFilter (CmIcmpFilter *pkParam, Buffer *mBuf);
extern S16 cmUnpkCmIcmpFilter (CmIcmpFilter *unpkParam, Buffer *mBuf);
typedef struct cmDnsResponse CmDnsResponse;



typedef S16 (*USRTXFUNC) ( Ptr usrTxFuncParam, CmTptAddr *dnsAddr, Buffer *mBuf )



        ;


typedef S16 (*USRRXFUNC) ( Ptr usrEntry, CmDnsResponse *dnsRsp )


        ;


typedef struct cmDnsDbgInfo
{
   U32 dbgMask;
   Txt *prntBuf;
   U8 *layerName;
}CmDnsDbgInfo;


typedef struct cmDnsQueryInfo
{
   U8 qNameLen;
   U8 qName[256];
   U16 qType;
   U16 qclass;
   U8 service;
   U8 protocol;
}CmDnsQueryInfo;


typedef struct cmDnsReqIdLst
{
   U16 indx;
   Ptr usrPtr;
}CmDnsReqIdLst;


typedef struct cmDnsCb
{
   State state;

   CmTptAddr dnsTptAddr;







   USRTXFUNC txFunc;
   USRRXFUNC rxFunc;
   Mem sMem;
   EntityId tapaEnt;
   U16 entId;
   CmDnsDbgInfo dbgInfo;
   U16 requestIdLstSz;
   U16 nxtRequestId;
   U16 lastRequestId;
   Bool supportMt;
   pthread_mutex_t dnsReqLck;
   CmDnsReqIdLst **dnsReqLst;
}CmDnsCb;


typedef struct cmDnsCtrlMsgHdr
{
   U16 requestId;
   U8 msgType;
   U8 opCode;
   U8 isAuth;
   U8 isTrunc;
   U8 qryRecursive;
   U8 recurAvl;
   U8 responseCode;
   U16 qdCount;
   U16 anCount;
   U16 nsCount;
   U16 arCount;
}CmDnsCtrlMsgHdr;
typedef struct cmDns2782RR
{
   U8 service;
   U8 protocol;
   U8 nameLen;
   U8 name[256];
   U32 ttl;
   U16 qclass;
   U16 priority;
   U16 weight;
   U16 port;
   U8 targetLen;
   U8 target[256];

}CmDns2782RR;
typedef struct cmDns1035RR
{
   U8 nameLen;
   U8 name[256];
   U16 type;
   U16 qclass;
   U32 ttl;
   union
   {
     U32 ipAddress;
   }rdata;
}CmDns1035RR;

typedef union cmDnsRecord
{
   CmDns1035RR rsrcRcrd;
   CmDns2782RR srvRcrd;



}CmDnsRecord;


struct cmDnsResponse
{
   CmDnsCtrlMsgHdr header;
   CmDnsQueryInfo queryInfo;
   CmDnsRecord ans[10];
   CmDns1035RR auth[1];
   CmDns1035RR add[1];





};


typedef struct cmDnsSuppSrvcs
{
   S8 *service;
   U16 srvcLen;
}CmDnsSuppSrvcs;

extern CmDnsSuppSrvcs srvcs[9];

typedef struct cmDnsSuppProtos
{
   S8 *protocol;
   U16 protoLen;
}CmDnsSuppProtos;

extern CmDnsSuppProtos protos[6];







extern S16 cmDnsInitDnsCb ( CmDnsCb *dnsCb, CmDnsDbgInfo *dbgInfo, CmTptAddr *dnsTptAddr, USRTXFUNC txFunc, USRRXFUNC rxFunc, Mem *sMem, U16 entId, EntityId *tapaEnt, U16 reqIdLstSz )
       ;
extern Void cmDnsDeInitDnsCb ( CmDnsCb *dnsCb )

       ;


extern S16 cmDnsGenRslvReq ( CmDnsCb *dnsCb, Ptr dnsSocket, CmDnsQueryInfo *queryInfo, Ptr usrPtr, U16 *requestId, Mem *dMem )






      ;
extern S16 cmDnsPrcDnsRsp ( CmDnsCb *dnsCb, CmTptAddr *srcTptAddr, Buffer *mBuf )



      ;


extern S16 cmDnsDecodeHdr ( CmDnsResponse *dnsRsp, U8 *msg, U16 *indx )



      ;

extern S16 cmDnsDecodeQuery ( CmDnsCb *dnsCb, CmDnsResponse *dnsRsp, U8 *msg, U16 *indx )




      ;


extern S16 cmDnsDecodeRR ( CmDnsCb *dnsCb, CmDnsResponse *dnsRsp, U8 *msg, U16 *indx, U8 rrType, U16 *noOfRR, U16 maxRR )







      ;

extern S16 cmDnsDecode1035RR ( CmDns1035RR *rsrcRcrd, U8 *msg, U16 *indx, Bool *canonical )





      ;

extern S16 cmDnsDecode2782RR ( CmDnsCb *dnsCb, CmDns2782RR *srvRcrd, U8 *msg, U16 *indx, U16 rrIndex )





      ;
extern S16 cmDnsDecodeDmnName ( U8 *domain, U8 *msg, U16 *indx, U8 *nameLen )




      ;


extern S16 cmDnsDecode2782Name ( CmDnsCb *dnsCb, U8 *msg, U16 *indx, U8 *service, U8 *protocol )





      ;


extern S16 cmDnsCmpTptAddr ( CmTptAddr *addr1, CmTptAddr *addr2 )


      ;



extern Void cmDnsAbortRslvReq ( CmDnsCb *dnsCb, U16 requestId )


      ;


extern Ptr cmDnsGetUsrEntryFrmRsp ( CmDnsCb *dnsCb, CmDnsResponse *dnsRsp )


      ;
typedef S16 (*HitBndReq) (Pst *pst, SuId suId, SpId spId);
typedef S16 (*HitUbndReq) (Pst *pst, SpId spId, Reason reason);
typedef S16 (*HitServOpenReq) (Pst *pst, SpId spId, UConnId servConId, CmTptAddr *servTAddr, CmTptParam *tPar, CmIcmpFilter *icmpFilter, U8 srvcType)

                                                                            ;
typedef S16 (*HitConReq) (Pst *pst, SpId spId, UConnId suConId, CmTptAddr *remAddr, CmTptAddr *localAddr, CmTptParam *tPar, U8 srvcType)

                                                               ;
typedef S16 (*HitConRsp) (Pst *pst, SpId spId, UConnId suConId, UConnId spConId)
                                                 ;
typedef S16 (*HitDatReq) (Pst *pst, SpId spId, UConnId spConId, Buffer *mBuf)
                                              ;
typedef S16 (*HitUDatReq) (Pst *pst, SpId spId, UConnId spConId, CmTptAddr *remAddr, CmTptAddr *srcAddr, CmIpHdrParm *hdrParm, CmTptParam *tPar, Buffer *mBuf)


                                              ;
typedef S16 (*HitDiscReq) (Pst *pst, SpId spId, U8 choice, UConnId conId, Action action, CmTptParam *tPar)
                                                                 ;
typedef S16 (*HitConInd) (Pst *pst, SuId suId, UConnId servConId, UConnId spconId, CmTptAddr *peerAddr)
                                                                      ;
typedef S16 (*HitConCfm) (Pst *pst, SuId suId, UConnId suConId, UConnId spconId, CmTptAddr *localAddr)
                                                                       ;
typedef S16 (*HitBndCfm) (Pst *pst, SuId suId, U8 status);
typedef S16 (*HitDatInd) (Pst *pst, SuId suId, UConnId suconId, Buffer *mBuf)
                                              ;






typedef S16 (*HitUDatInd) (Pst *pst, SuId suId, UConnId suconId, CmTptAddr *srcAddr, CmTptAddr *destAddr, CmIpHdrParm *hdrParm, Buffer *mBuf)


                                              ;

typedef S16 (*HitDiscInd) (Pst *pst, SuId suId, U8 choice, UConnId conId, Reason reason)
                                               ;
typedef S16 (*HitDiscCfm) (Pst *pst, SuId suId, U8 choice, UConnId conId, Action action)
                                                              ;
typedef S16 (*HitFlcInd) (Pst *pst, SuId suId, UConnId suConId, Reason reason)
                                               ;
extern S16 HiUiHitBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 HiUiHitUbndReq (Pst *pst, SpId spId, Reason reason);

extern S16 HiUiHitServOpenReq (Pst *pst, SpId spId, UConnId servConId, CmTptAddr *servTAddr, CmTptParam *tPar, CmIcmpFilter *icmpFilter, U8 srvcType)

                                                                            ;
extern S16 HiUiHitConReq (Pst *pst, SpId spId, UConnId suConId, CmTptAddr *remAddr, CmTptAddr *localAddr, CmTptParam *tPar, U8 srvcType)

                                                                    ;
extern S16 HiUiHitConRsp (Pst *pst, SpId spId, UConnId suConId, UConnId spConId)
                                                      ;
extern S16 HiUiHitDatReq (Pst *pst, SpId spId, UConnId spConId, Buffer *mBuf)
                                                   ;
extern S16 HiUiHitUDatReq (Pst *pst, SpId spId, UConnId spConId, CmTptAddr *remAddr, CmTptAddr *srcAddr, CmIpHdrParm *hdrParm, CmTptParam *tPar, Buffer *mBuf)


                                                   ;
extern S16 HiUiHitDiscReq (Pst *pst, SpId spId, U8 choice, UConnId conId, Action action, CmTptParam *tPar)

                                                       ;
extern S16 HiUiHitConInd (Pst *pst, SuId suId, UConnId servConId, UConnId spConId, CmTptAddr *peerAddr)
                                                                           ;
extern S16 HiUiHitConCfm (Pst *pst, SuId suId, UConnId suConId, UConnId spConId, CmTptAddr *localAddr)
                                                                            ;
extern S16 HiUiHitBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 HiUiHitDatInd (Pst *pst, SuId suId, UConnId suConId, Buffer *mBuf)
                                                   ;






extern S16 HiUiHitUDatInd (Pst *pst, SuId suId, UConnId suConId, CmTptAddr *srcAddr, CmTptAddr *destAddr, CmIpHdrParm *hdrParm, Buffer *mBuf)


                                                   ;

extern S16 HiUiHitDiscInd (Pst *pst, SuId suId, U8 choice, UConnId conId, Reason reason)
                                                                   ;
extern S16 HiUiHitDiscCfm (Pst *pst, SuId suId, U8 choice, UConnId conId, Action action)
                                                                   ;
extern S16 HiUiHitFlcInd (Pst *pst, SuId suId, UConnId suConId, Reason reason)
                                                                     ;
extern S16 SbLiHitBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 SbLiHitUbndReq (Pst *pst, SpId spId, Reason reason);


extern S16 SbLiHitServOpenReq (Pst *pst, SpId spId,UConnId servConId, CmTptAddr *servTAddr, CmTptParam *tPar, CmIcmpFilter *icmpFilter, U8 srvcType)

                                                                            ;
extern S16 SbLiHitUDatReq (Pst *pst, SpId spId, UConnId spConId, CmTptAddr *remAddr, CmTptAddr *srcAddr, CmIpHdrParm *hdrParm, CmTptParam *tPar, Buffer *mBuf)


                                                   ;
extern S16 SbLiHitDiscReq (Pst *pst, SpId spId, U8 choice, UConnId conId, Action action, CmTptParam *tPar)

                                                       ;
extern S16 SbLiHitConCfm (Pst *pst, SuId suId, UConnId suConId, UConnId spConId, CmTptAddr *localAddr)
                                                                            ;
extern S16 SbLiHitBndCfm (Pst *pst, SuId suId, U8 status);






extern S16 SbLiHitUDatInd (Pst *pst, SuId suId, UConnId suConId, CmTptAddr *srcAddr, CmTptAddr *remAddr, CmIpHdrParm *ipHdrParm, Buffer *mBuf)


                                                   ;

extern S16 SbLiHitDiscInd (Pst *pst, SuId suId, U8 choice, UConnId conId, Reason reason)
                                                                   ;
extern S16 SbLiHitDiscCfm (Pst *pst, SuId suId, U8 choice, UConnId conId, Action action)
                                                                   ;
extern S16 EgLiHitBndReq (Pst *pst, SuId suId, SpId spId);

extern S16 EgLiHitUbndReq (Pst *pst, SpId spId, Reason reason);

extern S16 EgLiHitServOpenReq (Pst *pst, SpId spId, UConnId servConId, CmTptAddr *servTAddr, CmTptParam *tPar, CmIcmpFilter *icmpFilter, U8 srvcType)

                                                                       ;

extern S16 EgLiHitConCfm (Pst *pst, SpId spId, UConnId suConnId, UConnId spConnId, CmTptAddr *localAddr )
                                                                         ;

extern S16 EgLiHitUDatReq (Pst *pst, SpId spId, UConnId spConId, CmTptAddr *remAddr, CmTptAddr *srcAddr, CmIpHdrParm *hdrParm, CmTptParam *tPar, Buffer *mBuf)


                                                   ;
extern S16 EgLiHitDiscReq (Pst *pst, SpId spId, U8 choice, UConnId conId, Action action, CmTptParam *tPar)

                                                       ;

extern S16 EgLiHitBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 EgLiHitUDatInd (Pst *pst, SuId suId, UConnId suConId, CmTptAddr *srcAddr, CmTptAddr *remAddr, CmIpHdrParm *ipHdrParm, Buffer *mBuf)


                                                   ;
extern S16 EgLiHitDiscInd (Pst *pst, SuId suId, U8 choice, UConnId conId, Reason reason)
                                                                   ;
extern S16 EgLiHitDiscCfm (Pst *pst, SuId suId, U8 choice, UConnId conId, Action action)
                                                                   ;
extern S16 cmPkHitBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 cmPkHitUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 cmPkHitServOpenReq (Pst *pst, SpId spId, UConnId servConId, CmTptAddr *servTAddr, CmTptParam *tPar, CmIcmpFilter *icmpFilter, U8 srvcType)

                                                                            ;
extern S16 cmPkHitConReq (Pst *pst, SpId spId, UConnId suConId, CmTptAddr *remAddr, CmTptAddr *localAddr, CmTptParam *tPar, U8 srvcType)

                                                                    ;
extern S16 cmPkHitConRsp (Pst *pst, SpId spId, UConnId suConId, UConnId spConId)
                                                      ;
extern S16 cmPkHitDatReq (Pst *pst, SpId spId, UConnId spConId, Buffer *mBuf)
                                                   ;
extern S16 cmPkHitUDatReq (Pst *pst, SpId spId, UConnId spConId, CmTptAddr *remAddr, CmTptAddr *srcAddr, CmIpHdrParm *ipHdrParm, CmTptParam *tPar, Buffer *mBuf)


                                                   ;
extern S16 cmPkHitDiscReq (Pst *pst, SpId spId, U8 choice, UConnId conId, Action action, CmTptParam *tPar)

                                                       ;
extern S16 cmPkHitConInd (Pst *pst, SuId suId, UConnId servConId, UConnId spConId, CmTptAddr *peerAddr)
                                                                           ;
extern S16 cmPkHitConCfm (Pst *pst, SuId suId, UConnId suConId, UConnId spConId, CmTptAddr *localAddr)
                                                                            ;
extern S16 cmPkHitBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 cmPkHitDatInd (Pst *pst, SuId suId, UConnId suConId, Buffer *mBuf)
                                                   ;






extern S16 cmPkHitUDatInd (Pst *pst, SuId suId, UConnId suConId, CmTptAddr *arcAddr, CmTptAddr *destAddr, CmIpHdrParm *ipHdrParm, Buffer *mBuf)


                                                   ;

extern S16 cmPkHitDiscInd (Pst *pst, SuId suId, U8 choice, UConnId conId, Reason reason)
                                                                   ;
extern S16 cmPkHitDiscCfm (Pst *pst, SuId suId, U8 choice, UConnId conId, Action action)
                                                                   ;
extern S16 cmPkHitFlcInd (Pst *pst, SuId suId, UConnId suConId, Reason reason)
                                                                     ;
extern S16 cmUnpkHitBndReq (HitBndReq func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkHitUbndReq (HitUbndReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkHitServOpenReq (HitServOpenReq func, Pst *pst, Buffer *mBuf)
                                                   ;
extern S16 cmUnpkHitConReq (HitConReq func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkHitConRsp (HitConRsp func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkHitDatReq (HitDatReq func, Pst *pst, Buffer *mBuf);




extern S16 cmUnpkHitUDatReq (HitUDatReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkHitDiscReq (HitDiscReq func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkHitConInd (HitConInd func, Pst *pst, Buffer *mBuf)
                                                   ;
extern S16 cmUnpkHitConCfm (HitConCfm func, Pst *pst, Buffer *mBuf)
                                                   ;
extern S16 cmUnpkHitBndCfm (HitBndCfm func, Pst *pst, Buffer *mBuf)
                                                   ;
extern S16 cmUnpkHitDatInd (HitDatInd func, Pst *pst, Buffer *mBuf)
                                                   ;




extern S16 cmUnpkHitUDatInd (HitUDatInd func, Pst *pst, Buffer *mBuf)
                                                   ;


extern S16 cmUnpkHitDiscInd (HitDiscInd func, Pst *pst, Buffer *mBuf)
                                                   ;
extern S16 cmUnpkHitDiscCfm (HitDiscCfm func, Pst *pst, Buffer *mBuf)
                                                   ;
extern S16 cmUnpkHitFlcInd (HitFlcInd func, Pst *pst, Buffer *mBuf)
                                                   ;
typedef enum egtMsgType
{
   EGT_GTP_MSG_INVALID = 0,
   EGT_GTPU_MSG_ECHO_REQ = 1,
   EGT_GTPU_MSG_ECHO_RSP = 2,
   EGT_GTPU_MSG_ERROR_IND = 26,
   EGT_GTPU_MSG_SUPP_EXT_HDR_NTF = 31,
   EGT_GTPU_MSG_END_MARKER = 254,
   EGT_GTPU_MSG_GPDU,

   EGT_GTP_MSG_MAX
}EgtMsgType;
typedef enum _egtIntfEnt
{
   EGT_INT_S1_U_ENB_GTP_U = 0,
   EGT_INT_S1_U_SGW_GTP_U,
   EGT_INT_S12_RNC_GTP_U,
   EGT_INT_S12_SGW_GTP_U,
   EGT_INT_S5_S8_SGW_GTP_U,
   EGT_INT_S5_S8_PGW_GTP_U = 5,
   EGT_INT_S5_S8_SGW_GTP_C,
   EGT_INT_S5_S8_PGW_GTP_C,
   EGT_INT_S5_S8_SGW_PMIPv6,
   EGT_INT_S5_S8_PGW_PMIPv6,
   EGT_INT_S11_MME_GTP_C = 10,
   EGT_INT_S11_S4_SGW_GTP_C,
   EGT_INT_S10_MME_GTP_C,
   EGT_INT_S3_MME_GTP_C,
   EGT_INT_S3_SGSN_GTP_C,
   EGT_INT_S4_SGSN_GTP_U = 15,
   EGT_INT_S4_SGW_GTP_U,
   EGT_INT_S4_SGSN_GTP_C,
   EGT_INT_S16_SGSN_GTP_C,
   EGT_INT_X2_DL_ENB_GTP_U,
   EGT_INT_X2_UL_ENB_GTP_U = 20,
   EGT_INT_RNC_GTP_U,
   EGT_INT_SGSN_GTP_U,
   EGT_INT_SGW_GTP_U,
   EGT_INT_ENTINVALID
}EgtIntfEnt;
typedef enum _egtErrType
{
   EGT_ERR_NO_ERR,
   EGT_ERR_REQ_FAIL,
   EGT_ERR_TEID_EXHAUSTED,
   EGT_ERR_UNKNOWN_TEID_MSG,
   EGT_ERR_INV_INTF_TYPE,
   EGT_ERR_INV_TUNN_NET_EVNT,
   EGT_ERR_INV_TUNN_USR_EVNT,
   EGT_ERR_MSG_INV_INT,
   EGT_ERR_MSG_NO_MATCH,
   EGT_ERR_MSG_UNABLE_TO_COMPLY,
   EGT_ERR_MSG_MISS_MAND_IE,
   EGT_ERR_MSG_INV_LEN,
   EGT_ERR_MSG_INV_VERSION,
   EGT_ERR_MSG_INV_HDR,
   EGT_ERR_MSG_INV_TYPE,
   EGT_ERR_IE_UNKNOWN,
   EGT_ERR_IE_INV_LEN,
   EGT_ERR_INV_IE_TYPE,
   EGT_ERR_INV_IE_VAL,
   EGT_ERR_MEM_ALLOC_FAILED,
   EGT_ERR_INV_TEID,
   EGT_ERR_DFTL_SRV_NOT_PRSNT,
   EGT_ERR_TIMER_FAILED,
   EGT_ERR_MSG_SNDING_FAIL,
   EGT_ERR_INV_SAP,
   EGT_ERR_INV_IE_DATA_TYPE,
   EGT_ERR_UNKNOWN_TV,
   EGT_ERR_IE_NOT_ASCD_ORDER,
   EGT_ERR_UNSUPP_EXT_HDR,
   EGT_ERR_WRONG_EXT_HDR,
   EGT_ERR_MSG_INV_PTTYPE,
   EGT_ERR_MAN_IE_INV_LEN,
   EGT_ERR_NO_SEQ,
   EGT_ERR_MAX_TDPU_SIZE_EXCED,
   EGT_ERR_INV_DATA_TYPE,
   EGT_ERR_INV_PARAM,
   EGT_ERR_INV_DST_IP,
   EGT_ERR_MSG_NOT_ALLWD,
   EGT_ERR_DST_MULT_IP,
   EGT_ERR_INV_SRC_IP,
   EGT_ERR_INV_SRC_PORT,
   EGT_ERR_CAUSE_MEM_FAIL,
   EGT_ERR_INV_TEID_RCVD,
   EGT_ERR_PENDING_CNTRL_OP,
   EGT_ERR_END_MARKER_RCVD,
   EGT_ERR_MSG_INVOVR_LEN_PBMSG,



   EGT_ERR_MAX_RETRY_EXHAUSTED,
   EGT_ERR_INV_SEQ_NUM,

   EGT_ERR_INV_PIGGY_MSG,

   EGT_ERR_RSP_PIGGY_TMR_EXP,

   EGT_ERR_MAX_ERR

}EgtErrType;
typedef struct _egDatStr132
{
   U16 length;
   U8 val[132];
   U16 spare1;



} EgDatStr132;
typedef struct _egPvtExt
{
   U16 entId;
   EgDatStr132 propVal;
} EgPvtExt;
typedef struct _egErrEvnt
{
   U32 localTeid;
   U32 transId;
   U32 remTeid;
   CmTptAddr remAddr;
   U8 intfType;


   U32 seqNo;
   EgtErrType errCause;
   U8 failedIeInst;
   U8 failedIeType;
   U8 failedMsgType;
} EgErrEvnt;





typedef struct _egUExtHdr
{
   TknU16 udpPort;
   TknU16 pdcpNmb;
} EgUExtHdr;





typedef struct _egUMsgHdr
{
   TknU8 nPduNmb;
   TknU32 seqNumber;
   EgUExtHdr extHdr;
   U32 teId;
   U8 msgType;
}EgUMsgHdr;

typedef struct _egUMsg EgUMsg;




struct _egUMsg
{






   CmMemListCp memCp;

   EgUMsgHdr msgHdr;
   CmTptAddr srcAddr;
   CmTptAddr remAddr;
   U32 lclTeid;
   union
   {
      CmLListCp egIeList;
      Buffer *mBuf;
   }u;
   EgUMsg *next;
};




typedef struct _egUIpAddr
{
   U8 addrType;
   union
   {
      CmIpAddr ipv4;



   } u;
} EgUIpAddr;



typedef struct _egUExtHdrTypeLst
{
   U8 noOfExtHdrs;
   U8 extType[2];
} EgUExtHdrTypeLst;



typedef struct _egUIe
{
  CmLList node;
  U8 ieType;
  U8 dataType;
  union
  {
     U8 valUnSgnd8;
     U32 valUnSgnd32;
     EgPvtExt pvtExt;
     EgUIpAddr ipAddr;
     EgUExtHdrTypeLst extHdrTypeLst;
  }t;
} EgUIe;



typedef struct _egUStatus
{
   CmTptAddr srcAddr;
   CmTptAddr dstAddr;
   CmStatus cfmStatus;
} EgUStatus;



typedef struct _egUErrEvnt
{
   U32 localTeid;
   U32 remTeid;
   EgtErrType errCause;
   CmTptAddr srcAddr;
   CmTptAddr dstAddr;
   U32 diagInfo;
   U8 failedIeType;
   U8 failedMsgType;
} EgUErrEvnt;



typedef struct _egUTnlMgmt
{
   U8 action;
   U8 intfType;

   U8 dscp;
   Bool reOrderPres;


   U8 tunnelType;


   U32 teId;
   U32 remTeId;
   U8 reordAlgo;

   U16 expSeqNmb;
   CmTptAddr srcAddr;
   CmTptAddr dstIpAddr;
   CmTptAddr frmDstIpAddr;
   U16 maxTPduSize;
   CmStatus cfmStatus;
} EgUTnlMgmt;



typedef struct _egtUEvnt
{
   U8 event;
   union
   {
      EgUTnlMgmt tnlMgmt;
      EgUMsg *egMsg;
      EgUStatus status;
      EgUStatus uStaInd;
      EgUErrEvnt errInd;
   } u;
} EgtUEvnt;
typedef S16 (*EgtBndReq) ( Pst *pst, SuId suId, SpId spId)


                                  ;

typedef S16 (*EgtBndCfm) ( Pst *pst, SuId suId, U8 status)


                                    ;

typedef S16 (*EgtUbndReq) ( Pst *pst, SpId spId, Reason reason)


                                    ;
typedef S16 (*EgtEguDatReq) ( Pst *pst, SpId spId, EgtUEvnt *datReq)


                                     ;


typedef S16 (*EgtEguDatInd) ( Pst *pst, SuId suId, EgtUEvnt *datInd)


                                     ;


typedef S16 (*EgtEguLclTnlMgmtReq) ( Pst *pst, SpId spId, EgtUEvnt *mgmtReq)


                                      ;


typedef S16 (*EgtEguLclTnlMgmtCfm) ( Pst *pst, SuId suId, EgtUEvnt *mgmtCfm)


                                      ;


typedef S16 (*EgtEguStaReq) ( Pst *pst, SpId spId, EgtUEvnt *staReq)


                                     ;


typedef S16 (*EgtEguStaCfm) ( Pst *pst, SuId suId, EgtUEvnt *staCfm)


                                     ;


typedef S16 (*EgtEguUStaInd) ( Pst *pst, SuId suId, EgtUEvnt *uStaInd)


                                      ;


typedef S16 (*EgtEguErrInd) ( Pst *pst, SuId suId, EgtUEvnt *errInd)


                                     ;
extern S16 EgUiEgtBndReq ( Pst *pst, SuId suId, SpId spId);
extern S16 EgUiEgtBndCfm ( Pst *pst, SuId suId, U8 status);
extern S16 EgUiEgtUbndReq ( Pst *pst, SpId spId, Reason reason);
extern S16 EgUiEgtEguDatReq (Pst *pst, SpId spId, EgtUEvnt *egtUEvnt);
extern S16 EgUiEgtEguDatInd (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
extern S16 EgUiEgtEguLclTnlMgmtReq (Pst *pst, SpId spId, EgtUEvnt *egtUEvnt);
extern S16 EgUiEgtEguLclTnlMgmtCfm (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
extern S16 EgUiEgtEguStaReq (Pst *pst, SpId spId, EgtUEvnt *egtUEvnt);
extern S16 EgUiEgtEguStaCfm (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
extern S16 EgUiEgtEguUStaInd (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
extern S16 EgUiEgtEguErrInd (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);







extern S16 EuLiEgtBndReq ( Pst *pst, SuId suId, SpId spId);

extern S16 EuLiEgtBndCfm ( Pst *pst, SuId suId, U8 status);

extern S16 EuLiEgtUbndReq ( Pst *pst, SpId spId, Reason reason);
extern S16 EuLiEgtEguDatReq (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
extern S16 EuLiEgtEguDatInd (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);

extern S16 EuLiEgtEguLclTnlMgmtReq (Pst *pst, SpId spId, EgtUEvnt *egtUEvnt);
extern S16 EuLiEgtEguLclTnlMgmtCfm (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);

extern S16 EuLiEgtEguStaReq (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
extern S16 EuLiEgtEguStaCfm (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);

extern S16 EuLiEgtEguUStaInd (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);

extern S16 EuLiEgtEguErrInd (Pst *pst, SpId spId, EgtUEvnt *egtUEvnt);
extern S16 cmPkEgtBndReq
( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 cmUnpkEgtBndReq
( EgtBndReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkEgtBndCfm
( Pst * pst, SuId suId, U8 status )



  ;

extern S16 cmUnpkEgtBndCfm
( EgtBndCfm func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkEgtUbndReq
( Pst * pst, SpId spId, Reason reason )



  ;

extern S16 cmUnpkEgtUbndReq
( EgtUbndReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkEgDatStr132
( EgDatStr132 *param, Buffer *mBuf )


  ;

extern S16 cmUnpkEgDatStr132
( EgDatStr132 *param, Buffer *mBuf )


  ;
extern S16 cmPkEgPvtExt
( EgPvtExt *param, Buffer *mBuf )


  ;

extern S16 cmUnpkEgPvtExt
( EgPvtExt *param, Buffer *mBuf )


  ;


extern S16 cmPkEgtEguDatReq ( Pst *pst, SpId spId, EgtUEvnt *egtUEvnt )




  ;

extern S16 cmUnpkEgtEguDatReq ( EgtEguDatReq func, Pst *pst, Buffer *mBuf, Mem *memInfo )





  ;

extern S16 cmPkEgtEguDatInd ( Pst *pst, SuId suId, EgtUEvnt *egtUEvnt )




  ;

extern S16 cmUnpkEgtEguDatInd ( EgtEguDatInd func, Pst *pst, Buffer *mBuf )




  ;

extern S16 cmPkEgtEguLclTnlMgmtReq ( Pst *pst, SpId spId, EgtUEvnt *egtUEvnt )




  ;

extern S16 cmUnpkEgtEguLclTnlMgmtReq ( EgtEguLclTnlMgmtReq func, Pst *pst, Buffer *mBuf, Mem *memInfo )





  ;

extern S16 cmPkEgtEguLclTnlMgmtCfm ( Pst *pst, SuId suId, EgtUEvnt *egtUEvnt )




  ;

extern S16 cmUnpkEgtEguLclTnlMgmtCfm ( EgtEguLclTnlMgmtCfm func, Pst *pst, Buffer *mBuf )




  ;

extern S16 cmPkEgtEguStaReq ( Pst *pst, SpId spId, EgtUEvnt *egtUEvnt )




  ;

extern S16 cmUnpkEgtEguStaReq ( EgtEguStaReq func, Pst *pst, Buffer *mBuf, Mem *memInfo )





  ;

extern S16 cmPkEgtEguStaCfm ( Pst *pst, SuId suId, EgtUEvnt *egtUEvnt )




  ;

extern S16 cmUnpkEgtEguStaCfm ( EgtEguStaCfm func, Pst *pst, Buffer *mBuf )




  ;

extern S16 cmPkEgtEguUStaInd ( Pst *pst, SuId suId, EgtUEvnt *egtUEvnt )




  ;

extern S16 cmUnpkEgtEguUStaInd ( EgtEguUStaInd func, Pst *pst, Buffer *mBuf )




  ;

extern S16 cmPkEgtEguErrInd ( Pst *pst, SuId suId, EgtUEvnt *egtUEvnt )




  ;

extern S16 cmUnpkEgtEguErrInd ( EgtEguErrInd func, Pst *pst, Buffer *mBuf )




  ;

extern S16 cmPkEgUExtHdr ( EgUExtHdr *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUExtHdr ( EgUExtHdr *unpkStruct, Buffer *mBuf )



  ;

extern S16 cmPkEgUMsgHdr ( EgUMsgHdr *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUMsgHdr ( EgUMsgHdr *unpkStruct, Buffer *mBuf )



  ;

extern S16 cmPkEgUMsg ( EgUMsg *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUMsg ( EgUMsg *unpkStruct, Buffer *mBuf, Mem memInfo )




  ;

extern S16 cmPkEgUIpAddr ( EgUIpAddr *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUIpAddr ( EgUIpAddr *unpkStruct, Buffer *mBuf )



  ;

extern S16 cmPkEgUExtHdrTypeLst ( EgUExtHdrTypeLst *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUExtHdrTypeLst ( EgUExtHdrTypeLst *unpkStruct, Buffer *mBuf )



  ;

extern S16 cmPkEgUIeList ( CmLListCp *pkList, Buffer *mBuf, CmMemListCp *memCp )




  ;

extern S16 cmUnpkEgUIeList ( CmLListCp *unpkList, Buffer *mBuf, CmMemListCp *memCp )




  ;

extern S16 cmPkEgUIe ( EgUIe *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUIe ( EgUIe *unpkStruct, Buffer *mBuf )



  ;

extern S16 cmPkEgUStatus ( EgUStatus *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUStatus ( EgUStatus *unpkStruct, Buffer *mBuf )



  ;

extern S16 cmPkEgUErrEvnt ( EgUErrEvnt *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUErrEvnt ( EgUErrEvnt *unpkStruct, Buffer *mBuf )



  ;

extern S16 cmPkEgUTnlMgmt ( EgUTnlMgmt *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgUTnlMgmt ( EgUTnlMgmt *unpkStruct, Buffer *mBuf )



  ;

extern S16 cmPkEgtUEvnt ( EgtUEvnt *pkStruct, Buffer *mBuf )



  ;

extern S16 cmUnpkEgtUEvnt ( EgtUEvnt *unpkStruct, Buffer *mBuf, Pst *pst )




  ;
typedef struct _legStr
{
    U16 length;
    Data buff[255];
}LegStr;





typedef enum _legEntity
{
   LEG_GTP_ENT_UNKNWN,
   LEG_GTP_ENT_MME,
   LEG_GTP_ENT_SGW,
   LEG_GTP_ENT_PGW,
   LEG_GTP_ENT_SGSN
}LegEntity;





typedef struct _legIeEntry
{
   U8 ieType;
   U8 dataType;
   U16 minLen;
   U16 maxLen;
}LegIeEntry;

typedef struct _legIeProperties LegIeProperties;
typedef struct _legGroupedIe LegGroupedIe;





struct _legGroupedIe
{
   U8 nmbGrpIe;
   U8 posIndex[10][256];
   LegIeProperties *ieProperties;
};





struct _legIeProperties
{
   U8 ieType;
   U8 ieClass;
   Bool ieList;
   U8 ieInst;
   LegGroupedIe *groupedIe;
};




typedef S16 (*EscFun) (Void *,U8 );
typedef struct _legMsgEntry
{
   U8 msgType;
   U8 posIndex[10][256];
   U8 nmbIeProp;
   LegIeProperties ieProperties[40];
   EscFun validateIe;
}LegMsgEntry;





typedef struct _egIeDictCfg
{
  LegIeEntry ieEntry[81];
  U16 posIdx[256];
  U8 nmbIe;

}EgIeDictCfg;





typedef struct _egGmDictCfg
{
  U8 intfType;
  U8 nmbMsg;
  LegMsgEntry *gmEntry;
}EgGmDictCfg;
typedef struct _egGenCfg
{
   TmrCfg eguT3Timer;
   U8 nmbRetries;
   TmrCfg echoTmr;
   TmrCfg reOrderTmr;
   U16 pvtExtId;

   U32 pduWindSize;
   U8 maxNumOfIp;
   U8 nodeArch;
 Bool lclEchoSup;







   S16 timerRes;
   U16 nmbUSaps;
   U16 maxNmbTSaps;
   U16 nmbSrvs;
   Status resThreshUpper;
   Status resThreshLower;
   Pst lmPst;





}EgGenCfg;







typedef struct _egUSapCfg
{
   SpId sapId;




   Selector selector;
   MemoryId mem;
   Priority priority;
   Route route;
   Ent dstEnt;
   Inst dstInst;
   ProcId dstProcId;
   U8 flag;






}EgUSapCfg;







typedef struct _egTSapCfg
{
   SuId tSapId;
   SpId spId;
   U16 tptType;
   Selector selector;
   MemoryId mem;
   Priority priority;
   Route route;
   Ent dstEnt;
   Inst dstInst;
   ProcId dstProcId;
   TmrCfg tInitTmr;
   CmTptParam tptParam;






}EgTSapCfg;



typedef struct _egTSapReCfg
{
   CmTptParam tPar;

   U8 maxBndRetry;
   TmrCfg bndTmCfg;
} EgTSapReCfg;
typedef struct _egIpInfo
{
   CmTptAddr srcIpAddr;
   SpId spId;
   U8 nodeType;
   Bool cfmStatus;
   U16 reason;
   LegStr echoReqPvtExtVal;

   LegStr echoRspPvtExtVal;

   LegStr errIndPvtExtVal;

}EgIpInfo;
typedef struct _egIpAddrCfg
{
   U8 nmbIpAddr;
   EgIpInfo *ipInfo;
}EgIpAddrCfg;
typedef struct _egTptSrvCfg
{
   SpId uSapId;
   U32 tptSrvId;
   SuId tSapId;
   CmTptAddr tptAddr;
   CmTptParam tptParam;
   S16 opnSrvRetryCnt;

   TmrCfg opnSrvTmr;





   TknStrOSXL hostName;
   U8 gtp_C_Or_U;

}EgTptSrvCfg;
typedef struct _egCfg
{
  union
   {
      EgGenCfg gen;
      EgUSapCfg uSap;
      EgTSapCfg tSap;

      EgIpAddrCfg ipAddr;

      EgTptSrvCfg tptSrv;




   } s;

   union
   {
      EgTSapReCfg tSapReCfg;
   }r;

}EgCfg;







typedef struct _egDbgCntrl
{
   U32 genDbgMask;
}EgDbgCntrl;







typedef struct _egTrcCntrl
{
   union
   {
      SpId tSapId;
   }t;
   S16 trcLen;
   U32 trcMask;
}EgTrcCntrl;







typedef struct egIpAddrCntrl
{
   CmTptAddr ipAddr;
   SpId fromSpId;
   SpId toSpId;
}EgIpAddrCntrl;
typedef struct egServerCntrl
{
   U8 type;




   union
   {
     U32 tptSrvId;
     CmTptAddr tptAddr;
   }t;
}EgServerCntrl;






typedef struct egSapCntrl
{
   SpId sapId;
}EgSapCntrl;







typedef struct _egCntrl
{
   DateTime dt;
   U8 action;
   U8 subAction;
   Bool flag;

   union
   {
      EgServerCntrl server;
      EgSapCntrl sap;
      EgTrcCntrl trcCntrl;

      EgDbgCntrl dbgCntrl;


      EgIpAddrCntrl ipAddress;


      U32 logMask;
 }s;
}EgCntrl;







typedef struct _egGenSta
{
   U32 memSize;
   U32 memAlloc;
   Bool resCong;
}EgGenSta;







typedef struct _egTSapSta
{
   SpId tSapId;
   S16 state;
}EgTSapSta;






typedef struct _egUSapSta
{
   SpId uSapId;
   S16 state;
}EgUSapSta;



typedef struct _egTptSrvSta
{
   SpId tSapId;
   U32 tptSrvId;
   Bool status;
   U8 state;
}EgTptSrvSta;



typedef struct _egTnlSta
{
   U32 teId;
   SpId spId;
   CmTptAddr srcIpAddr;

   CmTptAddr destIpAddr;

   Bool reOrderPrsnt;
}EgTnlSta;
typedef struct _egSta
{
   DateTime dt;
   union
   {
      SystemId sysId;
      EgGenSta genSta;
      EgUSapSta uSapSta;
      EgTSapSta tSapSta;

      EgTptSrvSta tSrvrSta;
      EgTnlSta tnlSta;

   } s;
}EgSta;







typedef struct _egErrSts
{
   Cntr invVerRx;
   Cntr invProtTypeRx;
   Cntr invMsgRx;
   Cntr invMsgLenRx;
   Cntr invIeOrderRx;
   Cntr invIeLenRx;
   Cntr invIeFormatRx;
   Cntr invManIeLenRx;
   Cntr missMandIeRx;
   Cntr unSuppExtHdrRx;
   Cntr wrngExtHdrRx;
   Cntr msgUnableCompRx;
   Cntr msgUnableCompTx;
   Cntr missMandIeTx;
   Cntr memAllocFldTx;
   Cntr invMsgTx;
   Cntr invTeidTx;
   Cntr invTeidRx;
   Cntr errSeqNoTx;
   Cntr errSeqNoRx;
   Cntr tpduExcdTx;
   Cntr invDatTypeTx;
}EgErrSts;

typedef struct _egGenSts
{
   Cntr numTxMsg;
   Cntr numRxMsg;
   Cntr numActvTnls;


   Cntr numNrmlDataTunn;

   Cntr numFwdDataTunn;


   Cntr numErrInd;

   Cntr cntInvldTeidInd;
   Cntr rxDesgMsg;

   EgErrSts errSts;
}EgGenSts;







typedef struct MsgSts
{
   Cntr Tx;
   Cntr Rx;
}EgMsgSts;







typedef struct _egSapSts
{
   SpId sapId;
   Cntr totalMsgsTx;
   Cntr totalMsgsRx;
   EgMsgSts msgType[256];

}EgSapSts;
typedef struct _egTnlSts
{
   U32 teId;
   SpId spId;
   CmTptAddr srcIpAddr;

   CmTptAddr destIpAddr;

   Cntr totalMsgsTx;
   Cntr totalMsgsRx;
   Bool reOrderPrsnt;
}EgTnlSts;
typedef struct _egTptSrvrSts
{
   SpId spId;
   CmTptAddr lclAddr;
   Cntr totalMsgsTx;
   Cntr totalMsgsRx;
}EgTptSrvrSts;







typedef struct _egIpSts
{
   CmTptAddr IpAddr;
   SpId spId;
   U32 nmbPorts;
   U32 *portsLst;
   U32 nmbActvSrvrs;
   U32 nmbInactvSrvr;
   Cntr totalMsgsTx;
   Cntr totalMsgsRx;
}EgIpSts;







typedef struct _egSts
{
   DateTime dt;
   union
   {
     EgGenSts gen;
     EgSapSts usap;
     EgSapSts tsap;

     EgIpSts ipSts;
     EgTptSrvrSts tptSrvrSts;
     EgTnlSts tnlSts;




   }s;
}EgSts;
typedef struct _egUstaDgnVal
{
   U8 type;
   union
   {
      Event event;
      SpId sapId;
      U32 connId;
      U8 choice;
      U8 ieType;
      CmTptAddr ipAddr;
      MemoryId mem;
   } t;
}EgUstaDgnVal;



typedef struct _egUstaDgn
{
   EgUstaDgnVal dgnVal[4];
}EgUstaDgn;



typedef struct _egUsta
{
   CmAlarm alarm;
   DateTime dt;
   EgUstaDgn dgn;
}EgUsta;







typedef struct _egTrc
{
   DateTime dt;
   U16 evnt;
   S16 length;
   CmTptAddr *srcAddr;
   CmTptAddr *remAddr;
}EgTrc;






typedef struct _egMngmt
{
   Header hdr;
   CmStatus cfm;
   union
   {
      EgCfg cfg;
      EgCntrl cntrl;
      EgSts sts;
      EgSta ssta;
      EgUsta usta;
      EgTrc trc;
   }u;
}EgMngmt;
typedef S16 (*LegCfgReq) ( Pst *pst, EgMngmt *cfgReq )

                                ;

typedef S16 (*LegCfgCfm) ( Pst *pst, EgMngmt *cfgCfm )


                               ;

typedef S16 (*LegStsReq) ( Pst *pst, Action action, EgMngmt *stsReq )



                               ;

typedef S16 (*LegStsCfm) ( Pst *pst, EgMngmt *stsCfm )


                               ;

typedef S16 (*LegStaReq) ( Pst *pst, EgMngmt *staReq )


                               ;

typedef S16 (*LegStaCfm) ( Pst *pst, EgMngmt *staCfm )


                               ;

typedef S16 (*LegStaInd) ( Pst *pst, EgMngmt *staInd )


                               ;

typedef S16 (*LegCntrlReq) ( Pst *pst, EgMngmt *cntrlReq )


                               ;

typedef S16 (*LegCntrlCfm) ( Pst *pst, EgMngmt *cntrlCfm )


                               ;

typedef S16 (*LegTrcInd) ( Pst *pst, EgMngmt *trcInd, Buffer *mBuf )



                               ;
 S16 EgMiLegCfgReq ( Pst *pst, EgMngmt *cfgReq )


                               ;
 S16 EgMiLegCfgCfm ( Pst *pst, EgMngmt *cfgCfm )


                               ;
 S16 EgMiLegStsReq ( Pst *pst, Action action, EgMngmt *stsReq )



                               ;
 S16 EgMiLegStsCfm ( Pst *pst, EgMngmt *stsCfm )


                               ;
 S16 EgMiLegStaReq ( Pst *pst, EgMngmt *staReq )


                               ;
 S16 EgMiLegStaCfm ( Pst *pst, EgMngmt *staCfm )


                               ;
 S16 EgMiLegStaInd ( Pst *pst, EgMngmt *staInd )


                               ;
 S16 EgMiLegCntrlReq ( Pst *pst, EgMngmt *cntrlReq )


                               ;
 S16 EgMiLegCntrlCfm ( Pst *pst, EgMngmt *cntrlCfm )


                               ;
 S16 EgMiLegTrcInd ( Pst *pst, EgMngmt *trcInd, Buffer *mBuf )



                               ;




 S16 SmMiLegCfgReq ( Pst *pst, EgMngmt *cfgReq )


                               ;

 S16 SmMiLegCfgCfm ( Pst *pst, EgMngmt *cfgCfm )


                               ;

 S16 SmMiLegStsReq ( Pst *pst, Action action, EgMngmt *stsReq )



                               ;

 S16 SmMiLegStsCfm ( Pst *pst, EgMngmt *stsCfm )


                               ;

 S16 SmMiLegStaReq ( Pst *pst, EgMngmt *staReq )


                               ;

 S16 SmMiLegStaCfm ( Pst *pst, EgMngmt *staCfm )


                               ;

 S16 SmMiLegStaInd ( Pst *pst, EgMngmt *staInd )


                               ;

 S16 SmMiLegCntrlReq ( Pst *pst, EgMngmt *cntrlReq )


                               ;

 S16 SmMiLegCntrlCfm ( Pst *pst, EgMngmt *cntrlCfm )


                               ;

 S16 SmMiLegTrcInd ( Pst *pst, EgMngmt *trcInd, Buffer *mBuf )



                               ;




extern S16 cmPkLegCfgReq (Pst* pst, EgMngmt * cfgReq);
extern S16 cmPkLegCntrlReq (Pst* pst, EgMngmt * cntrlReq);
extern S16 cmPkLegStaReq (Pst* pst, EgMngmt * staReq);
extern S16 cmPkLegStsReq (Pst* pst, Action action, EgMngmt * stsReq);


extern S16 cmUnpkLegCfgReq (LegCfgReq func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLegCntrlReq (LegCntrlReq func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLegStaReq (LegStaReq func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLegStsReq (LegStsReq func, Pst *pst, Buffer *mBuf);

extern S16 cmPkLegCfgCfm (Pst* pst, EgMngmt * cfgCfm);
extern S16 cmPkLegCntrlCfm (Pst* pst, EgMngmt * cntrlCfm);
extern S16 cmPkLegStsCfm (Pst* pst, EgMngmt * stsCfm);
extern S16 cmPkLegStaCfm (Pst* pst, EgMngmt * staCfm);

extern S16 cmUnpkLegCfgCfm (LegCfgCfm func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLegCntrlCfm (LegCntrlCfm func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLegStsCfm (LegStsCfm func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLegStaCfm (LegStaCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmPkLegStaInd (Pst* pst, EgMngmt * staInd);
extern S16 cmPkLegTrcInd (Pst* pst, EgMngmt * trcInd, Buffer * uBuf);

extern S16 cmUnpkLegStaInd (LegStaInd func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkLegTrcInd (LegTrcInd func, Pst *pst, Buffer *mBuf);

extern S16 cmPkEgGenCfg (EgGenCfg *genCfg, Buffer *mBuf, Pst *pst);
extern S16 cmPkEgUSapCfg (EgUSapCfg *usapCfg, Buffer *mBuf);
extern S16 cmPkEgTSapReCfg (EgTSapReCfg *tsapReCfg, Buffer *mBuf);
extern S16 cmPkEgTSapCfg (EgTSapCfg *tsapCfg, Buffer *mBuf);
extern S16 cmPkEgTptSrvCfg (EgTptSrvCfg *tsrvCfg, Buffer *mBuf);
extern S16 cmPkEgGmDictCfg (EgGmDictCfg *msgCfg, Buffer *mBuf);
extern S16 cmPkEgIeDictCfg (EgIeDictCfg *ieCfg, Buffer *mBuf);


extern S16 cmPkEgIpAddrCfg (EgIpAddrCfg *ipAddrCfg, Buffer *mBuf, Pst *pst);
extern S16 cmUnpkEgIpAddrCfg (EgIpAddrCfg *ipAddrCfg, Buffer *mBuf, Pst *pst);




extern S16 cmPkLegMsgEntry (LegMsgEntry *msg, Buffer *mBuf);
extern S16 cmPkLegIeProperties (LegIeProperties *ieProp, Buffer *mBuf);
extern S16 cmPkLegGroupedIe (LegGroupedIe *grpIe, Buffer *mBuf);
extern S16 cmPkLegIeEntry (LegIeEntry *ieEnt, Buffer *mBuf);

extern S16 cmUnpkEgGenCfg (EgGenCfg *genCfg, Buffer *mBuf, Pst *pst);
extern S16 cmUnpkEgUSapCfg (EgUSapCfg *usapCfg, Buffer *mBuf);
extern S16 cmUnpkEgTSapReCfg (EgTSapReCfg *tsapReCfg, Buffer *mBuf);
extern S16 cmUnpkEgTSapCfg (EgTSapCfg *tsapCfg, Buffer *mBuf);
extern S16 cmUnpkEgTptSrvCfg (EgTptSrvCfg *tsrvCfg, Buffer *mBuf);
extern S16 cmUnpkEgGmDictCfg (EgGmDictCfg *msgCfg, Buffer *mBuf);
extern S16 cmUnpkEgIeDictCfg (EgIeDictCfg *ieCfg, Buffer *mBuf);

extern S16 cmUnpkLegMsgEntry (LegMsgEntry *msg, Buffer *mBuf);
extern S16 cmUnpkLegIeProperties (LegIeProperties *ieProp, Buffer *mBuf);
extern S16 cmUnpkLegGroupedIe (LegGroupedIe *grpIe, Buffer *mBuf);
extern S16 cmUnpkLegIeEntry (LegIeEntry *ieEnt, Buffer *mBuf);

extern S16 cmPkEgTrcCntrl (EgTrcCntrl *trcCntrl, Buffer *mBuf);
extern S16 cmPkEgDbgCntrl (EgDbgCntrl *dbgCntrl, Buffer *mBuf);
extern S16 cmPkEgSapCntrl (EgSapCntrl *sapCntrl, Buffer *mBuf);
extern S16 cmPkEgServerCntrl (EgServerCntrl *srvCntrl, Buffer *mBuf);

extern S16 cmUnpkEgTrcCntrl (EgTrcCntrl *trcCntrl, Buffer *mBuf);
extern S16 cmUnpkEgDbgCntrl (EgDbgCntrl *dbgCntrl, Buffer *mBuf);
extern S16 cmUnpkEgSapCntrl (EgSapCntrl *sapCntrl, Buffer *mBuf);
extern S16 cmUnpkEgServerCntrl (EgServerCntrl *srvCntrl, Buffer *mBuf);

extern S16 cmPkEgGenSta (EgGenSta *genSta, Buffer *mBuf);
extern S16 cmPkEgUSapSta (EgUSapSta *usapSta, Buffer *mBuf);
extern S16 cmPkEgTSapSta (EgTSapSta *tsapSta, Buffer *mBuf);

extern S16 cmUnpkEgGenSta (EgGenSta *genSta, Buffer *mBuf);
extern S16 cmUnpkEgUSapSta (EgUSapSta *usapSta, Buffer *mBuf);
extern S16 cmUnpkEgTSapSta (EgTSapSta *tsapSta, Buffer *mBuf);

extern S16 cmPkEgGenSts (EgGenSts *genSts, Buffer *mBuf);
extern S16 cmPkEgMsgSts (EgMsgSts *msgSts, Buffer *mBuf);
extern S16 cmPkEgSapSts (EgSapSts *sapSts, Buffer *mBuf);

extern S16 cmUnpkEgGenSts (EgGenSts *genSts, Buffer *mBuf);
extern S16 cmUnpkEgMsgSts (EgMsgSts *msgSts, Buffer *mBuf);
extern S16 cmUnpkEgSapSts (EgSapSts *sapSts, Buffer *mBuf);

extern S16 cmPkEgUstaDgnVal (EgUstaDgnVal *dgnVal, Buffer *mBuf);
extern S16 cmPkEgUstaDgn (EgUstaDgn *dgn, Buffer *mBuf);

extern S16 cmUnpkEgUstaDgnVal (EgUstaDgnVal *dgnVal, Buffer *mBuf);
extern S16 cmUnpkEgUstaDgn (EgUstaDgn *dgn, Buffer *mBuf);


extern S16 cmPkLegStr (LegStr *legStr, Buffer *mBuf);
extern S16 cmUnpkLegStr (LegStr *legStr, Buffer *mBuf);
extern S16 cmPkEgIpAddrCntrl (EgIpAddrCntrl *ipCntrl, Buffer *mBuf);
extern S16 cmUnpkEgIpAddrCntrl (EgIpAddrCntrl *ipCntrl, Buffer *mBuf);
extern S16 cmPkEgIpAddrStsCfm (EgIpSts *ipSts, Buffer *mBuf, Pst *pst);
extern S16 cmPkEgSrvrStsCfm (EgTptSrvrSts *tSrvrSts, Buffer *mBuf);
extern S16 cmUnpkEgTnlStsCfm (EgTnlSts *tnlSts, Buffer *mBuf);
extern S16 cmUnpkEgSrvrStsCfm (EgTptSrvrSts *tSrvrSts, Buffer *mBuf);
extern S16 cmUnpkEgIpAddrStsCfm (EgIpSts *ipSts, Buffer *mBuf, Pst *pst);
extern S16 cmPkEgTnlStsCfm (EgTnlSts *tnlSts, Buffer *mBuf);
extern S16 cmPkEgIpAddrStsReq (EgIpSts *ipSts, Buffer *mBuf);
extern S16 cmPkEgSrvrStsReq (EgTptSrvrSts *tSrvrSts, Buffer *mBuf);
extern S16 cmPkEgTnlStsReq (EgTnlSts *tnlSts, Buffer *mBuf);
extern S16 cmUnpkEgIpAddrStsReq (EgIpSts *ipSts, Buffer *mBuf);
extern S16 cmUnpkEgSrvrStsReq (EgTptSrvrSts *tSrvrSts, Buffer *mBuf);
extern S16 cmUnpkEgTnlStsReq (EgTnlSts *tnlSts, Buffer *mBuf);
extern S16 cmPkEgSrvrStaReq (EgTptSrvSta *tserverSta, Buffer *mBuf);
extern S16 cmUnpkEgSrvrStaReq (EgTptSrvSta *tserverSta, Buffer *mBuf);
extern S16 cmPkEgTnlStaReq (EgTnlSta *tnlSta, Buffer *mBuf);
extern S16 cmUnpkEgTnlStaReq (EgTnlSta *tnlSta, Buffer *mBuf);
extern S16 cmUnpkEgTnlStaReq (EgTnlSta *tnlSta, Buffer *mBuf);
extern S16 cmUnpkEgSrvrStaCfm (EgTptSrvSta *tserverSta, Buffer *mBuf);
extern S16 cmPkEgTnlStaCfm (EgTnlSta *tnlSta, Buffer *mBuf);
extern S16 cmUnpkEgTnlStaCfm (EgTnlSta *tnlSta, Buffer *mBuf);
 S16 cmPkEgSrvrStaCfm (EgTptSrvSta *tserverSta, Buffer *mBuf);
extern S16 smEgActvTsk (Pst *pst, Buffer *mBuf);




extern S16 smEgActvInit (Ent ent, Inst inst, Region region, Reason reason)
                                                                    ;
extern S16 egActvInit (Ent ent, Inst inst, Region region, Reason reason);

extern S16 egActvTsk (Pst *pst, Buffer *mBuf);
typedef struct _egIeEntry
{
  U8 ieCode;
  U8 dataType;
  U16 minLen;
  U16 maxLen;

  Bool tvType;

}EgIeEntry;




typedef struct _egUIeProperties EgUIeProperties;



struct _egUIeProperties
{
   U8 ieType;
   U8 ieClass;
};



typedef struct _egUMsgEntry
{
   U8 msgType;
   U8 nmbIe;
   U8 nmbMandIe;
   EgUIeProperties ieProperties[3];
}EgUMsgEntry;



typedef struct _egUGmCb
{
   U16 posIdx[256];
   EgUMsgEntry gmEntry[6];
}EgUGmCb;



typedef struct _egUIeCb
{
   U16 posIdx[256];
   EgIeEntry ieEntry[6];
}EgUIeCb;



typedef struct _egUEdmCb
{
   EgUIeCb egIeCb;
   EgUGmCb egMsgCb;
}EgUEdmCb;







typedef struct egTSapCb EgTSapCb;
typedef struct egUSapCb EgUSapCb;
typedef struct egTunnCb EgTunnCb;
typedef struct egTptSrvCb EgTptSrvCb;
typedef struct _destAddrCb EgDestAddrCb;
typedef struct _ipCb EgIpCb;





typedef struct egTimer
{
   CmTimer tmr;
   U32 egCbPtr;
} EgTimer;





typedef struct _teIdCb EgTeIdCb;
typedef struct _egUThreadCb EgUThreadCb;

typedef struct _seqInfo
{
   Bool reOrder;
   U32 expSeqNmb;
   U32 curLastSeq;
   U32 lastRcvdSeq;
   U32 numRcvdPdus;
   U32 winStart;
   EgtUEvnt **pduArray;
}SeqInfo;


struct _teIdCb
{
   CmHashListEnt destTeIdEnt;

   CmHashListEnt egTeIdEnt;




   U8 tunnelType;

   U8 dscp;
   U8 reordAlgo;
   EgTimer reOrderTimer;
   U32 teId;
   SeqInfo *seqInfo;
   Bool endMarker;
   Bool reOrdering;
   Cntr totalMsgsTx;
   Cntr totalMsgsRx;
   EgUSapCb *uSapCb;

   EgDestAddrCb *dstAddrCb;
   EgTptSrvCb *tptSrvrCb;
   EgIpCb *ipCb;
   struct
   {
      U8 hdr[40];
      U8 cnt;
   }preEncHdr;
   U32 remTeid;


};

struct _destAddrCb
{
   CmHashListEnt destEnt;
   U32 echoReqSent;
   U8 intfType;


   U32 forwardingTunnCnt;
   U32 normaldataTunnCnt;

   CmTptAddr destIpAddr;
   Bool destReachable;


   Bool multicastAddr;
   CmHashListCp teIdLst;
   U16 maxTPduSize;
   S32 channel;
};

struct _ipCb
{
   CmHashListEnt ipCbOnUSapEnt;
   EgIpInfo ipAddrInfo;
   CmHashListCp tptServCbLst;
   EgIpSts ipStats;
   U16 status;
   CmHashListCp destAddrCbLst;
   Bool dfltPort;
   Bool encEchoAvail;
};

typedef struct _egUEchoReqCb
{
   CmHashListEnt echoEnt;
   U32 seqNo;
   SpId uSapId;
   Buffer *echoReqBuff;
   EgTptSrvCb *tptServerCb;
   CmTptAddr srcAddr;
   CmTptAddr destAddr;
}EgUEchoReqCb;

typedef struct egTptStat
{
   Cntr totalMsgsTx;
   Cntr totalMsgsRx;
}EgTptStat;


typedef struct _egUcb
{
   CmHashListCp echoReqHashList;
   CmTimer echoTimers;
   CmTimer n3t3Timers;
   EgUEdmCb edmUCb;
   Bool echoTmrStarted;

   U8 echoReqCntr;
}EgUcb;
typedef enum _egtMsgCat
{
   EG_GTPC_MSGCAT_REQUEST,
   EG_GTPC_MSGCAT_RESPONSE,
   EG_GTPC_MSGCAT_NOTFN,
   EG_GTPC_MSGCAT_ACKN,
   EG_GTPC_MSGCAT_COMMAND,
   EG_GTPC_MSGCAT_IND,
   EG_GTPC_MSGCAT_FAILIND,
   EG_GTPC_MSGCAT_RSP_ACK,
   EG_GTPC_MSGCAT_OTHER
}EgtMsgCat;



typedef enum _egModuleName
{
   EG_MOD_PCM,
   EG_MOD_PCM_USAP,
   EG_MOD_TPT,
   EG_MOD_EDM_GM,
   EG_MOD_EDM_IE,
   EG_MOD_CPM,
   EG_MOD_INVALID
}EgModuleName;


typedef enum _egTptSrvAct
{
   EG_TPT_TPTSRV_INVLD,
   EG_TPT_TPTSRV_CLOSE,
   EG_TPT_TPTSRV_OPEN,
   EG_TPT_TPTSRV_DISABLE,
   EG_TPT_TPTSRV_FREE
}EgTptSrvAct;




struct egUSapCb
{
   State state;
   SuId suId;
   Pst pst;
   EgUSapCfg cfg;
   EgSapSts sts;
   EgTSapCb *tSapCb;

   CmHashListCp ipCbHashList;
};
struct egTSapCb
{
   Pst pst;
   Ent contEnt;
   Bool cfgDone;
   SuId suId;
   SpId spId;
   State state;
   EgTSapCfg cfg;
   EgSapSts sts;
   EgTSapReCfg reCfg;
   U8 bndRetryCnt;
   U8 numSrvr;
   UConnId lastSuConnId;
   EgTptSrvCb **tptSrvCbLst;
   CmTimer timers[2];
   EgTimer bndTmr;
   U32 trcMask;
   S16 trcLen;
   Pst cfmPst;
   Header ctrlHdr;
   CmTptAddr tSapIpAddr;
   Bool ipCfgDone;
};






struct egTptSrvCb
{

   CmHashListEnt transportEnt;

   EgIpCb *ipCbPtr;
   EgTptStat stats;
   U16 portNum;
   U32 uSapId;
   Bool portStatus;
   Bool isdftlTptSrv;

   UConnId suConnId;
   UConnId spConnId;
   U8 state;
   TknStrOSXL hostName;
   EgTptSrvCfg cfg;
   EgUSapCb *uSapCb;
   EgTSapCb *tSapCb;
   EgTimer opnSrvTmrNode;
   S16 opnSrvCurRetryCnt;





};
typedef struct _egCb
{
   TskInit init;
   EgGenCfg genCfg;
   EgGenSts genSts;
   EgGenSta genSta;
   EgUSapCb **egtSapLst;



   EgTSapCb *tSapCb;




   CmTqCp egTqCp;
   CmTqType egTq[1024];
   U8 outOfRsrc;
   Bool shutdown;
   Bool ieCfgDone;

  EgUcb egUCb;
CmHashListCp egTeidHashListCp;

} EgCb;






typedef struct _eguEvnt
{
   U8 msgType;
   U16 seqNumber;
   U32 teid;
   CmTptAddr localAddr;
   CmTptAddr remAddr;
   EgTptSrvCb *srvCb;
   U8 intfType;
   S16 resultType;
   Region region;
   Pool pool;
   U8 failedIeInst;
   U8 failedIeType;
   U8 failedMsgType;
   U16 maxTPduSize;
   U16 tPduSize;
   Bool isEnc;
   U8 eventType;
   EgTeIdCb *teIdCb;
   EgDestAddrCb *destAddrCb;
   EgIpCb *ipCb;
   EgUSapCb *usap;
   EgTSapCb *tsap;
   EgMngmt *lmInfo;
   Bool errInd;

   Bool suppExtHdrNtf;

   Buffer *mBuf;
   EgUMsg *egMsg;
}EgUEvnt;







extern EgCb egCb;
extern S16 egTptInit ( Void );
extern Void egTptDeInit ( Void );
extern S16 egTptState ( CmTptAddr localAddr, TknU8 *state);
extern S16 egTptProcessTsapServers ( EgTSapCb *tsapCb, EgTptSrvAct srvAction)

                                                    ;
extern S16 egTptOpenServer ( EgTptSrvCb *serverCb, U16 *reason)

                                                    ;
extern Void egTptCloseServer ( EgTptSrvCb *serverCb )
                                                       ;
extern Void egTptFreeServer ( EgTptSrvCb *serverCb )
                                                       ;
extern Void egMiTptSrvOpenInd ( EgTptSrvCb *srvCb )

                 ;
extern Void egMiTptSrvCloseInd ( EgTptSrvCb *serverCb, Bool fromLMI )

                                                              ;
extern Data *egAlloc ( Size size )


  ;
extern S16 egFree ( Data *pCb, Size size )



  ;
extern S16 egSendLmAlarm ( U16 category, U16 event, U16 cause, EgUstaDgn *dgn )





  ;
extern S16 egSendLmCfm ( Pst *pst, Header *hdr, U8 type, EgMngmt *cfm )





  ;
extern Void egSendLmCntrlCfm (Pst *pst, U16 status, U16 reason, Header *hdr)


                                                   ;
extern Void egGenTrcInd ( EgTSapCb *tSapCb, S16 elmnt, CmTptAddr *srcAddr, CmTptAddr *destAddr, U16 evnt, Buffer *mBuf )







  ;





extern S16 egSchedTmr (Ptr egHandle, S16 tmrEvnt, Action action, U32 tmrVal)

                                                                ;

extern Void egTmrEvnt (Ptr cb, S16 event)
                                                ;

extern Void egCmInitTimer (EgTimer *tmr);

extern S16 egRegInitTmr (Void);

extern Void egRmvTmr ( U32 cbp, CmTimer *pTimerStruct, U8 tmrNum, U8 maxNmbTmrs)


                                                  ;




extern Void egCmPrntDbg ( U8 ptrType, void *ptr, S8 *name )


                                 ;

extern Void PrintEGTPStats (void )
                                  ;

extern Void ResetEGTPStats (void )
                                  ;





extern S16 egEdmDeInit ( Void )


  ;

extern S16 egAllocIntfLst ( U8 nmbIntf )


  ;


extern Size egGetIntfMem ( Void )


  ;
extern S16 egCpyCmTptAddr ( CmTptAddr *dst, CmTptAddr *src )


                                  ;
extern S16 egCmpTptAddr (CmTptAddr *one, CmTptAddr *two, Bool *addressMatch)

                                                                   ;






extern S16 egActvTmr (Void);




extern S16 egTptSendMsg (EgTptSrvCb *serverCb, CmTptAddr *destAddr, Buffer *mBuf, Pst *pst);

extern S16 egCpmInit (EgMngmt *cfgReq, EgModuleName module);

extern S16 egCpmDeinit (Void);

extern S16 egInitExt (Void);

extern S16 egGetSId (SystemId *sysId);
extern Void egUpdateTxStatistics ( EgtMsgType msgType, EgSapSts *sts )


                                     ;
extern Void egUpdateRxStatistics ( EgtMsgType msgType, EgSapSts *sts )


                                          ;


extern S16 egTptUdpServerDatReq ( EgTptSrvCb *serverCb, CmTptAddr *destAddr, Buffer *mBuf, Pst *pst, U8 tos )




                                                      ;


extern S16 egUCpmProcLiMsg
(
 EgUEvnt *eguEvnt,
 Pst *pst
 );


extern S16 egFTunProcEguDatReq
(
EgtUEvnt *egtUEvnt,
EgUSapCb *usap,
Pst *pst
);

extern Void egUCpmProcUiMsg
(
EgUEvnt *eguEvnt,
Pst *pst
);

extern Void egFUCpmProcUiMsg
(
EgTeIdCb *teIdCb,
EgUMsg *egMsg,
Pst *pst
);


extern S16 egUFEncodeGmHdr
(
   U8 *preEncHdr,
   EgUMsgHdr *statHdr,
   U8 *hdrIndex
);

extern S16 egFpTunProcFwdEguDatReq
(
U32 lclTeid,
U32 remTeid,
U32 tPduSise,
Buffer *mBuf,
U32 pdcpSduId,
U32 pdcpSeqNo
);

extern S16 egFTunProcEguDatReq
(
EgtUEvnt *egtUEvnt,
EgUSapCb *usap,
Pst *pst
);

extern S16 egFUEncMsgReq
(
   EgtUEvnt *evntMsg,

   EgTeIdCb *teIdCb,
   Buffer **mBuffer
);
extern S16 egLiPrcBndCfm
(
SuId suId,
EgTSapCb *tsapCb,
U16 result
);
extern S16 egUEncMsgReq (EgUEvnt *evntMsg);
extern S16 egUDecMsgReq (EgUEvnt *evntMsg);

extern S16 egUTptGetMsg (EgTptSrvCb *serverCb, CmTptAddr *srcAddr, Buffer *mBuf, Pst *pst);
extern S16 egUCmCreateEvent (EgUEvnt **newEvent);
extern S16 egTunProcEguDatReq (EgtUEvnt *egtUEvnt, EgUSapCb *usap, Pst *pst);
extern S16 egTunProcEguTnlMgmtReq (EgtUEvnt *egtUEvnt, EgUSapCb *usap);
extern S16 egUTunnTeidMod (EgtUEvnt *egtUEvnt, EgIpCb *ipCb);
extern S16 egUTunnTeidDel (EgtUEvnt *egtUEvnt, EgIpCb *ipCb, EgUSapCb *usap);
extern S16 egUTunnTeidReordEna (EgtUEvnt *egtUEvnt, EgIpCb *ipCb);
extern S16 egUTunnTeidReordDis (EgtUEvnt *egtUEvnt, EgIpCb *ipCb, EgUSapCb *usap);
extern S16 egUTunnTeidAdd (EgtUEvnt *egtUEvnt, EgIpCb *ipCb);
extern S16 egTunProcEguStaReq (EgtUEvnt *egtUEvnt, EgUSapCb *usap);
extern S16 egUFreeUiEvnt (EgtUEvnt *egtUEvnt);
extern S16 egUCpmHdlEvt (EgUEvnt *eguEvnt, Pst *pst);
extern S16 egTnlFreeReOrderQReq (Inst threadId);
extern S16 egUTunnDeleteTunnel (EgUEvnt *eguEvnt);
extern S16 egUCmFreeEvent (EgUEvnt *event);


extern S16 egUPlatTunnTeidAdd (EgDestAddrCb *dstCb);
extern S16 egUPlatTunnTeidDel (EgDestAddrCb *dstCb);

extern S16 egReordRcvdEguMsgs (EgTeIdCb *teidCb, EgtUEvnt *egtuEvt);

extern Void egUCpmProcMsg (EgUEvnt *eguEvnt, Pst *pst);

extern S16 egUCpmHdlTeid (EgUEvnt *eguEvnt);

extern S16 egGetThrdId (EgTeIdCb **egTeidCb, S16 event, EgUThreadCb **pThrCb);

extern S16 egAssignThrd (EgTeIdCb *egTeidCb);

extern S16 egLdDistribute (Void);

extern S16 egFlushReordRcvdGtpuPdus (EgTeIdCb *teidCb);
extern S16 egFlushAllPackets (EgTeIdCb *teidCb);
extern S16 egFlushTillHole (EgTeIdCb *teidCb);

extern S16 egDeleteTun (EgTeIdCb *teidCb);
extern S16 egSchedreOrdTmr (Ptr egHandle, S16 tmrEvnt, Action action, U32 tmrVal);
extern S16 egUTunnReordCfm (EgUEvnt *eguEvnt);
extern S16 egUHndlT3N3TmrExpiry (Void);

extern S16 egUSendEchoReqOnLclPort (EgIpCb *ipCb, EgUEvnt *echoEvnt, U16 *echoSeqNo)
                                                    ;
extern S16 egUSendEchoReq (Void);
extern S16 egMiProcIpCb (EgIpCb *ipCb, SpId spId);
extern Void egUCpmProcEguDatReq (EgtUEvnt *egtUEvnt, EgUSapCb *usap, Pst *pst);
extern Void egUCpmProcEguStaReq (EgtUEvnt *egtUEvnt, EgUSapCb *usap);
extern Void egUCpmProcEguTnlMgmtReq (EgtUEvnt *egtUEvnt, EgUSapCb *usap );
extern S16 EgMiHdlCntrlCfmFrmWrkr (EgUEvnt *eguEvnt);
extern S16 egMiRmvEchoCb (EgUSapCb *uSapCb, EgIpCb *ipCb, EgTptSrvCb *srvCb, EgTSapCb *tSapCb, U8 type)
                                                                                    ;
extern S16 egMiGetIpCb (EgUSapCb *uSapCb, EgMngmt *cntrlReq, U8 eventType, U8 *nmbReq);
extern S16 egMiIpCbDeInit (CmHashListCp *IpCbHashList, Bool del);
extern S16 egHndlRecvFb (U8 *buf, U32 bufLen );
 S16 egTptGetTsapFrmAddr ( CmTptAddr tptSrvAddr, EgTSapCb **tSapCb);


extern S16 SGetReadPtr(Buffer *mBuf, U8** data, MsgLen *len);
typedef struct egPartialMsg
{
   U32 seqNo;
   EgtMsgType msgType;
   EgtMsgCat msgCat;
   U32 teid;
   Bool pbMsgPres;
   Bool isitPbmsg;
   MsgLen iniMsgLen;
   MsgLen pbMsgLen;
}EgPartialMsg;
extern Void egTptIssueDiscReq ( EgTSapCb *tsapCb, U8 choice, ConnId connId)


                                                  ;
extern Void egTptDelAllServerContext ( EgTptSrvCb *serverCb, Bool informUser)

                                                       ;
extern S16 egUtlDelTknStrOSXL ( TknStrOSXL *delTknStrOSXL )
                                                            ;
typedef enum _egDataTypes
{
  EG_FTEID =1,
  EG_UNSIGNED_8 ,
  EG_UNSIGNED_16,
  EG_UNSIGNED_32,
  EG_CAUSE ,
  EG_PVT_EXTN ,
  EG_TRC_INFO ,
  EG_ULI_DATA ,
  EG_FQOS ,
  EG_BQOS_IEDATA =10,
  EG_PAA_IEDATA ,
  EG_GLOBAL_CNID,
  EG_STRING_8 ,
  EG_STRING_16 ,
  EG_STRING_32 ,
  EG_STRING_132 ,
  EG_STRING_MAX ,
  EG_SNETWORK ,
  EG_INDICATION ,
  EG_BEARER_FLAG =20,
  EG_GROUPED ,
  EG_IP_ADDR ,
  EG_S103_PDN_FW_INFO,
  EG_S1U_DATA_FW,
  EG_PDUNUM,
  EG_UE_TIME_ZONE,
  EG_TRACE_REF,
  EG_RAB_CONTEXT,
  EG_GSM_KEY_TRIP,
  EG_UMTS_KEY_CIPH_QUIN =30,
  EG_GSM_KEY_CIPH_QUIN,
  EG_UMTS_KEY_QUIN,
  EG_EPS_SEC_QUAD_QUIN,
  EG_UMTS_KEY_QUAD_QUIN,
  EG_AUTH_QUIN,
  EG_AUTH_QUAD = 36,
  EG_CMP_REQ,
  EG_GUTI,
  EG_F_CONT,
  EG_F_CAUSE =40,
  EG_TRGTID,
  EG_SRCID,
  EG_PKTFLOWID,
  EG_SRC_RNC_PDCP_CTX,
  EG_PDN_CONN_SET_ID =45,
  EG_AMBR,
  EG_GLOBAL_CN_ID,





  EG_EXT_HDR_TYPE_LST,
  EG_MAX_DATATYPE
}EgDataTypes;
 S16 EgUUtilAllocGmMsg (EgUMsg **egMsg, Mem *memInfo );
 S16 EgUUtilDeAllocGmMsg (EgUMsg **egMsg);
 S16 EgUUtilGmAppendIe (EgUMsg *egMsg, EgUIe *egIe );
 S16 EgUUtilGmDelIe ( EgUMsg *egMsg,U8 ieType,U8 occrCnt );
 S16 EgUUtilGmGetIeOccrCnt ( EgUMsg *egMsg, U8 *ieType, U16 *ieOccrCnt )
                                                          ;
 S16 EgUUtilGmDump ( EgUMsg *egMsg );




 S16 egUUtilCmpTptAddr (CmTptAddr *srcAddr, CmTptAddr *destAddr, U16 *port);
extern Void EgTLSendMsg(Bool param);







extern S16 SAttachPtrToBuf (Region region,Pool pool,Data *ptr,MsgLen totalLen,Buffer** mBuf)
                                          ;
extern void EgTLInitReq(Region region, Pool pool);
extern U32 EgTLReadMsg(U32 timeOut, U32 maxEvent);
extern void EgTLThShutdownReq(void);
extern S16 egTLSendSockMsg
(
CmInetFd *sockFd,
CmInetAddr *dstAddr,
CmInetMemInfo *info,
Buffer *mBuf,
MsgLen *len,
U8 tos
);
extern U32 EgTLBndReq
(
   Pst *pst,
   SuId suId,
   SpId spId
);
extern U32 EgTLUbndReq
(
   Pst *pst,
   SpId spId,
   Reason reason
);
extern U32 EgTLDiscServerReq
(
   UConnId conId
);


extern S16 EgLiHitBndCfm
(
 Pst *pst,
 SuId suId,
 U8 status
);


extern S16 EgLiHitConCfm
(
 Pst *pst,
 SuId suId,
 UConnId suConnId,
 UConnId spConnId,
 CmTptAddr *localAddr
);


extern S16 EgLiHitUDatInd
(
 Pst *pst,
 SuId suId,
 UConnId suConnId,
 CmTptAddr *srcAddr,
 CmTptAddr *remAddr,
 CmIpHdrParm *ipHdrParm,
 Buffer *mBuf
);
extern U32 EgTLDatReq
(
UConnId spConId,
CmTptAddr *remAddr,
CmTptAddr *srcAddr,
CmIpHdrParm *hdrParm,
Buffer *mBuf
);
extern U32 EgTLOpenServerReq
(
Pst *pst,
SpId spId,
UConnId servConId,
CmTptAddr *servTAddr
);
typedef struct _egTLmsgQueue
{
   CmTptAddr dstAddr;
   Buffer *mBuf;
   MsgLen msglen;



   U8 tos;
   Bool flag;
}EgTLMsgQueue;
typedef struct _egTLserverCb
{
   CmTptAddr serverAddress;
   EgTLMsgQueue msgQueue[256];
   EgTLMsgQueue egtpMsgQueue[256];
   U32 front;
   U32 rear;
   U32 egtpPktFront;
   U32 egtpPktRear;
   U32 qLen;
   U32 egtpPktQLen;
   U32 srvConId;
   U32 sockFd;



   U8 sockType;
   Bool isSocketNonBlocking;
   U32 latestFront;
   U32 latestRear;
}EgTLServerCb;
typedef struct _egDlPktCntrl
{
   U32 maxNumPacketsToRead;
   U32 oldDlTimeCnt;
   U32 numPacketProcessed;
   U32 dlTimeWindowCnt;
   U32 dlTimeWindow;
   U32 totalTime;
}EgDlPktCntrl;
typedef struct _egUlPktCntrl
{
   U32 maxNumPacketsToSend;
   U32 oldUlTimeCnt;
   U32 numPacketSent;
   U32 ulTimeWindowCnt;
   U32 ulTimeWindow;
}EgUlPktCntrl;
typedef struct _egUlQueueCntrl
{
   U32 queueFullCnt;
   U32 queueNotFullCnt;
}EgUlQueueCntrl;
typedef struct _egTLCb
{
   EgTLServerCb servers[1];
   CmInetMemInfo memInfo;
   U32 ePollFd;
   U32 maxMsgToread;
   Pst egPst;
   EgUlQueueCntrl egUlQueueCntrl;
   EgDlPktCntrl dlPktCntrl;
   EgUlPktCntrl ulPktCntrl;
   U32 isCpuBasedContrl;
}EgTLCb;

 EgTLCb egTLCb;



typedef enum _egTLsockType
{
   TH_SERVER = 1,
   TH_CLIENT,
   TH_MAX
}EgTLSockType;

typedef struct _packetInfo
{
   U32 numOfPktsRcvd;
   U32 numBytesRcvd;
   U32 numOfPktsSent;
   U32 numBytesSent;
}PacketInfo;
 EgCb egCb;





 S16 egGetFreeTptConnId ( EgTSapCb *TSapCb, U8 type, U8 patanahi, U16 maxNoSrvr, U16 lastConnId, U16 suconnId )







  ;

static Void egMiFillResponsePost ( Pst *respPst, Pst *reqPst, Header *reqHeader)


                                   ;






static S16 egMiFindSrvCb ( EgTptSrvCfg *TSrvCfg, EgTptSrvCb *TSrvCb)

                                     ;
static S16 egGenCfg ( EgGenCfg *genCfg, CmStatus *status )



  ;
static S16 egValidateGenCfg ( EgGenCfg *genCfg )


  ;
static S16 egValidateUSapCfg ( EgUSapCfg *egUsapCfg )


  ;
static S16 egUSapCfg ( EgUSapCfg *USapCfg, CmStatus *status )



  ;
static S16 egValidateTSapCfg ( EgTSapCfg *tSapCfg, EgTSapReCfg *tSapReCfg )



  ;
static S16 egTSapCfg ( EgTSapCfg *tSapCfg, EgTSapReCfg *tSapReCfg, CmStatus *status )




  ;
static S16 egIpAddrCfg
(
EgIpAddrCfg *ipAddrCfg,
CmStatus *status
);


static S16 egTServerCfg ( EgTptSrvCfg *TptSrvCfg, CmStatus * status )



  ;

static S16 egGenCntrl ( EgMngmt *genCntrl )


  ;
static S16 egUSapCntrl ( EgMngmt *uSapCntrl )


  ;




static S16 egIpAddrCntrl
(
EgMngmt *ipAddrCntrl
);
static S16 egTSapCntrl ( EgMngmt *tSapCntrl )


  ;
static S16 egTServerCntrl ( EgMngmt *tSrvrCntrl )


  ;
static S16 egUSapStaReq ( EgMngmt *staReq, EgMngmt *staCfm )



  ;
static S16 egTSapStaReq ( EgMngmt *staReq, EgMngmt *staCfm )



  ;
static S16 egGenStaReq ( EgMngmt *staReq, EgMngmt *staCfm )



  ;
static S16 egGenStsReq ( EgMngmt *stsReq, Action action, EgMngmt *stsCfm )




  ;
static S16 egUSapStsReq ( EgMngmt *stsReq, Action action, EgMngmt *stsCfm )




  ;
static S16 egTSapStsReq ( EgMngmt *stsReq, Action action, EgMngmt *stsCfm )




  ;
static S16 egUnbindNDisableTSap ( EgTSapCb *tSapCb, Bool ShutDownFlg )



  ;
static S16 egMiDisableUsap ( EgUSapCb *uSapCb )


  ;
static S16 egMiDelUsap ( EgUSapCb *uSapCb )


  ;
 S16 egShutdown ( Void )


  ;
static Void egInitEgCb (Void);

static S16 egInitEguCb (CmStatus *status);
static S16 egMiTptSrvrDeInit (CmHashListCp *tptSrvrHashList, Bool del);
static S16 egMiDestAddrDeInit (CmHashListCp *destAddrHashList, Bool del);
static S16 egSrvrStsReq (EgMngmt *stsReq, Action action, EgMngmt *stsCfm);
static S16 egIpAddrStsReq (EgMngmt *stsReq, Action action, EgMngmt *stsCfm);
static S16 egTnlStsReq (EgMngmt *stsReq, Action action, EgMngmt *stsCfm);
static S16 egTptSrvStaReq (EgMngmt *staReq, EgMngmt *staCfm);
static S16 egTnlStaReq (EgMngmt *staReq, EgMngmt *staCfm);
static S16 egMiMoveIpAddr (EgIpCb *ipCb, U16 fromSpId, U16 toSpId);
static S16 egMiDelIpAddr (EgIpCb *ipCb, U16 fromSpId);
static S16 egMiteIdCbDeInit (CmHashListCp *teIdHashList, Bool del);
 S16 EgMiLegCfgReq
(
Pst *pst,
EgMngmt *cfgReq
)





{
   S16 retValue = 0;
   EgMngmt cfgCfm;
   EgMngmt egCfg;


   Pst cfmPst;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",719); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }
   { if ((&(egCb.init))->dbgMask & (0x00000002)) { snprintf((&(egCb.init))->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Eg", (&(egCb.init))->procId, (&(egCb.init))->ent, (&(egCb.init))->inst,
                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
   ,
                                                                 740
   ); SPrint((&(egCb.init))->prntBuf); sprintf (egCb.init.prntBuf, "EgMiLegCfgReq (elmId(%d))\n", cfgReq->hdr.elmId.elmnt); SPrint((&(egCb.init))->prntBuf); } }
                                                                  ;




   cmMemset( (U8* )&cfgCfm, 0, sizeof(EgMngmt));
   cmMemset( (U8* )&egCfg, 0, sizeof(EgMngmt));





   (Void)cmMemcpy((U8 *)&egCfg.hdr, (U8 *)&cfgReq->hdr,
                                         sizeof(Header));

   egMiFillResponsePost(&cfmPst, pst, &cfgReq->hdr);






   if ( (!egCb.init.cfgDone) && (cfgReq->hdr.elmId.elmnt != 1))
   {
      SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                765
      , 0x4, ((0 + 0) + 116), 0, (Txt *)"EgMiLegCfgReq: General configuration not done ");
                                                                 ;




      cfgCfm.cfm.status = 1;
      cfgCfm.cfm.reason = 8;

      if(cfgReq->hdr.elmId.elmnt == 8)
      {
         cfgCfm.hdr.elmId.elmnt = cfgReq->hdr.elmId.elmnt;
         cfgCfm.u.cfg.s.ipAddr.nmbIpAddr = cfgReq->u.cfg.s.ipAddr.nmbIpAddr;
         cfgCfm.u.cfg.s.ipAddr.ipInfo = cfgReq->u.cfg.s.ipAddr.ipInfo;
      }





      egSendLmCfm(&cfmPst, &cfgReq->hdr, 1, &cfgCfm);

      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",786); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
   }






   switch (cfgReq->hdr.elmId.elmnt)
   {
      case 1:
      {



         retValue = egGenCfg((EgGenCfg *)&cfgReq->u.cfg.s.gen, &cfgCfm.cfm);

         break;
      }

      case 2:
      {



         retValue = egUSapCfg((EgUSapCfg *)&cfgReq->u.cfg.s.uSap, &cfgCfm.cfm);

         break;
      }

      case 3:
      {



         retValue = egTSapCfg((EgTSapCfg *)&cfgReq->u.cfg.s.tSap,
                                 &cfgReq->u.cfg.r.tSapReCfg, &cfgCfm.cfm);


         break;
      }




      case 8:
      {



         retValue = egIpAddrCfg((EgIpAddrCfg *)&cfgReq->u.cfg.s.ipAddr, &cfgCfm.cfm);
         if(retValue != 0 || cfgCfm.cfm.status != 0)
         {
            cfgCfm.hdr.elmId.elmnt = cfgReq->hdr.elmId.elmnt;
            cfgCfm.u.cfg.s.ipAddr.nmbIpAddr = cfgReq->u.cfg.s.ipAddr.nmbIpAddr;
            cfgCfm.u.cfg.s.ipAddr.ipInfo = cfgReq->u.cfg.s.ipAddr.ipInfo;
         }
         break;
      }



      case 4:
      {



         retValue = egTServerCfg((EgTptSrvCfg *)&cfgReq->u.cfg.s.tptSrv, &cfgCfm.cfm);

         break;
      }

      default:
      {
         SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                 861
         , 0x4, ((0 + 0) + 117), 0, (Txt *)"EgMiLegCfgReq: invalid elmnt");
                                                  ;




         cfgCfm.cfm.status = 1;
         cfgCfm.cfm.reason = 5;

         break;
      }
   }





   egSendLmCfm(&cfmPst, &cfgReq->hdr, 1, &cfgCfm);




   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",882); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egValidateGenCfg
(
EgGenCfg *genCfg
)




{
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",912); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }





   if(egCb.init.cfgDone == 1)
   {




      (Void) cmMemcpy((U8 *)&egCb.init.lmPst, (U8 *) &genCfg->lmPst,
                      (U32)sizeof(Pst));




      egCb.init.lmPst.srcProcId = egCb.init.procId;
      egCb.init.lmPst.srcEnt = egCb.init.ent;
      egCb.init.lmPst.srcInst = egCb.init.inst;
      egCb.init.lmPst.event = 0x00;


      egCb.init.lmPst.region = egCb.init.region;


      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",939); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };

   }





   if (genCfg->nmbUSaps < 1 || genCfg->nmbUSaps > 100)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                       950
      , 0x4, ((0 + 0) + 120), 0, (Txt *)"egValidateGenCfg: invalid number of USAPs");; if(49 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",950); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(49); }; } }
                                                                        ;
   }




   if (genCfg->nmbSrvs < 1 || genCfg->nmbSrvs > 100)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                       959
      , 0x4, ((0 + 0) + 121), 0, (Txt *)"egValidateGenCfg: invalid number of SRVRS");; if(50 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",959); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(50); }; } }
                                                                        ;
   }





   if (genCfg->timerRes < 1)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                        969
      , 0x4, ((0 + 0) + 124), 0, (Txt *)"egValidateGenCfg: invalid Timer Resolution");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",969); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                         ;
   }




   if (genCfg->resThreshUpper > 9 || genCfg->resThreshUpper < 5)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                        978
      , 0x4, ((0 + 0) + 125), 0, (Txt *)"egValidateGenCfg: invalid  Upper Threshold");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",978); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                         ;
   }




   if (genCfg->resThreshLower > 4 ||
                           genCfg->resThreshLower < 1)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                       988
      , 0x4, ((0 + 0) + 126), 0, (Txt *)"egValidateGenCfg: Invalid Lower Threshold");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",988); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                        ;
   }




   if (genCfg->echoTmr.enb == 1 && genCfg->echoTmr.val == 0)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                        997
      , 0x4, ((0 + 0) + 128), 0, (Txt *)"egValidateGenCfg: Invalid echo Timer value");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",997); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                         ;
   }




   if (genCfg->echoTmr.enb == 0 && genCfg->eguT3Timer.enb == 1)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                              1006
      , 0x4, ((0 + 0) + 129), 0, (Txt *)"egValidateGenCfg: Echo Timer needs to be enabled for T3 N3 timer");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1006); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                                               ;
   }




   if (genCfg->eguT3Timer.enb == 1 && genCfg->eguT3Timer.val == 0)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                        1015
      , 0x4, ((0 + 0) + 130), 0, (Txt *)"egValidateGenCfg: Invalid T3N3 Timer value");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1015); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                         ;
   }





   if ((genCfg->echoTmr.enb == 1) &&
         ((genCfg->eguT3Timer.val * (genCfg->nmbRetries + 1) > genCfg->echoTmr.val)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                                                  1026
      , 0x4, ((0 + 0) + 131), 0, (Txt *)"egValidateGenCfg: Invalid T3N3 Timer value: N3T3 Timer * (Number of Retries +1) > Echo Timer");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1026); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                                                                   ;
   }



   if ((genCfg->eguT3Timer.enb == 1) && (genCfg->nmbRetries == 0))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                        1034
      , 0x4, ((0 + 0) + 132), 0, (Txt *)"egValidateGenCfg: Invalid T3N3 Timer value");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1034); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                         ;
   }




   if (genCfg->reOrderTmr.enb == 1 && genCfg->reOrderTmr.val == 0)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                           1043
      , 0x4, ((0 + 0) + 133), 0, (Txt *)"egValidateGenCfg: Invalid Reorder Timer value");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1043); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                            ;
   }




   if (genCfg->pduWindSize == 0 && genCfg->nodeArch == 0)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                       1052
      , 0x4, ((0 + 0) + 134), 0, (Txt *)"egValidateGenCfg: Invalid PDU window size");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1052); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                        ;
   }




   if (genCfg->maxNumOfIp >= 100)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                     1061
      , 0x4, ((0 + 0) + 135), 0, (Txt *)"egValidateGenCfg: Invalid number of Ips");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1061); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                                      ;
   }
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1075); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egGenCfg
(
EgGenCfg *genCfg,
CmStatus *status
)





{
   Size memSize;
   S16 retValue = 0;
   U32 idx = 0;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1116); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }







   if ( (retValue = egValidateGenCfg(genCfg)) != 0)
   {
      { if(status != 0L) { status->status = 1; status->reason = retValue; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                              1127
      , 0x4, ((0 + 0) + 138), 0, (Txt *)"egGenCfg: Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1127); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                               ;
   }




   status->status = 0;
   status->reason = 0;





   if(!egCb.init.cfgDone)
   {
      egInitEgCb();




      if((retValue = egInitEguCb(status)) != 0)
      {
         { if(status != 0L) { status->status = 1; status->reason = retValue; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                              1150
         , 0x4, ((0 + 0) + 139), 0, (Txt *)"egGenCfg: Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1150); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                               ;
      }

   }
   else
   {





      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1161); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(3); };
   }






   (Void) cmMemcpy((U8 *) &egCb.genCfg, (U8 *)genCfg,
                   (U32)sizeof(EgGenCfg));
   memSize = egCb.genCfg.nmbUSaps * (sizeof(EgUSapCb) + sizeof(U32));

   memSize += (sizeof(EgTSapCb) + sizeof(U32));

   memSize += egCb.genCfg.nmbSrvs * (sizeof(EgTptSrvCb) + sizeof(U32));


   memSize += egCb.genCfg.maxNumOfIp * (sizeof(EgIpCb) + sizeof(U32));





   if ( (retValue = SGetSMem(egCb.init.region, (Size) memSize, &egCb.init.pool)) != 0)
   {
      { if(status != 0L) { status->status = 1; status->reason = retValue; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                  1197
      , 0x4, ((0 + 0) + 140), 0, (Txt *)"egGenCfg: Mem Alloc for Layer Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1197); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                   ;
   }
   egCb.egtSapLst = (EgUSapCb **) egAlloc((Size) (genCfg->nmbUSaps * sizeof(U32)));




   if (egCb.egtSapLst == 0L)
   {



      SPutSMem(egCb.init.region, egCb.init.pool);

      { if(status != 0L) { status->status = 1; status->reason = 4; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                1227
      , 0x4, ((0 + 0) + 141), 0, (Txt *)"egGenCfg: Mem Alloc for USap List Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1227); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                                 ;
   }




   for (idx = 0; idx < genCfg->nmbUSaps; idx++)
   {
      egCb.egtSapLst[idx] = (EgUSapCb *) 0L;
   }
   egCb.tSapCb = (EgTSapCb *) 0L;
   retValue = egRegInitTmr();

   if(retValue != 0)
   {



      retValue = egFree( (Data* )egCb.egtSapLst, (genCfg->nmbUSaps * sizeof(U32)));
      SPutSMem(egCb.init.region, egCb.init.pool);

      { if(status != 0L) { status->status = 1; status->reason = 7; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                            1296
      , 0x4, ((0 + 0) + 143), 0, (Txt *)"egGenCfg:  Timer Registration Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1296); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                             ;
   }




   (Void) cmMemcpy((U8 *)&egCb.init.lmPst, (U8 *) &genCfg->lmPst,
                   (U32)sizeof(Pst));

   egCb.init.lmPst.srcProcId = egCb.init.procId;
   egCb.init.lmPst.srcEnt = egCb.init.ent;
   egCb.init.lmPst.srcInst = egCb.init.inst;
   egCb.init.lmPst.event = 0x00;
   egCb.init.cfgDone = 1;
   egCb.genSta.memSize = memSize;




   status->status = 0;
   status->reason = 0;




     status->status = 0;
     status->reason = 0;

   { if ((&(egCb.init))->dbgMask & (0x00000002)) { snprintf((&(egCb.init))->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Eg", (&(egCb.init))->procId, (&(egCb.init))->ent, (&(egCb.init))->inst,
                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
   ,
                                              1347
   ); SPrint((&(egCb.init))->prntBuf); sprintf (egCb.init.prntBuf, "General configuration completed\n"); SPrint((&(egCb.init))->prntBuf); } }
                                               ;



   retValue = cmHashListInit(&(egCb.egTeidHashListCp),
                           1024,
                           sizeof(CmHashListEnt),
                           0,
                           7,
                           egCb.init.region,
                           egCb.init.pool);
   if(retValue != 0)
   {



      retValue = egFree( (Data* )egCb.egtSapLst, (genCfg->nmbUSaps * sizeof(U32)));
      SPutSMem(egCb.init.region, egCb.init.pool);

      { if(status != 0L) { status->status = 1; status->reason = 7; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                            1367
      , 0x4, ((0 + 0) + 143), 0, (Txt *)"egGenCfg:  Timer Registration Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1367); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                             ;
   }




   EgTLInitReq(egCb.init.region,egCb.init.pool);





   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1379); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static Void egInitEgCb
(
Void
)



{


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1407); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }






   egCb.genSta.memSize = 0;
   egCb.genSta.memAlloc = 0;





   egCb.shutdown = 0;
   egCb.ieCfgDone = 0;




   cmMemset((U8 *) &egCb.genCfg, (U8) 0, sizeof(EgGenCfg));




   cmMemset((U8 *) &egCb.genSts, (U8) 0, sizeof(EgGenSts));
   egCb.tSapCb = 0L;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1445); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
}
static S16 egValidateUSapCfg
(
EgUSapCfg *egUsapCfg
)




{
   EgUSapCb *uSapCb;
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1479); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   uSapCb = 0L;



   if ((egUsapCfg->sapId < (1 -1)) || (egUsapCfg->sapId >= egCb.genCfg.nmbUSaps))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                           1488
      , 0x4, ((0 + 0) + 145), 0, (Txt *)"egValidateUSapCfg():  Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1488); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                            ;
   }



   if(egUsapCfg->flag != 1)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                   1496
      , 0x4, ((0 + 0) + 149), 0, (Txt *)"egValidateUSapCfg():  Invalid protocol flag");; if(82 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1496); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(82); }; } }
                                                                    ;
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1499); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egUSapCfg
(
EgUSapCfg *UsapCfg,
CmStatus *status
)





{
   S16 retValue = 0;
   EgUSapCb *egUsapCb = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1538); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   status->status = 0;
   status->reason = 0;




   if ( (retValue = egValidateUSapCfg(UsapCfg)) != 0)
   {
      { if(status != 0L) { status->status = 1; status->reason = retValue; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                   1552
      , 0x4, ((0 + 0) + 150), 0, (Txt *)"egUSapCfg(): egValidateUSapCfg Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1552); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                    ;
   }




   if (egCb.egtSapLst[UsapCfg->sapId] == 0L)
   {



       egUsapCb = (EgUSapCb *) egAlloc((Size) sizeof(EgUSapCb));




       if (egUsapCb == 0L)
       {
          { if(status != 0L) { status->status = 1; status->reason = 4; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
          ,
                                                                          1571
          , 0x4, ((0 + 0) + 151), 0, (Txt *)"egUSapCfg(): Mem Alloc for USapCb Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1571); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                           ;
       }

   }
   else
   {



      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.prior = UsapCfg->priority;

      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.region = egCb.init.region;



      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.pool = UsapCfg->mem.pool;
      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.selector = UsapCfg->selector;
      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1620); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(3); };
   }





   egUsapCb->suId = 0;




   cmMemcpy((U8 *)&egUsapCb->cfg,
            (U8 *)UsapCfg, sizeof(EgUSapCfg));







   egUsapCb->pst.srcProcId = SFndProcId();




   egUsapCb->pst.srcEnt = egCb.init.ent;
   egUsapCb->pst.srcInst = egCb.init.inst;
   egUsapCb->pst.prior = UsapCfg->priority;
   egUsapCb->pst.route = UsapCfg->route;
   egUsapCb->pst.dstProcId = UsapCfg->dstProcId;
   egUsapCb->pst.dstEnt = UsapCfg->dstEnt;
   egUsapCb->pst.dstInst = UsapCfg->dstInst;

   egUsapCb->pst.event = 0;

   egUsapCb->pst.region = egCb.init.region;



   egUsapCb->pst.pool = UsapCfg->mem.pool;
   egUsapCb->pst.selector = UsapCfg->selector;




   (Void) cmMemset((U8 *)&egUsapCb->sts, 0, sizeof(EgSapSts));
   egUsapCb->sts.sapId = UsapCfg->sapId;




   egCb.egtSapLst[UsapCfg->sapId] = egUsapCb;

   {





          retValue = cmHashListInit(&(egUsapCb->ipCbHashList),
                               1024,
                               0,
                               0,
                               7,
                               egCb.init.region,
                               egCb.init.pool);
          if(retValue != 0)
           {



                egFree((Data *)egUsapCb,sizeof(EgUSapCb));
                status->status = 0;
                status->reason = 67;
                { if(status != 0L) { status->status = 1; status->reason = retValue; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                ,
                                                                                                        1696
                , 0x4, ((0 + 0) + 156), 0, (Txt *)"egUSapCfg(): Initialization of IpCb hash list failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1696); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                                                         ;
           }


    }



   egUsapCb->state = 1;
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1742); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egValidateTSapCfg
(
EgTSapCfg *tSapCfg,
EgTSapReCfg *tSapReCfg
)





{
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1775); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




     if((tSapCfg->tSapId > (SuId) 1) || (tSapCfg->tSapId < 0))
     {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                                 1783
       , 0x4, ((0 + 0) + 158), 0, (Txt *)"egValidateTSapCfg(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1783); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                                  ;
     }







   if (!egCb.tSapCb)

   {




     if((tSapCfg->tptType < 1) || (tSapCfg->tptType > 200))
     {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                                          1802
       , 0x4, ((0 + 0) + 159), 0, (Txt *)"egValidateTSapCfg(): Invalid Transport Type");; if(53 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1802); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(53); }; } }
                                                                           ;
     }
   }




   if((tSapReCfg->bndTmCfg.enb == 1) && (tSapReCfg->bndTmCfg.val == 0))
   {
     { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
     ,
                                                                        1812
     , 0x4, ((0 + 0) + 160), 0, (Txt *)"egValidateTSapCfg(): Invalid Bind Timer Val");; if(54 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1812); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(54); }; } }
                                                                         ;
   }




   if(tSapReCfg->maxBndRetry > 3)
   {
     { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
     ,
                                                                      1821
     , 0x4, ((0 + 0) + 161), 0, (Txt *)"egValidateTSapCfg(): Invalid Bind Retries");; if(55 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1821); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(55); }; } }
                                                                       ;
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1824); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTSapCfg
(
EgTSapCfg *tSapCfg,
EgTSapReCfg *tSapReCfg,
CmStatus *status
)






{
   S16 retValue = 0;
   EgTSapCb *NewTSapCb = 0L;







   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1871); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   status->status = 0;
   status->reason = 0;




   if ( (retValue = egValidateTSapCfg(tSapCfg, tSapReCfg)) != 0)
   {
      { if(status != 0L) { status->status = 1; status->reason = retValue; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                            1885
      , 0x4, ((0 + 0) + 162), 0, (Txt *)"egTSapCfg(): egValidate Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1885); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                             ;
   }
   if(!egCb.tSapCb)

   {
      NewTSapCb = (EgTSapCb *) egAlloc((Size) sizeof(EgTSapCb));

      if (NewTSapCb == 0L)
      {
        { if(status != 0L) { status->status = 1; status->reason = 4; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
        ,
                                                                              1903
        , 0x4, ((0 + 0) + 163), 0, (Txt *)"egTSapCfg(): Mem Alloc for TSapCb Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",1903); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                               ;
      }




      cmMemcpy((U8 *)&NewTSapCb->cfg, (U8 *) (tSapCfg),
               (U32)sizeof(EgTSapCfg));

      cmMemcpy((U8 *)&NewTSapCb->reCfg, (U8 *) (tSapReCfg),
               (U32)sizeof(EgTSapReCfg));




      NewTSapCb->tptSrvCbLst = (EgTptSrvCb **) egAlloc((Size)
                                            (egCb.genCfg.nmbSrvs *
                                             sizeof(U32)));




      NewTSapCb->suId = tSapCfg->tSapId;
      NewTSapCb->spId = tSapCfg->spId;
      NewTSapCb->state = 1;




      NewTSapCb->pst.prior = tSapCfg->priority;
      NewTSapCb->pst.route = tSapCfg->route;
      NewTSapCb->pst.selector = tSapCfg->selector;

      NewTSapCb->pst.region = egCb.init.region;



      NewTSapCb->pst.pool = tSapCfg->mem.pool;
      NewTSapCb->pst.dstProcId = tSapCfg->dstProcId;
      NewTSapCb->pst.dstEnt = tSapCfg->dstEnt;
      NewTSapCb->pst.dstInst = tSapCfg->dstInst;
      NewTSapCb->pst.srcProcId = egCb.init.procId;
      NewTSapCb->pst.srcEnt = egCb.init.ent;
      NewTSapCb->pst.srcInst = egCb.init.inst;
      NewTSapCb->pst.event = 0x00;





      NewTSapCb->lastSuConnId = egCb.genCfg.nmbSrvs;
      NewTSapCb->numSrvr = 0;
      NewTSapCb->bndRetryCnt = 0;
      NewTSapCb->contEnt = 0xFF;




      NewTSapCb->ctrlHdr.elmId.elmnt = 3;
      NewTSapCb->ctrlHdr.msgType = 2;
      NewTSapCb->ctrlHdr.entId.ent = egCb.init.ent;
      NewTSapCb->ctrlHdr.entId.inst = egCb.init.inst;
      egCb.tSapCb = NewTSapCb;
      egCb.tSapCb->cfgDone = 1;




      (Void)cmMemset((U8 *)&NewTSapCb->sts, 0, sizeof(EgSapSts));


      egCmInitTimer (&NewTSapCb->bndTmr);
      cmInitTimers (NewTSapCb->timers,2);





      NewTSapCb->pst.srcProcId = egCb.init.procId;
      NewTSapCb->contEnt = 0x0E;
   }
   else if (egCb.tSapCb->cfgDone)
   {




     cmMemcpy((U8 *)&egCb.tSapCb->reCfg, (U8 *) (tSapReCfg),
               sizeof(EgTSapReCfg));

     { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2007); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(3); };

   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2011); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTServerCfg
(
EgTptSrvCfg *TSrvCfg,
CmStatus *status
)





{
   EgTptSrvCb *TSrvCb = 0L;
   EgTSapCb *TSapCb = 0L;
   EgUSapCb *USapCb = 0L;
   S16 ret = 0;

   EgIpCb *ipCb = 0L;
   CmTptAddr lclIpAddr;
   U32 portNmb = 0;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2056); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }


   cmMemset((U8*)&lclIpAddr, 0, sizeof(CmTptAddr));






   status->status = 0;
   status->reason = 0;
   if (egCb.tSapCb == 0L)

   {
      { if(status != 0L) { status->status = 1; status->reason = 56; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                         2095
      , 0x4, ((0 + 0) + 164), 0, (Txt *)"egTServerCfg(): TSapCb Cfg Not Done");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2095); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                          ;
   }
   TSapCb = egCb.tSapCb;
   if(TSrvCfg->tptSrvId >= egCb.genCfg.nmbSrvs)
   {
      { if(status != 0L) { status->status = 1; status->reason = 13; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                           2134
      , 0x4, ((0 + 0) + 168), 0, (Txt *)"egTServerCfg(): Invalid Tpt Server ID");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2134); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                            ;
   }
   else
   {






    if((ret = egMiFindSrvCb((EgTptSrvCfg *)TSrvCfg, (EgTptSrvCb *)TSrvCb)) != 0)
    {





       { if(status != 0L) { status->status = 1; status->reason = ret; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                                                      2152
       , 0x4, ((0 + 0) + 169), 0, (Txt *)"egTServerCfg(): egMiFindSrvCb Failed, Server Already Configured");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2152); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                                       ;
    }
   }





   TSrvCb = (EgTptSrvCb *) egAlloc((Size) sizeof(EgTptSrvCb));





   if (TSrvCb == 0L)
   {
     { if(status != 0L) { status->status = 1; status->reason = 4; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
     ,
                                                                            2169
     , 0x4, ((0 + 0) + 173), 0, (Txt *)"egTServerCfg(): Mem Alloc for TSrvCb Failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2169); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                             ;
   }





   TSrvCb->state = 2;

   TSrvCb->suConnId = TSrvCfg->tptSrvId;
   TSrvCb->spConnId = 0;





   (Void)cmMemcpy((U8 *)&TSrvCb->cfg, (const U8 *)TSrvCfg,
                  (U32)sizeof (EgTptSrvCfg));






   TSrvCb->opnSrvCurRetryCnt = TSrvCfg->opnSrvRetryCnt;






   egCmInitTimer (&TSrvCb->opnSrvTmrNode);





   TSrvCb->tSapCb = TSapCb;






   if ( (USapCb = egCb.egtSapLst[TSrvCfg->uSapId]) == 0L )
   {



       egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));

       { if(status != 0L) { status->status = 1; status->reason = 12; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                                                   2221
       , 0x4, ((0 + 0) + 176), 0, (Txt *)"egTServerCfg(): Not able to find the associated USAP");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2221); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                                    ;
   }



   USapCb->tSapCb = TSapCb;
   TSrvCb->uSapCb = USapCb;
   if(TSrvCfg->gtp_C_Or_U == 1)
   {
      if(TSrvCfg->tptAddr.type == 4)
      {
         portNmb = TSrvCfg->tptAddr.u.ipv4TptAddr.port;
         TSrvCfg->tptAddr.u.ipv4TptAddr.port = 0;
      }







      else
      {



          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = 0L;
          status->status = 1;
          status->reason = ret;
          { if(status != 0L) { status->status = 1; status->reason = 70; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
          ,
                                                                         2260
          , 0x4, ((0 + 0) + 180), 0, (Txt *)"egTServerCfg(): Invalid Ip address type");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2260); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                          ;
      }

      if(portNmb == 3386)
      {



          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = 0L;
          status->status = 1;
          status->reason = ret;
          { if(status != 0L) { status->status = 1; status->reason = 81; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
          ,
                                                                                             2273
          , 0x4, ((0 + 0) + 181), 0, (Txt *)"egTServerCfg(): Configuration of EGTPV1 port is not allowed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2273); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                                              ;
      }

      egCpyCmTptAddr(&lclIpAddr, &(TSrvCfg->tptAddr));
      lclIpAddr.u.ipv4TptAddr.port = 0;

      ret = cmHashListFind(&USapCb->ipCbHashList, (U8 *)&(lclIpAddr),
                                            sizeof(CmTptAddr),0,(U32 *)&ipCb);

      if(ret != 0)
      {



          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = 0L;
          status->status = 1;
            status->reason = ret;
          { if(status != 0L) { status->status = 1; status->reason = 71; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
          ,
                                                                                 2292
          , 0x4, ((0 + 0) + 182), 0, (Txt *)"egTServerCfg(): searching the Ip Address failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2292); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                                  ;
      }

      TSrvCb->portNum = portNmb;





      if(portNmb != 2152 && ipCb->dfltPort != 1)
      {



          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = 0L;
          status->status = 1;
            status->reason = ret;
          { if(status != 0L) { status->status = 1; status->reason = 78; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
          ,
                                                                                           2311
          , 0x4, ((0 + 0) + 183), 0, (Txt *)"egTServerCfg(): Default port is not configured on this IP");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2311); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                                            ;
      }
      else if(portNmb == 2152)
      {
         TSrvCb->isdftlTptSrv = 1;
         ipCb->dfltPort = 1;
      }






      ret = cmHashListInsert(&(ipCb->tptServCbLst), (U32)TSrvCb,
                              (U8 *)&(TSrvCb->portNum), sizeof(U16));




      if(ret != 0)
      {



          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = 0L;
          status->status = 1;
            status->reason = ret;
          { if(status != 0L) { status->status = 1; status->reason = 72; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
          ,
                                                                                              2340
          , 0x4, ((0 + 0) + 184), 0, (Txt *)"egTServerCfg(): Insertion of TPT address CB into IPCB failed");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2340); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                                               ;
          { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2341); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
      }
      TSrvCb->ipCbPtr = ipCb;
      TSrvCb->portStatus = 1;
   }






   TSapCb->tptSrvCbLst[TSrvCb->suConnId] = TSrvCb;






   TSapCb->numSrvr++;







   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2367); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };

}
 S16 EgMiLegCntrlReq
(
Pst *pst,
EgMngmt *cntrlReq
)





{
   S16 retValue = 0;
   Pst cfmPst;
   EgMngmt cntrlCfm;





   U8 sendCfm = 1;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2413); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }
   { if ((&(egCb.init))->dbgMask & (0x00000002)) { snprintf((&(egCb.init))->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Eg", (&(egCb.init))->procId, (&(egCb.init))->ent, (&(egCb.init))->inst,
                                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
   ,
                                                                             2433
   ); SPrint((&(egCb.init))->prntBuf); sprintf (egCb.init.prntBuf, "EgMiLegCntrlReq (pst, elmId (%d))\n", cntrlReq->hdr.elmId.elmnt); SPrint((&(egCb.init))->prntBuf); } }
                                                                              ;

   cmMemset( (U8* )&cntrlCfm, 0, sizeof(EgMngmt));

   egMiFillResponsePost(&cfmPst, pst, &cntrlReq->hdr);




   if ( (!egCb.init.cfgDone) &&
         (cntrlReq->u.cntrl.action != 36))
   {
      SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                              2446
      , 0x4, ((0 + 0) + 186), 0, (Txt *)"EgMiLegCntrlReq: General configuration not done ");
                                                               ;




      cntrlCfm.cfm.status = 1;
      cntrlCfm.cfm.reason = 8;




      egSendLmCfm(&cfmPst, &cntrlReq->hdr, 2, &cntrlCfm);

      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2459); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
   }




   switch (cntrlReq->hdr.elmId.elmnt)
   {
      case 1:
         {



            retValue = egGenCntrl(cntrlReq);
            break;
         }

      case 2:
         {



            retValue = egUSapCntrl(cntrlReq);
            break;
         }

      case 3:
         {
            if(egCb.tSapCb)
               cmMemcpy((U8 *)&egCb.tSapCb->cfmPst, (U8 *)&cfmPst,
                     sizeof(Pst));


            retValue = egTSapCntrl(cntrlReq);
            break;
         }

      case 4:
         {



            retValue = egTServerCntrl(cntrlReq);
            break;
         }


      case 8:
         {



            retValue = egIpAddrCntrl(cntrlReq);
            break;
         }


      default:
         {
            SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                  2542
            , 0x4, ((0 + 0) + 190), 0, (Txt *)"EgMiLegCntrlReq: invalid elmnt");
                                                   ;

            retValue = 5;
            break;
         }
   }




   if(retValue == 0)
   {
      cntrlCfm.cfm.status = 0;




      if(cntrlReq->hdr.elmId.elmnt == 3 &&
            cntrlReq->u.cntrl.action == 21)
      {
         if((0L != egCb.tSapCb)&&(egCb.tSapCb->state != 2))
         {
            cntrlCfm.cfm.status = 2;
         }
         else
         {
            sendCfm = 0;
         }
      }
   }
   else
   {
      cntrlCfm.cfm.status = 1;
   }
   cntrlCfm.cfm.reason = retValue;
   if(1 == sendCfm)
   {
      egSendLmCfm(&cfmPst, &cntrlReq->hdr, 2, &cntrlCfm);
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2598); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egGenCntrl
(
EgMngmt *genCntrl
)




{
   S16 retValue = 0;
   CmStatus *Cfm = 0L;




   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2635); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }





   switch (genCntrl->u.cntrl.action)
   {



      case 1:
         {
            switch (genCntrl->u.cntrl.subAction)
            {
               case 3:
                  {



                     egCb.init.usta = 1;





                     break;
                  }

               case 5:
                  {



                     { if(1 == 2) { egCb.init.dbgMask &= ~(genCntrl->u.cntrl.s.dbgCntrl.genDbgMask); } else if(1 == 1) { egCb.init.dbgMask |= genCntrl->u.cntrl.s.dbgCntrl.genDbgMask; } }
                        break;
                  }

               case 4:
                  {
                     if(egCb.tSapCb == 0L)

                     {
                        { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                        ,
                                                                                       2701
                        , 0x4, ((0 + 0) + 191), 0, (Txt *)"egGenCntrl(): TSAP not configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2701); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                                        ;
                     }
                     egCb.tSapCb->trcMask |= genCntrl->u.cntrl.s.trcCntrl.trcMask;

                     egCb.tSapCb->trcLen = genCntrl->u.cntrl.s.trcCntrl.trcLen;
                     break;
                  }
               default:
                  {
                     { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                     ,
                                                                                  2740
                     , 0x4, ((0 + 0) + 192), 0, (Txt *)"egGenCntrl(): Invalid Subaction");; if(10 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2740); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(10); }; } }
                                                                                   ;
                  }
            }
            break;
         }




      case 2:
         {
            switch (genCntrl->u.cntrl.subAction)
            {
               case 3:
                  {



                     egCb.init.usta = 0;





                     break;
                  }

               case 5:
                  {



                     { if(2 == 2) { egCb.init.dbgMask &= ~(genCntrl->u.cntrl.s.dbgCntrl.genDbgMask); } else if(2 == 1) { egCb.init.dbgMask |= genCntrl->u.cntrl.s.dbgCntrl.genDbgMask; } }
                        break;
                  }

               case 4:
                  {
                     if(egCb.tSapCb == 0L)

                     {
                        { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                        ,
                                                                                       2803
                        , 0x4, ((0 + 0) + 193), 0, (Txt *)"egGenCntrl(): TSAP not configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2803); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                                        ;
                     }







                     egCb.tSapCb->trcMask &= ~(genCntrl->u.cntrl.s.trcCntrl.trcMask);
                     break;
                  }
               default:
                  {
                     { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                     ,
                                                                                  2838
                     , 0x4, ((0 + 0) + 194), 0, (Txt *)"egGenCntrl(): Invalid Subaction");; if(10 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2838); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(10); }; } }
                                                                                   ;
                  }
            }

            break;
         }

      case 36:
         {



            if ( (retValue = egShutdown()) != 0)
            {
               { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
               ,
                                                          2853
               , 0x4, ((0 + 0) + 195), 0, (Txt *)"egGenCntrl(): Layer shutdown Failed");; if(retValue != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2853); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); }; } }
                                                           ;
            }
            break;
         }

      default:
         {



            { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                        2864
            , 0x4, ((0 + 0) + 196), 0, (Txt *)"egGenCntrl(): Invalid Action");; if(9 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2864); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(9); }; } }
                                                         ;
         }
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2868); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egUSapCntrl
(
EgMngmt *uSapCntrl
)




{
   S16 retValue = 0;
   EgUSapCb *egUsapCb = 0L;
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2903); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   if ((uSapCntrl->u.cntrl.s.sap.sapId < (1 -1))||
       (uSapCntrl->u.cntrl.s.sap.sapId >= egCb.genCfg.nmbUSaps))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                          2912
      , 0x4, ((0 + 0) + 197), 0, (Txt *)"egUSapCntrl(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2912); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                           ;
   }




   if ( (egUsapCb = egCb.egtSapLst[uSapCntrl->u.cntrl.s.sap.sapId]) == 0L)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                2921
      , 0x4, ((0 + 0) + 198), 0, (Txt *)"egUSapCntrl(): USap Not Configured");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2921); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                                 ;
   }





   if ( (retValue = egMiRmvEchoCb(egUsapCb, 0L, 0L, 0L, 1)) != 0)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                      2931
      , 0x4, ((0 + 0) + 199), 0, (Txt *)"egUSapCntrl, Failed to remove echo Cb's");; if(retValue != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2931); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); }; } }
                                                       ;
   }




   switch (uSapCntrl->u.cntrl.action)
   {
      case 31:
      {
         if(egUsapCb->state != 3)
         {
            {

                if((retValue = egMiIpCbDeInit(&egUsapCb->ipCbHashList, 0)) != 0)
               {
                  { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                  ,
                                                                              2948
                  , 0x4, ((0 + 0) + 201), 0, (Txt *)"egUSapCntrl, Failed to disable the layer manager SAP");; if(retValue != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2948); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); }; } }
                                                                               ;
               }

               egUsapCb->state = 1;

            }
          }







          break;
      }

      case 7:
      {



         if ( (retValue = egMiDelUsap(egUsapCb)) != 0)
         {
             { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
             ,
                                                                        2973
             , 0x4, ((0 + 0) + 202), 0, (Txt *)"egUSapCntrl, Failed to delete the layer manager SAP");; if(retValue != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2973); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); }; } }
                                                                         ;
         }





         { if ((&(egCb.init))->dbgMask & (0x00000002)) { snprintf((&(egCb.init))->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Eg", (&(egCb.init))->procId, (&(egCb.init))->ent, (&(egCb.init))->inst,
                                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                                      2981
         ); SPrint((&(egCb.init))->prntBuf); sprintf (egCb.init.prntBuf, "Deleted the Upper SAP (%d)\n", egUsapCb->cfg.sapId); SPrint((&(egCb.init))->prntBuf); } }
                                                                       ;






         break;
      }
      default:
      {



          { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
          ,
                                                     2996
          , 0x4, ((0 + 0) + 203), 0, (Txt *)"egUSapCntrl, Invalid Action");; if(9 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",2996); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(9); }; } }
                                                      ;
      }
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3000); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egMiDisableUsap
(
EgUSapCb *uSapCb
)




{
   CmStatus *Cfm = 0L;

   S16 retValue = 0;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3036); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   if (uSapCb == 0L)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                   3041
      , 0x4, ((0 + 0) + 204), 0, (Txt *)"egMiDisableUsap(): uSapCb is NULLP");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3041); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                                    ;
   }

   switch(uSapCb->state)
   {
      case 2:
      {






          if(uSapCb->cfg.flag == 1)
          {
            if((retValue = egMiIpCbDeInit(&uSapCb->ipCbHashList, 1)) != 0)
            {
               SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *) "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c", 3058, 0x4, ((0 + 0) + 205), 0, (Txt *)"egMiDisableUsap(): DeInitialization of IpCb failed");;
                { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3059); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
            }
            cmHashListDeinit(&(uSapCb->ipCbHashList));
          }




         uSapCb->state = 3;
         { if ((&(egCb.init))->dbgMask & (0x00000002)) { snprintf((&(egCb.init))->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Eg", (&(egCb.init))->procId, (&(egCb.init))->ent, (&(egCb.init))->inst,
                                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                                         3078
         ); SPrint((&(egCb.init))->prntBuf); sprintf (egCb.init.prntBuf, "Disabled SAP: USAP UNBOUND (%d)\n", uSapCb->cfg.sapId); SPrint((&(egCb.init))->prntBuf); } }
                                                                          ;
         break;
      }
      case 1:

      case 3:

      {






          if(uSapCb->cfg.flag == 1)
          {
            if((retValue = egMiIpCbDeInit(&uSapCb->ipCbHashList, 1)) != 0)
            {
               SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *) "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c", 3096, 0x4, ((0 + 0) + 206), 0, (Txt *)"egMiDisableUsap(): DeInitialization of IpCb failed");;
                { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3097); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
            }
            cmHashListDeinit(&(uSapCb->ipCbHashList));
          }

            break;
      }
      default:
      {



            { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                            3110
            , 0x4, ((0 + 0) + 207), 0, (Txt *)"egMiDisableUsap(): Invalid State");; if(11 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3110); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(11); }; } }
                                                             ;
            { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3111); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); };
      }

   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3116); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egMiDelUsap
(
EgUSapCb *uSapCb
)




{
   S16 retValue = 0;
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3147); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   if (uSapCb == 0L)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                          3155
      , 0x4, ((0 + 0) + 208), 0, (Txt *)"egMiDelUsap, uSapCb is NULLP");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3155); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                           ;
   }




   if(uSapCb->state != 3)
   {
      if((retValue = egMiDisableUsap(uSapCb)) != 0)
      {
        { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
        ,
                                                                      3166
        , 0x4, ((0 + 0) + 209), 0, (Txt *)"egMiDelUsap, Disabling and unbinding SAP failed");; if(retValue != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3166); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); }; } }
                                                                       ;
      }
   }
   egCb.egtSapLst[uSapCb->cfg.sapId] = 0L;
   retValue = egFree( (Data* )uSapCb, sizeof(EgUSapCb));
   uSapCb = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3182); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTSapCntrl
(
EgMngmt *tSapCntrl
)




{
   S16 retValue = 0;
   Action action;
   EgTSapCb *tSapCb = 0L;
   CmStatus *Cfm = 0L;




   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3220); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   action = tSapCntrl->u.cntrl.action;




   tSapCb = egCb.tSapCb;





   if (tSapCb == 0L)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                3236
      , 0x4, ((0 + 0) + 210), 0, (Txt *)"egTSapCntrl(): TSap Not Configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3236); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                 ;
   }


   tSapCb->ctrlHdr.transId = tSapCntrl->hdr.transId;
   tSapCb->ctrlHdr.entId.ent = tSapCntrl->hdr.entId.ent;
   tSapCb->ctrlHdr.entId.inst = tSapCntrl->hdr.entId.inst;
   tSapCb->ctrlHdr.elmId.elmnt = tSapCntrl->hdr.elmId.elmnt;

   switch (action)
   {
      case 21:
         {



            if ((tSapCb->state == 2) ||
                  (tSapCb->state == 5))
            {
               { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3255); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
            }
            tSapCb->state = 5;
            tSapCb->contEnt = 0xFF;

            egLiPrcBndCfm(tSapCb->suId,tSapCb,1);
            break;
         }

      case 31:
         {



            if (tSapCb->state != 1)
            {
               retValue = egUnbindNDisableTSap(tSapCb, 0);
            }




            break;
         }

      case 7:
         {



            if (tSapCb->state != 1)
            {
               retValue = egUnbindNDisableTSap(tSapCb, 0);
            }
            retValue = egFree((Data *)tSapCb, sizeof(EgTSapCb));
            egCb.tSapCb = 0L;
            break;
         }

      default:
         {



            { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                         3339
            , 0x4, ((0 + 0) + 211), 0, (Txt *)"egTSapCntrl(): Invalid Action");; if(9 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3339); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(9); }; } }
                                                          ;
         }
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3343); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
}
static S16 egUnbindNDisableTSap
(
EgTSapCb *tSapCb,
Bool ShutDownFlg
)





{
   S16 retValue = 0;




   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3379); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }
   if(ShutDownFlg == 0)
   {



     (Void) egTptProcessTsapServers(tSapCb, EG_TPT_TPTSRV_FREE);




      retValue = egFree((Data *)tSapCb->tptSrvCbLst,
                     (Size) (egCb.genCfg.nmbSrvs * sizeof(U32)));



      egCb.tSapCb->tptSrvCbLst = 0L;


   }



   tSapCb->state = 1;
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3443); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTServerCntrl
(
EgMngmt *tSrvrCntrl
)




{
   S16 retVal = 0;
   S16 idx = 0;
   Action action;
   EgTptSrvCb *tSrvCb = 0L;

   EgTptSrvCb *tempSrvCb = 0L;

   CmStatus *Cfm = 0L;





   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3485); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   action = tSrvrCntrl->u.cntrl.action;
   if (!egCb.tSapCb)

   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                   3517
      , 0x4, ((0 + 0) + 212), 0, (Txt *)"egTServerCntrl(): TSap Not Configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3517); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                    ;
   }





   if(tSrvrCntrl->u.cntrl.s.server.type == 1)
   {
     idx = tSrvrCntrl->u.cntrl.s.server.t.tptSrvId;
     if(idx < egCb.genCfg.nmbSrvs)
     {



       tSrvCb = egCb.tSapCb->tptSrvCbLst[idx];

     }
   }
   else if(tSrvrCntrl->u.cntrl.s.server.type == 2)
   {




     for (idx=0; idx < egCb.genCfg.nmbSrvs; idx++)
     {



        if ((tSrvCb = egCb.tSapCb->tptSrvCbLst[idx]) != 0L)

        {



           if (tSrvrCntrl->u.cntrl.s.server.t.tptAddr.type == 4)
           {
              if ((tSrvCb->cfg.tptAddr.u.ipv4TptAddr.port ==
                       tSrvrCntrl->u.cntrl.s.server.t.tptAddr.u.ipv4TptAddr.port) &&
                    (tSrvCb->cfg.tptAddr.u.ipv4TptAddr.address ==
                     tSrvrCntrl->u.cntrl.s.server.t.tptAddr.u.ipv4TptAddr.address))
                 break;
           }
        }
     }
   }




   if ((idx >= egCb.genCfg.nmbSrvs) || (tSrvCb == 0L))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                     3580
      , 0x4, ((0 + 0) + 213), 0, (Txt *)"egTServerCntrl(): Invalid TPT Server");; if(59 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3580); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(59); }; } }
                                                                      ;
   }

   switch(action)
   {

      case 1:
         {



            retVal = egTptOpenServer (tSrvCb, 0L);

            if (retVal != 0)
            {
               { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
               ,
                                                                                  3596
               , 0x4, ((0 + 0) + 214), 0, (Txt *)"egTServerCntrl(): Could not init server instance \n");; if(59 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3596); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(59); }; } }
                                                                                   ;
            }
            break;
         }

      case 7:
         {

              if(tSrvCb->cfg.gtp_C_Or_U == 1)
            {
               retVal = egMiRmvEchoCb (0L, 0L, tSrvCb, 0L, 4);

               if (retVal != 0)
               {
                  { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                  ,
                                                                                     3611
                  , 0x4, ((0 + 0) + 215), 0, (Txt *)"egTServerCntrl(): Could not init server instance \n");; if(59 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3611); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(59); }; } }
                                                                                      ;
               }



                if((0 != (retVal = cmHashListFind(&(tSrvCb->ipCbPtr->tptServCbLst), (U8 *)&(tSrvCb->portNum),
                                             sizeof(U16),0,(U32 *)&tempSrvCb))) && tempSrvCb != tSrvCb)
                {
                       SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                       ,
                                                                                                3620
                       , 0x4, ((0 + 0) + 216), 0, (Txt *)"egTServerCntrl(): Failed to find the tpt server from IpCb hashList");
                                                                                                 ;
                }
                 else
                {
                  if ( (retVal = cmHashListDelete(&(tSrvCb->ipCbPtr->tptServCbLst), (U32)tempSrvCb)) != 0)
                  {
                        SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                        ,
                                                                                                           3627
                        , 0x4, ((0 + 0) + 217), 0, (Txt *)"egTServerCntrl(): Failed to delete tpt server Control block from hash list");
                                                                                                            ;
                  }
                }
             }






            if (tSrvCb->state != 2)
            {



               (Void) egTptCloseServer (tSrvCb);
            }
            egTptFreeServer(tSrvCb);







            egCb.tSapCb->tptSrvCbLst[idx] = 0L;

            break;
         }

      default:
         {
            { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                            3670
            , 0x4, ((0 + 0) + 218), 0, (Txt *)"egTServerCntrl(): Invalid action");; if(9 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3670); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(9); }; } }
                                                             ;
         }
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3674); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retVal); };
}
 S16 egShutdown
(
  Void
)



{
   S16 retValue = 0;
   S16 idx;





EgUEchoReqCb *echoReqCb = 0L;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3710); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }





   if (!egCb.init.cfgDone)
   {
      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3718); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
   }




   if (egCb.shutdown)
   {
      { if ((&(egCb.init))->dbgMask & (0x00000002)) { snprintf((&(egCb.init))->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Eg", (&(egCb.init))->procId, (&(egCb.init))->ent, (&(egCb.init))->inst, "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c", 3726); SPrint((&(egCb.init))->prntBuf); sprintf (egCb.init.prntBuf, "Layer Already SHUTDOWN\n"); SPrint((&(egCb.init))->prntBuf); } };

      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3728); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
   }

   egCb.shutdown = 1;



   egSchedTmr((U32) 0L, 5, 2, egCb.genCfg.echoTmr.val);
   retValue = egCpmDeinit();
   if(egCb.tSapCb != 0L)
   {




      egFree((Data *)egCb.tSapCb->tptSrvCbLst,
               (Size) (egCb.genCfg.nmbSrvs * sizeof(U32)));
      egCb.tSapCb->tptSrvCbLst = 0L;
      if(egCb.tSapCb->state != 1)
         {




         retValue = egUnbindNDisableTSap(egCb.tSapCb, 1);
         }







         retValue = egFree((Data *)egCb.tSapCb, sizeof(EgTSapCb));




         egCb.tSapCb = 0L;

      }





   for (idx = 0; idx < egCb.genCfg.nmbUSaps; idx++)
   {



      if (egCb.egtSapLst[idx] == 0L)
      {
          continue;
      }




       retValue = egMiDisableUsap(egCb.egtSapLst[idx]);




       retValue = egFree((Data *)egCb.egtSapLst[idx], sizeof(EgUSapCb));




      egCb.egtSapLst[idx] = 0L;
   }


   cmHashListDeinit(&(egCb.egTeidHashListCp));

   for(;((retValue = cmHashListGetNext(&(egCb.egUCb.echoReqHashList), (U32)0L, (U32*)&echoReqCb)) == 0);)
   {
      cmHashListDelete(&(egCb.egUCb.echoReqHashList), (U32)echoReqCb);
      { if (echoReqCb->echoReqBuff != (Buffer*) 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3856); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 2, 2,(Void*)echoReqCb->echoReqBuff, (U32)0 ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void)SPutMsg(echoReqCb->echoReqBuff); echoReqCb->echoReqBuff = 0L; } };
      { if (echoReqCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3857); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)echoReqCb, (U32)sizeof(EgUEchoReqCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) echoReqCb, (Size) sizeof(EgUEchoReqCb)); (echoReqCb) = 0L; }};
      echoReqCb = 0L;
   }
   cmHashListDeinit(&(egCb.egUCb.echoReqHashList));





   retValue = egFree((Data *)egCb.egtSapLst,
                     (Size)(egCb.genCfg.nmbUSaps * sizeof(U32)));





   SPutSMem(egCb.init.region, egCb.init.pool);
   egCb.init.cfgDone = 0;

   egCb.init.usta = 0;

   egCb.init.dbgMask = 0;

   egCb.init.acnt = 0;
   egCb.init.trc = 0;




   SDeregCfgTmr(egCb.init.ent,egCb.init.inst,egCb.genCfg.timerRes,100,egActvTmr);
   egActvInit (egCb.init.ent, egCb.init.inst,
               egCb.init.region, egCb.init.reason);
   EgTLThShutdownReq();

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3915); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
}
 S16 EgMiLegStaReq
(
Pst *pst,
EgMngmt *staReq
)





{
   S16 retValue;
   EgMngmt staCfm;
   Pst cfmPst;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3953); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }
   { if ((&(egCb.init))->dbgMask & (0x00000002)) { snprintf((&(egCb.init))->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Eg", (&(egCb.init))->procId, (&(egCb.init))->ent, (&(egCb.init))->inst,
                                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
   ,
                                                                      3974
   ); SPrint((&(egCb.init))->prntBuf); sprintf (egCb.init.prntBuf, "EgMiLegStaReq (pst, elmId (%d))\n", staReq->hdr.elmId.elmnt); SPrint((&(egCb.init))->prntBuf); } }
                                                                       ;

   cmMemset( (U8* )&staCfm, 0, sizeof(EgMngmt));
   egMiFillResponsePost(&cfmPst, pst, &staReq->hdr);




   if (!egCb.init.cfgDone)
   {
      SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                 3985
      , 0x4, ((0 + 0) + 221), 0, (Txt *)"EgMiLegStaReq: General configuration not done ");
                                                                  ;




      staCfm.cfm.status = 1;
      staCfm.cfm.reason = 8;




      egSendLmCfm(&cfmPst, &staReq->hdr, 4, &staCfm);

      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",3998); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
   }

   switch (staReq->hdr.elmId.elmnt)
   {
      case 1:
      {



         retValue = egGenStaReq(staReq, &staCfm);
         break;
      }

      case 7:
      {



         retValue = egGetSId(&staCfm.u.ssta.s.sysId);
         if(retValue == 1)
             retValue = 0;
         break;
      }

      case 2:
      {



         retValue = egUSapStaReq(staReq, &staCfm);
         break;
      }

      case 3:
      {



         retValue = egTSapStaReq(staReq, &staCfm);
         break;
      }


      case 4:
      {



         retValue = egTptSrvStaReq(staReq, &staCfm);
         break;
      }

      case 10:
      {



         retValue = egTnlStaReq(staReq, &staCfm);
         break;
      }


      default:
      {
         SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                  4064
         , 0x4, ((0 + 0) + 222), 0, (Txt *)"EgMiLegStaReq: Invalid elmnt");
                                                   ;

         retValue = 5;
         break;
      }
   }




    if(retValue == 0)
    {
       staCfm.cfm.status = 0;
    }
    else
    {
       staCfm.cfm.status = 1;
    }
    staCfm.cfm.reason = retValue;




   egSendLmCfm(&cfmPst, &staReq->hdr, 4, &staCfm);

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4089); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTptSrvStaReq
(
EgMngmt *staReq,
EgMngmt *staCfm
)





{
   CmStatus *Cfm = 0L;
   ConnId tSrvId = staReq->u.ssta.s.tSrvrSta.tptSrvId;
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4142); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }







   if (!egCb.tSapCb)

   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                   4154
      , 0x4, ((0 + 0) + 223), 0, (Txt *)"egTptSrvStaReq(): TSap not configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4154); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                    ;
   }






   if((tSrvId >= egCb.genCfg.nmbSrvs) || (egCb.tSapCb->tptSrvCbLst[tSrvId] == 0L))

   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                             4166
      , 0x4, ((0 + 0) + 224), 0, (Txt *)"egTptSrvStaReq(): Invalid Tpt Server ID");; if(13 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4166); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(13); }; } }
                                                              ;
   }
   staCfm->u.ssta.s.tSrvrSta.state = egCb.tSapCb->tptSrvCbLst[tSrvId]->state;
   staCfm->u.ssta.s.tSrvrSta.status = egCb.tSapCb->tptSrvCbLst[tSrvId]->portStatus;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4180); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTnlStaReq
(
EgMngmt *staReq,
EgMngmt *staCfm
)





{
   SpId sapId;
   EgIpCb *ipCb = 0L;
   EgDestAddrCb *destAddrCb = 0L;
   EgTeIdCb *teIdCb = 0L;
   CmTptAddr destAddr;
   CmTptAddr srcAddr;
   CmStatus *Cfm = 0L;
   U32 teId = 0;
   S16 retVal = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4221); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   teId = staReq->u.ssta.s.tnlSta.teId;
   sapId = staReq->u.ssta.s.tnlSta.spId;
   cmMemset((U8*)&destAddr, 0 , sizeof(CmTptAddr));
   cmMemset((U8*)&srcAddr, 0 , sizeof(CmTptAddr));

   egCpyCmTptAddr(&(srcAddr), &(staReq->u.ssta.s.tnlSta.srcIpAddr));
   egCpyCmTptAddr(&(destAddr), &(staReq->u.ssta.s.tnlSta.destIpAddr));




   if((sapId >= (SpId)100) || (sapId < 0)
                           || (egCb.egtSapLst[sapId] == (EgUSapCb *)0L))
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                  4238
       , 0x4, ((0 + 0) + 225), 0, (Txt *)"egTnlStaReq(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4238); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                   ;
   }

   if(0 != (retVal = cmHashListFind(&(egCb.egtSapLst[sapId]->ipCbHashList), (U8 *)&srcAddr,
                                         sizeof(CmTptAddr),0,(U32 *)&ipCb)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                       4245
      , 0x4, ((0 + 0) + 226), 0, (Txt *)"egTnlStaReq(): Finding the IpCb from the hash list failed");; if(71 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4245); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(71); }; } }
                                                                                        ;
   }

   if(0 != (retVal = cmHashListFind(&(ipCb->destAddrCbLst), (U8 *)&destAddr,
                                         sizeof(CmTptAddr),0,(U32 *)&destAddrCb)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                             4252
      , 0x4, ((0 + 0) + 227), 0, (Txt *)"egTnlStaReq(): Finding the destAddrCb from the hash list failed");; if(76 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4252); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(76); }; } }
                                                                                              ;
   }

   if(0 != (retVal = cmHashListFind(&(destAddrCb->teIdLst), (U8 *)&teId,
                                         sizeof(U32),0,(U32 *)&teIdCb)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                       4259
      , 0x4, ((0 + 0) + 228), 0, (Txt *)"egTnlStaReq(): Finding the teId from the hash list failed");; if(77 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4259); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(77); }; } }
                                                                                        ;
   }


   staCfm->u.ssta.s.tnlSta.reOrderPrsnt = teIdCb->reOrdering;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4265); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egUSapStaReq
(
EgMngmt *staReq,
EgMngmt *staCfm
)





{
   SpId sapId;
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4300); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   sapId = staReq->u.ssta.s.uSapSta.uSapId;




   if ((sapId < (1 -1)) || (sapId >= egCb.genCfg.nmbUSaps))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                           4310
      , 0x4, ((0 + 0) + 229), 0, (Txt *)"egUSapStaReq(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4310); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                            ;
   }




   if(egCb.egtSapLst[sapId] == 0L)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                 4319
      , 0x4, ((0 + 0) + 230), 0, (Txt *)"egUSapStaReq(): USap not configured");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4319); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                                  ;
   }




   staCfm->u.ssta.s.uSapSta.state = egCb.egtSapLst[sapId]->state;
   staCfm->u.ssta.s.uSapSta.uSapId = sapId;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4328); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTSapStaReq
(
EgMngmt *staReq,
EgMngmt *staCfm
)





{
   CmStatus *Cfm = 0L;
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4371); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }
   if (!egCb.tSapCb)

   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                 4393
      , 0x4, ((0 + 0) + 231), 0, (Txt *)"egTSapStaReq(): TSap not configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4393); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                  ;
   }
   staCfm->u.ssta.s.tSapSta.state = egCb.tSapCb->state;
   staCfm->u.ssta.s.tSapSta.tSapId = egCb.tSapCb->spId;
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4416); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egGenStaReq
(
EgMngmt *staReq,
EgMngmt *staCfm
)





{
   Status memStatus = 0;
   S16 retVal = 0;
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4450); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   if ( (retVal = SChkRes(egCb.init.region, egCb.init.pool, &memStatus)) != 0)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                    4458
      , 0x4, ((0 + 0) + 232), 0, (Txt *)"egGenStaReq: Getting Memory Statistics Failed ");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4458); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                     ;
   }

   staCfm->u.ssta.s.genSta.resCong = 0;






   if (memStatus <= egCb.genCfg.resThreshLower)
   {
     staCfm->u.ssta.s.genSta.resCong = 1;
   }





   staCfm->u.ssta.s.genSta.memSize = egCb.genSta.memSize;
   staCfm->u.ssta.s.genSta.memAlloc = egCb.genSta.memAlloc;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4480); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
 S16 EgMiLegStsReq
(
Pst *pst,
Action action,
EgMngmt *stsReq
)






{
   S16 retValue = 0;
   EgMngmt stsCfm;
   Pst cfmPst;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4520); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }
   cmMemset( (U8* )&stsCfm, 0, sizeof(EgMngmt));
   egMiFillResponsePost(&cfmPst, pst, &stsReq->hdr);




   if (!egCb.init.cfgDone)
   {
      SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                 4549
      , 0x4, ((0 + 0) + 234), 0, (Txt *)"EgMiLegStsReq: General configuration not done ");
                                                                  ;




      stsCfm.cfm.status = 1;
      stsCfm.cfm.reason = 8;




      egSendLmCfm(&cfmPst, &stsReq->hdr, 3, &stsCfm);

      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4562); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
   }

   { if ((&(egCb.init))->dbgMask & (0x00000002)) { snprintf((&(egCb.init))->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "Eg", (&(egCb.init))->procId, (&(egCb.init))->ent, (&(egCb.init))->inst,
                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
   ,
                                                                       4566
   ); SPrint((&(egCb.init))->prntBuf); sprintf (egCb.init.prntBuf, "EgMiLegStsReq (pst, elmId (%d))\n", stsReq->hdr.elmId.elmnt); SPrint((&(egCb.init))->prntBuf); } }
                                                                        ;

   switch (stsReq->hdr.elmId.elmnt)
   {
      case 1:
         {



            retValue = egGenStsReq(stsReq, action, &stsCfm);
            break;
         }

      case 2:
         {



            retValue = egUSapStsReq(stsReq, action, &stsCfm);
            break;
         }

      case 3:
         {



            retValue = egTSapStsReq(stsReq, action, &stsCfm);
            break;
         }


      case 4:
         {



            retValue = egSrvrStsReq(stsReq, action, &stsCfm);
            break;
         }

      case 8:
         {



            retValue = egIpAddrStsReq(stsReq, action, &stsCfm);
            break;
         }

      case 10:
         {



            retValue = egTnlStsReq(stsReq, action, &stsCfm);
            break;
         }

      default:
         {
            SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                4628
            , 0x4, ((0 + 0) + 235), 0, (Txt *)"EgMiLegStsReq: Invalid elmnt");
                                                 ;

            retValue = 5;
            break;
         }
   }




   if(retValue == 0)
   {
      stsCfm.cfm.status = 0;
   }
   else
   {
      stsCfm.cfm.status = 1;
   }
   stsCfm.cfm.reason = retValue;




   egSendLmCfm(&cfmPst, &stsReq->hdr, 3, &stsCfm);

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4653); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egGenStsReq
(
EgMngmt *stsReq,
Action action,
EgMngmt *stsCfm
)






{
   U32 wrkThrdCnt;
   U16 cnt = 0;
   EgErrSts tmpErrSts;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4689); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

      wrkThrdCnt = 0;

   for(cnt=0; cnt < egCb.genCfg.nmbUSaps; cnt++)
   {
      if(egCb.egtSapLst[cnt] != 0L)
      {
         egCb.genSts.numTxMsg = egCb.genSts.numTxMsg + egCb.egtSapLst[cnt]->sts.totalMsgsTx;
         egCb.genSts.numRxMsg = egCb.genSts.numRxMsg + egCb.egtSapLst[cnt]->sts.totalMsgsRx;
      }
   }




      (Void) cmMemcpy((U8 *)&stsCfm->u.sts.s.gen, (U8 *) &egCb.genSts,
                      (U32) sizeof(EgGenSts));
      (Void) cmMemset((U8 *)&tmpErrSts, 0, sizeof(EgErrSts));


   if (action == 0)




       (Void)cmMemset((U8 *) &egCb.genSts, '\0', sizeof(EgGenSts));

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4717); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egUSapStsReq
(
EgMngmt *stsReq,
Action action,
EgMngmt *stsCfm
)






{
   SpId sapId;
   EgUSapCb *uSapCb;
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4756); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   sapId = stsReq->u.sts.s.usap.sapId;




   if((sapId >= (SpId)egCb.genCfg.nmbUSaps) || (sapId < (1 -1)))
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                   4766
       , 0x4, ((0 + 0) + 236), 0, (Txt *)"egUSapStsReq(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4766); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                    ;
   }




   if((uSapCb = egCb.egtSapLst[sapId]) == 0L)
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                         4775
       , 0x4, ((0 + 0) + 237), 0, (Txt *)"egUSapStsReq(): USap not configured");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4775); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                          ;
   }




   cmMemcpy((U8 *) &stsCfm->u.sts.s.usap, (U8 *) &uSapCb->sts,
            sizeof(EgSapSts));

   if (action == 0)
   {



        cmMemset((Data *) &uSapCb->sts, '\0', sizeof(EgSapSts));
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4792); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTSapStsReq
(
EgMngmt *stsReq,
Action action,
EgMngmt *stsCfm
)






{
   SpId sapId;
   EgTSapCb *TSapCb;
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4827); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   sapId = stsReq->u.sts.s.tsap.sapId;







   if((sapId > (SpId)1) || (sapId < 0))
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                   4840
       , 0x4, ((0 + 0) + 238), 0, (Txt *)"egTSapStsReq(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4840); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                    ;
   }
   TSapCb = egCb.tSapCb;


   if (!TSapCb)
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                 4856
      , 0x4, ((0 + 0) + 239), 0, (Txt *)"egTSapStsReq(): TSap not configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4856); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                  ;
   }



   if((TSapCb = (EgTSapCb *)&egCb.tSapCb[sapId]) == 0L)
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                                  4864
       , 0x4, ((0 + 0) + 240), 0, (Txt *)"egTSapStsReq(): TSap not configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4864); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                   ;
   }




   cmMemcpy((U8 *) &stsCfm->u.sts.s.tsap, (U8 *) &TSapCb->sts,
            sizeof(EgSapSts));

   if (action == 0)
   {



        cmMemset((Data *) &TSapCb->sts, '\0', sizeof(EgSapSts));
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4881); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
 S16 egSendLmAlarm
(
U16 category,
U16 event,
U16 cause,
EgUstaDgn *dgn
)







{
   EgMngmt uSta;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4919); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   if (!egCb.init.usta)
   {
      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4926); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
   }




   (void) cmMemset( (U8* )&uSta, 0, sizeof(EgMngmt));

   SGetDateTime(&uSta.u.usta.dt);

   uSta.hdr.elmId.elmnt = 1;
   uSta.hdr.msgType = 5;
   uSta.hdr.entId.ent = egCb.init.ent;
   uSta.hdr.entId.inst = egCb.init.inst;




   cmMemcpy( (U8* )&uSta.u.usta.dgn, (U8* ) dgn, sizeof(EgUstaDgn));

   uSta.u.usta.alarm.category = category;
   uSta.u.usta.alarm.event = event;
   uSta.u.usta.alarm.cause = cause;




   EgMiLegStaInd(&egCb.init.lmPst, &uSta);

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",4955); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
 Void egGenTrcInd
(
EgTSapCb *tSapCb,
S16 elmnt,
CmTptAddr *srcAddr,
CmTptAddr *destAddr,
U16 evnt,
Buffer *mBuf
)
{
   S16 retValue = 0;
   MsgLen bufLen = 0;




   EgMngmt trc;
   Buffer *trcBuf=0L;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5004); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   if (egCb.init.cfgDone == 0)
   {
      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5011); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
   }





   if (elmnt == 2)
   {




      if ((tSapCb == 0L) || (tSapCb->trcLen == 0))
      {




         { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5030); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
      }

      SFndLenMsg(mBuf, &bufLen);




      if ((tSapCb->trcLen != -1) && (tSapCb->trcLen < bufLen))
      {
         bufLen = tSapCb->trcLen;
      }





      trc.hdr.elmId.elmnt = elmnt;

      trc.u.trc.evnt = evnt;
      trc.u.trc.length = bufLen;
      trc.u.trc.srcAddr = srcAddr;
      trc.u.trc.remAddr = destAddr;
           SCpyMsgMsg(mBuf, egCb.init.region, egCb.init.pool, &trcBuf);
           if (retValue != 0)
           {



             (Void)SPutMsg(trcBuf);
             { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5090); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
           }






       (Void)SGetDateTime(&trc.u.trc.dt);




       EgMiLegTrcInd(&egCb.init.lmPst, &trc, trcBuf);
   }

      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5106); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
}
 S16 egSendLmCfm
(
Pst *egPst,
Header *hdr,
U8 type,
EgMngmt *cfm
)







{
   CmStatus *Cfm= 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5141); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; };




   cmMemset( (U8 *)&cfm->hdr, '\0', sizeof(cfm->hdr));
   cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;
   cfm->hdr.entId.ent = egCb.init.ent;
   cfm->hdr.entId.inst = egCb.init.inst;


   cfm->hdr.transId = hdr->transId;





   switch (type)
   {
      case 1:
         {



            EgMiLegCfgCfm(egPst, cfm);
            break;
         }

      case 2:
         {



            EgMiLegCntrlCfm(egPst, cfm);
            break;
         }

      case 3:
         {



            EgMiLegStsCfm(egPst, cfm);
            break;
         }

      case 4:
         {



            EgMiLegStaCfm(egPst, cfm);
            break;
         }

      default:
         {



            { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                               5202
            , 0x4, ((0 + 0) + 241), 0, (Txt *)"egSendLmCfm(): Invalid Message Type");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5202); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                ;

            { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5204); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); };
         }
   }
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5207); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
 Void egSendLmCntrlCfm
(
Pst *pst,
U16 status,
U16 reason,
Header *hdr
)







{
   EgMngmt cntrlCfm;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5243); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; };

   { if (egCb.init.dbgMask & ((0x00000100 << 3))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5245); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [" "\"INFO\"" " : " "0" "]" ); printf("%s\n", egCb.init.prntBuf); }; egCmPrntDbg(0,(Void*) 0, (S8 *)"0"); { sprintf (egCb.init.prntBuf, ":"); printf("%s\n", egCb.init.prntBuf); }; { sprintf (egCb.init.prntBuf, "Sending Control Confirm"); printf("%s\n", egCb.init.prntBuf); }; { sprintf (egCb.init.prntBuf, "\n"); printf("%s\n", egCb.init.prntBuf); }; } };

   cmMemset((U8 *)&cntrlCfm, 0, sizeof(EgMngmt));




   cntrlCfm.cfm.status = status;
   cntrlCfm.cfm.reason = reason;


   egSendLmCfm(pst, hdr, 2, &cntrlCfm);

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5258); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
}
 Data *egAlloc
(
Size size
)




{
   S16 retValue = 0;

   Data *pCb = 0L;
   Status memStatus;
   CmStatus *Cfm = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5292); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   if (size == 0)
   {
      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5299); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(pCb); };
   }




   memStatus = 0;







   if ( (retValue = SGetSBuf(egCb.init.region, egCb.init.pool, &pCb, size)) != 0)
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                          5316
       , 0x4, ((0 + 0) + 242), 0, (Txt *)"egAlloc(): Memory Allocation Failed");; if(0L != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5316); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0L); }; } }
                                                           ;
   }
   else
   {



      (Void)cmMemset((U8 *) pCb, '\0', size);




      egCb.genSta.memAlloc += size;
   }




   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5334); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(pCb); };
}
 S16 egFree
(
Data *data,
Size size
)





{

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5367); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }




   if ((data == 0L) || (size == 0))
   {
      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5374); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
   }




   (Void) SPutSBuf(egCb.init.region,
                   egCb.init.pool,
                   data,
                   size);




   egCb.genSta.memAlloc -= size;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5390); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
 S16 egActvInit
(
Ent ent,
Inst inst,
Region region,
Reason reason
)
{
   U16 idx=0;
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5454); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; };
   (Void) cmMemset((U8 *) &egCb, 0, sizeof(egCb));






   egCb.init.ent = ent;
   egCb.init.inst = inst;
   egCb.init.region = region;
   egCb.init.reason = reason;




   egCb.init.procId = SFndProcId();





   egCb.init.usta = 0;




   egCb.init.cfgDone = 0;




   egCb.init.trc = 0;





   egCb.init.dbgMask = 0;
   egCb.egTqCp.nxtEnt = 0;
   egCb.egTqCp.tmrLen = 1024;




   egCb.egTqCp.nxtEnt = 0;
   egCb.egTqCp.tmrLen = 1024;




   for(idx=0; idx < 1024; idx++)
   {
      egCb.egTq[idx].first = (CmTimer *)0L;
      egCb.egTq[idx].tail = (CmTimer *)0L;
   }

   egInitExt();






   return(0);
}
 Void egMiTptSrvOpenInd
(
EgTptSrvCb *serverCb
)




{
   EgUsta sta;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5631); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; };

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));


   sta.dgn.dgnVal[0].type = 5;
   sta.dgn.dgnVal[0].t.connId = serverCb->suConnId;

   egSendLmAlarm (3,
         (256 + 1),
         0,
         &sta.dgn);


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5645); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
}
 Void egMiTptSrvCloseInd
(
EgTptSrvCb *serverCb,
Bool fromLMI
)





{
   EgUSapCb *uSapCb;
   Bool openSrv;
   EgTptSrvCb *curSrv;
   U16 nmbSrv;
   EgUsta sta;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5680); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; };






   { if (egCb.init.dbgMask & ((0x00000100 << 2))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5689); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [" "\"DEBUG\"" " : " "0" "]" ); printf("%s\n", egCb.init.prntBuf); }; egCmPrntDbg(0,(Void*) 0, (S8 *)"0"); { sprintf (egCb.init.prntBuf, ":"); printf("%s\n", egCb.init.prntBuf); }; { sprintf (egCb.init.prntBuf, "Indication from TPT that tptSrv is closed: " "Transport server (%ld) fromLMI(%d)", serverCb->suConnId, fromLMI); printf("%s\n", egCb.init.prntBuf); }; { sprintf (egCb.init.prntBuf, "\n"); printf("%s\n", egCb.init.prntBuf); }; } }

                                              ;


   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));




   sta.dgn.dgnVal[0].type = 5;
   sta.dgn.dgnVal[0].t.connId = serverCb->suConnId;





   if (fromLMI == 1)
   {



      egSendLmAlarm(
                  3,
                  (256 + 2),
                  8,
                  &sta.dgn);
   }
   else
   {



      egSendLmAlarm(
                  3,
                  (256 + 2),
                  (256 + 5),
                  &sta.dgn);
   }





   uSapCb = serverCb->uSapCb;
   if (uSapCb == 0L)
   {
      { if (egCb.init.dbgMask & ((0x00000100 << 6))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5734); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [" "\"ERROR\"" " : " "0" "]" ); printf("%s\n", egCb.init.prntBuf); }; egCmPrntDbg(0,(Void*) 0, (S8 *)"0"); { sprintf (egCb.init.prntBuf, ":"); printf("%s\n", egCb.init.prntBuf); }; { sprintf (egCb.init.prntBuf, "USAP is NULL"); printf("%s\n", egCb.init.prntBuf); }; { sprintf (egCb.init.prntBuf, "\n"); printf("%s\n", egCb.init.prntBuf); }; } };
      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5735); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
   }




   switch (uSapCb->state)
   {
      case 3:



         break;
      case 2:
         {



            openSrv = 0;




            for (nmbSrv = 0; nmbSrv < egCb.tSapCb->numSrvr; nmbSrv++)

            {



               curSrv = egCb.tSapCb->tptSrvCbLst[nmbSrv];


               if (( curSrv != 0L) && (curSrv->uSapCb != 0L))
               {
                  if ((curSrv->uSapCb->suId == uSapCb->suId) &&
                        (curSrv->state == 1))
                  {
                     openSrv = 1;
                     break;
                  }
               }
            }





            if (openSrv == 0)
            {
               uSapCb->state = 3;




               cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

               sta.dgn.dgnVal[0].type = 1;
               sta.dgn.dgnVal[0].t.sapId = uSapCb->suId;

               egSendLmAlarm(
                     3,
                     (256 + 3),
                     (256 + 6),
                     &sta.dgn);





            }
         }
         break;
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5809); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
}
static Void egMiFillResponsePost
(
Pst *respPst,
Pst *reqPst,
Header *reqHeader
)






{

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5842); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; };

   cmMemset((U8 *) respPst, (U8) 0, sizeof(Pst));


   respPst->srcEnt = egCb.init.ent;
   respPst->srcInst = egCb.init.inst;
   respPst->srcProcId = egCb.init.procId;
   respPst->dstEnt = reqPst->srcEnt;
   respPst->dstInst = reqPst->srcInst;
   respPst->dstProcId = reqPst->srcProcId;

   respPst->selector = reqHeader->response.selector;
   respPst->prior = reqHeader->response.prior;
   respPst->route = reqHeader->response.route;

   respPst->region = egCb.init.region;



   respPst->pool = reqHeader->response.mem.pool;


   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5865); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return; };
}
static S16 egInitEguCb
(
CmStatus *status
)




{
   U32 retValue = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5897); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   cmMemset((U8*)&egCb.egUCb, 0, sizeof(EgUcb));




    cmInitTimers(&(egCb.egUCb.echoTimers), 1);
    cmInitTimers(&(egCb.egUCb.n3t3Timers), 1);





   retValue = cmHashListInit(&(egCb.egUCb.echoReqHashList),
                        1024,
                        0,
                        0,
                        4,
                        egCb.init.region,
                        egCb.init.pool);

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5919); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };

}
static S16 egCheckIpAddrInUsapLst
(
CmTptAddr *ipAddr
)




{
   S16 retVal = 0;
   S32 cnt = 0;
   EgIpCb *ipCb = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5953); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

     for(cnt = 0; cnt < egCb.genCfg.nmbUSaps; cnt++)
     {
      if((egCb.egtSapLst[cnt] != 0L) &&
            (egCb.egtSapLst[cnt]->cfg.flag == 1))
      {
            if(0 == (retVal = cmHashListFind(&(egCb.egtSapLst[cnt]->ipCbHashList), (U8 *)ipAddr,
                                               sizeof(CmTptAddr),0,(U32 *)&ipCb)))
          {
              { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5963); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
          }
      }

     }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",5969); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); };

}
static S16 egIpAddrCfg
(
EgIpAddrCfg *ipAddrCfg,
CmStatus *status
)





{
   EgIpCb *tmpIpCb = 0L;
   U32 cnt = 0;
   S16 retVal = 0;
   SpId sapId = 0;
   CmTptAddr tmpSrcAddr;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6006); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   cmMemset((U8*)&tmpSrcAddr, 0, sizeof(CmTptAddr));




   status->status = 0;
   status->reason = 0;

   for(cnt = 0; cnt < ipAddrCfg->nmbIpAddr; cnt++)
   {

      sapId = ipAddrCfg->ipInfo[cnt].spId;
      if (!egCb.egtSapLst[sapId])
      {
         { if(status != 0L) { status->status = 1; status->reason = 80; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                                       6023
         , 0x4, ((0 + 0) + 245), 0, (Txt *)"egIpAddrCfg(): USapCb Cfg Not Done");; if(1 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6023); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); }; } }
                                                                        ;
      }






      egCpyCmTptAddr(&tmpSrcAddr, &(ipAddrCfg->ipInfo[cnt].srcIpAddr));
      tmpSrcAddr.u.ipv4TptAddr.port = 0;






      if((retVal = egCheckIpAddrInUsapLst(&tmpSrcAddr)) == 0)
      {
          ipAddrCfg->ipInfo[cnt].cfmStatus = 0;
            status->status = 1;
            status->reason = 68;
             SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
             ,
                                                              6045
             , 0x4, ((0 + 0) + 246), 0, (Txt *)"egIpAddrCfg(): IpAddress Already exits");

          continue;

      }

       { if (SGetSBuf(egCb.init.region, egCb.init.pool, (Data **) &tmpIpCb, (Size) sizeof(EgIpCb)) == 0) { cmMemset((U8 *)(*&tmpIpCb), 0, sizeof(EgIpCb)); { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6050); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 1,(Void*)&tmpIpCb, (U32)sizeof(EgIpCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; } else { (*&tmpIpCb) = 0L; {}; } };

    if (tmpIpCb == 0L)
       {
          { if (egCb.init.dbgMask & ((0x00000100 << 6))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6055); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [" "\"ERROR\"" " : " "0" "]" ); printf("%s\n", egCb.init.prntBuf); }; egCmPrntDbg(0,(Void*) 0, (S8 *)"0"); { sprintf (egCb.init.prntBuf, ":"); printf("%s\n", egCb.init.prntBuf); }; { sprintf (egCb.init.prntBuf,"\negCbTsk():Failed to Allocate the memory for EgIpCb\n"); printf("%s\n", egCb.init.prntBuf); }; { sprintf (egCb.init.prntBuf, "\n"); printf("%s\n", egCb.init.prntBuf); }; } }
                                                                         ;
           { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6056); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(1); };
       }






       retVal = cmHashListInit(&(tmpIpCb->tptServCbLst),
                            1024,
                            0,
                            0,
                            5,
                            egCb.init.region,
                            egCb.init.pool);

      if(retVal != 0)
        {





          { if (tmpIpCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6079); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)tmpIpCb, (U32)sizeof(EgIpCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) tmpIpCb, (Size) sizeof(EgIpCb)); (tmpIpCb) = 0L; }};
          ipAddrCfg->ipInfo[cnt].cfmStatus = 0;
            status->status = 1;
            status->reason = 67;
             SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
             ,
                                                                                          6084
             , 0x4, ((0 + 0) + 247), 0, (Txt *)"egIpAddrCfg(): Initialization of transport server hash list failed");

          continue;
      }





      tmpIpCb->dfltPort = 0;






      retVal = cmHashListInit(&(tmpIpCb->destAddrCbLst),
                            1024,
                            0,
                            0,
                            7,
                            egCb.init.region,
                            egCb.init.pool);

      if(retVal != 0)
        {




          ipAddrCfg->ipInfo[cnt].cfmStatus = 0;
          cmHashListDeinit(&(tmpIpCb->tptServCbLst));
          { if (tmpIpCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6115); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)tmpIpCb, (U32)sizeof(EgIpCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) tmpIpCb, (Size) sizeof(EgIpCb)); (tmpIpCb) = 0L; }};
            status->status = 1;
            status->reason = 67;
             SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
             ,
                                                                                             6119
             , 0x4, ((0 + 0) + 248), 0, (Txt *)"egIpAddrCfg(): Initialization of destination address hash list failed");

          continue;

      }





      cmMemcpy((U8 *)&(tmpIpCb->ipAddrInfo), (const U8 *)&(ipAddrCfg->ipInfo[cnt]),
                  sizeof (EgIpInfo));

      sapId = ipAddrCfg->ipInfo[cnt].spId;
      retVal = cmHashListInsert(&(egCb.egtSapLst[sapId]->ipCbHashList), (U32)tmpIpCb,
                           (U8*)&(tmpIpCb->ipAddrInfo.srcIpAddr), sizeof(CmTptAddr) );




        if(retVal != 0)
      {





          ipAddrCfg->ipInfo[cnt].cfmStatus = 0;
          cmHashListDeinit(&(tmpIpCb->tptServCbLst));
          cmHashListDeinit(&(tmpIpCb->destAddrCbLst));
          { if (tmpIpCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6156); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)tmpIpCb, (U32)sizeof(EgIpCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) tmpIpCb, (Size) sizeof(EgIpCb)); (tmpIpCb) = 0L; }};
            status->status = 1;
            status->reason = 69;
             SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
             ,
                                                                                  6160
             , 0x4, ((0 + 0) + 249), 0, (Txt *)"egIpAddrCfg(): Insertion of IpCb into the hash list failed");

          continue;
      }
   }

   if( status->status == 0)
   {





       { if ((ipAddrCfg->ipInfo) != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6172); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)(ipAddrCfg->ipInfo), (U32)(ipAddrCfg->nmbIpAddr * sizeof(EgIpInfo)) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) (ipAddrCfg->ipInfo), (Size) (ipAddrCfg->nmbIpAddr * sizeof(EgIpInfo))); ((ipAddrCfg->ipInfo)) = 0L; }};

   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6176); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };

}
static S16 egMiTptSrvrDeInit
(
CmHashListCp *tptSrvrHashList,
Bool del
)





{
   S16 retValue = 0;
   EgTptSrvCb *prevTptSrvrCb = 0L;
   EgTptSrvCb *tptSrvrCb = 0L;
   U32 idx = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6213); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   if( del == 1)
   {
      for (;((retValue = cmHashListGetNext(tptSrvrHashList,(U32) prevTptSrvrCb, (U32*)&tptSrvrCb)) == 0);)
      {






          if ( (retValue = cmHashListDelete(tptSrvrHashList, (U32)tptSrvrCb)) == 0)
          {






              idx = tptSrvrCb->suConnId;
              (Void) egTptCloseServer (tptSrvrCb);



              egTptFreeServer(tptSrvrCb);






              egCb.tSapCb->tptSrvCbLst[idx] = 0L;

           }
           else
          {
              SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
              ,
                                                                                                      6251
              , 0x4, ((0 + 0) + 250), 0, (Txt *)"egMiTptSrvrDeInit(): Failed to delete tpt server Control block from hash list");
                                                                                                       ;
          }
          prevTptSrvrCb = tptSrvrCb = 0L;
       }
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6257); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egMiteIdCbDeInit
(
CmHashListCp *teIdHashList,
Bool del
)





{
   S16 retValue = 0;
   EgTeIdCb *prevTeIdCb = 0L;
   EgTeIdCb *teIdCb = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6293); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   for (;((retValue = cmHashListGetNext(teIdHashList, (U32) prevTeIdCb, (U32*)&teIdCb)) == 0);)
   {




       if(del == 1)
       {
          if ( (retValue = cmHashListDelete(teIdHashList, (U32)teIdCb)) != 0)
         {
              SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
              ,
                                                                           6306
              , 0x4, ((0 + 0) + 251), 0, (Txt *)"egMiteIdCbDeInit(): Failed to delete the TeId Control block");
                                                                            ;
              { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6307); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
          }
          else
          {



             if(teIdCb->reOrdering == 1)
             {




                   egSchedTmr((Ptr)teIdCb, 6, 2, egCb.genCfg.reOrderTmr.val);

                  if(0 != (retValue = egFlushAllPackets(teIdCb)))
                  {
                     SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                     ,
                                                                             6325
                     , 0x4, ((0 + 0) + 252), 0, (Txt *)"egMiteIdCbDeInit(): failed to flush reorderin buffer");
                                                                              ;
                     { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6326); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
                  }

                 egFree((Data*)(teIdCb->seqInfo->pduArray), (sizeof(EgtUEvnt*) * egCb.genCfg.pduWindSize));
                 { if (teIdCb->seqInfo != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6330); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)teIdCb->seqInfo, (U32)sizeof(SeqInfo) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) teIdCb->seqInfo, (Size) sizeof(SeqInfo)); (teIdCb->seqInfo) = 0L; }};
             }
             { if (teIdCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6332); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)teIdCb, (U32)sizeof(EgTeIdCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) teIdCb, (Size) sizeof(EgTeIdCb)); (teIdCb) = 0L; }}
          }
          prevTeIdCb = teIdCb = 0L;
       }
       else
       {
          prevTeIdCb = teIdCb;
          teIdCb = 0L;
       }
    }
   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6342); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egMiDestAddrDeInit
(
CmHashListCp *destAddrHashList,
Bool del
)





{
   S16 retValue = 0;
   EgDestAddrCb *prevDestAddrCb = 0L;
   EgDestAddrCb *destAddrCb = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6376); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; };

   for (;((retValue = cmHashListGetNext(destAddrHashList, (U32)prevDestAddrCb, (U32*)&destAddrCb)) == 0);)
   {






      if((retValue = egMiteIdCbDeInit(&(destAddrCb->teIdLst), del)) != 0)
      {
         SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                                                         6389
         , 0x4, ((0 + 0) + 253), 0, (Txt *)"egMiDestAddrDeInit(): Failed to deInitialize the Tunnel Id control block");
                                                                                          ;
      }

      if(del == 1)
      {




         if ((retValue = cmHashListDelete(destAddrHashList, (U32)destAddrCb)) != 0)
         {
            SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                                                               6401
            , 0x4, ((0 + 0) + 254), 0, (Txt *)"egMiDestAddrDeInit(): Failed to delete the destination addressControl block");
                                                                                                ;
         }
         else
         {



            cmHashListDeinit(&(destAddrCb->teIdLst));
            { if (destAddrCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6409); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)destAddrCb, (U32)sizeof(EgDestAddrCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) destAddrCb, (Size) sizeof(EgDestAddrCb)); (destAddrCb) = 0L; }}
         }
         prevDestAddrCb = destAddrCb = 0L;
      }
      else
      {
         prevDestAddrCb = destAddrCb;
         destAddrCb = 0L;
      }
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6420); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
 S16 egMiIpCbDeInit
(
CmHashListCp *IpCbHashList,
Bool del
)





{
   S16 retValue = 0;
   EgIpCb *prevIpCb = 0L;
   EgIpCb *ipCb = 0L;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6455); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   for (;((retValue = cmHashListGetNext(IpCbHashList, (U32)prevIpCb, (U32*)&ipCb)) == 0);)
   {






      if((retValue = egMiTptSrvrDeInit((&(ipCb->tptServCbLst)), del)) != 0)
      {
           SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
           ,
                                                                                       6468
           , 0x4, ((0 + 0) + 255), 0, (Txt *)"egMiIpCbDeInit(): Failed to deInitialize the transport server control block");
                                                                                        ;
      }






      if((retValue = egMiDestAddrDeInit(&(ipCb->destAddrCbLst), del)) != 0)
      {
            SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                                                     6479
            , 0x4, ((0 + 0) + 256), 0, (Txt *)"egMiIpCbDeInit(): Failed to deInitialize the destination control block");
                                                                                      ;
      }


      if( del == 1)
      {




          if ( (retValue = cmHashListDelete(IpCbHashList, (U32)ipCb)) != 0)
          {
             SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
             ,
                                                                       6492
             , 0x4, ((0 + 0) + 257), 0, (Txt *)"egMiIpCbDeInit(): Failed to del the Ip Control block");
                                                                        ;
          }
          else
          {



            cmHashListDeinit(&(ipCb->destAddrCbLst));
            cmHashListDeinit(&(ipCb->tptServCbLst));
             { if (ipCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6501); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)ipCb, (U32)sizeof(EgIpCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) ipCb, (Size) sizeof(EgIpCb)); (ipCb) = 0L; }}
          }
         prevIpCb = ipCb = 0L;
      }
      else
      {
         prevIpCb = ipCb;
         ipCb = 0L;
      }
    }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6512); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egIpAddrCntrl
(
EgMngmt *ipAddrCntrl
)




{
   S16 retValue = 0;
   EgIpCb *ipCb = 0L;
   CmStatus *cfm = 0L;
   SpId fromSpId = 0;
   SpId toSpId = 0;
   CmTptAddr ipAddr;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6548); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }


   fromSpId = ipAddrCntrl->u.cntrl.s.ipAddress.fromSpId;
   toSpId = ipAddrCntrl->u.cntrl.s.ipAddress.toSpId;
   cmMemset((U8 *)&ipAddr, 0 ,sizeof(CmTptAddr));
   { ipAddr.type = ipAddrCntrl->u.cntrl.s.ipAddress.ipAddr.type; if(ipAddrCntrl->u.cntrl.s.ipAddress.ipAddr.type == 4) { ipAddr.u.ipv4TptAddr.address = ipAddrCntrl->u.cntrl.s.ipAddress.ipAddr.u.ipv4TptAddr.address; } };

   if (!egCb.egtSapLst[fromSpId])
   {
          { if(cfm != 0L) { cfm->status = 0; cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
          ,
                                                                                 6559
          , 0x4, ((0 + 0) + 258), 0, (Txt *)"egIpAddrCntrl(): USapCb Cfg Not Done");; if(80 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6559); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(80); }; } }
                                                                                  ;
   }





   if(0 != (retValue = cmHashListFind(&(egCb.egtSapLst[fromSpId]->ipCbHashList),
                         (U8 *)&ipAddr,sizeof(CmTptAddr),0,(U32 *)&ipCb)))
   {
         SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                                             6570
         , 0x4, ((0 + 0) + 259), 0, (Txt *)"egIpAddrCntrl(): failed to get the IpCb from sap list");
                                                                              ;
       { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6571); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
   }





   switch (ipAddrCntrl->u.cntrl.action)
   {
      case 107:
      {





           if ((retValue = egMiMoveIpAddr(ipCb, fromSpId, toSpId)) != 0)
           {
              SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
              ,
                                                                    6590
              , 0x4, ((0 + 0) + 260), 0, (Txt *)"egIpAddrCntrl(): Failed to move the Ip Control block");
                                                                     ;
             { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6591); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
           }
         break;
      }

      case 7:
      {






          if((retValue = egMiDelIpAddr(ipCb, fromSpId)) != 0)
          {
              SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
              ,
                                                                                      6607
              , 0x4, ((0 + 0) + 261), 0, (Txt *)"egIpAddrCntrl(): Failed to proc the destination control block");
                                                                                       ;

              { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6609); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
          }

          break;

      }

      default:
         {



            { if(cfm != 0L) { cfm->status = 0; cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                       6622
            , 0x4, ((0 + 0) + 262), 0, (Txt *)"egUSapCntrl, Invalid Action");; if(9 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6622); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(9); }; } }
                                                        ;
         }
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6626); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egSrvrStsReq
(
EgMngmt *stsReq,
Action action,
EgMngmt *stsCfm
)






{
   SpId sapId;
   EgTptSrvCb *tptSrvCb;
   CmStatus *Cfm = 0L;
   S16 retVal = 0;
   EgIpCb *ipCb;
   CmTptAddr tptAddr;
   U32 portNmb = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6665); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   sapId = stsReq->u.sts.s.tptSrvrSts.spId;





   cmMemset((U8 *)&tptAddr, 0 ,sizeof(CmTptAddr));
   { tptAddr.type = stsReq->u.sts.s.tptSrvrSts.lclAddr.type; if(stsReq->u.sts.s.tptSrvrSts.lclAddr.type == 4) { tptAddr.u.ipv4TptAddr.address = stsReq->u.sts.s.tptSrvrSts.lclAddr.u.ipv4TptAddr.address; } };

   { if(stsReq->u.sts.s.tptSrvrSts.lclAddr.type == 4) { portNmb = stsReq->u.sts.s.tptSrvrSts.lclAddr.u.ipv4TptAddr.port; } };
   if(((sapId >= (SpId)1) || (sapId < 0)) || (egCb.egtSapLst[sapId] == 0L))
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                   6688
       , 0x4, ((0 + 0) + 263), 0, (Txt *)"egSrvrStsReq(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6688); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                    ;
   }




   if (!egCb.tSapCb)

   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                 6698
      , 0x4, ((0 + 0) + 264), 0, (Txt *)"egSrvrStsReq(): TSap not configured");; if(56 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6698); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(56); }; } }
                                                                  ;
   }

   if(0 != (retVal = cmHashListFind(&(egCb.egtSapLst[sapId]->ipCbHashList), (U8 *)&tptAddr,
                                         sizeof(CmTptAddr),0,(U32 *)&ipCb)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                            6705
      , 0x4, ((0 + 0) + 265), 0, (Txt *)"egSrvrStsReq(): IpCb not found");; if(71 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6705); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(71); }; } }
                                                             ;
   }

   if(0 != (retVal = cmHashListFind(&(ipCb->tptServCbLst), (U8 *)&portNmb,
                                         sizeof(U16),0,(U32 *)&tptSrvCb)))
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                                6712
       , 0x4, ((0 + 0) + 266), 0, (Txt *)"egSrvrStsReq(): tptSrvCb not found");; if(75 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6712); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(75); }; } }
                                                                 ;
   }

   stsCfm->u.sts.s.tptSrvrSts.totalMsgsTx = tptSrvCb->stats.totalMsgsTx;
   stsCfm->u.sts.s.tptSrvrSts.totalMsgsRx = tptSrvCb->stats.totalMsgsRx;

   if (action == 0)
   {



        cmMemset((Data *) &tptSrvCb->stats, '\0', sizeof(EgTptStat));
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6726); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egIpAddrStsReq
(
EgMngmt *stsReq,
Action action,
EgMngmt *stsCfm
)






{
   SpId sapId;
   EgIpCb *ipCb = 0L;
   EgTptSrvCb *prevTptSrvCb = 0L;
   EgTptSrvCb *tptSrvCb = 0L;
   CmTptAddr tptAddr;
   CmStatus *Cfm = 0L;
   S16 retVal = 0;
   U32 cnt = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6767); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   sapId = stsReq->u.sts.s.ipSts.spId;




   cmMemset((U8 *)&tptAddr, 0 ,sizeof(CmTptAddr));
   { tptAddr.type = stsReq->u.sts.s.ipSts.IpAddr.type; if(stsReq->u.sts.s.ipSts.IpAddr.type == 4) { tptAddr.u.ipv4TptAddr.address = stsReq->u.sts.s.ipSts.IpAddr.u.ipv4TptAddr.address; } };







   if(((sapId > (SpId)1) || (sapId < 0)) || (egCb.egtSapLst[sapId] == 0L))
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                     6786
       , 0x4, ((0 + 0) + 267), 0, (Txt *)"egIpAddrStsReq(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6786); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                      ;
   }

   if(0 != (retVal = cmHashListFind(&(egCb.egtSapLst[sapId]->ipCbHashList), (U8 *)&tptAddr,
                                         sizeof(CmTptAddr),0,(U32 *)&ipCb)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                          6793
      , 0x4, ((0 + 0) + 268), 0, (Txt *)"egIpAddrStsReq(): Finding the IpCb from the hash list failed");; if(71 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6793); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(71); }; } }
                                                                                           ;
   }

   stsCfm->u.sts.s.ipSts.nmbPorts = egCb.egtSapLst[sapId]->ipCbHashList.nmbEnt;
   stsCfm->u.sts.s.ipSts.portsLst = (U32*)egAlloc((egCb.egtSapLst[sapId]->ipCbHashList.nmbEnt) * sizeof(U32));

   for(cnt = 0; cnt < stsCfm->u.sts.s.ipSts.nmbPorts; cnt++)
   {
      if((retVal = cmHashListGetNext(&(ipCb->tptServCbLst), (U32)prevTptSrvCb, (U32*)&tptSrvCb)) != 0)
      {

         egFree((Data*)(stsCfm->u.sts.s.ipSts.portsLst), sizeof(U32));

         stsCfm->u.sts.s.ipSts.portsLst = 0L;
         stsCfm->u.sts.s.ipSts.nmbPorts = 0;

         { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                                                                       6810
         , 0x4, ((0 + 0) + 269), 0, (Txt *)"egIpAddrStsReq(): Finding the tptSrvCb from the hash list failed");; if(75 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6810); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(75); }; } }
                                                                                                        ;
      }
      stsCfm->u.sts.s.ipSts.portsLst[cnt] = tptSrvCb->portNum;
      if(tptSrvCb->portStatus == 1)
      {
         stsCfm->u.sts.s.ipSts.nmbActvSrvrs++;
      }
      else
      {
         stsCfm->u.sts.s.ipSts.nmbInactvSrvr++;
      }
      prevTptSrvCb = tptSrvCb;
      tptSrvCb = 0L;
   }
   stsCfm->u.sts.s.ipSts.totalMsgsTx = ipCb->ipStats.totalMsgsTx;
   stsCfm->u.sts.s.ipSts.totalMsgsRx = ipCb->ipStats.totalMsgsRx;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6827); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egTnlStsReq
(
EgMngmt *stsReq,
Action action,
EgMngmt *stsCfm
)






{
   SpId sapId;
   EgIpCb *ipCb = 0L;
   EgDestAddrCb *destAddrCb = 0L;
   EgTeIdCb *teIdCb = 0L;
   CmTptAddr destAddr;
   CmTptAddr srcAddr;
   CmStatus *Cfm = 0L;
   U32 teId = 0;
   S16 retVal = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6869); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }

   teId = stsReq->u.sts.s.tnlSts.teId;
   sapId = stsReq->u.sts.s.tnlSts.spId;





   cmMemset((U8 *)&srcAddr, 0 ,sizeof(CmTptAddr));
   { srcAddr.type = stsReq->u.sts.s.tnlSts.srcIpAddr.type; if(stsReq->u.sts.s.tnlSts.srcIpAddr.type == 4) { srcAddr.u.ipv4TptAddr.address = stsReq->u.sts.s.tnlSts.srcIpAddr.u.ipv4TptAddr.address; } };

   cmMemset((U8 *)&destAddr, 0 ,sizeof(CmTptAddr));
   { destAddr.type = stsReq->u.sts.s.tnlSts.destIpAddr.type; if(stsReq->u.sts.s.tnlSts.destIpAddr.type == 4) { destAddr.u.ipv4TptAddr.address = stsReq->u.sts.s.tnlSts.destIpAddr.u.ipv4TptAddr.address; } };







   if(((sapId > (SpId)1) || (sapId < 0)) || (egCb.egtSapLst[sapId] == 0L))
   {
       { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
       ,
                                                  6893
       , 0x4, ((0 + 0) + 270), 0, (Txt *)"egTnlStsReq(): Invalid SapId");; if(12 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6893); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(12); }; } }
                                                   ;
   }

   if(0 != (retVal = cmHashListFind(&(egCb.egtSapLst[sapId]->ipCbHashList), (U8 *)&srcAddr,
                                         sizeof(CmTptAddr),0,(U32 *)&ipCb)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                       6900
      , 0x4, ((0 + 0) + 271), 0, (Txt *)"egTnlStsReq(): Finding the IpCb from the hash list failed");; if(71 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6900); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(71); }; } }
                                                                                        ;
   }



   if(0 != (retVal = cmHashListFind(&(ipCb->destAddrCbLst), (U8 *)&destAddr,
                                         sizeof(CmTptAddr),0,(U32 *)&destAddrCb)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                             6909
      , 0x4, ((0 + 0) + 272), 0, (Txt *)"egTnlStsReq(): Finding the destAddrCb from the hash list failed");; if(76 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6909); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(76); }; } }
                                                                                              ;
   }

   if(0 != (retVal = cmHashListFind(&(destAddrCb->teIdLst), (U8 *)&teId,
                                         sizeof(U32),0,(U32 *)&teIdCb)))
   {
      { if(Cfm != 0L) { Cfm->status = 0; Cfm->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                                       6916
      , 0x4, ((0 + 0) + 273), 0, (Txt *)"egTnlStsReq(): Finding the teId from the hash list failed");; if(77 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6916); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(77); }; } }
                                                                                        ;
   }


   stsCfm->u.sts.s.tnlSts.totalMsgsTx = teIdCb->totalMsgsTx;
   stsCfm->u.sts.s.tnlSts.totalMsgsRx = teIdCb->totalMsgsRx;
   stsCfm->u.sts.s.tnlSts.reOrderPrsnt = teIdCb->reOrdering;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6924); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
 S16 egMiProcIpCb
(
EgIpCb *ipCb,
SpId spId
)





{
     S16 retValue = 0;

     { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6957); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }





     if((retValue = egMiTptSrvrDeInit(&(ipCb->tptServCbLst), 1)) != 0)
     {
           SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
           ,
                                                                                    6966
           , 0x4, ((0 + 0) + 274), 0, (Txt *)"egMiProcIpCb(): Failed to deInitialize the transport server control block");
                                                                                     ;

         { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6968); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
     }





     if((retValue = egMiDestAddrDeInit(&(ipCb->destAddrCbLst), 1)) != 0)
     {
           SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *) "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c", 6977, 0x4, ((0 + 0) + 275), 0, (Txt *)"egMiProcIpCb(): Failed to deInitialize the destination control block");;
         { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6978); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
     }




     if ((retValue = cmHashListDelete(&(egCb.egtSapLst[spId]->ipCbHashList), (U32)ipCb)) != 0)
     {
           SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
           ,
                                                               6987
           , 0x4, ((0 + 0) + 276), 0, (Txt *)"egMiProcIpCb(): Failed to del the Ip Control block");
                                                                ;
         { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6988); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
     }
     else
     {



         retValue = cmHashListDeinit(&(ipCb->destAddrCbLst));
         retValue = cmHashListDeinit(&(ipCb->tptServCbLst));
         { if (ipCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",6997); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)ipCb, (U32)sizeof(EgIpCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) ipCb, (Size) sizeof(EgIpCb)); (ipCb) = 0L; }}
     }

    { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7000); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
}
static S16 egMiMoveIpAddr
(
EgIpCb *ipCb,
U16 fromSpId,
U16 toSpId
)






{

   EgUEchoReqCb *prevEchoReqCb = 0L;
   EgUEchoReqCb *echoReqCb = 0L;
   EgTptSrvCb *prevTptSrvCb = 0L;
   EgTptSrvCb *tptSrvCb = 0L;
   Bool match;
   CmStatus *status = 0L;
   S16 retValue = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7043); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }


   if (!egCb.egtSapLst[toSpId])
   {
      { if(status != 0L) { status->status = 0; status->reason = 0; } SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                              7049
      , 0x4, ((0 + 0) + 319), 0, (Txt *)"egMiMoveIpAddr(): USapCb Cfg Not Done");; if(80 != 0) { { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7049); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(80); }; } }
                                                                               ;
   }






   if ((retValue = cmHashListDelete(&(egCb.egtSapLst[fromSpId]->ipCbHashList), (U32)ipCb)) != 0)
     {
        SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
        ,
                                                                   7060
        , 0x4, ((0 + 0) + 320), 0, (Txt *)"egMiMoveIpAddr(): Failed to delete the Ip Control block");
                                                                    ;
        { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7061); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
   }





   if(0 != (retValue = cmHashListInsert(&(egCb.egtSapLst[toSpId]->ipCbHashList), (U32)ipCb,
                     (U8*)&(ipCb->ipAddrInfo.srcIpAddr), sizeof(CmTptAddr) )))
   {
      SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                    7072
      , 0x4, ((0 + 0) + 321), 0, (Txt *)"egMiMoveIpAddr(): Failed to delete the Ip Control block");
                                                                     ;
        { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7073); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
   }





   for (;((retValue = cmHashListGetNext(&egCb.egUCb.echoReqHashList, (U32) prevEchoReqCb, (U32*)&echoReqCb)) == 0);)
   {
       retValue = egCmpTptAddr(&(ipCb->ipAddrInfo.srcIpAddr), &(echoReqCb->srcAddr), &match);
      if (retValue == 0 && match == 1)
      {
         echoReqCb->uSapId = toSpId;
      }
      prevEchoReqCb = echoReqCb;
      echoReqCb = 0L;
   }


   for (;((retValue = cmHashListGetNext(&ipCb->tptServCbLst, (U32)prevTptSrvCb, (U32*)&tptSrvCb)) == 0);)
   {
      tptSrvCb->uSapCb = egCb.egtSapLst[toSpId];
      prevTptSrvCb = tptSrvCb;
      tptSrvCb = 0L;
   }

   if(retValue == 2)
   {
      retValue = 0;
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7104); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
}
static S16 egMiDelIpAddr
(
EgIpCb *ipCb,
U16 fromSpId
)





{

   EgUEchoReqCb *prevEchoReqCb = 0L;
   EgUEchoReqCb *echoReqCb = 0L;
   Bool match;
   S16 retValue = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7141); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }





   for (;((retValue = cmHashListGetNext(&(egCb.egUCb.echoReqHashList),
                           (U32) prevEchoReqCb, (U32*)&echoReqCb)) == 0);)
   {
    retValue = egCmpTptAddr(&(ipCb->ipAddrInfo.srcIpAddr), &(echoReqCb->srcAddr), &match);
    if (retValue == 0 && match == 1)
    {
     if ((retValue = cmHashListDelete(&(egCb.egUCb.echoReqHashList), (U32)echoReqCb)) != 0)
     {
      SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
      ,
                                                                7156
      , 0x4, ((0 + 0) + 322), 0, (Txt *)"egMiDelIpAddr(): Failed to delete the Ip Control block");
                                                                 ;
      { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7157); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
     }

     { if (echoReqCb->echoReqBuff != (Buffer*) 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7160); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 2, 2,(Void*)echoReqCb->echoReqBuff, (U32)0 ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void)SPutMsg(echoReqCb->echoReqBuff); echoReqCb->echoReqBuff = 0L; } };
     { if (echoReqCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7161); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)echoReqCb, (U32)sizeof(EgUEchoReqCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) echoReqCb, (Size) sizeof(EgUEchoReqCb)); (echoReqCb) = 0L; }}
      echoReqCb = 0L;
     continue;
    }
    prevEchoReqCb = echoReqCb;
    echoReqCb = 0L;
   }







    if((retValue = egMiProcIpCb(ipCb, fromSpId)) != 0)
    {
         SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
         ,
                                                                                7178
         , 0x4, ((0 + 0) + 323), 0, (Txt *)"egMiMoveIpAddr(): Failed to proc the destination control block");
                                                                                 ;

         { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7180); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
    }

    { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7183); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
}
 S16 egMiRmvEchoCb
(
EgUSapCb *uSapCb,
EgIpCb *ipCb,
EgTptSrvCb *srvCb,
EgTSapCb *tSapCb,
U8 type
)
{

   EgUEchoReqCb *prevEchoReqCb = 0L;
   EgUEchoReqCb *echoReqCb = 0L;
   Bool match = 0;
   Bool del = 0;
   S16 retValue = 0;

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7226); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }





   for (;((retValue = cmHashListGetNext(&(egCb.egUCb.echoReqHashList),
                           (U32) prevEchoReqCb, (U32*)&echoReqCb)) == 0);)
   {
      switch(type)
      {
         case 1 :
         {
            if(echoReqCb->uSapId == uSapCb->suId)
            {
               del = 1;
            }
            break;
         }
         case 2 :
         {
             retValue = egCmpTptAddr(&(ipCb->ipAddrInfo.srcIpAddr), &(echoReqCb->srcAddr), &match);
            if (retValue == 0 && match == 1)
            {
               del = 1;
            }
            break;
         }
         case 3 :
         {
            if(echoReqCb->tptServerCb->tSapCb == tSapCb)
            {
               del = 1;
            }
            break;
         }
         case 4 :
         {
            if(echoReqCb->tptServerCb == srvCb)
            {
               del = 1;
            }
            break;
         }
         default :
         {
            del = 1;
            break;
         }
      }
      if (del == 1)
      {
           if ((retValue = cmHashListDelete(&(egCb.egUCb.echoReqHashList), (U32)echoReqCb)) != 0)
           {
              SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
              ,
                                                                         7281
              , 0x4, ((0 + 0) + 324), 0, (Txt *)"egMiRmvEchoCb(): Failed to delete the Ip Control block");
                                                                          ;
            { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7282); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(retValue); };
           }
         del = 0;
         { if (echoReqCb->echoReqBuff != (Buffer*) 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7285); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 2, 2,(Void*)echoReqCb->echoReqBuff, (U32)0 ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void)SPutMsg(echoReqCb->echoReqBuff); echoReqCb->echoReqBuff = 0L; } };
         { if (echoReqCb != 0L) { { if (egCb.init.dbgMask & ((0x00000100 << 8))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7286); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " [ MEM  : %d %d %p %ld]\n", 3, 2,(Void*)echoReqCb, (U32)sizeof(EgUEchoReqCb) ); printf("%s\n", egCb.init.prntBuf); }; } }; (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) echoReqCb, (Size) sizeof(EgUEchoReqCb)); (echoReqCb) = 0L; }}
         echoReqCb = 0L;
         continue;
      }
      prevEchoReqCb = echoReqCb;
      echoReqCb = 0L;
   }

   { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7294); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf, " Exiting\n"); printf("%s\n", egCb.init.prntBuf); }; } return(0); };
}
static S16 egMiFindSrvCb
(
EgTptSrvCfg *TSrvCfg,
EgTptSrvCb *TSrvCb
)





{
    U16 idx = 0;

    { if (egCb.init.dbgMask & ((0x00000100 << 4))) { { { sprintf (egCb.init.prntBuf, " [%s 0x%x:%x]", "Eg", egCb.init.ent,egCb.init.inst); printf("%s\n", egCb.init.prntBuf); }; } { { sprintf (egCb.init.prntBuf, " [%s:%d]","/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c",7387); printf("%s\n", egCb.init.prntBuf); }; } { sprintf (egCb.init.prntBuf," Entering\n"); printf("%s\n", egCb.init.prntBuf); }; } ;; }







    for (idx=0; idx < egCb.genCfg.nmbSrvs; idx++)
    {




      if ((TSrvCb = egCb.tSapCb->tptSrvCbLst[idx]) != 0L)

      {




         if(idx == TSrvCfg->tptSrvId)
         {
            SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
            ,
                                                                          7411
            , 0x4, ((0 + 0) + 170), 0, (Txt *)"egMiFindSrvCb(): Tpt Server ID Already Configured");
                                                                           ;
            return(57);
         }






         if (TSrvCfg->tptAddr.type == 4)
         {
               if ((TSrvCb->cfg.tptAddr.u.ipv4TptAddr.port ==
                   TSrvCfg->tptAddr.u.ipv4TptAddr.port) &&
                  (TSrvCb->cfg.tptAddr.u.ipv4TptAddr.address ==
                   TSrvCfg->tptAddr.u.ipv4TptAddr.address))
               {
                  SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId, (Txt *)
                                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/egtpu/eg_mi.c"
                  ,
                                                                                        7428
                  , 0x4, ((0 + 0) + 171), 0, (Txt *)"egMiFindSrvCb(): Server with similar address,port already configured");
                                                                                         ;
                  return(57);
               }
         }
      }
    }

    return(0);
}
