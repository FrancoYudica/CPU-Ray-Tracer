#include "World.hpp"
#include "Constants.hpp"
#include "geometric_objects/Plane.hpp"
#include <iostream>

using namespace RT;

void World::build()
{
    // Clears previous build
    // [TODO] remove lights too
    root_container->clear();

    // Adds all scene objects
    build_function(*this);

    // Recalculates bounding box with new build
    root_container->recalculate_bounding_box();
    _built = true;
}

bool World::render_scene() const
{

    if (!_built) {
        std::cout << "[WARNING] Trying to render_scene and the scene isn't built" << std::endl;
        return false;
    }
    if (!tracer) {
        std::cout << "[WARNING] Tracer not initialized." << std::endl;
        return false;
    }

    if (!camera) {
        std::cout << "[WARNING] Camera not initialized." << std::endl;
        return false;
    }

    camera->setup_camera();
    camera->initialize_buffer(*this);
    camera->render_scene(*this);

    return true;
}

void World::display_pixel(
    const uint32_t row,
    const uint32_t column,
    const RGBColor& pixel_color) const
{
    // Should apply tone mapping, gamma correction and integer mapping
    RGBColor mapped_color = pixel_color;
    if (show_out_of_gamut) {
        if (pixel_color.r > 1.0 || pixel_color.g > 1.0 || pixel_color.b > 1.0) {
            mapped_color = out_of_gamut_color;
        }
    }

    // Gamma correction
    RGBColor color = Math::pow(mapped_color, view_plane.inv_gamma);
    render_buffer->set_pixel(column, row, color);
}

ShadeRec World::hit_objects(const Ray& ray) const
{

    ShadeRec sr(this, ray);
    double tmin = Constants::k_huge_value;
    root_container->hit(ray, tmin, sr);
    return sr;
}

/// @brief Returns true if it finds an object along that direction, in range [k_epsilon, max]
bool World::in_shadow(const Ray& ray, float max) const
{
    double tmin = max;
    return root_container->shadow_hit(ray, tmin);
}
