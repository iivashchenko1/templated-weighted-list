cmake_minimum_required(VERSION 3.16)
project(templated_weighted_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(weighted_list INTERFACE)
target_include_directories(weighted_list INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(weighted_list_example examples/example.cpp)
target_link_libraries(weighted_list_example PRIVATE weighted_list)

add_executable(weighted_list_tests tests/weighted_list_tests.cpp)
target_link_libraries(weighted_list_tests PRIVATE weighted_list)

enable_testing()
add_test(NAME weighted_list_tests COMMAND weighted_list_tests)
