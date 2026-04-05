cmake_minimum_required(VERSION 3.20)
project(VulkanTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# On Apple Silicon, help CMake find Homebrew packages
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

# Find our packages
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Create the executable
add_executable(VulkanTest main.cpp)

# Link the libraries to our executable
target_link_libraries(VulkanTest PRIVATE 
    Vulkan::Vulkan 
    glfw 
    glm::glm
)

# Copy shaders directory next to the executable
add_custom_command(TARGET VulkanTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:VulkanTest>/shaders"
)