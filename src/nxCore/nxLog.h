#ifndef  NXLOG_H
#define  NXLOG_H

#include <stdio.h>
#include <assert.h>

#define NX_LOG(a,b) printf("LOG (%s):%s\n", a,b);

#define NX_ASSERT(a) assert(a);

#endif   // NXLOG_H
