#include "Time.h"

#include <GLFW/glfw3.h>

double Time::getTime()
{
    return glfwGetTime();
}
