#ifndef __DEPTH_TRACER__
#define __DEPTH_TRACER__

#include "../ShadeRec.hpp"
#include "../Tracer.hpp"
#include "../World.hpp"
#include <math.h>

namespace RT {
namespace Tracers {
    class DepthTracer : public Tracer {
        // Returns colors based on the depth
    public:
        DepthTracer(World& world)
            : Tracer(world, TracerType::Depth)
            , max_distance(100.0f)
        {
        }

        RGBColor trace_ray(
            const Ray& ray,
            const uint32_t depth = 0) const override
        {
            ShadeRec record = world.hit_objects(ray);

            if (record.hit_an_object)
                return RGBColor(1.0f - record.t / max_distance);

            return RGBColor(0.0f);
        }

    public:
        double max_distance;
    };
}
}

#endif