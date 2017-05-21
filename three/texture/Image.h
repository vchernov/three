#pragma once

#include <cstring>
#include <cassert>

namespace three {

template<typename T>
class Image {
public:
    using ValueType = T;

    Image(int width, int height, int elementsPerPixel, unsigned int format)
        :
        width(width),
        height(height),
        elementsPerPixel(elementsPerPixel),
        format(format) {
        assert(width >= 0);
        assert(height >= 0);
        assert(elementsPerPixel >= 0);
        data = new T[width * height * elementsPerPixel];
    }

    Image(T* data, int width, int height, int elementsPerPixel, unsigned int format)
        :
        data(data),
        width(width),
        height(height),
        elementsPerPixel(elementsPerPixel),
        format(format) {
        assert(width >= 0);
        assert(height >= 0);
        assert(elementsPerPixel >= 0);
    }

    virtual ~Image() {
        delete[] data;
    }

    Image(const Image& other)
        :
        width(other.width),
        height(other.height),
        elementsPerPixel(other.elementsPerPixel),
        format(other.format) {
        auto size = other.width * other.height * other.elementsPerPixel;
        data = new T[size];
        memcpy(data, other.data, size);
    }

    Image& operator=(const Image& other) {
        if (other.data != data) {
            auto size = other.width * other.height * other.elementsPerPixel;
            if (size != width * height * elementsPerPixel) {
                delete[] data;
                data = new T[size];
            }
            memcpy(data, other.data, size);
            width = other.width;
            height = other.height;
            elementsPerPixel = other.elementsPerPixel;
            format = other.format;
        }
        return *this;
    }

    Image(Image&& other) noexcept
        :
        data(other.data),
        width(other.width),
        height(other.height),
        elementsPerPixel(other.elementsPerPixel),
        format(other.format) {
        other.data = nullptr;
        other.width = 0;
        other.height = 0;
        other.elementsPerPixel = 0;
    }

    Image operator=(Image&& other) noexcept {
        data = other.data;
        width = other.width;
        height = other.height;
        elementsPerPixel = other.elementsPerPixel;
        format = other.format;
        other.data = nullptr;
        other.width = 0;
        other.height = 0;
        other.elementsPerPixel = 0;
        return *this;
    }

    const void* getData() const {
        return data;
    }

    unsigned int getFormat() const {
        return format;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    T& operator[](int i) {
        return data[i];
    }

    T& operator()(int x, int y, int offset = 0) {
        return data[(y * width + x) * elementsPerPixel + offset];
    }

private:
    T* data;
    int width;
    int height;
    int elementsPerPixel;
    unsigned int format;
};

}
