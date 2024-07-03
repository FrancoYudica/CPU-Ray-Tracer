#pragma once
#ifndef __RT_CAMERA__
#define __RT_CAMERA__
#include "math_RT.hpp"

namespace RT {
class World;

enum class CameraType {
    Orthographic = 0,
    Pinhole,
    ThinLens,
    FishEye,
    SphericalPanoramic,
    StereoDual,
    StereoAnaglyph
};

class Camera {
public:
    Camera()
        : u(Vec3(0.0))
        , v(Vec3(0.0))
        , w(Vec3(0.0))
        , eye(Vec3(0.0))
        , look_at(Vec3(0.0, 0.0, 1.0))
        , up(Vec3(0.0, 1.0, 0.0))
        , exposure_time(1.0f)
        , roll(0.0)
    {
    }
    inline CameraType get_camera_type() { return camera_type; }
    inline void set_eye(const Vec3& eye) { this->eye = eye; }
    void set_up(const Vec3& up);
    inline void set_look_at(const Vec3& look_at) { this->look_at = look_at; }
    void set_roll(double roll);
    inline double get_roll() const { return roll; }

    /// @brief Calculates UVW normal base vectors
    virtual void setup_camera();

    /// @brief Each camera needs to set up the proper
    /// World::render_buffer size
    /// @param world Reference to world
    virtual void initialize_buffer(const World& world) const;

    /// @brief Renders scene in the current World::render_buffer
    /// @param world reference to world
    /// @param row_offset offset of render_buffer
    /// @param column_offset offset of render_buffer
    virtual void render_scene(
        const World& world,
        const uint32_t row_offset = 0,
        const uint32_t column_offset = 0)
        = 0;

    /// @brief Only called when rendering with stereoscopic cameras
    ///  by default, the method calls the usual render_scene.
    /// @param world
    /// @param x Displacement of view plane along u direction.
    /// this way, right and lett cameras have coincident view planes
    /// and this makes the asymmetric view frustum
    /// @param buffer_offset column offset
    virtual void render_stereo(
        const World& world,
        const double x,
        const uint32_t buffer_offset)
    {
        render_scene(world, 0, buffer_offset);
    }

public:
    Vec3 u, v, w;
    Vec3 eye, look_at;
    Vec3 up;
    float exposure_time;
    double roll;
    CameraType camera_type;
};
}

#endif