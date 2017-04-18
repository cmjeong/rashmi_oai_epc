///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinStack.h"
#include "TenpinResolvConfDns.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<TenpinResolvConfDns> TenpinResolvConfDns::s_instance;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

shared_ptr<TenpinResolvConfDns> TenpinResolvConfDns::GetInstance()
{
    if (NULL == s_instance)
    {
        s_instance.reset(new TenpinResolvConfDns());
    }

    return s_instance;
}

void TenpinResolvConfDns::Add(
    u32                 id,
    const IPv4Address&  dnsServer
)
{
   if (0 != dnsServer.Get())
   {
      FILE * ofp = fopen(m_tempFilename, "wb+");
      FILE * ifp = fopen(m_configFilename, "rb");

      if (ofp && ifp)
      {
         fprintf(ofp, "# tenpin added %u\n", id);
         fprintf(ofp, "nameserver %s\n", dnsServer.ToString());

         while (!feof(ifp))
         {
            int ch = fgetc(ifp);
            if (!feof(ifp))
            {
               fputc(ch, ofp);
            }
         }

         fclose(ofp);
         ofp = NULL;
         fclose(ifp);
         ifp = NULL;

         rename(m_tempFilename, m_configFilename);
      }
      if(ofp)
      {
         fclose(ofp);
         ofp = NULL;
      }
      if(ifp)
      {
         fclose(ifp);
         ifp = NULL;
      }
   }
}

void TenpinResolvConfDns::Remove(
    u32 id
)
{
   FILE * ofp = fopen(m_tempFilename, "wb+");
   FILE * ifp = fopen(m_configFilename, "rb");

   if (ofp && ifp)
   {
      char line[256];
      u32  lineId;

      while (!feof(ifp))
      {
         line[0] = '\0';
         lineId  = ~id;

         if(fgets(line, sizeof(line), ifp) == NULL)
         {
            TRACE_MSG(" TenpinResolvConfDns::Remove, Unable to fetch line.");
         }

         if (    (1 == sscanf(line, "# tenpin added %u\n", &lineId))
               && (lineId == id)
            )
         {
            /* match, discard this and next line */
            if(fgets(line, sizeof(line), ifp) == NULL)
            {
               TRACE_MSG(" TenpinResolvConfDns::Remove, Unable to fetch line.");
            }
         }
         else
         {
            fputs(line, ofp);
         }
      }

      fclose(ofp);
      fclose(ifp);
      ofp = NULL;
      ifp = NULL;

      rename(m_tempFilename, m_configFilename);
   }
   if(ofp)
   {
      fclose(ofp);
      ofp = NULL;
   }
   if(ifp)
   {
      fclose(ifp);
      ifp = NULL;
   }
}
