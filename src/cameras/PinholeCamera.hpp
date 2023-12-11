#pragma once
#ifndef __RT_PINHOLE_CAMERA__
#define __RT_PINHOLE_CAMERA__

#include "../Camera.hpp"

namespace RT {
namespace Cameras {
    class PinholeCamera : public Camera {

    public:
        PinholeCamera()
            : Camera()
            , d(100.0f)
            , zoom(1.0f)
        {
            camera_type = CameraType::Pinhole;
        }
        void render_scene(
            const World& world,
            const uint32_t row_offset = 0,
            const uint32_t column_offset = 0) override;

        void render_stereo(const World& world, const double x, const uint32_t buffer_offset) override;
        inline void set_view_distance(double d) { this->d = d; }
        inline void set_zoom(float zoom) { this->zoom = zoom; }

    private:
        Vec3 _ray_direction(const Vec2& pixel) const;

    public:
        double d; // Distance to view plane
        float zoom; // Zoom factor
    };
}
}

#endif