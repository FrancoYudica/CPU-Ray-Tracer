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
            Vec3 max = Vec3(1.0))
            : _min(min)
            , _max(max)
            , Compound(GeometricObjectType::CompoundBox)
        {

            _rect_x_min = std::make_shared<Rect>();
            _rect_x_max = std::make_shared<Rect>();
            _rect_y_min = std::make_shared<Rect>();
            _rect_y_max = std::make_shared<Rect>();
            _rect_z_min = std::make_shared<Rect>();
            _rect_z_max = std::make_shared<Rect>();
            _recalculate_edges();

            add_object(_rect_x_min);
            add_object(_rect_x_max);
            add_object(_rect_z_min);
            add_object(_rect_z_max);
            add_object(_rect_y_min);
            add_object(_rect_y_max);
        }

        inline Vec3 get_min() const { return _min; }
        inline Vec3 get_max() const { return _max; }
        inline Vec3 get_center() const { return _min + 0.5 * (_max - _min); }
        inline double get_half_dx() const { return 0.5 * (_max.x - _min.x); }
        inline double get_half_dy() const { return 0.5 * (_max.y - _min.y); }
        inline double get_half_dz() const { return 0.5 * (_max.z - _min.z); }

        void set_min(const Vec3& m)
        {
            _min = m;
            _recalculate_edges();
        }
        void set_max(const Vec3& m)
        {
            _max = m;
            _recalculate_edges();
        }

        void set_center(const Vec3& center)
        {
            Vec3 half_size = Vec3(
                get_half_dx(),
                get_half_dy(),
                get_half_dz());

            _min = center - half_size;
            _max = center + half_size;
            _recalculate_edges();
        }

        void set_half_dx(double dx)
        {
            Vec3 center = get_center();
            _min.x = center.x - dx;
            _max.x = center.x + dx;
            _recalculate_edges();
        }

        void set_half_dy(double dy)
        {
            Vec3 center = get_center();
            _min.y = center.y - dy;
            _max.y = center.y + dy;
            _recalculate_edges();
        }

        void set_half_dz(double dz)
        {
            Vec3 center = get_center();
            _min.z = center.z - dz;
            _max.z = center.z + dz;
            _recalculate_edges();
        }

    private:
        void _recalculate_edges()
        {
            set_bounding_box(_min, _max);
            _rect_x_min->set_p0(Vec3(_min.x, _min.y, _min.z));
            _rect_x_min->set_a(Vec3(0.0, 0.0, _max.z - _min.z));
            _rect_x_min->set_b(Vec3(0.0, _max.y - _min.y, 0.0));

            _rect_x_max->set_p0(Vec3(_max.x, _min.y, _max.z));
            _rect_x_max->set_a(Vec3(0.0, 0.0, _min.z - _max.z));
            _rect_x_max->set_b(Vec3(0.0, _max.y - _min.y, 0.0));

            _rect_z_min->set_p0(Vec3(_max.x, _min.y, _min.z));
            _rect_z_min->set_a(Vec3(_min.x - _max.x, 0.0, 0.0));
            _rect_z_min->set_b(Vec3(0.0, _max.y - _min.y, 0.0));

            _rect_z_max->set_p0(Vec3(_min.x, _min.y, _max.z));
            _rect_z_max->set_a(Vec3(_max.x - _min.x, 0.0, 0.0));
            _rect_z_max->set_b(Vec3(0.0, _max.y - _min.y, 0.0));

            _rect_y_min->set_p0(Vec3(_max.x, _min.y, _max.z));
            _rect_y_min->set_a(Vec3(_min.x - _max.x, 0.0, 0.0));
            _rect_y_min->set_b(Vec3(0.0, 0.0, _min.z - _max.z));

            _rect_y_max->set_p0(Vec3(_min.x, _max.y, _max.z));
            _rect_y_max->set_a(Vec3(_max.x - _min.x, 0.0, 0.0));
            _rect_y_max->set_b(Vec3(0.0, 0.0, _min.z - _max.z));
        }

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