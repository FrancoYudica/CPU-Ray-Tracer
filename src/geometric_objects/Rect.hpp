#ifndef __RT_RECT__
#define __RT_RECT__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class Rect : public GeometricObject {

    public:
        Rect(
            const Vec3& p0 = Vec3(0.0, 0.0, 0.0),
            const Vec3& a = Vec3(0.0, 0.0, -1.0),
            const Vec3& b = Vec3(0.0, 1.0, 0.0));

        /// @brief Sets 'a' and updates length squared
        void set_a(const Vec3& a);

        /// @brief Sets 'b' and updates length squared
        void set_b(const Vec3& b);

        inline void set_p0(const Vec3& p0) { _p0 = p0; }

        inline Vec3 get_a() const { return _a; }
        inline Vec3 get_b() const { return _b; }
        inline Vec3 get_p0() const { return _p0; }
        inline Vec3 get_normal() const { return _normal; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

        bool shadow_hit(const Ray& ray, double& tmin) const override;

        Vec3 get_normal(const Vec3& p) const override;

        Vec3 sample_surface() const override;

        void set_surface_sampler(std::shared_ptr<Sampler> sampler) override;

        void recalculate_bounding_box() override;

    private:
        void _update_data();

    private:
        /// @brief 3D space coordinate. Rectangle origin corner
        Vec3 _p0;

        Vec3 _normal;

        // with 'a' and 'b' directions the plane is defined
        // and with the length of the vectors, 'a' and 'b'
        // we can test if a point is inside the rectangle
        /// @brief Direction and length of plane axis
        Vec3 _a;

        /// @brief Direction and length of plane axis
        Vec3 _b;

    private:
        double _a_len_squared;
        double _b_len_squared;
    };
}
}

#endif