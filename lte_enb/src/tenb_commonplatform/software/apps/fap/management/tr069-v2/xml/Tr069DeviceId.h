///////////////////////////////////////////////////////////////////////////////
//
// Tr069DeviceId.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069DeviceId_h_
#define __Tr069DeviceId_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069XmlStringUtils.h"

using namespace std;
using namespace boost;
using namespace tr069;

namespace tr069
{

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

class DeviceId
{
   public:
      DeviceId()
      {}

      virtual ~DeviceId()
      {}

      bool QueryValid();

      static string ToXml()
      {
         stringstream ss;

         string serialNumber;
         string manufacturer;
         string oui;
         string productClass;
         Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_LONG_SERIAL_NUMBER,serialNumber);
         Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_MANUFACTURER,manufacturer);
         Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_OUI_OF_MANUFACTURER,oui);
         Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_PRODUCT_CLASS, productClass);

         ss <<
            "<DeviceId>"
            "<Manufacturer>" << manufacturer << "</Manufacturer>"
            "<OUI>" << oui << "</OUI>"
            "<ProductClass>" << productClass << "</ProductClass>"
            "<SerialNumber>" << XmlStringUtils::Filter(serialNumber) << "</SerialNumber>"
            "</DeviceId>";

         return ss.str();
      }

};

}

#endif
