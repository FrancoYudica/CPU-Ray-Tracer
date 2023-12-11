#ifndef __RT_STEREO_CAMERA__
#define __RT_STEREO_CAMERA__

#include "../Camera.hpp"
#include "../Constants.hpp"
#include <memory>

namespace RT {

namespace Cameras {
    /*
        Stereo camera outputs a buffer with 2 images
        Viewing type defines where the left and right camera
        images are placed.
        Parallel: The rendered image of the left camera is placed on the LEFT side
        Transverse: The rendered image of the left camera is placed on the RIGHT side
    */
    enum class StereoViewingType {
        Parallel,
        Transverse
    };

    /// @brief Base class for all StereoCameras
    class StereoCamera : public Camera {
    public:
        virtual void render_scene(
            const World& world,
            const uint32_t row_offset = 0,
            const uint32_t column_offset = 0) override
            = 0;

        void setup_camera() override;
        inline void set_viewing(
            StereoViewingType type)
        {
            viewing_type = type;
        }
        inline void set_left_camera(
            const std::shared_ptr<Camera>& camera)
        {
            left_camera = camera;
        }
        inline void set_right_camera(
            const std::shared_ptr<Camera>& camera)
        {
            right_camera = camera;
        }
        void set_stereo_angle_degrees(
            double angle)
        {
            beta = angle *= Constants::PI_OVER_180;
        }

    public:
        std::shared_ptr<Camera> left_camera, right_camera;
        double beta;
        StereoViewingType viewing_type;
    };
}
}

#endif