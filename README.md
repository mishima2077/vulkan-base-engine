# Vulkan Base Setup

A minimal, explicit Vulkan rendering pipeline built from scratch in C++. 
This repository serves as a boilerplate for future low-level systems and graphics programming projects.

At first I vibecoded it, it worked but I didn't get much value out of it. Then I started to write the current repo, I am following this tutorial:
https://vulkan-tutorial.com/Introduction

now instead of %5, I understand around %50 of the code, maybe more. Great Success!

## Current Capabilities
- Sets up all the necessary vulkan initialization to draw a triangle.
- Has a resizable glfw window.
- Uses vertex buffers to transfer data to shaders.

## TODO
- Use SDL instead of GLFW.
- ...

## How to Build (Windows)
1. Ensure Visual Studio 2022 (with C++ CMake tools) and the LunarG Vulkan SDK are installed.
2. Install dependencies via vcpkg: `vcpkg install glfw3 glm`
3. Open the folder in Visual Studio, point the CMake toolchain to your vcpkg installation, and build.

## Author
Adil Mert Ergörün
