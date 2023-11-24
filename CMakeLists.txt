cmake_minimum_required(VERSION 3.26)

set(This RasterizationEngine)
project(${This} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${This}
                main.cpp
                Canvas.cpp
                Box.cpp
                Line.cpp
                Mesh.cpp
                Triangle.cpp
                Vector.cpp
                Matrix.cpp
                Shader.cpp
                Texture.cpp
                Vertex.cpp
                Camera.cpp
                Shapes.cpp
                Transformations.cpp)



enable_testing()

add_executable(
        testing_exec
        test/CanvasTest.cpp
        test/VecTest.cpp
        test/TriangleTest.cpp
        Vector.cpp
        Canvas.cpp
        Triangle.cpp
        Line.cpp
)
target_link_libraries(
        testing_exec
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(testing_exec)
