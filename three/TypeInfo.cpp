#include "TypeInfo.h"

#include <GL/glew.h>

namespace three {

template<>
const GLenum TypeInfo<float>::dataType = GL_FLOAT;

template<>
const GLenum TypeInfo<unsigned int>::dataType = GL_UNSIGNED_INT;

template<>
const GLenum TypeInfo<unsigned short>::dataType = GL_UNSIGNED_SHORT;

template<>
const GLenum TypeInfo<unsigned char>::dataType = GL_UNSIGNED_BYTE;

}
