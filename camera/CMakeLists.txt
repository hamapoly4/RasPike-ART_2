cmake_minimum_required(VERSION 2.8)
project(capture)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(capture capture.cpp)
target_link_libraries(capture ${OpenCV_LIBS})

