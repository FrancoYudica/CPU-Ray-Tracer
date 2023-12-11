#ifndef __RT_JITTERED_LIGHT_DIRECTIONAL__
#define __RT_JITTERED_LIGHT_DIRECTIONAL__
#include "../Light.hpp"
#include "../Sampler.hpp"
#include <memory>

namespace RT {
namespace Lights {
    class JitteredDirectionalLight : public Light {
    public:
        JitteredDirectionalLight()
            : _color(Constants::WHITE)
            , _ls(1.0)
            , _direction(Vec3(0.0))
            , _theta(Constants::PI_OVER_4)
            , _sampler(nullptr)
            , Light(LightType::JitteredDirectional)
        {
        }

        JitteredDirectionalLight(const Vec3 direction)
            : _color(Constants::WHITE)
            , _ls(1.0)
            , _direction(direction)
            , _theta(Constants::PI_OVER_4)
            , _sampler(nullptr)
            , Light(LightType::Directional)
        {
        }

        // Setters ----------------------------------------------------------

        inline void set_scale_radiance(const float& scale) { _ls = scale; }

        inline void set_direction(const Vec3& direction) { _direction = direction; }

        inline void set_theta(const double& t) { _theta = t; }

        inline void set_color(const RGBColor& color) { _color = color; }

        void set_sampler(std::shared_ptr<Sampler> sampler);

        void set_samples(uint32_t samples);

        // Getters ----------------------------------------------------------

        inline Vec3 get_direction() const { return _direction; }

        inline float get_scale_radiance() const { return _ls; }

        inline double get_theta() const { return _theta; }

        inline RGBColor get_color() const { return _color; }

        std::shared_ptr<Sampler>& get_sampler() { return _sampler; }

        /// Light overrides -------------------------------------------------

        Vec3 get_direction(const ShadeRec& sr) override;

        RGBColor L(const ShadeRec& sr) override;

        bool in_shadow(const Ray& ray, const ShadeRec& sr) override;

    private:
        Vec3 _direction;

        /// @brief Stores last sample point for exact shadow tests
        Vec3 _last_sample;

        /// @brief Light intensity
        float _ls;

        /// @brief Angle that measures the amount
        /// of randomness along the direction of the ray
        double _theta;
        RGBColor _color;

        std::shared_ptr<Sampler> _sampler;
    };
}

}

#endif