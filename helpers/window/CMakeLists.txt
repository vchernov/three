add_library(window
    IWindow.h
    Window.h
    Window.cpp
    OrbitWindow.h
    OrbitWindow.cpp
    WindowFactory.h
    WindowFactory.cpp
    Time.h
    Time.cpp
)

find_package(glfw3 REQUIRED)

target_link_libraries(window
    PRIVATE glfw
    PUBLIC engine
)
