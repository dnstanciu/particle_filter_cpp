cmake_minimum_required(VERSION 2.8.4)
project(particle_filter_cpp)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

set(SOURCE_FILES src/main.cpp src/Particle.cpp src/Utils.cpp src/World.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/dragos/DTC/PhD/particle_filter_cpp/bin")

add_executable(particle_filter_cpp ${SOURCE_FILES})

target_link_libraries( particle_filter_cpp ${OpenCV_LIBS} )