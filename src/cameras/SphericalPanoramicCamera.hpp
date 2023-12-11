#ifndef __RT_SPHERICAL_PANORAMIC_CAMERA__
#define __RT_SPHERICAL_PANORAMIC_CAMERA__
#include "../Camera.hpp"
#include "../Sampler.hpp"
#include <memory>

namespace RT {
namespace Cameras {
    class SphericalPanoramicCamera : public Camera {
    public:
        SphericalPanoramicCamera()
            : psi_max(3.1415926536 / 4.0)
            , lambda_max(3.1415926536 / 2.0)
        {
            camera_type = CameraType::SphericalPanoramic;
        }

        void render_scene(
            const World& world,
            const uint32_t row_offset = 0,
            const uint32_t column_offset = 0) override;

        inline void set_psi_max(double psi) { this->psi_max = psi; }
        inline void set_lambda_max(double lambda) { this->lambda_max = lambda; }

    public:
        double psi_max;
        double lambda_max;

    private:
        Vec3 _ray_direction(
            const Vec2& pixel_point,
            const uint32_t h_res,
            const uint32_t v_res);

    private:
        std::shared_ptr<Sampler> _sampler;
    };
}
}

#endif