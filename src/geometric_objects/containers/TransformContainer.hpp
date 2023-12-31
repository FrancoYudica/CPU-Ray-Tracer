#ifndef __RT_TRANSFORM_CONTAINER__
#define __RT_TRANSFORM_CONTAINER__

#include "../../AABBox.hpp"
#include "../../Instance.hpp"
#include "../../Ray.hpp"
#include "../Container.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace RT {
namespace GeometricObjects {

    /// @brief Container that implements a Bounding volume hierarchy
    /// optimization algorithm.
    class TransformContainer : public Container {

    public:
        TransformContainer();

        virtual void add(const GeometricObjectPtr& object) override;
        virtual bool remove(const GeometricObjectPtr& object) override;
        virtual void clear() override;
        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        virtual bool shadow_hit(const Ray& ray, double& tmin) const override;
        virtual void recalculate_bounding_box() override;

        void set_translation(const Vec3& translation);
        void set_scale(const Vec3& scale);
        void set_rotation_x(const double& rotation);
        void set_rotation_y(const double& rotation);
        void set_rotation_z(const double& rotation);
        void set_transform_the_texture(bool transform);

        Vec3 get_translation() const;
        Vec3 get_scale() const;
        Vec3 get_rotation() const;
        bool get_transform_the_texture() const;

    private:
        std::shared_ptr<Container> _container;
        std::shared_ptr<Instance> _instance;
    };
}
}

#endif