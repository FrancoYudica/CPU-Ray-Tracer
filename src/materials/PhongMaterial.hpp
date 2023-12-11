#ifndef __RT_PHONG_MATERIAL__
#define __RT_PHONG_MATERIAL__
#include "../Material.hpp"
#include "../brdf/GlossySpecular.hpp"
#include "../brdf/Lambertian.hpp"

namespace RT {
namespace Materials {
    class Phong : public Material {
    public:
        Phong()
            : ambient_brdf(std::make_shared<BRDFS::Lambertian>())
            , diffuse_brdf(std::make_shared<BRDFS::Lambertian>())
            , specular_brdf(std::make_shared<BRDFS::GlossySpecularBlinnPhong>())
            , Material(MaterialType::Phong)
        {
        }

        /// @brief Sets ambient reflection coefficient
        inline void set_ka(const float& k) { ambient_brdf->kd = k; }

        /// @brief Sets diffuse reflection coefficient
        inline void set_kd(const float& k) { diffuse_brdf->kd = k; }

        /// @brief Sets specular reflection coefficient
        inline void set_ks(const float& k) { specular_brdf->ks = k; }

        /// @brief Sets specular exponent
        inline void set_specular_exp(const float& exp) { specular_brdf->e = exp; }

        /// @brief Sets diffuse color
        inline void set_ca(const RGBColor& ambient_color) { ambient_brdf->cd = ambient_color; }
        inline void set_cd(const RGBColor& diffuse_color) { diffuse_brdf->cd = diffuse_color; }
        inline void set_cs(const RGBColor& specular_color) { specular_brdf->cs = specular_color; }

        RGBColor shade(const ShadeRec& sr) override;
        RGBColor area_light_shade(const ShadeRec& sr) override;

    public:
        std::shared_ptr<BRDFS::Lambertian> ambient_brdf;
        std::shared_ptr<BRDFS::Lambertian> diffuse_brdf;
        std::shared_ptr<BRDFS::GlossySpecularBlinnPhong> specular_brdf;
    };
}
}

#endif