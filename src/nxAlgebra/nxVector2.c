#include "nxVector2.h"

void nxVector2_init0(nxVector2* obj)
{
    obj->x = 0.0f;
    obj->y = 0.0f;
}

void nxVector2_init(nxVector2* obj,
        nxFloat x,
        nxFloat y)
{
    obj->x = x;
    obj->y = y;
}

/*
void nxVector2_fromCpVect(cpVect* vec, nxVector2* res)
{
    res->x = vec->x;
    res->y = vec->y;
}

void nxVector2_toCpVect(const nxVector2* vec, cpVect* res)
{
    res->x = vec->x;
    res->y = vec->y;
}
*/
