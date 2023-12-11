#ifndef __RT_MULTI_JITTERED_SAMPLER__
#define __RT_MULTI_JITTERED_SAMPLER__
#include "../Sampler.hpp"

namespace RT {
namespace Samplers {
    class MultiJitteredSampler : public Sampler {
    public:
        MultiJitteredSampler(uint32_t samples)
            : Sampler(SamplerType::MultiJittered)
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