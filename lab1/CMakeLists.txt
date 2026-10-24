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
  URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.4.0.tar.gz
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
include(Catch)
catch_discover_tests(lab1_tests)

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

if(ENABLE_COVERAGE)
    target_compile_options(lab1_tests PRIVATE --coverage)
    target_link_options(lab1_tests PRIVATE --coverage)

    find_program(GCOVR_EXECUTABLE gcovr)

    if(GCOVR_EXECUTABLE)
        add_custom_target(coverage
            COMMAND ctest --output-on-failure
            COMMAND ${GCOVR_EXECUTABLE} -r ${CMAKE_SOURCE_DIR} --exclude ".*_deps.*" --exclude ".*tests.*"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS lab1_tests
            COMMENT "Запуск тестов и подсчет покрытия..."
        )
    else()
        message(WARNING "Утилита gcovr не найдена. Установите её командой: sudo apt install gcovr")
    endif()
endif()
