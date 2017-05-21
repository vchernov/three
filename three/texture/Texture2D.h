#pragma once

#include "Texture.h"
#include "Image.h"
#include "../TypeInfo.h"

namespace three {

class Texture2D : public Texture<GL_TEXTURE_2D> {
public:
    static void upload(const void* data, unsigned int dataType, unsigned int format, int width, int height, int internalFormat);

    template<typename T>
    static void upload(const Image<T>& img, int internalFormat) {
        upload(img.getData(), getImageDataType<T>(), img.getFormat(), img.getWidth(), img.getHeight(), internalFormat);
    }

private:
    template<class T>
    static unsigned int getImageDataType();
};

}
