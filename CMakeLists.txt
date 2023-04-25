cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(slam_dunk)

find_package(PCL 1.3 REQUIRED COMPONENTS common io)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})



add_definitions(${PCL_DEFINITIONS})

set(SOURCES
    main.cpp
)

set(HEADERS

)

add_executable(slam_dunk ${SOURCES} ${HEADERS})
target_link_libraries(slam_dunk ${PCL_LIBRARIES})
target_link_libraries(slam_dunk pcl_visualization)