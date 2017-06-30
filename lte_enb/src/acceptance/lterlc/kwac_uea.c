/*---------------------------------------------------------
 *					f8.c
 *---------------------------------------------------------*/

#include <math.h>
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "pju.h"           /* PJU defines */
#include "rgu.h"           /* RGU defines */
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_lib.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_pju.h"      /* CKW Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_lib.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_pju.x"      /* CKW Acceptance defines */


/* Note : U64 is changed to U32[]. The higher bytes are in U32[0] and the lower 
 * bytes are in U32[1] */

PRIVATE S16 MUL64x ARGS((
U32* V,
U32* c,
U32* out
));
PRIVATE S16 MUL64xPOW ARGS((
U32* V,
U8 i,
U32* c,
U32* out
));
PRIVATE U32 mask32bit ARGS((
U32 n
));
/* f8.
 * Input key: 128 bit Confidentiality Key.
 * Input count:32-bit Count, Frame dependent input.
 * Input bearer: 5-bit Bearer identity (in the LSB side).
 * Input dir:1 bit, direction of transmission.
 * Input data: length number of bits, input bit stream.
 * Input length: 16 bit Length, i.e., the number of bits to be encrypted or 
 *               decrypted.
 * Output data: Output bit stream. Assumes data is suitably memory 
 * allocated.
 * Encrypts/decrypts blocks of data between 1 and 20000 bits in length as 
 * defined in Section 3.
 */

#ifdef ANSI
PUBLIC void kwAcSnowF8
(
U8 *key,
U32 count,
U32 bearer,
U32 dir,
U8 *data,
U32 length 
)
#else
PUBLIC void kwAcSnowF8(key, count, bearer, dir, data, length)
U8 *key;
U32 count;
U32 bearer;
U32 dir;
U8 *data;
U32 length ;
#endif
{
  U32 K[4],IV[4];
  U32 n = ( length + 31 ) / 32;
  U32 i=0;
  U32 *KS;

  /*Initialisation*/

  /* Load the confidentiality key for SNOW 3G initialization as in section 3.4. */
  memcpy(K+3,key+0,4);  /*K[3] = key[0]; we assume K[3]=key[0]||key[1]||...||key[31] , with key[0] the
                         * most important bit of key*/
  memcpy(K+2,key+4,4);  /*K[2] = key[1];*/
  memcpy(K+1,key+8,4);  /*K[1] = key[2];*/
  memcpy(K+0,key+12,4); /*K[0] = key[3]; we assume K[0]=key[96]||key[97]||...||key[127] , with key[127] the
                 * least important bit of key*/

  /* Prepare the initialization vector (IV) for SNOW 3G initialization as in section 3.4. */
  IV[3] = count;
  IV[2] = (bearer << 27) | ((dir & 0x1) << 26);

  IV[1] = IV[3];
  IV[0] = IV[2];

  /* Run SNOW 3G algorithm to generate sequence of key stream bits KS*/
  kwAcSnowInit(K,IV);

  PJ_ALLOC(KS, (4*n));
  kwAcSnowGenKeystrm(n,(U32*)KS); 

  /* Exclusive-OR the input data with keystream to generate the output bit stream */
  for (i=0;i<n*4;i++)
    data[i] ^= *(((U8*)KS)+i); 

  PJ_FREE(KS, (4*n));
}

/* End of f8.c */




/*---------------------------------------------------------
 *					f9.c
 *---------------------------------------------------------*/
/* MUL64x.
 * Input V: a 64-bit input.
 * Input c: a 64-bit input.
 * Output : a 64-bit output.
 * A 64-bit memory is allocated which is to be freed by the calling 
 * function.
 * See section 4.3.2 for details.
 */

#ifdef ANSI
PRIVATE S16 MUL64x
(
U32* V,
U32* c,
U32* out
)
#else
PRIVATE S16 MUL64x(V, c, out)
U32* V;
U32* c;
U32* out;
#endif
{
   U32 tmp;
   if ( V[0] & 0x80000000 )
   {
      out[0]  =  V[0] << 1;
      tmp   =  ((V[1] & (1 << 31)) >> 31);
      out[0]  |= tmp;
      out[1]  =  V[1] << 1;
      
      out[0] ^= c[0];
      out[1] ^= c[1];
   }
   else
   {
      out[0]  =  V[0] << 1;
      tmp   =  ((V[1] & (1 << 31)) >> 31);
      out[0]  |= tmp;
      out[1]  =  V[1] << 1;
   }
   RETVALUE(ROK);
}

/* MUL64xPOW.
 * Input V: a 64-bit input.
 * Input i: a positive integer.
 * Input c: a 64-bit input.
 * Output : a 64-bit output.
 * A 64-bit memory is allocated which is to be freed by the calling function.
 * See section 4.3.3 for details.
 */

#ifdef ANSI
PRIVATE S16 MUL64xPOW
(
U32* V,
U8 i,
U32* c,
U32* out
)
#else
PRIVATE S16 MUL64xPOW(V, i, c, out)
U32* V;
 U8 i;
U32* c;
U32* out;
#endif
{
   U32 mulOut[2];
   mulOut[0]= mulOut[1] = 0;
   if ( i == 0)
   {
      out[0]   =  V[0];
      out[1]   =  V[1];
	   RETVALUE(ROK);
   }
   else
   {
	   MUL64xPOW(V,i-1,c, &mulOut[0]);
	   MUL64x( mulOut,c, out);
      RETVALUE(ROK);
   }
}

/* MUL64.
 * Input V: a 64-bit input.
 * Input P: a 64-bit input.
 * Input c: a 64-bit input.
 * Output : a 64-bit output.
 * A 64-bit memory is allocated which is to be freed by the calling 
 * function.
 * See section 4.3.4 for details.
 */


#ifdef ANSI
PRIVATE S16 MUL64
(
U32 *V,
U32 *P,
U32 *c,
U32 *out
)
#else
PRIVATE S16 MUL64(V, P, c, out)
U32 *V;
U32 *P;
U32 *c;
U32 *out;
#endif
{
   U32 i = 0;
   U32 mulOut[2];
   U32 tmp[2];

   mulOut[0] =  out [0]  =  tmp[0]   =  0;
   mulOut[1] =  out [1]  =  tmp[1]   =  0;

   for ( i=0; i<64; i++)
   {
      if(i < 32)
      {
         tmp[1]   =  P[1] >> i;
         tmp[1]   |=  (P[0] % (1 << i)) << (32 - i);
         tmp[0]   =  P[0] >> i;
      }
      else
      {
         tmp[1]   =  P[0] >> (i -32);
         tmp[0]   =  0;
      }

      if(tmp[1] & 0x1)
      {
         MUL64xPOW(V,i,c, &mulOut[0]);
         out[0] ^=mulOut[0];
         out[1] ^=mulOut[1];
      }
   }

   RETVALUE(ROK);

}
/* mask32bit.
 * Input n: an integer in 1-32.
 * Output : a 32 bit mask.
 * Prepares a 32 bit mask with required number of 1 bits on the MSB side.
 */
#ifdef ANSI
PRIVATE U32 mask32bit
(
U32 n
)
#else
PRIVATE U32 mask32bit(n)
U32 n;
#endif
{
  U32 mask=0x0;
  if ( n%32 == 0 )
   RETVALUE(0xffffffff);

  while (n--)
    mask =  (mask>>1) ^ 0x80000000;
  RETVALUE( mask);
}

/* f9.
 * Input key: 128 bit Integrity Key.
 * Input count:32-bit Count, Frame dependent input.
 * Input fresh: 32-bit Random number.
 * Input dir:1 bit, direction of transmission (in the LSB).
 * Input data: length number of bits, input bit stream.
 * Input length: 64 bit Length, i.e., the number of bits to be MAC'd.
 * Output  : 32 bit block used as MAC 
 * Generates 32-bit MAC using UIA2 algorithm as defined in Section 4.
 */
#ifdef ANSI
PUBLIC U8* kwAcSnowF9
(
U8* key,
U32 count,
U32 fresh,
U32 dir,
U8 *data,
U32 length
)
#else
PUBLIC U8* kwAcSnowF9(key, count, fresh, dir, data, length)
U8* key;
U32 count;
U32 fresh;
U32 dir;
U8 *data;
U32 length;
#endif
{
  U32 K[4],IV[4], z[5];
  U32 i=0,D;
  PRIVATE U32 MAC_I = 0; /* static memory for the result */
  U32 EVAL[2];
  U32 V[2];
  U32 P[2];
  U32 Q[2];
  U32 c[2];
  U32 tmp[2];

  U32 M_D_2[2];
  U32 rem_bits = 0;
  U32 mask = 0;
  U32 *message;

  EVAL[0]= 0;
  V[0]   = 0;
  P[0]   = 0;
  Q[0]   = 0;
  c[0]   = 0;
  tmp[0] = 0;
  M_D_2[0] = 0;
  EVAL[1]= 0;
  V[1]   = 0;
  P[1]   = 0;
  Q[1]   = 0;
  c[1]   = 0;
  tmp[1] = 0;
  M_D_2[1] = 0;

  message = (U32*)data; /* To operate 32 bit message internally. */

  /* Load the Integrity Key for SNOW3G initialization as in section 4.4. */
  memcpy(K+3,key+0,4);  /*K[3] = key[0]; we assume K[3]=key[0]||key[1]||...||key[31] , with key[0] the
                         * most important bit of key*/
  memcpy(K+2,key+4,4);  /*K[2] = key[1];*/
  memcpy(K+1,key+8,4);  /*K[1] = key[2];*/
  memcpy(K+0,key+12,4); /*K[0] = key[3]; we assume K[0]=key[96]||key[97]||...||key[127] , with key[127] the
                         * least important bit of key*/

  /* Prepare the Initialization Vector (IV) for SNOW3G initialization as in section 4.4. */
  IV[3] = count;
  IV[2] = fresh;
  IV[1] = count ^ ( dir << 31 ) ;
  IV[0] = fresh ^ (dir << 15);

  z[0] = z[1] = z[2] = z[3] = z[4] = 0;

  /* Run SNOW 3G to produce 5 keystream words z_1, z_2, z_3, z_4 and z_5. */
  kwAcSnowInit(K,IV);
  kwAcSnowGenKeystrm(5,z);
  

  /* 
  P = (U8*)z[0] << 32 | (U8*)z[1];
  Q = (U8*)z[2] << 32 | (U8*)z[3];
  */

  P[0] = z[0];
  P[1] = z[1];
  Q[0] = z[2];
  Q[1] = z[3];

  /* Calculation */

  D = ceil( length / 64.0 ) + 1;
  /* EVAL = 0; */
  EVAL[0]   =  0;
  EVAL[1]   =  0;

  /* c = 0x1b; */
  c[0] = 0;
  c[1] = 0x1b;

  
  /* for 0 <= i <= D-3 */
  for (i=0;i<D-2;i++)
  {
     /* V = EVAL ^ ( (U8*)message[2*i] << 32 | (U8*)message[2*i+1] ); */
     V[0] = EVAL[0] ^ message[2*i];
     V[1] = EVAL[1] ^ message[2*i+1];

     /* EVAL = MUL64(V,P,c); */
     MUL64(&V[0],&P[0],&c[0], &EVAL[0]);
  }

  /* for D-2 */
  rem_bits = length % 64;
  if (rem_bits == 0)
     rem_bits = 64;
  
  mask = mask32bit(rem_bits%32);
 
  if (rem_bits > 32)
  {
    M_D_2[0] =  message[2*(D-2)];
    M_D_2[1] =  (message[2*(D-2)+1] & mask);
  } else
  {
    M_D_2[0] = ( message[2*(D-2)] & mask); 
    M_D_2[1] = 0;
  }

  V[0] = EVAL[0] ^ M_D_2[0];
  V[1] = EVAL[1] ^ M_D_2[1];


  MUL64(&V[0],&P[0],&c[0], &EVAL[0]);

  /* for D-1 */
  EVAL[1] ^= length;  

  /* Multiply by Q */
  MUL64(&EVAL[0],&Q[0],&c[0], &tmp[0]);
  EVAL[0]   =  tmp[0];
  EVAL[1]   =  tmp[1];
      

  MAC_I = (U32)(EVAL[0] ) ^ z[4];
  
  return (U8*) &MAC_I;
}

/* End of f9.c */

/*------------------------------------------------------------------------*/


