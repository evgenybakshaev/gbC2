cmake_minimum_required(VERSION 3.5)

project(Homework2 LANGUAGES C)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(${PROJECT_NAME} ${sources} ${headers})
