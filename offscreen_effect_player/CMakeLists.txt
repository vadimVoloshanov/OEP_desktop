set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

file(GLOB_RECURSE srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(offscreen_ep STATIC ${srcs})

target_include_directories(offscreen_ep PUBLIC
    ${include_dirs}
)

target_include_directories(offscreen_ep SYSTEM PUBLIC ${LIBYUV_INCLUDE_DIRS})

target_link_libraries(offscreen_ep
    Async++
    bnb_effect_player
    glad
    offscreen_rt
    yuv
)