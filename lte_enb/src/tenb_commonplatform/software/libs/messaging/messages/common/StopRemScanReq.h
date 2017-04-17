/*
 * StopRemScanReq.h
 *
 *  Created on: 23 Feb 2010
 *      Author: jouroussoff
 */

#ifndef STOPREMSCANREQ_H_
#define STOPREMSCANREQ_H_

class StopRemScanReq : public threeway::Serialisable
{
public:
    StopRemScanReq() {};
    virtual ~StopRemScanReq(){};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_STOP_REM_SCAN_REQ; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const {return 0;};
    virtual bool DeSerialise(const u8* data, u32 dataLen) {return true;};

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const {ostringstream stream; stream << "Stop Rem Scan Req " << endl; return (stream.str());};

private:
};

#endif /* STOPREMSCANREQ_H_ */
