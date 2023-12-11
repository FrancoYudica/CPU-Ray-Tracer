#include "PartSphere.hpp"
#include "../../Constants.hpp"

using namespace RT;
using namespace GeometricObjects;

bool PartSphere::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    double a = Math::dot(ray.direction, ray.direction);
    double b = 2.0 * Math::dot(ray.direction, ray.origin);
    double c = Math::dot(ray.origin, ray.origin) - 1.0;

    double disc = b * b - 4.0 * a * c;

    // No roots -> no intersection
    if (disc < 0)
        return false;

    double e = sqrt(disc);
    double denom = 2.0 * a;

    // Smaller root
    double t = (-b - e) / denom;
    if (t > Constants::k_epsilon) {

        double y = ray.origin.y + t * ray.direction.y;

        // Tests for theta in range
        if (y >= _min_y && y <= _max_y) {
            double x = ray.origin.x + t * ray.direction.x;
            double z = ray.origin.z + t * ray.direction.z;

            // Tests for phi in range
            double phi = Math::atan2_ranged(x, z);
            if (phi >= _min_phi && phi <= _max_phi) {

                // Valid hit at this point
                tmin = t;

                Vec3 normal = (ray.origin + t * ray.direction);
                record.set_normal(normal, get_normal_type());

                record.local_hit_point.x = x;
                record.local_hit_point.y = y;
                record.local_hit_point.z = z;
                record.hit_point = record.local_hit_point;
                record.material = get_material();

                return true;
            }
        }
    }

    // Larger root
    t = (-b + e) / denom;

    if (t > Constants::k_epsilon) {

        double y = ray.origin.y + t * ray.direction.y;

        // Tests for theta in range
        if (y >= _min_y && y <= _max_y) {
            double x = ray.origin.x + t * ray.direction.x;
            double z = ray.origin.z + t * ray.direction.z;

            // Tests for phi in range
            double phi = Math::atan2_ranged(x, z);
            if (phi >= _min_phi && phi <= _max_phi) {

                // Valid hit at this point
                tmin = t;

                Vec3 normal = (ray.origin + t * ray.direction);
                record.set_normal(normal, get_normal_type());
                record.local_hit_point.x = x;
                record.local_hit_point.y = y;
                record.local_hit_point.z = z;
                record.material = get_material();

                return true;
            }
        }
    }

    return false;
}

bool PartSphere::shadow_hit(const Ray& ray, double& tmin) const
{

    double a = Math::dot(ray.direction, ray.direction);
    double b = 2.0 * Math::dot(ray.direction, ray.origin);
    double c = Math::dot(ray.origin, ray.origin) - 1.0;

    double disc = b * b - 4.0 * a * c;

    // No roots -> no intersection
    if (disc < 0)
        return false;

    double e = sqrt(disc);
    double denom = 2.0 * a;

    // Smaller root
    double t = (-b - e) / denom;
    if (t > Constants::k_epsilon) {

        double y = ray.origin.y + t * ray.direction.y;

        // Tests for theta in range
        if (y >= _min_y && y <= _max_y) {
            double x = ray.origin.x + t * ray.direction.x;
            double z = ray.origin.z + t * ray.direction.z;

            // Tests for phi in range
            double phi = Math::atan2_ranged(x, z);
            if (phi >= _min_phi && phi <= _max_phi) {

                // Valid hit at this point
                tmin = t;
                return true;
            }
        }
    }
    // Larger root
    t = (-b + e) / denom;

    if (t > Constants::k_epsilon) {

        double y = ray.origin.y + t * ray.direction.y;

        // Tests for theta in range
        if (y >= _min_y && y <= _max_y) {
            double x = ray.origin.x + t * ray.direction.x;
            double z = ray.origin.z + t * ray.direction.z;

            // Tests for phi in range
            double phi = Math::atan2_ranged(x, z);
            if (phi >= _min_phi && phi <= _max_phi) {

                // Valid hit at this point
                tmin = t;
                return true;
            }
        }
    }

    return false;
}
