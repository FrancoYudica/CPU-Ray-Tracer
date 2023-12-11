#ifndef __RT_BRDF_LAMBERTIAN__
#define __RT_BRDF_LAMBERTIAN__
#include "../BRDF.hpp"

namespace RT {
namespace BRDFS {
    class Lambertian : public BRDF {
    public:
        Lambertian()
            : kd(1.0f)
            , cd(Constants::WHITE)
            , BRDF(BRDFType::Lambertian)
        {
        }

        RGBColor f(
            const ShadeRec& sr,
            const Vec3& wi,
            const Vec3& wo) const override;

        RGBColor sample_f(
            const ShadeRec& sr,
            Vec3& wi,
            const Vec3& wo) const override;

        RGBColor rho(
            const ShadeRec& sr,
            const Vec3& wo) const override;

    public:
        /// @brief Diffuse reflection coefficient in range [0, 1]
        float kd;

        /// @brief Diffuse color
        RGBColor cd;
    };
}
}

#endif