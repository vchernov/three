add_library(image
    ImageUtils.h
    ImageUtils.cpp
)

target_link_libraries(image
    PUBLIC
		engine
)
