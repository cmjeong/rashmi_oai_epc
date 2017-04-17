///////////////////////////////////////////////////////////////////////////////
//
// oftwareRelease.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SoftwareRelease.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

typedef struct SrNumberNamePair_tag
{
    u32 softwareRelease;
    const char * unusualName;
} SrNumberNamePair;


static const SrNumberNamePair srMapOfUnusualNames[] =
{
        { 0xffffffff,          "3gFemtotality_?_0"},
};

string SoftwareReleaseToString(u32 softwareRelease, u8 significantDigits)
{
    ostringstream relAsString;

    /*for( unsigned i = 0;
         i < (sizeof(srMapOfUnusualNames)/sizeof(srMapOfUnusualNames[0]));
         i++)
    {
         if(softwareRelease == srMapOfUnusualNames[i].softwareRelease)
         {
             relAsString << srMapOfUnusualNames[i].unusualName;
             return relAsString.str();
         }
    }
    */

    /* else return :
     * "R0-0"      (if 0) or
     * "Rw-0"      (if x==0, y==0, z==0) or
     * "Rw-x"      (if y==0, z==0) or
     * "Rw-x-y"    (if y!=0, z==0) or
     * "Rw-x-y-z"  (if z!=0)
     */


    /*softwareRelease will be of form 01020300 where
    01 = Major Release
    02 = Sub Release
    03 = Patch Release
    00 = For Future use*/
    u8 w = (u8)((softwareRelease >> 24) & 0xff); //01
    u8 x = (u8)((softwareRelease >> 16) & 0xff); //02
    u8 y = (u8)((softwareRelease >>  8) & 0xff); //03
    u8 z = (u8)((softwareRelease >>  0) & 0xff); //00

    if(significantDigits == 0)
    {
        if(z!=0)
        {
            significantDigits = 4;
        }
        else if(y!=0)
        {
            significantDigits = 3;
        }
        else
        {
            significantDigits = 2;
        }
    }

    switch(significantDigits)
    {
        case 4:
        {
            relAsString << "SW" << (u32)w << "." << (u32)x << "." << (u32)y << "." << (u32)z; //SW1.2.3.0
        }
        break;

        default:
            // We'll default to 3.
        case 3:
        {
            relAsString << "SW" << (u32)w << "." << (u32)x << "." << (u32)y ; //SW1.2.3
        }
        break;

        case 2:
        {
            relAsString << "SW" << (u32)w << "." << (u32)x ; //SW1.2
        }
        break;

        case 1:
        {
            relAsString << "SW" << (u32)w ; //SW1
        }
        break;
    }

    return relAsString.str();
}
