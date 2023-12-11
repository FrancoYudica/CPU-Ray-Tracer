#include "Container.hpp"

using namespace RT;
using namespace GeometricObjects;

void Container::add(const GeometricObjectPtr& object)
{
    _objects.push_back(object);
}

bool Container::contains(const GeometricObjectPtr& object) const
{
    return std::find(_objects.begin(), _objects.end(), object) != std::end(_objects);
}

bool Container::remove(const GeometricObjectPtr& object)
{
    auto itr = std::find(_objects.begin(), _objects.end(), object);

    if (itr == std::end(_objects))
        return false;

    _objects.erase(itr);
    return true;
}

void Container::reserve(uint32_t count)
{
    _objects.reserve(count);
}

void Container::clear()
{
    _objects.clear();
}

size_t Container::size()
{
    return _objects.size();
}

bool Container::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{

    double t;

    ShadeRec sr(record.world, ray);

    // Finds nearest ShadeRec
    for (const GeometricObjectPtr& object : _objects) {

        if (!object->is_visible())
            continue;

        // Tests if bounding box fails
        if (object->has_bounding_box() && !object->get_bounding_box().hit(ray))
            continue;

        if (object->hit(ray, t, sr) && t < tmin) {
            tmin = t;
            record = sr;
            record.t = t;
            record.hit_an_object = true;
        }
    }
    return record.hit_an_object;
}

bool Container::shadow_hit(const Ray& ray, double& tmin) const
{
    double t;

    for (const GeometricObjectPtr& object : _objects) {

        // If object doesn't cast shadows
        if (!object->is_visible() || !object->casts_shadows())
            continue;

        // Tests for bounding box fail
        if (object->has_bounding_box() && !object->get_bounding_box().hit(ray))
            continue;

        if (object->shadow_hit(ray, t) && t < tmin) {
            return true;
        }
    }
    return false;
}
