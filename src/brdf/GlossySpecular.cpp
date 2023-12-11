#include "GlossySpecular.hpp"
#include "../Ray.hpp"
#include "../ShadeRec.hpp"

using namespace RT;

RGBColor BRDFS::GlossySpecularPhong::f(
    const ShadeRec& sr,
    const Vec3& wi,
    const Vec3& wo) const
{
    // Phong model implementation
    RGBColor L;

    // Calculates reflected direction
    Vec3 normal = sr.get_normal();
    double n_dot_wi = Math::dot(normal, wi);
    Vec3 r(-wi + 2.0 * normal * n_dot_wi);

    // Specular cos(a)
    float r_dot_wo = Math::dot(r, wo);

    if (r_dot_wo > 0.0)
        L = cs * (ks * std::pow(r_dot_wo, e));

    return L;
}

RGBColor BRDFS::GlossySpecularBlinnPhong::f(
    const ShadeRec& sr,
    const Vec3& wi,
    const Vec3& wo) const
{
    // Blinn model implementation
    RGBColor L;

    Vec3 r = Math::normalize(wi + wo);

    float r_dot_n = Math::dot(r, sr.get_normal());

    if (r_dot_n > 0.0)
        L = cs * (ks * std::pow(r_dot_n, e));

    return L;
}
