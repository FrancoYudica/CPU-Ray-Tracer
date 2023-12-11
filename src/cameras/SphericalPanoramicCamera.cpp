#include "SphericalPanoramicCamera.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Cameras;

void SphericalPanoramicCamera::render_scene(
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

    for (uint32_t row = 0; row < world.view_plane.v_res; row++) {
        for (uint32_t column = 0; column < view_plane.h_res; column++) {
            pixel_color = RGBColor(0.0f);
            for (uint32_t sample_index = 0; sample_index < view_plane.samples; sample_index++) {
                Vec2 sample = view_plane.sampler->sample_unit_square();

                // Pixel size isn't required
                pixel.x = column - 0.5f * (view_plane.h_res - 1.0f) + sample.x;
                pixel.y = row - 0.5f * (view_plane.v_res - 1.0f) + sample.y;

                ray.direction = _ray_direction(pixel, world.view_plane.h_res, world.view_plane.v_res);
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

Vec3 SphericalPanoramicCamera::_ray_direction(
    const Vec2& pixel_point,
    const uint32_t h_res,
    const uint32_t v_res)
{

    // Normalized device coordinates [-1, 1]
    Vec2 pp_n(
        pixel_point.x * 2.0 / h_res,
        pixel_point.y * 2.0 / v_res);

    float radius_squared = pp_n.x * pp_n.x + pp_n.y * pp_n.y;
    float radius = sqrtf(radius_squared);

    // compute the spherical azimuth and polar angles
    float lambda = pp_n.x * lambda_max;
    float psi = pp_n.y * psi_max;

    float phi = Constants::PI - lambda;
    float theta = Constants::PI_2 - psi;

    double sin_phi = sin(phi);
    double cos_phi = cos(phi);
    double sin_theta = sin(theta);
    double cos_theta = cos(theta);

    Vec3 dir = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w;
    return dir;
}