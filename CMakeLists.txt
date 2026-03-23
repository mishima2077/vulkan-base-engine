cmake_minimum_required(VERSION 3.20)
project(VulkanTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find our packages
find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Create the executable
add_executable(VulkanTest main.cpp)

# Link the libraries to our executable
target_link_libraries(VulkanTest PRIVATE 
    Vulkan::Vulkan 
    glfw 
    glm::glm
)