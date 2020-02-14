#include "ImageUtils.h"

#include "../engine/fs/FileNotFoundException.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../3rdparty/stb/stb_image.h"

using namespace three;

ImageRGB ImageUtils::loadImage(const std::string& fn)
{
    stbi_set_flip_vertically_on_load(1);

    int width, height, numChannels;
    uint8_t* pixels = stbi_load(fn.c_str(), &width, &height, &numChannels, STBI_default);
    if (pixels == nullptr)
        throw FileNotFoundException(fn);

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

    return ImageRGB(pixels, width, height, numChannels, format);
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

ImageRGB ImageUtils::createPlainColorImage(int width, int height, uint8_t r, uint8_t g, uint8_t b)
{
    ImageRGB img(width, height, 3, GL_RGB);
    for (int y = 0; y < img.getHeight(); y++)
    {
        for (int x = 0; x < img.getWidth(); x++)
        {
            img(x, y, 0) = r;
            img(x, y, 1) = g;
            img(x, y, 2) = b;
        }
    }
    return img;
}
