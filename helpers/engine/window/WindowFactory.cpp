#include "WindowFactory.h"

#include "Window.h"
#include "OrbitWindow.h"

std::unique_ptr<IWindow> WindowFactory::createWindow(const std::string& title, int width, int height) {
    return std::make_unique<Window>(title, width, height);
}

std::unique_ptr<IWindow> WindowFactory::createWindowWithOrbitCamera(const std::string& title, int width, int height,
    std::shared_ptr<three::OrbitControls> controls) {
    return std::make_unique<OrbitWindow>(title, width, height, controls);
}
