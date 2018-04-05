#include <iostream>
#include <mutex>
#include <future>

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
#include "../../helpers/engine/MeshBuilder.h"

using namespace three;

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

    std::vector<Model> models;
    BoundingBox sceneBounds;

    std::future<std::vector<ModelLoader::Geometry>> loadResult = std::async(std::launch::async, &ModelLoader::loadGeometry, modelFn);

    Uniform<glm::vec3> colorUniform(program.getUniformLocation("color"));

    while (wnd->isRunning()) {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMatUniform.set(controls->getViewMatrix());
        colorUniform.set(glm::vec3(1.0f, 1.0f, 1.0f));

        for (auto& model : models) {
            modelMatUniform.set(model.transform.getTransformationMatrix());
            model.draw();
        }

        wnd->swapBuffers();

        if (loadResult.valid() && loadResult.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
            std::vector<ModelLoader::Geometry> geo = loadResult.get();

            for (auto& g : geo) {
                Model model;
                Mesh mesh = MeshBuilder::build(g);
                SubMesh submesh = SubMesh(std::move(mesh), BoundingBox::calculate(g.vertices));
                model.meshes.push_back(std::move(submesh));
                models.push_back(std::move(model));

                sceneBounds.encapsulate(submesh.getBounds());
                controls->setPosition(sceneBounds.getCenter());
                controls->setRadius(glm::length(sceneBounds.getSize()));
            }
        }
    }

    std::cout << "end" << std::endl;
    return 0;
}
