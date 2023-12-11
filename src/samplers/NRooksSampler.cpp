#include "NRooksSampler.hpp"
#include "../Random.hpp"

using namespace RT::Samplers;

void NRooksSampler::generate_samples()
{
    _samples.reserve(_num_sets * _num_samples);

    // Generates the diagonal samples
    for (uint32_t set = 0; set < _num_sets; set++) {
        for (uint32_t i = 0; i < _num_samples; i++) {
            Vec2 sample(
                (i + RT::Random::unit_float()) / _num_samples,
                (i + RT::Random::unit_float()) / _num_samples);
            _samples.push_back(sample);
        }
    }

    // Shuffle X coordinate
    for (uint32_t set_index = 0; set_index < _num_sets; set_index++) {
        for (uint32_t i = 0; i < _num_samples; i++) {

            int32_t current_index = set_index * _num_samples + i;

            // Take random index
            int32_t sample_index = RT::Random::random_int() % _num_samples;
            int32_t swap_index = sample_index + set_index * _num_samples;
            std::swap(_samples[current_index].x, _samples[swap_index].x);
        }
    }

    // Shuffle Y coordinate
    for (uint32_t set_index = 0; set_index < _num_sets; set_index++) {
        for (uint32_t i = 0; i < _num_samples; i++) {

            int32_t current_index = set_index * _num_samples + i;

            // Take random index
            int32_t sample_index = RT::Random::random_int() % _num_samples;
            int32_t swap_index = sample_index + set_index * _num_samples;

            std::swap(_samples[current_index].y, _samples[swap_index].y);
        }
    }
}