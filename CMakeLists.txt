cmake_minimum_required(VERSION 3.31.6)
project(walnut CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)

# add imgui
file(GLOB IMGUI_SRC
        "vendor/imgui/*.cpp"
        "vendor/imgui/backends/imgui_impl_glfw.cpp"
        "vendor/imgui/backends/imgui_impl_vulkan.cpp"
)
add_library(imgui STATIC ${IMGUI_SRC})
target_link_libraries(imgui PUBLIC glfw)
target_include_directories(imgui PUBLIC "vendor/imgui")

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/GUI)

include_directories(${PROJECT_NAME} PRIVATE Platform/GUI/Walnut/ImGui ${Vulkan_INCLUDE_DIRS})

file(GLOB_RECURSE ${PROJECT_NAME}_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI/Walnut/**.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI/Walnut/**.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source/Walnut/**.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source/Walnut/**.cpp
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})