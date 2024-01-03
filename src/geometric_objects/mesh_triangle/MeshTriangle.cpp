#include "MeshTriangle.hpp"

using namespace RT;
using namespace GeometricObjects;

MeshTriangle::MeshTriangle(
    std::shared_ptr<Mesh> mesh,
    uint32_t index0,
    uint32_t index1,
    uint32_t index2,
    GeometricObjectType type)
    : _mesh(mesh)
    , _index0(index0)
    , _index1(index1)
    , _index2(index2)
    , GeometricObject(type)
{
    Vec3 v0 = _mesh->vertices[_index0];
    Vec3 v1 = _mesh->vertices[_index1];
    Vec3 v2 = _mesh->vertices[_index2];

    _normal = Math::normalize(Math::cross(
        v1 - v0,
        v2 - v0));
}

bool MeshTriangle::shadow_hit(const Ray& ray, double& tmin) const
{
    // Linear system coefficients

    Vec3 v0 = _mesh->vertices[_index0];
    Vec3 v1 = _mesh->vertices[_index1];
    Vec3 v2 = _mesh->vertices[_index2];

    double a = v0.x - v1.x;
    double b = v0.x - v2.x;
    double c = ray.direction.x;
    double d = v0.x - ray.origin.x;

    double e = v0.y - v1.y;
    double f = v0.y - v2.y;
    double g = ray.direction.y;
    double h = v0.y - ray.origin.y;

    double i = v0.z - v1.z;
    double j = v0.z - v2.z;
    double k = ray.direction.z;
    double l = v0.z - ray.origin.z;

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

Vec3 MeshTriangle::get_normal(const Vec3& p) const
{
    return _normal;
}

Vec3 MeshTriangle::sample_surface() const
{
    // Uniform triangle sample
    Vec2 sample = _surface_sampler->sample_unit_square();

    // If this happens, the sample leads a point
    // outside the segment bc
    if (sample.x + sample.y > 1.0) {
        sample.x = 1.0 - sample.x;
        sample.y = 1.0 - sample.y;
    }

    Vec3 v0 = _mesh->vertices[_index0];
    Vec3 v1 = _mesh->vertices[_index1];
    Vec3 v2 = _mesh->vertices[_index2];

    Vec3 v0v1 = v1 - v0;
    Vec3 v0v2 = v2 - v0;

    return v0 + sample.x * v0v1 + sample.y * v0v2;
}

void MeshTriangle::set_surface_sampler(std::shared_ptr<Sampler> sampler)
{
    _surface_sampler = sampler;
    _surface_sampler->generate_samples();
    _surface_sampler->setup_shuffled_indices();
}

void MeshTriangle::recalculate_bounding_box()
{

    Vec3 v0 = _mesh->vertices[_index0];
    Vec3 v1 = _mesh->vertices[_index1];
    Vec3 v2 = _mesh->vertices[_index2];

    Vec3 min(
        std::min(v0.x, std::min(v1.x, v2.x)) - Constants::k_epsilon,
        std::min(v0.y, std::min(v1.y, v2.y)) - Constants::k_epsilon,
        std::min(v0.z, std::min(v1.z, v2.z)) - Constants::k_epsilon);
    Vec3 max(
        std::max(v0.x, std::max(v1.x, v2.x)) + Constants::k_epsilon,
        std::max(v0.y, std::max(v1.y, v2.y)) + Constants::k_epsilon,
        std::max(v0.z, std::max(v1.z, v2.z)) + Constants::k_epsilon);

    set_bounding_box(min, max);
}