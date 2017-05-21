#pragma once

#include <string>

#include "../../three/texture/Image.h"
#include "../../three/texture/Texture2D.h"

class ImageUtils {
public:
    static three::Image<uint8_t> loadImage(const std::string& fn);

    static three::Texture2D loadTexture(const std::string& fn, int internalFormat);
};
