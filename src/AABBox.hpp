/**
 * Axis Aligned Bounding Box, used to test ray hit
 */

#ifndef __RT_BONDING_BOX__
#define __RT_BONDING_BOX__
#include "ShadeRec.hpp"

namespace RT {
class AABBox {
public:
    AABBox(
        const Vec3& min,
        const Vec3& max)
    {
        this->min = min;
        this->max = max;
    }

    AABBox(const AABBox& other)
        : min(other.min)
        , max(other.max)
    {
    }

    bool hit(const Ray& ray) const
    {
        // Calculates Ray t distance intersections for all planes
        double tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;

        // X plane
        double inv_dx = 1.0 / ray.direction.x;
        if (inv_dx >= 0) {
            tx_min = (min.x - ray.origin.x) * inv_dx;
            tx_max = (max.x - ray.origin.x) * inv_dx;
        } else {
            tx_min = (max.x - ray.origin.x) * inv_dx;
            tx_max = (min.x - ray.origin.x) * inv_dx;
        }

        // Y plane
        double inv_dy = 1.0 / ray.direction.y;
        if (inv_dy >= 0) {
            ty_min = (min.y - ray.origin.y) * inv_dy;
            ty_max = (max.y - ray.origin.y) * inv_dy;
        } else {
            ty_min = (max.y - ray.origin.y) * inv_dy;
            ty_max = (min.y - ray.origin.y) * inv_dy;
        }

        // Z plane
        double inv_dz = 1.0 / ray.direction.z;
        if (inv_dz >= 0) {
            tz_min = (min.z - ray.origin.z) * inv_dz;
            tz_max = (max.z - ray.origin.z) * inv_dz;
        } else {
            tz_min = (max.z - ray.origin.z) * inv_dz;
            tz_max = (min.z - ray.origin.z) * inv_dz;
        }

        // All intervals [tx_min, tx_max] [ty_min, ty_max] [z_min, z_max]
        // should intersect in order to get a hit

        // t0 is max(tx_min, ty_min, tz_min)
        // t1 is min(tx_max, ty_max, tz_max)
        double t0, t1;

        // finds largest entering value
        if (tx_min > ty_min) {
            t0 = tx_min;
        } else {
            t0 = ty_min;
        }
        if (tz_min > t0) {
            t0 = tz_min;
        }

        // finds smallest exiting value
        if (tx_max < ty_max) {
            t1 = tx_max;
        } else {
            t1 = ty_max;
        }
        if (tz_max < t1) {
            t1 = tz_max;
        }

        return t0 < t1 && t1 > Constants::k_epsilon;
    }

    /// @brief Returns surrounding box of two AABBox
    static AABBox get_surrounding(const AABBox& a, const AABBox& b)
    {
        Vec3 min_a = a.get_min();
        Vec3 max_a = a.get_max();
        Vec3 min_b = b.get_min();
        Vec3 max_b = b.get_max();
        return AABBox(
            Vec3(
                std::min(min_a.x, min_b.x),
                std::min(min_a.y, min_b.y),
                std::min(min_a.z, min_b.z)),
            Vec3(
                std::max(max_a.x, max_b.x),
                std::max(max_a.y, max_b.y),
                std::max(max_a.z, max_b.z)));
    }

    inline Vec3 get_min() const
    {
        return min;
    }
    inline Vec3 get_max() const
    {
        return max;
    }

private:
    Vec3 min, max;
};
}

#endif