#ifndef __RT_GENERIC_CYLINDER__
#define __RT_GENERIC_CYLINDER__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    /// @brief Cylinder with origin in x=0, z=0 and orientation around Y axis
    class GenericCylinder : public GeometricObject {
    public:
        GenericCylinder(
            double radius = 1.0,
            double y0 = -1.0,
            double y1 = 1.0);

        inline double get_radius() const { return _radius; }
        inline double get_y0() const { return _y0; }
        inline double get_y1() const { return _y1; }

        inline void set_radius(double r) { _radius = r; }
        inline void set_y0(double y0) { _y0 = y0; }
        inline void set_y1(double y1) { _y1 = y1; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        bool shadow_hit(const Ray& ray, double& tmin) const override;
        void recalculate_bounding_box() override;

    private:
        double _radius;
        double _y0;
        double _y1;
    };
}
}

#endif