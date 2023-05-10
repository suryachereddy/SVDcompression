# set cmake version
cmake_minimum_required(VERSION 3.0)

project(
    SVDcompress
    )

# set c++ standard
set(CMAKE_CXX_STANDARD 11)
find_package( OpenCV REQUIRED )

find_package (Eigen3 3.3 REQUIRED)

set(INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIRECTORIES})
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(svd ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries( svd ${OpenCV_LIBS} )
target_link_libraries (svd Eigen3::Eigen)
