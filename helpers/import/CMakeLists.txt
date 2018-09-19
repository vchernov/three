add_library(import
    ModelImporter.h
    ModelImporter.cpp
)

find_package(assimp REQUIRED)

target_link_libraries(import
    PRIVATE assimp
    PUBLIC engine
)
