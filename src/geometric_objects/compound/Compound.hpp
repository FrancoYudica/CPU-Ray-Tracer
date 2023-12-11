#ifndef __RT_COMPOUND__
#define __RT_COMPOUND__
#include "../../GeometricObject.hpp"
#include <memory>
#include <vector>

namespace RT {
namespace GeometricObjects {
    class Compound : public GeometricObject {
    public:
        Compound(GeometricObjectType type)
            : GeometricObject(type)
        {
        }

        virtual void add_object(const GeometricObjectPtr object);

        virtual void set_material(const std::shared_ptr<Material>& mtl) override;

        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

        /// @brief Hit called when trying to cast shadows
        /// @param ray Origin in intersection and direction to light
        virtual bool shadow_hit(const Ray& ray, double& tmin) const override;

    protected:
        std::vector<GeometricObjectPtr> _objects;
    };
}
}

#endif