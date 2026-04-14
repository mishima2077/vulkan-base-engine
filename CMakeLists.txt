cmake_minimum_required(VERSION 3.20)
project(VulkanTest)

set(CMAKE_CXX_STANDARD 20)
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

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(VulkanTest PRIVATE RELEASE)
endif()

# Link the libraries to our executable
target_link_libraries(VulkanTest PRIVATE 
    Vulkan::Vulkan 
    glfw 
    glm::glm
)

# Create the executable
add_executable(VulkanTestNew main_new.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(VulkanTestNew PRIVATE RELEASE)
endif()

# Link the libraries to our executable
target_link_libraries(VulkanTestNew PRIVATE 
    Vulkan::Vulkan 
    glfw 
    glm::glm
)

# -----------------------------------------------------------------------------
# Shader compilation setup
# -----------------------------------------------------------------------------

find_program(GLSLC_EXECUTABLE NAMES glslc HINTS "$ENV{VULKAN_SDK}/Bin" "$ENV{VULKAN_SDK}/bin")
if(NOT GLSLC_EXECUTABLE)
    message(FATAL_ERROR "glslc not found! Please install Vulkan SDK or add glslc to PATH.")
endif()

file(GLOB SHADER_SOURCES "${CMAKE_SOURCE_DIR}/shaders/*.vert" "${CMAKE_SOURCE_DIR}/shaders/*.frag")

set(COMPILED_SHADERS "")
foreach(SHADER ${SHADER_SOURCES})
    get_filename_component(FILE_NAME ${SHADER} NAME_WE) # name without extension
    get_filename_component(FILE_EXT ${SHADER} EXT)      # extension, e.g. ".vert"

    # Map extension to spv filename
    if(FILE_EXT STREQUAL ".vert")
        set(SPV_NAME "vert.spv")
    elseif(FILE_EXT STREQUAL ".frag")
        set(SPV_NAME "frag.spv")
    else()
        message(FATAL_ERROR "Unknown shader extension: ${FILE_EXT}")
    endif()

    set(SPV_FILE "${CMAKE_BINARY_DIR}/shaders/${SPV_NAME}")

    add_custom_command(
        OUTPUT ${SPV_FILE}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/shaders"
        COMMAND ${GLSLC_EXECUTABLE} ${SHADER} -o ${SPV_FILE}
        DEPENDS ${SHADER}
        COMMENT "Compiling shader ${FILE_NAME}${FILE_EXT} -> ${SPV_NAME}"
        VERBATIM
    )

    list(APPEND COMPILED_SHADERS ${SPV_FILE})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${COMPILED_SHADERS})

add_dependencies(VulkanTest Shaders)

add_custom_command(TARGET VulkanTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:VulkanTest>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/shaders"
            "$<TARGET_FILE_DIR:VulkanTest>/shaders"
)

add_dependencies(VulkanTestNew Shaders)

add_custom_command(TARGET VulkanTestNew POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:VulkanTest>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/shaders"
            "$<TARGET_FILE_DIR:VulkanTest>/shaders"
)
