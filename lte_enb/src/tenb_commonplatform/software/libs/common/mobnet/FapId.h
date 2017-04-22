///////////////////////////////////////////////////////////////////////////////
//
// FapId.h
//
// Represents a FAP ID.  E.g. short FAP ID, 15 alpha-numeric chars.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FapId_h_
#define __FapId_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FapId : public threeway::Serialisable
{
public:
    // Fixed lengths of a short FAP ID.
    // For historical reasons some FAPs in Radisys engineering have 17 byte FAP IDs
    // derived from their serial numbers.  This is being phased out but is still
    // valid and we have to deal with it.
    static const u8 SHORT_FAP_ID_LEN = 15;
    static const u8 SHORT_FAP_ID_ENGINEERING_LEN = 17;

    /**
     * Validate an external string (e.g. from TPM) before constructing a FapId object.
     */
    static bool IsValid(const std::string& shortFapIdStr);

    /**
     * Default constructor.
     */
    FapId();

    /**
     * Construct with a short FAP ID string of the form 0005B9-NNNNNNNN.
     *
     * Will validate the string is correct length and assert if not so make
     * sure you've validated any FAP ID from an external input first!
     */
    FapId(const std::string& shortFapId);

    /**
     * Destructor.
     */
    virtual ~FapId();

    /**
     * Implement Serialisable.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_FAP_ID; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Check if has been set.
     */
    bool IsSet() const { return m_isSet; }

    /**
     * Check length.  Either 0, SHORT_FAP_ID_LEN or SHORT_FAP_ID_ENGINEERING_LEN
     */
    u32 GetShortFapIdLength() const { return (u32)m_shortFapId.size(); }

    /**
     * Get the full FAP ID.  Will assert if not set.
     *
     * Is of the form: 0005B9-NNNNNNNN.Radisys.com
     */
    std::string GetFullFapId() const;

    /**
     * Get the short FAP ID.  Will assert if not set.
     *
     * Is of the form: 0005B9-NNNNNNNN
     */
    std::string GetShortFapId() const;

    /**
     * Get the short FAP ID adjusted down to normal length by dropping
     * 2 chars if the length is engineering length.
     */
    std::string GetShortEquivFapId() const;

    /**
     * Check for equivalence.  This is a looser version of == that allows
     * us to compare a 15 and 17 digit FAP ID by ignore the first 2 digits
     * of the 17 digit FAP ID.  If both are 15 or both are 17 long then a
     * normal == compare is done.
     */
    bool IsEquivalentTo(const FapId& rhs);

    /**
     * Check for equality.  I.e. FAP ID and set/not-set both match.
     */
    bool operator==(const FapId& rhs) const;
    bool operator!=(const FapId& rhs) const;

private:

    // Has it been set?
    bool m_isSet;

    // Short FAP ID.
    std::string m_shortFapId;
};

}

#endif
