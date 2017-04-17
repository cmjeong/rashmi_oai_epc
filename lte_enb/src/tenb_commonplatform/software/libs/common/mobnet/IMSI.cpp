///////////////////////////////////////////////////////////////////////////////
//
// IMSI.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/HexString.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IMSI.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

IMSI::IMSI() :
    HexString(IMSI_MIN_LENGTH, IMSI_MAX_LENGTH)
{
}

IMSI::IMSI(const IMSI& imsiRef)
{
    Clone(imsiRef);
}

IMSI::IMSI(const char * imsiHexString) :
    HexString(IMSI_MIN_LENGTH, IMSI_MAX_LENGTH, imsiHexString)
{
}

IMSI::IMSI(const u8* imsiHexArray , const u8 imsiLength ) :
    HexString(IMSI_MIN_LENGTH, IMSI_MAX_LENGTH, imsiHexArray, (u32)(imsiLength) )
{
}

IMSI::IMSI(const unsigned long * imsiULongHexArray, const int imsiLength) :
    HexString(IMSI_MIN_LENGTH, IMSI_MAX_LENGTH)
{
    SetIMSI(imsiULongHexArray, imsiLength);
}

IMSI::~IMSI()
{
}

void IMSI::SetIMSI(const char * imsiHexString)
{
    RSYS_ASSERT(imsiHexString != NULL);

    SetHexString(imsiHexString);
}


void IMSI::SetIMSI(const u8* imsiHexArray, const u8 imsiLength)
{
    RSYS_ASSERT(imsiHexArray != NULL);

    SetHexArray(imsiHexArray, (u32)(imsiLength));
}

void IMSI::SetIMSI(const unsigned long * imsiULongHexArray, const int imsiLength)
{
    RSYS_ASSERT(imsiULongHexArray != NULL);

    u8 imsi[IMSI_MAX_LENGTH];

    for(int i = 0; i < imsiLength; i++)
    {
        imsi[i] = (u8)imsiULongHexArray[i];
    }

    SetHexArray(imsi, (u32)imsiLength);
}

void IMSI::SetIMSIFromAsnStyle (const u8 *imsiValue, const u8 numOctets)
{
   RSYS_ASSERT(imsiValue != NULL);
   RSYS_ASSERT(IMSI_OCTET_LENGTH_VALID(numOctets));

   TRACE("Setting IMSI from ASN style with length", numOctets);

   // This is actually BCD encoded digits...
   u8 expandedImsi[IMSI_MAX_LENGTH];  
   u8 digitCount = 0;

   for (u8 i=0;i<numOctets;i++)
   {
      if(digitCount < IMSI_MAX_LENGTH - 1)
      {
         expandedImsi[digitCount++] = imsiValue[i] & 0x0f;

         if( (i+1) >= numOctets )
         {
            /*If there are odd number of digits then the last nibble will be padded with 0xf*/
            if( (imsiValue[i] & 0xf0) == (0xf0) )
               break;
         }

         expandedImsi[digitCount++] = (imsiValue[i] & 0xf0) >> 4;
      }
   }

   SetHexArray (expandedImsi, (u32)(digitCount));
}

u8 IMSI::GetIMSIAsAsnStyle (u8 *imsiValue, u32 imsiValueSize) const
{
   RSYS_ASSERT(imsiValue != NULL);
   RSYS_ASSERT(IMSI_OCTET_LENGTH_VALID(imsiValueSize));

   u8 expandedImsi[IMSI_MAX_LENGTH]; 
   u32 digitCount = 0;
   u8 imsiLength = 0;

   if (GetByteArray(expandedImsi, IMSI_MAX_LENGTH))
   {
      u32 len = GetSize();
      imsiLength = ( ( len % 2 ) ? ( (len+1)/2 ) : ( len/2 )  );    //even or odd number of bytes
      for (u8 i=0; i<imsiLength; i++, digitCount+=2)
      {
         if(digitCount < IMSI_MAX_LENGTH)
         {
            imsiValue[i] =  (u8)((expandedImsi[digitCount] & 0x0f));
         }
         if ((digitCount+1) >= len)
         {
            imsiValue[i] |= 0xf0;  // last digit needs padding
         }
         else
         {
            if((digitCount+1) < IMSI_MAX_LENGTH)
            {
               imsiValue[i] |= ((expandedImsi[digitCount+1] & 0x0f) << 4);
            }
         }
      }
   }

   return imsiLength;
}

}
