#ifndef DEFINES_H
#define DEFINES_H

//#include "libfixmath/fixmath.h"
//include "fixed_point.h"
#include "fixed_point.hpp"

//typedef fix16_t dtype;
//typedef uint8_t dtype;
//typedef fpml::fixed_point<short,8> dtype;
typedef FixedPoint<4,4> dtype;
#define WINDOW_SIZE		256
#define GAP_SHAPE		192
#define OUTPUT_SIZE		256
#define ITERATOR_BITS	9
#endif