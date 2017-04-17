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



typedef U8 UmtsRbId;
typedef U32 UmtsUrnti;
typedef U16 UmtsCrnti;
typedef U8 UmtsLogChType;
typedef U8 UmtsRlcSvcType;
typedef U8 UmtsOperatingMode;
typedef U8 UmtsUeType;
typedef U16 UmtsHrnti;
typedef U16 UmtsErnti;
typedef U32 UmtsCellId;
typedef U32 UmtsCRNCCtxId;

typedef struct umtsCPICHInfo
{
   Bool barredStatus;
   U16 primScramblingCode;
} UmtsCPICHInfo;


typedef struct umtsFreqInfo
{
   Bool barredStatus;
   U16 uarfcnUl;
   U16 uarfcnDl;
   U8 numCells;
   UmtsCPICHInfo *primCPICHInfo;
} UmtsFreqInfo;


typedef struct umtsCellInfoLst
{
   U8 numFddCell;
   UmtsFreqInfo *cellInfo;
} UmtsCellInfoLst;

typedef struct umtsCctrchId
{
   U8 cctrchIdentity;
   U8 tFlag;
   union {
      UmtsCellId cellId;
      U32 ueId;
   } t;
}UmtsCctrchId;

typedef struct umtsTrChId
{
   UmtsCctrchId cctrchId;
   U8 chType;
   U16 chIdentity;



}UmtsTrChId;

typedef struct umtsRlcId
{
   U8 tFlag;
   union {
   U32 ueId;
   U32 cellId;
   } t;
   U8 rbId;
}UmtsRlcId;


typedef struct umtsPdcpId
{
   U8 cmnOrDed;
   union {
      UmtsUrnti ueId;
      U32 cmnId;
   } u;
   UmtsRbId rbId;
} UmtsPdcpId;

typedef struct umtsLogChId
{
   UmtsLogChType logCh;
   U8 inst;
   union {
      U32 ueId;
      U32 cellId;
   } type;
   U8 logChId;
}UmtsLogChId;

typedef struct umtsPiBitMap
{
   U8 len;
   U8 map[18];
} UmtsPiBitMap;







extern S16 cmUnpkUmtsRlcId (UmtsRlcId *rlcId, Buffer *mBuf);
extern S16 cmUnpkUmtsUrnti (UmtsUrnti *ueId, Buffer *mBuf);
extern S16 cmUnpkUmtsCrnti (UmtsCrnti *ueId, Buffer *mBuf);
extern S16 cmUnpkUmtsRbId (UmtsRbId *rbId, Buffer *mBuf);
extern S16 cmUnpkUmtsLogChId (UmtsLogChId *logChId, Buffer *mBuf);
extern S16 cmUnpkUmtsLogChType (UmtsLogChType *logCh, Buffer *mBuf);
extern S16 cmUnpkUmtsRlcSvcType (UmtsRlcSvcType *svc, Buffer *mBuf);
extern S16 cmUnpkUmtsOperatingMode (UmtsOperatingMode *mode,Buffer *mBuf);
extern S16 cmUnpkUmtsTrChId (UmtsTrChId *trCh, Buffer *mBuf);
extern S16 cmUnpkUmtsPiBitMap (UmtsPiBitMap *pi, Buffer *mBuf);
extern S16 cmUnpkUmtsCPICHInfo ( UmtsCPICHInfo *param, Buffer *mBuf);
extern S16 cmUnpkUmtsFreqInfo (UmtsFreqInfo *param,Ptr ptr,Buffer *mBuf);
extern S16 cmUnpkUmtsCellInfoLst (UmtsCellInfoLst *param,Ptr ptr,Buffer *mBuf);

extern S16 cmPkUmtsTrChId (UmtsTrChId *trCh, Buffer *mBuf);
extern S16 cmPkUmtsOperatingMode (UmtsOperatingMode *mode, Buffer *mBuf);
extern S16 cmPkUmtsRlcSvcType (UmtsRlcSvcType *svc, Buffer *mBuf);
extern S16 cmPkUmtsLogChId (UmtsLogChId *logChId, Buffer *mBuf);
extern S16 cmPkUmtsLogChType (UmtsLogChType *logCh, Buffer *mBuf);
extern S16 cmPkUmtsRlcId (UmtsRlcId *rlcId, Buffer *mBuf);
extern S16 cmPkUmtsCrnti (UmtsCrnti *ueId, Buffer *mBuf);
extern S16 cmPkUmtsUrnti (UmtsUrnti *ueId, Buffer *mBuf);
extern S16 cmPkUmtsRbId (UmtsRbId *rbId, Buffer *mBuf);
extern S16 cmPkUmtsPiBitMap (UmtsPiBitMap *pi, Buffer *mBuf);
extern S16 cmPkUmtsCPICHInfo ( UmtsCPICHInfo *param, Buffer *mBuf);
extern S16 cmPkUmtsFreqInfo ( UmtsFreqInfo *param, Buffer *mBuf);
extern S16 cmPkUmtsCellInfoLst ( UmtsCellInfoLst *param, Buffer *mBuf);

extern S16 cmPkUmtsCellId (UmtsCellId *param,Buffer *mBuf);
extern S16 cmPkUmtsHrnti (UmtsHrnti *param,Buffer *mBuf);
extern S16 cmPkUmtsCRNCCtxId (UmtsCRNCCtxId *ctxId,Buffer *mBuf);

extern S16 cmUnpkUmtsCellId (UmtsCellId *param,Buffer *mBuf);
extern S16 cmUnpkUmtsHrnti (UmtsHrnti *param,Buffer *mBuf);
extern S16 cmUnpkUmtsCRNCCtxId (UmtsCRNCCtxId *param,Buffer *mBuf);



extern S16 cmUnpkUmtsCctrchId ( UmtsCctrchId *ccTrCh, Buffer *mBuf )


  ;

extern S16 cmPkUmtsCctrchId ( UmtsCctrchId *ccTrCh, Buffer *mBuf )


  ;

extern S16 cmPkUmtsPdcpId (UmtsPdcpId *PdcpId, Buffer *mBuf);
extern S16 cmUnpkUmtsPdcpId (UmtsPdcpId *pdcpId, Buffer *mBuf);
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






typedef struct cmPAsnErrIeInfo
{
   U16 errType;
   U16 criticality;
   U32 ieId;
}CmPAsnErrIeInfo;







typedef struct cmPAsnErr
{
   S16 errCode;


   U16 errCause;
   U16 ieCount;
   CmPAsnErrIeInfo ieInfo[15];


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
typedef enum enumSztCriticality
{
 SztCriticalityrejectEnum,
 SztCriticalityignoreEnum,
 SztCriticalitynotifyEnum
} EnumSztCriticality;
typedef TknU32 SztCriticality;


typedef enum enumSztPresence
{
 SztPresenceoptionalEnum,
 SztPresenceconditionalEnum,
 SztPresencemandatoryEnum
} EnumSztPresence;
typedef TknU32 SztPresence;


typedef TknU32 SztPrivIE_IDlocal;

typedef struct s1apPrivIE_ID
{
 TknU8 choice;
 union {
  SztPrivIE_IDlocal local;
 } val;
} SztPrivIE_ID;


typedef TknU32 SztProcedureCode;


typedef TknU32 SztProtExtnID;


typedef TknU32 SztProtIE_ID;


typedef enum enumSztTrgMsg
{
 SztTrgMsginitiating_messageEnum,
 SztTrgMsgsuccessful_outcomeEnum,
 SztTrgMsgunsuccessfull_outcomeEnum
} EnumSztTrgMsg;
typedef TknU32 SztTrgMsg;


typedef TknStrOSXL SztTBCD_STRING;

typedef SztTBCD_STRING SztPLMNidentity;

typedef TknBStr32 SztCellIdentity;
typedef struct s1ap_ExtnEUTRAN_CGI_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnEUTRAN_CGI_ExtIEsCls;
typedef struct s1apProtExtnField_EUTRAN_CGI_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnEUTRAN_CGI_ExtIEsCls extensionValue;
} SztProtExtnField_EUTRAN_CGI_ExtIEs;

typedef struct s1apProtExtnCont_EUTRAN_CGI_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_EUTRAN_CGI_ExtIEs *member;
}SztProtExtnCont_EUTRAN_CGI_ExtIEs;

typedef struct s1apEUTRAN_CGI
{
 TknPres pres;
 SztPLMNidentity pLMNidentity;
 SztCellIdentity cell_ID;
 SztProtExtnCont_EUTRAN_CGI_ExtIEs iE_Extns;
} SztEUTRAN_CGI;

typedef struct s1apCellIdLstforMDT
{
 TknU16 noComp;
 SztEUTRAN_CGI *member;
}SztCellIdLstforMDT;

typedef struct s1ap_ExtnCellBasedMDT_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCellBasedMDT_ExtIEsCls;
typedef struct s1apProtExtnField_CellBasedMDT_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCellBasedMDT_ExtIEsCls extensionValue;
} SztProtExtnField_CellBasedMDT_ExtIEs;

typedef struct s1apProtExtnCont_CellBasedMDT_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CellBasedMDT_ExtIEs *member;
}SztProtExtnCont_CellBasedMDT_ExtIEs;

typedef struct s1apCellBasedMDT
{
 TknPres pres;
 SztCellIdLstforMDT cellIdLstforMDT;
 SztProtExtnCont_CellBasedMDT_ExtIEs iE_Extns;
} SztCellBasedMDT;


typedef TknStr4 SztTAC;
typedef struct s1apTALstforMDT
{
 TknU16 noComp;
 SztTAC *member;
}SztTALstforMDT;

typedef struct s1ap_ExtnTABasedMDT_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTABasedMDT_ExtIEsCls;
typedef struct s1apProtExtnField_TABasedMDT_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTABasedMDT_ExtIEsCls extensionValue;
} SztProtExtnField_TABasedMDT_ExtIEs;

typedef struct s1apProtExtnCont_TABasedMDT_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TABasedMDT_ExtIEs *member;
}SztProtExtnCont_TABasedMDT_ExtIEs;

typedef struct s1apTABasedMDT
{
 TknPres pres;
 SztTALstforMDT tALstforMDT;
 SztProtExtnCont_TABasedMDT_ExtIEs iE_Extns;
} SztTABasedMDT;

typedef struct s1ap_ExtnTAI_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTAI_ExtIEsCls;
typedef struct s1apProtExtnField_TAI_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTAI_ExtIEsCls extensionValue;
} SztProtExtnField_TAI_ExtIEs;

typedef struct s1apProtExtnCont_TAI_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TAI_ExtIEs *member;
}SztProtExtnCont_TAI_ExtIEs;

typedef struct s1apTAI
{
 TknPres pres;
 SztPLMNidentity pLMNidentity;
 SztTAC tAC;
 SztProtExtnCont_TAI_ExtIEs iE_Extns;
} SztTAI;

typedef struct s1apTAILstforMDT
{
 TknU16 noComp;
 SztTAI *member;
}SztTAILstforMDT;

typedef struct s1ap_ExtnTAIBasedMDT_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTAIBasedMDT_ExtIEsCls;
typedef struct s1apProtExtnField_TAIBasedMDT_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTAIBasedMDT_ExtIEsCls extensionValue;
} SztProtExtnField_TAIBasedMDT_ExtIEs;

typedef struct s1apProtExtnCont_TAIBasedMDT_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TAIBasedMDT_ExtIEs *member;
}SztProtExtnCont_TAIBasedMDT_ExtIEs;

typedef struct s1apTAIBasedMDT
{
 TknPres pres;
 SztTAILstforMDT tAILstforMDT;
 SztProtExtnCont_TAIBasedMDT_ExtIEs iE_Extns;
} SztTAIBasedMDT;

typedef struct s1apAreaScopeOfMDT
{
 TknU8 choice;
 union {
  SztCellBasedMDT cellBased;
  SztTABasedMDT tABased;
  SztTAIBasedMDT tAIBased;
 } val;
} SztAreaScopeOfMDT;


typedef TknU32 SztPriorityLvl;


typedef enum enumSztPre_emptionCapblty
{
 SztPre_emptionCapbltyshall_not_trigger_pre_emptionEnum,
 SztPre_emptionCapbltymay_trigger_pre_emptionEnum
} EnumSztPre_emptionCapblty;
typedef TknU32 SztPre_emptionCapblty;


typedef enum enumSztPre_emptionVulnerability
{
 SztPre_emptionVulnerabilitynot_pre_emptableEnum,
 SztPre_emptionVulnerabilitypre_emptableEnum
} EnumSztPre_emptionVulnerability;
typedef TknU32 SztPre_emptionVulnerability;

typedef struct s1ap_ExtnAllocnAndRetentionPriority_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls;
typedef struct s1apProtExtnField_AllocnAndRetentionPriority_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls extensionValue;
} SztProtExtnField_AllocnAndRetentionPriority_ExtIEs;

typedef struct s1apProtExtnCont_AllocnAndRetentionPriority_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *member;
}SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs;

typedef struct s1apAllocnAndRetentionPriority
{
 TknPres pres;
 SztPriorityLvl priorityLvl;
 SztPre_emptionCapblty pre_emptionCapblty;
 SztPre_emptionVulnerability pre_emptionVulnerability;
 SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs iE_Extns;
} SztAllocnAndRetentionPriority;


typedef TknU32 SztE_RAB_ID;


typedef TknU32 SztPDCP_SN;


typedef TknU32 SztHFN;

typedef struct s1ap_ExtnCOUNTvalue_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCOUNTvalue_ExtIEsCls;
typedef struct s1apProtExtnField_COUNTvalue_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCOUNTvalue_ExtIEsCls extensionValue;
} SztProtExtnField_COUNTvalue_ExtIEs;

typedef struct s1apProtExtnCont_COUNTvalue_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_COUNTvalue_ExtIEs *member;
}SztProtExtnCont_COUNTvalue_ExtIEs;

typedef struct s1apCOUNTvalue
{
 TknPres pres;
 SztPDCP_SN pDCP_SN;
 SztHFN hFN;
 SztProtExtnCont_COUNTvalue_ExtIEs iE_Extns;
} SztCOUNTvalue;


typedef TknStrBSXL SztReceiveStatusofULPDCPSDUs;

typedef TknU32 SztPDCP_SNExtended;


typedef TknU32 SztHFNMdfd;

typedef struct s1ap_ExtnCOUNTValueExtended_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCOUNTValueExtended_ExtIEsCls;
typedef struct s1apProtExtnField_COUNTValueExtended_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCOUNTValueExtended_ExtIEsCls extensionValue;
} SztProtExtnField_COUNTValueExtended_ExtIEs;

typedef struct s1apProtExtnCont_COUNTValueExtended_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_COUNTValueExtended_ExtIEs *member;
}SztProtExtnCont_COUNTValueExtended_ExtIEs;

typedef struct s1apCOUNTValueExtended
{
 TknPres pres;
 SztPDCP_SNExtended pDCP_SNExtended;
 SztHFNMdfd hFNMdfd;
 SztProtExtnCont_COUNTValueExtended_ExtIEs iE_Extns;
} SztCOUNTValueExtended;


typedef TknStrBSXL SztReceiveStatusOfULPDCPSDUsExtended;
typedef struct s1ap_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls{
 union {
  SztCOUNTValueExtended sztid_ULCOUNTValueExtended;
  SztCOUNTValueExtended sztid_DLCOUNTValueExtended;
  SztReceiveStatusOfULPDCPSDUsExtended sztReceiveStatusOfULPDCPSDUsExtended;
 } u;
} Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls;
typedef struct s1apProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls extensionValue;
} SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs;

typedef struct s1apProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs
{
 TknU16 noComp;
 SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *member;
}SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs;

typedef struct s1apBrs_SubjToStatusTfr_Item
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztCOUNTvalue uL_COUNTvalue;
 SztCOUNTvalue dL_COUNTvalue;
 SztReceiveStatusofULPDCPSDUs receiveStatusofULPDCPSDUs;
 SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs iE_Extns;
} SztBrs_SubjToStatusTfr_Item;

typedef struct s1ap_ValueBrs_SubjToStatusTfr_ItemIEsCls{
 union {
  SztBrs_SubjToStatusTfr_Item sztBrs_SubjToStatusTfr_Item;
 } u;
} Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls;
typedef struct s1apProtIE_Field_Brs_SubjToStatusTfr_ItemIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls value;
} SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs;


typedef SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs;
typedef struct s1apBrs_SubjToStatusTfrLst
{
 TknU16 noComp;
 SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs *member;
}SztBrs_SubjToStatusTfrLst;


typedef TknStrOSXL SztBitRate;

typedef struct s1apBPLMNs
{
 TknU16 noComp;
 SztPLMNidentity *member;
}SztBPLMNs;


typedef TknU32 SztNumberOfBroadcasts;

typedef struct s1ap_ExtnCellID_Cancelled_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCellID_Cancelled_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CellID_Cancelled_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCellID_Cancelled_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CellID_Cancelled_Item_ExtIEs;

typedef struct s1apProtExtnCont_CellID_Cancelled_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CellID_Cancelled_Item_ExtIEs *member;
}SztProtExtnCont_CellID_Cancelled_Item_ExtIEs;

typedef struct s1apCellID_Cancelled_Item
{
 TknPres pres;
 SztEUTRAN_CGI eCGI;
 SztNumberOfBroadcasts numberOfBroadcasts;
 SztProtExtnCont_CellID_Cancelled_Item_ExtIEs iE_Extns;
} SztCellID_Cancelled_Item;

typedef struct s1apCellID_Cancelled
{
 TknU16 noComp;
 SztCellID_Cancelled_Item *member;
}SztCellID_Cancelled;

typedef struct s1ap_ExtnCancelledCellinTAI_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CancelledCellinTAI_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CancelledCellinTAI_Item_ExtIEs;

typedef struct s1apProtExtnCont_CancelledCellinTAI_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CancelledCellinTAI_Item_ExtIEs *member;
}SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs;

typedef struct s1apCancelledCellinTAI_Item
{
 TknPres pres;
 SztEUTRAN_CGI eCGI;
 SztNumberOfBroadcasts numberOfBroadcasts;
 SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs iE_Extns;
} SztCancelledCellinTAI_Item;

typedef struct s1apCancelledCellinTAI
{
 TknU16 noComp;
 SztCancelledCellinTAI_Item *member;
}SztCancelledCellinTAI;

typedef struct s1ap_ExtnTAI_Cancelled_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTAI_Cancelled_Item_ExtIEsCls;
typedef struct s1apProtExtnField_TAI_Cancelled_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTAI_Cancelled_Item_ExtIEsCls extensionValue;
} SztProtExtnField_TAI_Cancelled_Item_ExtIEs;

typedef struct s1apProtExtnCont_TAI_Cancelled_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TAI_Cancelled_Item_ExtIEs *member;
}SztProtExtnCont_TAI_Cancelled_Item_ExtIEs;

typedef struct s1apTAI_Cancelled_Item
{
 TknPres pres;
 SztTAI tAI;
 SztCancelledCellinTAI cancelledCellinTAI;
 SztProtExtnCont_TAI_Cancelled_Item_ExtIEs iE_Extns;
} SztTAI_Cancelled_Item;

typedef struct s1apTAI_Cancelled
{
 TknU16 noComp;
 SztTAI_Cancelled_Item *member;
}SztTAI_Cancelled;


typedef TknStrOSXL SztEmergencyAreaID;
typedef struct s1ap_ExtnCancelledCellinEAI_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CancelledCellinEAI_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CancelledCellinEAI_Item_ExtIEs;

typedef struct s1apProtExtnCont_CancelledCellinEAI_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CancelledCellinEAI_Item_ExtIEs *member;
}SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs;

typedef struct s1apCancelledCellinEAI_Item
{
 TknPres pres;
 SztEUTRAN_CGI eCGI;
 SztNumberOfBroadcasts numberOfBroadcasts;
 SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs iE_Extns;
} SztCancelledCellinEAI_Item;

typedef struct s1apCancelledCellinEAI
{
 TknU16 noComp;
 SztCancelledCellinEAI_Item *member;
}SztCancelledCellinEAI;

typedef struct s1ap_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls;
typedef struct s1apProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls extensionValue;
} SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs;

typedef struct s1apProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs *member;
}SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs;

typedef struct s1apEmergencyAreaID_Cancelled_Item
{
 TknPres pres;
 SztEmergencyAreaID emergencyAreaID;
 SztCancelledCellinEAI cancelledCellinEAI;
 SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs iE_Extns;
} SztEmergencyAreaID_Cancelled_Item;

typedef struct s1apEmergencyAreaID_Cancelled
{
 TknU16 noComp;
 SztEmergencyAreaID_Cancelled_Item *member;
}SztEmergencyAreaID_Cancelled;

typedef struct s1apBroadcastCancelledAreaLst
{
 TknU8 choice;
 union {
  SztCellID_Cancelled cellID_Cancelled;
  SztTAI_Cancelled tAI_Cancelled;
  SztEmergencyAreaID_Cancelled emergencyAreaID_Cancelled;
 } val;
} SztBroadcastCancelledAreaLst;

typedef struct s1ap_ExtnCellID_Broadcast_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCellID_Broadcast_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CellID_Broadcast_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCellID_Broadcast_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CellID_Broadcast_Item_ExtIEs;

typedef struct s1apProtExtnCont_CellID_Broadcast_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CellID_Broadcast_Item_ExtIEs *member;
}SztProtExtnCont_CellID_Broadcast_Item_ExtIEs;

typedef struct s1apCellID_Broadcast_Item
{
 TknPres pres;
 SztEUTRAN_CGI eCGI;
 SztProtExtnCont_CellID_Broadcast_Item_ExtIEs iE_Extns;
} SztCellID_Broadcast_Item;

typedef struct s1apCellID_Broadcast
{
 TknU16 noComp;
 SztCellID_Broadcast_Item *member;
}SztCellID_Broadcast;

typedef struct s1ap_ExtnCompletedCellinTAI_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CompletedCellinTAI_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CompletedCellinTAI_Item_ExtIEs;

typedef struct s1apProtExtnCont_CompletedCellinTAI_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *member;
}SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs;

typedef struct s1apCompletedCellinTAI_Item
{
 TknPres pres;
 SztEUTRAN_CGI eCGI;
 SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs iE_Extns;
} SztCompletedCellinTAI_Item;

typedef struct s1apCompletedCellinTAI
{
 TknU16 noComp;
 SztCompletedCellinTAI_Item *member;
}SztCompletedCellinTAI;

typedef struct s1ap_ExtnTAI_Broadcast_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTAI_Broadcast_Item_ExtIEsCls;
typedef struct s1apProtExtnField_TAI_Broadcast_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTAI_Broadcast_Item_ExtIEsCls extensionValue;
} SztProtExtnField_TAI_Broadcast_Item_ExtIEs;

typedef struct s1apProtExtnCont_TAI_Broadcast_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TAI_Broadcast_Item_ExtIEs *member;
}SztProtExtnCont_TAI_Broadcast_Item_ExtIEs;

typedef struct s1apTAI_Broadcast_Item
{
 TknPres pres;
 SztTAI tAI;
 SztCompletedCellinTAI completedCellinTAI;
 SztProtExtnCont_TAI_Broadcast_Item_ExtIEs iE_Extns;
} SztTAI_Broadcast_Item;

typedef struct s1apTAI_Broadcast
{
 TknU16 noComp;
 SztTAI_Broadcast_Item *member;
}SztTAI_Broadcast;

typedef struct s1ap_ExtnCompletedCellinEAI_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CompletedCellinEAI_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CompletedCellinEAI_Item_ExtIEs;

typedef struct s1apProtExtnCont_CompletedCellinEAI_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *member;
}SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs;

typedef struct s1apCompletedCellinEAI_Item
{
 TknPres pres;
 SztEUTRAN_CGI eCGI;
 SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs iE_Extns;
} SztCompletedCellinEAI_Item;

typedef struct s1apCompletedCellinEAI
{
 TknU16 noComp;
 SztCompletedCellinEAI_Item *member;
}SztCompletedCellinEAI;

typedef struct s1ap_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls;
typedef struct s1apProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls extensionValue;
} SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs;

typedef struct s1apProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *member;
}SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs;

typedef struct s1apEmergencyAreaID_Broadcast_Item
{
 TknPres pres;
 SztEmergencyAreaID emergencyAreaID;
 SztCompletedCellinEAI completedCellinEAI;
 SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs iE_Extns;
} SztEmergencyAreaID_Broadcast_Item;

typedef struct s1apEmergencyAreaID_Broadcast
{
 TknU16 noComp;
 SztEmergencyAreaID_Broadcast_Item *member;
}SztEmergencyAreaID_Broadcast;

typedef struct s1apBroadcastCompletedAreaLst
{
 TknU8 choice;
 union {
  SztCellID_Broadcast cellID_Broadcast;
  SztTAI_Broadcast tAI_Broadcast;
  SztEmergencyAreaID_Broadcast emergencyAreaID_Broadcast;
 } val;
} SztBroadcastCompletedAreaLst;


typedef enum enumSztCauseRadioNw
{
 SztCauseRadioNwunspecifiedEnum,
 SztCauseRadioNwtx2relocoverall_expiryEnum,
 SztCauseRadioNwsuccessful_handoverEnum,
 SztCauseRadioNwrelease_due_to_eutran_generated_reasonEnum,
 SztCauseRadioNwhandover_cancelledEnum,
 SztCauseRadioNwpartial_handoverEnum,
 SztCauseRadioNwho_failure_in_target_EPC_eNB_or_target_systemEnum,
 SztCauseRadioNwho_target_not_allowedEnum,
 SztCauseRadioNwtS1relocoverall_expiryEnum,
 SztCauseRadioNwtS1relocprep_expiryEnum,
 SztCauseRadioNwcell_not_availableEnum,
 SztCauseRadioNwunknown_targetIDEnum,
 SztCauseRadioNwno_radio_resources_available_in_target_cellEnum,
 SztCauseRadioNwunknown_mme_ue_s1ap_idEnum,
 SztCauseRadioNwunknown_enb_ue_s1ap_idEnum,
 SztCauseRadioNwunknown_pair_ue_s1ap_idEnum,
 SztCauseRadioNwhandover_desirable_for_radio_reasonEnum,
 SztCauseRadioNwtime_critical_handoverEnum,
 SztCauseRadioNwresource_optimisation_handoverEnum,
 SztCauseRadioNwreduce_load_in_serving_cellEnum,
 SztCauseRadioNwuser_inactivityEnum,
 SztCauseRadioNwradio_connection_with_ue_lostEnum,
 SztCauseRadioNwload_balancing_tau_requiredEnum,
 SztCauseRadioNwcs_fallback_triggeredEnum,
 SztCauseRadioNwue_not_available_for_ps_serviceEnum,
 SztCauseRadioNwradio_resources_not_availableEnum,
 SztCauseRadioNwfailure_in_radio_interface_procedureEnum,
 SztCauseRadioNwinvalid_qos_combinationEnum,
 SztCauseRadioNwinterrat_redirectionEnum,
 SztCauseRadioNwinteraction_with_other_procedureEnum,
 SztCauseRadioNwunknown_E_RAB_IDEnum,
 SztCauseRadioNwmultiple_E_RAB_ID_instancesEnum,
 SztCauseRadioNwencryption_and_or_integrity_protection_algorithms_not_supportedEnum,
 SztCauseRadioNws1_intra_system_handover_triggeredEnum,
 SztCauseRadioNws1_inter_system_handover_triggeredEnum,
 SztCauseRadioNwx2_handover_triggeredEnum,
 SztCauseRadioNwredirection_towards_1xRTTEnum,
 SztCauseRadioNwnot_supported_QCI_valueEnum,
 SztCauseRadioNwinvalid_CSG_IdEnum
} EnumSztCauseRadioNw;
typedef TknU32 SztCauseRadioNw;


typedef enum enumSztCauseTport
{
 SztCauseTporttransport_resource_unavailableEnum,
 SztCauseTportunspecifiedEnum
} EnumSztCauseTport;
typedef TknU32 SztCauseTport;


typedef enum enumSztCauseNas
{
 SztCauseNasnormal_releaseEnum,
 SztCauseNasauthentication_failureEnum,
 SztCauseNasdetachEnum,
 SztCauseNasunspecifiedEnum,
 SztCauseNascsg_subscription_expiryEnum
} EnumSztCauseNas;
typedef TknU32 SztCauseNas;


typedef enum enumSztCauseProt
{
 SztCauseProttransfer_syntax_errorEnum,
 SztCauseProtabstract_syntax_error_rejectEnum,
 SztCauseProtabstract_syntax_error_ignore_and_notifyEnum,
 SztCauseProtmessage_not_compatible_with_receiver_stateEnum,
 SztCauseProtsemantic_errorEnum,
 SztCauseProtabstract_syntax_error_falsely_constructed_messageEnum,
 SztCauseProtunspecifiedEnum
} EnumSztCauseProt;
typedef TknU32 SztCauseProt;


typedef enum enumSztCauseMisc
{
 SztCauseMisccontrol_processing_overloadEnum,
 SztCauseMiscnot_enough_user_plane_processing_resourcesEnum,
 SztCauseMischardware_failureEnum,
 SztCauseMiscom_interventionEnum,
 SztCauseMiscunspecifiedEnum,
 SztCauseMiscunknown_PLMNEnum
} EnumSztCauseMisc;
typedef TknU32 SztCauseMisc;

typedef struct s1apCause
{
 TknU8 choice;
 union {
  SztCauseRadioNw radioNw;
  SztCauseTport transport;
  SztCauseNas nas;
  SztCauseProt protocol;
  SztCauseMisc misc;
 } val;
} SztCause;


typedef enum enumSztCellAccessMode
{
 SztCellAccessModehybridEnum
} EnumSztCellAccessMode;
typedef TknU32 SztCellAccessMode;


typedef TknStrOSXL SztCdma2000PDU;

typedef enum enumSztCdma2000RATTyp
{
 SztCdma2000RATTyphRPDEnum,
 SztCdma2000RATTyponexRTTEnum
} EnumSztCdma2000RATTyp;
typedef TknU32 SztCdma2000RATTyp;


typedef TknStrOSXL SztCdma2000SectorID;

typedef enum enumSztCdma2000HOStatus
{
 SztCdma2000HOStatushOSuccessEnum,
 SztCdma2000HOStatushOFailEnum
} EnumSztCdma2000HOStatus;
typedef TknU32 SztCdma2000HOStatus;


typedef enum enumSztCdma2000HOReqdInd
{
 SztCdma2000HOReqdIndtrueEnum
} EnumSztCdma2000HOReqdInd;
typedef TknU32 SztCdma2000HOReqdInd;


typedef TknStrOSXL SztCdma2000OneXMEID;

typedef TknStrOSXL SztCdma2000OneXMSI;

typedef TknStrOSXL SztCdma2000OneXPilot;
typedef struct s1ap_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls;
typedef struct s1apProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls extensionValue;
} SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs;

typedef struct s1apProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *member;
}SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs;

typedef struct s1apCdma2000OneXSRVCCInfo
{
 TknPres pres;
 SztCdma2000OneXMEID cdma2000OneXMEID;
 SztCdma2000OneXMSI cdma2000OneXMSI;
 SztCdma2000OneXPilot cdma2000OneXPilot;
 SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs iE_Extns;
} SztCdma2000OneXSRVCCInfo;


typedef TknStrOSXL SztCdma2000OneXRAND;

typedef enum enumSztCell_Size
{
 SztCell_SizeverysmallEnum,
 SztCell_SizesmallEnum,
 SztCell_SizemediumEnum,
 SztCell_SizelargeEnum
} EnumSztCell_Size;
typedef TknU32 SztCell_Size;

typedef struct s1ap_ExtnCellTyp_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCellTyp_ExtIEsCls;
typedef struct s1apProtExtnField_CellTyp_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCellTyp_ExtIEsCls extensionValue;
} SztProtExtnField_CellTyp_ExtIEs;

typedef struct s1apProtExtnCont_CellTyp_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CellTyp_ExtIEs *member;
}SztProtExtnCont_CellTyp_ExtIEs;

typedef struct s1apCellTyp
{
 TknPres pres;
 SztCell_Size cell_Size;
 SztProtExtnCont_CellTyp_ExtIEs iE_Extns;
} SztCellTyp;


typedef TknStr4 SztLAC;

typedef TknStr4 SztCI;

typedef TknStr4 SztRAC;
typedef struct s1ap_ExtnCGI_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCGI_ExtIEsCls;
typedef struct s1apProtExtnField_CGI_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCGI_ExtIEsCls extensionValue;
} SztProtExtnField_CGI_ExtIEs;

typedef struct s1apProtExtnCont_CGI_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CGI_ExtIEs *member;
}SztProtExtnCont_CGI_ExtIEs;

typedef struct s1apCGI
{
 TknPres pres;
 SztPLMNidentity pLMNidentity;
 SztLAC lAC;
 SztCI cI;
 SztRAC rAC;
 SztProtExtnCont_CGI_ExtIEs iE_Extns;
} SztCGI;


typedef enum enumSztCNDomain
{
 SztCNDomainpsEnum,
 SztCNDomaincsEnum
} EnumSztCNDomain;
typedef TknU32 SztCNDomain;


typedef enum enumSztConcurrentWarningMsgIndicator
{
 SztConcurrentWarningMsgIndicatortrueEnum
} EnumSztConcurrentWarningMsgIndicator;
typedef TknU32 SztConcurrentWarningMsgIndicator;


typedef TknStrOSXL SztCorrelation_ID;

typedef enum enumSztCSFallbackIndicator
{
 SztCSFallbackIndicatorcs_fallback_requiredEnum,
 SztCSFallbackIndicatorcs_fallback_high_priorityEnum
} EnumSztCSFallbackIndicator;
typedef TknU32 SztCSFallbackIndicator;


typedef TknBStr32 SztCSG_Id;
typedef struct s1ap_ExtnCSG_IdLst_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCSG_IdLst_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CSG_IdLst_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCSG_IdLst_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CSG_IdLst_Item_ExtIEs;

typedef struct s1apProtExtnCont_CSG_IdLst_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CSG_IdLst_Item_ExtIEs *member;
}SztProtExtnCont_CSG_IdLst_Item_ExtIEs;

typedef struct s1apCSG_IdLst_Item
{
 TknPres pres;
 SztCSG_Id cSG_Id;
 SztProtExtnCont_CSG_IdLst_Item_ExtIEs iE_Extns;
} SztCSG_IdLst_Item;

typedef struct s1apCSG_IdLst
{
 TknU16 noComp;
 SztCSG_IdLst_Item *member;
}SztCSG_IdLst;


typedef enum enumSztCSGMembershipStatus
{
 SztCSGMembershipStatusmemberEnum,
 SztCSGMembershipStatusnot_memberEnum
} EnumSztCSGMembershipStatus;
typedef TknU32 SztCSGMembershipStatus;


typedef enum enumSztTypOfErr
{
 SztTypOfErrnot_understoodEnum,
 SztTypOfErrmissingEnum
} EnumSztTypOfErr;
typedef TknU32 SztTypOfErr;

typedef struct s1ap_ExtnCriticalityDiag_IE_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CriticalityDiag_IE_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs;

typedef struct s1apProtExtnCont_CriticalityDiag_IE_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *member;
}SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs;

typedef struct s1apCriticalityDiag_IE_Item
{
 TknPres pres;
 SztCriticality iECriticality;
 SztProtIE_ID iE_ID;
 SztTypOfErr typeOfErr;
 SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs iE_Extns;
} SztCriticalityDiag_IE_Item;

typedef struct s1apCriticalityDiag_IE_Lst
{
 TknU16 noComp;
 SztCriticalityDiag_IE_Item *member;
}SztCriticalityDiag_IE_Lst;

typedef struct s1ap_ExtnCriticalityDiag_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnCriticalityDiag_ExtIEsCls;
typedef struct s1apProtExtnField_CriticalityDiag_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnCriticalityDiag_ExtIEsCls extensionValue;
} SztProtExtnField_CriticalityDiag_ExtIEs;

typedef struct s1apProtExtnCont_CriticalityDiag_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_CriticalityDiag_ExtIEs *member;
}SztProtExtnCont_CriticalityDiag_ExtIEs;

typedef struct s1apCriticalityDiag
{
 TknPres pres;
 SztProcedureCode procedureCode;
 SztTrgMsg triggeringMsg;
 SztCriticality procedureCriticality;
 SztCriticalityDiag_IE_Lst iEsCriticalityDiag;
 SztProtExtnCont_CriticalityDiag_ExtIEs iE_Extns;
} SztCriticalityDiag;


typedef TknBStr32 SztDataCodingScheme;

typedef enum enumSztDL_Fwding
{
 SztDL_FwdingdL_Fwding_proposedEnum
} EnumSztDL_Fwding;
typedef TknU32 SztDL_Fwding;


typedef enum enumSztDirect_Fwding_Path_Avlblty
{
 SztDirect_Fwding_Path_AvlbltydirectPathAvailableEnum
} EnumSztDirect_Fwding_Path_Avlblty;
typedef TknU32 SztDirect_Fwding_Path_Avlblty;


typedef enum enumSztData_Fwding_Not_Possible
{
 SztData_Fwding_Not_Possibledata_Fwding_not_PossibleEnum
} EnumSztData_Fwding_Not_Possible;
typedef TknU32 SztData_Fwding_Not_Possible;

typedef struct s1apECGILst
{
 TknU16 noComp;
 SztEUTRAN_CGI *member;
}SztECGILst;

typedef struct s1apEmergencyAreaIDLst
{
 TknU16 noComp;
 SztEmergencyAreaID *member;
}SztEmergencyAreaIDLst;


typedef TknBStr32 SztENB_IDmacroENB_ID;

typedef TknBStr32 SztENB_IDhomeENB_ID;
typedef struct s1apENB_ID
{
 TknU8 choice;
 union {
  SztENB_IDmacroENB_ID macroENB_ID;
  SztENB_IDhomeENB_ID homeENB_ID;
 } val;
} SztENB_ID;

typedef struct s1ap_ExtnLAI_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnLAI_ExtIEsCls;
typedef struct s1apProtExtnField_LAI_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnLAI_ExtIEsCls extensionValue;
} SztProtExtnField_LAI_ExtIEs;

typedef struct s1apProtExtnCont_LAI_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_LAI_ExtIEs *member;
}SztProtExtnCont_LAI_ExtIEs;

typedef struct s1apLAI
{
 TknPres pres;
 SztPLMNidentity pLMNidentity;
 SztLAC lAC;
 SztProtExtnCont_LAI_ExtIEs iE_Extns;
} SztLAI;

typedef struct s1ap_ExtnGERAN_Cell_ID_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnGERAN_Cell_ID_ExtIEsCls;
typedef struct s1apProtExtnField_GERAN_Cell_ID_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnGERAN_Cell_ID_ExtIEsCls extensionValue;
} SztProtExtnField_GERAN_Cell_ID_ExtIEs;

typedef struct s1apProtExtnCont_GERAN_Cell_ID_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_GERAN_Cell_ID_ExtIEs *member;
}SztProtExtnCont_GERAN_Cell_ID_ExtIEs;

typedef struct s1apGERAN_Cell_ID
{
 TknPres pres;
 SztLAI lAI;
 SztRAC rAC;
 SztCI cI;
 SztProtExtnCont_GERAN_Cell_ID_ExtIEs iE_Extns;
} SztGERAN_Cell_ID;

typedef struct s1ap_ExtnGlobalENB_ID_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnGlobalENB_ID_ExtIEsCls;
typedef struct s1apProtExtnField_GlobalENB_ID_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnGlobalENB_ID_ExtIEsCls extensionValue;
} SztProtExtnField_GlobalENB_ID_ExtIEs;

typedef struct s1apProtExtnCont_GlobalENB_ID_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_GlobalENB_ID_ExtIEs *member;
}SztProtExtnCont_GlobalENB_ID_ExtIEs;

typedef struct s1apGlobal_ENB_ID
{
 TknPres pres;
 SztPLMNidentity pLMNidentity;
 SztENB_ID eNB_ID;
 SztProtExtnCont_GlobalENB_ID_ExtIEs iE_Extns;
} SztGlobal_ENB_ID;


typedef TknStr4 SztMME_Group_ID;

typedef TknStr4 SztMME_Code;
typedef struct s1ap_ExtnGUMMEI_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnGUMMEI_ExtIEsCls;
typedef struct s1apProtExtnField_GUMMEI_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnGUMMEI_ExtIEsCls extensionValue;
} SztProtExtnField_GUMMEI_ExtIEs;

typedef struct s1apProtExtnCont_GUMMEI_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_GUMMEI_ExtIEs *member;
}SztProtExtnCont_GUMMEI_ExtIEs;

typedef struct s1apGUMMEI
{
 TknPres pres;
 SztPLMNidentity pLMN_Identity;
 SztMME_Group_ID mME_Group_ID;
 SztMME_Code mME_Code;
 SztProtExtnCont_GUMMEI_ExtIEs iE_Extns;
} SztGUMMEI;

typedef struct s1apGUMMEILst
{
 TknU16 noComp;
 SztGUMMEI *member;
}SztGUMMEILst;

typedef struct s1ap_ExtnENB_StatusTfr_TprntCont_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls;
typedef struct s1apProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls extensionValue;
} SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs;

typedef struct s1apProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *member;
}SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs;

typedef struct s1apENB_StatusTfr_TprntCont
{
 TknPres pres;
 SztBrs_SubjToStatusTfrLst bearers_SubjToStatusTfrLst;
 SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs iE_Extns;
} SztENB_StatusTfr_TprntCont;


typedef TknU32 SztENB_UE_S1AP_ID;


typedef TknStrOSXL SztENBname;

typedef TknStrBSXL SztTportLyrAddr;
typedef struct s1apENBX2TLAs
{
 TknU16 noComp;
 SztTportLyrAddr *member;
}SztENBX2TLAs;


typedef TknBStr32 SztEncryptionAlgorithms;
typedef struct s1apEPLMNs
{
 TknU16 noComp;
 SztPLMNidentity *member;
}SztEPLMNs;


typedef enum enumSztEventTyp
{
 SztEventTypdirectEnum,
 SztEventTypchange_of_serve_cellEnum,
 SztEventTypstop_change_of_serve_cellEnum
} EnumSztEventTyp;
typedef TknU32 SztEventTyp;

typedef struct s1ap_ExtnE_RABInformLstItem_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABInformLstItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABInformLstItem_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABInformLstItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABInformLstItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABInformLstItem_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABInformLstItem_ExtIEs *member;
}SztProtExtnCont_E_RABInformLstItem_ExtIEs;

typedef struct s1apE_RABInformLstItem
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztDL_Fwding dL_Fwding;
 SztProtExtnCont_E_RABInformLstItem_ExtIEs iE_Extns;
} SztE_RABInformLstItem;

typedef struct s1ap_ValueE_RABInformLstIEsCls{
 union {
  SztE_RABInformLstItem sztE_RABInformLstItem;
 } u;
} Szt_ValueE_RABInformLstIEsCls;
typedef struct s1apProtIE_Field_E_RABInformLstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABInformLstIEsCls value;
} SztProtIE_Field_E_RABInformLstIEs;


typedef SztProtIE_Field_E_RABInformLstIEs SztProtIE_SingleCont_E_RABInformLstIEs;
typedef struct s1apE_RABInformLst
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABInformLstIEs *member;
}SztE_RABInformLst;

typedef struct s1ap_ExtnE_RABItem_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABItem_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABItem_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABItem_ExtIEs *member;
}SztProtExtnCont_E_RABItem_ExtIEs;

typedef struct s1apE_RABItem
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztCause cause;
 SztProtExtnCont_E_RABItem_ExtIEs iE_Extns;
} SztE_RABItem;

typedef struct s1ap_ValueE_RABItemIEsCls{
 union {
  SztE_RABItem sztE_RABItem;
 } u;
} Szt_ValueE_RABItemIEsCls;
typedef struct s1apProtIE_Field_E_RABItemIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABItemIEsCls value;
} SztProtIE_Field_E_RABItemIEs;


typedef SztProtIE_Field_E_RABItemIEs SztProtIE_SingleCont_E_RABItemIEs;
typedef struct s1apE_RABLst
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABItemIEs *member;
}SztE_RABLst;


typedef TknU32 SztQCI;

typedef struct s1ap_ExtnGBR_QosInform_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnGBR_QosInform_ExtIEsCls;
typedef struct s1apProtExtnField_GBR_QosInform_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnGBR_QosInform_ExtIEsCls extensionValue;
} SztProtExtnField_GBR_QosInform_ExtIEs;

typedef struct s1apProtExtnCont_GBR_QosInform_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_GBR_QosInform_ExtIEs *member;
}SztProtExtnCont_GBR_QosInform_ExtIEs;

typedef struct s1apGBR_QosInform
{
 TknPres pres;
 SztBitRate e_RAB_MaxBitrateDL;
 SztBitRate e_RAB_MaxBitrateUL;
 SztBitRate e_RAB_GuaranteedBitrateDL;
 SztBitRate e_RAB_GuaranteedBitrateUL;
 SztProtExtnCont_GBR_QosInform_ExtIEs iE_Extns;
} SztGBR_QosInform;

typedef struct s1ap_ExtnE_RABQoSParams_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABQoSParams_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABQoSParams_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABQoSParams_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABQoSParams_ExtIEs;

typedef struct s1apProtExtnCont_E_RABQoSParams_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABQoSParams_ExtIEs *member;
}SztProtExtnCont_E_RABQoSParams_ExtIEs;

typedef struct s1apE_RABLvlQoSParams
{
 TknPres pres;
 SztQCI qCI;
 SztAllocnAndRetentionPriority allocationRetentionPriority;
 SztGBR_QosInform gbrQosInform;
 SztProtExtnCont_E_RABQoSParams_ExtIEs iE_Extns;
} SztE_RABLvlQoSParams;


typedef TknU32 SztEUTRANRoundTripDelayEstimationInfo;


typedef TknU32 SztExtendedRNC_ID;


typedef TknU32 SztExtendedRepetitionPeriod;


typedef enum enumSztForbiddenInterRATs
{
 SztForbiddenInterRATsallEnum,
 SztForbiddenInterRATsgeranEnum,
 SztForbiddenInterRATsutranEnum,
 SztForbiddenInterRATscdma2000Enum,
 SztForbiddenInterRATsgeranandutranEnum,
 SztForbiddenInterRATscdma2000andutranEnum
} EnumSztForbiddenInterRATs;
typedef TknU32 SztForbiddenInterRATs;

typedef struct s1apForbiddenTACs
{
 TknU16 noComp;
 SztTAC *member;
}SztForbiddenTACs;

typedef struct s1ap_ExtnForbiddenTAs_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnForbiddenTAs_Item_ExtIEsCls;
typedef struct s1apProtExtnField_ForbiddenTAs_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnForbiddenTAs_Item_ExtIEsCls extensionValue;
} SztProtExtnField_ForbiddenTAs_Item_ExtIEs;

typedef struct s1apProtExtnCont_ForbiddenTAs_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_ForbiddenTAs_Item_ExtIEs *member;
}SztProtExtnCont_ForbiddenTAs_Item_ExtIEs;

typedef struct s1apForbiddenTAs_Item
{
 TknPres pres;
 SztPLMNidentity pLMN_Identity;
 SztForbiddenTACs forbiddenTACs;
 SztProtExtnCont_ForbiddenTAs_Item_ExtIEs iE_Extns;
} SztForbiddenTAs_Item;

typedef struct s1apForbiddenTAs
{
 TknU16 noComp;
 SztForbiddenTAs_Item *member;
}SztForbiddenTAs;

typedef struct s1apForbiddenLACs
{
 TknU16 noComp;
 SztLAC *member;
}SztForbiddenLACs;

typedef struct s1ap_ExtnForbiddenLAs_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnForbiddenLAs_Item_ExtIEsCls;
typedef struct s1apProtExtnField_ForbiddenLAs_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnForbiddenLAs_Item_ExtIEsCls extensionValue;
} SztProtExtnField_ForbiddenLAs_Item_ExtIEs;

typedef struct s1apProtExtnCont_ForbiddenLAs_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_ForbiddenLAs_Item_ExtIEs *member;
}SztProtExtnCont_ForbiddenLAs_Item_ExtIEs;

typedef struct s1apForbiddenLAs_Item
{
 TknPres pres;
 SztPLMNidentity pLMN_Identity;
 SztForbiddenLACs forbiddenLACs;
 SztProtExtnCont_ForbiddenLAs_Item_ExtIEs iE_Extns;
} SztForbiddenLAs_Item;

typedef struct s1apForbiddenLAs
{
 TknU16 noComp;
 SztForbiddenLAs_Item *member;
}SztForbiddenLAs;


typedef TknStrOSXL SztGTP_TEID;

typedef enum enumSztGUMMEITyp
{
 SztGUMMEITypnativeEnum,
 SztGUMMEITypmappedEnum
} EnumSztGUMMEITyp;
typedef TknU32 SztGUMMEITyp;


typedef enum enumSztGWCntxtRlsInd
{
 SztGWCntxtRlsIndtrueEnum
} EnumSztGWCntxtRlsInd;
typedef TknU32 SztGWCntxtRlsInd;

typedef struct s1ap_ExtnHovrRestrnLst_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnHovrRestrnLst_ExtIEsCls;
typedef struct s1apProtExtnField_HovrRestrnLst_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnHovrRestrnLst_ExtIEsCls extensionValue;
} SztProtExtnField_HovrRestrnLst_ExtIEs;

typedef struct s1apProtExtnCont_HovrRestrnLst_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_HovrRestrnLst_ExtIEs *member;
}SztProtExtnCont_HovrRestrnLst_ExtIEs;

typedef struct s1apHovrRestrnLst
{
 TknPres pres;
 SztPLMNidentity servingPLMN;
 SztEPLMNs equivalentPLMNs;
 SztForbiddenTAs forbiddenTAs;
 SztForbiddenLAs forbiddenLAs;
 SztForbiddenInterRATs forbiddenInterRATs;
 SztProtExtnCont_HovrRestrnLst_ExtIEs iE_Extns;
} SztHovrRestrnLst;


typedef enum enumSztHovrTyp
{
 SztHovrTypintralteEnum,
 SztHovrTypltetoutranEnum,
 SztHovrTypltetogeranEnum,
 SztHovrTyputrantolteEnum,
 SztHovrTypgerantolteEnum
} EnumSztHovrTyp;
typedef TknU32 SztHovrTyp;


typedef TknBStr32 SztMeasurementsToActivate;

typedef enum enumSztM1RprtngTrigger
{
 SztM1RprtngTriggerperiodicEnum,
 SztM1RprtngTriggera2eventtriggeredEnum,
 SztM1RprtngTriggera2eventtriggered_periodicEnum
} EnumSztM1RprtngTrigger;
typedef TknU32 SztM1RprtngTrigger;


typedef TknU32 SztThreshold_RSRP;


typedef TknU32 SztThreshold_RSRQ;

typedef struct s1apMeasurementThresholdA2
{
 TknU8 choice;
 union {
  SztThreshold_RSRP threshold_RSRP;
  SztThreshold_RSRQ threshold_RSRQ;
 } val;
} SztMeasurementThresholdA2;

typedef struct s1ap_ExtnM1ThresholdEventA2_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnM1ThresholdEventA2_ExtIEsCls;
typedef struct s1apProtExtnField_M1ThresholdEventA2_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnM1ThresholdEventA2_ExtIEsCls extensionValue;
} SztProtExtnField_M1ThresholdEventA2_ExtIEs;

typedef struct s1apProtExtnCont_M1ThresholdEventA2_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_M1ThresholdEventA2_ExtIEs *member;
}SztProtExtnCont_M1ThresholdEventA2_ExtIEs;

typedef struct s1apM1ThresholdEventA2
{
 TknPres pres;
 SztMeasurementThresholdA2 measurementThreshold;
 SztProtExtnCont_M1ThresholdEventA2_ExtIEs iE_Extns;
} SztM1ThresholdEventA2;


typedef enum enumSztReportIntervalMDT
{
 SztReportIntervalMDTms120Enum,
 SztReportIntervalMDTms240Enum,
 SztReportIntervalMDTms480Enum,
 SztReportIntervalMDTms640Enum,
 SztReportIntervalMDTms1024Enum,
 SztReportIntervalMDTms2048Enum,
 SztReportIntervalMDTms5120Enum,
 SztReportIntervalMDTms10240Enum,
 SztReportIntervalMDTmin1Enum,
 SztReportIntervalMDTmin6Enum,
 SztReportIntervalMDTmin12Enum,
 SztReportIntervalMDTmin30Enum,
 SztReportIntervalMDTmin60Enum
} EnumSztReportIntervalMDT;
typedef TknU32 SztReportIntervalMDT;


typedef enum enumSztReportAmountMDT
{
 SztReportAmountMDTr1Enum,
 SztReportAmountMDTr2Enum,
 SztReportAmountMDTr4Enum,
 SztReportAmountMDTr8Enum,
 SztReportAmountMDTr16Enum,
 SztReportAmountMDTr32Enum,
 SztReportAmountMDTr64Enum,
 SztReportAmountMDTrinfinityEnum
} EnumSztReportAmountMDT;
typedef TknU32 SztReportAmountMDT;

typedef struct s1ap_ExtnM1PeriodicRprtng_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnM1PeriodicRprtng_ExtIEsCls;
typedef struct s1apProtExtnField_M1PeriodicRprtng_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnM1PeriodicRprtng_ExtIEsCls extensionValue;
} SztProtExtnField_M1PeriodicRprtng_ExtIEs;

typedef struct s1apProtExtnCont_M1PeriodicRprtng_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_M1PeriodicRprtng_ExtIEs *member;
}SztProtExtnCont_M1PeriodicRprtng_ExtIEs;

typedef struct s1apM1PeriodicRprtng
{
 TknPres pres;
 SztReportIntervalMDT reportInterval;
 SztReportAmountMDT reportAmount;
 SztProtExtnCont_M1PeriodicRprtng_ExtIEs iE_Extns;
} SztM1PeriodicRprtng;


typedef enum enumSztM3period
{
 SztM3periodms100Enum,
 SztM3periodms1000Enum,
 SztM3periodms10000Enum
} EnumSztM3period;
typedef TknU32 SztM3period;

typedef struct s1ap_ExtnM3Config_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnM3Config_ExtIEsCls;
typedef struct s1apProtExtnField_M3Config_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnM3Config_ExtIEsCls extensionValue;
} SztProtExtnField_M3Config_ExtIEs;

typedef struct s1apProtExtnCont_M3Config_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_M3Config_ExtIEs *member;
}SztProtExtnCont_M3Config_ExtIEs;

typedef struct s1apM3Config
{
 TknPres pres;
 SztM3period m3period;
 SztProtExtnCont_M3Config_ExtIEs iE_Extns;
} SztM3Config;


typedef enum enumSztM4period
{
 SztM4periodms1024Enum,
 SztM4periodms2048Enum,
 SztM4periodms5120Enum,
 SztM4periodms10240Enum,
 SztM4periodmin1Enum
} EnumSztM4period;
typedef TknU32 SztM4period;


typedef enum enumSztLinks_to_log
{
 SztLinks_to_loguplinkEnum,
 SztLinks_to_logdownlinkEnum,
 SztLinks_to_logboth_uplink_and_downlinkEnum
} EnumSztLinks_to_log;
typedef TknU32 SztLinks_to_log;

typedef struct s1ap_ExtnM4Config_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnM4Config_ExtIEsCls;
typedef struct s1apProtExtnField_M4Config_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnM4Config_ExtIEsCls extensionValue;
} SztProtExtnField_M4Config_ExtIEs;

typedef struct s1apProtExtnCont_M4Config_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_M4Config_ExtIEs *member;
}SztProtExtnCont_M4Config_ExtIEs;

typedef struct s1apM4Config
{
 TknPres pres;
 SztM4period m4period;
 SztLinks_to_log m4_links_to_log;
 SztProtExtnCont_M4Config_ExtIEs iE_Extns;
} SztM4Config;


typedef enum enumSztM5period
{
 SztM5periodms1024Enum,
 SztM5periodms2048Enum,
 SztM5periodms5120Enum,
 SztM5periodms10240Enum,
 SztM5periodmin1Enum
} EnumSztM5period;
typedef TknU32 SztM5period;

typedef struct s1ap_ExtnM5Config_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnM5Config_ExtIEsCls;
typedef struct s1apProtExtnField_M5Config_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnM5Config_ExtIEsCls extensionValue;
} SztProtExtnField_M5Config_ExtIEs;

typedef struct s1apProtExtnCont_M5Config_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_M5Config_ExtIEs *member;
}SztProtExtnCont_M5Config_ExtIEs;

typedef struct s1apM5Config
{
 TknPres pres;
 SztM5period m5period;
 SztLinks_to_log m5_links_to_log;
 SztProtExtnCont_M5Config_ExtIEs iE_Extns;
} SztM5Config;


typedef TknBStr32 SztMDT_Loc_Info;
typedef struct s1ap_ExtnImmediateMDT_ExtIEsCls{
 union {
  SztM3Config sztM3Config;
  SztM4Config sztM4Config;
  SztM5Config sztM5Config;
  SztMDT_Loc_Info sztMDT_Loc_Info;
 } u;
} Szt_ExtnImmediateMDT_ExtIEsCls;
typedef struct s1apProtExtnField_ImmediateMDT_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnImmediateMDT_ExtIEsCls extensionValue;
} SztProtExtnField_ImmediateMDT_ExtIEs;

typedef struct s1apProtExtnCont_ImmediateMDT_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_ImmediateMDT_ExtIEs *member;
}SztProtExtnCont_ImmediateMDT_ExtIEs;

typedef struct s1apImmediateMDT
{
 TknPres pres;
 SztMeasurementsToActivate measurementsToActivate;
 SztM1RprtngTrigger m1reportingTrigger;
 SztM1ThresholdEventA2 m1thresholdeventA2;
 SztM1PeriodicRprtng m1periodicRprtng;
 SztProtExtnCont_ImmediateMDT_ExtIEs iE_Extns;
} SztImmediateMDT;


typedef TknStrOSXL SztIMSI;

typedef TknBStr32 SztIntegrityProtectionAlgorithms;

typedef TknBStr32 SztIntfsToTrace;

typedef TknU32 SztTime_UE_StayedInCell;


typedef TknU32 SztTime_UE_StayedInCell_EnhancedGranularity;

typedef struct s1ap_ExtnLastVisitedEUTRANCellInform_ExtIEsCls{
 union {
  SztTime_UE_StayedInCell_EnhancedGranularity sztTime_UE_StayedInCell_EnhancedGranularity;
  SztCause sztCause;
 } u;
} Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls;
typedef struct s1apProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls extensionValue;
} SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs;

typedef struct s1apProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *member;
}SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs;

typedef struct s1apLastVisitedEUTRANCellInform
{
 TknPres pres;
 SztEUTRAN_CGI global_Cell_ID;
 SztCellTyp cellTyp;
 SztTime_UE_StayedInCell time_UE_StayedInCell;
 SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs iE_Extns;
} SztLastVisitedEUTRANCellInform;


typedef TknStrOSXL SztLastVisitedUTRANCellInform;
typedef struct s1apLastVisitedGERANCellInform
{
 TknU8 choice;
 union {
  TknU8 unused;
 } val;
} SztLastVisitedGERANCellInform;

typedef struct s1apLastVisitedCell_Item
{
 TknU8 choice;
 union {
  SztLastVisitedEUTRANCellInform e_UTRAN_Cell;
  SztLastVisitedUTRANCellInform uTRAN_Cell;
  SztLastVisitedGERANCellInform gERAN_Cell;
 } val;
} SztLastVisitedCell_Item;


typedef TknStrOSXL SztL3_Inform;

typedef TknStrOSXL SztLPPa_PDU;

typedef enum enumSztLoggingInterval
{
 SztLoggingIntervalms128Enum,
 SztLoggingIntervalms256Enum,
 SztLoggingIntervalms512Enum,
 SztLoggingIntervalms1024Enum,
 SztLoggingIntervalms2048Enum,
 SztLoggingIntervalms3072Enum,
 SztLoggingIntervalms4096Enum,
 SztLoggingIntervalms6144Enum
} EnumSztLoggingInterval;
typedef TknU32 SztLoggingInterval;


typedef enum enumSztLoggingDuration
{
 SztLoggingDurationm10Enum,
 SztLoggingDurationm20Enum,
 SztLoggingDurationm40Enum,
 SztLoggingDurationm60Enum,
 SztLoggingDurationm90Enum,
 SztLoggingDurationm120Enum
} EnumSztLoggingDuration;
typedef TknU32 SztLoggingDuration;

typedef struct s1ap_ExtnLoggedMDT_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnLoggedMDT_ExtIEsCls;
typedef struct s1apProtExtnField_LoggedMDT_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnLoggedMDT_ExtIEsCls extensionValue;
} SztProtExtnField_LoggedMDT_ExtIEs;

typedef struct s1apProtExtnCont_LoggedMDT_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_LoggedMDT_ExtIEs *member;
}SztProtExtnCont_LoggedMDT_ExtIEs;

typedef struct s1apLoggedMDT
{
 TknPres pres;
 SztLoggingInterval loggingInterval;
 SztLoggingDuration loggingDuration;
 SztProtExtnCont_LoggedMDT_ExtIEs iE_Extns;
} SztLoggedMDT;


typedef enum enumSztMDT_Actvn
{
 SztMDT_Actvnimmediate_MDT_onlyEnum,
 SztMDT_Actvnimmediate_MDT_and_TraceEnum,
 SztMDT_Actvnlogged_MDT_onlyEnum
} EnumSztMDT_Actvn;
typedef TknU32 SztMDT_Actvn;

typedef struct s1apMDTMode
{
 TknU8 choice;
 union {
  SztImmediateMDT immediateMDT;
  SztLoggedMDT loggedMDT;
 } val;
} SztMDTMode;

typedef struct s1apMDTPLMNLst
{
 TknU16 noComp;
 SztPLMNidentity *member;
}SztMDTPLMNLst;

typedef struct s1ap_ExtnMDT_Config_ExtIEsCls{
 union {
  SztMDTPLMNLst sztMDTPLMNLst;
 } u;
} Szt_ExtnMDT_Config_ExtIEsCls;
typedef struct s1apProtExtnField_MDT_Config_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnMDT_Config_ExtIEsCls extensionValue;
} SztProtExtnField_MDT_Config_ExtIEs;

typedef struct s1apProtExtnCont_MDT_Config_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_MDT_Config_ExtIEs *member;
}SztProtExtnCont_MDT_Config_ExtIEs;

typedef struct s1apMDT_Config
{
 TknPres pres;
 SztMDT_Actvn mdt_Actvn;
 SztAreaScopeOfMDT areaScopeOfMDT;
 SztMDTMode mDTMode;
 SztProtExtnCont_MDT_Config_ExtIEs iE_Extns;
} SztMDT_Config;


typedef enum enumSztManagementBasedMDTAllowed
{
 SztManagementBasedMDTAllowedallowedEnum
} EnumSztManagementBasedMDTAllowed;
typedef TknU32 SztManagementBasedMDTAllowed;


typedef enum enumSztPrivacyIndicator
{
 SztPrivacyIndicatorimmediate_MDTEnum,
 SztPrivacyIndicatorlogged_MDTEnum
} EnumSztPrivacyIndicator;
typedef TknU32 SztPrivacyIndicator;


typedef TknBStr32 SztMsgIdentifier;

typedef TknBStr32 SztMobilityInform;

typedef TknStrOSXL SztMMEname;

typedef enum enumSztMMERelaySupportIndicator
{
 SztMMERelaySupportIndicatortrueEnum
} EnumSztMMERelaySupportIndicator;
typedef TknU32 SztMMERelaySupportIndicator;


typedef TknU32 SztMME_UE_S1AP_ID;


typedef TknStrOSXL SztM_TMSI;

typedef TknStrOSXL SztMSClassmark2;

typedef TknStrOSXL SztMSClassmark3;

typedef TknStrOSXL SztNAS_PDU;

typedef TknStrOSXL SztNASSecurParamsfromE_UTRAN;

typedef TknStrOSXL SztNASSecurParamstoE_UTRAN;

typedef TknU32 SztNumberofBroadcastRqst;


typedef TknStrOSXL SztOldBSS_ToNewBSS_Inform;

typedef enum enumSztOverloadAction
{
 SztOverloadActionreject_non_emergency_mo_dtEnum,
 SztOverloadActionreject_rrc_cr_signallingEnum,
 SztOverloadActionpermit_emergency_sessions_and_mobile_terminated_services_onlyEnum,
 SztOverloadActionpermit_high_priority_sessions_and_mobile_terminated_services_onlyEnum,
 SztOverloadActionreject_delay_tolerant_accessEnum
} EnumSztOverloadAction;
typedef TknU32 SztOverloadAction;

typedef struct s1apOverloadResp
{
 TknU8 choice;
 union {
  SztOverloadAction overloadAction;
 } val;
} SztOverloadResp;


typedef enum enumSztPagDRX
{
 SztPagDRXv32Enum,
 SztPagDRXv64Enum,
 SztPagDRXv128Enum,
 SztPagDRXv256Enum
} EnumSztPagDRX;
typedef TknU32 SztPagDRX;


typedef enum enumSztPagPriority
{
 SztPagPrioritypriolevel1Enum,
 SztPagPrioritypriolevel2Enum,
 SztPagPrioritypriolevel3Enum,
 SztPagPrioritypriolevel4Enum,
 SztPagPrioritypriolevel5Enum,
 SztPagPrioritypriolevel6Enum,
 SztPagPrioritypriolevel7Enum,
 SztPagPrioritypriolevel8Enum
} EnumSztPagPriority;
typedef TknU32 SztPagPriority;


typedef TknStr4 SztPort_Number;

typedef enum enumSztPS_ServiceNotAvailable
{
 SztPS_ServiceNotAvailableps_service_not_availableEnum
} EnumSztPS_ServiceNotAvailable;
typedef TknU32 SztPS_ServiceNotAvailable;


typedef TknU32 SztRelativeMMECapacity;


typedef enum enumSztRelayNode_Indicator
{
 SztRelayNode_IndicatortrueEnum
} EnumSztRelayNode_Indicator;
typedef TknU32 SztRelayNode_Indicator;


typedef enum enumSztReportArea
{
 SztReportAreaecgiEnum
} EnumSztReportArea;
typedef TknU32 SztReportArea;

typedef struct s1ap_ExtnRqstTyp_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnRqstTyp_ExtIEsCls;
typedef struct s1apProtExtnField_RqstTyp_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnRqstTyp_ExtIEsCls extensionValue;
} SztProtExtnField_RqstTyp_ExtIEs;

typedef struct s1apProtExtnCont_RqstTyp_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_RqstTyp_ExtIEs *member;
}SztProtExtnCont_RqstTyp_ExtIEs;

typedef struct s1apRqstTyp
{
 TknPres pres;
 SztEventTyp eventTyp;
 SztReportArea reportArea;
 SztProtExtnCont_RqstTyp_ExtIEs iE_Extns;
} SztRqstTyp;


typedef TknStrOSXL SztRIMInform;

typedef TknU32 SztRNC_ID;

typedef struct s1ap_ExtnTgetRNC_ID_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTgetRNC_ID_ExtIEsCls;
typedef struct s1apProtExtnField_TgetRNC_ID_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTgetRNC_ID_ExtIEsCls extensionValue;
} SztProtExtnField_TgetRNC_ID_ExtIEs;

typedef struct s1apProtExtnCont_TgetRNC_ID_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TgetRNC_ID_ExtIEs *member;
}SztProtExtnCont_TgetRNC_ID_ExtIEs;

typedef struct s1apTgetRNC_ID
{
 TknPres pres;
 SztLAI lAI;
 SztRAC rAC;
 SztRNC_ID rNC_ID;
 SztExtendedRNC_ID extendedRNC_ID;
 SztProtExtnCont_TgetRNC_ID_ExtIEs iE_Extns;
} SztTgetRNC_ID;

typedef struct s1apRIMRoutingAddr
{
 TknU8 choice;
 union {
  SztGERAN_Cell_ID gERAN_Cell_ID;
  SztTgetRNC_ID targetRNC_ID;
 } val;
} SztRIMRoutingAddr;

typedef struct s1ap_ExtnRIMTfr_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnRIMTfr_ExtIEsCls;
typedef struct s1apProtExtnField_RIMTfr_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnRIMTfr_ExtIEsCls extensionValue;
} SztProtExtnField_RIMTfr_ExtIEs;

typedef struct s1apProtExtnCont_RIMTfr_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_RIMTfr_ExtIEs *member;
}SztProtExtnCont_RIMTfr_ExtIEs;

typedef struct s1apRIMTfr
{
 TknPres pres;
 SztRIMInform rIMInform;
 SztRIMRoutingAddr rIMRoutingAddr;
 SztProtExtnCont_RIMTfr_ExtIEs iE_Extns;
} SztRIMTfr;


typedef TknU32 SztRepetitionPeriod;


typedef TknStrOSXL SztRRC_Cont;

typedef enum enumSztRRC_Establishment_Cause
{
 SztRRC_Establishment_CauseemergencyEnum,
 SztRRC_Establishment_CausehighPriorityAccessEnum,
 SztRRC_Establishment_Causemt_AccessEnum,
 SztRRC_Establishment_Causemo_SignallingEnum,
 SztRRC_Establishment_Causemo_DataEnum,
 SztRRC_Establishment_Causedelay_TolerantAccessEnum
} EnumSztRRC_Establishment_Cause;
typedef TknU32 SztRRC_Establishment_Cause;


typedef TknU32 SztRouting_ID;


typedef TknStrBSXL SztSecurKey;

typedef TknU32 SztSecurCntxtnextHopChainingCount;

typedef struct s1ap_ExtnSecurCntxt_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnSecurCntxt_ExtIEsCls;
typedef struct s1apProtExtnField_SecurCntxt_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnSecurCntxt_ExtIEsCls extensionValue;
} SztProtExtnField_SecurCntxt_ExtIEs;

typedef struct s1apProtExtnCont_SecurCntxt_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_SecurCntxt_ExtIEs *member;
}SztProtExtnCont_SecurCntxt_ExtIEs;

typedef struct s1apSecurCntxt
{
 TknPres pres;
 SztSecurCntxtnextHopChainingCount nextHopChainingCount;
 SztSecurKey nextHopParameter;
 SztProtExtnCont_SecurCntxt_ExtIEs iE_Extns;
} SztSecurCntxt;


typedef TknBStr32 SztSerialNumber;

typedef enum enumSztSONInformRqst
{
 SztSONInformRqstx2TNL_Config_InfoEnum,
 SztSONInformRqsttime_Synchronization_InfoEnum
} EnumSztSONInformRqst;
typedef TknU32 SztSONInformRqst;

typedef struct s1apENBX2GTPTLAs
{
 TknU16 noComp;
 SztTportLyrAddr *member;
}SztENBX2GTPTLAs;

typedef struct s1ap_ExtnENBX2ExtTLA_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnENBX2ExtTLA_ExtIEsCls;
typedef struct s1apProtExtnField_ENBX2ExtTLA_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnENBX2ExtTLA_ExtIEsCls extensionValue;
} SztProtExtnField_ENBX2ExtTLA_ExtIEs;

typedef struct s1apProtExtnCont_ENBX2ExtTLA_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_ENBX2ExtTLA_ExtIEs *member;
}SztProtExtnCont_ENBX2ExtTLA_ExtIEs;

typedef struct s1apENBX2ExtTLA
{
 TknPres pres;
 SztTportLyrAddr iPsecTLA;
 SztENBX2GTPTLAs gTPTLAa;
 SztProtExtnCont_ENBX2ExtTLA_ExtIEs iE_Extns;
} SztENBX2ExtTLA;

typedef struct s1apENBX2ExtTLAs
{
 TknU16 noComp;
 SztENBX2ExtTLA *member;
}SztENBX2ExtTLAs;

typedef struct s1ap_ExtnX2TNLConfigInfo_ExtIEsCls{
 union {
  SztENBX2ExtTLAs sztENBX2ExtTLAs;
 } u;
} Szt_ExtnX2TNLConfigInfo_ExtIEsCls;
typedef struct s1apProtExtnField_X2TNLConfigInfo_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnX2TNLConfigInfo_ExtIEsCls extensionValue;
} SztProtExtnField_X2TNLConfigInfo_ExtIEs;

typedef struct s1apProtExtnCont_X2TNLConfigInfo_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_X2TNLConfigInfo_ExtIEs *member;
}SztProtExtnCont_X2TNLConfigInfo_ExtIEs;

typedef struct s1apX2TNLConfigInfo
{
 TknPres pres;
 SztENBX2TLAs eNBX2TportLyrAddres;
 SztProtExtnCont_X2TNLConfigInfo_ExtIEs iE_Extns;
} SztX2TNLConfigInfo;


typedef TknU32 SztStratumLvl;


typedef enum enumSztSynchronizationStatus
{
 SztSynchronizationStatussynchronousEnum,
 SztSynchronizationStatusasynchronousEnum
} EnumSztSynchronizationStatus;
typedef TknU32 SztSynchronizationStatus;

typedef struct s1ap_ExtnTimeSynchronizationInfo_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTimeSynchronizationInfo_ExtIEsCls;
typedef struct s1apProtExtnField_TimeSynchronizationInfo_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTimeSynchronizationInfo_ExtIEsCls extensionValue;
} SztProtExtnField_TimeSynchronizationInfo_ExtIEs;

typedef struct s1apProtExtnCont_TimeSynchronizationInfo_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TimeSynchronizationInfo_ExtIEs *member;
}SztProtExtnCont_TimeSynchronizationInfo_ExtIEs;

typedef struct s1apTimeSynchronizationInfo
{
 TknPres pres;
 SztStratumLvl stratumLvl;
 SztSynchronizationStatus synchronizationStatus;
 SztProtExtnCont_TimeSynchronizationInfo_ExtIEs iE_Extns;
} SztTimeSynchronizationInfo;

typedef struct s1ap_ExtnSONInformReply_ExtIEsCls{
 union {
  SztTimeSynchronizationInfo sztTimeSynchronizationInfo;
 } u;
} Szt_ExtnSONInformReply_ExtIEsCls;
typedef struct s1apProtExtnField_SONInformReply_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnSONInformReply_ExtIEsCls extensionValue;
} SztProtExtnField_SONInformReply_ExtIEs;

typedef struct s1apProtExtnCont_SONInformReply_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_SONInformReply_ExtIEs *member;
}SztProtExtnCont_SONInformReply_ExtIEs;

typedef struct s1apSONInformReply
{
 TknPres pres;
 SztX2TNLConfigInfo x2TNLConfigInfo;
 SztProtExtnCont_SONInformReply_ExtIEs iE_Extns;
} SztSONInformReply;

typedef struct s1apSONInform
{
 TknU8 choice;
 union {
  SztSONInformRqst sONInformRqst;
  SztSONInformReply sONInformReply;
 } val;
} SztSONInform;

typedef struct s1ap_ExtnTgeteNB_ID_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTgeteNB_ID_ExtIEsCls;
typedef struct s1apProtExtnField_TgeteNB_ID_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTgeteNB_ID_ExtIEsCls extensionValue;
} SztProtExtnField_TgeteNB_ID_ExtIEs;

typedef struct s1apProtExtnCont_TgeteNB_ID_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TgeteNB_ID_ExtIEs *member;
}SztProtExtnCont_TgeteNB_ID_ExtIEs;

typedef struct s1apTgeteNB_ID
{
 TknPres pres;
 SztGlobal_ENB_ID global_ENB_ID;
 SztTAI selected_TAI;
 SztProtExtnCont_TgeteNB_ID_ExtIEs iE_Extns;
} SztTgeteNB_ID;

typedef struct s1ap_ExtnSrceNB_ID_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnSrceNB_ID_ExtIEsCls;
typedef struct s1apProtExtnField_SrceNB_ID_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnSrceNB_ID_ExtIEsCls extensionValue;
} SztProtExtnField_SrceNB_ID_ExtIEs;

typedef struct s1apProtExtnCont_SrceNB_ID_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_SrceNB_ID_ExtIEs *member;
}SztProtExtnCont_SrceNB_ID_ExtIEs;

typedef struct s1apSrceNB_ID
{
 TknPres pres;
 SztGlobal_ENB_ID global_ENB_ID;
 SztTAI selected_TAI;
 SztProtExtnCont_SrceNB_ID_ExtIEs iE_Extns;
} SztSrceNB_ID;

typedef struct s1ap_ExtnSONConfigTfr_ExtIEsCls{
 union {
  SztX2TNLConfigInfo sztX2TNLConfigInfo;
 } u;
} Szt_ExtnSONConfigTfr_ExtIEsCls;
typedef struct s1apProtExtnField_SONConfigTfr_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnSONConfigTfr_ExtIEsCls extensionValue;
} SztProtExtnField_SONConfigTfr_ExtIEs;

typedef struct s1apProtExtnCont_SONConfigTfr_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_SONConfigTfr_ExtIEs *member;
}SztProtExtnCont_SONConfigTfr_ExtIEs;

typedef struct s1apSONConfigTfr
{
 TknPres pres;
 SztTgeteNB_ID targeteNB_ID;
 SztSrceNB_ID sourceeNB_ID;
 SztSONInform sONInform;
 SztProtExtnCont_SONConfigTfr_ExtIEs iE_Extns;
} SztSONConfigTfr;


typedef TknStrOSXL SztSrc_ToTget_TprntCont;

typedef TknStrOSXL SztSrcBSS_ToTgetBSS_TprntCont;

typedef enum enumSztSRVCCOperationPossible
{
 SztSRVCCOperationPossiblepossibleEnum
} EnumSztSRVCCOperationPossible;
typedef TknU32 SztSRVCCOperationPossible;


typedef enum enumSztSRVCCHOInd
{
 SztSRVCCHOIndpSandCSEnum,
 SztSRVCCHOIndcSonlyEnum
} EnumSztSRVCCHOInd;
typedef TknU32 SztSRVCCHOInd;


typedef TknU32 SztSubscriberProfileIDforRFP;

typedef struct s1apUE_HistoryInform
{
 TknU16 noComp;
 SztLastVisitedCell_Item *member;
}SztUE_HistoryInform;

typedef struct s1ap_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls{
 union {
  SztMobilityInform sztMobilityInform;
 } u;
} Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls;
typedef struct s1apProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls extensionValue;
} SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs;

typedef struct s1apProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *member;
}SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs;

typedef struct s1apSrceNB_ToTgeteNB_TprntCont
{
 TknPres pres;
 SztRRC_Cont rRC_Cont;
 SztE_RABInformLst e_RABInformLst;
 SztEUTRAN_CGI targetCell_ID;
 SztSubscriberProfileIDforRFP subscriberProfileIDforRFP;
 SztUE_HistoryInform uE_HistoryInform;
 SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs iE_Extns;
} SztSrceNB_ToTgeteNB_TprntCont;


typedef TknStrOSXL SztSrcRNC_ToTgetRNC_TprntCont;
typedef struct s1apSrvdPLMNs
{
 TknU16 noComp;
 SztPLMNidentity *member;
}SztSrvdPLMNs;

typedef struct s1apSrvdGroupIDs
{
 TknU16 noComp;
 SztMME_Group_ID *member;
}SztSrvdGroupIDs;

typedef struct s1apSrvdMMECs
{
 TknU16 noComp;
 SztMME_Code *member;
}SztSrvdMMECs;

typedef struct s1ap_ExtnSrvdGUMMEIsItem_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls;
typedef struct s1apProtExtnField_SrvdGUMMEIsItem_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls extensionValue;
} SztProtExtnField_SrvdGUMMEIsItem_ExtIEs;

typedef struct s1apProtExtnCont_SrvdGUMMEIsItem_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *member;
}SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs;

typedef struct s1apSrvdGUMMEIsItem
{
 TknPres pres;
 SztSrvdPLMNs servedPLMNs;
 SztSrvdGroupIDs servedGroupIDs;
 SztSrvdMMECs servedMMECs;
 SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs iE_Extns;
} SztSrvdGUMMEIsItem;

typedef struct s1apSrvdGUMMEIs
{
 TknU16 noComp;
 SztSrvdGUMMEIsItem *member;
}SztSrvdGUMMEIs;

typedef struct s1ap_ExtnSuppTAs_Item_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnSuppTAs_Item_ExtIEsCls;
typedef struct s1apProtExtnField_SuppTAs_Item_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnSuppTAs_Item_ExtIEsCls extensionValue;
} SztProtExtnField_SuppTAs_Item_ExtIEs;

typedef struct s1apProtExtnCont_SuppTAs_Item_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_SuppTAs_Item_ExtIEs *member;
}SztProtExtnCont_SuppTAs_Item_ExtIEs;

typedef struct s1apSuppTAs_Item
{
 TknPres pres;
 SztTAC tAC;
 SztBPLMNs broadcastPLMNs;
 SztProtExtnCont_SuppTAs_Item_ExtIEs iE_Extns;
} SztSuppTAs_Item;

typedef struct s1apSuppTAs
{
 TknU16 noComp;
 SztSuppTAs_Item *member;
}SztSuppTAs;

typedef struct s1ap_ExtnS_TMSI_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnS_TMSI_ExtIEsCls;
typedef struct s1apProtExtnField_S_TMSI_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnS_TMSI_ExtIEsCls extensionValue;
} SztProtExtnField_S_TMSI_ExtIEs;

typedef struct s1apProtExtnCont_S_TMSI_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_S_TMSI_ExtIEs *member;
}SztProtExtnCont_S_TMSI_ExtIEs;

typedef struct s1apS_TMSI
{
 TknPres pres;
 SztMME_Code mMEC;
 SztM_TMSI m_TMSI;
 SztProtExtnCont_S_TMSI_ExtIEs iE_Extns;
} SztS_TMSI;

typedef struct s1apTAILstforWarning
{
 TknU16 noComp;
 SztTAI *member;
}SztTAILstforWarning;

typedef struct s1apTgetID
{
 TknU8 choice;
 union {
  SztTgeteNB_ID targeteNB_ID;
  SztTgetRNC_ID targetRNC_ID;
  SztCGI cGI;
 } val;
} SztTgetID;

typedef struct s1ap_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls;
typedef struct s1apProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls extensionValue;
} SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs;

typedef struct s1apProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *member;
}SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs;

typedef struct s1apTgeteNB_ToSrceNB_TprntCont
{
 TknPres pres;
 SztRRC_Cont rRC_Cont;
 SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs iE_Extns;
} SztTgeteNB_ToSrceNB_TprntCont;


typedef TknStrOSXL SztTget_ToSrc_TprntCont;

typedef TknStrOSXL SztTgetRNC_ToSrcRNC_TprntCont;

typedef TknStrOSXL SztTgetBSS_ToSrcBSS_TprntCont;

typedef enum enumSztTimeToWait
{
 SztTimeToWaitv1sEnum,
 SztTimeToWaitv2sEnum,
 SztTimeToWaitv5sEnum,
 SztTimeToWaitv10sEnum,
 SztTimeToWaitv20sEnum,
 SztTimeToWaitv60sEnum
} EnumSztTimeToWait;
typedef TknU32 SztTimeToWait;


typedef TknStrOSXL SztE_UTRAN_Trace_ID;

typedef enum enumSztTraceDepth
{
 SztTraceDepthminimumEnum,
 SztTraceDepthmediumEnum,
 SztTraceDepthmaximumEnum,
 SztTraceDepthminimumWithoutVendorSpecificExtnEnum,
 SztTraceDepthmediumWithoutVendorSpecificExtnEnum,
 SztTraceDepthmaximumWithoutVendorSpecificExtnEnum
} EnumSztTraceDepth;
typedef TknU32 SztTraceDepth;

typedef struct s1ap_ExtnTraceActvn_ExtIEsCls{
 union {
  SztMDT_Config sztMDT_Config;
 } u;
} Szt_ExtnTraceActvn_ExtIEsCls;
typedef struct s1apProtExtnField_TraceActvn_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTraceActvn_ExtIEsCls extensionValue;
} SztProtExtnField_TraceActvn_ExtIEs;

typedef struct s1apProtExtnCont_TraceActvn_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TraceActvn_ExtIEs *member;
}SztProtExtnCont_TraceActvn_ExtIEs;

typedef struct s1apTraceActvn
{
 TknPres pres;
 SztE_UTRAN_Trace_ID e_UTRAN_Trace_ID;
 SztIntfsToTrace interfacesToTrace;
 SztTraceDepth traceDepth;
 SztTportLyrAddr traceCollectionEntityIPAddr;
 SztProtExtnCont_TraceActvn_ExtIEs iE_Extns;
} SztTraceActvn;


typedef TknU32 SztTrafficLoadReductionInd;

typedef struct s1ap_ExtnTunnel_Inform_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTunnel_Inform_ExtIEsCls;
typedef struct s1apProtExtnField_Tunnel_Inform_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTunnel_Inform_ExtIEsCls extensionValue;
} SztProtExtnField_Tunnel_Inform_ExtIEs;

typedef struct s1apProtExtnCont_Tunnel_Inform_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_Tunnel_Inform_ExtIEs *member;
}SztProtExtnCont_Tunnel_Inform_ExtIEs;

typedef struct s1apTunnelInform
{
 TknPres pres;
 SztTportLyrAddr transportLyrAddr;
 SztPort_Number uDP_Port_Number;
 SztProtExtnCont_Tunnel_Inform_ExtIEs iE_Extns;
} SztTunnelInform;

typedef struct s1ap_ExtnUEAgg_MaxBitrates_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls;
typedef struct s1apProtExtnField_UEAgg_MaxBitrates_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls extensionValue;
} SztProtExtnField_UEAgg_MaxBitrates_ExtIEs;

typedef struct s1apProtExtnCont_UEAgg_MaxBitrates_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *member;
}SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs;

typedef struct s1apUEAggMaxBitrate
{
 TknPres pres;
 SztBitRate uEaggregateMaxBitRateDL;
 SztBitRate uEaggregateMaxBitRateUL;
 SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs iE_Extns;
} SztUEAggMaxBitrate;

typedef struct s1ap_ExtnUE_S1AP_ID_pair_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls;
typedef struct s1apProtExtnField_UE_S1AP_ID_pair_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls extensionValue;
} SztProtExtnField_UE_S1AP_ID_pair_ExtIEs;

typedef struct s1apProtExtnCont_UE_S1AP_ID_pair_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *member;
}SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs;

typedef struct s1apUE_S1AP_ID_pair
{
 TknPres pres;
 SztMME_UE_S1AP_ID mME_UE_S1AP_ID;
 SztENB_UE_S1AP_ID eNB_UE_S1AP_ID;
 SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs iE_Extns;
} SztUE_S1AP_ID_pair;

typedef struct s1apUE_S1AP_IDs
{
 TknU8 choice;
 union {
  SztUE_S1AP_ID_pair uE_S1AP_ID_pair;
  SztMME_UE_S1AP_ID mME_UE_S1AP_ID;
 } val;
} SztUE_S1AP_IDs;

typedef struct s1ap_ExtnUE_assocLogS1_ConItemExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnUE_assocLogS1_ConItemExtIEsCls;
typedef struct s1apProtExtnField_UE_assocLogS1_ConItemExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnUE_assocLogS1_ConItemExtIEsCls extensionValue;
} SztProtExtnField_UE_assocLogS1_ConItemExtIEs;

typedef struct s1apProtExtnCont_UE_assocLogS1_ConItemExtIEs
{
 TknU16 noComp;
 SztProtExtnField_UE_assocLogS1_ConItemExtIEs *member;
}SztProtExtnCont_UE_assocLogS1_ConItemExtIEs;

typedef struct s1apUE_assocLogS1_ConItem
{
 TknPres pres;
 SztMME_UE_S1AP_ID mME_UE_S1AP_ID;
 SztENB_UE_S1AP_ID eNB_UE_S1AP_ID;
 SztProtExtnCont_UE_assocLogS1_ConItemExtIEs iE_Extns;
} SztUE_assocLogS1_ConItem;


typedef TknBStr32 SztUEIdentityIdxValue;
typedef struct s1apUEPagID
{
 TknU8 choice;
 union {
  SztS_TMSI s_TMSI;
  SztIMSI iMSI;
 } val;
} SztUEPagID;


typedef TknStrOSXL SztUERadioCapblty;
typedef struct s1ap_ExtnUESecurCapabilities_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnUESecurCapabilities_ExtIEsCls;
typedef struct s1apProtExtnField_UESecurCapabilities_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnUESecurCapabilities_ExtIEsCls extensionValue;
} SztProtExtnField_UESecurCapabilities_ExtIEs;

typedef struct s1apProtExtnCont_UESecurCapabilities_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_UESecurCapabilities_ExtIEs *member;
}SztProtExtnCont_UESecurCapabilities_ExtIEs;

typedef struct s1apUESecurCapabilities
{
 TknPres pres;
 SztEncryptionAlgorithms encryptionAlgorithms;
 SztIntegrityProtectionAlgorithms integrityProtectionAlgorithms;
 SztProtExtnCont_UESecurCapabilities_ExtIEs iE_Extns;
} SztUESecurCapabilities;


typedef enum enumSztVoiceSupportMatchIndicator
{
 SztVoiceSupportMatchIndicatorsupportedEnum,
 SztVoiceSupportMatchIndicatornot_supportedEnum
} EnumSztVoiceSupportMatchIndicator;
typedef TknU32 SztVoiceSupportMatchIndicator;

typedef struct s1apWarningAreaLst
{
 TknU8 choice;
 union {
  SztECGILst cellIDLst;
  SztTAILstforWarning trackingAreaLstforWarning;
  SztEmergencyAreaIDLst emergencyAreaIDLst;
 } val;
} SztWarningAreaLst;


typedef TknStr4 SztWarningTyp;

typedef TknStrOSXL SztWarningSecurInfo;

typedef TknStrOSXL SztWarningMsgContents;
typedef struct s1ap_ValueHovrReqdIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztHovrTyp sztHovrTyp;
  SztCause sztCause;
  SztTgetID sztTgetID;
  SztDirect_Fwding_Path_Avlblty sztDirect_Fwding_Path_Avlblty;
  SztSRVCCHOInd sztSRVCCHOInd;
  SztSrc_ToTget_TprntCont sztid_Src_ToTget_TprntCont;
  SztSrc_ToTget_TprntCont sztid_Src_ToTget_TprntCont_Secondary;
  SztMSClassmark2 sztMSClassmark2;
  SztMSClassmark3 sztMSClassmark3;
  SztCSG_Id sztCSG_Id;
  SztCellAccessMode sztCellAccessMode;
  SztPS_ServiceNotAvailable sztPS_ServiceNotAvailable;
 } u;
} Szt_ValueHovrReqdIEsCls;
typedef struct s1apProtIE_Field_HovrReqdIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrReqdIEsCls value;
} SztProtIE_Field_HovrReqdIEs;

typedef struct s1apProtIE_Cont_HovrReqdIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrReqdIEs *member;
}SztProtIE_Cont_HovrReqdIEs;

typedef struct s1apHovrReqd
{
 TknPres pres;
 SztProtIE_Cont_HovrReqdIEs protocolIEs;
} SztHovrReqd;

typedef struct s1ap_ExtnE_RABDataFwdingItem_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABDataFwdingItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABDataFwdingItem_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABDataFwdingItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABDataFwdingItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABDataFwdingItem_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABDataFwdingItem_ExtIEs *member;
}SztProtExtnCont_E_RABDataFwdingItem_ExtIEs;

typedef struct s1apE_RABDataFwdingItem
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztTportLyrAddr dL_transportLyrAddr;
 SztGTP_TEID dL_gTP_TEID;
 SztTportLyrAddr uL_TportLyrAddr;
 SztGTP_TEID uL_GTP_TEID;
 SztProtExtnCont_E_RABDataFwdingItem_ExtIEs iE_Extns;
} SztE_RABDataFwdingItem;

typedef struct s1ap_ValueE_RABDataFwdingItemIEsCls{
 union {
  SztE_RABDataFwdingItem sztE_RABDataFwdingItem;
 } u;
} Szt_ValueE_RABDataFwdingItemIEsCls;
typedef struct s1apProtIE_Field_E_RABDataFwdingItemIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABDataFwdingItemIEsCls value;
} SztProtIE_Field_E_RABDataFwdingItemIEs;


typedef SztProtIE_Field_E_RABDataFwdingItemIEs SztProtIE_SingleCont_E_RABDataFwdingItemIEs;
typedef struct s1apProtIE_ContLst_E_RABDataFwdingItemIEs
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABDataFwdingItemIEs *member;
}SztProtIE_ContLst_E_RABDataFwdingItemIEs;


typedef SztProtIE_ContLst_E_RABDataFwdingItemIEs SztE_RAB_IE_ContLst_E_RABDataFwdingItemIEs;

typedef SztE_RAB_IE_ContLst_E_RABDataFwdingItemIEs SztE_RABSubjtoDataFwdingLst;
typedef struct s1ap_ValueHovrCmmdIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztHovrTyp sztHovrTyp;
  SztNASSecurParamsfromE_UTRAN sztNASSecurParamsfromE_UTRAN;
  SztE_RABSubjtoDataFwdingLst sztE_RABSubjtoDataFwdingLst;
  SztE_RABLst sztE_RABLst;
  SztTget_ToSrc_TprntCont sztid_Tget_ToSrc_TprntCont;
  SztTget_ToSrc_TprntCont sztid_Tget_ToSrc_TprntCont_Secondary;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueHovrCmmdIEsCls;
typedef struct s1apProtIE_Field_HovrCmmdIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrCmmdIEsCls value;
} SztProtIE_Field_HovrCmmdIEs;

typedef struct s1apProtIE_Cont_HovrCmmdIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrCmmdIEs *member;
}SztProtIE_Cont_HovrCmmdIEs;

typedef struct s1apHovrCmmd
{
 TknPres pres;
 SztProtIE_Cont_HovrCmmdIEs protocolIEs;
} SztHovrCmmd;

typedef struct s1ap_ValueHovrPrepFailIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCause sztCause;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueHovrPrepFailIEsCls;
typedef struct s1apProtIE_Field_HovrPrepFailIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrPrepFailIEsCls value;
} SztProtIE_Field_HovrPrepFailIEs;

typedef struct s1apProtIE_Cont_HovrPrepFailIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrPrepFailIEs *member;
}SztProtIE_Cont_HovrPrepFailIEs;

typedef struct s1apHovrPrepFail
{
 TknPres pres;
 SztProtIE_Cont_HovrPrepFailIEs protocolIEs;
} SztHovrPrepFail;

typedef struct s1ap_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls{
 union {
  SztData_Fwding_Not_Possible sztData_Fwding_Not_Possible;
 } u;
} Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *member;
}SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs;

typedef struct s1apE_RABToBeSetupItemHOReq
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztTportLyrAddr transportLyrAddr;
 SztGTP_TEID gTP_TEID;
 SztE_RABLvlQoSParams e_RABlevelQosParams;
 SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs iE_Extns;
} SztE_RABToBeSetupItemHOReq;

typedef struct s1ap_ValueE_RABToBeSetupItemHOReqIEsCls{
 union {
  SztE_RABToBeSetupItemHOReq sztE_RABToBeSetupItemHOReq;
 } u;
} Szt_ValueE_RABToBeSetupItemHOReqIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSetupItemHOReqIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABToBeSetupItemHOReqIEsCls value;
} SztProtIE_Field_E_RABToBeSetupItemHOReqIEs;


typedef SztProtIE_Field_E_RABToBeSetupItemHOReqIEs SztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs;
typedef struct s1apProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs *member;
}SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs;


typedef SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs SztE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs;

typedef SztE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs SztE_RABToBeSetupLstHOReq;
typedef struct s1ap_ValueHovrRqstIEsCls{
 union {
  SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID;
  SztHovrTyp sztHovrTyp;
  SztCause sztCause;
  SztUEAggMaxBitrate sztUEAggMaxBitrate;
  SztE_RABToBeSetupLstHOReq sztE_RABToBeSetupLstHOReq;
  SztSrc_ToTget_TprntCont sztSrc_ToTget_TprntCont;
  SztUESecurCapabilities sztUESecurCapabilities;
  SztHovrRestrnLst sztHovrRestrnLst;
  SztTraceActvn sztTraceActvn;
  SztRqstTyp sztRqstTyp;
  SztSRVCCOperationPossible sztSRVCCOperationPossible;
  SztSecurCntxt sztSecurCntxt;
  SztNASSecurParamstoE_UTRAN sztNASSecurParamstoE_UTRAN;
  SztCSG_Id sztCSG_Id;
  SztCSGMembershipStatus sztCSGMembershipStatus;
  SztGUMMEI sztGUMMEI;
  SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID_2;
  SztManagementBasedMDTAllowed sztManagementBasedMDTAllowed;
  SztMDTPLMNLst sztMDTPLMNLst;
 } u;
} Szt_ValueHovrRqstIEsCls;
typedef struct s1apProtIE_Field_HovrRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrRqstIEsCls value;
} SztProtIE_Field_HovrRqstIEs;

typedef struct s1apProtIE_Cont_HovrRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrRqstIEs *member;
}SztProtIE_Cont_HovrRqstIEs;

typedef struct s1apHovrRqst
{
 TknPres pres;
 SztProtIE_Cont_HovrRqstIEs protocolIEs;
} SztHovrRqst;

typedef struct s1ap_ExtnE_RABAdmtdItem_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABAdmtdItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABAdmtdItem_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABAdmtdItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABAdmtdItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABAdmtdItem_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABAdmtdItem_ExtIEs *member;
}SztProtExtnCont_E_RABAdmtdItem_ExtIEs;

typedef struct s1apE_RABAdmtdItem
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztTportLyrAddr transportLyrAddr;
 SztGTP_TEID gTP_TEID;
 SztTportLyrAddr dL_transportLyrAddr;
 SztGTP_TEID dL_gTP_TEID;
 SztTportLyrAddr uL_TportLyrAddr;
 SztGTP_TEID uL_GTP_TEID;
 SztProtExtnCont_E_RABAdmtdItem_ExtIEs iE_Extns;
} SztE_RABAdmtdItem;

typedef struct s1ap_ValueE_RABAdmtdItemIEsCls{
 union {
  SztE_RABAdmtdItem sztE_RABAdmtdItem;
 } u;
} Szt_ValueE_RABAdmtdItemIEsCls;
typedef struct s1apProtIE_Field_E_RABAdmtdItemIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABAdmtdItemIEsCls value;
} SztProtIE_Field_E_RABAdmtdItemIEs;


typedef SztProtIE_Field_E_RABAdmtdItemIEs SztProtIE_SingleCont_E_RABAdmtdItemIEs;
typedef struct s1apProtIE_ContLst_E_RABAdmtdItemIEs
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABAdmtdItemIEs *member;
}SztProtIE_ContLst_E_RABAdmtdItemIEs;


typedef SztProtIE_ContLst_E_RABAdmtdItemIEs SztE_RAB_IE_ContLst_E_RABAdmtdItemIEs;

typedef SztE_RAB_IE_ContLst_E_RABAdmtdItemIEs SztE_RABAdmtdLst;
typedef struct s1ap_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls;
typedef struct s1apProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls extensionValue;
} SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs;

typedef struct s1apProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *member;
}SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs;

typedef struct s1apE_RABFailedToSetupItemHOReqAck
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztCause cause;
 SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs iE_Extns;
} SztE_RABFailedToSetupItemHOReqAck;

typedef struct s1ap_ValueE_RABFailedtoSetupItemHOReqAckIEsCls{
 union {
  SztE_RABFailedToSetupItemHOReqAck sztE_RABFailedToSetupItemHOReqAck;
 } u;
} Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls;
typedef struct s1apProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls value;
} SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs;


typedef SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs SztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs;
typedef struct s1apProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs *member;
}SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs;


typedef SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs SztE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs;

typedef SztE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs SztE_RABFailedtoSetupLstHOReqAck;
typedef struct s1ap_ValueHovrRqstAckgIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_RABAdmtdLst sztE_RABAdmtdLst;
  SztE_RABFailedtoSetupLstHOReqAck sztE_RABFailedtoSetupLstHOReqAck;
  SztTget_ToSrc_TprntCont sztTget_ToSrc_TprntCont;
  SztCSG_Id sztCSG_Id;
  SztCriticalityDiag sztCriticalityDiag;
  SztCellAccessMode sztCellAccessMode;
 } u;
} Szt_ValueHovrRqstAckgIEsCls;
typedef struct s1apProtIE_Field_HovrRqstAckgIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrRqstAckgIEsCls value;
} SztProtIE_Field_HovrRqstAckgIEs;

typedef struct s1apProtIE_Cont_HovrRqstAckgIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrRqstAckgIEs *member;
}SztProtIE_Cont_HovrRqstAckgIEs;

typedef struct s1apHovrRqstAckg
{
 TknPres pres;
 SztProtIE_Cont_HovrRqstAckgIEs protocolIEs;
} SztHovrRqstAckg;

typedef struct s1ap_ValueHovrFailIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztCause sztCause;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueHovrFailIEsCls;
typedef struct s1apProtIE_Field_HovrFailIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrFailIEsCls value;
} SztProtIE_Field_HovrFailIEs;

typedef struct s1apProtIE_Cont_HovrFailIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrFailIEs *member;
}SztProtIE_Cont_HovrFailIEs;

typedef struct s1apHovrFail
{
 TknPres pres;
 SztProtIE_Cont_HovrFailIEs protocolIEs;
} SztHovrFail;

typedef struct s1ap_ValueHovrNtfyIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztEUTRAN_CGI sztEUTRAN_CGI;
  SztTAI sztTAI;
  SztTunnelInform sztTunnelInform;
 } u;
} Szt_ValueHovrNtfyIEsCls;
typedef struct s1apProtIE_Field_HovrNtfyIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrNtfyIEsCls value;
} SztProtIE_Field_HovrNtfyIEs;

typedef struct s1apProtIE_Cont_HovrNtfyIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrNtfyIEs *member;
}SztProtIE_Cont_HovrNtfyIEs;

typedef struct s1apHovrNtfy
{
 TknPres pres;
 SztProtIE_Cont_HovrNtfyIEs protocolIEs;
} SztHovrNtfy;

typedef struct s1ap_ExtnE_RABToBeSwedDLItem_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSwedDLItem_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSwedDLItem_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *member;
}SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs;

typedef struct s1apE_RABToBeSwedDLItem
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztTportLyrAddr transportLyrAddr;
 SztGTP_TEID gTP_TEID;
 SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs iE_Extns;
} SztE_RABToBeSwedDLItem;

typedef struct s1ap_ValueE_RABToBeSwedDLItemIEsCls{
 union {
  SztE_RABToBeSwedDLItem sztE_RABToBeSwedDLItem;
 } u;
} Szt_ValueE_RABToBeSwedDLItemIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSwedDLItemIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABToBeSwedDLItemIEsCls value;
} SztProtIE_Field_E_RABToBeSwedDLItemIEs;


typedef SztProtIE_Field_E_RABToBeSwedDLItemIEs SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs;
typedef struct s1apProtIE_ContLst_E_RABToBeSwedDLItemIEs
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs *member;
}SztProtIE_ContLst_E_RABToBeSwedDLItemIEs;


typedef SztProtIE_ContLst_E_RABToBeSwedDLItemIEs SztE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs;

typedef SztE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs SztE_RABToBeSwedDLLst;
typedef struct s1ap_ValuePathSwRqstIEsCls{
 union {
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_RABToBeSwedDLLst sztE_RABToBeSwedDLLst;
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztEUTRAN_CGI sztEUTRAN_CGI;
  SztTAI sztTAI;
  SztUESecurCapabilities sztUESecurCapabilities;
  SztCSG_Id sztCSG_Id;
  SztCellAccessMode sztCellAccessMode;
  SztGUMMEI sztGUMMEI;
  SztCSGMembershipStatus sztCSGMembershipStatus;
  SztTunnelInform sztTunnelInform;
 } u;
} Szt_ValuePathSwRqstIEsCls;
typedef struct s1apProtIE_Field_PathSwRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValuePathSwRqstIEsCls value;
} SztProtIE_Field_PathSwRqstIEs;

typedef struct s1apProtIE_Cont_PathSwRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_PathSwRqstIEs *member;
}SztProtIE_Cont_PathSwRqstIEs;

typedef struct s1apPathSwRqst
{
 TknPres pres;
 SztProtIE_Cont_PathSwRqstIEs protocolIEs;
} SztPathSwRqst;

typedef struct s1ap_ExtnE_RABToBeSwedULItem_ExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSwedULItem_ExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSwedULItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSwedULItem_ExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *member;
}SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs;

typedef struct s1apE_RABToBeSwedULItem
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztTportLyrAddr transportLyrAddr;
 SztGTP_TEID gTP_TEID;
 SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs iE_Extns;
} SztE_RABToBeSwedULItem;

typedef struct s1ap_ValueE_RABToBeSwedULItemIEsCls{
 union {
  SztE_RABToBeSwedULItem sztE_RABToBeSwedULItem;
 } u;
} Szt_ValueE_RABToBeSwedULItemIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSwedULItemIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABToBeSwedULItemIEsCls value;
} SztProtIE_Field_E_RABToBeSwedULItemIEs;


typedef SztProtIE_Field_E_RABToBeSwedULItemIEs SztProtIE_SingleCont_E_RABToBeSwedULItemIEs;
typedef struct s1apProtIE_ContLst_E_RABToBeSwedULItemIEs
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABToBeSwedULItemIEs *member;
}SztProtIE_ContLst_E_RABToBeSwedULItemIEs;


typedef SztProtIE_ContLst_E_RABToBeSwedULItemIEs SztE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs;

typedef SztE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs SztE_RABToBeSwedULLst;
typedef struct s1ap_ValuePathSwRqstAckgIEsCls{
 union {
  SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztUEAggMaxBitrate sztUEAggMaxBitrate;
  SztE_RABToBeSwedULLst sztE_RABToBeSwedULLst;
  SztE_RABLst sztE_RABLst;
  SztSecurCntxt sztSecurCntxt;
  SztCriticalityDiag sztCriticalityDiag;
  SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID_2;
  SztCSGMembershipStatus sztCSGMembershipStatus;
 } u;
} Szt_ValuePathSwRqstAckgIEsCls;
typedef struct s1apProtIE_Field_PathSwRqstAckgIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValuePathSwRqstAckgIEsCls value;
} SztProtIE_Field_PathSwRqstAckgIEs;

typedef struct s1apProtIE_Cont_PathSwRqstAckgIEs
{
 TknU16 noComp;
 SztProtIE_Field_PathSwRqstAckgIEs *member;
}SztProtIE_Cont_PathSwRqstAckgIEs;

typedef struct s1apPathSwRqstAckg
{
 TknPres pres;
 SztProtIE_Cont_PathSwRqstAckgIEs protocolIEs;
} SztPathSwRqstAckg;

typedef struct s1ap_ValuePathSwRqstFailIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCause sztCause;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValuePathSwRqstFailIEsCls;
typedef struct s1apProtIE_Field_PathSwRqstFailIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValuePathSwRqstFailIEsCls value;
} SztProtIE_Field_PathSwRqstFailIEs;

typedef struct s1apProtIE_Cont_PathSwRqstFailIEs
{
 TknU16 noComp;
 SztProtIE_Field_PathSwRqstFailIEs *member;
}SztProtIE_Cont_PathSwRqstFailIEs;

typedef struct s1apPathSwRqstFail
{
 TknPres pres;
 SztProtIE_Cont_PathSwRqstFailIEs protocolIEs;
} SztPathSwRqstFail;

typedef struct s1ap_ValueHovrCancelIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCause sztCause;
 } u;
} Szt_ValueHovrCancelIEsCls;
typedef struct s1apProtIE_Field_HovrCancelIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrCancelIEsCls value;
} SztProtIE_Field_HovrCancelIEs;

typedef struct s1apProtIE_Cont_HovrCancelIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrCancelIEs *member;
}SztProtIE_Cont_HovrCancelIEs;

typedef struct s1apHovrCancel
{
 TknPres pres;
 SztProtIE_Cont_HovrCancelIEs protocolIEs;
} SztHovrCancel;

typedef struct s1ap_ValueHovrCancelAckgIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueHovrCancelAckgIEsCls;
typedef struct s1apProtIE_Field_HovrCancelAckgIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueHovrCancelAckgIEsCls value;
} SztProtIE_Field_HovrCancelAckgIEs;

typedef struct s1apProtIE_Cont_HovrCancelAckgIEs
{
 TknU16 noComp;
 SztProtIE_Field_HovrCancelAckgIEs *member;
}SztProtIE_Cont_HovrCancelAckgIEs;

typedef struct s1apHovrCancelAckg
{
 TknPres pres;
 SztProtIE_Cont_HovrCancelAckgIEs protocolIEs;
} SztHovrCancelAckg;

typedef struct s1ap_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls{
 union {
  SztCorrelation_ID sztCorrelation_ID;
 } u;
} Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *member;
}SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs;

typedef struct s1apE_RABToBeSetupItemBrSUReq
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztE_RABLvlQoSParams e_RABlevelQoSParams;
 SztTportLyrAddr transportLyrAddr;
 SztGTP_TEID gTP_TEID;
 SztNAS_PDU nAS_PDU;
 SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs iE_Extns;
} SztE_RABToBeSetupItemBrSUReq;

typedef struct s1ap_ValueE_RABToBeSetupItemBrSUReqIEsCls{
 union {
  SztE_RABToBeSetupItemBrSUReq sztE_RABToBeSetupItemBrSUReq;
 } u;
} Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSetupItemBrSUReqIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls value;
} SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs;


typedef SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs SztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs;
typedef struct s1apE_RABToBeSetupLstBrSUReq
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs *member;
}SztE_RABToBeSetupLstBrSUReq;

typedef struct s1ap_ValueE_RABSetupRqstIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztUEAggMaxBitrate sztUEAggMaxBitrate;
  SztE_RABToBeSetupLstBrSUReq sztE_RABToBeSetupLstBrSUReq;
 } u;
} Szt_ValueE_RABSetupRqstIEsCls;
typedef struct s1apProtIE_Field_E_RABSetupRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABSetupRqstIEsCls value;
} SztProtIE_Field_E_RABSetupRqstIEs;

typedef struct s1apProtIE_Cont_E_RABSetupRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_E_RABSetupRqstIEs *member;
}SztProtIE_Cont_E_RABSetupRqstIEs;

typedef struct s1apE_RABSetupRqst
{
 TknPres pres;
 SztProtIE_Cont_E_RABSetupRqstIEs protocolIEs;
} SztE_RABSetupRqst;

typedef struct s1ap_ExtnE_RABSetupItemBrSUResExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABSetupItemBrSUResExtIEsCls;
typedef struct s1apProtExtnField_E_RABSetupItemBrSUResExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABSetupItemBrSUResExtIEsCls extensionValue;
} SztProtExtnField_E_RABSetupItemBrSUResExtIEs;

typedef struct s1apProtExtnCont_E_RABSetupItemBrSUResExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABSetupItemBrSUResExtIEs *member;
}SztProtExtnCont_E_RABSetupItemBrSUResExtIEs;

typedef struct s1apE_RABSetupItemBrSURes
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztTportLyrAddr transportLyrAddr;
 SztGTP_TEID gTP_TEID;
 SztProtExtnCont_E_RABSetupItemBrSUResExtIEs iE_Extns;
} SztE_RABSetupItemBrSURes;

typedef struct s1ap_ValueE_RABSetupItemBrSUResIEsCls{
 union {
  SztE_RABSetupItemBrSURes sztE_RABSetupItemBrSURes;
 } u;
} Szt_ValueE_RABSetupItemBrSUResIEsCls;
typedef struct s1apProtIE_Field_E_RABSetupItemBrSUResIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABSetupItemBrSUResIEsCls value;
} SztProtIE_Field_E_RABSetupItemBrSUResIEs;


typedef SztProtIE_Field_E_RABSetupItemBrSUResIEs SztProtIE_SingleCont_E_RABSetupItemBrSUResIEs;
typedef struct s1apE_RABSetupLstBrSURes
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABSetupItemBrSUResIEs *member;
}SztE_RABSetupLstBrSURes;

typedef struct s1ap_ValueE_RABSetupRespIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_RABSetupLstBrSURes sztE_RABSetupLstBrSURes;
  SztE_RABLst sztE_RABLst;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueE_RABSetupRespIEsCls;
typedef struct s1apProtIE_Field_E_RABSetupRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABSetupRespIEsCls value;
} SztProtIE_Field_E_RABSetupRespIEs;

typedef struct s1apProtIE_Cont_E_RABSetupRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_E_RABSetupRespIEs *member;
}SztProtIE_Cont_E_RABSetupRespIEs;

typedef struct s1apE_RABSetupResp
{
 TknPres pres;
 SztProtIE_Cont_E_RABSetupRespIEs protocolIEs;
} SztE_RABSetupResp;

typedef struct s1ap_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *member;
}SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs;

typedef struct s1apE_RABToBeMdfdItemBrModReq
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztE_RABLvlQoSParams e_RABLvlQoSParams;
 SztNAS_PDU nAS_PDU;
 SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs iE_Extns;
} SztE_RABToBeMdfdItemBrModReq;

typedef struct s1ap_ValueE_RABToBeMdfdItemBrModReqIEsCls{
 union {
  SztE_RABToBeMdfdItemBrModReq sztE_RABToBeMdfdItemBrModReq;
 } u;
} Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeMdfdItemBrModReqIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls value;
} SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs;


typedef SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs SztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs;
typedef struct s1apE_RABToBeMdfdLstBrModReq
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs *member;
}SztE_RABToBeMdfdLstBrModReq;

typedef struct s1ap_ValueE_RABMdfyRqstIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztUEAggMaxBitrate sztUEAggMaxBitrate;
  SztE_RABToBeMdfdLstBrModReq sztE_RABToBeMdfdLstBrModReq;
 } u;
} Szt_ValueE_RABMdfyRqstIEsCls;
typedef struct s1apProtIE_Field_E_RABMdfyRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABMdfyRqstIEsCls value;
} SztProtIE_Field_E_RABMdfyRqstIEs;

typedef struct s1apProtIE_Cont_E_RABMdfyRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_E_RABMdfyRqstIEs *member;
}SztProtIE_Cont_E_RABMdfyRqstIEs;

typedef struct s1apE_RABMdfyRqst
{
 TknPres pres;
 SztProtIE_Cont_E_RABMdfyRqstIEs protocolIEs;
} SztE_RABMdfyRqst;

typedef struct s1ap_ExtnE_RABMdfyItemBrModResExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABMdfyItemBrModResExtIEsCls;
typedef struct s1apProtExtnField_E_RABMdfyItemBrModResExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABMdfyItemBrModResExtIEsCls extensionValue;
} SztProtExtnField_E_RABMdfyItemBrModResExtIEs;

typedef struct s1apProtExtnCont_E_RABMdfyItemBrModResExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABMdfyItemBrModResExtIEs *member;
}SztProtExtnCont_E_RABMdfyItemBrModResExtIEs;

typedef struct s1apE_RABMdfyItemBrModRes
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztProtExtnCont_E_RABMdfyItemBrModResExtIEs iE_Extns;
} SztE_RABMdfyItemBrModRes;

typedef struct s1ap_ValueE_RABMdfyItemBrModResIEsCls{
 union {
  SztE_RABMdfyItemBrModRes sztE_RABMdfyItemBrModRes;
 } u;
} Szt_ValueE_RABMdfyItemBrModResIEsCls;
typedef struct s1apProtIE_Field_E_RABMdfyItemBrModResIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABMdfyItemBrModResIEsCls value;
} SztProtIE_Field_E_RABMdfyItemBrModResIEs;


typedef SztProtIE_Field_E_RABMdfyItemBrModResIEs SztProtIE_SingleCont_E_RABMdfyItemBrModResIEs;
typedef struct s1apE_RABMdfyLstBrModRes
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABMdfyItemBrModResIEs *member;
}SztE_RABMdfyLstBrModRes;

typedef struct s1ap_ValueE_RABMdfyRespIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_RABMdfyLstBrModRes sztE_RABMdfyLstBrModRes;
  SztE_RABLst sztE_RABLst;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueE_RABMdfyRespIEsCls;
typedef struct s1apProtIE_Field_E_RABMdfyRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABMdfyRespIEsCls value;
} SztProtIE_Field_E_RABMdfyRespIEs;

typedef struct s1apProtIE_Cont_E_RABMdfyRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_E_RABMdfyRespIEs *member;
}SztProtIE_Cont_E_RABMdfyRespIEs;

typedef struct s1apE_RABMdfyResp
{
 TknPres pres;
 SztProtIE_Cont_E_RABMdfyRespIEs protocolIEs;
} SztE_RABMdfyResp;

typedef struct s1ap_ValueE_RABRlsCmmdIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztUEAggMaxBitrate sztUEAggMaxBitrate;
  SztE_RABLst sztE_RABLst;
  SztNAS_PDU sztNAS_PDU;
 } u;
} Szt_ValueE_RABRlsCmmdIEsCls;
typedef struct s1apProtIE_Field_E_RABRlsCmmdIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABRlsCmmdIEsCls value;
} SztProtIE_Field_E_RABRlsCmmdIEs;

typedef struct s1apProtIE_Cont_E_RABRlsCmmdIEs
{
 TknU16 noComp;
 SztProtIE_Field_E_RABRlsCmmdIEs *member;
}SztProtIE_Cont_E_RABRlsCmmdIEs;

typedef struct s1apE_RABRlsCmmd
{
 TknPres pres;
 SztProtIE_Cont_E_RABRlsCmmdIEs protocolIEs;
} SztE_RABRlsCmmd;

typedef struct s1ap_ExtnE_RABRlsItemBrRelCompExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls;
typedef struct s1apProtExtnField_E_RABRlsItemBrRelCompExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls extensionValue;
} SztProtExtnField_E_RABRlsItemBrRelCompExtIEs;

typedef struct s1apProtExtnCont_E_RABRlsItemBrRelCompExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *member;
}SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs;

typedef struct s1apE_RABRlsItemBrRelComp
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs iE_Extns;
} SztE_RABRlsItemBrRelComp;

typedef struct s1ap_ValueE_RABRlsItemBrRelCompIEsCls{
 union {
  SztE_RABRlsItemBrRelComp sztE_RABRlsItemBrRelComp;
 } u;
} Szt_ValueE_RABRlsItemBrRelCompIEsCls;
typedef struct s1apProtIE_Field_E_RABRlsItemBrRelCompIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABRlsItemBrRelCompIEsCls value;
} SztProtIE_Field_E_RABRlsItemBrRelCompIEs;


typedef SztProtIE_Field_E_RABRlsItemBrRelCompIEs SztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs;
typedef struct s1apE_RABRlsLstBrRelComp
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs *member;
}SztE_RABRlsLstBrRelComp;

typedef struct s1ap_ValueE_RABRlsRespIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_RABRlsLstBrRelComp sztE_RABRlsLstBrRelComp;
  SztE_RABLst sztE_RABLst;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueE_RABRlsRespIEsCls;
typedef struct s1apProtIE_Field_E_RABRlsRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABRlsRespIEsCls value;
} SztProtIE_Field_E_RABRlsRespIEs;

typedef struct s1apProtIE_Cont_E_RABRlsRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_E_RABRlsRespIEs *member;
}SztProtIE_Cont_E_RABRlsRespIEs;

typedef struct s1apE_RABRlsResp
{
 TknPres pres;
 SztProtIE_Cont_E_RABRlsRespIEs protocolIEs;
} SztE_RABRlsResp;

typedef struct s1ap_ValueE_RABRlsIndIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_RABLst sztE_RABLst;
 } u;
} Szt_ValueE_RABRlsIndIEsCls;
typedef struct s1apProtIE_Field_E_RABRlsIndIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABRlsIndIEsCls value;
} SztProtIE_Field_E_RABRlsIndIEs;

typedef struct s1apProtIE_Cont_E_RABRlsIndIEs
{
 TknU16 noComp;
 SztProtIE_Field_E_RABRlsIndIEs *member;
}SztProtIE_Cont_E_RABRlsIndIEs;

typedef struct s1apE_RABRlsInd
{
 TknPres pres;
 SztProtIE_Cont_E_RABRlsIndIEs protocolIEs;
} SztE_RABRlsInd;

typedef struct s1ap_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls{
 union {
  SztCorrelation_ID sztCorrelation_ID;
 } u;
} Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *member;
}SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs;

typedef struct s1apE_RABToBeSetupItemCtxtSUReq
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztE_RABLvlQoSParams e_RABlevelQoSParams;
 SztTportLyrAddr transportLyrAddr;
 SztGTP_TEID gTP_TEID;
 SztNAS_PDU nAS_PDU;
 SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs iE_Extns;
} SztE_RABToBeSetupItemCtxtSUReq;

typedef struct s1ap_ValueE_RABToBeSetupItemCtxtSUReqIEsCls{
 union {
  SztE_RABToBeSetupItemCtxtSUReq sztE_RABToBeSetupItemCtxtSUReq;
 } u;
} Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls value;
} SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs;


typedef SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs SztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs;
typedef struct s1apE_RABToBeSetupLstCtxtSUReq
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs *member;
}SztE_RABToBeSetupLstCtxtSUReq;

typedef struct s1ap_ValueInitCntxtSetupRqstIEsCls{
 union {
  SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztUEAggMaxBitrate sztUEAggMaxBitrate;
  SztE_RABToBeSetupLstCtxtSUReq sztE_RABToBeSetupLstCtxtSUReq;
  SztUESecurCapabilities sztUESecurCapabilities;
  SztSecurKey sztSecurKey;
  SztTraceActvn sztTraceActvn;
  SztHovrRestrnLst sztHovrRestrnLst;
  SztUERadioCapblty sztUERadioCapblty;
  SztSubscriberProfileIDforRFP sztSubscriberProfileIDforRFP;
  SztCSFallbackIndicator sztCSFallbackIndicator;
  SztSRVCCOperationPossible sztSRVCCOperationPossible;
  SztCSGMembershipStatus sztCSGMembershipStatus;
  SztLAI sztLAI;
  SztGUMMEI sztGUMMEI;
  SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID_2;
  SztManagementBasedMDTAllowed sztManagementBasedMDTAllowed;
  SztMDTPLMNLst sztMDTPLMNLst;
 } u;
} Szt_ValueInitCntxtSetupRqstIEsCls;
typedef struct s1apProtIE_Field_InitCntxtSetupRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueInitCntxtSetupRqstIEsCls value;
} SztProtIE_Field_InitCntxtSetupRqstIEs;

typedef struct s1apProtIE_Cont_InitCntxtSetupRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_InitCntxtSetupRqstIEs *member;
}SztProtIE_Cont_InitCntxtSetupRqstIEs;

typedef struct s1apInitCntxtSetupRqst
{
 TknPres pres;
 SztProtIE_Cont_InitCntxtSetupRqstIEs protocolIEs;
} SztInitCntxtSetupRqst;

typedef struct s1ap_ExtnE_RABSetupItemCtxtSUResExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls;
typedef struct s1apProtExtnField_E_RABSetupItemCtxtSUResExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls extensionValue;
} SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs;

typedef struct s1apProtExtnCont_E_RABSetupItemCtxtSUResExtIEs
{
 TknU16 noComp;
 SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *member;
}SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs;

typedef struct s1apE_RABSetupItemCtxtSURes
{
 TknPres pres;
 SztE_RAB_ID e_RAB_ID;
 SztTportLyrAddr transportLyrAddr;
 SztGTP_TEID gTP_TEID;
 SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs iE_Extns;
} SztE_RABSetupItemCtxtSURes;

typedef struct s1ap_ValueE_RABSetupItemCtxtSUResIEsCls{
 union {
  SztE_RABSetupItemCtxtSURes sztE_RABSetupItemCtxtSURes;
 } u;
} Szt_ValueE_RABSetupItemCtxtSUResIEsCls;
typedef struct s1apProtIE_Field_E_RABSetupItemCtxtSUResIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueE_RABSetupItemCtxtSUResIEsCls value;
} SztProtIE_Field_E_RABSetupItemCtxtSUResIEs;


typedef SztProtIE_Field_E_RABSetupItemCtxtSUResIEs SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs;
typedef struct s1apE_RABSetupLstCtxtSURes
{
 TknU16 noComp;
 SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs *member;
}SztE_RABSetupLstCtxtSURes;

typedef struct s1ap_ValueInitCntxtSetupRespIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_RABSetupLstCtxtSURes sztE_RABSetupLstCtxtSURes;
  SztE_RABLst sztE_RABLst;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueInitCntxtSetupRespIEsCls;
typedef struct s1apProtIE_Field_InitCntxtSetupRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueInitCntxtSetupRespIEsCls value;
} SztProtIE_Field_InitCntxtSetupRespIEs;

typedef struct s1apProtIE_Cont_InitCntxtSetupRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_InitCntxtSetupRespIEs *member;
}SztProtIE_Cont_InitCntxtSetupRespIEs;

typedef struct s1apInitCntxtSetupResp
{
 TknPres pres;
 SztProtIE_Cont_InitCntxtSetupRespIEs protocolIEs;
} SztInitCntxtSetupResp;

typedef struct s1ap_ValueInitCntxtSetupFailIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCause sztCause;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueInitCntxtSetupFailIEsCls;
typedef struct s1apProtIE_Field_InitCntxtSetupFailIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueInitCntxtSetupFailIEsCls value;
} SztProtIE_Field_InitCntxtSetupFailIEs;

typedef struct s1apProtIE_Cont_InitCntxtSetupFailIEs
{
 TknU16 noComp;
 SztProtIE_Field_InitCntxtSetupFailIEs *member;
}SztProtIE_Cont_InitCntxtSetupFailIEs;

typedef struct s1apInitCntxtSetupFail
{
 TknPres pres;
 SztProtIE_Cont_InitCntxtSetupFailIEs protocolIEs;
} SztInitCntxtSetupFail;

typedef struct s1ap_ExtnTAIItemExtIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ExtnTAIItemExtIEsCls;
typedef struct s1apProtExtnField_TAIItemExtIEs
{
 TknPres pres;
 SztProtExtnID id;
 SztCriticality criticality;
 Szt_ExtnTAIItemExtIEsCls extensionValue;
} SztProtExtnField_TAIItemExtIEs;

typedef struct s1apProtExtnCont_TAIItemExtIEs
{
 TknU16 noComp;
 SztProtExtnField_TAIItemExtIEs *member;
}SztProtExtnCont_TAIItemExtIEs;

typedef struct s1apTAIItem
{
 TknPres pres;
 SztTAI tAI;
 SztProtExtnCont_TAIItemExtIEs iE_Extns;
} SztTAIItem;

typedef struct s1ap_ValueTAIItemIEsCls{
 union {
  SztTAIItem sztTAIItem;
 } u;
} Szt_ValueTAIItemIEsCls;
typedef struct s1apProtIE_Field_TAIItemIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueTAIItemIEsCls value;
} SztProtIE_Field_TAIItemIEs;


typedef SztProtIE_Field_TAIItemIEs SztProtIE_SingleCont_TAIItemIEs;
typedef struct s1apTAILst
{
 TknU16 noComp;
 SztProtIE_SingleCont_TAIItemIEs *member;
}SztTAILst;

typedef struct s1ap_ValuePagIEsCls{
 union {
  SztUEIdentityIdxValue sztUEIdentityIdxValue;
  SztUEPagID sztUEPagID;
  SztPagDRX sztPagDRX;
  SztCNDomain sztCNDomain;
  SztTAILst sztTAILst;
  SztCSG_IdLst sztCSG_IdLst;
  SztPagPriority sztPagPriority;
 } u;
} Szt_ValuePagIEsCls;
typedef struct s1apProtIE_Field_PagIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValuePagIEsCls value;
} SztProtIE_Field_PagIEs;

typedef struct s1apProtIE_Cont_PagIEs
{
 TknU16 noComp;
 SztProtIE_Field_PagIEs *member;
}SztProtIE_Cont_PagIEs;

typedef struct s1apPag
{
 TknPres pres;
 SztProtIE_Cont_PagIEs protocolIEs;
} SztPag;

typedef struct s1ap_ValueUECntxtRlsRqst_IEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCause sztCause;
  SztGWCntxtRlsInd sztGWCntxtRlsInd;
 } u;
} Szt_ValueUECntxtRlsRqst_IEsCls;
typedef struct s1apProtIE_Field_UECntxtRlsRqst_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUECntxtRlsRqst_IEsCls value;
} SztProtIE_Field_UECntxtRlsRqst_IEs;

typedef struct s1apProtIE_Cont_UECntxtRlsRqst_IEs
{
 TknU16 noComp;
 SztProtIE_Field_UECntxtRlsRqst_IEs *member;
}SztProtIE_Cont_UECntxtRlsRqst_IEs;

typedef struct s1apUECntxtRlsRqst
{
 TknPres pres;
 SztProtIE_Cont_UECntxtRlsRqst_IEs protocolIEs;
} SztUECntxtRlsRqst;

typedef struct s1ap_ValueUECntxtRlsCmmd_IEsCls{
 union {
  SztUE_S1AP_IDs sztUE_S1AP_IDs;
  SztCause sztCause;
 } u;
} Szt_ValueUECntxtRlsCmmd_IEsCls;
typedef struct s1apProtIE_Field_UECntxtRlsCmmd_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUECntxtRlsCmmd_IEsCls value;
} SztProtIE_Field_UECntxtRlsCmmd_IEs;

typedef struct s1apProtIE_Cont_UECntxtRlsCmmd_IEs
{
 TknU16 noComp;
 SztProtIE_Field_UECntxtRlsCmmd_IEs *member;
}SztProtIE_Cont_UECntxtRlsCmmd_IEs;

typedef struct s1apUECntxtRlsCmmd
{
 TknPres pres;
 SztProtIE_Cont_UECntxtRlsCmmd_IEs protocolIEs;
} SztUECntxtRlsCmmd;

typedef struct s1ap_ValueUECntxtRlsComplete_IEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueUECntxtRlsComplete_IEsCls;
typedef struct s1apProtIE_Field_UECntxtRlsComplete_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUECntxtRlsComplete_IEsCls value;
} SztProtIE_Field_UECntxtRlsComplete_IEs;

typedef struct s1apProtIE_Cont_UECntxtRlsComplete_IEs
{
 TknU16 noComp;
 SztProtIE_Field_UECntxtRlsComplete_IEs *member;
}SztProtIE_Cont_UECntxtRlsComplete_IEs;

typedef struct s1apUECntxtRlsComplete
{
 TknPres pres;
 SztProtIE_Cont_UECntxtRlsComplete_IEs protocolIEs;
} SztUECntxtRlsComplete;

typedef struct s1ap_ValueUECntxtModificationRqstIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztSecurKey sztSecurKey;
  SztSubscriberProfileIDforRFP sztSubscriberProfileIDforRFP;
  SztUEAggMaxBitrate sztUEAggMaxBitrate;
  SztCSFallbackIndicator sztCSFallbackIndicator;
  SztUESecurCapabilities sztUESecurCapabilities;
  SztCSGMembershipStatus sztCSGMembershipStatus;
  SztLAI sztLAI;
 } u;
} Szt_ValueUECntxtModificationRqstIEsCls;
typedef struct s1apProtIE_Field_UECntxtModificationRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUECntxtModificationRqstIEsCls value;
} SztProtIE_Field_UECntxtModificationRqstIEs;

typedef struct s1apProtIE_Cont_UECntxtModificationRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_UECntxtModificationRqstIEs *member;
}SztProtIE_Cont_UECntxtModificationRqstIEs;

typedef struct s1apUECntxtModificationRqst
{
 TknPres pres;
 SztProtIE_Cont_UECntxtModificationRqstIEs protocolIEs;
} SztUECntxtModificationRqst;

typedef struct s1ap_ValueUECntxtModificationRespIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueUECntxtModificationRespIEsCls;
typedef struct s1apProtIE_Field_UECntxtModificationRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUECntxtModificationRespIEsCls value;
} SztProtIE_Field_UECntxtModificationRespIEs;

typedef struct s1apProtIE_Cont_UECntxtModificationRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_UECntxtModificationRespIEs *member;
}SztProtIE_Cont_UECntxtModificationRespIEs;

typedef struct s1apUECntxtModificationResp
{
 TknPres pres;
 SztProtIE_Cont_UECntxtModificationRespIEs protocolIEs;
} SztUECntxtModificationResp;

typedef struct s1ap_ValueUECntxtModificationFailIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCause sztCause;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueUECntxtModificationFailIEsCls;
typedef struct s1apProtIE_Field_UECntxtModificationFailIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUECntxtModificationFailIEsCls value;
} SztProtIE_Field_UECntxtModificationFailIEs;

typedef struct s1apProtIE_Cont_UECntxtModificationFailIEs
{
 TknU16 noComp;
 SztProtIE_Field_UECntxtModificationFailIEs *member;
}SztProtIE_Cont_UECntxtModificationFailIEs;

typedef struct s1apUECntxtModificationFail
{
 TknPres pres;
 SztProtIE_Cont_UECntxtModificationFailIEs protocolIEs;
} SztUECntxtModificationFail;

typedef struct s1ap_ValueUERadioCapbltyMatchRqstIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztUERadioCapblty sztUERadioCapblty;
 } u;
} Szt_ValueUERadioCapbltyMatchRqstIEsCls;
typedef struct s1apProtIE_Field_UERadioCapbltyMatchRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUERadioCapbltyMatchRqstIEsCls value;
} SztProtIE_Field_UERadioCapbltyMatchRqstIEs;

typedef struct s1apProtIE_Cont_UERadioCapbltyMatchRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_UERadioCapbltyMatchRqstIEs *member;
}SztProtIE_Cont_UERadioCapbltyMatchRqstIEs;

typedef struct s1apUERadioCapbltyMatchRqst
{
 TknPres pres;
 SztProtIE_Cont_UERadioCapbltyMatchRqstIEs protocolIEs;
} SztUERadioCapbltyMatchRqst;

typedef struct s1ap_ValueUERadioCapbltyMatchRespIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztVoiceSupportMatchIndicator sztVoiceSupportMatchIndicator;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueUERadioCapbltyMatchRespIEsCls;
typedef struct s1apProtIE_Field_UERadioCapbltyMatchRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUERadioCapbltyMatchRespIEsCls value;
} SztProtIE_Field_UERadioCapbltyMatchRespIEs;

typedef struct s1apProtIE_Cont_UERadioCapbltyMatchRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_UERadioCapbltyMatchRespIEs *member;
}SztProtIE_Cont_UERadioCapbltyMatchRespIEs;

typedef struct s1apUERadioCapbltyMatchResp
{
 TknPres pres;
 SztProtIE_Cont_UERadioCapbltyMatchRespIEs protocolIEs;
} SztUERadioCapbltyMatchResp;

typedef struct s1ap_ValueDlnkNASTport_IEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztNAS_PDU sztNAS_PDU;
  SztHovrRestrnLst sztHovrRestrnLst;
  SztSubscriberProfileIDforRFP sztSubscriberProfileIDforRFP;
 } u;
} Szt_ValueDlnkNASTport_IEsCls;
typedef struct s1apProtIE_Field_DlnkNASTport_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueDlnkNASTport_IEsCls value;
} SztProtIE_Field_DlnkNASTport_IEs;

typedef struct s1apProtIE_Cont_DlnkNASTport_IEs
{
 TknU16 noComp;
 SztProtIE_Field_DlnkNASTport_IEs *member;
}SztProtIE_Cont_DlnkNASTport_IEs;

typedef struct s1apDlnkNASTport
{
 TknPres pres;
 SztProtIE_Cont_DlnkNASTport_IEs protocolIEs;
} SztDlnkNASTport;

typedef struct s1ap_ValueInitUEMsg_IEsCls{
 union {
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztNAS_PDU sztNAS_PDU;
  SztTAI sztTAI;
  SztEUTRAN_CGI sztEUTRAN_CGI;
  SztRRC_Establishment_Cause sztRRC_Establishment_Cause;
  SztS_TMSI sztS_TMSI;
  SztCSG_Id sztCSG_Id;
  SztGUMMEI sztGUMMEI;
  SztCellAccessMode sztCellAccessMode;
  SztTportLyrAddr sztTportLyrAddr;
  SztRelayNode_Indicator sztRelayNode_Indicator;
  SztGUMMEITyp sztGUMMEITyp;
  SztTunnelInform sztTunnelInform;
 } u;
} Szt_ValueInitUEMsg_IEsCls;
typedef struct s1apProtIE_Field_InitUEMsg_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueInitUEMsg_IEsCls value;
} SztProtIE_Field_InitUEMsg_IEs;

typedef struct s1apProtIE_Cont_InitUEMsg_IEs
{
 TknU16 noComp;
 SztProtIE_Field_InitUEMsg_IEs *member;
}SztProtIE_Cont_InitUEMsg_IEs;

typedef struct s1apInitUEMsg
{
 TknPres pres;
 SztProtIE_Cont_InitUEMsg_IEs protocolIEs;
} SztInitUEMsg;

typedef struct s1ap_ValueUlnkNASTport_IEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztNAS_PDU sztNAS_PDU;
  SztEUTRAN_CGI sztEUTRAN_CGI;
  SztTAI sztTAI;
  SztTportLyrAddr sztTportLyrAddr;
 } u;
} Szt_ValueUlnkNASTport_IEsCls;
typedef struct s1apProtIE_Field_UlnkNASTport_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUlnkNASTport_IEsCls value;
} SztProtIE_Field_UlnkNASTport_IEs;

typedef struct s1apProtIE_Cont_UlnkNASTport_IEs
{
 TknU16 noComp;
 SztProtIE_Field_UlnkNASTport_IEs *member;
}SztProtIE_Cont_UlnkNASTport_IEs;

typedef struct s1apUlnkNASTport
{
 TknPres pres;
 SztProtIE_Cont_UlnkNASTport_IEs protocolIEs;
} SztUlnkNASTport;

typedef struct s1ap_ValueNASNonDlvryInd_IEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztNAS_PDU sztNAS_PDU;
  SztCause sztCause;
 } u;
} Szt_ValueNASNonDlvryInd_IEsCls;
typedef struct s1apProtIE_Field_NASNonDlvryInd_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueNASNonDlvryInd_IEsCls value;
} SztProtIE_Field_NASNonDlvryInd_IEs;

typedef struct s1apProtIE_Cont_NASNonDlvryInd_IEs
{
 TknU16 noComp;
 SztProtIE_Field_NASNonDlvryInd_IEs *member;
}SztProtIE_Cont_NASNonDlvryInd_IEs;

typedef struct s1apNASNonDlvryInd
{
 TknPres pres;
 SztProtIE_Cont_NASNonDlvryInd_IEs protocolIEs;
} SztNASNonDlvryInd;


typedef enum enumSztResetAll
{
 SztResetAllreset_allEnum
} EnumSztResetAll;
typedef TknU32 SztResetAll;

typedef struct s1ap_ValueUE_assocLogS1_ConItemResCls{
 union {
  SztUE_assocLogS1_ConItem sztUE_assocLogS1_ConItem;
 } u;
} Szt_ValueUE_assocLogS1_ConItemResCls;
typedef struct s1apProtIE_Field_UE_assocLogS1_ConItemRes
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUE_assocLogS1_ConItemResCls value;
} SztProtIE_Field_UE_assocLogS1_ConItemRes;


typedef SztProtIE_Field_UE_assocLogS1_ConItemRes SztProtIE_SingleCont_UE_assocLogS1_ConItemRes;
typedef struct s1apUE_assocLogS1_ConLstRes
{
 TknU16 noComp;
 SztProtIE_SingleCont_UE_assocLogS1_ConItemRes *member;
}SztUE_assocLogS1_ConLstRes;

typedef struct s1apResetTyp
{
 TknU8 choice;
 union {
  SztResetAll s1_Intf;
  SztUE_assocLogS1_ConLstRes partOfS1_Intf;
 } val;
} SztResetTyp;

typedef struct s1ap_ValueResetIEsCls{
 union {
  SztCause sztCause;
  SztResetTyp sztResetTyp;
 } u;
} Szt_ValueResetIEsCls;
typedef struct s1apProtIE_Field_ResetIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueResetIEsCls value;
} SztProtIE_Field_ResetIEs;

typedef struct s1apProtIE_Cont_ResetIEs
{
 TknU16 noComp;
 SztProtIE_Field_ResetIEs *member;
}SztProtIE_Cont_ResetIEs;

typedef struct s1apReset
{
 TknPres pres;
 SztProtIE_Cont_ResetIEs protocolIEs;
} SztReset;

typedef struct s1ap_ValueUE_assocLogS1_ConItemResAckCls{
 union {
  SztUE_assocLogS1_ConItem sztUE_assocLogS1_ConItem;
 } u;
} Szt_ValueUE_assocLogS1_ConItemResAckCls;
typedef struct s1apProtIE_Field_UE_assocLogS1_ConItemResAck
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUE_assocLogS1_ConItemResAckCls value;
} SztProtIE_Field_UE_assocLogS1_ConItemResAck;


typedef SztProtIE_Field_UE_assocLogS1_ConItemResAck SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck;
typedef struct s1apUE_assocLogS1_ConLstResAck
{
 TknU16 noComp;
 SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck *member;
}SztUE_assocLogS1_ConLstResAck;

typedef struct s1ap_ValueResetAckgIEsCls{
 union {
  SztUE_assocLogS1_ConLstResAck sztUE_assocLogS1_ConLstResAck;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueResetAckgIEsCls;
typedef struct s1apProtIE_Field_ResetAckgIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueResetAckgIEsCls value;
} SztProtIE_Field_ResetAckgIEs;

typedef struct s1apProtIE_Cont_ResetAckgIEs
{
 TknU16 noComp;
 SztProtIE_Field_ResetAckgIEs *member;
}SztProtIE_Cont_ResetAckgIEs;

typedef struct s1apResetAckg
{
 TknPres pres;
 SztProtIE_Cont_ResetAckgIEs protocolIEs;
} SztResetAckg;

typedef struct s1ap_ValueErrIndIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCause sztCause;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueErrIndIEsCls;
typedef struct s1apProtIE_Field_ErrIndIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueErrIndIEsCls value;
} SztProtIE_Field_ErrIndIEs;

typedef struct s1apProtIE_Cont_ErrIndIEs
{
 TknU16 noComp;
 SztProtIE_Field_ErrIndIEs *member;
}SztProtIE_Cont_ErrIndIEs;

typedef struct s1apErrInd
{
 TknPres pres;
 SztProtIE_Cont_ErrIndIEs protocolIEs;
} SztErrInd;

typedef struct s1ap_ValueS1SetupRqstIEsCls{
 union {
  SztGlobal_ENB_ID sztGlobal_ENB_ID;
  SztENBname sztENBname;
  SztSuppTAs sztSuppTAs;
  SztPagDRX sztPagDRX;
  SztCSG_IdLst sztCSG_IdLst;
 } u;
} Szt_ValueS1SetupRqstIEsCls;
typedef struct s1apProtIE_Field_S1SetupRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueS1SetupRqstIEsCls value;
} SztProtIE_Field_S1SetupRqstIEs;

typedef struct s1apProtIE_Cont_S1SetupRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_S1SetupRqstIEs *member;
}SztProtIE_Cont_S1SetupRqstIEs;

typedef struct s1apS1SetupRqst
{
 TknPres pres;
 SztProtIE_Cont_S1SetupRqstIEs protocolIEs;
} SztS1SetupRqst;

typedef struct s1ap_ValueS1SetupRespIEsCls{
 union {
  SztMMEname sztMMEname;
  SztSrvdGUMMEIs sztSrvdGUMMEIs;
  SztRelativeMMECapacity sztRelativeMMECapacity;
  SztMMERelaySupportIndicator sztMMERelaySupportIndicator;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueS1SetupRespIEsCls;
typedef struct s1apProtIE_Field_S1SetupRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueS1SetupRespIEsCls value;
} SztProtIE_Field_S1SetupRespIEs;

typedef struct s1apProtIE_Cont_S1SetupRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_S1SetupRespIEs *member;
}SztProtIE_Cont_S1SetupRespIEs;

typedef struct s1apS1SetupResp
{
 TknPres pres;
 SztProtIE_Cont_S1SetupRespIEs protocolIEs;
} SztS1SetupResp;

typedef struct s1ap_ValueS1SetupFailIEsCls{
 union {
  SztCause sztCause;
  SztTimeToWait sztTimeToWait;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueS1SetupFailIEsCls;
typedef struct s1apProtIE_Field_S1SetupFailIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueS1SetupFailIEsCls value;
} SztProtIE_Field_S1SetupFailIEs;

typedef struct s1apProtIE_Cont_S1SetupFailIEs
{
 TknU16 noComp;
 SztProtIE_Field_S1SetupFailIEs *member;
}SztProtIE_Cont_S1SetupFailIEs;

typedef struct s1apS1SetupFail
{
 TknPres pres;
 SztProtIE_Cont_S1SetupFailIEs protocolIEs;
} SztS1SetupFail;

typedef struct s1ap_ValueENBConfigUpdIEsCls{
 union {
  SztENBname sztENBname;
  SztSuppTAs sztSuppTAs;
  SztCSG_IdLst sztCSG_IdLst;
  SztPagDRX sztPagDRX;
 } u;
} Szt_ValueENBConfigUpdIEsCls;
typedef struct s1apProtIE_Field_ENBConfigUpdIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueENBConfigUpdIEsCls value;
} SztProtIE_Field_ENBConfigUpdIEs;

typedef struct s1apProtIE_Cont_ENBConfigUpdIEs
{
 TknU16 noComp;
 SztProtIE_Field_ENBConfigUpdIEs *member;
}SztProtIE_Cont_ENBConfigUpdIEs;

typedef struct s1apENBConfigUpd
{
 TknPres pres;
 SztProtIE_Cont_ENBConfigUpdIEs protocolIEs;
} SztENBConfigUpd;

typedef struct s1ap_ValueENBConfigUpdAckgIEsCls{
 union {
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueENBConfigUpdAckgIEsCls;
typedef struct s1apProtIE_Field_ENBConfigUpdAckgIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueENBConfigUpdAckgIEsCls value;
} SztProtIE_Field_ENBConfigUpdAckgIEs;

typedef struct s1apProtIE_Cont_ENBConfigUpdAckgIEs
{
 TknU16 noComp;
 SztProtIE_Field_ENBConfigUpdAckgIEs *member;
}SztProtIE_Cont_ENBConfigUpdAckgIEs;

typedef struct s1apENBConfigUpdAckg
{
 TknPres pres;
 SztProtIE_Cont_ENBConfigUpdAckgIEs protocolIEs;
} SztENBConfigUpdAckg;

typedef struct s1ap_ValueENBConfigUpdFailIEsCls{
 union {
  SztCause sztCause;
  SztTimeToWait sztTimeToWait;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueENBConfigUpdFailIEsCls;
typedef struct s1apProtIE_Field_ENBConfigUpdFailIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueENBConfigUpdFailIEsCls value;
} SztProtIE_Field_ENBConfigUpdFailIEs;

typedef struct s1apProtIE_Cont_ENBConfigUpdFailIEs
{
 TknU16 noComp;
 SztProtIE_Field_ENBConfigUpdFailIEs *member;
}SztProtIE_Cont_ENBConfigUpdFailIEs;

typedef struct s1apENBConfigUpdFail
{
 TknPres pres;
 SztProtIE_Cont_ENBConfigUpdFailIEs protocolIEs;
} SztENBConfigUpdFail;

typedef struct s1ap_ValueMMEConfigUpdIEsCls{
 union {
  SztMMEname sztMMEname;
  SztSrvdGUMMEIs sztSrvdGUMMEIs;
  SztRelativeMMECapacity sztRelativeMMECapacity;
 } u;
} Szt_ValueMMEConfigUpdIEsCls;
typedef struct s1apProtIE_Field_MMEConfigUpdIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueMMEConfigUpdIEsCls value;
} SztProtIE_Field_MMEConfigUpdIEs;

typedef struct s1apProtIE_Cont_MMEConfigUpdIEs
{
 TknU16 noComp;
 SztProtIE_Field_MMEConfigUpdIEs *member;
}SztProtIE_Cont_MMEConfigUpdIEs;

typedef struct s1apMMEConfigUpd
{
 TknPres pres;
 SztProtIE_Cont_MMEConfigUpdIEs protocolIEs;
} SztMMEConfigUpd;

typedef struct s1ap_ValueMMEConfigUpdAckgIEsCls{
 union {
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueMMEConfigUpdAckgIEsCls;
typedef struct s1apProtIE_Field_MMEConfigUpdAckgIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueMMEConfigUpdAckgIEsCls value;
} SztProtIE_Field_MMEConfigUpdAckgIEs;

typedef struct s1apProtIE_Cont_MMEConfigUpdAckgIEs
{
 TknU16 noComp;
 SztProtIE_Field_MMEConfigUpdAckgIEs *member;
}SztProtIE_Cont_MMEConfigUpdAckgIEs;

typedef struct s1apMMEConfigUpdAckg
{
 TknPres pres;
 SztProtIE_Cont_MMEConfigUpdAckgIEs protocolIEs;
} SztMMEConfigUpdAckg;

typedef struct s1ap_ValueMMEConfigUpdFailIEsCls{
 union {
  SztCause sztCause;
  SztTimeToWait sztTimeToWait;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueMMEConfigUpdFailIEsCls;
typedef struct s1apProtIE_Field_MMEConfigUpdFailIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueMMEConfigUpdFailIEsCls value;
} SztProtIE_Field_MMEConfigUpdFailIEs;

typedef struct s1apProtIE_Cont_MMEConfigUpdFailIEs
{
 TknU16 noComp;
 SztProtIE_Field_MMEConfigUpdFailIEs *member;
}SztProtIE_Cont_MMEConfigUpdFailIEs;

typedef struct s1apMMEConfigUpdFail
{
 TknPres pres;
 SztProtIE_Cont_MMEConfigUpdFailIEs protocolIEs;
} SztMMEConfigUpdFail;

typedef struct s1ap_ValueDlnkS1cdma2000tunnelingIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_RABSubjtoDataFwdingLst sztE_RABSubjtoDataFwdingLst;
  SztCdma2000HOStatus sztCdma2000HOStatus;
  SztCdma2000RATTyp sztCdma2000RATTyp;
  SztCdma2000PDU sztCdma2000PDU;
 } u;
} Szt_ValueDlnkS1cdma2000tunnelingIEsCls;
typedef struct s1apProtIE_Field_DlnkS1cdma2000tunnelingIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueDlnkS1cdma2000tunnelingIEsCls value;
} SztProtIE_Field_DlnkS1cdma2000tunnelingIEs;

typedef struct s1apProtIE_Cont_DlnkS1cdma2000tunnelingIEs
{
 TknU16 noComp;
 SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *member;
}SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs;

typedef struct s1apDlnkS1cdma2000tunneling
{
 TknPres pres;
 SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs protocolIEs;
} SztDlnkS1cdma2000tunneling;

typedef struct s1ap_ValueUlnkS1cdma2000tunnelingIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCdma2000RATTyp sztCdma2000RATTyp;
  SztCdma2000SectorID sztCdma2000SectorID;
  SztCdma2000HOReqdInd sztCdma2000HOReqdInd;
  SztCdma2000OneXSRVCCInfo sztCdma2000OneXSRVCCInfo;
  SztCdma2000OneXRAND sztCdma2000OneXRAND;
  SztCdma2000PDU sztCdma2000PDU;
  SztEUTRANRoundTripDelayEstimationInfo sztEUTRANRoundTripDelayEstimationInfo;
 } u;
} Szt_ValueUlnkS1cdma2000tunnelingIEsCls;
typedef struct s1apProtIE_Field_UlnkS1cdma2000tunnelingIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUlnkS1cdma2000tunnelingIEsCls value;
} SztProtIE_Field_UlnkS1cdma2000tunnelingIEs;

typedef struct s1apProtIE_Cont_UlnkS1cdma2000tunnelingIEs
{
 TknU16 noComp;
 SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *member;
}SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs;

typedef struct s1apUlnkS1cdma2000tunneling
{
 TknPres pres;
 SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs protocolIEs;
} SztUlnkS1cdma2000tunneling;

typedef struct s1ap_ValueUECapbltyInfoIndIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztUERadioCapblty sztUERadioCapblty;
 } u;
} Szt_ValueUECapbltyInfoIndIEsCls;
typedef struct s1apProtIE_Field_UECapbltyInfoIndIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUECapbltyInfoIndIEsCls value;
} SztProtIE_Field_UECapbltyInfoIndIEs;

typedef struct s1apProtIE_Cont_UECapbltyInfoIndIEs
{
 TknU16 noComp;
 SztProtIE_Field_UECapbltyInfoIndIEs *member;
}SztProtIE_Cont_UECapbltyInfoIndIEs;

typedef struct s1apUECapbltyInfoInd
{
 TknPres pres;
 SztProtIE_Cont_UECapbltyInfoIndIEs protocolIEs;
} SztUECapbltyInfoInd;

typedef struct s1ap_ValueENBStatusTfrIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztENB_StatusTfr_TprntCont sztENB_StatusTfr_TprntCont;
 } u;
} Szt_ValueENBStatusTfrIEsCls;
typedef struct s1apProtIE_Field_ENBStatusTfrIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueENBStatusTfrIEsCls value;
} SztProtIE_Field_ENBStatusTfrIEs;

typedef struct s1apProtIE_Cont_ENBStatusTfrIEs
{
 TknU16 noComp;
 SztProtIE_Field_ENBStatusTfrIEs *member;
}SztProtIE_Cont_ENBStatusTfrIEs;

typedef struct s1apENBStatusTfr
{
 TknPres pres;
 SztProtIE_Cont_ENBStatusTfrIEs protocolIEs;
} SztENBStatusTfr;

typedef struct s1ap_ValueMMEStatusTfrIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztENB_StatusTfr_TprntCont sztENB_StatusTfr_TprntCont;
 } u;
} Szt_ValueMMEStatusTfrIEsCls;
typedef struct s1apProtIE_Field_MMEStatusTfrIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueMMEStatusTfrIEsCls value;
} SztProtIE_Field_MMEStatusTfrIEs;

typedef struct s1apProtIE_Cont_MMEStatusTfrIEs
{
 TknU16 noComp;
 SztProtIE_Field_MMEStatusTfrIEs *member;
}SztProtIE_Cont_MMEStatusTfrIEs;

typedef struct s1apMMEStatusTfr
{
 TknPres pres;
 SztProtIE_Cont_MMEStatusTfrIEs protocolIEs;
} SztMMEStatusTfr;

typedef struct s1ap_ValueTraceStartIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztTraceActvn sztTraceActvn;
 } u;
} Szt_ValueTraceStartIEsCls;
typedef struct s1apProtIE_Field_TraceStartIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueTraceStartIEsCls value;
} SztProtIE_Field_TraceStartIEs;

typedef struct s1apProtIE_Cont_TraceStartIEs
{
 TknU16 noComp;
 SztProtIE_Field_TraceStartIEs *member;
}SztProtIE_Cont_TraceStartIEs;

typedef struct s1apTraceStart
{
 TknPres pres;
 SztProtIE_Cont_TraceStartIEs protocolIEs;
} SztTraceStart;

typedef struct s1ap_ValueTraceFailIndIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_UTRAN_Trace_ID sztE_UTRAN_Trace_ID;
  SztCause sztCause;
 } u;
} Szt_ValueTraceFailIndIEsCls;
typedef struct s1apProtIE_Field_TraceFailIndIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueTraceFailIndIEsCls value;
} SztProtIE_Field_TraceFailIndIEs;

typedef struct s1apProtIE_Cont_TraceFailIndIEs
{
 TknU16 noComp;
 SztProtIE_Field_TraceFailIndIEs *member;
}SztProtIE_Cont_TraceFailIndIEs;

typedef struct s1apTraceFailInd
{
 TknPres pres;
 SztProtIE_Cont_TraceFailIndIEs protocolIEs;
} SztTraceFailInd;

typedef struct s1ap_ValueDeactvTraceIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_UTRAN_Trace_ID sztE_UTRAN_Trace_ID;
 } u;
} Szt_ValueDeactvTraceIEsCls;
typedef struct s1apProtIE_Field_DeactvTraceIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueDeactvTraceIEsCls value;
} SztProtIE_Field_DeactvTraceIEs;

typedef struct s1apProtIE_Cont_DeactvTraceIEs
{
 TknU16 noComp;
 SztProtIE_Field_DeactvTraceIEs *member;
}SztProtIE_Cont_DeactvTraceIEs;

typedef struct s1apDeactvTrace
{
 TknPres pres;
 SztProtIE_Cont_DeactvTraceIEs protocolIEs;
} SztDeactvTrace;

typedef struct s1ap_ValueCellTrafficTraceIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztE_UTRAN_Trace_ID sztE_UTRAN_Trace_ID;
  SztEUTRAN_CGI sztEUTRAN_CGI;
  SztTportLyrAddr sztTportLyrAddr;
  SztPrivacyIndicator sztPrivacyIndicator;
 } u;
} Szt_ValueCellTrafficTraceIEsCls;
typedef struct s1apProtIE_Field_CellTrafficTraceIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueCellTrafficTraceIEsCls value;
} SztProtIE_Field_CellTrafficTraceIEs;

typedef struct s1apProtIE_Cont_CellTrafficTraceIEs
{
 TknU16 noComp;
 SztProtIE_Field_CellTrafficTraceIEs *member;
}SztProtIE_Cont_CellTrafficTraceIEs;

typedef struct s1apCellTrafficTrace
{
 TknPres pres;
 SztProtIE_Cont_CellTrafficTraceIEs protocolIEs;
} SztCellTrafficTrace;

typedef struct s1ap_ValueLocRprtngCntrlIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztRqstTyp sztRqstTyp;
 } u;
} Szt_ValueLocRprtngCntrlIEsCls;
typedef struct s1apProtIE_Field_LocRprtngCntrlIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueLocRprtngCntrlIEsCls value;
} SztProtIE_Field_LocRprtngCntrlIEs;

typedef struct s1apProtIE_Cont_LocRprtngCntrlIEs
{
 TknU16 noComp;
 SztProtIE_Field_LocRprtngCntrlIEs *member;
}SztProtIE_Cont_LocRprtngCntrlIEs;

typedef struct s1apLocRprtngCntrl
{
 TknPres pres;
 SztProtIE_Cont_LocRprtngCntrlIEs protocolIEs;
} SztLocRprtngCntrl;

typedef struct s1ap_ValueLocRprtngFailIndIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztCause sztCause;
 } u;
} Szt_ValueLocRprtngFailIndIEsCls;
typedef struct s1apProtIE_Field_LocRprtngFailIndIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueLocRprtngFailIndIEsCls value;
} SztProtIE_Field_LocRprtngFailIndIEs;

typedef struct s1apProtIE_Cont_LocRprtngFailIndIEs
{
 TknU16 noComp;
 SztProtIE_Field_LocRprtngFailIndIEs *member;
}SztProtIE_Cont_LocRprtngFailIndIEs;

typedef struct s1apLocRprtngFailInd
{
 TknPres pres;
 SztProtIE_Cont_LocRprtngFailIndIEs protocolIEs;
} SztLocRprtngFailInd;

typedef struct s1ap_ValueLocReportIEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztEUTRAN_CGI sztEUTRAN_CGI;
  SztTAI sztTAI;
  SztRqstTyp sztRqstTyp;
 } u;
} Szt_ValueLocReportIEsCls;
typedef struct s1apProtIE_Field_LocReportIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueLocReportIEsCls value;
} SztProtIE_Field_LocReportIEs;

typedef struct s1apProtIE_Cont_LocReportIEs
{
 TknU16 noComp;
 SztProtIE_Field_LocReportIEs *member;
}SztProtIE_Cont_LocReportIEs;

typedef struct s1apLocReport
{
 TknPres pres;
 SztProtIE_Cont_LocReportIEs protocolIEs;
} SztLocReport;

typedef struct s1ap_ValueOverloadStartIEsCls{
 union {
  SztOverloadResp sztOverloadResp;
  SztGUMMEILst sztGUMMEILst;
  SztTrafficLoadReductionInd sztTrafficLoadReductionInd;
 } u;
} Szt_ValueOverloadStartIEsCls;
typedef struct s1apProtIE_Field_OverloadStartIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueOverloadStartIEsCls value;
} SztProtIE_Field_OverloadStartIEs;

typedef struct s1apProtIE_Cont_OverloadStartIEs
{
 TknU16 noComp;
 SztProtIE_Field_OverloadStartIEs *member;
}SztProtIE_Cont_OverloadStartIEs;

typedef struct s1apOverloadStart
{
 TknPres pres;
 SztProtIE_Cont_OverloadStartIEs protocolIEs;
} SztOverloadStart;

typedef struct s1ap_ValueOverloadStopIEsCls{
 union {
  SztGUMMEILst sztGUMMEILst;
 } u;
} Szt_ValueOverloadStopIEsCls;
typedef struct s1apProtIE_Field_OverloadStopIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueOverloadStopIEsCls value;
} SztProtIE_Field_OverloadStopIEs;

typedef struct s1apProtIE_Cont_OverloadStopIEs
{
 TknU16 noComp;
 SztProtIE_Field_OverloadStopIEs *member;
}SztProtIE_Cont_OverloadStopIEs;

typedef struct s1apOverloadStop
{
 TknPres pres;
 SztProtIE_Cont_OverloadStopIEs protocolIEs;
} SztOverloadStop;

typedef struct s1ap_ValueWriteReplaceWarningRqstIEsCls{
 union {
  SztMsgIdentifier sztMsgIdentifier;
  SztSerialNumber sztSerialNumber;
  SztWarningAreaLst sztWarningAreaLst;
  SztRepetitionPeriod sztRepetitionPeriod;
  SztExtendedRepetitionPeriod sztExtendedRepetitionPeriod;
  SztNumberofBroadcastRqst sztNumberofBroadcastRqst;
  SztWarningTyp sztWarningTyp;
  SztWarningSecurInfo sztWarningSecurInfo;
  SztDataCodingScheme sztDataCodingScheme;
  SztWarningMsgContents sztWarningMsgContents;
  SztConcurrentWarningMsgIndicator sztConcurrentWarningMsgIndicator;
 } u;
} Szt_ValueWriteReplaceWarningRqstIEsCls;
typedef struct s1apProtIE_Field_WriteReplaceWarningRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueWriteReplaceWarningRqstIEsCls value;
} SztProtIE_Field_WriteReplaceWarningRqstIEs;

typedef struct s1apProtIE_Cont_WriteReplaceWarningRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_WriteReplaceWarningRqstIEs *member;
}SztProtIE_Cont_WriteReplaceWarningRqstIEs;

typedef struct s1apWriteReplaceWarningRqst
{
 TknPres pres;
 SztProtIE_Cont_WriteReplaceWarningRqstIEs protocolIEs;
} SztWriteReplaceWarningRqst;

typedef struct s1ap_ValueWriteReplaceWarningRespIEsCls{
 union {
  SztMsgIdentifier sztMsgIdentifier;
  SztSerialNumber sztSerialNumber;
  SztBroadcastCompletedAreaLst sztBroadcastCompletedAreaLst;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueWriteReplaceWarningRespIEsCls;
typedef struct s1apProtIE_Field_WriteReplaceWarningRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueWriteReplaceWarningRespIEsCls value;
} SztProtIE_Field_WriteReplaceWarningRespIEs;

typedef struct s1apProtIE_Cont_WriteReplaceWarningRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_WriteReplaceWarningRespIEs *member;
}SztProtIE_Cont_WriteReplaceWarningRespIEs;

typedef struct s1apWriteReplaceWarningResp
{
 TknPres pres;
 SztProtIE_Cont_WriteReplaceWarningRespIEs protocolIEs;
} SztWriteReplaceWarningResp;

typedef struct s1apInter_SystemInformTfrTyp
{
 TknU8 choice;
 union {
  SztRIMTfr rIMTfr;
 } val;
} SztInter_SystemInformTfrTyp;

typedef struct s1ap_ValueENBDirectInformTfrIEsCls{
 union {
  SztInter_SystemInformTfrTyp sztInter_SystemInformTfrTyp;
 } u;
} Szt_ValueENBDirectInformTfrIEsCls;
typedef struct s1apProtIE_Field_ENBDirectInformTfrIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueENBDirectInformTfrIEsCls value;
} SztProtIE_Field_ENBDirectInformTfrIEs;

typedef struct s1apProtIE_Cont_ENBDirectInformTfrIEs
{
 TknU16 noComp;
 SztProtIE_Field_ENBDirectInformTfrIEs *member;
}SztProtIE_Cont_ENBDirectInformTfrIEs;

typedef struct s1apENBDirectInformTfr
{
 TknPres pres;
 SztProtIE_Cont_ENBDirectInformTfrIEs protocolIEs;
} SztENBDirectInformTfr;

typedef struct s1ap_ValueMMEDirectInformTfrIEsCls{
 union {
  SztInter_SystemInformTfrTyp sztInter_SystemInformTfrTyp;
 } u;
} Szt_ValueMMEDirectInformTfrIEsCls;
typedef struct s1apProtIE_Field_MMEDirectInformTfrIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueMMEDirectInformTfrIEsCls value;
} SztProtIE_Field_MMEDirectInformTfrIEs;

typedef struct s1apProtIE_Cont_MMEDirectInformTfrIEs
{
 TknU16 noComp;
 SztProtIE_Field_MMEDirectInformTfrIEs *member;
}SztProtIE_Cont_MMEDirectInformTfrIEs;

typedef struct s1apMMEDirectInformTfr
{
 TknPres pres;
 SztProtIE_Cont_MMEDirectInformTfrIEs protocolIEs;
} SztMMEDirectInformTfr;

typedef struct s1ap_ValueENBConfigTfrIEsCls{
 union {
  SztSONConfigTfr sztSONConfigTfr;
 } u;
} Szt_ValueENBConfigTfrIEsCls;
typedef struct s1apProtIE_Field_ENBConfigTfrIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueENBConfigTfrIEsCls value;
} SztProtIE_Field_ENBConfigTfrIEs;

typedef struct s1apProtIE_Cont_ENBConfigTfrIEs
{
 TknU16 noComp;
 SztProtIE_Field_ENBConfigTfrIEs *member;
}SztProtIE_Cont_ENBConfigTfrIEs;

typedef struct s1apENBConfigTfr
{
 TknPres pres;
 SztProtIE_Cont_ENBConfigTfrIEs protocolIEs;
} SztENBConfigTfr;

typedef struct s1ap_ValueMMEConfigTfrIEsCls{
 union {
  SztSONConfigTfr sztSONConfigTfr;
 } u;
} Szt_ValueMMEConfigTfrIEsCls;
typedef struct s1apProtIE_Field_MMEConfigTfrIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueMMEConfigTfrIEsCls value;
} SztProtIE_Field_MMEConfigTfrIEs;

typedef struct s1apProtIE_Cont_MMEConfigTfrIEs
{
 TknU16 noComp;
 SztProtIE_Field_MMEConfigTfrIEs *member;
}SztProtIE_Cont_MMEConfigTfrIEs;

typedef struct s1apMMEConfigTfr
{
 TknPres pres;
 SztProtIE_Cont_MMEConfigTfrIEs protocolIEs;
} SztMMEConfigTfr;

typedef struct s1ap_ValuePrivMsgIEsCls{
 union {
  TknU8 unused;
 } u;
} Szt_ValuePrivMsgIEsCls;
typedef struct s1apPrivIE_Field_PrivMsgIEs
{
 TknPres pres;
 SztPrivIE_ID id;
 SztCriticality criticality;
 Szt_ValuePrivMsgIEsCls value;
} SztPrivIE_Field_PrivMsgIEs;

typedef struct s1apPrivIE_Cont_PrivMsgIEs
{
 TknU16 noComp;
 SztPrivIE_Field_PrivMsgIEs *member;
}SztPrivIE_Cont_PrivMsgIEs;

typedef struct s1apPrivMsg
{
 TknPres pres;
 SztPrivIE_Cont_PrivMsgIEs privateIEs;
} SztPrivMsg;

typedef struct s1ap_ValueKillRqstIEsCls{
 union {
  SztMsgIdentifier sztMsgIdentifier;
  SztSerialNumber sztSerialNumber;
  SztWarningAreaLst sztWarningAreaLst;
 } u;
} Szt_ValueKillRqstIEsCls;
typedef struct s1apProtIE_Field_KillRqstIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueKillRqstIEsCls value;
} SztProtIE_Field_KillRqstIEs;

typedef struct s1apProtIE_Cont_KillRqstIEs
{
 TknU16 noComp;
 SztProtIE_Field_KillRqstIEs *member;
}SztProtIE_Cont_KillRqstIEs;

typedef struct s1apKillRqst
{
 TknPres pres;
 SztProtIE_Cont_KillRqstIEs protocolIEs;
} SztKillRqst;

typedef struct s1ap_ValueKillRespIEsCls{
 union {
  SztMsgIdentifier sztMsgIdentifier;
  SztSerialNumber sztSerialNumber;
  SztBroadcastCancelledAreaLst sztBroadcastCancelledAreaLst;
  SztCriticalityDiag sztCriticalityDiag;
 } u;
} Szt_ValueKillRespIEsCls;
typedef struct s1apProtIE_Field_KillRespIEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueKillRespIEsCls value;
} SztProtIE_Field_KillRespIEs;

typedef struct s1apProtIE_Cont_KillRespIEs
{
 TknU16 noComp;
 SztProtIE_Field_KillRespIEs *member;
}SztProtIE_Cont_KillRespIEs;

typedef struct s1apKillResp
{
 TknPres pres;
 SztProtIE_Cont_KillRespIEs protocolIEs;
} SztKillResp;

typedef struct s1ap_ValueDlnkUEAssociatedLPPaTport_IEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztRouting_ID sztRouting_ID;
  SztLPPa_PDU sztLPPa_PDU;
 } u;
} Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls;
typedef struct s1apProtIE_Field_DlnkUEAssociatedLPPaTport_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls value;
} SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs;

typedef struct s1apProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs
{
 TknU16 noComp;
 SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *member;
}SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs;

typedef struct s1apDlnkUEAssociatedLPPaTport
{
 TknPres pres;
 SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs protocolIEs;
} SztDlnkUEAssociatedLPPaTport;

typedef struct s1ap_ValueUlnkUEAssociatedLPPaTport_IEsCls{
 union {
  SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
  SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
  SztRouting_ID sztRouting_ID;
  SztLPPa_PDU sztLPPa_PDU;
 } u;
} Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls;
typedef struct s1apProtIE_Field_UlnkUEAssociatedLPPaTport_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls value;
} SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs;

typedef struct s1apProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs
{
 TknU16 noComp;
 SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *member;
}SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs;

typedef struct s1apUlnkUEAssociatedLPPaTport
{
 TknPres pres;
 SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs protocolIEs;
} SztUlnkUEAssociatedLPPaTport;

typedef struct s1ap_ValueDlnkNonUEAssociatedLPPaTport_IEsCls{
 union {
  SztRouting_ID sztRouting_ID;
  SztLPPa_PDU sztLPPa_PDU;
 } u;
} Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls;
typedef struct s1apProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls value;
} SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs;

typedef struct s1apProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs
{
 TknU16 noComp;
 SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *member;
}SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs;

typedef struct s1apDlnkNonUEAssociatedLPPaTport
{
 TknPres pres;
 SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs protocolIEs;
} SztDlnkNonUEAssociatedLPPaTport;

typedef struct s1ap_ValueUlnkNonUEAssociatedLPPaTport_IEsCls{
 union {
  SztRouting_ID sztRouting_ID;
  SztLPPa_PDU sztLPPa_PDU;
 } u;
} Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls;
typedef struct s1apProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs
{
 TknPres pres;
 SztProtIE_ID id;
 SztCriticality criticality;
 Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls value;
} SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs;

typedef struct s1apProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs
{
 TknU16 noComp;
 SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *member;
}SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs;

typedef struct s1apUlnkNonUEAssociatedLPPaTport
{
 TknPres pres;
 SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs protocolIEs;
} SztUlnkNonUEAssociatedLPPaTport;

typedef struct s1ap_InitiatingMsgCls{
 union {
  SztHovrReqd sztHovrReqd;
  SztHovrRqst sztHovrRqst;
  SztPathSwRqst sztPathSwRqst;
  SztE_RABSetupRqst sztE_RABSetupRqst;
  SztE_RABMdfyRqst sztE_RABMdfyRqst;
  SztE_RABRlsCmmd sztE_RABRlsCmmd;
  SztInitCntxtSetupRqst sztInitCntxtSetupRqst;
  SztHovrCancel sztHovrCancel;
  SztKillRqst sztKillRqst;
  SztReset sztReset;
  SztS1SetupRqst sztS1SetupRqst;
  SztUECntxtModificationRqst sztUECntxtModificationRqst;
  SztUECntxtRlsCmmd sztUECntxtRlsCmmd;
  SztENBConfigUpd sztENBConfigUpd;
  SztMMEConfigUpd sztMMEConfigUpd;
  SztWriteReplaceWarningRqst sztWriteReplaceWarningRqst;
  SztUERadioCapbltyMatchRqst sztUERadioCapbltyMatchRqst;
  SztHovrNtfy sztHovrNtfy;
  SztE_RABRlsInd sztE_RABRlsInd;
  SztPag sztPag;
  SztDlnkNASTport sztDlnkNASTport;
  SztInitUEMsg sztInitUEMsg;
  SztUlnkNASTport sztUlnkNASTport;
  SztErrInd sztErrInd;
  SztNASNonDlvryInd sztNASNonDlvryInd;
  SztUECntxtRlsRqst sztUECntxtRlsRqst;
  SztDlnkS1cdma2000tunneling sztDlnkS1cdma2000tunneling;
  SztUlnkS1cdma2000tunneling sztUlnkS1cdma2000tunneling;
  SztUECapbltyInfoInd sztUECapbltyInfoInd;
  SztENBStatusTfr sztENBStatusTfr;
  SztMMEStatusTfr sztMMEStatusTfr;
  SztDeactvTrace sztDeactvTrace;
  SztTraceStart sztTraceStart;
  SztTraceFailInd sztTraceFailInd;
  SztCellTrafficTrace sztCellTrafficTrace;
  SztLocRprtngCntrl sztLocRprtngCntrl;
  SztLocRprtngFailInd sztLocRprtngFailInd;
  SztLocReport sztLocReport;
  SztOverloadStart sztOverloadStart;
  SztOverloadStop sztOverloadStop;
  SztENBDirectInformTfr sztENBDirectInformTfr;
  SztMMEDirectInformTfr sztMMEDirectInformTfr;
  SztENBConfigTfr sztENBConfigTfr;
  SztMMEConfigTfr sztMMEConfigTfr;
  SztPrivMsg sztPrivMsg;
  SztDlnkUEAssociatedLPPaTport sztDlnkUEAssociatedLPPaTport;
  SztUlnkUEAssociatedLPPaTport sztUlnkUEAssociatedLPPaTport;
  SztDlnkNonUEAssociatedLPPaTport sztDlnkNonUEAssociatedLPPaTport;
  SztUlnkNonUEAssociatedLPPaTport sztUlnkNonUEAssociatedLPPaTport;
 } u;
} Szt_InitiatingMsgCls;
typedef struct s1apInitiatingMsg
{
 TknPres pres;
 SztProcedureCode procedureCode;
 SztCriticality criticality;
 Szt_InitiatingMsgCls value;
} SztInitiatingMsg;

typedef struct s1ap_SuccessfulOutcomeCls{
 union {
  SztHovrCmmd sztHovrCmmd;
  SztHovrRqstAckg sztHovrRqstAckg;
  SztPathSwRqstAckg sztPathSwRqstAckg;
  SztE_RABSetupResp sztE_RABSetupResp;
  SztE_RABMdfyResp sztE_RABMdfyResp;
  SztE_RABRlsResp sztE_RABRlsResp;
  SztInitCntxtSetupResp sztInitCntxtSetupResp;
  SztHovrCancelAckg sztHovrCancelAckg;
  SztKillResp sztKillResp;
  SztResetAckg sztResetAckg;
  SztS1SetupResp sztS1SetupResp;
  SztUECntxtModificationResp sztUECntxtModificationResp;
  SztUECntxtRlsComplete sztUECntxtRlsComplete;
  SztENBConfigUpdAckg sztENBConfigUpdAckg;
  SztMMEConfigUpdAckg sztMMEConfigUpdAckg;
  SztWriteReplaceWarningResp sztWriteReplaceWarningResp;
  SztUERadioCapbltyMatchResp sztUERadioCapbltyMatchResp;
 } u;
} Szt_SuccessfulOutcomeCls;
typedef struct s1apSuccessfulOutcome
{
 TknPres pres;
 SztProcedureCode procedureCode;
 SztCriticality criticality;
 Szt_SuccessfulOutcomeCls value;
} SztSuccessfulOutcome;

typedef struct s1ap_UnsuccessfulOutcomeCls{
 union {
  SztHovrPrepFail sztHovrPrepFail;
  SztHovrFail sztHovrFail;
  SztPathSwRqstFail sztPathSwRqstFail;
  SztInitCntxtSetupFail sztInitCntxtSetupFail;
  SztS1SetupFail sztS1SetupFail;
  SztUECntxtModificationFail sztUECntxtModificationFail;
  SztENBConfigUpdFail sztENBConfigUpdFail;
  SztMMEConfigUpdFail sztMMEConfigUpdFail;
 } u;
} Szt_UnsuccessfulOutcomeCls;
typedef struct s1apUnsuccessfulOutcome
{
 TknPres pres;
 SztProcedureCode procedureCode;
 SztCriticality criticality;
 Szt_UnsuccessfulOutcomeCls value;
} SztUnsuccessfulOutcome;

typedef struct s1apS1AP_PDU
{
 TknU8 choice;
 union {
  SztInitiatingMsg initiatingMsg;
  SztSuccessfulOutcome successfulOutcome;
  SztUnsuccessfulOutcome unsuccessfulOutcome;
 } val;
} SztS1AP_PDU;










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
typedef U16 SctStrmId;
typedef U16 SctPort;
typedef U32 SctTSN;
typedef U16 SctRTT;
typedef U16 SctStatus;
typedef U16 SctResult;
typedef U16 SctCause;
typedef S32 SctWinSize;
typedef TknStr64 SctVSInfo;





typedef struct _sctNetAddrLst
{
   U8 nmb;
   CmNetAddr nAddr[5];
} SctNetAddrLst;


typedef struct _sctRtrvInfo
{
   U32 nmbUnsentDgms;
   U32 nmbUnackDgms;
   U32 nmbUndelDgms;
   SctTSN lastAckTsn;
   SctTSN lastSentTsn;
} SctRtrvInfo;


typedef struct _sctDatIndType
{
   U8 type;
   SctTSN tsn;
   U16 seqNum;
   Bool last;
} SctDatIndType;


typedef struct _SctInitParams
{
   U32 iTag;
   U32 a_rwnd;
   SctStrmId outStrms;
   SctStrmId inStrms;
   SctTSN iTsn;
   U32 cookieLife;
   SctPort peerPort;
   SctPort localPort;
   SctNetAddrLst peerAddrLst;
   SctNetAddrLst localAddrLst;
   U16 supAddress;
   U8 hstNameLen;
   U8 hstName[255];
} SctInitParams;


typedef struct _SctCookieParams
{
   UConnId spAssocId;
   UConnId suAssocId;
   SctPort peerPort;
   SctNetAddrLst peerAddrLst;





} SctCookieParams;


typedef struct _SctAssocIndParams
{
   U8 type;
   union
   {
      SctInitParams initParams;
      SctCookieParams cookieParams;
   } t;




} SctAssocIndParams;


typedef struct _sctAssocInfo
{
   SctWinSize rwnd;
   U8 connSta;
   CmNetAddr priDstAddr;
   SctPort dstPort;
   SctNetAddrLst dstAddrLst;
} SctAssocInfo;


typedef struct _sctAddrInfo
{
   U16 rtt;
   U32 cwnd;
   U32 rto;
   Bool active;
} SctAddrInfo;


typedef struct _sctStaInfo
{
   U8 staType;
   union
   {
      SctAssocInfo assocInfo;
      SctAddrInfo addrInfo;
      SctRtrvInfo rtrvInfo;
   } u;
} SctStaInfo;
typedef S16 (*SctBndReq) (Pst *pst, SuId suId, SpId spId)

                                                         ;

typedef S16 (*SctBndCfm) (Pst *pst, SuId suId, SctResult result)

                                                           ;
typedef S16 (*SctEndpOpenReq) (Pst *pst, SpId spId, UConnId suEndpId, SctPort port, CmNetAddr *intfNAddr)



                                                               ;


typedef S16 (*SctEndpOpenCfm) (Pst *pst, SuId suId, UConnId suEndpId, UConnId spEndpId, SctResult result, SctCause cause)




                                                           ;

typedef S16 (*SctEndpCloseReq) (Pst *pst, SpId spId, UConnId endpId, U8 endpIdType)


                                                                ;

typedef S16 (*SctEndpCloseCfm) (Pst *pst, SuId suId, UConnId suEndpId, SctResult result, SctCause cause)



                                                           ;
typedef S16 (*SctAssocReq) (Pst *pst, SpId spId, UConnId spEndpId, UConnId suAssocId, CmNetAddr *priDstNAddr, SctPort dstPort, SctStrmId outStrms, SctNetAddrLst *dstNAddrLst, SctNetAddrLst *srcNAddrLst, Buffer *vsInfo)
                                                           ;


typedef S16 (*SctAssocInd) (Pst *pst, SuId suId, UConnId suEndpId, SctAssocIndParams *assocParams, Buffer *vsInfo)



                                                              ;
typedef S16 (*SctAssocRsp) (Pst *pst, SpId spId, UConnId spEndpId, SctAssocIndParams *assocParams, SctResult result, Buffer *vsInfo)




                                                              ;
typedef S16 (*SctAssocCfm) (Pst *pst, SuId suId, UConnId suAssocId, UConnId spAssocId, SctNetAddrLst *dstNAddrLst, SctPort dstPort, SctStrmId outStrms, Buffer *vsInfo)






                                                           ;


typedef S16 (*SctTermReq) (Pst *pst, SpId spId, UConnId assocId, U8 assocIdType, Bool abrtFlg)



                                                            ;

typedef S16 (*SctTermInd) (Pst *pst, SuId suId, UConnId assocId, U8 assocIdType, SctStatus status, SctCause cause, SctRtrvInfo *rtrvInfo)





                                                             ;

typedef S16 (*SctTermCfm) (Pst *pst, SuId suId, UConnId suAssocId, SctResult result, SctCause cause)



                                                          ;

typedef S16 (*SctSetPriReq) (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr)


                                                             ;

typedef S16 (*SctSetPriCfm) (Pst *pst, SuId suId, UConnId suAssocId, SctResult result, SctCause cause)



                                                          ;

typedef S16 (*SctHBeatReq) (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, U16 intervalTime, SctStatus status)




                                                           ;

typedef S16 (*SctHBeatCfm) (Pst *pst, SuId suId, UConnId suAssocId, CmNetAddr *dstNAddr, SctStatus status, SctResult result, SctCause cause)





                                                          ;

typedef S16 (*SctDatReq) (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, SctStrmId strmId, Bool unorderFlg, Bool nobundleFlg, U16 lifeTime, U32 protId, Buffer *mBuf)
                                                         ;

typedef S16 (*SctDatInd) (Pst *pst, SuId suId, UConnId suAssocId, SctStrmId strmId, SctDatIndType *indType, U32 protId, Buffer *mBuf)





                                                         ;

typedef S16 (*SctStaReq) (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, U8 staType)



                                                            ;

typedef S16 (*SctStaCfm) (Pst *pst, SuId suId, UConnId suAssocId, CmNetAddr *dstNAddr, SctResult result, SctCause cause, SctStaInfo *staInfo)





                                                            ;
typedef S16 (*SctStaInd) (Pst *pst, SuId suId, UConnId suAssocId, UConnId spAssocId, CmNetAddr *dstNAddr, SctStatus status, SctCause cause, Buffer *mBuf)






                                                         ;


typedef S16 (*SctFlcInd) (Pst *pst, SuId suId, UConnId suAssocId, Reason reason)


                                                           ;







extern S16 SbUiSctBndReq (Pst *pst, SuId suId, SpId spId)

                                                               ;

extern S16 SbUiSctBndCfm (Pst *pst, SuId suId, SctResult result)

                                                                 ;
extern S16 SbUiSctEndpOpenReq (Pst *pst, SpId spId, UConnId suEndpId, SctPort port, CmNetAddr *intfNAddr)



                                                                    ;

extern S16 SbUiSctEndpOpenCfm (Pst *pst, SuId suId, UConnId suEndpId, UConnId spEndpId, SctResult result, SctCause cause)




                                                                ;

extern S16 SbUiSctEndpCloseReq (Pst *pst, SpId spId, UConnId endpId, U8 endpIdType)


                                                                     ;

extern S16 SbUiSctEndpCloseCfm (Pst *pst, SuId suId, UConnId suEndpId, SctResult result, SctCause cause)



                                                                ;
extern S16 SbUiSctAssocReq (Pst *pst, SpId spId, UConnId spEndpId, UConnId suAssocId, CmNetAddr *priDstNAddr, SctPort dstPort, SctStrmId outStrms, SctNetAddrLst *dstNAddrLst, SctNetAddrLst *srcNAddrLst, Buffer *vsInfo)
                                                                 ;


extern S16 SbUiSctAssocInd (Pst *pst, SuId suId, UConnId suEndpId, SctAssocIndParams *assocParams, Buffer *vsInfo)



                                                                     ;
extern S16 SbUiSctAssocRsp (Pst *pst, SpId spId, UConnId spEndpId, SctAssocIndParams *assocIndParams, SctResult result, Buffer *vsInfo)




                                                                     ;
extern S16 SbUiSctAssocCfm (Pst *pst, SuId suId, UConnId suAssocId, UConnId spAssocId, SctNetAddrLst *dstNAddrLst, SctPort dstPort, SctStrmId outStrms, Buffer *vsInfo)






                                                                 ;



extern S16 SbUiSctTermReq (Pst *pst, SpId spId, UConnId assocId, U8 assocIdType, Bool abrtFlg)



                                                                  ;

extern S16 SbUiSctTermInd (Pst *pst, SuId suId, UConnId assocId, U8 assocIdType, SctStatus status, SctCause cause, SctRtrvInfo *rtrvInfo)





                                                                   ;

extern S16 SbUiSctTermCfm (Pst *pst, SuId suId, UConnId suAssocId, SctResult result, SctCause cause)



                                                                ;

extern S16 SbUiSctSetPriReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr)


                                                                   ;

extern S16 SbUiSctSetPriCfm (Pst *pst, SuId suId, UConnId suAssocId, SctResult result, SctCause cause)



                                                                ;

extern S16 SbUiSctHBeatReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, U16 intervalTime, SctStatus status)




                                                                 ;

extern S16 SbUiSctHBeatCfm (Pst *pst, SuId suId, UConnId suAssocId, CmNetAddr *dstNAddr, SctStatus status, SctResult result, SctCause cause)





                                                                ;

extern S16 SbUiSctDatReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, SctStrmId strmId, Bool unorderFlg, Bool nobundleFlg, U16 lifeTime, U32 protId, Buffer *mBuf)
                                                               ;

extern S16 SbUiSctDatInd (Pst *pst, SuId suId, UConnId suAssocId, SctStrmId strmId, SctDatIndType *indType, U32 protId, Buffer *mBuf)





                                                               ;

extern S16 SbUiSctStaReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, U8 staType)



                                                                  ;

extern S16 SbUiSctStaCfm (Pst *pst, SuId suId, UConnId suAssocId, CmNetAddr *dstNAddr, SctResult result, SctCause cause, SctStaInfo *staInfo)





                                                                  ;
extern S16 SbUiSctStaInd (Pst *pst, SuId suId, UConnId suAssocId, UConnId spAssocId, CmNetAddr *dstNAddr, SctStatus status, SctCause cause, Buffer *mBuf)






                                                      ;

extern S16 SbUiSctFlcInd (Pst *pst, SuId suId, UConnId suAssocId, Reason reason)


                                                                 ;
extern S16 cmPkSctBndReq (Pst *pst, SuId suId, SpId spId)

                                                               ;

extern S16 cmPkSctBndCfm (Pst *pst, SuId suId, SctResult result)

                                                                 ;
extern S16 cmPkSctEndpOpenReq (Pst *pst, SpId spId, UConnId suEndpId, SctPort port, CmNetAddr *intfNAddr)



                                                                    ;


extern S16 cmPkSctEndpOpenCfm (Pst *pst, SuId suId, UConnId suEndpId, UConnId spEndpId, SctResult result, SctCause cause)




                                                                ;

extern S16 cmPkSctEndpCloseReq (Pst *pst, SpId spId, UConnId endpId, U8 endpIdType)


                                                                     ;

extern S16 cmPkSctEndpCloseCfm (Pst *pst, SuId suId, UConnId suEndpId, SctResult result, SctCause cause)



                                                                ;
extern S16 cmPkSctAssocReq (Pst *pst, SpId spId, UConnId spEndpId, UConnId suAssocId, CmNetAddr *priDstNAddr, SctPort dstPort, SctStrmId outStrms, SctNetAddrLst *dstNAddrLst, SctNetAddrLst *srcNAddrLst, Buffer *vsInfo)
                                                                 ;


extern S16 cmPkSctAssocInd (Pst *pst, SuId suId, UConnId suEndpId, SctAssocIndParams *assocParams, Buffer *vsInfo)



                                                                     ;
extern S16 cmPkSctAssocRsp (Pst *pst, SpId spId, UConnId spEndpId, SctAssocIndParams *assocParams, SctResult result, Buffer *vsInfo)




                                                                     ;
extern S16 cmPkSctAssocCfm (Pst *pst, SuId suId, UConnId suAssocId, UConnId spAssocId, SctNetAddrLst *dstNAddrLst, SctPort dstPort, SctStrmId outStrms, Buffer *vsInfo)






                                                                 ;


extern S16 cmPkSctTermReq (Pst *pst, SpId spId, UConnId assocId, U8 assocIdType, Bool abrtFlg)



                                                                  ;

extern S16 cmPkSctTermInd (Pst *pst, SuId suId, UConnId assocId, U8 assocIdType, SctStatus status, SctCause cause, SctRtrvInfo *rtrvInfo)





                                                                   ;

extern S16 cmPkSctTermCfm (Pst *pst, SuId suId, UConnId suAssocId, SctResult result, SctCause cause)



                                                                ;

extern S16 cmPkSctSetPriReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr)


                                                                   ;

extern S16 cmPkSctSetPriCfm (Pst *pst, SuId suId, UConnId suAssocId, SctResult result, SctCause cause)



                                                                ;

extern S16 cmPkSctHBeatReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, U16 intervalTime, SctStatus status)




                                                                 ;

extern S16 cmPkSctHBeatCfm (Pst *pst, SuId suId, UConnId suAssocId, CmNetAddr *dstNAddr, SctStatus status, SctResult result, SctCause cause)





                                                                ;

extern S16 cmPkSctDatReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, SctStrmId strmId, Bool unorderFlg, Bool nobundleFlg, U16 lifeTime, U32 protId, Buffer *mBuf)
                                                               ;

extern S16 cmPkSctDatInd (Pst *pst, SuId suId, UConnId suAssocId, SctStrmId strmId, SctDatIndType *indType, U32 protId, Buffer *mBuf)





                                                               ;

extern S16 cmPkSctStaReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, U8 staType)



                                                                  ;

extern S16 cmPkSctStaCfm (Pst *pst, SuId suId, UConnId suAssocId, CmNetAddr *dstNAddr, SctResult result, SctCause cause, SctStaInfo *staInfo)





                                                                  ;
extern S16 cmPkSctStaInd (Pst *pst, SuId suId, UConnId suAssocId, UConnId spAssocId, CmNetAddr *dstNAddr, SctStatus status, SctCause cause, Buffer *mBuf)






                                                      ;


extern S16 cmPkSctFlcInd (Pst *pst, SuId suId, UConnId suAssocId, Reason reason)


                                                                 ;


extern S16 cmUnpkSctBndReq (SctBndReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctBndCfm (SctBndCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctEndpOpenReq (SctEndpOpenReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctEndpOpenCfm (SctEndpOpenCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctEndpCloseReq (SctEndpCloseReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctEndpCloseCfm (SctEndpCloseCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctAssocReq (SctAssocReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctAssocInd (SctAssocInd func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctAssocRsp (SctAssocRsp func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctAssocCfm (SctAssocCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctTermReq (SctTermReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctTermInd (SctTermInd func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctTermCfm (SctTermCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctSetPriReq (SctSetPriReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctSetPriCfm (SctSetPriCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctHBeatReq (SctHBeatReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctHBeatCfm (SctHBeatCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctDatReq (SctDatReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctDatInd (SctDatInd func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctStaReq (SctStaReq func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctStaCfm (SctStaCfm func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctStaInd (SctStaInd func, Pst *pst, Buffer *mBuf);

extern S16 cmUnpkSctFlcInd (SctFlcInd func, Pst *pst, Buffer *mBuf);


extern S16 cmPkSctNetAddrLst (SctNetAddrLst *pkParam, Buffer *mBuf);
extern S16 cmUnpkSctNetAddrLst (SctNetAddrLst *pkParam, Buffer *mBuf);
extern S16 SzLiSctBndReq (Pst *pst, SuId suId, SpId spId)

                                                               ;

extern S16 SzLiSctBndCfm (Pst *pst, SuId suId, SctResult result)

                                                                 ;
extern S16 SzLiSctEndpOpenReq (Pst *pst, SpId spId, UConnId suEndpId, SctPort port, CmNetAddr *intfNAddr)



                                                                    ;


extern S16 SzLiSctEndpOpenCfm (Pst *pst, SuId suId, UConnId suEndpId, UConnId spEndpId, SctResult result, SctCause cause)




                                                                ;

extern S16 SzLiSctEndpCloseReq (Pst *pst, SpId spId, UConnId endpId, U8 endpIdType)


                                                                     ;

extern S16 SzLiSctEndpCloseCfm (Pst *pst, SuId suId, UConnId suEndpId, SctResult result, SctCause cause)



                                                                ;
extern S16 SzLiSctAssocReq (Pst *pst, SpId spId, UConnId spEndpId, UConnId suAssocId, CmNetAddr *priDstNAddr, SctPort dstPort, SctStrmId outStrms, SctNetAddrLst *dstNAddrLst, SctNetAddrLst *srcNAddrLst, Buffer *vsInfo)
                                                                 ;




extern S16 SzLiSctAssocInd (Pst *pst, SuId suId, UConnId suEndpId, SctAssocIndParams *assocParams, Buffer *vsInfo)



                                                                     ;
extern S16 SzLiSctAssocRsp (Pst *pst, SpId spId, UConnId spEndpId, SctAssocIndParams *assocIndParams, SctResult result, Buffer *vsInfo)




                                                                     ;
extern S16 SzLiSctAssocCfm (Pst *pst, SuId suId, UConnId suAssocId, UConnId spAssocId, SctNetAddrLst *dstNAddrLst, SctPort dstPort, SctStrmId outStrms, Buffer *vsInfo)






                                                                 ;


extern S16 SzLiSctTermReq (Pst *pst, SpId spId, UConnId assocId, U8 assocIdType, Bool abrtFlg)



                                                                  ;

extern S16 SzLiSctTermInd (Pst *pst, SuId suId, UConnId assocId, U8 assocIdType, SctStatus status, SctCause cause, SctRtrvInfo *rtrvInfo)





                                                                   ;

extern S16 SzLiSctTermCfm (Pst *pst, SuId suId, UConnId suAssocId, SctResult result, SctCause cause)



                                                                ;
extern S16 SzLiSctStaReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, U8 staType )



                                                                   ;

extern S16 SzLiSctDatReq (Pst *pst, SpId spId, UConnId spAssocId, CmNetAddr *dstNAddr, SctStrmId strmId, Bool unorderFlg, Bool nobundleFlg, U16 lifeTime, U32 protId, Buffer *mBuf)
                                                               ;

extern S16 SzLiSctDatInd (Pst *pst, SuId suId, UConnId suAssocId, SctStrmId strmId, SctDatIndType *indType, U32 protId, Buffer *mBuf)





                                                               ;
extern S16 SzLiSctStaInd (Pst *pst, SuId suId, UConnId suAssocId, UConnId spAssocId, CmNetAddr *dstNAddr, SctStatus status, SctCause cause, Buffer *mBuf)






                                                               ;


extern S16 SzLiSctFlcInd (Pst *pst, SuId suId, UConnId suAssocId, Reason reason)


                                                                 ;


typedef TknU32 SztNumberOfIuInstances;


typedef enum enumSztRelocationTyp
{
   SztRelocationTypue_not_involvedEnum,
   SztRelocationTypue_involvedEnum
} EnumSztRelocationTyp;
typedef TknU32 SztRelocationTyp;


typedef TknStrBSXL SztIntegrityProtectionKey;

typedef TknU32 SztCN_DomainIndicator;


typedef TknU32 SztEncryptionAlgorithm;





typedef TknU8 SztChosenEncryptionAlgorithm;


typedef TknU8 SztChosenIntegrityProtectionAlgorithm;


typedef TknU8 sztIntegrityProtectionAlgo;


typedef sztIntegrityProtectionAlgo sztIntegrityProtectionAlgorithm;


typedef TknU8 sztEncryptionAlgo;


typedef sztEncryptionAlgo sztEncryptionAlgorithm;


typedef TknStrBSXL SztEncryptionKey;


typedef TknU32 SztD_RNTI;


typedef TknU32 SztTgetCellId;

typedef struct s1ap_ExtnSrcUTRANCellID_ExtIEsCls
{
   union
   {
      TknU8 unused;
   } u;
} Szt_ExtnSrcUTRANCellID_ExtIEsCls;
typedef struct s1apProtExtnField_SrcUTRANCellID_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnSrcUTRANCellID_ExtIEsCls extensionValue;
} SztProtExtnField_SrcUTRANCellID_ExtIEs;
typedef struct s1apProtExtnCont_SrcUTRANCellID_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_SrcUTRANCellID_ExtIEs *member;
}SztProtExtnCont_SrcUTRANCellID_ExtIEs;

typedef struct s1apSrcUTRANCellID
{
   TknPres pres;
   SztPLMNidentity pLMNidentity;
   SztTgetCellId uTRANcellID;
   SztProtExtnCont_SrcUTRANCellID_ExtIEs iE_Extns;
} SztSrcUTRANCellID;


typedef TknStr4 Szt3gRAC;

typedef struct s1ap3g_ExtnCGI_ExtIEsCls{
   union {
      Szt3gRAC sztRAC;
   } u;
} Szt3g_ExtnCGI_ExtIEsCls;

typedef struct s1ap3gProtExtnField_CGI_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt3g_ExtnCGI_ExtIEsCls extensionValue;
} Szt3gProtExtnField_CGI_ExtIEs;

typedef struct s1ap3gProtExtnCont_CGI_ExtIEs
{
   TknU16 noComp;
   Szt3gProtExtnField_CGI_ExtIEs *member;
}Szt3gProtExtnCont_CGI_ExtIEs;

typedef struct s1ap3gCGI
{
   TknPres pres;
   SztPLMNidentity pLMNidentity;
   SztLAC lAC;
   SztCI cI;
   Szt3gProtExtnCont_CGI_ExtIEs iE_Extns;
} Szt3gCGI;

typedef struct s1apSrcCellID
{
   TknU8 choice;
   union {
      SztSrcUTRANCellID sourceUTRANCellID;
      Szt3gCGI sourceGERANCellID;
   } val;
} SztSrcCellID;

typedef TknBStr32 SztRAB_ID;


typedef TknU32 SztDCH_ID;


typedef TknU32 SztDSCH_ID;


typedef TknU32 SztHS_DSCH_MAC_d_Flow_ID;


typedef TknU32 SztE_DCH_MAC_d_Flow_ID;


typedef TknU32 SztUSCH_ID;


typedef enum enumSztCN_DomainIndicator
{
   SztCN_DomainIndicatorcs_domainEnum,
   SztCN_DomainIndicatorps_domainEnum
} EnumSztCN_DomainIndicator;

typedef struct s1ap_ExtnTrCH_ID_ExtIEsCls{
   union {
      SztHS_DSCH_MAC_d_Flow_ID sztHS_DSCH_MAC_d_Flow_ID;
      SztE_DCH_MAC_d_Flow_ID sztE_DCH_MAC_d_Flow_ID;
   } u;
} Szt_ExtnTrCH_ID_ExtIEsCls;

typedef struct s1apProtExtnField_TrCH_ID_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnTrCH_ID_ExtIEsCls extensionValue;
} SztProtExtnField_TrCH_ID_ExtIEs;
typedef struct s1apProtExtnCont_TrCH_ID_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_TrCH_ID_ExtIEs *member;
}SztProtExtnCont_TrCH_ID_ExtIEs;

typedef struct s1apTrCH_ID
{
   TknPres pres;
   SztDCH_ID dCH_ID;
   SztDSCH_ID dSCH_ID;
   SztUSCH_ID uSCH_ID;
   SztProtExtnCont_TrCH_ID_ExtIEs iE_Extns;
} SztTrCH_ID;

typedef struct s1apTrCH_ID_Lst
{
   TknU16 noComp;
   SztTrCH_ID *member;
}SztTrCH_ID_Lst;

typedef struct s1ap_ExtnRAB_TrCH_MappingItem_ExtIEsCls
{
   union
   {
      SztCN_DomainIndicator sztCN_DomainIndicator;
   } u;
} Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls;

typedef struct s1apProtExtnField_RAB_TrCH_MappingItem_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls extensionValue;
} SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs;

typedef struct s1apProtExtnCont_RAB_TrCH_MappingItem_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs *member;
}SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs;

typedef struct s1apRAB_TrCH_MappingItem
{
   TknPres pres;
   SztRAB_ID rAB_ID;
   SztTrCH_ID_Lst trCH_ID_Lst;
   SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs iE_Extns;
} SztRAB_TrCH_MappingItem;

typedef struct s1apRAB_TrCH_Mapping
{
   TknU16 noComp;
   SztRAB_TrCH_MappingItem *member;
}SztRAB_TrCH_Mapping;



typedef TknU32 SztSRB_ID;

typedef struct s1ap_ExtnSRB_TrCH_MappingItem_ExtIEsCls
{
   union
   {
      TknU8 unused;
   } u;
} Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls;

typedef struct s1apProtExtnField_SRB_TrCH_MappingItem_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls extensionValue;
} SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs;
typedef struct s1apProtExtnCont_SRB_TrCH_MappingItem_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs *member;
}SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs;

typedef struct s1apSRB_TrCH_MappingItem
{
   TknPres pres;
   SztSRB_ID sRB_ID;
   SztTrCH_ID trCH_ID;
   SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs iE_Extns;
} SztSRB_TrCH_MappingItem;

typedef struct s1apSRB_TrCH_Mapping
{
   TknU16 noComp;
   SztSRB_TrCH_MappingItem *member;
}SztSRB_TrCH_Mapping;


typedef TknU32 SztCell_Capacity_Class_Value;


typedef TknU32 SztLoadValue;


typedef TknU32 SztRTLoadValue;


typedef TknU32 SztNRTLoadInformValue;
typedef struct s1ap_ExtnCellLoadInform_ExtIEsCls
{
   union
   {
      TknU8 unused;
   } u;
} Szt_ExtnCellLoadInform_ExtIEsCls;
typedef struct s1apProtExtnField_CellLoadInform_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnCellLoadInform_ExtIEsCls extensionValue;
} SztProtExtnField_CellLoadInform_ExtIEs;

typedef struct s1apProtExtnCont_CellLoadInform_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_CellLoadInform_ExtIEs *member;
}SztProtExtnCont_CellLoadInform_ExtIEs;

typedef struct s1apCellLoadInform
{
   TknPres pres;
   SztCell_Capacity_Class_Value cell_Capacity_Class_Value;
   SztLoadValue loadValue;
   SztRTLoadValue rTLoadValue;
   SztNRTLoadInformValue nRTLoadInformValue;
   SztProtExtnCont_CellLoadInform_ExtIEs iE_Extns;
} SztCellLoadInform;

typedef struct s1ap_ExtnCellLoadInformGroup_ExtIEsCls
{
   union
   {
      TknU8 unused;
   } u;
} Szt_ExtnCellLoadInformGroup_ExtIEsCls;

typedef struct s1apProtExtnField_CellLoadInformGroup_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnCellLoadInformGroup_ExtIEsCls extensionValue;
} SztProtExtnField_CellLoadInformGroup_ExtIEs;
typedef struct s1apProtExtnCont_CellLoadInformGroup_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_CellLoadInformGroup_ExtIEs *member;
}SztProtExtnCont_CellLoadInformGroup_ExtIEs;


typedef TknStrOSXL SztTraceReference;


typedef TknU32 SztTraceRecordingSessionReference;

typedef struct s1ap_ExtnTraceRecordingSessionInform_ExtIEsCls{
   union {
      TknU8 unused;
   } u;
} Szt_ExtnTraceRecordingSessionInform_ExtIEsCls;

typedef struct s1apProtExtnField_TraceRecordingSessionInform_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnTraceRecordingSessionInform_ExtIEsCls extensionValue;
} SztProtExtnField_TraceRecordingSessionInform_ExtIEs;

typedef struct s1apProtExtnCont_TraceRecordingSessionInform_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_TraceRecordingSessionInform_ExtIEs *member;
}SztProtExtnCont_TraceRecordingSessionInform_ExtIEs;

typedef struct s1apTraceRecordingSessionInform
{
   TknPres pres;
   SztTraceReference traceReference;
   SztTraceRecordingSessionReference traceRecordingSessionReference;
   SztProtExtnCont_TraceRecordingSessionInform_ExtIEs iE_Extns;
} SztTraceRecordingSessionInform;


typedef enum enumSztMBMSLinkingInform
{
   SztMBMSLinkingInformuE_has_joined_multicast_servicesEnum
} EnumSztMBMSLinkingInform;
typedef TknU32 SztMBMSLinkingInform;


typedef TknStrOSXL SztUE_History_Inform;


typedef enum enumSztCSFB_Inform
{
   SztCSFB_InformcsfbEnum,
   SztCSFB_Informcsfb_high_priorityEnum
} EnumSztCSFB_Inform;
typedef TknU32 SztCSFB_Inform;


typedef TknStrBSXL SztSRVCC_Informnonce;
typedef struct s1ap_ExtnSRVCC_Inform_ExtIEsCls
{
   union
   {
      TknU8 unused;
   } u;
} Szt_ExtnSRVCC_Inform_ExtIEsCls;

typedef struct s1apProtExtnField_SRVCC_Inform_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnSRVCC_Inform_ExtIEsCls extensionValue;
} SztProtExtnField_SRVCC_Inform_ExtIEs;

typedef struct s1apProtExtnCont_SRVCC_Inform_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_SRVCC_Inform_ExtIEs *member;
}SztProtExtnCont_SRVCC_Inform_ExtIEs;

typedef struct s1apSRVCC_Inform
{
   TknPres pres;
   SztSRVCC_Informnonce nonce;
   SztProtExtnCont_SRVCC_Inform_ExtIEs iE_Extns;
} SztSRVCC_Inform;


typedef struct s1apCellLoadInformGroup
{
   TknPres pres;
   SztSrcCellID sourceCellID;
   SztCellLoadInform uplinkCellLoadInform;
   SztCellLoadInform downlinkCellLoadInform;
   SztProtExtnCont_CellLoadInformGroup_ExtIEs iE_Extns;
} SztCellLoadInformGroup;

typedef struct s1ap_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls
{
   union
   {
      SztSRB_TrCH_Mapping sztSRB_TrCH_Mapping;
      SztCellLoadInformGroup sztCellLoadInformGroup;
      SztTraceRecordingSessionInform sztTraceRecordingSessionInform;
      SztMBMSLinkingInform sztMBMSLinkingInform;
      SztD_RNTI sztD_RNTI;
      SztUE_History_Inform sztUE_History_Inform;
      SztSubscriberProfileIDforRFP sztSubscriberProfileIDforRFP;
      SztSRVCC_Inform sztSRVCC_Inform;
      SztRAB_ID sztRAB_ID;
      SztCSFB_Inform sztCSFB_Inform;
   } u;
} Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls;

typedef struct s1apProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls extensionValue;
} SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs;

typedef struct s1apProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *member;
}SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs;

typedef struct s1apSrcRNC_ToTgetRNC_TprntCont
{
   TknPres pres;
   SztRRC_Cont rRC_Cont;
   SztNumberOfIuInstances numberOfIuInstances;
   SztRelocationTyp relocationTyp;
   SztChosenIntegrityProtectionAlgorithm chosenIntegrityProtectionAlgorithm;
   SztIntegrityProtectionKey integrityProtectionKey;
   SztChosenEncryptionAlgorithm chosenEncryptionAlgorithForSignalling;
   SztEncryptionKey cipheringKey;
   SztChosenEncryptionAlgorithm chosenEncryptionAlgorithForCS;
   SztChosenEncryptionAlgorithm chosenEncryptionAlgorithForPS;
   SztD_RNTI d_RNTI;
   SztTgetCellId targetCellId;
   SztRAB_TrCH_Mapping rAB_TrCH_Mapping;
   SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs iE_Extns;
} SztSrcRNC_ToTgetRNC_TprntCont_3gasn;



typedef struct s1ap_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls{
   union {
      TknU8 unused;
   } u;
} Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls;

typedef struct s1apProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
{
   TknPres pres;
   SztProtExtnID id;
   SztCriticality criticality;
   Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls extensionValue;
} SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs;

typedef struct s1apProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
{
   TknU16 noComp;
   SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *member;
}SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs;
typedef struct s1apTgetRNC_ToSrcRNC_TprntCont
{
   TknPres pres;
   SztRRC_Cont rRC_Cont;
   SztD_RNTI d_RNTI;
   SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs iE_Extns;
} SztTgetRNC_ToSrcRNC_TprntCont_3gasn;






typedef U16 SztPort;
typedef struct s1appdu
{
   CmMemListCp memCp;
   SztS1AP_PDU pdu;
}S1apPdu;


typedef struct sztConReq
{
   TknU32 peerId;
   union
   {
      UConnId spConnId;
      UConnId suConnId;
   }u;
   S1apPdu *pdu;
}SztConReq;

typedef SztConReq SztConInd;

typedef struct sztConRsp
{
   UConnId suConnId;
   UConnId spConnId;
   S1apPdu *pdu;
}SztConRsp;


typedef struct sztRelReq
{
   U8 connIdType;
   U8 relType;
   UConnId connId;
   S1apPdu *pdu;
}SztRelReq;

typedef struct sztRelInd
{
   TknU32 suConnId;
   UConnId spConnId;
   S1apPdu *pdu;
}SztRelInd;

typedef SztConRsp SztConCfm;

typedef struct sztRelCfm
{
   UConnId suConnId;
   UConnId spConnId;
   U8 relType;
   S1apPdu *pdu;
}SztRelCfm;

typedef SztConRsp SztRelRsp;

typedef struct sztDatReq
{
   UConnId spConnId;
   S1apPdu *pdu;
}SztDatEvntReq;

typedef struct sztDatInd
{
   UConnId suConnId;
   S1apPdu *pdu;
}SztDatEvntInd;


typedef struct sztUDatEvnt
{
   TknU32 transId;
   TknU32 peerId;
   S1apPdu *pdu;
}SztUDatEvnt;



typedef struct sztConnSt
{
   UConnId connId;
   State state;
}SztConnSt;
typedef struct sztAudConn
{
   U8 connIdType;
   U8 nmbConn;
   SztConnSt connSt[10];
}SztAudConn;

typedef struct sztAudPeer
{
   U32 peerId;
   State peerState;
}SztAudPeer;

typedef struct sztReqStatus
{
   U16 status;
   U16 cause;
}SztReqStatus;
typedef struct sztAudEvnt
{
   U8 type;
   union
   {
      SztAudConn audConn;
      SztAudPeer audPeer;
   }u;
   SztReqStatus status;
}SztAudEvnt;

typedef struct sztStaInd
{
   TknU32 peerId;
   U8 type;
   U8 status;
   U8 reason;
}SztStaInd;

typedef struct sztLclErrInd
{
   TknU32 suConnId;
   TknU32 spConnId;
   TknU32 transId;
   U8 causeType;
   U8 causeValue;
}SztLclErrInd;



typedef struct szIePdu
{
   CmMemListCp memCp;
   union
   {
      SztSrceNB_ToTgeteNB_TprntCont srcToTget;
      SztTgeteNB_ToSrceNB_TprntCont tgetToSrc;


      SztSrcRNC_ToTgetRNC_TprntCont_3gasn srcRncToTgetRnc;
      SztTgetRNC_ToSrcRNC_TprntCont_3gasn TgetRncToSrcRnc;
      SztSrcCellID utraSrcCellId;

      SztGlobal_ENB_ID globalEnbId;
   }u;
}SzIePdu;


typedef struct sztEncDecEvnt
{
   U32 transId;
   TknU8 type;


   TknU8 ieType;

   union
   {
      S1apPdu *pdu;


      SzIePdu *iePdu;

      Buffer *mBuf;
   }u;
}SztEncDecEvnt;

typedef struct sztFlcInd
{
   TknU32 peerId;
   U8 status;
}SztFlcInd;
typedef struct _sztAbortS1
{
   TknU32 peerId;
   CmStatus abortS1Cfm;
   U8 sndAbortFlag;
} SztAbortS1;




typedef S16 (*SztBndReq) ( Pst *pst, SuId suId, SpId spId )



          ;

typedef S16 (*SztUbndReq) ( Pst *pst, SpId spId, Reason reason )



          ;

typedef S16 (*SztBndCfm) ( Pst *pst, SuId suId, U8 status )



          ;

typedef S16 (*SztStatusInd) ( Pst *pst, SuId suId, SztStaInd *sztSta )



          ;

typedef S16 (*SztFlowControlInd) ( Pst *pst, SuId suId, SztFlcInd *flcInd )



          ;

typedef S16 (*SztErrorInd) ( Pst *pst, SuId suId, SztLclErrInd *sztLclErrInd )



          ;

typedef S16 (*SztUDatReq) ( Pst *pst, SpId spId, SztUDatEvnt *uDatEvnt )



          ;

typedef S16 (*SztUDatInd) ( Pst *pst, SuId suId, SztUDatEvnt *uDatEvnt )



          ;

typedef S16 (*SztConnReq) ( Pst *pst, SpId spId, SztConReq *conReq )



          ;

typedef S16 (*SztConnInd) ( Pst *pst, SuId suId, SztConInd *conInd )



          ;

typedef S16 (*SztConnRsp) ( Pst *pst, SpId spId, SztConRsp *conRsp )



          ;

typedef S16 (*SztConnCfm) ( Pst *pst, SuId suId, SztConCfm *conCfm )



          ;

typedef S16 (*SztRelsReq) ( Pst *pst, SpId spId, SztRelReq *relReq )



          ;

typedef S16 (*SztRelsInd) ( Pst *pst, SuId suId, SztRelInd *relInd )



          ;

typedef S16 (*SztRelsRsp) ( Pst *pst, SpId spId, SztRelRsp *relRsp )



          ;

typedef S16 (*SztRelsCfm) ( Pst *pst, SuId suId, SztRelCfm *relCfm )



          ;

typedef S16 (*SztDatReq) ( Pst *pst, SpId spId, SztDatEvntReq *datEvnt )



          ;

typedef S16 (*SztDatInd) ( Pst *pst, SuId suId, SztDatEvntInd *datEvnt )



          ;

typedef S16 (*SztEncDecReq) ( Pst *pst, SpId spId, SztEncDecEvnt *sztEncDecEvnt )



          ;

typedef S16 (*SztEncDecCfm) ( Pst *pst, SuId suId, SztEncDecEvnt *sztEncDecEvnt, SztReqStatus *status )




          ;

typedef S16 (*SztAudReq) ( Pst *pst, SpId spId, SztAudEvnt *audEvnt )



          ;

typedef S16 (*SztAudCfm) ( Pst *pst, SuId suId, SztAudEvnt *audEvnt )



          ;



typedef S16 (*SztAbortS1Req) ( Pst *pst, SpId spId, SztAbortS1 *abortS1 )



          ;

typedef S16 (*SztAbortS1Cfm) ( Pst *pst, SuId suId, SztAbortS1 *abortS1 )



          ;
extern S16 cmPkS1apPdu (S1apPdu *param,Buffer *mBuf);


extern S16 cmPkS1apPduIe (SztEncDecEvnt *param,Buffer *mBuf);

extern S16 cmPkSztBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 cmPkSztUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 cmPkSztBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 cmPkSztStaInd (Pst *pst, SuId suId, SztStaInd *sztSta);
extern S16 cmPkSztFlcInd (Pst *pst, SuId suId, SztFlcInd *sztSta);
extern S16 cmPkSztLclErrInd (Pst *pst, SuId suId, SztLclErrInd *sztErrInd)
                                                    ;
extern S16 cmPkSztUDatReq (Pst *pst, SpId spId, SztUDatEvnt *uDatEvnt);
extern S16 cmPkSztUDatInd (Pst *pst, SuId suId, SztUDatEvnt *uDatEvnt);
extern S16 cmPkSztConReq (Pst *pst, SpId spId, SztConReq *conReq);
extern S16 cmPkSztConInd (Pst *pst, SuId suId, SztConInd *conInd);
extern S16 cmPkSztConRsp (Pst *pst, SpId spId, SztConRsp *conRsp);
extern S16 cmPkSztConCfm (Pst *pst, SuId suId, SztConCfm *conCfm);
extern S16 cmPkSztRelReq (Pst *pst, SpId spId, SztRelReq *relReq);
extern S16 cmPkSztRelInd (Pst *pst, SuId suId, SztRelInd *relInd);
extern S16 cmPkSztRelRsp (Pst *pst, SpId spId, SztRelRsp *relRsp);
extern S16 cmPkSztRelCfm (Pst *pst, SuId suId, SztRelCfm *relCfm);
extern S16 cmPkSztDatReq (Pst *pst, SpId spId, SztDatEvntReq *datEvnt);
extern S16 cmPkSztDatInd (Pst *pst, SuId suId, SztDatEvntInd *datEvnt);
extern S16 cmPkSztEncDecReq (Pst *pst, SpId spId, SztEncDecEvnt *sztEncDecEvnt)
                                                                ;
extern S16 cmPkSztEncDecCfm (Pst *pst, SuId suId, SztEncDecEvnt *sztEncDecEvnt, SztReqStatus *status)

                                                        ;
extern S16 cmPkSztAudReq (Pst *pst, SpId spId, SztAudEvnt *audEvnt);
extern S16 cmPkSztAudCfm (Pst *pst, SuId suId, SztAudEvnt *audEvnt);
extern S16 cmPkSztAudEvnt ( SztAudEvnt *audEvnt, Buffer *mBuf);
extern S16 cmUnpkSztAudEvnt ( SztAudEvnt *audEvnt, Buffer *mBuf);



extern S16 cmPkSztAbortS1Req (Pst *pst, SpId spId, SztAbortS1 *abortS1);
extern S16 cmPkSztAbortS1Cfm (Pst *pst, SuId suId, SztAbortS1 *abortS1);
extern S16 cmUnpkS1apPdu (S1apPdu *param,Mem *sMem,Buffer *mBuf);


extern S16 cmUnpkS1apPduIe (SztEncDecEvnt *param,Mem *sMem,Buffer *mBuf);

extern S16 cmUnpkSztBndReq (SztBndReq func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkSztUbndReq (SztUbndReq func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkSztBndCfm (SztBndCfm func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkSztStaInd (SztStatusInd func,Pst *pst,Buffer *mBuf);
extern S16 cmUnpkSztFlcInd (SztFlowControlInd func,Pst *pst,Buffer *mBuf);
extern S16 cmUnpkFlcStaInd (SztFlowControlInd func,Pst *pst,Buffer *mBuf);
extern S16 cmUnpkSztLclErrInd (SztErrorInd func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkSztUDatReq (SztUDatReq func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztUDatInd (SztUDatInd func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztConReq (SztConnReq func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztConInd (SztConnInd func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztConRsp (SztConnRsp func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztConCfm (SztConnCfm func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztRelReq (SztRelsReq func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztRelInd (SztRelsInd func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztRelRsp (SztRelsRsp func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztRelCfm (SztRelsCfm func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztDatReq (SztDatReq func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztDatInd (SztDatInd func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztEncDecReq (SztEncDecReq func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztEncDecCfm (SztEncDecCfm func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                           ;
extern S16 cmUnpkSztAudReq (SztAudReq func, Pst *pst, Buffer *mBuf, Mem *sMem)


                                            ;
extern S16 cmUnpkSztAudCfm (SztAudCfm func, Pst *pst, Buffer *mBuf,Mem *sMem)
                                                         ;
extern S16 cmUnpkSztAbortS1Req (SztAbortS1Req func, Pst *pst, Buffer *mBuf);
extern S16 cmUnpkSztAbortS1Cfm (SztAbortS1Cfm func, Pst *pst, Buffer *mBuf);
extern S16 SzUiSztBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 SzUiSztUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 SzUiSztBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 SzUiSztStaInd (Pst *pst, SuId suId, SztStaInd *sztSta);

extern S16 SzUiSztFlcInd (Pst *pst, SuId suId, SztFlcInd *flcInd);
extern S16 SzUiSztErrInd (Pst *pst, SuId suId, SztLclErrInd *sztErrInd)
                                                              ;
extern S16 SzUiSztUDatReq (Pst *pst, SpId spId, SztUDatEvnt *uDatEvnt)
                                                            ;
extern S16 SzUiSztUDatInd (Pst *pst, SuId suId, SztUDatEvnt *uDatEvnt)
                                                            ;
extern S16 SzUiSztConReq (Pst *pst, SpId spId, SztConReq *conReq);
extern S16 SzUiSztConInd (Pst *pst, SuId suId, SztConInd *conInd);
extern S16 SzUiSztConRsp (Pst *pst, SpId spId, SztConRsp *conRsp);
extern S16 SzUiSztConCfm (Pst *pst, SuId suId, SztConCfm *conCfm);
extern S16 SzUiSztRelReq (Pst *pst, SpId spId, SztRelReq *relReq);
extern S16 SzUiSztRelInd (Pst *pst, SuId suId, SztRelInd *relInd);
extern S16 SzUiSztRelRsp (Pst *pst, SpId spId, SztRelRsp *relRsp);
extern S16 SzUiSztRelCfm (Pst *pst, SuId suId, SztRelCfm *relCfm);
extern S16 SzUiSztDatReq (Pst *pst, SpId spId, SztDatEvntReq *datEvnt)
                                                             ;
extern S16 SzUiSztDatInd (Pst *pst, SuId suId, SztDatEvntInd *datEvnt)
                                                             ;
extern S16 SzUiSztEncDecReq (Pst *pst, SpId spId, SztEncDecEvnt *sztEncDecEvnt)
                                                                   ;
extern S16 SzUiSztEncDecCfm (Pst *pst, SuId suId, SztEncDecEvnt *encDecEvnt, SztReqStatus *status)

                                                                         ;
extern S16 SzUiSztAudReq (Pst *pst, SpId spId, SztAudEvnt *audEvnt);
extern S16 SzUiSztAudCfm (Pst *pst, SuId suId, SztAudEvnt *audEvnt);



extern S16 SzUiSztAbortS1Req (Pst *pst, SpId spId, SztAbortS1 *abortS1);
extern S16 SzUiSztAbortS1Cfm (Pst *pst, SuId suId, SztAbortS1 *abortS1);
extern S16 UzLiSztBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 UzLiSztUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 UzLiSztBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 UzLiSztStaInd (Pst *pst, SuId suId, SztStaInd *sztSta);
extern S16 UzLiSztFlcInd (Pst *pst, SuId suId, SztFlcInd *flcInd);
extern S16 UzLiSztErrInd (Pst *pst, SuId suId, SztLclErrInd *lclErrInd)
                                                              ;
extern S16 UzLiSztUDatReq (Pst *pst, SpId spId, SztUDatEvnt *uDatEvnt)
                                                            ;
extern S16 UzLiSztUDatInd (Pst *pst, SuId suId, SztUDatEvnt *uDatEvnt)
                                                            ;
extern S16 UzLiSztConReq (Pst *pst, SpId spId, SztConReq *conReq);
extern S16 UzLiSztConInd (Pst *pst, SuId suId, SztConInd *conInd);
extern S16 UzLiSztConRsp (Pst *pst, SpId spId, SztConRsp *conRsp);
extern S16 UzLiSztConCfm (Pst *pst, SuId suId, SztConCfm *conCfm);
extern S16 UzLiSztRelReq (Pst *pst, SpId spId, SztRelReq *relReq);
extern S16 UzLiSztRelInd (Pst *pst, SuId suId, SztRelInd *relInd);
extern S16 UzLiSztRelRsp (Pst *pst, SpId spId, SztRelRsp *relRsp);
extern S16 UzLiSztRelCfm (Pst *pst, SuId suId, SztRelCfm *relCfm);
extern S16 UzLiSztDatReq (Pst *pst, SpId spId, SztDatEvntReq *datEvnt)
                                                             ;
extern S16 UzLiSztDatInd (Pst *pst, SuId suId, SztDatEvntInd *datEvnt)
                                                             ;
extern S16 UzLiSztEncDecReq (Pst *pst, SpId spId, SztEncDecEvnt *encDecEvnt)
                                                                ;
extern S16 UzLiSztEncDecCfm (Pst *pst, SuId suId, SztEncDecEvnt *encDecEvnt, SztReqStatus *status)

                                                           ;
extern S16 UzLiSztAudReq (Pst *pst, SpId spId, SztAudEvnt *audEvnt);
extern S16 UzLiSztAudCfm (Pst *pst, SuId suId, SztAudEvnt *audEvnt);


extern S16 UzLiSztAbortS1Cfm (Pst *pst, SuId suId, SztAbortS1 *abortS1);
extern S16 UzLiSztAbortS1Req (Pst *pst, SpId spId, SztAbortS1 *abortS1);
typedef U32 SzeNbId;

typedef struct szMmeId
{
   U8 plmn[3];
   U8 mmeGroupId[2];
   U8 mmeCode[1];
} SzMmeId;

typedef struct szSctpAddr
{
   SctNetAddrLst ipAddr;
   SctPort sctPort;
} SzSctpAddr;


typedef struct szGenConfig
{
   S16 nmbSztSaps;
   S16 nmbSctSaps;
   U32 nmbConn;
   U32 nmbPeer;
   S16 timeRes;







   Pst lmPst;
} SzGenCfg;


typedef struct szSztSapConfig
{
   SpId spId;
   Selector selector;
   MemoryId mem;
   Priority priority;
   Route route;
} SzSztSapCfg;



typedef struct szSctSapConfig
{
   SuId suId;
   SpId spId;
   Selector selector;
   MemoryId mem;
   Priority priority;
   Route route;
   ProcId dstProcId;
   Ent dstEntId;
   Inst dstInstId;
   TmrCfg tBndTmr;
   U8 maxBndRetry;


   SzSctpAddr srcAddr;

} SzSctSapCfg;


typedef struct szProtConfig
{




   U8 nodeType;

   union
   {

      SzeNbId eNbId;





   } u;

} SzProtCfg;

typedef struct szAssocCfg
{
   SctStrmId locOutStrms;
   TknU16 comProcStrm;
   CmNetAddr priDstAddr;
   SctPort dstPort;
   SctNetAddrLst dstAddrLst;
   U16 nmbRetry;


   TmrCfg tmrAssocRecov;
} SzAssocCfg;

typedef struct szPeerInfo
{
   U8 type;
   TknU32 peerId;
   SpId uSapId;
   SpId sapId;
   SzAssocCfg assocCfg;


   Bool skipUeSm;

} SzPeerInfo;

typedef struct szPeerConfig
{
   U32 nmbPeers;
   SzPeerInfo *peerInfo;
} SzPeerCfg;

typedef struct szCfg
{
   union
   {
      SzGenCfg gen;
      SzSztSapCfg sztSap;
      SzSctSapCfg sctSap;
      SzProtCfg prot;
      SzPeerCfg peer;
   } u;
} SzCfg;




typedef struct szSapCntrl
{
   SpId id;
} SzSapCntrl;


typedef struct szDbgCntrl
{
   U32 dbgMask;
} SzDbgCntrl;



typedef struct szLSapTrcCntrl
{
   SpId lSapId;
   U32 trcMask;
   S32 trcLen;
} SzLSapTrcCntrl;

typedef struct szPNodeTrcCntrl
{
   TknU32 peerId;
   U32 trcMask;
   S32 trcLen;
} SzPNodeTrcCntrl;

typedef struct szPeerControl
{
   U32 nmbPeers;
   TknU32 *peerId;
}SzPeerCntrl;

typedef struct szCntrl
{
   Action action;
   Action subAction;
   union
   {
      SzSapCntrl sap;
      SzLSapTrcCntrl lSapTrc;
      SzPNodeTrcCntrl pNodeTrc;

      SzDbgCntrl dbg;





      SzPeerCntrl peer;
   } u;
} SzCntrl;





typedef struct szGenSta
{
   U32 memSize;
   U32 memAlloc;
   Cntr nmbActvPeerConn;
   U32 nmbPeer;
} SzGenSta;

typedef struct szSapSta
{
   SpId sapId;
   U8 status;
} SzSapSta;

typedef struct szPeerStaInfo
{
   TknU32 peerId;
   U8 peerState;
   UConnId spAssocId;
   Bool connected;


   U16 nmbRetries;


}SzPeerStaInfo;

typedef struct szPeerSta
{
   U32 nmbPeer;
   SzPeerStaInfo *peerStaInfo;
} SzPeerSta;

typedef struct szSsta
{
   union
   {
      SzSapSta sap;
      SystemId sysId;
      SzGenSta gen;
      SzPeerSta peer;
   } s;
} SzSsta;






typedef struct szCntr
{
   Cntr tx;
   Cntr rx;
} SzCntr;

typedef struct szPduSts
{
   SzCntr eRABSetupReq;
   SzCntr eRABSetupResp;
   SzCntr eRABModReq;
   SzCntr eRABModResp;
   SzCntr eRABRelCmd;
   SzCntr eRABRelComp;
   SzCntr eRABRelReq;
   SzCntr initCxtSetup;
   SzCntr initCxtSetupResp;
   SzCntr initCxtSetupFail;
   SzCntr ueCxtRelReq;
   SzCntr ueCxtRelCmd;
   SzCntr ueCxtRelComp;
   SzCntr ueCxtModReq;
   SzCntr ueCxtModResp;
   SzCntr ueCxtModFail;
   SzCntr initUEMsg;
   SzCntr dwnNASTpt;
   SzCntr upNASTpt;
   SzCntr nonDelIndNAS;
   SzCntr errInd;
   SzCntr noData;
   SzCntr reset;
   SzCntr resetAck;
   SzCntr setupReq;
   SzCntr setupResp;
   SzCntr setupFail;
   SzCntr paging;
   SzCntr handReqd;
   SzCntr handCmd;
   SzCntr handPrepFail;
   SzCntr handReq;
   SzCntr handReqAck;
   SzCntr handFail;
   SzCntr handNtfy;
   SzCntr pathSwchReq;
   SzCntr pathSwchReqAck;
   SzCntr pathSwchReqFail;
   SzCntr handCan;
   SzCntr handCanAck;
   SzCntr eNBStaTrans;
   SzCntr mmeStaTrans;
   SzCntr deactTrace;
   SzCntr traceStart;
   SzCntr traceFailInd;
   SzCntr locReportCntrl;
   SzCntr locReportFailInd;
   SzCntr locReport;
   SzCntr enbCfgUpd;
   SzCntr enbCfgUpdAck;
   SzCntr enbCfgUpdFail;
   SzCntr mmeCfgUpd;
   SzCntr mmeCfgUpdAck;
   SzCntr mmeCfgUpdFail;
   SzCntr upS1CDMA2000Tunn;
   SzCntr dnS1CDMA2000Tunn;
   SzCntr ueCapInfoInd;
   SzCntr overloadStart;
   SzCntr overloadStop;
   SzCntr writeRepWarnReq;
   SzCntr writeRepWarnRsp;
   SzCntr enbDirInfoTrans;
   SzCntr mmeDirInfoTrans;
   SzCntr privMsg;
   SzCntr eNBConfigTfr;
   SzCntr mmeConfigTfr;
   SzCntr cellTrafficTrace;


   SzCntr killReq;
   SzCntr killResp;
   SzCntr dwlnkUeAssocLPPaTprt;
   SzCntr uplnkUeAssocLPPaTprt;
   SzCntr dwlnkNonUeAssocLPPaTprt;
   SzCntr uplnkNonUeAssocLPPaTprt;

} SzPduSts;


typedef struct szSctSapSts
{
   SuId suId;
   struct
   {
      SzPduSts pdu;
      SzCntr szDedProcSts;
      SzCntr szComProcSts;
   }cfm;

} SzSctSapSts;



typedef struct szRadioNwErrSts
{
   StsCntr unknownMmeUeS1apId;
   StsCntr unknownEnbUeS1apId;
   StsCntr unknownPairUeS1apId;

}SzRadioNwErrSts;

typedef struct szProtErrSts
{

   StsCntr transferSyntaxErr;


   StsCntr absSyntaxErrRej;


   StsCntr absSyntaxErrIgnAndNtfy;


   StsCntr msgNotCompWithRcvrState;


   StsCntr semanticErr;


   StsCntr absSyntaxErrFalslyConsMsg;


   StsCntr protunspecified;

}SzProtErrSts;

typedef struct szErrSts
{
   SzRadioNwErrSts radioNwErrSts;
   SzProtErrSts protErrSts;

}SzErrSts;


typedef struct szPeerNodeSts
{
   TknU32 peerId;
   struct
   {
      Cntr nmbUnexpEvt;


      Cntr nmbTRafExp;

      SzPduSts pdu;
      SzCntr szDedProcSts;
      SzCntr szComProcSts;


      SzErrSts errSts;

   }cfm;

} SzPeerNodeSts;

typedef struct szAudSts
{
   Cntr nmbAudReq;
   Cntr nmbAudConn;
   Cntr nmbAudPeer;
   Cntr nmbAudFlc;

}SzAudSts;

typedef struct szGenSts
{
   Cntr nmbConn;
   Cntr nmbFailConn;
   U32 maxMemAlloc;
   Cntr nmbDecErr;
   Cntr nmbEncErr;
   SzAudSts audSts;
} SzGenSts;

typedef struct szSts
{
   union
   {
      SzGenSts gen;
      SzPeerNodeSts node;
      SzSctSapSts sctSap;
   } u;
} SzSts;





typedef struct szUstaDgn
{
   U8 type;
   union
   {
      MemoryId mem;
      SpId sapId;
      TknU32 peerId;
      UConnId connId;
      U8 data[256];
   }u;
} SzUstaDgn;

typedef struct szUsta
{
   DateTime dt;
   CmAlarm alarm;
   SzUstaDgn dgn;
} SzUsta;




typedef struct szTrc
{
   DateTime dt;
   U16 event;
   SzSctpAddr srcAddr;
   SzSctpAddr dstAddr;
   SpId sapId;
   UConnId suConnId;
} SzTrc;




typedef struct szMngmt
{
   Header hdr;

   CmStatus cfm;

   union
   {
      SzCfg cfg;
      SzCntrl cntrl;
      SzSsta ssta;
      SzUsta usta;
      SzSts sts;
      SzTrc trc;
   } u;
} SzMngmt;





typedef S16 (*LszCfgReq) ( Pst *pst, SzMngmt *cfg )


     ;

typedef S16 (*LszCfgCfm) ( Pst *pst, SzMngmt *cfg )


     ;

typedef S16 (*LszCntrlReq) ( Pst *pst, SzMngmt *cntrl )


     ;

typedef S16 (*LszCntrlCfm) ( Pst *pst, SzMngmt *cntrl )


     ;

typedef S16 (*LszStsReq) ( Pst *pst, Action action, SzMngmt *sts )



     ;

typedef S16 (*LszStsCfm) ( Pst *pst, SzMngmt *sts )


     ;

typedef S16 (*LszStaReq) ( Pst *pst, SzMngmt *sta )


     ;

typedef S16 (*LszStaCfm) ( Pst *pst, SzMngmt *sta )


     ;

typedef S16 (*LszStaInd) ( Pst *pst, SzMngmt *usta )


     ;

typedef S16 (*LszTrcInd) ( Pst *pst, SzMngmt *trc, Buffer *mBuf )



     ;


extern S16 SzMiLszCfgReq (Pst *pst, SzMngmt *cfg);
extern S16 SzMiLszCfgCfm (Pst *pst, SzMngmt *cfg);
extern S16 SzMiLszCntrlReq (Pst *pst, SzMngmt *cntrl);
extern S16 SzMiLszCntrlCfm (Pst *pst, SzMngmt *cntrl);
extern S16 SzMiLszStaInd (Pst *pst, SzMngmt *sta);
extern S16 SzMiLszTrcInd (Pst *pst, SzMngmt *trc, Buffer *mBuf);
extern S16 SzMiLszStaReq (Pst *pst, SzMngmt *sta);
extern S16 SzMiLszStaCfm (Pst *pst, SzMngmt *sta);
extern S16 SzMiLszStsReq (Pst *pst, Action action, SzMngmt *sts);
extern S16 SzMiLszStsCfm (Pst *pst, SzMngmt *sts);
extern S16 SmMiLszCfgReq (Pst *pst, SzMngmt *cfg);
extern S16 SmMiLszCfgCfm (Pst *pst, SzMngmt *cfg);
extern S16 SmMiLszStaCfm (Pst *pst, SzMngmt *sta);
extern S16 SmMiLszStaReq (Pst *pst, SzMngmt *sta);
extern S16 SmMiLszStaInd (Pst *pst, SzMngmt *sta);
extern S16 SmMiLszCntrlReq (Pst *pst, SzMngmt *cntrl);
extern S16 SmMiLszCntrlCfm (Pst *pst, SzMngmt *cntrl);
extern S16 SmMiLszStsReq (Pst *pst, Action action,SzMngmt *sts);
extern S16 SmMiLszStsCfm (Pst *pst, SzMngmt *sts);
extern S16 SmMiLszTrcInd (Pst *pst, SzMngmt *trc, Buffer *mBuf);
extern S16 smSzActvInit (Ent ent, Inst inst, Region region, Reason reason)
                                                ;
extern S16 szActvInit (Ent ent, Inst inst, Region region, Reason reason)
                                                ;


extern S16 smSzActvTsk (Pst *pst, Buffer *mBuf);
extern S16 szActvTsk (Pst *pst, Buffer *mBuf);





extern S16 cmPkSzMmeId ( SzMmeId *param, Buffer *mBuf )


           ;
extern S16 cmPkSzSctpAddr ( SzSctpAddr *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzMmeId ( SzMmeId *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzSctpAddr ( SzSctpAddr *param, Buffer *mBuf )


           ;
extern S16 cmPkSzGenCfg ( SzGenCfg *param, Buffer *mBuf )


           ;
extern S16 cmPkSzProtCfg ( SzProtCfg *param, Buffer *mBuf )


           ;
extern S16 cmPkSzSztSapCfg ( SzSztSapCfg *param, Buffer *mBuf )


           ;
extern S16 cmPkSzSctSapCfg ( SzSctSapCfg *param, Buffer *mBuf )


           ;
extern S16 cmPkSzAssocCfg ( SzAssocCfg *param, Buffer *mBuf )


           ;
extern S16 cmPkSzPeerInfo ( SzPeerInfo *param, Buffer *mBuf )


           ;
extern S16 cmPkSzPeerCfg ( Pst *pst, SzPeerCfg *param, Buffer *mBuf )



           ;
extern S16 cmPkSzCfg ( SzCfg *param, Elmnt elmnt, Buffer *mBuf, Pst *pst )




           ;
extern S16 cmUnpkSzGenCfg ( SzGenCfg *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzProtCfg ( SzProtCfg *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzSztSapCfg ( SzSztSapCfg *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzSctSapCfg ( SzSctSapCfg *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzAssocCfg ( SzAssocCfg *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzPeerInfo ( SzPeerInfo *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzPeerCfg ( Pst *pst, SzPeerCfg *param, Buffer *mBuf )



           ;
extern S16 cmUnpkSzCfg ( SzCfg *param, Elmnt elmnt, Buffer *mBuf, Pst *pst )




           ;
extern S16 cmPkSzSapCntrl ( SzSapCntrl *param, Buffer *mBuf )


           ;

extern S16 cmPkSzDbgCntrl ( SzDbgCntrl *param, Buffer *mBuf )


           ;

extern S16 cmPkSzLSapTrcCntrl ( SzLSapTrcCntrl *param, Buffer *mBuf )


           ;
extern S16 cmPkSzPNodeTrcCntrl ( SzPNodeTrcCntrl *param, Buffer *mBuf )


           ;
extern S16 cmPkSzPeerCntrl ( Pst *pst, SzPeerCntrl *param, Buffer *mBuf )



           ;
extern S16 cmPkSzCntrl ( SzCntrl *param, Elmnt elmnt, Buffer *mBuf, Pst *pst )




           ;
extern S16 cmPkSzTrc ( SzTrc *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzSapCntrl ( SzSapCntrl *param, Buffer *mBuf )


           ;

extern S16 cmUnpkSzDbgCntrl ( SzDbgCntrl *param, Buffer *mBuf )


           ;

extern S16 cmUnpkSzLSapTrcCntrl ( SzLSapTrcCntrl *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzPNodeTrcCntrl ( SzPNodeTrcCntrl *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzPeerCntrl ( Pst *pst, SzPeerCntrl *param, Buffer *mBuf )



           ;
extern S16 cmUnpkSzCntrl ( SzCntrl *param, Elmnt elmnt, Buffer *mBuf, Pst *pst )




           ;
extern S16 cmUnpkSzTrc ( SzTrc *param, Buffer *mBuf )


           ;
extern S16 cmPkSzUstaDgn ( SzUstaDgn *param, Buffer *mBuf )


           ;
extern S16 cmPkSzUsta ( SzUsta *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzUstaDgn ( SzUstaDgn *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzUsta ( SzUsta *param, Buffer *mBuf )


           ;
extern S16 cmPkSzGenSta ( SzGenSta *param, Buffer *mBuf )


           ;
extern S16 cmPkSzSapSta ( SzSapSta *param, S16 eventType, Buffer *mBuf )



           ;
extern S16 cmPkSzPeerStaInfo ( SzPeerStaInfo *param, Buffer *mBuf )


           ;
extern S16 cmPkSzPeerSta ( Pst *pst, SzPeerSta *param, Buffer *mBuf )



           ;
extern S16 cmPkSzSsta ( SzSsta *param, Elmnt elmnt, S16 eventType, Buffer *mBuf, Pst *pst )





           ;
extern S16 cmUnpkSzGenSta ( SzGenSta *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzSapSta ( SzSapSta *param, S16 eventType, Buffer *mBuf )



           ;
extern S16 cmUnpkSzPeerStaInfo ( SzPeerStaInfo *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzPeerSta ( Pst *pst, SzPeerSta *param, Buffer *mBuf )



           ;
extern S16 cmUnpkSzSsta ( SzSsta *param, Elmnt elmnt, S16 eventType, Buffer *mBuf, Pst *pst )





           ;
extern S16 cmPkSzCntr ( SzCntr *param, Buffer *mBuf )


           ;
extern S16 cmPkSzPduSts ( SzPduSts *param, Buffer *mBuf )


           ;


extern S16 cmPkSzErrSts ( SzErrSts *param, Buffer *mBuf )


           ;

extern S16 cmPkSzSctSapSts ( SzSctSapSts *param, S16 eventType, Buffer *mBuf )



           ;
extern S16 cmPkSzPeerNodeSts ( SzPeerNodeSts *param, S16 eventType, Buffer *mBuf )



           ;
extern S16 cmPkSzAudSts ( SzAudSts *param, Buffer *mBuf )


           ;
extern S16 cmPkSzGenSts ( SzGenSts *param, Buffer *mBuf )


           ;
extern S16 cmPkSzSts ( SzSts *param, Elmnt elmnt, S16 eventType, Buffer *mBuf )




           ;
extern S16 cmUnpkSzCntr ( SzCntr *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzPduSts ( SzPduSts *param, Buffer *mBuf )


           ;


extern S16 cmUnpkSzErrSts ( SzErrSts *param, Buffer *mBuf )


           ;

extern S16 cmUnpkSzSctSapSts ( SzSctSapSts *param, S16 eventType, Buffer *mBuf )



           ;
extern S16 cmUnpkSzPeerNodeSts ( SzPeerNodeSts *param, S16 eventType, Buffer *mBuf )



           ;
extern S16 cmUnpkSzAudSts ( SzAudSts *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzGenSts ( SzGenSts *param, Buffer *mBuf )


           ;
extern S16 cmUnpkSzSts ( SzSts *param, Elmnt elmnt, S16 eventType, Buffer *mBuf )




           ;
extern S16 cmPkSzMngmt ( SzMngmt *param, S16 eventType, Ent entity, Buffer *mBuf, Pst *pst )





           ;
extern S16 cmUnpkSzMngmt ( SzMngmt *param, S16 eventType, Ent entity, Buffer *mBuf, Pst *pst )





           ;
extern S16 cmPkLszCfgReq ( Pst *pst, SzMngmt *cfg )


           ;
extern S16 cmPkLszCfgCfm ( Pst *pst, SzMngmt *cfg )


           ;
extern S16 cmPkLszCntrlReq ( Pst *pst, SzMngmt *cntrl )


           ;
extern S16 cmPkLszCntrlCfm ( Pst *pst, SzMngmt *cntrl )


           ;
extern S16 cmPkLszStsReq ( Pst *pst, Action action, SzMngmt *sts )



           ;
extern S16 cmPkLszStsCfm ( Pst *pst, SzMngmt *sts )


           ;
extern S16 cmPkLszStaReq ( Pst *pst, SzMngmt *sta )


           ;
extern S16 cmPkLszStaCfm ( Pst *pst, SzMngmt *sta )


           ;
extern S16 cmPkLszStaInd ( Pst *pst, SzMngmt *usta )


           ;
extern S16 cmPkLszTrcInd ( Pst *pst, SzMngmt *trc, Buffer *mBuf )



           ;
extern S16 cmUnpkLszCfgReq ( LszCfgReq func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszCfgCfm ( LszCfgCfm func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszCntrlReq ( LszCntrlReq func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszCntrlCfm ( LszCntrlCfm func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszStsReq ( LszStsReq func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszStsCfm ( LszStsCfm func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszStaReq ( LszStaReq func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszStaCfm ( LszStaCfm func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszStaInd ( LszStaInd func, Pst *pst, Buffer *mBuf )



           ;
extern S16 cmUnpkLszTrcInd ( LszTrcInd func, Pst *pst, Buffer *mBuf )



           ;
typedef U32 SzConRefNo;

typedef struct szPeerCb SzPeerCb;
typedef struct szAssocCb SzAssocCb;

typedef struct szEndpCb
{
   CmHashListCp assocCp;
   UConnId locSpEndpId;
   UConnId locSuEndpId;
   State epState;
   SctPort port;

   SctNetAddrLst srcAddrLst;





}SzEndpCb;

typedef struct szSctSapCb
{
   State state;
   SuId suId;
   SpId spId;
   Pst pst;
   Ent contEnt;
   U32 trcMask;
   S32 trcLen;
   U8 maxBndRetry;
   TmrCfg tBndTmr;
   U8 retryCnt;
   CmTimer timers[10];
   Bool cfgDone;

   SzSctSapSts sts;
   Bool endpCfgDone;
   SzEndpCb endpCb;
}SzSctSapCb;

typedef struct szSztSapCb
{
   SuId suId;
   SpId spId;
   Pst pst;
   State state;

   CmHashListCp suConnLst;
}SzSztSapCb;



struct szPeerCb
{
   CmHashListEnt hashEnt;
   U32 peerId;
   U8 nodeType;

   Bool skipUeSm;





   U32 nmbConn;
   SzAssocCb *assocCb;
   State state;
   Bool delPcb;
   U32 trcMask;
   S32 trcLen;
   SzSztSapCb *sztSapCb;
   SzSctSapCb *sctSapCb;
   S1apPdu *setupReq;
   SzPeerNodeSts peerSts;
   CmHashListCp conRefLst;
   CmHashListCp conRefLstRem;
   SctStrmId comStreamId;
   U16 nextStreamId;
   S1apPdu *resetPdu;


   Bool s1Abort;






};

struct szAssocCb
{
   UConnId spAssocId;
   UConnId suAssocId;
   State assocState;

   SzPeerCb *peer;
   SzAssocCfg *assocCfg;






};


typedef struct szPeerAddrPortEntry
{
   CmNetAddr peerAddr;
   SztPort port;
} SzPeerAddrPortEntry;

typedef struct szPeerAddrPortCb
{
   CmHashListEnt hashEnt;
   SzPeerAddrPortEntry peerAddrPort;
   SzPeerCb *peerCbPtr;
} SzPeerAddrPortCb;



typedef struct szConPartyCb
{
   SzPeerCb *peerCb;
   SctStrmId streamNo;
   UConnId suConnId;
   UConnId spConnId;
}SzConPartyCb;


typedef struct szConCb
{
   CmHashListEnt lclConHlEnt;
   CmHashListEnt peerConHlEnt;
   CmHashListEnt suConHlEnt;
   CmHashListEnt peerConHlEntRem;
   U8 state;
   SzConRefNo lclConRefNo;
   SzConRefNo rmtConRefNo;

   SzConPartyCb cd;

   U8 conType;




}SzConCb;


typedef struct szNodeCb
{
   U8 nodeType;
   SzProtCfg protCfg;
   SzSctpAddr nodeAddr;
   U8 cfgDone;
   U16 nmbMap;





}SzNodeCb;


typedef struct _szCb
{
   TskInit init;
   SzGenCfg genCfg;
   SzGenSts genSts;
   SzGenSta genSta;
   SzSztSapCb **sztSapLst;
   SzSctSapCb **sctSapLst;
   SzNodeCb nodeCb;
   CmHashListCp peerLst;
   CmHashListCp peerAddrPortLst;
   CmTqCp szTqCp;
   CmTqType szTq[64];

   U8 outOfRsrc;
   U8 pendingOp;
   CmHashListCp lclConCp;
   U32 lclConCntr;
   Bool shutdown;
   U8 nodeDbg[10];





} SzCb;
extern SzCb szCb;


typedef S16 (*PFRAM) (SzConCb *conCb, SzPeerCb *peerCb, S1apPdu *pdu);
typedef S16 (*PFSZLIMSGHANDLER) (SzPeerCb *peerCb, S1apPdu *pdu);
typedef S16 (*PFSZMGMTUIMSGHANDLER) (SzPeerCb *peerCb, S1apPdu *pdu, SzSztSapCb *uSapCb, U8 *cause)
                                                                         ;





extern U8 SzMsgId[48][3];
extern PFRAM szSmUiEnb[73][4];
extern PFRAM szSmLiEnb[73][4];

extern PFSZLIMSGHANDLER szLiRcvEnb[73];
extern PFSZMGMTUIMSGHANDLER szMgmtUiEnb[73];
extern S16 szActvTmr (Void);

extern S16 szGetSId (SystemId *s);


extern S16 szNdbAllocConCb (SzConCb **conCb,SzPeerCb *peer);
extern S16 szNdbGetConCb (SzConRefNo conId,SzConCb **connectionCb);
extern S16 szNdbDeallocConCb (SzConRefNo conRef,SzPeerCb *peerCb, U8 conRefType);
extern S16 szNdbGetStream (SzPeerCb *peerCb,SctStrmId *strmId);
extern S16 szNdbInitPeerLst (Void);
extern S16 szNdbAllocPeerCb (U32 peerId, SzPeerCb **peer);
extern S16 szNdbChkPeer (TknU32 peerId,SzPeerCb **peerCb);
extern S16 szNdbRelConns (SzPeerCb *peer);
extern S16 szNdbDeallocPeerCb (SzPeerCb *peer);
extern S16 szNdbDeallocAllPeerCb (SpId sapId, U8 sapDir, U8 opn);




extern S16 szNdbFillPeerAssocParams (SzPeerCb *peerCb, SzAssocCfg *assocCfg)
                                                                ;
extern S16 szNdbAddPeerAddrPortCb (SctNetAddrLst *dstAddrLst, SctPort dstPort, SzPeerCb *peerAssoc)

                                                              ;
extern S16 szNdbFindPeerAddrPortCb (SctNetAddrLst *dstAddrLst, SctPort dstPort, SzPeerCb **peerAssoc)

                                                               ;
extern S16 szNdbRemPeerAddrPortCb (SzPeerCb *peer);


extern S16 szSmExcMt (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu,U8 evnt,U8 dir);
extern S16 szSmRcvEstStMsg (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmIdleStPeerErr (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmPeerErrHdlr (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmSndConnStMsg (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmSndEstStMsg (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmLclRlsReq (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmLclErrMsg (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmLclErrState (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmSndIdleStMsg (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);

extern S16 szSmSndConnStHoFail (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmRcvConnStPathSwReqFail (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);






extern S16 szSmRcvIdleStMsg (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmRcvConnStMsg (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmSemPeerErr (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmRcvIdleStErrInd (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);
extern S16 szSmRcvConnStErrInd (SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu);


extern U16 szDbGetEnbS1apId (S1apPdu *pdu);
extern U16 szDbGetMmeS1apId (S1apPdu *pdu);
extern S16 szLiErrHndlr (S1apPdu *pdu, U8 group,U16 cause, S1apPdu **rspPdu,Mem mem)
                                                        ;


extern S16 szUiSndConInd (SzConCb *conCb,SztConInd *conInd);
extern S16 szUiSndConCfm (SzConCb *conCb,SztConCfm *conCfm);
extern S16 szUiSndDatInd (SzConCb *conCb,SztDatEvntInd *datEvt);
extern S16 szUiSndUDatInd (SzPeerCb *peerCb, SztUDatEvnt *uDatEvn);
extern S16 szUiSndRelInd (SzConCb *conCb,SztRelInd *relInd);
extern S16 szUiSndRelCfm (SzConCb *conCb,SztRelCfm *relCfm);




extern S16 szEncode (Mem *mem, S1apPdu **s1apPdu, Buffer **mBuf);
extern S16 szDecode (Mem *mem, CmPAsnErr *asnErr, S1apPdu **s1apPdu, Buffer **mBuf);


extern S16 szIeEncode (Mem *mem, SztEncDecEvnt *sztEncDecEvnt);
extern S16 szIeDecode (Mem *mem, CmPAsnErr *asnErr, SztEncDecEvnt *sztEncDecEvnt);

extern S16 szGetIE (SztS1AP_PDU *pdu, U32 id, TknU8 **ie);

extern S16 szDbFillResetAck (S1apPdu *pdu, S1apPdu **rstAckPdu, Mem mem, U8 *cause);
extern S16 szDbFillResetFrmPdu (S1apPdu *pdu, S1apPdu **rstPdu, Mem mem);

extern S16 szUtilsGetConCb (SzPeerCb *peerCb, S1apPdu *pdu, SzConCb **conCb)
                  ;
extern S16 szUtilsBldUnsucOutComeMsg (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **errPdu, Mem mem, CmPAsnErr *asnErr)
                                                                 ;

extern S16 szDbFillMMEConfigUpdFail (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **errIndPdu, Mem mem, CmPAsnErr *asnErr)
                                                                    ;
extern S16 szDbFillENBConfigUpdFail (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **errIndPdu, Mem mem, CmPAsnErr *asnErr)
                                                                    ;
extern S16 szDbFillS1SetupFail (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **errIndPdu, Mem mem, CmPAsnErr *asnErr)
                                                                    ;
extern S16 szDbFillPathSwRqstFail (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **errIndPdu, Mem mem, CmPAsnErr *asnErr)
                                                                    ;
extern S16 szDbFillHovrFail (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **errIndPdu, Mem mem, CmPAsnErr *asnErr)
                                                                    ;
extern S16 szDbFillHovrPrepFail (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **errIndPdu, Mem mem, CmPAsnErr *asnErr)
                                                                    ;


extern S16 szUtilsGetMsgIdx (U8 *evnt,S1apPdu *pdu);
extern S16 szValidateSdus (S1apPdu *pdu,U8 primType, U8 *evnt);
extern S16 szUtilsAllocConId (U32 *connId);
extern S16 szDbFillInitCxtSetupFail (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **initCxtSetupFail, Mem mem, CmPAsnErr *asnErr)




                                                             ;
extern S16 szDbFillUeCxtModFail (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **ueCxtModFailPdu, Mem mem, CmPAsnErr *asnErr)




                                                         ;
extern S16 szDbFillErrInd (S1apPdu *pdu, U8 causeChoice, U32 causeVal, S1apPdu **errIndPdu, Mem mem, CmPAsnErr *asnErr)




                                                   ;
extern S16 szIncErrSts (SzPeerCb *peer, U16 causeTyp, U16 cause);


extern S16 szUbndSztSap (SpId uSapId, U8 opn);


extern S16 szMgmtUiSetupReq (SzPeerCb *peerCb, S1apPdu *pdu, SzSztSapCb *uSapCb, U8 *cause)
                                                                     ;
extern S16 szMgmtLiPaging (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtLiSetupRsp (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtLiSetupFailure (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtLiOvldStart (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtLiOvldStop (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtLiWarningReq (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtLiMmeDirTrans (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtUiInvldMsgHandler (SzPeerCb *peerCb, S1apPdu *pdu, SzSztSapCb *uSapCb, U8 *cause)
                                                                     ;
extern S16 szMgmtUiMsgHandler (SzPeerCb *peerCb, S1apPdu *pdu, SzSztSapCb *uSapCb, U8 *cause)
                                                                     ;
extern S16 szMgmtUiRst (SzPeerCb *peerCb, S1apPdu *pdu, SzSztSapCb *uSapCb, U8 *cause)
                                                                     ;
extern S16 szMgmtUiRstAck (SzPeerCb *peerCb, S1apPdu *pdu, SzSztSapCb *uSapCb, U8 *cause)
                                                                     ;
extern S16 szMgmtLiRst (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtLiRstAck (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtUiErrInd (SzPeerCb *peerCb, S1apPdu *pdu, SzSztSapCb *uSapCb, U8 *cause)
                                                                     ;
extern S16 szMgmtLiErrInd (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szMgmtLiMsgHandler (SzPeerCb *peerCb, S1apPdu *pdu);

extern Void szSendLmAlarm (U16 category,U16 event,U16 cause,SzUstaDgn *dgn);
extern S16 szSendLmTrc (S32 trcLen, SzTrc *trcParam, Buffer *mBuf);
extern S16 szShutdown (Void);


extern S16 szLiSndToLower (SzPeerCb *peerCb, SzConCb *conCb, S1apPdu *pdu);
extern S16 szLiRcvFromLower (Buffer *mBuf,SzPeerCb *peerCb);
extern S16 szLiCOMsgHandler (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szLiPeerErrHandler (SzPeerCb *peerCb, S1apPdu *pdu);
extern S16 szLiSndAssocReq (SzAssocCb *assocCb);
extern S16 szLiTermAssoc (SzPeerCb **peerCb, Bool assocAbort);





extern Void szTmrEvnt (U32 cb, S16 event);
extern S16 szRegInitTmr (Void);
extern Void szStartTmr (CmTimer *tmr,U32 cb,U8 evnt,TmrCfg *wait);
extern Void szStopTmr (CmTimer *tmr);


extern S16 szDelSztSap ( SpId sapId, U8 opn);

extern S16 szDelSctSap (SuId lSapId, U8 opn);






extern S16 szProtIE_Cont_HovrReqdIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_HovrCmmdIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_HovrPrepFailIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_HovrRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_HovrRqstAckgIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_HovrFailIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_HovrNtfyIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_PathSwRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_PathSwRqstAckgIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_PathSwRqstFailIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_HovrCancelIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_HovrCancelAckgIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_E_RABSetupRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_E_RABSetupRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_E_RABMdfyRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_E_RABMdfyRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_E_RABRlsCmmdIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_E_RABRlsRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_E_RABRlsIndIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_InitCntxtSetupRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_InitCntxtSetupRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_InitCntxtSetupFailIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_PagIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UECntxtRlsRqst_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UECntxtRlsCmmd_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UECntxtRlsComplete_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UECntxtModificationRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UECntxtModificationRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UECntxtModificationFailIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UERadioCapbltyMatchRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UERadioCapbltyMatchRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_DlnkNASTport_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_InitUEMsg_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UlnkNASTport_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_NASNonDlvryInd_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ResetIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ResetAckgIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ErrIndIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_S1SetupRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_S1SetupRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_S1SetupFailIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ENBConfigUpdIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ENBConfigUpdAckgIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ENBConfigUpdFailIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_MMEConfigUpdIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_MMEConfigUpdAckgIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_MMEConfigUpdFailIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_DlnkS1cdma2000tunnelingIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UlnkS1cdma2000tunnelingIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UECapbltyInfoIndIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ENBStatusTfrIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_MMEStatusTfrIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_TraceStartIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_TraceFailIndIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_DeactvTraceIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_CellTrafficTraceIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_LocRprtngCntrlIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_LocRprtngFailIndIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_LocReportIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_OverloadStartIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_OverloadStopIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_WriteReplaceWarningRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_WriteReplaceWarningRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ENBDirectInformTfrIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_MMEDirectInformTfrIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_ENBConfigTfrIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_MMEConfigTfrIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szPrivIE_Cont_PrivMsgIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_KillRqstIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_KillRespIEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_DlnkUEAssociatedLPPaTport_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UlnkUEAssociatedLPPaTport_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEsValidate (CmPAsnMsgCp *msgCp);
extern S16 szProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEsValidate (CmPAsnMsgCp *msgCp);


U32 flagSz3O = 0x1 | 0x10000000 |0x80000000;
U32 flagSz3M = 0x2 | 0x10000000 | 0x80000000;
U32 flagSz3D = 0x4 | 0x10000000 | 0x80000000;







typedef struct _szProtIEs
{
   TknPres pres;
   TknU32 id;
   TknU32 criticality;
} SzProtIEs;

typedef struct _szMsgIeInf
{
   U32 procId;
   U32 criticality;
   U32 presFlag;
} SzMsgIeInf;

typedef struct _szMsgConInf
{
   SzMsgIeInf infArr[32];
   U16 maxIes;
   U16 minIes;
} SzMsgConInf;

extern S16 szValidateProtIes (SzMsgConInf *conInf, CmPAsnMsgCp *msgCp, Void *iePtr, U32 ieSize, U8 numIes);


 S16 szValidateProtIes
(
SzMsgConInf *conInf,
CmPAsnMsgCp *msgCp,
Void *iePtr,
U32 ieSize,
U8 numIes
)
{
   U8 idx = 0;
   U8 furIdx = 0;
   S8 evntIdx = 0;
   Bool idExists = 0;
   U32 memPtr = 0;

   S8 iesLeft;
   TknU32 *fieldIe = 0L;
   SzMsgIeInf *array = conInf->infArr;
   TknU32 *fieldCrit = 0L;
   S16 ret = 0;

   CmPAsnErr *err = 0L;


   ;;

   if(conInf->maxIes == 0)
   {
      return(0);
   }


  iesLeft = conInf->minIes;


   err = msgCp->err;
   err->ieCount = 0;
   err->errCode = 0;



   for(evntIdx = 0; evntIdx < numIes; evntIdx++)
   {

      memPtr = (ieSize * evntIdx);


      fieldIe = &((SzProtIEs *)((U8 *)iePtr + memPtr))->id;
      fieldCrit = &((SzProtIEs *)((U8 *)iePtr + memPtr))->criticality;


      if(idx < conInf->maxIes)
      {
         if(fieldIe->val != array[idx].procId)
         {

            furIdx = (idx + 1);
            idExists = 0;

            while(furIdx < conInf->maxIes)
            {
               if(fieldIe->val == array[furIdx].procId)
               {

                  idExists = 1;
                  break;
               }
               else
               {
                  furIdx++;
               }
            }


            if(idExists)
            {


               if (((array[idx].presFlag == 0x2) &&
                   (array[idx].criticality & 1)) ||
                   (array[idx].presFlag == 0x1))
               {


                  idx = furIdx + 1;
                  if(iesLeft)
                  {
                     iesLeft--;
                  }
                  continue;

               }
               else
               {

                  err->ieCount = 0;
                  err->errCause = 5;

                  return(1);
               }
            }
            else
            {



               furIdx = 0;
               idExists = 0;
               while(furIdx < conInf->maxIes)
               {
                  if(fieldIe->val == array[furIdx].procId)
                  {

                     idExists = 1;
                     break;
                  }
                  else
                  {
                     furIdx++;
                  }
               }

               if(idExists)
               {

                  err->ieCount = 0;
                  err->errCause = 5;

                  return(1);
               }

               else
               {




                  if((fieldCrit->val & 1))
                  {


                      fieldIe->pres = 0;
                      continue;
                  }
                  else
                  {
                     if(err->ieCount < 15)
                     {
                        err->ieInfo[err->ieCount].ieId = fieldIe->val;
                        err->ieInfo[err->ieCount].criticality = fieldCrit->val;
                        err->ieInfo[err->ieCount].errType=
                               0;
                        err->ieCount++;
                     }
                     continue;
                  }



               }
            }
         }

         else
         {

            if((array[idx].presFlag == 0x2) && (iesLeft))
            {
               iesLeft--;
            }
            idx++;
         }
      }
      else
      {
         furIdx = 0;
         idExists = 0;
         while(furIdx < conInf->maxIes)
         {
            if(fieldIe->val == array[furIdx].procId)
            {

               idExists = 1;
               break;
            }
            else
            {
               furIdx++;
            }
         }




         if(idExists)
         {


            err->ieCount = 0;
            err->errCause = 5;

            return(1);
         }
         else
         {

            if((fieldCrit->val & 1))
            {


               fieldIe->pres = 0;
               continue;
            }
            else
            {

               if(err->ieCount < 15)
               {
                  err->ieInfo[err->ieCount].ieId = fieldIe->val;
                  err->ieInfo[err->ieCount].criticality = fieldCrit->val;
                  err->ieInfo[err->ieCount].errType=
                                        0;
                  err->ieCount++;
               }
               continue;
            }

         }
      }
   }


   if(err->ieCount)
   {
      err->errCause = 1;
      return(1);
   }


   else if(iesLeft > 0)



   {
      while((iesLeft > 0) && (idx < conInf->maxIes))
      {


         if((array[idx].presFlag == 0x2) &&
            (array[idx].criticality & 1))
         {
            idx++;
            iesLeft--;
         }
         else if(array[idx].presFlag == 0x2)
         {


            if(err->ieCount < 15)
            {
               err->ieInfo[err->ieCount].ieId = array[idx].procId;
               err->ieInfo[err->ieCount].criticality = array[idx].criticality;
               err->ieInfo[err->ieCount].errType = 1;
               err->ieCount++;
            }







            { if ((&szCb.init)->dbgMask & (0x00000100)) { snprintf((&szCb.init)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", szCb.nodeDbg, (&szCb.init)->procId, (&szCb.init)->ent, (&szCb.init)->inst,

                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/s1ap/sz_db.c"
            ,

                                    403
            ); SPrint((&szCb.init)->prntBuf); sprintf (szCb.init.prntBuf, "szValidateProtIes: Mandatory IE missing: %ld \n", array[idx].procId); SPrint((&szCb.init)->prntBuf); } }

                                     ;


            idx++;
            iesLeft--;
            ret = 1;
         }
         else
         {
            idx++;
         }
      }



      if(err->ieCount)
      {
         err->errCause = 1;
         return(1);
      }

   }

   return(ret);
}
CmPAsnElmDef szConstTerm =
{



   CM_PASN_TET_SETSEQ_TERM,
   0,
   0,
   &flagSz3M,
   0,
   0L,
   0L
};
 CmPAsnElmDef szNull =
{



  CM_PASN_TET_NULL,
  0,
  0,
  &flagSz3M,
  0,
  0L,
  0L
};
CmPAsnElmDef szExtMkr =
{



  CM_PASN_TET_EXT_MKR,
  0,
  0,
  &flagSz3M,
  0,
  0L,
  0L
};

CmPAsnTknEnum szCriticalityLst[4] =
{
 3,
 SztCriticalityrejectEnum,
 SztCriticalityignoreEnum,
 SztCriticalitynotifyEnum
};
CmPAsnEnumDef szCriticalityspec =
{



 szCriticalityLst,
 0L
};
CmPAsnElmDef szOptCriticality =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztCriticality),
 &flagSz3O,
 0,
 (U8 *)(&szCriticalityspec),
 0L
};
CmPAsnElmDef szCriticality =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztCriticality),
 &flagSz3M,
 0,
 (U8 *)(&szCriticalityspec),
 0L
};


CmPAsnTknEnum szPresenceLst[4] =
{
 3,
 SztPresenceoptionalEnum,
 SztPresenceconditionalEnum,
 SztPresencemandatoryEnum
};
CmPAsnEnumDef szPresencespec =
{



 szPresenceLst,
 0L
};
CmPAsnElmDef szPresence =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztPresence),
 &flagSz3M,
 0,
 (U8 *)(&szPresencespec),
 0L
};


CmPAsnUIntDef szPrivIE_IDlocalspec =
{



 0,
 65535UL
};
CmPAsnElmDef szPrivIE_IDlocal =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztPrivIE_IDlocal),
 &flagSz3M,
 0,
 (U8 *)(&szPrivIE_IDlocalspec),
 0L
};

 CmPAsnElmDef *szPrivIE_IDTkn[] =
{
 &szPrivIE_IDlocal,
 &szConstTerm
};
CmPAsnChoiceDef szPrivIE_IDspec =
{



 2,
 0,
 &szPrivIE_IDTkn[0]
};
CmPAsnElmDef szPrivIE_ID =
{



 CM_PASN_TET_CHOICE,
 0,
 sizeof(SztPrivIE_ID),
 &flagSz3M,
 0L,
 (U8 *)(&szPrivIE_IDspec),
 0L
};

CmPAsnUIntDef szProcedureCodespec =
{



 0,
 255UL
};
CmPAsnElmDef szProcedureCode =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztProcedureCode),
 &flagSz3M,
 0,
 (U8 *)(&szProcedureCodespec),
 0L
};
CmPAsnElmDef szOptProcedureCode =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztProcedureCode),
 &flagSz3O,
 0,
 (U8 *)(&szProcedureCodespec),
 0L
};


CmPAsnUIntDef szProtExtnIDspec =
{



 0,
 65535UL
};
CmPAsnElmDef szProtExtnID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztProtExtnID),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnIDspec),
 0L
};


CmPAsnUIntDef szProtIE_IDspec =
{



 0,
 65535UL
};
CmPAsnElmDef szProtIE_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztProtIE_ID),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_IDspec),
 0L
};


CmPAsnTknEnum szTrgMsgLst[4] =
{
 3,
 SztTrgMsginitiating_messageEnum,
 SztTrgMsgsuccessful_outcomeEnum,
 SztTrgMsgunsuccessfull_outcomeEnum
};
CmPAsnEnumDef szTrgMsgspec =
{



 szTrgMsgLst,
 0L
};
CmPAsnElmDef szOptTrgMsg =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztTrgMsg),
 &flagSz3O,
 0,
 (U8 *)(&szTrgMsgspec),
 0L
};

CmPAsnOctStrDef szTBCD_STRINGspec =
{



 3,
 3
};
CmPAsnElmDef szTBCD_STRING =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztTBCD_STRING),
 &flagSz3M,
 0,
 (U8 *) (&szTBCD_STRINGspec),
 0L
};

CmPAsnBitStrDef szCellIdentityspec =
{



 28,
 28
};
CmPAsnElmDef szCellIdentity =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztCellIdentity),
 &flagSz3M,
 0,
 (U8 *) (&szCellIdentityspec),
 0L
};
 CmPAsnElmDef *sz_ExtnEUTRAN_CGI_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnEUTRAN_CGI_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnEUTRAN_CGI_ExtIEsClsInfo =
{
 0,
 &sz_ExtnEUTRAN_CGI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnEUTRAN_CGI_ExtIEsClsSpec =
{



 &sz_ExtnEUTRAN_CGI_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnEUTRAN_CGI_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnEUTRAN_CGI_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnEUTRAN_CGI_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnEUTRAN_CGI_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_EUTRAN_CGI_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnEUTRAN_CGI_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_EUTRAN_CGI_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_EUTRAN_CGI_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_EUTRAN_CGI_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_EUTRAN_CGI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_EUTRAN_CGI_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_EUTRAN_CGI_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_EUTRAN_CGI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_EUTRAN_CGI_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_EUTRAN_CGI_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_EUTRAN_CGI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_EUTRAN_CGI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_EUTRAN_CGI_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szEUTRAN_CGITkn[] =
{
 &szTBCD_STRING,
 &szCellIdentity,
 &szOptProtExtnCont_EUTRAN_CGI_ExtIEs,
  &szProtExtnField_EUTRAN_CGI_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szEUTRAN_CGIspec =
{



 1,
 0,
 0L,
 0L,
 &szEUTRAN_CGITkn[0],
 0
};
 CmPAsnElmDef szEUTRAN_CGI =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztEUTRAN_CGI),
 &flagSz3M,
 0,
 (U8 *)(&szEUTRAN_CGIspec),
 0L
};
CmPAsnSetSeqOfDef szCellIdLstforMDTspec =
{



 1,
 32,
 3*sizeof(U32)
};
 CmPAsnElmDef szCellIdLstforMDT =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCellIdLstforMDT),
 &flagSz3M,
 0,
 (U8 *) (&szCellIdLstforMDTspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCellBasedMDT_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCellBasedMDT_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCellBasedMDT_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCellBasedMDT_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCellBasedMDT_ExtIEsClsSpec =
{



 &sz_ExtnCellBasedMDT_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCellBasedMDT_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCellBasedMDT_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCellBasedMDT_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCellBasedMDT_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CellBasedMDT_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCellBasedMDT_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CellBasedMDT_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CellBasedMDT_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CellBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CellBasedMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CellBasedMDT_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CellBasedMDT_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CellBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CellBasedMDT_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CellBasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CellBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CellBasedMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CellBasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCellBasedMDTTkn[] =
{
 &szCellIdLstforMDT,
  &szEUTRAN_CGI,
  &szConstTerm,
 &szOptProtExtnCont_CellBasedMDT_ExtIEs,
  &szProtExtnField_CellBasedMDT_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCellBasedMDTspec =
{



 1,
 0,
 0L,
 0L,
 &szCellBasedMDTTkn[0],
 0
};
 CmPAsnElmDef szCellBasedMDT =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCellBasedMDT),
 &flagSz3M,
 0,
 (U8 *)(&szCellBasedMDTspec),
 0L
};
CmPAsnOctStrDef szTACspec =
{



 2,
 2
};
CmPAsnElmDef szTAC =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztTAC),
 &flagSz3M,
 0,
 (U8 *) (&szTACspec),
 0L
};
CmPAsnSetSeqOfDef szTALstforMDTspec =
{



 1,
 8,
 3*sizeof(U32)
};
 CmPAsnElmDef szTALstforMDT =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztTALstforMDT),
 &flagSz3M,
 0,
 (U8 *) (&szTALstforMDTspec),
 0L
};
 CmPAsnElmDef *sz_ExtnTABasedMDT_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTABasedMDT_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTABasedMDT_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTABasedMDT_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTABasedMDT_ExtIEsClsSpec =
{



 &sz_ExtnTABasedMDT_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTABasedMDT_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTABasedMDT_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTABasedMDT_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTABasedMDT_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TABasedMDT_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTABasedMDT_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TABasedMDT_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TABasedMDT_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TABasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TABasedMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TABasedMDT_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TABasedMDT_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TABasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TABasedMDT_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TABasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TABasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TABasedMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TABasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTABasedMDTTkn[] =
{
 &szTALstforMDT,
  &szTAC,
  &szConstTerm,
 &szOptProtExtnCont_TABasedMDT_ExtIEs,
  &szProtExtnField_TABasedMDT_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTABasedMDTspec =
{



 1,
 0,
 0L,
 0L,
 &szTABasedMDTTkn[0],
 0
};
 CmPAsnElmDef szTABasedMDT =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTABasedMDT),
 &flagSz3M,
 0,
 (U8 *)(&szTABasedMDTspec),
 0L
};
 CmPAsnElmDef *sz_ExtnTAI_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTAI_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTAI_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTAI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTAI_ExtIEsClsSpec =
{



 &sz_ExtnTAI_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTAI_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTAI_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTAI_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTAI_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TAI_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTAI_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TAI_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TAI_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TAI_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TAI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TAI_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TAI_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TAI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAI_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TAI_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TAI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TAI_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTAITkn[] =
{
 &szTBCD_STRING,
 &szTAC,
 &szOptProtExtnCont_TAI_ExtIEs,
  &szProtExtnField_TAI_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTAIspec =
{



 1,
 0,
 0L,
 0L,
 &szTAITkn[0],
 0
};
 CmPAsnElmDef szTAI =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTAI),
 &flagSz3M,
 0,
 (U8 *)(&szTAIspec),
 0L
};
CmPAsnSetSeqOfDef szTAILstforMDTspec =
{



 1,
 8,
 3*sizeof(U32)
};
 CmPAsnElmDef szTAILstforMDT =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztTAILstforMDT),
 &flagSz3M,
 0,
 (U8 *) (&szTAILstforMDTspec),
 0L
};
 CmPAsnElmDef *sz_ExtnTAIBasedMDT_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTAIBasedMDT_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTAIBasedMDT_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTAIBasedMDT_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTAIBasedMDT_ExtIEsClsSpec =
{



 &sz_ExtnTAIBasedMDT_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTAIBasedMDT_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTAIBasedMDT_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTAIBasedMDT_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTAIBasedMDT_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TAIBasedMDT_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTAIBasedMDT_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TAIBasedMDT_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TAIBasedMDT_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TAIBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TAIBasedMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TAIBasedMDT_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TAIBasedMDT_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TAIBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAIBasedMDT_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TAIBasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TAIBasedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAIBasedMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TAIBasedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTAIBasedMDTTkn[] =
{
 &szTAILstforMDT,
  &szTAI,
  &szConstTerm,
 &szOptProtExtnCont_TAIBasedMDT_ExtIEs,
  &szProtExtnField_TAIBasedMDT_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTAIBasedMDTspec =
{



 1,
 0,
 0L,
 0L,
 &szTAIBasedMDTTkn[0],
 0
};
 CmPAsnElmDef szTAIBasedMDT =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTAIBasedMDT),
 &flagSz3M,
 0,
 (U8 *)(&szTAIBasedMDTspec),
 0L
};
 CmPAsnElmDef *szAreaScopeOfMDTTkn[] =
{
 &szCellBasedMDT,
 &szTABasedMDT,
 &szNull,
 &szExtMkr,
 &szTAIBasedMDT,
 &szConstTerm
};
CmPAsnChoiceDef szAreaScopeOfMDTspec =
{



 3,
 1,
 &szAreaScopeOfMDTTkn[0]
};
CmPAsnElmDef szAreaScopeOfMDT =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztAreaScopeOfMDT),
 &flagSz3M,
 0L,
 (U8 *)(&szAreaScopeOfMDTspec),
 0L
};

CmPAsnUIntDef szPriorityLvlspec =
{



 0,
 15UL
};
CmPAsnElmDef szPriorityLvl =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztPriorityLvl),
 &flagSz3M,
 0,
 (U8 *)(&szPriorityLvlspec),
 0L
};


CmPAsnTknEnum szPre_emptionCapbltyLst[3] =
{
 2,
 SztPre_emptionCapbltyshall_not_trigger_pre_emptionEnum,
 SztPre_emptionCapbltymay_trigger_pre_emptionEnum
};
CmPAsnEnumDef szPre_emptionCapbltyspec =
{



 szPre_emptionCapbltyLst,
 0L
};
CmPAsnElmDef szPre_emptionCapblty =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztPre_emptionCapblty),
 &flagSz3M,
 0,
 (U8 *)(&szPre_emptionCapbltyspec),
 0L
};


CmPAsnTknEnum szPre_emptionVulnerabilityLst[3] =
{
 2,
 SztPre_emptionVulnerabilitynot_pre_emptableEnum,
 SztPre_emptionVulnerabilitypre_emptableEnum
};
CmPAsnEnumDef szPre_emptionVulnerabilityspec =
{



 szPre_emptionVulnerabilityLst,
 0L
};
CmPAsnElmDef szPre_emptionVulnerability =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztPre_emptionVulnerability),
 &flagSz3M,
 0,
 (U8 *)(&szPre_emptionVulnerabilityspec),
 0L
};

 CmPAsnElmDef *sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInfo =
{
 0,
 &sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnAllocnAndRetentionPriority_ExtIEsClsSpec =
{



 &sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnAllocnAndRetentionPriority_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnAllocnAndRetentionPriority_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnAllocnAndRetentionPriority_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_AllocnAndRetentionPriority_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnAllocnAndRetentionPriority_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_AllocnAndRetentionPriority_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_AllocnAndRetentionPriority_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_AllocnAndRetentionPriority_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_AllocnAndRetentionPriority_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_AllocnAndRetentionPriority_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_AllocnAndRetentionPriority_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_AllocnAndRetentionPriority_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_AllocnAndRetentionPriority_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szAllocnAndRetentionPriorityTkn[] =
{
 &szPriorityLvl,
 &szPre_emptionCapblty,
 &szPre_emptionVulnerability,
 &szOptProtExtnCont_AllocnAndRetentionPriority_ExtIEs,
  &szProtExtnField_AllocnAndRetentionPriority_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szAllocnAndRetentionPriorityspec =
{



 1,
 0,
 0L,
 0L,
 &szAllocnAndRetentionPriorityTkn[0],
 0
};
 CmPAsnElmDef szAllocnAndRetentionPriority =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztAllocnAndRetentionPriority),
 &flagSz3M,
 0,
 (U8 *)(&szAllocnAndRetentionPriorityspec),
 0L
};

CmPAsnUIntDef szE_RAB_IDspec =
{



 0,
 15UL
};
CmPAsnElmDef szE_RAB_ID =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(SztE_RAB_ID),
 &flagSz3M,
 0,
 (U8 *)(&szE_RAB_IDspec),
 0L
};


CmPAsnUIntDef szPDCP_SNspec =
{



 0,
 4095UL
};
CmPAsnElmDef szPDCP_SN =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztPDCP_SN),
 &flagSz3M,
 0,
 (U8 *)(&szPDCP_SNspec),
 0L
};


CmPAsnUIntDef szHFNspec =
{



 0,
 1048575UL
};
CmPAsnElmDef szHFN =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztHFN),
 &flagSz3M,
 0,
 (U8 *)(&szHFNspec),
 0L
};

 CmPAsnElmDef *sz_ExtnCOUNTvalue_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCOUNTvalue_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCOUNTvalue_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCOUNTvalue_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCOUNTvalue_ExtIEsClsSpec =
{



 &sz_ExtnCOUNTvalue_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCOUNTvalue_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCOUNTvalue_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCOUNTvalue_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCOUNTvalue_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_COUNTvalue_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCOUNTvalue_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_COUNTvalue_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_COUNTvalue_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_COUNTvalue_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_COUNTvalue_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_COUNTvalue_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_COUNTvalue_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_COUNTvalue_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_COUNTvalue_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_COUNTvalue_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_COUNTvalue_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_COUNTvalue_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_COUNTvalue_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCOUNTvalueTkn[] =
{
 &szPDCP_SN,
 &szHFN,
 &szOptProtExtnCont_COUNTvalue_ExtIEs,
  &szProtExtnField_COUNTvalue_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCOUNTvaluespec =
{



 1,
 0,
 0L,
 0L,
 &szCOUNTvalueTkn[0],
 0
};
 CmPAsnElmDef szCOUNTvalue =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCOUNTvalue),
 &flagSz3M,
 0,
 (U8 *)(&szCOUNTvaluespec),
 0L
};
CmPAsnBitStrDef szReceiveStatusofULPDCPSDUsspec =
{



 4096,
 4096
};
CmPAsnElmDef szOptReceiveStatusofULPDCPSDUs =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(SztReceiveStatusofULPDCPSDUs),
 &flagSz3O,
 0,
 (U8 *) (&szReceiveStatusofULPDCPSDUsspec),
 0L
};
CmPAsnElmDef szReceiveStatusofULPDCPSDUs =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(SztReceiveStatusofULPDCPSDUs),
 &flagSz3M,
 0,
 (U8 *) (&szReceiveStatusofULPDCPSDUsspec),
 0L
};

CmPAsnUIntDef szPDCP_SNExtendedspec =
{



 0,
 32767UL
};
CmPAsnElmDef szPDCP_SNExtended =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztPDCP_SNExtended),
 &flagSz3M,
 0,
 (U8 *)(&szPDCP_SNExtendedspec),
 0L
};


CmPAsnUIntDef szHFNMdfdspec =
{



 0,
 131071UL
};
CmPAsnElmDef szHFNMdfd =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztHFNMdfd),
 &flagSz3M,
 0,
 (U8 *)(&szHFNMdfdspec),
 0L
};

 CmPAsnElmDef *sz_ExtnCOUNTValueExtended_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCOUNTValueExtended_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCOUNTValueExtended_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCOUNTValueExtended_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCOUNTValueExtended_ExtIEsClsSpec =
{



 &sz_ExtnCOUNTValueExtended_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCOUNTValueExtended_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCOUNTValueExtended_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCOUNTValueExtended_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCOUNTValueExtended_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_COUNTValueExtended_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCOUNTValueExtended_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_COUNTValueExtended_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_COUNTValueExtended_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_COUNTValueExtended_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_COUNTValueExtended_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_COUNTValueExtended_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_COUNTValueExtended_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_COUNTValueExtended_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_COUNTValueExtended_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_COUNTValueExtended_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_COUNTValueExtended_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_COUNTValueExtended_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_COUNTValueExtended_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCOUNTValueExtendedTkn[] =
{
 &szPDCP_SNExtended,
 &szHFNMdfd,
 &szOptProtExtnCont_COUNTValueExtended_ExtIEs,
  &szProtExtnField_COUNTValueExtended_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCOUNTValueExtendedspec =
{



 1,
 0,
 0L,
 0L,
 &szCOUNTValueExtendedTkn[0],
 0
};
 CmPAsnElmDef szCOUNTValueExtended =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCOUNTValueExtended),
 &flagSz3M,
 0,
 (U8 *)(&szCOUNTValueExtendedspec),
 0L
};
CmPAsnBitStrDef szReceiveStatusOfULPDCPSDUsExtendedspec =
{



 1,
 16384
};
CmPAsnElmDef szReceiveStatusOfULPDCPSDUsExtended =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(SztReceiveStatusOfULPDCPSDUsExtended),
 &flagSz3M,
 0,
 (U8 *) (&szReceiveStatusOfULPDCPSDUsExtendedspec),
 0L
};
 CmPAsnElmDef *sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInst[] =
{
 &szCOUNTValueExtended,
 &szCOUNTValueExtended,
 &szReceiveStatusOfULPDCPSDUsExtended
};
 U32 sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInstId[] =
{
 179,
 180,
 181
};
 CmPAsnClassInfo sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInfo =
{
 3,
 &sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsSpec =
{



 &sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEsspec),
 0L
};
 CmPAsnElmDef *szBrs_SubjToStatusTfr_ItemTkn[] =
{
 &szE_RAB_ID,
 &szCOUNTvalue,
 &szCOUNTvalue,
 &szOptReceiveStatusofULPDCPSDUs,
 &szOptProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs,
  &szProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szBrs_SubjToStatusTfr_Itemspec =
{



 2,
 0,
 0L,
 0L,
 &szBrs_SubjToStatusTfr_ItemTkn[0],
 0
};
 CmPAsnElmDef szBrs_SubjToStatusTfr_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztBrs_SubjToStatusTfr_Item),
 &flagSz3M,
 0,
 (U8 *)(&szBrs_SubjToStatusTfr_Itemspec),
 0L
};
 CmPAsnElmDef *sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInst[] =
{
 &szBrs_SubjToStatusTfr_Item
};
 U32 sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInstId[] =
{
 89
};
SzMsgConInf szBrs_SubjToStatusTfr_ItemIEsConInf =
{
 {
  { 89, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInfo =
{
 1,
 &sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueBrs_SubjToStatusTfr_ItemIEsClsSpec =
{



 &sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueBrs_SubjToStatusTfr_ItemIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueBrs_SubjToStatusTfr_ItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueBrs_SubjToStatusTfr_ItemIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_Brs_SubjToStatusTfr_ItemIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueBrs_SubjToStatusTfr_ItemIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_Brs_SubjToStatusTfr_ItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_Brs_SubjToStatusTfr_ItemIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_Brs_SubjToStatusTfr_ItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_Brs_SubjToStatusTfr_ItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef szBrs_SubjToStatusTfrLstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szBrs_SubjToStatusTfrLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztBrs_SubjToStatusTfrLst),
 &flagSz3M,
 0,
 (U8 *) (&szBrs_SubjToStatusTfrLstspec),
 0L
};

CmPAsnUIntXLDef szBitRatespec =
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
CmPAsnElmDef szBitRate =
{



 CM_PASN_TET_UINTXL,
 0,
 sizeof(SztBitRate),
 &flagSz3M,
 0,
 (U8 *)(&szBitRatespec),
 0L
};

CmPAsnSetSeqOfDef szBPLMNsspec =
{



 1,
 6,
 3*sizeof(U32)
};
 CmPAsnElmDef szBPLMNs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztBPLMNs),
 &flagSz3M,
 0,
 (U8 *) (&szBPLMNsspec),
 0L
};

CmPAsnUIntDef szNumberOfBroadcastsspec =
{



 0,
 65535UL
};
CmPAsnElmDef szNumberOfBroadcasts =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztNumberOfBroadcasts),
 &flagSz3M,
 0,
 (U8 *)(&szNumberOfBroadcastsspec),
 0L
};

 CmPAsnElmDef *sz_ExtnCellID_Cancelled_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCellID_Cancelled_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCellID_Cancelled_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCellID_Cancelled_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCellID_Cancelled_Item_ExtIEsClsSpec =
{



 &sz_ExtnCellID_Cancelled_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCellID_Cancelled_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCellID_Cancelled_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCellID_Cancelled_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCellID_Cancelled_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CellID_Cancelled_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCellID_Cancelled_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CellID_Cancelled_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CellID_Cancelled_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CellID_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CellID_Cancelled_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CellID_Cancelled_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CellID_Cancelled_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CellID_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CellID_Cancelled_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CellID_Cancelled_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CellID_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CellID_Cancelled_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CellID_Cancelled_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCellID_Cancelled_ItemTkn[] =
{
 &szEUTRAN_CGI,
 &szNumberOfBroadcasts,
 &szOptProtExtnCont_CellID_Cancelled_Item_ExtIEs,
  &szProtExtnField_CellID_Cancelled_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCellID_Cancelled_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szCellID_Cancelled_ItemTkn[0],
 0
};
 CmPAsnElmDef szCellID_Cancelled_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCellID_Cancelled_Item),
 &flagSz3M,
 0,
 (U8 *)(&szCellID_Cancelled_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szCellID_Cancelledspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szCellID_Cancelled =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCellID_Cancelled),
 &flagSz3M,
 0,
 (U8 *) (&szCellID_Cancelledspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCancelledCellinTAI_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCancelledCellinTAI_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCancelledCellinTAI_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCancelledCellinTAI_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCancelledCellinTAI_Item_ExtIEsClsSpec =
{



 &sz_ExtnCancelledCellinTAI_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCancelledCellinTAI_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCancelledCellinTAI_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCancelledCellinTAI_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CancelledCellinTAI_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCancelledCellinTAI_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CancelledCellinTAI_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CancelledCellinTAI_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CancelledCellinTAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CancelledCellinTAI_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CancelledCellinTAI_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CancelledCellinTAI_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CancelledCellinTAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CancelledCellinTAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CancelledCellinTAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CancelledCellinTAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCancelledCellinTAI_ItemTkn[] =
{
 &szEUTRAN_CGI,
 &szNumberOfBroadcasts,
 &szOptProtExtnCont_CancelledCellinTAI_Item_ExtIEs,
  &szProtExtnField_CancelledCellinTAI_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCancelledCellinTAI_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szCancelledCellinTAI_ItemTkn[0],
 0
};
 CmPAsnElmDef szCancelledCellinTAI_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCancelledCellinTAI_Item),
 &flagSz3M,
 0,
 (U8 *)(&szCancelledCellinTAI_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szCancelledCellinTAIspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szCancelledCellinTAI =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCancelledCellinTAI),
 &flagSz3M,
 0,
 (U8 *) (&szCancelledCellinTAIspec),
 0L
};
 CmPAsnElmDef *sz_ExtnTAI_Cancelled_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTAI_Cancelled_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTAI_Cancelled_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTAI_Cancelled_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTAI_Cancelled_Item_ExtIEsClsSpec =
{



 &sz_ExtnTAI_Cancelled_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTAI_Cancelled_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTAI_Cancelled_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTAI_Cancelled_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTAI_Cancelled_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TAI_Cancelled_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTAI_Cancelled_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TAI_Cancelled_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TAI_Cancelled_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TAI_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TAI_Cancelled_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TAI_Cancelled_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TAI_Cancelled_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TAI_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAI_Cancelled_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TAI_Cancelled_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TAI_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAI_Cancelled_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TAI_Cancelled_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTAI_Cancelled_ItemTkn[] =
{
 &szTAI,
 &szCancelledCellinTAI,
  &szCancelledCellinTAI_Item,
  &szConstTerm,
 &szOptProtExtnCont_TAI_Cancelled_Item_ExtIEs,
  &szProtExtnField_TAI_Cancelled_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTAI_Cancelled_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szTAI_Cancelled_ItemTkn[0],
 0
};
 CmPAsnElmDef szTAI_Cancelled_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTAI_Cancelled_Item),
 &flagSz3M,
 0,
 (U8 *)(&szTAI_Cancelled_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szTAI_Cancelledspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szTAI_Cancelled =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztTAI_Cancelled),
 &flagSz3M,
 0,
 (U8 *) (&szTAI_Cancelledspec),
 0L
};
CmPAsnOctStrDef szEmergencyAreaIDspec =
{



 3,
 3
};
CmPAsnElmDef szEmergencyAreaID =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztEmergencyAreaID),
 &flagSz3M,
 0,
 (U8 *) (&szEmergencyAreaIDspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCancelledCellinEAI_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCancelledCellinEAI_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCancelledCellinEAI_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCancelledCellinEAI_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCancelledCellinEAI_Item_ExtIEsClsSpec =
{



 &sz_ExtnCancelledCellinEAI_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCancelledCellinEAI_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCancelledCellinEAI_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCancelledCellinEAI_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CancelledCellinEAI_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCancelledCellinEAI_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CancelledCellinEAI_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CancelledCellinEAI_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CancelledCellinEAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CancelledCellinEAI_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CancelledCellinEAI_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CancelledCellinEAI_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CancelledCellinEAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CancelledCellinEAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CancelledCellinEAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CancelledCellinEAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCancelledCellinEAI_ItemTkn[] =
{
 &szEUTRAN_CGI,
 &szNumberOfBroadcasts,
 &szOptProtExtnCont_CancelledCellinEAI_Item_ExtIEs,
  &szProtExtnField_CancelledCellinEAI_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCancelledCellinEAI_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szCancelledCellinEAI_ItemTkn[0],
 0
};
 CmPAsnElmDef szCancelledCellinEAI_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCancelledCellinEAI_Item),
 &flagSz3M,
 0,
 (U8 *)(&szCancelledCellinEAI_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szCancelledCellinEAIspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szCancelledCellinEAI =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCancelledCellinEAI),
 &flagSz3M,
 0,
 (U8 *) (&szCancelledCellinEAIspec),
 0L
};
 CmPAsnElmDef *sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsClsSpec =
{



 &sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szEmergencyAreaID_Cancelled_ItemTkn[] =
{
 &szEmergencyAreaID,
 &szCancelledCellinEAI,
  &szCancelledCellinEAI_Item,
  &szConstTerm,
 &szOptProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs,
  &szProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szEmergencyAreaID_Cancelled_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szEmergencyAreaID_Cancelled_ItemTkn[0],
 0
};
 CmPAsnElmDef szEmergencyAreaID_Cancelled_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztEmergencyAreaID_Cancelled_Item),
 &flagSz3M,
 0,
 (U8 *)(&szEmergencyAreaID_Cancelled_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szEmergencyAreaID_Cancelledspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szEmergencyAreaID_Cancelled =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztEmergencyAreaID_Cancelled),
 &flagSz3M,
 0,
 (U8 *) (&szEmergencyAreaID_Cancelledspec),
 0L
};
 CmPAsnElmDef *szBroadcastCancelledAreaLstTkn[] =
{
 &szCellID_Cancelled,
  &szCellID_Cancelled_Item,
  &szConstTerm,
 &szTAI_Cancelled,
  &szTAI_Cancelled_Item,
  &szConstTerm,
 &szEmergencyAreaID_Cancelled,
  &szEmergencyAreaID_Cancelled_Item,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szBroadcastCancelledAreaLstspec =
{



 3,
 0,
 &szBroadcastCancelledAreaLstTkn[0]
};
CmPAsnElmDef szBroadcastCancelledAreaLst =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztBroadcastCancelledAreaLst),
 &flagSz3M,
 0L,
 (U8 *)(&szBroadcastCancelledAreaLstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCellID_Broadcast_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCellID_Broadcast_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCellID_Broadcast_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCellID_Broadcast_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCellID_Broadcast_Item_ExtIEsClsSpec =
{



 &sz_ExtnCellID_Broadcast_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCellID_Broadcast_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCellID_Broadcast_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCellID_Broadcast_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCellID_Broadcast_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CellID_Broadcast_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCellID_Broadcast_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CellID_Broadcast_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CellID_Broadcast_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CellID_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CellID_Broadcast_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CellID_Broadcast_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CellID_Broadcast_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CellID_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CellID_Broadcast_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CellID_Broadcast_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CellID_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CellID_Broadcast_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CellID_Broadcast_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCellID_Broadcast_ItemTkn[] =
{
 &szEUTRAN_CGI,
 &szOptProtExtnCont_CellID_Broadcast_Item_ExtIEs,
  &szProtExtnField_CellID_Broadcast_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCellID_Broadcast_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szCellID_Broadcast_ItemTkn[0],
 0
};
 CmPAsnElmDef szCellID_Broadcast_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCellID_Broadcast_Item),
 &flagSz3M,
 0,
 (U8 *)(&szCellID_Broadcast_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szCellID_Broadcastspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szCellID_Broadcast =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCellID_Broadcast),
 &flagSz3M,
 0,
 (U8 *) (&szCellID_Broadcastspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCompletedCellinTAI_Item_ExtIEsClsSpec =
{



 &sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCompletedCellinTAI_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCompletedCellinTAI_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCompletedCellinTAI_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CompletedCellinTAI_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCompletedCellinTAI_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CompletedCellinTAI_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CompletedCellinTAI_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CompletedCellinTAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CompletedCellinTAI_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CompletedCellinTAI_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CompletedCellinTAI_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CompletedCellinTAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CompletedCellinTAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CompletedCellinTAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CompletedCellinTAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCompletedCellinTAI_ItemTkn[] =
{
 &szEUTRAN_CGI,
 &szOptProtExtnCont_CompletedCellinTAI_Item_ExtIEs,
  &szProtExtnField_CompletedCellinTAI_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCompletedCellinTAI_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szCompletedCellinTAI_ItemTkn[0],
 0
};
 CmPAsnElmDef szCompletedCellinTAI_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCompletedCellinTAI_Item),
 &flagSz3M,
 0,
 (U8 *)(&szCompletedCellinTAI_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szCompletedCellinTAIspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szCompletedCellinTAI =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCompletedCellinTAI),
 &flagSz3M,
 0,
 (U8 *) (&szCompletedCellinTAIspec),
 0L
};
 CmPAsnElmDef *sz_ExtnTAI_Broadcast_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTAI_Broadcast_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTAI_Broadcast_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTAI_Broadcast_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTAI_Broadcast_Item_ExtIEsClsSpec =
{



 &sz_ExtnTAI_Broadcast_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTAI_Broadcast_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTAI_Broadcast_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTAI_Broadcast_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTAI_Broadcast_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TAI_Broadcast_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTAI_Broadcast_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TAI_Broadcast_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TAI_Broadcast_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TAI_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TAI_Broadcast_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TAI_Broadcast_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TAI_Broadcast_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TAI_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAI_Broadcast_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TAI_Broadcast_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TAI_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAI_Broadcast_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TAI_Broadcast_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTAI_Broadcast_ItemTkn[] =
{
 &szTAI,
 &szCompletedCellinTAI,
  &szCompletedCellinTAI_Item,
  &szConstTerm,
 &szOptProtExtnCont_TAI_Broadcast_Item_ExtIEs,
  &szProtExtnField_TAI_Broadcast_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTAI_Broadcast_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szTAI_Broadcast_ItemTkn[0],
 0
};
 CmPAsnElmDef szTAI_Broadcast_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTAI_Broadcast_Item),
 &flagSz3M,
 0,
 (U8 *)(&szTAI_Broadcast_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szTAI_Broadcastspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szTAI_Broadcast =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztTAI_Broadcast),
 &flagSz3M,
 0,
 (U8 *) (&szTAI_Broadcastspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCompletedCellinEAI_Item_ExtIEsClsSpec =
{



 &sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCompletedCellinEAI_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCompletedCellinEAI_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCompletedCellinEAI_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CompletedCellinEAI_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCompletedCellinEAI_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CompletedCellinEAI_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CompletedCellinEAI_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CompletedCellinEAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CompletedCellinEAI_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CompletedCellinEAI_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CompletedCellinEAI_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CompletedCellinEAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CompletedCellinEAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CompletedCellinEAI_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CompletedCellinEAI_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCompletedCellinEAI_ItemTkn[] =
{
 &szEUTRAN_CGI,
 &szOptProtExtnCont_CompletedCellinEAI_Item_ExtIEs,
  &szProtExtnField_CompletedCellinEAI_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCompletedCellinEAI_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szCompletedCellinEAI_ItemTkn[0],
 0
};
 CmPAsnElmDef szCompletedCellinEAI_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCompletedCellinEAI_Item),
 &flagSz3M,
 0,
 (U8 *)(&szCompletedCellinEAI_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szCompletedCellinEAIspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szCompletedCellinEAI =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCompletedCellinEAI),
 &flagSz3M,
 0,
 (U8 *) (&szCompletedCellinEAIspec),
 0L
};
 CmPAsnElmDef *sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsSpec =
{



 &sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szEmergencyAreaID_Broadcast_ItemTkn[] =
{
 &szEmergencyAreaID,
 &szCompletedCellinEAI,
  &szCompletedCellinEAI_Item,
  &szConstTerm,
 &szOptProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs,
  &szProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szEmergencyAreaID_Broadcast_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szEmergencyAreaID_Broadcast_ItemTkn[0],
 0
};
 CmPAsnElmDef szEmergencyAreaID_Broadcast_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztEmergencyAreaID_Broadcast_Item),
 &flagSz3M,
 0,
 (U8 *)(&szEmergencyAreaID_Broadcast_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szEmergencyAreaID_Broadcastspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szEmergencyAreaID_Broadcast =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztEmergencyAreaID_Broadcast),
 &flagSz3M,
 0,
 (U8 *) (&szEmergencyAreaID_Broadcastspec),
 0L
};
 CmPAsnElmDef *szBroadcastCompletedAreaLstTkn[] =
{
 &szCellID_Broadcast,
  &szCellID_Broadcast_Item,
  &szConstTerm,
 &szTAI_Broadcast,
  &szTAI_Broadcast_Item,
  &szConstTerm,
 &szEmergencyAreaID_Broadcast,
  &szEmergencyAreaID_Broadcast_Item,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szBroadcastCompletedAreaLstspec =
{



 3,
 0,
 &szBroadcastCompletedAreaLstTkn[0]
};
CmPAsnElmDef szBroadcastCompletedAreaLst =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztBroadcastCompletedAreaLst),
 &flagSz3M,
 0L,
 (U8 *)(&szBroadcastCompletedAreaLstspec),
 0L
};

CmPAsnTknEnum szCauseRadioNwExtLst[4] =
{
 3,
 SztCauseRadioNwredirection_towards_1xRTTEnum,
 SztCauseRadioNwnot_supported_QCI_valueEnum,
 SztCauseRadioNwinvalid_CSG_IdEnum
};
CmPAsnTknEnum szCauseRadioNwLst[37] =
{
 36,
 SztCauseRadioNwunspecifiedEnum,
 SztCauseRadioNwtx2relocoverall_expiryEnum,
 SztCauseRadioNwsuccessful_handoverEnum,
 SztCauseRadioNwrelease_due_to_eutran_generated_reasonEnum,
 SztCauseRadioNwhandover_cancelledEnum,
 SztCauseRadioNwpartial_handoverEnum,
 SztCauseRadioNwho_failure_in_target_EPC_eNB_or_target_systemEnum,
 SztCauseRadioNwho_target_not_allowedEnum,
 SztCauseRadioNwtS1relocoverall_expiryEnum,
 SztCauseRadioNwtS1relocprep_expiryEnum,
 SztCauseRadioNwcell_not_availableEnum,
 SztCauseRadioNwunknown_targetIDEnum,
 SztCauseRadioNwno_radio_resources_available_in_target_cellEnum,
 SztCauseRadioNwunknown_mme_ue_s1ap_idEnum,
 SztCauseRadioNwunknown_enb_ue_s1ap_idEnum,
 SztCauseRadioNwunknown_pair_ue_s1ap_idEnum,
 SztCauseRadioNwhandover_desirable_for_radio_reasonEnum,
 SztCauseRadioNwtime_critical_handoverEnum,
 SztCauseRadioNwresource_optimisation_handoverEnum,
 SztCauseRadioNwreduce_load_in_serving_cellEnum,
 SztCauseRadioNwuser_inactivityEnum,
 SztCauseRadioNwradio_connection_with_ue_lostEnum,
 SztCauseRadioNwload_balancing_tau_requiredEnum,
 SztCauseRadioNwcs_fallback_triggeredEnum,
 SztCauseRadioNwue_not_available_for_ps_serviceEnum,
 SztCauseRadioNwradio_resources_not_availableEnum,
 SztCauseRadioNwfailure_in_radio_interface_procedureEnum,
 SztCauseRadioNwinvalid_qos_combinationEnum,
 SztCauseRadioNwinterrat_redirectionEnum,
 SztCauseRadioNwinteraction_with_other_procedureEnum,
 SztCauseRadioNwunknown_E_RAB_IDEnum,
 SztCauseRadioNwmultiple_E_RAB_ID_instancesEnum,
 SztCauseRadioNwencryption_and_or_integrity_protection_algorithms_not_supportedEnum,
 SztCauseRadioNws1_intra_system_handover_triggeredEnum,
 SztCauseRadioNws1_inter_system_handover_triggeredEnum,
 SztCauseRadioNwx2_handover_triggeredEnum
};
CmPAsnEnumDef szCauseRadioNwspec =
{



 szCauseRadioNwLst,
 szCauseRadioNwExtLst
};
CmPAsnElmDef szCauseRadioNw =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCauseRadioNw),
 &flagSz3M,
 0,
 (U8 *)(&szCauseRadioNwspec),
 0L
};


CmPAsnTknEnum szCauseTportLst[3] =
{
 2,
 SztCauseTporttransport_resource_unavailableEnum,
 SztCauseTportunspecifiedEnum
};
CmPAsnEnumDef szCauseTportspec =
{



 szCauseTportLst,
 0L
};
CmPAsnElmDef szCauseTport =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCauseTport),
 &flagSz3M,
 0,
 (U8 *)(&szCauseTportspec),
 0L
};


CmPAsnTknEnum szCauseNasExtLst[2] =
{
 1,
 SztCauseNascsg_subscription_expiryEnum
};
CmPAsnTknEnum szCauseNasLst[5] =
{
 4,
 SztCauseNasnormal_releaseEnum,
 SztCauseNasauthentication_failureEnum,
 SztCauseNasdetachEnum,
 SztCauseNasunspecifiedEnum
};
CmPAsnEnumDef szCauseNasspec =
{



 szCauseNasLst,
 szCauseNasExtLst
};
CmPAsnElmDef szCauseNas =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCauseNas),
 &flagSz3M,
 0,
 (U8 *)(&szCauseNasspec),
 0L
};


CmPAsnTknEnum szCauseProtLst[8] =
{
 7,
 SztCauseProttransfer_syntax_errorEnum,
 SztCauseProtabstract_syntax_error_rejectEnum,
 SztCauseProtabstract_syntax_error_ignore_and_notifyEnum,
 SztCauseProtmessage_not_compatible_with_receiver_stateEnum,
 SztCauseProtsemantic_errorEnum,
 SztCauseProtabstract_syntax_error_falsely_constructed_messageEnum,
 SztCauseProtunspecifiedEnum
};
CmPAsnEnumDef szCauseProtspec =
{



 szCauseProtLst,
 0L
};
CmPAsnElmDef szCauseProt =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCauseProt),
 &flagSz3M,
 0,
 (U8 *)(&szCauseProtspec),
 0L
};


CmPAsnTknEnum szCauseMiscLst[7] =
{
 6,
 SztCauseMisccontrol_processing_overloadEnum,
 SztCauseMiscnot_enough_user_plane_processing_resourcesEnum,
 SztCauseMischardware_failureEnum,
 SztCauseMiscom_interventionEnum,
 SztCauseMiscunspecifiedEnum,
 SztCauseMiscunknown_PLMNEnum
};
CmPAsnEnumDef szCauseMiscspec =
{



 szCauseMiscLst,
 0L
};
CmPAsnElmDef szCauseMisc =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCauseMisc),
 &flagSz3M,
 0,
 (U8 *)(&szCauseMiscspec),
 0L
};

 CmPAsnElmDef *szCauseTkn[] =
{
 &szCauseRadioNw,
 &szCauseTport,
 &szCauseNas,
 &szCauseProt,
 &szCauseMisc,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szCausespec =
{



 5,
 0,
 &szCauseTkn[0]
};
CmPAsnElmDef szCause =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztCause),
 &flagSz3M,
 0L,
 (U8 *)(&szCausespec),
 0L
};

CmPAsnTknEnum szCellAccessModeLst[2] =
{
 1,
 SztCellAccessModehybridEnum
};
CmPAsnEnumDef szCellAccessModespec =
{



 szCellAccessModeLst,
 0L
};
CmPAsnElmDef szCellAccessMode =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCellAccessMode),
 &flagSz3M,
 0,
 (U8 *)(&szCellAccessModespec),
 0L
};

CmPAsnOctStrDef szCdma2000PDUspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szCdma2000PDU =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztCdma2000PDU),
 &flagSz3M,
 0,
 (U8 *) (&szCdma2000PDUspec),
 0L
};

CmPAsnTknEnum szCdma2000RATTypLst[3] =
{
 2,
 SztCdma2000RATTyphRPDEnum,
 SztCdma2000RATTyponexRTTEnum
};
CmPAsnEnumDef szCdma2000RATTypspec =
{



 szCdma2000RATTypLst,
 0L
};
CmPAsnElmDef szCdma2000RATTyp =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCdma2000RATTyp),
 &flagSz3M,
 0,
 (U8 *)(&szCdma2000RATTypspec),
 0L
};

CmPAsnOctStrDef szCdma2000SectorIDspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szCdma2000SectorID =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztCdma2000SectorID),
 &flagSz3M,
 0,
 (U8 *) (&szCdma2000SectorIDspec),
 0L
};

CmPAsnTknEnum szCdma2000HOStatusLst[3] =
{
 2,
 SztCdma2000HOStatushOSuccessEnum,
 SztCdma2000HOStatushOFailEnum
};
CmPAsnEnumDef szCdma2000HOStatusspec =
{



 szCdma2000HOStatusLst,
 0L
};
CmPAsnElmDef szCdma2000HOStatus =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCdma2000HOStatus),
 &flagSz3M,
 0,
 (U8 *)(&szCdma2000HOStatusspec),
 0L
};


CmPAsnTknEnum szCdma2000HOReqdIndLst[2] =
{
 1,
 SztCdma2000HOReqdIndtrueEnum
};
CmPAsnEnumDef szCdma2000HOReqdIndspec =
{



 szCdma2000HOReqdIndLst,
 0L
};
CmPAsnElmDef szCdma2000HOReqdInd =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCdma2000HOReqdInd),
 &flagSz3M,
 0,
 (U8 *)(&szCdma2000HOReqdIndspec),
 0L
};

CmPAsnOctStrDef szCdma2000OneXMEIDspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szCdma2000OneXMEID =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztCdma2000OneXMEID),
 &flagSz3M,
 0,
 (U8 *) (&szCdma2000OneXMEIDspec),
 0L
};
CmPAsnOctStrDef szCdma2000OneXMSIspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szCdma2000OneXMSI =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztCdma2000OneXMSI),
 &flagSz3M,
 0,
 (U8 *) (&szCdma2000OneXMSIspec),
 0L
};
CmPAsnOctStrDef szCdma2000OneXPilotspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szCdma2000OneXPilot =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztCdma2000OneXPilot),
 &flagSz3M,
 0,
 (U8 *) (&szCdma2000OneXPilotspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsSpec =
{



 &sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCdma2000OneXSRVCCInfoTkn[] =
{
 &szCdma2000OneXMEID,
 &szCdma2000OneXMSI,
 &szCdma2000OneXPilot,
 &szOptProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs,
  &szProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCdma2000OneXSRVCCInfospec =
{



 1,
 0,
 0L,
 0L,
 &szCdma2000OneXSRVCCInfoTkn[0],
 0
};
 CmPAsnElmDef szCdma2000OneXSRVCCInfo =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCdma2000OneXSRVCCInfo),
 &flagSz3M,
 0,
 (U8 *)(&szCdma2000OneXSRVCCInfospec),
 0L
};
CmPAsnOctStrDef szCdma2000OneXRANDspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szCdma2000OneXRAND =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztCdma2000OneXRAND),
 &flagSz3M,
 0,
 (U8 *) (&szCdma2000OneXRANDspec),
 0L
};

CmPAsnTknEnum szCell_SizeLst[5] =
{
 4,
 SztCell_SizeverysmallEnum,
 SztCell_SizesmallEnum,
 SztCell_SizemediumEnum,
 SztCell_SizelargeEnum
};
CmPAsnEnumDef szCell_Sizespec =
{



 szCell_SizeLst,
 0L
};
CmPAsnElmDef szCell_Size =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCell_Size),
 &flagSz3M,
 0,
 (U8 *)(&szCell_Sizespec),
 0L
};

 CmPAsnElmDef *sz_ExtnCellTyp_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCellTyp_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCellTyp_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCellTyp_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCellTyp_ExtIEsClsSpec =
{



 &sz_ExtnCellTyp_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCellTyp_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCellTyp_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCellTyp_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCellTyp_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CellTyp_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCellTyp_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CellTyp_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CellTyp_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CellTyp_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CellTyp_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CellTyp_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CellTyp_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CellTyp_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CellTyp_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CellTyp_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CellTyp_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CellTyp_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CellTyp_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCellTypTkn[] =
{
 &szCell_Size,
 &szOptProtExtnCont_CellTyp_ExtIEs,
  &szProtExtnField_CellTyp_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCellTypspec =
{



 1,
 0,
 0L,
 0L,
 &szCellTypTkn[0],
 0
};
 CmPAsnElmDef szCellTyp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCellTyp),
 &flagSz3M,
 0,
 (U8 *)(&szCellTypspec),
 0L
};
CmPAsnOctStrDef szLACspec =
{



 2,
 2
};
CmPAsnElmDef szLAC =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztLAC),
 &flagSz3M,
 0,
 (U8 *) (&szLACspec),
 0L
};
CmPAsnOctStrDef szCIspec =
{



 2,
 2
};
CmPAsnElmDef szCI =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztCI),
 &flagSz3M,
 0,
 (U8 *) (&szCIspec),
 0L
};
CmPAsnOctStrDef szRACspec =
{



 1,
 1
};
CmPAsnElmDef szOptRAC =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztRAC),
 &flagSz3O,
 0,
 (U8 *) (&szRACspec),
 0L
};
CmPAsnElmDef szRAC =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztRAC),
 &flagSz3M,
 0,
 (U8 *) (&szRACspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCGI_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCGI_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCGI_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCGI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCGI_ExtIEsClsSpec =
{



 &sz_ExtnCGI_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCGI_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCGI_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCGI_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCGI_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CGI_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCGI_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CGI_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CGI_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CGI_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CGI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CGI_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CGI_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CGI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CGI_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CGI_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CGI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CGI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CGI_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCGITkn[] =
{
 &szTBCD_STRING,
 &szLAC,
 &szCI,
 &szOptRAC,
 &szOptProtExtnCont_CGI_ExtIEs,
  &szProtExtnField_CGI_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCGIspec =
{



 2,
 0,
 0L,
 0L,
 &szCGITkn[0],
 0
};
 CmPAsnElmDef szCGI =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCGI),
 &flagSz3M,
 0,
 (U8 *)(&szCGIspec),
 0L
};

CmPAsnTknEnum szCNDomainLst[3] =
{
 2,
 SztCNDomainpsEnum,
 SztCNDomaincsEnum
};
CmPAsnEnumDef szCNDomainspec =
{



 szCNDomainLst,
 0L
};
CmPAsnElmDef szCNDomain =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztCNDomain),
 &flagSz3M,
 0,
 (U8 *)(&szCNDomainspec),
 0L
};


CmPAsnTknEnum szConcurrentWarningMsgIndicatorLst[2] =
{
 1,
 SztConcurrentWarningMsgIndicatortrueEnum
};
CmPAsnEnumDef szConcurrentWarningMsgIndicatorspec =
{



 szConcurrentWarningMsgIndicatorLst,
 0L
};
CmPAsnElmDef szConcurrentWarningMsgIndicator =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztConcurrentWarningMsgIndicator),
 &flagSz3M,
 0,
 (U8 *)(&szConcurrentWarningMsgIndicatorspec),
 0L
};

CmPAsnOctStrDef szCorrelation_IDspec =
{



 4,
 4
};
CmPAsnElmDef szCorrelation_ID =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztCorrelation_ID),
 &flagSz3M,
 0,
 (U8 *) (&szCorrelation_IDspec),
 0L
};

CmPAsnTknEnum szCSFallbackIndicatorExtLst[2] =
{
 1,
 SztCSFallbackIndicatorcs_fallback_high_priorityEnum
};
CmPAsnTknEnum szCSFallbackIndicatorLst[2] =
{
 1,
 SztCSFallbackIndicatorcs_fallback_requiredEnum
};
CmPAsnEnumDef szCSFallbackIndicatorspec =
{



 szCSFallbackIndicatorLst,
 szCSFallbackIndicatorExtLst
};
CmPAsnElmDef szCSFallbackIndicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztCSFallbackIndicator),
 &flagSz3M,
 0,
 (U8 *)(&szCSFallbackIndicatorspec),
 0L
};

CmPAsnBitStrDef szCSG_Idspec =
{



 27,
 27
};
CmPAsnElmDef szCSG_Id =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztCSG_Id),
 &flagSz3M,
 0,
 (U8 *) (&szCSG_Idspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCSG_IdLst_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCSG_IdLst_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCSG_IdLst_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCSG_IdLst_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCSG_IdLst_Item_ExtIEsClsSpec =
{



 &sz_ExtnCSG_IdLst_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCSG_IdLst_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCSG_IdLst_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCSG_IdLst_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCSG_IdLst_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CSG_IdLst_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCSG_IdLst_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CSG_IdLst_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CSG_IdLst_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CSG_IdLst_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CSG_IdLst_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CSG_IdLst_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CSG_IdLst_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CSG_IdLst_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CSG_IdLst_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CSG_IdLst_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CSG_IdLst_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CSG_IdLst_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CSG_IdLst_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCSG_IdLst_ItemTkn[] =
{
 &szCSG_Id,
 &szOptProtExtnCont_CSG_IdLst_Item_ExtIEs,
  &szProtExtnField_CSG_IdLst_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCSG_IdLst_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szCSG_IdLst_ItemTkn[0],
 0
};
 CmPAsnElmDef szCSG_IdLst_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCSG_IdLst_Item),
 &flagSz3M,
 0,
 (U8 *)(&szCSG_IdLst_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szCSG_IdLstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szCSG_IdLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCSG_IdLst),
 &flagSz3M,
 0,
 (U8 *) (&szCSG_IdLstspec),
 0L
};

CmPAsnTknEnum szCSGMembershipStatusLst[3] =
{
 2,
 SztCSGMembershipStatusmemberEnum,
 SztCSGMembershipStatusnot_memberEnum
};
CmPAsnEnumDef szCSGMembershipStatusspec =
{



 szCSGMembershipStatusLst,
 0L
};
CmPAsnElmDef szCSGMembershipStatus =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztCSGMembershipStatus),
 &flagSz3M,
 0,
 (U8 *)(&szCSGMembershipStatusspec),
 0L
};


CmPAsnTknEnum szTypOfErrLst[3] =
{
 2,
 SztTypOfErrnot_understoodEnum,
 SztTypOfErrmissingEnum
};
CmPAsnEnumDef szTypOfErrspec =
{



 szTypOfErrLst,
 0L
};
CmPAsnElmDef szTypOfErr =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztTypOfErr),
 &flagSz3M,
 0,
 (U8 *)(&szTypOfErrspec),
 0L
};

 CmPAsnElmDef *sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsSpec =
{



 &sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCriticalityDiag_IE_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCriticalityDiag_IE_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CriticalityDiag_IE_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCriticalityDiag_IE_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CriticalityDiag_IE_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CriticalityDiag_IE_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CriticalityDiag_IE_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CriticalityDiag_IE_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CriticalityDiag_IE_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CriticalityDiag_IE_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CriticalityDiag_IE_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CriticalityDiag_IE_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CriticalityDiag_IE_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCriticalityDiag_IE_ItemTkn[] =
{
 &szCriticality,
 &szProtIE_ID,
 &szTypOfErr,
 &szOptProtExtnCont_CriticalityDiag_IE_Item_ExtIEs,
  &szProtExtnField_CriticalityDiag_IE_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCriticalityDiag_IE_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szCriticalityDiag_IE_ItemTkn[0],
 0
};
 CmPAsnElmDef szCriticalityDiag_IE_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCriticalityDiag_IE_Item),
 &flagSz3M,
 0,
 (U8 *)(&szCriticalityDiag_IE_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szCriticalityDiag_IE_Lstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptCriticalityDiag_IE_Lst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztCriticalityDiag_IE_Lst),
 &flagSz3O,
 0,
 (U8 *) (&szCriticalityDiag_IE_Lstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnCriticalityDiag_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnCriticalityDiag_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnCriticalityDiag_ExtIEsClsInfo =
{
 0,
 &sz_ExtnCriticalityDiag_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnCriticalityDiag_ExtIEsClsSpec =
{



 &sz_ExtnCriticalityDiag_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnCriticalityDiag_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnCriticalityDiag_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnCriticalityDiag_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnCriticalityDiag_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_CriticalityDiag_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnCriticalityDiag_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_CriticalityDiag_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_CriticalityDiag_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_CriticalityDiag_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_CriticalityDiag_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_CriticalityDiag_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_CriticalityDiag_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_CriticalityDiag_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CriticalityDiag_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_CriticalityDiag_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_CriticalityDiag_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_CriticalityDiag_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_CriticalityDiag_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szCriticalityDiagTkn[] =
{
 &szOptProcedureCode,
 &szOptTrgMsg,
 &szOptCriticality,
 &szOptCriticalityDiag_IE_Lst,
  &szCriticalityDiag_IE_Item,
  &szConstTerm,
 &szOptProtExtnCont_CriticalityDiag_ExtIEs,
  &szProtExtnField_CriticalityDiag_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCriticalityDiagspec =
{



 5,
 0,
 0L,
 0L,
 &szCriticalityDiagTkn[0],
 0
};
 CmPAsnElmDef szCriticalityDiag =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCriticalityDiag),
 &flagSz3M,
 0,
 (U8 *)(&szCriticalityDiagspec),
 0L
};
CmPAsnBitStrDef szDataCodingSchemespec =
{



 8,
 8
};
CmPAsnElmDef szDataCodingScheme =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztDataCodingScheme),
 &flagSz3M,
 0,
 (U8 *) (&szDataCodingSchemespec),
 0L
};

CmPAsnTknEnum szDL_FwdingLst[2] =
{
 1,
 SztDL_FwdingdL_Fwding_proposedEnum
};
CmPAsnEnumDef szDL_Fwdingspec =
{



 szDL_FwdingLst,
 0L
};
CmPAsnElmDef szOptDL_Fwding =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztDL_Fwding),
 &flagSz3O,
 0,
 (U8 *)(&szDL_Fwdingspec),
 0L
};


CmPAsnTknEnum szDirect_Fwding_Path_AvlbltyLst[2] =
{
 1,
 SztDirect_Fwding_Path_AvlbltydirectPathAvailableEnum
};
CmPAsnEnumDef szDirect_Fwding_Path_Avlbltyspec =
{



 szDirect_Fwding_Path_AvlbltyLst,
 0L
};
CmPAsnElmDef szDirect_Fwding_Path_Avlblty =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztDirect_Fwding_Path_Avlblty),
 &flagSz3M,
 0,
 (U8 *)(&szDirect_Fwding_Path_Avlbltyspec),
 0L
};


CmPAsnTknEnum szData_Fwding_Not_PossibleLst[2] =
{
 1,
 SztData_Fwding_Not_Possibledata_Fwding_not_PossibleEnum
};
CmPAsnEnumDef szData_Fwding_Not_Possiblespec =
{



 szData_Fwding_Not_PossibleLst,
 0L
};
CmPAsnElmDef szData_Fwding_Not_Possible =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztData_Fwding_Not_Possible),
 &flagSz3M,
 0,
 (U8 *)(&szData_Fwding_Not_Possiblespec),
 0L
};

CmPAsnSetSeqOfDef szECGILstspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szECGILst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztECGILst),
 &flagSz3M,
 0,
 (U8 *) (&szECGILstspec),
 0L
};
CmPAsnSetSeqOfDef szEmergencyAreaIDLstspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szEmergencyAreaIDLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztEmergencyAreaIDLst),
 &flagSz3M,
 0,
 (U8 *) (&szEmergencyAreaIDLstspec),
 0L
};
CmPAsnBitStrDef szENB_IDmacroENB_IDspec =
{



 20,
 20
};
CmPAsnElmDef szENB_IDmacroENB_ID =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztENB_IDmacroENB_ID),
 &flagSz3M,
 0,
 (U8 *) (&szENB_IDmacroENB_IDspec),
 0L
};
CmPAsnBitStrDef szENB_IDhomeENB_IDspec =
{



 28,
 28
};
CmPAsnElmDef szENB_IDhomeENB_ID =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztENB_IDhomeENB_ID),
 &flagSz3M,
 0,
 (U8 *) (&szENB_IDhomeENB_IDspec),
 0L
};
 CmPAsnElmDef *szENB_IDTkn[] =
{
 &szENB_IDmacroENB_ID,
 &szENB_IDhomeENB_ID,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szENB_IDspec =
{



 2,
 0,
 &szENB_IDTkn[0]
};
CmPAsnElmDef szENB_ID =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztENB_ID),
 &flagSz3M,
 0L,
 (U8 *)(&szENB_IDspec),
 0L
};
 CmPAsnElmDef *sz_ExtnLAI_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnLAI_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnLAI_ExtIEsClsInfo =
{
 0,
 &sz_ExtnLAI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnLAI_ExtIEsClsSpec =
{



 &sz_ExtnLAI_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnLAI_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnLAI_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnLAI_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnLAI_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_LAI_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnLAI_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_LAI_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_LAI_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_LAI_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_LAI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_LAI_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_LAI_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_LAI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_LAI_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_LAI_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_LAI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_LAI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_LAI_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szLAITkn[] =
{
 &szTBCD_STRING,
 &szLAC,
 &szOptProtExtnCont_LAI_ExtIEs,
  &szProtExtnField_LAI_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szLAIspec =
{



 1,
 0,
 0L,
 0L,
 &szLAITkn[0],
 0
};
 CmPAsnElmDef szLAI =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztLAI),
 &flagSz3M,
 0,
 (U8 *)(&szLAIspec),
 0L
};
 CmPAsnElmDef *sz_ExtnGERAN_Cell_ID_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnGERAN_Cell_ID_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnGERAN_Cell_ID_ExtIEsClsInfo =
{
 0,
 &sz_ExtnGERAN_Cell_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnGERAN_Cell_ID_ExtIEsClsSpec =
{



 &sz_ExtnGERAN_Cell_ID_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnGERAN_Cell_ID_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnGERAN_Cell_ID_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnGERAN_Cell_ID_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnGERAN_Cell_ID_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_GERAN_Cell_ID_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnGERAN_Cell_ID_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_GERAN_Cell_ID_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_GERAN_Cell_ID_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_GERAN_Cell_ID_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_GERAN_Cell_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_GERAN_Cell_ID_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_GERAN_Cell_ID_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_GERAN_Cell_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_GERAN_Cell_ID_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_GERAN_Cell_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_GERAN_Cell_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_GERAN_Cell_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_GERAN_Cell_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szGERAN_Cell_IDTkn[] =
{
 &szLAI,
 &szRAC,
 &szCI,
 &szOptProtExtnCont_GERAN_Cell_ID_ExtIEs,
  &szProtExtnField_GERAN_Cell_ID_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szGERAN_Cell_IDspec =
{



 1,
 0,
 0L,
 0L,
 &szGERAN_Cell_IDTkn[0],
 0
};
 CmPAsnElmDef szGERAN_Cell_ID =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztGERAN_Cell_ID),
 &flagSz3M,
 0,
 (U8 *)(&szGERAN_Cell_IDspec),
 0L
};
 CmPAsnElmDef *sz_ExtnGlobalENB_ID_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnGlobalENB_ID_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnGlobalENB_ID_ExtIEsClsInfo =
{
 0,
 &sz_ExtnGlobalENB_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnGlobalENB_ID_ExtIEsClsSpec =
{



 &sz_ExtnGlobalENB_ID_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnGlobalENB_ID_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnGlobalENB_ID_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnGlobalENB_ID_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnGlobalENB_ID_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_GlobalENB_ID_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnGlobalENB_ID_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_GlobalENB_ID_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_GlobalENB_ID_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_GlobalENB_ID_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_GlobalENB_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_GlobalENB_ID_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_GlobalENB_ID_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_GlobalENB_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_GlobalENB_ID_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_GlobalENB_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_GlobalENB_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_GlobalENB_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_GlobalENB_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szGlobal_ENB_IDTkn[] =
{
 &szTBCD_STRING,
 &szENB_ID,
 &szOptProtExtnCont_GlobalENB_ID_ExtIEs,
  &szProtExtnField_GlobalENB_ID_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szGlobal_ENB_IDspec =
{



 1,
 0,
 0L,
 0L,
 &szGlobal_ENB_IDTkn[0],
 0
};
 CmPAsnElmDef szGlobal_ENB_ID =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztGlobal_ENB_ID),
 &flagSz3M,
 0,
 (U8 *)(&szGlobal_ENB_IDspec),
 0L
};
CmPAsnOctStrDef szMME_Group_IDspec =
{



 2,
 2
};
CmPAsnElmDef szMME_Group_ID =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztMME_Group_ID),
 &flagSz3M,
 0,
 (U8 *) (&szMME_Group_IDspec),
 0L
};
CmPAsnOctStrDef szMME_Codespec =
{



 1,
 1
};
CmPAsnElmDef szMME_Code =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztMME_Code),
 &flagSz3M,
 0,
 (U8 *) (&szMME_Codespec),
 0L
};
 CmPAsnElmDef *sz_ExtnGUMMEI_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnGUMMEI_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnGUMMEI_ExtIEsClsInfo =
{
 0,
 &sz_ExtnGUMMEI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnGUMMEI_ExtIEsClsSpec =
{



 &sz_ExtnGUMMEI_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnGUMMEI_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnGUMMEI_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnGUMMEI_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnGUMMEI_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_GUMMEI_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnGUMMEI_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_GUMMEI_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_GUMMEI_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_GUMMEI_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_GUMMEI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_GUMMEI_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_GUMMEI_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_GUMMEI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_GUMMEI_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_GUMMEI_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_GUMMEI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_GUMMEI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_GUMMEI_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szGUMMEITkn[] =
{
 &szTBCD_STRING,
 &szMME_Group_ID,
 &szMME_Code,
 &szOptProtExtnCont_GUMMEI_ExtIEs,
  &szProtExtnField_GUMMEI_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szGUMMEIspec =
{



 1,
 0,
 0L,
 0L,
 &szGUMMEITkn[0],
 0
};
 CmPAsnElmDef szGUMMEI =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztGUMMEI),
 &flagSz3M,
 0,
 (U8 *)(&szGUMMEIspec),
 0L
};
CmPAsnSetSeqOfDef szGUMMEILstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szGUMMEILst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztGUMMEILst),
 &flagSz3M,
 0,
 (U8 *) (&szGUMMEILstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInfo =
{
 0,
 &sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsSpec =
{



 &sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnENB_StatusTfr_TprntCont_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnENB_StatusTfr_TprntCont_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnENB_StatusTfr_TprntCont_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szENB_StatusTfr_TprntContTkn[] =
{
 &szBrs_SubjToStatusTfrLst,
  &szProtIE_Field_Brs_SubjToStatusTfr_ItemIEs,
  &szConstTerm,
 &szOptProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs,
  &szProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szENB_StatusTfr_TprntContspec =
{



 1,
 0,
 0L,
 0L,
 &szENB_StatusTfr_TprntContTkn[0],
 0
};
 CmPAsnElmDef szENB_StatusTfr_TprntCont =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztENB_StatusTfr_TprntCont),
 &flagSz3M,
 0,
 (U8 *)(&szENB_StatusTfr_TprntContspec),
 0L
};

CmPAsnUIntDef szENB_UE_S1AP_IDspec =
{



 0,
 16777215UL
};
CmPAsnElmDef szENB_UE_S1AP_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztENB_UE_S1AP_ID),
 &flagSz3M,
 0,
 (U8 *)(&szENB_UE_S1AP_IDspec),
 0L
};
CmPAsnElmDef szOptENB_UE_S1AP_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztENB_UE_S1AP_ID),
 &flagSz3O,
 0,
 (U8 *)(&szENB_UE_S1AP_IDspec),
 0L
};

U32 szENBnameAlpLst[] = {74 , ' ', '\'', '(', ')', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', '=', '?', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
CmPAsnMulStrDef szENBnamespec =
{



 szENBnameAlpLst,
 150,
 1,
 122,
 32
};
CmPAsnElmDef szENBname =
{



 CM_PASN_TET_PRNSTRXL,
 1,
 sizeof(SztENBname),
 &flagSz3M,
 0,
 (U8 *) (&szENBnamespec),
 0L
};
CmPAsnBitStrDef szTportLyrAddrspec =
{



 1,
 160
};
CmPAsnElmDef szOptTportLyrAddr =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(SztTportLyrAddr),
 &flagSz3O,
 0,
 (U8 *) (&szTportLyrAddrspec),
 0L
};
CmPAsnElmDef szTportLyrAddr =
{



 CM_PASN_TET_BITSTRXL,
 1,
 sizeof(SztTportLyrAddr),
 &flagSz3M,
 0,
 (U8 *) (&szTportLyrAddrspec),
 0L
};
CmPAsnSetSeqOfDef szENBX2TLAsspec =
{



 1,
 2,
 3*sizeof(U32)
};
 CmPAsnElmDef szENBX2TLAs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztENBX2TLAs),
 &flagSz3M,
 0,
 (U8 *) (&szENBX2TLAsspec),
 0L
};
CmPAsnBitStrDef szEncryptionAlgorithmsspec =
{



 16,
 16
};
CmPAsnElmDef szEncryptionAlgorithms =
{



 CM_PASN_TET_BITSTR,
 1,
 sizeof(SztEncryptionAlgorithms),
 &flagSz3M,
 0,
 (U8 *) (&szEncryptionAlgorithmsspec),
 0L
};
CmPAsnSetSeqOfDef szEPLMNsspec =
{



 1,
 15,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptEPLMNs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztEPLMNs),
 &flagSz3O,
 0,
 (U8 *) (&szEPLMNsspec),
 0L
};

CmPAsnTknEnum szEventTypLst[4] =
{
 3,
 SztEventTypdirectEnum,
 SztEventTypchange_of_serve_cellEnum,
 SztEventTypstop_change_of_serve_cellEnum
};
CmPAsnEnumDef szEventTypspec =
{



 szEventTypLst,
 0L
};
CmPAsnElmDef szEventTyp =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztEventTyp),
 &flagSz3M,
 0,
 (U8 *)(&szEventTypspec),
 0L
};

 CmPAsnElmDef *sz_ExtnE_RABInformLstItem_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABInformLstItem_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABInformLstItem_ExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABInformLstItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABInformLstItem_ExtIEsClsSpec =
{



 &sz_ExtnE_RABInformLstItem_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABInformLstItem_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABInformLstItem_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABInformLstItem_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABInformLstItem_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABInformLstItem_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABInformLstItem_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABInformLstItem_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABInformLstItem_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABInformLstItem_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABInformLstItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABInformLstItem_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABInformLstItem_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABInformLstItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABInformLstItem_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABInformLstItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABInformLstItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABInformLstItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABInformLstItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABInformLstItemTkn[] =
{
 &szE_RAB_ID,
 &szOptDL_Fwding,
 &szOptProtExtnCont_E_RABInformLstItem_ExtIEs,
  &szProtExtnField_E_RABInformLstItem_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABInformLstItemspec =
{



 2,
 0,
 0L,
 0L,
 &szE_RABInformLstItemTkn[0],
 0
};
 CmPAsnElmDef szE_RABInformLstItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABInformLstItem),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABInformLstItemspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABInformLstIEsClsInst[] =
{
 &szE_RABInformLstItem
};
 U32 sz_ValueE_RABInformLstIEsClsInstId[] =
{
 78
};
SzMsgConInf szE_RABInformLstIEsConInf =
{
 {
  { 78, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABInformLstIEsClsInfo =
{
 1,
 &sz_ValueE_RABInformLstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABInformLstIEsClsSpec =
{



 &sz_ValueE_RABInformLstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABInformLstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABInformLstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABInformLstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABInformLstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABInformLstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABInformLstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABInformLstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABInformLstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABInformLstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABInformLstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABInformLstIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABInformLstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptE_RABInformLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABInformLst),
 &flagSz3O,
 0,
 (U8 *) (&szE_RABInformLstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABItem_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABItem_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABItem_ExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABItem_ExtIEsClsSpec =
{



 &sz_ExtnE_RABItem_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABItem_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABItem_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABItem_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABItem_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABItem_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABItem_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABItem_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABItem_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABItem_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABItem_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABItem_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABItem_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABItemTkn[] =
{
 &szE_RAB_ID,
 &szCause,
 &szOptProtExtnCont_E_RABItem_ExtIEs,
  &szProtExtnField_E_RABItem_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABItemspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABItemTkn[0],
 0
};
 CmPAsnElmDef szE_RABItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABItem),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABItemspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABItemIEsClsInst[] =
{
 &szE_RABItem
};
 U32 sz_ValueE_RABItemIEsClsInstId[] =
{
 35
};
SzMsgConInf szE_RABItemIEsConInf =
{
 {
  { 35, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABItemIEsClsInfo =
{
 1,
 &sz_ValueE_RABItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABItemIEsClsSpec =
{



 &sz_ValueE_RABItemIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABItemIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABItemIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABItemIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABItemIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABItemIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABItemIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABItemIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABLstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szE_RABLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABLst),
 &flagSz3M,
 0,
 (U8 *) (&szE_RABLstspec),
 0L
};

CmPAsnUIntDef szQCIspec =
{



 0,
 255UL
};
CmPAsnElmDef szQCI =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztQCI),
 &flagSz3M,
 0,
 (U8 *)(&szQCIspec),
 0L
};

 CmPAsnElmDef *sz_ExtnGBR_QosInform_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnGBR_QosInform_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnGBR_QosInform_ExtIEsClsInfo =
{
 0,
 &sz_ExtnGBR_QosInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnGBR_QosInform_ExtIEsClsSpec =
{



 &sz_ExtnGBR_QosInform_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnGBR_QosInform_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnGBR_QosInform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnGBR_QosInform_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnGBR_QosInform_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_GBR_QosInform_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnGBR_QosInform_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_GBR_QosInform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_GBR_QosInform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_GBR_QosInform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_GBR_QosInform_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_GBR_QosInform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_GBR_QosInform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_GBR_QosInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_GBR_QosInform_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_GBR_QosInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_GBR_QosInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_GBR_QosInform_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_GBR_QosInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szGBR_QosInformTkn[] =
{
 &szBitRate,
 &szBitRate,
 &szBitRate,
 &szBitRate,
 &szOptProtExtnCont_GBR_QosInform_ExtIEs,
  &szProtExtnField_GBR_QosInform_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szGBR_QosInformspec =
{



 1,
 0,
 0L,
 0L,
 &szGBR_QosInformTkn[0],
 0
};
 CmPAsnElmDef szGBR_QosInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztGBR_QosInform),
 &flagSz3M,
 0,
 (U8 *)(&szGBR_QosInformspec),
 0L
};
 CmPAsnElmDef szOptGBR_QosInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztGBR_QosInform),
 &flagSz3O,
 0,
 (U8 *)(&szGBR_QosInformspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABQoSParams_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABQoSParams_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABQoSParams_ExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABQoSParams_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABQoSParams_ExtIEsClsSpec =
{



 &sz_ExtnE_RABQoSParams_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABQoSParams_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABQoSParams_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABQoSParams_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABQoSParams_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABQoSParams_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABQoSParams_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABQoSParams_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABQoSParams_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABQoSParams_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABQoSParams_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABQoSParams_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABQoSParams_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABQoSParams_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABQoSParams_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABQoSParams_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABQoSParams_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABQoSParams_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABQoSParams_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABLvlQoSParamsTkn[] =
{
 &szQCI,
 &szAllocnAndRetentionPriority,
 &szOptGBR_QosInform,
 &szOptProtExtnCont_E_RABQoSParams_ExtIEs,
  &szProtExtnField_E_RABQoSParams_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABLvlQoSParamsspec =
{



 2,
 0,
 0L,
 0L,
 &szE_RABLvlQoSParamsTkn[0],
 0
};
 CmPAsnElmDef szE_RABLvlQoSParams =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABLvlQoSParams),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABLvlQoSParamsspec),
 0L
};

CmPAsnUIntDef szEUTRANRoundTripDelayEstimationInfospec =
{



 0,
 2047UL
};
CmPAsnElmDef szEUTRANRoundTripDelayEstimationInfo =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztEUTRANRoundTripDelayEstimationInfo),
 &flagSz3M,
 0,
 (U8 *)(&szEUTRANRoundTripDelayEstimationInfospec),
 0L
};


CmPAsnUIntDef szExtendedRNC_IDspec =
{



 4096,
 65535UL
};
CmPAsnElmDef szOptExtendedRNC_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztExtendedRNC_ID),
 &flagSz3O,
 0,
 (U8 *)(&szExtendedRNC_IDspec),
 0L
};


CmPAsnUIntDef szExtendedRepetitionPeriodspec =
{



 4096,
 131071UL
};
CmPAsnElmDef szExtendedRepetitionPeriod =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztExtendedRepetitionPeriod),
 &flagSz3M,
 0,
 (U8 *)(&szExtendedRepetitionPeriodspec),
 0L
};


CmPAsnTknEnum szForbiddenInterRATsExtLst[3] =
{
 2,
 SztForbiddenInterRATsgeranandutranEnum,
 SztForbiddenInterRATscdma2000andutranEnum
};
CmPAsnTknEnum szForbiddenInterRATsLst[5] =
{
 4,
 SztForbiddenInterRATsallEnum,
 SztForbiddenInterRATsgeranEnum,
 SztForbiddenInterRATsutranEnum,
 SztForbiddenInterRATscdma2000Enum
};
CmPAsnEnumDef szForbiddenInterRATsspec =
{



 szForbiddenInterRATsLst,
 szForbiddenInterRATsExtLst
};
CmPAsnElmDef szOptForbiddenInterRATs =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztForbiddenInterRATs),
 &flagSz3O,
 0,
 (U8 *)(&szForbiddenInterRATsspec),
 0L
};

CmPAsnSetSeqOfDef szForbiddenTACsspec =
{



 1,
 4096,
 3*sizeof(U32)
};
 CmPAsnElmDef szForbiddenTACs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztForbiddenTACs),
 &flagSz3M,
 0,
 (U8 *) (&szForbiddenTACsspec),
 0L
};
 CmPAsnElmDef *sz_ExtnForbiddenTAs_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnForbiddenTAs_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnForbiddenTAs_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnForbiddenTAs_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnForbiddenTAs_Item_ExtIEsClsSpec =
{



 &sz_ExtnForbiddenTAs_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnForbiddenTAs_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnForbiddenTAs_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnForbiddenTAs_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnForbiddenTAs_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_ForbiddenTAs_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnForbiddenTAs_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_ForbiddenTAs_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_ForbiddenTAs_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_ForbiddenTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_ForbiddenTAs_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_ForbiddenTAs_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_ForbiddenTAs_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_ForbiddenTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ForbiddenTAs_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_ForbiddenTAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_ForbiddenTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ForbiddenTAs_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_ForbiddenTAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szForbiddenTAs_ItemTkn[] =
{
 &szTBCD_STRING,
 &szForbiddenTACs,
  &szTAC,
  &szConstTerm,
 &szOptProtExtnCont_ForbiddenTAs_Item_ExtIEs,
  &szProtExtnField_ForbiddenTAs_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szForbiddenTAs_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szForbiddenTAs_ItemTkn[0],
 0
};
 CmPAsnElmDef szForbiddenTAs_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztForbiddenTAs_Item),
 &flagSz3M,
 0,
 (U8 *)(&szForbiddenTAs_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szForbiddenTAsspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptForbiddenTAs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztForbiddenTAs),
 &flagSz3O,
 0,
 (U8 *) (&szForbiddenTAsspec),
 0L
};
CmPAsnSetSeqOfDef szForbiddenLACsspec =
{



 1,
 4096,
 3*sizeof(U32)
};
 CmPAsnElmDef szForbiddenLACs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztForbiddenLACs),
 &flagSz3M,
 0,
 (U8 *) (&szForbiddenLACsspec),
 0L
};
 CmPAsnElmDef *sz_ExtnForbiddenLAs_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnForbiddenLAs_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnForbiddenLAs_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnForbiddenLAs_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnForbiddenLAs_Item_ExtIEsClsSpec =
{



 &sz_ExtnForbiddenLAs_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnForbiddenLAs_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnForbiddenLAs_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnForbiddenLAs_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnForbiddenLAs_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_ForbiddenLAs_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnForbiddenLAs_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_ForbiddenLAs_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_ForbiddenLAs_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_ForbiddenLAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_ForbiddenLAs_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_ForbiddenLAs_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_ForbiddenLAs_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_ForbiddenLAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ForbiddenLAs_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_ForbiddenLAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_ForbiddenLAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ForbiddenLAs_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_ForbiddenLAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szForbiddenLAs_ItemTkn[] =
{
 &szTBCD_STRING,
 &szForbiddenLACs,
  &szLAC,
  &szConstTerm,
 &szOptProtExtnCont_ForbiddenLAs_Item_ExtIEs,
  &szProtExtnField_ForbiddenLAs_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szForbiddenLAs_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szForbiddenLAs_ItemTkn[0],
 0
};
 CmPAsnElmDef szForbiddenLAs_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztForbiddenLAs_Item),
 &flagSz3M,
 0,
 (U8 *)(&szForbiddenLAs_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szForbiddenLAsspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptForbiddenLAs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztForbiddenLAs),
 &flagSz3O,
 0,
 (U8 *) (&szForbiddenLAsspec),
 0L
};
CmPAsnOctStrDef szGTP_TEIDspec =
{



 4,
 4
};
CmPAsnElmDef szOptGTP_TEID =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztGTP_TEID),
 &flagSz3O,
 0,
 (U8 *) (&szGTP_TEIDspec),
 0L
};
CmPAsnElmDef szGTP_TEID =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztGTP_TEID),
 &flagSz3M,
 0,
 (U8 *) (&szGTP_TEIDspec),
 0L
};

CmPAsnTknEnum szGUMMEITypLst[3] =
{
 2,
 SztGUMMEITypnativeEnum,
 SztGUMMEITypmappedEnum
};
CmPAsnEnumDef szGUMMEITypspec =
{



 szGUMMEITypLst,
 0L
};
CmPAsnElmDef szGUMMEITyp =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztGUMMEITyp),
 &flagSz3M,
 0,
 (U8 *)(&szGUMMEITypspec),
 0L
};


CmPAsnTknEnum szGWCntxtRlsIndLst[2] =
{
 1,
 SztGWCntxtRlsIndtrueEnum
};
CmPAsnEnumDef szGWCntxtRlsIndspec =
{



 szGWCntxtRlsIndLst,
 0L
};
CmPAsnElmDef szGWCntxtRlsInd =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztGWCntxtRlsInd),
 &flagSz3M,
 0,
 (U8 *)(&szGWCntxtRlsIndspec),
 0L
};

 CmPAsnElmDef *sz_ExtnHovrRestrnLst_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnHovrRestrnLst_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnHovrRestrnLst_ExtIEsClsInfo =
{
 0,
 &sz_ExtnHovrRestrnLst_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnHovrRestrnLst_ExtIEsClsSpec =
{



 &sz_ExtnHovrRestrnLst_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnHovrRestrnLst_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnHovrRestrnLst_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnHovrRestrnLst_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnHovrRestrnLst_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_HovrRestrnLst_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnHovrRestrnLst_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_HovrRestrnLst_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_HovrRestrnLst_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_HovrRestrnLst_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_HovrRestrnLst_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_HovrRestrnLst_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_HovrRestrnLst_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_HovrRestrnLst_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_HovrRestrnLst_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_HovrRestrnLst_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_HovrRestrnLst_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_HovrRestrnLst_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_HovrRestrnLst_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szHovrRestrnLstTkn[] =
{
 &szTBCD_STRING,
 &szOptEPLMNs,
  &szTBCD_STRING,
  &szConstTerm,
 &szOptForbiddenTAs,
  &szForbiddenTAs_Item,
  &szConstTerm,
 &szOptForbiddenLAs,
  &szForbiddenLAs_Item,
  &szConstTerm,
 &szOptForbiddenInterRATs,
 &szOptProtExtnCont_HovrRestrnLst_ExtIEs,
  &szProtExtnField_HovrRestrnLst_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrRestrnLstspec =
{



 5,
 0,
 0L,
 0L,
 &szHovrRestrnLstTkn[0],
 0
};
 CmPAsnElmDef szHovrRestrnLst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrRestrnLst),
 &flagSz3M,
 0,
 (U8 *)(&szHovrRestrnLstspec),
 0L
};

CmPAsnTknEnum szHovrTypLst[6] =
{
 5,
 SztHovrTypintralteEnum,
 SztHovrTypltetoutranEnum,
 SztHovrTypltetogeranEnum,
 SztHovrTyputrantolteEnum,
 SztHovrTypgerantolteEnum
};
CmPAsnEnumDef szHovrTypspec =
{



 szHovrTypLst,
 0L
};
CmPAsnElmDef szHovrTyp =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztHovrTyp),
 &flagSz3M,
 0,
 (U8 *)(&szHovrTypspec),
 0L
};

CmPAsnBitStrDef szMeasurementsToActivatespec =
{



 8,
 8
};
CmPAsnElmDef szMeasurementsToActivate =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztMeasurementsToActivate),
 &flagSz3M,
 0,
 (U8 *) (&szMeasurementsToActivatespec),
 0L
};

CmPAsnTknEnum szM1RprtngTriggerExtLst[2] =
{
 1,
 SztM1RprtngTriggera2eventtriggered_periodicEnum
};
CmPAsnTknEnum szM1RprtngTriggerLst[3] =
{
 2,
 SztM1RprtngTriggerperiodicEnum,
 SztM1RprtngTriggera2eventtriggeredEnum
};
CmPAsnEnumDef szM1RprtngTriggerspec =
{



 szM1RprtngTriggerLst,
 szM1RprtngTriggerExtLst
};
CmPAsnElmDef szM1RprtngTrigger =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztM1RprtngTrigger),
 &flagSz3M,
 0,
 (U8 *)(&szM1RprtngTriggerspec),
 0L
};


CmPAsnUIntDef szThreshold_RSRPspec =
{



 0,
 97UL
};
CmPAsnElmDef szThreshold_RSRP =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztThreshold_RSRP),
 &flagSz3M,
 0,
 (U8 *)(&szThreshold_RSRPspec),
 0L
};


CmPAsnUIntDef szThreshold_RSRQspec =
{



 0,
 34UL
};
CmPAsnElmDef szThreshold_RSRQ =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztThreshold_RSRQ),
 &flagSz3M,
 0,
 (U8 *)(&szThreshold_RSRQspec),
 0L
};

 CmPAsnElmDef *szMeasurementThresholdA2Tkn[] =
{
 &szThreshold_RSRP,
 &szThreshold_RSRQ,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szMeasurementThresholdA2spec =
{



 2,
 0,
 &szMeasurementThresholdA2Tkn[0]
};
CmPAsnElmDef szMeasurementThresholdA2 =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztMeasurementThresholdA2),
 &flagSz3M,
 0L,
 (U8 *)(&szMeasurementThresholdA2spec),
 0L
};
 CmPAsnElmDef *sz_ExtnM1ThresholdEventA2_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnM1ThresholdEventA2_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnM1ThresholdEventA2_ExtIEsClsInfo =
{
 0,
 &sz_ExtnM1ThresholdEventA2_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnM1ThresholdEventA2_ExtIEsClsSpec =
{



 &sz_ExtnM1ThresholdEventA2_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnM1ThresholdEventA2_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnM1ThresholdEventA2_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnM1ThresholdEventA2_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnM1ThresholdEventA2_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_M1ThresholdEventA2_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnM1ThresholdEventA2_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_M1ThresholdEventA2_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_M1ThresholdEventA2_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_M1ThresholdEventA2_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_M1ThresholdEventA2_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_M1ThresholdEventA2_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_M1ThresholdEventA2_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_M1ThresholdEventA2_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M1ThresholdEventA2_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_M1ThresholdEventA2_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_M1ThresholdEventA2_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M1ThresholdEventA2_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_M1ThresholdEventA2_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szM1ThresholdEventA2Tkn[] =
{
 &szMeasurementThresholdA2,
 &szOptProtExtnCont_M1ThresholdEventA2_ExtIEs,
  &szProtExtnField_M1ThresholdEventA2_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szM1ThresholdEventA2spec =
{



 1,
 0,
 0L,
 0L,
 &szM1ThresholdEventA2Tkn[0],
 0
};
 CmPAsnElmDef szM1ThresholdEventA2 =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztM1ThresholdEventA2),
 &flagSz3M,
 0,
 (U8 *)(&szM1ThresholdEventA2spec),
 0L
};
 CmPAsnElmDef szOptM1ThresholdEventA2 =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztM1ThresholdEventA2),
 &flagSz3O,
 0,
 (U8 *)(&szM1ThresholdEventA2spec),
 0L
};

CmPAsnTknEnum szReportIntervalMDTLst[14] =
{
 13,
 SztReportIntervalMDTms120Enum,
 SztReportIntervalMDTms240Enum,
 SztReportIntervalMDTms480Enum,
 SztReportIntervalMDTms640Enum,
 SztReportIntervalMDTms1024Enum,
 SztReportIntervalMDTms2048Enum,
 SztReportIntervalMDTms5120Enum,
 SztReportIntervalMDTms10240Enum,
 SztReportIntervalMDTmin1Enum,
 SztReportIntervalMDTmin6Enum,
 SztReportIntervalMDTmin12Enum,
 SztReportIntervalMDTmin30Enum,
 SztReportIntervalMDTmin60Enum
};
CmPAsnEnumDef szReportIntervalMDTspec =
{



 szReportIntervalMDTLst,
 0L
};
CmPAsnElmDef szReportIntervalMDT =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztReportIntervalMDT),
 &flagSz3M,
 0,
 (U8 *)(&szReportIntervalMDTspec),
 0L
};


CmPAsnTknEnum szReportAmountMDTLst[9] =
{
 8,
 SztReportAmountMDTr1Enum,
 SztReportAmountMDTr2Enum,
 SztReportAmountMDTr4Enum,
 SztReportAmountMDTr8Enum,
 SztReportAmountMDTr16Enum,
 SztReportAmountMDTr32Enum,
 SztReportAmountMDTr64Enum,
 SztReportAmountMDTrinfinityEnum
};
CmPAsnEnumDef szReportAmountMDTspec =
{



 szReportAmountMDTLst,
 0L
};
CmPAsnElmDef szReportAmountMDT =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztReportAmountMDT),
 &flagSz3M,
 0,
 (U8 *)(&szReportAmountMDTspec),
 0L
};

 CmPAsnElmDef *sz_ExtnM1PeriodicRprtng_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnM1PeriodicRprtng_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnM1PeriodicRprtng_ExtIEsClsInfo =
{
 0,
 &sz_ExtnM1PeriodicRprtng_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnM1PeriodicRprtng_ExtIEsClsSpec =
{



 &sz_ExtnM1PeriodicRprtng_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnM1PeriodicRprtng_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnM1PeriodicRprtng_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnM1PeriodicRprtng_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnM1PeriodicRprtng_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_M1PeriodicRprtng_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnM1PeriodicRprtng_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_M1PeriodicRprtng_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_M1PeriodicRprtng_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_M1PeriodicRprtng_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_M1PeriodicRprtng_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_M1PeriodicRprtng_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_M1PeriodicRprtng_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_M1PeriodicRprtng_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M1PeriodicRprtng_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_M1PeriodicRprtng_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_M1PeriodicRprtng_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M1PeriodicRprtng_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_M1PeriodicRprtng_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szM1PeriodicRprtngTkn[] =
{
 &szReportIntervalMDT,
 &szReportAmountMDT,
 &szOptProtExtnCont_M1PeriodicRprtng_ExtIEs,
  &szProtExtnField_M1PeriodicRprtng_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szM1PeriodicRprtngspec =
{



 1,
 0,
 0L,
 0L,
 &szM1PeriodicRprtngTkn[0],
 0
};
 CmPAsnElmDef szM1PeriodicRprtng =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztM1PeriodicRprtng),
 &flagSz3M,
 0,
 (U8 *)(&szM1PeriodicRprtngspec),
 0L
};
 CmPAsnElmDef szOptM1PeriodicRprtng =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztM1PeriodicRprtng),
 &flagSz3O,
 0,
 (U8 *)(&szM1PeriodicRprtngspec),
 0L
};

CmPAsnTknEnum szM3periodLst[4] =
{
 3,
 SztM3periodms100Enum,
 SztM3periodms1000Enum,
 SztM3periodms10000Enum
};
CmPAsnEnumDef szM3periodspec =
{



 szM3periodLst,
 0L
};
CmPAsnElmDef szM3period =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztM3period),
 &flagSz3M,
 0,
 (U8 *)(&szM3periodspec),
 0L
};

 CmPAsnElmDef *sz_ExtnM3Config_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnM3Config_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnM3Config_ExtIEsClsInfo =
{
 0,
 &sz_ExtnM3Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnM3Config_ExtIEsClsSpec =
{



 &sz_ExtnM3Config_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnM3Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnM3Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnM3Config_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnM3Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_M3Config_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnM3Config_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_M3Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_M3Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_M3Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_M3Config_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_M3Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_M3Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_M3Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M3Config_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_M3Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_M3Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M3Config_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_M3Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szM3ConfigTkn[] =
{
 &szM3period,
 &szOptProtExtnCont_M3Config_ExtIEs,
  &szProtExtnField_M3Config_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szM3Configspec =
{



 1,
 0,
 0L,
 0L,
 &szM3ConfigTkn[0],
 0
};
 CmPAsnElmDef szM3Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztM3Config),
 &flagSz3M,
 0,
 (U8 *)(&szM3Configspec),
 0L
};

CmPAsnTknEnum szM4periodLst[6] =
{
 5,
 SztM4periodms1024Enum,
 SztM4periodms2048Enum,
 SztM4periodms5120Enum,
 SztM4periodms10240Enum,
 SztM4periodmin1Enum
};
CmPAsnEnumDef szM4periodspec =
{



 szM4periodLst,
 0L
};
CmPAsnElmDef szM4period =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztM4period),
 &flagSz3M,
 0,
 (U8 *)(&szM4periodspec),
 0L
};


CmPAsnTknEnum szLinks_to_logLst[4] =
{
 3,
 SztLinks_to_loguplinkEnum,
 SztLinks_to_logdownlinkEnum,
 SztLinks_to_logboth_uplink_and_downlinkEnum
};
CmPAsnEnumDef szLinks_to_logspec =
{



 szLinks_to_logLst,
 0L
};
CmPAsnElmDef szLinks_to_log =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztLinks_to_log),
 &flagSz3M,
 0,
 (U8 *)(&szLinks_to_logspec),
 0L
};

 CmPAsnElmDef *sz_ExtnM4Config_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnM4Config_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnM4Config_ExtIEsClsInfo =
{
 0,
 &sz_ExtnM4Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnM4Config_ExtIEsClsSpec =
{



 &sz_ExtnM4Config_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnM4Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnM4Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnM4Config_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnM4Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_M4Config_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnM4Config_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_M4Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_M4Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_M4Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_M4Config_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_M4Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_M4Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_M4Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M4Config_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_M4Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_M4Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M4Config_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_M4Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szM4ConfigTkn[] =
{
 &szM4period,
 &szLinks_to_log,
 &szOptProtExtnCont_M4Config_ExtIEs,
  &szProtExtnField_M4Config_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szM4Configspec =
{



 1,
 0,
 0L,
 0L,
 &szM4ConfigTkn[0],
 0
};
 CmPAsnElmDef szM4Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztM4Config),
 &flagSz3M,
 0,
 (U8 *)(&szM4Configspec),
 0L
};

CmPAsnTknEnum szM5periodLst[6] =
{
 5,
 SztM5periodms1024Enum,
 SztM5periodms2048Enum,
 SztM5periodms5120Enum,
 SztM5periodms10240Enum,
 SztM5periodmin1Enum
};
CmPAsnEnumDef szM5periodspec =
{



 szM5periodLst,
 0L
};
CmPAsnElmDef szM5period =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztM5period),
 &flagSz3M,
 0,
 (U8 *)(&szM5periodspec),
 0L
};

 CmPAsnElmDef *sz_ExtnM5Config_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnM5Config_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnM5Config_ExtIEsClsInfo =
{
 0,
 &sz_ExtnM5Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnM5Config_ExtIEsClsSpec =
{



 &sz_ExtnM5Config_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnM5Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnM5Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnM5Config_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnM5Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_M5Config_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnM5Config_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_M5Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_M5Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_M5Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_M5Config_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_M5Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_M5Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_M5Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M5Config_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_M5Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_M5Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_M5Config_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_M5Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szM5ConfigTkn[] =
{
 &szM5period,
 &szLinks_to_log,
 &szOptProtExtnCont_M5Config_ExtIEs,
  &szProtExtnField_M5Config_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szM5Configspec =
{



 1,
 0,
 0L,
 0L,
 &szM5ConfigTkn[0],
 0
};
 CmPAsnElmDef szM5Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztM5Config),
 &flagSz3M,
 0,
 (U8 *)(&szM5Configspec),
 0L
};
CmPAsnBitStrDef szMDT_Loc_Infospec =
{



 8,
 8
};
CmPAsnElmDef szMDT_Loc_Info =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztMDT_Loc_Info),
 &flagSz3M,
 0,
 (U8 *) (&szMDT_Loc_Infospec),
 0L
};
 CmPAsnElmDef *sz_ExtnImmediateMDT_ExtIEsClsInst[] =
{
 &szM3Config,
 &szM4Config,
 &szM5Config,
 &szMDT_Loc_Info
};
 U32 sz_ExtnImmediateMDT_ExtIEsClsInstId[] =
{
 171,
 172,
 173,
 174
};
 CmPAsnClassInfo sz_ExtnImmediateMDT_ExtIEsClsInfo =
{
 4,
 &sz_ExtnImmediateMDT_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnImmediateMDT_ExtIEsClsSpec =
{



 &sz_ExtnImmediateMDT_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnImmediateMDT_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnImmediateMDT_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnImmediateMDT_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnImmediateMDT_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_ImmediateMDT_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnImmediateMDT_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_ImmediateMDT_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_ImmediateMDT_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_ImmediateMDT_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_ImmediateMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_ImmediateMDT_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_ImmediateMDT_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_ImmediateMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ImmediateMDT_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_ImmediateMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_ImmediateMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ImmediateMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_ImmediateMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szImmediateMDTTkn[] =
{
 &szMeasurementsToActivate,
 &szM1RprtngTrigger,
 &szOptM1ThresholdEventA2,
 &szOptM1PeriodicRprtng,
 &szOptProtExtnCont_ImmediateMDT_ExtIEs,
  &szProtExtnField_ImmediateMDT_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szImmediateMDTspec =
{



 3,
 0,
 0L,
 0L,
 &szImmediateMDTTkn[0],
 0
};
 CmPAsnElmDef szImmediateMDT =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztImmediateMDT),
 &flagSz3M,
 0,
 (U8 *)(&szImmediateMDTspec),
 0L
};
CmPAsnOctStrDef szIMSIspec =
{



 3,
 8
};
CmPAsnElmDef szIMSI =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztIMSI),
 &flagSz3M,
 0,
 (U8 *) (&szIMSIspec),
 0L
};
CmPAsnBitStrDef szIntegrityProtectionAlgorithmsspec =
{



 16,
 16
};
CmPAsnElmDef szIntegrityProtectionAlgorithms =
{



 CM_PASN_TET_BITSTR,
 1,
 sizeof(SztIntegrityProtectionAlgorithms),
 &flagSz3M,
 0,
 (U8 *) (&szIntegrityProtectionAlgorithmsspec),
 0L
};
CmPAsnBitStrDef szIntfsToTracespec =
{



 8,
 8
};
CmPAsnElmDef szIntfsToTrace =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztIntfsToTrace),
 &flagSz3M,
 0,
 (U8 *) (&szIntfsToTracespec),
 0L
};

CmPAsnUIntDef szTime_UE_StayedInCellspec =
{



 0,
 4095UL
};
CmPAsnElmDef szTime_UE_StayedInCell =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztTime_UE_StayedInCell),
 &flagSz3M,
 0,
 (U8 *)(&szTime_UE_StayedInCellspec),
 0L
};


CmPAsnUIntDef szTime_UE_StayedInCell_EnhancedGranularityspec =
{



 0,
 40950UL
};
CmPAsnElmDef szTime_UE_StayedInCell_EnhancedGranularity =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztTime_UE_StayedInCell_EnhancedGranularity),
 &flagSz3M,
 0,
 (U8 *)(&szTime_UE_StayedInCell_EnhancedGranularityspec),
 0L
};

 CmPAsnElmDef *sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInst[] =
{
 &szTime_UE_StayedInCell_EnhancedGranularity,
 &szCause
};
 U32 sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInstId[] =
{
 167,
 168
};
 CmPAsnClassInfo sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInfo =
{
 2,
 &sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsSpec =
{



 &sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnLastVisitedEUTRANCellInform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnLastVisitedEUTRANCellInform_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_LastVisitedEUTRANCellInform_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnLastVisitedEUTRANCellInform_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_LastVisitedEUTRANCellInform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_LastVisitedEUTRANCellInform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_LastVisitedEUTRANCellInform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_LastVisitedEUTRANCellInform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_LastVisitedEUTRANCellInform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szLastVisitedEUTRANCellInformTkn[] =
{
 &szEUTRAN_CGI,
 &szCellTyp,
 &szTime_UE_StayedInCell,
 &szOptProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs,
  &szProtExtnField_LastVisitedEUTRANCellInform_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szLastVisitedEUTRANCellInformspec =
{



 1,
 0,
 0L,
 0L,
 &szLastVisitedEUTRANCellInformTkn[0],
 0
};
 CmPAsnElmDef szLastVisitedEUTRANCellInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztLastVisitedEUTRANCellInform),
 &flagSz3M,
 0,
 (U8 *)(&szLastVisitedEUTRANCellInformspec),
 0L
};
CmPAsnOctStrDef szLastVisitedUTRANCellInformspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szLastVisitedUTRANCellInform =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztLastVisitedUTRANCellInform),
 &flagSz3M,
 0,
 (U8 *) (&szLastVisitedUTRANCellInformspec),
 0L
};
 CmPAsnElmDef *szLastVisitedGERANCellInformTkn[] =
{
 &szNull,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szLastVisitedGERANCellInformspec =
{



 1,
 0,
 &szLastVisitedGERANCellInformTkn[0]
};
CmPAsnElmDef szLastVisitedGERANCellInform =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztLastVisitedGERANCellInform),
 &flagSz3M,
 0L,
 (U8 *)(&szLastVisitedGERANCellInformspec),
 0L
};
 CmPAsnElmDef *szLastVisitedCell_ItemTkn[] =
{
 &szLastVisitedEUTRANCellInform,
 &szLastVisitedUTRANCellInform,
 &szLastVisitedGERANCellInform,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szLastVisitedCell_Itemspec =
{



 3,
 0,
 &szLastVisitedCell_ItemTkn[0]
};
CmPAsnElmDef szLastVisitedCell_Item =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztLastVisitedCell_Item),
 &flagSz3M,
 0L,
 (U8 *)(&szLastVisitedCell_Itemspec),
 0L
};
CmPAsnOctStrDef szL3_Informspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szL3_Inform =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztL3_Inform),
 &flagSz3M,
 0,
 (U8 *) (&szL3_Informspec),
 0L
};
CmPAsnOctStrDef szLPPa_PDUspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szLPPa_PDU =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztLPPa_PDU),
 &flagSz3M,
 0,
 (U8 *) (&szLPPa_PDUspec),
 0L
};

CmPAsnTknEnum szLoggingIntervalLst[9] =
{
 8,
 SztLoggingIntervalms128Enum,
 SztLoggingIntervalms256Enum,
 SztLoggingIntervalms512Enum,
 SztLoggingIntervalms1024Enum,
 SztLoggingIntervalms2048Enum,
 SztLoggingIntervalms3072Enum,
 SztLoggingIntervalms4096Enum,
 SztLoggingIntervalms6144Enum
};
CmPAsnEnumDef szLoggingIntervalspec =
{



 szLoggingIntervalLst,
 0L
};
CmPAsnElmDef szLoggingInterval =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztLoggingInterval),
 &flagSz3M,
 0,
 (U8 *)(&szLoggingIntervalspec),
 0L
};


CmPAsnTknEnum szLoggingDurationLst[7] =
{
 6,
 SztLoggingDurationm10Enum,
 SztLoggingDurationm20Enum,
 SztLoggingDurationm40Enum,
 SztLoggingDurationm60Enum,
 SztLoggingDurationm90Enum,
 SztLoggingDurationm120Enum
};
CmPAsnEnumDef szLoggingDurationspec =
{



 szLoggingDurationLst,
 0L
};
CmPAsnElmDef szLoggingDuration =
{



 CM_PASN_TET_ENUM,
 0,
 sizeof(SztLoggingDuration),
 &flagSz3M,
 0,
 (U8 *)(&szLoggingDurationspec),
 0L
};

 CmPAsnElmDef *sz_ExtnLoggedMDT_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnLoggedMDT_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnLoggedMDT_ExtIEsClsInfo =
{
 0,
 &sz_ExtnLoggedMDT_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnLoggedMDT_ExtIEsClsSpec =
{



 &sz_ExtnLoggedMDT_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnLoggedMDT_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnLoggedMDT_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnLoggedMDT_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnLoggedMDT_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_LoggedMDT_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnLoggedMDT_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_LoggedMDT_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_LoggedMDT_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_LoggedMDT_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_LoggedMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_LoggedMDT_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_LoggedMDT_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_LoggedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_LoggedMDT_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_LoggedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_LoggedMDT_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_LoggedMDT_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_LoggedMDT_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szLoggedMDTTkn[] =
{
 &szLoggingInterval,
 &szLoggingDuration,
 &szOptProtExtnCont_LoggedMDT_ExtIEs,
  &szProtExtnField_LoggedMDT_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szLoggedMDTspec =
{



 1,
 0,
 0L,
 0L,
 &szLoggedMDTTkn[0],
 0
};
 CmPAsnElmDef szLoggedMDT =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztLoggedMDT),
 &flagSz3M,
 0,
 (U8 *)(&szLoggedMDTspec),
 0L
};

CmPAsnTknEnum szMDT_ActvnLst[4] =
{
 3,
 SztMDT_Actvnimmediate_MDT_onlyEnum,
 SztMDT_Actvnimmediate_MDT_and_TraceEnum,
 SztMDT_Actvnlogged_MDT_onlyEnum
};
CmPAsnEnumDef szMDT_Actvnspec =
{



 szMDT_ActvnLst,
 0L
};
CmPAsnElmDef szMDT_Actvn =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztMDT_Actvn),
 &flagSz3M,
 0,
 (U8 *)(&szMDT_Actvnspec),
 0L
};

 CmPAsnElmDef *szMDTModeTkn[] =
{
 &szImmediateMDT,
 &szLoggedMDT,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szMDTModespec =
{



 2,
 0,
 &szMDTModeTkn[0]
};
CmPAsnElmDef szMDTMode =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztMDTMode),
 &flagSz3M,
 0L,
 (U8 *)(&szMDTModespec),
 0L
};
CmPAsnSetSeqOfDef szMDTPLMNLstspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef szMDTPLMNLst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztMDTPLMNLst),
 &flagSz3M,
 0,
 (U8 *) (&szMDTPLMNLstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnMDT_Config_ExtIEsClsInst[] =
{
 &szMDTPLMNLst,
  &szTBCD_STRING,
  &szConstTerm,

};
 U32 sz_ExtnMDT_Config_ExtIEsClsInstId[] =
{
 178,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo sz_ExtnMDT_Config_ExtIEsClsInfo =
{
 3,
 &sz_ExtnMDT_Config_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnMDT_Config_ExtIEsClsSpec =
{



 &sz_ExtnMDT_Config_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnMDT_Config_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnMDT_Config_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnMDT_Config_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnMDT_Config_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_MDT_Config_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnMDT_Config_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_MDT_Config_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_MDT_Config_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_MDT_Config_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_MDT_Config_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_MDT_Config_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_MDT_Config_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_MDT_Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_MDT_Config_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_MDT_Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_MDT_Config_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_MDT_Config_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_MDT_Config_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szMDT_ConfigTkn[] =
{
 &szMDT_Actvn,
 &szAreaScopeOfMDT,
 &szMDTMode,
 &szOptProtExtnCont_MDT_Config_ExtIEs,
  &szProtExtnField_MDT_Config_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szMDT_Configspec =
{



 1,
 0,
 0L,
 0L,
 &szMDT_ConfigTkn[0],
 0
};
 CmPAsnElmDef szMDT_Config =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztMDT_Config),
 &flagSz3M,
 0,
 (U8 *)(&szMDT_Configspec),
 0L
};

CmPAsnTknEnum szManagementBasedMDTAllowedLst[2] =
{
 1,
 SztManagementBasedMDTAllowedallowedEnum
};
CmPAsnEnumDef szManagementBasedMDTAllowedspec =
{



 szManagementBasedMDTAllowedLst,
 0L
};
CmPAsnElmDef szManagementBasedMDTAllowed =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztManagementBasedMDTAllowed),
 &flagSz3M,
 0,
 (U8 *)(&szManagementBasedMDTAllowedspec),
 0L
};


CmPAsnTknEnum szPrivacyIndicatorLst[3] =
{
 2,
 SztPrivacyIndicatorimmediate_MDTEnum,
 SztPrivacyIndicatorlogged_MDTEnum
};
CmPAsnEnumDef szPrivacyIndicatorspec =
{



 szPrivacyIndicatorLst,
 0L
};
CmPAsnElmDef szPrivacyIndicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztPrivacyIndicator),
 &flagSz3M,
 0,
 (U8 *)(&szPrivacyIndicatorspec),
 0L
};

CmPAsnBitStrDef szMsgIdentifierspec =
{



 16,
 16
};
CmPAsnElmDef szMsgIdentifier =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztMsgIdentifier),
 &flagSz3M,
 0,
 (U8 *) (&szMsgIdentifierspec),
 0L
};
CmPAsnBitStrDef szMobilityInformspec =
{



 32,
 32
};
CmPAsnElmDef szMobilityInform =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztMobilityInform),
 &flagSz3M,
 0,
 (U8 *) (&szMobilityInformspec),
 0L
};
U32 szMMEnameAlpLst[] = {74 , ' ', '\'', '(', ')', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', '=', '?', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
CmPAsnMulStrDef szMMEnamespec =
{



 szMMEnameAlpLst,
 150,
 1,
 122,
 32
};
CmPAsnElmDef szMMEname =
{



 CM_PASN_TET_PRNSTRXL,
 1,
 sizeof(SztMMEname),
 &flagSz3M,
 0,
 (U8 *) (&szMMEnamespec),
 0L
};

CmPAsnTknEnum szMMERelaySupportIndicatorLst[2] =
{
 1,
 SztMMERelaySupportIndicatortrueEnum
};
CmPAsnEnumDef szMMERelaySupportIndicatorspec =
{



 szMMERelaySupportIndicatorLst,
 0L
};
CmPAsnElmDef szMMERelaySupportIndicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztMMERelaySupportIndicator),
 &flagSz3M,
 0,
 (U8 *)(&szMMERelaySupportIndicatorspec),
 0L
};


CmPAsnUIntDef szMME_UE_S1AP_IDspec =
{



 0,
 4294967295UL
};
CmPAsnElmDef szMME_UE_S1AP_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztMME_UE_S1AP_ID),
 &flagSz3M,
 0,
 (U8 *)(&szMME_UE_S1AP_IDspec),
 0L
};
CmPAsnElmDef szOptMME_UE_S1AP_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztMME_UE_S1AP_ID),
 &flagSz3O,
 0,
 (U8 *)(&szMME_UE_S1AP_IDspec),
 0L
};

CmPAsnOctStrDef szM_TMSIspec =
{



 4,
 4
};
CmPAsnElmDef szM_TMSI =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztM_TMSI),
 &flagSz3M,
 0,
 (U8 *) (&szM_TMSIspec),
 0L
};
CmPAsnOctStrDef szMSClassmark2spec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szMSClassmark2 =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztMSClassmark2),
 &flagSz3M,
 0,
 (U8 *) (&szMSClassmark2spec),
 0L
};
CmPAsnOctStrDef szMSClassmark3spec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szMSClassmark3 =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztMSClassmark3),
 &flagSz3M,
 0,
 (U8 *) (&szMSClassmark3spec),
 0L
};
CmPAsnOctStrDef szNAS_PDUspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szOptNAS_PDU =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztNAS_PDU),
 &flagSz3O,
 0,
 (U8 *) (&szNAS_PDUspec),
 0L
};
CmPAsnElmDef szNAS_PDU =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztNAS_PDU),
 &flagSz3M,
 0,
 (U8 *) (&szNAS_PDUspec),
 0L
};
CmPAsnOctStrDef szNASSecurParamsfromE_UTRANspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szNASSecurParamsfromE_UTRAN =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztNASSecurParamsfromE_UTRAN),
 &flagSz3M,
 0,
 (U8 *) (&szNASSecurParamsfromE_UTRANspec),
 0L
};
CmPAsnOctStrDef szNASSecurParamstoE_UTRANspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szNASSecurParamstoE_UTRAN =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztNASSecurParamstoE_UTRAN),
 &flagSz3M,
 0,
 (U8 *) (&szNASSecurParamstoE_UTRANspec),
 0L
};

CmPAsnUIntDef szNumberofBroadcastRqstspec =
{



 0,
 65535UL
};
CmPAsnElmDef szNumberofBroadcastRqst =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztNumberofBroadcastRqst),
 &flagSz3M,
 0,
 (U8 *)(&szNumberofBroadcastRqstspec),
 0L
};

CmPAsnOctStrDef szOldBSS_ToNewBSS_Informspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szOldBSS_ToNewBSS_Inform =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztOldBSS_ToNewBSS_Inform),
 &flagSz3M,
 0,
 (U8 *) (&szOldBSS_ToNewBSS_Informspec),
 0L
};

CmPAsnTknEnum szOverloadActionExtLst[3] =
{
 2,
 SztOverloadActionpermit_high_priority_sessions_and_mobile_terminated_services_onlyEnum,
 SztOverloadActionreject_delay_tolerant_accessEnum
};
CmPAsnTknEnum szOverloadActionLst[4] =
{
 3,
 SztOverloadActionreject_non_emergency_mo_dtEnum,
 SztOverloadActionreject_rrc_cr_signallingEnum,
 SztOverloadActionpermit_emergency_sessions_and_mobile_terminated_services_onlyEnum
};
CmPAsnEnumDef szOverloadActionspec =
{



 szOverloadActionLst,
 szOverloadActionExtLst
};
CmPAsnElmDef szOverloadAction =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztOverloadAction),
 &flagSz3M,
 0,
 (U8 *)(&szOverloadActionspec),
 0L
};

 CmPAsnElmDef *szOverloadRespTkn[] =
{
 &szOverloadAction,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szOverloadRespspec =
{



 1,
 0,
 &szOverloadRespTkn[0]
};
CmPAsnElmDef szOverloadResp =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztOverloadResp),
 &flagSz3M,
 0L,
 (U8 *)(&szOverloadRespspec),
 0L
};

CmPAsnTknEnum szPagDRXLst[5] =
{
 4,
 SztPagDRXv32Enum,
 SztPagDRXv64Enum,
 SztPagDRXv128Enum,
 SztPagDRXv256Enum
};
CmPAsnEnumDef szPagDRXspec =
{



 szPagDRXLst,
 0L
};
CmPAsnElmDef szPagDRX =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztPagDRX),
 &flagSz3M,
 0,
 (U8 *)(&szPagDRXspec),
 0L
};


CmPAsnTknEnum szPagPriorityLst[9] =
{
 8,
 SztPagPrioritypriolevel1Enum,
 SztPagPrioritypriolevel2Enum,
 SztPagPrioritypriolevel3Enum,
 SztPagPrioritypriolevel4Enum,
 SztPagPrioritypriolevel5Enum,
 SztPagPrioritypriolevel6Enum,
 SztPagPrioritypriolevel7Enum,
 SztPagPrioritypriolevel8Enum
};
CmPAsnEnumDef szPagPriorityspec =
{



 szPagPriorityLst,
 0L
};
CmPAsnElmDef szPagPriority =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztPagPriority),
 &flagSz3M,
 0,
 (U8 *)(&szPagPriorityspec),
 0L
};

CmPAsnOctStrDef szPort_Numberspec =
{



 2,
 2
};
CmPAsnElmDef szOptPort_Number =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztPort_Number),
 &flagSz3O,
 0,
 (U8 *) (&szPort_Numberspec),
 0L
};
CmPAsnElmDef szPort_Number =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztPort_Number),
 &flagSz3M,
 0,
 (U8 *) (&szPort_Numberspec),
 0L
};

CmPAsnTknEnum szPS_ServiceNotAvailableLst[2] =
{
 1,
 SztPS_ServiceNotAvailableps_service_not_availableEnum
};
CmPAsnEnumDef szPS_ServiceNotAvailablespec =
{



 szPS_ServiceNotAvailableLst,
 0L
};
CmPAsnElmDef szPS_ServiceNotAvailable =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztPS_ServiceNotAvailable),
 &flagSz3M,
 0,
 (U8 *)(&szPS_ServiceNotAvailablespec),
 0L
};


CmPAsnUIntDef szRelativeMMECapacityspec =
{



 0,
 255UL
};
CmPAsnElmDef szRelativeMMECapacity =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztRelativeMMECapacity),
 &flagSz3M,
 0,
 (U8 *)(&szRelativeMMECapacityspec),
 0L
};


CmPAsnTknEnum szRelayNode_IndicatorLst[2] =
{
 1,
 SztRelayNode_IndicatortrueEnum
};
CmPAsnEnumDef szRelayNode_Indicatorspec =
{



 szRelayNode_IndicatorLst,
 0L
};
CmPAsnElmDef szRelayNode_Indicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztRelayNode_Indicator),
 &flagSz3M,
 0,
 (U8 *)(&szRelayNode_Indicatorspec),
 0L
};


CmPAsnTknEnum szReportAreaLst[2] =
{
 1,
 SztReportAreaecgiEnum
};
CmPAsnEnumDef szReportAreaspec =
{



 szReportAreaLst,
 0L
};
CmPAsnElmDef szReportArea =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztReportArea),
 &flagSz3M,
 0,
 (U8 *)(&szReportAreaspec),
 0L
};

 CmPAsnElmDef *sz_ExtnRqstTyp_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnRqstTyp_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnRqstTyp_ExtIEsClsInfo =
{
 0,
 &sz_ExtnRqstTyp_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnRqstTyp_ExtIEsClsSpec =
{



 &sz_ExtnRqstTyp_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnRqstTyp_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnRqstTyp_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnRqstTyp_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnRqstTyp_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_RqstTyp_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnRqstTyp_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_RqstTyp_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_RqstTyp_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_RqstTyp_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_RqstTyp_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_RqstTyp_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_RqstTyp_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_RqstTyp_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_RqstTyp_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_RqstTyp_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_RqstTyp_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_RqstTyp_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_RqstTyp_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szRqstTypTkn[] =
{
 &szEventTyp,
 &szReportArea,
 &szOptProtExtnCont_RqstTyp_ExtIEs,
  &szProtExtnField_RqstTyp_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szRqstTypspec =
{



 1,
 0,
 0L,
 0L,
 &szRqstTypTkn[0],
 0
};
 CmPAsnElmDef szRqstTyp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztRqstTyp),
 &flagSz3M,
 0,
 (U8 *)(&szRqstTypspec),
 0L
};
CmPAsnOctStrDef szRIMInformspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szRIMInform =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztRIMInform),
 &flagSz3M,
 0,
 (U8 *) (&szRIMInformspec),
 0L
};

CmPAsnUIntDef szRNC_IDspec =
{



 0,
 4095UL
};
CmPAsnElmDef szRNC_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztRNC_ID),
 &flagSz3M,
 0,
 (U8 *)(&szRNC_IDspec),
 0L
};

 CmPAsnElmDef *sz_ExtnTgetRNC_ID_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTgetRNC_ID_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTgetRNC_ID_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTgetRNC_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTgetRNC_ID_ExtIEsClsSpec =
{



 &sz_ExtnTgetRNC_ID_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTgetRNC_ID_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTgetRNC_ID_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTgetRNC_ID_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTgetRNC_ID_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TgetRNC_ID_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTgetRNC_ID_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TgetRNC_ID_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TgetRNC_ID_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TgetRNC_ID_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TgetRNC_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TgetRNC_ID_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TgetRNC_ID_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TgetRNC_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TgetRNC_ID_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TgetRNC_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TgetRNC_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TgetRNC_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TgetRNC_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTgetRNC_IDTkn[] =
{
 &szLAI,
 &szOptRAC,
 &szRNC_ID,
 &szOptExtendedRNC_ID,
 &szOptProtExtnCont_TgetRNC_ID_ExtIEs,
  &szProtExtnField_TgetRNC_ID_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTgetRNC_IDspec =
{



 3,
 0,
 0L,
 0L,
 &szTgetRNC_IDTkn[0],
 0
};
 CmPAsnElmDef szTgetRNC_ID =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTgetRNC_ID),
 &flagSz3M,
 0,
 (U8 *)(&szTgetRNC_IDspec),
 0L
};
 CmPAsnElmDef *szRIMRoutingAddrTkn[] =
{
 &szGERAN_Cell_ID,
 &szExtMkr,
 &szTgetRNC_ID,
 &szConstTerm
};
CmPAsnChoiceDef szRIMRoutingAddrspec =
{



 1,
 1,
 &szRIMRoutingAddrTkn[0]
};
CmPAsnElmDef szRIMRoutingAddr =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztRIMRoutingAddr),
 &flagSz3M,
 0L,
 (U8 *)(&szRIMRoutingAddrspec),
 0L
};
CmPAsnElmDef szOptRIMRoutingAddr =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztRIMRoutingAddr),
 &flagSz3O,
 0L,
 (U8 *)(&szRIMRoutingAddrspec),
 0L
};
 CmPAsnElmDef *sz_ExtnRIMTfr_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnRIMTfr_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnRIMTfr_ExtIEsClsInfo =
{
 0,
 &sz_ExtnRIMTfr_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnRIMTfr_ExtIEsClsSpec =
{



 &sz_ExtnRIMTfr_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnRIMTfr_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnRIMTfr_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnRIMTfr_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnRIMTfr_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_RIMTfr_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnRIMTfr_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_RIMTfr_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_RIMTfr_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_RIMTfr_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_RIMTfr_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_RIMTfr_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_RIMTfr_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_RIMTfr_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_RIMTfr_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_RIMTfr_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_RIMTfr_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_RIMTfr_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_RIMTfr_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szRIMTfrTkn[] =
{
 &szRIMInform,
 &szOptRIMRoutingAddr,
 &szOptProtExtnCont_RIMTfr_ExtIEs,
  &szProtExtnField_RIMTfr_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szRIMTfrspec =
{



 2,
 0,
 0L,
 0L,
 &szRIMTfrTkn[0],
 0
};
 CmPAsnElmDef szRIMTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztRIMTfr),
 &flagSz3M,
 0,
 (U8 *)(&szRIMTfrspec),
 0L
};

CmPAsnUIntDef szRepetitionPeriodspec =
{



 0,
 4095UL
};
CmPAsnElmDef szRepetitionPeriod =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztRepetitionPeriod),
 &flagSz3M,
 0,
 (U8 *)(&szRepetitionPeriodspec),
 0L
};

CmPAsnOctStrDef szRRC_Contspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szRRC_Cont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztRRC_Cont),
 &flagSz3M,
 0,
 (U8 *) (&szRRC_Contspec),
 0L
};

CmPAsnTknEnum szRRC_Establishment_CauseExtLst[2] =
{
 1,
 SztRRC_Establishment_Causedelay_TolerantAccessEnum
};
CmPAsnTknEnum szRRC_Establishment_CauseLst[6] =
{
 5,
 SztRRC_Establishment_CauseemergencyEnum,
 SztRRC_Establishment_CausehighPriorityAccessEnum,
 SztRRC_Establishment_Causemt_AccessEnum,
 SztRRC_Establishment_Causemo_SignallingEnum,
 SztRRC_Establishment_Causemo_DataEnum
};
CmPAsnEnumDef szRRC_Establishment_Causespec =
{



 szRRC_Establishment_CauseLst,
 szRRC_Establishment_CauseExtLst
};
CmPAsnElmDef szRRC_Establishment_Cause =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztRRC_Establishment_Cause),
 &flagSz3M,
 0,
 (U8 *)(&szRRC_Establishment_Causespec),
 0L
};


CmPAsnUIntDef szRouting_IDspec =
{



 0,
 255UL
};
CmPAsnElmDef szRouting_ID =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztRouting_ID),
 &flagSz3M,
 0,
 (U8 *)(&szRouting_IDspec),
 0L
};

CmPAsnBitStrDef szSecurKeyspec =
{



 256,
 256
};
CmPAsnElmDef szSecurKey =
{



 CM_PASN_TET_BITSTRXL,
 0,
 sizeof(SztSecurKey),
 &flagSz3M,
 0,
 (U8 *) (&szSecurKeyspec),
 0L
};

CmPAsnUIntDef szSecurCntxtnextHopChainingCountspec =
{



 0,
 7UL
};
CmPAsnElmDef szSecurCntxtnextHopChainingCount =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztSecurCntxtnextHopChainingCount),
 &flagSz3M,
 0,
 (U8 *)(&szSecurCntxtnextHopChainingCountspec),
 0L
};

 CmPAsnElmDef *sz_ExtnSecurCntxt_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnSecurCntxt_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnSecurCntxt_ExtIEsClsInfo =
{
 0,
 &sz_ExtnSecurCntxt_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSecurCntxt_ExtIEsClsSpec =
{



 &sz_ExtnSecurCntxt_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnSecurCntxt_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnSecurCntxt_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnSecurCntxt_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnSecurCntxt_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_SecurCntxt_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnSecurCntxt_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SecurCntxt_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_SecurCntxt_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_SecurCntxt_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_SecurCntxt_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_SecurCntxt_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_SecurCntxt_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_SecurCntxt_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SecurCntxt_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_SecurCntxt_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_SecurCntxt_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SecurCntxt_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_SecurCntxt_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szSecurCntxtTkn[] =
{
 &szSecurCntxtnextHopChainingCount,
 &szSecurKey,
 &szOptProtExtnCont_SecurCntxt_ExtIEs,
  &szProtExtnField_SecurCntxt_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szSecurCntxtspec =
{



 1,
 0,
 0L,
 0L,
 &szSecurCntxtTkn[0],
 0
};
 CmPAsnElmDef szSecurCntxt =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztSecurCntxt),
 &flagSz3M,
 0,
 (U8 *)(&szSecurCntxtspec),
 0L
};
CmPAsnBitStrDef szSerialNumberspec =
{



 16,
 16
};
CmPAsnElmDef szSerialNumber =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztSerialNumber),
 &flagSz3M,
 0,
 (U8 *) (&szSerialNumberspec),
 0L
};

CmPAsnTknEnum szSONInformRqstExtLst[2] =
{
 1,
 SztSONInformRqsttime_Synchronization_InfoEnum
};
CmPAsnTknEnum szSONInformRqstLst[2] =
{
 1,
 SztSONInformRqstx2TNL_Config_InfoEnum
};
CmPAsnEnumDef szSONInformRqstspec =
{



 szSONInformRqstLst,
 szSONInformRqstExtLst
};
CmPAsnElmDef szSONInformRqst =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztSONInformRqst),
 &flagSz3M,
 0,
 (U8 *)(&szSONInformRqstspec),
 0L
};

CmPAsnSetSeqOfDef szENBX2GTPTLAsspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptENBX2GTPTLAs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztENBX2GTPTLAs),
 &flagSz3O,
 0,
 (U8 *) (&szENBX2GTPTLAsspec),
 0L
};
 CmPAsnElmDef *sz_ExtnENBX2ExtTLA_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnENBX2ExtTLA_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnENBX2ExtTLA_ExtIEsClsInfo =
{
 0,
 &sz_ExtnENBX2ExtTLA_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnENBX2ExtTLA_ExtIEsClsSpec =
{



 &sz_ExtnENBX2ExtTLA_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnENBX2ExtTLA_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnENBX2ExtTLA_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnENBX2ExtTLA_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnENBX2ExtTLA_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_ENBX2ExtTLA_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnENBX2ExtTLA_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_ENBX2ExtTLA_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_ENBX2ExtTLA_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_ENBX2ExtTLA_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_ENBX2ExtTLA_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_ENBX2ExtTLA_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_ENBX2ExtTLA_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_ENBX2ExtTLA_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ENBX2ExtTLA_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_ENBX2ExtTLA_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_ENBX2ExtTLA_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_ENBX2ExtTLA_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_ENBX2ExtTLA_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szENBX2ExtTLATkn[] =
{
 &szOptTportLyrAddr,
 &szOptENBX2GTPTLAs,
  &szTportLyrAddr,
  &szConstTerm,
 &szOptProtExtnCont_ENBX2ExtTLA_ExtIEs,
  &szProtExtnField_ENBX2ExtTLA_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szENBX2ExtTLAspec =
{



 3,
 0,
 0L,
 0L,
 &szENBX2ExtTLATkn[0],
 0
};
 CmPAsnElmDef szENBX2ExtTLA =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztENBX2ExtTLA),
 &flagSz3M,
 0,
 (U8 *)(&szENBX2ExtTLAspec),
 0L
};
CmPAsnSetSeqOfDef szENBX2ExtTLAsspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef szENBX2ExtTLAs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztENBX2ExtTLAs),
 &flagSz3M,
 0,
 (U8 *) (&szENBX2ExtTLAsspec),
 0L
};
 CmPAsnElmDef *sz_ExtnX2TNLConfigInfo_ExtIEsClsInst[] =
{
 &szENBX2ExtTLAs,
  &szENBX2ExtTLA,
  &szConstTerm,

};
 U32 sz_ExtnX2TNLConfigInfo_ExtIEsClsInstId[] =
{
 153,
  0xffffffff,
  0xffffffff
};
 CmPAsnClassInfo sz_ExtnX2TNLConfigInfo_ExtIEsClsInfo =
{
 3,
 &sz_ExtnX2TNLConfigInfo_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnX2TNLConfigInfo_ExtIEsClsSpec =
{



 &sz_ExtnX2TNLConfigInfo_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnX2TNLConfigInfo_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnX2TNLConfigInfo_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnX2TNLConfigInfo_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnX2TNLConfigInfo_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_X2TNLConfigInfo_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnX2TNLConfigInfo_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_X2TNLConfigInfo_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_X2TNLConfigInfo_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_X2TNLConfigInfo_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_X2TNLConfigInfo_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_X2TNLConfigInfo_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_X2TNLConfigInfo_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_X2TNLConfigInfo_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_X2TNLConfigInfo_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_X2TNLConfigInfo_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_X2TNLConfigInfo_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_X2TNLConfigInfo_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_X2TNLConfigInfo_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szX2TNLConfigInfoTkn[] =
{
 &szENBX2TLAs,
  &szTportLyrAddr,
  &szConstTerm,
 &szOptProtExtnCont_X2TNLConfigInfo_ExtIEs,
  &szProtExtnField_X2TNLConfigInfo_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szX2TNLConfigInfospec =
{



 1,
 0,
 0L,
 0L,
 &szX2TNLConfigInfoTkn[0],
 0
};
 CmPAsnElmDef szX2TNLConfigInfo =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztX2TNLConfigInfo),
 &flagSz3M,
 0,
 (U8 *)(&szX2TNLConfigInfospec),
 0L
};
 CmPAsnElmDef szOptX2TNLConfigInfo =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztX2TNLConfigInfo),
 &flagSz3O,
 0,
 (U8 *)(&szX2TNLConfigInfospec),
 0L
};

CmPAsnUIntDef szStratumLvlspec =
{



 0,
 3UL
};
CmPAsnElmDef szStratumLvl =
{



 CM_PASN_TET_UINT32,
 1,
 sizeof(SztStratumLvl),
 &flagSz3M,
 0,
 (U8 *)(&szStratumLvlspec),
 0L
};


CmPAsnTknEnum szSynchronizationStatusLst[3] =
{
 2,
 SztSynchronizationStatussynchronousEnum,
 SztSynchronizationStatusasynchronousEnum
};
CmPAsnEnumDef szSynchronizationStatusspec =
{



 szSynchronizationStatusLst,
 0L
};
CmPAsnElmDef szSynchronizationStatus =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztSynchronizationStatus),
 &flagSz3M,
 0,
 (U8 *)(&szSynchronizationStatusspec),
 0L
};

 CmPAsnElmDef *sz_ExtnTimeSynchronizationInfo_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTimeSynchronizationInfo_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTimeSynchronizationInfo_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTimeSynchronizationInfo_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTimeSynchronizationInfo_ExtIEsClsSpec =
{



 &sz_ExtnTimeSynchronizationInfo_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTimeSynchronizationInfo_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTimeSynchronizationInfo_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTimeSynchronizationInfo_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTimeSynchronizationInfo_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TimeSynchronizationInfo_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTimeSynchronizationInfo_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TimeSynchronizationInfo_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TimeSynchronizationInfo_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TimeSynchronizationInfo_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TimeSynchronizationInfo_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TimeSynchronizationInfo_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TimeSynchronizationInfo_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TimeSynchronizationInfo_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TimeSynchronizationInfo_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TimeSynchronizationInfo_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TimeSynchronizationInfo_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TimeSynchronizationInfo_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TimeSynchronizationInfo_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTimeSynchronizationInfoTkn[] =
{
 &szStratumLvl,
 &szSynchronizationStatus,
 &szOptProtExtnCont_TimeSynchronizationInfo_ExtIEs,
  &szProtExtnField_TimeSynchronizationInfo_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTimeSynchronizationInfospec =
{



 1,
 0,
 0L,
 0L,
 &szTimeSynchronizationInfoTkn[0],
 0
};
 CmPAsnElmDef szTimeSynchronizationInfo =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTimeSynchronizationInfo),
 &flagSz3M,
 0,
 (U8 *)(&szTimeSynchronizationInfospec),
 0L
};
 CmPAsnElmDef *sz_ExtnSONInformReply_ExtIEsClsInst[] =
{
 &szTimeSynchronizationInfo
};
 U32 sz_ExtnSONInformReply_ExtIEsClsInstId[] =
{
 149
};
 CmPAsnClassInfo sz_ExtnSONInformReply_ExtIEsClsInfo =
{
 1,
 &sz_ExtnSONInformReply_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSONInformReply_ExtIEsClsSpec =
{



 &sz_ExtnSONInformReply_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnSONInformReply_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnSONInformReply_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnSONInformReply_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnSONInformReply_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_SONInformReply_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnSONInformReply_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SONInformReply_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_SONInformReply_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_SONInformReply_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_SONInformReply_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_SONInformReply_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_SONInformReply_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_SONInformReply_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SONInformReply_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_SONInformReply_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_SONInformReply_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SONInformReply_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_SONInformReply_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szSONInformReplyTkn[] =
{
 &szOptX2TNLConfigInfo,
 &szOptProtExtnCont_SONInformReply_ExtIEs,
  &szProtExtnField_SONInformReply_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szSONInformReplyspec =
{



 2,
 0,
 0L,
 0L,
 &szSONInformReplyTkn[0],
 0
};
 CmPAsnElmDef szSONInformReply =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztSONInformReply),
 &flagSz3M,
 0,
 (U8 *)(&szSONInformReplyspec),
 0L
};
 CmPAsnElmDef *szSONInformTkn[] =
{
 &szSONInformRqst,
 &szSONInformReply,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szSONInformspec =
{



 2,
 0,
 &szSONInformTkn[0]
};
CmPAsnElmDef szSONInform =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztSONInform),
 &flagSz3M,
 0L,
 (U8 *)(&szSONInformspec),
 0L
};
 CmPAsnElmDef *sz_ExtnTgeteNB_ID_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTgeteNB_ID_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTgeteNB_ID_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTgeteNB_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTgeteNB_ID_ExtIEsClsSpec =
{



 &sz_ExtnTgeteNB_ID_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTgeteNB_ID_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTgeteNB_ID_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTgeteNB_ID_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTgeteNB_ID_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TgeteNB_ID_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTgeteNB_ID_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TgeteNB_ID_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TgeteNB_ID_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TgeteNB_ID_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TgeteNB_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TgeteNB_ID_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TgeteNB_ID_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TgeteNB_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TgeteNB_ID_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TgeteNB_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TgeteNB_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TgeteNB_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TgeteNB_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTgeteNB_IDTkn[] =
{
 &szGlobal_ENB_ID,
 &szTAI,
 &szOptProtExtnCont_TgeteNB_ID_ExtIEs,
  &szProtExtnField_TgeteNB_ID_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTgeteNB_IDspec =
{



 1,
 0,
 0L,
 0L,
 &szTgeteNB_IDTkn[0],
 0
};
 CmPAsnElmDef szTgeteNB_ID =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTgeteNB_ID),
 &flagSz3M,
 0,
 (U8 *)(&szTgeteNB_IDspec),
 0L
};
 CmPAsnElmDef *sz_ExtnSrceNB_ID_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnSrceNB_ID_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnSrceNB_ID_ExtIEsClsInfo =
{
 0,
 &sz_ExtnSrceNB_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSrceNB_ID_ExtIEsClsSpec =
{



 &sz_ExtnSrceNB_ID_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnSrceNB_ID_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnSrceNB_ID_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnSrceNB_ID_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnSrceNB_ID_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_SrceNB_ID_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnSrceNB_ID_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SrceNB_ID_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_SrceNB_ID_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_SrceNB_ID_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_SrceNB_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_SrceNB_ID_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_SrceNB_ID_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_SrceNB_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SrceNB_ID_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_SrceNB_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_SrceNB_ID_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SrceNB_ID_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_SrceNB_ID_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szSrceNB_IDTkn[] =
{
 &szGlobal_ENB_ID,
 &szTAI,
 &szOptProtExtnCont_SrceNB_ID_ExtIEs,
  &szProtExtnField_SrceNB_ID_ExtIEs,
  &szConstTerm,
 &szConstTerm
};
CmPAsnSetSeqDef szSrceNB_IDspec =
{



 1,
 0,
 0L,
 0L,
 &szSrceNB_IDTkn[0],
 0
};
 CmPAsnElmDef szSrceNB_ID =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztSrceNB_ID),
 &flagSz3M,
 0,
 (U8 *)(&szSrceNB_IDspec),
 0L
};
 CmPAsnElmDef *sz_ExtnSONConfigTfr_ExtIEsClsInst[] =
{
 &szX2TNLConfigInfo
};
 U32 sz_ExtnSONConfigTfr_ExtIEsClsInstId[] =
{
 152
};
 CmPAsnClassInfo sz_ExtnSONConfigTfr_ExtIEsClsInfo =
{
 1,
 &sz_ExtnSONConfigTfr_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSONConfigTfr_ExtIEsClsSpec =
{



 &sz_ExtnSONConfigTfr_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnSONConfigTfr_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnSONConfigTfr_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnSONConfigTfr_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnSONConfigTfr_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_SONConfigTfr_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnSONConfigTfr_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SONConfigTfr_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_SONConfigTfr_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_SONConfigTfr_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_SONConfigTfr_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_SONConfigTfr_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_SONConfigTfr_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_SONConfigTfr_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SONConfigTfr_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_SONConfigTfr_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_SONConfigTfr_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SONConfigTfr_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_SONConfigTfr_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szSONConfigTfrTkn[] =
{
 &szTgeteNB_ID,
 &szSrceNB_ID,
 &szSONInform,
 &szOptProtExtnCont_SONConfigTfr_ExtIEs,
  &szProtExtnField_SONConfigTfr_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szSONConfigTfrspec =
{



 1,
 0,
 0L,
 0L,
 &szSONConfigTfrTkn[0],
 0
};
 CmPAsnElmDef szSONConfigTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztSONConfigTfr),
 &flagSz3M,
 0,
 (U8 *)(&szSONConfigTfrspec),
 0L
};
CmPAsnOctStrDef szSrc_ToTget_TprntContspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szSrc_ToTget_TprntCont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztSrc_ToTget_TprntCont),
 &flagSz3M,
 0,
 (U8 *) (&szSrc_ToTget_TprntContspec),
 0L
};
CmPAsnOctStrDef szSrcBSS_ToTgetBSS_TprntContspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szSrcBSS_ToTgetBSS_TprntCont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztSrcBSS_ToTgetBSS_TprntCont),
 &flagSz3M,
 0,
 (U8 *) (&szSrcBSS_ToTgetBSS_TprntContspec),
 0L
};

CmPAsnTknEnum szSRVCCOperationPossibleLst[2] =
{
 1,
 SztSRVCCOperationPossiblepossibleEnum
};
CmPAsnEnumDef szSRVCCOperationPossiblespec =
{



 szSRVCCOperationPossibleLst,
 0L
};
CmPAsnElmDef szSRVCCOperationPossible =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztSRVCCOperationPossible),
 &flagSz3M,
 0,
 (U8 *)(&szSRVCCOperationPossiblespec),
 0L
};


CmPAsnTknEnum szSRVCCHOIndLst[3] =
{
 2,
 SztSRVCCHOIndpSandCSEnum,
 SztSRVCCHOIndcSonlyEnum
};
CmPAsnEnumDef szSRVCCHOIndspec =
{



 szSRVCCHOIndLst,
 0L
};
CmPAsnElmDef szSRVCCHOInd =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztSRVCCHOInd),
 &flagSz3M,
 0,
 (U8 *)(&szSRVCCHOIndspec),
 0L
};


CmPAsnUIntDef szSubscriberProfileIDforRFPspec =
{



 1,
 256UL
};
CmPAsnElmDef szSubscriberProfileIDforRFP =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztSubscriberProfileIDforRFP),
 &flagSz3M,
 0,
 (U8 *)(&szSubscriberProfileIDforRFPspec),
 0L
};
CmPAsnElmDef szOptSubscriberProfileIDforRFP =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztSubscriberProfileIDforRFP),
 &flagSz3O,
 0,
 (U8 *)(&szSubscriberProfileIDforRFPspec),
 0L
};

CmPAsnSetSeqOfDef szUE_HistoryInformspec =
{



 1,
 16,
 3*sizeof(U32)
};
 CmPAsnElmDef szUE_HistoryInform =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztUE_HistoryInform),
 &flagSz3M,
 0,
 (U8 *) (&szUE_HistoryInformspec),
 0L
};
 CmPAsnElmDef *sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInst[] =
{
 &szMobilityInform
};
 U32 sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInstId[] =
{
 175
};
 CmPAsnClassInfo sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInfo =
{
 1,
 &sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsSpec =
{



 &sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szSrceNB_ToTgeteNB_TprntContTkn[] =
{
 &szRRC_Cont,
 &szOptE_RABInformLst,
  &szProtIE_Field_E_RABInformLstIEs,
  &szConstTerm,
 &szEUTRAN_CGI,
 &szOptSubscriberProfileIDforRFP,
 &szUE_HistoryInform,
  &szLastVisitedCell_Item,
  &szConstTerm,
 &szOptProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs,
  &szProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szSrceNB_ToTgeteNB_TprntContspec =
{



 3,
 0,
 0L,
 0L,
 &szSrceNB_ToTgeteNB_TprntContTkn[0],
 0
};
 CmPAsnElmDef szSrceNB_ToTgeteNB_TprntCont =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztSrceNB_ToTgeteNB_TprntCont),
 &flagSz3M,
 0,
 (U8 *)(&szSrceNB_ToTgeteNB_TprntContspec),
 0L
};
CmPAsnOctStrDef szSrcRNC_ToTgetRNC_TprntContspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szSrcRNC_ToTgetRNC_TprntCont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztSrcRNC_ToTgetRNC_TprntCont),
 &flagSz3M,
 0,
 (U8 *) (&szSrcRNC_ToTgetRNC_TprntContspec),
 0L
};
CmPAsnSetSeqOfDef szSrvdPLMNsspec =
{



 1,
 32,
 3*sizeof(U32)
};
 CmPAsnElmDef szSrvdPLMNs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztSrvdPLMNs),
 &flagSz3M,
 0,
 (U8 *) (&szSrvdPLMNsspec),
 0L
};
CmPAsnSetSeqOfDef szSrvdGroupIDsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szSrvdGroupIDs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztSrvdGroupIDs),
 &flagSz3M,
 0,
 (U8 *) (&szSrvdGroupIDsspec),
 0L
};
CmPAsnSetSeqOfDef szSrvdMMECsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szSrvdMMECs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztSrvdMMECs),
 &flagSz3M,
 0,
 (U8 *) (&szSrvdMMECsspec),
 0L
};
 CmPAsnElmDef *sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInfo =
{
 0,
 &sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSrvdGUMMEIsItem_ExtIEsClsSpec =
{



 &sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnSrvdGUMMEIsItem_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnSrvdGUMMEIsItem_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnSrvdGUMMEIsItem_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_SrvdGUMMEIsItem_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnSrvdGUMMEIsItem_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SrvdGUMMEIsItem_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_SrvdGUMMEIsItem_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_SrvdGUMMEIsItem_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_SrvdGUMMEIsItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_SrvdGUMMEIsItem_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_SrvdGUMMEIsItem_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_SrvdGUMMEIsItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_SrvdGUMMEIsItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_SrvdGUMMEIsItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_SrvdGUMMEIsItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szSrvdGUMMEIsItemTkn[] =
{
 &szSrvdPLMNs,
  &szTBCD_STRING,
  &szConstTerm,
 &szSrvdGroupIDs,
  &szMME_Group_ID,
  &szConstTerm,
 &szSrvdMMECs,
  &szMME_Code,
  &szConstTerm,
 &szOptProtExtnCont_SrvdGUMMEIsItem_ExtIEs,
  &szProtExtnField_SrvdGUMMEIsItem_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szSrvdGUMMEIsItemspec =
{



 1,
 0,
 0L,
 0L,
 &szSrvdGUMMEIsItemTkn[0],
 0
};
 CmPAsnElmDef szSrvdGUMMEIsItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztSrvdGUMMEIsItem),
 &flagSz3M,
 0,
 (U8 *)(&szSrvdGUMMEIsItemspec),
 0L
};
CmPAsnSetSeqOfDef szSrvdGUMMEIsspec =
{



 1,
 8,
 3*sizeof(U32)
};
 CmPAsnElmDef szSrvdGUMMEIs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztSrvdGUMMEIs),
 &flagSz3M,
 0,
 (U8 *) (&szSrvdGUMMEIsspec),
 0L
};
 CmPAsnElmDef *sz_ExtnSuppTAs_Item_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnSuppTAs_Item_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnSuppTAs_Item_ExtIEsClsInfo =
{
 0,
 &sz_ExtnSuppTAs_Item_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnSuppTAs_Item_ExtIEsClsSpec =
{



 &sz_ExtnSuppTAs_Item_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnSuppTAs_Item_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnSuppTAs_Item_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnSuppTAs_Item_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnSuppTAs_Item_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_SuppTAs_Item_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnSuppTAs_Item_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_SuppTAs_Item_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_SuppTAs_Item_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_SuppTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_SuppTAs_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_SuppTAs_Item_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_SuppTAs_Item_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_SuppTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SuppTAs_Item_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_SuppTAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_SuppTAs_Item_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_SuppTAs_Item_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_SuppTAs_Item_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szSuppTAs_ItemTkn[] =
{
 &szTAC,
 &szBPLMNs,
  &szTBCD_STRING,
  &szConstTerm,
 &szOptProtExtnCont_SuppTAs_Item_ExtIEs,
  &szProtExtnField_SuppTAs_Item_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szSuppTAs_Itemspec =
{



 1,
 0,
 0L,
 0L,
 &szSuppTAs_ItemTkn[0],
 0
};
 CmPAsnElmDef szSuppTAs_Item =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztSuppTAs_Item),
 &flagSz3M,
 0,
 (U8 *)(&szSuppTAs_Itemspec),
 0L
};
CmPAsnSetSeqOfDef szSuppTAsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szSuppTAs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztSuppTAs),
 &flagSz3M,
 0,
 (U8 *) (&szSuppTAsspec),
 0L
};
 CmPAsnElmDef *sz_ExtnS_TMSI_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnS_TMSI_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnS_TMSI_ExtIEsClsInfo =
{
 0,
 &sz_ExtnS_TMSI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnS_TMSI_ExtIEsClsSpec =
{



 &sz_ExtnS_TMSI_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnS_TMSI_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnS_TMSI_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnS_TMSI_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnS_TMSI_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_S_TMSI_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnS_TMSI_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_S_TMSI_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_S_TMSI_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_S_TMSI_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_S_TMSI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_S_TMSI_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_S_TMSI_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_S_TMSI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_S_TMSI_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_S_TMSI_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_S_TMSI_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_S_TMSI_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_S_TMSI_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szS_TMSITkn[] =
{
 &szMME_Code,
 &szM_TMSI,
 &szOptProtExtnCont_S_TMSI_ExtIEs,
  &szProtExtnField_S_TMSI_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szS_TMSIspec =
{



 1,
 0,
 0L,
 0L,
 &szS_TMSITkn[0],
 0
};
 CmPAsnElmDef szS_TMSI =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztS_TMSI),
 &flagSz3M,
 0,
 (U8 *)(&szS_TMSIspec),
 0L
};
CmPAsnSetSeqOfDef szTAILstforWarningspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szTAILstforWarning =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztTAILstforWarning),
 &flagSz3M,
 0,
 (U8 *) (&szTAILstforWarningspec),
 0L
};
 CmPAsnElmDef *szTgetIDTkn[] =
{
 &szTgeteNB_ID,
 &szTgetRNC_ID,
 &szCGI,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szTgetIDspec =
{



 3,
 0,
 &szTgetIDTkn[0]
};
CmPAsnElmDef szTgetID =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztTgetID),
 &flagSz3M,
 0L,
 (U8 *)(&szTgetIDspec),
 0L
};
 CmPAsnElmDef *sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsSpec =
{



 &sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTgeteNB_ToSrceNB_TprntContTkn[] =
{
 &szRRC_Cont,
 &szOptProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs,
  &szProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTgeteNB_ToSrceNB_TprntContspec =
{



 1,
 0,
 0L,
 0L,
 &szTgeteNB_ToSrceNB_TprntContTkn[0],
 0
};
 CmPAsnElmDef szTgeteNB_ToSrceNB_TprntCont =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTgeteNB_ToSrceNB_TprntCont),
 &flagSz3M,
 0,
 (U8 *)(&szTgeteNB_ToSrceNB_TprntContspec),
 0L
};
CmPAsnOctStrDef szTget_ToSrc_TprntContspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szTget_ToSrc_TprntCont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztTget_ToSrc_TprntCont),
 &flagSz3M,
 0,
 (U8 *) (&szTget_ToSrc_TprntContspec),
 0L
};
CmPAsnOctStrDef szTgetRNC_ToSrcRNC_TprntContspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szTgetRNC_ToSrcRNC_TprntCont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztTgetRNC_ToSrcRNC_TprntCont),
 &flagSz3M,
 0,
 (U8 *) (&szTgetRNC_ToSrcRNC_TprntContspec),
 0L
};
CmPAsnOctStrDef szTgetBSS_ToSrcBSS_TprntContspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szTgetBSS_ToSrcBSS_TprntCont =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztTgetBSS_ToSrcBSS_TprntCont),
 &flagSz3M,
 0,
 (U8 *) (&szTgetBSS_ToSrcBSS_TprntContspec),
 0L
};

CmPAsnTknEnum szTimeToWaitLst[7] =
{
 6,
 SztTimeToWaitv1sEnum,
 SztTimeToWaitv2sEnum,
 SztTimeToWaitv5sEnum,
 SztTimeToWaitv10sEnum,
 SztTimeToWaitv20sEnum,
 SztTimeToWaitv60sEnum
};
CmPAsnEnumDef szTimeToWaitspec =
{



 szTimeToWaitLst,
 0L
};
CmPAsnElmDef szTimeToWait =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztTimeToWait),
 &flagSz3M,
 0,
 (U8 *)(&szTimeToWaitspec),
 0L
};

CmPAsnOctStrDef szE_UTRAN_Trace_IDspec =
{



 8,
 8
};
CmPAsnElmDef szE_UTRAN_Trace_ID =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztE_UTRAN_Trace_ID),
 &flagSz3M,
 0,
 (U8 *) (&szE_UTRAN_Trace_IDspec),
 0L
};

CmPAsnTknEnum szTraceDepthLst[7] =
{
 6,
 SztTraceDepthminimumEnum,
 SztTraceDepthmediumEnum,
 SztTraceDepthmaximumEnum,
 SztTraceDepthminimumWithoutVendorSpecificExtnEnum,
 SztTraceDepthmediumWithoutVendorSpecificExtnEnum,
 SztTraceDepthmaximumWithoutVendorSpecificExtnEnum
};
CmPAsnEnumDef szTraceDepthspec =
{



 szTraceDepthLst,
 0L
};
CmPAsnElmDef szTraceDepth =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztTraceDepth),
 &flagSz3M,
 0,
 (U8 *)(&szTraceDepthspec),
 0L
};

 CmPAsnElmDef *sz_ExtnTraceActvn_ExtIEsClsInst[] =
{
 &szMDT_Config
};
 U32 sz_ExtnTraceActvn_ExtIEsClsInstId[] =
{
 162
};
 CmPAsnClassInfo sz_ExtnTraceActvn_ExtIEsClsInfo =
{
 1,
 &sz_ExtnTraceActvn_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTraceActvn_ExtIEsClsSpec =
{



 &sz_ExtnTraceActvn_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTraceActvn_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTraceActvn_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTraceActvn_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTraceActvn_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TraceActvn_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTraceActvn_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TraceActvn_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TraceActvn_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TraceActvn_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TraceActvn_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TraceActvn_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TraceActvn_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TraceActvn_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TraceActvn_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TraceActvn_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TraceActvn_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TraceActvn_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TraceActvn_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTraceActvnTkn[] =
{
 &szE_UTRAN_Trace_ID,
 &szIntfsToTrace,
 &szTraceDepth,
 &szTportLyrAddr,
 &szOptProtExtnCont_TraceActvn_ExtIEs,
  &szProtExtnField_TraceActvn_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTraceActvnspec =
{



 1,
 0,
 0L,
 0L,
 &szTraceActvnTkn[0],
 0
};
 CmPAsnElmDef szTraceActvn =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTraceActvn),
 &flagSz3M,
 0,
 (U8 *)(&szTraceActvnspec),
 0L
};

CmPAsnUIntDef szTrafficLoadReductionIndspec =
{



 1,
 99UL
};
CmPAsnElmDef szTrafficLoadReductionInd =
{



 CM_PASN_TET_UINT32,
 0,
 sizeof(SztTrafficLoadReductionInd),
 &flagSz3M,
 0,
 (U8 *)(&szTrafficLoadReductionIndspec),
 0L
};

 CmPAsnElmDef *sz_ExtnTunnel_Inform_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTunnel_Inform_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTunnel_Inform_ExtIEsClsInfo =
{
 0,
 &sz_ExtnTunnel_Inform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTunnel_Inform_ExtIEsClsSpec =
{



 &sz_ExtnTunnel_Inform_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTunnel_Inform_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTunnel_Inform_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTunnel_Inform_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTunnel_Inform_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_Tunnel_Inform_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTunnel_Inform_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_Tunnel_Inform_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_Tunnel_Inform_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_Tunnel_Inform_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_Tunnel_Inform_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_Tunnel_Inform_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_Tunnel_Inform_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_Tunnel_Inform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_Tunnel_Inform_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_Tunnel_Inform_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_Tunnel_Inform_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_Tunnel_Inform_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_Tunnel_Inform_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szTunnelInformTkn[] =
{
 &szTportLyrAddr,
 &szOptPort_Number,
 &szOptProtExtnCont_Tunnel_Inform_ExtIEs,
  &szProtExtnField_Tunnel_Inform_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTunnelInformspec =
{



 2,
 0,
 0L,
 0L,
 &szTunnelInformTkn[0],
 0
};
 CmPAsnElmDef szTunnelInform =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTunnelInform),
 &flagSz3M,
 0,
 (U8 *)(&szTunnelInformspec),
 0L
};
 CmPAsnElmDef *sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInfo =
{
 0,
 &sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnUEAgg_MaxBitrates_ExtIEsClsSpec =
{



 &sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnUEAgg_MaxBitrates_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnUEAgg_MaxBitrates_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnUEAgg_MaxBitrates_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_UEAgg_MaxBitrates_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnUEAgg_MaxBitrates_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_UEAgg_MaxBitrates_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_UEAgg_MaxBitrates_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_UEAgg_MaxBitrates_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_UEAgg_MaxBitrates_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_UEAgg_MaxBitrates_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_UEAgg_MaxBitrates_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_UEAgg_MaxBitrates_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_UEAgg_MaxBitrates_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_UEAgg_MaxBitrates_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_UEAgg_MaxBitrates_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szUEAggMaxBitrateTkn[] =
{
 &szBitRate,
 &szBitRate,
 &szOptProtExtnCont_UEAgg_MaxBitrates_ExtIEs,
  &szProtExtnField_UEAgg_MaxBitrates_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUEAggMaxBitratespec =
{



 1,
 0,
 0L,
 0L,
 &szUEAggMaxBitrateTkn[0],
 0
};
 CmPAsnElmDef szUEAggMaxBitrate =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUEAggMaxBitrate),
 &flagSz3M,
 0,
 (U8 *)(&szUEAggMaxBitratespec),
 0L
};
 CmPAsnElmDef *sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInfo =
{
 0,
 &sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnUE_S1AP_ID_pair_ExtIEsClsSpec =
{



 &sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnUE_S1AP_ID_pair_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnUE_S1AP_ID_pair_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnUE_S1AP_ID_pair_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_UE_S1AP_ID_pair_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnUE_S1AP_ID_pair_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_UE_S1AP_ID_pair_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_UE_S1AP_ID_pair_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_UE_S1AP_ID_pair_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_UE_S1AP_ID_pair_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_UE_S1AP_ID_pair_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_UE_S1AP_ID_pair_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_UE_S1AP_ID_pair_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_UE_S1AP_ID_pair_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_UE_S1AP_ID_pair_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_UE_S1AP_ID_pair_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szUE_S1AP_ID_pairTkn[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szOptProtExtnCont_UE_S1AP_ID_pair_ExtIEs,
  &szProtExtnField_UE_S1AP_ID_pair_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUE_S1AP_ID_pairspec =
{



 1,
 0,
 0L,
 0L,
 &szUE_S1AP_ID_pairTkn[0],
 0
};
 CmPAsnElmDef szUE_S1AP_ID_pair =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUE_S1AP_ID_pair),
 &flagSz3M,
 0,
 (U8 *)(&szUE_S1AP_ID_pairspec),
 0L
};
 CmPAsnElmDef *szUE_S1AP_IDsTkn[] =
{
 &szUE_S1AP_ID_pair,
 &szMME_UE_S1AP_ID,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szUE_S1AP_IDsspec =
{



 2,
 0,
 &szUE_S1AP_IDsTkn[0]
};
CmPAsnElmDef szUE_S1AP_IDs =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztUE_S1AP_IDs),
 &flagSz3M,
 0L,
 (U8 *)(&szUE_S1AP_IDsspec),
 0L
};
 CmPAsnElmDef *sz_ExtnUE_assocLogS1_ConItemExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnUE_assocLogS1_ConItemExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnUE_assocLogS1_ConItemExtIEsClsInfo =
{
 0,
 &sz_ExtnUE_assocLogS1_ConItemExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnUE_assocLogS1_ConItemExtIEsClsSpec =
{



 &sz_ExtnUE_assocLogS1_ConItemExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnUE_assocLogS1_ConItemExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnUE_assocLogS1_ConItemExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnUE_assocLogS1_ConItemExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnUE_assocLogS1_ConItemExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_UE_assocLogS1_ConItemExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnUE_assocLogS1_ConItemExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_UE_assocLogS1_ConItemExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_UE_assocLogS1_ConItemExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_UE_assocLogS1_ConItemExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_UE_assocLogS1_ConItemExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_UE_assocLogS1_ConItemExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_UE_assocLogS1_ConItemExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_UE_assocLogS1_ConItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_UE_assocLogS1_ConItemExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_UE_assocLogS1_ConItemExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_UE_assocLogS1_ConItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_UE_assocLogS1_ConItemExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_UE_assocLogS1_ConItemExtIEsspec),
 0L
};
 CmPAsnElmDef *szUE_assocLogS1_ConItemTkn[] =
{
 &szOptMME_UE_S1AP_ID,
 &szOptENB_UE_S1AP_ID,
 &szOptProtExtnCont_UE_assocLogS1_ConItemExtIEs,
  &szProtExtnField_UE_assocLogS1_ConItemExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUE_assocLogS1_ConItemspec =
{



 3,
 0,
 0L,
 0L,
 &szUE_assocLogS1_ConItemTkn[0],
 0
};
 CmPAsnElmDef szUE_assocLogS1_ConItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUE_assocLogS1_ConItem),
 &flagSz3M,
 0,
 (U8 *)(&szUE_assocLogS1_ConItemspec),
 0L
};
CmPAsnBitStrDef szUEIdentityIdxValuespec =
{



 10,
 10
};
CmPAsnElmDef szUEIdentityIdxValue =
{



 CM_PASN_TET_BITSTR,
 0,
 sizeof(SztUEIdentityIdxValue),
 &flagSz3M,
 0,
 (U8 *) (&szUEIdentityIdxValuespec),
 0L
};
 CmPAsnElmDef *szUEPagIDTkn[] =
{
 &szS_TMSI,
 &szIMSI,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szUEPagIDspec =
{



 2,
 0,
 &szUEPagIDTkn[0]
};
CmPAsnElmDef szUEPagID =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztUEPagID),
 &flagSz3M,
 0L,
 (U8 *)(&szUEPagIDspec),
 0L
};
CmPAsnOctStrDef szUERadioCapbltyspec =
{



 0,
 0x7FFFFFFF
};
CmPAsnElmDef szUERadioCapblty =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztUERadioCapblty),
 &flagSz3M,
 0,
 (U8 *) (&szUERadioCapbltyspec),
 0L
};
 CmPAsnElmDef *sz_ExtnUESecurCapabilities_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnUESecurCapabilities_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnUESecurCapabilities_ExtIEsClsInfo =
{
 0,
 &sz_ExtnUESecurCapabilities_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnUESecurCapabilities_ExtIEsClsSpec =
{



 &sz_ExtnUESecurCapabilities_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnUESecurCapabilities_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnUESecurCapabilities_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnUESecurCapabilities_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnUESecurCapabilities_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_UESecurCapabilities_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnUESecurCapabilities_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_UESecurCapabilities_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_UESecurCapabilities_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_UESecurCapabilities_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_UESecurCapabilities_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_UESecurCapabilities_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_UESecurCapabilities_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_UESecurCapabilities_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_UESecurCapabilities_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_UESecurCapabilities_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_UESecurCapabilities_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_UESecurCapabilities_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_UESecurCapabilities_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szUESecurCapabilitiesTkn[] =
{
 &szEncryptionAlgorithms,
 &szIntegrityProtectionAlgorithms,
 &szOptProtExtnCont_UESecurCapabilities_ExtIEs,
  &szProtExtnField_UESecurCapabilities_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUESecurCapabilitiesspec =
{



 1,
 0,
 0L,
 0L,
 &szUESecurCapabilitiesTkn[0],
 0
};
 CmPAsnElmDef szUESecurCapabilities =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUESecurCapabilities),
 &flagSz3M,
 0,
 (U8 *)(&szUESecurCapabilitiesspec),
 0L
};

CmPAsnTknEnum szVoiceSupportMatchIndicatorLst[3] =
{
 2,
 SztVoiceSupportMatchIndicatorsupportedEnum,
 SztVoiceSupportMatchIndicatornot_supportedEnum
};
CmPAsnEnumDef szVoiceSupportMatchIndicatorspec =
{



 szVoiceSupportMatchIndicatorLst,
 0L
};
CmPAsnElmDef szVoiceSupportMatchIndicator =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztVoiceSupportMatchIndicator),
 &flagSz3M,
 0,
 (U8 *)(&szVoiceSupportMatchIndicatorspec),
 0L
};

 CmPAsnElmDef *szWarningAreaLstTkn[] =
{
 &szECGILst,
  &szEUTRAN_CGI,
  &szConstTerm,
 &szTAILstforWarning,
  &szTAI,
  &szConstTerm,
 &szEmergencyAreaIDLst,
  &szEmergencyAreaID,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szWarningAreaLstspec =
{



 3,
 0,
 &szWarningAreaLstTkn[0]
};
CmPAsnElmDef szWarningAreaLst =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztWarningAreaLst),
 &flagSz3M,
 0L,
 (U8 *)(&szWarningAreaLstspec),
 0L
};
CmPAsnOctStrDef szWarningTypspec =
{



 2,
 2
};
CmPAsnElmDef szWarningTyp =
{



 CM_PASN_TET_OCTSTR,
 0,
 sizeof(SztWarningTyp),
 &flagSz3M,
 0,
 (U8 *) (&szWarningTypspec),
 0L
};
CmPAsnOctStrDef szWarningSecurInfospec =
{



 50,
 50
};
CmPAsnElmDef szWarningSecurInfo =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztWarningSecurInfo),
 &flagSz3M,
 0,
 (U8 *) (&szWarningSecurInfospec),
 0L
};
CmPAsnOctStrDef szWarningMsgContentsspec =
{



 1,
 9600
};
CmPAsnElmDef szWarningMsgContents =
{



 CM_PASN_TET_OCTSTRXL,
 0,
 sizeof(SztWarningMsgContents),
 &flagSz3M,
 0,
 (U8 *) (&szWarningMsgContentsspec),
 0L
};
 CmPAsnElmDef *sz_ValueHovrReqdIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szHovrTyp,
 &szCause,
 &szTgetID,
 &szDirect_Fwding_Path_Avlblty,
 &szSRVCCHOInd,
 &szSrc_ToTget_TprntCont,
 &szSrc_ToTget_TprntCont,
 &szMSClassmark2,
 &szMSClassmark3,
 &szCSG_Id,
 &szCellAccessMode,
 &szPS_ServiceNotAvailable
};
 U32 sz_ValueHovrReqdIEsClsInstId[] =
{
 0,
 8,
 1,
 2,
 4,
 79,
 125,
 104,
 138,
 132,
 133,
 127,
 145,
 150
};
SzMsgConInf szHovrReqdIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 1, 0, 0x2 },
  { 2, 1, 0x2 },
  { 4, 0, 0x2 },
  { 79, 1, 0x1 },
  { 125, 0, 0x1 },
  { 104, 0, 0x2 },
  { 138, 0, 0x1 },
  { 132, 0, 0x1 },
  { 133, 1, 0x1 },
  { 127, 0, 0x1 },
  { 145, 0, 0x1 },
  { 150, 1, 0x1 }
 },
 14,
 6
};
 CmPAsnClassInfo sz_ValueHovrReqdIEsClsInfo =
{
 14,
 &sz_ValueHovrReqdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrReqdIEsClsSpec =
{



 &sz_ValueHovrReqdIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrReqdIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrReqdIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrReqdIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrReqdIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrReqdIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrReqdIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrReqdIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrReqdIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrReqdIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrReqdIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrReqdIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrReqdIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrReqdIEs *protIe = 0L;
 SztProtIE_Field_HovrReqdIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrReqdIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrReqdIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrReqdIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrReqdIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrReqdIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrReqdIEs),
 &flagSz3M,
 szProtIE_Cont_HovrReqdIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrReqdIEsspec),
 0L
};
 CmPAsnElmDef *szHovrReqdTkn[] =
{
 &szProtIE_Cont_HovrReqdIEs,
  &szProtIE_Field_HovrReqdIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrReqdspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrReqdTkn[0],
 0
};
 CmPAsnElmDef szHovrReqd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrReqd),
 &flagSz3M,
 0,
 (U8 *)(&szHovrReqdspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABDataFwdingItem_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABDataFwdingItem_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABDataFwdingItem_ExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABDataFwdingItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABDataFwdingItem_ExtIEsClsSpec =
{



 &sz_ExtnE_RABDataFwdingItem_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABDataFwdingItem_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABDataFwdingItem_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABDataFwdingItem_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABDataFwdingItem_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABDataFwdingItem_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABDataFwdingItem_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABDataFwdingItem_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABDataFwdingItem_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABDataFwdingItem_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABDataFwdingItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABDataFwdingItem_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABDataFwdingItem_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABDataFwdingItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABDataFwdingItem_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABDataFwdingItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABDataFwdingItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABDataFwdingItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABDataFwdingItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABDataFwdingItemTkn[] =
{
 &szE_RAB_ID,
 &szOptTportLyrAddr,
 &szOptGTP_TEID,
 &szOptTportLyrAddr,
 &szOptGTP_TEID,
 &szOptProtExtnCont_E_RABDataFwdingItem_ExtIEs,
  &szProtExtnField_E_RABDataFwdingItem_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABDataFwdingItemspec =
{



 5,
 0,
 0L,
 0L,
 &szE_RABDataFwdingItemTkn[0],
 0
};
 CmPAsnElmDef szE_RABDataFwdingItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABDataFwdingItem),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABDataFwdingItemspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABDataFwdingItemIEsClsInst[] =
{
 &szE_RABDataFwdingItem
};
 U32 sz_ValueE_RABDataFwdingItemIEsClsInstId[] =
{
 14
};
SzMsgConInf szE_RABDataFwdingItemIEsConInf =
{
 {
  { 14, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABDataFwdingItemIEsClsInfo =
{
 1,
 &sz_ValueE_RABDataFwdingItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABDataFwdingItemIEsClsSpec =
{



 &sz_ValueE_RABDataFwdingItemIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABDataFwdingItemIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABDataFwdingItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABDataFwdingItemIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABDataFwdingItemIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABDataFwdingItemIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABDataFwdingItemIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABDataFwdingItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABDataFwdingItemIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABDataFwdingItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABDataFwdingItemIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABDataFwdingItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABDataFwdingItemIEsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_ContLst_E_RABDataFwdingItemIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_ContLst_E_RABDataFwdingItemIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtIE_ContLst_E_RABDataFwdingItemIEsspec),
 0L
};


 CmPAsnElmDef *sz_ValueHovrCmmdIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szHovrTyp,
 &szNASSecurParamsfromE_UTRAN,
 &szProtIE_ContLst_E_RABDataFwdingItemIEs,
  &szProtIE_Field_E_RABDataFwdingItemIEs,
  &szConstTerm,
 &szE_RABLst,
  &szProtIE_Field_E_RABItemIEs,
  &szConstTerm,
 &szTget_ToSrc_TprntCont,
 &szTget_ToSrc_TprntCont,
 &szCriticalityDiag
};
 U32 sz_ValueHovrCmmdIEsClsInstId[] =
{
 0,
 8,
 1,
 135,
 12,
  0xffffffff,
  0xffffffff,
 13,
  0xffffffff,
  0xffffffff,
 123,
 139,
 58
};
SzMsgConInf szHovrCmmdIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 1, 0, 0x2 },
  { 135, 0, 0x1 },
  { 12, 1, 0x1 },
  { 13, 1, 0x1 },
  { 123, 0, 0x2 },
  { 139, 0, 0x1 },
  { 58, 1, 0x1 }
 },
 9,
 4
};
 CmPAsnClassInfo sz_ValueHovrCmmdIEsClsInfo =
{
 13,
 &sz_ValueHovrCmmdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrCmmdIEsClsSpec =
{



 &sz_ValueHovrCmmdIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrCmmdIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrCmmdIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrCmmdIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrCmmdIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrCmmdIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrCmmdIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrCmmdIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrCmmdIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrCmmdIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrCmmdIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrCmmdIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrCmmdIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrCmmdIEs *protIe = 0L;
 SztProtIE_Field_HovrCmmdIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrCmmdIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrCmmdIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrCmmdIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrCmmdIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrCmmdIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrCmmdIEs),
 &flagSz3M,
 szProtIE_Cont_HovrCmmdIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrCmmdIEsspec),
 0L
};
 CmPAsnElmDef *szHovrCmmdTkn[] =
{
 &szProtIE_Cont_HovrCmmdIEs,
  &szProtIE_Field_HovrCmmdIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrCmmdspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrCmmdTkn[0],
 0
};
 CmPAsnElmDef szHovrCmmd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrCmmd),
 &flagSz3M,
 0,
 (U8 *)(&szHovrCmmdspec),
 0L
};
 CmPAsnElmDef *sz_ValueHovrPrepFailIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCause,
 &szCriticalityDiag
};
 U32 sz_ValueHovrPrepFailIEsClsInstId[] =
{
 0,
 8,
 2,
 58
};
SzMsgConInf szHovrPrepFailIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 2, 1, 0x2 },
  { 58, 1, 0x1 }
 },
 4,
 3
};
 CmPAsnClassInfo sz_ValueHovrPrepFailIEsClsInfo =
{
 4,
 &sz_ValueHovrPrepFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrPrepFailIEsClsSpec =
{



 &sz_ValueHovrPrepFailIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrPrepFailIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrPrepFailIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrPrepFailIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrPrepFailIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrPrepFailIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrPrepFailIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrPrepFailIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrPrepFailIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrPrepFailIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrPrepFailIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrPrepFailIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrPrepFailIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrPrepFailIEs *protIe = 0L;
 SztProtIE_Field_HovrPrepFailIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrPrepFailIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrPrepFailIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrPrepFailIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrPrepFailIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrPrepFailIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrPrepFailIEs),
 &flagSz3M,
 szProtIE_Cont_HovrPrepFailIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrPrepFailIEsspec),
 0L
};
 CmPAsnElmDef *szHovrPrepFailTkn[] =
{
 &szProtIE_Cont_HovrPrepFailIEs,
  &szProtIE_Field_HovrPrepFailIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrPrepFailspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrPrepFailTkn[0],
 0
};
 CmPAsnElmDef szHovrPrepFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrPrepFail),
 &flagSz3M,
 0,
 (U8 *)(&szHovrPrepFailspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInst[] =
{
 &szData_Fwding_Not_Possible
};
 U32 sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInstId[] =
{
 143
};
 CmPAsnClassInfo sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInfo =
{
 1,
 &sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsSpec =
{



 &sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABToBeSetupItemHOReqTkn[] =
{
 &szE_RAB_ID,
 &szTportLyrAddr,
 &szGTP_TEID,
 &szE_RABLvlQoSParams,
 &szOptProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs,
  &szProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSetupItemHOReqspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABToBeSetupItemHOReqTkn[0],
 0
};
 CmPAsnElmDef szE_RABToBeSetupItemHOReq =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABToBeSetupItemHOReq),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABToBeSetupItemHOReqspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABToBeSetupItemHOReqIEsClsInst[] =
{
 &szE_RABToBeSetupItemHOReq
};
 U32 sz_ValueE_RABToBeSetupItemHOReqIEsClsInstId[] =
{
 27
};
SzMsgConInf szE_RABToBeSetupItemHOReqIEsConInf =
{
 {
  { 27, 0, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABToBeSetupItemHOReqIEsClsInfo =
{
 1,
 &sz_ValueE_RABToBeSetupItemHOReqIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSetupItemHOReqIEsClsSpec =
{



 &sz_ValueE_RABToBeSetupItemHOReqIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABToBeSetupItemHOReqIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABToBeSetupItemHOReqIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABToBeSetupItemHOReqIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABToBeSetupItemHOReqIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABToBeSetupItemHOReqIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABToBeSetupItemHOReqIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSetupItemHOReqIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABToBeSetupItemHOReqIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABToBeSetupItemHOReqIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABToBeSetupItemHOReqIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABToBeSetupItemHOReqIEsspec),
 0L
};

CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABToBeSetupItemHOReqIEsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_ContLst_E_RABToBeSetupItemHOReqIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtIE_ContLst_E_RABToBeSetupItemHOReqIEsspec),
 0L
};


 CmPAsnElmDef *sz_ValueHovrRqstIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szHovrTyp,
 &szCause,
 &szUEAggMaxBitrate,
 &szProtIE_ContLst_E_RABToBeSetupItemHOReqIEs,
  &szProtIE_Field_E_RABToBeSetupItemHOReqIEs,
  &szConstTerm,
 &szSrc_ToTget_TprntCont,
 &szUESecurCapabilities,
 &szHovrRestrnLst,
 &szTraceActvn,
 &szRqstTyp,
 &szSRVCCOperationPossible,
 &szSecurCntxt,
 &szNASSecurParamstoE_UTRAN,
 &szCSG_Id,
 &szCSGMembershipStatus,
 &szGUMMEI,
 &szMME_UE_S1AP_ID,
 &szManagementBasedMDTAllowed,
 &szMDTPLMNLst,
  &szTBCD_STRING,
  &szConstTerm,

};
 U32 sz_ValueHovrRqstIEsClsInstId[] =
{
 0,
 1,
 2,
 66,
 53,
  0xffffffff,
  0xffffffff,
 104,
 107,
 41,
 25,
 98,
 124,
 40,
 136,
 127,
 146,
 75,
 158,
 165,
 177,
  0xffffffff,
  0xffffffff
};
SzMsgConInf szHovrRqstIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 1, 0, 0x2 },
  { 2, 1, 0x2 },
  { 66, 0, 0x2 },
  { 53, 0, 0x2 },
  { 104, 0, 0x2 },
  { 107, 0, 0x2 },
  { 41, 1, 0x1 },
  { 25, 1, 0x1 },
  { 98, 1, 0x1 },
  { 124, 1, 0x1 },
  { 40, 0, 0x2 },
  { 136, 0, 0x1 },
  { 127, 0, 0x1 },
  { 146, 1, 0x1 },
  { 75, 1, 0x1 },
  { 158, 1, 0x1 },
  { 165, 1, 0x1 },
  { 177, 1, 0x1 }
 },
 19,
 8
};
 CmPAsnClassInfo sz_ValueHovrRqstIEsClsInfo =
{
 23,
 &sz_ValueHovrRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrRqstIEsClsSpec =
{



 &sz_ValueHovrRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrRqstIEs *protIe = 0L;
 SztProtIE_Field_HovrRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrRqstIEs),
 &flagSz3M,
 szProtIE_Cont_HovrRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrRqstIEsspec),
 0L
};
 CmPAsnElmDef *szHovrRqstTkn[] =
{
 &szProtIE_Cont_HovrRqstIEs,
  &szProtIE_Field_HovrRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrRqstTkn[0],
 0
};
 CmPAsnElmDef szHovrRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrRqst),
 &flagSz3M,
 0,
 (U8 *)(&szHovrRqstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABAdmtdItem_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABAdmtdItem_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABAdmtdItem_ExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABAdmtdItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABAdmtdItem_ExtIEsClsSpec =
{



 &sz_ExtnE_RABAdmtdItem_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABAdmtdItem_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABAdmtdItem_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABAdmtdItem_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABAdmtdItem_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABAdmtdItem_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABAdmtdItem_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABAdmtdItem_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABAdmtdItem_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABAdmtdItem_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABAdmtdItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABAdmtdItem_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABAdmtdItem_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABAdmtdItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABAdmtdItem_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABAdmtdItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABAdmtdItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABAdmtdItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABAdmtdItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABAdmtdItemTkn[] =
{
 &szE_RAB_ID,
 &szTportLyrAddr,
 &szGTP_TEID,
 &szOptTportLyrAddr,
 &szOptGTP_TEID,
 &szOptTportLyrAddr,
 &szOptGTP_TEID,
 &szOptProtExtnCont_E_RABAdmtdItem_ExtIEs,
  &szProtExtnField_E_RABAdmtdItem_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABAdmtdItemspec =
{



 5,
 0,
 0L,
 0L,
 &szE_RABAdmtdItemTkn[0],
 0
};
 CmPAsnElmDef szE_RABAdmtdItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABAdmtdItem),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABAdmtdItemspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABAdmtdItemIEsClsInst[] =
{
 &szE_RABAdmtdItem
};
 U32 sz_ValueE_RABAdmtdItemIEsClsInstId[] =
{
 20
};
SzMsgConInf szE_RABAdmtdItemIEsConInf =
{
 {
  { 20, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABAdmtdItemIEsClsInfo =
{
 1,
 &sz_ValueE_RABAdmtdItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABAdmtdItemIEsClsSpec =
{



 &sz_ValueE_RABAdmtdItemIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABAdmtdItemIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABAdmtdItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABAdmtdItemIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABAdmtdItemIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABAdmtdItemIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABAdmtdItemIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABAdmtdItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABAdmtdItemIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABAdmtdItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABAdmtdItemIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABAdmtdItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABAdmtdItemIEsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_ContLst_E_RABAdmtdItemIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_ContLst_E_RABAdmtdItemIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtIE_ContLst_E_RABAdmtdItemIEsspec),
 0L
};


 CmPAsnElmDef *sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsSpec =
{



 &sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABFailedToSetupItemHOReqAckTkn[] =
{
 &szE_RAB_ID,
 &szCause,
 &szOptProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs,
  &szProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABFailedToSetupItemHOReqAckspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABFailedToSetupItemHOReqAckTkn[0],
 0
};
 CmPAsnElmDef szE_RABFailedToSetupItemHOReqAck =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABFailedToSetupItemHOReqAck),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABFailedToSetupItemHOReqAckspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInst[] =
{
 &szE_RABFailedToSetupItemHOReqAck
};
 U32 sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInstId[] =
{
 21
};
SzMsgConInf szE_RABFailedtoSetupItemHOReqAckIEsConInf =
{
 {
  { 21, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInfo =
{
 1,
 &sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsSpec =
{



 &sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABFailedtoSetupItemHOReqAckIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABFailedtoSetupItemHOReqAckIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABFailedtoSetupItemHOReqAckIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEsspec),
 0L
};

CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEsspec),
 0L
};


 CmPAsnElmDef *sz_ValueHovrRqstAckgIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szProtIE_ContLst_E_RABAdmtdItemIEs,
  &szProtIE_Field_E_RABAdmtdItemIEs,
  &szConstTerm,
 &szProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs,
  &szProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs,
  &szConstTerm,
 &szTget_ToSrc_TprntCont,
 &szCSG_Id,
 &szCriticalityDiag,
 &szCellAccessMode
};
 U32 sz_ValueHovrRqstAckgIEsClsInstId[] =
{
 0,
 8,
 18,
  0xffffffff,
  0xffffffff,
 19,
  0xffffffff,
  0xffffffff,
 123,
 127,
 58,
 145
};
SzMsgConInf szHovrRqstAckgIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 18, 1, 0x2 },
  { 19, 1, 0x1 },
  { 123, 0, 0x2 },
  { 127, 1, 0x1 },
  { 58, 1, 0x1 },
  { 145, 1, 0x1 }
 },
 8,
 4
};
 CmPAsnClassInfo sz_ValueHovrRqstAckgIEsClsInfo =
{
 12,
 &sz_ValueHovrRqstAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrRqstAckgIEsClsSpec =
{



 &sz_ValueHovrRqstAckgIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrRqstAckgIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrRqstAckgIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrRqstAckgIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrRqstAckgIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrRqstAckgIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrRqstAckgIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrRqstAckgIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrRqstAckgIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrRqstAckgIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrRqstAckgIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrRqstAckgIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrRqstAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrRqstAckgIEs *protIe = 0L;
 SztProtIE_Field_HovrRqstAckgIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrRqstAckgIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrRqstAckgIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrRqstAckgIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrRqstAckgIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrRqstAckgIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrRqstAckgIEs),
 &flagSz3M,
 szProtIE_Cont_HovrRqstAckgIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrRqstAckgIEsspec),
 0L
};
 CmPAsnElmDef *szHovrRqstAckgTkn[] =
{
 &szProtIE_Cont_HovrRqstAckgIEs,
  &szProtIE_Field_HovrRqstAckgIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrRqstAckgspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrRqstAckgTkn[0],
 0
};
 CmPAsnElmDef szHovrRqstAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrRqstAckg),
 &flagSz3M,
 0,
 (U8 *)(&szHovrRqstAckgspec),
 0L
};
 CmPAsnElmDef *sz_ValueHovrFailIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szCause,
 &szCriticalityDiag
};
 U32 sz_ValueHovrFailIEsClsInstId[] =
{
 0,
 2,
 58
};
SzMsgConInf szHovrFailIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 2, 1, 0x2 },
  { 58, 1, 0x1 }
 },
 3,
 2
};
 CmPAsnClassInfo sz_ValueHovrFailIEsClsInfo =
{
 3,
 &sz_ValueHovrFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrFailIEsClsSpec =
{



 &sz_ValueHovrFailIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrFailIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrFailIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrFailIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrFailIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrFailIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrFailIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrFailIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrFailIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrFailIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrFailIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrFailIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrFailIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrFailIEs *protIe = 0L;
 SztProtIE_Field_HovrFailIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrFailIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrFailIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrFailIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrFailIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrFailIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrFailIEs),
 &flagSz3M,
 szProtIE_Cont_HovrFailIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrFailIEsspec),
 0L
};
 CmPAsnElmDef *szHovrFailTkn[] =
{
 &szProtIE_Cont_HovrFailIEs,
  &szProtIE_Field_HovrFailIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrFailspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrFailTkn[0],
 0
};
 CmPAsnElmDef szHovrFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrFail),
 &flagSz3M,
 0,
 (U8 *)(&szHovrFailspec),
 0L
};
 CmPAsnElmDef *sz_ValueHovrNtfyIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szEUTRAN_CGI,
 &szTAI,
 &szTunnelInform
};
 U32 sz_ValueHovrNtfyIEsClsInstId[] =
{
 0,
 8,
 100,
 67,
 176
};
SzMsgConInf szHovrNtfyIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 100, 1, 0x2 },
  { 67, 1, 0x2 },
  { 176, 1, 0x1 }
 },
 5,
 4
};
 CmPAsnClassInfo sz_ValueHovrNtfyIEsClsInfo =
{
 5,
 &sz_ValueHovrNtfyIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrNtfyIEsClsSpec =
{



 &sz_ValueHovrNtfyIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrNtfyIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrNtfyIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrNtfyIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrNtfyIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrNtfyIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrNtfyIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrNtfyIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrNtfyIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrNtfyIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrNtfyIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrNtfyIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrNtfyIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrNtfyIEs *protIe = 0L;
 SztProtIE_Field_HovrNtfyIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrNtfyIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrNtfyIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrNtfyIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrNtfyIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrNtfyIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrNtfyIEs),
 &flagSz3M,
 szProtIE_Cont_HovrNtfyIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrNtfyIEsspec),
 0L
};
 CmPAsnElmDef *szHovrNtfyTkn[] =
{
 &szProtIE_Cont_HovrNtfyIEs,
  &szProtIE_Field_HovrNtfyIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrNtfyspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrNtfyTkn[0],
 0
};
 CmPAsnElmDef szHovrNtfy =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrNtfy),
 &flagSz3M,
 0,
 (U8 *)(&szHovrNtfyspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsSpec =
{



 &sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABToBeSwedDLItem_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABToBeSwedDLItem_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABToBeSwedDLItem_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABToBeSwedDLItem_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSwedDLItem_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABToBeSwedDLItem_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABToBeSwedDLItem_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABToBeSwedDLItem_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSwedDLItem_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABToBeSwedDLItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSwedDLItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABToBeSwedDLItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSwedDLItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABToBeSwedDLItemTkn[] =
{
 &szE_RAB_ID,
 &szTportLyrAddr,
 &szGTP_TEID,
 &szOptProtExtnCont_E_RABToBeSwedDLItem_ExtIEs,
  &szProtExtnField_E_RABToBeSwedDLItem_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSwedDLItemspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABToBeSwedDLItemTkn[0],
 0
};
 CmPAsnElmDef szE_RABToBeSwedDLItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABToBeSwedDLItem),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABToBeSwedDLItemspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABToBeSwedDLItemIEsClsInst[] =
{
 &szE_RABToBeSwedDLItem
};
 U32 sz_ValueE_RABToBeSwedDLItemIEsClsInstId[] =
{
 23
};
SzMsgConInf szE_RABToBeSwedDLItemIEsConInf =
{
 {
  { 23, 0, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABToBeSwedDLItemIEsClsInfo =
{
 1,
 &sz_ValueE_RABToBeSwedDLItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSwedDLItemIEsClsSpec =
{



 &sz_ValueE_RABToBeSwedDLItemIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABToBeSwedDLItemIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABToBeSwedDLItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABToBeSwedDLItemIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABToBeSwedDLItemIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABToBeSwedDLItemIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABToBeSwedDLItemIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSwedDLItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABToBeSwedDLItemIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABToBeSwedDLItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABToBeSwedDLItemIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABToBeSwedDLItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABToBeSwedDLItemIEsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_ContLst_E_RABToBeSwedDLItemIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_ContLst_E_RABToBeSwedDLItemIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtIE_ContLst_E_RABToBeSwedDLItemIEsspec),
 0L
};


 CmPAsnElmDef *sz_ValuePathSwRqstIEsClsInst[] =
{
 &szENB_UE_S1AP_ID,
 &szProtIE_ContLst_E_RABToBeSwedDLItemIEs,
  &szProtIE_Field_E_RABToBeSwedDLItemIEs,
  &szConstTerm,
 &szMME_UE_S1AP_ID,
 &szEUTRAN_CGI,
 &szTAI,
 &szUESecurCapabilities,
 &szCSG_Id,
 &szCellAccessMode,
 &szGUMMEI,
 &szCSGMembershipStatus,
 &szTunnelInform
};
 U32 sz_ValuePathSwRqstIEsClsInstId[] =
{
 8,
 22,
  0xffffffff,
  0xffffffff,
 88,
 100,
 67,
 107,
 127,
 145,
 157,
 146,
 176
};
SzMsgConInf szPathSwRqstIEsConInf =
{
 {
  { 8, 0, 0x2 },
  { 22, 0, 0x2 },
  { 88, 0, 0x2 },
  { 100, 1, 0x2 },
  { 67, 1, 0x2 },
  { 107, 1, 0x2 },
  { 127, 1, 0x1 },
  { 145, 1, 0x1 },
  { 157, 1, 0x1 },
  { 146, 1, 0x1 },
  { 176, 1, 0x1 }
 },
 11,
 6
};
 CmPAsnClassInfo sz_ValuePathSwRqstIEsClsInfo =
{
 13,
 &sz_ValuePathSwRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePathSwRqstIEsClsSpec =
{



 &sz_ValuePathSwRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValuePathSwRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValuePathSwRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValuePathSwRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValuePathSwRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_PathSwRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValuePathSwRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_PathSwRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_PathSwRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_PathSwRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_PathSwRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_PathSwRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_PathSwRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_PathSwRqstIEs *protIe = 0L;
 SztProtIE_Field_PathSwRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_PathSwRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_PathSwRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szPathSwRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_PathSwRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_PathSwRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_PathSwRqstIEs),
 &flagSz3M,
 szProtIE_Cont_PathSwRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_PathSwRqstIEsspec),
 0L
};
 CmPAsnElmDef *szPathSwRqstTkn[] =
{
 &szProtIE_Cont_PathSwRqstIEs,
  &szProtIE_Field_PathSwRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szPathSwRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szPathSwRqstTkn[0],
 0
};
 CmPAsnElmDef szPathSwRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztPathSwRqst),
 &flagSz3M,
 0,
 (U8 *)(&szPathSwRqstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSwedULItem_ExtIEsClsSpec =
{



 &sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABToBeSwedULItem_ExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABToBeSwedULItem_ExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABToBeSwedULItem_ExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABToBeSwedULItem_ExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABToBeSwedULItem_ExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSwedULItem_ExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABToBeSwedULItem_ExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABToBeSwedULItem_ExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABToBeSwedULItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABToBeSwedULItem_ExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSwedULItem_ExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABToBeSwedULItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSwedULItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABToBeSwedULItem_ExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSwedULItem_ExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABToBeSwedULItemTkn[] =
{
 &szE_RAB_ID,
 &szTportLyrAddr,
 &szGTP_TEID,
 &szOptProtExtnCont_E_RABToBeSwedULItem_ExtIEs,
  &szProtExtnField_E_RABToBeSwedULItem_ExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSwedULItemspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABToBeSwedULItemTkn[0],
 0
};
 CmPAsnElmDef szE_RABToBeSwedULItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABToBeSwedULItem),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABToBeSwedULItemspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABToBeSwedULItemIEsClsInst[] =
{
 &szE_RABToBeSwedULItem
};
 U32 sz_ValueE_RABToBeSwedULItemIEsClsInstId[] =
{
 94
};
SzMsgConInf szE_RABToBeSwedULItemIEsConInf =
{
 {
  { 94, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABToBeSwedULItemIEsClsInfo =
{
 1,
 &sz_ValueE_RABToBeSwedULItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSwedULItemIEsClsSpec =
{



 &sz_ValueE_RABToBeSwedULItemIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABToBeSwedULItemIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABToBeSwedULItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABToBeSwedULItemIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABToBeSwedULItemIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABToBeSwedULItemIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABToBeSwedULItemIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSwedULItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABToBeSwedULItemIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABToBeSwedULItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABToBeSwedULItemIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABToBeSwedULItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef szProtIE_ContLst_E_RABToBeSwedULItemIEsspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_ContLst_E_RABToBeSwedULItemIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_ContLst_E_RABToBeSwedULItemIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtIE_ContLst_E_RABToBeSwedULItemIEsspec),
 0L
};


 CmPAsnElmDef *sz_ValuePathSwRqstAckgIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szUEAggMaxBitrate,
 &szProtIE_ContLst_E_RABToBeSwedULItemIEs,
  &szProtIE_Field_E_RABToBeSwedULItemIEs,
  &szConstTerm,
 &szE_RABLst,
  &szProtIE_Field_E_RABItemIEs,
  &szConstTerm,
 &szSecurCntxt,
 &szCriticalityDiag,
 &szMME_UE_S1AP_ID,
 &szCSGMembershipStatus
};
 U32 sz_ValuePathSwRqstAckgIEsClsInstId[] =
{
 0,
 8,
 66,
 95,
  0xffffffff,
  0xffffffff,
 33,
  0xffffffff,
  0xffffffff,
 40,
 58,
 158,
 146
};
SzMsgConInf szPathSwRqstAckgIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 66, 1, 0x1 },
  { 95, 1, 0x1 },
  { 33, 1, 0x1 },
  { 40, 0, 0x2 },
  { 58, 1, 0x1 },
  { 158, 1, 0x1 },
  { 146, 1, 0x1 }
 },
 9,
 3
};
 CmPAsnClassInfo sz_ValuePathSwRqstAckgIEsClsInfo =
{
 13,
 &sz_ValuePathSwRqstAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePathSwRqstAckgIEsClsSpec =
{



 &sz_ValuePathSwRqstAckgIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValuePathSwRqstAckgIEsClsInst[0],



};
 CmPAsnElmDef sz_ValuePathSwRqstAckgIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValuePathSwRqstAckgIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValuePathSwRqstAckgIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_PathSwRqstAckgIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValuePathSwRqstAckgIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_PathSwRqstAckgIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_PathSwRqstAckgIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_PathSwRqstAckgIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_PathSwRqstAckgIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_PathSwRqstAckgIEsspec),
 0L
};


 S16 szProtIE_Cont_PathSwRqstAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_PathSwRqstAckgIEs *protIe = 0L;
 SztProtIE_Field_PathSwRqstAckgIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_PathSwRqstAckgIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_PathSwRqstAckgIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szPathSwRqstAckgIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_PathSwRqstAckgIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_PathSwRqstAckgIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_PathSwRqstAckgIEs),
 &flagSz3M,
 szProtIE_Cont_PathSwRqstAckgIEsValidate,
 (U8 *) (&szProtIE_Cont_PathSwRqstAckgIEsspec),
 0L
};
 CmPAsnElmDef *szPathSwRqstAckgTkn[] =
{
 &szProtIE_Cont_PathSwRqstAckgIEs,
  &szProtIE_Field_PathSwRqstAckgIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szPathSwRqstAckgspec =
{



 0,
 0,
 0L,
 0L,
 &szPathSwRqstAckgTkn[0],
 0
};
 CmPAsnElmDef szPathSwRqstAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztPathSwRqstAckg),
 &flagSz3M,
 0,
 (U8 *)(&szPathSwRqstAckgspec),
 0L
};
 CmPAsnElmDef *sz_ValuePathSwRqstFailIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCause,
 &szCriticalityDiag
};
 U32 sz_ValuePathSwRqstFailIEsClsInstId[] =
{
 0,
 8,
 2,
 58
};
SzMsgConInf szPathSwRqstFailIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 2, 1, 0x2 },
  { 58, 1, 0x1 }
 },
 4,
 3
};
 CmPAsnClassInfo sz_ValuePathSwRqstFailIEsClsInfo =
{
 4,
 &sz_ValuePathSwRqstFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePathSwRqstFailIEsClsSpec =
{



 &sz_ValuePathSwRqstFailIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValuePathSwRqstFailIEsClsInst[0],



};
 CmPAsnElmDef sz_ValuePathSwRqstFailIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValuePathSwRqstFailIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValuePathSwRqstFailIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_PathSwRqstFailIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValuePathSwRqstFailIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_PathSwRqstFailIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_PathSwRqstFailIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_PathSwRqstFailIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_PathSwRqstFailIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_PathSwRqstFailIEsspec),
 0L
};


 S16 szProtIE_Cont_PathSwRqstFailIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_PathSwRqstFailIEs *protIe = 0L;
 SztProtIE_Field_PathSwRqstFailIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_PathSwRqstFailIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_PathSwRqstFailIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szPathSwRqstFailIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_PathSwRqstFailIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_PathSwRqstFailIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_PathSwRqstFailIEs),
 &flagSz3M,
 szProtIE_Cont_PathSwRqstFailIEsValidate,
 (U8 *) (&szProtIE_Cont_PathSwRqstFailIEsspec),
 0L
};
 CmPAsnElmDef *szPathSwRqstFailTkn[] =
{
 &szProtIE_Cont_PathSwRqstFailIEs,
  &szProtIE_Field_PathSwRqstFailIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szPathSwRqstFailspec =
{



 0,
 0,
 0L,
 0L,
 &szPathSwRqstFailTkn[0],
 0
};
 CmPAsnElmDef szPathSwRqstFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztPathSwRqstFail),
 &flagSz3M,
 0,
 (U8 *)(&szPathSwRqstFailspec),
 0L
};
 CmPAsnElmDef *sz_ValueHovrCancelIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCause
};
 U32 sz_ValueHovrCancelIEsClsInstId[] =
{
 0,
 8,
 2
};
SzMsgConInf szHovrCancelIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 2, 1, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueHovrCancelIEsClsInfo =
{
 3,
 &sz_ValueHovrCancelIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrCancelIEsClsSpec =
{



 &sz_ValueHovrCancelIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrCancelIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrCancelIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrCancelIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrCancelIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrCancelIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrCancelIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrCancelIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrCancelIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrCancelIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrCancelIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrCancelIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrCancelIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrCancelIEs *protIe = 0L;
 SztProtIE_Field_HovrCancelIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrCancelIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrCancelIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrCancelIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrCancelIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrCancelIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrCancelIEs),
 &flagSz3M,
 szProtIE_Cont_HovrCancelIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrCancelIEsspec),
 0L
};
 CmPAsnElmDef *szHovrCancelTkn[] =
{
 &szProtIE_Cont_HovrCancelIEs,
  &szProtIE_Field_HovrCancelIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrCancelspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrCancelTkn[0],
 0
};
 CmPAsnElmDef szHovrCancel =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrCancel),
 &flagSz3M,
 0,
 (U8 *)(&szHovrCancelspec),
 0L
};
 CmPAsnElmDef *sz_ValueHovrCancelAckgIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCriticalityDiag
};
 U32 sz_ValueHovrCancelAckgIEsClsInstId[] =
{
 0,
 8,
 58
};
SzMsgConInf szHovrCancelAckgIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 58, 1, 0x1 }
 },
 3,
 2
};
 CmPAsnClassInfo sz_ValueHovrCancelAckgIEsClsInfo =
{
 3,
 &sz_ValueHovrCancelAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueHovrCancelAckgIEsClsSpec =
{



 &sz_ValueHovrCancelAckgIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueHovrCancelAckgIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueHovrCancelAckgIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueHovrCancelAckgIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueHovrCancelAckgIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_HovrCancelAckgIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueHovrCancelAckgIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_HovrCancelAckgIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_HovrCancelAckgIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_HovrCancelAckgIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_HovrCancelAckgIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_HovrCancelAckgIEsspec),
 0L
};


 S16 szProtIE_Cont_HovrCancelAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_HovrCancelAckgIEs *protIe = 0L;
 SztProtIE_Field_HovrCancelAckgIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_HovrCancelAckgIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_HovrCancelAckgIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szHovrCancelAckgIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_HovrCancelAckgIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_HovrCancelAckgIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_HovrCancelAckgIEs),
 &flagSz3M,
 szProtIE_Cont_HovrCancelAckgIEsValidate,
 (U8 *) (&szProtIE_Cont_HovrCancelAckgIEsspec),
 0L
};
 CmPAsnElmDef *szHovrCancelAckgTkn[] =
{
 &szProtIE_Cont_HovrCancelAckgIEs,
  &szProtIE_Field_HovrCancelAckgIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szHovrCancelAckgspec =
{



 0,
 0,
 0L,
 0L,
 &szHovrCancelAckgTkn[0],
 0
};
 CmPAsnElmDef szHovrCancelAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztHovrCancelAckg),
 &flagSz3M,
 0,
 (U8 *)(&szHovrCancelAckgspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInst[] =
{
 &szCorrelation_ID
};
 U32 sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInstId[] =
{
 156
};
 CmPAsnClassInfo sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInfo =
{
 1,
 &sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsSpec =
{



 &sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABToBeSetupItemBrSUReqTkn[] =
{
 &szE_RAB_ID,
 &szE_RABLvlQoSParams,
 &szTportLyrAddr,
 &szGTP_TEID,
 &szNAS_PDU,
 &szOptProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs,
  &szProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSetupItemBrSUReqspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABToBeSetupItemBrSUReqTkn[0],
 0
};
 CmPAsnElmDef szE_RABToBeSetupItemBrSUReq =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABToBeSetupItemBrSUReq),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABToBeSetupItemBrSUReqspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInst[] =
{
 &szE_RABToBeSetupItemBrSUReq
};
 U32 sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInstId[] =
{
 17
};
SzMsgConInf szE_RABToBeSetupItemBrSUReqIEsConInf =
{
 {
  { 17, 0, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInfo =
{
 1,
 &sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSetupItemBrSUReqIEsClsSpec =
{



 &sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABToBeSetupItemBrSUReqIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABToBeSetupItemBrSUReqIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABToBeSetupItemBrSUReqIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABToBeSetupItemBrSUReqIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABToBeSetupItemBrSUReqIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSetupItemBrSUReqIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABToBeSetupItemBrSUReqIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABToBeSetupItemBrSUReqIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABToBeSetupItemBrSUReqIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABToBeSetupLstBrSUReqspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szE_RABToBeSetupLstBrSUReq =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABToBeSetupLstBrSUReq),
 &flagSz3M,
 0,
 (U8 *) (&szE_RABToBeSetupLstBrSUReqspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABSetupRqstIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szUEAggMaxBitrate,
 &szE_RABToBeSetupLstBrSUReq,
  &szProtIE_Field_E_RABToBeSetupItemBrSUReqIEs,
  &szConstTerm,

};
 U32 sz_ValueE_RABSetupRqstIEsClsInstId[] =
{
 0,
 8,
 66,
 16,
  0xffffffff,
  0xffffffff
};
SzMsgConInf szE_RABSetupRqstIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 66, 0, 0x1 },
  { 16, 0, 0x2 }
 },
 4,
 3
};
 CmPAsnClassInfo sz_ValueE_RABSetupRqstIEsClsInfo =
{
 6,
 &sz_ValueE_RABSetupRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABSetupRqstIEsClsSpec =
{



 &sz_ValueE_RABSetupRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABSetupRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABSetupRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABSetupRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABSetupRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABSetupRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABSetupRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABSetupRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABSetupRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABSetupRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABSetupRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABSetupRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_E_RABSetupRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_E_RABSetupRqstIEs *protIe = 0L;
 SztProtIE_Field_E_RABSetupRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_E_RABSetupRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_E_RABSetupRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szE_RABSetupRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABSetupRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_E_RABSetupRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_E_RABSetupRqstIEs),
 &flagSz3M,
 szProtIE_Cont_E_RABSetupRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_E_RABSetupRqstIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABSetupRqstTkn[] =
{
 &szProtIE_Cont_E_RABSetupRqstIEs,
  &szProtIE_Field_E_RABSetupRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABSetupRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szE_RABSetupRqstTkn[0],
 0
};
 CmPAsnElmDef szE_RABSetupRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABSetupRqst),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABSetupRqstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABSetupItemBrSUResExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABSetupItemBrSUResExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABSetupItemBrSUResExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABSetupItemBrSUResExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABSetupItemBrSUResExtIEsClsSpec =
{



 &sz_ExtnE_RABSetupItemBrSUResExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABSetupItemBrSUResExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABSetupItemBrSUResExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABSetupItemBrSUResExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABSetupItemBrSUResExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABSetupItemBrSUResExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABSetupItemBrSUResExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABSetupItemBrSUResExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABSetupItemBrSUResExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABSetupItemBrSUResExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABSetupItemBrSUResExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABSetupItemBrSUResExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABSetupItemBrSUResExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABSetupItemBrSUResExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABSetupItemBrSUResExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABSetupItemBrSUResExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABSetupItemBrSUResExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABSetupItemBrSUResExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABSetupItemBrSUResExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABSetupItemBrSUResTkn[] =
{
 &szE_RAB_ID,
 &szTportLyrAddr,
 &szGTP_TEID,
 &szOptProtExtnCont_E_RABSetupItemBrSUResExtIEs,
  &szProtExtnField_E_RABSetupItemBrSUResExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABSetupItemBrSUResspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABSetupItemBrSUResTkn[0],
 0
};
 CmPAsnElmDef szE_RABSetupItemBrSURes =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABSetupItemBrSURes),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABSetupItemBrSUResspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABSetupItemBrSUResIEsClsInst[] =
{
 &szE_RABSetupItemBrSURes
};
 U32 sz_ValueE_RABSetupItemBrSUResIEsClsInstId[] =
{
 39
};
SzMsgConInf szE_RABSetupItemBrSUResIEsConInf =
{
 {
  { 39, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABSetupItemBrSUResIEsClsInfo =
{
 1,
 &sz_ValueE_RABSetupItemBrSUResIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABSetupItemBrSUResIEsClsSpec =
{



 &sz_ValueE_RABSetupItemBrSUResIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABSetupItemBrSUResIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABSetupItemBrSUResIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABSetupItemBrSUResIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABSetupItemBrSUResIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABSetupItemBrSUResIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABSetupItemBrSUResIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABSetupItemBrSUResIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABSetupItemBrSUResIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABSetupItemBrSUResIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABSetupItemBrSUResIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABSetupItemBrSUResIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABSetupLstBrSUResspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szE_RABSetupLstBrSURes =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABSetupLstBrSURes),
 &flagSz3M,
 0,
 (U8 *) (&szE_RABSetupLstBrSUResspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABSetupRespIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szE_RABSetupLstBrSURes,
  &szProtIE_Field_E_RABSetupItemBrSUResIEs,
  &szConstTerm,
 &szE_RABLst,
  &szProtIE_Field_E_RABItemIEs,
  &szConstTerm,
 &szCriticalityDiag
};
 U32 sz_ValueE_RABSetupRespIEsClsInstId[] =
{
 0,
 8,
 28,
  0xffffffff,
  0xffffffff,
 29,
  0xffffffff,
  0xffffffff,
 58
};
SzMsgConInf szE_RABSetupRespIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 28, 1, 0x1 },
  { 29, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 5,
 2
};
 CmPAsnClassInfo sz_ValueE_RABSetupRespIEsClsInfo =
{
 9,
 &sz_ValueE_RABSetupRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABSetupRespIEsClsSpec =
{



 &sz_ValueE_RABSetupRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABSetupRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABSetupRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABSetupRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABSetupRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABSetupRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABSetupRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABSetupRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABSetupRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABSetupRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABSetupRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABSetupRespIEsspec),
 0L
};


 S16 szProtIE_Cont_E_RABSetupRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_E_RABSetupRespIEs *protIe = 0L;
 SztProtIE_Field_E_RABSetupRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_E_RABSetupRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_E_RABSetupRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szE_RABSetupRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABSetupRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_E_RABSetupRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_E_RABSetupRespIEs),
 &flagSz3M,
 szProtIE_Cont_E_RABSetupRespIEsValidate,
 (U8 *) (&szProtIE_Cont_E_RABSetupRespIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABSetupRespTkn[] =
{
 &szProtIE_Cont_E_RABSetupRespIEs,
  &szProtIE_Field_E_RABSetupRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABSetupRespspec =
{



 0,
 0,
 0L,
 0L,
 &szE_RABSetupRespTkn[0],
 0
};
 CmPAsnElmDef szE_RABSetupResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABSetupResp),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABSetupRespspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsSpec =
{



 &sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABToBeMdfdItemBrModReqTkn[] =
{
 &szE_RAB_ID,
 &szE_RABLvlQoSParams,
 &szNAS_PDU,
 &szOptProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs,
  &szProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeMdfdItemBrModReqspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABToBeMdfdItemBrModReqTkn[0],
 0
};
 CmPAsnElmDef szE_RABToBeMdfdItemBrModReq =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABToBeMdfdItemBrModReq),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABToBeMdfdItemBrModReqspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInst[] =
{
 &szE_RABToBeMdfdItemBrModReq
};
 U32 sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInstId[] =
{
 36
};
SzMsgConInf szE_RABToBeMdfdItemBrModReqIEsConInf =
{
 {
  { 36, 0, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInfo =
{
 1,
 &sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeMdfdItemBrModReqIEsClsSpec =
{



 &sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABToBeMdfdItemBrModReqIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABToBeMdfdItemBrModReqIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABToBeMdfdItemBrModReqIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABToBeMdfdItemBrModReqIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABToBeMdfdItemBrModReqIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeMdfdItemBrModReqIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABToBeMdfdItemBrModReqIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABToBeMdfdItemBrModReqIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABToBeMdfdItemBrModReqIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABToBeMdfdLstBrModReqspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szE_RABToBeMdfdLstBrModReq =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABToBeMdfdLstBrModReq),
 &flagSz3M,
 0,
 (U8 *) (&szE_RABToBeMdfdLstBrModReqspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABMdfyRqstIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szUEAggMaxBitrate,
 &szE_RABToBeMdfdLstBrModReq,
  &szProtIE_Field_E_RABToBeMdfdItemBrModReqIEs,
  &szConstTerm,

};
 U32 sz_ValueE_RABMdfyRqstIEsClsInstId[] =
{
 0,
 8,
 66,
 30,
  0xffffffff,
  0xffffffff
};
SzMsgConInf szE_RABMdfyRqstIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 66, 0, 0x1 },
  { 30, 0, 0x2 }
 },
 4,
 3
};
 CmPAsnClassInfo sz_ValueE_RABMdfyRqstIEsClsInfo =
{
 6,
 &sz_ValueE_RABMdfyRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABMdfyRqstIEsClsSpec =
{



 &sz_ValueE_RABMdfyRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABMdfyRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABMdfyRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABMdfyRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABMdfyRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABMdfyRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABMdfyRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABMdfyRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABMdfyRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABMdfyRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABMdfyRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABMdfyRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_E_RABMdfyRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_E_RABMdfyRqstIEs *protIe = 0L;
 SztProtIE_Field_E_RABMdfyRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_E_RABMdfyRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_E_RABMdfyRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szE_RABMdfyRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABMdfyRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_E_RABMdfyRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_E_RABMdfyRqstIEs),
 &flagSz3M,
 szProtIE_Cont_E_RABMdfyRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_E_RABMdfyRqstIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABMdfyRqstTkn[] =
{
 &szProtIE_Cont_E_RABMdfyRqstIEs,
  &szProtIE_Field_E_RABMdfyRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABMdfyRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szE_RABMdfyRqstTkn[0],
 0
};
 CmPAsnElmDef szE_RABMdfyRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABMdfyRqst),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABMdfyRqstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABMdfyItemBrModResExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABMdfyItemBrModResExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABMdfyItemBrModResExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABMdfyItemBrModResExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABMdfyItemBrModResExtIEsClsSpec =
{



 &sz_ExtnE_RABMdfyItemBrModResExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABMdfyItemBrModResExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABMdfyItemBrModResExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABMdfyItemBrModResExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABMdfyItemBrModResExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABMdfyItemBrModResExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABMdfyItemBrModResExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABMdfyItemBrModResExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABMdfyItemBrModResExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABMdfyItemBrModResExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABMdfyItemBrModResExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABMdfyItemBrModResExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABMdfyItemBrModResExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABMdfyItemBrModResExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABMdfyItemBrModResExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABMdfyItemBrModResExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABMdfyItemBrModResExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABMdfyItemBrModResExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABMdfyItemBrModResExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABMdfyItemBrModResTkn[] =
{
 &szE_RAB_ID,
 &szOptProtExtnCont_E_RABMdfyItemBrModResExtIEs,
  &szProtExtnField_E_RABMdfyItemBrModResExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABMdfyItemBrModResspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABMdfyItemBrModResTkn[0],
 0
};
 CmPAsnElmDef szE_RABMdfyItemBrModRes =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABMdfyItemBrModRes),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABMdfyItemBrModResspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABMdfyItemBrModResIEsClsInst[] =
{
 &szE_RABMdfyItemBrModRes
};
 U32 sz_ValueE_RABMdfyItemBrModResIEsClsInstId[] =
{
 37
};
SzMsgConInf szE_RABMdfyItemBrModResIEsConInf =
{
 {
  { 37, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABMdfyItemBrModResIEsClsInfo =
{
 1,
 &sz_ValueE_RABMdfyItemBrModResIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABMdfyItemBrModResIEsClsSpec =
{



 &sz_ValueE_RABMdfyItemBrModResIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABMdfyItemBrModResIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABMdfyItemBrModResIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABMdfyItemBrModResIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABMdfyItemBrModResIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABMdfyItemBrModResIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABMdfyItemBrModResIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABMdfyItemBrModResIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABMdfyItemBrModResIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABMdfyItemBrModResIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABMdfyItemBrModResIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABMdfyItemBrModResIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABMdfyLstBrModResspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szE_RABMdfyLstBrModRes =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABMdfyLstBrModRes),
 &flagSz3M,
 0,
 (U8 *) (&szE_RABMdfyLstBrModResspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABMdfyRespIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szE_RABMdfyLstBrModRes,
  &szProtIE_Field_E_RABMdfyItemBrModResIEs,
  &szConstTerm,
 &szE_RABLst,
  &szProtIE_Field_E_RABItemIEs,
  &szConstTerm,
 &szCriticalityDiag
};
 U32 sz_ValueE_RABMdfyRespIEsClsInstId[] =
{
 0,
 8,
 31,
  0xffffffff,
  0xffffffff,
 32,
  0xffffffff,
  0xffffffff,
 58
};
SzMsgConInf szE_RABMdfyRespIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 31, 1, 0x1 },
  { 32, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 5,
 2
};
 CmPAsnClassInfo sz_ValueE_RABMdfyRespIEsClsInfo =
{
 9,
 &sz_ValueE_RABMdfyRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABMdfyRespIEsClsSpec =
{



 &sz_ValueE_RABMdfyRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABMdfyRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABMdfyRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABMdfyRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABMdfyRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABMdfyRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABMdfyRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABMdfyRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABMdfyRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABMdfyRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABMdfyRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABMdfyRespIEsspec),
 0L
};


 S16 szProtIE_Cont_E_RABMdfyRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_E_RABMdfyRespIEs *protIe = 0L;
 SztProtIE_Field_E_RABMdfyRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_E_RABMdfyRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_E_RABMdfyRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szE_RABMdfyRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABMdfyRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_E_RABMdfyRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_E_RABMdfyRespIEs),
 &flagSz3M,
 szProtIE_Cont_E_RABMdfyRespIEsValidate,
 (U8 *) (&szProtIE_Cont_E_RABMdfyRespIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABMdfyRespTkn[] =
{
 &szProtIE_Cont_E_RABMdfyRespIEs,
  &szProtIE_Field_E_RABMdfyRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABMdfyRespspec =
{



 0,
 0,
 0L,
 0L,
 &szE_RABMdfyRespTkn[0],
 0
};
 CmPAsnElmDef szE_RABMdfyResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABMdfyResp),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABMdfyRespspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABRlsCmmdIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szUEAggMaxBitrate,
 &szE_RABLst,
  &szProtIE_Field_E_RABItemIEs,
  &szConstTerm,
 &szNAS_PDU
};
 U32 sz_ValueE_RABRlsCmmdIEsClsInstId[] =
{
 0,
 8,
 66,
 33,
  0xffffffff,
  0xffffffff,
 26
};
SzMsgConInf szE_RABRlsCmmdIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 66, 0, 0x1 },
  { 33, 1, 0x2 },
  { 26, 1, 0x1 }
 },
 5,
 3
};
 CmPAsnClassInfo sz_ValueE_RABRlsCmmdIEsClsInfo =
{
 7,
 &sz_ValueE_RABRlsCmmdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABRlsCmmdIEsClsSpec =
{



 &sz_ValueE_RABRlsCmmdIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABRlsCmmdIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABRlsCmmdIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABRlsCmmdIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABRlsCmmdIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABRlsCmmdIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABRlsCmmdIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABRlsCmmdIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABRlsCmmdIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABRlsCmmdIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABRlsCmmdIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABRlsCmmdIEsspec),
 0L
};


 S16 szProtIE_Cont_E_RABRlsCmmdIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_E_RABRlsCmmdIEs *protIe = 0L;
 SztProtIE_Field_E_RABRlsCmmdIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_E_RABRlsCmmdIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_E_RABRlsCmmdIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szE_RABRlsCmmdIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABRlsCmmdIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_E_RABRlsCmmdIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_E_RABRlsCmmdIEs),
 &flagSz3M,
 szProtIE_Cont_E_RABRlsCmmdIEsValidate,
 (U8 *) (&szProtIE_Cont_E_RABRlsCmmdIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABRlsCmmdTkn[] =
{
 &szProtIE_Cont_E_RABRlsCmmdIEs,
  &szProtIE_Field_E_RABRlsCmmdIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABRlsCmmdspec =
{



 0,
 0,
 0L,
 0L,
 &szE_RABRlsCmmdTkn[0],
 0
};
 CmPAsnElmDef szE_RABRlsCmmd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABRlsCmmd),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABRlsCmmdspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABRlsItemBrRelCompExtIEsClsSpec =
{



 &sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABRlsItemBrRelCompExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABRlsItemBrRelCompExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABRlsItemBrRelCompExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABRlsItemBrRelCompExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABRlsItemBrRelCompExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABRlsItemBrRelCompExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABRlsItemBrRelCompExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABRlsItemBrRelCompExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABRlsItemBrRelCompExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABRlsItemBrRelCompExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABRlsItemBrRelCompExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABRlsItemBrRelCompExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABRlsItemBrRelCompExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABRlsItemBrRelCompExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABRlsItemBrRelCompExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABRlsItemBrRelCompTkn[] =
{
 &szE_RAB_ID,
 &szOptProtExtnCont_E_RABRlsItemBrRelCompExtIEs,
  &szProtExtnField_E_RABRlsItemBrRelCompExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABRlsItemBrRelCompspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABRlsItemBrRelCompTkn[0],
 0
};
 CmPAsnElmDef szE_RABRlsItemBrRelComp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABRlsItemBrRelComp),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABRlsItemBrRelCompspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABRlsItemBrRelCompIEsClsInst[] =
{
 &szE_RABRlsItemBrRelComp
};
 U32 sz_ValueE_RABRlsItemBrRelCompIEsClsInstId[] =
{
 15
};
SzMsgConInf szE_RABRlsItemBrRelCompIEsConInf =
{
 {
  { 15, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABRlsItemBrRelCompIEsClsInfo =
{
 1,
 &sz_ValueE_RABRlsItemBrRelCompIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABRlsItemBrRelCompIEsClsSpec =
{



 &sz_ValueE_RABRlsItemBrRelCompIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABRlsItemBrRelCompIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABRlsItemBrRelCompIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABRlsItemBrRelCompIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABRlsItemBrRelCompIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABRlsItemBrRelCompIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABRlsItemBrRelCompIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABRlsItemBrRelCompIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABRlsItemBrRelCompIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABRlsItemBrRelCompIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABRlsItemBrRelCompIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABRlsItemBrRelCompIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABRlsLstBrRelCompspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szE_RABRlsLstBrRelComp =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABRlsLstBrRelComp),
 &flagSz3M,
 0,
 (U8 *) (&szE_RABRlsLstBrRelCompspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABRlsRespIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szE_RABRlsLstBrRelComp,
  &szProtIE_Field_E_RABRlsItemBrRelCompIEs,
  &szConstTerm,
 &szE_RABLst,
  &szProtIE_Field_E_RABItemIEs,
  &szConstTerm,
 &szCriticalityDiag
};
 U32 sz_ValueE_RABRlsRespIEsClsInstId[] =
{
 0,
 8,
 69,
  0xffffffff,
  0xffffffff,
 34,
  0xffffffff,
  0xffffffff,
 58
};
SzMsgConInf szE_RABRlsRespIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 69, 1, 0x1 },
  { 34, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 5,
 2
};
 CmPAsnClassInfo sz_ValueE_RABRlsRespIEsClsInfo =
{
 9,
 &sz_ValueE_RABRlsRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABRlsRespIEsClsSpec =
{



 &sz_ValueE_RABRlsRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABRlsRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABRlsRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABRlsRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABRlsRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABRlsRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABRlsRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABRlsRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABRlsRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABRlsRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABRlsRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABRlsRespIEsspec),
 0L
};


 S16 szProtIE_Cont_E_RABRlsRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_E_RABRlsRespIEs *protIe = 0L;
 SztProtIE_Field_E_RABRlsRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_E_RABRlsRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_E_RABRlsRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szE_RABRlsRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABRlsRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_E_RABRlsRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_E_RABRlsRespIEs),
 &flagSz3M,
 szProtIE_Cont_E_RABRlsRespIEsValidate,
 (U8 *) (&szProtIE_Cont_E_RABRlsRespIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABRlsRespTkn[] =
{
 &szProtIE_Cont_E_RABRlsRespIEs,
  &szProtIE_Field_E_RABRlsRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABRlsRespspec =
{



 0,
 0,
 0L,
 0L,
 &szE_RABRlsRespTkn[0],
 0
};
 CmPAsnElmDef szE_RABRlsResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABRlsResp),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABRlsRespspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABRlsIndIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szE_RABLst,
  &szProtIE_Field_E_RABItemIEs,
  &szConstTerm,

};
 U32 sz_ValueE_RABRlsIndIEsClsInstId[] =
{
 0,
 8,
 110,
  0xffffffff,
  0xffffffff
};
SzMsgConInf szE_RABRlsIndIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 110, 1, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueE_RABRlsIndIEsClsInfo =
{
 5,
 &sz_ValueE_RABRlsIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABRlsIndIEsClsSpec =
{



 &sz_ValueE_RABRlsIndIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABRlsIndIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABRlsIndIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABRlsIndIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABRlsIndIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABRlsIndIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABRlsIndIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABRlsIndIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABRlsIndIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABRlsIndIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABRlsIndIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABRlsIndIEsspec),
 0L
};


 S16 szProtIE_Cont_E_RABRlsIndIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_E_RABRlsIndIEs *protIe = 0L;
 SztProtIE_Field_E_RABRlsIndIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_E_RABRlsIndIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_E_RABRlsIndIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szE_RABRlsIndIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_E_RABRlsIndIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_E_RABRlsIndIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_E_RABRlsIndIEs),
 &flagSz3M,
 szProtIE_Cont_E_RABRlsIndIEsValidate,
 (U8 *) (&szProtIE_Cont_E_RABRlsIndIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABRlsIndTkn[] =
{
 &szProtIE_Cont_E_RABRlsIndIEs,
  &szProtIE_Field_E_RABRlsIndIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABRlsIndspec =
{



 0,
 0,
 0L,
 0L,
 &szE_RABRlsIndTkn[0],
 0
};
 CmPAsnElmDef szE_RABRlsInd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABRlsInd),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABRlsIndspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInst[] =
{
 &szCorrelation_ID
};
 U32 sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInstId[] =
{
 156
};
 CmPAsnClassInfo sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInfo =
{
 1,
 &sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsSpec =
{



 &sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABToBeSetupItemCtxtSUReqTkn[] =
{
 &szE_RAB_ID,
 &szE_RABLvlQoSParams,
 &szTportLyrAddr,
 &szGTP_TEID,
 &szOptNAS_PDU,
 &szOptProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs,
  &szProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABToBeSetupItemCtxtSUReqspec =
{



 2,
 0,
 0L,
 0L,
 &szE_RABToBeSetupItemCtxtSUReqTkn[0],
 0
};
 CmPAsnElmDef szE_RABToBeSetupItemCtxtSUReq =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABToBeSetupItemCtxtSUReq),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABToBeSetupItemCtxtSUReqspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInst[] =
{
 &szE_RABToBeSetupItemCtxtSUReq
};
 U32 sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInstId[] =
{
 52
};
SzMsgConInf szE_RABToBeSetupItemCtxtSUReqIEsConInf =
{
 {
  { 52, 0, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInfo =
{
 1,
 &sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsSpec =
{



 &sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABToBeSetupItemCtxtSUReqIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABToBeSetupItemCtxtSUReqIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABToBeSetupItemCtxtSUReqIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABToBeSetupLstCtxtSUReqspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szE_RABToBeSetupLstCtxtSUReq =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABToBeSetupLstCtxtSUReq),
 &flagSz3M,
 0,
 (U8 *) (&szE_RABToBeSetupLstCtxtSUReqspec),
 0L
};
 CmPAsnElmDef *sz_ValueInitCntxtSetupRqstIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szUEAggMaxBitrate,
 &szE_RABToBeSetupLstCtxtSUReq,
  &szProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs,
  &szConstTerm,
 &szUESecurCapabilities,
 &szSecurKey,
 &szTraceActvn,
 &szHovrRestrnLst,
 &szUERadioCapblty,
 &szSubscriberProfileIDforRFP,
 &szCSFallbackIndicator,
 &szSRVCCOperationPossible,
 &szCSGMembershipStatus,
 &szLAI,
 &szGUMMEI,
 &szMME_UE_S1AP_ID,
 &szManagementBasedMDTAllowed,
 &szMDTPLMNLst,
  &szTBCD_STRING,
  &szConstTerm,

};
 U32 sz_ValueInitCntxtSetupRqstIEsClsInstId[] =
{
 0,
 8,
 66,
 24,
  0xffffffff,
  0xffffffff,
 107,
 73,
 25,
 41,
 74,
 106,
 108,
 124,
 146,
 159,
 75,
 158,
 165,
 177,
  0xffffffff,
  0xffffffff
};
SzMsgConInf szInitCntxtSetupRqstIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 66, 0, 0x2 },
  { 24, 0, 0x2 },
  { 107, 0, 0x2 },
  { 73, 0, 0x2 },
  { 25, 1, 0x1 },
  { 41, 1, 0x1 },
  { 74, 1, 0x1 },
  { 106, 1, 0x1 },
  { 108, 0, 0x1 },
  { 124, 1, 0x1 },
  { 146, 1, 0x1 },
  { 159, 1, 0x1 },
  { 75, 1, 0x1 },
  { 158, 1, 0x1 },
  { 165, 1, 0x1 },
  { 177, 1, 0x1 }
 },
 18,
 6
};
 CmPAsnClassInfo sz_ValueInitCntxtSetupRqstIEsClsInfo =
{
 22,
 &sz_ValueInitCntxtSetupRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueInitCntxtSetupRqstIEsClsSpec =
{



 &sz_ValueInitCntxtSetupRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueInitCntxtSetupRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueInitCntxtSetupRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueInitCntxtSetupRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueInitCntxtSetupRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_InitCntxtSetupRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueInitCntxtSetupRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_InitCntxtSetupRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_InitCntxtSetupRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_InitCntxtSetupRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_InitCntxtSetupRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_InitCntxtSetupRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_InitCntxtSetupRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_InitCntxtSetupRqstIEs *protIe = 0L;
 SztProtIE_Field_InitCntxtSetupRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_InitCntxtSetupRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_InitCntxtSetupRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szInitCntxtSetupRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_InitCntxtSetupRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_InitCntxtSetupRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_InitCntxtSetupRqstIEs),
 &flagSz3M,
 szProtIE_Cont_InitCntxtSetupRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_InitCntxtSetupRqstIEsspec),
 0L
};
 CmPAsnElmDef *szInitCntxtSetupRqstTkn[] =
{
 &szProtIE_Cont_InitCntxtSetupRqstIEs,
  &szProtIE_Field_InitCntxtSetupRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szInitCntxtSetupRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szInitCntxtSetupRqstTkn[0],
 0
};
 CmPAsnElmDef szInitCntxtSetupRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztInitCntxtSetupRqst),
 &flagSz3M,
 0,
 (U8 *)(&szInitCntxtSetupRqstspec),
 0L
};
 CmPAsnElmDef *sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInfo =
{
 0,
 &sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsSpec =
{



 &sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnE_RABSetupItemCtxtSUResExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnE_RABSetupItemCtxtSUResExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_E_RABSetupItemCtxtSUResExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnE_RABSetupItemCtxtSUResExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_E_RABSetupItemCtxtSUResExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_E_RABSetupItemCtxtSUResExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_E_RABSetupItemCtxtSUResExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_E_RABSetupItemCtxtSUResExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_E_RABSetupItemCtxtSUResExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_E_RABSetupItemCtxtSUResExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_E_RABSetupItemCtxtSUResExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_E_RABSetupItemCtxtSUResExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_E_RABSetupItemCtxtSUResExtIEsspec),
 0L
};
 CmPAsnElmDef *szE_RABSetupItemCtxtSUResTkn[] =
{
 &szE_RAB_ID,
 &szTportLyrAddr,
 &szGTP_TEID,
 &szOptProtExtnCont_E_RABSetupItemCtxtSUResExtIEs,
  &szProtExtnField_E_RABSetupItemCtxtSUResExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szE_RABSetupItemCtxtSUResspec =
{



 1,
 0,
 0L,
 0L,
 &szE_RABSetupItemCtxtSUResTkn[0],
 0
};
 CmPAsnElmDef szE_RABSetupItemCtxtSURes =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztE_RABSetupItemCtxtSURes),
 &flagSz3M,
 0,
 (U8 *)(&szE_RABSetupItemCtxtSUResspec),
 0L
};
 CmPAsnElmDef *sz_ValueE_RABSetupItemCtxtSUResIEsClsInst[] =
{
 &szE_RABSetupItemCtxtSURes
};
 U32 sz_ValueE_RABSetupItemCtxtSUResIEsClsInstId[] =
{
 50
};
SzMsgConInf szE_RABSetupItemCtxtSUResIEsConInf =
{
 {
  { 50, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueE_RABSetupItemCtxtSUResIEsClsInfo =
{
 1,
 &sz_ValueE_RABSetupItemCtxtSUResIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueE_RABSetupItemCtxtSUResIEsClsSpec =
{



 &sz_ValueE_RABSetupItemCtxtSUResIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueE_RABSetupItemCtxtSUResIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueE_RABSetupItemCtxtSUResIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueE_RABSetupItemCtxtSUResIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueE_RABSetupItemCtxtSUResIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_E_RABSetupItemCtxtSUResIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueE_RABSetupItemCtxtSUResIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_E_RABSetupItemCtxtSUResIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_E_RABSetupItemCtxtSUResIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_E_RABSetupItemCtxtSUResIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_E_RABSetupItemCtxtSUResIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_E_RABSetupItemCtxtSUResIEsspec),
 0L
};

CmPAsnSetSeqOfDef szE_RABSetupLstCtxtSUResspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szE_RABSetupLstCtxtSURes =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztE_RABSetupLstCtxtSURes),
 &flagSz3M,
 0,
 (U8 *) (&szE_RABSetupLstCtxtSUResspec),
 0L
};
 CmPAsnElmDef *sz_ValueInitCntxtSetupRespIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szE_RABSetupLstCtxtSURes,
  &szProtIE_Field_E_RABSetupItemCtxtSUResIEs,
  &szConstTerm,
 &szE_RABLst,
  &szProtIE_Field_E_RABItemIEs,
  &szConstTerm,
 &szCriticalityDiag
};
 U32 sz_ValueInitCntxtSetupRespIEsClsInstId[] =
{
 0,
 8,
 51,
  0xffffffff,
  0xffffffff,
 48,
  0xffffffff,
  0xffffffff,
 58
};
SzMsgConInf szInitCntxtSetupRespIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 51, 1, 0x2 },
  { 48, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 5,
 3
};
 CmPAsnClassInfo sz_ValueInitCntxtSetupRespIEsClsInfo =
{
 9,
 &sz_ValueInitCntxtSetupRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueInitCntxtSetupRespIEsClsSpec =
{



 &sz_ValueInitCntxtSetupRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueInitCntxtSetupRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueInitCntxtSetupRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueInitCntxtSetupRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueInitCntxtSetupRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_InitCntxtSetupRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueInitCntxtSetupRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_InitCntxtSetupRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_InitCntxtSetupRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_InitCntxtSetupRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_InitCntxtSetupRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_InitCntxtSetupRespIEsspec),
 0L
};


 S16 szProtIE_Cont_InitCntxtSetupRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_InitCntxtSetupRespIEs *protIe = 0L;
 SztProtIE_Field_InitCntxtSetupRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_InitCntxtSetupRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_InitCntxtSetupRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szInitCntxtSetupRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_InitCntxtSetupRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_InitCntxtSetupRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_InitCntxtSetupRespIEs),
 &flagSz3M,
 szProtIE_Cont_InitCntxtSetupRespIEsValidate,
 (U8 *) (&szProtIE_Cont_InitCntxtSetupRespIEsspec),
 0L
};
 CmPAsnElmDef *szInitCntxtSetupRespTkn[] =
{
 &szProtIE_Cont_InitCntxtSetupRespIEs,
  &szProtIE_Field_InitCntxtSetupRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szInitCntxtSetupRespspec =
{



 0,
 0,
 0L,
 0L,
 &szInitCntxtSetupRespTkn[0],
 0
};
 CmPAsnElmDef szInitCntxtSetupResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztInitCntxtSetupResp),
 &flagSz3M,
 0,
 (U8 *)(&szInitCntxtSetupRespspec),
 0L
};
 CmPAsnElmDef *sz_ValueInitCntxtSetupFailIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCause,
 &szCriticalityDiag
};
 U32 sz_ValueInitCntxtSetupFailIEsClsInstId[] =
{
 0,
 8,
 2,
 58
};
SzMsgConInf szInitCntxtSetupFailIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 2, 1, 0x2 },
  { 58, 1, 0x1 }
 },
 4,
 3
};
 CmPAsnClassInfo sz_ValueInitCntxtSetupFailIEsClsInfo =
{
 4,
 &sz_ValueInitCntxtSetupFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueInitCntxtSetupFailIEsClsSpec =
{



 &sz_ValueInitCntxtSetupFailIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueInitCntxtSetupFailIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueInitCntxtSetupFailIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueInitCntxtSetupFailIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueInitCntxtSetupFailIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_InitCntxtSetupFailIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueInitCntxtSetupFailIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_InitCntxtSetupFailIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_InitCntxtSetupFailIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_InitCntxtSetupFailIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_InitCntxtSetupFailIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_InitCntxtSetupFailIEsspec),
 0L
};


 S16 szProtIE_Cont_InitCntxtSetupFailIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_InitCntxtSetupFailIEs *protIe = 0L;
 SztProtIE_Field_InitCntxtSetupFailIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_InitCntxtSetupFailIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_InitCntxtSetupFailIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szInitCntxtSetupFailIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_InitCntxtSetupFailIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_InitCntxtSetupFailIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_InitCntxtSetupFailIEs),
 &flagSz3M,
 szProtIE_Cont_InitCntxtSetupFailIEsValidate,
 (U8 *) (&szProtIE_Cont_InitCntxtSetupFailIEsspec),
 0L
};
 CmPAsnElmDef *szInitCntxtSetupFailTkn[] =
{
 &szProtIE_Cont_InitCntxtSetupFailIEs,
  &szProtIE_Field_InitCntxtSetupFailIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szInitCntxtSetupFailspec =
{



 0,
 0,
 0L,
 0L,
 &szInitCntxtSetupFailTkn[0],
 0
};
 CmPAsnElmDef szInitCntxtSetupFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztInitCntxtSetupFail),
 &flagSz3M,
 0,
 (U8 *)(&szInitCntxtSetupFailspec),
 0L
};
 CmPAsnElmDef *sz_ExtnTAIItemExtIEsClsInst[] =
{
 0L
};
 U32 sz_ExtnTAIItemExtIEsClsInstId[] =
{
 0xffffffff
};
 CmPAsnClassInfo sz_ExtnTAIItemExtIEsClsInfo =
{
 0,
 &sz_ExtnTAIItemExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ExtnTAIItemExtIEsClsSpec =
{



 &sz_ExtnTAIItemExtIEsClsInfo,
 (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
 &sz_ExtnTAIItemExtIEsClsInst[0],



};
 CmPAsnElmDef sz_ExtnTAIItemExtIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ExtnTAIItemExtIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ExtnTAIItemExtIEsClsSpec)
};
 CmPAsnElmDef *szProtExtnField_TAIItemExtIEsTkn[] =
{
 &szProtExtnID,
 &szCriticality,
 &sz_ExtnTAIItemExtIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtExtnField_TAIItemExtIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtExtnField_TAIItemExtIEsTkn[0],
 0
};
 CmPAsnElmDef szProtExtnField_TAIItemExtIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtExtnField_TAIItemExtIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtExtnField_TAIItemExtIEsspec),
 0L
};
CmPAsnSetSeqOfDef szProtExtnCont_TAIItemExtIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szOptProtExtnCont_TAIItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAIItemExtIEs),
 &flagSz3O,
 0,
 (U8 *) (&szProtExtnCont_TAIItemExtIEsspec),
 0L
};
 CmPAsnElmDef szProtExtnCont_TAIItemExtIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtExtnCont_TAIItemExtIEs),
 &flagSz3M,
 0,
 (U8 *) (&szProtExtnCont_TAIItemExtIEsspec),
 0L
};
 CmPAsnElmDef *szTAIItemTkn[] =
{
 &szTAI,
 &szOptProtExtnCont_TAIItemExtIEs,
  &szProtExtnField_TAIItemExtIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTAIItemspec =
{



 1,
 0,
 0L,
 0L,
 &szTAIItemTkn[0],
 0
};
 CmPAsnElmDef szTAIItem =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTAIItem),
 &flagSz3M,
 0,
 (U8 *)(&szTAIItemspec),
 0L
};
 CmPAsnElmDef *sz_ValueTAIItemIEsClsInst[] =
{
 &szTAIItem
};
 U32 sz_ValueTAIItemIEsClsInstId[] =
{
 47
};
SzMsgConInf szTAIItemIEsConInf =
{
 {
  { 47, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueTAIItemIEsClsInfo =
{
 1,
 &sz_ValueTAIItemIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueTAIItemIEsClsSpec =
{



 &sz_ValueTAIItemIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueTAIItemIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueTAIItemIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueTAIItemIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueTAIItemIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_TAIItemIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueTAIItemIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_TAIItemIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_TAIItemIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_TAIItemIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_TAIItemIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_TAIItemIEsspec),
 0L
};

CmPAsnSetSeqOfDef szTAILstspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szTAILst =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztTAILst),
 &flagSz3M,
 0,
 (U8 *) (&szTAILstspec),
 0L
};
 CmPAsnElmDef *sz_ValuePagIEsClsInst[] =
{
 &szUEIdentityIdxValue,
 &szUEPagID,
 &szPagDRX,
 &szCNDomain,
 &szTAILst,
  &szProtIE_Field_TAIItemIEs,
  &szConstTerm,
 &szCSG_IdLst,
  &szCSG_IdLst_Item,
  &szConstTerm,
 &szPagPriority
};
 U32 sz_ValuePagIEsClsInstId[] =
{
 80,
 43,
 44,
 109,
 46,
  0xffffffff,
  0xffffffff,
 128,
  0xffffffff,
  0xffffffff,
 151
};
SzMsgConInf szPagIEsConInf =
{
 {
  { 80, 1, 0x2 },
  { 43, 1, 0x2 },
  { 44, 1, 0x1 },
  { 109, 1, 0x2 },
  { 46, 1, 0x2 },
  { 128, 1, 0x1 },
  { 151, 1, 0x1 }
 },
 7,
 4
};
 CmPAsnClassInfo sz_ValuePagIEsClsInfo =
{
 11,
 &sz_ValuePagIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePagIEsClsSpec =
{



 &sz_ValuePagIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValuePagIEsClsInst[0],



};
 CmPAsnElmDef sz_ValuePagIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValuePagIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValuePagIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_PagIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValuePagIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_PagIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_PagIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_PagIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_PagIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_PagIEsspec),
 0L
};


 S16 szProtIE_Cont_PagIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_PagIEs *protIe = 0L;
 SztProtIE_Field_PagIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_PagIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_PagIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szPagIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_PagIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_PagIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_PagIEs),
 &flagSz3M,
 szProtIE_Cont_PagIEsValidate,
 (U8 *) (&szProtIE_Cont_PagIEsspec),
 0L
};
 CmPAsnElmDef *szPagTkn[] =
{
 &szProtIE_Cont_PagIEs,
  &szProtIE_Field_PagIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szPagspec =
{



 0,
 0,
 0L,
 0L,
 &szPagTkn[0],
 0
};
 CmPAsnElmDef szPag =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztPag),
 &flagSz3M,
 0,
 (U8 *)(&szPagspec),
 0L
};
 CmPAsnElmDef *sz_ValueUECntxtRlsRqst_IEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCause,
 &szGWCntxtRlsInd
};
 U32 sz_ValueUECntxtRlsRqst_IEsClsInstId[] =
{
 0,
 8,
 2,
 164
};
SzMsgConInf szUECntxtRlsRqst_IEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 2, 1, 0x2 },
  { 164, 0, 0x1 }
 },
 4,
 3
};
 CmPAsnClassInfo sz_ValueUECntxtRlsRqst_IEsClsInfo =
{
 4,
 &sz_ValueUECntxtRlsRqst_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtRlsRqst_IEsClsSpec =
{



 &sz_ValueUECntxtRlsRqst_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUECntxtRlsRqst_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUECntxtRlsRqst_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUECntxtRlsRqst_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUECntxtRlsRqst_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UECntxtRlsRqst_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUECntxtRlsRqst_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtRlsRqst_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UECntxtRlsRqst_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UECntxtRlsRqst_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UECntxtRlsRqst_IEsspec),
 0L
};


 S16 szProtIE_Cont_UECntxtRlsRqst_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UECntxtRlsRqst_IEs *protIe = 0L;
 SztProtIE_Field_UECntxtRlsRqst_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UECntxtRlsRqst_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUECntxtRlsRqst_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtRlsRqst_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UECntxtRlsRqst_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UECntxtRlsRqst_IEs),
 &flagSz3M,
 szProtIE_Cont_UECntxtRlsRqst_IEsValidate,
 (U8 *) (&szProtIE_Cont_UECntxtRlsRqst_IEsspec),
 0L
};
 CmPAsnElmDef *szUECntxtRlsRqstTkn[] =
{
 &szProtIE_Cont_UECntxtRlsRqst_IEs,
  &szProtIE_Field_UECntxtRlsRqst_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUECntxtRlsRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szUECntxtRlsRqstTkn[0],
 0
};
 CmPAsnElmDef szUECntxtRlsRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUECntxtRlsRqst),
 &flagSz3M,
 0,
 (U8 *)(&szUECntxtRlsRqstspec),
 0L
};
 CmPAsnElmDef *sz_ValueUECntxtRlsCmmd_IEsClsInst[] =
{
 &szUE_S1AP_IDs,
 &szCause
};
 U32 sz_ValueUECntxtRlsCmmd_IEsClsInstId[] =
{
 99,
 2
};
SzMsgConInf szUECntxtRlsCmmd_IEsConInf =
{
 {
  { 99, 0, 0x2 },
  { 2, 1, 0x2 }
 },
 2,
 2
};
 CmPAsnClassInfo sz_ValueUECntxtRlsCmmd_IEsClsInfo =
{
 2,
 &sz_ValueUECntxtRlsCmmd_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtRlsCmmd_IEsClsSpec =
{



 &sz_ValueUECntxtRlsCmmd_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUECntxtRlsCmmd_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUECntxtRlsCmmd_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUECntxtRlsCmmd_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUECntxtRlsCmmd_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UECntxtRlsCmmd_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUECntxtRlsCmmd_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtRlsCmmd_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UECntxtRlsCmmd_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UECntxtRlsCmmd_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UECntxtRlsCmmd_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UECntxtRlsCmmd_IEsspec),
 0L
};


 S16 szProtIE_Cont_UECntxtRlsCmmd_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UECntxtRlsCmmd_IEs *protIe = 0L;
 SztProtIE_Field_UECntxtRlsCmmd_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UECntxtRlsCmmd_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UECntxtRlsCmmd_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUECntxtRlsCmmd_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtRlsCmmd_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UECntxtRlsCmmd_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UECntxtRlsCmmd_IEs),
 &flagSz3M,
 szProtIE_Cont_UECntxtRlsCmmd_IEsValidate,
 (U8 *) (&szProtIE_Cont_UECntxtRlsCmmd_IEsspec),
 0L
};
 CmPAsnElmDef *szUECntxtRlsCmmdTkn[] =
{
 &szProtIE_Cont_UECntxtRlsCmmd_IEs,
  &szProtIE_Field_UECntxtRlsCmmd_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUECntxtRlsCmmdspec =
{



 0,
 0,
 0L,
 0L,
 &szUECntxtRlsCmmdTkn[0],
 0
};
 CmPAsnElmDef szUECntxtRlsCmmd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUECntxtRlsCmmd),
 &flagSz3M,
 0,
 (U8 *)(&szUECntxtRlsCmmdspec),
 0L
};
 CmPAsnElmDef *sz_ValueUECntxtRlsComplete_IEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCriticalityDiag
};
 U32 sz_ValueUECntxtRlsComplete_IEsClsInstId[] =
{
 0,
 8,
 58
};
SzMsgConInf szUECntxtRlsComplete_IEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 58, 1, 0x1 }
 },
 3,
 2
};
 CmPAsnClassInfo sz_ValueUECntxtRlsComplete_IEsClsInfo =
{
 3,
 &sz_ValueUECntxtRlsComplete_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtRlsComplete_IEsClsSpec =
{



 &sz_ValueUECntxtRlsComplete_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUECntxtRlsComplete_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUECntxtRlsComplete_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUECntxtRlsComplete_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUECntxtRlsComplete_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UECntxtRlsComplete_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUECntxtRlsComplete_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtRlsComplete_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UECntxtRlsComplete_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UECntxtRlsComplete_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UECntxtRlsComplete_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UECntxtRlsComplete_IEsspec),
 0L
};


 S16 szProtIE_Cont_UECntxtRlsComplete_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UECntxtRlsComplete_IEs *protIe = 0L;
 SztProtIE_Field_UECntxtRlsComplete_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UECntxtRlsComplete_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UECntxtRlsComplete_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUECntxtRlsComplete_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtRlsComplete_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UECntxtRlsComplete_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UECntxtRlsComplete_IEs),
 &flagSz3M,
 szProtIE_Cont_UECntxtRlsComplete_IEsValidate,
 (U8 *) (&szProtIE_Cont_UECntxtRlsComplete_IEsspec),
 0L
};
 CmPAsnElmDef *szUECntxtRlsCompleteTkn[] =
{
 &szProtIE_Cont_UECntxtRlsComplete_IEs,
  &szProtIE_Field_UECntxtRlsComplete_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUECntxtRlsCompletespec =
{



 0,
 0,
 0L,
 0L,
 &szUECntxtRlsCompleteTkn[0],
 0
};
 CmPAsnElmDef szUECntxtRlsComplete =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUECntxtRlsComplete),
 &flagSz3M,
 0,
 (U8 *)(&szUECntxtRlsCompletespec),
 0L
};
 CmPAsnElmDef *sz_ValueUECntxtModificationRqstIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szSecurKey,
 &szSubscriberProfileIDforRFP,
 &szUEAggMaxBitrate,
 &szCSFallbackIndicator,
 &szUESecurCapabilities,
 &szCSGMembershipStatus,
 &szLAI
};
 U32 sz_ValueUECntxtModificationRqstIEsClsInstId[] =
{
 0,
 8,
 73,
 106,
 66,
 108,
 107,
 146,
 159
};
SzMsgConInf szUECntxtModificationRqstIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 73, 0, 0x1 },
  { 106, 1, 0x1 },
  { 66, 1, 0x1 },
  { 108, 0, 0x1 },
  { 107, 0, 0x1 },
  { 146, 1, 0x1 },
  { 159, 1, 0x1 }
 },
 9,
 2
};
 CmPAsnClassInfo sz_ValueUECntxtModificationRqstIEsClsInfo =
{
 9,
 &sz_ValueUECntxtModificationRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtModificationRqstIEsClsSpec =
{



 &sz_ValueUECntxtModificationRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUECntxtModificationRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUECntxtModificationRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUECntxtModificationRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUECntxtModificationRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UECntxtModificationRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUECntxtModificationRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtModificationRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UECntxtModificationRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UECntxtModificationRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UECntxtModificationRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UECntxtModificationRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_UECntxtModificationRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UECntxtModificationRqstIEs *protIe = 0L;
 SztProtIE_Field_UECntxtModificationRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UECntxtModificationRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UECntxtModificationRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUECntxtModificationRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtModificationRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UECntxtModificationRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UECntxtModificationRqstIEs),
 &flagSz3M,
 szProtIE_Cont_UECntxtModificationRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_UECntxtModificationRqstIEsspec),
 0L
};
 CmPAsnElmDef *szUECntxtModificationRqstTkn[] =
{
 &szProtIE_Cont_UECntxtModificationRqstIEs,
  &szProtIE_Field_UECntxtModificationRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUECntxtModificationRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szUECntxtModificationRqstTkn[0],
 0
};
 CmPAsnElmDef szUECntxtModificationRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUECntxtModificationRqst),
 &flagSz3M,
 0,
 (U8 *)(&szUECntxtModificationRqstspec),
 0L
};
 CmPAsnElmDef *sz_ValueUECntxtModificationRespIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCriticalityDiag
};
 U32 sz_ValueUECntxtModificationRespIEsClsInstId[] =
{
 0,
 8,
 58
};
SzMsgConInf szUECntxtModificationRespIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 58, 1, 0x1 }
 },
 3,
 2
};
 CmPAsnClassInfo sz_ValueUECntxtModificationRespIEsClsInfo =
{
 3,
 &sz_ValueUECntxtModificationRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtModificationRespIEsClsSpec =
{



 &sz_ValueUECntxtModificationRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUECntxtModificationRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUECntxtModificationRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUECntxtModificationRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUECntxtModificationRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UECntxtModificationRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUECntxtModificationRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtModificationRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UECntxtModificationRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UECntxtModificationRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UECntxtModificationRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UECntxtModificationRespIEsspec),
 0L
};


 S16 szProtIE_Cont_UECntxtModificationRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UECntxtModificationRespIEs *protIe = 0L;
 SztProtIE_Field_UECntxtModificationRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UECntxtModificationRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UECntxtModificationRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUECntxtModificationRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtModificationRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UECntxtModificationRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UECntxtModificationRespIEs),
 &flagSz3M,
 szProtIE_Cont_UECntxtModificationRespIEsValidate,
 (U8 *) (&szProtIE_Cont_UECntxtModificationRespIEsspec),
 0L
};
 CmPAsnElmDef *szUECntxtModificationRespTkn[] =
{
 &szProtIE_Cont_UECntxtModificationRespIEs,
  &szProtIE_Field_UECntxtModificationRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUECntxtModificationRespspec =
{



 0,
 0,
 0L,
 0L,
 &szUECntxtModificationRespTkn[0],
 0
};
 CmPAsnElmDef szUECntxtModificationResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUECntxtModificationResp),
 &flagSz3M,
 0,
 (U8 *)(&szUECntxtModificationRespspec),
 0L
};
 CmPAsnElmDef *sz_ValueUECntxtModificationFailIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCause,
 &szCriticalityDiag
};
 U32 sz_ValueUECntxtModificationFailIEsClsInstId[] =
{
 0,
 8,
 2,
 58
};
SzMsgConInf szUECntxtModificationFailIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 2, 1, 0x2 },
  { 58, 1, 0x1 }
 },
 4,
 3
};
 CmPAsnClassInfo sz_ValueUECntxtModificationFailIEsClsInfo =
{
 4,
 &sz_ValueUECntxtModificationFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECntxtModificationFailIEsClsSpec =
{



 &sz_ValueUECntxtModificationFailIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUECntxtModificationFailIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUECntxtModificationFailIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUECntxtModificationFailIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUECntxtModificationFailIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UECntxtModificationFailIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUECntxtModificationFailIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECntxtModificationFailIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UECntxtModificationFailIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UECntxtModificationFailIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UECntxtModificationFailIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UECntxtModificationFailIEsspec),
 0L
};


 S16 szProtIE_Cont_UECntxtModificationFailIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UECntxtModificationFailIEs *protIe = 0L;
 SztProtIE_Field_UECntxtModificationFailIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UECntxtModificationFailIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UECntxtModificationFailIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUECntxtModificationFailIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECntxtModificationFailIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UECntxtModificationFailIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UECntxtModificationFailIEs),
 &flagSz3M,
 szProtIE_Cont_UECntxtModificationFailIEsValidate,
 (U8 *) (&szProtIE_Cont_UECntxtModificationFailIEsspec),
 0L
};
 CmPAsnElmDef *szUECntxtModificationFailTkn[] =
{
 &szProtIE_Cont_UECntxtModificationFailIEs,
  &szProtIE_Field_UECntxtModificationFailIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUECntxtModificationFailspec =
{



 0,
 0,
 0L,
 0L,
 &szUECntxtModificationFailTkn[0],
 0
};
 CmPAsnElmDef szUECntxtModificationFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUECntxtModificationFail),
 &flagSz3M,
 0,
 (U8 *)(&szUECntxtModificationFailspec),
 0L
};
 CmPAsnElmDef *sz_ValueUERadioCapbltyMatchRqstIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szUERadioCapblty
};
 U32 sz_ValueUERadioCapbltyMatchRqstIEsClsInstId[] =
{
 0,
 8,
 74
};
SzMsgConInf szUERadioCapbltyMatchRqstIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 74, 1, 0x1 }
 },
 3,
 2
};
 CmPAsnClassInfo sz_ValueUERadioCapbltyMatchRqstIEsClsInfo =
{
 3,
 &sz_ValueUERadioCapbltyMatchRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUERadioCapbltyMatchRqstIEsClsSpec =
{



 &sz_ValueUERadioCapbltyMatchRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUERadioCapbltyMatchRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUERadioCapbltyMatchRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUERadioCapbltyMatchRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUERadioCapbltyMatchRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UERadioCapbltyMatchRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUERadioCapbltyMatchRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UERadioCapbltyMatchRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UERadioCapbltyMatchRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UERadioCapbltyMatchRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UERadioCapbltyMatchRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UERadioCapbltyMatchRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_UERadioCapbltyMatchRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UERadioCapbltyMatchRqstIEs *protIe = 0L;
 SztProtIE_Field_UERadioCapbltyMatchRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UERadioCapbltyMatchRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UERadioCapbltyMatchRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUERadioCapbltyMatchRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UERadioCapbltyMatchRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UERadioCapbltyMatchRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UERadioCapbltyMatchRqstIEs),
 &flagSz3M,
 szProtIE_Cont_UERadioCapbltyMatchRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_UERadioCapbltyMatchRqstIEsspec),
 0L
};
 CmPAsnElmDef *szUERadioCapbltyMatchRqstTkn[] =
{
 &szProtIE_Cont_UERadioCapbltyMatchRqstIEs,
  &szProtIE_Field_UERadioCapbltyMatchRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUERadioCapbltyMatchRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szUERadioCapbltyMatchRqstTkn[0],
 0
};
 CmPAsnElmDef szUERadioCapbltyMatchRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUERadioCapbltyMatchRqst),
 &flagSz3M,
 0,
 (U8 *)(&szUERadioCapbltyMatchRqstspec),
 0L
};
 CmPAsnElmDef *sz_ValueUERadioCapbltyMatchRespIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szVoiceSupportMatchIndicator,
 &szCriticalityDiag
};
 U32 sz_ValueUERadioCapbltyMatchRespIEsClsInstId[] =
{
 0,
 8,
 169,
 58
};
SzMsgConInf szUERadioCapbltyMatchRespIEsConInf =
{
 {
  { 0, 1, 0x2 },
  { 8, 1, 0x2 },
  { 169, 0, 0x2 },
  { 58, 1, 0x1 }
 },
 4,
 3
};
 CmPAsnClassInfo sz_ValueUERadioCapbltyMatchRespIEsClsInfo =
{
 4,
 &sz_ValueUERadioCapbltyMatchRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUERadioCapbltyMatchRespIEsClsSpec =
{



 &sz_ValueUERadioCapbltyMatchRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUERadioCapbltyMatchRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUERadioCapbltyMatchRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUERadioCapbltyMatchRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUERadioCapbltyMatchRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UERadioCapbltyMatchRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUERadioCapbltyMatchRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UERadioCapbltyMatchRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UERadioCapbltyMatchRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UERadioCapbltyMatchRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UERadioCapbltyMatchRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UERadioCapbltyMatchRespIEsspec),
 0L
};


 S16 szProtIE_Cont_UERadioCapbltyMatchRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UERadioCapbltyMatchRespIEs *protIe = 0L;
 SztProtIE_Field_UERadioCapbltyMatchRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UERadioCapbltyMatchRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UERadioCapbltyMatchRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUERadioCapbltyMatchRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UERadioCapbltyMatchRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UERadioCapbltyMatchRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UERadioCapbltyMatchRespIEs),
 &flagSz3M,
 szProtIE_Cont_UERadioCapbltyMatchRespIEsValidate,
 (U8 *) (&szProtIE_Cont_UERadioCapbltyMatchRespIEsspec),
 0L
};
 CmPAsnElmDef *szUERadioCapbltyMatchRespTkn[] =
{
 &szProtIE_Cont_UERadioCapbltyMatchRespIEs,
  &szProtIE_Field_UERadioCapbltyMatchRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUERadioCapbltyMatchRespspec =
{



 0,
 0,
 0L,
 0L,
 &szUERadioCapbltyMatchRespTkn[0],
 0
};
 CmPAsnElmDef szUERadioCapbltyMatchResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUERadioCapbltyMatchResp),
 &flagSz3M,
 0,
 (U8 *)(&szUERadioCapbltyMatchRespspec),
 0L
};
 CmPAsnElmDef *sz_ValueDlnkNASTport_IEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szNAS_PDU,
 &szHovrRestrnLst,
 &szSubscriberProfileIDforRFP
};
 U32 sz_ValueDlnkNASTport_IEsClsInstId[] =
{
 0,
 8,
 26,
 41,
 106
};
SzMsgConInf szDlnkNASTport_IEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 26, 0, 0x2 },
  { 41, 1, 0x1 },
  { 106, 1, 0x1 }
 },
 5,
 3
};
 CmPAsnClassInfo sz_ValueDlnkNASTport_IEsClsInfo =
{
 5,
 &sz_ValueDlnkNASTport_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueDlnkNASTport_IEsClsSpec =
{



 &sz_ValueDlnkNASTport_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueDlnkNASTport_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueDlnkNASTport_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueDlnkNASTport_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueDlnkNASTport_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_DlnkNASTport_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueDlnkNASTport_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_DlnkNASTport_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_DlnkNASTport_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_DlnkNASTport_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_DlnkNASTport_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_DlnkNASTport_IEsspec),
 0L
};


 S16 szProtIE_Cont_DlnkNASTport_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_DlnkNASTport_IEs *protIe = 0L;
 SztProtIE_Field_DlnkNASTport_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_DlnkNASTport_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_DlnkNASTport_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szDlnkNASTport_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_DlnkNASTport_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_DlnkNASTport_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_DlnkNASTport_IEs),
 &flagSz3M,
 szProtIE_Cont_DlnkNASTport_IEsValidate,
 (U8 *) (&szProtIE_Cont_DlnkNASTport_IEsspec),
 0L
};
 CmPAsnElmDef *szDlnkNASTportTkn[] =
{
 &szProtIE_Cont_DlnkNASTport_IEs,
  &szProtIE_Field_DlnkNASTport_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szDlnkNASTportspec =
{



 0,
 0,
 0L,
 0L,
 &szDlnkNASTportTkn[0],
 0
};
 CmPAsnElmDef szDlnkNASTport =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztDlnkNASTport),
 &flagSz3M,
 0,
 (U8 *)(&szDlnkNASTportspec),
 0L
};
 CmPAsnElmDef *sz_ValueInitUEMsg_IEsClsInst[] =
{
 &szENB_UE_S1AP_ID,
 &szNAS_PDU,
 &szTAI,
 &szEUTRAN_CGI,
 &szRRC_Establishment_Cause,
 &szS_TMSI,
 &szCSG_Id,
 &szGUMMEI,
 &szCellAccessMode,
 &szTportLyrAddr,
 &szRelayNode_Indicator,
 &szGUMMEITyp,
 &szTunnelInform
};
 U32 sz_ValueInitUEMsg_IEsClsInstId[] =
{
 8,
 26,
 67,
 100,
 134,
 96,
 127,
 75,
 145,
 155,
 160,
 170,
 176
};
SzMsgConInf szInitUEMsg_IEsConInf =
{
 {
  { 8, 0, 0x2 },
  { 26, 0, 0x2 },
  { 67, 0, 0x2 },
  { 100, 1, 0x2 },
  { 134, 1, 0x2 },
  { 96, 0, 0x1 },
  { 127, 0, 0x1 },
  { 75, 0, 0x1 },
  { 145, 0, 0x1 },
  { 155, 1, 0x1 },
  { 160, 0, 0x1 },
  { 170, 1, 0x1 },
  { 176, 1, 0x1 }
 },
 13,
 5
};
 CmPAsnClassInfo sz_ValueInitUEMsg_IEsClsInfo =
{
 13,
 &sz_ValueInitUEMsg_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueInitUEMsg_IEsClsSpec =
{



 &sz_ValueInitUEMsg_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueInitUEMsg_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueInitUEMsg_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueInitUEMsg_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueInitUEMsg_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_InitUEMsg_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueInitUEMsg_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_InitUEMsg_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_InitUEMsg_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_InitUEMsg_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_InitUEMsg_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_InitUEMsg_IEsspec),
 0L
};


 S16 szProtIE_Cont_InitUEMsg_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_InitUEMsg_IEs *protIe = 0L;
 SztProtIE_Field_InitUEMsg_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_InitUEMsg_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_InitUEMsg_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szInitUEMsg_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_InitUEMsg_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_InitUEMsg_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_InitUEMsg_IEs),
 &flagSz3M,
 szProtIE_Cont_InitUEMsg_IEsValidate,
 (U8 *) (&szProtIE_Cont_InitUEMsg_IEsspec),
 0L
};
 CmPAsnElmDef *szInitUEMsgTkn[] =
{
 &szProtIE_Cont_InitUEMsg_IEs,
  &szProtIE_Field_InitUEMsg_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szInitUEMsgspec =
{



 0,
 0,
 0L,
 0L,
 &szInitUEMsgTkn[0],
 0
};
 CmPAsnElmDef szInitUEMsg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztInitUEMsg),
 &flagSz3M,
 0,
 (U8 *)(&szInitUEMsgspec),
 0L
};
 CmPAsnElmDef *sz_ValueUlnkNASTport_IEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szNAS_PDU,
 &szEUTRAN_CGI,
 &szTAI,
 &szTportLyrAddr
};
 U32 sz_ValueUlnkNASTport_IEsClsInstId[] =
{
 0,
 8,
 26,
 100,
 67,
 155
};
SzMsgConInf szUlnkNASTport_IEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 26, 0, 0x2 },
  { 100, 1, 0x2 },
  { 67, 1, 0x2 },
  { 155, 1, 0x1 }
 },
 6,
 5
};
 CmPAsnClassInfo sz_ValueUlnkNASTport_IEsClsInfo =
{
 6,
 &sz_ValueUlnkNASTport_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUlnkNASTport_IEsClsSpec =
{



 &sz_ValueUlnkNASTport_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUlnkNASTport_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUlnkNASTport_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUlnkNASTport_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUlnkNASTport_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UlnkNASTport_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUlnkNASTport_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UlnkNASTport_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UlnkNASTport_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UlnkNASTport_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UlnkNASTport_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UlnkNASTport_IEsspec),
 0L
};


 S16 szProtIE_Cont_UlnkNASTport_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UlnkNASTport_IEs *protIe = 0L;
 SztProtIE_Field_UlnkNASTport_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UlnkNASTport_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UlnkNASTport_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUlnkNASTport_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UlnkNASTport_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UlnkNASTport_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UlnkNASTport_IEs),
 &flagSz3M,
 szProtIE_Cont_UlnkNASTport_IEsValidate,
 (U8 *) (&szProtIE_Cont_UlnkNASTport_IEsspec),
 0L
};
 CmPAsnElmDef *szUlnkNASTportTkn[] =
{
 &szProtIE_Cont_UlnkNASTport_IEs,
  &szProtIE_Field_UlnkNASTport_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUlnkNASTportspec =
{



 0,
 0,
 0L,
 0L,
 &szUlnkNASTportTkn[0],
 0
};
 CmPAsnElmDef szUlnkNASTport =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUlnkNASTport),
 &flagSz3M,
 0,
 (U8 *)(&szUlnkNASTportspec),
 0L
};
 CmPAsnElmDef *sz_ValueNASNonDlvryInd_IEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szNAS_PDU,
 &szCause
};
 U32 sz_ValueNASNonDlvryInd_IEsClsInstId[] =
{
 0,
 8,
 26,
 2
};
SzMsgConInf szNASNonDlvryInd_IEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 26, 1, 0x2 },
  { 2, 1, 0x2 }
 },
 4,
 4
};
 CmPAsnClassInfo sz_ValueNASNonDlvryInd_IEsClsInfo =
{
 4,
 &sz_ValueNASNonDlvryInd_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueNASNonDlvryInd_IEsClsSpec =
{



 &sz_ValueNASNonDlvryInd_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueNASNonDlvryInd_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueNASNonDlvryInd_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueNASNonDlvryInd_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueNASNonDlvryInd_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_NASNonDlvryInd_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueNASNonDlvryInd_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_NASNonDlvryInd_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_NASNonDlvryInd_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_NASNonDlvryInd_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_NASNonDlvryInd_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_NASNonDlvryInd_IEsspec),
 0L
};


 S16 szProtIE_Cont_NASNonDlvryInd_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_NASNonDlvryInd_IEs *protIe = 0L;
 SztProtIE_Field_NASNonDlvryInd_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_NASNonDlvryInd_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_NASNonDlvryInd_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szNASNonDlvryInd_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_NASNonDlvryInd_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_NASNonDlvryInd_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_NASNonDlvryInd_IEs),
 &flagSz3M,
 szProtIE_Cont_NASNonDlvryInd_IEsValidate,
 (U8 *) (&szProtIE_Cont_NASNonDlvryInd_IEsspec),
 0L
};
 CmPAsnElmDef *szNASNonDlvryIndTkn[] =
{
 &szProtIE_Cont_NASNonDlvryInd_IEs,
  &szProtIE_Field_NASNonDlvryInd_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szNASNonDlvryIndspec =
{



 0,
 0,
 0L,
 0L,
 &szNASNonDlvryIndTkn[0],
 0
};
 CmPAsnElmDef szNASNonDlvryInd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztNASNonDlvryInd),
 &flagSz3M,
 0,
 (U8 *)(&szNASNonDlvryIndspec),
 0L
};

CmPAsnTknEnum szResetAllLst[2] =
{
 1,
 SztResetAllreset_allEnum
};
CmPAsnEnumDef szResetAllspec =
{



 szResetAllLst,
 0L
};
CmPAsnElmDef szResetAll =
{



 CM_PASN_TET_ENUM,
 1,
 sizeof(SztResetAll),
 &flagSz3M,
 0,
 (U8 *)(&szResetAllspec),
 0L
};

 CmPAsnElmDef *sz_ValueUE_assocLogS1_ConItemResClsInst[] =
{
 &szUE_assocLogS1_ConItem
};
 U32 sz_ValueUE_assocLogS1_ConItemResClsInstId[] =
{
 91
};
SzMsgConInf szUE_assocLogS1_ConItemResConInf =
{
 {
  { 91, 0, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueUE_assocLogS1_ConItemResClsInfo =
{
 1,
 &sz_ValueUE_assocLogS1_ConItemResClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUE_assocLogS1_ConItemResClsSpec =
{



 &sz_ValueUE_assocLogS1_ConItemResClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUE_assocLogS1_ConItemResClsInst[0],



};
 CmPAsnElmDef sz_ValueUE_assocLogS1_ConItemResCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUE_assocLogS1_ConItemResCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUE_assocLogS1_ConItemResClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UE_assocLogS1_ConItemResTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUE_assocLogS1_ConItemResCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UE_assocLogS1_ConItemResspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UE_assocLogS1_ConItemResTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UE_assocLogS1_ConItemRes =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UE_assocLogS1_ConItemRes),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UE_assocLogS1_ConItemResspec),
 0L
};

CmPAsnSetSeqOfDef szUE_assocLogS1_ConLstResspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szUE_assocLogS1_ConLstRes =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztUE_assocLogS1_ConLstRes),
 &flagSz3M,
 0,
 (U8 *) (&szUE_assocLogS1_ConLstResspec),
 0L
};
 CmPAsnElmDef *szResetTypTkn[] =
{
 &szResetAll,
 &szUE_assocLogS1_ConLstRes,
  &szProtIE_Field_UE_assocLogS1_ConItemRes,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szResetTypspec =
{



 2,
 0,
 &szResetTypTkn[0]
};
CmPAsnElmDef szResetTyp =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztResetTyp),
 &flagSz3M,
 0L,
 (U8 *)(&szResetTypspec),
 0L
};
 CmPAsnElmDef *sz_ValueResetIEsClsInst[] =
{
 &szCause,
 &szResetTyp
};
 U32 sz_ValueResetIEsClsInstId[] =
{
 2,
 92
};
SzMsgConInf szResetIEsConInf =
{
 {
  { 2, 1, 0x2 },
  { 92, 0, 0x2 }
 },
 2,
 2
};
 CmPAsnClassInfo sz_ValueResetIEsClsInfo =
{
 2,
 &sz_ValueResetIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueResetIEsClsSpec =
{



 &sz_ValueResetIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueResetIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueResetIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueResetIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueResetIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ResetIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueResetIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ResetIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ResetIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ResetIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ResetIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ResetIEsspec),
 0L
};


 S16 szProtIE_Cont_ResetIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ResetIEs *protIe = 0L;
 SztProtIE_Field_ResetIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ResetIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ResetIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szResetIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ResetIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ResetIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ResetIEs),
 &flagSz3M,
 szProtIE_Cont_ResetIEsValidate,
 (U8 *) (&szProtIE_Cont_ResetIEsspec),
 0L
};
 CmPAsnElmDef *szResetTkn[] =
{
 &szProtIE_Cont_ResetIEs,
  &szProtIE_Field_ResetIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szResetspec =
{



 0,
 0,
 0L,
 0L,
 &szResetTkn[0],
 0
};
 CmPAsnElmDef szReset =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztReset),
 &flagSz3M,
 0,
 (U8 *)(&szResetspec),
 0L
};
 CmPAsnElmDef *sz_ValueUE_assocLogS1_ConItemResAckClsInst[] =
{
 &szUE_assocLogS1_ConItem
};
 U32 sz_ValueUE_assocLogS1_ConItemResAckClsInstId[] =
{
 91
};
SzMsgConInf szUE_assocLogS1_ConItemResAckConInf =
{
 {
  { 91, 1, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueUE_assocLogS1_ConItemResAckClsInfo =
{
 1,
 &sz_ValueUE_assocLogS1_ConItemResAckClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUE_assocLogS1_ConItemResAckClsSpec =
{



 &sz_ValueUE_assocLogS1_ConItemResAckClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUE_assocLogS1_ConItemResAckClsInst[0],



};
 CmPAsnElmDef sz_ValueUE_assocLogS1_ConItemResAckCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUE_assocLogS1_ConItemResAckCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUE_assocLogS1_ConItemResAckClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UE_assocLogS1_ConItemResAckTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUE_assocLogS1_ConItemResAckCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UE_assocLogS1_ConItemResAckspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UE_assocLogS1_ConItemResAckTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UE_assocLogS1_ConItemResAck =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UE_assocLogS1_ConItemResAck),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UE_assocLogS1_ConItemResAckspec),
 0L
};

CmPAsnSetSeqOfDef szUE_assocLogS1_ConLstResAckspec =
{



 1,
 256,
 3*sizeof(U32)
};
 CmPAsnElmDef szUE_assocLogS1_ConLstResAck =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztUE_assocLogS1_ConLstResAck),
 &flagSz3M,
 0,
 (U8 *) (&szUE_assocLogS1_ConLstResAckspec),
 0L
};
 CmPAsnElmDef *sz_ValueResetAckgIEsClsInst[] =
{
 &szUE_assocLogS1_ConLstResAck,
  &szProtIE_Field_UE_assocLogS1_ConItemResAck,
  &szConstTerm,
 &szCriticalityDiag
};
 U32 sz_ValueResetAckgIEsClsInstId[] =
{
 93,
  0xffffffff,
  0xffffffff,
 58
};
SzMsgConInf szResetAckgIEsConInf =
{
 {
  { 93, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 2,
 0
};
 CmPAsnClassInfo sz_ValueResetAckgIEsClsInfo =
{
 4,
 &sz_ValueResetAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueResetAckgIEsClsSpec =
{



 &sz_ValueResetAckgIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueResetAckgIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueResetAckgIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueResetAckgIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueResetAckgIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ResetAckgIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueResetAckgIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ResetAckgIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ResetAckgIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ResetAckgIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ResetAckgIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ResetAckgIEsspec),
 0L
};


 S16 szProtIE_Cont_ResetAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ResetAckgIEs *protIe = 0L;
 SztProtIE_Field_ResetAckgIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ResetAckgIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ResetAckgIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szResetAckgIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ResetAckgIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ResetAckgIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ResetAckgIEs),
 &flagSz3M,
 szProtIE_Cont_ResetAckgIEsValidate,
 (U8 *) (&szProtIE_Cont_ResetAckgIEsspec),
 0L
};
 CmPAsnElmDef *szResetAckgTkn[] =
{
 &szProtIE_Cont_ResetAckgIEs,
  &szProtIE_Field_ResetAckgIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szResetAckgspec =
{



 0,
 0,
 0L,
 0L,
 &szResetAckgTkn[0],
 0
};
 CmPAsnElmDef szResetAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztResetAckg),
 &flagSz3M,
 0,
 (U8 *)(&szResetAckgspec),
 0L
};
 CmPAsnElmDef *sz_ValueErrIndIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCause,
 &szCriticalityDiag
};
 U32 sz_ValueErrIndIEsClsInstId[] =
{
 0,
 8,
 2,
 58
};
SzMsgConInf szErrIndIEsConInf =
{
 {
  { 0, 1, 0x1 },
  { 8, 1, 0x1 },
  { 2, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 4,
 0
};
 CmPAsnClassInfo sz_ValueErrIndIEsClsInfo =
{
 4,
 &sz_ValueErrIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueErrIndIEsClsSpec =
{



 &sz_ValueErrIndIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueErrIndIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueErrIndIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueErrIndIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueErrIndIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ErrIndIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueErrIndIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ErrIndIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ErrIndIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ErrIndIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ErrIndIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ErrIndIEsspec),
 0L
};


 S16 szProtIE_Cont_ErrIndIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ErrIndIEs *protIe = 0L;
 SztProtIE_Field_ErrIndIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ErrIndIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ErrIndIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szErrIndIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ErrIndIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ErrIndIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ErrIndIEs),
 &flagSz3M,
 szProtIE_Cont_ErrIndIEsValidate,
 (U8 *) (&szProtIE_Cont_ErrIndIEsspec),
 0L
};
 CmPAsnElmDef *szErrIndTkn[] =
{
 &szProtIE_Cont_ErrIndIEs,
  &szProtIE_Field_ErrIndIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szErrIndspec =
{



 0,
 0,
 0L,
 0L,
 &szErrIndTkn[0],
 0
};
 CmPAsnElmDef szErrInd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztErrInd),
 &flagSz3M,
 0,
 (U8 *)(&szErrIndspec),
 0L
};
 CmPAsnElmDef *sz_ValueS1SetupRqstIEsClsInst[] =
{
 &szGlobal_ENB_ID,
 &szENBname,
 &szSuppTAs,
  &szSuppTAs_Item,
  &szConstTerm,
 &szPagDRX,
 &szCSG_IdLst,
  &szCSG_IdLst_Item,
  &szConstTerm,

};
 U32 sz_ValueS1SetupRqstIEsClsInstId[] =
{
 59,
 60,
 64,
  0xffffffff,
  0xffffffff,
 137,
 128,
  0xffffffff,
  0xffffffff
};
SzMsgConInf szS1SetupRqstIEsConInf =
{
 {
  { 59, 0, 0x2 },
  { 60, 1, 0x1 },
  { 64, 0, 0x2 },
  { 137, 1, 0x2 },
  { 128, 0, 0x1 }
 },
 5,
 3
};
 CmPAsnClassInfo sz_ValueS1SetupRqstIEsClsInfo =
{
 9,
 &sz_ValueS1SetupRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueS1SetupRqstIEsClsSpec =
{



 &sz_ValueS1SetupRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueS1SetupRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueS1SetupRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueS1SetupRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueS1SetupRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_S1SetupRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueS1SetupRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_S1SetupRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_S1SetupRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_S1SetupRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_S1SetupRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_S1SetupRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_S1SetupRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_S1SetupRqstIEs *protIe = 0L;
 SztProtIE_Field_S1SetupRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_S1SetupRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_S1SetupRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szS1SetupRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_S1SetupRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_S1SetupRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_S1SetupRqstIEs),
 &flagSz3M,
 szProtIE_Cont_S1SetupRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_S1SetupRqstIEsspec),
 0L
};
 CmPAsnElmDef *szS1SetupRqstTkn[] =
{
 &szProtIE_Cont_S1SetupRqstIEs,
  &szProtIE_Field_S1SetupRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szS1SetupRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szS1SetupRqstTkn[0],
 0
};
 CmPAsnElmDef szS1SetupRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztS1SetupRqst),
 &flagSz3M,
 0,
 (U8 *)(&szS1SetupRqstspec),
 0L
};
 CmPAsnElmDef *sz_ValueS1SetupRespIEsClsInst[] =
{
 &szMMEname,
 &szSrvdGUMMEIs,
  &szSrvdGUMMEIsItem,
  &szConstTerm,
 &szRelativeMMECapacity,
 &szMMERelaySupportIndicator,
 &szCriticalityDiag
};
 U32 sz_ValueS1SetupRespIEsClsInstId[] =
{
 61,
 105,
  0xffffffff,
  0xffffffff,
 87,
 163,
 58
};
SzMsgConInf szS1SetupRespIEsConInf =
{
 {
  { 61, 1, 0x1 },
  { 105, 0, 0x2 },
  { 87, 1, 0x2 },
  { 163, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 5,
 2
};
 CmPAsnClassInfo sz_ValueS1SetupRespIEsClsInfo =
{
 7,
 &sz_ValueS1SetupRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueS1SetupRespIEsClsSpec =
{



 &sz_ValueS1SetupRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueS1SetupRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueS1SetupRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueS1SetupRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueS1SetupRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_S1SetupRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueS1SetupRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_S1SetupRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_S1SetupRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_S1SetupRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_S1SetupRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_S1SetupRespIEsspec),
 0L
};


 S16 szProtIE_Cont_S1SetupRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_S1SetupRespIEs *protIe = 0L;
 SztProtIE_Field_S1SetupRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_S1SetupRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_S1SetupRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szS1SetupRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_S1SetupRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_S1SetupRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_S1SetupRespIEs),
 &flagSz3M,
 szProtIE_Cont_S1SetupRespIEsValidate,
 (U8 *) (&szProtIE_Cont_S1SetupRespIEsspec),
 0L
};
 CmPAsnElmDef *szS1SetupRespTkn[] =
{
 &szProtIE_Cont_S1SetupRespIEs,
  &szProtIE_Field_S1SetupRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szS1SetupRespspec =
{



 0,
 0,
 0L,
 0L,
 &szS1SetupRespTkn[0],
 0
};
 CmPAsnElmDef szS1SetupResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztS1SetupResp),
 &flagSz3M,
 0,
 (U8 *)(&szS1SetupRespspec),
 0L
};
 CmPAsnElmDef *sz_ValueS1SetupFailIEsClsInst[] =
{
 &szCause,
 &szTimeToWait,
 &szCriticalityDiag
};
 U32 sz_ValueS1SetupFailIEsClsInstId[] =
{
 2,
 65,
 58
};
SzMsgConInf szS1SetupFailIEsConInf =
{
 {
  { 2, 1, 0x2 },
  { 65, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 3,
 1
};
 CmPAsnClassInfo sz_ValueS1SetupFailIEsClsInfo =
{
 3,
 &sz_ValueS1SetupFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueS1SetupFailIEsClsSpec =
{



 &sz_ValueS1SetupFailIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueS1SetupFailIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueS1SetupFailIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueS1SetupFailIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueS1SetupFailIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_S1SetupFailIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueS1SetupFailIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_S1SetupFailIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_S1SetupFailIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_S1SetupFailIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_S1SetupFailIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_S1SetupFailIEsspec),
 0L
};


 S16 szProtIE_Cont_S1SetupFailIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_S1SetupFailIEs *protIe = 0L;
 SztProtIE_Field_S1SetupFailIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_S1SetupFailIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_S1SetupFailIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szS1SetupFailIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_S1SetupFailIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_S1SetupFailIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_S1SetupFailIEs),
 &flagSz3M,
 szProtIE_Cont_S1SetupFailIEsValidate,
 (U8 *) (&szProtIE_Cont_S1SetupFailIEsspec),
 0L
};
 CmPAsnElmDef *szS1SetupFailTkn[] =
{
 &szProtIE_Cont_S1SetupFailIEs,
  &szProtIE_Field_S1SetupFailIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szS1SetupFailspec =
{



 0,
 0,
 0L,
 0L,
 &szS1SetupFailTkn[0],
 0
};
 CmPAsnElmDef szS1SetupFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztS1SetupFail),
 &flagSz3M,
 0,
 (U8 *)(&szS1SetupFailspec),
 0L
};
 CmPAsnElmDef *sz_ValueENBConfigUpdIEsClsInst[] =
{
 &szENBname,
 &szSuppTAs,
  &szSuppTAs_Item,
  &szConstTerm,
 &szCSG_IdLst,
  &szCSG_IdLst_Item,
  &szConstTerm,
 &szPagDRX
};
 U32 sz_ValueENBConfigUpdIEsClsInstId[] =
{
 60,
 64,
  0xffffffff,
  0xffffffff,
 128,
  0xffffffff,
  0xffffffff,
 137
};
SzMsgConInf szENBConfigUpdIEsConInf =
{
 {
  { 60, 1, 0x1 },
  { 64, 0, 0x1 },
  { 128, 0, 0x1 },
  { 137, 1, 0x1 }
 },
 4,
 0
};
 CmPAsnClassInfo sz_ValueENBConfigUpdIEsClsInfo =
{
 8,
 &sz_ValueENBConfigUpdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBConfigUpdIEsClsSpec =
{



 &sz_ValueENBConfigUpdIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueENBConfigUpdIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueENBConfigUpdIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueENBConfigUpdIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueENBConfigUpdIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ENBConfigUpdIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueENBConfigUpdIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBConfigUpdIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ENBConfigUpdIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ENBConfigUpdIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ENBConfigUpdIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ENBConfigUpdIEsspec),
 0L
};


 S16 szProtIE_Cont_ENBConfigUpdIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ENBConfigUpdIEs *protIe = 0L;
 SztProtIE_Field_ENBConfigUpdIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ENBConfigUpdIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ENBConfigUpdIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szENBConfigUpdIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBConfigUpdIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ENBConfigUpdIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ENBConfigUpdIEs),
 &flagSz3M,
 szProtIE_Cont_ENBConfigUpdIEsValidate,
 (U8 *) (&szProtIE_Cont_ENBConfigUpdIEsspec),
 0L
};
 CmPAsnElmDef *szENBConfigUpdTkn[] =
{
 &szProtIE_Cont_ENBConfigUpdIEs,
  &szProtIE_Field_ENBConfigUpdIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szENBConfigUpdspec =
{



 0,
 0,
 0L,
 0L,
 &szENBConfigUpdTkn[0],
 0
};
 CmPAsnElmDef szENBConfigUpd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztENBConfigUpd),
 &flagSz3M,
 0,
 (U8 *)(&szENBConfigUpdspec),
 0L
};
 CmPAsnElmDef *sz_ValueENBConfigUpdAckgIEsClsInst[] =
{
 &szCriticalityDiag
};
 U32 sz_ValueENBConfigUpdAckgIEsClsInstId[] =
{
 58
};
SzMsgConInf szENBConfigUpdAckgIEsConInf =
{
 {
  { 58, 1, 0x1 }
 },
 1,
 0
};
 CmPAsnClassInfo sz_ValueENBConfigUpdAckgIEsClsInfo =
{
 1,
 &sz_ValueENBConfigUpdAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBConfigUpdAckgIEsClsSpec =
{



 &sz_ValueENBConfigUpdAckgIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueENBConfigUpdAckgIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueENBConfigUpdAckgIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueENBConfigUpdAckgIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueENBConfigUpdAckgIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ENBConfigUpdAckgIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueENBConfigUpdAckgIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBConfigUpdAckgIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ENBConfigUpdAckgIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ENBConfigUpdAckgIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ENBConfigUpdAckgIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ENBConfigUpdAckgIEsspec),
 0L
};


 S16 szProtIE_Cont_ENBConfigUpdAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ENBConfigUpdAckgIEs *protIe = 0L;
 SztProtIE_Field_ENBConfigUpdAckgIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ENBConfigUpdAckgIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ENBConfigUpdAckgIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szENBConfigUpdAckgIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBConfigUpdAckgIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ENBConfigUpdAckgIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ENBConfigUpdAckgIEs),
 &flagSz3M,
 szProtIE_Cont_ENBConfigUpdAckgIEsValidate,
 (U8 *) (&szProtIE_Cont_ENBConfigUpdAckgIEsspec),
 0L
};
 CmPAsnElmDef *szENBConfigUpdAckgTkn[] =
{
 &szProtIE_Cont_ENBConfigUpdAckgIEs,
  &szProtIE_Field_ENBConfigUpdAckgIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szENBConfigUpdAckgspec =
{



 0,
 0,
 0L,
 0L,
 &szENBConfigUpdAckgTkn[0],
 0
};
 CmPAsnElmDef szENBConfigUpdAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztENBConfigUpdAckg),
 &flagSz3M,
 0,
 (U8 *)(&szENBConfigUpdAckgspec),
 0L
};
 CmPAsnElmDef *sz_ValueENBConfigUpdFailIEsClsInst[] =
{
 &szCause,
 &szTimeToWait,
 &szCriticalityDiag
};
 U32 sz_ValueENBConfigUpdFailIEsClsInstId[] =
{
 2,
 65,
 58
};
SzMsgConInf szENBConfigUpdFailIEsConInf =
{
 {
  { 2, 1, 0x2 },
  { 65, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 3,
 1
};
 CmPAsnClassInfo sz_ValueENBConfigUpdFailIEsClsInfo =
{
 3,
 &sz_ValueENBConfigUpdFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBConfigUpdFailIEsClsSpec =
{



 &sz_ValueENBConfigUpdFailIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueENBConfigUpdFailIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueENBConfigUpdFailIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueENBConfigUpdFailIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueENBConfigUpdFailIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ENBConfigUpdFailIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueENBConfigUpdFailIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBConfigUpdFailIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ENBConfigUpdFailIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ENBConfigUpdFailIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ENBConfigUpdFailIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ENBConfigUpdFailIEsspec),
 0L
};


 S16 szProtIE_Cont_ENBConfigUpdFailIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ENBConfigUpdFailIEs *protIe = 0L;
 SztProtIE_Field_ENBConfigUpdFailIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ENBConfigUpdFailIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ENBConfigUpdFailIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szENBConfigUpdFailIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBConfigUpdFailIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ENBConfigUpdFailIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ENBConfigUpdFailIEs),
 &flagSz3M,
 szProtIE_Cont_ENBConfigUpdFailIEsValidate,
 (U8 *) (&szProtIE_Cont_ENBConfigUpdFailIEsspec),
 0L
};
 CmPAsnElmDef *szENBConfigUpdFailTkn[] =
{
 &szProtIE_Cont_ENBConfigUpdFailIEs,
  &szProtIE_Field_ENBConfigUpdFailIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szENBConfigUpdFailspec =
{



 0,
 0,
 0L,
 0L,
 &szENBConfigUpdFailTkn[0],
 0
};
 CmPAsnElmDef szENBConfigUpdFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztENBConfigUpdFail),
 &flagSz3M,
 0,
 (U8 *)(&szENBConfigUpdFailspec),
 0L
};
 CmPAsnElmDef *sz_ValueMMEConfigUpdIEsClsInst[] =
{
 &szMMEname,
 &szSrvdGUMMEIs,
  &szSrvdGUMMEIsItem,
  &szConstTerm,
 &szRelativeMMECapacity
};
 U32 sz_ValueMMEConfigUpdIEsClsInstId[] =
{
 61,
 105,
  0xffffffff,
  0xffffffff,
 87
};
SzMsgConInf szMMEConfigUpdIEsConInf =
{
 {
  { 61, 1, 0x1 },
  { 105, 0, 0x1 },
  { 87, 0, 0x1 }
 },
 3,
 0
};
 CmPAsnClassInfo sz_ValueMMEConfigUpdIEsClsInfo =
{
 5,
 &sz_ValueMMEConfigUpdIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEConfigUpdIEsClsSpec =
{



 &sz_ValueMMEConfigUpdIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueMMEConfigUpdIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueMMEConfigUpdIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueMMEConfigUpdIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueMMEConfigUpdIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_MMEConfigUpdIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueMMEConfigUpdIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEConfigUpdIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_MMEConfigUpdIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_MMEConfigUpdIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_MMEConfigUpdIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_MMEConfigUpdIEsspec),
 0L
};


 S16 szProtIE_Cont_MMEConfigUpdIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_MMEConfigUpdIEs *protIe = 0L;
 SztProtIE_Field_MMEConfigUpdIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_MMEConfigUpdIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_MMEConfigUpdIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szMMEConfigUpdIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEConfigUpdIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_MMEConfigUpdIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_MMEConfigUpdIEs),
 &flagSz3M,
 szProtIE_Cont_MMEConfigUpdIEsValidate,
 (U8 *) (&szProtIE_Cont_MMEConfigUpdIEsspec),
 0L
};
 CmPAsnElmDef *szMMEConfigUpdTkn[] =
{
 &szProtIE_Cont_MMEConfigUpdIEs,
  &szProtIE_Field_MMEConfigUpdIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szMMEConfigUpdspec =
{



 0,
 0,
 0L,
 0L,
 &szMMEConfigUpdTkn[0],
 0
};
 CmPAsnElmDef szMMEConfigUpd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztMMEConfigUpd),
 &flagSz3M,
 0,
 (U8 *)(&szMMEConfigUpdspec),
 0L
};
 CmPAsnElmDef *sz_ValueMMEConfigUpdAckgIEsClsInst[] =
{
 &szCriticalityDiag
};
 U32 sz_ValueMMEConfigUpdAckgIEsClsInstId[] =
{
 58
};
SzMsgConInf szMMEConfigUpdAckgIEsConInf =
{
 {
  { 58, 1, 0x1 }
 },
 1,
 0
};
 CmPAsnClassInfo sz_ValueMMEConfigUpdAckgIEsClsInfo =
{
 1,
 &sz_ValueMMEConfigUpdAckgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEConfigUpdAckgIEsClsSpec =
{



 &sz_ValueMMEConfigUpdAckgIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueMMEConfigUpdAckgIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueMMEConfigUpdAckgIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueMMEConfigUpdAckgIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueMMEConfigUpdAckgIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_MMEConfigUpdAckgIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueMMEConfigUpdAckgIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEConfigUpdAckgIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_MMEConfigUpdAckgIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_MMEConfigUpdAckgIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_MMEConfigUpdAckgIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_MMEConfigUpdAckgIEsspec),
 0L
};


 S16 szProtIE_Cont_MMEConfigUpdAckgIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_MMEConfigUpdAckgIEs *protIe = 0L;
 SztProtIE_Field_MMEConfigUpdAckgIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_MMEConfigUpdAckgIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_MMEConfigUpdAckgIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szMMEConfigUpdAckgIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEConfigUpdAckgIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_MMEConfigUpdAckgIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_MMEConfigUpdAckgIEs),
 &flagSz3M,
 szProtIE_Cont_MMEConfigUpdAckgIEsValidate,
 (U8 *) (&szProtIE_Cont_MMEConfigUpdAckgIEsspec),
 0L
};
 CmPAsnElmDef *szMMEConfigUpdAckgTkn[] =
{
 &szProtIE_Cont_MMEConfigUpdAckgIEs,
  &szProtIE_Field_MMEConfigUpdAckgIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szMMEConfigUpdAckgspec =
{



 0,
 0,
 0L,
 0L,
 &szMMEConfigUpdAckgTkn[0],
 0
};
 CmPAsnElmDef szMMEConfigUpdAckg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztMMEConfigUpdAckg),
 &flagSz3M,
 0,
 (U8 *)(&szMMEConfigUpdAckgspec),
 0L
};
 CmPAsnElmDef *sz_ValueMMEConfigUpdFailIEsClsInst[] =
{
 &szCause,
 &szTimeToWait,
 &szCriticalityDiag
};
 U32 sz_ValueMMEConfigUpdFailIEsClsInstId[] =
{
 2,
 65,
 58
};
SzMsgConInf szMMEConfigUpdFailIEsConInf =
{
 {
  { 2, 1, 0x2 },
  { 65, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 3,
 1
};
 CmPAsnClassInfo sz_ValueMMEConfigUpdFailIEsClsInfo =
{
 3,
 &sz_ValueMMEConfigUpdFailIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEConfigUpdFailIEsClsSpec =
{



 &sz_ValueMMEConfigUpdFailIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueMMEConfigUpdFailIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueMMEConfigUpdFailIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueMMEConfigUpdFailIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueMMEConfigUpdFailIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_MMEConfigUpdFailIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueMMEConfigUpdFailIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEConfigUpdFailIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_MMEConfigUpdFailIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_MMEConfigUpdFailIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_MMEConfigUpdFailIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_MMEConfigUpdFailIEsspec),
 0L
};


 S16 szProtIE_Cont_MMEConfigUpdFailIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_MMEConfigUpdFailIEs *protIe = 0L;
 SztProtIE_Field_MMEConfigUpdFailIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_MMEConfigUpdFailIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_MMEConfigUpdFailIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szMMEConfigUpdFailIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEConfigUpdFailIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_MMEConfigUpdFailIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_MMEConfigUpdFailIEs),
 &flagSz3M,
 szProtIE_Cont_MMEConfigUpdFailIEsValidate,
 (U8 *) (&szProtIE_Cont_MMEConfigUpdFailIEsspec),
 0L
};
 CmPAsnElmDef *szMMEConfigUpdFailTkn[] =
{
 &szProtIE_Cont_MMEConfigUpdFailIEs,
  &szProtIE_Field_MMEConfigUpdFailIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szMMEConfigUpdFailspec =
{



 0,
 0,
 0L,
 0L,
 &szMMEConfigUpdFailTkn[0],
 0
};
 CmPAsnElmDef szMMEConfigUpdFail =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztMMEConfigUpdFail),
 &flagSz3M,
 0,
 (U8 *)(&szMMEConfigUpdFailspec),
 0L
};
 CmPAsnElmDef *sz_ValueDlnkS1cdma2000tunnelingIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szProtIE_ContLst_E_RABDataFwdingItemIEs,
  &szProtIE_Field_E_RABDataFwdingItemIEs,
  &szConstTerm,
 &szCdma2000HOStatus,
 &szCdma2000RATTyp,
 &szCdma2000PDU
};
 U32 sz_ValueDlnkS1cdma2000tunnelingIEsClsInstId[] =
{
 0,
 8,
 12,
  0xffffffff,
  0xffffffff,
 83,
 71,
 70
};
SzMsgConInf szDlnkS1cdma2000tunnelingIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 12, 1, 0x1 },
  { 83, 1, 0x1 },
  { 71, 0, 0x2 },
  { 70, 0, 0x2 }
 },
 6,
 4
};
 CmPAsnClassInfo sz_ValueDlnkS1cdma2000tunnelingIEsClsInfo =
{
 8,
 &sz_ValueDlnkS1cdma2000tunnelingIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueDlnkS1cdma2000tunnelingIEsClsSpec =
{



 &sz_ValueDlnkS1cdma2000tunnelingIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueDlnkS1cdma2000tunnelingIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueDlnkS1cdma2000tunnelingIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueDlnkS1cdma2000tunnelingIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueDlnkS1cdma2000tunnelingIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_DlnkS1cdma2000tunnelingIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueDlnkS1cdma2000tunnelingIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_DlnkS1cdma2000tunnelingIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_DlnkS1cdma2000tunnelingIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_DlnkS1cdma2000tunnelingIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_DlnkS1cdma2000tunnelingIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_DlnkS1cdma2000tunnelingIEsspec),
 0L
};


 S16 szProtIE_Cont_DlnkS1cdma2000tunnelingIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *protIe = 0L;
 SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_DlnkS1cdma2000tunnelingIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szDlnkS1cdma2000tunnelingIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_DlnkS1cdma2000tunnelingIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_DlnkS1cdma2000tunnelingIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs),
 &flagSz3M,
 szProtIE_Cont_DlnkS1cdma2000tunnelingIEsValidate,
 (U8 *) (&szProtIE_Cont_DlnkS1cdma2000tunnelingIEsspec),
 0L
};
 CmPAsnElmDef *szDlnkS1cdma2000tunnelingTkn[] =
{
 &szProtIE_Cont_DlnkS1cdma2000tunnelingIEs,
  &szProtIE_Field_DlnkS1cdma2000tunnelingIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szDlnkS1cdma2000tunnelingspec =
{



 0,
 0,
 0L,
 0L,
 &szDlnkS1cdma2000tunnelingTkn[0],
 0
};
 CmPAsnElmDef szDlnkS1cdma2000tunneling =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztDlnkS1cdma2000tunneling),
 &flagSz3M,
 0,
 (U8 *)(&szDlnkS1cdma2000tunnelingspec),
 0L
};
 CmPAsnElmDef *sz_ValueUlnkS1cdma2000tunnelingIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCdma2000RATTyp,
 &szCdma2000SectorID,
 &szCdma2000HOReqdInd,
 &szCdma2000OneXSRVCCInfo,
 &szCdma2000OneXRAND,
 &szCdma2000PDU,
 &szEUTRANRoundTripDelayEstimationInfo
};
 U32 sz_ValueUlnkS1cdma2000tunnelingIEsClsInstId[] =
{
 0,
 8,
 71,
 72,
 84,
 102,
 97,
 70,
 140
};
SzMsgConInf szUlnkS1cdma2000tunnelingIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 71, 0, 0x2 },
  { 72, 0, 0x2 },
  { 84, 1, 0x1 },
  { 102, 0, 0x1 },
  { 97, 0, 0x1 },
  { 70, 0, 0x2 },
  { 140, 1, 0x1 }
 },
 9,
 5
};
 CmPAsnClassInfo sz_ValueUlnkS1cdma2000tunnelingIEsClsInfo =
{
 9,
 &sz_ValueUlnkS1cdma2000tunnelingIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUlnkS1cdma2000tunnelingIEsClsSpec =
{



 &sz_ValueUlnkS1cdma2000tunnelingIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUlnkS1cdma2000tunnelingIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUlnkS1cdma2000tunnelingIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUlnkS1cdma2000tunnelingIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUlnkS1cdma2000tunnelingIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UlnkS1cdma2000tunnelingIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUlnkS1cdma2000tunnelingIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UlnkS1cdma2000tunnelingIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UlnkS1cdma2000tunnelingIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UlnkS1cdma2000tunnelingIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UlnkS1cdma2000tunnelingIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UlnkS1cdma2000tunnelingIEsspec),
 0L
};


 S16 szProtIE_Cont_UlnkS1cdma2000tunnelingIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *protIe = 0L;
 SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UlnkS1cdma2000tunnelingIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUlnkS1cdma2000tunnelingIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UlnkS1cdma2000tunnelingIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UlnkS1cdma2000tunnelingIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs),
 &flagSz3M,
 szProtIE_Cont_UlnkS1cdma2000tunnelingIEsValidate,
 (U8 *) (&szProtIE_Cont_UlnkS1cdma2000tunnelingIEsspec),
 0L
};
 CmPAsnElmDef *szUlnkS1cdma2000tunnelingTkn[] =
{
 &szProtIE_Cont_UlnkS1cdma2000tunnelingIEs,
  &szProtIE_Field_UlnkS1cdma2000tunnelingIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUlnkS1cdma2000tunnelingspec =
{



 0,
 0,
 0L,
 0L,
 &szUlnkS1cdma2000tunnelingTkn[0],
 0
};
 CmPAsnElmDef szUlnkS1cdma2000tunneling =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUlnkS1cdma2000tunneling),
 &flagSz3M,
 0,
 (U8 *)(&szUlnkS1cdma2000tunnelingspec),
 0L
};
 CmPAsnElmDef *sz_ValueUECapbltyInfoIndIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szUERadioCapblty
};
 U32 sz_ValueUECapbltyInfoIndIEsClsInstId[] =
{
 0,
 8,
 74
};
SzMsgConInf szUECapbltyInfoIndIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 74, 1, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueUECapbltyInfoIndIEsClsInfo =
{
 3,
 &sz_ValueUECapbltyInfoIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUECapbltyInfoIndIEsClsSpec =
{



 &sz_ValueUECapbltyInfoIndIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUECapbltyInfoIndIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUECapbltyInfoIndIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUECapbltyInfoIndIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUECapbltyInfoIndIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UECapbltyInfoIndIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUECapbltyInfoIndIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UECapbltyInfoIndIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UECapbltyInfoIndIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UECapbltyInfoIndIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UECapbltyInfoIndIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UECapbltyInfoIndIEsspec),
 0L
};


 S16 szProtIE_Cont_UECapbltyInfoIndIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UECapbltyInfoIndIEs *protIe = 0L;
 SztProtIE_Field_UECapbltyInfoIndIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UECapbltyInfoIndIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UECapbltyInfoIndIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUECapbltyInfoIndIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UECapbltyInfoIndIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UECapbltyInfoIndIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UECapbltyInfoIndIEs),
 &flagSz3M,
 szProtIE_Cont_UECapbltyInfoIndIEsValidate,
 (U8 *) (&szProtIE_Cont_UECapbltyInfoIndIEsspec),
 0L
};
 CmPAsnElmDef *szUECapbltyInfoIndTkn[] =
{
 &szProtIE_Cont_UECapbltyInfoIndIEs,
  &szProtIE_Field_UECapbltyInfoIndIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUECapbltyInfoIndspec =
{



 0,
 0,
 0L,
 0L,
 &szUECapbltyInfoIndTkn[0],
 0
};
 CmPAsnElmDef szUECapbltyInfoInd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUECapbltyInfoInd),
 &flagSz3M,
 0,
 (U8 *)(&szUECapbltyInfoIndspec),
 0L
};
 CmPAsnElmDef *sz_ValueENBStatusTfrIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szENB_StatusTfr_TprntCont
};
 U32 sz_ValueENBStatusTfrIEsClsInstId[] =
{
 0,
 8,
 90
};
SzMsgConInf szENBStatusTfrIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 90, 0, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueENBStatusTfrIEsClsInfo =
{
 3,
 &sz_ValueENBStatusTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBStatusTfrIEsClsSpec =
{



 &sz_ValueENBStatusTfrIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueENBStatusTfrIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueENBStatusTfrIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueENBStatusTfrIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueENBStatusTfrIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ENBStatusTfrIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueENBStatusTfrIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBStatusTfrIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ENBStatusTfrIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ENBStatusTfrIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ENBStatusTfrIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ENBStatusTfrIEsspec),
 0L
};


 S16 szProtIE_Cont_ENBStatusTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ENBStatusTfrIEs *protIe = 0L;
 SztProtIE_Field_ENBStatusTfrIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ENBStatusTfrIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ENBStatusTfrIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szENBStatusTfrIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBStatusTfrIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ENBStatusTfrIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ENBStatusTfrIEs),
 &flagSz3M,
 szProtIE_Cont_ENBStatusTfrIEsValidate,
 (U8 *) (&szProtIE_Cont_ENBStatusTfrIEsspec),
 0L
};
 CmPAsnElmDef *szENBStatusTfrTkn[] =
{
 &szProtIE_Cont_ENBStatusTfrIEs,
  &szProtIE_Field_ENBStatusTfrIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szENBStatusTfrspec =
{



 0,
 0,
 0L,
 0L,
 &szENBStatusTfrTkn[0],
 0
};
 CmPAsnElmDef szENBStatusTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztENBStatusTfr),
 &flagSz3M,
 0,
 (U8 *)(&szENBStatusTfrspec),
 0L
};
 CmPAsnElmDef *sz_ValueMMEStatusTfrIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szENB_StatusTfr_TprntCont
};
 U32 sz_ValueMMEStatusTfrIEsClsInstId[] =
{
 0,
 8,
 90
};
SzMsgConInf szMMEStatusTfrIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 90, 0, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueMMEStatusTfrIEsClsInfo =
{
 3,
 &sz_ValueMMEStatusTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEStatusTfrIEsClsSpec =
{



 &sz_ValueMMEStatusTfrIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueMMEStatusTfrIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueMMEStatusTfrIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueMMEStatusTfrIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueMMEStatusTfrIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_MMEStatusTfrIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueMMEStatusTfrIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEStatusTfrIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_MMEStatusTfrIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_MMEStatusTfrIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_MMEStatusTfrIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_MMEStatusTfrIEsspec),
 0L
};


 S16 szProtIE_Cont_MMEStatusTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_MMEStatusTfrIEs *protIe = 0L;
 SztProtIE_Field_MMEStatusTfrIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_MMEStatusTfrIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_MMEStatusTfrIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szMMEStatusTfrIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEStatusTfrIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_MMEStatusTfrIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_MMEStatusTfrIEs),
 &flagSz3M,
 szProtIE_Cont_MMEStatusTfrIEsValidate,
 (U8 *) (&szProtIE_Cont_MMEStatusTfrIEsspec),
 0L
};
 CmPAsnElmDef *szMMEStatusTfrTkn[] =
{
 &szProtIE_Cont_MMEStatusTfrIEs,
  &szProtIE_Field_MMEStatusTfrIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szMMEStatusTfrspec =
{



 0,
 0,
 0L,
 0L,
 &szMMEStatusTfrTkn[0],
 0
};
 CmPAsnElmDef szMMEStatusTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztMMEStatusTfr),
 &flagSz3M,
 0,
 (U8 *)(&szMMEStatusTfrspec),
 0L
};
 CmPAsnElmDef *sz_ValueTraceStartIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szTraceActvn
};
 U32 sz_ValueTraceStartIEsClsInstId[] =
{
 0,
 8,
 25
};
SzMsgConInf szTraceStartIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 25, 1, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueTraceStartIEsClsInfo =
{
 3,
 &sz_ValueTraceStartIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueTraceStartIEsClsSpec =
{



 &sz_ValueTraceStartIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueTraceStartIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueTraceStartIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueTraceStartIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueTraceStartIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_TraceStartIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueTraceStartIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_TraceStartIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_TraceStartIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_TraceStartIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_TraceStartIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_TraceStartIEsspec),
 0L
};


 S16 szProtIE_Cont_TraceStartIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_TraceStartIEs *protIe = 0L;
 SztProtIE_Field_TraceStartIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_TraceStartIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_TraceStartIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szTraceStartIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_TraceStartIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_TraceStartIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_TraceStartIEs),
 &flagSz3M,
 szProtIE_Cont_TraceStartIEsValidate,
 (U8 *) (&szProtIE_Cont_TraceStartIEsspec),
 0L
};
 CmPAsnElmDef *szTraceStartTkn[] =
{
 &szProtIE_Cont_TraceStartIEs,
  &szProtIE_Field_TraceStartIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTraceStartspec =
{



 0,
 0,
 0L,
 0L,
 &szTraceStartTkn[0],
 0
};
 CmPAsnElmDef szTraceStart =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTraceStart),
 &flagSz3M,
 0,
 (U8 *)(&szTraceStartspec),
 0L
};
 CmPAsnElmDef *sz_ValueTraceFailIndIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szE_UTRAN_Trace_ID,
 &szCause
};
 U32 sz_ValueTraceFailIndIEsClsInstId[] =
{
 0,
 8,
 86,
 2
};
SzMsgConInf szTraceFailIndIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 86, 1, 0x2 },
  { 2, 1, 0x2 }
 },
 4,
 4
};
 CmPAsnClassInfo sz_ValueTraceFailIndIEsClsInfo =
{
 4,
 &sz_ValueTraceFailIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueTraceFailIndIEsClsSpec =
{



 &sz_ValueTraceFailIndIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueTraceFailIndIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueTraceFailIndIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueTraceFailIndIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueTraceFailIndIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_TraceFailIndIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueTraceFailIndIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_TraceFailIndIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_TraceFailIndIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_TraceFailIndIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_TraceFailIndIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_TraceFailIndIEsspec),
 0L
};


 S16 szProtIE_Cont_TraceFailIndIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_TraceFailIndIEs *protIe = 0L;
 SztProtIE_Field_TraceFailIndIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_TraceFailIndIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_TraceFailIndIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szTraceFailIndIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_TraceFailIndIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_TraceFailIndIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_TraceFailIndIEs),
 &flagSz3M,
 szProtIE_Cont_TraceFailIndIEsValidate,
 (U8 *) (&szProtIE_Cont_TraceFailIndIEsspec),
 0L
};
 CmPAsnElmDef *szTraceFailIndTkn[] =
{
 &szProtIE_Cont_TraceFailIndIEs,
  &szProtIE_Field_TraceFailIndIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szTraceFailIndspec =
{



 0,
 0,
 0L,
 0L,
 &szTraceFailIndTkn[0],
 0
};
 CmPAsnElmDef szTraceFailInd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztTraceFailInd),
 &flagSz3M,
 0,
 (U8 *)(&szTraceFailIndspec),
 0L
};
 CmPAsnElmDef *sz_ValueDeactvTraceIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szE_UTRAN_Trace_ID
};
 U32 sz_ValueDeactvTraceIEsClsInstId[] =
{
 0,
 8,
 86
};
SzMsgConInf szDeactvTraceIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 86, 1, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueDeactvTraceIEsClsInfo =
{
 3,
 &sz_ValueDeactvTraceIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueDeactvTraceIEsClsSpec =
{



 &sz_ValueDeactvTraceIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueDeactvTraceIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueDeactvTraceIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueDeactvTraceIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueDeactvTraceIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_DeactvTraceIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueDeactvTraceIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_DeactvTraceIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_DeactvTraceIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_DeactvTraceIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_DeactvTraceIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_DeactvTraceIEsspec),
 0L
};


 S16 szProtIE_Cont_DeactvTraceIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_DeactvTraceIEs *protIe = 0L;
 SztProtIE_Field_DeactvTraceIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_DeactvTraceIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_DeactvTraceIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szDeactvTraceIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_DeactvTraceIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_DeactvTraceIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_DeactvTraceIEs),
 &flagSz3M,
 szProtIE_Cont_DeactvTraceIEsValidate,
 (U8 *) (&szProtIE_Cont_DeactvTraceIEsspec),
 0L
};
 CmPAsnElmDef *szDeactvTraceTkn[] =
{
 &szProtIE_Cont_DeactvTraceIEs,
  &szProtIE_Field_DeactvTraceIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szDeactvTracespec =
{



 0,
 0,
 0L,
 0L,
 &szDeactvTraceTkn[0],
 0
};
 CmPAsnElmDef szDeactvTrace =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztDeactvTrace),
 &flagSz3M,
 0,
 (U8 *)(&szDeactvTracespec),
 0L
};
 CmPAsnElmDef *sz_ValueCellTrafficTraceIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szE_UTRAN_Trace_ID,
 &szEUTRAN_CGI,
 &szTportLyrAddr,
 &szPrivacyIndicator
};
 U32 sz_ValueCellTrafficTraceIEsClsInstId[] =
{
 0,
 8,
 86,
 100,
 131,
 166
};
SzMsgConInf szCellTrafficTraceIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 86, 1, 0x2 },
  { 100, 1, 0x2 },
  { 131, 1, 0x2 },
  { 166, 1, 0x1 }
 },
 6,
 5
};
 CmPAsnClassInfo sz_ValueCellTrafficTraceIEsClsInfo =
{
 6,
 &sz_ValueCellTrafficTraceIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueCellTrafficTraceIEsClsSpec =
{



 &sz_ValueCellTrafficTraceIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueCellTrafficTraceIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueCellTrafficTraceIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueCellTrafficTraceIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueCellTrafficTraceIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_CellTrafficTraceIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueCellTrafficTraceIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_CellTrafficTraceIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_CellTrafficTraceIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_CellTrafficTraceIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_CellTrafficTraceIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_CellTrafficTraceIEsspec),
 0L
};


 S16 szProtIE_Cont_CellTrafficTraceIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_CellTrafficTraceIEs *protIe = 0L;
 SztProtIE_Field_CellTrafficTraceIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_CellTrafficTraceIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_CellTrafficTraceIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szCellTrafficTraceIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_CellTrafficTraceIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_CellTrafficTraceIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_CellTrafficTraceIEs),
 &flagSz3M,
 szProtIE_Cont_CellTrafficTraceIEsValidate,
 (U8 *) (&szProtIE_Cont_CellTrafficTraceIEsspec),
 0L
};
 CmPAsnElmDef *szCellTrafficTraceTkn[] =
{
 &szProtIE_Cont_CellTrafficTraceIEs,
  &szProtIE_Field_CellTrafficTraceIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szCellTrafficTracespec =
{



 0,
 0,
 0L,
 0L,
 &szCellTrafficTraceTkn[0],
 0
};
 CmPAsnElmDef szCellTrafficTrace =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztCellTrafficTrace),
 &flagSz3M,
 0,
 (U8 *)(&szCellTrafficTracespec),
 0L
};
 CmPAsnElmDef *sz_ValueLocRprtngCntrlIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szRqstTyp
};
 U32 sz_ValueLocRprtngCntrlIEsClsInstId[] =
{
 0,
 8,
 98
};
SzMsgConInf szLocRprtngCntrlIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 98, 1, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueLocRprtngCntrlIEsClsInfo =
{
 3,
 &sz_ValueLocRprtngCntrlIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueLocRprtngCntrlIEsClsSpec =
{



 &sz_ValueLocRprtngCntrlIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueLocRprtngCntrlIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueLocRprtngCntrlIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueLocRprtngCntrlIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueLocRprtngCntrlIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_LocRprtngCntrlIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueLocRprtngCntrlIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_LocRprtngCntrlIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_LocRprtngCntrlIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_LocRprtngCntrlIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_LocRprtngCntrlIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_LocRprtngCntrlIEsspec),
 0L
};


 S16 szProtIE_Cont_LocRprtngCntrlIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_LocRprtngCntrlIEs *protIe = 0L;
 SztProtIE_Field_LocRprtngCntrlIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_LocRprtngCntrlIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_LocRprtngCntrlIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szLocRprtngCntrlIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_LocRprtngCntrlIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_LocRprtngCntrlIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_LocRprtngCntrlIEs),
 &flagSz3M,
 szProtIE_Cont_LocRprtngCntrlIEsValidate,
 (U8 *) (&szProtIE_Cont_LocRprtngCntrlIEsspec),
 0L
};
 CmPAsnElmDef *szLocRprtngCntrlTkn[] =
{
 &szProtIE_Cont_LocRprtngCntrlIEs,
  &szProtIE_Field_LocRprtngCntrlIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szLocRprtngCntrlspec =
{



 0,
 0,
 0L,
 0L,
 &szLocRprtngCntrlTkn[0],
 0
};
 CmPAsnElmDef szLocRprtngCntrl =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztLocRprtngCntrl),
 &flagSz3M,
 0,
 (U8 *)(&szLocRprtngCntrlspec),
 0L
};
 CmPAsnElmDef *sz_ValueLocRprtngFailIndIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szCause
};
 U32 sz_ValueLocRprtngFailIndIEsClsInstId[] =
{
 0,
 8,
 2
};
SzMsgConInf szLocRprtngFailIndIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 2, 1, 0x2 }
 },
 3,
 3
};
 CmPAsnClassInfo sz_ValueLocRprtngFailIndIEsClsInfo =
{
 3,
 &sz_ValueLocRprtngFailIndIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueLocRprtngFailIndIEsClsSpec =
{



 &sz_ValueLocRprtngFailIndIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueLocRprtngFailIndIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueLocRprtngFailIndIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueLocRprtngFailIndIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueLocRprtngFailIndIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_LocRprtngFailIndIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueLocRprtngFailIndIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_LocRprtngFailIndIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_LocRprtngFailIndIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_LocRprtngFailIndIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_LocRprtngFailIndIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_LocRprtngFailIndIEsspec),
 0L
};


 S16 szProtIE_Cont_LocRprtngFailIndIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_LocRprtngFailIndIEs *protIe = 0L;
 SztProtIE_Field_LocRprtngFailIndIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_LocRprtngFailIndIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_LocRprtngFailIndIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szLocRprtngFailIndIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_LocRprtngFailIndIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_LocRprtngFailIndIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_LocRprtngFailIndIEs),
 &flagSz3M,
 szProtIE_Cont_LocRprtngFailIndIEsValidate,
 (U8 *) (&szProtIE_Cont_LocRprtngFailIndIEsspec),
 0L
};
 CmPAsnElmDef *szLocRprtngFailIndTkn[] =
{
 &szProtIE_Cont_LocRprtngFailIndIEs,
  &szProtIE_Field_LocRprtngFailIndIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szLocRprtngFailIndspec =
{



 0,
 0,
 0L,
 0L,
 &szLocRprtngFailIndTkn[0],
 0
};
 CmPAsnElmDef szLocRprtngFailInd =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztLocRprtngFailInd),
 &flagSz3M,
 0,
 (U8 *)(&szLocRprtngFailIndspec),
 0L
};
 CmPAsnElmDef *sz_ValueLocReportIEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szEUTRAN_CGI,
 &szTAI,
 &szRqstTyp
};
 U32 sz_ValueLocReportIEsClsInstId[] =
{
 0,
 8,
 100,
 67,
 98
};
SzMsgConInf szLocReportIEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 100, 1, 0x2 },
  { 67, 1, 0x2 },
  { 98, 1, 0x2 }
 },
 5,
 5
};
 CmPAsnClassInfo sz_ValueLocReportIEsClsInfo =
{
 5,
 &sz_ValueLocReportIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueLocReportIEsClsSpec =
{



 &sz_ValueLocReportIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueLocReportIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueLocReportIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueLocReportIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueLocReportIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_LocReportIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueLocReportIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_LocReportIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_LocReportIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_LocReportIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_LocReportIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_LocReportIEsspec),
 0L
};


 S16 szProtIE_Cont_LocReportIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_LocReportIEs *protIe = 0L;
 SztProtIE_Field_LocReportIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_LocReportIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_LocReportIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szLocReportIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_LocReportIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_LocReportIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_LocReportIEs),
 &flagSz3M,
 szProtIE_Cont_LocReportIEsValidate,
 (U8 *) (&szProtIE_Cont_LocReportIEsspec),
 0L
};
 CmPAsnElmDef *szLocReportTkn[] =
{
 &szProtIE_Cont_LocReportIEs,
  &szProtIE_Field_LocReportIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szLocReportspec =
{



 0,
 0,
 0L,
 0L,
 &szLocReportTkn[0],
 0
};
 CmPAsnElmDef szLocReport =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztLocReport),
 &flagSz3M,
 0,
 (U8 *)(&szLocReportspec),
 0L
};
 CmPAsnElmDef *sz_ValueOverloadStartIEsClsInst[] =
{
 &szOverloadResp,
 &szGUMMEILst,
  &szGUMMEI,
  &szConstTerm,
 &szTrafficLoadReductionInd
};
 U32 sz_ValueOverloadStartIEsClsInstId[] =
{
 101,
 154,
  0xffffffff,
  0xffffffff,
 161
};
SzMsgConInf szOverloadStartIEsConInf =
{
 {
  { 101, 0, 0x2 },
  { 154, 1, 0x1 },
  { 161, 1, 0x1 }
 },
 3,
 1
};
 CmPAsnClassInfo sz_ValueOverloadStartIEsClsInfo =
{
 5,
 &sz_ValueOverloadStartIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueOverloadStartIEsClsSpec =
{



 &sz_ValueOverloadStartIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueOverloadStartIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueOverloadStartIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueOverloadStartIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueOverloadStartIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_OverloadStartIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueOverloadStartIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_OverloadStartIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_OverloadStartIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_OverloadStartIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_OverloadStartIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_OverloadStartIEsspec),
 0L
};


 S16 szProtIE_Cont_OverloadStartIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_OverloadStartIEs *protIe = 0L;
 SztProtIE_Field_OverloadStartIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_OverloadStartIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_OverloadStartIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szOverloadStartIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_OverloadStartIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_OverloadStartIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_OverloadStartIEs),
 &flagSz3M,
 szProtIE_Cont_OverloadStartIEsValidate,
 (U8 *) (&szProtIE_Cont_OverloadStartIEsspec),
 0L
};
 CmPAsnElmDef *szOverloadStartTkn[] =
{
 &szProtIE_Cont_OverloadStartIEs,
  &szProtIE_Field_OverloadStartIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szOverloadStartspec =
{



 0,
 0,
 0L,
 0L,
 &szOverloadStartTkn[0],
 0
};
 CmPAsnElmDef szOverloadStart =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztOverloadStart),
 &flagSz3M,
 0,
 (U8 *)(&szOverloadStartspec),
 0L
};
 CmPAsnElmDef *sz_ValueOverloadStopIEsClsInst[] =
{
 &szGUMMEILst,
  &szGUMMEI,
  &szConstTerm,

};
 U32 sz_ValueOverloadStopIEsClsInstId[] =
{
 154,
  0xffffffff,
  0xffffffff
};
SzMsgConInf szOverloadStopIEsConInf =
{
 {
  { 154, 1, 0x1 }
 },
 1,
 0
};
 CmPAsnClassInfo sz_ValueOverloadStopIEsClsInfo =
{
 3,
 &sz_ValueOverloadStopIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueOverloadStopIEsClsSpec =
{



 &sz_ValueOverloadStopIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueOverloadStopIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueOverloadStopIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueOverloadStopIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueOverloadStopIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_OverloadStopIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueOverloadStopIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_OverloadStopIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_OverloadStopIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_OverloadStopIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_OverloadStopIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_OverloadStopIEsspec),
 0L
};


 S16 szProtIE_Cont_OverloadStopIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_OverloadStopIEs *protIe = 0L;
 SztProtIE_Field_OverloadStopIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_OverloadStopIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_OverloadStopIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szOverloadStopIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_OverloadStopIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_OverloadStopIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_OverloadStopIEs),
 &flagSz3M,
 szProtIE_Cont_OverloadStopIEsValidate,
 (U8 *) (&szProtIE_Cont_OverloadStopIEsspec),
 0L
};
 CmPAsnElmDef *szOverloadStopTkn[] =
{
 &szProtIE_Cont_OverloadStopIEs,
  &szProtIE_Field_OverloadStopIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szOverloadStopspec =
{



 0,
 0,
 0L,
 0L,
 &szOverloadStopTkn[0],
 0
};
 CmPAsnElmDef szOverloadStop =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztOverloadStop),
 &flagSz3M,
 0,
 (U8 *)(&szOverloadStopspec),
 0L
};
 CmPAsnElmDef *sz_ValueWriteReplaceWarningRqstIEsClsInst[] =
{
 &szMsgIdentifier,
 &szSerialNumber,
 &szWarningAreaLst,
 &szRepetitionPeriod,
 &szExtendedRepetitionPeriod,
 &szNumberofBroadcastRqst,
 &szWarningTyp,
 &szWarningSecurInfo,
 &szDataCodingScheme,
 &szWarningMsgContents,
 &szConcurrentWarningMsgIndicator
};
 U32 sz_ValueWriteReplaceWarningRqstIEsClsInstId[] =
{
 111,
 112,
 113,
 114,
 144,
 115,
 116,
 117,
 118,
 119,
 142
};
SzMsgConInf szWriteReplaceWarningRqstIEsConInf =
{
 {
  { 111, 0, 0x2 },
  { 112, 0, 0x2 },
  { 113, 1, 0x1 },
  { 114, 0, 0x2 },
  { 144, 0, 0x1 },
  { 115, 0, 0x2 },
  { 116, 1, 0x1 },
  { 117, 1, 0x1 },
  { 118, 1, 0x1 },
  { 119, 1, 0x1 },
  { 142, 0, 0x1 }
 },
 11,
 4
};
 CmPAsnClassInfo sz_ValueWriteReplaceWarningRqstIEsClsInfo =
{
 11,
 &sz_ValueWriteReplaceWarningRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueWriteReplaceWarningRqstIEsClsSpec =
{



 &sz_ValueWriteReplaceWarningRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueWriteReplaceWarningRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueWriteReplaceWarningRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueWriteReplaceWarningRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueWriteReplaceWarningRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_WriteReplaceWarningRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueWriteReplaceWarningRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_WriteReplaceWarningRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_WriteReplaceWarningRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_WriteReplaceWarningRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_WriteReplaceWarningRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_WriteReplaceWarningRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_WriteReplaceWarningRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_WriteReplaceWarningRqstIEs *protIe = 0L;
 SztProtIE_Field_WriteReplaceWarningRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_WriteReplaceWarningRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_WriteReplaceWarningRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szWriteReplaceWarningRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_WriteReplaceWarningRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_WriteReplaceWarningRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_WriteReplaceWarningRqstIEs),
 &flagSz3M,
 szProtIE_Cont_WriteReplaceWarningRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_WriteReplaceWarningRqstIEsspec),
 0L
};
 CmPAsnElmDef *szWriteReplaceWarningRqstTkn[] =
{
 &szProtIE_Cont_WriteReplaceWarningRqstIEs,
  &szProtIE_Field_WriteReplaceWarningRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szWriteReplaceWarningRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szWriteReplaceWarningRqstTkn[0],
 0
};
 CmPAsnElmDef szWriteReplaceWarningRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztWriteReplaceWarningRqst),
 &flagSz3M,
 0,
 (U8 *)(&szWriteReplaceWarningRqstspec),
 0L
};
 CmPAsnElmDef *sz_ValueWriteReplaceWarningRespIEsClsInst[] =
{
 &szMsgIdentifier,
 &szSerialNumber,
 &szBroadcastCompletedAreaLst,
 &szCriticalityDiag
};
 U32 sz_ValueWriteReplaceWarningRespIEsClsInstId[] =
{
 111,
 112,
 120,
 58
};
SzMsgConInf szWriteReplaceWarningRespIEsConInf =
{
 {
  { 111, 0, 0x2 },
  { 112, 0, 0x2 },
  { 120, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 4,
 2
};
 CmPAsnClassInfo sz_ValueWriteReplaceWarningRespIEsClsInfo =
{
 4,
 &sz_ValueWriteReplaceWarningRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueWriteReplaceWarningRespIEsClsSpec =
{



 &sz_ValueWriteReplaceWarningRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueWriteReplaceWarningRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueWriteReplaceWarningRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueWriteReplaceWarningRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueWriteReplaceWarningRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_WriteReplaceWarningRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueWriteReplaceWarningRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_WriteReplaceWarningRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_WriteReplaceWarningRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_WriteReplaceWarningRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_WriteReplaceWarningRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_WriteReplaceWarningRespIEsspec),
 0L
};


 S16 szProtIE_Cont_WriteReplaceWarningRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_WriteReplaceWarningRespIEs *protIe = 0L;
 SztProtIE_Field_WriteReplaceWarningRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_WriteReplaceWarningRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_WriteReplaceWarningRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szWriteReplaceWarningRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_WriteReplaceWarningRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_WriteReplaceWarningRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_WriteReplaceWarningRespIEs),
 &flagSz3M,
 szProtIE_Cont_WriteReplaceWarningRespIEsValidate,
 (U8 *) (&szProtIE_Cont_WriteReplaceWarningRespIEsspec),
 0L
};
 CmPAsnElmDef *szWriteReplaceWarningRespTkn[] =
{
 &szProtIE_Cont_WriteReplaceWarningRespIEs,
  &szProtIE_Field_WriteReplaceWarningRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szWriteReplaceWarningRespspec =
{



 0,
 0,
 0L,
 0L,
 &szWriteReplaceWarningRespTkn[0],
 0
};
 CmPAsnElmDef szWriteReplaceWarningResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztWriteReplaceWarningResp),
 &flagSz3M,
 0,
 (U8 *)(&szWriteReplaceWarningRespspec),
 0L
};
 CmPAsnElmDef *szInter_SystemInformTfrTypTkn[] =
{
 &szRIMTfr,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szInter_SystemInformTfrTypspec =
{



 1,
 0,
 &szInter_SystemInformTfrTypTkn[0]
};
CmPAsnElmDef szInter_SystemInformTfrTyp =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztInter_SystemInformTfrTyp),
 &flagSz3M,
 0L,
 (U8 *)(&szInter_SystemInformTfrTypspec),
 0L
};
 CmPAsnElmDef *sz_ValueENBDirectInformTfrIEsClsInst[] =
{
 &szInter_SystemInformTfrTyp
};
 U32 sz_ValueENBDirectInformTfrIEsClsInstId[] =
{
 121
};
SzMsgConInf szENBDirectInformTfrIEsConInf =
{
 {
  { 121, 0, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueENBDirectInformTfrIEsClsInfo =
{
 1,
 &sz_ValueENBDirectInformTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBDirectInformTfrIEsClsSpec =
{



 &sz_ValueENBDirectInformTfrIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueENBDirectInformTfrIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueENBDirectInformTfrIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueENBDirectInformTfrIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueENBDirectInformTfrIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ENBDirectInformTfrIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueENBDirectInformTfrIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBDirectInformTfrIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ENBDirectInformTfrIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ENBDirectInformTfrIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ENBDirectInformTfrIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ENBDirectInformTfrIEsspec),
 0L
};


 S16 szProtIE_Cont_ENBDirectInformTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ENBDirectInformTfrIEs *protIe = 0L;
 SztProtIE_Field_ENBDirectInformTfrIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ENBDirectInformTfrIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ENBDirectInformTfrIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szENBDirectInformTfrIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBDirectInformTfrIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ENBDirectInformTfrIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ENBDirectInformTfrIEs),
 &flagSz3M,
 szProtIE_Cont_ENBDirectInformTfrIEsValidate,
 (U8 *) (&szProtIE_Cont_ENBDirectInformTfrIEsspec),
 0L
};
 CmPAsnElmDef *szENBDirectInformTfrTkn[] =
{
 &szProtIE_Cont_ENBDirectInformTfrIEs,
  &szProtIE_Field_ENBDirectInformTfrIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szENBDirectInformTfrspec =
{



 0,
 0,
 0L,
 0L,
 &szENBDirectInformTfrTkn[0],
 0
};
 CmPAsnElmDef szENBDirectInformTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztENBDirectInformTfr),
 &flagSz3M,
 0,
 (U8 *)(&szENBDirectInformTfrspec),
 0L
};
 CmPAsnElmDef *sz_ValueMMEDirectInformTfrIEsClsInst[] =
{
 &szInter_SystemInformTfrTyp
};
 U32 sz_ValueMMEDirectInformTfrIEsClsInstId[] =
{
 122
};
SzMsgConInf szMMEDirectInformTfrIEsConInf =
{
 {
  { 122, 0, 0x2 }
 },
 1,
 1
};
 CmPAsnClassInfo sz_ValueMMEDirectInformTfrIEsClsInfo =
{
 1,
 &sz_ValueMMEDirectInformTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEDirectInformTfrIEsClsSpec =
{



 &sz_ValueMMEDirectInformTfrIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueMMEDirectInformTfrIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueMMEDirectInformTfrIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueMMEDirectInformTfrIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueMMEDirectInformTfrIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_MMEDirectInformTfrIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueMMEDirectInformTfrIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEDirectInformTfrIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_MMEDirectInformTfrIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_MMEDirectInformTfrIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_MMEDirectInformTfrIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_MMEDirectInformTfrIEsspec),
 0L
};


 S16 szProtIE_Cont_MMEDirectInformTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_MMEDirectInformTfrIEs *protIe = 0L;
 SztProtIE_Field_MMEDirectInformTfrIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_MMEDirectInformTfrIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_MMEDirectInformTfrIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szMMEDirectInformTfrIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEDirectInformTfrIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_MMEDirectInformTfrIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_MMEDirectInformTfrIEs),
 &flagSz3M,
 szProtIE_Cont_MMEDirectInformTfrIEsValidate,
 (U8 *) (&szProtIE_Cont_MMEDirectInformTfrIEsspec),
 0L
};
 CmPAsnElmDef *szMMEDirectInformTfrTkn[] =
{
 &szProtIE_Cont_MMEDirectInformTfrIEs,
  &szProtIE_Field_MMEDirectInformTfrIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szMMEDirectInformTfrspec =
{



 0,
 0,
 0L,
 0L,
 &szMMEDirectInformTfrTkn[0],
 0
};
 CmPAsnElmDef szMMEDirectInformTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztMMEDirectInformTfr),
 &flagSz3M,
 0,
 (U8 *)(&szMMEDirectInformTfrspec),
 0L
};
 CmPAsnElmDef *sz_ValueENBConfigTfrIEsClsInst[] =
{
 &szSONConfigTfr
};
 U32 sz_ValueENBConfigTfrIEsClsInstId[] =
{
 129
};
SzMsgConInf szENBConfigTfrIEsConInf =
{
 {
  { 129, 1, 0x1 }
 },
 1,
 0
};
 CmPAsnClassInfo sz_ValueENBConfigTfrIEsClsInfo =
{
 1,
 &sz_ValueENBConfigTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueENBConfigTfrIEsClsSpec =
{



 &sz_ValueENBConfigTfrIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueENBConfigTfrIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueENBConfigTfrIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueENBConfigTfrIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueENBConfigTfrIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_ENBConfigTfrIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueENBConfigTfrIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_ENBConfigTfrIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_ENBConfigTfrIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_ENBConfigTfrIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_ENBConfigTfrIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_ENBConfigTfrIEsspec),
 0L
};


 S16 szProtIE_Cont_ENBConfigTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_ENBConfigTfrIEs *protIe = 0L;
 SztProtIE_Field_ENBConfigTfrIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_ENBConfigTfrIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_ENBConfigTfrIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szENBConfigTfrIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_ENBConfigTfrIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_ENBConfigTfrIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_ENBConfigTfrIEs),
 &flagSz3M,
 szProtIE_Cont_ENBConfigTfrIEsValidate,
 (U8 *) (&szProtIE_Cont_ENBConfigTfrIEsspec),
 0L
};
 CmPAsnElmDef *szENBConfigTfrTkn[] =
{
 &szProtIE_Cont_ENBConfigTfrIEs,
  &szProtIE_Field_ENBConfigTfrIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szENBConfigTfrspec =
{



 0,
 0,
 0L,
 0L,
 &szENBConfigTfrTkn[0],
 0
};
 CmPAsnElmDef szENBConfigTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztENBConfigTfr),
 &flagSz3M,
 0,
 (U8 *)(&szENBConfigTfrspec),
 0L
};
 CmPAsnElmDef *sz_ValueMMEConfigTfrIEsClsInst[] =
{
 &szSONConfigTfr
};
 U32 sz_ValueMMEConfigTfrIEsClsInstId[] =
{
 130
};
SzMsgConInf szMMEConfigTfrIEsConInf =
{
 {
  { 130, 1, 0x1 }
 },
 1,
 0
};
 CmPAsnClassInfo sz_ValueMMEConfigTfrIEsClsInfo =
{
 1,
 &sz_ValueMMEConfigTfrIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueMMEConfigTfrIEsClsSpec =
{



 &sz_ValueMMEConfigTfrIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueMMEConfigTfrIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueMMEConfigTfrIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueMMEConfigTfrIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueMMEConfigTfrIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_MMEConfigTfrIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueMMEConfigTfrIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_MMEConfigTfrIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_MMEConfigTfrIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_MMEConfigTfrIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_MMEConfigTfrIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_MMEConfigTfrIEsspec),
 0L
};


 S16 szProtIE_Cont_MMEConfigTfrIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_MMEConfigTfrIEs *protIe = 0L;
 SztProtIE_Field_MMEConfigTfrIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_MMEConfigTfrIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_MMEConfigTfrIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szMMEConfigTfrIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_MMEConfigTfrIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_MMEConfigTfrIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_MMEConfigTfrIEs),
 &flagSz3M,
 szProtIE_Cont_MMEConfigTfrIEsValidate,
 (U8 *) (&szProtIE_Cont_MMEConfigTfrIEsspec),
 0L
};
 CmPAsnElmDef *szMMEConfigTfrTkn[] =
{
 &szProtIE_Cont_MMEConfigTfrIEs,
  &szProtIE_Field_MMEConfigTfrIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szMMEConfigTfrspec =
{



 0,
 0,
 0L,
 0L,
 &szMMEConfigTfrTkn[0],
 0
};
 CmPAsnElmDef szMMEConfigTfr =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztMMEConfigTfr),
 &flagSz3M,
 0,
 (U8 *)(&szMMEConfigTfrspec),
 0L
};
 CmPAsnElmDef *sz_ValuePrivMsgIEsClsInst[] =
{
 0L
};
 U32 sz_ValuePrivMsgIEsClsInstId[] =
{
 0xffffffff
};
SzMsgConInf szPrivMsgIEsConInf =
{
 {
  { 0xffffffff, 0x0 }
 },
 0,
 0
};
 CmPAsnClassInfo sz_ValuePrivMsgIEsClsInfo =
{
 0,
 &sz_ValuePrivMsgIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValuePrivMsgIEsClsSpec =
{



 &sz_ValuePrivMsgIEsClsInfo,
 0,
 &sz_ValuePrivMsgIEsClsInst[0],



};
 CmPAsnElmDef sz_ValuePrivMsgIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValuePrivMsgIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValuePrivMsgIEsClsSpec)
};
 CmPAsnElmDef *szPrivIE_Field_PrivMsgIEsTkn[] =
{
 &szPrivIE_ID,
 &szCriticality,
 &sz_ValuePrivMsgIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szPrivIE_Field_PrivMsgIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szPrivIE_Field_PrivMsgIEsTkn[0],
 0
};
 CmPAsnElmDef szPrivIE_Field_PrivMsgIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztPrivIE_Field_PrivMsgIEs),
 &flagSz3M,
 0,
 (U8 *)(&szPrivIE_Field_PrivMsgIEsspec),
 0L
};


 S16 szPrivIE_Cont_PrivMsgIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztPrivIE_Cont_PrivMsgIEs *protIe = 0L;
 SztPrivIE_Field_PrivMsgIEs *member = 0L;

 ;;

 protIe = (SztPrivIE_Cont_PrivMsgIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztPrivIE_Field_PrivMsgIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szPrivMsgIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szPrivIE_Cont_PrivMsgIEsspec =
{



 1,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szPrivIE_Cont_PrivMsgIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztPrivIE_Cont_PrivMsgIEs),
 &flagSz3M,
 szPrivIE_Cont_PrivMsgIEsValidate,
 (U8 *) (&szPrivIE_Cont_PrivMsgIEsspec),
 0L
};
 CmPAsnElmDef *szPrivMsgTkn[] =
{
 &szPrivIE_Cont_PrivMsgIEs,
  &szPrivIE_Field_PrivMsgIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szPrivMsgspec =
{



 0,
 0,
 0L,
 0L,
 &szPrivMsgTkn[0],
 0
};
 CmPAsnElmDef szPrivMsg =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztPrivMsg),
 &flagSz3M,
 0,
 (U8 *)(&szPrivMsgspec),
 0L
};
 CmPAsnElmDef *sz_ValueKillRqstIEsClsInst[] =
{
 &szMsgIdentifier,
 &szSerialNumber,
 &szWarningAreaLst
};
 U32 sz_ValueKillRqstIEsClsInstId[] =
{
 111,
 112,
 113
};
SzMsgConInf szKillRqstIEsConInf =
{
 {
  { 111, 0, 0x2 },
  { 112, 0, 0x2 },
  { 113, 1, 0x1 }
 },
 3,
 2
};
 CmPAsnClassInfo sz_ValueKillRqstIEsClsInfo =
{
 3,
 &sz_ValueKillRqstIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueKillRqstIEsClsSpec =
{



 &sz_ValueKillRqstIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueKillRqstIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueKillRqstIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueKillRqstIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueKillRqstIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_KillRqstIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueKillRqstIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_KillRqstIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_KillRqstIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_KillRqstIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_KillRqstIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_KillRqstIEsspec),
 0L
};


 S16 szProtIE_Cont_KillRqstIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_KillRqstIEs *protIe = 0L;
 SztProtIE_Field_KillRqstIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_KillRqstIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_KillRqstIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szKillRqstIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_KillRqstIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_KillRqstIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_KillRqstIEs),
 &flagSz3M,
 szProtIE_Cont_KillRqstIEsValidate,
 (U8 *) (&szProtIE_Cont_KillRqstIEsspec),
 0L
};
 CmPAsnElmDef *szKillRqstTkn[] =
{
 &szProtIE_Cont_KillRqstIEs,
  &szProtIE_Field_KillRqstIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szKillRqstspec =
{



 0,
 0,
 0L,
 0L,
 &szKillRqstTkn[0],
 0
};
 CmPAsnElmDef szKillRqst =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztKillRqst),
 &flagSz3M,
 0,
 (U8 *)(&szKillRqstspec),
 0L
};
 CmPAsnElmDef *sz_ValueKillRespIEsClsInst[] =
{
 &szMsgIdentifier,
 &szSerialNumber,
 &szBroadcastCancelledAreaLst,
 &szCriticalityDiag
};
 U32 sz_ValueKillRespIEsClsInstId[] =
{
 111,
 112,
 141,
 58
};
SzMsgConInf szKillRespIEsConInf =
{
 {
  { 111, 0, 0x2 },
  { 112, 0, 0x2 },
  { 141, 1, 0x1 },
  { 58, 1, 0x1 }
 },
 4,
 2
};
 CmPAsnClassInfo sz_ValueKillRespIEsClsInfo =
{
 4,
 &sz_ValueKillRespIEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueKillRespIEsClsSpec =
{



 &sz_ValueKillRespIEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueKillRespIEsClsInst[0],



};
 CmPAsnElmDef sz_ValueKillRespIEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueKillRespIEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueKillRespIEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_KillRespIEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueKillRespIEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_KillRespIEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_KillRespIEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_KillRespIEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_KillRespIEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_KillRespIEsspec),
 0L
};


 S16 szProtIE_Cont_KillRespIEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_KillRespIEs *protIe = 0L;
 SztProtIE_Field_KillRespIEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_KillRespIEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_KillRespIEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szKillRespIEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_KillRespIEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_KillRespIEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_KillRespIEs),
 &flagSz3M,
 szProtIE_Cont_KillRespIEsValidate,
 (U8 *) (&szProtIE_Cont_KillRespIEsspec),
 0L
};
 CmPAsnElmDef *szKillRespTkn[] =
{
 &szProtIE_Cont_KillRespIEs,
  &szProtIE_Field_KillRespIEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szKillRespspec =
{



 0,
 0,
 0L,
 0L,
 &szKillRespTkn[0],
 0
};
 CmPAsnElmDef szKillResp =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztKillResp),
 &flagSz3M,
 0,
 (U8 *)(&szKillRespspec),
 0L
};
 CmPAsnElmDef *sz_ValueDlnkUEAssociatedLPPaTport_IEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szRouting_ID,
 &szLPPa_PDU
};
 U32 sz_ValueDlnkUEAssociatedLPPaTport_IEsClsInstId[] =
{
 0,
 8,
 148,
 147
};
SzMsgConInf szDlnkUEAssociatedLPPaTport_IEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 148, 0, 0x2 },
  { 147, 0, 0x2 }
 },
 4,
 4
};
 CmPAsnClassInfo sz_ValueDlnkUEAssociatedLPPaTport_IEsClsInfo =
{
 4,
 &sz_ValueDlnkUEAssociatedLPPaTport_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueDlnkUEAssociatedLPPaTport_IEsClsSpec =
{



 &sz_ValueDlnkUEAssociatedLPPaTport_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueDlnkUEAssociatedLPPaTport_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueDlnkUEAssociatedLPPaTport_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueDlnkUEAssociatedLPPaTport_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_DlnkUEAssociatedLPPaTport_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueDlnkUEAssociatedLPPaTport_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_DlnkUEAssociatedLPPaTport_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_DlnkUEAssociatedLPPaTport_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_DlnkUEAssociatedLPPaTport_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_DlnkUEAssociatedLPPaTport_IEsspec),
 0L
};


 S16 szProtIE_Cont_DlnkUEAssociatedLPPaTport_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs *protIe = 0L;
 SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szDlnkUEAssociatedLPPaTport_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_DlnkUEAssociatedLPPaTport_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs),
 &flagSz3M,
 szProtIE_Cont_DlnkUEAssociatedLPPaTport_IEsValidate,
 (U8 *) (&szProtIE_Cont_DlnkUEAssociatedLPPaTport_IEsspec),
 0L
};
 CmPAsnElmDef *szDlnkUEAssociatedLPPaTportTkn[] =
{
 &szProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs,
  &szProtIE_Field_DlnkUEAssociatedLPPaTport_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szDlnkUEAssociatedLPPaTportspec =
{



 0,
 0,
 0L,
 0L,
 &szDlnkUEAssociatedLPPaTportTkn[0],
 0
};
 CmPAsnElmDef szDlnkUEAssociatedLPPaTport =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztDlnkUEAssociatedLPPaTport),
 &flagSz3M,
 0,
 (U8 *)(&szDlnkUEAssociatedLPPaTportspec),
 0L
};
 CmPAsnElmDef *sz_ValueUlnkUEAssociatedLPPaTport_IEsClsInst[] =
{
 &szMME_UE_S1AP_ID,
 &szENB_UE_S1AP_ID,
 &szRouting_ID,
 &szLPPa_PDU
};
 U32 sz_ValueUlnkUEAssociatedLPPaTport_IEsClsInstId[] =
{
 0,
 8,
 148,
 147
};
SzMsgConInf szUlnkUEAssociatedLPPaTport_IEsConInf =
{
 {
  { 0, 0, 0x2 },
  { 8, 0, 0x2 },
  { 148, 0, 0x2 },
  { 147, 0, 0x2 }
 },
 4,
 4
};
 CmPAsnClassInfo sz_ValueUlnkUEAssociatedLPPaTport_IEsClsInfo =
{
 4,
 &sz_ValueUlnkUEAssociatedLPPaTport_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUlnkUEAssociatedLPPaTport_IEsClsSpec =
{



 &sz_ValueUlnkUEAssociatedLPPaTport_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUlnkUEAssociatedLPPaTport_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUlnkUEAssociatedLPPaTport_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUlnkUEAssociatedLPPaTport_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UlnkUEAssociatedLPPaTport_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUlnkUEAssociatedLPPaTport_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UlnkUEAssociatedLPPaTport_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UlnkUEAssociatedLPPaTport_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UlnkUEAssociatedLPPaTport_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UlnkUEAssociatedLPPaTport_IEsspec),
 0L
};


 S16 szProtIE_Cont_UlnkUEAssociatedLPPaTport_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs *protIe = 0L;
 SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUlnkUEAssociatedLPPaTport_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UlnkUEAssociatedLPPaTport_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs),
 &flagSz3M,
 szProtIE_Cont_UlnkUEAssociatedLPPaTport_IEsValidate,
 (U8 *) (&szProtIE_Cont_UlnkUEAssociatedLPPaTport_IEsspec),
 0L
};
 CmPAsnElmDef *szUlnkUEAssociatedLPPaTportTkn[] =
{
 &szProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs,
  &szProtIE_Field_UlnkUEAssociatedLPPaTport_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUlnkUEAssociatedLPPaTportspec =
{



 0,
 0,
 0L,
 0L,
 &szUlnkUEAssociatedLPPaTportTkn[0],
 0
};
 CmPAsnElmDef szUlnkUEAssociatedLPPaTport =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUlnkUEAssociatedLPPaTport),
 &flagSz3M,
 0,
 (U8 *)(&szUlnkUEAssociatedLPPaTportspec),
 0L
};
 CmPAsnElmDef *sz_ValueDlnkNonUEAssociatedLPPaTport_IEsClsInst[] =
{
 &szRouting_ID,
 &szLPPa_PDU
};
 U32 sz_ValueDlnkNonUEAssociatedLPPaTport_IEsClsInstId[] =
{
 148,
 147
};
SzMsgConInf szDlnkNonUEAssociatedLPPaTport_IEsConInf =
{
 {
  { 148, 0, 0x2 },
  { 147, 0, 0x2 }
 },
 2,
 2
};
 CmPAsnClassInfo sz_ValueDlnkNonUEAssociatedLPPaTport_IEsClsInfo =
{
 2,
 &sz_ValueDlnkNonUEAssociatedLPPaTport_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueDlnkNonUEAssociatedLPPaTport_IEsClsSpec =
{



 &sz_ValueDlnkNonUEAssociatedLPPaTport_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueDlnkNonUEAssociatedLPPaTport_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueDlnkNonUEAssociatedLPPaTport_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueDlnkNonUEAssociatedLPPaTport_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueDlnkNonUEAssociatedLPPaTport_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEsspec),
 0L
};


 S16 szProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs *protIe = 0L;
 SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szDlnkNonUEAssociatedLPPaTport_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs),
 &flagSz3M,
 szProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEsValidate,
 (U8 *) (&szProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEsspec),
 0L
};
 CmPAsnElmDef *szDlnkNonUEAssociatedLPPaTportTkn[] =
{
 &szProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs,
  &szProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szDlnkNonUEAssociatedLPPaTportspec =
{



 0,
 0,
 0L,
 0L,
 &szDlnkNonUEAssociatedLPPaTportTkn[0],
 0
};
 CmPAsnElmDef szDlnkNonUEAssociatedLPPaTport =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztDlnkNonUEAssociatedLPPaTport),
 &flagSz3M,
 0,
 (U8 *)(&szDlnkNonUEAssociatedLPPaTportspec),
 0L
};
 CmPAsnElmDef *sz_ValueUlnkNonUEAssociatedLPPaTport_IEsClsInst[] =
{
 &szRouting_ID,
 &szLPPa_PDU
};
 U32 sz_ValueUlnkNonUEAssociatedLPPaTport_IEsClsInstId[] =
{
 148,
 147
};
SzMsgConInf szUlnkNonUEAssociatedLPPaTport_IEsConInf =
{
 {
  { 148, 0, 0x2 },
  { 147, 0, 0x2 }
 },
 2,
 2
};
 CmPAsnClassInfo sz_ValueUlnkNonUEAssociatedLPPaTport_IEsClsInfo =
{
 2,
 &sz_ValueUlnkNonUEAssociatedLPPaTport_IEsClsInstId[0]
};
CmPAsnClassIEDef sz_ValueUlnkNonUEAssociatedLPPaTport_IEsClsSpec =
{



 &sz_ValueUlnkNonUEAssociatedLPPaTport_IEsClsInfo,
 (sizeof(SztProtIE_ID) + sizeof(SztCriticality)),
 &sz_ValueUlnkNonUEAssociatedLPPaTport_IEsClsInst[0],



};
 CmPAsnElmDef sz_ValueUlnkNonUEAssociatedLPPaTport_IEsCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_ValueUlnkNonUEAssociatedLPPaTport_IEsClsSpec)
};
 CmPAsnElmDef *szProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEsTkn[] =
{
 &szProtIE_ID,
 &szCriticality,
 &sz_ValueUlnkNonUEAssociatedLPPaTport_IEsCls,
 &szConstTerm
};
CmPAsnSetSeqDef szProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEsspec =
{



 0,
 0,
 0L,
 0L,
 &szProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEsTkn[0],
 0
};
 CmPAsnElmDef szProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs),
 &flagSz3M,
 0,
 (U8 *)(&szProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEsspec),
 0L
};


 S16 szProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEsValidate
(
CmPAsnMsgCp *msgCp
)




{
 U8 numIes = 0;
 U32 sizeIe = 0;

 S16 ret = 0;
 SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs *protIe = 0L;
 SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *member = 0L;

 ;;

 protIe = (SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs *)(msgCp->evntStr);
 numIes = protIe->noComp.val;

 sizeIe = sizeof(SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs);

 member = &protIe->member[0];

 ret = szValidateProtIes(&szUlnkNonUEAssociatedLPPaTport_IEsConInf, msgCp, member, sizeIe, numIes);

 return(ret);
}
CmPAsnSetSeqOfDef szProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEsspec =
{



 0,
 65535,
 3*sizeof(U32)
};
 CmPAsnElmDef szProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs =
{



 CM_PASN_TET_SEQOF,
 0,
 sizeof(SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs),
 &flagSz3M,
 szProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEsValidate,
 (U8 *) (&szProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEsspec),
 0L
};
 CmPAsnElmDef *szUlnkNonUEAssociatedLPPaTportTkn[] =
{
 &szProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs,
  &szProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs,
  &szConstTerm,
 &szExtMkr,
 &szConstTerm
};
CmPAsnSetSeqDef szUlnkNonUEAssociatedLPPaTportspec =
{



 0,
 0,
 0L,
 0L,
 &szUlnkNonUEAssociatedLPPaTportTkn[0],
 0
};
 CmPAsnElmDef szUlnkNonUEAssociatedLPPaTport =
{



 CM_PASN_TET_SEQ,
 1,
 sizeof(SztUlnkNonUEAssociatedLPPaTport),
 &flagSz3M,
 0,
 (U8 *)(&szUlnkNonUEAssociatedLPPaTportspec),
 0L
};
 CmPAsnElmDef *sz_InitiatingMsgClsInst[] =
{
 &szHovrReqd,
 &szHovrRqst,
 &szPathSwRqst,
 &szE_RABSetupRqst,
 &szE_RABMdfyRqst,
 &szE_RABRlsCmmd,
 &szInitCntxtSetupRqst,
 &szHovrCancel,
 &szKillRqst,
 &szReset,
 &szS1SetupRqst,
 &szUECntxtModificationRqst,
 &szUECntxtRlsCmmd,
 &szENBConfigUpd,
 &szMMEConfigUpd,
 &szWriteReplaceWarningRqst,
 &szUERadioCapbltyMatchRqst,
 &szHovrNtfy,
 &szE_RABRlsInd,
 &szPag,
 &szDlnkNASTport,
 &szInitUEMsg,
 &szUlnkNASTport,
 &szErrInd,
 &szNASNonDlvryInd,
 &szUECntxtRlsRqst,
 &szDlnkS1cdma2000tunneling,
 &szUlnkS1cdma2000tunneling,
 &szUECapbltyInfoInd,
 &szENBStatusTfr,
 &szMMEStatusTfr,
 &szDeactvTrace,
 &szTraceStart,
 &szTraceFailInd,
 &szCellTrafficTrace,
 &szLocRprtngCntrl,
 &szLocRprtngFailInd,
 &szLocReport,
 &szOverloadStart,
 &szOverloadStop,
 &szENBDirectInformTfr,
 &szMMEDirectInformTfr,
 &szENBConfigTfr,
 &szMMEConfigTfr,
 &szPrivMsg,
 &szDlnkUEAssociatedLPPaTport,
 &szUlnkUEAssociatedLPPaTport,
 &szDlnkNonUEAssociatedLPPaTport,
 &szUlnkNonUEAssociatedLPPaTport
};
 U32 sz_InitiatingMsgClsInstId[] =
{
 0,
 1,
 3,
 5,
 6,
 7,
 9,
 4,
 43,
 14,
 17,
 21,
 23,
 29,
 30,
 36,
 48,
 2,
 8,
 10,
 11,
 12,
 13,
 15,
 16,
 18,
 19,
 20,
 22,
 24,
 25,
 26,
 27,
 28,
 42,
 31,
 32,
 33,
 34,
 35,
 37,
 38,
 40,
 41,
 39,
 44,
 45,
 46,
 47
};
 CmPAsnClassInfo sz_InitiatingMsgClsInfo =
{
 49,
 &sz_InitiatingMsgClsInstId[0]
};
CmPAsnClassIEDef sz_InitiatingMsgClsSpec =
{



 &sz_InitiatingMsgClsInfo,
 (sizeof(SztProcedureCode) + sizeof(SztCriticality)),
 &sz_InitiatingMsgClsInst[0],



};
 CmPAsnElmDef sz_InitiatingMsgCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_InitiatingMsgCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_InitiatingMsgClsSpec)
};
 CmPAsnElmDef *szInitiatingMsgTkn[] =
{
 &szProcedureCode,
 &szCriticality,
 &sz_InitiatingMsgCls,
 &szConstTerm
};
CmPAsnSetSeqDef szInitiatingMsgspec =
{



 0,
 0,
 0L,
 0L,
 &szInitiatingMsgTkn[0],
 0
};
 CmPAsnElmDef szInitiatingMsg =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztInitiatingMsg),
 &flagSz3M,
 0,
 (U8 *)(&szInitiatingMsgspec),
 0L
};
 CmPAsnElmDef *sz_SuccessfulOutcomeClsInst[] =
{
 &szHovrCmmd,
 &szHovrRqstAckg,
 &szPathSwRqstAckg,
 &szE_RABSetupResp,
 &szE_RABMdfyResp,
 &szE_RABRlsResp,
 &szInitCntxtSetupResp,
 &szHovrCancelAckg,
 &szKillResp,
 &szResetAckg,
 &szS1SetupResp,
 &szUECntxtModificationResp,
 &szUECntxtRlsComplete,
 &szENBConfigUpdAckg,
 &szMMEConfigUpdAckg,
 &szWriteReplaceWarningResp,
 &szUERadioCapbltyMatchResp
};
 U32 sz_SuccessfulOutcomeClsInstId[] =
{
 0,
 1,
 3,
 5,
 6,
 7,
 9,
 4,
 43,
 14,
 17,
 21,
 23,
 29,
 30,
 36,
 48
};
 CmPAsnClassInfo sz_SuccessfulOutcomeClsInfo =
{
 17,
 &sz_SuccessfulOutcomeClsInstId[0]
};
CmPAsnClassIEDef sz_SuccessfulOutcomeClsSpec =
{



 &sz_SuccessfulOutcomeClsInfo,
 (sizeof(SztProcedureCode) + sizeof(SztCriticality)),
 &sz_SuccessfulOutcomeClsInst[0],



};
 CmPAsnElmDef sz_SuccessfulOutcomeCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_SuccessfulOutcomeCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_SuccessfulOutcomeClsSpec)
};
 CmPAsnElmDef *szSuccessfulOutcomeTkn[] =
{
 &szProcedureCode,
 &szCriticality,
 &sz_SuccessfulOutcomeCls,
 &szConstTerm
};
CmPAsnSetSeqDef szSuccessfulOutcomespec =
{



 0,
 0,
 0L,
 0L,
 &szSuccessfulOutcomeTkn[0],
 0
};
 CmPAsnElmDef szSuccessfulOutcome =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztSuccessfulOutcome),
 &flagSz3M,
 0,
 (U8 *)(&szSuccessfulOutcomespec),
 0L
};
 CmPAsnElmDef *sz_UnsuccessfulOutcomeClsInst[] =
{
 &szHovrPrepFail,
 &szHovrFail,
 &szPathSwRqstFail,
 &szInitCntxtSetupFail,
 &szS1SetupFail,
 &szUECntxtModificationFail,
 &szENBConfigUpdFail,
 &szMMEConfigUpdFail
};
 U32 sz_UnsuccessfulOutcomeClsInstId[] =
{
 0,
 1,
 3,
 9,
 17,
 21,
 29,
 30
};
 CmPAsnClassInfo sz_UnsuccessfulOutcomeClsInfo =
{
 8,
 &sz_UnsuccessfulOutcomeClsInstId[0]
};
CmPAsnClassIEDef sz_UnsuccessfulOutcomeClsSpec =
{



 &sz_UnsuccessfulOutcomeClsInfo,
 (sizeof(SztProcedureCode) + sizeof(SztCriticality)),
 &sz_UnsuccessfulOutcomeClsInst[0],



};
 CmPAsnElmDef sz_UnsuccessfulOutcomeCls =
{



 CM_PASN_TET_CLASSIE,
 0,
 sizeof(Szt_UnsuccessfulOutcomeCls),
 &flagSz3M,
 0,
 (U8 *)(&sz_UnsuccessfulOutcomeClsSpec)
};
 CmPAsnElmDef *szUnsuccessfulOutcomeTkn[] =
{
 &szProcedureCode,
 &szCriticality,
 &sz_UnsuccessfulOutcomeCls,
 &szConstTerm
};
CmPAsnSetSeqDef szUnsuccessfulOutcomespec =
{



 0,
 0,
 0L,
 0L,
 &szUnsuccessfulOutcomeTkn[0],
 0
};
 CmPAsnElmDef szUnsuccessfulOutcome =
{



 CM_PASN_TET_SEQ,
 0,
 sizeof(SztUnsuccessfulOutcome),
 &flagSz3M,
 0,
 (U8 *)(&szUnsuccessfulOutcomespec),
 0L
};
 CmPAsnElmDef *szS1AP_PDUTkn[] =
{
 &szInitiatingMsg,
 &szSuccessfulOutcome,
 &szUnsuccessfulOutcome,
 &szExtMkr,
 &szConstTerm
};
CmPAsnChoiceDef szS1AP_PDUspec =
{



 3,
 0,
 &szS1AP_PDUTkn[0]
};
CmPAsnElmDef szS1AP_PDU =
{



 CM_PASN_TET_CHOICE,
 1,
 sizeof(SztS1AP_PDU),
 &flagSz3M,
 0L,
 (U8 *)(&szS1AP_PDUspec),
 0L
};
 CmPAsnElmDef *szMsgDb[] =
{
   &szS1AP_PDU,
   0L
};
 CmPAsnElmDef *szMsgDbIe[][2] =
{
   {
      0L
   },
   {
      &szSrceNB_ToTgeteNB_TprntCont,
      0L
   },
   {
      &szTgeteNB_ToSrceNB_TprntCont,
      0L
   }
};


 CmPAsnElmDef *szMsgIEDb[][4] =
{
   {
   &szUE_HistoryInform,
      &szLastVisitedCell_Item,
      0L,
      0L
   },
   {
      &szGlobal_ENB_ID,
      0L,
      0L,
      0L
  }
};