#include "Instance.hpp"
#include "Material.hpp"
#include "glm/gtx/transform.hpp"
#include "Math_rt.hpp"

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

    // Recalculates bounding box
    if (_object->has_bounding_box()) {
        AABBox object_bbox = _object->get_bounding_box();
        set_bounding_box(
            _transform * Vec4(object_bbox.get_min(), 1.0),
            _transform * Vec4(object_bbox.get_max(), 1.0));
    }
}
