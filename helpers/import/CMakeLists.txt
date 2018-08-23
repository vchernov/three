add_library(import
    ModelLoader.h
    ModelLoader.cpp
)

find_package(assimp REQUIRED)

target_link_libraries(import
    PRIVATE assimp
    PUBLIC engine
)
