#include "AreaLight.hpp"
#include "../World.hpp"

using namespace RT;

Vec3 Lights::AreaLight::get_direction(const ShadeRec& sr)
{
    _sample_point = geometry->sample_surface();
    _surface_normal = geometry->get_normal(_sample_point);
    _wi = _sample_point - sr.hit_point;
    _magnitude = Math::magnitude(_wi);
    _wi /= _magnitude; // Normalization
    return _wi;
}

bool Lights::AreaLight::in_shadow(const Ray& ray, const ShadeRec& sr)
{
    // k_2_epsilon is used, since shadow rays offset k_epsilon along the normal
    // therefore, subtracting 2 * k_epsilon stops shadow check ignoring
    // AreaLight geometry
    return sr.world->in_shadow(ray, _magnitude - Constants::k_2_epsilon);
}

RGBColor Lights::AreaLight::L(const ShadeRec& sr)
{
    float n_dot_wi = Math::dot(-_surface_normal, _wi);

    if (n_dot_wi > 0.0f)
        return geometry->get_material()->get_Le();

    return Constants::BLACK;
}

float Lights::AreaLight::G(const ShadeRec& sr) const
{
    return Math::dot(-_surface_normal, _wi) / powf(_magnitude, k);
}

float Lights::AreaLight::pdf(const ShadeRec& sr) const
{
    return geometry->pdf(sr);
}
