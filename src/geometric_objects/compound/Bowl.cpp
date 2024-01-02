#include "Bowl.hpp"

using namespace RT;
using namespace GeometricObjects;

Bowl::Bowl(const double& inner_radius, const double& outer_radius)

    : Compound(GeometricObjectType::Bowl)
{
    enable_bounding_box();

    _inner_sphere = std::make_shared<PartSphere>(
        0.0,
        Constants::PI_2,
        Constants::PI_OVER_2,
        Constants::PI);

    _outer_sphere = std::make_shared<PartSphere>(
        0.0,
        Constants::PI_2,
        Constants::PI_OVER_2,
        Constants::PI);

    _inner_sphere_instance = std::make_shared<Instance>(_inner_sphere);
    _outer_sphere_instance = std::make_shared<Instance>(_outer_sphere);

    _inner_sphere_instance->set_scale(Vec3(inner_radius));
    _outer_sphere_instance->set_scale(Vec3(outer_radius));

    _annulus = std::make_shared<Annulus>(
        inner_radius,
        outer_radius,
        Vec3(0.0, 0.0, 0.0),
        Vec3(0.0, 1.0, 0.0));

    _inner_sphere->set_normal_inwards();

    add_object(_annulus);
    add_object(_inner_sphere_instance);
    add_object(_outer_sphere_instance);
}
double Bowl::get_inner_radius() const
{
    return _annulus->get_inner_radius();
}

double Bowl::get_outer_radius() const
{
    return _annulus->get_outer_radius();
}

void Bowl::set_inner_radius(double r)
{
    _inner_sphere_instance->set_scale(RT::Vec3(r));
    _annulus->set_inner_radius(r);
}

void Bowl::set_outer_radius(double r)
{
    _outer_sphere_instance->set_scale(RT::Vec3(r));
    _annulus->set_outer_radius(r);
}
