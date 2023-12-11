#include "EmissiveMaterial.hpp"
#include "../ShadeRec.hpp"

using namespace RT;

RGBColor Materials::Emissive::shade(const ShadeRec& sr)
{
    return Constants::PINK;
}
RGBColor Materials::Emissive::area_light_shade(const ShadeRec& sr)
{
    if (Math::dot(sr.ray.direction, -sr.get_normal()) > 0.0)
        return ls * color;
    return Constants::BLACK;
}

RGBColor Materials::Emissive::get_Le() const
{
    return ls * color;
}