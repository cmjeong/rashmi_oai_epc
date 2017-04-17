/*---------------------------------------------------------
 *					Kasumi.h
 *---------------------------------------------------------*/

#if 0
typedef unsigned  char   u8;
typedef unsigned short  u16;
typedef unsigned  long  u32;
#endif /* #if 0 */
/*--------- 16 bit rotate left ------------------------------------------*/

#define ROL16(a,b) (U16)((a<<b)|(a>>(16-b)))

