cmake_minimum_required(VERSION 3.7)

project(hclust)

option(HCLUST_BUILD_DEMO "Build demo application" ON)
enable_language(C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(hclust)
target_include_directories(hclust PRIVATE ./)

target_sources(hclust PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/fastcluster.cpp
)


if ( ${HCLUST_BUILD_DEMO} )
    add_executable(hclust-demo demo.cpp)
    target_include_directories(hclust-demo PRIVATE ./)
    target_link_libraries(hclust-demo hclust)
endif()