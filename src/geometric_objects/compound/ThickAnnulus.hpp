#ifndef __RT_THICK_ANNULUS__
#define __RT_THICK_ANNULUS__
#include "../GenericCylinder.hpp"
#include "../part_objects/Annulus.hpp"

#include "Compound.hpp"
namespace RT {
namespace GeometricObjects {

    class ThickAnnulus : public Compound {
    public:
        ThickAnnulus(
            double height = 2.0,
            double inner_radius = 0.5,
            double outer_radius = 1.0);

        inline double get_inner_radius() const { return _inner_cylinder->get_radius(); }
        inline double get_outer_radius() const { return _outer_cylinder->get_radius(); }

        void set_inner_radius(float r);
        void set_outer_radius(float r);

    private:
        std::shared_ptr<GenericCylinder> _inner_cylinder;
        std::shared_ptr<GenericCylinder> _outer_cylinder;

        std::shared_ptr<Annulus> _top_annulus;
        std::shared_ptr<Annulus> _bottom_annulus;
    };
}
}

#endif