/*---------------------------------------------------------
 *					Kasumi.x
 *---------------------------------------------------------*/
/*------- unions: used to remove "endian" issues ------------------------*/

typedef union {
	U32 b32;
	U16 b16[2];
	U8  b8[4];
} DWORD;

typedef union {
	U16 b16;
	U8  b8[2];
} WORD;

/*------- Function decalarations: ---------------------------------------*/

EXTERN VOID kwAcKeySchedule ARGS(( key ));
EXTERN VOID kwAcKasumi ARGS(( data ));
EXTERN U8 *kwAcF9 ARGS((key, count, fresh, dir, data, length ));
EXTERN U8 * kwAcF9( u8 *key,int count,int fresh, int dir,u8 *data,int length );



