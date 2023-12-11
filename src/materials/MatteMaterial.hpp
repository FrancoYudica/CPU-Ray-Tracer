#ifndef __RT_MATTE_MATERIAL__
#define __RT_MATTE_MATERIAL__
#include "../Material.hpp"
#include "../brdf/Lambertian.hpp"

namespace RT {
namespace Materials {
    class Matte : public Material {
    public:
        Matte()
            : ambient_brdf(std::make_shared<BRDFS::Lambertian>())
            , diffuse_brdf(std::make_shared<BRDFS::Lambertian>())
            , Material(MaterialType::Matte)
        {
        }

        /// @brief Sets ambient reflection coefficient
        inline void set_ka(const float& k) { ambient_brdf->kd = k; }

        /// @brief Sets diffuse reflection coefficient
        inline void set_kd(const float& k) { diffuse_brdf->kd = k; }

        /// @brief Sets diffuse color
        inline void set_cd(const RGBColor& diffuse_color) { diffuse_brdf->cd = diffuse_color; }

        /// @brief Sets ambient color
        inline void set_ca(const RGBColor& ambient_color) { ambient_brdf->cd = ambient_color; }

        RGBColor shade(const ShadeRec& sr) override;

        RGBColor area_light_shade(const ShadeRec& sr) override;

    public:
        std::shared_ptr<BRDFS::Lambertian> ambient_brdf;
        std::shared_ptr<BRDFS::Lambertian> diffuse_brdf;
    };
}
}

#endif