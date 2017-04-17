static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_FILE_ID=187;
static int RLOG_MODULE_ID=4096;


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





extern U32 rgNumPrachRecvd;
extern U32 rgNumRarSched;
extern U32 rgNumBI;
extern U32 rgNumMsg3CrcPassed;
extern U32 rgNumMsg3CrcFailed ;
extern U32 rgNumMsg3FailMaxRetx ;
extern U32 rgNumMsg4Ack ;
extern U32 rgNumMsg4Nack ;

extern U32 rgNumMsg4FailMaxRetx ;
extern U32 rgNumSrRecvd;
extern U32 rgNumSrGrant;
extern U32 rgNumMsg3CrntiCE;
extern U32 rgNumDedPream ;
extern U32 rgNumMsg3CCCHSdu;
extern U32 rgNumCCCHSduCrntiNotFound ;
extern U32 rgNumCrntiCeCrntiNotFound ;
extern U32 rgNumMsg4WithCCCHSdu ;
extern U32 rgNumMsg4WoCCCHSdu ;
extern U32 rgNumMsg4Dtx ;
extern U32 rgNumMsg3AckSent ;
extern U32 rgNumMsg3NackSent ;
extern U32 rgNumMsg4PdcchWithCrnti ;
extern U32 rgNumRarFailDuetoRntiExhaustion ;
extern U32 rgNumTAModified ;
extern U32 rgNumTASent ;
extern U32 rgNumMsg4ToBeTx ;
extern U32 rgNumMsg4Txed ;
extern U32 rgNumMsg3DtxRcvd;

extern U32 rgNumDedPreamUECtxtFound;
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
typedef enum rgrGrpPwrFormat
{
   RGR_PWR_FORMAT_3,
   RGR_PWR_FORMAT_3A
} RgrGrpPwrFormat;
typedef enum rgrCqiPrdicity
{
   RGR_CQI_PRD_MS2 = 2,
   RGR_CQI_PRD_MS5 = 5,
   RGR_CQI_PRD_MS10 = 10,
   RGR_CQI_PRD_MS20 = 20,
   RGR_CQI_PRD_MS32 = 32,
   RGR_CQI_PRD_MS40 = 40,
   RGR_CQI_PRD_MS64 = 64,
   RGR_CQI_PRD_MS80 = 80,
   RGR_CQI_PRD_MS128 = 128,
   RGR_CQI_PRD_MS160 = 160,
   RGR_CQI_PRD_MS256 = 256,
   RGR_CQI_PRD_MSOff
} RgrCqiPrdicity;



typedef enum rgrPrdCqiMode
{
   RGR_PRD_CQI_MOD10,
   RGR_PRD_CQI_MOD11,
   RGR_PRD_CQI_MOD20,
   RGR_PRD_CQI_MOD21
} RgrPrdCqiMode;



typedef enum rgrPwrAlpha
{
   RGR_PWR_ALPHA0 = 0,
   RGR_PWR_ALPHA4 = 4,
   RGR_PWR_ALPHA5 = 5,
   RGR_PWR_ALPHA6 = 6,
   RGR_PWR_ALPHA7 = 7,
   RGR_PWR_ALPHA8 = 8,
   RGR_PWR_ALPHA9 = 9,
   RGR_PWR_ALPHAALL = 10
} RgrPwrAlpha;


typedef enum rgrAckNackRepFactor
{
   RGR_ACKNACK_REPFACT_N2 = 2,
   RGR_ACKNACK_REPFACT_N4 = 4,
   RGR_ACKNACK_REPFACT_N6 = 6
} RgrAckNackRepFactor;





typedef enum rgrTxModeTrnstn
{
   RGR_TXMODE_RECFG_CMPLT = 0,
   RGR_TXMODE_RECFG_START
}RgrTxModeTrnstn;




typedef enum rgrTxMode
{
   RGR_UE_TM_1 = 1,
   RGR_UE_TM_2,
   RGR_UE_TM_3,
   RGR_UE_TM_4,
   RGR_UE_TM_5,
   RGR_UE_TM_6,
   RGR_UE_TM_7,
   RGR_UE_TM_8




} RgrTxMode;


typedef enum rgrRaSfn
{
   RGR_SFN_EVEN,
   RGR_SFN_ANY,






   RGR_SFN_NA
} RgrRaSfn;


typedef enum rgrSrsCfgPrd
{
   RGR_SRS_CFG_PRD_1 = 1,
   RGR_SRS_CFG_PRD_2 = 2,
   RGR_SRS_CFG_PRD_5 = 5,
   RGR_SRS_CFG_PRD_10 = 10,
   RGR_SRS_CFG_PRD_INF
} RgrSrsCfgPrd;



typedef enum rgrSrsBwCfg
{
   RGR_SRS_BWCFG_0 = 0,
   RGR_SRS_BWCFG_1 = 1,
   RGR_SRS_BWCFG_2 = 2,
   RGR_SRS_BWCFG_3 = 3,
   RGR_SRS_BWCFG_4 = 4,
   RGR_SRS_BWCFG_5 = 5,
   RGR_SRS_BWCFG_6 = 6,
   RGR_SRS_BWCFG_7 = 7
} RgrSrsBwCfg;




typedef enum rgrPhichNg
{
   RGR_NG_ONESIXTH,
   RGR_NG_HALF,
   RGR_NG_ONE,
   RGR_NG_TWO
} RgrPhichNg;


typedef enum rgrAprdCqiMode
{
   RGR_APRD_CQI_MOD12,
   RGR_APRD_CQI_MOD20,
   RGR_APRD_CQI_MOD22,
   RGR_APRD_CQI_MOD30,
   RGR_APRD_CQI_MOD31
} RgrAprdCqiMode;




typedef enum rgrSpsImplRelCnt
{
   RGR_SPS_E2 = 2,
   RGR_SPS_E3 = 3,
   RGR_SPS_E4 = 4,
   RGR_SPS_E8 = 8
} RgrSpsImplRelCnt;





typedef enum rgrSpsPrd
{
   RGR_SPS_PRD_10SF = 10,
   RGR_SPS_PRD_20SF = 20,
   RGR_SPS_PRD_32SF = 32,
   RGR_SPS_PRD_40SF = 40,
   RGR_SPS_PRD_64SF = 64,
   RGR_SPS_PRD_80SF = 80,
   RGR_SPS_PRD_128SF = 128,
   RGR_SPS_PRD_160SF = 160,
   RGR_SPS_PRD_320SF = 320,
   RGR_SPS_PRD_640SF = 640,
   RGR_SPS_PRD_INVALID
} RgrSpsPrd;
typedef enum _rgrSiPerd
{
   RGR_SI_PERD_8 = 8,
   RGR_SI_PERD_16 = 16,
   RGR_SI_PERD_32 = 32,
   RGR_SI_PERD_64 = 64,
   RGR_SI_PERD_128 = 128,
   RGR_SI_PERD_256 = 256,
   RGR_SI_PERD_512 = 512
} RgrSiPeriodicity;






typedef enum _rgrModPerd
{
   RGR_MOD_PERD_64 = 64,
   RGR_MOD_PERD_128 = 128,
   RGR_MOD_PERD_256 = 256,
   RGR_MOD_PERD_512 = 512,
   RGR_MOD_PERD_1024 = 1024
} RgrModPeriodicity;


typedef enum rgrSiCfgType
{
   RGR_SI_CFG_TYPE_MIB = 0,
   RGR_SI_CFG_TYPE_SIB1,
   RGR_SI_CFG_TYPE_SI,
   RGR_SI_CFG_TYPE_SIB1_PWS,
   RGR_SI_CFG_TYPE_SIB8_CDMA,
   RGR_SI_STOP
} RgrSiCfgType;






typedef enum _rgrDrxTmrPerd
{
   RGR_DRX_PRD_1PSF = 1,
   RGR_DRX_PRD_2PSF = 2,
   RGR_DRX_PRD_3PSF = 3,
   RGR_DRX_PRD_4PSF = 4,
   RGR_DRX_PRD_5PSF = 5,
   RGR_DRX_PRD_6PSF = 6,
   RGR_DRX_PRD_8PSF = 8,
   RGR_DRX_PRD_10PSF = 10,
   RGR_DRX_PRD_16PSF = 16,
   RGR_DRX_PRD_20PSF = 20,
   RGR_DRX_PRD_24PSF = 24,
   RGR_DRX_PRD_30PSF = 30,
   RGR_DRX_PRD_33PSF = 33,
   RGR_DRX_PRD_40PSF = 40,
   RGR_DRX_PRD_50PSF = 50,
   RGR_DRX_PRD_60PSF = 60,
   RGR_DRX_PRD_80PSF = 80,
   RGR_DRX_PRD_100PSF = 100,
   RGR_DRX_PRD_200PSF = 200,
   RGR_DRX_PRD_300PSF = 300,
   RGR_DRX_PRD_500PSF = 500,
   RGR_DRX_PRD_750PSF = 750,
   RGR_DRX_PRD_1280PSF = 1280,
   RGR_DRX_PRD_1920PSF = 1920,
   RGR_DRX_PRD_2560PSF = 2560
}RgrDrxTmrPrd;





typedef enum _rgrDrxCyclePerd
{
   RGR_DRX_PRD_2SF = 2,
   RGR_DRX_PRD_5SF = 5,
   RGR_DRX_PRD_8SF = 8,
   RGR_DRX_PRD_10SF = 10,
   RGR_DRX_PRD_16SF = 16,
   RGR_DRX_PRD_20SF = 20,
   RGR_DRX_PRD_32SF = 32,
   RGR_DRX_PRD_40SF = 40,
   RGR_DRX_PRD_64SF = 64,
   RGR_DRX_PRD_80SF = 80,
   RGR_DRX_PRD_128SF = 128,
   RGR_DRX_PRD_160SF = 160,
   RGR_DRX_PRD_256SF = 256,
   RGR_DRX_PRD_320SF = 320,
   RGR_DRX_PRD_512SF = 512,
   RGR_DRX_PRD_640SF = 640,
   RGR_DRX_PRD_1024SF = 1024,
   RGR_DRX_PRD_1280SF = 1280,
   RGR_DRX_PRD_2048SF = 2048,
   RGR_DRX_PRD_2560SF = 2560
}RgrDrxCyclePrd;




typedef enum _rgrDrxShortCycleTmr
{
   RGR_DRX_SHRTCYCLE_MIN = 1,
   RGR_DRX_SHRTCYCLE_MAX = 16
}RgrDrxShrtCycleTmr;
typedef enum
{
   RGRUE_DLPWRCNTRL_PA_DB_6 = 0,
   RGRUE_DLPWRCNTRL_PA_DB_4DOT77,
   RGRUE_DLPWRCNTRL_PA_DB_3,
   RGRUE_DLPWRCNTRL_PA_DB_1DOT77,
   RGRUE_DLPWRCNTRL_PA_DB0,
   RGRUE_DLPWRCNTRL_PA_DB1,
   RGRUE_DLPWRCNTRL_PA_DB2,
   RGRUE_DLPWRCNTRL_PA_DB3
} RgrUeDlPwrCntrlPaCfg;


typedef enum rgrSchFrmt1b3TypEnum
{
   RG_SCH_UCI_FORMAT1A_1B,
   RG_SCH_UCI_FORMAT1B_CS,
   RG_SCH_UCI_FORMAT3,
   RG_SCH_UCI_FORMAT_NON_CA
}RgrSchFrmt1b3TypEnum;



typedef struct rgrCfgTransId
{
   U8 trans[12];
} RgrCfgTransId;


typedef struct rgrDlHqCfg
{
   U8 maxDlHqTx;


   U8 maxMsg4HqTx;


} RgrDlHqCfg;


typedef struct rgrRntiCfg
{
   CmLteRnti startRnti;
   U16 size;

} RgrRntiCfg;


typedef struct rgrDlCmnCodeRateCfg
{
   U16 bcchPchRaCodeRate;


   U16 pdcchCodeRate;



   U8 ccchCqi;


} RgrDlCmnCodeRateCfg;


typedef struct rgrCfiCfg
{
   U8 cfi;
} RgrCfiCfg;


typedef struct rgrPuschSubBandCfg
{
  U8 subbandStart;
  U8 numSubbands;
  U8 size;
  U8 dmrs[110];
} RgrPuschSubBandCfg;


typedef struct rgrUlCmnCodeRateCfg
{
   U8 ccchCqi;

} RgrUlCmnCodeRateCfg;




typedef struct rgrUlTrgCqiCfg
{
   U8 trgCqi;

} RgrUlTrgCqiCfg;


typedef struct rgrBwCfg
{
   U8 dlTotalBw;
   U8 ulTotalBw;
} RgrBwCfg;



typedef struct rgrPhichCfg
{
   RgrPhichNg ngEnum;
   Bool isDurExtend;
} RgrPhichCfg;



typedef struct rgrPucchCfg
{
   U8 resourceSize;
   U16 n1PucchAn;
   U8 deltaShift;
   U8 cyclicShift;

   U8 maxPucchRb;




} RgrPucchCfg;


typedef struct rgrSrsCfg
{

   Bool isSrsCfgSetup;
   RgrSrsCfgPrd srsCfgPrdEnum;
   RgrSrsBwCfg srsBwEnum;

   U8 srsSubFrameCfg;

} RgrSrsCfg;


typedef struct rgrRachCfg
{
   U8 preambleFormat;
   U8 raWinSize;

   struct raOccasionS
   {
      U8 size;
      RgrRaSfn sfnEnum;
      U8 subFrameNum[10];
   } raOccasion;
   U8 maxMsg3Tx;
   U8 numRaPreamble;
   U8 sizeRaPreambleGrpA;
   U16 msgSizeGrpA;
   U8 prachResource;




   U8 contResTmr;


} RgrRachCfg;




typedef struct rgrSiCfg
{
   U8 siWinSize;
   U8 retxCnt;





   RgrModPeriodicity modPrd;
   U8 numSi;
   RgrSiPeriodicity siPeriodicity[16];
   U16 minPeriodicity;


} RgrSiCfg;



typedef struct rgrTpcRntiCfg
{
   CmLteRnti startTpcRnti;
   U16 size;
} RgrTpcRntiCfg;




typedef struct rgrUlPwrCfg
{
   S8 p0NominalPusch;

   RgrPwrAlpha alpha;

   S8 p0NominalPucch;

   S8 deltaPreambleMsg3;

   RgrTpcRntiCfg pucchPwrFmt3;
   RgrTpcRntiCfg pucchPwrFmt3a;
   RgrTpcRntiCfg puschPwrFmt3;
   RgrTpcRntiCfg puschPwrFmt3a;
} RgrUlPwrCfg;



typedef struct rgrPuschCfg
{
   U8 numSubBands;

   Bool isIntraHop;

   U8 hopOffst;

} RgrPuschCfg;



typedef struct rgrCodeBookRstCfg
{
   Bool pres;
   U32 pmiBitMap[2];
} RgrCodeBookRstCfg;


typedef struct rgrPreambleSetCfg
{
   Bool pres;
   U8 start;
   U8 size;

} RgrPreambleSetCfg;



typedef struct rgrCmnLchCfg
{
   CmLteLcId lcId;
   CmLteLcType lcType;






   U8 dir;




   CmLteTrchType dlTrchType;





   CmLteTrchType ulTrchType;




} RgrCmnLchCfg;



typedef struct rgrDlfsCfg
{
  U8 isDlFreqSel;

  U8 thresholdCqi;






} RgrDlfsCfg;





typedef enum _rgrFeature
{
   RGR_ABS = 1 << 0,
   RGR_SFR = 1 << 1,
   RGR_DSFR = 1 << 2,
   RGR_RE = 1 << 3







} RgrFeature;



typedef enum _rgrFeaturestatus
{
   RGR_DISABLE = 0,
   RGR_ENABLE = 1
} RgrFeatureStatus;



typedef enum _rgrAbsPatternType
{
   RGR_ABS_MUTE = 1 << 0,
   RGR_ABS_TRANSMIT = 1 << 1
} RgrAbsPatternType;



typedef struct rgrSfrRbRange
{
   U8 startRb;
   U8 endRb;
} RgrSfrRbRange;




typedef struct rgrPwrThreshold
{
   RgrUeDlPwrCntrlPaCfg pLow;
   RgrUeDlPwrCntrlPaCfg pHigh;
} RgrPwrThreshold;




typedef struct rgrSfrConfig
{
   RgrFeatureStatus status;
   RgrSfrRbRange cellEdgeRbRange;

   RgrPwrThreshold pwrThreshold;

} RgrSfrConfig;


typedef struct rgrDsfrConfig
{
   RgrFeatureStatus status;
} RgrDsfrConfig;



typedef struct rgrAbsConfig
{
   RgrFeatureStatus status;
   U32 absPatternType;
   U8 absPattern[40];
   U32 absLoadPeriodicity;
} RgrAbsConfig;



typedef struct rgrLteAdvancedCellConfig
{
   U32 pres;
   RgrAbsConfig absCfg;
   RgrSfrConfig sfrCfg;
   RgrDsfrConfig dsfrCfg;
} RgrLteAdvancedCellConfig;
typedef struct rgrEnbPfs
{
   U8 tptCoeffi;

   U8 fairCoeffi;

   U32 qciWgt[9];
} RgrEnbPfs;




typedef enum rgrCellAccsMode
{
   RGR_CELL_ACCS_OPEN = 1,
   RGR_CELL_ACCS_CLOSED,
   RGR_CELL_ACCS_HYBRID
} RgrCellAccsMode;




typedef enum rgrCellCntrlCmdType
{
   RGR_CNTRL_CMD_RACH_OVRLD=1,
   RGR_CNTRL_CMD_CPU_OVRLD
}RgrCellCntrlCmdType;




typedef struct rgrCellCntrlCmdCfg
{
   RgrCellCntrlCmdType cmdType;

   union rgrCellCmdDesc
   {

      struct rachOvrLd
      {
         Bool backOffEnb;
         U8 backOffVal;
      }rachOvrLd;


      struct cpuOvrLd
      {
         U8 instruction;
      }cpuOvrLd;
   }cmdDesc;
} RgrCellCntrlCmdCfg;







typedef struct rgrSchedEnbCfg
{
   U8 numTxAntPorts;
   U8 dlSchdType;

   union rgrDlSchInfoS
   {
      RgrEnbPfs dlPfs;

   } dlSchInfo;
   U8 ulSchdType;

   union rgrUlSchInfoS
   {
      RgrEnbPfs ulPfs;







   } ulSchInfo;
   RgrCellAccsMode accsMode;
} RgrSchedEnbCfg;
typedef struct rgrSpsCellCfg
{
   U8 maxSpsDlBw;

   U16 maxSpsUePerDlSf;

   U16 maxSpsUePerUlSf;

} RgrSpsCellCfg;




typedef struct rgrCellCsgParamCfg
{
   U8 minDlResNonCsg;
   U8 minUlResNonCsg;
} RgrCellCsgParamCfg;


typedef struct rgrLteUCfg
{
   Bool isLaaCell;
}RgrLteUCfg;




typedef struct rgrCellCfg
{
   CmLteCellId cellId;
   Inst macInst;





   U8 maxMsg3PerUlSf;



   U8 maxUePerUlSf;


   U8 maxUePerDlSf;



   U8 maxCcchPerDlSf;




   U8 maxUlBwPerUe;





   U8 maxDlBwPerUe;





   U8 maxDlRetxBw;





   U8 maxDlUeNewTxPerTti;




   U8 maxUlUeNewTxPerTti;




   Bool isCpUlExtend;

   Bool isCpDlExtend;

   Bool cellModSchm;



   S8 pMax;


   U8 dlfsSchdType;

   RgrDlHqCfg dlHqCfg;
   RgrRntiCfg macRnti;
   RgrCfiCfg cfiCfg;
   RgrUlTrgCqiCfg trgUlCqi;
   RgrDlCmnCodeRateCfg dlCmnCodeRate;

   RgrPuschSubBandCfg puschSubBand;
   RgrUlCmnCodeRateCfg ulCmnCodeRate;

   RgrDlfsCfg dlfsCfg;
   RgrBwCfg bwCfg;
   RgrPhichCfg phichCfg;
   RgrPucchCfg pucchCfg;
   RgrSrsCfg srsCfg;

   RgrRachCfg rachCfg;
   RgrSiCfg siCfg;
   RgrUlPwrCfg pwrCfg;
   RgrPuschCfg puschCfg;
   RgrPreambleSetCfg macPreambleSet;

   U8 numCmnLcs;
   RgrCmnLchCfg cmnLcCfg[6];

   RgrCellCsgParamCfg csgParamCfg;
   U8 rrmTtiIndPrd;
   RgrSpsCellCfg spsCfg;

   RgrLteAdvancedCellConfig rgrLteAdvCfg;
   U16 t300TmrVal;


   U16 bcchTxPwrOffset;




   U16 pcchTxPwrOffset;




   U16 rarTxPwrOffset;





   U16 phichTxPwrOffset;




   Bool isDynCfiEnb;

   Bool isAutoCfgModeEnb;

   RgrUeDlPwrCntrlPaCfg msg4pAVal;

   RgrLteUCfg lteUCfg;
} RgrCellCfg;


typedef struct rgrUeAprdDlCqiCfg
{
   Bool pres;

   RgrAprdCqiMode aprdModeEnum;





} RgrUeAprdDlCqiCfg;
typedef struct rgrUeDlPCqiSetup
{
      U16 cqiPResIdx;
      U16 cqiPCfgIdx;
      U8 cqiRepType;
      U8 k;

      U8 riEna;
      U16 riCfgIdx;
      Bool sANCQI;
      RgrPrdCqiMode prdModeEnum;
}RgrUeDlPCqiSetup;





typedef struct rgrUeDlPCqiCfg
{
   U8 type;
   RgrUeDlPCqiSetup cqiSetup;
} RgrUePrdDlCqiCfg;







typedef enum rgrUlSrsBwInfo
{
   RGR_ULSRS_BW_0 = 0,
   RGR_ULSRS_BW_1 = 1,
   RGR_ULSRS_BW_2 = 2,
   RGR_ULSRS_BW_3 = 3
} RgrUlSrsBwInfo;






typedef enum rgrUlSrsHoBwInfo
{
   RGR_ULSRS_HOP_BW_0 = 0,
   RGR_ULSRS_HOP_BW_1 = 1,
   RGR_ULSRS_HOP_BW_2 = 2,
   RGR_ULSRS_HOP_BW_3 = 3
} RgrUlSrsHoBwInfo;





typedef enum rgrUlSrsCycShiftInfo
{
   RGR_ULSRS_CYSHIFT_0 = 0,
   RGR_ULSRS_CYSHIFT_1 = 1,
   RGR_ULSRS_CYSHIFT_2 = 2,
   RGR_ULSRS_CYSHIFT_3 = 3,
   RGR_ULSRS_CYSHIFT_4 = 4,
   RGR_ULSRS_CYSHIFT_5 = 5,
   RGR_ULSRS_CYSHIFT_6 = 6,
   RGR_ULSRS_CYSHIFT_7 = 7
} RgrUlSrsCycShiftInfo;







typedef struct rgrUeUlSrsSetupCfg
{
   U16 srsCfgIdx;

   RgrUlSrsBwInfo srsBw;
   RgrUlSrsHoBwInfo srsHopBw;
   RgrUlSrsCycShiftInfo cycShift;
   Bool duration;

   Bool sANSrs;







   U8 txComb;
   U8 fDomPosi;
}RgrUeUlSrsSetupCfg;






typedef enum rgrUeDsrTransMax
{
   RGR_DSR_TXMAX_4=4,
   RGR_DSR_TXMAX_16=16,
   RGR_DSR_TXMAX_32=32,
   RGR_DSR_TXMAX_64=64
}RgrUeDsrTransMax;





typedef struct rgrUeSrSetupCfg
{
   U16 srResIdx;
   U8 srCfgIdx;

}RgrUeSrSetupCfg;




typedef struct rgrUeSrCfg
{
   Bool type;
   RgrUeSrSetupCfg srSetup;
}RgrUeSrCfg;




typedef struct rgrUeUlSrsCfg
{
   U8 type;
   RgrUeUlSrsSetupCfg srsSetup;

}RgrUeUlSrsCfg;
typedef struct rgrUePuschDedCfg
{
   Bool pres;
   U8 bACKIdx;
   U8 bRIIdx;
   U8 bCQIIdx;
}RgrUePuschDedCfg;



typedef struct rgrUeDlCqiCfg
{
   RgrUeAprdDlCqiCfg aprdCqiCfg;
   RgrUePrdDlCqiCfg prdCqiCfg;
} RgrUeDlCqiCfg;



typedef struct rgrUeMeasGapCfg
{
   Bool isMesGapEnabled;
   U8 gapPrd;
   U8 gapOffst;
} RgrUeMeasGapCfg;


typedef struct rgrDrxLongCycleOffst
{
   U16 longDrxCycle;
   U16 drxStartOffst;
} RgrDrxLongCycleOffst;



typedef struct rgrDrxShortDrx
{
   Bool pres;
   U16 shortDrxCycle;
   U8 drxShortCycleTmr;
} RgrDrxShortDrx;



typedef struct rgrUeDrxCfg
{
   Bool isDrxEnabled;
   U8 drxOnDurTmr;

   U16 drxInactvTmr;

   U8 drxRetxTmr;

   RgrDrxLongCycleOffst drxLongCycleOffst;
   RgrDrxShortDrx drxShortDrx;
} RgrUeDrxCfg;



typedef struct rgrUeCapCfg
{
   U8 pwrClass;
   Bool intraSfFeqHop;
   Bool resAloocType1;
   Bool simCqiAckNack;
   Bool txAntSel;

} RgrUeCapCfg;



typedef struct rgrUeAckNackRepCfg
{
   Bool isAckNackEnabled;



   U16 pucchAckNackRep;
   RgrAckNackRepFactor ackNackRepFactor;
} RgrUeAckNackRepCfg;



typedef struct rgrUeTxModeCfg
{
   Bool pres;
   RgrTxModeTrnstn tmTrnstnState;

   RgrTxMode txModeEnum;
} RgrUeTxModeCfg;


typedef struct rgrUeUlHqCfg
{
   U8 maxUlHqTx;
   U8 deltaHqOffst;

} RgrUeUlHqCfg;


typedef struct rgrUeGrpPwrCfg
{
   Bool pres;
   CmLteRnti tpcRnti;
   U8 idx;
} RgrUeGrpPwrCfg;


typedef struct rgrUeUlPwrCfg
{
   RgrUeGrpPwrCfg uePuschPwr;
   RgrUeGrpPwrCfg uePucchPwr;
   Bool isAccumulated;
   Bool isDeltaMCSEnabled;
   S8 p0UePusch;
   S8 p0UePucch;
   U8 pSRSOffset;

   U8 trgCqi;


} RgrUeUlPwrCfg;


typedef struct rgrUeQosCfg
{
   Bool ambrPres;
   U32 dlAmbr;
   U32 ueBr;
} RgrUeQosCfg;


typedef struct rgrUeTaTmrCfg
{
   Bool pres;
   U16 taTmr;
} RgrUeTaTmrCfg;







typedef struct rgrUeBsrTmrCfg
{
   Bool isPrdBsrTmrPres;

   U16 prdBsrTmr;


   U16 retxBsrTmr;

} RgrUeBsrTmrCfg;






typedef struct rgrUeSpsDlCfg
{
   Bool isDlSpsEnabled;
   U8 numSpsHqProc;

   U8 numPucchVal;
   U32 n1PucchVal[4];
   RgrSpsPrd dlSpsPrdctyEnum;
   U16 explicitRelCnt;

} RgrUeSpsDlCfg;

typedef struct rgrUlSpsLcInfo
{
   Bool isSpsEnabled;
   U8 lcId;
}RgrUlSpsLcInfo;



typedef struct rgrUeSpsUlCfg
{
   Bool isUlSpsEnabled;

   RgrSpsImplRelCnt implicitRelCnt;





   Bool pwrCfgPres;

   struct
   {
      S8 p0NominalPuschVal;
      S8 p0UePuschVal;
   } pwrCfg;
   RgrSpsPrd ulSpsPrdctyEnum;
   U8 lcCnt;
   RgrUlSpsLcInfo spsLcInfo[10];



   Bool isLcSRMaskEnab ;


} RgrUeSpsUlCfg;



typedef struct rgrUeSpsCfg
{
   CmLteRnti spsRnti;
   RgrUeSpsDlCfg dlSpsCfg;
   RgrUeSpsUlCfg ulSpsCfg;

} RgrUeSpsCfg;


typedef enum rgrUeTxAntSelType
{
   RGR_UE_TX_ANT_OPENLOOP,
   RGR_UE_TX_ANT_CLOSEDLOOP
} RgrUeTxAntSelType;


typedef struct rgrUeTxAntSelCfg
{
   Bool pres;
   RgrUeTxAntSelType selType;
} RgrUeTxAntSelCfg;
typedef struct rgrUeCqiReptCfg
{
   U8 numColltdCqiRept;

}RgrUeCqiReptCfg;



typedef struct rgrSubBandCqiInfo
{
   U8 cqi[2];
   U8 subBandIdx;

} RgrSubBandCqiInfo;




typedef struct rgrUeCqiRept
{
   U8 cqi[2];
   U8 cqiMode;
   RgrSubBandCqiInfo sbCqiInfo[13];
   U8 numSubBand;

} RgrUeCqiRept;




typedef struct RgrUeCqiInfo
{
   RgrUeCqiRept cqiRept[16];
   U8 numCqiRept;
} RgrUeCqiInfo;




typedef struct rgrStaIndInfo
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   RgrUeCqiInfo ueCqiInfo;
}RgrStaIndInfo;





typedef struct rgrLoadInfIndInfo
{
   CmLteCellId cellId;
   U16 bw;
   U32 type;
   union
   {
      TknStrOSXL rntpInfo;
      U32 absLoadInfo[40];
   } u;
}RgrLoadInfIndInfo;






typedef struct rgrUepACfg
{

   RgrUeDlPwrCntrlPaCfg pA;


   Bool pAPrsnt;
}RgrUepACfg;


typedef struct rgrUePdschDedCfg
{
   RgrUepACfg uepACfg;

}RgrUePdschDedCfg;





typedef struct rgrLteAdvancedUeConfig
{
   U32 pres;
   Bool isUeCellEdge;
   Bool isAbsUe;
} RgrLteAdvancedUeConfig;


typedef enum RgrAccessStratumRls
{
 RGR_REL_8,
 RGR_REL_9,
 RGR_REL_10,
 RGR_REL_11,
 RGR_REL_SPARE_4,
 RGR_REL_SPARE_3,
 RGR_REL_SPARE_2,
 RGR_REL_SPARE_1,
} RgrAccessStratumRls;



typedef struct rgrUeCfg
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   RgrUeTxModeCfg txMode;
   RgrUeDlCqiCfg ueDlCqiCfg;
   RgrUeUlHqCfg ueUlHqCfg;
   RgrUeUlPwrCfg ueUlPwrCfg;
   RgrUeQosCfg ueQosCfg;
   RgrUeTaTmrCfg ueTaTmrCfg;





   RgrUeBsrTmrCfg ueBsrTmrCfg;



   CmLteUeCategory ueCatEnum;


   RgrUeDrxCfg ueDrxCfg;

   Bool isTtiBundlEnabled;
   RgrUeAckNackRepCfg ueAckNackCfg;
   RgrUeMeasGapCfg ueMesGapCfg;
   RgrUeCapCfg ueCapCfg;
   RgrCodeBookRstCfg ueCodeBookRstCfg;

   TknU8 dedPreambleId;
   RgrUeSpsCfg ueSpsCfg;







   RgrUeUlSrsCfg srsCfg;
   RgrUeSrCfg srCfg;
   RgrUePuschDedCfg puschDedCfg;

   RgrUeTxAntSelCfg ulTxAntSel;






   RgrUeCqiReptCfg ueCqiReptCfg;




   RgrUePdschDedCfg uePdschDedCfg;


   RgrLteAdvancedUeConfig ueLteAdvCfg;

   RgrAccessStratumRls accessStratumRls;
   U8 csgMmbrSta;
} RgrUeCfg;


typedef struct rgrLchQosCfg
{
   U8 qci;

   U32 gbr;
   U32 mbr;
} RgrLchQosCfg;



typedef struct rgrLchSpsCfg
{
   Bool isSpsEnabled;

} RgrLchSpsCfg;


typedef struct rgrDlLchCfg
{
   CmLteTrchType dlTrchType;





   RgrLchQosCfg dlQos;

   RgrLchSpsCfg dlSpsCfg;
} RgrDlLchCfg;



typedef struct rgrUlLchCfg
{
  CmLteLcId lcId;
  U8 qci;
} RgrUlLchCfg;


typedef struct rgrUlLcgCfg
{
   U8 lcgId;






   U32 gbr;
   U32 mbr;
} RgrUlLcgCfg;



typedef struct rgrUlLchQciCfg
{
   CmLteLcId lcId;
   U8 qci;
   U8 lcgId;
}RgrUlLchQciCfg;



typedef struct rgrLchCfg
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   CmLteLcId lcId;
   CmLteLcType lcType;






   RgrDlLchCfg dlInfo;
   RgrUlLchQciCfg ulLchQciInfo;
   U8 lcgId;
} RgrLchCfg;


typedef struct rgrLcgCfg
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   RgrUlLcgCfg ulInfo;
} RgrLcgCfg;



typedef struct rgrCfg
{
   U8 cfgType;
   union
   {
      RgrCellCfg cellCfg;
      RgrUeCfg ueCfg;
      RgrLchCfg lchCfg;
      RgrLcgCfg lcgCfg;
      RgrSchedEnbCfg schedEnbCfg;
   } u;
} RgrCfg;



typedef struct rgrActvTime
{
   Bool pres;
   CmLteTimingInfo actvTime;
} RgrActvTime;



typedef struct rgrCellRecfg
{
   CmLteCellId cellId;
   U32 recfgTypes;
   RgrActvTime recfgActvTime;
   RgrDlHqCfg dlHqRecfg;
   RgrCfiCfg cfiRecfg;

   RgrUlTrgCqiCfg trgUlCqi;
   RgrDlCmnCodeRateCfg dlCmnCodeRate;

   RgrPuschSubBandCfg puschSubBand;
   RgrUlCmnCodeRateCfg ulCmnCodeRate;

   RgrPucchCfg pucchRecfg;
   RgrSrsCfg srsRecfg;
   RgrRachCfg rachRecfg;
   RgrDlfsCfg dlfsRecfg;




   RgrSiCfg siReCfg;

   U16 t300TmrVal;

   RgrLteAdvancedCellConfig rgrLteAdvCfg;

   Bool isDynCfiEnb;

   Bool isAutoCfgModeEnb;

   RgrCellCsgParamCfg csgParamCfg;
   RgrCellCntrlCmdCfg cntrlCmdCfg;

} RgrCellRecfg;
typedef struct rgrUeRecfg
{
   CmLteCellId cellId;
   CmLteRnti oldCrnti;
   CmLteRnti newCrnti;





   U32 ueRecfgTypes;

   RgrUeTxModeCfg txMode;
   RgrUeAprdDlCqiCfg aprdDlCqiRecfg;



   RgrUeUlHqCfg ueUlHqRecfg;
   RgrUeQosCfg ueQosRecfg;
   RgrUeTaTmrCfg ueTaTmrRecfg;





   RgrUeBsrTmrCfg ueBsrTmrRecfg;


   RgrUeUlPwrCfg ueUlPwrRecfg;


   RgrUeDrxCfg ueDrxRecfg;



   Bool isTtiBundlEnabled;

   RgrUeAckNackRepCfg ueAckNackRecfg;
   RgrUeCapCfg ueCapRecfg;
   RgrUeMeasGapCfg ueMeasGapRecfg;
   RgrCodeBookRstCfg ueCodeBookRstRecfg;


   CmLteUeCategory ueCatEnum;
   RgrUeTxAntSelCfg ulTxAntSel;




   RgrUeSpsCfg ueSpsRecfg;
   RgrUePrdDlCqiCfg cqiCfg;
   RgrUeUlSrsCfg srsCfg;
   RgrUeSrCfg srCfg;
   RgrUePuschDedCfg puschDedCfg;






   RgrUeCqiReptCfg ueCqiReptCfg;



   RgrUePdschDedCfg uePdschDedCfg;


   RgrLteAdvancedUeConfig ueLteAdvCfg;







   RgrAccessStratumRls accessStratumRls;
   U8 csgMmbrSta;
} RgrUeRecfg;


typedef struct rgrLchRecfg
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   CmLteLcId lcId;

   U8 recfgTypes;


struct dlRecfgS
   {
      RgrLchQosCfg dlQos;

      RgrLchSpsCfg dlSpsRecfg;
   } dlRecfg;

   RgrUlLchQciCfg ulLchQciInfo;
   U8 lcgId;
} RgrLchRecfg;


typedef struct rgrLcgRecfg
{
   CmLteCellId cellId;
   CmLteRnti crnti;

   struct ullcgRecfgS
   {
      U8 lcgId;





      U32 gbr;
      U32 mbr;
   } ulRecfg;
}RgrLcgRecfg;


typedef struct rgrRecfg
{
   U8 recfgType;
   union
   {
      RgrCellRecfg cellRecfg;
      RgrUeRecfg ueRecfg;
      RgrLchRecfg lchRecfg;
      RgrLcgRecfg lcgRecfg;
   } u;
} RgrRecfg;


typedef struct rgrDel
{
   U8 delType;

   union rgrDelU
   {

      struct rgrCellDelS
      {
         CmLteCellId cellId;
      } cellDel;


      struct rgrUeDelS
      {
         CmLteCellId cellId;
         CmLteRnti crnti;
      } ueDel;


      struct rgrLchDelS
      {
         CmLteCellId cellId;
         CmLteRnti crnti;
         CmLteLcId lcId;
         U8 lcgId;
      } lchDel;


      struct rgrLcgDelS
      {
         CmLteCellId cellId;
         CmLteRnti crnti;
         U8 lcgId;
      } lcgDel;
   } u;
} RgrDel;


typedef struct rgrRst
{
   CmLteCellId cellId;
   CmLteRnti crnti;
} RgrRst;

typedef enum rgrSonCfgType
{
   RGR_SON_PRB_CFG
}RgrSonCfgType;


typedef enum rgrPaVal
{
   RGR_PA_DB_NEG_6,
   RGR_PA_DB_NEG_4_77,
   RGR_PA_DB_NEG_3,
   RGR_PA_DB_NEG_1_77,
   RGR_PA_DB_0,
   RGR_PA_DB_1,
   RGR_PA_DB_2,
   RGR_PA_DB_3,
   RGR_PA_NEGTIVE_INF
}RgrPaVal;


typedef enum rgrPaLevel
{
   RGR_PA_LVL_NORMAL,
   RGR_PA_LVL_LOW,
   RGR_PA_LVL_HIGH
}RgrPaLevel;





typedef struct rgrPrbCfg
{
   U8 isSonIcicEnable;
   U8 numCellEdgeUEs;
   U8 numCellCentreUEs;
   CmLteRnti cellEdgeUe[16];
   CmLteRnti cellCentreUe[16];
   RgrPaLevel paLevelPerPrb[110];
}RgrPrbCfg;



typedef struct rgrSonCfg
{
   RgrSonCfgType cfgType;
   union
   {
      RgrPrbCfg prbCfg;
   }u;
}RgrSonCfg;


typedef struct rgrCfgReqInfo
{

   U8 action;
   union
   {
      RgrCfg cfgInfo;
      RgrRecfg recfgInfo;
      RgrDel delInfo;
      RgrRst rstInfo;
      RgrSonCfg sonCfg;



   } u;
} RgrCfgReqInfo;







typedef struct rgrTtiIndInfo
{
   CmLteCellId cellId;
   U16 sfn;
} RgrTtiIndInfo;
typedef struct rgrSiCfgReqInfo
{
   CmLteCellId cellId;
   RgrSiCfgType cfgType;
   U8 siId;

   Buffer *pdu;
}RgrSiCfgReqInfo;





typedef struct rgrWarningSiCfgReqInfo
{
   CmLteCellId cellId;
   U8 siId;
   CmLListCp siPduLst;
}RgrWarningSiCfgReqInfo;

typedef struct rgrSegmentInfo
{
   CmLList cmasSegPduLstLnk;
   Buffer* pdu;
}RgrSegmentInfo;
typedef struct rgrUeStaIndInfo
{
   CmLteCellId cellId;
   CmLteRnti crnti;
   U8 status;
}RgrUeStaIndInfo;
typedef struct rgrLoadInfReqInfo
{
   CmLteCellId cellId;
   U8 rgrCcPHighStartRb;
   U8 rgrCcPHighEndRb;
}RgrLoadInfReqInfo;
typedef S16 (*RgrBndReq) ( Pst* pst, SuId suId, SpId spId)


                              ;
typedef S16 (*RgrTtiInd) ( Pst* pst, SuId suId, RgrTtiIndInfo *ttiInd)


                                 ;
typedef S16 (*RgrBndCfm) ( Pst* pst, SuId suId, U8 status)


                                ;
typedef S16 (*RgrUbndReq) ( Pst* pst, SpId spId, Reason reason)


                                ;
typedef S16 (*RgrCfgReq) ( Pst* pst, SpId spId, RgrCfgTransId transId, RgrCfgReqInfo * cfgReqInfo)



                                    ;
typedef S16 (*RgrCfgCfm) ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 status)



                                ;
typedef S16 (*RgrSiCfgReq) ( Pst *pst, SpId spId, RgrCfgTransId transId, RgrSiCfgReqInfo *siCfgReq)



                                ;
typedef S16 (*RgrSiCfgCfm) ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 status)



                                ;
typedef S16 (*RgrWarningSiCfgReq) ( Pst *pst, SpId spId, RgrCfgTransId transId, RgrWarningSiCfgReqInfo *warningSiCfgReq)



                                             ;
typedef S16 (*RgrWarningSiCfgCfm) ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 siId, U8 status)




                                ;
typedef S16 (*RgrWarningSiStopReq) ( Pst *pst, SpId spId, RgrCfgTransId transId, U8 siId )



                            ;
typedef S16 (*RgrLoadInfReq) ( Pst *pst, SpId spId, RgrCfgTransId transId, RgrLoadInfReqInfo *loadInfReq)



                                          ;






typedef S16 (*RgrStaInd) ( Pst* pst, SuId suId, RgrStaIndInfo *staInd)


                                 ;



typedef S16 (*RgrLoadInfInd) ( Pst* pst, SuId suId, RgrLoadInfIndInfo *loadInfInd)


                                     ;


typedef S16 (*RgrUeStaInd) ( Pst* pst, SuId suId, RgrUeStaIndInfo *staInd)


                                   ;
extern S16 RgUiRgrBndReq ( Pst* pst, SuId suId, SpId spId )



  ;
extern S16 RgUiRgrTtiInd ( Pst* pst, SuId suId, RgrTtiIndInfo *ttiInd )



  ;



extern S16 cmPkRgrSpsCellCfg ( RgrSpsCellCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrSpsDlCellCfg ( RgrSpsCellCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeSpsDlCfg ( RgrUeSpsDlCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeSpsDlCfg ( RgrUeSpsDlCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeSpsUlCfg ( RgrUeSpsUlCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeSpsUlCfg ( RgrUeSpsUlCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeSpsCfg ( RgrUeSpsCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeSpsCfg ( RgrUeSpsCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrLchSpsCfg ( RgrLchSpsCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrLchSpsCfg ( RgrLchSpsCfg *param, Buffer *mBuf )


  ;


extern S16 cmPkRgrUlLchCfg ( RgrUlLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUlLchCfg ( RgrUlLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUlLchQciCfg ( RgrUlLchQciCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUlLchQciCfg ( RgrUlLchQciCfg *param, Buffer *mBuf )


  ;





extern S16 cmPkRgrUeCqiReptCfg ( RgrUeCqiReptCfg *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrUeCqiReptCfg ( RgrUeCqiReptCfg *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrSubBandCqiInfo ( RgrSubBandCqiInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkRgrStaInd ( Pst* pst, SuId suId, RgrStaIndInfo* staInd )



  ;

extern S16 cmUnpkRgrStaInd ( RgrStaInd func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrStaIndInfo ( RgrStaIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrStaIndInfo ( RgrStaIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkRgrUeCqiInfo ( RgrUeCqiInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrUeCqiInfo ( RgrUeCqiInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkRgrUeCqiRept ( RgrUeCqiRept *param, Buffer *mBuf )


  ;

extern S16 cmPkRgrSubBandCqiInfo ( RgrSubBandCqiInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrUeCqiRept ( RgrUeCqiRept *param, Buffer *mBuf )


  ;



extern S16 cmPkRgrLoadInfInd ( Pst* pst, SuId suId, RgrLoadInfIndInfo* loadInfInd )



  ;

extern S16 cmUnpkRgrLoadInfInd ( RgrLoadInfInd func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrLoadInfIndInfo ( RgrLoadInfIndInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrLoadInfIndInfo ( RgrLoadInfIndInfo *param, Pst *pst, Buffer *mBuf )



  ;



extern S16 cmPkRgrUePdschDedCfg ( RgrUePdschDedCfg *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrUePdschDedCfg ( RgrUePdschDedCfg *param, Buffer *mBuf )


  ;

extern S16 cmPkRgrUepACfg ( RgrUepACfg *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrUepACfg ( RgrUepACfg *param, Buffer *mBuf )


  ;
extern S16 RgUiRgrBndCfm ( Pst* pst, SuId suId, U8 status )



  ;
extern S16 RgUiRgrUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;
extern S16 RgUiRgrCfgReq ( Pst* pst, SpId spId, RgrCfgTransId transId, RgrCfgReqInfo * cfgReqInfo )




  ;
extern S16 RgUiRgrCfgCfm ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 status )




  ;
extern S16 RgUiRgrSiCfgReq ( Pst *pst, SpId spId, RgrCfgTransId transId, RgrSiCfgReqInfo *siCfgReq )




  ;
extern S16 RgUiRgrSiCfgCfm ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 status )




  ;
extern S16 RgUiRgrWarningSiCfgReq ( Pst *pst, SpId spId, RgrCfgTransId transId, RgrWarningSiCfgReqInfo *WarningSiCfgReqInfo )




  ;
extern S16 RgUiRgrWarningSiCfgCfm ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 siId, U8 status )





  ;
extern S16 RgUiRgrWarningSiStopReq ( Pst *pst, SpId spId, RgrCfgTransId transId, U8 siId )




  ;
extern S16 RgUiRgrLoadInfReq ( Pst *pst, SpId spId, RgrCfgTransId transId, RgrLoadInfReqInfo *loadInfReq )




  ;
extern S16 RgUiRgrStaInd ( Pst* pst, SuId suId, RgrStaIndInfo *staInd )



  ;

extern S16 RgUiRgrUeStaInd ( Pst *pst, SuId suId, RgrUeStaIndInfo *ueStaInd )



  ;
extern S16 RgUiRgrLoadInfInd ( Pst* pst, SuId suId, RgrLoadInfIndInfo *loadInfInd )



  ;
extern S16 cmPkRgrBndReq ( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 cmUnpkRgrBndReq ( RgrBndReq func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkRgrTtiInd ( Pst* pst, SuId suId, RgrTtiIndInfo *ttiInd )



           ;
extern S16 cmPkRgrTtiIndInfo ( RgrTtiIndInfo *ttiInd, Buffer *mBuf)

                               ;

extern S16 cmUnpkRgrTtiInd ( RgrTtiInd func, Pst* pst, Buffer *mBuf )



           ;
extern S16 cmUnpkRgrTtiIndInfo ( RgrTtiIndInfo *param, Buffer *mBuf )


           ;

extern S16 cmPkRgrBndCfm ( Pst* pst, SuId suId, U8 status )



  ;

extern S16 cmUnpkRgrBndCfm ( RgrBndCfm func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;

extern S16 cmUnpkRgrUbndReq ( RgrUbndReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrCfgReq ( Pst* pst, SpId spId, RgrCfgTransId transId, RgrCfgReqInfo * cfgReqInfo )




  ;

extern S16 cmUnpkRgrCfgReq ( RgrCfgReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrCfgCfm ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 status )




  ;

extern S16 cmUnpkRgrCfgCfm ( RgrCfgCfm func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrCfgTransId ( RgrCfgTransId *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCfgTransId ( RgrCfgTransId *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrDlHqCfg ( RgrDlHqCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrDlHqCfg ( RgrDlHqCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrRntiCfg ( RgrRntiCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrRntiCfg ( RgrRntiCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrDlCmnCodeRateCfg ( RgrDlCmnCodeRateCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrDlCmnCodeRateCfg ( RgrDlCmnCodeRateCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrCfiCfg ( RgrCfiCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCfiCfg ( RgrCfiCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrPuschSubBandCfg ( RgrPuschSubBandCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrPuschSubBandCfg ( RgrPuschSubBandCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUlCmnCodeRateCfg ( RgrUlCmnCodeRateCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUlCmnCodeRateCfg ( RgrUlCmnCodeRateCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUlTrgCqiCfg ( RgrUlTrgCqiCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUlTrgCqiCfg ( RgrUlTrgCqiCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrBwCfg ( RgrBwCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrBwCfg ( RgrBwCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrPhichCfg ( RgrPhichCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrPhichCfg ( RgrPhichCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrPucchCfg ( RgrPucchCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrPucchCfg ( RgrPucchCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrSrsCfg ( RgrSrsCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrSrsCfg ( RgrSrsCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrRachCfg ( RgrRachCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrRachCfg ( RgrRachCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrSiCfg ( RgrSiCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrSiCfg ( RgrSiCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrTpcRntiCfg ( RgrTpcRntiCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrTpcRntiCfg ( RgrTpcRntiCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUlPwrCfg ( RgrUlPwrCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUlPwrCfg ( RgrUlPwrCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrPuschCfg ( RgrPuschCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrPuschCfg ( RgrPuschCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrCodeBookRstCfg ( RgrCodeBookRstCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCodeBookRstCfg ( RgrCodeBookRstCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrPreambleSetCfg ( RgrPreambleSetCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrPreambleSetCfg ( RgrPreambleSetCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrCmnLchCfg ( RgrCmnLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCmnLchCfg ( RgrCmnLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrDlfsCfg ( RgrDlfsCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrDlfsCfg ( RgrDlfsCfg *param, Buffer *mBuf )


  ;





extern S16 cmPkRgrWarningSiCfgReq ( Pst* pst, SpId spId, RgrCfgTransId transId, RgrWarningSiCfgReqInfo *warningSiCfgReqInfo )




  ;

extern S16 cmUnpkRgrWarningSiCfgReq ( RgrWarningSiCfgReq func, Pst *pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrWarningSiCfgReqInfo ( Pst *pst, RgrWarningSiCfgReqInfo *param, Buffer *mBuf )



  ;

extern S16 cmUnpkRgrWarningSiCfgReqInfo ( Pst *pst, RgrWarningSiCfgReqInfo *param, Buffer *mBuf )



  ;

extern S16 cmPkRgrWarningSiStopReq ( Pst *pst, SpId spId, RgrCfgTransId transId, U8 siId )




  ;

extern S16 cmUnpkRgrWarningSiStopReq ( RgrWarningSiStopReq func, Pst *pst, Buffer *mBuf )



  ;


extern S16 cmPkRgrWarningSiCfgCfm ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 siId, U8 status )





  ;

extern S16 cmUnpkRgrWarningSiCfgCfm ( RgrWarningSiCfgCfm func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRgrSiCfgReq ( Pst* pst, SpId spId, RgrCfgTransId transId, RgrSiCfgReqInfo * cfgReqInfo )




  ;

extern S16 cmUnpkRgrSiCfgReq ( RgrSiCfgReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrSiCfgReqInfo ( RgrSiCfgReqInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrSiCfgReqInfo ( RgrSiCfgReqInfo *param, Buffer *mBuf )


  ;

extern S16 cmPkRgrSiCfgCfm ( Pst* pst, SuId suId, RgrCfgTransId transId, U8 status )




  ;

extern S16 cmUnpkRgrSiCfgCfm ( RgrSiCfgCfm func, Pst* pst, Buffer *mBuf )



  ;





extern S16 cmPkRgrLoadInfReq ( Pst* pst, SpId spId, RgrCfgTransId transId, RgrLoadInfReqInfo * loadInfReq )




  ;

extern S16 cmUnpkRgrLoadInfReq ( RgrLoadInfReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRgrLoadInfReqInfo ( RgrLoadInfReqInfo *param, Buffer *mBuf )


  ;

extern S16 cmUnpkRgrLoadInfReqInfo ( RgrLoadInfReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrEnbPfs ( RgrEnbPfs *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrEnbPfs ( RgrEnbPfs *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrCellCfg ( RgrCellCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCellCfg ( RgrCellCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeAprdDlCqiCfg ( RgrUeAprdDlCqiCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeAprdDlCqiCfg ( RgrUeAprdDlCqiCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrSchedEnbCfg ( RgrSchedEnbCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrSchedEnbCfg ( RgrSchedEnbCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUePrdDlCqiCfg ( RgrUePrdDlCqiCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUePrdDlCqiCfg ( RgrUePrdDlCqiCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeDlCqiCfg ( RgrUeDlCqiCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeDlCqiCfg ( RgrUeDlCqiCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeMeasGapCfg ( RgrUeMeasGapCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeMeasGapCfg ( RgrUeMeasGapCfg *param, Buffer *mBuf )


  ;

extern S16 cmPkRgrDrxLongCycleOffst ( RgrDrxLongCycleOffst *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrDrxLongCycleOffst ( RgrDrxLongCycleOffst *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrDrxShortDrx ( RgrDrxShortDrx *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrDrxShortDrx ( RgrDrxShortDrx *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeDrxCfg ( RgrUeDrxCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeDrxCfg ( RgrUeDrxCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeCapCfg ( RgrUeCapCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeCapCfg ( RgrUeCapCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeAckNackRepCfg ( RgrUeAckNackRepCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeAckNackRepCfg ( RgrUeAckNackRepCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeTxModeCfg ( RgrUeTxModeCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeTxModeCfg ( RgrUeTxModeCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeUlHqCfg ( RgrUeUlHqCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeUlHqCfg ( RgrUeUlHqCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeGrpPwrCfg ( RgrUeGrpPwrCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeGrpPwrCfg ( RgrUeGrpPwrCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeUlPwrCfg ( RgrUeUlPwrCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeUlPwrCfg ( RgrUeUlPwrCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeQosCfg ( RgrUeQosCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeQosCfg ( RgrUeQosCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeTaTmrCfg ( RgrUeTaTmrCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeTaTmrCfg ( RgrUeTaTmrCfg *param, Buffer *mBuf )


  ;





extern S16 cmPkRgrUeBsrTmrCfg ( RgrUeBsrTmrCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeBsrTmrCfg ( RgrUeBsrTmrCfg *param, Buffer *mBuf )


  ;


extern S16 cmPkRgrUeCfg ( RgrUeCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeCfg ( RgrUeCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrLchQosCfg ( RgrLchQosCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrLchQosCfg ( RgrLchQosCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrDlLchCfg ( RgrDlLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrDlLchCfg ( RgrDlLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUlLcgCfg ( RgrUlLcgCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUlLcgCfg ( RgrUlLcgCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrLchCfg ( RgrLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrLchCfg ( RgrLchCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrLcgCfg ( RgrLcgCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrLcgCfg ( RgrLcgCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrCfg ( RgrCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCfg ( RgrCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrActvTime ( RgrActvTime *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrActvTime ( RgrActvTime *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrCellRecfg ( RgrCellRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCellRecfg ( RgrCellRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeRecfg ( RgrUeRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeRecfg ( RgrUeRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrLchRecfg ( RgrLchRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrLchRecfg ( RgrLchRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrLcgRecfg ( RgrLcgRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrLcgRecfg ( RgrLcgRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrRecfg ( RgrRecfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrRecfg ( RgrRecfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrDel ( RgrDel *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrDel ( RgrDel *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrRst ( RgrRst *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrRst ( RgrRst *param, Buffer *mBuf )


  ;

extern S16 cmPkRgrSonCfg ( RgrSonCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrSonCfg ( RgrSonCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrSonPrbCfg ( RgrPrbCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrSonPrbCfg ( RgrPrbCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrCfgReqInfo ( RgrCfgReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCfgReqInfo ( RgrCfgReqInfo *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUeTxAntSelCfg ( RgrUeTxAntSelCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUeTxAntSelCfg ( RgrUeTxAntSelCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrUePuschDedCfg ( RgrUePuschDedCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrUePuschDedCfg ( RgrUePuschDedCfg *param, Buffer *mBuf )


  ;


extern S16 cmPkRgrUeDlPCqiSetup ( RgrUeDlPCqiSetup *param, Buffer *mBuf )



  ;

extern S16 cmUnpkRgrUeDlPCqiSetup ( RgrUeDlPCqiSetup *param, Buffer *mBuf )



  ;

extern S16 cmPkRgrUeUlSrsSetupCfg ( RgrUeUlSrsSetupCfg *param, Buffer *mBuf )



  ;

extern S16 cmUnpkRgrUeUlSrsSetupCfg ( RgrUeUlSrsSetupCfg *param, Buffer *mBuf )



  ;

extern S16 cmPkRgrUeSrSetupCfg ( RgrUeSrSetupCfg *param, Buffer *mBuf )



  ;

extern S16 cmUnpkRgrUeSrSetupCfg ( RgrUeSrSetupCfg *param, Buffer *mBuf )



  ;

extern S16 cmPkRgrUeSrCfg ( RgrUeSrCfg *param, Buffer *mBuf )



  ;

extern S16 cmUnpkRgrUeSrCfg ( RgrUeSrCfg *param, Buffer *mBuf )



  ;

extern S16 cmPkRgrUeUlSrsCfg ( RgrUeUlSrsCfg *param, Buffer *mBuf )



  ;

extern S16 cmUnpkRgrUeUlSrsCfg ( RgrUeUlSrsCfg *param, Buffer *mBuf )



  ;
extern S16 NxLiRgrUeStaInd ( Pst* pst, SuId suId, RgrUeStaIndInfo *ueStaInd )



  ;

extern S16 cmPkRgrUeStaInd ( Pst* pst, SuId suId, RgrUeStaIndInfo* ueStaInd )




  ;

extern S16 cmUnpkRgrUeStaInd ( RgrUeStaInd func, Pst *pst, Buffer *mBuf )




  ;

extern S16 cmPkRgrUeStaIndInfo ( RgrUeStaIndInfo *param, Buffer *mBuf )



  ;


extern S16 cmUnpkRgrUeStaIndInfo ( RgrUeStaIndInfo *param, Buffer *mBuf )



  ;



extern S16 cmPkRgrLteAdvancedUeConfig ( RgrLteAdvancedUeConfig *param, Buffer *mBuf )


              ;

extern S16 cmUnpkRgrLteAdvancedUeConfig ( RgrLteAdvancedUeConfig *param, Buffer *mBuf )


              ;

extern S16 cmPkRgrAbsConfig ( RgrAbsConfig *param, Buffer *mBuf )


              ;

extern S16 cmUnpkRgrAbsConfig ( RgrAbsConfig *param, Buffer *mBuf )


              ;

extern S16 cmPkRgrSfrConfig ( RgrSfrConfig *param, Buffer *mBuf )


              ;

extern S16 cmUnpkRgrSfrConfig ( RgrSfrConfig *param, Buffer *mBuf )


              ;

extern S16 cmPkRgrCellLteAdvancedFeatureCfg ( RgrLteAdvancedCellConfig *param, Buffer *mBuf )


              ;

extern S16 cmUnpkRgrCellLteAdvancedFeatureCfg ( RgrLteAdvancedCellConfig *param, Buffer *mBuf )


              ;

extern S16 cmPkRgrDsfrConfig ( RgrDsfrConfig *param, Buffer *mBuf )


           ;

extern S16 cmUnpkRgrDsfrConfig ( RgrDsfrConfig *param, Buffer *mBuf )


           ;


extern S16 cmPkRgrCellCsgParamCfg ( RgrCellCsgParamCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCellCsgParamCfg ( RgrCellCsgParamCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRgrCellCntrlCmdCfg ( RgrCellCntrlCmdCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRgrCellCntrlCmdCfg ( RgrCellCntrlCmdCfg *param, Buffer *mBuf )


  ;
typedef struct rgmPrbRprtCfg
{
   U16 usPrbAvgPeriodicty;
   U8 bConfigType;
   U8 bCellId;
}RgmPrbRprtCfg;


typedef struct rgmPrbRptPerQci
{
   U8 bQci;
   U8 bAvgPrbUlUsage;
   U8 bAvgPrbDlUsage;
}RgmPrbRptPerQci;

typedef struct rgmPrbRprtInd
{
   RgmPrbRptPerQci stQciPrbRpts[4];

   U8 bCellId;




   U8 bPrbUsageMask;
}RgmPrbRprtInd;

typedef enum
{
   RGM_TXN_MODE1,
   RGM_TXN_MODE2,
   RGM_TXN_MODE3,
   RGM_TXN_MODE4,
   RGM_TXN_MODE5,
   RGM_TXN_MODE6,
   RGM_TXN_MODE7,
   RGM_TXN_MODE8
} RgmTxnMode;

typedef struct rgmTransModeInd
{
   RgmTxnMode eMode;
   U16 usCrnti;
   U8 bCellId;
}RgmTransModeInd;




typedef S16 (*RgmBndReq) ( Pst* pst, SuId suId, SpId spId)


                              ;

typedef S16 (*RgmUbndReq) ( Pst* pst, SpId spId, Reason reason)


                                ;


typedef S16 (*RgmBndCfm) ( Pst* pst, SuId suId, U8 status)


                                ;


typedef S16 (*RgmCfgPrbRprtFptr) ( Pst* pst, SpId spId, RgmPrbRprtCfg * prbRprtCfg)


                                    ;


typedef S16 (*RgmPrbRprtIndFptr) ( Pst* pst, SuId suId, RgmPrbRprtInd * prbRprtInd)


                                   ;

typedef S16 (*RgmTransModeIndFptr) ( Pst* pst, SuId suId, RgmTransModeInd * transModeInd)


                                      ;







extern S16 RgUiRgmBndReq (Pst* pst,SuId suId,SpId spId);






extern S16 RgUiRgmUbndReq (Pst* pst,SpId spId,Reason reason);







extern S16 RgUiRgmBndCfm (Pst* pst,SuId suId,U8 status);







extern S16 RgUiRgmCfgPrbRprt (Pst* pst,SuId suId,RgmPrbRprtCfg *prbRprtCfg);







extern S16 RgUiRgmPrbRprtInd (Pst* pst,SuId suId,RgmPrbRprtInd *prbRprtInd);





extern S16 RmLiRgmBndReq ( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 RmLiRgmUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;


extern S16 RmLiRgmBndCfm ( Pst* pst, SuId suId, U8 status )



  ;


extern S16 RmLiRgmCfgPrbRprt ( Pst* pst, SpId spId, RgmPrbRprtCfg* prbRprtCfg )



  ;


extern S16 RmLiRgmPrbRprtInd ( Pst* pst, SuId suId, RgmPrbRprtInd* prbRprtInd )



  ;


extern S16 RmLiRgmTransModeInd ( Pst* pst, SuId suId, RgmTransModeInd* transModeInd )



  ;




extern S16 cmPkLwLcRgmBndReq ( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 cmUnpkLwLcRgmBndReq ( RgmBndReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkLwLcRgmUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;

extern S16 cmUnpkLwLcRgmUbndReq ( RgmUbndReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkLwLcRgmBndCfm ( Pst* pst, SuId suId, U8 status )



  ;


extern S16 cmUnpkLwLcRgmBndCfm ( RgmBndCfm func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkLwLcRgmCfgPrbRprt ( Pst* pst, SpId spId, RgmPrbRprtCfg * prbRprtCfg )



  ;


extern S16 cmUnpkLwLcRgmCfgPrbRprt ( RgmCfgPrbRprtFptr func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkLwLcRgmPrbRprtInd ( Pst* pst, SuId suId, RgmPrbRprtInd * prbRprtInd )



  ;


extern S16 cmUnpkLwLcRgmPrbRprtInd ( RgmPrbRprtIndFptr func, Pst* pst, Buffer *mBuf )



  ;




extern S16 cmPkRgmBndReq ( Pst* pst, SuId suId, SpId spId )



  ;

extern S16 cmUnpkRgmBndReq ( RgmBndReq func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRgmUbndReq ( Pst* pst, SpId spId, Reason reason )



  ;

extern S16 cmUnpkRgmUbndReq ( RgmUbndReq func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRgmBndCfm ( Pst* pst, SuId suId, U8 status )



  ;


extern S16 cmUnpkRgmBndCfm ( RgmBndCfm func, Pst* pst, Buffer *mBuf )



  ;


extern S16 cmPkRgmCfgPrbRprt ( Pst* pst, SpId spId, RgmPrbRprtCfg * prbRprtCfg )



  ;


extern S16 cmPkCfgPrbRprt ( RgmPrbRprtCfg * prbRprtCfg, Buffer *mBuf )


  ;

extern S16 cmPkPrbRprtInd ( RgmPrbRprtInd * prbRprtInd, Buffer *mBuf )


  ;



extern S16 cmUnpkRgmCfgPrbRprt ( RgmCfgPrbRprtFptr func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmUnPkCfgPrbRprt ( RgmPrbRprtCfg * prbRprtCfg, Buffer *mBuf )


  ;



extern S16 cmPkRgmPrbRprtInd ( Pst* pst, SuId suId, RgmPrbRprtInd * prbRprtInd )



  ;


extern S16 cmUnpkPrbRprtInd ( RgmPrbRprtInd * prbRprtInd, Buffer *mBuf )


  ;

extern S16 cmPkTransModeInd ( RgmTransModeInd *transModeInd, Buffer *mBuf )


  ;

extern S16 cmUnpkTransModeInd ( RgmTransModeInd *transModeInd, Buffer *mBuf )


  ;
extern S16 cmPkRgmTransModeInd ( Pst* pst, SuId suId, RgmTransModeInd *transModeInd )



  ;


extern S16 cmUnpkRgmTransModeInd ( RgmTransModeIndFptr func, Pst* pst, Buffer *mBuf )



           ;



extern S16 cmUnpkRgmPrbRprtInd ( RgmPrbRprtIndFptr func, Pst* pst, Buffer *mBuf )



  ;

extern S16 cmPkRgmPrbQciRpt ( RgmPrbRptPerQci *qciPrbRprt, Buffer *mBuf )


  ;

extern S16 cmUnpkRgmPrbQciRpt ( RgmPrbRptPerQci *qciPrbRprt, Buffer *mBuf )


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








typedef struct rgSchHistNode
{
   U32 line;
   S8* file;
   const S8* func;
   Void * dbgVal;


   U32 action;
}RgSchHistNode;






typedef struct rgSchHistInfo
{
   U32 histCount;
   RgSchHistNode hist[50];
}RgSchHistInfo;
typedef TfuDciFormat1aInfo RgDciFmt1AInfo;
typedef TfuRaReqInfo RgTfuRaReqInfo;
typedef TfuSubbandCqiInfo RgSchSubbandCqiInfo;
typedef TfuHqIndInfo RgTfuHqIndInfo;
typedef TfuHqInfo RgTfuHqInfo;





typedef struct rgSchQciCb RgSchQciCb;
typedef struct rgSchUeCb RgSchUeCb;
typedef struct rgSchCellCb RgSchCellCb;
typedef struct rgSchErrInfo RgSchErrInfo;
typedef struct rgSchUlAlloc RgSchUlAlloc;
typedef struct rgSchUlRetxAlloc RgSchUlRetxAlloc;
typedef struct rgSchUlHqProcCb RgSchUlHqProcCb;
typedef struct rgSchDlHqProcCb RgSchDlHqProcCb;


typedef struct rgSchDlHqTbCb RgSchDlHqTbCb;
typedef struct rgSchLcgCb RgSchLcgCb;
typedef struct rgSchDlHqEnt RgSchDlHqEnt;
typedef struct rgSchRaCb RgSchRaCb;
typedef struct _rgSchCb RgSchCb;
typedef struct rgSchUlLcCb RgSchUlLcCb;
typedef struct rgSchDlLcCb RgSchDlLcCb;
typedef struct _rgSchdApis RgSchdApis;






typedef struct rgSchDlSfAllocInfo RgSchDlSfAllocInfo;


typedef struct rgSchUeCellInfo RgSchUeCellInfo;




struct _rgSchdApis
{
   S16 (*rgSCHRgrUeCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *cfg, RgSchErrInfo *err)
                               ;
   S16 (*rgSCHRgrUeRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *recfg, RgSchErrInfo *err)
                               ;
   Void (*rgSCHFreeUe) (RgSchCellCb *cell, RgSchUeCb *ue);
   S16 (*rgSCHRgrCellCfg) (RgSchCellCb *cell, RgrCellCfg *cfg, RgSchErrInfo *err)
                               ;
   S16 (*rgSCHRgrCellRecfg) (RgSchCellCb *cell, RgrCellRecfg *recfg, RgSchErrInfo *err)
                               ;
   Void (*rgSCHFreeCell) (RgSchCellCb *cell);
   S16 (*rgSCHRgrLchCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dl, RgrLchCfg *cfg, RgSchErrInfo *errInfo)
                                                                    ;
   S16 (*rgSCHRgrLcgCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg, RgrLcgCfg *cfg, RgSchErrInfo *errInfo)
                                                                    ;
   S16 (*rgSCHRgrLchRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dl, RgrLchRecfg *recfg, RgSchErrInfo *errInfo)

                                   ;
   S16 (*rgSCHRgrLcgRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg, RgrLcgRecfg *recfg, RgSchErrInfo *errInfo)
                                                                        ;
   Void (*rgSCHFreeDlLc) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc);
   Void (*rgSCHFreeLcg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg);
   S16 (*rgSCHRgrLchDel) (RgSchCellCb *cell, RgSchUeCb *ue,CmLteLcId lcId, U8 lcgId)
                                       ;
   Void (*rgSCHActvtUlUe) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHActvtDlUe) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHHdlUlTransInd) (RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo timingInfo)
                                        ;
   Void (*rgSCHUeReset) (RgSchCellCb *cell, RgSchUeCb *ue);
   S16 (*rgSCHUpdBsrShort) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *ulLcg, U8 bsr, RgSchErrInfo *err);
   S16 (*rgSCHUpdBsrTrunc) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *ulLcg, U8 bsr, RgSchErrInfo *err);
   S16 (*rgSCHUpdBsrLong) (RgSchCellCb *cell, RgSchUeCb *ue, U8 bsArr[], RgSchErrInfo *err);
   S16 (*rgSCHUpdPhr) (RgSchCellCb *cell, RgSchUeCb *ue, U8 phr, RgSchErrInfo *err);
   S16 (*rgSCHUpdExtPhr) (RgSchCellCb *cell, RgSchUeCb *ue, RgInfExtPhrCEInfo * extPhr, RgSchErrInfo *err);




   S16 (*rgSCHContResUlGrant) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchErrInfo *err);
   S16 (*rgSCHSrRcvd) (RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo, RgSchErrInfo *err);
   S16 (*rgSCHTti) (RgSchCellCb *cell, RgSchErrInfo *err);
   Void (*rgSCHUlCqiInd) ( RgSchCellCb *cell, RgSchUeCb *ue, TfuUlCqiRpt *ulCqiInfo);
   Void (*rgSCHPucchDeltaPwrInd) ( RgSchCellCb *cell, RgSchUeCb *ue, S8 delta)
                                     ;
   S16 (*rgSCHlUeReset) ( RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHDlDedBoUpd) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *svc);

   Void (*rgSCHUlRecMsg3Alloc) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchRaCb *raCb)
                             ;
   Void (*rgSCHUlHqProcForUe) (RgSchCellCb *cell, CmLteTimingInfo frm, RgSchUeCb *ue, RgSchUlHqProcCb **procRef)
                                                       ;
   RgSchUlAlloc *(*rgSCHFirstRcptnReq) (RgSchCellCb *cell);
   RgSchUlAlloc *(*rgSCHNextRcptnReq) (RgSchCellCb *cell, RgSchUlAlloc *alloc)
                                 ;
   RgSchUlAlloc *(*rgSCHFirstHqFdbkAlloc) (RgSchCellCb *cell, U8 idx);
   RgSchUlAlloc *(*rgSCHNextHqFdbkAlloc) (RgSchCellCb *cell, RgSchUlAlloc *alloc,U8 idx)
                                        ;
   Void (*rgSCHDlProcAddToRetx) (RgSchCellCb *cell,RgSchDlHqProcCb *hqP);
   Void (*rgSCHDlCqiInd) (RgSchCellCb *cell, RgSchUeCb *ue, Bool isPucchInfo, Void *dlCqi, CmLteTimingInfo timingInfo)
                                                                       ;


Void (*rgSCHSrsInd) (RgSchCellCb *cell, RgSchUeCb *ue, TfuSrsRpt* srsInd, CmLteTimingInfo timingInfo)
                                                        ;


   Void (*rgSCHDlTARpt) (RgSchCellCb *cell, RgSchUeCb *ue);


   Void (*rgSCHDlRlsSubFrm) (RgSchCellCb *cell, CmLteTimingInfo subFrm);


   Void (*rgSCHHdlCrntiCE) (RgSchCellCb *cell, RgSchUeCb * ue);
   Void (*rgSCHDlProcAck) (RgSchCellCb *cell, RgSchDlHqProcCb *hqP);
   Void (*rgSCHDlProcDtx) (RgSchCellCb *cell, RgSchDlHqProcCb *hqP);
   Void (*rgSCHDlRelPdcchFbk) (RgSchCellCb *cell, RgSchUeCb * ue, U8 isAck)
                      ;
   Void (*rgSCHUlSpsRelInd) (RgSchCellCb *cell, RgSchUeCb * ue, Bool isExplRel)
                            ;

   Void (*rgSCHUlSpsActInd) (RgSchCellCb *cell, RgSchUeCb * ue, U16 sduSuze)
                         ;

   Void (*rgSCHUlCrcFailInd) (RgSchCellCb *cell, RgSchUeCb * ue, CmLteTimingInfo crcTime)
                                       ;
   Void (*rgSCHUlCrcInd) (RgSchCellCb *cell, RgSchUeCb * ue, CmLteTimingInfo crcTime)
                                       ;

   Void (*rgSCHDrxStrtInActvTmrInUl) (RgSchCellCb *cell);
   Void (*rgSCHUpdUeDataIndLcg) (RgSchCellCb *cell, RgSchUeCb * ue, RgInfUeDatInd *datInd);





};







typedef RgrUePrdDlCqiCfg RgSchUeDlPCqiCfg;





typedef RgrUeDlPCqiSetup RgSchUeDlPCqiSetup;






typedef RgrUeUlSrsCfg RgSchUeUlSrsCfg;







typedef RgrUeUlSrsSetupCfg RgSchUeSrsUlSetupCfg;





typedef RgrUeSrCfg RgSchUeSrCfg;





typedef RgrUeSrSetupCfg RgSchUeSrSetupCfg;







typedef struct rgSchPerPucchCb
{
   CmLListCp srLst;
   CmLListCp srsLst;
   CmLListCp cqiLst;
   CmLListCp riLst;
}RgSchPerPucchCb;




typedef struct rgSchUePCqiSrsSrCfgIdxTbl
{
   U16 min;
   U16 max;
   U16 peri;
   U16 offset;
}RgSchUePCqiSrsSrCfgIdxTbl;






typedef struct rgSchUeSrsCfgIdxTbl
{
   U16 min;
   U16 max;
   U16 peri;
   U16 offset1;
   U16 offset2;

}RgSchUeSrsCfgIdxTbl;






typedef struct rgSchUeSrsCb
{
    RgSchUeUlSrsCfg srsCfg;
    U16 peri;
    U16 offset;
    U16 nSrsTrIdx;



    CmLList srsLstEnt;
    U8 selectedAnt;
    U16 srsDist;
    Bool srsRecpPrcsd;


}RgSchUeSrsCb;
typedef struct rgSchUeBwSubSzBwParts
{
   U8 rbStart;
   U8 rbEnd;
   U8 subSize;
   U8 bwParts;

}RgSchUeBwSubSzBwParts;
typedef struct rgSchUePCqiCb
{
   RgrUePrdDlCqiCfg cqiCfg;
   U16 cqiPeri;
   U16 cqiOffset;
   U16 riOffset;
   U16 riPeri;
   U16 nCqiTrIdx;
   U16 nRiTrIdx;


   U16 riDist;
   U16 h;
   U8 riNumBits;
   Bool isWb;

   U8 bpIdx;
   U8 label;
   U8 J;

   CmLList cqiLstEnt;

   CmLList riLstEnt;

   Bool invalidateCqi;
   U8 perRiVal;
   Bool riRecpPrcsd;
   RgSchUeCellInfo *servCellInfo;

   RgSchHistInfo histElem;
}RgSchUePCqiCb;






typedef struct rgSchUeSrCfgIdx
{
   U16 sIsr;
   U16 eIsr;
   U16 peri;
   U16 offset;
}RgSchUeSrCfgIdx;
typedef struct rgSchUeSrCb
{
    RgSchUeSrCfg srCfg;
    U16 offset;
    U16 peri;

    U16 nSrTrIdx;






   CmLList srLstEnt;

}RgSchUeSrCb;
typedef enum rgSchCqiReqField
{
   RG_SCH_APCQI_NO = 0,
   RG_SCH_APCQI_SERVING_CC,
   RG_SCH_APCQI_1ST_SERVING_CCS_SET,
   RG_SCH_APCQI_2ND_SERVING_CCS_SET
}RgSchCqiReqField;



typedef struct rgSchUeACqiCb
{
 RgrUeAprdDlCqiCfg aCqiCfg;
 U8 L;

 U8 N;
 U8 M;
 U8 riNumBits;
 U8 k;
 U8 cqiPmiSzR1;
 U8 cqiPmiSzRn1;
 U32 aCqiTrigWt;
 RgSchCqiReqField cqiReqField;

}RgSchUeACqiCb;

typedef enum
{
   RG_SCH_FDD_PCQI_TBL = 0,
   RG_SCH_TDD_PCQI_TBL,
   RG_SCH_RI_TBL,
   RG_SCH_FDD_SRS_TBL,
   RG_SCH_TDD_SRS_TBL,
   RG_SCH_SR_TBL
} RgSchPerTbl;





typedef U8 RgSchFddCellSpSrsSubfrmTbl[16][10];
typedef struct rgSchUlIMcsInfo
{
   U8 qm;
   U8 iTbs;
} RgSchUlIMcsTbl[29];
extern RgSchUlIMcsTbl rgUlIMcsTbl;

typedef struct rgSchUeCatTbl
{
   U32 maxUlBits;




   U32 maxDlBits[2];




   U32 maxSftChBits;
   Bool ul64qamSup;


   U32 maxDlTbBits;


   U8 maxTxLyrs;


} RgSchUeCatTbl[8 + 1];
extern RgSchUeCatTbl rgUeCatTbl;



typedef U32 RgSchTbSzTbl[2][27][110];






typedef U8 RgSchRaPrmblToRaFrmTbl[3 +1];

extern RgSchRaPrmblToRaFrmTbl rgRaPrmblToRaFrmTbl;

extern U8 rgRvTable[4];

typedef struct rgDciFmt
{
   U8 dciType;
   union
   {
      RgDciFmt1AInfo dci1a;
   } dci;
} RgDciFmt;

typedef enum rgSchPdcchSearchSpace
{
   RG_SCH_UE_SPECIFIC_SEARCH_SPACE,
   RG_SCH_CMN_SEARCH_SPACE,
}RgSchPdcchSearchSpace;





typedef struct rgSchPdcch {
   U8 nCce;
   CmLteAggrLvl aggrLvl;
   TfuDciInfo dci;
   U16 rnti;






   CmLteTimingInfo relFbkTiming;

   Bool isSpsRnti;
   U16 crnti;

   CmLList lnk;
   RgSchUeCb *ue;
   RgSchPdcchSearchSpace pdcchSearchSpace;
   U8 dciNumOfBits;
} RgSchPdcch;





typedef struct rgSchPdcchInfo {
   U8 *map;
   U8 currCfi;
   U16 nCce;
   CmLListCp pdcchs;
} RgSchPdcchInfo;

typedef struct rgSchPhich
{
   CmLList lnk;
   U8 hqFeedBack;
   U8 rbStart;
   U8 nDmrs;

   Bool isForMsg3;



} RgSchPhich;

typedef struct rgSchPhichInfo
{
   CmLListCp phichs;
} RgSchPhichInfo;

typedef struct rgSchBcchTb
{
   RgSchPdcch *pdcch;
   Buffer *tb;
   U16 tbSize;
} RgSchBcchTb;

typedef struct rgSchPcchTb
{
   RgSchPdcch *pdcch;
   Buffer *tb;
   U16 tbSize;
} RgSchPcchTb;

typedef struct rgSchRaRspAlloc
{
   U16 raRnti;
   U32 tbSz;
   TknU8 backOffInd;
   CmLListCp raRspLst;
   CmLListCp contFreeUeLst;
   RgSchPdcch *pdcch;
}RgSchRaRspAlloc;

typedef struct rgSchBchTb
{
   Buffer *tb;
   U16 tbSize;
}RgSchBchTb;






struct rgSchDlSfAllocInfo
{
  U32 raType0Mask;
  U32 raType1Mask[4];

  U32 raType1UsedRbs[4];

  U32 nxtRbgSubset;
  U32 raType2Mask[4];

};





typedef struct rgrPwrHiCCRange
{
   U8 startRb;
   U8 endRb;
} RgrPwrHiCCRange;

typedef struct rgSchSFRTotalPoolInfo
{
   CmLListCp ccPool;

   Bool ccBwFull;
   CmLListCp cePool;

   Bool ceBwFull;
   Bool isUeCellEdge;
   Bool CERetx;
   Bool CCRetx;
   Bool CC1;
   Bool CC2;
   U8 CCPool1BwAvlbl;
   U8 CCPool2BwAvlbl;
   U8 CEPoolBwAvlbl;
}RgSchSFRTotalPoolInfo;

typedef struct rgSchSFRPoolInfo
{

   U16 poolstartRB;
   U16 poolendRB;
   U16 bw;

   U8 type2Start;
   U8 type2End;
   U8 type0End;

   U16 bwAlloced;
   Bool CCPool2Exists;
   struct rgSchSFRPoolInfo * adjCCPool;
   RgrPwrHiCCRange pwrHiCCRange;
}RgSchSFRPoolInfo;


typedef struct rgSchPuschBwInfo
{
   U8 numSb;
   U8 startRb;
}RgSchPuschBwInfo;

typedef struct rgSchDynCfiCb
{
   U8 isDynCfiEnb;
   U8 maxCfi;
   U8 switchOvrWinLen;
   U16 cceFailCnt;

   U16 *cceFailSamples;

   U16 cceFailSum;

   U16 cfiStepUpTtiCnt;

   U16 cceUsed;

   U16 lowCceCnt;


   U16 cfiStepDownTtiCnt;

   U32 cfiSwitches;
   U32 cfiIncr;
   U32 cfiDecr;

   U8 cfi2NCceTbl[3][4];

   U8 numFailSamples;

   U16 failSamplePrd;
   U16 ttiCnt;

   RgSchPuschBwInfo bwInfo[4];
   U8 pdcchSfIdx;
   U8 prevCceFailIdx;

   Bool switchOvrInProgress;
   Bool dynCfiRecfgPend;
}RgSchDynCfiCb;

typedef struct rgSchDlSf
{
   U8 cceCnt;
   Bool isCceFailure;

   U8 dlUlBothCmplt;

   U8 sfNum;
   U16 bw;
   U16 bwAlloced;
   U16 bwAssigned;

   RgSchSFRTotalPoolInfo sfrTotalPoolInfo;
   TknStrOSXL rntpInfo;


   U8 type2Start;
   U8 type2End;

   U8 type0End;

   U8 lstRbgDfct;

   Bool txDone;
   U32 numDlActvUes;
   RgSchBchTb bch;
   RgSchBcchTb bcch;
   RgSchPcchTb pcch;
   RgSchPdcchInfo pdcchInfo;
   RgSchPhichInfo phichInfo;


   CmLListCp ueLst;
   CmLListCp laaSCellUeLst;
   CmLListCp msg4HqPLst;

   U8 remUeCnt;
   Bool schdAmbrNxt;

   U8 schdCcchUe;
   RgSchRaRspAlloc raRsp[4];


   Void *dlfsSf;
   CmLListCp ackNakRepQ;


   Bool isSPSOcc;
   RgSchDlSfAllocInfo dlSfAllocInfo;
   U32 spsAllocdBw;
   RgSchPdcch *relPdcch;
   U32 schedLcCount;
   U32 totalLcCntOfSlctdUes;

   U32 totPrbReq;


  U32 beTotPrbReq;



   U8 dlIdx;




} RgSchDlSf;




typedef struct rgSchDlRbAllocRaType0
{
   U8 numDlAlloc;
   U32 dlAllocBitMask;
} RgSchDlRbAllocRaType0;





typedef struct rgSchDlRbAllocRaType1
{
   U8 numDlAlloc;
   U8 shift;

   U8 rbgSubset;
   U32 dlAllocBitMask;
} RgSchDlRbAllocRaType1;



typedef struct rgSchDlRbAllocRaType2
{
   Bool isLocal;
   U8 rbStart;
   U8 numRb;
} RgSchDlRbAllocRaType2;



typedef struct rgSchDlTbAllocInfo
{
   Bool schdlngForTb;

   Bool isDisabled;
   U32 bytesReq;

   U32 bytesAlloc;
   U8 iTbs;

   U8 imcs;

   U8 noLyr;
   RgSchDlHqTbCb *tbCb;
}RgSchDlTbAllocInfo;



typedef struct rgSchMimoAllocInfo
{
   Bool hasNewTxData;


   Bool swpFlg;

   U8 precIdxInfo;
   U8 numTxLyrs;
}RgSchMimoAllocInfo;




typedef struct rgSchLaaTBInfo
{
   CmLList laaTbsLnk;
   U8 procId;
   U8 numTBs;
   U32 tbSz[2];
   U16 hqPStamp;



   RgSchUeCb *ue;
   RgSchCellCb *laaSCell;
}RgSchLaaTBInfo;



typedef struct rgSchLaaDlRbAlloc
{
   Bool isLaaTB;

   RgSchLaaTBInfo *laaTBInfo;

}RgSchLaaDlRbAlloc;



typedef struct rgSchDlRbAlloc
{
   CmLteRnti rnti;

   U8 rbsReq;

   RgSchDlSf *dlSf;

   TfuDciFormat dciFormat;
   U8 raType;
   RgSchPdcch *pdcch;
   union allocInfoU
   {
      RgSchDlRbAllocRaType0 raType0;


      RgSchDlRbAllocRaType1 raType1;


      RgSchDlRbAllocRaType2 raType2;
   } allocInfo;
   U8 rbsAlloc;
   U8 numRapids;

   U8 nPrb;
   U32 raIndex;
   Bool schdFirst;

   U8 biEstmt;
   RgSchMimoAllocInfo mimoAllocInfo;
   RgSchDlTbAllocInfo tbInfo[2];



   U8 cqiForTx;

   RgSchDlSfAllocInfo resAllocInfo;


   Bool isSchdBySps;

   CmLteTimingInfo spsSchdTime;



   RgSchLaaDlRbAlloc laaDlRbAlloc;
} RgSchDlRbAlloc;





typedef struct rgSchUlGrnt
{
   U8 iMcs;
   U8 iMcsCrnt;
   U8 hop;
   U8 rbStart;
   U8 numRb;
   U8 tpc;
   U8 nDmrs;
   U8 delayBit;

   Bool isRtx;

   U16 datSz;
   TfuModScheme modOdr;
} RgSchUlGrnt;







struct rgSchUlRetxAlloc
{
   CmLteRnti rnti;
   U8 numSb;
   U32 tbSz;
   U8 iMcs;
   RgSchUeCb *ue;
   Bool forMsg3;

   RgSchRaCb *raCb;

   CmLListCp *reTxLst;
};





typedef struct rgSchUlHole
{
   U8 start;
   U8 num;
   struct rgSchUlHole *prv;
   struct rgSchUlHole *nxt;
   struct rgSchUlAlloc *nxtAlloc;
   struct rgSchUlAlloc *prvAlloc;
} RgSchUlHole;





struct rgSchUlAlloc
{
   RgSchUlHqProcCb *hqProc;
   CmLteRnti rnti;
   U8 sbStart;
   U8 numSb;
   RgSchUlGrnt grnt;

   RgSchPdcch *pdcch;
   RgSchUeCb *ue;
   Bool forMsg3;
   Bool isMsg3CCCHSdu;
   Bool isMsg3CrntiCe;

   RgSchRaCb *raCb;
   Bool mrgdNewTxAlloc;


   RgSchUlAlloc *prv;
   RgSchUlAlloc *nxt;
   RgSchUlHole *prvHole;
   RgSchUlHole *nxtHole;

   void *allocDbRef;
   void *holeDbRef;
   Bool isAdaptive;
};





typedef struct rgSchUlAllocMem
{
   U8 maxAllocs;
   RgSchUlAlloc *firstFree;
   RgSchUlAlloc *allocs;
} RgSchUlAllocMem;





typedef struct rgSchUlAllocDb
{
   U8 count;
   RgSchUlAlloc *first;
   RgSchUlAllocMem mem;
} RgSchUlAllocDb;





typedef struct rgSchUlHoleMem
{
   U8 maxHoles;
   RgSchUlHole *firstFree;
   RgSchUlHole *holes;
} RgSchUlHoleMem;





typedef struct rgSchUlHoleDb
{
   U8 count;
   RgSchUlHole *first;
   RgSchUlHoleMem mem;
} RgSchUlHoleDb;





typedef struct rgSchUlSf
{
   U8 idx;

   CmLListCp reTxLst;






   U32 totPrb;


   U8 *allocCountRef;




   RgSchUlAllocDb *allocDb;
   RgSchUlHoleDb *holeDb;
   U8 availSubbands;

   U8 numACqiCount;
} RgSchUlSf;






typedef struct rgSchClcBoRpt
{
   CmLList boLstEnt;
   U32 bo;
   CmLteTimingInfo timeToTx;

   CmLteTimingInfo maxTimeToTx;
   U8 retxCnt;
   U16 i;
   U8 nPrb;

   U8 mcs;
} RgSchClcBoRpt;





typedef struct rgSchClcDlLcCb
{
   U8 lcId;
   Bool si;
   CmLListCp boLst;
} RgSchClcDlLcCb;





typedef struct rgSchSrsTxOffst
{
   U8 count;
   U8 offst[8];
} RgSchSrsTxOffst;





typedef struct rgSchSrsCfg
{

   Bool isSrsCfgPres;
   RgrSrsCfgPrd srsCfgPrdEnum;
   RgrSrsBwCfg srsBwEnum;
   RgSchSrsTxOffst srsTxOffst;


    U8 srsSubFrameCfg;


} RgSchSrsCfg;






typedef struct rgSchCfgElem
{
   CmLList cfgReqLstEnt;
   CmLteTimingInfo actvTime;
   struct rgrCfgS
   {
      Region reg;
      Pool pool;
      RgrCfgReqInfo *rgrCfgReq;

      RgrCfgTransId transId;
   } rgrCfg;
} RgSchCfgElem;






typedef struct rgSchCfgCb
{
   CmLListCp crntRgrCfgLst;

   CmLListCp pndngRgrCfgLst;

} RgSchCfgCfb;





typedef struct rgSchRntiLnk
{
   U16 rnti;

   CmLList rntiGrdPoolLnk;
   struct rgSchRntiLnk *prv;
   struct rgSchRntiLnk *nxt;
} RgSchRntiLnk;





typedef struct rgSchRntiDb
{
   U16 rntiStart;
   U16 maxRntis;
   U16 count;
   RgSchRntiLnk *freeRnti;
   RgSchRntiLnk *lastRnti;
   RgSchRntiLnk *rntiPool;

   CmLListCp rntiGuardPool;

} RgSchRntiDb;





typedef struct rgSchRaInfoCb
{
   CmLListCp raReqLst[(2*10)];



   CmLListCp raCbLst;
   CmLListCp toBeSchdLst;

} RgSchRaInfoCb;





struct rgSchUlHqProcCb
{
   U8 ndi;
   U8 remTx;
   RgSchUlAlloc *alloc;

   Bool rcvdCrcInd;

   U8 rvIdx;
   TknU8 rvIdxPhy;

   CmLList reTxLnk;
   RgSchUlRetxAlloc reTxAlloc;

   Bool isRetx;
   U8 procId;
   U8 ulSfIdx;






   Bool isSpsActvnHqP;

   Bool isSpsOccnHqP;


   void *hqEnt;
};





typedef struct rgSchUlHqCb
{
   U8 maxHqRetx;

   U8 numHqPrcs;



   RgSchUlHqProcCb hqProcCb[8];




} RgUeUlHqCb;
struct rgSchQciCb
{
   U8 qci;
   U32 dlPrbCount;
   U32 dlUeCount;
   U32 dlTotal_UeCount;

   U32 ulUeCount;
   U32 ulTotal_UeCount;

};
struct rgSchLcgCb
{


   U8 lcgId;
   Void *sch;







   U8 lcCnt;
   U8 lcId[10];

};





struct rgSchUlLcCb
{
   Bool isValid;
   U8 lcId;
   U8 lcgArrIdx;
   RgSchLcgCb *lcg;
   RgrLchQosCfg ulQos;

   RgSchQciCb *qciCb;
};





typedef struct rgSchHoPoUeGrnt
{
   U8 rapId;
   U8 hop;
   U8 rbStart;
   U8 numRb;
   U8 tpc;
   U8 iMcsCrnt;
   TknU16 ta;
   CmLList raRspLnk;

   U16 datSz;
   Bool cqiReqBit;
} RgSchHoPoUeGrnt;





typedef struct rgSchCmnSpsUlUeSchdInfo
{
   U32 allocBwMask[4];


   U8 scaledCqi;
   U16 actvSfLstIdx;

   CmLteTimingInfo ulSpsActvOcc;

   CmLteTimingInfo crntUlSpsOcc;

   RgSchUlAlloc allocInfo;
   RgSchUlAlloc *crntAlloc;
   RgSchUlSf *crntAllocSf;
} RgSchCmnSpsUlUeSchdInfo;





typedef struct rgSchCmnUlUeSpsInfo
{
   CmLList actvUeLstEnt;

   CmLList pndngUeLstEnt;


   Bool isUlSpsActv;

   U8 measGapMask[10];


   U8 state;



   Bool pdcchToRetx;

   RgSchCmnSpsUlUeSchdInfo ulSpsSchdInfo;


   U8 spsOccIdx;

   U32 packetSize;
   U32 spsSduSize;
   U32 spsGrantSize;

   CmLteTimingInfo lastSpsDatRecvdTime;

   CmLListCp *spsList;

   U32 actPdcchCrcFailCount;

   U32 crcFailCntSpsOcc;

   U32 relPdcchSntCnt;






} RgSchCmnUlUeSpsInfo;







typedef struct rgSchUeUlCb
{
   RgSchUlLcCb lcCb[10];

   RgSchLcgCb lcgArr[4];
   U8 ulInactvMask;
   CmLList ulInactvLnk;
   RgSchHoPoUeGrnt rarGrnt;
   RgrUeTxAntSelCfg ulTxAntSel;


   RgrUeBsrTmrCfg bsrTmrCfg;



   RgrUeSpsUlCfg ulSpsCfg;
   U8 explicitRelCnt;

   U16 spsPrdcty;


   CmLteTimingInfo relPdcchSchdTime;






   U8 betaHqOffst;

   U8 betaCqiOffst;
   U8 betaRiOffst;

   U32 cqiRiSz;

   U32 betaOffstVal;

   U32 maxBytesPerUePerTti;

   U32 minReqBytes;
   U32 totalBsr;
   U32 nonLcg0Bs;
   U32 nonGbrLcgBs;
   U32 effBsr;

   U32 cfgdAmbr;
   U32 effAmbr;
   CmLteTimingInfo ulTransTime;


   RgSchCmnUlUeSpsInfo ulSpsInfo;

   Bool isUlCaEnabled;
   CmLteCellId ctrlOnServCellIdx[4];




  Bool useExtBSRSizes;
} RgSchUeUlCb;





typedef struct rgSchCcchSchdInfo
{
   U32 totBytes;
   CmLList retxLnk;
   U8 rvIdx;
} RgSchCcchSchdInfo;





typedef struct rgSchDlGrnt
{
   U16 schdTime;
   U8 rbStrt;
   U8 numRb;
   U8 iMcs;
   U8 rv;
} RgSchDlGrnt;





typedef struct rgSchLchAllocInfo
{
   U8 lcId;
   U32 schdData;
} RgSchLchAllocInfo;




typedef struct rgSchDrxDlHqProcCb
{
   CmLList harqRTTEnt;
   CmLList harqRetxEnt;

   U16 rttIndx;
   U16 reTxIndx;
   U8 retxTmrReduction;






} RgSchDrxDlHqProcCb;




typedef enum
{
   HQ_TB_ACKED=0,
   HQ_TB_NACKED,
   HQ_TB_WAITING
}RgSchHqTbState;




struct rgSchDlHqTbCb
{
   U8 tbIdx;

   U32 tbSz;
   U8 txCntr;
   U8 ndi;
   TknU8 schdTa;

   U8 contResCe;
   U8 numLch;

   CmLteTimingInfo timingInfo;
   RgSchLchAllocInfo lchSchdDataArr[10];
   RgSchLchAllocInfo *lchSchdData;
   RgSchCcchSchdInfo ccchSchdInfo;
   U8 fbkRepCntr;
   U8 fbkRecpRepCntr;
   CmLList anRepLnk[6];




   RgSchDlSf *crntSubfrm[6];
   U8 ackCount;
   U8 isAckNackDtx;
   U8 nackCount;
   U8 dtxCount;
   RgSchDlGrnt dlGrnt;
   Bool taSnt;
   U8 numLyrs;

   RgSchHqTbState state;
   RgSchDlHqProcCb *hqP;


   U8 cntrRetxAllocFail;





};







typedef struct rgSchLaaHqP
{
   CmLList hqPToShiftLnk;

   CmLList errIndHqpLnk;

   U8 procId;

   U8 sCellMacInstId;

   U8 tbId;


   U16 hqPStamp;



   U8 overflowCycles;

   U8 hqPToShiftIdx;

}RgSchLaaHqP;





struct rgSchDlHqProcCb
{
   CmLList lnk;
   RgSchDlHqEnt *hqE;



   U8 procId;
   Void *sch;

   RgSchDlHqTbCb tbInfo[2];
   RgSchDrxDlHqProcCb drxCb;

   U8 tbCnt;



   TknU16 spsN1PucchRes;





   CmLList reqLnk;
   CmLList schdLstLnk;

   Bool hasDcch;

   Bool cwSwpEnabled;

   U8 tpc;



   CmLList hqPSfLnk;

   RgSchPdcch *pdcch;
   RgSchDlSf *subFrm;
   U8 dlDai;
   U8 ulDai;





   RgSchLaaHqP laaHqP;

};





struct rgSchDlHqEnt
{
   RgSchRaCb *raCb;
   RgSchUeCb *ue;
   CmLListCp free;
   CmLListCp inUse;
   U8 maxHqTx;
   RgSchDlHqProcCb *msg4Proc;


   RgSchDlHqProcCb *ccchSduProc;



   U8 numHqPrcs;



   RgSchDlHqProcCb procs[8];

   Void *sch;

   RgSchCellCb *cell;

};






typedef enum rgSchTaState
{
   RGSCH_TA_IDLE = 0,
   RGSCH_TA_TOBE_SCHEDULED,
   RGSCH_TA_SCHEDULED
} RgSchTaState;





typedef struct rgSchUeDlTaCb
{
  U16 cfgTaTmr;
  U8 ta;
  U8 numRemSf;
  RgSchTaState state;

  Bool outStndngTa;

  U8 outStndngTaval;
} RgSchUeDlTaCb;





struct rgSchDlLcCb
{
   U8 lcId;
   U32 bo;
   RgSchUeCb *ue;

   CmLteLcType lcType;
   RgSchQciCb *qciCb;


   RgrLchSpsCfg dlLcSpsCfg;


   U16 estRlcHdrSz;
   Bool staPduPrsnt;

   U32 staPduBo;

   Void *sch;
   U32 prbsReqd;
   CmLList schdLnk;
   U32 oldestSduArrTime;
   CmLList lcFlowCntrlEnt;
   CmLList lcPdbFbkLnk;
   Bool setMaxUlPrio;
   Bool setMaxDlPrio;
};


typedef struct rgSchN1PucchResCb
{
   U16 n1PucchIdx;
   CmLList n1Lnk;
}RgSchN1PucchResCb;


typedef struct rgSchSCellN1ResCb
{
  U8 cw1N1ResCount;
  U8 cw2N1ResCount;
  RgSchN1PucchResCb cw1N1Res[4];
  RgSchN1PucchResCb cw2N1Res[4];
}RgSchSCellN1ResCb;

typedef struct rgSchDlHqInfo
{
   Bool isPuschHarqRecpPres;
   RgrSchFrmt1b3TypEnum uciFrmtTyp;

   U8 totalTbCnt;


   CmLList dlSfUeLnk;
   CmLList dlSfLaaUeLnk;
   CmLListCp hqPLst;





}RgSchDlHqInfo;




typedef struct rgUeMeasGapCfg
{
   Bool isMesGapEnabled;
   U8 gapPrd;
   U8 gapOffst;
} RgUeMeasGapCfg;



typedef struct rgSchUeMeasGapCb
{
   Bool isMesGapEnabled;
   U8 isMeasuring;
   U8 gapPrd;
   U8 gapOffst;
   CmLList measQLnk;
   CmLList ackNakQLnk;
   CmTimer measGapTmr;
   CmTimer measGapUlInactvTmr;
   CmTimer measGapDlInactvTmr;
} RgSchUeMeasGapCb;



typedef struct rgSchUeAckNakRepCb
{
   Bool isAckNackEnabled;
   U8 isAckNakRep;
   U8 cfgRepCnt;
   U8 repCntr;
   U16 pucchRes;
   CmTimer ackNakRepUlInactvTmr;
   CmTimer ackNakRepDlInactvTmr;
   CmTimer ackNakRepTmr;
   CmLList ackNakRepLnk;
   CmLListCp *prsntQ;

} RgSchUeAckNakRepCb;





typedef struct rgSchUeMimoInfo
{
   RgrTxMode oldTMode;
   RgrTxMode txMode;
   TknU32 doa;
   Bool puschFdbkVld;

   TfuDlCqiPuschInfo puschPmiInfo;

   RgrCodeBookRstCfg cdbkSbstRstrctn;




   S32 txModUpChgFactor;
   S32 txModDownChgFactor;


}RgSchUeMimoInfo;







typedef struct rgSchCqiRawPuschMode31
{
   U8 wideBCqiCw0;
   U8 totLenSbDiffCqiCw0;
   U8 r1WideBCqiCw1;
   U8 r1TotLenSbDiffCqiCw1;
   U8 rg1WideBCqiCw1;
   U8 rg1TotLenSbDiffCqiCw1;
   U8 r1PmiBitLen;
   U8 rg1PmiBitLen;
} RgSchCqiRawPuschMode31;




typedef struct rgSchCqiRawPuschMode30
{
   U8 wideBCqiCw;
   U8 totLenSbDiffCqi;
} RgSchCqiRawPuschMode30;




typedef struct rgSchCqiRawPuschMode22
{
   U8 wideBCqiCw0;
   U8 sBDiffCqiCw0;
   U8 r1WideBCqiCw1;
   U8 r1SbDiffCqiCw1;
   U8 rg1WideBCqiCw1;
   U8 rg1SbDiffCqiCw1;
   U8 posOfM;
   U8 r1PmiBitLen;
   U8 rg1PmiBitLen;
} RgSchCqiRawPuschMode22;




typedef struct rgSchCqiRawPuschMode20
{
   U8 wideBCqiCw;
   U8 subBandDiffCqi;
   U8 posOfM;
} RgSchCqiRawPuschMode20;




typedef struct rgSchCqiRawPuschMode12
{
   U8 wideBCqiCw0;
   U8 r1WideBCqiCw1;
   U8 rg1WideBCqiCw1;
   U8 r1TotalPmiBitLen;
   U8 rg1TotalPmiBitLen;
} RgSchCqiRawPuschMode12;





typedef struct rgSchDlCqiRawPusch
{
   TfuDlCqiPuschMode mode;
   TknU8 ri;
   union
   {
      RgSchCqiRawPuschMode12 mode12Info;
      RgSchCqiRawPuschMode20 mode20Info;
      RgSchCqiRawPuschMode22 mode22Info;
      RgSchCqiRawPuschMode30 mode30Info;
      RgSchCqiRawPuschMode31 mode31Info;
   }u;
} RgSchDlCqiRawPusch;

typedef struct rgSchPuschRawCqiInfoPerCell
{
   U8 sCellIdx;

   RgSchDlCqiRawPusch puschRawCqiInfo;
} RgSchPuschRawCqiInfoPerCell;

typedef struct rgSchPuschRawCqiInfoForSCells
{
   U8 numOfCells;
   RgSchPuschRawCqiInfoPerCell cqiBitWidth[8];
} RgSchPuschRawCqiInfoForSCells;

typedef struct rgSchPucchRawCqiInfoPerCell
{
  U8 sCellIdx;

  TfuDlCqiPucch pucchRawCqiInfo;
} RgSchPucchRawCqiInfoPerCell;

typedef struct rgSchUeRawCqiBitWidthInfo
{
  TfuRecpReqType type;
  CmLteTimingInfo recvTime;
   union
   {
      RgSchPucchRawCqiInfoPerCell pucch;
      RgSchPuschRawCqiInfoForSCells pusch;
   }u;
} RgSchUeRawCqiBitWidthInfo;
struct rgSchUeCellInfo
{
   CmHashListEnt ueLstEnt;
   RgSchUeCb *ue;






   RgSchDlHqEnt *hqEnt;
   RgSchDlRbAlloc dlAllocCb;
   RgSchCellCb *cell;
   Void *sch;
   RgrUeTxModeCfg txMode;





   U8 reqForCqi;

   RgSchUeACqiCb acqiCb;
   RgSchUePCqiCb cqiCb;
   TknU8 pA;



   U8 cqiRiWritIdx;

   U8 cqiRiReadIdx;

   CmTimer deactTmr;
   CmTimer actDelayTmr;

};
typedef struct rgSchUeDlCb
{
   RgSchUeDlTaCb taCb;

   RgSchDlLcCb *lcCb[10];

   RgrUeDlCqiCfg ueDlCqiCfg;
   U8 dlInactvMask;
   RgSchCqiReqField reqForCqi;
   Bool pCqiPrsnt;
   Bool acqiResGrntd;
   CmLList dlInactvLnk;





   RgrUeSpsDlCfg dlSpsCfg;
   Bool isSpsHqPInUse;


   RgSchPdcch spsOccPdcch;


   U8 numHqDlSfInfo;



   RgSchDlHqInfo dlSfHqInfo[20];


   U32 ambrCfgd;


   U32 aggTbBits;
   CmLteTimingInfo lstSchTime;

} RgSchUeDlCb;
typedef struct rgSchDrxUeCb
{



   Bool srRcvd;
   Bool raRcvd;

   U8 onDurTmrLen;
   U16 drxStartOffset;
   S16 onDurExpDistance;

   U8 drxRetransTmrLen;

   U16 inactvtyTmrLen;
   S16 drxInactDistance;

   Bool isLongCycle;
   U16 longDrxCycle;

   Bool isShortCycleCfgd;
   U8 shortCycleTmrLen;
   U16 shortDrxCycle;
   S16 drxShortCycleDistance;


   CmLList onDurationEnt;
   CmLList onDurationExpEnt;
   CmLList inActvTmrEnt;
   CmLList shortCycleEnt;

   S16 distance;




   U16 onDurIndx;
   U16 onDurExpIndx;
   U16 drxInactvIndx;
   U16 shortCycleIndx;

   U8 shortCycleTmr;
   U32 drxDlInactvMask;
   U32 drxUlInactvMask;
   U32 drxDlInactvMaskPerCell[8];
   U32 drxUlInactvMaskPerCell[8];
} RgSchDrxUeCb;






typedef struct RgSchCqiInfo
{
   U8 cqiCount;

   RgrUeCqiRept cqiRept[16];
}RgSchCqiInfo;







typedef struct rgSchLteAdvUeCb
{
   RgrLteAdvancedUeConfig rgrLteAdvUeCfg;
   Bool isCCUePHigh;
} RgSchLteAdvFeatureUeCb;



typedef struct rgSchUeDciSize {
   U8 cmnSize[TFU_DCI_FORMAT_1A+1];
   U8 dedSize[TFU_DCI_FORMAT_2A+1];
   U8 noUlCcSize[TFU_DCI_FORMAT_2A+1];

} RgSchUeDciSize;
struct rgSchUeCb
{
   U32 totalBo;
   U32 totalPrbRequired;


   CmHashListEnt spsUeLstEnt;
   U32 spsOccasionCnt;

   RgSchRntiLnk *rntiLnk;
   CmLteRnti ueId;
   RgSchUeMimoInfo mimoInfo;


   CmLteRnti spsRnti;


   CmLteTimingInfo relPdcchTxTime;




   CmLteTimingInfo relPdcchFbkTiming;


   RgSchCellCb *cell;

   RgSchUeUlCb ul;
   RgSchUeDlCb dl;
   CmLteTimingInfo datIndTime;

   CmLteTimingInfo macCeRptTime;

   U32 y[10];





   CmLList taLnk;
   CmLList dlTaLnk;
   CmTimer taTmr;
   RgSchUeMeasGapCb measGapCb;
   RgSchUeAckNakRepCb ackNakRepCb;







   CmTimer bsrTmr;

   CmLList ccchSduLnk;



   struct
   {
      U32 bo;

   } dlCcchInfo;







   CmLteUeCategory ueCatEnum;



   RgSchUeSrsCb srsCb;
   RgSchUeSrCb srCb;
   Bool isDrxEnabled;
   RgSchDrxUeCb *drxCb;

   CmLList ulDrxInactvLnk;
   CmLList dlDrxInactvLnk;

   CmLList ulDrxInactvTmrLnk;

   CmLList dlDrxInactvTmrLnk;



   U8 validTxAnt;

   U8 cqiRiWritIdx;

   U8 cqiRiReadIdx;

   RgSchUeRawCqiBitWidthInfo rawCqiBitW[(2 * 2)];
   U8 initNumRbs;





   RgrUeCqiReptCfg cqiReptCfgInfo;
   RgSchCqiInfo schCqiInfo;



   RgSchLteAdvFeatureUeCb lteAdvUeCb;
   Bool isMsg4PdcchWithCrnti;

   Bool isSrGrant;
   Bool txModeTransCmplt;

   CmTimer txModeTransTmr;






   U8 refreshOffset;
   U8 csgMmbrSta;

   TSL2UeStatsCb *tenbStats;

   CmLListCp flowCntrlLcLst;
   CmLList ueFlowCntrlEnt;

   RgSchLcgCb *repLcg;







   RgSchSCellN1ResCb n1PucchF1bResCb;
   RgrSchFrmt1b3TypEnum uciFrmtTyp;


   U8 numSCells;
   U8 cellIdToCellIdxMap[8];

   RgSchUeCellInfo *cellInfo[8];

   RgSchUePCqiCb *nPCqiCb;
   RgSchUePCqiCb *nPRiCb;

   U8 remBoCnt;

   U8 *zeroBoCnt;






   RgSchUeDciSize dciSize;
   RgrAccessStratumRls accessStratumRls;







};






typedef struct rgSchUpSapCfgInfo
{
   Pst sapPst;
   SpId spId;
   SuId suId;
}RgSchUpSapCfgInfo;





typedef struct rgSchLowSapCfgInfo
{
   Pst sapPst;
   SpId spId;
   SuId suId;
   TmrCfg bndTmr;
}RgSchLowSapCfgInfo;





typedef struct rgSchUpSapCb
{
   RgSchUpSapCfgInfo sapCfg;
   RgSapSta sapSta;
   RgSchCellCb *cell;
}RgSchUpSapCb;





typedef struct rgSchLowSapCb
{
   RgSchLowSapCfgInfo sapCfg;
   RgSapSta sapSta;
   U8 numBndRetries;
   RgSchCellCb *cell;
   CmTimer tmrBlk;
}RgSchLowSapCb;






typedef struct rgSchLmResponse
{
   TranId transId;
   Resp response;
}RgSchLmResponse;


typedef enum sfnEnum
{
   RG_SCH_SFN_ANY,
   RG_SCH_SFN_ODD,
   RG_SCH_SFN_EVEN
} SfnEnum;

typedef struct rgSchConfigIdx
{
   U8 configurationIndex;
   SfnEnum sfn;
   U8 subframes[10];
} RgSchConfigIdx;

typedef struct rgSchRapId
{
   U8 rapId;
   CmLteTimingInfo lastAllocPRACHMaskIdx;
} RgSchRapId;

typedef struct pdcchOrderCfg
{
   RgSchRapId rapIds[64];
   RgSchConfigIdx configIdx;
} PdcchOrderCfg;




typedef struct rgSchMeasGapCb
{
   CmLListCp gapPrd40Q[40];

   CmLListCp gapPrd80Q[80];

} RgSchMeasGapCb;



typedef struct rgSchAckNakRepCb
{



   CmLListCp ackNakRepQ[10];

} RgSchAckNakRepCb;




typedef struct rgSchBwRbgInfo
{
   U8 numRbs;

   U8 numRbgs;

   U8 rbgSize;
   U8 lastRbgSize;
   U8 rbgSubsetSize[4];


}RgSchBwRbgInfo;




typedef struct rgSchDrxQ
{
   CmLListCp onDurationQ;
   CmLListCp onDurationExpQ;
   CmLListCp inActvTmrQ;
   CmLListCp harqRTTQ;
   CmLListCp harqRetxQ;
   CmLListCp shortCycleQ;
} RgSchDrxQ;







typedef struct rgSchDRXCellCb
{
   RgSchDrxQ drxQ[256 ];

   Bool delInUlScan;



} RgSchDRXCellCb;






typedef struct sib1Info
{
   Buffer *sib1;
   U8 mcs;
   U8 nPrb;
   MsgLen msgLen;
}RgSchSib1Info;


typedef struct siInfo
{
   Buffer *si;
   U8 mcs;
   U8 nPrb;
   MsgLen msgLen;
}RgSchSiInfo;



typedef struct rgSchSiCfgInfo
{
   Buffer *mib;
   RgSchSib1Info sib1Info;
   RgSchSiInfo siInfo[16];
}RgSchSiCfgInfo;



typedef struct rgSchSiCtx
{
   U8 siId;
   CmLteTimingInfo timeToTx;

   CmLteTimingInfo maxTimeToTx;
   U8 retxCntRem;
   U16 i;
   Bool warningSiFlag;
} RgSchSiCtx;




typedef struct warningSiPdu
{
   CmLList lnk;
   Buffer *pdu;
   U8 mcs;
   U8 nPrb;
   MsgLen msgLen;
}RgSchWarningSiPdu;




typedef struct warningSiSeg
{

   CmLListCp segLstCp;
   RgSchWarningSiPdu pduNode[64];
   RgrCfgTransId transId;
}RgSchWarningSiSeg;



typedef struct warningSi
{

   RgSchWarningSiSeg warningSiMsg;

   U8 siId;
   U8 idx;
}RgSchWarningSiInfo;



typedef struct siArray
{
   Bool isWarningSi;
   void *si;
}
RgSchSiArray;


typedef struct rgSchSiCb
{
   Bool siBitMask;

   RgSchSiCtx siCtx;
   RgrSiCfg newSiCfg;


   S8 inWindow;


   RgSchSiCfgInfo crntSiInfo;
   RgSchSiCfgInfo newSiInfo;
   RgSchWarningSiInfo warningSi[3];

   RgSchSiArray siArray[16];
} RgSchSiCb;


typedef struct rgSchBiInfo
{
   U16 prevBiTime;

   CmLteTimingInfo biTime;
} RgSchBiInfo;


typedef struct rgSchQciPrbUsage
{
   U8 qci;
   U32 dlTotPrbUsed;
   U32 ulTotPrbUsed;
}RgSchQciPrbUsage;



typedef struct rgSchPrbUsage
{
   Bool prbRprtEnabld;
   U16 rprtPeriod;

   CmLteTimingInfo startTime;


   RgSchQciPrbUsage qciPrbRpts[4];



}RgSchPrbUsage;




typedef enum rgSchAbsSfEnum
{
   RG_SCH_ABS_ENABLED_NONABS_SF = 0,
   RG_SCH_ABS_ENABLED_ABS_SF = 1,
   RG_SCH_ABS_DISABLED = 2
} RgSchAbsSfEnum;


typedef struct rgSchLteAdvFeatureCb
{
   RgrSfrConfig sfrCfg;
   RgrDsfrConfig dsfrCfg;
   RgrAbsConfig absCfg;
   RgSchAbsSfEnum absDlSfInfo;

   U8 absPatternDlIdx;
   U32 absLoadTtiCnt;
   U32 absLoadInfo[40];
} RgSchLteAdvFeatureCb;




typedef struct rgSchCellDciSize {
   U8 baseSize[TFU_DCI_FORMAT_1A+1];
   U8 size[TFU_DCI_FORMAT_3A+1];


   U8 dci0HopSize;
} RgSchCellDciSize;





typedef struct rgSchMeasCb
{
   U32 dlTpt;
   U32 dlBytesCnt;
   U32 ulTpt;
   U32 ulBytesCnt;
}RgSchMeasCb;





typedef struct rgSchThrsldsCb
{
   U8 maxDlItbs;
   U8 maxUlItbs;
}RgSchThrsldsCb;




typedef struct rgSchCpuOvrLdCntrlCb
{
   U8 cpuOvrLdIns;
   U32 tgtDlTpt;
   U32 tgtUlTpt;
   U8 dlNxtIndxDecNumUeTti;
   U8 ulNxtIndxDecNumUeTti;
   U8 maxUeNewTxPerTti[10];
   U8 maxUeNewRxPerTti[10];
}RgSchCpuOvrLdCntrlCb;






typedef struct rgSchLaaCellCb
{
   CmLListCp errIndHqpLst;
   CmLListCp laaTbsToBeSchedLst;

   CmLListCp hqPToShiftChkQ[128];


}RgSchLaaCellCb;





struct rgSchCellCb
{
   CmLteCellId cellId;
   Inst instIdx;
   Inst macInst;
   U8 schTickDelta;
   Bool stopSiSch;
   U8 stopDlSch;
   Bool stopUlSch;
   Bool isDlDataAllwd;
   RgrDlHqCfg dlHqCfg;
   RgSchRntiDb rntiDb;
   struct schdInfoS
   {
      Void *sch;
      RgSchdApis *apis;
   } sc;

   Bool isCpUlExtend;
   Bool isCpDlExtend;
   U8 numTxAntPorts;
   RgrBwCfg bwCfg;
   U8 pbchRbStart;
   U8 pbchRbEnd;
   U8 numCellRSPerSf;

   RgrPhichCfg phichCfg;
   RgrPucchCfg pucchCfg;
   RgSchSrsCfg srsCfg;
   RgrRachCfg rachCfg;

   RgSchBiInfo biInfo;
   RgrSiCfg siCfg;


   RgrPuschCfg puschCfg;

   RgrPreambleSetCfg macPreambleSet;

   CmLteTimingInfo crntTime;

   CmLteTimingInfo hiDci0Time;
   CmLteTimingInfo hqRlsTime;
   CmLteTimingInfo dlSfRlsTime;
   CmLteTimingInfo dlDciTime;
   CmLteTimingInfo rcpReqTime;
   RgSchCfgCfb rgCfgInfo;

   U8 ulCcchId;
   U8 dlCcchId;
   RgSchClcDlLcCb cmnLcCb[4];
   CmHashListCp ueLst;



   CmHashListCp spsUeLst;


   CmLListCp taUeLst;


   CmLListCp ccchSduUeLst;

   CmLListCp contResGrdTmrLst;

   CmLListCp contResTmrLst;


   RgSchRaInfoCb raInfo;

   CmLListCp pdcchLst;
   CmTqCp tqCp;
   CmTqType tq[10];
   U8 crntSfIdx;




   RgInfSfAlloc sfAllocArr[10];


   RgInfRlsHqInfo rlsHqArr[10];

   U8 crntHqIdx;
   RgSchLowSapCb *tfuSap;


   RgSchUpSapCb *rgrSap;


   RgSchUpSapCb *rgmSap;


   U8 rrmTtiIndPrd;





   PdcchOrderCfg pdcchOrdCfg;
   RgSchMeasGapCb measGapCb;
   RgSchAckNakRepCb ackNakRepCb;
   RgSchDlSf *subFrms[20];
   U16 nCce;

   RgSchDynCfiCb dynCfiCb;

   U8 noOfRbgs;
   U8 rbgSize;


   RgSchBwRbgInfo dlBwRbgInfo;

   RgrSpsCellCfg spsCellCfg;

   RgSchBwRbgInfo spsBwRbgInfo;
   U8 ulAvailBw;


 RgSchPerPucchCb pCqiSrsSrLst[320];







   RgSchDRXCellCb *drxCb;



   RgSchSiCb siCb;

   RgSchPrbUsage prbUsage;
   U16 t300TmrVal;

   TknStrOSXL rntpAggrInfo;
   RgrLoadInfReqInfo loadInfReqInfo;


   RgSchLteAdvFeatureCb lteAdvCb;


   U32 dlNumUeSchedPerTti[8];
   U32 ulNumUeSchedPerTti[8];
   Bool overLoadBackOffEnab;
   U8 overLoadBackOffval;
   U8 refreshUeCnt[16];
   U8 minDlResNonCsg;
   U8 minUlResNonCsg;
   Bool isAutoCfgModeEnb;

   CmLListCp lcMonitorLst;
   U32 prbCnt;
   U32 maxPrbCnt;

   RgSchCpuOvrLdCntrlCb cpuOvrLdCntrl;
   RgSchMeasCb measurements;
   RgSchThrsldsCb thresholds;

   TSL2CellStatsCb *tenbStats;

   RgSchCellDciSize dciSize;
   RgrLteUCfg rgSchLAACellCfg;
   RgSchLaaCellCb laaCellCb;
};





typedef struct rgSchGenCb
{
   U8 tmrRes;
   RgSchLmResponse *bndCfmResp;
   RgSchLmResponse ustaResp;
   U8 startCellId;






}RgSchGenCb;





struct _rgSchCb
{
   TskInit rgSchInit;
   RgSchGenCb genCfg;
   U8 numSaps;
   RgSchUpSapCb *rgrSap;
   RgSchLowSapCb *tfuSap;
   RgSchUpSapCb *rgmSap;
   CmTqCp tmrTqCp;
   CmTqType tmrTq[100];
   U8 rgSchDlDelta;
   U8 rgSchCmnDlDelta;
   U8 rgSchUlDelta;
   RgSchCellCb *cells[8];
   RgrSchedEnbCfg rgrSchedEnbCfg;
   Void *rgSchEnbPfsDl;
   CmLListCp laaMovedTBNodeLst;

};


extern RgSchCb rgSchCb[2];
typedef struct rgSchRaReqInfo
{
   CmLList raReqLstEnt;
   CmLteTimingInfo timingInfo;
   RgTfuRaReqInfo raReq;
   RgSchUeCb *ue;
} RgSchRaReqInfo;





typedef enum rgSchRaState
{
   RGSCH_RA_MSG3_PENDING,
   RGSCH_RA_MSG4_PENDING,
   RGSCH_RA_MSG4_DONE
} RgSchRaState;





struct rgSchRaCb
{
   CmLList raCbLnk;
   CmLList schdLnk;

   CmLteRnti tmpCrnti;
   CmLteTimingInfo timingInfo;
   RgSchRntiLnk *rntiLnk;
   RgSchRaState raState;
   struct
   {
      U32 bo;
   } dlCcchInfo;
   U8 msg3HqProcId;

   RgSchUlHqProcCb msg3HqProc;
   RgSchUeCb *ue;
   Bool toDel;
   TknU8 phr;

   CmLList rspLnk;
   U8 rapId;
   TknU16 ta;
   RgSchUlGrnt msg3Grnt;
   U32 y[10];
   RgSchDlHqEnt *dlHqE;
   U8 ccchCqi;
   RgSchDlRbAlloc rbAllocInfo;

   CmLteTimingInfo msg3AllocTime;


   CmLList contResTmrLnk;

   CmLteTimingInfo expiryTime;


   U32 ccchSduBo;


};





struct rgSchErrInfo
{
   U8 errType;
   U16 errCause;
};
extern Void rgSCHTmrStartTmr ( RgSchCellCb *cellCb, Ptr cb, S16 tmrEvnt, U32 tmrVal)



                             ;

extern Void rgSCHTmrStopTmr ( RgSchCellCb *cellCb, S16 tmrEvnt, Ptr cb)


                         ;

extern Void rgSCHTmrProcTmr ( Ptr cb, S16 tmrEvnt)

                              ;



extern S16 rgSCHTomRaReqInd ( RgSchCellCb *cell, TfuRaReqIndInfo *raReqInd)

                                    ;

extern S16 rgSCHTomPucchDeltaPwrInd ( RgSchCellCb *cell, TfuPucchDeltaPwrIndInfo *pucchDeltaPwr)

                                                 ;

extern S16 rgSCHTomUlCqiInd ( RgSchCellCb *cell, TfuUlCqiIndInfo *ulCqiInd)

                                    ;

extern S16 rgSCHTomSrInd ( RgSchCellCb *cell, TfuSrIndInfo *srInd)

                                 ;

extern S16 rgSCHTomDlCqiInd ( RgSchCellCb *cell, TfuDlCqiIndInfo *dlCqiInd)

                                    ;


extern S16 rgSCHTomRawCqiInd ( RgSchCellCb *cell, TfuRawCqiIndInfo* rawCqiInd )



  ;

extern S16 rgSCHTomSrsInd ( RgSchCellCb *cell, TfuSrsIndInfo* srsInd )



  ;



extern S16 rgSCHTomDoaInd ( RgSchCellCb *cell, TfuDoaIndInfo *doaInd)

                                  ;
extern S16 rgSCHTomCrcInd ( RgSchCellCb *cell, TfuCrcIndInfo *crcInd)

                                ;

extern Void rgSCHTomTtiInd ( TfuTtiIndInfo *ttiInd, Inst inst)

                    ;

extern S16 rgSCHTomHarqAckInd ( RgSchCellCb *cell, TfuHqIndInfo *harqAckInd)

                                        ;

extern S16 rgSCHTomTimingAdvInd ( RgSchCellCb *cell, TfuTimingAdvIndInfo *timingAdvInd)

                                            ;





extern S16 schActvInit (Ent entity, Inst inst, Region region, Reason reason)
                              ;
extern S16 rgSCHLmmStartTmr (Inst instId, S16 tmrEvnt, U32 tmrVal, U32 cb)
                             ;
extern S16 rgSCHLmmStopTmr (Inst instId, S16 tmrEvnt, U32 cb);
extern S16 rgSCHLmmTmrExpiry (U32 cb, S16 tmrEvnt);

extern S16 rgSCHLmmBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 schActvTmr (Ent entity, Inst inst);

extern S16 rgSCHLmmStaInd (Inst instId, U16 category, U16 event, U16 cause, RgUstaDgn *dgn)
                                                     ;
extern S16 schActvTsk (Pst *pst, Buffer *mBuf);
extern Void rgSCHLmmFillCfmPst (Pst *reqPst,Pst *cfmPst,RgMngmt *cfm);
extern U16 rgSCHLmmInstCfg (RgCfg *cfg, Inst inst);
extern Void printSchCellInfo (Void);
extern Void rgSCHLmmGenCntrl (RgMngmt *cntrl,RgMngmt *cfm,Pst *cfmPst);
extern Void rgSCHLmmSapCntrl (RgMngmt *cntrl,RgMngmt *cfm,Pst *cfmPst);




extern S16 rgSCHCfgVldtRgrCellCfg (Inst inst, RgrCellCfg *cellCfg, RgSchCellCb *cell, RgSchErrInfo *errInfo)
                                                ;
extern S16 rgSCHCfgRgrCellCfg (RgSchCb *instCb, SpId spId, RgrCellCfg *cellCfg, RgSchErrInfo *errInfo)
                                                  ;
extern S16 rgSCHCfgRgrSchedEnbCfg (Inst inst, SpId spId, RgrSchedEnbCfg *schedEnbCfg, RgSchErrInfo *errInfo)
                                                          ;
extern S16 rgSCHCfgVldtRgrCellRecfg (Inst inst, RgrCellRecfg *cellRecfg, RgSchCellCb **cell, RgSchErrInfo *errInfo)
                                                  ;
extern S16 rgSCHCfgRgrCellRecfg (RgSchCellCb *cell, RgrCellRecfg *cellRecfg, RgSchErrInfo *errInfo)
                             ;

extern S16 rgSCHCfgVldtRgrUeCfg (Inst inst, RgrUeCfg *ueCfg, RgSchCellCb **cell, RgSchErrInfo *errInfo)
                                                  ;
extern S16 rgSCHCfgRgrUeCfg (RgSchCellCb *cell, RgrUeCfg *ueCfg, RgSchErrInfo *errInfo)
                              ;
extern S16 rgSCHCfgVldtRgrUeRecfg (Inst inst, RgrUeRecfg *ueRecfg, RgSchCellCb **cell, RgSchUeCb **ue, RgSchErrInfo *errInfo)
                                                                 ;
extern S16 rgSCHCfgRgrUeRecfg (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *ueRecfg, RgSchErrInfo *errInfo)
                                       ;

extern S16 rgSCHCfgVldtRgrLcCfg (Inst inst, RgrLchCfg *lcCfg, RgSchCellCb **cell, RgSchUeCb **ue, RgSchErrInfo *errInfo)
                                                                  ;
extern S16 rgSCHCfgRgrLchCfg (RgSchCellCb *cell, RgSchUeCb *ue, RgrLchCfg *lcCfg, RgSchErrInfo *errInfo)
                                               ;
extern S16 rgSCHCfgVldtRgrLchRecfg (Inst inst, RgrLchRecfg *lcRecfg, RgSchCellCb **cell, RgSchUeCb **ue, RgSchDlLcCb **dlLc, RgSchErrInfo *errInfo)

                             ;
extern S16 rgSCHCfgRgrLchRecfg (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc, RgrLchRecfg *lcRecfg, RgSchErrInfo *errInfo)
                                                                         ;

extern S16 rgSCHCfgVldtRgrLcgRecfg (Inst inst,RgrLcgRecfg *lcgRecfg, RgSchCellCb *cell,RgSchUeCb **ue,RgSchErrInfo *errInfo )
                                                                  ;
extern S16 rgSCHCfgVldtRgrLcgCfg (Inst inst,RgrLcgCfg *lcgCfg, RgSchCellCb **cell,RgSchUeCb **ue,RgSchErrInfo *errInfo )
                                                                   ;
extern S16 rgSCHCfgVldtRgrSchedEnbCfg (Inst inst, RgrSchedEnbCfg *schedEnbCfg, RgSchErrInfo *errInfo )
                                                              ;
extern S16 rgSCHCfgRgrLcgCfg (RgSchCellCb *cell,RgSchUeCb *ue, RgrLcgCfg *lcgCfg,RgSchErrInfo *errInfo )
                                                   ;
extern S16 rgSCHCfgRgrLcgRecfg (RgSchCellCb *cell,RgSchUeCb *ue, RgrLcgRecfg *lcgRecfg,RgSchErrInfo *errInfo)
                                                      ;

extern S16 rgSCHCfgVldtRgrUeReset (Inst inst, RgrRst *reset, RgSchCellCb *cell, RgSchUeCb **ue,RgSchErrInfo *errInfo)
                                                   ;
extern S16 rgSCHCfgRgrUeReset (RgSchCellCb *cell,RgSchUeCb *ue,RgrRst *reset, RgSchErrInfo *errInfo)
                                  ;

extern S16 rgSCHCfgRgrCellDel (RgSchCellCb *cell, RgrDel *cellDelInfo, RgSchErrInfo *errInfo)
                             ;
extern S16 rgSCHCfgRgrUeDel (RgSchCellCb *cell, RgrDel *ueDelInfo, RgSchErrInfo *errInfo)
                             ;
extern S16 rgSCHCfgRgrLcDel (RgSchCellCb *cell, RgrDel *lcDelInfo, RgSchErrInfo *errInfo)
                             ;
extern S16 rgSCHCfgRgrLcgDel (RgSchCellCb *cell,RgrDel *lcDelInfo, RgSchErrInfo *errInfo)
                                ;
extern Void rgSCHCfgFreeCellCb (RgSchCellCb *cell);


extern S16 rgSCHCfgVldtRgrSiCfg ( Inst inst, RgrSiCfgReqInfo *siCfg, RgSchCellCb *cell, RgSchErrInfo *errInfo)
                                                                   ;
extern S16 rgSCHGomHndlSiCfg ( Region reg, Pool pool, RgSchCb *instCb, SpId spId, RgrCfgTransId transId, RgrSiCfgReqInfo *cfgReqInfo)

                                                                      ;
extern S16 rgSCHUtlRgrSiCfgCfm (Inst inst, SpId spId, RgrCfgTransId transId,U8 status)
                                                                   ;

extern S16 rgSCHGomHndlWarningSiCfg ( Region reg, Pool pool, RgSchCb *instCb, SpId spId, RgrCfgTransId transId, RgrWarningSiCfgReqInfo *warningSiCfgReqInfo)

                                                               ;

extern Void rgSCHGomHndlWarningSiStopReq ( Region reg, Pool pool, RgSchCb *instCb, U8 siId, RgrCfgTransId transId, SpId spId)

                                                       ;

extern S16 rgSCHUtlRgrWarningSiCfgCfm (Inst inst, SpId spId, U8 siId, RgrCfgTransId transId,U8 status)
                                                                   ;



extern S16 rgSchDSFRRntpInfoInit (TknStrOSXL *rntpPtr, RgSchCellCb *cell, U16 bw)
                                                   ;
extern S16 rgSchDSFRRntpInfoFree (TknStrOSXL *rntpPtr, RgSchCellCb *cell, U16 bw)
                                                   ;
extern S16 rgSchUpdtRNTPInfo (RgSchCellCb *cell, RgSchDlSf *sf, RgrLoadInfReqInfo *loadInfReq)
                                                                     ;
extern S16 rgSCHCfgVldtRgrLoadInf ( Inst inst, RgrLoadInfReqInfo *loadInfReq, RgSchCellCb *cell, RgSchErrInfo *errInfo)
                                                                   ;
extern S16 rgSCHGomHndlLoadInf ( Region reg, Pool pool, RgSchCb *instCb, SpId spId, RgrCfgTransId transId, RgrLoadInfReqInfo *cfgReqInfo)

                                                                          ;





extern S16 rgSCHGomHndlCfg (Region reg, Pool pool, RgSchCb *instCb, SpId spId, RgrCfgTransId transId, RgrCfgReqInfo *cfgReqInfo)
                                                                              ;
extern S16 rgSCHGomTtiHndlr (RgSchCellCb *cell, SpId spId);





extern S16 rgSCHRamVldtUeCfg ( RgSchCellCb *cell, RgrUeCfg *ueCfg )


  ;
extern S16 rgSCHRamProcRaReq (RgSchCellCb *cell, CmLteRnti raRnti, TfuRachInfo *raReqInd, CmLteTimingInfo timingInfo, RgSchErrInfo *err)


                                                       ;
extern S16 rgSCHRamCreateRaCb (RgSchCellCb *cell, RgSchRaCb **raCb, RgSchErrInfo *err)
                                                       ;
extern S16 rgSCHRamRgrUeCfg (RgSchCellCb *cell, RgSchUeCb *ue, RgSchRaCb *raCb, RgSchErrInfo *err)
                                                                        ;
extern S16 rgSCHRamProcMsg3 (RgSchCellCb *cell, RgSchUeCb *ue, RgSchRaCb *raCb, RgInfUeDatInd *pdu, RgSchErrInfo *err)

                                                       ;
extern S16 rgSCHRamUpdtBo (RgSchCellCb *cell, RgSchRaCb *raCb, RgInfCmnBoRpt *staRsp)
                                                           ;
extern S16 rgSCHRamMsg3DatInd (RgSchRaCb *raCb);
extern S16 rgSCHRamMsg3FailureInd (RgSchRaCb *raCb);
extern S16 rgSCHRamMsg4FdbkInd (RgSchRaCb *raCb);
extern S16 rgSCHRamMsg4Done (RgSchCellCb *cell, RgSchRaCb *raCb);
extern S16 rgSCHRamDelRaCb (RgSchCellCb *cell, RgSchRaCb *raCb, Bool rlsRnti)
                                                  ;
extern S16 rgSCHRamFreeCell (RgSchCellCb *cell);
extern S16 rgSCHRamTtiHndlr (RgSchCellCb *cell);
extern Void rgSCHCmnUlSch (RgSchCellCb *cell);
extern Void rgSCHCmnDlCommonChSch (RgSchCellCb *cell);


extern S16 rgSCHCmnBsrTmrExpry ( RgSchUeCb *ueCb);






extern S16 rgSCHRamAddToRaInfoSchdLst(RgSchCellCb *cell, RgSchRaCb *raCb);

extern S16 rgSCHRamRmvFrmRaInfoSchdLst(RgSchCellCb *cell, RgSchRaCb *raCb);



extern Void rgSCHUhmNonadapRetx (RgSchUlHqProcCb *hqProc);
extern S16 rgSCHUhmHqEntInit (RgSchCellCb *cellCb, RgSchUeCb *ueCb);

extern Void rgSCHUhmProcDatInd (RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo frm)
                              ;




extern Void rgSCHUhmProcMsg3DatInd (RgSchUlHqProcCb *hqProc);
extern Void rgSCHUhmProcMsg3Failure (RgSchUlHqProcCb *hqProc);

extern Void rgSCHUhmProcHqFailure (RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo frm, TknU8 rv)
                                        ;




extern RgSchUlHqProcCb* rgSCHUhmGetUlHqProc (RgSchCellCb *cell, RgSchUeCb *ue, U8 idx)
                 ;
extern Void rgSCHUhmNewTx (RgSchUlHqProcCb *hqProc, U8 maxHqRetx, RgSchUlAlloc *alloc)
                              ;
extern Void rgSCHUhmFreeProc (RgSchUlHqProcCb *hqProc, RgSchCellCb *cell)
                                 ;
extern Void rgSCHUhmRetx (RgSchUlHqProcCb *hqProc, RgSchUlAlloc *alloc);
extern Void rgSCHUhmRgrUeCfg ( RgSchCellCb *cellCb, RgSchUeCb *ueCb, RgrUeCfg *ueCfg)
                           ;
extern Void rgSCHUhmRgrUeRecfg ( RgSchCellCb *cellCb, RgSchUeCb *ueCb, RgrUeRecfg *ueRecfg)
                               ;
extern Void rgSCHUhmFreeUe ( RgSchCellCb *cellCb, RgUeUlHqCb *hqEnt);
extern S16 rgSCHUhmAppendPhich ( RgSchCellCb *cellCb, CmLteTimingInfo frm, U8 idx)
                                       ;


extern S16 rgSCHDbmInitCell (RgSchCellCb *cellCb);
extern S16 rgSCHDbmDeInitUeCbLst ( RgSchCellCb *cellCb);



extern S16 rgSCHDbmInsUeCb ( RgSchCellCb *cellCb, RgSchUeCb *ueCb);
extern RgSchUeCb* rgSCHDbmGetUeCb ( RgSchCellCb *cellCb, CmLteRnti ueId);
extern RgSchUeCb* rgSCHDbmGetNextUeCb ( RgSchCellCb *cellCb, RgSchUeCb *ueCb);
extern S16 rgSCHDbmDelUeCb ( RgSchCellCb *cellCb, RgSchUeCb *ueCb);



extern S16 rgSCHDbmInitUe (RgSchUeCb *ueCb);
extern Void rgSCHDbmInsDlDedLcCb (RgSchUeCb *ueCb, RgSchDlLcCb *dlLcCb);
extern Void rgSCHDbmDelDlDedLcCb (RgSchUeCb *ueCb, RgSchDlLcCb *dlLcCb);
extern RgSchDlLcCb* rgSCHDbmGetDlDedLcCb ( RgSchUeCb *ueCb, CmLteLcId idx);
extern RgSchDlLcCb* rgSCHDbmGetFirstDlDedLcCb (RgSchUeCb *ueCbb);
extern RgSchDlLcCb* rgSCHDbmGetNextDlDedLcCb (RgSchUeCb *ueCb, RgSchDlLcCb *lcCb);
extern RgSchClcDlLcCb* rgSCHDbmGetCmnLcCb ( RgSchCellCb *cellCb, CmLteLcId lcId);
extern RgSchClcDlLcCb* rgSCHDbmGetBcchOnBch ( RgSchCellCb *cellCb );
extern RgSchClcDlLcCb* rgSCHDbmGetFirstBcchOnDlsch ( RgSchCellCb *cellCb);
extern RgSchClcDlLcCb* rgSCHDbmGetSecondBcchOnDlsch ( RgSchCellCb *cellCb);
extern RgSchClcDlLcCb* rgSCHDbmGetPcch ( RgSchCellCb *cellCb);
extern Void rgSCHDbmInsBcchOnBch ( RgSchCellCb *cellCb, RgSchClcDlLcCb *cmnDlLcCb);
extern Void rgSCHDbmInsBcchOnDlsch ( RgSchCellCb *cellCb, RgSchClcDlLcCb *cmnDlLcCb);
extern Void rgSCHDbmInsPcch ( RgSchCellCb *cellCb, RgSchClcDlLcCb *cmnDlLcCb);

extern Void rgSCHDbmInitCmnLcBoLst ( RgSchClcDlLcCb *cmnDlLcCb);
extern Void rgSCHDbmInsCmnLcBoRpt ( RgSchClcDlLcCb *cmnDlLcCb, RgSchClcBoRpt *cmnBoRpt)
                                                             ;
extern RgSchRaCb* rgSCHDbmGetRaCb ( RgSchCellCb *cellCb, CmLteRnti key);
extern Void rgSCHDbmInsCrntRgrCfgElem ( RgSchCellCb *cellCb, RgSchCfgElem *cfgElem)
                                                                 ;
extern Void rgSCHDbmInsPndngRgrCfgElem ( RgSchCellCb *cellCb, RgSchCfgElem *cfgElem)
                                                                 ;
extern RgSchCfgElem* rgSCHDbmGetNextCrntRgrCfgElem ( RgSchCellCb *cellCb, RgSchCfgElem *cfgElem)
                                                                          ;
extern RgSchCfgElem* rgSCHDbmGetNextPndngRgrCfgElem ( RgSchCellCb *cellCb, RgSchCfgElem *cfgElem)
                                                                          ;
extern RgSchCfgElem* rgSCHDbmGetPndngRgrCfgElemByKey ( RgSchCellCb *cellCb, CmLteTimingInfo key)
                                                                        ;
extern RgSchCfgElem* rgSCHDbmDelCrntRgrCfgElem ( RgSchCellCb *cellCb, RgSchCfgElem *cfgElem)
                                                                       ;
extern RgSchCfgElem* rgSCHDbmDelPndngRgrCfgElem ( RgSchCellCb *cellCb, RgSchCfgElem *cfgElem)
                                                                       ;

extern S16 rgSCHDbmRntiDbInit ( RgSchCellCb *cellCb, U16 rntiStart, U16 maxRntis);
extern Void rgSCHDbmRntiDbDeInit ( RgSchCellCb *cellCb);
extern RgSchRntiLnk* rgSCHDbmGetRnti ( RgSchCellCb *cellCb);
extern Void rgSCHDbmRlsRnti ( RgSchCellCb *cellCb, RgSchRntiLnk *rntiLnk);

extern Void rgSCHUtlIndRntiRls2Mac ( RgSchCellCb *cell, CmLteRnti rnti, Bool ueIdChng, CmLteRnti newRnti)
                                                                            ;



extern S16 rgSCHDbmDeInitSpsUeCbLst (RgSchCellCb *cellCb);
extern S16 rgSCHDbmInsSpsUeCb (RgSchCellCb *cellCb, RgSchUeCb *ueCb);
extern RgSchUeCb* rgSCHDbmGetSpsUeCb (RgSchCellCb *cellCb, CmLteRnti ueId);
extern RgSchUeCb* rgSCHDbmGetNextSpsUeCb (RgSchCellCb *cellCb, RgSchUeCb *ueCb);
extern S16 rgSCHDbmDelSpsUeCb (RgSchCellCb *cellCb,RgSchUeCb *ueCb);
extern S16 rgSchSFRTotalPoolInit (RgSchCellCb *cell, RgSchDlSf *sf);


extern RgSchDlHqEnt *rgSCHDhmHqEntInit (RgSchCellCb *cell);
extern S16 rgSCHDhmGetAvlHqProc (RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo timingInfo, RgSchDlHqProcCb **hqP)
                                                          ;
extern Void rgSCHDhmHqRetx (RgSchDlHqEnt *hqE, CmLteTimingInfo timeInfo, RgSchDlHqProcCb *hqP)
                                                         ;
extern RgSchDlHqProcCb * rgSCHDhmLastSchedHqProc (RgSchDlHqEnt *hqE);

extern S16 rgSCHDhmGetCcchSduHqProc (RgSchUeCb *ueCb, CmLteTimingInfo timeInfo, RgSchDlHqProcCb **hqP)
                                                                 ;
extern S16 rgSCHDhmGetMsg4HqProc (RgSchRaCb *raCb, CmLteTimingInfo timeInfo);
extern Void rgSCHDhmRlsHqProc (RgSchDlHqProcCb *hqP);

extern Void rgSCHDhmRlsHqpTb (RgSchDlHqProcCb *hqP, U8 tbIdx, Bool togNdi);
extern Void rgSCHUtlDlHqPTbAddToTx (RgSchDlSf *subFrm, RgSchDlHqProcCb *hqP, U8 tbIdx )
                                 ;
extern Void rgSCHDhmHqTbRetx ( RgSchDlHqEnt *hqE, CmLteTimingInfo timingInfo, RgSchDlHqProcCb *hqP, U8 tbIdx)
                                                            ;
extern Void rgSCHUtlDlHqPTbAddToTx (RgSchDlSf *subFrm, RgSchDlHqProcCb *hqP, U8 tbIdx )
                                 ;
extern Void rgSCHDhmHqTbRetx ( RgSchDlHqEnt *hqE, CmLteTimingInfo timingInfo, RgSchDlHqProcCb *hqP, U8 tbIdx)
                                                            ;





extern Void rgSCHDhmSchdTa (RgSchUeCb *ueCb, RgSchDlHqTbCb *tbInfo);
extern S16 rgSCHDhmHqFdbkInd (Void *cb, U8 cbType, RgSchCellCb *cellCb, CmLteTimingInfo timingInfo, RgTfuHqInfo *fdbk, RgInfRlsHqInfo *rlsHqBufs,RgSchErrInfo *err)

                                                                  ;

extern S16 rgSCHDhmPrcFdbkForTb(RgSchCellCb *cell,RgSchUeCb *ue,
                               RgSchDlHqProcCb *hqP,RgSchDlSf *sf,Bool isMsg4,
                               U16 rnti,U8 tbCnt,CmLteTimingInfo timingInfo, U8 isAck,
                               RgInfRlsHqInfo *rlsHqBufs,RgSchErrInfo *err
                               );

extern Void rgSCHDhmRgrUeCfg (RgSchCellCb *cellCb, RgSchUeCb *ueCb, RgrUeCfg *ueCfg, RgSchErrInfo *err)
                                                                        ;
extern Void rgSCHDhmRgrUeRecfg (RgSchCellCb *cellCb, RgSchUeCb *ueCb, RgrUeRecfg *ueCfg, RgSchErrInfo *err)
                                                                          ;
extern Void rgSCHDhmRgrCellCfg (RgSchCellCb *cellCb, RgrCellCfg *cellCfg, RgSchErrInfo *err)
                                                       ;
extern Void rgSCHDhmRgrCellRecfg (RgSchCellCb *cellCb, RgrCellRecfg *cellRecfg, RgSchErrInfo *err)
                                                                   ;
extern Void rgSCHDhmFreeUe (RgSchUeCb *ueCb);
extern Void rgSCHDhmUpdTa (RgSchCellCb *cellCb, RgSchUeCb *ueCb, U8 ta);
extern Void rgSCHDhmProcTAExp (RgSchUeCb *ue);

extern S16 rgSCHDhmAddLcData (Inst inst, RgSchLchAllocInfo *lchData, RgSchDlHqTbCb *tbInfo)
                                                           ;
extern S16 rgSCHDhmRlsDlsfHqProc (RgSchCellCb *cellCb, CmLteTimingInfo timingInfo)
            ;
extern S16 rgSCHDhmGetHqProcFrmId ( RgSchCellCb *cell, RgSchUeCb *ue, U8 idx, RgSchDlHqProcCb **hqP )




  ;



extern S16 rgSCHDhmDlRetxAllocFail ( RgSchUeCb *ue, RgSchDlHqProcCb *proc )


  ;


extern Void rgSCHDhmHqEntReset ( RgSchDlHqEnt *hqE )

  ;


extern S16 rgSCHMeasGapANRepUeCfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *ueCfg )



  ;
extern S16 rgSCHMeasGapANRepUeRecfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *ueRecfg )



  ;

extern Void rgSCHMeasGapANRepUeDel ( RgSchCellCb *cell, RgSchUeCb *ue, Bool isUeDel )



  ;
extern S16 rgSCHMeasGapANRepTtiHndl ( RgSchCellCb *cell )

  ;
extern S16 rgSCHMeasGapANRepGetDlInactvUe ( RgSchCellCb *cell, CmLListCp *dlInactvUeLst )


  ;
extern S16 rgSCHMeasGapANRepGetUlInactvUe ( RgSchCellCb *cell, CmLListCp *ulInactvUeLst )


  ;
extern Void rgSCHMeasGapANRepDlInactvTmrExpry ( RgSchUeCb *ue, U8 tmrEvnt )


  ;
extern Void rgSCHMeasGapANRepUlInactvTmrExpry ( RgSchUeCb *ue, U8 tmrEvnt )


  ;
extern Void rgSCHMeasGapANRepTmrExpry ( RgSchUeCb *ue )

  ;
extern Void rgSCHAckNakRepTmrExpry ( RgSchUeCb *ue )

  ;
extern Void rgSCHAckNakRepSndHqFbkRcpReq ( RgSchCellCb *cell, RgSchDlSf *dlSf, CmLteTimingInfo timingInfo)


                                ;

extern Void rgSCHAckNakRepAddToQ ( RgSchCellCb *cell, RgSchDlSf *crntDlSf)

                             ;





extern Void rgSCHUtlHdlCrcInd ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo timingInfo )



  ;
extern F64 rgSCHUtlPower ( F64 x, F64 n )



  ;

 extern U32 rgSCHUtlParse ( U8 *buff, U8 startPos, U8 endPos, U8 buffSize )





   ;

 extern U8 rgSCHUtlFindDist ( U16 crntTime, U16 tempIdx )



  ;

extern Bool rgSCHUtlPdcchAvail (RgSchCellCb *cell, RgSchPdcchInfo *pdcchInfo, U32 loc, CmLteAggrLvl aggrLvl, RgSchPdcch **pdcch)
                                                                       ;
extern Void rgSCHUtlPdcchPut (RgSchCellCb *cell, RgSchPdcchInfo *pdcchInfo, RgSchPdcch *pdcch)
                           ;





extern S16 rgSCHUtlAddPhich (RgSchCellCb *cellCb, CmLteTimingInfo frm, U8 hqFeedBack, U8 nDmrs, U8 rbStart,Bool isForMsg3)
                                                             ;

extern RgSchDlSf* rgSCHUtlSubFrmGet (RgSchCellCb *cell, CmLteTimingInfo frm)
                              ;
extern Void rgSCHUtlSubFrmPut (RgSchCellCb *cell, RgSchDlSf *sf);
extern U8 rgSCHUtlLog32bitNbase2 (U32 n);
extern Void rgSCHUtlUpdY (U16 rnti, U32 y[]);
extern U32 rgSCHUtlGetY (RgSchUeCb *ue, U8 subFrm);




extern RgSchDlHqProcCb * rgSCHDhmSpsDlGetHqProc (RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo timingInfo)
                             ;





extern U8 rgSCHUtlCalcNCce (U8 bw, RgrPhichNg ng, U8 cfi, U8 numAntna, Bool isEcp)
       ;






extern S16 rgSCHUtlGetPhichInfo (RgSchUlHqProcCb *hqProc, U8 *rbStartRef, U8 *nDmrsRef)
                       ;
extern S16 rgSCHUtlAllocRcptInfo ( RgSchCellCb *cell, RgSchUlAlloc *alloc, CmLteTimingInfo *timeInfo, TfuUeUlSchRecpInfo *recpReq )




           ;


extern S16 rgSCHUtlRgrCellCfg (RgSchCellCb *cell, RgrCellCfg *cellCfg, RgSchErrInfo *errInfo)
                                ;
extern S16 rgSCHUtlRgrCellRecfg (RgSchCellCb *cell, RgrCellRecfg *recfg, RgSchErrInfo *errInfo)
                                ;
extern S16 rgSCHUtlFreeCell (RgSchCellCb *cell);
extern S16 rgSCHUtlRgrUeCfg (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *cfg, RgSchErrInfo *err)
                                           ;
extern S16 rgSCHUtlRgrLcCfg (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dl, RgrLchCfg *cfg,RgSchErrInfo *errInfo)
                                                                ;
extern S16 rgSCHUtlRgrLcDel (RgSchCellCb *cell, RgSchUeCb *ue, CmLteLcId lcId, U8 lcgId)
                                   ;
extern S16 rgSCHUtlRgrLcRecfg (RgSchCellCb *cell,RgSchUeCb *ue, RgSchDlLcCb *dlLc,RgrLchRecfg *recfg,RgSchErrInfo *err)
                                                              ;
extern S16 rgSCHUtlRgrLcgCfg (RgSchCellCb *cell,RgSchUeCb *ue, RgrLcgCfg *cfg,RgSchErrInfo *errInfo)
                                               ;
extern S16 rgSCHUtlRgrLcgRecfg (RgSchCellCb *cell,RgSchUeCb *ue, RgrLcgRecfg *recfg,RgSchErrInfo *err)
                                               ;
extern Void rgSCHUtlRgrLcgDel (RgSchCellCb *cell,RgSchUeCb *ue, U8 lcgId)
                   ;
extern Void rgSCHUtlDlCqiInd (RgSchCellCb *cell, RgSchUeCb *ue, TfuDlCqiRpt *dlCqiInd, CmLteTimingInfo timingInfo)
                                                            ;



extern Void rgSCHUtlRawCqiInd ( RgSchCellCb *cell, RgSchUeCb *ue, TfuRawCqiRpt* rawCqiRpt, CmLteTimingInfo timingInfo )





  ;

extern Void rgSCHUtlSrsInd ( RgSchCellCb *cell, RgSchUeCb *ue, TfuSrsRpt* srsRpt, CmLteTimingInfo timingInfo )





  ;
extern S16 rgSCHUtlGetCfgPerOff ( RgSchPerTbl tbl, U16 cfgIdx, U16 *peri, U16 *offset )





  ;


extern Void rgSCHUtlDoaInd (RgSchCellCb *cell, RgSchUeCb *ue, TfuDoaRpt *doaInd)
                            ;
extern Void rgSCHUtlDlTARpt (RgSchCellCb *cell, RgSchUeCb *ue);

extern Void rgSCHUtlDlRlsSubFrm (RgSchCellCb *cell, CmLteTimingInfo subFrm);
extern Void rgSCHUtlDlProcAddToRetx (RgSchCellCb *cell, RgSchDlHqProcCb *hqP)
                               ;
extern S16 rgSCHUtlRegSch (U8 schIdx, RgSchdApis *apis);
extern Void rgSCHUtlDlHqProcAddToTx (RgSchDlSf *subFrm, RgSchDlHqProcCb *hqP);

extern Void rgSCHUtlDlHqPTbRmvFrmTx (RgSchDlSf *subFrm, RgSchDlHqProcCb *hqP, U8 tbIdx, Bool isRepeating)
                                                           ;
extern S16 rgSCHUtlRgrUeRecfg (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *recfg, RgSchErrInfo *err)
                                               ;
extern Void rgSCHUtlFreeDlLc (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc)
                            ;
extern Void rgSCHUtlFreeUlLc (RgSchCellCb *cell, RgSchUeCb *ue, RgSchUlLcCb *ulLc)
                            ;
extern Void rgSCHUtlFreeUe (RgSchCellCb *cell, RgSchUeCb *ue);
extern Void rgSCHUtlDlDedBoUpd (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *svc)
                           ;





extern Void rgSCHUtlRecMsg3Alloc (RgSchCellCb *cell, RgSchUeCb *ue, RgSchRaCb *raCb)
                          ;
extern S16 rgSCHUtlContResUlGrant (RgSchCellCb *cell, RgSchUeCb *ue, RgSchErrInfo *err)
                            ;
extern S16 rgSCHUtlSrRcvd (RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo, RgSchErrInfo *err)
                                             ;
extern Void rgSCHUtlUpdBsrShort (RgSchCellCb *cell, RgSchUeCb *ue, U8 lcgId, U8 bsr, RgSchErrInfo *err)
                                    ;
extern Void rgSCHUtlUpdBsrTrunc (RgSchCellCb *cell, RgSchUeCb *ue, U8 lcgId, U8 bsr, RgSchErrInfo *err)
                                    ;
extern Void rgSCHUtlUpdBsrLong (RgSchCellCb *cell, RgSchUeCb *ue, U8 bsr1,U8 bsr2,U8 bsr3,U8 bsr4, RgSchErrInfo *err)
                                                             ;
extern S16 rgSCHUtlUpdPhr (RgSchCellCb *cell, RgSchUeCb *ue, U8 phr, RgSchErrInfo *err)
                                    ;
extern S16 rgSCHUtlUpdExtPhr ( RgSchCellCb *cell, RgSchUeCb *ue, RgInfExtPhrCEInfo * extPhr, RgSchErrInfo *err)
                                               ;
extern S16 rgSCHUtlDataRcvd (RgSchCellCb *cell, RgSchUeCb *ue, U8 numLc, RgSchUlLcCb *lcArr[], U16 bytesArr[], RgSchErrInfo *err)
                                                                  ;
extern Void rgSCHUtlUlCqiInd ( RgSchCellCb *cell, RgSchUeCb *ue, TfuUlCqiRpt *ulCqiInfo)
                                                            ;
extern Void rgSCHUtlPucchDeltaPwrInd ( RgSchCellCb *cell, RgSchUeCb *ue, S8 delta)
                   ;
extern Void rgSCHUtlUeReset ( RgSchCellCb *cell, RgSchUeCb *ue);
extern Void rgSCHUtlUlHqProcForUe (RgSchCellCb *cell, CmLteTimingInfo frm, RgSchUeCb *ue, RgSchUlHqProcCb **procRef)
                                                   ;
extern RgSchUlAlloc *rgSCHUtlFirstRcptnReq (RgSchCellCb *cell);
extern RgSchUlAlloc *rgSCHUtlNextRcptnReq (RgSchCellCb *cell, RgSchUlAlloc *alloc)
                              ;
extern RgSchUlAlloc *rgSCHUtlFirstHqFdbkAlloc (RgSchCellCb *cell, U8 idx);
extern RgSchUlAlloc *rgSCHUtlNextHqFdbkAlloc (RgSchCellCb *cell, RgSchUlAlloc *alloc, U8 idx)
                                      ;
extern S16 rgSCHUtlTfuBndReq (Inst inst, SuId suId, SpId spId);
extern S16 rgSCHUtlTfuUBndReq (Inst inst, RgSchLowSapCfgInfo sapCfg, Reason reason);
extern S16 rgSCHUtlResetSfAlloc (RgInfSfAlloc *sfAlloc, Bool resetCmnLcInfo, Bool restAlloc)
                                                 ;
extern S16 rgSCHUtlGetSfAlloc (RgSchCellCb *cell);
extern S16 rgSCHUtlPutSfAlloc (RgSchCellCb *cell);
extern S16 rgSCHUtlAllocSBuf (Inst inst, Data **pData, Size size);


extern Void rgSCHUtlFreeSBuf (Inst inst, Data **data, Size size);
extern Void rgSCHUtlFillDgnParams (Inst inst, RgUstaDgn *dgn,U8 dgnType);
extern Void rgSCHUtlGetPstToLyr (Pst *pst,RgSchCb *schCb,Inst macInst);
extern S16 rgSCHUtlFillRgInfCmnLcInfo (RgSchDlSf *sf,RgInfSfAlloc *sfAlloc, CmLteLcId lcId, Bool sendInd)
                                                               ;
extern S16 rgSCHUtlFillRgInfRarInfo (RgSchDlSf *sf,RgInfSfAlloc *sfAlloc,RgSchCellCb *cell);
extern S16 rgSCHUtlFillPdschDciInfo (TfuPdschDciInfo *pdschDci,TfuDciInfo *pdcchDci)
                   ;

extern Void rgSCHUtlFillRgInfUeInfo (RgSchDlSf*, RgSchCellCb *cell, CmLListCp *dlDrxInactvTmrLst, CmLListCp *dlInActvLst, CmLListCp *ulInActvLst)
                                                                                          ;

extern S16 rgSCHUtlUpdSch (RgInfSfDatInd *subfrmInfo, RgSchCellCb *cellCb, RgSchUeCb *ueCb, RgInfUeDatInd *pdu,RgSchErrInfo *err)
                                                                      ;
extern S16 rgSCHUtlHndlCcchBoUpdt (RgSchCellCb *cell,RgInfCmnBoRpt *boRpt);
extern S16 rgSCHUtlHndlBcchPcchBoUpdt (RgSchCellCb *cell,RgInfCmnBoRpt *boUpdt)
                 ;
extern S16 rgSCHUtlRgrBndCfm (Inst inst, SuId suId,U8 status);


extern S16 rgSCHUtlRgrTtiInd (RgSchCellCb *cell, RgrTtiIndInfo *ttiInd);





extern S16 rgSCHUtlRgrCfgCfm (Inst inst, SpId spId, RgrCfgTransId transId,U8 status)
                                                                   ;

extern S16 rgSCHUtlProcMsg3 (RgInfSfDatInd *subfrmInfo, RgSchCellCb *cellCb, RgSchUeCb *ueCb, CmLteRnti rnti,RgInfUeDatInd *pdu, RgSchErrInfo *err )

                                ;




extern S16 rgSCHUtlTfuCntrlReq (Inst inst, S16 sapId, TfuCntrlReqInfo *cntrlReq)
                                    ;
extern S16 rgSCHUtlTfuRecpReq (Inst inst, S16 sapId, TfuRecpReqInfo *recpReq)
                                  ;
extern S16 rgSCHUtlValidateTfuSap (Inst inst,SuId suId);
extern S16 rgSCHUtlAllocEventMem (Inst inst,Ptr *memPtr,Size memSize);
extern S16 rgSCHUtlGetEventMem (Ptr *ptr,Size len,Ptr memCpa);
extern S16 rgSCHUtlGetRlsHqAlloc (RgSchCellCb *cell);
extern S16 rgSCHUtlPutRlsHqAlloc (RgSchCellCb *cell);

extern S16 rgSCHUtlDlActvtUe (RgSchCellCb *cell, RgSchUeCb *ue);
extern S16 rgSCHUtlUlActvtUe (RgSchCellCb *cell, RgSchUeCb *ue);
extern Void rgSCHUtlHdlUlTransInd (RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo timingInfo)
                                                               ;

extern Void rgSCHUtlUpdACqiTrigWt (RgSchUeCb *ue,RgSchUeCellInfo *sCellInfo, U8 isAck);



extern S32 rgSCHUtlGetAllwdCchTbSz (U32 bo, U8 *nPrb, U8 *mcs )
  ;

extern S16 rgSCHUtlUpdtBo (RgSchCellCb *cell, RgInfCmnBoRpt *staRsp)
                                                          ;
extern S16 rgSCHUtlAddUeToCcchSduLst (RgSchCellCb *cell, RgSchUeCb *ueCb)

                                                     ;


extern Void rgSCHUtlPutSiInfo (RgSchCellCb *cell);
extern Void rgSCHUtlFreeWarningSiSeg (Region reg,Pool pool, CmLListCp *siPduLst)
                                                                 ;
extern Void rgSCHUtlFreeWarningSiPdu (RgSchCellCb *cell);
extern Buffer *rgSCHUtlGetWarningSiPdu (RgSchCellCb *cell);
extern S16 rgSCHUtlGetMcsAndNPrb (RgSchCellCb *cell, U8 *nPrb, U8 *mcs, MsgLen *msgLen);
extern S16 rgSCHUtlCalMcsAndNPrb (RgSchCellCb *cell, U8 cfgType, MsgLen msgLen, U8 siId);
extern Void rgSCHCmnDlSch ( RgSchCellCb *cell )


  ;
extern Void rgSCHCmnSndCnsldtInfo ( RgSchCellCb *cell )


  ;
extern Void rgSCHCmnCnsldtSfAlloc ( RgSchCellCb *cell )


  ;


extern Void rgSCHCmnDlAllocFnlz ( RgSchCellCb *cell )


  ;


extern Void rgSCHUtlDlRelPdcchFbk ( RgSchCellCb *cell, RgSchUeCb *ue, Bool isAck )



  ;

extern Void rgSCHUtlDlProcAck ( RgSchCellCb *cell, RgSchDlHqProcCb *hqP )


  ;
extern S16 rgSCHUtlSpsRelInd ( RgSchCellCb *cellCb, RgSchUeCb *ueCb, Bool isExplRel )



  ;

extern Void rgSCHCmnDlSch ( RgSchCellCb *cell )


  ;

extern S16 rgSCHUtlSpsActInd ( RgSchCellCb *cellCb, RgSchUeCb *ueCb, U16 spsSduSize )



  ;

extern Void rgSCHUtlHdlCrcFailInd ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo timingInfo )



  ;

extern Void rgSCHUtlHdlCrntiCE ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;




extern S16 rgSCHUtlUlSfInit ( RgSchCellCb *cell, RgSchUlSf *sf, U8 idx, U8 maxUePerSf )




           ;
extern Void rgSCHUtlUlSfDeinit ( RgSchCellCb *cell, RgSchUlSf *sf )


           ;
extern RgSchUlAlloc *rgSCHUtlUlAllocGetHole ( RgSchUlSf *sf, U8 numRb, RgSchUlHole *hole )



           ;
extern RgSchUlAlloc *rgSCHUtlUlAllocGetCompHole ( RgSchUlSf *sf, RgSchUlHole *hole )


           ;
extern RgSchUlAlloc *rgSCHUtlUlAllocGetPartHole ( RgSchUlSf *sf, U8 numRb, RgSchUlHole *hole )



           ;
extern Void rgSCHUtlUlAllocRls ( RgSchUlSf *sf, RgSchUlAlloc *alloc )


           ;


extern Void rgSCHUtlUlAllocRelease ( RgSchUlAlloc *alloc )

           ;
extern RgSchUlAlloc *rgSCHUtlUlAllocFirst ( RgSchUlSf *sf )

           ;
extern RgSchUlAlloc *rgSCHUtlUlAllocNxt ( RgSchUlSf *sf, RgSchUlAlloc *alloc )


           ;
extern RgSchUlHole *rgSCHUtlUlHoleFirst ( RgSchUlSf *sf )

           ;
extern RgSchUlHole *rgSCHUtlUlHoleNxt ( RgSchUlSf *sf, RgSchUlHole *hole )


           ;
extern RgSchUlAlloc *rgSCHUtlUlAllocGetAdjNxt ( RgSchUlAllocDb *db, RgSchUlAlloc *prv )


           ;
extern RgSchUlAlloc *rgSCHUtlUlAllocGetFirst ( RgSchUlAllocDb *db )

           ;
extern Void rgSCHUtlUlHoleAddAlloc ( RgSchUlSf *sf, RgSchUlAlloc *alloc )


           ;

extern Void rgSCHUtlUlHoleAddAllocation ( RgSchUlAlloc *alloc )

           ;

extern Void rgSCHUtlUlHoleJoin ( RgSchUlHoleDb *db, RgSchUlHole *prv, RgSchUlHole *nxt, RgSchUlAlloc *alloc )




           ;
extern Void rgSCHUtlUlHoleExtndRight ( RgSchUlHoleDb *db, RgSchUlHole *prv, RgSchUlAlloc *alloc )



           ;
extern Void rgSCHUtlUlHoleExtndLeft ( RgSchUlHoleDb *db, RgSchUlHole *nxt, RgSchUlAlloc *alloc )



           ;
extern Void rgSCHUtlUlHoleNew ( RgSchUlHoleDb *db, RgSchUlAlloc *alloc )


           ;
extern Void rgSCHUtlUlHoleUpdAllocLnks ( RgSchUlHole *hole, RgSchUlAlloc *prvAlloc, RgSchUlAlloc *nxtAlloc )



           ;
extern Void rgSCHUtlUlHoleIns ( RgSchUlHoleDb *db, RgSchUlHole *hole )


           ;
extern Void rgSCHUtlUlHoleIncr ( RgSchUlHoleDb *db, RgSchUlHole *hole )


           ;
extern Void rgSCHUtlUlHoleDecr ( RgSchUlHoleDb *db, RgSchUlHole *hole )


           ;
extern Void rgSCHUtlUlHoleRls ( RgSchUlHoleDb *db, RgSchUlHole *hole )


           ;
extern S16 rgSCHUtlUlAllocMemInit ( RgSchCellCb *cell, RgSchUlAllocMem *mem, U8 maxAllocs )



           ;
extern Void rgSCHUtlUlAllocMemDeinit ( RgSchCellCb *cell, RgSchUlAllocMem *mem )


           ;
extern S16 rgSCHUtlUlHoleMemInit ( RgSchCellCb *cell, RgSchUlHoleMem *mem, U8 maxHoles, RgSchUlHole **holeRef )




           ;
extern Void rgSCHUtlUlHoleMemDeinit ( RgSchCellCb *cell, RgSchUlHoleMem *mem )


           ;
extern RgSchUlAlloc *rgSCHUtlUlAllocMemGet ( RgSchUlAllocMem *mem )

           ;
extern Void rgSCHUtlUlAllocMemRls ( RgSchUlAllocMem *mem, RgSchUlAlloc *alloc )


           ;
extern RgSchUlHole *rgSCHUtlUlHoleMemGet ( RgSchUlHoleMem *mem )

           ;
extern Void rgSCHUtlUlHoleMemRls ( RgSchUlHoleMem *mem, RgSchUlHole *hole )


           ;
extern RgSchUlAlloc *rgSCHUtlUlGetSpfcAlloc ( RgSchUlSf *sf, U8 startSb, U8 numSb )



  ;



extern S16 rgSCHDrxCellCfg (RgSchCellCb *cell, RgrCellCfg *cellCfg);
extern Void rgSCHDrxCellDel (RgSchCellCb *cell);
extern S16 rgSCHDrxUeCfg (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *ueCfg)
                                               ;

extern S16 rgSCHDrxUeReCfg (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *ueCfg)
                                                 ;

extern S16 rgSCHDrxUeDel (RgSchCellCb *cell,RgSchUeCb *ue);
extern Void rgSCHDrxTtiInd (RgSchCellCb *cell);

extern S16 rgSCHDrxSfAlloc (RgSchCellCb *cellCb, RgSchDlSf *dlSf)
                                  ;
extern S16 rgSCHDrxDlTrnsFail (RgSchCellCb *cell, RgSchDlHqProcCb *dlHq)
                                    ;
extern Void rgSCHDrxDedRa (RgSchCellCb *cellCb, RgSchUeCb* ueCb);
extern S16 rgSCHDrxSrInd (RgSchCellCb *cell,RgSchUeCb *ue);

extern Void rgSCHDrxStrtInActvTmr (RgSchCellCb *cell, CmLListCp *ueLst, U8 direction)

                                                     ;
extern S16 rgSCHUtlGetDrxSchdUesInDl (RgSchCellCb *cellCb, RgSchUeCb *ueCb, RgSchDlHqProcCb *dlHq, RgInfUeAlloc *allocInfo, CmLListCp *dlDrxInactvTmrLst, CmLListCp *dlInActvLst, CmLListCp *ulInActvLst)





                                                                      ;
extern Void rgSCHDrxStartHarqRTTTmr (RgSchCellCb *cell, RgSchDlHqProcCb *hqP, U8 tbCnt)

                                                                 ;
extern Void rgSCHDrxUeHqReset (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlHqEnt *hqE, U8 cellIdx)


                                                          ;





extern const RgSchFddCellSpSrsSubfrmTbl rgSchFddCellSpSrsSubfrmTbl;
 S16 rgSCHUtlRgrStaInd ( RgSchCellCb *cell, RgrStaIndInfo *rgrSta )


  ;

 S16 rgSCHUtlFillSndStaInd ( RgSchCellCb *cell, RgSchUeCb *ue, RgrStaIndInfo *staInfo, U8 numCqiRept )




  ;

 S16 rgSCHUtlRgrUeStaInd ( RgSchCellCb *cell, RgrUeStaIndInfo *rgrUeSta )


  ;

 S16 rgSCHUtlFillSndUeStaInd ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeStaIndInfo *ueStaInfo )



  ;



 S16 rgSCHUtlRgrLoadInfInd ( RgSchCellCb *cell, RgrLoadInfIndInfo *rgrLoadInf )


  ;
 Void rgSCHUtlRlsRnti ( RgSchCellCb *cellCb, RgSchRntiLnk *rntiLnk, Bool ueIdChngd, CmLteRnti newRnti )




  ;
 S16 rgSCHUtlRgmBndCfm ( Inst instId, SuId suId, U8 status )



  ;
 Void rgSCHDhmDelHqEnt ( RgSchCellCb *cell, RgSchDlHqEnt **hqE )


  ;
 Void rgSCHDhmAssgnUeHqEntFrmRaCb ( RgSchUeCb *ue, RgSchRaCb *raCb )


  ;
 Void rgSCHUtlReTxTa ( RgSchCellCb *cellCb, RgSchUeCb *ueCb)

                 ;

 Void rgSchSFRTotalPoolFree ( RgSchSFRTotalPoolInfo *sfrTotalPoolInfo, RgSchCellCb *cell)

                               ;
 Void rgSchDSFRPwrCheck ( RgSchDlSf *sf, Bool *isAllUePwrHigh)

                                         ;


 S16 rgSCHUtlUpdAvgPrbUsage ( RgSchCellCb *cell )

  ;

 U8 rgSchUtlCfg0ReTxIdx ( RgSchCellCb *cell, CmLteTimingInfo phichTime, U8 hqFdbkIdx )



  ;

extern S16 rgSCHUtlBuildNSendLcgReg ( RgSchCellCb *cell, CmLteRnti crnti, U8 lcgId, Bool isGbr )




  ;

extern Void rgSCHUtlPdcchInit ( RgSchCellCb *cell, RgSchDlSf *subFrm, U16 nCce)


                            ;
extern Void rgSCHDynCfiReCfg ( RgSchCellCb *cell, Bool isDynCfiEnb )


  ;
 Void rgSchUtlCalcTotalPrbReq (RgSchCellCb *cell, RgSchUeCb *ue, U32 bo, U32 *prbReqrd)


                                                                  ;
extern U8 rgSchUtlGetNumSbs ( RgSchCellCb *cell, RgSchUeCb *ue, U32 *numSbs )



  ;

extern U8 rgSchUtlSortInsUeLst ( RgSchCellCb *cell, CmLListCp *ueLst, CmLList *node, U8 subbandRequired )




  ;
extern S16 rgSCHUtlResetCpuOvrLdState ( RgSchCellCb *cell, U8 cnrtCpuOvrLdIns )


  ;
extern Void rgSCHUtlCpuOvrLdAdjItbsCap ( RgSchCellCb *cell )

  ;

extern S16 rgSCHTomUtlPcqiSbCalcBpIdx ( CmLteTimingInfo crntTimInfo, RgSchUeCb *ueCb, RgSchUePCqiCb *cqiCb )



  ;
extern Void rgSCHTomUtlGetTrigSet ( RgSchCellCb *cell, RgSchUeCb *ueCb, U8 cqiReq, U8 *triggerSet )




  ;

extern Void rgSCHUtlUpdUeDciSize ( RgSchCellCb *cell, RgSchUeCb *ueCb, Bool isCsi2Bit )



  ;
extern Void rgSCHUtlCalcDciSizes ( RgSchCellCb *cell )

  ;

extern Void rgSchCmnPreDlSch ( RgSchCellCb **cell, U8 nCell, RgSchCellCb **cellLst )



   ;

extern Void rgSchCmnPstDlSch ( RgSchCellCb *cell )

   ;

extern S16 rgSCHLaaErrInd ( RgSchCellCb *cell, TfuErrIndInfo *errInd )


  ;

extern Void rgSCHLaaSch ( RgSchCellCb *cell )

  ;

extern Bool rgSCHLaaSCellEnabled ( RgSchCellCb *cell )

   ;

extern S16 rgSCHLaaSCellCbInit ( RgSchCellCb *cell )

   ;

extern Void rgSCHLaaSCellCbDeInit ( RgSchCellCb *cell )

   ;
typedef struct _rgDlSchdApis RgDlSchdApis;
typedef struct _rgUlSchdApis RgUlSchdApis;
typedef struct _rgDlfsSchdApis RgDlfsSchdApis;
typedef Void (*RgDlSchdInits[4]) (RgDlSchdApis *apis);
typedef Void (*RgUlSchdInits[4]) (RgUlSchdApis *apis);
typedef Void (*RgDlfsSchdInits[4]) (RgDlfsSchdApis *apis);
typedef struct rgSchCmnDlRbAllocInfo RgSchCmnDlRbAllocInfo;
typedef struct rgSchCmnUeUlAlloc RgSchCmnUeUlAlloc;
typedef struct rgSchCmnUlRbAllocInfo RgSchCmnUlRbAllocInfo;





struct _rgUlSchdApis
{
   S16 (*rgSCHRgrUlUeCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *cfg, RgSchErrInfo *err)
                                                                        ;
   S16 (*rgSCHRgrUlUeRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *recfg, RgSchErrInfo *err)
                                                                        ;
   Void (*rgSCHFreeUlUe) (RgSchCellCb *cell, RgSchUeCb *ue);
   S16 (*rgSCHRgrUlCellCfg) (RgSchCellCb *cell, RgrCellCfg *cfg, RgSchErrInfo *err)
                                                                        ;
   S16 (*rgSCHRgrUlCellRecfg) (RgSchCellCb *cell, RgrCellRecfg *recfg, RgSchErrInfo *err)
                                                                        ;
   Void (*rgSCHFreeUlCell) (RgSchCellCb *cell);
   S16 (*rgSCHRgrUlLcgCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg, RgrLcgCfg *cfg, RgSchErrInfo *errInfo)
                                                                 ;
   S16 (*rgSCHRgrUlLcCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrLchCfg *cfg, RgSchErrInfo *errInfo)
                                                ;
   S16 (*rgSCHRgrUlLcgRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg, RgrLcgRecfg *recfg, RgSchErrInfo *errInfo)
                                                                     ;
   S16 (*rgSCHRgrUlLcRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrLchRecfg *recfg, RgSchErrInfo *errInfo)
                                                    ;
   Void (*rgSCHFreeUlLcg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg);
   S16 (*rgSCHRgrUlLchDel) (RgSchCellCb *cell, RgSchUeCb *ue, CmLteLcId lcId, U8 lcgId);
   Void (*rgSCHUlActvtUe) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHUpdBsrShort) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *ulLcg, U8 bsr);
   Void (*rgSCHUpdBsrTrunc) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *ulLcg, U8 bsr);
   Void (*rgSCHUpdBsrLong) (RgSchCellCb *cell, RgSchUeCb *ue, U8 bsArr[]);
   Void (*rgSCHContResUlGrant) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHSrRcvd) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHUlSched) (RgSchCellCb *cell, RgSchCmnUlRbAllocInfo *allocInfo)
                        ;
   Void (*rgSCHUlCqiInd) ( RgSchCellCb *cell, RgSchUeCb *ue, TfuUlCqiRpt *ulCqiInfo);
   S16 (*rgSCHRgrUlLcgUpd) (RgSchCellCb *cell, RgSchUeCb *ue, RgInfUeDatInd *datInd);
   Void (*rgSCHUlUeRefresh) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHUlUeReset) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHUlAllocFnlz) (RgSchCellCb *cell, RgSchCmnUlRbAllocInfo *allocInfo)
                                             ;
   Void (*rgSCHUlInactvtUes) (RgSchCellCb *cell, CmLListCp *lst);
};





struct _rgDlSchdApis
{
   S16 (*rgSCHRgrDlUeCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *cfg, RgSchErrInfo *err)
                                                                        ;
   S16 (*rgSCHRgrDlUeRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *recfg, RgSchErrInfo *err)
                                                                        ;
   Void (*rgSCHFreeDlUe) (RgSchCellCb *cell, RgSchUeCb *ue);
   S16 (*rgSCHRgrDlCellCfg) (RgSchCellCb *cell, RgrCellCfg *cfg, RgSchErrInfo *err)
                                                                        ;
   S16 (*rgSCHRgrDlCellRecfg) (RgSchCellCb *cell, RgrCellRecfg *recfg, RgSchErrInfo *err)
                                                                        ;
   Void (*rgSCHFreeDlCell) (RgSchCellCb *cell);
   S16 (*rgSCHRgrDlLcCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dl, RgrLchCfg *cfg, RgSchErrInfo *errInfo)

                                ;
   S16 (*rgSCHRgrDlLcRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dl, RgrLchRecfg *recfg, RgSchErrInfo *errInfo)

                                ;
   Void (*rgSCHFreeDlLc) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc);
   Void (*rgSCHDlActvtUe) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHDlNewSched) (RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo);
   Void (*rgSCHDlPreSched) (RgSchCellCb *cell);
   Void (*rgSCHDlPstSched) (Inst schInst);
   Void (*rgSCHDlRetxSched) (RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo);
   Void (*rgSCHDlCeSched) (RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo);
   Void (*rgSCHDlDedBoUpd) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *svc);
   Void (*rgSCHDlProcAddToRetx) (RgSchCellCb *cell,RgSchDlHqProcCb *hqP);
   Void (*rgSCHDlCqiInd) (RgSchCellCb *cell, RgSchUeCb *ue, Bool isPucchInfo, Void *dlCqi);

   Void (*rgSCHSrsInd) (RgSchCellCb *cell, RgSchUeCb *ue, TfuSrsRpt*srsInd);

   Void (*rgSCHDlAllocFnlz) (RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo)
                                             ;
   Void (*rgSCHDlUeRefresh) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHDlUeReset) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHDlInactvtUes) (RgSchCellCb *cell, CmLListCp *lst);

   S16 (*rgSCHDlUeHqEntInit) (RgSchCellCb *cell, RgSchDlHqEnt *hqE);

   S16 (*rgSCHDlUeHqEntDeInit) (RgSchCellCb *cell, RgSchDlHqEnt *hqE);
   Void (*rgSCHDlProcRmvFrmRetx) (RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlHqProcCb *hqP);







   Void (*rgSCHDlTickForPdbTrkng ) (RgSchCellCb *cell);
   S16 (*rgSCHDlFillFlwCtrlInfo) (RgSchCellCb *cell, RgInfSfAlloc *sfAlloc);
};





struct _rgDlfsSchdApis
{
   S16 (*rgSCHDlfsCellCfg) (RgSchCellCb *cell, RgrCellCfg *cfg, RgSchErrInfo *err)
                                                                        ;
   S16 (*rgSCHDlfsCellRecfg) (RgSchCellCb *cell, RgrCellRecfg *recfg, RgSchErrInfo *err)
                                                                        ;
   Void (*rgSCHDlfsCellDel) (RgSchCellCb *cell);
   S16 (*rgSCHDlfsUeCfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *cfg, RgSchErrInfo *err)
                                                                 ;
   S16 (*rgSCHDlfsUeRecfg) (RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *recfg, RgSchErrInfo *err)
                                                                       ;
   Void (*rgSCHDlfsUeDel) (RgSchCellCb *cell, RgSchUeCb *ue);
   Void (*rgSCHDlfsDlCqiInd) (RgSchCellCb *cell, RgSchUeCb *ue, Bool isPucchInfo, Void *dlCqiRpt, CmLteTimingInfo timingInfo)


                                                              ;
   Void (*rgSCHDlfsReinitSf) (RgSchCellCb *cell, RgSchDlSf *dlSf);
   Void (*rgSCHDlfsAllocRb) (RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *dlRbAllocInfo)
                                                 ;

   Void (*rgSCHDlfsBcchPcchAllocRb) (RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *dlRbAllocInfo);
   Void (*rgSCHDlfsAddUeToLst) (RgSchCellCb *cell, CmLListCp *lCp, RgSchDlHqProcCb *hqP);
};

typedef enum rgSchCmnTpcAccVal
{
   RG_SCH_CMN_TPC_ACC_NEG_1DB = 0,
   RG_SCH_CMN_TPC_ACC_0DB = 1,
   RG_SCH_CMN_TPC_ACC_1DB = 2,
   RG_SCH_CMN_TPC_ACC_3DB = 3
} RgSchCmnTpcAccVal;

typedef enum rgSchCmnTpcAbsVal
{
   RG_SCH_CMN_TPC_ABS_NEG_4DB = 0,
   RG_SCH_CMN_TPC_ABS_NEG_1DB = 1,
   RG_SCH_CMN_TPC_ABS_1DB = 2,
   RG_SCH_CMN_TPC_ABS_4DB = 3
} RgSchCmnTpcAbsVal;


typedef enum rgSchCmnRank
{
   RG_SCH_CMN_RANK_1 = 1,
   RG_SCH_CMN_RANK_2 = 2,
   RG_SCH_CMN_RANK_3 = 3,
   RG_SCH_CMN_RANK_4 = 4
} RgSchCmnRank;


typedef struct rgSchCmnUlCqiInfo
{
   U8 qm;
   U16 eff;
} RgSchCmnUlCqiInfo;

extern RgSchCmnUlCqiInfo rgSchCmnUlCqiTbl[16];
extern S8 rgSchCmnDlCqiDiffOfst[8];


extern S8 rgSchCmnApUeSelDiffCqi[4];
extern S8 rgSchCmnApEnbConfDiffCqi[4];



extern U8 rgSchCmnUlCqiToTbsTbl[2][16];
typedef struct rgSchCmnSpsDlUeSchdInfo
{
   U8 scaledCqi;
   U16 actvSfTblIdx;

   CmLteTimingInfo schdKey;

   RgSchDlRbAlloc spsAllocInfo;

   U8 allocN1PucchIdx;




} RgSchCmnSpsDlUeSchdInfo;





typedef struct rgSchCmnDlUeSpsStatInfo
{
   U32 numSchedSPSRnti;
   U32 totalSPSSchedOcc;

   U32 numSpsReactv;
   U32 numSpsActv;
   U32 numSpsRel;
}RgSchCmnDlUeSpsStatInfo;





typedef struct rgSchCmnDlUeSpsInfo
{
   CmLteTimingInfo prevDlBoUpdTm;
   CmLList zeroBOSvcUesEnt;
   CmLList actvUeLstEnt;

   CmLList pndngUeLstEnt;




   CmLList wtngForRelFdbkUeEnt;


   RgSchDlLcCb *spsSvc;

   CmLListCp *spsList;

   U32 measGapMask[3];


   U16 n1PucchIdx[4];

   U8 actionPndng;

   U8 dlSpsStatus;
   U8 prdIdx;

   RgSchCmnSpsDlUeSchdInfo dlSpsUeSchdInfo;

   Bool isRelPdcchSent;




   U8 numRelPdcchSent;

   RgSchCmnDlUeSpsStatInfo statInfo;
   U8 dynSchedCount;

   U8 reducedBoCount;

   U32 maxChgdBo;

   U32 spsSchedBo;
   Bool isDynSched;
} RgSchCmnDlUeSpsInfo;





typedef struct rgSchCmnSpsDlSf
{
  U32 rbsAlloc;

  RgSchDlSfAllocInfo spsAllocInfo;
  U32 n1PucchMask[((96 + 31)/32)];

  U8 numDlSpsActiveUes;

} RgSchCmnSpsDlSf;





typedef struct rgSchCmnSpsDlN1Pucch RgSchCmnSpsDlN1Pucch;
struct rgSchCmnSpsDlN1Pucch
{
 U16 idx;
 U16 n1PucchVal;
 U32 numUes;
 U16 next;
};





typedef struct rgSchCmnSpsDlN1PucchDb
{
  U16 numFreeN1Pucch;
  U16 numInUseN1Pucch;

  RgSchCmnSpsDlN1Pucch *freeN1PucchStart;
  RgSchCmnSpsDlN1Pucch *inUseN1PucchStart;

  RgSchCmnSpsDlN1Pucch n1PucchLst[96];


} RgSchCmnSpsDlN1PucchDb;





typedef struct rgSchCmnDlCellSpsInfo
{
  CmLListCp zeroBOSvcUes;


  CmLListCp toBeSchdSvcs;
  CmLListCp retxHqProcs;



  CmLListCp actvDlSpsUeLsts[640];



  CmLListCp toBeActvtdUes;

  CmLListCp toBeRelUes;




  CmLListCp wtngForRelFdbkUeLst[10];




  U16 spsPrdLcmVal;


  U8 lcmIdx;
  RgSchCmnSpsDlSf *spsSfTbl;
  RgSchCmnSpsDlN1PucchDb n1PucchDb;

} RgSchCmnDlCellSpsInfo;





typedef struct rgSchCmnSpsUlAlloc
{
   U8 sbStart;
   U8 numSb;
} RgSchCmnSpsUlAlloc;





typedef struct rgSchCmnSpsUlSf
{
   U32 ulBwBitMask[4];


   U8 maskLen;
   U8 numUlSpsActiveUes;
   RgSchCmnSpsUlAlloc allocInfo;

} RgSchCmnSpsUlSf;





typedef struct rgSchCmnUlCellSpsInfo
{
   U8 spsSbStart;
   U8 numSpsSb;
   U16 spsPrdLcmVal;


   RgSchCmnSpsUlSf *spsSfLst;
   CmLListCp actvUlSpsUeLsts[640];



   CmLListCp toBeActvtdUeLst;

   CmLListCp toBeRelUeLst;

} RgSchCmnUlCellSpsInfo;
typedef struct rgSchCmnUlCellRa
{
   U8 prmblANumSb;
   U8 prmblAIMcs;
   U8 prmblBNumSb;
   U8 prmblBIMcs;
} RgSchCmnUlCellRa;

typedef struct rgSchCmnCellClcITbs
{
   U8 iTbs2Rbs;
   U8 iTbs3Rbs;
}RgSchCmnCellClcITbs;

typedef struct rgSchCmnDlCell
{
   Bool isDlFreqSel;

   U8 maxUeNewTxPerTti;
   U8 numRaSubFrms;
   U8 iTbsCap;
   U16 nCce;
   U8 maxDlBwPerUe;
   U8 maxDlRetxBw;
   U8 maxUePerDlSf;


   U8 maxCcchPerDlSf;
   U8 msg4TxDelay;


   RgSchCmnCellClcITbs cmnChITbs;
   CmLteAggrLvl cmnChAggrLvl;
   U8 ccchCqi;
   CmLListCp msg4RetxLst;


   CmLListCp ccchSduRetxLst;

   Void *cqiToTbsTbl[2][4];


   Void *cqiToEffTbl[2][4];
   U8 newCfi;
   U8 currCfi;

   U16 noResPerRb[4];
   CmLteTimingInfo time;
   Void *schSpfc;
   Void *dlfsCell;
   CmLListCp taLst;


   RgSchCmnDlCellSpsInfo dlSpsInfo;


   U32 bitsPerRb;
   U16 bcchTxPwrOffset;




   U16 pcchTxPwrOffset;




   U16 rarTxPwrOffset;





   U16 phichTxPwrOffset;




   U32 ncsgPrbCnt;
   U32 totPrbCnt;
   RgrUeDlPwrCntrlPaCfg msg4pAVal;






} RgSchCmnDlCell;



typedef struct rgSchCmnTpcRntiCb
{
   CmLteRnti tpcRnti;
   Bool isFmt3a;
   CmLListCp toBeSchdUes;

   CmLListCp cfgdUes;
   CmLList schdLnk;

} RgSchCmnTpcRntiCb;



typedef struct rgSchCmnUlPwrCb
{
   U8 tpcPucchRntiCnt;
   RgSchCmnTpcRntiCb tpcPucchRntiLst[100];

   U8 tpcPuschRntiCnt;
   RgSchCmnTpcRntiCb tpcPuschRntiLst[100];

   CmLListCp pucchGrpPwr;

   CmLListCp puschGrpPwr;

   S8 pMax;
   U8 trgUlCqi;
} RgSchCmnUlPwrCb;





typedef struct rgSchCmnUlCell
{
   U8 maxUeNewTxPerTti;

   U8 maxUlBwPerUe;
   U8 maxSbPerUe;
   U8 dfltUlCqi;
   U8 max16qamCqi;
   U8 maxUlSpsCqi;
   U8 iTbsCap;
   U8 sbSize;
   U8 dmrsArrSize;
   U8 *dmrsArr;
   RgSchCmnUlCellRa ra;
   U8 idx;
   U8 schdIdx;
   U8 schdHqProcIdx;
   U8 msg3SchdIdx;
   U8 msg3SchdHqProcIdx;
   U8 rcpReqIdx;

   U8 hqFdbkIdx[2];


   U8 reTxIdx[2];


   U8 spsUlRsrvIdx;
   U8 spsUlRsrvHqProcIdx;

   CmLteTimingInfo schdTime;




   RgSchUlSf ulSfArr[8 +8];

   Void *schSpfc;
   RgSchCmnUlPwrCb ulPwrCb;
   U8 ulNumRePerRb;

   U8 maxAllocPerUlSf;


   U8 maxMsg3PerUlSf;



   RgSchCmnUlCellSpsInfo ulSpsInfo;
   U16 schdTti;



   U32 ncsgPrbCnt;
   U32 totPrbCnt;
} RgSchCmnUlCell;



typedef struct rgSchCmnAckNakRepCb
{



   CmLListCp ackNakRepQ[10];

} RgSchCmnAckNakRepCb;



typedef struct rgSchCmnMeasGapCb
{
   CmLListCp gapPrd40Q[40];

   CmLListCp gapPrd80Q[80];

} RgSchCmnMeasGapCb;




typedef struct rgSchCmnRapIdMap
{
   U8 rapId;
   CmLListCp assgndUes;

} RgSchCmnRapIdMap;




typedef struct rgSchCmnRachCfg
{
   U8 numDedPrm;
   U8 dedPrmStart;
   U8 remDedPrm;

   CmLteTimingInfo applFrm;

   U8 prachMskIndx;

   RgSchCmnRapIdMap rapIdMap[60];

   CmLListCp hoUeLst;
   CmLListCp pdcchOdrLst;

} RgSchCmnRachCfg;



typedef struct rgSchCmnUeUlPwrCb
{
   Bool isAccumulated;
   Bool deltaMcsEnbld;

   U8 pucchIdx;
   U8 puschIdx;
   U8 isPhrAvail;
   S8 phVal;
   S8 pwrPerRb;
   S8 maxUePwr;
   U8 maxUlRbs;
   S8 delta;
   U8 numRb;
   S8 remPuschPwr;

   S8 remPucchPwr;
   U8 pucchTpc;
   U8 puschTpc;
   U8 trgCqi;
   RgSchCmnTpcRntiCb *tpcPucchRntiCb;
   CmLList pucchGrpLnk;

   CmLList schdPucchGrpLnk;

   RgSchCmnTpcRntiCb *tpcPuschRntiCb;
   CmLList puschGrpLnk;

   CmLList schdPuschGrpLnk;

   S8 p0UePusch;
   S8 p0UePucch;
   S8 maxPwrPerRb;
   S8 maxPwrDeltaByPhr;
} RgSchCmnUeUlPwrCb;



struct rgSchCmnUeUlAlloc
{

   U32 reqBytes;


   U32 allocdBytes;
   RgSchUlAlloc *alloc;
   CmLList reqLnk;
   CmLList schdLstLnk;
};

typedef struct rgSchCmnAllocRecord
{
   U32 alloc;
   CmLteTimingInfo allocTime;
   CmLList lnk;
   U8 numRb;
   U8 cqi;
   U8 tpc;
}RgSchCmnAllocRecord;







typedef struct ueUlLaCb
{
   S32 deltaiTbs;
   U32 iTbsUpperCap;
   S32 cqiBasediTbs;
   Bool lastiTbsIgnored;
} UeUlLaCb;






typedef struct rgSchCmnUlUe
{
   U8 maxUlCqi;
   U8 crntUlCqi[2];


   U8 validUlCqi;

   U8 lastCfi;
   CmLListCp ulAllocLst;



   Void *schSpfc;
   RgSchCmnUeUlPwrCb ulPwrCb;
   RgSchCmnUeUlAlloc alloc;

   U32 schedOccns;
   U32 schedRetxOccns;
   U32 avgCqi;
   U32 numCqiOccns;
   U32 prbAlloc;


   UeUlLaCb ulLaCb;

   RgUeUlHqCb hqEnt;
   U8 subbandShare;

   U32 subbandRequired;

   CmLList ulSchedLnk;

} RgSchCmnUlUe;



typedef struct rgSchCmnMsg4RbAlloc
{
   RgSchDlSf *msg4DlSf;

   CmLListCp msg4TxLst;
   CmLListCp msg4RetxLst;
   CmLListCp schdMsg4TxLst;
   CmLListCp schdMsg4RetxLst;
   CmLListCp nonSchdMsg4TxLst;
   CmLListCp nonSchdMsg4RetxLst;

} RgSchCmnMsg4RbAlloc;


typedef struct rgSchCmnCcchSduRbAlloc
{
   RgSchDlSf *ccchSduDlSf;

   CmLListCp ccchSduTxLst;
   CmLListCp ccchSduRetxLst;
   CmLListCp schdCcchSduTxLst;
   CmLListCp schdCcchSduRetxLst;
   CmLListCp nonSchdCcchSduTxLst;
   CmLListCp nonSchdCcchSduRetxLst;

} RgSchCmnCcchSduRbAlloc;




typedef struct rgSchCmnUeRbAlloc
{
   RgSchDlSf *dedDlSf;


   CmLListCp txHqPLst;

   CmLListCp retxHqPLst;

   CmLListCp errIndTxHqPLst;

   CmLListCp retxSpsHqPLst;

   CmLListCp txSpsHqPLst;


   CmLListCp txLaaHqPLst;

   CmLListCp schdTxHqPLst;
   CmLListCp schdRetxHqPLst;
   CmLListCp nonSchdTxHqPLst;
   CmLListCp nonSchdRetxHqPLst;


   CmLListCp txRetxHqPLst;

   CmLListCp schdTxRetxHqPLst;
   CmLListCp nonSchdTxRetxHqPLst;

   CmLListCp schdRetxSpsHqPLst;
   CmLListCp nonSchdRetxSpsHqPLst;

   CmLListCp schdTxSpsHqPLst;
   CmLListCp nonSchdTxSpsHqPLst;

   CmLListCp schdTxLaaHqPLst;
   CmLListCp nonSchdTxLaaHqPLst;
   CmLListCp schdErrIndTxHqPLst;
   CmLListCp nonSchdErrIndTxHqPLst;
} RgSchCmnUeRbAlloc;



struct rgSchCmnDlRbAllocInfo
{
   RgSchDlRbAlloc pcchAlloc;
   RgSchDlRbAlloc bcchAlloc;
   RgSchDlRbAlloc raRspAlloc[4];
   RgSchCmnMsg4RbAlloc msg4Alloc;


   RgSchCmnCcchSduRbAlloc ccchSduAlloc;

   RgSchCmnUeRbAlloc dedAlloc;
};





typedef struct rgSchCmnCell
{
   RgrCfiCfg cfiCfg;
   RgrUlTrgCqiCfg trgUlCqi;
   CmTqCp tmrTqCp;

   CmTqType tmrTq[16];
   RgrDlCmnCodeRateCfg dlCmnCodeRate;

   RgrPuschSubBandCfg puschSubBand;
   RgrUlCmnCodeRateCfg ulCmnCodeRate;

   RgSchCmnRachCfg rachCfg;
   RgSchCmnUlCell ul;
   RgSchCmnDlCell dl;
   RgUlSchdApis *apisUl;
   RgDlSchdApis *apisDl;
   RgDlfsSchdApis *apisDlfs;
   CmLteAggrLvl dciAggrLvl[16][10];


   RgSchCmnDlRbAllocInfo allocInfo;
}RgSchCmnCell;






typedef struct rgSchCmnDlUeRachInfo
{
   CmLList inActUeLnk;
   CmLList poLnk;
   CmLList hoLnk;
   CmLList rapIdLnk;
   CmLteTimingInfo asgnOppr;
   U8 hoRapId;
   U8 poRapId;
}RgSchCmnDlUeRachInfo;






typedef struct rgSchCmnDlUeCwInfo
{
   U8 cqi;
   U8 iTbs[2];



   U32 eff[2];



   U8 noLyr;

   U16 dtxCnt;
   U16 ackCnt;
   U16 nackCnt;
}RgSchCmnDlUeCwInfo;



typedef struct rgSchCmnUeMimoInfo
{
   RgSchCmnDlUeCwInfo cwInfo[2];
   U8 ri;
   U8 pmi;
   U8 btrCwIdx;
   U8 forceTD;

}RgSchCmnUeMimoInfo;

typedef struct ueLaCb {
   S32 deltaiTbs;
   U32 iTbsUpperCap;
   S32 cqiBasediTbs;
   Bool lastiTbsIgnored;
   U8 notFirstCqi;
   U8 numLastiTbsIgnored;
} UeLaCb;





typedef struct rgSchCmnDlUe
{
   U32 maxSbSz;
   U32 maxTbSz;
   U8 maxRb;
   U32 maxTbBits;
   RgSchCmnUeMimoInfo mimoInfo;
   RgSchDlHqProcCb *proc;
   Void *schSpfc;
   Void *dlfsUe;
   U32 outStndAlloc;

   RgSchCmnDlUeRachInfo rachInfo;

   RgSchCmnDlUeSpsInfo dlSpsInfo;


   U32 schedOccns;
   U32 currPdbLvl;
   U32 prevOccnLvlUpd;




   U32 schedRetxOccns;
   U32 avgCqi;
   U32 numCqiOccns;
   U32 numRi1;
   U32 numRi2;
   U32 boReported;
   U32 prbAlloc;
   U32 remAmbrForStats;

   UeLaCb laCb[2];
   U8 cqiFlag;
   U8 lastCfi;

} RgSchCmnDlUe;



struct rgSchCmnUlRbAllocInfo
{
   RgSchUlSf *sf;
   CmLListCp contResLst;
   CmLListCp schdContResLst;
   CmLListCp nonSchdContResLst;
   CmLListCp ueLst;
   CmLListCp schdUeLst;
   CmLListCp nonSchdUeLst;
};





typedef struct rgSchCmnUeInfo
{
   U8 ueCat;
   CmTimer tmr;
} RgSchCmnUeInfo;




typedef struct rgSchCmnUe
{
  RgSchCmnUeInfo cmn;

  RgSchCmnUlUe ul;
  RgSchCmnDlUe dl;
} RgSchCmnUe;

typedef struct rgSchCmnLcg
{
   U32 bs;
   U32 cfgdGbr;
   U32 effGbr;
   U32 deltaMbr;
   U32 effDeltaMbr;
   U32 reportedBs;
   Void *schSpfc;
}RgSchCmnLcg;






typedef struct rgSchCmnDlSvcSpsInfo
{
   CmLList toBeSchdSvcEnt;
   U16 zeroBoOcassionCnt;

   U32 effSpsBo;
   U32 bytesReq;
   U8 hdrEst;

} RgSchCmnDlSvcSpsInfo;


typedef struct rgSchCmnDlSvc {
   U8 qci;
   U8 prio;
   U32 gbr;
   U32 mbr;
   Void *schSpfc[8];

   RgSchCmnDlSvcSpsInfo dlSvcSpsInfo;


}RgSchCmnDlSvc;

typedef struct rgSchCmnDlHqProc {
   CmLList retxLnk;
   U32 totBytes;

   Bool isSpsSvcSchd;


   Bool isSpsActv;


   U8 spsAction;

   CmLteTimingInfo maxRetxTime;


   Void *schSpfc;
}RgSchCmnDlHqProc;






typedef U8 RgSchCmnCqiToTbs[16];



typedef U32 RgSchCmnTbSzEff[27];



extern RgSchCmnTbSzEff rgSchCmnNorCfi1Eff[2], rgSchCmnNorCfi2Eff[2];
extern RgSchCmnTbSzEff rgSchCmnNorCfi3Eff[2], rgSchCmnNorCfi4Eff[2];

extern RgSchCmnTbSzEff rgSchCmnNorUlEff[1],rgSchCmnExtUlEff[1];
extern RgSchCmnCqiToTbs rgSchCmnNorCfi1CqiToTbs[2], rgSchCmnNorCfi2CqiToTbs[2];
extern RgSchCmnCqiToTbs rgSchCmnNorCfi3CqiToTbs[2], rgSchCmnNorCfi4CqiToTbs[2];
extern RgSchCmnCqiToTbs *rgSchCmnCqiToTbs[2][2][4];
extern RgSchCmnTbSzEff rgSchCmnExtCfi1Eff[2], rgSchCmnExtCfi2Eff[2];
extern RgSchCmnTbSzEff rgSchCmnExtCfi3Eff[2], rgSchCmnExtCfi4Eff[2];
extern RgSchCmnCqiToTbs rgSchCmnExtCfi1CqiToTbs[2], rgSchCmnExtCfi2CqiToTbs[2];
extern RgSchCmnCqiToTbs rgSchCmnExtCfi3CqiToTbs[2], rgSchCmnExtCfi4CqiToTbs[2];

extern RgSchCmnTbSzEff
*rgSchCmnEffTbl[2][2][3][4];

extern RgSchCmnTbSzEff *rgSchCmnUlEffTbl[2];

extern RgSchTbSzTbl rgTbSzTbl;

extern Void rgSCHCmnInit (Void )
  ;
extern S16 rgSCHCmnRgrCellCfg ( RgSchCellCb *cell, RgrCellCfg *cellCfg, RgSchErrInfo *err )



  ;
extern S16 rgSCHCmnRgrCellRecfg ( RgSchCellCb *cell, RgrCellRecfg *recfg, RgSchErrInfo *err )



  ;
extern Void rgSCHCmnFreeDlLc ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *svc )



  ;
extern Void rgSCHCmnCellDel ( RgSchCellCb *cell )

  ;
extern Void rgSCHCmnDlRlsSubFrm ( RgSchCellCb *cell, CmLteTimingInfo frm )


  ;
extern S16 rgSCHCmnRgrUeCfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *ueCfg, RgSchErrInfo *err )




  ;
extern S16 rgSCHCmnRgrUeRecfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *ueRecfg, RgSchErrInfo *err )




  ;
extern Void rgSCHCmnUeDel ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern Void rgSCHCmnUeReset ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern S16 rgSCHCmnRgrLcgRecfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg, RgrLcgRecfg *reCfg, RgSchErrInfo *err )





  ;
extern S16 rgSCHCmnRgrLcgCfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg, RgrLcgCfg *lcgCfg, RgSchErrInfo *err )





  ;
extern S16 rgSCHCmnRgrLchCfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc, RgrLchCfg *lcCfg, RgSchErrInfo *err )





  ;
extern S16 rgSCHCmnRgrLchDel ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteLcId lcId, U8 lcgId )




  ;
extern S16 rgSCHCmnRgrLchRecfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc, RgrLchRecfg *lcRecfg, RgSchErrInfo *err )





  ;
extern Void rgSCHCmnLcgDel ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg )



  ;
extern S16 rgSCHCmnUpdBsrShort ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *ulLcg, U8 bsr, RgSchErrInfo *err )





  ;
extern S16 rgSCHCmnUpdBsrTrunc ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *ulLcg, U8 bsr, RgSchErrInfo *err )





  ;
extern S16 rgSCHCmnUpdBsrLong ( RgSchCellCb *cell, RgSchUeCb *ue, U8 bsArr[], RgSchErrInfo *err )




  ;
extern S16 rgSCHCmnDataRcvd ( RgSchCellCb *cell, RgSchUeCb *ue, U8 numLc, RgSchUlLcCb *lcArr[], U16 bytesArr[], RgSchErrInfo *err )






  ;
extern Void rgSCHCmnUlCqiInd ( RgSchCellCb *cell, RgSchUeCb *ue, TfuUlCqiRpt *ulCqiInfo )



  ;
extern S16 rgSCHCmnUpdExtPhr ( RgSchCellCb *cell, RgSchUeCb *ue, RgInfExtPhrCEInfo *extPhr, RgSchErrInfo *err )




  ;
extern S16 rgSCHCmnUpdPhr ( RgSchCellCb *cell, RgSchUeCb *ue, U8 phr, RgSchErrInfo *err )




  ;
extern S16 rgSCHCmnUpdUlHqProc ( RgSchCellCb *cell, RgSchUlHqProcCb *curProc, RgSchUlHqProcCb *oldProc )



  ;
extern S16 rgSCHCmnContResUlGrant ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchErrInfo *err )



  ;
extern Void rgSCHCmnActvtUlUe ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern Void rgSCHCmnActvtDlUe ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern Void rgSCHCmnHdlUlTransInd ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo timingInfo )



  ;
extern S16 rgSCHCmnSrRcvd ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo frm, RgSchErrInfo *err )




  ;
extern Void rgSCHCmnUlRbAllocAddUeToLst ( RgSchCellCb *cell, RgSchUeCb *ue, CmLListCp *lst )



  ;
extern S16 rgSCHCmnTti ( RgSchCellCb *cell, RgSchErrInfo *err )


  ;
extern Void rgSCHCmnUlHqProcForUe ( RgSchCellCb *cell, CmLteTimingInfo frm, RgSchUeCb *ue, RgSchUlHqProcCb **procRef )




  ;
extern RgSchUlAlloc *rgSCHCmnFirstRcptnReq ( RgSchCellCb *cell )

  ;
extern RgSchUlAlloc *rgSCHCmnNextRcptnReq ( RgSchCellCb *cell, RgSchUlAlloc *alloc )


  ;
extern RgSchUlAlloc *rgSCHCmnFirstHqFdbkAlloc ( RgSchCellCb *cell, U8 idx )


  ;
extern RgSchUlAlloc *rgSCHCmnNextHqFdbkAlloc ( RgSchCellCb *cell, RgSchUlAlloc *alloc, U8 idx )



  ;
extern Void rgSCHCmnDlDedBoUpd ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *svc )



  ;




extern Void rgSCHCmnDlMsg4ProcRmvFrmRetx ( RgSchCellCb *cell, RgSchDlHqProcCb *hqP )


  ;
extern Void rgSCHCmnDlProcAddToRetx ( RgSchCellCb *cell, RgSchDlHqProcCb *hqP )


  ;
extern Void rgSCHCmnDlCqiInd ( RgSchCellCb *cell, RgSchUeCb *ue, Bool isPucchInfo, Void *dlCqi, CmLteTimingInfo timingInfo )





  ;


extern Void rgSCHCmnRawCqiInd ( RgSchCellCb *cellCb, RgSchUeCb *ueCb, TfuRawCqiRpt *rawCqiRpt, CmLteTimingInfo timingInfo )





  ;

extern Void rgSCHCmnSrsInd ( RgSchCellCb *cellCb, RgSchUeCb *ueCb, TfuSrsRpt *srsRpt, CmLteTimingInfo timingInfo )





  ;


extern Void rgSCHCmnDlTARpt ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern RgSchPdcch *rgSCHCmnCmnPdcchAlloc ( RgSchCellCb *cell, RgSchDlSf *subFrm )


  ;
extern RgSchUlAlloc *rgSCHCmnUlSbAlloc ( RgSchUlSf *sf, U8 numSb, RgSchUlHole *hole )



  ;
extern Void rgSCHCmnRlsUlSf ( RgSchCellCb *cell, U8 idx )


  ;


extern Void rgSCHCmnUlRecMsg3Alloc ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchRaCb *raCb )



  ;




 Void rgSCHCmnUpdVars ( RgSchCellCb *cell )

  ;


extern Void rgSCHCmnFillHqPTb ( RgSchCellCb *cell, RgSchDlRbAlloc *rbAllocInfo, U8 tbAllocIdx, RgSchPdcch *pdcch )




  ;

extern Void rgSCHCmnDlProcAck ( RgSchCellCb *cell, RgSchDlHqProcCb *hqP )


  ;
extern Void rgSCHCmnHdlCrntiCE ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern Void rgSCHCmnDlRelPdcchFbk ( RgSchCellCb *cell, RgSchUeCb *ue, Bool isAck )



  ;
extern Void rgSCHCmnDlGetRbgInfo ( U8 dlTotalBw, U8 dlSubsetBw, U8 maxRaType1SubsetBw, U8 rbgSize, RgSchBwRbgInfo *rbgInfo )





  ;
extern U8 rgSCHCmnDlRaType0Alloc ( RgSchDlSfAllocInfo *allocedInfo, U8 rbsReq, RgSchBwRbgInfo *rbgInfo, U8 *numAllocRbs, RgSchDlSfAllocInfo *resAllocInfo, Bool isPartialAlloc )






  ;
extern U8 rgSCHCmnDlRaType2Alloc ( RgSchDlSfAllocInfo *allocedInfo, U8 rbsReq, RgSchBwRbgInfo *rbgInfo, U8 *rbStart, RgSchDlSfAllocInfo *resAllocInfo, Bool isPartialAlloc )






  ;
extern Bool rgSCHCmnAllocUeInSpsBw ( RgSchDlSf *dlSf, RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlRbAlloc *rbAllocInfo, Bool isPartialAlloc )





  ;

extern Void rgSCHCmnDrxStrtInActvTmrInUl (RgSchCellCb *cell);
extern Void rgSCHCmnUpdUeDataIndLcg (RgSchCellCb *cell, RgSchUeCb *ue, RgInfUeDatInd *datInd);





extern U8 rgSCHCmnGetUlHqProcIdx (CmLteTimingInfo *timeInfo, RgSchCellCb *cell);

extern Void rgSchCmnSetCqiReqField ( RgSchUeCellInfo *cellInfo, RgSchUeCb *ue, RgSchCqiReqField *cqiReq )



  ;




extern Void rgSCHCmnUlFreeAlloc ( RgSchCellCb *cell, RgSchUlAlloc *alloc )


  ;

extern Void rgSCHCmnUlFreeAllocation ( RgSchCellCb *cell, RgSchUlSf *sf, RgSchUlAlloc *alloc )



  ;

extern S16 rgSCHCmnAllocDlRb ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *dlRbAllocInfo )


  ;


extern Void rgSCHCmnAllocUlRb ( RgSchCellCb *cell, RgSchCmnUlRbAllocInfo *ulRbAllocInfo )


  ;


extern RgSchPdcch *rgSCHCmnPdcchAllocCrntSf ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern Void rgSCHCmnPdcchRlsCrntSf ( RgSchCellCb *cell, RgSchPdcch *pdcch )


  ;
extern Void rgSCHCmnUlFillPdcchWithAlloc ( RgSchPdcch *pdcch, RgSchUlAlloc *alloc, RgSchUeCb *ue )



  ;
extern Void rgSCHCmnUlAllocFillTpc ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchUlAlloc *alloc )



  ;
extern Void rgSCHCmnUlAllocFillNdmrs ( RgSchCmnUlCell *cellUl, RgSchUlAlloc *alloc )


  ;
extern Void rgSCHCmnUlAllocLnkHqProc ( RgSchUeCb *ue, RgSchUlAlloc *alloc, RgSchUlHqProcCb *proc, Bool isReTx )




  ;
extern RgSchPdcch *rgSCHCmnPdcchAlloc ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlSf *subFrm, U32 y, U8 cqi, TfuDciFormat dciFrmt, Bool isDtx )







  ;
extern Void rgSCHCmnRdcImcsTxTb ( RgSchDlRbAlloc *allocInfo, U8 tbInfoIdx, U32 cnsmdBytes )



  ;
extern Void rgSCHCmnFillPdcch ( RgSchCellCb *cell, RgSchPdcch *pdcch, RgSchDlRbAlloc *rbAllocInfo )



  ;
extern U8 rgSCHCmnUpdDai ( RgSchUeCb *ue, CmLteTimingInfo *fdbkTime, U8 m, Bool havePdcch, RgSchDlHqProcCb *hqP, U8 *ulDai )







  ;
extern Void rgSCHCmnFillHqPPdcch ( RgSchCellCb *cell, RgSchDlRbAlloc *rbAllocInfo, RgSchDlHqProcCb *hqP )



  ;
extern S16 rgSCHCmnDlChkResAvl ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, RgSchDlHqProcCb *proc, U32 *bo, U8 *iTbs, U32 *maxRb )







  ;
extern S16 rgSCHCmnDlDedAlloc ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, RgSchDlHqProcCb *proc, U32 bo, U8 iTbs, U32 maxRb, U32 *bytes )
  ;
extern Void rgSCHCmnUlUeFillAllocInfo ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;

extern U8 rgSCHCmnUlGetITbsFrmIMcs ( U8 iMcs )

  ;

extern U8 rgSCHCmnUlGetIMcsFrmITbs ( U8 iTbs, CmLteUeCategory ueCtg )


  ;
extern U32 rgSCHCmnUlMinTbBitsForITbs ( RgSchCmnUlCell *cellUl, U8 iTbs )


  ;
extern U8 rgSCHCmnUlGetITbs ( RgSchCellCb *cell, RgSchUeCb *ue, Bool isEcp )



  ;
extern Void rgSCHCmnUlAllocFillRbInfo ( RgSchCellCb *cell, RgSchUlSf *sf, RgSchUlAlloc *alloc )



  ;
extern Void rgSCHCmnDlUeResetTemp ( RgSchUeCb *ue, RgSchDlHqProcCb *hqP )


  ;
extern Void rgSCHCmnUlUeResetTemp ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;


extern S16 rgSCHCmnDlAllocTxRb ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
extern Bool rgSCHCmnIsDlCsgPrio ( RgSchCellCb *cell )

  ;
extern Bool rgSCHCmnIsUlCsgPrio ( RgSchCellCb *cell )

  ;
extern S16 rgSCHCmnDlAllocRetxRb ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;

extern Void rgSCHCmnClcRbAlloc ( RgSchCellCb *cell, U32 bo, U8 cqi, U8 *rb, U32 *tbs, U8 *mcs, U8 *iTbs, Bool isSpsBo, RgSchDlSf *sf )
  ;
 U32 rgSCHCmnCalcRiv ( U8 bw, U8 rbStart, U8 numRb )



  ;




extern Void rgSCHCmnUlAdd2UeLst ( RgSchCellCb *cell, RgSchCmnUlRbAllocInfo *allocInfo, RgSchUeCb *ue )



  ;
extern Void rgSCHCmnUlAdd2CntResLst ( RgSchCmnUlRbAllocInfo *allocInfo, RgSchUeCb *ue )


  ;
extern Void rgSCHCmnRmvFrmTaLst ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;

extern Void rgSCHCmnUlUpdOutStndAlloc ( RgSchCellCb *cell, RgSchUeCb *ue, U32 alloc )



  ;

extern Void rgSCHCmnUlRecordUeAlloc ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;




extern Void rgSCHPwrInit ( Void)
               ;
extern U8 rgSCHPwrPuschTpcForUe ( RgSchCellCb *cell, RgSchUeCb *ue)

                          ;
extern U8 rgSCHPwrGetMaxUlRb ( RgSchCellCb *cell, RgSchUeCb *ue)

                          ;
extern U8 rgSCHPwrPucchTpcForUe ( RgSchCellCb *cell, RgSchUeCb *ue)

                          ;
extern Void rgSCHPwrGrpCntrlPucch ( RgSchCellCb *cell, RgSchDlSf *dlSf)

                            ;
extern Void rgSCHPwrGrpCntrlPusch ( RgSchCellCb *cell, RgSchDlSf *dlSf, RgSchUlSf *ulSf)


                            ;
extern Void rgSCHPwrPucchDeltaInd ( RgSchCellCb *cell, RgSchUeCb *ue, S8 pwrDelta)


                               ;
extern Void rgSCHPwrUpdExtPhr ( RgSchCellCb *cell, RgSchUeCb *ue, RgInfExtPhrCEInfo *extPhr, RgSchCmnAllocRecord *allocInfo)



                                           ;
extern Void rgSCHPwrUpdPhr ( RgSchCellCb *cell, RgSchUeCb *ue, U8 phr, RgSchCmnAllocRecord *allocInfo, S8 maxUePwr)




                                          ;
extern Void rgSCHPwrUlCqiInd ( RgSchCellCb *cell, RgSchUeCb *ue )


           ;
extern Void rgSCHPwrRecordRbAlloc ( RgSchCellCb *cell, RgSchUeCb *ue, U8 numRb )



           ;
extern S16 rgSCHPwrCellCfg ( RgSchCellCb *cell, RgrCellCfg *cfg)

                                    ;
extern S16 rgSCHPwrCellRecfg ( RgSchCellCb *cell, RgrCellRecfg *recfg)

                                      ;
extern Void rgSCHPwrCellDel ( RgSchCellCb *cell)
                            ;
extern S16 rgSCHPwrUeCfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *cfg)


                           ;
extern S16 rgSCHPwrUeRecfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *recfg)


                               ;
extern Void rgSCHPwrUeDel ( RgSchCellCb *cell, RgSchUeCb *ue)

                            ;
extern Void rgSCHPwrUeReset ( RgSchCellCb *cell, RgSchUeCb *ue)

                            ;


extern S16 rgSCHCmnSpsUlProcCrcInd ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo crcTime )



  ;
extern Void rgSCHCmnSpsInit (Void);

extern Void rgSCHCmnSpsRelDlSpsActHqP ( RgSchCellCb *cell, RgSchDlHqProcCb *hqP)

                         ;

extern S16 rgSCHCmnSpsCellCfg ( RgSchCellCb *cell, RgrCellCfg *cellCfg, RgSchErrInfo *err)


                         ;
extern Void rgSCHCmnSpsCellDel ( RgSchCellCb *cell )

  ;
extern S16 rgSCHCmnSpsUeCfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCfg *ueCfg, RgSchErrInfo *err )




  ;
extern S16 rgSCHCmnSpsUeRecfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *ueRecfg, RgSchErrInfo *err )




  ;
extern Void rgSCHCmnSpsUeDel ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern S16 rgSCHCmnSpsDlLcRecfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc, RgrLchRecfg *lcRecfg, RgSchErrInfo *err )





  ;
extern S16 rgSCHCmnSpsDlLcCfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc, RgrLchCfg *lcCfg, RgSchErrInfo *err )





  ;
extern Void rgSCHCmnSpsDlLcDel ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc )



  ;
extern Void rgSCHCmnSpsDlCqiIndHndlr ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo timingInfo )



  ;
extern Void rgSCHCmnSpsDlDedBoUpd ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlLcCb *dlLc )



  ;
extern Void rgSCHCmnSpsDlUeReset ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern Void rgSCHCmnSpsDlProcAddToRetx ( RgSchCellCb *cell, RgSchDlHqProcCb *hqP )


  ;
extern Void rgSCHCmnSpsDlProcAck ( RgSchCellCb *cell, RgSchDlHqProcCb *hqP )


  ;

extern Void rgSCHCmnSpsDlRelPdcchFbk ( RgSchCellCb *cell, RgSchUeCb *ue, Bool isAck )



  ;
extern Void rgSCHCmnSpsDlSched ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;







extern Void rgSCHCmnSpsDlAllocFnlz ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;

extern Void rgSCHCmnSpsDlUpdDlSfAllocWithSps ( RgSchCellCb *cell, CmLteTimingInfo schdTime, RgSchDlSf *dlSf )



  ;



extern Void rgSCHCmnSpsUlLcgDel ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *lcg )



  ;
extern Void rgSCHCmnSpsUlUeReset ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern Void rgSCHCmnSpsUlProcRelInd ( RgSchCellCb *cell, RgSchUeCb *ue, Bool isExplRel )



  ;

extern Void rgSCHCmnSpsUlProcActInd ( RgSchCellCb *cell, RgSchUeCb *ue, U16 spsSduSize )



  ;
extern Void rgSCHCmnSpsPhrInd ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;


extern S16 rgSCHCmnSpsBsrRpt ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchLcgCb *ulLcg )



  ;


extern S16 rgSCHCmnSpsUlCqiInd ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
extern S16 rgSCHCmnSpsUlProcDtxInd ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo dtxTime )



  ;
extern S16 rgSCHCmnSpsUlTti ( RgSchCellCb *cell, RgSchCmnUlRbAllocInfo *allocInfo )


  ;







extern Void rgSCHCmnUlSpsRelInd ( RgSchCellCb *cell, RgSchUeCb *ue, Bool isExplRel )



  ;


extern Void rgSCHCmnUlSpsActInd ( RgSchCellCb *cell, RgSchUeCb *ue, U16 spsSduSize )



  ;

extern Void rgSCHCmnUlCrcFailInd ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo crcTime )



  ;
extern Void rgSCHCmnUlCrcInd ( RgSchCellCb *cell, RgSchUeCb *ue, CmLteTimingInfo crcTime )



  ;



extern Void rgSCHCmnSpsDlReTxRelPdcch ( RgSchCellCb *cell )

  ;


extern Void rgSCHCmnChkRetxAllowDtx
( RgSchCellCb *cell, RgSchUeCb *ueCb, RgSchDlHqProcCb *proc, Bool *reTxAllwd )




  ;

extern S16 PtUiRgmBndCfm (Pst* pst, SuId suId, U8 status);

extern S16 rgSCHCmnDlInitHqEnt
( RgSchCellCb *cell, RgSchDlHqEnt *hqEnt )


  ;

extern Void rgSchCmnDlSfHqDel
( RgSchUeCb *ue, RgSchCellCb *cell )


  ;

extern Void rgSCHCmnDlDeInitHqEnt
( RgSchCellCb *cell, RgSchDlHqEnt *hqE )


  ;
extern U8 rgSCHCmnUlGetCqi
( RgSchCellCb *cell, RgSchUeCb *ue, CmLteUeCategory ueCtgy )



  ;

extern S16 rgSCHDhmUpdBlerBasediTbsEff ( RgSchCellCb *cell, RgSchUeCb *ueCb, U8 tbCnt )



           ;


extern Void rgSchCmnUpdCfiDb ( RgSchCellCb *cell, U8 delta )


           ;
extern S16 RgUiRgmChangeTransModeInd ( Pst *pst, SuId suId, RgmTransModeInd *transModeInd)


                                          ;

extern Void rgSchCheckAndTriggerModeChange ( RgSchCellCb *cell, RgSchUeCb *ue, U8 reportediTbs, U8 previTbs, U8 maxiTbs )





  ;
extern Void rgSCHRrDlProcRmvFrmRetx ( RgSchCellCb *cell, RgSchDlHqProcCb *hqP )


  ;
extern U8 rgSchUtlGetServCellIdx ( Inst inst, U16 cellId, RgSchUeCb *ue )



           ;
extern S16 rgSchUtlVldtCellId ( Inst inst, U16 cellId )


  ;
extern Void rgSCHCmnLaaTxAllocFnlz ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;

extern Void rgSCHLaaErrIndDlAllocFnlz ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;

extern Void rgSCHLaaDlAllocFnlz ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;

extern S16 rgSCHCmnDlAllocErrIndTxRb ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
extern Void rgSCHSc1UlInit (RgUlSchdApis *apis);

extern Void rgSCHRrUlInit (RgUlSchdApis *apis);
extern Void rgSCHMaxciUlInit (RgUlSchdApis *apis);
extern Void rgSCHPfsUlInit (RgUlSchdApis *apis);

extern Void rgSCHSc1DlInit (RgDlSchdApis *apis);

extern Void rgSCHRrDlInit (RgDlSchdApis *apis);
extern Void rgSCHMaxciDlInit (RgDlSchdApis *apis);
extern Void rgSCHPfsDlInit (RgDlSchdApis *apis);

extern Void rgSCHDlfsInit (RgDlfsSchdApis *apis);




static Void rgSCHDlSiSched (RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo, RgInfSfAlloc *subfrmAlloc)

                                                  ;
static Void rgSCHChkNUpdSiCfg (RgSchCellCb *cell);
static Void rgSCHSelectSi (RgSchCellCb *cell);



static S16 rgSCHCmnNonDlfsUpdDSFRTyp2Alloc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlSf *dlSf,
U8 rbStrt,
U8 numRb
);
static S16 rgSCHCmnBuildRntpInfo (
RgSchCellCb *cell,
U8 *rntpPtr,
U8 startRb,
U8 nmbRb,
U16 bw
);


 Void rgSCHCmnDlSpsSch
(
 RgSchCellCb *cell
);


static Void rgSCHCmnNonDlfsBcchPcchRbAlloc ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static Void rgSCHBcchPcchDlRbAlloc ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static Void rgSCHCmnDlBcchPcchAlloc ( RgSchCellCb *cell )

  ;

static Void rgSCHCmnDlCqiOnPucchInd ( RgSchCellCb *cell, RgSchUeCb *ue, TfuDlCqiPucch *pucchCqi, RgrUeCqiRept *ueCqiRept, Bool *isCqiAvail, Bool *is2ndCwCqiAvail )






   ;
static Void rgSCHCmnDlCqiOnPuschInd ( RgSchCellCb *cell, RgSchUeCb *ue, TfuDlCqiPusch *puschCqi, RgrUeCqiRept *ueCqiRept, Bool *isCqiAvail, Bool *is2ndCwCqiAvail )






   ;
static S16 rgSCHCmnUeDlPwrCtColltCqiRept ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeCqiRept *ueCqiRept)


                                   ;


static Void rgSCHCmnGetRefreshPer ( RgSchCellCb *cell, RgSchUeCb *ue, U32 *waitPer)


                          ;
static S16 rgSCHCmnApplyUeRefresh ( RgSchCellCb *cell, RgSchUeCb *ue)

                     ;

static Void rgSCHCmnDlSetUeAllocLmtLa ( RgSchCellCb *cell, RgSchUeCb *ue )



  ;
static Void rgSCHCheckAndSetTxScheme ( RgSchCellCb *cell, RgSchUeCb *ue )



  ;
static Void rgSCHCmnNonDlfsType0Alloc
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
RgSchDlRbAlloc *allocInfo,
RgSchUeCb *ue
);
static Void rgSCHCmnInitRbAlloc ( RgSchCellCb *cell )


  ;






 RgSchdApis rgSchCmnApis;
static RgUlSchdApis rgSchUlSchdTbl[4];
static RgDlSchdApis rgSchDlSchdTbl[4];

static RgDlfsSchdApis rgSchDlfsSchdTbl[1];

static RgUlSchdInits rgSchUlSchdInits = {rgSCHSc1UlInit, rgSCHPfsUlInit, rgSCHRrUlInit, rgSCHMaxciUlInit};
static RgDlSchdInits rgSchDlSchdInits = {rgSCHSc1DlInit, rgSCHPfsDlInit, rgSCHRrDlInit, rgSCHMaxciDlInit};

static RgDlfsSchdInits rgSchDlfsSchdInits = {rgSCHDlfsInit};


typedef Void (*RgSchCmnDlAllocRbFunc) (RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo)

                                        ;
typedef U8 (*RgSchCmnDlGetPrecInfFunc) (RgSchCellCb *cell, RgSchUeCb *ue, U8 numLyrs, Bool bothCwEnbld)
                                    ;

static Void rgSCHCmnFillHqPPdcchDciFrmt1 ( RgSchCellCb *cell, RgSchDlRbAlloc *rbAllocInfo, RgSchDlHqProcCb *hqP, RgSchPdcch *pdcch, U8 tpc )





  ;
static Void rgSCHCmnFillHqPPdcchDciFrmt1A ( RgSchCellCb *cell, RgSchDlRbAlloc *rbAllocInfo, RgSchDlHqProcCb *hqP, RgSchPdcch *pdcch, U8 tpc )





  ;
static Void rgSCHCmnFillHqPPdcchDciFrmt1B ( RgSchCellCb *cell, RgSchDlRbAlloc *rbAllocInfo, RgSchDlHqProcCb *hqP, RgSchPdcch *pdcch, U8 tpc )





  ;
static Void rgSCHCmnFillHqPPdcchDciFrmt2 ( RgSchCellCb *cell, RgSchDlRbAlloc *rbAllocInfo, RgSchDlHqProcCb *hqP, RgSchPdcch *pdcch, U8 tpc )





  ;
static Void rgSCHCmnFillHqPPdcchDciFrmt2A ( RgSchCellCb *cell, RgSchDlRbAlloc *rbAllocInfo, RgSchDlHqProcCb *hqP, RgSchPdcch *pdcch, U8 tpc )





  ;
static Void rgSCHCmnDlAllocTxRbTM1 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocTxRbTM2 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocTxRbTM3 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocTxRbTM4 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocTxRbTM6 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocTxRbTM7 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocRetxRbTM1 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocRetxRbTM2 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocRetxRbTM3 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocRetxRbTM4 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocRetxRbTM6 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlAllocRetxRbTM7 ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
RgSchCmnDlAllocRbFunc dlAllocTxRbFunc[7] = {rgSCHCmnDlAllocTxRbTM1,
rgSCHCmnDlAllocTxRbTM2, rgSCHCmnDlAllocTxRbTM3, rgSCHCmnDlAllocTxRbTM4,
0L, rgSCHCmnDlAllocTxRbTM6, rgSCHCmnDlAllocTxRbTM7};


RgSchCmnDlAllocRbFunc dlAllocRetxRbFunc[7] = {rgSCHCmnDlAllocRetxRbTM1,
rgSCHCmnDlAllocRetxRbTM2, rgSCHCmnDlAllocRetxRbTM3, rgSCHCmnDlAllocRetxRbTM4,
0L, rgSCHCmnDlAllocRetxRbTM6, rgSCHCmnDlAllocRetxRbTM7};
static U8 rgSCHCmnDlTM3PrecInf2 ( RgSchCellCb *cell, RgSchUeCb *ue, U8 numTxLyrs, Bool bothCwEnbld )




  ;
static U8 rgSCHCmnDlTM3PrecInf4 ( RgSchCellCb *cell, RgSchUeCb *ue, U8 numTxLyrs, Bool bothCwEnbld )




  ;
static U8 rgSCHCmnDlTM4PrecInf2 ( RgSchCellCb *cell, RgSchUeCb *ue, U8 numTxLyrs, Bool bothCwEnbld )




  ;
static U8 rgSCHCmnDlTM4PrecInf4 ( RgSchCellCb *cell, RgSchUeCb *ue, U8 numTxLyrs, Bool bothCwEnbld )




  ;

RgSchCmnDlGetPrecInfFunc getPrecInfoFunc[2][2] = {
{rgSCHCmnDlTM3PrecInf2, rgSCHCmnDlTM3PrecInf4},
{rgSCHCmnDlTM4PrecInf2, rgSCHCmnDlTM4PrecInf4}
};

static S16 rgSCHCmnDlAlloc1CwRetxRb ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, RgSchDlHqTbCb *tbInfo, U8 noLyr, U8 *numRb, U32 *effBo )







  ;
static S16 rgSCHCmnDlAlloc2CwRetxRb ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, RgSchDlHqProcCb *proc, U8 *numRb, Bool *swpFlg, U32 *effBo )







  ;
static Void rgSCHCmnDlTM3TxTx ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlTM3TxRetx ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static Void rgSCHCmnDlTM3RetxRetx ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, U32 bo, U32 *effBo, RgSchDlHqProcCb *proc, RgSchCmnDlRbAllocInfo *cellWdAllocInfo )







  ;
static TfuDciFormat rgSCHCmnSlctPdcchFrmt ( RgSchCellCb *cell, RgSchUeCb *ue, U8 *raType )



  ;
static Void rgSCHCmnNonDlfsUpdTyp2Alloc ( RgSchCellCb *cell, RgSchDlSf *dlSf, U8 rbStrt, U8 numRb )




  ;


static Void rgSCHCmnNonDlfsSFRCmnChannelUpdTyp2Alloc ( RgSchCellCb *cell, RgSchDlSf *dlSf, U8 rbStrt, U8 numRb )




  ;


static Void rgSCHCmnDlRbInfoAddUeTx ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo, RgSchUeCb *ue, RgSchDlHqProcCb *proc )




  ;
static Void rgSCHCmnDlRbInfoAddUeRetx ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo, RgSchUeCb *ue, RgSchDlHqProcCb *hqP )




  ;
static Void rgSCHCmnDlAdd2NonSchdRetxLst ( RgSchCmnDlRbAllocInfo *allocInfo, RgSchUeCb *ue, RgSchDlHqProcCb *proc )



  ;
static S16 rgSCHCmnDlAlloc2CwTxRetxRb ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, RgSchDlHqTbCb *reTxTb, RgSchDlHqTbCb *txTb, U8 *numRb, U32 *effBo )







  ;
static S16 rgSCHCmnDlAlloc2CwTxRb ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, RgSchDlHqProcCb *proc, U32 bo, U8 *numRb, U32 *effBo )







  ;
static S16 rgSCHCmnDlAlloc1CwTxRb ( RgSchCellCb *cell, RgSchDlSf *subFrm, RgSchUeCb *ue, RgSchDlHqTbCb *tbInfo, U32 bo, U8 *numRb, U32 *effBo )







  ;
static Void rgSCHCmnDlGetBestFitHole ( U32 *allocMask, U8 numMaskRbs, U32 *crntAllocMask, U8 rbsReq, U8 *allocStart, U8 *allocNumRbs, Bool isPartialAlloc )







  ;







static U32 rgSCHCmnGetRaType0Mask ( U8 rbIdx, U8 rbgSize )


  ;
static U32 rgSCHCmnGetRaType2Mask ( U8 rbIdx, U8 *maskIdx )


  ;


 Bool rgSCHCmnRetxAllocAvoid ( RgSchDlSf *subFrm, RgSchCellCb *cell, RgSchDlHqProcCb *proc )



  ;

static U16 rgSCHCmnGetSiSetId ( U16 sfn, U8 sf, U16 minPeriodicity )



  ;


static S16 rgSCHCmnUlMdfyGrntForCqi ( RgSchCellCb *cell, RgSchUeCb *ue, U32 maxRb, U32 *numSb, U8 *iTbs, U32 hqSz, U32 stepDownItbs, U32 effTgt )
  ;






 U32 rgSchCmnBetaCqiOffstTbl[16] = {0, 0, 1125,
   1250, 1375, 1625, 1750, 2000, 2250, 2500, 2875,
   3125, 3500, 4000, 5000, 6250};
 U32 rgSchCmnBetaHqOffstTbl[16] = {2000, 2500, 3125,
   4000, 5000, 6250, 8000,10000, 12625, 15875, 20000,
   31000, 50000,80000,126000,0};
 U32 rgSchCmnBetaRiOffstTbl[16] = {1250, 1625, 2000,
   2500, 3125, 4000, 5000, 6250, 8000, 10000,12625,
   15875,20000,0,0,0};
 S8 rgSchCmnDlCqiDiffOfst[8] = {0, 1, 2, 3, -4, -3, -2, -1};


const static U8 rgSchCmnAntIdx[5] = {0,0,1,0,2};
const static U8 rgSchCmnNumResForCrs[5] = {0,6,12,0,16};
U32 cfiSwitchCnt ;
U32 cfiIncr ;
U32 cfiDecr ;



 S8 rgSchCmnApUeSelDiffCqi[4] = {1, 2, 3, 4};
 S8 rgSchCmnApEnbConfDiffCqi[4] = {0, 1, 2, -1};


typedef struct rgSchCmnDlUeDciFrmtOptns
{
  TfuDciFormat spfcDciFrmt;

  U8 spfcDciRAType;
  TfuDciFormat prfrdDciFrmt;

  U8 prfrdDciRAType;
}RgSchCmnDlUeDciFrmtOptns;



RgSchCmnDlUeDciFrmtOptns rgSchCmnDciFrmtOptns[7] = {
   {TFU_DCI_FORMAT_1, 0, TFU_DCI_FORMAT_1A, 2},
   {TFU_DCI_FORMAT_1, 0, TFU_DCI_FORMAT_1A, 2},
   {TFU_DCI_FORMAT_2A,0, TFU_DCI_FORMAT_1A, 2},
   {TFU_DCI_FORMAT_2, 0, TFU_DCI_FORMAT_1A, 2},
   {TFU_DCI_FORMAT_1D,2, TFU_DCI_FORMAT_1A, 2},
   {TFU_DCI_FORMAT_1B,2, TFU_DCI_FORMAT_1A, 2},
   {TFU_DCI_FORMAT_1, 0, TFU_DCI_FORMAT_1A, 2}
};
typedef struct rgSchCmnDlImcsTbl
{
  U8 modOdr;
  U8 iTbs;
}RgSchCmnDlImcsTbl[29];

const struct rgSchCmnMult235Info
{
   U8 match;

   U8 prvMatch;

} rgSchCmnMult235Tbl[110+1] = {
   {0, 0},
   {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {6, 6}, {8, 8},
   {9, 9}, {10, 10}, {10, 10}, {12, 12}, {12, 12}, {15, 12}, {15, 15},
   {16, 16}, {16, 16}, {18, 18}, {18, 18}, {20, 20}, {20, 20}, {20, 20},
   {24, 20}, {24, 24}, {25, 25}, {25, 25}, {27, 27}, {27, 27}, {30, 27},
   {30, 30}, {30, 30}, {32, 32}, {32, 32}, {32, 32}, {36, 32}, {36, 36},
   {36, 36}, {36, 36}, {40, 36}, {40, 40}, {40, 40}, {40, 40}, {45, 40},
   {45, 40}, {45, 45}, {45, 45}, {48, 45}, {48, 48}, {48, 48}, {50, 50},
   {50, 50}, {50, 50}, {54, 50}, {54, 54}, {54, 54}, {54, 54}, {54, 54},
   {60, 54}, {60, 54}, {60, 60}, {60, 60}, {60, 60}, {64, 60}, {64, 64},
   {64, 64}, {64, 64}, {64, 64}, {64, 64}, {72, 64}, {72, 64}, {72, 64},
   {72, 72}, {72, 72}, {75, 72}, {75, 75}, {75, 75}, {75, 75}, {80, 75},
   {80, 75}, {80, 80}, {81, 81}, {81, 81}, {81, 81}, {81, 81}, {81, 81},
   {90, 81}, {90, 81}, {90, 81}, {90, 81}, {90, 90}, {90, 90}, {90, 90},
   {90, 90}, {96, 90}, {96, 90}, {96, 96}, {96, 96}, {96, 96}, {100, 96},
   {100, 100}, {100, 100}, {100, 100}, {100, 100}, {100, 100}, {108, 100},
   {108, 100}, {108, 100}, {108, 108}, {108, 108}, {108, 108}
};



const static S16 rgSchCmnBiTbl[13] = {
      0, 10, 20, 30,40,60,80,120,160,240,320,480,960};
 RgSchCmnUlCqiInfo rgSchCmnUlCqiTbl[16] = {
 { 0, 0 },
 {2,156 },
 {2,240 },
 {2,386 },
 {2,616 },
 {2,898 },
 {2,1204 },
 {4,1512 },
 {4,1960 },
 {4,2464 },
 {6,3402 },
 {6,3996 },
 {6,4102 },
 {6,4342 },
 {6,5238 },
 {6,5728 },
};
static U8 rgSchCmnDlQciPrio[9] = {1, 3, 2, 4, 0, 5, 6, 7, 8};
static U16 rgSchCmnCqiPdschEff[4][16] = {{207, 271, 333, 431, 648, 899, 1161, 1482, 1889, 2103, 2905, 3412, 3956, 4474, 4655, 5397} ,{226, 226, 226, 364, 471, 708, 983, 1411, 1833, 2299, 2612, 3177, 3731, 4326, 4893, 5090},
    {248, 248, 248, 326, 519, 780, 1084, 1399, 1786, 2278, 2714, 3194, 3810, 4442, 5069, 5398},{276, 276, 276, 276, 446, 708, 1052, 1382, 1734, 2254, 2827, 3212, 3908, 4590, 4953, 5653}};

static U16 rgSchCmn2LyrCqiPdschEff[4][16] = {{188, 226, 309, 366, 412, 539, 662, 859, 1052, 1293, 1535, 2585, 2957, 3340, 4775, 5300} ,{197, 232, 306, 322, 408, 450, 588, 723, 938, 1150, 1413, 1679, 2826, 3233, 5222, 5796},
    {166, 207, 233, 307, 343, 408, 422, 495, 586, 648, 797, 1035, 1268, 1558, 3117, 3567}, {177, 200, 221, 287, 323, 386, 433, 497, 522, 676, 722, 888, 1153, 1413, 1737, 3476}};



static U8 rgSchCmnDlRvTbl[4] = {0, 2, 3, 1};
static U16 rgSchCmnDciFrmtSizes[10];


static U16 rgSchCmnCqiPdcchEff[16] = { 400, 100, 150, 200, 250, 280, 340, 365, 380, 400, 500, 600, 700, 800, 900, 1000};
static U32 rgSchCmnBsrTbl[64] = {
   0, 10, 12, 14, 17, 19, 22, 26,
   31, 36, 42, 49, 57, 67, 78, 91,
   107, 125, 146, 171, 200, 234, 274, 321,
   376, 440, 515, 603, 706, 826, 967, 1132,
   1326, 1552, 1817, 2127, 2490, 2915, 3413, 3995,
   4677, 5476, 6411, 7505, 8787, 10287, 12043, 14099,
   16507, 19325, 22624, 26487, 31009, 36304, 42502, 49759,
   58255, 68201, 79846, 93479, 109439, 128125, 150000, 220000
};

static U32 rgSchCmnExtBsrTbl[64] = {
   0, 10, 13, 16, 19, 23, 29, 35,
   43, 53, 65, 80, 98, 120, 147, 181,
   223, 274, 337, 414, 509, 625, 769, 945,
   1162, 1429, 1757, 2161, 2657, 3267, 4017, 4940,
   6074, 7469, 9185, 11294, 13888, 17077, 20999, 25822,
   31752, 39045, 48012, 59039, 72598, 89272, 109774, 134986,
   165989, 204111, 250990, 308634, 379519, 466683, 573866, 705666,
   867737, 1067031, 1312097, 1613447, 1984009, 2439678, 3000000, 3100000
};


static U8 rgSchCmnUlRvIdxToIMcsTbl[4] = {32, 30, 31, 29};

 U8 rgSchCmnUlCqiToTbsTbl[2][16];

 RgSchTbSzTbl rgTbSzTbl = {
 {
   {16, 32, 56, 88, 120, 152, 176, 208, 224, 256, 288, 328, 344, 376, 392, 424, 456, 488, 504, 536, 568, 600, 616, 648, 680, 712, 744, 776, 776, 808, 840, 872, 904, 936, 968, 1000, 1032, 1032, 1064, 1096, 1128, 1160, 1192, 1224, 1256, 1256, 1288, 1320, 1352, 1384, 1416, 1416, 1480, 1480, 1544, 1544, 1608, 1608, 1608, 1672, 1672, 1736, 1736, 1800, 1800, 1800, 1864, 1864, 1928, 1928, 1992, 1992, 2024, 2088, 2088, 2088, 2152, 2152, 2216, 2216, 2280, 2280, 2280, 2344, 2344, 2408, 2408, 2472, 2472, 2536, 2536, 2536, 2600, 2600, 2664, 2664, 2728, 2728, 2728, 2792, 2792, 2856, 2856, 2856, 2984, 2984, 2984, 2984, 2984, 3112},
   {24, 56, 88, 144, 176, 208, 224, 256, 328, 344, 376, 424, 456, 488, 520, 568, 600, 632, 680, 712, 744, 776, 808, 872, 904, 936, 968, 1000, 1032, 1064, 1128, 1160, 1192, 1224, 1256, 1288, 1352, 1384, 1416, 1416, 1480, 1544, 1544, 1608, 1608, 1672, 1736, 1736, 1800, 1800, 1864, 1864, 1928, 1992, 1992, 2024, 2088, 2088, 2152, 2152, 2216, 2280, 2280, 2344, 2344, 2408, 2472, 2472, 2536, 2536, 2600, 2600, 2664, 2728, 2728, 2792, 2792, 2856, 2856, 2856, 2984, 2984, 2984, 3112, 3112, 3112, 3240, 3240, 3240, 3240, 3368, 3368, 3368, 3496, 3496, 3496, 3496, 3624, 3624, 3624, 3752, 3752, 3752, 3752, 3880, 3880, 3880, 4008, 4008, 4008},
   {32, 72, 144, 176, 208, 256, 296, 328, 376, 424, 472, 520, 568, 616, 648, 696, 744, 776, 840, 872, 936, 968, 1000, 1064, 1096, 1160, 1192, 1256, 1288, 1320, 1384, 1416, 1480, 1544, 1544, 1608, 1672, 1672, 1736, 1800, 1800, 1864, 1928, 1992, 2024, 2088, 2088, 2152, 2216, 2216, 2280, 2344, 2344, 2408, 2472, 2536, 2536, 2600, 2664, 2664, 2728, 2792, 2856, 2856, 2856, 2984, 2984, 3112, 3112, 3112, 3240, 3240, 3240, 3368, 3368, 3368, 3496, 3496, 3496, 3624, 3624, 3624, 3752, 3752, 3880, 3880, 3880, 4008, 4008, 4008, 4136, 4136, 4136, 4264, 4264, 4264, 4392, 4392, 4392, 4584, 4584, 4584, 4584, 4584, 4776, 4776, 4776, 4776, 4968, 4968},
   {40, 104, 176, 208, 256, 328, 392, 440, 504, 568, 616, 680, 744, 808, 872, 904, 968, 1032, 1096, 1160, 1224, 1256, 1320, 1384, 1416, 1480, 1544, 1608, 1672, 1736, 1800, 1864, 1928, 1992, 2024, 2088, 2152, 2216, 2280, 2344, 2408, 2472, 2536, 2536, 2600, 2664, 2728, 2792, 2856, 2856, 2984, 2984, 3112, 3112, 3240, 3240, 3368, 3368, 3496, 3496, 3624, 3624, 3624, 3752, 3752, 3880, 3880, 4008, 4008, 4136, 4136, 4264, 4264, 4392, 4392, 4392, 4584, 4584, 4584, 4776, 4776, 4776, 4776, 4968, 4968, 4968, 5160, 5160, 5160, 5352, 5352, 5352, 5352, 5544, 5544, 5544, 5736, 5736, 5736, 5736, 5992, 5992, 5992, 5992, 6200, 6200, 6200, 6200, 6456, 6456},
   {56, 120, 208, 256, 328, 408, 488, 552, 632, 696, 776, 840, 904, 1000, 1064, 1128, 1192, 1288, 1352, 1416, 1480, 1544, 1608, 1736, 1800, 1864, 1928, 1992, 2088, 2152, 2216, 2280, 2344, 2408, 2472, 2600, 2664, 2728, 2792, 2856, 2984, 2984, 3112, 3112, 3240, 3240, 3368, 3496, 3496, 3624, 3624, 3752, 3752, 3880, 4008, 4008, 4136, 4136, 4264, 4264, 4392, 4392, 4584, 4584, 4584, 4776, 4776, 4968, 4968, 4968, 5160, 5160, 5160, 5352, 5352, 5544, 5544, 5544, 5736, 5736, 5736, 5992, 5992, 5992, 5992, 6200, 6200, 6200, 6456, 6456, 6456, 6456, 6712, 6712, 6712, 6968, 6968, 6968, 6968, 7224, 7224, 7224, 7480, 7480, 7480, 7480, 7736, 7736, 7736, 7992},
   {72, 144, 224, 328, 424, 504, 600, 680, 776, 872, 968, 1032, 1128, 1224, 1320, 1384, 1480, 1544, 1672, 1736, 1864, 1928, 2024, 2088, 2216, 2280, 2344, 2472, 2536, 2664, 2728, 2792, 2856, 2984, 3112, 3112, 3240, 3368, 3496, 3496, 3624, 3752, 3752, 3880, 4008, 4008, 4136, 4264, 4392, 4392, 4584, 4584, 4776, 4776, 4776, 4968, 4968, 5160, 5160, 5352, 5352, 5544, 5544, 5736, 5736, 5736, 5992, 5992, 5992, 6200, 6200, 6200, 6456, 6456, 6712, 6712, 6712, 6968, 6968, 6968, 7224, 7224, 7224, 7480, 7480, 7480, 7736, 7736, 7736, 7992, 7992, 7992, 8248, 8248, 8248, 8504, 8504, 8760, 8760, 8760, 8760, 9144, 9144, 9144, 9144, 9528, 9528, 9528, 9528, 9528},
   {328, 176, 256, 392, 504, 600, 712, 808, 936, 1032, 1128, 1224, 1352, 1480, 1544, 1672, 1736, 1864, 1992, 2088, 2216, 2280, 2408, 2472, 2600, 2728, 2792, 2984, 2984, 3112, 3240, 3368, 3496, 3496, 3624, 3752, 3880, 4008, 4136, 4136, 4264, 4392, 4584, 4584, 4776, 4776, 4968, 4968, 5160, 5160, 5352, 5352, 5544, 5736, 5736, 5992, 5992, 5992, 6200, 6200, 6456, 6456, 6456, 6712, 6712, 6968, 6968, 6968, 7224, 7224, 7480, 7480, 7736, 7736, 7736, 7992, 7992, 8248, 8248, 8248, 8504, 8504, 8760, 8760, 8760, 9144, 9144, 9144, 9144, 9528, 9528, 9528, 9528, 9912, 9912, 9912, 10296, 10296, 10296, 10296, 10680, 10680, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11448},
   {104, 224, 328, 472, 584, 712, 840, 968, 1096, 1224, 1320, 1480, 1608, 1672, 1800, 1928, 2088, 2216, 2344, 2472, 2536, 2664, 2792, 2984, 3112, 3240, 3368, 3368, 3496, 3624, 3752, 3880, 4008, 4136, 4264, 4392, 4584, 4584, 4776, 4968, 4968, 5160, 5352, 5352, 5544, 5736, 5736, 5992, 5992, 6200, 6200, 6456, 6456, 6712, 6712, 6712, 6968, 6968, 7224, 7224, 7480, 7480, 7736, 7736, 7992, 7992, 8248, 8248, 8504, 8504, 8760, 8760, 8760, 9144, 9144, 9144, 9528, 9528, 9528, 9912, 9912, 9912, 10296, 10296, 10296, 10680, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11448, 11448, 11832, 11832, 11832, 12216, 12216, 12216, 12576, 12576, 12576, 12960, 12960, 12960, 12960, 13536, 13536},
   {120, 256, 392, 536, 680, 808, 968, 1096, 1256, 1384, 1544, 1672, 1800, 1928, 2088, 2216, 2344, 2536, 2664, 2792, 2984, 3112, 3240, 3368, 3496, 3624, 3752, 3880, 4008, 4264, 4392, 4584, 4584, 4776, 4968, 4968, 5160, 5352, 5544, 5544, 5736, 5992, 5992, 6200, 6200, 6456, 6456, 6712, 6968, 6968, 7224, 7224, 7480, 7480, 7736, 7736, 7992, 7992, 8248, 8504, 8504, 8760, 8760, 9144, 9144, 9144, 9528, 9528, 9528, 9912, 9912, 9912, 10296, 10296, 10680, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11448, 11832, 11832, 12216, 12216, 12216, 12576, 12576, 12576, 12960, 12960, 12960, 13536, 13536, 13536, 13536, 14112, 14112, 14112, 14112, 14688, 14688, 14688, 14688, 15264, 15264, 15264, 15264},
   {136, 296, 456, 616, 776, 936, 1096, 1256, 1416, 1544, 1736, 1864, 2024, 2216, 2344, 2536, 2664, 2856, 2984, 3112, 3368, 3496, 3624, 3752, 4008, 4136, 4264, 4392, 4584, 4776, 4968, 5160, 5160, 5352, 5544, 5736, 5736, 5992, 6200, 6200, 6456, 6712, 6712, 6968, 6968, 7224, 7480, 7480, 7736, 7992, 7992, 8248, 8248, 8504, 8760, 8760, 9144, 9144, 9144, 9528, 9528, 9912, 9912, 10296, 10296, 10296, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11832, 11832, 11832, 12216, 12216, 12576, 12576, 12960, 12960, 12960, 13536, 13536, 13536, 13536, 14112, 14112, 14112, 14112, 14688, 14688, 14688, 15264, 15264, 15264, 15264, 15840, 15840, 15840, 16416, 16416, 16416, 16416, 16992, 16992, 16992, 16992, 17568},
   {144, 328, 504, 680, 872, 1032, 1224, 1384, 1544, 1736, 1928, 2088, 2280, 2472, 2664, 2792, 2984, 3112, 3368, 3496, 3752, 3880, 4008, 4264, 4392, 4584, 4776, 4968, 5160, 5352, 5544, 5736, 5736, 5992, 6200, 6200, 6456, 6712, 6712, 6968, 7224, 7480, 7480, 7736, 7992, 7992, 8248, 8504, 8504, 8760, 9144, 9144, 9144, 9528, 9528, 9912, 9912, 10296, 10296, 10680, 10680, 11064, 11064, 11448, 11448, 11448, 11832, 11832, 12216, 12216, 12576, 12576, 12960, 12960, 12960, 13536, 13536, 13536, 14112, 14112, 14112, 14688, 14688, 14688, 14688, 15264, 15264, 15264, 15840, 15840, 15840, 16416, 16416, 16416, 16992, 16992, 16992, 16992, 17568, 17568, 17568, 18336, 18336, 18336, 18336, 18336, 19080, 19080, 19080, 19080},
   {176, 376, 584, 776, 1000, 1192, 1384, 1608, 1800, 2024, 2216, 2408, 2600, 2792, 2984, 3240, 3496, 3624, 3880, 4008, 4264, 4392, 4584, 4776, 4968, 5352, 5544, 5736, 5992, 5992, 6200, 6456, 6712, 6968, 6968, 7224, 7480, 7736, 7736, 7992, 8248, 8504, 8760, 8760, 9144, 9144, 9528, 9528, 9912, 9912, 10296, 10680, 10680, 11064, 11064, 11448, 11448, 11832, 11832, 12216, 12216, 12576, 12576, 12960, 12960, 13536, 13536, 13536, 14112, 14112, 14112, 14688, 14688, 14688, 15264, 15264, 15840, 15840, 15840, 16416, 16416, 16416, 16992, 16992, 16992, 17568, 17568, 17568, 18336, 18336, 18336, 18336, 19080, 19080, 19080, 19080, 19848, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 21384, 21384, 22152, 22152, 22152},
   {208, 440, 680, 904, 1128, 1352, 1608, 1800, 2024, 2280, 2472, 2728, 2984, 3240, 3368, 3624, 3880, 4136, 4392, 4584, 4776, 4968, 5352, 5544, 5736, 5992, 6200, 6456, 6712, 6712, 6968, 7224, 7480, 7736, 7992, 8248, 8504, 8760, 8760, 9144, 9528, 9528, 9912, 9912, 10296, 10680, 10680, 11064, 11064, 11448, 11832, 11832, 12216, 12216, 12576, 12576, 12960, 12960, 13536, 13536, 14112, 14112, 14112, 14688, 14688, 15264, 15264, 15264, 15840, 15840, 16416, 16416, 16416, 16992, 16992, 17568, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 22920, 23688, 23688, 23688, 23688, 24496, 24496, 24496, 24496, 25456},
   {224, 488, 744, 1000, 1256, 1544, 1800, 2024, 2280, 2536, 2856, 3112, 3368, 3624, 3880, 4136, 4392, 4584, 4968, 5160, 5352, 5736, 5992, 6200, 6456, 6712, 6968, 7224, 7480, 7736, 7992, 8248, 8504, 8760, 9144, 9144, 9528, 9912, 9912, 10296, 10680, 10680, 11064, 11448, 11448, 11832, 12216, 12216, 12576, 12960, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 14688, 15264, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 16992, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 22920, 23688, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 25456, 26416, 26416, 26416, 26416, 27376, 27376, 27376, 27376, 28336, 28336},
   {256, 552, 840, 1128, 1416, 1736, 1992, 2280, 2600, 2856, 3112, 3496, 3752, 4008, 4264, 4584, 4968, 5160, 5544, 5736, 5992, 6200, 6456, 6968, 7224, 7480, 7736, 7992, 8248, 8504, 8760, 9144, 9528, 9912, 9912, 10296, 10680, 11064, 11064, 11448, 11832, 12216, 12216, 12576, 12960, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 15264, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 25456, 26416, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 28336, 28336, 29296, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704},
   {280, 600, 904, 1224, 1544, 1800, 2152, 2472, 2728, 3112, 3368, 3624, 4008, 4264, 4584, 4968, 5160, 5544, 5736, 6200, 6456, 6712, 6968, 7224, 7736, 7992, 8248, 8504, 8760, 9144, 9528, 9912, 10296, 10296, 10680, 11064, 11448, 11832, 11832, 12216, 12576, 12960, 12960, 13536, 13536, 14112, 14688, 14688, 15264, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 23688, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 26416, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 28336, 29296, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008},
   {328, 632, 968, 1288, 1608, 1928, 2280, 2600, 2984, 3240, 3624, 3880, 4264, 4584, 4968, 5160, 5544, 5992, 6200, 6456, 6712, 7224, 7480, 7736, 7992, 8504, 8760, 9144, 9528, 9912, 9912, 10296, 10680, 11064, 11448, 11832, 12216, 12216, 12576, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 17568, 17568, 18336, 18336, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 21384, 21384, 22152, 22152, 22152, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 26416, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 34008, 35160, 35160, 35160, 35160},
   {336, 696, 1064, 1416, 1800, 2152, 2536, 2856, 3240, 3624, 4008, 4392, 4776, 5160, 5352, 5736, 6200, 6456, 6712, 7224, 7480, 7992, 8248, 8760, 9144, 9528, 9912, 10296, 10296, 10680, 11064, 11448, 11832, 12216, 12576, 12960, 13536, 13536, 14112, 14688, 14688, 15264, 15264, 15840, 16416, 16416, 16992, 17568, 17568, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 22152, 22152, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 26416, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 35160, 36696, 36696, 36696, 36696, 37888, 37888, 37888, 39232, 39232, 39232, 39232},
   {376, 776, 1160, 1544, 1992, 2344, 2792, 3112, 3624, 4008, 4392, 4776, 5160, 5544, 5992, 6200, 6712, 7224, 7480, 7992, 8248, 8760, 9144, 9528, 9912, 10296, 10680, 11064, 11448, 11832, 12216, 12576, 12960, 13536, 14112, 14112, 14688, 15264, 15264, 15840, 16416, 16416, 16992, 17568, 17568, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 21384, 21384, 22152, 22152, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 26416, 26416, 27376, 27376, 27376, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 40576, 42368, 42368, 42368, 42368, 43816, 43816},
   {408, 840, 1288, 1736, 2152, 2600, 2984, 3496, 3880, 4264, 4776, 5160, 5544, 5992, 6456, 6968, 7224, 7736, 8248, 8504, 9144, 9528, 9912, 10296, 10680, 11064, 11448, 12216, 12576, 12960, 13536, 13536, 14112, 14688, 15264, 15264, 15840, 16416, 16992, 16992, 17568, 18336, 18336, 19080, 19080, 19848, 20616, 20616, 21384, 21384, 22152, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 25456, 26416, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 46888},
   {440, 904, 1384, 1864, 2344, 2792, 3240, 3752, 4136, 4584, 5160, 5544, 5992, 6456, 6968, 7480, 7992, 8248, 8760, 9144, 9912, 10296, 10680, 11064, 11448, 12216, 12576, 12960, 13536, 14112, 14688, 14688, 15264, 15840, 16416, 16992, 16992, 17568, 18336, 18336, 19080, 19848, 19848, 20616, 20616, 21384, 22152, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 46888, 48936, 48936, 48936, 48936, 48936, 51024, 51024, 51024},
   {488, 1000, 1480, 1992, 2472, 2984, 3496, 4008, 4584, 4968, 5544, 5992, 6456, 6968, 7480, 7992, 8504, 9144, 9528, 9912, 10680, 11064, 11448, 12216, 12576, 12960, 13536, 14112, 14688, 15264, 15840, 15840, 16416, 16992, 17568, 18336, 18336, 19080, 19848, 19848, 20616, 21384, 21384, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 46888, 48936, 48936, 48936, 48936, 51024, 51024, 51024, 51024, 52752, 52752, 52752, 52752, 55056, 55056, 55056},
   {520, 1064, 1608, 2152, 2664, 3240, 3752, 4264, 4776, 5352, 5992, 6456, 6968, 7480, 7992, 8504, 9144, 9528, 10296, 10680, 11448, 11832, 12576, 12960, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 16992, 17568, 18336, 19080, 19080, 19848, 20616, 21384, 21384, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 30576, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 48936, 51024, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336, 57336, 57336, 59256, 59256, 59256},
   {552, 1128, 1736, 2280, 2856, 3496, 4008, 4584, 5160, 5736, 6200, 6968, 7480, 7992, 8504, 9144, 9912, 10296, 11064, 11448, 12216, 12576, 12960, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 19848, 20616, 21384, 22152, 22152, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 30576, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 37888, 37888, 37888, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336, 57336, 57336, 59256, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776},
   {584, 1192, 1800, 2408, 2984, 3624, 4264, 4968, 5544, 5992, 6712, 7224, 7992, 8504, 9144, 9912, 10296, 11064, 11448, 12216, 12960, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 19848, 20616, 21384, 22152, 22920, 22920, 23688, 24496, 25456, 25456, 26416, 26416, 27376, 28336, 28336, 29296, 29296, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 52752, 52752, 52752, 52752, 55056, 55056, 55056, 57336, 57336, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776, 63776, 63776, 63776, 66592, 66592, 66592, 66592},
   {616, 1256, 1864, 2536, 3112, 3752, 4392, 5160, 5736, 6200, 6968, 7480, 8248, 8760, 9528, 10296, 10680, 11448, 12216, 12576, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 20616, 20616, 21384, 22152, 22920, 23688, 24496, 24496, 25456, 26416, 26416, 27376, 28336, 28336, 29296, 29296, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776, 63776, 63776, 63776, 66592, 66592, 66592, 66592, 68808, 68808, 68808, 71112},
   {712, 1480, 2216, 2984, 3752, 4392, 5160, 5992, 6712, 7480, 8248, 8760, 9528, 10296, 11064, 11832, 12576, 13536, 14112, 14688, 15264, 16416, 16992, 17568, 18336, 19080, 19848, 20616, 21384, 22152, 22920, 23688, 24496, 25456, 25456, 26416, 27376, 28336, 29296, 29296, 30576, 30576, 31704, 32856, 32856, 34008, 35160, 35160, 36696, 36696, 37888, 37888, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 45352, 45352, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 63776, 63776, 63776, 66592, 66592, 66592, 68808, 68808, 68808, 71112, 71112, 71112, 73712, 73712, 75376, 75376, 75376, 75376, 75376, 75376, 75376, 75376, 75376, 75376, 75376}
 },
 {
   {32, 88, 152, 208, 256, 328, 376, 424, 488, 536, 600, 648, 712, 776, 808, 872, 936, 1000, 1032, 1096, 1160, 1224, 1256, 1320, 1384, 1416, 1480, 1544, 1608, 1672, 1736, 1800, 1800, 1864, 1928, 1992, 2088, 2088, 2152, 2216, 2280, 2344, 2408, 2472, 2536, 2536, 2600, 2664, 2728, 2792, 2856, 2856, 2984, 2984, 3112, 3112, 3240, 3240, 3240, 3368, 3368, 3496, 3496, 3624, 3624, 3624, 3752, 3752, 3880, 3880, 4008, 4008, 4008, 4136, 4136, 4136, 4264, 4264, 4392, 4392, 4584, 4584, 4584, 4776, 4776, 4776, 4776, 4968, 4968, 5160, 5160, 5160, 5160, 5160, 5352, 5352, 5544, 5544, 5544, 5544, 5544, 5736, 5736, 5736, 5992, 5992, 5992, 5992, 5992, 6200},
   {56, 144, 208, 256, 344, 424, 488, 568, 632, 712, 776, 872, 936, 1000, 1064, 1160, 1224, 1288, 1384, 1416, 1544, 1608, 1672, 1736, 1800, 1864, 1992, 2024, 2088, 2152, 2280, 2344, 2408, 2472, 2536, 2600, 2728, 2792, 2856, 2856, 2984, 3112, 3112, 3240, 3240, 3368, 3496, 3496, 3624, 3624, 3752, 3752, 3880, 4008, 4008, 4008, 4136, 4136, 4264, 4264, 4392, 4584, 4584, 4776, 4776, 4776, 4968, 4968, 5160, 5160, 5160, 5160, 5352, 5544, 5544, 5544, 5544, 5736, 5736, 5736, 5992, 5992, 5992, 6200, 6200, 6200, 6456, 6456, 6456, 6456, 6712, 6712, 6712, 6968, 6968, 6968, 6968, 7224, 7224, 7224, 7480, 7480, 7480, 7480, 7736, 7736, 7736, 7992, 7992, 7992},
   {72, 176, 256, 328, 424, 520, 616, 696, 776, 872, 968, 1064, 1160, 1256, 1320, 1416, 1544, 1608, 1672, 1800, 1864, 1992, 2088, 2152, 2216, 2344, 2408, 2536, 2600, 2664, 2792, 2856, 2984, 3112, 3112, 3240, 3368, 3368, 3496, 3624, 3624, 3752, 3880, 4008, 4008, 4136, 4264, 4264, 4392, 4584, 4584, 4584, 4776, 4776, 4968, 5160, 5160, 5160, 5352, 5352, 5544, 5544, 5736, 5736, 5736, 5992, 5992, 6200, 6200, 6200, 6456, 6456, 6456, 6712, 6712, 6712, 6968, 6968, 6968, 7224, 7224, 7224, 7480, 7480, 7736, 7736, 7736, 7992, 7992, 7992, 8248, 8248, 8248, 8504, 8504, 8504, 8760, 8760, 8760, 9144, 9144, 9144, 9144, 9144, 9528, 9528, 9528, 9528, 9912, 9912},
   {104, 208, 328, 440, 568, 680, 808, 904, 1032, 1160, 1256, 1384, 1480, 1608, 1736, 1864, 1992, 2088, 2216, 2344, 2472, 2536, 2664, 2792, 2856, 2984, 3112, 3240, 3368, 3496, 3624, 3752, 3880, 4008, 4136, 4264, 4392, 4392, 4584, 4776, 4776, 4968, 4968, 5160, 5352, 5352, 5544, 5544, 5736, 5736, 5992, 5992, 6200, 6200, 6456, 6456, 6712, 6712, 6968, 6968, 7224, 7224, 7224, 7480, 7480, 7736, 7736, 7992, 7992, 8248, 8248, 8504, 8504, 8760, 8760, 8760, 9144, 9144, 9144, 9528, 9528, 9528, 9528, 9912, 9912, 9912, 10296, 10296, 10296, 10680, 10680, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11448, 11448, 11832, 11832, 11832, 11832, 12576, 12576, 12576, 12576, 12960, 12960},
   {120, 256, 408, 552, 696, 840, 1000, 1128, 1288, 1416, 1544, 1736, 1864, 1992, 2152, 2280, 2408, 2600, 2728, 2856, 2984, 3112, 3240, 3496, 3624, 3752, 3880, 4008, 4136, 4264, 4392, 4584, 4776, 4968, 4968, 5160, 5352, 5544, 5544, 5736, 5992, 5992, 6200, 6200, 6456, 6456, 6712, 6968, 6968, 7224, 7224, 7480, 7480, 7736, 7992, 7992, 8248, 8248, 8504, 8504, 8760, 8760, 9144, 9144, 9144, 9528, 9528, 9912, 9912, 9912, 10296, 10296, 10296, 10680, 10680, 11064, 11064, 11064, 11448, 11448, 11448, 11832, 11832, 11832, 11832, 12576, 12576, 12576, 12960, 12960, 12960, 12960, 13536, 13536, 13536, 14112, 14112, 14112, 14112, 14688, 14688, 14688, 14688, 14688, 14688, 14688, 15264, 15264, 15264, 15840},
   {144, 328, 504, 680, 872, 1032, 1224, 1384, 1544, 1736, 1928, 2088, 2280, 2472, 2664, 2792, 2984, 3112, 3368, 3496, 3752, 3880, 4008, 4264, 4392, 4584, 4776, 4968, 5160, 5352, 5544, 5736, 5736, 5992, 6200, 6200, 6456, 6712, 6968, 6968, 7224, 7480, 7480, 7736, 7992, 7992, 8248, 8504, 8760, 8760, 9144, 9144, 9528, 9528, 9528, 9912, 9912, 10296, 10296, 10680, 10680, 11064, 11064, 11448, 11448, 11448, 11832, 11832, 11832, 12576, 12576, 12576, 12960, 12960, 13536, 13536, 13536, 14112, 14112, 14112, 14688, 14688, 14688, 14688, 14688, 14688, 15264, 15264, 15264, 15840, 15840, 15840, 16416, 16416, 16416, 16992, 16992, 17568, 17568, 17568, 17568, 18336, 18336, 18336, 18336, 19080, 19080, 19080, 19080, 19080},
   {176, 392, 600, 808, 1032, 1224, 1480, 1672, 1864, 2088, 2280, 2472, 2728, 2984, 3112, 3368, 3496, 3752, 4008, 4136, 4392, 4584, 4776, 4968, 5160, 5352, 5736, 5992, 5992, 6200, 6456, 6712, 6968, 6968, 7224, 7480, 7736, 7992, 8248, 8248, 8504, 8760, 9144, 9144, 9528, 9528, 9912, 9912, 10296, 10296, 10680, 10680, 11064, 11448, 11448, 11832, 11832, 11832, 12576, 12576, 12960, 12960, 12960, 13536, 13536, 14112, 14112, 14112, 14688, 14688, 14688, 14688, 15264, 15264, 15264, 15840, 15840, 16416, 16416, 16416, 16992, 16992, 17568, 17568, 17568, 18336, 18336, 18336, 18336, 19080, 19080, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 20616, 20616, 21384, 21384, 21384, 21384, 24264, 24264, 24264, 22920, 22920, 22920},
   {224, 472, 712, 968, 1224, 1480, 1672, 1928, 2216, 2472, 2664, 2984, 3240, 3368, 3624, 3880, 4136, 4392, 4584, 4968, 5160, 5352, 5736, 5992, 6200, 6456, 6712, 6712, 6968, 7224, 7480, 7736, 7992, 8248, 8504, 8760, 9144, 9144, 9528, 9912, 9912, 10296, 10680, 10680, 11064, 11448, 11448, 11832, 11832, 12216, 12576, 12576, 12960, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 14688, 14688, 15264, 15264, 15840, 15840, 16416, 16416, 16992, 16992, 17568, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 21384, 24264, 24264, 24264, 22920, 22920, 22920, 22920, 23688, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 25456, 25456, 25456, 25456, 27376, 27376},
   {256, 536, 808, 1096, 1384, 1672, 1928, 2216, 2536, 2792, 3112, 3368, 3624, 3880, 4264, 4584, 4776, 4968, 5352, 5544, 5992, 6200, 6456, 6712, 6968, 7224, 7480, 7736, 7992, 8504, 8760, 9144, 9144, 9528, 9912, 9912, 10296, 10680, 11064, 11064, 11448, 11832, 12216, 12216, 12576, 12960, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 15264, 15264, 15264, 15840, 15840, 16416, 16992, 16992, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19080, 19848, 19848, 19848, 20616, 20616, 21384, 21384, 21384, 24264, 24264, 24264, 22920, 22920, 22920, 23688, 23688, 24496, 24496, 24496, 25456, 25456, 25456, 25456, 25456, 25456, 27376, 27376, 27376, 27376, 28336, 28336, 28336, 28336, 29296, 29296, 29296, 29296, 30576, 30576, 30576, 30576},
   {296, 616, 936, 1256, 1544, 1864, 2216, 2536, 2856, 3112, 3496, 3752, 4136, 4392, 4776, 5160, 5352, 5736, 5992, 6200, 6712, 6968, 7224, 7480, 7992, 8248, 8504, 8760, 9144, 9528, 9912, 10296, 10296, 10680, 11064, 11448, 11832, 11832, 12216, 12576, 12960, 13536, 13536, 14112, 14112, 14688, 14688, 15264, 15264, 15840, 16416, 16416, 16992, 16992, 17568, 17568, 18336, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 20616, 20616, 21384, 21384, 24264, 24264, 24264, 22920, 22920, 23688, 23688, 23688, 24496, 24496, 25456, 25456, 25456, 25456, 25456, 27376, 27376, 27376, 27376, 28336, 28336, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 32856, 32856, 34008, 34008, 34008, 34008, 35160},
   {328, 680, 1032, 1384, 1736, 2088, 2472, 2792, 3112, 3496, 3880, 4264, 4584, 4968, 5352, 5736, 5992, 6200, 6712, 6968, 7480, 7736, 7992, 8504, 8760, 9144, 9528, 9912, 10296, 10680, 11064, 11448, 11448, 11832, 12216, 12576, 12960, 13536, 13536, 14112, 14688, 14688, 15264, 15264, 15840, 16416, 16416, 16992, 16992, 17568, 18336, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 20616, 21384, 21384, 24264, 24264, 22920, 22920, 22920, 23688, 23688, 24496, 24496, 25456, 25456, 25456, 25456, 25456, 27376, 27376, 27376, 28336, 28336, 28336, 29296, 29296, 29296, 29296, 30576, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 36696, 36696, 37888, 37888, 37888, 37888},
   {376, 776, 1192, 1608, 2024, 2408, 2792, 3240, 3624, 4008, 4392, 4776, 5352, 5736, 5992, 6456, 6968, 7224, 7736, 7992, 8504, 8760, 9144, 9528, 9912, 10680, 11064, 11448, 11832, 12216, 12576, 12960, 13536, 13536, 14112, 14688, 14688, 15264, 15840, 16416, 16416, 16992, 17568, 17568, 18336, 18336, 19080, 19080, 19848, 19848, 20616, 21384, 21384, 22152, 22152, 22920, 22920, 23688, 23688, 24496, 24496, 25456, 25456, 25456, 25456, 27376, 27376, 27376, 28336, 28336, 28336, 29296, 29296, 29296, 30576, 30576, 31704, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 36696, 37888, 37888, 37888, 37888, 39232, 39232, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 42368, 43816, 43816, 43816},
   {440, 904, 1352, 1800, 2280, 2728, 3240, 3624, 4136, 4584, 4968, 5544, 5992, 6456, 6712, 7224, 7736, 8248, 8760, 9144, 9528, 9912, 10680, 11064, 11448, 11832, 12216, 12576, 12960, 13536, 14112, 14688, 15264, 15264, 15840, 16416, 16992, 17568, 17568, 18336, 19080, 19080, 19848, 19848, 20616, 21384, 21384, 22152, 22152, 22920, 23688, 23688, 24496, 24496, 25456, 25456, 25456, 25456, 27376, 27376, 28336, 28336, 28336, 29296, 29296, 30576, 30576, 30576, 31704, 31704, 32856, 32856, 32856, 34008, 34008, 35160, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 46888, 48936, 48936, 48936, 48936, 51024},
   {488, 1000, 1544, 2024, 2536, 3112, 3624, 4136, 4584, 5160, 5736, 6200, 6712, 7224, 7736, 8248, 8760, 9144, 9912, 10296, 10680, 11448, 11832, 12216, 12960, 13536, 14112, 14688, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 18336, 19080, 19848, 19848, 20616, 21384, 21384, 22152, 22920, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 26416, 27376, 27376, 28336, 29296, 29296, 29296, 30576, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 34008, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 51024, 52752, 52752, 52752, 52752, 55056, 55056, 55056, 55056, 57336, 57336},
   {552, 1128, 1736, 2280, 2856, 3496, 4008, 4584, 5160, 5736, 6200, 6968, 7480, 7992, 8504, 9144, 9912, 10296, 11064, 11448, 12216, 12576, 12960, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 19848, 20616, 21384, 22152, 22152, 22920, 23688, 24496, 24496, 25456, 25456, 26416, 27376, 27376, 28336, 28336, 29296, 29296, 30576, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 45352, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 57336, 57336, 57336, 57336, 59256, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776, 63776},
   {600, 1224, 1800, 2472, 3112, 3624, 4264, 4968, 5544, 6200, 6712, 7224, 7992, 8504, 9144, 9912, 10296, 11064, 11832, 12216, 12960, 13536, 14112, 14688, 15264, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 20616, 20616, 21384, 22152, 22920, 23688, 23688, 24496, 25456, 25456, 26416, 27376, 27376, 28336, 29296, 29296, 30576, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 46888, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 57336, 57336, 57336, 59256, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776, 63776, 63776, 63776, 66592, 66592, 66592, 68808, 68808},
   {632, 1288, 1928, 2600, 3240, 3880, 4584, 5160, 5992, 6456, 7224, 7736, 8504, 9144, 9912, 10296, 11064, 11832, 12216, 12960, 13536, 14112, 14688, 15840, 16416, 16992, 17568, 18336, 19080, 19848, 19848, 20616, 21384, 22152, 22920, 23688, 24496, 24496, 25456, 26416, 26416, 27376, 28336, 28336, 29296, 30576, 30576, 31704, 31704, 32856, 32856, 34008, 34008, 35160, 35160, 36696, 36696, 37888, 37888, 39232, 39232, 39232, 40576, 40576, 42368, 42368, 43816, 43816, 43816, 45352, 45352, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 57336, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776, 63776, 63776, 63776, 66592, 66592, 66592, 68808, 68808, 68808, 68808, 71112, 71112, 71112, 71112},
   {696, 1416, 2152, 2856, 3624, 4392, 5160, 5736, 6456, 7224, 7992, 8760, 9528, 10296, 10680, 11448, 12216, 12960, 13536, 14688, 15264, 15840, 16416, 17568, 18336, 19080, 19848, 20616, 20616, 21384, 22152, 22920, 23688, 24496, 25456, 26416, 26416, 27376, 28336, 29296, 29296, 30576, 30576, 31704, 32856, 32856, 34008, 35160, 35160, 36696, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 40576, 42368, 42368, 43816, 43816, 45352, 45352, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 52752, 52752, 52752, 55056, 55056, 55056, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 61664, 63776, 63776, 63776, 66592, 66592, 66592, 68808, 68808, 68808, 71112, 71112, 71112, 71112, 73712, 73712, 73712, 73712, 76208, 76208, 76208, 78704, 78704, 78704, 78704},
   {776, 1544, 2344, 3112, 4008, 4776, 5544, 6200, 7224, 7992, 8760, 9528, 10296, 11064, 11832, 12576, 13536, 14112, 15264, 15840, 16416, 17568, 18336, 19080, 19848, 20616, 21384, 22152, 22920, 23688, 24496, 25456, 26416, 27376, 27376, 28336, 29296, 30576, 30576, 31704, 32856, 32856, 34008, 35160, 35160, 36696, 37888, 37888, 39232, 39232, 40576, 40576, 42368, 42368, 43816, 43816, 45352, 45352, 46888, 46888, 48936, 48936, 48936, 51024, 51024, 52752, 52752, 55056, 55056, 55056, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 63776, 63776, 63776, 66592, 66592, 66592, 68808, 68808, 68808, 71112, 71112, 71112, 73712, 73712, 73712, 76208, 76208, 76208, 76208, 78704, 78704, 78704, 81176, 81176, 81176, 81176, 84760, 84760, 84760, 84760, 87936, 87936},
   {840, 1736, 2600, 3496, 4264, 5160, 5992, 6968, 7736, 8504, 9528, 10296, 11064, 12216, 12960, 13536, 14688, 15264, 16416, 16992, 18336, 19080, 19848, 20616, 21384, 22152, 22920, 24496, 25456, 25456, 26416, 27376, 28336, 29296, 30576, 30576, 31704, 32856, 34008, 34008, 35160, 36696, 36696, 37888, 39232, 39232, 40576, 40576, 42368, 43816, 43816, 45352, 45352, 46888, 46888, 48936, 48936, 51024, 51024, 51024, 52752, 52752, 55056, 55056, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 61664, 63776, 63776, 66592, 66592, 66592, 68808, 68808, 68808, 71112, 71112, 71112, 73712, 73712, 73712, 76208, 76208, 76208, 78704, 78704, 78704, 81176, 81176, 81176, 81176, 84760, 84760, 84760, 87936, 87936, 87936, 87936, 90816, 90816, 90816, 93800, 93800, 93800, 93800},
   {904, 1864, 2792, 3752, 4584, 5544, 6456, 7480, 8248, 9144, 10296, 11064, 12216, 12960, 14112, 14688, 15840, 16992, 17568, 18336, 19848, 20616, 21384, 22152, 22920, 24496, 25456, 26416, 27376, 28336, 29296, 29296, 30576, 31704, 32856, 34008, 34008, 35160, 36696, 36696, 37888, 39232, 40576, 40576, 42368, 42368, 43816, 45352, 45352, 46888, 46888, 48936, 48936, 51024, 51024, 52752, 52752, 55056, 55056, 57336, 57336, 59256, 59256, 59256, 61664, 61664, 63776, 63776, 63776, 66592, 66592, 68808, 68808, 68808, 71112, 71112, 71112, 73712, 73712, 73712, 76208, 76208, 78704, 78704, 78704, 81176, 81176, 81176, 84760, 84760, 84760, 84760, 87936, 87936, 87936, 90816, 90816, 90816, 93800, 93800, 93800, 93800, 97896, 97896, 97896, 97896, 97896, 101840, 101840, 101840},
   {1000, 1992, 2984, 4008, 4968, 5992, 6968, 7992, 9144, 9912, 11064, 12216, 12960, 14112, 15264, 15840, 16992, 18336, 19080, 19848, 21384, 22152, 22920, 24496, 25456, 26416, 27376, 28336, 29296, 30576, 31704, 31704, 32856, 34008, 35160, 36696, 36696, 37888, 39232, 40576, 40576, 42368, 43816, 43816, 45352, 46888, 46888, 48936, 48936, 51024, 51024, 52752, 52752, 55056, 55056, 57336, 57336, 59256, 59256, 61664, 61664, 63776, 63776, 63776, 66592, 66592, 68808, 68808, 71112, 71112, 71112, 73712, 73712, 73712, 76208, 76208, 78704, 78704, 78704, 81176, 81176, 81176, 84760, 84760, 84760, 87936, 87936, 87936, 90816, 90816, 90816, 93800, 93800, 93800, 93800, 97896, 97896, 97896, 97896, 101840, 101840, 101840, 101840, 105528, 105528, 105528, 105528, 110136, 110136, 110136},
   {1064, 2152, 3240, 4264, 5352, 6456, 7480, 8504, 9528, 10680, 11832, 12960, 14112, 15264, 16416, 16992, 18336, 19080, 20616, 21384, 22920, 23688, 24496, 25456, 27376, 28336, 29296, 30576, 31704, 32856, 34008, 34008, 35160, 36696, 37888, 39232, 40576, 40576, 42368, 43816, 43816, 45352, 46888, 46888, 48936, 48936, 51024, 51024, 52752, 55056, 55056, 57336, 57336, 59256, 59256, 61664, 61664, 63776, 63776, 66592, 66592, 68808, 68808, 68808, 71112, 71112, 73712, 73712, 73712, 76208, 76208, 78704, 78704, 81176, 81176, 81176, 84760, 84760, 84760, 87936, 87936, 87936, 90816, 90816, 90816, 93800, 93800, 93800, 97896, 97896, 97896, 97896, 101840, 101840, 101840, 101840, 105528, 105528, 105528, 110136, 110136, 110136, 110136, 115040, 115040, 115040, 115040, 119816, 119816, 119816},
   {1128, 2280, 3496, 4584, 5736, 6968, 7992, 9144, 10296, 11448, 12576, 13536, 14688, 15840, 16992, 18336, 19848, 20616, 22152, 22920, 24496, 25456, 26416, 27376, 28336, 29296, 30576, 31704, 32856, 34008, 35160, 36696, 37888, 39232, 40576, 40576, 42368, 43816, 45352, 45352, 46888, 48936, 48936, 51024, 51024, 52752, 55056, 55056, 57336, 57336, 59256, 59256, 61664, 61664, 63776, 63776, 66592, 66592, 68808, 68808, 71112, 71112, 73712, 73712, 76208, 76208, 76208, 78704, 78704, 81176, 81176, 81176, 84760, 84760, 87936, 87936, 87936, 90816, 90816, 90816, 93800, 93800, 93800, 97896, 97896, 97896, 101840,101840,101840,101840,105528, 105528, 105528, 110136, 110136, 110136, 110136, 115040, 115040, 115040, 115040, 119816, 119816, 119816, 119816, 124464, 124464, 124464, 124464, 128496},
   {1192, 2408, 3624, 4968, 5992, 7224, 8504, 9912, 11064, 12216, 13536, 14688, 15840, 16992, 18336, 19848, 20616, 22152, 22920, 24496, 25456, 26416, 28336, 29296, 30576, 31704, 32856, 34008, 35160, 36696, 37888, 39232, 40576, 42368, 42368, 43816, 45352, 46888, 46888, 48936, 51024, 51024, 52752, 52752, 55056, 57336, 57336, 59256, 59256, 61664, 61664, 63776, 63776, 66592, 66592, 68808, 71112, 71112, 73712, 73712, 73712, 76208, 76208, 78704, 78704, 81176, 81176, 84760, 84760, 84760, 87936, 87936, 90816, 90816, 90816, 93800, 93800, 93800, 97896, 97896, 97896, 101840, 101840, 101840, 105528, 105528, 105528, 105528, 110136, 110136, 110136, 115040, 115040, 115040, 115040, 119816, 119816, 119816, 124464, 124464, 124464, 124464, 128496, 128496, 128496, 128496, 133208, 133208, 133208, 133208},
   {1256, 2536, 3752, 5160, 6200, 7480, 8760, 10296, 11448, 12576, 14112, 15264, 16416, 17568, 19080, 20616, 21384, 22920, 24496, 25456, 26416, 28336, 29296, 30576, 31704, 32856, 34008, 35160, 36696, 37888, 39232, 40576, 42368, 43816, 43816, 45352, 46888, 48936, 48936, 51024, 52752, 52752, 55056, 55056, 57336, 59256, 59256, 61664, 61664, 63776, 63776, 66592, 66592, 68808, 71112, 71112, 73712, 73712, 76208, 76208, 78704, 78704, 81176, 81176, 81176, 84760, 84760, 87936, 87936, 87936, 90816, 90816, 93800, 93800, 93800, 97896, 97896, 97896, 101840, 101840, 101840, 105528, 105528, 105528, 110136, 110136, 110136, 110136, 115040,115040, 115040, 119816, 119816, 119816, 124464, 124464, 124464, 124464, 128496, 128496, 128496, 128496, 133208, 133208, 133208, 133208, 137792, 137792, 137792, 142248},
   {1480, 2984, 4392, 5992, 7480, 8760, 10296, 11832, 13536, 14688, 16416, 17568, 19080, 20616, 22152, 23688, 25456, 26416, 28336, 29296, 30576, 32856, 34008, 35160, 36696, 37888, 40576, 40576, 42368, 43816, 45352, 46888, 48936, 51024, 52752, 52752, 55056, 55056, 57336, 59256, 59256, 61664, 63776, 63776, 66592, 68808, 68808, 71112, 73712, 75376, 75376, 75376, 75376, 75376, 75376, 81176, 84760, 84760, 87936, 87936, 90816, 90816, 93800, 93800, 97896, 97896, 97896, 101840, 101840, 105528, 105528, 105528, 110136, 110136, 110136, 110136, 115040, 115040, 115040, 119816, 119816, 119816, 124464, 124464, 124464, 128496, 128496, 128496, 133208, 133208, 133208, 137792, 137792, 137792, 142248, 142248, 142248, 146856, 146856,149776, 149776, 149776, 149776, 149776, 149776, 149776, 149776, 149776, 149776, 149776}
 }
};
RgSchUlIMcsTbl rgUlIMcsTbl = {
   {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5},
   {2, 6}, {2, 7}, {2, 8}, {2, 9}, {2, 10},
   {4, 10}, {4, 11}, {4, 12}, {4, 13}, {4, 14},
   {4, 15}, {4, 16}, {4, 17}, {4, 18}, {4, 19},
   {6, 19}, {6, 20}, {6, 21}, {6, 22}, {6, 23},
   {6, 24}, {6, 25}, {6, 26}
};
RgSchUeCatTbl rgUeCatTbl = {
   {5160, {10296,0}, 250368, 0, 10296, 1},
   {25456, {51024,0}, 1237248, 0, 51024, 2},
   {51024, {75376,0}, 1237248, 0, 102048, 2},
   {51024, {75376,0}, 1827072, 0, 150752, 2},
   {75376, {149776,0}, 3667200, 1, 299552, 4},
   {51024, {75376,149776}, 3654144, 0, 301504, 4},
   {51024, {75376,149776}, 3654144, 0, 301504, 4},
   {149776,{299856,0}, 35982720,1, 2998560, 8}
};




U8 rgSchCmnHarqRtt[8] = {4,7,10,9,12,15,6,8};

U8 rgSchCfiSwitchOvrWinLen[] = {7, 4, 2, 3, 2, 1, 6, 8};



RgSchCmnTbSzEff rgSchCmnNorCfi1Eff[2], rgSchCmnNorCfi2Eff[2];
RgSchCmnTbSzEff rgSchCmnNorCfi3Eff[2], rgSchCmnNorCfi4Eff[2];

RgSchCmnTbSzEff rgSchCmnNorUlEff[1],rgSchCmnExtUlEff[1];
RgSchCmnCqiToTbs rgSchCmnNorCfi1CqiToTbs[2], rgSchCmnNorCfi2CqiToTbs[2];
RgSchCmnCqiToTbs rgSchCmnNorCfi3CqiToTbs[2], rgSchCmnNorCfi4CqiToTbs[2];
RgSchCmnCqiToTbs *rgSchCmnCqiToTbs[2][2][4];
RgSchCmnTbSzEff rgSchCmnExtCfi1Eff[2], rgSchCmnExtCfi2Eff[2];
RgSchCmnTbSzEff rgSchCmnExtCfi3Eff[2], rgSchCmnExtCfi4Eff[2];
RgSchCmnCqiToTbs rgSchCmnExtCfi1CqiToTbs[2], rgSchCmnExtCfi2CqiToTbs[2];
RgSchCmnCqiToTbs rgSchCmnExtCfi3CqiToTbs[2], rgSchCmnExtCfi4CqiToTbs[2];

RgSchCmnTbSzEff *rgSchCmnEffTbl[2][2][3][4];
RgSchCmnTbSzEff *rgSchCmnUlEffTbl[2];




RgSchRaPrmblToRaFrmTbl rgRaPrmblToRaFrmTbl = {1, 2, 2, 3};


extern RgUlSchdInits rgSchUlSchdInits;
extern RgDlSchdInits rgSchDlSchdInits;
extern RgDlfsSchdInits rgSchDlfsSchdInits;


static S16 rgSCHCmnUeIdleExdThrsld ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
static RgSchUeCb* rgSCHCmnGetHoUe ( RgSchCellCb *cell, RgSchRaReqInfo *raReq )


  ;
static Void rgSCHCmnDelDedPreamble ( RgSchCellCb *cell, U8 preambleId )


  ;
static RgSchUeCb* rgSCHCmnGetPoUe ( RgSchCellCb *cell, RgSchRaReqInfo *raReq )


  ;
static Void rgSCHCmnDelRachInfo ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
static S16 rgSCHCmnUlRbAllocForPoHoUe ( RgSchCellCb *cell, RgSchUlSf *sf, RgSchUeCb *ue, U8 maxRb )




  ;
static Void rgSCHCmnHdlHoPo ( RgSchCellCb *cell, CmLListCp *raRspLst, RgSchRaReqInfo *raReq )



  ;
static Void rgSCHCmnAllocPoHoGrnt ( RgSchCellCb *cell, CmLListCp *raRspLst, RgSchUeCb *ue, RgSchRaReqInfo *raReq )




  ;
static Void rgSCHCmnFillPdcchOdr2Sf ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchPdcch *pdcc, U8 rapId, U8 prachMskIdx )





  ;
static Void rgSCHCmnDlAdd2PdcchOdrQ ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
static Void rgSCHCmnDlRmvFrmPdcchOdrQ ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
static Void rgSCHCmnUpdNxtPrchMskIdx ( RgSchCellCb *cell )

  ;
static Void rgSCHCmnUpdRachParam ( RgSchCellCb *cell )

  ;
static S16 rgSCHCmnAllocPOParam ( RgSchCellCb *cell, RgSchDlSf *dlSf, RgSchUeCb *ue, RgSchPdcch **pdcch, U8 *rapId, U8 *prachMskIdx )






  ;
static Void rgSCHCmnGenPdcchOrder ( RgSchCellCb *cell, RgSchDlSf *dlSf )


  ;
static Void rgSCHCmnCfgRachDedPrm ( RgSchCellCb *cell )

  ;


static Void rgSCHCmnHdlUlInactUes ( RgSchCellCb *cell )

  ;
static Void rgSCHCmnHdlDlInactUes ( RgSchCellCb *cell )

  ;
static Void rgSCHCmnUlInit (Void )
  ;
static Void rgSCHCmnDlInit (Void )
  ;
static Void rgSCHCmnInitUlRbAllocInfo ( RgSchCmnUlRbAllocInfo *allocInfo )

  ;
static Void rgSCHCmnInitDlRbAllocInfo ( RgSchCmnDlRbAllocInfo *allocInfo )

  ;
static Void rgSCHCmnUpdUlCompEffBsr ( RgSchUeCb *ue )

  ;
static Void rgSCHCmnGrpPwrCntrlPucch ( RgSchCellCb *cell, RgSchDlSf *dlSf )


  ;
static Void rgSCHCmnGrpPwrCntrlPusch ( RgSchCellCb *cell, RgSchUlSf *ulSf )


  ;
static Void rgSCHCmnDelUeFrmRefreshQ ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
static S16 rgSCHCmnTmrExpiry ( U32 cb, S16 tmrEvnt )


  ;
static S16 rgSCHCmnTmrProc ( RgSchCellCb *cell )

  ;
static Void rgSCHCmnAddUeToRefreshQ ( RgSchCellCb *cell, RgSchUeCb *ue, U32 wait )



  ;
static Void rgSCHCmnDlCcchRetx ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static Void rgSCHCmnUpdUeMimoInfo ( RgrUeCfg *ueCfg, RgSchCmnDlUe *ueDl, RgSchCellCb *cell, RgSchCmnCell *cellSchd )




  ;
static Void rgSCHCmnUpdUeUlCqiInfo ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchCmnUlUe *ueUl, RgSchCmnUe *ueSchCmn, RgSchCmnCell *cellSchd, Bool isEcp )






  ;

static Void rgSCHCmnDlCcchSduRetx ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static Void rgSCHCmnDlCcchSduTx ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static S16 rgSCHCmnCcchSduAlloc ( RgSchCellCb *cell, RgSchUeCb *ueCb, RgSchCmnDlRbAllocInfo *allocInfo )



  ;
static S16 rgSCHCmnCcchSduDedAlloc ( RgSchCellCb *cell, RgSchUeCb *ueCb )


  ;
static S16 rgSCHCmnNonDlfsCcchSduRbAlloc ( RgSchCellCb *cell, RgSchUeCb *ueCb, RgSchDlSf *dlSf )



  ;

static Void rgSCHCmnInitVars ( RgSchCellCb *cell )

           ;


static Void rgSCHCmnUlRbAllocForLst ( RgSchCellCb *cell, RgSchUlSf *sf, U32 count, CmLListCp *reqLst, CmLListCp *schdLst, CmLListCp *nonSchdLst, Bool isNewTx )







           ;
static S16 rgSCHCmnUlRbAllocForUe ( RgSchCellCb *cell, RgSchUlSf *sf, RgSchUeCb *ue, U8 maxRb, RgSchUlHole *hole )





           ;
static Void rgSCHCmnMsg3GrntReq ( RgSchCellCb *cell, CmLteRnti rnti, Bool preamGrpA, RgSchUlHqProcCb *hqProc, RgSchUlAlloc **ulAllocRef, U8 *hqProcIdRef )






           ;
static Void rgSCHCmnUlNonadapRetx ( RgSchCmnUlCell *cellUl, RgSchUlAlloc *alloc, U8 idx )



           ;

static Void rgSCHCmnDlCcchRarAlloc ( RgSchCellCb *cell )

  ;
static Void rgSCHCmnDlCcchTx ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static Void rgSCHCmnDlBcchPcch ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo, RgInfSfAlloc *subfrmAlloc )



  ;
static Bool rgSCHCmnChkInWin ( CmLteTimingInfo frm, CmLteTimingInfo start, CmLteTimingInfo end )



  ;
static Bool rgSCHCmnChkPastWin ( CmLteTimingInfo frm, CmLteTimingInfo end )


  ;
static Void rgSCHCmnClcAlloc ( RgSchCellCb *cell, RgSchDlSf *sf, RgSchClcDlLcCb *lch, U16 rnti, RgSchCmnDlRbAllocInfo *allocInfo )





  ;
static S16 rgSCHCmnMsg4Alloc ( RgSchCellCb *cell, RgSchRaCb *raCb, RgSchCmnDlRbAllocInfo *allocInfo )



  ;
static S16 rgSCHCmnMsg4DedAlloc ( RgSchCellCb *cell, RgSchRaCb *raCb )


  ;
static Void rgSCHCmnDlRaRsp ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static S16 rgSCHCmnRaRspAlloc ( RgSchCellCb *cell, RgSchDlSf *subFrm, U16 rntiIdx, U16 rarnti, U8 noRaRnti, RgSchCmnDlRbAllocInfo *allocInfo )






  ;
static Void rgSCHCmnUlUeDelAllocs ( RgSchCellCb *cell, RgSchUeCb *ue )


  ;
static Void rgSCHCmnDlSetUeAllocLmt ( RgSchCellCb *cell, RgSchCmnDlUe *ueDl )


  ;
static S16 rgSCHCmnDlRgrCellCfg ( RgSchCellCb *cell, RgrCellCfg *cfg, RgSchErrInfo *err )



  ;
static Void rgSCHCmnUlAdapRetx ( RgSchUlAlloc *alloc, RgSchUlHqProcCb *proc )


  ;
static Void rgSCHCmnUlUpdAllocRetx ( RgSchUlSf *reTxSf, RgSchUlAlloc *alloc )


  ;
static Void rgSCHCmnUlSfReTxAllocs ( RgSchCellCb *cell, RgSchUlSf *sf )


  ;

static Void rgSCHCmnUlSfRlsRetxProcs ( RgSchCellCb *cell, RgSchUlSf *sf )


  ;


static Void rgSCHCmnDlHdlTxModeRecfg ( RgSchCellCb *cell, RgSchUeCb *ue, RgrUeRecfg *ueRecfg, U8 numTxPorts )





  ;
static Void rgSCHCmnDlRbAlloc ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static Void rgSCHCmnNonDlfsRbAlloc ( RgSchCellCb *cell, RgSchCmnDlRbAllocInfo *allocInfo )


  ;
static S16 rgSCHCmnNonDlfsCmnRbAlloc ( RgSchCellCb *cell, RgSchDlRbAlloc *cmnAllocInfo)

                                     ;


static Void rgSCHCmnNonDlfsPbchRbAllocAdj ( RgSchCellCb *cell, RgSchDlRbAlloc *cmnAllocInfo, U8 pbchSsRsSym, Bool isBcchPcch )




  ;

static Void rgSCHCmnNonDlfsPbchTbSizeAdj ( RgSchDlRbAlloc *allocInfo, U8 numOvrlapgPbchRb, U8 pbchSsRsSym, U8 idx, U32 bytesReq )





  ;


static Void rgSCHCmnFindNumPbchOvrlapRbs ( RgSchCellCb *cell, RgSchDlSf *dlSf, RgSchDlRbAlloc *allocInfo, U8 *numOvrlapgPbchRb )




  ;

static U8 rgSCHCmnFindNumAddtlRbsAvl ( RgSchCellCb *cell, RgSchDlSf *dlSf, RgSchDlRbAlloc *allocInfo )



  ;

static Void rgSCHCmnFindCodeRate ( RgSchCellCb *cell, RgSchDlSf *dlSf, RgSchDlRbAlloc *allocInfo, U8 idx )




  ;


static Void rgSCHCmnNonDlfsMsg4Alloc ( RgSchCellCb *cell, RgSchCmnMsg4RbAlloc *msg4AllocInfo, U8 isRetx )



  ;
static S16 rgSCHCmnNonDlfsMsg4RbAlloc ( RgSchCellCb *cell, RgSchRaCb *raCb, RgSchDlSf *dlSf )



  ;
static Void rgSCHCmnNonDlfsDedRbAlloc ( RgSchCellCb *cell, RgSchCmnUeRbAlloc *allocInfo, CmLListCp *ueLst, CmLListCp *schdUeLst, CmLListCp *nonSchdUeLst )





  ;
static S16 rgSCHCmnNonDlfsUeRbAlloc ( RgSchCellCb *cell, RgSchUeCb *ue, RgSchDlSf *dlSf, U8 *isDlBwAvail )




  ;
static Void rgSCHCmnFindUlCqiUlTxAnt ( RgSchCellCb *cell, RgSchUeCb *ue, U8 wideCqi )




   ;
 static RgSchCmnRank rgSCHCmnComputeRank ( RgrTxMode txMode, U32 *pmiBitMap, U8 numTxPorts )




   ;

 static RgSchCmnRank rgSCHCmnComp2TxMode3 ( U32 *pmiBitMap )


   ;

  static RgSchCmnRank rgSCHCmnComp4TxMode3 ( U32 *pmiBitMap )


   ;

  static RgSchCmnRank rgSCHCmnComp2TxMode4 ( U32 *pmiBitMap )


   ;

  static RgSchCmnRank rgSCHCmnComp4TxMode4 ( U32 *pmiBitMap )


   ;

 static U8 rgSCHCmnCalcWcqiFrmSnr ( RgSchCellCb *cell, TfuSrsRpt *srsRpt )



   ;
static Void rgSCHCmnCompEff
(
U8 noPdcchSym,
U8 cpType,
U8 txAntIdx,
RgSchCmnTbSzEff *effTbl
)







{
   U8 noResPerRb;
   U8 noSymPerRb;
   U8 resOfCrs;
   U8 i, j;

   ;;

   switch (cpType)
   {
      case 0:
         noSymPerRb = 14;
         break;
      case 1:
         noSymPerRb = 12;
         break;
      default:

         return;
   }



   switch (txAntIdx)
   {
      case 0:
         resOfCrs = 6;
         break;
      case 1:
         resOfCrs = 12;
         break;
      case 2:
         resOfCrs = 16;
         break;
      default:

         return;
   }
   noResPerRb = ((noSymPerRb - noPdcchSym) * 12) - resOfCrs;
   for (i = 0; i < 27; i++)
   {
      (*effTbl)[i] = 0;
      for (j = 0; j < 110; j++)
      {

         (*effTbl)[i] += (rgTbSzTbl[0][i][j] * 1024) / (noResPerRb * (j+1));
      }
      (*effTbl)[i] /= 110;
   }
   return;
}
static Void rgSCHCmnCompUlEff
(
U8 noUlRsSym,
U8 cpType,
RgSchCmnTbSzEff *effTbl
)






{
   U8 noResPerRb;
   U8 noSymPerRb;
   U8 i, j;

   ;;

   switch (cpType)
   {
      case 0:
         noSymPerRb = 14;
         break;
      case 1:
         noSymPerRb = 12;
         break;
      default:

         return;
   }

   noResPerRb = ((noSymPerRb - noUlRsSym) * 12);
   for (i = 0; i < 27; i++)
   {
      (*effTbl)[i] = 0;
      for (j = 0; j < 110; j++)
      {

         (*effTbl)[i] += (rgTbSzTbl[0][i][j] * 1024) / (noResPerRb * (j+1));
      }
      (*effTbl)[i] /= 110;
   }
   return;
}
static Void rgSCHCmn2LyrCompEff
(
U8 noPdcchSym,
U8 cpType,
U8 txAntIdx,
RgSchCmnTbSzEff *effTbl2Lyr
)







{
   U8 noResPerRb;
   U8 noSymPerRb;
   U8 resOfCrs;
   U8 i, j;

   ;;

   switch (cpType)
   {
      case 0:
         noSymPerRb = 14;
         break;
      case 1:
         noSymPerRb = 12;
         break;
      default:

         return;
   }



   switch (txAntIdx)
   {
      case 0:
         resOfCrs = 6;
         break;
      case 1:
         resOfCrs = 12;
         break;
      case 2:
         resOfCrs = 16;
         break;
      default:

         return;
   }

   noResPerRb = ((noSymPerRb - noPdcchSym) * 12) - resOfCrs;
   for (i = 0; i < 27; i++)
   {
      (*effTbl2Lyr)[i] = 0;
      for (j = 0; j < 110; j++)
      {

         (*effTbl2Lyr)[i] += (rgTbSzTbl[1][i][j] * 1024) / (noResPerRb * (j+1));
      }
      (*effTbl2Lyr)[i] /= 110;
   }
   return;
}
static Void rgSCHCmnGetDciFrmtSizes
(
RgSchCellCb *cell
)




{

   ;;


   rgSchCmnDciFrmtSizes[0] = 1 +
                             1 +
                             rgSCHUtlLog32bitNbase2((cell->bwCfg.ulTotalBw *
                             (cell->bwCfg.ulTotalBw + 1))/2) +
                             5 +
                             1 +
                             2 +
                             3 +




                             1;

   rgSchCmnDciFrmtSizes[1] = 1 +
   (((cell->bwCfg.dlTotalBw) + (cell->rbgSize)-1) / (cell->rbgSize)) +
                             5 +

                             3 +



                             1 +
                             2 +
                             2;


   rgSchCmnDciFrmtSizes[2] = 1 +
               1 +
               5 +

               3 +




               1 +
               2 +
               2 +
               1 + rgSCHUtlLog32bitNbase2((cell->bwCfg.dlTotalBw *
                   (cell->bwCfg.dlTotalBw + 1))/2);




   rgSchCmnDciFrmtSizes[3] = 1 +
                             rgSCHUtlLog32bitNbase2((cell->bwCfg.dlTotalBw *
                             (cell->bwCfg.dlTotalBw + 1))/2) +
                             5 +
                             3 +




                             1 +
                             2 +
                             2 +
                             ((cell->numTxAntPorts == 4)? 4:2) +
                             1;



   rgSchCmnDciFrmtSizes[4] = (cell->bwCfg.dlTotalBw < 50)? 0:1 +
                             (cell->bwCfg.dlTotalBw < 50)?
                             (rgSCHUtlLog32bitNbase2((cell->bwCfg.dlTotalBw/2 *
                                (cell->bwCfg.dlTotalBw/2 + 1))/2)) :
                             (rgSCHUtlLog32bitNbase2((cell->bwCfg.dlTotalBw/4 *
                                (cell->bwCfg.dlTotalBw/4 + 1))/2)) +
                             5;


   rgSchCmnDciFrmtSizes[5] = 1 +
                             rgSCHUtlLog32bitNbase2((cell->bwCfg.dlTotalBw *
                             (cell->bwCfg.dlTotalBw + 1))/2) +
                             5 +
                             3 +



                             1 +
                             2 +
                             2 +
                             ((cell->numTxAntPorts == 4)? 4:2) +
                             1;


   rgSchCmnDciFrmtSizes[6] = ((cell->bwCfg.dlTotalBw < 10)?0:1) +
                             (((cell->bwCfg.dlTotalBw) + (cell->rbgSize)-1) / (cell->rbgSize)) +
                             2 +



                             3 +
                             1 +
                             (5 + 1 + 2)*2 +
                             ((cell->numTxAntPorts == 4)? 6:3);


   rgSchCmnDciFrmtSizes[7] = ((cell->bwCfg.dlTotalBw < 10)?0:1) +
                             (((cell->bwCfg.dlTotalBw) + (cell->rbgSize)-1) / (cell->rbgSize)) +
                             2 +



                             3 +
                             1 +
                             (5 + 1 + 2)*2 +
                             ((cell->numTxAntPorts == 4)? 2:0);


   rgSchCmnDciFrmtSizes[8] = rgSchCmnDciFrmtSizes[0];


   rgSchCmnDciFrmtSizes[9] = rgSchCmnDciFrmtSizes[0];

   return;
}
static Void rgSCHCmnGetCqiDciFrmt2AggrLvl
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U8 i;
   U8 j;

   ;;

   for (i = 0; i < 16; i++)
   {
      for (j = 0; j < 10; j++)
      {
         U32 pdcchBits;

         pdcchBits = (rgSchCmnDciFrmtSizes[j] * 1024)/rgSchCmnCqiPdcchEff[i];
         if (pdcchBits < 72)
         {
             if(j == 0)
             {
               cellSch->dciAggrLvl[i][j] = CM_LTE_AGGR_LVL1;
             }
             else
             {
               cellSch->dciAggrLvl[i][j] = CM_LTE_AGGR_LVL2;
             }
             continue;
         }
         if (pdcchBits < 144)
         {
             cellSch->dciAggrLvl[i][j] = CM_LTE_AGGR_LVL2;
             continue;
         }
         if (pdcchBits < 288)
         {
             cellSch->dciAggrLvl[i][j] = CM_LTE_AGGR_LVL4;
             continue;
         }
         cellSch->dciAggrLvl[i][j] = CM_LTE_AGGR_LVL8;
      }
   }
   return;
}
static Void rgSCHCmnDlInit
(
)



{
   U8 i;
   S16 j;
   S16 k;
   U8 idx;
   RgSchCmnTbSzEff *effTbl;
   RgSchCmnCqiToTbs *tbsTbl;

   ;;







   rgSchCmnEffTbl[0][0][0][0] = &rgSchCmnNorCfi1Eff[0];
   rgSchCmnEffTbl[0][0][0][1] = &rgSchCmnNorCfi2Eff[0];
   rgSchCmnEffTbl[0][0][0][2] = &rgSchCmnNorCfi3Eff[0];
   rgSchCmnEffTbl[0][0][0][3] = &rgSchCmnNorCfi4Eff[0];

   rgSchCmnEffTbl[0][0][1][0] = &rgSchCmnNorCfi1Eff[0];
   rgSchCmnEffTbl[0][0][1][1] = &rgSchCmnNorCfi2Eff[0];
   rgSchCmnEffTbl[0][0][1][2] = &rgSchCmnNorCfi3Eff[0];
   rgSchCmnEffTbl[0][0][1][3] = &rgSchCmnNorCfi4Eff[0];

   rgSchCmnEffTbl[0][0][2][0] = &rgSchCmnNorCfi1Eff[0];
   rgSchCmnEffTbl[0][0][2][1] = &rgSchCmnNorCfi2Eff[0];
   rgSchCmnEffTbl[0][0][2][2] = &rgSchCmnNorCfi3Eff[0];
   rgSchCmnEffTbl[0][0][2][3] = &rgSchCmnNorCfi4Eff[0];


   rgSchCmnCqiToTbs[0][0][0] = &rgSchCmnNorCfi1CqiToTbs[0];
   rgSchCmnCqiToTbs[0][0][1] = &rgSchCmnNorCfi2CqiToTbs[0];
   rgSchCmnCqiToTbs[0][0][2] = &rgSchCmnNorCfi3CqiToTbs[0];
   rgSchCmnCqiToTbs[0][0][3] = &rgSchCmnNorCfi4CqiToTbs[0];





   rgSchCmnEffTbl[1][0][0][0] = &rgSchCmnNorCfi1Eff[1];
   rgSchCmnEffTbl[1][0][0][1] = &rgSchCmnNorCfi2Eff[1];
   rgSchCmnEffTbl[1][0][0][2] = &rgSchCmnNorCfi3Eff[1];
   rgSchCmnEffTbl[1][0][0][3] = &rgSchCmnNorCfi4Eff[1];

   rgSchCmnEffTbl[1][0][1][0] = &rgSchCmnNorCfi1Eff[1];
   rgSchCmnEffTbl[1][0][1][1] = &rgSchCmnNorCfi2Eff[1];
   rgSchCmnEffTbl[1][0][1][2] = &rgSchCmnNorCfi3Eff[1];
   rgSchCmnEffTbl[1][0][1][3] = &rgSchCmnNorCfi4Eff[1];

   rgSchCmnEffTbl[1][0][2][0] = &rgSchCmnNorCfi1Eff[1];
   rgSchCmnEffTbl[1][0][2][1] = &rgSchCmnNorCfi2Eff[1];
   rgSchCmnEffTbl[1][0][2][2] = &rgSchCmnNorCfi3Eff[1];
   rgSchCmnEffTbl[1][0][2][3] = &rgSchCmnNorCfi4Eff[1];


   rgSchCmnCqiToTbs[1][0][0] = &rgSchCmnNorCfi1CqiToTbs[1];
   rgSchCmnCqiToTbs[1][0][1] = &rgSchCmnNorCfi2CqiToTbs[1];
   rgSchCmnCqiToTbs[1][0][2] = &rgSchCmnNorCfi3CqiToTbs[1];
   rgSchCmnCqiToTbs[1][0][3] = &rgSchCmnNorCfi4CqiToTbs[1];

   for (idx = 0; idx < 3; idx++)
   {
      for (i = 0; i < 4; i++)
      {

         rgSCHCmnCompEff((U8)(i + 1), 0, idx,
               rgSchCmnEffTbl[0][0][idx][i]);
         rgSCHCmn2LyrCompEff((U8)(i + 1), 0, idx,
               rgSchCmnEffTbl[1][0][idx][i]);
      }
   }

   for (idx = 0; idx < 3; idx++)
   {
      for (i = 0; i < 4; i++)
      {
         effTbl = rgSchCmnEffTbl[0][0][idx][i];
         tbsTbl = rgSchCmnCqiToTbs[0][0][i];
         for (j = 27 - 1, k = 16 - 1;
               (j >= 0) && (k > 0); --j)
         {


            if ((*effTbl)[j] <= rgSchCmnCqiPdschEff[i][k])
            {
               (*tbsTbl)[k--] = (U8)j;
            }
         }
         for (; k > 0; --k)
         {
            (*tbsTbl)[k] = 0;
         }

         effTbl = rgSchCmnEffTbl[1][0][idx][i];
         tbsTbl = rgSchCmnCqiToTbs[1][0][i];
         for (j = 27 - 1, k = 16 - 1;
               (j >= 0) && (k > 0); --j)
         {


            if ((*effTbl)[j] <= rgSchCmn2LyrCqiPdschEff[i][k])
            {
               (*tbsTbl)[k--] = (U8)j;
            }
         }
         for (; k > 0; --k)
         {
            (*tbsTbl)[k] = 0;
         }
      }
   }






   rgSchCmnEffTbl[0][1][0][0] = &rgSchCmnExtCfi1Eff[0];
   rgSchCmnEffTbl[0][1][0][1] = &rgSchCmnExtCfi2Eff[0];
   rgSchCmnEffTbl[0][1][0][2] = &rgSchCmnExtCfi3Eff[0];
   rgSchCmnEffTbl[0][1][0][3] = &rgSchCmnExtCfi4Eff[0];

   rgSchCmnEffTbl[0][1][1][0] = &rgSchCmnExtCfi1Eff[0];
   rgSchCmnEffTbl[0][1][1][1] = &rgSchCmnExtCfi2Eff[0];
   rgSchCmnEffTbl[0][1][1][2] = &rgSchCmnExtCfi3Eff[0];
   rgSchCmnEffTbl[0][1][1][3] = &rgSchCmnExtCfi4Eff[0];

   rgSchCmnEffTbl[0][1][2][0] = &rgSchCmnExtCfi1Eff[0];
   rgSchCmnEffTbl[0][1][2][1] = &rgSchCmnExtCfi2Eff[0];
   rgSchCmnEffTbl[0][1][2][2] = &rgSchCmnExtCfi3Eff[0];
   rgSchCmnEffTbl[0][1][2][3] = &rgSchCmnExtCfi4Eff[0];


   rgSchCmnCqiToTbs[0][1][0] = &rgSchCmnExtCfi1CqiToTbs[0];
   rgSchCmnCqiToTbs[0][1][1] = &rgSchCmnExtCfi2CqiToTbs[0];
   rgSchCmnCqiToTbs[0][1][2] = &rgSchCmnExtCfi3CqiToTbs[0];
   rgSchCmnCqiToTbs[0][1][3] = &rgSchCmnExtCfi4CqiToTbs[0];





   rgSchCmnEffTbl[1][1][0][0] = &rgSchCmnExtCfi1Eff[1];
   rgSchCmnEffTbl[1][1][0][1] = &rgSchCmnExtCfi2Eff[1];
   rgSchCmnEffTbl[1][1][0][2] = &rgSchCmnExtCfi3Eff[1];
   rgSchCmnEffTbl[1][1][0][3] = &rgSchCmnExtCfi4Eff[1];

   rgSchCmnEffTbl[1][1][1][0] = &rgSchCmnExtCfi1Eff[1];
   rgSchCmnEffTbl[1][1][1][1] = &rgSchCmnExtCfi2Eff[1];
   rgSchCmnEffTbl[1][1][1][2] = &rgSchCmnExtCfi3Eff[1];
   rgSchCmnEffTbl[1][1][1][3] = &rgSchCmnExtCfi4Eff[1];

   rgSchCmnEffTbl[1][1][2][0] = &rgSchCmnExtCfi1Eff[1];
   rgSchCmnEffTbl[1][1][2][1] = &rgSchCmnExtCfi2Eff[1];
   rgSchCmnEffTbl[1][1][2][2] = &rgSchCmnExtCfi3Eff[1];
   rgSchCmnEffTbl[1][1][2][3] = &rgSchCmnExtCfi4Eff[1];


   rgSchCmnCqiToTbs[1][1][0] = &rgSchCmnExtCfi1CqiToTbs[1];
   rgSchCmnCqiToTbs[1][1][1] = &rgSchCmnExtCfi2CqiToTbs[1];
   rgSchCmnCqiToTbs[1][1][2] = &rgSchCmnExtCfi3CqiToTbs[1];
   rgSchCmnCqiToTbs[1][1][3] = &rgSchCmnExtCfi4CqiToTbs[1];

   for (idx = 0; idx < 3; idx++)
   {
      for (i = 0; i < 4; i++)
      {

         rgSCHCmnCompEff( (U8)(i + 1 ), (U8)1, idx,
               rgSchCmnEffTbl[0][1][idx][i]);
         rgSCHCmn2LyrCompEff((U8)(i + 1), (U8) 1,idx,
               rgSchCmnEffTbl[1][1][idx][i]);
      }
   }

   for (idx = 0; idx < 3; idx++)
   {
      for (i = 0; i < 4; i++)
      {
         effTbl = rgSchCmnEffTbl[0][1][idx][i];
         tbsTbl = rgSchCmnCqiToTbs[0][1][i];
         for (j = 27 - 1, k = 16 - 1;
               (j >= 0) && (k > 0); --j)
         {


            if ((*effTbl)[j] <= rgSchCmnCqiPdschEff[i][k])
            {
               (*tbsTbl)[k--] = (U8)j;
            }
         }
         for (; k > 0; --k)
         {
            (*tbsTbl)[k] = 0;
         }

         effTbl = rgSchCmnEffTbl[1][1][idx][i];
         tbsTbl = rgSchCmnCqiToTbs[1][1][i];
         for (j = 27 - 1, k = 16 - 1;
               (j >= 0) && (k > 0); --j)
         {


            if ((*effTbl)[j] <= rgSchCmn2LyrCqiPdschEff[i][k])
            {
               (*tbsTbl)[k--] = (U8)j;
            }
         }
         for (; k > 0; --k)
         {
            (*tbsTbl)[k] = 0;
         }
      }
   }
   return;
}
static Void rgSCHCmnUlInit
(
)



{
   U8 *mapTbl = &rgSchCmnUlCqiToTbsTbl[0][0];
   RgSchCmnTbSzEff *effTbl = &rgSchCmnNorUlEff[0];
   const RgSchCmnUlCqiInfo *cqiTbl = &rgSchCmnUlCqiTbl[0];
   S16 i;
   S16 j;
   ;;


   rgSchCmnUlEffTbl[0] = &rgSchCmnNorUlEff[0];



   rgSCHCmnCompUlEff(2,0,rgSchCmnUlEffTbl[0]);

   for (i = 27 - 1, j = 16 - 1;
         i >= 0 && j > 0; --i)
   {
      if ((*effTbl)[i] <= cqiTbl[j].eff)
      {
         mapTbl[j--] = (U8)i;
      }
   }
   for (; j > 0; --j)
   {
      mapTbl[j] = 0;
   }
   effTbl = &rgSchCmnExtUlEff[0];
   mapTbl = &rgSchCmnUlCqiToTbsTbl[1][0];


   rgSchCmnUlEffTbl[1] = &rgSchCmnExtUlEff[0];



   rgSCHCmnCompUlEff(3,1,rgSchCmnUlEffTbl[1]);

   for (i = 27 - 1, j = 16 - 1;
         i >= 0 && j > 0; --i)
   {
      if ((*effTbl)[i] <= cqiTbl[j].eff)
      {
         mapTbl[j--] = (U8)i;
      }
   }
   for (; j > 0; --j)
   {
      mapTbl[j] = 0;
   }
   rgSCHPwrInit();
   return;
}
 Void rgSCHCmnInit
(
)



{
   U8 idx;
   ;;

   rgSCHCmnDlInit();
   rgSCHCmnUlInit();

   rgSCHCmnSpsInit();



   rgSchCmnApis.rgSCHRgrUeCfg = rgSCHCmnRgrUeCfg;
   rgSchCmnApis.rgSCHRgrUeRecfg = rgSCHCmnRgrUeRecfg;
   rgSchCmnApis.rgSCHFreeUe = rgSCHCmnUeDel;
   rgSchCmnApis.rgSCHRgrCellCfg = rgSCHCmnRgrCellCfg;
   rgSchCmnApis.rgSCHRgrCellRecfg = rgSCHCmnRgrCellRecfg;
   rgSchCmnApis.rgSCHFreeCell = rgSCHCmnCellDel;
   rgSchCmnApis.rgSCHRgrLchCfg = rgSCHCmnRgrLchCfg;
   rgSchCmnApis.rgSCHRgrLcgCfg = rgSCHCmnRgrLcgCfg;
   rgSchCmnApis.rgSCHRgrLchRecfg = rgSCHCmnRgrLchRecfg;
   rgSchCmnApis.rgSCHRgrLcgRecfg = rgSCHCmnRgrLcgRecfg;
   rgSchCmnApis.rgSCHFreeDlLc = rgSCHCmnFreeDlLc;
   rgSchCmnApis.rgSCHFreeLcg = rgSCHCmnLcgDel;
   rgSchCmnApis.rgSCHRgrLchDel = rgSCHCmnRgrLchDel;
   rgSchCmnApis.rgSCHActvtUlUe = rgSCHCmnActvtUlUe;
   rgSchCmnApis.rgSCHActvtDlUe = rgSCHCmnActvtDlUe;
   rgSchCmnApis.rgSCHHdlUlTransInd = rgSCHCmnHdlUlTransInd;
   rgSchCmnApis.rgSCHDlDedBoUpd = rgSCHCmnDlDedBoUpd;
   rgSchCmnApis.rgSCHUlRecMsg3Alloc = rgSCHCmnUlRecMsg3Alloc;
   rgSchCmnApis.rgSCHUlCqiInd = rgSCHCmnUlCqiInd;
   rgSchCmnApis.rgSCHPucchDeltaPwrInd = rgSCHPwrPucchDeltaInd;
   rgSchCmnApis.rgSCHUlHqProcForUe = rgSCHCmnUlHqProcForUe;



   rgSchCmnApis.rgSCHUpdBsrShort = rgSCHCmnUpdBsrShort;
   rgSchCmnApis.rgSCHUpdBsrTrunc = rgSCHCmnUpdBsrTrunc;
   rgSchCmnApis.rgSCHUpdBsrLong = rgSCHCmnUpdBsrLong;
   rgSchCmnApis.rgSCHUpdPhr = rgSCHCmnUpdPhr;
   rgSchCmnApis.rgSCHUpdExtPhr = rgSCHCmnUpdExtPhr;
   rgSchCmnApis.rgSCHContResUlGrant = rgSCHCmnContResUlGrant;
   rgSchCmnApis.rgSCHSrRcvd = rgSCHCmnSrRcvd;
   rgSchCmnApis.rgSCHFirstRcptnReq = rgSCHCmnFirstRcptnReq;
   rgSchCmnApis.rgSCHNextRcptnReq = rgSCHCmnNextRcptnReq;
   rgSchCmnApis.rgSCHFirstHqFdbkAlloc = rgSCHCmnFirstHqFdbkAlloc;
   rgSchCmnApis.rgSCHNextHqFdbkAlloc = rgSCHCmnNextHqFdbkAlloc;
   rgSchCmnApis.rgSCHDlProcAddToRetx = rgSCHCmnDlProcAddToRetx;
   rgSchCmnApis.rgSCHDlCqiInd = rgSCHCmnDlCqiInd;

   rgSchCmnApis.rgSCHSrsInd = rgSCHCmnSrsInd;

   rgSchCmnApis.rgSCHDlTARpt = rgSCHCmnDlTARpt;
   rgSchCmnApis.rgSCHDlRlsSubFrm = rgSCHCmnDlRlsSubFrm;
   rgSchCmnApis.rgSCHUeReset = rgSCHCmnUeReset;

   rgSchCmnApis.rgSCHHdlCrntiCE = rgSCHCmnHdlCrntiCE;
   rgSchCmnApis.rgSCHDlProcAck = rgSCHCmnDlProcAck;
   rgSchCmnApis.rgSCHDlRelPdcchFbk = rgSCHCmnDlRelPdcchFbk;
   rgSchCmnApis.rgSCHUlSpsRelInd = rgSCHCmnUlSpsRelInd;
   rgSchCmnApis.rgSCHUlSpsActInd = rgSCHCmnUlSpsActInd;
   rgSchCmnApis.rgSCHUlCrcFailInd = rgSCHCmnUlCrcFailInd;
   rgSchCmnApis.rgSCHUlCrcInd = rgSCHCmnUlCrcInd;

   rgSchCmnApis.rgSCHDrxStrtInActvTmrInUl = rgSCHCmnDrxStrtInActvTmrInUl;
   rgSchCmnApis.rgSCHUpdUeDataIndLcg = rgSCHCmnUpdUeDataIndLcg;

   for (idx = 0; idx < 4; ++idx)
   {
      rgSchUlSchdInits[idx](&rgSchUlSchdTbl[idx]);
      rgSchDlSchdInits[idx](&rgSchDlSchdTbl[idx]);
   }


   for (idx = 0; idx < 1; ++idx)
   {
      rgSchDlfsSchdInits[idx](&rgSchDlfsSchdTbl[idx]);
   }





   return;
}
 Void rgSCHCmnDlRlsSubFrm
(
RgSchCellCb *cell,
CmLteTimingInfo frm
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchDlSf *sf;

   ;;


   sf = rgSCHUtlSubFrmGet(cell, frm);

   rgSCHUtlSubFrmPut(cell, sf);
   if (sf->dlfsSf)
   {

      cellSch->apisDlfs->rgSCHDlfsReinitSf(cell, sf);
   }
   return;
}
static Void rgSCHCmnDlCcchRarAlloc
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;

   rgSCHCmnDlCcchRetx(cell, &cellSch->allocInfo);

   if(RG_SCH_ABS_ENABLED_ABS_SF == cell->lteAdvCb.absDlSfInfo)
   {
      if(cell->lteAdvCb.absCfg.absPatternType & RGR_ABS_MUTE)
      {

      }
      else
      {
         rgSCHCmnDlCcchTx(cell, &cellSch->allocInfo);
      }
   }
   else
   {
      rgSCHCmnDlCcchTx(cell, &cellSch->allocInfo);
   }







   rgSCHCmnDlCcchSduRetx(cell, &cellSch->allocInfo);

   if(RG_SCH_ABS_ENABLED_ABS_SF == cell->lteAdvCb.absDlSfInfo)
   {
      if(cell->lteAdvCb.absCfg.absPatternType & RGR_ABS_MUTE)
      {

      }
      else
      {
         rgSCHCmnDlCcchSduTx(cell, &cellSch->allocInfo);
      }
   }
   else
   {
      rgSCHCmnDlCcchSduTx(cell, &cellSch->allocInfo);
   }
   if(RG_SCH_ABS_ENABLED_ABS_SF == cell->lteAdvCb.absDlSfInfo)
   {
      if(cell->lteAdvCb.absCfg.absPatternType & RGR_ABS_MUTE)
      {

      }
      else
      {

         if (cellSch->dl.currCfi == cellSch->dl.newCfi)
         {
            rgSCHCmnDlRaRsp(cell, &cellSch->allocInfo);
         }
      }
   }
   else
   {

      if (cellSch->dl.currCfi == cellSch->dl.newCfi)
      {
         rgSCHCmnDlRaRsp(cell, &cellSch->allocInfo);
      }
   }



   return;
}
static S16 rgSCHCmnCcchSduAlloc
(
RgSchCellCb *cell,
RgSchUeCb *ueCb,
RgSchCmnDlRbAllocInfo *allocInfo
)






{
   RgSchDlRbAlloc *rbAllocInfo;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ueCb->cellInfo[ueCb->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   ;;


   if (allocInfo->ccchSduAlloc.ccchSduDlSf->bw <=
       allocInfo->ccchSduAlloc.ccchSduDlSf->bwAssigned)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0001,L_ERROR,DBG_CELLID, cell->cellId,ueCb->ueId, 0, 0, 0,                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                2862      , "bw<=bwAssigned for UEID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;
      return(1);
   }

   if (rgSCHDhmGetCcchSduHqProc(ueCb, cellSch->dl.time, &(ueDl->proc)) != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0002,L_ERROR,DBG_CELLID, cell->cellId,ueCb->ueId, 0, 0, 0,                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                             2869      , "rgSCHDhmGetCcchSduHqProc failed UEID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                              ;
      return(1);
   }

   rbAllocInfo = &(((ueCb)->cellInfo[(ueCb)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   rbAllocInfo->dlSf = allocInfo->ccchSduAlloc.ccchSduDlSf;

   if (rgSCHCmnCcchSduDedAlloc(cell, ueCb) != 0)
   {

      rgSCHDhmRlsHqpTb(ueDl->proc, 0, 0);
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0003,L_ERROR,DBG_CELLID, cell->cellId,ueCb->ueId, 0, 0, 0,                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                            2881      , "rgSCHCmnCcchSduDedAlloc failed UEID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                             ;
      return(1);
   }
   cmLListAdd2Tail(&allocInfo->ccchSduAlloc.ccchSduTxLst, &ueDl->proc->reqLnk);
   ueDl->proc->reqLnk.node = (U32)ueDl->proc;
   allocInfo->ccchSduAlloc.ccchSduDlSf->schdCcchUe++;

   return(0);
}
static Void rgSCHCmnDlCcchSduTx
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   CmLList *node;
   RgSchUeCb *ueCb;
   RgSchCmnDlUe *ueCmnDl;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   RgSchDlSf *dlSf = allocInfo->ccchSduAlloc.ccchSduDlSf;

   ;;

   node = cell->ccchSduUeLst.first;
   while(node)
   {
      if(cellSch->dl.maxCcchPerDlSf &&
            dlSf->schdCcchUe == cellSch->dl.maxCcchPerDlSf)
      {
         break;
      }
      else
      {
         ueCb = (RgSchUeCb *)(node->node);
         ueCmnDl = (&(((RgSchCmnUe *)((ueCb->cellInfo[ueCb->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
         node = node->next;





         if ((!(ueCb->dl.dlInactvMask & 0x20)) &&
               (!ueCmnDl->proc))
         {
            if ((rgSCHCmnCcchSduAlloc(cell, ueCb, allocInfo)) != 0)
            {
               break;
            }
         }
         else
         {
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0004,L_ERROR,DBG_CELLID, cell->cellId, ueCb->ueId, 0, 0, 0,                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                                           2955            , "ERROR!! THIS SHOULD " "NEVER HAPPEN for UEID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                            ;
            continue;
         }
      }
   }
   return;
}
static Void rgSCHCmnDlCcchTx
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   CmLList *node;
   RgSchRaCb *raCb;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchDlSf *dlSf = allocInfo->msg4Alloc.msg4DlSf;

   ;;

   node = cell->raInfo.toBeSchdLst.first;
   while(node)
   {
      if(cellSch->dl.maxCcchPerDlSf &&
            dlSf->schdCcchUe == cellSch->dl.maxCcchPerDlSf)
      {
         break;
      }
      else
      {

         raCb = (RgSchRaCb *)(node->node);
         node = node->next;


         if ((rgSCHCmnMsg4Alloc(cell, raCb, allocInfo)) != 0)
         {
            break;
         }
      }
   }
   return;
}
static Void rgSCHCmnDlCcchSduRetx
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   RgSchDlRbAlloc *rbAllocInfo;
   CmLList *node;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchUeCb *ueCb;
   RgSchDlHqProcCb *hqP;
   U8 retxBw = 0;
   RgSchCmnDlUe *ueDl;
   RgSchDlSf *dlSf = allocInfo->ccchSduAlloc.ccchSduDlSf;

   ;;

   node = cellSch->dl.ccchSduRetxLst.first;
   while(node)
   {
      if(cellSch->dl.maxCcchPerDlSf &&
            dlSf->schdCcchUe == cellSch->dl.maxCcchPerDlSf)
      {
         break;
      }
      else
      {

         hqP = (RgSchDlHqProcCb *)(node->node);
         node = node->next;
         if (hqP->tbInfo[0].dlGrnt.numRb > (dlSf->bw - dlSf->bwAssigned))
         {
            break;
         }
         ueCb = (RgSchUeCb*)(hqP->hqE->ue);
         ueDl = (&(((RgSchCmnUe *)((ueCb->cellInfo[ueCb->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

         rbAllocInfo = &(((ueCb)->cellInfo[(ueCb)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;

         rbAllocInfo->dlSf = dlSf;
         rbAllocInfo->tbInfo[0].bytesReq = hqP->tbInfo[0].ccchSchdInfo.totBytes;
         rbAllocInfo->rbsReq = hqP->tbInfo[0].dlGrnt.numRb;

         do { if (((&hqP->tbInfo[0])->isAckNackDtx == 4)) { rbAllocInfo->tbInfo[0].imcs = (&hqP->tbInfo[0])->dlGrnt.iMcs; } else { if ((&hqP->tbInfo[0])->dlGrnt.iMcs < 29) { U8 _iTbs; do { if ((&hqP->tbInfo[0])->dlGrnt.iMcs <= 9) _iTbs = (&hqP->tbInfo[0])->dlGrnt.iMcs; else if ((&hqP->tbInfo[0])->dlGrnt.iMcs <= 16) _iTbs = (&hqP->tbInfo[0])->dlGrnt.iMcs - 1; else _iTbs = (&hqP->tbInfo[0])->dlGrnt.iMcs - 2; }while(0); do { if ((_iTbs) <= 9) (rbAllocInfo->tbInfo[0].imcs) = 29; else if ((_iTbs) <= 15) (rbAllocInfo->tbInfo[0].imcs) = 30; else (rbAllocInfo->tbInfo[0].imcs) = 31;} while(0); } else { rbAllocInfo->tbInfo[0].imcs = (&hqP->tbInfo[0])->dlGrnt.iMcs; } }}while(0)
                                           ;
         rbAllocInfo->rnti = ueCb->ueId;
         rbAllocInfo->tbInfo[0].noLyr = hqP->tbInfo[0].numLyrs;

         rbAllocInfo->tbInfo[0].tbCb = &hqP->tbInfo[0];
         rbAllocInfo->tbInfo[0].schdlngForTb = 1;

         ueDl->proc = hqP;

         retxBw += rbAllocInfo->rbsReq;

         cmLListAdd2Tail(&allocInfo->ccchSduAlloc.ccchSduRetxLst,
               &hqP->reqLnk);
         hqP->reqLnk.node = (U32)hqP;
         dlSf->schdCcchUe++;
      }
   }
   dlSf->bwAssigned += retxBw;
   return;
}
static Void rgSCHCmnDlCcchRetx
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   CmLList *node;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchRaCb *raCb;
   RgSchDlHqProcCb *hqP;
   U8 retxBw = 0;
   RgSchDlSf *dlSf = allocInfo->msg4Alloc.msg4DlSf;

   ;;

   node = cellSch->dl.msg4RetxLst.first;
   while(node)
   {
      if(cellSch->dl.maxCcchPerDlSf &&
            dlSf->schdCcchUe == cellSch->dl.maxCcchPerDlSf)
      {
         break;
      }
      else
      {
         hqP = (RgSchDlHqProcCb *)(node->node);

         node = node->next;
         if (hqP->tbInfo[0].dlGrnt.numRb > (dlSf->bw - dlSf->bwAssigned))
         {
            break;
         }
         raCb = (RgSchRaCb*)(hqP->hqE->raCb);

         raCb->rbAllocInfo.dlSf = dlSf;
         raCb->rbAllocInfo.tbInfo[0].bytesReq = hqP->tbInfo[0].ccchSchdInfo.totBytes;
         raCb->rbAllocInfo.rbsReq = hqP->tbInfo[0].dlGrnt.numRb;

         do { if (((&hqP->tbInfo[0])->isAckNackDtx == 4)) { raCb->rbAllocInfo.tbInfo[0].imcs = (&hqP->tbInfo[0])->dlGrnt.iMcs; } else { if ((&hqP->tbInfo[0])->dlGrnt.iMcs < 29) { U8 _iTbs; do { if ((&hqP->tbInfo[0])->dlGrnt.iMcs <= 9) _iTbs = (&hqP->tbInfo[0])->dlGrnt.iMcs; else if ((&hqP->tbInfo[0])->dlGrnt.iMcs <= 16) _iTbs = (&hqP->tbInfo[0])->dlGrnt.iMcs - 1; else _iTbs = (&hqP->tbInfo[0])->dlGrnt.iMcs - 2; }while(0); do { if ((_iTbs) <= 9) (raCb->rbAllocInfo.tbInfo[0].imcs) = 29; else if ((_iTbs) <= 15) (raCb->rbAllocInfo.tbInfo[0].imcs) = 30; else (raCb->rbAllocInfo.tbInfo[0].imcs) = 31;} while(0); } else { raCb->rbAllocInfo.tbInfo[0].imcs = (&hqP->tbInfo[0])->dlGrnt.iMcs; } }}while(0)
                                                ;
         raCb->rbAllocInfo.rnti = raCb->tmpCrnti;
         raCb->rbAllocInfo.tbInfo[0].noLyr = hqP->tbInfo[0].numLyrs;

         raCb->rbAllocInfo.tbInfo[0].tbCb = &hqP->tbInfo[0];
         raCb->rbAllocInfo.tbInfo[0].schdlngForTb = 1;

         retxBw += raCb->rbAllocInfo.rbsReq;

         cmLListAdd2Tail(&allocInfo->msg4Alloc.msg4RetxLst,
               &hqP->reqLnk);
         hqP->reqLnk.node = (U32)hqP;
         dlSf->schdCcchUe++;
      }
   }
   dlSf->bwAssigned += retxBw;
   return;
}
static Void rgSCHCmnDlBcchPcch
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo,
RgInfSfAlloc *subfrmAlloc
)






{
   CmLteTimingInfo frm;
   RgSchDlSf *sf;
   RgSchClcDlLcCb *pcch;
   RgSchClcBoRpt *bo;






   ;;

   frm = cell->crntTime;





   do { if ((frm.subframe += (2 + 0)) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);




   sf = rgSCHUtlSubFrmGet(cell, frm);
   rgSCHDlSiSched(cell, allocInfo, subfrmAlloc);


   pcch = rgSCHDbmGetPcch(cell);







   if (pcch->boLst.first != 0L)
   {
      bo = (RgSchClcBoRpt *)(pcch->boLst.first->node);

      if ((((frm).sfn == (bo->timeToTx).sfn) && ((frm).subframe == (bo->timeToTx).subframe)))
      {

         rgSCHCmnClcAlloc(cell, sf, pcch, 0xfffe, allocInfo);
      }
   }
   return;
}
static Bool rgSCHCmnChkInWin
(
CmLteTimingInfo frm,
CmLteTimingInfo start,
CmLteTimingInfo end
)






{
   Bool inWin = 0;

   ;;

   if (end.sfn > start.sfn)
   {
      if (frm.sfn > start.sfn
            || (frm.sfn == start.sfn && frm.subframe >= start.subframe))
      {
         if (frm.sfn < end.sfn
               || (frm.sfn == end.sfn && frm.subframe <= start.subframe))
         {
            inWin = 1;
         }
      }
   }

   else if (end.sfn < start.sfn)
   {
      if (frm.sfn > start.sfn
            || (frm.sfn == start.sfn && frm.subframe >= start.subframe))
      {
         inWin = 1;
      }
      else
      {
         if (frm.sfn < end.sfn
               || (frm.sfn == end.sfn && frm.subframe <= end.subframe))
         {
            inWin = 1;
         }
      }
   }
   else
   {
      if (frm.sfn == start.sfn
            && (frm.subframe >= start.subframe
               && frm.subframe <= end.subframe))
      {
         inWin = 1;
      }
   }

   return(inWin);
}
static Bool rgSCHCmnChkPastWin
(
CmLteTimingInfo frm,
CmLteTimingInfo end
)





{
   CmLteTimingInfo refFrm = end;
   Bool pastWin;

   ;;

   refFrm.sfn = ((refFrm.sfn) + 1) & 0x03ff;
   do { if ((end.subframe += 1) > 9) { end.sfn = ((end.sfn) + 1) & 0x03ff; end.subframe -= 10; }} while(0);
   pastWin = rgSCHCmnChkInWin(frm, end, refFrm);

   return(pastWin);
}
static Void rgSCHCmnClcAlloc
(
RgSchCellCb *cell,
RgSchDlSf *sf,
RgSchClcDlLcCb *lch,
U16 rnti,
RgSchCmnDlRbAllocInfo *allocInfo
)
{
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchClcBoRpt *bo;
   U32 rb=0;
   U8 mcs;
   U32 tbs;





   ;;

   bo = (RgSchClcBoRpt *)(lch->boLst.first->node);

   mcs = bo->mcs;
   tbs = bo->bo;

   if(cellDl->bitsPerRb==0)
   {
      while ((rgTbSzTbl[0][0][rb]) < (tbs*8))
      {
         rb++;
      }
      rb = rb+1;
   }
   else
   {
      rb = ((((tbs*8)) + (cellDl->bitsPerRb)-1) / (cellDl->bitsPerRb));
   }
   if (rb > sf->bw - sf->bwAssigned)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0005,L_ERROR,DBG_CELLID, cell->cellId,rnti, 0, 0, 0,                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                          3583      , "BW allocation " "failed for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                           ;
      return;
   }


   sf->bwAssigned = sf->bwAssigned + rb;

   if (rnti == 0xffff)
   {
      allocInfo->bcchAlloc.rnti = rnti;
      allocInfo->bcchAlloc.dlSf = sf;
      allocInfo->bcchAlloc.tbInfo[0].bytesReq = tbs;
      allocInfo->bcchAlloc.rbsReq = rb;
      allocInfo->bcchAlloc.tbInfo[0].imcs = mcs;
      allocInfo->bcchAlloc.tbInfo[0].noLyr = 1;

      allocInfo->bcchAlloc.nPrb = bo->nPrb;
   }
   else
   {
      allocInfo->pcchAlloc.rnti = rnti;
      allocInfo->pcchAlloc.dlSf = sf;
      allocInfo->pcchAlloc.tbInfo[0].bytesReq = tbs;
      allocInfo->pcchAlloc.rbsReq = rb;
      allocInfo->pcchAlloc.tbInfo[0].imcs = mcs;
      allocInfo->pcchAlloc.tbInfo[0].noLyr = 1;
      allocInfo->pcchAlloc.nPrb = bo->nPrb;
   }
   return;
}
 RgSchPdcch *rgSCHCmnCmnPdcchAlloc
(
RgSchCellCb *cell,
RgSchDlSf *subFrm
)





{
   U8 i;
   CmLteAggrLvl aggrLvl;
   U8 pdcchCnt;
   RgSchPdcchInfo *pdcchInfo;
   RgSchPdcch *pdcch;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U8 numCce;

   ;;

   aggrLvl = cellSch->dl.cmnChAggrLvl;

   pdcchInfo = &(subFrm->pdcchInfo);
   if(cell->nCce != pdcchInfo->nCce)
   {
      rgSCHUtlPdcchInit(cell, subFrm, cell->nCce);
   }


   switch (aggrLvl)
   {
      case CM_LTE_AGGR_LVL4:
        pdcchCnt = 4;
        numCce = 4;
        break;
      case CM_LTE_AGGR_LVL8:
        pdcchCnt = 2;
        numCce = 8;
        break;
      default:
        return(0L);
   }


   for (i = 0; i < pdcchCnt; i++)
   {
      if (rgSCHUtlPdcchAvail(cell, pdcchInfo, i, aggrLvl, &pdcch) == 1)
      {

         pdcch->isSpsRnti = 0;


         subFrm->cceCnt += numCce;
         pdcch->pdcchSearchSpace = RG_SCH_CMN_SEARCH_SPACE;

         return(pdcch);
      }
   }


   subFrm->isCceFailure = 1;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0006,L_DEBUG,DBG_CELLID, cell->cellId, aggrLvl, 0, 0, 0,            "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"   ,            3710   , "PDCCH ERR: NO PDDCH AVAIL IN COMMON SEARCH SPACE aggr:%u", RLOG_FILE_ID, RLOG_MODULE_NAME); }

             ;
   return(0L);
}
 Void rgSCHCmnClcRbAlloc
(
RgSchCellCb *cell,
U32 bo,
U8 cqi,
U8 *rb,
U32 *tbs,
U8 *mcs,
U8 *iTbs,
Bool isSpsBo,
RgSchDlSf *sf
)
{
   U8 iTbsVal;
   RgSchCmnTbSzEff *effTbl;
   U32 eff;
   U32 noRes;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U8 cfi = cellSch->dl.currCfi;
   U32 tmpRb=0;
   ;;


   if(isSpsBo)
   {
     cfi = 3;
   }
   effTbl = (RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[0][cfi]);
   iTbsVal = (*(RgSchCmnCqiToTbs *)(cellSch->dl.cqiToTbsTbl[0][cfi]))[cqi];
   do { if (iTbsVal <= 9) *mcs = iTbsVal; else if (iTbsVal <= 15) *mcs = iTbsVal + 1; else *mcs = iTbsVal + 2;} while(0);

   if (isSpsBo)
   {
      if ( *mcs > 15)
      {
         *mcs=15;
      }
      do { if (*mcs <= 9) iTbsVal = *mcs; else if (*mcs <= 16) iTbsVal = *mcs - 1; else iTbsVal = *mcs - 2; }while(0);
      *iTbs = iTbsVal;
   }



   eff = (*effTbl)[iTbsVal];


   noRes = ((bo * 8 * 1024) / eff );



   tmpRb = (((noRes) + (cellSch->dl.noResPerRb[cfi])-1) / (cellSch->dl.noResPerRb[cfi]));

   ;
   if (tmpRb > cellSch->dl.maxDlBwPerUe)
   {
      tmpRb = cellSch->dl.maxDlBwPerUe;
   }
   while ((rgTbSzTbl[0][iTbsVal][tmpRb-1]/8) < bo &&
           (tmpRb < cellSch->dl.maxDlBwPerUe))
   {
      tmpRb++;
      ;
   }
   *tbs = rgTbSzTbl[0][iTbsVal][tmpRb-1]/8;
   *rb = (U8)tmpRb;
   do { if (iTbsVal <= 9) *mcs = iTbsVal; else if (iTbsVal <= 15) *mcs = iTbsVal + 1; else *mcs = iTbsVal + 2;} while(0);

   return;
}
static S16 rgSCHCmnMsg4Alloc
(
RgSchCellCb *cell,
RgSchRaCb *raCb,
RgSchCmnDlRbAllocInfo *allocInfo
)






{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;


   rgNumMsg4ToBeTx++;

   if (allocInfo->msg4Alloc.msg4DlSf->bw <=
       allocInfo->msg4Alloc.msg4DlSf->bwAssigned)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0007,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                         3907      , "bw<=bwAssigned", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                          ;
      return(1);
   }

   if (rgSCHDhmGetMsg4HqProc(raCb, cellSch->dl.time) != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0008,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                       3914      , "rgSCHDhmGetMsg4HqProc failed", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                        ;
      return(1);
   }

   raCb->rbAllocInfo.dlSf = allocInfo->msg4Alloc.msg4DlSf;

   if (rgSCHCmnMsg4DedAlloc(cell, raCb) != 0)
   {

      rgSCHDhmRlsHqpTb(raCb->dlHqE->msg4Proc, 0, 0);
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0009,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                       3925      , "rgSCHCmnMsg4DedAlloc failed.", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                        ;
      return(1);
   }
   cmLListAdd2Tail(&allocInfo->msg4Alloc.msg4TxLst, &raCb->dlHqE->msg4Proc->reqLnk);
   raCb->dlHqE->msg4Proc->reqLnk.node = (U32)raCb->dlHqE->msg4Proc;
   allocInfo->msg4Alloc.msg4DlSf->schdCcchUe++;

   return(0);
}
 RgSchPdcch *rgSCHCmnPdcchAlloc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlSf *subFrm,
U32 y,
U8 cqi,
TfuDciFormat dciFrmt,
Bool isDtx
)
{
   U8 i;
   CmLteAggrLvl aggrLvl;
   U16 loc;
   RgSchPdcchInfo *pdcchInfo;
   U8 pdcchCnt;
   RgSchPdcch *pdcch;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U8 numCce;

   ;;



   aggrLvl = cellSch->dciAggrLvl[cqi][dciFrmt];
   if (isDtx)
   {
      if (aggrLvl != CM_LTE_AGGR_LVL8)
      {
         switch(aggrLvl)
         {
            case CM_LTE_AGGR_LVL1:
               aggrLvl = CM_LTE_AGGR_LVL2;
                break;
            case CM_LTE_AGGR_LVL2:
               aggrLvl = CM_LTE_AGGR_LVL4;
               break;
            case CM_LTE_AGGR_LVL4:
               aggrLvl = CM_LTE_AGGR_LVL8;
               break;
            default:
               break;
         }

      }
   }

   pdcchInfo = &subFrm->pdcchInfo;
   if(cell->nCce != pdcchInfo->nCce)
   {
      rgSCHUtlPdcchInit(cell, subFrm, cell->nCce);
   }


   if (pdcchInfo->nCce < (1 << (aggrLvl - 1)))
   {

      subFrm->isCceFailure = 1;
      if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb000a,L_DEBUG,DBG_CELLID, cell->cellId, aggrLvl, 0, 0, 0,                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                   4058      , "PDCCH ERR: NO PDDCH AVAIL IN UE SEARCH SPACE :aggr(%u)", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                    ;

      return(0L);
   }

   switch (aggrLvl)
   {
      case CM_LTE_AGGR_LVL1:
        pdcchCnt = 6;
        numCce = 1;
        break;
      case CM_LTE_AGGR_LVL2:
        pdcchCnt = 6;
        numCce = 2;
        break;
      case CM_LTE_AGGR_LVL4:
        pdcchCnt = 2;
        numCce = 4;
        break;
      case CM_LTE_AGGR_LVL8:
        pdcchCnt = 2;
        numCce = 8;
        break;
      default:
        return(0L);
   }


   for (i = 0; i < pdcchCnt; i++)
   {

      loc = (y+i) % (pdcchInfo->nCce / (1 << (aggrLvl - 1)));

      if (rgSCHUtlPdcchAvail(cell, pdcchInfo, loc, aggrLvl, &pdcch) == 1)
      {

         pdcch->dci.u.format1aInfo.t.pdschInfo.isTBMsg4= 0;
         pdcch->dci.u.format0Info.isSrGrant = 0;

         pdcch->isSpsRnti = 0;


         subFrm->cceCnt += numCce;
         pdcch->pdcchSearchSpace = RG_SCH_UE_SPECIFIC_SEARCH_SPACE;
         if (ue != 0L)
         {
            {
               pdcch->dciNumOfBits = ue->dciSize.dedSize[dciFrmt];
            }
         }
         else
         {

            pdcch->dciNumOfBits = cell->dciSize.size[dciFrmt];
         }
         return(pdcch);
      }
   }


   subFrm->isCceFailure = 1;

   if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb000b,L_DEBUG,DBG_CELLID, cell->cellId, aggrLvl, 0, 0, 0,                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"   ,                4130   , "PDCCH ERR: NO PDDCH AVAIL IN UE SEARCH SPACE :aggr(%u)", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                 ;
   return(0L);
}
static S16 rgSCHCmnCcchSduDedAlloc
(
RgSchCellCb *cell,
RgSchUeCb *ueCb
)





{
   RgSchDlHqEnt *hqE = 0L;
   U32 effBo;
   RgSchDlRbAlloc *rbAllocinfo = 0L;
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   U8 iTbs;
   U8 numRb;




   ;;

   rbAllocinfo = &(((ueCb)->cellInfo[(ueCb)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;

   effBo = ueCb->dlCcchInfo.bo + 1;






   rgSCHCmnClcRbAlloc(cell, effBo, cellDl->ccchCqi, &rbAllocinfo->rbsReq,
                      &rbAllocinfo->tbInfo[0].bytesReq,
                      &rbAllocinfo->tbInfo[0].imcs, &iTbs, 0,
                      rbAllocinfo->dlSf);


   iTbs = 0;

   if ((S16)rbAllocinfo->rbsReq > ((S16)(rbAllocinfo->dlSf->bw -
                                   rbAllocinfo->dlSf->bwAssigned)))
   {



      if (rbAllocinfo->dlSf->bwAssigned == 0)
      {
         numRb = rbAllocinfo->dlSf->bw;
         do { if (rbAllocinfo->tbInfo[0].imcs <= 9) iTbs = rbAllocinfo->tbInfo[0].imcs; else if (rbAllocinfo->tbInfo[0].imcs <= 16) iTbs = rbAllocinfo->tbInfo[0].imcs - 1; else iTbs = rbAllocinfo->tbInfo[0].imcs - 2; }while(0);
         while (rgTbSzTbl[0][++iTbs][numRb-1]/8 < effBo)
         {
            iTbs++;
         }
         rbAllocinfo->rbsReq = numRb;
         rbAllocinfo->tbInfo[0].bytesReq = rgTbSzTbl[0][iTbs][numRb-1]/8;
         do { if (iTbs <= 9) rbAllocinfo->tbInfo[0].imcs = iTbs; else if (iTbs <= 15) rbAllocinfo->tbInfo[0].imcs = iTbs + 1; else rbAllocinfo->tbInfo[0].imcs = iTbs + 2;} while(0);
      }
      else
      {
         return(1);
      }
   }


   rbAllocinfo->dlSf->bwAssigned = rbAllocinfo->dlSf->bwAssigned +
                                   rbAllocinfo->rbsReq;
   hqE = (ueCb->cellInfo[ueCb->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]]->hqEnt);
   rbAllocinfo->tbInfo[0].tbCb = &hqE->ccchSduProc->tbInfo[0];
   rbAllocinfo->rnti = ueCb->ueId;
   rbAllocinfo->tbInfo[0].noLyr = 1;

   return(0);
}
static S16 rgSCHCmnMsg4DedAlloc
(
RgSchCellCb *cell,
RgSchRaCb *raCb
)





{
   U32 effBo;
   RgSchDlRbAlloc *rbAllocinfo = &raCb->rbAllocInfo;
   U8 iTbs;
   U8 numRb;





   ;;

   effBo = raCb->dlCcchInfo.bo + 1 + 7;






   rgSCHCmnClcRbAlloc(cell, effBo, raCb->ccchCqi, &rbAllocinfo->rbsReq,
                      &rbAllocinfo->tbInfo[0].bytesReq,
                      &rbAllocinfo->tbInfo[0].imcs, &iTbs, 0,
                      rbAllocinfo->dlSf);


   iTbs = 0;

   if ((S16)rbAllocinfo->rbsReq > ((S16)(rbAllocinfo->dlSf->bw -
               rbAllocinfo->dlSf->bwAssigned)))
   {



      if (rbAllocinfo->dlSf->bwAssigned == 0)
      {
         numRb = rbAllocinfo->dlSf->bw;
         do { if (rbAllocinfo->tbInfo[0].imcs <= 9) iTbs = rbAllocinfo->tbInfo[0].imcs; else if (rbAllocinfo->tbInfo[0].imcs <= 16) iTbs = rbAllocinfo->tbInfo[0].imcs - 1; else iTbs = rbAllocinfo->tbInfo[0].imcs - 2; }while(0);
         while (rgTbSzTbl[0][++iTbs][numRb-1]/8 < effBo)
         {
            iTbs++;
         }
         rbAllocinfo->rbsReq = numRb;
         rbAllocinfo->tbInfo[0].bytesReq = rgTbSzTbl[0][iTbs][numRb-1]/8;
         do { if (iTbs <= 9) rbAllocinfo->tbInfo[0].imcs = iTbs; else if (iTbs <= 15) rbAllocinfo->tbInfo[0].imcs = iTbs + 1; else rbAllocinfo->tbInfo[0].imcs = iTbs + 2;} while(0);
      }
      else
      {
         return(1);
      }
   }


   rbAllocinfo->dlSf->bwAssigned = rbAllocinfo->dlSf->bwAssigned +
                                   rbAllocinfo->rbsReq;
   rbAllocinfo->rnti = raCb->tmpCrnti;
   rbAllocinfo->tbInfo[0].tbCb = &raCb->dlHqE->msg4Proc->tbInfo[0];
   rbAllocinfo->tbInfo[0].schdlngForTb = 1;
   rbAllocinfo->tbInfo[0].noLyr = 1;

   return(0);
}
static Void rgSCHCmnDlRaRsp
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   CmLteTimingInfo frm;
   CmLteTimingInfo winStartFrm;
   RgSchDlSf *subFrm;
   U8 winStartIdx;
   U8 winGap;
   U8 rarnti;
   U8 raIdx;
   RgSchCmnCell *sched;
   U8 i,noRaRnti=0;
   ;;

   frm = cell->crntTime;
   do { if ((frm.subframe += (2 + 0)) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);



   subFrm = rgSCHUtlSubFrmGet(cell, frm);
   sched = ((RgSchCmnCell *)((cell)->sc.sch));



   winGap = (sched->dl.numRaSubFrms-1) + (cell->rachCfg.raWinSize-1)
             +3;



   do { S32 _subframe; _subframe = frm.sfn * 10 + frm.subframe; _subframe = _subframe - winGap; if(_subframe < 0) { _subframe = (1024 * 10) + _subframe; } winStartFrm.sfn = _subframe / 10; winStartFrm.subframe = _subframe % 10; } while(0);

   winStartIdx = (winStartFrm.sfn & 1) * 10 + winStartFrm.subframe;

   for(i = 0; ((i < cell->rachCfg.raWinSize) && (noRaRnti < 4)); i++)
   {
      raIdx = (winStartIdx + i) % (2*10);

      if (cell->raInfo.raReqLst[raIdx].first != 0L)
      {
         allocInfo->raRspAlloc[noRaRnti].biEstmt =
                         (!i * 1);
         rarnti = raIdx % 10 + 1;
         if (rgSCHCmnRaRspAlloc(cell, subFrm, raIdx,
                                 rarnti, noRaRnti, allocInfo) != 0)
         {

            break;
         }


         if(allocInfo->raRspAlloc[noRaRnti].numRapids < cell->raInfo.raReqLst[raIdx].count)
         {
            break;
         }
         noRaRnti++;

      }
   }
   return;
}
static S16 rgSCHCmnRaRspAlloc
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
U16 raIndex,
U16 rarnti,
U8 noRaRnti,
RgSchCmnDlRbAllocInfo *allocInfo
)
{
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   U16 noBytes;
   U32 rb = 0;
   U32 tbs;

   U8 mcs;
   CmLListCp *reqLst;

   Bool isAlloc = 0;
   static U8 schdNumRapid = 0;
   U8 remNumRapid = 0;
   U8 nPrb = 0;
   S32 allwdTbSz = 0;





   ;;





   if(noRaRnti == 0)
   {
      schdNumRapid = 0;
   }


   if (subFrm->bw == subFrm->bwAssigned)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb000c,L_ERROR,DBG_CELLID, cell->cellId,rarnti, 0, 0, 0,                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                            4592      , "bw == bwAssigned RARNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                             ;
      return(1);
   }

   reqLst = &cell->raInfo.raReqLst[raIndex];
   if (reqLst->count == 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb000d,L_ERROR,DBG_CELLID, cell->cellId,rarnti, 0, 0, 0,                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                          4600      , "reqLst Count=0 RARNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                           ;
      return(1);
   }

   else
   {
      RgSchRaReqInfo *raReq;
      RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);
      RgSchUeCb *ue;
      CmLList *node;

      node = reqLst->first;
      while(node)
      {
         raReq = (RgSchRaReqInfo *)(node->node);
         node = raReq->raReqLstEnt.next;

         if(((raReq->raReq.rapId) >= (cell->rachCfg.numRaPreamble)) && (raReq->ue == 0L))
         {

            if ((raReq->raReq.rapId < cellSch->rachCfg.dedPrmStart) ||
                (raReq->raReq.rapId > cellSch->rachCfg.dedPrmStart +
                  cellSch->rachCfg.numDedPrm - 1))
            {

               ue = rgSCHCmnGetHoUe(cell, raReq);
            }
            else
            {

               ue = rgSCHCmnGetPoUe(cell, raReq);
            }



            if (ue == 0L)
            {
               cmLListDelFrm(reqLst, &raReq->raReqLstEnt);


               rgSCHUtlFreeSBuf(cell->instIdx, (Data **)&raReq,
                     sizeof(RgSchRaReqInfo));




               rgNumDedPream--;




            }
            else
            {
               raReq->ue = ue;
            }
         }


         else
         {
            break;
         }
      }
   }

   remNumRapid = reqLst->count;



   if ( schdNumRapid+remNumRapid > cellUl->maxMsg3PerUlSf )
   {
      remNumRapid = cellUl->maxMsg3PerUlSf-schdNumRapid;
   }


   while (remNumRapid)
   {


      noBytes = ((remNumRapid) * 7) +
                 allocInfo->raRspAlloc[noRaRnti].biEstmt;
      if ((allwdTbSz = rgSCHUtlGetAllwdCchTbSz(noBytes*8, &nPrb, &mcs)) == -1)
      {
         remNumRapid--;
         continue;
      }


      if(cellDl->bitsPerRb==0)
      {
         while ((rgTbSzTbl[0][0][rb]) <(U32) allwdTbSz)
         {
            rb++;
         }
         rb = rb+1;
      }
      else
      {
         rb = (((allwdTbSz) + (cellDl->bitsPerRb)-1) / (cellDl->bitsPerRb));
      }
      if (rb > subFrm->bw - subFrm->bwAssigned)
      {
         remNumRapid--;
         continue;
      }

      isAlloc = 1;
      tbs = allwdTbSz/8;
      break;
   }
   if (!isAlloc)
   {
      if( L_INFO < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb000e,L_INFO,DBG_CELLID, cell->cellId, 0, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c",4730, "BW alloc Failed", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(1);
   }

   subFrm->bwAssigned = subFrm->bwAssigned + rb;


   allocInfo->raRspAlloc[noRaRnti].rnti = rarnti;
   allocInfo->raRspAlloc[noRaRnti].tbInfo[0].bytesReq = tbs;
   allocInfo->raRspAlloc[noRaRnti].rbsReq = rb;
   allocInfo->raRspAlloc[noRaRnti].dlSf = subFrm;
   allocInfo->raRspAlloc[noRaRnti].tbInfo[0].imcs = mcs;
   allocInfo->raRspAlloc[noRaRnti].raIndex = raIndex;

   allocInfo->raRspAlloc[noRaRnti].numRapids = remNumRapid;
   allocInfo->raRspAlloc[noRaRnti].nPrb = nPrb;
   allocInfo->raRspAlloc[noRaRnti].tbInfo[0].noLyr = 1;

   schdNumRapid += remNumRapid;
   return(0);
}
 Void rgSCHCmnUlAllocFillRbInfo
(
RgSchCellCb *cell,
RgSchUlSf *sf,
RgSchUlAlloc *alloc
)






{
    RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
    RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
    U8 cfi = cellDl->currCfi;


   ;;

   alloc->grnt.rbStart = (alloc->sbStart * cellUl->sbSize) +
                                    cell->dynCfiCb.bwInfo[cfi].startRb;


   alloc->grnt.numRb = (alloc->numSb * cellUl->sbSize);

   return;
}
static Void rgSCHCmnMsg3GrntReq
(
RgSchCellCb *cell,
CmLteRnti rnti,
Bool preamGrpA,
RgSchUlHqProcCb *hqProc,
RgSchUlAlloc **ulAllocRef,
U8 *hqProcIdRef
)
{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchUlSf *sf = &cellUl->ulSfArr[cellUl->msg3SchdIdx];
   RgSchUlHole *hole;
   RgSchUlAlloc *alloc;
   U8 iMcs;
   U8 numSb;

   ;;

   *ulAllocRef = 0L;


   if (*sf->allocCountRef >= cellUl->maxAllocPerUlSf)
   {
      return;
   }
   if (preamGrpA == 0)
   {
      numSb = cellUl->ra.prmblBNumSb;
      iMcs = cellUl->ra.prmblBIMcs;
   }
   else
   {
      numSb = cellUl->ra.prmblANumSb;
      iMcs = cellUl->ra.prmblAIMcs;
   }

   if ((hole = rgSCHUtlUlHoleFirst(sf)) != 0L)
   {
      if(*sf->allocCountRef == 0)
      {
         RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);

         if (sf->holeDb->count == 1 && (hole->start == 0))
         {
            hole->num = cell->dynCfiCb.bwInfo[cellDl->currCfi].numSb;

            hole->num = cell->dynCfiCb.bwInfo[cellDl->currCfi].numSb;
         }
         else
         {
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb000f,L_ERROR,DBG_CELLID, cell->cellId,rnti, 0, 0, 0,                                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                                                     4883            , "Error! holeDb sanity check failed RNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                      ;
         }
      }
      if (numSb <= hole->num)
      {
         U8 iTbs;
         alloc = rgSCHUtlUlAllocGetHole(sf, numSb, hole);
         rgSCHCmnUlAllocFillRbInfo(cell, sf, alloc);
         alloc->grnt.iMcs = iMcs;
         alloc->grnt.iMcsCrnt = iMcs;
         iTbs = rgSCHCmnUlGetITbsFrmIMcs(iMcs);
         ;

         alloc->grnt.datSz = rgTbSzTbl[0][iTbs][alloc->grnt.numRb-1] / 8;
         do { ; alloc->grnt.modOdr = (TfuModScheme)rgUlIMcsTbl[iMcs].qm;} while(0);

         alloc->grnt.nDmrs = 0;
         alloc->grnt.hop = 0;
         alloc->grnt.delayBit = 0;
         alloc->grnt.isRtx = 0;
         *ulAllocRef = alloc;
         *hqProcIdRef = (cellUl->msg3SchdHqProcIdx);
         hqProc->procId = *hqProcIdRef;
         hqProc->ulSfIdx = (cellUl->msg3SchdIdx);
         alloc->rnti = rnti;
         alloc->ue = 0L;
         alloc->pdcch = 0;
         alloc->forMsg3 = 1;
         alloc->hqProc = hqProc;
         rgSCHUhmNewTx(hqProc, (U8)(cell->rachCfg.maxMsg3Tx - 1), alloc);
         if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0010,L_DEBUG,DBG_CELLID, cell->cellId, alloc->rnti, ((U32)alloc->hqProc), alloc->hqProc->procId, alloc->hqProc->ulSfIdx,                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                     4918         , "RNTI:%d MSG3 ALLOC proc(%p)procId(%d)schdIdx(%d)", RLOG_FILE_ID, RLOG_MODULE_NAME); }




                                      ;
         if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0011,L_DEBUG,DBG_CELLID, cell->cellId, ((U32)alloc), cell->rachCfg.maxMsg3Tx, 0, 0,                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                      4922         , "alloc(%p)maxMsg3Tx(%d)", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                       ;
      }
   }

   return;
}
static Void rgSCHCmnDlSetUeAllocLmt
(
RgSchCellCb *cell,
RgSchCmnDlUe *ueDl
)





{
   U8 modOrder;
   U32 maxRb;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U8 cfi = cellSch->dl.currCfi;

   ;;



   ueDl->mimoInfo.cwInfo[0].iTbs[0] = (*(RgSchCmnCqiToTbs *)(cellSch->dl.cqiToTbsTbl[0][cfi]))
                           [ueDl->mimoInfo.cwInfo[0].cqi];

   ueDl->mimoInfo.cwInfo[0].iTbs[1] = (*(RgSchCmnCqiToTbs *)(cellSch->dl.cqiToTbsTbl[1][cfi]))
                           [ueDl->mimoInfo.cwInfo[0].cqi];

   ueDl->mimoInfo.cwInfo[0].eff[0] = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[0][cfi]))
                           [ueDl->mimoInfo.cwInfo[0].iTbs[0]];

   ueDl->mimoInfo.cwInfo[0].eff[1] = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[1][cfi]))
                           [ueDl->mimoInfo.cwInfo[0].iTbs[1]];


   ueDl->mimoInfo.cwInfo[1].iTbs[0] = (*(RgSchCmnCqiToTbs *)(cellSch->dl.cqiToTbsTbl[0][cfi]))
                           [ueDl->mimoInfo.cwInfo[1].cqi];

   ueDl->mimoInfo.cwInfo[1].iTbs[1] = (*(RgSchCmnCqiToTbs *)(cellSch->dl.cqiToTbsTbl[1][cfi]))
                           [ueDl->mimoInfo.cwInfo[1].cqi];

   ueDl->mimoInfo.cwInfo[1].eff[0] = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[0][cfi]))
                           [ueDl->mimoInfo.cwInfo[1].iTbs[0]];

   ueDl->mimoInfo.cwInfo[1].eff[1] = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[1][cfi]))
                           [ueDl->mimoInfo.cwInfo[1].iTbs[1]];





   (ueDl->mimoInfo.ri/2 == 0)? (ueDl->mimoInfo.cwInfo[0].noLyr = 1) :
              (ueDl->mimoInfo.cwInfo[0].noLyr = ueDl->mimoInfo.ri/2);
   ueDl->mimoInfo.cwInfo[1].noLyr = ueDl->mimoInfo.ri - ueDl->mimoInfo.cwInfo[0].noLyr;
   do { if (ueDl->mimoInfo.cwInfo[0].iTbs[1] <= 9) modOrder = 2; else if (ueDl->mimoInfo.cwInfo[0].iTbs[1] <= 15) modOrder = 4; else modOrder = 6;} while(0);


   maxRb = ((ueDl->maxSbSz)/(cellSch->dl.noResPerRb[cfi] * modOrder *
                   ueDl->mimoInfo.ri));
   if (cellSch->dl.isDlFreqSel)
   {

      maxRb -= maxRb % cell->rbgSize;
   }
   ueDl->maxRb = ((maxRb) <= (cellSch->dl.maxDlBwPerUe) ? (maxRb) : (cellSch->dl.maxDlBwPerUe));
   if (cellSch->dl.isDlFreqSel)
   {

      if (ueDl->maxRb % cell->rbgSize)
      {
         ueDl->maxRb += (cell->rbgSize -
                         (ueDl->maxRb % cell->rbgSize));
      }
   }



   if (ueDl->mimoInfo.ri < 2)
   {
      ueDl->mimoInfo.btrCwIdx = 0;
   }
   else
   {
      if (ueDl->mimoInfo.cwInfo[0].eff[ueDl->mimoInfo.cwInfo[0].noLyr-1] <
          ueDl->mimoInfo.cwInfo[1].eff[ueDl->mimoInfo.cwInfo[1].noLyr-1])
      {
         ueDl->mimoInfo.btrCwIdx = 1;
      }
      else
      {
         ueDl->mimoInfo.btrCwIdx = 0;
      }
   }

   return;
   }
static Void rgSCHCheckAndSetTxScheme
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U8 cfi = cellSch->dl.currCfi;
   U8 maxiTbs;
   U8 cqiBasediTbs;
   U8 actualiTbs;

   ;;

   maxiTbs = (*(RgSchCmnCqiToTbs*)(cellSch->dl.cqiToTbsTbl[0][cfi]))
                [16 - 1];
   cqiBasediTbs = (ueDl->laCb[0].cqiBasediTbs)/100;
   actualiTbs = ueDl->mimoInfo.cwInfo[0].iTbs[0];

   if((actualiTbs < 5) && (cqiBasediTbs >
     actualiTbs) && ((cqiBasediTbs - actualiTbs) > 5))
   {
      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x08); };
   }

   if(actualiTbs >= maxiTbs)
   {
      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD &= ~(0x08); };
   }

   return;
}
static Void rgSCHCmnDlSetUeAllocLmtLa
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   U8 modOrder;
   U32 maxRb;
   U8 reportediTbs;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U8 cfi = cellSch->dl.currCfi;
   U8 maxiTbs;
   U8 cwIdx;

   ;;

   maxiTbs = (*(RgSchCmnCqiToTbs *)(cellSch->dl.cqiToTbsTbl[0][cfi]))[16 - 1];
   if(ueDl->cqiFlag == 1)
   {

      reportediTbs = (*(RgSchCmnCqiToTbs *)(cellSch->dl.cqiToTbsTbl[0][cfi]))
                        [ueDl->mimoInfo.cwInfo[0].cqi];



      if(1 == cell->isAutoCfgModeEnb)
      {
         rgSchCheckAndTriggerModeChange(cell, ue, reportediTbs,
               ueDl->mimoInfo.cwInfo[0].iTbs[0], maxiTbs);
      }

      for(cwIdx=0; cwIdx < 2; cwIdx++)
      {
         S32 iTbsNew ;
         reportediTbs = (*(RgSchCmnCqiToTbs *)(cellSch->dl.cqiToTbsTbl[0][cfi]))
                        [ueDl->mimoInfo.cwInfo[cwIdx].cqi];

         iTbsNew = (S32) reportediTbs;

         if(!ueDl->laCb[cwIdx].notFirstCqi)
         {

            ueDl->laCb[cwIdx].cqiBasediTbs = (iTbsNew * 100);
            ueDl->laCb[cwIdx].notFirstCqi = 1;
         }
         else if ((((reportediTbs) > (ueDl->mimoInfo.cwInfo[cwIdx].iTbs[0]) ? (reportediTbs) - (ueDl->mimoInfo.cwInfo[cwIdx].iTbs[0]) : (ueDl->mimoInfo.cwInfo[cwIdx].iTbs[0]) - (reportediTbs))) > 5)
         {


            ueDl->laCb[cwIdx].lastiTbsIgnored = 1;
            ueDl->laCb[cwIdx].numLastiTbsIgnored++;
            if( ueDl->laCb[cwIdx].numLastiTbsIgnored > 10)
            {

               ueDl->laCb[cwIdx].cqiBasediTbs = (iTbsNew * 100);
               ueDl->laCb[cwIdx].deltaiTbs = 0;
               ueDl->laCb[cwIdx].lastiTbsIgnored = 0;
               ueDl->laCb[cwIdx].numLastiTbsIgnored = 0;
            }
         }
         else
         {
            if (ueDl->laCb[cwIdx].lastiTbsIgnored != 1)
            {
               ueDl->laCb[cwIdx].cqiBasediTbs = ((20 * iTbsNew * 100) +
                     (80 * ueDl->laCb[cwIdx].cqiBasediTbs))/100;
            }
            else
            {


               ueDl->laCb[cwIdx].cqiBasediTbs = ((20 * iTbsNew * 100) +
                     (80 * ueDl->mimoInfo.cwInfo[cwIdx].iTbs[0] * 100))/100;
               ueDl->laCb[cwIdx].deltaiTbs = 0;
               ueDl->laCb[cwIdx].lastiTbsIgnored = 0;
            }
         }

         iTbsNew = (ueDl->laCb[cwIdx].cqiBasediTbs + ueDl->laCb[cwIdx].deltaiTbs)/100;

         { if (iTbsNew < 0) { iTbsNew = 0; } else if (iTbsNew > (maxiTbs)) { iTbsNew = (maxiTbs); }};

         ueDl->mimoInfo.cwInfo[cwIdx].iTbs[0] = ((iTbsNew) <= (cell->thresholds.maxDlItbs) ? (iTbsNew) : (cell->thresholds.maxDlItbs));
         ueDl->mimoInfo.cwInfo[cwIdx].iTbs[1] = ueDl->mimoInfo.cwInfo[cwIdx].iTbs[0];

         ueDl->mimoInfo.cwInfo[cwIdx].eff[0] = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[0][cfi]))
                                               [ueDl->mimoInfo.cwInfo[cwIdx].iTbs[0]];

         ueDl->mimoInfo.cwInfo[cwIdx].eff[1] = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[1][cfi]))
                                               [ueDl->mimoInfo.cwInfo[cwIdx].iTbs[1]];
         if((ue->mimoInfo.txMode != RGR_UE_TM_3) && (ue->mimoInfo.txMode != RGR_UE_TM_4))
         {
            break;
         }
      }
      ueDl->cqiFlag = 0;
   }



   (ueDl->mimoInfo.ri/2 == 0)? (ueDl->mimoInfo.cwInfo[0].noLyr = 1) :
              (ueDl->mimoInfo.cwInfo[0].noLyr = ueDl->mimoInfo.ri/2);
   ueDl->mimoInfo.cwInfo[1].noLyr = ueDl->mimoInfo.ri - ueDl->mimoInfo.cwInfo[0].noLyr;
   if (ueDl->mimoInfo.ri < 2)
   {
      ueDl->mimoInfo.btrCwIdx = 0;
   }
   else
   {
      if (ueDl->mimoInfo.cwInfo[0].eff[ueDl->mimoInfo.cwInfo[0].noLyr-1] <
          ueDl->mimoInfo.cwInfo[1].eff[ueDl->mimoInfo.cwInfo[1].noLyr-1])
      {
         ueDl->mimoInfo.btrCwIdx = 1;
      }
      else
      {
         ueDl->mimoInfo.btrCwIdx = 0;
      }
   }



   do { if (ueDl->mimoInfo.cwInfo[ueDl->mimoInfo.btrCwIdx].iTbs[1] <= 9) modOrder = 2; else if (ueDl->mimoInfo.cwInfo[ueDl->mimoInfo.btrCwIdx].iTbs[1] <= 15) modOrder = 4; else modOrder = 6;} while(0);

   maxRb = ((ueDl->maxSbSz)/(cellSch->dl.noResPerRb[cfi] * modOrder *
                   ueDl->mimoInfo.ri));
   if (cellSch->dl.isDlFreqSel)
   {

      maxRb -= maxRb % cell->rbgSize;
   }
   ueDl->maxRb = ((maxRb) <= (cellSch->dl.maxDlBwPerUe) ? (maxRb) : (cellSch->dl.maxDlBwPerUe));
   if (cellSch->dl.isDlFreqSel)
   {

      if (ueDl->maxRb % cell->rbgSize)
      {
         ueDl->maxRb += (cell->rbgSize -
                         (ueDl->maxRb % cell->rbgSize));
      }
   }

   return;
}
static Void rgSCHCmnDlHqPResetTemp
(
RgSchDlHqProcCb *hqP
)




{

   ;;



    hqP->reqLnk.node = (U32)0L;
    hqP->schdLstLnk.node = (U32)0L;

   return;
}
 Void rgSCHCmnDlUeResetTemp
(
RgSchUeCb *ue,
RgSchDlHqProcCb *hqP
)





{
   RgSchDlRbAlloc *allocInfo;
   RgSchCmnDlUe *cmnUe = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   ;;





   if((cmnUe->proc == hqP) || (cmnUe->proc == 0L))
   {
      cmnUe->proc = 0L;
      allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
      cmMemset((U8 *)allocInfo, (U8)0, sizeof(RgSchDlRbAlloc));
      allocInfo->rnti = ue->ueId;


      cmnUe->outStndAlloc = 0;
   }
   rgSCHCmnDlHqPResetTemp(hqP);

   return;
}
 Void rgSCHCmnUlUeResetTemp
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnUlUe *cmnUlUe = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));

   ;;

   cmMemset((U8 *)&cmnUlUe->alloc, (U8)0, sizeof(cmnUlUe->alloc));

   return;
}
 Void rgSCHCmnFillPdcch
(
RgSchCellCb *cell,
RgSchPdcch *pdcch,
RgSchDlRbAlloc *rbAllocInfo
)






{

   ;;



   pdcch->rnti = rbAllocInfo->rnti;
   pdcch->dci.dciFormat = rbAllocInfo->dciFormat;
   switch(rbAllocInfo->dciFormat)
   {
      case TFU_DCI_FORMAT_1A:
         pdcch->dci.u.format1aInfo.isPdcchOrder = 0;




         if (rbAllocInfo->nPrb == 3)
         {
            pdcch->dci.u.format1aInfo.t.pdschInfo.tpcCmd = 1;
         }
         else
         {
            pdcch->dci.u.format1aInfo.t.pdschInfo.tpcCmd = 0;
         }
         pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.nGap2.pres = 0;
         pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.isLocal = 1;
         pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.mcs =
                                                                   rbAllocInfo->tbInfo[0].imcs;
         pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.ndi = 0;
         pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.rv = 0;

         pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.alloc.type =
            TFU_ALLOC_TYPE_RIV;
         pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.alloc.u.riv =
            rgSCHCmnCalcRiv (cell->bwCfg.dlTotalBw,
                  rbAllocInfo->allocInfo.raType2.rbStart,
                  rbAllocInfo->allocInfo.raType2.numRb);
         break;
      case TFU_DCI_FORMAT_1:
         pdcch->dci.u.format1Info.tpcCmd = 0;





            pdcch->dci.u.format1Info.allocInfo.isAllocType0 = 1;
            pdcch->dci.u.format1Info.allocInfo.resAllocMap[0] =
               ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 24)
                & 0xff);
            pdcch->dci.u.format1Info.allocInfo.resAllocMap[1] =
               ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 16)
                & 0x00ff);
            pdcch->dci.u.format1Info.allocInfo.resAllocMap[2] =
               ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 8)
                & 0x0000ff);
            pdcch->dci.u.format1Info.allocInfo.resAllocMap[3] =
               ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask & 0x000000ff));



         pdcch->dci.u.format1Info.allocInfo.harqProcId = 0;
         pdcch->dci.u.format1Info.allocInfo.ndi = 0;
         pdcch->dci.u.format1Info.allocInfo.mcs = rbAllocInfo->tbInfo[0].imcs;
         pdcch->dci.u.format1Info.allocInfo.rv = 0;



         break;
      default:
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0012,L_ERROR,DBG_CELLID, cell->cellId,rbAllocInfo->rnti, 0, 0, 0,                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                      5535         , "Allocator's icorrect " "dciForamt Fill RNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                       ;
         break;
   }
   return;
}
 U32 rgHqRvRetxCnt[4][2];
 U32 rgUlrate_grant;
 Void rgSCHCmnFillHqPTb
(
RgSchCellCb *cell,
RgSchDlRbAlloc *rbAllocInfo,
U8 tbAllocIdx,
RgSchPdcch *pdcch
)
{
   RgSchCmnDlCell *cmnCellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchDlTbAllocInfo *tbAllocInfo = &rbAllocInfo->tbInfo[tbAllocIdx];
   RgSchDlHqTbCb *tbInfo = tbAllocInfo->tbCb;
   RgSchDlHqProcCb *hqP = tbInfo->hqP;

   ;;




   if ( tbAllocInfo->isDisabled)
   {

      tbInfo->dlGrnt.iMcs = 0;
      tbInfo->dlGrnt.rv = 1;
   }

   else if (tbInfo->txCntr > 0)
   {

      tbInfo->timingInfo = cmnCellDl->time;

      if ((tbInfo->isAckNackDtx == 4))
      {
         tbInfo->dlGrnt.iMcs = tbAllocInfo->imcs;
         rgHqRvRetxCnt[tbInfo->dlGrnt.rv][tbInfo->tbIdx]++;
      }
      else
      {
         tbInfo->dlGrnt.rv = rgSchCmnDlRvTbl[++(tbInfo->ccchSchdInfo.rvIdx) & 0x03];
      }


      tbInfo->ccchSchdInfo.totBytes = tbAllocInfo->bytesAlloc;
      ;
      rgSCHDhmHqTbRetx(hqP->hqE, tbInfo->timingInfo, hqP, tbInfo->tbIdx);
   }

   else
   {

      tbInfo->dlGrnt.iMcs = tbAllocInfo->imcs;
      tbInfo->tbSz = tbAllocInfo->bytesAlloc;
      tbInfo->timingInfo = cmnCellDl->time;
      tbInfo->dlGrnt.rv = rgSchCmnDlRvTbl[0];

      tbInfo->ccchSchdInfo.rvIdx = 0;
      tbInfo->ccchSchdInfo.totBytes = tbAllocInfo->bytesAlloc;






      cell->measurements.dlBytesCnt += tbAllocInfo->bytesAlloc;
   }


   if ( tbAllocInfo->isDisabled == 0 )
   {

      tbInfo->numLyrs = tbAllocInfo->noLyr;


      tbInfo->state = HQ_TB_WAITING;
      hqP->subFrm = rbAllocInfo->dlSf;
      tbInfo->hqP->pdcch = pdcch;
      tbInfo->dlGrnt.numRb = rbAllocInfo->rbsAlloc;




      rgSCHUtlDlHqPTbAddToTx(hqP->subFrm, hqP, tbInfo->tbIdx);
   }
   return;
}
 Void rgSCHCmnFillHqPPdcch
(
RgSchCellCb *cell,
RgSchDlRbAlloc *rbAllocInfo,
RgSchDlHqProcCb *hqP
)






{
   RgSchCmnDlCell *cmnCell = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchPdcch *pdcch = rbAllocInfo->pdcch;
   U8 tpc = 1;

   ;;

   if (hqP->hqE->ue)
   {







      {
         tpc = rgSCHPwrPucchTpcForUe(cell, hqP->hqE->ue);
      }



      pdcch->ue = hqP->hqE->ue;
      if (hqP->hqE->ue->csgMmbrSta == 0)
      {
         cmnCell->ncsgPrbCnt += rbAllocInfo->rbsAlloc;
      }
      cmnCell->totPrbCnt += rbAllocInfo->rbsAlloc;

      hqP->hqE->ue->tenbStats->stats.nonPersistent.sch[(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlPrbUsg +=
         rbAllocInfo->rbsAlloc;
      hqP->hqE->ue->tenbStats->stats.nonPersistent.sch[(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlSumCw0iTbs +=
         rbAllocInfo->tbInfo[0].iTbs;
      hqP->hqE->ue->tenbStats->stats.nonPersistent.sch[(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlNumCw0iTbs ++;
      hqP->hqE->ue->tenbStats->stats.nonPersistent.sch[(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlTpt +=
         (rbAllocInfo->tbInfo[0].bytesAlloc << 3);
      hqP->hqE->cell->tenbStats->sch.dlPrbUsage[0] +=
         rbAllocInfo->rbsAlloc;
      hqP->hqE->cell->tenbStats->sch.dlSumCw0iTbs +=
         rbAllocInfo->tbInfo[0].iTbs;
      hqP->hqE->cell->tenbStats->sch.dlNumCw0iTbs ++;
      hqP->hqE->cell->tenbStats->sch.dlTtlTpt +=
         (rbAllocInfo->tbInfo[0].bytesAlloc << 3);
      if (rbAllocInfo->tbInfo[1].schdlngForTb)
      {
         hqP->hqE->cell->tenbStats->sch.dlSumCw1iTbs +=
            rbAllocInfo->tbInfo[1].iTbs;
         hqP->hqE->cell->tenbStats->sch.dlNumCw1iTbs ++;
         hqP->hqE->ue->tenbStats->stats.nonPersistent.sch[(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlSumCw1iTbs +=
            rbAllocInfo->tbInfo[1].iTbs;
         hqP->hqE->ue->tenbStats->stats.nonPersistent.sch[(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlNumCw1iTbs ++;
         hqP->hqE->ue->tenbStats->stats.nonPersistent.sch[(U8)((hqP->hqE->cell->cellId >= rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId) ? (hqP->hqE->cell->cellId - rgSchCb[hqP->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlTpt +=
            (rbAllocInfo->tbInfo[1].bytesAlloc << 3);
         hqP->hqE->cell->tenbStats->sch.dlTtlTpt +=
            (rbAllocInfo->tbInfo[1].bytesAlloc << 3);
      }

   }

   pdcch->rnti = rbAllocInfo->rnti;
   pdcch->dci.dciFormat = rbAllocInfo->dciFormat;

   switch(rbAllocInfo->dciFormat)
   {
      case TFU_DCI_FORMAT_1:
          {
              rgSCHCmnFillHqPPdcchDciFrmt1(cell, rbAllocInfo, hqP,
                      pdcch, tpc);
              break;
          }
      case TFU_DCI_FORMAT_1A:
          {
              rgSCHCmnFillHqPPdcchDciFrmt1A(cell, rbAllocInfo, hqP,
                      pdcch, tpc);
              break;
          }
      case TFU_DCI_FORMAT_1B:
          {
              rgSCHCmnFillHqPPdcchDciFrmt1B(cell, rbAllocInfo, hqP,
                      pdcch, tpc);
              break;
          }
      case TFU_DCI_FORMAT_2:
          {
              rgSCHCmnFillHqPPdcchDciFrmt2(cell, rbAllocInfo, hqP,
                      pdcch, tpc);
              break;
          }
      case TFU_DCI_FORMAT_2A:
          {
               rgSCHCmnFillHqPPdcchDciFrmt2A(cell, rbAllocInfo, hqP,
                       pdcch, tpc);
               break;
          }
      default:
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0013,L_ERROR,DBG_CELLID, cell->cellId,rbAllocInfo->rnti, 0, 0, 0,                                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                                                6076         , "Allocator's incorrect dciForamt Fill for RNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                 ;
         break;
   }
   return;
}
static Void rgSCHCmnFillHqPPdcchDciFrmt1
(
RgSchCellCb *cell,
RgSchDlRbAlloc *rbAllocInfo,
RgSchDlHqProcCb *hqP,
RgSchPdcch *pdcch,
U8 tpc
)
{
   RgSchCmnDlHqProc *cmnHqDl = ((RgSchCmnDlHqProc *)((hqP)->sch));


    ;

    rgSCHCmnFillHqPTb(cell, rbAllocInfo, 0, pdcch);
    pdcch->dci.u.format1Info.tpcCmd = tpc;





       pdcch->dci.u.format1Info.allocInfo.isAllocType0 = 1;
       pdcch->dci.u.format1Info.allocInfo.resAllocMap[0] =
         ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 24)
               & 0xff);
       pdcch->dci.u.format1Info.allocInfo.resAllocMap[1] =
         ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 16)
               & 0x00ff);
       pdcch->dci.u.format1Info.allocInfo.resAllocMap[2] =
           ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 8)
               & 0x0000ff);
       pdcch->dci.u.format1Info.allocInfo.resAllocMap[3] =
           ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask & 0x000000ff));




    if ((!(hqP->tbInfo[0].txCntr)) &&
       (cmnHqDl != (RgSchCmnDlHqProc*)0L &&
         ((cmnHqDl->spsAction & (1 << 0)) ||
         (cmnHqDl->spsAction & ((1 << 1) | (1 << 2)))))
       )
    {
       pdcch->dci.u.format1Info.allocInfo.harqProcId = 0;
    }
    else
    {
      pdcch->dci.u.format1Info.allocInfo.harqProcId = hqP->procId;
    }




    pdcch->dci.u.format1Info.allocInfo.ndi =
                        rbAllocInfo->tbInfo[0].tbCb->ndi;
    pdcch->dci.u.format1Info.allocInfo.mcs =
                        rbAllocInfo->tbInfo[0].imcs;
    pdcch->dci.u.format1Info.allocInfo.rv =
                        rbAllocInfo->tbInfo[0].tbCb->dlGrnt.rv;
       return;
}
static Void rgSCHCmnFillHqPPdcchDciFrmt1A
(
RgSchCellCb *cell,
RgSchDlRbAlloc *rbAllocInfo,
RgSchDlHqProcCb *hqP,
RgSchPdcch *pdcch,
U8 tpc
)
{






   RgSchCmnDlHqProc *cmnHqDl = ((RgSchCmnDlHqProc *)((hqP)->sch));


    ;

    rgSCHCmnFillHqPTb(cell, rbAllocInfo, 0, pdcch);
    pdcch->dci.u.format1aInfo.isPdcchOrder = 0;
    pdcch->dci.u.format1aInfo.t.pdschInfo.tpcCmd = tpc;
    pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.mcs =
      rbAllocInfo->tbInfo[0].imcs;
    pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.harqProcId.pres = 1;

    if ((!(hqP->tbInfo[0].txCntr)) &&
       ( cmnHqDl != (RgSchCmnDlHqProc*)0L &&
         ((cmnHqDl->spsAction & (1 << 0)) ||
         (cmnHqDl->spsAction & ((1 << 1) | (1 << 2))))
       ))
    {
       pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.harqProcId.val = 0;
    }
    else
    {
      pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.harqProcId.val
                                                = hqP->procId;
    }




    pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.ndi =
       rbAllocInfo->tbInfo[0].tbCb->ndi;
    pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.rv =
       rbAllocInfo->tbInfo[0].tbCb->dlGrnt.rv;

    pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.isLocal = 1;
    pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.nGap2.pres = 0;
    pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.alloc.type =
            TFU_ALLOC_TYPE_RIV;
    pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.alloc.u.riv =
    rgSCHCmnCalcRiv (cell->bwCfg.dlTotalBw,
                  rbAllocInfo->allocInfo.raType2.rbStart,
                  rbAllocInfo->allocInfo.raType2.numRb);
    return;
}
static Void rgSCHCmnFillHqPPdcchDciFrmt1B
(
RgSchCellCb *cell,
RgSchDlRbAlloc *rbAllocInfo,
RgSchDlHqProcCb *hqP,
RgSchPdcch *pdcch,
U8 tpc
)
{






   RgSchCmnDlHqProc *cmnHqDl = ((RgSchCmnDlHqProc *)((hqP)->sch));


    ;

    rgSCHCmnFillHqPTb(cell, rbAllocInfo, 0, pdcch);
    pdcch->dci.u.format1bInfo.tpcCmd = tpc;
    pdcch->dci.u.format1bInfo.allocInfo.mcs =
           rbAllocInfo->tbInfo[0].imcs;

    if ((!(hqP->tbInfo[0].txCntr)) &&
       ( cmnHqDl != (RgSchCmnDlHqProc*)0L &&
         ((cmnHqDl->spsAction & (1 << 0)) ||
         (cmnHqDl->spsAction & ((1 << 1) | (1 << 2))))
       ))
    {
       pdcch->dci.u.format1bInfo.allocInfo.harqProcId = 0;
    }
    else
    {
      pdcch->dci.u.format1bInfo.allocInfo.harqProcId = hqP->procId;
    }



    pdcch->dci.u.format1bInfo.allocInfo.ndi =
          rbAllocInfo->tbInfo[0].tbCb->ndi;
    pdcch->dci.u.format1bInfo.allocInfo.rv =
           rbAllocInfo->tbInfo[0].tbCb->dlGrnt.rv;

    pdcch->dci.u.format1bInfo.allocInfo.isLocal = 1;
    pdcch->dci.u.format1bInfo.allocInfo.nGap2.pres = 0;
    pdcch->dci.u.format1bInfo.allocInfo.alloc.type =
            TFU_ALLOC_TYPE_RIV;
    pdcch->dci.u.format1bInfo.allocInfo.alloc.u.riv =
    rgSCHCmnCalcRiv (cell->bwCfg.dlTotalBw,
                  rbAllocInfo->allocInfo.raType2.rbStart,
                  rbAllocInfo->allocInfo.raType2.numRb);

    pdcch->dci.u.format1bInfo.allocInfo.pmiCfm =
               rbAllocInfo->mimoAllocInfo.precIdxInfo >> 4;
    pdcch->dci.u.format1bInfo.allocInfo.tPmi =
               rbAllocInfo->mimoAllocInfo.precIdxInfo & 0x0F;
    return;

}
static Void rgSCHCmnFillHqPPdcchDciFrmt2
(
RgSchCellCb *cell,
RgSchDlRbAlloc *rbAllocInfo,
RgSchDlHqProcCb *hqP,
RgSchPdcch *pdcch,
U8 tpc
)
{
   RgSchCmnDlHqProc *cmnHqDl = ((RgSchCmnDlHqProc *)((hqP)->sch));


    ;

    rgSCHCmnFillHqPTb(cell, rbAllocInfo, 0, pdcch);

    if (rbAllocInfo->tbInfo[1].schdlngForTb ||
        rbAllocInfo->tbInfo[1].isDisabled)
    {
        rgSCHCmnFillHqPTb(cell, rbAllocInfo, 1, pdcch);
    }
    pdcch->dci.u.format2Info.tpcCmd = tpc;





        pdcch->dci.u.format2Info.allocInfo.isAllocType0 = 1;
        pdcch->dci.u.format2Info.allocInfo.resAllocMap[0] =
          ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 24)
               & 0xff);
        pdcch->dci.u.format2Info.allocInfo.resAllocMap[1] =
           ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 16)
               & 0x00ff);
        pdcch->dci.u.format2Info.allocInfo.resAllocMap[2] =
               ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 8)
                & 0x0000ff);
        pdcch->dci.u.format2Info.allocInfo.resAllocMap[3] =
               ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask & 0x000000ff));




    if ((!(hqP->tbInfo[0].txCntr)) &&
       ( cmnHqDl != (RgSchCmnDlHqProc*)0L &&
         ((cmnHqDl->spsAction & (1 << 0)) ||
         (cmnHqDl->spsAction & ((1 << 1) | (1 << 2))))
       ))
    {
       pdcch->dci.u.format2Info.allocInfo.harqProcId = 0;
    }
    else
    {
      pdcch->dci.u.format2Info.allocInfo.harqProcId = hqP->procId;
    }




     pdcch->dci.u.format2Info.allocInfo.tbInfo[0].mcs = 0;
     pdcch->dci.u.format2Info.allocInfo.tbInfo[0].rv = 1;
     pdcch->dci.u.format2Info.allocInfo.tbInfo[1].mcs = 0;
     pdcch->dci.u.format2Info.allocInfo.tbInfo[1].rv = 1;

     pdcch->dci.u.format2Info.allocInfo.tbInfo[rbAllocInfo->tbInfo[0].
        tbCb->tbIdx].ndi = rbAllocInfo->tbInfo[0].tbCb->ndi;
     pdcch->dci.u.format2Info.allocInfo.tbInfo[rbAllocInfo->tbInfo[0].
        tbCb->tbIdx].mcs = rbAllocInfo->tbInfo[0].imcs;
     pdcch->dci.u.format2Info.allocInfo.tbInfo[rbAllocInfo->tbInfo[0].
            tbCb->tbIdx].rv = rbAllocInfo->tbInfo[0].tbCb->dlGrnt.rv;



     if (rbAllocInfo->tbInfo[1].schdlngForTb == 1)
     {
            pdcch->dci.u.format2Info.allocInfo.tbInfo[rbAllocInfo->tbInfo[1].
                tbCb->tbIdx].ndi = rbAllocInfo->tbInfo[1].tbCb->ndi;
            pdcch->dci.u.format2Info.allocInfo.tbInfo[rbAllocInfo->tbInfo[1].
                tbCb->tbIdx].mcs = rbAllocInfo->tbInfo[1].imcs;
            pdcch->dci.u.format2Info.allocInfo.tbInfo[rbAllocInfo->tbInfo[1].
                tbCb->tbIdx].rv = rbAllocInfo->tbInfo[1].tbCb->dlGrnt.rv;
     }
     pdcch->dci.u.format2Info.allocInfo.transSwap =
             rbAllocInfo->mimoAllocInfo.swpFlg;
     pdcch->dci.u.format2Info.allocInfo.precoding =
             rbAllocInfo->mimoAllocInfo.precIdxInfo;
     return;
}
static Void rgSCHCmnFillHqPPdcchDciFrmt2A
(
RgSchCellCb *cell,
RgSchDlRbAlloc *rbAllocInfo,
RgSchDlHqProcCb *hqP,
RgSchPdcch *pdcch,
U8 tpc
)
{





   RgSchCmnDlHqProc *cmnHqDl = ((RgSchCmnDlHqProc *)((hqP)->sch));


    ;

    rgSCHCmnFillHqPTb(cell, rbAllocInfo, 0, pdcch);

    if (rbAllocInfo->tbInfo[1].schdlngForTb ||
          rbAllocInfo->tbInfo[1].isDisabled)
    {

        rgSCHCmnFillHqPTb(cell, rbAllocInfo, 1, pdcch);
    }

    pdcch->dci.u.format2AInfo.tpcCmd = tpc;





        pdcch->dci.u.format2AInfo.allocInfo.isAllocType0 = 1;
        pdcch->dci.u.format2AInfo.allocInfo.resAllocMap[0] =
              ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 24)
               & 0xff);
        pdcch->dci.u.format2AInfo.allocInfo.resAllocMap[1] =
              ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 16)
               & 0x00ff);
        pdcch->dci.u.format2AInfo.allocInfo.resAllocMap[2] =
               ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask >> 8)
                & 0x0000ff);
        pdcch->dci.u.format2AInfo.allocInfo.resAllocMap[3] =
               ((rbAllocInfo->allocInfo.raType0.dlAllocBitMask & 0x000000ff));




    if ((!(hqP->tbInfo[0].txCntr)) &&
       ( cmnHqDl != (RgSchCmnDlHqProc*)0L &&
         ((cmnHqDl->spsAction & (1 << 0)) ||
         (cmnHqDl->spsAction & ((1 << 1) | (1 << 2))))
       ))
    {
       pdcch->dci.u.format2AInfo.allocInfo.harqProcId = 0;
    }
    else
    {
      pdcch->dci.u.format2AInfo.allocInfo.harqProcId = hqP->procId;
    }




    pdcch->dci.u.format2AInfo.allocInfo.tbInfo[0].mcs = 0;
    pdcch->dci.u.format2AInfo.allocInfo.tbInfo[0].rv = 1;
    pdcch->dci.u.format2AInfo.allocInfo.tbInfo[1].mcs = 0;
    pdcch->dci.u.format2AInfo.allocInfo.tbInfo[1].rv = 1;

    pdcch->dci.u.format2AInfo.allocInfo.tbInfo[rbAllocInfo->tbInfo[0].
            tbCb->tbIdx].ndi = rbAllocInfo->tbInfo[0].tbCb->ndi;
    pdcch->dci.u.format2AInfo.allocInfo.tbInfo[rbAllocInfo->tbInfo[0].
            tbCb->tbIdx].mcs = rbAllocInfo->tbInfo[0].imcs;
    pdcch->dci.u.format2AInfo.allocInfo.tbInfo[rbAllocInfo->tbInfo[0].
            tbCb->tbIdx].rv = rbAllocInfo->tbInfo[0].tbCb->dlGrnt.rv;




    if (rbAllocInfo->tbInfo[1].schdlngForTb == 1)
    {
            pdcch->dci.u.format2AInfo.allocInfo.tbInfo[rbAllocInfo->tbInfo[1].
               tbCb->tbIdx].ndi = rbAllocInfo->tbInfo[1].tbCb->ndi;
            pdcch->dci.u.format2AInfo.allocInfo.tbInfo[rbAllocInfo->tbInfo[1].
               tbCb->tbIdx].mcs = rbAllocInfo->tbInfo[1].imcs;
            pdcch->dci.u.format2AInfo.allocInfo.tbInfo[rbAllocInfo->tbInfo[1].
               tbCb->tbIdx].rv = rbAllocInfo->tbInfo[1].tbCb->dlGrnt.rv;

    }
    pdcch->dci.u.format2AInfo.allocInfo.transSwap =
            rbAllocInfo->mimoAllocInfo.swpFlg;
    pdcch->dci.u.format2AInfo.allocInfo.precoding =
            rbAllocInfo->mimoAllocInfo.precIdxInfo;
    return;
}
static Void rgSCHCmnInitVars
(
RgSchCellCb *cell
)




{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);

   ;;

   cellUl->idx = 0xff;
   cellUl->schdIdx = 0xff;
   cellUl->schdHqProcIdx = 0xff;
   cellUl->msg3SchdIdx = 0xff;
   cellUl->msg3SchdHqProcIdx = 0xff;
   cellUl->rcpReqIdx = 0xff;
   cellUl->hqFdbkIdx[0] = 0xff;
   cellUl->hqFdbkIdx[1] = 0xff;
   cellUl->reTxIdx[0] = 0xff;
   cellUl->reTxIdx[1] = 0xff;

  return;

}
 Void rgSCHCmnUpdVars
(
RgSchCellCb *cell
)




{
   CmLteTimingInfo timeInfo;
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   U16 idx;

   ;;

   idx = (cell->crntTime.sfn * 10 + cell->crntTime.subframe);
   cellUl->idx = ((idx) % (8 +8));






   idx = (cellUl->idx + (4 - 2) + 4);
   cellUl->schdIdx = ((idx) % (8 +8));

   { U32 absoluteTime; absoluteTime = cell->crntTime.sfn * 10 + cell->crntTime.subframe; absoluteTime += (4 - 2) + 4; timeInfo.sfn = absoluteTime/10; timeInfo.subframe = absoluteTime % 10;}

   cellUl->schdHqProcIdx = rgSCHCmnGetUlHqProcIdx(&timeInfo, cell);


   cellUl->schdTime = timeInfo;


   idx = (cellUl->idx + (2 + 0) + 6);
   cellUl->msg3SchdIdx = ((idx) % (8 +8));

   { U32 absoluteTime; absoluteTime = cell->crntTime.sfn * 10 + cell->crntTime.subframe; absoluteTime += (2 + 0)+ 6; timeInfo.sfn = absoluteTime/10; timeInfo.subframe = absoluteTime % 10;}

   cellUl->msg3SchdHqProcIdx = rgSCHCmnGetUlHqProcIdx(&timeInfo, cell);




   { U32 absoluteTime; absoluteTime = cell->crntTime.sfn * 10 + cell->crntTime.subframe; absoluteTime += (2 + 0)+ 6 + 1; timeInfo.sfn = absoluteTime/10; timeInfo.subframe = absoluteTime % 10;}
                                                            ;
   cellUl->spsUlRsrvIdx = (cellUl->msg3SchdIdx+1) % 8 +8;
   cellUl->spsUlRsrvHqProcIdx = cellUl->schdHqProcIdx;


   idx = (cellUl->idx + 2);

   cellUl->rcpReqIdx = ((idx) % (8 +8));




   idx = (cellUl->idx - 2 + 8 +8);
   cellUl->hqFdbkIdx[0] = (idx % (8 +8));

   idx = ((cellUl->schdIdx) % (8 +8));

   cellUl->reTxIdx[0] = (U8) idx;



   rgSCHCmnUpdRachParam(cell);

   return;
}
 U8 rgSCHCmnGetUlHqProcIdx
(
CmLteTimingInfo *timeInfo,
RgSchCellCb *cell
)





{
   U8 procId;
   U32 numUlSf;


   numUlSf = (timeInfo->sfn * 10 + timeInfo->subframe);
   procId = numUlSf % 8;
   return(procId);
}
 Void rgSCHCmnUlFreeAlloc
(
RgSchCellCb *cell,
RgSchUlAlloc *alloc
)





{
   RgSchUlHqProcCb *hqProc;
   ;;

   if (alloc->forMsg3)
   {

      if ((alloc->hqProc->remTx == 0) &&
          (alloc->hqProc->rcvdCrcInd == 0) &&
          (alloc->raCb))
      {
         RgSchRaCb *raCb = alloc->raCb;
         rgSCHUhmFreeProc(alloc->hqProc, cell);
         rgSCHUtlUlAllocRelease(alloc);
         rgSCHRamDelRaCb(cell, raCb, 1);
         return;
      }
   }

   hqProc = alloc->hqProc;
   rgSCHUtlUlAllocRelease(alloc);
   rgSCHUhmFreeProc(hqProc, cell);
   return;
}
 Void rgSCHCmnUlFreeAllocation
(
RgSchCellCb *cell,
RgSchUlSf *sf,
RgSchUlAlloc *alloc
)






{
   RgSchUlHqProcCb *hqProc;

   ;;

   if (alloc->forMsg3)
   {

      if ((alloc->hqProc->remTx == 0) &&
          (alloc->hqProc->rcvdCrcInd == 0) &&
          (alloc->raCb))
      {
         RgSchRaCb *raCb = alloc->raCb;
         rgSCHUhmFreeProc(alloc->hqProc, cell);
         rgSCHUtlUlAllocRls(sf, alloc);
         rgSCHRamDelRaCb(cell, raCb, 1);
         return;
      }
   }

   hqProc = alloc->hqProc;
   rgSCHUhmFreeProc(hqProc, cell);




   rgSCHUtlUlAllocRls(sf, alloc);

   return;
}
 RgSchPdcch *rgSCHCmnPdcchAllocCrntSf
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   CmLteTimingInfo frm = cell->crntTime;
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   RgSchDlSf *sf;
   U32 y;
   RgSchPdcch *pdcch = 0L;

   ;;
   do { if ((frm.subframe += (4 - 2)) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);
   sf = rgSCHUtlSubFrmGet(cell, frm);

   y = rgSCHUtlGetY(ue, sf->sfNum);
   {
      pdcch = rgSCHCmnPdcchAlloc(cell, ue, sf, y, ueDl->mimoInfo.cwInfo[0].cqi, TFU_DCI_FORMAT_0, 0);
   }
   return(pdcch);
}
 Void rgSCHCmnUlAllocFillNdmrs
(
RgSchCmnUlCell *cellUl,
RgSchUlAlloc *alloc
)





{
   ;;
   alloc->grnt.nDmrs = cellUl->dmrsArr[alloc->sbStart];
   return;
}
 Void rgSCHCmnUlAllocLnkHqProc
(
RgSchUeCb *ue,
RgSchUlAlloc *alloc,
RgSchUlHqProcCb *proc,
Bool isRetx
)







{
   ;;

   if(1 == isRetx)
   {
      rgSCHCmnUlAdapRetx(alloc, proc);
   }
   else
   {



      rgSCHUhmNewTx(proc, ((RgUeUlHqCb*)proc->hqEnt)->maxHqRetx, alloc);
   }
   return;
}
 Void rgSCHCmnPdcchRlsCrntSf
(
RgSchCellCb *cell,
RgSchPdcch *pdcch
)





{
   CmLteTimingInfo frm = cell->crntTime;
   RgSchDlSf *sf;

   ;;

   do { if ((frm.subframe += (4 - 2)) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);
   sf = rgSCHUtlSubFrmGet(cell, frm);
   rgSCHUtlPdcchPut(cell, &sf->pdcchInfo, pdcch);
   return;
}
 Void rgSCHCmnUlFillPdcchWithAlloc
(
RgSchPdcch *pdcch,
RgSchUlAlloc *alloc,
RgSchUeCb *ue
)






{
   ;;

   pdcch->ue = ue;
   pdcch->rnti = alloc->rnti;
   pdcch->dci.dciFormat = TFU_DCI_FORMAT_0;
   pdcch->dci.u.format0Info.hoppingEnbld = alloc->grnt.hop;
   pdcch->dci.u.format0Info.rbStart = alloc->grnt.rbStart;
   pdcch->dci.u.format0Info.numRb = alloc->grnt.numRb;
   pdcch->dci.u.format0Info.mcs = alloc->grnt.iMcsCrnt;
   pdcch->dci.u.format0Info.ndi = alloc->hqProc->ndi;
   pdcch->dci.u.format0Info.nDmrs = alloc->grnt.nDmrs;
   pdcch->dci.u.format0Info.tpcCmd = alloc->grnt.tpc;



   pdcch->dci.u.format0Info.isSrGrant = ue->isSrGrant;



   pdcch->dci.u.format0Info.isMsg4PdcchWithCrnti = ue->isMsg4PdcchWithCrnti;
   ue->isMsg4PdcchWithCrnti = 0;




   if (ue->dl.acqiResGrntd)
   {
      pdcch->dci.u.format0Info.cqiReq = ue->dl.reqForCqi;

      ue->dl.acqiResGrntd = 0;
      ue->dl.reqForCqi = RG_SCH_APCQI_NO;
   }
   else
   {
      pdcch->dci.u.format0Info.cqiReq = RG_SCH_APCQI_NO;
   }
   pdcch->dci.u.format0Info.numCqiBit = 1;
   if (pdcch->pdcchSearchSpace == RG_SCH_UE_SPECIFIC_SEARCH_SPACE)
   {






      pdcch->dciNumOfBits = ue->dciSize.dedSize[TFU_DCI_FORMAT_0];
   }
   else
   {
      pdcch->dciNumOfBits = ue->dciSize.cmnSize[TFU_DCI_FORMAT_0];
   }
   ue->dl.reqForCqi = RG_SCH_APCQI_NO;






   pdcch->dci.u.format0Info.hqProcId = alloc->hqProc->procId;

   if (ue->ul.ulTxAntSel.selType == RGR_UE_TX_ANT_CLOSEDLOOP)
   {
      pdcch->dci.u.format0Info.txAntenna = ue->validTxAnt;
   }

   else
   {
      pdcch->dci.u.format0Info.txAntenna = 0;
   }
   return;
}
 Void rgSCHCmnUlAllocFillTpc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchUlAlloc *alloc
)






{
   ;;
   alloc->grnt.tpc = rgSCHPwrPuschTpcForUe(cell, ue);
   return;
}
static Void rgSCHCmnAddUeToRefreshQ
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U32 wait
)






{
   RgSchCmnCell *sched = ((RgSchCmnCell *)((cell)->sc.sch));
   CmTmrArg arg;
   RgSchCmnUeInfo *ueSchd = &(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn);

   ;;
   (cell=cell);

   cmMemset((U8 *)&arg, 0, sizeof(arg));
   arg.tqCp = &sched->tmrTqCp;
   arg.tq = sched->tmrTq;
   arg.timers = &ueSchd->tmr;
   arg.cb = (U32)ue;
   arg.tNum = 0;
   arg.max = 1;
   arg.evnt = 1;
   arg.wait = wait;
   cmPlcCbTq(&arg);
   return;
}
static Void rgSCHCmnUlUeReset
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   U8 lcgCnt=0;
   RgSchCmnLcg *lcgCmn;
   CmLList *node;
   RgSchCmnAllocRecord *allRcd;
   ;;

   ue->ul.minReqBytes = 0;
   ue->ul.totalBsr = 0;
   ue->ul.effBsr = 0;
   ue->ul.nonGbrLcgBs = 0;
   ue->ul.effAmbr = ue->ul.cfgdAmbr;

   node = ueUl->ulAllocLst.first;
   while (node)
   {
      allRcd = (RgSchCmnAllocRecord *)node->node;
      allRcd->alloc = 0;
      node = node->next;
   }
   for(lcgCnt = 0; lcgCnt < 4; lcgCnt++)
   {
      lcgCmn = ((RgSchCmnLcg *)((&ue->ul.lcgArr[lcgCnt])->sch));
      lcgCmn->bs = 0;
      lcgCmn->reportedBs = 0;
      lcgCmn->effGbr = lcgCmn->cfgdGbr;
      lcgCmn->effDeltaMbr = lcgCmn->deltaMbr;
   }
   rgSCHCmnUlUeDelAllocs(cell, ue);

   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
      rgSCHCmnSpsUlUeReset(cell, ue);
   }

   ue->isSrGrant = 0;
   cellSchd->apisUl->rgSCHUlUeReset(cell, ue);


   return;

}
static Void rgSCHCmnResetRiCqi
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnUe *ueSchCmn = ((RgSchCmnUe *)((ue->cellInfo[(ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)])])->sch));
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));

   ;;

   rgSCHCmnUpdUeUlCqiInfo(cell, ue, ueUl, ueSchCmn, cellSchd,
         cell->isCpUlExtend);

   ueDl->mimoInfo.cwInfo[0].cqi = cellSchd->dl.ccchCqi;
   ueDl->mimoInfo.cwInfo[1].cqi = cellSchd->dl.ccchCqi;
   ueDl->mimoInfo.ri = 1;
   if ((ue->mimoInfo.txMode == RGR_UE_TM_4) ||
          (ue->mimoInfo.txMode == RGR_UE_TM_6))
   {
      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x02); };
   }
   if (ue->mimoInfo.txMode == RGR_UE_TM_3)
   {
      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x01); };
   }
   rgSCHCmnDlSetUeAllocLmt(cell, ueDl);



   RgSchUeACqiCb *acqiCb = &(((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->acqiCb));
   if(acqiCb && acqiCb->aCqiCfg.pres)
   {
      acqiCb->aCqiTrigWt = 0;
   }


   return;
}
static Void rgSCHCmnDlUeReset
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlCell *cellCmnDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   ;;

   if (ueDl->rachInfo.poLnk.node != 0L)
   {
      rgSCHCmnDlRmvFrmPdcchOdrQ(cell, ue);
   }



   if (ue->dlTaLnk.node)
   {
      cmLListDelFrm(&cellCmnDl->taLst, &ue->dlTaLnk);
      ue->dlTaLnk.node = (U32)0L;
   }
   else if (ue->taTmr.tmrEvnt != -1)
   {
      rgSCHTmrStopTmr(cell, ue->taTmr.tmrEvnt, ue);
   }



   if (ue->dl.dlSpsCfg.isDlSpsEnabled)
   {
      rgSCHCmnSpsDlUeReset(cell, ue);
   }

   cellSchd->apisDl->rgSCHDlUeReset(cell, ue);






}
 Void rgSCHCmnUeReset
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   U8 idx;
   ;;

   rgSCHCmnDelRachInfo(cell, ue);

   rgSCHPwrUeReset(cell, ue);

   rgSCHCmnUlUeReset(cell, ue);
   rgSCHCmnDlUeReset(cell, ue);




   for (idx = 0;idx < 8; idx++)
   {
      if (ue->cellInfo[idx] != 0L)
      {
         rgSCHCmnResetRiCqi(ue->cellInfo[idx]->cell, ue);
      }
   }

   RgSchUeCellInfo *pCellInfo = (ue->cellInfo[0]);
   if(pCellInfo->acqiCb.aCqiCfg.pres)
   {
      ue->dl.reqForCqi = RG_SCH_APCQI_SERVING_CC;
   }
   return;
}
 Void rgSCHCmnActvtUlUe
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;

   cellSchd->apisUl->rgSCHUlActvtUe(cell, ue);
   return;
}
 Void rgSCHCmnActvtDlUe
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;

   cellSchd->apisDl->rgSCHDlActvtUe(cell, ue);
   return;
}
 Void rgSCHCmnHdlUlTransInd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
CmLteTimingInfo timingInfo
)






{
   ;;


   ue->ul.ulTransTime.sfn = timingInfo.sfn; ue->ul.ulTransTime.subframe = timingInfo.subframe;;
   if ((ue->ul.ulInactvMask & 0x04))
   {


      if((ue->dl.dlInactvMask == 0)) { ue->dl.dlInactvMask &= ~0x04; } else { ue->dl.dlInactvMask &= ~0x04; if((ue->dl.dlInactvMask == 0)) { rgSCHUtlDlActvtUe(cell, ue); } };
      if((ue->ul.ulInactvMask == 0)) { ue->ul.ulInactvMask &= ~0x04; } else { ue->ul.ulInactvMask &= ~0x04; if((ue->ul.ulInactvMask == 0)) { rgSCHUtlUlActvtUe(cell, ue); } };
   }
   return;
}
static RgSchCmnRank rgSCHCmnComp4TxMode4
(
 U32 *pmiBitMap
 )




{
   U32 bitMap0, bitMap1;
   ;;
   bitMap0 = pmiBitMap[0];
   bitMap1 = pmiBitMap[1];
   if((bitMap1) & 0xFFFF)
   {
      return(RG_SCH_CMN_RANK_1);
   }
   else if((bitMap1>>16) & 0xFFFF)
   {
      return(RG_SCH_CMN_RANK_2);
   }
   else if((bitMap0) & 0xFFFF)
   {
      return(RG_SCH_CMN_RANK_3);
   }
   else if((bitMap0>>16) & 0xFFFF)
   {
      return(RG_SCH_CMN_RANK_4);
   }
   else
   {
      return(RG_SCH_CMN_RANK_1);
   }
}
static RgSchCmnRank rgSCHCmnComp2TxMode4
(
 U32 *pmiBitMap
 )




{
   U32 bitMap0;
   ;;
   bitMap0 = pmiBitMap[0];
   if((bitMap0>>26)& 0x0F)
   {
      return(RG_SCH_CMN_RANK_1);
   }
   else if((bitMap0>>30) & 3)
   {
      return(RG_SCH_CMN_RANK_2);
   }
   else
   {
      return(RG_SCH_CMN_RANK_1);
   }
}
static RgSchCmnRank rgSCHCmnComp4TxMode3
(
 U32 *pmiBitMap
 )




{
   U32 bitMap0;
   ;;
   bitMap0 = pmiBitMap[0];
   if((bitMap0>>28)& 1)
   {
      return(RG_SCH_CMN_RANK_1);
   }
   else if((bitMap0>>29) &1)
   {
      return(RG_SCH_CMN_RANK_2);
   }
   else if((bitMap0>>30) &1)
   {
      return(RG_SCH_CMN_RANK_3);
   }
   else if((bitMap0>>31) &1)
   {
      return(RG_SCH_CMN_RANK_4);
   }
   else
   {
      return(RG_SCH_CMN_RANK_1);
   }
}
static RgSchCmnRank rgSCHCmnComp2TxMode3
(
 U32 *pmiBitMap
 )




{
   U32 bitMap0;
   ;;
   bitMap0 = pmiBitMap[0];
   if((bitMap0>>30)& 1)
   {
      return(RG_SCH_CMN_RANK_1);
   }
   else if((bitMap0>>31) &1)
   {
      return(RG_SCH_CMN_RANK_2);
   }
   else
   {
      return(RG_SCH_CMN_RANK_1);
   }
}
static RgSchCmnRank rgSCHCmnComputeRank
(
 RgrTxMode txMode,
 U32 *pmiBitMap,
 U8 numTxPorts
 )






{
   ;;

   if (numTxPorts ==2 && txMode == RGR_UE_TM_3)
   {
      return(rgSCHCmnComp2TxMode3(pmiBitMap));
   }
   else if (numTxPorts ==4 && txMode == RGR_UE_TM_3)
   {
      return(rgSCHCmnComp4TxMode3(pmiBitMap));
   }
   else if (numTxPorts ==2 && txMode == RGR_UE_TM_4)
   {
      return(rgSCHCmnComp2TxMode4(pmiBitMap));
   }
   else if (numTxPorts ==4 && txMode == RGR_UE_TM_4)
   {
      return(rgSCHCmnComp4TxMode4(pmiBitMap));
   }
   else
   {
      return(RG_SCH_CMN_RANK_1);
   }
}
 Void rgSCHCmnDlDeInitHqEnt
(
RgSchCellCb *cell,
RgSchDlHqEnt *hqE
)





{
   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchDlHqProcCb *hqP;
   U8 cnt;
   S16 ret;

   ;;
   ret = cellSchd->apisDl->rgSCHDlUeHqEntDeInit(cell, hqE);


   if(1 == ret)
   {
   }

   for(cnt = 0; cnt < hqE->numHqPrcs; cnt++)
   {
      hqP = &hqE->procs[cnt];
      if ((((RgSchCmnDlHqProc *)((hqP)->sch))))
      {
         rgSCHUtlFreeSBuf(cell->instIdx,
              (Data**)(&(hqP->sch)), (sizeof(RgSchCmnDlHqProc)));
      }
   }
   return;
}
 S16 rgSCHCmnDlInitHqEnt
(
RgSchCellCb *cell,
RgSchDlHqEnt *hqEnt
)






{
   RgSchDlHqProcCb *hqP;
   U8 cnt;

   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;

   for(cnt = 0; cnt < hqEnt->numHqPrcs; cnt++)
   {
      hqP = &hqEnt->procs[cnt];
      if (rgSCHUtlAllocSBuf(cell->instIdx,
               (Data**)&(hqP->sch), (sizeof(RgSchCmnDlHqProc))) != 0)
      {
         return(1);
      }

      hqP->laaHqP.procId = 0xff;
   }

   if(0 != cellSchd->apisDl->rgSCHDlUeHqEntInit(cell, hqEnt))
   {
      return(1);
   }

   return(0);
}
static U8 rgSCHCmnGetRefreshDist
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   U8 refOffst;

   Inst inst = cell->instIdx;

   ;;

   for(refOffst = 0; refOffst < 16; refOffst++)
   {
      if(cell->refreshUeCnt[refOffst] < 4)
      {
         cell->refreshUeCnt[refOffst]++;
         ue->refreshOffset = refOffst;

         return(refOffst);
      }
   }

   { if ((&rgSchCb[inst].rgSchInit)->dbgMask & ((0x00000100 << 1))) { snprintf((&rgSchCb[inst].rgSchInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "MAC Scheduler", (&rgSchCb[inst].rgSchInit)->procId, (&rgSchCb[inst].rgSchInit)->ent, (&rgSchCb[inst].rgSchInit)->inst, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c", 8435); SPrint((&rgSchCb[inst].rgSchInit)->prntBuf); sprintf (rgSchCb[inst].rgSchInit.prntBuf, "Allocation of refresh distribution failed\n"); SPrint((&rgSchCb[inst].rgSchInit)->prntBuf); } };

   cell->refreshUeCnt[refOffst-1]++;
   ue->refreshOffset = refOffst-1;

   return(refOffst-1);
}
static Void rgSCHCmnGetRefreshPer
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U32 *waitPer
)






{
   U32 refreshPer;
   U32 crntSubFrm;

   ;;

   refreshPer = 32 * 10;
   crntSubFrm = cell->crntTime.sfn * 10 + cell->crntTime.subframe;

   *waitPer = refreshPer - (crntSubFrm % refreshPer);
   *waitPer = (((*waitPer) + (10)-1) / (10));
   *waitPer = *waitPer + rgSCHCmnGetRefreshDist(cell, ue);

   return;
}
 S16 rgSCHCmnRgrUeCfg
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgrUeCfg *ueCfg,
RgSchErrInfo *err
)







{
   RgSchDlRbAlloc *allocInfo;
   S16 ret;
   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnUe *ueSchCmn;
   RgSchCmnUlUe *ueUl;
   RgSchCmnDlUe *ueDl;
   U8 cnt;
   RgSchCmnAllocRecord *allRcd;
   U32 waitPer;
   U32 idx = (U8)((cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1));
   RgSchUeCellInfo *pCellInfo = (ue->cellInfo[0]);
   ;;



   if((rgSCHUtlAllocSBuf(cell->instIdx,
               (Data**)&(((ue->cellInfo[ue->cellIdToCellIdxMap[idx]])->sch)), (sizeof(RgSchCmnUe))) != 0))
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0014,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                8827      , "Memory allocation FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                 ;
      err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
      return(1);
   }
   ueSchCmn = ((RgSchCmnUe *)((ue->cellInfo[(ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)])])->sch));
   ue->dl.ueDlCqiCfg = ueCfg->ueDlCqiCfg;
   pCellInfo->acqiCb.aCqiCfg = ueCfg->ueDlCqiCfg.aprdCqiCfg;
   if(ueCfg->ueCatEnum > 0 )
   {

      ueSchCmn->cmn.ueCat = ueCfg->ueCatEnum - 1;
   }
   else
   {
      ueSchCmn->cmn.ueCat = 0;
   }
   cmInitTimers(&ueSchCmn->cmn.tmr, 1);


   ueDl = &ueSchCmn->dl;


   if (ueCfg->dedPreambleId.pres == 1)
   {

      rgSCHCmnDelDedPreamble(cell, ueCfg->dedPreambleId.val);

      ueDl->rachInfo.hoRapId = ueCfg->dedPreambleId.val;
      cmLListAdd2Tail(&cellSchd->rachCfg.hoUeLst, &ueDl->rachInfo.hoLnk);
      ueDl->rachInfo.hoLnk.node = (U32)ue;
   }

   rgSCHCmnUpdUeMimoInfo(ueCfg, ueDl, cell, cellSchd);

   if (ueCfg->txMode.pres == 1)
   {
      if ((ueCfg->txMode.txModeEnum == RGR_UE_TM_4) ||
            (ueCfg->txMode.txModeEnum == RGR_UE_TM_6))
      {
         { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x02); };
      }
      if (ueCfg->txMode.txModeEnum == RGR_UE_TM_3)
      {
         { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x01); };
      }
   }
   ;
   ueDl->maxTbBits = rgUeCatTbl[ueSchCmn->cmn.ueCat].maxDlTbBits;

   U8 ri = 0;
   ri = ((ri) <= (cell->numTxAntPorts) ? (ri) : (cell->numTxAntPorts));
   if(((CM_LTE_UE_CAT_6 == ueSchCmn->cmn.ueCat )
            ||(CM_LTE_UE_CAT_7 == ueSchCmn->cmn.ueCat))
                  && (4 == ri))
   {
      ueDl->maxTbSz = rgUeCatTbl[ueSchCmn->cmn.ueCat].maxDlBits[1];
   }
   else
   {
      ueDl->maxTbSz = rgUeCatTbl[ueSchCmn->cmn.ueCat].maxDlBits[0];
   }






   ueDl->maxSbSz = (rgUeCatTbl[ueSchCmn->cmn.ueCat].maxSftChBits/
         8);

   rgSCHCmnDlSetUeAllocLmt(cell, ueDl);
   if (ueCfg->ueQosCfg.ambrPres)
   {

      ue->dl.ambrCfgd = (ueCfg->ueQosCfg.dlAmbr * 32)/100;
   }
   else
   {

      ue->dl.ambrCfgd = 0;
   }

   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   allocInfo->rnti = ue->ueId;


   ueDl->lastCfi = cellSchd->dl.currCfi;

   if ((cellSchd->apisDl->rgSCHRgrDlUeCfg(cell, ue, ueCfg, err)) != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0015,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                      8918      , "Spec Sched DL UE CFG FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                       ;
      return(1);
   }




   ueUl = &ueSchCmn->ul;

   rgSCHCmnUpdUeUlCqiInfo(cell, ue, ueUl, ueSchCmn, cellSchd,
            cell->isCpUlExtend);

   ue->ul.maxBytesPerUePerTti = rgUeCatTbl[ueSchCmn->cmn.ueCat].maxUlBits *
                               16 / (16*8);


   if (ueCfg->ueQosCfg.ueBr == 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0016,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                         8937      , "UeBr configured " "as 0 for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                          ;
      err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
      return(1);
   }
   ue->ul.cfgdAmbr = (ueCfg->ueQosCfg.ueBr * 32)/100;
   ue->ul.effAmbr = ue->ul.cfgdAmbr;
   ue->ul.ulTransTime.sfn = cell->crntTime.sfn; ue->ul.ulTransTime.subframe = cell->crntTime.subframe;;


   cmLListInit(&ueUl->ulAllocLst);

   for (cnt = 0; cnt < 10; cnt++)
   {
      if((rgSCHUtlAllocSBuf(cell->instIdx,
                  (Data**)&(allRcd),sizeof(RgSchCmnAllocRecord)) != 0))
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0017,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                              8954         , "Memory allocation FAILED" "for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                               ;
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         return(1);
      }
      allRcd->allocTime = cell->crntTime;
      cmLListAdd2Tail(&ueUl->ulAllocLst, &allRcd->lnk);
      allRcd->lnk.node = (U32)allRcd;
   }

   for (cnt=0; cnt<4; cnt++)
   {
      ret = rgSCHUtlAllocSBuf(cell->instIdx,
            (Data**)&(ue->ul.lcgArr[cnt].sch), (sizeof(RgSchCmnLcg)));
      if (ret != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0018,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                               8970         , "SCH struct alloc failed for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                ;
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         return(ret);
      }
   }

   ret = rgSCHPwrUeCfg(cell, ue, ueCfg);
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0019,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                    8980      , "Could not do " "power config for UE CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                     ;
      return(1);
   }

   ret = rgSCHCmnSpsUeCfg(cell, ue, ueCfg, err);
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb001a,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                               8988      , "Could not do " "SPS config for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                ;
      return(1);
   }


   if ((cellSchd->apisUl->rgSCHRgrUlUeCfg(cell, ue, ueCfg, err)) != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb001b,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                          8996      , "Spec Sched UL UE CFG FAILED" "for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                           ;
      return(1);
   }


   if (cellSchd->dl.isDlFreqSel)
   {
      if ((cellSchd->apisDlfs->rgSCHDlfsUeCfg(cell, ue, ueCfg, err)) != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb001c,L_ERROR,DBG_CELLID, cell->cellId,ueCfg->crnti, 0, 0, 0,                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                              9006         , "DLFS UE config FAILED" "for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                               ;
         return(1);
      }
   }


   rgSCHCmnGetRefreshPer(cell, ue, &waitPer);

   rgSCHCmnAddUeToRefreshQ(cell, ue, waitPer);

   return(0);
}
static Void rgSCHCmnDlHdlTxModeRecfg
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgrUeRecfg *ueRecfg,
U8 numTxPorts
)
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   ;;

   if (ueRecfg->txMode.pres != 1)
   {
      return;
   }

   ue->txModeTransCmplt =0;
   rgSCHTmrStartTmr (ue->cell, ue, 9, 1000);
   if (ueRecfg->txMode.tmTrnstnState == RGR_TXMODE_RECFG_CMPLT)
   {
      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD &= ~(0x04); }
                                                           ;

     ueDl->mimoInfo.ri = 1;
     if ((ueRecfg->txMode.txModeEnum == RGR_UE_TM_4) ||
          (ueRecfg->txMode.txModeEnum == RGR_UE_TM_6))
      {
         { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x02); };
      }
      if (ueRecfg->txMode.txModeEnum == RGR_UE_TM_3)
      {
         { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x01); };
      }

      return;
   }
   if (ueRecfg->txMode.tmTrnstnState == RGR_TXMODE_RECFG_START)
   {

      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD = (0); };
      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x04); };



      if(ueRecfg->txMode.pres)
      {
         if((ueRecfg->txMode.txModeEnum ==RGR_UE_TM_3) ||
               (ueRecfg->txMode.txModeEnum ==RGR_UE_TM_4))
         {
            if(ueRecfg->ueCodeBookRstRecfg.pres)
            {
               ueDl->mimoInfo.ri =
                  rgSCHCmnComputeRank(ueRecfg->txMode.txModeEnum,
                    ueRecfg->ueCodeBookRstRecfg.pmiBitMap, numTxPorts);
            }
            else
            {
               ueDl->mimoInfo.ri = 1;
            }
         }
         else
         {
            ueDl->mimoInfo.ri = 1;
         }
      }
      else
      {
         ueDl->mimoInfo.ri = 1;
      }



      if ((ueRecfg->txMode.txModeEnum == RGR_UE_TM_4) ||
          (ueRecfg->txMode.txModeEnum == RGR_UE_TM_6))
      {
         { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x02); };
      }
      if (ueRecfg->txMode.txModeEnum == RGR_UE_TM_3)
      {
         { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x01); };
      }
      return;
   }
}
static Void rgSCHCmnUpdUeMimoInfo
(
RgrUeCfg *ueCfg,
RgSchCmnDlUe *ueDl,
RgSchCellCb *cell,
RgSchCmnCell *cellSchd
)







{
   ;

   if(ueCfg->txMode.pres)
   {
      if((ueCfg->txMode.txModeEnum ==RGR_UE_TM_3) ||
            (ueCfg->txMode.txModeEnum ==RGR_UE_TM_4))
      {
         if(ueCfg->ueCodeBookRstCfg.pres)
         {
            ueDl->mimoInfo.ri =
               rgSCHCmnComputeRank(ueCfg->txMode.txModeEnum,
                 ueCfg->ueCodeBookRstCfg.pmiBitMap, cell->numTxAntPorts);
         }
         else
         {
            ueDl->mimoInfo.ri = 1;
         }
      }
      else
      {
         ueDl->mimoInfo.ri = 1;
      }
   }
   else
   {
      ueDl->mimoInfo.ri = 1;
   }




   ueDl->mimoInfo.cwInfo[0].cqi = cellSchd->dl.ccchCqi;
   ueDl->mimoInfo.cwInfo[1].cqi = cellSchd->dl.ccchCqi;

   return;
}
static Void rgSCHCmnUpdUeUlCqiInfo
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchCmnUlUe *ueUl,
RgSchCmnUe *ueSchCmn,
RgSchCmnCell *cellSchd,
Bool isEcp
)
{

   ;


   if(ue->srsCb.srsCfg.type == 1)
   {
     if(ue->ul.ulTxAntSel.pres)
     {
       ueUl->crntUlCqi[ue->srsCb.selectedAnt] = cellSchd->ul.dfltUlCqi;
       ueUl->validUlCqi = ueUl->crntUlCqi[ue->srsCb.selectedAnt];
     }
     else
     {
       ueUl->crntUlCqi[0] = cellSchd->ul.dfltUlCqi;
       ueUl->validUlCqi = ueUl->crntUlCqi[0];
     }
      ue->validTxAnt = ue->srsCb.selectedAnt;
   }
   else
   {
      ueUl->validUlCqi = cellSchd->ul.dfltUlCqi;
      ue->validTxAnt = 0;
   }

   ueUl->ulLaCb.cqiBasediTbs = rgSchCmnUlCqiToTbsTbl[isEcp]
                                                [ueUl->validUlCqi] * 100;
   ueUl->ulLaCb.deltaiTbs = 0;





   ;
   if (rgUeCatTbl[ueSchCmn->cmn.ueCat].ul64qamSup == 0)
   {
      ueUl->maxUlCqi = cellSchd->ul.max16qamCqi;
   }
   else
   {
      ueUl->maxUlCqi = 16 - 1;
   }

   return;
}
static Void rgSCHCmnUpdUeCatCfg
(
RgSchUeCb *ue,
RgSchCellCb *cell
)





{
   RgSchDlHqEnt *hqE = 0L;
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   RgSchCmnUe *ueSchCmn = ((RgSchCmnUe *)((ue->cellInfo[(ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)])])->sch));
   RgSchCmnCell *cellSchd = ((RgSchCmnCell *)((cell)->sc.sch));

   ;

   ueDl->maxTbBits = rgUeCatTbl[ueSchCmn->cmn.ueCat].maxDlTbBits;

   hqE = (ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]]->hqEnt);

   U8 ri = 0;
   ri = ((ri) <= (cell->numTxAntPorts) ? (ri) : (cell->numTxAntPorts));
   if(((CM_LTE_UE_CAT_6 == ueSchCmn->cmn.ueCat )
            ||(CM_LTE_UE_CAT_7 == ueSchCmn->cmn.ueCat))
         && (4 == ri))
   {
      ueDl->maxTbSz = rgUeCatTbl[ueSchCmn->cmn.ueCat].maxDlBits[1];
   }
   else
   {
      ueDl->maxTbSz = rgUeCatTbl[ueSchCmn->cmn.ueCat].maxDlBits[0];
   }

   ueDl->maxSbSz = (rgUeCatTbl[ueSchCmn->cmn.ueCat].maxSftChBits/
                           hqE->numHqPrcs);
   if (rgUeCatTbl[ueSchCmn->cmn.ueCat].ul64qamSup == 0)
   {
      ueUl->maxUlCqi = cellSchd->ul.max16qamCqi;
   }
   else
   {
      ueUl->maxUlCqi = 16 - 1;
   }
   ue->ul.maxBytesPerUePerTti = rgUeCatTbl[ueSchCmn->cmn.ueCat].maxUlBits *
                   16 / (16*8);
   return;
}
 S16 rgSCHCmnRgrUeRecfg
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgrUeRecfg *ueRecfg,
RgSchErrInfo *err
)







{
   RgSchCmnCell *cellSchCmn = ((RgSchCmnCell *)((cell)->sc.sch));
   U32 waitPer;

   ;;

   if (ueRecfg->ueRecfgTypes & (1<<0))
   {

      rgSCHCmnDlHdlTxModeRecfg(cell, ue, ueRecfg, cell->numTxAntPorts);



   }
   if(ueRecfg->ueRecfgTypes & (1<<26))
   {
      ue->csgMmbrSta = ueRecfg->csgMmbrSta;
   }

   if(ueRecfg->ueRecfgTypes & (1<<11))
   {
       rgSCHCmnUpdUeCatCfg(ue, cell);
   }
   if (ueRecfg->ueRecfgTypes & (1<<1))
   {
      RgSchUeCellInfo *pCellInfo = (ue->cellInfo[0]);
      pCellInfo->acqiCb.aCqiCfg = ueRecfg->aprdDlCqiRecfg;
   }
   if (ueRecfg->ueRecfgTypes & (1<<6))
   {
      if (rgSCHPwrUeRecfg(cell, ue, ueRecfg) != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb001d,L_ERROR,DBG_CELLID, cell->cellId,ueRecfg->oldCrnti, 0, 0, 0,                                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                                                9431         , "Power Reconfiguration Failed for OLD CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                 ;
         return(1);
      }
   }

   if (ueRecfg->ueRecfgTypes & (1<<4))
   {

      if (ueRecfg->ueQosRecfg.ueBr == 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb001e,L_ERROR,DBG_CELLID, cell->cellId,ueRecfg->oldCrnti, 0, 0, 0,                                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                                9442         , "UeBr " "configured as 0 for OLD CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                 ;
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         return(1);
      }
      ue->ul.cfgdAmbr = (ueRecfg->ueQosRecfg.ueBr *
      32)/100;

      if (ueRecfg->ueQosRecfg.ambrPres)
      {
         ue->dl.ambrCfgd = (ueRecfg->ueQosRecfg.dlAmbr *
         32)/100;
      }


      rgSCHCmnDelUeFrmRefreshQ(cell, ue);

      rgSCHCmnGetRefreshPer(cell, ue, &waitPer);
      rgSCHCmnApplyUeRefresh(cell, ue);
      rgSCHCmnAddUeToRefreshQ(cell, ue, waitPer);
   }

   if ((cellSchCmn->apisUl->rgSCHRgrUlUeRecfg(cell, ue, ueRecfg, err)) != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb001f,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, 0, 0, 0,                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                 9466      , "Spec Sched UL UE ReCFG FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                  ;
      return(1);
   }
   if ((cellSchCmn->apisDl->rgSCHRgrDlUeRecfg(cell, ue, ueRecfg, err)) != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0020,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, 0, 0, 0,                                                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                 9472      , "Spec Sched DL UE ReCFG FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                  ;
      return(1);
   }

   if (cellSchCmn->dl.isDlFreqSel)
   {
      if ((cellSchCmn->apisDlfs->rgSCHDlfsUeRecfg(cell, ue,
         ueRecfg, err)) != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0021,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, 0, 0, 0,                                                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                               9482         , "DLFS UE re-config FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                ;
         return(1);
      }
   }



   if (rgSCHCmnSpsUeRecfg(cell, ue, ueRecfg, err) != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0022,L_ERROR,DBG_CELLID, cell->cellId, ue->ueId, 0, 0, 0,                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                             9492      , "DL SPS ReCFG FAILED for UE CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                              ;
      return(1);
   }


   return(0);
}
static Void rgSCHCmnUlUeDelAllocs
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   U8 i;

   RgSchCmnUlUeSpsInfo *ulSpsUe = &(ue->ul.ulSpsInfo);

   ;;

   for (i = 0; i < ueUl->hqEnt.numHqPrcs; ++i)
   {
      RgSchUlHqProcCb *proc = rgSCHUhmGetUlHqProc(cell, ue, i);

      proc->ndi = 0;
      if (proc->alloc)
      {


          if(proc->alloc == ulSpsUe->ulSpsSchdInfo.crntAlloc)
          {
               ulSpsUe->ulSpsSchdInfo.crntAlloc = 0L;
             ulSpsUe->ulSpsSchdInfo.crntAllocSf = 0L;
          }

          rgSCHCmnUlFreeAllocation(cell, &cellUl->ulSfArr[proc->ulSfIdx],
                                                         proc->alloc);



      }


      if (proc->reTxLnk.node)
      {
         cmLListDelFrm(proc->reTxAlloc.reTxLst, &proc->reTxLnk);
         proc->reTxLnk.node = (U32)0L;
      }
   }
   return;
}
static Void rgSCHCmnDelUeFrmRefreshQ
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *sched = ((RgSchCmnCell *)((cell)->sc.sch));
   CmTmrArg arg;
   RgSchCmnUeInfo *ueSchd = &(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn);

   ;;

   cmMemset((U8 *)&arg, 0, sizeof(arg));
   arg.tqCp = &sched->tmrTqCp;
   arg.tq = sched->tmrTq;
   arg.timers = &ueSchd->tmr;
   arg.cb = (U32)ue;
   arg.tNum = 0;
   arg.max = 1;
   arg.evnt = 1;

   cmRmvCbTq(&arg);
   return;
}
static Void rgSCHCmnUeCcchSduDel
(
RgSchCellCb *cell,
RgSchUeCb *ueCb
)





{
   RgSchDlHqEnt *hqE = 0L;
   RgSchDlHqProcCb *ccchSduHqP = 0L;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;

   hqE = (ueCb->cellInfo[ueCb->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]]->hqEnt);
   if (hqE == 0L)
   {
      return;
   }
   ccchSduHqP = hqE->ccchSduProc;
   if(ueCb->ccchSduLnk.node != 0L)
   {

      cmLListDelFrm(&(cell->ccchSduUeLst), &(ueCb->ccchSduLnk));
      ueCb->ccchSduLnk.node = 0L;
   }
   else if(ccchSduHqP != 0L)
   {

      if(ccchSduHqP->pdcch)
      {
         cmLListDelFrm(&ccchSduHqP->subFrm->pdcchInfo.pdcchs,
               &ccchSduHqP->pdcch->lnk);
         cmLListAdd2Tail(&cell->pdcchLst, &ccchSduHqP->pdcch->lnk);
         ccchSduHqP->pdcch = 0L;
      }
      if(ccchSduHqP->tbInfo[0].ccchSchdInfo.retxLnk.node != 0L)
      {

         cmLListDelFrm(&cellSch->dl.ccchSduRetxLst,
          &ccchSduHqP->tbInfo[0].ccchSchdInfo.retxLnk);

         rgSCHDhmRlsHqpTb(ccchSduHqP, 0, 1);
      }
      else if ((ccchSduHqP->subFrm != 0L) &&
       (ccchSduHqP->hqPSfLnk.node != 0L))
      {
         rgSCHUtlDlHqPTbRmvFrmTx(ccchSduHqP->subFrm,
               ccchSduHqP, 0, 0);
         rgSCHDhmRlsHqpTb(ccchSduHqP, 0, 1);
      }
   }
   return;
}
 Void rgSCHCmnUeDel
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchDlHqEnt *hqE = 0L;
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   CmLList *node;
   RgSchCmnAllocRecord *allRcd;
   U8 cnt;
   RgSchCmnCell *cellSchCmn = ((RgSchCmnCell *)((cell)->sc.sch));
   U32 idx = 0;
   ;;

   if (((RgSchCmnUe *)((ue->cellInfo[(ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)])])->sch)) == 0L)
   {

      return;
   }
   hqE = (ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]]->hqEnt);
   if(hqE)
   {

      rgSCHCmnUeCcchSduDel(cell, ue);
   }
   rgSCHCmnDelUeFrmRefreshQ(cell, ue);

   rgSCHCmnUlUeDelAllocs(cell, ue);

   rgSCHCmnDelRachInfo(cell, ue);

   cellSchCmn->apisUl->rgSCHFreeUlUe(cell, ue);
   cellSchCmn->apisDl->rgSCHFreeDlUe(cell, ue);

   rgSCHPwrUeDel(cell, ue);


   rgSCHCmnSpsUeDel(cell, ue);



   rgSchCmnDlSfHqDel(ue, cell);


   if (cellSchCmn->dl.isDlFreqSel)
   {
      cellSchCmn->apisDlfs->rgSCHDlfsUeDel(cell, ue);
   }
   node = ueUl->ulAllocLst.first;



   while(node)
   {
      allRcd = (RgSchCmnAllocRecord *)node->node;
      node = node->next;
      cmLListDelFrm(&ueUl->ulAllocLst, &allRcd->lnk);
      rgSCHUtlFreeSBuf(cell->instIdx,
         (Data**)(&allRcd), (sizeof(RgSchCmnAllocRecord)));
   }

   for(cnt = 0; cnt < 4; cnt++)
   {
      if (ue->ul.lcgArr[cnt].sch != 0L)
      {
         rgSCHUtlFreeSBuf(cell->instIdx,
            (Data**)(&(ue->ul.lcgArr[cnt].sch)), (sizeof(RgSchCmnLcg)));
      }
   }


   idx = (U8)((cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId) & (8 - 1));
   rgSCHUtlFreeSBuf(cell->instIdx,
         (Data**)(&(((ue->cellInfo[ue->cellIdToCellIdxMap[idx]])->sch))), (sizeof(RgSchCmnUe)));
   return;
}
static S16 rgSCHCmnDlCnsdrCmnRt
(
RgSchCellCb *cell,
RgrDlCmnCodeRateCfg *dlCmnCodeRate
)





{
   RgSchCmnCell *cellDl = ((RgSchCmnCell *)((cell)->sc.sch));
   U32 bitsPerRb;
   U32 bitsPer2Rb;
   U32 bitsPer3Rb;
   U8 i, rbNum;
   U32 pdcchBits;

   ;;



   if (dlCmnCodeRate->bcchPchRaCodeRate != 0)
   {
      bitsPerRb = ((dlCmnCodeRate->bcchPchRaCodeRate * 2) *
            cellDl->dl.noResPerRb[3])/1024;
   }
   else
   {
      bitsPerRb = ((512 * 2) *
            cellDl->dl.noResPerRb[3])/1024;
   }


   cellDl->dl.bitsPerRb = bitsPerRb;


   i = 0;
   rbNum = 2;
   bitsPer2Rb = bitsPerRb * rbNum;
   while ((i < 9) && (rgTbSzTbl[0][i][rbNum - 1] <= bitsPer2Rb))
      i++;

   (i <= 1)? (cellDl->dl.cmnChITbs.iTbs2Rbs = 0) :
      (cellDl->dl.cmnChITbs.iTbs2Rbs = i-1);


   i = 0;
   rbNum = 3;
   bitsPer3Rb = bitsPerRb * rbNum;
   while ((i < 9) && (rgTbSzTbl[0][i][rbNum - 1] <= bitsPer3Rb))
         i++;

   (i <= 1)? (cellDl->dl.cmnChITbs.iTbs3Rbs = 0) :
      (cellDl->dl.cmnChITbs.iTbs3Rbs = i-1);


   pdcchBits = 1 +
      1 +
      5 +

      3 +




      1 +
      2 +
      2 +
      1 + rgSCHUtlLog32bitNbase2((cell->bwCfg.dlTotalBw *
               (cell->bwCfg.dlTotalBw + 1))/2);





   if (dlCmnCodeRate->pdcchCodeRate != 0)
   {
      pdcchBits = (pdcchBits * 1024)/dlCmnCodeRate->pdcchCodeRate;
      if (pdcchBits <= 288)
      {
         cellDl->dl.cmnChAggrLvl = CM_LTE_AGGR_LVL4;
      }
      else
      {
         cellDl->dl.cmnChAggrLvl = CM_LTE_AGGR_LVL8;
      }
   }
   else
   {
      cellDl->dl.cmnChAggrLvl = CM_LTE_AGGR_LVL4;
   }
   if (dlCmnCodeRate->ccchCqi == 0)
   {
      return(1);
   }
   else
   {
      cellDl->dl.ccchCqi = dlCmnCodeRate->ccchCqi;
   }
   return(0);
}
static S16 rgSCHCmnDlRgrCellCfg
(
RgSchCellCb *cell,
RgrCellCfg *cfg,
RgSchErrInfo *err
)






{
   S16 ret;
   RgSchCmnCell *cellSch;
   U8 cp;
   U8 numPdcchSym;
   U8 noSymPerSlot;
   U8 cfi;
   U8 cfiIdx;

   ;;

   cellSch = ((RgSchCmnCell *)((cell)->sc.sch));






   cellSch->dl.numRaSubFrms = rgRaPrmblToRaFrmTbl[cell->rachCfg.preambleFormat];


   cell->dlHqCfg.maxMsg4HqTx = cfg->dlHqCfg.maxMsg4HqTx;



   cellSch->dl.msg4TxDelay = (cfg->dlHqCfg.maxMsg4HqTx-1) *
                                 rgSchCmnHarqRtt[7] + 3;

   if (cell->bwCfg.dlTotalBw <= 10)
   {
      cfiIdx = 1;
      numPdcchSym = 2;
   }
   else
   {
      cfiIdx = 0;
      numPdcchSym = 1;
   }

   if (cell->isCpDlExtend == 1)
   {
      cp = 1;
      noSymPerSlot = 6;
   }
   else
   {
      cp = 0;
      noSymPerSlot = 7;
   }


   for(cfi = 1; cfi < 4; cfi++, cfiIdx++)
   {
      cellSch->dl.cqiToTbsTbl[0][cfi] = rgSchCmnCqiToTbs[0][cp][cfiIdx];
      cellSch->dl.cqiToEffTbl[0][cfi] = rgSchCmnEffTbl[0][cp][rgSchCmnAntIdx
                                                 [cell->numTxAntPorts]][cfiIdx];
      cellSch->dl.cqiToTbsTbl[1][cfi] = rgSchCmnCqiToTbs[1][cp][cfiIdx];
      cellSch->dl.cqiToEffTbl[1][cfi] = rgSchCmnEffTbl[1][cp][rgSchCmnAntIdx
                                                 [cell->numTxAntPorts]][cfiIdx];
   }


   if(cell->dynCfiCb.isDynCfiEnb)
   {

      cellSch->dl.currCfi = cellSch->dl.newCfi = 1;
   }
   else
   {

      cellSch->dl.currCfi = cellSch->cfiCfg.cfi;
      cellSch->dl.newCfi = cellSch->dl.currCfi;
   }







   for (cfi = 1; cfi < 4; cfi++, numPdcchSym++)
   {
       cellSch->dl.noResPerRb[cfi] = (((noSymPerSlot * 2)
            - numPdcchSym) * 12) - rgSchCmnNumResForCrs[cell->numTxAntPorts];
   }

   if (cfg->maxDlBwPerUe == 0)
   {
      cellSch->dl.maxDlBwPerUe = 100;
   }
   else
   {
      cellSch->dl.maxDlBwPerUe = cfg->maxDlBwPerUe;
   }
   if (cfg->maxDlRetxBw == 0)
   {
      cellSch->dl.maxDlRetxBw = 100;
   }
   else
   {
      cellSch->dl.maxDlRetxBw = cfg->maxDlRetxBw;
   }


   cellSch->dl.maxUePerDlSf = cfg->maxUePerDlSf;
   cellSch->dl.maxUeNewTxPerTti = cfg->maxDlUeNewTxPerTti;
   if (cfg->maxUePerDlSf == 0)
   {
      cellSch->dl.maxUePerDlSf = 4;
   }

   if (cellSch->dl.maxUePerDlSf < cellSch->dl.maxUeNewTxPerTti)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0023,L_ERROR,DBG_CELLID, cell->cellId, cellSch->dl.maxUePerDlSf, cellSch->dl.maxUeNewTxPerTti, 0, 0,                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                        10477      , "FAILED MaxUePerDlSf(%u) < MaxDlUeNewTxPerTti(%u)", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                         ;
      return(1);
   }

   if (cfg->maxCcchPerDlSf > cfg->maxUePerDlSf)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0024,L_ERROR,DBG_CELLID, cell->cellId, cfg->maxCcchPerDlSf, cfg->maxUePerDlSf, 0, 0,                                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                   10485      , "Invalid configuration !: " "maxCcchPerDlSf %u > maxUePerDlSf %u", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                                                    ;

      return(1);
   }
   else if (!cfg->maxCcchPerDlSf)
   {





      cellSch->dl.maxCcchPerDlSf = cfg->maxUePerDlSf;
   }
   else
   {
      cellSch->dl.maxCcchPerDlSf = cfg->maxCcchPerDlSf;
   }


   if (rgSCHCmnDlCnsdrCmnRt(cell, &cfg->dlCmnCodeRate) != 0)
   {
      return(1);
   }
   cmLListInit(&cellSch->dl.msg4RetxLst);

   cmLListInit(&cellSch->dl.ccchSduRetxLst);



   if (cellSch->apisDlfs == 0L)
   {
      cellSch->apisDlfs = &rgSchDlfsSchdTbl[cfg->dlfsSchdType];
   }
   if (cfg->dlfsCfg.isDlFreqSel)
   {
      ret = cellSch->apisDlfs->rgSCHDlfsCellCfg(cell, cfg, err);
      if (ret != 0)
      {
         return(1);
      }
   }
   cellSch->dl.isDlFreqSel = cfg->dlfsCfg.isDlFreqSel;



   ret = rgSCHPwrCellCfg(cell, cfg);
   if (ret != 0)
   {
      return(1);
   }

   cellSch->dl.bcchTxPwrOffset = cfg->bcchTxPwrOffset;
   cellSch->dl.pcchTxPwrOffset = cfg->pcchTxPwrOffset;
   cellSch->dl.rarTxPwrOffset = cfg->rarTxPwrOffset;
   cellSch->dl.phichTxPwrOffset = cfg->phichTxPwrOffset;
   { (&cellSch->dl)->ncsgPrbCnt = 0; (&cellSch->dl)->totPrbCnt = 1; };
   return(0);
}
static U8 rgSCHCmnUlCalcReqRbCeil
(
U32 bytes,
U8 cqi,
RgSchCmnUlCell *cellUl
)






{
   U32 numRe = ((((bytes * 8) * 1024) + (rgSchCmnUlCqiTbl[cqi].eff)-1) / (rgSchCmnUlCqiTbl[cqi].eff));
   ;;
   return((U8)(((numRe) + (((cellUl)->ulNumRePerRb))-1) / (((cellUl)->ulNumRePerRb))));
}
static S16 rgSCHCmnPrecompMsg3Vars
(
RgSchCmnUlCell *cellUl,
U8 ccchCqi,
U16 msgSzA,
U8 sbSize,
Bool isEcp
)
{
   U8 numSb;
   U8 ccchTbs;
   U8 ccchMcs;
   U8 numRb = 0;
   U8 iTbs = 0;
   U16 msg3GrntSz = 0;

   ;;

   if (ccchCqi > cellUl->max16qamCqi)
   {
      ccchCqi = cellUl->max16qamCqi;
   }


   ccchTbs = rgSchCmnUlCqiToTbsTbl[(U8)isEcp][ccchCqi];
   ccchMcs = rgSCHCmnUlGetIMcsFrmITbs(ccchTbs, CM_LTE_UE_CAT_1);

   if (ccchMcs >= 15)
   {
      ccchMcs = 15;
   }






   while((ccchMcs = (rgSCHCmnUlGetIMcsFrmITbs(
                      rgSchCmnUlCqiToTbsTbl[(U8)isEcp][ccchCqi],CM_LTE_UE_CAT_1))
                    ) >
                 15)
   {
      ccchCqi--;
   }

   iTbs = rgSchCmnUlCqiToTbsTbl[(U8)isEcp][ccchCqi];

   if (msgSzA < 7)
   {
      return(1);
   }
   numSb = (((rgSCHCmnUlCalcReqRbCeil(msgSzA, ccchCqi, cellUl)) + (sbSize)-1) / (sbSize));

   numRb = numSb * sbSize;
   msg3GrntSz = 8 * msgSzA;

   while( (rgTbSzTbl[0][iTbs][numRb - 1]) < msg3GrntSz)
   {
      ++numSb;
      numRb = numSb * sbSize;
   }
   while (rgSchCmnMult235Tbl[numSb].match != numSb)
   {
      ++numSb;
   }


   cellUl->ra.prmblBNumSb = numSb;
   cellUl->ra.prmblBIMcs = ccchMcs;
   numSb = (((rgSCHCmnUlCalcReqRbCeil(7, ccchCqi, cellUl)) + (sbSize)-1) / (sbSize))

                ;

   numRb = numSb * sbSize;
   msg3GrntSz = 8 * 7;
   while( (rgTbSzTbl[0][iTbs][numRb - 1]) < msg3GrntSz)
   {
      ++numSb;
      numRb = numSb * sbSize;
   }
   while (rgSchCmnMult235Tbl[numSb].match != numSb)
   {
      ++numSb;
   }


   cellUl->ra.prmblANumSb = numSb;
   cellUl->ra.prmblAIMcs = ccchMcs;
   return(0);
}
static S16 rgSCHCmnUlCalcAvailBw
(
RgSchCellCb *cell,
RgrCellCfg *cellCfg,
U8 cfi,
U8 *rbStartRef,
U8 *bwAvailRef
)
{
   U8 c = 3;
   U8 ulBw = cell->bwCfg.ulTotalBw;
   U8 n2Rb = cell->pucchCfg.resourceSize;
   U8 pucchDeltaShft = cell->pucchCfg.deltaShift;
   U16 n1Pucch = cell->pucchCfg.n1PucchAn;
   U8 n1Cs = cell->pucchCfg.cyclicShift;
   U8 n1PerRb;
   U8 totalCce;
   U16 n1Max;
   U8 n1Rb;
   U32 mixedRb;
   U8 exclRb;
   U8 n1RbPart;
   U8 puschRbStart;

   ;;

   if (cell->isCpUlExtend)
   {
      c = 2;
   }

   n1PerRb = c * 12 / pucchDeltaShft;

   totalCce = cell->dynCfiCb.cfi2NCceTbl[0][cfi];

   n1Max = n1Pucch + totalCce-1;



   n1RbPart = (c*n1Cs)/pucchDeltaShft;
   n1Rb = (U8)((n1Max - n1RbPart) / n1PerRb);
   mixedRb = (((n1Cs) + (8)-1) / (8));



   if(n1Pucch < n1RbPart)
   {
      exclRb = n2Rb;
   }
   else
   {
      exclRb = n2Rb + mixedRb + n1Rb;
   }
   puschRbStart = exclRb/2 + 1;

   if (puschRbStart*2 >= ulBw)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0025,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c",10893, "No bw available for PUSCH", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(1);
   }

   *rbStartRef = puschRbStart;
   *bwAvailRef = ulBw - puschRbStart * 2;

   if(cell->pucchCfg.maxPucchRb !=0 &&
      (puschRbStart * 2 > cell->pucchCfg.maxPucchRb))
   {
      cell->dynCfiCb.maxCfi = ((cfi-1) <= (cell->dynCfiCb.maxCfi) ? (cfi-1) : (cell->dynCfiCb.maxCfi));
   }

   return(0);
}
static S16 rgSCHCmnUlCellInit
(
 RgSchCellCb *cell,
 RgrCellCfg *cellCfg
 )





{
   S16 ret;
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   U8 maxUePerUlSf = cellCfg->maxUePerUlSf;


   U8 maxMsg3PerUlSf = cellCfg->maxMsg3PerUlSf;

   U8 maxUlBwPerUe = cellCfg->maxUlBwPerUe;
   U8 sbSize = cellCfg->puschSubBand.size;
   U8 i;
   U8 rbStart;
   U8 bwAvail;
   U8 cfi;
   U8 maxSbPerUe;
   U8 numSb;
   U8 maxSubfrms = 8 +8;




   U8 iTbs;



   RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);

   ;;

   cellUl->maxUeNewTxPerTti = cellCfg->maxUlUeNewTxPerTti;
   if (maxUePerUlSf == 0)
   {
      maxUePerUlSf = 1;
   }

   if (maxMsg3PerUlSf == 0)
   {
      maxMsg3PerUlSf = 1;
   }




   if(maxMsg3PerUlSf > 10)
   {
      maxMsg3PerUlSf = 10;
   }

   if(maxMsg3PerUlSf > maxUePerUlSf)
   {
      maxMsg3PerUlSf = maxUePerUlSf;
   }



   cellUl->maxAllocPerUlSf = maxUePerUlSf;
   cellUl->maxMsg3PerUlSf = maxMsg3PerUlSf;




   if (cellUl->maxAllocPerUlSf < cellUl->maxUeNewTxPerTti)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0026,L_ERROR,DBG_CELLID, cell->cellId, cellUl->maxAllocPerUlSf, cellUl->maxUeNewTxPerTti, 0, 0,                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                    11012      , "FAILED: MaxUePerUlSf(%u) < MaxUlUeNewTxPerTti(%u)", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                     ;
      return(1);
   }
   if (maxUlBwPerUe == 0)
   {

      maxUlBwPerUe = cell->bwCfg.ulTotalBw;
   }
   cellUl->maxUlBwPerUe = maxUlBwPerUe;


   if (!cellCfg->isCpUlExtend)
   {
      cellUl->ulNumRePerRb = 12 * (14 - 2);
   }
   else
   {
      cellUl->ulNumRePerRb = 12 * (12 - 2);
   }

   if (sbSize != rgSchCmnMult235Tbl[sbSize].match)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0027,L_ERROR,DBG_CELLID, cell->cellId, sbSize, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c",11052, "Invalid subband size %d", RLOG_FILE_ID, RLOG_MODULE_NAME); };
      return(1);
   }
   maxSbPerUe = maxUlBwPerUe / sbSize;
   if (maxSbPerUe == 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0028,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                      11059      , "rgSCHCmnUlCellInit(): " "maxUlBwPerUe/sbSize is zero", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                       ;
      return(1);
   }
   cellUl->maxSbPerUe = rgSchCmnMult235Tbl[maxSbPerUe].prvMatch;


   if ((!((cellCfg->ulCmnCodeRate.ccchCqi) > 0 && (cellCfg->ulCmnCodeRate.ccchCqi) < 16))
         || (!((cellCfg->trgUlCqi.trgCqi) > 0 && (cellCfg->trgUlCqi.trgCqi) < 16)))
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0029,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                      11069      , "rgSCHCmnUlCellInit(): " "Invalid cqi", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                       ;
      return(1);
   }
   cellUl->dfltUlCqi = cellCfg->ulCmnCodeRate.ccchCqi;





    for (i = 16 - 1;i > 0; --i)
   {
      if( L_INFO < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb002a,L_INFO,DBG_CELLID, cell->cellId, i, rgSchCmnUlCqiToTbsTbl[cell->isCpUlExtend][i], 0, 0,                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                        11083      , "CQI %u:iTbs %u", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                                         ;
   }
   for (i = 16 - 1; i != 0; --i)
   {

      iTbs = rgSchCmnUlCqiToTbsTbl[cell->isCpUlExtend][i];
      if (iTbs <= 20)
      {
         if( L_INFO < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb002b,L_INFO,DBG_CELLID, cell->cellId, i, 0, 0, 0,                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                 11100         , "16 QAM CQI %u", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                  ;
         cellUl->max16qamCqi = i;
         break;
      }
   }


   ret = rgSCHCmnPrecompMsg3Vars(cellUl, cellCfg->ulCmnCodeRate.ccchCqi,
         cell->rachCfg.msgSizeGrpA, sbSize, cell->isCpUlExtend);
   if (ret != 0)
   {
      return(ret);
   }

   cellUl->sbSize = sbSize;
   for (cfi = 1; cfi < 4; cfi++)
   {



      ret = rgSCHCmnUlCalcAvailBw(cell, cellCfg, cfi, &rbStart, &bwAvail);

      if (ret != 0)
      {
         return(ret);
      }

      if (cfi == 1)
      {
         cell->ulAvailBw = bwAvail;
      }

      numSb = bwAvail/sbSize;

      cell->dynCfiCb.bwInfo[cfi].startRb = rbStart;
      cell->dynCfiCb.bwInfo[cfi].numSb = numSb;
   }

   if(0 == cell->dynCfiCb.maxCfi)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb002c,L_ERROR,DBG_CELLID, cell->cellId, cellSch->cfiCfg.cfi, cell->dynCfiCb.maxCfi, cell->pucchCfg.maxPucchRb, 0,                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                        11181      , "Incorrect Default CFI(%u), maxCfi(%u), maxPucchRb(%d)", RLOG_FILE_ID, RLOG_MODULE_NAME); }


                                         ;

      return(1);
   }


   cellUl->dmrsArrSize = cell->dynCfiCb.bwInfo[1].numSb;
   ret = rgSCHUtlAllocSBuf(cell->instIdx, (Data **)&cellUl->dmrsArr,
         cellUl->dmrsArrSize * sizeof(*cellUl->dmrsArr));
   if (ret != 0)
   {
      return(ret);
   }
   for (i = 0; i < cellUl->dmrsArrSize; ++i)
   {
      cellUl->dmrsArr[i] = cellCfg->puschSubBand.dmrs[i];
   }


   for (i = 0; i < maxSubfrms; ++i)
   {
      ret = rgSCHUtlUlSfInit(cell, &cellUl->ulSfArr[i], i,
                             cellUl->maxAllocPerUlSf);
      if (ret != 0)
      {
         for (; i != 0; --i)
         {
            rgSCHUtlUlSfDeinit(cell, &cellUl->ulSfArr[i-1]);
         }


         rgSCHUtlFreeSBuf(cell->instIdx, (Data **)(&(cellUl->dmrsArr)),
               cellUl->dmrsArrSize * sizeof(*cellUl->dmrsArr));






         return(ret);
      }
   }
   { (cellUl)->ncsgPrbCnt = 0; (cellUl)->totPrbCnt = 1; };
   return(0);
}
 S16 rgSCHCmnRgrCellCfg
(
RgSchCellCb *cell,
RgrCellCfg *cellCfg,
RgSchErrInfo *err
)






{
   S16 ret;
   RgSchCmnCell *cellSch;
   ;;





   if (((ret = rgSCHUtlAllocSBuf(cell->instIdx,
      (Data**)&(cell->sc.sch), (sizeof(RgSchCmnCell)))) != 0))
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb002d,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                   11271      , "Memory allocation FAILED", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                    ;
      err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
      return(ret);
   }
   cellSch = (RgSchCmnCell *)(cell->sc.sch);
   cellSch->cfiCfg = cellCfg->cfiCfg;
   cellSch->trgUlCqi.trgCqi = cellCfg->trgUlCqi.trgCqi;

   cellSch->tmrTqCp.nxtEnt = 0;
   cellSch->tmrTqCp.tmrLen = 16;


   rgSCHCmnCfgRachDedPrm(cell);
   ret = rgSCHCmnUlCellInit(cell, cellCfg);
   if (ret != 0)
   {

      err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
      return(ret);
   }
   ret = rgSCHCmnDlRgrCellCfg(cell, cellCfg, err);
   if (ret != 0)
   {
      err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
      return(ret);
   }



   rgSCHCmnGetDciFrmtSizes(cell);
   rgSCHCmnGetCqiDciFrmt2AggrLvl(cell);

   cellSch->apisUl = &rgSchUlSchdTbl[rgSchCb[cell->instIdx].rgrSchedEnbCfg.ulSchdType];
   ret = cellSch->apisUl->rgSCHRgrUlCellCfg(cell, cellCfg, err);
   if (ret != 0)
   {
      return(ret);
   }

   cellSch->apisDl = &rgSchDlSchdTbl[rgSchCb[cell->instIdx].rgrSchedEnbCfg.dlSchdType];


   ret = rgSCHCmnSpsCellCfg(cell, cellCfg, err);
   if (ret != 0)
   {
      return(ret);
   }

   ret = cellSch->apisDl->rgSCHRgrDlCellCfg(cell, cellCfg, err);
   if (ret != 0)
   {
      return(ret);
   }
   rgSCHCmnInitVars(cell);

   return(0);
}
 S16 rgSCHCmnRgrCellRecfg
(
RgSchCellCb *cell,
RgrCellRecfg *recfg,
RgSchErrInfo *err
)






{
   S16 ret;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);

   ;;

   if (recfg->recfgTypes & (1<<4))
   {
      U8 oldCqi = cellUl->dfltUlCqi;
      if (!((recfg->ulCmnCodeRate.ccchCqi) > 0 && (recfg->ulCmnCodeRate.ccchCqi) < 16))
      {
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb002e,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                         11384         , "rgSCHCmnRgrCellRecfg(): " "Invalid cqi", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                          ;
         return(1);
      }
      cellUl->dfltUlCqi = recfg->ulCmnCodeRate.ccchCqi;
      ret = rgSCHCmnPrecompMsg3Vars(cellUl, recfg->ulCmnCodeRate.ccchCqi,
            cell->rachCfg.msgSizeGrpA, cellUl->sbSize, cell->isCpUlExtend);
      if (ret != 0)
      {
         cellUl->dfltUlCqi = oldCqi;
         rgSCHCmnPrecompMsg3Vars(cellUl, recfg->ulCmnCodeRate.ccchCqi,
               cell->rachCfg.msgSizeGrpA, cellUl->sbSize, cell->isCpUlExtend);
         return(ret);
      }
   }

   if (recfg->recfgTypes & (1<<0))
   {
      if (rgSCHCmnDlCnsdrCmnRt(cell, &recfg->dlCmnCodeRate) != 0)
      {
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         return(1);
      }
   }


   ret = cellSch->apisUl->rgSCHRgrUlCellRecfg(cell, recfg, err);
   if (ret != 0)
   {
      return(1);
   }


   ret = cellSch->apisDl->rgSCHRgrDlCellRecfg(cell, recfg, err);
   if (ret != 0)
   {
      return(1);
   }

   if (recfg->recfgTypes & (1<<9))
   {
      ret = cellSch->apisDlfs->rgSCHDlfsCellRecfg(cell, recfg, err);
      if (ret != 0)
      {
         return(1);
      }
      cellSch->dl.isDlFreqSel = recfg->dlfsRecfg.isDlFreqSel;
   }

   if (recfg->recfgTypes & (1<<10))
   {
      ret = rgSCHPwrCellRecfg(cell, recfg);
      if (ret != 0)
      {
         return(1);
      }
   }

   return(0);
}
static Void rgSCHCmnUlCellDeinit
(
RgSchCellCb *cell
)




{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   U8 ulSfIdx;







   ;;
   if (cellUl->dmrsArr != 0L)
   {


      rgSCHUtlFreeSBuf(cell->instIdx,(Data **)(&(cellUl->dmrsArr)),
               cellUl->dmrsArrSize * sizeof(*cellUl->dmrsArr));
   }




   for (ulSfIdx = 0; ulSfIdx < 8 +8; ++ulSfIdx)

   {
      rgSCHUtlUlSfDeinit(cell, &cellUl->ulSfArr[ulSfIdx]);
   }
   return;
}
 Void rgSCHCmnCellDel
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;




   if (cellSch == 0L)
   {
      return;
   }

   rgSCHCmnUlCellDeinit(cell);
   if (cellSch->apisUl)
   {


      cellSch->apisUl->rgSCHFreeUlCell(cell);
   }


   cmLListInit(&cellSch->dl.taLst);
   if (cellSch->apisDl)
   {
      cellSch->apisDl->rgSCHFreeDlCell(cell);
   }


   if (cellSch->dl.isDlFreqSel && cellSch->apisDlfs)
   {
      cellSch->apisDlfs->rgSCHDlfsCellDel(cell);
   }

   rgSCHPwrCellDel(cell);

   rgSCHCmnSpsCellDel(cell);




   rgSCHUtlFreeSBuf(cell->instIdx,
      (Data**)(&(cell->sc.sch)), (sizeof(RgSchCmnCell)));
   return;
}
static S16 rgSCHCmnValidateDlQos
(
RgrLchQosCfg *dlQos
)




{
   U8 qci = dlQos->qci;

   ;;

   if ( qci < 1 || qci > 9 )
   {
      return(1);
   }

   if ((qci >= 1) &&
       (qci <= 4))
   {
      if ((dlQos->mbr == 0) || (dlQos->mbr < dlQos->gbr))
      {
         return(1);
      }
   }
   return(0);
}
 S16 rgSCHCmnRgrLchCfg
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlLcCb *dlLc,
RgrLchCfg *lcCfg,
RgSchErrInfo *err
)
{
   S16 ret;

   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;

   ret = rgSCHUtlAllocSBuf(cell->instIdx,
      (Data**)&((dlLc)->sch), (sizeof(RgSchCmnDlSvc)));
   if (ret != 0)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb002f,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, lcCfg->lcId, 0, 0,                                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                            11700      , "rgSCHCmnRgrLchCfg(): " "SCH struct alloc failed for CRNTI:%d LCID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                             ;
      err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
      return(ret);
   }
   if(lcCfg->lcType != 5)
   {
      ret = rgSCHCmnValidateDlQos(&lcCfg->dlInfo.dlQos);
      if (ret != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0030,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, lcCfg->lcId, 0, 0,                                                                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                                               11710         , "rgSchCmnCrgLcCfg(): " "DlQos validation failed for CRNTI:%d LCID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                ;
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         return(ret);
      }

      ((RgSchCmnDlSvc *)(dlLc->sch))->qci = lcCfg->dlInfo.dlQos.qci;
      ((RgSchCmnDlSvc *)(dlLc->sch))->prio = rgSchCmnDlQciPrio[lcCfg->dlInfo.dlQos.qci - 1];
      ((RgSchCmnDlSvc *)(dlLc->sch))->gbr = (lcCfg->dlInfo.dlQos.gbr *
      32)/100;
      ((RgSchCmnDlSvc *)(dlLc->sch))->mbr = (lcCfg->dlInfo.dlQos.mbr *
      32)/100;
   }
   else
   {

    ((RgSchCmnDlSvc *)(dlLc->sch))->prio=0;
   }
   dlLc->ue = ue;
   dlLc->lcType=lcCfg->lcType;
   ret = cellSch->apisDl->rgSCHRgrDlLcCfg(cell, ue, dlLc, lcCfg, err);
   if (ret != 0)
   {
      return(1);
   }

   ret = cellSch->apisUl->rgSCHRgrUlLcCfg(cell, ue, lcCfg, err);
   if (ret != 0)
   {
      return(1);
   }
   if(lcCfg->dlInfo.dlSpsCfg.isSpsEnabled)
   {

      ret = rgSCHCmnSpsDlLcCfg(cell, ue, dlLc, lcCfg, err);
      if (ret != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0031,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, lcCfg->lcId, 0, 0,                                                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                                                          11757         , "rgSchCmnRgrLchCfg(): " "SPS configuration failed for DL LC for CRNTI:%d LCID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                           ;
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         return(1);
      }
   }


   return(0);
}
 S16 rgSCHCmnRgrLchRecfg
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlLcCb *dlLc,
RgrLchRecfg *lcRecfg,
RgSchErrInfo *err
)
{
   S16 ret;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;

   if(dlLc->lcType != 5)
   {
      ret = rgSCHCmnValidateDlQos(&lcRecfg->dlRecfg.dlQos);

      if (ret != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0032,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, lcRecfg->lcId, 0, 0,                                                                                    "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                                                    11819         , "DlQos validation failed for CRNTI:%d LCID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                     ;
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         return(ret);
      }
      if (((RgSchCmnDlSvc *)(dlLc->sch))->qci != lcRecfg->dlRecfg.dlQos.qci)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0033,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, lcRecfg->lcId, 0, 0,                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                                       11826         , "Qci, hence lc Priority change " "not supported for CRNTI:%d LCID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                        ;
         err->errCause = (((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1);
         return(ret);
      }
      ((RgSchCmnDlSvc *)(dlLc->sch))->gbr = (lcRecfg->dlRecfg.dlQos.gbr *
      32)/100;
      ((RgSchCmnDlSvc *)(dlLc->sch))->mbr = (lcRecfg->dlRecfg.dlQos.mbr *
      32)/100;
   }
   else
   {

      ((RgSchCmnDlSvc *)(dlLc->sch))->prio = 0;
   }

   ret = cellSch->apisDl->rgSCHRgrDlLcRecfg(cell, ue, dlLc, lcRecfg, err);
   if (ret != 0)
   {
      return(1);
   }
   ret = cellSch->apisUl->rgSCHRgrUlLcRecfg(cell, ue, lcRecfg, err);
   if (ret != 0)
   {
      return(1);
   }


   if (lcRecfg->recfgTypes & (1<<1))
   {

      if(lcRecfg->dlRecfg.dlSpsRecfg.isSpsEnabled)
      {
         ret = rgSCHCmnSpsDlLcRecfg(cell, ue, dlLc, lcRecfg, err);
         if (ret != 0)
         {
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0034,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, lcRecfg->lcId, 0, 0,                                                                                          "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                                                                          11862            , "SPS re-configuration not " "supported for dlLC Ignore this CRNTI:%d LCID:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                           ;
         }
      }
      return(0);
   }


   return(0);
}
 S16 rgSCHCmnRgrLcgCfg
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchLcgCb *lcg,
RgrLcgCfg *lcgCfg,
RgSchErrInfo *err
)
{
   S16 ret;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnLcg *ulLcg = ((RgSchCmnLcg *)(ue->ul.lcgArr[lcgCfg->ulInfo.lcgId].sch));

   ;;

   ulLcg->cfgdGbr = (lcgCfg->ulInfo.gbr * 32)/100;
   ulLcg->effGbr = ulLcg->cfgdGbr;
   ulLcg->deltaMbr = ((lcgCfg->ulInfo.mbr - lcgCfg->ulInfo.gbr) * 32)/100;
   ulLcg->effDeltaMbr = ulLcg->deltaMbr;

   ret = cellSch->apisUl->rgSCHRgrUlLcgCfg(cell, ue, lcg, lcgCfg, err);
   if (ret != 0)
   {
      return(1);
   }
   if (((ulLcg->cfgdGbr) != 0))
   {

      rgSCHUtlBuildNSendLcgReg(cell, ue->ueId, lcgCfg->ulInfo.lcgId, 1);
   }
   return(0);
}
 S16 rgSCHCmnRgrLcgRecfg
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchLcgCb *lcg,
RgrLcgRecfg *reCfg,
RgSchErrInfo *err
)
{
   S16 ret;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnLcg *ulLcg = ((RgSchCmnLcg *)(ue->ul.lcgArr[reCfg->ulRecfg.lcgId].sch));

   ;;

   ulLcg->cfgdGbr = (reCfg->ulRecfg.gbr * 32)/100;
   ulLcg->effGbr = ulLcg->cfgdGbr;
   ulLcg->deltaMbr = ((reCfg->ulRecfg.mbr - reCfg->ulRecfg.gbr) * 32)/100;
   ulLcg->effDeltaMbr = ulLcg->deltaMbr;

   ret = cellSch->apisUl->rgSCHRgrUlLcgRecfg(cell, ue, lcg, reCfg, err);
   if (ret != 0)
   {
      return(1);
   }
   if (((ulLcg->cfgdGbr) != 0))
   {

      rgSCHUtlBuildNSendLcgReg(cell, ue->ueId, reCfg->ulRecfg.lcgId, 1);
   }
   else
   {

      rgSCHUtlBuildNSendLcgReg(cell, ue->ueId, reCfg->ulRecfg.lcgId, 0);
   }
   return(0);
}
 S16 rgSCHCmnRgrLchDel
(
RgSchCellCb *cell,
RgSchUeCb *ue,
CmLteLcId lcId,
U8 lcgId
)







{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;
   cellSch->apisUl->rgSCHRgrUlLchDel(cell, ue, lcId, lcgId);
   return(0);
}
 Void rgSCHCmnLcgDel
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchLcgCb *lcg
)






{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnLcg *lcgCmn = ((RgSchCmnLcg *)((lcg)->sch));
   ;;

   if (lcgCmn == 0L)
   {
      return;
   }

   if (((lcgCmn->cfgdGbr) != 0))
   {

      rgSCHUtlBuildNSendLcgReg(cell, ue->ueId, lcg->lcgId, 0);
   }


   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
      rgSCHCmnSpsUlLcgDel(cell, ue, lcg);
   }


   lcgCmn->effGbr = 0;
   lcgCmn->reportedBs = 0;
   lcgCmn->cfgdGbr = 0;


   lcgCmn->bs = 0;
   cellSch->apisUl->rgSCHFreeUlLcg(cell, ue, lcg);
   return;
}
 Void rgSCHCmnFreeDlLc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlLcCb *svc
)






{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;
   if (svc->sch == 0L)
   {
      return;
   }
   cellSch->apisDl->rgSCHFreeDlLc(cell, ue, svc);
   if (svc->dlLcSpsCfg.isSpsEnabled)
   {
      rgSCHCmnSpsDlLcDel(cell, ue, svc);
   }




   rgSCHUtlFreeSBuf(cell->instIdx,
         (Data**)(&(svc->sch)), (sizeof(RgSchCmnDlSvc)));
   return;
}
static Void rgSCHCmnDlCcchSduRetxFnlz
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   CmLList *node;
   RgSchCmnDlCell *cmnCellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchDlRbAlloc *rbAllocInfo;
   RgSchDlHqProcCb *hqP;
   RgSchUeCb *ue;
   ;;


   node = allocInfo->ccchSduAlloc.schdCcchSduRetxLst.first;
   while (node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      ue = hqP->hqE->ue;
      rbAllocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
      node = node->next;
      rgSCHCmnFillHqPPdcch(cell, rbAllocInfo, hqP);


      cmLListDelFrm(&cmnCellDl->ccchSduRetxLst, &hqP->tbInfo[0].ccchSchdInfo.retxLnk);
      hqP->tbInfo[0].ccchSchdInfo.retxLnk.node = (U32)0L;



      rgSCHCmnDlUeResetTemp(ue, hqP);
   }


   node = allocInfo->ccchSduAlloc.nonSchdCcchSduRetxLst.first;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      ue = hqP->hqE->ue;
      node = node->next;

      rgSCHCmnDlUeResetTemp(ue, hqP);
   }
   return;
}
static Void rgSCHCmnDlCcchRetxFnlz
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   CmLList *node;
   RgSchCmnDlCell *cmnCellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchDlRbAlloc *rbAllocInfo;
   RgSchDlHqProcCb *hqP;
   RgSchRaCb *raCb;
   ;;


   node = allocInfo->msg4Alloc.schdMsg4RetxLst.first;
   while (node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      raCb = hqP->hqE->raCb;
      rbAllocInfo = &raCb->rbAllocInfo;
      node = node->next;
      rgSCHCmnFillHqPPdcch(cell, rbAllocInfo, hqP);


      cmLListDelFrm(&cmnCellDl->msg4RetxLst, &hqP->tbInfo[0].ccchSchdInfo.retxLnk);
      hqP->tbInfo[0].ccchSchdInfo.retxLnk.node = (U32)0L;


      cmMemset((U8 *)rbAllocInfo, (U8)0, sizeof(*rbAllocInfo));
      rgSCHCmnDlHqPResetTemp(hqP);
   }


   node = allocInfo->msg4Alloc.nonSchdMsg4RetxLst.first;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      raCb = hqP->hqE->raCb;
      node = node->next;
      cmMemset((U8 *)&raCb->rbAllocInfo, (U8)0, sizeof(raCb->rbAllocInfo));
      rgSCHCmnDlHqPResetTemp(hqP);
   }
   return;
}
static Void rgSCHCmnDlCcchSduTxFnlz
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   CmLList *node;
   RgSchUeCb *ueCb;
   RgSchDlRbAlloc *rbAllocInfo;
   RgSchDlHqProcCb *hqP;
   RgSchLchAllocInfo lchSchdData;
   ;;


   node = allocInfo->ccchSduAlloc.schdCcchSduTxLst.first;
   while (node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      ueCb = hqP->hqE->ue;
      node = node->next;
      rbAllocInfo = &(((ueCb)->cellInfo[(ueCb)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;


      rgSCHCmnFillHqPPdcch(cell, rbAllocInfo, hqP);


      cmLListDelFrm(&cell->ccchSduUeLst, &ueCb->ccchSduLnk);
      ueCb->ccchSduLnk.node = (U32)0L;



      ueCb->dlCcchInfo.bo = 0;


      hqP->tbInfo[0].contResCe = 0;
      lchSchdData.lcId = 0;
      lchSchdData.schdData = hqP->tbInfo[0].ccchSchdInfo.totBytes -
                             (1);
      rgSCHDhmAddLcData(cell->instIdx, &lchSchdData, &hqP->tbInfo[0]);



      rgSCHCmnDlUeResetTemp(ueCb, hqP);
   }


   node = allocInfo->ccchSduAlloc.nonSchdCcchSduTxLst.first;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      ueCb = hqP->hqE->ue;
      node = node->next;

      rgSCHDhmRlsHqpTb(hqP, 0, 0);



      rgSCHCmnDlUeResetTemp(ueCb, hqP);
   }
   return;
}
static Void rgSCHCmnDlCcchTxFnlz
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   CmLList *node;
   RgSchRaCb *raCb;
   RgSchDlRbAlloc *rbAllocInfo;
   RgSchDlHqProcCb *hqP;
   RgSchLchAllocInfo lchSchdData;
   ;;


   node = allocInfo->msg4Alloc.schdMsg4TxLst.first;
   while (node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      raCb = hqP->hqE->raCb;
      node = node->next;
      rbAllocInfo = &raCb->rbAllocInfo;


      rgSCHCmnFillHqPPdcch(cell, rbAllocInfo, hqP);


      rgSCHRamRmvFrmRaInfoSchdLst(cell, raCb);



      lchSchdData.lcId = 0;
      lchSchdData.schdData = hqP->tbInfo[0].ccchSchdInfo.totBytes -
         (1 + 7);




      hqP->tbInfo[0].contResCe = 1;

      if(raCb->dlCcchInfo.bo)
      {
         rgSCHDhmAddLcData(cell->instIdx, &lchSchdData, &hqP->tbInfo[0]);
      }
      else
      {
      }


      cmMemset((U8 *)&raCb->rbAllocInfo, (U8)0, sizeof(raCb->rbAllocInfo));
      rgSCHCmnDlHqPResetTemp(hqP);
   }
   node = allocInfo->msg4Alloc.nonSchdMsg4TxLst.first;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      raCb = hqP->hqE->raCb;
      node = node->next;
      rbAllocInfo = &raCb->rbAllocInfo;

      rgSCHDhmRlsHqpTb(hqP, 0, 0);



      cmMemset((U8 *)rbAllocInfo, (U8)0, sizeof(*rbAllocInfo));
      rgSCHCmnDlHqPResetTemp(hqP);
   }

   return;
}
static U8 rgSCHCmnGetBiIndex
(
RgSchCellCb *cell,
U32 ueCount
)





{
   S16 prevVal = 0;
   U16 newBiVal = 0;
   U8 idx = 0;
   U16 timeDiff = 0;

   ;

   if (cell->biInfo.prevBiTime != 0)
   {
      timeDiff =((cell->crntTime.sfn*10+cell->crntTime.subframe) < (cell->biInfo.biTime.sfn*10+cell->biInfo.biTime.subframe)? ((cell->crntTime.sfn+1024)*10+cell->crntTime.subframe) - (cell->biInfo.biTime.sfn*10+cell->biInfo.biTime.subframe) : (cell->crntTime.sfn*10+cell->crntTime.subframe) - (cell->biInfo.biTime.sfn*10+cell->biInfo.biTime.subframe));
      prevVal = cell->biInfo.prevBiTime - timeDiff;
   }
   if (prevVal < 0)
   {
      prevVal = 0;
   }
   newBiVal = ( prevVal + ( ueCount * 1 ));

   cell->biInfo.biTime.sfn = cell->crntTime.sfn; cell->biInfo.biTime.subframe = cell->crntTime.subframe;


   do
   {
      if (rgSchCmnBiTbl[idx] > newBiVal)
      {
         break;
      }
      idx++;
   }while(idx < 13 -1);
   cell->biInfo.prevBiTime = rgSchCmnBiTbl[idx];

   return(idx);
}
static Void rgSCHCmnDlRaRspFnlz
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   U32 rarCnt = 0;
   RgSchDlRbAlloc *raRspAlloc;
   RgSchDlSf *subFrm = 0L;
   RgSchRaCb *raCb;
   RgSchErrInfo err;
   CmLListCp *reqLst;
   RgSchRaReqInfo *raReq;
   Bool preamGrpA;
   RgSchUlAlloc *ulAllocRef=0L;
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   U8 allocRapidCnt = 0;






   ;;

   for (rarCnt=0; rarCnt<4; rarCnt++)
   {
      raRspAlloc = &allocInfo->raRspAlloc[rarCnt];

      if (!raRspAlloc->pdcch)
      {
         continue;
      }
      else
      {
         subFrm = raRspAlloc->dlSf;
         reqLst = &cell->raInfo.raReqLst[raRspAlloc->raIndex];

         allocRapidCnt = raRspAlloc->numRapids;
         while (allocRapidCnt)
         {
            raReq = (RgSchRaReqInfo *)(reqLst->first->node);


            if (((raReq->raReq.rapId) >= (cell->rachCfg.numRaPreamble)))
            {
               rgSCHCmnHdlHoPo(cell, &subFrm->raRsp[rarCnt].contFreeUeLst,
                     raReq);
               cmLListDelFrm(reqLst, reqLst->first);
               allocRapidCnt--;


               rgSCHUtlFreeSBuf(cell->instIdx, (Data **)&raReq,
                     sizeof(RgSchRaReqInfo));
               continue;
            }

            if(cell->overLoadBackOffEnab)
            {
               cmLListDelFrm(reqLst, reqLst->first);
               allocRapidCnt--;
               rgSCHUtlFreeSBuf(cell->instIdx, (Data **)&raReq,
                     sizeof(RgSchRaReqInfo));
               continue;
            }





            if (rgSCHRamCreateRaCb(cell, &raCb, &err) != 0)
            {
               break;
            }

            if (raReq->raReq.rapId < cell->rachCfg.sizeRaPreambleGrpA)
               preamGrpA = 1;
            else
               preamGrpA = 0;

            rgSCHCmnMsg3GrntReq(cell, raCb->tmpCrnti, preamGrpA,
                  &(raCb->msg3HqProc), &ulAllocRef, &raCb->msg3HqProcId);
            if (ulAllocRef == 0L)
            {
               rgSCHRamDelRaCb(cell, raCb, 1);
               break;
            }
            if (raReq->raReq.cqiPres)
            {
               raCb->ccchCqi = raReq->raReq.cqiIdx;
            }
            else
            {
               raCb->ccchCqi = cellDl->ccchCqi;
            }
            raCb->rapId = raReq->raReq.rapId;
            raCb->ta.pres = 1;
            raCb->ta.val = raReq->raReq.ta;
            raCb->msg3Grnt = ulAllocRef->grnt;

            raCb->msg3Grnt.tpc = raReq->raReq.tpc;

            ulAllocRef->raCb = raCb;



            raCb->msg3AllocTime = cell->crntTime;
            do { if ((raCb->msg3AllocTime.subframe += (2 + 0) + 6) > 9) { raCb->msg3AllocTime.sfn = ((raCb->msg3AllocTime.sfn) + 1) & 0x03ff; raCb->msg3AllocTime.subframe -= 10; }} while(0);
            cmLListAdd2Tail(&subFrm->raRsp[rarCnt].raRspLst, &raCb->rspLnk);
            raCb->rspLnk.node = (U32)raCb;
            cmLListDelFrm(reqLst, reqLst->first);
            allocRapidCnt--;


            rgSCHUtlFreeSBuf(cell->instIdx, (Data **)&raReq,
                  sizeof(RgSchRaReqInfo));


            rgNumRarSched++;

         }


         subFrm->raRsp[rarCnt].raRnti = raRspAlloc->rnti;
         subFrm->raRsp[rarCnt].pdcch = raRspAlloc->pdcch;
         subFrm->raRsp[rarCnt].tbSz = raRspAlloc->tbInfo[0].bytesAlloc;

         rgSCHCmnFillPdcch(cell, subFrm->raRsp[rarCnt].pdcch, raRspAlloc);


         if(cell->overLoadBackOffEnab)
         {
            subFrm->raRsp[rarCnt].backOffInd.pres = 1;
            subFrm->raRsp[rarCnt].backOffInd.val = cell->overLoadBackOffval;
            continue;
         }
         else
         {
            subFrm->raRsp[rarCnt].backOffInd.pres = 0;
         }



         reqLst = &cell->raInfo.raReqLst[raRspAlloc->raIndex];
         if ((raRspAlloc->biEstmt) && (reqLst->count))
         {
            subFrm->raRsp[0].backOffInd.pres = 1;

            subFrm->raRsp[0].backOffInd.val =
            rgSCHCmnGetBiIndex(cell, reqLst->count);


            rgNumBI++;

         }
         else if ((subFrm->raRsp[rarCnt].raRspLst.first == 0L) &&
               (subFrm->raRsp[rarCnt].contFreeUeLst.first == 0L))
         {

            rgSCHUtlPdcchPut(cell, &subFrm->pdcchInfo, raRspAlloc->pdcch);
            subFrm->raRsp[rarCnt].pdcch = 0L;
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0035,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                       12894            , "rgSCHCmnRaRspAlloc(): " "Not even one RaReq.", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                        ;
            return;
         }
      }
      if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0036,L_DEBUG,DBG_CELLID, cell->cellId, raRspAlloc->rnti, cell->crntTime.sfn, cell->crntTime.subframe, 0,                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                   12902      , "RNTI:%d Scheduled RAR @ (%u,%u) ", RLOG_FILE_ID, RLOG_MODULE_NAME); }



                                    ;
   }
   return;
}
static U8 rgSCHCmnDlCalcRvForBcch
(
RgSchCellCb *cell,
Bool si,
U16 i
)






{
   U8 k, rv;
   CmLteTimingInfo frm;
   ;;

   frm = cell->crntTime;
   do { if ((frm.subframe += (2 + 0)) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);

   if(si)
   {
      k = i % 4;
   }
   else
   {
      k = (frm.sfn/2) % 4;
   }
   rv = (((3*k) + (2)-1) / (2)) % 4;
   return(rv);
}
static Void rgSCHCmnDlBcchPcchFnlz
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   RgSchDlRbAlloc *rbAllocInfo;
   RgSchDlSf *subFrm;







   U8 nextSfIdx = (cell->crntSfIdx) % 10;




   RgSchClcDlLcCb *pcch;
   RgSchClcBoRpt *bo;




   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);

   ;;


   rbAllocInfo = &allocInfo->pcchAlloc;
   if (rbAllocInfo->pdcch)
   {
      RgInfSfAlloc *subfrmAlloc = &(cell->sfAllocArr[nextSfIdx]);






      nextSfIdx = (cell->crntSfIdx) % 10;


      subFrm = rbAllocInfo->dlSf;
      pcch = rgSCHDbmGetPcch(cell);
      if(pcch == 0L)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0037,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                13032         , "rgSCHCmnDlBcchPcchFnlz( ): " "No Pcch Present", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                 ;
         return;
      }





      bo = (RgSchClcBoRpt *)pcch->boLst.first->node;
      cmLListDelFrm(&pcch->boLst, &bo->boLstEnt);


      rgSCHUtlFreeSBuf(cell->instIdx, (Data **)&bo, sizeof(RgSchClcBoRpt));

      subFrm->pcch.tbSize = rbAllocInfo->tbInfo[0].bytesAlloc;
      subFrm->pcch.pdcch = rbAllocInfo->pdcch;

      rgSCHCmnFillPdcch(cell, subFrm->pcch.pdcch, rbAllocInfo);
      rgSCHUtlFillRgInfCmnLcInfo(subFrm, subfrmAlloc, pcch->lcId, 1);


      subfrmAlloc->cmnLcInfo.pcchInfo.txPwrOffset = cellDl->pcchTxPwrOffset;
   }


   rbAllocInfo = &allocInfo->bcchAlloc;
   if (rbAllocInfo->pdcch)
   {
      RgInfSfAlloc *subfrmAlloc = &(cell->sfAllocArr[nextSfIdx]);




      nextSfIdx = (cell->crntSfIdx) % 10;


      subFrm = rbAllocInfo->dlSf;


      subFrm->bcch.tbSize = rbAllocInfo->tbInfo[0].bytesAlloc;
      subFrm->bcch.pdcch = rbAllocInfo->pdcch;

      rgSCHCmnFillPdcch(cell, subFrm->bcch.pdcch, rbAllocInfo);

      if(rbAllocInfo->schdFirst)
      {





         SCpyMsgMsg(cell->siCb.crntSiInfo.sib1Info.sib1,
               rgSchCb[cell->instIdx].rgSchInit.region,
               rgSchCb[cell->instIdx].rgSchInit.pool,
               &subfrmAlloc->cmnLcInfo.bcchInfo.pdu);

         subFrm->bcch.pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.rv =
            rgSCHCmnDlCalcRvForBcch(cell, 0, 0);
      }
      else
      {
         U16 i;

         Buffer *pdu;

         i = cell->siCb.siCtx.i;

         cell->siCb.siCtx.retxCntRem--;


         if(cell->siCb.siCtx.warningSiFlag == 0)
         {
            SCpyMsgMsg(cell->siCb.siArray[cell->siCb.siCtx.siId-1].si,
                  rgSchCb[cell->instIdx].rgSchInit.region,
                  rgSchCb[cell->instIdx].rgSchInit.pool,
                  &subfrmAlloc->cmnLcInfo.bcchInfo.pdu);
         }
         else
         {
            pdu = rgSCHUtlGetWarningSiPdu(cell);
            ;
            SCpyMsgMsg(pdu,
                  rgSchCb[cell->instIdx].rgSchInit.region,
                  rgSchCb[cell->instIdx].rgSchInit.pool,
                  &subfrmAlloc->cmnLcInfo.bcchInfo.pdu);
            if(cell->siCb.siCtx.retxCntRem == 0)
            {
               rgSCHUtlFreeWarningSiPdu(cell);
               cell->siCb.siCtx.warningSiFlag = 0;

            }
         }
         subFrm->bcch.pdcch->dci.u.format1aInfo.t.pdschInfo.allocInfo.rv =
            rgSCHCmnDlCalcRvForBcch(cell, 1, i);
      }
      rgSCHUtlFillRgInfCmnLcInfo(subFrm, subfrmAlloc, 0L, 0L);



      subfrmAlloc->cmnLcInfo.bcchInfo.txPwrOffset = cellDl->bcchTxPwrOffset;



   }

   return;
}
 Void rgSCHCmnUlAdd2CntResLst
(
RgSchCmnUlRbAllocInfo *allocInfo,
RgSchUeCb *ue
)





{
   RgSchCmnUeUlAlloc *ulAllocInfo = &(((&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((ue->cell->cellId >= rgSchCb[ue->cell->instIdx].genCfg.startCellId) ? (ue->cell->cellId - rgSchCb[ue->cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul)))->alloc);
   ;;
   cmLListAdd2Tail(&allocInfo->contResLst, &ulAllocInfo->reqLnk);
   ulAllocInfo->reqLnk.node = (U32)ue;
   return;
}
 Void rgSCHCmnUlAdd2UeLst
(
RgSchCellCb *cell,
RgSchCmnUlRbAllocInfo *allocInfo,
RgSchUeCb *ue
)






{
   RgSchCmnUeUlAlloc *ulAllocInfo = &(((&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul)))->alloc);
   ;;
   if (ulAllocInfo->reqLnk.node == 0L)
   {
      cmLListAdd2Tail(&allocInfo->ueLst, &ulAllocInfo->reqLnk);
      ulAllocInfo->reqLnk.node = (U32)ue;
   }
   return;
}
 Void rgSCHCmnAllocUlRb
(
RgSchCellCb *cell,
RgSchCmnUlRbAllocInfo *allocInfo
)





{
   RgSchUlSf *sf = allocInfo->sf;
   ;;

   sf->numACqiCount = 0;


   rgSCHCmnUlRbAllocForLst(cell, sf, allocInfo->contResLst.count,
         &allocInfo->contResLst, &allocInfo->schdContResLst,
         &allocInfo->nonSchdContResLst, (Bool)0);


   rgSCHCmnUlRbAllocForLst(cell, sf, allocInfo->ueLst.count,
         &allocInfo->ueLst, &allocInfo->schdUeLst,
         &allocInfo->nonSchdUeLst, (Bool)1);
   return;
}
static Void rgSCHCmnUlRbAllocForLst
(
RgSchCellCb *cell,
RgSchUlSf *sf,
U32 count,
CmLListCp *reqLst,
CmLListCp *schdLst,
CmLListCp *nonSchdLst,
Bool isNewTx
)
{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   CmLList *lnk;
   U8 sbCount;
   U8 leftOverSb = 0;
   U8 leftOverSbPerUe = 0;
   U8 leftOverSbForNxtUe = 0;
   RgSchUlHole *hole;






   ;;

   if(schdLst->count == 0)
   {
      cmLListInit(schdLst);
   }

   cmLListInit(nonSchdLst);
   for (lnk = reqLst->first; count; lnk = lnk->next, --count)
   {
      RgSchUeCb *ue = (RgSchUeCb *)lnk->node;
      RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
      S16 ret;
      U8 maxRb;
      U8 maxSb=0;


      if ((hole = rgSCHUtlUlHoleFirst(sf)) == 0L)
      {
         break;
      }


      if(isNewTx == 1)
      {
         if (rgSchCb[cell->instIdx].rgrSchedEnbCfg.ulSchdType == 2)
         {

            ueUl->subbandShare = sf->availSubbands;
         }
         else
         {
            if(!ueUl->subbandShare)
            {
               ueUl->subbandShare = sf->availSubbands;
            }
            ueUl->subbandShare += (leftOverSbPerUe + leftOverSbForNxtUe);
         }
         leftOverSbForNxtUe = 0;
         maxSb = hole->num;

         sbCount = ((ueUl->subbandShare) <= (maxSb) ? (ueUl->subbandShare) : (maxSb));
      }

      maxRb = rgSCHPwrGetMaxUlRb(cell, ue);
      if(isNewTx == 1)
      {
         maxRb = (((sbCount * cellUl->sbSize)) <= (maxRb) ? ((sbCount * cellUl->sbSize)) : (maxRb));
      }

      ret = rgSCHCmnUlRbAllocForUe(cell, sf, ue, maxRb, hole);
      if (ret == 0)
      {
         rgSCHCmnUlRbAllocAddUeToLst(cell, ue, schdLst);
         rgSCHCmnUlUeFillAllocInfo(cell, ue);
      }
      else
      {
         rgSCHCmnUlRbAllocAddUeToLst(cell, ue, nonSchdLst);
         ue->isMsg4PdcchWithCrnti = 0;
         ue->isSrGrant = 0;
      }
      if((isNewTx == 1) &&
         (rgSchCb[cell->instIdx].rgrSchedEnbCfg.ulSchdType != 2) &&
         (count > 1))
      {
         leftOverSb = ueUl->subbandShare - (maxSb - hole->num);


         leftOverSbPerUe += (leftOverSb / (count - 1));

         leftOverSbForNxtUe = (leftOverSb % (count - 1));
      }
      ueUl->subbandShare = 0;

   }
   for (; count; lnk = lnk->next, --count)
   {
      RgSchUeCb *ue = (RgSchUeCb *)lnk->node;
      rgSCHCmnUlRbAllocAddUeToLst(cell, ue, nonSchdLst);
      ue->isMsg4PdcchWithCrnti = 0;
   }
   return;
}
static S16 rgSCHCmnUlMdfyGrntForCqi
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U32 maxRb,
U32 *numSb,
U8 *iTbs,
U32 hqSz,
U32 stepDownItbs,
U32 effTgt
)
{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((ue->cell)->sc.sch))->ul);
   U32 nPrb;
   U32 totREs;
   U32 cqiRiREs;
   U32 hqREs;
   U32 remREsForPusch;
   U32 bitsPerRe;
   U32 tbSz;
   U32 betaOffVal = ue->ul.betaOffstVal;
   U32 cqiRiRptSz = ue->ul.cqiRiSz;
   U32 betaOffHqVal = rgSchCmnBetaHqOffstTbl[ue->ul.betaHqOffst];
   U32 resNumSb = *numSb;
   U32 puschEff = 1000;
   U8 modOdr;
   U8 iMcs;
   Bool mdfyiTbsFlg = 0;
   U8 resiTbs = *iTbs;

   ;


   do
   {
      iMcs = rgSCHCmnUlGetIMcsFrmITbs(resiTbs, ((&(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn))->ueCat + 1));
      do { ; modOdr = (TfuModScheme)rgUlIMcsTbl[iMcs].qm;} while(0);
      if (((&(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn))->ueCat + 1) != CM_LTE_UE_CAT_5)
      {
         modOdr = ((4) <= (modOdr) ? (4) : (modOdr));
      }
      else
      {
         modOdr = ((6) <= (modOdr) ? (6) : (modOdr));
      }
      nPrb = resNumSb * cellUl->sbSize;

      if ((nPrb >= maxRb) && (resiTbs <= 10))
      {

         return(1);
      }
      totREs = nPrb * ((cellUl)->ulNumRePerRb);
      tbSz = rgTbSzTbl[0][resiTbs][nPrb-1];

      cqiRiREs = (totREs * betaOffVal * cqiRiRptSz)/(1000 * tbSz);

      hqREs = (totREs * betaOffHqVal * hqSz)/(1000 * tbSz);
      if ((cqiRiREs + hqREs) < totREs)
      {
         remREsForPusch = totREs - cqiRiREs - hqREs;
         bitsPerRe = (tbSz * 1000)/remREsForPusch;
         puschEff = bitsPerRe/modOdr;
      }
      if (puschEff < effTgt)
      {

          break;
      }
      else
      {

         if (mdfyiTbsFlg == 0)
         {
            if (nPrb < maxRb)
            {
              resNumSb = resNumSb + 1;
            }
            mdfyiTbsFlg = 1;
         }
         else
         {
            if (resiTbs > 10)
            {
               resiTbs-= stepDownItbs;
            }
            mdfyiTbsFlg = 0;
         }
      }
   }while (1);


   *numSb = resNumSb;
   *iTbs = resiTbs;

   return(0);
}
static S16 rgSCHCmnUlRbAllocForUe
(
RgSchCellCb *cell,
RgSchUlSf *sf,
RgSchUeCb *ue,
U8 maxRb,
RgSchUlHole *hole
)
{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   U8 sbSize = cellUl->sbSize;
   U32 maxBits = ue->ul.maxBytesPerUePerTti*8;
   U32 bits;
   RgSchUlAlloc *alloc = 0L;
   U32 nPrb = 0;
   U8 iTbs;
   U32 eff;
   U8 numSb;
   Bool limit = 0;
   U8 iMcs;
   U8 iMcsCrnt;
   RgSchUlHqProcCb *proc = &ueUl->hqEnt.hqProcCb[cellUl->schdHqProcIdx];
   RgSchPdcch *pdcch;
   U32 reqSb;

   CmLteUeCategory ueCtg = (CmLteUeCategory)(((&(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn))->ueCat + 1));
   U32 hqSz = 0;





   ;;

   pdcch = rgSCHCmnPdcchAllocCrntSf(cell, ue);
   if(pdcch == 0L)
   {
      if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0038,L_DEBUG,DBG_CELLID, cell->cellId,ue->ueId, 0, 0, 0,                                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                              13710      , "rgSCHCmnUlRbAllocForUe(): Could not get PDCCH for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                               ;
      return(1);
   }

   iTbs = rgSCHCmnUlGetITbs(cell, ue, cell->isCpUlExtend);

   if (!cell->isCpUlExtend)
   {
      ;
      eff = rgSchCmnNorUlEff[0][iTbs];
   }
   else
   {
      ;
      eff = rgSchCmnExtUlEff[0][iTbs];
   }

   bits = ueUl->alloc.reqBytes * 8;
   if (bits < rgSCHCmnUlMinTbBitsForITbs(cellUl, iTbs))
   {
      if (!maxRb)
      {
         limit = 1;
         numSb = 0;
      }
      else
      {
         numSb = 1;
         nPrb = numSb * sbSize;
      }
   }
   else
   {
      if (bits > maxBits)
      {
         bits = maxBits;
         nPrb = bits * 1024 / eff / ((cellUl)->ulNumRePerRb);
         if (nPrb > maxRb)
         {
            limit = 1;
            nPrb = maxRb;
         }
         numSb = nPrb / sbSize;
      }
      else
      {
         nPrb = (((((((bits * 1024) + (eff)/2) / (eff)))) + (((cellUl)->ulNumRePerRb))/2) / (((cellUl)->ulNumRePerRb)))
                                                   ;
         if (nPrb > maxRb)
         {
            limit = 1;
            nPrb = maxRb;
         }
         numSb = (((nPrb) + (sbSize)/2) / (sbSize));
      }
   }
   if (!numSb)
   {
      if (limit)
      {
         rgSCHCmnPdcchRlsCrntSf(cell, pdcch);
         return(1);
      }
      else
      {
         ++numSb;

         nPrb = numSb * sbSize;
      }
   }


   if((numSb*sbSize) > maxRb)
   {

     numSb = (maxRb/sbSize);

     nPrb = numSb * sbSize;
   }

   if(!numSb)
   {

       numSb = 1;

       nPrb = numSb * sbSize;
   }


   reqSb = numSb;
   ue->dl.acqiResGrntd = 0;
   if((sf->numACqiCount < 1) && (RG_SCH_APCQI_NO != ue->dl.reqForCqi))
   {
      if (rgSCHCmnUlMdfyGrntForCqi(cell, ue, maxRb, &reqSb, &iTbs, hqSz, 1, 530) == 0)
      {
         sf->numACqiCount++;
         ue->dl.acqiResGrntd = 1;
      }
   }
   else if (ue->dl.pCqiPrsnt == 1)
   {
      if (ue->ul.cqiRiSz > 0)
      {
         rgSCHCmnUlMdfyGrntForCqi(cell, ue, maxRb, &reqSb, &iTbs, hqSz, 1, 930);
      }
   }
   else if (hqSz == 2)
   {
      ue->ul.cqiRiSz = 0;
      rgSCHCmnUlMdfyGrntForCqi(cell, ue, maxRb, &reqSb, &iTbs, hqSz, 1, 930);
   }


   iMcs = rgSCHCmnUlGetIMcsFrmITbs(iTbs,ueCtg);
   iMcsCrnt = iMcs;
   numSb = reqSb;


   if(numSb)
   {
      alloc = rgSCHCmnUlSbAlloc(sf, (U8) (((numSb) <= (cellUl->maxSbPerUe) ? (numSb) : (cellUl->maxSbPerUe))),
                                hole);
   }
   if (alloc == 0L)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0039,L_ERROR,DBG_CELLID, cell->cellId,numSb, ue->ueId, 0, 0,                                                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                                     13869      , "rgSCHCmnUlRbAllocForUe(): Could not get UlAlloc %d CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                      ;
      rgSCHCmnPdcchRlsCrntSf(cell, pdcch);
      return(1);
   }
   rgSCHCmnUlAllocFillRbInfo(cell, sf, alloc);




   if (ue->csgMmbrSta != 1)
   {
      cellUl->ncsgPrbCnt += alloc->grnt.numRb;
   }
   cellUl->totPrbCnt += alloc->grnt.numRb;
   alloc->pdcch = pdcch;
   alloc->grnt.iMcs = iMcs;
   alloc->grnt.iMcsCrnt = iMcsCrnt;
   alloc->grnt.hop = 0;


   ue->initNumRbs = alloc->grnt.numRb;

   alloc->forMsg3 = 0;
   ;

   ueUl->alloc.allocdBytes = rgTbSzTbl[0][iTbs][alloc->grnt.numRb-1] / 8;


   rgUlrate_grant += ueUl->alloc.allocdBytes;


   alloc->grnt.datSz = ueUl->alloc.allocdBytes;
   do { ; alloc->grnt.modOdr = (TfuModScheme)rgUlIMcsTbl[iMcs].qm;} while(0);
   alloc->grnt.isRtx = 0;
   alloc->hqProc = proc;
   alloc->hqProc->ulSfIdx = cellUl->schdIdx;
   alloc->ue = ue;

   alloc->rnti = ue->ueId;
   ueUl->alloc.alloc = alloc;


   return(0);
}
 Void rgSCHCmnUlRbAllocAddUeToLst
(
RgSchCellCb *cell,
RgSchUeCb *ue,
CmLListCp *lst
)






{
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   ;;
   (cell=cell);

   cmLListAdd2Tail(lst, &ueUl->alloc.schdLstLnk);
   ueUl->alloc.schdLstLnk.node = (U32)ue;
}
static Void rgSCHCmnUlAllocFnlz
(
RgSchCellCb *cell,
RgSchCmnUlRbAllocInfo *allocInfo
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;


   cellSch->apisUl->rgSCHUlAllocFnlz(cell, allocInfo);

   return;
}
 Void rgSCHCmnDlAllocFnlz
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlRbAllocInfo *allocInfo = &cellSch->allocInfo;

   ;;

   rgSCHCmnDlCcchRetxFnlz(cell, allocInfo);
   rgSCHCmnDlCcchTxFnlz(cell, allocInfo);



   rgSCHCmnDlCcchSduRetxFnlz(cell, allocInfo);
   rgSCHCmnDlCcchSduTxFnlz(cell, allocInfo);

   rgSCHCmnDlRaRspFnlz(cell, allocInfo);



   rgSCHCmnSpsDlAllocFnlz(cell, allocInfo);







   cellSch->apisDl->rgSCHDlAllocFnlz(cell, allocInfo);


   return;

}
static Void rgSCHCmnUlAlloc
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchCmnUlRbAllocInfo allocInfo;
   RgSchCmnUlRbAllocInfo *allocInfoRef = &allocInfo;

   ;;


   rgSCHCmnInitUlRbAllocInfo(allocInfoRef);


   allocInfoRef->sf = &cellUl->ulSfArr[cellUl->schdIdx];






   rgSCHCmnSpsUlTti(cell, allocInfoRef);


   if(*allocInfoRef->sf->allocCountRef == 0)
   {
      RgSchUlHole *hole;

      if ((hole = rgSCHUtlUlHoleFirst(allocInfoRef->sf)) != 0L)
      {

         if (allocInfoRef->sf->holeDb->count == 1 && hole->start == 0)
         {
            hole->num = cell->dynCfiCb.bwInfo[cellDl->currCfi].numSb;

            allocInfoRef->sf->availSubbands = cell->dynCfiCb.
                                              bwInfo[cellDl->currCfi].numSb;
         }
         else
         {
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb003a,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                                        14257            , "Error! holeDb sanity check failed", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                         ;
         }
      }
   }



   rgSCHCmnUlSfReTxAllocs(cell, allocInfoRef->sf);
   rgSCHCmnUlSfRlsRetxProcs(cell, allocInfoRef->sf);


   cellSch->apisUl->rgSCHUlSched(cell, allocInfoRef);


   rgSCHCmnAllocUlRb(cell, allocInfoRef);


   rgSCHCmnGrpPwrCntrlPusch(cell, allocInfoRef->sf);

   cell->sc.apis->rgSCHDrxStrtInActvTmrInUl(cell);

   rgSCHCmnUlAllocFnlz(cell, allocInfoRef);

   return;
}
 Void rgSCHCmnSndCnsldtInfo
(
RgSchCellCb *cell
)




{
   RgInfSfAlloc *subfrmAlloc;
   Pst pst;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;

   subfrmAlloc = &(cell->sfAllocArr[cell->crntSfIdx]);


   rgSCHUtlGetPstToLyr(&pst, &rgSchCb[cell->instIdx], cell->macInst);
   subfrmAlloc->cellId = cell->cellId;

   cellSch->apisDl->rgSCHDlFillFlwCtrlInfo(cell, subfrmAlloc);







   if((subfrmAlloc->rarInfo.numRaRntis) ||
      (subfrmAlloc->ueInfo.numUes) ||
            (subfrmAlloc->cmnLcInfo.bitMask) ||
            (subfrmAlloc->flowCntrlInfo.numUes))

   {
      RgSchMacSfAlloc(&pst, subfrmAlloc);
   }

   cell->crntSfIdx = (cell->crntSfIdx + 1) % 10;




   return;
}
 Void rgSCHCmnCnsldtSfAlloc
(
RgSchCellCb *cell
)




{
   RgInfSfAlloc *subfrmAlloc;
   CmLteTimingInfo frm;
   RgSchDlSf *dlSf;
   CmLListCp dlDrxInactvTmrLst;
   CmLListCp dlInActvLst;
   CmLListCp ulInActvLst;
   RgSchCmnCell *cellSch = 0L;

   ;;

   cmLListInit(&dlDrxInactvTmrLst);
   cmLListInit(&dlInActvLst);
   cmLListInit(&ulInActvLst);

   subfrmAlloc = &(cell->sfAllocArr[cell->crntSfIdx]);







   if ((cell->crntTime.subframe + ((2 + 0) - 2)) >= 10) subfrmAlloc->timingInfo.sfn = (cell->crntTime.sfn + (cell->crntTime.subframe + ((2 + 0) - 2))/10) % 1024; else subfrmAlloc->timingInfo.sfn = cell->crntTime.sfn; subfrmAlloc->timingInfo.subframe = (cell->crntTime.subframe + ((2 + 0) - 2)) % 10;
                                                       ;



   frm = cell->crntTime;
   do { if ((frm.subframe += (2 + 0)) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);
   dlSf = rgSCHUtlSubFrmGet(cell, frm);


   rgSCHUtlFillRgInfRarInfo(dlSf, subfrmAlloc, cell);


   rgSCHUtlFillRgInfUeInfo(dlSf, cell, &dlDrxInactvTmrLst,
                           &dlInActvLst, &ulInActvLst);




   cellSch = ((RgSchCmnCell *)((cell)->sc.sch));


   cellSch->apisUl->rgSCHUlInactvtUes(cell, &ulInActvLst);
   cellSch->apisDl->rgSCHDlInactvtUes(cell, &dlInActvLst);



   (Void)rgSCHDrxStrtInActvTmr(cell,&dlDrxInactvTmrLst,1);

   return;
}
static Void rgSCHCmnInitDlRbAllocInfo
(
RgSchCmnDlRbAllocInfo *allocInfo
)




{
   ;;
   cmMemset((U8 *)&allocInfo->pcchAlloc, (U8)0, sizeof(RgSchDlRbAlloc));
   cmMemset((U8 *)&allocInfo->bcchAlloc, (U8)0, sizeof(RgSchDlRbAlloc));
   cmMemset((U8 *)allocInfo->raRspAlloc, (U8)0,
         4*sizeof(RgSchDlRbAlloc));

   allocInfo->msg4Alloc.msg4DlSf = 0L;
   cmLListInit(&allocInfo->msg4Alloc.msg4TxLst);
   cmLListInit(&allocInfo->msg4Alloc.msg4RetxLst);
   cmLListInit(&allocInfo->msg4Alloc.schdMsg4TxLst);
   cmLListInit(&allocInfo->msg4Alloc.schdMsg4RetxLst);
   cmLListInit(&allocInfo->msg4Alloc.nonSchdMsg4TxLst);
   cmLListInit(&allocInfo->msg4Alloc.nonSchdMsg4RetxLst);

   allocInfo->ccchSduAlloc.ccchSduDlSf = 0L;
   cmLListInit(&allocInfo->ccchSduAlloc.ccchSduTxLst);
   cmLListInit(&allocInfo->ccchSduAlloc.ccchSduRetxLst);
   cmLListInit(&allocInfo->ccchSduAlloc.schdCcchSduTxLst);
   cmLListInit(&allocInfo->ccchSduAlloc.schdCcchSduRetxLst);
   cmLListInit(&allocInfo->ccchSduAlloc.nonSchdCcchSduTxLst);
   cmLListInit(&allocInfo->ccchSduAlloc.nonSchdCcchSduRetxLst);


   allocInfo->dedAlloc.dedDlSf = 0L;
   cmLListInit(&allocInfo->dedAlloc.txHqPLst);
   cmLListInit(&allocInfo->dedAlloc.retxHqPLst);
   cmLListInit(&allocInfo->dedAlloc.schdTxHqPLst);
   cmLListInit(&allocInfo->dedAlloc.schdRetxHqPLst);
   cmLListInit(&allocInfo->dedAlloc.nonSchdTxHqPLst);
   cmLListInit(&allocInfo->dedAlloc.nonSchdRetxHqPLst);

   cmLListInit(&allocInfo->dedAlloc.txRetxHqPLst);
   cmLListInit(&allocInfo->dedAlloc.schdTxRetxHqPLst);
   cmLListInit(&allocInfo->dedAlloc.nonSchdTxRetxHqPLst);

   cmLListInit(&allocInfo->dedAlloc.txSpsHqPLst);
   cmLListInit(&allocInfo->dedAlloc.retxSpsHqPLst);
   cmLListInit(&allocInfo->dedAlloc.schdTxSpsHqPLst);
   cmLListInit(&allocInfo->dedAlloc.schdRetxSpsHqPLst);
   cmLListInit(&allocInfo->dedAlloc.nonSchdTxSpsHqPLst);
   cmLListInit(&allocInfo->dedAlloc.nonSchdRetxSpsHqPLst);

   cmLListInit(&allocInfo->dedAlloc.txLaaHqPLst);
   cmLListInit(&allocInfo->dedAlloc.schdTxLaaHqPLst);
   cmLListInit(&allocInfo->dedAlloc.nonSchdTxLaaHqPLst);


   cmLListInit(&allocInfo->dedAlloc.errIndTxHqPLst);
   cmLListInit(&allocInfo->dedAlloc.schdErrIndTxHqPLst);
   cmLListInit(&allocInfo->dedAlloc.nonSchdErrIndTxHqPLst);
   return;
}
static Void rgSCHCmnInitUlRbAllocInfo
(
RgSchCmnUlRbAllocInfo *allocInfo
)




{
   ;;
   allocInfo->sf = 0L;
   cmLListInit(&allocInfo->contResLst);
   cmLListInit(&allocInfo->schdContResLst);
   cmLListInit(&allocInfo->nonSchdContResLst);
   cmLListInit(&allocInfo->ueLst);
   cmLListInit(&allocInfo->schdUeLst);
   cmLListInit(&allocInfo->nonSchdUeLst);

   return;
}
static Void rgSCHCmnGrpPwrCntrlPucch
(
RgSchCellCb *cell,
RgSchDlSf *dlSf
)





{
   ;;

   rgSCHPwrGrpCntrlPucch(cell, dlSf);

   return;
}
static Void rgSCHCmnGrpPwrCntrlPusch
(
RgSchCellCb *cell,
RgSchUlSf *ulSf
)





{

   CmLteTimingInfo frm;
   RgSchDlSf *dlSf;

   ;;




   frm = cell->crntTime;

   do { if ((frm.subframe += 2) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);

   dlSf = rgSCHUtlSubFrmGet(cell, frm);

   rgSCHPwrGrpCntrlPusch(cell, dlSf, ulSf);

   return;
}
static S16 rgSCHCmnApplyUeRefresh
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U32 effGbrBsr = 0;
   U32 effNonGbrBsr = 0;
   U32 lcgId;

   ;;


   ue->ul.effAmbr = ue->ul.cfgdAmbr;

   for (lcgId = 1; lcgId < 4; lcgId++)
   {
      if (((&ue->ul.lcgArr[lcgId])->lcgId != 255))
      {
         RgSchCmnLcg *cmnLcg = ((RgSchCmnLcg *)(ue->ul.lcgArr[lcgId].sch));

         if (((cmnLcg->cfgdGbr) != 0))
         {
            cmnLcg->effGbr = cmnLcg->cfgdGbr;
            cmnLcg->effDeltaMbr = cmnLcg->deltaMbr;
            cmnLcg->bs = ((cmnLcg->reportedBs) <= (cmnLcg->effGbr + cmnLcg->effDeltaMbr) ? (cmnLcg->reportedBs) : (cmnLcg->effGbr + cmnLcg->effDeltaMbr));

            effGbrBsr += cmnLcg->bs;
         }
         else
         {
            effNonGbrBsr += cmnLcg->reportedBs;
            cmnLcg->bs = ((cmnLcg->reportedBs) <= (ue->ul.effAmbr) ? (cmnLcg->reportedBs) : (ue->ul.effAmbr));
         }
      }
   }
   effNonGbrBsr = ((effNonGbrBsr) <= (ue->ul.effAmbr) ? (effNonGbrBsr) : (ue->ul.effAmbr));
   ue->ul.nonGbrLcgBs = effNonGbrBsr;

   ue->ul.nonLcg0Bs = effGbrBsr + effNonGbrBsr;
   ue->ul.effBsr = ue->ul.nonLcg0Bs +
                  ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs;




   cellSch->apisUl->rgSCHUlUeRefresh(cell, ue);
   cellSch->apisDl->rgSCHDlUeRefresh(cell, ue);

   return(0);
}
static S16 rgSCHCmnTmrExpiry
(
U32 cb,
S16 tmrEvnt
)





{
   RgSchUeCb *ue = (RgSchUeCb *)cb;
   RgSchCellCb *cell = ue->cell;



   ;;
   (tmrEvnt=tmrEvnt);


   rgSCHCmnApplyUeRefresh(cell, ue);

   rgSCHCmnAddUeToRefreshQ(cell, ue, 32);

   return(0);
}
static S16 rgSCHCmnTmrProc
(
RgSchCellCb *cell
)




{
   RgSchCmnDlCell *cmnDlCell = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchCmnUlCell *cmnUlCell = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);


   ;;

   if (cell->crntTime.subframe == 0)
   {

      if ((cell->crntTime.sfn % 16) == 0)
      {
         { (cmnDlCell)->ncsgPrbCnt = 0; (cmnDlCell)->totPrbCnt = 1; };
         { (cmnUlCell)->ncsgPrbCnt = 0; (cmnUlCell)->totPrbCnt = 1; };
      }
      if ((cell->crntTime.sfn % 50) == 0)
      {

         cell->measurements.ulTpt = ((cell->measurements.ulTpt * 95) + ( cell->measurements.ulBytesCnt * 5))/100;
         cell->measurements.dlTpt = ((cell->measurements.dlTpt * 95) + ( cell->measurements.dlBytesCnt * 5))/100;

         rgSCHUtlCpuOvrLdAdjItbsCap(cell);

         cell->measurements.ulBytesCnt = 0;
         cell->measurements.dlBytesCnt = 0;
      }



      RgSchCmnCell *sched = ((RgSchCmnCell *)((cell)->sc.sch));
      cmPrcTmr(&sched->tmrTqCp, sched->tmrTq, (PFV)rgSCHCmnTmrExpiry);
   }

   return(0);
}
static Void rgSchCmnUpdCfiVal
(
RgSchCellCb *cell,
U8 delta
)





{
   RgSchDlSf *dlSf;
   CmLteTimingInfo pdsch;
   RgSchCmnDlCell *cellCmnDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   U8 dlIdx;







   ;;

   pdsch = cell->crntTime;
   do { if ((pdsch.subframe += delta) > 9) { pdsch.sfn = ((pdsch.sfn) + 1) & 0x03ff; pdsch.subframe -= 10; }} while(0);
   dlSf = rgSCHUtlSubFrmGet(cell, pdsch);




   dlSf->pdcchInfo.currCfi = cellCmnDl->currCfi;
   if(cell->dynCfiCb.pdcchSfIdx != 0xFF)
   {



      dlIdx = (((pdsch.sfn & 1) * 10) + pdsch.subframe);
      ;



      if(cell->dynCfiCb.pdcchSfIdx == dlIdx)
      {
         cellCmnDl->currCfi = cellCmnDl->newCfi;
         cell->dynCfiCb.pdcchSfIdx = 0xFF;
         cell->nCce = cell->dynCfiCb.cfi2NCceTbl[0][cellCmnDl->currCfi];




         dlSf->pdcchInfo.currCfi = cellCmnDl->currCfi;
         cell->dynCfiCb.switchOvrWinLen = rgSchCfiSwitchOvrWinLen[7];

      }
   }

   return;
}
static Void rgSchCmnUpdtPdcchSfIdx
(
RgSchCellCb *cell,
U8 dlIdx
)






{
   U8 idx;

   ;;


   cell->dynCfiCb.cceUsed = 0;
   cell->dynCfiCb.lowCceCnt = 0;

   cell->dynCfiCb.cceFailSum = 0;
   cell->dynCfiCb.cceFailCnt = 0;
   cell->dynCfiCb.prevCceFailIdx = 0;

   cell->dynCfiCb.switchOvrInProgress = 1;

   for(idx = 0; idx < cell->dynCfiCb.numFailSamples; idx++)
   {
      cell->dynCfiCb.cceFailSamples[idx] = 0;
   }

   cell->dynCfiCb.ttiCnt = 0;

   cell->dynCfiCb.cfiSwitches++;
   cfiSwitchCnt = cell->dynCfiCb.cfiSwitches;





   cell->dynCfiCb.pdcchSfIdx = (dlIdx + 4) %
        20;

}
 Void rgSchCmnUpdCfiDb
(
RgSchCellCb *cell,
U8 delta
)





{
   CmLteTimingInfo frm;
   RgSchDlSf *dlSf;




   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U8 nCceLowerCfi = 0;
   U8 currCfi;
   U8 cceFailIdx;
   U32 totalCce;
   U8 dlIdx;
   U16 ttiMod;

   ;;


   frm = cell->crntTime;
   do { if ((frm.subframe += delta) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);
   dlIdx = (((frm.sfn & 1) * 10) + frm.subframe);
   ;
   dlSf = cell->subFrms[dlIdx];


   currCfi = cellSch->dl.currCfi;

   if(!cell->dynCfiCb.switchOvrInProgress)
   {
      do{
         if(!cell->dynCfiCb.isDynCfiEnb)
         {
            if(currCfi != cellSch->cfiCfg.cfi)
            {
               if(currCfi < cellSch->cfiCfg.cfi)
               {
                  { cellSch->dl.newCfi = ((currCfi) < cell->dynCfiCb.maxCfi) ? (currCfi + 1):cell->dynCfiCb.maxCfi; cell->dynCfiCb.cfiIncr++; }
                  cfiIncr = cell->dynCfiCb.cfiIncr;
               }
               else
               {
                  { cellSch->dl.newCfi = currCfi-1; cell->dynCfiCb.cfiDecr++; }
                  cfiDecr = cell->dynCfiCb.cfiDecr;
               }
            }
            break;
         }
         {
            ttiMod = cell->dynCfiCb.ttiCnt % 1000;
         }

         dlSf->dlUlBothCmplt++;



         if(dlSf->dlUlBothCmplt == 2)

         {


            cell->dynCfiCb.cceFailCnt += dlSf->isCceFailure;
            cell->dynCfiCb.cceFailSum += dlSf->isCceFailure;


            if(currCfi < cell->dynCfiCb.maxCfi)
            {
               if(cell->dynCfiCb.cceFailSum >= cell->dynCfiCb.cfiStepUpTtiCnt)
               {
                  { cellSch->dl.newCfi = ((currCfi) < cell->dynCfiCb.maxCfi) ? (currCfi + 1):cell->dynCfiCb.maxCfi; cell->dynCfiCb.cfiIncr++; }
                  cfiIncr = cell->dynCfiCb.cfiIncr;
                  break;
               }
            }




            cell->dynCfiCb.cceUsed += dlSf->cceCnt;

            if(currCfi > 1)
            {





               nCceLowerCfi = cell->dynCfiCb.cfi2NCceTbl[0][currCfi-1];

               if(dlSf->cceCnt < nCceLowerCfi)
               {


                  cell->dynCfiCb.lowCceCnt++;
               }

               if(ttiMod == 0)
               {
                  totalCce = (nCceLowerCfi * cell->dynCfiCb.cfiStepDownTtiCnt *
                        90)/100;

                  if((!cell->dynCfiCb.cceFailSum) &&
                        (cell->dynCfiCb.lowCceCnt >=
                         cell->dynCfiCb.cfiStepDownTtiCnt) &&
                        (cell->dynCfiCb.cceUsed < totalCce))
                  {
                     { cellSch->dl.newCfi = currCfi-1; cell->dynCfiCb.cfiDecr++; }
                     cfiDecr = cell->dynCfiCb.cfiDecr;
                     break;
                  }
               }
            }

            cceFailIdx = ttiMod/cell->dynCfiCb.failSamplePrd;

            if(cceFailIdx != cell->dynCfiCb.prevCceFailIdx)
            {


               cell->dynCfiCb.cceFailSum -= cell->dynCfiCb.cceFailSamples[cceFailIdx];


               cell->dynCfiCb.cceFailSamples[cell->dynCfiCb.prevCceFailIdx]
                  = cell->dynCfiCb.cceFailCnt;

               cell->dynCfiCb.prevCceFailIdx = cceFailIdx;


               cell->dynCfiCb.cceFailCnt = 0;
            }

            if(ttiMod == 0)
            {

               cell->dynCfiCb.cceUsed = 0;
               cell->dynCfiCb.lowCceCnt = 0;
               cell->dynCfiCb.ttiCnt = 0;
            }

            cell->dynCfiCb.ttiCnt++;
         }
      }while(0);

      if(cellSch->dl.newCfi != cellSch->dl.currCfi)
      {



         rgSchCmnUpdtPdcchSfIdx(cell, dlIdx);

      }
   }
}
 Void rgSCHCmnDlCommonChSch
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;

   cellSch->apisDl->rgSCHDlTickForPdbTrkng(cell);
   rgSchCmnUpdCfiVal(cell, (2 + 0));


   rgSCHCmnHdlDlInactUes(cell);


   rgSCHCmnTmrProc(cell);

   if (cell->isDlDataAllwd && (cell->stopSiSch == 0))
   {
      rgSCHCmnInitRbAlloc(cell);
      rgSCHCmnDlBcchPcchAlloc(cell);
   }
   else
   {
      if(cell->siCb.inWindow != 0)
      {
         cell->siCb.inWindow--;
      }
   }
   if (cell->isDlDataAllwd && (cell->stopDlSch == 0))
   {
      rgSCHCmnDlCcchRarAlloc(cell);
   }
   return;
}
 Void rgSCHCmnUlSch
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;
   if(cellSch->ul.schdIdx != 0xff)
   {
      rgSchCmnUpdCfiVal(cell, (4 - 2));


      rgSCHCmnHdlUlInactUes(cell);

      rgSCHCmnUlAlloc(cell);


      rgSchCmnUpdCfiDb(cell, (4 - 2));

      if(cell->dynCfiCb.switchOvrWinLen > 0)
      {

         cell->dynCfiCb.switchOvrWinLen--;

         if(!cell->dynCfiCb.switchOvrWinLen)
         {
            if(cell->dynCfiCb.dynCfiRecfgPend)
            {

               cell->dynCfiCb.isDynCfiEnb ^= 1;
               rgSCHDynCfiReCfg(cell, cell->dynCfiCb.isDynCfiEnb);
               cell->dynCfiCb.dynCfiRecfgPend = 0;
            }
            cell->dynCfiCb.switchOvrInProgress = 0;
         }
      }
   }
   return;
}
 Void rgSCHCmnDlDedBoUpd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlLcCb *svc
)






{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;



   if ((ue->ul.ulInactvMask & 0x04))
   {
      RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));


      if (ueDl->rachInfo.rapIdLnk.node == 0L)
      {
         rgSCHCmnDlAdd2PdcchOdrQ(cell, ue);
      }
   }




   if (svc->dlLcSpsCfg.isSpsEnabled)
   {
      rgSCHCmnSpsDlDedBoUpd(cell, ue, svc);

      return;
   }

   cellSch->apisDl->rgSCHDlDedBoUpd(cell, ue, svc);






   return;
}
 Void rgSCHCmnRmvFrmTaLst
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnDlCell *cellCmnDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   ;;

   cmLListDelFrm(&cellCmnDl->taLst, &ue->dlTaLnk);
   ue->dlTaLnk.node = (U32)0L;

   return;
}
 Void rgSCHCmnDlMsg4ProcRmvFrmRetx
(
RgSchCellCb *cell,
RgSchDlHqProcCb *hqP
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;

   if (hqP->tbInfo[0].ccchSchdInfo.retxLnk.node)
   {
      if (hqP->hqE->msg4Proc == hqP)
      {
         cmLListDelFrm(&cellSch->dl.msg4RetxLst,
               &hqP->tbInfo[0].ccchSchdInfo.retxLnk);
         hqP->tbInfo[0].ccchSchdInfo.retxLnk.node = (U32)0L;
      }

      else if(hqP->hqE->ccchSduProc == hqP)
      {
         cmLListDelFrm(&cellSch->dl.ccchSduRetxLst,
               &hqP->tbInfo[0].ccchSchdInfo.retxLnk);
         hqP->tbInfo[0].ccchSchdInfo.retxLnk.node = (U32)0L;
      }

   }
   return;
}
 Void rgSCHCmnDlProcAddToRetx
(
RgSchCellCb *cell,
RgSchDlHqProcCb *hqP
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;

   if (hqP->hqE->msg4Proc == hqP)
   {
      cmLListAdd2Tail(&cellSch->dl.msg4RetxLst,
            &hqP->tbInfo[0].ccchSchdInfo.retxLnk);
      hqP->tbInfo[0].ccchSchdInfo.retxLnk.node = (U32)hqP;
   }

   else if(hqP->hqE->ccchSduProc == hqP)
   {

      cmLListAdd2Tail(&cellSch->dl.ccchSduRetxLst,
            &hqP->tbInfo[0].ccchSchdInfo.retxLnk);
      hqP->tbInfo[0].ccchSchdInfo.retxLnk.node = (U32)hqP;
   }

   else
   {

      if ((((RgSchCmnDlHqProc *)((hqP)->sch))->isSpsSvcSchd))
      {

         rgSCHCmnSpsDlProcAddToRetx(cell, hqP);
         return;
      }

      cellSch->apisDl->rgSCHDlProcAddToRetx(cell, hqP);
   }
   return;
}
static Void rgSCHCmnDlSetUeRi
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 ri,
Bool isPer
)







{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   RgSchCmnUeInfo *ueSchCmn = &(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn);
   ;;


   RgSchUePCqiCb *cqiCb = &((ue)->cellInfo [ue->cellIdToCellIdxMap[(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]]->cqiCb);
   (isPer=isPer);






   if (ue->txModeTransCmplt == 0)
   {
      return;
   }



   ri = ((ri) <= (cell->numTxAntPorts) ? (ri) : (cell->numTxAntPorts));




   if ((cell->numTxAntPorts == 2) && (ue->mimoInfo.txMode == RGR_UE_TM_4))
   {
      if ((ri == 2) && ( ueDl->mimoInfo.ri == 1))
      {
         ueDl->mimoInfo.pmi = (ueDl->mimoInfo.pmi < 2)? 1:2;
      }
   }


   ueDl->mimoInfo.ri = ((ri) <= (rgUeCatTbl[ueSchCmn->ueCat].maxTxLyrs) ? (ri) : (rgUeCatTbl[ueSchCmn->ueCat].maxTxLyrs));

   ue->tenbStats->stats.nonPersistent.sch[(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)].riCnt[ueDl->mimoInfo.ri-1]++;
   cell->tenbStats->sch.riCnt[ueDl->mimoInfo.ri-1]++;



   ue->tenbStats->stats.nonPersistent.sch[0].riCnt[ueDl->mimoInfo.ri-1]++;
   cell->tenbStats->sch.riCnt[ueDl->mimoInfo.ri-1]++;



   if (isPer)
   {

      cqiCb->perRiVal = ueDl->mimoInfo.ri;

      cqiCb->invalidateCqi = 0;
   }
   else
   {

      if (cqiCb->perRiVal != ueDl->mimoInfo.ri)
      {



         cqiCb->invalidateCqi = 1;
      }
      else
      {
         cqiCb->invalidateCqi = 0;
      }
   }


   if (ueDl->mimoInfo.ri > 1)
   {
      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD &= ~(0x01); };
   }
   else if (ue->mimoInfo.txMode == RGR_UE_TM_3)
   {
      { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD |= (0x01); };
   }

   return;
}
static S16 rgSCHCmnDlSetUePmi
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 pmi
)






{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   ;;

   if (ue->txModeTransCmplt == 0)
   {
       return(1);
   }

   if (cell->numTxAntPorts == 2)
   {
      if (pmi > 3)
      {
         return(1);
      }
      if (ueDl->mimoInfo.ri == 2)
      {


         if (pmi == 2 || pmi == 3)
         {
            return(1);
         }
         ueDl->mimoInfo.pmi = pmi+1;
      }
      else
      {
         ueDl->mimoInfo.pmi = pmi;
      }
   }
   else if (cell->numTxAntPorts == 4)
   {
      if (pmi > 15)
      {
         return(1);
      }
      ueDl->mimoInfo.pmi = pmi;
   }

   { RgSchCmnDlUe *_ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl)); _ueDl->mimoInfo.forceTD &= ~(0x02); };
   return(0);
}
static Void rgSCHCmnDlProcCqiMode10
(
 RgSchCellCb *cell,
 RgSchUeCb *ue,
 TfuDlCqiPucch *pucchCqi,
 Bool *isCqiAvail
 )
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   ;;

   if (pucchCqi->u.mode10Info.type == TFU_RPT_CQI)
   {


      if((pucchCqi->u.mode10Info.u.cqi) && (pucchCqi->u.mode10Info.u.cqi
               < 16))
      {
         ueDl->cqiFlag = 1;
         ueDl->mimoInfo.cwInfo[0].cqi = pucchCqi->u.mode10Info.u.cqi;
         ueDl->mimoInfo.cwInfo[1].cqi = ueDl->mimoInfo.cwInfo[0].cqi;



         *isCqiAvail = 1;

      }
      else
      {
         return;
      }
   }
   else if (pucchCqi->u.mode10Info.type == TFU_RPT_RI)
   {
      if ( (pucchCqi->u.mode10Info.u.ri >= 1 && pucchCqi->u.mode10Info.u.ri <= 4) )
      {
         rgSCHCmnDlSetUeRi(cell, ue, pucchCqi->u.mode10Info.u.ri,
                           1);
      }
      else
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb003b,L_ERROR,DBG_CELLID, cell->cellId, pucchCqi->u.mode10Info.u.ri, ue->ueId, 0, 0,                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                15848         , "Invalid RI value(%x) CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;
         return;
      }
   }
}
static Void rgSCHCmnDlProcCqiMode11
(
 RgSchCellCb *cell,
 RgSchUeCb *ue,
 TfuDlCqiPucch *pucchCqi,
 Bool *isCqiAvail,
 Bool *is2ndCwCqiAvail
 )
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   ;;

   if (pucchCqi->u.mode11Info.type == TFU_RPT_CQI)
   {
      ue->mimoInfo.puschFdbkVld = 0;

      if((pucchCqi->u.mode11Info.u.cqi.cqi) &&
            (pucchCqi->u.mode11Info.u.cqi.cqi < 16))
      {
         ueDl->cqiFlag = 1;



         *isCqiAvail = 1;

         ueDl->mimoInfo.cwInfo[0].cqi = pucchCqi->u.mode11Info.u.cqi.cqi;
         if (pucchCqi->u.mode11Info.u.cqi.wideDiffCqi.pres)
         {
            if (ueDl->mimoInfo.cwInfo[0].cqi > rgSchCmnDlCqiDiffOfst[pucchCqi->u.mode11Info.u.cqi.wideDiffCqi.val]) { ueDl->mimoInfo.cwInfo[1].cqi = ueDl->mimoInfo.cwInfo[0].cqi - rgSchCmnDlCqiDiffOfst[pucchCqi->u.mode11Info.u.cqi.wideDiffCqi.val]; } else { ueDl->mimoInfo.cwInfo[1].cqi = 1; }

                                                                                  ;



            *is2ndCwCqiAvail = 1;

         }
      }
      else
      {
         return;
      }
      rgSCHCmnDlSetUePmi(cell, ue,
            pucchCqi->u.mode11Info.u.cqi.pmi);
   }
   else if (pucchCqi->u.mode11Info.type == TFU_RPT_RI)
   {
      if( (pucchCqi->u.mode11Info.u.ri >= 1 && pucchCqi->u.mode11Info.u.ri <= 4))
      {
         rgSCHCmnDlSetUeRi(cell, ue, pucchCqi->u.mode11Info.u.ri,
                           1);
      }
      else
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb003c,L_ERROR,DBG_CELLID, cell->cellId, pucchCqi->u.mode11Info.u.ri, ue->ueId, 0, 0,                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                15954         , "Invalid RI value(%x) CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;
         return;
      }
   }
}
static Void rgSCHCmnDlProcCqiMode20
(
 RgSchCellCb *cell,
 RgSchUeCb *ue,
 TfuDlCqiPucch *pucchCqi,
 Bool *isCqiAvail
 )
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   ;;

   if (pucchCqi->u.mode20Info.type == TFU_RPT_CQI)
   {
      if (pucchCqi->u.mode20Info.u.cqi.isWideband)
      {

         if((pucchCqi->u.mode20Info.u.cqi.u.wideCqi) &&
               (pucchCqi->u.mode20Info.u.cqi.u.wideCqi < 16))
         {
            ueDl->cqiFlag = 1;
            ueDl->mimoInfo.cwInfo[0].cqi = pucchCqi->u.mode20Info.u.cqi.
                                           u.wideCqi;
            ueDl->mimoInfo.cwInfo[1].cqi = ueDl->mimoInfo.cwInfo[0].cqi;



            *isCqiAvail = 1;

         }
         else
         {
            return;
         }
      }
   }
   else if (pucchCqi->u.mode20Info.type == TFU_RPT_RI)
   {
      if((pucchCqi->u.mode20Info.u.ri >= 1 && pucchCqi->u.mode20Info.u.ri <= 4))
      {
         rgSCHCmnDlSetUeRi(cell, ue, pucchCqi->u.mode20Info.u.ri,
                           1);
      }
      else
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb003d,L_ERROR,DBG_CELLID, cell->cellId, pucchCqi->u.mode20Info.u.ri, ue->ueId, 0, 0,                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                16049         , "Invalid RI value(%x) CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;
         return;
      }
   }
}
static Void rgSCHCmnDlProcCqiMode21
(
 RgSchCellCb *cell,
 RgSchUeCb *ue,
 TfuDlCqiPucch *pucchCqi,
 Bool *isCqiAvail,
 Bool *is2ndCwCqiAvail
 )
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   ;;

   if (pucchCqi->u.mode21Info.type == TFU_RPT_CQI)
   {
      ue->mimoInfo.puschFdbkVld = 0;
      if (pucchCqi->u.mode21Info.u.cqi.isWideband)
      {

         if((pucchCqi->u.mode21Info.u.cqi.u.wideCqi.cqi) &&
               (pucchCqi->u.mode21Info.u.cqi.u.wideCqi.cqi < 16))
         {
            ueDl->cqiFlag = 1;
            ueDl->mimoInfo.cwInfo[0].cqi = pucchCqi->u.mode21Info.u.cqi.
                                           u.wideCqi.cqi;
            if (pucchCqi->u.mode21Info.u.cqi.u.wideCqi.diffCqi.pres)
            {
               if (ueDl->mimoInfo.cwInfo[0].cqi > rgSchCmnDlCqiDiffOfst[pucchCqi->u.mode21Info.u.cqi.u.wideCqi.diffCqi.val]) { ueDl->mimoInfo.cwInfo[1].cqi = ueDl->mimoInfo.cwInfo[0].cqi - rgSchCmnDlCqiDiffOfst[pucchCqi->u.mode21Info.u.cqi.u.wideCqi.diffCqi.val]; } else { ueDl->mimoInfo.cwInfo[1].cqi = 1; }

                                                                                        ;



               *is2ndCwCqiAvail = 1;

            }



            *isCqiAvail = 1;

         }
         else
         {
            return;
         }
         rgSCHCmnDlSetUePmi(cell, ue,
               pucchCqi->u.mode21Info.u.cqi.u.wideCqi.pmi);
      }
   }
   else if (pucchCqi->u.mode21Info.type == TFU_RPT_RI)
   {
      if((pucchCqi->u.mode21Info.u.ri >= 1 && pucchCqi->u.mode21Info.u.ri <= 4))
      {
         rgSCHCmnDlSetUeRi(cell, ue, pucchCqi->u.mode21Info.u.ri,
                           1);
      }
      else
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb003e,L_ERROR,DBG_CELLID, cell->cellId, pucchCqi->u.mode21Info.u.ri, ue->ueId, 0, 0,                                                "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                16161         , "Invalid RI value(%x) CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                 ;
         return;
      }
   }
}
static Void rgSCHCmnDlCqiOnPucchInd
(
 RgSchCellCb *cell,
 RgSchUeCb *ue,
 TfuDlCqiPucch *pucchCqi,
 RgrUeCqiRept *ueCqiRept,
 Bool *isCqiAvail,
 Bool *is2ndCwCqiAvail
 )
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   ;;





   ueCqiRept->cqiMode = pucchCqi->mode;


   switch(pucchCqi->mode)
   {
      case TFU_PUCCH_CQI_MODE10:

         rgSCHCmnDlProcCqiMode10(cell, ue, pucchCqi, isCqiAvail);



         ueDl->cqiFlag = 1;
         break;
      case TFU_PUCCH_CQI_MODE11:

         rgSCHCmnDlProcCqiMode11(cell, ue, pucchCqi, isCqiAvail,
                is2ndCwCqiAvail);



         ueDl->cqiFlag = 1;
         break;
      case TFU_PUCCH_CQI_MODE20:

         rgSCHCmnDlProcCqiMode20(cell, ue, pucchCqi, isCqiAvail);



         ueDl->cqiFlag = 1;
         break;
      case TFU_PUCCH_CQI_MODE21:

         rgSCHCmnDlProcCqiMode21(cell, ue, pucchCqi, isCqiAvail,
                is2ndCwCqiAvail);



         ueDl->cqiFlag = 1;
         break;
      default:
         {
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb003f,L_ERROR,DBG_CELLID, cell->cellId, pucchCqi->mode, ue->ueId, 0, 0,                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                      16275            , "Unknown CQI Mode %d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                       ;



            *isCqiAvail = 0;

         }
         break;
   }

  return;
}
static Void rgSCHCmnDlCqiOnPuschInd
(
 RgSchCellCb *cell,
 RgSchUeCb *ue,
 TfuDlCqiPusch *puschCqi,
 RgrUeCqiRept *ueCqiRept,
 Bool *isCqiAvail,
 Bool *is2ndCwCqiAvail
 )
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U32 prevRiVal = 0;
   ;;
   if (puschCqi->ri.pres == 1)
   {
      if ((puschCqi->ri.val >= 1 && puschCqi->ri.val <= 4))
      {


         if (RGR_UE_TM_4 == ue->mimoInfo.txMode )
         {
            prevRiVal = ueDl->mimoInfo.ri;
         }
         rgSCHCmnDlSetUeRi(cell, ue, puschCqi->ri.val, 0);
      }
      else
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0040,L_ERROR,DBG_CELLID, cell->cellId, puschCqi->ri.val, ue->ueId, 0, 0,                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                     16365         , "Invalid RI value(%x) CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                      ;
         return;
      }
   }
   ue->mimoInfo.puschFdbkVld = 0;




   ueCqiRept->cqiMode = puschCqi->mode;



   switch(puschCqi->mode)
   {
      case TFU_PUSCH_CQI_MODE_20:


         if((puschCqi->u.mode20Info.wideBandCqi) &&
               (puschCqi->u.mode20Info.wideBandCqi < 16))
         {
            ueDl->mimoInfo.cwInfo[0].cqi = puschCqi->u.mode20Info.wideBandCqi;
            ueDl->mimoInfo.cwInfo[1].cqi = ueDl->mimoInfo.cwInfo[0].cqi;



           *isCqiAvail = 1;

         }
         else
         {
            return;
         }
         break;
      case TFU_PUSCH_CQI_MODE_30:

         if((puschCqi->u.mode30Info.wideBandCqi) &&
               (puschCqi->u.mode30Info.wideBandCqi < 16))
         {
            ueDl->mimoInfo.cwInfo[0].cqi = puschCqi->u.mode30Info.wideBandCqi;
            ueDl->mimoInfo.cwInfo[1].cqi = ueDl->mimoInfo.cwInfo[0].cqi;



            *isCqiAvail = 1;
         }
         else
         {
            return;
         }
         break;
      case TFU_PUSCH_CQI_MODE_12:

         if((puschCqi->u.mode12Info.cqiIdx[0]) &&
               (puschCqi->u.mode12Info.cqiIdx[0] < 16))
         {
            ueDl->mimoInfo.cwInfo[0].cqi = puschCqi->u.mode12Info.cqiIdx[0];



            *isCqiAvail = 1;

         }
         else
         {
            return;
         }
         if((puschCqi->u.mode12Info.cqiIdx[1]) &&
               (puschCqi->u.mode12Info.cqiIdx[1] < 16))
         {
            ueDl->mimoInfo.cwInfo[1].cqi = puschCqi->u.mode12Info.cqiIdx[1];





            *is2ndCwCqiAvail = 1;

         }
         else
         {
            return;
         }
         ue->mimoInfo.puschFdbkVld = 1;
         ue->mimoInfo.puschPmiInfo.mode = TFU_PUSCH_CQI_MODE_12;
         ue->mimoInfo.puschPmiInfo.u.mode12Info = puschCqi->u.mode12Info;



         break;
      case TFU_PUSCH_CQI_MODE_22:

         if((puschCqi->u.mode22Info.wideBandCqi[0]) &&
               (puschCqi->u.mode22Info.wideBandCqi[0] < 16))
         {
            ueDl->mimoInfo.cwInfo[0].cqi = puschCqi->u.mode22Info.wideBandCqi[0];



            *isCqiAvail = 1;

         }
         else
         {
            return;
         }
         if((puschCqi->u.mode22Info.wideBandCqi[1]) &&
               (puschCqi->u.mode22Info.wideBandCqi[1] < 16))
         {
            ueDl->mimoInfo.cwInfo[1].cqi = puschCqi->u.mode22Info.wideBandCqi[1];





            *is2ndCwCqiAvail = 1;

         }
         else
         {
            return;
         }
         rgSCHCmnDlSetUePmi(cell, ue, puschCqi->u.mode22Info.wideBandPmi);
         ue->mimoInfo.puschFdbkVld = 1;
         ue->mimoInfo.puschPmiInfo.mode = TFU_PUSCH_CQI_MODE_22;
         ue->mimoInfo.puschPmiInfo.u.mode22Info = puschCqi->u.mode22Info;
         break;
      case TFU_PUSCH_CQI_MODE_31:

         if((puschCqi->u.mode31Info.wideBandCqi[0]) &&
               (puschCqi->u.mode31Info.wideBandCqi[0] < 16))
         {
            ueDl->mimoInfo.cwInfo[0].cqi = puschCqi->u.mode31Info.wideBandCqi[0];



            *isCqiAvail = 1;

         }
         if (ueDl->mimoInfo.ri > 1)
         {
           if((puschCqi->u.mode31Info.wideBandCqi[1]) &&
               (puschCqi->u.mode31Info.wideBandCqi[1] < 16))
           {
             ueDl->mimoInfo.cwInfo[1].cqi = puschCqi->u.mode31Info.wideBandCqi[1];





             *is2ndCwCqiAvail = 1;

           }
         }
         if (rgSCHCmnDlSetUePmi(cell, ue, puschCqi->u.mode31Info.pmi) != 0)
         {

            if ((puschCqi->ri.pres == 1) &&
                (RGR_UE_TM_4 == ue->mimoInfo.txMode))
            {
               ueDl->mimoInfo.ri = prevRiVal;
            }
         }
         ue->mimoInfo.puschPmiInfo.mode = TFU_PUSCH_CQI_MODE_31;
         ue->mimoInfo.puschPmiInfo.u.mode31Info = puschCqi->u.mode31Info;
         break;
      default:
         {
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0041,L_ERROR,DBG_CELLID, cell->cellId, puschCqi->mode, ue->ueId, 0, 0,                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                      16542            , "Unknown CQI Mode %d CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                       ;

            if ((puschCqi->ri.pres == 1) &&
                (RGR_UE_TM_4 == ue->mimoInfo.txMode))
            {
               ueDl->mimoInfo.ri = prevRiVal;
            }



           *isCqiAvail = 0;


            *is2ndCwCqiAvail = 0;

         }
         break;
   }

   return;
}
 Void rgSCHCmnDlCqiInd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
Bool isPucchInfo,
Void *dlCqi,
CmLteTimingInfo timingInfo
)
{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));



   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   RgrUeCqiRept ueCqiRept = {{0}};
   Bool isCqiAvail = 0;


   Bool is2ndCwCqiAvail = 0;


   ;;


   if (isPucchInfo)
   {
      rgSCHCmnDlCqiOnPucchInd(cell, ue, (TfuDlCqiPucch *)dlCqi, &ueCqiRept, &isCqiAvail, &is2ndCwCqiAvail);
   }
   else
   {
      rgSCHCmnDlCqiOnPuschInd(cell, ue, (TfuDlCqiPusch *)dlCqi, &ueCqiRept, &isCqiAvail, &is2ndCwCqiAvail);
   }
   if (((ue)->cqiReptCfgInfo.numColltdCqiRept != 0) && (isCqiAvail || is2ndCwCqiAvail))
   {
      ueCqiRept.cqi[0] = ueDl->mimoInfo.cwInfo[0].cqi;




      ueCqiRept.cqi[1] = 0;
      if(is2ndCwCqiAvail)
      {
         ueCqiRept.cqi[1] = ueDl->mimoInfo.cwInfo[1].cqi;
      }
      rgSCHCmnUeDlPwrCtColltCqiRept(cell, ue, &ueCqiRept);

   }


   rgSCHCmnDlSetUeAllocLmtLa(cell, ue);
   rgSCHCheckAndSetTxScheme(cell, ue);




   if (cellSch->dl.isDlFreqSel)
   {
      cellSch->apisDlfs->rgSCHDlfsDlCqiInd(cell, ue, isPucchInfo, dlCqi, timingInfo);
   }


   rgSCHCmnSpsDlCqiIndHndlr(cell, ue, timingInfo);


   cellSch->apisDl->rgSCHDlCqiInd(cell, ue, isPucchInfo, dlCqi);
   ueDl->avgCqi += ueDl->mimoInfo.cwInfo[0].cqi;
   ueDl->numCqiOccns++;
   if (ueDl->mimoInfo.ri == 1)
   {
      ueDl->numRi1++;
   }
   else
   {
      ueDl->numRi2++;
   }



   ue->tenbStats->stats.nonPersistent.sch[(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlSumCw0Cqi += ueDl->mimoInfo.cwInfo[0].cqi;
   ue->tenbStats->stats.nonPersistent.sch[(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlSumCw1Cqi += ueDl->mimoInfo.cwInfo[1].cqi;
   ue->tenbStats->stats.nonPersistent.sch[(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlNumCw0Cqi ++;
   ue->tenbStats->stats.nonPersistent.sch[(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)].dlNumCw1Cqi ++;
   cell->tenbStats->sch.dlSumCw0Cqi += ueDl->mimoInfo.cwInfo[0].cqi;
   cell->tenbStats->sch.dlSumCw1Cqi += ueDl->mimoInfo.cwInfo[1].cqi;
   cell->tenbStats->sch.dlNumCw0Cqi ++;
   cell->tenbStats->sch.dlNumCw1Cqi ++;

   return;
}
static U8 rgSCHCmnCalcWcqiFrmSnr
(
 RgSchCellCb *cell,
 TfuSrsRpt *srsRpt
 )





{
   U8 wideCqi=1;
   ;;



       if (srsRpt->snr[0] <=50)
       {
           wideCqi=3;
       }
       else if (srsRpt->snr[0]>=51 && srsRpt->snr[0] <=100)
       {
           wideCqi=6;
       }
       else if (srsRpt->snr[0]>=101 && srsRpt->snr[0] <=150)
       {
           wideCqi=9;
       }
       else if (srsRpt->snr[0]>=151 && srsRpt->snr[0] <=200)
       {
           wideCqi=12;
       }
       else if (srsRpt->snr[0]>=201 && srsRpt->snr[0] <=250)
       {
           wideCqi=14;
       }
       else
       {
           wideCqi=15;
       }
   return(wideCqi);
}
 Void rgSCHCmnSrsInd
(
 RgSchCellCb *cell,
 RgSchUeCb *ue,
 TfuSrsRpt *srsRpt,
 CmLteTimingInfo timingInfo
 )







{
    U8 wideCqi;
    U32 recReqTime;
    ;;

    recReqTime = (timingInfo.sfn * 10) + timingInfo.subframe;
    ue->srsCb.selectedAnt = (recReqTime/ue->srsCb.peri)%2;
    if(srsRpt->wideCqiPres)
    {
        wideCqi = srsRpt->wideCqi;
    }
    else
    {
        wideCqi = rgSCHCmnCalcWcqiFrmSnr(cell, srsRpt);
    }
    rgSCHCmnFindUlCqiUlTxAnt(cell, ue, wideCqi);
    return;
}
 Void rgSCHCmnDlTARpt
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   CmLListCp poInactvLst;

   ;;




   if ((ue->dl.taCb.cfgTaTmr) && (rgSCHCmnUeIdleExdThrsld(cell, ue) == 0))
   {
      U32 prevDlMsk = ue->dl.dlInactvMask;
      U32 prevUlMsk = ue->ul.ulInactvMask;
      ue->dl.dlInactvMask |= 0x04;
      ue->ul.ulInactvMask |= 0x04;

      cmLListInit(&poInactvLst);
      cmLListAdd2Tail(&poInactvLst, &ueDl->rachInfo.inActUeLnk);
      ueDl->rachInfo.inActUeLnk.node = (U32)ue;

      if (prevDlMsk == 0)
      {
         cellSch->apisDl->rgSCHDlInactvtUes(cell, &poInactvLst);
      }
      if (prevUlMsk == 0)
      {
         cellSch->apisUl->rgSCHUlInactvtUes(cell, &poInactvLst);
      }
   }
   else
   {

      if (!ue->dlTaLnk.node)
      {
         cmLListAdd2Tail(&cellDl->taLst, &ue->dlTaLnk);
         ue->dlTaLnk.node = (U32)ue;
      }
      else
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0042,L_ERROR,DBG_CELLID, cell->cellId, ue->ueId, 0, 0, 0,                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                       16891         , "<TA>TA duplicate entry attempt failed: UEID:%u", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                        ;
      }
   }
   return;
}
static Void rgSCHCmnFindUlCqiUlTxAnt
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 wideCqi
)






{


   ue->validTxAnt = 1;

   return;
}
 Void rgSCHCmnUlCqiInd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
TfuUlCqiRpt *ulCqiInfo
)






{
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   U8 iTbsNew;
   S32 previTbs;


     CmLteUeCategory ueCtg = (CmLteUeCategory)(((&(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn))->ueCat + 1));


   ;;


   ueUl->crntUlCqi[0] = ulCqiInfo->wideCqi;

   ueUl->validUlCqi = ueUl->crntUlCqi[0];
   ue->validTxAnt = 0;

   iTbsNew = rgSchCmnUlCqiToTbsTbl[cell->isCpUlExtend][ueUl->validUlCqi];
   previTbs = (ueUl->ulLaCb.cqiBasediTbs + ueUl->ulLaCb.deltaiTbs)/100;

   if (((iTbsNew) > (previTbs) ? (iTbsNew) - (previTbs) : (previTbs) - (iTbsNew)) > 5)
   {


      ueUl->ulLaCb.lastiTbsIgnored = 1;
   }
   else
   {
      if (ueUl->ulLaCb.lastiTbsIgnored != 1)
      {
         ueUl->ulLaCb.cqiBasediTbs = ((20 * iTbsNew * 100) +
                                       (80 * ueUl->ulLaCb.cqiBasediTbs))/100;
      }
      else
      {


         ueUl->ulLaCb.cqiBasediTbs = ((20 * iTbsNew * 100) +
                                        (80 * previTbs * 100))/100;
         ueUl->ulLaCb.deltaiTbs = 0;
         ueUl->ulLaCb.lastiTbsIgnored = 0;
      }
   }


   rgSCHPwrUlCqiInd(cell, ue);

   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
      rgSCHCmnSpsUlCqiInd(cell, ue);
   }


   cellSch->apisUl->rgSCHUlCqiInd(cell, ue, ulCqiInfo);


   ueUl->numCqiOccns++;
   ueUl->avgCqi += rgSCHCmnUlGetCqi(cell, ue, ueCtg);



   {
      ue->tenbStats->stats.nonPersistent.sch[(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)].ulSumCqi += rgSCHCmnUlGetCqi(cell, ue, ueCtg);
      ue->tenbStats->stats.nonPersistent.sch[(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)].ulNumCqi ++;
      cell->tenbStats->sch.ulSumCqi += rgSCHCmnUlGetCqi(cell, ue, ueCtg);
      cell->tenbStats->sch.ulNumCqi ++;
   }


   return;
}
 Void rgSCHCmnUlHqProcForUe
(
RgSchCellCb *cell,
CmLteTimingInfo frm,
RgSchUeCb *ue,
RgSchUlHqProcCb **procRef
)







{
   U8 procId = rgSCHCmnGetUlHqProcIdx(&frm, cell);
   ;;
   *procRef = rgSCHUhmGetUlHqProc(cell, ue, procId);
   return;
}
 S16 rgSCHCmnBsrTmrExpry
(
RgSchUeCb *ueCb
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((ueCb->cell)->sc.sch));

   ;

   ueCb->isSrGrant = 1;

   cellSch->apisUl->rgSCHSrRcvd(ueCb->cell, ueCb);

   return(0);
}
 S16 rgSCHCmnUpdBsrShort
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchLcgCb *ulLcg,
U8 bsr,
RgSchErrInfo *err
)
{
   U8 lcgCnt;



   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnLcg *cmnLcg = 0L;




   ;;

   if (!((ulLcg)->lcgId != 255))
   {
      err->errCause = ((((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1) + 1);
      return(1);
   }
   for (lcgCnt=0; lcgCnt<4; lcgCnt++)
   {
      if (((&ue->ul.lcgArr[lcgCnt])->lcgId != 255))
      {
         ((RgSchCmnLcg *)(ue->ul.lcgArr[lcgCnt].sch))->bs = 0;
         ((RgSchCmnLcg *)(ue->ul.lcgArr[lcgCnt].sch))->reportedBs = 0;
      }
   }
   ue->ul.nonGbrLcgBs = 0;
   ue->ul.nonLcg0Bs = 0;

   cmnLcg = ((RgSchCmnLcg *)(ulLcg->sch));

   if (1 == ue->ul.useExtBSRSizes)
   {
      cmnLcg->reportedBs = rgSchCmnExtBsrTbl[bsr];
   }
   else
   {
      cmnLcg->reportedBs = rgSchCmnBsrTbl[bsr];
   }
   if (((cmnLcg->cfgdGbr) != 0))
   {

      cmnLcg->bs = ((cmnLcg->reportedBs) <= (cmnLcg->effGbr + cmnLcg->effDeltaMbr) ? (cmnLcg->reportedBs) : (cmnLcg->effGbr + cmnLcg->effDeltaMbr));
   }
   else if (0 == ulLcg->lcgId)
   {

      cmnLcg->bs = cmnLcg->reportedBs;
   }
   else
   {

      ue->ul.nonGbrLcgBs = ((cmnLcg->reportedBs) <= (ue->ul.effAmbr) ? (cmnLcg->reportedBs) : (ue->ul.effAmbr));
      cmnLcg->bs = ue->ul.nonGbrLcgBs;
   }
   ue->ul.totalBsr = cmnLcg->bs;


   if ((ue->bsrTmr.tmrEvnt != -1) && (bsr == 0))
   {
      rgSCHTmrStopTmr(cell, ue->bsrTmr.tmrEvnt, ue);
   }


   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
      rgSCHCmnSpsBsrRpt(cell, ue, ulLcg);
   }

   rgSCHCmnUpdUlCompEffBsr(ue);

   cellSch->apisUl->rgSCHUpdBsrShort(cell, ue, ulLcg, bsr);
   return(0);
}
 S16 rgSCHCmnUpdBsrTrunc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchLcgCb *ulLcg,
U8 bsr,
RgSchErrInfo *err
)
{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnLcg *cmnLcg = 0L;
   S32 cnt;




   ;;

   if (!((ulLcg)->lcgId != 255))
   {
      err->errCause = ((((((((((((((((0 + 1) + 4) + 1) + 7) + 1) + 2) + 1) ) + 1) + 2) + 1) + 1) + 1) + 16) + 1) + 1);
      return(1);
   }


   if (ulLcg->lcgId)
   {
      for (cnt = ulLcg->lcgId-1; cnt >= 0; cnt--)
      {
         ((RgSchCmnLcg *)(ue->ul.lcgArr[cnt].sch))->bs = 0;
         ((RgSchCmnLcg *)(ue->ul.lcgArr[cnt].sch))->reportedBs = 0;
      }
   }
   ue->ul.nonGbrLcgBs = 0;
   ue->ul.nonLcg0Bs = 0;
   cmnLcg = ((RgSchCmnLcg *)(ulLcg->sch));
   if (1 == ue->ul.useExtBSRSizes)
   {
      cmnLcg->reportedBs = rgSchCmnExtBsrTbl[bsr];
   }
   else
   {
      cmnLcg->reportedBs = rgSchCmnBsrTbl[bsr];
   }
   if (((cmnLcg->cfgdGbr) != 0))
   {
      cmnLcg->bs = ((cmnLcg->reportedBs) <= (cmnLcg->effGbr + cmnLcg->effDeltaMbr) ? (cmnLcg->reportedBs) : (cmnLcg->effGbr + cmnLcg->effDeltaMbr));
   }
   else if(ulLcg->lcgId == 0)
   {

      cmnLcg->bs = cmnLcg->reportedBs;
   }
   else
   {
      ue->ul.nonGbrLcgBs = ((cmnLcg->reportedBs) <= (ue->ul.effAmbr) ? (cmnLcg->reportedBs) : (ue->ul.effAmbr));
      cmnLcg->bs = ue->ul.nonGbrLcgBs;
   }
   ue->ul.totalBsr = cmnLcg->bs;

   for (cnt = ulLcg->lcgId+1; cnt < 4; cnt++)
   {



      ue->ul.totalBsr += ((RgSchCmnLcg *)(ue->ul.lcgArr[cnt].sch))->bs;
   }

   rgSCHCmnUpdUlCompEffBsr(ue);

   cellSch->apisUl->rgSCHUpdBsrTrunc(cell, ue, ulLcg, bsr);
   return(0);
}
 S16 rgSCHCmnUpdBsrLong
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 *bsArr,
RgSchErrInfo *err
)







{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U32 tmpBsArr[4] = {0, 0, 0, 0};
   U32 nonGbrBs = 0;




   U32 lcgId;

   ;;
   ue->ul.nonGbrLcgBs = 0;
   ue->ul.nonLcg0Bs = 0;

   if (((&ue->ul.lcgArr[0])->lcgId != 255))
   {
      if (1 == ue->ul.useExtBSRSizes)
      {
         ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs = rgSchCmnExtBsrTbl[bsArr[0]];
         ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->reportedBs = rgSchCmnExtBsrTbl[bsArr[0]];
         tmpBsArr[0] = rgSchCmnExtBsrTbl[bsArr[0]];
      }
      else
      {
         ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs = rgSchCmnBsrTbl[bsArr[0]];
         ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->reportedBs = rgSchCmnBsrTbl[bsArr[0]];
         tmpBsArr[0] = rgSchCmnBsrTbl[bsArr[0]];
      }
   }
   for (lcgId = 1; lcgId < 4; lcgId++)
   {
      if (((&ue->ul.lcgArr[lcgId])->lcgId != 255))
      {
         RgSchCmnLcg *cmnLcg = ((RgSchCmnLcg *)(ue->ul.lcgArr[lcgId].sch));

         if (1 == ue->ul.useExtBSRSizes)
         {
            cmnLcg->reportedBs = rgSchCmnExtBsrTbl[bsArr[lcgId]];
         }
         else
         {
            cmnLcg->reportedBs = rgSchCmnBsrTbl[bsArr[lcgId]];
         }
         if (((cmnLcg->cfgdGbr) != 0))
         {
            cmnLcg->bs = ((cmnLcg->reportedBs) <= (cmnLcg->effGbr + cmnLcg->effDeltaMbr) ? (cmnLcg->reportedBs) : (cmnLcg->effGbr + cmnLcg->effDeltaMbr));
            tmpBsArr[lcgId] = cmnLcg->bs;
         }
         else
         {
            nonGbrBs += cmnLcg->reportedBs;
            tmpBsArr[lcgId] = cmnLcg->reportedBs;
            cmnLcg->bs = ((cmnLcg->reportedBs) <= (ue->ul.effAmbr) ? (cmnLcg->reportedBs) : (ue->ul.effAmbr));
         }
      }
   }
   ue->ul.nonGbrLcgBs = ((nonGbrBs) <= (ue->ul.effAmbr) ? (nonGbrBs) : (ue->ul.effAmbr));

   ue->ul.totalBsr = tmpBsArr[0] + tmpBsArr[1] + tmpBsArr[2] + tmpBsArr[3];

   if ((ue->bsrTmr.tmrEvnt != -1) && (ue->ul.totalBsr == 0))
   {
      rgSCHTmrStopTmr(cell, ue->bsrTmr.tmrEvnt, ue);
   }



   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
     if(ue->ul.totalBsr - tmpBsArr[1] == 0)
     {
        rgSCHCmnSpsBsrRpt(cell, ue, &ue->ul.lcgArr[1]);
     }
   }

   rgSCHCmnUpdUlCompEffBsr(ue);

   cellSch->apisUl->rgSCHUpdBsrLong(cell, ue, bsArr);
   return(0);
}
 S16 rgSCHCmnUpdExtPhr
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgInfExtPhrCEInfo *extPhr,
RgSchErrInfo *err
)







{
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   RgSchCmnAllocRecord *allRcd;
   CmLList *node = ueUl->ulAllocLst.last;


   RgSchCmnUlUeSpsInfo *ulSpsUe = &(ue->ul.ulSpsInfo);

   ;;

   (err=err);

   while (node)
   {
      allRcd = (RgSchCmnAllocRecord *)node->node;
      node = node->prev;
      if ((((ue->macCeRptTime).sfn == (allRcd->allocTime).sfn) && ((ue->macCeRptTime).subframe == (allRcd->allocTime).subframe)))
      {
         rgSCHPwrUpdExtPhr(cell, ue, extPhr, allRcd);
         break;
      }
   }

   if(ulSpsUe->isUlSpsActv)
   {
      rgSCHCmnSpsPhrInd(cell,ue);
   }


   return(0);
}
 S16 rgSCHCmnUpdPhr
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 phr,
RgSchErrInfo *err
)







{
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   RgSchCmnAllocRecord *allRcd;
   CmLList *node = ueUl->ulAllocLst.last;


   RgSchCmnUlUeSpsInfo *ulSpsUe = &(ue->ul.ulSpsInfo);

   ;;

   (err=err);

   while (node)
   {
      allRcd = (RgSchCmnAllocRecord *)node->node;
      node = node->prev;
      if ((((ue->macCeRptTime).sfn == (allRcd->allocTime).sfn) && ((ue->macCeRptTime).subframe == (allRcd->allocTime).subframe)))
      {
         rgSCHPwrUpdPhr(cell, ue, phr, allRcd, (-128));
         break;
      }
   }

   if(ulSpsUe->isUlSpsActv)
   {
      rgSCHCmnSpsPhrInd(cell,ue);
   }


   return(0);
}
 S16 rgSCHCmnContResUlGrant
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchErrInfo *err
)






{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;

   cellSch->apisUl->rgSCHContResUlGrant(cell, ue);

   return(0);
}
 S16 rgSCHCmnSrRcvd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
CmLteTimingInfo frm,
RgSchErrInfo *err
)







{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   CmLList *node = ueUl->ulAllocLst.last;

   ;;

   do { if ((frm.subframe += 1) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);
   while (node)
   {
      RgSchCmnAllocRecord *allRcd = (RgSchCmnAllocRecord *)node->node;
      if ((((frm).sfn == (allRcd->allocTime).sfn) && ((frm).subframe == (allRcd->allocTime).subframe)))
      {
         break;
      }
      node = node->prev;
   }
   if (node)
   {





     if(ue->dl.reqForCqi == RG_SCH_APCQI_NO)
     {
        return(0);
     }
   }

   ue->isSrGrant = 1;
   cellSch->apisUl->rgSCHSrRcvd(cell, ue);

   return(0);
}
 RgSchUlAlloc *rgSCHCmnFirstRcptnReq
(
RgSchCellCb *cell
)




{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);



   RgSchUlAlloc* alloc = 0L;


   ;;

   if (cellUl->rcpReqIdx != 0xff)
   {
    RgSchUlSf* sf = &cellUl->ulSfArr[cellUl->rcpReqIdx];
    alloc = rgSCHUtlUlAllocFirst(sf);

    if (alloc && alloc->hqProc == 0L)
    {
     alloc = rgSCHUtlUlAllocNxt(sf, alloc);
    }
   }

   return(alloc);
}
 RgSchUlAlloc *rgSCHCmnNextRcptnReq
(
RgSchCellCb *cell,
RgSchUlAlloc *alloc
)





{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);



   ;;

   if (cellUl->rcpReqIdx != 0xff)
   {
    RgSchUlSf *sf = &cellUl->ulSfArr[cellUl->rcpReqIdx];

    alloc = rgSCHUtlUlAllocNxt(sf, alloc);
    if (alloc && alloc->hqProc == 0L)
    {
     alloc = rgSCHUtlUlAllocNxt(sf, alloc);
    }
   }
   else
   {
    alloc = 0L;
   }

   return(alloc);
}
 Void rgSCHCmnDrxStrtInActvTmrInUl
(
RgSchCellCb *cell
)




{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchUlSf *sf = &(cellUl->ulSfArr[cellUl->schdIdx]);
   RgSchUlAlloc *alloc = rgSCHUtlUlAllocFirst(sf);
   CmLListCp ulUeLst;
   RgSchUeCb *ueCb;


   ;;

   cmLListInit(&ulUeLst);

   while(alloc)
   {
      ueCb = alloc->ue;

      if (ueCb)
      {
         if (!(alloc->grnt.isRtx) && ueCb->isDrxEnabled && !(ueCb->isSrGrant)



             && (alloc->hqProc->isSpsOccnHqP == 0)

             )
         {
            cmLListAdd2Tail(&ulUeLst,&(ueCb->ulDrxInactvTmrLnk));
            ueCb->ulDrxInactvTmrLnk.node = (U32)ueCb;
         }
      }

      alloc = rgSCHUtlUlAllocNxt(sf, alloc);
   }

   (Void)rgSCHDrxStrtInActvTmr(cell,&ulUeLst,0);

   return;
}
 RgSchUlAlloc *rgSCHCmnFirstHqFdbkAlloc
(
RgSchCellCb *cell,
U8 idx
)





{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);



   RgSchUlAlloc *alloc = 0L;


   ;;

   if (cellUl->hqFdbkIdx[idx] != 0xff)
   {
   RgSchUlSf *sf = &cellUl->ulSfArr[cellUl->hqFdbkIdx[idx]];
   alloc = rgSCHUtlUlAllocFirst(sf);

   while (alloc && (alloc->hqProc == 0L))
   {
    alloc = rgSCHUtlUlAllocNxt(sf, alloc);
   }
   }

   return(alloc);
}
 RgSchUlAlloc *rgSCHCmnNextHqFdbkAlloc
(
RgSchCellCb *cell,
RgSchUlAlloc *alloc,
U8 idx
)






{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   ;;

   if (cellUl->hqFdbkIdx[idx] != 0xff)
   {
      RgSchUlSf *sf = &cellUl->ulSfArr[cellUl->hqFdbkIdx[idx]];

      alloc = rgSCHUtlUlAllocNxt(sf, alloc);
      while (alloc && (alloc->hqProc == 0L))
      {
         alloc = rgSCHUtlUlAllocNxt(sf, alloc);
      }
   }
   else
   {
   alloc = 0L;
   }
   return(alloc);
}
 U8 rgSCHCmnUlGetITbsFrmIMcs
(
U8 iMcs
)




{
   ;;

   return(rgUlIMcsTbl[iMcs].iTbs);
}
 U8 rgSCHCmnUlGetIMcsFrmITbs
(
U8 iTbs,
CmLteUeCategory ueCtg
)





{
   U8 iMcs;
   ;;

   if (iTbs <= 10)
   {
      iMcs = iTbs;
   }





   else if ( iTbs < 19 )
   {
      iMcs = iTbs + 1;
   }
   else if ((iTbs == 19) && (ueCtg != CM_LTE_UE_CAT_5))
   {
      iMcs = iTbs + 1;
   }
   else
   {
      iMcs = iTbs + 2;
   }

   return(iMcs);
}
 U32 rgSCHCmnUlMinTbBitsForITbs
(
RgSchCmnUlCell *cellUl,
U8 iTbs
)





{
   ;;

   ;

   return(rgTbSzTbl[0][iTbs][cellUl->sbSize-1]);
}
 RgSchUlAlloc *rgSCHCmnUlSbAlloc
(
RgSchUlSf *sf,
U8 numSb,
RgSchUlHole *hole
)






{
   U8 holeSz;
   RgSchUlAlloc *alloc;
   ;;

   if ((holeSz = rgSchCmnMult235Tbl[hole->num].prvMatch) == hole->num)
   {
      numSb = rgSchCmnMult235Tbl[numSb].match;
      if (numSb >= holeSz)
      {
         alloc = rgSCHUtlUlAllocGetCompHole(sf, hole);
      }
      else
      {
         alloc = rgSCHUtlUlAllocGetPartHole(sf, numSb, hole);
      }
   }
   else
   {
      if (numSb < holeSz)
      {
         numSb = rgSchCmnMult235Tbl[numSb].match;
      }
      else
      {
         numSb = rgSchCmnMult235Tbl[numSb].prvMatch;
      }

      if ( numSb >= holeSz )
      {
         numSb = holeSz;
      }
      alloc = rgSCHUtlUlAllocGetPartHole(sf, numSb, hole);
   }
   return(alloc);
}
 Void rgSCHCmnUlUeFillAllocInfo
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchCmnUeUlAlloc *ulAllocInfo;
   RgSchCmnUlUe *ueUl;




   ;;

   ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   ulAllocInfo = &ueUl->alloc;


   rgSCHCmnUlAllocFillTpc(cell, ue, ulAllocInfo->alloc);
   rgSCHCmnUlAllocFillNdmrs(cellUl, ulAllocInfo->alloc);
   rgSCHCmnUlAllocLnkHqProc(ue, ulAllocInfo->alloc, ulAllocInfo->alloc->hqProc,
                     ulAllocInfo->alloc->hqProc->isRetx);

   rgSCHCmnUlFillPdcchWithAlloc(ulAllocInfo->alloc->pdcch,
         ulAllocInfo->alloc, ue);


   if ((ulAllocInfo->alloc->hqProc->isRetx == 1) && (ulAllocInfo->alloc->ue) &&
        (ulAllocInfo->alloc->rnti == ulAllocInfo->alloc->ue->spsRnti))
   {
      ulAllocInfo->alloc->pdcch->dci.u.format0Info.ndi = 1;
   }


   rgSCHCmnUlRecordUeAlloc(cell, ue);


   if (!ulAllocInfo->alloc->hqProc->isRetx)
   {
      rgSCHCmnUlUpdOutStndAlloc(cell, ue, ulAllocInfo->allocdBytes);
   }
   return;
}
static Void rgSCHCmnUpdUlCompEffBsr
(
RgSchUeCb *ue
)




{
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((ue->cell->cellId >= rgSchCb[ue->cell->instIdx].genCfg.startCellId) ? (ue->cell->cellId - rgSchCb[ue->cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   CmLList *node = ueUl->ulAllocLst.last;
   RgSchCmnAllocRecord *allRcd;
   U32 outStndAlloc=0;
   U32 nonLcg0OutStndAllocBs=0;
   U32 nonLcg0Bsr=0;
   U8 lcgId;
   RgSchCmnLcg *cmnLcg = 0L;
   ;;

   while (node)
   {
      allRcd = (RgSchCmnAllocRecord *)node->node;
      if ((((ue->macCeRptTime).sfn == (allRcd->allocTime).sfn) && ((ue->macCeRptTime).subframe == (allRcd->allocTime).subframe)))
      {
         node = node->next;
         break;
      }
      node = node->prev;
   }
   while (node)
   {
      allRcd = (RgSchCmnAllocRecord *)node->node;
      node = node->next;
      outStndAlloc += allRcd->alloc;
   }

   cmnLcg = (RgSchCmnLcg *)(ue->ul.lcgArr[0].sch);

   if (cmnLcg->bs > outStndAlloc)
   {
      cmnLcg->bs -= outStndAlloc;
      ue->ul.minReqBytes = cmnLcg->bs;
      outStndAlloc = 0;
   }
   else
   {
      nonLcg0OutStndAllocBs = outStndAlloc - cmnLcg->bs;
      cmnLcg->bs = 0;
   }

   for(lcgId = 1;lcgId < 4; lcgId++)
   {
      if(((&ue->ul.lcgArr[lcgId])->lcgId != 255))
      {
         cmnLcg = ((RgSchCmnLcg *) (ue->ul.lcgArr[lcgId].sch));
         if (((cmnLcg->cfgdGbr) != 0))
         {
            nonLcg0Bsr += cmnLcg->bs;
         }
      }
   }
   nonLcg0Bsr += ue->ul.nonGbrLcgBs;
   if (nonLcg0OutStndAllocBs > nonLcg0Bsr)
   {
      nonLcg0Bsr = 0;
   }
   else
   {
      nonLcg0Bsr -= nonLcg0OutStndAllocBs;
   }
   ue->ul.nonLcg0Bs = nonLcg0Bsr;



   ue->ul.effBsr = nonLcg0Bsr +
                  ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs;
   return;
}
 Void rgSCHCmnUlRecordUeAlloc
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{



   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   CmLListCp *lst = &ueUl->ulAllocLst;
   CmLList *node = ueUl->ulAllocLst.first;
   RgSchCmnAllocRecord *allRcd = (RgSchCmnAllocRecord *)(node->node);
   RgSchCmnUeUlAlloc *ulAllocInfo = &ueUl->alloc;
   CmLteUeCategory ueCtg = (CmLteUeCategory)(((&(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn))->ueCat + 1));
   ;;

   cmLListDelFrm(lst, &allRcd->lnk);



   allRcd->allocTime = cell->crntTime;

   do { if ((allRcd->allocTime.subframe += ((4 - 2) + 4)) > 9) { allRcd->allocTime.sfn = ((allRcd->allocTime.sfn) + 1) & 0x03ff; allRcd->allocTime.subframe -= 10; }} while(0)
                                                                        ;



   cmLListAdd2Tail(lst, &allRcd->lnk);


   allRcd->alloc = ulAllocInfo->allocdBytes;
   allRcd->numRb = ulAllocInfo->alloc->grnt.numRb;

   allRcd->cqi = rgSCHCmnUlGetCqi(cell, ue, ueCtg);
   allRcd->tpc = ulAllocInfo->alloc->grnt.tpc;

   rgSCHPwrRecordRbAlloc(cell, ue, allRcd->numRb);

   cell->measurements.ulBytesCnt += ulAllocInfo->allocdBytes;

   return;
}
 Void rgSCHCmnUlRecMsg3Alloc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchRaCb *raCb
)






{
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   CmLListCp *lst = &ueUl->ulAllocLst;
   CmLList *node = ueUl->ulAllocLst.first;
   RgSchCmnAllocRecord *allRcd = (RgSchCmnAllocRecord *)(node->node);


   ;;

   cmLListDelFrm(lst, node);
   allRcd->allocTime = raCb->msg3AllocTime;
   cmLListAdd2Tail(lst, node);


   allRcd->alloc = raCb->msg3Grnt.datSz;
   allRcd->numRb = raCb->msg3Grnt.numRb;
   allRcd->cqi = raCb->ccchCqi;
   allRcd->tpc = raCb->msg3Grnt.tpc;

   rgSCHPwrRecordRbAlloc(cell, ue, allRcd->numRb);

   return;
}
 Void rgSCHCmnUlUpdOutStndAlloc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U32 alloc
)






{
   U32 nonLcg0Alloc=0;
   ;;


   if (((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs > alloc)
   {
      ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs -= alloc;
   }
   else
   {
      nonLcg0Alloc = alloc - ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs;
      ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs = 0;
   }

   if (nonLcg0Alloc >= ue->ul.nonLcg0Bs)
   {
      ue->ul.nonLcg0Bs = 0;
   }
   else
   {
      ue->ul.nonLcg0Bs -= nonLcg0Alloc;
   }



   ue->ul.effBsr = ue->ul.nonLcg0Bs +
                  ((RgSchCmnLcg *)(ue->ul.lcgArr[0].sch))->bs;

   if (ue->ul.effBsr == 0)
   {
      if (ue->bsrTmr.tmrEvnt != -1)
      {
         rgSCHTmrStopTmr(cell, ue->bsrTmr.tmrEvnt, ue);
      }

      if (0 == ue->isSrGrant)
      {
         if (ue->ul.bsrTmrCfg.isPrdBsrTmrPres)
         {
            rgSCHTmrStartTmr(cell, ue, 8,
                  ue->ul.bsrTmrCfg.prdBsrTmr);
         }
      }
   }


   ue->ul.minReqBytes = 0;

   return;
}
 U8 rgSCHCmnUlGetITbs
(
RgSchCellCb *cell,
RgSchUeCb *ue,
Bool isEcp
)






{
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));

   CmLteUeCategory ueCtgy = (CmLteUeCategory)(((&(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn))->ueCat + 1));
   U8 cqi;

   S32 iTbs;
   U8 maxiTbs = rgSchCmnUlCqiToTbsTbl[(U8)isEcp][ueUl->maxUlCqi];


   ;;



   if ( (ueCtgy != CM_LTE_UE_CAT_5) &&
        (ueUl->validUlCqi > ueUl->maxUlCqi)
      )
   {
      cqi = ueUl->maxUlCqi;
   }
   else
   {
      cqi = ueUl->validUlCqi;
   }


   iTbs = (ueUl->ulLaCb.cqiBasediTbs + ueUl->ulLaCb.deltaiTbs)/100;

   { if (iTbs < 0) { iTbs = 0; } else if (iTbs > (maxiTbs)) { iTbs = (maxiTbs); }};

   iTbs = ((iTbs) <= (ue->cell->thresholds.maxUlItbs) ? (iTbs) : (ue->cell->thresholds.maxUlItbs));

   return(iTbs);
   return(rgSchCmnUlCqiToTbsTbl[(U8)isEcp][cqi]);
}
static Void rgSCHCmnDlRbInfoAddUeTx
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo,
RgSchUeCb *ue,
RgSchDlHqProcCb *hqP
)







{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((ue->cell)->sc.sch));
   RgSchDlRbAlloc *ueAllocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((ue->cell->cellId >= rgSchCb[ue->cell->instIdx].genCfg.startCellId) ? (ue->cell->cellId - rgSchCb[ue->cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;

   ;;

   if (hqP->reqLnk.node == 0L)
   {
      if (cellSch->dl.isDlFreqSel)
      {
         cellSch->apisDlfs->rgSCHDlfsAddUeToLst(cell,
           &allocInfo->dedAlloc.txHqPLst, hqP);
      }
      else
      {
         if(ueAllocInfo->laaDlRbAlloc.isLaaTB)
         {
            cmLListAdd2Tail(&allocInfo->dedAlloc.txLaaHqPLst, &hqP->reqLnk);
         }
         else
         {
            cmLListAdd2Tail(&allocInfo->dedAlloc.txHqPLst, &hqP->reqLnk);
         }
         hqP->reqLnk.node = (U32)hqP;
      }
   }
   return;
}
static Void rgSCHCmnDlRbInfoAddUeRetx
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo,
RgSchUeCb *ue,
RgSchDlHqProcCb *hqP
)







{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((ue->cell)->sc.sch));

   ;;

   if (cellSch->dl.isDlFreqSel)
   {
      cellSch->apisDlfs->rgSCHDlfsAddUeToLst(cell,
        &allocInfo->dedAlloc.retxHqPLst, hqP);
   }
   else
   {

      cmLListAdd2Tail(&allocInfo->dedAlloc.retxHqPLst, &hqP->reqLnk);
      hqP->reqLnk.node = (U32)hqP;
   }
   return;
}
static Void rgSCHCmnDlRbInfoAddUeRetxTx
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo,
RgSchUeCb *ue,
RgSchDlHqProcCb *hqP
)







{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((ue->cell)->sc.sch));

   ;;

   if (cellSch->dl.isDlFreqSel)
   {
      cellSch->apisDlfs->rgSCHDlfsAddUeToLst(cell,
        &allocInfo->dedAlloc.txRetxHqPLst, hqP);
   }
   else
   {
      cmLListAdd2Tail(&allocInfo->dedAlloc.txRetxHqPLst, &hqP->reqLnk);
      hqP->reqLnk.node = (U32)hqP;
   }
   return;
}
static Void rgSCHCmnDlAdd2NonSchdRetxLst
(
RgSchCmnDlRbAllocInfo *allocInfo,
RgSchUeCb *ue,
RgSchDlHqProcCb *hqP
)






{
   CmLList *schdLnkNode;

   ;;


   if ( (hqP->sch != (RgSchCmnDlHqProc *)0L) &&
         ((((RgSchCmnDlHqProc *)((hqP)->sch))->isSpsSvcSchd)))
   {
      return;
   }


   schdLnkNode = &hqP->schdLstLnk;
   { (schdLnkNode)->node = (U32)hqP; (schdLnkNode)->prev = 0L; (schdLnkNode)->next = 0L;};
   cmLListAdd2Tail(&allocInfo->dedAlloc.nonSchdRetxHqPLst, schdLnkNode);

   return;
}
static Void rgSCHCmnDlRbInfoAddUeErrIndTx
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo,
RgSchUeCb *ue,
RgSchDlHqProcCb *hqP
)







{

   ;;

   cmLListAdd2Tail(&allocInfo->dedAlloc.errIndTxHqPLst, &hqP->reqLnk);
   hqP->reqLnk.node = (U32)hqP;

   return;
}
static Void rgSCHCmnUlAdapRetx
(
RgSchUlAlloc *alloc,
RgSchUlHqProcCb *proc
)





{
   ;;

   rgSCHUhmRetx(proc, alloc);
   if (proc->rvIdx != 0)
   {
      alloc->grnt.iMcsCrnt = rgSchCmnUlRvIdxToIMcsTbl[proc->rvIdx];
   }
   else
   {
      alloc->grnt.iMcsCrnt = alloc->grnt.iMcs;
   }
   return;
}
static Void rgSCHCmnHdlUlInactUes
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   CmLListCp ulInactvLst;
   ;;

   cmLListInit(&ulInactvLst);


   rgSCHMeasGapANRepGetUlInactvUe (cell, &ulInactvLst);

   cellSch->apisUl->rgSCHUlInactvtUes(cell, &ulInactvLst);

   return;
}
static Void rgSCHCmnHdlDlInactUes
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   CmLListCp dlInactvLst;
   ;;

   cmLListInit(&dlInactvLst);


   rgSCHMeasGapANRepGetDlInactvUe (cell, &dlInactvLst);

   cellSch->apisDl->rgSCHDlInactvtUes(cell, &dlInactvLst);
   return;
}
static S16 rgSCHCmnUeIdleExdThrsld
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{

   U32 sfDiff = (cell->crntTime.sfn*10+cell->crntTime.subframe) < (ue->ul.ulTransTime.sfn*10+ue->ul.ulTransTime.subframe)? ((cell->crntTime.sfn+1024)*10+cell->crntTime.subframe) - (ue->ul.ulTransTime.sfn*10+ue->ul.ulTransTime.subframe) : (cell->crntTime.sfn*10+cell->crntTime.subframe) - (ue->ul.ulTransTime.sfn*10+ue->ul.ulTransTime.subframe);

   ;;

   if (sfDiff > (U32)(3 * ue->dl.taCb.cfgTaTmr))
   {
      return(0);
   }
   else
   {
      return(1);
   }
}
static Void rgSCHCmnCfgRachDedPrm
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);
   U32 gap = (6+(2 + 0));
   U32 sfDiff;
   U8 cnt;
   ;;

   if (cell->macPreambleSet.pres == 0)
   {
      return;
   }
   cellSch->rachCfg.numDedPrm = cell->macPreambleSet.size;
   cellSch->rachCfg.dedPrmStart = cell->macPreambleSet.start;

   cmLListInit(&cellSch->rachCfg.hoUeLst);

   cmLListInit(&cellSch->rachCfg.pdcchOdrLst);


   for (cnt = 0; cnt<cellSch->rachCfg.numDedPrm; cnt++)
   {
      cellSch->rachCfg.rapIdMap[cnt].rapId = cellSch->rachCfg.dedPrmStart +
                                             cnt;
      cmLListInit(&cellSch->rachCfg.rapIdMap[cnt].assgndUes);
   }


   cellSch->rachCfg.remDedPrm = cellSch->rachCfg.numDedPrm;

   cellSch->rachCfg.prachMskIndx = 0;
   if (cell->rachCfg.raOccasion.sfnEnum == RGR_SFN_EVEN)
   {
      cellSch->rachCfg.applFrm.sfn = (cell->crntTime.sfn +
            (cell->crntTime.sfn % 2)) % 1024;
   }
   else
   {
      cellSch->rachCfg.applFrm.sfn = cell->crntTime.sfn;
   }


   if (cellSch->rachCfg.applFrm.sfn == cell->crntTime.sfn)
   {
      while (cellSch->rachCfg.prachMskIndx < cell->rachCfg.raOccasion.size)
      {
         if (cell->crntTime.subframe <
               cell->rachCfg.raOccasion.subFrameNum[cellSch->rachCfg.prachMskIndx])
         {
            break;
         }
         cellSch->rachCfg.prachMskIndx++;
      }
      if (cellSch->rachCfg.prachMskIndx == cell->rachCfg.raOccasion.size)
      {
         if (cell->rachCfg.raOccasion.sfnEnum == RGR_SFN_ANY)
         {
            cellSch->rachCfg.applFrm.sfn = (cellSch->rachCfg.applFrm.sfn+1) %
                                           1024;
         }
         else
         {
            cellSch->rachCfg.applFrm.sfn = (cellSch->rachCfg.applFrm.sfn+2) %
                                           1024;
         }
         cellSch->rachCfg.prachMskIndx = 0;
      }
      cellSch->rachCfg.applFrm.subframe =
                                          cell->rachCfg.raOccasion.subFrameNum[cellSch->rachCfg.prachMskIndx];
   }
   else
   {
      cellSch->rachCfg.applFrm.subframe =
                                          cell->rachCfg.raOccasion.subFrameNum[cellSch->rachCfg.prachMskIndx];
   }


   sfDiff = (cellSch->rachCfg.applFrm.sfn*10+cellSch->rachCfg.applFrm.subframe) < (cell->crntTime.sfn*10+cell->crntTime.subframe)? ((cellSch->rachCfg.applFrm.sfn+1024)*10+cellSch->rachCfg.applFrm.subframe) - (cell->crntTime.sfn*10+cell->crntTime.subframe) : (cellSch->rachCfg.applFrm.sfn*10+cellSch->rachCfg.applFrm.subframe) - (cell->crntTime.sfn*10+cell->crntTime.subframe);
   while (sfDiff <= gap)
   {
      rgSCHCmnUpdNxtPrchMskIdx(cell);
      sfDiff = (cellSch->rachCfg.applFrm.sfn*10+cellSch->rachCfg.applFrm.subframe) < (cell->crntTime.sfn*10+cell->crntTime.subframe)? ((cellSch->rachCfg.applFrm.sfn+1024)*10+cellSch->rachCfg.applFrm.subframe) - (cell->crntTime.sfn*10+cell->crntTime.subframe) : (cellSch->rachCfg.applFrm.sfn*10+cellSch->rachCfg.applFrm.subframe) - (cell->crntTime.sfn*10+cell->crntTime.subframe);
   }

   return;
}
static Void rgSCHCmnUpdNxtPrchMskIdx
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);
   ;;


   if (cellSch->rachCfg.prachMskIndx == cell->rachCfg.raOccasion.size - 1)
   {

      cellSch->rachCfg.prachMskIndx = 0;
      if (cell->rachCfg.raOccasion.sfnEnum == RGR_SFN_ANY)
      {
         cellSch->rachCfg.applFrm.sfn = (cellSch->rachCfg.applFrm.sfn+1) %
                                        1024;
      }
      else
      {
         cellSch->rachCfg.applFrm.sfn = (cellSch->rachCfg.applFrm.sfn+2) %
                                        1024;
      }
      cellSch->rachCfg.applFrm.subframe = cell->rachCfg.raOccasion.
                                          subFrameNum[0];
   }
   else
   {
      cellSch->rachCfg.prachMskIndx += 1;
      if ( cellSch->rachCfg.prachMskIndx < 10 )
      {
         cellSch->rachCfg.applFrm.subframe =
                                          cell->rachCfg.raOccasion.subFrameNum[cellSch->rachCfg.prachMskIndx];
      }
   }
   return;
}
static Void rgSCHCmnUpdRachParam
(
RgSchCellCb *cell
)




{

   RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);
   U32 gap = (6+(2 + 0));
   U32 sfDiff;
   ;;

   if (cell->macPreambleSet.pres == 0)
   {
      return;
   }
   sfDiff = (cellSch->rachCfg.applFrm.sfn*10+cellSch->rachCfg.applFrm.subframe) < (cell->crntTime.sfn*10+cell->crntTime.subframe)? ((cellSch->rachCfg.applFrm.sfn+1024)*10+cellSch->rachCfg.applFrm.subframe) - (cell->crntTime.sfn*10+cell->crntTime.subframe) : (cellSch->rachCfg.applFrm.sfn*10+cellSch->rachCfg.applFrm.subframe) - (cell->crntTime.sfn*10+cell->crntTime.subframe)
                        ;
   if (sfDiff > gap)
   {

      return;
   }
   rgSCHCmnUpdNxtPrchMskIdx(cell);

   cellSch->rachCfg.remDedPrm = cellSch->rachCfg.numDedPrm;

   return;
}
static S16 rgSCHCmnAllocPOParam
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
RgSchUeCb *ue,
RgSchPdcch **pdcch,
U8 *rapId,
U8 *prachMskIdx
)
{

   RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U32 y;

   ;;

   if (cell->macPreambleSet.pres == 1)
   {
      if (cellSch->rachCfg.remDedPrm == 0)
      {
         return(1);
      }
      y = rgSCHUtlGetY(ue, dlSf->sfNum);

      if ((*pdcch = rgSCHCmnPdcchAlloc(cell, ue, dlSf, y, ueDl->mimoInfo.cwInfo[0].cqi, TFU_DCI_FORMAT_1A, 0)) == 0L)
      {
         return(1);
      }



      *prachMskIdx = cellSch->rachCfg.prachMskIndx + 1;

      *rapId = cellSch->rachCfg.dedPrmStart +
         cellSch->rachCfg.numDedPrm - cellSch->rachCfg.remDedPrm;
      cellSch->rachCfg.remDedPrm--;

      ueDl->rachInfo.asgnOppr = cellSch->rachCfg.applFrm;
      ;
      cmLListAdd2Tail(&cellSch->rachCfg.rapIdMap[*rapId - cellSch->rachCfg.dedPrmStart].assgndUes,
             &ueDl->rachInfo.rapIdLnk);
      ueDl->rachInfo.rapIdLnk.node = (U32)ue;
      ueDl->rachInfo.poRapId = *rapId;
   }
   else
   {
      y = rgSCHUtlGetY(ue, dlSf->sfNum);

      if ((*pdcch = rgSCHCmnPdcchAlloc(cell, ue, dlSf, y, ueDl->mimoInfo.cwInfo[0].cqi, TFU_DCI_FORMAT_1A, 0)) == 0L)
      {
         return(1);
      }
      *prachMskIdx = 0;
      *rapId = 0;
   }

   return(0);
}
static Void rgSCHCmnGenPdcchOrder
(
RgSchCellCb *cell,
RgSchDlSf *dlSf
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   CmLList *node = cellSch->rachCfg.pdcchOdrLst.first;
   RgSchUeCb *ue;
   U8 rapId;
   U8 prachMskIdx;
   RgSchPdcch *pdcch = 0L;

   ;;

   while (node)
   {
      ue = (RgSchUeCb *)node->node;
      node = node->next;



      if ((ue->measGapCb.isMeasuring == 1) ||
           (ue->ul.ulInactvMask & 0x01) ||
           (ue->isDrxEnabled &&
             ue->dl.dlInactvMask & 0x08)
           )
      {
         continue;
      }
      if (rgSCHCmnAllocPOParam(cell, dlSf, ue, &pdcch, &rapId,
               &prachMskIdx) != 0)
      {
         break;
      }

      rgSCHCmnFillPdcchOdr2Sf(cell, ue, pdcch, rapId, prachMskIdx);

      rgSCHCmnDlRmvFrmPdcchOdrQ(cell, ue);

      rgSCHPwrUeReset(cell, ue);
   }
   return;
}
static Void rgSCHCmnDlAdd2PdcchOdrQ
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   ;;

   if (ueDl->rachInfo.poLnk.node == 0L)
   {
      cmLListAdd2Tail(&cellSch->rachCfg.pdcchOdrLst, &ueDl->rachInfo.poLnk);
      ueDl->rachInfo.poLnk.node = (U32)ue;
   }
   return;
}
static Void rgSCHCmnDlRmvFrmPdcchOdrQ
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   ;;

   cmLListDelFrm(&cellSch->rachCfg.pdcchOdrLst, &ueDl->rachInfo.poLnk);
   ueDl->rachInfo.poLnk.node = 0L;
   return;
}
static Void rgSCHCmnFillPdcchOdr2Sf
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchPdcch *pdcch,
U8 rapId,
U8 prachMskIdx
)
{
   RgSchUeACqiCb *acqiCb = &(((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->acqiCb));

   ;;

   pdcch->rnti = ue->ueId;
   pdcch->dci.dciFormat = TFU_DCI_FORMAT_1A;
   pdcch->dci.u.format1aInfo.isPdcchOrder = 1;
   pdcch->dci.u.format1aInfo.t.pdcchOrder.preambleIdx = rapId;
   pdcch->dci.u.format1aInfo.t.pdcchOrder.prachMaskIdx = prachMskIdx;




   if(ue->dl.ueDlCqiCfg.aprdCqiCfg.pres)
   {
      ue->dl.reqForCqi = RG_SCH_APCQI_SERVING_CC;
      acqiCb->aCqiTrigWt = 0;
   }


   return;
}
static Void rgSCHCmnDelRachInfo
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U8 rapIdIdx;

   ;;

   if (ueDl->rachInfo.poLnk.node)
   {
      rgSCHCmnDlRmvFrmPdcchOdrQ(cell, ue);
   }
   if (ueDl->rachInfo.hoLnk.node)
   {
      cmLListDelFrm(&cellSch->rachCfg.hoUeLst, &ueDl->rachInfo.hoLnk);
      ueDl->rachInfo.hoLnk.node = 0L;
   }
   if (ueDl->rachInfo.rapIdLnk.node)
   {
      rapIdIdx = ueDl->rachInfo.poRapId - cellSch->rachCfg.dedPrmStart;
      cmLListDelFrm(&cellSch->rachCfg.rapIdMap[rapIdIdx].assgndUes,
          &ueDl->rachInfo.rapIdLnk);
      ueDl->rachInfo.rapIdLnk.node = 0L;
   }
   return;
}
static Void rgSCHCmnHdlHoPo
(
RgSchCellCb *cell,
CmLListCp *raRspLst,
RgSchRaReqInfo *raReq
)






{
   RgSchUeCb *ue = raReq->ue;
   ;;

   if ( ue->isDrxEnabled )
   {
      rgSCHDrxDedRa(cell,ue);
   }
   rgSCHCmnAllocPoHoGrnt(cell, raRspLst, ue, raReq);
   return;
}
static RgSchUeCb* rgSCHCmnGetHoUe
(
RgSchCellCb *cell,
RgSchRaReqInfo *raReq
)





{
   RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);
   CmLList *node;
   CmLListCp *ueLst;
   RgSchUeCb *ue;
   RgSchCmnDlUe *ueDl;
   ;;

   ueLst = &cellSch->rachCfg.hoUeLst;
   node = ueLst->first;
   while (node)
   {
      ue = (RgSchUeCb *)node->node;
      node = node->next;
      ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
      if (ueDl->rachInfo.hoRapId == raReq->raReq.rapId)
      {
         return(ue);
      }
   }
   return(0L);
}



static Void rgSCHCmnDelDedPreamble
(
RgSchCellCb *cell,
U8 preambleId
)





{
   RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);
   CmLList *node;
   CmLListCp *ueLst;
   RgSchUeCb *ue;
   RgSchCmnDlUe *ueDl;
   ;;

   ueLst = &cellSch->rachCfg.hoUeLst;
   node = ueLst->first;
   while (node)
   {
      ue = (RgSchUeCb *)node->node;
      node = node->next;
      ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
      if (ueDl->rachInfo.hoRapId == preambleId)
      {
         cmLListDelFrm(ueLst, &ueDl->rachInfo.hoLnk);
         ueDl->rachInfo.hoLnk.node = (U32)0L;
      }
   }
}
static RgSchUeCb* rgSCHCmnGetPoUe
(
RgSchCellCb *cell,
RgSchRaReqInfo *raReq
)





{
   RgSchCmnCell *cellSch = (RgSchCmnCell *)(cell->sc.sch);
   CmLList *node;
   CmLListCp *ueLst;
   RgSchUeCb *ue;
   RgSchCmnDlUe *ueDl;
   U8 rapIdIdx;
   ;;

   rapIdIdx = raReq->raReq.rapId -cellSch->rachCfg.dedPrmStart;
   ueLst = &cellSch->rachCfg.rapIdMap[rapIdIdx].assgndUes;
   node = ueLst->first;
   while (node)
   {
      ue = (RgSchUeCb *)node->node;
      node = node->next;
      ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));


      cmLListDelFrm(ueLst, &ueDl->rachInfo.rapIdLnk);
      ueDl->rachInfo.rapIdLnk.node = (U32)0L;
      if ((((ueDl->rachInfo.asgnOppr).sfn == (raReq->timingInfo).sfn) && ((ueDl->rachInfo.asgnOppr).subframe == (raReq->timingInfo).subframe)))
      {
         return(ue);
      }
   }

   return(0L);
}
 U8 rgSCHCmnUlGetCqi
(
RgSchCellCb *cell,
RgSchUeCb *ue,
CmLteUeCategory ueCtgy
)






{
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   U8 cqi;

   ;;

   cqi = ueUl->maxUlCqi;

   if (!((ueCtgy != CM_LTE_UE_CAT_5) &&
        (ueUl->validUlCqi > ueUl->maxUlCqi)))
   {
      cqi = ueUl->validUlCqi;
   }







   return(cqi);
}
static S16 rgSCHCmnUlRbAllocForPoHoUe
(
RgSchCellCb *cell,
RgSchUlSf *sf,
RgSchUeCb *ue,
U8 maxRb
)







{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   U8 sbSize = cellUl->sbSize;
   U32 maxBits = ue->ul.maxBytesPerUePerTti*8;
   U32 bits;
   RgSchUlAlloc *alloc;
   U32 nPrb;
   U8 iTbs;
   U32 eff;
   U32 numSb;
   U8 iMcs;
   U8 iMcsCrnt;
   U8 cqi;
   U8 modOdr;
   RgSchUlHole *hole;
   RgSchUlHqProcCb *proc = &ueUl->hqEnt.hqProcCb[cellUl->msg3SchdHqProcIdx];
   CmLteUeCategory ueCtg = (CmLteUeCategory)(((&(((RgSchCmnUe *)(((ue)->cellInfo[0])->sch))->cmn))->ueCat + 1));

   ;;
   if ((hole = rgSCHUtlUlHoleFirst(sf)) == 0L)
   {
      return(1);
   }

   cqi = rgSCHCmnUlGetCqi(cell, ue, ueCtg);
   ;
   iTbs = rgSchCmnUlCqiToTbsTbl[(U8)cell->isCpUlExtend][cqi];
   iMcs = rgSCHCmnUlGetIMcsFrmITbs(iTbs,ueCtg);
   while(iMcs > 15)
   {
       cqi--;
       iTbs = rgSchCmnUlCqiToTbsTbl[(U8)cell->isCpUlExtend][cqi];
       iMcs = rgSCHCmnUlGetIMcsFrmITbs(iTbs, ueCtg);
   }

   do { ; modOdr = (TfuModScheme)rgUlIMcsTbl[iMcs].qm;} while(0);
   if (!cell->isCpUlExtend)
   {
      eff = rgSchCmnNorUlEff[0][iTbs];
   }
   else
   {
      eff = rgSchCmnExtUlEff[0][iTbs];
   }

   bits = ueUl->alloc.reqBytes * 8;
   if (bits < rgSCHCmnUlMinTbBitsForITbs(cellUl, iTbs))
   {
      numSb = 1;
      nPrb = numSb * sbSize;
   }
   else
   {
      if (bits > maxBits)
      {
         bits = maxBits;
         nPrb = bits * 1024 / eff / ((cellUl)->ulNumRePerRb);
         if (nPrb > maxRb)
         {
            nPrb = maxRb;
         }
         numSb = nPrb / sbSize;
      }
      else
      {

         nPrb = (((((((bits * 1024) + (eff)-1) / (eff)))) + (((cellUl)->ulNumRePerRb))-1) / (((cellUl)->ulNumRePerRb)))
                                                      ;
         if (nPrb > maxRb)
         {
            nPrb = maxRb;
         }
         numSb = (((nPrb) + (sbSize)/2) / (sbSize));
      }
   }
   iMcsCrnt = iMcs;

   alloc = rgSCHCmnUlSbAlloc(sf, (U8)((numSb) <= (cellUl->maxSbPerUe) ? (numSb) : (cellUl->maxSbPerUe)),
                             hole);
   if (alloc == 0L)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0043,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                                              "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                              20944      , "rgSCHCmnUlRbAllocForPoHoUe(): Could not get UlAlloc", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                               ;
      return(1);
   }
   rgSCHCmnUlAllocFillRbInfo(cell, sf, alloc);


   alloc->grnt.modOdr = (TfuModScheme) modOdr;
   alloc->grnt.iMcs = iMcs;
   alloc->grnt.iMcsCrnt = iMcsCrnt;
   alloc->grnt.hop = 0;

   alloc->forMsg3 = 1;
   alloc->hqProc = proc;
   alloc->hqProc->ulSfIdx = cellUl->msg3SchdIdx;
   alloc->ue = ue;
   alloc->rnti = ue->ueId;


   ue->initNumRbs = alloc->grnt.numRb;

   ueUl->alloc.alloc = alloc;
   iTbs = rgSCHCmnUlGetITbsFrmIMcs(iMcs);
   ;
   alloc->grnt.datSz = rgTbSzTbl[0][iTbs][alloc->grnt.numRb-1] / 8;


   do { ; alloc->grnt.modOdr = (TfuModScheme)rgUlIMcsTbl[alloc->grnt.iMcsCrnt].qm;} while(0);
   rgSCHUhmNewTx(proc, ueUl->hqEnt.maxHqRetx, alloc);

   return(0);
}
static Void rgSCHCmnAllocPoHoGrnt
(
RgSchCellCb *cell,
CmLListCp *raRspLst,
RgSchUeCb *ue,
RgSchRaReqInfo *raReq
)







{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
   RgSchUlGrnt *grnt;
   RgSchUlSf *sf = &cellUl->ulSfArr[cellUl->msg3SchdIdx];

   ;;


   rgSCHCmnUlUeDelAllocs(cell, ue);

   if (*sf->allocCountRef >= cellUl->maxAllocPerUlSf)
   {
      return;
   }
   ueUl->alloc.reqBytes = 2;
   if (rgSCHCmnUlRbAllocForPoHoUe(cell, sf, ue, 110) != 0)
   {
      return;
   }


   grnt = &ueUl->alloc.alloc->grnt;


   if (grnt == 0L)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0044,L_ERROR,DBG_INSTID, cell->instIdx,ue->ueId, 0, 0, 0,                                                         "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                         21039      , "Failed to get" "the grant for HO/PDCCH Order. CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                          ;
      return;
   }
   ue->ul.rarGrnt.rapId = raReq->raReq.rapId;
   ue->ul.rarGrnt.hop = grnt->hop;
   ue->ul.rarGrnt.rbStart = grnt->rbStart;
   ue->ul.rarGrnt.numRb = grnt->numRb;
   ue->ul.rarGrnt.tpc = grnt->tpc;
   ue->ul.rarGrnt.iMcsCrnt = grnt->iMcsCrnt;
   ue->ul.rarGrnt.ta.pres = 1;
   ue->ul.rarGrnt.ta.val = raReq->raReq.ta;
   ue->ul.rarGrnt.datSz = grnt->datSz;
   if((sf->numACqiCount < 1) && (RG_SCH_APCQI_NO != ue->dl.reqForCqi))
   {
      {
         ue->ul.rarGrnt.cqiReqBit = ue->dl.reqForCqi;
      }
      ue->dl.reqForCqi = RG_SCH_APCQI_NO;
      sf->numACqiCount++;
   }
   else
   {
      ue->ul.rarGrnt.cqiReqBit = 0;
   }

   cmLListAdd2Tail(raRspLst, &ue->ul.rarGrnt.raRspLnk);
   ue->ul.rarGrnt.raRspLnk.node = (U32)ue;

   return;
}
static Void rgSCHCmnUlNonadapRetx
(
RgSchCmnUlCell *cellUl,
RgSchUlAlloc *alloc,
U8 idx
)






{
   ;;
   rgSCHUhmRetx(alloc->hqProc, alloc);


   alloc->hqProc->isRetx = 1;
   alloc->hqProc->ulSfIdx = cellUl->reTxIdx[idx];

   if (alloc->hqProc->rvIdx != 0)
   {
      alloc->grnt.iMcsCrnt = rgSchCmnUlRvIdxToIMcsTbl[alloc->hqProc->rvIdx];
   }
   else
   {
      alloc->grnt.iMcsCrnt = alloc->grnt.iMcs;
   }
   alloc->grnt.isRtx = 1;
   alloc->pdcch = 0L;
   return;
}
static Bool rgSCHCmnUlAllocsOvrLap
(
RgSchUlAlloc *alloc1,
RgSchUlAlloc *alloc2
)





{

   ;;

   if (((alloc1->sbStart >= alloc2->sbStart) &&
         (alloc1->sbStart <= alloc2->sbStart + alloc2->numSb-1)) ||
        ((alloc2->sbStart >= alloc1->sbStart) &&
         (alloc2->sbStart <= alloc1->sbStart + alloc1->numSb-1)))
   {
      return(1);
   }
   return(0);
}
static Void rgSCHCmnUlCpyAllocInfo
(
RgSchCellCb *cell,
RgSchUlAlloc *srcAlloc,
RgSchUlAlloc *dstAlloc
)






{
   RgSchCmnUlUe *ueUl;
   ;;

   dstAlloc->grnt = srcAlloc->grnt;
   dstAlloc->hqProc = srcAlloc->hqProc;
   if (dstAlloc->hqProc)

   {
      dstAlloc->hqProc->alloc = dstAlloc;
   }
   dstAlloc->ue = srcAlloc->ue;
   dstAlloc->rnti = srcAlloc->rnti;
   dstAlloc->forMsg3 = srcAlloc->forMsg3;
   dstAlloc->raCb = srcAlloc->raCb;
   dstAlloc->pdcch = srcAlloc->pdcch;

   if (dstAlloc->ue)
   {
      ueUl = (&(((RgSchCmnUe *)((dstAlloc->ue->cellInfo[dstAlloc->ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
      ueUl->alloc.alloc = dstAlloc;

      if (dstAlloc->ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
      {
         if((dstAlloc->ue->ul.ulSpsInfo.ulSpsSchdInfo.crntAlloc != 0L)
               && (dstAlloc->ue->ul.ulSpsInfo.ulSpsSchdInfo.crntAlloc == srcAlloc))
         {
            dstAlloc->ue->ul.ulSpsInfo.ulSpsSchdInfo.crntAlloc = dstAlloc;
         }
      }

   }

   return;
}
static Void rgSCHCmnUlInsAllocFrmNewSf2OldSf
(
RgSchCellCb *cell,
RgSchUlSf *newSf,
RgSchUlSf *oldSf,
RgSchUlAlloc *srcAlloc
)







{
   RgSchUlAlloc *alloc, *dstAlloc, *nxtAlloc;


   RgSchCmnCell *schCmnCell = (RgSchCmnCell *)(cell->sc.sch);
   U8 remAllocs;
   ;;

   if ((alloc = rgSCHUtlUlAllocFirst(oldSf)) != 0L)
   {
      do
      {
         nxtAlloc = rgSCHUtlUlAllocNxt(oldSf, alloc);



         if (rgSCHCmnUlAllocsOvrLap(alloc, srcAlloc) == 1)
         {
            rgSCHCmnUlUpdAllocRetx(newSf, alloc);
            rgSCHUtlUlAllocRls(oldSf, alloc);
         }

         if (srcAlloc->sbStart + srcAlloc->numSb - 1 <= alloc->sbStart)
         {
            break;
         }
      } while ((alloc = nxtAlloc) != 0L);
   }





   remAllocs = schCmnCell->ul.maxAllocPerUlSf - *oldSf->allocCountRef;
   if (!remAllocs)
   {




      if ((alloc = rgSCHUtlUlAllocFirst(oldSf)) != 0L)
      {
         do
         {
            nxtAlloc = rgSCHUtlUlAllocNxt(oldSf, alloc);
            if (!alloc->mrgdNewTxAlloc)
            {




               rgSCHCmnUlFreeAllocation(cell, oldSf, alloc);
               break;
            }
         }while((alloc = nxtAlloc) != 0L);
      }
   }
   dstAlloc = rgSCHUtlUlGetSpfcAlloc(oldSf, srcAlloc->sbStart, srcAlloc->numSb);
   rgSCHCmnUlCpyAllocInfo(cell, srcAlloc, dstAlloc);


   dstAlloc->mrgdNewTxAlloc = 1;
   return;
}
static Void rgSCHCmnUlMergeSfAllocs
(
RgSchCellCb *cell,
RgSchUlSf *oldSf,
RgSchUlSf *newSf
)






{
   RgSchUlAlloc *alloc, *nxtAlloc;
   ;;
   (cell=cell);



   if ((alloc = rgSCHUtlUlAllocFirst(newSf)) != 0L)
   {
      do
      {
         nxtAlloc = rgSCHUtlUlAllocNxt(newSf, alloc);
         rgSCHCmnUlInsAllocFrmNewSf2OldSf(cell, newSf, oldSf, alloc);
         rgSCHUtlUlAllocRls(newSf, alloc);
      } while((alloc = nxtAlloc) != 0L);
   }
   return;
}
static Void rgSCHCmnUlSwapSfAllocs
(
RgSchCellCb *cell,
RgSchUlSf *oldSf,
RgSchUlSf *newSf
)






{
   RgSchUlAllocDb *tempAllocDb = newSf->allocDb;
   RgSchUlHoleDb *tempHoleDb = newSf->holeDb;
   U8 tempAvailSbs = newSf->availSubbands;

   ;;
   (cell=cell);

   newSf->allocDb = oldSf->allocDb;
   newSf->holeDb = oldSf->holeDb;
   newSf->availSubbands = oldSf->availSubbands;

   oldSf->allocDb = tempAllocDb;
   oldSf->holeDb = tempHoleDb;
   oldSf->availSubbands = tempAvailSbs;


   newSf->allocCountRef = &newSf->allocDb->count;
   oldSf->allocCountRef = &oldSf->allocDb->count;
   return;
}
static Void rgSCHCmnUlPrcNonAdptRetx
(
RgSchCellCb *cell,
RgSchUlSf *newSf,
U8 idx
)






{
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchUlAlloc *alloc, *nxtAlloc;
   ;;


   if ((alloc = rgSCHUtlUlAllocFirst(newSf)) != 0L)
   {
      do
      {
         nxtAlloc = rgSCHUtlUlAllocNxt(newSf, alloc);

         if (alloc->mrgdNewTxAlloc)
         {
            alloc->mrgdNewTxAlloc = 0;
            continue;
         }


         rgSCHCmnUlNonadapRetx(cellUl, alloc, idx);

      } while((alloc = nxtAlloc) != 0L);
   }
   return;
}
static Void rgSCHCmnUlPrfmSfMerge
(
RgSchCellCb *cell,
RgSchUlSf *oldSf,
RgSchUlSf *newSf,
U8 idx
)







{
   ;;


   rgSCHCmnUlMergeSfAllocs(cell, oldSf, newSf);

   rgSCHCmnUlSwapSfAllocs(cell, oldSf, newSf);


   rgSCHCmnUlPrcNonAdptRetx(cell, newSf, idx);

   return;
}
static Void rgSCHCmnUlRmvCmpltdAllocs
(
RgSchCellCb *cell,
RgSchUlSf *sf,
RgSchUlSf *newSf
)






{
   RgSchUlAlloc *alloc, *nxtAlloc;
   ;;

   if ((alloc = rgSCHUtlUlAllocFirst(sf)) == 0L)
   {
      return;
   }
   do
   {
      nxtAlloc = rgSCHUtlUlAllocNxt(sf, alloc);
      if ((alloc->hqProc->rcvdCrcInd) || (alloc->hqProc->remTx == 0))
      {


         if ((alloc->forMsg3 == 1) && (alloc->hqProc->remTx == 0))
         {
            rgNumMsg3FailMaxRetx++;

            cell->tenbStats->sch.msg3Fail++;

         }
         rgSCHCmnUlFreeAllocation(cell, sf, alloc);
      }



      else if((alloc->ue != 0L) && ((1 != alloc->forMsg3) &&
                ((alloc->ue->measGapCb.isMeasuring == 1) ||
                        (alloc->ue->ackNakRepCb.isAckNakRep == 1))))
      {
        rgSCHCmnUlUpdAllocRetx(newSf, alloc);
        rgSCHUtlUlAllocRls(sf, alloc);
      }
   } while ((alloc = nxtAlloc) != 0L);

   return;
}
 Void rgSCHCmnRlsUlSf
(
RgSchCellCb *cell,
U8 idx
)





{
   ;;

   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);

   if ((cellUl->hqFdbkIdx[idx] != 0xff) &&
       (cellUl->reTxIdx[idx] != 0xff))
   {
    RgSchUlSf *oldSf = &cellUl->ulSfArr[cellUl->hqFdbkIdx[idx]];
    RgSchUlSf *newSf = &cellUl->ulSfArr[cellUl->reTxIdx[idx]];


    if (rgSCHUtlUlAllocFirst(oldSf) == 0L)
    {
     return;
    }





    rgSCHCmnUlRmvCmpltdAllocs(cell, oldSf, newSf);


    rgSCHCmnUlPrfmSfMerge(cell, oldSf, newSf,idx);

      oldSf->numACqiCount = 0;
   }
   return;
}
static Void rgSCHCmnUlUpdAllocRetx
(
RgSchUlSf *reTxSf,
RgSchUlAlloc *alloc
)





{
   U8 iTbs;
   ;;
   alloc->hqProc->reTxAlloc.rnti = alloc->rnti;
   alloc->hqProc->reTxAlloc.numSb = alloc->numSb;
   alloc->hqProc->reTxAlloc.iMcs = alloc->grnt.iMcs;
   iTbs = rgSCHCmnUlGetITbsFrmIMcs(alloc->grnt.iMcs);
   ;
   alloc->hqProc->reTxAlloc.tbSz =
      rgTbSzTbl[0][iTbs][alloc->grnt.numRb-1]/8;
   alloc->hqProc->reTxAlloc.ue = alloc->ue;
   alloc->hqProc->reTxAlloc.forMsg3 = alloc->forMsg3;
   alloc->hqProc->reTxAlloc.raCb = alloc->raCb;


   alloc->hqProc->isRetx = 1;
   alloc->hqProc->alloc = 0L;
   alloc->hqProc->ulSfIdx = 0xff;

   cmLListAdd2Tail(&reTxSf->reTxLst, &alloc->hqProc->reTxLnk);
   alloc->hqProc->reTxLnk.node = (U32)alloc->hqProc;

   alloc->hqProc->reTxAlloc.reTxLst = &reTxSf->reTxLst;
   alloc->hqProc->alloc = 0L;
   return;
}
static Bool rgSCHCmnUlAdapRetxAlloc
(
RgSchCellCb *cell,
RgSchUlSf *sf,
RgSchUlHqProcCb *proc,
RgSchUlHole *hole
)







{
   U8 numSb = proc->reTxAlloc.numSb;
   U8 iMcs = proc->reTxAlloc.iMcs;
   CmLteTimingInfo frm = cell->crntTime;
   RgSchCmnUlCell *cellUl = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);
   RgSchDlSf *dlSf;
   RgSchPdcch *pdcch;
   RgSchUlAlloc *alloc;
   ;;




   do { if ((frm.subframe += (4 - 2)) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);
   dlSf = rgSCHUtlSubFrmGet(cell, frm);
   pdcch = rgSCHCmnCmnPdcchAlloc(cell, dlSf);
   if (pdcch == 0L)
   {
      return(0);
   }


   if (numSb <= hole->num)
   {
      alloc = rgSCHUtlUlAllocGetHole(sf, numSb, hole);


         if(alloc == 0L)
         {
            rgSCHUtlPdcchPut(cell, &dlSf->pdcchInfo, pdcch);
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0045,L_ERROR,DBG_CELLID, cell->cellId, proc->reTxAlloc.rnti, 0, 0, 0,                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                      21834            , "UL Alloc fail for msg3 retx for rnti: %d\n", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                                       ;
            return(0);
         }

      rgSCHCmnUlAllocFillRbInfo(cell, sf, alloc);
      alloc->grnt.iMcs = iMcs;
      alloc->grnt.datSz = proc->reTxAlloc.tbSz;
      do { ; alloc->grnt.modOdr = (TfuModScheme)rgUlIMcsTbl[iMcs].qm;} while(0);


      alloc->grnt.nDmrs = 0;
      alloc->grnt.hop = 0;
      alloc->grnt.delayBit = 0;
      alloc->grnt.isRtx = 1;
      proc->ulSfIdx = cellUl->schdIdx;
      alloc->rnti = proc->reTxAlloc.rnti;

      alloc->ue = proc->reTxAlloc.ue;
      alloc->pdcch = pdcch;
      alloc->forMsg3 = proc->reTxAlloc.forMsg3;
      alloc->raCb = proc->reTxAlloc.raCb;
      alloc->hqProc = proc;
      alloc->isAdaptive = 1;


      if (alloc->raCb)
      {
         alloc->raCb->msg3Grnt= alloc->grnt;



         alloc->raCb->msg3AllocTime = cell->crntTime;
         do { if ((alloc->raCb->msg3AllocTime.subframe += (2 + 4)) > 9) { alloc->raCb->msg3AllocTime.sfn = ((alloc->raCb->msg3AllocTime.sfn) + 1) & 0x03ff; alloc->raCb->msg3AllocTime.subframe -= 10; }} while(0);



         rgSCHCmnUlAdapRetx(alloc, proc);

         pdcch->rnti = alloc->rnti;
         pdcch->dci.dciFormat = TFU_DCI_FORMAT_0;
         pdcch->dci.u.format0Info.hoppingEnbld = alloc->grnt.hop;
         pdcch->dci.u.format0Info.rbStart = alloc->grnt.rbStart;
         pdcch->dci.u.format0Info.numRb = alloc->grnt.numRb;
         pdcch->dci.u.format0Info.mcs = alloc->grnt.iMcsCrnt;
         pdcch->dci.u.format0Info.ndi = alloc->hqProc->ndi;
         pdcch->dci.u.format0Info.nDmrs = alloc->grnt.nDmrs;
         pdcch->dci.u.format0Info.tpcCmd = alloc->grnt.tpc;
         pdcch->dciNumOfBits = cell->dciSize.size[TFU_DCI_FORMAT_0];
      }
      else
      {
         RgSchCmnUlUe *ueUl = (&(((RgSchCmnUe *)((alloc->ue->cellInfo[alloc->ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->ul));
         ueUl->alloc.alloc = alloc;

         rgSCHCmnUlUeFillAllocInfo(cell, alloc->ue);

         ueUl->alloc.alloc->pdcch->dci.u.format0Info.cqiReq = RG_SCH_APCQI_NO;
         pdcch->dciNumOfBits = alloc->ue->dciSize.cmnSize[TFU_DCI_FORMAT_0];
      }

      proc->isRetx = 0;
   }
   else
   {
      rgSCHUtlPdcchPut(cell, &dlSf->pdcchInfo, pdcch);
      if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0046,L_DEBUG,DBG_CELLID, cell->cellId, proc->reTxAlloc.rnti, 0, 0, 0,                                   "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                   21909      , "Num SB not suffiecient for adap retx for rnti: %d", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                                    ;
      return(0);
   }
   return(1);
}
static Void rgSCHCmnUlSfRlsRetxProcs
(
RgSchCellCb *cell,
RgSchUlSf *sf
)





{
   CmLListCp *cp;
   CmLList *node;
   RgSchUlHqProcCb *proc;

   ;;

   cp = &(sf->reTxLst);
   node = cp->first;
   while (node)
   {
      proc = (RgSchUlHqProcCb *)node->node;
      node = node->next;

      cmLListDelFrm(proc->reTxAlloc.reTxLst, &proc->reTxLnk);
      proc->reTxLnk.node = (U32)0L;
      proc->reTxAlloc.reTxLst = (U32)0L;
   }
   return;
}
static Void rgSCHCmnUlSfReTxAllocs
(
RgSchCellCb *cell,
RgSchUlSf *sf
)





{
   CmLListCp *cp;
   CmLList *node;
   RgSchUlHqProcCb *proc;
   RgSchUlHole *hole;
   RgSchUeCb *ue;
   RgSchCmnCell *schCmnCell = (RgSchCmnCell *)(cell->sc.sch);
   ;;

   cp = &(sf->reTxLst);
   node = cp->first;
   while ((node))
   {
      proc = (RgSchUlHqProcCb *)node->node;
      ue = proc->reTxAlloc.ue;
      node = node->next;



      if((ue != 0L) &&
            ((ue->measGapCb.isMeasuring == 1)||
               (ue->ackNakRepCb.isAckNakRep == 1)))
      {
         continue;
      }

      if (((hole = rgSCHUtlUlHoleFirst(sf)) == 0L)
            || (sf->allocDb->count == schCmnCell->ul.maxAllocPerUlSf))
      {

         break;
      }

      if (rgSCHCmnUlAdapRetxAlloc(cell, sf, proc, hole) == 0)
      {
         continue;
      }

      cmLListDelFrm(proc->reTxAlloc.reTxLst, &proc->reTxLnk);

      proc->reTxLnk.node = (U32)0L;
      proc->reTxAlloc.reTxLst = (U32)0L;
   }
   return;
}
static Void rgSCHCmnDlRbAlloc
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   ;;

   if (cellSch->dl.isDlFreqSel)
   {
      cellSch->apisDlfs->rgSCHDlfsAllocRb(cell, allocInfo);
   }
   else
   {
      rgSCHCmnNonDlfsRbAlloc(cell, allocInfo);
   }
   return;
}
 Void rgSCHCmnDlGetRbgInfo
(
U8 dlTotalBw,
U8 dlSubsetBw,
U8 maxRaType1SubsetBw,
U8 rbgSize,
RgSchBwRbgInfo *rbgInfo
)
{
   rbgInfo->numRbgs = ((dlSubsetBw + rbgSize - 1)/rbgSize);
   rbgInfo->lastRbgSize = rbgSize -
            (dlSubsetBw - ((dlSubsetBw/rbgSize) * rbgSize));



   rbgInfo->numRbs = (rbgInfo->numRbgs * rbgSize > dlTotalBw) ?
      dlTotalBw:(rbgInfo->numRbgs * rbgSize);
   rbgInfo->rbgSize = rbgSize;
}
 U8 rgSCHCmnDlRaType0Alloc
(
RgSchDlSfAllocInfo *allocedInfo,
U8 rbsReq,
RgSchBwRbgInfo *rbgInfo,
U8 *numAllocRbs,
RgSchDlSfAllocInfo *resAllocInfo,
Bool isPartialAlloc
)
{

   U32 remNumRbs, rbgPosInRbgMask, ueRaType2Mask;
   U8 type2MaskIdx, cnt, rbIdx;
   U8 maskSize, rbg;
   U8 bestNumAvailRbs = 0;
   U8 usedRbs = 0;
   U8 numAllocRbgs = 0;
   U8 rbgSize = rbgInfo->rbgSize;
   U32 *rbgMask = &(resAllocInfo->raType0Mask);






   U32 *raType2Mask = resAllocInfo->raType2Mask;

   U32 allocedMask = allocedInfo->raType0Mask;

   maskSize = rbgInfo->numRbgs;

   *numAllocRbs = 0;
   { U8 _pos = 0; *&usedRbs = 0; for (_pos = 0; _pos < maskSize; ++_pos) { *&usedRbs += (allocedMask & (1 << (31 - _pos))) ? 1: 0; }};
   if (maskSize == usedRbs)
   {

      remNumRbs = 0;
   }
   else
   {
      remNumRbs = (maskSize - usedRbs - 1) * rbgSize;


      if (!(allocedMask & (1 << (31 - (maskSize - 1)))))
      {
         remNumRbs += rbgInfo->lastRbgSize;
      }
   }



   if (!isPartialAlloc)
   {
      if (remNumRbs >= rbsReq)
      {
         bestNumAvailRbs = rbsReq;
      }
   }
   else
   {
      bestNumAvailRbs = remNumRbs > rbsReq ? rbsReq : remNumRbs;
   }


   if (bestNumAvailRbs)
   {
      for (rbg = 0; rbg < maskSize - 1; ++rbg)
      {
         rbgPosInRbgMask = 1 << (31 - (rbg));
         if (!(allocedMask & rbgPosInRbgMask))
         {

            *rbgMask |= rbgPosInRbgMask;


            rbIdx = rbg * rbgSize;

            for (cnt = 0; cnt < rbgSize; ++cnt)
            {



               ueRaType2Mask = rgSCHCmnGetRaType2Mask(rbIdx, &type2MaskIdx);






               raType2Mask[type2MaskIdx] |= ueRaType2Mask;
               rbIdx++;
            }
            *numAllocRbs += rbgSize;
            remNumRbs -= rbgSize;
            ++numAllocRbgs;
            if (*numAllocRbs >= bestNumAvailRbs)
            {
               break;
            }
         }
      }


      if (*numAllocRbs < bestNumAvailRbs)
      {
         rbgPosInRbgMask = 1 << (31 - (rbg));
         *rbgMask |= rbgPosInRbgMask;
         *numAllocRbs += rbgInfo->lastRbgSize;


         rbIdx = ((rbgInfo->numRbgs - 1 ) * rbgSize );

         for (cnt = 0; cnt < rbgInfo->lastRbgSize; ++cnt)
         {



            ueRaType2Mask = rgSCHCmnGetRaType2Mask(rbIdx, &type2MaskIdx);






            raType2Mask[type2MaskIdx] |= ueRaType2Mask;
            rbIdx++;
         }
         remNumRbs -= rbgInfo->lastRbgSize;
         ++numAllocRbgs;
      }


   }

   return(numAllocRbgs);
}
 U8 rgSCHCmnDlRaType2Alloc
(
RgSchDlSfAllocInfo *allocedInfo,
U8 rbsReq,
RgSchBwRbgInfo *rbgInfo,
U8 *rbStart,
RgSchDlSfAllocInfo *resAllocInfo,
Bool isPartialAlloc
)
{
   U8 numAllocRbs = 0;
   U8 rbIdx;
   U8 rbgSize = rbgInfo->rbgSize;
   U32 *rbgMask = &resAllocInfo->raType0Mask;



   U32 *raType2Mask = resAllocInfo->raType2Mask;



   U32 *allocedMask = allocedInfo->raType2Mask;


   rgSCHCmnDlGetBestFitHole(allocedMask, rbgInfo->numRbs,
         raType2Mask, rbsReq, rbStart, &numAllocRbs, isPartialAlloc);
   if (numAllocRbs)
   {

      U8 rbCnt = numAllocRbs;




      U32 ueRaType0Mask;
      rbIdx = *rbStart;

      while(rbCnt)
      {

         ueRaType0Mask = rgSCHCmnGetRaType0Mask(rbIdx, rbgSize);
         *rbgMask |= ueRaType0Mask;
         --rbCnt;
         rbIdx++;
      }
   }

   return(numAllocRbs);
}
static U32 rgSCHCmnGetRaType0Mask
(
U8 rbIdx,
U8 rbgSize
)





{
   U8 rbg;
   U32 rbgPosInRbgMask = 0;

   rbg = rbIdx/rbgSize;
   rbgPosInRbgMask = 1 << (31 - (rbg));

   return(rbgPosInRbgMask);
}
static U32 rgSCHCmnGetRaType2Mask
(
U8 rbIdx,
U8 *maskIdx
)





{
   U32 rbPosInType2;

   *maskIdx = rbIdx / 32;
   rbPosInType2 = 1 << (31 - (rbIdx % 32));

   return(rbPosInType2);
}
 Bool rgSCHCmnAllocUeInSpsBw
(
RgSchDlSf *dlSf,
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlRbAlloc *rbAllocInfo,
Bool isPartialAlloc
)
{
   U8 rbgSize = cell->rbgSize;
   U8 numAllocRbs = 0;
   U8 numAllocRbgs = 0;
   U8 rbStart = 0;
   U8 idx, noLyr, iTbs;
   RgSchCmnDlUe *dlUe = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   RgSchDlSfAllocInfo *dlSfAlloc = &rbAllocInfo->dlSf->dlSfAllocInfo;
   RgSchBwRbgInfo *spsRbgInfo = &cell->spsBwRbgInfo;
   U32 y;



   if ((0 == rbAllocInfo->tbInfo[0].schdlngForTb) &&
         (0 == rbAllocInfo->tbInfo[1].schdlngForTb))
   {
      return(1);
   }


   if (dlSf->spsAllocdBw == spsRbgInfo->numRbs)
   {

      return(0);
   }
   if (!isPartialAlloc)
   {
      if((dlSf->spsAllocdBw + rbAllocInfo->rbsReq) > spsRbgInfo->numRbs)
      {
         return(1);
      }
   }



   if (rbAllocInfo->raType == 0)
   {
      rbAllocInfo->rbsReq += (rbgSize - rbAllocInfo->rbsReq % rbgSize);
      numAllocRbgs = rgSCHCmnDlRaType0Alloc(dlSfAlloc,
            rbAllocInfo->rbsReq, spsRbgInfo, &numAllocRbs,
            &rbAllocInfo->resAllocInfo, isPartialAlloc);
   }
   else if (rbAllocInfo->raType == 2)
   {
      numAllocRbs = rgSCHCmnDlRaType2Alloc(dlSfAlloc,
            rbAllocInfo->rbsReq, spsRbgInfo,
            &rbStart, &rbAllocInfo->resAllocInfo, isPartialAlloc);
   }
   if (!numAllocRbs)
   {
      return(1);
   }

   y = rgSCHUtlGetY(ue, dlSf->sfNum);
   if (!(rbAllocInfo->pdcch =
            rgSCHCmnPdcchAlloc(cell, ue, dlSf, y, dlUe->mimoInfo.cwInfo[0].cqi,
               rbAllocInfo->dciFormat, 0)))
   {

      return(1);
   }


   iTbs = rbAllocInfo->tbInfo[0].iTbs;
   noLyr = rbAllocInfo->tbInfo[0].noLyr;
   rbAllocInfo->tbInfo[0].bytesAlloc =
      rgTbSzTbl[noLyr - 1][iTbs][numAllocRbs - 1]/8;

   if (rbAllocInfo->tbInfo[1].schdlngForTb)
   {
      iTbs = rbAllocInfo->tbInfo[1].iTbs;
      noLyr = rbAllocInfo->tbInfo[1].noLyr;
      rbAllocInfo->tbInfo[1].bytesAlloc =
         rgTbSzTbl[noLyr - 1][iTbs][numAllocRbs - 1]/8;;
   }


   if (rbAllocInfo->raType == 0)
   {
      rbAllocInfo->allocInfo.raType0.dlAllocBitMask =
         rbAllocInfo->resAllocInfo.raType0Mask;
      rbAllocInfo->allocInfo.raType0.numDlAlloc = numAllocRbgs;
   }
   else if (rbAllocInfo->raType == 2)
   {
      rbAllocInfo->allocInfo.raType2.isLocal = 1;
      rbAllocInfo->allocInfo.raType2.rbStart = rbStart;
      rbAllocInfo->allocInfo.raType2.numRb = numAllocRbs;
   }

   rbAllocInfo->rbsAlloc = numAllocRbs;
   rbAllocInfo->tbInfo[0].schdlngForTb = 1;




   dlSfAlloc->raType0Mask |= rbAllocInfo->resAllocInfo.raType0Mask;
   for (idx = 0; idx < 4; ++idx)
   {
      dlSfAlloc->raType2Mask[idx] |= rbAllocInfo->resAllocInfo.raType2Mask[idx];
   }

   dlSf->spsAllocdBw += numAllocRbs;
   return(1);
}
static Void rgSCHCmnDlGetBestFitHole
(
U32 *allocMask,
U8 numMaskRbs,
U32 *crntAllocMask,
U8 rbsReq,
U8 *allocStart,
U8 *allocNumRbs,
Bool isPartialAlloc
)
{
   U8 maskSz = (numMaskRbs + 31)/32;
   U8 maxMaskPos = (numMaskRbs % 32);
   U8 maskIdx, maskPos;
   U8 numAvailRbs = 0;
   U8 bestAvailNumRbs = 0;
   S8 bestStartPos = -1;
   S8 startPos = -1;
   U32 tmpMask[4] = {0};
   U32 bestMask[4] = {0};

   *allocNumRbs = numAvailRbs;
   *allocStart = 0;

   for (maskIdx = 0; maskIdx < maskSz; ++maskIdx)
   {
      maxMaskPos = 31;
      if (maskIdx == (maskSz - 1))
      {
         if (numMaskRbs % 32)
         {
            maxMaskPos = numMaskRbs % 32;
         }
      }
      for (maskPos = 0; maskPos < maxMaskPos; ++maskPos)
      {
         if (!(allocMask[maskIdx] & (1 << (31 - maskPos))))
         {
            tmpMask[maskIdx] |= (1 << (31 - maskPos));
            if (startPos == -1)
            {
               startPos = maskIdx * 32 + maskPos;
            }
            ++numAvailRbs;
            if (numAvailRbs == rbsReq)
            {
               *allocStart = (U8)startPos;
               *allocNumRbs = rbsReq;
               break;
            }
         }
         else
         {
            if (numAvailRbs > bestAvailNumRbs)
            {
               bestAvailNumRbs = numAvailRbs;
               bestStartPos = startPos;
               cmMemcpy((U8 *)bestMask, (U8 *) tmpMask, 4 * sizeof(U32));
            }
            numAvailRbs = 0;
            startPos = -1;
            cmMemset((U8 *)tmpMask, 0, 4 * sizeof(U32));
         }
      }
      if (*allocNumRbs == rbsReq)
      {
         break;
      }
   }

   if (*allocNumRbs == rbsReq)
   {

      cmMemcpy((U8 *)crntAllocMask, (U8 *) tmpMask, 4 * sizeof(U32));
      return;
   }
   else
   {
      if (bestAvailNumRbs && isPartialAlloc)
      {

         *allocStart = (U8)bestStartPos;
         *allocNumRbs = bestAvailNumRbs;

         cmMemcpy((U8 *)crntAllocMask, (U8 *) bestMask, 4 * sizeof(U32));
      }
   }

   return;
}
static Void rgSCHCmnFindCodeRate
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
RgSchDlRbAlloc *allocInfo,
U8 idx
)







{
    U8 numOvrlapgPbchRb = 0;
    U32 numPdschRe = 0;
    U32 code_rate;
    U8 numResvdRePerSpclSf = 0;
    RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);

    U8 numResvdRePerSf = ((cellDl->currCfi * 12) + (cell->numCellRSPerSf - (1 << cell->numTxAntPorts)));

    ;


    if(dlSf->sfNum == 5)
    {
        rgSCHCmnFindNumPbchOvrlapRbs(cell,dlSf,allocInfo,&numOvrlapgPbchRb);
        numResvdRePerSpclSf = (((cellDl->currCfi + 2) *
                                  12) + (cell->numCellRSPerSf - (1 << cell->numTxAntPorts)));
    }
    else if (dlSf->sfNum == 0)
    {
        rgSCHCmnFindNumPbchOvrlapRbs(cell,dlSf,allocInfo,&numOvrlapgPbchRb);
        numResvdRePerSpclSf = (((cellDl->currCfi + 2 + 4) *
                                  12) + (cell->numCellRSPerSf - ((1 << cell->numTxAntPorts)*2)));
    }

    numPdschRe = (12 * 14 * allocInfo->rbsReq) -
                 ((numResvdRePerSf * (allocInfo->rbsReq - numOvrlapgPbchRb)) +
                  (numResvdRePerSpclSf * numOvrlapgPbchRb));

    code_rate = (((allocInfo->tbInfo[idx].bytesReq)*8*100)/(numPdschRe * 6));
    return;
}
static Void rgSCHCmnNonDlfsPbchTbImcsAdj
(
RgSchCellCb *cell,
RgSchDlRbAlloc *allocInfo,
U8 idx,
U8 rbsReq
)







{
   U8 noLyrs = 0;
   U8 tbs = 0;
   U32 origBytesReq;
   U8 noRbgs = 0;
   U8 noRbs = 0;
   RgSchDlSf *dlSf = allocInfo->dlSf;

   do { if (allocInfo->tbInfo[idx].imcs <= 9) tbs = allocInfo->tbInfo[idx].imcs; else if (allocInfo->tbInfo[idx].imcs <= 16) tbs = allocInfo->tbInfo[idx].imcs - 1; else tbs = allocInfo->tbInfo[idx].imcs - 2; }while(0);
   noLyrs = allocInfo->tbInfo[idx].noLyr;

   if((allocInfo->raType == 0))
   {
      noRbgs = ((((allocInfo->rbsReq + dlSf->lstRbgDfct)) + (cell->rbgSize)-1) / (cell->rbgSize));
      noRbs = (noRbgs * cell->rbgSize) - dlSf->lstRbgDfct;
   }
   else
   {
       noRbs = allocInfo->rbsReq;
   }


   if (allocInfo->rbsReq == 0 )
   {
      return;
   }
   origBytesReq = rgTbSzTbl[noLyrs - 1][tbs][rbsReq - 1]/8;



   if(tbs > 0)
   {
      if(((rgTbSzTbl[noLyrs - 1][0][noRbs - 1])/8) < origBytesReq)
      {
          ;
          while(((rgTbSzTbl[noLyrs - 1][tbs][noRbs - 1])/8) > origBytesReq)
          {
              tbs--;
          }
      }
      else
      {
          tbs = 0;
      }
      allocInfo->tbInfo[idx].bytesReq = rgTbSzTbl[noLyrs - 1][tbs][noRbs - 1]/8;
      allocInfo->tbInfo[idx].iTbs = tbs;
      do { if (tbs <= 9) allocInfo->tbInfo[idx].imcs = tbs; else if (tbs <= 15) allocInfo->tbInfo[idx].imcs = tbs + 1; else allocInfo->tbInfo[idx].imcs = tbs + 2;} while(0);
   }

   return;
}
static Void rgSCHCmnNonDlfsPbchTbSizeAdj
(
RgSchDlRbAlloc *allocInfo,
U8 numOvrlapgPbchRb,
U8 pbchSsRsSym,
U8 idx,
U32 bytesReq
)
{
   U32 reducedTbs = 0;
   U8 noLyrs = 0;
   U8 tbs = 0;

   noLyrs = allocInfo->tbInfo[idx].noLyr;

   do { if (allocInfo->tbInfo[idx].imcs <= 9) tbs = allocInfo->tbInfo[idx].imcs; else if (allocInfo->tbInfo[idx].imcs <= 16) tbs = allocInfo->tbInfo[idx].imcs - 1; else tbs = allocInfo->tbInfo[idx].imcs - 2; }while(0);

   reducedTbs = bytesReq - (((U32)numOvrlapgPbchRb * (U32)pbchSsRsSym * 6)/8);




   if(((rgTbSzTbl[noLyrs - 1][0][allocInfo->rbsReq - 1])/8) < reducedTbs)
   {
       while(((rgTbSzTbl[noLyrs - 1][tbs][allocInfo->rbsReq - 1])/8) > reducedTbs)
       {
           tbs--;
       }
   }
   else
   {
       tbs = 0;
   }
   allocInfo->tbInfo[idx].bytesReq = rgTbSzTbl[noLyrs - 1][tbs][allocInfo->rbsReq - 1]/8;
   allocInfo->tbInfo[idx].iTbs = tbs;
   do { if (tbs <= 9) allocInfo->tbInfo[idx].imcs = tbs; else if (tbs <= 15) allocInfo->tbInfo[idx].imcs = tbs + 1; else allocInfo->tbInfo[idx].imcs = tbs + 2;} while(0);

   return;
}
static U8 rgSCHCmnFindNumAddtlRbsAvl
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
RgSchDlRbAlloc *allocInfo
)






{
    U8 addtlRbsAvl = 0;

    ;

    if (allocInfo->raType == 0)
    {
         addtlRbsAvl = (((dlSf->type0End - dlSf->type2End + 1)*
                        cell->rbgSize) - dlSf->lstRbgDfct) - allocInfo->rbsReq;
    }
    else if (allocInfo->raType == 2)
    {
       addtlRbsAvl = (dlSf->bw - dlSf->bwAlloced) - allocInfo->rbsReq;
    }

    return(addtlRbsAvl);

}
static Void rgSCHCmnFindNumPbchOvrlapRbs
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
RgSchDlRbAlloc *allocInfo,
U8 *numOvrlapgPbchRb
)







{
    *numOvrlapgPbchRb = 0;
    ;



   if(dlSf->bwAlloced <= (cell->pbchRbStart))
   {




       if((dlSf->bwAlloced + allocInfo->rbsReq) > cell->pbchRbStart)
       {
           *numOvrlapgPbchRb = (dlSf->bwAlloced + allocInfo->rbsReq) - (cell->pbchRbStart);
           if(*numOvrlapgPbchRb > 6)
                *numOvrlapgPbchRb = 6;
       }
   }
   else if ((dlSf->bwAlloced > (cell->pbchRbStart)) &&
         (dlSf->bwAlloced < (cell->pbchRbEnd)))
   {




      if(dlSf->bwAlloced + allocInfo->rbsReq < (cell->pbchRbEnd))
      {


         *numOvrlapgPbchRb = allocInfo->rbsReq;
      }
      else
      {


         *numOvrlapgPbchRb = (cell->pbchRbEnd) - dlSf->bwAlloced;
      }
   }
    return;

}
static Void rgSCHCmnNonDlfsPbchRbAllocAdj
(
RgSchCellCb *cell,
RgSchDlRbAlloc *allocInfo,
U8 pbchSsRsSym,
Bool isBcchPcch
)







{
   RgSchDlSf *dlSf = allocInfo->dlSf;
   U8 numOvrlapgPbchRb = 0;
   U8 numOvrlapgAdtlPbchRb = 0;
   U8 totSym;
   U8 addtlRbsReq = 0;
   U8 moreAddtlRbsReq = 0;
   U8 addtlRbsAdd = 0;
   U8 moreAddtlRbsAdd = 0;
   U8 tbs;
   U8 origRbsReq = 0;
   U32 bytesReq;
   U8 noLyr;
   U8 divResult;


   ;;


   origRbsReq = allocInfo->rbsReq;
   rgSCHCmnFindNumPbchOvrlapRbs(cell,dlSf,allocInfo,&numOvrlapgPbchRb);

  totSym = (cell->isCpDlExtend) ? 144 : 168;




   divResult = (numOvrlapgPbchRb * pbchSsRsSym)/totSym;
   if((numOvrlapgPbchRb * pbchSsRsSym) % totSym)
   {
      divResult++;
   }
   addtlRbsReq = divResult;

   { U8 addtlRbsAvl; addtlRbsAvl = rgSCHCmnFindNumAddtlRbsAvl(cell,dlSf,allocInfo); if(addtlRbsReq > addtlRbsAvl) { addtlRbsAdd = addtlRbsAvl; } else { addtlRbsAdd = addtlRbsReq; }}



   allocInfo->rbsReq = allocInfo->rbsReq + addtlRbsAdd;




   if(addtlRbsAdd && ((dlSf->bwAlloced + allocInfo->rbsReq - addtlRbsAdd) < (cell->pbchRbEnd)))
   {
      if((dlSf->bwAlloced + allocInfo->rbsReq) <= (cell->pbchRbEnd))
      {



          divResult = (addtlRbsAdd * pbchSsRsSym)/totSym;
          if((addtlRbsAdd * pbchSsRsSym) % totSym)
          {
            divResult++;
          }

          moreAddtlRbsReq = divResult;

          { U8 addtlRbsAvl; addtlRbsAvl = rgSCHCmnFindNumAddtlRbsAvl(cell,dlSf,allocInfo); if(moreAddtlRbsReq > addtlRbsAvl) { moreAddtlRbsAdd = addtlRbsAvl; } else { moreAddtlRbsAdd = moreAddtlRbsReq; }}

          allocInfo->rbsReq = allocInfo->rbsReq + moreAddtlRbsAdd;
      }
      else
      {




          numOvrlapgAdtlPbchRb = (cell->pbchRbEnd) - ((dlSf->bwAlloced + allocInfo->rbsReq) - addtlRbsAdd);

          divResult = (numOvrlapgAdtlPbchRb * pbchSsRsSym)/totSym;
          if((numOvrlapgAdtlPbchRb * pbchSsRsSym) % totSym)
          {
             divResult++;
          }

          moreAddtlRbsReq = divResult;

          { U8 addtlRbsAvl; addtlRbsAvl = rgSCHCmnFindNumAddtlRbsAvl(cell,dlSf,allocInfo); if(moreAddtlRbsReq > addtlRbsAvl) { moreAddtlRbsAdd = addtlRbsAvl; } else { moreAddtlRbsAdd = moreAddtlRbsReq; }}

          allocInfo->rbsReq = allocInfo->rbsReq + moreAddtlRbsAdd;
      }
   }
   if (isBcchPcch == 1)
   {
      return;
   }

   do { if (allocInfo->tbInfo[0].imcs <= 9) tbs = allocInfo->tbInfo[0].imcs; else if (allocInfo->tbInfo[0].imcs <= 16) tbs = allocInfo->tbInfo[0].imcs - 1; else tbs = allocInfo->tbInfo[0].imcs - 2; }while(0);
   if(tbs == 6)
   {


      allocInfo->rbsReq = allocInfo->rbsReq - addtlRbsAdd - moreAddtlRbsAdd;
   }
   else if(tbs && ((0 == addtlRbsAdd) && (moreAddtlRbsAdd == 0)))
   {






      rgSCHCmnFindNumPbchOvrlapRbs(cell,dlSf,allocInfo,&numOvrlapgPbchRb);

      noLyr = allocInfo->tbInfo[0].noLyr;
      ;
      bytesReq = rgTbSzTbl[noLyr - 1][tbs][allocInfo->rbsReq - 1]/8;

      rgSCHCmnNonDlfsPbchTbSizeAdj(allocInfo,numOvrlapgPbchRb,pbchSsRsSym,0,bytesReq);

      if(allocInfo->tbInfo[1].schdlngForTb == 1)
      {
          noLyr = allocInfo->tbInfo[1].noLyr;
          bytesReq = rgTbSzTbl[noLyr - 1][tbs][allocInfo->rbsReq - 1]/8;
          rgSCHCmnNonDlfsPbchTbSizeAdj(allocInfo,numOvrlapgPbchRb,pbchSsRsSym,1,bytesReq);
      }

   }
   else if(tbs && ((addtlRbsAdd != addtlRbsReq) ||
          (addtlRbsAdd && (moreAddtlRbsReq != moreAddtlRbsAdd))))
   {





      rgSCHCmnNonDlfsPbchTbImcsAdj(cell, allocInfo, 0 , origRbsReq);

      if(allocInfo->tbInfo[1].schdlngForTb == 1)
      {
          rgSCHCmnNonDlfsPbchTbImcsAdj(cell, allocInfo, 1 , origRbsReq);
      }

      rgSCHCmnFindNumPbchOvrlapRbs(cell,dlSf,allocInfo,&numOvrlapgPbchRb);
      numOvrlapgPbchRb = numOvrlapgPbchRb - (addtlRbsAdd + moreAddtlRbsAdd);

      rgSCHCmnNonDlfsPbchTbSizeAdj(allocInfo,numOvrlapgPbchRb,pbchSsRsSym,0,allocInfo->tbInfo[0].bytesReq);

      if(allocInfo->tbInfo[1].schdlngForTb == 1)
      {
          rgSCHCmnNonDlfsPbchTbSizeAdj(allocInfo,numOvrlapgPbchRb,pbchSsRsSym,1,allocInfo->tbInfo[1].bytesReq);
      }

   }
   else
   {



      rgSCHCmnNonDlfsPbchTbImcsAdj(cell, allocInfo, 0 , origRbsReq);

      if(allocInfo->tbInfo[1].schdlngForTb == 1)
      {
          rgSCHCmnNonDlfsPbchTbImcsAdj(cell, allocInfo, 1 , origRbsReq);
      }
   }

   return;
}
static S16 rgSCHCmnNonDlfsCmnRbAlloc
(
RgSchCellCb *cell,
RgSchDlRbAlloc *allocInfo
)





{


   U8 rbsAlloc = 0;

   U8 pbchSsRsSym = 0;
   U8 pbchFrame = 0;
   U8 tbs = 0;
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);

   RgSchDlSf *dlSf = allocInfo->dlSf;

   U8 rbStart = 0;
   U8 spsRbsAlloc = 0;
   RgSchDlSfAllocInfo *dlSfAlloc = &allocInfo->dlSf->dlSfAllocInfo;

   ;;

   allocInfo->tbInfo[0].noLyr = 1;




   allocInfo->resAllocInfo.raType0Mask = 0;
   cmMemset((U8*)allocInfo->resAllocInfo.raType1Mask, 0,
         4 * sizeof (U32));
   cmMemset((U8*)allocInfo->resAllocInfo.raType2Mask, 0,
         4 * sizeof (U32));

   if ((dlSf->spsAllocdBw >= cell->spsBwRbgInfo.numRbs) &&
         (dlSf->bwAlloced == dlSf->bw))



   {
      return(1);
   }

   if (allocInfo->rbsReq > (dlSf->bw - dlSf->bwAlloced))
   {

      if ((allocInfo->tbInfo[0].imcs < 29) && (dlSf->bwAlloced < dlSf->bw))



      {

         allocInfo->rbsReq = dlSf->bw - dlSf->bwAlloced;
         do { if (allocInfo->tbInfo[0].imcs <= 9) tbs = allocInfo->tbInfo[0].imcs; else if (allocInfo->tbInfo[0].imcs <= 16) tbs = allocInfo->tbInfo[0].imcs - 1; else tbs = allocInfo->tbInfo[0].imcs - 2; }while(0);
         allocInfo->tbInfo[0].bytesReq = rgTbSzTbl[0][tbs][allocInfo->rbsReq - 1]/8;
      }
      else
      {


         if (dlSf->spsAllocdBw < cell->spsBwRbgInfo.numRbs)
         {
            spsRbsAlloc =
               rgSCHCmnDlRaType2Alloc(dlSfAlloc,
                     allocInfo->rbsReq, &cell->spsBwRbgInfo, &rbStart,
                     &allocInfo->resAllocInfo, 0);


            rbsAlloc = spsRbsAlloc;
            dlSf->spsAllocdBw += spsRbsAlloc;
         }
         if (!spsRbsAlloc)

         {
            return(1);
         }
      }
   }



   allocInfo->pdcch = rgSCHCmnCmnPdcchAlloc(cell, dlSf);
   if (allocInfo->pdcch == 0L)
   {
      return(1);
   }
   allocInfo->dciFormat = TFU_DCI_FORMAT_1A;
   allocInfo->pdcch->dciNumOfBits = cell->dciSize.size[TFU_DCI_FORMAT_1A];
   allocInfo->raType = 2;
   allocInfo->allocInfo.raType2.isLocal = 1;

   if (spsRbsAlloc)
   {
      allocInfo->allocInfo.raType2.rbStart = rbStart;
      allocInfo->allocInfo.raType2.numRb = allocInfo->rbsReq;
      allocInfo->rbsAlloc = allocInfo->rbsReq;
   }



   if (!spsRbsAlloc)
   {


      if(dlSf->sfNum)
      {
         if(!(dlSf->sfNum == 5))
         {


            allocInfo->allocInfo.raType2.rbStart = rbStart;




         }
         else
         {
            pbchFrame = 1;


            pbchSsRsSym = (((cellDl->currCfi) + 2) *
                  12 + cell->numCellRSPerSf);
         }
      }
      else
      {
         pbchFrame = 1;


         pbchSsRsSym = (((cellDl->currCfi) + 4 +
                  2) * 12 +
               cell->numCellRSPerSf);
      }

      if((pbchFrame) &&
            (((dlSf->bwAlloced + allocInfo->rbsReq) - cell->pbchRbStart) > 0)&&
            (dlSf->bwAlloced < cell->pbchRbEnd))
      {
         if(allocInfo->tbInfo[0].imcs < 29)
         {
            rgSCHCmnNonDlfsPbchRbAllocAdj(cell, allocInfo, pbchSsRsSym, 1);
         }
      }


   }



   if (!spsRbsAlloc)
   {


      allocInfo->allocInfo.raType2.rbStart = (U8)dlSf->type2Start;
      allocInfo->allocInfo.raType2.numRb = allocInfo->rbsReq;
      allocInfo->rbsAlloc = allocInfo->rbsReq;



      if (cell->lteAdvCb.sfrCfg.status == RGR_ENABLE)
      {
         rgSCHCmnNonDlfsSFRCmnChannelUpdTyp2Alloc(cell, dlSf,
               allocInfo->allocInfo.raType2.rbStart,
               allocInfo->allocInfo.raType2.numRb);
      }
      else

      {
         rgSCHCmnNonDlfsUpdTyp2Alloc(cell, dlSf,
               allocInfo->allocInfo.raType2.rbStart,
               allocInfo->allocInfo.raType2.numRb);
      }


   }


   allocInfo->tbInfo[0].bytesAlloc = allocInfo->tbInfo[0].bytesReq;



   if (spsRbsAlloc)
   {
      U8 idx;

      dlSfAlloc->raType0Mask |= allocInfo->resAllocInfo.raType0Mask;
      for (idx = 0; idx < 4; ++idx)
      {
         dlSfAlloc->raType2Mask[idx] |=
            allocInfo->resAllocInfo.raType2Mask[idx];
      }
   }


   return(0);
}
static Bool rgSCHCmnNonDlfsSFRBwAvlbl
(
RgSchCellCb *cell,
RgSchSFRPoolInfo **sfrpoolInfo,
RgSchDlSf *dlSf,
RgSchDlRbAlloc *allocInfo,
Bool isUeCellEdge
)
{
   CmLListCp *l;
   CmLListCp *l1;
   CmLList *n;
   CmLList *n1;
   RgSchSFRPoolInfo *sfrPool;
   RgSchSFRPoolInfo *sfrCEPool;

   U8 tbs;
   U8 noLyrs;
   RgSchSFRPoolInfo *poolWithMaxAvlblBw = 0L;
   U32 bwAvlbl = 0;
   U32 addtnlPRBs = 0;

   if (dlSf->bw <= dlSf->bwAlloced)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0047,L_ERROR,DBG_CELLID, cell->cellId, dlSf->sfNum, allocInfo->rnti, 0, 0,                                                                                           "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                                           23848      , "BW is fully allocated for subframe (%d) CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                            ;
      return 0;
   }

   if (dlSf->sfrTotalPoolInfo.ccBwFull == 1)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0048,L_ERROR,DBG_CELLID, cell->cellId,allocInfo->rnti, 0, 0, 0,                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                        23855      , "BW is fully allocated for CC Pool CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                         ;
      return 0;
   }

   if ((dlSf->sfrTotalPoolInfo.ceBwFull == 1) && (isUeCellEdge))
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0049,L_ERROR,DBG_CELLID, cell->cellId,allocInfo->rnti, 0, 0, 0,                                                                        "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                        23862      , "BW is fully allocated for CE Pool CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                         ;
      return 0;
   }




   if(isUeCellEdge)
   {
      l = &dlSf->sfrTotalPoolInfo.cePool;
   }
   else
   {
      l = &dlSf->sfrTotalPoolInfo.ccPool;
   }

   n = ((l)->crnt = (l)->first);

   while(n)
   {
      if (allocInfo->raType == 0)
      {
         sfrPool = (RgSchSFRPoolInfo*)(n->node);


         if(allocInfo->tbInfo[0].tbCb->txCntr)
         {


            if (allocInfo->rbsReq % cell->rbgSize == 0)
            {
               if ((sfrPool->type2End == dlSf->type2End) && dlSf->lstRbgDfct)
               {

                  sfrPool->type0End--;
                  sfrPool->bwAlloced += (cell->rbgSize - dlSf->lstRbgDfct);

                  dlSf->lstRbgDfct = 0;


                  dlSf->type0End--;
                  dlSf->bwAlloced += (cell->rbgSize - dlSf->lstRbgDfct);
               }
            }
            else
            {
               if (dlSf->lstRbgDfct)
               {

                  if ((allocInfo->rbsReq % cell->rbgSize) != (cell->rbgSize - dlSf->lstRbgDfct))
                  {
                     return(0);
                  }
                  else
                  {
                     if (sfrPool->type2End != dlSf->type2End)
                     {
                        continue;
                     }
                  }
               }
               else
               {

                  return(0);
               }
            }
         }


         if(allocInfo->rbsReq <= (((sfrPool->type0End - sfrPool->type2End + 1)*
                     cell->rbgSize) - dlSf->lstRbgDfct))
         {
            *sfrpoolInfo = sfrPool;
            return(1);
         }
         else
         {
            if (sfrPool->bw <= sfrPool->bwAlloced + cell->rbgSize)
            {
               n = ((l)->crnt = ((l)->crnt ? (l)->crnt->next : (l)->first));



               if((!isUeCellEdge) && (!n->node))
               {
                  l = &dlSf->sfrTotalPoolInfo.cePool;
                  n = ((l)->crnt = (l)->first);
               }

               continue;
            }


            if(allocInfo->tbInfo[0].tbCb->txCntr == 0)
            {

               allocInfo->rbsReq = (((sfrPool->type0End - sfrPool->type2End + 1)*
                        cell->rbgSize) - dlSf->lstRbgDfct);
               do { if (allocInfo->tbInfo[0].imcs <= 9) tbs = allocInfo->tbInfo[0].imcs; else if (allocInfo->tbInfo[0].imcs <= 16) tbs = allocInfo->tbInfo[0].imcs - 1; else tbs = allocInfo->tbInfo[0].imcs - 2; }while(0);
               noLyrs = allocInfo->tbInfo[0].noLyr;
               allocInfo->tbInfo[0].bytesReq = rgTbSzTbl[noLyrs-1][tbs][allocInfo->rbsReq - 1]/8;
               *sfrpoolInfo = sfrPool;
               return(1);
            }
            else
            {
               n = ((l)->crnt = ((l)->crnt ? (l)->crnt->next : (l)->first));



               if((!isUeCellEdge) && (!n->node))
               {
                  l = &dlSf->sfrTotalPoolInfo.cePool;
                  n = ((l)->crnt = (l)->first);
               }

               continue;
            }


         }
      }
      else if (allocInfo->raType == 2)
      {
         sfrPool = (RgSchSFRPoolInfo*)(n->node);


         if ((isUeCellEdge) &&
            (allocInfo->tbInfo[0].tbCb->txCntr != 0))
         {
            if(allocInfo->rbsReq > (sfrPool->bw - sfrPool->bwAlloced))
            {




               if (sfrPool->type0End == (((sfrPool->poolendRB + 1) / cell->rbgSize) - 1))
               {
                  if (sfrPool->adjCCPool &&
                        (sfrPool->adjCCPool->type2Start == sfrPool->poolendRB + 1) &&
                        (allocInfo->rbsReq <= ((sfrPool->bw - sfrPool->bwAlloced) +
                                               ((sfrPool->adjCCPool->bw - sfrPool->adjCCPool->bwAlloced)))))
                  {
                     addtnlPRBs = allocInfo->rbsReq - (sfrPool->bw - sfrPool->bwAlloced);


                     sfrPool->bw += addtnlPRBs;
                     sfrPool->type0End = ((sfrPool->poolendRB + addtnlPRBs + 1) /
                           cell->rbgSize) - 1;


                     sfrPool->adjCCPool->type2Start += addtnlPRBs;
                     sfrPool->adjCCPool->type2End = (((sfrPool->adjCCPool->type2Start) + (cell->rbgSize)-1) / (cell->rbgSize))
                                         ;
                     sfrPool->adjCCPool->bw -= addtnlPRBs;
                     *sfrpoolInfo = sfrPool;
                     return(1);
                  }
               }
            }
         }





         if(1 == sfrPool->CCPool2Exists)
         {
            l1 = &dlSf->sfrTotalPoolInfo.cePool;
            n1 = ((l1)->crnt = (l1)->first);
            sfrCEPool = (RgSchSFRPoolInfo*)(n1->node);
            if(allocInfo->rbsReq <= (sfrCEPool->bw - sfrCEPool->bwAlloced))
            {
               *sfrpoolInfo = sfrCEPool;
               return(1);
            }
            else if(allocInfo->rbsReq <= (sfrPool->bw - sfrPool->bwAlloced))
            {
               *sfrpoolInfo = sfrPool;
               return(1);
            }

            else if ((sfrPool->poolstartRB == sfrPool->type2Start) &&
                  (sfrCEPool->type0End == ((sfrCEPool->poolendRB + 1) / cell->rbgSize) - 1))
            {
               if(allocInfo->rbsReq <= (sfrCEPool->bw - sfrCEPool->bwAlloced) +
                     (sfrPool->bw - sfrPool->bwAlloced))
               {



                  addtnlPRBs = allocInfo->rbsReq - (sfrPool->bw - sfrPool->bwAlloced);


                  sfrPool->type2Start -= addtnlPRBs;
                  sfrPool->type2End = (((sfrPool->type2Start) + (cell->rbgSize)-1) / (cell->rbgSize));
                  sfrPool->bw += addtnlPRBs;
                  if (addtnlPRBs == (sfrCEPool->bw - sfrCEPool->bwAlloced))
                  {
                     sfrCEPool->bwAlloced = sfrCEPool->bw;
                     dlSf->sfrTotalPoolInfo.ceBwFull = 1;
                  }
                  else
                  {
                     sfrCEPool->bw -= addtnlPRBs;
                     sfrCEPool->type0End = ((sfrCEPool->poolendRB + 1 - addtnlPRBs) / cell->rbgSize) - 1;
                  }
                  *sfrpoolInfo = sfrPool;
                  return(1);
               }
               else if ( bwAvlbl <
                     ((sfrCEPool->bw - sfrCEPool->bwAlloced) +
                      (sfrPool->bw - sfrPool->bwAlloced)))
               {

                  if(allocInfo->tbInfo[0].tbCb->txCntr == 0)
                  {
                     sfrPool->type2Start = sfrCEPool->type2Start;
                     sfrPool->bw += sfrCEPool->bw - sfrCEPool->bwAlloced;
                     sfrCEPool->type2Start = sfrCEPool->poolendRB + 1;
                     sfrCEPool->bwAlloced = sfrCEPool->bw;
                     dlSf->sfrTotalPoolInfo.ceBwFull = 1;


                     allocInfo->rbsReq = (sfrPool->bw - sfrPool->bwAlloced);
                     do { if (allocInfo->tbInfo[0].imcs <= 9) tbs = allocInfo->tbInfo[0].imcs; else if (allocInfo->tbInfo[0].imcs <= 16) tbs = allocInfo->tbInfo[0].imcs - 1; else tbs = allocInfo->tbInfo[0].imcs - 2; }while(0);
                     noLyrs = allocInfo->tbInfo[0].noLyr;
                     allocInfo->tbInfo[0].bytesReq =
                        rgTbSzTbl[noLyrs-1][tbs][allocInfo->rbsReq - 1]/8;
                     *sfrpoolInfo = sfrPool;
                     return(1);
                  }
                  else
                  {
                     return(0);
                  }
               }
            }
         }
         if (allocInfo->rbsReq <= (sfrPool->bw - sfrPool->bwAlloced))
         {
            *sfrpoolInfo = sfrPool;
            return(1);
         }
         else
         {
            if(allocInfo->tbInfo[0].tbCb->txCntr == 0)
            {
               if (bwAvlbl < sfrPool->bw - sfrPool->bwAlloced)
               {
                  if (isUeCellEdge)
                  {
                     dlSf->sfrTotalPoolInfo.ceBwFull = 1;
                  }
                  bwAvlbl = sfrPool->bw - sfrPool->bwAlloced;
                  poolWithMaxAvlblBw = sfrPool;
               }
               n = ((l)->crnt = ((l)->crnt ? (l)->crnt->next : (l)->first));

               if ((isUeCellEdge == 0) && (n == 0L))
               {
                  if(l != &dlSf->sfrTotalPoolInfo.cePool)
                  {
                     l = &dlSf->sfrTotalPoolInfo.cePool;
                     n = ((l)->crnt = (l)->first);
                  }
               }

               if (n == 0L)
               {
                  if (bwAvlbl == 0)
                  {
                     if (isUeCellEdge)
                     {
                        dlSf->sfrTotalPoolInfo.ceBwFull = 1;
                     }
                     else
                     {
                        dlSf->sfrTotalPoolInfo.ccBwFull = 1;
                     }
                     return(0);
                  }
                  else
                  {

                     allocInfo->rbsReq = poolWithMaxAvlblBw->bw -
                        poolWithMaxAvlblBw->bwAlloced;
                     do { if (allocInfo->tbInfo[0].imcs <= 9) tbs = allocInfo->tbInfo[0].imcs; else if (allocInfo->tbInfo[0].imcs <= 16) tbs = allocInfo->tbInfo[0].imcs - 1; else tbs = allocInfo->tbInfo[0].imcs - 2; }while(0);
                     noLyrs = allocInfo->tbInfo[0].noLyr;
                     allocInfo->tbInfo[0].bytesReq =
                        rgTbSzTbl[noLyrs-1][tbs][allocInfo->rbsReq - 1]/8;
                     *sfrpoolInfo = poolWithMaxAvlblBw;
                     return(1);
                  }
               }
            }
            else
            {
               n = ((l)->crnt = ((l)->crnt ? (l)->crnt->next : (l)->first));

               if ((isUeCellEdge == 0) && (n == 0L))
               {
                  if(l != &dlSf->sfrTotalPoolInfo.cePool)
                  {
                     l = &dlSf->sfrTotalPoolInfo.cePool;
                     n = ((l)->crnt = (l)->first);
                  }
               }

               if (n == 0L)
               {
                  return(0);
               }
            }

         }
      }
   }
   return(0);
}
static Bool rgSCHCmnNonDlfsBwAvlbl
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
RgSchDlRbAlloc *allocInfo
)






{
   U8 tbs;
   U8 noLyrs;
   U8 ignoredDfctRbg = 0;

   ;;
   if (dlSf->bw <= dlSf->bwAlloced)
   {
      if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb004a,L_DEBUG,DBG_CELLID, cell->cellId, dlSf->bw, dlSf->bwAlloced, allocInfo->rnti, 0,                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                  24234      , "(%d:%d)FAILED CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                   ;
      return(0);
   }
   if (allocInfo->raType == 0)
   {


       if(allocInfo->tbInfo[0].tbCb->txCntr)
       {



          if (allocInfo->rbsReq % cell->rbgSize == 0)
          {
             if (dlSf->lstRbgDfct)
             {


                dlSf->type0End--;
                dlSf->bwAlloced += (cell->rbgSize - dlSf->lstRbgDfct);

                dlSf->lstRbgDfct = 0;
                ignoredDfctRbg = 1;

             }
          }
          else
          {
             if (dlSf->lstRbgDfct)
             {

                if ((allocInfo->rbsReq % cell->rbgSize) != (cell->rbgSize - dlSf->lstRbgDfct))
                {
                   return(0);
                }
             }
             else
             {

                return(0);
             }
          }
       }



      if(allocInfo->rbsReq <= (((dlSf->type0End - dlSf->type2End + 1)*
               cell->rbgSize) - dlSf->lstRbgDfct))
      {
         return(1);
      }


      else
      {

         if (dlSf->bw <= dlSf->bwAlloced + cell->rbgSize)
         {


            if(ignoredDfctRbg == 1)
            {
               dlSf->type0End++;
               dlSf->bwAlloced -= (cell->rbgSize - dlSf->lstRbgDfct);
               dlSf->lstRbgDfct = 1;
            }


            return(0);
         }


         if(allocInfo->tbInfo[0].tbCb->txCntr == 0)
         {

            allocInfo->rbsReq = (((dlSf->type0End - dlSf->type2End + 1)*
                        cell->rbgSize) - dlSf->lstRbgDfct);
            do { if (allocInfo->tbInfo[0].imcs <= 9) tbs = allocInfo->tbInfo[0].imcs; else if (allocInfo->tbInfo[0].imcs <= 16) tbs = allocInfo->tbInfo[0].imcs - 1; else tbs = allocInfo->tbInfo[0].imcs - 2; }while(0);
            noLyrs = allocInfo->tbInfo[0].noLyr;
            allocInfo->tbInfo[0].bytesReq = rgTbSzTbl[noLyrs-1][tbs][allocInfo->rbsReq - 1]/8;
         }
         else
         {


            if(ignoredDfctRbg == 1)
            {
               dlSf->type0End++;
               dlSf->bwAlloced -= (cell->rbgSize - dlSf->lstRbgDfct);
               dlSf->lstRbgDfct = 1;
            }

            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb004b,L_ERROR,DBG_CELLID, cell->cellId, allocInfo->rnti, 0, 0, 0,                                 "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"            ,                                 24336            , "FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                  ;
            return(0);
         }
         return(1);
      }
   }
   else if (allocInfo->raType == 2)
   {
      if (allocInfo->rbsReq <= (dlSf->bw - dlSf->bwAlloced))
      {
         return(1);
      }


      else
      {


         if(allocInfo->tbInfo[0].tbCb->txCntr == 0)
         {

            allocInfo->rbsReq = dlSf->bw - dlSf->bwAlloced;
            do { if (allocInfo->tbInfo[0].imcs <= 9) tbs = allocInfo->tbInfo[0].imcs; else if (allocInfo->tbInfo[0].imcs <= 16) tbs = allocInfo->tbInfo[0].imcs - 1; else tbs = allocInfo->tbInfo[0].imcs - 2; }while(0);
            noLyrs = allocInfo->tbInfo[0].noLyr;
            allocInfo->tbInfo[0].bytesReq = rgTbSzTbl[noLyrs-1][tbs][allocInfo->rbsReq - 1]/8;
         }
         else
         {
            if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb004c,L_ERROR,DBG_CELLID, cell->cellId,allocInfo->rnti, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c",24373, "FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); };
            return(0);
         }


         return(1);
      }
   }
   if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb004d,L_ERROR,DBG_CELLID, cell->cellId,allocInfo->rnti, 0, 0, 0, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c",24381, "FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); };
   return(0);
}
 Void rgSCHCmnNonDlfsSFRCmnChannelUpdTyp2Alloc
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
U8 rbStrt,
U8 numRb
)







{
   CmLListCp *l;
   CmLList *n;
   RgSchSFRPoolInfo *sfrPool;
   ;;

   l = &dlSf->sfrTotalPoolInfo.ccPool;

   dlSf->type2End = ((((rbStrt+numRb)) + (cell->rbgSize)-1) / (cell->rbgSize));
   dlSf->bwAlloced += numRb;
   dlSf->type2Start += numRb;
   n = ((l)->crnt = (l)->first);

   while(n->node)
   {
    sfrPool = (RgSchSFRPoolInfo*)(n->node);
      n = ((l)->crnt = ((l)->crnt ? (l)->crnt->next : (l)->first));


      if((sfrPool->poolendRB >= dlSf->type2Start) && (sfrPool->type2Start < dlSf->type2Start))
      {
         sfrPool->type2End = dlSf->type2End;
         sfrPool->bwAlloced = dlSf->type2Start - sfrPool->poolstartRB;
         sfrPool->type2Start = dlSf->type2Start;
      }
      else
      {

         if(dlSf->type2Start > sfrPool->poolendRB)
         {
           sfrPool->type2End = sfrPool->type0End + 1;
           sfrPool->bwAlloced = sfrPool->bw;
           sfrPool->type2Start = sfrPool->poolendRB + 1;
         }
      }
      if (!n)
      {
         if (l != &dlSf->sfrTotalPoolInfo.cePool)
         {
            l = &dlSf->sfrTotalPoolInfo.cePool;
            n = ((l)->crnt = (l)->first);
         }
         else
            return;
      }
   }
   return;
}
static S16 rgSCHCmnNonDlfsUpdDSFRTyp2Alloc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlSf *dlSf,
U8 rbStrt,
U8 numRb
)
{
   CmLListCp *l;
   CmLList *n;
   RgSchSFRPoolInfo *sfrCCPool1 = 
                                  ((void *)0)
                                      ;
   RgSchSFRPoolInfo *sfrCCPool2 = 
                                  ((void *)0)
                                      ;
   S16 ret = 1;

   ;;



   l = &dlSf->sfrTotalPoolInfo.ccPool;
   n = ((l)->crnt = (l)->first);
   while(n)
   {
      sfrCCPool1 = (RgSchSFRPoolInfo*)(n->node);

      if (sfrCCPool1 == 0L)
            {
               if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb004e,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, 0, 0, 0,                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"               ,                                                                  24519               , "rgSCHCmnNonDlfsUpdDSFRTyp2Alloc():" "sfrCCPool1 is NULL for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                   ;
               return(1);
            }
      n = ((l)->crnt = ((l)->crnt ? (l)->crnt->next : (l)->first));
      if(n)
      {
          sfrCCPool2 = (RgSchSFRPoolInfo*)(n->node);
          n = ((l)->crnt = ((l)->crnt ? (l)->crnt->next : (l)->first));
      }
      if((sfrCCPool1) && (sfrCCPool2))
      {

          if(((dlSf->type2Start >= sfrCCPool1->pwrHiCCRange.startRb) &&
              (dlSf->type2Start + numRb < sfrCCPool1->pwrHiCCRange.endRb)) ||
             ((dlSf->type2Start >= sfrCCPool2->pwrHiCCRange.startRb) &&
              (dlSf->type2Start + numRb < sfrCCPool2->pwrHiCCRange.endRb)))
          {
               ue->lteAdvUeCb.isCCUePHigh = 1;


               ret = rgSCHCmnBuildRntpInfo(cell, dlSf->rntpInfo.val, dlSf->type2Start, numRb, dlSf->bw);
               if (ret != 0)
               {
                    if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb004f,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, 0, 0, 0,                                                                                               "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"                    ,                                                                                               24543                    , "rgSCHCmnNonDlfsUpdDSFRTyp2Alloc():" "rgSCHCmnBuildRntpInfo() function returned RFAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                                ;
                    return(1);
               }
           }
      }
      else
      {
         if((dlSf->type2Start >= sfrCCPool1->pwrHiCCRange.startRb) &&
               (dlSf->type2Start + numRb < sfrCCPool1->pwrHiCCRange.endRb))
         {
            ue->lteAdvUeCb.isCCUePHigh = 1;


            ret = rgSCHCmnBuildRntpInfo(cell, dlSf->rntpInfo.val, dlSf->type2Start, numRb, dlSf->bw);
            if (ret != 0)
            {
               if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0050,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, 0, 0, 0,                                                                                             "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"               ,                                                                                             24560               , "rgSCHCmnNonDlfsUpdDSFRTyp2Alloc():" "rgSCHCmnBuildRntpInfo() function returned RFAILED CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                                              ;
               return(1);
            }
         }
      }
   }
   dlSf->type2End = ((((rbStrt+numRb)) + (cell->rbgSize)-1) / (cell->rbgSize));





   return(0);
}
static Void rgSCHCmnNonDlfsUpdTyp2Alloc
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
U8 rbStrt,
U8 numRb
)







{
   ;;

   dlSf->type2End = ((((rbStrt+numRb)) + (cell->rbgSize)-1) / (cell->rbgSize));

   dlSf->bwAlloced += numRb;

   dlSf->type2Start += numRb;

   return;
}
static Void rgSCHCmnNonDlfsType0Alloc
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
RgSchDlRbAlloc *allocInfo,
RgSchUeCb *ue
)







{
   U32 dlAllocMsk = 0;
   U8 rbgFiller = dlSf->lstRbgDfct;
   U8 noRbgs = ((((allocInfo->rbsReq + rbgFiller)) + (cell->rbgSize)-1) / (cell->rbgSize));

   U8 noRbs;
   U8 noLyr;
   U8 iTbs;
   U32 tb1BytesAlloc = 0;
   U32 tb2BytesAlloc = 0;
   U32 availBits = 0;
   RgSchCmnDlUe *dlUe = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   ;;



   noRbs = (noRbgs * cell->rbgSize) - rbgFiller;
   if (dlSf->bwAlloced + noRbs > dlSf->bw)
   {
      if (--noRbgs == 0)
      {
         return;
      }
      noRbs = (noRbgs * cell->rbgSize) - rbgFiller;
   }





   if((noRbs > allocInfo->rbsReq) &&
         (allocInfo->rbsReq + rbgFiller) % cell->rbgSize)
   {


      if ((allocInfo->tbInfo[0].schdlngForTb) && (!allocInfo->tbInfo[0].tbCb->txCntr))
      {
         iTbs = allocInfo->tbInfo[0].iTbs;
         noLyr = allocInfo->tbInfo[0].noLyr;
         tb1BytesAlloc = rgTbSzTbl[noLyr - 1][iTbs][noRbs - 1]/8;
      }

      if ((allocInfo->tbInfo[1].schdlngForTb) && (!allocInfo->tbInfo[1].tbCb->txCntr))
      {
         iTbs = allocInfo->tbInfo[1].iTbs;
         noLyr = allocInfo->tbInfo[1].noLyr;
         tb2BytesAlloc = rgTbSzTbl[noLyr - 1][iTbs][noRbs - 1]/8;
      }


      if (tb1BytesAlloc || tb2BytesAlloc)
      {
         if (dlUe->maxTbBits > ue->dl.aggTbBits)
         {
            availBits = dlUe->maxTbBits - ue->dl.aggTbBits;
         }
         if (( ue->dl.aggTbBits >= dlUe->maxTbBits) ||
               (tb1BytesAlloc >= dlUe->maxTbSz/8) ||
               (tb2BytesAlloc >= dlUe->maxTbSz/8) ||
               (noRbs >= dlUe->maxRb))
         {
            if (--noRbgs == 0)
            {
               return;
            }
            noRbs = (noRbgs * cell->rbgSize) - rbgFiller;
         }
      }
   }



   dlAllocMsk |= (((1 << noRbgs) - 1) << (31 - dlSf->type0End));

   dlSf->type0End -= noRbgs;




   dlSf->bwAlloced += noRbs;


   allocInfo->allocInfo.raType0.numDlAlloc = noRbgs;
   allocInfo->allocInfo.raType0.dlAllocBitMask |= dlAllocMsk;
   allocInfo->rbsAlloc = noRbs;


   iTbs = allocInfo->tbInfo[0].iTbs;
   noLyr = allocInfo->tbInfo[0].noLyr;


   if (allocInfo->tbInfo[0].tbCb->txCntr)
   {
      allocInfo->tbInfo[0].bytesAlloc =
         allocInfo->tbInfo[0].bytesReq;
   }
   else
   {
      allocInfo->tbInfo[0].bytesAlloc =
         rgTbSzTbl[noLyr - 1][iTbs][noRbs - 1]/8;
   }

   if (allocInfo->tbInfo[1].schdlngForTb)
   {
      iTbs = allocInfo->tbInfo[1].iTbs;
      noLyr = allocInfo->tbInfo[1].noLyr;


      if (allocInfo->tbInfo[1].tbCb->txCntr)
      {
         allocInfo->tbInfo[1].bytesAlloc =
            allocInfo->tbInfo[1].bytesReq;
      }
      else
      {
         allocInfo->tbInfo[1].bytesAlloc =
            rgTbSzTbl[noLyr - 1][iTbs][noRbs - 1]/8;;
      }
   }



   dlSf->lstRbgDfct = 0;
   return;
}
static S16 rgSCHCmnBuildRntpInfo
(
RgSchCellCb *cell,
U8 *rntpPtr,
U8 startRb,
U8 nmbRb,
U16 bw
)
{
   U16 rbPtrStartIdx;
   U16 rbPtrEndIdx;
   U16 rbBitLoc;
   U16 nmbRbPerByte;

   ;;

   rbPtrStartIdx = (startRb)/8;
   rbPtrEndIdx = (startRb + nmbRb)/8;

   if (rntpPtr == 0L)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0051,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                                  25210      , "rgSCHCmnBuildRntpInfo():" "rntpPtr can't be NULLP (Memory Allocation Failed)", RLOG_FILE_ID, RLOG_MODULE_NAME); }

                                                                   ;
      return(1);
   }

   while(rbPtrStartIdx <= rbPtrEndIdx)
   {
      rbBitLoc = (startRb)%8;


      if (rbPtrStartIdx == rbPtrEndIdx)
      {
         rntpPtr[rbPtrStartIdx] = rntpPtr[rbPtrStartIdx]
                                     | (((1<<nmbRb)-1)<<rbBitLoc);
      }


      if (rbPtrStartIdx != rbPtrEndIdx)
      {
         nmbRbPerByte = 8 - rbBitLoc;
         nmbRb = nmbRb - nmbRbPerByte;
         rntpPtr[rbPtrStartIdx] = rntpPtr[rbPtrStartIdx]
                                     | (((1<<nmbRbPerByte)-1)<<rbBitLoc);
         startRb = startRb + nmbRbPerByte;
      }

      rbPtrStartIdx++;
   }





   return(0);
}
static S16 rgSCHCmnNonDlfsUpdSFRPoolTyp2Alloc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlSf *dlSf,
RgSchSFRPoolInfo *sfrPool,
U8 rbStrt,
U8 numRb
)
{




   ;;
   dlSf->type2End = ((((rbStrt+numRb)) + (cell->rbgSize)-1) / (cell->rbgSize));
   sfrPool->type2End = ((((rbStrt+numRb)) + (cell->rbgSize)-1) / (cell->rbgSize));
   return(0);
}
static Void rgSCHCmnNonDlfsSFRPoolType0Alloc
(
RgSchCellCb *cell,
RgSchDlSf *dlSf,
RgSchSFRPoolInfo *poolInfo,
RgSchDlRbAlloc *allocInfo
)







{
   U32 dlAllocMsk = 0;
   U8 rbgFiller = 0;
   U8 noRbgs = 0;
   U8 noRbs;
   U8 noLyr;
   U8 iTbs;

   ;;

   if (poolInfo->poolstartRB + poolInfo->bw == dlSf->bw)
   {
  if (poolInfo->type0End == dlSf->bw/4)
  {
   rbgFiller = dlSf->lstRbgDfct;


   dlSf->lstRbgDfct = 0;
  }
   }

   noRbgs = ((((allocInfo->rbsReq + rbgFiller)) + (cell->rbgSize)-1) / (cell->rbgSize));



   noRbs = (noRbgs * cell->rbgSize) - rbgFiller;
   if (dlSf->bwAlloced + noRbs > dlSf->bw)
   {
      if (--noRbgs == 0)
      {
         return;
      }
      noRbs = (noRbgs * cell->rbgSize) - rbgFiller;
   }







   dlAllocMsk |= (((1 << noRbgs) - 1) << (31 - poolInfo->type0End));

   poolInfo->type0End -= noRbgs;



   poolInfo->bwAlloced += noRbs + dlSf->lstRbgDfct;
   dlSf->bwAlloced += noRbs + dlSf->lstRbgDfct;


   allocInfo->allocInfo.raType0.numDlAlloc = noRbgs;
   allocInfo->allocInfo.raType0.dlAllocBitMask |= dlAllocMsk;
   allocInfo->rbsAlloc = noRbs;


   iTbs = allocInfo->tbInfo[0].iTbs;
   noLyr = allocInfo->tbInfo[0].noLyr;


   if (allocInfo->tbInfo[0].tbCb->txCntr)
   {
      allocInfo->tbInfo[0].bytesAlloc =
         allocInfo->tbInfo[0].bytesReq;
   }
   else
   {
      allocInfo->tbInfo[0].bytesAlloc =
         rgTbSzTbl[noLyr - 1][iTbs][noRbs - 1]/8;
   }

   if (allocInfo->tbInfo[1].schdlngForTb)
   {
      iTbs = allocInfo->tbInfo[1].iTbs;
      noLyr = allocInfo->tbInfo[1].noLyr;


      if (allocInfo->tbInfo[1].tbCb->txCntr)
      {
         allocInfo->tbInfo[1].bytesAlloc =
            allocInfo->tbInfo[1].bytesReq;
      }
      else
      {
         allocInfo->tbInfo[1].bytesAlloc =
            rgTbSzTbl[noLyr - 1][iTbs][noRbs - 1]/8;;
      }
   }



   dlSf->lstRbgDfct = 0;
   return;
}
static void rgSCHCmnNonDlfsDsfrRntpComp
(
RgSchCellCb *cell,
RgSchDlSf *dlSf
)





{
   static U16 samples = 0;
   U16 i;
   U16 bwBytes = (dlSf->bw-1)/8;
   RgrLoadInfIndInfo *rgrLoadInf;
   U16 len;
   U16 ret = 0;

   ;;

   len = (dlSf->bw % 8 == 0) ? dlSf->bw/8 : dlSf->bw/8 + 1;


   for(i = 0; i <= bwBytes; i++)
   {
     cell->rntpAggrInfo.val[i] |= dlSf->rntpInfo.val[i];
   }
   samples = samples + 1;


   if(10000 == samples)
   {

      ret = rgSCHUtlAllocSBuf (cell->instIdx,(Data**)&rgrLoadInf,
               sizeof(RgrLoadInfIndInfo));
      if (ret != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0052,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                  25515         , "Could not " "allocate memory for sending LoadInfo", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                   ;
         return;
      }

      rgrLoadInf->u.rntpInfo.pres = cell->rntpAggrInfo.pres;

      rgrLoadInf->u.rntpInfo.len = len;


      rgrLoadInf->u.rntpInfo.val = cell->rntpAggrInfo.val;
      rgrLoadInf->cellId = cell->cellId;


      rgrLoadInf->bw = dlSf->bw;
      rgrLoadInf->type = RGR_SFR;

      ret = rgSCHUtlRgrLoadInfInd(cell, rgrLoadInf);
      if(ret == 1)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0053,L_ERROR,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                            25535         , "rgSCHCmnNonDlfsDsfrRntpComp():" "rgSCHUtlRgrLoadInfInd() returned RFAILED", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                             ;
      }

      cmMemset(cell->rntpAggrInfo.val,0,len);
      samples = 0;
   }
 }
static S16 rgSCHCmnSFRNonDlfsUeRbAlloc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlSf *dlSf,
U8 *isDlBwAvail
)







{
   U32 y;
   RgSchDlRbAlloc *allocInfo;
   RgSchCmnDlUe *dlUe;
   Bool isUECellEdge;
   RgSchSFRPoolInfo *sfrpoolInfo = 0L;

   ;;

   isUECellEdge = ue->lteAdvUeCb.rgrLteAdvUeCfg.isUeCellEdge;;

   dlUe = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   *isDlBwAvail = 1;


   if (rgSCHCmnNonDlfsSFRBwAvlbl(cell, &sfrpoolInfo, dlSf, allocInfo, isUECellEdge) != 1)
   {


      if (isUECellEdge)
      {
         *isDlBwAvail = 1;
      }
      else
      {
         *isDlBwAvail = 0;
      }
      return(1);
   }


   y = rgSCHUtlGetY(ue, dlSf->sfNum);

   if (dlUe->proc->tbInfo[0].isAckNackDtx == 4 || dlUe->proc->tbInfo[1].isAckNackDtx)
   {
      allocInfo->pdcch = rgSCHCmnPdcchAlloc(cell, ue, dlSf, y, dlUe->mimoInfo.cwInfo[0].cqi, allocInfo->dciFormat, 1);
   }
   else
   {
      allocInfo->pdcch = rgSCHCmnPdcchAlloc(cell, ue, dlSf, y, dlUe->mimoInfo.cwInfo[0].cqi, allocInfo->dciFormat,0);
   }

   if (!(allocInfo->pdcch))
   {

      return(1);
   }


   allocInfo->rnti = ue->ueId;
   if (allocInfo->raType == 2)
   {
      allocInfo->allocInfo.raType2.isLocal = 1;


      allocInfo->allocInfo.raType2.rbStart = (U8)sfrpoolInfo->type2Start;
      allocInfo->allocInfo.raType2.numRb = allocInfo->rbsReq;


      rgSCHCmnNonDlfsUpdSFRPoolTyp2Alloc(cell, ue, dlSf, sfrpoolInfo,
            allocInfo->allocInfo.raType2.rbStart,
            allocInfo->allocInfo.raType2.numRb);
      allocInfo->rbsAlloc = allocInfo->rbsReq;
      allocInfo->tbInfo[0].bytesAlloc = allocInfo->tbInfo[0].bytesReq;
   }
   else if (allocInfo->raType == 0)
   {
      rgSCHCmnNonDlfsSFRPoolType0Alloc(cell, dlSf, sfrpoolInfo, allocInfo);
   }


   rgSCHCmnFindCodeRate(cell,dlSf,allocInfo,0);
   if(allocInfo->tbInfo[1].schdlngForTb == 1)
   {
      rgSCHCmnFindCodeRate(cell,dlSf,allocInfo,1);
   }





   dlSf->bwAlloced += allocInfo->rbsReq;


   return(0);
}
static S16 rgSCHCmnNonDlfsUeRbAlloc
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlSf *dlSf,
U8 *isDlBwAvail
)







{
   U32 y;
   RgSchDlRbAlloc *allocInfo;
   RgSchCmnDlUe *dlUe;
   ;;

   dlUe = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   *isDlBwAvail = 1;
   if (rgSCHCmnNonDlfsBwAvlbl(cell, dlSf, allocInfo) != 1)
   {
      if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0054,L_DEBUG,DBG_CELLID, cell->cellId, ue->ueId, 0, 0, 0,                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                  25771      , "FAILED for CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                   ;
      *isDlBwAvail = 0;
      return(1);
   }



   y = rgSCHUtlGetY(ue, dlSf->sfNum);
   if (dlUe->proc->tbInfo[0].isAckNackDtx == 4
       || dlUe->proc->tbInfo[1].isAckNackDtx)
   {
      allocInfo->pdcch = rgSCHCmnPdcchAlloc(cell, ue, dlSf, y, dlUe->mimoInfo.cwInfo[0].cqi, allocInfo->dciFormat, 1);
   }
   else
   {
      allocInfo->pdcch = rgSCHCmnPdcchAlloc(cell, ue, dlSf, y, dlUe->mimoInfo.cwInfo[0].cqi, allocInfo->dciFormat,0);
   }
   if (!(allocInfo->pdcch))
   {


      return(1);
   }

   allocInfo->rnti = ue->ueId;





   if (allocInfo->raType == 2)
   {
      allocInfo->allocInfo.raType2.isLocal = 1;
      allocInfo->allocInfo.raType2.rbStart = (U8)dlSf->type2Start;
      allocInfo->allocInfo.raType2.numRb = allocInfo->rbsReq;



      if ((cell->lteAdvCb.dsfrCfg.status == RGR_ENABLE) && (cell->lteAdvCb.sfrCfg.status == RGR_ENABLE))
      {
         rgSCHCmnNonDlfsUpdDSFRTyp2Alloc(cell, ue, dlSf,
               allocInfo->allocInfo.raType2.rbStart,
               allocInfo->allocInfo.raType2.numRb);
      }
      else

      {
         rgSCHCmnNonDlfsUpdTyp2Alloc(cell, dlSf,
               allocInfo->allocInfo.raType2.rbStart,
               allocInfo->allocInfo.raType2.numRb);
      }

      allocInfo->rbsAlloc = allocInfo->rbsReq;
      allocInfo->tbInfo[0].bytesAlloc = allocInfo->tbInfo[0].bytesReq;
   }
   else if (allocInfo->raType == 0)
   {
      rgSCHCmnNonDlfsType0Alloc(cell, dlSf, allocInfo, ue);
   }


   rgSCHCmnFindCodeRate(cell,dlSf,allocInfo,0);
   if(allocInfo->tbInfo[1].schdlngForTb == 1)
   {
      rgSCHCmnFindCodeRate(cell,dlSf,allocInfo,1);
   }







   dlUe->prbAlloc += allocInfo->rbsAlloc;
   if (allocInfo->tbInfo[0].tbCb->txCntr)
   {
      dlUe->schedRetxOccns++;
   }
   else
   {
      dlUe->schedOccns++;
   }
   dlUe->prbAlloc += allocInfo->rbsAlloc;


   return(0);
}
static Void rgSCHCmnNonDlfsCcchSduAlloc
(
RgSchCellCb *cell,
RgSchCmnCcchSduRbAlloc *allocInfo,
U8 isRetx
)






{
   S16 ret;
   CmLListCp *ccchSduLst = 0L;
   CmLListCp *schdCcchSduLst = 0L;
   CmLListCp *nonSchdCcchSduLst = 0L;
   CmLList *schdLnkNode = 0L;
   CmLList *toBeSchdLnk = 0L;
   RgSchDlSf *dlSf = allocInfo->ccchSduDlSf;
   RgSchUeCb *ueCb = 0L;
   RgSchDlHqProcCb *hqP = 0L;
   ;;

   if (isRetx)
   {

      ccchSduLst = &(allocInfo->ccchSduRetxLst);
      schdCcchSduLst = &(allocInfo->schdCcchSduRetxLst);
      nonSchdCcchSduLst = &(allocInfo->nonSchdCcchSduRetxLst);
   }
   else
   {

      ccchSduLst = &(allocInfo->ccchSduTxLst);
      schdCcchSduLst = &(allocInfo->schdCcchSduTxLst);
      nonSchdCcchSduLst = &(allocInfo->nonSchdCcchSduTxLst);
   }


   toBeSchdLnk = ((ccchSduLst)->crnt = (ccchSduLst)->first);
   for (; toBeSchdLnk; toBeSchdLnk = toBeSchdLnk->next)
   {
      hqP = (RgSchDlHqProcCb *)(toBeSchdLnk->node);
      ueCb = hqP->hqE->ue;
      schdLnkNode = &hqP->schdLstLnk;
      { (schdLnkNode)->node = (U32)hqP; (schdLnkNode)->prev = 0L; (schdLnkNode)->next = 0L;};
      ret = rgSCHCmnNonDlfsCcchSduRbAlloc(cell, ueCb, dlSf);
      if (ret != 0)
      {


         do
         {
            hqP = (RgSchDlHqProcCb *)(toBeSchdLnk->node);
            ueCb = hqP->hqE->ue;
            schdLnkNode = &hqP->schdLstLnk;
            { (schdLnkNode)->node = (U32)hqP; (schdLnkNode)->prev = 0L; (schdLnkNode)->next = 0L;};
            cmLListAdd2Tail(nonSchdCcchSduLst, schdLnkNode);
            toBeSchdLnk = toBeSchdLnk->next;
         } while(toBeSchdLnk);
         return;
      }


      cmLListAdd2Tail(schdCcchSduLst, schdLnkNode);
   }


   return;
}
static S16 rgSCHCmnNonDlfsCcchSduRbAlloc
(
RgSchCellCb *cell,
RgSchUeCb *ueCb,
RgSchDlSf *dlSf
)






{
   U32 y;
   RgSchDlRbAlloc *allocInfo;
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ueCb->cellInfo[ueCb->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   ;;


   allocInfo = &(((ueCb)->cellInfo[(ueCb)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;




   if ((dlSf->spsAllocdBw >= cell->spsBwRbgInfo.numRbs) &&
         (dlSf->bwAlloced == dlSf->bw))




   {
      return(1);
   }

   y = ueCb->y[dlSf->sfNum];

   if (ueDl->proc->tbInfo[0].isAckNackDtx == 4)
   {


      allocInfo->pdcch = rgSCHCmnPdcchAlloc(cell, ueCb, dlSf, y, ueDl->mimoInfo.cwInfo[0].cqi, TFU_DCI_FORMAT_1A, 1);
   }
   else
   {
      allocInfo->pdcch = rgSCHCmnPdcchAlloc(cell, ueCb, dlSf, y, ueDl->mimoInfo.cwInfo[0].cqi, TFU_DCI_FORMAT_1A, 0);
   }
   if (!(allocInfo->pdcch))
   {

      return(1);
   }


   allocInfo->dciFormat = TFU_DCI_FORMAT_1A;
   allocInfo->raType = 2;
   allocInfo->allocInfo.raType2.isLocal = 1;



      allocInfo->allocInfo.raType2.rbStart = (U8)dlSf->type2Start;
      allocInfo->allocInfo.raType2.numRb = allocInfo->rbsReq;
      allocInfo->rbsAlloc = allocInfo->rbsReq;
      allocInfo->tbInfo[0].bytesAlloc = allocInfo->tbInfo[0].bytesReq;




      if (cell->lteAdvCb.sfrCfg.status == RGR_ENABLE)
      {
         rgSCHCmnNonDlfsSFRCmnChannelUpdTyp2Alloc(cell, dlSf,
               allocInfo->allocInfo.raType2.rbStart,
               allocInfo->allocInfo.raType2.numRb);
      }
      else

      {
         rgSCHCmnNonDlfsUpdTyp2Alloc(cell, dlSf,
               allocInfo->allocInfo.raType2.rbStart,
               allocInfo->allocInfo.raType2.numRb);
      }





   return(0);
}
static S16 rgSCHCmnNonDlfsMsg4RbAlloc
(
RgSchCellCb *cell,
RgSchRaCb *raCb,
RgSchDlSf *dlSf
)






{
   U32 y;
   RgSchDlRbAlloc *allocInfo;
   ;;


   allocInfo = &((raCb)->rbAllocInfo);;


   if ((dlSf->spsAllocdBw >= cell->spsBwRbgInfo.numRbs) &&
         (dlSf->bwAlloced == dlSf->bw))




   {

      return(1);
   }


   y = raCb->y[dlSf->sfNum];

   if (raCb->dlHqE->msg4Proc->tbInfo[0].isAckNackDtx == 4)
   {
      allocInfo->pdcch = rgSCHCmnPdcchAlloc(cell, raCb->ue, dlSf, y, raCb->ccchCqi, TFU_DCI_FORMAT_1A, 1);
   }
   else
   {
      allocInfo->pdcch = rgSCHCmnPdcchAlloc(cell, raCb->ue, dlSf, y, raCb->ccchCqi, TFU_DCI_FORMAT_1A, 0);
   }
   if (!(allocInfo->pdcch))
   {

      return(1);
   }


   allocInfo->pdcch->dci.u.format1aInfo.t.pdschInfo.isTBMsg4 = 1;


   allocInfo->dciFormat = TFU_DCI_FORMAT_1A;
   allocInfo->raType = 2;
   allocInfo->allocInfo.raType2.isLocal = 1;



        allocInfo->allocInfo.raType2.rbStart = (U8)dlSf->type2Start;
        allocInfo->allocInfo.raType2.numRb = allocInfo->rbsReq;


        if (cell->lteAdvCb.sfrCfg.status == RGR_ENABLE)
        {
           rgSCHCmnNonDlfsSFRCmnChannelUpdTyp2Alloc(cell, dlSf,
                 allocInfo->allocInfo.raType2.rbStart,
                 allocInfo->allocInfo.raType2.numRb);
        }
        else

        {
           rgSCHCmnNonDlfsUpdTyp2Alloc(cell, dlSf,
                 allocInfo->allocInfo.raType2.rbStart,
                 allocInfo->allocInfo.raType2.numRb);
        }



   allocInfo->rbsAlloc = allocInfo->rbsReq;
   allocInfo->tbInfo[0].bytesAlloc = allocInfo->tbInfo[0].bytesReq;




   return(0);
}
static Void rgSCHCmnNonDlfsMsg4Alloc
(
RgSchCellCb *cell,
RgSchCmnMsg4RbAlloc *allocInfo,
U8 isRetx
)






{
   S16 ret;
   CmLListCp *msg4Lst = 0L;
   CmLListCp *schdMsg4Lst = 0L;
   CmLListCp *nonSchdMsg4Lst = 0L;
   CmLList *schdLnkNode = 0L;
   CmLList *toBeSchdLnk = 0L;
   RgSchDlSf *dlSf = allocInfo->msg4DlSf;
   RgSchRaCb *raCb = 0L;
   RgSchDlHqProcCb *hqP = 0L;
   ;;

   if (isRetx)
   {

      msg4Lst = &(allocInfo->msg4RetxLst);
      schdMsg4Lst = &(allocInfo->schdMsg4RetxLst);
      nonSchdMsg4Lst = &(allocInfo->nonSchdMsg4RetxLst);
   }
   else
   {

      msg4Lst = &(allocInfo->msg4TxLst);
      schdMsg4Lst = &(allocInfo->schdMsg4TxLst);
      nonSchdMsg4Lst = &(allocInfo->nonSchdMsg4TxLst);
   }


   toBeSchdLnk = ((msg4Lst)->crnt = (msg4Lst)->first);
   for (; toBeSchdLnk; toBeSchdLnk = toBeSchdLnk->next)
   {
      hqP = (RgSchDlHqProcCb *)(toBeSchdLnk->node);
      raCb = hqP->hqE->raCb;
      schdLnkNode = &hqP->schdLstLnk;
      { (schdLnkNode)->node = (U32)hqP; (schdLnkNode)->prev = 0L; (schdLnkNode)->next = 0L;};
      ret = rgSCHCmnNonDlfsMsg4RbAlloc(cell, raCb, dlSf);
      if (ret != 0)
      {


         do
         {
            hqP = (RgSchDlHqProcCb *)(toBeSchdLnk->node);
            raCb = hqP->hqE->raCb;
            schdLnkNode = &hqP->schdLstLnk;
            { (schdLnkNode)->node = (U32)hqP; (schdLnkNode)->prev = 0L; (schdLnkNode)->next = 0L;};
            cmLListAdd2Tail(nonSchdMsg4Lst, schdLnkNode);
            toBeSchdLnk = toBeSchdLnk->next;
         } while(toBeSchdLnk);
         return;
      }


      cmLListAdd2Tail(schdMsg4Lst, schdLnkNode);
      if (isRetx)
      {
      }
   }


   return;
}
static Void rgSCHCmnNonDlfsDedRbAlloc
(
RgSchCellCb *cell,
RgSchCmnUeRbAlloc *allocInfo,
CmLListCp *ueLst,
CmLListCp *schdHqPLst,
CmLListCp *nonSchdHqPLst
)
{
   S16 ret;

   CmLList *nonSchdLstPtr = 0L;
   CmLList *prevLstPtr = 0L;
   Bool isSpsBwAvail = 1;

   CmLList *schdLnkNode = 0L;
   CmLList *toBeSchdLnk = 0L;
   RgSchDlRbAlloc *dlAlloc = 0L;
   RgSchDlSf *dlSf = allocInfo->dedDlSf;
   RgSchUeCb *ue = 0L;
   RgSchDlHqProcCb *hqP = 0L;
   U8 isDlBwAvail;
   ;;



   toBeSchdLnk = ((ueLst)->crnt = (ueLst)->first);
   for (; toBeSchdLnk; toBeSchdLnk = toBeSchdLnk->next)
   {
      hqP = (RgSchDlHqProcCb *)(toBeSchdLnk->node);
      ue = hqP->hqE->ue;
      dlAlloc = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
      schdLnkNode = &hqP->schdLstLnk;
      { (schdLnkNode)->node = (U32)hqP; (schdLnkNode)->prev = 0L; (schdLnkNode)->next = 0L;};


      if ((cell->lteAdvCb.sfrCfg.status == RGR_ENABLE) && (1 == dlSf->sfrTotalPoolInfo.isUeCellEdge))
      {
         ret = rgSCHCmnSFRNonDlfsUeRbAlloc(cell, ue, dlSf, &isDlBwAvail);
      }
      else


      ret = rgSCHCmnNonDlfsUeRbAlloc(cell, ue, dlSf, &isDlBwAvail);
      if (!isDlBwAvail)
      {


         do
         {
            hqP = (RgSchDlHqProcCb *)(toBeSchdLnk->node);
            ue = hqP->hqE->ue;
            dlAlloc = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
            schdLnkNode = &hqP->schdLstLnk;
            { (schdLnkNode)->node = (U32)hqP; (schdLnkNode)->prev = 0L; (schdLnkNode)->next = 0L;};
            cmLListAdd2Tail(nonSchdHqPLst, schdLnkNode);
            toBeSchdLnk = toBeSchdLnk->next;
         } while(toBeSchdLnk);
         break;
      }

      if (ret == 0)
      {

         cmLListAdd2Tail(schdHqPLst, schdLnkNode);
         {
            if (ueLst == &allocInfo->retxHqPLst)
            {
               static U32 retxCnt = 0;
               ++retxCnt;
               if ((cell->crntTime.sfn % 10 == 0)&& (cell->crntTime.subframe == 0))
               {
               }
            }
         }
      }
      else
      {

         cmLListAdd2Tail(nonSchdHqPLst, schdLnkNode);
      }
   }


   if (!((ueLst == &allocInfo->retxHqPLst) ||
         (ueLst == &allocInfo->retxSpsHqPLst) ||
         (ueLst == &allocInfo->txRetxHqPLst)))
   {

      nonSchdLstPtr = ((nonSchdHqPLst)->crnt = (nonSchdHqPLst)->first);
      while (isSpsBwAvail && nonSchdLstPtr)
      {
         hqP = (RgSchDlHqProcCb *)(nonSchdLstPtr->node);
         ue = hqP->hqE->ue;
         dlAlloc = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
         if (dlAlloc->rbsAlloc)
         {

            prevLstPtr = nonSchdLstPtr;
            nonSchdLstPtr = nonSchdLstPtr->next;
            continue;
         }

         isSpsBwAvail =
                  rgSCHCmnAllocUeInSpsBw(dlSf, cell, ue, dlAlloc, 1);

         if (!isSpsBwAvail)
         {
            break;
         }
         prevLstPtr = nonSchdLstPtr;
         nonSchdLstPtr = nonSchdLstPtr->next;
         if (dlAlloc->rbsAlloc)
         {

            cmLListDelFrm(nonSchdHqPLst, prevLstPtr);

            cmLListAdd2Tail(schdHqPLst, prevLstPtr);

         }
      }
   }


   return;
}
 Void rgSCHCmnNonDlfsRbAlloc
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   U8 raRspCnt = 0;
   RgSchDlRbAlloc *reqAllocInfo;
   ;;


   if (allocInfo->msg4Alloc.msg4RetxLst.count)
   {
      rgSCHCmnNonDlfsMsg4Alloc(cell, &(allocInfo->msg4Alloc), 1);
   }



   if (allocInfo->msg4Alloc.msg4TxLst.count)
   {
      rgSCHCmnNonDlfsMsg4Alloc(cell, &(allocInfo->msg4Alloc), 0);
   }



   if (allocInfo->ccchSduAlloc.ccchSduRetxLst.count)
   {
      rgSCHCmnNonDlfsCcchSduAlloc(cell, &(allocInfo->ccchSduAlloc), 1);
   }



   if (allocInfo->ccchSduAlloc.ccchSduTxLst.count)
   {
      rgSCHCmnNonDlfsCcchSduAlloc(cell, &(allocInfo->ccchSduAlloc), 0);
   }



   for (raRspCnt = 0; raRspCnt < 4; ++raRspCnt)
   {

      reqAllocInfo = &(allocInfo->raRspAlloc[raRspCnt]);
      if (!reqAllocInfo->rbsReq)
      {
         break;
      }
      if ((rgSCHCmnNonDlfsCmnRbAlloc(cell, reqAllocInfo)) != 0)
      {
         break;
      }
   }







   if((allocInfo->dedAlloc.retxSpsHqPLst.count))
   {
      rgSCHCmnNonDlfsDedRbAlloc(cell, &(allocInfo->dedAlloc),
            &(allocInfo->dedAlloc.retxSpsHqPLst),
            &(allocInfo->dedAlloc.schdRetxSpsHqPLst),
            &(allocInfo->dedAlloc.nonSchdRetxSpsHqPLst));
   }

   if((allocInfo->dedAlloc.txSpsHqPLst.count))
   {
      rgSCHCmnNonDlfsDedRbAlloc(cell, &(allocInfo->dedAlloc),
            &(allocInfo->dedAlloc.txSpsHqPLst),
            &(allocInfo->dedAlloc.schdTxSpsHqPLst),
            &(allocInfo->dedAlloc.nonSchdTxSpsHqPLst));
   }



   if((allocInfo->dedAlloc.errIndTxHqPLst.count))
   {
      rgSCHCmnNonDlfsDedRbAlloc(cell, &(allocInfo->dedAlloc),
            &(allocInfo->dedAlloc.errIndTxHqPLst),
            &(allocInfo->dedAlloc.schdErrIndTxHqPLst),
            &(allocInfo->dedAlloc.nonSchdErrIndTxHqPLst));
   }

   if((allocInfo->dedAlloc.txLaaHqPLst.count))
   {
      rgSCHCmnNonDlfsDedRbAlloc(cell, &(allocInfo->dedAlloc),
            &(allocInfo->dedAlloc.txLaaHqPLst),
            &(allocInfo->dedAlloc.schdTxLaaHqPLst),
            &(allocInfo->dedAlloc.nonSchdTxLaaHqPLst));
   }

   if(allocInfo->dedAlloc.txRetxHqPLst.count)
   {
      rgSCHCmnNonDlfsDedRbAlloc(cell, &(allocInfo->dedAlloc),
            &(allocInfo->dedAlloc.txRetxHqPLst),
            &(allocInfo->dedAlloc.schdTxRetxHqPLst),
            &(allocInfo->dedAlloc.nonSchdTxRetxHqPLst));
   }

   if((allocInfo->dedAlloc.retxHqPLst.count))
   {
      rgSCHCmnNonDlfsDedRbAlloc(cell, &(allocInfo->dedAlloc),
            &(allocInfo->dedAlloc.retxHqPLst),
            &(allocInfo->dedAlloc.schdRetxHqPLst),
            &(allocInfo->dedAlloc.nonSchdRetxHqPLst));
   }


   if((allocInfo->dedAlloc.txHqPLst.count))
   {
      rgSCHCmnNonDlfsDedRbAlloc(cell, &(allocInfo->dedAlloc),
            &(allocInfo->dedAlloc.txHqPLst),
            &(allocInfo->dedAlloc.schdTxHqPLst),
            &(allocInfo->dedAlloc.nonSchdTxHqPLst));
   }
   {
      RgSchCmnCell *cmnCell = ((RgSchCmnCell *)((cell)->sc.sch));
      if ((allocInfo->dedAlloc.txRetxHqPLst.count +
               allocInfo->dedAlloc.retxHqPLst.count +
               allocInfo->dedAlloc.txHqPLst.count) >
            cmnCell->dl.maxUePerDlSf)
      {
         { if ((&rgSchCb[cell->instIdx].rgSchInit)->dbgMask & ((0x00000100 << 1))) { snprintf((&rgSchCb[cell->instIdx].rgSchInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "MAC Scheduler", (&rgSchCb[cell->instIdx].rgSchInit)->procId, (&rgSchCb[cell->instIdx].rgSchInit)->ent, (&rgSchCb[cell->instIdx].rgSchInit)->inst,



                                                     "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"
         ,



                                                     26582
         ); SPrint((&rgSchCb[cell->instIdx].rgSchInit)->prntBuf); sprintf (rgSchCb[cell->instIdx].rgSchInit.prntBuf,"UEs selected by" " scheduler exceed maximumUePerDlSf(%u)tx-retx %ld retx %ld tx %ld\n", cmnCell->dl.maxUePerDlSf, allocInfo->dedAlloc.txRetxHqPLst.count, allocInfo->dedAlloc.retxHqPLst.count, allocInfo->dedAlloc.txHqPLst.count); SPrint((&rgSchCb[cell->instIdx].rgSchInit)->prntBuf); } }



                                                      ;
      }
   }


   if(cell->lteAdvCb.dsfrCfg.status == RGR_ENABLE)
   {
      rgSCHCmnNonDlfsDsfrRntpComp(cell, allocInfo->dedAlloc.dedDlSf);
   }


   return;
}
 U32 rgSCHCmnCalcRiv
(
U8 bw,
U8 rbStart,
U8 numRb
)
{
   U8 numRbMinus1 = numRb - 1;
   U32 riv;

   ;;

   if (numRbMinus1 <= bw/2)
   {
      riv = bw * numRbMinus1 + rbStart;
   }
   else
   {
      riv = bw * (bw - numRbMinus1) + (bw - rbStart - 1);
   }
   return(riv);
}
static S32 rgSchCmnFetchItbs
(
RgSchCellCb *cell,
RgSchCmnDlUe *ueDl,
U8 cqi,
U8 cfi,
U8 cwIdx,
U8 noLyr
)
{

   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   S32 iTbs = 0;

   ;;
   {
      S32 tmpiTbs = (*(RgSchCmnCqiToTbs *)(cellDl->cqiToTbsTbl[0][cfi]))[cqi];

      iTbs = (ueDl->laCb[cwIdx].deltaiTbs + tmpiTbs*100)/100;

      { if (iTbs < 0) { iTbs = 0; } else if (iTbs > (tmpiTbs)) { iTbs = (tmpiTbs); }};

      iTbs = ((iTbs) <= (cell->thresholds.maxDlItbs) ? (iTbs) : (cell->thresholds.maxDlItbs));

      ueDl->mimoInfo.cwInfo[cwIdx].iTbs[noLyr - 1] = iTbs;

      ueDl->lastCfi = cfi;
      ueDl->laCb[cwIdx].deltaiTbs = 0;
   }

   return(iTbs);
}
static Void rgSCHCmnDlAllocTxRb1Tb1Cw
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   RgSchDlRbAlloc *allocInfo;
   S16 ret;
   U8 numRb;
   ;;

   ret = 0;
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;

   allocInfo->dciFormat = rgSCHCmnSlctPdcchFrmt(cell, ue,
         &allocInfo->raType);
   ret = rgSCHCmnDlAlloc1CwTxRb(cell, subFrm, ue, &proc->tbInfo[0],
         bo, &numRb, effBo);
   if (ret == 1)
   {

      return;
   }


   if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

   {
      rgSCHCmnDlRbInfoAddUeTx(cell, cellWdAllocInfo, ue, proc);
   }

   allocInfo->rbsReq = numRb;
   allocInfo->dlSf = subFrm;

   return;
}
static Void rgSCHCmnDlAllocRetxRb1Tb1Cw
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   RgSchDlRbAlloc *allocInfo;
   S16 ret;
   U8 numRb;
   ;;

   ret = 0;
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;

   allocInfo->dciFormat = rgSCHCmnSlctPdcchFrmt(cell, ue,
         &allocInfo->raType);


   ret = rgSCHCmnDlAlloc1CwRetxRb(cell, subFrm, ue, &proc->tbInfo[0],
         1, &numRb, effBo);
   if (ret == 1)
   {




      rgSCHCmnDlAdd2NonSchdRetxLst(cellWdAllocInfo, ue, proc);
      return;
   }


   if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

   {
      rgSCHCmnDlRbInfoAddUeRetx(cell, cellWdAllocInfo, ue, proc);
   }

   allocInfo->rbsReq = numRb;
   allocInfo->dlSf = subFrm;

   return;
}
static Void rgSCHCmnDlAllocTxRbTM1
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   ;;
   rgSCHCmnDlAllocTxRb1Tb1Cw(cell, subFrm, ue, bo, effBo, proc, cellWdAllocInfo);
   return;
}
static Void rgSCHCmnDlAllocRetxRbTM1
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   ;;
   rgSCHCmnDlAllocRetxRb1Tb1Cw(cell, subFrm, ue, bo, effBo, proc, cellWdAllocInfo);
   return;
}
static Void rgSCHCmnDlAllocTxRbTM2
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   ;;
   rgSCHCmnDlAllocTxRb1Tb1Cw(cell, subFrm, ue, bo, effBo, proc, cellWdAllocInfo);
   return;
}
static Void rgSCHCmnDlAllocRetxRbTM2
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   ;;
   rgSCHCmnDlAllocRetxRb1Tb1Cw(cell, subFrm, ue, bo, effBo, proc, cellWdAllocInfo);
   return;
}
static Void rgSCHCmnDlAllocTxRbTM3
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{

   ;;


   rgSCHCmnDlTM3TxTx(cell, subFrm, ue, bo, effBo,
         proc, cellWdAllocInfo);

   return;
}
static Void rgSCHCmnDlAllocRetxRbTM3
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{

   ;;

   if ((proc->tbInfo[0].state == HQ_TB_NACKED) &&
         (proc->tbInfo[1].state == HQ_TB_NACKED))
   {

      rgSCHCmnDlTM3RetxRetx(cell, subFrm, ue, bo, effBo,
            proc, cellWdAllocInfo);
   }
   else
   {


      rgSCHCmnDlTM3TxRetx(cell, subFrm, ue, bo, effBo,
            proc, cellWdAllocInfo);
   }

   return;
}
static TfuDciFormat rgSCHCmnSlctPdcchFrmt
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 *raType
)






{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;



   if ((cellSch->dl.isDlFreqSel) && (ue->txModeTransCmplt))
   {
      *raType = rgSchCmnDciFrmtOptns[ue->mimoInfo.txMode-1].spfcDciRAType;
      return(rgSchCmnDciFrmtOptns[ue->mimoInfo.txMode-1].spfcDciFrmt);
   }
   else
   {
      *raType = rgSchCmnDciFrmtOptns[ue->mimoInfo.txMode-1].prfrdDciRAType;
      return(rgSchCmnDciFrmtOptns[ue->mimoInfo.txMode-1].prfrdDciFrmt);
   }
}
static Void rgSCHCmnDlTM3RetxRetx
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   S16 ret;
   RgSchDlRbAlloc *allocInfo;
   U8 numRb;
   Bool swpFlg;
   U8 precInfo;
   U8 noTxLyrs;
   U8 precInfoAntIdx;

   ;;

   ret = 0;
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   swpFlg = 0;

   {
      allocInfo->dciFormat = TFU_DCI_FORMAT_2A;
      allocInfo->raType = 0;

      ret = rgSCHCmnDlAlloc2CwRetxRb(cell, subFrm, ue, proc, &numRb, &swpFlg,
            effBo);
      if (ret == 1)
      {

         rgSCHCmnDlAdd2NonSchdRetxLst(cellWdAllocInfo, ue, proc);
         return;
      }

      noTxLyrs = proc->tbInfo[0].numLyrs + proc->tbInfo[1].numLyrs;
      precInfoAntIdx = cell->numTxAntPorts/2 - 1;
      precInfo = (getPrecInfoFunc[0][precInfoAntIdx])(cell, ue, noTxLyrs, 1);
   }


   if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

   {

      rgSCHCmnDlRbInfoAddUeRetx(cell, cellWdAllocInfo, ue, proc);
   }

   { allocInfo->rbsReq = numRb; allocInfo->mimoAllocInfo.swpFlg = swpFlg; allocInfo->mimoAllocInfo.precIdxInfo = precInfo; allocInfo->mimoAllocInfo.numTxLyrs = noTxLyrs; allocInfo->dlSf = subFrm;}
                                    ;

   return;
}
static Void rgSCHCmnDlTM4RetxRetx
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   S16 ret;
   RgSchCmnDlUe *ueDl;
   RgSchDlRbAlloc *allocInfo;
   U8 numRb;
   Bool swpFlg = 0;
   U8 precInfo;

   U8 noTxLyrs;

   ;;

   ret = 0;
   ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;


   allocInfo->dciFormat = TFU_DCI_FORMAT_2;
   allocInfo->raType = 0;

   ret = rgSCHCmnDlAlloc2CwRetxRb(cell, subFrm, ue, proc, &numRb, &swpFlg,
         effBo);
   if (ret == 1)
   {

      rgSCHCmnDlAdd2NonSchdRetxLst(cellWdAllocInfo, ue, proc);
      return;
   }
   noTxLyrs = proc->tbInfo[0].numLyrs + proc->tbInfo[1].numLyrs;
   precInfo = 0;

   if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

   {

      rgSCHCmnDlRbInfoAddUeRetx(cell, cellWdAllocInfo, ue, proc);
   }

   { allocInfo->rbsReq = numRb; allocInfo->mimoAllocInfo.swpFlg = swpFlg; allocInfo->mimoAllocInfo.precIdxInfo = precInfo; allocInfo->mimoAllocInfo.numTxLyrs = noTxLyrs; allocInfo->dlSf = subFrm;}
                                    ;

   return;
}
static Void rgSCHCmnDlSMGetAttrForTxRetx
(
RgSchUeCb *ue,
RgSchDlHqProcCb *proc,
RgSchDlHqTbCb **retxTb,
RgSchDlHqTbCb **txTb,
Bool *frthrScp,
Bool *swpFlg
)
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((proc->hqE->cell->cellId >= rgSchCb[proc->hqE->cell->instIdx].genCfg.startCellId) ? (proc->hqE->cell->cellId - rgSchCb[proc->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   RgSchDlRbAlloc *allocInfo;

   ;;

   if (proc->tbInfo[0].state == HQ_TB_NACKED)
   {
      *retxTb = &proc->tbInfo[0];
      *txTb = &proc->tbInfo[1];


      if ((ue->mimoInfo.txMode == RGR_UE_TM_4) && (ueDl->mimoInfo.btrCwIdx == 1))
      {
         *swpFlg = 1;
         proc->cwSwpEnabled = 1;
      }
      if (proc->tbInfo[1].state == HQ_TB_ACKED)
      {
         allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((proc->hqE->cell->cellId >= rgSchCb[proc->hqE->cell->instIdx].genCfg.startCellId) ? (proc->hqE->cell->cellId - rgSchCb[proc->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
         *frthrScp = allocInfo->mimoAllocInfo.hasNewTxData;
      }
   }
   else
   {
      *retxTb = &proc->tbInfo[1];
      *txTb = &proc->tbInfo[0];


      if ((ue->mimoInfo.txMode == RGR_UE_TM_4) && (ueDl->mimoInfo.btrCwIdx == 0))
      {
         *swpFlg = 1;
         proc->cwSwpEnabled = 1;
      }
      if (proc->tbInfo[0].state == HQ_TB_ACKED)
      {
         allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((proc->hqE->cell->cellId >= rgSchCb[proc->hqE->cell->instIdx].genCfg.startCellId) ? (proc->hqE->cell->cellId - rgSchCb[proc->hqE->cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
         *frthrScp = allocInfo->mimoAllocInfo.hasNewTxData;
      }
   }
   return;
}
static U8 rgSCHCmnDlTM3PrecInf2
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 numTxLyrs,
Bool bothCwEnbld
)







{
   ;;

   return(0);
}
static U8 rgSCHCmnDlTM4PrecInf2
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 numTxLyrs,
Bool bothCwEnbld
)







{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U8 precIdx;

   ;;

   if (ueDl->mimoInfo.ri == numTxLyrs)
   {
      if (ueDl->mimoInfo.ri == 2)
      {


         if (ue->mimoInfo.puschFdbkVld)
         {
            precIdx = 2;
         }
         else
         {
            precIdx = ueDl->mimoInfo.pmi - 1;
         }
      }
      else
      {


         if (ue->mimoInfo.puschFdbkVld)
         {
            precIdx = 5;
         }
         else
         {
            precIdx = ueDl->mimoInfo.pmi + 1;
         }
      }
   }
   else if (ueDl->mimoInfo.ri > numTxLyrs)
   {



      if (ue->mimoInfo.puschFdbkVld)
      {
         precIdx = 5;
      }
      else
      {
         precIdx = (ueDl->mimoInfo.pmi- 1)* 2 + 1;
      }
   }
   else
   {
      precIdx = (ueDl->mimoInfo.pmi < 2)? 0:1;
   }
   return(precIdx);
}
static U8 rgSCHCmnDlTM3PrecInf4
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 numTxLyrs,
Bool bothCwEnbld
)







{
   U8 precIdx;

   ;;

   if (bothCwEnbld)
   {
      precIdx = numTxLyrs - 2;
   }
   else
   {
      precIdx = 1;
   }
   return(precIdx);
}
static U8 rgSCHCmnDlTM4PrecInf4
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 numTxLyrs,
Bool bothCwEnbld
)







{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U8 precInfoBaseIdx, precIdx;

   ;;

   precInfoBaseIdx = (ue->mimoInfo.puschFdbkVld)? (16):
      (ueDl->mimoInfo.pmi);
   if (bothCwEnbld)
   {
      precIdx = precInfoBaseIdx + (numTxLyrs-2)*17;
   }
   else
   {
      precInfoBaseIdx += 1;
      precIdx = precInfoBaseIdx + (numTxLyrs-1)*17;
   }
   return(precIdx);
}
static Void rgSCHCmnDlGetAttrForTM3
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlHqProcCb *proc,
U8 *numTxLyrs,
TfuDciFormat *dciFrmt,
U8 *prcdngInf,
RgSchDlHqTbCb **retxTb,
RgSchDlHqTbCb **txTb,
Bool *frthrScp,
Bool *swpFlg,
U8 *raType
)
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U8 precInfoAntIdx;

   ;;



   if (((((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd)) ||
         (ueDl->mimoInfo.forceTD))



   {


      if (proc->tbInfo[0].state == HQ_TB_NACKED)
      {
         *retxTb = &proc->tbInfo[0];
         *dciFrmt = rgSCHCmnSlctPdcchFrmt(cell, ue, raType);
      }
      else
      {
         *retxTb = &proc->tbInfo[1];
         *dciFrmt = TFU_DCI_FORMAT_2A;
         *raType = 0;
      }
      *numTxLyrs = 1;
      *frthrScp = 0;
      *prcdngInf = 0;
      return;
   }


   rgSCHCmnDlSMGetAttrForTxRetx(ue, proc, retxTb, txTb,
         frthrScp, swpFlg);
   if (*frthrScp)
   {


      if ((ueDl->mimoInfo.ri == 2)
            && ((*retxTb)->numLyrs == 2) && (cell->numTxAntPorts == 4))
      {


         *numTxLyrs = 2;
         *frthrScp = 0;
      }
      precInfoAntIdx = cell->numTxAntPorts/2 - 1;
      *prcdngInf = (getPrecInfoFunc[0][precInfoAntIdx])
                   (cell, ue, ueDl->mimoInfo.ri, *frthrScp);
      *dciFrmt = TFU_DCI_FORMAT_2A;
      *raType = 0;
   }
   else
   {
      if (cell->numTxAntPorts == 2)
      {

         *numTxLyrs = 1;
         if ((*retxTb)->tbIdx == 0)
         {
            *dciFrmt = rgSCHCmnSlctPdcchFrmt(cell, ue, raType);
         }
         else
         {

            *dciFrmt = TFU_DCI_FORMAT_2A;
            *raType = 0;
         }
         *prcdngInf = 0;
         return;
      }
      else
      {
         if ((*retxTb)->numLyrs == 2)
         {


            *numTxLyrs = 2;
            *dciFrmt = TFU_DCI_FORMAT_2A;
            *raType = 0;
            precInfoAntIdx = cell->numTxAntPorts/2 - 1;
            *prcdngInf = (getPrecInfoFunc[0][precInfoAntIdx])(cell, ue, *numTxLyrs, *frthrScp);
            return;
         }
         else
         {

            *numTxLyrs = 1;
            if ((*retxTb)->tbIdx == 0)
            {
               *dciFrmt = rgSCHCmnSlctPdcchFrmt(cell, ue, raType);
            }
            else
            {

               *dciFrmt = TFU_DCI_FORMAT_2A;
               *raType = 0;
            }
            *prcdngInf = 0;
            return;
         }
      }
   }

   return;
}
static Void rgSCHCmnDlGetAttrForTM4
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgSchDlHqProcCb *proc,
U8 *numTxLyrs,
TfuDciFormat *dciFrmt,
U8 *prcdngInf,
RgSchDlHqTbCb **retxTb,
RgSchDlHqTbCb **txTb,
Bool *frthrScp,
Bool *swpFlg,
U8 *raType
)
{
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   U8 precInfoAntIdx;

   ;;

   *frthrScp = 0;


   if (((((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd)) ||
         (ueDl->mimoInfo.forceTD))



   {


      if (proc->tbInfo[0].state == HQ_TB_NACKED)
      {
         *retxTb = &proc->tbInfo[0];
         *dciFrmt = rgSCHCmnSlctPdcchFrmt(cell, ue, raType);
      }
      else
      {
         *retxTb = &proc->tbInfo[1];
         *dciFrmt = TFU_DCI_FORMAT_2;
         *raType = 0;
      }
      *numTxLyrs = 1;
      *frthrScp = 0;
      *prcdngInf = 0;
      return;
   }

   if (ueDl->mimoInfo.ri == 1)
   {


      if (proc->tbInfo[0].state == HQ_TB_NACKED)
      {
         *retxTb = &proc->tbInfo[0];
      }
      else
      {
         *retxTb = &proc->tbInfo[1];
      }
      *numTxLyrs = 1;
      *dciFrmt = TFU_DCI_FORMAT_2;
      *raType = 0;
      *frthrScp = 0;
      *prcdngInf = 0;
      return;
   }


   rgSCHCmnDlSMGetAttrForTxRetx(ue, proc, retxTb, txTb,
         frthrScp, swpFlg);
   *dciFrmt = TFU_DCI_FORMAT_2;
   *raType = 0;
   if (*frthrScp)
   {


      if ((ueDl->mimoInfo.ri == 2)
            && ((*retxTb)->numLyrs == 2) && (cell->numTxAntPorts == 4))
      {


         *numTxLyrs = 2;
         *frthrScp = 0;
      }
      precInfoAntIdx = cell->numTxAntPorts/2 - 1;
      *prcdngInf = (getPrecInfoFunc[1][precInfoAntIdx])
                   (cell, ue, ueDl->mimoInfo.ri, *frthrScp);
   }
   else
   {
      if (cell->numTxAntPorts == 2)
      {

         *numTxLyrs = 1;
         *prcdngInf = (getPrecInfoFunc[1][cell->numTxAntPorts/2 - 1])
                      (cell, ue, *numTxLyrs, *frthrScp);
         return;
      }
      else
      {
         if ((*retxTb)->numLyrs == 2)
         {


            *numTxLyrs = 2;
            precInfoAntIdx = cell->numTxAntPorts/2 - 1;
            *prcdngInf = (getPrecInfoFunc[1][precInfoAntIdx])
                         (cell, ue, *numTxLyrs, *frthrScp);
            return;
         }
         else
         {


            *numTxLyrs = 1;
            precInfoAntIdx = cell->numTxAntPorts/2 - 1;
            *prcdngInf = (getPrecInfoFunc[1][precInfoAntIdx])
                         (cell, ue, *numTxLyrs, *frthrScp);
            return;
         }
      }
   }

   return;
}
static Void rgSCHCmnDlTM3TxRetx
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   S16 ret;
   RgSchDlRbAlloc *allocInfo;
   U8 numRb;
   RgSchDlHqTbCb *retxTb, *txTb;
   Bool frthrScp;
   Bool swpFlg;
   U8 prcdngInf;
   U8 numTxLyrs;

   ;;
   frthrScp = 0;

   ret = 0;
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   swpFlg = 0;


   rgSCHCmnDlGetAttrForTM3(cell, ue, proc, &numTxLyrs, &allocInfo->dciFormat,
         &prcdngInf, &retxTb, &txTb, &frthrScp, &swpFlg,
         &allocInfo->raType);
   if (frthrScp)
   {
      ret = rgSCHCmnDlAlloc2CwTxRetxRb(cell, subFrm, ue, retxTb, txTb,
            &numRb, effBo);
      if (ret == 1)
      {

         rgSCHCmnDlAdd2NonSchdRetxLst(cellWdAllocInfo, ue, proc);
         return;
      }

      rgSCHCmnDlRbInfoAddUeRetxTx(cell, cellWdAllocInfo, ue, proc);
   }
   else
   {
      ret = rgSCHCmnDlAlloc1CwRetxRb(cell, subFrm, ue, retxTb,
            numTxLyrs, &numRb, effBo);
      if (ret == 1)
      {

         rgSCHCmnDlAdd2NonSchdRetxLst(cellWdAllocInfo, ue, proc);
         return;
      }

      if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

      {

         rgSCHCmnDlRbInfoAddUeRetx(cell, cellWdAllocInfo, ue, proc);
      }
   }
   { allocInfo->rbsReq = numRb; allocInfo->mimoAllocInfo.swpFlg = swpFlg; allocInfo->mimoAllocInfo.precIdxInfo = prcdngInf; allocInfo->mimoAllocInfo.numTxLyrs = numTxLyrs; allocInfo->dlSf = subFrm;}
                                      ;

   return;
}
static Void rgSCHCmnDlTM4TxRetx
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   S16 ret;
   RgSchDlRbAlloc *allocInfo;
   U8 numRb;
   RgSchDlHqTbCb *retxTb, *txTb;
   Bool frthrScp;
   Bool swpFlg;
   U8 prcdngInf;
   U8 numTxLyrs;

   ;;

   ret = 0;
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   swpFlg = 0;


   rgSCHCmnDlGetAttrForTM4(cell, ue, proc, &numTxLyrs, &allocInfo->dciFormat,
         &prcdngInf, &retxTb, &txTb, &frthrScp, &swpFlg,
         &allocInfo->raType);
   if (frthrScp)
   {
      ret = rgSCHCmnDlAlloc2CwTxRetxRb(cell, subFrm, ue, retxTb, txTb,
            &numRb, effBo);
      if (ret == 1)
      {



         rgSCHCmnDlAdd2NonSchdRetxLst(cellWdAllocInfo, ue, proc);
         return;
      }

      rgSCHCmnDlRbInfoAddUeRetxTx(cell, cellWdAllocInfo, ue, proc);
   }
   else
   {
      ret = rgSCHCmnDlAlloc1CwRetxRb(cell, subFrm, ue, retxTb,
            numTxLyrs, &numRb, effBo);
      if (ret == 1)
      {

         rgSCHCmnDlAdd2NonSchdRetxLst(cellWdAllocInfo, ue, proc);
         return;
      }

      if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

      {

         rgSCHCmnDlRbInfoAddUeRetx(cell, cellWdAllocInfo, ue, proc);
      }
   }
   { allocInfo->rbsReq = numRb; allocInfo->mimoAllocInfo.swpFlg = swpFlg; allocInfo->mimoAllocInfo.precIdxInfo = prcdngInf; allocInfo->mimoAllocInfo.numTxLyrs = numTxLyrs; allocInfo->dlSf = subFrm;}


      return;
}
static Void rgSCHCmnDlTM3TxTx
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   RgSchCmnDlUe *ueDl;
   RgSchDlRbAlloc *allocInfo;
   U8 numRb;
   U8 noTxLyrs;
   U8 precInfo;
   S16 ret;
   U8 precInfoAntIdx;

   ;;

   ret = 0;
   ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;



   if (((((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd)) ||
         (ueDl->mimoInfo.forceTD))



   {
      allocInfo->dciFormat = rgSCHCmnSlctPdcchFrmt(cell, ue,
            &allocInfo->raType);
      ret = rgSCHCmnDlAlloc1CwTxRb(cell, subFrm, ue, &proc->tbInfo[0],
            bo, &numRb, effBo);
      if (ret == 1)
      {

         return;
      }
      noTxLyrs = 1;
      precInfo = 0;
   }
   else
   {
      allocInfo->dciFormat = TFU_DCI_FORMAT_2A;
      allocInfo->raType = 0;


      ret = rgSCHCmnDlAlloc2CwTxRb(cell, subFrm, ue, proc, bo, &numRb, effBo);
      if (ret == 1)
      {

         return;
      }
      noTxLyrs = ueDl->mimoInfo.ri;
      precInfoAntIdx = cell->numTxAntPorts/2 - 1;
      ;
      precInfo = (getPrecInfoFunc[0][precInfoAntIdx])(cell, ue, noTxLyrs, 1);
   }


   if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

   {

      rgSCHCmnDlRbInfoAddUeTx(cell, cellWdAllocInfo, ue, proc);
   }

   { allocInfo->rbsReq = numRb; allocInfo->mimoAllocInfo.swpFlg = 0; allocInfo->mimoAllocInfo.precIdxInfo = precInfo; allocInfo->mimoAllocInfo.numTxLyrs = noTxLyrs; allocInfo->dlSf = subFrm;}
                                    ;

   return;
}
static Void rgSCHCmnDlTM4TxTx
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   RgSchCmnDlUe *ueDl;
   RgSchDlRbAlloc *allocInfo;
   U8 numRb;
   U8 precInfo;
   U8 noTxLyrs;
   U8 precInfoAntIdx;
   S16 ret;

   ;;

   ret = 0;
   ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;



   if (((((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd)) ||
         (ueDl->mimoInfo.forceTD))



   {
      allocInfo->dciFormat = rgSCHCmnSlctPdcchFrmt(cell, ue,
            &allocInfo->raType);

      ret = rgSCHCmnDlAlloc1CwTxRb(cell, subFrm, ue, &proc->tbInfo[0],
            bo, &numRb, effBo);
      if (ret == 1)
      {

         return;
      }
      noTxLyrs = 1;
      precInfo = 0;
   }
   else
   {
      allocInfo->dciFormat = TFU_DCI_FORMAT_2;
      allocInfo->raType = 0;

      if (ueDl->mimoInfo.ri == 1)
      {

         ret = rgSCHCmnDlAlloc1CwTxRb(cell, subFrm, ue, &proc->tbInfo[0],
               bo, &numRb, effBo);
         if (ret == 1)
         {

            return;
         }
         noTxLyrs = 1;
         precInfo = 0;
      }
      else
      {

         ret = rgSCHCmnDlAlloc2CwTxRb(cell, subFrm, ue, proc, bo, &numRb, effBo);
         if (ret == 1)
         {

            return;
         }
         noTxLyrs = ueDl->mimoInfo.ri;
         precInfoAntIdx = cell->numTxAntPorts/2 - 1;
         precInfo = (getPrecInfoFunc[1][precInfoAntIdx])(cell, ue, noTxLyrs, 1);
      }
   }



   if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

   {

      rgSCHCmnDlRbInfoAddUeTx(cell, cellWdAllocInfo, ue, proc);
   }


   { allocInfo->rbsReq = numRb; allocInfo->mimoAllocInfo.swpFlg = 0; allocInfo->mimoAllocInfo.precIdxInfo = precInfo; allocInfo->mimoAllocInfo.numTxLyrs = noTxLyrs; allocInfo->dlSf = subFrm;}
                                    ;

   return;
}
static Void rgSCHCmnDlAllocTxRbTM4
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   ;;


   rgSCHCmnDlTM4TxTx(cell, subFrm, ue, bo, effBo,
         proc, cellWdAllocInfo);

   return;
}
static Void rgSCHCmnDlAllocRetxRbTM4
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   ;;

   if ((proc->tbInfo[0].state == HQ_TB_NACKED) &&
         (proc->tbInfo[1].state == HQ_TB_NACKED))
   {

      rgSCHCmnDlTM4RetxRetx(cell, subFrm, ue, bo, effBo,
            proc, cellWdAllocInfo);
   }
   else
   {


      rgSCHCmnDlTM4TxRetx(cell, subFrm, ue, bo, effBo,
            proc, cellWdAllocInfo);
   }

   return;
}
static Void rgSCHCmnDlAllocTxRbTM6
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   RgSchDlRbAlloc *allocInfo;
   RgSchCmnDlUe *ueDl;
   S16 ret;
   U8 numRb;

   ;;

   ret = 0;
   ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;

   if (ueDl->mimoInfo.forceTD)
   {
      allocInfo->dciFormat = TFU_DCI_FORMAT_1A;
      allocInfo->raType = 2;
   }
   else
   {
      allocInfo->dciFormat = TFU_DCI_FORMAT_1B;
      allocInfo->raType = 2;




      allocInfo->mimoAllocInfo.precIdxInfo |= ue->mimoInfo.puschFdbkVld << 4;
      allocInfo->mimoAllocInfo.precIdxInfo |= ueDl->mimoInfo.pmi;
   }
   ret = rgSCHCmnDlAlloc1CwTxRb(cell, subFrm, ue, &proc->tbInfo[0],
         bo, &numRb, effBo);
   if (ret == 1)
   {

      return;
   }


   if (!(((RgSchCmnDlHqProc *)((proc)->sch))->isSpsSvcSchd))

   {

      rgSCHCmnDlRbInfoAddUeTx(cell, cellWdAllocInfo, ue, proc);
   }

   allocInfo->rbsReq = numRb;
   allocInfo->dlSf = subFrm;
   return;
}
static Void rgSCHCmnDlAllocRetxRbTM6
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   RgSchDlRbAlloc *allocInfo;
   RgSchCmnDlUe *ueDl;
   S16 ret;
   U8 numRb;

   ;;

   ret = 0;
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   if (ueDl->mimoInfo.forceTD)
   {
      allocInfo->dciFormat = TFU_DCI_FORMAT_1A;
      allocInfo->raType = 2;
   }
   else
   {
      allocInfo->dciFormat = TFU_DCI_FORMAT_1B;
      allocInfo->raType = 2;




      allocInfo->mimoAllocInfo.precIdxInfo |= ue->mimoInfo.puschFdbkVld << 4;
      allocInfo->mimoAllocInfo.precIdxInfo |= ueDl->mimoInfo.pmi;
   }



   ret = rgSCHCmnDlAlloc1CwRetxRb(cell, subFrm, ue, &proc->tbInfo[0],
         1, &numRb, effBo);
   if (ret == 1)
   {

      rgSCHCmnDlAdd2NonSchdRetxLst(cellWdAllocInfo, ue, proc);
      return;
   }

   rgSCHCmnDlRbInfoAddUeRetx(cell, cellWdAllocInfo, ue, proc);

   allocInfo->rbsReq = numRb;
   allocInfo->dlSf = subFrm;
   return;
}
static Void rgSCHCmnDlAllocTxRbTM7
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   ;;
   rgSCHCmnDlAllocTxRb1Tb1Cw(cell, subFrm, ue, bo, effBo, proc, cellWdAllocInfo);
   return;
}
static Void rgSCHCmnDlAllocRetxRbTM7
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   ;;
   rgSCHCmnDlAllocRetxRb1Tb1Cw(cell, subFrm, ue, bo, effBo, proc, cellWdAllocInfo);
   return;
}
 S16 rgSCHCmnDlAllocTxRb
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   U32 newSchBits = 0;
   U32 prevSchBits = 0;
   RgSchDlRbAlloc *allocInfo;

   ;;

   if ( !((((cell->crntTime)).sfn == ((ue->dl.lstSchTime)).sfn) && (((cell->crntTime)).subframe == ((ue->dl.lstSchTime)).subframe)))
   {
      ue->dl.aggTbBits = 0;
   }
   *effBo = 0;



   if ((subFrm->bw <= subFrm->bwAssigned) || (0 == bo))
   {
      return(1);
   }



   if(cell->lteAdvCb.sfrCfg.status)
   {
     if(ue->lteAdvUeCb.rgrLteAdvUeCfg.isUeCellEdge)
     {
     if ((subFrm->sfrTotalPoolInfo.CEPoolBwAvlbl <= 0) || (0 == bo))
        {
       return(1);
        }
     }
   }


   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   if (allocInfo->tbInfo[0].schdlngForTb)
   {
      prevSchBits += allocInfo->tbInfo[0].bytesReq;
   }
   if (allocInfo->tbInfo[1].schdlngForTb)
   {
      prevSchBits += allocInfo->tbInfo[1].bytesReq;
   }


   (dlAllocTxRbFunc[ue->mimoInfo.txMode - 1])(cell, subFrm, ue, bo, effBo,
         proc, cellWdAllocInfo);

   if (*effBo)
   {

      if (allocInfo->tbInfo[0].schdlngForTb)
      {
         newSchBits += allocInfo->tbInfo[0].bytesReq;
      }
      if (allocInfo->tbInfo[1].schdlngForTb)
      {
         newSchBits += allocInfo->tbInfo[1].bytesReq;
      }
      if (newSchBits > prevSchBits)
      {
         ue->dl.aggTbBits += ((newSchBits - prevSchBits) * 8);
         (ue->dl.lstSchTime).sfn = (cell->crntTime).sfn; (ue->dl.lstSchTime).subframe = (cell->crntTime).subframe;
      }
   }

   return(0);
}
 Bool rgSCHCmnRetxAllocAvoid
(
RgSchDlSf *subFrm,
RgSchCellCb *cell,
RgSchDlHqProcCb *proc
)






{
   U8 reqRbs;

   ;;

   if (proc->tbInfo[0].state == HQ_TB_NACKED)
   {
      reqRbs = proc->tbInfo[0].dlGrnt.numRb;
   }
   else
   {
      reqRbs = proc->tbInfo[1].dlGrnt.numRb;
   }



   if (subFrm->sfNum % 5 == 0)
   {
      if ((subFrm->bwAssigned < cell->pbchRbEnd) &&
          (((subFrm->bwAssigned + reqRbs) - cell->pbchRbStart) > 0))
      {
         return(1);
      }
   }
   return(0);
}
 S16 rgSCHCmnDlAllocRetxRb
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   U32 newSchBits = 0;
   RgSchDlRbAlloc *allocInfo;

   ;;

   if ( !((((cell->crntTime)).sfn == ((ue->dl.lstSchTime)).sfn) && (((cell->crntTime)).subframe == ((ue->dl.lstSchTime)).subframe)))
   {
      ue->dl.aggTbBits = 0;
   }

   *effBo = 0;

   if (subFrm->bw <= subFrm->bwAssigned)
   {
      return(1);
   }
   if(cell->lteAdvCb.sfrCfg.status)
   {
      if(ue->lteAdvUeCb.rgrLteAdvUeCfg.isUeCellEdge)
      {
         if (subFrm->sfrTotalPoolInfo.CEPoolBwAvlbl <= 0)
         {
            return(1);
         }
      }
   }



   if (rgSCHCmnRetxAllocAvoid(subFrm, cell, proc) == 1)
   {
      return(0);
   }


   (dlAllocRetxRbFunc[ue->mimoInfo.txMode - 1])(cell, subFrm, ue, bo, effBo,
         proc, cellWdAllocInfo);

   if (*effBo)
   {
      allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;

      if (allocInfo->tbInfo[0].schdlngForTb)
      {
         newSchBits += allocInfo->tbInfo[0].bytesReq;
      }
      if (allocInfo->tbInfo[1].schdlngForTb)
      {
         newSchBits += allocInfo->tbInfo[1].bytesReq;
      }
      ue->dl.aggTbBits += (newSchBits * 8);
      (ue->dl.lstSchTime).sfn = (cell->crntTime).sfn; (ue->dl.lstSchTime).subframe = (cell->crntTime).subframe;
   }

   return(0);
}
static S16 rgSCHCmnDlAlloc1CwTxRb
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
RgSchDlHqTbCb *tbInfo,
U32 bo,
U8 *numRb,
U32 *effBo
)
{
   U32 noRes;
   U32 eff;
   U32 tbSz;
   U8 imcs;
   U8 iTbs;
   RgSchCmnDlCell *cellDl;
   RgSchCmnDlUe *ueDl;
   RgSchDlRbAlloc *allocInfo;
   U32 oldReq;
   U32 reqBytes;


   U32 tempNumRb;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U8 cfi;
   U32 availBits = 0;
   S16 availBw;



   ;;

   reqBytes = bo;
   cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   oldReq = ueDl->outStndAlloc;
   cfi = cellDl->currCfi;


   if (ueDl->maxTbBits > ue->dl.aggTbBits)
   {
      availBits = ueDl->maxTbBits - ue->dl.aggTbBits;
   }

   if ((allocInfo->rbsReq >= ueDl->maxRb) ||
         (allocInfo->tbInfo[0].bytesReq >= ueDl->maxTbSz/8) ||
         (ue->dl.aggTbBits >= ueDl->maxTbBits))
   {
      return(1);
   }



   if (ueDl->lastCfi == cfi)
   {
      iTbs = ueDl->mimoInfo.cwInfo[0].iTbs[0];
   }
   else
   {
      U8 cqi = ueDl->mimoInfo.cwInfo[0].cqi;



      iTbs = (U8) rgSchCmnFetchItbs(cell, ueDl, cqi, cfi, 0, 1);

   }



   if (tbInfo->hqP->hasDcch)
   {
      if (iTbs > 5)
      {
         iTbs = iTbs - 5;
      }
      else
      {
         iTbs = 0;
      }
   }

   else if (!cellSch->dl.isDlFreqSel)
   {







      if (subFrm->sfNum % 5 == 0)
      {
         (iTbs > 1)? (iTbs -= 2) : (iTbs = 0);
      }

   }
   eff = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[0][cfi]))[iTbs];

   if (tbInfo->hqP->hasDcch)
   {
   }

   ueDl->outStndAlloc += bo;

   bo = ((ueDl->outStndAlloc) <= (ueDl->maxTbSz/8) ? (ueDl->outStndAlloc) : (ueDl->maxTbSz/8));

   noRes = ((bo * 8 * 1024) / eff);



   tempNumRb = (((noRes) + (cellDl->noResPerRb[cfi])-1) / (cellDl->noResPerRb[cfi]));

   if (tempNumRb > ueDl->maxRb)
   {
      tempNumRb = ueDl->maxRb;
   }
   else
   {
      while ((tempNumRb < ueDl->maxRb) &&
            ((rgTbSzTbl[0][iTbs][tempNumRb-1]/8) < bo))
      {
         (tempNumRb)++;
      }
   }
   availBw = subFrm->bw - subFrm->bwAssigned;

   if ((S16)(tempNumRb - allocInfo->rbsReq) > availBw)
   {
      tempNumRb = availBw + allocInfo->rbsReq;
   }

   tbSz = rgTbSzTbl[0][iTbs][tempNumRb-1]/8;
   *effBo = ((tbSz - oldReq) <= (reqBytes) ? (tbSz - oldReq) : (reqBytes));


   if(allocInfo->laaDlRbAlloc.isLaaTB == 1)
   {
      if(*effBo < bo)
      {
         *effBo = 0;
         return(1);
      }
   }

   do { if (iTbs <= 9) imcs = iTbs; else if (iTbs <= 15) imcs = iTbs + 1; else imcs = iTbs + 2;} while(0);

   { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = tbSz; (&allocInfo->tbInfo[0])->iTbs = iTbs; (&allocInfo->tbInfo[0])->imcs = imcs; (&allocInfo->tbInfo[0])->tbCb = tbInfo; (&allocInfo->tbInfo[0])->noLyr = 1;}
                               ;
   *numRb = (U8) tempNumRb;


   subFrm->bwAssigned = subFrm->bwAssigned + tempNumRb - allocInfo->rbsReq;

   return(0);
}
 Void rgSCHCmnRdcImcsTxTb
(
RgSchDlRbAlloc *allocInfo,
U8 tbInfoIdx,
U32 cnsmdBytes
)






{
   return;

   U8 noLyr;
   U8 iTbs;
   U16 numRb;

   ;;

   iTbs = allocInfo->tbInfo[tbInfoIdx].iTbs;
   noLyr = allocInfo->tbInfo[tbInfoIdx].noLyr;
   numRb = allocInfo->rbsAlloc;
   if ( numRb > 0)
   {
      if ((rgTbSzTbl[noLyr-1][iTbs][numRb-1]/8) == cnsmdBytes)
      {
         return;
      }
   }

   while((rgTbSzTbl[noLyr-1][iTbs][numRb-1]/8) > cnsmdBytes)
   {
      if (iTbs == 0)
      {
         do { if (iTbs <= 9) allocInfo->tbInfo[tbInfoIdx]. tbCb->dlGrnt.iMcs = iTbs; else if (iTbs <= 15) allocInfo->tbInfo[tbInfoIdx]. tbCb->dlGrnt.iMcs = iTbs + 1; else allocInfo->tbInfo[tbInfoIdx]. tbCb->dlGrnt.iMcs = iTbs + 2;} while(0)
                                 ;
         return;
      }
      iTbs--;
   }
   iTbs++;
   do { if (iTbs <= 9) allocInfo->tbInfo[tbInfoIdx].tbCb->dlGrnt.iMcs = iTbs; else if (iTbs <= 15) allocInfo->tbInfo[tbInfoIdx].tbCb->dlGrnt.iMcs = iTbs + 1; else allocInfo->tbInfo[tbInfoIdx].tbCb->dlGrnt.iMcs = iTbs + 2;} while(0);

   return;
}
static S16 rgSCHCmnDlAlloc2CwTxRb
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
RgSchDlHqProcCb *proc,
U32 bo,
U8 *numRbRef,
U32 *effBo
)
{
   U32 noRes;
   U32 eff1, eff2;
   U32 tb1Sz, tb2Sz;
   U8 imcs1, imcs2;
   U8 noLyr1, noLyr2;
   U8 iTbs1, iTbs2;
   RgSchCmnDlCell *cellDl;
   RgSchCmnDlUe *ueDl;
   RgSchDlRbAlloc *allocInfo;
   U32 oldReq;
   U32 reqBytes;

   U32 numRb;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   U8 cfi = cellSch->dl.currCfi;
   S16 availBw;
   U32 availBits = 0;

   ;;

   reqBytes = bo;
   cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   oldReq = ueDl->outStndAlloc;


   if (ueDl->maxTbBits > ue->dl.aggTbBits)
   {
      availBits = ueDl->maxTbBits - ue->dl.aggTbBits;
   }

   if ((ue->dl.aggTbBits >= ueDl->maxTbBits) ||
         (allocInfo->tbInfo[0].bytesReq >= ueDl->maxTbSz/8) ||
         (allocInfo->tbInfo[1].bytesReq >= ueDl->maxTbSz/8) ||
         (allocInfo->rbsReq >= ueDl->maxRb))
   {
      if( L_DEBUG < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0055,L_DEBUG,DBG_CELLID, cell->cellId, 0, 0, 0, 0,                                                            "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                            30051      , "rgSCHCmnDlAllocRb(): UEs max allocation exceed", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                             ;
      return(1);
   }

   noLyr1 = ueDl->mimoInfo.cwInfo[0].noLyr;
   noLyr2 = ueDl->mimoInfo.cwInfo[1].noLyr;



   if (ueDl->lastCfi == cfi)
   {
      iTbs1 = ueDl->mimoInfo.cwInfo[0].iTbs[noLyr1 - 1];
      iTbs2 = ueDl->mimoInfo.cwInfo[1].iTbs[noLyr2 - 1];
   }
   else
   {
      U8 cqi = ueDl->mimoInfo.cwInfo[0].cqi;



      iTbs1 = (U8) rgSchCmnFetchItbs(cell, ueDl, cqi, cfi, 0, noLyr1);


      cqi = ueDl->mimoInfo.cwInfo[1].cqi;



      iTbs2 = (U8) rgSchCmnFetchItbs(cell, ueDl, cqi, cfi, 1, noLyr2);

   }



   if (proc->hasDcch)
   {
      if (iTbs1 > 5)
      {
         iTbs1 = iTbs1 - 5;
      }
      else
      {
         iTbs1 = 0;
      }
      if (iTbs2 > 5)
      {
         iTbs2 = iTbs2 - 5;
      }
      else
      {
         iTbs2 = 0;
      }
   }
   else if(!cellSch->dl.isDlFreqSel)
   {
   }
   eff1 = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[noLyr1 - 1][cfi]))[iTbs1];
   eff2 = (*(RgSchCmnTbSzEff *)(cellSch->dl.cqiToEffTbl[noLyr2 - 1][cfi]))[iTbs2];


   bo = ((bo) <= (availBits/8) ? (bo) : (availBits/8));
   ueDl->outStndAlloc += bo;

   bo = ((ueDl->outStndAlloc) <= (ueDl->maxTbBits/8) ? (ueDl->outStndAlloc) : (ueDl->maxTbBits/8));
   bo = (((((3 * 5 + 1)) >= ((bo*eff1)/(eff1+eff2)) ? ((3 * 5 + 1)) : ((bo*eff1)/(eff1+eff2)))) <= (ueDl->maxTbSz/8) ? ((((3 * 5 + 1)) >= ((bo*eff1)/(eff1+eff2)) ? ((3 * 5 + 1)) : ((bo*eff1)/(eff1+eff2)))) : (ueDl->maxTbSz/8))
                     +
        (((((3 * 5 + 1)) >= ((bo*eff2)/(eff1+eff2)) ? ((3 * 5 + 1)) : ((bo*eff2)/(eff1+eff2)))) <= ((ueDl->maxTbSz)/8) ? ((((3 * 5 + 1)) >= ((bo*eff2)/(eff1+eff2)) ? ((3 * 5 + 1)) : ((bo*eff2)/(eff1+eff2)))) : ((ueDl->maxTbSz)/8))
                       +
        1;

   noRes = ((bo * 8 * 1024) / (eff1 + eff2));



   numRb = (((noRes) + (cellDl->noResPerRb[cfi])-1) / (cellDl->noResPerRb[cfi]));

   if (numRb > ueDl->maxRb)
   {
      numRb = ueDl->maxRb;
   }
   else
   {



      while ((numRb <= ueDl->maxRb) &&
              (rgTbSzTbl[noLyr1 - 1][iTbs1][numRb-1] <= ueDl->maxTbSz) &&
              (rgTbSzTbl[noLyr2 - 1][iTbs2][numRb-1] <= ueDl->maxTbSz) &&
              ((rgTbSzTbl[noLyr1 - 1][iTbs1][numRb-1]/8 +
                rgTbSzTbl[noLyr2 - 1][iTbs2][numRb-1]/8) <= bo))
      {

         (numRb)++;
      }


   }
   availBw = subFrm->bw - subFrm->bwAssigned;

   if ((S16)(numRb - allocInfo->rbsReq) > availBw)
   {
      numRb = availBw + allocInfo->rbsReq;
   }
   tb1Sz = rgTbSzTbl[noLyr1 - 1][iTbs1][numRb-1]/8;
   tb2Sz = rgTbSzTbl[noLyr2 - 1][iTbs2][numRb-1]/8;
   subFrm->bwAssigned = subFrm->bwAssigned + numRb -
                        allocInfo->rbsReq;

   *effBo = (((tb1Sz + tb2Sz) - oldReq) <= (reqBytes) ? ((tb1Sz + tb2Sz) - oldReq) : (reqBytes));
   if(allocInfo->laaDlRbAlloc.isLaaTB == 1)
   {
      if(*effBo < bo)
      {
         *effBo = 0;
         return(1);
      }
   }
   do { if (iTbs1 <= 9) imcs1 = iTbs1; else if (iTbs1 <= 15) imcs1 = iTbs1 + 1; else imcs1 = iTbs1 + 2;} while(0);
   do { if (iTbs2 <= 9) imcs2 = iTbs2; else if (iTbs2 <= 15) imcs2 = iTbs2 + 1; else imcs2 = iTbs2 + 2;} while(0);
   { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = tb1Sz; (&allocInfo->tbInfo[0])->iTbs = iTbs1; (&allocInfo->tbInfo[0])->imcs = imcs1; (&allocInfo->tbInfo[0])->tbCb = &proc->tbInfo[0]; (&allocInfo->tbInfo[0])->noLyr = noLyr1;}
                                                ;
   { (&allocInfo->tbInfo[1])->schdlngForTb = 1; (&allocInfo->tbInfo[1])->bytesReq = tb2Sz; (&allocInfo->tbInfo[1])->iTbs = iTbs2; (&allocInfo->tbInfo[1])->imcs = imcs2; (&allocInfo->tbInfo[1])->tbCb = &proc->tbInfo[1]; (&allocInfo->tbInfo[1])->noLyr = noLyr2;}
                                                ;
   *numRbRef = (U8)numRb;


   return(0);
}
static S16 rgSCHCmnDlAlloc2CwTxRetxRb
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
RgSchDlHqTbCb *reTxTb,
RgSchDlHqTbCb *txTb,
U8 *numRb,
U32 *effBo
)
{
   RgSchCmnDlUe *ueDl;
   RgSchDlRbAlloc *allocInfo;
   U8 imcs1, imcs2;
   U8 noLyr2;
   U16 tb2Sz;
   RgSchCmnDlUeCwInfo *otherCw;
   S16 availBw;
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);
   U8 cfi = cellDl->currCfi;
   U8 iTbs;

   ;;

   ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));
   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;
   otherCw = &ueDl->mimoInfo.cwInfo[!(ueDl->mimoInfo.btrCwIdx)];





   availBw = subFrm->bw - subFrm->bwAssigned;
   *numRb = reTxTb->dlGrnt.numRb;
   if ((S16)*numRb > availBw)
   {
      return(1);
   }

   subFrm->bwAssigned += *numRb;
   noLyr2 = otherCw->noLyr;
   do { if ((reTxTb->isAckNackDtx == 4)) { imcs1 = reTxTb->dlGrnt.iMcs; } else { if (reTxTb->dlGrnt.iMcs < 29) { U8 _iTbs; do { if (reTxTb->dlGrnt.iMcs <= 9) _iTbs = reTxTb->dlGrnt.iMcs; else if (reTxTb->dlGrnt.iMcs <= 16) _iTbs = reTxTb->dlGrnt.iMcs - 1; else _iTbs = reTxTb->dlGrnt.iMcs - 2; }while(0); do { if ((_iTbs) <= 9) (imcs1) = 29; else if ((_iTbs) <= 15) (imcs1) = 30; else (imcs1) = 31;} while(0); } else { imcs1 = reTxTb->dlGrnt.iMcs; } }}while(0);



   if (ueDl->lastCfi == cfi)
   {
      iTbs = otherCw->iTbs[noLyr2-1];
   }
   else
   {




      iTbs = (U8) rgSchCmnFetchItbs(cell, ueDl, otherCw->cqi, cfi,
                                      !(ueDl->mimoInfo.btrCwIdx), noLyr2);

   }
   tb2Sz = rgTbSzTbl[noLyr2-1][iTbs][*numRb-1]/8;
   do { if (iTbs <= 9) imcs2 = iTbs; else if (iTbs <= 15) imcs2 = iTbs + 1; else imcs2 = iTbs + 2;} while(0);

   { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = reTxTb->tbSz; (&allocInfo->tbInfo[0])->iTbs = 0; (&allocInfo->tbInfo[0])->imcs = imcs1; (&allocInfo->tbInfo[0])->tbCb = reTxTb; (&allocInfo->tbInfo[0])->noLyr = reTxTb->numLyrs;}
                                                                ;

   { (&allocInfo->tbInfo[1])->schdlngForTb = 1; (&allocInfo->tbInfo[1])->bytesReq = tb2Sz; (&allocInfo->tbInfo[1])->iTbs = iTbs; (&allocInfo->tbInfo[1])->imcs = imcs2; (&allocInfo->tbInfo[1])->tbCb = txTb; (&allocInfo->tbInfo[1])->noLyr = noLyr2;}
                                                        ;

   *effBo = reTxTb->tbSz + tb2Sz;

   return(0);
}
static S16 rgSCHCmnDlAlloc2CwRetxRb
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
RgSchDlHqProcCb *proc,
U8 *numRb,
Bool *swpFlg,
U32 *effBo
)
{
   RgSchDlRbAlloc *allocInfo;
   U8 imcs1;
   U8 imcs2;
   RgSchDlHqTbCb *lrgTbInfo, *othrTbInfo;

   ;;

   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;





   lrgTbInfo = &proc->tbInfo[0];
   othrTbInfo = &proc->tbInfo[1];
   *numRb = lrgTbInfo->dlGrnt.numRb;
   if ((S16)*numRb > (S16)(subFrm->bw - subFrm->bwAssigned))
   {
      return(1);
   }

   subFrm->bwAssigned += *numRb;
   do { if ((lrgTbInfo->isAckNackDtx == 4)) { imcs1 = lrgTbInfo->dlGrnt.iMcs; } else { if (lrgTbInfo->dlGrnt.iMcs < 29) { U8 _iTbs; do { if (lrgTbInfo->dlGrnt.iMcs <= 9) _iTbs = lrgTbInfo->dlGrnt.iMcs; else if (lrgTbInfo->dlGrnt.iMcs <= 16) _iTbs = lrgTbInfo->dlGrnt.iMcs - 1; else _iTbs = lrgTbInfo->dlGrnt.iMcs - 2; }while(0); do { if ((_iTbs) <= 9) (imcs1) = 29; else if ((_iTbs) <= 15) (imcs1) = 30; else (imcs1) = 31;} while(0); } else { imcs1 = lrgTbInfo->dlGrnt.iMcs; } }}while(0);
   do { if ((othrTbInfo->isAckNackDtx == 4)) { imcs2 = othrTbInfo->dlGrnt.iMcs; } else { if (othrTbInfo->dlGrnt.iMcs < 29) { U8 _iTbs; do { if (othrTbInfo->dlGrnt.iMcs <= 9) _iTbs = othrTbInfo->dlGrnt.iMcs; else if (othrTbInfo->dlGrnt.iMcs <= 16) _iTbs = othrTbInfo->dlGrnt.iMcs - 1; else _iTbs = othrTbInfo->dlGrnt.iMcs - 2; }while(0); do { if ((_iTbs) <= 9) (imcs2) = 29; else if ((_iTbs) <= 15) (imcs2) = 30; else (imcs2) = 31;} while(0); } else { imcs2 = othrTbInfo->dlGrnt.iMcs; } }}while(0);
   { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = lrgTbInfo->tbSz; (&allocInfo->tbInfo[0])->iTbs = 0; (&allocInfo->tbInfo[0])->imcs = imcs1; (&allocInfo->tbInfo[0])->tbCb = lrgTbInfo; (&allocInfo->tbInfo[0])->noLyr = lrgTbInfo->numLyrs;}
                                                 ;
   { (&allocInfo->tbInfo[1])->schdlngForTb = 1; (&allocInfo->tbInfo[1])->bytesReq = othrTbInfo->tbSz; (&allocInfo->tbInfo[1])->iTbs = 0; (&allocInfo->tbInfo[1])->imcs = imcs2; (&allocInfo->tbInfo[1])->tbCb = othrTbInfo; (&allocInfo->tbInfo[1])->noLyr = othrTbInfo->numLyrs;}
                                                   ;
   *effBo = lrgTbInfo->tbSz + othrTbInfo->tbSz;



   return(0);
}
static S16 rgSCHCmnDlAlloc1CwRetxRb
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
RgSchDlHqTbCb *tbInfo,
U8 noLyr,
U8 *numRb,
U32 *effBo
)
{
   RgSchDlRbAlloc *allocInfo;
   U8 imcs;

   ;;

   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;





   *numRb = tbInfo->dlGrnt.numRb;
   if ((S16)*numRb > (S16)(subFrm->bw - subFrm->bwAssigned))
   {
      return(1);
   }

   subFrm->bwAssigned += *numRb;
   do { if ((tbInfo->isAckNackDtx == 4)) { imcs = tbInfo->dlGrnt.iMcs; } else { if (tbInfo->dlGrnt.iMcs < 29) { U8 _iTbs; do { if (tbInfo->dlGrnt.iMcs <= 9) _iTbs = tbInfo->dlGrnt.iMcs; else if (tbInfo->dlGrnt.iMcs <= 16) _iTbs = tbInfo->dlGrnt.iMcs - 1; else _iTbs = tbInfo->dlGrnt.iMcs - 2; }while(0); do { if ((_iTbs) <= 9) (imcs) = 29; else if ((_iTbs) <= 15) (imcs) = 30; else (imcs) = 31;} while(0); } else { imcs = tbInfo->dlGrnt.iMcs; } }}while(0);

   { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = tbInfo->tbSz; (&allocInfo->tbInfo[0])->iTbs = 0; (&allocInfo->tbInfo[0])->imcs = imcs; (&allocInfo->tbInfo[0])->tbCb = tbInfo; (&allocInfo->tbInfo[0])->noLyr = tbInfo->numLyrs;}
                                          ;
   *effBo = tbInfo->tbSz;

   return(0);
}
 Void rgSCHCmnDlRelPdcchFbk
(
RgSchCellCb *cell,
RgSchUeCb *ue,
Bool isAck
)






{

   ;;
   rgSCHCmnSpsDlRelPdcchFbk(cell, ue, isAck);
   return;

}
 Void rgSCHCmnDlProcAck
(
RgSchCellCb *cell,
RgSchDlHqProcCb *hqP
)





{

   ;;

   if ((((RgSchCmnDlHqProc *)((hqP)->sch))->isSpsSvcSchd))
   {

      rgSCHCmnSpsDlProcAck(cell, hqP);
   }
   return;
}
 Void rgSCHCmnHdlCrntiCE
(
RgSchCellCb *cell,
RgSchUeCb *ue
)





{

   ;;
   if ((ue->ul.ulInactvMask & 0x04))
   {

       if((ue->dl.dlInactvMask == 0)) { ue->dl.dlInactvMask &= ~0x04; } else { ue->dl.dlInactvMask &= ~0x04; if((ue->dl.dlInactvMask == 0)) { rgSCHUtlDlActvtUe(cell, ue); } };
       if((ue->ul.ulInactvMask == 0)) { ue->ul.ulInactvMask &= ~0x04; } else { ue->ul.ulInactvMask &= ~0x04; if((ue->ul.ulInactvMask == 0)) { rgSCHUtlUlActvtUe(cell, ue); } };
   }


   if (ue->dl.dlSpsCfg.isDlSpsEnabled)
   {
      rgSCHCmnSpsDlUeReset(cell, ue);
   }
   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
      rgSCHCmnSpsUlUeReset(cell, ue);
   }

   return;
}
 Void rgSCHCmnUlSpsRelInd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
Bool isExplRel
)






{

   ;;
   rgSCHCmnSpsUlProcRelInd(cell, ue, isExplRel);
   return;

}
 Void rgSCHCmnUlSpsActInd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U16 spsSduSize
)






{

   ;;

   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
      rgSCHCmnSpsUlProcActInd(cell, ue,spsSduSize);
   }
   return;

}
 Void rgSCHCmnUlCrcInd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
CmLteTimingInfo crcTime
)






{

   ;;
   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
      rgSCHCmnSpsUlProcCrcInd(cell, ue, crcTime);
   }
   return;

}
 Void rgSCHCmnUlCrcFailInd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
CmLteTimingInfo crcTime
)






{

   ;;
   if (ue->ul.ulSpsCfg.isUlSpsEnabled == 1)
   {
      rgSCHCmnSpsUlProcDtxInd(cell, ue, crcTime);
   }
   return;

}
static Void rgSCHCmnDlBcchPcchAlloc
(
RgSchCellCb *cell
)




{






   U8 nextSfIdx = (cell->crntSfIdx) % 10;


   RgInfSfAlloc *nextsfAlloc = &(cell->sfAllocArr[nextSfIdx]);
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   RgSchCmnDlRbAllocInfo *allocInfo = &cellSch->allocInfo;

   ;;



   rgSCHUtlResetSfAlloc(nextsfAlloc,1,0);


   rgSCHChkNUpdSiCfg(cell);
   rgSCHSelectSi(cell);



   rgSCHCmnDlBcchPcch(cell, allocInfo, nextsfAlloc);


   rgSCHBcchPcchDlRbAlloc(cell, allocInfo);


   rgSCHCmnDlBcchPcchFnlz(cell, allocInfo);

   return;
}
static Void rgSCHBcchPcchDlRbAlloc
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;


   if (cellSch->dl.isDlFreqSel)
   {
      cellSch->apisDlfs->rgSCHDlfsBcchPcchAllocRb(cell, allocInfo);
   }
   else
   {
      rgSCHCmnNonDlfsBcchPcchRbAlloc(cell, allocInfo);
   }

   return;
}
static Void rgSCHCmnNonDlfsBcchPcchRbAlloc
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo
)





{
   RgSchDlRbAlloc *reqAllocInfo;

   ;;



   reqAllocInfo = &(allocInfo->pcchAlloc);
   if (reqAllocInfo->rbsReq)
   {
      rgSCHCmnNonDlfsCmnRbAlloc(cell, reqAllocInfo);
   }

   reqAllocInfo = &(allocInfo->bcchAlloc);
   if (reqAllocInfo->rbsReq)
   {
      rgSCHCmnNonDlfsCmnRbAlloc(cell, reqAllocInfo);
   }
   return;
}
static Void rgSCHChkNUpdSiCfg
(
RgSchCellCb *cell
)




{
   CmLteTimingInfo pdSchTmInfo;

   ;;


   pdSchTmInfo = cell->crntTime;





   do { if ((pdSchTmInfo.subframe += (2 + 0)) > 9) { pdSchTmInfo.sfn = ((pdSchTmInfo.sfn) + 1) & 0x03ff; pdSchTmInfo.subframe -= 10; }} while(0);






   if((pdSchTmInfo.sfn % 2 == 0)
         && (5 == pdSchTmInfo.subframe))
   {

      if(cell->siCb.siBitMask & (1<<4))
      {
         do{ if(0L != cell->siCb.crntSiInfo.sib1Info.sib1) { if (0L != (cell->siCb.crntSiInfo.sib1Info.sib1)) { SPutMsg((cell->siCb.crntSiInfo.sib1Info.sib1)); cell->siCb.crntSiInfo.sib1Info.sib1 = 0L; } }; cell->siCb.crntSiInfo.sib1Info.sib1 = cell->siCb.newSiInfo.sib1Info.sib1; cell->siCb.newSiInfo.sib1Info.sib1 = 0L;}while(0)
                                                  ;
         cell->siCb.crntSiInfo.sib1Info.mcs =
            cell->siCb.newSiInfo.sib1Info.mcs;
         cell->siCb.crntSiInfo.sib1Info.nPrb =
             cell->siCb.newSiInfo.sib1Info.nPrb;
         cell->siCb.crntSiInfo.sib1Info.msgLen =
            cell->siCb.newSiInfo.sib1Info.msgLen;
         cell->siCb.siBitMask &= ~(1<<4);
      }
   }




   if(!((pdSchTmInfo.sfn % cell->siCfg.modPrd == 0)
            && (0 == pdSchTmInfo.subframe)))
   {
      return;
   }


   if(cell->siCb.siBitMask & (1<<1))
   {
      do{ if(0L != cell->siCb.crntSiInfo.mib) { if (0L != (cell->siCb.crntSiInfo.mib)) { SPutMsg((cell->siCb.crntSiInfo.mib)); cell->siCb.crntSiInfo.mib = 0L; } }; cell->siCb.crntSiInfo.mib = cell->siCb.newSiInfo.mib; cell->siCb.newSiInfo.mib = 0L;}while(0)
                                     ;
      cell->siCb.siBitMask &= ~(1<<1);
   }


   if(cell->siCb.siBitMask & (1<<2))
   {
      do{ if(0L != cell->siCb.crntSiInfo.sib1Info.sib1) { if (0L != (cell->siCb.crntSiInfo.sib1Info.sib1)) { SPutMsg((cell->siCb.crntSiInfo.sib1Info.sib1)); cell->siCb.crntSiInfo.sib1Info.sib1 = 0L; } }; cell->siCb.crntSiInfo.sib1Info.sib1 = cell->siCb.newSiInfo.sib1Info.sib1; cell->siCb.newSiInfo.sib1Info.sib1 = 0L;}while(0)
                                               ;
      cell->siCb.crntSiInfo.sib1Info.mcs = cell->siCb.newSiInfo.sib1Info.mcs;
      cell->siCb.crntSiInfo.sib1Info.nPrb = cell->siCb.newSiInfo.sib1Info.nPrb;
      cell->siCb.crntSiInfo.sib1Info.msgLen =
         cell->siCb.newSiInfo.sib1Info.msgLen;
      cell->siCb.siBitMask &= ~(1<<2);
   }


   if(cell->siCb.siBitMask & (1<<3))
   {
      U8 idx;




      if((cell->siCb.siBitMask & (1<<0)) &&
            (cell->siCfg.numSi != cell->siCb.newSiCfg.numSi))
      {
         for(idx = 0;idx < cell->siCb.newSiCfg.numSi;idx++)
         {
            do{ if(0L != cell->siCb.crntSiInfo.siInfo[idx].si) { if (0L != (cell->siCb.crntSiInfo.siInfo[idx].si)) { SPutMsg((cell->siCb.crntSiInfo.siInfo[idx].si)); cell->siCb.crntSiInfo.siInfo[idx].si = 0L; } }; cell->siCb.crntSiInfo.siInfo[idx].si = cell->siCb.newSiInfo.siInfo[idx].si; cell->siCb.newSiInfo.siInfo[idx].si = 0L;}while(0)
                                                      ;
            cell->siCb.siArray[idx].si = cell->siCb.crntSiInfo.siInfo[idx].si;
            cell->siCb.siArray[idx].isWarningSi = 0;

            cell->siCb.crntSiInfo.siInfo[idx].mcs = cell->siCb.newSiInfo.siInfo[idx].mcs;
            cell->siCb.crntSiInfo.siInfo[idx].nPrb = cell->siCb.newSiInfo.siInfo[idx].nPrb;
            cell->siCb.crntSiInfo.siInfo[idx].msgLen = cell->siCb.newSiInfo.siInfo[idx].msgLen;
         }






         if(cell->siCfg.numSi > cell->siCb.newSiCfg.numSi)
         {
            for(idx = cell->siCb.newSiCfg.numSi;
                  idx < cell->siCfg.numSi;idx++)
            {
               { if (0L != (cell->siCb.crntSiInfo.siInfo[idx].si)) { SPutMsg((cell->siCb.crntSiInfo.siInfo[idx].si)); cell->siCb.crntSiInfo.siInfo[idx].si = 0L; } };
               cell->siCb.siArray[idx].si = 0L;
            }
         }
      }
      else
      {



         for(idx = 0;idx < cell->siCfg.numSi;idx++)
         {
            if(0L != cell->siCb.newSiInfo.siInfo[idx].si)
            {
               do{ if(0L != cell->siCb.crntSiInfo.siInfo[idx].si) { if (0L != (cell->siCb.crntSiInfo.siInfo[idx].si)) { SPutMsg((cell->siCb.crntSiInfo.siInfo[idx].si)); cell->siCb.crntSiInfo.siInfo[idx].si = 0L; } }; cell->siCb.crntSiInfo.siInfo[idx].si = cell->siCb.newSiInfo.siInfo[idx].si; cell->siCb.newSiInfo.siInfo[idx].si = 0L;}while(0)
                                                         ;

               cell->siCb.siArray[idx].si = cell->siCb.crntSiInfo.siInfo[idx].si;
               cell->siCb.siArray[idx].isWarningSi = 0;
               cell->siCb.crntSiInfo.siInfo[idx].mcs = cell->siCb.newSiInfo.siInfo[idx].mcs;
               cell->siCb.crntSiInfo.siInfo[idx].nPrb = cell->siCb.newSiInfo.siInfo[idx].nPrb;
               cell->siCb.crntSiInfo.siInfo[idx].msgLen = cell->siCb.newSiInfo.siInfo[idx].msgLen;
            }
         }
      }
      cell->siCb.siBitMask &= ~(1<<3);
   }


   if(cell->siCb.siBitMask & (1<<0))
   {
      cell->siCfg = cell->siCb.newSiCfg;
      cell->siCb.siBitMask &= ~(1<<0);
   }

   return;
}
static Void rgSCHSelectSi
(
RgSchCellCb *cell
)




{
   CmLteTimingInfo crntTmInfo;
   U8 siWinSize;
   U16 x;
   U16 windowId;

   ;;


   crntTmInfo = cell->crntTime;





   do { if ((crntTmInfo.subframe += (2 + 0)) > 9) { crntTmInfo.sfn = ((crntTmInfo.sfn) + 1) & 0x03ff; crntTmInfo.subframe -= 10; }} while(0);


   siWinSize = cell->siCfg.siWinSize;


   if(cell->siCb.inWindow)
   {
      if ((crntTmInfo.sfn % cell->siCfg.minPeriodicity) == 0 &&
          crntTmInfo.subframe == 0)
      {

         cell->siCb.inWindow = siWinSize - 1;
      }
      else
      {
         cell->siCb.inWindow--;
         return;
      }
   }
   else
   {
      if((cell->siCb.siArray[cell->siCb.siCtx.siId - 1].isWarningSi == 1)&&
            (cell->siCb.siCtx.retxCntRem != 0))
      {
         rgSCHUtlFreeWarningSiPdu(cell);
         cell->siCb.siCtx.warningSiFlag = 0;
      }

      cell->siCb.inWindow = siWinSize - 1;
   }

   x = rgSCHCmnGetSiSetId(crntTmInfo.sfn, crntTmInfo.subframe,
                                  cell->siCfg.minPeriodicity);



   windowId = (((crntTmInfo.sfn * 10) +
            crntTmInfo.subframe) - (x * (cell->siCfg.minPeriodicity * 10)))
                                                               / siWinSize;

   if(windowId >= 16)
      return;



   if (0L != cell->siCb.siArray[windowId].si)
   {

      if(((cell->siCb.siArray[windowId].isWarningSi == 0) &&
               (x % (cell->siCfg.siPeriodicity[windowId]
                     /cell->siCfg.minPeriodicity) == 0)) ||
            ((cell->siCb.siArray[windowId].isWarningSi == 1) &&
             (x % (cell->siCfg.siPeriodicity[0]
                   /cell->siCfg.minPeriodicity) == 0)))
      {
         cell->siCb.siCtx.siId = windowId+1;
         cell->siCb.siCtx.retxCntRem = cell->siCfg.retxCnt;
         cell->siCb.siCtx.warningSiFlag = cell->siCb.siArray[windowId].
                                                           isWarningSi;
         cell->siCb.siCtx.timeToTx.sfn = crntTmInfo.sfn;
         cell->siCb.siCtx.timeToTx.subframe = crntTmInfo.subframe;

         if ((cell->siCb.siCtx.timeToTx.subframe + ((siWinSize - 1))) >= 10) cell->siCb.siCtx.maxTimeToTx.sfn = (cell->siCb.siCtx.timeToTx.sfn + (cell->siCb.siCtx.timeToTx.subframe + ((siWinSize - 1)))/10) % 1024; else cell->siCb.siCtx.maxTimeToTx.sfn = cell->siCb.siCtx.timeToTx.sfn; cell->siCb.siCtx.maxTimeToTx.subframe = (cell->siCb.siCtx.timeToTx.subframe + ((siWinSize - 1))) % 10;

      }
   }
   else
   {
      cell->siCb.siCtx.siId = 0;
   }

   return;
}
static Void rgSCHDlSiSched
(
RgSchCellCb *cell,
RgSchCmnDlRbAllocInfo *allocInfo,
RgInfSfAlloc *subfrmAlloc
)






{
   CmLteTimingInfo crntTimInfo;
   RgSchDlSf *sf;
   U8 nPrb = 0;
   U8 mcs = 0;
   MsgLen msgLen = 0;
   U32 rb=0;
   RgSchCmnDlCell *cellDl = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);







   ;;


   crntTimInfo = cell->crntTime;





   do { if ((crntTimInfo.subframe += (2 + 0)) > 9) { crntTimInfo.sfn = ((crntTimInfo.sfn) + 1) & 0x03ff; crntTimInfo.subframe -= 10; }} while(0);




   sf = rgSCHUtlSubFrmGet(cell, crntTimInfo);


   if((crntTimInfo.sfn % 4 == 0)
         && (0 == crntTimInfo.subframe))
   {
      MsgLen mibLen = 0;
      U8 sfnOctet, mibOct2 = 0;
      U8 mibOct1 = 0;

      if(0L == cell->siCb.crntSiInfo.mib)
         return;

      SFndLenMsg(cell->siCb.crntSiInfo.mib, &mibLen);
      sf->bch.tbSize = mibLen;

      rgSCHUtlFillRgInfCmnLcInfo(sf, subfrmAlloc, 0L, 0L);



      sfnOctet = (U8)(crntTimInfo.sfn >> 2);


      if(0 != SExamMsg((Data *)(&mibOct1),
               cell->siCb.crntSiInfo.mib, 0))
         return;

      if(0 != SExamMsg((Data *)(&mibOct2),
               cell->siCb.crntSiInfo.mib, 1))
         return;


      mibOct1 = (mibOct1 & 0xFC) | (sfnOctet >> 6);
      mibOct2 = (mibOct2 & 0x03) | (sfnOctet << 2);



      if(0 != SRepMsg((Data)(mibOct1),
               cell->siCb.crntSiInfo.mib, 0))
         return;

      if(0 != SRepMsg((Data)(mibOct2),
               cell->siCb.crntSiInfo.mib, 1))
         return;


      SCpyMsgMsg(cell->siCb.crntSiInfo.mib,
            rgSchCb[cell->instIdx].rgSchInit.region,
            rgSchCb[cell->instIdx].rgSchInit.pool,
            &subfrmAlloc->cmnLcInfo.bchInfo.pdu);






   }

   allocInfo->bcchAlloc.schdFirst = 0;




   if((crntTimInfo.sfn % 2 == 0)
         && (5 == crntTimInfo.subframe))
   {

      if(0L == (cell->siCb.crntSiInfo.sib1Info.sib1))
      {
         return;
      }

      allocInfo->bcchAlloc.schdFirst = 1;
      mcs = cell->siCb.crntSiInfo.sib1Info.mcs;
      nPrb = cell->siCb.crntSiInfo.sib1Info.nPrb;
      msgLen = cell->siCb.crntSiInfo.sib1Info.msgLen;
   }
   else
   {

      Bool invalid = 0;

      if(cell->siCb.siCtx.siId == 0)
         return;


      invalid = rgSCHCmnChkPastWin(crntTimInfo, cell->siCb.siCtx.maxTimeToTx);
      if(invalid)
      {

         if(cell->siCb.siCtx.retxCntRem)
         {
            SLogError(rgSchCb[cell->instIdx].rgSchInit.ent, rgSchCb[cell->instIdx].rgSchInit.inst, rgSchCb[cell->instIdx].rgSchInit.procId, (Txt *)
                                                                                       "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"
            , (S32)
                                                                                       31422
            , (ErrCls) (0x2), (ErrCode) (((0 + 0) + 11)), (ErrVal) ((ErrVal)cell->siCb.siCtx.siId), (Txt *) "rgSCHDlSiSched(): SI not scheduled and window expired")
                                                                                        ;
         }

         if(cell->siCb.siCtx.warningSiFlag == 1)
         {
            rgSCHUtlFreeWarningSiPdu(cell);
            cell->siCb.siCtx.warningSiFlag = 0;
         }
         return;
      }



      if(0 == (rgSCHCmnChkInWin(crntTimInfo,
                  cell->siCb.siCtx.timeToTx,
                  cell->siCb.siCtx.maxTimeToTx)))
      {
         return;

      }

      if(0 == cell->siCb.siCtx.retxCntRem)
      {
         return;
      }



      if(RGR_ENABLE == cell->lteAdvCb.absCfg.status)
      {

         if(cell->lteAdvCb.absCfg.absPatternType & RGR_ABS_MUTE)
         {

            if(RG_SCH_ABS_ENABLED_ABS_SF == (RgSchAbsSfEnum)(cell->lteAdvCb.absCfg.absPattern
                  [((crntTimInfo.sfn*10) + crntTimInfo.subframe) % 40]))
            {

               return;
            }
         }
      }






        if((rgSCHUtlGetMcsAndNPrb(cell, &nPrb, &mcs, &msgLen)) != 0)
        {
           return;
        }

      cell->siCb.siCtx.i = (crntTimInfo.sfn*10+crntTimInfo.subframe) < (cell->siCb.siCtx.timeToTx.sfn*10+cell->siCb.siCtx.timeToTx.subframe)? ((crntTimInfo.sfn+1024)*10+crntTimInfo.subframe) - (cell->siCb.siCtx.timeToTx.sfn*10+cell->siCb.siCtx.timeToTx.subframe) : (crntTimInfo.sfn*10+crntTimInfo.subframe) - (cell->siCb.siCtx.timeToTx.sfn*10+cell->siCb.siCtx.timeToTx.subframe)
                                      ;
   }




   if(cellDl->bitsPerRb==0)
   {
      while ((rgTbSzTbl[0][0][rb]) < (U32) (msgLen*8))
      {
         rb++;
      }
      rb = rb+1;
   }
   else
   {
      rb = ((((msgLen*8)) + (cellDl->bitsPerRb)-1) / (cellDl->bitsPerRb));
   }
   if (rb > sf->bw - sf->bwAssigned)
   {
      if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0056,L_ERROR,DBG_CELLID, cell->cellId,0xffff, 0, 0, 0,                                                      "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"      ,                                                      31514      , "rgSCHDlSiSched(): " "BW allocation failed CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                       ;
      return;
   }


   sf->bwAssigned = sf->bwAssigned + rb;


   allocInfo->bcchAlloc.rnti = 0xffff;
   allocInfo->bcchAlloc.dlSf = sf;
   allocInfo->bcchAlloc.rbsReq = rb;

   allocInfo->bcchAlloc.tbInfo[0].imcs = mcs;


   allocInfo->bcchAlloc.nPrb = nPrb;
   allocInfo->bcchAlloc.tbInfo[0].bytesReq = msgLen;
   allocInfo->bcchAlloc.tbInfo[0].noLyr = 1;
   return;
}
static S16 rgSCHCmnUeDlPwrCtColltCqiRept
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgrUeCqiRept *ueCqiRpt
)






{
   U8 *cqiCount = 0L;
   S16 retVal;
   RgrStaIndInfo *staInfo = 0L;

   ;



   cqiCount = &(ue->schCqiInfo.cqiCount);
   ue->schCqiInfo.cqiRept[(*cqiCount)++] =
                  *ueCqiRpt;



   if(((ue)->schCqiInfo.cqiCount >= (ue)->cqiReptCfgInfo.numColltdCqiRept ))
   {

      retVal = rgSCHUtlAllocSBuf (cell->instIdx,(Data**)&staInfo,
               sizeof(RgrStaIndInfo));
      if (retVal != 0)
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLevE(0xbb0057,L_ERROR,DBG_CELLID, cell->cellId,ue->ueId, 0, 0, 0,                                                                  "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c"         ,                                                                  31600         , "Could not " "allocate memory for sending StaInd CRNTI:%d", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                                   ;
         return(retVal);
      }
      retVal = rgSCHUtlFillSndStaInd(cell, ue, staInfo,
            ue->cqiReptCfgInfo.numColltdCqiRept);
      return(retVal);

   }

   return(0);
}
 Void rgSCHCmnChkRetxAllowDtx
(
RgSchCellCb *cell,
RgSchUeCb *ueCb,
RgSchDlHqProcCb *proc,
Bool *reTxAllwd
)







{
   ;


   *reTxAllwd = 1;

   if ((proc->tbInfo[0].isAckNackDtx == 4))
   {
       *reTxAllwd = 0;
   }

   return;
}
static U16 rgSCHCmnGetSiSetId
(
U16 sfn,
U8 sf,
U16 minPeriodicity
)






{


    return(((sfn * 10) + sf) / (minPeriodicity * 10));
}
 Void rgSCHCmnUpdUeDataIndLcg
(
RgSchCellCb *cell,
RgSchUeCb *ue,
RgInfUeDatInd *datInd
)






{
   U32 idx = 0;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   Inst inst = cell->instIdx;


   ;;

   for (idx = 0; (idx < 4 - 1); idx++)
   {
      if (datInd->lcgInfo[idx].bytesRcvd != 0)
      {
         U8 lcgId = datInd->lcgInfo[idx].lcgId;
         U32 bytesRcvd = datInd->lcgInfo[idx].bytesRcvd;

         if (((&ue->ul.lcgArr[lcgId])->lcgId != 255))
         {
            RgSchCmnLcg *cmnLcg = ((RgSchCmnLcg *)(ue->ul.lcgArr[lcgId].sch));
            if (((cmnLcg->cfgdGbr) != 0))
            {
               if(bytesRcvd > cmnLcg->effGbr)
               {
                  bytesRcvd -= cmnLcg->effGbr;
                  cmnLcg->effDeltaMbr = (cmnLcg->effDeltaMbr > bytesRcvd) ?
                                        (cmnLcg->effDeltaMbr - bytesRcvd) : (0);
                  cmnLcg->effGbr = 0;
               }
               else
               {
                  cmnLcg->effGbr -= bytesRcvd;
               }

               cmnLcg->reportedBs = (cmnLcg->reportedBs > datInd->lcgInfo[idx].bytesRcvd) ?
                                    (cmnLcg->reportedBs - datInd->lcgInfo[idx].bytesRcvd) : (0);
               cmnLcg->bs = ((cmnLcg->reportedBs) <= (cmnLcg->effGbr+cmnLcg->effDeltaMbr) ? (cmnLcg->reportedBs) : (cmnLcg->effGbr+cmnLcg->effDeltaMbr));
            }
            else if(lcgId != 0)
            {
               ue->ul.effAmbr = (ue->ul.effAmbr > datInd->lcgInfo[idx].bytesRcvd) ?
                               (ue->ul.effAmbr - datInd->lcgInfo[idx].bytesRcvd) : (0);
               cmnLcg->reportedBs = (cmnLcg->reportedBs > datInd->lcgInfo[idx].bytesRcvd) ?
                                    (cmnLcg->reportedBs - datInd->lcgInfo[idx].bytesRcvd) : (0);
               cmnLcg->bs = ((cmnLcg->reportedBs) <= (ue->ul.effAmbr) ? (cmnLcg->reportedBs) : (ue->ul.effAmbr));
               ue->ul.nonGbrLcgBs = (ue->ul.nonGbrLcgBs > datInd->lcgInfo[idx].bytesRcvd) ?
                                   (ue->ul.nonGbrLcgBs - datInd->lcgInfo[idx].bytesRcvd) : (0);
            }
            ue->ul.nonLcg0Bs = (ue->ul.nonLcg0Bs > datInd->lcgInfo[idx].bytesRcvd) ?
                              (ue->ul.nonLcg0Bs - datInd->lcgInfo[idx].bytesRcvd) : (0);
         }
      }
      else
      {
         break;
      }
   }
   if (cellSch->apisUl->rgSCHRgrUlLcgUpd(cell, ue, datInd) != 0)
   {
      { if ((&rgSchCb[inst].rgSchInit)->dbgMask & ((0x00000100 << 1))) { snprintf((&rgSchCb[inst].rgSchInit)->prntBuf, 255, "[%s %d:0x%x:%x] %s:%d ", "MAC Scheduler", (&rgSchCb[inst].rgSchInit)->procId, (&rgSchCb[inst].rgSchInit)->ent, (&rgSchCb[inst].rgSchInit)->inst, "/home/mrehwald/Desktop/Radisys/lte_enb/src/ltemac/rg_sch_cmn.c", 31945); SPrint((&rgSchCb[inst].rgSchInit)->prntBuf); sprintf (rgSchCb[inst].rgSchInit.prntBuf, "\n rgSCHCmnUpdUeDataIndLcg(): rgSCHRgrUlLcgUpd returned failure"); SPrint((&rgSchCb[inst].rgSchInit)->prntBuf); } };
   }
}
static Void rgSCHCmnInitRbAlloc
(
RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));
   CmLteTimingInfo frm;
   RgSchDlSf *dlSf;

   ;;


   rgSCHCmnInitDlRbAllocInfo(&cellSch->allocInfo);


   frm = cell->crntTime;
   do { if ((frm.subframe += (2 + 0)) > 9) { frm.sfn = ((frm.sfn) + 1) & 0x03ff; frm.subframe -= 10; }} while(0);
   cellSch->dl.time = frm;
   dlSf = rgSCHUtlSubFrmGet(cell, frm);
   dlSf->remUeCnt = cellSch->dl.maxUePerDlSf;

   cellSch->allocInfo.dedAlloc.dedDlSf = dlSf;
   cellSch->allocInfo.msg4Alloc.msg4DlSf = dlSf;



   if(RGR_ENABLE == cell->lteAdvCb.absCfg.status)
   {
      cell->lteAdvCb.absPatternDlIdx =
         ((frm.sfn*10) + frm.subframe) % 40;
      cell->lteAdvCb.absDlSfInfo = (RgSchAbsSfEnum)(cell->lteAdvCb.absCfg.absPattern[
            cell->lteAdvCb.absPatternDlIdx]);

   }
   else
   {
      cell->lteAdvCb.absDlSfInfo = RG_SCH_ABS_DISABLED;
   }



   cellSch->allocInfo.ccchSduAlloc.ccchSduDlSf = dlSf;



   rgSCHCmnSpsDlUpdDlSfAllocWithSps(cell, frm, dlSf);

   return;
}
static Void rgSCHCmnSendTxModeInd
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 newTxMode
)






{
   RgmTransModeInd *txModeChgInd;
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));

   ;;

   if(!(ueDl->mimoInfo.forceTD & 0x04))
   {

      if(SGetSBuf(cell->rgmSap->sapCfg.sapPst.region,
               cell->rgmSap->sapCfg.sapPst.pool, (Data**)&txModeChgInd,
               sizeof(RgmTransModeInd)) != 0)
      {
         return;
      }
      { txModeChgInd->usCrnti = ue->ueId; txModeChgInd->bCellId = cell->cellId; txModeChgInd->eMode = newTxMode - 1;};
      RgUiRgmChangeTransModeInd(&(cell->rgmSap->sapCfg.sapPst),
            cell->rgmSap->sapCfg.suId, txModeChgInd);
   }

   ue->mimoInfo.txModUpChgFactor = 0;
   ue->mimoInfo.txModDownChgFactor = 0;
   ueDl->laCb[0].deltaiTbs = 0;

   return;
}
 Void rgSchCheckAndTriggerModeChange
(
RgSchCellCb *cell,
RgSchUeCb *ue,
U8 reportediTbs,
U8 previTbs,
U8 maxiTbs
)
{
   RgrTxMode txMode;
   RgrTxMode modTxMode;

   ;;

   txMode = ue->mimoInfo.txMode;



   if(RGR_UE_TM_4 == txMode)
   {
      if((previTbs <= reportediTbs) && ((reportediTbs - previTbs) >= 10))
      {
         ue->mimoInfo.txModDownChgFactor += 1;
      }
      else
      {
         ue->mimoInfo.txModDownChgFactor -= 1;
      }

      ue->mimoInfo.txModDownChgFactor =
         ((ue->mimoInfo.txModDownChgFactor) >= (-(100)) ? (ue->mimoInfo.txModDownChgFactor) : (-(100)));

      if(ue->mimoInfo.txModDownChgFactor >= 100)
      {

         modTxMode = RGR_UE_TM_3;
         rgSCHCmnSendTxModeInd(cell, ue, modTxMode);
      }
   }



   if(RGR_UE_TM_3 == txMode)
   {
      if((previTbs > reportediTbs) || (maxiTbs == previTbs))
      {
         ue->mimoInfo.txModUpChgFactor += 1;
      }
      else
      {
         ue->mimoInfo.txModUpChgFactor -= 1;
      }

      ue->mimoInfo.txModUpChgFactor =
         ((ue->mimoInfo.txModUpChgFactor) >= (-(150)) ? (ue->mimoInfo.txModUpChgFactor) : (-(150)));


      if(ue->mimoInfo.txModUpChgFactor >= 150)
      {

         modTxMode = RGR_UE_TM_4;
         rgSCHCmnSendTxModeInd(cell, ue, modTxMode);
      }
   }

   return;
}
 Bool rgSCHCmnIsDlCsgPrio
(
RgSchCellCb *cell
)




{

   RgSchCmnDlCell *cmnDlCell = &(((RgSchCmnCell *)((cell)->sc.sch))->dl);

   ;

   if(RGR_CELL_ACCS_HYBRID != rgSchCb[cell->instIdx].rgrSchedEnbCfg.accsMode)
   {
      return(0);
   }
   else
   {
      if(((cmnDlCell->ncsgPrbCnt * 100) / cmnDlCell->totPrbCnt) < cell->minDlResNonCsg)
      {
         return(0);
      }
      else
      {
         return(1);
      }
   }
}
 Bool rgSCHCmnIsUlCsgPrio
(
RgSchCellCb *cell
)




{
   RgSchCmnUlCell *cmnUlCell = &(((RgSchCmnCell *)((cell)->sc.sch))->ul);

   ;


   if(RGR_CELL_ACCS_HYBRID != rgSchCb[cell->instIdx].rgrSchedEnbCfg.accsMode)
   {
      return(0);
   }
   else
   {
      if (((cmnUlCell->ncsgPrbCnt * 100) /cmnUlCell->totPrbCnt) < cell->minUlResNonCsg)
      {
         return(0);
      }
      else
      {
         return(1);
      }
   }
}
 Void rgSCHCmnDlSpsSch
(
 RgSchCellCb *cell
)




{
   RgSchDlSf *dlSf;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;




   dlSf = rgSCHUtlSubFrmGet(cell, cellSch->dl.time);


   rgSCHCmnSpsDlSched(cell, &cellSch->allocInfo);

   if ((dlSf->type2Start != 0) &&
         (dlSf->type2Start == (((cell->spsCellCfg.maxSpsDlBw + cell->rbgSize - 1)/cell->rbgSize) * cell->rbgSize)))
   {
      RgSchCmnDlCellSpsInfo *dlSpsCell = &(((RgSchCmnCell *)((cell)->sc.sch))->dl.dlSpsInfo);
      CmLteTimingInfo schdTime = cell->crntTime;
      U32 idx1 = 0, count = 0, raType2Mask = 0, dlSpsSfIdx = 0;
      U8 oldType2Start = dlSf->type2Start;

      dlSf->type2Start = 0;
      dlSf->type2End = 0;
      do { if ((schdTime.subframe += (2 + 0)) > 9) { schdTime.sfn = ((schdTime.sfn) + 1) & 0x03ff; schdTime.subframe -= 10; }} while(0);
      dlSpsSfIdx = (schdTime.sfn * 10 + schdTime.subframe) % dlSpsCell->spsPrdLcmVal;
      for (idx1 = 4; idx1 > 0; idx1--)
      {
         if (0 != (raType2Mask = dlSpsCell->spsSfTbl[dlSpsSfIdx].
                  spsAllocInfo.raType2Mask[idx1 - 1]))
         {
            while (!(raType2Mask & 0x01))
            {
               count++;
               raType2Mask >>=1;
            }
            dlSf->type2Start = (32 - count) + (( idx1 -1) * 32);
            break;
         }
      }

      dlSf->bwAlloced -= (oldType2Start - dlSf->type2Start);
      dlSf->spsAllocdBw += (oldType2Start - dlSf->type2Start);
      dlSf->type2End = (((dlSf->type2Start) + (cell->rbgSize)-1) / (cell->rbgSize));
   }

   return;
}
 Void rgSchCmnPreDlSch
(
 RgSchCellCb **cell,
 U8 nCell,
 RgSchCellCb **cellLst
)






{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell[0])->sc.sch));
   RgSchDlSf *sf;
   U8 idx;

   ;;

   if(nCell > 8)
   {
      return;
   }

   if (cell[0]->isDlDataAllwd && (cell[0]->stopDlSch == 0))
   {

      cellSch->apisDl->rgSCHDlPreSched(cell[0]);




      for (idx = 0; idx < nCell; idx++)
      {
         U8 j;
         cellSch = ((RgSchCmnCell *)((cell[idx])->sc.sch));
         sf = cellSch->allocInfo.dedAlloc.dedDlSf;

         if(idx == 0)
         {
            cellLst[idx] = cell[idx];
            continue;
         }

         for(j = 0; j < idx; j++)
         {
            RgSchCmnCell *cmnCell = ((RgSchCmnCell *)((cellLst[j])->sc.sch));
            RgSchDlSf *subfrm = cmnCell->allocInfo.dedAlloc.dedDlSf;

            if(sf->remUeCnt < subfrm->remUeCnt)
            {
               U8 k;
               for(k = idx; k > j; k--)
               {
                  cellLst[k] = cellLst[k-1];
               }
               break;
            }
         }
         cellLst[j] = cell[idx];
      }
   }
   else
   {
      for (idx = 0; idx < nCell; idx++)
      {
         cellLst[idx] = cell[idx];
      }
   }
   return;
}
 Void rgSchCmnPstDlSch
(
 RgSchCellCb *cell
)




{
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;

   if (cell->isDlDataAllwd && (cell->stopDlSch == 0))
   {
      cellSch->apisDl->rgSCHDlPstSched(cell->instIdx);
   }
}
 Void rgSCHCmnDlSch
(
 RgSchCellCb *cell
 )




{
   RgSchDlSf *dlSf;
   RgSchCmnCell *cellSch = ((RgSchCmnCell *)((cell)->sc.sch));

   ;;

   dlSf = rgSCHUtlSubFrmGet(cell, cellSch->dl.time);


   if((RG_SCH_ABS_ENABLED_ABS_SF == cell->lteAdvCb.absDlSfInfo) &&
                           (cell->lteAdvCb.absCfg.absPatternType & RGR_ABS_MUTE))
   {

   }
   else
   {

      cellSch->apisDl->rgSCHDlNewSched(cell, &cellSch->allocInfo);
   }



   rgSCHCmnDlRbAlloc(cell, &cellSch->allocInfo);


   rgSCHCmnDlAllocFnlz(cell);





   rgSCHCmnGenPdcchOrder(cell, dlSf);


   rgSCHCmnGrpPwrCntrlPucch(cell, dlSf);

   return;
}
 Void rgSchCmnDlSfHqDel
(
RgSchUeCb *ue,
RgSchCellCb *cell
)





{
   CmLList *node;
   RgSchDlHqProcCb *hqP;
   U32 i;

   for (i=0; i< ue->dl.numHqDlSfInfo;i++)
   {
      node = ue->dl.dlSfHqInfo[i].hqPLst.first;
      while (node)
      {
         hqP = (RgSchDlHqProcCb *)node->node;
         node = node->next;
         if (hqP->subFrm != 0L)
         {
            if (ue->dl.dlSfHqInfo[i].dlSfUeLnk.node)
            {

               ue->dl.dlSfHqInfo[i].dlSfUeLnk.node = 0L;
            }
         }
      }
   }



}
 Bool rgSchIsN1PucchResAvail
(
  CmLListCp *lst,
  RgSchUeCb *ue,
  U8 n1Idx,
  U8 resCount
)







{
   CmLList *node;
   RgSchN1PucchResCb *n1Pucch;
   U16 n1PucchIdx1 = ue->n1PucchF1bResCb.cw1N1Res[n1Idx].n1PucchIdx;
   U16 n1PucchIdx2;


   if(lst->count == 0)
      return(1);


   node = lst->first;
   while(node)
   {
      n1Pucch = (RgSchN1PucchResCb *)node->node;
      if(n1PucchIdx1 == n1Pucch->n1PucchIdx)
      {
         return(0);
      }
      node = node->next;
   }


   if(resCount == 2)
   {
      n1PucchIdx2 = ue->n1PucchF1bResCb.cw2N1Res[n1Idx].n1PucchIdx;
      node = lst->first;
      while(node)
      {
         n1Pucch = (RgSchN1PucchResCb *)node->node;
         if(n1PucchIdx2 == n1Pucch->n1PucchIdx)
         {
            return(0);
         }
         node = node->next;
      }
   }

   return(1);
}
 S16 rgSCHCmnDlAllocErrIndTxRb
(
RgSchCellCb *cell,
RgSchDlSf *subFrm,
RgSchUeCb *ue,
U32 bo,
U32 *effBo,
RgSchDlHqProcCb *proc,
RgSchCmnDlRbAllocInfo *cellWdAllocInfo
)
{
   RgrTxMode ueTxMode;
   RgSchDlRbAlloc *allocInfo;
   U8 numRb;
   RgSchDlHqTbCb *tb1, *tb2;
   U8 precInfo;
   Bool swpFlg = 0;
   U8 noTxLyrs;
   U8 precInfoAntIdx;
   RgSchCmnDlUe *ueDl = (&(((RgSchCmnUe *)((ue->cellInfo[ue->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->sch))->dl));


   ;;

   if ( !((((cell->crntTime)).sfn == ((ue->dl.lstSchTime)).sfn) && (((cell->crntTime)).subframe == ((ue->dl.lstSchTime)).subframe)))
   {
      ue->dl.aggTbBits = 0;
   }

   *effBo = 0;

   if (subFrm->bw <= subFrm->bwAssigned)
   {
      return(1);
   }
   numRb = proc->tbInfo[0].dlGrnt.numRb;

   if ((S16)numRb > (S16)(subFrm->bw - subFrm->bwAssigned))
   {
      return(1);
   }

   tb1 = &proc->tbInfo[0];
   tb2 = &proc->tbInfo[1];

   allocInfo = &(((ue)->cellInfo[(ue)->cellIdToCellIdxMap [(U8)((cell->cellId >= rgSchCb[cell->instIdx].genCfg.startCellId) ? (cell->cellId - rgSchCb[cell->instIdx].genCfg.startCellId)&(8 -1): 0)]])->dlAllocCb);;

   allocInfo->dciFormat = rgSCHCmnSlctPdcchFrmt(cell, ue,
                                       &allocInfo->raType);

   ueTxMode = ue->mimoInfo.txMode;
   switch(ueTxMode)
   {
      case RGR_UE_TM_1:
      case RGR_UE_TM_2:
      {
         { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = tb1->tbSz; (&allocInfo->tbInfo[0])->iTbs = 0; (&allocInfo->tbInfo[0])->imcs = tb1->dlGrnt.iMcs; (&allocInfo->tbInfo[0])->tbCb = tb1; (&allocInfo->tbInfo[0])->noLyr = tb1->numLyrs;}
                                                         ;
         *effBo = tb1->tbSz;
      }
      break;

      case RGR_UE_TM_3:
      {
         { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = tb1->tbSz; (&allocInfo->tbInfo[0])->iTbs = 0; (&allocInfo->tbInfo[0])->imcs = tb1->dlGrnt.iMcs; (&allocInfo->tbInfo[0])->tbCb = tb1; (&allocInfo->tbInfo[0])->noLyr = tb1->numLyrs;}
                                                         ;
         { (&allocInfo->tbInfo[1])->schdlngForTb = 1; (&allocInfo->tbInfo[1])->bytesReq = tb2->tbSz; (&allocInfo->tbInfo[1])->iTbs = 0; (&allocInfo->tbInfo[1])->imcs = tb2->dlGrnt.iMcs; (&allocInfo->tbInfo[1])->tbCb = tb2; (&allocInfo->tbInfo[1])->noLyr = tb2->numLyrs;}
                                                         ;

         noTxLyrs = proc->tbInfo[0].numLyrs + proc->tbInfo[1].numLyrs;
         precInfoAntIdx = cell->numTxAntPorts/2 - 1;
         precInfo = (getPrecInfoFunc[0][precInfoAntIdx])(cell, ue, noTxLyrs, 1);

         { allocInfo->rbsReq = numRb; allocInfo->mimoAllocInfo.swpFlg = swpFlg; allocInfo->mimoAllocInfo.precIdxInfo = precInfo; allocInfo->mimoAllocInfo.numTxLyrs = noTxLyrs; allocInfo->dlSf = subFrm;}
                                            ;
         *effBo = tb1->tbSz + tb2->tbSz;

      }
      break;

      case RGR_UE_TM_4:
      {
         { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = tb1->tbSz; (&allocInfo->tbInfo[0])->iTbs = 0; (&allocInfo->tbInfo[0])->imcs = tb1->dlGrnt.iMcs; (&allocInfo->tbInfo[0])->tbCb = tb1; (&allocInfo->tbInfo[0])->noLyr = tb1->numLyrs;}
                                                         ;
         { (&allocInfo->tbInfo[1])->schdlngForTb = 1; (&allocInfo->tbInfo[1])->bytesReq = tb2->tbSz; (&allocInfo->tbInfo[1])->iTbs = 0; (&allocInfo->tbInfo[1])->imcs = tb2->dlGrnt.iMcs; (&allocInfo->tbInfo[1])->tbCb = tb2; (&allocInfo->tbInfo[1])->noLyr = tb2->numLyrs;}
                                                         ;

         noTxLyrs = proc->tbInfo[0].numLyrs + proc->tbInfo[1].numLyrs;
         precInfo = 0;

         { allocInfo->rbsReq = numRb; allocInfo->mimoAllocInfo.swpFlg = swpFlg; allocInfo->mimoAllocInfo.precIdxInfo = precInfo; allocInfo->mimoAllocInfo.numTxLyrs = noTxLyrs; allocInfo->dlSf = subFrm;}
                                            ;
         *effBo = tb1->tbSz + tb2->tbSz;

      }
      break;

      case RGR_UE_TM_5:
      break;

      case RGR_UE_TM_6:
      {
         { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = tb1->tbSz; (&allocInfo->tbInfo[0])->iTbs = 0; (&allocInfo->tbInfo[0])->imcs = tb1->dlGrnt.iMcs; (&allocInfo->tbInfo[0])->tbCb = tb1; (&allocInfo->tbInfo[0])->noLyr = tb1->numLyrs;}
                                                         ;
         allocInfo->mimoAllocInfo.precIdxInfo |= ue->mimoInfo.puschFdbkVld << 4;
         allocInfo->mimoAllocInfo.precIdxInfo |= ueDl->mimoInfo.pmi;
         *effBo = tb1->tbSz;

      }
      break;
      case RGR_UE_TM_7:
      {
         { (&allocInfo->tbInfo[0])->schdlngForTb = 1; (&allocInfo->tbInfo[0])->bytesReq = tb1->tbSz; (&allocInfo->tbInfo[0])->iTbs = 0; (&allocInfo->tbInfo[0])->imcs = tb1->dlGrnt.iMcs; (&allocInfo->tbInfo[0])->tbCb = tb1; (&allocInfo->tbInfo[0])->noLyr = tb1->numLyrs;}
                                                         ;
         *effBo = tb1->tbSz;
      }
      break;
      case RGR_UE_TM_8:
      break;




      default:
      break;
   }


   subFrm->bwAssigned += numRb;

   allocInfo->rbsReq = numRb;
   allocInfo->dlSf = subFrm;

   rgSCHCmnDlRbInfoAddUeErrIndTx(cell, cellWdAllocInfo, ue, proc);

   return(0);
}
