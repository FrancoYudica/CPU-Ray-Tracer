#include "StereoCamera.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Cameras;

void StereoCamera::setup_camera()
{
    Camera::setup_camera();

    if (!left_camera)
        throw "StereoCamera::setup_cameras(). Forgot to set left camera";

    if (!right_camera)
        throw "StereoCamera::setup_cameras(). Forgot to set right camera";

    // Calculates the camera separation
    double r = length(look_at - eye);
    double x = r * tan(beta * 0.5);

    // Offsets the eyes and directions of cameras
    // along the horizontal (u) axis
    left_camera->set_eye(eye - x * u);
    left_camera->set_look_at(look_at - x * u);
    left_camera->setup_camera();
    left_camera->exposure_time = exposure_time;

    right_camera->set_eye(eye + x * u);
    right_camera->set_look_at(look_at + x * u);
    right_camera->setup_camera();
    right_camera->exposure_time = exposure_time;
}