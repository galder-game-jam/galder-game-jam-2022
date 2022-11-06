project(gamedev_base_tests VERSION 1.0.0)

add_executable(gamedev_base_tests main_tests.cpp logger_tests.cpp input_tests.cpp)

target_link_libraries(gamedev_base_tests raylib_template_library raylib_cpp raylib fmt box2d)