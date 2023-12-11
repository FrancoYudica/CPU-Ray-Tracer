#include "Rect.hpp"

using namespace RT;
using namespace GeometricObjects;

bool Rect::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    double t = Math::dot((_p0 - ray.origin), _normal) / Math::dot(ray.direction, _normal);

    if (t <= Constants::k_epsilon)
        return false;

    // Plane intersection point
    Vec3 p = ray.at(t);

    Vec3 d = p - _p0;

    // Tests if the projection on 'a' axis is smaller than the length of a
    double d_dot_a = Math::dot(d, _a);
    if (d_dot_a < 0.0 || d_dot_a > _a_len_squared)
        return false;

    // Tests if the projection on 'b' axis is smaller than the length of b
    double d_dot_b = Math::dot(d, _b);
    if (d_dot_b < 0.0 || d_dot_b > _b_len_squared)
        return false;

    tmin = t;
    record.set_normal(_normal, get_normal_type());
    record.local_hit_point = p;
    record.hit_point = record.local_hit_point;
    record.material = get_material();

    return true;
}

bool Rect::shadow_hit(const Ray& ray, double& tmin) const
{
    double t = Math::dot((_p0 - ray.origin), _normal) / Math::dot(ray.direction, _normal);

    if (t <= Constants::k_epsilon)
        return false;

    // Plane intersection point
    Vec3 p = ray.at(t);

    Vec3 d = p - _p0;

    // Tests if the projection on 'a' axis is smaller than the length of a
    double d_dot_a = Math::dot(d, _a);
    if (d_dot_a < 0.0 || d_dot_a > _a_len_squared)
        return false;

    // Tests if the projection on 'b' axis is smaller than the length of b
    double d_dot_b = Math::dot(d, _b);
    if (d_dot_b < 0.0 || d_dot_b > _b_len_squared)
        return false;

    tmin = t;
    return true;
}

Vec3 Rect::get_normal(const Vec3& p) const
{
    return _normal;
}

Vec3 Rect::sample_surface() const
{
    Vec2 sample = _surface_sampler->sample_unit_square();
    return _p0 + _a * sample.x + _b * sample.y;
}

void Rect::set_surface_sampler(std::shared_ptr<Sampler> sampler)
{
    _surface_sampler = sampler;
    _surface_sampler->generate_samples();
    _surface_sampler->setup_shuffled_indices();
}
