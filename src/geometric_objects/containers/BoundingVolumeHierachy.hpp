#ifndef __RT_BVH__
#define __RT_BVH__
#include "../../AABBox.hpp"
#include "../../Ray.hpp"
#include "../Container.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace RT {
namespace GeometricObjects {

    namespace Impl {
        class _BVHNode;
    }

    /// @brief Container that implements a Bounding volume hierarchy
    /// optimization algorithm.
    class BVH : public Container {

    public:
        BVH();

        /// @brief Returns true when tree is built
        bool is_built() const { return _built; }

        void set_built_state(bool state) { _built = state; }

        virtual void add(const GeometricObjectPtr& object) override;

        virtual bool remove(const GeometricObjectPtr& object) override;

        virtual void clear() override;

        /// @brief Rebuilds the entire tree
        void build_tree();

        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
        virtual bool shadow_hit(const Ray& ray, double& tmin) const override;

    private:
        std::shared_ptr<Impl::_BVHNode> _root_node;
        bool _built;
    };

    namespace Impl {
        class _BVHNode : public GeometricObject {
        public:
            _BVHNode()
                : GeometricObject(GeometricObjectType::BoundingVolumeHierarchy)
            {
            }
            _BVHNode(
                std::vector<GeometricObjectPtr>& objects,
                uint32_t start,
                uint32_t end);

            virtual bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;

            virtual bool shadow_hit(const Ray& ray, double& tmin) const override;

        private:
            bool _is_leaf;
            GeometricObjectPtr _min_child;
            GeometricObjectPtr _max_child;
        };
    }

}
}

#endif