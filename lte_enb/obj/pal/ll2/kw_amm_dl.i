static const char* RLOG_MODULE_NAME="AMM";
static int RLOG_MODULE_ID=2048;
static int RLOG_FILE_ID=189;

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






typedef enum {
 L_ALWAYS=0,
 L_FATAL,
 L_ERROR,
 L_WARNING,
 L_EVENT,
 L_INFO,
 L_DEBUG,
 L_UNUSED,
 L_MAX_LOG_LEVEL
} R_LOG_LEVEL;

typedef enum {
 DBG_CELLID,
   DBG_PEERID,
   DBG_ENBID,
  DBG_MMEID,
  DBG_CRNTI,
   DBG_UEIDX,
  DBG_UEID,
  DBG_RBID,
  DBG_LCID,
  DBG_LCGID,
 DBG_TRNSID,
   DBG_INSTID,
 DBG_MAX_IDs
} R_SPL_ARG;
typedef const char* PSTR;


typedef U32 LOGID;
void logLevH( LOGID logId, R_LOG_LEVEL logLevel, PSTR hex, int hexlen, ...);
void logLev0( LOGID logId, R_LOG_LEVEL logLevel, ...);
void logLev1( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, ...);
void logLev2( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, ...);
void logLev3( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, ...);
void logLev4( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...);
void logLevE(LOGID logId, R_LOG_LEVEL logLevel, R_SPL_ARG splType, U32 splVal,
U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...);
void logLevS( LOGID logId, R_LOG_LEVEL logLevel, const char* str, ...);


void hextostr(char* p, PSTR h, int hexlen);

extern int g_logLevel;
extern U32 g_modMask;
extern const char* g_logStr[L_MAX_LOG_LEVEL];
extern const char* g_splStr[DBG_MAX_IDs];




void rlSetLogPath(const char* logDir);





void rlInitLog(U8 type);







void rlSetLogFile(const char* fileName);





void rlSetLogPort(U32 port);




void rlSetLogLevel(R_LOG_LEVEL logLevel);





void rlSetModuleMask(U32 modMask);



void rlSetLogFileSizeLimit(U32 maxFileSize);




void rlSetNumOfLogFiles(U8 nMaxFiles);





void rlSetCircularBufferSize(U32 bufSize);




void rlSetRemoteLoggingFlag(S32 flag);




int rlHandleConInput(char ch);




void rlEnableDisableCore(S32 enable_core);



void rlEnaBleBufferedIO(void);



extern void rlUpdateRlogTti(void);



extern void rlResetLogRateLmt(void);



extern void rlResetLogRateLmt(void);




extern void rlStartLogCountLimit(void);



extern void rlStopLogCountLimit(void);



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
 U8 *cmMemcpy (U8 *tgt, const U8 *src, U32 len);
 S16 cmMemcmp (const U8 *s1, const U8 *s2, U32 len);
 U8 *cmMemset (U8 *src, U8 val, U32 len);

 S16 cmStrcmp (const U8 *s1, const U8 *s2);

 S16 cmStrncmp (const U8 *s1, const U8 *s2, MsgLen len);
 MsgLen cmStrlen (const U8 *s);
typedef struct kwGenCfg
{
   Pst lmPst;

   U32 maxUe;

   U16 maxKwuSaps;

   U16 maxUdxSaps;

   Ticks timeRes;

   U8 rlcMode;

   U16 maxRguSaps;
}KwGenCfg;



typedef struct kwSapCfg
{
   Selector selector;
   MemoryId mem;
   ProcId procId;
   Ent ent;
   Inst inst;
   SpId sapId;
   U16 bndTmrIntvl;
   Priority priority;
   Route route;
}KwSapCfg;




typedef struct kwCfg
{
   union
   {
      KwGenCfg gen;
      KwSapCfg sap;
   }s;
}KwCfg;



typedef struct kwGenSts
{
   CntrSts numUe;
   CntrSts pdusRecv;
   CntrSts pdusSent;
   CntrSts pdusRetx;
   CntrSts bytesRecv;
   CntrSts bytesSent;
   CntrSts unexpPdusRecv;
   CntrSts errorPdusRecv;
   CntrSts protTimeOut;

   CntrSts numOfRb;
   CntrSts numSduDisc;
}KwGenSts;



typedef struct kwKwuSapSts
{

   SpId spId;
   CntrSts sduRx;
   CntrSts sduTx;
}KwKwuSapSts;



typedef struct kwCkwCntSts
{
   CntrSts statMsgs;
}KwCkwCntSts;



typedef struct kwSts
{
   DateTime dt;
   union
   {
      KwGenSts gen;
      KwKwuSapSts kwuSap;
      KwCkwCntSts ckwSap;
   }s;
}KwSts;



typedef struct kwRguSapSta
{
   SuId suId;
   State state;
}KwRguSapSta;



typedef struct kwKwuSapSta
{
   SpId spId;
   State state;
}KwKwuSapSta;



typedef struct kwCkwCntSapSta
{
   SpId spId;
   State state;
}KwCkwCntSapSta;



typedef struct kwSSta
{
   DateTime dt;
   union
   {
      SystemId sysId;
      KwRguSapSta rguSap;
      KwKwuSapSta kwuSap;
      KwCkwCntSapSta ckwSap;
   }s;
}KwSSta;



typedef struct kwTrcCntrl
{
   U8 trcMask;
   S16 trcLen;
}KwTrcCntrl;



typedef struct kwDbgCntrl
{
   U32 dbgMask;

}KwDbgCntrl;



typedef struct kwSapCntrl
{
   SuId suId;
   SpId spId;
}KwSapCntrl;



typedef struct kwCntrl
{
   DateTime dt;
   U8 action;
   U8 subAction;
   union
   {
      KwTrcCntrl trcCntrl;
      KwDbgCntrl dbgCntrl;
      KwSapCntrl sapCntrl;



   }s;
}KwCntrl;



typedef struct kwUSta
{
   DateTime dt;
   CmAlarm alarm;
   SuId suId;
   U32 ueId;




}KwUSta;



typedef struct kwTrc
{
   DateTime dt;
   U16 event;

}KwTrc;



typedef struct _kwMngmt
{
   Header hdr;
   CmStatus cfm;
   union
   {
      KwCfg cfg;
      KwCntrl cntrl;
      KwSts sts;
      KwSSta ssta;
      KwUSta usta;
      KwTrc trc;
   }t;
}KwMngmt;
typedef S16 (*LkwCfgReq) (Pst *pst, KwMngmt *cfg);
typedef S16 (*LkwCfgCfm) (Pst *pst, KwMngmt *cfgCfm);

typedef S16 (*LkwCntrlReq) (Pst *pst, KwMngmt *cntl);
typedef S16 (*LkwCntrlCfm) (Pst *pst, KwMngmt *cntlCfm);

typedef S16 (*LkwStaInd) (Pst *pst, KwMngmt *staInd);
typedef S16 (*LkwStaReq) (Pst *pst, KwMngmt *staReq);
typedef S16 (*LkwStaCfm) (Pst *pst, KwMngmt *staCfm);

typedef S16 (*LkwStsReq) (Pst *pst, Action, KwMngmt *sts);
typedef S16 (*LkwStsCfm) (Pst *pst, Action, KwMngmt *stsCfm);

typedef S16 (*LkwTrcInd) (Pst *pst, KwMngmt *trc, Buffer *mBuf);
extern S16 KwMiLkwCfgReq (Pst *pst, KwMngmt *cfg);
extern S16 KwMiLkwCfgCfm (Pst *pst, KwMngmt *cfgCfm);
extern S16 KwMiLkwCntrlReq (Pst *pst, KwMngmt *cntl);
extern S16 KwMiLkwCntrlCfm (Pst *pst, KwMngmt *cntlCfm);
extern S16 KwMiLkwStaReq (Pst *pst, KwMngmt *staInd);
extern S16 KwMiLkwStaCfm (Pst *pst, KwMngmt *staCfm);
extern S16 KwMiLkwStsReq (Pst *pst, Action, KwMngmt *sts);
extern S16 KwMiLkwStsCfm (Pst *pst, Action action, KwMngmt *stsCfm);
extern S16 KwMiLkwTrcInd (Pst *pst, KwMngmt *trc, Buffer *mBuf);
extern S16 KwMiLkwStaInd (Pst *pst, KwMngmt *staReq);

extern Void kwSendLmAlarm ( U16 category, U16 event, U16 cause, SuId suId, U32 ueId)




                ;
extern S16 smKwActvInit (Ent ent, Inst inst, Region region, Reason reason);
extern S16 smKwActvTsk (Pst *pst, Buffer *mBuf);



extern S16 cmPkLkwCfgReq ( Pst *, KwMngmt * )


         ;

extern S16 cmPkLkwCfgCfm ( Pst *, KwMngmt * )


         ;


extern S16 cmPkLkwCntrlReq ( Pst *, KwMngmt * )


         ;

extern S16 cmPkLkwCntrlCfm ( Pst *, KwMngmt * )


         ;

extern S16 cmPkLkwStaInd ( Pst *, KwMngmt * )


         ;

extern S16 cmPkLkwStaReq ( Pst *, KwMngmt * )


         ;

extern S16 cmPkLkwStaCfm ( Pst *, KwMngmt * )


         ;

extern S16 cmPkLkwStsReq ( Pst *, Action, KwMngmt * )



         ;

extern S16 cmPkLkwStsCfm ( Pst *, Action, KwMngmt * )



         ;

extern S16 cmPkLkwTrcInd ( Pst *, KwMngmt *, Buffer * )



         ;

extern S16 cmUnpkLkwCfgReq ( LkwCfgReq, Pst *, Buffer * )



         ;

extern S16 cmUnpkLkwCfgCfm ( LkwCfgCfm, Pst *, Buffer * )



         ;

extern S16 cmUnpkLkwCntrlReq ( LkwCfgReq, Pst *, Buffer * )



         ;

extern S16 cmUnpkLkwCntrlCfm ( LkwCfgCfm, Pst *, Buffer * )



         ;

extern S16 cmUnpkLkwStaInd ( LkwStaInd, Pst *, Buffer * )



         ;

extern S16 cmUnpkLkwStaReq ( LkwStaReq, Pst *, Buffer * )



         ;

extern S16 cmUnpkLkwStaCfm ( LkwStaCfm, Pst *, Buffer * )



         ;

extern S16 cmUnpkLkwStsReq ( LkwStsReq, Pst *, Buffer * )



         ;

extern S16 cmUnpkLkwStsCfm ( LkwStsCfm, Pst *, Buffer * )


         ;


extern S16 cmUnpkLkwTrcInd ( LkwTrcInd, Pst *, Buffer *)


                 ;
typedef struct ckwLChInfo
{
   U8 lChId;

   U8 type;

}CkwLChInfo;



typedef struct ckwUmInfo
{
   struct _umDl
   {
      U8 snLen;
   }dl;
   struct _umUl
   {
      U8 snLen;

      U8 reOrdTmr;
   }ul;
}CkwUmInfo;



typedef struct ckwAmInfo
{
   struct _amDl
   {
      U16 pollRetxTmr;
      S16 pollPdu;



      S32 pollByte;

      U8 maxRetx;
   }dl;
   struct _amUl
   {
      U16 staProhTmr;
      U8 reOrdTmr;
   }ul;
}CkwAmInfo;



typedef union ckwTmInfo
{
   struct _tmDl
   {
      U32 buffSize;
   }dl;
}CkwTmInfo;



typedef struct ckwEntCfgInfo
{
   U8 cfgType;


   U8 rbId;

   U8 rbType;
   U8 qci;
   CkwLChInfo lCh[2];






   CmLteRlcMode entMode;
   U8 dir;





   S16 discardTmr;


   SpId rguSapId;

   union
   {
      CkwUmInfo umInfo;
      CkwAmInfo amInfo;
      CkwTmInfo tmInfo;
   }m;
}CkwEntCfgInfo;



typedef struct ckwCfgInfo
{
   U32 transId;
   CmLteRnti ueId;
   CmLteCellId cellId;
   U8 numEnt;

   CkwEntCfgInfo entCfg[24];

}CkwCfgInfo;



typedef struct ckwEntCfgCfmInfo
{
   U8 rbId;
   U8 rbType;
   CmStatus status;

   U8 cfgType;

}CkwEntCfgCfmInfo;



typedef struct ckwCfgCfmInfo
{
   U32 transId;
   CmLteRnti ueId;
   CmLteCellId cellId;
   U8 numEnt;
   CkwEntCfgCfmInfo entCfgCfm[24];

}CkwCfgCfmInfo;



typedef struct ckwUeInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
}CkwUeInfo;



typedef S16 (*CkwCfgReq) (Pst *pst, SpId spId, CkwCfgInfo *cfgInfo);
typedef S16 (*CkwCfgCfm) (Pst *pst, SuId suId, CkwCfgCfmInfo *cfmInfo);

typedef S16 (*CkwUeIdChgReq) (Pst *pst, SpId spId, U32 transId, CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo)
                                                                            ;
typedef S16 (*CkwUeIdChgCfm) (Pst *pst, SuId suId, U32 transId, CkwUeInfo *ueInfo, CmStatus status)
                                                                       ;

typedef S16 (*CkwBndReq) (Pst *pst, SuId suId, SpId spId);
typedef S16 (*CkwBndCfm) (Pst *pst, SuId suId, U8 status);
typedef S16 (*CkwUbndReq) (Pst *pst, SpId spId, Reason reason);
extern S16 KwUiCkwBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 KwUiCkwBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 KwUiCkwUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 KwUiCkwCfgReq (Pst *pst, SpId spId, CkwCfgInfo *cfgInfo);
extern S16 KwUiCkwCfgCfm (Pst *pst, SuId suId, CkwCfgCfmInfo *cfmInfo);
extern S16 KwUiCkwUeIdChgReq (Pst *pst, SpId spId, U32 transId, CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo)
                                                                            ;
extern S16 KwUiCkwUeIdChgCfm (Pst *pst, SuId suId, U32 transId, CkwUeInfo *ueInfo, CmStatus status)
                                                                       ;
extern S16 cmPkCkwTmInfo ( CkwTmInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCkwUmInfo ( CkwEntCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCkwAmInfo ( CkwAmInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCkwLChInfo ( CkwLChInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCkwEntCfgInfo ( CkwEntCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCkwCfgInfo ( CkwCfgInfo *param, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkCkwEntCfgCfmInfo ( CkwEntCfgCfmInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCkwCfgCfmInfo ( CkwCfgCfmInfo *param, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkCkwUeInfo ( CkwUeInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkCkwBndReq ( Pst *pst, SuId suId, SpId spId )



  ;

extern S16 cmPkCkwUbndReq ( Pst *pst, SpId spId, Reason reason )



  ;

extern S16 cmPkCkwBndCfm ( Pst *pst, SuId suId, U8 status )



  ;

extern S16 cmPkCkwCfgReq ( Pst *pst, SpId spId, CkwCfgInfo *cfgInfo )



  ;

extern S16 cmPkCkwCfgCfm ( Pst *pst, SuId suId, CkwCfgCfmInfo *cfgCfmInfo )



  ;

extern S16 cmPkCkwUeIdChgReq ( Pst *pst, SpId spId, U32 transId, CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo )





  ;

extern S16 cmPkCkwUeIdChgCfm ( Pst *pst, SuId suId, U32 transId, CkwUeInfo *ueInfo, CmStatus status )





  ;


extern S16 cmUnpkCkwTmInfo ( CkwTmInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCkwUmInfo ( CkwEntCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCkwAmInfo ( CkwAmInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCkwLInfo ( CkwLChInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCkwCfgCfmInfo ( CkwCfgCfmInfo *param, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCkwBndReq ( CkwBndReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCkwLChInfo ( CkwLChInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCkwEntCfgInfo ( CkwEntCfgInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCkwCfgInfo ( CkwCfgInfo *param, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCkwUeInfo ( CkwUeInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCkwCfgCfm ( CkwCfgCfm func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCkwUbndReq ( CkwUbndReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCkwBndCfm ( CkwBndCfm func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCkwCfgReq ( CkwCfgReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCkwEntCfgCfmInfo ( CkwEntCfgCfmInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkCkwUeIdChgReq ( CkwUeIdChgReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkCkwUeIdChgCfm ( CkwUeIdChgCfm func, Pst *pst, Buffer *mBuf )



  ;
typedef struct kwuDatReqInfo
{
   CmLteRlcId rlcId;
   U32 sduId;

   CmLteLcType lcType;
   union
   {
      CmLteTimingInfo tmg;
      CmLteRnti rnti;
   }tm;

}KwuDatReqInfo;


typedef struct kwuDatIndInfo
{
   CmLteRlcId rlcId;

   CmLteRnti tCrnti;

   Bool isOutOfSeq;
}KwuDatIndInfo;



typedef struct kwuDatCfmInfo
{
  CmLteRlcId rlcId;
  U32 numSduIds;
  U32 sduIds[1024];
}KwuDatCfmInfo;


typedef KwuDatCfmInfo KwuDiscSduInfo;


typedef struct kwuStaIndInfo
{
   CmLteRlcId rlcId;
   U32 numSdu;
   U32 sduId[100];
}KwuStaIndInfo;

typedef struct kwuFlowCntrlIndInfo
{
   CmLteRlcId rlcId;
   U32 pktAdmitCnt;
}KwuFlowCntrlIndInfo;
typedef S16 (*KwuBndReq) (Pst *pst, SuId suId, SpId spId);
typedef S16 (*KwuBndCfm) (Pst *pst, SuId suId, U8 status);
typedef S16 (*KwuUbndReq) (Pst *pst, SuId suId, Reason reason);

typedef S16 (*KwuDatReq) (Pst *pst, SpId spId, KwuDatReqInfo* datReq, Buffer *mBuf)
                       ;
typedef S16 (*KwuDatInd) (Pst *pst, SuId suId, KwuDatIndInfo* datInd, Buffer *mBuf)
                       ;
typedef S16 (*KwuDatCfm) (Pst *pst, SuId suId, KwuDatCfmInfo* datCfm);
typedef S16 (*KwuDiscSduReq) (Pst *pst, SpId spId, KwuDiscSduInfo* discSdu);
typedef S16 (*KwuStaInd) (Pst *pst, SuId suId, KwuStaIndInfo* staInd);
typedef S16 (*KwuFlowCntrlInd)(Pst *pst, SuId suId, KwuFlowCntrlIndInfo* flowCntrlInd);
typedef S16 (*KwuReEstCmpInd) (Pst *pst, SuId suId, CmLteRlcId rlcId);





typedef S16 (*KwuDiscSduCfm) (Pst *pst, SuId suId, KwuDiscSduInfo *discCfmInfo);
extern S16 KwUiKwuBndReq (Pst *pst, SuId suId, SpId spId)

                    ;
extern S16 KwUiKwuBndCfm (Pst *pst, SuId suId, U8 status)

                    ;
extern S16 KwUiKwuUbndReq (Pst *pst, SpId spId, Reason reason)

                        ;
extern S16 KwUiKwuDatReq (Pst *pst, SpId spId, KwuDatReqInfo* datReq, Buffer *buf)


                      ;
extern S16 KwUiKwuDatInd (Pst *pst, SuId suId, KwuDatIndInfo* datInd, Buffer *mBuf)


                       ;
extern S16 KwUiKwuDatCfm (Pst *pst, SuId suId, KwuDatCfmInfo* datCfm)

                                ;
extern S16 KwUiKwuDiscSduReq (Pst *pst, SpId spId, KwuDiscSduInfo* discSdu)

                                  ;
extern S16 KwUiKwuStaInd (Pst *pst, SuId suId, KwuStaIndInfo* staInd)

                                ;
extern S16 KwUiKwuDiscSduCfm (Pst *pst, SpId spId, KwuDiscSduInfo* discCfmSdu)

                                     ;
extern S16 KwUiKwuFlowCntrlInd (Pst *pst, SuId suId, KwuFlowCntrlIndInfo* flowCntrlIndInfo)

                                                ;
extern S16 KwUiKwuReEstCmpInd (Pst *pst, SuId suId, CmLteRlcId rlcId )


  ;
extern S16 PjLiKwuBndReq (Pst *pst, SuId suId, SpId spId)

                    ;

extern S16 PjLiKwuBndCfm (Pst *pst, SuId suId, U8 status)

                    ;

extern S16 PjLiKwuUbndReq (Pst *pst, SpId spId, Reason reason)

                        ;

extern S16 PjLiKwuDatReq (Pst *pst, SpId spId, KwuDatReqInfo* datReq, Buffer *buf)


                      ;

extern S16 PjLiKwuDatInd (Pst *pst, SuId suId, KwuDatIndInfo* datInd, Buffer *buf)


                      ;

extern S16 PjLiKwuDatCfm (Pst *pst, SuId suId, KwuDatCfmInfo* datCfm)

                                ;

extern S16 PjLiKwuStaInd (Pst *pst, SuId suId, KwuStaIndInfo* staInd)

                                ;

extern S16 PjLiKwuDiscSduReq (Pst *pst, SpId spId, KwuDiscSduInfo* discSdu)

                                  ;


extern S16 PjLiKwuReEstCmpInd (Pst *pst, SuId suId, CmLteRlcId rlcId)
                                      ;


extern S16 PjLiKwuDiscSduCfm (Pst *pst, SpId spId, KwuDiscSduInfo* discCfmSdu)

                                     ;
extern S16 PjLiKwuFlowCntrlInd (Pst *pst, SuId suId, KwuFlowCntrlIndInfo *flowCntrlInfo)

                                             ;
extern S16 cmPkKwuDatReqInfo ( KwuDatReqInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkKwuDatIndInfo ( KwuDatIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkKwuDatCfmInfo ( KwuDatCfmInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkKwuStaIndInfo ( KwuStaIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkKwuBndReq ( Pst * pst, SuId suId, SpId spId )



  ;

extern S16 cmPkKwuUbndReq ( Pst * pst, SuId suId, Reason reason )



  ;

extern S16 cmPkKwuBndCfm ( Pst * pst, SuId suId, U8 status )



  ;

extern S16 cmPkKwuDatReq ( Pst * pst, SpId spId, KwuDatReqInfo* datReq, Buffer * mBuf )




  ;

extern S16 cmPkKwuDatInd ( Pst * pst, SuId suId, KwuDatIndInfo* datInd, Buffer * mBuf )




  ;

extern S16 cmPkKwuDatCfm ( Pst * pst, SuId suId, KwuDatCfmInfo* datCfm )



  ;

extern S16 cmPkKwuStaInd ( Pst * pst, SuId suId, KwuStaIndInfo* staInd )



  ;

extern S16 cmPkKwuReEstCmpInd ( Pst * pst, SuId suId, CmLteRlcId rlcId )



  ;

extern S16 cmPkKwuDiscSduReq ( Pst * pst, SpId spId, KwuDiscSduInfo* discSdu )



  ;
extern S16 cmPkKwuDiscSduCfm ( Pst * pst, SpId spId, KwuDiscSduInfo* cfmSdu )



  ;

extern S16 cmPkKwuFlowCntrlInd ( Pst *pst, SuId suId, KwuFlowCntrlIndInfo *flowCntrlIndInfo )



  ;


extern S16 cmUnpkKwuDatReqInfo ( KwuDatReqInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkKwuDatIndInfo ( KwuDatIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkKwuDatCfmInfo ( KwuDatCfmInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkKwuStaIndInfo ( KwuStaIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkKwuBndReq ( KwuBndReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkKwuUbndReq ( KwuUbndReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkKwuBndCfm ( KwuBndCfm func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkKwuDatReq ( KwuDatReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkKwuDatInd ( KwuDatInd func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkKwuDatCfm ( KwuDatCfm func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkKwuStaInd ( KwuStaInd func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkKwuReEstCmpInd ( KwuReEstCmpInd func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmUnpkKwuDiscSduReq ( KwuDiscSduReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmUnpkKwuFlowCntrlInd ( KwuFlowCntrlInd func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmUnpkKwuDiscSduCfm ( KwuDiscSduCfm func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkKwuFlowCntrlIndInfo ( KwuFlowCntrlIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkKwuFlowCntrlIndInfo ( KwuFlowCntrlIndInfo *param, Buffer *mBuf )


  ;
typedef struct rguPduInfo
{
   U8 numPdu;
   Buffer *mBuf[4];
} RguPduInfo;





typedef struct rguDBoReport
{
   S32 bo;

   U16 estRlcHdrSz;
   Bool staPduPrsnt;


   U32 staPduBo;

   U32 oldestSduArrTime;
} RguDBoReport;




typedef struct rguCDatReqInfo
{
   CmLteCellId cellId;
   CmLteLcId lcId;
   CmLteLcType lcType;
   U32 transId;
   union{
   CmLteTimingInfo timeToTx;

   CmLteRnti rnti;
   }u;
   Buffer *pdu;
} RguCDatReqInfo;



typedef struct rguLchDatReq
{
   CmLteLcId lcId;
   RguDBoReport boReport;
   RguPduInfo pdu;
   Bool setMaxUlPrio;




} RguLchDatReq;
typedef struct rguDatReqTb
{
   U8 nmbLch;

   RguLchDatReq lchData[10];






}RguDatReqTb;




typedef struct rguDDatReqPerUe
{
   CmLteRnti rnti;
   U32 transId;
   U8 nmbOfTbs;
   RguDatReqTb datReqTb[2];
} RguDDatReqPerUe;




typedef struct rguDDatReqInfo
{
   CmLteCellId cellId;
   U8 nmbOfUeGrantPerTti;
   RguDDatReqPerUe datReq[8];
} RguDDatReqInfo;




typedef struct rguCDatIndInfo
{
   CmLteCellId cellId;
   CmLteRnti rnti;
   CmLteLcId lcId;
   Buffer *pdu;
} RguCDatIndInfo;
typedef struct rguLchDatInd
{
   CmLteLcId lcId;
   RguPduInfo pdu;

}RguLchDatInd;




typedef struct rguDDatIndInfo
{
   CmLteCellId cellId;
   CmLteRnti rnti;
   U8 numLch;

   RguLchDatInd lchData[10];




} RguDDatIndInfo;




typedef struct rguCStaRspInfo
{
   CmLteCellId cellId;
   CmLteLcId lcId;
   CmLteLcType lcType;
   S32 bo;
   union

   {
      CmLteTimingInfo timeToTx;

      CmLteRnti rnti;
   } u;
} RguCStaRspInfo;




typedef struct rguDStaRspInfo
{

   Pst post;

   CmLteCellId cellId;
   CmLteRnti rnti;
   CmLteLcId lcId;
   RguDBoReport boReport;
} RguDStaRspInfo;




typedef struct rguCStaIndInfo
{
   CmLteCellId cellId;
   CmLteLcId lcId;
   U32 transId;
   CmLteRnti rnti;
} RguCStaIndInfo;




typedef struct rguLchStaInd
{
   CmLteLcId lcId;
   S16 totBufSize;

} RguLchStaInd;




typedef struct rguStaIndTb
{
   U8 nmbLch;

   RguLchStaInd lchStaInd[10];





}RguStaIndTb;



typedef struct rguDStaIndPerUe
{
   CmLteRnti rnti;
   U32 transId;
   U8 nmbOfTbs;
   RguStaIndTb staIndTb[2];
   Bool fillCtrlPdu;
} RguDStaIndPerUe;




typedef struct rguDStaIndInfo
{
   CmLteCellId cellId;
   U8 nmbOfUeGrantPerTti;
   RguDStaIndPerUe staInd[8];
} RguDStaIndInfo;




typedef struct rguLcFlowCntrlInfo
{
  CmLteLcId lcId;
  U32 pktAdmitCnt;
  U32 maxBo4FlowCtrl;
}RguLcFlowCntrlInfo;




typedef struct rguUeFlowCntrlInfo
{
  CmLteRnti ueId;
  U32 numLcs;
  RguLcFlowCntrlInfo lcInfo[10];
}RguUeFlowCntrlInfo;




typedef struct rguFlowCntrlInd
{
   CmLteCellId cellId;
   U32 numUes;
   RguUeFlowCntrlInfo ueFlowCntrlInfo[8];
}RguFlowCntrlInd;
typedef struct rguInfoRingElem
{
  SpId spId;
  U8 event;
  Void *msg;
}RguInfoRingElem;




typedef S16 (*RguBndReq) ( Pst* pst, SuId suId, SpId spId)


                              ;

typedef S16 (*RguUbndReq) ( Pst* pst, SpId spId, Reason reason)


                                ;


typedef S16 (*RguBndCfm) ( Pst* pst, SuId suId, U8 status)


                                ;


typedef S16 (*RguCDatReq) ( Pst* pst, SpId spId, RguCDatReqInfo * datReq)


                                ;


typedef S16 (*RguDDatReq) ( Pst* pst, SpId spId, RguDDatReqInfo * datReq)


                                ;


typedef S16 (*RguCDatInd) ( Pst* pst, SuId suId, RguCDatIndInfo * datInd)


                                ;


typedef S16 (*RguDDatInd) ( Pst* pst, SuId suId, RguDDatIndInfo * datInd)


                                ;


typedef S16 (*RguCStaRsp) ( Pst* pst, SpId spId, RguCStaRspInfo * staRsp)


                                ;


typedef S16 (*RguDStaRsp) ( Pst* pst, SpId spId, RguDStaRspInfo * staRsp)


                                ;


typedef S16 (*RguCStaInd) ( Pst* pst, SuId suId, RguCStaIndInfo * staInd)


                                ;


typedef S16 (*RguDStaInd) ( Pst* pst, SuId suId, RguDStaIndInfo * staInd)


                                ;

typedef S16 (*RguFlowCntrlIndInfo) ( Pst *pst, SuId suId, RguFlowCntrlInd *flowCntrlInd)


                                       ;
extern S16 RgUiRguBndReq (Pst* pst,SuId suId,SpId spId);






extern S16 RgUiRguUbndReq (Pst* pst,SpId spId,Reason reason);







extern S16 RgUiRguBndCfm (Pst* pst,SuId suId,U8 status);







extern S16 RgUiRguCDatReq (Pst* pst,SpId spId,RguCDatReqInfo *datReq);







extern S16 RgUiRguDDatReq (Pst* pst,SpId spId,RguDDatReqInfo *datReq);







extern S16 RgUiRguCDatInd (Pst* pst,SuId suId,RguCDatIndInfo *datInd);







extern S16 RgUiRguDDatInd (Pst* pst,SuId suId,RguDDatIndInfo *datInd);







extern S16 RgUiRguCStaRsp (Pst* pst,SpId spId,RguCStaRspInfo *staRsp);







extern S16 RgUiRguDStaRsp (Pst* pst,SpId spId,RguDStaRspInfo *staRsp);







extern S16 RgUiRguCStaInd (Pst* pst,SuId suId,RguCStaIndInfo *staInd);







extern S16 RgUiRguDStaInd (Pst* pst,SuId suId,RguDStaIndInfo *staInd);

extern S16 RgUiRguFlowCntrlInd (Pst *pst, SuId suId, RguFlowCntrlInd *flowCntrlInd)
                               ;
extern S16 KwLiRguBndReq ( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 KwLiRguUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;


extern S16 KwLiRguBndCfm ( Pst* pst, SuId suId, U8 status )



  ;


extern S16 KwLiRguCDatReq ( Pst* pst, SpId spId, RguCDatReqInfo * datReq )



  ;


extern S16 KwLiRguDDatReq ( Pst* pst, SpId spId, RguDDatReqInfo * datReq )



  ;


extern S16 KwLiRguCDatInd ( Pst* pst, SuId suId, RguCDatIndInfo * datInd )



  ;


extern S16 KwLiRguDDatInd ( Pst* pst, SuId suId, RguDDatIndInfo * datInd )



  ;


extern S16 KwLiRguCStaRsp ( Pst* pst, SpId spId, RguCStaRspInfo * staRsp )



  ;


extern S16 KwLiRguDStaRsp ( Pst* pst, SpId spId, RguDStaRspInfo * staRsp )



  ;




extern S16 KwLiRguCStaInd ( Pst* pst, SuId suId, RguCStaIndInfo * staInd )



  ;




extern S16 KwLiRguDStaInd ( Pst* pst, SuId suId, RguDStaIndInfo * staInd )



  ;
extern S16 KwLiRguFlowCntrlInd ( Pst *pst, SuId suId, RguFlowCntrlInd *flowCntrlInd )



  ;




extern S16 cmPkRguBndReq ( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 cmUnpkRguBndReq ( RguBndReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRguUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;

extern S16 cmUnpkRguUbndReq ( RguUbndReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRguBndCfm ( Pst* pst, SuId suId, U8 status )



  ;


extern S16 cmUnpkRguBndCfm ( RguBndCfm func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRguCDatReq ( Pst* pst, SpId spId, RguCDatReqInfo * datReq )



  ;


extern S16 cmUnpkRguCDatReq ( RguCDatReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRguDDatReq ( Pst* pst, SpId spId, RguDDatReqInfo * datReq )



  ;


extern S16 cmUnpkRguDDatReq ( RguDDatReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRguCDatInd ( Pst* pst, SuId suId, RguCDatIndInfo * datInd )



  ;


extern S16 cmUnpkRguCDatInd ( RguCDatInd func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRguDDatInd ( Pst* pst, SuId suId, RguDDatIndInfo * datInd )



  ;


extern S16 cmUnpkRguDDatInd ( RguDDatInd func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRguCStaRsp ( Pst* pst, SpId spId, RguCStaRspInfo * staRsp )



  ;


extern S16 cmUnpkRguCStaRsp ( RguCStaRsp func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRguDStaRsp ( Pst* pst, SpId spId, RguDStaRspInfo * staRsp )



  ;


extern S16 cmUnpkRguDStaRsp ( RguDStaRsp func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkRguCStaInd ( Pst* pst, SuId suId, RguCStaIndInfo * staInd )



  ;




extern S16 cmUnpkRguCStaInd ( RguCStaInd func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkRguDStaInd ( Pst* pst, SuId suId, RguDStaIndInfo * staInd )



  ;
extern S16 cmPkRguFlowCntrlInfo ( RguFlowCntrlInd *param, Buffer *mBuf )


  ;
extern S16 cmPkRguUeFlowCntrlInfo ( RguUeFlowCntrlInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRguLcFlowCntrlInfo ( RguLcFlowCntrlInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguLcFlowCntrlInfo ( RguLcFlowCntrlInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguUeFlowCntrlInfo ( RguUeFlowCntrlInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguFlowCntrlInfo ( RguFlowCntrlInd *param, Buffer *mBuf )


  ;




extern S16 cmUnpkRguDStaInd ( RguDStaInd func, Pst* pst, Buffer *mBuf )



  ;
extern S16 cmPkRguPduInfo ( RguPduInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguPduInfo ( RguPduInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRguDBoReport ( RguDBoReport *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguDBoReport ( RguDBoReport *param, Buffer *mBuf )


  ;

extern S16 cmPkRguCDatReqInfo ( RguCDatReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguCDatReqInfo ( RguCDatReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRguLchDatReq ( RguLchDatReq *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguLchDatReq ( RguLchDatReq *param, Buffer *mBuf )


  ;
extern S16 cmPkRguDatReqTb ( RguDatReqTb *param, Buffer *mBuf )


  ;
extern S16 cmPkRguStaIndTb ( RguStaIndTb *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguStaIndTb ( RguStaIndTb *param, Buffer *mBuf )


  ;
extern S16 cmPkRguDDatReqInfo ( RguDDatReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguDDatReqInfo ( RguDDatReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguDatReqTb ( RguDatReqTb *param, Buffer *mBuf )


  ;

extern S16 cmPkRguCDatIndInfo ( RguCDatIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguCDatIndInfo ( RguCDatIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRguLchDatInd ( RguLchDatInd *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguLchDatInd ( RguLchDatInd *param, Buffer *mBuf )


  ;
extern S16 cmPkRguDDatIndInfo ( RguDDatIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguDDatIndInfo ( RguDDatIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkRguCStaRspInfo ( RguCStaRspInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguCStaRspInfo ( RguCStaRspInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRguDStaRspInfo ( RguDStaRspInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguDStaRspInfo ( RguDStaRspInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRguCStaIndInfo ( RguCStaIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguCStaIndInfo ( RguCStaIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRguLchStaInd ( RguLchStaInd *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguLchStaInd ( RguLchStaInd *param, Buffer *mBuf )


  ;
extern S16 cmPkRguDStaIndInfo ( RguDStaIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguDStaIndInfo ( RguDStaIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRguFlowCntrlInd ( RguFlowCntrlIndInfo func, Pst *pst, Buffer *mBuf )



   ;

extern S16 cmPkRguFlowCntrlInd ( Pst* pst, SuId suId, RguFlowCntrlInd *flowCntrlInd )



   ;

typedef U16 KwSn;

typedef RguDDatIndInfo KwDatIndInfo;

typedef RguDStaIndInfo KwDStaIndInfo;

typedef RguPduInfo KwPduInfo;
typedef struct _amRlcStats
{
   U32 numDLStaPduSent;
   U32 numDLNacksInStaPdu;
   U32 numDLBytesUnused;
   U32 numDLPollTimerExpiresSrb;
   U32 numDLPollTimerExpiresDrb;
   U32 numDLMaxRetx;
   U32 numDLRetransPdus;
   U32 numULPdusDiscarded;
   U32 numULReOrdTimerExpires;
   U32 numULStaPduRcvd;
   U32 numULNackInStaPduRcvd;
}AMRLCStats;

typedef struct _umRlcStats
{
   U32 numDLBytesUnused;
   U32 numDLMaxRetx;
   U32 numULPdusDiscarded;
   U32 numULReOrdTimerExpires;
   U32 numULPdusOutsideWindow;
}UMRLCStats;

typedef struct _rlcStats
{
   AMRLCStats amRlcStats;
   UMRLCStats umRlcStats;
}RLCStats;

extern RLCStats gRlcStats;
typedef struct kwUmHdr
{
   U8 fi;
   KwSn sn;
   U16 numLi;
   U16 li[(2 * 100)];
}KwUmHdr;
typedef struct kwAmHdr
{
   U8 dc;
   U8 rf;
   U8 p;
   U8 fi;
   U8 e;
   U8 lsf;
   KwSn sn;
   U16 so;
   U16 numLi;
   U16 li[(2 * 100)];
}KwAmHdr;


typedef struct kwCntrlInfo
{
   U16 val;
   U8 len;
   U16 idx;
   U8 emtBits;
   U16 e1Idx;
   U16 e2Idx;
   U8 e1eb;
}KwCntrlInfo;

typedef struct kwHdrInfo
{
   U16 val;
   U8 len;
   U8 eb;
   U8 *hdr;
   U16 idx;
   U8 pEb;
   U8 pLen;
}KwHdrInfo;

typedef struct kwExtHdr
{
   U16 val;
   U16 len;
   U8 hdr;
   U8 pLen;
}KwExtHdr;
typedef struct kwLchInfo
{
   CmLteLcId lChId;
   CmLteLcType lChType;
}KwLchInfo;
typedef struct kwUeKey
{
   CmLteRnti ueId;
   CmLteCellId cellId;
}KwUeKey;
typedef struct kwCkwSapCb
{
   Pst pst;
   SpId spId;
   SuId suId;
   U8 state;
   KwCkwCntSts sts;
}KwCkwSapCb;
typedef struct kwKwuSapCb
{
   Pst pst;
   SpId spId;
   SuId suId;
   U8 state;
   KwKwuSapSts sts;
}KwKwuSapCb;
typedef struct kwRguSapCb
{
   Pst pst;
   SpId spId;
   SuId suId;
   U8 state;
   CmTimer bndTmr;
   U16 bndTmrInt;
   U8 retryCnt;
}KwRguSapCb;
typedef struct kwUdxUlSapCb
{
   Pst pst;
   SpId spId;
   SuId suId;
   U8 state;
   CmTimer bndTmr;
   U16 bndTmrInt;
   U8 retryCnt;
}KwUdxUlSapCb;
typedef struct kwUdxDlSapCb
{
   Pst pst;
   SpId spId;
   SuId suId;
   U8 state;
}KwUdxDlSapCb;
typedef struct kwDlDataToBeFreed
{
   CmLListCp sduLst;
   CmLListCp txLst;
   CmLListCp reTxLst;
   CmLListCp rbLst;
}KwDlDataToBeFreed;
typedef struct _kwDlCb
{
   U8 numKwuSaps;
   U8 numUdxSaps;
   KwKwuSapCb *kwuDlSap;
   KwUdxDlSapCb *udxDlSap;
   KwRguSapCb *rguDlSap;
   CmHashListCp cellLstCp;
   CmHashListCp ueLstCp;
   KwDlDataToBeFreed toBeFreed;
   Pst selfPst;
   Buffer *selfPstMBuf;
   Bool shutdownReceived;
   Bool eventInQueue;



}KwDlCb;
typedef struct _kwUlCb
{
   KwCkwSapCb ckwSap;
   U8 numKwuSaps;
   U8 numUdxSaps;
   KwUdxUlSapCb *udxUlSap;
   KwKwuSapCb *kwuUlSap;
   KwRguSapCb *rguUlSap;
   CmHashListCp cellLstCp;
   CmHashListCp ueLstCp;
   CmHashListCp transIdLstCp;




}KwUlCb;
typedef struct _kwCb
{
   TskInit init;
   KwGenCfg genCfg;
   KwGenSts genSts;
   S16 trcLen;
   U8 trcMask;
   CmTqType kwTq[10];
   CmTqCp kwTqCp;
   union
   {
      KwUlCb *ulCb;
      KwDlCb *dlCb;
   } u;
}KwCb;

extern KwCb *kwCb[2];




extern S16 kwGetSId (SystemId *s);

extern Void kwTmrExpiry (U32 cb, S16 tmrEvnt);

extern S16 kwLmmSendTrc (KwCb *gCb, Event event, Buffer *mBuf);

extern Void kwStartTmr (KwCb *gCb, U32 cb, S16 tmrEvnt);

extern Void kwStopTmr (KwCb *gCb, U32 cb, U8 tmrType);

extern Bool kwChkTmr (KwCb *gCb,U32 cb, S16 tmrEvnt);
extern Void kwLmmSendAlarm (KwCb *gCb, U16 category, U16 event, U16 cause, SuId suId, U32 ueId)




                                            ;
typedef struct kwNackInfo
{
   U8 isSegment;
   U16 sn;
   U16 soStart;
   U16 soEnd;
}KwNackInfo;

typedef struct kwUdxStaPdu
{
   U16 ackSn;




   U8 nackCnt;
   KwNackInfo nackInfo[100];
}KwUdxStaPdu;

typedef struct kwUdxBufLst
{
   CmLListCp rlsTxLst;
   CmLListCp rlsRetxLst;
   CmLListCp rlsSduLst;
}KwUdxBufLst;
typedef struct kwStatusPdu
{
   U16 ackSn;
   KwNackInfo nackInfo[100];
   U16 nackCount;
   U16 controlBo;
}KwUdxDlStaPdu;
typedef S16 (*UdxBndCfm) (Pst* pst, SuId suId,U8 status );

typedef S16 (*UdxBndReq) (Pst* pst, SuId suId,SpId spId );

typedef S16 (*UdxUbndReq) (Pst* pst, SuId suId,Reason reason);

typedef S16 (*UdxCfgReq) (Pst *pst, SpId spId, CkwCfgInfo *cfgInfo);

typedef S16 (*UdxCfgCfm) (Pst* pst,SuId suId,CkwCfgCfmInfo *cfmInfo);

typedef S16 (*UdxStaUpdReq) (Pst* pst, SpId spId, CmLteRlcId *rlcId, KwUdxStaPdu *pStaPdu )


                                                         ;

typedef S16 (*UdxUeIdChgReq) (Pst *pst, SpId spId, U32 transId, CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo)



                                                         ;

typedef S16 (*UdxUeIdChgCfm) (Pst *pst, SuId suId, U32 transId, CmStatus status)


                                                    ;

typedef S16 (*UdxStaUpdCfm) (Pst* pst, SuId suId, CmLteRlcId *rlcId, KwUdxBufLst *pBufLst)


                                                        ;

typedef S16 (*UdxStaPduReq) (Pst* pst, SpId spId, CmLteRlcId *rlcId, KwUdxDlStaPdu *pStaPdu)


                                                          ;

typedef S16 (*UdxStaProhTmrStart) (Pst* pst, SuId suId, CmLteRlcId *rlcId)

                                                             ;
extern S16 cmPkUdxBndCfm (Pst* pst, SuId suId,U8 status );
extern S16 cmPkUdxBndReq (Pst* pst, SuId suId,SpId spId );
extern S16 cmPkUdxUbndReq (Pst* pst, SuId suId,Reason reason);
extern S16 cmPkUdxCfgReq (Pst *pst, SpId spId, CkwCfgInfo *cfgInfo);
extern S16 cmPkUdxCfgCfm ( Pst* pst,SuId suId,CkwCfgCfmInfo *cfmInfo);
extern S16 cmPkUdxStaUpdReq (Pst* pst,SpId spId,CmLteRlcId *rlcId, KwUdxStaPdu *pStaPdu )
                                                              ;
extern S16 cmPkUdxUeIdChgReq (Pst *pst, SpId spId, U32 transId, CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo)
                                                                           ;




extern S16 cmPkUdxUeIdChgCfm (Pst *pst, SuId suId, U32 transId, CmStatus status)
                                                    ;




extern S16 cmPkUdxStaUpdCfm (Pst* pst,SuId suId,CmLteRlcId *rlcId, KwUdxBufLst *pBufLst)
                                                    ;

extern S16 cmPkUdxStaPduReq ( Pst* pst,SpId spId, CmLteRlcId *rlcId, KwUdxDlStaPdu *pStaPdu )
                                                       ;
extern S16 cmPkUdxStaProhTmrStart (Pst *pst, SpId spId, CmLteRlcId *rlcId)

                                                           ;







extern S16 cmUnpkUdxBndCfm (UdxBndCfm func,Pst* pst, Buffer *mBuf );
extern S16 cmUnpkUdxBndReq (UdxBndReq func,Pst* pst, Buffer *mBuf );
extern S16 cmUnpkUdxUbndReq (UdxUbndReq func,Pst* pst, Buffer *mBuf);
extern S16 cmUnpkUdxCfgReq (UdxCfgReq func,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkUdxCfgCfm (UdxCfgCfm func , Pst* pst,Buffer *mBuf);
extern S16 cmUnpkUdxStaUpdReq (UdxStaUpdReq func,Pst* pst,Buffer *mBuf);
extern S16 cmUnpkUdxUeIdChgReq (UdxUeIdChgReq func,Pst *pst, Buffer *mBuf);
extern S16 cmUnpkUdxUeIdChgCfm (UdxUeIdChgCfm func,Pst *pst, Buffer *mBuf);

extern S16 cmUnpkUdxStaUpdCfm (UdxStaUpdCfm func,Pst* pst,Buffer *mBuf);

extern S16 cmUnpkUdxStaPduReq (UdxStaPduReq func, Pst* pst, Buffer *mBuf);

extern S16 cmUnpkUdxStaProhTmrStart (UdxStaProhTmrStart func, Pst* pst, Buffer *mBuf)

                                                        ;
extern S16 KwUlUdxBndReq (Pst* pst, SuId suId, SpId spId);

extern S16 KwDlUdxBndReq (Pst* pst, SuId suId, SpId spId);

extern S16 KwDlUdxBndCfm (Pst* pst, SuId suId, U8 status);

extern S16 KwUlUdxBndCfm (Pst* pst, SuId suId, U8 status);

extern S16 KwDlUdxCfgCfm (Pst* pst, SuId suId, CkwCfgCfmInfo *cfmInfo);

extern S16 KwUlUdxCfgCfm (Pst* pst, SuId suId, CkwCfgCfmInfo *cfmInfo);

extern S16 KwDlUdxUeIdChgCfm (Pst *pst, SuId suId, U32 transId, CmStatus status)


                                                    ;

extern S16 KwUlUdxUeIdChgCfm (Pst *pst, SuId suId, U32 transId, CmStatus status)


                                                    ;

extern S16 KwUlUdxUbndReq (Pst* pst, SuId suId, Reason reason);

extern S16 KwDlUdxUbndReq (Pst* pst, SuId suId, Reason reason);

extern S16 KwUlUdxUeIdChgReq (Pst *pst, SpId spId, U32 transId, CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo)



                                                         ;

extern S16 KwUlUdxCfgReq (Pst *pst, SpId spId, CkwCfgInfo *cfgInfo);

extern S16 KwDlUdxCfgReq (Pst *pst, SpId spId, CkwCfgInfo *cfgInfo);

extern S16 KwUlUdxStaUpdReq (Pst* pst, SpId spId, CmLteRlcId *rlcId, KwUdxStaPdu *pStaPdu)


                                                        ;

extern S16 KwDlUdxStaUpdReq (Pst* pst, SpId spId, CmLteRlcId *rlcId, KwUdxStaPdu *pStaPdu)


                                                        ;

extern S16 KwDlUdxStaUpdCfm (Pst* pst, SuId suId, CmLteRlcId *rlcId, KwUdxBufLst *pBufLst)


                                                        ;

extern S16 KwUlUdxStaUpdCfm (Pst* pst, SuId suId, CmLteRlcId *rlcId, KwUdxBufLst *pBufLst)


                                                        ;

extern S16 KwUlUdxStaPduReq (Pst *pst, SpId spId, CmLteRlcId *rlcId, KwUdxDlStaPdu *pStaPdu )


                                                           ;

extern S16 KwDlUdxStaPduReq (Pst *pst, SpId spId, CmLteRlcId *rlcId, KwUdxDlStaPdu *pStaPdu)


                                                          ;

extern S16 KwDlUdxUeIdChgReq (Pst *pst, SpId spId, U32 transId, CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo)



                                                         ;

extern S16 KwDlUdxCfgReq (Pst *pst, SpId spId, CkwCfgInfo *cfgInfo);


extern S16 KwUlUdxStaUpdCfm (Pst* pst, SuId suId, CmLteRlcId *rlcId, KwUdxBufLst *pBufLst)


                                                        ;

extern S16 KwDlUdxStaPduReq (Pst *pst, SpId spId, CmLteRlcId *rlcId, KwUdxDlStaPdu *pStaPdu)


                                                          ;

extern S16 KwUlUdxStaProhTmrStart (Pst *pst, SpId spId, CmLteRlcId *rlcId )

                                                            ;

extern S16 KwDlUdxStaProhTmrStart (Pst *pst, SpId spId, CmLteRlcId *rlcId )

                                                            ;
typedef struct tsInfL2CellStats
{
   U32 cellId;
   struct schCellStats{
      U32 msg4Fail;
      U32 msg3Fail;
      U32 dlSumCw0Cqi;
      U32 dlNumCw0Cqi;
      U32 dlSumCw1Cqi;
      U32 dlNumCw1Cqi;
      U32 dlSumCw0iTbs;
      U32 dlNumCw0iTbs;
      U32 dlSumCw1iTbs;
      U32 dlNumCw1iTbs;
      U32 riCnt[4];
      U32 dlNack[2][4];
      U32 dlAckNack[2][4];
      U32 dlDtx[2][4];
      U32 ulNack[4];
      U32 ulAckNack[4];
      U32 ulDtx[4];
      U32 dlPrbUsage[10];
      U32 ulPrbUsage[10];
      U32 dlPdbRatio[10];
      U32 avgTtiProcTime;
      U32 cntTtiProcTime1000;

      U32 cntTtiProcTime900;

      U32 cntTtiProcTime800;
      U32 cntTtiProcTime700;
      U32 cntTtiProcTime600;
      U32 cntTtiProcTime500;
      U32 ulSumCqi;
      U32 ulNumCqi;
      U32 ulSumiTbs;
      U32 ulNumiTbs;
      U32 dlTtlTpt;
      U32 ulTtlTpt;
   }sch;
   struct rlcCellStats{
      U32 maxRlcSrbRetxFail;
      U32 maxRlcDrbRetxFail;
      U32 reOdrTmrExp;
   }rlc;
}TSInfL2CellStats;

typedef struct tsInfL2UeStats
{
   U32 rnti;
   struct nonPersistentUeStats{
      struct schUeStats{
         U32 dlTxOccns;
         U32 dlRetxOccns;
         U32 dlPrbUsg;
         U32 dlNackCnt[2];
         U32 dlAckNackCnt[2];
         U32 dlDtxCnt[2];
         U32 dlSumCw0Cqi;
         U32 dlNumCw0Cqi;
         U32 dlSumCw1Cqi;
         U32 dlNumCw1Cqi;
         U32 dlSumCw0iTbs;
         U32 dlNumCw0iTbs;
         U32 dlSumCw1iTbs;
         U32 dlNumCw1iTbs;
         U32 cqiDropCnt;
         U32 dlPdbLvl[5];
         U32 riCnt[4];
         U32 dlBo;
         U32 dlTpt;
         U32 ulTxOccns;
         U32 ulRetxOccns;
         U32 ulPrbUsg;
         U32 ulAckNackCnt;
         U32 ulNackCnt;
         U32 ulDtxCnt;
         U32 ulSumCqi;
         U32 ulNumCqi;
         U32 ulSumiTbs;
         U32 ulNumiTbs;
         U32 ulTpt;
      }sch[12];
      struct pdcpUeStats{
         U32 dlPdcpDropCnt;
         U32 dlPdcpAckWaitDropCnt;
         U32 dlFlowCtrlDropCnt;
      }pdcp;
      struct rlcUeStats{
         U32 ulReOdrTmrExpCnt;
         U32 dlMaxPktsInSduQ;
         U32 dlMaxWindowSz;
      }rlc;
   }nonPersistent;
   struct persistentUeStats{
      U32 activatedSCells;
      U32 numActivation;
      U32 numDeactivation;
   }persistent;
}TSInfL2UeStats;

typedef struct tsInfStatsCb
{
   Bool initDone;
   Bool sockSend;
   Bool fileSend;
   Bool consPrint;
   U32 statsPer;
   U32 sockPort;
   Bool startSockSend;
   U8 cmdForFileStats;
   char fileName[100];
   FILE *fptr;
   U32 enbIp;
}TSInfStatsCb;

typedef Void (*TSInfL2UeStatsInd) ( Pst *, SuId , TSInfL2UeStats * )



  ;
extern Void TSInfHdlL2UeStatsInd ( Pst *pst, SuId suId, TSInfL2UeStats *stats )



  ;
extern Void TSInfUnpkL2UeStats ( TSInfL2UeStatsInd func, Pst *pst, Buffer *mBuf )



  ;
typedef Void (*TSInfL2CellStatsInd) ( Pst *, SuId , TSInfL2CellStats * )



  ;
extern Void TSInfHdlL2CellStatsInd ( Pst *pst, SuId suId, TSInfL2CellStats *stats )



  ;
extern Void TSInfUnpkL2CellStats ( TSInfL2CellStatsInd func, Pst *pst, Buffer *mBuf )



  ;
extern Void TSInfPkSndL2UeStats ( Pst *pst, SuId suId, TSInfL2UeStats *stats )



  ;
extern Void TSInfPkSndL2CellStats ( Pst *pst, SuId suId, TSInfL2CellStats *stats )



  ;
extern Void TSInfTrigStats ( Region region, Pool pool )


  ;





typedef TSInfL2CellStats TSL2CellStatsCb;

typedef struct tSL2UeStatsCb
{
   CmLList lnk;
   U32 inUse;

   TSInfL2UeStats stats;
}TSL2UeStatsCb;

extern Void TSL2AllocStatsMem ( Region region, Pool pool )


  ;
extern TSL2UeStatsCb* TSL2AllocUeStatsBlk ( U16 rnti )

  ;
extern Void TSL2DeallocUeStatsBlk ( U16 rnti, TSL2UeStatsCb *statsCb )


  ;
extern TSL2CellStatsCb* TSL2AllocCellStatsBlk ( U32 cellId )

  ;
extern Void TSL2DeallocCellStatsBlk ( U32 cellId )

  ;
extern Void TSL2SendStatsToApp ( Pst *pst, SuId suId )


  ;




typedef struct kwDlUeCb KwDlUeCb;







typedef struct kwPduMap
{
  KwSn sn;
}KwPduMap;
typedef struct kwSdu
{
   CmLList lstEnt;
   Buffer *mBuf;
   MsgLen sduSz;
   MsgLen actSz;





   union
   {
      struct _t
      {
         U16 sfn;
         U8 subframe;
         CmLteRnti rnti;
      }tm;

      struct _u
      {
         U32 sduId;
         Bool isSegmented;
      }um;

      struct _a
      {
         U32 sduId;
         MsgLen rcvdSz;
         Bool isSegmented;
      }am;
   }mode;

   Ticks arrTime;


}KwSdu;
typedef struct kwTm
{
   CmLListCp sduQ;
}KwTm;
typedef struct kwBoRep
{
   S32 bo;
   U16 estHdrSz;
   Bool staPduPrsnt;
   U32 staPduBo;
   U32 oldestSduArrTime;
} KwBoRep;
typedef struct kwDatReq
{
   MsgLen pduSz;
   KwPduInfo pduInfo;
   KwBoRep boRep;





}KwDatReq;
typedef struct kwUmDl
{
   CmLListCp sduQ;
   U8 snLen;
   S32 bo;
   S32 estHdrSz;
   KwSn vtUs;
   U16 modBitMask;
   U16 numLi;
   U16 li[100];
}KwUmDl;
typedef struct kwSduMap
{

   MsgLen sduSz;

   KwSdu* sdu;
}KwSduMap;
typedef struct kwRetx
{
   CmLList lstEnt;
   Buffer *seg;
   MsgLen segSz;
   MsgLen hdrSz;
   KwAmHdr amHdr;
   U16 soEnd;
   KwSn retxCnt;
   Bool yetToConst;
   Bool pendingReTrans;
   U8 numSdu;
   KwSduMap sduMap[100];
}KwRetx;
typedef struct kwTx
{
   Buffer *pdu;
   MsgLen pduSz;
   MsgLen hdrSz;
   KwAmHdr amHdr;
   U8 numSdu;
   KwSduMap sduMap[100];
   CmLList rlsLnk;
}KwTx;
typedef struct kwAmDl
{
   CmLListCp sduQ;
   KwSdu *nxtTx;
   CmTimer pollRetxTmr;
   U16 pollRetxTmrInt;
   S16 pollPdu;
   S32 pollByte;
   U8 maxRetx;
   S32 cntrlBo;
   S32 retxBo;
   U32 estHdrSz;
   S32 bo;

   KwTx **txBuf;



   CmLListCp retxLst;
   KwRetx *nxtRetx;
   KwSn vtS;
   KwSn vtMs;
   KwSn vtA;
   S16 pduWoPoll;
   S32 byteWoPoll;
   KwSn pollSn;
   S16 numSduPdu;
   Buffer *mBuf;

   Bool maxReTxReached;
   KwUdxDlStaPdu* pStaPdu;
}KwAmDl;
typedef struct _kwDlRbCb
{
   U8 qci;
   S16 discTmrInt;


   CmLteRlcId rlcId;
   KwLchInfo lch;
   CmLteRlcMode mode;
   U8 dir;
   Inst inst;
   SpId kwuSapId;
   SpId udxSapId;
   U32 transId;
   Bool reestInProgress;
   SpId rguSapId;
   union
   {
      KwTm tm;
      KwUmDl umDl;
      KwAmDl amDl;
   }m;
   CmLList rlsLnk;
   Bool cleanupStarted;
   U32 lastRprtdBoToMac;
   U32 boUnRprtdCnt;
}KwDlRbCb;







typedef struct kwDlLch
{
   KwDlRbCb *dlRbCb;
}KwDlLch;
typedef struct kwDlCellCb
{
   CmHashListEnt cellHlEnt;
   CmLteCellId cellId;
   KwDlRbCb *rbCb[10];
   KwDlLch lCh[6];
}KwDlCellCb;
struct kwDlUeCb
{
   CmHashListEnt ueHlEnt;
   CmLteRnti ueId;
   CmLteCellId cellId;
   KwDlRbCb *srbCb[3];
   KwDlRbCb *drbCb[32];
   KwDlLch lCh[12];







   TSL2UeStatsCb *tenbStats;

};







extern S16 kwCfgAddDlRb (KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm)



                                                        ;

extern S16 kwCfgReCfgDlRb (KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm)



                                                           ;

extern S16 kwCfgDelDlRb (KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm)



                                                         ;

extern S16 kwCfgDelDlUe (KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm)



                                                         ;

extern S16 kwCfgReEstDlRb (KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, Bool sndReEst, CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm)




                                                           ;

extern S16 kwCfgDelDlCell (KwCb *gCb, CmLteCellId cellId, CkwEntCfgInfo *entCfg, CkwEntCfgCfmInfo *entCfm)


                                                           ;

extern S16 kwCfgDlUeIdChng (KwCb *gCb, CkwUeInfo *ueInfo, CkwUeInfo *newUeInfo, CmStatus *status)


                                                     ;




extern S16 kwDbmDlInit (KwCb *gCb);

extern Void kwDbmDlDeInit (KwCb *gCb);

extern S16 kwDbmCreateDlUeCb (KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, KwDlUeCb **ueCb)


                                                     ;

extern S16 kwDbmFetchDlUeCb (KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, KwDlUeCb **ueCb)


                                                    ;

extern Void kwDbmDelDlUeCb (KwCb *gCb, KwDlUeCb *ueCb, Bool abortFlag)

                                                  ;

extern Void kwDbmDelAllDlUe (KwCb *gCb);

extern S16 kwDbmCreateDlCellCb (KwCb *gCb, CmLteCellId cellId, KwDlCellCb **cellCb)

                                                           ;

extern S16 kwDbmFetchDlCellCb (KwCb *gCb, CmLteCellId cellId, KwDlCellCb **cellCb)

                                                          ;

extern Void kwDbmDelDlCellCb (KwCb *gCb, KwDlCellCb *cellCb);

extern Void kwDbmDelAllDlCell (KwCb *gCb);

extern Void kwDbmFetchDlRbCbByRbId (KwCb *gCb, CmLteRlcId *rlcId, KwDlRbCb **rbCb)

                                                           ;

extern Void kwDbmFetchDlRbCbFromLchId (KwCb *gCb, CmLteRnti ueId, CmLteCellId cellId, CmLteLcId lcId, KwDlRbCb **rbCb)



                                                              ;

extern Void kwDbmDelAllDlRb (KwCb *gCb, KwDlRbCb **rbCbLst, U8 numRbCb);

extern S16 kwDbmDlShutdown (KwCb *gCb);

extern Void kwUtlGetCurrTime (U32 *time);
extern Void kwUtlTrigPdbFlowCntrl (KwCb *gCb, KwDlRbCb *rbCb, U32 pktAdmitCnt );
extern Void kwTmmQSdu (KwCb *gCb, KwDlRbCb *rbCb, KwuDatReqInfo *datReqInfo, Buffer *mBuf)


                                          ;
extern Void kwTmmSndToLi (KwCb *gCb, SuId suId, KwDlRbCb *rbCb, RguCStaIndInfo *staInd)


                                                        ;

extern Void kwDlTmmReEstablish (KwCb *gCb, KwDlRbCb *rbCb);




extern Void kwUmmQSdu (KwCb *gCb, KwDlRbCb *rbCb, KwuDatReqInfo *datReq, Buffer *mBuf)


                                           ;

extern Void kwUmmDiscSdu (KwCb *gCb, KwDlRbCb *rbCb, U32 sduId);

extern Void kwDlUmmReEstablish (KwCb *gCb, CmLteRlcId rlcId, Bool sndReEst, KwDlRbCb *rbCb)


                                                      ;

extern Void kwUmmProcessSdus (KwCb *gCb,KwDlRbCb *rbCb,KwDatReq *datReq);

extern Void kwUmmFreeDlRbCb (KwCb *gCb, KwDlRbCb *rbCb);





extern S32 kwAmmCalculateBo (KwAmDl *amDl);

extern Void kwAmmSendDStaRsp (KwCb *gCb, KwDlRbCb *rbCb, KwAmDl *amDl);

extern Void kwAmmQSdu (KwCb *gCb, KwDlRbCb *rbCb, Buffer *mBuf, KwuDatReqInfo *datReq)


                                                   ;

extern Void kwAmmProcessSdus (KwCb *gCb, KwDlRbCb *rbCb, KwDatReq *kwDatReq, Bool staPduPres)


                                                    ;

extern Void kwAmmDlReEstablish (KwCb *gCb, CmLteRlcId rlcId, KwDlRbCb *rbCb)

                                                     ;

extern Void kwAmmDlHndlStatusPdu (KwCb *gCb, KwDlRbCb *rbCb, KwUdxStaPdu *pStaPdu)

                                                              ;

extern S16 kwAmmDiscSdu (KwCb *gCb, KwDlRbCb *rbCb, U32 sduId);

extern Void kwAmmPollRetxTmrExp (KwCb *gCB, KwDlRbCb *rbCb);

extern Void kwAmmFreeDlRbCb (KwCb *gCb, KwDlRbCb *rbCb);




extern S16 kwUtlSndDStaRsp (KwCb *gCb, KwDlRbCb *rbCb, S32 bo, S32 estHdrSz, Bool staPduPrsnt, U32 staPduBo)




                                                ;




extern Void kwUtlEmptySduQ (KwCb *gCb,CmLListCp *sduQ);


extern Void kwUtlCalcLiForSdu (KwCb *gCb, U16 numLi, MsgLen msgLen, S16 *pduSz)


                                                 ;

extern S16 kwUtlSndToLi (KwCb *gCb, SuId suId, KwDStaIndInfo *staIndInfo);

extern Void kwUtlIncrementKwuStsSduTx (KwKwuSapCb *kwuSap);

extern Void kwUtlIncrementGenStsBytesAndPdusSent (KwGenSts *genSts, Buffer *pdu)
                                                                    ;

extern Void kwUtlFreeDlMemory (KwCb *gCb);

extern Void kwUtlInitToBeFreed (KwCb *gCb, KwDlDataToBeFreed *toBeFreed);

extern Void kwUtlInitializeSelfPst (KwCb *gCb);

extern Void kwUtlRaiseDlCleanupEvent (KwCb *gCb);

extern Void kwUtlAddSduToBeFreedQueue (KwCb *gCb, KwSdu *sdu);

extern Void kwUtlAddReTxPduToBeFreedQueue (KwCb *gCb, KwRetx *retx);

extern Void kwUtlAddTxPduToBeFreedQueue (KwCb *gCb, KwTx *pdu);
extern Void ResetRLCStats (Void);

extern Void PrintRLCStats (Void);

extern Void DumpRLCDlDebugInformation (Void);




extern S16 kwDlActvInit (Ent ent,Inst inst,Region region,Reason reason);

extern S16 kwDlActvTsk (Pst *pst, Buffer *mBuf);

extern Bool kwDlUtlIsReestInProgress (KwDlRbCb *rbCb);

extern Void kwDlUtlResetReestInProgress (KwDlRbCb *rbCb);

extern Void kwDlUtlResetReestInProgress ( KwDlRbCb *rbCb);

extern Void kwDlUtlSetReestInProgressForAllRBs (KwCb *gCb, KwDlUeCb *ueCb)
                ;
extern Void kwDlUtlSetReestInProgressForRB ( KwCb *gCb, KwDlRbCb *rbCb);
extern Void kwUtlFreeDlMem ( Void);
typedef struct ueIdentity
{
   uint16_t ueIndex;
   uint16_t cRnti;
}UeIdentity;


typedef struct rbIdentity
{
   uint8_t rbId;
   uint8_t lcId;
   uint8_t spare[2];
}RbIdentity;




typedef struct timingInfo
{
   uint16_t sfn;

   uint8_t sf;



   uint8_t spare;
}TimingInfo;







typedef struct dlPowerControlConfig
{
   uint16_t pcfichPowerOffset;






   uint16_t phichPowerOffset;






   uint16_t pdcchPowerOffset;





   uint16_t pbchTransmissionPower;





   uint16_t pchTransmissionPower;





   uint16_t spare;
}DlPowerControlConfig;



typedef struct schedulerSpecificConfiguration
{
   uint8_t dlSchedulingType;




   uint8_t ulSchedulingType;




   uint16_t spare;
}SchedulerSpecificConfiguration;



typedef struct numberOfUsersPerTTI
{
   uint8_t numberOfDlUsersPerTTI;


   uint8_t numberOfUlUsersPerTTI;


   uint16_t spare;
}NumberOfUsersPerTTI;



typedef struct puschConfiguration
{
   uint16_t numberOfSubBands;



   uint16_t hoppingMode;



   uint8_t hopOffset;
   uint8_t spare[3];
}PuschConfiguration;



typedef enum ulPowerAlpha
{
   POWER_ALPHA0 = 0,
   POWER_ALPHA4 = 4,
   POWER_ALPHA5 = 5,
   POWER_ALPHA6 = 6,
   POWER_ALPHA7 = 7,
   POWER_ALPHA8 = 8,
   POWER_ALPHA9 = 9,
   POWER_ALPHAALL = 10
}UlPowerAlpha;



typedef struct ulPowerControlConfig
{
   int8_t p0NominalPusch;

   int8_t p0NominalPucch;
   int8_t deltaPreambleMessage3;
   uint8_t spare ;
   UlPowerAlpha alpha;


   uint16_t format3PucchStartTpcRnti;
   uint16_t format3PucchEndRnti;

   uint16_t format3APucchStartTpcRnti;
   uint16_t format3APucchEndRnti;

   uint16_t format3PuschStartTpcRnti;
   uint16_t format3PuschEndRnti;

   uint16_t format3APuschStartTpcRnti;
   uint16_t format3APuschEndRnti;

}UlPowerControlConfig;



typedef struct rachConfiguration
{
   uint8_t raWindowSize;


   uint8_t maxMsg3HarqTransmissions;



   uint8_t numberOfRAPreambles;



   uint8_t sizeOfRAPreambleinGroupA;



   uint16_t messageSizeGroupA;


   uint8_t prachConfigurationIndex;


   uint8_t prachFrequencyOffset;


   uint8_t contentionResolutionTimer;

   uint8_t spare[3];
}RachConfiguration;



typedef enum srsBwConfiguration
{
   SRS_BANDWIDTH_0,
   SRS_BANDWIDTH_1,
   SRS_BANDWIDTH_2,
   SRS_BANDWIDTH_3,
   SRS_BANDWIDTH_4,
   SRS_BANDWIDTH_5,
   SRS_BANDWIDTH_6,
   SRS_BANDWIDTH_7
}SrsBwConfiguration;



typedef struct srsConfiguration
{
   Bool cellSpecificSrsEnable;

   uint8_t srsSubframeConfiguration;



   Bool simultaneousAckNackAndSrs;



   uint8_t spare;

   SrsBwConfiguration srsBwConfigInfo;






}SrsConfiguration;



typedef struct pucchConfiguration
{
   uint8_t resourceSize;



   uint8_t deltaShift;


   uint16_t n1PucchAckNack;

   uint8_t cyclicShift;



   uint8_t spare[3];

}PucchConfiguration;



typedef enum phichDuration
{
   PHICH_DUR_NORMAL,
   PHICH_DUR_EXTENDED
}PhichDuration;



typedef enum phichRE
{
   PHICH_R_ONE_SIXTH,
   PHICH_R_HALF,
   PHICH_R_ONE,
   PHICH_R_TWO
}PhichRE;



typedef struct phichConfiguration
{
   PhichRE phichResource;







   PhichDuration phichDuration;

}PhichConfiguration;



typedef enum duplexMode
{
   TDD,
   FDD,
   HD_FDD
}DuplexMode;



typedef enum bandwidth
{
   BW_RB_6 = 6,
   BW_RB_15 = 15,
   BW_RB_25 = 25,
   BW_RB_50 = 50,
   BW_RB_75 = 75,
   BW_RB_100 = 100
}Bandwidth;



typedef struct bandwidthConfiguration
{
   Bandwidth dlBandwidth;
   Bandwidth ulBandwidth;
   DuplexMode duplexingMode;
}BandwidthConfiguration;



typedef struct rntiConfiguration
{
   uint16_t startRnti;
   uint16_t endRnti;
}RntiConfiguration;



typedef struct harqConfiguration
{
   uint8_t maxDlHarqTransmissions;
   uint8_t maxMsg4HarqTransmissions;
   uint16_t spare;

}HarqConfiguration;



typedef struct macCellConfigReq
{
   uint8_t cyclicPrefix;


   Bool enable64Qam;
   uint8_t cfiValue;
   Bool dynamicCfiEnable;
   HarqConfiguration harqConfigInfo;

   RntiConfiguration rntiConfigInfo;
   Bool dlfsEnable;
   Bool ulfsEnable;
   int8_t pMax;
   uint8_t spare;
   uint16_t defaultPagingCycle;




   uint16_t spare1;
   BandwidthConfiguration bwInfo;

   PhichConfiguration phichConfigInfo;

   PucchConfiguration pucchConfigInfo;
   SrsConfiguration srsConfigInfo;
   RachConfiguration rachConfigInfo;
   UlPowerControlConfig ulPowerControlConfigInfo;
   PuschConfiguration puschConfigInfo;
   NumberOfUsersPerTTI numOfUsersPerTTI;
   SchedulerSpecificConfiguration schedulerSpecificConfigInfo;
   DlPowerControlConfig dlPowerControlConfigInfo;
   uint8_t numOfTxAntennas;




   uint8_t nB;
   uint16_t l3SfPeriodicity;

}MacCellConfigReq;




typedef struct macCellConfigRsp
{
   uint16_t status;


   uint16_t spare;
}MacCellConfigRsp;



typedef struct macCellDeleteRsp
{
   uint16_t status;


   uint16_t spare;
}MacCellDeleteRsp;



typedef struct transmissionModeConfig
{
   Bool transmissionModePresent;


   uint8_t transmissionMode;



   uint16_t spare;

}TransmissionModeConfig;



typedef enum aperiodicCqiTransMode
{
   APERIODIC_CQI_MOD12,
   APERIODIC_CQI_MOD20,
   APERIODIC_CQI_MOD22,
   APERIODIC_CQI_MOD30,
   APERIODIC_CQI_MOD31
}AperiodicCqiTransMode;



typedef struct aperiodicCqiConfig
{
   Bool present;


   uint8_t spare[3];
   AperiodicCqiTransMode aperiodicCqiMode;







}AperiodicCqiConfig;



typedef enum periodicCqiTransMode
{
   PERIODIC_CQI_MOD10,
   PERIODIC_CQI_MOD11,
   PERIODIC_CQI_MOD20,
   PERIODIC_CQI_MOD21
}PeriodicCqiTransMode;



typedef struct periodicCqiConfig
{
   Bool present;


   uint8_t cqiPucchResourceIndex;



   uint8_t cqiPmiConfigurationIndex;




   uint8_t k;


   PeriodicCqiTransMode periodicCqiMode;







   uint8_t simultaneousAckNackAndCqi;


   Bool riEnableFlag;


   uint16_t riConfigIndex;


}PeriodicCqiConfig;



typedef struct dlCqiConfig
{
   AperiodicCqiConfig aperiodicCqiConfigInfo;
   PeriodicCqiConfig periodicCqiConfigInfo;
}DlCqiConfig;



typedef struct ulHarqConfiguration
{
   uint8_t maxUlHarqTransmissions;
   uint8_t spare[3];
}UlHarqConfiguration;



typedef struct uePuschGroupPowerControlConfig
{
   Bool present;


   uint8_t index;



   uint16_t tpcRnti;
}UePuschGroupPowerControlConfig;



typedef struct uePucchGroupPowerControlConfig
{
   Bool present;



   uint8_t index;




   uint16_t tpcRnti;
   uint8_t accumulatedFlag;




   uint8_t deltaMcsFlag;


   int8_t p0UePusch;


   int8_t p0UePucch;


}UePucchGroupPowerControlConfig;



typedef struct ueQosConfiguration
{
   Bool ambrPresent;

   uint8_t spare[3];
   uint32_t dlAmbrValue;
   uint32_t ulByteRate;
}UeQosConfiguration;



typedef struct ueUlPowerControlConfig
{
   UePuschGroupPowerControlConfig uePuschGroupPowerControlConfigInfo;
   UePucchGroupPowerControlConfig uePucchGroupPowerControlConfigInfo;
}UeUlPowerControlConfig;



typedef struct ueDrxConfiguration
{
   Bool drxEnabledFlag;


   uint8_t cqiMask;
   uint16_t drxInactivitytimer;

   uint8_t drxOnDurationTimer;

   uint8_t drxRetransmissionTimer;

   uint16_t longDrxCycle;

   uint16_t longDrxCycleStartOffset;

   uint8_t spare[2];
   Bool shortDrxPresent;

   uint8_t spare1[3];
   uint16_t shortDrxCycle;

   uint16_t shortDrxCycleTimer;



}UeDrxConfiguration;



typedef struct cbSubsetRestrictionConfig
{
   Bool cbSubsetRestrictionflag;


   uint8_t spare[3];

   uint32_t cbBitmap[2];

}CbSubsetRestrictionConfig;



typedef struct srsUeConfiguration
{
   Bool srsConfigFlag;


   uint8_t srsConfigIndex;


   uint8_t srsBandwidth;




   uint8_t srsHoppingBandwidth;


   uint8_t srsCyclicShift;


   uint8_t duration;


   uint8_t transmissionComb;


   uint8_t frequencyDomainPosition;


}SrsUeConfiguration;



typedef struct srConfiguration
{
   Bool srConfigFlag;

   uint8_t srConfigIndex;


   uint16_t srResourceIndex;


}SrConfiguration;



typedef struct uePuschConfiguration
{
   Bool uePuschConfigSupport;


   uint8_t harqBetaOffset;

   uint8_t riBetaOffset;

   uint8_t cqiBetaOffset;

}UePuschConfiguration;



typedef struct ueMeasurementGapConfig
{
   Bool ueMeasurementGapFlag;


   uint8_t gapPeriod;

   uint8_t gapOffset;
   uint8_t spare;
}UeMeasurementGapConfig;



typedef struct uePdschConfiguration
{
   Bool uePdschPAConfigFlag;


   uint8_t pA;

   uint16_t spare;

}UePdschConfiguration;



typedef struct cqiPmiConfigIndexInfo
{
   uint16_t cqiPmiConfigIndex;




   uint16_t cqiPucchResourceIndex;




   uint8_t simultaneousAckNackAndCqi;





   uint8_t cqiFormatIndicatorPeriodic;




   uint16_t riConfigIndex;


   uint8_t subbandCqik;




   uint8_t spare[3];

}CqiPmiConfigIndexInfo;



typedef struct cqiPeriodicConfiguration
{
   uint8_t requestType;

   uint8_t spare[3];

   CqiPmiConfigIndexInfo cqiPeriodicInfo;
}CqiPeriodicConfiguration;



typedef struct ueTaTimerConfiguration
{
   Bool present;

   uint8_t spare;
   uint16_t taTimer;

}UeTaTimerConfiguration;



typedef struct gbrQosInfo
{
   uint32_t erabMaxBitRateDl;
   uint32_t erabMaxBitRateUl;
   uint32_t erabGuaranteedBitRateDl;
   uint32_t erabGuaranteedBitRateUl;
}GbrQosInfo;



typedef struct qosInfo
{
   uint8_t qci;
   uint8_t spare[3];
   GbrQosInfo gbrQosConfigInfo;
}QosInfo;



typedef struct dlLcCreateReq
{
   uint8_t lchPriority;
   uint8_t spare[3];
}DlLcConfig;



typedef struct ulLcCreateReq
{
   uint8_t lcgId;
   uint8_t spare[3];
}UlLcConfig;



typedef enum entityDirection
{
   UPLINK = 1,
   DOWNLINK = 2,
   BOTH = 3
}EntityDirection;



typedef struct createLcReq
{
   uint8_t lcConfigType;


   uint8_t lchId;
   uint8_t spare[2];
   EntityDirection dirInfo;
   UlLcConfig ulLcInfo;
   DlLcConfig dlLcInfo;
   QosInfo qosConfigInfo;
}LcConfigInfo;

typedef enum ueAsRelInfo
{
   UE_REL_8,
   UE_REL_9,
   UE_REL_10
} UEAsRelInfo;



typedef struct macUeConfigReq
{
   UeIdentity ueInfo;
   Bool ueConfigPresent;


   uint8_t ueCategory;



   Bool ttiBundlingEnable;



   uint8_t spare;
   TransmissionModeConfig transmissionModeConfigInfo;
   DlCqiConfig dlCqiConfigInfo;
   UlHarqConfiguration ulHarqConfigInfo;
   UeUlPowerControlConfig ueUlPowerControlConfigInfo;
   UeQosConfiguration ueQosConfigInfo;
   UeTaTimerConfiguration ueTaTimerConfigInfo;
   UeDrxConfiguration ueDrxConfigInfo;
   UeMeasurementGapConfig ueMeasurementGapConfigInfo;
   CbSubsetRestrictionConfig cbSubsetRestrictionConfigInfo;
   SrsUeConfiguration srsUeConfigInfo;
   SrConfiguration srConfigInfo;
   UePuschConfiguration uePuschConfigInfo;
   UePdschConfiguration uePdschConfigInfo;
   UEAsRelInfo ueRel;
   uint8_t numberOfLcs;

   uint8_t spare1[3];
   LcConfigInfo lcInfo[1];

}MacUeConfigReq;




typedef struct failedLcList
{
   uint8_t lcConfigType;


   uint8_t lchId;
   uint8_t spare[2];
}FailedLcList;



typedef struct macUeConfigRsp
{
   UeIdentity ueInfo;
   uint16_t status;


   uint8_t spare[2];
   uint8_t numberOfFailedLcs;
   uint8_t spare1[3];
   FailedLcList lc[1];
}MacUeConfigRsp;
typedef struct macUeReconfigReq
{
   uint16_t ueIndex;
   uint16_t oldCRnti;
   uint8_t ueCategory;



   uint8_t spare;
   uint16_t newCRnti;
   uint32_t bitMask;

   TransmissionModeConfig transmissionModeConfigInfo;
   DlCqiConfig dlCqiConfigInfo;
   UlHarqConfiguration ulHarqConfigInfo;
   UeUlPowerControlConfig ueUlPowerControlConfigInfo;
   UeQosConfiguration ueQosConfigInfo;
   UeTaTimerConfiguration ueTaTimerConfigInfo;
   UeDrxConfiguration ueDrxConfigInfo;
   UeMeasurementGapConfig ueMeasurementGapConfigInfo;
   CbSubsetRestrictionConfig cbSubsetRestrictionConfigInfo;
   SrsUeConfiguration srsUeConfigInfo;
   SrConfiguration srConfigInfo;
   UePuschConfiguration uePuschConfigInfo;
   UePdschConfiguration uePdschConfigInfo;
   Bool ttiBundlingEnable;



   uint8_t numberOfLcs;
   uint8_t spare1[2];
   LcConfigInfo LcInfo[1];
}MacUeReconfigReq;



typedef struct macUeReconfigRsp
{
   UeIdentity ueInfo;
   uint16_t status;


   uint8_t spare[2];
   uint8_t numberOfFailedLcs;
   uint8_t spare1[3];
   FailedLcList lc[10];
}MacUeReconfigRsp;



typedef struct macUeDeleteReq
{
   UeIdentity ueInfo;
}MacUeDeleteReq;



typedef struct macUeDeleteRsp
{
   UeIdentity ueInfo;
   uint16_t status;


   uint16_t spare;

}MacUeDeleteRsp;



typedef enum siModificationPeriod
{
   SI_MODIFICATION_PERD_64 = 64,
   SI_MODIFICATION_PERD_128 = 128,
   SI_MODIFICATION_PERD_256 = 256,
   SI_MODIFICATION_PERD_512 = 512,
   SI_MODIFICATION_PERD_1024 = 1024
}SiModificationPeriod;




typedef enum siBroadCastChangeTime
{
   SI_CHANGE_NORMAL = 1,
   SI_CHANGE_IMMEDIATE,
} SiBroadCastChangeTime;




typedef enum siWindowLength
{
   SI_WINDOW_LENGTH_1 = 1,
   SI_WINDOW_LENGTH_2 = 2,
   SI_WINDOW_LENGTH_5 = 5,
   SI_WINDOW_LENGTH_10 = 10,
   SI_WINDOW_LENGTH_15 = 15,
   SI_WINDOW_LENGTH_20 = 20,
   SI_WINDOW_LENGTH_40 = 40
}SiWindowLength;



typedef enum siPeriodicity
{
   SI_PERD_8 = 8,
   SI_PERD_16 = 16,
   SI_PERD_32 = 32,
   SI_PERD_64 = 64,
   SI_PERD_128 = 128,
   SI_PERD_256 = 256,
   SI_PERD_512 = 512
}SiPeriodicity;



typedef struct siPduInfo
{
   uint16_t pduLength;
   uint16_t spare;
   uint8_t spare1[3];
   uint8_t siPdu[1];
}SiPduInfo;



typedef struct siConfiguration
{
   uint16_t siId;
   uint16_t spare;

   uint8_t numSegments;
   uint8_t spare1[3];
   SiPeriodicity siPeriodicity;
   SiPduInfo siPduList[1];
}SiConfiguration;







typedef struct macBroadcastMsgReq
{
   SiWindowLength siWindowLen;
   SiModificationPeriod modfnPeriod;
   SiBroadCastChangeTime siBrdcstChngTim;


   uint16_t siCfgBitMask;






   uint16_t mibPduLen;
   uint16_t sib1PduLen;
   uint16_t spare;
   uint8_t siRetxCnt;
   uint8_t numSiPdus;

   uint8_t mibPdu[1];
   uint8_t sib1Pdu[1];
   SiConfiguration siConfigInfo[1];
}MacBroadcastMsgReq;



typedef struct macBroadcastMsgRsp
{
   uint16_t status;

   uint16_t spare;
}MacBroadcastMsgRsp;







typedef struct phyBandwidthConfig
{
   Bandwidth dlBandwidth;

   Bandwidth ulBandwidth;

   uint16_t frequencyBand;

   uint16_t dlEarfcn;
   uint16_t ulEarfcn;
   uint16_t spare;
}PhyBandwidthConfig;



typedef struct transmissionSchemeConfig
{
   DuplexMode duplexMode;

   uint16_t subCarrierSpacing;

   uint16_t cyclicPrefix;



}TransmissionSchemeConfig;



typedef struct antennaConfiguration
{
   uint16_t txAntennaPorts;


   uint16_t spare1;

}AntennaConfiguration;



typedef struct prachConfiguration
{
   uint16_t rootSeqIndex;
   uint16_t configIndex;

   uint16_t zeroCorrZoneConfig;

   uint16_t highSpeedFlag;



   uint16_t freqencyOffset;


   uint16_t spare;

}PrachConfiguration;



typedef struct phyPdschConfiguration
{
   uint16_t pB;

   uint16_t spare;
}PhyPdschConfiguration;



typedef struct ulReferenceSignalConfiguration
{
   Bool groupHoppingEnable;

   Bool sequnceHoppingEnable;

   uint16_t groupAssignment;


   uint16_t cyclicShift;



   uint16_t spare;
}UlReferenceSignalConfiguration;



typedef struct phyPuschConfiguration
{
   uint16_t hoppingMode;



   uint16_t hoppingOffset;


   uint16_t numberOfSubbands;


   Bool enable64Qam;

   uint8_t spare;
   UlReferenceSignalConfiguration ulRefSigCfgInfo;
}PhyPuschConfiguration;



typedef struct phyPhichConfiguration
{
   PhichDuration phichDuration;



   uint16_t phichPowerOffset;



   uint16_t spare;
   PhichRE phichResource;





}PhyPhichConfiguration;

typedef enum pucchCyclicShift {
   PUCCH_DELTASHIFT1 = 1,
   PUCCH_DELTASHIFT2,
   PUCCH_DELTASHIFT3
} PucchDeltaShift;



typedef struct phyPucchConfiguration
{
   uint16_t nRB;

   uint16_t nCS;

   uint16_t n1PucchAn;

   uint16_t spare;
   PucchDeltaShift deltaPucchShift;

}PhyPucchConfiguration;



typedef struct phySrsConfiguration
{
   uint16_t bwConfig;

   uint16_t sfConfig;


   uint16_t anSimultTx;





   uint16_t spare;
}PhySrsConfiguration;



typedef struct phySigConfiguration
{
   uint16_t priSyncSignal;



   uint16_t secSyncSignal;



   uint16_t refSignalPower;
   uint16_t spare;
}PhySigConfiguration;



typedef struct phyCellConfigReq
{
   uint16_t pci;
   uint16_t pcfichPowerOffset;





   PhyBandwidthConfig bwConfigInfo;
   TransmissionSchemeConfig txSchemeConfigInfo;
   AntennaConfiguration antennaConfigInfo;
   PrachConfiguration prachConfigInfo;
   PhyPdschConfiguration pdschConfigInfo;
   PhyPuschConfiguration puschConfigInfo;
   PhyPhichConfiguration phichConfigInfo;
   PhyPucchConfiguration pucchConfigInfo;
   PhySrsConfiguration srsConfigInfo;
   PhySigConfiguration sigConfigInfo;
   uint16_t spare;

}PhyCellConfigReq;




typedef struct phyCellConfigRsp
{
   uint16_t status;


   uint16_t spare;
}PhyCellConfigRsp;



typedef struct phyCellDeleteReq
{
   uint16_t spare[2];

}PhyCellDeleteReq;



typedef struct phyCellDeleteRsp
{
   uint16_t status;


   uint16_t spare;
}PhyCellDeleteRsp;



typedef struct l3TtiInd
{
   TimingInfo timingInfo;
}L3TtiInd;





typedef enum rlcCommonEntityType
{
   RLC_ENTITY_DL_BCCH = 1,
   RLC_ENTITY_DL_CCCH,
   RLC_ENTITY_UL_CCCH,
   RLC_ENTITY_DL_PCCH
}RlcCommonEntityType;

typedef struct rlcCommonChannelConfigReq
{
   uint8_t numberOfEntities;

   uint8_t spare[3];
   RlcCommonEntityType entityType[1];
} RlcCmnChnlConfigReq;




typedef struct rlcCommonChannelFailedEntity
{
   RlcCommonEntityType entityType;
} RlcComnChnlFailedEntity;

typedef struct rlcCommonChannelConfigRsp
{
   uint8_t configStatus;
   uint8_t numberOfEntities;

   uint8_t spare[2];
   RlcComnChnlFailedEntity cfgStatus[1];
} RlcCmnChnlConfigRsp;

typedef RlcCmnChnlConfigReq RlcCmnChnlDeleteReq;
typedef RlcCmnChnlConfigRsp RlcCmnChnlDeleteRsp;



typedef struct ackModeConfiguration
{
   uint16_t pollRetransmitTimer;
   int16_t pollPdu;
   uint8_t maxRetransmissions;
   uint8_t spare1;
   int16_t pollByte;

   uint8_t reorderingTimer;



   uint8_t spare2;
   uint16_t statusProhibitTimer;
}AckModeConfiguration;



typedef struct unAckModeConfiguration
{
   uint8_t dlSN;
   uint8_t ulSN;
   uint8_t reorderingTimer;
   uint8_t spare;
}UnAckModeConfiguration;

typedef enum rlcEntityCfgType
{
   RLC_RB_ADD = 1,
   RLC_RB_MODIFY,
   RLC_RB_DELETE,
   RLC_RB_RESET
}RlcEntityCfgType;



typedef struct rlcEntityConfiguration
{
   RlcEntityCfgType configType;
   RbIdentity rbInfo;
   uint8_t qci;

   uint8_t entityMode;

   uint8_t spare[2];
   EntityDirection direction;
   UnAckModeConfiguration unackModeConfigInfo;
   AckModeConfiguration ackModeConfigInfo;
}RlcEntityConfiguration;



typedef struct rlcUeConfigReq
{
   UeIdentity ueInfo;
   uint8_t numberOfEntites;

   uint8_t spare[3];
   RlcEntityConfiguration entityInfo[1];


}RlcUeConfigReq;



typedef struct rlcEntityConfirmation
{
   RbIdentity rbInfo;
   RlcEntityCfgType configType;
}RlcEntityConfirmation;



typedef struct rlcUeConfigRsp
{
   UeIdentity ueInfo;
   uint8_t status;
   uint8_t numberOfEntities;
   uint8_t spare[2];
   RlcEntityConfirmation entityInfo[1];


}RlcUeConfigRsp;







typedef struct rlcUeReconfigReq
{
   UeIdentity ueInfo;
   uint16_t recfgBitMask;

   uint16_t newCrnti;
   uint8_t numberOfEntites;

   uint8_t spare[3];
   RlcEntityConfiguration entityInfo[1];


}RlcUeReconfigReq;

typedef RlcUeConfigRsp RlcUeReconfigRsp;



typedef struct rlcUeDeleteReq
{
   UeIdentity ueInfo;
}RlcUeDeleteReq;



typedef struct rlcUeDeleteRsp
{
   UeIdentity ueInfo;
   uint8_t status;
}RlcUeDeleteRsp;




typedef struct rrcCcchMsgInd
{
   UeIdentity ueInfo;
   uint16_t msgLen;
   uint8_t spare[1];
   uint8_t ccchMsg[1];
} RrcCcchMsgInd;




typedef struct rlcCcchMsgReq
{
   UeIdentity ueInfo;
   uint16_t msgLen;
   uint8_t spare[1];
   uint8_t ccchMsg[1];
} RlcCcchMsgReq;




typedef struct rlcCcchUeRejReq
{
   UeIdentity ueInfo;
   uint16_t msgLen;
   uint8_t spare[1];
   uint8_t ccchMsg[1];
} RlcCcchUeRejReq;




typedef struct rlcPcchMsgReq
{
   TimingInfo timingInfo;
   uint16_t msgLen;
   uint16_t numberOfSfn;






   uint8_t ovrWrtMsg;

   uint8_t spare[3];
   uint8_t pcchMsg[1];
} RlcPcchMsgReq;

typedef enum l2UeRelCause
{
   L2_UEREL_CAUSE_MAXRETX = 1,
   L2_UEREL_CAUSE_ULSYNC_LOSS,
   L2_UEREL_CAUSE_UEINACTIVITY
} L2UeRelCause;




typedef struct l2UeRelInd
{
   UeIdentity ueInfo;
   L2UeRelCause cause;
} L2UeRelInd;
extern S16 tipSendUeRlsInd(U16 ueId, U16 cellId, U32 cause);







U32 kwStatusPduCnt, kwStatusAckCnt, kwStatusNcnt, kwSduSndCnt;






extern Void kwAmmDlHndlStatusPdu (KwCb *gCb, KwDlRbCb *rbCb, KwUdxStaPdu *pStaPdu)

                                                              ;
static Void kwResegRetxPdus (KwCb *gCb, KwDlRbCb *rbCb, KwDatReq *kwDatReq)

                                                         ;

static Void kwRemRetxPdu (KwCb *gCb, KwDlRbCb *rbCb, KwRetx *retx)

                                               ;

static Void kwAmmCreateStatusPdu (KwCb *gCb, KwDlRbCb *rbCb, KwDatReq *kwDatReq)

                                                             ;

static Void kwAmmCalcBytesReqdForNacks (KwNackInfo *nackInfo, U16 *numOfBytes, U16 *numOfBits)

                                                               ;

static Void kwFormDlCntrlBits (KwCb *gCb, KwCntrlInfo *cntrlInfo, U16 *staPdu, U16 *maxCPduLen)


                                                       ;

static Void kwAmmDlMarkPduForReTx (KwCb *gCb, KwDlRbCb *rbCb, KwRetx *retx)

                                                        ;

static Void kwAmmDlProcessSuccessfulTxPdu (KwCb *gCb, KwDlRbCb *rbCb, KwSn sn, KwuDatCfmInfo **datCfm)


                                                                         ;

static Void kwAmmDlSetVtAAndVtMS (KwAmDl *amDl, KwSn sn);

static Void kwAmmDlCheckAndStopPollTmr (KwCb *gCb, KwDlRbCb *rbCb, KwSn mAckSn)

                                                           ;

static Void kwAssembleSdus (KwCb *gCb, KwDlRbCb *rbCb, KwDatReq *kwDatReq)

                                                        ;

static Bool kwAmmDlCheckAndSetPoll (KwCb *gCb, KwDlRbCb *rbCb, Bool newPdu, MsgLen bufSz)


                                                         ;

static Void kwAmmCreatePdu (KwCb *gCb, KwDlRbCb *rbCb, KwAmHdr *amHdr, Buffer *pdu)


                                                ;

static Void kwAmmEstHdrSz (KwCb *gCb, KwAmDl *amDl, U8 type);

static Void kwAmmSndStaInd (KwCb *gCb,KwDlRbCb *rbCb, KwRetx *retx);

static Void kwGetNxtRetx (KwCb *gCb, KwRetx **retx);

static Void kwConstructAmHdr (KwCb *gCb, KwAmHdr *amHdr, Bool isSeg, U8 *hdr, U16 *idx)



                                               ;

static Void kwFormBits (KwHdrInfo *hdrInfo);

static Void kwAmmDlUpdateTxAndReTxBufForAckSn (KwCb *gCb, KwDlRbCb *rbCb, KwSn mAckSn, CmLList *retx, KwuDatCfmInfo **datCfm)



                                                                              ;

static Void kwAmmDlMoveFrmTxtoRetxBuffer (KwCb *gCb, KwAmDl *amDl, KwRetx **retx, KwSn sn)


                                                          ;

static Void kwAmmDlCheckIsSDUDelivered (KwCb *gCb, KwDlRbCb *rbCb, KwSduMap *sduLst, U8 numSdu, KwuDatCfmInfo **datCfm)



                                                                      ;
 Void kwAmmSendDStaRsp
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwAmDl *amDl
)






{
   S32 bo = kwAmmCalculateBo(amDl);

   if(bo)
   {
      kwUtlSndDStaRsp(gCb, rbCb, bo, amDl->estHdrSz, amDl->cntrlBo ?1:0,amDl->cntrlBo);
   }

   return;
}
static Void kwAmmDlCheckAndStopPollTmr
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwSn mAckSn
)






{
   KwSn mPollSn;

   { mPollSn = (rbCb->m.amDl.pollSn - rbCb->m.amDl.vtA) & 0x3ff; };

   if (mPollSn <= mAckSn)
   {
      if (kwChkTmr(gCb, (U32)rbCb, 4))
      {
         kwStopTmr(gCb, (U32)rbCb, 4);
      }
   }

   return;
}
static Void kwAmmDlSetVtAAndVtMS
(
KwAmDl *amDl,
KwSn sn
)





{
   amDl->vtA = sn;
   amDl->vtMs = (sn + 512) & 0x3ff;

   return;
}
static Void kwAmmDlProcessSuccessfulReTx
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwRetx *retx,
KwuDatCfmInfo **datCfm
)







{
   kwAmmDlCheckIsSDUDelivered(gCb, rbCb, retx->sduMap, retx->numSdu, datCfm);

   kwRemRetxPdu(gCb, rbCb, retx);

   return;
}
 Void kwAmmDlHndlStatusPdu
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwUdxStaPdu *pStaPdu
)






{
   KwRetx *retx;
   KwSn mSn;
   KwSn mAckSn;
   S32 oldRetxBo;
   CmLList *retxNode;
   KwuDatCfmInfo* datCfm;
   KwKwuSapCb *kwuSap;
   KwSn mVts;

   ;
   kwStatusPduCnt++;

   rbCb->m.amDl.numSduPdu = 0;
   kwuSap = gCb->u.dlCb->kwuDlSap + 1;


   oldRetxBo = rbCb->m.amDl.retxBo;


   { SGetStaticBuffer(kwuSap->pst.region, kwuSap->pst.pool, (Data **)&datCfm, (Size) sizeof(KwuDatCfmInfo), 0); };
   datCfm->numSduIds = 0;
   datCfm->rlcId = rbCb->rlcId;

   { mAckSn = (pStaPdu->ackSn - rbCb->m.amDl.vtA) & 0x3ff; };
   { mVts = (rbCb->m.amDl.vtS - rbCb->m.amDl.vtA) & 0x3ff; };

   if(mAckSn > mVts)
   {
      if( L_WARNING < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0001,L_WARNING,DBG_RBID, rbCb->rlcId.rbId, pStaPdu->ackSn, rbCb->m.amDl.vtA, rbCb->rlcId.ueId, rbCb->rlcId.cellId,                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"      ,                                 443      , "Invalid ACK SN = %d received. Current Vta =%d" "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }





                                  ;

      { if (datCfm != 0L) { (Void) SPutStaticBuffer(kwuSap->pst.region, kwuSap->pst.pool, (Data *) datCfm, (Size) sizeof(KwuDatCfmInfo), 0); datCfm = 0L; } };
      return;
   }



   kwAmmDlCheckAndStopPollTmr(gCb, rbCb, mAckSn);


   retxNode = rbCb->m.amDl.retxLst.first;


   if (pStaPdu->nackCnt)
   {
      U8 e2;
      KwSn sn;
      KwSn soStart;
      KwSn soEnd;
      KwSn nackSn;
      KwSn mNackSn;
      KwSn vtA = rbCb->m.amDl.vtA;
      KwSn transWinStartSn = rbCb->m.amDl.vtA;


      U32 idx = 0;


      if(pStaPdu->nackCnt)
      {
         vtA = pStaPdu->nackInfo[0].sn;
      }

      kwStatusNcnt += pStaPdu->nackCnt;


      while (idx < pStaPdu->nackCnt)
      {
         nackSn = pStaPdu->nackInfo[idx].sn;

         if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0002,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, nackSn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"         ,                                    488         , "kwHndlStaRsp: NACK SN = %d UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                     ;

         soStart = pStaPdu->nackInfo[idx].soStart;
         soEnd = pStaPdu->nackInfo[idx].soEnd;


         e2 = (soStart | soEnd);

         sn = transWinStartSn;



         transWinStartSn = (nackSn + 1) & 0x3ff;


         { mNackSn = (nackSn - rbCb->m.amDl.vtA) & 0x3ff; };

         if ((mNackSn > mAckSn) || (mNackSn >= mVts))
         {

            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0003,L_ERROR,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"            ,                                       511            , "Status Pdu is not correct UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                        ;
            { if (datCfm != 0L) { (Void) SPutStaticBuffer(kwuSap->pst.region, kwuSap->pst.pool, (Data *) datCfm, (Size) sizeof(KwuDatCfmInfo), 0); datCfm = 0L; } };
            return;
         }


         while (retxNode)
         {
            retx = (KwRetx *)(retxNode->node);
            { mSn = (retx->amHdr.sn - rbCb->m.amDl.vtA) & 0x3ff; };
            if (mSn < mNackSn)
            {
               retxNode = retxNode->next;
               kwAmmDlProcessSuccessfulReTx(gCb,rbCb, retx, &datCfm);
            }
            else
            {
               break;
            }
         }


         { mSn = (sn - rbCb->m.amDl.vtA) & 0x3ff; };
         while (mSn < mNackSn)
         {


            if ((rbCb->m.amDl.txBuf[sn] != 0L))
            {
               if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0004,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, sn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"               ,                                          544               , "kwHndlStaRsp: Handle ACK (sn = %d) UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                           ;


               kwAmmDlProcessSuccessfulTxPdu(gCb,rbCb, sn, &datCfm);
            }

            sn = (sn + 1) & 0x3ff;
            { mSn = (sn - rbCb->m.amDl.vtA) & 0x3ff; };
         }







         if (rbCb->m.amDl.txBuf[nackSn] != 0L)
         {

            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0005,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"            ,                                       567            , "kwHndlStaRsp: Move PDU from txBuf to retxLst" "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                        ;

            kwAmmDlMoveFrmTxtoRetxBuffer(gCb,
                                         &rbCb->m.amDl,
                                         &retx,
                                         sn);



               retxNode = retx->lstEnt.next;

            idx++;
            continue;
         }



         while (retxNode)
         {
            retx = (KwRetx *)(retxNode->node);
            if (retx->amHdr.sn != nackSn)
            {
               break;
            }



            if ((soEnd != 0) &&
                ((retx->soEnd < soStart) ))
            {
               if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0006,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, sn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"               ,                                          602               , "kwHndlStaRsp: Handle ACK for byte segment, Its " "sn = %d UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                           ;
               if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0007,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, retx->amHdr.so, retx->soEnd, rbCb->rlcId.ueId, rbCb->rlcId.cellId,                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"               ,                                          607               , "soStart and soEnd = %d, %d, UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                           ;

               retxNode = retxNode->next;
               kwAmmDlProcessSuccessfulReTx(gCb,rbCb, retx, &datCfm);
            }
            else
            {





               retxNode = retxNode->next;
               kwAmmDlMarkPduForReTx(gCb, rbCb, retx);
            }
         }

         idx++;
      }



      kwAmmDlUpdateTxAndReTxBufForAckSn(gCb,rbCb, mAckSn, retxNode, &datCfm);


      kwAmmDlSetVtAAndVtMS(&rbCb->m.amDl,vtA);
   }
   else
   {
     kwStatusAckCnt++;

      if( L_UNUSED < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0008,L_UNUSED,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"      ,                                 641      , "kwHndlStaRsp: Received All ACKS UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                  ;


      kwAmmDlUpdateTxAndReTxBufForAckSn(gCb,rbCb, mAckSn, retxNode, &datCfm);


      kwAmmDlSetVtAAndVtMS(&rbCb->m.amDl, pStaPdu->ackSn);
   }

   if(datCfm->numSduIds != 0)
   {
      if(datCfm->numSduIds > 1024)
      {
         if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0009,L_DEBUG,DBG_RBID, datCfm->rlcId.rbId, datCfm->numSduIds, datCfm->numSduIds-1024, rbCb->rlcId.ueId, rbCb->rlcId.cellId,                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"         ,                                    660         , "Sending [%lu] SDU Cfms to PDCP & [%lu] lost for" "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }





                                     ;
         datCfm->numSduIds = 1024;
      }
      kwSduSndCnt += datCfm->numSduIds;

      KwUiKwuDatCfm(&kwuSap->pst, kwuSap->suId, datCfm);
   }
   else
   {
      { if (datCfm != 0L) { (Void) SPutStaticBuffer(kwuSap->pst.region, kwuSap->pst.pool, (Data *) datCfm, (Size) sizeof(KwuDatCfmInfo), 0); datCfm = 0L; } };
   }


   { CmLList *tmpNode; if((tmpNode=((&rbCb->m.amDl.retxLst)->crnt = (&rbCb->m.amDl.retxLst)->first))) rbCb->m.amDl.nxtRetx = (KwRetx *)tmpNode->node; else rbCb->m.amDl.nxtRetx = 0L; };


   if (oldRetxBo != rbCb->m.amDl.retxBo)
   {
      kwAmmSendDStaRsp(gCb, rbCb, &rbCb->m.amDl);
   }

   return;
}
 S32 kwAmmCalculateBo
(
KwAmDl *amDl
)




{
   S32 bo;


   if (amDl->bo < 0)
   {
      amDl->bo = 0;
   }

   if (amDl->cntrlBo < 0)
   {
      amDl->cntrlBo = 0;
   }

   if (amDl->retxBo < 0)
   {
      amDl->retxBo = 0;
   }

   bo = amDl->cntrlBo + amDl->retxBo;


   if (! ((((amDl)->vtS - (amDl)->vtA) & 0x3ff) >= 512))
   {
      bo += amDl->bo;
   }

   return bo;
}
U32 kwRxSdu;
 Void kwAmmQSdu
(
KwCb *gCb,
KwDlRbCb *rbCb,
Buffer *mBuf,
KwuDatReqInfo *datReq
)







{
   KwSdu *sdu;







   ;


   SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&sdu, (Size) sizeof(KwSdu));
   ;

   kwUtlGetCurrTime(&sdu->arrTime);


   SFndLenMsg(mBuf, &sdu->sduSz);

   sdu->mBuf = mBuf;
   sdu->actSz = sdu->sduSz;
   sdu->mode.am.sduId = datReq->sduId;

   sdu->mode.am.rcvdSz = 0;
   sdu->mode.am.isSegmented = 0;
   if (rbCb->m.amDl.nxtTx == 0L)
   {
      if( L_UNUSED < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd000a,L_UNUSED,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"      ,                                  829      , "kwAmmQSdu: Received SDU will be transmitted next" "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                   ;
      rbCb->m.amDl.nxtTx = sdu;
   }


   cmLListAdd2Tail(&rbCb->m.amDl.sduQ, &sdu->lstEnt);
   sdu->lstEnt.node = (U32)sdu;
   rbCb->m.amDl.numSduPdu = 1;
   rbCb->m.amDl.bo = rbCb->m.amDl.bo + sdu->sduSz;
   rbCb->m.amDl.estHdrSz += 2;
   if(!kwDlUtlIsReestInProgress(rbCb))
   {
      kwAmmSendDStaRsp(gCb, rbCb, &rbCb->m.amDl);
   }

   return;
}
static Void kwAmmDlAssembleCntrlInfo
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwDatReq *kwDatReq
)






{
   KwUdxDlSapCb *sapCb;

   ;



   if (kwDatReq->pduSz >= (2 + 3))
   {




      kwDatReq->pduSz -= (rbCb->m.amDl.cntrlBo < 128) ?
                         2 : 3;


      kwAmmCreateStatusPdu(gCb,rbCb,kwDatReq);

      sapCb = (gCb->u.dlCb->udxDlSap + rbCb->udxSapId);
    KwDlUdxStaProhTmrStart(&(gCb->u.dlCb->udxDlSap->pst),
                             sapCb->suId, &(rbCb->rlcId));


      kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = rbCb->m.amDl.mBuf;
      kwDatReq->pduInfo.numPdu++;

      { if (rbCb->m.amDl.pStaPdu != 0L) { (Void) SPutStaticBuffer(gCb->u.dlCb->udxDlSap->pst.region, gCb->u.dlCb->udxDlSap->pst.pool, (Data *) rbCb->m.amDl.pStaPdu, (Size) sizeof(KwUdxDlStaPdu), 0); rbCb->m.amDl.pStaPdu = 0L; } }


                                               ;

      rbCb->m.amDl.pStaPdu = 0L;
      rbCb->m.amDl.mBuf = 0L;
      gRlcStats.amRlcStats.numDLStaPduSent++;
   }

   return;
}
 Void kwAmmProcessSdus
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwDatReq *kwDatReq,
Bool fillCtrlPdu
)







{
   ;







   if ((rbCb->m.amDl.cntrlBo != 0)



                               )
   {
      kwDatReq->boRep.staPduPrsnt = 1;
      kwDatReq->boRep.staPduBo = rbCb->m.amDl.cntrlBo;

      if (rbCb->m.amDl.pStaPdu != 0L)
      {
         kwAmmDlAssembleCntrlInfo (gCb, rbCb, kwDatReq);
      }
      else
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd000b,L_ERROR,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"         ,                                    1014         , "Miscomputation of control Bo. UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                     ;
      }
      rbCb->m.amDl.cntrlBo = 0;
   }


   rbCb->m.amDl.numSduPdu = 0;


   if ((kwDatReq->pduSz > 0) && (rbCb->m.amDl.nxtRetx != 0L))
   {
      kwResegRetxPdus (gCb,rbCb, kwDatReq);
   }


   if ((kwDatReq->pduSz > 0) && (rbCb->m.amDl.nxtTx != 0))
   {
      kwAssembleSdus(gCb,rbCb, kwDatReq);
   }

   if (rbCb->m.amDl.nxtRetx != 0L)
   {
      kwDatReq->boRep.oldestSduArrTime = rbCb->m.amDl.nxtRetx->sduMap[0].sdu->arrTime;
   }
   else if (rbCb->m.amDl.nxtTx != 0L)
   {
      kwDatReq->boRep.oldestSduArrTime = rbCb->m.amDl.nxtTx->arrTime;
   }

   kwDatReq->boRep.bo = kwAmmCalculateBo(&rbCb->m.amDl);
   kwDatReq->boRep.staPduBo = rbCb->m.amDl.cntrlBo;


   kwAmmEstHdrSz (gCb,&rbCb->m.amDl, 2);
   kwDatReq->boRep.estHdrSz = rbCb->m.amDl.estHdrSz;

   if(kwDatReq->pduSz > 0)
   {
      gRlcStats.amRlcStats.numDLBytesUnused += kwDatReq->pduSz;
   }
   return;
}
static Void kwSplitPdu
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwRetx *crnt,
KwRetx *next,
U16 size
)
{
   U8 fi;

   ;

   next->amHdr.sn = crnt->amHdr.sn;


   fi = crnt->amHdr.fi;
   crnt->amHdr.fi = crnt->amHdr.fi | 0x01;
   next->amHdr.fi = fi | 0x02;

   crnt->amHdr.rf = next->amHdr.rf = 1;
   next->amHdr.lsf = crnt->amHdr.lsf;


   crnt->amHdr.lsf = 0;
   crnt->amHdr.p = 0;


   next->segSz = crnt->segSz - size;
   crnt->segSz = size;
   crnt->hdrSz = 4;



   next->soEnd = crnt->soEnd;



   next->amHdr.so = crnt->amHdr.so + crnt->segSz;

   crnt->soEnd = next->amHdr.so - 1;


   crnt->amHdr.numLi = next->amHdr.numLi = 1;


   next->amHdr.p = 0;
   next->amHdr.dc = 0;
   next->amHdr.e = 0;



   next->sduMap[0].sdu = crnt->sduMap[0].sdu;
   crnt->sduMap[0].sduSz = crnt->segSz;
   next->sduMap[0].sduSz = next->segSz;
   next->numSdu = crnt->numSdu;


   SSegMsg(crnt->seg, size, &next->seg);
   next->retxCnt = crnt->retxCnt;
   next->yetToConst = 1;
   next->pendingReTrans = crnt->pendingReTrans;


   { if ((next->amHdr.numLi - 1) % 2) { next->hdrSz = ((3 * (next->amHdr.numLi - 2)) >> 1) + 2; } else { next->hdrSz = (3 * (next->amHdr.numLi - 1)) >> 1; } };
   next->hdrSz += 4;
   rbCb->m.amDl.estHdrSz += next->hdrSz;


   rbCb->m.amDl.retxLst.crnt = &crnt->lstEnt;
   { CmLList *nodeToIns = &next->lstEnt; nodeToIns->node = (U32) next; cmLListInsAfterCrnt(&rbCb->m.amDl.retxLst, nodeToIns); };
   rbCb->m.amDl.nxtRetx = next;

   return;
}
static Void kwSplitPduWithLi
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwRetx *crnt,
KwRetx *next,
U16 size
)
{
   U16 segSz = 0;
   U16 tSz = size;
   U32 liCnt = 0;
   U32 liIdx;
   KwAmHdr *oldHdr;
   KwAmHdr *newHdr;

   ;

   next->amHdr.sn = crnt->amHdr.sn;



   oldHdr = &crnt->amHdr;
   newHdr = &next->amHdr;

   next->numSdu = 0;
   newHdr->numLi = 0;


   while ((liCnt < oldHdr->numLi) && (tSz >= oldHdr->li[liCnt]))
   {
       if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd000c,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, crnt->amHdr.numLi, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"       ,                                  1222       , "kwSplitPduWithLi: numLi of in PDU = %d UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                   ;

       segSz += oldHdr->li[liCnt];
       tSz -= oldHdr->li[liCnt];


       if (tSz > 2)
       {

          tSz -= ((liCnt + 1) % 2) ? 2 : 1;
       }
       else
       {


          tSz = 0;
       }
       liCnt++;
   }
   next->segSz = crnt->segSz - (segSz + tSz);
   crnt->segSz = (segSz + tSz);



   if (tSz && (liCnt < oldHdr->numLi))
   {
      newHdr->li[0] = oldHdr->li[liCnt] - tSz;
      oldHdr->li[liCnt] = tSz;
      next->sduMap[0] = crnt->sduMap[liCnt];
      next->sduMap[0].sduSz -= tSz;
      crnt->sduMap[liCnt].sduSz = tSz;
      newHdr->numLi++;
      next->numSdu++;
      crnt->numSdu = liCnt + 1;
      liCnt++;
   }

   liIdx = 0;
   while ((liCnt + liIdx) < oldHdr->numLi)
   {
      newHdr->li[newHdr->numLi] = oldHdr->li[liCnt + liIdx];
      next->sduMap[next->numSdu++] = crnt->sduMap[liCnt + liIdx];
      liIdx++;
      newHdr->numLi++;
   }
   oldHdr->numLi = liCnt;
   crnt->numSdu = liCnt;


   { if ((next->amHdr.numLi - 1) % 2) { next->hdrSz = ((3 * (next->amHdr.numLi - 2)) >> 1) + 2; } else { next->hdrSz = (3 * (next->amHdr.numLi - 1)) >> 1; } };
   next->hdrSz += 4;
   rbCb->m.amDl.estHdrSz += next->hdrSz;


   next->amHdr.fi = crnt->amHdr.fi;
   if (tSz == 0)
   {



      crnt->amHdr.fi &= 0x02;
      next->amHdr.fi &= 0x01;
   }
   else
   {

      crnt->amHdr.fi |= 0x01;
      next->amHdr.fi |= 0x02;

   }
   crnt->amHdr.p = 0;
   crnt->amHdr.rf = next->amHdr.rf = 1;
   next->amHdr.lsf = crnt->amHdr.lsf;
   crnt->amHdr.lsf = 0;



   next->soEnd = crnt->soEnd;


   crnt->soEnd = crnt->amHdr.so + crnt->segSz - 1;
   next->amHdr.so = crnt->amHdr.so + crnt->segSz;


   next->amHdr.p = 0;
   next->amHdr.dc = 0;
   next->amHdr.e = 0;


   SSegMsg(crnt->seg, crnt->segSz, &next->seg);
   next->retxCnt = crnt->retxCnt;
   next->yetToConst = 1;
   next->pendingReTrans = crnt->pendingReTrans;


   rbCb->m.amDl.retxLst.crnt = &crnt->lstEnt;
   { CmLList *nodeToIns = &next->lstEnt; nodeToIns->node = (U32) next; cmLListInsAfterCrnt(&rbCb->m.amDl.retxLst, nodeToIns); };
   rbCb->m.amDl.nxtRetx = next;

   return;
}
static Void kwResegRetxPdus
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwDatReq *kwDatReq
)






{
   KwAmDl *amDl;
   KwRetx *retx;
   U8 hdr[(2*100)];
   U16 idx;
   Bool segFlg = 1;
   Buffer *pdu;







   ;


   amDl = &rbCb->m.amDl;
   while ((kwDatReq->pduSz > 0) && (amDl->nxtRetx != 0L)&&
          (kwDatReq->pduInfo.numPdu < 2))
   {
      U16 tmpSz;

      retx = amDl->nxtRetx;



      tmpSz = ((retx->segSz + retx->hdrSz)) < (kwDatReq->pduSz) ? ((retx->segSz + retx->hdrSz)) : (kwDatReq->pduSz);

      kwDatReq->pduSz -= (tmpSz < 128) ? 2 : 3;


      if (kwDatReq->pduSz <= retx->hdrSz)
      {
         return;
      }
      kwGetNxtRetx(gCb, &(amDl->nxtRetx));


      if (kwDatReq->pduSz >= (retx->segSz + retx->hdrSz))
      {
         U8 pollBit;

         if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd000d,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"         ,                                    1429         , "kwResegRetxPdus: Send retx buf without segmentation " "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                     ;

         if (retx->yetToConst)
         {

            kwConstructAmHdr(gCb,&retx->amHdr, segFlg, hdr, &idx);

            SAddPreMsgMultInOrder(hdr, idx + 1, retx->seg);
            retx->yetToConst = 0;
         }



         pollBit = kwAmmDlCheckAndSetPoll(gCb,rbCb, 0, 0);
         { U8 fHdr; if (pollBit != retx->amHdr.p) { SRemPreMsg((Data *)&fHdr, retx->seg); if (pollBit == 1) { fHdr = fHdr | 0x20; } else { fHdr = fHdr & 0xdf; } SAddPreMsg ((Data)fHdr, retx->seg); } retx->amHdr.p = pollBit; };

         kwDatReq->pduSz -= retx->hdrSz;
         kwDatReq->pduSz -= retx->segSz;
         rbCb->m.amDl.estHdrSz -= retx->hdrSz;
      }
      else
      {
         KwRetx *tNode;



         if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd000e,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"         ,                                    1472         , "kwResegRetxPdus: Segment retx buf UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                     ;



         kwDatReq->pduSz -= 4;
         if (kwDatReq->pduSz <= 0)
         {
            return;
         }


         SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&tNode, (Size) sizeof(KwRetx));
         tNode->lstEnt.next = 0;
         tNode->lstEnt.prev = 0;


         do { if ((retx)->yetToConst == 0) { Buffer *_tSeg; SSegMsg((retx)->seg, (retx)->hdrSz, &_tSeg); { if ((retx)->seg != 0L) { SPutMsg((retx)->seg); } (retx)->seg = 0L; }; (retx)->seg = _tSeg; } (rbCb)->m.amDl.estHdrSz -= retx->hdrSz;} while(0);


         if ((retx->amHdr.numLi - 1) == 0)
         {
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd000f,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"            ,                                       1508            , "kwResegRetxPdus: No LI for segmentation UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                        ;

            kwSplitPdu(gCb,rbCb, retx, tNode, kwDatReq->pduSz);

         }
         else
         {
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0010,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"            ,                                       1518            , "kwResegRetxPdus: LIs for segmentation UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                        ;


            kwSplitPduWithLi(gCb,rbCb, retx, tNode, kwDatReq->pduSz);
         }
         kwConstructAmHdr(gCb,&retx->amHdr, segFlg, hdr, &idx);
         SAddPreMsgMultInOrder(hdr, idx + 1, retx->seg);

         retx->hdrSz = idx + 1;



         { U8 fHdr; if (0 != retx->amHdr.p) { SRemPreMsg((Data *)&fHdr, retx->seg); if (0 == 1) { fHdr = fHdr | 0x20; } else { fHdr = fHdr & 0xdf; } SAddPreMsg ((Data)fHdr, retx->seg); } retx->amHdr.p = 0; };
         retx->yetToConst = 0;
         kwDatReq->pduSz = 0;
      }

      (SAddMsgRef((retx->seg), (gCb->init.region), (gCb->init.pool), (&pdu)));


      kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = pdu;
      kwDatReq->pduInfo.numPdu++;

      gCb->genSts.pdusRetx += 1;
      retx->soEnd = retx->amHdr.so + retx->segSz - 1;
      retx->pendingReTrans = 0;
      amDl->retxBo -= retx->segSz;
   }

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0011,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, amDl->retxBo, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"   ,                                   1571   , "kwResegRetxPdus: retxBo after resegmentation = %ld" "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                    ;
   amDl->numSduPdu = 0;

   return;
}
static Void kwAssembleSdus
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwDatReq *kwDatReq
)






{
   Buffer *pdu = 0L;
   MsgLen pduSz = kwDatReq->pduSz;
   KwAmDl *amDl = &rbCb->m.amDl;
   KwSdu *sdu = amDl->nxtTx;
   Bool pduCompleted = 0;
   U8 numSdu = 0;
   KwSduMap sduMap[28 + 1];
   Bool nxtTxUpd = 0;
   MsgLen sduSz;
   KwuDiscSduInfo *discSduInfo = 0L;
   KwKwuSapCb* kwuSap = gCb->u.dlCb->kwuDlSap + 1;
   Ticks timeDiff = 0;
   Ticks curTime = 0;
   U8 numNewPdu = 0;
   KwTx *txBuf = 0L;

   volatile U32 startTime = 0;

   ;
   { SGetStaticBuffer(kwuSap->pst.region, kwuSap->pst.pool, (Data **)&discSduInfo, (Size) sizeof(KwuDiscSduInfo), 0); }


                                                     ;
   discSduInfo->numSduIds = 0;
   discSduInfo->rlcId = rbCb->rlcId;

   kwUtlGetCurrTime(&curTime);
   amDl->sduQ.crnt = &sdu->lstEnt;

   while ((pduSz > 2) && (sdu != 0L) &&
          (kwDatReq->pduInfo.numPdu < 2) &&
          (numNewPdu < 2))
   {




      if ((sdu->mode.am.isSegmented == 0) && (rbCb->discTmrInt > 0) &&
            (rbCb->rlcId.rbType == 1))
      {

         timeDiff = (curTime<sdu->arrTime ? ((0xffffffff - sdu->arrTime) + curTime ): (curTime - sdu->arrTime));
         if (timeDiff > rbCb->discTmrInt)
         {
            CmLList* nxtNode;

            SStartTask(&startTime, 30275);




            amDl->numSduPdu++;

            amDl->bo -= sdu->sduSz;


            nxtNode = sdu->lstEnt.next;


            if(discSduInfo->numSduIds > 500)
            {
                if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0012,L_ERROR,DBG_RBID, rbCb->rlcId.rbId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0, 0,                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"                ,                                           1726                , "This is a big error, we shouldn't be here" "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                            ;
                break;
            }

            discSduInfo->sduIds[discSduInfo->numSduIds] = sdu->mode.am.sduId;
            discSduInfo->numSduIds++;

            cmLListDelFrm(&amDl->sduQ, &sdu->lstEnt);

            kwUtlAddSduToBeFreedQueue(gCb, sdu);
            kwUtlRaiseDlCleanupEvent(gCb);



            amDl->sduQ.crnt = nxtNode;

            if(nxtNode)
               sdu = (KwSdu*)nxtNode->node;
            else
               sdu = 0L;


            SStopTask(startTime, 30275);
            continue;
         }
      }
      nxtTxUpd = 0;
      sduSz = sdu->sduSz;





      if (pdu == 0L)
      {


         if (((((amDl)->vtS - (amDl)->vtA) & 0x3ff) >= 512))
         {
            break;
         }



         pduSz -= (pduSz < 128) ? 2 : 3;


         pduSz -= 2;




         if( pduSz <= 0 )
         {
            break;
         }


         SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&txBuf, (Size) sizeof(KwTx));
         amDl->txBuf[amDl->vtS] = txBuf;


         txBuf->numSdu = 0;
         txBuf->pdu = 0L;
         txBuf->amHdr.dc = 0;
         txBuf->amHdr.rf = 0;
         txBuf->amHdr.p = 0;
         txBuf->amHdr.fi = 0;
         txBuf->amHdr.e = 0;
         txBuf->amHdr.lsf = 0;
         txBuf->amHdr.so = 0;
         txBuf->amHdr.numLi = 0;

         txBuf->amHdr.sn = amDl->vtS;


         if (sdu->mode.am.isSegmented)
         {
            txBuf->amHdr.fi = 0x02;
            sdu->mode.am.isSegmented = 0;
         }
         pduCompleted = 0;
      }


      { if ( (pduSz > sduSz) && (sduSz < 2048) ) { pduSz -= (txBuf->amHdr.numLi % 2) ? 1 : 2; } };

      if( pduSz <= 0 )
      {

         { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) txBuf, (Size) sizeof(KwTx)); txBuf = 0L; };
         amDl->txBuf[amDl->vtS]=0L;
         break;
      }

      txBuf->amHdr.li[txBuf->amHdr.numLi++] = sduSz;

      if (pduSz == sduSz)
      {


         if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0013,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, sdu->mode.am.sduId, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"         ,                                         1844         , "kwAssembleSdus: PduSz matches SduSz for sduId = %ld" "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                          ;
         if (pdu == 0L)
         {
            pdu = sdu->mBuf;
            sdu->mBuf = 0L;
         }
         else
         {
            SCatMsg(pdu, sdu->mBuf, 0);
         }






         kwAmmCreatePdu(gCb,rbCb, &(txBuf->amHdr), pdu);
         pduCompleted = 1;


         amDl->numSduPdu++;

         kwUtlIncrementKwuStsSduTx(gCb->u.dlCb->kwuDlSap + rbCb->kwuSapId);
      }
      else if (pduSz > sduSz)
      {


         if (pdu == 0L)
         {
            pdu = sdu->mBuf;
            sdu->mBuf = 0L;
         }
         else
         {
            SCatMsg(pdu, sdu->mBuf, 0);
         }







         if ((sduSz > 2048) || (txBuf->amHdr.numLi >= 28))
         {

            kwAmmCreatePdu(gCb,rbCb, &(txBuf->amHdr), pdu);
            pduCompleted = 1;
         }


         amDl->numSduPdu++;

         kwUtlIncrementKwuStsSduTx(gCb->u.dlCb->kwuDlSap + rbCb->kwuSapId);
      }
      else
      {




         Buffer *remSeg = 0L;


         SSegMsg(sdu->mBuf, pduSz, &remSeg);
         if (pdu == 0L)
         {
            pdu = sdu->mBuf;
         }
         else
         {
            SCatMsg(pdu, sdu->mBuf, 0);
            SPutMsg((sdu->mBuf));;
         }
         sdu->mBuf = remSeg;
         sdu->sduSz -= pduSz;
         sduSz = pduSz;
         sdu->mode.am.isSegmented = 1;


         txBuf->amHdr.fi |= 0x01;





         kwAmmCreatePdu(gCb,rbCb, &(txBuf->amHdr), pdu);
         pduCompleted = 1;

         amDl->nxtTx = sdu;
         nxtTxUpd = 1;
      }


      amDl->bo -= sduSz;

      sduMap[numSdu].sdu = sdu;
      sduMap[numSdu++].sduSz = sduSz;
      if ((pduCompleted) || (numSdu >= 28))
      {

         if ((numSdu > 28) || (numSdu > 100))
         {
            SPutMsg((pdu));;
            pdu = 0L;
            pduSz = 0;
            break;
         }

         kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = pdu;
         kwDatReq->pduInfo.numPdu++;
         numNewPdu++;

         gCb->genSts.pdusSent++;


         txBuf->numSdu = numSdu;
         cmMemcpy((U8*)txBuf->sduMap, (U8 *)sduMap, sizeof(KwSduMap) * numSdu);;
         pdu = 0L;
         numSdu = 0;
      }

      pduSz -= sduSz;


      { CmLList *tmpNode; if((tmpNode = ((&amDl->sduQ)->crnt = ((&amDl->sduQ)->crnt ? (&amDl->sduQ)->crnt->next : (&amDl->sduQ)->first)))) sdu = (KwSdu *)tmpNode->node; else sdu = 0L; };
   }

   kwDatReq->pduSz = pduSz;

   if (!nxtTxUpd)
      amDl->nxtTx = sdu;
   if ((pdu != 0L) && (pduSz > 0) && (numSdu <= (28 +1)))
   {
      if (!pduCompleted)
      {


         kwAmmCreatePdu(gCb,rbCb, &(txBuf->amHdr), pdu);

         kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = pdu;
         kwDatReq->pduInfo.numPdu++;
         numNewPdu++;

         gCb->genSts.pdusSent++;


         { CmLList *tempNode = 0L; ((&amDl->sduQ)->crnt = (&amDl->sduQ)->last); tempNode = ((&amDl->sduQ)->crnt); if (tempNode != 0L) sdu = (KwSdu *)tempNode->node; else sdu = 0L; };
         txBuf->numSdu = numSdu;
         cmMemcpy((U8*)txBuf->sduMap, (U8 *)sduMap, sizeof(KwSduMap) * numSdu);;
      }
   }

   if(discSduInfo->numSduIds != 0)
   {

      KwUiKwuDiscSduCfm(&kwuSap->pst, kwuSap->suId, discSduInfo);
   }
   else
   {
      { if (discSduInfo != 0L) { (Void) SPutStaticBuffer(kwuSap->pst.region, kwuSap->pst.pool, (Data *) discSduInfo, (Size) sizeof(KwuDiscSduInfo), 0); discSduInfo = 0L; } };
   }



   if( L_UNUSED < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0014,L_UNUSED,DBG_RBID, rbCb->rlcId.rbId, amDl->bo, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"   ,                              2165   , "kwAssembleSdus: BO after assembly = %ld UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                               ;
   return;
}
static Bool kwAmmDlCheckAndSetPoll
(
KwCb *gCb,
KwDlRbCb *rbCb,
Bool newPdu,
MsgLen bufSz
)







{
   Bool pollBit = 0;
   KwAmDl *amDl = &(rbCb->m.amDl);

   ;




   if (newPdu)
   {
      amDl->pduWoPoll++;

      amDl->byteWoPoll += bufSz;

     if (((amDl->pollPdu != -1) && (amDl->pduWoPoll >= amDl->pollPdu)) ||
         ((amDl->pollByte != -1) && (amDl->byteWoPoll >= amDl->pollByte)))
     {
        pollBit = 1;
     }
   }


   if (((amDl->nxtTx == 0L) && (amDl->nxtRetx == 0L)) ||
       ((((amDl)->vtS - (amDl)->vtA) & 0x3ff) >= 512))
   {
      pollBit = 1;
   }

   if (pollBit)
   {
      amDl->pduWoPoll = 0;
      amDl->byteWoPoll = 0;

      amDl->pollSn = (amDl->vtS - 1) & 0x3ff;

      if( L_UNUSED < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0015,L_UNUSED,DBG_RBID, rbCb->rlcId.rbId, amDl->pollSn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"      ,                                  2255      , "kwAmmDlCheckAndSetPoll: Poll SN = %d UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                   ;






      if( 1 == kwChkTmr(gCb,(U32)rbCb,4) )
      {
         kwStopTmr(gCb,(U32)rbCb, 4);
      }

      kwStartTmr(gCb,(U32)rbCb, 4);
   }

   return(pollBit);
}
static Void kwAmmCreatePdu
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwAmHdr *amHdr,
Buffer *pdu
)







{
   U8 hdr[(2*100)];
   U16 idx;
   KwTx *txBuf;
   MsgLen pduSz;
   KwAmDl *amDl = &(rbCb->m.amDl);

   ;



   amHdr->sn = amDl->vtS;


   amDl->vtS = (amDl->vtS + 1) & 0x3ff;


   amHdr->rf = 0;
   SFndLenMsg(pdu, &pduSz);


   amHdr->p = kwAmmDlCheckAndSetPoll(gCb,rbCb, 1, pduSz);


   kwConstructAmHdr(gCb,amHdr, 0, hdr, &idx);


   SAddPreMsgMultInOrder(hdr, idx + 1, pdu);
   txBuf = amDl->txBuf[amHdr->sn];
   (SAddMsgRef((pdu), (gCb->init.region), (gCb->init.pool), (&(txBuf->pdu))));
   txBuf->pduSz = pduSz;
   txBuf->hdrSz = idx+1;

   gCb->genSts.bytesSent += pduSz;

   return;
}
static Void kwRemRetxPdu
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwRetx *retx
)






{
   ;

   cmLListDelFrm(&rbCb->m.amDl.retxLst, &retx->lstEnt);

   if( rbCb->m.amDl.retxLst.count == 0)
   {
      rbCb->m.amDl.nxtRetx = 0L;
   }

   if(retx->pendingReTrans == 1)
   {
      rbCb->m.amDl.retxBo -= retx->segSz;
      rbCb->m.amDl.estHdrSz -= retx->hdrSz;
   }

   kwUtlAddReTxPduToBeFreedQueue(gCb, retx);
   kwUtlRaiseDlCleanupEvent(gCb);

   return;
}
static Void kwAmmDlMarkPduForReTx
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwRetx *retx
)






{
   ;
   if (rbCb->m.amDl.maxReTxReached == 1)
   {
      return;
   }

   if(retx->pendingReTrans == 0)
   {
      retx->pendingReTrans = 1;
      ++retx->retxCnt;

      rbCb->m.amDl.retxBo += retx->segSz;
      rbCb->m.amDl.estHdrSz += retx->hdrSz;

      if (retx->retxCnt > rbCb->m.amDl.maxRetx)
      {




         if (1 != rbCb->m.amDl.maxReTxReached)
         {
            rbCb->m.amDl.maxReTxReached = 1;
            rbCb->m.amDl.bo = 0;
            rbCb->m.amDl.cntrlBo = 0;
            rbCb->m.amDl.retxBo = 0;

            kwUtlSndDStaRsp(gCb, rbCb, 0,0,0,0);
            kwAmmSndStaInd(gCb, rbCb, retx);

            tipSendUeRlsInd(rbCb->rlcId.ueId, rbCb->rlcId.cellId, L2_UEREL_CAUSE_MAXRETX);

            gRlcStats.amRlcStats.numDLMaxRetx++;
         }

         kwRemRetxPdu(gCb,rbCb, retx);

         return;
      }


      if (rbCb->m.amDl.nxtRetx == 0L)
      {
         rbCb->m.amDl.nxtRetx = retx;
      }

      gRlcStats.amRlcStats.numDLRetransPdus++;
   }


   return;
}
static Void kwAmmDlCheckIsSDUDelivered
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwSduMap *sduLst,
U8 numSdu,
KwuDatCfmInfo **datCfm
)
{
   U32 i;
   KwSdu *sdu;

   ;

   for (i = 0; i < numSdu && i < 100; i++)
   {
      sdu = sduLst[i].sdu;

      sdu->mode.am.rcvdSz += sduLst[i].sduSz;


      if (sdu->mode.am.rcvdSz == sdu->actSz)
      {

         if((*datCfm)->numSduIds < 1024)
         {
            (*datCfm)->sduIds[(*datCfm)->numSduIds++] = sdu->mode.am.sduId;
         }
         else
         {





            KwKwuSapCb *kwuSap;
            kwuSap = gCb->u.dlCb->kwuDlSap + 1;
            KwUiKwuDatCfm(&kwuSap->pst, kwuSap->suId, *datCfm);

            { SGetStaticBuffer(kwuSap->pst.region, kwuSap->pst.pool, (Data **)&*datCfm, (Size) sizeof(KwuDatCfmInfo), 0); };
            (*datCfm)->numSduIds = 0;
            (*datCfm)->rlcId = rbCb->rlcId;


            (*datCfm)->sduIds[(*datCfm)->numSduIds++] = sdu->mode.am.sduId;
         }


         cmLListDelFrm(&rbCb->m.amDl.sduQ, &sdu->lstEnt);
         kwUtlAddSduToBeFreedQueue(gCb, sdu);
         kwUtlRaiseDlCleanupEvent(gCb);
      }
   }

   return;
}
static Void kwAmmDlProcessSuccessfulTxPdu
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwSn sn,
KwuDatCfmInfo **datCfm
)







{
   ;

   kwAmmDlCheckIsSDUDelivered(gCb,
                              rbCb,
                              rbCb->m.amDl.txBuf[(sn)]->sduMap,
                              rbCb->m.amDl.txBuf[(sn)]->numSdu,
                              datCfm);

   kwUtlAddTxPduToBeFreedQueue(gCb, rbCb->m.amDl.txBuf[sn]);
   kwUtlRaiseDlCleanupEvent(gCb);

   rbCb->m.amDl.txBuf[sn] = 0L;

   return;
}
static Void kwAmmEstHdrSz
(
KwCb *gCb,
KwAmDl *amDl,
U8 type
)






{
   ;;

   if (type == 1)
   {
      amDl->estHdrSz += (amDl->numSduPdu * 2);

   }
   else if (type == 2)
   {
      amDl->estHdrSz -= (amDl->numSduPdu * 2);
   }

   return;
}
static Void kwAmmSndStaInd
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwRetx *retx
)






{
   KwuStaIndInfo *staInd;
   KwKwuSapCb *kwuSap;
   U32 i;

   ;;



   kwuSap = gCb->u.dlCb->kwuDlSap + 1;


   { SGetStaticBuffer(kwuSap->pst.region, kwuSap->pst.pool, (Data **)&staInd, (Size) sizeof(KwuStaIndInfo), 0); };
   cmMemcpy((U8*)&staInd->rlcId, (U8 *)&rbCb->rlcId, sizeof(CmLteRlcId));;
   if(retx->numSdu > 100)
   {
      staInd->numSdu = 100;
   }
   else
   {
      staInd->numSdu = retx->numSdu;
   }
   for (i = 0; i < staInd->numSdu; i++)
   {
      staInd->sduId[i] = retx->sduMap[i].sdu->mode.am.sduId;
   }



   KwUiKwuStaInd(&kwuSap->pst, kwuSap->suId, staInd);


   return;
}
static Void kwGetNxtRetx
(
KwCb *gCb,
KwRetx **retx
)





{
   CmLList *tNode;

   ;;

   do
   {
      tNode = &((*retx)->lstEnt);
      tNode = tNode->next;

      if (tNode)
      {
         *retx = (KwRetx *)tNode->node;
      }
      else
      {
         *retx = 0L;
         return;
      }
   }while((*retx)->pendingReTrans == 0);

   return;
}
 Void kwAmmDlReEstablish
(
KwCb *gCb,
CmLteRlcId rlcId,
KwDlRbCb *rbCb
)






{

   KwDlUeCb *ueCb;
   KwDlRbCb *resetRb;
   KwAmDl* newAmDl;
   KwAmDl* oldAmDl;
   { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&resetRb, (Size) sizeof(KwDlRbCb)) == 0) { cmMemset((U8 *)(resetRb), 0, sizeof(KwDlRbCb)); } else { (resetRb) = 0L; } };


   if(resetRb == 0L)
   {
      return;
   }

   cmMemcpy((U8*)resetRb, (U8 *)rbCb, sizeof(KwDlRbCb));;
   cmMemset((U8 *)&resetRb->m.amDl, (U8)0, sizeof(KwAmDl));;



   newAmDl = &resetRb->m.amDl;
   oldAmDl = &rbCb->m.amDl;

   newAmDl->pollPdu = oldAmDl->pollPdu;
   newAmDl->pollByte = oldAmDl->pollByte;
   newAmDl->maxRetx = oldAmDl->maxRetx;
   newAmDl->pollRetxTmrInt = oldAmDl->pollRetxTmrInt;
   rbCb->boUnRprtdCnt = (U32)0;
   rbCb->lastRprtdBoToMac = (U32)0;
   cmInitTimers(&(resetRb->m.amDl.pollRetxTmr), 1);



   resetRb->m.amDl.vtMs = 512;

   if (0 != kwDbmFetchDlUeCb(gCb,rlcId.ueId, rlcId.cellId, &ueCb))
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0016,L_ERROR,DBG_CELLID, rlcId.cellId, rlcId.ueId, rlcId.rbId, 0, 0,                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"      ,                         2847      , "UeId [%d]: UeCb not found RBID;%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                          ;
      return;
   }

   if(rlcId.rbType == 0)
   {
      ueCb->srbCb[rlcId.rbId] = resetRb;
   }
   else
   {
      ueCb->drbCb[rlcId.rbId] = resetRb;
   }

   ueCb->lCh[rbCb->lch.lChId - 1].dlRbCb = resetRb;

   if((resetRb->rlcId.rbType == 0)
                &&(resetRb->rlcId.rbId == 1))
   {

      kwDlUtlSetReestInProgressForAllRBs(gCb, ueCb);
   }
   else
   {
      kwDlUtlSetReestInProgressForRB(gCb, resetRb);
   }



   { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&resetRb->m.amDl.txBuf, (Size) ((512 << 1) * sizeof(KwTx*))) == 0) { cmMemset((U8 *)(resetRb->m.amDl.txBuf), 0, ((512 << 1) * sizeof(KwTx*))); } else { (resetRb->m.amDl.txBuf) = 0L; } }

                                               ;


   kwAmmFreeDlRbCb(gCb,rbCb);





   if(rlcId.rbType == 0)
   {
      kwDlUtlResetReestInProgress(ueCb->srbCb[rlcId.rbId]);
   }
   else
   {
      kwDlUtlResetReestInProgress(ueCb->drbCb[rlcId.rbId]);
   }

   return;
}
 S16 kwAmmDiscSdu
(
KwCb *gCb,
KwDlRbCb *rbCb,
U32 sduId
)






{
   ;;
   return(1);
}
 Void kwAmmPollRetxTmrExp
(
KwCb *gCb,
KwDlRbCb *rbCb
)





{
   KwRetx *retx;
   KwAmDl *amDl = &(rbCb->m.amDl);
   KwSn sn;

   ;;
   if(0 == rbCb->rlcId.rbType)
   {
      gRlcStats.amRlcStats.numDLPollTimerExpiresSrb++;
   }
   else
   {
      gRlcStats.amRlcStats.numDLPollTimerExpiresDrb++;
   }

   if (((amDl->nxtTx == 0L) && (amDl->nxtRetx == 0L)) ||
        ((((amDl)->vtS - (amDl)->vtA) & 0x3ff) >= 512))
   {
      sn = (amDl->vtS - 1) & 0x3ff;
      if (amDl->txBuf[sn] != 0L)
      {
         kwAmmDlMoveFrmTxtoRetxBuffer(gCb,amDl, &retx, sn);

         if (rbCb->m.amDl.nxtRetx == 0L)
         {
            rbCb->m.amDl.nxtRetx = retx;
         }

         kwAmmSendDStaRsp(gCb, rbCb, &rbCb->m.amDl);
         return;
      }

      { CmLList *tempNode = 0L; ((&amDl->retxLst)->crnt = (&amDl->retxLst)->last); tempNode = ((&amDl->retxLst)->crnt); if (tempNode != 0L) retx = (KwRetx *)tempNode->node; else retx = 0L; };


      if (retx != 0L)
      {
         kwAmmDlMarkPduForReTx(gCb, rbCb, retx);
         kwAmmSendDStaRsp(gCb, rbCb, &rbCb->m.amDl);
      }
   }

   return;
}
static Void kwAmmDlUpdateTxAndReTxBufForAckSn
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwSn mAckSn,
CmLList *retxNode,
KwuDatCfmInfo **datCfm
)
{
   KwSn mSn;
   KwSn sn;
   KwRetx *retx;

   ;;


   while (retxNode)
   {
      retx = (KwRetx *)(retxNode->node);
      retxNode = retxNode->next;
      { mSn = (retx->amHdr.sn - rbCb->m.amDl.vtA) & 0x3ff; };
      if (mSn < mAckSn)
      {
         kwAmmDlProcessSuccessfulReTx(gCb,rbCb, retx, datCfm);
      }
   }





   mSn = 0;
   sn = rbCb->m.amDl.vtA;
   while(mSn < mAckSn)
   {
      if (rbCb->m.amDl.txBuf[sn] != 0L)
      {
         if( L_UNUSED < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0017,L_UNUSED,DBG_RBID, rbCb->rlcId.rbId, sn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"         ,                                   3078         , "kwAmmDlUpdateTxAndReTxBufForAckSn: ACK for PDU " "with sn = %ld UEID:%ld CELLID:%ld", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                    ;

         kwAmmDlProcessSuccessfulTxPdu(gCb,rbCb, sn, datCfm);
      }

      sn = (sn + 1) & 0x3ff;
      { mSn = (sn - rbCb->m.amDl.vtA) & 0x3ff; };
   }

   return;
}
static Void kwConstructAmHdr
(
KwCb *gCb,
KwAmHdr *amHdr,
Bool isSeg,
U8 *hdr,
U16 *idx
)
{
   KwHdrInfo hdrInfo;
   U8 e;
   S16 numLi;
   U8 eb = 0;

   ;;

   cmMemset((U8 *)(&hdrInfo), 0, sizeof(KwHdrInfo));;

   hdrInfo.pEb = 1;
   hdrInfo.pLen = 0;

   hdrInfo.idx = *idx = 0;

   numLi = amHdr->numLi - 1;


   hdr[0] = 1;
   hdr[0] = hdr[0] << (8 - 1);
   eb = 8 - 1;

   hdrInfo.hdr = hdr;
   hdrInfo.eb = eb;

   { hdrInfo.val = amHdr->rf; hdrInfo.len = 1; };
   kwFormBits(&hdrInfo);

   { hdrInfo.val = amHdr->p; hdrInfo.len = 1; };
   kwFormBits(&hdrInfo);

   { hdrInfo.val = amHdr->fi; hdrInfo.len = 2; };
   kwFormBits(&hdrInfo);

   e = (numLi > 0) ? 1 : 0;
   { hdrInfo.val = e; hdrInfo.len = 1; };
   kwFormBits(&hdrInfo);

   { hdrInfo.val = amHdr->sn; hdrInfo.len = 10; };
   kwFormBits(&hdrInfo);

   if (isSeg == 1)
   {
      { hdrInfo.val = amHdr->lsf; hdrInfo.len = 1; };
      kwFormBits(&hdrInfo);

      { hdrInfo.val = amHdr->so; hdrInfo.len = 15; };
      kwFormBits(&hdrInfo);
   }


   if (numLi > 0)
   {
      U8 count = 0;
      while (count < (amHdr->numLi-1))
      {
         e = (numLi > 1) ? 1 : 0;
         { hdrInfo.val = e; hdrInfo.len = 1; };
         kwFormBits(&hdrInfo);

         { hdrInfo.val = amHdr->li[count]; hdrInfo.len = 11; };
         kwFormBits(&hdrInfo);

         count++;
         numLi--;
         if(hdrInfo.idx >= (2*100))
         {
             break;
         }

      }
   }

   hdr = hdrInfo.hdr;
   *idx = hdrInfo.idx;

   return;
}
static Void kwFormBits
(
KwHdrInfo *hdrInfo
)




{
   U16 val = hdrInfo->val;
   U8 len = hdrInfo->len;
   U8 eb = hdrInfo->eb;
   U8 *hdr = 0L;
   U16 idx = hdrInfo->idx;
   U8 pEb = hdrInfo->pEb;
   U8 pLen = hdrInfo->pLen;

   U16 pIdx = idx;
   U16 cIdx = idx + 1;
   U8 tPdu;
   U16 tVal;

   ;;

   hdr = hdrInfo->hdr;

   if (eb >= len)
   {
      if (pEb - pLen == 0)
      {
         idx++;
         pIdx = idx;
      }
      tPdu = (val << (eb - len)) | hdr[pIdx];
      hdr[pIdx] = tPdu;
      pEb = eb;
      pLen = len;
      eb = eb - len;
   }
   else if (eb < len)
   {
      tVal = val;
      if (eb != 0)
      {
         tPdu = (tVal >> (len - eb)) | hdr[pIdx];
         hdr[pIdx] = tPdu;
      }
      if (len - eb == 8)
      {
         hdr[cIdx] = (U8)tVal;
         idx = cIdx;
         pEb = eb;
         pLen = len;
         eb = 8 - (len - eb);
      }
      else if (len - eb < 8)
      {
         if (eb == 0)
            hdr[cIdx] = tVal << (8 - len);
         else
           hdr[cIdx] = tVal << (len - eb);
         idx = cIdx;
         pEb = eb;
         pLen = len;
         eb = 8 - (len - eb);
      }
      else
      {
         hdr[cIdx++] = tVal >> ((len - eb) - 8);
         hdr[cIdx] = tVal << 8;
         idx = cIdx;
         pEb = eb;
         pLen = len;
         eb = 8 - ((len - eb) - 8);
      }
   }

   hdrInfo->val = val;
   hdrInfo->len = len;
   hdrInfo->eb = eb;
   hdrInfo->hdr = hdr;
   hdrInfo->idx = idx;
   hdrInfo->pEb = pEb;
   hdrInfo->pLen = pLen;

   return;
}
static Void kwAmmAddPduToRetxLst
(
KwAmDl *amDl,
KwRetx *retx
)





{
   CmLList *node;
   KwRetx *tRetx;
   KwSn tMSn;
   KwSn retxMSn;

   ;;

   node = amDl->retxLst.last;
   { retxMSn = (retx->amHdr.sn - amDl->vtA) & 0x3ff; };
   while(node != 0L)
   {
      tRetx = (KwRetx *)(node->node);
      { tMSn = (tRetx->amHdr.sn - amDl->vtA) & 0x3ff; };
      if (tMSn > retxMSn)
      {
         node = node->prev;
      }
      else
      {
         break;
      }
   }
   if (node)
   {
      amDl->retxLst.crnt = node;
      cmLListInsAfterCrnt(&amDl->retxLst, &retx->lstEnt);
      retx->lstEnt.node = (U32)retx;
   }
   else
   {
      amDl->retxLst.crnt = amDl->retxLst.first;
      cmLListInsCrnt(&amDl->retxLst, &retx->lstEnt);
      retx->lstEnt.node = (U32)retx;
   }

   if (amDl->nxtRetx == 0L)
   {
      amDl->nxtRetx = retx;
   }

   return;
}
static Void kwAmmDlMoveFrmTxtoRetxBuffer
(
KwCb *gCb,
KwAmDl *amDl,
KwRetx **retx,
KwSn sn
)







{
   U32 maxSdu;
   KwTx* transmittedBuf = amDl->txBuf[sn];
   ;;


   SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&*retx, (Size) sizeof(KwRetx));
   (*retx)->seg = transmittedBuf->pdu;
   (*retx)->segSz = transmittedBuf->pduSz;

   (*retx)->soEnd = transmittedBuf->pduSz - 1;

   (*retx)->hdrSz = transmittedBuf->hdrSz;
   (*retx)->numSdu = transmittedBuf->numSdu;
   (*retx)->retxCnt = 1;
   (*retx)->yetToConst = 0;
   (*retx)->pendingReTrans = 1;


   (*retx)->lstEnt.next = 0;
   (*retx)->lstEnt.prev = 0;
   maxSdu = (transmittedBuf->numSdu < 28)?transmittedBuf->numSdu:
                                                   28;

   cmMemcpy((U8*)(*retx)->sduMap, (U8 *)transmittedBuf->sduMap, sizeof(KwSduMap) * maxSdu);

                                        ;

   cmMemcpy((U8*)&((*retx)->amHdr), (U8 *)&transmittedBuf->amHdr, sizeof(KwAmHdr));;
   (*retx)->amHdr.lsf = 1;
   kwAmmAddPduToRetxLst(amDl, (*retx));


   { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) transmittedBuf, (Size) sizeof(KwTx)); transmittedBuf = 0L; };
   amDl->txBuf[sn] = 0L;


   amDl->retxBo += (*retx)->segSz;
   amDl->estHdrSz += (*retx)->hdrSz;

   gRlcStats.amRlcStats.numDLRetransPdus++;
   return;
}
 Void kwAmmFreeDlRbCb
(
KwCb *gCb,
KwDlRbCb *rbCb
)





{

   if(1 == kwChkTmr(gCb,(U32)rbCb,4))
   {
      kwStopTmr(gCb,(U32)rbCb, 4);
   }


   rbCb->rlsLnk.node = (U32)rbCb;
   cmLListAdd2Tail(&gCb->u.dlCb->toBeFreed.rbLst, &rbCb->rlsLnk);


   cmLListCatLList(&(gCb->u.dlCb->toBeFreed.sduLst),&(rbCb->m.amDl.sduQ));

   kwUtlRaiseDlCleanupEvent(gCb);

   return;
}
static Void kwAmmCalcBytesReqdForNacks
(
KwNackInfo *nackInfo,
U16 *numOfBytes,
U16 *numOfBits
)






{
   if(nackInfo->isSegment)
   {
      *numOfBits += 42;
   }
   else
   {
      *numOfBits += 12;
   }


   *numOfBytes = (*numOfBits + 7) >> 3;

   return;
}
static Void kwAmmCreateStatusPdu
(
KwCb *gCb,
KwDlRbCb *rbCb,
KwDatReq *kwDatReq
)






{
    KwCntrlInfo cntrlInfo;
    KwSn sn;
    KwSn ack_sn;
    Buffer *mBuf;
    MsgLen cntrlPduSz;
    U16 staPdu[(((100*42+ 14 +7)/8)+1)/2 ];
    U8 cntrlPdu[((100*42+ 14 +7)/8)];
    U16 idx = 0;
    U8 emtBits = 0;
    U16 e1 = 0;
    U16 e1Idx = 0;
    U8 e1eb = 0;
    U16 soStart = 0;
    U16 soEnd = 0;
    U16 i = 0;
    U16 j = 0;
    KwSn tSn = 0;
    KwUdxDlStaPdu *pStaPdu;
    U16 numOfBits;
    U16 bytesToEncode;
    KwNackInfo *kwNackInfo;
    Bool ackFlagSet = 0;
    U16 maxCPduLen = ((100*42+ 14 +7)/8);
    U16 nkCnt = 0;

    ;


    pStaPdu = rbCb->m.amDl.pStaPdu;

    cmMemset((U8 *)(&cntrlInfo), 0, sizeof(KwCntrlInfo));;

    ack_sn = 0;
    staPdu[idx] = ack_sn;


    emtBits = 2;


    { cntrlInfo.val = e1; cntrlInfo.len = 1; cntrlInfo.idx = idx; cntrlInfo.emtBits = emtBits; };
    kwFormDlCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
    idx = cntrlInfo.idx;
    emtBits = cntrlInfo.emtBits;

    e1Idx = 0;
    e1eb = 0;
    numOfBits = 15;
    bytesToEncode = 2;

    for(nkCnt = 0;nkCnt < pStaPdu->nackCount; nkCnt++)
    {
       sn = pStaPdu->nackInfo[nkCnt].sn;

       kwNackInfo = &(pStaPdu->nackInfo[nkCnt]);


       kwAmmCalcBytesReqdForNacks(kwNackInfo, &bytesToEncode, &numOfBits);
       if( kwDatReq->pduSz >= bytesToEncode)
       {

          if(!kwNackInfo->isSegment)
          {
             tSn = sn;

             if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0018,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, sn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"             ,                                        3634             , "kwAssembleCntrlInfo: Missing PDU SN = %d " "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                         ;


             staPdu[e1Idx] = staPdu[e1Idx] | 2 << ((e1eb+1)-1);;




             tSn = sn << 2;
             { cntrlInfo.val = tSn; cntrlInfo.len = 12; cntrlInfo.idx = idx; cntrlInfo.emtBits = emtBits; };
             kwFormDlCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
             { e1Idx = cntrlInfo.e1Idx; e1eb = cntrlInfo.e1eb; idx = cntrlInfo.idx; emtBits = cntrlInfo.emtBits; };
             gRlcStats.amRlcStats.numDLNacksInStaPdu++;
          }
          else
          {
             tSn = sn;

             staPdu[e1Idx] = staPdu[e1Idx] | 2 << ((e1eb+1)-1);;


             tSn = sn << 2;
             tSn |= 1;


             { cntrlInfo.val = tSn; cntrlInfo.len = 12; cntrlInfo.idx = idx; cntrlInfo.emtBits = emtBits; }
                           ;
             kwFormDlCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
             { e1Idx = cntrlInfo.e1Idx; e1eb = cntrlInfo.e1eb; idx = cntrlInfo.idx; emtBits = cntrlInfo.emtBits; };

             soStart = kwNackInfo->soStart;
             soEnd = kwNackInfo->soEnd;


             { cntrlInfo.val = soStart; cntrlInfo.len = 15; cntrlInfo.idx = idx; cntrlInfo.emtBits = emtBits; };
             kwFormDlCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
             { e1Idx = cntrlInfo.e1Idx; e1eb = cntrlInfo.e1eb; idx = cntrlInfo.idx; emtBits = cntrlInfo.emtBits; };

             { cntrlInfo.val = soEnd; cntrlInfo.len = 15; cntrlInfo.idx = idx; cntrlInfo.emtBits = emtBits; };
             kwFormDlCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
             { e1Idx = cntrlInfo.e1Idx; e1eb = cntrlInfo.e1eb; idx = cntrlInfo.idx; emtBits = cntrlInfo.emtBits; };

             if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd0019,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, sn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"             ,                                             3681             , "kwAssembleCntrlInfo: Missing byte segment's" "SN:%d UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                              ;

             if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd001a,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, soStart, soEnd, rbCb->rlcId.ueId, rbCb->rlcId.cellId,                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"             ,                                             3689             , "kwAssembleCntrlInfo: Missing byte segment's" "soStart and soEnd = %d, %d " "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }





                                              ;

             gRlcStats.amRlcStats.numDLNacksInStaPdu++;
          }
       }

       else
       {
          ack_sn = kwNackInfo->sn;
          idx = cntrlInfo.idx;
          idx = cntrlInfo.idx;
          emtBits = cntrlInfo.emtBits;

          if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd001b,L_DEBUG,DBG_RBID, rbCb->rlcId.rbId, ack_sn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"          ,                                          3707          , "kwAssembleCntrlInfo: ACK PDU's SN = %d " "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                           ;

          staPdu[0] = staPdu[0] | (ack_sn << 2);
          ackFlagSet = 1;
          break;
       }
    }

    if(0 == ackFlagSet)
    {
       ack_sn = pStaPdu->ackSn;
       idx = cntrlInfo.idx;
       idx = cntrlInfo.idx;
       emtBits = cntrlInfo.emtBits;

       if( L_UNUSED < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbd001c,L_UNUSED,DBG_RBID, rbCb->rlcId.rbId, ack_sn, rbCb->rlcId.ueId, rbCb->rlcId.cellId, 0,                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterlc/kw_amm_dl.c"       ,                               3727       , "kwAssembleCntrlInfo: ACK PDU's SN = %d" "UEID:%d CELLID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                ;

       staPdu[0] = staPdu[0] | (ack_sn << 2);
    }


    for (i = 0, j = 0; i <= idx; i++)
    {
       U16 tmpPdu;
       tmpPdu = staPdu[i];
       cntrlPdu[j++] = (U8)(tmpPdu >> 8);
       cntrlPdu[j++] = (U8)staPdu[i];
    }



    SGetMsg((gCb->init.region), (gCb->init.pool),&mBuf);







    cntrlPduSz = (emtBits >= 8) ? j-1 : j;
    SAddPstMsgMult (cntrlPdu, cntrlPduSz, mBuf);

    kwDatReq->pduSz -= cntrlPduSz;

    rbCb->m.amDl.mBuf = mBuf;

    return;
}
static Void kwFormDlCntrlBits
(
KwCb *gCb,
KwCntrlInfo *cntrlInfo,
U16 *staPdu,
U16 *maxCPduLen
)







{
    U16 val = cntrlInfo->val;
    U16 len = cntrlInfo->len;
    U16 idx = cntrlInfo->idx;
    U8 eb = cntrlInfo->emtBits;
    U16 e1Idx = cntrlInfo->e1Idx;
    U16 e2Idx = cntrlInfo->e2Idx;
    U8 e1eb = cntrlInfo->e1eb;

    U16 pIdx = idx;
    U16 cIdx = idx + 1;
    U16 tPdu;
    U16 tVal = val;

    ;;


    if (eb >= len)
    {
        tPdu = (tVal << (eb-len) ) | staPdu[pIdx];
        staPdu[pIdx] = tPdu;
        eb = eb - len;
        if (len != 15)
        {

            e1Idx = e2Idx = pIdx;
            e1eb = eb;
        }
    }
    else
    {
        if (eb == 0)
        {
            staPdu[cIdx] = 0;
            tVal = tVal << (16 - len);
            staPdu[cIdx] = tVal;
            eb = 16 - len;

            if (len != 15)
            {
                e1Idx = e2Idx = cIdx;
                e1eb = eb;
            }
        }
        else
        {
            tPdu = (tVal >> (len - eb)) | staPdu[pIdx];
            staPdu[pIdx] = tPdu;
            staPdu[cIdx] = 0;
            staPdu[cIdx] = tVal << (16 - (len - eb));
            eb = 16 - (len - eb);

            if (len != 15)
            {

                if (eb == 15)
                {
                    e1Idx = pIdx;
                    e2Idx = cIdx;
                    e1eb = 0;
                }
                else
                {
                    e1Idx = e2Idx = cIdx;
                    e1eb = eb;
                }
            }
        }

        if ((cIdx - idx == 1) && (idx != 0))
        {
            *maxCPduLen -= 2;
        }
        idx = cIdx;
    }

    cntrlInfo->val = val;
    cntrlInfo->len = (U8)len;
    cntrlInfo->idx = idx;
    cntrlInfo->emtBits = eb;
    cntrlInfo->e1Idx = e1Idx;
    cntrlInfo->e2Idx = e2Idx;
    cntrlInfo->e1eb = e1eb;

    return;
}
