#include <iostream>
#include <mutex>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/shader/UniformBuffer.h"
#include "../../three/mesh/Mesh.h"
#include "../../three/camera/PerspectiveCamera.h"
#include "../../three/transform/ModelTransform.h"

#include "../../helpers/engine/window/WindowFactory.h"
#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/ModelLoader.h"
#include "../../helpers/engine/UniformName.h"
#include "../../helpers/engine/Model.h"

using namespace three;

Model loadModel(const std::string& fn, const ShaderProgram& shaderProg) {
    Model model;
    std::list<GeometryBuffer> geos = ModelLoader::load(fn, model.bounds);
    for (auto& geo : geos) {
        model.meshes.push_back(Mesh::create(geo.vertexBuffers, std::move(geo.indexBuffer), shaderProg, geo.primitiveType));
    }
    return model;
}

int main(int argc, char** argv) {
    std::cout << "start" << std::endl;
    std::cout << std::boolalpha;

    std::string modelFn;
    if (argc > 1) {
        modelFn = argv[1];
    }

    auto controls = std::make_shared<OrbitControls>();
    controls->setRotationSpeed(0.5f);
    controls->setZoomSpeed(0.2f);
    controls->setMoveSpeed(0.005f);
    auto wnd = WindowFactory::createWindowWithOrbitCamera("Asset Loading Example", 1024, 768, controls);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    auto modelShaderProg = ShaderUtils::loadShaderProgram("shaders/position_only.vert", "shaders/position_only.frag");
    modelShaderProg.use();

    auto camera = std::make_unique<PerspectiveCamera>(45.0f, (float)wnd->getWidth() / wnd->getHeight(), 0.1f, 100.0f);
    modelShaderProg.setUniform(modelShaderProg.getUniformLocation(UniformName::projectionMatrix), camera->getProjectionMatrix());

    assert(glGetError() == GL_NO_ERROR);

    auto model = loadModel(modelFn, modelShaderProg);

    controls->setPosition(model.bounds.center);
    controls->setRadius(glm::length(model.bounds.size));

    while (wnd->isRunning()) {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        modelShaderProg.setUniform(modelShaderProg.getUniformLocation(UniformName::viewMatrix), controls->getViewMatrix());
        modelShaderProg.setUniform(modelShaderProg.getUniformLocation("color"), glm::vec3(1.0f, 1.0f, 1.0f));
        modelShaderProg.setUniform(modelShaderProg.getUniformLocation(UniformName::modelMatrix), model.transform.getTransformationMatrix());

        model.draw();

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
