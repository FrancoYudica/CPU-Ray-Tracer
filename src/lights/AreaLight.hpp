#ifndef __RT_AREA_LIGHT__
#define __RT_AREA_LIGHT__
#include "../GeometricObject.hpp"
#include "../Light.hpp"

namespace RT {
class ShadeRec;
namespace Lights {
    class AreaLight : public Light {
    public:
        AreaLight(
            GeometricObjectPtr geometric_object)
            : k(2.0f)
            , Light(LightType::Area)
            , geometry(geometric_object)
            , _wi(Vec3(0.0, 0.0, 0.0))
            , _surface_normal(Vec3(0.0, 0.0, 0.0))
            , _sample_point(Vec3(0.0, 0.0, 0.0))
            , _magnitude(0.0)
        {
        }

        /// @brief Power value used in inverse power attenuation law
        inline void set_fall_off_power(const float& value)
        {
            k = value;
        }

        Vec3 get_direction(const ShadeRec& sr);

        bool in_shadow(const Ray& ray, const ShadeRec& sr) override;

        /// @brief Returns light radiance contribution
        RGBColor L(const ShadeRec& sr) override;

        /// @brief Geometry term of rendering equation, used to
        /// "modify" light radiance based on geometrical properties
        /// note that it's only overwritten by area lights
        float G(const ShadeRec& sr) const override;

        /// @brief Returns light surface area
        float pdf(const ShadeRec& sr) const override;

    public:
        /// @brief Inverse square law power.
        float k;
        GeometricObjectPtr geometry;

    private:
        double _magnitude;
        Vec3 _wi;
        Vec3 _surface_normal;
        Vec3 _sample_point;
    };
}

}

#endif