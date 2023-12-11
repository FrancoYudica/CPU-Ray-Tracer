#include "Sphere.hpp"
#include "../Constants.hpp"

using namespace RT;
using namespace GeometricObjects;

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    Vec3 temp = ray.origin - _center;
    double a = Math::dot(ray.direction, ray.direction);
    double b = 2.0 * Math::dot(ray.direction, temp);
    double c = Math::dot(temp, temp) - _radius * _radius;

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

    tmin = t;
    Vec3 n = (temp + t * ray.direction) / _radius;
    record.set_normal(n, get_normal_type());
    record.local_hit_point = ray.at(t);
    record.hit_point = record.local_hit_point;
    record.material = get_material();
    return true;
}

bool Sphere::shadow_hit(const Ray& ray, double& tmin) const
{

    Vec3 temp = ray.origin - _center;
    double a = Math::dot(ray.direction, ray.direction);
    double b = 2.0 * Math::dot(ray.direction, temp);
    double c = Math::dot(temp, temp) - _radius * _radius;

    double disc = b * b - 4.0 * a * c;

    if (disc < 0)
        return false;

    double e = sqrt(disc);
    double denom = 2.0 * a;

    double t = (-b - e) / denom; // Smaller root
    if (t < Constants::k_epsilon)
        t = (-b + e); // Larger root

    tmin = t;

    // Hit if t is positive
    return t > Constants::k_epsilon;
}
