#ifndef __RT_AREA_LIGHTING_TRACER__
#define __RT_AREA_LIGHTING_TRACER__

#include "../Constants.hpp"
#include "../ShadeRec.hpp"
#include "../Tracer.hpp"
#include "../World.hpp"

namespace RT {
namespace Tracers {
    class AreaLighting : public Tracer {
    public:
        AreaLighting(World& world)
            : Tracer(world, TracerType::AreaLighting)
        {
        }

        RGBColor trace_ray(
            const Ray& ray,
            const uint32_t depth = 0) const override
        {
            ShadeRec sr = world.hit_objects(ray);

            if (sr.hit_an_object)
                return sr.material->area_light_shade(sr);

            return world.background_color;
        }
    };
}
}

#endif