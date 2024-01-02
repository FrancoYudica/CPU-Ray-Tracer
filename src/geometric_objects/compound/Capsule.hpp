#ifndef __RT_CAPSULE__
#define __RT_CAPSULE__
#include "../Disk.hpp"
#include "../GenericCylinder.hpp"
#include "../Sphere.hpp"

#include "Compound.hpp"
namespace RT {
namespace GeometricObjects {

    /// @brief Generic Cylinder combined with 2 spheres that fills
    /// the top and bottom gaps
    class Capsule : public Compound {
    public:
        Capsule(
            double height = 2.0,
            double radius = 1.0);

        inline double get_height() const { return _height; }
        inline double get_radius() const { return _radius; }

        void set_height(const double& h);

        void set_radius(const double& r);

    private:
        std::shared_ptr<Sphere> _top_sphere;
        std::shared_ptr<Sphere> _bottom_sphere;
        std::shared_ptr<GenericCylinder> _cylinder;
        double _height;
        double _radius;
    };
}
}

#endif