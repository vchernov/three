add_library(shape
    Shape.h
    Shape.cpp
)

target_link_libraries(shape
    PUBLIC
		engine
)
