cmake_minimum_required(VERSION 3.28)
project(local_link CXX)
set(CMAKE_CXX_STANDARD 20)

if (EXISTS "${CMAKE_SOURCE_DIR}/local.cmake")
    include("${CMAKE_SOURCE_DIR}/local.cmake")
    message(STATUS "Included local.cmake")
endif ()
find_package(Qt6 REQUIRED COMPONENTS Core Gui Multimedia Qml Quick Network Test)
qt_standard_project_setup()

add_subdirectory(src)
enable_testing()
add_subdirectory(test/unit)