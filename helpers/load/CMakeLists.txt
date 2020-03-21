add_library(load
    ModelLoader.h
    ModelLoader.cpp
    gltf.h
    gltf.cpp
)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(load
    PRIVATE
        nlohmann_json::nlohmann_json
    PUBLIC
		engine
)
