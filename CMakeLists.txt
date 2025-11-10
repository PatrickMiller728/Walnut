cmake_minimum_required(VERSION 3.30.1)
project(walnut)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(spdlog REQUIRED)
find_package(Vulkan REQUIRED)
find_package(yaml-cpp REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI/Walnut/**.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI/Walnut/**.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source/Walnut/**.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source/Walnut/**.cpp
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI)

add_subdirectory(example)