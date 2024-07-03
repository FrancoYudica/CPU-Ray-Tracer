#ifndef __RT_SAMPLER__
#define __RT_SAMPLER__
#include "math_RT.hpp"
#include <vector>

namespace RT {

enum class SamplerType {
    Regular,
    Jittered,
    MultiJittered,
    NRooks
};
enum class SampleMode {
    Square,
    Disk,
    Hemisphere
};
class Sampler {
public:
    Sampler(SamplerType type)
        : _type(type)
        , _mode(SampleMode::Square)
    {
    }

    /// @brief Creates the samples and stores them
    virtual void generate_samples() = 0;

    void map_samples_to_unit_disk();
    void map_samples_to_hemisphere(const float e);

    /// @brief Set up the randomly shuffled indices
    void setup_shuffled_indices();

    /// @brief Gets the next sample in the unit square
    Vec2 sample_unit_square();
    Vec2 sample_unit_disk();
    Vec3f sample_unit_hemisphere(const Vec3f& u, const Vec3f& v, const Vec3f& w);

    inline uint32_t get_num_samples() const
    {
        return _num_samples;
    }
    inline uint32_t get_num_sets() const
    {
        return _num_sets;
    }
    inline SamplerType get_type() const
    {
        return _type;
    }
    inline SampleMode get_mode() const
    {
        return _mode;
    }

protected:
    /// @brief Sets represent the amount of boxes/pixels. It's usually a hardcoded value
    /// When sampling pixels, it's not necessary to match the screen pixel count, since
    /// generate_unit_square() introduces 'randomness'.
    uint32_t _num_sets;

    /// @brief For each of the sets, a number of samples is stored
    uint32_t _num_samples;

    /// @brief Contains the samples of all the sets
    /// Instead of storing them in a grid
    /// set1 = [s1_sample1, s1_sample2, s1_sample3, s1_sample4, ...]
    /// set2 = [s2_sample1, s2_sample2, s2_sample3, s2_sample4, ...]
    /// ...
    /// Samples are stored in a vector, in the following format
    /// samples = [
    ///            s1_sample1, s1_sample2, s1_sample3, s1_sample4,
    ///            s2_sample1, s2_sample2, s2_sample3, s2_sample4,
    ///            ...,
    ///            sn_sample1, sn_sample2, sn_sample3, sn_sample4
    ///            ]
    std::vector<Vec2> _samples;
    std::vector<Vec2> _disk_samples;
    std::vector<Vec3f> _hemisphere_samples;

    // Amount of calls to samples, used to retrieve different samples each time
    uint32_t _count;

private:
    std::vector<uint32_t> _shuffled_indices;
    uint32_t _jump;
    SamplerType _type;
    SampleMode _mode;
    float _e;
};
} // namespace RT

#endif