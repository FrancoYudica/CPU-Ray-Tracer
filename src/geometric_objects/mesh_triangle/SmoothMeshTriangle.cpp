#include "SmoothMeshTriangle.hpp"

using namespace RT;
using namespace GeometricObjects;

SmoothMeshTriangle::SmoothMeshTriangle(
    std::shared_ptr<Mesh> mesh,
    uint32_t index0,
    uint32_t index1,
    uint32_t index2)
    : MeshTriangle(
        mesh,
        index0,
        index1,
        index2,
        GeometricObjectType::SmoothMeshTriangle)
{
}

bool SmoothMeshTriangle::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{

    Vec3 v0 = _mesh->vertices[_index0];
    Vec3 v1 = _mesh->vertices[_index1];
    Vec3 v2 = _mesh->vertices[_index2];

    // Linear system coefficients
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

    // Interpolates normal with barycentric coordinates
    Vec3 n0 = _mesh->normals[_index0];
    Vec3 n1 = _mesh->normals[_index1];
    Vec3 n2 = _mesh->normals[_index2];
    Vec3 normal = (1 - beta - gamma) * n0 + beta * n1 + gamma * n2;

    record.set_normal(normal, get_normal_type());
    record.material = get_material();

    return true;
}
