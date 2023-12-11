#ifndef __RT_MATERIAL__
#define __RT_MATERIAL__
#include "Constants.hpp"

namespace RT {
class ShadeRec;

enum class MaterialType {
    Matte,
    Phong,
    Plastic,
    Emissive
};

class Material {
public:
    Material(MaterialType type)
        : _type(type)
    {
    }

    inline MaterialType get_type() const { return _type; }

    /// @return Emissive light component
    virtual RGBColor get_Le() const { return Constants::BLACK; }

    virtual RGBColor shade(const ShadeRec& sr) { return Constants::BLACK; }
    virtual RGBColor whitted_shade(const ShadeRec& sr) { return Constants::BLACK; }
    virtual RGBColor area_light_shade(const ShadeRec& sr) { return Constants::BLACK; }
    virtual RGBColor path_shade(const ShadeRec& sr) { return Constants::BLACK; }

private:
    MaterialType _type;
};
}

#endif