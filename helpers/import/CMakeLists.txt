add_library(import
    ModelImporter.h
    ModelImporter.cpp
	assimpHelpers.h
	assimpHelpers.cpp
	DynamicModelImporter.h
	DynamicModelImporter.cpp
)

find_package(assimp CONFIG REQUIRED)

target_link_libraries(import
    PRIVATE
		assimp::assimp
    PUBLIC
		engine
)
