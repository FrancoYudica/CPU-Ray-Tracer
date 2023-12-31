/**
 * Axis Aligned Bounding Box, used to test ray hit
 */

#ifndef __RT_BOX__
#define __RT_BOX__
#include "../GeometricObject.hpp"
#include "../Sampler.hpp"
#include "../ShadeRec.hpp"

#include <memory>

namespace RT {
namespace GeometricObjects {
    class Box : public GeometricObject {
    public:
        Box(
            const Vec3& min = Vec3(-1.0),
            const Vec3& max = Vec3(1.0))
            : _min(min)
            , _max(max)
            , GeometricObject(GeometricObjectType::Box)
        {
            _recalculate_pdf();
            recalculate_bounding_box();
            disable_bounding_box();
        }

        inline Vec3 get_min() const { return _min; }
        inline Vec3 get_max() const { return _max; }
        void set_min(const Vec3& m) { _min = m; }
        void set_max(const Vec3& m) { _max = m; }

        inline Vec3 get_center() const { return _min + 0.5 * (_max - _min); }
        inline double get_half_dx() const { return 0.5 * (_max.x - _min.x); }
        inline double get_half_dy() const { return 0.5 * (_max.y - _min.y); }
        inline double get_half_dz() const { return 0.5 * (_max.z - _min.z); }

        void set_center(const Vec3& center)
        {
            Vec3 half_size = Vec3(
                get_half_dx(),
                get_half_dy(),
                get_half_dz());

            _min = center - half_size;
            _max = center + half_size;
        }

        void set_half_dx(double dx)
        {
            Vec3 center = get_center();
            _min.x = center.x - dx;
            _max.x = center.x + dx;
        }

        void set_half_dy(double dy)
        {
            Vec3 center = get_center();
            _min.y = center.y - dy;
            _max.y = center.y + dy;
        }

        void set_half_dz(double dz)
        {
            Vec3 center = get_center();
            _min.z = center.z - dz;
            _max.z = center.z + dz;
        }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

        bool shadow_hit(const Ray& ray, double& tmin) const;

        void recalculate_bounding_box() override { set_bounding_box(_min, _max); }

    private:
        Vec3 _min, _max;

    private:
        Vec3 get_normal(const uint32_t& face) const;
        void _recalculate_pdf() { _inv_surface_area = 1.0f / (_max.x - _min.x) * (_max.y - _min.y) * (_max.z - _min.z); }
    };
}
}
#endif