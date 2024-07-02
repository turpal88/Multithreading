cmake_minimum_required(VERSION 3.20)
project(Lesson4_Task1 VERSION 1.0)


set(CMAKE_BUILD_TYPE Debug)

add_executable(LT4_1)
add_subdirectory(Shapes)

set_property(TARGET LT4_1 PROPERTY CXX_STANDARD 20)

set(sources ${CMAKE_CURRENT_SOURCE_DIR}/src/sources/lt4_1.cxx)

target_sources(LT4_1 PRIVATE ${sources})

target_include_directories(LT4_1 PRIVATE ${PROJECT_SOURCE_DIR}/Shapes/src/headers)

target_link_libraries(LT4_1 PRIVATE Shapes)

#set(binary_dir ${PROJECT_SOURCE_DIR}/install)

#set(CMAKE_BINARY_DIR  ${binary_dir})

install(TARGETS LT4_1 DESTINATION ${PROJECT_SOURCE_DIR}/install)


