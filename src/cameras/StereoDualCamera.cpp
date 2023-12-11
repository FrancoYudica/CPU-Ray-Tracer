#include "StereoDualCamera.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Cameras;

void StereoDualCamera::render_scene(
    const World& world,
    const uint32_t row_offset,
    const uint32_t column_offset)
{
    // Calculates the camera separation
    double r = length(look_at - eye);
    double x = r * tan(beta * 0.5);

    if (viewing_type == StereoViewingType::Parallel) {
        // Left camera on left side
        left_camera->render_stereo(world, x, 0);

        // Right camera on right side
        right_camera->render_stereo(world, -x, pixel_gap + world.view_plane.h_res);
    } else if (viewing_type == StereoViewingType::Transverse) {
        // Left camera on right side
        left_camera->render_stereo(world, x, pixel_gap + world.view_plane.h_res);

        // Right camera on left side
        right_camera->render_stereo(world, -x, 0);
    }
}

void StereoDualCamera::initialize_buffer(
    const World& world) const
{
    std::shared_ptr<RenderBuffer> buffer = std::make_shared<RenderBuffer>(
        world.view_plane.h_res * 2 + pixel_gap,
        world.view_plane.v_res);
    world.set_render_buffer(buffer);
}