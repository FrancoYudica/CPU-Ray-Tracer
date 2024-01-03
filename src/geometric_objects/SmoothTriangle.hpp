#ifndef __RT_TRIANGLE_SMOOTH__
#define __RT_TRIANGLE_SMOOTH__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class SmoothTriangle : public GeometricObject {

    public:
        SmoothTriangle(
            const Vec3& a = Vec3(0.0, 0.0, 0.0),
            const Vec3& b = Vec3(1.0, 0.0, 0.0),
            const Vec3& c = Vec3(1.0, 1.0, 0.0),
            const Vec3& na = Vec3(0.0, 0.0, 1.0),
            const Vec3& nb = Vec3(0.0, 0.0, 1.0),
            const Vec3& nc = Vec3(0.0, 0.0, 1.0));

        inline Vec3 get_a() const { return _a; }
        inline Vec3 get_b() const { return _b; }
        inline Vec3 get_c() const { return _c; }
        inline Vec3 get_na() const { return _na; }
        inline Vec3 get_nb() const { return _nb; }
        inline Vec3 get_nc() const { return _nc; }

        inline void set_a(const Vec3& a) { _a = a; }
        inline void set_b(const Vec3& b) { _b = b; }
        inline void set_c(const Vec3& c) { _c = c; }
        inline void set_na(const Vec3& na) { _na = na; }
        inline void set_nb(const Vec3& nb) { _nb = nb; }
        inline void set_nc(const Vec3& nc) { _nc = nc; }

        // GeometricObject abstract methods implementations ------------------------
        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

        bool shadow_hit(const Ray& ray, double& tmin) const override;

        Vec3 sample_surface() const override;

        void set_surface_sampler(std::shared_ptr<Sampler> sampler) override;

        void recalculate_bounding_box() override;

    private:
        /// @brief Triangle vertices, in counterclockwise order
        Vec3 _a,
            _b,
            _c;

        /// @brief Vertices normals
        Vec3 _na,
            _nb,
            _nc;

        /// @brief Stores side vectors
        Vec3 _ab, _ac;
    };
}
}
#endif