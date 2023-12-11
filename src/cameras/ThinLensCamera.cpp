#include "ThinLensCamera.hpp"
#include "../World.hpp"
#include "../samplers/MultiJitteredSampler.hpp"

using namespace RT;
using namespace Cameras;

void ThinLensCamera::render_scene(
    const World& world,
    const uint32_t row_offset,
    const uint32_t column_offset)
{

    if (!_sampler) {
        std::shared_ptr<Sampler> sampler = std::make_shared<Samplers::MultiJitteredSampler>(world.view_plane.samples);
        set_sampler(sampler);
    }

    // References to world data
    const ViewPlane& view_plane = world.view_plane;
    const std::shared_ptr<Tracer>& tracer = world.tracer;

    RGBColor pixel_color;
    Ray ray;
    Vec2 pixel_point;

    // Zoom modifies the pixel size
    double pixel_size = view_plane.pixel_size / zoom;

    for (uint32_t row = 0; row < world.view_plane.v_res; row++) {
        for (uint32_t column = 0; column < view_plane.h_res; column++) {
            pixel_color = RGBColor(0.0f);
            for (uint32_t sample_index = 0; sample_index < view_plane.samples; sample_index++) {

                // View plane pixel sample point
                Vec2 sample_vp = view_plane.sampler->sample_unit_square();
                pixel_point.x = pixel_size * (column - 0.5f * (view_plane.h_res - 1.0f) + sample_vp.x);
                pixel_point.y = pixel_size * (row - 0.5f * (view_plane.v_res - 1.0f) + sample_vp.y);

                // Lens sample point
                Vec2 sample_disk = _sampler->sample_unit_disk();
                Vec2 lens_point = lens_radius * sample_disk;

                // Calculates ray origin along lens surface. (The lens is perpendicular to w)
                ray.origin = lens_point.x * u + lens_point.y * v + eye;

                ray.direction = _ray_direction(pixel_point, lens_point);

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

void ThinLensCamera::set_sampler(const std::shared_ptr<Sampler>& sampler)
{
    _sampler = sampler;
    _sampler->generate_samples();
    _sampler->map_samples_to_unit_disk();
    _sampler->setup_shuffled_indices();
}

Vec3 ThinLensCamera::_ray_direction(const Vec2& pixel_point, const Vec2& lens_point)
{
    // Intersection point with focal plane
    Vec2 p = pixel_point * focal_distance / d;

    Vec3 dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - focal_distance * w;
    return Math::normalize(dir);
}
