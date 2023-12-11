#ifndef __RT_RANDOM__
#define __RT_RANDOM__
#include <random>

namespace RT {
namespace Random {

    /// @brief Returns a random uint32_t in range [0, max(uint32_t)]
    uint32_t random_int();

    /// @brief Sets int generator seed
    void set_int_seed(uint32_t seed);

    /// @brief Returns a random float in range [0.0f, 1.0f]
    uint32_t unit_float();

    /// @brief Sets float generator seed
    void set_float_seed(uint32_t seed);
}
}

#endif