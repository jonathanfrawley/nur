#include "nxLog.h"

void nxLog(nxLogLevel logLevel,
        const char* logMsg)
{
    switch(logLevel)
    {
        case NX_LOG_INFO:
        {
            printf("INFO: %s\n", logMsg);
            break;
        }
        case NX_LOG_WARN:
        {
            printf("WARN: %s\n", logMsg);
            break;
        }
        case NX_LOG_ERROR:
        {
            printf("ERROR: %s\n", logMsg);
            break;
        }
        case NX_LOG_CRITICAL:
        {
            printf("CRITICAL: %s\n", logMsg);
            break;
        }
        default:
        {
            nxAssertFail("Log level not defined.");
            break;
        }
    }
}

void nxAssertFail(const char* logMsg)
{
    printf("CRITICAL: %s\n", logMsg);
    assert(0);
}
