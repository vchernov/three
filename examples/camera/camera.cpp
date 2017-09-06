#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/mesh/Mesh.h"
#include "../../three/camera/PerspectiveCamera.h"
#include "../../three/transform/ModelTransform.h"

#include "../../helpers/engine/window/WindowFactory.h"
#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/UniformName.h"
#include "../../helpers/engine/Shape.h"

using namespace three;

struct Model {
    Mesh* mesh;
    ModelTransform transform;
    glm::vec3 color;
};

int main(int argc, char** argv) {
    std::cout << "start" << std::endl;
    std::cout << std::boolalpha;

    auto controls = std::make_shared<OrbitControls>();
    auto wnd = WindowFactory::createWindowWithOrbitCamera("Camera Example", 1024, 768, controls);
    auto camera = std::make_unique<PerspectiveCamera>(45.0f, (float)wnd->getWidth() / wnd->getHeight(), 0.1f, 10.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    auto shaderProg = ShaderUtils::loadShaderProgram("shaders/position_only.vert", "shaders/position_only.frag");
    shaderProg.use();

    auto primitiveGeo = Shape::createTriangle();
    auto primitiveMesh = Mesh::create(primitiveGeo.vertexBuffers, std::move(primitiveGeo.indexBuffer), shaderProg, primitiveGeo.primitiveType);

    auto gridGeo = Shape::createGrid(glm::vec3(-1.0f, -1.0f, -0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f), 8, 8);
    auto gridMesh = Mesh::create(gridGeo.vertexBuffers, std::move(gridGeo.indexBuffer), shaderProg, gridGeo.primitiveType);

    std::vector<Model> models;

    {
        Model model;
        model.mesh = &primitiveMesh;
        model.transform.position.z = 0.001f;
        model.color = glm::vec3(1.0f, 1.0f, 0.0f);
        models.push_back(model);
    }

    {
        Model model;
        model.mesh = &primitiveMesh;
        model.color = glm::vec3(0.0f, 0.0f, 1.0f);
        model.transform.position.x = 0.25f;
        model.transform.position.y = 0.25f;
        model.transform.position.z = 0.002f;
        model.transform.scale = glm::vec3(0.5f);
        model.transform.eulerAngles.z = 180.0f;
        models.push_back(model);
    }

    {
        Model model;
        model.mesh = &primitiveMesh;
        model.color = glm::vec3(0.0f, 1.0f, 0.0f);
        model.transform.position.x = -0.5f;
        model.transform.position.y = -0.25f;
        model.transform.position.z = 0.003f;
        model.transform.scale = glm::vec3(0.25f);
        model.transform.eulerAngles.z = -45.0f;
        models.push_back(model);
    }

    {
        Model model;
        model.mesh = &gridMesh;
        model.color = glm::vec3(1.0f, 1.0f, 1.0f);
        models.push_back(model);
    }

    controls->setRotationSpeed(0.5f);
    controls->setZoomSpeed(0.2f);
    controls->setMoveSpeed(0.005f);
    controls->setRadius(3.0f);

    shaderProg.setUniform(shaderProg.getUniformLocation(UniformName::projectionMatrix), camera->getProjectionMatrix());

    while (wnd->isRunning()) {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProg.setUniform(shaderProg.getUniformLocation(UniformName::viewMatrix), controls->getViewMatrix());

        for (const auto& model : models) {
            shaderProg.setUniform(shaderProg.getUniformLocation("color"), model.color);
            shaderProg.setUniform(shaderProg.getUniformLocation(UniformName::modelMatrix), model.transform.getTransformationMatrix());
            model.mesh->draw();
        }

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
