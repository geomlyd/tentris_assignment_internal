cmake_minimum_required(VERSION 3.22)

project(PersistentShapeContainer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(doctest REQUIRED)

add_library(shape_abstract INTERFACE)

target_include_directories(shape_abstract INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)

add_library(shape_impl
    src/triangle.cpp
    src/geometry_utils.cpp
    src/simple_quadrilateral.cpp
)

target_link_libraries(shape_impl PUBLIC shape_abstract)

target_include_directories(shape_impl PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

add_library(persistent_shape_container INTERFACE)

target_link_libraries(persistent_shape_container INTERFACE shape_abstract)

target_include_directories(persistent_shape_container INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)

add_library(serializers INTERFACE)

target_include_directories(serializers INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(serializers INTERFACE shape_impl)

add_executable(demo
    src/main.cpp
)

target_link_libraries(demo PRIVATE
    shape_impl
    serializers
    persistent_shape_container
)

enable_testing()

add_executable(tests
    tests/test_main.cpp
    tests/test_geometry_utils.cpp
    tests/test_triangle.cpp
    tests/test_simple_quadrilateral.cpp
)

target_link_libraries(tests PRIVATE
    doctest::doctest
    shape_impl
    serializers
    persistent_shape_container
)