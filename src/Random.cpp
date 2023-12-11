#include "Random.hpp"

static thread_local std::uniform_int_distribution<int32_t> _int_distribution(0, std::numeric_limits<int32_t>().max());
static thread_local uint32_t _int_seed = rand();
static thread_local std::mt19937 _int_generator(_int_seed);

static thread_local std::uniform_real_distribution<float> _float_distribution(0.0f, 1.0f);
static thread_local uint32_t _float_seed = rand();
static thread_local std::mt19937 _float_generator(_float_seed);

int32_t RT::Random::random_int()
{
    return _int_distribution(_int_generator);
}

void RT::Random::set_int_seed(uint32_t seed)
{
    _int_seed = seed;
    _int_generator = std::mt19937(_int_seed);
}

float RT::Random::unit_float()
{
    return _float_distribution(_float_generator);
}

void RT::Random::set_float_seed(uint32_t seed)
{
    _float_seed = seed;
    _float_generator = std::mt19937(_float_seed);
}