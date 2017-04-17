///////////////////////////////////////////////////////////////////////////////
//
// NumberConversions.c
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NumberConversions.h"
#include "Trace.h"

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////
/*Added for Byte array to float representation*/
float BigEndianByteArrayToFloat(const u8* byteArray)
{
   FloatRsprnt  fVal;
   
   fVal.u8Arr[3] = byteArray[3];
   fVal.u8Arr[2] = byteArray[2];
   fVal.u8Arr[1] = byteArray[1];
   fVal.u8Arr[0] = byteArray[0];

 return (fVal.f); 
}

/******************* u32 functions *************************/
u32 BigEndianByteArrayToU32(const u8* byteArray)
{
    return BytesToU32(byteArray[0], byteArray[1], byteArray[2], byteArray[3]);
}

u32 BytesToU32(u8 msByte, u8 byte2, u8 byte3, u8 lsByte)
{
    return (((u32)msByte) << 24) | (((u32)byte2) << 16) | (((u32)byte3) << 8) | (u32)lsByte;
}

void U32ToBigEndianByteArray(u32 value, u8* byteArray)
{
    U32ToBytes(value, &(byteArray[0]), &(byteArray[1]), &(byteArray[2]), &(byteArray[3]));
}


void U32ToBytes(u32 value, u8* msByte, u8* byte2, u8* byte3, u8* lsByte)
{
    *msByte = (u8)((value >> 24) & 0xff);
    *byte2  = (u8)((value >> 16) & 0xff);
    *byte3  = (u8)((value >> 8) & 0xff);
    *lsByte = (u8)(value & 0xff);
}

/*Added for Float to Byte array representation*/
void FloatToBigEndianByteArray(float value, u8* byteArray)
{
    FloatRsprnt  fVal;
    
    fVal.f = value;

    byteArray[3] =  fVal.u8Arr[3];
    byteArray[2]  = fVal.u8Arr[2];
    byteArray[1]  = fVal.u8Arr[1];
    byteArray[0] =  fVal.u8Arr[0];

}

/******************* u16 functions *************************/
u16 BigEndianByteArrayToU16(const u8* byteArray)
{
    return BytesToU16(byteArray[0], byteArray[1]);
}

u16 BytesToU16(u8 msByte, u8 lsByte)
{
    return (((u16)msByte) << 8) | (u16)lsByte;
}

void U16ToBigEndianByteArray(u16 value, u8* byteArray)
{
    U16ToBytes(value, &(byteArray[0]), &(byteArray[1]));
}

void U16ToBytes(u16 value, u8* msByte, u8* lsByte)
{
    *msByte = (u8)((value >> 8) & 0xff);
    *lsByte = (u8)(value & 0xff);
}

/******************* s16 functions *************************/
s16 BigEndianByteArrayToS16(const u8* byteArray)
{
    return BytesToS16(byteArray[0], byteArray[1]);
}

s16 BytesToS16(u8 msByte, u8 lsByte)
{
    return (((s16)msByte) << 8) | (s16)lsByte;
}

void S16ToBigEndianByteArray(s16 value, u8* byteArray)
{
    S16ToBytes(value, &(byteArray[0]), &(byteArray[1]));
}

void S16ToBytes(s16 value, u8* msByte, u8* lsByte)
{
    *msByte = (u8)((value >> 8) & 0xff);
    *lsByte = (u8)(value & 0xff);
}

void U16ToBCD(u16 value, u8 numDigits, u8 *pBCD, u32 maxLen)
{
    ENTER();

    u8 digitNum, i;
    u16 divisor;

    RSYS_ASSERT_PRINTF(maxLen >= numDigits, "U16ToBCD: Not enough space for result (numDigits=%u, maxLen=%" PRIu32 ").", numDigits, maxLen);

    if(numDigits == 0)
    {
        RETURN_VOID(); // Succeeded in doing nothing!
    }

    if(numDigits > 5)
    {
        numDigits = 5;
    }

    divisor = 1;
    for(i = 0; i < (numDigits - 1); i++)
    {
        divisor = divisor * 10;
    }

    for(digitNum = 0; digitNum < numDigits; digitNum++)
    {
        pBCD[digitNum] = value / divisor;
        value = value - pBCD[digitNum] * divisor;
        divisor = divisor / 10;
    }

    EXIT();
}


void BcdToU16(const u8 *pBCD, u8 numDigits, u16 *pValue)
{
    ENTER();

    s32 digitNum;
    u16 multiplier;

    *pValue = 0;

    if(numDigits < 1)
    {
        RETURN_VOID();
    }

    if(numDigits > 5)
    {
        numDigits = 5;
    }

    multiplier = 1;
    for(digitNum = (numDigits - 1); digitNum >= 0; digitNum--)
    {
        *pValue += pBCD[digitNum] * multiplier;
        multiplier = multiplier * 10;
    }

    EXIT();
}

#ifdef __cplusplus
}
#endif

/* END OF FILE */
