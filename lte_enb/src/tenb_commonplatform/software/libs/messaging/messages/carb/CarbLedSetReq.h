///////////////////////////////////////////////////////////////////////////////
//
// $Id: CarbLedSetReq.h 17897 2009-09-23 12:31:02Z mmarchetti $
//
// CarbLedSetReq message.
//
// Copyright (C) 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CarbLedSetReq_h_
#define __CarbLedSetReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <string>
#include <system/Serialisable.h>
#endif
#include <string.h> // needed for memset
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

#define NUM_LEDS 3

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/** Different states for a LED.
 */
typedef enum
{
    LED_OFF       = 0x00,   /**< Off. */
    LED_ON        = 0xff,   /**< Constantly on. */
    LED_FLASH_7_8 = 0x7f,   /**< Flashing at 1Hz, on for 7/8th of the time,
                                  off for 1/8ths. */
    LED_FLASH_3_4 = 0x3f,   /**< Flashing at 1Hz, on for 3/4th of the time,
                                  off for 1/4ths. */
    LED_FLASH_5_8 = 0x1f,   /**< Flashing at 1Hz, on for 5/8th of the time,
                                  off for 3/8ths. */
    LED_FLASH_1_2 = 0x0f,   /**< Flashing at 1Hz with 50% duty cycle. */

    LED_FLASH_3_8 = 0x07,   /**< Flashing at 1Hz, on for 3/8th of the time,
                                  off for 5/8ths. */
    LED_FLASH_1_4 = 0x03,   /**< Flashing at 1Hz, on for 1/4th of the time,
                                  off for 3/4th. */
    LED_FLASH_1_8 = 0x01    /**< Flashing at 1Hz, on for 1/8th of the time,
                                  off for 7/8ths. */
}
led_intensity_t;

typedef struct
{
    led_intensity_t intensity[NUM_LEDS];
    bool            pulsate[NUM_LEDS];
}
led_state_t;


///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

/** Message to set the board LEDs.
 * \ingroup Carb
 */
class CarbLedSetReq : public threeway::Serialisable
{
public:
    /*
     * Construction / destruction.
     */

    CarbLedSetReq() { memset(&m_ledState, 0, sizeof(m_ledState)); };

    /** Construct message with given LED statuses.
     */
    CarbLedSetReq(led_intensity_t led[NUM_LEDS], bool pulsate[NUM_LEDS]);
    CarbLedSetReq(led_intensity_t led0, led_intensity_t led1, led_intensity_t led2);
    virtual ~CarbLedSetReq() {};

    /*
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CARB_LED_SET_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /*
     * Accessors.
     */

    /** Get the LED setting for some LED.
     * \param[in] n  Index of the LED, 0-2.
     * \returns Led status value from the led_intensity_t enumeration.
     */
    led_intensity_t GetLedIntensity(u8 n) const  { return m_ledState.intensity[n]; }

    /** Get the LED pulsate status for some LED.
     * \param[in] n  Index of the LED, 0-2.
     * \retval TRUE  If the LED should pulsate.
     * \retval FALSE  If the LED should not pulsate.
     */
    bool        GetLedPulsate(u8 n) const { return m_ledState.pulsate[n]; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    led_state_t m_ledState;

};

}

#endif // __cplusplus

#endif // __CarbLedSetReq_h_
