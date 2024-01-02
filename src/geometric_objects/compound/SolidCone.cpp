#include "SolidCone.hpp"

using namespace RT;
using namespace GeometricObjects;

SolidCone::SolidCone(double height, double radius)

    : Compound(GeometricObjectType::SolidCone)
{
    enable_bounding_box();

    _cone = std::make_shared<Cone>(height, radius);
    _disk = std::make_shared<Disk>(radius, Vec3(0.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0));

    add_object(_cone);
    add_object(_disk);
}

void SolidCone::set_radius(const double& r)
{
    _cone->set_radius(r);
    _disk->set_radius(r);
}

void SolidCone::set_height(const double& h)
{
    _cone->set_height(h);
}