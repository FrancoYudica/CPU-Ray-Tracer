#ifndef __RT_ANNULUS__
#define __RT_ANNULUS__
#include "../../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class Annulus : public GeometricObject {

    public:
        Annulus(
            double inner_radius,
            double outer_radius,
            const Vec3& center,
            const Vec3& normal)
            : _inner_radius(inner_radius)
            , _outer_radius(outer_radius)
            , _center(center)
            , _normal(normal)
            , GeometricObject(GeometricObjectType::Annulus)
        {
            _recalculate_pdf();
            recalculate_bounding_box();
            disable_bounding_box();
        }

        Annulus()
            : Annulus(
                0.5,
                1.0,
                Vec3(0.0, 1.0, 0.0),
                Vec3(0.0, 1.0, 0.0))
        {
        }

        inline double get_inner_radius() const { return _inner_radius; }
        inline double get_outer_radius() const { return _outer_radius; }
        inline Vec3 get_normal() const { return _normal; }
        inline Vec3 get_center() const { return _center; }

        void set_inner_radius(float r)
        {
            _inner_radius = r;
            _recalculate_pdf();
        }

        void set_outer_radius(float r)
        {
            _outer_radius = r;
            _recalculate_pdf();
        }

        inline void set_center(const Vec3& c) { _center = c; }
        inline void set_normal(const Vec3& n) { _normal = n; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

        bool shadow_hit(const Ray& ray, double& tmin) const override;

        Vec3 get_normal(const Vec3& p) const override;

        Vec3 sample_surface() const override;

        void set_surface_sampler(std::shared_ptr<Sampler> sampler) override;

        void recalculate_bounding_box() override;

    private:
        double _inner_radius;
        double _outer_radius;
        Vec3 _normal;
        Vec3 _center;

    private:
        void _recalculate_pdf()
        {
            double inner_area = Constants::PI * _inner_radius * _inner_radius;
            double outer_area = Constants::PI * _outer_radius * _outer_radius;
            double annulus_area = outer_area - inner_area;
            _inv_surface_area = 1.0f / annulus_area;
        }
    };

}
}

#endif