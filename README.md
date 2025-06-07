# Walnut
Walnut is a simple application framework built with Dear ImGui and designed to be used with Vulkan - basically this means you can seamlessly blend real-time Vulkan rendering with a great UI library to build desktop applications. The plan is to expand Walnut to include common utilities to make immediate-mode desktop apps and simple Vulkan applications.

Currently only supports Windows - with macOS and Linux support planned.

- [About This Fork](#about-this-fork)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
  - [3rd Party Libraries](#3rd-party-libaries)
  - [Overlay Ports](#overlay-ports)
  - [Additional](#additional)
- [Using This Repository](#using-this-repository)

![WalnutExample](https://hazelengine.com/images/ForestLauncherScreenshot.jpg)
_<center>Forest Launcher - an application made with Walnut</center>_

## About This Fork
Walnut is a framework built by [TheCherno](https://www.youtube.com/@TheCherno). This fork is built on top of the dev branch of Walnut.

The major changes made have been with the build system, using CMake instead of Premake. In addition, the fork now uses vcpkg as a dependency manager. Other changes include necessary bug fixes caused by the different versions of dependencies.

Any additional changes are meant to be additive: keeping the original source code and file structure in-tact as much as possible.
## Requirements
- [CMake](https://cmake.org/)
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows) (preferably a recent version)

## Getting Started
Clone the repository:

This fork of Walnut uses [vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/overview) as a package manager, included as a submodule.
Navigate to the vcpkg directory and run `bootstrap-vcpkg.bat`:
```commandline
cd <path\to\vcpkg\bootstrap-vcpkg.bat>
bootstrap-vcpkg.bat
```

Included is the default vcpkg CMake preset found in `CMakePresets.json`. As per [vcpkg documentation](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd#4---build-and-run-the-project), you will want to create `CMakeUserPresets.json` in the root directory containing the following:
```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "<path to vcpkg>"
      }
    }
  ]
}
```
It is recommended *not* to add `CMakeUserPresets.json` to source control.

Configure the build using CMake:
```commandline
cmake --preset=default
```
Build the Project:
```commandline
cmake --build build
```

### 3rd party libaries
- [vcpkg](https://vcpkg.io/en/)
  - [Dear ImGui](https://github.com/ocornut/imgui)
  - [GLFW](https://github.com/glfw/glfw)
  - [spdlog](https://github.com/gabime/spdlog)
  - [yaml-cpp](https://github.com/jbeder/yaml-cpp)
  - [GLM](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb) (included as a header file, but *could* be added through vcpkg if desired)

I decided to use vcpkg *mostly* out of convenience, to keep dependencies as current as possible, and as an exercise to learn it. This creates a few issues, as Walnut originally used forks of ImGui and GLFW. This *can* be solved by using vcpkg's [Overlay Ports](https://learn.microsoft.com/en-us/vcpkg/concepts/overlay-ports), although I am unsure that this is truly the best way. 

### Overlay Ports
- Dear ImGui
  - Walnut uses Stack Layouts (PR [ocornut#846](https://github.com/ocornut/imgui/pull/846)). To implement this, the overlay port forces vcpkg to use thedmd's [feature/docking-layout-external](https://github.com/thedmd/imgui/tree/feature/docking-layout-external) fork instead of the base imgui repository.
  - Version: 1.91.0 WIP r19097
- GLFW
  - TheCherno's GLFW fork adds functionality for a resizable, undecorated window. Using this fork is a possibility, like with imgui's overlay port, but has not been updated. Instead, the overlay port applies a patch file.
  - The patch file adds Hazel's implementation for a new Window Hint: `GLFW_TITLEBAR`. When false, GLFW will create a window equivalent to one with no decoration but that can be moved and resized.
  - Admittedly, this feels like a hack. It may be better to either use the aforementioned GLFW fork, or create my own.

### Additional
- Walnut uses the [Roboto](https://fonts.google.com/specimen/Roboto) font ([Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0))

## Using This Repository
Following is a list of possible ways to use Walnut in your own projects.
### Replacing the example app with your own application.

Clone the repository using the `cmake` branch.
```commandline
  git clone -b <branch> <url>
```
Replace `example/DemoWindow.cpp` and update `example/CMakeLists.txt` or add your own folder, source files, and update `CMakeLists.txt`. 

### Include Walnut as a git submodule.
```commandline
git submodule add -b <branch> <url> <path>
```

There are a few caveats to using it as a submodule, entirely caused by vcpkg:
- Vcpkg will look for `vcpkg.json` in the root directory by default. You can change that by manually setting the cache variable `VCPKG_MANIFEST_DIR`.
  - For an example: check out my [Raytracing Project](https://github.com/PatrickMiller728/raytracing).
- Vcpkg currently does not support having two high-level manifest files. If you are using vcpkg in another part of your application, you will need to add Walnut's dependencies to the root `vcpkg.json`.
  - Using the `ExternalProject` CMake Module may fix this.

