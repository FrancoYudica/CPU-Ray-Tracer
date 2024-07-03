#ifndef __RT_LIGHT__
#define __RT_LIGHT__
#include "Constants.hpp"
#include "math_RT.hpp"

namespace RT {
class ShadeRec;
class Ray;
enum class LightType {
    Ambient,
    Directional,
    Point,
    AmbientOccluder,
    Area,
    Environment,
    JitteredPoint,
    JitteredDirectional
};
class Light {
public:
    Light(LightType type)
        : shadows(true)
        , _type(type)
    {
    }

    inline LightType get_type() const { return _type; }
    inline bool casts_shadows() const { return shadows; }
    inline void set_casts_shadows(bool casts) { shadows = casts; }
    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) = 0;
    /// @brief Direction towards light
    virtual Vec3 get_direction(const ShadeRec& sr) = 0;

    /// @brief Returns light radiance contribution
    virtual RGBColor L(const ShadeRec& sr) = 0;

    /// @brief Geometry term of rendering equation, used to
    /// "modify" light radiance based on geometrical properties
    /// note that it's only overwritten by area lights
    virtual float G(const ShadeRec& sr) const { return 1.0f; }

    /// @brief Returns light surface area
    virtual float pdf(const ShadeRec& sr) const { return 1.0f; }

public:
    bool shadows;

private:
    LightType _type;
};
}

#endif