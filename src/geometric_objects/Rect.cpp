#include "Rect.hpp"

using namespace RT;
using namespace GeometricObjects;

Rect::Rect(
    const Vec3& p0,
    const Vec3& a,
    const Vec3& b)
    : _p0(p0)
    , _a(a)
    , _b(b)
    , GeometricObject(GeometricObjectType::Rect)
{
    _a_len_squared = Math::magnitude_squared(a);
    _b_len_squared = Math::magnitude_squared(b);
    _update_data();
    recalculate_bounding_box();
    disable_bounding_box();
    set_normal_flip();
}

void Rect::set_a(const Vec3& a)
{
    _a = a;
    _a_len_squared = Math::magnitude_squared(_a);
    _update_data();
}

void Rect::set_b(const Vec3& b)
{
    _b = b;
    _b_len_squared = Math::magnitude_squared(_b);
    _update_data();
}
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

void RT::GeometricObjects::Rect::recalculate_bounding_box()
{
    Vec3 points[4] = {
        _p0,
        _p0 + _a,
        _p0 + _b,
        _p0 + _a + _b
    };

    Vec3 min(Constants::k_huge_value);
    Vec3 max(-Constants::k_huge_value);

    for (int8_t i = 0; i < 4; i++) {
        Vec3 p = points[i];
        min = Vec3(
            std::min(min.x, p.x),
            std::min(min.y, p.y),
            std::min(min.z, p.z));
        max = Vec3(
            std::max(max.x, p.x),
            std::max(max.y, p.y),
            std::max(max.z, p.z));
    }

    Vec3 eps(Constants::k_epsilon);
    set_bounding_box(min - eps, max + eps);
}

void RT::GeometricObjects::Rect::_update_data()
{
    _inv_surface_area = 1.0f / Math::magnitude(Math::cross(_a, _b));
    _normal = Math::normalize(Math::cross(_a, _b));
}