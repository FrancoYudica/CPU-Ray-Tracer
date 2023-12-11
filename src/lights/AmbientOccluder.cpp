#include "AmbientOccluder.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Lights;

void AmbientOccluder::set_sampler(std::shared_ptr<Sampler> sampler)
{
    this->sampler = sampler;
    sampler->generate_samples();
    sampler->setup_shuffled_indices();
    sampler->map_samples_to_hemisphere(1);
}

void AmbientOccluder::set_samples(uint32_t samples)
{
    // Multi jittered sampler only works properly with
    // perfect square samples
    bool perfect_square = Math::IsPerfectSquare(samples);

    std::shared_ptr<Sampler> sampler;
    if (perfect_square)
        sampler = std::make_shared<Samplers::MultiJitteredSampler>(samples);
    else {
        sampler = std::make_shared<Samplers::RegularSampler>(samples);
        std::cout << "[Warning]: AmbientOccluder::set_samples(n), n is not perfect square" << std::endl;
    }
    set_sampler(sampler);
}

bool AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr)
{
    return sr.world->in_shadow(ray);
}

Vec3 AmbientOccluder::get_direction(const ShadeRec& sr)
{
    return sampler->sample_unit_hemisphere(u, v, w);
}

RGBColor AmbientOccluder::L(const ShadeRec& sr)
{
    if (!casts_shadows())
        return ls * color;
    // Calculates orthonormal basis
    Vec3 normal = sr.get_normal();
    w = normal;

    v = Math::normalize(cross(w, Constants::JITTERED_UP));
    u = cross(v, w);

    // Gets direction from hemisphere
    Vec3 d = get_direction(sr);

    Ray shadow_ray = {
        sr.hit_point + normal * Constants::k_epsilon,
        d
    };

    // Decreases color
    if (in_shadow(shadow_ray, sr))
        return (min_intensity * ls) * color;

    return ls * color;
}