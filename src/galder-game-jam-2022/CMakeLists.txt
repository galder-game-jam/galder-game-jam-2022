# cmake_minimum_required(VERSION 3.23)
project(galder-game-jam-2022 VERSION 0.1.0)

# set(CMAKE_CXX_STANDARD 20)

# Copies game content to the executable folder when CMake file is loaded.
file(COPY ${CMAKE_SOURCE_DIR}/content/game/content DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(galder-game-jam-2022 main.cpp)

if(LINUX)
    target_link_libraries(galder-game-jam-2022 galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d)
elseif(WINDOWS)
    target_link_libraries(galder-game-jam-2022 galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d)
else()
    target_link_libraries(galder-game-jam-2022 galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d)

endif()