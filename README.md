# Vulkan Base Setup

A minimal, explicit Vulkan rendering pipeline built from scratch in C++. 
This repository serves as a boilerplate for future low-level systems and graphics programming projects.

To be fair with you all, I have no idea what is going on. I probably understand 5% of the code,
but still wanted to keep this starting point as I continue learning Vulkan.

## Current Capabilities
- I have no idea it just draws a shiny triangle without any errors. Currently its more than enough.

## How to Build (Windows)
1. Ensure Visual Studio 2022 (with C++ CMake tools) and the LunarG Vulkan SDK are installed.
2. Install dependencies via vcpkg: `vcpkg install glfw3 glm`
3. Open the folder in Visual Studio, point the CMake toolchain to your vcpkg installation, and build.

## Author
Adil Mert Ergörün
