cmake_minimum_required(VERSION 3.31.6)
project(walnut-example)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} DemoWindow.cpp)

target_link_libraries(${PROJECT_NAME} walnut)