#include "Sampler.hpp"
#include "Random.hpp"
#include <algorithm>

using namespace RT;

Vec2 Sampler::sample_unit_square()
{

    // For each new pixel
    if (_count % _num_samples == 0) {
        // Stores a random set offset. _jump ranges in [0, _num_sets * _num_samples - _num_samples]
        _jump = (RT::Random::random_int() % _num_sets) * _num_samples;
    }

    // Uses shuffled indices, this way 2 different Samplers can't have the same
    // linear sequence of samples
    return _samples[_jump + _shuffled_indices[_jump + _count++ % _num_samples]];
}

Vec2 Sampler::sample_unit_disk()
{
    // Same as sample_unit_square, but _disk_samples is used
    if (_count % _num_samples == 0)
        _jump = (RT::Random::random_int() % _num_sets) * _num_samples;
    return _disk_samples[_jump + _shuffled_indices[_jump + _count++ % _num_samples]];
}

Vec3f Sampler::sample_unit_hemisphere(const Vec3f& u, const Vec3f& v, const Vec3f& w)
{
    // Same as sample_unit_square, but _disk_samples is used
    if (_count % _num_samples == 0)
        _jump = (RT::Random::random_int() % _num_sets) * _num_samples;

    Vec3f& p = _hemisphere_samples[_jump + _shuffled_indices[_jump + _count++ % _num_samples]];
    return p.x * u + p.y * v + p.z * w;
}

void Sampler::setup_shuffled_indices()
{
    /*
    Shuffled indices stores random indices for each sample. Those indices
    ranges in [0, 1, 2, ..., _num_samples - 1]. Note that for each set we
    shuffle and then add the indices to _shuffled_indices, this way different
    sets have different indices
    */

    _shuffled_indices.reserve(_num_samples * _num_sets);

    std::vector<uint32_t> indices;
    indices.reserve(_num_samples);

    // Adds indices [0, 1, 2, ..., _num_samples - 1]
    for (uint32_t i = 0; i < _num_samples; i++)
        indices.push_back(i);

    for (uint32_t set = 0; set < _num_sets; set++) {
        // Shuffles indices
        std::random_shuffle(indices.begin(), indices.end());

        // Adds all the samples of the set
        for (uint32_t sample = 0; sample < _num_samples; sample++)
            _shuffled_indices.push_back(indices[sample]);
    }

    std::random_shuffle(indices.begin(), indices.end());
}

void Sampler::map_samples_to_unit_disk()
{
    _mode = SampleMode::Disk;
    // Maps the previously generated samples to a unit disk
    // and stores them in _disk_samples vector
    // The points have Math::magnitude in range [0, 1], inside unit disk

    // samples should be already generated
    uint32_t samples_size = _samples.size();
    _disk_samples.reserve(samples_size);

    Vec2 sample_point;

    // Polar coordinates
    float radius, angle;

    for (uint32_t i = 0; i < samples_size; i++) {
        // Maps sample point to range [-1.0, 1.0]
        sample_point = 2.0 * _samples[i] - 1.0;

        if (sample_point.x > -sample_point.y) // Sectors 1 and 2
        {
            if (sample_point.x > sample_point.y) // Sector 1
            {
                radius = sample_point.x;
                angle = sample_point.y / sample_point.x;
            } else // Sector 2
            {
                radius = sample_point.y;
                angle = 2.0f - sample_point.x / sample_point.y;
            }
        } else // Sectors 3 and 4
        {
            if (sample_point.x < sample_point.y) {
                radius = -sample_point.x;
                angle = 4.0f + sample_point.y / sample_point.x;
            } else {
                radius = -sample_point.y;
                // Avoids division by zero
                if (sample_point.y != 0.0f)
                    angle = 6.0f - sample_point.x / sample_point.y;
                else
                    angle = 0.0f;
            }
        }
        angle *= M_PI_4;
        _disk_samples.push_back(
            Vec2(
                radius * cosf(angle),
                radius * sinf(angle)));
    }
}

void Sampler::map_samples_to_hemisphere(const float e)
{
    _mode = SampleMode::Hemisphere;
    _e = e;

    uint32_t samples_size = _samples.size();
    _hemisphere_samples.reserve(samples_size);
    for (uint32_t i = 0; i < samples_size; i++) {
        const Vec2& sample = _samples[i];

        float cos_phi = cosf(2.0f * M_PI * sample.x);
        float sin_phi = sinf(2.0f * M_PI * sample.x);
        float cos_theta = powf((1.0f - sample.y), 1.0f / (e + 1.0f));
        float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);

        // Stores coefficients used in the linear combination
        float pu = sin_theta * cos_phi;
        float pv = sin_theta * sin_phi;
        float pw = cos_theta;
        _hemisphere_samples.push_back(Vec3f(pu, pv, pw));
    }
}
