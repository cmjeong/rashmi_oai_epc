///////////////////////////////////////////////////////////////////////////////
//
// CompressedModeDetails.h
//
// TODO: Describe purpose and usage of class(es).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CompressedModeDetails_h_
#define __CompressedModeDetails_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>

// TODO: Delete unused sections below.

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class CompressedModeDetails
{
public:
    CompressedModeDetails ()      { Reset(); }
    CompressedModeDetails (bool ulCompressedModeRequired, bool dlCompressedModeRequired)
                                  { m_ulCompressedModeRequired = ulCompressedModeRequired;
                                    m_dlCompressedModeRequired = dlCompressedModeRequired; }
    CompressedModeDetails (const CompressedModeDetails &rhs)
                                  { m_ulCompressedModeRequired = rhs.m_ulCompressedModeRequired;
                                    m_dlCompressedModeRequired = rhs.m_dlCompressedModeRequired; }

    CompressedModeDetails &operator+=(const CompressedModeDetails &rhs)
                                  { m_ulCompressedModeRequired |= rhs.m_ulCompressedModeRequired;
                                    m_dlCompressedModeRequired |= rhs.m_dlCompressedModeRequired;
                                    return(*this); }

    ~CompressedModeDetails () {};

    void Reset() { m_ulCompressedModeRequired = true;
                   m_dlCompressedModeRequired = true; }

    void SetUlCompressedModeRequired(bool ulRequired) { m_ulCompressedModeRequired = ulRequired; }
    void SetDlCompressedModeRequired(bool dlRequired) { m_dlCompressedModeRequired = dlRequired; }

    bool GetUlCompressedModeRequired() const { return m_ulCompressedModeRequired; }
    bool GetDlCompressedModeRequired() const { return m_dlCompressedModeRequired; }
    bool IsCompressedModeRequiredAtAll() { return m_ulCompressedModeRequired || m_dlCompressedModeRequired; }

    std::string ToString () const
    {
        std::ostringstream txtStream;
        txtStream << "UL/DL Measurements = " <<
                  ((m_ulCompressedModeRequired == true) ? "Yes" : "No") << " / " <<
                  ((m_dlCompressedModeRequired == true) ? "Yes" : "No");
        return txtStream.str ();
    }

private:
    bool m_ulCompressedModeRequired;
    bool m_dlCompressedModeRequired;
};

#endif
