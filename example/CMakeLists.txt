cmake_minimum_required(VERSION 3.30.1)
project(walnut-example)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} DemoWindow.cpp Source/AppLayer.cpp Source/DefaultLayer.cpp)

target_link_libraries(${PROJECT_NAME} walnut)