cmake_minimum_required(VERSION 3.28)

project(bfx VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include(FetchContent)



add_subdirectory(src)