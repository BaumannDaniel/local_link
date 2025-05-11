cmake_minimum_required(VERSION 3.28)
project(local_link CXX)
set(CMAKE_CXX_STANDARD 20)

set(Qt6_DIR /home/daniel/Qt/6.8.3/gcc_64/lib/cmake/Qt6)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Multimedia Qml Quick Network)
qt_standard_project_setup()

add_subdirectory(src)
enable_testing()
add_subdirectory(test/unit)