#ifndef __RT_BOWL__
#define __RT_BOWL__
#include "../part_objects/Annulus.hpp"
#include "../part_objects/PartSphere.hpp"
#include "Compound.hpp"

namespace RT {
namespace GeometricObjects {
    class Bowl : public Compound {
    public:
        Bowl(
            const double& inner_radius,
            const double& outer_radius)
            : Compound(GeometricObjectType::Bowl)
        {
            _inner_sphere = std::make_shared<PartSphere>(
                0.0,
                Constants::PI_2,
                Constants::PI_OVER_2,
                Constants::PI);

            /// @todo: Add bowl after implementing 'Affine transformations',
            /// since it's required to have two PartSphere of different
            /// radius, but radius can't be modified in PartSphere.
        }

    private:
        std::shared_ptr<PartSphere> _inner_sphere;
        std::shared_ptr<PartSphere> _outer_sphere;
        std::shared_ptr<Annulus> _annulus;
    };
}
}

#endif