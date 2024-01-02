#include "PartCylinder.hpp"
#include <iostream>

using namespace RT;
using namespace GeometricObjects;

PartCylinder::PartCylinder(
    double min_phi,
    double max_phi,
    double radius,
    double y0,
    double y1)
    : _radius(radius)
    , _y0(y0)
    , _y1(y1)
    , _min_phi(min_phi)
    , _max_phi(max_phi)
    , GeometricObject(GeometricObjectType::PartCylinder)
{
    recalculate_bounding_box();
    disable_bounding_box();
    set_normal_flip();
}

bool PartCylinder::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{

    // Quadratic equation coefficients
    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double b = 2.0 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
    double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - _radius * _radius;

    double disc = b * b - 4.0 * a * c;

    // No intersection
    if (disc < 0)
        return false;

    double disc_sqrt = sqrt(disc);
    double inv_denom = 0.5 / a;

    // Nearest root
    double t = (-b - disc_sqrt) * inv_denom;

    double y = ray.origin.y + ray.direction.y * t;

    // Positive and 'y' in range [y0, y1]
    if (t > Constants::k_epsilon && y > _y0 && y < _y1) {

        double x = ray.origin.x + ray.direction.x * t;
        double z = ray.origin.z + ray.direction.z * t;

        double phi = Math::atan2_ranged(x, z);
        if (phi >= _min_phi && phi <= _max_phi) {
            tmin = t;

            record.local_hit_point.x = x;
            record.local_hit_point.y = y;
            record.local_hit_point.z = z;
            record.hit_point = record.local_hit_point;
            Vec3 normal = Vec3(record.local_hit_point.x / _radius, 0.0, record.local_hit_point.z / _radius);
            record.set_normal(normal, get_normal_type());
            record.material = get_material();
            return true;
        }
    }

    t = (-b + disc_sqrt) * inv_denom;
    y = ray.origin.y + ray.direction.y * t;

    if (t > Constants::k_epsilon && y > _y0 && y < _y1) {

        double x = ray.origin.x + ray.direction.x * t;
        double z = ray.origin.z + ray.direction.z * t;

        double phi = Math::atan2_ranged(x, z);
        if (phi >= _min_phi && phi <= _max_phi) {
            tmin = t;

            record.local_hit_point.x = x;
            record.local_hit_point.y = y;
            record.local_hit_point.z = z;
            Vec3 normal = Vec3(record.local_hit_point.x / _radius, 0.0, record.local_hit_point.z / _radius);
            record.set_normal(normal, get_normal_type());
            record.material = get_material();
            return true;
        }
    }
    return false;
}

bool PartCylinder::shadow_hit(const Ray& ray, double& tmin) const
{

    // Quadratic equation coefficients
    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double b = 2.0 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
    double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - _radius * _radius;

    double disc = b * b - 4.0 * a * c;

    // No intersection
    if (disc < 0)
        return false;

    double disc_sqrt = sqrt(disc);
    double inv_denom = 0.5 / a;

    // Nearest root
    double t = (-b - disc_sqrt) * inv_denom;

    double y = ray.origin.y + ray.direction.y * t;

    // Positive and 'y' in range [y0, y1]
    if (t > Constants::k_epsilon && y > _y0 && y < _y1) {

        double x = ray.origin.x + ray.direction.x * t;
        double z = ray.origin.z + ray.direction.z * t;

        double phi = Math::atan2_ranged(x, z);
        if (phi >= _min_phi && phi <= _max_phi) {
            tmin = t;
            return true;
        }
    }

    t = (-b + disc_sqrt) * inv_denom;
    y = ray.origin.y + ray.direction.y * t;

    if (t > Constants::k_epsilon && y > _y0 && y < _y1) {

        double x = ray.origin.x + ray.direction.x * t;
        double z = ray.origin.z + ray.direction.z * t;

        double phi = Math::atan2_ranged(x, z);
        if (phi >= _min_phi && phi <= _max_phi) {
            tmin = t;
            return true;
        }
    }
    return false;
}

void RT::GeometricObjects::PartCylinder::recalculate_bounding_box()
{
    set_bounding_box(
        Vec3(-_radius, _y0, -_radius),
        Vec3(_radius, _y1, _radius));
}
