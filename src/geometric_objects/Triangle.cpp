#include "Triangle.hpp"

using namespace RT;
using namespace GeometricObjects;

bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    // Linear system coefficients
    double a = _a.x - _b.x;
    double b = _a.x - _c.x;
    double c = ray.direction.x;
    double d = _a.x - ray.origin.x;

    double e = _a.y - _b.y;
    double f = _a.y - _c.y;
    double g = ray.direction.y;
    double h = _a.y - ray.origin.y;

    double i = _a.z - _b.z;
    double j = _a.z - _c.z;
    double k = ray.direction.z;
    double l = _a.z - ray.origin.z;

    // Common determinant coefficients, this way
    // half of the total required calculations are made
    double m = f * k - g * j;
    double n = h * k - g * l;
    double p = f * l - h * j;
    double q = g * i - e * k;
    double s = e * j - f * i;

    double inv_D = 1.0 / (a * m + b * q + c * s);

    // Calculates beta
    double beta_determinant = d * m - b * n - c * p;
    double beta = beta_determinant * inv_D;

    if (beta > 1 || beta < 0)
        return false;

    // Calculates gamma
    double r = e * l - h * i;
    double gamma_determinant = a * n + d * q + c * r;
    double gamma = gamma_determinant * inv_D;
    if (gamma < 0 || gamma + beta > 1)
        return false;

    double t_determinant = a * p - b * r + d * s;
    double t = t_determinant * inv_D;

    if (t <= Constants::k_epsilon)
        return false;

    tmin = t;
    record.local_hit_point = ray.at(t);
    record.hit_point = record.local_hit_point;
    record.set_normal(_normal, get_normal_type());
    record.material = get_material();

    return true;
}

bool Triangle::shadow_hit(const Ray& ray, double& tmin) const
{
    // Linear system coefficients
    double a = _a.x - _b.x;
    double b = _a.x - _c.x;
    double c = ray.direction.x;
    double d = _a.x - ray.origin.x;

    double e = _a.y - _b.y;
    double f = _a.y - _c.y;
    double g = ray.direction.y;
    double h = _a.y - ray.origin.y;

    double i = _a.z - _b.z;
    double j = _a.z - _c.z;
    double k = ray.direction.z;
    double l = _a.z - ray.origin.z;

    // Common determinant coefficients
    double m = f * k - g * j;
    double n = h * k - g * l;
    double p = f * l - h * j;
    double q = g * i - e * k;
    double s = e * j - f * i;

    double inv_D = 1.0 / (a * m + b * q + c * s);

    // Calculates beta
    double beta_determinant = d * m - b * n - c * p;
    double beta = beta_determinant * inv_D;

    if (beta > 1 || beta < 0)
        return false;

    // Calculates gamma
    double r = e * l - h * i;
    double gamma_determinant = a * n + d * q + c * r;
    double gamma = gamma_determinant * inv_D;
    if (gamma < 0 || gamma + beta > 1)
        return false;

    double t_determinant = a * p - b * r + d * s;
    double t = t_determinant * inv_D;

    if (t <= Constants::k_epsilon)
        return false;

    tmin = t;
    return true;
}

Vec3 Triangle::get_normal(const Vec3& p) const
{
    return _normal;
}

Vec3 Triangle::sample_surface() const
{
    // Uniform triangle sample
    Vec2 sample = _surface_sampler->sample_unit_square();

    // If this happens, the sample leads a point
    // outside the segment bc
    if (sample.x + sample.y > 1.0) {
        sample.x = 1.0 - sample.x;
        sample.y = 1.0 - sample.y;
    }
    return _a + sample.x * _ab + sample.y + _ac;
}

void Triangle::set_surface_sampler(std::shared_ptr<Sampler> sampler)
{
    _surface_sampler = sampler;
    _surface_sampler->generate_samples();
    _surface_sampler->setup_shuffled_indices();
}

void RT::GeometricObjects::Triangle::recalculate_bounding_box()
{
    Vec3 min(
        std::min(_a.x, std::min(_b.x, _c.x)),
        std::min(_a.y, std::min(_b.y, _c.y)),
        std::min(_a.z, std::min(_b.z, _c.z)));
    Vec3 max(
        std::max(_a.x, std::max(_b.x, _c.x)),
        std::max(_a.y, std::max(_b.y, _c.y)),
        std::max(_a.z, std::max(_b.z, _c.z)));

    set_bounding_box(min, max);
}
