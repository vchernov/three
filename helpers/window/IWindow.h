#pragma once

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual bool isRunning() const = 0;
    virtual void processEvents() = 0;
    virtual void swapBuffers() = 0;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};
