static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_MODULE_ID=4096;
static int RLOG_FILE_ID=178;





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
typedef enum
{
   RG_DIAG_NA
} RgDiagSplArg;



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
typedef struct crgCfgTransId
{
   U8 trans[12];
} CrgCfgTransId;



typedef struct crgBwCfg
{
   U8 dlTotalBw;
   U8 ulTotalBw;
} CrgBwCfg;



typedef struct crgRachCfg
{
   U8 maxMsg3Tx;
} CrgRachCfg;
typedef struct crgCellCfg
{
   CmLteCellId cellId;
   CrgRachCfg rachCfg;
   CrgBwCfg bwCfg;

   SpId rguUlSapId;
   SpId rguDlSapId;

} CrgCellCfg;



typedef struct crgUeUlHqCfg
{
   U8 maxUlHqTx;
} CrgUeUlHqCfg;





typedef enum crgTxMode
{
   CRG_UE_TM_1 = 1,
   CRG_UE_TM_2,
   CRG_UE_TM_3,
   CRG_UE_TM_4,
   CRG_UE_TM_5,
   CRG_UE_TM_6,
   CRG_UE_TM_7
} CrgTxMode;



typedef struct crgTxModeCfg
{
   Bool pres;
   CrgTxMode tm;
}CrgTxModeCfg;


typedef struct crgUeCfg
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   CrgUeUlHqCfg ueUlHqCfg;
   CrgTxModeCfg txMode;

   SpId rguUlSapId;
   SpId rguDlSapId;







} CrgUeCfg;



typedef struct crgDlLchCfg
{
   U8 dlTrchType;





} CrgDlLchCfg;



typedef struct crgUlLchCfg
{
   U8 ulTrchType;




   U8 lcgId;
} CrgUlLchCfg;




typedef struct crgLchCfg
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   CmLteLcId lcId;
   CmLteLcType lcType;






   U8 dir;





   CrgDlLchCfg dlInfo;
   CrgUlLchCfg ulInfo;






} CrgLchCfg;



typedef struct crgCfg
{
   U8 cfgType;
   union crgCfgU
   {
      CrgCellCfg cellCfg;
      CrgUeCfg ueCfg;
      CrgLchCfg lchCfg;
   } u;
} CrgCfg;




typedef struct crgActvTime
{
   Bool pres;
   CmLteTimingInfo actvTime;
} CrgActvTime;




typedef struct crgCellRecfg
{
   CmLteCellId cellId;
   CrgRachCfg rachRecfg;
} CrgCellRecfg;



typedef struct crgUeRecfg
{
   CmLteCellId cellId;
   CmLteRnti oldCrnti;
   CmLteRnti newCrnti;


   CrgUeUlHqCfg ueUlHqRecfg;
   CrgTxModeCfg txMode;




} CrgUeRecfg;



typedef struct crgLchRecfg
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   CmLteLcId lcId;

   struct ulRecfgS
   {
      U8 lcgId;
   } ulRecfg;

} CrgLchRecfg;



typedef struct crgRecfg
{
   U8 recfgType;
   union crgRecfgU
   {
      CrgCellRecfg cellRecfg;
      CrgUeRecfg ueRecfg;
      CrgLchRecfg lchRecfg;
   } u;

} CrgRecfg;



typedef struct crgDel
{
   U8 delType;
   union crgDelU
   {
      struct cellDelS
      {
         CmLteCellId cellId;
      } cellDel;

      struct ueDelS
      {
         CmLteCellId cellId;
         CmLteRnti crnti;
      } ueDel;

      struct lchDelS
      {
         CmLteCellId cellId;
         CmLteRnti crnti;
         CmLteLcId lcId;
         U8 dir;




      } lchDel;
   } u;
} CrgDel;



typedef struct crgRst
{
   CmLteCellId cellId;
   CmLteRnti crnti;
} CrgRst;


typedef struct crgCfgReqInfo
{
   U8 action;
   union cfgReqInfoU
   {
      CrgCfg cfgInfo;
      CrgRecfg recfgInfo;
      CrgDel delInfo;
      CrgRst rstInfo;
   } u;
} CrgCfgReqInfo;





typedef S16 (*CrgBndReq) ( Pst* pst, SuId suId, SpId spId)


                              ;


typedef S16 (*CrgBndCfm) ( Pst* pst, SuId suId, U8 status)


                                ;

typedef S16 (*CrgUbndReq) ( Pst* pst, SpId spId, Reason reason)


                                ;


typedef S16 (*CrgCfgReq) ( Pst* pst, SpId spId, CrgCfgTransId transId, CrgCfgReqInfo * cfgReqInfo)



                                    ;

typedef S16 (*CrgCfgCfm) ( Pst* pst, SuId suId, CrgCfgTransId transId, U8 status)



                                ;


extern S16 RgUiCrgBndReq ( Pst* pst, SuId suId, SpId spId )



  ;


extern S16 RgUiCrgBndCfm ( Pst* pst, SuId suId, U8 status )



  ;

extern S16 RgUiCrgUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;


extern S16 RgUiCrgCfgReq ( Pst* pst, SpId spId, CrgCfgTransId transId, CrgCfgReqInfo * cfgReqInfo )




  ;

extern S16 RgUiCrgCfgCfm ( Pst* pst, SuId suId, CrgCfgTransId transId, U8 status )




  ;
extern S16 cmPkCrgBndReq ( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 cmUnpkCrgBndReq ( CrgBndReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkCrgBndCfm ( Pst* pst, SuId suId, U8 status )



  ;


extern S16 cmUnpkCrgBndCfm ( CrgBndCfm func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCrgUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;

extern S16 cmUnpkCrgUbndReq ( CrgUbndReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkCrgCfgReq ( Pst* pst, SpId spId, CrgCfgTransId transId, CrgCfgReqInfo * cfgReqInfo )




  ;


extern S16 cmUnpkCrgCfgReq ( CrgCfgReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkCrgCfgCfm ( Pst* pst, SuId suId, CrgCfgTransId transId, U8 status )




  ;

extern S16 cmUnpkCrgCfgCfm ( CrgCfgCfm func, Pst* pst, Buffer *mBuf )



  ;
extern S16 cmPkCrgCfgTransId ( CrgCfgTransId *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgCfgTransId ( CrgCfgTransId *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgBwCfg ( CrgBwCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgBwCfg ( CrgBwCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgRachCfg ( CrgRachCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgRachCfg ( CrgRachCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgCellCfg ( CrgCellCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgCellCfg ( CrgCellCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgUeUlHqCfg ( CrgUeUlHqCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgUeUlHqCfg ( CrgUeUlHqCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgUeCfg ( CrgUeCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgUeCfg ( CrgUeCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgDlLchCfg ( CrgDlLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgDlLchCfg ( CrgDlLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgUlLchCfg ( CrgUlLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgUlLchCfg ( CrgUlLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgLchCfg ( CrgLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgLchCfg ( CrgLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgCfg ( CrgCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgCfg ( CrgCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgActvTime ( CrgActvTime *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgActvTime ( CrgActvTime *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgCellRecfg ( CrgCellRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgCellRecfg ( CrgCellRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgUeRecfg ( CrgUeRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgUeRecfg ( CrgUeRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgLchRecfg ( CrgLchRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgLchRecfg ( CrgLchRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgRecfg ( CrgRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgRecfg ( CrgRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgDel ( CrgDel *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgDel ( CrgDel *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgRst ( CrgRst *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgRst ( CrgRst *param, Buffer *mBuf )


  ;
extern S16 cmPkCrgCfgReqInfo ( CrgCfgReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkCrgCfgReqInfo ( CrgCfgReqInfo *param, Buffer *mBuf )


  ;
typedef struct rgGenCfg
{
   Pst lmPst;
   MemoryId mem;
   U8 tmrRes;
   U8 numRguSaps;
   U8 startCellId;







}RgGenCfg;




typedef struct rgUpSapCfg
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
}RgUpSapCfg;




typedef struct rgLowSapCfg
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
   TmrCfg bndTmr;
}RgLowSapCfg;
typedef struct rgGenSts
{
   U32 numHarqFail;
   U32 numUeCfg;
   U16 numCellCfg;




}RgGenSts;




typedef struct rgSapSts
{
   U32 numPduRcvd;

   U32 numPduTxmit;

   U32 numPduDrop;

}RgSapSts;

typedef struct rgSchInstCfg
{
   U8 instId;
   RgGenCfg genCfg;
   U8 numSaps;
   RgUpSapCfg rgrSap[2];
   RgUpSapCfg rgmSap[2];
   RgLowSapCfg tfuSap[2];
} RgSchInstCfg;




typedef struct rgCfg
{
   union
   {
      RgGenCfg genCfg;

      RgUpSapCfg rguSap;
      RgUpSapCfg crgSap;
      RgLowSapCfg tfuSap;
      RgSchInstCfg schInstCfg;
   }s;
}RgCfg;




typedef struct rgSapSta
{
   U8 sapState;
}RgSapSta;




typedef struct rgSts
{
   DateTime dt;
   U8 sapInst;
   Action action;

   union
   {
      RgGenSts genSts;
      RgSapSts rguSts;
      RgSapSts crgSts;
      RgSapSts rgrSts;
      RgSapSts tfuSts;
   }s;
}RgSts;




typedef struct rgSsta
{
   DateTime dt;
   U8 sapInst;
   union
   {
      SystemId sysId;
      RgSapSta rguSapSta;
      RgSapSta crgSapSta;
      RgSapSta rgrSapSta;
      RgSapSta rgmSapSta;
      RgSapSta tfuSapSta;
   }s;
}RgSsta;




typedef struct rgUstaDgn
{
   U8 type;
   union
   {

      MemoryId mem;



   }u;
} RgUstaDgn;




typedef struct rgUsta
{
   CmAlarm cmAlarm;
   RgUstaDgn dgn;
}RgUsta;




typedef struct rgTrc
{
   DateTime dt;

   U8 evnt;



}RgTrc;




typedef struct rgDbgCntrl
{
   U32 dbgMask;





}RgDbgCntrl;




typedef struct rgSapCntrl
{
   SuId suId;
   SpId spId;
}RgSapCntrl;
typedef struct rgCntrl
{
   DateTime dt;
   U8 action;
   U8 subAction;
   U8 instId;
   union
   {
      RgDbgCntrl rgDbgCntrl;

      S16 trcLen;




      RgSapCntrl rgSapCntrl;
      U32 logMask;



   }s;
}RgCntrl;




typedef struct rgMngmt
{
   Header hdr;
   CmStatus cfm;
   union
   {
      RgCfg cfg;
      RgSts sts;
      RgSsta ssta;
      RgUsta usta;
      RgTrc trc;
      RgCntrl cntrl;
   }t;
}RgMngmt;
typedef S16 (*LrgCfgReq) ( Pst *pst, RgMngmt *cfg )


       ;

typedef S16 (*LrgSchCfgReq) ( Pst *pst, RgMngmt *cfg )


       ;

typedef S16 (*LrgCfgCfm) ( Pst *pst, RgMngmt *cfg )


       ;

typedef S16 (*LrgSchCfgCfm) ( Pst *pst, RgMngmt *cfg )


       ;

typedef S16 (*LrgCntrlReq) ( Pst *pst, RgMngmt *cntrl )


       ;

typedef S16 (*LrgSchCntrlReq) ( Pst *pst, RgMngmt *cntrl )


       ;

typedef S16 (*LrgCntrlCfm) ( Pst *pst, RgMngmt *cntrl )


       ;

typedef S16 (*LrgSchCntrlCfm) ( Pst *pst, RgMngmt *cntrl )


       ;
typedef S16 (*LrgStaReq) ( Pst *pst, RgMngmt *sta )


       ;

typedef S16 (*LrgStaCfm) ( Pst *pst, RgMngmt *sta )


       ;

typedef S16 (*LrgStaInd) ( Pst *pst, RgMngmt *sta )


       ;

typedef S16 (*LrgSchStaInd) ( Pst *pst, RgMngmt *sta )


       ;

typedef S16 (*LrgStsReq) ( Pst *pst, RgMngmt *sts )


       ;

typedef S16 (*LrgStsCfm) ( Pst *pst, RgMngmt *sts )


       ;

typedef S16 (*LrgTrcInd) ( Pst *pst, RgMngmt *trc, Buffer *mBuf )



       ;
extern S16 RgMiLrgCfgReq (Pst *pst, RgMngmt *cfg);
extern S16 RgMiLrgCfgCfm (Pst *pst, RgMngmt *cfm);
extern S16 RgMiLrgSchCfgReq (Pst *pst, RgMngmt *cfg);
extern S16 RgMiLrgSchCfgCfm (Pst *pst, RgMngmt *cfm);
extern S16 RgMiLrgStsReq (Pst *pst, RgMngmt *sts);
extern S16 RgMiLrgStsCfm (Pst *pst, RgMngmt *cfm);
extern S16 RgMiLrgStaReq (Pst *pst, RgMngmt *sta);
extern S16 RgMiLrgStaCfm (Pst *pst, RgMngmt *cfm);
extern S16 RgMiLrgStaInd (Pst *pst, RgMngmt *usta);
extern S16 RgMiLrgSchStaInd (Pst *pst, RgMngmt *usta);
extern S16 RgMiLrgCntrlReq (Pst *pst, RgMngmt *cntrl);
extern S16 RgMiLrgCntrlCfm ( Pst *pst, RgMngmt *cfm);
extern S16 RgMiLrgSchCntrlReq (Pst *pst, RgMngmt *cntrl);
extern S16 RgMiLrgSchCntrlCfm ( Pst *pst, RgMngmt *cfm);
extern S16 RgMiLrgTrcInd (Pst *pst, RgMngmt *trc, Buffer *mBuf);
extern S16 cmPkLrgCfgReq ( Pst * pst, RgMngmt * cfg )


  ;


extern S16 cmUnpkLrgCfgReq ( LrgCfgReq func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgSchCfgReq ( Pst * pst, RgMngmt * cfg )


  ;


extern S16 cmUnpkLrgSchCfgReq ( LrgSchCfgReq func, Pst * pst, Buffer *mBuf )



  ;
extern S16 cmPkLrgCfgCfm ( Pst * pst, RgMngmt * cfm )


  ;


extern S16 cmUnpkLrgCfgCfm ( LrgCfgCfm func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgSchCfgCfm ( Pst * pst, RgMngmt * cfg )


  ;


extern S16 cmUnpkLrgSchCfgCfm ( LrgSchCfgCfm func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgStsReq ( Pst * pst, RgMngmt * sts )


  ;


extern S16 cmUnpkLrgStsReq ( LrgStsReq func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgStsCfm ( Pst * pst, RgMngmt * cfm )


  ;


extern S16 cmUnpkLrgStsCfm ( LrgStsCfm func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgStaReq ( Pst * pst, RgMngmt * sta )


  ;


extern S16 cmUnpkLrgStaReq ( LrgStaReq func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgStaCfm ( Pst * pst, RgMngmt * cfm )


  ;


extern S16 cmUnpkLrgStaCfm ( LrgStaCfm func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgStaInd ( Pst * pst, RgMngmt * usta )


  ;


extern S16 cmUnpkLrgStaInd ( LrgStaInd func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgSchStaInd ( Pst * pst, RgMngmt * sta )


  ;


extern S16 cmUnpkLrgSchStaInd ( LrgSchStaInd func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgCntrlReq ( Pst * pst, RgMngmt * cntrl )


  ;


extern S16 cmUnpkLrgCntrlReq ( LrgCntrlReq func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgSchCntrlReq ( Pst * pst, RgMngmt * cntrl )


  ;


extern S16 cmUnpkLrgSchCntrlReq ( LrgSchCntrlReq func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgCntrlCfm ( Pst * pst, RgMngmt * cfm )


  ;


extern S16 cmUnpkLrgCntrlCfm ( LrgCntrlCfm func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgSchCntrlCfm ( Pst * pst, RgMngmt * cntrl )


  ;


extern S16 cmUnpkLrgSchCntrlCfm ( LrgSchCntrlCfm func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrgTrcInd ( Pst * pst, RgMngmt * trc, Buffer * trcBuf )



  ;


extern S16 cmUnpkLrgTrcInd ( LrgTrcInd func, Pst * pst, Buffer *mBuf )



  ;
extern S16 cmPkRgGenCfg ( RgGenCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgGenCfg ( RgGenCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgUpSapCfg ( RgUpSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgUpSapCfg ( RgUpSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgLowSapCfg ( RgLowSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgLowSapCfg ( RgLowSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgGenSts ( RgGenSts *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgGenSts ( RgGenSts *param, Buffer *mBuf )


  ;
extern S16 cmPkRgSapSts ( RgSapSts *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgSapSts ( RgSapSts *param, Buffer *mBuf )


  ;
extern S16 cmPkRgSchInstCfg ( RgSchInstCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgSchInstCfg ( RgSchInstCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgCfg ( RgCfg *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkRgCfg ( RgCfg *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmPkRgSapSta ( RgSapSta *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgSapSta ( RgSapSta *param, Buffer *mBuf )


  ;
extern S16 cmPkRgSts ( RgSts *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkRgSts ( RgSts *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmPkRgSsta ( Pst *pst, RgSsta *param, S16 elmnt, Buffer *mBuf )




  ;

extern S16 cmUnpkRgSsta ( Pst *pst, RgSsta *param, S16 elmnt, Buffer *mBuf )




  ;
extern S16 cmPkRgUstaDgn ( RgUstaDgn *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgUstaDgn ( RgUstaDgn *param, Buffer *mBuf )


  ;
extern S16 cmPkRgUsta ( RgUsta *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgUsta ( RgUsta *param, Buffer *mBuf )


  ;
extern S16 cmPkRgTrc ( RgTrc *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgTrc ( RgTrc *param, Buffer *mBuf )


  ;
extern S16 cmPkRgDbgCntrl ( RgDbgCntrl *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgDbgCntrl ( RgDbgCntrl *param, Buffer *mBuf )


  ;
extern S16 cmPkRgSapCntrl ( RgSapCntrl *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgSapCntrl ( RgSapCntrl *param, Buffer *mBuf )


  ;
extern S16 cmPkRgCntrl ( RgCntrl *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkRgCntrl ( RgCntrl *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmPkRgMngmt ( Pst *pst, RgMngmt *param, U8 eventType, Buffer *mBuf )




  ;
extern S16 cmUnpkRgMngmt ( Pst *pst, RgMngmt *param, U8 eventType, Buffer *mBuf )




  ;
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
typedef struct rgInfCmnBoRpt
{
   S16 cellSapId;
   CmLteCellId cellId;
   CmLteLcId lcId;

   CmLteLcType lcType;





   S32 bo;
   union
   {
      CmLteTimingInfo timeToTx;
      CmLteRnti rnti;

   } u;
} RgInfCmnBoRpt;




typedef struct rgInfDedBoRpt
{
   S16 cellSapId;
   CmLteCellId cellId;
   CmLteRnti rnti;
   CmLteLcId lcId;
   S32 bo;

   Bool staPduPrsnt;
   U16 estRlcHdrSz;

   U32 staPduBo;

  U32 oldestSduArrTime;
  Bool setMaxUlPrio;
  Bool setMaxDlPrio;
} RgInfDedBoRpt;






typedef struct rgInfUeDelInd
{
   S16 cellSapId;
   CmLteCellId cellId;
   CmLteRnti rnti;
} RgInfUeDelInd;
typedef struct rgInfRarUlGrnt
{
   U8 hop;
   U8 rbStart;
   U8 numRb;
   U8 tpc;
   U8 iMcsCrnt;
   U8 delayBit;
   U8 cqiBit;
} RgInfRarUlGrnt;




typedef struct rgInfCrntiInfo
{
    CmLteRnti tmpCrnti;
    U8 rapId;
    TknU16 ta;
    RgInfRarUlGrnt grnt;
    Bool isContFree;
}RgInfCrntiInfo;





typedef struct rgInfRaRntiInfo
{
   U16 raRnti;
   TfuPdschDciInfo dciInfo;

   U32 schdTbSz;

   TknU8 backOffInd;

   U8 numCrnti;
   RgInfCrntiInfo *crntiInfo;
}RgInfRaRntiInfo;





typedef struct rgInfRarInfo
{
 U8 numRaRntis;
 RgInfRaRntiInfo *raRntiInfo;
 U16 txPwrOffset;
}RgInfRarInfo;




typedef struct rgInfLcDatInfo
{
   CmLList lchLstEnt;
   U8 lcId;

   U32 numBytes;
} RgInfLcDatInfo;





typedef struct rgInfExtPhrSCellInfo
{
   U8 sCellIdx;
   U8 phr;
   U8 pCmax;
   U8 pBackOff;
}RgInfExtPhrSCellInfo;
typedef struct rgInfExtPhrCEInfo
{
   U8 type2Phr;
   U8 type2PCMax;
   U8 numServCells;
   RgInfExtPhrSCellInfo servCellPhr[8];
}RgInfExtPhrCEInfo;





typedef struct rgInfCeInfo
{
   U16 bitMask;
   struct
   {
      U16 cRnti;
      U8 phr;
      union
      {
         U8 truncBsr;

         U8 shortBsr;

         struct
         {
            U8 bs1;
            U8 bs2;
            U8 bs3;
            U8 bs4;
         }longBsr;
      }bsr;
      RgInfExtPhrCEInfo extPhr;
   } ces;
   U16 spsSduSize;


} RgInfCeInfo;

typedef struct rgInfLcgInfo
{
   U8 lcgId;
   U32 bytesRcvd;
}RgInfLcgInfo;





typedef struct rgInfUeDatInd
{
   CmLteRnti rnti;
   CmLList ueLstEnt;
   RgInfCeInfo ceInfo;
   RgInfLcgInfo lcgInfo[4 - 1];
}RgInfUeDatInd;





typedef struct rgInfSfDatInd
{
   CmMemListCp memCp;
   CmLListCp ueLst;

   U32 qcisUlPrbCnt[4];

   S16 cellSapId;
   CmLteCellId cellId;
   CmLteTimingInfo timingInfo;
}RgInfSfDatInd;






typedef struct rgInfUeTbInfo
{
   Bool disTb;

   Bool isReTx;
   TknU8 ta;






   U8 contResCe;





   U8 numSchLch;

   U32 schdTbSz;
   RgInfLcDatInfo schdDat[10];


} RgInfUeTbInfo;





typedef struct rgLaaTbReqInfo
{
   U8 sMacInstId;
   U8 sCellHqPId;
   U8 tbId;
   U16 hqPStamp;
}RgLaaTbReqInfo;






typedef struct rgInfUeAlloc
{
   CmLteRnti rnti;



   CmLteRnti pdcchRnti;




   TfuPdschDciInfo dciInfo;

   U8 hqProcId;
   S8 tbStrtIdx;
   TknU32 doa;
   TfuTxMode txMode;
   Bool puschRptUsd;

   TfuDlCqiPuschInfo puschPmiInfo;



   U8 nmbOfTBs;
   RgInfUeTbInfo tbInfo[2];


   U8 pa;



   U8 isEnbSFR;






   RgLaaTbReqInfo tbReqInfo;

}RgInfUeAlloc;





typedef struct rgInfUeInfo
{
   U8 numUes;
   RgInfUeAlloc *allocInfo;
}RgInfUeInfo;





typedef struct rgInfBcchInfo
{
   CmLteRnti rnti;
   TfuPdschDciInfo dciInfo;







   Buffer *pdu;

   U16 txPwrOffset;

}RgInfBcchInfo;




typedef struct rgInfPcchInfo
{
   CmLteRnti rnti;
   TfuPdschDciInfo dciInfo;

   CmLteLcId lcId;


   U16 txPwrOffset;

}RgInfPcchInfo;





typedef struct rgInfBchInfo
{




   Buffer *pdu;

}RgInfBchInfo;





typedef struct rgInfCmnLcInfo
{
   U16 bitMask;
   RgInfBchInfo bchInfo;
   RgInfPcchInfo pcchInfo;
   RgInfBcchInfo bcchInfo;
}RgInfCmnLcInfo;
typedef struct rgInfLcInfo
{
   CmLteLcId lcId;
   U32 pktAdmitCnt;
   U32 maxBo4FlowCtrl;
}RgInfLcFlowCntrlInfo;




typedef struct rgInfUeFlowCntrlInfo
{
   CmLteRnti ueId;
   U32 numLcs;
   RgInfLcFlowCntrlInfo lcInfo[10];
}RgInfUeFlowCntrlInfo;


typedef struct rgInfFlowCntrlInfo
{
   U32 numUes;
   RgInfUeFlowCntrlInfo ueFlowCntrlInfo[1];
}RgInfFlowCntrlInfo;



typedef struct rgInfSfAlloc
{
   CmLteCellId cellId;

   CmLteTimingInfo timingInfo;
   RgInfCmnLcInfo cmnLcInfo;
   RgInfRarInfo rarInfo;
   RgInfUeInfo ueInfo;



   RgInfFlowCntrlInfo flowCntrlInfo;
}RgInfSfAlloc;
typedef struct rgInfUeHqInfo
{
   CmLteRnti rnti;

   U8 hqProcId;

   U8 numOfTBs;
   U8 tbId[2];



   U8 status[2];
   U8 rlsOperationType;



   U16 saveId;
} RgInfUeHqInfo;






typedef struct rgInfRlsHqInfo
{
   CmLteCellId cellId;

   U8 numUes;
   RgInfUeHqInfo *ueHqInfo;
}RgInfRlsHqInfo;





typedef struct rgInfRlsRnti
{
   CmLteCellId cellId;

   CmLteRnti rnti;




   Bool ueIdChng;

   CmLteRnti newRnti;



}RgInfRlsRnti;





typedef struct rgInfCellReg
{
   CmLteCellId cellId;
   S16 cellSapId;
   U8 maxDlHqProcPerUe;
}RgInfCellReg;
typedef struct rgInfLcgRegReq
{
   CmLteCellId cellId;
   CmLteRnti crnti;


   U8 lcgId;
   Bool isGbr;
} RgInfLcgRegReq;
typedef struct rgInfSpsLcInfo
{
   CmLteCellId cellId;
   CmLteRnti crnti;


   CmLteRnti spsRnti;

   U8 spsLcCnt;

   U8 spsLcId[10];



   U8 implRelCnt;
   U16 spsPrd;
} RgInfSpsLcInfo;





typedef struct rgInfUlSpsReset
{
   CmLteCellId cellId;
   CmLteRnti crnti;


} RgInfUlSpsReset;




typedef struct rgInfSpsRelInfo
{
   S16 cellSapId;


   CmLteRnti cRnti;
   Bool isExplRel;

} RgInfSpsRelInfo;
extern S16 cmPkSchMacCellRegReq ( Pst* pst, RgInfCellReg* regReq )


  ;

typedef S16 (*CellRegReq) ( Pst* pst, RgInfCellReg* regReq )


  ;
extern S16 RgSchMacCellRegReq ( Pst* pst, RgInfCellReg* regReq )


  ;




extern S16 cmUnpkSchMacCellRegReq ( CellRegReq func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkMacSchDedBoUpdtReq ( Pst* pst, RgInfDedBoRpt* boRpt )


  ;

typedef S16 (*DedBoUpdtReq) ( Pst* pst, RgInfDedBoRpt* boRpt )


  ;
extern S16 RgMacSchDedBoUpdtReq ( Pst* pst, RgInfDedBoRpt* boRpt )


  ;




extern S16 cmUnpkMacSchDedBoUpdtReq ( DedBoUpdtReq func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkMacSchCmnBoUpdtReq ( Pst* pst, RgInfCmnBoRpt* boRpt )


  ;

typedef S16 (*CmnBoUpdtReq) ( Pst* pst, RgInfCmnBoRpt* boRpt )


  ;
extern S16 RgMacSchCmnBoUpdtReq ( Pst* pst, RgInfCmnBoRpt* boRpt )


  ;




extern S16 cmUnpkMacSchCmnBoUpdtReq ( CmnBoUpdtReq func, Pst* pst, Buffer *mBuf )



  ;






extern S16 cmPkMacSchUeDelInd ( Pst* pst, RgInfUeDelInd* ueDelInd )


  ;

typedef S16 (*UeDelInd) ( Pst* pst, RgInfUeDelInd* ueDelInd )


  ;







extern S16 RgMacSchUeDelInd ( Pst* pst, RgInfUeDelInd* ueDelInd )


  ;




extern S16 cmUnpkMacSchUeDelInd ( UeDelInd func, Pst* pst, Buffer *mBuf )



  ;





extern S16 cmPkMacSchSfRecpInd ( Pst* pst, RgInfSfDatInd* datInd )


  ;

typedef S16 (*SfRecpInd) ( Pst* pst, RgInfSfDatInd* datInd )


  ;
extern S16 RgMacSchSfRecpInd ( Pst* pst, RgInfSfDatInd* datInd )


  ;




extern S16 cmUnpkMacSchSfRecpInd ( SfRecpInd func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkSchMacSfAllocReq ( Pst* pst, RgInfSfAlloc* resAllocReq )


  ;

typedef S16 (*SfAllocReq) ( Pst* pst, RgInfSfAlloc* resAllocReq )


  ;







extern S16 RgSchMacSfAllocReq ( Pst* pst, RgInfSfAlloc* resAllocReq )


  ;




extern S16 cmUnpkSchMacSfAllocReq ( SfAllocReq func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkSchMacRlsHqReq ( Pst* pst, RgInfRlsHqInfo* sfHqInfo )


  ;

typedef S16 (*RlsHqReq) ( Pst* pst, RgInfRlsHqInfo* sfHqInfo )


  ;
extern S16 RgSchMacRlsHqReq ( Pst* pst, RgInfRlsHqInfo* sfHqInfo )


  ;





extern S16 cmUnpkSchMacRlsHqReq ( RlsHqReq func, Pst* pst, Buffer *mBuf )



  ;
extern S16 cmPkSchMacRlsRntiReq ( Pst* pst, RgInfRlsRnti* rlsRnti )


  ;

typedef S16 (*RlsRntiReq) ( Pst* pst, RgInfRlsRnti* rlsRnti )


  ;






extern S16 RgSchMacRlsRntiReq ( Pst* pst, RgInfRlsRnti* rlsRnt )


  ;




extern S16 cmUnpkSchMacRlsRntiReq ( RlsRntiReq func, Pst* pst, Buffer *mBuf )



  ;


typedef S16 (*LcgReg) ( Pst* pst, RgInfLcgRegReq *lcgRegReq )


  ;

extern S16 cmPkSchMacLcgRegReq ( Pst* pst, RgInfLcgRegReq *lcgRegReq )


  ;

extern S16 RgSchMacLcgRegReq (Pst *pst, RgInfLcgRegReq *lcgRegReq);

extern S16 cmUnpkSchMacLcgRegReq ( LcgReg func, Pst *pst, Buffer *mBuf )



  ;

extern S16 RgSchMacLcgReg (Pst* pst, RgInfLcgRegReq *lcgRegReq);







extern S16 cmPkSchMacSpsLcRegReq ( Pst* pst, RgInfSpsLcInfo *lcInfo )


  ;

typedef S16 (*SpsLcReg) ( Pst* pst, RgInfSpsLcInfo *lcInfo )


  ;






extern S16 RgSchMacSpsLcRegReq (Pst *pst, RgInfSpsLcInfo *lcInfo);

extern S16 cmUnpkSchMacSpsLcRegReq ( SpsLcReg func, Pst *pst, Buffer *mBuf )



  ;






extern S16 cmPkSchMacUlSpsResetReq ( Pst* pst, RgInfUlSpsReset *ulSpsResetInfo )


  ;

typedef S16 (*UlSpsReset) ( Pst* pst, RgInfUlSpsReset *ulSpsResetInfo )


  ;






extern S16 RgSchMacUlSpsResetReq (Pst *pst, RgInfUlSpsReset *ulSpsResetInfo);

extern S16 cmUnpkSchMacUlSpsResetReq ( UlSpsReset func, Pst *pst, Buffer *mBuf )



  ;
extern S16 cmPkSchMacSpsLcDeregReq ( Pst* pst, CmLteCellId cellId, CmLteRnti crnti )



  ;

typedef S16 (*SpsLcDereg) ( Pst* pst, CmLteCellId cellId, CmLteRnti crnti )



  ;






extern S16 RgSchMacSpsLcDeregReq (Pst *pst, CmLteCellId cellId, CmLteRnti crnti)
           ;

extern S16 cmUnpkSchMacSpsLcDeregReq ( SpsLcDereg func, Pst* pst, Buffer *mBuf )



  ;





extern S16 cmPkMacSchSpsRelInd ( Pst* pst, RgInfSpsRelInfo* relInfo )


  ;

typedef S16 (*SpsRelInd) ( Pst* pst, RgInfSpsRelInfo* relInfo )


  ;






extern S16 RgMacSchSpsRelInd (Pst *pst, RgInfSpsRelInfo *relInfo);

extern S16 cmUnpkMacSchSpsRelInd ( SpsRelInd func, Pst* pst, Buffer *mBuf )



  ;
extern S16 RgSchMacRlsRnti (Pst* pst, RgInfRlsRnti* rlsRnti);
extern S16 RgSchMacRlsHq (Pst* pst, RgInfRlsHqInfo* sfHqInfo);
extern S16 RgSchMacSfAlloc (Pst* pst, RgInfSfAlloc* resAllocReq);



extern S16 RgMacSchSfRecp (Pst* pst, RgInfSfDatInd* datInd);
extern S16 RgMacSchCmnBoUpdt ( Pst* pst, RgInfCmnBoRpt* boRpt);
extern S16 RgMacSchDedBoUpdt ( Pst* pst, RgInfDedBoRpt* boRpt);
extern S16 RgSchMacCellReg (Pst* pst,RgInfCellReg* regReq);
extern S16 RgSchMacSpsLcReg (Pst *pst, RgInfSpsLcInfo *lcInfo);
extern S16 RgSchMacUlSpsReset (Pst *pst, RgInfUlSpsReset *lcInfo);
extern S16 RgSchMacSpsLcDereg (Pst *pst, CmLteCellId cellId, CmLteRnti crnti)
           ;
extern S16 RgMacSchSpsRel (Pst *pst, RgInfSpsRelInfo* relInfo);

extern S16 RgMacSchUeDel (Pst* pst, RgInfUeDelInd* ueDelInd);
typedef U8 RgPrgLteLcgId;
typedef struct rgPrgUlLcInfo
{
   CmLteLcId lcId;
   RgPrgLteLcgId lcgId;







}RgPrgUlLcInfo;
typedef struct rgPrgLcgInfo
{


   RgPrgLteLcgId lcgId;
   U8 lcCount;
   Bool isGbr;
}RgPrgLcgInfo;







typedef struct rgPrgDlLcInfo
{
   CmLteLcId lcId;
}RgPrgDlLcInfo;
typedef RgPrgLteLcgId LteLcgId;
typedef RguDDatReqInfo RgRguDedDatReq;
typedef RguCDatReqInfo RgRguCmnDatReq;
typedef RguDStaRspInfo RgRguDedStaRsp;
typedef RguCStaRspInfo RgRguCmnStaRsp;
typedef RguDStaIndInfo RgRguDedStaInd;
typedef RguCStaIndInfo RgRguCmnStaInd;
typedef RguDDatIndInfo RgRguDedDatInd;
typedef RguCDatIndInfo RgRguCmnDatInd;
typedef RguLchStaInd RgRguLcStaInd;
typedef TfuPdschDciInfo RgTfuPdschDciInfo;
typedef TfuDatReqInfo RgTfuDatReqInfo;
typedef TfuDatReqPduInfo RgTfuDatReqPduInfo;
typedef RguDDatReqPerUe RgRguDDatReqPerUe;
typedef struct rgUeCb RgUeCb;
typedef struct rgErrInfo RgErrInfo;
typedef struct rgCellCb RgCellCb;
typedef struct rgUlHqProcCb RgUlHqProcCb;
typedef struct rgDlHqProcCb RgDlHqProcCb;
typedef struct rgLcgCb RgLcgCb;
typedef struct rgDlHqEnt RgDlHqEnt;
typedef struct _rgCb RgCb;
typedef RgPrgUlLcInfo RgUlLcCb;
typedef RgPrgDlLcInfo RgDlLcCb;
typedef struct rgPdcch {
   CmLteRnti rnti;
   RgTfuPdschDciInfo dci;
} RgPdcch;

typedef struct rgBcchTb
{
   RgPdcch pdcch;
   Buffer *tb;
   U16 txPwrOffset;
} RgBcchTb;

typedef struct rgPcchTb
{
   RgPdcch pdcch;
   Buffer *tb;
   U16 txPwrOffset;
} RgPcchTb;

typedef struct rgRaRspAlloc
{
   RgPdcch pdcch;
   Buffer *rar;
   U16 txPwrOffset;
}RgRaRspAlloc;

typedef struct rgBchTb
{
   Buffer *tb;
}RgBchTb;

typedef struct rgDlSf
{
   CmLteTimingInfo schdTime;
   Bool txDone;


   U8 remDatReqCnt;


   Bool statIndDone;

   RgBchTb bch;
   RgBcchTb bcch;
   RgPcchTb pcch;
   CmLListCp tbs;
   U8 numRaRsp;
   RgRaRspAlloc raRsp[60];

   U8 numTbReqsSent;

} RgDlSf;





typedef struct rgBcchDlschLcCb
{
   CmLteLcId lcId;
   Buffer *tb;
} RgBcchDlschLcCb;

typedef struct rgBcchBchLcCb
{
   CmLteLcId lcId;
} RgBcchBchLcCb;

typedef struct rgPcchLcCb
{
   CmLteLcId lcId;
} RgPcchLcCb;





typedef struct rgRaInfoCb
{
   CmLListCp ueRachLst;
} RgRaInfoCb;

typedef struct rgSchInstMap
{
   S16 cellSapId;
   Inst schInst;
} RgSchInstMap;





typedef struct rgUpSapCfgInfo
{
   Pst sapPst;
   SpId spId;
   SuId suId;
}RgUpSapCfgInfo;





typedef struct rgLowSapCfgInfo
{
   Pst sapPst;
   SpId spId;
   SuId suId;
   TmrCfg bndTmr;
}RgLowSapCfgInfo;





typedef struct rgUpSapCb
{
   RgUpSapCfgInfo sapCfg;
   RgSapSts sapSts;
   RgSapSta sapSta;
}RgUpSapCb;





typedef struct rgLowSapCb
{
   RgLowSapCfgInfo sapCfg;
   RgSapSts sapSts;
   RgSapSta sapSta;
   U8 numBndRetries;
}RgLowSapCb;


typedef struct rgLaaTbReq
{
   CmMemListCp *memCp;
   CmLListCp laaTbInfoLst;
} RgLaaTbReq;
typedef struct rgLaaTbInfo
{
   CmLList lnk;
   U8 sCellHqProcId;
   U8 pCellHqProcId;
   CmLteTimingInfo timingInfo;
   U16 saveId;
   U8 tbId;
   CmLteRnti rnti;
   U8 nmbOfTBs;
} RgLaaTbInfo;

typedef struct RgMUXSubHdr
{
   U8 shLen;
   U8 shData[3];
} RgMUXSubHdr;






struct rgCellCb
{
   CmHashListEnt cellLstEnt;
   RgSchInstMap schInstMap;
   CmLteCellId cellId;
   CmLteTimingInfo crntTime;
   U8 maxDlHqProcPerUe;
   CrgBwCfg bwCfg;
   CrgRachCfg rachCfg;

   RgUpSapCb *rguDlSap;
   RgUpSapCb *rguUlSap;
   Inst macInst;
   U8 cellActvState;


   CmLteLcId ulCcchId;
   CmLteLcId dlCcchId;
   RgBcchBchLcCb bcchBchInfo;

   RgPcchLcCb pcchInfo;
   U8 numBcchDlschInfo;
   RgBcchDlschLcCb bcchDlschInfo[2];

   CmHashListCp ueLst;



   CmHashListCp spsUeLst;


   RgRaInfoCb raInfo;

   RgDlSf subFrms[10];
   RguFlowCntrlInd *flowCntrlInd;

   U32 qcisUlPrbCnt[4];





};





typedef struct rgUlHqEnt
{
   U8 maxHqRetx;

} RgUlHqEnt;
struct rgLcgCb
{


   LteLcgId lcgId;
   U8 lcCount;





   Bool isGbr;
};
typedef struct rgUeUlCb
{
   RgUlHqEnt hqEnt;
   RgUlLcCb lcCb[10];

   RgLcgCb lcgArr[4];


   Bool spsLcId[10];
   U8 implRelCntr;

   U8 implRelCnt;

   U8 explRelCntr;
   U8 explRelCnt;

   U8 spsDatRcvd;

   U32 totSpsDatRcvd;


} RgUeUlCb;





typedef struct rgLchSchdData
{
   CmLteLcId lcId;
   U32 schdSz;
} RgLchSchdData;





typedef struct RgContResId
{
   U8 resId[6];
}RgContResId;




typedef struct rgTbInfo{
   U8 numSchLch;
   RgLchSchdData schdData[10];
   TknU8 schdTa;

   U8 contResCe;

   RgContResId *contResId;

   Buffer *tb;
   U32 tbSz;
   RgPdcch pdcch;
   CmLList sfLnk;
   RgDlSf *sf;
   CmLteTimingInfo timingInfo;
   TknU32 doa;
   TfuTxMode txMode;
   Bool puschRptUsd;

   TfuDlCqiPuschInfo puschPmiInfo;



   U8 pa;




   U8 isEnbSFR;




}RgTbInfo;





struct rgDlHqProcCb
{
   U8 procId;


   U8 numOfTBs;
   RgTbInfo tbInfo[2];
   U16 saveId;







};






typedef struct rgDlSavedHqProcInfo
{
   CmLList savedHqPLnk;
   U16 saveId;

   Buffer *tb[2];



}RgDlSavedHqProcInfo;





struct rgDlHqEnt
{
   U8 numHqProcs;
   RgDlHqProcCb *procs[8];
   CmLListCp savedProcLst[8];
};







typedef struct rgUeDlCb
{
   RgDlHqEnt hqEnt;
   RgDlLcCb lcCb[10];

} RgUeDlCb;
struct rgUeCb
{
   CmHashListEnt ueLstEnt;


   CmHashListEnt spsUeLstEnt;

   CmLList rachLstEnt;
   CmLteRnti ueId;


   CmLteRnti spsRnti;

   RgContResId contResId;
   RgUeUlCb ul;
   RgUeDlCb dl;


   CrgTxMode txMode;
   RgUpSapCb *rguDlSap;
   RgUpSapCb *rguUlSap;




};






typedef struct rgLmResponse
{
   TranId transId;
   Resp response;
}RgLmResponse;





typedef struct rgGenCb
{
   U8 tmrRes;
   RgLmResponse trcResp;
   RgLmResponse ustaResp;
   RgLmResponse bndCfmResp;
   Status memUpperThr;
   Status memLowerThr;
}RgGenCb;







struct _rgCb
{
   TskInit rgInit;
   S16 trcLen;
   RgGenCb genCfg;
   U8 numRguSaps;
   RgUpSapCb *rguSap;
   RgUpSapCb crgSap;
   RgLowSapCb tfuSap;
   RgGenSts genSts;
   CmTqCp tmrTqCp;
   CmTqType tmrTq[10];
   CmTimer tmrBlk[1];
   RgCellCb *inactiveCell;
   RgCellCb *cell;
   RgCellCb *prevCell;
   U8 bufCnt;
   Buffer *bufToFree[32];
};


extern RgCb rgCb[2];




typedef struct rgMacCeSubHdr
{
   CmLList subHdrLstEnt;
   CmLteLcId lcId;
} RgMacCeSubHdr;





typedef struct rgMacSdu
{
   CmLList sduLstEnt;
   CmLteLcId lcId;
   U16 len;
   Buffer *mBuf;
} RgMacSdu;





typedef struct rgMacPdu
{
   CmMemListCp memCp;
   CmLListCp ceLst;
   CmLListCp sduLst;
} RgMacPdu;





struct rgErrInfo
{
   U8 errType;
   U16 errCause;
};





typedef struct rgBldPduInfo
{
   Void *datReq;
   U8 reqType;
   MsgLen schdTbSz;
   U8 tbIndex;
   TknU8 ta;
   RgContResId *contResId;



} RgBldPduInfo;
extern S16 rgLIMTfuBndReq ( Inst inst, SuId suId, SpId spId)


                                    ;

extern S16 rgLIMTfuUbndReq ( Inst inst, SuId suId, Reason reason)


                                      ;

extern S16 rgLIMTfuDatReq ( Inst inst, TfuDatReqInfo *datReq)

                                ;



extern S16 rgTOMDatInd ( Inst inst, TfuDatIndInfo *datInd)

                                ;

extern S16 rgTOMTtiInd ( Inst inst, TfuTtiIndInfo *ttiInd)

                                ;
extern Void rgTOMRlsSf (Inst inst,RgDlSf *dlSf);

extern S16 rgSchMacSfAllocReq (Pst *pst, RgInfSfAlloc *sfInfo);




extern S16 rgLMMStartTmr (Inst inst,S16 tmrEvnt, U32 tmrVal, U32 cb);
extern S16 rgLMMStopTmr (Inst inst,S16 tmrEvnt, U32 cb);
extern S16 rgLMMTmrExpiry (U32 cb, S16 tmrEvnt);

extern S16 rgLMMStaInd (Inst inst,U16 category, U16 event, U16 cause, RgUstaDgn *dgn);


extern Void rgLMMTrcInd (Inst inst,Buffer *srcMbuf, U8 event);


extern S16 rgLMMBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 rgActvTmr (Ent ent, Inst inst );
extern S16 rgActvInit (Ent entity, Inst inst, Region region, Reason reason)
                              ;
extern S16 rgActvTsk (Pst *pst, Buffer *mBuf);




extern S16 rgCFGVldtCrgCellCfg (Inst inst,CrgCellCfg *cellCfg, RgErrInfo *errInfo);
extern S16 rgCFGVldtCrgUeCfg (Inst inst,CrgUeCfg *ueCfg, RgCellCb **cell, RgErrInfo *errInfo)
                ;
extern S16 rgCFGVldtCrgLcCfg (Inst inst,CrgLchCfg *lcCfg, RgCellCb **cell, RgUeCb **ue, RgErrInfo *errInfo)
                                 ;
extern S16 rgCFGVldtCrgCellRecfg (Inst inst,CrgCellRecfg *cellRecfg, RgCellCb **cell, RgErrInfo *errInfo)
                          ;
extern S16 rgCFGVldtCrgUeRecfg (Inst inst,CrgUeRecfg *ueRecfg, RgCellCb **cell, RgUeCb **ue, RgErrInfo *errInfo)
                                       ;
extern S16 rgCFGVldtCrgLcRecfg (Inst inst,CrgLchRecfg *lcRecfg, RgCellCb **cell, RgUeCb **ue, RgUlLcCb **ulLc, RgErrInfo *errInfo)
                                                        ;
extern S16 rgCFGVldtCrgUeReset (Inst inst,CrgRst *reset,RgCellCb **cell,RgUeCb **ue, RgErrInfo *errInfo)
                               ;

extern S16 rgCFGCrgCellCfg (Inst inst,CrgCellCfg *cellCfg, RgErrInfo *errInfo);
extern S16 rgCFGCrgUeCfg (Inst inst,RgCellCb *cell, CrgUeCfg *ueCfg, RgErrInfo *errInfo)
                ;
extern S16 rgCFGCrgLcCfg (Inst inst,RgCellCb *cell, RgUeCb *ue, CrgLchCfg *lcCfg, RgErrInfo *errInfo,Bool *isCfmRqrd,CrgCfgTransId transId)
                                                                          ;
extern S16 rgCFGCrgCellRecfg (Inst inst,RgCellCb *cell, CrgCellRecfg *cellRecfg, RgErrInfo *errInfo)
                          ;
extern S16 rgCFGCrgUeRecfg (Inst inst,RgCellCb *cell, RgUeCb *ue, CrgUeRecfg *ueRecfg, RgErrInfo *errInfo)
                                    ;
extern S16 rgCFGCrgLcRecfg (Inst inst,RgCellCb *cell, RgUeCb *ue, RgUlLcCb *ulLc, CrgLchRecfg *lcRecfg, RgErrInfo *errInfo, Bool *isCfmRqrd)
                                                                        ;
extern S16 rgCFGCrgCellDel (Inst inst,CrgDel *cellDelInfo, RgErrInfo *errInfo);
extern S16 rgCFGCrgUeDel (Inst inst,CrgDel *ueDelInfo, RgErrInfo *errInfo);
extern S16 rgCFGCrgLcDel (Inst inst,CrgDel *lcDelInfo, RgErrInfo *errInfo,Bool *isCfmRqrd,CrgCfgTransId transId)
                                                         ;
extern Void rgCFGFreeCellCb (RgCellCb *cell);
extern Void rgCFGFreeInactvCellCb (RgCellCb *cell);
extern S16 rgSchMacCellRegReq (Pst* pst,RgInfCellReg* regReq);
extern S16 rgCFGCrgUeReset (RgCellCb *cell,RgUeCb *ue,CrgRst *reset, RgErrInfo *errInfo)
                             ;




extern S16 rgCOMCfgReq (Inst inst,CrgCfgTransId transId, CrgCfgReqInfo *cfgReqInfo)
                      ;


extern S16 rgUIMRguBndCfm (Inst inst,SuId suId, U8 status);
extern S16 rgUIMSndDedStaInd (Inst inst,RgUpSapCb *rguDlSap,RgRguDedStaInd *staInd);
extern S16 rgUIMSndCmnStaInd (Inst inst,RgUpSapCb *rguDlSap,RgRguCmnStaInd *staInd);
extern S16 rgUIMSndDedDatInd (Inst inst,RgUpSapCb *rguDlSap,RgRguDedDatInd *datInd);
extern S16 rgUIMSndCmnDatInd (Inst inst,RgUpSapCb *rguSap,RgRguCmnDatInd *datInd);
extern S16 rgUIMCrgBndCfm (Inst inst,SuId suId,U8 status);
extern S16 rgUIMCrgCfgCfm (Inst inst,CrgCfgTransId transId,U8 status);





extern S16 rgROMDedDatReq (Inst inst,RgRguDedDatReq *datReq);
extern S16 rgROMCmnDatReq (Inst inst,RgRguCmnDatReq *datReq);
extern S16 rgROMDedStaRsp (Inst inst,RgRguDedStaRsp *staRsp);
extern S16 rgROMCmnStaRsp (Inst inst,RgRguCmnStaRsp *staRsp);
extern RgUeCb* rgRAMCreateUeCb (RgCellCb *cell, CmLteRnti tmpCrnti,Bool insert, RgErrInfo *err)
                                                                     ;
extern S16 rgRAMFreeCell (RgCellCb *cell);
extern Void rgRAMFreeUeCb (Inst inst,RgUeCb *ueCb);
extern S16 rgHndlRaResp (RgCellCb *cell,CmLteTimingInfo timingInfo, RgInfRarInfo *rarInfo,RgErrInfo *err)
                                                   ;
extern S16 rgSchMacRlsRntiReq (Pst *pst,RgInfRlsRnti* rlsRnti);



extern Void rgUHMCrgUeCfg ( RgCellCb *cellCb, RgUeCb *ueCb, CrgUeCfg *ueCfg)
                                                  ;
extern Void rgUHMCrgUeRecfg ( RgCellCb *cellCb, RgUeCb *ueCb, CrgUeRecfg *ueRecfg)
                                                   ;



extern S16 rgDUXDemuxData (Inst inst,RgMacPdu *pdu, RgInfCeInfo *ceInfo, Buffer **mBuf, RgErrInfo *err)
                                                               ;
extern S16 rgDUXExtSduLen ( Inst inst, Buffer *mBuf, U16 *sduLen, RgErrInfo *err )





  ;





extern S16 rgDBMInitInactvCellLst (U16 numBins);
extern S16 rgDBMDeInitInactvCellLst (Void);
extern S16 rgDBMInsInactvCellCb ( RgCellCb *cellCb);
extern RgCellCb* rgDBMGetInactvCellCb ( CmLteCellId cellId);
extern S16 rgDBMDelInactvCellCb ( RgCellCb *cellCb);
extern RgCellCb* rgDBMGetNextInactvCellCb (RgCellCb *cellCb);

extern S16 rgDBMInitCellLst ( U16 numBins);
extern S16 rgDBMDeInitCellLst (Void);
extern S16 rgDBMInsCellCb ( RgCellCb *cellCb);
extern RgCellCb* rgDBMGetCellCb ( CmLteCellId cellId);
extern S16 rgDBMDelCellCb ( RgCellCb *cellCb);
extern RgCellCb* rgDBMGetNextCellCb (RgCellCb *cellCb);
extern S16 rgDBMInitCell (RgCellCb *cellCb);

extern S16 rgDBMDeInitUeCbLst ( RgCellCb *cellCb);
extern S16 rgDBMInsUeCb ( RgCellCb *cellCb, RgUeCb *ueCb);
extern RgUeCb* rgDBMGetUeCb ( RgCellCb *cellCb, CmLteRnti ueId);
extern RgUeCb* rgDBMGetNextUeCb ( RgCellCb *cellCb, RgUeCb *ueCb);
extern S16 rgDBMDelUeCb ( RgCellCb *cellCb, RgUeCb *ueCb);
extern Void rgDBMInitUe (RgUeCb *ueCb);





extern Void rgDBMInsUlDedLcCb (RgUeCb *ueCb, CmLteLcId idx, LteLcgId gId)
                                               ;

extern Void rgDBMUpdUlDedLcCb (RgUeCb *ueCb, RgUlLcCb *ulLcCb, LteLcgId gId)
                                               ;

extern Void rgDBMInsDlDedLcCb (RgUeCb *ueCb, CmLteLcId idx);
extern Void rgDBMDelUlDedLcCb (RgUeCb *ueCb, RgUlLcCb *ulLcCb);
extern Void rgDBMDelDlDedLcCb (RgUeCb *ueCb, RgDlLcCb *dlLcCb);
extern RgDlLcCb* rgDBMGetDlDedLcCb ( RgUeCb *ueCb, CmLteLcId idx);
extern RgUlLcCb* rgDBMGetUlDedLcCb ( RgUeCb *ueCb, CmLteLcId idx);
extern Void rgDBMFreeCmnLcLst (RgCellCb *cellCb);
extern S16 rgDBMChkCmnLcCb ( RgCellCb *cellCb, CmLteLcId lcId);
extern RgBcchBchLcCb* rgDBMGetBcchOnBch ( RgCellCb *cellCb );
extern RgBcchDlschLcCb* rgDBMGetBcchOnDlsch ( RgCellCb *cellCb, CmLteLcId lcId)
                                                                   ;
extern RgPcchLcCb* rgDBMGetPcch ( RgCellCb *cellCb);
extern Void rgDBMInsBcchOnBch ( RgCellCb *cellCb, CmLteLcId idx);
extern Void rgDBMInsBcchOnDlsch ( RgCellCb *cellCb, CmLteLcId idx);
extern Void rgDBMInsPcch ( RgCellCb *cellCb, CmLteLcId idx);

extern Void rgDBMInsUeCbInRachLst (RgCellCb *cellCb,RgUeCb *ueCb);
extern RgUeCb* rgDBMGetUeCbFromRachLst (RgCellCb *cellCb,CmLteRnti key);
extern RgUeCb* rgDBMGetNextUeCbFromRachLst (RgCellCb *cellCb, RgUeCb *ueCb)
                                                                    ;
extern Void rgDBMDelUeCbFromRachLst (RgCellCb *cellCb,RgUeCb *ueCb);


extern S16 rgDBMDeInitSpsUeCbLst (RgCellCb *cellCb);
extern S16 rgDBMInsSpsUeCb (RgCellCb *cellCb, RgUeCb *ueCb);
extern RgUeCb* rgDBMGetSpsUeCb (RgCellCb *cellCb, CmLteRnti ueId);
extern RgUeCb* rgDBMGetNextSpsUeCb (RgCellCb *cellCb, RgUeCb *ueCb);
extern S16 rgDBMDelSpsUeCb (RgCellCb *cellCb,RgUeCb *ueCb);





extern Void rgCFGFreeUeCb (RgCellCb *cell, RgUeCb *ue);
extern S16 rgDHMHqEntInit (Inst inst,RgDlHqEnt *hqE, U8 maxHqProcs);
extern Void rgDHMRlsHqProc (RgDlHqProcCb *hqP);
extern Void rgDHMUeReset (RgCellCb *cell, RgDlHqEnt *hqE);
extern Void rgDHMHdlBufFree (Inst inst, Buffer **mBuf);
extern Void rgDHMFreeTbBufs (Inst inst);
extern S16 rgDHMRlsHqProcTB (RgCellCb *cell, RgDlHqProcCb *hqP,U8 tbIndex);
extern S16 rgDHMGetHqProcFrmId (RgUeCb *ue, U8 idx, RgDlHqProcCb **hqP);


extern S16 rgDHMSndDatReq (RgCellCb *cellCb, RgDlSf *dlSf, RgTfuDatReqInfo *datInfo, RgDlHqProcCb *hqProc, RgErrInfo *err)
                                                                      ;
extern S16 rgDHMHndlDedDatReq (Inst inst,RgDlHqProcCb *hqProc, RgRguDDatReqPerUe *datReq, RgErrInfo *err)
                                                                         ;

extern S16 rgDHMHndlCmnDatReq (Inst inst,RgDlHqProcCb *hqProc, RgRguCmnDatReq *datReq, RgErrInfo *err)
                                                        ;







extern S16 rgDHMSndConsolidatedStaInd (RgCellCb *cell,RgInfUeInfo *ueInfo, CmLteTimingInfo timingInfo, RgErrInfo *err)
                                                  ;


extern Void rgDHMFreeUe (Inst inst,RgDlHqEnt *hqE);
extern S16 rgSchMacRlsHqReq (Pst *pst, RgInfRlsHqInfo *rlshqUeInfo);





extern S16 rgMUXBldPdu (Inst inst, RgBldPduInfo *bldPdu, Buffer **txPdu, RgErrInfo *err)
                         ;





extern S16 rgMUXBldRarPdu (RgCellCb *cell, RgInfRaRntiInfo *alloc, Buffer **txPdu, RgErrInfo *err)
                                         ;




extern S16 rgAllocSBuf (Inst inst,Data **pData, Size size);
extern S16 rgGetMsg (Inst inst,Buffer **mBuf);


extern Void rgFreeSBuf (Inst inst,Data **data, Size size);
extern Void rgFillDgnParams (Inst inst,RgUstaDgn *dgn,U8 dgnType);
extern Void rgUpdtRguDedSts (Inst inst,RgUpSapCb *rguSap,U8 stsType, RgRguDedDatReq *datReq);
extern Void rgUpdtRguCmnSts (Inst inst,RgUpSapCb *rguSap,U8 stsType);
extern Void rgUpdtCellCnt (Inst inst,U8 updtType);
extern Void rgUpdtUeCnt (Inst inst,U8 updtType);
extern Void rgGetPstToInst (Pst *pst,Inst srcInst, Inst dstInst);
extern S16 rgAllocEventMem (Inst inst,Ptr *memPtr,Size memSize);
extern S16 rgGetEventMem (Inst inst,Ptr *ptr,Size len,Ptr memCp);
extern S16 rgAllocShrablSBuf (Inst inst,Data **pData, Size size);
extern Void rgPrintfSubFrameInfo (RgDlSf *dlSf);
extern Void printMacCellInfo (Void);
extern Void rgFreeSharableSBuf (Inst inst,Data **data, Size size);


extern S16 RgSchMacHndlRelReq ( RgCellCb *cell, RgUeCb *ue, RgInfUeHqInfo *ueHqInfo);
extern Void rgDHMFreeSavedHqP ( Inst inst, RgDlHqEnt *hqE, U8 procId);
extern Void rgLaaChkAndReqTbs (RgDlSf *dlSf,RgLaaTbReq** laaCellHqPLst, Inst pMacInst)
                                                   ;
extern Bool rgLaaChkAllRxTbs ( RgDlSf *dlSf )


   ;
extern S16 rgLaaPushHqPToScellLst ( RgInfUeAlloc *allocInfo, RgLaaTbReq** laaCellHqPLst, CmLteTimingInfo timingInfo )




  ;
extern Void rgLaaInitTbInfoLst ( RgLaaTbReq **tbInfoLst )


  ;

extern Void SsRngBufEnable (Void);
extern Void SsRngBufDisable (Void);
extern S16 SCreateSRngBuf (U8 id, Region region, Pool pool, U32 elmSize, U32 rngSize);
extern S16 SDestroySRngBuf (U8 id, Region region, Pool pool);
extern S16 SAttachSRngBuf (U8 id, U32 ent, U32 txRx);
extern S16 SEnqSRngBuf (U8 id, Void* elem);
extern S16 SDeqSRngBuf (U8 id, Void* elem);
extern S16 SPrintSRngStats (Void);
extern S16 pjBatchProc (Void);
extern Void* SRngGetWIndx (U8 rngId);
extern Void* SRngGetRIndx (U8 rngId);
extern Void SRngIncrRIndx (U8 rngId);
extern Void SRngIncrWIndx (U8 rngId);
extern S16 isRngEmpty (U8 rngId);
extern S16 SConnectSRngBuf (U8 id, U32 rxEnt);
extern U32 ssRngBufStatus;
extern S16 SGetNumElemInRng ( U8 id);



typedef struct
{
   U32 size;
   U32 read;
   U32 write;
   U32 type;
   Void* elem;
}SsRngBuf;


typedef struct
{
   U32 rngSize;
   U32 elemSize;
} SsRngCfg;


typedef struct
{
   SsRngBuf* r_addr;
   U32 txEnt;
   U32 rxEnt;
   U32 n_write;
   U32 n_read;
   U32 nReadFail;
   U32 nWriteFail;
   U32 rngState;
   U32 pktDrop;
   U32 nPktProc;
   U32 pktRate;
} SsRngBufTbl;


typedef struct
{
   U16 dlRngBuffCnt;
   U16 ulRngBuffCnt;
}SsRngBufCnt;


typedef enum
{
  SS_RNG_BUF_DEBUG_COUNTER,
  SS_RNG_BUF_ICPU_TO_DLPDCP,
  SS_RNG_BUF_DLPDCP_TO_DLRLC,
  SS_RNG_BUF_L2_RT_TO_FREE_MGR,
  SS_RNG_BUF_L2_NRT_TO_FREE_MGR,
  SS_RNG_BUF_PRC_L1D_TO_CL,
  SS_RNG_BUF_PRC_FREE_TO_CL,
  SS_RNG_BUF_ICPU_TO_DAM,
  SS_RNG_BUF_L2_NRT_DLRLC_TO_FREE_MGR,
  SS_RNG_BUF_ICPU_BATCH_START,
  SS_RNG_BUF_ULMAC_TO_ULRLC,
  SS_RNG_BUF_RX_TO_DLRLC,
  SS_RNG_BUF_RX_TO_ULPDCP,
  SS_RNG_BUF_DL_SMSG_REUSE,
  SS_RNG_BUF_DLRLC_TO_DLMAC,
  SS_RNG_BUF_MAC_HARQ,
  SS_RNG_BUF_MAX
} SsRngBufId;


typedef enum
{
   SS_RBUF_ENT_ICPU,
   SS_RBUF_ENT_DLPDCP,
   SS_RBUF_ENT_DLRLC,
   SS_RBUF_ENT_L2_RT,
   SS_RBUF_ENT_L2_NRT,
   SS_RBUF_ENT_FREE_MGR,
   SS_RBUF_ENT_CL,
   SS_RBUF_ENT_PRC_L1D,
   SS_RBUF_ENT_PRC_FREE,
   SS_RBUF_ENT_DAM





   ,SS_RBUF_ENT_ULPDCP,
   SS_RBUF_ENT_ULMAC,
   SS_RBUF_ENT_ICCRX_DL,
   SS_RBUF_ENT_ULRLC,
   SS_RBUF_ENT_DLRLC_DAT_REQ,
   SS_RBUF_ENT_DLMAC_DAT_REQ,
   SS_RBUF_ENT_DLRLC_STA_RSP,
   SS_RBUF_ENT_DLMAC_STA_RSP,
   SS_RBUF_ENT_MAC_HARQ_STA,
   SS_RBUF_ENT_RLC_HARQ_STA
}SsRngUserEnt;


typedef enum
{
   SS_RNG_DESTROYED,
   SS_RNG_CREATED,
   SS_RNG_TX_ATTACHED,
   SS_RNG_RX_ATTACHED,
   SS_RNG_READY,
   SS_RNG_EMPTY,
   SS_RNG_FULL
}SsRngBufState;


typedef struct
{
  Buffer* mBuf;
} SsRngBufElem;

extern SsRngBufTbl SsRngInfoTbl[SS_RNG_BUF_MAX];
 U8 rgRguDlSap;
 U8 rgRguUlSap;
 S16 RgUiRguBndReq
(
Pst *pst,
SuId suId,
SpId spId
)






{
   Inst inst;
   S16 ret = 0;
   Pst tmpPst;
   RgUstaDgn dgn;

   ;


   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;

   tmpPst.prior = pst->prior;
   tmpPst.route = pst->route;
   tmpPst.selector = pst->selector;
   tmpPst.region = rgCb[inst].rgInit.region;
   tmpPst.pool = rgCb[inst].rgInit.pool;
   tmpPst.srcProcId = rgCb[inst].rgInit.procId;
   tmpPst.srcEnt = rgCb[inst].rgInit.ent;
   tmpPst.srcInst = rgCb[inst].rgInit.inst;
   tmpPst.event = 0x00;
   tmpPst.dstProcId = pst->srcProcId;
   tmpPst.dstEnt = pst->srcEnt;
   tmpPst.dstInst = pst->srcInst;

   if(spId == rgCb[inst].rguSap[spId].sapCfg.spId)
   {

      switch (rgCb[inst].rguSap[spId].sapSta.sapState)
      {
         case 0:
            ;
            rgFillDgnParams(inst,&dgn, 1);
            ret = rgLMMStaInd(inst,2,0,
                  2, &dgn);
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20001, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",156, "SAP Not Configured", RLOG_FILE_ID, RLOG_MODULE_NAME); };
            ret = RgUiRguBndCfm(&tmpPst, suId, 2);
            break;
         case 1:
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20002, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",160, "SAP Not yet bound", RLOG_FILE_ID, RLOG_MODULE_NAME); };
            rgCb[inst].rguSap[spId].sapSta.sapState = 2;
            rgCb[inst].rguSap[spId].sapCfg.suId = suId;


            ret = rgUIMRguBndCfm(inst,spId, 1);

            rgFillDgnParams(inst,&dgn, 1);
            ret = rgLMMStaInd(inst,2,(256 + 0),
                  0, &dgn);
            break;
         case 2:
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20003, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",172, "SAP already bound", RLOG_FILE_ID, RLOG_MODULE_NAME); };

            ret = rgUIMRguBndCfm(inst,spId, 1);
            break;
         default:





            ret = rgUIMRguBndCfm(inst,spId, 2);
            break;
      }
   }
   else
   {





      ret = rgUIMRguBndCfm(inst,spId, 2);
   }
   return(ret);
}
 S16 RgUiRguUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)






{
   Inst inst;
   ;


   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;

   if (spId == rgCb[inst].rguSap[spId].sapCfg.spId)
   {
      switch(rgCb[inst].rguSap[spId].sapSta.sapState)
      {
         case 2:
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20004, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",242, "SAP already bound", RLOG_FILE_ID, RLOG_MODULE_NAME); };

            rgCb[inst].rguSap[spId].sapSta.sapState = 1;
            break;
         default:





            break;
      }
   }
   else
   {




      return(1);
   }
   return(0);
}
 S16 rgUIMRguBndCfm
(
Inst inst,
SpId spId,
U8 status
)






{
   S16 ret = 0;

   ;


   ret = RgUiRguBndCfm(&rgCb[inst].rguSap[spId].sapCfg.sapPst,
                      rgCb[inst].rguSap[spId].sapCfg.suId, status);
   if (ret != 0)
   {

      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20005, L_ERROR, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",307, "RgUiRguBndCfm Failed ", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(ret);
   }
   return(ret);
}
 S16 RgUiRguDDatReq
(
Pst *pst,
SpId spId,
RguDDatReqInfo *datReq
)






{
   S16 ret = 0;
   Inst inst;







   ;


   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;
   ret = rgROMDedDatReq(inst,datReq);
    SPutStaticBuffer(pst->region, pst->pool, (Data *)datReq,sizeof(RguDDatReqInfo), SS_SHARABLE_MEMORY);
   datReq = 0L;
   return(ret);
}
 S16 RgUiRguCDatReq
(
Pst *pst,
SpId spId,
RguCDatReqInfo *datReq
)






{
   Inst inst;
   S16 ret = 0;

   ;


   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;
   ret = rgROMCmnDatReq(inst,datReq);

   if(rgCb[inst].rgInit.trc)
   {
      rgLMMTrcInd(inst,datReq->pdu, 4);
   }
   if (ret == 1)
   {
      { if (datReq != 0L) { { if (0L != (datReq->pdu)) { SPutMsg((datReq->pdu)); datReq->pdu = 0L; } }; }};
   }
   ret = SPutStaticBuffer(pst->region, pst->pool,(Data *)datReq,sizeof(RguCDatReqInfo) , SS_SHARABLE_MEMORY);
   datReq = 0L;
   return(ret);
}
 S16 RgUiRguDStaRsp
(
Pst *pst,
SpId spId,
RguDStaRspInfo *staRsp
)






{
   Inst inst;

   S16 ret = 0;
   volatile U32 startTime = 0;

   ;

   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;

   SStartTask(&startTime, 30203);

   ret = rgROMDedStaRsp(inst,staRsp);
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xb20006,L_ERROR,DBG_CELLID, staRsp->cellId, 0, 0, 0, 0,                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c"      ,                                                      573      , "Processing Of Status Response Failed", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                       ;
   }



   SStopTask(startTime, 30203);
   return(ret);
}
 S16 RgUiRguCStaRsp
(
Pst *pst,
SpId spId,
RguCStaRspInfo *staRsp
)






{
   Inst inst;
   S16 ret = 0;

   ;


   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;
   ret = rgROMCmnStaRsp(inst,staRsp);
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xb20007,L_ERROR,DBG_CELLID, staRsp->cellId, 0, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",657, "Processing Of Status Response Failed", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(ret);
   }

   ret = SPutStaticBuffer(pst->region, pst->pool, (Data *)staRsp,sizeof(RguCStaRspInfo) , SS_SHARABLE_MEMORY);
   staRsp = 0L;
   return(ret);
}
 S16 rgUIMSndDedStaInd
(
Inst inst,
RgUpSapCb *rguSap,
RgRguDedStaInd *staInd
)






{
   S16 ret = 0;

   ;

   ;

   ret = RgUiRguDStaInd(&(rguSap->sapCfg.sapPst), rguSap->sapCfg.suId,
         staInd);
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xb20008,L_ERROR,DBG_CELLID, staInd->cellId, 0, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",792, "RgUiRguDStaInd Failed", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(ret);
   }
   return(ret);
}
 S16 rgUIMSndCmnStaInd
(
Inst inst,
RgUpSapCb *rguDlSap,
RgRguCmnStaInd *staInd
)






{
   S16 ret = 0;


   ;


   ret = RgUiRguCStaInd(&(rguDlSap->sapCfg.sapPst), rguDlSap->sapCfg.suId,
         staInd);
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xb20009,L_ERROR,DBG_CELLID, staInd->cellId, 0, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",841, "RgUiRguCStaInd Failed", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(ret);
   }
   return(ret);
}
 S16 rgUIMSndDedDatInd
(
Inst inst,
RgUpSapCb *rguUlSap,
RgRguDedDatInd *datInd
)






{
   S16 ret = 0;


   ;


   rguUlSap->sapSts.numPduTxmit += datInd->numLch;

   ret = RgUiRguDDatInd(&(rguUlSap->sapCfg.sapPst), rguUlSap->sapCfg.suId,
         datInd);
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xb2000a,L_ERROR,DBG_CELLID, datInd->cellId, 0, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",892, "RgUiRguDdatInd Failed", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(ret);
   }




   return(ret);
}
 S16 rgUIMSndCmnDatInd
(
Inst inst,
RgUpSapCb *rguUlSap,
RgRguCmnDatInd *datInd
)






{
   S16 ret = 0;

   ;


   ;

   rguUlSap->sapSts.numPduTxmit++;

   ;
   ret = RgUiRguCDatInd(&(rguUlSap->sapCfg.sapPst), rguUlSap->sapCfg.suId,
         datInd);
   if (ret != 0)
   {
      { if ((&rgCb[inst].rgInit)->dbgMask & ((0x00000100 << 1))) { snprintf((&rgCb[inst].rgInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "MAC", (&rgCb[inst].rgInit)->procId, (&rgCb[inst].rgInit)->ent, (&rgCb[inst].rgInit)->inst, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c", 949); SPrint((&rgCb[inst].rgInit)->prntBuf); sprintf (rgCb[inst].rgInit.prntBuf,"RgUiRguCDatInd Failed\n"); SPrint((&rgCb[inst].rgInit)->prntBuf); } };
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xb2000b,L_ERROR,DBG_CELLID, datInd->cellId, 0, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",950, "RgUiRguCDatInd Failed", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(ret);
   }
   return(ret);
}
 S16 RgUiCrgBndReq
(
Pst *pst,
SuId suId,
SpId spId
)






{
   S16 ret = 0;
   Pst tmpPst;
   RgUstaDgn dgn;
   Inst inst;

   ;


   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;

   tmpPst.prior = pst->prior;
   tmpPst.route = pst->route;
   tmpPst.selector = pst->selector;
   tmpPst.region = rgCb[inst].rgInit.region;
   tmpPst.pool = rgCb[inst].rgInit.pool;
   tmpPst.srcProcId = rgCb[inst].rgInit.procId;
   tmpPst.srcEnt = rgCb[inst].rgInit.ent;
   tmpPst.srcInst = rgCb[inst].rgInit.inst;
   tmpPst.event = 0x00;
   tmpPst.dstProcId = pst->srcProcId;
   tmpPst.dstEnt = pst->srcEnt;
   tmpPst.dstInst = pst->srcInst;


   if(spId == rgCb[inst].crgSap.sapCfg.spId)
   {

      switch (rgCb[inst].crgSap.sapSta.sapState)
      {
         case 0:

            rgFillDgnParams(inst,&dgn, 1);
            ret = rgLMMStaInd(inst,2,0,
                  2, &dgn);
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb2000c, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1024, "SAP Not Configured", RLOG_FILE_ID, RLOG_MODULE_NAME); };
            ret = RgUiCrgBndCfm(&tmpPst, suId, 2);
            break;
         case 1:
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb2000d, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1028, "SAP Not yet bound", RLOG_FILE_ID, RLOG_MODULE_NAME); };

            rgCb[inst].crgSap.sapSta.sapState = 2;
            rgCb[inst].crgSap.sapCfg.suId = suId;

            ret = rgUIMCrgBndCfm(inst,suId, 1);

            rgFillDgnParams(inst,&dgn, 1);
            ret = rgLMMStaInd(inst,2,(256 + 1),
                  0, &dgn);
            break;
         case 2:
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb2000e, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1040, "SAP is already bound", RLOG_FILE_ID, RLOG_MODULE_NAME); };

            ret = rgUIMCrgBndCfm(inst,suId, 1);
            break;
         default:




            ret = rgUIMCrgBndCfm(inst,suId, 2);
            break;
      }
   }
   else
   {




      ret = rgUIMCrgBndCfm(inst,suId, 2);
   }
   return(ret);
}
 S16 RgUiCrgUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)






{
   Inst inst;
   ;


   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;

   if (spId == rgCb[inst].crgSap.sapCfg.spId)
   {
      switch(rgCb[inst].crgSap.sapSta.sapState)
      {
         case 2:

            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb2000f, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1110, "SAP is already bound", RLOG_FILE_ID, RLOG_MODULE_NAME); };

            rgCb[inst].crgSap.sapSta.sapState = 1;
            break;
         default:




            return(1);
      }
   }
   else
   {




      return(1);
   }
   return(0);
}
 S16 rgUIMCrgBndCfm
(
Inst inst,
SuId suId,
U8 status
)






{
   ;


   if(RgUiCrgBndCfm(&(rgCb[inst].crgSap.sapCfg.sapPst), rgCb[inst].crgSap.sapCfg.suId, status) != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20010, L_ERROR, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1170, "RgUiCrgBndCfm Failed ", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(1);
   }

   return(0);
}
 S16 RgUiCrgCfgReq
(
Pst *pst,
SpId spId,
CrgCfgTransId transId,
CrgCfgReqInfo *cfgReqInfo
)







{
   Inst inst;
   S16 ret = 0;
   U8 cfmStatus = 0x00ff;
   U8 prntTrans[12 +1];

   ;;

   { if(pst->dstInst >= 2) { return(1); }};
   inst = pst->dstInst - 0;

   cmMemcpy((U8 *)prntTrans, (U8 *)transId.trans, 12);
   prntTrans[12] = '\0';



   if (cfgReqInfo == 0L)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20011, L_ERROR, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1230, "Input Param crgReqInfo is NULL ", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      rgUIMCrgCfgCfm(inst,transId, cfmStatus);
      return(1);
   }


   if (spId == rgCb[inst].crgSap.sapCfg.spId)
   {
      switch(rgCb[inst].crgSap.sapSta.sapState)
      {
         case 2:
            if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20012, L_DEBUG, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1241, "SAP is already bound", RLOG_FILE_ID, RLOG_MODULE_NAME); };
            break;
         default:




         SPutSBuf (pst->region, pst->pool, (Data *)cfgReqInfo,
               sizeof(CrgCfgReqInfo));
         cfgReqInfo = 0L;

            rgUIMCrgCfgCfm(inst,transId, cfmStatus);
            return(1);
      }
   }
   else
   {




      SPutSBuf (pst->region, pst->pool, (Data *)cfgReqInfo,
            sizeof(CrgCfgReqInfo));
      cfgReqInfo = 0L;
      rgUIMCrgCfgCfm(inst,transId, cfmStatus);
      return(1);
   }
   ret = rgCOMCfgReq(inst,transId, cfgReqInfo);
   SPutSBuf (pst->region, pst->pool, (Data *)cfgReqInfo,
         sizeof(CrgCfgReqInfo));
   cfgReqInfo = 0L;
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20013, L_ERROR, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1274, "Configuration Request Handling Failed ", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(1);
   }

   return(0);
}
 S16 rgUIMCrgCfgCfm
(
Inst inst,
CrgCfgTransId transId,
U8 status
)






{
   S16 ret = 0;

   ;;



   U8 prntTrans[12 +1];
   cmMemcpy((U8 *)prntTrans, (U8 *)transId.trans, 12);
   prntTrans[12] = '\0';


   ret = RgUiCrgCfgCfm(&(rgCb[inst].crgSap.sapCfg.sapPst), rgCb[inst].crgSap.sapCfg.suId, transId, status);
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev0(0xb20014, L_ERROR, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_uim.c",1327, "RgUiCrgCfgCfm Failed ", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(ret);
   }

   return(ret);
}
