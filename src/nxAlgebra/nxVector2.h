#ifndef  NXVECTOR2_H
#define  NXVECTOR2_H

#include <chipmunk.h>

#include <nxCore/nxTypes.h>

typedef struct nxVector2
{
	nxFloat x;
	nxFloat y;
} nxVector2;

void nxVector2_fromCpVect(cpVect* vec, nxVector2* res);
void nxVector2_toCpVect(const nxVector2* vec, cpVect* res);

#endif   // NXVECTOR2_H
