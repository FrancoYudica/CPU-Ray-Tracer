/// Replaces glm functions with simpler macros
/// Simpler vector type definitions
#ifndef __RT_MATH__
#define __RT_MATH__
#include "Constants.hpp"

namespace RT {

namespace Math {
#define IsZero(X) (X > -0.0001f && X < 0.0001f)
    static bool IsPerfectSquare(uint32_t X)
    {
        return powf(static_cast<int>(sqrt(X)), 2) == X;
    }

    static RGBColor pow(const RGBColor& color, float v)
    {
        return RGBColor(powf(color.r, v), powf(color.g, v), powf(color.b, v));
    }

    template <typename T>
    static T normalize(const T& v)
    {
        return glm::normalize(v);
    }

    template <typename T>
    static double magnitude(const T& v)
    {
        return glm::length(v);
    }

    static double magnitude_squared(const Vec3& v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    static double dot(const Vec3& x, const Vec3& y)
    {
        return glm::dot(x, y);
    }

    template <typename T>
    static T cross(const T& x, const T& y)
    {
        return glm::cross(x, y);
    }

    /// @brief Returns angle in range [0, 2PI]
    static double atan2_ranged(double y, double x)
    {
        double v = atan2(y, x);
        if (v < 0.0)
            v += Constants::PI_2;

        return v;
    }

    static Mat4 transpose(const Mat4& mat)
    {
        return glm::transpose(mat);
    }

    static Mat4 inverse(const Mat4& mat)
    {
        return glm::inverse(mat);
    }

    static Mat4 identity_mat4()
    {
        Mat4 i;
        i[0][0] = 1.0;
        i[1][1] = 1.0;
        i[2][2] = 1.0;
        i[3][3] = 1.0;
        return i;
    }

    int solve_quadric(double c[3], double s[2]);
    int solve_cubic(double c[4], double s[3]);
    int solve_quartic(double c[5], double s[4]);

}
}

#endif