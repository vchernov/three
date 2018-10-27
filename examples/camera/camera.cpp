#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/shader/Uniform.h"
#include "../../three/mesh/Mesh.h"
#include "../../three/camera/PerspectiveCamera.h"
#include "../../three/transform/ModelTransform.h"

#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/UniformName.h"

#include "../../helpers/shape/Shape.h"

#include "../../helpers/window/WindowFactory.h"

using namespace three;

struct SimpleModel
{
    Mesh* mesh;
    ModelTransform transform;
    glm::vec3 color;
};

int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;
    std::cout << std::boolalpha;

    auto controls = std::make_shared<OrbitControls>();
    controls->setRotationSpeed(0.5f);
    controls->setZoomSpeed(0.2f);
    controls->setMoveSpeed(0.005f);
    controls->setRadius(3.0f);
    auto wnd = WindowFactory::createWindowWithOrbitCamera("Camera Example", 1024, 768, controls);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

    auto program = ShaderUtils::loadShaderProgram("shaders/position_only.vert", "shaders/position_only.frag");
    program.use();

    auto camera = std::make_unique<PerspectiveCamera>(45.0f, (float)wnd->getWidth() / wnd->getHeight(), 0.1f, 10.0f);
    Uniform<glm::mat4>::update(
        program.getUniformLocation(UniformName::projectionMatrix),
        camera->getProjectionMatrix());
    Uniform<glm::mat4> viewMatUniform(program.getUniformLocation(UniformName::viewMatrix));
    Uniform<glm::mat4> modelMatUniform(program.getUniformLocation(UniformName::modelMatrix));

    auto primitiveMesh = Shape::createTriangle();
	auto gridMesh = Shape::createGrid(
		glm::vec3(-1.0f, -1.0f, -0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f),
		8, 8);

    std::vector<SimpleModel> models;

    {
        SimpleModel model;
        model.mesh = &primitiveMesh;
        model.transform.position.z = 0.001f;
        model.color = glm::vec3(1.0f, 1.0f, 0.0f);
        models.push_back(model);
    }

    {
        SimpleModel model;
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
        SimpleModel model;
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
        SimpleModel model;
        model.mesh = &gridMesh;
        model.color = glm::vec3(1.0f, 1.0f, 1.0f);
        models.push_back(model);
    }

    Uniform<glm::vec3> colorUniform(program.getUniformLocation("color"));

    while (wnd->isRunning())
    {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMatUniform.set(controls->getViewMatrix());

        for (const auto& model : models)
        {
            colorUniform.set(model.color);
            modelMatUniform.set(model.transform.getTransformationMatrix());
            model.mesh->draw();
        }

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
