#include "Cone.hpp"
#include "../Constants.hpp"

using namespace RT;
using namespace GeometricObjects;

bool Cone::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    double h_r_squared = _height_over_radius * _height_over_radius;
    double y_minus_height = ray.origin.y - _height;

    double a = h_r_squared * (ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z) - ray.direction.y * ray.direction.y;
    double b = 2.0 * (h_r_squared * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z) - y_minus_height * ray.direction.y);
    double c = h_r_squared * (ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z) - y_minus_height * y_minus_height;
    double disc = b * b - 4.0 * a * c;

    if (disc < 0)
        return false;

    double e = sqrt(disc);
    double denom = 2.0 * a;

    double t = (-b - e) / denom; // Smaller root
    if (t < Constants::k_epsilon)
        t = (-b + e); // Larger root

    // If 2 negative roots
    if (t < Constants::k_epsilon)
        return false;

    // Tests for height valid interval
    double y = ray.origin.y + t * ray.direction.y;
    if (y < 0.0 || y > _height)
        return false;

    record.local_hit_point.x = ray.origin.x + t * ray.direction.x;
    record.local_hit_point.y = y;
    record.local_hit_point.z = ray.origin.z + t * ray.direction.z;

    Vec3 normal = _compute_normal(record.local_hit_point);
    record.set_normal(normal, get_normal_type());
    record.material = get_material();
    record.hit_point = record.local_hit_point;

    tmin = t;
    return true;
}

bool Cone::shadow_hit(const Ray& ray, double& tmin) const
{
    double h_r_squared = _height_over_radius * _height_over_radius;
    double y_minus_height = ray.origin.y - _height;

    double a = h_r_squared * (ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z) - ray.direction.y * ray.direction.y;
    double b = 2.0 * (h_r_squared * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z) - y_minus_height * ray.direction.y);
    double c = h_r_squared * (ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z) - y_minus_height * y_minus_height;
    double disc = b * b - 4.0 * a * c;

    if (disc < 0)
        return false;

    double e = sqrt(disc);
    double denom = 2.0 * a;

    double t = (-b - e) / denom; // Smaller root
    if (t < Constants::k_epsilon)
        t = (-b + e); // Larger root

    // No valid roots
    if (t < Constants::k_epsilon)
        return false;

    tmin = t;
    double y = ray.origin.y + t * ray.direction.y;
    // Hit if Y in valid range [0, height]
    return y >= 0.0 && y <= _height;
}

void RT::GeometricObjects::Cone::recalculate_bounding_box()
{
    set_bounding_box(
        Vec3(-_radius, 0, -_radius),
        Vec3(_radius, _height, _radius));
}

Vec3 Cone::_compute_normal(const Vec3& p) const
{
    return Math::normalize(Vec3(
        _height_over_radius * p.x,
        _height - p.y,
        _height_over_radius * p.z));
}
