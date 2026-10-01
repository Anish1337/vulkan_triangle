cmake_minimum_required(VERSION 3.20)

project(vulkan_triangle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

add_executable(vulkan_triangle
    src/main.cpp
)

target_link_libraries(vulkan_triangle PRIVATE
    Vulkan::Vulkan
)