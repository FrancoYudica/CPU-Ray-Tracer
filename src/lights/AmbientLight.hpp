#ifndef __RT_LIGHT_AMBIENT__
#define __RT_LIGHT_AMBIENT__
#include "../Light.hpp"

namespace RT {
namespace Lights {
    class AmbientLight : public Light {
    public:
        AmbientLight()
            : color(Constants::WHITE)
            , ls(1.0f)
            , Light(LightType::Ambient)
        {
        }

        inline void scale_radiance(float l) { ls = l; }

        Vec3 get_direction(const ShadeRec& sr) override
        {
            return Vec3(0.0f);
        }

        RGBColor L(const ShadeRec& sr) override
        {
            return ls * color;
        }

        bool in_shadow(const Ray& ray, const ShadeRec& sr) override { return false; }

    public:
        /// @brief Light intensity
        float ls;
        RGBColor color;
    };
}

}

#endif