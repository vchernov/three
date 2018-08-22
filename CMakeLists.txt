cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(three)

add_subdirectory(three)

option(THREE_ENGINE "Build engine helper library." OFF)
if (THREE_ENGINE)
    add_subdirectory(helpers/engine)
endif()

option(THREE_IMAGE "Build image helper library." OFF)
if (THREE_IMAGE)
    add_subdirectory(helpers/image)
endif()

option(THREE_SHAPE "Build shape helper library." OFF)
if (THREE_SHAPE)
    add_subdirectory(helpers/shape)
endif()

option(THREE_WINDOW "Build window helper library." OFF)
if (THREE_WINDOW)
    add_subdirectory(helpers/window)
endif()

option(THREE_IMPORT "Build import helper library." OFF)
if (THREE_IMPORT)
    add_subdirectory(helpers/import)
endif()

option(THREE_BUILD_EXAMPLES "Build examples." OFF)
if (THREE_BUILD_EXAMPLES)
    add_subdirectory(examples/camera)
    add_subdirectory(examples/primitives)
    add_subdirectory(examples/lighting)
    add_subdirectory(examples/texturing)
    add_subdirectory(examples/loader)
endif()
