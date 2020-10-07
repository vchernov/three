#include <iostream>

#include <GL/glew.h>

#include "../../helpers/engine/fs/FileSystem.h"
#include "../../helpers/load/ModelLoader.h"
#include "../../helpers/window/WindowFactory.h"

using namespace three;

int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;
    std::cout << std::boolalpha;
    std::cout << FileSystem::getCurrentDirectory() << std::endl;

    std::string modelFn;
    if (argc > 1)
        modelFn = argv[1];

    auto controls = std::make_shared<OrbitControls>();
    controls->setRotationSpeed(0.5f);
    controls->setZoomSpeed(0.2f);
    controls->setMoveSpeed(0.005f);
    auto wnd = WindowFactory::createWindowWithOrbitCamera("glTF Loading Example", 1024, 768, controls);

    std::vector<Scene> scenes;

    try
    {
        ModelLoader::loadScene(modelFn, scenes);
    }
    catch (FileNotFoundException& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    while (wnd->isRunning())
    {
        wnd->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& scene : scenes)
        {
            scene.draw();
        }

        wnd->swapBuffers();
    }

    std::cout << "end" << std::endl;
    return 0;
}
