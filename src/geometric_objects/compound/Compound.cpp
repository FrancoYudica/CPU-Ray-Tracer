#include "Compound.hpp"
#include <iostream>

using namespace RT;
using namespace GeometricObjects;

void Compound::add_object(const GeometricObjectPtr object)
{
    _objects.push_back(object);

    // Sets compound material
    object->set_material(get_material());

    if (!object->has_bounding_box())
        return;

    // Sets / Combines bounding boxes
    if (!has_bounding_box())
        set_bounding_box(object->get_bounding_box());
    else
        set_bounding_box(AABBox::get_surrounding(get_bounding_box(), object->get_bounding_box()));
}

void Compound::set_material(const std::shared_ptr<Material>& mtl)
{
    GeometricObject::set_material(mtl);
    for (auto& object : _objects) {
        object->set_material(mtl);
    }
}

bool Compound::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    tmin = Constants::k_huge_value;
    double t;
    ShadeRec sr(record.world, ray);

    // Finds nearest hit and updates record
    for (auto& object : _objects) {

        // Tests for bounding box fail
        if (object->has_bounding_box() && !object->get_bounding_box().hit(ray))
            continue;

        bool did_hit = object->hit(ray, t, sr);

        if (did_hit && t < tmin) {
            tmin = t;
            record.hit_an_object = true;
            record.material = object->get_material();
            record.set_normal(sr.get_normal(), get_normal_type());
            record.local_hit_point = sr.local_hit_point;
            record.hit_point = sr.hit_point;
        }
    }

    return record.hit_an_object;
}

bool Compound::shadow_hit(const Ray& ray, double& tmin) const
{
    tmin = Constants::k_huge_value;
    double t;
    bool hit_any = false;

    // Finds nearest hit and updates tmin
    for (auto& object : _objects) {

        // If object doesn't cast shadows
        if (!object->shadows)
            continue;

        // Tests for bounding box fail
        if (object->has_bounding_box() && !object->get_bounding_box().hit(ray))
            continue;

        if (object->shadow_hit(ray, t) && t < tmin) {
            // Smaller tmin found
            hit_any = true;
            tmin = t;
        }
    }

    return hit_any;
}
