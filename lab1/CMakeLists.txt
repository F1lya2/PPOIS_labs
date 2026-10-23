cmake_minimum_required(VERSION 3.14)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(lab1_app
    app/main.cpp
    src/Post.cpp
    src/Turing.cpp
)
target_include_directories(lab1_app PRIVATE include)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(lab1_tests
    tests/test_post.cpp
    tests/test_turing.cpp
    src/Post.cpp
    src/Turing.cpp
)
target_include_directories(lab1_tests PRIVATE include)
target_link_libraries(lab1_tests PRIVATE Catch2::Catch2WithMain)

enable_testing()
add_test(NAME AllTests COMMAND lab1_tests)
