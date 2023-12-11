#include "Camera.hpp"
#include "RenderBuffer.hpp"
#include "World.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <memory>

using namespace RT;

void Camera::setup_camera()
{
    // flipped camera direction
    Vec3 camera_direction = Math::normalize(look_at - eye);
    w = -camera_direction;

    // When w is parallel to the up vector
    if (abs(Math::dot(camera_direction, up)) == 1.0f) {
        u = Vec3(sin(roll), 0.0f, cos(roll));
        v = Math::normalize(cross(u, up));
        return;
    }

    // Tests for special cases, where 'w' is parallel to 'up'

    // Calculates the base with the current up vector which is usually
    // the world up direction (0, 1, 0)
    Vec3 temp_u = Math::normalize(cross(up, w));
    Vec3 temp_v = Math::normalize(cross(w, temp_u));

    // Rotates temp_v around the look direction
    Vec3 up_local = Math::normalize(glm::rotate(temp_v, roll, -w));

    u = Math::normalize(cross(up_local, w));
    v = Math::normalize(cross(w, u));
}

void Camera::set_roll(double roll)
{
    // When rotation is used, the up vector should be this one
    up = Vec3(0.0, 1.0, 0.0);
    this->roll = roll;
}

void Camera::set_up(const Vec3& up)
{
    // Sets custom up vector
    this->up = up;

    // Deactivates rotation
    roll = 0.0;
}

void Camera::initialize_buffer(
    const World& world) const
{
    std::shared_ptr<RenderBuffer> buffer = std::make_shared<RenderBuffer>(
        world.view_plane.h_res,
        world.view_plane.v_res);
    world.set_render_buffer(buffer);
}
