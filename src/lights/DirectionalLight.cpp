#include "DirectionalLight.hpp"
#include "../Ray.hpp"
#include "../ShadeRec.hpp"
#include "../Tracer.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Lights;

bool DirectionalLight::in_shadow(
    const Ray& ray,
    const ShadeRec& sr)
{

    // When surface hemisphere isn't facing light direct
    // illumination can't reach that surface point
    if (Math::dot(sr.get_normal(), -direction) < 0.0f)
        return false;

    return sr.world->in_shadow(ray, Constants::k_huge_value);
}

Vec3 DirectionalLight::get_direction(const ShadeRec& sr)
{
    return -direction;
}

RGBColor DirectionalLight::L(const ShadeRec& sr)
{
    return ls * color;
}