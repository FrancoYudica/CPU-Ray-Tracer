#ifndef __RT_MESH__
#define __RT_MESH__
#include "Types_rt.hpp"
#include <vector>

namespace RT {
class Mesh {
public:
    std::vector<Vec3> vertices;

    std::vector<Vec3> normals;

    /// @brief Vertex indices
    std::vector<uint32_t> indices;

    /// @brief The faces shared by each vertex
    std::vector<std::vector<uint32_t>> vertex_faces;

    /// @brief u texture coordinate at each vertex
    std::vector<float> u;

    /// @brief v texture coordinate at each vertex
    std::vector<float> v;

    uint32_t vertices_count;
    uint32_t triangle_count;
};
}

#endif