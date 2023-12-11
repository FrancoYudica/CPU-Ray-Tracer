#include "OrthographicCamera.hpp"
#include "../Ray.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Cameras;

void OrthographicCamera::render_scene(
    const World& world,
    const uint32_t row_offset,
    const uint32_t column_offset)
{

    // References to world data
    const ViewPlane& view_plane = world.view_plane;
    const std::shared_ptr<Tracer>& tracer = world.tracer;

    RGBColor pixel_color;
    Ray ray;
    ray.direction = -w;
    Vec2 pixel;

    // Zoom modifies the pixel size
    double pixel_size = view_plane.pixel_size / zoom;

    for (uint32_t row = 0; row < world.view_plane.v_res; row++) {
        for (uint32_t column = 0; column < view_plane.h_res; column++) {
            pixel_color = RGBColor(0.0f);
            for (uint32_t sample_index = 0; sample_index < view_plane.samples; sample_index++) {
                Vec2 sample = view_plane.sampler->sample_unit_square();

                pixel.x = pixel_size * (column - 0.5f * (view_plane.h_res - 1.0f) + sample.x);
                pixel.y = pixel_size * (row - 0.5f * (view_plane.v_res - 1.0f) + sample.y);

                ray.origin = pixel.x * u + pixel.y * v - d * w + eye;
                pixel_color += tracer->trace_ray(ray);
            }
            pixel_color /= static_cast<float>(view_plane.samples);
            pixel_color *= exposure_time;
            world.display_pixel(
                row + row_offset,
                column + column_offset,
                pixel_color);
        }
    }
}
