#ifndef __RT_REGULAR_SAMPLER__
#define __RT_REGULAR_SAMPLER__
#include "../Sampler.hpp"

namespace RT {
namespace Samplers {
    class RegularSampler : public Sampler {
    public:
        RegularSampler(uint32_t samples)
            : Sampler(SamplerType::Regular)
        {
            /// Required: samples should be the square of a number
            _num_samples = samples;
            _num_sets = 87;
            _count = 0;
        }
        void generate_samples() override
        {
            _samples.reserve(_num_sets * _num_samples);
            uint32_t n = sqrt(_num_samples);

            for (uint32_t set = 0; set < _num_sets; set++) {
                for (uint32_t i = 0; i < n; i++) {
                    for (uint32_t j = 0; j < n; j++) {
                        Vec2 sample(
                            (i + 0.5f) / n,
                            (j + 0.5f) / n);
                        _samples.push_back(sample);
                    }
                }
            }
        }
    };
}
}

#endif