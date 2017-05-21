#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IWindow.h"

class Window : public IWindow {
public:
    Window(const std::string& title, int width, int height);
    ~Window() override;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool isRunning() const override;
    void processEvents() override;
    void swapBuffers() override;

    int getWidth() const override;
    int getHeight() const override;

private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

    int width;
    int height;

    GLFWwindow* window;
};
