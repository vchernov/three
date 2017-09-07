#include "OrbitWindow.h"

OrbitWindow::OrbitWindow(const std::string& title, int width, int height,
    std::shared_ptr<three::OrbitControls> controls)
    :
    Window(title, width, height),
    controls(controls) {
}

void OrbitWindow::handleKey(int key, int scancode, int action, int mods) {
    Window::handleKey(key, scancode, action, mods);
}

void OrbitWindow::handleMouseButton(int button, int action, int mods) {
    Window::handleMouseButton(button, action, mods);

    if (action == GLFW_PRESS && dragButton == invalidButton) {
        dragButton = button;
    } else if (action == GLFW_RELEASE && button == dragButton) {
        dragButton = invalidButton;
    }
}

void OrbitWindow::handleCursorPosition(double xpos, double ypos) {
    glm::dvec2 cursorPos(xpos, ypos);
    glm::dvec2 translation = cursorPos - lastCursorPos;

    if (dragButton == GLFW_MOUSE_BUTTON_LEFT) {
        controls->pitch((float)translation.x);
        controls->yaw((float)translation.y);
    }

    if (dragButton == GLFW_MOUSE_BUTTON_RIGHT || dragButton == GLFW_MOUSE_BUTTON_MIDDLE) {
        controls->move(translation);
    }

    lastCursorPos = cursorPos;
}

void OrbitWindow::handleScroll(double xoffset, double yoffset) {
    Window::handleScroll(xoffset, yoffset);

    controls->zoom((float)yoffset);
}
