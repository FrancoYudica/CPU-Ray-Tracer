#ifndef __RT_PLASTIC_MATERIAL__
#define __RT_PLASTIC_MATERIAL__
#include "../Material.hpp"
#include "../brdf/GlossySpecular.hpp"
#include "../brdf/Lambertian.hpp"
#include <memory>

namespace RT {
namespace Materials {
    class Plastic : public Material {

    public:
        Plastic()
            : ambient_brdf(std::make_shared<BRDFS::Lambertian>())
            , diffuse_brdf(std::make_shared<BRDFS::Lambertian>())
            , specular_brdf(std::make_shared<BRDFS::GlossySpecularBlinnPhong>())
            , Material(MaterialType::Plastic)
        {
        }

        inline void set_ambient(std::shared_ptr<BRDF> ambient) { ambient_brdf = ambient; }
        inline void set_diffuse(std::shared_ptr<BRDF> diffuse) { diffuse_brdf = diffuse; }
        inline void set_specular(std::shared_ptr<BRDF> specular) { specular_brdf = specular; }

        RGBColor shade(const ShadeRec& sr) override;
        RGBColor area_light_shade(const ShadeRec& sr) override;

    public:
        std::shared_ptr<BRDF> ambient_brdf;
        std::shared_ptr<BRDF> diffuse_brdf;
        std::shared_ptr<BRDF> specular_brdf;
    };
}
}

#endif