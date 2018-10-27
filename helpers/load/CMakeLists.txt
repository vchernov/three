add_library(load
    ModelLoader.h
    ModelLoader.cpp
)

target_link_libraries(load
    PUBLIC
		engine
)
