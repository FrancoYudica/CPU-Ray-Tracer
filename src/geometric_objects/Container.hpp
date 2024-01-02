#ifndef __RT_CONTAINER__
#define __RT_CONTAINER__
#include "../GeometricObject.hpp"
#include <algorithm>
#include <vector>

namespace RT {
namespace GeometricObjects {

    /// @brief Container is a GeometricObject subclass, used to store and
    /// manage multiple GeometricObjects.
    class Container : public GeometricObject {

    public:
        Container(GeometricObjectType object_type = GeometricObjectType::Container);

        /// @brief Adds geometric object to Container
        virtual void add(const GeometricObjectPtr& object);

        /// @brief  Tests if geometric object is in Container
        virtual bool contains(const GeometricObjectPtr& object) const;

        /// @brief Removes geometric object from container if it's contained
        /// @return True if object was removed successfully
        virtual bool remove(const GeometricObjectPtr& object);

        /// @brief Allocates memory for 'count' geometric objects
        virtual void reserve(uint32_t count);

        /// @brief Removes all geometric objects
        virtual void clear();

        /// @brief Amount of immediate GeometricObjects
        size_t size();

        std::vector<GeometricObjectPtr>::const_iterator begin() const { return _objects.begin(); }

        std::vector<GeometricObjectPtr>::const_iterator end() const { return _objects.end(); }

        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

        virtual bool shadow_hit(const Ray& ray, double& tmin) const override;

        virtual void recalculate_bounding_box() override;

    protected:
        std::vector<GeometricObjectPtr> _objects;
    };
}
}
#endif