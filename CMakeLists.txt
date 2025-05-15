cmake_minimum_required(VERSION 3.31.6)
project(walnut)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/yaml-cpp)

# add imgui
file(GLOB IMGUI_SRC
        "vendor/imgui/*.cpp"
        "vendor/imgui/backends/imgui_impl_glfw.cpp"
        "vendor/imgui/backends/imgui_impl_vulkan.cpp"
)
add_library(imgui STATIC ${IMGUI_SRC})
target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(imgui PUBLIC Vulkan::Vulkan)
target_include_directories(imgui PUBLIC "vendor/imgui")

file(GLOB_RECURSE ${PROJECT_NAME}_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI/Walnut/**.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI/Walnut/**.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source/Walnut/**.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source/Walnut/**.cpp
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp)

include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image)
include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source)
include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI)