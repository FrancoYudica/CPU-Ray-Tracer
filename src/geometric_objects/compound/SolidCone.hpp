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
            double radius = 1.0)
            : Compound(GeometricObjectType::SolidCone)
        {
            _cone = std::make_shared<Cone>(height, radius);
            _disk = std::make_shared<Disk>(radius, Vec3(0.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0));

            add_object(_cone);
            add_object(_disk);
            set_bounding_box(
                Vec3(-radius, 0.0, -radius),
                Vec3(radius, height, radius));
        }
        void set_radius(const double& r)
        {
            _cone->set_radius(r);
            _disk->set_radius(r);
            set_bounding_box(
                Vec3(-r, 0.0, -r),
                Vec3(r, _cone->get_height(), r));
        }
        void set_height(const double& h)
        {
            _cone->set_height(h);

            double r = _cone->get_radius();
            set_bounding_box(
                Vec3(-r, 0.0, -r),
                Vec3(r, h, r));
        }
        inline double get_radius() const { return _cone->get_radius(); }
        inline double get_height() const { return _cone->get_height(); }

    private:
        std::shared_ptr<Cone> _cone;
        std::shared_ptr<Disk> _disk;
    };
}
}

#endif