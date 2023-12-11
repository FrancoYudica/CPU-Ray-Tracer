#ifndef __RT_STEREO_DUAL_CAMERA__
#define __RT_STEREO_DUAL_CAMERA__

#include "../Constants.hpp"
#include "StereoCamera.hpp"
#include <memory>

namespace RT {
namespace Cameras {
    /// @brief Stereo camera that renders in a single
    // RenderBuffer both cameras render results.
    class StereoDualCamera : public StereoCamera {
    public:
        StereoDualCamera()
        {
            pixel_gap = 20;
            beta = 3.0 * Constants::PI_OVER_180;
            viewing_type = StereoViewingType::Parallel;
            camera_type = CameraType::StereoDual;
        }
        void render_scene(
            const World& world,
            const uint32_t row_offset = 0,
            const uint32_t column_offset = 0) override;

        inline void set_pixel_gap(
            uint32_t gap)
        {
            pixel_gap = gap;
        }

        void initialize_buffer(const World& world) const override;

    public:
        // Gap between the 2 rendered images.
        // Note that it doesn't affect the rendering of each camera
        // It's just where each camera places the rendered image
        // in the output buffer
        uint32_t pixel_gap;
    };
}
}

#endif