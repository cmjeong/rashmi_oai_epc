///////////////////////////////////////////////////////////////////////////////
//
// Trace
//
// Debug tracing functionality available in the system.
//
// This file and thus trace functionality can be included into both
// C and C++ source files.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Trace_h_
#define __Trace_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <3waytypes.h>
#include <system/Expect.h>
#include <system/SoftwareWarningInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

// Trace string maximum length.
static const u32 TRACE_STR_MAX_LENGTH   = 3072;

// Trace levels bit masks.
static const u32 TRACE_VERBOSE          = 0x00000001;
static const u32 TRACE_INFO             = 0x00000002;
static const u32 TRACE_WARNING          = 0x00000004;
static const u32 TRACE_CRITICAL         = 0x00000008;
static const u32 TRACE_FATAL            = 0x00000010;
static const u32 TRACE_CALL_STACK       = 0x00000020;
static const u32 TRACE_EXCEPTIONS       = 0x00000040;

// Null category used when no category is required/relevant.
static const u32 TRACE_CAT_NONE         = 0;
// True indicated new line required while printing on console.
static const bool NEW_LINE_TO_BE_APPENDED     = true;
static const bool NEW_LINE_NOT_TO_BE_APPENDED = false;

///////////////////////////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////////////////////////

/**
 * Trace criticality levels mask.
 */
extern u32 g_Trace_enabledLevels;

/**
 * Application specific categories mask.
 */
extern u32 g_Trace_enabledCategories;


///////////////////////////////////////////////////////////////////////////////
// Macros
///////////////////////////////////////////////////////////////////////////////
#ifdef ENTER
#undef ENTER
#endif

#define MAXNUMCLOSEDFILES 2
#define ENTER()
#define EXIT()
#define RETURN(rETURNvAL) return (rETURNvAL);
#define RETURN_VOID()    return;

/**
 * General trace macros.
 *
 * TRACE_PRINTF     - Format as per normal printf but adds prefix (time etc) and trailing \n.
 * TRACE_PRINTF_LEV - As above but takes a trace level, TRACE_VERBOSE, TRACE_INFO etc
 * TRACE_PRINTF_CAT - As above but takes a user defined category.
 *
 * TRACE_MSG        - For when all you need to do is output a fixed string.
 * TRACE_MSG_LEV    - As above but takes a trace level, TRACE_VERBOSE, TRACE_INFO etc
 * TRACE_MSG_CAT    - As above but takes a user defined category.
 */

#define TRACE_PRINTF(pRINTFaRGS...) \
    if(g_Trace_enabledLevels & TRACE_INFO) \
        Trace_TracePrintf(TRACE_CAT_NONE, TRACE_INFO, pRINTFaRGS);

#define TRACE_PRINTF_CONSOLE(pRINTFaRGS...) \
    if(g_Trace_enabledLevels & TRACE_INFO) \
        Trace_TraceConsole(TRACE_CAT_NONE, TRACE_INFO, NEW_LINE_TO_BE_APPENDED, pRINTFaRGS);

#define TRACE_PRINTF_CONSOLE_WITHOUT_NEWLINE(pRINTFaRGS...) \
    if(g_Trace_enabledLevels & TRACE_INFO) \
        Trace_TraceConsole(TRACE_CAT_NONE, TRACE_INFO, NEW_LINE_NOT_TO_BE_APPENDED, pRINTFaRGS);

#define TRACE_PRINTF_LEV(lEVEL, pRINTFaRGS...) \
    if(g_Trace_enabledLevels & (lEVEL)) \
        Trace_TracePrintf(TRACE_CAT_NONE, lEVEL, pRINTFaRGS);

#define TRACE_PRINTF_CAT(cATEGORY, lEVEL, pRINTFaRGS...) \
    if((g_Trace_enabledCategories & (cATEGORY)) && (g_Trace_enabledLevels & (lEVEL))) \
        Trace_TracePrintf(cATEGORY, lEVEL, pRINTFaRGS);

#define TRACE_MSG(sTR) \
    if(g_Trace_enabledLevels & TRACE_INFO) \
        Trace_TracePrintf(TRACE_CAT_NONE, TRACE_INFO, "%s", sTR);

#define TRACE_MSG_LEV(lEVEL, sTR) \
    if(g_Trace_enabledLevels & (lEVEL)) \
        Trace_TracePrintf(TRACE_CAT_NONE, lEVEL, "%s", sTR);

#define TRACE_MSG_CAT(cATEGORY, lEVEL, sTR) \
    if((g_Trace_enabledCategories & (cATEGORY)) && (g_Trace_enabledLevels & (lEVEL))) \
        Trace_TracePrintf(cATEGORY, lEVEL, "%s", sTR);

#define TRACE_SHOW_MEMORY_USAGE() \
    if(g_Trace_enabledLevels & TRACE_INFO) \
        Trace_ShowMemoryUsage(TRACE_CAT_NONE, TRACE_INFO);

#define TRACE_SHOW_MEMORY_USAGE_LEV(lEVEL) \
    if(g_Trace_enabledLevels & (lEVEL)) \
        Trace_ShowMemoryUsage(TRACE_CAT_NONE, lEVEL);

#define TRACE_SHOW_MEMORY_USAGE_CAT(cATEGORY, lEVEL) \
    if((g_Trace_enabledCategories & (cATEGORY)) && (g_Trace_enabledLevels & (lEVEL))) \
        Trace_ShowMemoryUsage(cATEGORY, lEVEL);

/**
 * Macros to check if a level or category is enabled before doing lots of trace computations.
 */
#define TRACE_LEV_ENABLED(lEVEL) \
    (g_Trace_enabledLevels & (lEVEL))

#define TRACE_CAT_ENABLED(cATEGORY, lEVEL) \
    ((g_Trace_enabledCategories & (cATEGORY)) && (g_Trace_enabledLevels & (lEVEL)))


/**
 * Assert macros.  Use these for design-by-contract and other coding error situations.
 */
#ifdef COVERITY_ANALYSIS
/**
 * This is for Coverity analysis only, it does not affect the real code at all.
 */
#include <assert.h>
#define RSYS_ASSERT(cONDITION)                       assert((cONDITION))
#define RSYS_ASSERT_PRINTF(cONDITION,pRINTFaRGS...)  assert((cONDITION))
#define RSYS_ASSERT_FAIL(pRINTFaRGS...)              assert((1==0))
/**
 * End of Coverity bit
 */
#else

#define RSYS_ASSERT(cONDITION) \
do { \
    bool assertionFailed = !(cONDITION); \
    if( unlikely( assertionFailed ) ) \
    { \
        const int errNum = errno; \
        Trace_TraceAssert(__BASE_FILE__, __FILE__, __LINE__, __FUNCTION__, \
                          __builtin_return_address(0), \
                          errNum, \
                          #cONDITION, \
                          " "); \
    } \
} while(false) // swallow semi-colon

#define RSYS_ASSERT_PRINTF(cONDITION, pRINTFaRGS...) \
do { \
    bool assertionFailed = !(cONDITION); \
    if( unlikely( assertionFailed ) ) \
    { \
        const int errNum = errno; \
        Trace_TraceAssert(__BASE_FILE__, __FILE__, __LINE__, __FUNCTION__, \
                          __builtin_return_address(0), \
                          errNum, \
                          #cONDITION, \
                          pRINTFaRGS); \
    } \
} while(false) // swallow semi-colon

#define RSYS_ASSERT_FAIL(pRINTFaRGS...) \
do { \
        const int errNum = errno; \
        Trace_TraceAssert(__BASE_FILE__, __FILE__, __LINE__, __FUNCTION__, \
                          __builtin_return_address(0), \
                          errNum, \
                          "Fail", \
                          pRINTFaRGS); \
} while(false) // swallow semi-colon

#endif

#ifdef __cplusplus
extern "C"
{
    // _start and _fini are the first and last text symbols
    // defined, respectively.  As we are statically linked,
    // all text symbols *must* be between these two.
    void _start();
    void _fini();
}

#define RSYS_ASSERT_FUNC_PTR(fn_p) \
    RSYS_ASSERT_PRINTF(((void*)(fn_p) < (void*)_start) || ((void*)(fn_p) > (void*)_fini), "Invalid code address " #fn_p);
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes / Functions
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

void Trace_TracePrintf(u32 category, u32 level, const char *format, ...) __attribute__((format(printf, 3, 4)));  /* 3=format 4=params */

void Trace_TraceConsole(u32 category, u32 level, bool isNewLineRequired, const char *format, ...) __attribute__((format(printf, 4, 5)));  /* 3=format 4=params */

int  Trace_TracePrintfFatal(const char *format, ...) __attribute__((format(printf, 1, 2)));  /* 1=format 2=params */

void Trace_FuncHex (const char *strMsg, const u8 *data, u32 datalength);

void Trace_TraceMessageSequenceTag(const char *src, const char *dest, const char *pd, const char *mt,
                                            u32 pid, const char *p1, const char *p2, const char *desc);
void Trace_TraceMessageSequenceShortTag(const char *src, const char *dest, const char *pd,
                                                 const char *mt, const char *desc);
void Trace_TraceAssert(const char *baseFile, const char *file, u32 line, const char * function,
                       const void *retAddrPtr, const int errNum,
                       const char *condition, const char *format, ...)  __attribute__((format(printf, 8, 9))); /* 8=format 9=params */;

void Trace_ShowMemoryUsage(u32 category, u32 level);

void Trace_EnableStdoutLogging(void);

void Trace_SetFileLoggingParams(const char *traceDir, const char *outputFileName);

void Trace_EnableFileLogging(u32 traceFileLimit);

/**
 * Unit tests can disable abort() after assert and then
 * catch it as an exception instead to allow checking of
 * function contract and other error/edge conditions.
 * Not to be used in release code!!
 */
void Trace_SetAssertAbortDisabled(bool abortDisabled);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

//
// C++ version - we are including this header file in C++ code.
//

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class Trace;
class Exception;
class TimeWrap;

///////////////////////////////////////////////////////////////////////////////
// Macros
///////////////////////////////////////////////////////////////////////////////

/**
 * General trace macros.
 *
 * TRACE            - Can take a string and one variable from a set of basic types.
 *                    May be more efficient than TRACE_PRINTF so favour it for single variable trace.
 * TRACE_LEV        - As above but takes a trace level, TRACE_VERBOSE, TRACE_INFO etc
 * TRACE_CAT        - As above but takes a user defined category.
 */

#define TRACE(mESSAGE, oBJECT) \
    if(g_Trace_enabledLevels & TRACE_INFO) \
        threeway::Trace::GetInstance().TraceFunc (0, TRACE_INFO, mESSAGE, oBJECT);

#define TRACE_LEV(lEVEL, mESSAGE, oBJECT) \
    if(g_Trace_enabledLevels & (lEVEL)) \
        threeway::Trace::GetInstance().TraceFunc (0, lEVEL, mESSAGE, oBJECT);

#define TRACE_CAT(cATEGORY, lEVEL, mESSAGE, oBJECT) \
    if((g_Trace_enabledCategories & (cATEGORY)) && (g_Trace_enabledLevels & (lEVEL))) \
        threeway::Trace::GetInstance().TraceFunc (cATEGORY, lEVEL, mESSAGE, oBJECT);

/**
 * A selection of more specialist trace macros.
 */

#define TRACE_X(mESSAGE, dATA, dATAlEN) \
    threeway::Trace::GetInstance().TraceFunc (0, TRACE_INFO, mESSAGE, dATA, dATAlEN);

#define TRACE_HEX(mESSAGE, vARu32) \
    threeway::Trace::GetInstance().TraceFuncHex (TRACE_INFO, mESSAGE, vARu32);

#define TRACE_HEX_MSG(mESSAGE, dATA, dATAlEN) \
    threeway::Trace::GetInstance().TraceFuncHex (TRACE_INFO, mESSAGE, dATA, dATAlEN);

#define TRACE_EXCEPTION(eXCEPTION) \
    if (g_Trace_enabledLevels & TRACE_EXCEPTIONS) \
        threeway::Trace::GetInstance().TraceFunc (0, TRACE_EXCEPTIONS, eXCEPTION);

/**
 * Macros for generating Protocol Professor style trace.
 *
 * E.g. PP|12:01:37.465011|M3UA-PEER|M3UA|M3UA|PayloadData||||opc=4 dpc=152 si=3 ni=0 mp=0 sls=8
 */

#define MESSAGE_TAG(srcLayer, destLayer, protocol, messageType, procedureId, transactionId1, transactionId2, additionalInfo) \
    threeway::Trace::GetInstance().TraceMessageSequenceTag (srcLayer, destLayer, protocol, messageType, procedureId, transactionId1, transactionId2, additionalInfo);

#define MESSAGE_TAG_SHORT(srcLayer, destLayer, protocol, messageType, additionalInfo) \
    threeway::Trace::GetInstance().TraceMessageSequenceTag (srcLayer, destLayer, protocol, messageType, additionalInfo);

#define MESSAGE_TAG_LEV(enable, level, srcLayer, destLayer, protocol, messageType, procedureId, transactionId1, transactionId2, additionalInfo) \
    if((enable) && (g_Trace_enabledLevels & (level))) \
        threeway::Trace::GetInstance().TraceMessageSequenceTag (srcLayer, destLayer, protocol, messageType, procedureId, transactionId1, transactionId2, additionalInfo);

#define MESSAGE_TAG_SHORT_LEV(level, srcLayer, destLayer, protocol, messageType, additionalInfo) \
    if(g_Trace_enabledLevels & (level)) \
        threeway::Trace::GetInstance().TraceMessageSequenceTag (srcLayer, destLayer, protocol, messageType, additionalInfo);

#define MESSAGE_TAG_SHORT_CAT(category, level, srcLayer, destLayer, protocol, messageType, additionalInfo) \
    if((g_Trace_enabledCategories & (category)) && (g_Trace_enabledLevels & (level))) \
        threeway::Trace::GetInstance().TraceMessageSequenceTag (srcLayer, destLayer, protocol, messageType, additionalInfo);

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

std::string Trace_GetMemoryUsageStr();

class Trace
{
protected:
    // Is singleton so private constructor.
    Trace();

public:
    /**
     * Get trace level/category as string.
     */
    static const char * TraceLevelToStr(u32 level);
    static const char * TraceCatToStr(u32 category);

    virtual ~Trace();
    static Trace& GetInstance();

    /**
     * Set a string used by trace functions when they need to dump
     * info about the application.  E.g. on an assert.
     */
    void SetApplicationInfo(const std::string& appInfo);
    std::string GetApplicationInfo() const { return m_appInfo; }

    void SetSoftwareWarningInterface( SoftwareWarningInterface * softwareWarningInterface, u32 level = TRACE_CRITICAL )
    {
        m_swWarningInterface = softwareWarningInterface;
        m_logSoftwareWarningLevel = level;
    }
    /**
     * Set up dir/filename for logging to file.
     */
    void SetFileLoggingParams(const char *traceDir, const char *outputFileName);

    /** Remove any old trace files for this app.
     */
    void RemoveOldTraceFiles();

    /**
     * Get/Set Trace Levels
     *
     * Accessors for the criticality mask.
     * Levels are user defined so can vary from app to app.
     */
    void SetTraceLevelsMask(u32 levelsMask);    // Modify entire levels mask.
    void SetTraceLevelOn(u32 levelsMask);       // Turn on specific level(s).
    void SetTraceLevelOff(u32 levelsMask);      // Turn off specific level(s).
    u32 GetTraceLevelsMask() const { return g_Trace_enabledLevels; };

    /**
     * Get/Set Trace Categories
     *
     * Accessors for the categories mask.
     * Categories are user defined so can vary from app to app.
     * An app must register the categories it wants to use.
     * The mask is unique per application.
     */
    void RegisterTraceCategory(u32 categoryMask, const char * categoryString); // Register a single category.
    void SetTraceCategoriesMask(u32 categoriesMask);    // Modify entire categories mask.
    void SetTraceCategoriesOn(u32 categoriesMask);      // Turn on specific categories.
    void SetTraceCategoriesOff(u32 categoriesMask);     // Turn off specific categories.
    u32  GetTraceCategoryFromString(const char * categoryString) const; // Get numeric category from string - allows easy set/clear by cat name from CLI.
    u32 GetTraceCategoriesMask() const { return g_Trace_enabledCategories; };

    void TraceFunc (u32 category, u32 level, const char *message, u32 numberValue);
    void TraceFunc (u32 category, u32 level, const char *message, s32 numberValue);
    void TraceFunc (u32 category, u32 level, const char *message, const char *strValue);
    void TraceFunc (u32 category, u32 level, const char *message, const std::string& str);
    void TraceFunc (u32 category, u32 level, const char *message, bool boolValue);
    void TraceFunc (u32 category, u32 level, const Exception &e);
    void TraceFunc (u32 category, u32 level, const char *message, const u8 digitArray [], u16 digitCount);
    void TraceFunc (u32 category, u32 level, const char *message, const TimeWrap &timeValue);
    void TraceFuncHex (u32 level, const char *message, u32 numberValue);
    void TraceFuncHex (u32 level, const char *message, const u8 *data, u32 datalength);

    void TraceMessageSequenceTag (const char *src, const char *dest, const char *pd, const char *mt,
                                  u32 pid, const char *p1, const char *p2, const char *desc);
    void TraceMessageSequenceTag (const char * src, const char * dest, const char * pd,
                                  const char * mt, const char * pid, const char *p1,
                                  const char * p2, const char * desc);
    void TraceMessageSequenceTag (const char * src, const char * dest, const char * pd,
                                  const char * mt, const char * desc);

    void AppendTraceToExistingFile ();

    // Enable console logging.  Not normally done, useful for unit tests though.
    void EnableStdoutLogging() { m_logToStdout = true; }
    bool IsStdoutLogging() { return m_logToStdout; }

    // Enable/disable/check logging to file.
    void EnableFileLogging (u32 traceFileLimit);
    void DisableFileLogging (const char * reason = NULL);
    bool LoggingToFile () const;
    const char * GetTraceFilename() const;

    // Enable/disable/check logging to UDP socket.
    void EnableUDPLogging (u16 destinationPort, u32 destinationAddress);
    void DisableUDPLogging ();
    bool LoggingToUdp () const;
    u32  GetUdpLoggingDestAddr() const;
    u16  GetUdpLoggingDestPort() const;

    const char * GetAssertionFailureLogFilename() const {return m_assertionFailureLogFilename;}

    /**
     * Get text of current trace levels etc.
     */
    std::string ToString() const;

    /**
     * Get text of available trace categories.
     */
    std::string GetRegisteredTraceCategoriesString() const;

    /**
     * Get a nicely formatted time string.
     */
    void GetTimeStr(char * outputBuff, u32 outputBuffLen);

    void LogToStderr(const char * traceMsg);
    void LogToFile(const char * traceMsg);
    void LogToUdp(const char *traceMsg);
    // Log warnings to AlarmLog
    void LogWarnings( u32 level, const char *traceMsg);
    int GetLogFilesToUpload(std::string filename[]);
protected:
    // Singleton instance.
    static shared_ptr<Trace> s_instance;

    /**
     * Get call stack indent - for use by derived classes e.g. NASTrace.
     */
    u32 GetCallStackIndent() const;

    // Trace directory and file name prefix.
    char    m_traceDir[MAX_PATH_LENGTH];
    char    m_outputFileNamePrefix[64];

    // Actual log file name.
    char    m_outputFileName[MAX_PATH_LENGTH];
    char    FileName[MAX_PATH_LENGTH];

private:
    // Logging to console (stdout).
    bool m_logToStdout;

    // Logging to file
    bool    m_loggingToFile;
    FILE *  m_outputFile;

    void TurnFileLoggingOn ();
    void TurnFileLoggingOff (const char *porQue = NULL);
    void StartNewTraceFile ();

    // Logging over UDP
    bool    m_loggingToUdp;
    SOCKET  m_loggingSocket;
    u32     m_destinationAddress;
    u16     m_destinationPort;

    void TurnUdpLoggingOn (u16 destinationPort, u32 destinationAddress);
    void TurnUdpLoggingOff ();

    bool SelectExistingTraceFile ();
    bool EndsWith(const char *end, const char *s);

    // Some info about the current app.  E.g. name and version.
    std::string m_appInfo;

    bool    m_appendloggingToExistingFile;

    // When an assert goes off we write a file to NV.  This variable
    // stores the path and filename of that file.
    static const char * m_assertionFailureLogFilename;

    // Maximum size (in bytes) of a trace file.
    // They are cycled if they reach this limit.
    u32 m_traceFileLimit;

    SoftwareWarningInterface * m_swWarningInterface;
    u32     m_logSoftwareWarningLevel;
    int m_numClosedFiles;
    int m_fileToDelete;
    std::string m_closedFiles[MAXNUMCLOSEDFILES];
};

}

#else

//
// C version - we are including this header file in C code.
//

#define MESSAGE_TAG(srcLayer, destLayer, protocol, messageType, procedureId, transactionId1, transactionId2, additionalInfo) \
    Trace_TraceMessageSequenceTag(srcLayer, destLayer, protocol, messageType, \
                                           procedureId, transactionId1, transactionId2, additionalInfo);

#define MESSAGE_TAG_SHORT(srcLayer, destLayer, protocol, messageType, additionalInfo) \
    Trace_TraceMessageSequenceTagShort(srcLayer, destLayer, protocol, messageType, additionalInfo);

#define TRACE_HEX_MSG(strMsg, data, dataLength) \
    Trace_FuncHex(strMsg, data, dataLength);

#endif /* C code */

#endif
