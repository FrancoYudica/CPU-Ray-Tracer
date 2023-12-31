#ifndef __RT_PLANE__
#define __RT_PLANE__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class Plane : public GeometricObject {

    public:
        Plane(
            const Vec3& origin = Vec3(0.0, 0.0, 0.0),
            const Vec3& normal = Vec3(0.0, 1.0, 0.0));

        void set_normal(const Vec3& normal) { this->_normal = normal; }
        void set_origin(const Vec3& origin) { this->_origin = origin; }
        Vec3 get_normal() const { return _normal; }
        Vec3 get_origin() const { return _origin; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        bool shadow_hit(const Ray& ray, double& tmin) const override;

    private:
        Vec3 _origin, _normal;
    };
}
}

#endif