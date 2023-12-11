#ifndef __RT_BUILD_FUNCTIONS__
#define __RT_BUILD_FUNCTIONS__
#include "Instance.hpp"
#include "Math_rt.hpp"
#include "World.hpp"
#include "geometric_objects/GeometricObjects.hpp"

#include "samplers/NRooksSampler.hpp"
#include "tracers/AreaLighting.hpp"
#include "tracers/RayCastTracer.hpp"

#include "cameras/AnaglyphCamera.hpp"
#include "cameras/OrthographicCamera.hpp"
#include "cameras/PinholeCamera.hpp"
#include "cameras/StereoCamera.hpp"
#include "cameras/ThinLensCamera.hpp"

#include "lights/Lights.hpp"

#include "materials/EmissiveMaterial.hpp"
#include "materials/MatteMaterial.hpp"
#include "materials/PhongMaterial.hpp"

#include "Constants.hpp"

namespace RT {
namespace BuildFunctions {

    /// @brief Sets up an common environment for testing
    static void setup_test_scene(World& world, int num_samples)
    {
        // Sets view plane ----------------------------------
        ViewPlane view_plane;
        uint32_t horizontal_resolution = 400;
        uint32_t vertical_resolution = 400;
        view_plane.set_hres(horizontal_resolution);
        view_plane.set_vres(vertical_resolution);
        view_plane.set_samples(num_samples);
        world.view_plane = view_plane;
        world.background_color = Constants::BLACK;

        // Tracer
        world.set_tracer(std::make_shared<Tracers::AreaLighting>(world));

        // Ambient light
        auto ambient_occluder = std::make_shared<Lights::AmbientOccluder>();
        ambient_occluder->scale_radiance(1.0);
        ambient_occluder->set_color(RGBColor(46.0 / 255.0));
        ambient_occluder->set_min_intensity(0.0f);
        ambient_occluder->set_samples(num_samples);
        world.set_ambient_light(ambient_occluder);

        // Pinhole camera
        auto camera = std::make_shared<Cameras::PinholeCamera>();
        camera->set_eye({ 2, 5, 7 });
        camera->set_look_at({ 0, 1, 0 });
        camera->set_view_distance(200);
        camera->setup_camera();
        world.set_camera(camera);
    }

    static void build_instance_test(World& world)
    {
        int num_samples = 1;

        // Sets view plane ----------------------------------
        ViewPlane view_plane;
        uint32_t horizontal_resolution = 400;
        uint32_t vertical_resolution = 400;
        view_plane.set_hres(horizontal_resolution);
        view_plane.set_vres(vertical_resolution);
        view_plane.set_samples(num_samples);
        world.view_plane = view_plane;
        world.background_color = Constants::BLACK;

        // Tracer
        world.set_tracer(std::make_shared<Tracers::AreaLighting>(world));

        // Ambient light
        auto ambient_occluder = std::make_shared<Lights::AmbientOccluder>();
        ambient_occluder->scale_radiance(1.0);
        ambient_occluder->set_color(RGBColor(46.0 / 255.0));
        ambient_occluder->set_min_intensity(0.0f);
        ambient_occluder->set_samples(num_samples);
        world.set_ambient_light(ambient_occluder);

        // Pinhole camera
        auto camera = std::make_shared<Cameras::PinholeCamera>();
        camera->set_eye({ 1.7, 1.7, 9 });
        camera->set_look_at({ 1.6, 1.5, 8 });
        camera->set_view_distance(550);
        camera->setup_camera();
        world.set_camera(camera);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.5);
        phong_mtl->set_kd(0.25);
        phong_mtl->set_ks(0.25);
        phong_mtl->set_ca(Vec3(1.0, 0.5, 0.7));
        phong_mtl->set_cd(Vec3(1.0, 0.5, 0.7));
        phong_mtl->set_cs(Vec3(1.0, 0.5, 0.7));

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);
        // Geometric objects
        auto cylinder = std::make_shared<GeometricObjects::Sphere>();
        cylinder->set_material(phong_mtl);

        double scale = 1.0f;
        uint32_t size = 3;
        for (uint32_t i = 0; i < size; i++) {
            for (uint32_t j = 0; j < size; j++) {
                auto instance = std::make_shared<Instance>(cylinder);
                instance->set_translation(Vec3(2.0 * i, 1, 2.0 * j));
                // instance->set_scale(Vec3(scale));
                world.add_object(instance);
            }
        }

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0, -2.0, 0.0),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        auto environment_material = std::make_shared<Materials::Emissive>();

        // Environment sphere. Has uses environment material
        {
            auto sphere = std::make_shared<GeometricObjects::Sphere>();
            sphere->set_normal_inwards();
            sphere->set_radius(10000.0);
            sphere->disable_shadows();
            sphere->set_material(environment_material);
            world.add_object(sphere);
        }

        // Environment light
        {
            auto environment_light = std::make_shared<Lights::EnvironmentLight>();
            environment_light->set_material(environment_material);
            environment_light->set_samples(num_samples);
            world.add_light(environment_light);
        }

        // Directional sun light
        {
            auto directional_sun = std::make_shared<Lights::JitteredDirectionalLight>();
            directional_sun->set_direction(Math::normalize(Vec3(1, -1, 0)));
            directional_sun->set_theta(0.25 * Constants::PI_OVER_4);
            directional_sun->set_samples(num_samples);
            world.add_light(directional_sun);
        }
    }

    static void build_instance_test_bvh(World& world)
    {
        int num_samples = 1;

        // Sets view plane ----------------------------------
        ViewPlane view_plane;
        uint32_t horizontal_resolution = 400;
        uint32_t vertical_resolution = 400;
        view_plane.set_hres(horizontal_resolution);
        view_plane.set_vres(vertical_resolution);
        view_plane.set_samples(num_samples);
        world.view_plane = view_plane;
        world.background_color = Constants::BLACK;

        // Tracer
        world.set_tracer(std::make_shared<Tracers::AreaLighting>(world));

        // Ambient light
        auto ambient_occluder = std::make_shared<Lights::AmbientOccluder>();
        ambient_occluder->scale_radiance(1.0);
        ambient_occluder->set_color(RGBColor(46.0 / 255.0));
        ambient_occluder->set_min_intensity(0.0f);
        ambient_occluder->set_samples(num_samples);
        world.set_ambient_light(ambient_occluder);

        // Pinhole camera
        auto camera = std::make_shared<Cameras::PinholeCamera>();
        camera->set_eye({ 10, 29, 60 });
        camera->set_look_at({ 0, 2, 0 });
        camera->set_view_distance(550);
        camera->setup_camera();
        world.set_camera(camera);

        // Materials
        auto phong_material_1 = std::make_shared<Materials::Phong>();
        phong_material_1->set_ka(0.5);
        phong_material_1->set_kd(0.25);
        phong_material_1->set_ks(0.25);
        phong_material_1->set_ca(Vec3(1.0, 0.5, 0.7));
        phong_material_1->set_cd(Vec3(1.0, 0.5, 0.7));
        phong_material_1->set_cs(Vec3(1.0, 0.5, 0.7));

        auto phong_material_2 = std::make_shared<Materials::Phong>();
        phong_material_2->set_ka(0.5);
        phong_material_2->set_kd(0.25);
        phong_material_2->set_ks(0.25);
        phong_material_2->set_ca(Vec3(0.3, 0.8, 0.7));
        phong_material_2->set_cd(Vec3(0.3, 0.8, 0.7));
        phong_material_2->set_cs(Vec3(0.3, 0.8, 0.7));

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects
        auto sphere1 = std::make_shared<GeometricObjects::Sphere>();
        sphere1->set_material(phong_material_1);
        auto sphere2 = std::make_shared<GeometricObjects::Capsule>();
        sphere2->set_material(phong_material_2);

        std::vector<GeometricObjectPtr> base_objects = {
            sphere1,
            sphere2
        };

        auto bvh = std::make_shared<GeometricObjects::BVH>();
        double scale = 1.0f;
        double spacing = 3 * scale;
        uint32_t size = 10;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                uint32_t base_object_index = rand() % base_objects.size();
                auto instance = std::make_shared<Instance>(base_objects[base_object_index]);
                instance->set_translation(Vec3(spacing * (i - size / 2), 1, spacing * (j - size / 2)));
                // instance->set_scale(Vec3(scale));
                bvh->add(instance);
                // world.add_object(instance);
            }
        }

        bvh->build_tree();
        world.add_object(bvh);
        //  - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0, -2.0, 0.0),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        auto environment_material = std::make_shared<Materials::Emissive>();

        // Environment sphere. Has uses environment material
        {
            auto sphere = std::make_shared<GeometricObjects::Sphere>();
            sphere->set_normal_inwards();
            sphere->set_radius(10000.0);
            sphere->disable_shadows();
            sphere->set_material(environment_material);
            world.add_object(sphere);
        }

        // Environment light
        {
            auto environment_light = std::make_shared<Lights::EnvironmentLight>();
            environment_light->set_material(environment_material);
            environment_light->set_samples(num_samples);
            world.add_light(environment_light);
        }

        // Directional sun light
        {
            auto directional_sun = std::make_shared<Lights::JitteredDirectionalLight>();
            directional_sun->set_direction(Math::normalize(Vec3(1, -1, 0)));
            directional_sun->set_theta(0.25 * Constants::PI_OVER_4);
            directional_sun->set_samples(num_samples);
            world.add_light(directional_sun);
        }
    }

    static void build_environment_light_test(World& world)
    {
        int num_samples = 1;

        // Sets view plane ----------------------------------
        ViewPlane view_plane;
        uint32_t horizontal_resolution = 400;
        uint32_t vertical_resolution = 400;
        view_plane.set_hres(horizontal_resolution);
        view_plane.set_vres(vertical_resolution);
        view_plane.set_samples(num_samples);
        world.view_plane = view_plane;
        world.background_color = Constants::BLACK;

        // Tracer
        world.set_tracer(std::make_shared<Tracers::AreaLighting>(world));

        // Ambient light
        auto ambient_occluder = std::make_shared<Lights::AmbientOccluder>();
        ambient_occluder->scale_radiance(1.0);
        ambient_occluder->set_color(RGBColor(46.0 / 255.0));
        ambient_occluder->set_min_intensity(0.0f);
        ambient_occluder->set_samples(num_samples);
        world.set_ambient_light(ambient_occluder);

        // Pinhole camera
        auto camera = std::make_shared<Cameras::PinholeCamera>();
        camera->set_eye({ 1.7, 1.7, 9 });
        camera->set_look_at({ 1.6, 1.5, 8 });
        camera->set_view_distance(550);
        camera->setup_camera();
        world.set_camera(camera);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.5);
        phong_mtl->set_kd(0.25);
        phong_mtl->set_ks(0.25);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects
        auto cylinder = std::make_shared<GeometricObjects::Capsule>();
        cylinder->set_material(phong_mtl);
        world.add_object(cylinder);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0, -2.0, 0.0),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        auto environment_material = std::make_shared<Materials::Emissive>();

        // Environment sphere. Has uses environment material
        {
            auto sphere = std::make_shared<GeometricObjects::Sphere>();
            sphere->set_normal_inwards();
            sphere->set_radius(10000.0);
            sphere->disable_shadows();
            sphere->set_material(environment_material);
            world.add_object(sphere);
        }

        // Environment light
        {
            auto environment_light = std::make_shared<Lights::EnvironmentLight>();
            environment_light->set_material(environment_material);
            environment_light->set_samples(num_samples);
            world.add_light(environment_light);
        }

        // Directional sun light
        {
            auto directional_sun = std::make_shared<Lights::JitteredDirectionalLight>();
            directional_sun->set_direction(Math::normalize(Vec3(1, -1, 0)));
            directional_sun->set_theta(0.25 * Constants::PI_OVER_4);
            directional_sun->set_samples(num_samples);
            world.add_light(directional_sun);
        }
    }
    static void build_objects_test(World& world)
    {
        int num_samples = 16;
        // Sets view plane ----------------------------------
        ViewPlane view_plane;
        uint32_t horizontal_resolution = 400;
        uint32_t vertical_resolution = 400;
        view_plane.set_hres(horizontal_resolution);
        view_plane.set_vres(vertical_resolution);
        view_plane.set_samples(num_samples);
        world.view_plane = view_plane;
        world.background_color = Constants::BLACK;

        // Tracer
        world.set_tracer(std::make_shared<Tracers::AreaLighting>(world));

        // Ambient light
        auto ambient_occluder = std::make_shared<Lights::AmbientOccluder>();
        ambient_occluder->scale_radiance(1.0);
        ambient_occluder->set_color(RGBColor(46.0 / 255.0));
        ambient_occluder->set_min_intensity(0.0f);
        ambient_occluder->set_samples(num_samples);
        world.set_ambient_light(ambient_occluder);

        // Pinhole camera
        auto camera = std::make_shared<Cameras::PinholeCamera>();
        camera->set_eye({ 30, 26, 55 });
        camera->set_look_at({ 0, 1, 0 });
        camera->set_view_distance(4000);
        camera->setup_camera();
        world.set_camera(camera);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects

        Vec3 size(1.0);
        Vec3 box_origin = Vec3(0, 2, 0);
        auto box = std::make_shared<GeometricObjects::Box>(
            box_origin - size * .5,
            box_origin + size * .5);

        box->set_material(phong_mtl);
        world.add_object(box);

        auto sphere2 = std::make_shared<GeometricObjects::Sphere>(
            Vec3(3, 1, 2),
            1.0);
        sphere2->set_material(phong_mtl);
        world.add_object(sphere2);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::YELLOW);
            emissive_material->scale_radiance(4.0);

            // Emissive sphere
            auto emissive_rect = std::make_shared<GeometricObjects::Rect>(
                Vec3(-3, 0.5, 0),
                Vec3(0, 0, -1),
                Vec3(0, 1, 0));

            emissive_rect->set_material(emissive_material);
            world.add_object(emissive_rect);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_rect->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(
                emissive_rect);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

    static void build_cylinder_test(World& world)
    {
        int num_samples = 1;
        setup_test_scene(world, num_samples);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects
        auto cylinder = std::make_shared<GeometricObjects::Capsule>();
        cylinder->set_material(phong_mtl);
        world.add_object(cylinder);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }
    static void build_cone_test(World& world)
    {
        int num_samples = 1;
        setup_test_scene(world, num_samples);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects
        auto cone = std::make_shared<GeometricObjects::SolidCone>();
        cone->set_material(phong_mtl);
        world.add_object(cone);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

    static void build_thick_annulus_test(World& world)
    {
        int num_samples = 1;
        setup_test_scene(world, num_samples);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects
        auto cone = std::make_shared<GeometricObjects::ThickAnnulus>();
        cone->set_material(phong_mtl);
        world.add_object(cone);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

    static void build_part_cylinder_test(World& world)
    {
        int num_samples = 36;
        setup_test_scene(world, num_samples);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects

        auto cylinder = std::make_shared<GeometricObjects::PartCylinder>();
        cylinder->set_material(phong_mtl);
        world.add_object(cylinder);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            // auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
            //     0.75,
            //     Vec3(1, 3.5, -1),
            //     Math::normalize(Vec3(0, -1, 1)));

            auto emissive_disk = std::make_shared<GeometricObjects::Annulus>(
                0.25,
                0.75,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);
            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

    static void build_part_sphere_test(World& world)
    {
        int num_samples = 1;
        setup_test_scene(world, num_samples);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects

        auto sphere = std::make_shared<GeometricObjects::PartSphere>();
        sphere->set_material(phong_mtl);
        world.add_object(sphere);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f, -1.0f, 0.0f),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

    static void build_part_torus_test(World& world)
    {
        int num_samples = 1;
        setup_test_scene(world, num_samples);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto torus = std::make_shared<GeometricObjects::PartTorus>();
        torus->set_material(phong_mtl);
        torus->set_normal_flip();
        world.add_object(torus);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f, -1.0f, 0.0f),
            Vec3(0, 1, 0));
        plane->set_material(phong_mtl);
        plane->set_normal_flip();

        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

    static void build_compound_box_test(World& world)
    {
        int num_samples = 1;
        setup_test_scene(world, num_samples);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto box = std::make_shared<GeometricObjects::CompoundBox>();
        box->set_material(phong_mtl);
        world.add_object(box);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f, -1.0f, 0.0f),
            Vec3(0, 1, 0));
        plane->set_material(phong_mtl);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

    static void build_solid_cylinder_test(World& world)
    {
        int num_samples = 1;
        setup_test_scene(world, num_samples);

        auto material = std::make_shared<Materials::Matte>();
        material->set_ka(0.75);
        material->set_kd(0.25);
        material->set_ca(Constants::WHITE);

        // Geometric objects

        auto cylinder = std::make_shared<GeometricObjects::Capsule>();
        cylinder->set_material(material);
        world.add_object(cylinder);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f, -2.0f, 0.0f),
            Vec3(0, 1, 0));
        plane->set_material(material);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }
    static void build_torus_test(World& world)
    {
        int num_samples = 1;
        setup_test_scene(world, num_samples);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Geometric objects

        auto torus = std::make_shared<GeometricObjects::Torus>();
        torus->set_material(phong_mtl);
        world.add_object(torus);

        auto sphere2 = std::make_shared<GeometricObjects::Sphere>(
            Vec3(3, 1, 2),
            1.0);
        sphere2->set_material(phong_mtl);
        world.add_object(sphere2);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.75f,
                Vec3(1, 3.5, -1),
                Math::normalize(Vec3(0, -1, 1)));

            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::YELLOW);
            emissive_material->scale_radiance(4.0);

            // Emissive sphere
            auto emissive_rect = std::make_shared<GeometricObjects::Rect>(
                Vec3(-3, 0.5, 0),
                Vec3(0, 0, -1),
                Vec3(0, 1, 0));

            emissive_rect->set_material(emissive_material);
            world.add_object(emissive_rect);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_rect->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(
                emissive_rect);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

    static void build_triangle_test(World& world)
    {
        int num_samples = 16;
        // Sets view plane ----------------------------------
        setup_test_scene(world, num_samples);

        // Pinhole camera
        auto camera = std::make_shared<Cameras::PinholeCamera>();
        camera->set_eye({ 1.8, 2, 3 });
        camera->set_look_at({ 0, 1, 0 });
        camera->set_view_distance(200);
        camera->setup_camera();
        world.set_camera(camera);

        // Materials
        auto phong_mtl = std::make_shared<Materials::Phong>();
        phong_mtl->set_ka(0.7);
        phong_mtl->set_kd(0.2);
        phong_mtl->set_ks(0.1);
        phong_mtl->set_ca(Constants::WHITE);
        phong_mtl->set_cd(Constants::WHITE);
        phong_mtl->set_cs(Constants::WHITE);

        auto matte_2 = std::make_shared<Materials::Matte>();
        matte_2->set_ka(0.75);
        matte_2->set_kd(0.25);
        matte_2->set_ca(Constants::WHITE);

        // Creates two half tetrahedrons
        Vec3 bottom = Vec3(0, 0, 0);
        double base_width = 2.0;
        double half_width = base_width * 0.5;
        double height = 3;
        Vec3 v0 = bottom + Vec3(0, height, 0);
        Vec3 v1 = bottom + Vec3(+half_width, height * 0.5, +half_width);
        Vec3 v2 = bottom + Vec3(+half_width, height * 0.5, -half_width);
        Vec3 v3 = bottom + Vec3(-half_width, height * 0.5, +half_width);
        Vec3 v4 = bottom;

        auto triangle0 = std::make_shared<GeometricObjects::Triangle>(
            v0,
            v1,
            v2);

        auto triangle1 = std::make_shared<GeometricObjects::Triangle>(
            v0,
            v3,
            v1);

        auto triangle2 = std::make_shared<GeometricObjects::Triangle>(
            v4,
            v2,
            v1);

        auto triangle3 = std::make_shared<GeometricObjects::Triangle>(
            v4,
            v1,
            v3);

        triangle0->set_material(phong_mtl);
        triangle1->set_material(phong_mtl);
        triangle2->set_material(phong_mtl);
        triangle3->set_material(phong_mtl);
        world.add_object(triangle0);
        world.add_object(triangle1);
        world.add_object(triangle2);
        world.add_object(triangle3);

        // - Plane
        auto plane = std::make_shared<GeometricObjects::Plane>(
            Vec3(0.0f),
            Vec3(0, 1, 0));
        plane->set_material(matte_2);
        world.add_object(plane);

        // Emissive material
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::GREEN);
            emissive_material->scale_radiance(4.0);

            auto emissive_triangle = std::make_shared<GeometricObjects::Triangle>(
                Vec3(0, Constants::k_epsilon, 0),
                Vec3(2, Constants::k_epsilon, 0),
                Vec3(2, Constants::k_epsilon, -2));

            emissive_triangle->set_material(emissive_material);
            world.add_object(emissive_triangle);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_triangle->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(emissive_triangle);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
        // Disk
        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::YELLOW);
            emissive_material->scale_radiance(4.0);

            auto emissive_triangle = std::make_shared<GeometricObjects::Triangle>(
                Vec3(0, Constants::k_epsilon, 0),
                Vec3(0, Constants::k_epsilon, 2),
                Vec3(2, Constants::k_epsilon, 2));

            emissive_triangle->set_material(emissive_material);
            world.add_object(emissive_triangle);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_triangle->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(
                emissive_triangle);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }

        {
            auto emissive_material = std::make_shared<Materials::Emissive>();
            emissive_material->set_ce(Constants::WHITE);
            emissive_material->scale_radiance(4.0);

            auto emissive_disk = std::make_shared<GeometricObjects::Disk>(
                0.5,
                Vec3(0, 4, 0),
                Math::normalize(Vec3(0.5, -1, 0)));
            emissive_disk->set_material(emissive_material);
            world.add_object(emissive_disk);

            // Sets surface sampler
            auto surface_sampler = std::make_shared<Samplers::MultiJitteredSampler>(num_samples);
            emissive_disk->set_surface_sampler(surface_sampler);

            // Area light
            auto area_light = std::make_shared<Lights::AreaLight>(
                emissive_disk);
            area_light->set_casts_shadows(true);
            area_light->set_fall_off_power(0.1);
            world.add_light(area_light);
        }
    }

}
}

#endif