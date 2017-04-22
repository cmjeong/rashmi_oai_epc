///////////////////////////////////////////////////////////////////////////////
//
// NumberConversions.h
//
// Utility functions for converting between different number representations. 
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NumberConversions_h_
#define __NumberConversions_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/* Prototypes are added for float to byte array and byte array to float representation */
extern float  BigEndianByteArrayToFloat(const u8* byteArray);
extern void   FloatToBigEndianByteArray(float value, u8* byteArray); 

extern u32  BigEndianByteArrayToU32(const u8* byteArray);
extern u32  BytesToU32(u8 msByte, u8 byte2, u8 byte3, u8 lsByte);
extern void U32ToBigEndianByteArray(u32 value, u8* byteArray); // Make damn sure there's space for 4 bytes!!
extern void U32ToBytes(u32 value, u8* msByte, u8* byte2, u8* byte3, u8* lsByte);

extern u16  BigEndianByteArrayToU16(const u8* byteArray);
extern u16  BytesToU16(u8 msByte, u8 lsByte);
extern void U16ToBigEndianByteArray(u16 value, u8* byteArray); // Make damn sure there's space for 2 bytes!!
extern void U16ToBytes(u16 value, u8* msByte, u8* lsByte);

extern s16  BigEndianByteArrayToS16(const u8* byteArray);
extern s16  BytesToS16(u8 msByte, u8 lsByte);
extern void S16ToBigEndianByteArray(s16 value, u8* byteArray); // Make damn sure there's space for 2 bytes!!
extern void S16ToBytes(s16 value, u8* msByte, u8* lsByte);

/**
 * Convert from, e.g. u16=12345 to u8[]={1,2,3,4,5} and vv.
 */
extern void U16ToBCD(u16 value, u8 numDigits, u8 *pBCD, u32 maxLen);
extern void BcdToU16(const u8 *pBCD, u8 numDigits, u16 *pValue);
/**
*This structure defines char representation of float 
*/
typedef union floatRsprnt
              {
                 float f;
                 u8    u8Arr[4];
              }FloatRsprnt; 
               

#ifdef __cplusplus
}
#endif

#endif
