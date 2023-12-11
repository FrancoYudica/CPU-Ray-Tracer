#ifndef __RT_ORTHOGRAPHIC_CAMERA__
#define __RT_ORTHOGRAPHIC_CAMERA__

#include "../Camera.hpp"

namespace RT {
namespace Cameras {
    class OrthographicCamera : public Camera {

    public:
        OrthographicCamera()
            : Camera()
            , d(100.0f)
            , zoom(1.0f)
        {
            camera_type = CameraType::Orthographic;
        }

        void render_scene(
            const World& world,
            const uint32_t row_offset = 0,
            const uint32_t column_offset = 0) override;

        inline void set_view_distance(double d) { this->d = d; }
        inline void set_zoom(float zoom) { this->zoom = zoom; }

    public:
        double d; // Distance to view plane
        float zoom; // Zoom factor
    };
}
}

#endif