///////////////////////////////////////////////////////////////////////////////
//
// PlmnId.h
//
// Represents a PLMN ID i.e. MCC/MNC pair.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __PlmnId_h_
#define __PlmnId_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <system/Trace.h>
#include <system/Regex.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#define ERE_PLMNID   "[0-9]{5,6}"

namespace rsysmob
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class PlmnId
{
public:
    PlmnId();
    PlmnId(u16 mcc, u16 mnc, bool twoDigitMnc = false);
    ~PlmnId();

    static bool Validate(const string & plmnId );

    void Set(  const string & plmnId  ); // e.g.  "00101", or "001001"
    string Get() const;

    u16 GetMcc() const;
    u16 GetMnc( bool * isTwoDigit = NULL ) const;

    /**
     * De/encode from/to 3 bytes of BCD.
     *
     * See 24.008 10.5.1.3 for 2/3 digit MNC explanation - Perkie "King of the 3GPP specs" Specmeister pointed this out to me:
     *
     *   "MNC, Mobile network code (octet 3 bits 5 to 8, octet 4)
     *    The coding of this field is the responsibility of each administration but BCD coding shall be used.
     *    The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA, Federal regulation mandates that a 3-digit
     *    MNC shall be used. However a network operator may decide to use only two digits in the MNC in the LAI
     *    over the radio interface. In this case, bits 5 to 8 of octet 3 shall be coded as "1111". Mobile
     *    equipment shall accept LAI coded in such a way."
     *
     *  8   7   6   5   4   3   2   1
     *  MCC digit 2     MCC digit 1    octet x
     *  MNC digit 3     MCC digit 3    octet x+1
     *  MNC digit 2     MNC digit 1    octet x+2
     */
    void SetFromBcdEncoded(const u8* encodedBcd);
    void GetAsBcdEncoded(u8* encodedBcd) const;

    /**
     * So... gotta love those 3GPP specs.  In 25.469 PLMN ID is encoded slightly differently.
     * Section 9.2.14:
     *
     * "
     * Digits 0 to 9, encoded 0000 to 1001, 1111 used as filler digit, two digits per octet,
     * bits 4 to 1 of octet n encoding digit 2n-1, bits 8 to 5 of octet n encoding digit 2n
     * The PLMN identity consists of 3 digits from MCC followed by either
     * a filler digit plus 2 digits from MNC (in case of 2 digit MNC) or
     * 3 digits from MNC (in case of a 3 digit MNC).
     * "
     *
     * I.e.
     *
     *  8   7   6   5   4   3   2   1
     *  MCC digit 2     MCC digit 1    octet x
     *  MNC digit 1     MCC digit 3    octet x+1    MNC digit 1 is filler 1111 for 2 digit MNC
     *  MNC digit 3     MNC digit 2    octet x+2
     */
    void GetAs25469BcdEncoded(u8* encodedBcd) const;
    void SetFrom25469BcdEncoded(const u8* encodedBcd);

    bool operator==(const PlmnId& rhs) const;

    std::string ToString() const;

private:
    static threeway::Regex s_plmnIdRegex;

    bool m_isSet;
    bool m_isTwoDigitMnc;
    u16 m_mcc;
    u16 m_mnc;
};

}

#endif
