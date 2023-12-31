#include "Instance.hpp"
#include "Material.hpp"
#include "Math_rt.hpp"
#include "glm/gtx/transform.hpp"

using namespace RT;

bool Instance::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    Ray transformed_ray;
    transformed_ray.origin = Vec3(_inv_transform * Vec4(ray.origin, 1.0));

    // Note that ray direction isn't normalized, this is necessary since we
    // are applying scaling
    transformed_ray.direction = Vec3(_inv_transform * Vec4(ray.direction, 0.0));

    if (_object->hit(transformed_ray, tmin, record)) {

        Vec3 local_n = record.get_normal();
        Vec3 n = Math::normalize(Vec3(Math::transpose(_inv_transform) * Vec4(local_n, 0.0)));
        record.set_normal(n, NormalType::Outwards);
        record.ray = ray;

        if (!_transform_the_texture) {
            record.local_hit_point = ray.at(tmin);
            record.hit_point = record.local_hit_point;
        }

        // Updates material, in case the instance is of type Compound.
        // in this case, different materials can be passed through the
        // record.
        if (record.material)
            material = record.material;

        return true;
    }

    return false;
}

bool Instance::shadow_hit(const Ray& ray, double& tmin) const
{

    Ray transformed_ray;
    transformed_ray.origin = Vec3(_inv_transform * Vec4(ray.origin, 1.0));
    transformed_ray.direction = Vec3(_inv_transform * Vec4(ray.direction, 0.0));

    return _object->shadow_hit(transformed_ray, tmin);
}

void RT::Instance::recalculate_bounding_box()
{
    _object->recalculate_bounding_box();
    // Recalculates bounding box
    if (!_object->has_bounding_box())
        return;

    AABBox object_bbox = _object->get_bounding_box();

    Vec3 box_min = object_bbox.get_min();
    Vec3 box_max = object_bbox.get_max();

    // When there is no rotation, only translation and scale
    if (RT::Math::magnitude(_rotation) == 0) {
        set_bounding_box(
            _transform * Vec4(box_min, 1.0),
            _transform * Vec4(box_max, 1.0));
        return;
    }

    // Instance is rotated, and bounding box is calculated by
    // taking the max and min transformed vertices of instance
    // bounding box
    Vec3 transformed_max(std::numeric_limits<double>::lowest());
    Vec3 transformed_min(Constants::k_huge_value);

    // Triple for loop, to test all the Box edges
    for (uint8_t x_axis = 0; x_axis <= 1; x_axis++) {
        for (uint8_t y_axis = 0; y_axis <= 1; y_axis++) {
            for (uint8_t z_axis = 0; z_axis <= 1; z_axis++) {

                // Values range from 0 to 1, so only one of the edges is picked
                double x = (1 - x_axis) * box_min.x + x_axis * box_max.x;
                double y = (1 - y_axis) * box_min.y + y_axis * box_max.y;
                double z = (1 - z_axis) * box_min.z + z_axis * box_max.z;

                Vec3 corner(x, y, z);
                Vec3 corner_transformed(_transform * Vec4(corner, 1.0));

                // Updates min and max
                for (uint8_t axis = 0; axis < 3; axis++) {
                    transformed_min[axis] = std::min(corner_transformed[axis], transformed_min[axis]);
                    transformed_max[axis] = std::max(corner_transformed[axis], transformed_max[axis]);
                }
            }
        }
    }

    set_bounding_box(transformed_min, transformed_max);
}

void Instance::set_translation(const Vec3& translation)
{
    _translation = translation;
    _recalculate_matrices();
}

void Instance::set_scale(const Vec3& scale)
{
    _scale = scale;
    _recalculate_matrices();
}

void Instance::set_rotation_x(const double& rotation)
{
    _rotation.x = rotation;
    _recalculate_matrices();
}

void Instance::set_rotation_y(const double& rotation)
{
    _rotation.y = rotation;
    _recalculate_matrices();
}

void Instance::set_rotation_z(const double& rotation)
{
    _rotation.z = rotation;
    _recalculate_matrices();
}

void Instance::_recalculate_matrices()
{
    // Recalculates matrices
    _transform = Mat4(1.0);
    _transform = glm::translate(_transform, _translation);
    _transform = glm::rotate(_transform, _rotation.x, Vec3(1.0, 0.0, 0.0));
    _transform = glm::rotate(_transform, _rotation.y, Vec3(0.0, 1.0, 0.0));
    _transform = glm::rotate(_transform, _rotation.z, Vec3(0.0, 0.0, 1.0));
    _transform = glm::scale(_transform, _scale);
    _inv_transform = glm::inverse(_transform);

    recalculate_bounding_box();
}
