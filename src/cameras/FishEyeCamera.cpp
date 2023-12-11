#include "FishEyeCamera.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Cameras;

void FishEyeCamera::render_scene(
    const World& world,
    const uint32_t row_offset,
    const uint32_t column_offset)
{
    // References to world data
    const ViewPlane& view_plane = world.view_plane;
    const std::shared_ptr<Tracer>& tracer = world.tracer;

    RGBColor pixel_color;
    Ray ray;
    ray.origin = eye;

    Vec2 pixel;

    double pixel_size = view_plane.pixel_size;
    float radius_squared;

    for (uint32_t row = 0; row < world.view_plane.v_res; row++) {
        for (uint32_t column = 0; column < view_plane.h_res; column++) {
            pixel_color = RGBColor(0.0f);
            for (uint32_t sample_index = 0; sample_index < view_plane.samples; sample_index++) {
                Vec2 sample = view_plane.sampler->sample_unit_square();

                // Pixel size isn't required
                pixel.x = column - 0.5f * (view_plane.h_res - 1.0f) + sample.x;
                pixel.y = row - 0.5f * (view_plane.v_res - 1.0f) + sample.y;

                ray.direction = _ray_direction(pixel, world.view_plane.h_res, world.view_plane.v_res, radius_squared);

                if (radius_squared <= 1)
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

Vec3 FishEyeCamera::_ray_direction(
    const Vec2& pixel_point,
    const uint32_t h_res,
    const uint32_t v_res,
    float& radius_squared)
{

    // Normalized device coordinates [-1, 1]
    Vec2 pp_n(
        pixel_point.x * 2.0 / h_res,
        pixel_point.y * 2.0 / v_res);

    radius_squared = pp_n.x * pp_n.x + pp_n.y * pp_n.y;

    if (radius_squared > 1.0)
        return Vec3(0.0);

    float radius = sqrtf(radius_squared);

    // Linear transformation for psi
    float psi = radius * psi_max;
    double sin_psi = sin(psi);
    double cos_psi = cos(psi);

    // (From polar coordinates)
    double sin_alpha = pp_n.y / radius;
    double cos_alpha = pp_n.x / radius;

    Vec3 dir = sin_psi * cos_alpha * u + sin_psi * sin_alpha * v - cos_psi * w;
    return normalize(dir);
}