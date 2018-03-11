#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/shader/Uniform.h"
#include "../../three/shader/AttributeInfo.h"
#include "../../three/mesh/Mesh.h"
#include "../../three/camera/PerspectiveCamera.h"
#include "../../three/transform/ModelTransform.h"

#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/UniformName.h"
#include "../../helpers/engine/Shape.h"

#include "../../helpers/window/WindowFactory.h"

using namespace three;

struct Model {
    explicit Model(Mesh mesh)
        : mesh(std::move(mesh)) {
    }

    Mesh mesh;
    ModelTransform transform;
    glm::vec3 color;
};

int main(int argc, char** argv) {
    std::cout << "start" << std::endl;
    std::cout << std::boolalpha;

    auto controls = std::make_shared<OrbitControls>();
    controls->setRotationSpeed(0.5f);
    controls->setZoomSpeed(0.2f);
    controls->setMoveSpeed(0.005f);
    controls->setRadius(3.0f);
    controls->yaw(45.0f);
    auto wnd = WindowFactory::createWindowWithOrbitCamera("Primitives Example", 1024, 768, controls);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    auto program = ShaderUtils::loadShaderProgram("shaders/position_only.vert", "shaders/position_only.frag");
    program.use();

    auto camera = std::make_unique<PerspectiveCamera>(45.0f, (float)wnd->getWidth() / wnd->getHeight(), 0.1f, 10.0f);
    Uniform<glm::mat4>::update(program.getUniformLocation(UniformName::projectionMatrix), camera->getProjectionMatrix());
    Uniform<glm::mat4> viewMatUniform(program.getUniformLocation(UniformName::viewMatrix));
    Uniform<glm::mat4> modelMatUniform(program.getUniformLocation(UniformName::modelMatrix));

    std::vector<Model> models;
    
    {
        Model model(Shape::createGrid(glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, -1.0f), 8, 8));
        model.color = glm::vec3(1.0f, 1.0f, 1.0f);
        models.push_back(std::move(model));
    }

    {
        Model model(Shape::createCube());
        model.color = glm::vec3(1.0f, 1.0f, 0.0f);
        model.transform.scale = glm::vec3(0.25f, 0.25f, 0.25f);
        model.transform.position = glm::vec3(0.5f, 0.0f, -0.25f);
        models.push_back(std::move(model));
    }

    {
        Model model(Shape::createSphere(32, 32));
        model.color = glm::vec3(0.0f, 1.0f, 0.0f);
        model.transform.scale = glm::vec3(0.25f, 0.25f, 0.25f);
        model.transform.position = glm::vec3(-0.25f, 0.25f, 0.25f);
        models.push_back(std::move(model));
    }

    Uniform<glm::vec3> colorUniform(program.getUniformLocation("color"));

    while (wnd->isRunning()) {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMatUniform.set(controls->getViewMatrix());

        for (const auto& model : models) {
            colorUniform.set(model.color);
            modelMatUniform.set(model.transform.getTransformationMatrix());
            model.mesh.draw();
        }

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
