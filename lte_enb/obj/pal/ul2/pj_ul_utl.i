static const char* RLOG_MODULE_NAME="PDCP";
static int RLOG_FILE_ID=251;
static int RLOG_MODULE_ID=1024;






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


enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
extern const unsigned short int **__ctype_b_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_tolower_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_toupper_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));






extern int isalnum (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha (int) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit (int) __attribute__ ((__nothrow__ , __leaf__));
extern int islower (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint (int) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit (int) __attribute__ ((__nothrow__ , __leaf__));



extern int tolower (int __c) __attribute__ ((__nothrow__ , __leaf__));


extern int toupper (int __c) __attribute__ ((__nothrow__ , __leaf__));








extern int isblank (int) __attribute__ ((__nothrow__ , __leaf__));






extern int isctype (int __c, int __mask) __attribute__ ((__nothrow__ , __leaf__));






extern int isascii (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int toascii (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int _toupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int _tolower (int) __attribute__ ((__nothrow__ , __leaf__));
extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) tolower (int __c)
{
  return __c >= -128 && __c < 256 ? (*__ctype_tolower_loc ())[__c] : __c;
}

extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) toupper (int __c)
{
  return __c >= -128 && __c < 256 ? (*__ctype_toupper_loc ())[__c] : __c;
}
extern int isalnum_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int islower_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));

extern int isblank_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));



extern int __tolower_l (int __c, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern int tolower_l (int __c, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));


extern int __toupper_l (int __c, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern int toupper_l (int __c, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));


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



extern int __sigismember (const __sigset_t *, int);
extern int __sigaddset (__sigset_t *, int);
extern int __sigdelset (__sigset_t *, int);
extern __inline __attribute__ ((__gnu_inline__)) int __sigismember (const __sigset_t *__set, int __sig) { unsigned long int __mask = (((unsigned long int) 1) << (((__sig) - 1) % (8 * sizeof (unsigned long int)))); unsigned long int __word = (((__sig) - 1) / (8 * sizeof (unsigned long int))); return (__set->__val[__word] & __mask) ? 1 : 0; }
extern __inline __attribute__ ((__gnu_inline__)) int __sigaddset ( __sigset_t *__set, int __sig) { unsigned long int __mask = (((unsigned long int) 1) << (((__sig) - 1) % (8 * sizeof (unsigned long int)))); unsigned long int __word = (((__sig) - 1) / (8 * sizeof (unsigned long int))); return ((__set->__val[__word] |= __mask), 0); }
extern __inline __attribute__ ((__gnu_inline__)) int __sigdelset ( __sigset_t *__set, int __sig) { unsigned long int __mask = (((unsigned long int) 1) << (((__sig) - 1) % (8 * sizeof (unsigned long int)))); unsigned long int __word = (((__sig) - 1) / (8 * sizeof (unsigned long int))); return ((__set->__val[__word] &= ~__mask), 0); }







typedef __sig_atomic_t sig_atomic_t;








typedef union sigval
  {
    int sival_int;
    void *sival_ptr;
  } sigval_t;
typedef __clock_t __sigchld_clock_t;



typedef struct
  {
    int si_signo;
    int si_errno;

    int si_code;

    union
      {
 int _pad[((128 / sizeof (int)) - 3)];


 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
   } _kill;


 struct
   {
     int si_tid;
     int si_overrun;
     sigval_t si_sigval;
   } _timer;


 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
     sigval_t si_sigval;
   } _rt;


 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
     int si_status;
     __sigchld_clock_t si_utime;
     __sigchld_clock_t si_stime;
   } _sigchld;


 struct
   {
     void *si_addr;
     short int si_addr_lsb;
     struct
       {
  void *_lower;
  void *_upper;
       } si_addr_bnd;
   } _sigfault;


 struct
   {
     long int si_band;
     int si_fd;
   } _sigpoll;


 struct
   {
     void *_call_addr;
     int _syscall;
     unsigned int _arch;
   } _sigsys;
      } _sifields;
  } siginfo_t ;
enum
{
  SI_ASYNCNL = -60,

  SI_TKILL = -6,

  SI_SIGIO,

  SI_ASYNCIO,

  SI_MESGQ,

  SI_TIMER,

  SI_QUEUE,

  SI_USER,

  SI_KERNEL = 0x80

};




enum
{
  ILL_ILLOPC = 1,

  ILL_ILLOPN,

  ILL_ILLADR,

  ILL_ILLTRP,

  ILL_PRVOPC,

  ILL_PRVREG,

  ILL_COPROC,

  ILL_BADSTK

};


enum
{
  FPE_INTDIV = 1,

  FPE_INTOVF,

  FPE_FLTDIV,

  FPE_FLTOVF,

  FPE_FLTUND,

  FPE_FLTRES,

  FPE_FLTINV,

  FPE_FLTSUB

};


enum
{
  SEGV_MAPERR = 1,

  SEGV_ACCERR

};


enum
{
  BUS_ADRALN = 1,

  BUS_ADRERR,

  BUS_OBJERR,

  BUS_MCEERR_AR,

  BUS_MCEERR_AO

};




enum
{
  TRAP_BRKPT = 1,

  TRAP_TRACE

};




enum
{
  CLD_EXITED = 1,

  CLD_KILLED,

  CLD_DUMPED,

  CLD_TRAPPED,

  CLD_STOPPED,

  CLD_CONTINUED

};


enum
{
  POLL_IN = 1,

  POLL_OUT,

  POLL_MSG,

  POLL_ERR,

  POLL_PRI,

  POLL_HUP

};
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




typedef void (*__sighandler_t) (int);




extern __sighandler_t __sysv_signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));

extern __sighandler_t sysv_signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));







extern __sighandler_t signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));





extern __sighandler_t bsd_signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));






extern int kill (__pid_t __pid, int __sig) __attribute__ ((__nothrow__ , __leaf__));






extern int killpg (__pid_t __pgrp, int __sig) __attribute__ ((__nothrow__ , __leaf__));




extern int raise (int __sig) __attribute__ ((__nothrow__ , __leaf__));




extern __sighandler_t ssignal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
extern int gsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));




extern void psignal (int __sig, const char *__s);


extern void psiginfo (const siginfo_t *__pinfo, const char *__s);
extern int sigpause (int __sig) __asm__ ("__xpg_sigpause");
extern int sigblock (int __mask) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));


extern int sigsetmask (int __mask) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));


extern int siggetmask (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
typedef __sighandler_t sighandler_t;




typedef __sighandler_t sig_t;





extern int sigemptyset (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigfillset (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigaddset (sigset_t *__set, int __signo) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigdelset (sigset_t *__set, int __signo) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigismember (const sigset_t *__set, int __signo)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int sigisemptyset (const sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigandset (sigset_t *__set, const sigset_t *__left,
        const sigset_t *__right) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3)));


extern int sigorset (sigset_t *__set, const sigset_t *__left,
       const sigset_t *__right) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3)));




struct sigaction
  {


    union
      {

 __sighandler_t sa_handler;

 void (*sa_sigaction) (int, siginfo_t *, void *);
      }
    __sigaction_handler;







    __sigset_t sa_mask;


    int sa_flags;


    void (*sa_restorer) (void);
  };


extern int sigprocmask (int __how, const sigset_t *__restrict __set,
   sigset_t *__restrict __oset) __attribute__ ((__nothrow__ , __leaf__));






extern int sigsuspend (const sigset_t *__set) __attribute__ ((__nonnull__ (1)));


extern int sigaction (int __sig, const struct sigaction *__restrict __act,
        struct sigaction *__restrict __oact) __attribute__ ((__nothrow__ , __leaf__));


extern int sigpending (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int sigwait (const sigset_t *__restrict __set, int *__restrict __sig)
     __attribute__ ((__nonnull__ (1, 2)));






extern int sigwaitinfo (const sigset_t *__restrict __set,
   siginfo_t *__restrict __info) __attribute__ ((__nonnull__ (1)));






extern int sigtimedwait (const sigset_t *__restrict __set,
    siginfo_t *__restrict __info,
    const struct timespec *__restrict __timeout)
     __attribute__ ((__nonnull__ (1)));



extern int sigqueue (__pid_t __pid, int __sig, const union sigval __val)
     __attribute__ ((__nothrow__ , __leaf__));
extern const char *const _sys_siglist[65];
extern const char *const sys_siglist[65];



struct _fpx_sw_bytes
{
  __uint32_t magic1;
  __uint32_t extended_size;
  __uint64_t xstate_bv;
  __uint32_t xstate_size;
  __uint32_t padding[7];
};

struct _fpreg
{
  unsigned short significand[4];
  unsigned short exponent;
};

struct _fpxreg
{
  unsigned short significand[4];
  unsigned short exponent;
  unsigned short padding[3];
};

struct _xmmreg
{
  __uint32_t element[4];
};





struct _fpstate
{

  __uint32_t cw;
  __uint32_t sw;
  __uint32_t tag;
  __uint32_t ipoff;
  __uint32_t cssel;
  __uint32_t dataoff;
  __uint32_t datasel;
  struct _fpreg _st[8];
  unsigned short status;
  unsigned short magic;


  __uint32_t _fxsr_env[6];
  __uint32_t mxcsr;
  __uint32_t reserved;
  struct _fpxreg _fxsr_st[8];
  struct _xmmreg _xmm[8];
  __uint32_t padding[56];
};
struct sigcontext
{
  unsigned short gs, __gsh;
  unsigned short fs, __fsh;
  unsigned short es, __esh;
  unsigned short ds, __dsh;
  unsigned long edi;
  unsigned long esi;
  unsigned long ebp;
  unsigned long esp;
  unsigned long ebx;
  unsigned long edx;
  unsigned long ecx;
  unsigned long eax;
  unsigned long trapno;
  unsigned long err;
  unsigned long eip;
  unsigned short cs, __csh;
  unsigned long eflags;
  unsigned long esp_at_signal;
  unsigned short ss, __ssh;
  struct _fpstate * fpstate;
  unsigned long oldmask;
  unsigned long cr2;
};
struct _xsave_hdr
{
  __uint64_t xstate_bv;
  __uint64_t reserved1[2];
  __uint64_t reserved2[5];
};

struct _ymmh_state
{
  __uint32_t ymmh_space[64];
};

struct _xstate
{
  struct _fpstate fpstate;
  struct _xsave_hdr xstate_hdr;
  struct _ymmh_state ymmh;
};


extern int sigreturn (struct sigcontext *__scp) __attribute__ ((__nothrow__ , __leaf__));










extern int siginterrupt (int __sig, int __interrupt) __attribute__ ((__nothrow__ , __leaf__));

struct sigstack
  {
    void *ss_sp;
    int ss_onstack;
  };



enum
{
  SS_ONSTACK = 1,

  SS_DISABLE

};
typedef struct sigaltstack
  {
    void *ss_sp;
    int ss_flags;
    size_t ss_size;
  } stack_t;


typedef int greg_t;





typedef greg_t gregset_t[19];



enum
{
  REG_GS = 0,

  REG_FS,

  REG_ES,

  REG_DS,

  REG_EDI,

  REG_ESI,

  REG_EBP,

  REG_ESP,

  REG_EBX,

  REG_EDX,

  REG_ECX,

  REG_EAX,

  REG_TRAPNO,

  REG_ERR,

  REG_EIP,

  REG_CS,

  REG_EFL,

  REG_UESP,

  REG_SS

};



struct _libc_fpreg
{
  unsigned short int significand[4];
  unsigned short int exponent;
};

struct _libc_fpstate
{
  unsigned long int cw;
  unsigned long int sw;
  unsigned long int tag;
  unsigned long int ipoff;
  unsigned long int cssel;
  unsigned long int dataoff;
  unsigned long int datasel;
  struct _libc_fpreg _st[8];
  unsigned long int status;
};


typedef struct _libc_fpstate *fpregset_t;


typedef struct
  {
    gregset_t gregs;


    fpregset_t fpregs;
    unsigned long int oldmask;
    unsigned long int cr2;
  } mcontext_t;


typedef struct ucontext
  {
    unsigned long int uc_flags;
    struct ucontext *uc_link;
    stack_t uc_stack;
    mcontext_t uc_mcontext;
    __sigset_t uc_sigmask;
    struct _libc_fpstate __fpregs_mem;
  } ucontext_t;





extern int sigstack (struct sigstack *__ss, struct sigstack *__oss)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));



extern int sigaltstack (const struct sigaltstack *__restrict __ss,
   struct sigaltstack *__restrict __oss) __attribute__ ((__nothrow__ , __leaf__));







extern int sighold (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern int sigrelse (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern int sigignore (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern __sighandler_t sigset (int __sig, __sighandler_t __disp) __attribute__ ((__nothrow__ , __leaf__));






extern int pthread_sigmask (int __how,
       const __sigset_t *__restrict __newmask,
       __sigset_t *__restrict __oldmask)__attribute__ ((__nothrow__ , __leaf__));


extern int pthread_kill (pthread_t __threadid, int __signo) __attribute__ ((__nothrow__ , __leaf__));



extern int pthread_sigqueue (pthread_t __threadid, int __signo,
        const union sigval __value) __attribute__ ((__nothrow__ , __leaf__));






extern int __libc_current_sigrtmin (void) __attribute__ ((__nothrow__ , __leaf__));

extern int __libc_current_sigrtmax (void) __attribute__ ((__nothrow__ , __leaf__));











extern int *__errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern char *program_invocation_name, *program_invocation_short_name;




typedef int error_t;

typedef enum {
LOG_ARG_INT,
LOG_ARG_STR,
LOG_ARG_HEX,
LOG_ARG_SPL
} LOG_ARG_TYPE;

typedef enum rlLogCntLmt
{
   RL_LOG_COUNT_LIMIT_START = 1,
   RL_LOG_COUNT_LIMIT_STOP
}RLLogCntLmt;



typedef enum
{
 L_TIME_REFERENCE=0,
 L_TIME_DELIMITER,
 L_SIGSEGV,
    L_TIME_TTI_UPDT
} LOGID_TYPE;

typedef struct
{
 time_t tv_sec;
 U32 ms_tti;
} __attribute__ ((__packed__)) LOGTIME;

typedef struct
{
 LOGID logId;
 LOGTIME logTime;
 unsigned int argType :2;
 unsigned int logLevel :3;
 unsigned int numOfArgs :3;
 U16 len;
} __attribute__ ((__packed__)) LOGDATA;

typedef struct
{
 LOGDATA logData;
 char buf[5000];
} __attribute__ ((__packed__)) ARGDATA;

typedef struct
{
 LOGDATA logData;
 U32 arg1;
 U32 arg2;
 U32 arg3;
 U32 arg4;
   char unusedByte[19];
} __attribute__ ((__packed__)) ARG4DATA;

typedef struct
{
 LOGDATA logData;
 U8 splEnum;
 U32 splArg;
 U32 arg1;
 U32 arg2;
 U32 arg3;
 U32 arg4;
   char unusedByte[14];
} __attribute__ ((__packed__)) SPL_ARGDATA;

typedef enum _endian {little_endian, big_endian} EndianType;

typedef struct
{
 U16 version;
 U32 dummy32;
 U8 endianType;
 char szTimeZone[8 +1];
 U16 END_MARKER;
   time_t time_sec;
} __attribute__ ((__packed__)) FILE_HEADER;



typedef struct {

 char szTaskName[16];
 U8* logBuff;
 U32 logBufLen;
 U32 logReadPos;
 U8 listIndex;

} THREAD_DATA;

extern void readL2LogBuff(void);
extern void processL2LogBuff(void);
extern S16 sendL2LogBuftoL3(void);
extern void rlInitL2Log(void);

extern void rlProcessLogBufFromL2(void *mBuf);
extern void rlInitL2SocSpecific(void);

extern void rlProcessTicks(void);
extern void rlGetL2LogBufPtr (void *mBuf, U32 *logLen,U8 **logPtr);
extern void rlInvalidateL2LogsInCache(U8 *ptr,U32 len);

extern U8 *g_l2rlogBuf;
extern U8 *g_l2LogBufStartPtr;
extern U8 *g_l2LogBufBasePtr;
extern U8 *g_logBufRcvdFromL2;
extern U8 *g_l2LogBaseBuff;
extern U32 g_l2LogBufLen;
extern U32 startL2Logging;
extern U32 g_l2logBuffPos;
extern U8 g_writeCirBuf;


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
typedef U8 CpjCipherKey;





typedef U8 CpjIntegrityKey;





typedef struct cpjRlcAm
{
   Bool statusRepReqd;
   U8 pdcpSNSize;
}CpjRlcAm;





typedef struct cpjRlcUm
{
   U8 pdcpSNSize;
}CpjRlcUm;





typedef struct cpjRlcInfo
{
   U8 dir;
   U8 mode;
   union
   {
      CpjRlcAm rlcAm;
      CpjRlcUm rlcUm;
   }m;
}CpjRlcInfo;






typedef struct cpjCipherInfo
{
   CpjCipherKey ctrlplnKey[16];

   CpjCipherKey usrplnKey[16];

   U8 algoType;





}CpjCipherInfo;





typedef struct cpjIntegInfo
{
   U8 algoType;




   CpjIntegrityKey intKey[16];
} CpjIntegInfo;





typedef struct cpjSecCfg
{
   Bool selSecAct;







   U8 isHo;
   CpjIntegInfo integInfo;
   CpjCipherInfo cipherInfo;
} CpjSecCfg;





typedef struct cpjRohcInfo
{
   U16 maxCid;
   Bool profLst[9];

}CpjRohcInfo;





typedef struct cpjHdrCompCfg
{
   Bool hdrCompUsed;
   CpjRohcInfo rohcInfo;
}CpjHdrCompCfg;





typedef struct cpjHoInfo
{
   U8 isHoPres;





   U8 snLen;
   U32 dlCount;
   U32 ulCount;
   U16 numBits;
   U8 *ulBitMap;

} CpjHoInfo;





typedef struct cpjAddCfgEnt
{
   Bool discReqd;

   Bool cfmReqd;






   CpjRlcInfo rlcInfo;
   S16 discardTmr;



   CpjHdrCompCfg hdrCompCfg;
}CpjAddCfgEnt;





typedef struct cpjModCfgEnt
{

   U8 bitFlag;


   Bool discReqd;


   Bool cfmReqd;


   CpjHdrCompCfg hdrCompCfg;
   CpjHoInfo hoInfo;
}CpjModCfgEnt;






typedef struct cpjCfgEnt
{
   U8 rbId;
   U8 cfgType;





   U8 rbType;



   union{
        CpjAddCfgEnt addCfg;

        CpjModCfgEnt modCfg;

   }m;
}CpjCfgEnt;
typedef struct cpjCfgReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   U8 numEnt;

   U8 isHo;

   SpId rlcUlSapId;
   SpId rlcDlSapId;

   CpjCfgEnt cfgEnt[10];

}CpjCfgReqInfo;





typedef struct cpjCfmEnt
{
   U8 rbId;
   U8 rbType;
   Status status;
   Reason reason;
}CpjCfmEnt;





typedef struct cpjCfgCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   U8 numEnt;
   CpjCfmEnt cfmEnt[10];

}CpjCfgCfmInfo;





typedef struct cpjReEstReqInfo
{
   CmLtePdcpId pdcpId;
   U32 transId;
   U8 intKey[16];
   CpjCipherKey ctrlplnKey[16];

   CpjCipherKey usrplnKey[16];

}CpjReEstReqInfo;





typedef struct cpjDataFwdReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   Bool isUlDatFwdReq;
}CpjDataFwdReqInfo;






typedef struct cpjDatResumeReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
}CpjDatResumeReqInfo;




typedef struct cpjReEstCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   Status status;




}CpjReEstCfmInfo;






typedef struct cpjSecCfgReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   CpjSecCfg secCfg;
}CpjSecCfgReqInfo;





typedef struct cpjSecCfgCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   Status status;
   Reason reason;
}CpjSecCfgCfmInfo;





typedef struct cpjUeInfo
{
   CmLteCellId cellId;
   CmLteRnti ueId;
}CpjUeInfo;





typedef struct cpjCountReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
} CpjCountReqInfo;





typedef struct cpjCountInfo
{
   U8 rbId;
   U8 dir;
   U32 ulCount;
   U32 dlCount;
} CpjCountInfo;




typedef struct cpjCountCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   U8 numRb;
   CpjCountInfo countInfo[12];
   Status status;
   Reason reason;
} CpjCountCfmInfo;






typedef struct cpjSduStaReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
} CpjSduStaReqInfo;





typedef struct cpjUlSduStaInfo
{
   U16 numBits;
   U8 *ulBitMap;
   U32 count;

} CpjUlSduStaInfo;





typedef struct cpjDlSduStaInfo
{
   U32 count;

} CpjDlSduStaInfo;





typedef struct cpjSduStaInfo
{
   U8 rbId;
   U8 dir;
   U8 snLen;
   CpjUlSduStaInfo ulSduStaInfo;
   CpjDlSduStaInfo dlSduStaInfo;
} CpjSduStaInfo;





typedef struct cpjSduStaCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   U8 numRb;
   CpjSduStaInfo sduStaInfo[12];

   Status status;
   Reason reason;
} CpjSduStaCfmInfo;





typedef struct cpjDatResumeCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   Status status;
   Reason reason;
} CpjDatResumeCfmInfo;





typedef struct cpjAsKeyInfo{
           U8 intgAlgoType;

           U8 ciphAlgoType;

           U8 secKey[32];

}CpjAsKeyInfo;


typedef struct cpjKenbStarInfo{
           U16 dlCarrFreq;
           U16 physCellId;
           U8 secKey[32];

}CpjKenbStarInfo;


typedef struct cpjNhKeyInfo{
           U16 dlCarrFreq;
           U16 physCellId;
           U8 secKey[32];

}CpjNhKeyInfo;

typedef struct cpjKdfReqInfo {
   U8 keyDerType;


   union
   {
      CpjAsKeyInfo kEnbInf;

      CpjKenbStarInfo kEnbStarInf;


      CpjNhKeyInfo nhKeyInf;


   } u;
} CpjKdfReqInfo;



typedef struct cpjCfgTransId {
   U8 trans[9];
} CpjCfgTransId;
typedef struct cpjAskeyCfmInfo{
          U8 intKey[32];

          U8 upCiphKey[32];

          U8 cpCiphKey[32];

}CpjAskeyCfmInfo;


typedef struct cpjKenbStarCfmInfo{
           U8 secKey[32];

}CpjKenbStarCfmInfo;


typedef struct cpjNhKeyCfmInfo{
           U8 secKey[32];

}CpjNhKeyCfmInfo;

typedef struct cpjKdfCfmInfo {
   U8 keyDerType;


   union
   {
      CpjAskeyCfmInfo kEnbInf;
      CpjKenbStarCfmInfo kEnbStarInf;

      CpjNhKeyCfmInfo nhKeyInf;

   } u;
} CpjKdfCfmInfo;
typedef S16 (*CpjBndReq) (Pst *pst, SuId suId, SpId spId);
typedef S16 (*CpjBndCfm) (Pst *pst, SuId suId, U8 status);
typedef S16 (*CpjUbndReq) (Pst *pst, SpId spId, Reason reason);
typedef S16 (*CpjCfgReq) (Pst *pst, SpId spId, CpjCfgReqInfo *cfgReq);
typedef S16 (*CpjCfgCfm) (Pst *pst, SuId suId, CpjCfgCfmInfo *cfgCfm);
typedef S16 (*CpjReEstReq) (Pst *pst, SpId spId, CpjReEstReqInfo *reEstReq);
typedef S16 (*CpjReEstCfm) (Pst *pst, SuId suId, CpjReEstCfmInfo *reEstCfm);
typedef S16 (*CpjSecCfgReq) (Pst *pst, SpId spId, CpjSecCfgReqInfo *secCfgReq);
typedef S16 (*CpjSecCfgCfm) (Pst *pst, SuId suId, CpjSecCfgCfmInfo *secCfgCfm);
typedef S16 (*CpjUeIdChgReq) (Pst *pst, SpId spId, U32 transId, CpjUeInfo *oldUeInfo, CpjUeInfo *newUeInfo)

                                                          ;
typedef S16 (*CpjUeIdChgCfm) (Pst *pst, SuId suId, U32 transId, CpjUeInfo *ueInfo, CmStatus status)
                                                                         ;
typedef S16 (*CpjCountReq) (Pst *pst, SpId spId, CpjCountReqInfo *countReq);
typedef S16 (*CpjCountCfm) (Pst *pst, SuId suId, CpjCountCfmInfo *countCfm);
typedef S16 (*CpjSduStaReq) (Pst *pst, SpId spId, CpjSduStaReqInfo *staReq);
typedef S16 (*CpjSduStaCfm) (Pst *pst, SuId suId, CpjSduStaCfmInfo *staCfm);
typedef S16 (*CpjDataFwdReq) (Pst *pst, SpId spId, CpjDataFwdReqInfo *dataFwdReq);
typedef S16 (*CpjDatResumeReq) (Pst *pst, SpId spId, CpjDatResumeReqInfo *DatResumeReq)
                        ;
typedef S16 (*CpjDatResumeCfm) (Pst *pst, SuId suId, CpjDatResumeCfmInfo *dataResCfm);
typedef S16 (*CpjKdfReq) ( Pst* pst, SpId spId, CpjCfgTransId transId, CpjKdfReqInfo* cfgReqInfo)



                                    ;


typedef S16 (*CpjKdfCfm) ( Pst* pst, SuId suId, CpjCfgTransId transId, CpjKdfCfmInfo* kdfCfmInfo, U8 status)




                                ;
extern S16 PjUiCpjBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 PjUiCpjBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 PjUiCpjUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 PjUiCpjCfgReq (Pst *pst, SpId spId, CpjCfgReqInfo *cfgReq);
extern S16 PjUiCpjCfgCfm (Pst *pst, SuId suId, CpjCfgCfmInfo *cfgCfm);
extern S16 PjUiCpjReEstReq (Pst *pst, SpId spId, CpjReEstReqInfo *reEstReq);
extern S16 PjUiCpjReEstCfm (Pst *pst, SuId suId, CpjReEstCfmInfo *reEstCfm);
extern S16 PjUiCpjSecCfgReq (Pst *pst, SpId spId, CpjSecCfgReqInfo *secCfgReq)
                                      ;
extern S16 PjUiCpjSecCfgCfm (Pst *pst, SuId suId, CpjSecCfgCfmInfo *secCfgCfm)
                                      ;
extern S16 PjUiCpjUeIdChgReq (Pst *pst, SpId spId, U32 transId, CpjUeInfo *oldUeInfo, CpjUeInfo *newUeInfo)
                                                                               ;
extern S16 PjUiCpjUeIdChgCfm (Pst *pst, SuId suId, U32 transId, CpjUeInfo *ueInfo, CmStatus status)
                                                                      ;
extern S16 PjUiCpjCountReq (Pst *pst, SpId spId, CpjCountReqInfo *countReq);
extern S16 PjUiCpjCountCfm (Pst *pst, SuId suId, CpjCountCfmInfo *countCfm);
extern S16 PjUiCpjSduStaReq (Pst *pst, SpId spId, CpjSduStaReqInfo *staReq);
extern S16 PjUiCpjSduStaCfm (Pst *pst, SuId suId, CpjSduStaCfmInfo *staCfm);
extern S16 PjUiCpjDatResumeReq (Pst *pst, SpId spId, CpjDatResumeReqInfo *dataResReq)
                      ;

extern S16 PjUiCpjDatForwardReq ( Pst *pst, SpId spId, CpjDataFwdReqInfo *dataFwdReq)
                                        ;

extern S16 PjUiCpjDatResumeCfm ( Pst *pst, SuId suId, CpjDatResumeCfmInfo *datResCfm)
                     ;
extern S16 PjUiCpjKdfCfm ( Pst* pst, SuId suId, CpjCfgTransId transId, CpjKdfCfmInfo *kdfCfmInf, U8 status )





  ;

extern S16 PjUiCpjKdfReq ( Pst* pst, SpId spId, CpjCfgTransId transId, CpjKdfReqInfo *kdfReqInfo )




  ;

extern S16 cmPkCpjKdfReq ( Pst* pst, SpId spId, CpjCfgTransId transId, CpjKdfReqInfo *kdfReqInfo )




  ;



extern S16 cmUnpkCpjKdfReq ( CpjKdfReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCpjKdfCfm ( Pst* pst, SuId suId, CpjCfgTransId transId, CpjKdfCfmInfo *kdfCfmInfo, U8 status )





  ;

extern S16 cmUnpkCpjKdfCfm ( CpjKdfCfm func, Pst* pst, Buffer *mBuf )



  ;
 S16 cmPkCpjBndReq ( Pst * pst, SuId suId, SpId spId )



  ;
 S16 cmUnpkCpjBndReq ( CpjBndReq func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjBndCfm ( Pst * pst, SuId suId, U8 status )



  ;
 S16 cmUnpkCpjBndCfm ( CpjBndCfm func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjUbndReq ( Pst * pst, SpId spId, Reason reason )



  ;
 S16 cmUnpkCpjUbndReq ( CpjUbndReq func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjCfgReq ( Pst * pst, SpId spId, CpjCfgReqInfo * cfgReq )



  ;
 S16 cmUnpkCpjCfgReq ( CpjCfgReq func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjCfgCfm ( Pst * pst, SuId suId, CpjCfgCfmInfo * cfgCfm )



  ;
 S16 cmUnpkCpjCfgCfm ( CpjCfgCfm func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjReEstReq ( Pst * pst, SpId spId, CpjReEstReqInfo * reEstReq )



  ;
 S16 cmUnpkCpjReEstReq ( CpjReEstReq func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjReEstCfm ( Pst * pst, SuId suId, CpjReEstCfmInfo * reEstCfm )



  ;
 S16 cmUnpkCpjReEstCfm ( CpjReEstCfm func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjSecCfgReq ( Pst * pst, SpId spId, CpjSecCfgReqInfo * secCfgReq )



  ;
 S16 cmUnpkCpjSecCfgReq ( CpjSecCfgReq func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjSecCfgCfm ( Pst * pst, SuId suId, CpjSecCfgCfmInfo * secCfgCfm )



  ;
 S16 cmUnpkCpjSecCfgCfm ( CpjSecCfgCfm func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjUeIdChgReq ( Pst * pst, SpId spId, U32 transId, CpjUeInfo * oldUeInfo, CpjUeInfo * newUeInfo )





  ;
 S16 cmUnpkCpjUeIdChgReq ( CpjUeIdChgReq func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjUeIdChgCfm ( Pst * pst, SuId suId, U32 transId, CpjUeInfo * ueInfo, CmStatus status )





  ;
 S16 cmUnpkCpjUeIdChgCfm ( CpjUeIdChgCfm func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjCountReq ( Pst * pst, SpId spId, CpjCountReqInfo * countReq )



  ;
 S16 cmUnpkCpjCountReq ( CpjCountReq func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjCountCfm ( Pst * pst, SuId suId, CpjCountCfmInfo * countCfm )



  ;
 S16 cmUnpkCpjCountCfm ( CpjCountCfm func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjSduStaReq ( Pst * pst, SpId spId, CpjSduStaReqInfo * staReq )



  ;
 S16 cmUnpkCpjSduStaReq ( CpjSduStaReq func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjStartDataFwdReq ( Pst * pst, SpId spId, CpjDataFwdReqInfo * dataFwdReq )



  ;
 S16 cmUnpkCpjStartDataFwdReq ( CpjDataFwdReq func, Pst *pst, Buffer *mBuf )



  ;

 S16 cmPkCpjDatResumeReq ( Pst * pst, SpId spId, CpjDatResumeReqInfo * dataFwdReq )



  ;

 S16 cmUnpkCpjDatResumeReq ( CpjDatResumeReq func, Pst *pst, Buffer *mBuf )



  ;

 S16 cmPkCpjSduStaCfm ( Pst * pst, SuId suId, CpjSduStaCfmInfo * staCfm )



  ;
 S16 cmUnpkCpjSduStaCfm ( CpjSduStaCfm func, Pst *pst, Buffer *mBuf )



  ;
 S16 cmPkCpjRlcAm ( CpjRlcAm *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjRlcAm ( CpjRlcAm *param, Buffer *mBuf )


  ;
 S16 cmPkCpjRlcUm ( CpjRlcUm *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjRlcUm ( CpjRlcUm *param, Buffer *mBuf )


  ;
 S16 cmPkCpjRlcInfo ( CpjRlcInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjRlcInfo ( CpjRlcInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjCipherInfo ( CpjCipherInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjCipherInfo ( CpjCipherInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjIntegInfo ( CpjIntegInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjIntegInfo ( CpjIntegInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjSecCfg ( CpjSecCfg *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjSecCfg ( CpjSecCfg *param, Buffer *mBuf )


  ;
 S16 cmPkCpjRohcInfo ( CpjRohcInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjRohcInfo ( CpjRohcInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjHdrCompCfg ( CpjHdrCompCfg *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjHdrCompCfg ( CpjHdrCompCfg *param, Buffer *mBuf )


  ;
 S16 cmPkCpjHoInfo ( Pst *pst, CpjHoInfo *param, Buffer *mBuf )



  ;
 S16 cmUnpkCpjHoInfo ( Pst *pst, CpjHoInfo *param, Buffer *mBuf )



  ;
 S16 cmPkCpjCfgEnt ( Pst *pst, CpjCfgEnt *param, Buffer *mBuf )



  ;
 S16 cmUnpkCpjCfgEnt ( Pst *pst, CpjCfgEnt *param, Buffer *mBuf )



  ;
 S16 cmPkCpjAddCfgEnt ( CpjAddCfgEnt *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjAddCfgEnt ( CpjAddCfgEnt *param, Buffer *mBuf )


  ;
 S16 cmPkCpjModCfgEnt ( Pst *pst, CpjModCfgEnt *param, Buffer *mBuf )



  ;
 S16 cmUnpkCpjModCfgEnt ( Pst *pst, CpjModCfgEnt *param, Buffer *mBuf )



  ;
 S16 cmPkCpjCfgReqInfo ( Pst *pst, CpjCfgReqInfo *param, Buffer *mBuf )



  ;
 S16 cmUnpkCpjCfgReqInfo ( Pst *pst, CpjCfgReqInfo *param, Buffer *mBuf )



  ;
 S16 cmPkCpjCfmEnt ( CpjCfmEnt *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjCfmEnt ( CpjCfmEnt *param, Buffer *mBuf )


  ;
 S16 cmPkCpjCfgCfmInfo ( CpjCfgCfmInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjCfgCfmInfo ( CpjCfgCfmInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjReEstReqInfo ( CpjReEstReqInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjReEstReqInfo ( CpjReEstReqInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjReEstCfmInfo ( CpjReEstCfmInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjReEstCfmInfo ( CpjReEstCfmInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjSecCfgReqInfo ( CpjSecCfgReqInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjSecCfgReqInfo ( CpjSecCfgReqInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjSecCfgCfmInfo ( CpjSecCfgCfmInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjSecCfgCfmInfo ( CpjSecCfgCfmInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjUeInfo ( CpjUeInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjUeInfo ( CpjUeInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjCountReqInfo ( CpjCountReqInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjCountReqInfo ( CpjCountReqInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjCountInfo ( CpjCountInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjCountInfo ( CpjCountInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjCountCfmInfo ( CpjCountCfmInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjCountCfmInfo ( CpjCountCfmInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjSduStaReqInfo ( CpjSduStaReqInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjSduStaReqInfo ( CpjSduStaReqInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjStartDataFwdReqInfo ( CpjDataFwdReqInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjStartDataFwdReqInfo ( CpjDataFwdReqInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjDatResumeReqInfo ( CpjDatResumeReqInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjDatResumeReqInfo ( CpjDatResumeReqInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjUlSduStaInfo ( Pst *pst, CpjUlSduStaInfo *param, Buffer *mBuf )



  ;
 S16 cmUnpkCpjUlSduStaInfo ( Pst *pst, CpjUlSduStaInfo *param, Buffer *mBuf )



  ;
 S16 cmPkCpjDlSduStaInfo ( CpjDlSduStaInfo *param, Buffer *mBuf )


  ;
 S16 cmUnpkCpjDlSduStaInfo ( CpjDlSduStaInfo *param, Buffer *mBuf )


  ;
 S16 cmPkCpjSduStaInfo ( Pst *pst, CpjSduStaInfo *param, Buffer *mBuf )



  ;
 S16 cmUnpkCpjSduStaInfo ( Pst *pst, CpjSduStaInfo *param, Buffer *mBuf )



  ;
 S16 cmPkCpjSduStaCfmInfo ( Pst *pst, CpjSduStaCfmInfo *param, Buffer *mBuf )



  ;
 S16 cmUnpkCpjSduStaCfmInfo ( Pst *pst, CpjSduStaCfmInfo *param, Buffer *mBuf )



  ;
 S16 cmUnpkCpjDatResumeCfmInfo ( Pst *pst, CpjDatResumeCfmInfo *param, Buffer *mBuf )



  ;

 S16 cmPkCpjDataResCfmInfo ( Pst *pst, CpjDatResumeCfmInfo *param, Buffer *mBuf )



  ;

 S16 cmUnpkCpjDatResumeCfm ( CpjDatResumeCfm func, Pst *pst, Buffer *mBuf )



  ;

 S16 cmPkCpjDatResumeCfm ( Pst * pst, SuId suId, CpjDatResumeCfmInfo * dataResCfm )



  ;

 S16 cmUnpkCpjDatResumeCfm ( CpjDatResumeCfm func, Pst *pst, Buffer *mBuf )



  ;

 S16 cmUnpkCpjNhKeyCfmInfo ( CpjNhKeyCfmInfo *param, Buffer *mBuf )


  ;

 S16 cmUnpkCpjKenbStarCfmInfo ( CpjKenbStarCfmInfo *param, Buffer *mBuf )


  ;

 S16 cmUnpkCpjAskeyCfmInfo ( CpjAskeyCfmInfo *param, Buffer *mBuf )


  ;

 S16 cmUnpkCpjKdfCfmInfo ( CpjKdfCfmInfo *param, Buffer *mBuf )


  ;

 S16 cmUnpkCpjCfgTransId ( CpjCfgTransId *param, Buffer *mBuf )


  ;

 S16 cmPkCpjNhKeyInfo ( CpjNhKeyInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjKenbStarInfo ( CpjKenbStarInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjAskeyInfo ( CpjAsKeyInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjKdfReqInfo ( CpjKdfReqInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjCfgTransId ( CpjCfgTransId *param, Buffer *mBuf )


  ;

 S16 cmUnpkCpjNhKeyInfo ( CpjNhKeyInfo *param, Buffer *mBuf )


  ;

 S16 cmUnpkCpjKenbStarInfo ( CpjKenbStarInfo *param, Buffer *mBuf )


  ;

 S16 cmUnpkCpjAskeyInfo ( CpjAsKeyInfo *param, Buffer *mBuf )


  ;

 S16 cmUnpkCpjKdfReqInfo ( CpjKdfReqInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjNhKeyCfmInfo ( CpjNhKeyCfmInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjKenbStarCfmInfo ( CpjKenbStarCfmInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjAskeyCfmInfo ( CpjAskeyCfmInfo *param, Buffer *mBuf )


  ;

 S16 cmPkCpjKdfCfmInfo ( CpjKdfCfmInfo *param, Buffer *mBuf )


  ;
typedef U32 PjuSduId;
typedef U32 PjuSduLen;





typedef struct pjuDatCfmSta
{
   PjuSduId sduId;
   U8 status;




}PjuDatCfmSta;





typedef struct pjuDatCfmInfo
{
   U16 numSdus;
   PjuDatCfmSta cfmSta[1024];
}PjuDatCfmInfo;




typedef struct pjuStaIndInfo
{
   U8 cause;
}PjuStaIndInfo;




typedef struct pjuDatFwdInfo
{
   PjuSduId sduId;
   U16 sn;
   Buffer *sdu;

}PjuDatFwdInfo;






typedef struct pjuDatFwdReqInfo
{
   U8 dir;

   U16 numSdus;
   PjuDatFwdInfo *datFwdInfo;
   Bool isLastDatFwdInd;
}PjuDatFwdReqInfo;





typedef PjuDatFwdReqInfo PjuDatFwdIndInfo;
typedef struct pjuDatReqInfo
{
  SpId spId;
  CmLtePdcpId pdcpId;
  PjuSduId sduId;
}PjuDatReqInfo;
typedef struct pjuDatIndInfo
{
  SuId suId;
  CmLtePdcpId pdcpId;
}PjuDatIndInfo;
typedef S16 (*PjuBndReq) ( Pst *, SuId, SpId )



          ;

typedef S16 (*PjuBndCfm) ( Pst *, SuId, U8 )



          ;

typedef S16 (*PjuUbndReq) ( Pst *, SpId, Reason )



          ;

typedef S16 (*PjuDatReq) ( Pst *, SpId, CmLtePdcpId *, PjuSduId, Buffer * )





          ;
typedef S16 (*PjuDatCfm) ( Pst *, SuId, CmLtePdcpId *, PjuDatCfmInfo * )




          ;

typedef S16 (*PjuDatInd) ( Pst *, SuId, CmLtePdcpId *, Buffer * )




          ;

typedef S16 (*PjuStaInd) ( Pst *, SuId, CmLtePdcpId *, PjuStaIndInfo *, Buffer * )





          ;

typedef S16 (*PjuDatFwdReq) ( Pst *, SpId, CmLtePdcpId *, PjuDatFwdReqInfo * )




          ;

typedef S16 (*PjuDatFwdInd) ( Pst *, SuId, CmLtePdcpId *, PjuDatFwdIndInfo * )




          ;
extern S16 PjUiPjuBndReq ( Pst* , SuId , SpId);
extern S16 PjUiPjuBndCfm ( Pst*, SuId, U8);
extern S16 PjUiPjuUbndReq ( Pst*, SpId, Reason);
extern S16 PjUiPjuDatReq ( Pst*, SpId, CmLtePdcpId *, PjuSduId, Buffer*);
extern S16 PjUiPjuDatCfm (Pst*, SuId, CmLtePdcpId *, PjuDatCfmInfo *);
extern S16 PjUiPjuDatInd (Pst*, SuId, CmLtePdcpId *, Buffer*);
extern S16 PjUiPjuStaInd (Pst*, SuId, CmLtePdcpId *, PjuStaIndInfo *, Buffer *);
extern S16 PjUiPjuDatFwdReq (Pst*, SpId, CmLtePdcpId *, PjuDatFwdReqInfo *);
extern S16 PjUiPjuDatFwdInd (Pst*, SuId, CmLtePdcpId *, PjuDatFwdIndInfo *);
extern S16 PxLiPjuBndReq ( Pst *, SuId, SpId )



         ;

extern S16 PxLiPjuUbndReq ( Pst *, SuId, Reason )



         ;

extern S16 PxLiPjuDatReq ( Pst *, SpId, CmLtePdcpId *, PjuSduId, Buffer * )





         ;

extern S16 PxLiPjuBndCfm ( Pst *, SuId, U8 )



         ;

extern S16 PxLiPjuDatInd ( Pst *, SuId, CmLtePdcpId *, Buffer * )




         ;

extern S16 PxLiPjuDatCfm ( Pst *, SuId , CmLtePdcpId *, PjuDatCfmInfo * )




         ;

extern S16 PxLiPjuStaInd ( Pst*, SuId, CmLtePdcpId *, PjuStaIndInfo * , Buffer * )





         ;

extern S16 PxLiPjuDatFwdReq ( Pst *, SpId, CmLtePdcpId *, PjuDatFwdReqInfo * )




         ;


extern S16 PxLiPjuDatFwdInd ( Pst *, SuId, CmLtePdcpId *, PjuDatFwdIndInfo * )




         ;
extern S16 cmPkPjuBndReq ( Pst* pst, SpId suId, SuId spId )



  ;
extern S16 cmUnpkPjuBndReq ( PjuBndReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuBndCfm ( Pst* pst, SuId suId, U8 status )



  ;
extern S16 cmUnpkPjuBndCfm ( PjuBndCfm func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;
extern S16 cmUnpkPjuUbndReq ( PjuUbndReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuDatReq ( Pst* pst, SpId spId, CmLtePdcpId * pdcpId, PjuSduId sduId, Buffer * mBuf )





  ;
extern S16 cmUnpkPjuDatReq ( PjuDatReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuDatCfm ( Pst* pst, SuId suId, CmLtePdcpId * pdcpId, PjuDatCfmInfo * datCfm )




  ;
extern S16 cmUnpkPjuDatCfm ( PjuDatCfm func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuDatInd ( Pst* pst, SuId suId, CmLtePdcpId * pdcpId, Buffer * mBuf )




  ;
extern S16 cmUnpkPjuDatInd ( PjuDatInd func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuStaInd ( Pst* pst, SuId suId, CmLtePdcpId * pdcpId, PjuStaIndInfo * staInd, Buffer *buff )





  ;
extern S16 cmUnpkPjuStaInd ( PjuStaInd func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuDatFwdReq ( Pst* pst, SpId spId, CmLtePdcpId * pdcpId, PjuDatFwdReqInfo * datFwdReq )




  ;
extern S16 cmUnpkPjuDatFwdReq ( PjuDatFwdReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuDatFwdInd ( Pst* pst, SuId suId, CmLtePdcpId * pdcpId, PjuDatFwdIndInfo * datFwdInd )




  ;
extern S16 cmUnpkPjuDatFwdInd ( PjuDatFwdInd func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjuDatCfmInfoSta ( PjuDatCfmSta *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjuDatCfmInfoSta ( PjuDatCfmSta *param, Buffer *mBuf )


  ;
extern S16 cmPkPjuDatCfmInfo ( PjuDatCfmInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjuDatCfmInfo ( PjuDatCfmInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkPjuStaIndInfo ( PjuStaIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjuStaIndInfo ( PjuStaIndInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkPjuDatFwdReqInfo ( PjuDatFwdReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjuDatFwdReqInfo ( Pst *pst, PjuDatFwdReqInfo *param, Buffer *mBuf )



  ;
extern S16 cmPkPjuDatFwdInfo ( PjuDatFwdInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjuDatFwdInfo ( PjuDatFwdInfo *param, Buffer *mBuf )


  ;
typedef struct pjGenCfg
{
   Pst lmPst;

   Ticks timeRes;
   U8 mode;
   U8 maxPjuSaps;
   U8 maxKwuSaps;
   U8 maxUdxSaps;
   U8 nmbUlBins;

   U8 nmbDlBins;

   U32 maxUe;
}PjGenCfg;



typedef struct pjSapCfg
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
}PjSapCfg;




typedef struct pjCfg
{
   union
   {
      PjGenCfg gen;
      PjSapCfg sap;
   }s;
}PjCfg;



typedef struct pjGenSts
{
   CntrSts numUe;
   CntrSts numOfRb;
   CntrSts rxPdus;
   CntrSts txPdus;
   CntrSts errorPdusRecv;
   CntrSts numSdusDisc;

   CntrSts numCmpFails;
   CntrSts numDecmpFails;
   CntrSts numIntgPrtFails;
   CntrSts numIntgVrfFails;
   CntrSts numCiphFails;
   CntrSts numDeciphFails;
   CntrSts numPdusDiscObdTmrExp;

   CntrSts numSdusDiscObdTmrExp;

   CntrSts numPktsFrwd;

   CntrSts numPktsRcvd;

}PjGenSts;



typedef struct pjPjuSts
{

   SpId spId;
   CntrSts rxSdus;
   CntrSts txSdus;
}PjPjuSts;


typedef struct pjSts
{
   DateTime dt;
   union
   {
      PjGenSts gen;
      PjPjuSts pjuSap;
   }s;
}PjSts;



typedef struct pjPjuSapSta
{
   SpId spId;
   State state;
}PjPjuSapSta;



typedef struct pjUdxSapSta
{
   SpId spId;
   State state;
}PjUdxSapSta;




typedef struct pjKwuSapSta
{
   SpId spId;
   State state;
}PjKwuSapSta;



typedef struct pjCpjSapSta
{
   SpId spId;
   State state;
}PjCpjSapSta;



typedef struct pjSSta
{
   DateTime dt;
   union
   {
      SystemId sysId;
      PjCpjSapSta cpjSap;
      PjPjuSapSta pjuSap;
      PjKwuSapSta kwuSap;
      PjUdxSapSta udxSap;
   }s;
}PjSSta;



typedef struct pjTrcCntrl
{
   U8 trcMask;
   S16 trcLen;
}PjTrcCntrl;



typedef struct pjDbgCntrl
{
   U32 dbgMask;

}PjDbgCntrl;



typedef struct pjSapCntrl
{
   SuId suId;
   SpId spId;
}PjSapCntrl;



typedef struct pjCntrl
{
   DateTime dt;
   U8 action;
   U8 subAction;
   union
   {
      PjTrcCntrl trcCntrl;
      PjDbgCntrl dbgCntrl;



      PjSapCntrl sapCntrl;
   }s;
}PjCntrl;



typedef struct pjUSta
{
   DateTime dt;
   CmAlarm alarm;
   SuId suId;
   U32 ueId;




}PjUSta;



typedef struct pjTrc
{
   DateTime dt;
   U16 event;

}PjTrc;



typedef struct _pjMngmt
{
   Header hdr;
   CmStatus cfm;
   union
   {
      PjCfg cfg;
      PjCntrl cntrl;
      PjSts sts;
      PjSSta ssta;
      PjUSta usta;
      PjTrc trc;
   }t;
}PjMngmt;
typedef S16 (*LpjCfgReq) (Pst *pst, PjMngmt *cfg);
typedef S16 (*LpjCfgCfm) (Pst *pst, PjMngmt *cfgCfm);

typedef S16 (*LpjCntrlReq) (Pst *pst, PjMngmt *cntl);
typedef S16 (*LpjCntrlCfm) (Pst *pst, PjMngmt *cntlCfm);

typedef S16 (*LpjStaInd) (Pst *pst, PjMngmt *staInd);
typedef S16 (*LpjStaReq) (Pst *pst, PjMngmt *staReq);
typedef S16 (*LpjStaCfm) (Pst *pst, PjMngmt *staCfm);

typedef S16 (*LpjStsReq) (Pst *pst, Action, PjMngmt *sts);
typedef S16 (*LpjStsCfm) (Pst *pst, Action, PjMngmt *stsCfm);

typedef S16 (*LpjTrcInd) (Pst *pst, PjMngmt *trc, Buffer *mBuf);
extern S16 PjMiLpjCfgReq (Pst *pst, PjMngmt *cfg);
extern S16 PjMiLpjCfgCfm (Pst *pst, PjMngmt *cfgCfm);
extern S16 PjMiLpjCntrlReq (Pst *pst, PjMngmt *cntl);
extern S16 PjMiLpjCntrlCfm (Pst *pst, PjMngmt *cntlCfm);
extern S16 PjMiLpjStaReq (Pst *pst, PjMngmt *staInd);
extern S16 PjMiLpjStaCfm (Pst *pst, PjMngmt *staCfm);
extern S16 PjMiLpjStsReq (Pst *pst, Action, PjMngmt *sts);
extern S16 PjMiLpjStsCfm (Pst *pst, Action action, PjMngmt *stsCfm);
extern S16 PjMiLpjTrcInd (Pst *pst, PjMngmt *trc, Buffer *mBuf);
extern S16 PjMiLpjStaInd (Pst *pst, PjMngmt *staReq);
extern Void pjSendLmAlarm (U16 category, U16 event, U16 cause, SuId suId, U32 ueId)



                ;
extern S16 smPjActvInit (Ent ent, Inst inst, Region region, Reason reason);
extern S16 smPjActvTsk (Pst *pst, Buffer *mBuf);




extern S16 cmPkLpjCfgReq ( Pst * pst, PjMngmt * cfg )


  ;
extern S16 cmUnpkLpjCfgReq ( LpjCfgReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjCfgCfm ( Pst * pst, PjMngmt * cfgCfm )


  ;
extern S16 cmUnpkLpjCfgCfm ( LpjCfgCfm func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjCntrlReq ( Pst * pst, PjMngmt * cntl )


  ;
extern S16 cmUnpkLpjCntrlReq ( LpjCntrlReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjCntrlCfm ( Pst * pst, PjMngmt * cntlCfm )


  ;
extern S16 cmUnpkLpjCntrlCfm ( LpjCntrlCfm func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjStaInd ( Pst * pst, PjMngmt * staInd )


  ;
extern S16 cmUnpkLpjStaInd ( LpjStaInd func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjStaReq ( Pst * pst, PjMngmt * staReq )


  ;
extern S16 cmUnpkLpjStaReq ( LpjStaReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjStaCfm ( Pst * pst, PjMngmt * staCfm )


  ;
extern S16 cmUnpkLpjStaCfm ( LpjStaCfm func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjStsReq ( Pst * pst, Action actn, PjMngmt * sts )



  ;
extern S16 cmUnpkLpjStsReq ( LpjStsReq func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjStsCfm ( Pst * pst, Action actn, PjMngmt * stsCfm )



  ;
extern S16 cmUnpkLpjStsCfm ( LpjStsCfm func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkLpjTrcInd ( Pst * pst, PjMngmt * trc, Buffer * mBuf )



  ;
extern S16 cmUnpkLpjTrcInd ( LpjTrcInd func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkPjGenCfg ( PjGenCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjGenCfg ( PjGenCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkPjSapCfg ( PjSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjSapCfg ( PjSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkPjCfg ( PjMngmt *cfg, Elmnt elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkPjCfg ( PjMngmt *cfg, Elmnt elmnt, Buffer *mBuf )



  ;
extern S16 cmPkPjGenSts ( PjGenSts *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjGenSts ( PjGenSts *param, Buffer *mBuf )


  ;
extern S16 cmPkPjPjuSts ( PjPjuSts *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjPjuSts ( PjPjuSts *param, Buffer *mBuf )


  ;
extern S16 cmPkPjSts ( PjMngmt *sts, Elmnt elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkPjSts ( PjMngmt *sts, Elmnt elmnt, Buffer *mBuf )



  ;
extern S16 cmPkPjPjuSapSta ( PjPjuSapSta *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjPjuSapSta ( PjPjuSapSta *param, Buffer *mBuf )


  ;
extern S16 cmPkPjCpjSapSta ( PjCpjSapSta *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjCpjSapSta ( PjCpjSapSta *param, Buffer *mBuf )


  ;
extern S16 cmPkPjSSta ( PjMngmt *ssta, Elmnt elmnt, Event eventType, Buffer *mBuf )




  ;
extern S16 cmUnpkPjSSta ( PjMngmt *ssta, Elmnt elmnt, Event eventType, Buffer *mBuf )




  ;
extern S16 cmPkPjTrcCntrl ( PjTrcCntrl *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjTrcCntrl ( PjTrcCntrl *param, Buffer *mBuf )


  ;
extern S16 cmPkPjDbgCntrl ( PjDbgCntrl *param, Buffer *mBuf )


  ;
extern S16 cmUnpkPjDbgCntrl ( PjDbgCntrl *param, Buffer *mBuf )


  ;
extern S16 cmPkPjCntrl ( PjMngmt *cntrl, Elmnt elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkPjCntrl ( PjMngmt *cfm, Elmnt elmnt, Buffer *mBuf )



  ;
extern S16 cmPkPjUSta ( PjMngmt *usta, Elmnt elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkPjUSta ( PjMngmt *usta, Elmnt elmnt, Buffer *mBuf )



  ;
extern S16 cmPkPjTrc ( PjMngmt *trc, Buffer *mBuf )


  ;
extern S16 cmUnpkPjTrc ( PjMngmt *trc, Buffer *mBuf )


  ;
extern S16 cmPkPjMngmt ( PjMngmt *param, Event eventType, Buffer *mBuf )



  ;
extern S16 cmUnpkPjMngmt ( PjMngmt *param, Event eventType, Buffer *mBuf )



  ;
typedef U16 PjSn;
typedef struct pjCfmEnt
{
   U8 rbId;
   U8 rbType;
   U8 cfgType;
   U8 res1;
   Status status;
   Reason reason;
}PjCfmEnt;






typedef struct pjAsyncCfm
{
   U8 cfmType;


   U8 startTmr;
   U8 entity;
   U8 numEnt;
   U32 libInitBitMask;
   U32 cmpInitBitMask;
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   PjCfmEnt cfmEnt[10];

}PjAsyncCfm;




typedef struct pjLibInfo
{
   U8 state;
   U8 res[1];
   U16 numReEstCmp;
   U16 numReEstDrb;
   CmTimer obdTmr;
   U32 tLibInitBitMask;
   U32 tCmpInitBitMask;
   PjAsyncCfm *asyncCfm[2];

   U16 nxtAvlbTxId;

   U16 crntTmrTxId;
   Bool onlySrb1;
   Bool waitForReEstTrig;



}PjLibInfo;



typedef struct pjSecInp
{
   U32 count;
   CmLteRbId rbId;
   U8 dir;
   U8 res[2];
}PjSecInp;



typedef struct pjCmpCxt
{
   CmLteCellId cellId;
   CmLteRnti ueId;
   CmLteRbId rbId;
   U8 rbType;
   U16 cfgTxId;
}PjCmpCxt;



typedef struct pjSecCxt
{
   CmLteCellId cellId;
   CmLteRnti ueId;
   U16 cfgTxId;
   U16 res;
   U8 dir;
}PjSecCxt;



typedef struct pjLibTrans
{

   CmLteCellId cellId;
   CmLteRnti ueId;
   U8 pdcpInstance;
   U8 hash_key[32];
   U8 strS[9];
   U8 strSlen;
   U8 intAlgoType;
   U8 fresh[4];
   U8 ciphAlgoType;
   U8 *key;
   U32 count;
   CmLteRbId rbId;
   U8 rbType;
   U16 res;
   U32 ueCb;



   U8 dir;
   U8 snLen;
}PjLibTrans;



typedef struct pjIntInfo
{
   U32 algoType;
   U8 intKey[16];
}PjIntInfo;



typedef struct pjCipherInfo
{
   U32 algoType;
   U8 cpKey[16];
   U8 upKey[16];
}PjCipherInfo;



typedef struct pjSec
{
   Bool secAct;

   Bool selSecAct;

   Bool firstMsg;

   PjIntInfo intInfo;
   PjCipherInfo cipherInfo;
   PjSecCxt secCxt;

   Void *intCxtId;

   Void *cpCxtId;

   Void *upCxtId;

}PjSec;



typedef struct pjBuf
{
   U8 numBins;
   U8 res1[3];
   U32 numEntries;
   CmLListCp *datQ;
   CmLListCp datCfmQ;
   CmLListCp sduSubmitQ;
   CmLListCp reEstPktQ;
   CmLListCp datPktQ;



}PjBuf;

typedef struct pjUeKey
{
   CmLteRnti ueId;
   CmLteCellId cellId;
}PjUeKey;



typedef struct pjCpjSapCb
{
   Pst pst;
   SpId spId;
   SuId suId;
   U8 state;
   U8 res[3];
}PjCpjSapCb;



typedef struct pjPjuSapCb
{
   SpId spId;
   SuId suId;
   U8 state;
   U8 res[3];
   PjPjuSts sts;
   Pst pst;
}PjPjuSapCb;

typedef struct pjUdxDlSapCb
{
   SpId spId;
   SuId suId;
   U8 state;
   U8 res[3];
   PjPjuSts sts;
   Pst pst;
}PjUdxDlSapCb;


typedef struct pjUdxUlSapCb
{
   Pst pst;
   SpId spId;
   SuId suId;
   U8 state;
   U8 retryCnt;
   U16 bndTmrInt;
   CmTimer bndTmr;
}PjUdxUlSapCb;


typedef struct pjKwuSapCb
{
   Pst pst;
   SpId spId;
   SuId suId;
   U8 state;
   U8 retryCnt;
   U16 bndTmrInt;
   CmTimer bndTmr;
}PjKwuSapCb;



typedef struct pjRohc
{
        Bool hdrCmpUsed;
        U8 res[3];
        U16 maxCid;
        U16 profId;
}PjRohc;
typedef struct pjCfgInfo
{
   CmHashListEnt transHlEnt;
   U32 transId;
   U32 uprLyrTransId;
   U8 cfgType;
   CpjCfgReqInfo *cfgInfo;
   CpjUeInfo *ueInfo;
   CpjUeInfo *newUeInfo;
   CpjSecCfgReqInfo *secCfgInfo;
   CpjReEstReqInfo *reEstReq;
   CpjCountReqInfo *cntReq;
   CpjSduStaReqInfo *staReq;
   CpjDatResumeReqInfo *datResReq;
} PjCfgInfo;



typedef struct _pjPerfSts
{
   U32 pjSduRcvCnt;
}PjPerfSts;




typedef struct _pjUlCb
{
   U32 transId;
   PjCpjSapCb cpjSap;
   PjUdxUlSapCb udxUlSap[1];
   PjPjuSapCb pjuSap[2];
   PjKwuSapCb kwuSap[2];
   CmHashListCp transIdLstCp;
   CmHashListCp ueLstCp;



}PjUlgCb;




typedef struct _pjDlCb
{
   PjUdxDlSapCb udxDlSap[1];
   PjPjuSapCb pjuSap[2];
   PjKwuSapCb kwuSap[2];
   PjGenSts pjGenSts;
   CmHashListCp ueLstCp;



}PjDlgCb;




typedef struct _pjCb
{
   CmTqType pjTq[10];
   CmTqCp pjTqCp;
   S16 trcLen;
   U8 trcMask;
   TskInit init;
   PjGenCfg pjGenCfg;
   PjGenSts pjGenSts;
   PjPerfSts pjPerfSts;
   union
   {
      PjUlgCb *ulCb;
      PjDlgCb *dlCb;
   } u;
}PjCb;

typedef struct _pdcpStats
{
    U32 numPdcpSdusDiscarded;
    U32 numPdcpSdusDiscMem;
}PDCPStats;

extern PDCPStats gPdcpStats;


extern PjCb *pjCb[2];


extern S16 pjStartTmr ( PjCb *gCb, U32 cb, S16 tmrEvnt )



  ;

extern S16 pjStopTmr ( PjCb *gCb, U32 cb, U8 tmrType )



  ;

extern Bool pjChkTmr ( PjCb *gCb, U32 cb, S16 tmrEvnt )



  ;

extern S16 pjTmrExpiry ( U32 cb, S16 tmrEvnt )


  ;
extern S16 pjDbmBufInit ( PjCb *gCb, PjBuf *buf, U8 numBins )



  ;

extern S16 pjLmmSendTrc (PjCb *gCb, Event event, Buffer *mBuf);




extern Void pjLmmSendAlarm (PjCb *gCb, U16 category, U16 event, U16 cause, SuId suId, U32 ueId)

                                                        ;

extern S16 pjUtlCmpClose ( PjCb *gCb, U32 cmpCxtId )


  ;
extern S16 pjDlActvInit ( Ent ent, Inst inst, Region region, Reason reason )




  ;

extern S16 pjDlActvTsk ( Pst *pst, Buffer *mBuf )


  ;


extern S16 pjUlActvInit ( Ent ent, Inst inst, Region region, Reason reason )




  ;

extern S16 pjUlActvTsk ( Pst *pst, Buffer *mBuf )


  ;

extern U32 pjMsCheckSpaccQueue (Bool isUl);
extern Void pjProcessSpaccRdWr ( U32 ttitick )

  ;
typedef U8 UdxCipherKey;





typedef U8 UdxIntegrityKey;





typedef struct udxRlcAm
{
   Bool statusRepReqd;
   U8 pdcpSNSize;
}UdxRlcAm;





typedef struct udxRlcUm
{
   U8 pdcpSNSize;
}UdxRlcUm;





typedef struct udxRlcInfo
{
   U8 dir;
   U8 mode;
   union
   {
      UdxRlcAm rlcAm;
      UdxRlcUm rlcUm;
   }m;
}UdxRlcInfo;






typedef struct udxCipherInfo
{
   UdxCipherKey ctrlplnKey[16];

   UdxCipherKey usrplnKey[16];

   U8 algoType;





}UdxCipherInfo;





typedef struct udxIntegInfo
{
   U8 algoType;




   UdxIntegrityKey intKey[16];
} UdxIntegInfo;





typedef struct udxSecCfg
{
   Bool selSecAct;







   Bool isHo;
   UdxIntegInfo integInfo;
   UdxCipherInfo cipherInfo;
} UdxSecCfg;





typedef struct udxRohcInfo
{
   U16 maxCid;
   Bool profLst[9];

}UdxRohcInfo;





typedef struct udxHdrCompCfg
{
   Bool hdrCompUsed;
   UdxRohcInfo rohcInfo;
}UdxHdrCompCfg;





typedef struct udxHoInfo
{
   U8 isHoPres;





   U8 snLen;
   U32 dlCount;
   U32 ulCount;
   U16 numBits;
   U8 *ulBitMap;

} UdxHoInfo;





typedef struct udxAddCfgEnt
{
   Bool discReqd;

   Bool cfmReqd;






   UdxRlcInfo rlcInfo;
   S16 discardTmr;



   UdxHdrCompCfg hdrCompCfg;
}UdxAddCfgEnt;





typedef struct udxModCfgEnt
{

   U8 bitFlag;


   Bool discReqd;


   Bool cfmReqd;


   UdxHdrCompCfg hdrCompCfg;
   UdxHoInfo hoInfo;
}UdxModCfgEnt;






typedef struct udxCfgEnt
{
   U8 rbId;
   U8 cfgType;





   U8 rbType;



   union{
        UdxAddCfgEnt addCfg;

        UdxModCfgEnt modCfg;

   }m;
}UdxCfgEnt;
typedef struct udxCfgReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   U8 numEnt;

   U8 isHo;

   SpId rlcUlSapId;
   SpId rlcDlSapId;

   UdxCfgEnt cfgEnt[10];

}UdxCfgReqInfo;






typedef struct udxUlStaRepInfo
{
   CmLtePdcpId pdcpId;
   Buffer *sta;
}UdxUlStaRepInfo;





typedef struct udxDlStaRepInfo
{
   CmLtePdcpId pdcpId;
   U16 fms;
   Buffer *staPdu;
}UdxDlStaRepInfo;






typedef struct udxUlFdbkPktInfo
{
    CmLtePdcpId pdcpId;
    Buffer *fbPkt;
}UdxUlFdbkPktInfo;





typedef struct udxDlFdbkPktInfo
{
    CmLtePdcpId pdcpId;
    Buffer *fbPkt;
}UdxDlFdbkPktInfo;






typedef struct udxCfmEnt
{
   U8 rbId;
   U8 rbType;
   Status status;
   Reason reason;
}UdxCfmEnt;





typedef struct udxCfgCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   U8 numEnt;
   UdxCfmEnt cfmEnt[10];

}UdxCfgCfmInfo;





typedef struct udxReEstReqInfo
{
   CmLtePdcpId pdcpId;
   U32 transId;
   U8 intKey[16];
   UdxCipherKey ctrlplnKey[16];

   UdxCipherKey usrplnKey[16];

}UdxReEstReqInfo;





typedef struct udxReEstCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   Status status;




}UdxReEstCfmInfo;






typedef struct udxSecCfgReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   UdxSecCfg secCfg;
}UdxSecCfgReqInfo;





typedef struct udxSecCfgCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   Status status;
   Reason reason;
}UdxSecCfgCfmInfo;





typedef struct udxUeInfo
{
   CmLteCellId cellId;
   CmLteRnti ueId;
}UdxUeInfo;





typedef struct udxCountReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
} UdxCountReqInfo;





typedef struct udxCountInfo
{
   U8 rbId;
   U8 dir;
   U32 ulCount;
   U32 dlCount;
} UdxCountInfo;




typedef struct udxCountCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   U8 numRb;
   UdxCountInfo countInfo[12];
   Status status;
   Reason reason;
} UdxCountCfmInfo;






typedef struct udxSduStaReqInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
} UdxSduStaReqInfo;





typedef struct udxDlSduStaInfo
{
   Bool hoPres;
   U32 count;

} UdxDlSduStaInfo;





typedef struct udxSduStaInfo
{
   U8 rbId;
   U8 dir;
   UdxDlSduStaInfo dlSduStaInfo;
} UdxSduStaInfo;





typedef struct udxSduStaCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   U8 numRb;
   UdxSduStaInfo sduStaInfo[12];

   Status status;
   Reason reason;
} UdxSduStaCfmInfo;





typedef struct udxDatResumeInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
} UdxDatResumeInfo;





typedef struct udxDatFwdCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   Status status;
   Reason reason;
}UdxDatFwdCfmInfo;


typedef struct udxDatResumeCfmInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   Status status;
   Reason reason;
} UdxDatResumeCfmInfo;




typedef struct udxDatForwardInfo
{
   CmLteRnti ueId;
   CmLteCellId cellId;
   U32 transId;
   Bool ulFwding;
} UdxDatForwardInfo;
typedef S16 (*UdxBndReq) (Pst *pst, SuId suId, SpId spId);
typedef S16 (*UdxBndCfm) (Pst *pst, SuId suId, U8 status);
typedef S16 (*UdxUbndReq) (Pst *pst, SpId spId, Reason reason);
typedef S16 (*UdxCfgReq) (Pst *pst, SpId spId, UdxCfgReqInfo *cfgReq);
typedef S16 (*UdxCfgCfm) (Pst *pst, SuId suId, UdxCfgCfmInfo *cfgCfm);
typedef S16 (*UdxReEstReq) (Pst *pst, SpId spId, UdxReEstReqInfo *reEstReq);
typedef S16 (*UdxReEstCfm) (Pst *pst, SuId suId, UdxReEstCfmInfo *reEstCfm);
typedef S16 (*UdxSecCfgReq) (Pst *pst, SpId spId, UdxSecCfgReqInfo *secCfgReq);
typedef S16 (*UdxSecCfgCfm) (Pst *pst, SuId suId, UdxSecCfgCfmInfo *secCfgCfm);
typedef S16 (*UdxUeIdChgReq) (Pst *pst, SpId spId, U32 transId, UdxUeInfo *oldUeInfo, UdxUeInfo *newUeInfo)

                                                          ;
typedef S16 (*UdxUeIdChgCfm) (Pst *pst, SuId suId, U32 transId, UdxUeInfo *ueInfo, CmStatus status)
                                                                         ;
typedef S16 (*UdxCountReq) (Pst *pst, SpId spId, UdxCountReqInfo *countReq);
typedef S16 (*UdxCountCfm) (Pst *pst, SuId suId, UdxCountCfmInfo *countCfm);
typedef S16 (*UdxSduStaReq) (Pst *pst, SpId spId, UdxSduStaReqInfo *staReq);
typedef S16 (*UdxSduStaCfm) (Pst *pst, SuId suId, UdxSduStaCfmInfo *staCfm);
typedef S16 (*UdxDatResumeCfm) (Pst *pst, SuId suId, UdxDatResumeCfmInfo *datResumeCfm);
typedef S16 (*UdxDatForwardCfm) (Pst *pst, SuId suId, UdxDatFwdCfmInfo *datFwdCfm);
typedef S16 (*UdxUlStaRep) (Pst *pst, SpId spId, UdxUlStaRepInfo *staRep);
typedef S16 (*UdxDlStaRep) (Pst *pst, SpId spId, UdxDlStaRepInfo *staRep);
typedef S16 (*UdxUlFdbkPkt) (Pst *pst, SpId spId, UdxUlFdbkPktInfo *fdbkPktInfo);
typedef S16 (*UdxDlFdbkPkt) (Pst *pst, SpId spId, UdxDlFdbkPktInfo *fdbkPktInfo);
typedef S16 (*UdxDatResumeReq) (Pst *pst, UdxDatResumeInfo *udxDatResumeInfo);
typedef S16 (*UdxDatForwardReq) (Pst *pst, UdxDatForwardInfo *udxDatForwardInfo);
extern S16 PjUlUdxBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 PjDlUdxBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 PjDlUdxBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 PjUlUdxBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 PjUlUdxUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 PjDlUdxUbndReq (Pst *pst, SpId spId, Reason reason);
extern S16 PjUlUdxCfgReq (Pst *pst, SpId spId, UdxCfgReqInfo *cfgReq);
extern S16 PjDlUdxCfgReq (Pst *pst, SpId spId, UdxCfgReqInfo *cfgReq);
extern S16 PjDlUdxUlStaRep (Pst *pst, SpId spId, UdxUlStaRepInfo *staRep);
extern S16 PjDlUdxDlStaRep (Pst *pst, SpId spId, UdxDlStaRepInfo *staRep);
extern S16 PjUlUdxUlFdbkPktInfo (Pst *pst, SpId spId, UdxUlFdbkPktInfo *fdbkPktInfo);
extern S16 PjUlUdxDlFdbkPktInfo (Pst *pst, SpId spId, UdxDlFdbkPktInfo *fdbkPktInfo);
extern S16 PjUlUdxCfgCfm (Pst *pst, SuId suId, UdxCfgCfmInfo *cfgCfm);
extern S16 PjDlUdxCfgCfm (Pst *pst, SuId suId, UdxCfgCfmInfo *cfgCfm);
extern S16 PjUlUdxReEstReq (Pst *pst, SpId spId, UdxReEstReqInfo *reEstReq);
extern S16 PjDlUdxReEstReq (Pst *pst, SpId spId, UdxReEstReqInfo *reEstReq);
extern S16 PjUlUdxReEstCfm (Pst *pst, SuId suId, UdxReEstCfmInfo *reEstCfm);
extern S16 PjDlUdxReEstCfm (Pst *pst, SuId suId, UdxReEstCfmInfo *reEstCfm);
extern S16 PjUlUdxSecCfgReq (Pst *pst, SpId spId, UdxSecCfgReqInfo *secCfgReq)
                                      ;
extern S16 PjDlUdxSecCfgReq (Pst *pst, SpId spId, UdxSecCfgReqInfo *secCfgReq)
                                      ;
extern S16 PjUlUdxSecCfgCfm (Pst *pst, SuId suId, UdxSecCfgCfmInfo *secCfgCfm)
                                      ;
extern S16 PjDlUdxSecCfgCfm (Pst *pst, SuId suId, UdxSecCfgCfmInfo *secCfgCfm)
                                      ;
extern S16 PjUlUdxUeIdChgReq (Pst *pst, SpId spId, U32 transId, UdxUeInfo *oldUeInfo, UdxUeInfo *newUeInfo)
                                                                               ;
extern S16 PjDlUdxUeIdChgReq (Pst *pst, SpId spId, U32 transId, UdxUeInfo *oldUeInfo, UdxUeInfo *newUeInfo)
                                                                               ;
extern S16 PjUlUdxUeIdChgCfm (Pst *pst, SuId suId, U32 transId, UdxUeInfo *ueInfo, CmStatus status)
                                                                      ;
extern S16 PjDlUdxUeIdChgCfm (Pst *pst, SuId suId, U32 transId, UdxUeInfo *ueInfo, CmStatus status)
                                                                      ;
extern S16 PjUlUdxCountReq (Pst *pst, SpId spId, UdxCountReqInfo *countReq);
extern S16 PjDlUdxCountReq (Pst *pst, SpId spId, UdxCountReqInfo *countReq);
extern S16 PjUlUdxCountCfm (Pst *pst, SuId suId, UdxCountCfmInfo *countCfm);
extern S16 PjDlUdxCountCfm (Pst *pst, SuId suId, UdxCountCfmInfo *countCfm);
extern S16 PjUlUdxSduStaReq (Pst *pst, SpId spId, UdxSduStaReqInfo *staReq);
extern S16 PjDlUdxSduStaReq (Pst *pst, SpId spId, UdxSduStaReqInfo *staReq);
extern S16 PjDlUdxSduStaCfm (Pst *pst, SuId suId, UdxSduStaCfmInfo *staCfm);
extern S16 PjUlUdxSduStaCfm (Pst *pst, SuId suId, UdxSduStaCfmInfo *staCfm);


extern S16 PjDlUdxDatResumeCfm (Pst *pst, SuId suId, UdxDatResumeCfmInfo *datResumeCfm)
                        ;
extern S16 PjUlUdxDatResumeCfm (Pst *pst, SuId suId, UdxDatResumeCfmInfo *datResumeCfm)
                        ;
extern S16 PjDlUdxDatFwdCfm (Pst *pst, SuId suId, UdxDatFwdCfmInfo *datFwdCfm)
                     ;
extern S16 PjUlUdxDatForwardCfm (Pst *pst, SuId suId, UdxDatFwdCfmInfo *datFwdCfm)
                     ;

extern S16 PjDlUdxUlFdbkPktInfo (Pst *pst, SpId spId, UdxUlFdbkPktInfo *fdbkPktInfo);
extern S16 PjDlUdxDlFdbkPktInfo (Pst * pst, SpId spId, UdxDlFdbkPktInfo * fdbkPktInfo);
extern S16 PjDlUdxDatResumeReq (Pst *pst, UdxDatResumeInfo *udxDatResumeInfo);
extern S16 PjUlUdxDatResumeReq (Pst *pst, UdxDatResumeInfo *udxDatResumeInfo);
extern S16 PjDlUdxDatForwardReq (Pst *pst, UdxDatForwardInfo *udxDatForwardInfo);
extern S16 PjUlUdxDatForwardReq (Pst *pst, UdxDatForwardInfo *udxDatForwardInfo);
extern S16 PjUlUdxDatResumeReqFB (Pst *pst, UdxDatResumeInfo *udxDatResumeInfo);
extern S16 PjUlUdxDatForwardReqFB (Pst *pst, UdxDatForwardInfo *udxDatForwardInfo);
typedef struct pjUlUeCb PjUlUeCb;
typedef struct pjUlRbCb PjUlRbCb;
typedef struct pjUlHoCfmInfo
{
   U8 rbId;
   Bool pres;
   U8 dir;
   U8 res1;
   U8 numBits;
   U8 res2[3];
   U8 *ulBitMap;
   U32 count;
}PjUlHoCfmInfo;





typedef struct pjUlHoInfo
{
   U32 transId;
   UdxSduStaCfmInfo *staCfm;
   PjUlHoCfmInfo *hoCfmInfo;
}PjUlHoInfo;
typedef struct pjRxEnt
{
   CmLList lstEnt;
   CmLList datPktEnt;
   U8 state;
   Bool discFlag;

   Bool dupEntry;

   Bool res;
   U32 count;
   Buffer *mBuf;



   Bool isOutSeq;
}PjRxEnt;



typedef struct pjUlCb
{

   PjSn nxtRxSn;
   U32 rxHfn;

   Bool staRepReqd;

   Bool discReqd;


   Bool transCmp;

   U8 state;
   PjBuf recBuf;
   U32 nxtSubCnt;

   U32 nxtSubDeCmp;

   U32 lastSubCnt;

   U32 obdPdu;
   U32 firstReEstCnt;





   CmLListCp ulPktLst;

   U32 fmsCount;




}PjUlCb;





struct pjUlRbCb
{
   CmLteRbId rbId;
   U8 rbType;
   CmLteRlcMode mode;
   U8 dir;
   U8 snLen;
   U8 state;
   PjSn firstSn;

   PjRohc rohc;
   PjCmpCxt cmpCxt;
   U32 cmpCxtId;







   PjUlCb ulCb;
   PjUlUeCb *ueCb;
   PjSec secInfo;
};




struct pjUlUeCb
{
   CmHashListEnt ueHlEnt;
   Inst inst;
   PjUeKey key;
   U8 numSrbs;
   U8 numDrbs;
   PjUlRbCb *srbCb[3];
   PjUlRbCb *drbCb[32];
   PjSec secInfo;
   PjUlHoInfo *hoInfo;
   PjLibInfo libInfo;





   Bool isUlDatFwdReqd;
};

typedef struct pjUlPkt
{
   CmLList lnk;
   PjSn sn;
   Buffer *pdu;
   U8 type;
} PjUlPkt;


extern S16 pjCfgAddUlRb (PjCb *gCb,CmLteRnti ueId,CmLteCellId cellId,U8 isHo, CpjCfgEnt *entCfg,PjUlUeCb **ueCb, CpjCfmEnt *entCfm )
                                                                      ;

extern S16 pjCfgReCfgUlRb (PjCb *gCb,PjUlUeCb *ueCb, CpjCfgEnt *entCfg, CpjCfmEnt *entCfm)
                                                                ;

extern S16 pjCfgDelUlRb (PjCb *gCb,PjUlUeCb *ueCb, CpjCfgEnt *entCfg,CpjCfmEnt *entCfm)
                                                             ;

extern S16 pjCfgReEstUlRb ( PjCb *gCb, PjUlUeCb *ueCb, CpjCfgEnt *entCfg, CpjCfmEnt *entCfm, UdxCfmEnt *entDlCfgCfm )





  ;

extern S16 pjCfgDelUlUe ( PjCb *gCb, PjUlUeCb *ueCb, CpjCfgEnt *entCfg, CpjCfmEnt *entCfm )




  ;

extern S16 pjCfgPrcSecUlCfg ( PjCb *gCb, CpjSecCfgReqInfo *secCfg, CpjSecCfgCfmInfo *cfgCfm )



  ;

extern S16 pjCfgUlUeIdChng ( PjCb *gCb, CpjUeInfo *ueInfo, CpjUeInfo *newUeInfo, CmStatus *status )




  ;

extern S16 pjCfgPrcUlCount ( PjCb *gCb, CpjCountReqInfo *countReq, CpjCountCfmInfo *countCfm, UdxCountCfmInfo *cntCfm )




  ;

extern S16 pjCfgDelPjUlRbCb ( PjCb *gCb, PjUlUeCb *ueCb, PjUlRbCb *rbCb )



  ;

extern S16 pjUtlUlCipherClose ( PjCb *gCb, Void *cpCxtId )


  ;

extern S16 pjUtlUlIntClose ( PjCb *gCb, Void *intCxtId )


  ;

extern S16 pjCfgUlReEstReq ( PjCb *gCb, CpjReEstReqInfo *reEstReq, CpjReEstCfmInfo *reEstCfm )



  ;

extern S16 pjDbmInsRxEnt ( PjCb *gCb, PjBuf *buf, PjRxEnt *rxEnt, Bool dupFlag )




  ;
extern S16 pjDbmBufInit ( PjCb *gCb, PjBuf *buf, U8 numBins )



  ;
extern PjRxEnt* pjDbmGetRxEnt ( PjCb *gCb, PjBuf *buf, U32 count )



  ;
extern PjRxEnt* pjDbmGetRxEntSn ( PjCb *gCb, PjBuf *buf, U16 sn )



  ;
extern S16 pjDbmDelRxEnt ( PjCb *gCb, PjBuf *buf, U32 count )



  ;
extern S16 pjDbmRxDelAll ( PjCb *gCb, PjBuf *buf )


  ;
extern S16 pjDbmRxDeInit ( PjCb *gCb, PjBuf *buf )


  ;

extern S16 pjDbmUlDeInit ( PjCb *gCb )

  ;

extern S16 pjDbmFetchUlUeCb ( PjCb *gCb, CmLteRnti ueId, CmLteCellId cellId, PjUlUeCb **ueCb )




  ;

extern S16 pjDbmCreateUlUeCb ( PjCb *gCb, CmLteRnti ueId, CmLteCellId cellId, PjUlUeCb **ueCb )




  ;
extern PjUlRbCb* pjDbmCreateUlRbCb ( PjCb *gCb, U8 rbId, U8 rbType, PjUlUeCb *ueCb, U8 rb )





  ;

extern S16 pjDbmFetchUlRbCb ( PjCb *gCb, CmLteRlcId rlcId, PjUlRbCb **rbCb )



  ;

extern S16 pjDbmDelUlRbCb ( PjCb *gCb, U8 rbId, U8 rbType, PjUlRbCb **rbCb, U8 rb, PjUlUeCb *ueCb )






  ;

extern S16 pjDbmDelUlUeCb ( PjCb *gCb, PjUlUeCb *ueCb, Bool abortFlag )



  ;

extern S16 PjDbmDelAllUlUe (PjCb *gCb);
extern S16 pjDbmDelAllUlRb ( PjCb *gCb, PjUlRbCb **rbCbLst, U8 numRbCb )



  ;
extern S16 pjDbmDelAllUlUe ( PjCb *gCb )

  ;

extern S16 pjDbmUlInit ( PjCb *gCb);
extern S16 pjDbmUlShutdown (PjCb *gCb);
extern S16 pjDbmAddUlTransIdLst (PjCb *gCb,PjCfgInfo *cfg);
extern S16 pjDbmFindUlTransIdLst (PjCb *gCb,U32 transId, PjCfgInfo **cfg)
                                                         ;
extern S16 pjDbmDelUlTransIdLst (PjCb *gCb,PjCfgInfo **cfg);
extern S16 pjDbmDelAllUlTransIdLst (PjCb *gCb);

extern S16 pjUtlUlUpdUpSecKeys ( PjCb *gCb, PjUlUeCb *ueCb);
extern S16 pjUtlUlUpdCpSecKeys ( PjCb *gCb, PjUlUeCb *ueCb);
extern S16 pjUtlUlHdlRbReEstComplete (PjCb *gCb, PjUlRbCb *pjRbCb);


extern S16 pjUtlUlCmpReset ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;


extern S16 pjUtlUlCmpInit ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;
extern S16 pjUtlUlIntInit ( PjCb *gCb, PjUlUeCb *ueCb )


  ;
extern S16 pjUtlUlCpInit ( PjCb *gCb, PjUlUeCb *ueCb )


  ;
extern S16 pjUtlUlUpInit ( PjCb *gCb, PjUlUeCb *ueCb )


  ;

extern S16 pjUtlUlCmpReq ( PjCb *gCb, PjUlRbCb *pjRbCb, Buffer *mBuf, Buffer **opSdu, U32 count )





  ;
extern S16 pjUtlUlIntProtReq ( PjCb *gCb, PjUlRbCb *pjRbCb, PjSecInp secInp , Buffer *mBuf, U32 *macI )





  ;
extern S16 pjUtlDeCmpReq ( PjCb *gCb, PjUlRbCb *pjRbCb, U32 count, Buffer *mBuf, Buffer **opSdu )





  ;
extern S16 pjUtlIntVerReq ( PjCb *gCb, PjUlRbCb *pjRbCb, PjSecInp secInp , Buffer *mBuf, U32 macI, Status *status )






  ;
extern S16 pjUtlDecipherReq ( PjCb *gCb, PjUlRbCb *pjRbCb, U32 count, Buffer *mBuf, Buffer **opSdu )





  ;
extern S16 pjUtlSndFeedback ( PjCb *gCb, PjUlRbCb *pjRbCb, Buffer *feedback )



  ;
extern S16 pjUtlUlReEstSrb1 ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;
extern S16 pjUtlUlReEstStart ( PjCb *gCb, PjUlUeCb *ueCb, CpjCfgReqInfo *cfgReq )



  ;
extern S16 pjUtlUlReEstHOStart ( PjCb *gCb, PjUlUeCb *ueCb, U32 transId, U32 *waitForHoTrig )




  ;
extern S16 pjUtlUlReEstReconfig ( PjCb *gCb, PjUlUeCb *ueCb )


  ;
extern S16 pjUtlUlReEstUl ( PjCb *gCb, PjUlUeCb *ueCb )


  ;
extern S16 pjUtlUlSndReEstCfgCfm ( PjCb *gCb, PjUlUeCb *ueCb )


  ;
extern S16 pjUtlUlSndSduStaCfm ( PjCb *gCb, PjUlUeCb *ueCb )


  ;
extern S16 pjUtlUlShutdown ( PjCb *gCb )

  ;
extern Void pjUtlUlFreeRb ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;

extern S16 pjUtlUlSndDatFwdInd ( PjCb *gCb, PjUlRbCb *pjRbCb, PjuDatFwdIndInfo *datFwdInd )



  ;
extern S16 pjUtlUlSndUlStaRep ( PjCb *gCb, PjUlRbCb *pjRbCb, Buffer *sta )



  ;

extern S16 pjUtlUlHdlObdInitCfm ( PjCb *gCb, PjUlUeCb *ueCb, U16 txIdx, U8 cfmType, U8 maskVal )





  ;
extern S16 pjUtlUlHdlInitObdTmrExp ( PjCb *gCb, PjUlUeCb *ueCb )


  ;

extern S16 pjCfgPrcUlSduSta ( PjCb *gCb, CpjSduStaReqInfo *staReq, UdxSduStaCfmInfo *staCfm )



  ;

extern S16 pjUtlUlSaveCfmInfo ( PjCb *gCb, PjUlUeCb *ueCb, U8 cfmType, Bool startTmr, U8 entity, U32 cfmPtr, U32 cfgPtr )







  ;


extern S16 pjUlmHdlSrbPkt ( PjCb *gCb, PjUlRbCb *pjRbCb, Buffer *pdu )



  ;
extern S16 pjUlmHndlDlStaRep ( PjCb *gCb, PjUlRbCb *pjRbCb, PjSn fms, Buffer *staPdu )




  ;

extern U32 pjMsCheckSpaccQueue ( Bool isUl )

  ;

extern S16 pjUlmHdlDrbPkt ( PjCb *gCb, PjUlRbCb *pjRbCb, Buffer *pdu, Bool isOutOfSeq )




  ;
extern S16 pjUlmProcessSrb ( PjCb *gCb, PjUlRbCb *pjRbCb, PjSn sn, Buffer *pdu )




  ;
extern S16 pjUlmProcessDrbUm ( PjCb *gCb, PjUlRbCb *pjRbCb, PjSn sn, Buffer *pdu )




  ;
extern S16 pjUlmProcessDrbAm ( PjCb *gCb, PjUlRbCb *pjRbCb, PjSn sn, Buffer *pdu, Bool isOutOfSeq )





  ;
extern S16 pjUlmHdlDecipher ( PjCb *gCb, PjUlRbCb *pjRbCb, PjRxEnt *rxEnt )



  ;
extern S16 pjUlmHdlIntVer ( PjCb *gCb, PjUlRbCb *pjRbCb, PjRxEnt *rxEnt )



  ;
extern S16 pjUlmHdlDeCmp ( PjCb *gCb, PjUlRbCb *pjRbCb, PjRxEnt *rxEnt )



  ;
extern S16 pjUlmDeliverSrb ( PjCb *gCb, PjUlRbCb *pjRbCb, PjRxEnt *rxEnt )



  ;
extern S16 pjUlmDeliverDrbUm ( PjCb *gCb, PjUlRbCb *pjRbCb, PjRxEnt *rxEnt )



  ;
extern S16 pjUlmDeliverDrbAm ( PjCb *gCb, PjUlRbCb *pjRbCb, PjRxEnt *rxEnt )



  ;
extern S16 pjUlmReEstSrb ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;
extern S16 pjUlmReEstDrbAm ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;
extern S16 pjUlmBldStaRep ( PjCb *gCb, PjUlRbCb *pjRbCb, PjSn fms, U8 *staRep, U16 bMapLen )





  ;
extern S16 pjUlmHdlDatFwdReq ( PjCb *gCb, PjUlRbCb *pjRbCb, PjuDatFwdReqInfo *datFwdReq )



  ;
extern S16 pjUlmSubmitForDecmp ( PjCb *gCb, PjUlRbCb *pjRbCb, PjRxEnt *rxEnt )



  ;

extern Void pjUlmHdlObdTmrExpiry ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;

extern Void pjUlmHdlErrUpdates ( PjCb *gCb, PjUlRbCb *pjRbCb, U32 errCnt )



  ;

extern Void pjLimDatInd ( PjCb *gCb, PjUlRbCb *pjRbCb, Buffer *mBuf, Bool isOutOfSeq )




  ;

extern Void pjLimReEstCmpInd ( PjUlRbCb *pjRbCb )

  ;
extern S16 pjDbmFetchPjUlRbCb ( PjUlUeCb *ueCb, U8 rbId, U8 rbType, PjUlRbCb **pjRbCb )




  ;

extern S16 pjUtlUlSndUlRohcFdbk ( PjCb *gCb, PjUlRbCb *pjRbCb, Buffer *fbPkt )



  ;

extern S16 pjUtlUlResetBuffrdPkts ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;

extern S16 pjUtlReEstProcUlRb ( PjCb *tPjCb, PjUlUeCb *ueCb, CpjCfgReqInfo *cfg )



  ;

extern S16 pjUtlCheckOnlySrbPresent ( PjCb *tPjCb, CmLtePdcpId pdcpId, U32 *waitForReEstTrig )



  ;

extern Void pjUlmReEstCmpInd ( PjCb *tPjCb, PjUlRbCb *tRbCb )


  ;

extern S16 PjUlUdxDlStaRep ( Pst *pst, SpId spId, UdxDlStaRepInfo *staRep )



  ;

extern S16 PjUlUdxUlStaRep ( Pst *pst, SpId spId, UdxUlStaRepInfo *staRep )



  ;







extern S16 pjUtlStartUlReEst ( PjCb *gCb, CpjReEstReqInfo *reEstReq, CpjReEstCfmInfo *reEstCfm )



  ;

extern S16 pjUtlUlPrcsDatResume ( PjCb *gCb, CpjDatResumeReqInfo *datResReq )


  ;

extern S16 pjUlmStartDataFrwdPerRb ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;

extern Void pjUlmProcessUlPktQ ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;

extern S16 pjUtlUlGetRbCb ( PjCb *gCb, CmLtePdcpId *pdcpId, PjUlRbCb **rbCb, U8 *retCause )




  ;

extern Void pjUtlEmptyUlPktList ( PjCb *gCb, PjUlRbCb *pjRbCb )


  ;

extern S16 pjUtlUlReEstHO ( PjCb *gCb, PjUlUeCb *ueCb )


  ;

extern S16 pjDbmFetchUlUeCb ( PjCb *gCb, CmLteRnti ueId, CmLteCellId cellId, PjUlUeCb **ueCb )




  ;
extern S16 pjUlmHndlDatFwdReq ( PjCb *gCb, PjUlRbCb *pjRbCb, PjuDatFwdReqInfo *datFwdReq )



  ;
extern Void dumpPDCPUlRbInformation ( PjUlRbCb* ulRbCb, U16 ueId )


  ;

extern void DumpPDCPUlDebugInformation ( Void )

  ;

extern Void pjDeInitDeCipherQ(Void);
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
typedef struct pjDlUeCb PjDlUeCb;
typedef struct pjDlRbCb PjDlRbCb;
typedef struct pjDlHoCfmInfo
{
   U8 rbId;
   Bool pres;
   U8 dir;
   U8 res1;
   U32 count;
}PjDlHoCfmInfo;





typedef struct pjDlHoInfo
{
   U32 transId;
   PjDlHoCfmInfo *hoCfmInfo;
}PjDlHoInfo;



typedef struct pjTxEnt
{
   CmLList lstEnt;
   CmLList datCfmEnt;
   CmLList sduSubmitEnt;
   CmLList reEstPktEnt;
   U8 state;
   U8 res;
   PjSn sn;
   U32 txHfn;

   U32 count;
   Data *ciphDBuf;
   Buffer *pdu;
   Buffer *sdu;



   U32 sduId;
   PjDlRbCb *rbCb;
   MsgLen bufLen;



}PjTxEnt;



typedef struct pjDlCb
{
   S16 discTmrInt;
   PjSn nxtTxSn;

   Bool cfmReqd;


   U8 res[3];
   PjBuf txBuf;
   U32 txHfn;

   U32 count;

   U32 nxtToSub;

   U32 cfmExp;

   CmTimer discTmr;




   CmLListCp dlPktQ;

   Buffer *staRep;
}PjDlCb;





struct pjDlRbCb
{
   CmLteRbId rbId;
   U8 rbType;
   CmLteRlcMode mode;
   U8 dir;
   U8 snLen;
   U8 state;
   PjSn firstSn;

   PjRohc rohc;
   PjCmpCxt cmpCxt;
   U32 cmpCxtId;
   Bool firstDlMsg;

   Bool dropOnlyOne;

   U32 pktAdmitCnt;

   U32 pktCnt;
   PjDlCb dlCb;
   PjDlUeCb *ueCb;
   U32 maxTxSn;
   PjUeKey key;
   CmLListCp dlPktLst;
   U32 rbOverloadCnt;
};


typedef struct pjDatCfm
{
   CmLteRlcId rlcId;
   U32 numSdu;
   U32 sduId[1024];
}PjDatCfm;




struct pjDlUeCb
{
   CmHashListEnt ueHlEnt;
   Inst inst;
   PjUeKey key;
   U8 numSrbs;
   U8 numDrbs;
   PjDlRbCb *srbCb[3];
   PjDlRbCb *drbCb[32];
   PjSec secInfo;
   PjDlHoInfo *hoInfo;
   PjLibInfo libInfo;

   U32 waitForReEstTrig;






   TSL2UeStatsCb *tenbStats;


   U16 ueIndex;

};

typedef struct pjDlPkt
{
   CmLList lnk;
   U8 type;
   U32 sduId;
   PjSn sn;
   Buffer *pdu;



} PjDlPkt;


extern S16 pjCfgAddDlRb (PjCb *gCb,CmLteRnti ueId,CmLteCellId cellId, U8 isHo, UdxCfgEnt *entCfg, PjDlUeCb **ueCb,UdxCfmEnt *entCfm )
                                                                              ;

extern S16 pjCfgReCfgDlRb (PjCb *gCb,PjDlUeCb *ueCb, UdxCfgEnt *entCfg, UdxCfmEnt *entCfm)
                                                                ;

extern S16 pjCfgDelDlRb (PjCb *gCb,PjDlUeCb *ueCb, UdxCfgEnt *entCfg,UdxCfmEnt *entCfm)
                                                             ;

extern S16 pjCfgReEstDlRb ( PjCb *gCb, PjDlUeCb *ueCb, UdxCfgEnt *entCfg, UdxCfmEnt *entCfm )




  ;

extern S16 pjCfgDelDlUe ( PjCb *gCb, PjDlUeCb *ueCb, UdxCfgEnt *entCfg, UdxCfmEnt *entCfm )




  ;

extern S16 pjCfgPrcSecDlCfg ( PjCb *gCb, UdxSecCfgReqInfo *secCfg, UdxSecCfgCfmInfo *cfgCfm )



  ;

extern S16 pjCfgDlUeIdChng ( PjCb *gCb, UdxUeInfo *ueInfo, UdxUeInfo *newUeInfo, CmStatus *status )




  ;

extern S16 pjCfgPrcDlCount ( PjCb *gCb, UdxCountReqInfo *countReq, UdxCountCfmInfo *countCfm )



  ;

extern S16 pjCfgDelPjDlRbCb ( PjCb *gCb, PjDlUeCb *ueCb, PjDlRbCb *rbCb )



  ;


extern S16 pjCfgDlReEstReq ( PjCb *gCb, UdxReEstReqInfo *reEstReq, UdxReEstCfmInfo *reEstCfm )



  ;

extern S16 pjDbmInsTxEnt ( PjCb *gCb, PjBuf *buf, PjTxEnt *txEnt )



  ;
extern S16 pjDbmDlBufInit ( PjCb *gCb, PjBuf *buf, U8 numBins )



  ;

extern PjTxEnt* pjDbmGetTxEnt ( PjCb *gCb, PjBuf *buf, U32 count )



  ;
extern PjTxEnt* pjDbmGetTxEntSn ( PjCb *gCb, PjBuf *buf, U16 sn )



  ;
extern S16 pjDbmDelTxEnt ( PjCb *gCb, PjBuf *buf, U32 count )



  ;
extern S16 pjDbmTxDelAll ( PjCb *gCb, PjBuf *buf )


  ;
extern S16 pjDbmTxDeInit ( PjCb *gCb, PjBuf *buf )


  ;

extern S16 pjDbmFetchDlUeCb ( PjCb *gCb, CmLteRnti ueId, CmLteCellId cellId, PjDlUeCb **ueCb )




  ;

extern S16 pjDbmCreateDlUeCb ( PjCb *gCb, CmLteRnti ueId, CmLteCellId cellId, PjDlUeCb **ueCb )




  ;
extern PjDlRbCb* pjDbmCreateDlRbCb ( PjCb *gCb, U8 rbId, U8 rbType, PjDlUeCb *ueCb, U8 rb )





  ;
extern S16 pjDbmDelDlRbCb ( PjCb *gCb, U8 rbId, U8 rbType, PjDlRbCb **rbCb, U8 rb, PjDlUeCb *ueCb )






  ;

extern S16 pjDbmDelDlUeCb ( PjCb *gCb, PjDlUeCb *ueCb, Bool abortFlag )



  ;

extern S16 pjDbmFetchDlRbCb ( PjCb *gCb, CmLteRlcId rlcId, PjDlRbCb **rbCb )



  ;

extern S16 PjDbmDelAllDlUe (PjCb *gCb);
extern S16 pjDbmDelAllDlRb ( PjCb *gCb, PjDlRbCb **rbCbLst, U8 numRbCb )



  ;

extern S16 pjDbmDlInit ( PjCb *gCb);
extern S16 pjDbmDlDeInit ( PjCb *gCb);
extern S16 pjDbmDlShutdown (PjCb *gCb);

extern S16 pjDlUtlCmpReset ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;


extern S16 pjUtlDlCmpInit ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;
extern S16 pjUtlDlIntInit ( PjCb *gCb, PjDlUeCb *ueCb )


  ;
extern S16 pjUtlDlCpInit ( PjCb *gCb, PjDlUeCb *ueCb )


  ;
extern S16 pjUtlDlUpInit ( PjCb *gCb, PjDlUeCb *ueCb )


  ;
extern S16 pjUtlDlCmpReset ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;
extern S16 pjUtlCmpReq ( PjCb *gCb, PjDlRbCb *pjRbCb, Buffer *mBuf, Buffer **opSdu, U32 count )





  ;
extern S16 pjUtlIntProtReq ( PjCb *gCb, PjDlRbCb *pjRbCb, PjSecInp secInp , Buffer **mBuf )




  ;
extern S16 pjUtlCipherReq ( PjCb *gCb, PjDlRbCb *pjRbCb, U32 count, Buffer *mBuf, Buffer **opSdu )





  ;
extern S16 pjUtlDlCmpClose ( U32 cmpCxtId )

  ;
extern S16 pjUtlDlIntClose ( PjCb *gCb, Void *intCxtId )


  ;

extern S16 pjUtlDlCipherClose ( PjCb *gCb, Void *cpCxtId )


  ;
extern S16 pjUtlDlReEstSrb1 ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;
extern S16 pjUtlDlReEstStart ( PjCb *gCb, PjDlUeCb *ueCb, UdxCfgReqInfo *cfgReq )



  ;
extern S16 pjUtlDlReEstHOStart ( PjCb *gCb, PjDlUeCb *ueCb, U32 transId, U32 waitForHoTrig )




  ;
extern S16 pjUtlDlReEstReconfig ( PjCb *gCb, PjDlUeCb *ueCb )


  ;
extern S16 pjUtlDlReEstDl ( PjCb *gCb, PjDlUeCb *ueCb )


  ;
extern S16 pjUtlDlSndReEstCfgCfm ( PjCb *gCb, PjDlUeCb *ueCb )


  ;
extern S16 pjUtlDlSndSduStaCfm ( PjCb *gCb, PjDlUeCb *ueCb )


  ;
extern S16 pjUtlDlShutdown ( PjCb *gCb )

  ;
extern Void pjUtlDlFreeRb ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;

extern S16 pjUtlDlSndDatFwdInd ( PjCb *gCb, PjDlRbCb *pjRbCb, PjuDatFwdIndInfo *datFwdInd )



  ;

extern S16 pjUtlDlHdlObdInitCfm ( PjCb *gCb, PjDlUeCb *ueCb, U16 txIdx, U8 cfmType, U8 maskVal )





  ;
extern S16 pjUtlDlHdlInitObdTmrExp ( PjCb *gCb, PjDlUeCb *ueCb )


  ;

extern S16 pjCfgPrcDlSduSta ( PjCb *gCb, UdxSduStaReqInfo *staReq )


  ;

extern S16 pjUtlDlSaveCfmInfo ( PjCb *gCb, PjDlUeCb *ueCb, U8 cfmType, Bool startTmr, U8 entity, U32 cfmPtr, U32 cfgPtr )







  ;


extern S16 pjDlmProcessSdus ( PjCb *gCb, PjDlRbCb *pjRbCb, Buffer *sdu, U32 sduId, PjSn sn, U32 txHfn )






  ;

extern S16 pjDlmProcDrb ( PjCb *gCb, PjDlRbCb *pjRbCb, PjTxEnt *txEnt )



  ;
extern S16 pjDlmProcSrb ( PjCb *gCb, PjDlRbCb *pjRbCb, PjTxEnt *txEnt )



  ;
extern Void pjDlmReEstSrb ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;

extern S16 pjDlmReEstDrbUm ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;

extern S16 pjDlmReEstDrbAm ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;
extern S16 pjDlmProcessCfm ( PjCb *gCb, PjDlRbCb *pjRbCb, PjDatCfm *pjDatCfm, U8 cfmType )




  ;
extern S16 pjDlmHndlStaRep ( PjCb *gCb, PjDlRbCb *pjRbCb, PjSn fms, Buffer *staPdu )




  ;
extern S16 pjDlmReEstHoDrbAm ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;
extern S16 pjDlmHdlDatFwdReq ( PjCb *gCb, PjDlRbCb *pjRbCb, PjuDatFwdReqInfo *datFwdReq )



  ;
extern S16 pjDlmDeliverPdu ( PjCb *gCb, PjDlRbCb *pjRbCb, PjTxEnt *txEnt )



  ;
extern S16 pjDlmObdTmrExp ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;
extern S16 pjDlmHdlIntProt ( PjCb *gCb, PjDlRbCb *pjRbCb, PjTxEnt *txEnt )



  ;
extern S16 pjDlmHdlCmp ( PjCb *gCb, PjDlRbCb *pjRbCb, PjTxEnt *txEnt )



  ;
extern S16 pjDlmHdlCiph ( PjCb *gCb, PjDlRbCb *pjRbCb, PjTxEnt *txEnt )



  ;
extern S16 pjDlmDiscTmrExp ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;

extern S16 pjDlmSendDatReq ( PjCb *gCb, PjDlRbCb *pjRbCb, U32 sduId, Buffer *mBuf)
                                              ;
extern S16 pjDlmSendDiscSdu ( PjCb *gCb, PjDlRbCb *pjRbCb, U32 sduId);

extern Void pjLimDatCfm ( PjCb *gCb, PjDlRbCb *pjRbCb, PjDatCfm *datCfm )



  ;
extern S16 pjUtlReEstDl ( PjCb *gCb, PjDlUeCb *ueCb )


  ;

extern Void pjLimStaInd ( PjCb *gCb, PjDlRbCb *pjRbCb, PjDatCfm *staInd )



  ;

extern S16 pjDbmFetchPjDlRbCb ( PjDlUeCb *ueCb, U8 rbId, U8 rbType, PjDlRbCb **pjRbCb )




  ;

extern Void pjDlmProcessDlPktQ ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;

extern Void pjDlmEnqueueDlPkt ( PjCb *gCb, PjDlRbCb *pjRbCb, U8 datType, PjuDatFwdReqInfo *datFwd, PjuSduId sduId, Buffer *pdu )






  ;
extern S16 pjDlmStartDataFrwdPerRb ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;

extern S16 pjDlmHndlDatFwdReq ( PjCb *gCb, PjDlRbCb *pjRbCb, PjuDatFwdReqInfo *datFwdReq )



  ;

extern S16 pjUtlDlUpdUpSecKeys ( PjCb *gCb, PjDlUeCb *ueCb )


  ;

extern S16 pjUtlDlUpdCpSecKeys ( PjCb *gCb, PjDlUeCb *ueCb )


  ;

extern S16 pjUtlDlReEstHO ( PjCb *gCb, PjDlUeCb *ueCb )


  ;

extern Void pjUtlEmptyDlPktList ( PjCb *gCb, PjDlRbCb *pjRbCb)

                  ;

extern Void pjDlmRbDataResume ( PjCb *gCb, PjDlRbCb *pjRbCb )


  ;

extern S16 pjDlmHdlNullCiph ( PjCb *gCb, PjDlRbCb *pjRbCb, PjTxEnt *txEnt )



  ;
void DumpPDCPDlDebugInformation(void);
void dumpPDCPDlRbInformation(PjDlRbCb* dlRbCb, U16 ueId);
void ResetPDCPStats(void);
void PrintPDCPStats(void);
extern Void pjDeInitCiphQ(Void);
extern S16 pjLibCmpInitReq ( PjCmpCxt cmpCxt, PjRohc rohc, U32 *cmpCxtId )



  ;
extern S16 pjLibCmpReq ( U32 cmpCxtId, Buffer *mBuf, Buffer **opSdu )



  ;
extern S16 pjLibDecmpReq ( U32 cmpCxtId, Buffer *mBuf, Buffer **opSdu, Buffer **feedback )




  ;
extern S16 pjLibCmpCloseReq ( U32 cmpCxtId )

  ;
extern S16 pjLibCmpResetReq ( U32 cmpCxtId )

  ;
extern S16 pjLibCmpFbReq ( U32 cmpCxtId, Buffer *feedback )


  ;
extern S16 PjLibObdUlInitReq ( PjCb *gCb )

  ;

extern S16 PjLibObdDlInitReq ( PjCb *gCb )

  ;

extern S16 pjLibObdPrcKenbCfg ( PjCb *gCb, CpjAsKeyInfo* kenbInf, CpjAskeyCfmInfo *kdfCfm )



  ;

extern S16 pjLibObdPrcKenbStarCfg ( PjCb *gCb, CpjKenbStarInfo* kenbInf, CpjKenbStarCfmInfo *kdfCfm )



  ;

extern S16 PjLibObdDlCloseReq (Void);

extern S16 PjLibObdUlCloseReq (Void);

extern S16 PjLibObdIntInitReq ( PjSec *secInp )

  ;

extern Void PjUlSpaccTrigger (Void);

extern Void PjDlSpaccTrigger (Void);


extern S16 PjLibObdIntProtReq ( PjLibTrans *libTrans, Buffer **mBuf )


  ;



extern S16 PjLibObdDlInitReq ( PjCb *gCb )

  ;

extern S16 PjLibObdUlInitReq ( PjCb *gCb )

  ;

extern S16 PjLibObdDlCloseReq (Void);

extern S16 PjLibObdUlCloseReq (Void);




extern S16 PjLibObdIntVerReq ( PjLibTrans *libTrans, Buffer * mBuf, U32 macI )



  ;
extern S16 PjLibObdIntCloseReq ( Void *intCxtId )

  ;


extern S16 PjLibObdCpInitReq ( PjSec *secInp )

  ;

extern S16 PjLibObdUpInitReq ( PjSec *secInp )

  ;


extern S16 PjLibObdCipherReq ( PjLibTrans *libTrans, Buffer *mBuf, Buffer **opSdu )



  ;
extern S16 PjLibObdDecipherReq ( PjLibTrans *libTrans, Buffer *mBuf, Buffer **opSdu )



  ;


extern S16 PjLibObdCipherCloseReq ( Void *cpCxtId )

  ;

extern S16 pjLibIntInitReq ( PjSecCxt secCxt, PjIntInfo intInfo, Void **cxtId )



  ;

extern S16 pjLibCpInitReq ( PjSecCxt secCxt, U8 algoType, U8 *cpKey, Void **cxtId )




  ;

extern S16 pjLibUpInitReq ( PjSecCxt secCxt, U8 algoType, U8 *upKey, Void **cxtId )




  ;
extern S16 pjLibDecipherReq ( U32 intCxtId, PjSecInp secInp, Buffer *mBuf, Buffer **opSdu )




  ;
extern S16 pjLibIntVerReq ( U32 intCxtId, PjSecInp secInp, Buffer *mBuf, U32 macI, Status *status )





  ;
extern S16 pjLibPktAdmCtrl ( PjDlRbCb *pjRbCb, Buffer *pkt )


  ;





static S16 pjUtlUlHdlSecInitCfm (PjCb *gCb,PjUlUeCb *ueCb, U16 txIdx,PjAsyncCfm *asyncCfm, CpjSecCfgCfmInfo *secCfgCfm,CpjReEstCfmInfo *reEstCfm)
                                                                                                     ;
static S16 pjUtlUlHdlCmpInitCfm (PjCb *gCb,PjUlUeCb *ueCb, U16 txIdx,PjAsyncCfm *asyncCfm, CpjCfgCfmInfo *cfgCfm)
                                                                     ;
 S16 pjUtlUlCmpInit
(
PjCb *gCb,
PjUlRbCb *pjRbCb
)





{
   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0001, L_DEBUG, pjRbCb->rbId, pjRbCb->rbType, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 131   , "pjUtlUlCmpInit(pjRbCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;
   pjLibCmpInitReq(pjRbCb->cmpCxt, pjRbCb->rohc, &(pjRbCb->cmpCxtId));


   return(0);

}
 S16 pjUtlUlIntInit
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{


   Void *ctxId = 
                ((void *)0)
                    ;




   S32 ret=0;

   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0002, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 195   , "pjUtlUlIntInit(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                     ;
   pjLibIntInitReq(ueCb->secInfo.secCxt, ueCb->secInfo.intInfo,&(ctxId));
   ueCb->secInfo.intCxtId = ctxId;


   return(ret);

}
 S16 pjUtlUlCpInit
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{


   Void *ctxId = 
                ((void *)0)
                    ;




   S16 ret = 0;

   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0003, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 276   , "pjUtlCpInit(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                     ;
   ret = pjLibCpInitReq(ueCb->secInfo.secCxt, (U8)ueCb->secInfo.cipherInfo.algoType,
                  ueCb->secInfo.cipherInfo.cpKey, &ctxId);
   ueCb->secInfo.cpCxtId = ctxId;


   return(ret);

}
 S16 pjUtlUlUpInit
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{


   Void* ctxId = 
                ((void *)0)
                    ;





   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0004, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 356   , "pjUtlUpInit(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                     ;
   pjLibUpInitReq(ueCb->secInfo.secCxt, (U8)ueCb->secInfo.cipherInfo.algoType,
                              ueCb->secInfo.cipherInfo.upKey, &ctxId);
   ueCb->secInfo.upCxtId = ctxId;


   return(0);

}
 S16 pjUtlUlCmpReset
(
PjCb *gCb,
PjUlRbCb *pjRbCb
)





{
   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0005, L_DEBUG, pjRbCb->rbId, pjRbCb->rbType, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 427   , "pjUtlUlCmpReset(pjRbCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;




   pjLibCmpResetReq(pjRbCb->cmpCxtId);


   return(0);

}
 S16 pjUtlUlCipherClose
(
PjCb *gCb,
Void *cpCxtId
)





{
   ;
   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb0006, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",473, "pjUtlUlCipherClose", RLOG_FILE_ID, RLOG_MODULE_NAME); };

   PjLibObdCipherCloseReq(cpCxtId);



   return(0);
}
 S16 pjUtlUlIntClose
(
PjCb *gCb,
Void *intCxtId
)





{
   ;
   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb0007, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",514, "pjUtlUlIntClose", RLOG_FILE_ID, RLOG_MODULE_NAME); };




   PjLibObdIntCloseReq(intCxtId);

   return(0);
}
 S16 pjUtlDecipherReq
(
PjCb *gCb,
PjUlRbCb *pjRbCb,
U32 count,
Buffer *mBuf,
Buffer **opSdu
)
{
   S16 ret = 0;
   PjUlUeCb *ulUeCb;
   PjLibTrans libTrans;
   Void *cxtId = 0L;
   ;

   if (pjRbCb->rbType == 0)
   {
      cxtId = pjRbCb->ueCb->secInfo.cpCxtId;
   }
   else
   {
      cxtId = pjRbCb->ueCb->secInfo.upCxtId;
   }
   ulUeCb = pjRbCb->ueCb;
   libTrans.pdcpInstance = gCb->init.inst;
   libTrans.count = count;
   libTrans.rbId = pjRbCb->rbId - 1;
   libTrans.dir = 0;
   libTrans.rbType = pjRbCb->rbType;
   libTrans.snLen = pjRbCb->snLen;
   libTrans.ciphAlgoType = ulUeCb->secInfo.cipherInfo.algoType;
   libTrans.ueCb = (U32)ulUeCb;
   libTrans.ueId = ulUeCb->key.ueId;
   libTrans.cellId = ulUeCb->key.cellId;
   if(0 == pjRbCb->rbType)
   {
      libTrans.key = ulUeCb->secInfo.cipherInfo.cpKey;
   }
   else
   {
      libTrans.key = ulUeCb->secInfo.cipherInfo.upKey;
   }
   ret = PjLibObdDecipherReq(&libTrans, mBuf, opSdu);

   return(ret);
}
 S16 pjUtlIntVerReq
(
PjCb *gCb,
PjUlRbCb *pjRbCb,
PjSecInp secInp ,
Buffer *mBuf,
U32 macI,
Status *status
)
{
   S16 ret = 0;
   PjUlUeCb *ulUeCb;
   PjLibTrans libTrans;
   Void *cxtId;
   ;

   cxtId = pjRbCb->ueCb->secInfo.intCxtId;
   ulUeCb = pjRbCb->ueCb;
   libTrans.pdcpInstance = gCb->init.inst;
   libTrans.count = secInp.count;
   libTrans.rbId = pjRbCb->rbId - 1;
   libTrans.dir = secInp.dir;
   libTrans.rbType = pjRbCb->rbType;
   libTrans.intAlgoType = ulUeCb->secInfo.intInfo.algoType;
   libTrans.ueCb = (U32)ulUeCb;
   libTrans.ueId = ulUeCb->key.ueId;
   libTrans.cellId = ulUeCb->key.cellId;
   libTrans.key = (U8*)&ulUeCb->secInfo.intInfo.intKey[0];
   { libTrans.fresh[0] = 0; libTrans.fresh[1] = 0; libTrans.fresh[2] = 0; libTrans.fresh[3] = libTrans.rbId; };
   ret = PjLibObdIntVerReq(&libTrans, mBuf, macI);

   return(ret);

}
 S16 pjUtlUlReEstSrb1
(
PjCb *gCb,
PjUlRbCb *pjRbCb
)





{
   PjUlUeCb *ueCb;

   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0008, L_DEBUG, pjRbCb->rbId, pjRbCb->rbType, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 848   , "pjUtlReEstSrb1(pjRbCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;

   ueCb = pjRbCb->ueCb;

   ueCb->libInfo.state = 2;




   pjUtlUlUpdCpSecKeys(gCb,ueCb);


   pjUlmReEstSrb(gCb,pjRbCb);


   if ((ueCb->numSrbs == 1) && (ueCb->numDrbs == 0))
   {
     pjUtlUlUpdUpSecKeys(gCb,ueCb);
   }

   return(0);
}
 S16 pjUtlUlReEstHO
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{
   U8 rbCnt;
   PjUlRbCb **rbCbLst;
   PjUlRbCb *pjRbCb;

   ;;





   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0009, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 913   , "pjUtlReEstHOStart(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;



   { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&ueCb->hoInfo, (Size) sizeof(PjUlHoInfo)) == 0) { cmMemset((U8 *)(ueCb->hoInfo), 0, sizeof(PjUlHoInfo)); } else { (ueCb->hoInfo) = 0L; } };







   { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&ueCb->hoInfo->hoCfmInfo, (Size) sizeof(PjUlHoCfmInfo) * 32) == 0) { cmMemset((U8 *)(ueCb->hoInfo->hoCfmInfo), 0, sizeof(PjUlHoCfmInfo) * 32); } else { (ueCb->hoInfo->hoCfmInfo) = 0L; } }
                                                          ;
   rbCbLst = ueCb->drbCb;
   for(rbCnt = 0; rbCnt < 32; rbCnt ++)
   {

      if( (pjRbCb = rbCbLst[rbCnt]) == 0L)
      {
         continue;
      }

      pjRbCb->state = 3;
      ueCb->libInfo.numReEstDrb++;
   }

   return(0);

}
 S16 pjUtlUlUpdUpSecKeys
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{
   PjSec *secInfo;
   Void *tmpUpCxt;

   ;;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb000a, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 1004   , "pjUtlUlUpdUpSecKeys(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;

   secInfo = &ueCb->secInfo;

   if(ueCb->secInfo.secAct == 1)
   {





      tmpUpCxt = ueCb->secInfo.upCxtId;

      pjUtlUlUpInit(gCb,ueCb);
      pjUtlUlCipherClose(gCb,tmpUpCxt);
   }

   return(0);
}
 S16 pjUtlUlUpdCpSecKeys
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{
   PjSec *secInfo;
   Void *tmpIntCxt;
   Void *tmpCpCxt;

   ;;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb000b, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 1063   , "pjUtlUlUpdCpSecKeys(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;

   secInfo = &ueCb->secInfo;

   if(ueCb->secInfo.secAct == 1)
   {





      tmpIntCxt = ueCb->secInfo.intCxtId;
      tmpCpCxt = ueCb->secInfo.cpCxtId;

      pjUtlUlCpInit(gCb,ueCb);
      pjUtlUlIntInit(gCb,ueCb);

      pjUtlUlIntClose(gCb,tmpIntCxt);
      pjUtlUlCipherClose(gCb,tmpCpCxt);
   }

   return(0);
}
 S16 pjUtlUlHdlRbReEstComplete
(
PjCb *gCb,
PjUlRbCb *pjRbCb
)





{
   PjUlUeCb *ueCb;

   ;;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev1(0xfb000c, L_DEBUG, pjRbCb->rbId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 1122   , "pjUtlUlHdlRbReEstComplete(rbCb(%d)", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                             ;

   ueCb = pjRbCb->ueCb;
   if (ueCb->libInfo.numReEstDrb == 0)
   {
      ueCb->libInfo.numReEstCmp++;
      return(0);
   }
   else
   {
      ueCb->libInfo.numReEstDrb--;
   }

   if (ueCb->libInfo.numReEstDrb == 0)
   {
      if (ueCb->libInfo.state == 2)
      {


         pjUtlUlUpdUpSecKeys(gCb, ueCb);




        pjUtlUlSndReEstCfgCfm(gCb,ueCb);
      }
      else if (ueCb->libInfo.state == 3)
      {
         pjUtlUlSndSduStaCfm(gCb,ueCb);
      }
   }
   return(0);

}
 S16 pjUtlUlSndReEstCfgCfm
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{
   CpjCfgCfmInfo *cfgCfmInfo;
   U8 txIdx;
   PjAsyncCfm *asyncCfm = 0L;
   PjCpjSapCb *cpjSap;

   ;;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb000d, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 1197   , "pjUtlSndReEstCfgCfm(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;


   for(txIdx = 0; txIdx < 2; txIdx++)
   {
      if((ueCb->libInfo.asyncCfm[txIdx] != 0L) &&
         (ueCb->libInfo.asyncCfm[txIdx]->cfmType & 0x04))
      {
         asyncCfm = ueCb->libInfo.asyncCfm[txIdx];
         break;
      }
   }


   if(asyncCfm == 0L)
   {
      return(0);
   }

   cpjSap = &(gCb->u.ulCb->cpjSap);
   if(SGetSBuf(cpjSap->pst.region,cpjSap->pst.pool,(Data **)&cfgCfmInfo,
      sizeof (CpjCfgCfmInfo)) != 0)
   {
      if( L_FATAL < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb000e, L_FATAL, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",1220, "Memory Allocation failed.", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(1);
   }

   { U8 _idx; for (_idx = 0; _idx < asyncCfm->numEnt ; _idx++) { if (asyncCfm->cfmEnt[_idx].cfgType == 0x04) { cfgCfmInfo->cfmEnt[_idx].status = 1; cfgCfmInfo->cfmEnt[_idx].reason = 0; } else { cfgCfmInfo->cfmEnt[_idx].status = asyncCfm->cfmEnt[_idx].status; cfgCfmInfo->cfmEnt[_idx].reason = asyncCfm->cfmEnt[_idx].reason; } cfgCfmInfo->cfmEnt[_idx].rbId = asyncCfm->cfmEnt[_idx].rbId; cfgCfmInfo->cfmEnt[_idx].rbType = asyncCfm->cfmEnt[_idx].rbType; } cfgCfmInfo->ueId = asyncCfm->ueId; cfgCfmInfo->cellId = asyncCfm->cellId; cfgCfmInfo->transId = asyncCfm->transId; cfgCfmInfo->numEnt = asyncCfm->numEnt; };
   { { if (ueCb->libInfo.asyncCfm[txIdx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[txIdx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[txIdx] = 0L; } }; ueCb->libInfo.asyncCfm[txIdx]=0L; if(ueCb->libInfo.nxtAvlbTxId == 2) { ueCb->libInfo.nxtAvlbTxId = txIdx; } };

   PjUiCpjCfgCfm(&gCb->u.ulCb->cpjSap.pst, gCb->u.ulCb->cpjSap.suId, cfgCfmInfo);

   return(0);
}
 S16 pjUtlUlSaveCfmInfo
(
PjCb *gCb,
PjUlUeCb *ueCb,
U8 cfmType,
Bool startTmr,
U8 entity,
U32 cfmPtr,
U32 cfgPtr
)
{
   S16 ret;
   CpjSecCfgCfmInfo *secCfm;
   CpjReEstCfmInfo *reEstCfm;
   CpjCfgCfmInfo *cfgCfm;
   U16 txId;
   PjAsyncCfm *tAsyncCfm;
   CpjCfgReqInfo *cfgReq;
   U8 cfmIdx;


   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xfb000f,L_DEBUG,DBG_UEID, ueCb->key.ueId, ueCb->key.cellId, cfmType, startTmr, entity,                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   ,                                                    1285   , "pjUtlSaveCfmInfo cellId(%d),cfmType(%d),startTmr(%d),entity(%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                                                     ;


   ret = 0;
   secCfm = 0L;
   reEstCfm = 0L;
   cfgCfm = 0L;
   cfgReq = 0L;
   txId = ueCb->libInfo.nxtAvlbTxId;

   if(txId == 2)
   {

      return(1);
   }


   if(ueCb->libInfo.asyncCfm[txId] != 0L)
   {
      return(1);
   }


   { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&ueCb->libInfo.asyncCfm[txId], (Size) sizeof(PjAsyncCfm)) == 0) { cmMemset((U8 *)(ueCb->libInfo.asyncCfm[txId]), 0, sizeof(PjAsyncCfm)); } else { (ueCb->libInfo.asyncCfm[txId]) = 0L; } };
   if(ueCb->libInfo.asyncCfm[txId]== 0L)
   {
      if( L_FATAL < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb0010, L_FATAL, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",1311, "Memory Allocation failed.", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(1);
   }


   tAsyncCfm = ueCb->libInfo.asyncCfm[txId];
   tAsyncCfm->libInitBitMask = ueCb->libInfo.tLibInitBitMask;
   tAsyncCfm->cmpInitBitMask = ueCb->libInfo.tCmpInitBitMask;
   tAsyncCfm->entity = entity;
   tAsyncCfm->startTmr = startTmr;

   ueCb->libInfo.tLibInitBitMask = 0;
   ueCb->libInfo.tCmpInitBitMask = 0;


   if(cfmType == 0x01)
   {
      secCfm = (CpjSecCfgCfmInfo *)cfmPtr;
      tAsyncCfm->cfmType = cfmType;
      tAsyncCfm->ueId = secCfm->ueId;
      tAsyncCfm->cellId = secCfm->cellId;
      tAsyncCfm->transId = secCfm->transId;
   }
   else if(cfmType == 0x10)
   {
      reEstCfm = (CpjReEstCfmInfo *)cfmPtr;
      tAsyncCfm->cfmType = cfmType;
      tAsyncCfm->ueId = reEstCfm->ueId;
      tAsyncCfm->cellId = reEstCfm->cellId;
      tAsyncCfm->transId = reEstCfm->transId;
   }
   else if((cfmType & 0x02) ||
           (cfmType & 0x04)||
           (cfmType & 0x08))
   {
      if(entity == 0xd8)
      {
         cfgCfm = (CpjCfgCfmInfo *)cfmPtr;
         cfgReq = (CpjCfgReqInfo *)cfgPtr;

         tAsyncCfm->cfmType = cfmType;
         tAsyncCfm->ueId = cfgCfm->ueId;
         tAsyncCfm->cellId = cfgCfm->cellId;
         tAsyncCfm->transId = cfgCfm->transId;
         tAsyncCfm->numEnt = cfgReq->numEnt;

         for ( cfmIdx = 0; cfmIdx < cfgReq->numEnt; cfmIdx++ )
         {
            tAsyncCfm->cfmEnt[cfmIdx].status = cfgCfm->cfmEnt[cfmIdx].status;
            tAsyncCfm->cfmEnt[cfmIdx].reason = cfgCfm->cfmEnt[cfmIdx].reason;
            tAsyncCfm->cfmEnt[cfmIdx].rbId = cfgCfm->cfmEnt[cfmIdx].rbId;
            tAsyncCfm->cfmEnt[cfmIdx].rbType = cfgCfm->cfmEnt[cfmIdx].rbType;
            tAsyncCfm->cfmEnt[cfmIdx].cfgType = cfgReq->cfgEnt[cfmIdx].cfgType;
         }
      }
      else if(entity == 0xd8)
      {
         CpjCfgEnt *pjCfg;
         CpjCfgCfmInfo *pjCfgCfm;

         pjCfgCfm = (CpjCfgCfmInfo *)cfmPtr;
         pjCfg = (CpjCfgEnt *)cfgPtr;

         tAsyncCfm->cfmType = cfmType;
         tAsyncCfm->transId = pjCfgCfm->transId;
         tAsyncCfm->ueId = pjCfgCfm->ueId;
         tAsyncCfm->cellId = pjCfgCfm->cellId;
         tAsyncCfm->numEnt = pjCfgCfm->numEnt;

         for ( cfmIdx = 0; cfmIdx < pjCfgCfm->numEnt; cfmIdx++ )
         {
            tAsyncCfm->cfmEnt[cfmIdx].status =
                                 pjCfgCfm->cfmEnt[cfmIdx].status;
            tAsyncCfm->cfmEnt[cfmIdx].reason =
                                 pjCfgCfm->cfmEnt[cfmIdx].reason;
            tAsyncCfm->cfmEnt[cfmIdx].rbId =
                                 pjCfgCfm->cfmEnt[cfmIdx].rbId;
            tAsyncCfm->cfmEnt[cfmIdx].rbType =
                                 pjCfgCfm->cfmEnt[cfmIdx].rbType;
         }
      }
   }
   if(tAsyncCfm->startTmr == 1)
   {
      if((pjChkTmr(gCb,(U32)ueCb, 0x15)) == 0)
      {
         pjStartTmr(gCb,(U32)ueCb, 0x15);
         ueCb->libInfo.crntTmrTxId = ueCb->libInfo.nxtAvlbTxId;
      }
   }


   for(cfmIdx = 0; cfmIdx < 2; cfmIdx++)
   {
      ueCb->libInfo.nxtAvlbTxId =
        (U16)((ueCb->libInfo.nxtAvlbTxId + 1) % 2);

      if(ueCb->libInfo.asyncCfm[ueCb->libInfo.nxtAvlbTxId] == 0L)
      {
         break;
      }
   }


   if(cfmIdx == 2)
   {
      ueCb->libInfo.nxtAvlbTxId = 2;
   }

   return(ret);
}
 S16 pjUtlUlHdlObdInitCfm
(
PjCb *gCb,
PjUlUeCb *ueCb,
U16 txIdx,
U8 cfmType,
U8 maskVal
)
{
   CpjSecCfgCfmInfo *secCfgCfm;
   CpjReEstCfmInfo *reEstCfm;
   PjAsyncCfm *asyncCfm;
   CpjCfgCfmInfo *cfgCfm;
   U8 idx;
   S16 ret;
   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xfb0011,L_DEBUG,DBG_UEID, ueCb->key.ueId, ueCb->key.cellId, txIdx, cfmType, maskVal,                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   ,                                                    1476   , "pjUtlHdlUlObdInitCfm(ueCb(%d,%d),txIdx(%d),cfmType(%d),maskVal(%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                                                     ;


   secCfgCfm = 0L;
   reEstCfm = 0L;
   cfgCfm = 0L;
   asyncCfm = 0L;
   ret = 0;

   if((txIdx == 2) ||
      (ueCb->libInfo.asyncCfm[txIdx] == 0L))
   {
      return(1);
   }

   asyncCfm = ueCb->libInfo.asyncCfm[txIdx];

   if(cfmType & 1)
   {

      asyncCfm->libInitBitMask ^= (maskVal);
      ret = pjUtlUlHdlSecInitCfm(gCb,ueCb,txIdx,asyncCfm,secCfgCfm,reEstCfm);
   }
   else if(cfmType & 2)
   {

      asyncCfm->cmpInitBitMask &= ~(1 << (maskVal - 1));


      for ( idx = 0; idx < asyncCfm->numEnt; idx++ )
      {
         if ( asyncCfm->cfmEnt[idx].rbId == maskVal)
         {
            asyncCfm->cfmEnt[idx].status = 1;
            asyncCfm->cfmEnt[idx].reason = 0;
            break;
         }
      }

      ret = pjUtlUlHdlCmpInitCfm(gCb,ueCb,txIdx,asyncCfm,cfgCfm);
   }

   return(ret);
}
 S16 pjUtlUlHdlInitObdTmrExp
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{
   S16 ret;
   CpjSecCfgCfmInfo *secCfgCfm;
   CpjCfgCfmInfo *cfgCfm;
   CpjReEstCfmInfo *reEstCfm;
   CpjCfgCfmInfo *pjCfgCfm;
   PjLibInfo *libInfo;
   PjAsyncCfm *asyncCfm;
   PjCpjSapCb *cpjSap;
   U16 txIdx;
   U16 idx;
   U16 cfgIdx;

   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0012, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 1568   , "pjUtlHdlInitObdTmrExp(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;

   ret = 0;
   cpjSap = &(gCb->u.ulCb->cpjSap);
   secCfgCfm = 0L;
   libInfo = &ueCb->libInfo;
   txIdx = libInfo->crntTmrTxId;


   { U16 _idx; if(ueCb->libInfo.crntTmrTxId == txIdx) { pjStopTmr(gCb,(U32)ueCb, 0x15); } if(pjChkTmr(gCb,(U32)ueCb, 0x15) == 0) { for(_idx = 0; _idx < (2 - 1) ; _idx++) { ueCb->libInfo.crntTmrTxId = (U16)((ueCb->libInfo.crntTmrTxId + 1) % 2); if((ueCb->libInfo.asyncCfm[ueCb->libInfo.crntTmrTxId] != 0L) && (ueCb->libInfo.asyncCfm[ueCb->libInfo.crntTmrTxId]->startTmr == 1)) { pjStartTmr(gCb,(U32)ueCb, 0x15); break; } } } };


   if( txIdx >= 2 || libInfo->asyncCfm[txIdx] == 0L)
   {
      return(0);
   }

   asyncCfm = libInfo->asyncCfm[txIdx];


   if(asyncCfm->cfmType & 0x01)
   {
      { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&secCfgCfm, (Size) sizeof(CpjSecCfgCfmInfo)) == 0) { cmMemset((U8 *)(secCfgCfm), 0, sizeof(CpjSecCfgCfmInfo)); } else { (secCfgCfm) = 0L; } };







      { secCfgCfm->ueId = asyncCfm->ueId; secCfgCfm->cellId = asyncCfm->cellId; secCfgCfm->transId = asyncCfm->transId; secCfgCfm->status = 1; secCfgCfm->reason = 0; };
      secCfgCfm->status = 2;
      secCfgCfm->reason = 22;

      { { if (ueCb->libInfo.asyncCfm[txIdx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[txIdx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[txIdx] = 0L; } }; ueCb->libInfo.asyncCfm[txIdx]=0L; if(ueCb->libInfo.nxtAvlbTxId == 2) { ueCb->libInfo.nxtAvlbTxId = txIdx; } };

      PjUiCpjSecCfgCfm(&(cpjSap->pst), cpjSap->suId, secCfgCfm);
   }


   else if ((asyncCfm->cfmType & 0x02) ||
            (asyncCfm->cfmType & 0x04))
   {
      { U16 _idx; { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&cfgCfm, (Size) sizeof(CpjCfgCfmInfo)) == 0) { cmMemset((U8 *)(cfgCfm), 0, sizeof(CpjCfgCfmInfo)); } else { (cfgCfm) = 0L; } }; if (cfgCfm != 0L) { for ( _idx = 0; _idx < asyncCfm->numEnt ; _idx++) { if ( asyncCfm->cmpInitBitMask & (1 << (asyncCfm->cfmEnt[_idx].rbId - 1))) { cfgCfm->cfmEnt[_idx].status = 2; cfgCfm->cfmEnt[_idx].reason = 22; } else { cfgCfm->cfmEnt[_idx].status = asyncCfm->cfmEnt[_idx].status; cfgCfm->cfmEnt[_idx].reason = asyncCfm->cfmEnt[_idx].reason; } cfgCfm->cfmEnt[_idx].rbId = asyncCfm->cfmEnt[_idx].rbId; cfgCfm->cfmEnt[_idx].rbType = asyncCfm->cfmEnt[_idx].rbType; } cfgCfm->ueId = asyncCfm->ueId; cfgCfm->cellId = asyncCfm->cellId; cfgCfm->transId = asyncCfm->transId; cfgCfm->numEnt = asyncCfm->numEnt; } };

      { { if (ueCb->libInfo.asyncCfm[txIdx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[txIdx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[txIdx] = 0L; } }; ueCb->libInfo.asyncCfm[txIdx]=0L; if(ueCb->libInfo.nxtAvlbTxId == 2) { ueCb->libInfo.nxtAvlbTxId = txIdx; } };

      PjUiCpjCfgCfm(&(cpjSap->pst), cpjSap->suId, cfgCfm);
   }
   else if (asyncCfm->cfmType & 0x10)
   {

      { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&reEstCfm, (Size) sizeof(CpjReEstCfmInfo)) == 0) { cmMemset((U8 *)(reEstCfm), 0, sizeof(CpjReEstCfmInfo)); } else { (reEstCfm) = 0L; } };







      { reEstCfm->ueId = asyncCfm->ueId; reEstCfm->cellId = asyncCfm->cellId; reEstCfm->transId = asyncCfm->transId; reEstCfm->status = 1; };

      { { if (ueCb->libInfo.asyncCfm[txIdx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[txIdx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[txIdx] = 0L; } }; ueCb->libInfo.asyncCfm[txIdx]=0L; if(ueCb->libInfo.nxtAvlbTxId == 2) { ueCb->libInfo.nxtAvlbTxId = txIdx; } };

      PjUiCpjReEstCfm(&gCb->u.ulCb->cpjSap.pst,
                       gCb->u.ulCb->cpjSap.suId, reEstCfm);


      cfgIdx = (U16)(txIdx + 1);

      for(idx = 0; idx < 2; idx++, cfgIdx++)
      {
         cfgIdx %= 2;
         if((libInfo->asyncCfm[cfgIdx] != 0L) &&
            (libInfo->asyncCfm[cfgIdx]->cfmType & 0x04))
         {
            break;
         }
      }


      if(idx == 2)
      {
         return(0);
      }

      { U16 _idx; if(ueCb->libInfo.crntTmrTxId == cfgIdx) { pjStopTmr(gCb,(U32)ueCb, 0x15); } if(pjChkTmr(gCb,(U32)ueCb, 0x15) == 0) { for(_idx = 0; _idx < (2 - 1) ; _idx++) { ueCb->libInfo.crntTmrTxId = (U16)((ueCb->libInfo.crntTmrTxId + 1) % 2); if((ueCb->libInfo.asyncCfm[ueCb->libInfo.crntTmrTxId] != 0L) && (ueCb->libInfo.asyncCfm[ueCb->libInfo.crntTmrTxId]->startTmr == 1)) { pjStartTmr(gCb,(U32)ueCb, 0x15); break; } } } };
      asyncCfm = libInfo->asyncCfm[cfgIdx];

      { U16 _idx; { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&cfgCfm, (Size) sizeof(CpjCfgCfmInfo)) == 0) { cmMemset((U8 *)(cfgCfm), 0, sizeof(CpjCfgCfmInfo)); } else { (cfgCfm) = 0L; } }; if (cfgCfm != 0L) { for ( _idx = 0; _idx < asyncCfm->numEnt ; _idx++) { if ( asyncCfm->cmpInitBitMask & (1 << (asyncCfm->cfmEnt[_idx].rbId - 1))) { cfgCfm->cfmEnt[_idx].status = 2; cfgCfm->cfmEnt[_idx].reason = 22; } else { cfgCfm->cfmEnt[_idx].status = asyncCfm->cfmEnt[_idx].status; cfgCfm->cfmEnt[_idx].reason = asyncCfm->cfmEnt[_idx].reason; } cfgCfm->cfmEnt[_idx].rbId = asyncCfm->cfmEnt[_idx].rbId; cfgCfm->cfmEnt[_idx].rbType = asyncCfm->cfmEnt[_idx].rbType; } cfgCfm->ueId = asyncCfm->ueId; cfgCfm->cellId = asyncCfm->cellId; cfgCfm->transId = asyncCfm->transId; cfgCfm->numEnt = asyncCfm->numEnt; } };

      { { if (ueCb->libInfo.asyncCfm[txIdx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[txIdx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[txIdx] = 0L; } }; ueCb->libInfo.asyncCfm[txIdx]=0L; if(ueCb->libInfo.nxtAvlbTxId == 2) { ueCb->libInfo.nxtAvlbTxId = txIdx; } };

      PjUiCpjCfgCfm(&(cpjSap->pst), cpjSap->suId, cfgCfm);
   }
   else if(asyncCfm->cfmType & 0x08)
   {

      pjStopTmr(gCb,(U32)ueCb, 0x15);
      ret = cmHashListDelete(&(gCb->u.ulCb->ueLstCp), (U32) ueCb);
      if (ret != 0)
      {


         if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xfb0013,L_DEBUG,DBG_UEID, ueCb->key.ueId, 0, 0, 0, 0,                                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"         ,                                                                         1673         , "pjUtlHdlInitObdTmrExp: cmHashListDelete Failed for ueCb.", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                          ;

      }

      if ( asyncCfm->entity == 0xd8 )
      {
         { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&cfgCfm, (Size) sizeof(CpjCfgCfmInfo)) == 0) { cmMemset((U8 *)(cfgCfm), 0, sizeof(CpjCfgCfmInfo)); } else { (cfgCfm) = 0L; } };
         for ( idx = 0; idx < asyncCfm->numEnt; idx++)
         {
            cfgCfm->cfmEnt[idx].status = asyncCfm->cfmEnt[idx].status;
            cfgCfm->cfmEnt[idx].reason = asyncCfm->cfmEnt[idx].reason;
            cfgCfm->cfmEnt[idx].rbId = asyncCfm->cfmEnt[idx].rbId;
            cfgCfm->cfmEnt[idx].rbType = asyncCfm->cfmEnt[idx].rbType;
         }
         cfgCfm->ueId = asyncCfm->ueId;
         cfgCfm->cellId = asyncCfm->cellId;
         cfgCfm->transId = asyncCfm->transId;
         cfgCfm->numEnt = asyncCfm->numEnt;


         for(idx = 0; idx < 2; idx++)
         {
            if(libInfo->asyncCfm[idx] != 0L)
            {
               { if (ueCb->libInfo.asyncCfm[idx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[idx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[idx] = 0L; } };
               ueCb->libInfo.asyncCfm[idx] = 0L;
            }
         }

         { if (ueCb != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb, (Size) sizeof(PjUlUeCb)); ueCb = 0L; } };
         PjUiCpjCfgCfm(&(cpjSap->pst), cpjSap->suId, cfgCfm);
      }
      else if ( asyncCfm->entity == 0xd8 )
      {
         { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&pjCfgCfm, (Size) sizeof(CpjCfgCfmInfo)) == 0) { cmMemset((U8 *)(pjCfgCfm), 0, sizeof(CpjCfgCfmInfo)); } else { (pjCfgCfm) = 0L; } };







         for ( idx = 0; idx < asyncCfm->numEnt; idx++)
         {
            pjCfgCfm->cfmEnt[idx].status = asyncCfm->cfmEnt[idx].status;
            pjCfgCfm->cfmEnt[idx].reason = asyncCfm->cfmEnt[idx].reason;
            pjCfgCfm->cfmEnt[idx].rbId = asyncCfm->cfmEnt[idx].rbId;
            pjCfgCfm->cfmEnt[idx].rbType = asyncCfm->cfmEnt[idx].rbType;
         }
         pjCfgCfm->ueId = asyncCfm->ueId;
         pjCfgCfm->cellId = asyncCfm->cellId;
         pjCfgCfm->transId = asyncCfm->transId;
         pjCfgCfm->numEnt = asyncCfm->numEnt;


         for(idx = 0; idx < 2; idx++)
         {
            if(libInfo->asyncCfm[idx] != 0L)
            {
               { if (ueCb->libInfo.asyncCfm[idx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[idx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[idx] = 0L; } };
               ueCb->libInfo.asyncCfm[idx] = 0L;
            }
         }

         { if (ueCb != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb, (Size) sizeof(PjUlUeCb)); ueCb = 0L; } };
         PjUiCpjCfgCfm(&(cpjSap->pst), cpjSap->suId, pjCfgCfm);
      }
   }

   return(ret);
}
 S16 pjUtlUlSndSduStaCfm
(
PjCb *gCb,
PjUlUeCb *ueCb
)





{
   U8 rbCnt;
   CpjSduStaCfmInfo *cfmInfo;
   UdxSduStaCfmInfo *udxCfmInfo;
   UdxSduStaInfo tempDlStaInfo[32] = {{0}};
   U8 rbId;
   U8 numRb = 0;
   PjUlHoCfmInfo *hoCfmInfo;
   CpjSduStaInfo *staInfo;
   Bool rbPres;
   PjCpjSapCb *cpjSap;
   PjUdxUlSapCb *udxSap;


   ;;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev2(0xfb0014, L_DEBUG, ueCb->key.ueId, ueCb->key.cellId, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"   , 1802   , "pjUtlUlSndSduStaCfm(ueCb(%d,%d))", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;

   cpjSap = &(gCb->u.ulCb->cpjSap);
   if(SGetSBuf(cpjSap->pst.region,cpjSap->pst.pool,(Data **)&cfmInfo,
      sizeof (CpjSduStaCfmInfo)) != 0)
   {
      if( L_FATAL < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb0015, L_FATAL, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",1808, "Memory Allocation failed.", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(1);
   }

   cfmInfo->ueId = ueCb->key.ueId;
   cfmInfo->cellId = ueCb->key.cellId;
   cfmInfo->transId = ueCb->hoInfo->transId;
   cfmInfo->reason = 0;
   udxCfmInfo = ueCb->hoInfo->staCfm;

   for(rbCnt = 0; rbCnt < udxCfmInfo->numRb; rbCnt++)
   {



      rbId = udxCfmInfo->sduStaInfo[rbCnt].rbId;
      if(udxCfmInfo->sduStaInfo[rbCnt].dlSduStaInfo.hoPres == 1)
      {
         tempDlStaInfo[rbId].rbId = udxCfmInfo->sduStaInfo[rbCnt].rbId;
         tempDlStaInfo[rbId].dir = udxCfmInfo->sduStaInfo[rbCnt].dir;
         tempDlStaInfo[rbId].dlSduStaInfo.count = udxCfmInfo->sduStaInfo[rbCnt].dlSduStaInfo.count;
         tempDlStaInfo[rbId].dlSduStaInfo.hoPres = 1;
      }
   }

   for(rbCnt = 0;
      ((rbCnt < 32) && (numRb < 12)); rbCnt++)
   {
      rbPres = 0;
      hoCfmInfo = &ueCb->hoInfo->hoCfmInfo[rbCnt];
      staInfo = &cfmInfo->sduStaInfo[numRb];
      memset((void *)staInfo,0,sizeof(CpjSduStaInfo));
      if(hoCfmInfo->pres == 1)
      {
         rbPres = 1;
         staInfo->rbId = hoCfmInfo->rbId;
         staInfo->dir |= hoCfmInfo->dir;
         staInfo->snLen = ueCb->drbCb[hoCfmInfo->rbId]->snLen;
         staInfo->ulSduStaInfo.numBits = hoCfmInfo->numBits;
         if (hoCfmInfo->numBits > 0)
         {

            cpjSap = &(gCb->u.ulCb->cpjSap);
            if(SGetSBuf(cpjSap->pst.region,cpjSap->pst.pool,
                        (Data **)&staInfo->ulSduStaInfo.ulBitMap,
                        sizeof (U8) * (hoCfmInfo->numBits / 8)) != 0)
            {
               if( L_FATAL < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb0016, L_FATAL, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",1855, "Memory Allocation failed.", RLOG_FILE_ID, RLOG_MODULE_NAME); };
               return(1);
            }
            { cmMemcpy((U8*)staInfo->ulSduStaInfo.ulBitMap, (U8 *)hoCfmInfo->ulBitMap, (hoCfmInfo->numBits / 8)); };
            { if (hoCfmInfo->ulBitMap != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) hoCfmInfo->ulBitMap, (Size) sizeof(U8) * (hoCfmInfo->numBits / 8)); hoCfmInfo->ulBitMap = 0L; } };
         }
         staInfo->ulSduStaInfo.count = hoCfmInfo->count;
      }
      if(tempDlStaInfo[rbCnt].dlSduStaInfo.hoPres == 1)
      {
         rbPres = 1;
         staInfo->rbId = tempDlStaInfo[rbCnt].rbId;
         staInfo->dir |= tempDlStaInfo[rbCnt].dir;
         staInfo->snLen = ueCb->drbCb[staInfo->rbId]->snLen;
         staInfo->dlSduStaInfo.count = tempDlStaInfo[rbCnt].dlSduStaInfo.count;
      }
      if(rbPres != 1)
      {
         continue;
      }
      else
      {
        numRb++;
      }
   }

   cfmInfo->numRb = numRb;
   cfmInfo->status = 0;
   cfmInfo->reason = 0;
   { if (ueCb->hoInfo->hoCfmInfo != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->hoInfo->hoCfmInfo, (Size) (32 * sizeof(PjUlHoCfmInfo))); ueCb->hoInfo->hoCfmInfo = 0L; } }
                                                          ;

   udxSap = (&(gCb->u.ulCb->udxUlSap[0]));
   { if (ueCb->hoInfo->staCfm != 0L) { (Void) SPutSBuf(udxSap->pst.region, udxSap->pst.pool, (Data *) ueCb->hoInfo->staCfm, (Size) sizeof (UdxSduStaCfmInfo)); ueCb->hoInfo->staCfm = 0L; } }
                                          ;
   { if (ueCb->hoInfo != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->hoInfo, (Size) sizeof(PjUlHoInfo)); ueCb->hoInfo = 0L; } };

   PjUiCpjSduStaCfm(&gCb->u.ulCb->cpjSap.pst,
                     gCb->u.ulCb->cpjSap.suId, cfmInfo);

   return(0);
}
 S16 pjUtlUlShutdown
(
PjCb *gCb
)




{
   S16 ret;
   PjUlUeCb *ueCb;
   PjUlUeCb *prevUeCb;
   PjUlRbCb *rbCb;
   PjUlRbCb **rbCbLst;
   PjSec *secInfo;
   U8 idx;



   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb0017, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",1936, "pjUtlShutdown()", RLOG_FILE_ID, RLOG_MODULE_NAME); };

   ret = 0;
   ueCb = 0L;
   prevUeCb = 0L;
   rbCb = 0L;
   rbCbLst = 0L;
   idx = 0;


   while (cmHashListGetNext(&(gCb->u.ulCb->ueLstCp), (U32) prevUeCb, (U32 *)&ueCb) == 0)
   {
      if ( ueCb != 0L )
      {






         rbCbLst = ueCb->srbCb;
         for (idx = 0; idx < 3; idx++)
         {
             rbCb = rbCbLst[idx];
             if (rbCb != 0L)
             {

               pjUtlUlFreeRb(gCb,rbCb);
             }
         }
         rbCbLst = ueCb->drbCb;
         for (idx = 0; idx < 32; idx++)
         {
             rbCb = rbCbLst[idx];
             if (rbCb != 0L)
             {
                pjUtlUlFreeRb(gCb,rbCb);
             }
         }

         secInfo = &(ueCb->secInfo);
         pjUtlUlCipherClose(gCb,secInfo->cpCxtId);
         pjUtlUlCipherClose(gCb,secInfo->upCxtId);
         pjUtlUlIntClose(gCb,secInfo->intCxtId);


         if (ueCb->hoInfo != 0L)
         {
            for (idx = 0; idx < 32; idx++)
            {
               if (ueCb->hoInfo->hoCfmInfo[idx].pres == 1)
               {
                  { if (ueCb->hoInfo->hoCfmInfo[idx].ulBitMap != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->hoInfo->hoCfmInfo[idx].ulBitMap, (Size) (ueCb->hoInfo->hoCfmInfo[idx].numBits % 8)? ((ueCb->hoInfo->hoCfmInfo[idx].numBits / 8) + 1): (ueCb->hoInfo->hoCfmInfo[idx].numBits / 8 )); ueCb->hoInfo->hoCfmInfo[idx].ulBitMap = 0L; } }


                                                                    ;
               }
            }

            { if (ueCb->hoInfo->hoCfmInfo != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->hoInfo->hoCfmInfo, (Size) (32 * sizeof(PjUlHoCfmInfo))); ueCb->hoInfo->hoCfmInfo = 0L; } }
                                                                       ;
            { if (ueCb->hoInfo != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->hoInfo, (Size) sizeof(PjUlHoInfo)); ueCb->hoInfo = 0L; } };
         }
      }
      prevUeCb = ueCb;
   }
   ret = pjDbmUlDeInit(gCb);






   return(ret);
}
 Void pjUtlUlFreeRb
(
PjCb *gCb,
PjUlRbCb *pjRbCb
)





{
   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb0018, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",2061, "pjUtlFreeRb()", RLOG_FILE_ID, RLOG_MODULE_NAME); };







   pjDbmRxDeInit(gCb,&(pjRbCb->ulCb.recBuf));

   pjUtlCmpClose(gCb,pjRbCb->cmpCxtId);

   return;
}
 S16 pjUtlUlSndDatFwdInd
(
PjCb *gCb,
PjUlRbCb *pjRbCb,
PjuDatFwdIndInfo *datFwdInd
)






{
   CmLtePdcpId *pdcpId;
   PjPjuSapCb *pjuSap;
   CmLtePdcpId pdcpIdTmp;

   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb0019, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",2115, "pjUtlSndDatFwdInd()", RLOG_FILE_ID, RLOG_MODULE_NAME); };

   pjuSap = &(gCb->u.ulCb->pjuSap[1]);
   pdcpId = &pdcpIdTmp;

   if(pdcpId != 0L)
   {
      pdcpId->ueId = pjRbCb->ueCb->key.ueId;
      pdcpId->cellId = pjRbCb->ueCb->key.cellId;
      pdcpId->rbId = pjRbCb->rbId;
      pdcpId->rbType = pjRbCb->rbType;

      gCb->pjGenSts.numPktsFrwd += datFwdInd->numSdus;

      if(gCb->init.trc == 1)
      {

         pjLmmSendTrc(gCb,0x48, 0L);
      }
      PjUiPjuDatFwdInd(&(pjuSap->pst), pjuSap->suId, pdcpId, datFwdInd);
   }

  return(0);

}
 S16 pjUtlUlSndUlStaRep
(
PjCb *gCb,
PjUlRbCb *pjRbCb,
Buffer *sta
)






{
   PjUdxUlSapCb *udxSap;
   UdxUlStaRepInfo *staRep;
   S16 ret = 0;

   udxSap = (&(gCb->u.ulCb->udxUlSap[0]));

   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb001a, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",2181, "pjUtlUlSndUlStaRep()", RLOG_FILE_ID, RLOG_MODULE_NAME); };

   { if(SGetStaticBuffer(udxSap->pst.region, udxSap->pst.pool, (Data **)&staRep, (Size) sizeof (UdxUlStaRepInfo), 0) != 0) { ret = 1; } }
                                                   ;

   if(ret != 0)
   {
     staRep = 0L;
   }

   if(staRep != 0L)
   {
      staRep->pdcpId.ueId = pjRbCb->ueCb->key.ueId;
      staRep->pdcpId.cellId = pjRbCb->ueCb->key.cellId;
      staRep->pdcpId.rbId = pjRbCb->rbId;
      staRep->pdcpId.rbType = pjRbCb->rbType;
      staRep->sta = sta;

      PjUlUdxUlStaRep(&(udxSap->pst), udxSap->spId, staRep);
   }
   else
   {
      { if (sta != 0L) { SPutMsg(sta); } sta = 0L; };
   }

   return(0);
}
 S16 pjUtlUlSndUlRohcFdbk
(
PjCb *gCb,
PjUlRbCb *pjRbCb,
Buffer *fbPkt
)






{
   PjUdxUlSapCb *udxSap;
   UdxUlFdbkPktInfo *fdbkPktInfo;
   S16 ret = 0;

   udxSap = (&(gCb->u.ulCb->udxUlSap[0]));

   ;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xfb001b, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c",2251, "pjUtlUlSndUlRohcFdbk()", RLOG_FILE_ID, RLOG_MODULE_NAME); };

   { if(SGetStaticBuffer(udxSap->pst.region, udxSap->pst.pool, (Data **)&fdbkPktInfo, (Size) sizeof (UdxUlFdbkPktInfo), 0) != 0) { ret = 1; } }
                                     ;
   if(ret != 0)
   {
      fdbkPktInfo= 0L;
   }

   if(fdbkPktInfo != 0L)
   {
      fdbkPktInfo->pdcpId.ueId = pjRbCb->ueCb->key.ueId;
      fdbkPktInfo->pdcpId.cellId = pjRbCb->ueCb->key.cellId;
      fdbkPktInfo->pdcpId.rbId = pjRbCb->rbId;
      fdbkPktInfo->pdcpId.rbType = pjRbCb->rbType;
      fdbkPktInfo->fbPkt = fbPkt;

      PjUlUdxUlFdbkPktInfo(&(udxSap->pst), udxSap->spId, fdbkPktInfo);
   }
   else
   {
      { if (fbPkt != 0L) { SPutMsg(fbPkt); } fbPkt = 0L; };
   }

   return(0);
}
 S16 pjUtlUlResetBuffrdPkts
(
PjCb *gCb,
PjUlRbCb *pjRbCb
)





{
   PjRxEnt *oldRxEnt = 0L;
   PjRxEnt *rxEnt = 0L;
   U32 pktCount = 0;
   U16 fms = 0;

   ;;

   fms = pjRbCb->ulCb.nxtRxSn;
   pktCount = pjRbCb->ulCb.recBuf.datPktQ.count;

   ((&pjRbCb->ulCb.recBuf.datPktQ)->crnt = (&pjRbCb->ulCb.recBuf.datPktQ)->first);
   while((((&pjRbCb->ulCb.recBuf.datPktQ)->crnt)) && (pktCount > 0))
   {

      { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&rxEnt, (Size) sizeof(PjRxEnt)) == 0) { cmMemset((U8 *)(rxEnt), 0, sizeof(PjRxEnt)); } else { (rxEnt) = 0L; } };
      oldRxEnt = (PjRxEnt *) ((((&pjRbCb->ulCb.recBuf.datPktQ)->crnt))->node);

      if (pjRbCb->snLen == 12)
      {
         if((oldRxEnt->count & 0x0fff) > fms)
         {

            rxEnt->count = (((pjRbCb->ulCb.rxHfn) << (pjRbCb->snLen)) | (oldRxEnt->count & 0x0fff));
            pktCount--;
         }
         else
         {



            rxEnt->count = (((pjRbCb->ulCb.rxHfn + 1) << (pjRbCb->snLen)) | (oldRxEnt->count & 0x0fff));
            pktCount--;
         }
      }
      else if (pjRbCb->snLen == 15)
      {
         if((oldRxEnt->count & 0x7fff) > fms)
         {

            rxEnt->count = (((pjRbCb->ulCb.rxHfn) << (pjRbCb->snLen)) | (oldRxEnt->count & 0x7fff));
            pktCount--;
         }
         else
         {



            rxEnt->count = (((pjRbCb->ulCb.rxHfn + 1) << (pjRbCb->snLen)) | (oldRxEnt->count & 0x7fff));
            pktCount--;
         }
      }

      rxEnt->state = 7;
      SCpyMsgMsg(oldRxEnt->mBuf, gCb->init.region, gCb->init.pool, &rxEnt->mBuf);
      rxEnt->isOutSeq = oldRxEnt->isOutSeq;


      pjDbmInsRxEnt(gCb, &pjRbCb->ulCb.recBuf, rxEnt, 0);

      pjDbmDelRxEnt(gCb, &pjRbCb->ulCb.recBuf, oldRxEnt->count);
      ((&pjRbCb->ulCb.recBuf.datPktQ)->crnt = ((&pjRbCb->ulCb.recBuf.datPktQ)->crnt ? (&pjRbCb->ulCb.recBuf.datPktQ)->crnt->next : (&pjRbCb->ulCb.recBuf.datPktQ)->first));
   }

   return(0);

}
 S16 pjUtlUlPrcsDatResume
(
PjCb *gCb,
CpjDatResumeReqInfo *datResReq
)





{
   U8 rbCnt;
   PjUlRbCb *pjRbCb = 0L;
   PjUlUeCb *ueCb= 0L;

   pjDbmFetchUlUeCb(gCb, datResReq->ueId, datResReq->cellId, &ueCb);
   if(!ueCb)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xfb001c,L_ERROR,DBG_CELLID, datResReq->cellId, datResReq->ueId, 0, 0, 0,                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltepdcp/pj_ul_utl.c"      ,                           2575      , "UeId[%u] not found", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                            ;
      return(1);
   }

   for(rbCnt = 0; rbCnt < 32; rbCnt ++)
   {

      if( (pjRbCb = ueCb->drbCb[rbCnt]) == 0L)
      {
         continue;
      }





      pjUlmProcessUlPktQ(gCb, pjRbCb);
      pjRbCb->state = 1;
   }
   ueCb->libInfo.state = 1;
   return(0);
}

 Void pjUtlEmptyUlPktList(PjCb *gCb, PjUlRbCb *pjRbCb)
{
   PjUlPkt *ulPkt;
   CmLListCp *ulPktLst = &pjRbCb->ulCb.ulPktLst;
   while(ulPktLst->first)
   {
      ulPkt = (PjUlPkt *)(ulPktLst->first->node);
      cmLListDelFrm(ulPktLst, ulPktLst->first);
      { if (ulPkt->pdu != 0L) { SPutMsg(ulPkt->pdu); } ulPkt->pdu = 0L; };
      { if (ulPkt != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ulPkt, (Size) sizeof(PjUlPkt)); ulPkt = 0L; } };
   }
   return;
}

void dumpPDCPUlRbInformation(PjUlRbCb* ulRbCb, U16 ueId)
{
   PjUlCb* ulCb = &ulRbCb->ulCb;

   printf("UE [%u] PDCP UL RB numEntries = %lu\n",ueId, ulCb->recBuf.numEntries);
}


void DumpPDCPUlDebugInformation(void)
{
   PjCb* ulInst = pjCb[0];

   PjUlgCb* ulgCb = ulInst->u.ulCb;

   PjUlUeCb *ueCb = 0L;
   printf("PDCP UL Information\n");
   printf("===================\n");


   while (0 == cmHashListGetNext(&ulgCb->ueLstCp,
                                   (U32) ueCb,
                                   (U32 *)&ueCb))
   {
      U32 i;
      for(i = 0; i < 3; i++)
      {
         PjUlRbCb* rbCb = ueCb->srbCb[i];
         if(rbCb != 0L)
         {
            dumpPDCPUlRbInformation(rbCb, ueCb->key.ueId);
         }
      }
      for(i = 0; i < 32; i++)
      {
         PjUlRbCb* rbCb = ueCb->drbCb[i];
         if(rbCb != 0L)
         {
            dumpPDCPUlRbInformation(rbCb, ueCb->key.ueId);
         }
      }
   }
}


static S16 pjUtlUlHdlSecInitCfm
(
PjCb *gCb,
PjUlUeCb *ueCb,
U16 txIdx,
PjAsyncCfm *asyncCfm,
CpjSecCfgCfmInfo *secCfgCfm,
CpjReEstCfmInfo *reEstCfm
)
{
   ;

   if(asyncCfm->libInitBitMask == 0)
   {
      { U16 _idx; if(ueCb->libInfo.crntTmrTxId == txIdx) { pjStopTmr(gCb,(U32)ueCb, 0x15); } if(pjChkTmr(gCb,(U32)ueCb, 0x15) == 0) { for(_idx = 0; _idx < (2 - 1) ; _idx++) { ueCb->libInfo.crntTmrTxId = (U16)((ueCb->libInfo.crntTmrTxId + 1) % 2); if((ueCb->libInfo.asyncCfm[ueCb->libInfo.crntTmrTxId] != 0L) && (ueCb->libInfo.asyncCfm[ueCb->libInfo.crntTmrTxId]->startTmr == 1)) { pjStartTmr(gCb,(U32)ueCb, 0x15); break; } } } };
      if(ueCb->libInfo.state == 1)
      {

         { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&secCfgCfm, (Size) sizeof(CpjSecCfgCfmInfo)) == 0) { cmMemset((U8 *)(secCfgCfm), 0, sizeof(CpjSecCfgCfmInfo)); } else { (secCfgCfm) = 0L; } };







         { secCfgCfm->ueId = asyncCfm->ueId; secCfgCfm->cellId = asyncCfm->cellId; secCfgCfm->transId = asyncCfm->transId; secCfgCfm->status = 1; secCfgCfm->reason = 0; };

         { { if (ueCb->libInfo.asyncCfm[txIdx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[txIdx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[txIdx] = 0L; } }; ueCb->libInfo.asyncCfm[txIdx]=0L; if(ueCb->libInfo.nxtAvlbTxId == 2) { ueCb->libInfo.nxtAvlbTxId = txIdx; } };

         PjUiCpjSecCfgCfm(&gCb->u.ulCb->cpjSap.pst, gCb->u.ulCb->cpjSap.suId, secCfgCfm);
      }
      else if(ueCb->libInfo.state == 2)
      {

         { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&reEstCfm, (Size) sizeof(CpjReEstCfmInfo)) == 0) { cmMemset((U8 *)(reEstCfm), 0, sizeof(CpjReEstCfmInfo)); } else { (reEstCfm) = 0L; } };
         { reEstCfm->ueId = asyncCfm->ueId; reEstCfm->cellId = asyncCfm->cellId; reEstCfm->transId = asyncCfm->transId; reEstCfm->status = 0; };


         { { if (ueCb->libInfo.asyncCfm[txIdx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[txIdx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[txIdx] = 0L; } }; ueCb->libInfo.asyncCfm[txIdx]=0L; if(ueCb->libInfo.nxtAvlbTxId == 2) { ueCb->libInfo.nxtAvlbTxId = txIdx; } };





         PjUiCpjReEstCfm(&gCb->u.ulCb->cpjSap.pst, gCb->u.ulCb->cpjSap.suId, reEstCfm);
      }
   }

 return(0);
}



static S16 pjUtlUlHdlCmpInitCfm
(
PjCb *gCb,
PjUlUeCb *ueCb,
U16 txIdx,
PjAsyncCfm *asyncCfm,
CpjCfgCfmInfo *cfgCfm
)
{
   U32 idx;

   ;

      if(asyncCfm->cmpInitBitMask == 0)
      {
         asyncCfm->libInitBitMask ^= (0x00000001);

         if((asyncCfm->libInitBitMask == 0) &&
               !(asyncCfm->cfmType & 0x04))
         {


            { if (SGetSBuf(gCb->init.region, gCb->init.pool, (Data **)&cfgCfm, (Size) sizeof(CpjCfgCfmInfo)) == 0) { cmMemset((U8 *)(cfgCfm), 0, sizeof(CpjCfgCfmInfo)); } else { (cfgCfm) = 0L; } };







            cfgCfm->transId = asyncCfm->transId;
            cfgCfm->ueId = asyncCfm->ueId;
            cfgCfm->cellId = asyncCfm->cellId;
            cfgCfm->numEnt = asyncCfm->numEnt;
            for ( idx = 0; idx < asyncCfm->numEnt; idx++ )
            {
               cfgCfm->cfmEnt[idx].status = asyncCfm->cfmEnt[idx].status;
               cfgCfm->cfmEnt[idx].reason = asyncCfm->cfmEnt[idx].reason;
               cfgCfm->cfmEnt[idx].rbId = asyncCfm->cfmEnt[idx].rbId;
               cfgCfm->cfmEnt[idx].rbType = asyncCfm->cfmEnt[idx].rbType;
            }


            { U16 _idx; if(ueCb->libInfo.crntTmrTxId == txIdx) { pjStopTmr(gCb,(U32)ueCb, 0x15); } if(pjChkTmr(gCb,(U32)ueCb, 0x15) == 0) { for(_idx = 0; _idx < (2 - 1) ; _idx++) { ueCb->libInfo.crntTmrTxId = (U16)((ueCb->libInfo.crntTmrTxId + 1) % 2); if((ueCb->libInfo.asyncCfm[ueCb->libInfo.crntTmrTxId] != 0L) && (ueCb->libInfo.asyncCfm[ueCb->libInfo.crntTmrTxId]->startTmr == 1)) { pjStartTmr(gCb,(U32)ueCb, 0x15); break; } } } };
            { { if (ueCb->libInfo.asyncCfm[txIdx] != 0L) { (Void) SPutSBuf(gCb->init.region, gCb->init.pool, (Data *) ueCb->libInfo.asyncCfm[txIdx], (Size) sizeof(PjAsyncCfm)); ueCb->libInfo.asyncCfm[txIdx] = 0L; } }; ueCb->libInfo.asyncCfm[txIdx]=0L; if(ueCb->libInfo.nxtAvlbTxId == 2) { ueCb->libInfo.nxtAvlbTxId = txIdx; } };


            PjUiCpjCfgCfm(&(gCb->u.ulCb->cpjSap.pst), gCb->u.ulCb->cpjSap.suId, cfgCfm);
         }
      }
   return(0);
}
