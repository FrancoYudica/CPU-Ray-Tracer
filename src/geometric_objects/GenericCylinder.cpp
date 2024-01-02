#include "GenericCylinder.hpp"

using namespace RT;
using namespace GeometricObjects;

RT::GeometricObjects::GenericCylinder::GenericCylinder(
    double radius,
    double y0,
    double y1)
    : _radius(radius)
    , _y0(y0)
    , _y1(y1)
    , GeometricObject(GeometricObjectType::GenericCylinder)
{
    recalculate_bounding_box();
    disable_bounding_box();
}

bool GenericCylinder::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{

    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double b = 2.0 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
    double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - _radius * _radius;

    double disc = b * b - 4.0 * a * c;
    if (disc < 0)
        return false;

    double disc_sqrt = sqrt(disc);
    double inv_denom = 0.5 / a;

    double t = (-b - disc_sqrt) * inv_denom; // Smaller root
    double y = ray.origin.y + ray.direction.y * t;

    if (t < Constants::k_epsilon || y < _y0 || y > _y1) {
        t = (-b + disc_sqrt) * inv_denom; // Larger root
        y = ray.origin.y + ray.direction.y * t;
    }

    if (t < Constants::k_epsilon || y < _y0 || y > _y1)
        return false;

    tmin = t;

    double x = ray.origin.x + ray.direction.x * t;
    double z = ray.origin.z + ray.direction.z * t;
    record.local_hit_point.x = x;
    record.local_hit_point.y = y;
    record.local_hit_point.z = z;
    record.hit_point = record.local_hit_point;
    Vec3 normal = Vec3(record.local_hit_point.x / _radius, 0.0, record.local_hit_point.z / _radius);
    record.set_normal(normal, get_normal_type());
    record.material = get_material();

    return true;
}

bool GenericCylinder::shadow_hit(const Ray& ray, double& tmin) const
{

    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double b = 2.0 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
    double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - _radius * _radius;

    double disc = b * b - 4.0 * a * c;
    if (disc < 0)
        return false;

    double disc_sqrt = sqrt(disc);
    double inv_denom = 0.5 / a;

    double t = (-b - disc_sqrt) * inv_denom; // Smaller root
    double y = ray.origin.y + ray.direction.y * t;

    if (t < Constants::k_epsilon || y < _y0 || y > _y1) {
        t = (-b + disc_sqrt) * inv_denom; // Larger root
        y = ray.origin.y + ray.direction.y * t;
    }

    tmin = t;
    return t > Constants::k_epsilon && y >= _y0 && y <= _y1;
}

void RT::GeometricObjects::GenericCylinder::recalculate_bounding_box()
{
    set_bounding_box(
        Vec3(-_radius, _y0, -_radius),
        Vec3(_radius, _y1, _radius));
}
