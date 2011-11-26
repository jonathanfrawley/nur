#ifndef  NXMATH_H
#define  NXMATH_H

#include <math.h>
#include <nxCore/nxTypes.h>
#include <nxCore/nxConstants.h>
#include <float.h>

#define NX_MAX_FLOAT FLT_MAX

#define nxMath_sqrt(x) sqrtf(x)
#define nxMath_pow(x,y) powf(x,y)
#define nxMath_abs(x) fabs(x)

#define nxMath_radToDeg(x) (x * (180.0f/NX_PI))

/*
inline nxFloat nxMath_radToDeg(nxFloat x)
{
	return x * (180.0f/NX_PI);
}
*/

#endif   // NXMATH_H
