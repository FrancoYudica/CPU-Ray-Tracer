#include "BoundingVolumeHierachy.hpp"
#include <iostream>

using namespace RT;
using namespace GeometricObjects;
using namespace Impl;

_BVHNode::_BVHNode(
    std::vector<GeometricObjectPtr>& objects,
    uint32_t start,
    uint32_t end)
    : GeometricObject(GeometricObjectType::BoundingVolumeHierarchy)
{

    // 1- Sort object with random criteria
    auto box_compare_x = [](const GeometricObjectPtr& a, const GeometricObjectPtr& b) {
        return a->get_bounding_box().get_min().x < b->get_bounding_box().get_min().x;
    };
    auto box_compare_y = [](const GeometricObjectPtr& a, const GeometricObjectPtr& b) {
        return a->get_bounding_box().get_min().y < b->get_bounding_box().get_min().y;
    };
    auto box_compare_z = [](const GeometricObjectPtr& a, const GeometricObjectPtr& b) {
        return a->get_bounding_box().get_min().z < b->get_bounding_box().get_min().z;
    };

    int sort_axis
        = rand() % 3;

    auto sorting_criteria = sort_axis == 0 ? box_compare_x : (sort_axis == 1 ? box_compare_y : box_compare_z);

    // Sorts by random criteria in range [start, end]
    std::sort(
        objects.begin() + start,
        objects.begin() + end,
        sorting_criteria);

    // 2- Store half of the objects in each node
    uint32_t objects_count = end - start + 1;
    if (objects_count == 1) {
        _is_leaf = true;
        _min_child = _max_child = objects[start];
    } else {
        _is_leaf = false;
        uint32_t middle = (start + end) / 2;
        _min_child = std::make_shared<_BVHNode>(objects, start, middle);
        _max_child = std::make_shared<_BVHNode>(objects, middle + 1, end);
    }

    // 3- Calculates surrounding box
    AABBox min_box = _min_child->get_bounding_box();
    AABBox max_box = _max_child->get_bounding_box();

    AABBox bounding_box = AABBox::get_surrounding(min_box, max_box);
    set_bounding_box(bounding_box);
}

bool _BVHNode::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{

    if (!get_bounding_box().hit(ray))
        return false;

    // Leaf node isn't subclass of BVH
    if (_is_leaf) {

        if (!_min_child->is_visible())
            return false;

        bool did_hit = _min_child->hit(ray, tmin, record);

        if (did_hit)
            record.material = _min_child->get_material();

        return did_hit;
    }

    // Tests intersections with childs and outputs
    // nearest ShadeRecord
    ShadeRec shade_rec_min(record.world, record.ray);
    ShadeRec shade_rec_max(record.world, record.ray);
    double t1 = Constants::k_huge_value;
    double t2 = Constants::k_huge_value;

    bool did_hit_min = _min_child->hit(ray, t1, shade_rec_min);
    bool did_hit_max = _max_child->hit(ray, t2, shade_rec_max);

    if (did_hit_min) {
        tmin = t1;
        record = shade_rec_min;
    }
    if (did_hit_max && t2 < t1) {
        tmin = t2;
        record = shade_rec_max;
    }

    return did_hit_min || did_hit_max;
}

bool _BVHNode::shadow_hit(const Ray& ray, double& tmin) const
{
    if (!get_bounding_box().hit(ray))
        return false;

    // Avoids testing twice
    if (_is_leaf) {

        if (!_min_child->is_visible())
            return false;

        return _min_child->shadow_hit(ray, tmin);
    }
    double t1 = Constants::k_huge_value;
    double t2 = Constants::k_huge_value;

    bool did_hit_min = _min_child->shadow_hit(ray, t1);
    bool did_hit_max = _max_child->shadow_hit(ray, t2);

    tmin = std::min(t1, t2);
    return did_hit_min || did_hit_max;
}

BVH::BVH()
    : Container(GeometricObjectType::BoundingVolumeHierarchy)
{
}

void BVH::add(const GeometricObjectPtr& object)
{
    RT::GeometricObjects::Container::add(object);
    _built = false;
}

bool BVH::remove(const GeometricObjectPtr& object)
{
    bool removed = Container::remove(object);
    if (removed)
        _built = false;
    return removed;
}

void BVH::clear()
{
    Container::clear();
    _built = false;
}

void BVH::build_tree()
{
    _root_node = std::make_shared<_BVHNode>(_objects, 0, _objects.size() - 1);
    _built = true;
}

bool BVH::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    return _root_node->hit(ray, tmin, record);
}

bool BVH::shadow_hit(const Ray& ray, double& tmin) const
{
    return _root_node->shadow_hit(ray, tmin);
}
