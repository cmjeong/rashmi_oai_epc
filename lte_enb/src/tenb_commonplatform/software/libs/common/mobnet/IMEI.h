///////////////////////////////////////////////////////////////////////////////
//
// IMEI.h
//
// Class representing a IMEI.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IMEI_h_
#define __IMEI_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IMEI
{
public:
    /**
     * 23.003.  IMEI is 14 digits plus a check digit but the check digit
     * is never transmitted, it is only there for validation when the IMEI
     * is manually transferred by real people.  However, in messages 15 digits
     * are transferred but the last one is always zero.
     */
    static const u8 IMEI_NUM_DIGITS = 14;

    /**
     * Packed data is 7.5 byte, last byte being a dummy check nibble.
     */
    static const u8 IMEI_PACKED_NUM_BITS = 60;
    static const u8 IMEI_PACKED_NUM_BYTES = 8;

    /**
     * Default constructor.
     */
    IMEI();

    /**
     * Construct with an array of 14 decimal digits.
     * e.g. { 1,2,3,4,5,6,7,8,9,0,1,2,3,4 }
     */
    IMEI(const u8 * imei);

    /**
     * Construct with a string of 14 decimal digit characters.
     * e.g. "12345678901234"
     */
    IMEI(const std::string& imei);

    /**
     * Destructor.
     */
    virtual ~IMEI();

    /**
     * Accessors
     */
    bool IsSet() const { return m_isSet; }
    u8 GetNumDigits() const { return m_isSet ? IMEI_NUM_DIGITS : 0; }
    void SetDigits(const u8* imeiDigits); // 14 expected
    const u8* GetDigits() const { return m_imei; }

    /**
     * Reset it to empty - no IMEI!
     */
    void Clear() { m_isSet = false; }

    /**
     * Compare byte-by-byte and whether set or not.
     */
    bool operator==(const IMEI& rhs) const;
    bool operator!=(const IMEI& rhs) const;

    /**
     * Set the IMEI from the packed form used in e.g. HNBAP ASN.
     * Expects 14 decimal digits, one per byte.
     */
    void SetImeiPacked(const u8 *imeiValue);

    /**
     * Get the IMEI in the packed form used in e.g. HNBAP ASN.
     * Length will be 8 (actually 7.5 bytes of valid value) as it
     * includes a zero-value dummy check digit.
     */
    void GetImeiPacked(u8 *imeiValue, u32 imeiValueSize) const;

    /**
     * Get as string - 14 decimal characters.
     * e.g. "12345678901234"
     */
    std::string ToString() const;

protected:

private:

    bool m_isSet;
    u8 m_imei[IMEI_NUM_DIGITS];
};

}

#endif
