project(galder-game-jam-library-tests VERSION 1.0.0)

add_executable(galder-game-jam-library-tests main_tests.cpp logger_tests.cpp input_tests.cpp)

target_link_libraries(galder-game-jam-library-tests galder-game-jam-library raylib_cpp raylib fmt box2d)