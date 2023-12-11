#include "JitteredPointLight.hpp"
#include "../ShadeRec.hpp"
#include "../World.hpp"
#include "../samplers/MultiJitteredSampler.hpp"
#include "../samplers/RegularSampler.hpp"

using namespace RT;
using namespace Lights;

void JitteredPointLight::set_sampler(std::shared_ptr<Sampler> sampler)
{
    _sampler = sampler;
    _sampler->generate_samples();
    _sampler->setup_shuffled_indices();
}

void JitteredPointLight::set_samples(uint32_t samples)
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

Vec3 JitteredPointLight::get_direction(const ShadeRec& sr)
{
    Vec2 sample = _sampler->sample_unit_square();

    // XZ plane rotation
    double phi = sample.x * Constants::PI_2;

    // Y axis and XZ plane rotation
    double theta = sample.y * Constants::PI;

    double dy = cos(theta);
    double sin_theta = sin(theta);
    double dx = cos(phi) * sin_theta;
    double dz = sin(phi) * sin_theta;
    _last_sample = _origin + _radius * Vec3(dx, dy, dz);

    return Math::normalize(_last_sample - sr.hit_point);
}

RGBColor JitteredPointLight::L(const ShadeRec& sr)
{
    float attenuation = _ls / std::pow(Math::magnitude(sr.hit_point - _last_sample), _k);
    return attenuation * _color;
}

bool JitteredPointLight::in_shadow(const Ray& ray, const ShadeRec& sr)
{

    // Ray direction isn't facing the normal
    Vec3 to_light = _last_sample - sr.hit_point;
    float distance = Math::magnitude(to_light);
    to_light /= distance;

    // When surface hemisphere isn't facing light direct
    // illumination can't reach that surface point
    if (Math::dot(sr.get_normal(), to_light) < 0.0f)
        return false;

    return sr.world->in_shadow(ray, distance);
}
