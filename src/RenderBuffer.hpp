#ifndef __RT_RENDER_BUFFER__
#define __RT_RENDER_BUFFER__
#include "Math_rt.hpp"
#include <cstring>
#include <iostream>
#include <stdint.h>
#include <vector>

namespace RT {
class RenderBuffer {
public:
    const uint32_t width;
    const uint32_t height;

public:
    RenderBuffer()
        : width(0)
        , height(0)
        , _raw_buffer(nullptr)
    {
    }
    RenderBuffer(const RenderBuffer& other)
        : width(other.width)
        , height(other.height)
    {
        // Creates a new buffer
        _raw_buffer = new RGBColor[width * height];
        memcpy(_raw_buffer, other.buffer_raw_ptr(), sizeof(RGBColor) * width * height);
        clear();
    }
    RenderBuffer(uint32_t width, uint32_t height)
        : width(width)
        , height(height)
    {
        _raw_buffer = new RGBColor[width * height];
        clear();
    }

    ~RenderBuffer()
    {
        delete[] _raw_buffer;
    }
    inline const RGBColor* buffer_raw_ptr() const { return _raw_buffer; }
    void clear()
    {
        memset(_raw_buffer, 0, sizeof(RGBColor) * width * height);
    }

    void set_pixel(
        const uint32_t& column,
        const uint32_t& row,
        const RGBColor& color)
    {
        _raw_buffer[column + row * width] = color;
    }

    RGBColor get_pixel(
        const uint32_t& column,
        const uint32_t& row) const
    {
        // Returns a copy of the color
        return _raw_buffer[column + row * width];
    }

    void copy_buffer(
        const RGBColor* source)
    {
        memcpy(_raw_buffer, source, sizeof(RGBColor) * width * height);
    }

private:
    RGBColor* _raw_buffer;
};
}

#endif