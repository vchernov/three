#include <iostream>
#include <array>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../three/shader/ShaderProgram.h"
#include "../../three/shader/Uniform.h"
#include "../../three/shader/UniformBuffer.h"
#include "../../three/mesh/Mesh.h"
#include "../../three/camera/PerspectiveCamera.h"
#include "../../three/transform/ModelTransform.h"
#include "../../three/shader/SmartShaderProgram.h"
#include "../../three/shader/ShaderManager.h"
#include "../../three/shader/SmartUniform.h"

#include "../../helpers/engine/window/WindowFactory.h"
#include "../../helpers/engine/ShaderUtils.h"
#include "../../helpers/engine/PrimitiveGenerator.h"
#include "../../helpers/engine/UniformName.h"
#include "../../helpers/engine/UniformBlockName.h"
#include "../../helpers/engine/AttributeName.h"
#include "../../helpers/engine/Time.h"
#include "../../helpers/engine/AttributeLocationBindings.h"

using namespace three;

struct Model {
public:
    Model(Mesh mesh, std::shared_ptr<SmartShaderProgram> program)
        :
        mesh(std::move(mesh)),
        program(std::move(program)) {
    }

    Mesh mesh;
    std::shared_ptr<SmartShaderProgram> program;
    ModelTransform transform;
    glm::vec3 color;
};

class PointLight {
public:
    explicit PointLight(std::shared_ptr<ShaderManager> shaderManager) {
        program = std::make_shared<SmartShaderProgram>(shaderManager);
        ShaderUtils::loadShaderProgram(program.get(), "shaders/lamp.vert", "shaders/lamp.frag");

        lightColorUniform = program->getUniform<glm::vec3>("lightColor");
        modelMatrixUniform = program->getUniform<glm::mat4>(UniformName::modelMatrix);

        std::array<glm::vec3, 1> points = {glm::vec3(0.0f, 0.0f, 0.0f)};

        vao.bind();

        VertexBuffer vb;
        vb.bind();
        VertexBuffer::allocate(points);

        int posAttribLoc = program->getAttributeLocation(AttributeName::position);
        vao.registerAttribute(VertexAttribute::create<float>(posAttribLoc, 3, 0, sizeof(glm::vec3)));
        vao.enableAttribute(posAttribLoc);

        VertexArrayObject::unbind();
    }

    void draw() const {
        program->use();
        modelMatrixUniform.lock()->set(getTransformationMatrix());
        lightColorUniform.lock()->set(lightColor);
        vao.bind();
        VertexBuffer::draw(GL_POINTS, 0, 1);
        VertexArrayObject::unbind();
    }

    glm::mat4 getTransformationMatrix() const {
        glm::mat4 transform = glm::mat4(1.0f);
        return glm::translate(transform, position);
    }

    glm::vec3 position;
    glm::vec3 lightColor;
    std::shared_ptr<SmartShaderProgram> program;

private:
    VertexArrayObject vao;
    std::weak_ptr<SmartUniform<glm::vec3>> lightColorUniform;
    std::weak_ptr<SmartUniform<glm::mat4>> modelMatrixUniform;
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

    auto shaderManager = std::make_shared<ShaderManager>();
    auto smartShaderProgram = std::make_shared<SmartShaderProgram>(shaderManager);
    ShaderUtils::loadShaderProgram(smartShaderProgram.get(), "shaders/phong.vert", "shaders/phong.frag");

    PointLight light(shaderManager);
    light.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    auto locationBindings = std::make_shared<AttributeLocationBindings>();
    locationBindings->addAttributes(smartShaderProgram.get());

    auto primitiveGenerator = PrimitiveGenerator(locationBindings);

    std::vector<Model> models;
    
    {
        Model model(primitiveGenerator.createCube(), smartShaderProgram);
        model.color = glm::vec3(1.0f, 1.0f, 0.0f);
        model.transform.scale = glm::vec3(0.25f, 0.25f, 0.25f);
        model.transform.position = glm::vec3(0.5f, -0.15f, -0.25f);
        models.push_back(std::move(model));
    }
    
    {
        Model model(primitiveGenerator.createSphere(32, 32), smartShaderProgram);
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

    smartShaderProgram->bindUniformBlock(UniformBlockName::camera, cameraUniformBuffer);
    light.program->bindUniformBlock(UniformBlockName::camera, cameraUniformBuffer);

    assert(glGetError() == GL_NO_ERROR);

    Uniform<glm::vec3> colorUniform(smartShaderProgram->getUniformLocation("color"));
    Uniform<glm::vec3> lightColorUniform(smartShaderProgram->getUniformLocation("lightColor"));
    Uniform<glm::vec3> lightPosUniform(smartShaderProgram->getUniformLocation("lightPos"));
    Uniform<glm::vec3> viewPosUniform(smartShaderProgram->getUniformLocation("viewPos"));
    Uniform<glm::mat4> modelMatrixUniform(smartShaderProgram->getUniformLocation(UniformName::modelMatrix));

    while (wnd->isRunning()) {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = (float)Time::getTime();
        //*
        light.position = glm::vec3(0.0f);
        light.position.x = sinf(time * 0.9f) * 1.2f;
        light.position.y = sinf(time * 0.2f) * 0.8f;
        light.position.z = sinf(time * 2.0f) * 0.6f;
        /*/
        light.position = controls->getEyePosition();
        //*/

        cameraUniformBuffer.bindBlock();
        glm::mat4 viewMat = controls->getViewMatrix();
        cameraUniformBuffer.write(glm::value_ptr(viewMat), 0, sizeof(viewMat));
        UniformBuffer::unbind();

        light.draw(); // gizmos

        for (const auto& model : models) {
            model.program->use();
            colorUniform.set(model.color);
            lightColorUniform.set(light.lightColor);
            lightPosUniform.set(light.position);
            viewPosUniform.set(controls->getEyePosition());
            modelMatrixUniform.set(model.transform.getTransformationMatrix());
            model.mesh.draw();
        }

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
