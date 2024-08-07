#ifndef __RT_RAY__
#define __RT_RAY__
#include "math_RT.hpp"

namespace RT {
struct Ray {
    Vec3 origin;
    Vec3 direction;
    Vec3 at(double t) const { return origin + t * direction; }
};
}

#endif