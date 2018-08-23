add_library(image
    ImageUtils.h
    ImageUtils.cpp
)

find_package(stb REQUIRED)

target_include_directories(image
    PRIVATE ${stb_INCLUDE_DIRS}
)

target_link_libraries(image
    PUBLIC engine
)
