///////////////////////////////////////////////////////////////////////////////
//
// $Id: CarbTemperatureCnf.h 28331 2010-07-17 15:25:20Z mmcternan $
//
// CarbTemperatureCnf message.
//
// Copyright (C) 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CarbTemperatureCnf_h_
#define __CarbTemperatureCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <string>
#include <system/Serialisable.h>
#endif
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

/** Response giving board temperature.
 * \ingroup Carb
 */
class CarbTemperatureCnf : public threeway::Serialisable
{
public:
    /*
     * Construction / destruction.
     */
    CarbTemperatureCnf(s32 boardDegC, s32 radioDegC);
    CarbTemperatureCnf();
    virtual ~CarbTemperatureCnf() {};

    /*
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CARB_TEMPERATURE_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /*
     * Accessors.
     */
    s32 GetBoardTemp() const { return m_boardDegC; }
    s32 GeRadioTemp() const { return m_radioDegC; }

    /**
     * Convert to strings for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:
    s32 m_boardDegC;
    s32 m_radioDegC;

};

}

#endif // __cplusplus

#endif // __CarbTemperatureCnf_h_
