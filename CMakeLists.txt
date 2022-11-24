cmake_minimum_required(VERSION 3.23)
project(galder-game-jam-2022-project VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DGAME_DEV_DEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
            FORCE)

endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG 1)
    message(STATUS "DEBUGGIN'")
else()
    set(RELEASE 1)
    message(STATUS "RELEASE")
endif()

set(LINUX 0)
set(WINDOWS 0)
set(APPLE 0)
set(MSVC 0)
set(MINGW 0)

if(UNIX AND NOT APPLE)
    message(STATUS "It's Linux!")
    set(LINUX 1)
elseif(APPLE)
    message(STATUS "It's Apple!")
    link_directories(/usr/local/opt/llvm/lib/)
    set(APPLE 1)
elseif(WIN32)
    set(WINDOWS 1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    if(MSVC)
        message(STATUS "It's MSVC!")
        set(MSVC 1)
    elseif(MINGW)
        message(STATUS "It's probably MinGW!")
        set(MINGW 1)
    endif()
endif()

# Makes sure everything is statically linked
set(BUILD_SHARED_LIBS OFF)

include_directories(${PROJECT_SOURCE_DIR}/external_libs
                    ${PROJECT_SOURCE_DIR}/external_libs/raylib/src
                    ${PROJECT_SOURCE_DIR}/external_libs/raylib-cpp/include
                    ${PROJECT_SOURCE_DIR}/external_libs/fmt/include
                    ${PROJECT_SOURCE_DIR}/external_libs/box2d/include
        )
add_subdirectory(external_libs/fmt)
add_subdirectory(external_libs/raylib)
add_subdirectory(external_libs/raylib-cpp)
add_subdirectory(external_libs/box2d)
add_subdirectory(src)
add_subdirectory(tests)

