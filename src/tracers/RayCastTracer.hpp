#ifndef __RT_RAY_CAST_TRACER__
#define __RT_RAY_CAST_TRACER__

#include "../Constants.hpp"
#include "../ShadeRec.hpp"
#include "../Tracer.hpp"
#include "../World.hpp"

namespace RT {
namespace Tracers {
    class RayCastTracer : public Tracer {
    public:
        RayCastTracer(World& world)
            : Tracer(world, TracerType::RayCast)
        {
        }

        RGBColor trace_ray(
            const Ray& ray,
            const uint32_t depth = 0) const override
        {
            ShadeRec sr = world.hit_objects(ray);

            if (sr.hit_an_object) {
                sr.ray = ray;
                return sr.material->shade(sr);
            }
            return world.background_color;
        }
    };
}
}

#endif