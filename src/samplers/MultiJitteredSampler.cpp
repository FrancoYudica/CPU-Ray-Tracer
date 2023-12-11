#include "MultiJitteredSampler.hpp"
#include "../Random.hpp"

using namespace RT::Samplers;

void MultiJitteredSampler::generate_samples()
{
    _samples.reserve(_num_sets * _num_samples);
    uint32_t n = sqrt(_num_samples);

    for (uint32_t set = 0; set < _num_sets; set++) {

        // Loops through all the X boxes
        uint32_t base = 0;
        for (uint32_t i = 0; i < _num_samples; i++) {
            uint32_t current_j = base + (i * n) % _num_samples;
            Vec2 sample(
                (i + RT::Random::unit_float()) / _num_samples,
                (current_j + RT::Random::unit_float()) / _num_samples);
            _samples.push_back(sample);

            // Base is increased every n iterations
            if ((i + 1) % n == 0)
                base++;
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