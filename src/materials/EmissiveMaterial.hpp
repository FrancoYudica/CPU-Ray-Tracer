#ifndef __RT_EMISSIVE_MATERIAL__
#define __RT_EMISSIVE_MATERIAL__
#include "../Material.hpp"
#include "../brdf/Lambertian.hpp"

namespace RT {
namespace Materials {
    class Emissive : public Material {
    public:
        Emissive()
            : color(Constants::WHITE)
            , ls(1.0f)
            , Material(MaterialType::Emissive)
        {
        }

        /// @brief Sets diffuse reflection coefficient
        inline void scale_radiance(const float& k) { ls = k; }

        /// @brief Sets emission color
        inline void set_ce(const RGBColor& emission_color) { color = emission_color; }

        RGBColor shade(const ShadeRec& sr) override;

        RGBColor area_light_shade(const ShadeRec& sr) override;

        RGBColor get_Le() const override;

    public:
        RGBColor color;
        float ls;
    };
}
}

#endif