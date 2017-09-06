#include <iostream>
#include <cmath>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/mesh/Mesh.h"
#include "../../three/camera/OrthographicCamera.h"

#include "../../helpers/engine/window/WindowFactory.h"
#include "../../helpers/engine/Vertex.h"
#include "../../helpers/engine/Face3.h"
#include "../../helpers/engine/Geometry.h"
#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/ImageUtils.h"
#include "../../helpers/engine/MeshBuilder.h"
#include "../../helpers/engine/UniformName.h"

using namespace three;

using MyGeometry = Geometry<VertexPositionTexture, Face3>;

MyGeometry createPlane(float s) {
    MyGeometry geo;
    geo.primitiveType = GL_TRIANGLES;

    geo.vertices.push_back({{-s, -s, 0.0f}, {0.0f, 0.0f}});
    geo.vertices.push_back({{s, -s, 0.0f}, {1.0f, 0.0f}});
    geo.vertices.push_back({{s, s, 0.0f}, {1.0f, 1.0f}});
    geo.vertices.push_back({{-s, s, 0.0f}, {0.0f, 1.0f}});

    geo.faces.push_back({0, 1, 2});
    geo.faces.push_back({0, 2, 3});

    return geo;
}

int main(int argc, char** argv) {
    std::cout << "start" << std::endl;
    std::cout << std::boolalpha;

    std::string imgFn;
    if (argc > 1) {
        imgFn = argv[1];
    }

    auto wnd = WindowFactory::createWindow("Texturing Example", 1024, 768);
    auto camera = std::make_unique<OrthographicCamera>(wnd->getWidth(), wnd->getHeight(), 0.1f, 10.0f);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

    auto shaderProg = ShaderUtils::loadShaderProgram("shaders/textured.vert", "shaders/textured.frag");
    shaderProg.use();

    auto mesh = MeshBuilder::build(createPlane((float)fmin(wnd->getWidth(), wnd->getHeight()) * 0.40f), shaderProg);

    auto tex = ImageUtils::loadTexture(imgFn, GL_RGBA8);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 transform;
    transform = glm::translate(transform, glm::vec3(wnd->getWidth() * 0.5f, wnd->getHeight() * 0.5f, -1.0f));

    shaderProg.setUniform(shaderProg.getUniformLocation(UniformName::modelMatrix), transform);
    shaderProg.setUniform(shaderProg.getUniformLocation(UniformName::viewMatrix), glm::mat4());
    shaderProg.setUniform(shaderProg.getUniformLocation(UniformName::projectionMatrix), camera->getProjectionMatrix());

    while (wnd->isRunning()) {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        tex.bind();
        mesh.draw();
        Texture2D::unbind();

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
