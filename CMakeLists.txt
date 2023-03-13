cmake_minimum_required(VERSION 3.0.0)
project(td5 VERSION 0.1.0)

include(CTest)
enable_testing()

set (CMAKE_CXX_STANDARD 20)

add_executable(td5 main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
