#pragma once

#include <memory>
#include <string>

#include "IWindow.h"

class WindowFactory {
public:
    static std::unique_ptr<IWindow> createApp(const std::string& title, int width, int height);
};
