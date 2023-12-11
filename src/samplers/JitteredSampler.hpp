#ifndef __RT_JITTERED_SAMPLER__
#define __RT_JITTERED_SAMPLER__
#include "../Sampler.hpp"

namespace RT {
namespace Samplers {
    class JitteredSampler : public Sampler {
    public:
        JitteredSampler(uint32_t samples)
            : Sampler(SamplerType::Jittered)
        {
            _num_samples = samples;
            _num_sets = 87;
            _count = 0;
        }
        void generate_samples() override;
    };
}
}

#endif