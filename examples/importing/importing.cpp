#include <iostream>
#include <future>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/shader/SmartShaderProgram.h"
#include "../../three/shader/ShaderManager.h"
#include "../../three/shader/Uniform.h"
#include "../../three/shader/UniformBuffer.h"
#include "../../three/camera/PerspectiveCamera.h"
#include "../../three/transform/ModelTransform.h"

#include "../../helpers/engine/FileSystem.h"
#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/MeshBuilder.h"
#include "../../helpers/engine/UniformName.h"
#include "../../helpers/engine/UniformBlockName.h"
#include "../../helpers/engine/Model.h"

#include "../../helpers/window/WindowFactory.h"

#include "../../helpers/import/ModelImporter.h"
#include "../../helpers/import/DynamicModelImporter.h"

using namespace three;

int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;
    std::cout << std::boolalpha;

    std::cout << FileSystem::getCurrentDirectory() << std::endl;

    std::string modelFn;
    if (argc > 1)
    {
        modelFn = argv[1];
    }

    auto controls = std::make_shared<OrbitControls>();
    controls->setRotationSpeed(0.5f);
    controls->setZoomSpeed(0.2f);
    controls->setMoveSpeed(0.005f);
    auto wnd = WindowFactory::createWindowWithOrbitCamera("Asset Importing Example", 1024, 768, controls);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    auto camera = std::make_unique<PerspectiveCamera>(45.0f, (float)wnd->getWidth() / wnd->getHeight(), 0.1f, 100.0f);

    auto shaderManager = std::make_shared<ShaderManager>();
    auto program = std::make_shared<SmartShaderProgram>(shaderManager);
    try
    {
        ShaderUtils::loadShaderProgram(program.get(), "shaders/default.vert", "shaders/default.frag");
    }
    catch (FileNotFoundException& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    program->use();

    UniformBuffer cameraUniformBuffer;
    UniformBuffer lightUniformBuffer;

    program->bindUniformBlock(UniformBlockName::camera, cameraUniformBuffer);
    program->bindUniformBlock(UniformBlockName::light, lightUniformBuffer);

    cameraUniformBuffer.bind();
    UniformBuffer::allocate(sizeof(glm::mat4) + sizeof(glm::mat4));
    glm::mat4 projMat = camera->getProjectionMatrix();
    UniformBuffer::write(glm::value_ptr(projMat), sizeof(glm::mat4), sizeof(projMat));
    UniformBuffer::unbind();

    lightUniformBuffer.bind();
    UniformBuffer::allocate(sizeof(glm::vec3) + sizeof(glm::vec3));
    glm::vec3 lightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    UniformBuffer::upload(0, sizeof(glm::vec3), glm::value_ptr(lightDiffuse));
    UniformBuffer::unbind();

    assert(glGetError() == GL_NO_ERROR);

    std::vector<Model> models;
    BoundingBox sceneBounds;

    //*
    std::future<std::vector<ModelImporter::ModelGeometry>> result = std::async(
        std::launch::async,
        &ModelImporter::loadGeometry,
        modelFn);
    //*/

    /*
    std::future<std::shared_ptr<DynamicModelImporter::IntermediateImportResult>> result = std::async(
        std::launch::async,
        &DynamicModelImporter::importModel,
        modelFn);
    //*/

    while (wnd->isRunning())
    {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cameraUniformBuffer.bind();
        glm::mat4 viewMat = controls->getViewMatrix();
        UniformBuffer::write(glm::value_ptr(viewMat), 0, sizeof(viewMat));
        UniformBuffer::unbind();

        lightUniformBuffer.bind();
        glm::vec3 lightPos = controls->getEyePosition();
        UniformBuffer::upload(sizeof(glm::vec3), sizeof(glm::vec3), glm::value_ptr(lightPos));
        UniformBuffer::unbind();

        for (auto& model : models)
        {
            model.draw();
        }

        wnd->swapBuffers();

        if (result.valid() && result.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
        {
            //Model model = DynamicModelImporter::loadModel(result.get());

            //*
            Model model;
            std::vector<ModelImporter::ModelGeometry> geo = result.get();
            for (auto& g : geo)
            {
                SubMesh submesh(MeshBuilder::build(g));
                submesh.bounds = BoundingBox::calculate(g.vertices);
                model.meshes.push_back(std::move(submesh));
            }
            //*/

            for (auto& submesh : model.meshes)
            {
                submesh.applyShader(program);

                sceneBounds.encapsulate(submesh.bounds);
                controls->setPosition(sceneBounds.getCenter());
                controls->setRadius(glm::length(sceneBounds.getSize()));
            }

            models.push_back(std::move(model));
        }
    }

    std::cout << "end" << std::endl;
    return 0;
}
