add_library(import
    ModelImporter.h
    ModelImporter.cpp
)

find_package(assimp REQUIRED)

target_include_directories(import
	PRIVATE ${ASSIMP_INCLUDE_DIRS}
)

target_link_libraries(import
    PRIVATE ${ASSIMP_LIBRARIES}
    PUBLIC engine
)
