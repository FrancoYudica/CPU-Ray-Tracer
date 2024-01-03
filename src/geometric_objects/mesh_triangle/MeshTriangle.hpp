#ifndef __RT_MESH_TRIANGLE__
#define __RT_MESH_TRIANGLE__
#include "../../GeometricObject.hpp"
#include "../../Mesh.hpp"

namespace RT {
namespace GeometricObjects {
    class MeshTriangle : public GeometricObject {

    public:
        MeshTriangle(
            std::shared_ptr<Mesh> mesh,
            uint32_t index0,
            uint32_t index1,
            uint32_t index2,
            GeometricObjectType type);

        // GeometricObject abstract methods implementations ------------------------
        bool shadow_hit(const Ray& ray, double& tmin) const override;

        Vec3 get_normal(const Vec3& p) const override;

        Vec3 sample_surface() const override;

        void set_surface_sampler(std::shared_ptr<Sampler> sampler) override;

        void recalculate_bounding_box() override;

    protected:
        uint32_t _index0;
        uint32_t _index1;
        uint32_t _index2;
        std::shared_ptr<Mesh> _mesh;
        Vec3 _normal;
    };
}
}

#endif