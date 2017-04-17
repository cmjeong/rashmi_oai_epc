
/*
 * SSI license header file
 */
#ifdef SS_MT
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#endif /* SS_MT */

#ifndef WIN32
#include <time.h>
#endif /* WIN32 */

#ifdef SS_VW
#include <sys/times.h>
#include <ioLib.h>
#include <sockLib.h>
#include <selectLib.h>
#include <hostLib.h>
#include <stdio.h>
#define SS_LIC_PORT 1234 /* license server port */
#endif /* SS_VW */

#ifndef _CCPU_TYPE_SHORTCUTS_
#define _CCPU_TYPE_SHORTCUTS_
typedef unsigned int u32_t;
typedef unsigned long long u64_t;
#endif /* _CCPU_TYPE_SHORTCUTS_ */

typedef unsigned int ccc_opaque_t;
typedef unsigned long long ccc_key_t[2];
typedef unsigned long long ccc_state_t[4];

#define _KEY_HALF_LEN 16
#define _IS_CRLF(x) (((x) == '\r') || ((x) == '\n'))
#define _IS_SPACETAB(x) (((x) == ' ') || ((x) == '\t'))
#define	_IS_COMMENT(x) ((x) == '#')
#define _IS_HEX(x) (				\
	((x) >= '0' && (x) <= '9') ||	\
	((x) >= 'a' && (x) <= 'f') ||	\
	((x) >= 'A' && (x) <= 'F')		\
)
#define _HEXVAL(x) (								\
	((x) >= '0' && (x) <= '9') ? (x) - '0' :		\
	((x) >= 'a' && (x) <= 'f') ? (x) + 10 - 'a' :	\
	(x) + 10 - 'A'									\
)

typedef enum {
	_INIT,
	_LEFT,
	_RIGHT,
	_FULL
} license_parse_state_t;

typedef struct license {
	u32_t	type;
	u32_t	n_uint32;
	u64_t	left;
	u64_t	right;
} license_t;

#define DEFAULT_INFILE "license"
#define	MAX_USEFUL_LINE	256		/* don't look further than this for valid data*/
#ifdef SS_VW
   char   gli[MAX_USEFUL_LINE]; 
#endif /* SS_VW */

typedef enum {
  no_multi_core = 1,
  multi_core = 2,
  other = 3,
  Super  = 99
} ccc_feature_t;

/*
 * binary licenses as they appear in the file.
 * len unit is u32_t and inclusive of type/len, which implies that records
 * are 32 bit aligned, no more, no less.
 *
 * type is:
 * 1) upSuite license - len == 6, key == 2x64 bit words.
 */


typedef enum {
  upSuite = 1
} ccc_lic_type_t;

/*
 * use inline versions of the functions (only version supported right now...)
 */
#ifndef INLINE
#define INLINE inline
#endif

/*
 * how much rotation??
 */
#define ROT	3

/*
 * handy global macros
 */
#define CCC_VERSION(x,y) (((x)<<5) | (y))
#define CCC_MAJOR(x)	((x)>>5)
#define CCC_MINOR(x)	((x)&0x1f)


/*
 * state layout
 */
enum { rota, rotb, xa, xb };

/*
 * key layout
 */

typedef struct {
#if defined(_BIT_FIELDS_HTOL)
/*
 * 40 data, 16 random, 8 checksum
 */
    u64_t
    hostid1:12,
      time2:8,
      cf2:1,
      feature1:8,
      tf2:1,
      major:4,
      countm:5,
      hf1:1,
      check1:8,
      rand1:16;
/*
 * 39 data, 17 random, 8 checksum
 */
    u64_t
    hf2:1,
      time1:8,
      cf1:1,
      minor:5,
      tf1:1,
      counte:3,
      hostid2:12,
      feature2:8,
      rand2:17,
      check2:8;

#else  /* little endian */
/*
 * 40 data, 16 random, 8 checksum
 */
    u64_t
    rand1:16,
      check1:8,
      hf1:1,
      countm:5,
      major:4,
      tf2:1,
      feature1:8,
      cf2:1,
      time2:8,
      hostid1:12;

/*
 * 39 data, 17 random, 8 checksum
 */
    u64_t
    check2:8,
      rand2:17,
      feature2:8,
      hostid2:12,
      counte:3,
      tf1:1,
      minor:5,
      cf1:1,
      time1:8,
      hf2:1;
#endif /* endianness */
} bits_t;



#define tf1     bits.tf1
#define tf2     bits.tf2
#define hf1     bits.hf1
#define hf2     bits.hf2
#define cf1     bits.cf1
#define cf2     bits.cf2

#define hostid1 bits.hostid1
#define hostid2 bits.hostid2

#define time1   bits.time1
#define time2   bits.time2

#define feature1  bits.feature1
#define feature2  bits.feature2

#define major1	bits.major
#define minor1	bits.minor

#define countm	bits.countm
#define counte	bits.counte

#define check1  bits.check1
#define check2  bits.check2
#define rand1   bits.rand1
#define rand2   bits.rand2

#define CHECK1 (rand1 + hostid2) * (rand2 + hostid1) * \
    (rand2 + time1) * (rand1 + time2) + (hf2 + cf2 + tf2 + rand1 + major1)

#define CHECK2  (rand2 + feature1) * (rand1 + feature2) * \
    (rand2 + countm) * (rand1 + counte) + (hf1 + cf1 + tf1 + rand2 + minor1)


/*
 * support routines used for playing with bits.
 */


/*
 * rand(3) LCG - not good for being random, but 1 to 1 on mappings, so
 * it's a useful hash.
 */
static INLINE ccc_opaque_t
next_rand(x)
{
  return(x * 1103515245 + 12345);
}

/*
 * rotate right
 */
static INLINE u64_t
ror(u64_t x, u64_t bits)
{
  if ((bits &= 63) == 0) return(x);
  else return((x>>bits) | (x<<(64-bits)));
}

/*
 * rotate left
 */
static INLINE u64_t
rol(u64_t x, u64_t bits)
{
  if ((bits &= 63) == 0) return(x);
  else return((x<<bits) | (x>>(64-bits)));
}

/*
 * run the feedback generator forward a number of times. (encrypt)
 */
static INLINE void
in(ccc_state_t ks, int r, int n)
{
  u64_t	a = ks[rota], b = ks[rotb];

  while(n--) {
    a += b; a = rol(a, r); b += a; b = rol(b, r);
  }

  ks[rota] = a; ks[rotb] = b;
}

/*
 * run the generator backward a number of times (decrypt)
 */
static INLINE void
out(ccc_state_t ks, int r, int n)
{
  u64_t	a = ks[rota], b = ks[rotb];

  while(n--) {
    b = ror(b, r); b -= a; a = ror(a, r); a -= b;
  }

  ks[rota] = a; ks[rotb] = b;
}

/*
 * spread bits - low 32 bits go to odd bits (backwards) hi 32 bits
 * go to even bits (in order)
 */
static INLINE u64_t
shuffle(u64_t in)
{
  int	    i;
  u64_t	    even = 0, odd = 0;

  i = 32;
  while(i--) {
    odd <<= 2;
    if (in & 1) odd |= 1;
    in >>= 1;
  }

  i = 32;
  while(i--) {
    even >>= 2;
    if (in & 1) even |= 0x8000000000000000ULL;
    in >>= 1;
  }

  return(even | odd);
}

/*
 * odd bits go to low 32 bits (backwards), even bits go to hi 32 bits
 */
static INLINE u64_t
unshuffle(u64_t in)
{
  int	    i;
  u64_t	    high = 0, low = 0;

  i = 32;
  while(i--) {
    low <<= 1;
    high >>= 1;
    if (in & 1) low |= 1;
    if (in & 2) high |= 0x80000000;
    in >>= 2;
  }
  return((high << 32) | low);
}

/*
 * return count encoded as 5.3 encoded count - we bias by 1 so that
 * 0 isn't wasted.
 */

#define CCC_EXP	3
#define CCC_MANT 5

static INLINE u32_t
itoc(u32_t count)
{
  u32_t	e = 0;

  --count;
  while (count >= (1<<CCC_MANT)) {
    ++e; count >>= 1;
  }
  return((count<<CCC_EXP) | e);
}

/*
 * return in from encoded 5.3 count
 */

static INLINE u32_t
ctoi(u32_t count)
{
  u32_t m = count>>CCC_EXP, e = count & ((1<<CCC_EXP)-1);

  return((m+1)<<e);
}



/*
 * first state - take the host id (prev) and set up the XOR stuff
 */
static INLINE ccc_opaque_t
key_1_init(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  ccc_state_t	gen;

/*
 * use a function of the host ID to generate the XOR mask
 */
  gen[rota] = prev*prev*prev;
  gen[rotb] = 0x9a31903932d9c024ULL;
  gen[xa] = gen[xb] = 0;

  in(gen, ROT, 513);

  state[rota] = key[0];
  state[rotb] = key[1];

  state[xa] = gen[rota];
  state[xb] = gen[rotb];

  return(prev);
}

/*
 * decode halfway.
 */
static INLINE ccc_opaque_t
key_2_init(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, 512);
  state[rota] ^= state[xa];
  state[rotb] ^= state[xb];
  return(prev);
}

/*
 * decode all the way, do the checksum, then encode and
 * shuffle.  Everybody after this extracts with:
 * 1) out(23)
 * 2) double unshuffle
 */
static INLINE ccc_opaque_t
key_3_init(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  union { bits_t bits; ccc_key_t key; } uu;
  ccc_opaque_t	checka, checkb;

#define bits uu.bits

  out(state, ROT, 512);
  uu.key[0] = unshuffle(unshuffle(unshuffle(state[rota])));
  uu.key[1] = shuffle(shuffle(shuffle(state[rotb])));
  checka = (CHECK1) & 0xff;
  checkb = (CHECK2) & 0xff;

#undef bits

  state[rota] = shuffle(shuffle(uu.key[0]));
  state[rotb] = shuffle(shuffle(uu.key[1]));
  in(state, ROT, 23);

  return((checka == uu.check1) && (checkb == uu.check2));
}

/*
 * ::HOSTID - kind of redundant, but there you are.
 */
static INLINE ccc_opaque_t
key_1_hostid(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  prev = next_rand(prev);
  in(state, ROT, 2*(prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_2_hostid(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, (prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_3_hostid(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, 23);
  return(prev);
}

static INLINE int
key_ok_hostid(ccc_opaque_t hostid, ccc_opaque_t prev,
	      ccc_key_t key, ccc_state_t state)
{
  ccc_opaque_t	    foo;
  union { bits_t bits; ccc_key_t key; } uu;

  out(state, ROT, (prev & 0xff));
  uu.key[0] = unshuffle(unshuffle(state[rota]));
  foo = uu.hostid1;
  uu.key[1] = unshuffle(unshuffle(state[rotb]));
  foo = foo + (uu.hostid2<<12);
  in(state, ROT, 23);
  return(prev == next_rand(foo));
}

/*
 * ::FEATURE
 */
static INLINE ccc_opaque_t
key_1_feature(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  prev = next_rand(prev);
  in(state, ROT, 2*(prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_2_feature(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, (prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_3_feature(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, 23);
  return(prev);
}

static INLINE int
key_ok_feature(ccc_opaque_t feature, ccc_opaque_t prev,
	      ccc_key_t key, ccc_state_t state)
{
  ccc_opaque_t	    foo;
  union { bits_t bits; ccc_key_t key; } uu;

  out(state, ROT, (prev & 0xff));
  uu.key[0] = unshuffle(unshuffle(state[rota]));
  foo = uu.feature1;
  uu.key[1] = unshuffle(unshuffle(state[rotb]));
  foo = foo + (uu.feature2<<8);
  in(state, ROT, 23);
  return(prev == next_rand(foo));
}

/*
 * ::DATE
 */
static INLINE ccc_opaque_t
key_1_date(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  prev = next_rand(prev);
  in(state, ROT, 2*(prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_2_date(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, (prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_3_date(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, 23);
  return(prev);
}

static INLINE int
key_ok_date(ccc_opaque_t date, ccc_opaque_t prev,
	      ccc_key_t key, ccc_state_t state)
{
  ccc_opaque_t	    foo;
  union { bits_t bits; ccc_key_t key; } uu;

  out(state, ROT, (prev & 0xff));
  uu.key[1] = unshuffle(unshuffle(state[rotb]));
  foo = uu.time1;
  uu.key[0] = unshuffle(unshuffle(state[rota]));
  foo = foo + (uu.time2<<8);
  in(state, ROT, 23);
  return((date>>16) < foo || (!uu.tf1 && !uu.tf2));
}


/*
 * ::VERSION
 */
static INLINE ccc_opaque_t
key_1_version(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  prev = next_rand(prev);
  in(state, ROT, 2*(prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_2_version(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, (prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_3_version(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, 23);
  return(prev);
}

static INLINE int
key_ok_version(ccc_opaque_t version, ccc_opaque_t prev,
	      ccc_key_t key, ccc_state_t state)
{
  ccc_opaque_t	    foo;
  union { bits_t bits; ccc_key_t key; } uu;

  out(state, ROT, (prev & 0xff));
  uu.key[0] = unshuffle(unshuffle(state[rota]));
  uu.key[1] = unshuffle(unshuffle(state[rotb]));
  foo = CCC_VERSION(uu.major1, uu.minor1);
  in(state, ROT, 23);
  return(version <= foo);
}


/*
 * ::COUNT
 */
static INLINE ccc_opaque_t
key_1_count(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  prev = next_rand(prev);
  in(state, ROT, 2*(prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_2_count(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, (prev & 0xff));
  return(prev);
}
static INLINE ccc_opaque_t
key_3_count(ccc_opaque_t prev, ccc_key_t key, ccc_state_t state)
{
  out(state, ROT, 23);
  return(prev);
}

static INLINE int
key_ok_count(ccc_opaque_t count, ccc_opaque_t prev,
	      ccc_key_t key, ccc_state_t state)
{
  ccc_opaque_t	    foo;
  union { bits_t bits; ccc_key_t key; } uu;

  out(state, ROT, (prev & 0xff));
  uu.key[0] = unshuffle(unshuffle(state[rota]));
  foo = uu.countm;
  uu.key[1] = unshuffle(unshuffle(state[rotb]));
  foo = (foo<<5) | uu.counte;
  in(state, ROT, 23);
  return(count <= ctoi(foo) || (!uu.cf1 && !uu.cf2));
}

#define _LICENSE_FILE "license"

static INLINE int _check_key(ccc_key_t key, u32_t hostid, u32_t ttl);
static INLINE int _get_keys(u32_t ttl);

/*
 * Fake hostids used in customer-specific, non-host-specific licenses.
 */
enum {
  FAKE_HOSTID_FIRST_ = 0x004e544c,  /* Nortel Networks */
  FAKE_HOSTID_LIMIT_ = (FAKE_HOSTID_FIRST_ + 1024)
};

/*
 * We are fed one line at a time. Caller depends on us to manipluate 
 * the passed in pointer, li. 
 */
static int
extract_license(unsigned char *li, license_t *lp)
{
	u64_t	left = 0, right = 0;
	int			c, hexcount = 0;
	license_parse_state_t state = _INIT;

	lp->type = 0x00000001;
	lp->n_uint32 = 6;

	while ((c = *li++) != 0) {

		if (_IS_SPACETAB(c)) {
			continue;
		} else if (_IS_CRLF(c) || _IS_COMMENT(c)) {
			break;
		}

		switch (state) {
		case _INIT:
			if (_IS_HEX(c)) {
				hexcount = 1;
				left = _HEXVAL(c);
				state = _LEFT;
			} else {
				return 0;
			}
			break;
		case _LEFT:
			if (_IS_HEX(c)) {
				left <<= 4;
				left += _HEXVAL(c);
				if (++hexcount >= _KEY_HALF_LEN) {
					hexcount = 0;
					state = _RIGHT;
				}
			} else {
				return 0;
			}
			break;
		case _RIGHT:
			if (_IS_HEX(c)) {
				right <<= 4;
				right += _HEXVAL(c);
				if (++hexcount >= _KEY_HALF_LEN) {
					lp->left = left;
					lp->right = right;
					state = _FULL;
				}
			} else {
				return 0;
			}
			break;
		case _FULL:
			/* 
			 * We are here because both the left portion of a license and the 
			 * right portion of a license had been found and there is a character
			 * other than a white-space or a comment character afterwards. Note:
			 * if a comment character is found, line parsing ends and we would
			 * not get to this point.
			 */
			return 0;
			break;
		default:
#ifndef SS_VW
			printf("%s", "Illegal state found in extract_license!\n");
#endif /* SS_VW */
			return (-1);
		}
	}

	if (state == _INIT) {
		return 0;
	}
	if (state == _FULL) {
		return 1;
	}
	return 0;
}


static INLINE int
_get_keys(u32_t ttl)
{

   char   li[MAX_USEFUL_LINE]; 
	license_t   lisense;
	ccc_key_t   ccc_key;
	int      retval = -1;
#ifdef SS_VW
	int fd;
	struct sockaddr_in licSrvAddr;
	struct sockaddr_in lsrv;
	struct fd_set lcselfds;
	struct timeval tv = {0};
	struct timeval *ptv;
	int adlen = sizeof(lsrv);

	if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		printf("%s", "Error creating socket for license \n");
		return retval;
	}
	licSrvAddr.sin_family = AF_INET;
	licSrvAddr.sin_port = htons(SS_LIC_PORT);
	licSrvAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(fd, (struct sockaddr*)&licSrvAddr, sizeof(struct sockaddr)) < 0)
        {
		printf("%s", "Error binding \n");
		return retval;
        }
	FD_ZERO(&lcselfds);
	FD_SET(fd, &lcselfds);
	tv.tv_sec = 30;
	tv.tv_usec = 0;


	if (ttl)
	{
		ptv = &tv;
	}
	else
	{
		ptv = NULL;
	}

	if (select(fd+1, &lcselfds, 0, 0, ptv) < 0)
	{
		printf("Error waiting for lic server\n");
	}
	else if (FD_ISSET(fd, &lcselfds))
	{
	   memset(li, 0, MAX_USEFUL_LINE);
	   if (recvfrom(fd, li, MAX_USEFUL_LINE, 0, (struct sockaddr*)&lsrv, &adlen) < 0)
	   {
		   printf("%s", "Nothing received from client \n");
	   }
	   strcpy(gli, li);
	}
	else
	{
	   strcpy(li, gli);
	}

#else
	FILE     *inFp;

	if ((inFp = fopen(_LICENSE_FILE, "r")) == NULL) return (-1);

	while (fgets(li, MAX_USEFUL_LINE, inFp) != NULL)
#endif /* SS_VW */
	{

	   /* search for a valid license line */
		if (extract_license(li, &lisense))
		{
            struct lisense {
               u32_t type;
               u32_t n_uint32;
               u32_t license[4];
            } *lp = (struct lisense *)&lisense;

		      u32_t fake;
      
	         retval = -1;
      
		      /* We only support type 1 licenses. */
#ifndef SS_VW
		      if (lp->type != 0x00000001) continue;
		      if (lp->n_uint32 != 6) continue;
#endif /* SS_VW */
		      
		      /* OK, it looks like a license... */
      
		      /*
		       * 32 bit alignment is guaranteed, but not 64, so take
		       * it 32 at a time.
		       */
		      /*#ifndef __linux__  */
            #if defined(sparc)
		      ccc_key[0] = lp->license[0];
		      ccc_key[0] <<= 32;
		      ccc_key[0] |= lp->license[1];
		      ccc_key[1] = lp->license[2];
		      ccc_key[1] <<= 32;
		      ccc_key[1] |= lp->license[3];
            #else
		      /* linux or solarix x86 */
		      ccc_key[0] = lp->license[1];
              ccc_key[0] <<= 32;
              ccc_key[0] |= lp->license[0];
              ccc_key[1] = lp->license[3];
              ccc_key[1] <<= 32;
              ccc_key[1] |= lp->license[2];
            #endif
#ifdef SS_MT
		      if (! _check_key(ccc_key, gethostid(), ttl)) {
			      retval = 0; /* success */
#ifdef SS_VW	
                  close(fd);		  
			      return retval;
#else
                  break;
#endif /* SS_VW */				  
		      }
#else
#endif /* WIN32 */
		      for (fake = FAKE_HOSTID_FIRST_; fake < FAKE_HOSTID_LIMIT_; ++fake) {
			      if (! _check_key(ccc_key, fake, ttl)) {
		 	   	      retval = 0; /* success */
		    	      break;
			      }
		      }
		      if (retval == 0) {
#ifdef SS_VW	
                  close(fd);		  
			      return retval;
#else
                  break;
#endif /* SS_VW */				  
		      }
	      }

	}
#ifdef SS_VW
     close(fd);
#else
     fclose(inFp);
#endif /* SS_VW */
	return (retval);
}

static INLINE int
_check_key(ccc_key_t key, u32_t hostid, u32_t ttl)
{
	ccc_opaque_t	prev;
	ccc_opaque_t	version = CCC_VERSION(2, 0); /* version 2.0 or higher */
	ccc_state_t		ks;
#ifdef SS_VW
	static u32_t rightnow;
#else
#ifdef SS_MT
	static time_t			rightnow;
#else
	SYSTEMTIME csystm;
	SYSTEMTIME esystm = {1970, 1, 4, 1, 0, 0, 0, 0};
	FILETIME efltm, cfltm;
	ULARGE_INTEGER ctime, etime, urtnow;
	static u32_t rightnow;
#endif /* WIN32 */
#endif /* SS_VW */
	int				is_super = 0;

	hostid &= 0x00FFFFFF;
#ifndef WIN32
	if (!rightnow)
	{
	   rightnow = time(0);
	}
	else
	{
	   rightnow += ttl;
	}
#else
	SystemTimeToFileTime(&esystm, &efltm);
	etime.LowPart = efltm.dwLowDateTime;
	etime.HighPart = efltm.dwHighDateTime;
	GetSystemTime(&csystm);
	SystemTimeToFileTime(&csystm, &cfltm);
	ctime.LowPart = cfltm.dwLowDateTime;
	ctime.HighPart = cfltm.dwHighDateTime;
	urtnow.QuadPart = (ctime.QuadPart - etime.QuadPart) / 10000000ULL;
	if (!rightnow)
	{
	   rightnow = urtnow.QuadPart;
	}
	else
	{
	   rightnow += ttl;
	}
#endif /* WIN32 */

	if (
		(prev = key_1_init(hostid, key, ks)) &&
		(prev = key_2_init(prev, key, ks)) &&
		(prev = key_3_init(prev, key, ks)) &&

		(prev = key_1_hostid(hostid, key, ks)) &&
		(prev = key_2_hostid(prev, key, ks)) &&
		(prev = key_3_hostid(prev, key, ks)) &&
		key_ok_hostid(hostid, prev, key, ks) &&

		(((prev = key_1_feature(no_multi_core, key, ks)) &&
		  (prev = key_2_feature(prev, key, ks)) &&
		  (prev = key_3_feature(prev, key, ks)) &&
		  key_ok_feature(no_multi_core, prev, key, ks)) ||
		 (is_super = ((prev = key_1_feature(Super, key, ks)) &&
					  (prev = key_2_feature(prev, key, ks)) &&
					  (prev = key_3_feature(prev, key, ks)) &&
					  key_ok_feature(Super, prev, key, ks)))) &&

		(is_super ||  /* super overrides version and date */

		 ((prev = key_1_version(version, key, ks)) &&
		  (prev = key_2_version(prev, key, ks)) &&
		  (prev = key_3_version(prev, key, ks)) &&
		  key_ok_version(version, prev, key, ks) &&

		  (prev = key_1_date(rightnow, key, ks)) &&
		  (prev = key_2_date(prev, key, ks)) &&
		  (prev = key_3_date(prev, key, ks)) &&
		  key_ok_date(rightnow, prev, key, ks)))
	) {
		return (0);
	} else {
		return (-1);
	}
}

#undef _LICENSE_FILE
