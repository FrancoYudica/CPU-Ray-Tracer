#include "Bowl.hpp"

double RT::GeometricObjects::Bowl::get_inner_radius() const
{
    return _annulus->get_inner_radius();
}

double RT::GeometricObjects::Bowl::get_outer_radius() const
{
    return _annulus->get_outer_radius();
}

void RT::GeometricObjects::Bowl::set_inner_radius(double r)
{
    _inner_sphere_instance->set_scale(RT::Vec3(r));
    _annulus->set_inner_radius(r);
}

void RT::GeometricObjects::Bowl::set_outer_radius(double r)
{
    _outer_sphere_instance->set_scale(RT::Vec3(r));
    _annulus->set_outer_radius(r);
}
