set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

file(GLOB_RECURSE srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(offscreen_rt STATIC ${srcs})

target_include_directories(offscreen_rt PUBLIC
    ${include_dirs}
)

target_include_directories(offscreen_rt SYSTEM PUBLIC ${LIBYUV_INCLUDE_DIRS})

target_link_libraries(offscreen_rt
    bnb_effect_player
    glad
    glfw
    yuv
)