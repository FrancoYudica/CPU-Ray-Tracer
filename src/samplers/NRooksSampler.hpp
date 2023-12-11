#ifndef __RT_NROOKS_SAMPLER__
#define __RT_NROOKS_SAMPLER__
#include "../Sampler.hpp"

namespace RT {
namespace Samplers {
    class NRooksSampler : public Sampler {
        /*
        Rooks sampler generates samples in the diagonal of the box,
        and then shuffles the X components and then the Y components.

        The output is no better than the "Jittered sampling"
        */
    public:
        NRooksSampler(uint32_t samples)
            : Sampler(SamplerType::NRooks)
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