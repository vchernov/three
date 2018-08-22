#include "ImageUtils.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace three;

Image<uint8_t> ImageUtils::loadImage(const std::string& fn)
{
    stbi_set_flip_vertically_on_load(1);

    int width, height, numChannels;
    uint8_t* pixels = stbi_load(fn.c_str(), &width, &height, &numChannels, STBI_default);
    if (pixels == nullptr)
    {
        std::cerr << "Could not load image from file: " << fn << std::endl;
        throw std::runtime_error("Image loading failed");
    }

    unsigned int format;
    switch (numChannels)
    {
    case STBI_grey:
        format = GL_LUMINANCE;
        break;
    case STBI_grey_alpha:
        format = GL_LUMINANCE_ALPHA;
        break;
    case STBI_rgb:
        format = GL_RGB;
        break;
    case STBI_rgb_alpha:
        format = GL_RGBA;
        break;
    default:
        throw std::runtime_error("Unsupported image format");
    }

    return Image<uint8_t>(pixels, width, height, numChannels, format);
}

Texture2D ImageUtils::loadTexture(const std::string& fn, int internalFormat)
{
    auto img = loadImage(fn);
    Texture2D tex;
    tex.bind();
    Texture2D::upload(img, internalFormat);
    Texture2D::setFiltering(GL_LINEAR, GL_LINEAR);
    Texture2D::setWrapping(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    Texture2D::unbind();
    return tex;
}
