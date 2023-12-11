#ifndef __RT_FISH_EYE_CAMERA__
#define __RT_FISH_EYE_CAMERA__
#include "../Camera.hpp"
#include "../Sampler.hpp"
#include <memory>

namespace RT {
namespace Cameras {
    class FishEyeCamera : public Camera {
    public:
        FishEyeCamera()
            : psi_max(3.1415926536 / 2.0)
        {
            camera_type = CameraType::FishEye;
        }

        void render_scene(
            const World& world,
            const uint32_t row_offset = 0,
            const uint32_t column_offset = 0) override;
        inline void set_psi_max(double psi) { this->psi_max = psi; }

    public:
        double psi_max;

    private:
        Vec3 _ray_direction(
            const Vec2& pixel_point,
            const uint32_t h_res,
            const uint32_t v_res,
            float& r_squared);

    private:
        std::shared_ptr<Sampler> _sampler;
    };
}
}

#endif