*********************************************************************17*/


/********************************************************************20**

     Name:    PDCP- acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_load.c

     Sid:      pjac_f8f9.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:47 2015

     Prg:     Adarsh 

*********************************************************************21*/
/*-------------------------------------------------------------------
 *				F8 - Confidentiality Algorithm
 *-------------------------------------------------------------------
 *
 *	A sample implementation of f8, the 3GPP Confidentiality algorithm.
 *
 *	This has been coded for clarity, not necessarily for efficiency.
 *
 *	This will compile and run correctly on both Intel (little endian)
 *  and Sparc (big endian) machines. (Compilers used supported 32-bit ints)
 *
 *	Version 1.0		05 November  1999
 *
 *-------------------------------------------------------------------*/
/*  Include stdio.h for standard input/output. */
/*  Used for giving output to the screen. */
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

/*---------------------------------------------------------
 * f8()
 *		Given key, count, bearer, direction,  data,
 *		and bit length  encrypt the bit stream
 *---------------------------------------------------------*/
#ifdef ANSI
EXTERN void kwAcKasF8
(
U8 *key,
int count,
int bearer,
int dir,
U8 *data,
int length 
)
#else
EXTERN void kwAcKasF8(key, count, bearer, dir, data, length)
U8 *key;
int count;
int bearer;
int dir;
U8 *data;
int length ;
#endif
{
	REGISTER64 A;		/* the modifier			*/
	REGISTER64 temp;		/* The working register	*/
	int i, n;
	U8  ModKey[16];		/* Modified key		*/
	U16 blkcnt;			/* The block counter */

	/* Start by building our global modifier */

	temp.b32[0]  = temp.b32[1]  = 0;
	A.b32[0]     = A.b32[1]     = 0;

	/* initialise register in an endian correct manner*/

	A.b8[0]  = (U8) (count>>24);
	A.b8[1]  = (U8) (count>>16);
	A.b8[2]  = (U8) (count>>8);
	A.b8[3]  = (U8) (count);
	A.b8[4]  = (U8) (bearer<<3);
	A.b8[4] |= (U8) (dir<<2);

	/* Construct the modified key and then "kasumi" A */

	for( n=0; n<16; ++n )
		ModKey[n] = (U8)(key[n] ^ 0x55);
	kwAcKeySchedule( ModKey );

	kwAcKasumi( A.b8 );	/* First encryption to create modifier */

	/* Final initialisation steps */

	blkcnt = 0;
	kwAcKeySchedule( key );

	/* Now run the block cipher */

	while( length > 0 )
	{
		/* First we calculate the next 64-bits of keystream */

		/* XOR in A and BLKCNT to last value */

		temp.b32[0] ^= A.b32[0];
		temp.b32[1] ^= A.b32[1];
		temp.b8[7] ^= (U8)  blkcnt;
		temp.b8[6] ^= (U8) (blkcnt>>8);

		/* KASUMI it to produce the next block of keystream */

		kwAcKasumi( temp.b8 );

		/* Set <n> to the number of bytes of input data	*
		 * we have to modify.  (=8 if length <= 64)		*/

		if( length >= 64 )
			n = 8;
		else
			n = (length+7)/8;

		/* XOR the keystream with the input data stream */

		for( i=0; i<n; ++i )
			*data++ ^= temp.b8[i];
		length -= 64;	/* done another 64 bits	*/
		++blkcnt;		/* increment BLKCNT		*/
	}
}

/*-----------------------------------------------------------
 *			e n d    o f    f 8 . c
 *-----------------------------------------------------------*/

/*-------------------------------------------------------------------
 *				F9 - Integrity Algorithm
 *-------------------------------------------------------------------
 *
 *	A sample implementation of f9, the 3GPP Integrity algorithm.
 *
 *	This has been coded for clarity, not necessarily for efficiency.
 *
 *	This will compile and run correctly on both Intel (little endian)
 *  and Sparc (big endian) machines. (Compilers used supported 32-bit ints)
 *
 *	Version 1.1		05 September  2000
 *
 *-------------------------------------------------------------------*/
/*---------------------------------------------------------
 * f9()
 *		Given key, count, fresh, direction, data,
 *		and message length, calculate the hash value
 *---------------------------------------------------------*/
#ifdef ANSI
PUBLIC U8* kwAcKasF9
(
U8 *key,
int count,
int fresh,
int dir,
U8 *data,
int length 
)
#else
PUBLIC U8* kwAcKasF9(key, count, fresh, dir, data, length)
U8 *key;
int count;
int fresh;
int dir;
U8 *data;
int length ;
#endif
{
	REGISTER64 A;	/* Holds the CBC chained data			*/
	REGISTER64 B;	/* Holds the XOR of all KASUMI outputs	*/
	U8  FinalBit[8] = {0x80, 0x40, 0x20, 0x10, 8,4,2,1};
	U8  ModKey[16];
	static U8 mac_i[4];	/* static memory for the result */
	int i, n;

	/* Start by initialising the block cipher */

	kwAcKeySchedule( key );

	/* Next initialise the MAC chain.  Make sure we	*
	 * have the data in the right byte order.			*
	 * <A> holds our chaining value...				*
	 * <B> is the running XOR of all KASUMI o/ps		*/

	for( n=0; n<4; ++n )
	{
		A.b8[n]   = (U8)(count>>(24-(n*8)));
		A.b8[n+4] = (U8)(fresh>>(24-(n*8)));
	}
	kwAcKasumi( A.b8 );
	B.b32[0] = A.b32[0];
	B.b32[1] = A.b32[1];

	/* Now run the blocks until we reach the last block */

	while( length >= 64 )
	{
		for( n=0; n<8; ++n )
			A.b8[n] ^= *data++;
		kwAcKasumi( A.b8 );
		length -= 64;
		B.b32[0] ^= A.b32[0];	/* running XOR across */
		B.b32[1] ^= A.b32[1];	/* the block outputs	 */
	}

	/* Process whole bytes in the last block */

	n = 0;
	while( length >=8 )
	{
		A.b8[n++] ^= *data++;
		length -= 8;
	}


	/* Now add the direction bit to the input bit stream	*
	 * If length (which holds the # of data bits in the	*
	 * last byte) is non-zero we add it in, otherwise		*
	 * it has to start a new byte.						*/

	if( length )
	{
		i = *data;
		if( dir )
			i |= FinalBit[length];
	}
	else
		i = dir ? 0x80 : 0;

	A.b8[n++] ^= (U8)i;

	/* Now add in the final '1' bit.  The problem here	*
	 * is if the message length happens to be n*64-1.		*
	 * If so we need to process this block and then		*
	 * create a new input block of 0x8000000000000000.	*/

	if( (length==7) && (n==8 ) )	/* then we've filled the block */
	{
		kwAcKasumi( A.b8 );
		B.b32[0] ^= A.b32[0];	/* running XOR across	*/
		B.b32[1] ^= A.b32[1];	/* the block outputs	*/

		A.b8[0] ^= 0x80;			/* toggle first bit */
		i = 0x80;
		n = 1;
	}
	else
	{
		if( length == 7 )		/* we finished off the last byte */
			A.b8[n] ^= 0x80;		/* so start a new one.....		*/
		else
			A.b8[n-1] ^= FinalBit[length+1];
	}


	kwAcKasumi( A.b8 );
	B.b32[0] ^= A.b32[0];	/* running XOR across	*/
	B.b32[1] ^= A.b32[1];	/* the block outputs		*/

	/* Final step is to KASUMI what we have using the	*
	 * key XORd with 0xAAAA.....						*/

	for( n=0; n<16; ++n )
		ModKey[n] = (U8)*key++ ^ 0xAA;
	kwAcKeySchedule( ModKey );
	kwAcKasumi( B.b8 );

	/* We return the left-most 32-bits of the result */

	for( n=0; n<4; ++n )
		mac_i[n] = B.b8[n];

	return( mac_i );
}
/*-----------------------------------------------------------
 *			e n d    o f    f 9 . c
 *-----------------------------------------------------------*/

/********************************************************************30**

         End of file:     pjac_f8f9.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:47 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      av          LTE PDCP Initial release 2.1
*********************************************************************91*/
