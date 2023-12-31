#ifndef __RT_CONSTANTS__
#define __RT_CONSTANTS__
#include "Types_rt.hpp"
#include <limits>

namespace RT {
namespace Constants {
    /// @brief Used for shadow ray "displacement"
    static double k_epsilon = 0.0001;
    static double k_2_epsilon = 2.0 * k_epsilon;
    static double k_huge_value = std::numeric_limits<double>::max();

    // COLORS
    static RGBColor BLACK(0.0f, 0.0f, 0.0f);
    static RGBColor WHITE(1.0f, 1.0f, 1.0f);
    static RGBColor RED(1.0f, 0.0f, 0.0f);
    static RGBColor GREEN(0.0f, 1.0f, 0.0f);
    static RGBColor BLUE(0.0f, 0.0f, 1.0f);
    static RGBColor YELLOW(1.0f, 1.0f, 0.0f);
    static RGBColor PINK(1.0f, 0.0f, 1.0f);

    static Vec3 JITTERED_UP(0.0072, 1.0, 0.0034);

    static Vec3 I(1.0, 0.0, 0.0);
    static Vec3 J(0.0, 1.0, 0.0);
    static Vec3 K(0.0, 0.0, 1.0);

    static double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
    static double PI_2 = PI * 2.0;
    static double PI_OVER_2 = PI / 2.0;
    static double PI_OVER_4 = PI / 4.0;
    static double INV_PI = 1.0 / PI;
    static double PI_OVER_180 = PI / 180.0;
    static double OVER_180_PI = 180.0 / PI;
}
}

#endif