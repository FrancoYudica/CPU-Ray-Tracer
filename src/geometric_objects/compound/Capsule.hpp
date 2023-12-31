#ifndef __RT_CAPSULE__
#define __RT_CAPSULE__
#include "../Disk.hpp"
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
            double radius = 1.0)
            : _height(height)
            , _radius(radius)
            , Compound(GeometricObjectType::Capsule)
        {
            _cylinder = std::make_shared<GenericCylinder>(
                radius,
                -0.5 * height,
                0.5 * height);

            _top_sphere = std::make_shared<Sphere>(Vec3(0.0, 0.5 * height, 0.0), radius);
            _bottom_sphere = std::make_shared<Sphere>(Vec3(0.0, -0.5 * height, 0.0), radius);
            add_object(_cylinder);
            add_object(_top_sphere);
            add_object(_bottom_sphere);
        }

        inline double get_height() const { return _height; }
        inline double get_radius() const { return _radius; }

        void set_height(const double& h)
        {
            _height = h;

            Vec3 top_center = _top_sphere->get_center();
            top_center.y = 0.5 * _height;
            _top_sphere->set_center(top_center);

            Vec3 bottom_center = _bottom_sphere->get_center();
            bottom_center.y = -0.5 * _height;
            _bottom_sphere->set_center(bottom_center);

            _cylinder->set_y0(-0.5 * _height);
            _cylinder->set_y1(+0.5 * _height);
        }

        void set_radius(const double& r)
        {
            _radius = r;
            _top_sphere->set_radius(r);
            _bottom_sphere->set_radius(r);
            _cylinder->set_radius(r);
        }

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