cmake_minimum_required(VERSION 3.8)
project(data_org)

#Find and include all source .cpp files
file(GLOB SOURCES "src/*.cpp")
include_directories(src)

# Create executable
add_executable(data_org ${SOURCES})

