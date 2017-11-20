#include "TypeInfo.h"

#include <GL/glew.h>

namespace three {

template<>
const unsigned int TypeInfo<float>::dataType = GL_FLOAT;

template<>
const unsigned int TypeInfo<unsigned int>::dataType = GL_UNSIGNED_INT;

template<>
const unsigned int TypeInfo<unsigned short>::dataType = GL_UNSIGNED_SHORT;

template<>
const unsigned int TypeInfo<unsigned char>::dataType = GL_UNSIGNED_BYTE;

}
