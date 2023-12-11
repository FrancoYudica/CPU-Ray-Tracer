#include "Annulus.hpp"

using namespace RT;
using namespace GeometricObjects;

bool Annulus::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    tmin = Math::dot((_center - ray.origin), _normal) / Math::dot(ray.direction, _normal);

    if (tmin <= Constants::k_epsilon)
        return false;

    Vec3 intersection = ray.at(tmin);

    double length_sqrd = Math::magnitude_squared(intersection - _center);

    // Hits outside
    if (length_sqrd > _outer_radius * _outer_radius || length_sqrd < _inner_radius * _inner_radius)
        return false;

    record.set_normal(_normal, get_normal_type());
    record.local_hit_point = intersection;
    record.hit_point = record.local_hit_point;
    record.material = get_material();
    return true;
}

bool Annulus::shadow_hit(const Ray& ray, double& tmin) const
{

    tmin = Math::dot((_center - ray.origin), _normal) / Math::dot(ray.direction, _normal);

    if (tmin <= Constants::k_epsilon)
        return false;

    Vec3 intersection = ray.at(tmin);

    double length_sqrd = Math::magnitude_squared(intersection - _center);
    return length_sqrd <= _outer_radius * _outer_radius && length_sqrd >= _inner_radius * _inner_radius;
}

Vec3 Annulus::get_normal(const Vec3& p) const
{
    return _normal;
}

Vec3 Annulus::sample_surface() const
{
    constexpr Vec3 jittered_up(0.0072, 1.0, 0.0034);
    Vec3 u = Math::cross(jittered_up, _normal);
    Vec3 v = Math::cross(u, _normal);
    Vec2 xy = _surface_sampler->sample_unit_disk();
    Vec2 sample_dir = Math::normalize(xy);
    Vec2 local_sample = _inner_radius * sample_dir + (_outer_radius - _inner_radius) * xy;
    return _center + local_sample.x * u + local_sample.y * v;
}

void Annulus::set_surface_sampler(std::shared_ptr<Sampler> sampler)
{
    _surface_sampler = sampler;
    _surface_sampler->generate_samples();
    _surface_sampler->setup_shuffled_indices();
    _surface_sampler->map_samples_to_unit_disk();
}
