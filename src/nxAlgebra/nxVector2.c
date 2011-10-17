#include "nxVector2.h"

void nxVector2_fromCpVect(cpVect* vec, nxVector2* res)
{
    res->x = vec->x;
    res->y = vec->y;
}

void nxVector2_toCpVect(nxVector2* vec, cpVect* res)
{
    res->x = vec->x;
    res->y = vec->y;
}
