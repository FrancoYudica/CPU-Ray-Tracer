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
        Bowl(
            const double& inner_radius = 0.5,
            const double& outer_radius = 1.0);

        /// @brief Returns inner radius
        double get_inner_radius() const;

        /// @brief Returns outer radius
        double get_outer_radius() const;

        void set_inner_radius(double);

        void set_outer_radius(double);

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