#include "Box.hpp"
#include <iostream>

using namespace RT;
using namespace GeometricObjects;

Vec3 Box::get_normal(const uint32_t& face) const
{
    switch (face) {
    case 0:
        return Vec3(-1.0, 0.0, 0.0); // -x face
    case 1:
        return Vec3(0.0, -1.0, 0.0); // -y face
    case 2:
        return Vec3(0.0, 0.0, -1.0); // -z face
    case 3:
        return Vec3(1.0, 0.0, 0.0); // +x face
    case 4:
        return Vec3(0.0, 1.0, 0.0); // +y face
    case 5:
        return Vec3(0.0, 0.0, 1.0); // +z face
    default:
        return Vec3();
    }
}

bool Box::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    // Calculates Ray t distance intersections for all planes
    double tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;

    // X plane
    double inv_dx = 1.0 / ray.direction.x;
    if (inv_dx >= 0) {
        tx_min = (_min.x - ray.origin.x) * inv_dx;
        tx_max = (_max.x - ray.origin.x) * inv_dx;
    } else {
        tx_min = (_max.x - ray.origin.x) * inv_dx;
        tx_max = (_min.x - ray.origin.x) * inv_dx;
    }

    // Y plane
    double inv_dy = 1.0 / ray.direction.y;
    if (inv_dy >= 0) {
        ty_min = (_min.y - ray.origin.y) * inv_dy;
        ty_max = (_max.y - ray.origin.y) * inv_dy;
    } else {
        ty_min = (_max.y - ray.origin.y) * inv_dy;
        ty_max = (_min.y - ray.origin.y) * inv_dy;
    }

    // Z plane
    double inv_dz = 1.0 / ray.direction.z;
    if (inv_dz >= 0) {
        tz_min = (_min.z - ray.origin.z) * inv_dz;
        tz_max = (_max.z - ray.origin.z) * inv_dz;
    } else {
        tz_min = (_max.z - ray.origin.z) * inv_dz;
        tz_max = (_min.z - ray.origin.z) * inv_dz;
    }

    // All intervals [tx_min, tx_max] [ty_min, ty_max] [z_min, z_max]
    // should intersect in order to get a hit

    // t0 is max(tx_min, ty_min, tz_min)
    // t1 is min(tx_max, ty_max, tz_max)
    double t0, t1;
    uint32_t face_in;
    uint32_t face_out;

    // finds largest entering value
    if (tx_min > ty_min) {
        t0 = tx_min;
        face_in = (inv_dx >= 0.0) ? 0 : 3;
    } else {
        t0 = ty_min;
        face_in = (inv_dy >= 0.0) ? 1 : 4;
    }
    if (tz_min > t0) {
        t0 = tz_min;
        face_in = (inv_dz >= 0.0) ? 2 : 5;
    }

    // finds smallest exiting value
    if (tx_max < ty_max) {
        t1 = tx_max;
        face_out = (inv_dx >= 0.0) ? 3 : 0;
    } else {
        t1 = ty_max;
        face_out = (inv_dy >= 0.0) ? 4 : 1;
    }
    if (tz_max < t1) {
        t1 = tz_max;
        face_out = (inv_dz >= 0.0) ? 5 : 2;
    }

    // if hits
    if (t0 < t1 && t1 > Constants::k_epsilon) {

        // if ray is outside object
        if (t0 > Constants::k_epsilon) {
            tmin = t0;
            record.set_normal(get_normal(face_in), get_normal_type());
        } else {
            tmin = t1;
            record.set_normal(get_normal(face_out), get_normal_type());
        }
        record.local_hit_point = ray.at(tmin);
        record.hit_point = record.local_hit_point;
        record.material = get_material();

        return true;
    }
    return false;
}

bool Box::shadow_hit(const Ray& ray, double& tmin) const
{
    // Calculates Ray t distance intersections for all planes
    double tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;

    // X plane
    double inv_dx = 1.0 / ray.direction.x;
    if (inv_dx >= 0) {
        tx_min = (_min.x - ray.origin.x) * inv_dx;
        tx_max = (_max.x - ray.origin.x) * inv_dx;
    } else {
        tx_min = (_max.x - ray.origin.x) * inv_dx;
        tx_max = (_min.x - ray.origin.x) * inv_dx;
    }

    // Y plane
    double inv_dy = 1.0 / ray.direction.y;
    if (inv_dy >= 0) {
        ty_min = (_min.y - ray.origin.y) * inv_dy;
        ty_max = (_max.y - ray.origin.y) * inv_dy;
    } else {
        ty_min = (_max.y - ray.origin.y) * inv_dy;
        ty_max = (_min.y - ray.origin.y) * inv_dy;
    }

    // Z plane
    double inv_dz = 1.0 / ray.direction.z;
    if (inv_dz >= 0) {
        tz_min = (_min.z - ray.origin.z) * inv_dz;
        tz_max = (_max.z - ray.origin.z) * inv_dz;
    } else {
        tz_min = (_max.z - ray.origin.z) * inv_dz;
        tz_max = (_min.z - ray.origin.z) * inv_dz;
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

    // if hit
    if (t0 < t1 && t1 > Constants::k_epsilon) {
        // if outside box
        if (t0 > Constants::k_epsilon)
            tmin = t0;
        else
            tmin = t1;
        return true;
    }
    return false;
}
