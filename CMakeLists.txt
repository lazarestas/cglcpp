cmake_minimum_required(VERSION 3.24)
project(conway)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:\\Users\\Stas\\Downloads\\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(conway main.cpp logic.h console.h)
target_link_libraries(conway sfml-graphics)