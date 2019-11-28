# cmake_minimum_required(VERSION <specify CMake version here>)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project(ForestCreator)

set(CMAKE_CXX_STANDARD 11)

add_executable(ForestCreator main.cpp Cell.cpp Cell.h Forest.cpp Forest.h)