#ifndef __RT_PART_CYLINDER__
#define __RT_PART_CYLINDER__

#include "../../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {

    /// @brief Cylinder with origin in x=0, z=0 and orientation around Y axis
    /// also, normals are automatically flipped inside hit when necessary
    class PartCylinder : public GeometricObject {
    public:
        PartCylinder(
            double min_phi = Constants::PI_OVER_4,
            double max_phi = Constants::PI_2 - Constants::PI_OVER_4,
            double radius = 1.0,
            double y0 = -1.0,
            double y1 = 1.0)
            : _radius(radius)
            , _y0(y0)
            , _y1(y1)
            , _min_phi(min_phi)
            , _max_phi(max_phi)
            , GeometricObject(GeometricObjectType::PartCylinder)
        {
            recalculate_bounding_box();
            disable_bounding_box();
            set_normal_flip();
        }

        inline double get_radius() const { return _radius; }
        inline double get_y0() const { return _y0; }
        inline double get_y1() const { return _y1; }
        inline double get_min_phi() const { return _min_phi; }
        inline double get_max_phi() const { return _max_phi; }

        inline void set_radius(double r) { _radius = r; }
        inline void set_y0(double y0) { _y0 = y0; }
        inline void set_y1(double y1) { _y1 = y1; }
        inline void set_max_phi(double max) { _max_phi = max; }
        inline void set_min_phi(double min) { _min_phi = min; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        bool shadow_hit(const Ray& ray, double& tmin) const override;
        void recalculate_bounding_box() override;

    private:
        double _radius;
        double _y0;
        double _y1;

        /// @brief phi is an angle in radians measured in the ZX plane,
        /// and starts from the positive Z axis. Both, max_phi and min_phi
        /// should range in [0, 2*PI]
        double _max_phi, _min_phi;
    };
}
}

#endif