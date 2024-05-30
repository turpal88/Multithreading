cmake_minimum_required(VERSION 3.20)
project(Lesson3_Task1 VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(SelectionSort)
add_executable(LT3_1)
set_target_properties(LT3_1 PROPERTIES LINKER_LANGUAGE CXX)
#set(headers ${CMAKE_SOURCE_DIR}/src/headers/lt3_1.h src/headers/selection_sort.h)
set(sources ${CMAKE_CURRENT_SOURCE_DIR}/src/sources/lt3_1.cxx)
target_sources(LT3_1 PRIVATE ${sources})

target_include_directories(LT3_1 PRIVATE 
${PROJECT_SOURCE_DIR}/SelectionSort/src/headers)

target_link_libraries(LT3_1 PRIVATE SelectionSort)



install(TARGETS LT3_1 DESTINATION ${PROJECT_SOURCE_DIR}/install)