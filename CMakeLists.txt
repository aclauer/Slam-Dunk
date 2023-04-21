cmake_minimum_required(VERSION 3.10)

project(slam_dunk)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLFW3_INCLUDE_DIRS})

set(SOURCES
    test.cpp
    resources/shaderClass.cpp
    resources/EBO.cpp
    resources/VAO.cpp
    resources/VBO.cpp
)

set(HEADERS
    resources/shaderClass.h
    resources/EBO.h
    resources/VAO.h
    resources/VBO.h
)

add_executable(slam_dunk ${SOURCES} ${HEADERS})

target_link_libraries(slam_dunk glfw)
target_link_libraries(slam_dunk GLEW)
target_link_libraries(slam_dunk GL)
