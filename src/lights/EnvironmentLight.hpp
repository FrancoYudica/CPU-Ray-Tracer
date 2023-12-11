#ifndef __RT_ENVIRONMENT_LIGHT__
#define __RT_ENVIRONMENT_LIGHT__
#include "../Light.hpp"
#include "../Material.hpp"
#include "../Sampler.hpp"
#include <memory>

namespace RT {
namespace Lights {
    class EnvironmentLight : public Light {
    public:
        EnvironmentLight()
            : _environment_material(nullptr)
            , Light(LightType::Environment)
        {
        }
        inline void set_material(std::shared_ptr<Material> mtl) { _environment_material = mtl; }
        void set_sampler(std::shared_ptr<Sampler> sampler);
        void set_samples(uint32_t samples);

        inline std::shared_ptr<Material>& get_material() { return _environment_material; }
        inline std::shared_ptr<Sampler>& get_sampler() { return _sampler; }

        bool in_shadow(const Ray& ray, const ShadeRec& sr);
        Vec3 get_direction(const ShadeRec& sr);
        RGBColor L(const ShadeRec& sr);

    private:
        std::shared_ptr<Material> _environment_material;
        std::shared_ptr<Sampler> _sampler;
    };
}
}

#endif