#include "AnaglyphCamera.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Cameras;

void AnaglyphCamera::render_scene(
    const World& world,
    const uint32_t row_offset,
    const uint32_t column_offset)
{
    // Calculates the camera separation
    double r = length(look_at - eye);
    double x = r * tan(beta * 0.5);

    // Holds the first rendered buffer
    std::shared_ptr<RenderBuffer> secondary_render_buffer = std::make_shared<RenderBuffer>(
        world.view_plane.h_res,
        world.view_plane.v_res);

    if (viewing_type == StereoViewingType::Parallel) {
        // Left camera on left side
        left_camera->render_stereo(world, x, 0);
        secondary_render_buffer->copy_buffer(world.render_buffer->buffer_raw_ptr());

        // Right camera on right side
        right_camera->render_stereo(world, -x, 0);
    } else if (viewing_type == StereoViewingType::Transverse) {
        // Left camera on right side
        left_camera->render_stereo(world, x, 0);
        secondary_render_buffer->copy_buffer(world.render_buffer->buffer_raw_ptr());

        // Right camera on left side
        right_camera->render_stereo(world, -x, 0);
    }

    // secondary_render_buffer contains the render of left camera
    // world.render_buffer contains the render of right camera
    // Now, writes in world.render_buffer the combination of both buffers
    RGBColor right_color = Constants::WHITE - left_color;
    for (uint32_t column = 0; column < secondary_render_buffer->width; column++)
        for (uint32_t row = 0; row < secondary_render_buffer->height; row++) {
            RGBColor left = secondary_render_buffer->get_pixel(column, row);
            RGBColor right = world.render_buffer->get_pixel(column, row);
            RGBColor final_color = left_color * left + right_color * right;
            world.render_buffer->set_pixel(
                column,
                row,
                final_color);
        }
}
