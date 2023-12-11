#include "JitteredSampler.hpp"
#include "../Random.hpp"

using namespace RT::Samplers;

void JitteredSampler::generate_samples()
{
    _samples.reserve(_num_sets * _num_samples);
    uint32_t n = sqrt(_num_samples);

    for (uint32_t set = 0; set < _num_sets; set++) {
        for (uint32_t i = 0; i < n; i++) {
            for (uint32_t j = 0; j < n; j++) {
                Vec2 sample(
                    (i + RT::Random::unit_float()) / n,
                    (j + RT::Random::unit_float()) / n);
                _samples.push_back(sample);
            }
        }
    }
}