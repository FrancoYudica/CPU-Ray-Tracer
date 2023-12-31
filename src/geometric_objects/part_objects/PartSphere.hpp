#ifndef __RT_PART_SPHERE__
#define __RT_PART_SPHERE__
#include "../../GeometricObject.hpp"

namespace RT {
namespace GeometricObjects {
    class PartSphere : public GeometricObject {

    public:
        PartSphere(
            double min_phi = Constants::PI_OVER_4,
            double max_phi = Constants::PI_2 - Constants::PI_OVER_4,
            double min_theta = Constants::PI_OVER_4,
            double max_theta = Constants::PI - Constants::PI_OVER_4)
            : _min_phi(min_phi)
            , _max_phi(max_phi)
            , _min_theta(min_theta)
            , _max_theta(max_theta)
            , _min_y(cos(max_theta))
            , _max_y(cos(min_theta))
            , GeometricObject(GeometricObjectType::PartSphere)
        {
            recalculate_bounding_box();
            disable_bounding_box();
            set_normal_flip();
        }

        inline double get_min_phi() const { return _min_phi; }
        inline double get_max_phi() const { return _max_phi; }
        inline double get_min_theta() const { return _min_theta; }
        inline double get_max_theta() const { return _max_theta; }

        inline void set_max_phi(double max) { _max_phi = max; }
        inline void set_min_phi(double min) { _min_phi = min; }
        inline void set_max_theta(double max)
        {
            _max_theta = max;
            _min_y = cos(max);
        }
        inline void set_min_theta(double min)
        {
            _min_theta = min;
            _max_y = cos(min);
        }

        bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        bool shadow_hit(const Ray& ray, double& tmin) const override;
        void recalculate_bounding_box() override;

    private:
        /// @brief phi is an angle in radians measured in the ZX plane,
        /// and starts from the positive Z axis. Both, max_phi and min_phi
        /// should range in [0, 2*PI]
        double _max_phi, _min_phi;

        /// @brief theta is an angle in radians measured around the positive Y axis,
        /// theta ranges in [0, PI]
        double _max_theta, _min_theta;

        /// @brief Cosine of max theta and min theta. This way we can avoid using acos(y)
        double _max_y, _min_y;
    };
}
}

#endif