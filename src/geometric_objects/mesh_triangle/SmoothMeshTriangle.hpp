#ifndef __RT_SMOOTH_MESH_TRIANGLE__
#define __RT_SMOOTH_MESH_TRIANGLE__

#include "MeshTriangle.hpp"

namespace RT {
namespace GeometricObjects {
    class SmoothMeshTriangle : public MeshTriangle {

    public:
        SmoothMeshTriangle(
            std::shared_ptr<Mesh> mesh,
            uint32_t index0,
            uint32_t index1,
            uint32_t index2);

        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& record) const override;
    };
}
}

#endif