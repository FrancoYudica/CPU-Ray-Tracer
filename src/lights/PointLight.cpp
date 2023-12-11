#include "PointLight.hpp"
#include "../ShadeRec.hpp"
#include "../Tracer.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Lights;

Vec3 PointLight::get_direction(const ShadeRec& sr)
{
    return Math::normalize(origin - sr.hit_point);
}

RGBColor PointLight::L(const ShadeRec& sr)
{
    float attenuation = ls / std::pow(Math::magnitude(sr.hit_point - origin), k);
    return attenuation * color;
}

bool PointLight::in_shadow(
    const Ray& ray,
    const ShadeRec& sr)
{
    // Ray direction isn't facing the normal
    Vec3 to_light = origin - sr.hit_point;
    float distance = Math::magnitude(to_light);
    to_light /= distance;

    // When surface hemisphere isn't facing light direct
    // illumination can't reach that surface point
    if (Math::dot(sr.get_normal(), to_light) < 0.0f)
        return false;

    return sr.world->in_shadow(ray, distance);
}
