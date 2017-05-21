#include "WindowFactory.h"

#include "Window.h"

std::unique_ptr<IWindow> WindowFactory::createApp(const std::string& title, int width, int height) {
    return std::make_unique<Window>(title, width, height);
}
