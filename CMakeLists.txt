cmake_minimum_required(VERSION 3.20)
project(DA_PROJ_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp include/utils.h src/utils.cpp include/Menu.h src/Menu.cpp src/Company.cpp include/Company.h include/constants.h)
