#ifndef __RT_NORMAL_TRACER__
#define __RT_NORMAL_TRACER__

#include "../ShadeRec.hpp"
#include "../Tracer.hpp"
#include "../World.hpp"
#include <math.h>

namespace RT {
namespace Tracers {
    class NormalTracer : public Tracer {
        // Shades with normals
    public:
        NormalTracer(World& world)
            : Tracer(world, TracerType::Normal)
        {
        }

        RGBColor trace_ray(
            const Ray& ray,
            const uint32_t depth = 0) const override
        {
            ShadeRec record = world.hit_objects(ray);

            if (record.hit_an_object)
                return (record.get_normal() + 1.0) / 2.0;

            return RGBColor(0.0f);
        }

    public:
        double max_distance;
    };
}
}

#endif