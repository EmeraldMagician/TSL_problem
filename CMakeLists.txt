cmake_minimum_required(VERSION 3.5)

project(TSL_problem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TSL_problem main.cpp testing.hpp common.hpp
                stupid.hpp linear.hpp dynamic.hpp genetic.hpp
                2opt.hpp lkh.hpp research.hpp)
               #numbers.hpp numbers.cpp
               #funcs.hpp funcs.cpp
               #glut_funcs.hpp glut_funcs.cpp)
target_link_libraries(TSL_problem GL glut)
