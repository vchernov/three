#include <iostream>
#include <mutex>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/shader/Uniform.h"
#include "../../three/shader/UniformBuffer.h"
#include "../../three/camera/PerspectiveCamera.h"
#include "../../three/transform/ModelTransform.h"

#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/UniformName.h"
#include "../../helpers/engine/Model.h"

#include "../../helpers/window/WindowFactory.h"

#include "../../helpers/import/ModelLoader.h"

using namespace three;

Model loadModel(const std::string& fn) {
    Model model;
    model.meshes = ModelLoader::load(fn, model.bounds);
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

    auto program = ShaderUtils::loadShaderProgram("shaders/position_only.vert", "shaders/position_only.frag");
    program.use();

    auto camera = std::make_unique<PerspectiveCamera>(45.0f, (float)wnd->getWidth() / wnd->getHeight(), 0.1f, 100.0f);
    Uniform<glm::mat4>::update(program.getUniformLocation(UniformName::projectionMatrix), camera->getProjectionMatrix());
    Uniform<glm::mat4> viewMatUniform(program.getUniformLocation(UniformName::viewMatrix));
    Uniform<glm::mat4> modelMatUniform(program.getUniformLocation(UniformName::modelMatrix));

    assert(glGetError() == GL_NO_ERROR);

    auto model = loadModel(modelFn);

    controls->setPosition(model.bounds.center);
    controls->setRadius(glm::length(model.bounds.size));

    Uniform<glm::vec3> colorUniform(program.getUniformLocation("color"));

    while (wnd->isRunning()) {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMatUniform.set(controls->getViewMatrix());
        modelMatUniform.set(model.transform.getTransformationMatrix());
        colorUniform.set(glm::vec3(1.0f, 1.0f, 1.0f));

        model.draw();

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
