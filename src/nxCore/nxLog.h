#ifndef  NXLOG_H
#define  NXLOG_H

#include <stdio.h>
#include <assert.h>

/**
 * Simple Logging helper functions.
 **/
enum nxLogLevel 
{
    NX_LOG_INFO,
    NX_LOG_WARN,
    NX_LOG_ERROR
};

void nxLog(nxLogLevel logLevel
        const char* logMsg);
void nxAssertFail(const char* logMsg);

#endif   // NXLOG_H
