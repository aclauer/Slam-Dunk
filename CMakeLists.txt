cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(slam_dunk)

find_package(PCL 1.3 REQUIRED COMPONENTS common io)
find_package(OpenCV REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})

add_definitions(${PCL_DEFINITIONS})

set(SOURCES
    main.cpp
    Preprocessor.cpp
)

set(HEADERS
    Preprocessor.h
)

add_executable(slam_dunk ${SOURCES} ${HEADERS})
target_link_libraries(slam_dunk ${PCL_LIBRARIES})
target_link_libraries(slam_dunk pcl_visualization)
target_link_libraries(slam_dunk ${OpenCV_LIBS})
