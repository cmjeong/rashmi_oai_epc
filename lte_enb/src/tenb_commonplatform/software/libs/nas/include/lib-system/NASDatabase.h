///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASDatabase.h
//
// The common information held in all of the NAS database files.  Also some
// common management functions are here.
//
// Copyright ? 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASDatabase_h_
#define __NASDatabase_h_


///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

typedef struct structNASDatabaseHeader
{
	// Date and time the database file was first created.
	char dbCreated[32];

	// Date and time the database file was last updated.
	char dbUpdated[32];

	// Number of entries in the database.
	u32 dbEntries;

}NASDatabaseHeader;

///////////////////////////////////////////////////////////////////////////////
// Class: NASDatabase
// Desc : Top level entry point for asking the NASDatabase questions.
///////////////////////////////////////////////////////////////////////////////
class NASDatabase
{
public:
	// Construction / destruction.
	NASDatabase  (const char *databaseName);
	virtual ~NASDatabase ();

	void OpenNASDatabase ();
	void CloseNASDatabase ();
	void CommitNASDatabase (u32 numberOfEntries);
	void AppendNASDatabaseItem (void *databaseItem, u32 itemSize);

	virtual void CreateDatabase (FILE *dbHandle) = 0;
	virtual void ReadDatabaseContent (u32 numberOfEntries, FILE *dbHandle) = 0;
	virtual void WriteDatabaseContent (FILE *dbHandle) = 0;

protected:

	// Name of the physical database file.
	char m_databaseName[MAX_PATH];

	// Handle to the archive file.  We update this every time there is an
	// operation that results in a change to the NASDatabase content.  Should
	// we make this *protected* so that leaf classes can access database directly?
	FILE *m_databaseFile;
};

#endif
