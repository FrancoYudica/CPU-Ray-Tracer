#ifndef __RT_ANAGLYPH_CAMERA__
#define __RT_ANAGLYPH_CAMERA__

#include "../Constants.hpp"
#include "StereoCamera.hpp"
#include <memory>

namespace RT {
namespace Cameras {
    class AnaglyphCamera : public StereoCamera {
    public:
        AnaglyphCamera()
        {
            beta = 3.0 * Constants::PI_OVER_180;
            viewing_type = StereoViewingType::Parallel;
            left_color = Constants::RED;
            camera_type = CameraType::StereoAnaglyph;
        }
        void render_scene(
            const World& world,
            const uint32_t row_offset = 0,
            const uint32_t column_offset = 0) override;

        void set_left_color(
            const RGBColor color)
        {
            left_color = color;
        }

    public:
        /// @brief Left eye lens color
        RGBColor left_color;
    };
}
}

#endif