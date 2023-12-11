#ifndef __RT_LIGHT_POINT__
#define __RT_LIGHT_POINT__
#include "../Light.hpp"

namespace RT {
class ShadeRec;
namespace Lights {
    class PointLight : public Light {
    public:
        PointLight()
            : color(Constants::WHITE)
            , ls(1.0)
            , origin(Vec3(0.0))
            , k(0)
            , Light(LightType::Point)
        {
        }

        PointLight(const Vec3 origin)
            : color(Constants::WHITE)
            , ls(1.0)
            , origin(origin)
            , k(0)
            , Light(LightType::Point)
        {
        }

        inline void scale_radiance(const float& scale) { ls = scale; }

        /// @brief Power value used in inverse power attenuation law
        inline void set_fall_off_power(const float& value) { k = value; }

        inline void set_location(const Vec3& location) { origin = location; }

        Vec3 get_direction(const ShadeRec& sr);

        RGBColor L(const ShadeRec& sr) override;

        bool in_shadow(const Ray& ray, const ShadeRec& sr) override;

    public:
        Vec3 origin;

        /// @brief Light intensity
        float ls;

        /// @brief Inverse square law power
        float k;
        RGBColor color;
    };
}

}

#endif