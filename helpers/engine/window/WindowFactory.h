#pragma once

#include <memory>
#include <string>

#include "IWindow.h"

#include "../../../three/camera/OrbitControls.h"

class WindowFactory {
public:
    static std::unique_ptr<IWindow> createWindow(const std::string& title, int width, int height);

    static std::unique_ptr<IWindow> createWindowWithOrbitCamera(const std::string& title, int width, int height,
        std::shared_ptr<three::OrbitControls> controls);
};
