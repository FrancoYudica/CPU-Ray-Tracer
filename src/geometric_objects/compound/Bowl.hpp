#ifndef __RT_BOWL__
#define __RT_BOWL__
#include "../../Instance.hpp"
#include "../part_objects/Annulus.hpp"
#include "../part_objects/PartSphere.hpp"
#include "Compound.hpp"

namespace RT {
namespace GeometricObjects {
    class Bowl : public Compound {
    public:
        Bowl()
            : Bowl(0.5, 1.0)
        {
        }

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

            _outer_sphere = std::make_shared<PartSphere>(
                0.0,
                Constants::PI_2,
                Constants::PI_OVER_2,
                Constants::PI);

            _inner_sphere_instance = std::make_shared<Instance>(_inner_sphere);
            _outer_sphere_instance = std::make_shared<Instance>(_outer_sphere);

            _inner_sphere_instance->set_scale(Vec3(inner_radius));
            _outer_sphere_instance->set_scale(Vec3(outer_radius));

            _annulus = std::make_shared<Annulus>(
                inner_radius,
                outer_radius,
                Vec3(0.0, 0.0, 0.0),
                Vec3(0.0, 1.0, 0.0));

            _inner_sphere->set_normal_inwards();

            add_object(_annulus);
            add_object(_inner_sphere_instance);
            add_object(_outer_sphere_instance);
        }

    private:
        std::shared_ptr<PartSphere> _inner_sphere;
        std::shared_ptr<PartSphere> _outer_sphere;
        std::shared_ptr<Instance> _outer_sphere_instance;
        std::shared_ptr<Instance> _inner_sphere_instance;
        std::shared_ptr<Annulus> _annulus;
    };
}
}

#endif