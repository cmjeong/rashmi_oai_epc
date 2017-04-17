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
 U8 *cmMemcpy (U8 *tgt, const U8 *src, U32 len);
 S16 cmMemcmp (const U8 *s1, const U8 *s2, U32 len);
 U8 *cmMemset (U8 *src, U8 val, U32 len);

 S16 cmStrcmp (const U8 *s1, const U8 *s2);

 S16 cmStrncmp (const U8 *s1, const U8 *s2, MsgLen len);
 MsgLen cmStrlen (const U8 *s);

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

extern S16 cmPkSztPrivIE_ID (SztPrivIE_ID *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnEUTRAN_CGI_ExtIEsCls (Szt_ExtnEUTRAN_CGI_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_EUTRAN_CGI_ExtIEs (SztProtExtnField_EUTRAN_CGI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_EUTRAN_CGI_ExtIEs (SztProtExtnCont_EUTRAN_CGI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztEUTRAN_CGI (SztEUTRAN_CGI *param, Buffer *mBuf);
extern S16 cmPkSztCellIdLstforMDT (SztCellIdLstforMDT *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCellBasedMDT_ExtIEsCls (Szt_ExtnCellBasedMDT_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CellBasedMDT_ExtIEs (SztProtExtnField_CellBasedMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CellBasedMDT_ExtIEs (SztProtExtnCont_CellBasedMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCellBasedMDT (SztCellBasedMDT *param, Buffer *mBuf);
extern S16 cmPkSztTALstforMDT (SztTALstforMDT *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTABasedMDT_ExtIEsCls (Szt_ExtnTABasedMDT_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TABasedMDT_ExtIEs (SztProtExtnField_TABasedMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TABasedMDT_ExtIEs (SztProtExtnCont_TABasedMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTABasedMDT (SztTABasedMDT *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTAI_ExtIEsCls (Szt_ExtnTAI_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TAI_ExtIEs (SztProtExtnField_TAI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TAI_ExtIEs (SztProtExtnCont_TAI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTAI (SztTAI *param, Buffer *mBuf);
extern S16 cmPkSztTAILstforMDT (SztTAILstforMDT *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTAIBasedMDT_ExtIEsCls (Szt_ExtnTAIBasedMDT_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TAIBasedMDT_ExtIEs (SztProtExtnField_TAIBasedMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TAIBasedMDT_ExtIEs (SztProtExtnCont_TAIBasedMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTAIBasedMDT (SztTAIBasedMDT *param, Buffer *mBuf);
extern S16 cmPkSztAreaScopeOfMDT (SztAreaScopeOfMDT *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls (Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs (SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs (SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztAllocnAndRetentionPriority (SztAllocnAndRetentionPriority *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCOUNTvalue_ExtIEsCls (Szt_ExtnCOUNTvalue_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_COUNTvalue_ExtIEs (SztProtExtnField_COUNTvalue_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_COUNTvalue_ExtIEs (SztProtExtnCont_COUNTvalue_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCOUNTvalue (SztCOUNTvalue *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCOUNTValueExtended_ExtIEsCls (Szt_ExtnCOUNTValueExtended_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_COUNTValueExtended_ExtIEs (SztProtExtnField_COUNTValueExtended_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_COUNTValueExtended_ExtIEs (SztProtExtnCont_COUNTValueExtended_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCOUNTValueExtended (SztCOUNTValueExtended *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls (Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs (SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs (SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztBrs_SubjToStatusTfr_Item (SztBrs_SubjToStatusTfr_Item *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls (Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs (SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs *param, Buffer *mBuf);
extern S16 cmPkSztBrs_SubjToStatusTfrLst (SztBrs_SubjToStatusTfrLst *param, Buffer *mBuf);
extern S16 cmPkSztBPLMNs (SztBPLMNs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls (Szt_ExtnCellID_Cancelled_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CellID_Cancelled_Item_ExtIEs (SztProtExtnField_CellID_Cancelled_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs (SztProtExtnCont_CellID_Cancelled_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCellID_Cancelled_Item (SztCellID_Cancelled_Item *param, Buffer *mBuf);
extern S16 cmPkSztCellID_Cancelled (SztCellID_Cancelled *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls (Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs (SztProtExtnField_CancelledCellinTAI_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs (SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCancelledCellinTAI_Item (SztCancelledCellinTAI_Item *param, Buffer *mBuf);
extern S16 cmPkSztCancelledCellinTAI (SztCancelledCellinTAI *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls (Szt_ExtnTAI_Cancelled_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TAI_Cancelled_Item_ExtIEs (SztProtExtnField_TAI_Cancelled_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs (SztProtExtnCont_TAI_Cancelled_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTAI_Cancelled_Item (SztTAI_Cancelled_Item *param, Buffer *mBuf);
extern S16 cmPkSztTAI_Cancelled (SztTAI_Cancelled *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls (Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs (SztProtExtnField_CancelledCellinEAI_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs (SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCancelledCellinEAI_Item (SztCancelledCellinEAI_Item *param, Buffer *mBuf);
extern S16 cmPkSztCancelledCellinEAI (SztCancelledCellinEAI *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls (Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs (SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs (SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztEmergencyAreaID_Cancelled_Item (SztEmergencyAreaID_Cancelled_Item *param, Buffer *mBuf);
extern S16 cmPkSztEmergencyAreaID_Cancelled (SztEmergencyAreaID_Cancelled *param, Buffer *mBuf);
extern S16 cmPkSztBroadcastCancelledAreaLst (SztBroadcastCancelledAreaLst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls (Szt_ExtnCellID_Broadcast_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CellID_Broadcast_Item_ExtIEs (SztProtExtnField_CellID_Broadcast_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs (SztProtExtnCont_CellID_Broadcast_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCellID_Broadcast_Item (SztCellID_Broadcast_Item *param, Buffer *mBuf);
extern S16 cmPkSztCellID_Broadcast (SztCellID_Broadcast *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls (Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs (SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs (SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCompletedCellinTAI_Item (SztCompletedCellinTAI_Item *param, Buffer *mBuf);
extern S16 cmPkSztCompletedCellinTAI (SztCompletedCellinTAI *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls (Szt_ExtnTAI_Broadcast_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TAI_Broadcast_Item_ExtIEs (SztProtExtnField_TAI_Broadcast_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs (SztProtExtnCont_TAI_Broadcast_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTAI_Broadcast_Item (SztTAI_Broadcast_Item *param, Buffer *mBuf);
extern S16 cmPkSztTAI_Broadcast (SztTAI_Broadcast *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls (Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs (SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs (SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCompletedCellinEAI_Item (SztCompletedCellinEAI_Item *param, Buffer *mBuf);
extern S16 cmPkSztCompletedCellinEAI (SztCompletedCellinEAI *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls (Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs (SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs (SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztEmergencyAreaID_Broadcast_Item (SztEmergencyAreaID_Broadcast_Item *param, Buffer *mBuf);
extern S16 cmPkSztEmergencyAreaID_Broadcast (SztEmergencyAreaID_Broadcast *param, Buffer *mBuf);
extern S16 cmPkSztBroadcastCompletedAreaLst (SztBroadcastCompletedAreaLst *param, Buffer *mBuf);
extern S16 cmPkSztCause (SztCause *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls (Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs (SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs (SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCdma2000OneXSRVCCInfo (SztCdma2000OneXSRVCCInfo *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCellTyp_ExtIEsCls (Szt_ExtnCellTyp_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CellTyp_ExtIEs (SztProtExtnField_CellTyp_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CellTyp_ExtIEs (SztProtExtnCont_CellTyp_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCellTyp (SztCellTyp *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCGI_ExtIEsCls (Szt_ExtnCGI_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CGI_ExtIEs (SztProtExtnField_CGI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CGI_ExtIEs (SztProtExtnCont_CGI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCGI (SztCGI *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCSG_IdLst_Item_ExtIEsCls (Szt_ExtnCSG_IdLst_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CSG_IdLst_Item_ExtIEs (SztProtExtnField_CSG_IdLst_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CSG_IdLst_Item_ExtIEs (SztProtExtnCont_CSG_IdLst_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCSG_IdLst_Item (SztCSG_IdLst_Item *param, Buffer *mBuf);
extern S16 cmPkSztCSG_IdLst (SztCSG_IdLst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls (Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs (SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs (SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCriticalityDiag_IE_Item (SztCriticalityDiag_IE_Item *param, Buffer *mBuf);
extern S16 cmPkSztCriticalityDiag_IE_Lst (SztCriticalityDiag_IE_Lst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnCriticalityDiag_ExtIEsCls (Szt_ExtnCriticalityDiag_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_CriticalityDiag_ExtIEs (SztProtExtnField_CriticalityDiag_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_CriticalityDiag_ExtIEs (SztProtExtnCont_CriticalityDiag_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztCriticalityDiag (SztCriticalityDiag *param, Buffer *mBuf);
extern S16 cmPkSztECGILst (SztECGILst *param, Buffer *mBuf);
extern S16 cmPkSztEmergencyAreaIDLst (SztEmergencyAreaIDLst *param, Buffer *mBuf);
extern S16 cmPkSztENB_ID (SztENB_ID *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnLAI_ExtIEsCls (Szt_ExtnLAI_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_LAI_ExtIEs (SztProtExtnField_LAI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_LAI_ExtIEs (SztProtExtnCont_LAI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztLAI (SztLAI *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnGERAN_Cell_ID_ExtIEsCls (Szt_ExtnGERAN_Cell_ID_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_GERAN_Cell_ID_ExtIEs (SztProtExtnField_GERAN_Cell_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_GERAN_Cell_ID_ExtIEs (SztProtExtnCont_GERAN_Cell_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztGERAN_Cell_ID (SztGERAN_Cell_ID *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnGlobalENB_ID_ExtIEsCls (Szt_ExtnGlobalENB_ID_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_GlobalENB_ID_ExtIEs (SztProtExtnField_GlobalENB_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_GlobalENB_ID_ExtIEs (SztProtExtnCont_GlobalENB_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztGlobal_ENB_ID (SztGlobal_ENB_ID *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnGUMMEI_ExtIEsCls (Szt_ExtnGUMMEI_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_GUMMEI_ExtIEs (SztProtExtnField_GUMMEI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_GUMMEI_ExtIEs (SztProtExtnCont_GUMMEI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztGUMMEI (SztGUMMEI *param, Buffer *mBuf);
extern S16 cmPkSztGUMMEILst (SztGUMMEILst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls (Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs (SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs (SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztENB_StatusTfr_TprntCont (SztENB_StatusTfr_TprntCont *param, Buffer *mBuf);
extern S16 cmPkSztENBX2TLAs (SztENBX2TLAs *param, Buffer *mBuf);
extern S16 cmPkSztEPLMNs (SztEPLMNs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABInformLstItem_ExtIEsCls (Szt_ExtnE_RABInformLstItem_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABInformLstItem_ExtIEs (SztProtExtnField_E_RABInformLstItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABInformLstItem_ExtIEs (SztProtExtnCont_E_RABInformLstItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABInformLstItem (SztE_RABInformLstItem *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABInformLstIEsCls (Szt_ValueE_RABInformLstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABInformLstIEs (SztProtIE_Field_E_RABInformLstIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABInformLst (SztE_RABInformLst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABItem_ExtIEsCls (Szt_ExtnE_RABItem_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABItem_ExtIEs (SztProtExtnField_E_RABItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABItem_ExtIEs (SztProtExtnCont_E_RABItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABItem (SztE_RABItem *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABItemIEsCls (Szt_ValueE_RABItemIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABItemIEs (SztProtIE_Field_E_RABItemIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABLst (SztE_RABLst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnGBR_QosInform_ExtIEsCls (Szt_ExtnGBR_QosInform_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_GBR_QosInform_ExtIEs (SztProtExtnField_GBR_QosInform_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_GBR_QosInform_ExtIEs (SztProtExtnCont_GBR_QosInform_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztGBR_QosInform (SztGBR_QosInform *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABQoSParams_ExtIEsCls (Szt_ExtnE_RABQoSParams_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABQoSParams_ExtIEs (SztProtExtnField_E_RABQoSParams_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABQoSParams_ExtIEs (SztProtExtnCont_E_RABQoSParams_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABLvlQoSParams (SztE_RABLvlQoSParams *param, Buffer *mBuf);
extern S16 cmPkSztForbiddenTACs (SztForbiddenTACs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnForbiddenTAs_Item_ExtIEsCls (Szt_ExtnForbiddenTAs_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_ForbiddenTAs_Item_ExtIEs (SztProtExtnField_ForbiddenTAs_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs (SztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztForbiddenTAs_Item (SztForbiddenTAs_Item *param, Buffer *mBuf);
extern S16 cmPkSztForbiddenTAs (SztForbiddenTAs *param, Buffer *mBuf);
extern S16 cmPkSztForbiddenLACs (SztForbiddenLACs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnForbiddenLAs_Item_ExtIEsCls (Szt_ExtnForbiddenLAs_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_ForbiddenLAs_Item_ExtIEs (SztProtExtnField_ForbiddenLAs_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs (SztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztForbiddenLAs_Item (SztForbiddenLAs_Item *param, Buffer *mBuf);
extern S16 cmPkSztForbiddenLAs (SztForbiddenLAs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnHovrRestrnLst_ExtIEsCls (Szt_ExtnHovrRestrnLst_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_HovrRestrnLst_ExtIEs (SztProtExtnField_HovrRestrnLst_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_HovrRestrnLst_ExtIEs (SztProtExtnCont_HovrRestrnLst_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrRestrnLst (SztHovrRestrnLst *param, Buffer *mBuf);
extern S16 cmPkSztMeasurementThresholdA2 (SztMeasurementThresholdA2 *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnM1ThresholdEventA2_ExtIEsCls (Szt_ExtnM1ThresholdEventA2_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_M1ThresholdEventA2_ExtIEs (SztProtExtnField_M1ThresholdEventA2_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_M1ThresholdEventA2_ExtIEs (SztProtExtnCont_M1ThresholdEventA2_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztM1ThresholdEventA2 (SztM1ThresholdEventA2 *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnM1PeriodicRprtng_ExtIEsCls (Szt_ExtnM1PeriodicRprtng_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_M1PeriodicRprtng_ExtIEs (SztProtExtnField_M1PeriodicRprtng_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_M1PeriodicRprtng_ExtIEs (SztProtExtnCont_M1PeriodicRprtng_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztM1PeriodicRprtng (SztM1PeriodicRprtng *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnM3Config_ExtIEsCls (Szt_ExtnM3Config_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_M3Config_ExtIEs (SztProtExtnField_M3Config_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_M3Config_ExtIEs (SztProtExtnCont_M3Config_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztM3Config (SztM3Config *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnM4Config_ExtIEsCls (Szt_ExtnM4Config_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_M4Config_ExtIEs (SztProtExtnField_M4Config_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_M4Config_ExtIEs (SztProtExtnCont_M4Config_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztM4Config (SztM4Config *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnM5Config_ExtIEsCls (Szt_ExtnM5Config_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_M5Config_ExtIEs (SztProtExtnField_M5Config_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_M5Config_ExtIEs (SztProtExtnCont_M5Config_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztM5Config (SztM5Config *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnImmediateMDT_ExtIEsCls (Szt_ExtnImmediateMDT_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_ImmediateMDT_ExtIEs (SztProtExtnField_ImmediateMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_ImmediateMDT_ExtIEs (SztProtExtnCont_ImmediateMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztImmediateMDT (SztImmediateMDT *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls (Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs (SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs (SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztLastVisitedEUTRANCellInform (SztLastVisitedEUTRANCellInform *param, Buffer *mBuf);
extern S16 cmPkSztLastVisitedGERANCellInform (SztLastVisitedGERANCellInform *param, Buffer *mBuf);
extern S16 cmPkSztLastVisitedCell_Item (SztLastVisitedCell_Item *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnLoggedMDT_ExtIEsCls (Szt_ExtnLoggedMDT_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_LoggedMDT_ExtIEs (SztProtExtnField_LoggedMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_LoggedMDT_ExtIEs (SztProtExtnCont_LoggedMDT_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztLoggedMDT (SztLoggedMDT *param, Buffer *mBuf);
extern S16 cmPkSztMDTMode (SztMDTMode *param, Buffer *mBuf);
extern S16 cmPkSztMDTPLMNLst (SztMDTPLMNLst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnMDT_Config_ExtIEsCls (Szt_ExtnMDT_Config_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_MDT_Config_ExtIEs (SztProtExtnField_MDT_Config_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_MDT_Config_ExtIEs (SztProtExtnCont_MDT_Config_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztMDT_Config (SztMDT_Config *param, Buffer *mBuf);
extern S16 cmPkSztOverloadResp (SztOverloadResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnRqstTyp_ExtIEsCls (Szt_ExtnRqstTyp_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_RqstTyp_ExtIEs (SztProtExtnField_RqstTyp_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_RqstTyp_ExtIEs (SztProtExtnCont_RqstTyp_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztRqstTyp (SztRqstTyp *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTgetRNC_ID_ExtIEsCls (Szt_ExtnTgetRNC_ID_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TgetRNC_ID_ExtIEs (SztProtExtnField_TgetRNC_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TgetRNC_ID_ExtIEs (SztProtExtnCont_TgetRNC_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTgetRNC_ID (SztTgetRNC_ID *param, Buffer *mBuf);
extern S16 cmPkSztRIMRoutingAddr (SztRIMRoutingAddr *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnRIMTfr_ExtIEsCls (Szt_ExtnRIMTfr_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_RIMTfr_ExtIEs (SztProtExtnField_RIMTfr_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_RIMTfr_ExtIEs (SztProtExtnCont_RIMTfr_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztRIMTfr (SztRIMTfr *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnSecurCntxt_ExtIEsCls (Szt_ExtnSecurCntxt_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_SecurCntxt_ExtIEs (SztProtExtnField_SecurCntxt_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_SecurCntxt_ExtIEs (SztProtExtnCont_SecurCntxt_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztSecurCntxt (SztSecurCntxt *param, Buffer *mBuf);
extern S16 cmPkSztENBX2GTPTLAs (SztENBX2GTPTLAs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnENBX2ExtTLA_ExtIEsCls (Szt_ExtnENBX2ExtTLA_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_ENBX2ExtTLA_ExtIEs (SztProtExtnField_ENBX2ExtTLA_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_ENBX2ExtTLA_ExtIEs (SztProtExtnCont_ENBX2ExtTLA_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztENBX2ExtTLA (SztENBX2ExtTLA *param, Buffer *mBuf);
extern S16 cmPkSztENBX2ExtTLAs (SztENBX2ExtTLAs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnX2TNLConfigInfo_ExtIEsCls (Szt_ExtnX2TNLConfigInfo_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_X2TNLConfigInfo_ExtIEs (SztProtExtnField_X2TNLConfigInfo_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_X2TNLConfigInfo_ExtIEs (SztProtExtnCont_X2TNLConfigInfo_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztX2TNLConfigInfo (SztX2TNLConfigInfo *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls (Szt_ExtnTimeSynchronizationInfo_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TimeSynchronizationInfo_ExtIEs (SztProtExtnField_TimeSynchronizationInfo_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs (SztProtExtnCont_TimeSynchronizationInfo_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTimeSynchronizationInfo (SztTimeSynchronizationInfo *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnSONInformReply_ExtIEsCls (Szt_ExtnSONInformReply_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_SONInformReply_ExtIEs (SztProtExtnField_SONInformReply_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_SONInformReply_ExtIEs (SztProtExtnCont_SONInformReply_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztSONInformReply (SztSONInformReply *param, Buffer *mBuf);
extern S16 cmPkSztSONInform (SztSONInform *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTgeteNB_ID_ExtIEsCls (Szt_ExtnTgeteNB_ID_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TgeteNB_ID_ExtIEs (SztProtExtnField_TgeteNB_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TgeteNB_ID_ExtIEs (SztProtExtnCont_TgeteNB_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTgeteNB_ID (SztTgeteNB_ID *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnSrceNB_ID_ExtIEsCls (Szt_ExtnSrceNB_ID_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_SrceNB_ID_ExtIEs (SztProtExtnField_SrceNB_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_SrceNB_ID_ExtIEs (SztProtExtnCont_SrceNB_ID_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztSrceNB_ID (SztSrceNB_ID *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnSONConfigTfr_ExtIEsCls (Szt_ExtnSONConfigTfr_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_SONConfigTfr_ExtIEs (SztProtExtnField_SONConfigTfr_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_SONConfigTfr_ExtIEs (SztProtExtnCont_SONConfigTfr_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztSONConfigTfr (SztSONConfigTfr *param, Buffer *mBuf);
extern S16 cmPkSztUE_HistoryInform (SztUE_HistoryInform *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls (Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs (SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs (SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztSrceNB_ToTgeteNB_TprntCont (SztSrceNB_ToTgeteNB_TprntCont *param, Buffer *mBuf);
extern S16 cmPkSztSrvdPLMNs (SztSrvdPLMNs *param, Buffer *mBuf);
extern S16 cmPkSztSrvdGroupIDs (SztSrvdGroupIDs *param, Buffer *mBuf);
extern S16 cmPkSztSrvdMMECs (SztSrvdMMECs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls (Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs (SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs (SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztSrvdGUMMEIsItem (SztSrvdGUMMEIsItem *param, Buffer *mBuf);
extern S16 cmPkSztSrvdGUMMEIs (SztSrvdGUMMEIs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnSuppTAs_Item_ExtIEsCls (Szt_ExtnSuppTAs_Item_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_SuppTAs_Item_ExtIEs (SztProtExtnField_SuppTAs_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_SuppTAs_Item_ExtIEs (SztProtExtnCont_SuppTAs_Item_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztSuppTAs_Item (SztSuppTAs_Item *param, Buffer *mBuf);
extern S16 cmPkSztSuppTAs (SztSuppTAs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnS_TMSI_ExtIEsCls (Szt_ExtnS_TMSI_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_S_TMSI_ExtIEs (SztProtExtnField_S_TMSI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_S_TMSI_ExtIEs (SztProtExtnCont_S_TMSI_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztS_TMSI (SztS_TMSI *param, Buffer *mBuf);
extern S16 cmPkSztTAILstforWarning (SztTAILstforWarning *param, Buffer *mBuf);
extern S16 cmPkSztTgetID (SztTgetID *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls (Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs (SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs (SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTgeteNB_ToSrceNB_TprntCont (SztTgeteNB_ToSrceNB_TprntCont *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTraceActvn_ExtIEsCls (Szt_ExtnTraceActvn_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TraceActvn_ExtIEs (SztProtExtnField_TraceActvn_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TraceActvn_ExtIEs (SztProtExtnCont_TraceActvn_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTraceActvn (SztTraceActvn *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTunnel_Inform_ExtIEsCls (Szt_ExtnTunnel_Inform_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_Tunnel_Inform_ExtIEs (SztProtExtnField_Tunnel_Inform_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_Tunnel_Inform_ExtIEs (SztProtExtnCont_Tunnel_Inform_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTunnelInform (SztTunnelInform *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls (Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs (SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs (SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztUEAggMaxBitrate (SztUEAggMaxBitrate *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls (Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs (SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs (SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztUE_S1AP_ID_pair (SztUE_S1AP_ID_pair *param, Buffer *mBuf);
extern S16 cmPkSztUE_S1AP_IDs (SztUE_S1AP_IDs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls (Szt_ExtnUE_assocLogS1_ConItemExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_UE_assocLogS1_ConItemExtIEs (SztProtExtnField_UE_assocLogS1_ConItemExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs (SztProtExtnCont_UE_assocLogS1_ConItemExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztUE_assocLogS1_ConItem (SztUE_assocLogS1_ConItem *param, Buffer *mBuf);
extern S16 cmPkSztUEPagID (SztUEPagID *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnUESecurCapabilities_ExtIEsCls (Szt_ExtnUESecurCapabilities_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_UESecurCapabilities_ExtIEs (SztProtExtnField_UESecurCapabilities_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_UESecurCapabilities_ExtIEs (SztProtExtnCont_UESecurCapabilities_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztUESecurCapabilities (SztUESecurCapabilities *param, Buffer *mBuf);
extern S16 cmPkSztWarningAreaLst (SztWarningAreaLst *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrReqdIEsCls (Szt_ValueHovrReqdIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrReqdIEs (SztProtIE_Field_HovrReqdIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrReqdIEs (SztProtIE_Cont_HovrReqdIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrReqd (SztHovrReqd *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls (Szt_ExtnE_RABDataFwdingItem_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABDataFwdingItem_ExtIEs (SztProtExtnField_E_RABDataFwdingItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs (SztProtExtnCont_E_RABDataFwdingItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABDataFwdingItem (SztE_RABDataFwdingItem *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABDataFwdingItemIEsCls (Szt_ValueE_RABDataFwdingItemIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABDataFwdingItemIEs (SztProtIE_Field_E_RABDataFwdingItemIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_ContLst_E_RABDataFwdingItemIEs (SztProtIE_ContLst_E_RABDataFwdingItemIEs *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrCmmdIEsCls (Szt_ValueHovrCmmdIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrCmmdIEs (SztProtIE_Field_HovrCmmdIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrCmmdIEs (SztProtIE_Cont_HovrCmmdIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrCmmd (SztHovrCmmd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrPrepFailIEsCls (Szt_ValueHovrPrepFailIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrPrepFailIEs (SztProtIE_Field_HovrPrepFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrPrepFailIEs (SztProtIE_Cont_HovrPrepFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrPrepFail (SztHovrPrepFail *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls (Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs (SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs (SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeSetupItemHOReq (SztE_RABToBeSetupItemHOReq *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABToBeSetupItemHOReqIEsCls (Szt_ValueE_RABToBeSetupItemHOReqIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs (SztProtIE_Field_E_RABToBeSetupItemHOReqIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs (SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrRqstIEsCls (Szt_ValueHovrRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrRqstIEs (SztProtIE_Field_HovrRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrRqstIEs (SztProtIE_Cont_HovrRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrRqst (SztHovrRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABAdmtdItem_ExtIEsCls (Szt_ExtnE_RABAdmtdItem_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABAdmtdItem_ExtIEs (SztProtExtnField_E_RABAdmtdItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABAdmtdItem_ExtIEs (SztProtExtnCont_E_RABAdmtdItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABAdmtdItem (SztE_RABAdmtdItem *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABAdmtdItemIEsCls (Szt_ValueE_RABAdmtdItemIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABAdmtdItemIEs (SztProtIE_Field_E_RABAdmtdItemIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_ContLst_E_RABAdmtdItemIEs (SztProtIE_ContLst_E_RABAdmtdItemIEs *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls (Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs (SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs (SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABFailedToSetupItemHOReqAck (SztE_RABFailedToSetupItemHOReqAck *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls (Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs (SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs (SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrRqstAckgIEsCls (Szt_ValueHovrRqstAckgIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrRqstAckgIEs (SztProtIE_Field_HovrRqstAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrRqstAckgIEs (SztProtIE_Cont_HovrRqstAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrRqstAckg (SztHovrRqstAckg *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrFailIEsCls (Szt_ValueHovrFailIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrFailIEs (SztProtIE_Field_HovrFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrFailIEs (SztProtIE_Cont_HovrFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrFail (SztHovrFail *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrNtfyIEsCls (Szt_ValueHovrNtfyIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrNtfyIEs (SztProtIE_Field_HovrNtfyIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrNtfyIEs (SztProtIE_Cont_HovrNtfyIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrNtfy (SztHovrNtfy *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls (Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs (SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs (SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeSwedDLItem (SztE_RABToBeSwedDLItem *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABToBeSwedDLItemIEsCls (Szt_ValueE_RABToBeSwedDLItemIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABToBeSwedDLItemIEs (SztProtIE_Field_E_RABToBeSwedDLItemIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs (SztProtIE_ContLst_E_RABToBeSwedDLItemIEs *param, Buffer *mBuf);
extern S16 cmPkSzt_ValuePathSwRqstIEsCls (Szt_ValuePathSwRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_PathSwRqstIEs (SztProtIE_Field_PathSwRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_PathSwRqstIEs (SztProtIE_Cont_PathSwRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztPathSwRqst (SztPathSwRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls (Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs (SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs (SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeSwedULItem (SztE_RABToBeSwedULItem *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABToBeSwedULItemIEsCls (Szt_ValueE_RABToBeSwedULItemIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABToBeSwedULItemIEs (SztProtIE_Field_E_RABToBeSwedULItemIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_ContLst_E_RABToBeSwedULItemIEs (SztProtIE_ContLst_E_RABToBeSwedULItemIEs *param, Buffer *mBuf);
extern S16 cmPkSzt_ValuePathSwRqstAckgIEsCls (Szt_ValuePathSwRqstAckgIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_PathSwRqstAckgIEs (SztProtIE_Field_PathSwRqstAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_PathSwRqstAckgIEs (SztProtIE_Cont_PathSwRqstAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztPathSwRqstAckg (SztPathSwRqstAckg *param, Buffer *mBuf);
extern S16 cmPkSzt_ValuePathSwRqstFailIEsCls (Szt_ValuePathSwRqstFailIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_PathSwRqstFailIEs (SztProtIE_Field_PathSwRqstFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_PathSwRqstFailIEs (SztProtIE_Cont_PathSwRqstFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztPathSwRqstFail (SztPathSwRqstFail *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrCancelIEsCls (Szt_ValueHovrCancelIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrCancelIEs (SztProtIE_Field_HovrCancelIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrCancelIEs (SztProtIE_Cont_HovrCancelIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrCancel (SztHovrCancel *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueHovrCancelAckgIEsCls (Szt_ValueHovrCancelAckgIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_HovrCancelAckgIEs (SztProtIE_Field_HovrCancelAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_HovrCancelAckgIEs (SztProtIE_Cont_HovrCancelAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztHovrCancelAckg (SztHovrCancelAckg *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls (Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs (SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs (SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeSetupItemBrSUReq (SztE_RABToBeSetupItemBrSUReq *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls (Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs (SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeSetupLstBrSUReq (SztE_RABToBeSetupLstBrSUReq *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABSetupRqstIEsCls (Szt_ValueE_RABSetupRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABSetupRqstIEs (SztProtIE_Field_E_RABSetupRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_E_RABSetupRqstIEs (SztProtIE_Cont_E_RABSetupRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABSetupRqst (SztE_RABSetupRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls (Szt_ExtnE_RABSetupItemBrSUResExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABSetupItemBrSUResExtIEs (SztProtExtnField_E_RABSetupItemBrSUResExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs (SztProtExtnCont_E_RABSetupItemBrSUResExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABSetupItemBrSURes (SztE_RABSetupItemBrSURes *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABSetupItemBrSUResIEsCls (Szt_ValueE_RABSetupItemBrSUResIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABSetupItemBrSUResIEs (SztProtIE_Field_E_RABSetupItemBrSUResIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABSetupLstBrSURes (SztE_RABSetupLstBrSURes *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABSetupRespIEsCls (Szt_ValueE_RABSetupRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABSetupRespIEs (SztProtIE_Field_E_RABSetupRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_E_RABSetupRespIEs (SztProtIE_Cont_E_RABSetupRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABSetupResp (SztE_RABSetupResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls (Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs (SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs (SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeMdfdItemBrModReq (SztE_RABToBeMdfdItemBrModReq *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls (Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs (SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeMdfdLstBrModReq (SztE_RABToBeMdfdLstBrModReq *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABMdfyRqstIEsCls (Szt_ValueE_RABMdfyRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABMdfyRqstIEs (SztProtIE_Field_E_RABMdfyRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_E_RABMdfyRqstIEs (SztProtIE_Cont_E_RABMdfyRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABMdfyRqst (SztE_RABMdfyRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls (Szt_ExtnE_RABMdfyItemBrModResExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABMdfyItemBrModResExtIEs (SztProtExtnField_E_RABMdfyItemBrModResExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs (SztProtExtnCont_E_RABMdfyItemBrModResExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABMdfyItemBrModRes (SztE_RABMdfyItemBrModRes *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABMdfyItemBrModResIEsCls (Szt_ValueE_RABMdfyItemBrModResIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABMdfyItemBrModResIEs (SztProtIE_Field_E_RABMdfyItemBrModResIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABMdfyLstBrModRes (SztE_RABMdfyLstBrModRes *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABMdfyRespIEsCls (Szt_ValueE_RABMdfyRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABMdfyRespIEs (SztProtIE_Field_E_RABMdfyRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_E_RABMdfyRespIEs (SztProtIE_Cont_E_RABMdfyRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABMdfyResp (SztE_RABMdfyResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABRlsCmmdIEsCls (Szt_ValueE_RABRlsCmmdIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABRlsCmmdIEs (SztProtIE_Field_E_RABRlsCmmdIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_E_RABRlsCmmdIEs (SztProtIE_Cont_E_RABRlsCmmdIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABRlsCmmd (SztE_RABRlsCmmd *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls (Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs (SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs (SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABRlsItemBrRelComp (SztE_RABRlsItemBrRelComp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABRlsItemBrRelCompIEsCls (Szt_ValueE_RABRlsItemBrRelCompIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABRlsItemBrRelCompIEs (SztProtIE_Field_E_RABRlsItemBrRelCompIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABRlsLstBrRelComp (SztE_RABRlsLstBrRelComp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABRlsRespIEsCls (Szt_ValueE_RABRlsRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABRlsRespIEs (SztProtIE_Field_E_RABRlsRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_E_RABRlsRespIEs (SztProtIE_Cont_E_RABRlsRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABRlsResp (SztE_RABRlsResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABRlsIndIEsCls (Szt_ValueE_RABRlsIndIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABRlsIndIEs (SztProtIE_Field_E_RABRlsIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_E_RABRlsIndIEs (SztProtIE_Cont_E_RABRlsIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABRlsInd (SztE_RABRlsInd *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls (Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs (SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs (SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeSetupItemCtxtSUReq (SztE_RABToBeSetupItemCtxtSUReq *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls (Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs (SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABToBeSetupLstCtxtSUReq (SztE_RABToBeSetupLstCtxtSUReq *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueInitCntxtSetupRqstIEsCls (Szt_ValueInitCntxtSetupRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_InitCntxtSetupRqstIEs (SztProtIE_Field_InitCntxtSetupRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_InitCntxtSetupRqstIEs (SztProtIE_Cont_InitCntxtSetupRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztInitCntxtSetupRqst (SztInitCntxtSetupRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls (Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs (SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs (SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABSetupItemCtxtSURes (SztE_RABSetupItemCtxtSURes *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueE_RABSetupItemCtxtSUResIEsCls (Szt_ValueE_RABSetupItemCtxtSUResIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs (SztProtIE_Field_E_RABSetupItemCtxtSUResIEs *param, Buffer *mBuf);
extern S16 cmPkSztE_RABSetupLstCtxtSURes (SztE_RABSetupLstCtxtSURes *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueInitCntxtSetupRespIEsCls (Szt_ValueInitCntxtSetupRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_InitCntxtSetupRespIEs (SztProtIE_Field_InitCntxtSetupRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_InitCntxtSetupRespIEs (SztProtIE_Cont_InitCntxtSetupRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztInitCntxtSetupResp (SztInitCntxtSetupResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueInitCntxtSetupFailIEsCls (Szt_ValueInitCntxtSetupFailIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_InitCntxtSetupFailIEs (SztProtIE_Field_InitCntxtSetupFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_InitCntxtSetupFailIEs (SztProtIE_Cont_InitCntxtSetupFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztInitCntxtSetupFail (SztInitCntxtSetupFail *param, Buffer *mBuf);
extern S16 cmPkSzt_ExtnTAIItemExtIEsCls (Szt_ExtnTAIItemExtIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtExtnField_TAIItemExtIEs (SztProtExtnField_TAIItemExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtExtnCont_TAIItemExtIEs (SztProtExtnCont_TAIItemExtIEs *param, Buffer *mBuf);
extern S16 cmPkSztTAIItem (SztTAIItem *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueTAIItemIEsCls (Szt_ValueTAIItemIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_TAIItemIEs (SztProtIE_Field_TAIItemIEs *param, Buffer *mBuf);
extern S16 cmPkSztTAILst (SztTAILst *param, Buffer *mBuf);
extern S16 cmPkSzt_ValuePagIEsCls (Szt_ValuePagIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_PagIEs (SztProtIE_Field_PagIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_PagIEs (SztProtIE_Cont_PagIEs *param, Buffer *mBuf);
extern S16 cmPkSztPag (SztPag *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUECntxtRlsRqst_IEsCls (Szt_ValueUECntxtRlsRqst_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UECntxtRlsRqst_IEs (SztProtIE_Field_UECntxtRlsRqst_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UECntxtRlsRqst_IEs (SztProtIE_Cont_UECntxtRlsRqst_IEs *param, Buffer *mBuf);
extern S16 cmPkSztUECntxtRlsRqst (SztUECntxtRlsRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUECntxtRlsCmmd_IEsCls (Szt_ValueUECntxtRlsCmmd_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UECntxtRlsCmmd_IEs (SztProtIE_Field_UECntxtRlsCmmd_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UECntxtRlsCmmd_IEs (SztProtIE_Cont_UECntxtRlsCmmd_IEs *param, Buffer *mBuf);
extern S16 cmPkSztUECntxtRlsCmmd (SztUECntxtRlsCmmd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUECntxtRlsComplete_IEsCls (Szt_ValueUECntxtRlsComplete_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UECntxtRlsComplete_IEs (SztProtIE_Field_UECntxtRlsComplete_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UECntxtRlsComplete_IEs (SztProtIE_Cont_UECntxtRlsComplete_IEs *param, Buffer *mBuf);
extern S16 cmPkSztUECntxtRlsComplete (SztUECntxtRlsComplete *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUECntxtModificationRqstIEsCls (Szt_ValueUECntxtModificationRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UECntxtModificationRqstIEs (SztProtIE_Field_UECntxtModificationRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UECntxtModificationRqstIEs (SztProtIE_Cont_UECntxtModificationRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztUECntxtModificationRqst (SztUECntxtModificationRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUECntxtModificationRespIEsCls (Szt_ValueUECntxtModificationRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UECntxtModificationRespIEs (SztProtIE_Field_UECntxtModificationRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UECntxtModificationRespIEs (SztProtIE_Cont_UECntxtModificationRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztUECntxtModificationResp (SztUECntxtModificationResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUECntxtModificationFailIEsCls (Szt_ValueUECntxtModificationFailIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UECntxtModificationFailIEs (SztProtIE_Field_UECntxtModificationFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UECntxtModificationFailIEs (SztProtIE_Cont_UECntxtModificationFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztUECntxtModificationFail (SztUECntxtModificationFail *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUERadioCapbltyMatchRqstIEsCls (Szt_ValueUERadioCapbltyMatchRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UERadioCapbltyMatchRqstIEs (SztProtIE_Field_UERadioCapbltyMatchRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs (SztProtIE_Cont_UERadioCapbltyMatchRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztUERadioCapbltyMatchRqst (SztUERadioCapbltyMatchRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUERadioCapbltyMatchRespIEsCls (Szt_ValueUERadioCapbltyMatchRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UERadioCapbltyMatchRespIEs (SztProtIE_Field_UERadioCapbltyMatchRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UERadioCapbltyMatchRespIEs (SztProtIE_Cont_UERadioCapbltyMatchRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztUERadioCapbltyMatchResp (SztUERadioCapbltyMatchResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueDlnkNASTport_IEsCls (Szt_ValueDlnkNASTport_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_DlnkNASTport_IEs (SztProtIE_Field_DlnkNASTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_DlnkNASTport_IEs (SztProtIE_Cont_DlnkNASTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztDlnkNASTport (SztDlnkNASTport *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueInitUEMsg_IEsCls (Szt_ValueInitUEMsg_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_InitUEMsg_IEs (SztProtIE_Field_InitUEMsg_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_InitUEMsg_IEs (SztProtIE_Cont_InitUEMsg_IEs *param, Buffer *mBuf);
extern S16 cmPkSztInitUEMsg (SztInitUEMsg *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUlnkNASTport_IEsCls (Szt_ValueUlnkNASTport_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UlnkNASTport_IEs (SztProtIE_Field_UlnkNASTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UlnkNASTport_IEs (SztProtIE_Cont_UlnkNASTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztUlnkNASTport (SztUlnkNASTport *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueNASNonDlvryInd_IEsCls (Szt_ValueNASNonDlvryInd_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_NASNonDlvryInd_IEs (SztProtIE_Field_NASNonDlvryInd_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_NASNonDlvryInd_IEs (SztProtIE_Cont_NASNonDlvryInd_IEs *param, Buffer *mBuf);
extern S16 cmPkSztNASNonDlvryInd (SztNASNonDlvryInd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUE_assocLogS1_ConItemResCls (Szt_ValueUE_assocLogS1_ConItemResCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UE_assocLogS1_ConItemRes (SztProtIE_Field_UE_assocLogS1_ConItemRes *param, Buffer *mBuf);
extern S16 cmPkSztUE_assocLogS1_ConLstRes (SztUE_assocLogS1_ConLstRes *param, Buffer *mBuf);
extern S16 cmPkSztResetTyp (SztResetTyp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueResetIEsCls (Szt_ValueResetIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ResetIEs (SztProtIE_Field_ResetIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ResetIEs (SztProtIE_Cont_ResetIEs *param, Buffer *mBuf);
extern S16 cmPkSztReset (SztReset *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUE_assocLogS1_ConItemResAckCls (Szt_ValueUE_assocLogS1_ConItemResAckCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UE_assocLogS1_ConItemResAck (SztProtIE_Field_UE_assocLogS1_ConItemResAck *param, Buffer *mBuf);
extern S16 cmPkSztUE_assocLogS1_ConLstResAck (SztUE_assocLogS1_ConLstResAck *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueResetAckgIEsCls (Szt_ValueResetAckgIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ResetAckgIEs (SztProtIE_Field_ResetAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ResetAckgIEs (SztProtIE_Cont_ResetAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztResetAckg (SztResetAckg *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueErrIndIEsCls (Szt_ValueErrIndIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ErrIndIEs (SztProtIE_Field_ErrIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ErrIndIEs (SztProtIE_Cont_ErrIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztErrInd (SztErrInd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueS1SetupRqstIEsCls (Szt_ValueS1SetupRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_S1SetupRqstIEs (SztProtIE_Field_S1SetupRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_S1SetupRqstIEs (SztProtIE_Cont_S1SetupRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztS1SetupRqst (SztS1SetupRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueS1SetupRespIEsCls (Szt_ValueS1SetupRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_S1SetupRespIEs (SztProtIE_Field_S1SetupRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_S1SetupRespIEs (SztProtIE_Cont_S1SetupRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztS1SetupResp (SztS1SetupResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueS1SetupFailIEsCls (Szt_ValueS1SetupFailIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_S1SetupFailIEs (SztProtIE_Field_S1SetupFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_S1SetupFailIEs (SztProtIE_Cont_S1SetupFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztS1SetupFail (SztS1SetupFail *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueENBConfigUpdIEsCls (Szt_ValueENBConfigUpdIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ENBConfigUpdIEs (SztProtIE_Field_ENBConfigUpdIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ENBConfigUpdIEs (SztProtIE_Cont_ENBConfigUpdIEs *param, Buffer *mBuf);
extern S16 cmPkSztENBConfigUpd (SztENBConfigUpd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueENBConfigUpdAckgIEsCls (Szt_ValueENBConfigUpdAckgIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ENBConfigUpdAckgIEs (SztProtIE_Field_ENBConfigUpdAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ENBConfigUpdAckgIEs (SztProtIE_Cont_ENBConfigUpdAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztENBConfigUpdAckg (SztENBConfigUpdAckg *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueENBConfigUpdFailIEsCls (Szt_ValueENBConfigUpdFailIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ENBConfigUpdFailIEs (SztProtIE_Field_ENBConfigUpdFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ENBConfigUpdFailIEs (SztProtIE_Cont_ENBConfigUpdFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztENBConfigUpdFail (SztENBConfigUpdFail *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueMMEConfigUpdIEsCls (Szt_ValueMMEConfigUpdIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_MMEConfigUpdIEs (SztProtIE_Field_MMEConfigUpdIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_MMEConfigUpdIEs (SztProtIE_Cont_MMEConfigUpdIEs *param, Buffer *mBuf);
extern S16 cmPkSztMMEConfigUpd (SztMMEConfigUpd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueMMEConfigUpdAckgIEsCls (Szt_ValueMMEConfigUpdAckgIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_MMEConfigUpdAckgIEs (SztProtIE_Field_MMEConfigUpdAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_MMEConfigUpdAckgIEs (SztProtIE_Cont_MMEConfigUpdAckgIEs *param, Buffer *mBuf);
extern S16 cmPkSztMMEConfigUpdAckg (SztMMEConfigUpdAckg *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueMMEConfigUpdFailIEsCls (Szt_ValueMMEConfigUpdFailIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_MMEConfigUpdFailIEs (SztProtIE_Field_MMEConfigUpdFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_MMEConfigUpdFailIEs (SztProtIE_Cont_MMEConfigUpdFailIEs *param, Buffer *mBuf);
extern S16 cmPkSztMMEConfigUpdFail (SztMMEConfigUpdFail *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueDlnkS1cdma2000tunnelingIEsCls (Szt_ValueDlnkS1cdma2000tunnelingIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs (SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs (SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *param, Buffer *mBuf);
extern S16 cmPkSztDlnkS1cdma2000tunneling (SztDlnkS1cdma2000tunneling *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUlnkS1cdma2000tunnelingIEsCls (Szt_ValueUlnkS1cdma2000tunnelingIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs (SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs (SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *param, Buffer *mBuf);
extern S16 cmPkSztUlnkS1cdma2000tunneling (SztUlnkS1cdma2000tunneling *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUECapbltyInfoIndIEsCls (Szt_ValueUECapbltyInfoIndIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UECapbltyInfoIndIEs (SztProtIE_Field_UECapbltyInfoIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UECapbltyInfoIndIEs (SztProtIE_Cont_UECapbltyInfoIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztUECapbltyInfoInd (SztUECapbltyInfoInd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueENBStatusTfrIEsCls (Szt_ValueENBStatusTfrIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ENBStatusTfrIEs (SztProtIE_Field_ENBStatusTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ENBStatusTfrIEs (SztProtIE_Cont_ENBStatusTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztENBStatusTfr (SztENBStatusTfr *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueMMEStatusTfrIEsCls (Szt_ValueMMEStatusTfrIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_MMEStatusTfrIEs (SztProtIE_Field_MMEStatusTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_MMEStatusTfrIEs (SztProtIE_Cont_MMEStatusTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztMMEStatusTfr (SztMMEStatusTfr *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueTraceStartIEsCls (Szt_ValueTraceStartIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_TraceStartIEs (SztProtIE_Field_TraceStartIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_TraceStartIEs (SztProtIE_Cont_TraceStartIEs *param, Buffer *mBuf);
extern S16 cmPkSztTraceStart (SztTraceStart *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueTraceFailIndIEsCls (Szt_ValueTraceFailIndIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_TraceFailIndIEs (SztProtIE_Field_TraceFailIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_TraceFailIndIEs (SztProtIE_Cont_TraceFailIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztTraceFailInd (SztTraceFailInd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueDeactvTraceIEsCls (Szt_ValueDeactvTraceIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_DeactvTraceIEs (SztProtIE_Field_DeactvTraceIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_DeactvTraceIEs (SztProtIE_Cont_DeactvTraceIEs *param, Buffer *mBuf);
extern S16 cmPkSztDeactvTrace (SztDeactvTrace *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueCellTrafficTraceIEsCls (Szt_ValueCellTrafficTraceIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_CellTrafficTraceIEs (SztProtIE_Field_CellTrafficTraceIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_CellTrafficTraceIEs (SztProtIE_Cont_CellTrafficTraceIEs *param, Buffer *mBuf);
extern S16 cmPkSztCellTrafficTrace (SztCellTrafficTrace *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueLocRprtngCntrlIEsCls (Szt_ValueLocRprtngCntrlIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_LocRprtngCntrlIEs (SztProtIE_Field_LocRprtngCntrlIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_LocRprtngCntrlIEs (SztProtIE_Cont_LocRprtngCntrlIEs *param, Buffer *mBuf);
extern S16 cmPkSztLocRprtngCntrl (SztLocRprtngCntrl *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueLocRprtngFailIndIEsCls (Szt_ValueLocRprtngFailIndIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_LocRprtngFailIndIEs (SztProtIE_Field_LocRprtngFailIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_LocRprtngFailIndIEs (SztProtIE_Cont_LocRprtngFailIndIEs *param, Buffer *mBuf);
extern S16 cmPkSztLocRprtngFailInd (SztLocRprtngFailInd *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueLocReportIEsCls (Szt_ValueLocReportIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_LocReportIEs (SztProtIE_Field_LocReportIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_LocReportIEs (SztProtIE_Cont_LocReportIEs *param, Buffer *mBuf);
extern S16 cmPkSztLocReport (SztLocReport *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueOverloadStartIEsCls (Szt_ValueOverloadStartIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_OverloadStartIEs (SztProtIE_Field_OverloadStartIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_OverloadStartIEs (SztProtIE_Cont_OverloadStartIEs *param, Buffer *mBuf);
extern S16 cmPkSztOverloadStart (SztOverloadStart *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueOverloadStopIEsCls (Szt_ValueOverloadStopIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_OverloadStopIEs (SztProtIE_Field_OverloadStopIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_OverloadStopIEs (SztProtIE_Cont_OverloadStopIEs *param, Buffer *mBuf);
extern S16 cmPkSztOverloadStop (SztOverloadStop *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueWriteReplaceWarningRqstIEsCls (Szt_ValueWriteReplaceWarningRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_WriteReplaceWarningRqstIEs (SztProtIE_Field_WriteReplaceWarningRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_WriteReplaceWarningRqstIEs (SztProtIE_Cont_WriteReplaceWarningRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztWriteReplaceWarningRqst (SztWriteReplaceWarningRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueWriteReplaceWarningRespIEsCls (Szt_ValueWriteReplaceWarningRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_WriteReplaceWarningRespIEs (SztProtIE_Field_WriteReplaceWarningRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_WriteReplaceWarningRespIEs (SztProtIE_Cont_WriteReplaceWarningRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztWriteReplaceWarningResp (SztWriteReplaceWarningResp *param, Buffer *mBuf);
extern S16 cmPkSztInter_SystemInformTfrTyp (SztInter_SystemInformTfrTyp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueENBDirectInformTfrIEsCls (Szt_ValueENBDirectInformTfrIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ENBDirectInformTfrIEs (SztProtIE_Field_ENBDirectInformTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ENBDirectInformTfrIEs (SztProtIE_Cont_ENBDirectInformTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztENBDirectInformTfr (SztENBDirectInformTfr *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueMMEDirectInformTfrIEsCls (Szt_ValueMMEDirectInformTfrIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_MMEDirectInformTfrIEs (SztProtIE_Field_MMEDirectInformTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_MMEDirectInformTfrIEs (SztProtIE_Cont_MMEDirectInformTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztMMEDirectInformTfr (SztMMEDirectInformTfr *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueENBConfigTfrIEsCls (Szt_ValueENBConfigTfrIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_ENBConfigTfrIEs (SztProtIE_Field_ENBConfigTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_ENBConfigTfrIEs (SztProtIE_Cont_ENBConfigTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztENBConfigTfr (SztENBConfigTfr *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueMMEConfigTfrIEsCls (Szt_ValueMMEConfigTfrIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_MMEConfigTfrIEs (SztProtIE_Field_MMEConfigTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_MMEConfigTfrIEs (SztProtIE_Cont_MMEConfigTfrIEs *param, Buffer *mBuf);
extern S16 cmPkSztMMEConfigTfr (SztMMEConfigTfr *param, Buffer *mBuf);
extern S16 cmPkSzt_ValuePrivMsgIEsCls (Szt_ValuePrivMsgIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztPrivIE_Field_PrivMsgIEs (SztPrivIE_Field_PrivMsgIEs *param, Buffer *mBuf);
extern S16 cmPkSztPrivIE_Cont_PrivMsgIEs (SztPrivIE_Cont_PrivMsgIEs *param, Buffer *mBuf);
extern S16 cmPkSztPrivMsg (SztPrivMsg *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueKillRqstIEsCls (Szt_ValueKillRqstIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_KillRqstIEs (SztProtIE_Field_KillRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_KillRqstIEs (SztProtIE_Cont_KillRqstIEs *param, Buffer *mBuf);
extern S16 cmPkSztKillRqst (SztKillRqst *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueKillRespIEsCls (Szt_ValueKillRespIEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_KillRespIEs (SztProtIE_Field_KillRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_KillRespIEs (SztProtIE_Cont_KillRespIEs *param, Buffer *mBuf);
extern S16 cmPkSztKillResp (SztKillResp *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls (Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs (SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs (SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztDlnkUEAssociatedLPPaTport (SztDlnkUEAssociatedLPPaTport *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls (Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs (SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs (SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztUlnkUEAssociatedLPPaTport (SztUlnkUEAssociatedLPPaTport *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls (Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs (SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs (SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztDlnkNonUEAssociatedLPPaTport (SztDlnkNonUEAssociatedLPPaTport *param, Buffer *mBuf);
extern S16 cmPkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls (Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs (SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs (SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs *param, Buffer *mBuf);
extern S16 cmPkSztUlnkNonUEAssociatedLPPaTport (SztUlnkNonUEAssociatedLPPaTport *param, Buffer *mBuf);
extern S16 cmPkSzt_InitiatingMsgCls (Szt_InitiatingMsgCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztInitiatingMsg (SztInitiatingMsg *param, Buffer *mBuf);
extern S16 cmPkSzt_SuccessfulOutcomeCls (Szt_SuccessfulOutcomeCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztSuccessfulOutcome (SztSuccessfulOutcome *param, Buffer *mBuf);
extern S16 cmPkSzt_UnsuccessfulOutcomeCls (Szt_UnsuccessfulOutcomeCls *param, U32 val, Buffer *mBuf);
extern S16 cmPkSztUnsuccessfulOutcome (SztUnsuccessfulOutcome *param, Buffer *mBuf);
extern S16 cmPkSztS1AP_PDU (SztS1AP_PDU *param, Buffer *mBuf);
extern S16 cmUnpkSztPrivIE_ID (SztPrivIE_ID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnEUTRAN_CGI_ExtIEsCls (Szt_ExtnEUTRAN_CGI_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_EUTRAN_CGI_ExtIEs (SztProtExtnField_EUTRAN_CGI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_EUTRAN_CGI_ExtIEs (SztProtExtnCont_EUTRAN_CGI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztEUTRAN_CGI (SztEUTRAN_CGI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCellIdLstforMDT (SztCellIdLstforMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCellBasedMDT_ExtIEsCls (Szt_ExtnCellBasedMDT_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CellBasedMDT_ExtIEs (SztProtExtnField_CellBasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CellBasedMDT_ExtIEs (SztProtExtnCont_CellBasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCellBasedMDT (SztCellBasedMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTALstforMDT (SztTALstforMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTABasedMDT_ExtIEsCls (Szt_ExtnTABasedMDT_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TABasedMDT_ExtIEs (SztProtExtnField_TABasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TABasedMDT_ExtIEs (SztProtExtnCont_TABasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTABasedMDT (SztTABasedMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTAI_ExtIEsCls (Szt_ExtnTAI_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TAI_ExtIEs (SztProtExtnField_TAI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TAI_ExtIEs (SztProtExtnCont_TAI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAI (SztTAI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAILstforMDT (SztTAILstforMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTAIBasedMDT_ExtIEsCls (Szt_ExtnTAIBasedMDT_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TAIBasedMDT_ExtIEs (SztProtExtnField_TAIBasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TAIBasedMDT_ExtIEs (SztProtExtnCont_TAIBasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAIBasedMDT (SztTAIBasedMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztAreaScopeOfMDT (SztAreaScopeOfMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls (Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs (SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs (SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztAllocnAndRetentionPriority (SztAllocnAndRetentionPriority *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCOUNTvalue_ExtIEsCls (Szt_ExtnCOUNTvalue_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_COUNTvalue_ExtIEs (SztProtExtnField_COUNTvalue_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_COUNTvalue_ExtIEs (SztProtExtnCont_COUNTvalue_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCOUNTvalue (SztCOUNTvalue *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCOUNTValueExtended_ExtIEsCls (Szt_ExtnCOUNTValueExtended_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_COUNTValueExtended_ExtIEs (SztProtExtnField_COUNTValueExtended_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_COUNTValueExtended_ExtIEs (SztProtExtnCont_COUNTValueExtended_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCOUNTValueExtended (SztCOUNTValueExtended *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls (Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs (SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs (SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztBrs_SubjToStatusTfr_Item (SztBrs_SubjToStatusTfr_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls (Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs (SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztBrs_SubjToStatusTfrLst (SztBrs_SubjToStatusTfrLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztBPLMNs (SztBPLMNs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls (Szt_ExtnCellID_Cancelled_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CellID_Cancelled_Item_ExtIEs (SztProtExtnField_CellID_Cancelled_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs (SztProtExtnCont_CellID_Cancelled_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCellID_Cancelled_Item (SztCellID_Cancelled_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCellID_Cancelled (SztCellID_Cancelled *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls (Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs (SztProtExtnField_CancelledCellinTAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs (SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCancelledCellinTAI_Item (SztCancelledCellinTAI_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCancelledCellinTAI (SztCancelledCellinTAI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls (Szt_ExtnTAI_Cancelled_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TAI_Cancelled_Item_ExtIEs (SztProtExtnField_TAI_Cancelled_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs (SztProtExtnCont_TAI_Cancelled_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAI_Cancelled_Item (SztTAI_Cancelled_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAI_Cancelled (SztTAI_Cancelled *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls (Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs (SztProtExtnField_CancelledCellinEAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs (SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCancelledCellinEAI_Item (SztCancelledCellinEAI_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCancelledCellinEAI (SztCancelledCellinEAI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls (Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs (SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs (SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztEmergencyAreaID_Cancelled_Item (SztEmergencyAreaID_Cancelled_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztEmergencyAreaID_Cancelled (SztEmergencyAreaID_Cancelled *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztBroadcastCancelledAreaLst (SztBroadcastCancelledAreaLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls (Szt_ExtnCellID_Broadcast_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CellID_Broadcast_Item_ExtIEs (SztProtExtnField_CellID_Broadcast_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs (SztProtExtnCont_CellID_Broadcast_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCellID_Broadcast_Item (SztCellID_Broadcast_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCellID_Broadcast (SztCellID_Broadcast *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls (Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs (SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs (SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCompletedCellinTAI_Item (SztCompletedCellinTAI_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCompletedCellinTAI (SztCompletedCellinTAI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls (Szt_ExtnTAI_Broadcast_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TAI_Broadcast_Item_ExtIEs (SztProtExtnField_TAI_Broadcast_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs (SztProtExtnCont_TAI_Broadcast_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAI_Broadcast_Item (SztTAI_Broadcast_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAI_Broadcast (SztTAI_Broadcast *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls (Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs (SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs (SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCompletedCellinEAI_Item (SztCompletedCellinEAI_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCompletedCellinEAI (SztCompletedCellinEAI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls (Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs (SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs (SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztEmergencyAreaID_Broadcast_Item (SztEmergencyAreaID_Broadcast_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztEmergencyAreaID_Broadcast (SztEmergencyAreaID_Broadcast *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztBroadcastCompletedAreaLst (SztBroadcastCompletedAreaLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCause (SztCause *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls (Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs (SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs (SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCdma2000OneXSRVCCInfo (SztCdma2000OneXSRVCCInfo *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCellTyp_ExtIEsCls (Szt_ExtnCellTyp_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CellTyp_ExtIEs (SztProtExtnField_CellTyp_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CellTyp_ExtIEs (SztProtExtnCont_CellTyp_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCellTyp (SztCellTyp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCGI_ExtIEsCls (Szt_ExtnCGI_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CGI_ExtIEs (SztProtExtnField_CGI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CGI_ExtIEs (SztProtExtnCont_CGI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCGI (SztCGI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCSG_IdLst_Item_ExtIEsCls (Szt_ExtnCSG_IdLst_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CSG_IdLst_Item_ExtIEs (SztProtExtnField_CSG_IdLst_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CSG_IdLst_Item_ExtIEs (SztProtExtnCont_CSG_IdLst_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCSG_IdLst_Item (SztCSG_IdLst_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCSG_IdLst (SztCSG_IdLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls (Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs (SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs (SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCriticalityDiag_IE_Item (SztCriticalityDiag_IE_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCriticalityDiag_IE_Lst (SztCriticalityDiag_IE_Lst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnCriticalityDiag_ExtIEsCls (Szt_ExtnCriticalityDiag_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_CriticalityDiag_ExtIEs (SztProtExtnField_CriticalityDiag_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_CriticalityDiag_ExtIEs (SztProtExtnCont_CriticalityDiag_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCriticalityDiag (SztCriticalityDiag *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztECGILst (SztECGILst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztEmergencyAreaIDLst (SztEmergencyAreaIDLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENB_ID (SztENB_ID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnLAI_ExtIEsCls (Szt_ExtnLAI_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_LAI_ExtIEs (SztProtExtnField_LAI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_LAI_ExtIEs (SztProtExtnCont_LAI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztLAI (SztLAI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnGERAN_Cell_ID_ExtIEsCls (Szt_ExtnGERAN_Cell_ID_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_GERAN_Cell_ID_ExtIEs (SztProtExtnField_GERAN_Cell_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_GERAN_Cell_ID_ExtIEs (SztProtExtnCont_GERAN_Cell_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztGERAN_Cell_ID (SztGERAN_Cell_ID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnGlobalENB_ID_ExtIEsCls (Szt_ExtnGlobalENB_ID_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_GlobalENB_ID_ExtIEs (SztProtExtnField_GlobalENB_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_GlobalENB_ID_ExtIEs (SztProtExtnCont_GlobalENB_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztGlobal_ENB_ID (SztGlobal_ENB_ID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnGUMMEI_ExtIEsCls (Szt_ExtnGUMMEI_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_GUMMEI_ExtIEs (SztProtExtnField_GUMMEI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_GUMMEI_ExtIEs (SztProtExtnCont_GUMMEI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztGUMMEI (SztGUMMEI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztGUMMEILst (SztGUMMEILst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls (Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs (SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs (SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENB_StatusTfr_TprntCont (SztENB_StatusTfr_TprntCont *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBX2TLAs (SztENBX2TLAs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztEPLMNs (SztEPLMNs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABInformLstItem_ExtIEsCls (Szt_ExtnE_RABInformLstItem_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABInformLstItem_ExtIEs (SztProtExtnField_E_RABInformLstItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABInformLstItem_ExtIEs (SztProtExtnCont_E_RABInformLstItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABInformLstItem (SztE_RABInformLstItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABInformLstIEsCls (Szt_ValueE_RABInformLstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABInformLstIEs (SztProtIE_Field_E_RABInformLstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABInformLst (SztE_RABInformLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABItem_ExtIEsCls (Szt_ExtnE_RABItem_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABItem_ExtIEs (SztProtExtnField_E_RABItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABItem_ExtIEs (SztProtExtnCont_E_RABItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABItem (SztE_RABItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABItemIEsCls (Szt_ValueE_RABItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABItemIEs (SztProtIE_Field_E_RABItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABLst (SztE_RABLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnGBR_QosInform_ExtIEsCls (Szt_ExtnGBR_QosInform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_GBR_QosInform_ExtIEs (SztProtExtnField_GBR_QosInform_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_GBR_QosInform_ExtIEs (SztProtExtnCont_GBR_QosInform_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztGBR_QosInform (SztGBR_QosInform *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABQoSParams_ExtIEsCls (Szt_ExtnE_RABQoSParams_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABQoSParams_ExtIEs (SztProtExtnField_E_RABQoSParams_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABQoSParams_ExtIEs (SztProtExtnCont_E_RABQoSParams_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABLvlQoSParams (SztE_RABLvlQoSParams *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztForbiddenTACs (SztForbiddenTACs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnForbiddenTAs_Item_ExtIEsCls (Szt_ExtnForbiddenTAs_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_ForbiddenTAs_Item_ExtIEs (SztProtExtnField_ForbiddenTAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs (SztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztForbiddenTAs_Item (SztForbiddenTAs_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztForbiddenTAs (SztForbiddenTAs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztForbiddenLACs (SztForbiddenLACs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnForbiddenLAs_Item_ExtIEsCls (Szt_ExtnForbiddenLAs_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_ForbiddenLAs_Item_ExtIEs (SztProtExtnField_ForbiddenLAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs (SztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztForbiddenLAs_Item (SztForbiddenLAs_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztForbiddenLAs (SztForbiddenLAs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnHovrRestrnLst_ExtIEsCls (Szt_ExtnHovrRestrnLst_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_HovrRestrnLst_ExtIEs (SztProtExtnField_HovrRestrnLst_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_HovrRestrnLst_ExtIEs (SztProtExtnCont_HovrRestrnLst_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrRestrnLst (SztHovrRestrnLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMeasurementThresholdA2 (SztMeasurementThresholdA2 *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnM1ThresholdEventA2_ExtIEsCls (Szt_ExtnM1ThresholdEventA2_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_M1ThresholdEventA2_ExtIEs (SztProtExtnField_M1ThresholdEventA2_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_M1ThresholdEventA2_ExtIEs (SztProtExtnCont_M1ThresholdEventA2_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztM1ThresholdEventA2 (SztM1ThresholdEventA2 *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnM1PeriodicRprtng_ExtIEsCls (Szt_ExtnM1PeriodicRprtng_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_M1PeriodicRprtng_ExtIEs (SztProtExtnField_M1PeriodicRprtng_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_M1PeriodicRprtng_ExtIEs (SztProtExtnCont_M1PeriodicRprtng_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztM1PeriodicRprtng (SztM1PeriodicRprtng *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnM3Config_ExtIEsCls (Szt_ExtnM3Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_M3Config_ExtIEs (SztProtExtnField_M3Config_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_M3Config_ExtIEs (SztProtExtnCont_M3Config_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztM3Config (SztM3Config *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnM4Config_ExtIEsCls (Szt_ExtnM4Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_M4Config_ExtIEs (SztProtExtnField_M4Config_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_M4Config_ExtIEs (SztProtExtnCont_M4Config_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztM4Config (SztM4Config *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnM5Config_ExtIEsCls (Szt_ExtnM5Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_M5Config_ExtIEs (SztProtExtnField_M5Config_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_M5Config_ExtIEs (SztProtExtnCont_M5Config_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztM5Config (SztM5Config *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnImmediateMDT_ExtIEsCls (Szt_ExtnImmediateMDT_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_ImmediateMDT_ExtIEs (SztProtExtnField_ImmediateMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_ImmediateMDT_ExtIEs (SztProtExtnCont_ImmediateMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztImmediateMDT (SztImmediateMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls (Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs (SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs (SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztLastVisitedEUTRANCellInform (SztLastVisitedEUTRANCellInform *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztLastVisitedGERANCellInform (SztLastVisitedGERANCellInform *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztLastVisitedCell_Item (SztLastVisitedCell_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnLoggedMDT_ExtIEsCls (Szt_ExtnLoggedMDT_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_LoggedMDT_ExtIEs (SztProtExtnField_LoggedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_LoggedMDT_ExtIEs (SztProtExtnCont_LoggedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztLoggedMDT (SztLoggedMDT *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMDTMode (SztMDTMode *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMDTPLMNLst (SztMDTPLMNLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnMDT_Config_ExtIEsCls (Szt_ExtnMDT_Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_MDT_Config_ExtIEs (SztProtExtnField_MDT_Config_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_MDT_Config_ExtIEs (SztProtExtnCont_MDT_Config_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMDT_Config (SztMDT_Config *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztOverloadResp (SztOverloadResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnRqstTyp_ExtIEsCls (Szt_ExtnRqstTyp_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_RqstTyp_ExtIEs (SztProtExtnField_RqstTyp_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_RqstTyp_ExtIEs (SztProtExtnCont_RqstTyp_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztRqstTyp (SztRqstTyp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTgetRNC_ID_ExtIEsCls (Szt_ExtnTgetRNC_ID_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TgetRNC_ID_ExtIEs (SztProtExtnField_TgetRNC_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TgetRNC_ID_ExtIEs (SztProtExtnCont_TgetRNC_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTgetRNC_ID (SztTgetRNC_ID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztRIMRoutingAddr (SztRIMRoutingAddr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnRIMTfr_ExtIEsCls (Szt_ExtnRIMTfr_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_RIMTfr_ExtIEs (SztProtExtnField_RIMTfr_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_RIMTfr_ExtIEs (SztProtExtnCont_RIMTfr_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztRIMTfr (SztRIMTfr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnSecurCntxt_ExtIEsCls (Szt_ExtnSecurCntxt_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_SecurCntxt_ExtIEs (SztProtExtnField_SecurCntxt_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_SecurCntxt_ExtIEs (SztProtExtnCont_SecurCntxt_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSecurCntxt (SztSecurCntxt *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBX2GTPTLAs (SztENBX2GTPTLAs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnENBX2ExtTLA_ExtIEsCls (Szt_ExtnENBX2ExtTLA_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_ENBX2ExtTLA_ExtIEs (SztProtExtnField_ENBX2ExtTLA_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_ENBX2ExtTLA_ExtIEs (SztProtExtnCont_ENBX2ExtTLA_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBX2ExtTLA (SztENBX2ExtTLA *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBX2ExtTLAs (SztENBX2ExtTLAs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnX2TNLConfigInfo_ExtIEsCls (Szt_ExtnX2TNLConfigInfo_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_X2TNLConfigInfo_ExtIEs (SztProtExtnField_X2TNLConfigInfo_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_X2TNLConfigInfo_ExtIEs (SztProtExtnCont_X2TNLConfigInfo_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztX2TNLConfigInfo (SztX2TNLConfigInfo *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls (Szt_ExtnTimeSynchronizationInfo_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TimeSynchronizationInfo_ExtIEs (SztProtExtnField_TimeSynchronizationInfo_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs (SztProtExtnCont_TimeSynchronizationInfo_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTimeSynchronizationInfo (SztTimeSynchronizationInfo *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnSONInformReply_ExtIEsCls (Szt_ExtnSONInformReply_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_SONInformReply_ExtIEs (SztProtExtnField_SONInformReply_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_SONInformReply_ExtIEs (SztProtExtnCont_SONInformReply_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSONInformReply (SztSONInformReply *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSONInform (SztSONInform *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTgeteNB_ID_ExtIEsCls (Szt_ExtnTgeteNB_ID_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TgeteNB_ID_ExtIEs (SztProtExtnField_TgeteNB_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TgeteNB_ID_ExtIEs (SztProtExtnCont_TgeteNB_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTgeteNB_ID (SztTgeteNB_ID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnSrceNB_ID_ExtIEsCls (Szt_ExtnSrceNB_ID_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_SrceNB_ID_ExtIEs (SztProtExtnField_SrceNB_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_SrceNB_ID_ExtIEs (SztProtExtnCont_SrceNB_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSrceNB_ID (SztSrceNB_ID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnSONConfigTfr_ExtIEsCls (Szt_ExtnSONConfigTfr_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_SONConfigTfr_ExtIEs (SztProtExtnField_SONConfigTfr_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_SONConfigTfr_ExtIEs (SztProtExtnCont_SONConfigTfr_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSONConfigTfr (SztSONConfigTfr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUE_HistoryInform (SztUE_HistoryInform *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls (Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs (SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs (SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSrceNB_ToTgeteNB_TprntCont (SztSrceNB_ToTgeteNB_TprntCont *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSrvdPLMNs (SztSrvdPLMNs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSrvdGroupIDs (SztSrvdGroupIDs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSrvdMMECs (SztSrvdMMECs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls (Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs (SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs (SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSrvdGUMMEIsItem (SztSrvdGUMMEIsItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSrvdGUMMEIs (SztSrvdGUMMEIs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnSuppTAs_Item_ExtIEsCls (Szt_ExtnSuppTAs_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_SuppTAs_Item_ExtIEs (SztProtExtnField_SuppTAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_SuppTAs_Item_ExtIEs (SztProtExtnCont_SuppTAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSuppTAs_Item (SztSuppTAs_Item *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSuppTAs (SztSuppTAs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnS_TMSI_ExtIEsCls (Szt_ExtnS_TMSI_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_S_TMSI_ExtIEs (SztProtExtnField_S_TMSI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_S_TMSI_ExtIEs (SztProtExtnCont_S_TMSI_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztS_TMSI (SztS_TMSI *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAILstforWarning (SztTAILstforWarning *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTgetID (SztTgetID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls (Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs (SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs (SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTgeteNB_ToSrceNB_TprntCont (SztTgeteNB_ToSrceNB_TprntCont *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTraceActvn_ExtIEsCls (Szt_ExtnTraceActvn_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TraceActvn_ExtIEs (SztProtExtnField_TraceActvn_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TraceActvn_ExtIEs (SztProtExtnCont_TraceActvn_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTraceActvn (SztTraceActvn *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTunnel_Inform_ExtIEsCls (Szt_ExtnTunnel_Inform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_Tunnel_Inform_ExtIEs (SztProtExtnField_Tunnel_Inform_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_Tunnel_Inform_ExtIEs (SztProtExtnCont_Tunnel_Inform_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTunnelInform (SztTunnelInform *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls (Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs (SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs (SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUEAggMaxBitrate (SztUEAggMaxBitrate *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls (Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs (SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs (SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUE_S1AP_ID_pair (SztUE_S1AP_ID_pair *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUE_S1AP_IDs (SztUE_S1AP_IDs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls (Szt_ExtnUE_assocLogS1_ConItemExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_UE_assocLogS1_ConItemExtIEs (SztProtExtnField_UE_assocLogS1_ConItemExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs (SztProtExtnCont_UE_assocLogS1_ConItemExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUE_assocLogS1_ConItem (SztUE_assocLogS1_ConItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUEPagID (SztUEPagID *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnUESecurCapabilities_ExtIEsCls (Szt_ExtnUESecurCapabilities_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_UESecurCapabilities_ExtIEs (SztProtExtnField_UESecurCapabilities_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_UESecurCapabilities_ExtIEs (SztProtExtnCont_UESecurCapabilities_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUESecurCapabilities (SztUESecurCapabilities *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztWarningAreaLst (SztWarningAreaLst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrReqdIEsCls (Szt_ValueHovrReqdIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrReqdIEs (SztProtIE_Field_HovrReqdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrReqdIEs (SztProtIE_Cont_HovrReqdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrReqd (SztHovrReqd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls (Szt_ExtnE_RABDataFwdingItem_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABDataFwdingItem_ExtIEs (SztProtExtnField_E_RABDataFwdingItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs (SztProtExtnCont_E_RABDataFwdingItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABDataFwdingItem (SztE_RABDataFwdingItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABDataFwdingItemIEsCls (Szt_ValueE_RABDataFwdingItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABDataFwdingItemIEs (SztProtIE_Field_E_RABDataFwdingItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_ContLst_E_RABDataFwdingItemIEs (SztProtIE_ContLst_E_RABDataFwdingItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrCmmdIEsCls (Szt_ValueHovrCmmdIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrCmmdIEs (SztProtIE_Field_HovrCmmdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrCmmdIEs (SztProtIE_Cont_HovrCmmdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrCmmd (SztHovrCmmd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrPrepFailIEsCls (Szt_ValueHovrPrepFailIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrPrepFailIEs (SztProtIE_Field_HovrPrepFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrPrepFailIEs (SztProtIE_Cont_HovrPrepFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrPrepFail (SztHovrPrepFail *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls (Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs (SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs (SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeSetupItemHOReq (SztE_RABToBeSetupItemHOReq *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABToBeSetupItemHOReqIEsCls (Szt_ValueE_RABToBeSetupItemHOReqIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs (SztProtIE_Field_E_RABToBeSetupItemHOReqIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs (SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrRqstIEsCls (Szt_ValueHovrRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrRqstIEs (SztProtIE_Field_HovrRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrRqstIEs (SztProtIE_Cont_HovrRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrRqst (SztHovrRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABAdmtdItem_ExtIEsCls (Szt_ExtnE_RABAdmtdItem_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABAdmtdItem_ExtIEs (SztProtExtnField_E_RABAdmtdItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABAdmtdItem_ExtIEs (SztProtExtnCont_E_RABAdmtdItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABAdmtdItem (SztE_RABAdmtdItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABAdmtdItemIEsCls (Szt_ValueE_RABAdmtdItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABAdmtdItemIEs (SztProtIE_Field_E_RABAdmtdItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_ContLst_E_RABAdmtdItemIEs (SztProtIE_ContLst_E_RABAdmtdItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls (Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs (SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs (SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABFailedToSetupItemHOReqAck (SztE_RABFailedToSetupItemHOReqAck *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls (Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs (SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs (SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrRqstAckgIEsCls (Szt_ValueHovrRqstAckgIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrRqstAckgIEs (SztProtIE_Field_HovrRqstAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrRqstAckgIEs (SztProtIE_Cont_HovrRqstAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrRqstAckg (SztHovrRqstAckg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrFailIEsCls (Szt_ValueHovrFailIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrFailIEs (SztProtIE_Field_HovrFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrFailIEs (SztProtIE_Cont_HovrFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrFail (SztHovrFail *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrNtfyIEsCls (Szt_ValueHovrNtfyIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrNtfyIEs (SztProtIE_Field_HovrNtfyIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrNtfyIEs (SztProtIE_Cont_HovrNtfyIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrNtfy (SztHovrNtfy *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls (Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs (SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs (SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeSwedDLItem (SztE_RABToBeSwedDLItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABToBeSwedDLItemIEsCls (Szt_ValueE_RABToBeSwedDLItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABToBeSwedDLItemIEs (SztProtIE_Field_E_RABToBeSwedDLItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs (SztProtIE_ContLst_E_RABToBeSwedDLItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValuePathSwRqstIEsCls (Szt_ValuePathSwRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_PathSwRqstIEs (SztProtIE_Field_PathSwRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_PathSwRqstIEs (SztProtIE_Cont_PathSwRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztPathSwRqst (SztPathSwRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls (Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs (SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs (SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeSwedULItem (SztE_RABToBeSwedULItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABToBeSwedULItemIEsCls (Szt_ValueE_RABToBeSwedULItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABToBeSwedULItemIEs (SztProtIE_Field_E_RABToBeSwedULItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_ContLst_E_RABToBeSwedULItemIEs (SztProtIE_ContLst_E_RABToBeSwedULItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValuePathSwRqstAckgIEsCls (Szt_ValuePathSwRqstAckgIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_PathSwRqstAckgIEs (SztProtIE_Field_PathSwRqstAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_PathSwRqstAckgIEs (SztProtIE_Cont_PathSwRqstAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztPathSwRqstAckg (SztPathSwRqstAckg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValuePathSwRqstFailIEsCls (Szt_ValuePathSwRqstFailIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_PathSwRqstFailIEs (SztProtIE_Field_PathSwRqstFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_PathSwRqstFailIEs (SztProtIE_Cont_PathSwRqstFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztPathSwRqstFail (SztPathSwRqstFail *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrCancelIEsCls (Szt_ValueHovrCancelIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrCancelIEs (SztProtIE_Field_HovrCancelIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrCancelIEs (SztProtIE_Cont_HovrCancelIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrCancel (SztHovrCancel *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueHovrCancelAckgIEsCls (Szt_ValueHovrCancelAckgIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_HovrCancelAckgIEs (SztProtIE_Field_HovrCancelAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_HovrCancelAckgIEs (SztProtIE_Cont_HovrCancelAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztHovrCancelAckg (SztHovrCancelAckg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls (Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs (SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs (SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeSetupItemBrSUReq (SztE_RABToBeSetupItemBrSUReq *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls (Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs (SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeSetupLstBrSUReq (SztE_RABToBeSetupLstBrSUReq *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABSetupRqstIEsCls (Szt_ValueE_RABSetupRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABSetupRqstIEs (SztProtIE_Field_E_RABSetupRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_E_RABSetupRqstIEs (SztProtIE_Cont_E_RABSetupRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABSetupRqst (SztE_RABSetupRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls (Szt_ExtnE_RABSetupItemBrSUResExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABSetupItemBrSUResExtIEs (SztProtExtnField_E_RABSetupItemBrSUResExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs (SztProtExtnCont_E_RABSetupItemBrSUResExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABSetupItemBrSURes (SztE_RABSetupItemBrSURes *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABSetupItemBrSUResIEsCls (Szt_ValueE_RABSetupItemBrSUResIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABSetupItemBrSUResIEs (SztProtIE_Field_E_RABSetupItemBrSUResIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABSetupLstBrSURes (SztE_RABSetupLstBrSURes *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABSetupRespIEsCls (Szt_ValueE_RABSetupRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABSetupRespIEs (SztProtIE_Field_E_RABSetupRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_E_RABSetupRespIEs (SztProtIE_Cont_E_RABSetupRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABSetupResp (SztE_RABSetupResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls (Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs (SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs (SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeMdfdItemBrModReq (SztE_RABToBeMdfdItemBrModReq *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls (Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs (SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeMdfdLstBrModReq (SztE_RABToBeMdfdLstBrModReq *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABMdfyRqstIEsCls (Szt_ValueE_RABMdfyRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABMdfyRqstIEs (SztProtIE_Field_E_RABMdfyRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_E_RABMdfyRqstIEs (SztProtIE_Cont_E_RABMdfyRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABMdfyRqst (SztE_RABMdfyRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls (Szt_ExtnE_RABMdfyItemBrModResExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABMdfyItemBrModResExtIEs (SztProtExtnField_E_RABMdfyItemBrModResExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs (SztProtExtnCont_E_RABMdfyItemBrModResExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABMdfyItemBrModRes (SztE_RABMdfyItemBrModRes *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABMdfyItemBrModResIEsCls (Szt_ValueE_RABMdfyItemBrModResIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABMdfyItemBrModResIEs (SztProtIE_Field_E_RABMdfyItemBrModResIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABMdfyLstBrModRes (SztE_RABMdfyLstBrModRes *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABMdfyRespIEsCls (Szt_ValueE_RABMdfyRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABMdfyRespIEs (SztProtIE_Field_E_RABMdfyRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_E_RABMdfyRespIEs (SztProtIE_Cont_E_RABMdfyRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABMdfyResp (SztE_RABMdfyResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABRlsCmmdIEsCls (Szt_ValueE_RABRlsCmmdIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABRlsCmmdIEs (SztProtIE_Field_E_RABRlsCmmdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_E_RABRlsCmmdIEs (SztProtIE_Cont_E_RABRlsCmmdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABRlsCmmd (SztE_RABRlsCmmd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls (Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs (SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs (SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABRlsItemBrRelComp (SztE_RABRlsItemBrRelComp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABRlsItemBrRelCompIEsCls (Szt_ValueE_RABRlsItemBrRelCompIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABRlsItemBrRelCompIEs (SztProtIE_Field_E_RABRlsItemBrRelCompIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABRlsLstBrRelComp (SztE_RABRlsLstBrRelComp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABRlsRespIEsCls (Szt_ValueE_RABRlsRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABRlsRespIEs (SztProtIE_Field_E_RABRlsRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_E_RABRlsRespIEs (SztProtIE_Cont_E_RABRlsRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABRlsResp (SztE_RABRlsResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABRlsIndIEsCls (Szt_ValueE_RABRlsIndIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABRlsIndIEs (SztProtIE_Field_E_RABRlsIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_E_RABRlsIndIEs (SztProtIE_Cont_E_RABRlsIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABRlsInd (SztE_RABRlsInd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls (Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs (SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs (SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeSetupItemCtxtSUReq (SztE_RABToBeSetupItemCtxtSUReq *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls (Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs (SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABToBeSetupLstCtxtSUReq (SztE_RABToBeSetupLstCtxtSUReq *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueInitCntxtSetupRqstIEsCls (Szt_ValueInitCntxtSetupRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_InitCntxtSetupRqstIEs (SztProtIE_Field_InitCntxtSetupRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_InitCntxtSetupRqstIEs (SztProtIE_Cont_InitCntxtSetupRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztInitCntxtSetupRqst (SztInitCntxtSetupRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls (Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs (SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs (SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABSetupItemCtxtSURes (SztE_RABSetupItemCtxtSURes *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueE_RABSetupItemCtxtSUResIEsCls (Szt_ValueE_RABSetupItemCtxtSUResIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs (SztProtIE_Field_E_RABSetupItemCtxtSUResIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztE_RABSetupLstCtxtSURes (SztE_RABSetupLstCtxtSURes *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueInitCntxtSetupRespIEsCls (Szt_ValueInitCntxtSetupRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_InitCntxtSetupRespIEs (SztProtIE_Field_InitCntxtSetupRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_InitCntxtSetupRespIEs (SztProtIE_Cont_InitCntxtSetupRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztInitCntxtSetupResp (SztInitCntxtSetupResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueInitCntxtSetupFailIEsCls (Szt_ValueInitCntxtSetupFailIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_InitCntxtSetupFailIEs (SztProtIE_Field_InitCntxtSetupFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_InitCntxtSetupFailIEs (SztProtIE_Cont_InitCntxtSetupFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztInitCntxtSetupFail (SztInitCntxtSetupFail *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ExtnTAIItemExtIEsCls (Szt_ExtnTAIItemExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnField_TAIItemExtIEs (SztProtExtnField_TAIItemExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtExtnCont_TAIItemExtIEs (SztProtExtnCont_TAIItemExtIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAIItem (SztTAIItem *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueTAIItemIEsCls (Szt_ValueTAIItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_TAIItemIEs (SztProtIE_Field_TAIItemIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTAILst (SztTAILst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValuePagIEsCls (Szt_ValuePagIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_PagIEs (SztProtIE_Field_PagIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_PagIEs (SztProtIE_Cont_PagIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztPag (SztPag *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUECntxtRlsRqst_IEsCls (Szt_ValueUECntxtRlsRqst_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UECntxtRlsRqst_IEs (SztProtIE_Field_UECntxtRlsRqst_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UECntxtRlsRqst_IEs (SztProtIE_Cont_UECntxtRlsRqst_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUECntxtRlsRqst (SztUECntxtRlsRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUECntxtRlsCmmd_IEsCls (Szt_ValueUECntxtRlsCmmd_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UECntxtRlsCmmd_IEs (SztProtIE_Field_UECntxtRlsCmmd_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UECntxtRlsCmmd_IEs (SztProtIE_Cont_UECntxtRlsCmmd_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUECntxtRlsCmmd (SztUECntxtRlsCmmd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUECntxtRlsComplete_IEsCls (Szt_ValueUECntxtRlsComplete_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UECntxtRlsComplete_IEs (SztProtIE_Field_UECntxtRlsComplete_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UECntxtRlsComplete_IEs (SztProtIE_Cont_UECntxtRlsComplete_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUECntxtRlsComplete (SztUECntxtRlsComplete *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUECntxtModificationRqstIEsCls (Szt_ValueUECntxtModificationRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UECntxtModificationRqstIEs (SztProtIE_Field_UECntxtModificationRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UECntxtModificationRqstIEs (SztProtIE_Cont_UECntxtModificationRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUECntxtModificationRqst (SztUECntxtModificationRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUECntxtModificationRespIEsCls (Szt_ValueUECntxtModificationRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UECntxtModificationRespIEs (SztProtIE_Field_UECntxtModificationRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UECntxtModificationRespIEs (SztProtIE_Cont_UECntxtModificationRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUECntxtModificationResp (SztUECntxtModificationResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUECntxtModificationFailIEsCls (Szt_ValueUECntxtModificationFailIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UECntxtModificationFailIEs (SztProtIE_Field_UECntxtModificationFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UECntxtModificationFailIEs (SztProtIE_Cont_UECntxtModificationFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUECntxtModificationFail (SztUECntxtModificationFail *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUERadioCapbltyMatchRqstIEsCls (Szt_ValueUERadioCapbltyMatchRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UERadioCapbltyMatchRqstIEs (SztProtIE_Field_UERadioCapbltyMatchRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs (SztProtIE_Cont_UERadioCapbltyMatchRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUERadioCapbltyMatchRqst (SztUERadioCapbltyMatchRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUERadioCapbltyMatchRespIEsCls (Szt_ValueUERadioCapbltyMatchRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UERadioCapbltyMatchRespIEs (SztProtIE_Field_UERadioCapbltyMatchRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRespIEs (SztProtIE_Cont_UERadioCapbltyMatchRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUERadioCapbltyMatchResp (SztUERadioCapbltyMatchResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueDlnkNASTport_IEsCls (Szt_ValueDlnkNASTport_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_DlnkNASTport_IEs (SztProtIE_Field_DlnkNASTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_DlnkNASTport_IEs (SztProtIE_Cont_DlnkNASTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztDlnkNASTport (SztDlnkNASTport *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueInitUEMsg_IEsCls (Szt_ValueInitUEMsg_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_InitUEMsg_IEs (SztProtIE_Field_InitUEMsg_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_InitUEMsg_IEs (SztProtIE_Cont_InitUEMsg_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztInitUEMsg (SztInitUEMsg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUlnkNASTport_IEsCls (Szt_ValueUlnkNASTport_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UlnkNASTport_IEs (SztProtIE_Field_UlnkNASTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UlnkNASTport_IEs (SztProtIE_Cont_UlnkNASTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUlnkNASTport (SztUlnkNASTport *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueNASNonDlvryInd_IEsCls (Szt_ValueNASNonDlvryInd_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_NASNonDlvryInd_IEs (SztProtIE_Field_NASNonDlvryInd_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_NASNonDlvryInd_IEs (SztProtIE_Cont_NASNonDlvryInd_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztNASNonDlvryInd (SztNASNonDlvryInd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUE_assocLogS1_ConItemResCls (Szt_ValueUE_assocLogS1_ConItemResCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemRes (SztProtIE_Field_UE_assocLogS1_ConItemRes *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUE_assocLogS1_ConLstRes (SztUE_assocLogS1_ConLstRes *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztResetTyp (SztResetTyp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueResetIEsCls (Szt_ValueResetIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ResetIEs (SztProtIE_Field_ResetIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ResetIEs (SztProtIE_Cont_ResetIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztReset (SztReset *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUE_assocLogS1_ConItemResAckCls (Szt_ValueUE_assocLogS1_ConItemResAckCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemResAck (SztProtIE_Field_UE_assocLogS1_ConItemResAck *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUE_assocLogS1_ConLstResAck (SztUE_assocLogS1_ConLstResAck *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueResetAckgIEsCls (Szt_ValueResetAckgIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ResetAckgIEs (SztProtIE_Field_ResetAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ResetAckgIEs (SztProtIE_Cont_ResetAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztResetAckg (SztResetAckg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueErrIndIEsCls (Szt_ValueErrIndIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ErrIndIEs (SztProtIE_Field_ErrIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ErrIndIEs (SztProtIE_Cont_ErrIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztErrInd (SztErrInd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueS1SetupRqstIEsCls (Szt_ValueS1SetupRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_S1SetupRqstIEs (SztProtIE_Field_S1SetupRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_S1SetupRqstIEs (SztProtIE_Cont_S1SetupRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztS1SetupRqst (SztS1SetupRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueS1SetupRespIEsCls (Szt_ValueS1SetupRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_S1SetupRespIEs (SztProtIE_Field_S1SetupRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_S1SetupRespIEs (SztProtIE_Cont_S1SetupRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztS1SetupResp (SztS1SetupResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueS1SetupFailIEsCls (Szt_ValueS1SetupFailIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_S1SetupFailIEs (SztProtIE_Field_S1SetupFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_S1SetupFailIEs (SztProtIE_Cont_S1SetupFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztS1SetupFail (SztS1SetupFail *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueENBConfigUpdIEsCls (Szt_ValueENBConfigUpdIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ENBConfigUpdIEs (SztProtIE_Field_ENBConfigUpdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ENBConfigUpdIEs (SztProtIE_Cont_ENBConfigUpdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBConfigUpd (SztENBConfigUpd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueENBConfigUpdAckgIEsCls (Szt_ValueENBConfigUpdAckgIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ENBConfigUpdAckgIEs (SztProtIE_Field_ENBConfigUpdAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ENBConfigUpdAckgIEs (SztProtIE_Cont_ENBConfigUpdAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBConfigUpdAckg (SztENBConfigUpdAckg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueENBConfigUpdFailIEsCls (Szt_ValueENBConfigUpdFailIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ENBConfigUpdFailIEs (SztProtIE_Field_ENBConfigUpdFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ENBConfigUpdFailIEs (SztProtIE_Cont_ENBConfigUpdFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBConfigUpdFail (SztENBConfigUpdFail *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueMMEConfigUpdIEsCls (Szt_ValueMMEConfigUpdIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_MMEConfigUpdIEs (SztProtIE_Field_MMEConfigUpdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_MMEConfigUpdIEs (SztProtIE_Cont_MMEConfigUpdIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMMEConfigUpd (SztMMEConfigUpd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueMMEConfigUpdAckgIEsCls (Szt_ValueMMEConfigUpdAckgIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_MMEConfigUpdAckgIEs (SztProtIE_Field_MMEConfigUpdAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_MMEConfigUpdAckgIEs (SztProtIE_Cont_MMEConfigUpdAckgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMMEConfigUpdAckg (SztMMEConfigUpdAckg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueMMEConfigUpdFailIEsCls (Szt_ValueMMEConfigUpdFailIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_MMEConfigUpdFailIEs (SztProtIE_Field_MMEConfigUpdFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_MMEConfigUpdFailIEs (SztProtIE_Cont_MMEConfigUpdFailIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMMEConfigUpdFail (SztMMEConfigUpdFail *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueDlnkS1cdma2000tunnelingIEsCls (Szt_ValueDlnkS1cdma2000tunnelingIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs (SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs (SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztDlnkS1cdma2000tunneling (SztDlnkS1cdma2000tunneling *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUlnkS1cdma2000tunnelingIEsCls (Szt_ValueUlnkS1cdma2000tunnelingIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs (SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs (SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUlnkS1cdma2000tunneling (SztUlnkS1cdma2000tunneling *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUECapbltyInfoIndIEsCls (Szt_ValueUECapbltyInfoIndIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UECapbltyInfoIndIEs (SztProtIE_Field_UECapbltyInfoIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UECapbltyInfoIndIEs (SztProtIE_Cont_UECapbltyInfoIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUECapbltyInfoInd (SztUECapbltyInfoInd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueENBStatusTfrIEsCls (Szt_ValueENBStatusTfrIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ENBStatusTfrIEs (SztProtIE_Field_ENBStatusTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ENBStatusTfrIEs (SztProtIE_Cont_ENBStatusTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBStatusTfr (SztENBStatusTfr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueMMEStatusTfrIEsCls (Szt_ValueMMEStatusTfrIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_MMEStatusTfrIEs (SztProtIE_Field_MMEStatusTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_MMEStatusTfrIEs (SztProtIE_Cont_MMEStatusTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMMEStatusTfr (SztMMEStatusTfr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueTraceStartIEsCls (Szt_ValueTraceStartIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_TraceStartIEs (SztProtIE_Field_TraceStartIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_TraceStartIEs (SztProtIE_Cont_TraceStartIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTraceStart (SztTraceStart *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueTraceFailIndIEsCls (Szt_ValueTraceFailIndIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_TraceFailIndIEs (SztProtIE_Field_TraceFailIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_TraceFailIndIEs (SztProtIE_Cont_TraceFailIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztTraceFailInd (SztTraceFailInd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueDeactvTraceIEsCls (Szt_ValueDeactvTraceIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_DeactvTraceIEs (SztProtIE_Field_DeactvTraceIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_DeactvTraceIEs (SztProtIE_Cont_DeactvTraceIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztDeactvTrace (SztDeactvTrace *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueCellTrafficTraceIEsCls (Szt_ValueCellTrafficTraceIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_CellTrafficTraceIEs (SztProtIE_Field_CellTrafficTraceIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_CellTrafficTraceIEs (SztProtIE_Cont_CellTrafficTraceIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztCellTrafficTrace (SztCellTrafficTrace *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueLocRprtngCntrlIEsCls (Szt_ValueLocRprtngCntrlIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_LocRprtngCntrlIEs (SztProtIE_Field_LocRprtngCntrlIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_LocRprtngCntrlIEs (SztProtIE_Cont_LocRprtngCntrlIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztLocRprtngCntrl (SztLocRprtngCntrl *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueLocRprtngFailIndIEsCls (Szt_ValueLocRprtngFailIndIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_LocRprtngFailIndIEs (SztProtIE_Field_LocRprtngFailIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_LocRprtngFailIndIEs (SztProtIE_Cont_LocRprtngFailIndIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztLocRprtngFailInd (SztLocRprtngFailInd *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueLocReportIEsCls (Szt_ValueLocReportIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_LocReportIEs (SztProtIE_Field_LocReportIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_LocReportIEs (SztProtIE_Cont_LocReportIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztLocReport (SztLocReport *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueOverloadStartIEsCls (Szt_ValueOverloadStartIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_OverloadStartIEs (SztProtIE_Field_OverloadStartIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_OverloadStartIEs (SztProtIE_Cont_OverloadStartIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztOverloadStart (SztOverloadStart *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueOverloadStopIEsCls (Szt_ValueOverloadStopIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_OverloadStopIEs (SztProtIE_Field_OverloadStopIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_OverloadStopIEs (SztProtIE_Cont_OverloadStopIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztOverloadStop (SztOverloadStop *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueWriteReplaceWarningRqstIEsCls (Szt_ValueWriteReplaceWarningRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_WriteReplaceWarningRqstIEs (SztProtIE_Field_WriteReplaceWarningRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_WriteReplaceWarningRqstIEs (SztProtIE_Cont_WriteReplaceWarningRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztWriteReplaceWarningRqst (SztWriteReplaceWarningRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueWriteReplaceWarningRespIEsCls (Szt_ValueWriteReplaceWarningRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_WriteReplaceWarningRespIEs (SztProtIE_Field_WriteReplaceWarningRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_WriteReplaceWarningRespIEs (SztProtIE_Cont_WriteReplaceWarningRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztWriteReplaceWarningResp (SztWriteReplaceWarningResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztInter_SystemInformTfrTyp (SztInter_SystemInformTfrTyp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueENBDirectInformTfrIEsCls (Szt_ValueENBDirectInformTfrIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ENBDirectInformTfrIEs (SztProtIE_Field_ENBDirectInformTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ENBDirectInformTfrIEs (SztProtIE_Cont_ENBDirectInformTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBDirectInformTfr (SztENBDirectInformTfr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueMMEDirectInformTfrIEsCls (Szt_ValueMMEDirectInformTfrIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_MMEDirectInformTfrIEs (SztProtIE_Field_MMEDirectInformTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_MMEDirectInformTfrIEs (SztProtIE_Cont_MMEDirectInformTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMMEDirectInformTfr (SztMMEDirectInformTfr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueENBConfigTfrIEsCls (Szt_ValueENBConfigTfrIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_ENBConfigTfrIEs (SztProtIE_Field_ENBConfigTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_ENBConfigTfrIEs (SztProtIE_Cont_ENBConfigTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztENBConfigTfr (SztENBConfigTfr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueMMEConfigTfrIEsCls (Szt_ValueMMEConfigTfrIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_MMEConfigTfrIEs (SztProtIE_Field_MMEConfigTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_MMEConfigTfrIEs (SztProtIE_Cont_MMEConfigTfrIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztMMEConfigTfr (SztMMEConfigTfr *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValuePrivMsgIEsCls (Szt_ValuePrivMsgIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztPrivIE_Field_PrivMsgIEs (SztPrivIE_Field_PrivMsgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztPrivIE_Cont_PrivMsgIEs (SztPrivIE_Cont_PrivMsgIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztPrivMsg (SztPrivMsg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueKillRqstIEsCls (Szt_ValueKillRqstIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_KillRqstIEs (SztProtIE_Field_KillRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_KillRqstIEs (SztProtIE_Cont_KillRqstIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztKillRqst (SztKillRqst *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueKillRespIEsCls (Szt_ValueKillRespIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_KillRespIEs (SztProtIE_Field_KillRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_KillRespIEs (SztProtIE_Cont_KillRespIEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztKillResp (SztKillResp *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls (Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs (SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs (SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztDlnkUEAssociatedLPPaTport (SztDlnkUEAssociatedLPPaTport *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls (Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs (SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs (SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUlnkUEAssociatedLPPaTport (SztUlnkUEAssociatedLPPaTport *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls (Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs (SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs (SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztDlnkNonUEAssociatedLPPaTport (SztDlnkNonUEAssociatedLPPaTport *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls (Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs (SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs (SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUlnkNonUEAssociatedLPPaTport (SztUlnkNonUEAssociatedLPPaTport *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_InitiatingMsgCls (Szt_InitiatingMsgCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztInitiatingMsg (SztInitiatingMsg *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_SuccessfulOutcomeCls (Szt_SuccessfulOutcomeCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztSuccessfulOutcome (SztSuccessfulOutcome *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSzt_UnsuccessfulOutcomeCls (Szt_UnsuccessfulOutcomeCls *param, U32 val, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztUnsuccessfulOutcome (SztUnsuccessfulOutcome *param, Ptr ptr, Buffer *mBuf);
extern S16 cmUnpkSztS1AP_PDU (SztS1AP_PDU *param, Ptr ptr, Buffer *mBuf);

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
extern S16 PtUiSztBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 PtUiSztStaInd (Pst *pst, SuId suId, SztStaInd *sztSta);
extern S16 PtUiSztFlcInd (Pst *pst, SuId suId, SztFlcInd *flcInd);
extern S16 PtUiSztErrInd (Pst *pst, SuId suId, SztLclErrInd *sztErrInd);
extern S16 PtUiSztUDatInd (Pst *pst, SuId suId, SztUDatEvnt *uDatEvnt);
extern S16 PtUiSztConInd (Pst *pst, SuId suId, SztConInd *conInd);
extern S16 PtUiSztConCfm (Pst *pst, SuId suId, SztConCfm *conCfm);
extern S16 PtUiSztRelInd (Pst *pst, SuId suId, SztRelInd *relInd);
extern S16 PtUiSztRelCfm (Pst *pst, SuId suId, SztRelCfm *relCfm);
extern S16 PtUiSztDatInd (Pst *pst, SuId suId, SztDatEvntInd *datEvnt);
extern S16 PtUiSztEncDecCfm (Pst *pst, SuId suId, SztEncDecEvnt *sztEncDecEvnt, SztReqStatus *status)
                                                                            ;
extern S16 PtUiSztAudCfm (Pst *pst, SuId suId, SztAudEvnt *audEvnt);


extern S16 PtUiSztAbortS1Cfm (Pst *pst, SuId suId, SztAbortS1 *abortS1);




 SztBndCfm szUiSztBndCfmMt [3] =
{

   cmPkSztBndCfm,






   PtUiSztBndCfm,


   UzLiSztBndCfm,



};

 SztStatusInd szUiSztStaIndMt [] =
{

   cmPkSztStaInd,






   PtUiSztStaInd,


   UzLiSztStaInd,



};

 SztFlowControlInd szUiSztFlcIndMt [] =
{

   cmPkSztFlcInd,






   PtUiSztFlcInd,


   UzLiSztFlcInd,



};

 SztErrorInd szUiSztErrIndMt [] =
{

   cmPkSztLclErrInd,






   PtUiSztErrInd,


   UzLiSztErrInd,



};

 SztUDatInd szUiSztUDatIndMt [] =
{

   cmPkSztUDatInd,






   PtUiSztUDatInd,


   UzLiSztUDatInd,



};

 SztConnInd szUiSztConIndMt [] =
{

   cmPkSztConInd,






   PtUiSztConInd,


   UzLiSztConInd,



};

 SztConnCfm szUiSztConCfmMt [] =
{

   cmPkSztConCfm,






   PtUiSztConCfm,


   UzLiSztConCfm,



};



 SztAbortS1Cfm szUiSztAbortS1CfmMt [] =
{

   cmPkSztAbortS1Cfm,






   PtUiSztAbortS1Cfm,


   UzLiSztAbortS1Cfm,



};



 SztRelsInd szUiSztRelIndMt [] =
{

   cmPkSztRelInd,






   PtUiSztRelInd,


   UzLiSztRelInd,




};

 SztRelsCfm szUiSztRelCfmMt [] =
{

   cmPkSztRelCfm,






   PtUiSztRelCfm,


   UzLiSztRelCfm,



};

 SztDatInd szUiSztDatIndMt [] =
{

   cmPkSztDatInd,






   PtUiSztDatInd,


   UzLiSztDatInd,



};

 SztEncDecCfm szUiSztEncDecCfmMt [] =
{

   cmPkSztEncDecCfm,






   PtUiSztEncDecCfm,


   UzLiSztEncDecCfm,



};

 SztAudCfm szUiSztAudCfmMt [] =
{

   cmPkSztAudCfm,






   PtUiSztAudCfm,


   UzLiSztAudCfm,



};
 S16 SzUiSztBndCfm
(
Pst *pst,
SuId suId,
U8 status
)






{
   ;

   (*szUiSztBndCfmMt[pst->selector])
      (pst, suId, status);

   return(0);
}
 S16 SzUiSztStaInd
(
Pst *pst,
SuId suId,
SztStaInd *sztSta
)






{
   ;

   (*szUiSztStaIndMt[pst->selector])
      (pst, suId, sztSta);

   return(0);
}
 S16 SzUiSztFlcInd
(
Pst *pst,
SuId suId,
SztFlcInd *flcInd
)






{
   ;

   (*szUiSztFlcIndMt[pst->selector])
      (pst, suId, flcInd);

   return(0);
}
 S16 SzUiSztErrInd
(
Pst *pst,
SuId suId,
SztLclErrInd *sztErrInd
)






{
   ;

   (*szUiSztErrIndMt[pst->selector])
      (pst, suId, sztErrInd);

   return(0);
}
 S16 SzUiSztUDatInd
(
Pst *pst,
SuId suId,
SztUDatEvnt *uDatEvnt
)






{
   ;

   (*szUiSztUDatIndMt[pst->selector])
      (pst, suId, uDatEvnt);

   return(0);
}
 S16 SzUiSztConInd
(
Pst *pst,
SuId suId,
SztConInd *conInd
)






{
   ;

   (*szUiSztConIndMt[pst->selector])
      (pst, suId, conInd);

   return(0);
}
 S16 SzUiSztAbortS1Cfm
(
Pst *pst,
SuId suId,
SztAbortS1 *abortS1
)






{
   ;

   (*szUiSztAbortS1CfmMt[pst->selector])
      (pst, suId, abortS1);

   return(0);
}
 S16 SzUiSztConCfm
(
Pst *pst,
SuId suId,
SztConCfm *conCfm
)






{
   ;

   (*szUiSztConCfmMt[pst->selector])
      (pst, suId, conCfm);

   return(0);
}
 S16 SzUiSztRelInd
(
Pst *pst,
SuId suId,
SztRelInd *relInd
)






{
   ;

   (*szUiSztRelIndMt[pst->selector])
      (pst, suId, relInd);

   return(0);
}
 S16 SzUiSztRelCfm
(
Pst *pst,
SuId suId,
SztRelCfm *relCfm
)






{
   ;

   (*szUiSztRelCfmMt[pst->selector])
      (pst, suId, relCfm);

   return(0);
}
 S16 SzUiSztDatInd
(
Pst *pst,
SuId suId,
SztDatEvntInd *datEvnt
)






{
   ;

   (*szUiSztDatIndMt[pst->selector])
      (pst, suId, datEvnt);

   return(0);
}
 S16 SzUiSztEncDecCfm
(
Pst *pst,
SuId suId,
SztEncDecEvnt *sztEncDecEvnt,
SztReqStatus *status
)







{
   ;

   (*szUiSztEncDecCfmMt[pst->selector])
      (pst, suId, sztEncDecEvnt, status);

   return(0);
}
 S16 SzUiSztAudCfm
(
Pst *pst,
SuId suId,
SztAudEvnt *audEvnt
)






{
   ;

   (*szUiSztAudCfmMt[pst->selector])
      (pst, suId, audEvnt);

   return(0);
}
 S16 PtUiSztBndCfm
(
Pst *pst,
SuId suId,
U8 status
)






{
   ;






   return(0);
}
 S16 PtUiSztStaInd
(
Pst *pst,
SuId suId,
SztStaInd *sztSta
)






{
   ;






   return(0);
}
 S16 PtUiSztFlcInd
(
Pst *pst,
SuId suId,
SztFlcInd *flcInd
)






{
   ;






   return(0);
}
 S16 PtUiSztErrInd
(
Pst *pst,
SuId suId,
SztLclErrInd *sztErrInd
)






{
   ;






   return(0);
}
 S16 PtUiSztUDatInd
(
Pst *pst,
SuId suId,
SztUDatEvnt *uDatEvnt
)






{
   ;






   return(0);
}
 S16 PtUiSztConInd
(
Pst *pst,
SuId suId,
SztConInd *conInd
)






{
   ;






   return(0);
}
 S16 PtUiSztConCfm
(
Pst *pst,
SuId suId,
SztConCfm *conCfm
)






{
   ;






   return(0);
}
 S16 PtUiSztAbortS1Cfm
(
Pst *pst,
SuId suId,
SztAbortS1 *abortS1
)






{
   ;






   return(0);
}
 S16 PtUiSztRelInd
(
Pst *pst,
SuId suId,
SztRelInd *relInd
)






{
   ;






   return(0);
}
 S16 PtUiSztRelCfm
(
Pst *pst,
SuId suId,
SztRelCfm *relCfm
)






{
   ;






   return(0);
}
 S16 PtUiSztDatInd
(
Pst *pst,
SuId suId,
SztDatEvntInd *datEvnt
)






{
   ;






   return(0);
}
 S16 PtUiSztEncDecCfm
(
Pst *pst,
SuId suId,
SztEncDecEvnt *sztEncDecEvnt,
SztReqStatus *status
)







{
   ;






   return(0);
}
 S16 PtUiSztAudCfm
(
Pst *pst,
SuId suId,
SztAudEvnt *audEvnt
)






{
   ;






   return(0);
}
