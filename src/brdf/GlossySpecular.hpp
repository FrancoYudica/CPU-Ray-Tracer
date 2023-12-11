/*
-----Implementations of glossy specular models.--------------------------------
- The first BRDF uses the Phong implementation, calculating the reflected
direction and then computing dot product with light direction
- The seconds BRDF uses Blinn modification to Phong model, where instead of
calculating the reflected direction, just adds the ray direction and the light
direction, and then computes the dot product with the surface normal. This is a
great approximation.

*/

#ifndef __RT_BRDF_GLOSSY_SPECULAR__
#define __RT_BRDF_GLOSSY_SPECULAR__

#include "../BRDF.hpp"
#include "../Constants.hpp"

namespace RT {
namespace BRDFS {
    class GlossySpecularPhong : public BRDF {
    public:
        GlossySpecularPhong()
            : ks(1.0f)
            , e(8)
            , cs(Constants::WHITE)
            , BRDF(BRDFType::GlossySpecularPhong)
        {
        }

        inline void set_specular_coefficient(float k) { ks = k; }
        inline void set_specular_exp(float exp) { e = exp; }
        inline void set_specular_color(const RGBColor& color) { cs = color; }

        RGBColor f(
            const ShadeRec& sr,
            const Vec3& wi,
            const Vec3& wo) const override;

        virtual RGBColor sample_f(
            const ShadeRec& sr,
            Vec3& wi,
            const Vec3& wo) const { return Constants::BLACK; };

        virtual RGBColor rho(
            const ShadeRec& sr,
            const Vec3& wo) const { return Constants::BLACK; }

    public:
        /// @brief Specular reflection coefficient in range [0, 1]
        float ks;

        /// @brief Specular power exponent
        float e;

        /// @brief Specular color
        RGBColor cs;
    };

    class GlossySpecularBlinnPhong : public BRDF {
    public:
        GlossySpecularBlinnPhong()
            : ks(1.0f)
            , e(8)
            , cs(Constants::WHITE)
            , BRDF(BRDFType::GlossySpecularBlinnPhong)
        {
        }

        inline void set_specular_coefficient(float k) { ks = k; }
        inline void set_specular_exp(float exp) { e = exp; }
        inline void set_specular_color(const RGBColor& color) { cs = color; }

        RGBColor f(
            const ShadeRec& sr,
            const Vec3& wi,
            const Vec3& wo) const override;

        virtual RGBColor sample_f(
            const ShadeRec& sr,
            Vec3& wi,
            const Vec3& wo) const { return Constants::BLACK; };

        virtual RGBColor rho(
            const ShadeRec& sr,
            const Vec3& wo) const { return Constants::BLACK; }

    public:
        /// @brief Specular reflection coefficient in range [0, 1]
        float ks;

        /// @brief Specular power exponent
        float e;

        /// @brief Specular color
        RGBColor cs;
    };

}
}

#endif