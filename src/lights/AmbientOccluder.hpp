#ifndef __RT_AMBIENT_OCCLUDER__
#define __RT_AMBIENT_OCCLUDER__
#include "../Light.hpp"
#include "../Sampler.hpp"
#include "../samplers/MultiJitteredSampler.hpp"
#include <memory>

namespace RT {
namespace Lights {
    /// @brief Ambient Occlusion is implemented in light
    /// call to L(ShadeRec&). Requires Sampler to sample
    /// in intersection normal hemisphere.
    class AmbientOccluder : public Light {
    public:
        AmbientOccluder()
            : min_intensity(0.0f)
            , ls(1.0f)
            , color(Constants::WHITE)
            , Light(LightType::AmbientOccluder)
            , sampler(nullptr)
        {
            shadows = true;
        }

        inline void set_min_intensity(float i) { min_intensity = i; }
        inline void scale_radiance(float l) { ls = l; }
        inline void set_color(const RGBColor& c) { color = c; }

        void set_sampler(std::shared_ptr<Sampler> sampler);

        void set_samples(uint32_t samples);

        bool in_shadow(const Ray& ray, const ShadeRec& sr) override;

        Vec3 get_direction(const ShadeRec& sr) override;

        RGBColor L(const ShadeRec& sr) override;

    public:
        /// @brief Intensity of radiance when ray is occluded
        float min_intensity;

        /// @brief Sampler used to sample hemisphere
        std::shared_ptr<Sampler> sampler;
        RGBColor color;
        float ls;

    private:
        Vec3 u, v, w;
    };
}
}

#endif
