#include "Plane.hpp"
#include "../Constants.hpp"

using namespace RT;
using namespace GeometricObjects;

RT::GeometricObjects::Plane::Plane(
    const Vec3& origin,
    const Vec3& normal)
    : _origin(origin)
    , _normal(normal)
    , GeometricObject(GeometricObjectType::Plane)
{
    disable_bounding_box();
}

bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    double t = Math::dot(_origin - ray.origin, _normal) / Math::dot(ray.direction, _normal);

    if (t > Constants::k_epsilon) {
        tmin = t;
        record.set_normal(_normal, get_normal_type());
        record.local_hit_point = ray.at(t);
        record.hit_point = record.local_hit_point;
        record.material = get_material();
        return true;
    }
    return false;
}

bool Plane::shadow_hit(const Ray& ray, double& tmin) const
{
    tmin = Math::dot(_origin - ray.origin, _normal) / Math::dot(ray.direction, _normal);
    return tmin > Constants::k_epsilon;
}