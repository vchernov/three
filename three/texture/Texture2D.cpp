#include "Texture2D.h"

#include <cassert>

#include <glm/glm.hpp>

namespace three {

void Texture2D::upload(const void* data, unsigned int dataType, unsigned int format, int width, int height, int internalFormat) {
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, dataType, data);
    assert(glGetError() == GL_NO_ERROR);
}

template<>
unsigned Texture2D::getImageDataType<uint8_t>() {
    return TypeInfo<uint8_t>::dataType;
}

template<>
unsigned Texture2D::getImageDataType<glm::vec3>() {
    return TypeInfo<glm::vec3::value_type>::dataType;
}

}
