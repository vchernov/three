add_library(load
    ModelLoader.h
    ModelLoader.cpp
)

find_package(fx-gltf REQUIRED)

target_include_directories(load
    PRIVATE ${fx-gltf_INCLUDE_DIRS}
)

target_link_libraries(load
    PUBLIC engine
)
