cmake_minimum_required(VERSION 3.30.1)
project(walnut)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(spdlog REQUIRED)
find_package(Vulkan REQUIRED)
find_package(yaml-cpp REQUIRED)

set(SOURCE_FILES
        Walnut/Platform/GUI/Walnut/ApplicationGUI.cpp
        Walnut/Platform/GUI/Walnut/Image.cpp
        Walnut/Platform/GUI/Walnut/ImGui/ImGuiBuild.cpp
        Walnut/Platform/GUI/Walnut/ImGui/ImGuiTheme.cpp
        Walnut/Platform/GUI/Walnut/Input/Input.cpp
        Walnut/Platform/GUI/Walnut/UI/Console.cpp
        Walnut/Platform/GUI/Walnut/UI/UI.cpp
        Walnut/Source/Walnut/Random.cpp
        Walnut/Source/Walnut/Core/Log.cpp
        Walnut/Source/Walnut/Serialization/BufferStream.cpp
        Walnut/Source/Walnut/Serialization/FileStream.cpp
        Walnut/Source/Walnut/Serialization/StreamReader.cpp
        Walnut/Source/Walnut/Serialization/StreamWriter.cpp
        Walnut/Source/Walnut/Utils/StringUtils.cpp
)

set(API_HEADERS
        Walnut/Platform/GUI/Walnut/ApplicationGUI.h
        Walnut/Platform/GUI/Walnut/Image.h
        Walnut/Platform/GUI/Walnut/ImGui/ImGuiTheme.h
        Walnut/Platform/GUI/Walnut/Input/Input.h
        Walnut/Platform/GUI/Walnut/Input/KeyCodes.h
        Walnut/Platform/GUI/Walnut/UI/Console.h
        Walnut/Platform/GUI/Walnut/UI/UI.h
        Walnut/Source/Walnut/Application.h
        Walnut/Source/Walnut/EntryPoint.h
        Walnut/Source/Walnut/Layer.h
        Walnut/Source/Walnut/Random.h
        Walnut/Source/Walnut/Timer.h
        Walnut/Source/Walnut/Core/Assert.h
        Walnut/Source/Walnut/Core/Buffer.h
        Walnut/Source/Walnut/Core/Log.h
        Walnut/Source/Walnut/Core/LogCustomFormatters.h
        Walnut/Source/Walnut/Serialization/BufferStream.h
        Walnut/Source/Walnut/Serialization/FileStream.h
        Walnut/Source/Walnut/Serialization/StreamReader.h
        Walnut/Source/Walnut/Serialization/StreamWriter.h
        Walnut/Source/Walnut/Utils/StringUtils.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${API_HEADERS})

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
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>  # for client in install mode
)

# https://github.com/fmtlib/fmt/blob/master/CMakeLists.txt

add_subdirectory(example)

# This section is essential for the dependent library targets to be properly exported
# for vcpkg to consume the library target(s) for this project.

include(CMakePackageConfigHelpers)

# Install the library and its headers
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/walnut"
)

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