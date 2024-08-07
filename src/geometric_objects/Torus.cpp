#include "Torus.hpp"
#include "../math_RT.hpp"

using namespace RT;
using namespace GeometricObjects;

RT::GeometricObjects::Torus::Torus(double a, double b)
    : _a(a)
    , _b(b)
    , GeometricObject(GeometricObjectType::Torus)
{
    recalculate_bounding_box();
    enable_bounding_box();
}
bool Torus::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    double x1 = ray.origin.x;
    double y1 = ray.origin.y;
    double z1 = ray.origin.z;
    double d1 = ray.direction.x;
    double d2 = ray.direction.y;
    double d3 = ray.direction.z;

    double coeffs[5];
    double roots[4];

    // define the coefficients
    double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
    double e = x1 * x1 + y1 * y1 + z1 * z1 - _a * _a - _b * _b;
    double f = x1 * d1 + y1 * d2 + z1 * d3;
    double four_a_sqrd = 4.0 * _a * _a;
    coeffs[0] = e * e - four_a_sqrd * (_b * _b - y1 * y1);
    // constant term
    coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
    coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
    coeffs[3] = 4.0 * sum_d_sqrd * f;
    coeffs[4] = sum_d_sqrd * sum_d_sqrd;
    // coefficient of t^4
    // find the roots
    int num_real_roots = Math::solve_quartic(coeffs, roots);

    if (num_real_roots == 0)
        return false;

    bool intersected = false;
    double t = Constants::k_huge_value;

    // Finds nearest intersection
    for (int j = 0; j < num_real_roots; j++) {
        if (roots[j] > Constants::k_epsilon) {
            intersected = true;
            if (roots[j] < t)
                t = roots[j];
        }
    }

    if (!intersected)
        return false;

    tmin = t;
    record.local_hit_point = ray.at(t);
    record.hit_point = record.local_hit_point;
    record.set_normal(_compute_normal(record.local_hit_point), get_normal_type());
    record.material = get_material();

    return true;
}

bool Torus::shadow_hit(const Ray& ray, double& tmin) const
{
    double x1 = ray.origin.x;
    double y1 = ray.origin.y;
    double z1 = ray.origin.z;
    double d1 = ray.direction.x;
    double d2 = ray.direction.y;
    double d3 = ray.direction.z;

    double coeffs[5];
    double roots[4];

    // define the coefficients
    double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
    double e = x1 * x1 + y1 * y1 + z1 * z1 - _a * _a - _b * _b;
    double f = x1 * d1 + y1 * d2 + z1 * d3;
    double four_a_sqrd = 4.0 * _a * _a;
    coeffs[0] = e * e - four_a_sqrd * (_b * _b - y1 * y1);
    // constant term
    coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
    coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
    coeffs[3] = 4.0 * sum_d_sqrd * f;
    coeffs[4] = sum_d_sqrd * sum_d_sqrd;
    // coefficient of t^4
    // find the roots
    int num_real_roots = Math::solve_quartic(coeffs, roots);
    if (num_real_roots == 0)
        return false;

    tmin = Constants::k_huge_value;

    // Finds nearest intersection
    for (int j = 0; j < num_real_roots; j++) {
        if (roots[j] > Constants::k_epsilon && roots[j] < tmin) {
            tmin = roots[j];
        }
    }

    return true;
}

void RT::GeometricObjects::Torus::recalculate_bounding_box()
{
    double extra_box_gap = 2.0 * Constants::k_epsilon;
    set_bounding_box(Vec3(-_a - _b, -_b - extra_box_gap, -_a - _b), Vec3(_a + _b, _b + extra_box_gap, _a + _b));
}

Vec3 Torus::_compute_normal(const Vec3& p) const
{
    double v = Math::dot(p, p) - (_a * _a + _b * _b);
    Vec3 normal(
        4.0 * p.x * v,
        4.0 * p.y * (v + 2.0 * _a * _a),
        4.0 * p.z * v);

    return Math::normalize(normal);
}
