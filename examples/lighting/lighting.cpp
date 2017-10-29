#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/shader/UniformBuffer.h"
#include "../../three/mesh/Mesh.h"
#include "../../three/camera/PerspectiveCamera.h"
#include "../../three/transform/ModelTransform.h"
#include "../../three/TypeInfo.h"

#include "../../helpers/engine/window/WindowFactory.h"
#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/Shape.h"
#include "../../helpers/engine/AttributeName.h"
#include "../../helpers/engine/UniformName.h"
#include "../../helpers/engine/UniformBlockName.h"
#include "../../helpers/engine/Time.h"

using namespace three;

struct Model {
    explicit Model(Mesh mesh)
        : mesh(std::move(mesh)) {
    }

    Mesh mesh;
    ModelTransform transform;
    glm::vec3 color;
};

class PointLight {
public:
    PointLight() {
        lampShaderProg = ShaderUtils::loadShaderProgram("shaders/lamp.vert", "shaders/lamp.frag");

        vao.bind();
        vertexBuffer.bind();
        std::vector<glm::vec3> points = {{0.0f, 0.0f, 0.0f}};
        vertexBuffer.upload(points);
        vertexBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
        vertexBuffer.enableAttributes(lampShaderProg);
        VertexArrayObject::unbind();
    }

    void draw() {
        lampShaderProg.use();
        lampShaderProg.setUniform(lampShaderProg.getUniformLocation("lightColor"), lightColor);
        lampShaderProg.setUniform(lampShaderProg.getUniformLocation(UniformName::modelMatrix), getTransformationMatrix());

        vao.bind();
        vertexBuffer.draw(GL_POINTS);
        VertexArrayObject::unbind();
    }

    glm::mat4 getTransformationMatrix() const {
        glm::mat4 transform = glm::mat4(1.0f);
        return glm::translate(transform, position);
    }

    glm::vec3 position;
    glm::vec3 lightColor;
    ShaderProgram lampShaderProg;

private:
    VertexArrayObject vao;
    VertexBuffer vertexBuffer;
};

int main(int argc, char** argv) {
    std::cout << "start" << std::endl;
    std::cout << std::boolalpha;

    auto controls = std::make_shared<OrbitControls>();
    controls->setRotationSpeed(0.5f);
    controls->setZoomSpeed(0.2f);
    controls->setMoveSpeed(0.005f);
    controls->setRadius(3.0f);
    auto wnd = WindowFactory::createWindowWithOrbitCamera("Lighting Example", 1024, 768, controls);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_PROGRAM_POINT_SIZE);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

    auto camera = std::make_unique<PerspectiveCamera>(45.0f, (float)wnd->getWidth() / wnd->getHeight(), 0.1f, 10.0f);

    auto modelShaderProg = ShaderUtils::loadShaderProgram("shaders/phong.vert", "shaders/phong.frag");

    PointLight light;
    light.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    std::vector<Model> models;

    {
        auto geo = Shape::createCube();
        auto mesh = Mesh::create(geo.vertexBuffers, std::move(geo.indexBuffer), modelShaderProg, geo.primitiveType);
        Model model(std::move(mesh));
        model.color = glm::vec3(1.0f, 1.0f, 0.0f);
        model.transform.scale = glm::vec3(0.25f, 0.25f, 0.25f);
        model.transform.position = glm::vec3(0.5f, -0.15f, -0.25f);
        models.push_back(std::move(model));
    }

    {
        auto geo = Shape::createSphere(32, 32);
        auto mesh = Mesh::create(geo.vertexBuffers, std::move(geo.indexBuffer), modelShaderProg, geo.primitiveType);
        Model model(std::move(mesh));
        model.color = glm::vec3(0.0f, 1.0f, 0.0f);
        model.transform.scale = glm::vec3(0.25f, 0.25f, 0.25f);
        model.transform.position = glm::vec3(-0.25f, 0.0f, 0.25f);
        models.push_back(std::move(model));
    }

    UniformBuffer cameraUniformBuffer;
    cameraUniformBuffer.bindBlock();
    cameraUniformBuffer.allocate(sizeof(glm::mat4) + sizeof(glm::mat4));
    glm::mat4 projMat = camera->getProjectionMatrix();
    cameraUniformBuffer.write(glm::value_ptr(projMat), sizeof(glm::mat4), sizeof(projMat));
    UniformBuffer::unbind();

    modelShaderProg.bindUniformBlock(UniformBlockName::camera, cameraUniformBuffer);
    light.lampShaderProg.bindUniformBlock(UniformBlockName::camera, cameraUniformBuffer);

    assert(glGetError() == GL_NO_ERROR);

    while (wnd->isRunning()) {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = (float)Time::getTime();
        light.position = glm::vec3(0.0f);
        light.position.x = sinf(time * 0.9f) * 1.2f;
        light.position.y = sinf(time * 0.2f) * 0.8f;
        light.position.z = sinf(time * 2.0f) * 0.6f;

        cameraUniformBuffer.bindBlock();
        glm::mat4 viewMat = controls->getViewMatrix();
        cameraUniformBuffer.write(glm::value_ptr(viewMat), 0, sizeof(viewMat));
        UniformBuffer::unbind();

        light.draw(); // gizmos

        modelShaderProg.use();

        for (const auto& model : models) {
            modelShaderProg.setUniform(modelShaderProg.getUniformLocation("color"), model.color);
            modelShaderProg.setUniform(modelShaderProg.getUniformLocation("lightColor"), light.lightColor);
            modelShaderProg.setUniform(modelShaderProg.getUniformLocation("lightPos"), light.position);
            modelShaderProg.setUniform(modelShaderProg.getUniformLocation("viewPos"), controls->getEyePosition());
            modelShaderProg.setUniform(modelShaderProg.getUniformLocation(UniformName::modelMatrix), model.transform.getTransformationMatrix());
            model.mesh.draw();
        }

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
