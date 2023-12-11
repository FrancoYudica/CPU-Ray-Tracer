#ifndef __SPHERE__
#define __SPHERE__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class Sphere : public GeometricObject {

    public:
        Sphere(
            const Vec3& center = Vec3(0.0, 0.0, 0.0),
            const double radius = 1.0)
            : _center(center)
            , _radius(radius)
            , GeometricObject(GeometricObjectType::Sphere)
        {
            _recalculate_bbox();
        }
        void set_radius(const float& r)
        {
            _radius = r;
            _recalculate_bbox();
        }
        inline void set_center(const Vec3& c)
        {
            _center = c;
            _recalculate_bbox();
        }
        inline float get_radius() const { return _radius; }
        inline Vec3 get_center() const { return _center; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        bool shadow_hit(const Ray& ray, double& tmin) const override;

    private:
        void _recalculate_bbox()
        {
            set_bounding_box(
                Vec3(_center.x - _radius, _center.y - _radius, _center.z - _radius),
                Vec3(_center.x + _radius, _center.y + _radius, _center.z + _radius));
        }

        Vec3 _center;
        double _radius;
    };
}
}

#endif