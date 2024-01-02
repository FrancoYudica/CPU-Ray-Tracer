#ifndef __RT_SOLID_CONE_
#define __RT_SOLID_CONE_
#include "../Cone.hpp"
#include "../Disk.hpp"

#include "Compound.hpp"
namespace RT {
namespace GeometricObjects {

    /// @brief Cone with a Disk in the XZ plane
    class SolidCone : public Compound {
    public:
        SolidCone(
            double height = 2.0,
            double radius = 1.0);
        void set_radius(const double& r);
        void set_height(const double& h);
        inline double get_radius() const { return _cone->get_radius(); }
        inline double get_height() const { return _cone->get_height(); }

    private:
        std::shared_ptr<Cone> _cone;
        std::shared_ptr<Disk> _disk;
    };
}
}

#endif