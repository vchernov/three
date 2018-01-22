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
    glm::vec2 cursorPos(static_cast<float>(xpos), static_cast<float>(ypos));
    glm::vec2 translation = cursorPos - lastCursorPos;

    if (dragButton == GLFW_MOUSE_BUTTON_LEFT) {
        controls->pitch(translation.x);
        controls->yaw(translation.y);
    }

    if (dragButton == GLFW_MOUSE_BUTTON_RIGHT || dragButton == GLFW_MOUSE_BUTTON_MIDDLE) {
        controls->move(-translation.x, translation.y);
    }

    lastCursorPos = cursorPos;
}

void OrbitWindow::handleScroll(double xoffset, double yoffset) {
    Window::handleScroll(xoffset, yoffset);

    controls->zoom(static_cast<float>(yoffset));
}
