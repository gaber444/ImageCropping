cmake_minimum_required(VERSION 3.20.0)
project(branje)

set(CMAKE_CXX_STANDARD 17)
message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

find_package(OpenCV REQUIRED)

add_subdirectory(src)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(karkulator-lib ${OpenCV_LIBS})

add_executable(branje-executable src/main.cpp)

target_link_libraries(branje-executable PRIVATE karkulator-lib)