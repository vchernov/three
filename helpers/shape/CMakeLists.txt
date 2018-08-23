add_library(shape
    Shape.h
    Shape.cpp
)

find_package(par REQUIRED)

target_include_directories(shape
    PRIVATE ${par_INCLUDE_DIRS}
)

target_link_libraries(shape
    PUBLIC engine
)
