#ifndef __RT_JITTERED_LIGHT_POINT__
#define __RT_JITTERED_LIGHT_POINT__
#include "../Light.hpp"
#include "../Sampler.hpp"
#include <memory>

namespace RT {
class ShadeRec;
namespace Lights {
    class JitteredPointLight : public Light {
    public:
        JitteredPointLight()
            : _color(Constants::WHITE)
            , _ls(1.0)
            , _origin(Vec3(0.0))
            , _k(0)
            , _radius(0.25)
            , _sampler(nullptr)
            , Light(LightType::JitteredPoint)
        {
        }

        JitteredPointLight(const Vec3 origin)
            : _color(Constants::WHITE)
            , _ls(1.0)
            , _origin(origin)
            , _k(0)
            , _radius(0.25)
            , _sampler(nullptr)
            , Light(LightType::JitteredPoint)
        {
        }

        // Setters ----------------------------------------------------------

        inline void set_scale_radiance(const float& scale) { _ls = scale; }

        /// @brief Power value used in inverse power attenuation law
        inline void set_fall_off_power(const float& value) { _k = value; }

        inline void set_origin(const Vec3& location) { _origin = location; }

        inline void set_radius(const double& r) { _radius = r; }

        inline void set_color(const RGBColor& color) { _color = color; }

        void set_sampler(std::shared_ptr<Sampler> sampler);

        void set_samples(uint32_t samples);

        // Getters ----------------------------------------------------------

        inline Vec3 get_origin() const { return _origin; }

        inline float get_scale_radiance() const { return _ls; }

        inline float get_fall_off_power() const { return _k; }

        inline double get_radius() const { return _radius; }

        inline RGBColor get_color() const { return _color; }

        std::shared_ptr<Sampler>& get_sampler() { return _sampler; }

        /// Light overrides -------------------------------------------------

        Vec3 get_direction(const ShadeRec& sr) override;

        RGBColor L(const ShadeRec& sr) override;

        bool in_shadow(const Ray& ray, const ShadeRec& sr) override;

    private:
        Vec3 _origin;

        /// @brief Stores last sample point for exact shadow tests
        Vec3 _last_sample;

        /// @brief Light intensity
        float _ls;

        /// @brief Inverse square law power
        float _k;

        /// @brief Radius that determines the point
        /// light random direction sources.
        double _radius;
        RGBColor _color;

        std::shared_ptr<Sampler> _sampler;
    };
}

}

#endif