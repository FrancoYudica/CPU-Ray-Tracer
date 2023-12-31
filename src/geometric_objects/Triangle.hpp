#ifndef __RT_TRIANGLE__
#define __RT_TRIANGLE__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class Triangle : public GeometricObject {

    public:
        Triangle()
            : Triangle(
                Vec3(0.0, 0.0, 0.0),
                Vec3(1.0, 0.0, 0.5),
                Vec3(1.0, 1.0, 0.5))
        {
        }

        Triangle(
            const Vec3& a,
            const Vec3& b,
            const Vec3& c)
            : _a(a)
            , _b(b)
            , _c(c)
            , GeometricObject(GeometricObjectType::Triangle)
        {
            recalculate_bounding_box();
            disable_bounding_box();
            _update_data();
        }

        inline Vec3 get_a() const { return _a; }
        inline Vec3 get_b() const { return _b; }
        inline Vec3 get_c() const { return _c; }
        inline Vec3 get_normal() const { return _normal; }
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
        void _update_data()
        {
            _ab = _b - _a;
            _ac = _c - _a;
            Vec3 cross_abc = Math::cross(_ab, _ac);
            double cross_magnitude = Math::magnitude(cross_abc);
            _normal = cross_abc / cross_magnitude;

            // Surface area is half the magnitude of the cross product between
            // the vectors b - a, and c - a. It's half the parallelogram area.
            _inv_surface_area = 1.0f / (0.5f * cross_magnitude);
        }

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