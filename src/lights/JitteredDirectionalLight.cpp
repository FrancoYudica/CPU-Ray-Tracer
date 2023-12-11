#include "JitteredDirectionalLight.hpp"
#include "../ShadeRec.hpp"
#include "../World.hpp"
#include "../samplers/MultiJitteredSampler.hpp"
#include "../samplers/RegularSampler.hpp"

using namespace RT;
using namespace Lights;

void JitteredDirectionalLight::set_sampler(std::shared_ptr<Sampler> sampler)
{
    _sampler = sampler;
    _sampler->generate_samples();
    _sampler->map_samples_to_unit_disk();
    _sampler->setup_shuffled_indices();
}

void JitteredDirectionalLight::set_samples(uint32_t samples)
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

Vec3 JitteredDirectionalLight::get_direction(const ShadeRec& sr)
{
    Vec2 sample = _sampler->sample_unit_square();
    Vec3 w = _direction;
    Vec3 u = Math::cross(w, Constants::JITTERED_UP);
    Vec3 v = Math::cross(u, w);

    Vec3 sample_plane = sample.x * u + sample.y * v;
    double max_radius = tan(_theta);
    sample_plane *= max_radius;

    _last_sample = Math::normalize(_direction + sample_plane);
    return -_last_sample;
}

RGBColor JitteredDirectionalLight::L(const ShadeRec& sr)
{
    return _ls * _color;
}

bool JitteredDirectionalLight::in_shadow(const Ray& ray, const ShadeRec& sr)
{
    Vec3 to_light = -_last_sample;
    if (Math::dot(sr.get_normal(), to_light) < 0.0f)
        return false;

    return sr.world->in_shadow(ray);
}
