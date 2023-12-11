#ifndef __RT_TORUS__
#define __RT_TORUS__
#include "../AABBox.hpp"
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class Torus : public GeometricObject {
    public:
        Torus(double a = 2.0, double b = 1.0)
            : _a(a)
            , _b(b)
            , GeometricObject(GeometricObjectType::Torus)
        {
            double extra_box_gap = 2.0 * Constants::k_epsilon;
            set_bounding_box(Vec3(-a - b, -b - extra_box_gap, -a - b), Vec3(a + b, b + extra_box_gap, a + b));

        }
        inline double get_a() const { return _a; }
        inline double get_b() const { return _b; }

        inline void set_a(double a) { _a = a; }
        inline void set_b(double b) { _b = b; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        bool shadow_hit(const Ray& ray, double& tmin) const override;

    private:
        Vec3 _compute_normal(const Vec3& p) const;

    private:
        double _a;
        double _b;
    };
}
}
#endif