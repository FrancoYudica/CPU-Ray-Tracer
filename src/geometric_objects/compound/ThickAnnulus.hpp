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
            double outer_radius = 1.0)
            : Compound(GeometricObjectType::ThickAnnulus)
        {
            _inner_cylinder = std::make_shared<GenericCylinder>(
                inner_radius,
                -0.5 * height,
                0.5 * height);

            _inner_cylinder->set_normal_inwards();

            _outer_cylinder = std::make_shared<GenericCylinder>(
                outer_radius,
                -0.5 * height,
                0.5 * height);

            _top_annulus = std::make_shared<Annulus>(
                inner_radius,
                outer_radius,
                Vec3(0.0, 0.5 * height, 0.0),
                Vec3(0.0, 1.0, 0.0));

            _bottom_annulus = std::make_shared<Annulus>(
                inner_radius,
                outer_radius,
                Vec3(0.0, -0.5 * height, 0.0),
                Vec3(0.0, -1.0, 0.0));

            add_object(_inner_cylinder);
            add_object(_outer_cylinder);
            add_object(_top_annulus);
            add_object(_bottom_annulus);

            _recalculate_bbox();
        }

        inline double get_inner_radius() const { return _inner_cylinder->get_radius(); }
        inline double get_outer_radius() const { return _outer_cylinder->get_radius(); }

        void set_inner_radius(float r)
        {
            _inner_cylinder->set_radius(r);
            _top_annulus->set_inner_radius(r);
            _bottom_annulus->set_inner_radius(r);
            _recalculate_bbox();
        }

        void set_outer_radius(float r)
        {
            _outer_cylinder->set_radius(r);
            _top_annulus->set_outer_radius(r);
            _bottom_annulus->set_outer_radius(r);
            _recalculate_bbox();
        }

    private:
        void _recalculate_bbox()
        {
            double outer_radius = _outer_cylinder->get_radius();
            double height = _outer_cylinder->get_y1() - _outer_cylinder->get_y0();
            set_bounding_box(
                Vec3(-outer_radius, -height * 0.5, -outer_radius),
                Vec3(outer_radius, height * 0.5, outer_radius));
        }

    private:
        std::shared_ptr<GenericCylinder> _inner_cylinder;
        std::shared_ptr<GenericCylinder> _outer_cylinder;

        std::shared_ptr<Annulus> _top_annulus;
        std::shared_ptr<Annulus> _bottom_annulus;
    };
}
}

#endif