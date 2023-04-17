cmake_minimum_required(VERSION 3.10)

project(slam_dunk)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLFW3_INCLUDE_DIRS})
add_executable(slam_dunk test.cpp)

target_link_libraries(slam_dunk glfw)
target_link_libraries(slam_dunk GLEW)
target_link_libraries(slam_dunk GL)
