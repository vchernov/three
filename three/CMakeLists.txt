add_library(three
    TypeInfo.h
    TypeInfo.cpp
    BufferObject.h
    shader/Shader.h
    shader/Shader.cpp
    shader/ShaderProgram.h
    shader/ShaderProgram.cpp
    shader/Uniform.h
    shader/Uniform.cpp
    shader/UniformBuffer.h
    shader/UniformBuffer.cpp
    shader/AttributeInfo.h
    shader/ShaderManager.h
    shader/ShaderManager.cpp
    shader/ManageableShaderProgram.h
    shader/ManageableShaderProgram.cpp
    shader/SmartShaderProgram.h
    shader/IDeferredUniform.h
    shader/SmartUniform.h
    mesh/VertexBuffer.h
    mesh/VertexBuffer.cpp
    mesh/IndexBuffer.h
    mesh/IndexBuffer.cpp
    mesh/VertexArrayObject.h
    mesh/VertexArrayObject.cpp
    mesh/Mesh.h
    mesh/Mesh.cpp
    mesh/Face.h
    mesh/VertexAttribute.h
    mesh/VertexAttribute.cpp
    mesh/AttributeBindings.h
    texture/Image.h
    texture/Texture.h
    texture/Texture2D.h
    texture/Texture2D.cpp
    transform/Transform.h
    transform/Transform.cpp
    transform/ModelTransform.h
    transform/ModelTransform.cpp
    camera/Camera.h
    camera/PerspectiveCamera.h
    camera/PerspectiveCamera.cpp
    camera/OrthographicCamera.h
    camera/OrthographicCamera.cpp
    camera/OrbitControls.h
    camera/OrbitControls.cpp
)

target_compile_features(three PUBLIC cxx_std_14)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_include_directories(three
    PUBLIC ${OPENGL_INCLUDE_DIR}
    PUBLIC ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(three
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${GLEW_LIBRARIES}
    PUBLIC glm
)
