///////////////////////////////////////////////////////////////////////////////
//
// TMSI.h
//
// Class representing a TMSI.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TMSI_h_
#define __TMSI_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <Radisys.h>
#include <system/HexString.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TMSI : public HexString
{
public:
    static const u8 TMSI_NUM_HEX_DIGITS = 8;

    /**
     * Default constructor.
     */
    TMSI();

    /**
     * Construct with an array of hex digits.
     */
    TMSI(const u8 * hexArray);

    /**
     * Destructor.
     */
    virtual ~TMSI();

    /**
     * Set the TMSI from the packed form used in e.g. HNBAP ASN.
     */
    void SetTmsiFromAsnStyle(const u8 *tmsiValue);

    /**
     * Set the TMSI from unsigned long digits (Encodix style).
     */
    void SetTmsiFromULongArray(const unsigned long *tmsiValue);

    /**
     * Get the TMSI in the packed form used in e.g. HNBAP ASN.
     *
     * \return Length of packed TMSI.
     */
    u8 GetTmsiAsAsnStyle(u8 *tmsiValue, u32 tmsiValueSize) const;

protected:

private:

};

}

#endif
