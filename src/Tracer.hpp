#ifndef __RT_TRACER__
#define __RT_TRACER__
#include "Constants.hpp"
#include "Ray.hpp"
#include "Types_rt.hpp"
#include <memory>

namespace RT {

class World;
enum class TracerType {
    RayCast,
    Depth,
    Normal,
    AreaLighting
};
class Tracer {
public:
    Tracer(World& world, TracerType tracer_type)
        : world(world)
        , _tracer_type(tracer_type)
    {
    }

    virtual RGBColor trace_ray(const Ray& ray, const uint32_t depth = 0) const
    {
        return Constants::BLACK;
    }
    virtual RGBColor trace_ray(const Ray& ray, float& min, const uint32_t depth) const
    {
        return Constants::BLACK;
    }
    TracerType get_type()
    {
        return _tracer_type;
    }

protected:
    World& world;

private:
    TracerType _tracer_type;
};
} // namespace RT

#endif