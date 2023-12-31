#ifndef __RT_CONE__
#define __RT_CONE__
#include "../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {

    /// @brief Generic cone that lays in the XZ plane and has it's vertex on the y axis
    /// where y = height.
    class Cone : public GeometricObject {

    public:
        Cone(
            const double height = 2.0,
            const double radius = 1.0)
            : _height(height)
            , _radius(radius)
            , _height_over_radius(height / radius)
            , GeometricObject(GeometricObjectType::Cone)
        {
        }
        void set_radius(const double& r)
        {
            _radius = r;
            _height_over_radius = _height / _radius;
        }
        void set_height(const double& h)
        {
            _height = h;
            _height_over_radius = _height / _radius;
        }
        inline double get_radius() const { return _radius; }
        inline double get_height() const { return _height; }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        bool shadow_hit(const Ray& ray, double& tmin) const override;
        void recalculate_bounding_box() override;

    private:
        Vec3 _compute_normal(const Vec3& p) const;

    private:
        double _height;
        double _radius;

        /// @brief Little optimization for intersection and normal calculation
        double _height_over_radius;
    };
}
}

#endif