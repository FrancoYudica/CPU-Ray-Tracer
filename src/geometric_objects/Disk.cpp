#include "Disk.hpp"
#include "../Ray.hpp"

using namespace RT;
using namespace GeometricObjects;

bool Disk::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    double t = Math::dot((_center - ray.origin), _normal) / Math::dot(ray.direction, _normal);

    if (t <= Constants::k_epsilon)
        return false;

    Vec3 intersection = ray.at(t);

    double length_sqrd = Math::magnitude_squared(intersection - _center);

    if (length_sqrd > _radius * _radius)
        return false;

    tmin = t;
    record.set_normal(_normal, get_normal_type());
    record.local_hit_point = intersection;
    record.hit_point = record.local_hit_point;
    record.material = get_material();

    return true;
}

bool Disk::shadow_hit(const Ray& ray, double& tmin) const
{
    double t = Math::dot((_center - ray.origin), _normal) / Math::dot(ray.direction, _normal);

    if (t <= Constants::k_epsilon)
        return false;

    Vec3 intersection = ray.at(t);

    double length_sqrd = Math::magnitude_squared(intersection - _center);

    tmin = t;
    return length_sqrd <= _radius * _radius;
}

Vec3 Disk::get_normal(const Vec3& p) const
{
    return _normal;
}

Vec3 Disk::sample_surface() const
{
    constexpr Vec3 jittered_up(0.0072, 1.0, 0.0034);
    Vec3 u = cross(jittered_up, _normal);
    Vec3 v = cross(u, _normal);
    Vec2 sample = _radius * _surface_sampler->sample_unit_disk();
    return _center + sample.x * u + sample.y * v;
}

void Disk::set_surface_sampler(std::shared_ptr<Sampler> sampler)
{
    _surface_sampler = sampler;
    _surface_sampler->generate_samples();
    _surface_sampler->setup_shuffled_indices();
    _surface_sampler->map_samples_to_unit_disk();
}
