///////////////////////////////////////////////////////////////////////////////
//
// NASDatabase.cpp
//
// The common information held in all of the NAS database files.  Also some
// common management functions are here.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include <system/TimeWrap.h>
#include <system/StringUtils.h>

#include <System3Way.h>
#include <NASTrace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASDatabase.h"
#include "NASString.h"

///////////////////////////////////////////////////////////////////////////////
// Class: NASDatabase
// Desc : Top level entry point for asking the NASDatabase questions.
///////////////////////////////////////////////////////////////////////////////

NASDatabase::NASDatabase (const char *databaseName) :
	m_databaseFile (NULL)
{
	NAS_ENTER ();

	strncpysafe (m_databaseName, databaseName, sizeof(m_databaseName));

	NAS_EXIT ();
}

NASDatabase::~NASDatabase ()
{
	NAS_ENTER ();
	NAS_EXIT ();
}

void NASDatabase::OpenNASDatabase ()
{
	NAS_ENTER ();
	NAS_MSG ("******************************");
	NAS_MSG ("**  NASDatabase Opening DB  **");
	NAS_MSG ("******************************");
	NAS_TRACE ("Using Database", m_databaseName);

	if (m_databaseFile != NULL)
	{
		fflush (m_databaseFile);
		fclose (m_databaseFile);
	}//end if

	NAS_MSG ("NASDatabase IS Running");
	if ((m_databaseFile = fopen (m_databaseName, "r+b")) != NULL)
	{
		NASDatabaseHeader dbContents;
		fread (&dbContents, sizeof (NASDatabaseHeader), 1, m_databaseFile);

		NAS_TRACE ("Obtained Header, Number Of Records Is", dbContents.dbEntries);
		if (dbContents.dbEntries > 0)
			ReadDatabaseContent (dbContents.dbEntries, m_databaseFile);
	}
	else
	{
		NAS_MSG ("Database Not Present - Trying To Create");
		if ((m_databaseFile = fopen (m_databaseName, "wb")) != NULL)
		{
			NASDatabaseHeader dbContents;
			memset (&dbContents, 0, sizeof (NASDatabaseHeader));

			threeway::TimeWrap t1;
			NASString s1 (t1);
			s1 [s1.GetLength() - 5] = '\0';

			strncpysafe(dbContents.dbCreated, (const char *) s1, sizeof(dbContents.dbCreated));
			strncpysafe(dbContents.dbUpdated, (const char *) s1, sizeof(dbContents.dbUpdated));
			dbContents.dbEntries = 0;

			fwrite (&dbContents, sizeof (NASDatabaseHeader), 1, m_databaseFile);

			// Okay the header information is out, let's see if the leaf class
			// has any defaults to put into this shiny new database.
			CreateDatabase (m_databaseFile);
			fclose (m_databaseFile);

			m_databaseFile = fopen (m_databaseName, "r+b");

			NAS_MSG ("Empty Database Created & Ready For Use");
		}
		else
		{
			NAS_MSG ("********************************************");
			NAS_MSG ("**  Very Serious - No Database Available  **");
			NAS_MSG ("********************************************");
		}//end if
	}//end if

	// And intentionally leave it open.  Prevent any malicious influences from editing / deleting
	// it from under us while we are running.

	NAS_EXIT ();
}

void NASDatabase::CloseNASDatabase ()
{
	NAS_ENTER ();
	NAS_MSG ("************************");
	NAS_MSG ("**  Closing Database  **");
	NAS_MSG ("************************");

	if (m_databaseFile != NULL)
	{
		fflush (m_databaseFile);
		fclose (m_databaseFile);
		m_databaseFile = NULL;
	}//end if

	NAS_EXIT ();
}

void NASDatabase::AppendNASDatabaseItem (void *databaseItem, u32 itemSize)
{
	NAS_ENTER ();

	if (m_databaseFile != NULL)
	{
		// Ths is a _bit_ of a hack, but it's SUPER efficient as a solution
		// so tat's why I've done it.  Just read / write the new number of
		// entries field, then fast forward to the end and append the new item.
		u32 dbEntryCount = 0;
		fseek (m_databaseFile, 64, SEEK_SET);
		fread (&dbEntryCount, sizeof (u32), 1, m_databaseFile);

		NAS_TRACE ("Appending Database Item: Old Number Of Entries Was", dbEntryCount);
		dbEntryCount++;
		fseek (m_databaseFile, 64, SEEK_SET);
		fwrite (&dbEntryCount, sizeof (u32), 1, m_databaseFile);

		fseek (m_databaseFile, 0, SEEK_END);
		fwrite (databaseItem, itemSize, 1, m_databaseFile);

		fflush (m_databaseFile);

	}//end if

	NAS_EXIT ();
}

void NASDatabase::CommitNASDatabase (u32 dbEntries)
{
	NAS_ENTER ();

	if (m_databaseFile != NULL)
	{
		// Perhaps we better start at the beginning...
		rewind (m_databaseFile);

		// Empty a default header ready for use...
		NASDatabaseHeader dbContents;
		memset (&dbContents, 0, sizeof (NASDatabaseHeader));

		// Read existing header to preserve create time.
		fread (&dbContents, sizeof (NASDatabaseHeader), 1, m_databaseFile);

		// New entry count + update time.
		dbContents.dbEntries = dbEntries;

		threeway::TimeWrap t1;
		NASString s1 (t1);
		s1 [s1.GetLength() - 5] = '\0';
		strncpysafe(dbContents.dbUpdated, (const char *) s1, sizeof(dbContents.dbUpdated));

		NAS_TRACE ("NASDatabase Entry Count Is", dbContents.dbEntries);

		// Don't forget to rewind us again!!  We previously read the header.
		rewind (m_databaseFile);
		fwrite (&dbContents, sizeof (NASDatabaseHeader), 1, m_databaseFile);

		if (dbContents.dbEntries > 0)
			WriteDatabaseContent (m_databaseFile);

		fflush (m_databaseFile);
	}//end if

	NAS_EXIT ();
}


