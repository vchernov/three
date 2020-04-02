#include <array>
#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <lyra/lyra.hpp>

#include "../three/shader/ShaderProgram.h"

#include "../helpers/engine/ShaderUtils.h"
#include "../helpers/engine/fs/FileSystem.h"
#include "../helpers/window/Time.h"
#include "../helpers/window/WindowFactory.h"
#include "../three/mesh/IndexBuffer.h"
#include "../three/mesh/VertexArrayObject.h"
#include "../three/mesh/VertexBuffer.h"
#include "../three/shader/Uniform.h"

int main(int argc, char** argv)
{
    bool showHelp = false;
    int width = 1024;
    int height = 768;
    std::string fragShaderFn;

    const auto cli = lyra::help(showHelp)
        | lyra::opt(width, "width")["-w"]["--width"]("How wide should it be?")
        | lyra::opt(height, "height")["-x"]["--height"]("How high should it be?")
        | lyra::opt(fragShaderFn, "fragment shader")["-f"]["--frag"]("Fragment shader file name.").required();

    const auto argParseResult = cli.parse({argc, argv});
    if (!argParseResult)
    {
        std::cerr << argParseResult.errorMessage() << std::endl;
        std::cerr << cli << std::endl;
        return 1;
    }

    if (showHelp)
    {
        std::cerr << cli << std::endl;
        return 0;
    }

    auto wnd = WindowFactory::createWindow(fragShaderFn, width, height);

    three::ShaderProgram program;
    try
    {
        std::cout << std::boolalpha;
        program = ShaderUtils::loadShaderProgram("shaderviewer.vert", fragShaderFn);
    }
    catch (FileNotFoundException& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    program.use();

    three::Uniform<glm::vec2>::update(program.getUniformLocation("u_resolution"), {width, height});
    int timeUniformLoc = program.getUniformLocation("u_time");

    three::VertexArrayObject vao;
    vao.bind();

    glm::vec2 vertices[] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    three::VertexBuffer vertexBuffer;
    vertexBuffer.bind();
    three::VertexBuffer::allocate(4 * sizeof(glm::vec2), vertices);

    unsigned short indices[] = {0, 1, 2, 0, 2, 3};
    three::IndexBuffer indexBuffer;
    indexBuffer.bind();
    indexBuffer.allocate(GL_UNSIGNED_SHORT, sizeof(unsigned short), 6, indices);

    vao.registerAttribute(three::VertexAttribute::create<float>(0, 2, 0, sizeof(glm::vec2)));
    vao.enableAttribute(0);

    while (wnd->isRunning())
    {
        wnd->processEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        float time = (float)Time::getTime();
        three::Uniform<float>::update(timeUniformLoc, time);

        indexBuffer.draw(GL_TRIANGLES);
        wnd->swapBuffers();
    }

    return 0;
}
