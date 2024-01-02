#include "ThickAnnulus.hpp"

using namespace RT;
using namespace GeometricObjects;

ThickAnnulus::ThickAnnulus(double height, double inner_radius, double outer_radius)

    : Compound(GeometricObjectType::ThickAnnulus)
{
    enable_bounding_box();

    _inner_cylinder = std::make_shared<GenericCylinder>(
        inner_radius,
        -0.5 * height,
        0.5 * height);

    _inner_cylinder->set_normal_inwards();

    _outer_cylinder = std::make_shared<GenericCylinder>(
        outer_radius,
        -0.5 * height,
        0.5 * height);

    _top_annulus = std::make_shared<Annulus>(
        inner_radius,
        outer_radius,
        Vec3(0.0, 0.5 * height, 0.0),
        Vec3(0.0, 1.0, 0.0));

    _bottom_annulus = std::make_shared<Annulus>(
        inner_radius,
        outer_radius,
        Vec3(0.0, -0.5 * height, 0.0),
        Vec3(0.0, -1.0, 0.0));

    add_object(_inner_cylinder);
    add_object(_outer_cylinder);
    add_object(_top_annulus);
    add_object(_bottom_annulus);
}

void ThickAnnulus::set_inner_radius(float r)
{
    _inner_cylinder->set_radius(r);
    _top_annulus->set_inner_radius(r);
    _bottom_annulus->set_inner_radius(r);
}

void ThickAnnulus::set_outer_radius(float r)
{
    _outer_cylinder->set_radius(r);
    _top_annulus->set_outer_radius(r);
    _bottom_annulus->set_outer_radius(r);
}