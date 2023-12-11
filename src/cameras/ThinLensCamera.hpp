#ifndef __RT_THIN_LENS__
#define __RT_THIN_LENS__
#include "../Camera.hpp"
#include "../Sampler.hpp"
#include <memory>

namespace RT {
namespace Cameras {
    class ThinLensCamera : public Camera {
    public:
        ThinLensCamera()
            : focal_distance(200.0)
            , lens_radius(1.0)
            , d(100.0)
            , zoom(1.0f)
        {
            camera_type = CameraType::ThinLens;
        }

        void render_scene(
            const World& world,
            const uint32_t row_offset = 0,
            const uint32_t column_offset = 0) override;

        inline void set_view_distance(double d) { this->d = d; }
        inline void set_lens_radius(double lr) { lens_radius = lr; }
        inline void set_focal_distance(double d) { focal_distance = d; }
        inline void set_zoom(float zoom) { this->zoom = zoom; }
        void set_sampler(const std::shared_ptr<Sampler>& sampler);

    public:
        double focal_distance; // Distance to the focal plane
        double lens_radius; // Radius of thin lens
        double d; // Distance to view plane
        float zoom;

    private:
        Vec3 _ray_direction(const Vec2& pixel_point, const Vec2& lens_point);

    private:
        std::shared_ptr<Sampler> _sampler;
    };
}
}

#endif