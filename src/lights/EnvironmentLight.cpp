#include "EnvironmentLight.hpp"
#include "../ShadeRec.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Lights;

void EnvironmentLight::set_sampler(std::shared_ptr<Sampler> sampler)
{
    _sampler = sampler;
    _sampler->generate_samples();
    _sampler->setup_shuffled_indices();
    _sampler->map_samples_to_hemisphere(1.0);
}

void EnvironmentLight::set_samples(uint32_t samples)
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

bool EnvironmentLight::in_shadow(const Ray& ray, const ShadeRec& sr)
{
    return sr.world->in_shadow(ray);
}

Vec3 EnvironmentLight::get_direction(const ShadeRec& sr)
{

    // Calculates orthonormal basis
    Vec3 normal = sr.get_normal();
    Vec3 w = normal;
    Vec3 v = Math::normalize(cross(w, Constants::JITTERED_UP));
    Vec3 u = cross(v, w);
    Vec3 d = _sampler->sample_unit_hemisphere(u, v, w);
    return d;
}

RGBColor EnvironmentLight::L(const ShadeRec& sr)
{
    return _environment_material->get_Le();
}
