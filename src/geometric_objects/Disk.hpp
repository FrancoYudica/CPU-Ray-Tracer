#ifndef __RT_DISK__
#define __RT_DISK__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class Disk : public GeometricObject {

    public:
        Disk(
            double radius = 1.0,
            const Vec3& center = Vec3(0.0, 1.0, 0.0),
            const Vec3& normal = Vec3(0.0, 1.0, 0.0));

        inline double get_radius() const { return _radius; }
        inline Vec3 get_normal() const { return _normal; }
        inline Vec3 get_center() const { return _center; }

        void set_radius(float r)
        {
            _radius = r;
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
        double _radius;
        Vec3 _normal;
        Vec3 _center;

    private:
        void _recalculate_pdf() { _inv_surface_area = 1.0f / (Constants::PI * _radius * _radius); }
    };

}
}

#endif