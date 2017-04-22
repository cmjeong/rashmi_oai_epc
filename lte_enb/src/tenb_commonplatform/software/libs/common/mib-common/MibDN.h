///////////////////////////////////////////////////////////////////////////////
//
// MibDN.h
//
// Represents a distinguished name i.e. a set of RDN's that uniquely
// reference an object and instance.
//
// DN = RDN.RDN.RDN = class.instance.class.instance.class.instance
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibDN_h_
#define __MibDN_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <deque>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibRDN.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
// NOTE: Do *not* add attributes to this class because the base class destructor isn't virtual
class MibDN : public  std::deque<MibRDN>, public threeway::Serialisable
{
   public:
      /**
       * DN helpers.
       * TODO: Could move this out to a "platform" library as it references explicit object classes
       * that may not be present in a given product.
       */
      static MibDN GenerateMibDN( const std::string & str);
      static MibDN GenerateMibDN(MibObjectClass mibObjectClass, u32 mibObjectInstance = 0);
      static MibDN  GenerateMibDN(MibDN &dn, MibObjectClass mibObjectClass, u32 mibObjectInstance = 0);
      static s32 GetMibObjectInstanceNum(MibDN dN,s32 idx=-1);
      static s32 GetMibObjectInstanceNum(std::string dNString,s32 idx=-1);
      friend std::ostream& operator<< (std::ostream& os, const MibDN& s);

      /**
       * Implement Serialisable.
       */
      virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_DN; }
      virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
      virtual bool DeSerialise(const u8* data, u32 dataLen);
      std::string ToString() const;

   private:
      // Hide push_front. Possibly never needed.
      void push_front(const MibRDN&) {};
};
#endif
