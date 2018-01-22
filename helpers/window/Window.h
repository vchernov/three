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

protected:
    virtual void handleKey(int key, int scancode, int action, int mods);
    virtual void handleMouseButton(int button, int action, int mods);
    virtual void handleCursorPosition(double xpos, double ypos);
    virtual void handleScroll(double xoffset, double yoffset);

private:
    static void errorCallback(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    int width;
    int height;

    GLFWwindow* window;
};
