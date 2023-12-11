#ifndef __RT_PART_TORUS__
#define __RT_PART_TORUS__
#include "../../AABBox.hpp"
#include "../../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class PartTorus : public GeometricObject {
    public:
        PartTorus(
            double min_phi = Constants::PI_OVER_4,
            double max_phi = Constants::PI_2 - Constants::PI_OVER_4,
            double min_theta = Constants::PI_OVER_2,
            double max_theta = Constants::PI_2,
            double a = 2.0,
            double b = 1.0)
            : _a(a)
            , _b(b)
            , _min_phi(min_phi)
            , _max_phi(max_phi)
            , _min_theta(min_theta)
            , _max_theta(max_theta)
            , GeometricObject(GeometricObjectType::PartTorus)
        {
            set_bounding_box(Vec3(-a - b, -b, -a - b), Vec3(a + b, b, a + b));
        }
        inline double get_a() const { return _a; }
        inline double get_b() const { return _b; }
        inline double get_min_phi() const { return _min_phi; }
        inline double get_max_phi() const { return _max_phi; }
        inline double get_min_theta() const { return _min_theta; }
        inline double get_max_theta() const { return _max_theta; }

        inline void set_a(double a) { _a = a; }
        inline void set_b(double b) { _b = b; }
        inline void set_max_phi(double max) { _max_phi = max; }
        inline void set_min_phi(double min) { _min_phi = min; }
        inline void set_max_theta(double max) { _max_theta = max; }
        inline void set_min_theta(double min) { _min_theta = min; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        bool shadow_hit(const Ray& ray, double& tmin) const override;

    private:
        Vec3 _compute_normal(const Vec3& p) const;

    private:
        double _a;
        double _b;

        /// @brief phi is an angle in radians measured in the ZX plane,
        /// and starts from the positive Z axis. Both, max_phi and min_phi
        /// should range in [0, 2*PI]
        double _min_phi, _max_phi;
        double _min_theta, _max_theta;
    };
}
}
#endif