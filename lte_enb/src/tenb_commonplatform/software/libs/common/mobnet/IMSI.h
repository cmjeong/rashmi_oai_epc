///////////////////////////////////////////////////////////////////////////////
//
// IMSI.h
//
// IMSI type.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IMSI_h_
#define __IMSI_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/HexString.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

/*
As per the RRC spec 25.331 IMSI length is defined to be between 6 - 21 digits. However, the IU spec specifies the IMSI to be less than or equal to 15 digits. Due
to the disagreement between the two specs, the IMSI length has been chosen to be between 6 - 15 digits. When the IU spec changes, additional changes will have to be done
in the ASN1 code as well to accomodate IMSIs with length greater than 15 digits.
*/

#define IMSI_MIN_LENGTH   6    // As per 25.331
#define IMSI_MAX_LENGTH   15   // 21 As per 25.331

#define IMSI_MIN_OCTETS   ((IMSI_MIN_LENGTH % 2) ? ( (IMSI_MIN_LENGTH + 1)/2 ) : ( (IMSI_MIN_LENGTH)/2 )  )   // As per 25.331
#define IMSI_MAX_OCTETS   ((IMSI_MAX_LENGTH % 2) ? ( (IMSI_MAX_LENGTH + 1)/2 ) : ( (IMSI_MAX_LENGTH)/2 )  )   // As per 25.331

#define IMSI_LENGTH_VALID(imsiLen)   ( ( (imsiLen < IMSI_MIN_LENGTH) || (imsiLen > IMSI_MAX_LENGTH) ) ? 0 : 1) 
#define IMSI_OCTET_LENGTH_VALID(octetLen)   ( ( (octetLen < IMSI_MIN_OCTETS) || (octetLen > IMSI_MAX_OCTETS) ) ? 0 : 1) 


namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IMSI : public HexString
{
public:
    /**
     * Various constructors to build an IMSI from a string of hex digits
     * e.g. 123456789ABCDEF (null terminated) or a byte array [1,2, ... ,15].
     * IMSI is always 15 hex digits.
     * TODO - the above comment is technically wrong, standards say 6..21 digits
     * for an IMSI, this may trip us up later!
     */
    IMSI();
    IMSI(const IMSI& imsiRef);
    IMSI(const char * imsiHexString);
    IMSI(const u8* imsiHexArray, const u8 imsiLength);
    IMSI(const unsigned long * imsiULongHexArray, const int imsiLength);
    virtual ~IMSI();

    // Set IMSI either by string "01...EF" or hex byte array [0,1, ... ,14,15]
    void SetIMSI(const char * imsiHexString);
    void SetIMSI(const u8* imsiHexArray, const u8 imsiLength);
    void SetIMSI(const unsigned long * imsiULongHexArray, const int imsiLength);	  // Provided for easy setting from encodix format.

    /**
     * Set the IMSI from the packed form used in e.g. HNBAP ASN.
     */
    void SetIMSIFromAsnStyle (const u8 *imsiValue, const u8 numOctets);    // Provided for easy setting from RANAP/HNBAP format.

    /**
     * Get the IMSI in the packed form used in e.g. HNBAP ASN.
     *
     * \return Length of packed IMSI.
     */
    u8  GetIMSIAsAsnStyle (u8 *imsiValue, u32 imsiValueSize) const;
};

}

#endif
