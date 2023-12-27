#ifndef __RT_INSTANCE__
#define __RT_INSTANCE__
#include "GeometricObject.hpp"
namespace RT {

class Instance : public GeometricObject {
public:
    Instance(const GeometricObjectPtr object)
        : _object(object)
        , _transform(1.0)
        , _inv_transform(1.0)
        , _translation(0.0)
        , _scale(1.0)
        , _rotation(0.0)
        , _transform_the_texture(false)
        , GeometricObject(GeometricObjectType::Instance)
    {
        set_material(object->get_material());
        _recalculate_matrices();
    }

    bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

    bool shadow_hit(const Ray& ray, double& tmin) const override;

    void set_translation(const Vec3& translation);
    void set_scale(const Vec3& scale);
    void set_rotation_x(const double& rotation);
    void set_rotation_y(const double& rotation);
    void set_rotation_z(const double& rotation);
    inline void set_transform_the_texture(bool transform) { _transform_the_texture = transform; }

    inline Vec3 get_translation() const { return _translation; }
    inline Vec3 get_scale() const { return _scale; }
    inline Vec3 get_rotation() const { return _rotation; }
    inline bool get_transform_the_texture() const { return _transform_the_texture; }
    inline GeometricObjectPtr get_object() const { return _object; }

private:
    void _recalculate_matrices();

private:
    GeometricObjectPtr _object;

    Mat4 _transform;
    Mat4 _inv_transform;

    Vec3 _translation;
    Vec3 _scale;
    Vec3 _rotation;

    /// @brief Do we also transform the texture
    bool _transform_the_texture;
};

}

#endif