#pragma once

#include <string>

#include "../../three/texture/Image.h"
#include "../../three/texture/Texture2D.h"

using ImageRGB = three::Image<uint8_t>;

class ImageUtils
{
public:
    static ImageRGB loadImage(const std::string& fn);

    static three::Texture2D loadTexture(const std::string& fn, int internalFormat);

    static ImageRGB createPlainColorImage(int width, int height, uint8_t r, uint8_t g, uint8_t b);
};
