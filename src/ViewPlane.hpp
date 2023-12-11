#ifndef __RT_VIEW_PLANE__
#define __RT_VIEW_PLANE__
#include "Sampler.hpp"
#include "samplers/JitteredSampler.hpp"
#include "samplers/MultiJitteredSampler.hpp"
#include "samplers/RegularSampler.hpp"
#include <memory>
#include <stdint.h>

namespace RT {
class ViewPlane {
public:
    uint32_t h_res; // Horizontal resolution
    uint32_t v_res; // Vertical resolution
    uint32_t samples; // Samples per pixel
    float pixel_size;
    float gamma; // Monitor gamma factor
    float inv_gamma; // One over gamma
    std::shared_ptr<Sampler> sampler;

    ViewPlane()
        : gamma(1.0f)
        , inv_gamma(1.0f)
        , samples(1)
        , h_res(480)
        , v_res(480)
        , pixel_size(1.0f)
    {
    }

    void set_gamma(float gamma)
    {
        // Sets gamma and calculates inv gamma
        this->gamma = gamma;
        this->inv_gamma = 1.0f / gamma;
    }
    inline void set_pixel_size(float size) { pixel_size = size; }
    inline void set_hres(uint32_t hres) { h_res = hres; }
    inline void set_vres(uint32_t vres) { v_res = vres; }
    inline void set_samples(uint32_t spp)
    {
        samples = spp;
        if (samples == 1)
            sampler = std::make_shared<Samplers::RegularSampler>(1);
        else
            sampler = std::make_shared<Samplers::MultiJitteredSampler>(samples);
        sampler->generate_samples();
        sampler->setup_shuffled_indices();
    }
    inline void set_sampler(std::shared_ptr<Sampler>& s)
    {
        sampler = s;
        sampler->generate_samples();
        sampler->setup_shuffled_indices();
        samples = sampler->get_num_samples();
    }
};
}

#endif