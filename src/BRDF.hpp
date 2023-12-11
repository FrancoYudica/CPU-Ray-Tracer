#ifndef __RT_BRDF_H__
#define __RT_BRDF_H__
#include "Constants.hpp"
#include "Sampler.hpp"
#include <memory>

namespace RT {

enum class BRDFType {
    Lambertian,
    GlossySpecularPhong,
    GlossySpecularBlinnPhong
};

class ShadeRec;
class BRDF {
public:
    BRDF(BRDFType type)
        : _type(type)
    {
    }

    inline BRDFType get_type() const { return _type; }

    /// @brief
    /// @param wi Incoming direction
    /// @param wo reflected direction
    /// @return
    virtual RGBColor f(
        const ShadeRec& sr,
        const Vec3& wi,
        const Vec3& wo) const
        = 0;

    /// @brief Used to compute the direction of reflected rays
    /// @return
    virtual RGBColor sample_f(
        const ShadeRec& sr,
        Vec3& wi,
        const Vec3& wo) const
        = 0;

    /// @brief
    /// @return bihemispherical reflectance
    virtual RGBColor rho(
        const ShadeRec& sr,
        const Vec3& wo) const
        = 0;

protected:
    std::shared_ptr<Sampler> sampler;

private:
    BRDFType _type;
};
}

#endif