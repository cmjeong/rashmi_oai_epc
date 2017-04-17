static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_MODULE_ID=128;
static int RLOG_FILE_ID=160;


extern "C" {
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
typedef S8 (*PFS8) (void );
typedef S16 (*PFS16) (void );
typedef S32 (*PFS32) (void );
typedef void (*PFVOID) (void );
typedef void ( *PIF) (void );
typedef U32 MFTYPE;




typedef S8 *ARGTYPE;
}

extern "C" {









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

extern "C" {



extern int clone (int (*__fn) (void *__arg), void *__child_stack,
    int __flags, void *__arg, ...) throw ();


extern int unshare (int __flags) throw ();


extern int sched_getcpu (void) throw ();


extern int setns (int __fd, int __nstype) throw ();



}







struct __sched_param
  {
    int __sched_priority;
  };
typedef unsigned long int __cpu_mask;






typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;
extern "C" {

extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
  throw ();
extern cpu_set_t *__sched_cpualloc (size_t __count) throw () ;
extern void __sched_cpufree (cpu_set_t *__set) throw ();

}




extern "C" {


extern int sched_setparam (__pid_t __pid, const struct sched_param *__param)
     throw ();


extern int sched_getparam (__pid_t __pid, struct sched_param *__param) throw ();


extern int sched_setscheduler (__pid_t __pid, int __policy,
          const struct sched_param *__param) throw ();


extern int sched_getscheduler (__pid_t __pid) throw ();


extern int sched_yield (void) throw ();


extern int sched_get_priority_max (int __algorithm) throw ();


extern int sched_get_priority_min (int __algorithm) throw ();


extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) throw ();
extern int sched_setaffinity (__pid_t __pid, size_t __cpusetsize,
         const cpu_set_t *__cpuset) throw ();


extern int sched_getaffinity (__pid_t __pid, size_t __cpusetsize,
         cpu_set_t *__cpuset) throw ();


}
extern "C" {










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

extern "C" {


extern int clock_adjtime (__clockid_t __clock_id, struct timex *__utx) throw ();

}


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



extern clock_t clock (void) throw ();


extern time_t time (time_t *__timer) throw ();


extern double difftime (time_t __time1, time_t __time0)
     throw () __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) throw ();





extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) throw ();





extern char *strptime (const char *__restrict __s,
         const char *__restrict __fmt, struct tm *__tp)
     throw ();





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
     __locale_t __loc) throw ();



extern char *strptime_l (const char *__restrict __s,
    const char *__restrict __fmt, struct tm *__tp,
    __locale_t __loc) throw ();






extern struct tm *gmtime (const time_t *__timer) throw ();



extern struct tm *localtime (const time_t *__timer) throw ();





extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) throw ();



extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) throw ();





extern char *asctime (const struct tm *__tp) throw ();


extern char *ctime (const time_t *__timer) throw ();







extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) throw ();


extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) throw ();




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) throw ();



extern int daylight;
extern long int timezone;





extern int stime (const time_t *__when) throw ();
extern time_t timegm (struct tm *__tp) throw ();


extern time_t timelocal (struct tm *__tp) throw ();


extern int dysize (int __year) throw () __attribute__ ((__const__));
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) throw ();


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) throw ();


extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     throw ();






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) throw ();




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) throw ();


extern int timer_delete (timer_t __timerid) throw ();


extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) throw ();


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     throw ();


extern int timer_getoverrun (timer_t __timerid) throw ();





extern int timespec_get (struct timespec *__ts, int __base)
     throw () __attribute__ ((__nonnull__ (1)));
extern int getdate_err;
extern struct tm *getdate (const char *__string);
extern int getdate_r (const char *__restrict __string,
        struct tm *__restrict __resbufp);


}

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
extern "C" {




extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) throw () __attribute__ ((__nonnull__ (1, 3)));





extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));







extern int pthread_join (pthread_t __th, void **__thread_return);




extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) throw ();







extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
     const struct timespec *__abstime);






extern int pthread_detach (pthread_t __th) throw ();



extern pthread_t pthread_self (void) throw () __attribute__ ((__const__));


extern int pthread_equal (pthread_t __thread1, pthread_t __thread2)
  throw () __attribute__ ((__const__));







extern int pthread_attr_init (pthread_attr_t *__attr) throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_destroy (pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getdetachstate (const pthread_attr_t *__attr,
     int *__detachstate)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
     int __detachstate)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getguardsize (const pthread_attr_t *__attr,
          size_t *__guardsize)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
          size_t __guardsize)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getschedparam (const pthread_attr_t *__restrict __attr,
           struct sched_param *__restrict __param)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedparam (pthread_attr_t *__restrict __attr,
           const struct sched_param *__restrict
           __param) throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_getschedpolicy (const pthread_attr_t *__restrict
     __attr, int *__restrict __policy)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getinheritsched (const pthread_attr_t *__restrict
      __attr, int *__restrict __inherit)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
      int __inherit)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getscope (const pthread_attr_t *__restrict __attr,
      int *__restrict __scope)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getstackaddr (const pthread_attr_t *__restrict
          __attr, void **__restrict __stackaddr)
     throw () __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__deprecated__));





extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
          void *__stackaddr)
     throw () __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__));


extern int pthread_attr_getstacksize (const pthread_attr_t *__restrict
          __attr, size_t *__restrict __stacksize)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
          size_t __stacksize)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getstack (const pthread_attr_t *__restrict __attr,
      void **__restrict __stackaddr,
      size_t *__restrict __stacksize)
     throw () __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
      size_t __stacksize) throw () __attribute__ ((__nonnull__ (1)));





extern int pthread_attr_setaffinity_np (pthread_attr_t *__attr,
     size_t __cpusetsize,
     const cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (1, 3)));



extern int pthread_attr_getaffinity_np (const pthread_attr_t *__attr,
     size_t __cpusetsize,
     cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (1, 3)));


extern int pthread_getattr_default_np (pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_setattr_default_np (const pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));




extern int pthread_getattr_np (pthread_t __th, pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (2)));







extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
      const struct sched_param *__param)
     throw () __attribute__ ((__nonnull__ (3)));


extern int pthread_getschedparam (pthread_t __target_thread,
      int *__restrict __policy,
      struct sched_param *__restrict __param)
     throw () __attribute__ ((__nonnull__ (2, 3)));


extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     throw ();




extern int pthread_getname_np (pthread_t __target_thread, char *__buf,
          size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2)));


extern int pthread_setname_np (pthread_t __target_thread, const char *__name)
     throw () __attribute__ ((__nonnull__ (2)));





extern int pthread_getconcurrency (void) throw ();


extern int pthread_setconcurrency (int __level) throw ();







extern int pthread_yield (void) throw ();




extern int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize,
       const cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (3)));


extern int pthread_getaffinity_np (pthread_t __th, size_t __cpusetsize,
       cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (3)));
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




class __pthread_cleanup_class
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;

 public:
  __pthread_cleanup_class (void (*__fct) (void *), void *__arg)
    : __cancel_routine (__fct), __cancel_arg (__arg), __do_it (1) { }
  ~__pthread_cleanup_class () { if (__do_it) __cancel_routine (__cancel_arg); }
  void __setdoit (int __newval) { __do_it = __newval; }
  void __defer () { pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED,
        &__cancel_type); }
  void __restore () const { pthread_setcanceltype (__cancel_type, 0); }
};
struct __jmp_buf_tag;
extern int __sigsetjmp (struct __jmp_buf_tag *__env, int __savemask) throw ();





extern int pthread_mutex_init (pthread_mutex_t *__mutex,
          const pthread_mutexattr_t *__mutexattr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
        const struct timespec *__restrict
        __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_getprioceiling (const pthread_mutex_t *
      __restrict __mutex,
      int *__restrict __prioceiling)
     throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
      int __prioceiling,
      int *__restrict __old_ceiling)
     throw () __attribute__ ((__nonnull__ (1, 3)));




extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));

extern int pthread_mutex_consistent_np (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t *
      __restrict __attr,
      int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
      int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_gettype (const pthread_mutexattr_t *__restrict
          __attr, int *__restrict __kind)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *
       __restrict __attr,
       int *__restrict __protocol)
     throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
       int __protocol)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *
          __restrict __attr,
          int *__restrict __prioceiling)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
          int __prioceiling)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getrobust (const pthread_mutexattr_t *__attr,
     int *__robustness)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern int pthread_mutexattr_getrobust_np (const pthread_mutexattr_t *__attr,
        int *__robustness)
     throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
     int __robustness)
     throw () __attribute__ ((__nonnull__ (1)));

extern int pthread_mutexattr_setrobust_np (pthread_mutexattr_t *__attr,
        int __robustness)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock,
    const pthread_rwlockattr_t *__restrict
    __attr) throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));





extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
       int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getkind_np (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pref)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
       int __pref) throw () __attribute__ ((__nonnull__ (1)));







extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
         const pthread_condattr_t *__restrict __cond_attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_destroy (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_signal (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));






extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
         pthread_mutex_t *__restrict __mutex)
     __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
       pthread_mutex_t *__restrict __mutex,
       const struct timespec *__restrict __abstime)
     __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_condattr_init (pthread_condattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_getpshared (const pthread_condattr_t *
     __restrict __attr,
     int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
     int __pshared) throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_condattr_getclock (const pthread_condattr_t *
          __restrict __attr,
          __clockid_t *__restrict __clock_id)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
          __clockid_t __clock_id)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));






extern int pthread_barrier_init (pthread_barrier_t *__restrict __barrier,
     const pthread_barrierattr_t *__restrict
     __attr, unsigned int __count)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_getpshared (const pthread_barrierattr_t *
        __restrict __attr,
        int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
        int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_key_create (pthread_key_t *__key,
          void (*__destr_function) (void *))
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_key_delete (pthread_key_t __key) throw ();


extern void *pthread_getspecific (pthread_key_t __key) throw ();


extern int pthread_setspecific (pthread_key_t __key,
    const void *__pointer) throw () ;




extern int pthread_getcpuclockid (pthread_t __thread_id,
      __clockid_t *__clock_id)
     throw () __attribute__ ((__nonnull__ (2)));
extern int pthread_atfork (void (*__prepare) (void),
      void (*__parent) (void),
      void (*__child) (void)) throw ();
}
extern "C" {





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
extern "C" {
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
}


extern "C" {

__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     throw () __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     throw () __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     throw () __attribute__ ((__const__));
}





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
}






typedef union
{
  char __size[16];
  long int __align;
} sem_t;


extern "C" {



extern int sem_init (sem_t *__sem, int __pshared, unsigned int __value)
     throw ();

extern int sem_destroy (sem_t *__sem) throw ();


extern sem_t *sem_open (const char *__name, int __oflag, ...) throw ();


extern int sem_close (sem_t *__sem) throw ();


extern int sem_unlink (const char *__name) throw ();





extern int sem_wait (sem_t *__sem);






extern int sem_timedwait (sem_t *__restrict __sem,
     const struct timespec *__restrict __abstime);



extern int sem_trywait (sem_t *__sem) throw ();


extern int sem_post (sem_t *__sem) throw ();


extern int sem_getvalue (sem_t *__restrict __sem, int *__restrict __sval)
     throw ();


}
extern "C" {



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




extern "C" {


extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) throw ();
extern int _IO_ferror (_IO_FILE *__fp) throw ();

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) throw ();
extern void _IO_funlockfile (_IO_FILE *) throw ();
extern int _IO_ftrylockfile (_IO_FILE *) throw ();
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) throw ();
}




typedef __gnuc_va_list va_list;


typedef _G_fpos_t fpos_t;





typedef _G_fpos64_t fpos64_t;



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;







extern int remove (const char *__filename) throw ();

extern int rename (const char *__old, const char *__new) throw ();




extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) throw ();








extern FILE *tmpfile (void) ;
extern FILE *tmpfile64 (void) ;



extern char *tmpnam (char *__s) throw () ;





extern char *tmpnam_r (char *__s) throw () ;
extern char *tempnam (const char *__dir, const char *__pfx)
     throw () __attribute__ ((__malloc__)) ;








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

extern int fflush_unlocked (FILE *__stream);
extern int fcloseall (void);









extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;


extern FILE *fopen64 (const char *__restrict __filename,
        const char *__restrict __modes) ;
extern FILE *freopen64 (const char *__restrict __filename,
   const char *__restrict __modes,
   FILE *__restrict __stream) ;




extern FILE *fdopen (int __fd, const char *__modes) throw () ;





extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     _IO_cookie_io_functions_t __io_funcs) throw () ;




extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  throw () ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) throw () ;






extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) throw ();



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) throw ();





extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) throw ();


extern void setlinebuf (FILE *__stream) throw ();








extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) throw ();





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) throw ();





extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     throw () __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     throw () __attribute__ ((__format__ (__printf__, 3, 0)));






extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     throw () __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     throw () __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     throw () __attribute__ ((__format__ (__printf__, 2, 3))) ;




extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));








extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) throw ();








extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     throw () __attribute__ ((__format__ (__scanf__, 2, 0)));









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
     ;

extern char *fgets_unlocked (char *__restrict __s, int __n,
        FILE *__restrict __stream) ;
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;








extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

extern int fputs_unlocked (const char *__restrict __s,
      FILE *__restrict __stream);
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);

extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;






extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);



extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) ;
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);




extern void clearerr (FILE *__stream) throw ();

extern int feof (FILE *__stream) throw () ;

extern int ferror (FILE *__stream) throw () ;




extern void clearerr_unlocked (FILE *__stream) throw ();
extern int feof_unlocked (FILE *__stream) throw () ;
extern int ferror_unlocked (FILE *__stream) throw () ;








extern void perror (const char *__s);






extern int sys_nerr;
extern const char *const sys_errlist[];


extern int _sys_nerr;
extern const char *const _sys_errlist[];




extern int fileno (FILE *__stream) throw () ;




extern int fileno_unlocked (FILE *__stream) throw () ;
extern FILE *popen (const char *__command, const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) throw ();





extern char *cuserid (char *__s);




struct obstack;


extern int obstack_printf (struct obstack *__restrict __obstack,
      const char *__restrict __format, ...)
     throw () __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
       const char *__restrict __format,
       __gnuc_va_list __args)
     throw () __attribute__ ((__format__ (__printf__, 2, 0)));







extern void flockfile (FILE *__stream) throw ();



extern int ftrylockfile (FILE *__stream) throw () ;


extern void funlockfile (FILE *__stream) throw ();
}

extern "C" {













extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) throw () __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));






extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));





extern void *memset (void *__s, int __c, size_t __n) throw () __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));



extern "C++"
{
extern void *memchr (void *__s, int __c, size_t __n)
      throw () __asm ("memchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const void *memchr (const void *__s, int __c, size_t __n)
      throw () __asm ("memchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}










extern "C++" void *rawmemchr (void *__s, int __c)
     throw () __asm ("rawmemchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const void *rawmemchr (const void *__s, int __c)
     throw () __asm ("rawmemchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));







extern "C++" void *memrchr (void *__s, int __c, size_t __n)
      throw () __asm ("memrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const void *memrchr (const void *__s, int __c, size_t __n)
      throw () __asm ("memrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));









extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) throw () __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (2)));

extern int strcoll_l (const char *__s1, const char *__s2, __locale_t __l)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    __locale_t __l) throw () __attribute__ ((__nonnull__ (2, 4)));




extern char *strdup (const char *__s)
     throw () __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     throw () __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));



extern "C++"
{
extern char *strchr (char *__s, int __c)
     throw () __asm ("strchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *strchr (const char *__s, int __c)
     throw () __asm ("strchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}






extern "C++"
{
extern char *strrchr (char *__s, int __c)
     throw () __asm ("strrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *strrchr (const char *__s, int __c)
     throw () __asm ("strrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}










extern "C++" char *strchrnul (char *__s, int __c)
     throw () __asm ("strchrnul") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const char *strchrnul (const char *__s, int __c)
     throw () __asm ("strchrnul") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));









extern size_t strcspn (const char *__s, const char *__reject)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern "C++"
{
extern char *strpbrk (char *__s, const char *__accept)
     throw () __asm ("strpbrk") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern const char *strpbrk (const char *__s, const char *__accept)
     throw () __asm ("strpbrk") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
}






extern "C++"
{
extern char *strstr (char *__haystack, const char *__needle)
     throw () __asm ("strstr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern const char *strstr (const char *__haystack, const char *__needle)
     throw () __asm ("strstr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
}







extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     throw () __attribute__ ((__nonnull__ (2)));




extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     throw () __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     throw () __attribute__ ((__nonnull__ (2, 3)));





extern "C++" char *strcasestr (char *__haystack, const char *__needle)
     throw () __asm ("strcasestr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern "C++" const char *strcasestr (const char *__haystack,
         const char *__needle)
     throw () __asm ("strcasestr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)));



extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));





extern size_t strlen (const char *__s)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strnlen (const char *__string, size_t __maxlen)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern char *strerror (int __errnum) throw ();

extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2))) ;





extern char *strerror_l (int __errnum, __locale_t __l) throw ();





extern void __bzero (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));



extern void bcopy (const void *__src, void *__dest, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));


extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));



extern "C++"
{
extern char *index (char *__s, int __c)
     throw () __asm ("index") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *index (const char *__s, int __c)
     throw () __asm ("index") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}







extern "C++"
{
extern char *rindex (char *__s, int __c)
     throw () __asm ("rindex") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *rindex (const char *__s, int __c)
     throw () __asm ("rindex") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}







extern int ffs (int __i) throw () __attribute__ ((__const__));




extern int ffsl (long int __l) throw () __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     throw () __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));





extern int strcasecmp_l (const char *__s1, const char *__s2,
    __locale_t __loc)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, __locale_t __loc)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));





extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) throw ();


extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern int strverscmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strfry (char *__string) throw () __attribute__ ((__nonnull__ (1)));


extern void *memfrob (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));







extern "C++" char *basename (char *__filename)
     throw () __asm ("basename") __attribute__ ((__nonnull__ (1)));
extern "C++" const char *basename (const char *__filename)
     throw () __asm ("basename") __attribute__ ((__nonnull__ (1)));
}

extern "C" {

extern "C" {


struct iovec
  {
    void *iov_base;
    size_t iov_len;
  };
extern "C" {


extern ssize_t process_vm_readv (pid_t __pid, const struct iovec *__lvec,
     unsigned long int __liovcnt,
     const struct iovec *__rvec,
     unsigned long int __riovcnt,
     unsigned long int __flags)
  throw ();


extern ssize_t process_vm_writev (pid_t __pid, const struct iovec *__lvec,
      unsigned long int __liovcnt,
      const struct iovec *__rvec,
      unsigned long int __riovcnt,
      unsigned long int __flags)
  throw ();

}
extern ssize_t readv (int __fd, const struct iovec *__iovec, int __count)
  ;
extern ssize_t writev (int __fd, const struct iovec *__iovec, int __count)
  ;
extern ssize_t preadv (int __fd, const struct iovec *__iovec, int __count,
         __off_t __offset) ;
extern ssize_t pwritev (int __fd, const struct iovec *__iovec, int __count,
   __off_t __offset) ;
extern ssize_t preadv64 (int __fd, const struct iovec *__iovec, int __count,
    __off64_t __offset) ;
extern ssize_t pwritev64 (int __fd, const struct iovec *__iovec, int __count,
     __off64_t __offset) ;



}














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
          struct cmsghdr *__cmsg) throw ();
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
struct mmsghdr
  {
    struct msghdr msg_hdr;
    unsigned int msg_len;

  };






extern int socket (int __domain, int __type, int __protocol) throw ();





extern int socketpair (int __domain, int __type, int __protocol,
         int __fds[2]) throw ();


extern int bind (int __fd, const struct sockaddr * __addr, socklen_t __len)
     throw ();


extern int getsockname (int __fd, struct sockaddr *__restrict __addr,
   socklen_t *__restrict __len) throw ();
extern int connect (int __fd, const struct sockaddr * __addr, socklen_t __len);



extern int getpeername (int __fd, struct sockaddr *__restrict __addr,
   socklen_t *__restrict __len) throw ();






extern ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);






extern ssize_t recv (int __fd, void *__buf, size_t __n, int __flags);






extern ssize_t sendto (int __fd, const void *__buf, size_t __n,
         int __flags, const struct sockaddr * __addr,
         socklen_t __addr_len);
extern ssize_t recvfrom (int __fd, void *__restrict __buf, size_t __n,
    int __flags, struct sockaddr *__restrict __addr,
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
         socklen_t *__restrict __optlen) throw ();




extern int setsockopt (int __fd, int __level, int __optname,
         const void *__optval, socklen_t __optlen) throw ();





extern int listen (int __fd, int __n) throw ();
extern int accept (int __fd, struct sockaddr *__restrict __addr,
     socklen_t *__restrict __addr_len);






extern int accept4 (int __fd, struct sockaddr *__restrict __addr,
      socklen_t *__restrict __addr_len, int __flags);
extern int shutdown (int __fd, int __how) throw ();




extern int sockatmark (int __fd) throw ();







extern int isfdtype (int __fd, int __fdtype) throw ();
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




extern "C" {


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
extern uint32_t ntohl (uint32_t __netlong) throw () __attribute__ ((__const__));
extern uint16_t ntohs (uint16_t __netshort)
     throw () __attribute__ ((__const__));
extern uint32_t htonl (uint32_t __hostlong)
     throw () __attribute__ ((__const__));
extern uint16_t htons (uint16_t __hostshort)
     throw () __attribute__ ((__const__));




extern int bindresvport (int __sockfd, struct sockaddr_in *__sock_in) throw ();


extern int bindresvport6 (int __sockfd, struct sockaddr_in6 *__sock_in)
     throw ();
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
     throw () __attribute__ ((__deprecated__));
extern int inet6_option_init (void *__bp, struct cmsghdr **__cmsgp,
         int __type) throw () __attribute__ ((__deprecated__));
extern int inet6_option_append (struct cmsghdr *__cmsg,
    const uint8_t *__typep, int __multx,
    int __plusy) throw () __attribute__ ((__deprecated__));
extern uint8_t *inet6_option_alloc (struct cmsghdr *__cmsg, int __datalen,
        int __multx, int __plusy)
     throw () __attribute__ ((__deprecated__));
extern int inet6_option_next (const struct cmsghdr *__cmsg,
         uint8_t **__tptrp)
     throw () __attribute__ ((__deprecated__));
extern int inet6_option_find (const struct cmsghdr *__cmsg,
         uint8_t **__tptrp, int __type)
     throw () __attribute__ ((__deprecated__));



extern int inet6_opt_init (void *__extbuf, socklen_t __extlen) throw ();
extern int inet6_opt_append (void *__extbuf, socklen_t __extlen, int __offset,
        uint8_t __type, socklen_t __len, uint8_t __align,
        void **__databufp) throw ();
extern int inet6_opt_finish (void *__extbuf, socklen_t __extlen, int __offset)
     throw ();
extern int inet6_opt_set_val (void *__databuf, int __offset, void *__val,
         socklen_t __vallen) throw ();
extern int inet6_opt_next (void *__extbuf, socklen_t __extlen, int __offset,
      uint8_t *__typep, socklen_t *__lenp,
      void **__databufp) throw ();
extern int inet6_opt_find (void *__extbuf, socklen_t __extlen, int __offset,
      uint8_t __type, socklen_t *__lenp,
      void **__databufp) throw ();
extern int inet6_opt_get_val (void *__databuf, int __offset, void *__val,
         socklen_t __vallen) throw ();



extern socklen_t inet6_rth_space (int __type, int __segments) throw ();
extern void *inet6_rth_init (void *__bp, socklen_t __bp_len, int __type,
        int __segments) throw ();
extern int inet6_rth_add (void *__bp, const struct in6_addr *__addr) throw ();
extern int inet6_rth_reverse (const void *__in, void *__out) throw ();
extern int inet6_rth_segments (const void *__bp) throw ();
extern struct in6_addr *inet6_rth_getaddr (const void *__bp, int __index)
     throw ();





extern int getipv4sourcefilter (int __s, struct in_addr __interface_addr,
    struct in_addr __group, uint32_t *__fmode,
    uint32_t *__numsrc, struct in_addr *__slist)
     throw ();


extern int setipv4sourcefilter (int __s, struct in_addr __interface_addr,
    struct in_addr __group, uint32_t __fmode,
    uint32_t __numsrc,
    const struct in_addr *__slist)
     throw ();



extern int getsourcefilter (int __s, uint32_t __interface_addr,
       const struct sockaddr *__group,
       socklen_t __grouplen, uint32_t *__fmode,
       uint32_t *__numsrc,
       struct sockaddr_storage *__slist) throw ();


extern int setsourcefilter (int __s, uint32_t __interface_addr,
       const struct sockaddr *__group,
       socklen_t __grouplen, uint32_t __fmode,
       uint32_t __numsrc,
       const struct sockaddr_storage *__slist) throw ();


}

}

extern "C" {
}
extern "C" {
}
extern "C" {
typedef enum LrmCause
{
 LRM_CAUSE_NOT_APP,
 LRM_CAUSE_CELLID_UNKNOWN,
 LRM_CAUSE_MMEID_UNKNOWN,
 LRM_CAUSE_CELL_ALREADY_EXISTS,
 LRM_CAUSE_MME_ALREADY_EXISTS,
 LRM_CAUSE_ENB_ALREADY_UP,
 LRM_CAUSE_MME_ALREADY_UP,
 LRM_CAUSE_MME_ALREADY_DOWN,
   LRM_CAUSE_INVALID_CFG_TYPE,
 LRM_CAUSE_INVALID_CFG_INFO,
 LRM_CAUSE_OTHER
} LrmCause;

typedef struct LrmStatusCause
{
 LrmCause enCause;
 U8 bStatus;
} LrmStatusCause;


}


extern "C" {
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




}
extern "C" {






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
typedef S16 (*SsAlloc) (void *, Size *, U32, Data **);





typedef S16 (*SsFree) (void *, Data *, Size);

typedef S16 (*SsCtl) (void *, Event, SMemCtl *);




typedef struct sRegInfo
{
   void *regCb;
   U32 flags;




   Data *start;
   Size size;
   SsAlloc alloc;
   SsFree free;
   SsCtl ctl;

} SRegInfo;
extern "C" {
extern "C" {





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




typedef void (*PFV) (U32, S16);

extern void cmInitTimers (CmTimer* timers, U8 max);
extern void cmPlcCbTq (CmTmrArg* arg);
extern void cmRmvCbTq (CmTmrArg* arg);
extern void cmPrcTmr (CmTqCp* tqCp, CmTqType* tq, PFV func);
extern void cmRstCbTq (CmTmrArg* arg);


}
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
}
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

extern void prntMem (Data *strtAdr,S16 len);
extern void prntMsg (Buffer *mBuf);
extern void prntMsg1 (Buffer *mBuf,S16 src,S16 dst);
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
extern void SLogError (Ent ent, Inst inst, ProcId procId, Txt *file, S32 line, ErrCls errCls, ErrCode errCode, ErrVal errVal, Txt *errDesc)

                                                    ;

extern U32 SGetSystemTsk (void);




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
extern void SSetProcId (ProcId pId);


extern S16 SGetDBufSiz (Region region, Pool pool, S16 *size);
extern S16 SGetStrtIdx (Region region, Pool pool, S16 *idx);
extern S16 SGetEndIdx (Region region, Pool pool, S16 *idx);
extern S16 SGetStrtPad (Region region, Pool pool, S16 *pad);
extern void SExit (void);




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
extern S8* SGetConfigPath (void);


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
}


extern void SIncrementTtiCount(void);
extern Ticks SGetTtiCount(void);
extern void ysPrntBkTrace(void);
extern void ssMlogInit(void);
extern void ssMlogIncrCounter(void);


extern void ssRegMainThread(void);






extern S16 ssGetDBufOfSize(Region region,Size size,Buffer **dBuf);


extern "C" {
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



}
extern "C" {






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

extern void cmInitMemCp ( CmMemListCp *memCp, Size maxBlkSize, Mem *sMem )


                                                 ;







extern S16 cmGetMem ( Ptr memPtr, Size size, Ptr *allocPtr)


                                               ;

extern void cmFreeMem ( Ptr memPtr)
                                            ;

extern void cmGetMemStatus ( Ptr memPtr, CmMemStatus *status)

                                                       ;


}
extern "C" {



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

extern void cmLListInit (CmLListCp *lList);
extern void cmLListAdd2Head (CmLListCp *lList, CmLList *node);
extern void cmLListAdd2Tail (CmLListCp *lList, CmLList *node);
extern void cmLListInsCrnt (CmLListCp *lList, CmLList *node);

extern void cmLListInsAfterCrnt (CmLListCp *lList, CmLList *node);
extern CmLList *cmLListDelFrm (CmLListCp *lList, CmLList *node);
extern void cmLListCatLList ( CmLListCp *list1, CmLListCp *list2);


}
extern "C" {






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


}
extern "C" {
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
extern void UpdateSocCpuInfo(CmCpuStatsInfo *cpuInfo,U8 Idx);

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

extern void cmUpdateTtiCounters(U32 ttiProcessingTime);
extern void cmResetTtiCounters(void);



}
extern "C" {


 U8 *cmMemcpy (U8 *tgt, const U8 *src, U32 len);
 S16 cmMemcmp (const U8 *s1, const U8 *s2, U32 len);
 U8 *cmMemset (U8 *src, U8 val, U32 len);

 S16 cmStrcmp (const U8 *s1, const U8 *s2);

 S16 cmStrncmp (const U8 *s1, const U8 *s2, MsgLen len);
 MsgLen cmStrlen (const U8 *s);


}
extern "C" {










typedef unsigned long int nfds_t;


struct pollfd
  {
    int fd;
    short int events;
    short int revents;
  };


extern "C" {
extern int poll (struct pollfd *__fds, nfds_t __nfds, int __timeout);
extern int ppoll (struct pollfd *__fds, nfds_t __nfds,
    const struct timespec *__timeout,
    const __sigset_t *__ss);


}

extern "C" {

struct rpcent
{
  char *r_name;
  char **r_aliases;
  int r_number;
};

extern void setrpcent (int __stayopen) throw ();
extern void endrpcent (void) throw ();
extern struct rpcent *getrpcbyname (const char *__name) throw ();
extern struct rpcent *getrpcbynumber (int __number) throw ();
extern struct rpcent *getrpcent (void) throw ();


extern int getrpcbyname_r (const char *__name, struct rpcent *__result_buf,
      char *__buffer, size_t __buflen,
      struct rpcent **__result) throw ();

extern int getrpcbynumber_r (int __number, struct rpcent *__result_buf,
        char *__buffer, size_t __buflen,
        struct rpcent **__result) throw ();

extern int getrpcent_r (struct rpcent *__result_buf, char *__buffer,
   size_t __buflen, struct rpcent **__result) throw ();


}











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
extern "C" {







extern int *__h_errno_location (void) throw () __attribute__ ((__const__));
extern void herror (const char *__str) throw ();


extern const char *hstrerror (int __err_num) throw ();




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


extern void freeaddrinfo (struct addrinfo *__ai) throw ();


extern const char *gai_strerror (int __ecode) throw ();





extern int getnameinfo (const struct sockaddr *__restrict __sa,
   socklen_t __salen, char *__restrict __host,
   socklen_t __hostlen, char *__restrict __serv,
   socklen_t __servlen, int __flags);
extern int getaddrinfo_a (int __mode, struct gaicb *__list[],
     int __ent, struct sigevent *__restrict __sig);
extern int gai_suspend (const struct gaicb *const __list[], int __ent,
   const struct timespec *__timeout);


extern int gai_error (struct gaicb *__req) throw ();


extern int gai_cancel (struct gaicb *__gaicbp) throw ();


}




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
extern S16 cmInetInit (void);
extern S16 cmInetDeInit (void);
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
extern S16 cmInetNtop (U8 type,void *address,S8 *asciiAddr,U32 len);





extern S32 cmInetGetAddrInfo (const S8* node, const S8* service, const CmInetAddrInfo *hints, CmInetAddrInfo **res)
                                                                                         ;
extern void cmInetFreeAddrInfo (CmInetAddrInfo *res);
}






extern "C" {




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
}

extern "C" {





typedef enum cmRrmDsrTransMax
{
   DSR_TRANS_N4,
   DSR_TRANS_N8,
   DSR_TRANS_N16,
   DSR_TRANS_N32,
   DSR_TRANS_N64,
   DSR_TRANS_MAX
}CmRrmDsrTransMax;







typedef struct cmRrmDrxLongCycleOffst
{
   U16 usLongDrxCycle;
   U16 usDrxStartOffst;
} CmRrmDrxLongCycleOffst;
typedef struct cmRrmDrxShortDrx
{
   Bool bPres;
   U16 usShortDrxCycle;
   U8 bDrxShortCycleTmr;
} CmRrmDrxShortDrx;
typedef struct cmRrmDrxCfg
{
   Bool bIsDrxEnabled;
   TknS32 stCqiMask;
   U8 bDrxOnDurTmr;
   U16 usDrxInactvTmr;
   U8 bDrxRetxTmr;
   CmRrmDrxLongCycleOffst stDrxLongCycleOffst;
   CmRrmDrxShortDrx stDrxShortDrx;
} CmRrmDrxCfg;

typedef struct cmRrmCellDrxCfg
{
   Bool bIsGbrDrxDis;
   Bool bIsDrxEnabled;
   U8 bDrxRetxTmr;
   U16 usDrxInactvTmr;
   U16 usLongDrxCycleGbr;
   U16 usLongDrxCycleNonGbr;
} CmRrmCellDrxCfg;
typedef enum cmRrmAcBarringTime
{
 RM_ACB_TIME_S4,
 RM_ACB_TIME_S8,
 RM_ACB_TIME_S16,
 RM_ACB_TIME_S32,
 RM_ACB_TIME_S64,
 RM_ACB_TIME_S128,
 RM_ACB_TIME_S256,
 RM_ACB_TIME_S512
} CmRrmAcBarringTime;
typedef enum cmRrmAcBarringFactor
{
 RM_ACB_FACTOR_P00,
 RM_ACB_FACTOR_P05,
 RM_ACB_FACTOR_P10,
 RM_ACB_FACTOR_P15,
 RM_ACB_FACTOR_P20,
 RM_ACB_FACTOR_P25,
 RM_ACB_FACTOR_P30,
 RM_ACB_FACTOR_P40,
 RM_ACB_FACTOR_P50,
 RM_ACB_FACTOR_P60,
 RM_ACB_FACTOR_P70,
 RM_ACB_FACTOR_P75,
 RM_ACB_FACTOR_P80,
 RM_ACB_FACTOR_P85,
 RM_ACB_FACTOR_P90,
 RM_ACB_FACTOR_P95,
 RM_ACB_FACTOR_NA
} CmRrmAcBarringFactor;
typedef struct cmRrmAcb
{
 CmRrmAcBarringTime enAcbTime;
   CmRrmAcBarringFactor enAcbFactor;
   U8 bAcbForSpac;
} CmRrmAcb;

typedef struct cmRrmAcbInfo
{
   CmRrmAcb stAcBarringMoData;
   CmRrmAcb stAcBarringMoSig;
   U8 bAcBarringEmergency;


   U8 bIsacBarringMoSig;

   U8 bIsacBarringMoData;

} CmRrmAcbInfo;


}




extern "C" {




typedef enum rmuS1apCause
{
   RMU_CAUSE_UNSPECIFIED,
   RMU_CAUSE_TX2_RELOC_OVERALL_EXP,
   RMU_CAUSE_SUCC_HANDOVER,
   RMU_CAUSE_REL_EUTRAN_REASON,
   RMU_CAUSE_HANDOVER_CANCELLED,
   RMU_CAUSE_PARTIAL_HANDOVER,
   RMU_CAUSE_HANDOVER_FAILURE_TRGT_SYS,
   RMU_CAUSE_HANDOVER_TRGT_NOT_ALLOWED,
   RMU_CAUSE_TS1_RELOCOVERALL_EXP,
   RMU_CAUSE_TS1_RELOCPREP_EXP,
   RMU_CAUSE_CELL_NOTAVAILABLE,
   RMU_CAUSE_UNKNOWN_TRGT_ID,
   RMU_CAUSE_NO_RESOURCES_IN_TRGT_CELL,
   RMU_CAUSE_UNKNOWN_ALLOC_MME_UE_S1AP_ID,
   RMU_CAUSE_UNKNOWN_ALLOC_ENB_UE_S1AP_ID,
   RMU_CAUSE_UNKNOWN_INCONSIST_PAIR_UE_S1AP_ID,
   RMU_CAUSE_HANDOVER_DESIRABLE_RADIO_REASON,
   RMU_CAUSE_TIME_CRITICAL_HANDOVER,
   RMU_CAUSE_RESOURCE_OPTIMIZE_HANDOVER,
   RMU_CAUSE_REDUCE_LOAD_IN_SERV_CELL,
   RMU_CAUSE_USR_INACTIVITY,
   RMU_CAUSE_RADIO_CON_UE_LOST,
   RMU_CAUSE_LOAD_BLNC_TAU_REQD,
   RMU_CAUSE_CS_FALLBACK_TRIGGERED,
   RMU_CAUSE_UE_NOTAVAILABLE_PS_SER,
   RMU_CAUSE_RADIO_RESOURCE_NOT_AVAIL,
   RMU_CAUSE_FAIL_RADIO_INTF_PROC,
   RMU_CAUSE_INVALID_QOS_COMB,
   RMU_CAUSE_INTER_RAT_REDIRECT,
   RMU_CAUSE_INTERACT_ITHER_PROC,
   RMU_CAUSE_UNKNOWN_ERAB_ID,
   RMU_CAUSE_MULT_ERAB_ID_INSTANCES,
   RMU_CAUSE_ENCRYPT_INTEGRITY_NOT_SUPPORT,
   RMU_CAUSE_S1_INTRA_SYS_HANDOVER_TRIGGERED,
   RMU_CAUSE_S1_INTER_SYS_HANDOVER_TRIGGERED,
   RMU_CAUSE_X2_HANDOVER_TRIGGERED,
   RMU_CAUSE_REDIRECT_1XRTT,
   RMU_CAUSE_NOT_SUPPORT_QCI,
   RMU_CAUSE_INVALID_CSG_ID,
   RMU_CAUSE_BH_BW_NOT_AVAILABLE,
   RMU_CAUSE_MAX_QCI_REACHED,
   RMU_CAUSE_CHECK_PRB_REQ
}RmuS1apCause;




typedef enum rmuAccessStratumRls
{
   RMU_ACCESS_STRATUM_REL8,
   RMU_ACCESS_STRATUM_REL9,
   RMU_ACCESS_STRATUM_REL9HIGHER
} RmuAccessStratumRls;


typedef struct rmuAcbParamInd
{
  CmRrmAcbInfo stAcbInfo;
} RmuAcbParamInd;

typedef enum rmuCellRecfgType
{
   RMU_CELL_RECFG_ACB_IND
}RmuCellRecfgType;

typedef struct rmuCellRecfgInd
{
   RmuAcbParamInd stAcbParamInd;
   RmuCellRecfgType enCellRecfgType;
   U8 bCellId;
} RmuCellRecfgInd;



typedef enum rmuEnbStatus
{
   RMU_ENB_STATUS_UP,
   RMU_ENB_STATUS_DOWN
}RmuEnbStatus;

typedef enum rmuMmeStatus
{
   RMU_MME_STATUS_UP = 0,
   RMU_MME_STATUS_DOWN
}RmuMmeStatus;

typedef struct rmuMmeStatusInd
{
  RmuMmeStatus enMmeStatus;
  U16 usMmeId;
} RmuMmeStatusInd;

typedef struct rmuEnbStatusInd
{
  U8 bCellId;
  RmuEnbStatus enEnbStatus;
} RmuEnbStatusInd;



typedef enum rmuFsmStatusType
{
   RMU_FSM_STATUS_MME,
   RMU_FSM_STATUS_ENB
}RmuFsmStatusType;

typedef struct rmuFsmStatusInd
{
  RmuFsmStatusType enStatusType;
  union {
      RmuMmeStatusInd stMmeStatusInd;
      RmuEnbStatusInd stEnbStatusInd;
  }u;
} RmuFsmStatusInd;



typedef enum rmuMmeOvldStatus
{
   RMU_MME_REJECT_MODATA,
   RMU_MME_REJECT_MOSIG_MODATA,
   RMU_MME_PERMITONLY_EMG_MTACCESS,
   RMU_MME_PERMITONLY_HIGHPRI_MTACCESS,
   RMU_MME_REJECT_DELAY_TOLERNT_ACCESS,
   RMU_MME_OVLD_STATUS_NORMAL
}RmuMmeOvldStatus;

typedef struct rmuMmeOvldStartInd
{
   RmuMmeOvldStatus enMmeOvldStatus;
   U16 usMmeId;
} RmuMmeOvldStartInd;


typedef struct rmuMmeOvldStopInd
{
   U16 usMmeId;
} RmuMmeOvldStopInd;


typedef enum rmuConEstCause
{
   RMU_EST_CAUSE_EMERGENCY,
   RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS,
   RMU_EST_CAUSE_MT_ACCESS,
   RMU_EST_CAUSE_MO_SIGNALLING,
   RMU_EST_CAUSE_MO_DATA,
   RMU_EST_CAUSE_DELAY_TOLERANT,
   RMU_EST_CAUSE_HO_REQ,
   RMU_MAX_EST_CAUSE
} RmuConEstCause;

typedef struct rmuUeAdmitReq
{
   RmuConEstCause enConEstabCause;
   U32 uiTransId;
   U16 usCrnti;
   U8 bCellId;
} RmuUeAdmitReq;


typedef enum rmuRrcCause
{
   RMU_CAUSE_CELLID_UNKNOWN,
   RMU_CAUSE_MMEID_UNKNOWN,
   RMU_CAUSE_UEID_UNKNOWN,
   RMU_CAUSE_OUT_OF_RESOURCE,
   RMU_CAUSE_MAX_UE_REACHED,
   RMU_CAUSE_CELL_ALREADY_EXISTS,
   RMU_CAUSE_MME_ALREADY_EXISTS,
   RMU_CAUSE_UEID_ALREADY_EXISTS,
   RMU_CAUSE_ENB_ALREADY_UP,
   RMU_CAUSE_NOT_APP,
   RMU_CAUSE_MAX_CSG_UE_REACHED,
   RMU_CAUSE_MAX_NON_CSG_UE_REACHED,
   RMU_CAUSE_MAX_EXTRA_UE_REACHED,
   RMU_CAUSE_OTHER
} RmuRrcCause;

typedef enum rmuStatus
{
   RMU_FAILURE,
   RMU_SUCCESS,
   RMU_REDIRECT
} RmuStatus;

typedef struct rmuStatusInfo
{
   RmuRrcCause enCause;
   RmuStatus enStatus;
} RmuStatusInfo;



typedef enum rmuHandOverType
{
   RMU_HO_TYPE_IntraLTE,
   RMU_HO_TYPE_LTEtoUTRAN,
   RMU_HO_TYPE_LTEtoGERAN,
   RMU_HO_TYPE_UTRANtoLTE,
   RMU_HO_TYPE_GERANtoLTE,
   RMU_HO_TYPE_S1,
   RMU_HO_TYPE_X2
} RmuHandOverType;

typedef enum rmuErabAction
{
   RMU_ADD_ERAB,
   RMU_MOD_ERAB,
   RMU_DEL_ERAB
} RmuErabAction;


typedef struct rmuPst
{
  U16 usDstProcId;
  U16 usSrcProcId;
  U8 bDstEnt;
  U8 bSstInst;
  U8 bSrcEnt;
  U8 bSrcInst;
  U8 bPrior;
  U8 bRoute;
  U8 bEvent;
} RmuPst;

typedef struct rmuUEAggreMaxBitRateIe
{
   U32 uiAggUEMaxBitRateUL;
   U32 uiAggUEMaxBitRateDL;
} RmuUEAggreMaxBitRateIe;

typedef struct rmuErabGbrInfoIe
{
   U32 uiErabDlMbr;
   U32 uiErabUlMbr;
   U32 uiErabDlGbr;
   U32 uiErabUlGbr;
} RmuErabGbrInfoIe;

typedef struct rmuErabArpInfoIe
{
   U8 bErabPrioLvl;
   Bool bErabPreemptCap;
   Bool bErabPreemptVul;
} RmuErabArpInfoIe;

typedef struct rmuErabQosInfoIe
{
   RmuErabArpInfoIe stErabArpInfo;
   RmuErabGbrInfoIe stErabGbrInfo;
   U8 bErabQCI;

} RmuUErabQosInfoIe;

typedef struct rmuErabAddModIe
{
   RmuUErabQosInfoIe stErabQosInfo;

   U8 bErabId;

} RmuUErabAddModIe;

typedef struct rmuErabRelIe
{
   RmuS1apCause enErabRelCause;
   U8 bErabId;

} RmuErabRelIe;

typedef struct rmuErabConfigIe
{
   RmuUErabAddModIe stErabAddModLst[8];
   RmuErabRelIe stErabRelLst[8];
   RmuUEAggreMaxBitRateIe stUeAmbrInfo;
   RmuErabAction enErabAction;
   U16 usNoErabsToAddMod;
   U8 bNoErabsToRel;
   U8 bIsUeAmbrPres;

} RmuErabConfigIe;
typedef struct rmuErabRelLst
{
   RmuErabRelIe stErabRelLst[8];
   U8 bNoErabsToRel;
} RmuErabRelLst;
typedef enum rmuPcqiFormatInd
{
   RMU_PCQI_FMT_WIDEBAND,
   RMU_PCQI_FMT_SUBBAND
} RmuPcqiFormatInd;

typedef enum rmuPucchReportMode
{
   RMU_CQI_MODE10,
   RMU_CQI_MODE11,
   RMU_CQI_MODE20,
   RMU_CQI_MODE21
} RmuPucchReportMode;

typedef enum rmuPuschReportMode
{
   RMU_APRD_CQI_MODE12,
   RMU_APRD_CQI_MODE20,
   RMU_APRD_CQI_MODE22,
   RMU_APRD_CQI_MODE30,
   RMU_APRD_CQI_MODE31
} RmuPuschReportMode;

typedef struct rmuRiConfigIndex
{
   Bool bPres;
   U16 usRiConfigIndex;
} RmuRiConfigIndex;

typedef enum rmuSubbandCqiPeriodicityFactor
{
 RMU_PERIODICITY_FACTOR_N2,
 RMU_PERIODICITY_FACTOR_N4
}RmuSubbandCqiPeriodicityFactor;

typedef struct rmuPCqiReportCfg
{
   U8 type;
   RmuPcqiFormatInd enCqiFormatInd;
   RmuPucchReportMode enPucchReportMode;
   U16 usCqiResourceIndex;
   U16 usCqiConfigIndex;

   RmuRiConfigIndex riConfigIndex;
   U8 bFactorK;


 RmuSubbandCqiPeriodicityFactor sBCqiPeriodicityFactor;
   U8 bSimulAckNackCqi;

   U16 srCfgIdx;
} RmuPCqiReportCfg;

typedef struct rmuApCqiReportCfg
{
   Bool enbld;
   RmuPuschReportMode enPuschReportMode;
} RmuApCqiReportCfg;

typedef struct rmuUeCqiReportCfg
{
   RmuPCqiReportCfg stPrdCqiRepCfg;
   RmuApCqiReportCfg stAPrdCqiRepCfg;
} RmuUeCqiReportCfg;

typedef struct rmuUeSrCfg
{
   U16 usSrIdx;
   U16 usSrResIdx;
   CmRrmDsrTransMax enDsrTransMax;
} RmuUeSrCfg;

typedef enum
{
   RMU_TXN_MODE1,
   RMU_TXN_MODE2,
   RMU_TXN_MODE3,
   RMU_TXN_MODE4,
   RMU_TXN_MODE5,
   RMU_TXN_MODE6,
   RMU_TXN_MODE7
} RmuTxnMode;

typedef struct rmuAntInfo
{
   RmuTxnMode eTxnMode;
   U16 stcodebookSubset;
   U8 ueTxnAntSel;
} RmuAntInfo;
typedef struct rmuUeDedPhyCfg
{
   U8 bPhyCfgDedResBitMap;
   RmuUeCqiReportCfg stCqiRepCfg;
   RmuAntInfo stAntInfo;
 RmuUeSrCfg stSrCfg;





} RmuUeDedPhyCfg;


typedef struct rmuUeMacMainCfg
{
   U8 bMacMainCfgBitMap;
   CmRrmDrxCfg stRmDrxCfg;
} RmuUeMacMainCfg;


typedef struct rmuSpsP0Persistent
{
      S8 sP0NominalPUSCHPersistent;
      S8 sP0UEPuschPersistent;
} RmuSpsP0Persistent;

typedef enum
{
   RMU_SPS_E2,
   RMU_SPS_E3,
   RMU_SPS_E4,
   RMU_SPS_E8
} RmuSpsImplctRelAftr;

typedef enum
{
   RMU_SPS_UL_INTERVAL_E10,
   RMU_SPS_UL_INTERVAL_E20,
   RMU_SPS_UL_INTERVAL_E32,
   RMU_SPS_UL_INTERVAL_E40,
   RMU_SPS_UL_INTERVAL_E64,
   RMU_SPS_UL_INTERVAL_E80,
   RMU_SPS_UL_INTERVAL_E128,
   RMU_SPS_UL_INTERVAL_E160,
   RMU_SPS_UL_INTERVAL_E320,
   RMU_SPS_UL_INTERVAL_E640,
   RMU_SPS_UL_INTERVAL_SPARE6,
   RMU_SPS_UL_INTERVAL_SPARE5,
   RMU_SPS_UL_INTERVAL_SPARE4,
   RMU_SPS_UL_INTERVAL_SPARE3,
   RMU_SPS_UL_INTERVAL_SPARE2,
   RMU_SPS_UL_INTERVAL_SPARE1
}RmuSpsIntervalUl;

typedef enum
{
   RMU_SPS_DL_INTERVAL_E10,
   RMU_SPS_DL_INTERVAL_E20,
   RMU_SPS_DL_INTERVAL_E32,
   RMU_SPS_DL_INTERVAL_E40,
   RMU_SPS_DL_INTERVAL_E64,
   RMU_SPS_DL_INTERVAL_E80,
   RMU_SPS_DL_INTERVAL_E128,
   RMU_SPS_DL_INTERVAL_E160,
   RMU_SPS_DL_INTERVAL_E320,
   RMU_SPS_DL_INTERVAL_E640,
   RMU_SPS_DL_INTERVAL_SPARE6,
   RMU_SPS_DL_INTERVAL_SPARE5,
   RMU_SPS_DL_INTERVAL_SPARE4,
   RMU_SPS_DL_INTERVAL_SPARE3,
   RMU_SPS_DL_INTERVAL_SPARE2,
   RMU_SPS_DL_INTERVAL_SPARE1
}RmuSpsIntervalDl;

typedef struct rmuSpsConfigUl
{
    Bool bIsSpsEnabled;
    RmuSpsIntervalUl eSpsIntervalUl;
    RmuSpsImplctRelAftr eImplctRelAftr;
    Bool bTwoIntervalCfg;
    Bool bP0PersistentPres;
    RmuSpsP0Persistent stP0Persistent;
} RmuSpsConfigUl;

typedef struct rmuSpsConfigDl
{
    Bool bIsSpsEnabled;
    RmuSpsIntervalDl eSpsIntervalDl;
    U16 usExplctRelAftr;
    U8 usNumOfConfSpsProc;
    U8 usNumN1Pucch;
    U16 usN1Pucch[4];
} RmuSpsConfigDl;

typedef struct rmuUeSpsCfg
{
    RmuSpsConfigDl stSpsConfigDl;
    RmuSpsConfigUl stSpsConfigUl;
} RmuUeSpsCfg;


typedef struct rmuUeRadioResCfg
{
   U8 bRadioResDedBitMap;
   RmuUeDedPhyCfg stPhyCfgDed;
   RmuUeMacMainCfg stMacMainCfg;

   RmuUeSpsCfg stSpsCfg;

} RmuUeRadioResCfg;

typedef struct rmuUeAdmitRsp
{
   RmuStatusInfo stStatusInfo;
   RmuUeRadioResCfg stUeRadioResCfg;
   U32 uiTransId;
   U16 usCrnti;
   U8 bCellId;
   U8 bWaitTime;

} RmuUeAdmitRsp;



typedef enum rmuScellAction
{
   RMU_SCELL_ADD,
   RMU_SCELL_MOD_COMMON,
   RMU_SCELL_MOD_DEDICATED,
   RMU_SCELL_RELEASE
} RmuScellAction;

typedef struct rmuSCellInfo
{

   RmuScellAction action;
   CmLteCellId sCellId;
   U8 sCellIdx;

}RmuSCellInfo;
typedef struct rmuUeScellInfoReq
{
   U32 uiTransId;
   U8 pCellId;
   U8 numOfScell;
   RmuSCellInfo sCellIInfo[7];
} RmuUeScellInfoReq;

typedef struct rmuUeSCellDedInfo
{
   RmuStatusInfo stStatusInfo;
   U8 sCellIdx;
   RmuUeCqiReportCfg stCqiRepCfg;
} RmuUeSCellDedInfo;

typedef struct rmuUeSCellInfoRsp
{
   U8 numSCells;
   RmuUeSCellDedInfo sCellDedInfo[7];
} RmuUeSCellInfoRsp;

typedef struct rmuEutraCapInfo
{
   U32 uiFeatureGrpIndicator;

   U32 uiUeCategory;

   RmuAccessStratumRls uiUeAccessStratumRls;

} RmuEutraCapInfo;

typedef struct rmuUeCapInfoIe
{
   RmuEutraCapInfo stEutraCapInfo;
} RmuUeCapInfoIe;

typedef struct rmuUeHoReq
{
   RmuErabConfigIe stErabConfInfo;
   RmuUeCapInfoIe stUeCapInfo;
   RmuUeRadioResCfg stUeRadioResCfg;
   RmuHandOverType enHoType;
   RmuS1apCause enHoS1apCause;
   U32 uiTransId;
   U16 usCrnti;
   U8 bCellId;
   Bool isEmrgncyBrersPsnt;
   U8 isMember;
} RmuUeHoReq;


typedef struct rmuErabAdmitted
{
   U8 bErabId;

   Bool bIsDlSpsEnabled;
   Bool bIsUlSpsEnabled;

} RmuErabAdmitted;

typedef struct rmuErabRejected
{
   RmuS1apCause enCause;
   U8 bErabId;
} RmuErabRejected;

typedef struct rmuUeHoRsp
{
   RmuErabAdmitted stErabAdmitLst[8];
   RmuErabRejected stErabRejectLst[8];
   RmuUeRadioResCfg stUeRadioResCfg;
   RmuStatusInfo stStatusInfo;
   U32 uiTransId;
   U16 usCrnti;
   U8 bCellId;
   U8 bNoErabsAdmitted;
   U8 bNoErabsRejected;
   Bool isGBRBearerExists;
} RmuUeHoRsp;


typedef struct rmuUeRelReq
{
   U32 uiTransId;
   U16 usCrnti;
   U8 bCellId;
} RmuUeRelReq;


typedef struct rmuUeRelRsp
{
   RmuStatusInfo stStatusInfo;
   U32 uiTransId;
   U16 usCrnti;
   U8 bCellId;
} RmuUeRelRsp;


typedef struct rmuUeRelInd
{
   RmuRrcCause enRelCause;
   U16 usCrnti;
   U8 bCellId;
} RmuUeRelInd;
typedef struct rmuUeERabRelInd
{
   RmuErabRelLst stErabRelInfo;
   U16 usCrnti;
   U8 bCellId;
} RmuUeERabRelInd;


typedef struct rmuUeRecfgReq
{
   RmuErabConfigIe stErabConfInfo;
   RmuUeCapInfoIe stUeCapInfo;
   RmuUeScellInfoReq stSCellInfoReq;
   U32 uiTransId;
   U16 usCrnti;
   U16 usUeNewCrnti;
   U8 bCellId;
   U8 bRecfgBitMap;

   U8 isMember;





} RmuUeRecfgReq;


typedef struct rmuUeInactInd
{
   CmLteRnti uiCrnti;
   CmLteCellId uiCellId;
   U8 uiInactEvt;
} RmuUeInactInd;


typedef struct rmuUeRecfgRsp
{
   RmuErabAdmitted stErabAcceptLst[8];
   RmuErabRejected stErabRejectLst[8];
   RmuUeRadioResCfg stUeRadioResCfg;
   RmuUeSCellInfoRsp stUeSCellResCfg;
   RmuStatusInfo stStatusInfo;
   U32 uiTransId;
   U16 usCrnti;
   U8 bCellId;
   U8 bRecfgBitMap;

   U8 bNoErabsAccepted;
   U8 bNoErabsRejected;
   Bool isGBRBearerExists;
} RmuUeRecfgRsp;

typedef RmuUeRecfgRsp RmuUeRecfgInd;


typedef struct rmuUeSpsDisInd
{
   U8 cellId;
   U16 usCrnti;
} RmuUeSpsDisInd;


typedef union
{
 RmuUeAdmitReq stRmuUeAdmitReq;
 RmuUeAdmitRsp stRmuUeAdmitRsp;
 RmuUeRecfgReq stRmuUeRecfgReq;
 RmuUeRecfgRsp stRmuUeRecfgRsp;
 RmuUeRelReq stRmuUeRelReq;
 RmuUeRelRsp stRmuUeRelRsp;
 RmuUeHoReq stRmuUeHoReq;
 RmuUeHoRsp stRmuUeHoRsp;
 RmuCellRecfgInd stRmuCellRecfgInd;
 RmuFsmStatusInd stRmuFsmStatusInd;
 RmuUeRelInd stRmuUeRelInd;
   RmuUeERabRelInd stRmuUeERabRelInd;
   RmuMmeOvldStartInd stRmuOverLoadStartInd;
   RmuMmeOvldStopInd stRmuOverLoadStopInd;

   RmuUeSpsDisInd stRmuSpsDisInd;


   RmuUeInactInd stRmuUeInactInd;
   RmuUeRecfgInd stRmuUeReCfgInd;
} RmuCommonMsg;



typedef S16 (*RmuFsmStatusIndFPtr) ( Pst *pst, SuId suId, RmuFsmStatusInd *statusInd )



          ;

typedef S16 (*RmuMmeOvldStartIndFPtr) ( Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo )



          ;

typedef S16 (*RmuMmeOvldStopIndFPtr) ( Pst *pst, SuId suId, RmuMmeOvldStopInd *stopInfo )



          ;
typedef S16 (*RmuUeAdmitReqFPtr) ( Pst *pst, SuId suId, RmuUeAdmitReq *admitInfo )



          ;
typedef S16 (*RmuUeHoReqFPtr) ( Pst *pst, SuId suId, RmuUeHoReq *hoInfo )



          ;
typedef S16 (*RmuUeRelReqFPtr) ( Pst *pst, SuId suId, RmuUeRelReq *relInfo )



          ;
typedef S16 (*RmuUeRecfgReqFPtr) ( Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo )



          ;

typedef S16 (*RmuUeInactIndFPtr) ( Pst *pst, SuId suId, RmuUeInactInd *rrmUeInactInd )



          ;

typedef S16 (*RmuUeSpsDisIndFPtr) ( Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd )



          ;


typedef S16 (*RmuBndReqFPtr) ( Pst *pst, SuId suId, SpId spId )



          ;

typedef S16 (*RmuCellRecfgIndFPtr) ( Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInfo )



          ;

typedef S16 (*RmuUeRecfgIndFPtr) ( Pst *pst, SuId suId, RmuUeRecfgInd *ueRecfgInfo )



          ;
typedef S16 (*RmuUeAdmitRspFPtr) ( Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspinfo )



          ;
typedef S16 (*RmuUeHoRspFPtr) ( Pst *pst, SuId suId, RmuUeHoRsp *hoRspinfo )



          ;
typedef S16 (*RmuUeRelRspFPtr) ( Pst *pst, SuId suId, RmuUeRelRsp *relrspinfo )



          ;
typedef S16 (*RmuUeRelIndFPtr) ( Pst *pst, SuId suId, RmuUeRelInd *relIndinfo )



          ;


typedef S16 (*RmuUeERabRelIndFPtr) ( Pst *pst, SuId suId, RmuUeERabRelInd *relIndinfo )



          ;
typedef S16 (*RmuUeRecfgRspFPtr) ( Pst *pst, SuId suId, RmuUeRecfgRsp *recfgRspinfo )



          ;
typedef S16 (*RmuBndCfmFPtr) ( Pst *pst, SuId suId, U8 status )



          ;


extern S16 cmPkRmuFsmStatusInd (Pst *pst, SuId suId, RmuFsmStatusInd *statusInd);
extern S16 cmPkRmuMmeOverloadStartInd (Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo);
extern S16 cmPkRmuMmeOverloadStopInd (Pst *pst, SuId suId, RmuMmeOvldStopInd *stopinfo);
extern S16 cmPkRmuUeAdmitReq (Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo);
extern S16 cmPkRmuUeHoReq (Pst *pst, SuId suId, RmuUeHoReq *hoinfo);
extern S16 cmPkRmuUeRelReq (Pst *pst, SuId suId, RmuUeRelReq *relinfo);
extern S16 cmPkRmuUeRecfgReq (Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo);

extern S16 cmPkRmuUeSpsDisInd (Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd);



extern S16 cmPkRmuUeInactInd (Pst *pst, SuId suId, RmuUeInactInd *rrmUeInactInd)
                                                   ;

extern S16 cmPkRmuBndReq (Pst *pst, SuId suId, SpId spId);

extern S16 cmUnpkRmuCellRecfgInd (RmuCellRecfgIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkRmuUeRecfgInd (RmuUeRecfgIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkRmuUeAdmitRsp (RmuUeAdmitRspFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkRmuUeHoRsp (RmuUeHoRspFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkRmuUeRelRsp (RmuUeRelRspFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkRmuUeRelInd (RmuUeRelIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkRmuUeERabRelInd (RmuUeERabRelIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkRmuUeRecfgRsp (RmuUeRecfgRspFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkRmuBndCfm (RmuBndCfmFPtr func, Pst* pst, Buffer* mBuf);


extern S16 cmPkLwLcRmuFsmStatusInd (Pst *pst, SuId suId, RmuFsmStatusInd *statusInd);
extern S16 cmPkLwLcRmuMmeOverloadStartInd (Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo);
extern S16 cmPkLwLcRmuMmeOverloadStopInd (Pst *pst, SuId suId, RmuMmeOvldStopInd *stopinfo);
extern S16 cmPkLwLcRmuUeAdmitReq (Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo);
extern S16 cmPkLwLcRmuUeHoReq (Pst *pst, SuId suId, RmuUeHoReq *hoinfo);
extern S16 cmPkLwLcRmuUeRelReq (Pst *pst, SuId suId, RmuUeRelReq *relinfo);
extern S16 cmPkLwLcRmuUeRecfgReq (Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo);

extern S16 cmPkLwLcRmuUeSpsDisInd (Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd);



extern S16 cmPkLwLcRmuUeInactInd (Pst *pst, SuId suId, RmuUeInactInd *rrmUeInactInd)
                                                       ;

extern S16 cmPkLwLcRmuBndReq (Pst *pst, SuId suId, SpId spId);

extern S16 cmUnpkLwLcRmuCellReCfgInd (RmuCellRecfgIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeReCfgInd (RmuUeRecfgIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeAdmitRsp (RmuUeAdmitRspFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeHoRsp (RmuUeHoRspFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeRelRsp (RmuUeRelRspFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeRelInd (RmuUeRelIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeERabRelInd (RmuUeERabRelIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeRecfgRsp (RmuUeRecfgRspFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuBndCfm (RmuBndCfmFPtr func, Pst* pst, Buffer* mBuf);

extern S16 cmPkLwLcRmuUeAdmitRsp (Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspInfo);
extern S16 cmPkLwLcRmuUeHoRsp (Pst *pst, SuId suId, RmuUeHoRsp *hoRspInfo);
extern S16 cmPkLwLcRmuUeRelRsp (Pst *pst, SuId suId, RmuUeRelRsp *ueRelRspInfo);
extern S16 cmPkLwLcRmuUeRelInd (Pst *pst, SuId suId, RmuUeRelInd *ueRelIndInfo);
extern S16 cmPkLwLcRmuUeERabRelInd (Pst *pst, SuId suId, RmuUeERabRelInd *rabRelIndInfo);
extern S16 cmPkLwLcRmuUeRecfgRsp (Pst *pst, SuId suId, RmuUeRecfgRsp *ueRecfgRspInfo);
extern S16 cmPkLwLcRmuCellRecfgInd (Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInd);
extern S16 cmPkLwLcRmuUeRecfgInd (Pst *pst, SuId suId, RmuUeRecfgInd *ueRecfgInd);
extern S16 cmPkLwLcRmuBndCfm (Pst *pst, SuId suId, U8 status);

extern S16 cmUnpkLwLcRmuBndReq (RmuBndReqFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeAdmitReq (RmuUeAdmitReqFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeHoReq (RmuUeHoReqFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeRelReq (RmuUeRelReqFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeRelReq (RmuUeRelReqFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuUeRecfgReq (RmuUeRecfgReqFPtr func, Pst* pst, Buffer* mBuf);

extern S16 cmUnpkLwLcRmuUeSpsDisInd (RmuUeSpsDisIndFPtr func, Pst* pst, Buffer* mBuf);


extern S16 cmUnpkLwLcRmuUeInactInd (RmuUeInactIndFPtr func,Pst* pst,Buffer* mBuf);
extern S16 cmUnpkLwLcRmuMmeOvldStartInd (RmuMmeOvldStartIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuMmeOvldStopInd (RmuMmeOvldStopIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 cmUnpkLwLcRmuFsmStatusInd (RmuFsmStatusIndFPtr func, Pst* pst, Buffer* mBuf);
extern S16 WrLiRmuFsmStatusInd (Pst *pst, SuId suId, RmuFsmStatusInd *statusInd);
extern S16 WrLiRmuMmeOverloadStartInd (Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo);
extern S16 WrLiRmuMmeOverloadStopInd (Pst *pst, SuId suId, RmuMmeOvldStopInd *stopinfo);
extern S16 WrLiRmuUeAdmitReq (Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo);
extern S16 WrLiRmuUeHoReq (Pst *pst, SuId suId, RmuUeHoReq *hoinfo);
extern S16 WrLiRmuUeRelReq (Pst *pst, SuId suId, RmuUeRelReq *relinfo);
extern S16 WrLiRmuUeRecfgReq (Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo);

extern S16 WrLiRmuUeSpsDisInd (Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd);


extern S16 WrLiRmuUeInactInd (Pst *pst, SuId suId,RmuUeInactInd *rrmUeInactInd);

extern S16 WrLiRmuBndReq (Pst *pst, SuId suId, SpId spId);

extern S16 WrLiRmuCellRecfgInd (Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInfo);
extern S16 WrLiRmuUeRecfgInd (Pst *pst, SuId suId, RmuUeRecfgInd *ueRecfgInfo);
extern S16 WrLiRmuUeAdmitRsp (Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspinfo);
extern S16 WrLiRmuUeHoRsp (Pst *pst, SuId suId, RmuUeHoRsp *hoRspinfo);
extern S16 WrLiRmuUeRelRsp (Pst *pst, SuId suId, RmuUeRelRsp *relrspinfo);
extern S16 WrLiRmuUeRelInd (Pst *pst, SuId suId, RmuUeRelInd *relIndinfo);
extern S16 WrLiRmuUeERabRelInd (Pst *pst, SuId suId, RmuUeERabRelInd *relIndinfo);
extern S16 WrLiRmuUeRecfgRsp (Pst *pst, SuId suId, RmuUeRecfgRsp *recfgRspinfo);
extern S16 WrLiRmuBndCfm (Pst *pst, SuId suId, U8 status);


extern S16 RmUiRmuBndReq (Pst *pst, SuId suId, SpId spId);
extern S16 RmUiRmuFsmStatusInd (Pst *pst, SuId suId, RmuFsmStatusInd *statusInd);
extern S16 RmUiRmuUeAdmitReq (Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo);
extern S16 RmUiRmuUeHoReq (Pst *pst, SuId suId, RmuUeHoReq *hoinfo);
extern S16 RmUiRmuUeRelReq (Pst *pst, SuId suId, RmuUeRelReq *relinfo);
extern S16 RmUiRmuUeRecfgReq (Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo);

extern S16 RmUiRmuUeSpsDisInd (Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd);


extern S16 RmUiRmuUeInactInd (Pst *pst, SuId suId, RmuUeInactInd *rrmUeInactInd)
                                                   ;

extern S16 RmUiRmuMmeOvldStartInd (Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo);
extern S16 RmUiRmuMmeOvldStopInd (Pst *pst, SuId suId,RmuMmeOvldStopInd *stopinfo);

extern S16 RmUiRmuCellRecfgInd (Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInfo);
extern S16 RmUiRmuUeRecfgInd (Pst *pst, SuId suId, RmuUeRecfgInd *pstUeRecfgInd);
extern S16 RmUiRmuUeAdmitRsp (Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspinfo);
extern S16 RmUiRmuUeHoRsp (Pst *pst, SuId suId, RmuUeHoRsp *hoRspinfo);
extern S16 RmUiRmuUeRelRsp (Pst *pst, SuId suId, RmuUeRelRsp *relrspinfo);
extern S16 RmUiRmuUeRelInd (Pst *pst, SuId suId, RmuUeRelInd *relIndinfo);
extern S16 RmUiRmuUeERabRelInd (Pst *pst, SuId suId, RmuUeERabRelInd *relIndinfo);
extern S16 RmUiRmuUeRecfgRsp (Pst *pst, SuId suId, RmuUeRecfgRsp *recfgRspinfo);
extern S16 RmUiRmuBndCfm (Pst *pst, SuId suId, U8 status);
extern S16 PtPkRmuUeAdmitRsp (Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspInfo);
extern S16 PtPkRmuUeHoRsp (Pst *pst, SuId suId, RmuUeHoRsp *hoRspInfo);
extern S16 PtPkRmuUeRelRsp (Pst *pst, SuId suId, RmuUeRelRsp *ueRelRspInfo);
extern S16 PtPkRmuUeRelInd (Pst *pst, SuId suId, RmuUeRelInd *ueRelIndInfo);
extern S16 PtPkRmuUeERabRelInd (Pst *pst, SuId suId, RmuUeERabRelInd *rabRelIndInfo);
extern S16 PtPkRmuUeRecfgRsp (Pst *pst, SuId suId, RmuUeRecfgRsp *ueRecfgRspInfo);
extern S16 PtPkRmuCellRecfgInd (Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInd);
extern S16 PtPkRmuUeRecfgInd (Pst *pst, SuId suId, RmuUeRecfgInd *ueRecfgInd);
extern S16 PtPkRmuBndCfm (Pst *pst, SuId suId, U8 status);



}

extern "C" {





typedef struct rmGenCfg
{
   Pst lmPst;
   MemoryId mem;
   U8 tmrRes;
   U8 maxRmuSaps;
} RmGenCfg;




typedef struct rmUSapCfg
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
} RmUSapCfg;




typedef struct rmLSapCfg
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
} RmLSapCfg;




typedef struct rmCfg
{
   union
   {
      RmGenCfg genCfg;

      RmUSapCfg rmuSap;
      RmLSapCfg rgmSap;
   }s;
} RmCfg;




typedef struct rmSapCntrl
{
   SuId suId;
   SpId spId;
} RmSapCntrl;




typedef struct rmCntrl
{
   DateTime dt;
   U8 action;
   U8 subAction;
   U8 instId;
   union
   {
      RmSapCntrl rmSapCntrl;
   }u;

} RmCntrl;


typedef enum lrmCfgAction
{
 LRM_CFG_ADD = 1,
   LRM_CFG_MOD,
   LRM_CFG_DEL
} LrmCfgAction;

typedef enum lrmCellBandwidth
{
   LRM_BANDWIDTH_6,
   LRM_BANDWIDTH_15,
   LRM_BANDWIDTH_25,
   LRM_BANDWIDTH_50,
   LRM_BANDWIDTH_75,
   LRM_BANDWIDTH_100,
   LRM_BANDWIDTH_MAX
}LrmCellBandwidth;


typedef struct lrmSpsCellConfigData
{
   Bool bIsSpsEnabled;
   U16 usMaxDlSpsUePerTti;
   U16 usMaxUlSpsUePerTti;
} LrmSpsCellConfigData;


typedef enum lrmSplSfConfig
{
   LRM_SPL_SF_CONFIG_0,
   LRM_SPL_SF_CONFIG_1,
   LRM_SPL_SF_CONFIG_2,
   LRM_SPL_SF_CONFIG_3,
   LRM_SPL_SF_CONFIG_4,
   LRM_SPL_SF_CONFIG_5,
   LRM_SPL_SF_CONFIG_6,
   LRM_SPL_SF_CONFIG_7,
   LRM_SPL_SF_CONFIG_8
}LrmSplSfConfig;
typedef enum lrmUlDlConfig
{
   LRM_UL_DL_CONFIG_0,
   LRM_UL_DL_CONFIG_1,
   LRM_UL_DL_CONFIG_2,
   LRM_UL_DL_CONFIG_3,
   LRM_UL_DL_CONFIG_4,
   LRM_UL_DL_CONFIG_5,
   LRM_UL_DL_CONFIG_6,
   LRM_UL_DL_CONFIG_MAX
}LrmUlDlConfig;
typedef enum lrmCqiPrdcty
{
   LRM_CQI_PRDCTY_2,
   LRM_CQI_PRDCTY_5,
   LRM_CQI_PRDCTY_10,
   LRM_CQI_PRDCTY_20,
   LRM_CQI_PRDCTY_40,
   LRM_CQI_PRDCTY_80,
   LRM_CQI_PRDCTY_160,
   LRM_CQI_PRDCTY_32,
   LRM_CQI_PRDCTY_64,
   LRM_CQI_PRDCTY_128,
   LRM_CQI_PRDCTY_MAX
}LrmCqiPrdcty;

typedef enum lrmSrPrdcty
{
   LRM_SR_PRDCTY_5,
   LRM_SR_PRDCTY_10,
   LRM_SR_PRDCTY_20,
   LRM_SR_PRDCTY_40,
   LRM_SR_PRDCTY_80,
   LRM_SR_PRDCTY_2,
   LRM_SR_PRDCTY_1,
   LRM_SR_PRDCTY_MAX
}LrmSrPrdcty;


typedef struct lrmCellConfigData
{
   CmRrmCellDrxCfg stRmCellDrxCfg;
 LrmCellBandwidth enCellDlBandWidth;
   CmRrmAcbInfo stAcbInfo;
 U16 usMaxUlBroadbandBw;
 U16 usMaxDlBroadbandBw;
   U16 usN1Pucch;
 U8 bNRbCqi;
 U8 bNCsAn;
 U8 bMaxActiveUesServed;
 U8 bMaxSigUesServed;
 U8 flagDlfsScheduling;
 U8 flagTransMode;
 U8 bWaitTime;
 U8 bCellId;
   U8 bRcmAlgoType;
 U8 bNumTxAnt;
   LrmSrPrdcty enSrPrdcty;
   LrmCqiPrdcty enCqiPrdcty;
   U16 usNumSrResPerTti;
   U16 usNumCqiResPerTti;
   LrmUlDlConfig enUlDlConfig;
   LrmSplSfConfig enSplSfCfg;
   CmRrmDsrTransMax enDsrTransMax;
   Bool bSimulCqiAckNack;
   U8 bArpForEmergencyBearer;
   LrmSpsCellConfigData stSpsCellCfg;
   U32 utNumOfPrbRpts;
   U32 utPrbRptInterval;

   U8 bMaxAvgGbrPrbUsage;
   U16 bRbcQci1TmngReq;
   U8 bRbcQci2TmngReq;
   U8 bRbcQci3TmngReq;
   U8 bRbcQci4TmngReq;
   U8 bRbcQci4TmngReqEnable;
   U8 bNumDlNewUesPerTti;
   U8 bNumUlNewUesPerTti;
   U8 bNumDlReTxUesPerTti;
   U8 bNumUlReTxUesPerTti;
   U8 bDuplexMode;
   U8 usAccessMode;
   U16 usMaxNonCsgUes;
   U16 usMaxCsgUes;
   U16 usMaxExtraUes;

   U8 usMaxDlUePerTti;
   Bool bIsCaEnabled;

} LrmCellConfigData;


typedef struct lrmCellConfiguration
{
 LrmCfgAction enCellAddModDel;
 LrmCellConfigData stCellCfgInfo;
 U16 usReCfgType;
} LrmCellConfiguration;

typedef struct lrmCellCfgRsp
{
 LrmStatusCause statusInfo;
 U8 bCellId;
} LrmCellCfgRsp;

typedef struct lrmEnodebCfgResp
{
 LrmStatusCause statusInfo;
} LrmEnodebCfgResp;
typedef struct lrmMmeCfg
{
   LrmCfgAction enMmeAddModOrDel;
   U16 usMmeId;
} LrmMmeCfg;




typedef struct lrmEnbConfiguration
{
 U8 bCfgType;
   union
   {
    U8 bMaxNumCells;
    LrmMmeCfg stMmeCfg;
   } u;
} LrmEnbConfiguration;

typedef enum lrmCfgType
{
 LRM_ENB_CONFIG,
 LRM_CELL_CONFIG
}LrmCfgType;

typedef struct rmProtoCfg
{
 LrmCfgType bCfgType;
 union
 {
  LrmCellConfiguration stCellCfg;
  LrmEnbConfiguration stEnbCfg;
 } u;
} RmProtoCfg;





typedef struct rmUstaDgn
{
  U8 bType;
  union {
     Mem stMem;
  }u;
} RmUstaDgn;




typedef struct lrmRmUsta
{
   CmAlarm alarm;
   RmUstaDgn stDgn;
} LrmRmUsta;
typedef enum lrmEnbStaType
{
   LRM_ENBSTATYPE_CELLUP,
   LRM_ENBSTATYPE_CPULOAD
}LrmEnbStaType;
typedef struct lrmEnbStaInd
{
   LrmEnbStaType enStaType;
   union {
      U8 bCpuLoad;
      U8 bCellId;
   }u;
} LrmEnbStaInd;




typedef struct rmUsta
{
   U8 bStaType;
   union {
      LrmEnbStaInd stEnbStaInfo;
      LrmRmUsta stAlarm;
   }u;
} RmUsta;






typedef struct rmMngmt
{
   Header hdr;
   CmStatus cfm;
   union
   {
      RmCfg cfg;
      RmCntrl cntrl;
      RmProtoCfg protoCfg;
      RmUsta usta;
   }t;
} RmMngmt;





typedef S16 (*LrmCfgReq) ( Pst *pst, RmMngmt *cfg )


       ;

typedef S16 (*LrmCfgCfm) ( Pst *pst, RmMngmt *cfg )


       ;

typedef S16 (*LrmCntrlReq) ( Pst *pst, RmMngmt *cntrl )


       ;

typedef S16 (*LrmEnbStatusInd) ( Pst *pst, RmMngmt *usta )


       ;


typedef S16 (*LrmStaInd) ( Pst *pst, RmMngmt *usta )


       ;

typedef S16 (*LrmCntrlCfm) ( Pst *pst, RmMngmt *usta )


       ;
extern S16 RmMiLrmCfgReq (Pst *pst, RmMngmt *cfg);
extern S16 RmMiLrmCntrlReq (Pst *pst, RmMngmt *cntrl);
extern S16 RmMiLrmCfgCfm (Pst *pst, RmMngmt *cfm);
extern S16 RmMiLrmCntrlReq (Pst *pst, RmMngmt *cntrl);
extern S16 RmMiLrmCntrlCfm ( Pst *pst, RmMngmt *cfm);
extern S16 RmMiLrmEnbStaInd (Pst *pst, RmMngmt *usta);
extern S16 RmMiLrmStaInd (Pst *pst, RmMngmt *usta);
extern S16 cmPkLwLcLrmCfgReq ( Pst * pst, RmMngmt * cfg )


  ;




extern S16 cmUnpkLwLcLrmCfgReq ( LrmCfgReq func, Pst *pst, Buffer *mBuf )



  ;



extern S16 cmPkLwLcLrmCfgCfm ( Pst * pst, RmMngmt * cfm )


  ;


extern S16 cmUnpkLwLcLrmCfgCfm ( LrmCfgCfm func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmUnpkLwLcLrmCntrlReq ( LrmCntrlReq func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkLwLcLrmCntrlReq ( Pst * pst, RmMngmt * cntrl )


  ;


extern S16 cmPkLwLcLrmCntrlCfm ( Pst * pst, RmMngmt * cfm )


  ;


extern S16 cmUnpkLwLcLrmCntrlCfm ( LrmCntrlCfm func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkLwLcLrmEnbStaInd ( Pst * pst, RmMngmt * usta )


  ;



extern S16 cmPkLwLcLrmStaInd ( Pst * pst, RmMngmt * usta )


  ;


extern S16 cmUnpkLwLcLrmEnbStaInd ( LrmEnbStatusInd func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmUnpkLwLcLrmStaInd ( LrmStaInd func, Pst * pst, Buffer *mBuf )



  ;
extern S16 cmPkLrmCfgReq ( Pst * pst, RmMngmt * cfg )


  ;


extern S16 cmUnpkLrmCfgReq ( LrmCfgReq func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkLrmCfgCfm ( Pst * pst, RmMngmt * cfm )


  ;


extern S16 cmUnpkLrmCfgCfm ( LrmCfgCfm func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmUnpkLrmCntrlReq ( LrmCntrlReq func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkLrmEnbStaInd ( Pst * pst, RmMngmt * usta )


  ;


extern S16 cmUnpkLrmEnbStaInd ( LrmStaInd func, Pst * pst, Buffer *mBuf )



  ;



extern S16 cmPkLrmStaInd ( Pst * pst, RmMngmt * usta )


  ;


extern S16 cmUnpkLrmStaInd ( LrmStaInd func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrmCntrlReq ( Pst * pst, RmMngmt * cntrl )


  ;


extern S16 cmUnpkLrmCntrlReq ( LrmCntrlReq func, Pst * pst, Buffer *mBuf )



  ;


extern S16 cmPkLrmCntrlCfm ( Pst * pst, RmMngmt * cfm )


  ;


extern S16 cmUnpkLrmCntrlCfm ( LrmCntrlCfm func, Pst * pst, Buffer *mBuf )



  ;
extern S16 cmPkRmGenCfg ( RmGenCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRmGenCfg ( RmGenCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRmUpSapCfg ( RmUSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRmUpSapCfg ( RmUSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRmLowSapCfg ( RmLSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmUnpkRmLowSapCfg ( RmLSapCfg *param, Buffer *mBuf )


  ;
extern S16 cmPkRmCfg ( RmCfg *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkRmCfg ( RmCfg *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmPkRmCntrl ( RmCntrl *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmUnpkRmCntrl ( RmCntrl *param, S16 elmnt, Buffer *mBuf )



  ;
extern S16 cmPkRmMngmt ( Pst *pst, RmMngmt *param, U8 eventType, Buffer *mBuf )




  ;
extern S16 cmUnpkRmMngmt ( Pst *pst, RmMngmt *param, U8 eventType, Buffer *mBuf )




  ;


extern S16 rrmInit(U8 itfType);
extern S16 rmActvTsk(Pst *pst,Buffer *mBuf);
extern S16 rmActvInit( Ent entity,
                       Inst inst,
                       Region region,
                       Reason reason
                     );



}
extern "C" {
}
extern "C" {
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


}

extern "C" {


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




}




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
typedef enum RmUeTxnMode
{
   RM_UE_TXN_MODE1,
   RM_UE_TXN_MODE2,
   RM_UE_TXN_MODE3,
   RM_UE_TXN_MODE4,
   RM_UE_TXN_MODE5,
   RM_UE_TXN_MODE6,
   RM_UE_TXN_MODE7
} RmUeTxnMode;
typedef struct rmUiSapCb
{
   Pst pst;
   SuId suId;
   SpId spId;
   State sapState;
   Mem mem;
   CmTimer timer;
   U8 bndRetryCnt;
   U8 maxBndRetry;
   U8 numBndRetries;
   TmrCfg bndTmr;
} RmUiSapCb;
typedef struct rmliSapCb
{
   Pst pst;
   SuId suId;
   SpId spId;
   State sapState;
   Mem mem;
   CmTimer timer;
   U8 bndRetryCnt;
   U8 maxBndRetry;
   U8 numBndRetries;
   TmrCfg bndTmr;
} RmLiSapCb;







typedef struct rmLmResponse
{
   TranId transId;
   Resp response;
}RmLmResponse;






typedef struct rmGenCb
{
   U8 tmrRes;
   RmLmResponse bndCfmResp;
   Status memUpperThr;
   Status memLowerThr;
}RmGenCb;
typedef struct rmCb
{
   Mem mem;
   RmGenCb genCfg;
   CmTqCp tmrTqCp;
   CmTqType tmrTq[10];
   TskInit rmInit;
   Header lmHdr;
   RmUiSapCb rmuSap;
   RmLiSapCb rgmSap;
   CmTimer tmrBlk[1];
} RmCb;



extern S16 rmLIMRgmBndReq ( SuId suId, SpId spId)

                                    ;

extern S16 rmLIMRgmUbndReq ( SuId suId, Reason reason)

                                      ;




extern S16 rmLrmStartTmr (S16 tmrEvnt, U32 tmrVal, U32 cb);
extern S16 rmLrmStopTmr (S16 tmrEvnt, U32 cb);
extern S16 rmLrmTmrExpiry (U32 cb, S16 tmrEvnt);



extern S16 rmLrmBndCfm (SuId suId, U8 status);
extern S16 rmActvTmr (Ent ent, Inst inst );

extern RmCb g_stRmCb;
enum rmGbrQciNum
{
   RM_QCI_ONE=1,
   RM_QCI_TWO,
   RM_QCI_THREE,
   RM_QCI_FOUR
};
typedef struct rrmErabAdmitted
{
   U32 uiReqPrbForDl;
   U32 uiReqPrbForUl;
   U8 bERabId;
} RrmErabAdmitted;
typedef struct rrmErabRejected
{
   U32 uiReqPrbForDl;
   U32 uiReqPrbForUl;
   U32 uiDiffPrbForDl;
   U32 uiDiffPrbForUl;
   U32 uiQci;
   U8 bArpVal;
   U8 bCause;
   U8 bERabId;
   bool bIsPreemptable;
   bool bErabPreemptCap;
   bool bIsModifyReq;
} RrmErabRejected;
typedef struct rrmRbcRspInfo
{
  RrmErabAdmitted eRabAcceptedLst[8];
  RrmErabRejected eRabRejectedLst[8];
  U8 nErabsAccepted;
  U8 nErabsRejected;
  bool isGBRBearerExists;
  U16 usCRNTI;
} RrmRbcRspInfo;


typedef struct rmTddUlSfInfo
{
   U8 bNumUlSfs;
   U8 bUlSfNum[10];
} RmTddUlSfInfo;


typedef enum rmDuplexMode
{
    RM_MODE_FDD=1,
    RM_MODE_TDD
} RmDuplexMode;

class CRmRcmResMgr
{
   public:
    U16 getAvailUlSubframeLst(U16 usSrPrdcty, U16 *usAvalUlSfs);
    static U8 getNumUlSf(LrmUlDlConfig enUlDlConfig);

   public:
      static RmTddUlSfInfo m_astRmTddUlSfInfo[LRM_UL_DL_CONFIG_MAX];

   public:
      LrmUlDlConfig m_enUlDlCfg;
      U16 m_usMaxActiveUeCount;
      U16 m_usMaxDlUePerTti;
      U16 m_usN1Pucch;
};


inline U8 CRmRcmResMgr::getNumUlSf(LrmUlDlConfig enUlDlConfig)
{
   return m_astRmTddUlSfInfo[enUlDlConfig].bNumUlSfs;
}

inline U8* rrmAlloc(U16 usMsgLen)
{
 U8 *pbMsg;
 { if (SGetSBuf(g_stRmCb.rmInit.region, g_stRmCb.rmInit.pool, (Data **)(&pbMsg), (usMsgLen)) == 0) { { cmMemset((U8 *)((*(&pbMsg))), 0, ((usMsgLen))); }; } else { (*(&pbMsg)) = 0L; } };
 return pbMsg;
}

inline void rrmFree(U8* pbMsg, U16 usMsgLen)
{
 { (void) SPutSBuf(g_stRmCb.rmInit.region, g_stRmCb.rmInit.pool, (Data *) (pbMsg), (Size) (usMsgLen)); (pbMsg) = 0L; };
}
typedef enum rmQciPriority
{
   RM_QCI_PRIORITY_VAL1 = 1,
   RM_QCI_PRIORITY_VAL2,
   RM_QCI_PRIORITY_VAL3,
   RM_QCI_PRIORITY_VAL4,
   RM_QCI_PRIORITY_VAL5,
   RM_QCI_PRIORITY_VAL6,
   RM_QCI_PRIORITY_VAL7,
   RM_QCI_PRIORITY_VAL8,
   RM_QCI_PRIORITY_VAL9,
   RM_QCI_MAX_VALUE
} RmQciPriority;

U8 getQciPriority(U8 bQci);


typedef U8 RmTddNumDlSubfrmTbl[LRM_UL_DL_CONFIG_MAX][10];
extern RmTddNumDlSubfrmTbl rmTddNumDlSubfrmTbl;


typedef U8 RmTddNumUlSubfrmTbl[LRM_UL_DL_CONFIG_MAX][10];
extern RmTddNumUlSubfrmTbl rmTddNumUlSubfrmTbl;
void getTotalNumberOfDlUlSubframes(LrmUlDlConfig cfgMode,
                                   U32 timingReqInMs,
                                   U32 *totalNumDlSf,
                                   U32 *totalNumUlSf);
U8 getNumPrbs(LrmCellBandwidth enDlBw);
U32 getNumDlSubFramesPerFrame(U32 bCfgMode);
U32 getNumUlSubFramesPerFrame(U32 bCfgMode);
RmuUErabAddModIe *getRbAddModIe(RmuErabConfigIe & stERAB, U8 bErabId);


bool isGbrBearer(U32 qci);


bool isValidQci(U32 qci);

U8 g_bQciToPriorityMap[RM_QCI_MAX_VALUE] =
{
 RM_QCI_PRIORITY_VAL2,
 RM_QCI_PRIORITY_VAL4,
 RM_QCI_PRIORITY_VAL3,
 RM_QCI_PRIORITY_VAL5,
 RM_QCI_PRIORITY_VAL1,
 RM_QCI_PRIORITY_VAL6,
 RM_QCI_PRIORITY_VAL7,
 RM_QCI_PRIORITY_VAL8,
 RM_QCI_PRIORITY_VAL9
};

U8 getQciPriority(U8 bQci)
{
 return ((bQci > RM_QCI_MAX_VALUE) || (bQci == 0)) ? 255 : (g_bQciToPriorityMap[bQci-1]);
}





 RmTddNumDlSubfrmTbl rmTddNumDlSubfrmTbl = {
        {1, 2, 2, 2, 2, 3, 4, 4, 4, 4},
        {1, 2, 2, 2, 3, 4, 5, 5, 5, 6},
        {1, 2, 2, 3, 4, 5, 6, 6, 7, 8},
        {1, 2, 2, 2, 2, 3, 4, 5, 6, 7},
        {1, 2, 2, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 2, 2, 2, 3, 4, 4, 4, 5}
};





 RmTddNumUlSubfrmTbl rmTddNumUlSubfrmTbl = {
        {0, 0, 1, 2, 3, 3, 3, 4, 5, 6},
        {0, 0, 1, 2, 2, 2, 2, 3, 4, 4},
        {0, 0, 1, 1, 1, 1, 1, 2, 2, 2},
        {0, 0, 1, 2, 3, 3, 3, 3, 3, 3},
        {0, 0, 1, 2, 2, 2, 2, 2, 2, 2},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 2, 3, 3, 3, 4, 5, 5}
};

void getTotalNumberOfDlUlSubframes(LrmUlDlConfig cfgMode,
                                   U32 timingReqInMs,
                                   U32 *totalNumDlSf,
                                   U32 *totalNumUlSf)
{

   U8 numOfDlPlusSpecialSfsPerFrame = rmTddNumDlSubfrmTbl[cfgMode][10 -1];

   U8 numOfUlSfsPerFrame = rmTddNumUlSubfrmTbl[cfgMode][10 -1];
   U8 numOfSubFramesLessThanFrame;



   *totalNumDlSf = numOfDlPlusSpecialSfsPerFrame * (timingReqInMs/10);



   *totalNumUlSf = numOfUlSfsPerFrame * (timingReqInMs/10);


   numOfSubFramesLessThanFrame = timingReqInMs % 10;


   if(numOfSubFramesLessThanFrame != 0)
   {
      (*totalNumDlSf) += rmTddNumDlSubfrmTbl[cfgMode][numOfSubFramesLessThanFrame];
      (*totalNumUlSf) += rmTddNumUlSubfrmTbl[cfgMode][numOfSubFramesLessThanFrame];
   }
   return;
}

bool isGbrBearer(U32 bQci)
{
   return (bQci >= 1 && bQci <= 4);
}

bool isValidQci(U32 bQci)
{
   return (bQci >= 1 && bQci <= 9);
}

U32 getNumDlSubFramesPerFrame(U32 bCfgMode)
{
   return (rmTddNumDlSubfrmTbl[bCfgMode][10 -1]);
}

U32 getNumUlSubFramesPerFrame(U32 bCfgMode)
{
   return (rmTddNumUlSubfrmTbl[bCfgMode][10 -1]);
}

U8 getNumPrbs(LrmCellBandwidth enDlBw)
{
   U8 bNumRbs;

   switch(enDlBw)
   {
      case LRM_BANDWIDTH_25:
      {
         bNumRbs = 25;
      }
      break;

      case LRM_BANDWIDTH_50:
      {
         bNumRbs = 50;
      }
      break;

      case LRM_BANDWIDTH_75:
      {
         bNumRbs = 75;
      }
      break;

      case LRM_BANDWIDTH_100:
      {
         bNumRbs = 100;
      }
      break;

      default:
      {
         if( L_ERROR < g_logLevel || g_modMask & RLOG_MODULE_ID){ logLev1(0xa00001, L_ERROR, enDlBw, "/home/mrehwald/Desktop/Radisys/lte_enb/src/lterrm/src/rm_utils.cpp"         , 156         , "Invalid Bandwidth Configuration [%d]. " "Assuming MAX PRBS as 100", RLOG_FILE_ID, RLOG_MODULE_NAME); }
                                                  ;
         bNumRbs = 100;
         break;
      }
   }
   return bNumRbs;
}

RmuUErabAddModIe *getRbAddModIe(RmuErabConfigIe & stERAB, U8 bErabId)
{
   U32 uiRbIdx;
   for(uiRbIdx = 0; uiRbIdx < stERAB.usNoErabsToAddMod; uiRbIdx++)
   {
      if(stERAB.stErabAddModLst[uiRbIdx].bErabId == bErabId)
      {
         return(&stERAB.stErabAddModLst[uiRbIdx]);
      }
   }
   return(0L);
}
