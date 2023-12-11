#ifndef __RT_WORLD__
#define __RT_WORLD__
#include "Camera.hpp"
#include "Light.hpp"
#include "RenderBuffer.hpp"
#include "Tracer.hpp"
#include "Types_rt.hpp"
#include "ViewPlane.hpp"
#include "geometric_objects/Container.hpp"
#include <functional>
#include <memory>
#include <vector>

namespace RT {

typedef std::function<void(World&)> WorldBuildFunction;
class World {

public:
    ViewPlane view_plane;
    RGBColor background_color;
    std::shared_ptr<Tracer> tracer;
    WorldBuildFunction build_function;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Light> ambient_light;
    std::vector<std::shared_ptr<Light>> lights;
    mutable std::shared_ptr<RenderBuffer> render_buffer;
    bool show_out_of_gamut;
    RGBColor out_of_gamut_color;
    std::shared_ptr<GeometricObjects::Container> root_container;

public:
    World(const World& world) = delete;
    World()
        : background_color(Constants::BLACK)
        , out_of_gamut_color(Constants::RED)
        , show_out_of_gamut(false)
        , tracer(nullptr)
        , camera(nullptr)
        , ambient_light(nullptr)
    {
        root_container = std::make_shared<GeometricObjects::Container>();
    }
    inline void add_object(const GeometricObjectPtr& object) { root_container->add(object); }
    inline void add_light(const std::shared_ptr<Light>& light) { lights.push_back(light); }
    inline void set_tracer(std::shared_ptr<Tracer> tracer) { this->tracer = tracer; }
    inline void set_camera(std::shared_ptr<Camera> camera) { this->camera = camera; }
    inline void set_build(const WorldBuildFunction& build) { this->build_function = build; }
    inline void set_render_buffer(const std::shared_ptr<RenderBuffer>& buffer) const { render_buffer = buffer; }
    inline void set_ambient_light(const std::shared_ptr<Light>& light) { ambient_light = light; }
    inline void set_out_of_gamut_color(const RGBColor& color) { out_of_gamut_color = color; }
    void build();
    bool render_scene() const;
    ShadeRec hit_objects(const Ray& ray) const;
    bool in_shadow(const Ray& ray, float max = Constants::k_huge_value) const;

    void display_pixel(
        const uint32_t row,
        const uint32_t column,
        const RGBColor& pixel_color) const;

private:
    bool _built;
};
}

#endif