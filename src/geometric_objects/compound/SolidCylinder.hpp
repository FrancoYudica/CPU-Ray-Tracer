#ifndef __RT_SOLID_CYLINDER__
#define __RT_SOLID_CYLINDER__
#include "../Disk.hpp"
#include "../GenericCylinder.hpp"

#include "Compound.hpp"
namespace RT {
namespace GeometricObjects {

    /// @brief Generic Cylinder combined with 2 disks that fills
    /// the top and bottom gaps
    class SolidCylinder : public Compound {
    public:
        SolidCylinder()
            : Compound(GeometricObjectType::SolidCylinder)
        {
            auto cylinder = std::make_shared<GenericCylinder>();
            auto top_disk = std::make_shared<Disk>(1.0, Vec3(0.0, 1.0, 0.0), Vec3(0.0, 1.0, 0.0));
            auto bot_disk = std::make_shared<Disk>(1.0, Vec3(0.0, -1.0, 0.0), Vec3(0.0, -1.0, 0.0));
            add_object(cylinder);
            add_object(top_disk);
            add_object(bot_disk);
        }
    };
}
}

#endif