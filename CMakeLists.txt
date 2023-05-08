# set cmake version
cmake_minimum_required(VERSION 3.0)

project(
    SVDcompress
    )

# set c++ standard
set(CMAKE_CXX_STANDARD 11)
set(INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIRECTORIES})
add_executable(svd ${PROJECT_SOURCE_DIR}/src/main.cpp)

