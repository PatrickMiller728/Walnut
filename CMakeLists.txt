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

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image>   # for headers when building
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Source>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Walnut/Platform/GUI>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/vendor/stb_image>     # for client in install mode
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Walnut/Source>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Walnut/Platform/GUI>
)

add_subdirectory(example)

# This section is essential for the dependent library targets to be properly exported
# for vcpkg to consume the library target(s) for this project.

include(CMakePackageConfigHelpers)

# Install the library and its headers
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# Export all targets
install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE Walnut:: # Give each library a namespace which will create an alias library
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Generate and install the Config file
configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)