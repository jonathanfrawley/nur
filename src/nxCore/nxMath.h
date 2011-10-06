#ifndef  NXMATH_H
#define  NXMATH_H

#include <math.h>
#include <nxCore/nxTypes.h>

const nxFloat NX_PI = 3.14159265f;
const nxFloat NX_PI_OVER_180 = 0.0174532925f;

#define nxMath_sqrt(x) sqrtf(x)
#define nxMath_pow(x,y) powf(x,y)
#define nxMath_abs(x) fabs(x)

nxFloat nxMath_radToDeg(nxFloat x)
{
	return x * (180.0f/NX_PI);
}

#endif   // NXMATH_H
