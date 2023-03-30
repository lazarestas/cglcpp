cmake_minimum_required(VERSION 3.24)
project(conway)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

add_executable(conway main.cpp include/logic.h include/console.h include/window.h)
target_link_libraries(conway sfml-graphics)