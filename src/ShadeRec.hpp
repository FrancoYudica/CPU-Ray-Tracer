#ifndef __RT_SHADE_RECORD__
#define __RT_SHADE_RECORD__
#include "Material.hpp"
#include "Math_rt.hpp"
#include "Ray.hpp"
#include <memory>

namespace RT {
class World;

/// @brief Normal setup after hit
enum class NormalType : uint8_t {

    /// @brief Normal is flipped if necessary
    Flip,

    /// @brief Normal always points outwards, therefore
    /// no flipping or modification is done
    Outwards,

    /// @brief Normal always points inwards
    Inwards
};

struct ShadeRec {
    bool hit_an_object;
    double t;

    /// @brief Nearest object material
    std::shared_ptr<Material> material;

    /// @brief Hit point in world coordinates
    Vec3 hit_point;

    /// @brief Hit point in object local coordinates
    Vec3 local_hit_point;

    Ray ray;

    /// @brief Recursion depth
    uint32_t depth;

    const World* world;

    ShadeRec(const World* world, const Ray& ray)
        : hit_an_object(false)
        , t(0.0)
        , material(nullptr)
        , hit_point(Vec3(0.0, 0.0, 0.0))
        , local_hit_point(Vec3(0.0, 0.0, 0.0))
        , ray(ray)
        , depth(0)
        , world(world)
        , _normal(Vec3(0.0, 0.0, 0.0))
    {
    }

    ShadeRec(const ShadeRec& rec)
        : hit_an_object(rec.hit_an_object)
        , t(rec.t)
        , material(rec.material)
        , hit_point(rec.hit_point)
        , local_hit_point(rec.local_hit_point)
        , ray(rec.ray)
        , depth(rec.depth)
        , world(rec.world)
        , _normal(rec.get_normal())
    {
    }

    Vec3 get_normal() const { return _normal; }

    void set_normal(const Vec3& n, const NormalType& normal_type)
    {
        _normal = n;
        switch (normal_type) {
        case NormalType::Flip:

            // Flips when normal and ray.direction
            // point to the "same side"
            if (Math::dot(_normal, ray.direction) > 0.0) {
                _normal *= -1.0;
            }

            break;
        // Keeps normal in the same direction, since
        // GeometricObject subclasses should return
        // outwards normal by default.
        case NormalType::Outwards:
            break;

        // Flips normal
        case NormalType::Inwards:
            _normal *= -1.0;
            break;
        }
    }

private:
    /// @brief Normal in world coordinates
    Vec3 _normal;
};
} // namespace RT

#endif