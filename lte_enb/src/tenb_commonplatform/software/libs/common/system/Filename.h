///////////////////////////////////////////////////////////////////////////////
//
// Filename.h
//
// Manage a string of representing a Filename.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Filename_h_
#define __Filename_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

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

class Filename : public std::string
{
    // Some naming conventions derived from GNU make.
public:
                                                // e.g.
    Filename( std::string filename);            //  /tmp/blah.tar.gz
    Filename( std::string dir,                  //  /tmp/
              std::string notdir);              //  blah.tar.gz
    Filename( std::string dir,                  //  /tmp/
              std::string notdirLessSuffix,     //  blah.tar
              std::string suffix);              //  .gz

    virtual ~Filename() {}

                                                // e.g.
    Filename GetNotDir() const;                 //  blah.tar.gz
    Filename GetDir() const;                    //  /tmp/
    Filename GetBasename() const;               //  /tmp/blah.tar
    std::string GetSuffix() const;              //  .gz

    void SetNotDir( std::string );
    void SetDir( std::string );
    void SetBasename( std::string );
    void SetSuffix( std::string );

private:
    bool EndsWithSlash( const std::string & );
    void AppendSuffix( const std::string & );
};

}

#endif
