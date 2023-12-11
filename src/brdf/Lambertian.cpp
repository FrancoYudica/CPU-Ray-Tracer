#include "Lambertian.hpp"

using namespace RT;
using namespace BRDFS;

RGBColor Lambertian::f(
    const ShadeRec& sr,
    const Vec3& wi,
    const Vec3& wo) const
{
    return (float)(Constants::INV_PI * kd) * cd;
}

RGBColor Lambertian::sample_f(
    const ShadeRec& sr,
    Vec3& wi,
    const Vec3& wo) const
{
    return Constants::BLACK;
}

RGBColor Lambertian::rho(
    const ShadeRec& sr,
    const Vec3& wo) const
{
    return kd * cd;
}
