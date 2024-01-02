#ifndef __RT_TRIANGLE__
#define __RT_TRIANGLE__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class Triangle : public GeometricObject {

    public:
        Triangle(
            const Vec3& a = Vec3(0.0, 0.0, 0.0),
            const Vec3& b = Vec3(1.0, 0.0, 0.5),
            const Vec3& c = Vec3(1.0, 1.0, 0.5));

        inline Vec3
        get_a() const
        {
            return _a;
        }
        inline Vec3 get_b() const
        {
            return _b;
        }
        inline Vec3 get_c() const
        {
            return _c;
        }
        inline Vec3 get_normal() const
        {
            return _normal;
        }
        void set_a(const Vec3& a)
        {
            _a = a;
            _update_data();
        }
        void set_b(const Vec3& b)
        {
            _b = b;
            _update_data();
        }
        void set_c(const Vec3& c)
        {
            _c = c;
            _update_data();
        }

        // GeometricObject abstract methods implementations ------------------------
        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

        bool shadow_hit(const Ray& ray, double& tmin) const override;

        Vec3 get_normal(const Vec3& p) const override;

        Vec3 sample_surface() const override;

        void set_surface_sampler(std::shared_ptr<Sampler> sampler) override;

        void recalculate_bounding_box() override;

    private:
        /// @brief Updates lateral segments, normal and inverse area
        void _update_data();

    private:
        /// @brief Triangle vertices, in counterclockwise order
        Vec3 _a,
            _b,
            _c;

        /// @brief Stores side vectors
        Vec3 _ab, _ac;

        Vec3 _normal;
    };
}
}
#endif