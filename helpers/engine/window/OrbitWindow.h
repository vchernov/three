#pragma once

#include <memory>

#include "Window.h"
#include "../../../three/camera/OrbitControls.h"

class OrbitWindow : public Window {
public:
    OrbitWindow(const std::string& title, int width, int height,
        std::shared_ptr<three::OrbitControls> controls);

protected:
    void handleKey(int key, int scancode, int action, int mods) override;
    void handleMouseButton(int button, int action, int mods) override;
    void handleCursorPosition(double xpos, double ypos) override;
    void handleScroll(double xoffset, double yoffset) override;

private:
    static const int invalidButton = -1;

    std::shared_ptr<three::OrbitControls> controls;
    int dragButton = invalidButton;
    glm::dvec2 lastCursorPos;
};
