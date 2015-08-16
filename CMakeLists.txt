project(libpdf-separate-build)
cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)
pkg_check_modules(REQ nspr REQUIRED)

include_directories("${REQ_INCLUDE_DIRS}")
link_directories(${REQ_LIBRARY_DIRS})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -pthread")

add_subdirectory(src)
