#ifndef __RT_COMPOUND_BOX__
#define __RT_COMPOUND_BOX__
#include "../Rect.hpp"

#include "Compound.hpp"
namespace RT {
namespace GeometricObjects {

    /// @brief Axis aligned box that is made out of 4 Rects. This way it's possible
    /// to setup different textures to different faces of the Box.
    class CompoundBox : public Compound {
    public:
        CompoundBox(
            Vec3 min = Vec3(-1.0),
            Vec3 max = Vec3(1.0));

        inline Vec3 get_min() const { return _min; }
        inline Vec3 get_max() const { return _max; }
        inline Vec3 get_center() const { return _min + 0.5 * (_max - _min); }
        inline double get_half_dx() const { return 0.5 * (_max.x - _min.x); }
        inline double get_half_dy() const { return 0.5 * (_max.y - _min.y); }
        inline double get_half_dz() const { return 0.5 * (_max.z - _min.z); }
        void set_min(const Vec3& m);
        void set_max(const Vec3& m);
        void set_center(const Vec3& center);
        void set_half_dx(double dx);
        void set_half_dy(double dy);
        void set_half_dz(double dz);

    private:
        void _recalculate_edges();

    private:
        Vec3 _min, _max;
        std::shared_ptr<Rect> _rect_x_min;
        std::shared_ptr<Rect> _rect_x_max;
        std::shared_ptr<Rect> _rect_y_min;
        std::shared_ptr<Rect> _rect_y_max;
        std::shared_ptr<Rect> _rect_z_min;
        std::shared_ptr<Rect> _rect_z_max;
    };
}
}

#endif