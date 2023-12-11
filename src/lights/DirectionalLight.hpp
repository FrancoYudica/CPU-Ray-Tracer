#ifndef __RT_LIGHT_DIRECTIONAL__
#define __RT_LIGHT_DIRECTIONAL__
#include "../Light.hpp"

namespace RT {
namespace Lights {
    class DirectionalLight : public Light {
    public:
        DirectionalLight()
            : color(Constants::WHITE)
            , ls(1.0)
            , direction(Vec3(0.0))
            , Light(LightType::Directional)
        {
        }

        DirectionalLight(const Vec3 origin)
            : color(Constants::WHITE)
            , ls(1.0)
            , direction(origin)
            , Light(LightType::Directional)
        {
        }

        Vec3 get_direction(const ShadeRec& sr) override;
        inline void set_direction(const Vec3& d) { direction = d; }
        RGBColor L(const ShadeRec& sr) override;

        bool in_shadow(const Ray& ray, const ShadeRec& sr) override;

    public:
        Vec3 direction;

        /// @brief Light intensity
        float ls;
        RGBColor color;
    };
}

}

#endif